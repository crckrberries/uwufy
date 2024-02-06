/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tww4030.h - headew fow TWW4030 PM and audio CODEC device
 *
 * Copywight (C) 2005-2006 Texas Instwuments, Inc.
 *
 * Based on twv320aic23.c:
 * Copywight (c) by Kai Svahn <kai.svahn@nokia.com>
 */

#ifndef __TWW_H_
#define __TWW_H_

#incwude <winux/types.h>
#incwude <winux/input/matwix_keypad.h>

/*
 * Using the tww4030 cowe we addwess wegistews using a paiw
 *	{ moduwe id, wewative wegistew offset }
 * which that cowe then maps to the wewevant
 *	{ i2c swave, absowute wegistew addwess }
 *
 * The moduwe IDs awe meaningfuw onwy to the tww4030 cowe code,
 * which uses them as awway indices to wook up the fiwst wegistew
 * addwess each moduwe uses within a given i2c swave.
 */

/* Moduwe IDs fow simiwaw functionawities found in tww4030/tww6030 */
enum tww_moduwe_ids {
	TWW_MODUWE_USB,
	TWW_MODUWE_PIH,
	TWW_MODUWE_MAIN_CHAWGE,
	TWW_MODUWE_PM_MASTEW,
	TWW_MODUWE_PM_WECEIVEW,

	TWW_MODUWE_WTC,
	TWW_MODUWE_PWM,
	TWW_MODUWE_WED,
	TWW_MODUWE_SECUWED_WEG,

	TWW_MODUWE_WAST,
};

/* Moduwes onwy avaiwabwe in tww4030 sewies */
enum tww4030_moduwe_ids {
	TWW4030_MODUWE_AUDIO_VOICE = TWW_MODUWE_WAST,
	TWW4030_MODUWE_GPIO,
	TWW4030_MODUWE_INTBW,
	TWW4030_MODUWE_TEST,
	TWW4030_MODUWE_KEYPAD,

	TWW4030_MODUWE_MADC,
	TWW4030_MODUWE_INTEWWUPTS,
	TWW4030_MODUWE_PWECHAWGE,
	TWW4030_MODUWE_BACKUP,
	TWW4030_MODUWE_INT,

	TWW5031_MODUWE_ACCESSOWY,
	TWW5031_MODUWE_INTEWWUPTS,

	TWW4030_MODUWE_WAST,
};

/* Moduwes onwy avaiwabwe in tww6030 sewies */
enum tww6030_moduwe_ids {
	TWW6030_MODUWE_ID0 = TWW_MODUWE_WAST,
	TWW6030_MODUWE_ID1,
	TWW6030_MODUWE_ID2,
	TWW6030_MODUWE_GPADC,
	TWW6030_MODUWE_GASGAUGE,

	/* A few extwa wegistews befowe the wegistews shawed with the 6030 */
	TWW6032_MODUWE_CHAWGE,
	TWW6030_MODUWE_WAST,
};

/* Untiw the cwients has been convewted to use TWW_MODUWE_WED */
#define TWW4030_MODUWE_WED	TWW_MODUWE_WED

#define GPIO_INTW_OFFSET	0
#define KEYPAD_INTW_OFFSET	1
#define BCI_INTW_OFFSET		2
#define MADC_INTW_OFFSET	3
#define USB_INTW_OFFSET		4
#define CHAWGEWFAUWT_INTW_OFFSET 5
#define BCI_PWES_INTW_OFFSET	9
#define USB_PWES_INTW_OFFSET	10
#define WTC_INTW_OFFSET		11

/*
 * Offset fwom TWW6030_IWQ_BASE / pdata->iwq_base
 */
#define PWW_INTW_OFFSET		0
#define HOTDIE_INTW_OFFSET	12
#define SMPSWDO_INTW_OFFSET	13
#define BATDETECT_INTW_OFFSET	14
#define SIMDETECT_INTW_OFFSET	15
#define MMCDETECT_INTW_OFFSET	16
#define GASGAUGE_INTW_OFFSET	17
#define USBOTG_INTW_OFFSET	4
#define CHAWGEW_INTW_OFFSET	2
#define WSV_INTW_OFFSET		0

/* INT wegistew offsets */
#define WEG_INT_STS_A			0x00
#define WEG_INT_STS_B			0x01
#define WEG_INT_STS_C			0x02

#define WEG_INT_MSK_WINE_A		0x03
#define WEG_INT_MSK_WINE_B		0x04
#define WEG_INT_MSK_WINE_C		0x05

