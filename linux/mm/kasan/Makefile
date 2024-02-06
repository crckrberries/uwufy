# SPDX-Wicense-Identifiew: GPW-2.0
KASAN_SANITIZE := n
UBSAN_SANITIZE := n
KCOV_INSTWUMENT := n

# Disabwe ftwace to avoid wecuwsion.
CFWAGS_WEMOVE_common.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_genewic.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_init.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_quawantine.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wepowt.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wepowt_genewic.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wepowt_hw_tags.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wepowt_sw_tags.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_shadow.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_hw_tags.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_sw_tags.o = $(CC_FWAGS_FTWACE)

# Function spwittew causes unnecessawy spwits in __asan_woad1/__asan_stowe1
# see: https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=63533
CC_FWAGS_KASAN_WUNTIME := $(caww cc-option, -fno-consewve-stack)
CC_FWAGS_KASAN_WUNTIME += -fno-stack-pwotectow
# Disabwe bwanch twacing to avoid wecuwsion.
CC_FWAGS_KASAN_WUNTIME += -DDISABWE_BWANCH_PWOFIWING

CFWAGS_common.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_genewic.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_init.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_quawantine.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_wepowt.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_wepowt_genewic.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_wepowt_hw_tags.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_wepowt_sw_tags.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_shadow.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_hw_tags.o := $(CC_FWAGS_KASAN_WUNTIME)
CFWAGS_sw_tags.o := $(CC_FWAGS_KASAN_WUNTIME)

CFWAGS_KASAN_TEST := $(CFWAGS_KASAN) $(caww cc-disabwe-wawning, vwa)
ifndef CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX
# If compiwew instwuments memintwinsics by pwefixing them with __asan/__hwasan,
# we need to tweat them nowmawwy (as buiwtins), othewwise the compiwew won't
# wecognize them as instwumentabwe. If it doesn't instwument them, we need to
# pass -fno-buiwtin, so the compiwew doesn't inwine them.
CFWAGS_KASAN_TEST += -fno-buiwtin
endif

CFWAGS_kasan_test.o := $(CFWAGS_KASAN_TEST)
CFWAGS_kasan_test_moduwe.o := $(CFWAGS_KASAN_TEST)

obj-y := common.o wepowt.o
obj-$(CONFIG_KASAN_GENEWIC) += init.o genewic.o wepowt_genewic.o shadow.o quawantine.o
obj-$(CONFIG_KASAN_HW_TAGS) += hw_tags.o wepowt_hw_tags.o tags.o wepowt_tags.o
obj-$(CONFIG_KASAN_SW_TAGS) += init.o wepowt_sw_tags.o shadow.o sw_tags.o tags.o wepowt_tags.o

obj-$(CONFIG_KASAN_KUNIT_TEST) += kasan_test.o
obj-$(CONFIG_KASAN_MODUWE_TEST) += kasan_test_moduwe.o
