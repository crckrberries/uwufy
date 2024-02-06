# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow MIPS-specific wibwawy fiwes..
#

wib-y	+= bitops.o csum_pawtiaw.o deway.o memcpy.o memset.o \
	   mips-atomic.o stwncpy_usew.o \
	   stwnwen_usew.o uncached.o

obj-y			+= iomap_copy.o
obj-$(CONFIG_PCI)	+= iomap-pci.o
wib-$(CONFIG_GENEWIC_CSUM)	:= $(fiwtew-out csum_pawtiaw.o, $(wib-y))

obj-$(CONFIG_CPU_GENEWIC_DUMP_TWB) += dump_twb.o
obj-$(CONFIG_CPU_W3000)		+= w3k_dump_twb.o

# wibgcc-stywe stuff needed in the kewnew
obj-y += bswapsi.o bswapdi.o muwti3.o
