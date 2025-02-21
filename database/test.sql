SELECT * FROM pg_catalog.pg_tables;
\c hotel_management;
CREATE DATABASE hotel_managment;
-------------------------------------------
CREATE SCHEMA views_schema;
CREATE SCHEMA procedures_schema;
-------------------------------------------

----------------zrobic po utworzeniu tabel------------------
CREATE USER order_user WITH PASSWORD 'securepassword123';
GRANT INSERT ON public.reservations TO order_user;
GRANT UPDATE ON public.rooms TO order_user;
GRANT SELECT ON views_schema.available_rooms TO order_user;

CREATE USER stats_user WITH PASSWORD 'securepassword123';
GRANT SELECT ON views_schema.room_type_statistics TO stats_user;
GRANT SELECT ON views_schema.available_rooms TO stats_user;
GRANT SELECT ON views_schema.reservation_details TO stats_user;


CREATE TABLE public.guests (
    guest_id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    surname TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL,
    phone_number TEXT UNIQUE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP 

);

--------------------------------------------------------------------------------------

CREATE TABLE public.rooms (
    room_id SERIAL PRIMARY KEY,
    room_number INT UNIQUE NOT NULL,
    room_type TEXT CHECK (room_type IN ('Single', 'Double', 'Suite')) NOT NULL,
    price_per_night NUMERIC(10, 2) NOT NULL,
    is_available BOOLEAN DEFAULT TRUE
);

--------------------------------------------------------------------------------------

CREATE TABLE public.reservations (
    reservation_id SERIAL PRIMARY KEY,
    guest_id INT REFERENCES public.guests(guest_id) ON DELETE CASCADE,
    room_id INT REFERENCES public.rooms(room_id) ON DELETE CASCADE,
    check_in_date DATE NOT NULL,
    check_out_date DATE NOT NULL,
    total_cost NUMERIC(10, 2) NOT NULL,
    reservation_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT valid_dates CHECK (check_out_date > check_in_date)
);

--------------------------------------------------------------------------------------

CREATE VIEW views_schema.available_rooms AS
SELECT
    room_id,
    room_number,
    room_type,
    price_per_night
FROM public.rooms
WHERE is_available = TRUE;

--------------------------------------------------------------------------------------

CREATE VIEW views_schema.reservation_details AS
SELECT
    r.reservation_id,
    r.guest_id,
    CONCAT(g.name, ' ', g.surname) AS guest_name,
    r.room_id,
    rm.room_number,
    r.check_in_date,
    r.check_out_date,
    r.total_cost
FROM reservations r
JOIN public.guests g ON r.guest_id = g.guest_id
JOIN public.rooms rm ON r.room_id = rm.room_id;


--------------------------------------------------------------------------------------

CREATE MATERIALIZED VIEW views_schema.room_type_statistics AS
SELECT
    room_type,
    AVG(price_per_night) AS average_price_per_night
FROM public.rooms
GROUP BY room_type;

--------------------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION procedures_schema.calculate_reservation_cost(
    room_id INT,
    check_in_date DATE,
    check_out_date DATE
) RETURNS NUMERIC AS $$
DECLARE
    price_per_night NUMERIC;
    total_days INT;
BEGIN
    SELECT price_per_night INTO price_per_night
    FROM public.rooms
    WHERE id = room_id;

    total_days := check_out_date - check_in_date;

    RETURN price_per_night * total_days;
END;
$$ LANGUAGE plpgsql;

--------------------------------------------------------------------------------------

CREATE OR REPLACE PROCEDURE procedures_schema.create_reservation(
    guest_id INT,
    room_id INT,
    check_in_date DATE,
    check_out_date DATE
)
LANGUAGE plpgsql AS $$
BEGIN
    INSERT INTO public.reservations (
        guest_id, room_id, check_in_date, check_out_date, total_cost)
    VALUES (
        guest_id,
        room_id,
        check_in_date,
        check_out_date,
        procedures_schema.calculate_reservation_cost(room_id, check_in_date, check_out_date)
    );

    UPDATE public.rooms
    SET is_available = FALSE
    WHERE id = room_id;
END;
$$;

--------------------------------------------------------------------------------------

CREATE INDEX idx_guests_email
ON public.guests (email);

--------------------------------------------------------------------------------------


CREATE INDEX idx_rooms_room_type
ON public.rooms (room_type);

--------------------------------------------------------------------------------------


CREATE INDEX idx_reservations_dates
ON public.reservations (check_in_date, check_out_date);


--------------------------------------------------------------------------------------


CREATE OR REPLACE FUNCTION procedures_schema.set_room_available()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE public.rooms
    SET is_available = TRUE
    WHERE room_id = OLD.room_id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

--------------------------------------------------------------------------------------

CREATE TRIGGER after_reservation_delete
AFTER DELETE ON public.reservations
FOR EACH ROW
EXECUTE FUNCTION procedures_schema.set_room_available();

--------------------------------------------------------------------------------------


INSERT INTO public.guests (name, surname, email, phone_number)
VALUES 
('Anna', 'Kowalska', 'anna.kowalska@example.com', '123456789'),
('Jan', 'Nowak', 'jan.nowak@example.com', '987654321');

INSERT INTO public.rooms (room_number, room_type, price_per_night, is_available)
VALUES 
(101, 'Single', 150, TRUE),
(102, 'Double', 250, TRUE),
(201, 'Suite', 500, TRUE);

INSERT INTO public.reservations (guest_id, room_id, check_in_date, check_out_date, total_cost)
VALUES 
(1, 101, '2025-01-01', '2025-01-05', 600),
(2, 102, '2025-01-02', '2025-01-06', 1000);




SELECT * FROM views_schema.available_rooms;

SELECT * FROM views_schema.reservation_details;

SELECT * FROM views_schema.room_type_statistics;


SELECT procedures_schema.calculate_reservation_cost(101, '2025-01-01', '2025-01-05');


CALL procedures_schema.create_reservation(1, 201, '2025-01-10', '2025-01-15');


DELETE FROM public.reservations WHERE reservation_id = 1;

SELECT * FROM public.rooms WHERE room_id = 101;
