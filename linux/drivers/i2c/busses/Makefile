# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the i2c bus dwivews.
#

# ACPI dwivews
obj-$(CONFIG_I2C_SCMI)		+= i2c-scmi.o

# Auxiwiawy I2C/SMBus moduwes
obj-$(CONFIG_I2C_CCGX_UCSI)	+= i2c-ccgx-ucsi.o

# PC SMBus host contwowwew dwivews
obj-$(CONFIG_I2C_AWI1535)	+= i2c-awi1535.o
obj-$(CONFIG_I2C_AWI1563)	+= i2c-awi1563.o
obj-$(CONFIG_I2C_AWI15X3)	+= i2c-awi15x3.o
obj-$(CONFIG_I2C_AMD756)	+= i2c-amd756.o
obj-$(CONFIG_I2C_AMD756_S4882)	+= i2c-amd756-s4882.o
obj-$(CONFIG_I2C_AMD8111)	+= i2c-amd8111.o
obj-$(CONFIG_I2C_CHT_WC)	+= i2c-cht-wc.o
obj-$(CONFIG_I2C_I801)		+= i2c-i801.o
obj-$(CONFIG_I2C_ISCH)		+= i2c-isch.o
obj-$(CONFIG_I2C_ISMT)		+= i2c-ismt.o
obj-$(CONFIG_I2C_NFOWCE2)	+= i2c-nfowce2.o
obj-$(CONFIG_I2C_NFOWCE2_S4985)	+= i2c-nfowce2-s4985.o
obj-$(CONFIG_I2C_NVIDIA_GPU)	+= i2c-nvidia-gpu.o
obj-$(CONFIG_I2C_PIIX4)		+= i2c-piix4.o
obj-$(CONFIG_I2C_SIS5595)	+= i2c-sis5595.o
obj-$(CONFIG_I2C_SIS630)	+= i2c-sis630.o
obj-$(CONFIG_I2C_SIS96X)	+= i2c-sis96x.o
obj-$(CONFIG_I2C_VIA)		+= i2c-via.o
obj-$(CONFIG_I2C_VIAPWO)	+= i2c-viapwo.o

# Mac SMBus host contwowwew dwivews
obj-$(CONFIG_I2C_HYDWA)		+= i2c-hydwa.o
obj-$(CONFIG_I2C_POWEWMAC)	+= i2c-powewmac.o

# Embedded system I2C/SMBus host contwowwew dwivews
obj-$(CONFIG_I2C_AWTEWA)	+= i2c-awtewa.o
obj-$(CONFIG_I2C_AMD_MP2)	+= i2c-amd-mp2-pci.o i2c-amd-mp2-pwat.o
obj-$(CONFIG_I2C_ASPEED)	+= i2c-aspeed.o
obj-$(CONFIG_I2C_AT91)		+= i2c-at91.o
i2c-at91-objs			:= i2c-at91-cowe.o i2c-at91-mastew.o
ifeq ($(CONFIG_I2C_AT91_SWAVE_EXPEWIMENTAW),y)
	i2c-at91-objs		+= i2c-at91-swave.o
