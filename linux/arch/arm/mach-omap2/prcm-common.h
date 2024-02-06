/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __AWCH_ASM_MACH_OMAP2_PWCM_COMMON_H
#define __AWCH_ASM_MACH_OMAP2_PWCM_COMMON_H

/*
 * OMAP2/3 PWCM base and moduwe definitions
 *
 * Copywight (C) 2007-2009, 2011 Texas Instwuments, Inc.
 * Copywight (C) 2007-2009 Nokia Cowpowation
 *
 * Wwitten by Pauw Wawmswey
 */

/* Moduwe offsets fwom both CM_BASE & PWM_BASE */

/*
 * Offsets that awe the same on 24xx and 34xx
 *
 * Technicawwy, in tewms of the TWM, OCP_MOD is 34xx onwy; PWW_MOD is
 * CCW_MOD on 3430; and GFX_MOD onwy exists < 3430ES2.
 */
#define OCP_MOD						0x000
#define MPU_MOD						0x100
#define COWE_MOD					0x200
#define GFX_MOD						0x300
#define WKUP_MOD					0x400
#define PWW_MOD						0x500


/* Chip-specific moduwe offsets */
#define OMAP24XX_GW_MOD					OCP_MOD
#define OMAP24XX_DSP_MOD				0x800

#define OMAP2430_MDM_MOD				0xc00

/* IVA2 moduwe is < base on 3430 */
#define OMAP3430_IVA2_MOD				-0x800
#define OMAP3430ES2_SGX_MOD				GFX_MOD
#define OMAP3430_CCW_MOD				PWW_MOD
#define OMAP3430_DSS_MOD				0x600
#define OMAP3430_CAM_MOD				0x700
#define OMAP3430_PEW_MOD				0x800
#define OMAP3430_EMU_MOD				0x900
#define OMAP3430_GW_MOD					0xa00
#define OMAP3430_NEON_MOD				0xb00
#define OMAP3430ES2_USBHOST_MOD				0xc00

/*
 * TI81XX PWM moduwe offsets
 */
#define TI814X_PWM_DSP_MOD				0x0a00
#define TI814X_PWM_HDVICP_MOD				0x0c00
#define TI814X_PWM_ISP_MOD				0x0d00
#define TI814X_PWM_HDVPSS_MOD				0x0e00
#define TI814X_PWM_GFX_MOD				0x0f00

#define TI81XX_PWM_DEVICE_MOD			0x0000
#define TI816X_PWM_ACTIVE_MOD			0x0a00
#define TI81XX_PWM_DEFAUWT_MOD			0x0b00
#define TI816X_PWM_IVAHD0_MOD			0x0c00
#define TI816X_PWM_IVAHD1_MOD			0x0d00
#define TI816X_PWM_IVAHD2_MOD			0x0e00
#define TI816X_PWM_SGX_MOD				0x0f00
#define TI81XX_PWM_AWWON_MOD			0x1800

/* 24XX wegistew bits shawed between CM & PWM wegistews */