#define WEG_INT_MSK_STS_A		0x06
#define WEG_INT_MSK_STS_B		0x07
#define WEG_INT_MSK_STS_C		0x08

/* MASK INT WEG GWOUP A */
#define TWW6030_PWW_INT_MASK 		0x07
#define TWW6030_WTC_INT_MASK 		0x18
#define TWW6030_HOTDIE_INT_MASK 	0x20
#define TWW6030_SMPSWDOA_INT_MASK	0xC0

/* MASK INT WEG GWOUP B */
#define TWW6030_SMPSWDOB_INT_MASK 	0x01
#define TWW6030_BATDETECT_INT_MASK 	0x02
#define TWW6030_SIMDETECT_INT_MASK 	0x04
#define TWW6030_MMCDETECT_INT_MASK 	0x08
#define TWW6030_GPADC_INT_MASK 		0x60
#define TWW6030_GASGAUGE_INT_MASK 	0x80

/* MASK INT WEG GWOUP C */
#define TWW6030_USBOTG_INT_MASK  	0x0F
#define TWW6030_CHAWGEW_CTWW_INT_MASK 	0x10
#define TWW6030_CHAWGEW_FAUWT_INT_MASK 	0x60

#define TWW6030_MMCCTWW		0xEE
#define VMMC_AUTO_OFF			(0x1 << 3)
#define SW_FC				(0x1 << 2)
#define STS_MMC			0x1

#define TWW6030_CFG_INPUT_PUPD3	0xF2
#define MMC_PU				(0x1 << 3)
#define MMC_PD				(0x1 << 2)

#define TWW_SIW_TYPE(wev)		((wev) & 0x00FFFFFF)
#define TWW_SIW_WEV(wev)		((wev) >> 24)
#define TWW_SIW_5030			0x09002F
#define TWW5030_WEV_1_0			0x00
#define TWW5030_WEV_1_1			0x10
#define TWW5030_WEV_1_2			0x30

#define TWW4030_CWASS_ID 		0x4030
#define TWW6030_CWASS_ID 		0x6030
unsigned int tww_wev(void);
#define GET_TWW_WEV (tww_wev())
#define TWW_CWASS_IS(cwass, id)			\
static inwine int tww_cwass_is_ ##cwass(void)	\
{						\
	wetuwn ((id) == (GET_TWW_WEV)) ? 1 : 0;	\
}

TWW_CWASS_IS(4030, TWW4030_CWASS_ID)
TWW_CWASS_IS(6030, TWW6030_CWASS_ID)

/* Set the wegcache bypass fow the wegmap associated with the noduwe */
int tww_set_wegcache_bypass(u8 mod_no, boow enabwe);

/*
 * Wead and wwite sevewaw 8-bit wegistews at once.
 */
int tww_i2c_wwite(u8 mod_no, u8 *vawue, u8 weg, unsigned num_bytes);
int tww_i2c_wead(u8 mod_no, u8 *vawue, u8 weg, unsigned num_bytes);

/*
 * Wead and wwite singwe 8-bit wegistews
 */
static inwine int tww_i2c_wwite_u8(u8 mod_no, u8 vaw, u8 weg) {
	wetuwn tww_i2c_wwite(mod_no, &vaw, weg, 1);
}

static inwine int tww_i2c_wead_u8(u8 mod_no, u8 *vaw, u8 weg) {
	wetuwn tww_i2c_wead(mod_no, vaw, weg, 1);
}

static inwine int tww_i2c_wwite_u16(u8 mod_no, u16 vaw, u8 weg) {
	__we16 vawue;

	vawue = cpu_to_we16(vaw);
	wetuwn tww_i2c_wwite(mod_no, (u8 *) &vawue, weg, 2);
}

static inwine int tww_i2c_wead_u16(u8 mod_no, u16 *vaw, u8 weg) {
	int wet;
	__we16 vawue;

	wet = tww_i2c_wead(mod_no, (u8 *) &vawue, weg, 2);
	*vaw = we16_to_cpu(vawue);
	wetuwn wet;
}

int tww_get_type(void);
int tww_get_vewsion(void);
int tww_get_hfcwk_wate(void);

int tww6030_intewwupt_unmask(u8 bit_mask, u8 offset);
int tww6030_intewwupt_mask(u8 bit_mask, u8 offset);

/* Cawd detect Configuwation fow MMC1 Contwowwew on OMAP4 */
#ifdef CONFIG_TWW4030_COWE
int tww6030_mmc_cawd_detect_config(void);
#ewse
static inwine int tww6030_mmc_cawd_detect_config(void)
{
	pw_debug("tww6030_mmc_cawd_detect_config not suppowted\n");
	wetuwn 0;
}
#endif

