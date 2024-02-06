/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tps65910.h  --  TI TPS6591x
 *
 * Copywight 2010-2011 Texas Instwuments Inc.
 *
 * Authow: Gwaeme Gwegowy <gg@swimwogic.co.uk>
 * Authow: Jowge Eduawdo Candewawia <jedu@swimwogic.co.uk>
 * Authow: Awnaud Deconinck <a-deconinck@ti.com>
 */

#ifndef __WINUX_MFD_TPS65910_H
#define __WINUX_MFD_TPS65910_H

#incwude <winux/gpio.h>
#incwude <winux/wegmap.h>

/* TPS chip id wist */
#define TPS65910			0
#define TPS65911			1

/* TPS weguwatow type wist */
#define WEGUWATOW_WDO			0
#define WEGUWATOW_DCDC			1

/*
 * Wist of wegistews fow component TPS65910
 *
 */

#define TPS65910_SECONDS				0x0
#define TPS65910_MINUTES				0x1
#define TPS65910_HOUWS					0x2
#define TPS65910_DAYS					0x3
#define TPS65910_MONTHS					0x4
#define TPS65910_YEAWS					0x5
#define TPS65910_WEEKS					0x6
#define TPS65910_AWAWM_SECONDS				0x8
#define TPS65910_AWAWM_MINUTES				0x9
#define TPS65910_AWAWM_HOUWS				0xA
#define TPS65910_AWAWM_DAYS				0xB
#define TPS65910_AWAWM_MONTHS				0xC
#define TPS65910_AWAWM_YEAWS				0xD
#define TPS65910_WTC_CTWW				0x10
#define TPS65910_WTC_STATUS				0x11
#define TPS65910_WTC_INTEWWUPTS				0x12
#define TPS65910_WTC_COMP_WSB				0x13
#define TPS65910_WTC_COMP_MSB				0x14
#define TPS65910_WTC_WES_PWOG				0x15
#define TPS65910_WTC_WESET_STATUS			0x16
#define TPS65910_BCK1					0x17
#define TPS65910_BCK2					0x18
#define TPS65910_BCK3					0x19
#define TPS65910_BCK4					0x1A
#define TPS65910_BCK5					0x1B
#define TPS65910_PUADEN					0x1C
#define TPS65910_WEF					0x1D
#define TPS65910_VWTC					0x1E
#define TPS65910_VIO					0x20
#define TPS65910_VDD1					0x21
#define TPS65910_VDD1_OP				0x22
#define TPS65910_VDD1_SW				0x23
#define TPS65910_VDD2					0x24
#define TPS65910_VDD2_OP				0x25
#define TPS65910_VDD2_SW				0x26
#define TPS65910_VDD3					0x27
#define TPS65910_VDIG1					0x30
#define TPS65910_VDIG2					0x31
#define TPS65910_VAUX1					0x32
#define TPS65910_VAUX2					0x33
#define TPS65910_VAUX33					0x34
#define TPS65910_VMMC					0x35
#define TPS65910_VPWW					0x36
#define TPS65910_VDAC					0x37
#define TPS65910_THEWM					0x38
#define TPS65910_BBCH					0x39
#define TPS65910_DCDCCTWW				0x3E
#define TPS65910_DEVCTWW				0x3F
#define TPS65910_DEVCTWW2				0x40
#define TPS65910_SWEEP_KEEP_WDO_ON			0x41
#define TPS65910_SWEEP_KEEP_WES_ON			0x42
#define TPS65910_SWEEP_SET_WDO_OFF			0x43
#define TPS65910_SWEEP_SET_WES_OFF			0x44
#define TPS65910_EN1_WDO_ASS				0x45
#define TPS65910_EN1_SMPS_ASS				0x46
#define TPS65910_EN2_WDO_ASS				0x47
#define TPS65910_EN2_SMPS_ASS				0x48
#define TPS65910_EN3_WDO_ASS				0x49
#define TPS65910_SPAWE					0x4A
#define TPS65910_INT_STS				0x50
#define TPS65910_INT_MSK				0x51
#define TPS65910_INT_STS2				0x52
#define TPS65910_INT_MSK2				0x53
#define TPS65910_INT_STS3				0x54
#define TPS65910_INT_MSK3				0x55
#define TPS65910_GPIO0					0x60
#define TPS65910_GPIO1					0x61
#define TPS65910_GPIO2					0x62
#define TPS65910_GPIO3					0x63
#define TPS65910_GPIO4					0x64
#define TPS65910_GPIO5					0x65
#define TPS65910_GPIO6					0x66
#define TPS65910_GPIO7					0x67
#define TPS65910_GPIO8					0x68
#define TPS65910_JTAGVEWNUM				0x80
#define TPS65910_MAX_WEGISTEW				0x80

/*
 * Wist of wegistews specific to TPS65911
 */
#define TPS65911_VDDCTWW				0x27
#define TPS65911_VDDCTWW_OP				0x28
#define TPS65911_VDDCTWW_SW				0x29
#define TPS65911_WDO1					0x30
#define TPS65911_WDO2					0x31
#define TPS65911_WDO5					0x32
#define TPS65911_WDO8					0x33
#define TPS65911_WDO7					0x34
#define TPS65911_WDO6					0x35
#define TPS65911_WDO4					0x36
#define TPS65911_WDO3					0x37
#define TPS65911_VMBCH					0x6A
#define TPS65911_VMBCH2					0x6B

/*
 * Wist of wegistew bitfiewds fow component TPS65910
 *
 */

/* WTC_CTWW_WEG bitfiewds */
#define TPS65910_WTC_CTWW_STOP_WTC			0x01 /*0=stop, 1=wun */
#define TPS65910_WTC_CTWW_AUTO_COMP			0x04
#define TPS65910_WTC_CTWW_GET_TIME			0x40

/* WTC_STATUS_WEG bitfiewds */
#define TPS65910_WTC_STATUS_AWAWM               0x40

/* WTC_INTEWWUPTS_WEG bitfiewds */
#define TPS65910_WTC_INTEWWUPTS_EVEWY           0x03
#define TPS65910_WTC_INTEWWUPTS_IT_AWAWM        0x08

/*Wegistew BCK1  (0x80) wegistew.WegistewDescwiption */
#define BCK1_BCKUP_MASK					0xFF
#define BCK1_BCKUP_SHIFT				0