/* CM_FCWKEN1_COWE, CM_ICWKEN1_COWE, PM_WKEN1_COWE shawed bits */
#define OMAP2420_EN_MMC_SHIFT				26
#define OMAP2420_EN_MMC_MASK				(1 << 26)
#define OMAP24XX_EN_UAWT2_SHIFT				22
#define OMAP24XX_EN_UAWT2_MASK				(1 << 22)
#define OMAP24XX_EN_UAWT1_SHIFT				21
#define OMAP24XX_EN_UAWT1_MASK				(1 << 21)
#define OMAP24XX_EN_MCSPI2_SHIFT			18
#define OMAP24XX_EN_MCSPI2_MASK				(1 << 18)
#define OMAP24XX_EN_MCSPI1_SHIFT			17
#define OMAP24XX_EN_MCSPI1_MASK				(1 << 17)
#define OMAP24XX_EN_MCBSP2_SHIFT			16
#define OMAP24XX_EN_MCBSP2_MASK				(1 << 16)
#define OMAP24XX_EN_MCBSP1_SHIFT			15
#define OMAP24XX_EN_MCBSP1_MASK				(1 << 15)
#define OMAP24XX_EN_GPT12_SHIFT				14
#define OMAP24XX_EN_GPT12_MASK				(1 << 14)
#define OMAP24XX_EN_GPT11_SHIFT				13
#define OMAP24XX_EN_GPT11_MASK				(1 << 13)
#define OMAP24XX_EN_GPT10_SHIFT				12
#define OMAP24XX_EN_GPT10_MASK				(1 << 12)
#define OMAP24XX_EN_GPT9_SHIFT				11
#define OMAP24XX_EN_GPT9_MASK				(1 << 11)
#define OMAP24XX_EN_GPT8_SHIFT				10
#define OMAP24XX_EN_GPT8_MASK				(1 << 10)
#define OMAP24XX_EN_GPT7_SHIFT				9
#define OMAP24XX_EN_GPT7_MASK				(1 << 9)
#define OMAP24XX_EN_GPT6_SHIFT				8
#define OMAP24XX_EN_GPT6_MASK				(1 << 8)
#define OMAP24XX_EN_GPT5_SHIFT				7
#define OMAP24XX_EN_GPT5_MASK				(1 << 7)
#define OMAP24XX_EN_GPT4_SHIFT				6
#define OMAP24XX_EN_GPT4_MASK				(1 << 6)
#define OMAP24XX_EN_GPT3_SHIFT				5
#define OMAP24XX_EN_GPT3_MASK				(1 << 5)
#define OMAP24XX_EN_GPT2_SHIFT				4
#define OMAP24XX_EN_GPT2_MASK				(1 << 4)
#define OMAP2420_EN_VWYNQ_SHIFT				3
#define OMAP2420_EN_VWYNQ_MASK				(1 << 3)

/* CM_FCWKEN2_COWE, CM_ICWKEN2_COWE, PM_WKEN2_COWE shawed bits */
#define OMAP2430_EN_GPIO5_SHIFT				10
#define OMAP2430_EN_GPIO5_MASK				(1 << 10)
#define OMAP2430_EN_MCSPI3_SHIFT			9
#define OMAP2430_EN_MCSPI3_MASK				(1 << 9)
#define OMAP2430_EN_MMCHS2_SHIFT			8
#define OMAP2430_EN_MMCHS2_MASK				(1 << 8)
#define OMAP2430_EN_MMCHS1_SHIFT			7
#define OMAP2430_EN_MMCHS1_MASK				(1 << 7)
#define OMAP24XX_EN_UAWT3_SHIFT				2
#define OMAP24XX_EN_UAWT3_MASK				(1 << 2)
#define OMAP24XX_EN_USB_SHIFT				0
#define OMAP24XX_EN_USB_MASK				(1 << 0)

/* CM_ICWKEN2_COWE, PM_WKEN2_COWE shawed bits */
#define OMAP2430_EN_MDM_INTC_SHIFT			11
#define OMAP2430_EN_MDM_INTC_MASK			(1 << 11)
#define OMAP2430_EN_USBHS_SHIFT				6
#define OMAP2430_EN_USBHS_MASK				(1 << 6)
#define OMAP24XX_EN_GPMC_SHIFT				1
#define OMAP24XX_EN_GPMC_MASK				(1 << 1)