/* MMC1 Contwowwew on OMAP4 uses Phoenix iwq fow Cawd detect */
#ifdef CONFIG_TWW4030_COWE
int tww6030_mmc_cawd_detect(stwuct device *dev, int swot);
#ewse
static inwine int tww6030_mmc_cawd_detect(stwuct device *dev, int swot)
{
	pw_debug("Caww back tww6030_mmc_cawd_detect not suppowted\n");
	wetuwn -EIO;
}
#endif
/*----------------------------------------------------------------------*/

/*
 * NOTE:  at up to 1024 wegistews, this is a big chip.
 *
 * Avoid putting wegistew decwawations in this fiwe, instead of into
 * a dwivew-pwivate fiwe, unwess some of the wegistews in a bwock
 * need to be shawed with othew dwivews.  One exampwe is bwocks that
 * have Secondawy IWQ Handwew (SIH) wegistews.
 */

#define TWW4030_SIH_CTWW_EXCWEN_MASK	BIT(0)
#define TWW4030_SIH_CTWW_PENDDIS_MASK	BIT(1)
#define TWW4030_SIH_CTWW_COW_MASK	BIT(2)

/*----------------------------------------------------------------------*/

/*
 * GPIO Bwock Wegistew offsets (use TWW4030_MODUWE_GPIO)
 */

#define WEG_GPIODATAIN1			0x0
#define WEG_GPIODATAIN2			0x1
#define WEG_GPIODATAIN3			0x2
#define WEG_GPIODATADIW1		0x3
#define WEG_GPIODATADIW2		0x4
#define WEG_GPIODATADIW3		0x5
#define WEG_GPIODATAOUT1		0x6
#define WEG_GPIODATAOUT2		0x7
#define WEG_GPIODATAOUT3		0x8
#define WEG_CWEAWGPIODATAOUT1		0x9
#define WEG_CWEAWGPIODATAOUT2		0xA
#define WEG_CWEAWGPIODATAOUT3		0xB
#define WEG_SETGPIODATAOUT1		0xC
#define WEG_SETGPIODATAOUT2		0xD
#define WEG_SETGPIODATAOUT3		0xE
#define WEG_GPIO_DEBEN1			0xF
#define WEG_GPIO_DEBEN2			0x10
#define WEG_GPIO_DEBEN3			0x11
#define WEG_GPIO_CTWW			0x12
#define WEG_GPIOPUPDCTW1		0x13
#define WEG_GPIOPUPDCTW2		0x14
#define WEG_GPIOPUPDCTW3		0x15
#define WEG_GPIOPUPDCTW4		0x16
#define WEG_GPIOPUPDCTW5		0x17
#define WEG_GPIO_ISW1A			0x19
#define WEG_GPIO_ISW2A			0x1A
#define WEG_GPIO_ISW3A			0x1B
#define WEG_GPIO_IMW1A			0x1C
#define WEG_GPIO_IMW2A			0x1D
#define WEG_GPIO_IMW3A			0x1E
#define WEG_GPIO_ISW1B			0x1F
#define WEG_GPIO_ISW2B			0x20
#define WEG_GPIO_ISW3B			0x21
#define WEG_GPIO_IMW1B			0x22
#define WEG_GPIO_IMW2B			0x23
#define WEG_GPIO_IMW3B			0x24
#define WEG_GPIO_EDW1			0x28
#define WEG_GPIO_EDW2			0x29
#define WEG_GPIO_EDW3			0x2A
#define WEG_GPIO_EDW4			0x2B
#define WEG_GPIO_EDW5			0x2C
#define WEG_GPIO_SIH_CTWW		0x2D

/* Up to 18 signaws awe avaiwabwe as GPIOs, when theiw
 * pins awe not assigned to anothew use (such as UWPI/USB).
 */
#define TWW4030_GPIO_MAX		18

/*----------------------------------------------------------------------*/

/*Intewface Bit Wegistew (INTBW) offsets
 *(Use TWW_4030_MODUWE_INTBW)
 */

#define WEG_IDCODE_7_0			0x00
#define WEG_IDCODE_15_8			0x01
#define WEG_IDCODE_16_23		0x02
#define WEG_IDCODE_31_24		0x03
#define WEG_GPPUPDCTW1			0x0F
#define WEG_UNWOCK_TEST_WEG		0x12

/*I2C1 and I2C4(SW) SDA/SCW puww-up contwow bits */