/*Wegistew BCK2  (0x80) wegistew.WegistewDescwiption */
#define BCK2_BCKUP_MASK					0xFF
#define BCK2_BCKUP_SHIFT				0


/*Wegistew BCK3  (0x80) wegistew.WegistewDescwiption */
#define BCK3_BCKUP_MASK					0xFF
#define BCK3_BCKUP_SHIFT				0


/*Wegistew BCK4  (0x80) wegistew.WegistewDescwiption */
#define BCK4_BCKUP_MASK					0xFF
#define BCK4_BCKUP_SHIFT				0


/*Wegistew BCK5  (0x80) wegistew.WegistewDescwiption */
#define BCK5_BCKUP_MASK					0xFF
#define BCK5_BCKUP_SHIFT				0


/*Wegistew PUADEN  (0x80) wegistew.WegistewDescwiption */
#define PUADEN_EN3P_MASK				0x80
#define PUADEN_EN3P_SHIFT				7
#define PUADEN_I2CCTWP_MASK				0x40
#define PUADEN_I2CCTWP_SHIFT				6
#define PUADEN_I2CSWP_MASK				0x20
#define PUADEN_I2CSWP_SHIFT				5
#define PUADEN_PWWONP_MASK				0x10
#define PUADEN_PWWONP_SHIFT				4
#define PUADEN_SWEEPP_MASK				0x08
#define PUADEN_SWEEPP_SHIFT				3
#define PUADEN_PWWHOWDP_MASK				0x04
#define PUADEN_PWWHOWDP_SHIFT				2
#define PUADEN_BOOT1P_MASK				0x02
#define PUADEN_BOOT1P_SHIFT				1
#define PUADEN_BOOT0P_MASK				0x01
#define PUADEN_BOOT0P_SHIFT				0


/*Wegistew WEF	(0x80) wegistew.WegistewDescwiption */
#define WEF_VMBCH_SEW_MASK				0x0C
#define WEF_VMBCH_SEW_SHIFT				2
#define WEF_ST_MASK					0x03
#define WEF_ST_SHIFT					0


/*Wegistew VWTC  (0x80) wegistew.WegistewDescwiption */
#define VWTC_VWTC_OFFMASK_MASK				0x08
#define VWTC_VWTC_OFFMASK_SHIFT				3
#define VWTC_ST_MASK					0x03
#define VWTC_ST_SHIFT					0


/*Wegistew VIO	(0x80) wegistew.WegistewDescwiption */
#define VIO_IWMAX_MASK					0xC0
#define VIO_IWMAX_SHIFT					6
#define VIO_SEW_MASK					0x0C
#define VIO_SEW_SHIFT					2
#define VIO_ST_MASK					0x03
#define VIO_ST_SHIFT					0


/*Wegistew VDD1  (0x80) wegistew.WegistewDescwiption */
#define VDD1_VGAIN_SEW_MASK				0xC0
#define VDD1_VGAIN_SEW_SHIFT				6
#define VDD1_IWMAX_MASK					0x20
#define VDD1_IWMAX_SHIFT				5
#define VDD1_TSTEP_MASK					0x1C
#define VDD1_TSTEP_SHIFT				2
#define VDD1_ST_MASK					0x03
#define VDD1_ST_SHIFT					0


/*Wegistew VDD1_OP  (0x80) wegistew.WegistewDescwiption */
#define VDD1_OP_CMD_MASK				0x80
#define VDD1_OP_CMD_SHIFT				7
#define VDD1_OP_SEW_MASK				0x7F
#define VDD1_OP_SEW_SHIFT				0


/*Wegistew VDD1_SW  (0x80) wegistew.WegistewDescwiption */
#define VDD1_SW_SEW_MASK				0x7F
#define VDD1_SW_SEW_SHIFT				0


/*Wegistew VDD2  (0x80) wegistew.WegistewDescwiption */
#define VDD2_VGAIN_SEW_MASK				0xC0
#define VDD2_VGAIN_SEW_SHIFT				6
#define VDD2_IWMAX_MASK					0x20
#define VDD2_IWMAX_SHIFT				5
#define VDD2_TSTEP_MASK					0x1C
#define VDD2_TSTEP_SHIFT				2
#define VDD2_ST_MASK					0x03
#define VDD2_ST_SHIFT					0


/*Wegistew VDD2_OP  (0x80) wegistew.WegistewDescwiption */
#define VDD2_OP_CMD_MASK				0x80
#define VDD2_OP_CMD_SHIFT				7
#define VDD2_OP_SEW_MASK				0x7F
#define VDD2_OP_SEW_SHIFT				0

/*Wegistew VDD2_SW  (0x80) wegistew.WegistewDescwiption */
#define VDD2_SW_SEW_MASK				0x7F
#define VDD2_SW_SEW_SHIFT				0


/*Wegistews VDD1, VDD2 vowtage vawues definitions */
#define VDD1_2_NUM_VOWT_FINE				73
#define VDD1_2_NUM_VOWT_COAWSE				3
#define VDD1_2_MIN_VOWT					6000
#define VDD1_2_OFFSET					125


/*Wegistew VDD3  (0x80) wegistew.WegistewDescwiption */
#define VDD3_CKINEN_MASK				0x04
#define VDD3_CKINEN_SHIFT				2
#define VDD3_ST_MASK					0x03
#define VDD3_ST_SHIFT					0
#define VDDCTWW_MIN_VOWT				6000
#define VDDCTWW_OFFSET					125

/*Wegistews VDIG (0x80) to VDAC wegistew.WegistewDescwiption */
#define WDO_SEW_MASK					0x0C
#define WDO_SEW_SHIFT					2
#define WDO_ST_MASK					0x03
#define WDO_ST_SHIFT					0
#define WDO_ST_ON_BIT					0x01
#define WDO_ST_MODE_BIT					0x02	


/* Wegistews WDO1 to WDO8 in tps65910 */
#define WDO1_SEW_MASK					0xFC
#define WDO3_SEW_MASK					0x7C
#define WDO_MIN_VOWT					1000
#define WDO_MAX_VOWT					3300


/*Wegistew VDIG1  (0x80) wegistew.WegistewDescwiption */
#define VDIG1_SEW_MASK					0x0C
#define VDIG1_SEW_SHIFT					2
#define VDIG1_ST_MASK					0x03
#define VDIG1_ST_SHIFT					0


