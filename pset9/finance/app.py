import os
import datetime as dt

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Configure current date and time
date = dt.datetime.now()


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query for the user's symbols and shares
    user_id = session["user_id"]
    stocks = db.execute(
        "SELECT symbol, quantity AS shares FROM symbols JOIN holdings ON symbol_id = symbols.id WHERE user_id = ?", user_id
    )

    # Query for the username
    username = (db.execute("SELECT username FROM users WHERE id = ?", user_id))[0]["username"]
    total_sum = 0

    # Search for the current price of each stock and calculate the total value of each holding
    for row in stocks:
        result = lookup(row["symbol"])
        row["price"] = usd(result["price"])
        row["total"] = usd(result["price"] * row["shares"])
        total_sum += result["price"] * row["shares"]

    # Query for the current user's cash
    user_cash = (db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"]))[0]["cash"]

    # Sum everything
    total_sum += user_cash

    # Render a table with all user's stock information
    return render_template("index.html", username=username, stocks=stocks, user_cash=usd(user_cash), total_sum=usd(total_sum))



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    user_id = session["user_id"]

    if request.method == "POST":

        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a symbol")

        # Ensure symbol exists
        result = lookup(symbol)
        if result is None:
            return apology("invalid symbol")

        # Ensure shares were submitted
        shares = request.form.get("shares")
        if not shares:
            return apology("missing shares")

        # Ensures shares are a positive number
        try:
            shares = int(shares)
        except ValueError:
            return apology("shares must be a number")
        if shares < 1:
            return apology("shares must be a positive number")

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        total_price = result["price"] * shares

        # Ensure user has enough cash
        if user_cash[0]["cash"] < total_price:
            return apology("not enough cash to buy share(s)")

        # Verifies if symbol already exists in database
        search_symbol = db.execute("SELECT id FROM symbols WHERE symbol = ?", result["symbol"])
        if not search_symbol:
            symbol_id = db.execute("INSERT INTO symbols (symbol) VALUES (?)", result["symbol"])
        else:
            symbol_id = search_symbol[0]["id"]

        # Update user's current cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, user_id)

        # Insert purchase information into database
        db.execute(
            "INSERT INTO transactions (user_id, symbol_id, type, shares, price, date) VALUES (?, ?, ?, ?, ?, ?)",
            user_id, symbol_id, "buy", shares, result["price"], date
        )

        # Update total number of user's shares
        search_holding = db.execute("SELECT * FROM holdings WHERE symbol_id = ? AND user_id = ?", symbol_id, user_id)
        if not search_holding:
            db.execute("INSERT INTO holdings (symbol_id, user_id, quantity) VALUES (?, ?, ?)", symbol_id, user_id, shares)
        else:
            db.execute("UPDATE holdings SET quantity = quantity + ?", shares)

        # Redirect user to home page
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query database for transaction data
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, type, shares, price, date FROM transactions JOIN symbols ON symbol_id = symbols.id WHERE user_id = ?", user_id
    )

    # Format prices as USD
    for row in transactions:
        row["price"] = usd(row["price"])

    # Render data in history page
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide a symbol")

        # Search for the symbol and its price
        result = lookup(symbol)
        if result is None:
            return apology("invalid symbol")

        # Show quote result to the user
        return render_template("quoted.html", symbol=result["symbol"], price=usd(result["price"]))

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username")

        # Ensure password was subimitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password")

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must confirm your password")

        # Password validation
        if password != request.form.get("confirmation"):
            return apology("passwords must be the same")

        hash = generate_password_hash(password, method='pbkdf2', salt_length=16)

        # Ensure the user has a unique username and insert into database
        try:
            user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            session["user_id"] = user_id
        except ValueError:
            return apology("username already exists")

        # Redirect user to home page
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Query for shares that the user owns
    user_id = session["user_id"]
    stock_symbols = db.execute(
        "SELECT symbol, symbol_id FROM holdings JOIN symbols ON symbol_id = symbols.id WHERE user_id = ?", user_id
    )

    if request.method == "POST":

        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("missing symbol")

        # Ensure user owns shares for that symbol
        for row in stock_symbols:
            if symbol == row["symbol"]:
                symbol_id = row["symbol_id"]
                break
        else:
            return apology("invalid symbol")

        # Ensure shares were submitted
        shares = request.form.get("shares")
        if not shares:
            return apology("missing shares")

        # Ensure shares are a positive number
        try:
            shares = int(shares)
        except ValueError:
            return apology("shares must be a number")
        if shares < 1:
            return apology("shares must be a positive number")

        # Ensure user owns enough shares to sell and update total number of user's shares
        search_holding = db.execute("SELECT * FROM holdings WHERE symbol_id = ? AND user_id = ?", symbol_id, user_id)
        if not search_holding:
            return apology("something went wrong")
        elif shares > search_holding[0]["quantity"]:
            return apology("not enough shares to sell")
        else:
            db.execute("UPDATE holdings SET quantity = quantity - ? WHERE user_id = ? AND symbol_id = ?", shares, user_id, symbol_id)
            db.execute("DELETE FROM holdings WHERE quantity <= 0 AND user_id = ? AND symbol_id = ?", user_id, symbol_id)

        # Update user's cash
        result = lookup(symbol)
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", result["price"] * shares, user_id)

        # Update transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol_id, type, shares, price, date) VALUES (?, ?, ?, ?, ?, ?)",
            user_id, symbol_id, "sell", shares, result["price"], date
        )

        # Redirect user to home page
        return redirect("/")

    return render_template("sell.html", stock_symbols=stock_symbols)
