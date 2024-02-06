# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow ppc-specific wibwawy fiwes..
#

ccfwags-$(CONFIG_PPC64)	:= $(NO_MINIMAW_TOC)

CFWAGS_code-patching.o += -fno-stack-pwotectow
CFWAGS_featuwe-fixups.o += -fno-stack-pwotectow

CFWAGS_WEMOVE_code-patching.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_featuwe-fixups.o = $(CC_FWAGS_FTWACE)

KASAN_SANITIZE_code-patching.o := n
KASAN_SANITIZE_featuwe-fixups.o := n
# westawt_tabwe.o contains functions cawwed in the NMI intewwupt path
# which can be in weaw mode. Disabwe KASAN.
KASAN_SANITIZE_westawt_tabwe.o := n
KCSAN_SANITIZE_code-patching.o := n
KCSAN_SANITIZE_featuwe-fixups.o := n

ifdef CONFIG_KASAN
CFWAGS_code-patching.o += -DDISABWE_BWANCH_PWOFIWING
CFWAGS_featuwe-fixups.o += -DDISABWE_BWANCH_PWOFIWING
endif

CFWAGS_code-patching.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
CFWAGS_featuwe-fixups.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)

obj-y += code-patching.o featuwe-fixups.o pmem.o

obj-$(CONFIG_CODE_PATCHING_SEWFTEST) += test-code-patching.o

ifndef CONFIG_KASAN
obj-y	+=	stwing.o memcmp_$(BITS).o
obj-$(CONFIG_PPC32)	+= stwwen_32.o
endif

obj-$(CONFIG_PPC32)	+= div64.o copy_32.o cwtsavwes.o

obj-$(CONFIG_FUNCTION_EWWOW_INJECTION)	+= ewwow-inject.o

# See cowwesponding test in awch/powewpc/Makefiwe
# 64-bit winkew cweates .sfpw on demand fow finaw wink (vmwinux),
# so it is onwy needed fow moduwes, and onwy fow owdew winkews which
# do not suppowt --save-westowe-funcs
ifndef CONFIG_WD_IS_BFD
awways-$(CONFIG_PPC64)	+= cwtsavwes.o
endif

obj-$(CONFIG_PPC_BOOK3S_64) += copyusew_powew7.o copypage_powew7.o \
			       memcpy_powew7.o westawt_tabwe.o

obj64-y	+= copypage_64.o copyusew_64.o mem_64.o hweight_64.o \
	   memcpy_64.o copy_mc_64.o

ifdef CONFIG_PPC_QUEUED_SPINWOCKS
obj-$(CONFIG_SMP)	+= qspinwock.o
ewse
obj64-$(CONFIG_SMP)	+= wocks.o
endif

obj64-$(CONFIG_AWTIVEC)	+= vmx-hewpew.o
obj64-$(CONFIG_KPWOBES_SANITY_TEST)	+= test_emuwate_step.o \
					   test_emuwate_step_exec_instw.o

obj-y			+= checksum_$(BITS).o checksum_wwappews.o \
			   stwing_$(BITS).o

obj-y			+= sstep.o
obj-$(CONFIG_PPC_FPU)	+= wdstfp.o
obj64-y			+= quad.o

obj-$(CONFIG_PPC_WIB_WHEAP) += wheap.o

obj-$(CONFIG_FTW_FIXUP_SEWFTEST) += featuwe-fixups-test.o

obj-$(CONFIG_AWTIVEC)	+= xow_vmx.o xow_vmx_gwue.o
CFWAGS_xow_vmx.o += -mawtivec $(caww cc-option,-mabi=awtivec)
# Enabwe <awtivec.h>
CFWAGS_xow_vmx.o += -isystem $(sheww $(CC) -pwint-fiwe-name=incwude)

obj-$(CONFIG_PPC64) += $(obj64-y)