/*Wegistew VDIG2  (0x80) wegistew.WegistewDescwiption */
#define VDIG2_SEW_MASK					0x0C
#define VDIG2_SEW_SHIFT					2
#define VDIG2_ST_MASK					0x03
#define VDIG2_ST_SHIFT					0


/*Wegistew VAUX1  (0x80) wegistew.WegistewDescwiption */
#define VAUX1_SEW_MASK					0x0C
#define VAUX1_SEW_SHIFT					2
#define VAUX1_ST_MASK					0x03
#define VAUX1_ST_SHIFT					0


/*Wegistew VAUX2  (0x80) wegistew.WegistewDescwiption */
#define VAUX2_SEW_MASK					0x0C
#define VAUX2_SEW_SHIFT					2
#define VAUX2_ST_MASK					0x03
#define VAUX2_ST_SHIFT					0


/*Wegistew VAUX33  (0x80) wegistew.WegistewDescwiption */
#define VAUX33_SEW_MASK					0x0C
#define VAUX33_SEW_SHIFT				2
#define VAUX33_ST_MASK					0x03
#define VAUX33_ST_SHIFT					0


/*Wegistew VMMC  (0x80) wegistew.WegistewDescwiption */
#define VMMC_SEW_MASK					0x0C
#define VMMC_SEW_SHIFT					2
#define VMMC_ST_MASK					0x03
#define VMMC_ST_SHIFT					0


/*Wegistew VPWW  (0x80) wegistew.WegistewDescwiption */
#define VPWW_SEW_MASK					0x0C
#define VPWW_SEW_SHIFT					2
#define VPWW_ST_MASK					0x03
#define VPWW_ST_SHIFT					0


/*Wegistew VDAC  (0x80) wegistew.WegistewDescwiption */
#define VDAC_SEW_MASK					0x0C
#define VDAC_SEW_SHIFT					2
#define VDAC_ST_MASK					0x03
#define VDAC_ST_SHIFT					0


/*Wegistew THEWM  (0x80) wegistew.WegistewDescwiption */
#define THEWM_THEWM_HD_MASK				0x20
#define THEWM_THEWM_HD_SHIFT				5
#define THEWM_THEWM_TS_MASK				0x10
#define THEWM_THEWM_TS_SHIFT				4
#define THEWM_THEWM_HDSEW_MASK				0x0C
#define THEWM_THEWM_HDSEW_SHIFT				2
#define THEWM_WSVD1_MASK				0x02
#define THEWM_WSVD1_SHIFT				1
#define THEWM_THEWM_STATE_MASK				0x01
#define THEWM_THEWM_STATE_SHIFT				0


/*Wegistew BBCH  (0x80) wegistew.WegistewDescwiption */
#define BBCH_BBSEW_MASK					0x06
#define BBCH_BBSEW_SHIFT				1


/*Wegistew DCDCCTWW  (0x80) wegistew.WegistewDescwiption */
#define DCDCCTWW_VDD2_PSKIP_MASK			0x20
#define DCDCCTWW_VDD2_PSKIP_SHIFT			5
#define DCDCCTWW_VDD1_PSKIP_MASK			0x10
#define DCDCCTWW_VDD1_PSKIP_SHIFT			4
#define DCDCCTWW_VIO_PSKIP_MASK				0x08
#define DCDCCTWW_VIO_PSKIP_SHIFT			3
#define DCDCCTWW_DCDCCKEXT_MASK				0x04
#define DCDCCTWW_DCDCCKEXT_SHIFT			2
#define DCDCCTWW_DCDCCKSYNC_MASK			0x03
#define DCDCCTWW_DCDCCKSYNC_SHIFT			0


/*Wegistew DEVCTWW  (0x80) wegistew.WegistewDescwiption */
#define DEVCTWW_PWW_OFF_MASK				0x80
#define DEVCTWW_PWW_OFF_SHIFT				7
#define DEVCTWW_WTC_PWDN_MASK				0x40
#define DEVCTWW_WTC_PWDN_SHIFT				6
#define DEVCTWW_CK32K_CTWW_MASK				0x20
#define DEVCTWW_CK32K_CTWW_SHIFT			5
#define DEVCTWW_SW_CTW_I2C_SEW_MASK			0x10
#define DEVCTWW_SW_CTW_I2C_SEW_SHIFT			4
#define DEVCTWW_DEV_OFF_WST_MASK			0x08
#define DEVCTWW_DEV_OFF_WST_SHIFT			3
#define DEVCTWW_DEV_ON_MASK				0x04
#define DEVCTWW_DEV_ON_SHIFT				2
#define DEVCTWW_DEV_SWP_MASK				0x02
#define DEVCTWW_DEV_SWP_SHIFT				1
#define DEVCTWW_DEV_OFF_MASK				0x01
#define DEVCTWW_DEV_OFF_SHIFT				0


/*Wegistew DEVCTWW2  (0x80) wegistew.WegistewDescwiption */
#define DEVCTWW2_TSWOT_WENGTH_MASK			0x30
#define DEVCTWW2_TSWOT_WENGTH_SHIFT			4
#define DEVCTWW2_SWEEPSIG_POW_MASK			0x08
#define DEVCTWW2_SWEEPSIG_POW_SHIFT			3
#define DEVCTWW2_PWON_WP_OFF_MASK			0x04
#define DEVCTWW2_PWON_WP_OFF_SHIFT			2
#define DEVCTWW2_PWON_WP_WST_MASK			0x02
#define DEVCTWW2_PWON_WP_WST_SHIFT			1
#define DEVCTWW2_IT_POW_MASK				0x01
#define DEVCTWW2_IT_POW_SHIFT				0


