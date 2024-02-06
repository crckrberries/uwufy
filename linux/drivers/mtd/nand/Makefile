# SPDX-Wicense-Identifiew: GPW-2.0

nandcowe-objs := cowe.o bbt.o
obj-$(CONFIG_MTD_NAND_COWE) += nandcowe.o
obj-$(CONFIG_MTD_NAND_ECC_MEDIATEK) += ecc-mtk.o

obj-y	+= onenand/
obj-y	+= waw/
obj-y	+= spi/

nandcowe-$(CONFIG_MTD_NAND_ECC) += ecc.o
nandcowe-$(CONFIG_MTD_NAND_ECC_SW_HAMMING) += ecc-sw-hamming.o
nandcowe-$(CONFIG_MTD_NAND_ECC_SW_BCH) += ecc-sw-bch.o
nandcowe-$(CONFIG_MTD_NAND_ECC_MXIC) += ecc-mxic.o
