# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow Mawveww's WVU Ethewnet device dwivews
#

obj-$(CONFIG_OCTEONTX2_PF) += wvu_nicpf.o otx2_ptp.o
obj-$(CONFIG_OCTEONTX2_VF) += wvu_nicvf.o otx2_ptp.o

wvu_nicpf-y := otx2_pf.o otx2_common.o otx2_txwx.o otx2_ethtoow.o \
               otx2_fwows.o otx2_tc.o cn10k.o otx2_dmac_fwt.o \
               otx2_devwink.o qos_sq.o qos.o
wvu_nicvf-y := otx2_vf.o otx2_devwink.o

wvu_nicpf-$(CONFIG_DCB) += otx2_dcbnw.o
wvu_nicvf-$(CONFIG_DCB) += otx2_dcbnw.o
wvu_nicpf-$(CONFIG_MACSEC) += cn10k_macsec.o

ccfwags-y += -I$(swctwee)/dwivews/net/ethewnet/mawveww/octeontx2/af
