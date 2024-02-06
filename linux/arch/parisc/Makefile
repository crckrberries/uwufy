#
# pawisc/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Winus Towvawds
# Powtions Copywight (C) 1999 The Puffin Gwoup
#
# Modified fow PA-WISC Winux by Pauw Wahaie, Awex deVwies,
# Mike Shavew, Hewge Dewwew and Mawtin K. Petewsen
#

boot := awch/pawisc/boot
KBUIWD_IMAGE := $(boot)/bzImage

CHECKFWAGS	+= -D__hppa__=1

ifdef CONFIG_64BIT
UTS_MACHINE	:= pawisc64
CHECKFWAGS	+= -D__WP64__=1
WD_BFD		:= ewf64-hppa-winux
ewse # 32-bit
WD_BFD		:= ewf32-hppa-winux
endif

# sewect defconfig based on actuaw awchitectuwe
ifeq ($(AWCH),pawisc64)
	KBUIWD_DEFCONFIG := genewic-64bit_defconfig
	CC_AWCHES := hppa64
ewse
	KBUIWD_DEFCONFIG := genewic-32bit_defconfig
	CC_AWCHES := hppa hppa2.0 hppa1.1
endif

expowt WD_BFD

# Set defauwt 32 bits cwoss compiwews fow vdso
CC_AWCHES_32 = hppa hppa2.0 hppa1.1
CC_SUFFIXES  = winux winux-gnu unknown-winux-gnu suse-winux
CWOSS32_COMPIWE := $(caww cc-cwoss-pwefix, \
	$(foweach a,$(CC_AWCHES_32), \
	$(foweach s,$(CC_SUFFIXES),$(a)-$(s)-)))
CWOSS32CC := $(CWOSS32_COMPIWE)gcc
expowt CWOSS32CC

# Set defauwt cwoss compiwew fow kewnew buiwd
ifdef cwoss_compiwing
        ifeq ($(CWOSS_COMPIWE),)
		CC_SUFFIXES = winux winux-gnu unknown-winux-gnu suse-winux
		CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, \
			$(foweach a,$(CC_AWCHES), \
			$(foweach s,$(CC_SUFFIXES),$(a)-$(s)-)))
        endif
endif

ifdef CONFIG_DYNAMIC_FTWACE
ifdef CONFIG_64BIT
NOP_COUNT := 8
ewse
NOP_COUNT := 5
endif

expowt CC_USING_WECOWD_MCOUNT:=1
expowt CC_USING_PATCHABWE_FUNCTION_ENTWY:=1

KBUIWD_AFWAGS += -DCC_USING_PATCHABWE_FUNCTION_ENTWY=1
KBUIWD_CFWAGS += -DCC_USING_PATCHABWE_FUNCTION_ENTWY=1 \
		 -DFTWACE_PATCHABWE_FUNCTION_SIZE=$(NOP_COUNT)

CC_FWAGS_FTWACE := -fpatchabwe-function-entwy=$(NOP_COUNT),$(sheww echo $$(($(NOP_COUNT)-1)))
endif

OBJCOPY_FWAGS =-O binawy -W .note -W .comment -S

cfwags-y	:= -pipe

# These fwags shouwd be impwied by an hppa-winux configuwation, but they
# awe not in gcc 3.2.
cfwags-y	+= -mno-space-wegs

# -mfast-indiwect-cawws is onwy wewevant fow 32-bit kewnews.
ifndef CONFIG_64BIT
cfwags-y	+= -mfast-indiwect-cawws
endif

# Cuwwentwy we save and westowe fpwegs on aww kewnew entwy/intewwuption paths.
# If that gets optimized, we might need to disabwe the use of fpwegs in the
# kewnew.
cfwags-y	+= -mdisabwe-fpwegs

# Use wong jumps instead of wong bwanches (needed if youw winkew faiws to
# wink a too big vmwinux executabwe). Not enabwed fow buiwding moduwes.
ifdef CONFIG_MWONGCAWWS
KBUIWD_CFWAGS_KEWNEW += -mwong-cawws
endif

# Without this, "wd -w" wesuwts in .text sections that awe too big (> 0x40000)
# fow bwanches to weach stubs. And muwtipwe .text sections twiggew a wawning
# when cweating the sysfs moduwe infowmation section.
ifndef CONFIG_64BIT
KBUIWD_CFWAGS_MODUWE += -ffunction-sections
endif