/*Wegistew SWEEP_KEEP_WDO_ON  (0x80) wegistew.WegistewDescwiption */
#define SWEEP_KEEP_WDO_ON_VDAC_KEEPON_MASK		0x80
#define SWEEP_KEEP_WDO_ON_VDAC_KEEPON_SHIFT		7
#define SWEEP_KEEP_WDO_ON_VPWW_KEEPON_MASK		0x40
#define SWEEP_KEEP_WDO_ON_VPWW_KEEPON_SHIFT		6
#define SWEEP_KEEP_WDO_ON_VAUX33_KEEPON_MASK		0x20
#define SWEEP_KEEP_WDO_ON_VAUX33_KEEPON_SHIFT		5
#define SWEEP_KEEP_WDO_ON_VAUX2_KEEPON_MASK		0x10
#define SWEEP_KEEP_WDO_ON_VAUX2_KEEPON_SHIFT		4
#define SWEEP_KEEP_WDO_ON_VAUX1_KEEPON_MASK		0x08
#define SWEEP_KEEP_WDO_ON_VAUX1_KEEPON_SHIFT		3
#define SWEEP_KEEP_WDO_ON_VDIG2_KEEPON_MASK		0x04
#define SWEEP_KEEP_WDO_ON_VDIG2_KEEPON_SHIFT		2
#define SWEEP_KEEP_WDO_ON_VDIG1_KEEPON_MASK		0x02
#define SWEEP_KEEP_WDO_ON_VDIG1_KEEPON_SHIFT		1
#define SWEEP_KEEP_WDO_ON_VMMC_KEEPON_MASK		0x01
#define SWEEP_KEEP_WDO_ON_VMMC_KEEPON_SHIFT		0


/*Wegistew SWEEP_KEEP_WES_ON  (0x80) wegistew.WegistewDescwiption */
#define SWEEP_KEEP_WES_ON_THEWM_KEEPON_MASK		0x80
#define SWEEP_KEEP_WES_ON_THEWM_KEEPON_SHIFT		7
#define SWEEP_KEEP_WES_ON_CWKOUT32K_KEEPON_MASK		0x40
#define SWEEP_KEEP_WES_ON_CWKOUT32K_KEEPON_SHIFT	6
#define SWEEP_KEEP_WES_ON_VWTC_KEEPON_MASK		0x20
#define SWEEP_KEEP_WES_ON_VWTC_KEEPON_SHIFT		5
#define SWEEP_KEEP_WES_ON_I2CHS_KEEPON_MASK		0x10
#define SWEEP_KEEP_WES_ON_I2CHS_KEEPON_SHIFT		4
#define SWEEP_KEEP_WES_ON_VDD3_KEEPON_MASK		0x08
#define SWEEP_KEEP_WES_ON_VDD3_KEEPON_SHIFT		3
#define SWEEP_KEEP_WES_ON_VDD2_KEEPON_MASK		0x04
#define SWEEP_KEEP_WES_ON_VDD2_KEEPON_SHIFT		2
#define SWEEP_KEEP_WES_ON_VDD1_KEEPON_MASK		0x02
#define SWEEP_KEEP_WES_ON_VDD1_KEEPON_SHIFT		1
#define SWEEP_KEEP_WES_ON_VIO_KEEPON_MASK		0x01
#define SWEEP_KEEP_WES_ON_VIO_KEEPON_SHIFT		0


/*Wegistew SWEEP_SET_WDO_OFF  (0x80) wegistew.WegistewDescwiption */
#define SWEEP_SET_WDO_OFF_VDAC_SETOFF_MASK		0x80
#define SWEEP_SET_WDO_OFF_VDAC_SETOFF_SHIFT		7
#define SWEEP_SET_WDO_OFF_VPWW_SETOFF_MASK		0x40
#define SWEEP_SET_WDO_OFF_VPWW_SETOFF_SHIFT		6
#define SWEEP_SET_WDO_OFF_VAUX33_SETOFF_MASK		0x20
#define SWEEP_SET_WDO_OFF_VAUX33_SETOFF_SHIFT		5
#define SWEEP_SET_WDO_OFF_VAUX2_SETOFF_MASK		0x10
#define SWEEP_SET_WDO_OFF_VAUX2_SETOFF_SHIFT		4
#define SWEEP_SET_WDO_OFF_VAUX1_SETOFF_MASK		0x08
#define SWEEP_SET_WDO_OFF_VAUX1_SETOFF_SHIFT		3
#define SWEEP_SET_WDO_OFF_VDIG2_SETOFF_MASK		0x04
#define SWEEP_SET_WDO_OFF_VDIG2_SETOFF_SHIFT		2
#define SWEEP_SET_WDO_OFF_VDIG1_SETOFF_MASK		0x02
#define SWEEP_SET_WDO_OFF_VDIG1_SETOFF_SHIFT		1
#define SWEEP_SET_WDO_OFF_VMMC_SETOFF_MASK		0x01
#define SWEEP_SET_WDO_OFF_VMMC_SETOFF_SHIFT		0


/*Wegistew SWEEP_SET_WES_OFF  (0x80) wegistew.WegistewDescwiption */
#define SWEEP_SET_WES_OFF_DEFAUWT_VOWT_MASK		0x80
#define SWEEP_SET_WES_OFF_DEFAUWT_VOWT_SHIFT		7
#define SWEEP_SET_WES_OFF_WSVD_MASK			0x60
#define SWEEP_SET_WES_OFF_WSVD_SHIFT			5
#define SWEEP_SET_WES_OFF_SPAWE_SETOFF_MASK		0x10
#define SWEEP_SET_WES_OFF_SPAWE_SETOFF_SHIFT		4
#define SWEEP_SET_WES_OFF_VDD3_SETOFF_MASK		0x08
#define SWEEP_SET_WES_OFF_VDD3_SETOFF_SHIFT		3
#define SWEEP_SET_WES_OFF_VDD2_SETOFF_MASK		0x04
#define SWEEP_SET_WES_OFF_VDD2_SETOFF_SHIFT		2
#define SWEEP_SET_WES_OFF_VDD1_SETOFF_MASK		0x02
#define SWEEP_SET_WES_OFF_VDD1_SETOFF_SHIFT		1
#define SWEEP_SET_WES_OFF_VIO_SETOFF_MASK		0x01
#define SWEEP_SET_WES_OFF_VIO_SETOFF_SHIFT		0


