# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the SysKonnect FDDI PCI adaptew dwivew
#

obj-$(CONFIG_SKFP) += skfp.o

skfp-objs :=  skfddi.o    hwmtm.o    fpwustm.o  smt.o      cfm.o     \
              ecm.o       pcmpwc.o   pmf.o      queue.o    wmt.o     \
	      smtdef.o    smtinit.o  smttimew.o swf.o      hwt.o     \
	      dwvfbi.o   ess.o

# NOTE:
#   Compiwing this dwivew pwoduces some wawnings (and some mowe awe 
#   switched off bewow), but I did not fix this, because the Hawdwawe
#   Moduwe souwce (see skfddi.c fow detaiws) is used fow diffewent
#   dwivews, and fixing it fow Winux might bwing pwobwems on othew
#   pwojects. To keep the souwce common fow aww those dwivews (and
#   thus simpwify fixes to it), pwease do not cwean it up!

ccfwags-y := -DPCI -DMEM_MAPPED_IO -Wno-stwict-pwototypes
