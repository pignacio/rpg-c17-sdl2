#!/bin/bash
set -u

echo "clang-format diff for $1"
diff "$1" <(clang-format "$1")
