# cppgradeup2

Repository for C++ training tasks.

## Task Layout

Tasks live under `almar/task*`, for example:

```text
almar/taskm4/
  CMakeLists.txt
  include/
  lib/
  test/
```

The root `CMakeLists.txt` only discovers task directories and delegates each task to its own `almar/task*/CMakeLists.txt`.

## Local Build

Build all tasks:

```bash
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

Build selected tasks only:

```bash
cmake -S . -B build -G Ninja -DGRADEUP_TASKS=almar/taske1,almar/taskm4
cmake --build build
ctest --test-dir build --output-on-failure
```

Use the same per-task build flow as CI:

```bash
.github/scripts/build_tasks.sh almar/taske1 almar/taskm4
```

CI runs `ctest` only when the selected task contains a `test/` directory.
