#! /bin/bash
set -u

cd "$(dirname "$0")/.."

run-clang-tidy.py
