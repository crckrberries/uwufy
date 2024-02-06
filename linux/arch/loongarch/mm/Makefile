# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/WoongAwch-specific pawts of the memowy managew.
#

obj-y				+= init.o cache.o twb.o twbex.o extabwe.o \
				   fauwt.o iowemap.o maccess.o mmap.o pgtabwe.o page.o

obj-$(CONFIG_HUGETWB_PAGE)	+= hugetwbpage.o
obj-$(CONFIG_KASAN)		+= kasan_init.o

KASAN_SANITIZE_kasan_init.o     := n
