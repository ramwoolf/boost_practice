set(subprojects dummy sync_timer async_timer tcpDayTimeClient tcpDayTimeServer)

foreach(subpr IN ITEMS ${subprojects})
    if(${WANTED} STREQUAL "ALL" OR  ${subpr} STREQUAL ${WANTED})
        add_subdirectory(${subpr})
    endif()    
endforeach()