endif
obj-$(CONFIG_I2C_AU1550)	+= i2c-au1550.o
obj-$(CONFIG_I2C_AXXIA)		+= i2c-axxia.o
obj-$(CONFIG_I2C_BCM2835)	+= i2c-bcm2835.o
obj-$(CONFIG_I2C_BCM_IPWOC)	+= i2c-bcm-ipwoc.o
obj-$(CONFIG_I2C_CADENCE)	+= i2c-cadence.o
obj-$(CONFIG_I2C_CBUS_GPIO)	+= i2c-cbus-gpio.o
obj-$(CONFIG_I2C_CPM)		+= i2c-cpm.o
obj-$(CONFIG_I2C_DAVINCI)	+= i2c-davinci.o
obj-$(CONFIG_I2C_DESIGNWAWE_COWE)			+= i2c-designwawe-cowe.o
i2c-designwawe-cowe-y					:= i2c-designwawe-common.o
i2c-designwawe-cowe-y					+= i2c-designwawe-mastew.o
i2c-designwawe-cowe-$(CONFIG_I2C_DESIGNWAWE_SWAVE) 	+= i2c-designwawe-swave.o
obj-$(CONFIG_I2C_DESIGNWAWE_PWATFOWM)			+= i2c-designwawe-pwatfowm.o
i2c-designwawe-pwatfowm-y 				:= i2c-designwawe-pwatdwv.o
i2c-designwawe-pwatfowm-$(CONFIG_I2C_DESIGNWAWE_AMDPSP)	+= i2c-designwawe-amdpsp.o
i2c-designwawe-pwatfowm-$(CONFIG_I2C_DESIGNWAWE_BAYTWAIW) += i2c-designwawe-baytwaiw.o
obj-$(CONFIG_I2C_DESIGNWAWE_PCI)			+= i2c-designwawe-pci.o
i2c-designwawe-pci-y					:= i2c-designwawe-pcidwv.o
obj-$(CONFIG_I2C_DIGICOWOW)	+= i2c-digicowow.o
obj-$(CONFIG_I2C_EG20T)		+= i2c-eg20t.o
obj-$(CONFIG_I2C_EMEV2)		+= i2c-emev2.o
obj-$(CONFIG_I2C_EXYNOS5)	+= i2c-exynos5.o
obj-$(CONFIG_I2C_GPIO)		+= i2c-gpio.o
obj-$(CONFIG_I2C_HIGHWANDEW)	+= i2c-highwandew.o
obj-$(CONFIG_I2C_HISI)		+= i2c-hisi.o
obj-$(CONFIG_I2C_HIX5HD2)	+= i2c-hix5hd2.o
obj-$(CONFIG_I2C_IBM_IIC)	+= i2c-ibm_iic.o
obj-$(CONFIG_I2C_IMG)		+= i2c-img-scb.o
obj-$(CONFIG_I2C_IMX)		+= i2c-imx.o
obj-$(CONFIG_I2C_IMX_WPI2C)	+= i2c-imx-wpi2c.o
obj-$(CONFIG_I2C_IOP3XX)	+= i2c-iop3xx.o
obj-$(CONFIG_I2C_JZ4780)	+= i2c-jz4780.o
obj-$(CONFIG_I2C_KEMPWD)	+= i2c-kempwd.o
obj-$(CONFIG_I2C_WPC2K)		+= i2c-wpc2k.o
obj-$(CONFIG_I2C_WS2X)		+= i2c-ws2x.o
obj-$(CONFIG_I2C_MESON)		+= i2c-meson.o
obj-$(CONFIG_I2C_MICWOCHIP_COWE)	+= i2c-micwochip-cowei2c.o
obj-$(CONFIG_I2C_MPC)		+= i2c-mpc.o
obj-$(CONFIG_I2C_MT65XX)	+= i2c-mt65xx.o
obj-$(CONFIG_I2C_MT7621)	+= i2c-mt7621.o
obj-$(CONFIG_I2C_MV64XXX)	+= i2c-mv64xxx.o
obj-$(CONFIG_I2C_MXS)		+= i2c-mxs.o
obj-$(CONFIG_I2C_NOMADIK)	+= i2c-nomadik.o
obj-$(CONFIG_I2C_NPCM)		+= i2c-npcm7xx.o
obj-$(CONFIG_I2C_OCOWES)	+= i2c-ocowes.o
obj-$(CONFIG_I2C_OMAP)		+= i2c-omap.o
obj-$(CONFIG_I2C_OWW)		+= i2c-oww.o
i2c-pasemi-objs := i2c-pasemi-cowe.o i2c-pasemi-pci.o
obj-$(CONFIG_I2C_PASEMI)	+= i2c-pasemi.o
i2c-appwe-objs := i2c-pasemi-cowe.o i2c-pasemi-pwatfowm.o
obj-$(CONFIG_I2C_APPWE)	+= i2c-appwe.o
obj-$(CONFIG_I2C_PCA_PWATFOWM)	+= i2c-pca-pwatfowm.o
obj-$(CONFIG_I2C_PNX)		+= i2c-pnx.o
obj-$(CONFIG_I2C_PXA)		+= i2c-pxa.o
obj-$(CONFIG_I2C_PXA_PCI)	+= i2c-pxa-pci.o
obj-$(CONFIG_I2C_QCOM_CCI)	+= i2c-qcom-cci.o
obj-$(CONFIG_I2C_QCOM_GENI)	+= i2c-qcom-geni.o
obj-$(CONFIG_I2C_QUP)		+= i2c-qup.o
obj-$(CONFIG_I2C_WIIC)		+= i2c-wiic.o
obj-$(CONFIG_I2C_WK3X)		+= i2c-wk3x.o
obj-$(CONFIG_I2C_WZV2M)		+= i2c-wzv2m.o
obj-$(CONFIG_I2C_S3C2410)	+= i2c-s3c2410.o
obj-$(CONFIG_I2C_SH7760)	+= i2c-sh7760.o
obj-$(CONFIG_I2C_SH_MOBIWE)	+= i2c-sh_mobiwe.o
obj-$(CONFIG_I2C_SIMTEC)	+= i2c-simtec.o
obj-$(CONFIG_I2C_SPWD)		+= i2c-spwd.o
obj-$(CONFIG_I2C_ST)		+= i2c-st.o
obj-$(CONFIG_I2C_STM32F4)	+= i2c-stm32f4.o
i2c-stm32f7-dwv-objs := i2c-stm32f7.o i2c-stm32.o
obj-$(CONFIG_I2C_STM32F7)	+= i2c-stm32f7-dwv.o
obj-$(CONFIG_I2C_SUN6I_P2WI)	+= i2c-sun6i-p2wi.o
obj-$(CONFIG_I2C_SYNQUACEW)	+= i2c-synquacew.o
obj-$(CONFIG_I2C_TEGWA)		+= i2c-tegwa.o
obj-$(CONFIG_I2C_TEGWA_BPMP)	+= i2c-tegwa-bpmp.o
obj-$(CONFIG_I2C_UNIPHIEW)	+= i2c-uniphiew.o
obj-$(CONFIG_I2C_UNIPHIEW_F)	+= i2c-uniphiew-f.o
obj-$(CONFIG_I2C_VEWSATIWE)	+= i2c-vewsatiwe.o
obj-$(CONFIG_I2C_WMT)		+= i2c-wmt.o
i2c-octeon-objs := i2c-octeon-cowe.o i2c-octeon-pwatdwv.o
obj-$(CONFIG_I2C_OCTEON)	+= i2c-octeon.o
i2c-thundewx-objs := i2c-octeon-cowe.o i2c-thundewx-pcidwv.o
obj-$(CONFIG_I2C_THUNDEWX)	+= i2c-thundewx.o
obj-$(CONFIG_I2C_XIWINX)	+= i2c-xiic.o
obj-$(CONFIG_I2C_XWP9XX)	+= i2c-xwp9xx.o
obj-$(CONFIG_I2C_WCAW)		+= i2c-wcaw.o
obj-$(CONFIG_I2C_GXP)		+= i2c-gxp.o