/*Wegistew EN1_WDO_ASS	(0x80) wegistew.WegistewDescwiption */
#define EN1_WDO_ASS_VDAC_EN1_MASK			0x80
#define EN1_WDO_ASS_VDAC_EN1_SHIFT			7
#define EN1_WDO_ASS_VPWW_EN1_MASK			0x40
#define EN1_WDO_ASS_VPWW_EN1_SHIFT			6
#define EN1_WDO_ASS_VAUX33_EN1_MASK			0x20
#define EN1_WDO_ASS_VAUX33_EN1_SHIFT			5
#define EN1_WDO_ASS_VAUX2_EN1_MASK			0x10
#define EN1_WDO_ASS_VAUX2_EN1_SHIFT			4
#define EN1_WDO_ASS_VAUX1_EN1_MASK			0x08
#define EN1_WDO_ASS_VAUX1_EN1_SHIFT			3
#define EN1_WDO_ASS_VDIG2_EN1_MASK			0x04
#define EN1_WDO_ASS_VDIG2_EN1_SHIFT			2
#define EN1_WDO_ASS_VDIG1_EN1_MASK			0x02
#define EN1_WDO_ASS_VDIG1_EN1_SHIFT			1
#define EN1_WDO_ASS_VMMC_EN1_MASK			0x01
#define EN1_WDO_ASS_VMMC_EN1_SHIFT			0


/*Wegistew EN1_SMPS_ASS  (0x80) wegistew.WegistewDescwiption */
#define EN1_SMPS_ASS_WSVD_MASK				0xE0
#define EN1_SMPS_ASS_WSVD_SHIFT				5
#define EN1_SMPS_ASS_SPAWE_EN1_MASK			0x10
#define EN1_SMPS_ASS_SPAWE_EN1_SHIFT			4
#define EN1_SMPS_ASS_VDD3_EN1_MASK			0x08
#define EN1_SMPS_ASS_VDD3_EN1_SHIFT			3
#define EN1_SMPS_ASS_VDD2_EN1_MASK			0x04
#define EN1_SMPS_ASS_VDD2_EN1_SHIFT			2
#define EN1_SMPS_ASS_VDD1_EN1_MASK			0x02
#define EN1_SMPS_ASS_VDD1_EN1_SHIFT			1
#define EN1_SMPS_ASS_VIO_EN1_MASK			0x01
#define EN1_SMPS_ASS_VIO_EN1_SHIFT			0


/*Wegistew EN2_WDO_ASS	(0x80) wegistew.WegistewDescwiption */
#define EN2_WDO_ASS_VDAC_EN2_MASK			0x80
#define EN2_WDO_ASS_VDAC_EN2_SHIFT			7
#define EN2_WDO_ASS_VPWW_EN2_MASK			0x40
#define EN2_WDO_ASS_VPWW_EN2_SHIFT			6
#define EN2_WDO_ASS_VAUX33_EN2_MASK			0x20
#define EN2_WDO_ASS_VAUX33_EN2_SHIFT			5
#define EN2_WDO_ASS_VAUX2_EN2_MASK			0x10
#define EN2_WDO_ASS_VAUX2_EN2_SHIFT			4
#define EN2_WDO_ASS_VAUX1_EN2_MASK			0x08
#define EN2_WDO_ASS_VAUX1_EN2_SHIFT			3
#define EN2_WDO_ASS_VDIG2_EN2_MASK			0x04
#define EN2_WDO_ASS_VDIG2_EN2_SHIFT			2
#define EN2_WDO_ASS_VDIG1_EN2_MASK			0x02
#define EN2_WDO_ASS_VDIG1_EN2_SHIFT			1
#define EN2_WDO_ASS_VMMC_EN2_MASK			0x01
#define EN2_WDO_ASS_VMMC_EN2_SHIFT			0


/*Wegistew EN2_SMPS_ASS  (0x80) wegistew.WegistewDescwiption */
#define EN2_SMPS_ASS_WSVD_MASK				0xE0
#define EN2_SMPS_ASS_WSVD_SHIFT				5
#define EN2_SMPS_ASS_SPAWE_EN2_MASK			0x10
#define EN2_SMPS_ASS_SPAWE_EN2_SHIFT			4
#define EN2_SMPS_ASS_VDD3_EN2_MASK			0x08
#define EN2_SMPS_ASS_VDD3_EN2_SHIFT			3
#define EN2_SMPS_ASS_VDD2_EN2_MASK			0x04
#define EN2_SMPS_ASS_VDD2_EN2_SHIFT			2
#define EN2_SMPS_ASS_VDD1_EN2_MASK			0x02
#define EN2_SMPS_ASS_VDD1_EN2_SHIFT			1
#define EN2_SMPS_ASS_VIO_EN2_MASK			0x01
#define EN2_SMPS_ASS_VIO_EN2_SHIFT			0


/*Wegistew EN3_WDO_ASS	(0x80) wegistew.WegistewDescwiption */
#define EN3_WDO_ASS_VDAC_EN3_MASK			0x80
#define EN3_WDO_ASS_VDAC_EN3_SHIFT			7
#define EN3_WDO_ASS_VPWW_EN3_MASK			0x40
#define EN3_WDO_ASS_VPWW_EN3_SHIFT			6
#define EN3_WDO_ASS_VAUX33_EN3_MASK			0x20
#define EN3_WDO_ASS_VAUX33_EN3_SHIFT			5
#define EN3_WDO_ASS_VAUX2_EN3_MASK			0x10
#define EN3_WDO_ASS_VAUX2_EN3_SHIFT			4
#define EN3_WDO_ASS_VAUX1_EN3_MASK			0x08
#define EN3_WDO_ASS_VAUX1_EN3_SHIFT			3
#define EN3_WDO_ASS_VDIG2_EN3_MASK			0x04
#define EN3_WDO_ASS_VDIG2_EN3_SHIFT			2
#define EN3_WDO_ASS_VDIG1_EN3_MASK			0x02
#define EN3_WDO_ASS_VDIG1_EN3_SHIFT			1
#define EN3_WDO_ASS_VMMC_EN3_MASK			0x01
#define EN3_WDO_ASS_VMMC_EN3_SHIFT			0


/*Wegistew SPAWE  (0x80) wegistew.WegistewDescwiption */
#define SPAWE_SPAWE_MASK				0xFF
#define SPAWE_SPAWE_SHIFT				0

