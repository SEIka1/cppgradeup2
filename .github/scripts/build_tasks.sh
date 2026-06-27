#!/usr/bin/env bash
set -euo pipefail

if [[ $# -eq 0 ]]; then
  mapfile -t raw_tasks < <(find almar -mindepth 1 -maxdepth 1 -type d -name 'task*' 2>/dev/null | sort)
else
  raw_tasks=("$@")
fi

tasks=()
for task in "${raw_tasks[@]}"; do
  task="${task#"${task%%[![:space:]]*}"}"
  task="${task%"${task##*[![:space:]]}"}"
  [[ -n "$task" ]] && tasks+=("$task")
done

if [[ ${#tasks[@]} -eq 0 ]]; then
  echo "No task directories found."
  exit 1
fi

for task in "${tasks[@]}"; do
  if [[ ! "$task" =~ ^almar/task[^/]+$ ]]; then
    echo "Invalid task path: $task"
    echo "Expected: almar/task*"
    exit 1
  fi
  if [[ ! -d "$task" ]]; then
    echo "Task directory does not exist: $task"
    exit 1
  fi
  if [[ ! -f "$task/CMakeLists.txt" ]]; then
    echo "Task has no CMakeLists.txt: $task"
    exit 1
  fi
done

for task in "${tasks[@]}"; do
  build_dir="build/${task//\//_}"

  echo "Building $task"
  cmake -S . -B "$build_dir" -G Ninja \
    -DGRADEUP_TASKS="$task" \
    -DGRADEUP_FAIL_ON_EMPTY=ON
  cmake --build "$build_dir"

  if [[ -d "$task/test" ]]; then
    echo "Testing $task"
    ctest --test-dir "$build_dir" --output-on-failure
  else
    echo "No test/ directory found for $task; skipping ctest."
  fi
done
