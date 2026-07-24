#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "❌ Usage:"
  echo "   ./generate_scaffold.sh <name>"
  echo "   ./generate_scaffold.sh <folder> <name>"
  echo ""
  echo "Examples:"
  echo "   ./generate_scaffold.sh linked_list"
  echo "   ./generate_scaffold.sh greedy assign_mice_to_holes"
}

if [ "$#" -ne 1 ] && [ "$#" -ne 2 ]; then
  usage
  exit 1
fi

# Parse args
if [ "$#" -eq 1 ]; then
  FOLDER=""
  NAME="$1"
else
  FOLDER="$1"
  NAME="$2"
fi

# Validate simple naming (optional but helpful)
[[ "$NAME" =~ ^[A-Za-z0-9_]+$ ]] || { echo "❌ Invalid task name: $NAME"; exit 1; }
if [ -n "$FOLDER" ]; then
  [[ "$FOLDER" =~ ^[A-Za-z0-9_]+$ ]] || { echo "❌ Invalid folder name: $FOLDER"; exit 1; }
fi

# Base directories must exist
[[ -d "src" ]] || { echo "❌ Missing folder: src"; exit 1; }
[[ -d "header" ]] || { echo "❌ Missing folder: header"; exit 1; }
[[ -d "unit_tests" ]] || { echo "❌ Missing folder: unit_tests"; exit 1; }

# If folder mode, category folders must already exist (DON'T create them)
if [ -n "$FOLDER" ]; then
  [[ -d "src/${FOLDER}" ]] || { echo "❌ Missing folder: src/${FOLDER}"; exit 1; }
  [[ -d "header/${FOLDER}" ]] || { echo "❌ Missing folder: header/${FOLDER}"; exit 1; }
  [[ -d "unit_tests/${FOLDER}" ]] || { echo "❌ Missing folder: unit_tests/${FOLDER}"; exit 1; }
fi

# Build paths depending on mode
if [ -n "$FOLDER" ]; then
  CPP_FILE="src/${FOLDER}/${NAME}.cpp"
  HEADER_FILE="header/${FOLDER}/${NAME}.hpp"
  TEST_FILE="unit_tests/${FOLDER}/test_${NAME}.cpp"
  INCLUDE_PATH="${FOLDER}/${NAME}.hpp"
else
  CPP_FILE="src/${NAME}.cpp"
  HEADER_FILE="header/${NAME}.hpp"
  TEST_FILE="unit_tests/test_${NAME}.cpp"
  INCLUDE_PATH="${NAME}.hpp"
fi

create_if_missing() {
  local path="$1"
  local content="$2"
  if [[ -e "$path" ]]; then
    echo "⚠️  SKIP (exists): $path"
  else
    printf "%s" "$content" > "$path"
    echo "✅ CREATED: $path"
  fi
}

create_if_missing "$CPP_FILE" \
$'#include <string>\n#include <vector>\n\n'

create_if_missing "$HEADER_FILE" \
$'#pragma once\n\n#include <string>\n#include <vector>\n\n'

create_if_missing "$TEST_FILE" \
$'#include <gtest/gtest.h>\n#include "graph.hpp"\n\n'