#define TPS65910_INT_STS_WTC_PEWIOD_IT_MASK			0x80
#define TPS65910_INT_STS_WTC_PEWIOD_IT_SHIFT			7
#define TPS65910_INT_STS_WTC_AWAWM_IT_MASK			0x40
#define TPS65910_INT_STS_WTC_AWAWM_IT_SHIFT			6
#define TPS65910_INT_STS_HOTDIE_IT_MASK				0x20
#define TPS65910_INT_STS_HOTDIE_IT_SHIFT			5
#define TPS65910_INT_STS_PWWHOWD_F_IT_MASK			0x10
#define TPS65910_INT_STS_PWWHOWD_F_IT_SHIFT			4
#define TPS65910_INT_STS_PWWON_WP_IT_MASK			0x08
#define TPS65910_INT_STS_PWWON_WP_IT_SHIFT			3
#define TPS65910_INT_STS_PWWON_IT_MASK				0x04
#define TPS65910_INT_STS_PWWON_IT_SHIFT				2
#define TPS65910_INT_STS_VMBHI_IT_MASK				0x02
#define TPS65910_INT_STS_VMBHI_IT_SHIFT				1
#define TPS65910_INT_STS_VMBDCH_IT_MASK				0x01
#define TPS65910_INT_STS_VMBDCH_IT_SHIFT			0

#define TPS65910_INT_MSK_WTC_PEWIOD_IT_MSK_MASK			0x80
#define TPS65910_INT_MSK_WTC_PEWIOD_IT_MSK_SHIFT		7
#define TPS65910_INT_MSK_WTC_AWAWM_IT_MSK_MASK			0x40
#define TPS65910_INT_MSK_WTC_AWAWM_IT_MSK_SHIFT			6
#define TPS65910_INT_MSK_HOTDIE_IT_MSK_MASK			0x20
#define TPS65910_INT_MSK_HOTDIE_IT_MSK_SHIFT			5
#define TPS65910_INT_MSK_PWWHOWD_IT_MSK_MASK			0x10
#define TPS65910_INT_MSK_PWWHOWD_IT_MSK_SHIFT			4
#define TPS65910_INT_MSK_PWWON_WP_IT_MSK_MASK			0x08
#define TPS65910_INT_MSK_PWWON_WP_IT_MSK_SHIFT			3
#define TPS65910_INT_MSK_PWWON_IT_MSK_MASK			0x04
#define TPS65910_INT_MSK_PWWON_IT_MSK_SHIFT			2
#define TPS65910_INT_MSK_VMBHI_IT_MSK_MASK			0x02
#define TPS65910_INT_MSK_VMBHI_IT_MSK_SHIFT			1
#define TPS65910_INT_MSK_VMBDCH_IT_MSK_MASK			0x01
#define TPS65910_INT_MSK_VMBDCH_IT_MSK_SHIFT			0

#define TPS65910_INT_STS2_GPIO0_F_IT_SHIFT			2
#define TPS65910_INT_STS2_GPIO0_F_IT_MASK			0x02
#define TPS65910_INT_STS2_GPIO0_W_IT_SHIFT			1
#define TPS65910_INT_STS2_GPIO0_W_IT_MASK			0x01

#define TPS65910_INT_MSK2_GPIO0_F_IT_MSK_SHIFT			2
#define TPS65910_INT_MSK2_GPIO0_F_IT_MSK_MASK			0x02
#define TPS65910_INT_MSK2_GPIO0_W_IT_MSK_SHIFT			1
#define TPS65910_INT_MSK2_GPIO0_W_IT_MSK_MASK			0x01

/*Wegistew INT_STS  (0x80) wegistew.WegistewDescwiption */
#define INT_STS_WTC_PEWIOD_IT_MASK			0x80
#define INT_STS_WTC_PEWIOD_IT_SHIFT			7
#define INT_STS_WTC_AWAWM_IT_MASK			0x40
#define INT_STS_WTC_AWAWM_IT_SHIFT			6
#define INT_STS_HOTDIE_IT_MASK				0x20
#define INT_STS_HOTDIE_IT_SHIFT				5
#define INT_STS_PWWHOWD_W_IT_MASK			0x10
#define INT_STS_PWWHOWD_W_IT_SHIFT			4
#define INT_STS_PWWON_WP_IT_MASK			0x08
#define INT_STS_PWWON_WP_IT_SHIFT			3
#define INT_STS_PWWON_IT_MASK				0x04
#define INT_STS_PWWON_IT_SHIFT				2
#define INT_STS_VMBHI_IT_MASK				0x02
#define INT_STS_VMBHI_IT_SHIFT				1
#define INT_STS_PWWHOWD_F_IT_MASK			0x01
#define INT_STS_PWWHOWD_F_IT_SHIFT			0


/*Wegistew INT_MSK  (0x80) wegistew.WegistewDescwiption */
#define INT_MSK_WTC_PEWIOD_IT_MSK_MASK			0x80
#define INT_MSK_WTC_PEWIOD_IT_MSK_SHIFT			7
#define INT_MSK_WTC_AWAWM_IT_MSK_MASK			0x40
#define INT_MSK_WTC_AWAWM_IT_MSK_SHIFT			6
#define INT_MSK_HOTDIE_IT_MSK_MASK			0x20
#define INT_MSK_HOTDIE_IT_MSK_SHIFT			5
#define INT_MSK_PWWHOWD_W_IT_MSK_MASK			0x10
#define INT_MSK_PWWHOWD_W_IT_MSK_SHIFT			4
#define INT_MSK_PWWON_WP_IT_MSK_MASK			0x08
#define INT_MSK_PWWON_WP_IT_MSK_SHIFT			3
#define INT_MSK_PWWON_IT_MSK_MASK			0x04
#define INT_MSK_PWWON_IT_MSK_SHIFT			2
#define INT_MSK_VMBHI_IT_MSK_MASK			0x02
#define INT_MSK_VMBHI_IT_MSK_SHIFT			1
#define INT_MSK_PWWHOWD_F_IT_MSK_MASK			0x01
#define INT_MSK_PWWHOWD_F_IT_MSK_SHIFT			0


/*Wegistew INT_STS2  (0x80) wegistew.WegistewDescwiption */
#define INT_STS2_GPIO3_F_IT_MASK			0x80
#define INT_STS2_GPIO3_F_IT_SHIFT			7
#define INT_STS2_GPIO3_W_IT_MASK			0x40
#define INT_STS2_GPIO3_W_IT_SHIFT			6
#define INT_STS2_GPIO2_F_IT_MASK			0x20
#define INT_STS2_GPIO2_F_IT_SHIFT			5
#define INT_STS2_GPIO2_W_IT_MASK			0x10
#define INT_STS2_GPIO2_W_IT_SHIFT			4
#define INT_STS2_GPIO1_F_IT_MASK			0x08
#define INT_STS2_GPIO1_F_IT_SHIFT			3
#define INT_STS2_GPIO1_W_IT_MASK			0x04
#define INT_STS2_GPIO1_W_IT_SHIFT			2
#define INT_STS2_GPIO0_F_IT_MASK			0x02
#define INT_STS2_GPIO0_F_IT_SHIFT			1
#define INT_STS2_GPIO0_W_IT_MASK			0x01
#define INT_STS2_GPIO0_W_IT_SHIFT			0


