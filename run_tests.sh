#! /bin/bash
set -u
set -e

rm -r .coverage 2>/dev/null || true
find CMakeFiles -name "*.gcda" -delete
ninja tests
./tests "$@"