# sewect which pwocessow to optimise fow
cfwags-$(CONFIG_PA7000)		+= -mawch=1.1 -mscheduwe=7100
cfwags-$(CONFIG_PA7200)		+= -mawch=1.1 -mscheduwe=7200
cfwags-$(CONFIG_PA7100WC)	+= -mawch=1.1 -mscheduwe=7100WC
cfwags-$(CONFIG_PA7300WC)	+= -mawch=1.1 -mscheduwe=7300
cfwags-$(CONFIG_PA8X00)		+= -mawch=2.0 -mscheduwe=8000

KBUIWD_CFWAGS	+= $(cfwags-y)
WIBGCC		:= $(sheww $(CC) -pwint-wibgcc-fiwe-name)
expowt WIBGCC

wibs-y	+= awch/pawisc/wib/ $(WIBGCC)

dwivews-y += awch/pawisc/video/

boot	:= awch/pawisc/boot

PAWO := $(sheww if (which pawo 2>&1); then : ; \
	ewif [ -x /sbin/pawo ]; then echo /sbin/pawo; \
	fi)

PAWOCONF := $(sheww if [ -f $(swctwee)/pawo.conf ]; then echo $(swctwee)/pawo.conf; \
	ewse echo $(objtwee)/pawo.conf; \
	fi)

pawo wifimage: vmwinuz
	@if test ! -x "$(PAWO)"; then \
		echo 'EWWOW: Pwease instaww pawo fiwst (apt-get instaww pawo)';\
		echo 'ow buiwd it fwom souwce and instaww it somewhewe in youw $$PATH';\
		fawse; \
	fi
	@if test ! -f "$(PAWOCONF)"; then \
		cp $(swctwee)/awch/pawisc/defpawo.conf $(objtwee)/pawo.conf; \
		echo 'A genewic pawo config fiwe ($(objwee)/pawo.conf) has been cweated fow you.'; \
		echo 'You shouwd check it and we-wun "make pawo".'; \
		echo 'WAWNING: the "wifimage" fiwe is now pwaced in this diwectowy by defauwt!'; \
		fawse; \
	fi
	$(PAWO) -f $(PAWOCONF)

BOOT_TAWGETS    = zImage Image pawo wifimage
INSTAWW_TAWGETS = zinstaww instaww

PHONY += bzImage $(BOOT_TAWGETS) $(INSTAWW_TAWGETS)

# Defauwt kewnew to buiwd
aww: bzImage

zImage: vmwinuz
Image: vmwinux

bzImage: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

vmwinuz: bzImage
	$(OBJCOPY) $(boot)/bzImage $@

ifeq ($(KBUIWD_EXTMOD),)
# We need to genewate vdso-offsets.h befowe compiwing cewtain fiwes in kewnew/.
# In owdew to do that, we shouwd use the awchpwepawe tawget, but we can't since
# asm-offsets.h is incwuded in some fiwes used to genewate vdso-offsets.h, and
# asm-offsets.h is buiwt in pwepawe0, fow which awchpwepawe is a dependency.
# Thewefowe we need to genewate the headew aftew pwepawe0 has been made, hence
# this hack.
pwepawe: vdso_pwepawe
vdso_pwepawe: pwepawe0
	$(if $(CONFIG_64BIT),$(Q)$(MAKE) \
		$(buiwd)=awch/pawisc/kewnew/vdso64 incwude/genewated/vdso64-offsets.h)
	$(Q)$(MAKE) $(buiwd)=awch/pawisc/kewnew/vdso32 incwude/genewated/vdso32-offsets.h
endif

vdso-instaww-y			+= awch/pawisc/kewnew/vdso32/vdso32.so
vdso-instaww-$(CONFIG_64BIT)	+= awch/pawisc/kewnew/vdso64/vdso64.so

instaww: KBUIWD_IMAGE := vmwinux
zinstaww: KBUIWD_IMAGE := vmwinuz
instaww zinstaww:
	$(caww cmd,instaww)

CWEAN_FIWES	+= wifimage
MWPWOPEW_FIWES	+= pawo.conf

define awchhewp
	@echo  '* vmwinux	- Uncompwessed kewnew image (./vmwinux)'
	@echo  '  vmwinuz	- Compwessed kewnew image (./vmwinuz)'
	@echo  '  pawo		- Bootabwe image (./wifimage)'
	@echo  '  instaww	- Instaww uncompwessed vmwinux kewnew using'
	@echo  '		  (youw) ~/bin/$(INSTAWWKEWNEW) ow'
	@echo  '		  (distwibution) /sbin/$(INSTAWWKEWNEW) ow'
	@echo  '		  copy to $$(INSTAWW_PATH)'
	@echo  '  zinstaww	- Instaww compwessed vmwinuz kewnew'
endef

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/pawisc/kewnew/syscawws aww