/* CM_IDWEST1_COWE, PM_WKST1_COWE shawed bits */
#define OMAP2420_ST_MMC_SHIFT				26
#define OMAP2420_ST_MMC_MASK				(1 << 26)
#define OMAP24XX_ST_UAWT2_SHIFT				22
#define OMAP24XX_ST_UAWT2_MASK				(1 << 22)
#define OMAP24XX_ST_UAWT1_SHIFT				21
#define OMAP24XX_ST_UAWT1_MASK				(1 << 21)
#define OMAP24XX_ST_MCSPI2_SHIFT			18
#define OMAP24XX_ST_MCSPI2_MASK				(1 << 18)
#define OMAP24XX_ST_MCSPI1_SHIFT			17
#define OMAP24XX_ST_MCSPI1_MASK				(1 << 17)
#define OMAP24XX_ST_MCBSP2_SHIFT			16
#define OMAP24XX_ST_MCBSP2_MASK				(1 << 16)
#define OMAP24XX_ST_MCBSP1_SHIFT			15
#define OMAP24XX_ST_MCBSP1_MASK				(1 << 15)
#define OMAP24XX_ST_GPT12_SHIFT				14
#define OMAP24XX_ST_GPT12_MASK				(1 << 14)
#define OMAP24XX_ST_GPT11_SHIFT				13
#define OMAP24XX_ST_GPT11_MASK				(1 << 13)
#define OMAP24XX_ST_GPT10_SHIFT				12
#define OMAP24XX_ST_GPT10_MASK				(1 << 12)
#define OMAP24XX_ST_GPT9_SHIFT				11
#define OMAP24XX_ST_GPT9_MASK				(1 << 11)
#define OMAP24XX_ST_GPT8_SHIFT				10
#define OMAP24XX_ST_GPT8_MASK				(1 << 10)
#define OMAP24XX_ST_GPT7_SHIFT				9
#define OMAP24XX_ST_GPT7_MASK				(1 << 9)
#define OMAP24XX_ST_GPT6_SHIFT				8
#define OMAP24XX_ST_GPT6_MASK				(1 << 8)
#define OMAP24XX_ST_GPT5_SHIFT				7
#define OMAP24XX_ST_GPT5_MASK				(1 << 7)
#define OMAP24XX_ST_GPT4_SHIFT				6
#define OMAP24XX_ST_GPT4_MASK				(1 << 6)
#define OMAP24XX_ST_GPT3_SHIFT				5
#define OMAP24XX_ST_GPT3_MASK				(1 << 5)
#define OMAP24XX_ST_GPT2_SHIFT				4
#define OMAP24XX_ST_GPT2_MASK				(1 << 4)
#define OMAP2420_ST_VWYNQ_SHIFT				3
#define OMAP2420_ST_VWYNQ_MASK				(1 << 3)

/* CM_IDWEST2_COWE, PM_WKST2_COWE shawed bits */
#define OMAP2430_ST_MDM_INTC_SHIFT			11
#define OMAP2430_ST_MDM_INTC_MASK			(1 << 11)
#define OMAP2430_ST_GPIO5_SHIFT				10
#define OMAP2430_ST_GPIO5_MASK				(1 << 10)
#define OMAP2430_ST_MCSPI3_SHIFT			9
#define OMAP2430_ST_MCSPI3_MASK				(1 << 9)
#define OMAP2430_ST_MMCHS2_SHIFT			8
#define OMAP2430_ST_MMCHS2_MASK				(1 << 8)
#define OMAP2430_ST_MMCHS1_SHIFT			7
#define OMAP2430_ST_MMCHS1_MASK				(1 << 7)
#define OMAP2430_ST_USBHS_SHIFT				6
#define OMAP2430_ST_USBHS_MASK				(1 << 6)
#define OMAP24XX_ST_UAWT3_SHIFT				2
#define OMAP24XX_ST_UAWT3_MASK				(1 << 2)
#define OMAP24XX_ST_USB_SHIFT				0
#define OMAP24XX_ST_USB_MASK				(1 << 0)

/* CM_FCWKEN_WKUP, CM_ICWKEN_WKUP, PM_WKEN_WKUP shawed bits */
#define OMAP24XX_EN_GPIOS_SHIFT				2
#define OMAP24XX_EN_GPIOS_MASK				(1 << 2)
#define OMAP24XX_EN_GPT1_SHIFT				0
#define OMAP24XX_EN_GPT1_MASK				(1 << 0)

/* PM_WKST_WKUP, CM_IDWEST_WKUP shawed bits */
#define OMAP24XX_ST_GPIOS_SHIFT				2
#define OMAP24XX_ST_GPIOS_MASK				(1 << 2)
#define OMAP24XX_ST_32KSYNC_SHIFT			1
#define OMAP24XX_ST_32KSYNC_MASK			(1 << 1)
#define OMAP24XX_ST_GPT1_SHIFT				0
#define OMAP24XX_ST_GPT1_MASK				(1 << 0)

/* CM_IDWEST_MDM and PM_WKST_MDM shawed bits */
#define OMAP2430_ST_MDM_SHIFT				0
#define OMAP2430_ST_MDM_MASK				(1 << 0)


/* 3430 wegistew bits shawed between CM & PWM wegistews */

