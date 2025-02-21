CREATE DATABASE hotel_management;
\c hotel_management;
SELECT * FROM pg_catalog.pg_tables;

---------------------------------------------------------------------------

CREATE SCHEMA views_schema;
CREATE SCHEMA procedures_schema;

---zrobic po utworzeniu danych tabel-----------------------------------

CREATE USER order_user WITH PASSWORD 'securepassword123';
GRANT INSERT ON public.reservations TO order_user;
GRANT UPDATE ON public.rooms TO order_user;
GRANT SELECT ON views_schema.available_rooms TO order_user;


CREATE USER stats_user WITH PASSWORD 'securepassword123';
GRANT SELECT ON views_schema.room_type_statistics TO stats_user;
GRANT SELECT ON views_schema.available_rooms TO stats_user;
GRANT SELECT ON views_schema.reservation_details TO stats_user;

---------------------------------------------------------------------------

CREATE TABLE guests (
    guest_id SERIAL PRIMARY KEY, 
    first_name TEXT NOT NULL, 
    last_name TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL, 
    phone_number VARCHAR(15), 
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP 
);

---------------------------------------------------------------------------

CREATE TABLE public.rooms (
    room_id SERIAL PRIMARY KEY,
    room_number INT UNIQUE NOT NULL, 
    room_type VARCHAR(20) NOT NULL CHECK (room_type IN ('Single', 'Double', 'Suite')), 
    price_per_night DECIMAL(10, 2) NOT NULL,
    is_available BOOLEAN DEFAULT TRUE
);

---------------------------------------------------------------------------

CREATE TABLE public.reservations (
    reservation_id SERIAL PRIMARY KEY,            
    guest_id INT NOT NULL REFERENCES public.guests(guest_id) ON DELETE CASCADE,
    room_id INT NOT NULL REFERENCES public.rooms(room_id) ON DELETE CASCADE, 
    check_in_date DATE NOT NULL,                  
    check_out_date DATE NOT NULL,                 
    total_cost NUMERIC(10, 2),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, 
    CONSTRAINT check_dates CHECK (check_out_date > check_in_date)
);

---------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION calculate_total_cost()
RETURNS TRIGGER AS $$
BEGIN
    SELECT (NEW.check_out_date - NEW.check_in_date) * price_per_night
    INTO NEW.total_cost
    FROM public.rooms
    WHERE rooms.room_id = NEW.room_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

---------------------------------------------------------------------------

CREATE TRIGGER trigger_calculate_total_cost
BEFORE INSERT OR UPDATE ON public.reservations
FOR EACH ROW
EXECUTE FUNCTION calculate_total_cost();

---------------------------------------------------------------------------

CREATE VIEW views_schema.available_rooms AS SELECT
    room_id,
    room_number,
    room_type,
    price_per_night
FROM public.rooms
WHERE is_available = TRUE;

---------------------------------------------------------------------------

CREATE VIEW views_schema.reservation_details AS
SELECT
    r.reservation_id,
    g.first_name || ' ' || g.last_name AS guest_name,
    rm.room_number,
    r.check_in_date,
    r.check_out_date,
    r.total_cost
FROM public.reservations r
JOIN public.guests g ON r.guest_id = g.guest_id
JOIN public.rooms rm ON r.room_id = rm.room_id;

---------------------------------------------------------------------------

CREATE MATERIALIZED VIEW views_schema.room_type_statistics AS
SELECT
    room_type,
    AVG(price_per_night) AS avg_price_per_night
FROM public.rooms
GROUP BY room_type;

---------------------------------------------------------------------------

CREATE FUNCTION procedures_schema.calculate_reservation_cost(
    room_id INT,
    check_in DATE,
    check_out DATE
) RETURNS NUMERIC AS $$
DECLARE
    price_per_night NUMERIC;
BEGIN
    SELECT price_per_night INTO price_per_night
    FROM public.rooms
    WHERE room_id = $1;    RETURN (check_out - check_in) * price_per_night;
END;    
$$ LANGUAGE plpgsql;

---------------------------------------------------------------------------

CREATE PROCEDURE procedures_schema.create_reservation(
    guest_id INT,
    room_id INT,
    check_in DATE,
    check_out DATE
)
LANGUAGE plpgsql
AS $$
BEGIN
    IF NOT EXISTS (
        SELECT 1 FROM public.rooms WHERE room_id = $2 AND is_available = TRUE
    ) THEN
        RAISE EXCEPTION 'Room is not available';
    END IF;
    INSERT INTO public.reservations (guest_id, room_id, check_in_date, check_out_date, total_cost)
    VALUES ($1, $2, $3, $4, procedures_schema.calculate_reservation_cost($2, $3, $4));
    UPDATE public.rooms SET is_available = FALSE WHERE room_id = $2;
END;
$$;

---------------------------------------------------------------------------

CREATE INDEX idx_guest_email ON public.guests(email);
CREATE INDEX idx_room_type ON public.rooms(room_type);
CREATE INDEX idx_reservation_dates ON public.reservations(check_in_date, check_out_date);
CREATE FUNCTION procedures_schema.update_room_availability()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE public.rooms
    SET is_available = TRUE
    WHERE room_id = OLD.room_id;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

---------------------------------------------------------------------------

CREATE TRIGGER after_reservation_delete
AFTER DELETE ON public.reservations
FOR EACH ROW
EXECUTE FUNCTION procedures_schema.update_room_availability();

---------------------------------------------------------------------------

INSERT INTO public.guests (first_name, last_name, email, phone_number)
VALUES
('Jan', 'Kowalski', 'kowalski@gmail.com', '123456789'),
('Piotr', 'Nowak', 'nowak@gmail.com', '987654321');
('asd', 'asdasda', 'nieistniejacy@gmail.com', '1233536'),
('dddd', 'asdasdasd', 'nowy@gmail.com', '92434234221');
('Jasssn', 'Kowalsssski', 'starry@gmail.com', '188888889'),
('Piotr', 'Nowak', 'asdaddddd@gmail.com', '7777777777');
('Jan', 'Kowalski', 'aaaaaaa@gmail.com', '546456456'),
('Piotr', 'Nowak', 'nowssssssssk@gmail.com', '9342341');
INSERT INTO public.rooms (room_number, room_type, price_per_night, is_available)
VALUES
(101, 'Single', 100.00, TRUE),
(102, 'Double', 150.00, TRUE),
(103, 'Suite', 300.00, TRUE);
CALL procedures_schema.create_reservation(1, 101, '2025-01-25', '2025-01-30');