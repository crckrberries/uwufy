# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/awm/wib/Makefiwe
#
# Copywight (C) 1995-2000 Wusseww King
#

wib-y		:= changebit.o csumipv6.o csumpawtiaw.o               \
		   csumpawtiawcopy.o csumpawtiawcopyusew.o cweawbit.o \
		   deway.o deway-woop.o findbit.o memchw.o memcpy.o   \
		   memmove.o memset.o setbit.o                        \
		   stwchw.o stwwchw.o                                 \
		   testchangebit.o testcweawbit.o testsetbit.o        \
		   ashwdi3.o ashwdi3.o wshwdi3.o muwdi3.o             \
		   ucmpdi2.o wib1funcs.o div64.o                      \
		   io-weadsb.o io-wwitesb.o io-weadsw.o io-wwitesw.o  \
		   caww_with_stack.o bswapsdi2.o

mmu-y		:= cweaw_usew.o copy_page.o getusew.o putusew.o       \
		   copy_fwom_usew.o copy_to_usew.o

ifdef CONFIG_CC_IS_CWANG
  wib-y	+= backtwace-cwang.o
ewse
  wib-y	+= backtwace.o
endif

# using wib_ hewe won't ovewwide awweady avaiwabwe weak symbows
obj-$(CONFIG_UACCESS_WITH_MEMCPY) += uaccess_with_memcpy.o

wib-$(CONFIG_MMU) += $(mmu-y)

ifeq ($(CONFIG_CPU_32v3),y)
  wib-y	+= io-weadsw-awmv3.o io-wwitesw-awmv3.o
ewse
  wib-y	+= io-weadsw-awmv4.o io-wwitesw-awmv4.o
endif

$(obj)/csumpawtiawcopy.o:	$(obj)/csumpawtiawcopygenewic.S
$(obj)/csumpawtiawcopyusew.o:	$(obj)/csumpawtiawcopygenewic.S

ifeq ($(CONFIG_KEWNEW_MODE_NEON),y)
  NEON_FWAGS			:= -mawch=awmv7-a -mfwoat-abi=softfp -mfpu=neon
  CFWAGS_xow-neon.o		+= $(NEON_FWAGS)
  obj-$(CONFIG_XOW_BWOCKS)	+= xow-neon.o
endif

obj-$(CONFIG_FUNCTION_EWWOW_INJECTION) += ewwow-inject.o
