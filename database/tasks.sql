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



/*
2. Utwórz tabelę `orders` z kolumnami:
   - `id` (klucz główny, numer seryjny),
   - `product_id` (klucz obcy do `products`),
   - `quantity` (zamówiona ilość),
   - `order_date` (data zamówienia).
*/



/*
3. Utwórz widok `inventory_status`, który pokazuje:
   - ID produktu,
   - nazwę produktu,
   - ilość w magazynie,
   - całkowitą wartość stanu magazynowego (`stock * price`).
*/



/*
4. Utwórz funkcję `check_availability(product_id INT, quantity INT)`, która sprawdza, czy zamówiona ilość produktu jest dostępna w magazynie.
*/



/*
5. Utwórz procedurę `place_order(product_id INT, quantity INT)`, która:
   - Sprawdza dostępność produktu za pomocą funkcji `check_availability`.
   - Dodaje zamówienie do tabeli `orders`.
   - Aktualizuje ilość `stock` w tabeli `products`.
*/



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



/*
2. Utwórz widok `active_users`, który pokazuje:
   - ID użytkownika,
   - nazwę użytkownika,
   - adres e-mail.
*/



/*
3. Utwórz funkcję `validate_email(email TEXT)`, która:
   - Sprawdza, czy adres e-mail zawiera znak `@` i końcówkę domeny (np. `.com`).
*/



/*
4. Utwórz procedurę `register_user(username TEXT, email TEXT)`, która:
   - Waliduje adres e-mail za pomocą funkcji `validate_email`.
   - Dodaje nowego użytkownika do tabeli `users` z `is_active` ustawionym na TRUE.
*/



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



/*
2. Utwórz widok `monthly_sales_summary`, który pokazuje:
   - Miesiąc,
   - ID produktu,
   - nazwę produktu,
   - sumę sprzedanych jednostek w danym miesiącu.
*/



/*
3. Utwórz funkcję `get_total_sales(product_id INT)`, która oblicza całkowitą ilość sprzedanego produktu.
*/



/*
4. Utwórz procedurę `generate_sales_report(month INT, year INT)`, która generuje raport sprzedaży dla danego miesiąca i roku, zapisując go w nowej tabeli `sales_report`.
*/



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
   