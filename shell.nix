{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.sqlite
    pkgs.gcc

    # keep this line if you use bash
    pkgs.bashInteractive
  ];
}
