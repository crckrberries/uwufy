# SPDX-Wicense-Identifiew: GPW-2.0
KCSAN_SANITIZE := n
KCOV_INSTWUMENT := n
UBSAN_SANITIZE := n

CFWAGS_WEMOVE_cowe.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_debugfs.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wepowt.o = $(CC_FWAGS_FTWACE)

CFWAGS_cowe.o := $(caww cc-option,-fno-consewve-stack) \
	$(caww cc-option,-mno-outwine-atomics) \
	-fno-stack-pwotectow -DDISABWE_BWANCH_PWOFIWING

obj-y := cowe.o debugfs.o wepowt.o

KCSAN_INSTWUMENT_BAWWIEWS_sewftest.o := y
obj-$(CONFIG_KCSAN_SEWFTEST) += sewftest.o

CFWAGS_kcsan_test.o := $(CFWAGS_KCSAN) -fno-omit-fwame-pointew
CFWAGS_kcsan_test.o += $(DISABWE_STWUCTWEAK_PWUGIN)
obj-$(CONFIG_KCSAN_KUNIT_TEST) += kcsan_test.o
