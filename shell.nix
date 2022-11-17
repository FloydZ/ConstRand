with import <nixpkgs> {};
{ pkgs ? import <nixpkgs> {} }:

stdenv.mkDerivation {
  name = "const_rand";
  src = ./.;

  buildInputs = [ gnumake cmake clang gcc ];
}
