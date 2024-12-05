CREATE TABLE account (
    account_id SERIAL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL CHECK (first_name !~ '\\s'), 
    last_name VARCHAR(50) NOT NULL CHECK (last_name !~ '\\s'), 
    email VARCHAR(100) NOT NULL UNIQUE CHECK (email ~ '^[^@]+@[^@]+\.[^@]+$'), 
    password VARCHAR(255) NOT NULL CHECK (LENGTH(password) >= 8) 
);
