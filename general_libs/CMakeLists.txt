add_definitions(${KLESS_DEFINES})

set(SOURCES
    src/Klessydra_ctx_switch.c
    src/Klessydra_En_Int.c
    src/Klessydra_get_coreID.c
    src/Klessydra_get_backup_coreID.c
    src/Klessydra_get_mhartid.c
    src/klessydra_lock_acquire.c
    src/klessydra_lock_release.c
    src/klessydra_lock_set.c
    src/Klessydra_WFI.c
    src/load_mem.c
	src/performance_counters.c
    src/send_multi_sw_irq.c
    src/send_sw_irq.c
    src/sync_barrier.c
    )

set(HEADERS
    inc/functions.h
    inc/klessydra_defs.h
    inc/riscv_test.h
    inc/test_macros.h
    inc/encoding.h
    )

include_directories(inc/)

add_library(kless_libs STATIC ${SOURCES} ${HEADERS})

