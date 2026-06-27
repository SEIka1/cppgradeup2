#!/usr/bin/env bash
set -euo pipefail

base_sha="${1:-}"
head_sha="${2:-HEAD}"
zero_sha="0000000000000000000000000000000000000000"

if [[ -n "$base_sha" && "$base_sha" != "$zero_sha" ]] && git cat-file -e "$base_sha^{commit}" 2>/dev/null; then
  git diff --name-only "$base_sha" "$head_sha"
else
  git diff-tree --root --no-commit-id --name-only -r "$head_sha"
fi | awk -F/ '$1 == "almar" && $2 ~ /^task[^/]+$/ { print $1 "/" $2 }' | sort -u
