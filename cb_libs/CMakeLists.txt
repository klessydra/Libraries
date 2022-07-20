set(SOURCES
    src/Disjoint_LinUCB.cpp
    src/Hybrid_LinUCB.cpp
    src/values.cpp
    )

set(HEADERS
    inc/Disjoint_LinUCB.hpp
    inc/Hybrid_LinUCB.hpp
    inc/matrix.hpp
    inc/params.hpp
    inc/params_hybrid.hpp
    inc/offline_script.hpp
    inc/info.hpp
    )

include_directories(inc/)

add_library(cb_libs STATIC ${SOURCES} ${HEADERS})

