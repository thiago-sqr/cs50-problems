CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    symbol_id INTEGER NOT NULL,
    type TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    date DATETIME NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id),
    FOREIGN KEY(symbol_id) REFERENCES symbols(id)
);

CREATE TABLE symbols (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    symbol TEXT NOT NULL
);

CREATE UNIQUE INDEX symbol ON symbols (symbol);

CREATE TABLE holdings (
    user_id INTEGER NOT NULL,
    symbol_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id),
    FOREIGN KEY(symbol_id) REFERENCES symbols(id)
);