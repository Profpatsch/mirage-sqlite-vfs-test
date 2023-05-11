This is an example of how we could make an sqlite VFS that requires no unix syscalls,
but rather is passed everything it needs from outside.

This way we can pass the environment from the Ocaml runtime / MirageOS backend and use sqlite as the base of permanent storage in mirageos.

The base for this is the [example test_onefile.c VFS](https://www.sqlite.org/src/doc/trunk/src/test_onefile.c) (public domain) from the sqlite docs.

The commit history of this repo should be enlightening to figure out what I tried out so far.

# Next steps

* Replace all stubbed out references to `pParent` with our own functionality (and remove `pParent`)
* Compile a static sqlite that only contains this VFS (with the `-DSQLITE_OS_OTHER=1` config option to sqlite.c, concatenating our VFS to `sqlite.c`; `sqlite3_os_init` and `sqlite3_os_end` have to be stubbed out somehow)
* Remove the journal from the block device, so that we just have a normal database file that we can open with `sqlite3` and the unix backend outside the unikernel (and figure out whether it’s okay to have the journal in memory)
* [Build an ocaml package](https://github.com/pkel/sqlite3-ocaml/commit/b9f97010364ced241cee1b79212a03d9f235e6fc) which exposes the necessary functions as C pointers, fills the `onefile_functions` struct and calls `sqlite3_onefile_from_c`. Get ocaml implementations for these from the `mirage-*` packages from opam (they abstract over the mirage backends like `hvt`, `unix` etc)