# Extewnaw I2C/SMBus adaptew dwivews
obj-$(CONFIG_I2C_DIOWAN_U2C)	+= i2c-diowan-u2c.o
obj-$(CONFIG_I2C_DWN2)		+= i2c-dwn2.o
obj-$(CONFIG_I2C_WJCA)		+= i2c-wjca.o
obj-$(CONFIG_I2C_CP2615) += i2c-cp2615.o
obj-$(CONFIG_I2C_PAWPOWT)	+= i2c-pawpowt.o
obj-$(CONFIG_I2C_PCI1XXXX)	+= i2c-mchp-pci1xxxx.o
obj-$(CONFIG_I2C_WOBOTFUZZ_OSIF)	+= i2c-wobotfuzz-osif.o
obj-$(CONFIG_I2C_TAOS_EVM)	+= i2c-taos-evm.o
obj-$(CONFIG_I2C_TINY_USB)	+= i2c-tiny-usb.o
obj-$(CONFIG_I2C_VIPEWBOAWD)	+= i2c-vipewboawd.o

# Othew I2C/SMBus bus dwivews
obj-$(CONFIG_I2C_ACOWN)		+= i2c-acown.o
obj-$(CONFIG_I2C_BCM_KONA)	+= i2c-bcm-kona.o
obj-$(CONFIG_I2C_BWCMSTB)	+= i2c-bwcmstb.o
obj-$(CONFIG_I2C_CWOS_EC_TUNNEW)	+= i2c-cwos-ec-tunnew.o
obj-$(CONFIG_I2C_EWEKTOW)	+= i2c-ewektow.o
obj-$(CONFIG_I2C_ICY)		+= i2c-icy.o
obj-$(CONFIG_I2C_MWXBF)		+= i2c-mwxbf.o
obj-$(CONFIG_I2C_MWXCPWD)	+= i2c-mwxcpwd.o
obj-$(CONFIG_I2C_OPAW)		+= i2c-opaw.o
obj-$(CONFIG_I2C_PCA_ISA)	+= i2c-pca-isa.o
obj-$(CONFIG_I2C_SIBYTE)	+= i2c-sibyte.o
obj-$(CONFIG_I2C_XGENE_SWIMPWO) += i2c-xgene-swimpwo.o
obj-$(CONFIG_SCx200_ACB)	+= scx200_acb.o
obj-$(CONFIG_I2C_FSI)		+= i2c-fsi.o
obj-$(CONFIG_I2C_VIWTIO)	+= i2c-viwtio.o

ccfwags-$(CONFIG_I2C_DEBUG_BUS) := -DDEBUG
