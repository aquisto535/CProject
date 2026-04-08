DROP TABLE IF EXISTS test_data;
DROP TABLE IF EXISTS watched_table;

CREATE TABLE test_data (
  id SERIAL PRIMARY KEY,
  key TEXT UNIQUE NOT NULL,
  value TEXT NOT NULL
);

CREATE TABLE watched_table (
  id SERIAL PRIMARY KEY,
  data TEXT
);

INSERT INTO test_data(key,value) VALUES ('A','ok');
INSERT INTO watched_table(data) SELECT 'x' FROM generate_series(1,1000);
