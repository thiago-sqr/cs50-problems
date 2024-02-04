-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Finding the crime scene description
SELECT description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';
-- Theft took place at 10:15
-- 3 witnesses, each interview transcript mentions bakery
-- Littering took place at 16:36??


-- searching transcripts about bakery
SELECT name, year, month, day, transcript
FROM interviews
WHERE transcript
LIKE '%bakery%';
-- ruth: seek for bakery security logs within 10 min after theft
-- eugene: search for ATM transactions on that day
-- raymond: seek for the earliest flight of day 29, accomplice purchased the flight ticket


-- earliest flights on July 29th, origin: Fiftyville
SELECT *
FROM flights
WHERE origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
)
AND year = 2023
AND month = 7
AND day = 29;
-- hour: 8:20 AM
-- destiny id: 4
-- flight id: 36


-- searching for airport id = 4
SELECT *
FROM airports
WHERE id = 4;
-- LaGuardia Airport, New York City


-- people who took the earliest flight on July 29th
SELECT name
FROM people
WHERE people.passport_number IN (
    SELECT passengers.passport_number
    FROM passengers
    WHERE flight_id = 36
);


-- account numbers of people who withdrew money on that day
SELECT id, account_number, amount
FROM atm_transactions
WHERE year = 2023
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';


-- license plates of vehicles whose drivers left the bakery within 10 minutes after the theft
SELECT minute, license_plate
FROM bakery_security_logs
WHERE year = 2023
AND month = 7
AND day = 28
AND activity = 'exit'
AND hour = 10
AND minute >= 15
AND minute <= 25;


-- name of owners of these license plates
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND activity = 'exit'
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
);


-- names of people who made phone calls on that day with a duration of less than 1 minute
SELECT name
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year= 2023
    AND month = 7
    AND day = 28
    AND duration < 60
);


-- people who match all the searches above
SELECT name
FROM people
JOIN bank_accounts
ON id = person_id
WHERE name IN (
    SELECT name
    FROM people
    WHERE people.passport_number IN (
        SELECT passengers.passport_number
        FROM passengers
        WHERE flight_id = 36
    )
)
AND name IN (
    SELECT name
    FROM people
    WHERE phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year= 2023
        AND month = 7
        AND day = 28
        AND duration <= 60
    )
)
AND name IN (
    SELECT name
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND activity = 'exit'
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
    )
)
AND account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND transaction_type = 'withdraw'
    AND atm_location = 'Leggett Street'
);
-- THE THIEF WAS BRUCE


-- person who received a phone call from Bruce on that day
SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year= 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller = (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
);
-- ACCOMPLICE WAS ROBIN
