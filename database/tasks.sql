CREATE SCHEMA tasks_pw; -- nowa schema(folder) żeby w nim przechowywać zadania 
SELECT * FROM pg_catalog.pg_tables WHERE schemaname = 'tasks_pw'; -- sprawdzenie zawartości schemy

/*
============================================================================
### **Zadanie 1: System zarządzania projektami**
#### **Cel:**
Utwórz system do zarządzania projektami, który zawiera:
- Tabelę do przechowywania danych o projektach.
- Tabelę do przechowywania danych o zadaniach w projektach.
- Widok pokazujący podsumowanie projektów z liczbą zadań w każdym projekcie.
- Procedurę, która pozwala na dodanie nowego projektu z zadaniami.

#### **Wymagania:**
1. Utwórz tabelę `projects` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `name` (nazwa projektu),
   - `created_at` (data utworzenia projektu).
*/
   CREATE TABLE tasks_pw.projects
(
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

/*
2. Utwórz tabelę `tasks` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `project_id` (klucz obcy do `projects`),
   - `task_name` (nazwa zadania),
   - `status` (status zadania, np. TODO, IN_PROGRESS, DONE).
*/

CREATE TABLE tasks_pw.tasks
(
    id SERIAL PRIMARY KEY,
    project_id INT REFERENCES tasks_pw.tasks(id) ON DELETE CASCADE,
    task_name VARCHAR(255) NOT NULL,
    status VARCHAR(50) CHECK (status IN('TO_DO', 'IN_PROGRESS', 'DONE')) NOT NULL
);

/*
3. Utwórz widok `project_summary`, który pokazuje:
   - `id` projektu,
   - nazwę projektu,
   - liczbę zadań w projekcie,
   - liczbę ukończonych zadań.
*/

CREATE VIEW tasks_pw.project_summary AS
SELECT
    p.id AS id_project,
    p.name AS name_project,
    COUNT(t.id) AS total_tasks,
    COUNT(CASE WHEN t.status = 'DONE' THEN 1 END) AS completed_tasks
FROM tasks_pw.projects p
LEFT JOIN tasks_pw.tasks t ON p.id = t.project_id
GROUP BY p.name, p.id;


/*
4. Utwórz procedurę `add_project_with_tasks`, która:
   - Przyjmuje nazwę projektu i listę zadań.
   - Dodaje projekt i przypisuje do niego zadania.
*/

CREATE OR REPLACE PROCEDURE tasks_pw.add_project_with_tasks(
    project_name VARCHAR,
    task_names TEXT[] -- Tablica nazw zadań np ('Project A', ARRAY['Task 1', 'Task 2', 'Task 3'])
)
LANGUAGE plpgsql AS $$
DECLARE
    project_id INT;      -- Zmienna do przechowania ID projektu
    task_name TEXT;      -- Zmienna pomocnicza do przechowywania pojedynczego zadania
BEGIN
    INSERT INTO tasks_pw.projects (name)
    VALUES (project_name)
    RETURNING id INTO project_id;

    -- Iteracja po tablicy z zadaniami i dodanie ich do tabeli tasks
    FOREACH task_name IN ARRAY task_names LOOP
        INSERT INTO tasks_pw.tasks (project_id, task_name, status)
        VALUES (project_id, task_name, 'TO_DO');
    END LOOP;
END;
$$;

/*
============================================================================
============================================================================

### **Zadanie 2: Zarządzanie magazynem**
#### **Cel:**
Utwórz system zarządzania magazynem, który:
- Przechowuje dane o produktach i zamówieniach.
- Zawiera widok pokazujący aktualny stan magazynowy.
- Funkcję do sprawdzania dostępności produktu.
- Procedurę realizującą zamówienia.

#### **Wymagania:**
1. Utwórz tabelę `products` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `name` (nazwa produktu),
   - `stock` (ilość w magazynie),
   - `price` (cena produktu).
*/

CREATE TABLE tasks_pw.products
(
   id SERIAL PRIMARY KEY,
   name VARCHAR(255) NOT NULL,
   stock INT NOT NULL CHECK(stock >= 0),
   price NUMERIC(10,2) NOT NULL CHECK(price >=0)
);

/*
2. Utwórz tabelę `orders` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `product_id` (klucz obcy do `products`),
   - `quantity` (zamówiona ilość),
   - `order_date` (data zamówienia).
*/

CREATE TABLE tasks_pw.orders
(
   id SERIAL PRIMARY KEY,
   product_id INT REFERENCES products(id) ON DELETE CASCADE,
   quantity INT NOT NULL CHECK(quantity >= 0),
   order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

/*
3. Utwórz widok `inventory_status`, który pokazuje:
   - ID produktu,
   - nazwę produktu,
   - ilość w magazynie,
   - całkowitą wartość stanu magazynowego (`stock * price`).
*/

CREATE VIEW tasks_pw.inventory_status AS
SELECT
   p.id AS product_id,
   p.name AS product_name,
   p.stock AS total_products,
   stock * price AS total_value
FROM products p;

/*
4. Utwórz funkcję `check_availability(product_id INT, quantity INT)`, która sprawdza, czy zamówiona ilość produktu jest dostępna w magazynie.
*/

CREATE OR REPLACE FUNCTION tasks_pw.check_availability(product_id INT, quantity INT)
RETURNS BOOLEAN AS $$
DECLARE
   available_stock INT;
BEGIN
   SELECT stock INTO available_stock FROM products WHERE id = project_id;

IF available_stock < quantity THEN
   RETURN TRUE;
ELSE
   RETURN FALSE;
END IF;
END;
$$ LANGUAGE plpgsql;


/*
5. Utwórz procedurę `place_order(product_id INT, quantity INT)`, która:
   - Sprawdza dostępność produktu za pomocą funkcji `check_availability`.
   - Dodaje zamówienie do tabeli `orders`.
   - Aktualizuje ilość `stock` w tabeli `products`.
*/

CREATE OR REPLACE PROCEDURE tasks_pw.place_order(product_id INT, quantity INT)
LANGUAGE plpgsql AS $$
BEGIN
   IF NOT check_availability(product_id, quantity) THEN
      RAISE EXCEPTION 'Produkt o ID % ma niewystarczajacy stan magazynowy', product_id;
   END IF;

   INSERT INTO orders (product_id, quantity)
   VALUES(product_id, quantity);

   UPDATE products
   SET stock = stock - quantity
   WHERE id = product_id;

   RAISE NOTICE 'Zamówienie złożone pomyślnie dla produktu o ID %, ilość: %', product_id, quantity;
END;
$$;


/*
============================================================================
============================================================================
### **Zadanie 3: System rejestracji użytkowników**
#### **Cel:**
Utwórz system rejestracji użytkowników z:
- Tabelą przechowującą dane użytkowników.
- Widokiem pokazującym aktywnych użytkowników.
- Funkcją sprawdzającą poprawność adresu e-mail.
- Procedurą rejestracji użytkownika.

#### **Wymagania:**
1. Utwórz tabelę `users` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `username` (unikalna nazwa użytkownika),
   - `email` (adres e-mail),
   - `is_active` (flaga aktywności: TRUE/FALSE),
   - `created_at` (data utworzenia konta).
*/

CREATE TABLE tasks_pw.users
(
   id SERIAL PRIMARY KEY,
   username VARCHAR(255) UNIQUE NOT NULL,
   email TEXT NOT NULL,
   is_active BOOLEAN DEFAULT TRUE,
   created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

/*
2. Utwórz widok `active_users`, który pokazuje:
   - ID użytkownika,
   - nazwę użytkownika,
   - adres e-mail.
*/

CREATE VIEW tasks_pw.active_users AS
SELECT
   id AS id_user,
   username AS name_user,
   email AS email_user
FROM tasks_pw.users
WHERE is_active = TRUE;

/*
3. Utwórz funkcję `validate_email(email TEXT)`, która:
   - Sprawdza, czy adres e-mail zawiera znak `@` i końcówkę domeny (np. `.com`).
*/

CREATE OR REPLACE FUNCTION tasks_pw.validate_email(email TEXT)
RETURNS BOOLEAN AS $$
BEGIN
   IF email LIKE '%@%.%' THEN
      RETURN TRUE;
   ELSE
      RETURN FALSE;
   END IF;
END;
$$ LANGUAGE plpgsql;

/*
4. Utwórz procedurę `register_user(username TEXT, email TEXT)`, która:
   - Waliduje adres e-mail za pomocą funkcji `validate_email`.
   - Dodaje nowego użytkownika do tabeli `users` z `is_active` ustawionym na TRUE.
*/

CREATE OR REPLACE PROCEDURE tasks_pw.register_user(username TEXT, email TEXT)
LANGUAGE plpgsql AS $$
BEGIN
   IF validate_email(email) THEN
      INSERT INTO users(username, email, is_active)
      VALUES (username, email);
   ELSE
      RAISE EXCEPTION 'Invalid email address: %', email;
   END IF;
END;
$$;

/*
============================================================================
============================================================================
### **Zadanie 4: System raportowania sprzedaży**
#### **Cel:**
Utwórz system raportowania sprzedaży:
- Przechowuj dane o sprzedaży i produktach.
- Utwórz widok pokazujący miesięczne podsumowanie sprzedaży.
- Utwórz funkcję obliczającą całkowitą sprzedaż dla produktu.
- Utwórz procedurę generującą raport sprzedaży.

#### **Wymagania:**
1. Utwórz tabelę `sales` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `product_id` (klucz obcy do tabeli `products`),
   - `quantity` (sprzedana ilość),
   - `sale_date` (data sprzedaży).
*/

CREATE TABLE tasks_pw.sales
(
   id SERIAL PRIMARY KEY,
   product_id INT REFERENCES products(id),
   quantity INT CHECK(quantity > 0) NOT NULL,
   sale_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

/*
2. Utwórz widok `monthly_sales_summary`, który pokazuje:
   - Miesiąc,
   - ID produktu,
   - nazwę produktu,
   - sumę sprzedanych jednostek w danym miesiącu.
*/

CREATE VIEW tasks_pw.monthly_sales_summary AS
SELECT
   EXTRACT(MONTH FROM sale_date) AS Month,
   product_id,
   products.name AS name_product,
   SUM(quantity) AS sale_total
FROM tasks_pw.sales
JOIN tasks_pw.products ON tasks_pw.sales.product_id = tasks_pw.products.id
GROUP BY EXTRACT(MONTH FROM sale_date), product_id, products.name;

/*
3. Utwórz funkcję `get_total_sales(product_id INT)`, która oblicza całkowitą ilość sprzedanego produktu.
*/

CREATE OR REPLACE FUNCTION tasks_pw.get_total_sales(product_id INT)
 -- parametry podane w () przy tworzeniu funkcji/procedury to parametry ktore podaje uzytkownik podczas wywolania funkcji/procedury
RETURN INT AS $$
DECLARE
   total_sales INT;
BEGIN
   SELECT SUM(quantity) INTO total_sales
   FROM tasks_pw.sales
   WHERE product_id = product_id;

   RETURN total_sales;
END;
$$ LANGUAGE plpgsql;

/*
4. Utwórz procedurę `generate_sales_report(month INT, year INT)`, która generuje raport sprzedaży dla danego miesiąca i roku, zapisując go w nowej tabeli `sales_report`.
*/

CREATE OR REPLACE PROCEDURE generate_sales_report(month INT, year INT)
LANGUAGE plpgsql AS $$
BEGIN
   -- Usunięcie istniejących danych dla danego miesiąca i roku
   DELETE FROM tasks_pw.sales_report WHERE month = generate_sales_report.month AND year = generate_sales_report.year;

   -- Wstawienie nowego raportu
   INSERT INTO tasks_pw.sales_report (month, year, product_id, product_name, total_quantity)
   SELECT
      month,
      year,
      products.id AS product_id,
      products.name AS product_name,
      SUM(sales.quantity) AS total_quantity
   FROM tasks_pw.sales AS sales
   JOIN tasks_pw.products AS products ON sales.product_id = products.id
   WHERE EXTRACT(MONTH FROM sales.sale_date) = month AND EXTRACT(YEAR FROM sales.sale_date) = year
   GROUP BY products.id, products.name;
END;
$$;


/*
============================================================================
============================================================================
### **Zadanie 5: Zarządzanie książkami w bibliotece**
#### **Cel:**
Utwórz system do zarządzania książkami i wypożyczeniami:
- Przechowuj dane o książkach i wypożyczeniach.
- Utwórz widok pokazujący dostępne książki.
- Utwórz funkcję obliczającą czas wypożyczenia.
- Utwórz procedurę obsługującą wypożyczenie książki.

#### **Wymagania:**
1. Utwórz tabelę `books` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `title` (tytuł książki),
   - `author` (autor),
   - `is_available` (flaga dostępności: TRUE/FALSE).
*/



/*
2. Utwórz tabelę `borrowings` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `book_id` (klucz obcy do tabeli `books`),
   - `borrow_date` (data wypożyczenia),
   - `return_date` (data zwrotu).
*/



/*
3. Utwórz widok `available_books`, który pokazuje wszystkie dostępne książki (`is_available = TRUE`).
*/



/*
4. Utwórz funkcję `calculate_borrow_days(borrow_date DATE, return_date DATE)`, która oblicza liczbę dni wypożyczenia.
*/



/*
5. Utwórz procedurę `borrow_book(book_id INT, borrow_date DATE)`, która:
   - Sprawdza, czy książka jest dostępna.
   - Ustawia `is_available = FALSE` w tabeli `books`.
   - Dodaje wpis do tabeli `borrowings`.
*/



/*
   ============================================================================
   