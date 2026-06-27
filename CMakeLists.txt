cmake_minimum_required(VERSION 3.20)

project(cppgradeup2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard used by tasks")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

define_property(GLOBAL PROPERTY GRADEUP_INCLUDED_TASKS
    BRIEF_DOCS "Task directories included by the root CMake project"
    FULL_DOCS "Task directories included by the root CMake project")

set(GRADEUP_STUDENT_DIR "almar" CACHE STRING "Top-level student directory")
set(GRADEUP_TASKS "" CACHE STRING "Comma- or semicolon-separated task directories to configure, relative to the repo root")
option(GRADEUP_FAIL_ON_EMPTY "Fail configuration when no task CMakeLists.txt files are found" OFF)

set(_gradeup_explicit_tasks OFF)

if(GRADEUP_TASKS)
    set(_gradeup_explicit_tasks ON)
    string(REPLACE "," ";" _gradeup_task_candidates "${GRADEUP_TASKS}")
else()
    file(GLOB _gradeup_task_candidates
        LIST_DIRECTORIES true
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/${GRADEUP_STUDENT_DIR}/task*")
endif()

set(_gradeup_included_tasks "")

foreach(_task IN LISTS _gradeup_task_candidates)
    if(IS_ABSOLUTE "${_task}")
        set(_task_abs "${_task}")
    else()
        set(_task_abs "${CMAKE_CURRENT_SOURCE_DIR}/${_task}")
    endif()

    file(REAL_PATH "${_task_abs}" _task_real BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" EXPAND_TILDE)
    file(RELATIVE_PATH _task_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_task_real}")

    if(NOT IS_DIRECTORY "${_task_real}")
        if(_gradeup_explicit_tasks)
            message(FATAL_ERROR "Task directory does not exist: ${_task_rel}")
        endif()
        continue()
    endif()

    if(NOT _task_rel MATCHES "^${GRADEUP_STUDENT_DIR}/task[^/]+$")
        message(FATAL_ERROR "Invalid task path '${_task_rel}'. Expected '${GRADEUP_STUDENT_DIR}/task*'.")
    endif()

    if(NOT EXISTS "${_task_real}/CMakeLists.txt")
        if(_gradeup_explicit_tasks)
            message(FATAL_ERROR "Task has no CMakeLists.txt: ${_task_rel}")
        endif()
        message(STATUS "Skipping ${_task_rel}: CMakeLists.txt not found")
        continue()
    endif()

    string(REPLACE "/" "_" _task_build_dir "${_task_rel}")
    add_subdirectory("${_task_real}" "${CMAKE_CURRENT_BINARY_DIR}/${_task_build_dir}")
    list(APPEND _gradeup_included_tasks "${_task_rel}")
endforeach()

set_property(GLOBAL PROPERTY GRADEUP_INCLUDED_TASKS "${_gradeup_included_tasks}")

if(NOT _gradeup_included_tasks)
    if(GRADEUP_FAIL_ON_EMPTY)
        message(FATAL_ERROR "No task CMakeLists.txt files were found.")
    endif()
    message(STATUS "No task CMakeLists.txt files were found.")
else()
    list(JOIN _gradeup_included_tasks ", " _gradeup_included_tasks_text)
    message(STATUS "Included tasks: ${_gradeup_included_tasks_text}")
endif()
