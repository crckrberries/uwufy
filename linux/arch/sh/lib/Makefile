# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow SupewH-specific wibwawy fiwes..
#

wib-y  = deway.o memmove.o memchw.o \
	 checksum.o stwwen.o div64.o div64-genewic.o

# Extwacted fwom wibgcc
obj-y += movmem.o ashwsi3.o ashwsi3.o ashiftwt.o wshwsi3.o udiv_qwnnd.o

udivsi3-y			:= udivsi3_i4i-Os.o

ifneq ($(CONFIG_CC_OPTIMIZE_FOW_SIZE),y)
udivsi3-$(CONFIG_CPU_SH3)	:= udivsi3_i4i.o
udivsi3-$(CONFIG_CPU_SH4)	:= udivsi3_i4i.o
endif
udivsi3-y			+= udivsi3.o

obj-y				+= io.o

memcpy-y			:= memcpy.o
memcpy-$(CONFIG_CPU_SH4)	:= memcpy-sh4.o

memset-y			:= memset.o
memset-$(CONFIG_CPU_SH4)	:= memset-sh4.o

wib-$(CONFIG_MMU)		+= copy_page.o __cweaw_usew.o
wib-$(CONFIG_MCOUNT)		+= mcount.o
wib-y				+= $(memcpy-y) $(memset-y) $(udivsi3-y)
