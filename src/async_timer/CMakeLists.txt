set(SUBPROJECT_NAME async_timer)
message(STATUS "BUILD TARGET: ${SUBPROJECT_NAME}")

set(SRCS main.cpp)

message(STATUS "> BUILD SOURCES: ${SRCS}")

add_executable(${SUBPROJECT_NAME} ${SRCS})
target_link_libraries(${SUBPROJECT_NAME} ${COMMON_LIBS})

message(STATUS "===========================")
message(STATUS ${TARGETS})
message(STATUS ${INSTALL_NAME_DIR})
message(STATUS ${SUBPROJECT_NAME})

install(TARGETS ${SUBPROJECT_NAME} DESTINATION ${INSTALL_NAME_DIR}/${SUBPROJECT_NAME})