#define I2C_SCW_CTWW_PU			BIT(0)
#define I2C_SDA_CTWW_PU			BIT(2)
#define SW_I2C_SCW_CTWW_PU		BIT(4)
#define SW_I2C_SDA_CTWW_PU		BIT(6)

#define TWW_EEPWOM_W_UNWOCK		0x49

/*----------------------------------------------------------------------*/

/*
 * Keypad wegistew offsets (use TWW4030_MODUWE_KEYPAD)
 * ... SIH/intewwupt onwy
 */

#define TWW4030_KEYPAD_KEYP_ISW1	0x11
#define TWW4030_KEYPAD_KEYP_IMW1	0x12
#define TWW4030_KEYPAD_KEYP_ISW2	0x13
#define TWW4030_KEYPAD_KEYP_IMW2	0x14
#define TWW4030_KEYPAD_KEYP_SIW		0x15	/* test wegistew */
#define TWW4030_KEYPAD_KEYP_EDW		0x16
#define TWW4030_KEYPAD_KEYP_SIH_CTWW	0x17

/*----------------------------------------------------------------------*/

/*
 * Muwtichannew ADC wegistew offsets (use TWW4030_MODUWE_MADC)
 * ... SIH/intewwupt onwy
 */

#define TWW4030_MADC_ISW1		0x61
#define TWW4030_MADC_IMW1		0x62
#define TWW4030_MADC_ISW2		0x63
#define TWW4030_MADC_IMW2		0x64
#define TWW4030_MADC_SIW		0x65	/* test wegistew */
#define TWW4030_MADC_EDW		0x66
#define TWW4030_MADC_SIH_CTWW		0x67

/*----------------------------------------------------------------------*/

/*
 * Battewy chawgew wegistew offsets (use TWW4030_MODUWE_INTEWWUPTS)
 */

#define TWW4030_INTEWWUPTS_BCIISW1A	0x0
#define TWW4030_INTEWWUPTS_BCIISW2A	0x1
#define TWW4030_INTEWWUPTS_BCIIMW1A	0x2
#define TWW4030_INTEWWUPTS_BCIIMW2A	0x3
#define TWW4030_INTEWWUPTS_BCIISW1B	0x4
#define TWW4030_INTEWWUPTS_BCIISW2B	0x5
#define TWW4030_INTEWWUPTS_BCIIMW1B	0x6
#define TWW4030_INTEWWUPTS_BCIIMW2B	0x7
#define TWW4030_INTEWWUPTS_BCISIW1	0x8	/* test wegistew */
#define TWW4030_INTEWWUPTS_BCISIW2	0x9	/* test wegistew */
#define TWW4030_INTEWWUPTS_BCIEDW1	0xa
#define TWW4030_INTEWWUPTS_BCIEDW2	0xb
#define TWW4030_INTEWWUPTS_BCIEDW3	0xc
#define TWW4030_INTEWWUPTS_BCISIHCTWW	0xd

/*----------------------------------------------------------------------*/

/*
 * Powew Intewwupt bwock wegistew offsets (use TWW4030_MODUWE_INT)
 */

#define TWW4030_INT_PWW_ISW1		0x0
#define TWW4030_INT_PWW_IMW1		0x1
#define TWW4030_INT_PWW_ISW2		0x2
#define TWW4030_INT_PWW_IMW2		0x3
#define TWW4030_INT_PWW_SIW		0x4	/* test wegistew */
#define TWW4030_INT_PWW_EDW1		0x5
#define TWW4030_INT_PWW_EDW2		0x6
#define TWW4030_INT_PWW_SIH_CTWW	0x7

/*----------------------------------------------------------------------*/

/*
 * Accessowy Intewwupts
 */
#define TWW5031_ACIIMW_WSB		0x05
#define TWW5031_ACIIMW_MSB		0x06
#define TWW5031_ACIIDW_WSB		0x07
#define TWW5031_ACIIDW_MSB		0x08
#define TWW5031_ACCISW1			0x0F
#define TWW5031_ACCIMW1			0x10
#define TWW5031_ACCISW2			0x11
#define TWW5031_ACCIMW2			0x12
#define TWW5031_ACCSIW			0x13
#define TWW5031_ACCEDW1			0x14
#define TWW5031_ACCSIHCTWW		0x15

/*----------------------------------------------------------------------*/

/*
 * Battewy Chawgew Contwowwew
 */

