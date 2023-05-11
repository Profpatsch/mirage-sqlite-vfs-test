-- Initialize sqlite3 and load our onepage VFS, then open a database file with that VFS
.load ./onefile_ext
.open "file:mydb.sqlite?vfs=onefile"

CREATE TABLE IF NOT EXISTS llama (line);
INSERT INTO llama (line) VALUES
  ('heres a llama'),
  ('theres a llama'),
  ('and another little llama'),
  ('fuzzy llama'),
  ('funny llama'),
  ('llama llama'),
  ('duck');

.dump
