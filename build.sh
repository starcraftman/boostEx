#!/usr/bin/env bash
# Run this to build project with cmake
# Alternative to my normal makefiles
ROOT=$(readlink -f $(dirname $0))
BDIR=$ROOT/gen

usage() {
  echo "USAGE: ./$(basename $0) OPT1 OPT2 ...
    clean    : Remove build dir.
    propOpts : Build program_options files.
    python   : Build boost::python lib.
    test     : Run tests.

  NB: Be sure to 'clean' before switching between projects.
  i.e. ./build.sh clean python"
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

if [ -z "$1" ]; then
  usage
  exit
fi

for arg; do
  case "$arg" in
    *help|-h)
      usage
      exit
      ;;
    clean)
      rm -rf "$BDIR" "python/libBoost.so"
      mkdir -p "$BDIR"
      touch "$BDIR/DUMMY"
      ;;
    std*)
      build -DStdNew=ON
      $BDIR/StdNew
      ;;
    test*)
      build -DTest=ON
      $BDIR/BoostTest
      ;;
    progOpts*)
      build -DProgOpts=ON
      echo "Run programs separately, see --help."
      echo "The programs available are: "
      echo ./gen/ProgOpts*
      ;;
    python*)
      build -DPython=ON -DStaticBoost=OFF
      echo "Executing Python code."
      ./python/run.py
      ;;
    *)
      echo "Invalid command, see the help."
      ;;
  esac
done
