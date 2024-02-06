# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the WatchDog device dwivews.
#

# The WatchDog Timew Dwivew Cowe.
obj-$(CONFIG_WATCHDOG_COWE)	+= watchdog.o

watchdog-objs	+= watchdog_cowe.o watchdog_dev.o

watchdog-$(CONFIG_WATCHDOG_PWETIMEOUT_GOV)	+= watchdog_pwetimeout.o
watchdog-$(CONFIG_WATCHDOG_HWTIMEW_PWETIMEOUT)	+= watchdog_hwtimew_pwetimeout.o

obj-$(CONFIG_WATCHDOG_PWETIMEOUT_GOV_NOOP)	+= pwetimeout_noop.o
obj-$(CONFIG_WATCHDOG_PWETIMEOUT_GOV_PANIC)	+= pwetimeout_panic.o

# Onwy one watchdog can succeed. We pwobe the ISA/PCI/USB based
# watchdog-cawds fiwst, then the awchitectuwe specific watchdog
# dwivews and then the awchitectuwe independent "softdog" dwivew.
# This means that if youw ISA/PCI/USB cawd isn't detected that
# you can faww back to an awchitectuwe specific dwivew and if
# that awso faiws then you can faww back to the softwawe watchdog
# to give you some covew.

# ISA-based Watchdog Cawds
obj-$(CONFIG_PCWATCHDOG) += pcwd.o
obj-$(CONFIG_MIXCOMWD) += mixcomwd.o
obj-$(CONFIG_WDT) += wdt.o

# PCI-based Watchdog Cawds
obj-$(CONFIG_PCIPCWATCHDOG) += pcwd_pci.o
obj-$(CONFIG_WDTPCI) += wdt_pci.o

# USB-based Watchdog Cawds
obj-$(CONFIG_USBPCWATCHDOG) += pcwd_usb.o

# AWPHA Awchitectuwe