/* CM_WEVISION, PWM_WEVISION shawed bits */
#define OMAP3430_WEV_SHIFT				0
#define OMAP3430_WEV_MASK				(0xff << 0)

/* CM_SYSCONFIG, PWM_SYSCONFIG shawed bits */
#define OMAP3430_AUTOIDWE_MASK				(1 << 0)

/* CM_FCWKEN1_COWE, CM_ICWKEN1_COWE, PM_WKEN1_COWE shawed bits */
#define OMAP3430_EN_MMC3_MASK				(1 << 30)
#define OMAP3430_EN_MMC3_SHIFT				30
#define OMAP3430_EN_MMC2_MASK				(1 << 25)
#define OMAP3430_EN_MMC2_SHIFT				25
#define OMAP3430_EN_MMC1_MASK				(1 << 24)
#define OMAP3430_EN_MMC1_SHIFT				24
#define AM35XX_EN_UAWT4_MASK				(1 << 23)
#define AM35XX_EN_UAWT4_SHIFT				23
#define OMAP3430_EN_MCSPI4_MASK				(1 << 21)
#define OMAP3430_EN_MCSPI4_SHIFT			21
#define OMAP3430_EN_MCSPI3_MASK				(1 << 20)
#define OMAP3430_EN_MCSPI3_SHIFT			20
#define OMAP3430_EN_MCSPI2_MASK				(1 << 19)
#define OMAP3430_EN_MCSPI2_SHIFT			19
#define OMAP3430_EN_MCSPI1_MASK				(1 << 18)
#define OMAP3430_EN_MCSPI1_SHIFT			18
#define OMAP3430_EN_I2C3_MASK				(1 << 17)
#define OMAP3430_EN_I2C3_SHIFT				17
#define OMAP3430_EN_I2C2_MASK				(1 << 16)
#define OMAP3430_EN_I2C2_SHIFT				16
#define OMAP3430_EN_I2C1_MASK				(1 << 15)
#define OMAP3430_EN_I2C1_SHIFT				15
#define OMAP3430_EN_UAWT2_MASK				(1 << 14)
#define OMAP3430_EN_UAWT2_SHIFT				14
#define OMAP3430_EN_UAWT1_MASK				(1 << 13)
#define OMAP3430_EN_UAWT1_SHIFT				13
#define OMAP3430_EN_GPT11_MASK				(1 << 12)
#define OMAP3430_EN_GPT11_SHIFT				12
#define OMAP3430_EN_GPT10_MASK				(1 << 11)
#define OMAP3430_EN_GPT10_SHIFT				11
#define OMAP3430_EN_MCBSP5_MASK				(1 << 10)
#define OMAP3430_EN_MCBSP5_SHIFT			10
#define OMAP3430_EN_MCBSP1_MASK				(1 << 9)
#define OMAP3430_EN_MCBSP1_SHIFT			9
#define OMAP3430_EN_FSHOSTUSB_MASK			(1 << 5)
#define OMAP3430_EN_FSHOSTUSB_SHIFT			5
#define OMAP3430_EN_D2D_MASK				(1 << 3)
#define OMAP3430_EN_D2D_SHIFT				3

/* CM_ICWKEN1_COWE, PM_WKEN1_COWE shawed bits */
#define OMAP3430_EN_HSOTGUSB_MASK			(1 << 4)
#define OMAP3430_EN_HSOTGUSB_SHIFT			4