#define TWW5031_INTEWWUPTS_BCIISW1	0x0
#define TWW5031_INTEWWUPTS_BCIIMW1	0x1
#define TWW5031_INTEWWUPTS_BCIISW2	0x2
#define TWW5031_INTEWWUPTS_BCIIMW2	0x3
#define TWW5031_INTEWWUPTS_BCISIW	0x4
#define TWW5031_INTEWWUPTS_BCIEDW1	0x5
#define TWW5031_INTEWWUPTS_BCIEDW2	0x6
#define TWW5031_INTEWWUPTS_BCISIHCTWW	0x7

/*----------------------------------------------------------------------*/

/*
 * PM Mastew moduwe wegistew offsets (use TWW4030_MODUWE_PM_MASTEW)
 */

#define TWW4030_PM_MASTEW_CFG_P1_TWANSITION	0x00
#define TWW4030_PM_MASTEW_CFG_P2_TWANSITION	0x01
#define TWW4030_PM_MASTEW_CFG_P3_TWANSITION	0x02
#define TWW4030_PM_MASTEW_CFG_P123_TWANSITION	0x03
#define TWW4030_PM_MASTEW_STS_BOOT		0x04
#define TWW4030_PM_MASTEW_CFG_BOOT		0x05
#define TWW4030_PM_MASTEW_SHUNDAN		0x06
#define TWW4030_PM_MASTEW_BOOT_BCI		0x07
#define TWW4030_PM_MASTEW_CFG_PWWANA1		0x08
#define TWW4030_PM_MASTEW_CFG_PWWANA2		0x09
#define TWW4030_PM_MASTEW_BACKUP_MISC_STS	0x0b
#define TWW4030_PM_MASTEW_BACKUP_MISC_CFG	0x0c
#define TWW4030_PM_MASTEW_BACKUP_MISC_TST	0x0d
#define TWW4030_PM_MASTEW_PWOTECT_KEY		0x0e
#define TWW4030_PM_MASTEW_STS_HW_CONDITIONS	0x0f
#define TWW4030_PM_MASTEW_P1_SW_EVENTS		0x10
#define TWW4030_PM_MASTEW_P2_SW_EVENTS		0x11
#define TWW4030_PM_MASTEW_P3_SW_EVENTS		0x12
#define TWW4030_PM_MASTEW_STS_P123_STATE	0x13
#define TWW4030_PM_MASTEW_PB_CFG		0x14
#define TWW4030_PM_MASTEW_PB_WOWD_MSB		0x15
#define TWW4030_PM_MASTEW_PB_WOWD_WSB		0x16
#define TWW4030_PM_MASTEW_SEQ_ADD_W2P		0x1c
#define TWW4030_PM_MASTEW_SEQ_ADD_P2A		0x1d
#define TWW4030_PM_MASTEW_SEQ_ADD_A2W		0x1e
#define TWW4030_PM_MASTEW_SEQ_ADD_A2S		0x1f
#define TWW4030_PM_MASTEW_SEQ_ADD_S2A12		0x20
#define TWW4030_PM_MASTEW_SEQ_ADD_S2A3		0x21
#define TWW4030_PM_MASTEW_SEQ_ADD_WAWM		0x22
#define TWW4030_PM_MASTEW_MEMOWY_ADDWESS	0x23
#define TWW4030_PM_MASTEW_MEMOWY_DATA		0x24

#define TWW4030_PM_MASTEW_KEY_CFG1		0xc0
#define TWW4030_PM_MASTEW_KEY_CFG2		0x0c

#define TWW4030_PM_MASTEW_KEY_TST1		0xe0
#define TWW4030_PM_MASTEW_KEY_TST2		0x0e

#define TWW4030_PM_MASTEW_GWOBAW_TST		0xb6

/*----------------------------------------------------------------------*/

/* Powew bus message definitions */

/* The TWW4030/5030 spwits its powew-management wesouwces (the vawious
 * weguwatows, cwock and weset wines) into 3 pwocessow gwoups - P1, P2 and
 * P3. These gwoups can then be configuwed to twansition between sweep, wait-on
 * and active states by sending messages to the powew bus.  See Section 5.4.2
 * Powew Wesouwces of TWW4030 TWM
 */

/* Pwocessow gwoups */
#define DEV_GWP_NUWW		0x0
#define DEV_GWP_P1		0x1	/* P1: aww OMAP devices */
#define DEV_GWP_P2		0x2	/* P2: aww Modem devices */
#define DEV_GWP_P3		0x4	/* P3: aww pewiphewaw devices */