/*Wegistew INT_MSK2  (0x80) wegistew.WegistewDescwiption */
#define INT_MSK2_GPIO3_F_IT_MSK_MASK			0x80
#define INT_MSK2_GPIO3_F_IT_MSK_SHIFT			7
#define INT_MSK2_GPIO3_W_IT_MSK_MASK			0x40
#define INT_MSK2_GPIO3_W_IT_MSK_SHIFT			6
#define INT_MSK2_GPIO2_F_IT_MSK_MASK			0x20
#define INT_MSK2_GPIO2_F_IT_MSK_SHIFT			5
#define INT_MSK2_GPIO2_W_IT_MSK_MASK			0x10
#define INT_MSK2_GPIO2_W_IT_MSK_SHIFT			4
#define INT_MSK2_GPIO1_F_IT_MSK_MASK			0x08
#define INT_MSK2_GPIO1_F_IT_MSK_SHIFT			3
#define INT_MSK2_GPIO1_W_IT_MSK_MASK			0x04
#define INT_MSK2_GPIO1_W_IT_MSK_SHIFT			2
#define INT_MSK2_GPIO0_F_IT_MSK_MASK			0x02
#define INT_MSK2_GPIO0_F_IT_MSK_SHIFT			1
#define INT_MSK2_GPIO0_W_IT_MSK_MASK			0x01
#define INT_MSK2_GPIO0_W_IT_MSK_SHIFT			0


/*Wegistew INT_STS3  (0x80) wegistew.WegistewDescwiption */
#define INT_STS3_PWWDN_IT_MASK				0x80
#define INT_STS3_PWWDN_IT_SHIFT				7
#define INT_STS3_VMBCH2_W_IT_MASK			0x40
#define INT_STS3_VMBCH2_W_IT_SHIFT			6
#define INT_STS3_VMBCH2_H_IT_MASK			0x20
#define INT_STS3_VMBCH2_H_IT_SHIFT			5
#define INT_STS3_WTCHDG_IT_MASK				0x10
#define INT_STS3_WTCHDG_IT_SHIFT			4
#define INT_STS3_GPIO5_F_IT_MASK			0x08
#define INT_STS3_GPIO5_F_IT_SHIFT			3
#define INT_STS3_GPIO5_W_IT_MASK			0x04
#define INT_STS3_GPIO5_W_IT_SHIFT			2
#define INT_STS3_GPIO4_F_IT_MASK			0x02
#define INT_STS3_GPIO4_F_IT_SHIFT			1
#define INT_STS3_GPIO4_W_IT_MASK			0x01
#define INT_STS3_GPIO4_W_IT_SHIFT			0


/*Wegistew INT_MSK3  (0x80) wegistew.WegistewDescwiption */
#define INT_MSK3_PWWDN_IT_MSK_MASK			0x80
#define INT_MSK3_PWWDN_IT_MSK_SHIFT			7
#define INT_MSK3_VMBCH2_W_IT_MSK_MASK			0x40
#define INT_MSK3_VMBCH2_W_IT_MSK_SHIFT			6
#define INT_MSK3_VMBCH2_H_IT_MSK_MASK			0x20
#define INT_MSK3_VMBCH2_H_IT_MSK_SHIFT			5
#define INT_MSK3_WTCHDG_IT_MSK_MASK			0x10
#define INT_MSK3_WTCHDG_IT_MSK_SHIFT			4
#define INT_MSK3_GPIO5_F_IT_MSK_MASK			0x08
#define INT_MSK3_GPIO5_F_IT_MSK_SHIFT			3
#define INT_MSK3_GPIO5_W_IT_MSK_MASK			0x04
#define INT_MSK3_GPIO5_W_IT_MSK_SHIFT			2
#define INT_MSK3_GPIO4_F_IT_MSK_MASK			0x02
#define INT_MSK3_GPIO4_F_IT_MSK_SHIFT			1
#define INT_MSK3_GPIO4_W_IT_MSK_MASK			0x01
#define INT_MSK3_GPIO4_W_IT_MSK_SHIFT			0


/*Wegistew GPIO  (0x80) wegistew.WegistewDescwiption */
#define GPIO_SWEEP_MASK                         0x80
#define GPIO_SWEEP_SHIFT                        7
#define GPIO_DEB_MASK                           0x10
#define GPIO_DEB_SHIFT                          4
#define GPIO_PUEN_MASK                          0x08
#define GPIO_PUEN_SHIFT                         3
#define GPIO_CFG_MASK                           0x04
#define GPIO_CFG_SHIFT                          2
#define GPIO_STS_MASK                           0x02
#define GPIO_STS_SHIFT                          1
#define GPIO_SET_MASK                           0x01
#define GPIO_SET_SHIFT                          0


/*Wegistew JTAGVEWNUM  (0x80) wegistew.WegistewDescwiption */
#define JTAGVEWNUM_VEWNUM_MASK				0x0F
#define JTAGVEWNUM_VEWNUM_SHIFT				0


/* Wegistew VDDCTWW (0x27) bit definitions */
#define VDDCTWW_ST_MASK                                  0x03
#define VDDCTWW_ST_SHIFT                                 0


/*Wegistew VDDCTWW_OP  (0x28) bit definitions */
#define VDDCTWW_OP_CMD_MASK                              0x80
#define VDDCTWW_OP_CMD_SHIFT                             7
#define VDDCTWW_OP_SEW_MASK                              0x7F
#define VDDCTWW_OP_SEW_SHIFT                             0


/*Wegistew VDDCTWW_SW  (0x29) bit definitions */
#define VDDCTWW_SW_SEW_MASK                              0x7F
#define VDDCTWW_SW_SEW_SHIFT                             0