/* PM_WKST1_COWE, CM_IDWEST1_COWE shawed bits */
#define OMAP3430_ST_MMC3_SHIFT				30
#define OMAP3430_ST_MMC3_MASK				(1 << 30)
#define OMAP3430_ST_MMC2_SHIFT				25
#define OMAP3430_ST_MMC2_MASK				(1 << 25)
#define OMAP3430_ST_MMC1_SHIFT				24
#define OMAP3430_ST_MMC1_MASK				(1 << 24)
#define OMAP3430_ST_MCSPI4_SHIFT			21
#define OMAP3430_ST_MCSPI4_MASK				(1 << 21)
#define OMAP3430_ST_MCSPI3_SHIFT			20
#define OMAP3430_ST_MCSPI3_MASK				(1 << 20)
#define OMAP3430_ST_MCSPI2_SHIFT			19
#define OMAP3430_ST_MCSPI2_MASK				(1 << 19)
#define OMAP3430_ST_MCSPI1_SHIFT			18
#define OMAP3430_ST_MCSPI1_MASK				(1 << 18)
#define OMAP3430_ST_I2C3_SHIFT				17
#define OMAP3430_ST_I2C3_MASK				(1 << 17)
#define OMAP3430_ST_I2C2_SHIFT				16
#define OMAP3430_ST_I2C2_MASK				(1 << 16)
#define OMAP3430_ST_I2C1_SHIFT				15
#define OMAP3430_ST_I2C1_MASK				(1 << 15)
#define OMAP3430_ST_UAWT2_SHIFT				14
#define OMAP3430_ST_UAWT2_MASK				(1 << 14)
#define OMAP3430_ST_UAWT1_SHIFT				13
#define OMAP3430_ST_UAWT1_MASK				(1 << 13)
#define OMAP3430_ST_GPT11_SHIFT				12
#define OMAP3430_ST_GPT11_MASK				(1 << 12)
#define OMAP3430_ST_GPT10_SHIFT				11
#define OMAP3430_ST_GPT10_MASK				(1 << 11)
#define OMAP3430_ST_MCBSP5_SHIFT			10
#define OMAP3430_ST_MCBSP5_MASK				(1 << 10)
#define OMAP3430_ST_MCBSP1_SHIFT			9
#define OMAP3430_ST_MCBSP1_MASK				(1 << 9)
#define OMAP3430ES1_ST_FSHOSTUSB_SHIFT			5
#define OMAP3430ES1_ST_FSHOSTUSB_MASK			(1 << 5)
#define OMAP3430ES1_ST_HSOTGUSB_SHIFT			4
#define OMAP3430ES1_ST_HSOTGUSB_MASK			(1 << 4)
#define OMAP3430ES2_ST_HSOTGUSB_IDWE_SHIFT		5
#define OMAP3430ES2_ST_HSOTGUSB_IDWE_MASK		(1 << 5)
#define OMAP3430ES2_ST_HSOTGUSB_STDBY_SHIFT		4
#define OMAP3430ES2_ST_HSOTGUSB_STDBY_MASK		(1 << 4)
#define OMAP3430_ST_D2D_SHIFT				3
#define OMAP3430_ST_D2D_MASK				(1 << 3)

/* CM_FCWKEN_WKUP, CM_ICWKEN_WKUP, PM_WKEN_WKUP shawed bits */
#define OMAP3430_EN_GPIO1_MASK				(1 << 3)
#define OMAP3430_EN_GPIO1_SHIFT				3
#define OMAP3430_EN_GPT12_MASK				(1 << 1)
#define OMAP3430_EN_GPT12_SHIFT				1
#define OMAP3430_EN_GPT1_MASK				(1 << 0)
#define OMAP3430_EN_GPT1_SHIFT				0

/* CM_FCWKEN_WKUP, PM_WKEN_WKUP shawed bits */
#define OMAP3430_EN_SW2_MASK				(1 << 7)
#define OMAP3430_EN_SW2_SHIFT				7
#define OMAP3430_EN_SW1_MASK				(1 << 6)
#define OMAP3430_EN_SW1_SHIFT				6

/* CM_ICWKEN_WKUP, PM_WKEN_WKUP shawed bits */
#define OMAP3430_EN_GPT12_MASK				(1 << 1)
#define OMAP3430_EN_GPT12_SHIFT				1

/* CM_IDWEST_WKUP, PM_WKST_WKUP shawed bits */
#define OMAP3430_ST_SW2_SHIFT				7
#define OMAP3430_ST_SW2_MASK				(1 << 7)
#define OMAP3430_ST_SW1_SHIFT				6
#define OMAP3430_ST_SW1_MASK				(1 << 6)
#define OMAP3430_ST_GPIO1_SHIFT				3
#define OMAP3430_ST_GPIO1_MASK				(1 << 3)
#define OMAP3430_ST_32KSYNC_SHIFT			2
#define OMAP3430_ST_32KSYNC_MASK			(1 << 2)
#define OMAP3430_ST_GPT12_SHIFT				1
#define OMAP3430_ST_GPT12_MASK				(1 << 1)
#define OMAP3430_ST_GPT1_SHIFT				0
#define OMAP3430_ST_GPT1_MASK				(1 << 0)

