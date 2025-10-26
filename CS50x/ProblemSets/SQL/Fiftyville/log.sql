-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Use .schema command to understand what's in the database
-- Ten tables. Three types.
-- 1)Theft: crime_scene_reports | interviews | bakery_security_logs
-- 2)Airplane: airports | flights | passengers
-- 3)Others: people | phone_calls | bank_accounts | atm_transactions

-- .......................................................................

-- Initial information: 2024.7.28 Humphrey Street
-- 1、Find reports about the theft based on the time and location of the theft from crime_scene_reports

SELECT description FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Get information:
-- 1、Theft took place at 10:15am at the Humphrey Street bakery.
-- 2、Three witnesses were interviewed that day and all of them mentioned bakery

-- .......................................................................

-- 2、Find witness testimony based on date and keywords

SELECT transcript FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Get information:
-- 1、10.15am-10.25am, the thief into a car and left from bakery parking lot
-- 2、2024.7.28, morning, the thief used ATM to withdraw money on Leggett Street [USED]
-- 3、2024.7.28, the thief had a call(<1min) with his accomplice. [USED]
-- 4、The thief took 7.29' earliest flight out of Fiftyville. [USED]
-- 5、The accomplice bought the tickets.

-- .......................................................................

-- 3、Find out where the thief went based on the flight information
SELECT A.city, flights.id FROM airports AS A
JOIN flights ON A.id = destination_airport_id
JOIN airports AS B ON B.id = origin_airport_id
WHERE B.city = 'Fiftyville' AND year = 2024 AND month = 7 AND day = 29
ORDER BY hour LIMIT 1;

-- Get information: The thief escaped to the New York City and the flight id was 36

-- .......................................................................

-- 4、The identity of the thief is determined based on the thief's morning phone records,
--    withdrawal information and passenger information of the flight he took

SELECT name FROM people
JOIN bank_accounts ON person_id = people.id
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2024 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
AND phone_calls.year = 2024 AND phone_calls.month = 7 AND phone_calls.day = 28
AND phone_calls.duration < 60 AND passengers.flight_id = 36 ;

-- Get information: Bruce Kenny Taylor(Three suspects)

-- .......................................................................

-- 5、Check whether any of the three people left the bakery by car between 10.15am-10.25am
SELECT name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2024 AND month = 7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = 'exit' AND name IN ('Bruce', 'Kenny', 'Taylor');

-- Get result: Bruce

-- .......................................................................

-- 6、Find the accomplices of Bruce based on the call records
SELECT A.name FROM people AS A
JOIN phone_calls ON A.phone_number = receiver
JOIN people AS B ON caller = B.phone_number
WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60 AND B.name = 'Bruce';

-- Get reuslt: Robin
