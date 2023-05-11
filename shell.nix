{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.sqlite
    pkgs.gcc
    pkgs.rlwrap

    # keep this line if you use bash
    pkgs.bashInteractive
  ];
}
