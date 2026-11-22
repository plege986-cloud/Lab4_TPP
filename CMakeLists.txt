
cmake_minimum_required(VERSION 3.20)

project(Lab4_TPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

if(NOT BUILD_SHARED_LIBS)
    add_compile_definitions(INTEGRATION_STATIC DIFFERENTIATION_STATIC)
endif()

add_library(IntegrationLib
    student_a/integration.cpp
)

add_library(DifferentiationLib
    student_b/differentiation.cpp
)

target_include_directories(IntegrationLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/student_a
)

target_include_directories(DifferentiationLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/student_b
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(IntegrationLib PRIVATE
        INTEGRATION_EXPORTS
    )

    target_compile_definitions(DifferentiationLib PRIVATE
        DIFFERENTIATION_EXPORTS
    )
endif()

add_executable(IntegrationTest
    app/main.cpp
)

target_link_libraries(IntegrationTest PRIVATE
    IntegrationLib
    DifferentiationLib
)

if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET IntegrationTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:IntegrationLib>
            $<TARGET_FILE_DIR:IntegrationTest>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:DifferentiationLib>
            $<TARGET_FILE_DIR:IntegrationTest>
    )

    add_executable(ExplicitTest
        app/explicit.cpp
    )

    add_custom_command(TARGET ExplicitTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:IntegrationLib>
            $<TARGET_FILE_DIR:ExplicitTest>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:DifferentiationLib>
            $<TARGET_FILE_DIR:ExplicitTest>
    )
endif()
