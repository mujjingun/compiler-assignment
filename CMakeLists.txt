cmake_minimum_required(VERSION 2.8)

project(compiler1 LANGUAGES C)

set(LEX_HEADER "${CMAKE_BINARY_DIR}/lex.yy.h")
set(LEX_SOURCE "${CMAKE_BINARY_DIR}/lex.yy.c")
set(LEX_OUTPUTS ${LEX_HEADER} ${LEX_SOURCE})
set(LEX_COMMAND "flex")

add_custom_command(OUTPUT ${LEX_OUTPUTS}
    COMMAND ${LEX_COMMAND} "${CMAKE_SOURCE_DIR}/tiny.l"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS "tiny.l"
    VERBATIM)

add_custom_target(lex DEPENDS ${LEX_OUTPUTS})

add_executable(${PROJECT_NAME}
    "main.c"
    "utils.c"
    ${LEX_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
