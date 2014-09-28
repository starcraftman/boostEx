#!/usr/bin/env bash
# Run this to build project with cmake
# Alternative to my normal makefiles
ROOT=$(readlink -f $(dirname $0))
BDIR=$ROOT/gen

usage() {
  echo "Builds the project. Takes optional args:
  clean: Remove build dir.
  run  : Execute main program.
  test : Run tests."
}

build() {
  if [ "$(uname -s)" == "Linux" -a ! -d ./libs ]; then
    ./GetLibs.py gtest boost SDL
  fi

  pushd "$BDIR"
  if [ ! -f "$BDIR/CMakeCache.txt" ]; then
    cmake $@ ..
  fi
  make
  popd
}

for arg; do
  case "$arg" in
    "--help"|"-h"|"help")
      usage
      exit
      ;;
    "clean")
      rm -rf "$BDIR" "python/libBoost.so"
      mkdir -p "$BDIR"
      touch "$BDIR/DUMMY"
      ;;
    "test")
      build "-DTest=ON"
      $BDIR/BoostTest
      ;;
    "progOpts")
      build "-DProgOpts=ON"
      echo "Run programs separately, see --help."
      echo "The programs available are: "
      echo ./gen/ProgOpts*
      ;;
    "python")
      build "-DPython=ON"
      echo "Executing Python code."
      ./python/simple.py
      ;;
    *) # Default is to run
      echo "Invalid command, see the help."
      ;;
  esac
done