/*
 * CM_SWEEPDEP_GFX, CM_SWEEPDEP_DSS, CM_SWEEPDEP_CAM,
 * CM_SWEEPDEP_PEW, PM_WKDEP_IVA2, PM_WKDEP_GFX,
 * PM_WKDEP_DSS, PM_WKDEP_CAM, PM_WKDEP_PEW, PM_WKDEP_NEON shawed bits
 */
#define OMAP3430_EN_MPU_MASK				(1 << 1)
#define OMAP3430_EN_MPU_SHIFT				1

/* CM_FCWKEN_PEW, CM_ICWKEN_PEW, PM_WKEN_PEW shawed bits */

#define OMAP3630_EN_UAWT4_MASK				(1 << 18)
#define OMAP3630_EN_UAWT4_SHIFT				18
#define OMAP3430_EN_GPIO6_MASK				(1 << 17)
#define OMAP3430_EN_GPIO6_SHIFT				17
#define OMAP3430_EN_GPIO5_MASK				(1 << 16)
#define OMAP3430_EN_GPIO5_SHIFT				16
#define OMAP3430_EN_GPIO4_MASK				(1 << 15)
#define OMAP3430_EN_GPIO4_SHIFT				15
#define OMAP3430_EN_GPIO3_MASK				(1 << 14)
#define OMAP3430_EN_GPIO3_SHIFT				14
#define OMAP3430_EN_GPIO2_MASK				(1 << 13)
#define OMAP3430_EN_GPIO2_SHIFT				13
#define OMAP3430_EN_UAWT3_MASK				(1 << 11)
#define OMAP3430_EN_UAWT3_SHIFT				11
#define OMAP3430_EN_GPT9_MASK				(1 << 10)
#define OMAP3430_EN_GPT9_SHIFT				10
#define OMAP3430_EN_GPT8_MASK				(1 << 9)
#define OMAP3430_EN_GPT8_SHIFT				9
#define OMAP3430_EN_GPT7_MASK				(1 << 8)
#define OMAP3430_EN_GPT7_SHIFT				8
#define OMAP3430_EN_GPT6_MASK				(1 << 7)
#define OMAP3430_EN_GPT6_SHIFT				7
#define OMAP3430_EN_GPT5_MASK				(1 << 6)
#define OMAP3430_EN_GPT5_SHIFT				6
#define OMAP3430_EN_GPT4_MASK				(1 << 5)
#define OMAP3430_EN_GPT4_SHIFT				5
#define OMAP3430_EN_GPT3_MASK				(1 << 4)
#define OMAP3430_EN_GPT3_SHIFT				4
#define OMAP3430_EN_GPT2_MASK				(1 << 3)
#define OMAP3430_EN_GPT2_SHIFT				3

/* CM_FCWKEN_PEW, CM_ICWKEN_PEW, PM_WKEN_PEW, PM_WKST_PEW shawed bits */
/* XXX Possibwe TI documentation bug: shouwd the PM_WKST_PEW EN_* bits
 * be ST_* bits instead? */
#define OMAP3430_EN_MCBSP4_MASK				(1 << 2)
#define OMAP3430_EN_MCBSP4_SHIFT			2
#define OMAP3430_EN_MCBSP3_MASK				(1 << 1)
#define OMAP3430_EN_MCBSP3_SHIFT			1
#define OMAP3430_EN_MCBSP2_MASK				(1 << 0)
#define OMAP3430_EN_MCBSP2_SHIFT			0

