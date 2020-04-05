set(SUBPROJECT_NAME dummy)
message(STATUS "Build ${SUBPROJECT_NAME}")

set(SRCS main.cpp)

message(STATUS "> BUILD SOURCES: ${SRCS}")

add_executable(${SUBPROJECT_NAME} ${SRCS})
target_link_libraries(${SUBPROJECT_NAME})

install(TARGETS ${SUBPROJECT_NAME} DESTINATION ${INSTALL_NAME_DIR}/${SUBPROJECT_NAME})