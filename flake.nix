{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    devkitNix.url = "github:bandithedoge/devkitNix";
    bannertool = {
      url = "github:Epicpkmn11/bannertool";
      flake = false;
    };
    bannertoolBuildtools = {
      url = "github:Steveice10/buildtools";
      flake = false;
    };
    projectCTR = {
      url = "github:3DSGuy/Project_CTR";
      flake = false;
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    devkitNix,
    bannertool,
    bannertoolBuildtools,
    projectCTR,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [devkitNix.overlays.default];
        };

        bannertoolPackage = pkgs.stdenv.mkDerivation {
          pname = "bannertool";
          version = "1.2.2";
          src = bannertool;

          nativeBuildInputs = [pkgs.zip];

          postPatch = ''
            rm -rf buildtools
            cp -r ${bannertoolBuildtools} buildtools
            substituteInPlace Makefile \
              --replace-fail 'VERSION_PARTS := $(subst ., ,$(shell git describe --tags --abbrev=0))' \
                             'VERSION_PARTS := 1 2 2'
          '';

          installPhase = ''
            runHook preInstall
            mkdir -p $out/bin
            install -m755 output/*/bannertool $out/bin/bannertool
            runHook postInstall
          '';
        };

        makeromPackage = pkgs.stdenv.mkDerivation {
          pname = "makerom";
          version = "unstable-2026-01-18";
          src = projectCTR;

          buildPhase = ''
            runHook preBuild
            make -C makerom deps
            make -C makerom -j$NIX_BUILD_CORES program
            runHook postBuild
          '';

          installPhase = ''
            runHook preInstall
            install -Dm755 makerom/bin/makerom $out/bin/makerom
            runHook postInstall
          '';
        };

        projectStdenv = pkgs.stdenvAdapters.addAttrsToDerivation {
          nativeBuildInputs = [
            pkgs.devkitNix.devkitARM
            bannertoolPackage
            makeromPackage
          ];
        } pkgs.devkitNix.stdenvARM;
      in {
        devShells.default = pkgs.mkShell.override {stdenv = projectStdenv;} {};

        packages.bannertool = bannertoolPackage;
        packages.makerom = makeromPackage;
        packages.default = projectStdenv.mkDerivation {
          name = "mc-poggers-3ds";
          src = ./.;

          makeFlags = ["TARGET=mc-poggers-3ds"];
          installPhase = ''
            mkdir $out
            cp mc-poggers-3ds.3dsx mc-poggers-3ds.cia $out
          '';
        };
      }
    );
}
