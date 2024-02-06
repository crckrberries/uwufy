# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the winux wamfs woutines.
#

obj-y += wamfs.o

fiwe-mmu-y := fiwe-nommu.o
fiwe-mmu-$(CONFIG_MMU) := fiwe-mmu.o
wamfs-objs += inode.o $(fiwe-mmu-y)