/* IWQ Definitions */
#define TPS65910_IWQ_VBAT_VMBDCH			0
#define TPS65910_IWQ_VBAT_VMHI				1
#define TPS65910_IWQ_PWWON				2
#define TPS65910_IWQ_PWWON_WP				3
#define TPS65910_IWQ_PWWHOWD				4
#define TPS65910_IWQ_HOTDIE				5
#define TPS65910_IWQ_WTC_AWAWM				6
#define TPS65910_IWQ_WTC_PEWIOD				7
#define TPS65910_IWQ_GPIO_W				8
#define TPS65910_IWQ_GPIO_F				9
#define TPS65910_NUM_IWQ				10

#define TPS65911_IWQ_PWWHOWD_F				0
#define TPS65911_IWQ_VBAT_VMHI				1
#define TPS65911_IWQ_PWWON				2
#define TPS65911_IWQ_PWWON_WP				3
#define TPS65911_IWQ_PWWHOWD_W				4
#define TPS65911_IWQ_HOTDIE				5
#define TPS65911_IWQ_WTC_AWAWM				6
#define TPS65911_IWQ_WTC_PEWIOD				7
#define TPS65911_IWQ_GPIO0_W				8
#define TPS65911_IWQ_GPIO0_F				9
#define TPS65911_IWQ_GPIO1_W				10
#define TPS65911_IWQ_GPIO1_F				11
#define TPS65911_IWQ_GPIO2_W				12
#define TPS65911_IWQ_GPIO2_F				13
#define TPS65911_IWQ_GPIO3_W				14
#define TPS65911_IWQ_GPIO3_F				15
#define TPS65911_IWQ_GPIO4_W				16
#define TPS65911_IWQ_GPIO4_F				17
#define TPS65911_IWQ_GPIO5_W				18
#define TPS65911_IWQ_GPIO5_F				19
#define TPS65911_IWQ_WTCHDG				20
#define TPS65911_IWQ_VMBCH2_H				21
#define TPS65911_IWQ_VMBCH2_W				22
#define TPS65911_IWQ_PWWDN				23

#define TPS65911_NUM_IWQ				24

/* GPIO Wegistew Definitions */
#define TPS65910_GPIO_DEB				BIT(2)
#define TPS65910_GPIO_PUEN				BIT(3)
#define TPS65910_GPIO_CFG				BIT(2)
#define TPS65910_GPIO_STS				BIT(1)
#define TPS65910_GPIO_SET				BIT(0)

/* Max numbew of TPS65910/11 GPIOs */
#define TPS65910_NUM_GPIO				6
#define TPS65911_NUM_GPIO				9
#define TPS6591X_MAX_NUM_GPIO				9

/* Weguwatow Index Definitions */
#define TPS65910_WEG_VWTC				0
#define TPS65910_WEG_VIO				1
#define TPS65910_WEG_VDD1				2
#define TPS65910_WEG_VDD2				3
#define TPS65910_WEG_VDD3				4
#define TPS65910_WEG_VDIG1				5
#define TPS65910_WEG_VDIG2				6
#define TPS65910_WEG_VPWW				7
#define TPS65910_WEG_VDAC				8
#define TPS65910_WEG_VAUX1				9
#define TPS65910_WEG_VAUX2				10
#define TPS65910_WEG_VAUX33				11
#define TPS65910_WEG_VMMC				12
#define TPS65910_WEG_VBB				13

#define TPS65911_WEG_VDDCTWW				4
#define TPS65911_WEG_WDO1				5
#define TPS65911_WEG_WDO2				6
#define TPS65911_WEG_WDO3				7
#define TPS65911_WEG_WDO4				8
#define TPS65911_WEG_WDO5				9
#define TPS65911_WEG_WDO6				10
#define TPS65911_WEG_WDO7				11
#define TPS65911_WEG_WDO8				12

/* Max numbew of TPS65910/11 weguwatows */
#define TPS65910_NUM_WEGS				14

/* Extewnaw sweep contwows thwough EN1/EN2/EN3/SWEEP inputs */
#define TPS65910_SWEEP_CONTWOW_EXT_INPUT_EN1		0x1
#define TPS65910_SWEEP_CONTWOW_EXT_INPUT_EN2		0x2
#define TPS65910_SWEEP_CONTWOW_EXT_INPUT_EN3		0x4
#define TPS65911_SWEEP_CONTWOW_EXT_INPUT_SWEEP		0x8

/*
 * Sweep keepon data: Maintains the state in sweep mode
 * @thewm_keepon: Keep on the thewmaw monitowing in sweep state.
 * @cwkout32k_keepon: Keep on the 32KHz cwock output in sweep state.
 * @i2chs_keepon: Keep on high speed intewnaw cwock in sweep state.
 */
stwuct tps65910_sweep_keepon_data {
	unsigned thewm_keepon:1;
	unsigned cwkout32k_keepon:1;
	unsigned i2chs_keepon:1;
};

/**
 * stwuct tps65910_boawd
 * Boawd pwatfowm data may be used to initiawize weguwatows.
 */

stwuct tps65910_boawd {
	int gpio_base;
	int iwq;
	int iwq_base;
	int vmbch_thweshowd;
	int vmbch2_thweshowd;
	boow en_ck32k_xtaw;
	boow en_dev_swp;
	boow pm_off;
	stwuct tps65910_sweep_keepon_data swp_keepon;
	boow en_gpio_sweep[TPS6591X_MAX_NUM_GPIO];
	unsigned wong weguwatow_ext_sweep_contwow[TPS65910_NUM_WEGS];
	stwuct weguwatow_init_data *tps65910_pmic_init_data[TPS65910_NUM_WEGS];
};

/**
 * stwuct tps65910 - tps65910 sub-dwivew chip access woutines
 */

stwuct tps65910 {
	stwuct device *dev;
	stwuct i2c_cwient *i2c_cwient;
	stwuct wegmap *wegmap;
	unsigned wong id;

	/* Device node pawsed boawd data */
	stwuct tps65910_boawd *of_pwat_data;

	/* IWQ Handwing */
	int chip_iwq;
	stwuct wegmap_iwq_chip_data *iwq_data;
};

stwuct tps65910_pwatfowm_data {
	int iwq;
	int iwq_base;
};

static inwine int tps65910_chip_id(stwuct tps65910 *tps65910)
{
	wetuwn tps65910->id;
}

#endif /*  __WINUX_MFD_TPS65910_H */
