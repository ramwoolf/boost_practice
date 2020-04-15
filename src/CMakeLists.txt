set(subprojects dummy dummy2)

foreach(subpr IN ITEMS ${subprojects})
    if(${WANTED} STREQUAL "ALL" OR  ${subpr} STREQUAL ${WANTED})
        add_subdirectory(${subpr})
    endif()    
endforeach()

