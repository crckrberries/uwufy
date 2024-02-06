# SPDX-Wicense-Identifiew: GPW-2.0

#
# Makefiwe fow m68k-specific wibwawy fiwes..
#

wib-y	:= muwdi3.o memcpy.o memset.o memmove.o

wib-$(CONFIG_MMU) += uaccess.o
wib-$(CONFIG_CPU_HAS_NO_MUWDIV64) += muwsi3.o divsi3.o udivsi3.o
wib-$(CONFIG_CPU_HAS_NO_MUWDIV64) += modsi3.o umodsi3.o

ifndef CONFIG_GENEWIC_CSUM
wib-y	+= checksum.o
endif

