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
    RETURN LENGTH(input_txt) - LENGTH(REPLACE(input_txt, characterr, ''));
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE VIEW user_view AS
SELECT id, username, email FROM users;

CREATE OR REPLACE FUNCTION handle_view_changes()
RETURN TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        INSERT INTO users (username,email) VALUES (NEW.username, NEW.email);
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER instead_of_trigger
INSTEAD OF INSERT
ON user_view
FOR EACH ROW
EXECUTE FUNCTION handle_view_changes();

============================================================

CREATE TABLE projects (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    create_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP 
);

CREATE TABLE tasks (
    id SERIAL PRIMARY KEY,
    project_id INT REFERENCES projects(id) ON DELETE CASCADE,
    task_name VARCHAR(255) NOT NULL,
    status VARCHAR(50) CHECK (status IN ('TO_DO', 'IN_PROGRESS', 'DONE')) NOT NULL
);

CREATE VIEW project_summary AS 
SELECT 
    p.id AS project_id,
    p.name AS project_name,
    COUNT(t.id) AS total_tasks,
    COUNT(CASE WHEN t.status = 'DONE' THEN 1 END) AS completed
FROM 
    projects p 
LEFT JOIN 
    tasks t ON p.id = t.project_id
GROUP BY 
    p.id, p.name;


CREATE PROCEDURE add_project_with_tasks(
    project_name VARCHAR,
    task_list TEXT[]
)
LANGUAGE plpgsql
AS $$
DECLARE 
    project_id INT;
    task_name TEXT;

BEGIN 
    INSERT INTO projects (name) VALUES (project_name)
    RETURNING id INTO project_id;

    FOREACH task_name IN ARRAY task_list LOOP 
        INSERT INTO tasks (project_id, task_name, status)
        VALUES (project_id, task_name, 'TODO');
    END LOOP;
END;
$$;

==============================================

CREATE TABLE products(
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    stock INT NOT NULL CHECK (stock >= 0),
    price NUMERIC(10,2) NOT NULL CHECK (price >=0)
);

CREATE TABLE orders(
    id SERIAL PRIMARY KEY,
    product_id INT REFERENCES products(id) ON DELETE CASCADE,
    quantity INT NOT NULL CHECK (quantity > 0),
    order_data TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE VIEW inventory_status AS 
SELECT 
    id AS product_id,
    name AS product_name,
    stock AS stock_quantity
FROM products;

INSERT INTO products(name, stock, price)