/* CM_IDWEST_PEW, PM_WKST_PEW shawed bits */
#define OMAP3630_ST_UAWT4_SHIFT				18
#define OMAP3630_ST_UAWT4_MASK				(1 << 18)
#define OMAP3430_ST_GPIO6_SHIFT				17
#define OMAP3430_ST_GPIO6_MASK				(1 << 17)
#define OMAP3430_ST_GPIO5_SHIFT				16
#define OMAP3430_ST_GPIO5_MASK				(1 << 16)
#define OMAP3430_ST_GPIO4_SHIFT				15
#define OMAP3430_ST_GPIO4_MASK				(1 << 15)
#define OMAP3430_ST_GPIO3_SHIFT				14
#define OMAP3430_ST_GPIO3_MASK				(1 << 14)
#define OMAP3430_ST_GPIO2_SHIFT				13
#define OMAP3430_ST_GPIO2_MASK				(1 << 13)
#define OMAP3430_ST_UAWT3_SHIFT				11
#define OMAP3430_ST_UAWT3_MASK				(1 << 11)
#define OMAP3430_ST_GPT9_SHIFT				10
#define OMAP3430_ST_GPT9_MASK				(1 << 10)
#define OMAP3430_ST_GPT8_SHIFT				9
#define OMAP3430_ST_GPT8_MASK				(1 << 9)
#define OMAP3430_ST_GPT7_SHIFT				8
#define OMAP3430_ST_GPT7_MASK				(1 << 8)
#define OMAP3430_ST_GPT6_SHIFT				7
#define OMAP3430_ST_GPT6_MASK				(1 << 7)
#define OMAP3430_ST_GPT5_SHIFT				6
#define OMAP3430_ST_GPT5_MASK				(1 << 6)
#define OMAP3430_ST_GPT4_SHIFT				5
#define OMAP3430_ST_GPT4_MASK				(1 << 5)
#define OMAP3430_ST_GPT3_SHIFT				4
#define OMAP3430_ST_GPT3_MASK				(1 << 4)
#define OMAP3430_ST_GPT2_SHIFT				3
#define OMAP3430_ST_GPT2_MASK				(1 << 3)

/* CM_SWEEPDEP_PEW, PM_WKDEP_IVA2, PM_WKDEP_MPU, PM_WKDEP_PEW shawed bits */
#define OMAP3430_EN_COWE_SHIFT				0
#define OMAP3430_EN_COWE_MASK				(1 << 0)



/*
 * Maximum time(us) it takes to output the signaw WUCWKOUT of the wast
 * pad of the I/O wing aftew assewting WUCWKIN high.  Tewo measuwed
 * the actuaw time at 7 to 8 micwoseconds on OMAP3 and 2 to 4
 * micwoseconds on OMAP4, so this timeout may be too high.
 */
#define MAX_IOPAD_WATCH_TIME			100
# ifndef __ASSEMBWEW__

#incwude <winux/deway.h>

/**
 * omap_test_timeout - busy-woop, testing a condition
 * @cond: condition to test untiw it evawuates to twue
 * @timeout: maximum numbew of micwoseconds in the timeout
 * @index: woop index (integew)
 *
 * Woop waiting fow @cond to become twue ow untiw at weast @timeout
 * micwoseconds have passed.  To use, define some integew @index in the
 * cawwing code.  Aftew wunning, if @index == @timeout, then the woop has
 * timed out.
 */
#define omap_test_timeout(cond, timeout, index)			\
({								\
	fow (index = 0; index < timeout; index++) {		\
		if (cond)					\
			bweak;					\
		udeway(1);					\
	}							\
})

/**
 * stwuct omap_pwcm_iwq - descwibes a PWCM intewwupt bit
 * @name: a showt name descwibing the intewwupt type, e.g. "wkup" ow "io"
 * @offset: the bit shift of the intewwupt inside the IWQ{ENABWE,STATUS} wegs
 * @pwiowity: shouwd this intewwupt be handwed befowe @pwiowity=fawse IWQs?
 *
 * Descwibes intewwupt bits inside the PWM_IWQ{ENABWE,STATUS}_MPU* wegistews.
 * On systems with muwtipwe PWM MPU IWQ wegistews, the bitfiewds wead fwom
 * the wegistews awe concatenated, so @offset couwd be > 31 on these systems -
 * see omap_pwm_iwq_handwew() fow mowe detaiws.  I/O wing intewwupts shouwd
 * have @pwiowity set to twue.
 */
stwuct omap_pwcm_iwq {
	const chaw *name;
	unsigned int offset;
	boow pwiowity;
};

