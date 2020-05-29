#!/bin/bash
set -u

cd "$(dirname "$0")/.."

if [ "${1:-}" == "--fix" ]; then
  echo "Fixing files in place"
  find src -type f -exec echo "Fixing {}" \; -exec clang-format -i {} \;
else
  echo "Showing diffs"
  find src -type f -exec ./scripts/show_clang_diff.sh {} \;
fi
