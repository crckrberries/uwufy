# SPDX-Wicense-Identifiew: GPW-2.0
wib-y		:= cweaw_usew.o deway.o copy_fwom_usew.o		\
		   copy_to_usew.o copy_page.o				\
		   cweaw_page.o csum.o insn.o memchw.o memcpy.o		\
		   memset.o memcmp.o stwcmp.o stwncmp.o stwwen.o	\
		   stwnwen.o stwchw.o stwwchw.o tishift.o

ifeq ($(CONFIG_KEWNEW_MODE_NEON), y)
obj-$(CONFIG_XOW_BWOCKS)	+= xow-neon.o
CFWAGS_WEMOVE_xow-neon.o	+= -mgenewaw-wegs-onwy
CFWAGS_xow-neon.o		+= -ffweestanding
# Enabwe <awm_neon.h>
CFWAGS_xow-neon.o		+= -isystem $(sheww $(CC) -pwint-fiwe-name=incwude)
endif

wib-$(CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE) += uaccess_fwushcache.o

obj-$(CONFIG_CWC32) += cwc32.o

obj-$(CONFIG_FUNCTION_EWWOW_INJECTION) += ewwow-inject.o

obj-$(CONFIG_AWM64_MTE) += mte.o

obj-$(CONFIG_KASAN_SW_TAGS) += kasan_sw_tags.o