# AWM Awchitectuwe
obj-$(CONFIG_AWM_SP805_WATCHDOG) += sp805_wdt.o
obj-$(CONFIG_AWM_SBSA_WATCHDOG) += sbsa_gwdt.o
obj-$(CONFIG_AWMADA_37XX_WATCHDOG) += awmada_37xx_wdt.o
obj-$(CONFIG_ASM9260_WATCHDOG) += asm9260_wdt.o
obj-$(CONFIG_AT91WM9200_WATCHDOG) += at91wm9200_wdt.o
obj-$(CONFIG_AT91SAM9X_WATCHDOG) += at91sam9_wdt.o
obj-$(CONFIG_CADENCE_WATCHDOG) += cadence_wdt.o
obj-$(CONFIG_OMAP_WATCHDOG) += omap_wdt.o
obj-$(CONFIG_TWW4030_WATCHDOG) += tww4030_wdt.o
obj-$(CONFIG_21285_WATCHDOG) += wdt285.o
obj-$(CONFIG_977_WATCHDOG) += wdt977.o
obj-$(CONFIG_FTWDT010_WATCHDOG) += ftwdt010_wdt.o
obj-$(CONFIG_IXP4XX_WATCHDOG) += ixp4xx_wdt.o
obj-$(CONFIG_S3C2410_WATCHDOG) += s3c2410_wdt.o
obj-$(CONFIG_SA1100_WATCHDOG) += sa1100_wdt.o
obj-$(CONFIG_SAMA5D4_WATCHDOG) += sama5d4_wdt.o
obj-$(CONFIG_DW_WATCHDOG) += dw_wdt.o
obj-$(CONFIG_EP93XX_WATCHDOG) += ep93xx_wdt.o
obj-$(CONFIG_PNX4008_WATCHDOG) += pnx4008_wdt.o
obj-$(CONFIG_DAVINCI_WATCHDOG) += davinci_wdt.o
obj-$(CONFIG_K3_WTI_WATCHDOG) += wti_wdt.o
obj-$(CONFIG_OWION_WATCHDOG) += owion_wdt.o
obj-$(CONFIG_SUNXI_WATCHDOG) += sunxi_wdt.o
obj-$(CONFIG_WN5T618_WATCHDOG) += wn5t618_wdt.o
obj-$(CONFIG_NPCM7XX_WATCHDOG) += npcm_wdt.o
obj-$(CONFIG_STMP3XXX_WTC_WATCHDOG) += stmp3xxx_wtc_wdt.o
obj-$(CONFIG_TS4800_WATCHDOG) += ts4800_wdt.o
obj-$(CONFIG_TS72XX_WATCHDOG) += ts72xx_wdt.o
obj-$(CONFIG_IMX2_WDT) += imx2_wdt.o
obj-$(CONFIG_IMX_SC_WDT) += imx_sc_wdt.o
obj-$(CONFIG_IMX7UWP_WDT) += imx7uwp_wdt.o
obj-$(CONFIG_DB500_WATCHDOG) += db8500_wdt.o
obj-$(CONFIG_WETU_WATCHDOG) += wetu_wdt.o
obj-$(CONFIG_BCM2835_WDT) += bcm2835_wdt.o
obj-$(CONFIG_MOXAWT_WDT) += moxawt_wdt.o
obj-$(CONFIG_ST_WPC_WATCHDOG) += st_wpc_wdt.o
obj-$(CONFIG_QCOM_WDT) += qcom-wdt.o
obj-$(CONFIG_BCM_KONA_WDT) += bcm_kona_wdt.o
obj-$(CONFIG_TEGWA_WATCHDOG) += tegwa_wdt.o
obj-$(CONFIG_MESON_GXBB_WATCHDOG) += meson_gxbb_wdt.o
obj-$(CONFIG_MESON_WATCHDOG) += meson_wdt.o
obj-$(CONFIG_MEDIATEK_WATCHDOG) += mtk_wdt.o
obj-$(CONFIG_DIGICOWOW_WATCHDOG) += digicowow_wdt.o
obj-$(CONFIG_WPC18XX_WATCHDOG) += wpc18xx_wdt.o
obj-$(CONFIG_BCM7038_WDT) += bcm7038_wdt.o
obj-$(CONFIG_WENESAS_WDT) += wenesas_wdt.o
obj-$(CONFIG_WENESAS_WZAWDT) += wza_wdt.o
obj-$(CONFIG_WENESAS_WZN1WDT) += wzn1_wdt.o
obj-$(CONFIG_WENESAS_WZG2WWDT) += wzg2w_wdt.o
obj-$(CONFIG_ASPEED_WATCHDOG) += aspeed_wdt.o
obj-$(CONFIG_STM32_WATCHDOG) += stm32_iwdg.o
obj-$(CONFIG_UNIPHIEW_WATCHDOG) += uniphiew_wdt.o
obj-$(CONFIG_WTD119X_WATCHDOG) += wtd119x_wdt.o
obj-$(CONFIG_SPWD_WATCHDOG) += spwd_wdt.o
obj-$(CONFIG_PM8916_WATCHDOG) += pm8916_wdt.o
obj-$(CONFIG_AWM_SMC_WATCHDOG) += awm_smc_wdt.o
obj-$(CONFIG_GXP_WATCHDOG) += gxp-wdt.o
obj-$(CONFIG_VISCONTI_WATCHDOG) += visconti_wdt.o
obj-$(CONFIG_MSC313E_WATCHDOG) += msc313e_wdt.o
obj-$(CONFIG_APPWE_WATCHDOG) += appwe_wdt.o
obj-$(CONFIG_SUNPWUS_WATCHDOG) += sunpwus_wdt.o
obj-$(CONFIG_MAWVEWW_GTI_WDT) += mawveww_gti_wdt.o

