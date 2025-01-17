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
    stock,
    stock * price AS total_value
FROM products;

INSERT INTO products (name, price, stock)
VALUES
    ('Mleko', 2.50, 100),
    ('Chleb', 1.80, 150),
    ('Jajka', 3.20, 200);


DELETE FROM products WHERE name = 'mleko' AND stock = 5;


CREATE OR REPLACE FUNCTION check_availability(product_id INT, quantity INT)
RETURNS BOOLEAN AS $$
DECLARE
    available_stock INT;
BEGIN 

    SELECT stock INTO available_stock
    FROM products
    WHERE id = product_id;


    IF available_stock >= quantity THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END;
$$ LANGUAGE plpgsql;

=============================================

CREATE TABLE users(
    id SERIAL PRIMARY KEY,
    username VARCHAR(255) UNIQUE NOT NULL,
    email TEXT NOT NULL,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE VIEW active_users AS
SELECT
    id AS user_id,
    username AS user_name,
    email AS user_email
FROM users
WHERE is_active = TRUE;

CREATE OR REPLACE FUNCTION validate_email(email TEXT)
RETURNS BOOLEAN AS $$
BEGIN
    IF email LIKE '%@%.%' THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE register_user(username VARCHAR(255), email TEXT)
LANGUAGE plpgsql AS $$
BEGIN
    IF validate_email(email) THEN
        INSERT INTO users (username, email, is_active)
        VALUES (username, email, TRUE);
    ELSE
        RAISE EXCEPTION 'Invalid email format';
    END IF;
END;
$$;

CALL register_user('john_doe', 'john.doeexample.com'); -- invalid insert email

CALL register_user('john_doe', 'john.doe@example.com'); -- Insert complete


========================================

CREATE TABLE sales (
    id SERIAL PRIMARY KEY,
    product_id INT REFERENCES products(id),
    quantity INT NOT NULL CHECK (quantity > 0),
    sale_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE VIEW monthly_sales_summary AS
SELECT
    EXTRACT(MONTH FROM sale_date) AS month,
    s.product_id,
    p.name AS product_name,
    SUM(s.quantity) AS total_sales
FROM sales s
JOIN products p ON s.product_id = p.id
GROUP BY EXTRACT(MONTH FROM sale_date), s.product_id, p.name;



INSERT INTO sales (product_id, quantity, sale_date)
VALUES
    (5, 50, '2025-01-10'),
    (6, 100, '2025-01-15'),
    (7, 80, '2025-01-20'),
    (5, 70, '2025-02-10'),
    (6, 150, '2025-02-15'),
    (7, 100, '2025-02-20');


==============================
/*
### **Zadanie 5: Zarządzanie książkami w bibliotece**
#### **Cel:**
Utwórz system do zarządzania książkami i wypożyczeniami:
- Przechowuj dane o książkach i wypożyczeniach.
- Utwórz widok pokazujący dostępne książki.
- Utwórz funkcję obliczającą czas wypożyczenia.
- Utwórz procedurę obsługującą wypożyczenie książki.

#### **Wymagania:**
1. Utwórz tabelę books z kolumnami:
   - id (klucz główny, numer seryjny),
   - title (tytuł książki),
   - author (autor),
   - is_available (flaga dostępności: TRUE/FALSE).

2. Utwórz tabelę borrowings z kolumnami:
   - id (klucz główny, numer seryjny),
   - book_id (klucz obcy do tabeli books),
   - borrow_date (data wypożyczenia),
   - return_date (data zwrotu).

3. Utwórz widok available_books, który pokazuje wszystkie dostępne książki (is_available = TRUE).

4. Utwórz funkcję calculate_borrow_days(borrow_date DATE, return_date DATE), która oblicza liczbę dni wypożyczenia.

5. Utwórz procedurę borrow_book(book_id INT, borrow_date DATE), która:
   - Sprawdza, czy książka jest dostępna.
   - Ustawia is_available = FALSE w tabeli books.
   - Dodaje wpis do tabeli borrowings.
*/

CREATE TABLE books(
    id SERIAL PRIMARY KEY,
    title VARCHAR (255) NOT NULL,
    author VARCHAR (50) NOT NULL,
    is_available BOOLEAN DEFAULT TRUE
);

INSERT INTO books (title, author, is_available)
VALUES
    ('Wiedźmin', 'Andrzej Sapkowski', TRUE),
    ('Harry Potter', 'J.K. Rowling', TRUE),
    ('Hobbit', 'J.R.R. Tolkien', TRUE);



CREATE TABLE borrowings(
    id SERIAL PRIMARY KEY,
    book_id INT REFERENCES books(id),
    borrow_date DATE NOT NULL,
    return_date DATE
);

-- Wypożyczenie książki o ID = 1
CALL borrow_book(1, '2025-01-15');



CREATE VIEW available_books AS
SELECT
    id AS id_book,
    title AS title_book,
    author AS author_book
FROM books
WHERE is_available = TRUE;

CREATE OR REPLACE FUNCTION calculate_borrow_days(borrow_date DATE, return_date DATE)
RETURNS INT AS $$
BEGIN
    RETURN (return_date - borrow_date);
END;
$$ LANGUAGE plpgsql;

UPDATE borrowings
SET return_date = '2025-01-20'
WHERE book_id = 1;

SELECT calculate_borrow_days('2025-01-10', '2025-01-20');



CREATE OR REPLACE PROCEDURE borrow_book(book_id INT, borrow_date DATE)
LANGUAGE plpgsql AS $$
BEGIN
    IF EXISTS (SELECT 1 FROM books WHERE id = book_id AND is_available = TRUE) THEN
        UPDATE books
        SET is_available = FALSE
        WHERE id = book_id;

        INSERT INTO borrowings (book_id, borrow_date)
        VALUES(book_id, borrow_date);

    ELSE
        RAISE EXCEPTION 'Książka o ID % jest już wypożyczona', book_id;
    END IF;
END;
$$;

CALL borrow_book(1, '2025-01-16');