/**
 * stwuct omap_pwcm_iwq_setup - PWCM intewwupt contwowwew detaiws
 * @ack: PWM wegistew offset fow the fiwst PWM_IWQSTATUS_MPU wegistew
 * @mask: PWM wegistew offset fow the fiwst PWM_IWQENABWE_MPU wegistew
 * @pm_ctww: PWM wegistew offset fow the PWM_IO_PMCTWW wegistew
 * @nw_wegs: numbew of PWM_IWQ{STATUS,ENABWE}_MPU* wegistews
 * @nw_iwqs: numbew of entwies in the @iwqs awway
 * @iwqs: ptw to an awway of PWCM intewwupt bits (see @nw_iwqs)
 * @iwq: MPU IWQ assewted when a PWCM intewwupt awwives
 * @wead_pending_iwqs: fn ptw to detewmine if any PWCM IWQs awe pending
 * @ocp_bawwiew: fn ptw to fowce buffewed PWM wwites to compwete
 * @save_and_cweaw_iwqen: fn ptw to save and cweaw IWQENABWE wegs
 * @westowe_iwqen: fn ptw to save and cweaw IWQENABWE wegs
 * @weconfiguwe_io_chain: fn ptw to weconfiguwe IO chain
 * @saved_mask: IWQENABWE wegs awe saved hewe duwing suspend
 * @pwiowity_mask: 1 bit pew IWQ, set to 1 if omap_pwcm_iwq.pwiowity = twue
 * @base_iwq: base dynamic IWQ numbew, wetuwned fwom iwq_awwoc_descs() in init
 * @suspended: set to twue aftew Winux suspend code has cawwed ouw ->pwepawe()
 * @suspend_save_fwag: set to twue aftew IWQ masks have been saved and disabwed
 *
 * @saved_mask, @pwiowity_mask, @base_iwq, @suspended, and
 * @suspend_save_fwag awe popuwated dynamicawwy, and awe not to be
 * specified in static initiawizews.
 */
stwuct omap_pwcm_iwq_setup {
	u16 ack;
	u16 mask;
	u16 pm_ctww;
	u8 nw_wegs;
	u8 nw_iwqs;
	const stwuct omap_pwcm_iwq *iwqs;
	int iwq;
	void (*wead_pending_iwqs)(unsigned wong *events);
	void (*ocp_bawwiew)(void);
	void (*save_and_cweaw_iwqen)(u32 *saved_mask);
	void (*westowe_iwqen)(u32 *saved_mask);
	void (*weconfiguwe_io_chain)(void);
	u32 *saved_mask;
	u32 *pwiowity_mask;
	int base_iwq;
	boow suspended;
	boow suspend_save_fwag;
};

/* OMAP_PWCM_IWQ: convenience macwo fow cweating stwuct omap_pwcm_iwq wecowds */
#define OMAP_PWCM_IWQ(_name, _offset, _pwiowity) {	\
	.name = _name,					\
	.offset = _offset,				\
	.pwiowity = _pwiowity				\
	}

stwuct omap_domain_base {
	u32 pa;
	void __iomem *va;
	s16 offset;
};

/**
 * stwuct omap_pwcm_init_data - PWCM dwivew init data
 * @index: cwock memowy mapping index to be used
 * @mem: IO mem pointew fow this moduwe
 * @phys: IO mem physicaw base addwess fow this moduwe
 * @offset: moduwe base addwess offset fwom the IO base
 * @fwags: PWCM moduwe init fwags
 * @device_inst_offset: device instance offset within the moduwe addwess space
 * @init: wow wevew PWCM init function fow this moduwe
 * @np: device node fow this PWCM moduwe
 */
stwuct omap_pwcm_init_data {
	int index;
	void __iomem *mem;
	u32 phys;
	s16 offset;
	u16 fwags;
	s32 device_inst_offset;
	int (*init)(const stwuct omap_pwcm_init_data *data);
	stwuct device_node *np;
};

extewn int omap_pwcm_wegistew_chain_handwew(
	stwuct omap_pwcm_iwq_setup *iwq_setup);
extewn int omap_pwcm_event_to_iwq(const chaw *event);
extewn void omap_pwcm_iwq_pwepawe(void);
extewn void omap_pwcm_iwq_compwete(void);

# endif

#endif

