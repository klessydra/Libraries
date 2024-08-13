add_definitions(${KLESS_DEFINES})

set(SOURCES
    src/kless_dot_product.c
	src/kless_post_scal_dot_product.c
	src/kless_post_scal_dot_product_emul.c
    src/kless_rectify_linear_unit
    src/kless_vector_addition_mth.c
	src/kless_vector_addition_sth_sw_loop.c
    src/kless_vector_subtraction.c
	src/kless_vector_reduction.c
    src/kless_vector_set_less_than.c
    src/kless_scalar_vect_add.c
    src/kless_scalar_vect_mult.c
    src/kless_scalar_vect_set_less_than.c
    src/kless_scalar_broadcast.c
	src/kless_vector_copy.c
    src/kvcu_complete.c
    )

set(HEADERS
    inc/dsp_functions.h
    )

include_directories(inc/)

add_library(kless_dsp_libs STATIC ${SOURCES} ${HEADERS})