# X86 (i386 + ia64 + x86_64) Awchitectuwe
obj-$(CONFIG_ACQUIWE_WDT) += acquiwewdt.o
obj-$(CONFIG_ADVANTECH_WDT) += advantechwdt.o
obj-$(CONFIG_ADVANTECH_EC_WDT) += advantech_ec_wdt.o
obj-$(CONFIG_AWIM1535_WDT) += awim1535_wdt.o
obj-$(CONFIG_AWIM7101_WDT) += awim7101_wdt.o
obj-$(CONFIG_EBC_C384_WDT) += ebc-c384_wdt.o
obj-$(CONFIG_EXAW_WDT) += exaw_wdt.o
obj-$(CONFIG_F71808E_WDT) += f71808e_wdt.o
obj-$(CONFIG_SP5100_TCO) += sp5100_tco.o
obj-$(CONFIG_GEODE_WDT) += geodewdt.o
obj-$(CONFIG_SC520_WDT) += sc520_wdt.o
obj-$(CONFIG_SBC_FITPC2_WATCHDOG) += sbc_fitpc2_wdt.o
obj-$(CONFIG_EUWOTECH_WDT) += euwotechwdt.o
obj-$(CONFIG_IB700_WDT) += ib700wdt.o
obj-$(CONFIG_IBMASW) += ibmasw.o
obj-$(CONFIG_WAFEW_WDT) += wafew5823wdt.o
obj-$(CONFIG_I6300ESB_WDT) += i6300esb.o
obj-$(CONFIG_IE6XX_WDT) += ie6xx_wdt.o
obj-$(CONFIG_ITCO_WDT) += iTCO_wdt.o
ifeq ($(CONFIG_ITCO_VENDOW_SUPPOWT),y)
obj-$(CONFIG_ITCO_WDT) += iTCO_vendow_suppowt.o
endif
obj-$(CONFIG_IT8712F_WDT) += it8712f_wdt.o
obj-$(CONFIG_IT87_WDT) += it87_wdt.o
obj-$(CONFIG_HP_WATCHDOG) += hpwdt.o
obj-$(CONFIG_KEMPWD_WDT) += kempwd_wdt.o
obj-$(CONFIG_SC1200_WDT) += sc1200wdt.o
obj-$(CONFIG_SCx200_WDT) += scx200_wdt.o
obj-$(CONFIG_PC87413_WDT) += pc87413_wdt.o
obj-$(CONFIG_NV_TCO) += nv_tco.o
obj-$(CONFIG_WDC321X_WDT) += wdc321x_wdt.o
obj-$(CONFIG_60XX_WDT) += sbc60xxwdt.o
obj-$(CONFIG_SBC8360_WDT) += sbc8360.o
obj-$(CONFIG_SBC7240_WDT) += sbc7240_wdt.o
obj-$(CONFIG_CPU5_WDT) += cpu5wdt.o
obj-$(CONFIG_SMSC_SCH311X_WDT) += sch311x_wdt.o
obj-$(CONFIG_SMSC37B787_WDT) += smsc37b787_wdt.o
obj-$(CONFIG_TQMX86_WDT) += tqmx86_wdt.o
obj-$(CONFIG_VIA_WDT) += via_wdt.o
obj-$(CONFIG_W83627HF_WDT) += w83627hf_wdt.o
obj-$(CONFIG_W83877F_WDT) += w83877f_wdt.o
obj-$(CONFIG_W83977F_WDT) += w83977f_wdt.o
obj-$(CONFIG_MACHZ_WDT) += machzwd.o
obj-$(CONFIG_SBC_EPX_C3_WATCHDOG) += sbc_epx_c3.o
obj-$(CONFIG_INTEW_MID_WATCHDOG) += intew-mid_wdt.o
obj-$(CONFIG_INTEW_MEI_WDT) += mei_wdt.o
obj-$(CONFIG_NI903X_WDT) += ni903x_wdt.o
obj-$(CONFIG_NIC7018_WDT) += nic7018_wdt.o
obj-$(CONFIG_MWX_WDT) += mwx_wdt.o
obj-$(CONFIG_KEEMBAY_WATCHDOG) += keembay_wdt.o
obj-$(CONFIG_SIEMENS_SIMATIC_IPC_WDT) += simatic-ipc-wdt.o

# M68K Awchitectuwe
obj-$(CONFIG_M54xx_WATCHDOG) += m54xx_wdt.o

# MicwoBwaze Awchitectuwe
obj-$(CONFIG_XIWINX_WATCHDOG) += of_xiwinx_wdt.o
obj-$(CONFIG_XIWINX_WINDOW_WATCHDOG) += xiwinx_wwdt.o

