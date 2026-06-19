cmake_minimum_required(VERSION 3.27)
project(minilog)

set (CMAKE_CXX_STANDARD 23)

add_subdirectory(src)


if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message (STATUS "minilog: Running standalone, enabling test targets")

    set(OUTPUT ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT})


    if (NOT WIN32)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wextra -fsanitize=undefined")
    endif()

    add_subdirectory(tests)
    add_subdirectory(demos)
    add_custom_target(test
        COMMAND tests
        DEPENDS tests
        COMMENT "Compile and run tests")

    if (MINILOG_LINT)
        find_program(
            CLANGTIDY
            NAMES "clang-tidy" "clang-tidy.exe"
            REQUIRED
            )

        set (CLANG_TIDY_COMMAND "${CLANGTIDY}" "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
        if (STC_LINT_WARNINGS_ARE_ERRORS)
            list (APPEND CLANG_TIDY_COMMAND  -warnings-as-errors=*)
        endif()

        if (WIN32)
            list (APPEND CLANG_TIDY_COMMAND --extra-arg=/EHsc)
        endif()

        message(STATUS "Using CLANG_TIDY_COMMAND=${CLANG_TIDY_COMMAND}")
        set_target_properties(stc PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
    endif()

endif()
