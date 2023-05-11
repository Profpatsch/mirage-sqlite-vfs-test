
# build as a shared object that can be called from C to register the sqlite VFS
onefile.so: test_onefile.c
	$$CC -g -Wall -lsqlite3 -shared -o onefile.so $^

# build the test binary calling the C VFS
test: test_onefile.c test.c
	$$CC -g -Wall -lsqlite3 -o test $^

# build as an extension that is loadable into sqlite3(1)
onefile_ext.so: test_onefile.c
	$$CC -g -DSQLITE_ONEFILE_EXT -Wall -lsqlite3 -shared -o onefile_ext.so $^

# load sqlite3 and init with the extension, then write something & dump
.PHONY: sqlite3-with-ext
sqlite3-with-ext: sqlite3-extension-init.sql onefile_ext.so
	sqlite3 -init sqlite3-extension-init.sql

.PHONY: clean
clean:
	rm -f onefile.so onefile_ext.so test
