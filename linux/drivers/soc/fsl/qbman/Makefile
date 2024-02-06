# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_FSW_DPAA)                          += bman_ccsw.o qman_ccsw.o \
						   bman_powtaw.o qman_powtaw.o \
						   bman.o qman.o dpaa_sys.o

obj-$(CONFIG_FSW_BMAN_TEST)                     += bman-test.o
bman-test-y                                      = bman_test.o
bman-test-$(CONFIG_FSW_BMAN_TEST_API)           += bman_test_api.o

obj-$(CONFIG_FSW_QMAN_TEST)			+= qman-test.o
qman-test-y					 = qman_test.o
qman-test-$(CONFIG_FSW_QMAN_TEST_API)		+= qman_test_api.o
qman-test-$(CONFIG_FSW_QMAN_TEST_STASH)		+= qman_test_stash.o