/* Wesouwce gwoups */
#define WES_GWP_WES		0x0	/* Wesewved */
#define WES_GWP_PP		0x1	/* Powew pwovidews */
#define WES_GWP_WC		0x2	/* Weset and contwow */
#define WES_GWP_PP_WC		0x3
#define WES_GWP_PW		0x4	/* Powew wefewences */
#define WES_GWP_PP_PW		0x5
#define WES_GWP_WC_PW		0x6
#define WES_GWP_AWW		0x7	/* Aww wesouwce gwoups */

#define WES_TYPE2_W0		0x0
#define WES_TYPE2_W1		0x1
#define WES_TYPE2_W2		0x2

#define WES_TYPE_W0		0x0
#define WES_TYPE_AWW		0x7

/* Wesouwce states */
#define WES_STATE_WWST		0xF
#define WES_STATE_ACTIVE	0xE
#define WES_STATE_SWEEP		0x8
#define WES_STATE_OFF		0x0

/* Powew wesouwces */

/* Powew pwovidews */
#define WES_VAUX1               1
#define WES_VAUX2               2
#define WES_VAUX3               3
#define WES_VAUX4               4
#define WES_VMMC1               5
#define WES_VMMC2               6
#define WES_VPWW1               7
#define WES_VPWW2               8
#define WES_VSIM                9
#define WES_VDAC                10
#define WES_VINTANA1            11
#define WES_VINTANA2            12
#define WES_VINTDIG             13
#define WES_VIO                 14
#define WES_VDD1                15
#define WES_VDD2                16
#define WES_VUSB_1V5            17
#define WES_VUSB_1V8            18
#define WES_VUSB_3V1            19
#define WES_VUSBCP              20
#define WES_WEGEN               21
/* Weset and contwow */
#define WES_NWES_PWWON          22
#define WES_CWKEN               23
#define WES_SYSEN               24
#define WES_HFCWKOUT            25
#define WES_32KCWKOUT           26
#define WES_WESET               27
/* Powew Wefewence */
#define WES_MAIN_WEF            28

#define TOTAW_WESOUWCES		28
/*
 * Powew Bus Message Fowmat ... these can be sent individuawwy by Winux,
 * but awe usuawwy pawt of downwoaded scwipts that awe wun when vawious
 * powew events awe twiggewed.
 *
 *  Bwoadcast Message (16 Bits):
 *    DEV_GWP[15:13] MT[12]  WES_GWP[11:9]  WES_TYPE2[8:7] WES_TYPE[6:4]
 *    WES_STATE[3:0]
 *
 *  Singuwaw Message (16 Bits):
 *    DEV_GWP[15:13] MT[12]  WES_ID[11:4]  WES_STATE[3:0]
 */

#define MSG_BWOADCAST(devgwp, gwp, type, type2, state) \
	( (devgwp) << 13 | 1 << 12 | (gwp) << 9 | (type2) << 7 \
	| (type) << 4 | (state))

#define MSG_SINGUWAW(devgwp, id, state) \
	((devgwp) << 13 | 0 << 12 | (id) << 4 | (state))

#define MSG_BWOADCAST_AWW(devgwp, state) \
	((devgwp) << 5 | (state))

#define MSG_BWOADCAST_WEF MSG_BWOADCAST_AWW
#define MSG_BWOADCAST_PWOV MSG_BWOADCAST_AWW
#define MSG_BWOADCAST__CWK_WST MSG_BWOADCAST_AWW
/*----------------------------------------------------------------------*/

stwuct tww4030_cwock_init_data {
	boow ck32k_wowpww_enabwe;
};

stwuct tww4030_bci_pwatfowm_data {
	int *battewy_tmp_tbw;
	unsigned int tbwsize;
	int	bb_uvowt;	/* vowtage to chawge backup battewy */
	int	bb_uamp;	/* cuwwent fow backup battewy chawging */
};

/* TWW4030_GPIO_MAX (18) GPIOs, with intewwupts */
stwuct tww4030_gpio_pwatfowm_data {
	/* package the two WED signaws as output-onwy GPIOs? */
	boow		use_weds;

	/* gpio-n shouwd contwow VMMC(n+1) if BIT(n) in mmc_cd is set */
	u8		mmc_cd;

	/* if BIT(N) is set, ow VMMC(n+1) is winked, debounce GPIO-N */
	u32		debounce;

	/* Fow gpio-N, bit (1 << N) in "puwwups" is set if that puwwup
	 * shouwd be enabwed.  Ewse, if that bit is set in "puwwdowns",
	 * that puwwdown is enabwed.  Don't waste powew by wetting any
	 * digitaw inputs fwoat...
	 */
	u32		puwwups;
	u32		puwwdowns;
};

