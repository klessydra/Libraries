set(SOURCES
    src/Disjoint_LinUCB.cpp
    src/Hybrid_LinUCB.cpp
    #src/offline_script.cpp
    #src/offline_script_hybrid.cpp
    #src/offline_script_hybrid_opt.cpp
    src/values.cpp
    #src/EXP3_opt.cpp
    )

set(HEADERS
    inc/Disjoint_LinUCB.hpp
    inc/Hybrid_LinUCB.hpp
    inc/matrix.hpp
    inc/params.hpp
    inc/params_hybrid.hpp
    inc/offline_script.hpp
    #inc/offline_script_hybrid.hpp
    #inc/offline_script_hybrid_opt.hpp
    #inc/EXP3_opt.hpp
    inc/info.hpp
    )

include_directories(inc/)

add_library(cb_libs STATIC ${SOURCES} ${HEADERS})

