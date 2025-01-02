/*
sudo -i -u postgres
psql
*/

CREATE TABLE account (
    account_id SERIAL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL CHECK (first_name !~ '\\s'), 
    last_name VARCHAR(50) NOT NULL CHECK (last_name !~ '\\s'), 
    email VARCHAR(100) NOT NULL UNIQUE CHECK (email ~ '^[^@]+@[^@]+\.[^@]+$'), 
    password VARCHAR(255) NOT NULL CHECK (LENGTH(password) >= 8) 
);


CREATE RECURSIVE VIEW employee_hierarchy (employee_id, employee_name, manager_id, level) AS (
    SELECT
        id AS employee_id,
        name AS employee_name,
        manager_id,
        1 AS level
    FROM
        employees
    WHERE
        manager_id IS NULL
    UNION ALL
    SELECT
        e.id AS employee_id,
        e.name AS employee_name,
        e.manager_id,
        eh.level + 1
    FROM
        employees e
    JOIN
        employee_hierarchy eh
    ON
        e.manager_id = eh.employee_id
);


SELECT * FROM employee_hierarchy ORDER BY level, employee_name;


CREATE TABLE accounts (
    account_id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    email VARCHAR(100) NOT NULL UNIQUE,
    balance NUMERIC(10, 2) DEFAULT 0,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO accounts (username, email, balance, is_active, created_at)
VALUES
('john_doe','john.doe@example.com', 100.00, TRUE, CURRENT_TIMESTAMP),
('jane_doe','jane.doe@example.com', 0, TRUE, CURRENT_TIMESTAMP),
('inactive_user','inactive.user.doe@example.com', 50.00, FALSE, CURRENT_TIMESTAMP),
('active_user','active.user@example.com', 200.00, TRUE, CURRENT_TIMESTAMP),
('zero_balance','zero.balance@example.com', 0, TRUE, CURRENT_TIMESTAMP);


CREATE VIEW editable_accounts AS
SELECT account_id, username, email, balance, is_active
FROM accounts
WHERE is_active = TRUE AND balance > 0
WITH LOCAL CHECK OPTION;

CREATE VIEW readonly_accounts AS
SELECT account_id, username, email, balance, is_active
FROM accounts
WHERE balance = 0;

CREATE MATERIALIZED VIEW materialized_accounts AS
SELECT account_id, username, email, balance, is_active, created_at
FROM editable_accounts
WHERE is_active = TRUE AND balance > 50
WITH DATA;

UPDATE editable_accounts
SET balance = balance - 50
WHERE username = 'john_doe';

UPDATE editable_accounts
SET balance = 10
WHERE username = 'john_doe';

UPDATE readonly_accounts
SET balance = 10
WHERE username = 'jane_doe';



CREATE OR REPLACE FUNCTION calculate_rectangle_area(length NUMERIC, width NUMERIC)
RETURNS NUMERIC AS $$
BEGIN
    RETURN length * width;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION count_character_occurrences(input_txt TEXT, characterr TEXT)
RETURNS INTEGER AS $$
BEGIN
    RETURN LENGTH(input_txt) - LENGTH(REPLACE(input_txt, characterds, ''));
END;
$$ LANGUAGE plpgsql;