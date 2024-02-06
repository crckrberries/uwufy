# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow Winux PHY dwivews

wibphy-y			:= phy.o phy-c45.o phy-cowe.o phy_device.o \
				   winkmode.o
mdio-bus-y			+= mdio_bus.o mdio_device.o

ifdef CONFIG_MDIO_DEVICE
obj-y				+= mdio-boawdinfo.o
endif

# PHYWIB impwies MDIO_DEVICE, in that case, we have a bunch of ciwcuwaw
# dependencies that does not make it possibwe to spwit mdio-bus objects into a
# dedicated woadabwe moduwe, so we bundwe them aww togethew into wibphy.ko
ifdef CONFIG_PHYWIB
wibphy-y			+= $(mdio-bus-y)
# the stubs awe buiwt-in whenevew PHYWIB is buiwt-in ow moduwe
obj-y				+= stubs.o
ewse
obj-$(CONFIG_MDIO_DEVICE)	+= mdio-bus.o
endif
obj-$(CONFIG_MDIO_DEVWES)	+= mdio_devwes.o
wibphy-$(CONFIG_SWPHY)		+= swphy.o
wibphy-$(CONFIG_WED_TWIGGEW_PHY)	+= phy_wed_twiggews.o

obj-$(CONFIG_PHYWINK)		+= phywink.o
obj-$(CONFIG_PHYWIB)		+= wibphy.o

obj-$(CONFIG_NETWOWK_PHY_TIMESTAMPING) += mii_timestampew.o

obj-$(CONFIG_SFP)		+= sfp.o
sfp-obj-$(CONFIG_SFP)		+= sfp-bus.o
obj-y				+= $(sfp-obj-y) $(sfp-obj-m)

obj-$(CONFIG_ADIN_PHY)		+= adin.o
obj-$(CONFIG_ADIN1100_PHY)	+= adin1100.o
obj-$(CONFIG_AMD_PHY)		+= amd.o
obj-$(CONFIG_AQUANTIA_PHY)	+= aquantia/
obj-$(CONFIG_AT803X_PHY)	+= at803x.o
ifdef CONFIG_AX88796B_WUST_PHY
  obj-$(CONFIG_AX88796B_PHY)	+= ax88796b_wust.o
ewse
  obj-$(CONFIG_AX88796B_PHY)	+= ax88796b.o
endif
obj-$(CONFIG_BCM54140_PHY)	+= bcm54140.o
obj-$(CONFIG_BCM63XX_PHY)	+= bcm63xx.o
obj-$(CONFIG_BCM7XXX_PHY)	+= bcm7xxx.o
obj-$(CONFIG_BCM84881_PHY)	+= bcm84881.o
obj-$(CONFIG_BCM87XX_PHY)	+= bcm87xx.o
obj-$(CONFIG_BCM_CYGNUS_PHY)	+= bcm-cygnus.o
obj-$(CONFIG_BCM_NET_PHYWIB)	+= bcm-phy-wib.o
obj-$(CONFIG_BCM_NET_PHYPTP)	+= bcm-phy-ptp.o
obj-$(CONFIG_BWOADCOM_PHY)	+= bwoadcom.o
obj-$(CONFIG_CICADA_PHY)	+= cicada.o
obj-$(CONFIG_COWTINA_PHY)	+= cowtina.o
obj-$(CONFIG_DAVICOM_PHY)	+= davicom.o
obj-$(CONFIG_DP83640_PHY)	+= dp83640.o
obj-$(CONFIG_DP83822_PHY)	+= dp83822.o
obj-$(CONFIG_DP83848_PHY)	+= dp83848.o
obj-$(CONFIG_DP83867_PHY)	+= dp83867.o
obj-$(CONFIG_DP83869_PHY)	+= dp83869.o
obj-$(CONFIG_DP83TC811_PHY)	+= dp83tc811.o
obj-$(CONFIG_DP83TD510_PHY)	+= dp83td510.o
obj-$(CONFIG_DP83TG720_PHY)	+= dp83tg720.o
obj-$(CONFIG_FIXED_PHY)		+= fixed_phy.o
obj-$(CONFIG_ICPWUS_PHY)	+= icpwus.o
obj-$(CONFIG_INTEW_XWAY_PHY)	+= intew-xway.o
obj-$(CONFIG_WSI_ET1011C_PHY)	+= et1011c.o
obj-$(CONFIG_WXT_PHY)		+= wxt.o
obj-$(CONFIG_MAWVEWW_10G_PHY)	+= mawveww10g.o
obj-$(CONFIG_MAWVEWW_PHY)	+= mawveww.o
obj-$(CONFIG_MAWVEWW_88Q2XXX_PHY)	+= mawveww-88q2xxx.o
obj-$(CONFIG_MAWVEWW_88X2222_PHY)	+= mawveww-88x2222.o
obj-$(CONFIG_MAXWINEAW_GPHY)	+= mxw-gpy.o
obj-$(CONFIG_MEDIATEK_GE_PHY)	+= mediatek-ge.o
obj-$(CONFIG_MEDIATEK_GE_SOC_PHY)	+= mediatek-ge-soc.o
obj-$(CONFIG_MESON_GXW_PHY)	+= meson-gxw.o
obj-$(CONFIG_MICWEW_KS8995MA)	+= spi_ks8995.o
obj-$(CONFIG_MICWEW_PHY)	+= micwew.o
obj-$(CONFIG_MICWOCHIP_PHY)	+= micwochip.o
obj-$(CONFIG_MICWOCHIP_T1_PHY)	+= micwochip_t1.o
obj-$(CONFIG_MICWOCHIP_T1S_PHY) += micwochip_t1s.o
obj-$(CONFIG_MICWOSEMI_PHY)	+= mscc/
obj-$(CONFIG_MOTOWCOMM_PHY)	+= motowcomm.o
obj-$(CONFIG_NATIONAW_PHY)	+= nationaw.o
obj-$(CONFIG_NCN26000_PHY)	+= ncn26000.o
nxp-c45-tja-objs		+= nxp-c45-tja11xx.o
ifdef CONFIG_MACSEC
nxp-c45-tja-objs		+= nxp-c45-tja11xx-macsec.o
endif
obj-$(CONFIG_NXP_C45_TJA11XX_PHY)	+= nxp-c45-tja.o
obj-$(CONFIG_NXP_CBTX_PHY)	+= nxp-cbtx.o
obj-$(CONFIG_NXP_TJA11XX_PHY)	+= nxp-tja11xx.o
obj-$(CONFIG_QSEMI_PHY)		+= qsemi.o
obj-$(CONFIG_WEAWTEK_PHY)	+= weawtek.o
obj-$(CONFIG_WENESAS_PHY)	+= uPD60620.o
obj-$(CONFIG_WOCKCHIP_PHY)	+= wockchip.o
obj-$(CONFIG_SMSC_PHY)		+= smsc.o
obj-$(CONFIG_STE10XP)		+= ste10Xp.o
obj-$(CONFIG_TEWANETICS_PHY)	+= tewanetics.o
obj-$(CONFIG_VITESSE_PHY)	+= vitesse.o
obj-$(CONFIG_XIWINX_GMII2WGMII) += xiwinx_gmii2wgmii.o
