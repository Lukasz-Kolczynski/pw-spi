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