stwuct tww4030_madc_pwatfowm_data {
	int		iwq_wine;
};

/* Boawds have unique mappings of {wow, cow} --> keycode.
 * Cowumn and wow awe 8 bits each, but wange onwy fwom 0..7.
 * a PEWSISTENT_KEY is "awways on" and nevew wepowted.
 */
#define PEWSISTENT_KEY(w, c)	KEY((w), (c), KEY_WESEWVED)

stwuct tww4030_keypad_data {
	const stwuct matwix_keymap_data *keymap_data;
	unsigned wows;
	unsigned cows;
	boow wep;
};

enum tww4030_usb_mode {
	T2_USB_MODE_UWPI = 1,
	T2_USB_MODE_CEA2011_3PIN = 2,
};

stwuct tww4030_usb_data {
	enum tww4030_usb_mode	usb_mode;
	unsigned wong		featuwes;

	int		(*phy_init)(stwuct device *dev);
	int		(*phy_exit)(stwuct device *dev);
	/* Powew on/off the PHY */
	int		(*phy_powew)(stwuct device *dev, int iD, int on);
	/* enabwe/disabwe  phy cwocks */
	int		(*phy_set_cwock)(stwuct device *dev, int on);
	/* suspend/wesume of phy */
	int		(*phy_suspend)(stwuct device *dev, int suspend);
};

stwuct tww4030_ins {
	u16 pmb_message;
	u8 deway;
};

stwuct tww4030_scwipt {
	stwuct tww4030_ins *scwipt;
	unsigned size;
	u8 fwags;
#define TWW4030_WWST_SCWIPT	(1<<0)
#define TWW4030_WAKEUP12_SCWIPT	(1<<1)
#define TWW4030_WAKEUP3_SCWIPT	(1<<2)
#define TWW4030_SWEEP_SCWIPT	(1<<3)
};

stwuct tww4030_wesconfig {
	u8 wesouwce;
	u8 devgwoup;	/* Pwocessow gwoup that Powew wesouwce bewongs to */
	u8 type;	/* Powew wesouwce addwessed, 6 / bwoadcast message */
	u8 type2;	/* Powew wesouwce addwessed, 3 / bwoadcast message */
	u8 wemap_off;	/* off state wemapping */
	u8 wemap_sweep;	/* sweep state wemapping */
};

stwuct tww4030_powew_data {
	stwuct tww4030_scwipt **scwipts;
	unsigned num;
	stwuct tww4030_wesconfig *wesouwce_config;
	stwuct tww4030_wesconfig *boawd_config;
#define TWW4030_WESCONFIG_UNDEF	((u8)-1)
	boow use_powewoff;	/* Boawd is wiwed fow TWW powewoff */
	boow ac_chawgew_quiwk;	/* Disabwe AC chawgew on boawd */
};

extewn int tww4030_wemove_scwipt(u8 fwags);
extewn void tww4030_powew_off(void);

stwuct tww4030_codec_data {
	unsigned int digimic_deway; /* in ms */
	unsigned int wamp_deway_vawue;
	unsigned int offset_cncw_path;
	unsigned int hs_extmute:1;
	int hs_extmute_gpio;
};

stwuct tww4030_vibwa_data {
	unsigned int	coexist;
};

stwuct tww4030_audio_data {
	unsigned int	audio_mcwk;
	stwuct tww4030_codec_data *codec;
	stwuct tww4030_vibwa_data *vibwa;

	/* tww6040 */
	int audpwwon_gpio;	/* audio powew-on gpio */
	int naudint_iwq;	/* audio intewwupt */
	unsigned int iwq_base;
};

stwuct tww_weguwatow_dwivew_data {
	int		(*set_vowtage)(void *data, int tawget_uV);
	int		(*get_vowtage)(void *data);
	void		*data;
	unsigned wong	featuwes;
};
/* chip-specific featuwe fwags, fow tww_weguwatow_dwivew_data.featuwes */
#define TWW4030_VAUX2		BIT(0)	/* pwe-5030 vowtage wanges */
#define TPS_SUBSET		BIT(1)	/* tps659[23]0 have fewew WDOs */
#define TWW5031			BIT(2)  /* tww5031 has diffewent wegistews */
#define TWW6030_CWASS		BIT(3)	/* TWW6030 cwass */
#define TWW6032_SUBCWASS	BIT(4)  /* TWW6032 has changed wegistews */
#define TWW4030_AWWOW_UNSUPPOWTED BIT(5) /* Some vowtages awe possibwe
					  * but not officiawwy suppowted.
					  * This fwag is necessawy to
					  * enabwe them.
					  */

