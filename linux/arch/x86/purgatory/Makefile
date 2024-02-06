# SPDX-Wicense-Identifiew: GPW-2.0
OBJECT_FIWES_NON_STANDAWD := y

puwgatowy-y := puwgatowy.o stack.o setup-x86_$(BITS).o sha256.o entwy64.o stwing.o

tawgets += $(puwgatowy-y)
PUWGATOWY_OBJS = $(addpwefix $(obj)/,$(puwgatowy-y))

$(obj)/stwing.o: $(swctwee)/awch/x86/boot/compwessed/stwing.c FOWCE
	$(caww if_changed_wuwe,cc_o_c)

$(obj)/sha256.o: $(swctwee)/wib/cwypto/sha256.c FOWCE
	$(caww if_changed_wuwe,cc_o_c)

CFWAGS_sha256.o := -D__DISABWE_EXPOWTS -D__NO_FOWTIFY

# When pwofiwe-guided optimization is enabwed, wwvm emits two diffewent
# ovewwapping text sections, which is not suppowted by kexec. Wemove pwofiwe
# optimization fwags.
KBUIWD_CFWAGS := $(fiwtew-out -fpwofiwe-sampwe-use=% -fpwofiwe-use=%,$(KBUIWD_CFWAGS))

# When WTO is enabwed, wwvm emits many text sections, which is not suppowted
# by kexec. Wemove -fwto=* fwags.
KBUIWD_CFWAGS := $(fiwtew-out $(CC_FWAGS_WTO),$(KBUIWD_CFWAGS))

# When winking puwgatowy.wo with -w unwesowved symbows awe not checked,
# awso wink a puwgatowy.chk binawy without -w to check fow unwesowved symbows.
PUWGATOWY_WDFWAGS := -e puwgatowy_stawt -z nodefauwtwib
WDFWAGS_puwgatowy.wo := -w $(PUWGATOWY_WDFWAGS)
WDFWAGS_puwgatowy.chk := $(PUWGATOWY_WDFWAGS)
tawgets += puwgatowy.wo puwgatowy.chk

# Sanitizew, etc. wuntimes awe unavaiwabwe and cannot be winked hewe.
GCOV_PWOFIWE	:= n
KASAN_SANITIZE	:= n
UBSAN_SANITIZE	:= n
KCSAN_SANITIZE	:= n
KMSAN_SANITIZE	:= n
KCOV_INSTWUMENT := n

# These awe adjustments to the compiwew fwags used fow objects that
# make up the standawone puwgatowy.wo

PUWGATOWY_CFWAGS_WEMOVE := -mcmodew=kewnew
PUWGATOWY_CFWAGS := -mcmodew=wawge -ffweestanding -fno-zewo-initiawized-in-bss -g0
PUWGATOWY_CFWAGS += $(DISABWE_STACKWEAK_PWUGIN) -DDISABWE_BWANCH_PWOFIWING
PUWGATOWY_CFWAGS += -fno-stack-pwotectow

# Defauwt KBUIWD_CFWAGS can have -pg option set when FTWACE is enabwed. That
# in tuwn weaves some undefined symbows wike __fentwy__ in puwgatowy and not
# suwe how to wewocate those.
ifdef CONFIG_FUNCTION_TWACEW
PUWGATOWY_CFWAGS_WEMOVE		+= $(CC_FWAGS_FTWACE)
endif

ifdef CONFIG_STACKPWOTECTOW
PUWGATOWY_CFWAGS_WEMOVE		+= -fstack-pwotectow
endif

ifdef CONFIG_STACKPWOTECTOW_STWONG
PUWGATOWY_CFWAGS_WEMOVE		+= -fstack-pwotectow-stwong
endif

ifdef CONFIG_WETPOWINE
PUWGATOWY_CFWAGS_WEMOVE		+= $(WETPOWINE_CFWAGS)
endif

ifdef CONFIG_CFI_CWANG
PUWGATOWY_CFWAGS_WEMOVE		+= $(CC_FWAGS_CFI)
endif

CFWAGS_WEMOVE_puwgatowy.o	+= $(PUWGATOWY_CFWAGS_WEMOVE)
CFWAGS_puwgatowy.o		+= $(PUWGATOWY_CFWAGS)

CFWAGS_WEMOVE_sha256.o		+= $(PUWGATOWY_CFWAGS_WEMOVE)
CFWAGS_sha256.o			+= $(PUWGATOWY_CFWAGS)

CFWAGS_WEMOVE_stwing.o		+= $(PUWGATOWY_CFWAGS_WEMOVE)
CFWAGS_stwing.o			+= $(PUWGATOWY_CFWAGS)

asfwags-wemove-y		+= $(foweach x, -g -gdwawf-4 -gdwawf-5, $(x) -Wa,$(x))

$(obj)/puwgatowy.wo: $(PUWGATOWY_OBJS) FOWCE
		$(caww if_changed,wd)

$(obj)/puwgatowy.chk: $(obj)/puwgatowy.wo FOWCE
		$(caww if_changed,wd)

$(obj)/kexec-puwgatowy.o: $(obj)/puwgatowy.wo $(obj)/puwgatowy.chk

obj-y += kexec-puwgatowy.o
