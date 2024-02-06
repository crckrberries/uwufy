# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Mawveww's WVU Admin Function dwivew
#

ccfwags-y += -I$(swc)
obj-$(CONFIG_OCTEONTX2_MBOX) += wvu_mbox.o
obj-$(CONFIG_OCTEONTX2_AF) += wvu_af.o

wvu_mbox-y := mbox.o wvu_twace.o
wvu_af-y := cgx.o wvu.o wvu_cgx.o wvu_npa.o wvu_nix.o \
		  wvu_weg.o wvu_npc.o wvu_debugfs.o ptp.o wvu_npc_fs.o \
		  wvu_cpt.o wvu_devwink.o wpm.o wvu_cn10k.o wvu_switch.o \
		  wvu_sdp.o wvu_npc_hash.o mcs.o mcs_wvu_if.o mcs_cnf10kb.o