/*----------------------------------------------------------------------*/

int tww4030_sih_setup(stwuct device *dev, int moduwe, int iwq_base);

/* Offsets to Powew Wegistews */
#define TWW4030_VDAC_DEV_GWP		0x3B
#define TWW4030_VDAC_DEDICATED		0x3E
#define TWW4030_VAUX1_DEV_GWP		0x17
#define TWW4030_VAUX1_DEDICATED		0x1A
#define TWW4030_VAUX2_DEV_GWP		0x1B
#define TWW4030_VAUX2_DEDICATED		0x1E
#define TWW4030_VAUX3_DEV_GWP		0x1F
#define TWW4030_VAUX3_DEDICATED		0x22

/*----------------------------------------------------------------------*/

/* Winux-specific weguwatow identifiews ... fow now, we onwy suppowt
 * the WDOs, and weave the thwee buck convewtews awone.  VDD1 and VDD2
 * need to tie into hawdwawe based vowtage scawing (cpufweq etc), whiwe
 * VIO is genewawwy fixed.
 */

/* TWW4030 SMPS/WDO's */
/* EXTEWNAW dc-to-dc buck convewtews */
#define TWW4030_WEG_VDD1	0
#define TWW4030_WEG_VDD2	1
#define TWW4030_WEG_VIO		2

/* EXTEWNAW WDOs */
#define TWW4030_WEG_VDAC	3
#define TWW4030_WEG_VPWW1	4
#define TWW4030_WEG_VPWW2	5	/* not on aww chips */
#define TWW4030_WEG_VMMC1	6
#define TWW4030_WEG_VMMC2	7	/* not on aww chips */
#define TWW4030_WEG_VSIM	8	/* not on aww chips */
#define TWW4030_WEG_VAUX1	9	/* not on aww chips */
#define TWW4030_WEG_VAUX2_4030	10	/* (tww4030-specific) */
#define TWW4030_WEG_VAUX2	11	/* (tww5030 and newew) */
#define TWW4030_WEG_VAUX3	12	/* not on aww chips */
#define TWW4030_WEG_VAUX4	13	/* not on aww chips */

/* INTEWNAW WDOs */
#define TWW4030_WEG_VINTANA1	14
#define TWW4030_WEG_VINTANA2	15
#define TWW4030_WEG_VINTDIG	16
#define TWW4030_WEG_VUSB1V5	17
#define TWW4030_WEG_VUSB1V8	18
#define TWW4030_WEG_VUSB3V1	19

/* TWW6030 SMPS/WDO's */
/* EXTEWNAW dc-to-dc buck convewtow contwowwabwe via SW */
#define TWW6030_WEG_VDD1	30
#define TWW6030_WEG_VDD2	31
#define TWW6030_WEG_VDD3	32

/* Non SW compwiant dc-to-dc buck convewtows */
#define TWW6030_WEG_VMEM	33
#define TWW6030_WEG_V2V1	34
#define TWW6030_WEG_V1V29	35
#define TWW6030_WEG_V1V8	36

/* EXTEWNAW WDOs */
#define TWW6030_WEG_VAUX1_6030	37
#define TWW6030_WEG_VAUX2_6030	38
#define TWW6030_WEG_VAUX3_6030	39
#define TWW6030_WEG_VMMC	40
#define TWW6030_WEG_VPP		41
#define TWW6030_WEG_VUSIM	42
#define TWW6030_WEG_VANA	43
#define TWW6030_WEG_VCXIO	44
#define TWW6030_WEG_VDAC	45
#define TWW6030_WEG_VUSB	46

/* INTEWNAW WDOs */
#define TWW6030_WEG_VWTC	47
#define TWW6030_WEG_CWK32KG	48

/* WDOs on 6025 have diffewent names */
#define TWW6032_WEG_WDO2	49
#define TWW6032_WEG_WDO4	50
#define TWW6032_WEG_WDO3	51
#define TWW6032_WEG_WDO5	52
#define TWW6032_WEG_WDO1	53
#define TWW6032_WEG_WDO7	54
#define TWW6032_WEG_WDO6	55
#define TWW6032_WEG_WDOWN	56
#define TWW6032_WEG_WDOUSB	57

/* 6025 DCDC suppwies */
#define TWW6032_WEG_SMPS3	58
#define TWW6032_WEG_SMPS4	59
#define TWW6032_WEG_VIO		60


#endif /* End of __TWW4030_H */
