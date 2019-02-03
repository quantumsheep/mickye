CREATE TABLE log (
	id integer PRIMARY KEY AUTOINCREMENT,
	message text,
	date text
);

CREATE TABLE client (
	id integer PRIMARY KEY AUTOINCREMENT,
	ipv4 varchar,
	ipv6 varchar
);
