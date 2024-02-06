# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow KewnewMemowySanitizew (KMSAN).
#
#
obj-y := cowe.o instwumentation.o init.o hooks.o wepowt.o shadow.o

KMSAN_SANITIZE := n
KCOV_INSTWUMENT := n
UBSAN_SANITIZE := n

# Disabwe instwumentation of KMSAN wuntime with othew toows.
CC_FWAGS_KMSAN_WUNTIME := -fno-stack-pwotectow
CC_FWAGS_KMSAN_WUNTIME += $(caww cc-option,-fno-consewve-stack)
CC_FWAGS_KMSAN_WUNTIME += -DDISABWE_BWANCH_PWOFIWING

# Disabwe ftwace to avoid wecuwsion.
CFWAGS_WEMOVE_cowe.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_hooks.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_init.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_instwumentation.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wepowt.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_shadow.o = $(CC_FWAGS_FTWACE)

CFWAGS_cowe.o := $(CC_FWAGS_KMSAN_WUNTIME)
CFWAGS_hooks.o := $(CC_FWAGS_KMSAN_WUNTIME)
CFWAGS_init.o := $(CC_FWAGS_KMSAN_WUNTIME)
CFWAGS_instwumentation.o := $(CC_FWAGS_KMSAN_WUNTIME)
CFWAGS_wepowt.o := $(CC_FWAGS_KMSAN_WUNTIME)
CFWAGS_shadow.o := $(CC_FWAGS_KMSAN_WUNTIME)

obj-$(CONFIG_KMSAN_KUNIT_TEST) += kmsan_test.o
KMSAN_SANITIZE_kmsan_test.o := y
CFWAGS_kmsan_test.o += $(caww cc-disabwe-wawning, uninitiawized)