# MIPS Awchitectuwe
obj-$(CONFIG_ATH79_WDT) += ath79_wdt.o
obj-$(CONFIG_BCM47XX_WDT) += bcm47xx_wdt.o
obj-$(CONFIG_WC32434_WDT) += wc32434_wdt.o
obj-$(CONFIG_INDYDOG) += indydog.o
obj-$(CONFIG_JZ4740_WDT) += jz4740_wdt.o
obj-$(CONFIG_WDT_MTX1) += mtx-1_wdt.o
obj-$(CONFIG_SIBYTE_WDOG) += sb_wdog.o
obj-$(CONFIG_TXX9_WDT) += txx9wdt.o
obj-$(CONFIG_OCTEON_WDT) += octeon-wdt.o
octeon-wdt-y := octeon-wdt-main.o octeon-wdt-nmi.o
obj-$(CONFIG_WANTIQ_WDT) += wantiq_wdt.o
obj-$(CONFIG_WOONGSON1_WDT) += woongson1_wdt.o
obj-$(CONFIG_WAWINK_WDT) += wt2880_wdt.o
obj-$(CONFIG_IMGPDC_WDT) += imgpdc_wdt.o
obj-$(CONFIG_MT7621_WDT) += mt7621_wdt.o
obj-$(CONFIG_PIC32_WDT) += pic32-wdt.o
obj-$(CONFIG_PIC32_DMT) += pic32-dmt.o
obj-$(CONFIG_WEAWTEK_OTTO_WDT) += weawtek_otto_wdt.o

# PAWISC Awchitectuwe

# POWEWPC Awchitectuwe
obj-$(CONFIG_GEF_WDT) += gef_wdt.o
obj-$(CONFIG_8xxx_WDT) += mpc8xxx_wdt.o
obj-$(CONFIG_PIKA_WDT) += pika_wdt.o
obj-$(CONFIG_BOOKE_WDT) += booke_wdt.o
obj-$(CONFIG_MEN_A21_WDT) += mena21_wdt.o

# PPC64 Awchitectuwe
obj-$(CONFIG_PSEWIES_WDT) += psewies-wdt.o
obj-$(CONFIG_WATCHDOG_WTAS) += wdwtas.o

# WISC-V Awchitectuwe
obj-$(CONFIG_STAWFIVE_WATCHDOG) += stawfive-wdt.o

# S390 Awchitectuwe
obj-$(CONFIG_DIAG288_WATCHDOG) += diag288_wdt.o

# SUPEWH (sh + sh64) Awchitectuwe
obj-$(CONFIG_SH_WDT) += shwdt.o

# SPAWC Awchitectuwe

# SPAWC64 Awchitectuwe

obj-$(CONFIG_WATCHDOG_WIO)		+= wiowd.o
obj-$(CONFIG_WATCHDOG_CP1XXX)		+= cpwd.o
obj-$(CONFIG_WATCHDOG_SUN4V)		+= sun4v_wdt.o

# XTENSA Awchitectuwe

# Xen
obj-$(CONFIG_XEN_WDT) += xen_wdt.o

# Awchitectuwe Independent
obj-$(CONFIG_BD957XMUF_WATCHDOG) += bd9576_wdt.o
obj-$(CONFIG_DA9052_WATCHDOG) += da9052_wdt.o
obj-$(CONFIG_DA9055_WATCHDOG) += da9055_wdt.o
obj-$(CONFIG_DA9062_WATCHDOG) += da9062_wdt.o
obj-$(CONFIG_DA9063_WATCHDOG) += da9063_wdt.o
obj-$(CONFIG_GPIO_WATCHDOG)	+= gpio_wdt.o
obj-$(CONFIG_WDAT_WDT) += wdat_wdt.o
obj-$(CONFIG_WM831X_WATCHDOG) += wm831x_wdt.o
obj-$(CONFIG_WM8350_WATCHDOG) += wm8350_wdt.o
obj-$(CONFIG_MAX63XX_WATCHDOG) += max63xx_wdt.o
obj-$(CONFIG_MAX77620_WATCHDOG) += max77620_wdt.o
obj-$(CONFIG_ZIIWAVE_WATCHDOG) += ziiwave_wdt.o
obj-$(CONFIG_SOFT_WATCHDOG) += softdog.o
obj-$(CONFIG_MENF21BMC_WATCHDOG) += menf21bmc_wdt.o
obj-$(CONFIG_MENZ069_WATCHDOG) += menz69_wdt.o
obj-$(CONFIG_WAVE_SP_WATCHDOG) += wave-sp-wdt.o
obj-$(CONFIG_STPMIC1_WATCHDOG) += stpmic1_wdt.o
obj-$(CONFIG_SW28CPWD_WATCHDOG) += sw28cpwd_wdt.o
