from cs50 import SQL
import csv

with open("students.csv") as file:
    reader = csv.DictReader(file)
    db = SQL("sqlite:///roster.db")
    house_log = {}
    house_id = 1

    for row in reader:
        house = row['house']
        head = row['head']
        if house not in house_log:
            db.execute("INSERT INTO houses (id, house, head) VALUES (?, ?, ?)", house_id, house, head)
            house_log[house] = house_id
            house_id += 1

    file.seek(0)
    
    for data in reader:
        house = data['house']
        student_id = data['id']
        if house in house_log:
            db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student_id, house_log[house])