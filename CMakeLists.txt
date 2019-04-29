cmake_minimum_required(VERSION 2.8)

project(compiler1 LANGUAGES C)

set(LEX_HEADER "${CMAKE_BINARY_DIR}/lex.yy.h")
set(LEX_SOURCE "${CMAKE_BINARY_DIR}/lex.yy.c")
set(LEX_OUTPUTS ${LEX_HEADER} ${LEX_SOURCE})
set(LEX_COMMAND "flex")

add_custom_command(OUTPUT ${LEX_OUTPUTS}
    COMMAND ${LEX_COMMAND} "${CMAKE_SOURCE_DIR}/lex.l"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS "lex.l"
    VERBATIM)

add_custom_target(lex DEPENDS ${LEX_OUTPUTS})

set(BISON_HEADER "${CMAKE_BINARY_DIR}/parser.tab.h")
set(BISON_SOURCE "${CMAKE_BINARY_DIR}/parser.tab.c")
set(BISON_OUTPUTS ${BISON_HEADER} ${BISON_SOURCE})
set(BISON_COMMAND "bison")

add_custom_command(OUTPUT ${BISON_OUTPUTS}
    COMMAND ${BISON_COMMAND} "${CMAKE_SOURCE_DIR}/parser.y"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS "parser.y"
    VERBATIM)

add_custom_target(bison DEPENDS ${BISON_OUTPUTS})

add_executable(${PROJECT_NAME}
    "main.c"
    "scan.c"
    "utils.c"
    ${LEX_SOURCE}
    ${BISON_SOURCE}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
add_dependencies(${PROJECT_NAME} lex bison)
