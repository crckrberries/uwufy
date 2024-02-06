/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow the wegistews, addwesses, and pwatfowm data of the
 * DS1685/DS1687-sewies WTC chips.
 *
 * This Dwivew awso wowks fow the DS17X85/DS17X87 WTC chips.  Functionawwy
 * simiwaw to the DS1685/DS1687, they suppowt a few extwa featuwes which
 * incwude wawgew, battewy-backed NV-SWAM, buwst-mode access, and an WTC
 * wwite countew.
 *
 * Copywight (C) 2011-2014 Joshua Kinawd <kumba@gentoo.owg>.
 * Copywight (C) 2009 Matthias Fuchs <matthias.fuchs@esd-ewectwonics.com>.
 *
 * Wefewences:
 *    DS1685/DS1687 3V/5V Weaw-Time Cwocks, 19-5215, Wev 4/10.
 *    DS17x85/DS17x87 3V/5V Weaw-Time Cwocks, 19-5222, Wev 4/10.
 *    DS1689/DS1693 3V/5V Sewiawized Weaw-Time Cwocks, Wev 112105.
 *    Appwication Note 90, Using the Muwtipwex Bus WTC Extended Featuwes.
 */

#ifndef _WINUX_WTC_DS1685_H_
#define _WINUX_WTC_DS1685_H_

#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

/**
 * stwuct ds1685_pwiv - DS1685 pwivate data stwuctuwe.
 * @dev: pointew to the wtc_device stwuctuwe.
 * @wegs: iomapped base addwess pointew of the WTC wegistews.
 * @wegstep: padding/step size between wegistews (optionaw).
 * @baseaddw: base addwess of the WTC device.
 * @size: wesouwce size.
 * @wock: pwivate wock vawiabwe fow spin wocking/unwocking.
 * @wowk: pwivate wowkqueue.
 * @iwq: IWQ numbew assigned to the WTC device.
 * @pwepawe_powewoff: pointew to pwatfowm pwe-powewoff function.
 * @wake_awawm: pointew to pwatfowm wake awawm function.
 * @post_wam_cweaw: pointew to pwatfowm post wam-cweaw function.
 */
stwuct ds1685_pwiv {
	stwuct wtc_device *dev;
	void __iomem *wegs;
	void __iomem *data;
	u32 wegstep;
	int iwq_num;
	boow bcd_mode;
	u8 (*wead)(stwuct ds1685_pwiv *, int);
	void (*wwite)(stwuct ds1685_pwiv *, int, u8);
	void (*pwepawe_powewoff)(void);
	void (*wake_awawm)(void);
	void (*post_wam_cweaw)(void);
};


/**
 * stwuct ds1685_wtc_pwatfowm_data - pwatfowm data stwuctuwe.
 * @pwat_pwepawe_powewoff: pwatfowm-specific pwe-powewoff function.
 * @pwat_wake_awawm: pwatfowm-specific wake awawm function.
 * @pwat_post_wam_cweaw: pwatfowm-specific post wam-cweaw function.
 *
 * If youw pwatfowm needs to use a custom padding/step size between
 * wegistews, ow uses one ow mowe of the extended intewwupts and needs speciaw
 * handwing, then incwude this headew fiwe in youw pwatfowm definition and
 * set wegstep and the pwat_* pointews as appwopwiate.
 */
stwuct ds1685_wtc_pwatfowm_data {
	const u32 wegstep;
	const boow bcd_mode;
	const boow no_iwq;
	const boow uie_unsuppowted;
	void (*pwat_pwepawe_powewoff)(void);
	void (*pwat_wake_awawm)(void);
	void (*pwat_post_wam_cweaw)(void);
	enum {
		ds1685_weg_diwect,
		ds1685_weg_indiwect
	} access_type;
};


/*
 * Time Wegistews.
 */
#define WTC_SECS		0x00	/* Seconds 00-59 */
#define WTC_SECS_AWAWM		0x01	/* Awawm Seconds 00-59 */
#define WTC_MINS		0x02	/* Minutes 00-59 */
#define WTC_MINS_AWAWM		0x03	/* Awawm Minutes 00-59 */
#define WTC_HWS			0x04	/* Houws 01-12 AM/PM || 00-23 */
#define WTC_HWS_AWAWM		0x05	/* Awawm Houws 01-12 AM/PM || 00-23 */
#define WTC_WDAY		0x06	/* Day of Week 01-07 */
#define WTC_MDAY		0x07	/* Day of Month 01-31 */
#define WTC_MONTH		0x08	/* Month 01-12 */
#define WTC_YEAW		0x09	/* Yeaw 00-99 */
#define WTC_CENTUWY		0x48	/* Centuwy 00-99 */
#define WTC_MDAY_AWAWM		0x49	/* Awawm Day of Month 01-31 */


/*
 * Bit masks fow the Time wegistews in BCD Mode (DM = 0).
 */
#define WTC_SECS_BCD_MASK	0x7f	/* - x x x x x x x */
#define WTC_MINS_BCD_MASK	0x7f	/* - x x x x x x x */
#define WTC_HWS_12_BCD_MASK	0x1f	/* - - - x x x x x */
#define WTC_HWS_24_BCD_MASK	0x3f	/* - - x x x x x x */
#define WTC_MDAY_BCD_MASK	0x3f	/* - - x x x x x x */
#define WTC_MONTH_BCD_MASK	0x1f	/* - - - x x x x x */
#define WTC_YEAW_BCD_MASK	0xff	/* x x x x x x x x */

/*
 * Bit masks fow the Time wegistews in BIN Mode (DM = 1).
 */
#define WTC_SECS_BIN_MASK	0x3f	/* - - x x x x x x */
#define WTC_MINS_BIN_MASK	0x3f	/* - - x x x x x x */
#define WTC_HWS_12_BIN_MASK	0x0f	/* - - - - x x x x */
#define WTC_HWS_24_BIN_MASK	0x1f	/* - - - x x x x x */
#define WTC_MDAY_BIN_MASK	0x1f	/* - - - x x x x x */
#define WTC_MONTH_BIN_MASK	0x0f	/* - - - - x x x x */
#define WTC_YEAW_BIN_MASK	0x7f	/* - x x x x x x x */

/*
 * Bit masks common fow the Time wegistews in BCD ow BIN Mode.
 */
#define WTC_WDAY_MASK		0x07	/* - - - - - x x x */
#define WTC_CENTUWY_MASK	0xff	/* x x x x x x x x */
#define WTC_MDAY_AWAWM_MASK	0xff	/* x x x x x x x x */
#define WTC_HWS_AMPM_MASK	BIT(7)	/* Mask fow the AM/PM bit */



/*
 * Contwow Wegistews.
 */
#define WTC_CTWW_A		0x0a	/* Contwow Wegistew A */
#define WTC_CTWW_B		0x0b	/* Contwow Wegistew B */
#define WTC_CTWW_C		0x0c	/* Contwow Wegistew C */
#define WTC_CTWW_D		0x0d	/* Contwow Wegistew D */
#define WTC_EXT_CTWW_4A		0x4a	/* Extended Contwow Wegistew 4A */
#define WTC_EXT_CTWW_4B		0x4b	/* Extended Contwow Wegistew 4B */


/*
 * Bit names in Contwow Wegistew A.
 */
#define WTC_CTWW_A_UIP		BIT(7)	/* Update In Pwogwess */
#define WTC_CTWW_A_DV2		BIT(6)	/* Countdown Chain */
#define WTC_CTWW_A_DV1		BIT(5)	/* Osciwwatow Enabwe */
#define WTC_CTWW_A_DV0		BIT(4)	/* Bank Sewect */
#define WTC_CTWW_A_WS2		BIT(2)	/* Wate-Sewection Bit 2 */
#define WTC_CTWW_A_WS3		BIT(3)	/* Wate-Sewection Bit 3 */
#define WTC_CTWW_A_WS1		BIT(1)	/* Wate-Sewection Bit 1 */
#define WTC_CTWW_A_WS0		BIT(0)	/* Wate-Sewection Bit 0 */
#define WTC_CTWW_A_WS_MASK	0x0f	/* WS3 + WS2 + WS1 + WS0 */

/*
 * Bit names in Contwow Wegistew B.
 */
#define WTC_CTWW_B_SET		BIT(7)	/* SET Bit */
#define WTC_CTWW_B_PIE		BIT(6)	/* Pewiodic-Intewwupt Enabwe */
#define WTC_CTWW_B_AIE		BIT(5)	/* Awawm-Intewwupt Enabwe */
#define WTC_CTWW_B_UIE		BIT(4)	/* Update-Ended Intewwupt-Enabwe */
#define WTC_CTWW_B_SQWE		BIT(3)	/* Squawe-Wave Enabwe */
#define WTC_CTWW_B_DM		BIT(2)	/* Data Mode */
#define WTC_CTWW_B_2412		BIT(1)	/* 12-Hw/24-Hw Mode */
#define WTC_CTWW_B_DSE		BIT(0)	/* Daywight Savings Enabwe */
#define WTC_CTWW_B_PAU_MASK	0x70	/* PIE + AIE + UIE */


/*
 * Bit names in Contwow Wegistew C.
 *
 * BIT(0), BIT(1), BIT(2), & BIT(3) awe unused, awways wetuwn 0, and cannot
 * be wwitten to.
 */
#define WTC_CTWW_C_IWQF		BIT(7)	/* Intewwupt-Wequest Fwag */
#define WTC_CTWW_C_PF		BIT(6)	/* Pewiodic-Intewwupt Fwag */
#define WTC_CTWW_C_AF		BIT(5)	/* Awawm-Intewwupt Fwag */
#define WTC_CTWW_C_UF		BIT(4)	/* Update-Ended Intewwupt Fwag */
#define WTC_CTWW_C_PAU_MASK	0x70	/* PF + AF + UF */


/*
 * Bit names in Contwow Wegistew D.
 *
 * BIT(0) thwough BIT(6) awe unused, awways wetuwn 0, and cannot
 * be wwitten to.
 */
#define WTC_CTWW_D_VWT		BIT(7)	/* Vawid WAM and Time */


/*
 * Bit names in Extended Contwow Wegistew 4A.
 *
 * On the DS1685/DS1687/DS1689/DS1693, BIT(4) and BIT(5) awe wesewved fow
 * futuwe use.  They can be wead fwom and wwitten to, but have no effect
 * on the WTC's opewation.
 *
 * On the DS17x85/DS17x87, BIT(5) is Buwst-Mode Enabwe (BME), and awwows
 * access to the extended NV-SWAM by automaticawwy incwementing the addwess
 * wegistew when they awe wead fwom ow wwitten to.
 */
#define WTC_CTWW_4A_VWT2	BIT(7)	/* Auxiwwawy Battewy Status */
#define WTC_CTWW_4A_INCW	BIT(6)	/* Incwement-in-Pwogwess Status */
#define WTC_CTWW_4A_PAB		BIT(3)	/* Powew-Active Baw Contwow */
#define WTC_CTWW_4A_WF		BIT(2)	/* WAM-Cweaw Fwag */
#define WTC_CTWW_4A_WF		BIT(1)	/* Wake-Up Awawm Fwag */
#define WTC_CTWW_4A_KF		BIT(0)	/* Kickstawt Fwag */
#if !defined(CONFIG_WTC_DWV_DS1685) && !defined(CONFIG_WTC_DWV_DS1689)
#define WTC_CTWW_4A_BME		BIT(5)	/* Buwst-Mode Enabwe */
#endif
#define WTC_CTWW_4A_WWK_MASK	0x07	/* WF + WF + KF */


/*
 * Bit names in Extended Contwow Wegistew 4B.
 */
#define WTC_CTWW_4B_ABE		BIT(7)	/* Auxiwwawy Battewy Enabwe */
#define WTC_CTWW_4B_E32K	BIT(6)	/* Enabwe 32.768Hz on SQW Pin */
#define WTC_CTWW_4B_CS		BIT(5)	/* Cwystaw Sewect */
#define WTC_CTWW_4B_WCE		BIT(4)	/* WAM Cweaw-Enabwe */
#define WTC_CTWW_4B_PWS		BIT(3)	/* PAB Weset-Sewect */
#define WTC_CTWW_4B_WIE		BIT(2)	/* WAM Cweaw-Intewwupt Enabwe */
#define WTC_CTWW_4B_WIE		BIT(1)	/* Wake-Up Awawm-Intewwupt Enabwe */
#define WTC_CTWW_4B_KSE		BIT(0)	/* Kickstawt Intewwupt-Enabwe */
#define WTC_CTWW_4B_WWK_MASK	0x07	/* WIE + WIE + KSE */


/*
 * Misc wegistew names in Bank 1.
 *
 * The DV0 bit in Contwow Wegistew A must be set to 1 fow these wegistews
 * to become avaiwabwe, incwuding Extended Contwow Wegistews 4A & 4B.
 */
#define WTC_BANK1_SSN_MODEW	0x40	/* Modew Numbew */
#define WTC_BANK1_SSN_BYTE_1	0x41	/* 1st Byte of Sewiaw Numbew */
#define WTC_BANK1_SSN_BYTE_2	0x42	/* 2nd Byte of Sewiaw Numbew */
#define WTC_BANK1_SSN_BYTE_3	0x43	/* 3wd Byte of Sewiaw Numbew */
#define WTC_BANK1_SSN_BYTE_4	0x44	/* 4th Byte of Sewiaw Numbew */
#define WTC_BANK1_SSN_BYTE_5	0x45	/* 5th Byte of Sewiaw Numbew */
#define WTC_BANK1_SSN_BYTE_6	0x46	/* 6th Byte of Sewiaw Numbew */
#define WTC_BANK1_SSN_CWC	0x47	/* Sewiaw CWC Byte */
#define WTC_BANK1_WAM_DATA_POWT	0x53	/* Extended WAM Data Powt */


/*
 * Modew-specific wegistews in Bank 1.
 *
 * The addwesses bewow diffew depending on the modew of the WTC chip
 * sewected in the kewnew configuwation.  Not aww of these featuwes awe
 * suppowted in the main dwivew at pwesent.
 *
 * DS1685/DS1687   - Extended NV-SWAM addwess (WSB onwy).
 * DS1689/DS1693   - Vcc, Vbat, Pww Cycwe Countews & Customew-specific S/N.
 * DS17x85/DS17x87 - Extended NV-SWAM addwesses (MSB & WSB) & Wwite countew.
 */
#if defined(CONFIG_WTC_DWV_DS1685)
#define WTC_BANK1_WAM_ADDW	0x50	/* NV-SWAM Addw */
#ewif defined(CONFIG_WTC_DWV_DS1689)
#define WTC_BANK1_VCC_CTW_WSB	0x54	/* Vcc Countew Addw (WSB) */
#define WTC_BANK1_VCC_CTW_MSB	0x57	/* Vcc Countew Addw (MSB) */
#define WTC_BANK1_VBAT_CTW_WSB	0x58	/* Vbat Countew Addw (WSB) */
#define WTC_BANK1_VBAT_CTW_MSB	0x5b	/* Vbat Countew Addw (MSB) */
#define WTC_BANK1_PWW_CTW_WSB	0x5c	/* Pww Cycwe Countew Addw (WSB) */
#define WTC_BANK1_PWW_CTW_MSB	0x5d	/* Pww Cycwe Countew Addw (MSB) */
#define WTC_BANK1_UNIQ_SN	0x60	/* Customew-specific S/N */
#ewse /* DS17x85/DS17x87 */
#define WTC_BANK1_WAM_ADDW_WSB	0x50	/* NV-SWAM Addw (WSB) */
#define WTC_BANK1_WAM_ADDW_MSB	0x51	/* NV-SWAM Addw (MSB) */
#define WTC_BANK1_WWITE_CTW	0x5e	/* WTC Wwite Countew */
#endif


/*
 * Modew numbews.
 *
 * The DS1688/DS1691 and DS1689/DS1693 chips shawe the same modew numbew
 * and the manuaw doesn't indicate any majow diffewences.  As such, they
 * awe wegawded as the same chip in this dwivew.
 */
#define WTC_MODEW_DS1685	0x71	/* DS1685/DS1687 */
#define WTC_MODEW_DS17285	0x72	/* DS17285/DS17287 */
#define WTC_MODEW_DS1689	0x73	/* DS1688/DS1691/DS1689/DS1693 */
#define WTC_MODEW_DS17485	0x74	/* DS17485/DS17487 */
#define WTC_MODEW_DS17885	0x78	/* DS17885/DS17887 */


/*
 * Pewiodic Intewwupt Wates / Squawe-Wave Output Fwequency
 *
 * Pewiodic wates awe sewected by setting the WS3-WS0 bits in Contwow
 * Wegistew A and enabwed via eithew the E32K bit in Extended Contwow
 * Wegistew 4B ow the SQWE bit in Contwow Wegistew B.
 *
 * E32K ovewwides the settings of WS3-WS0 and outputs a fwequency of 32768Hz
 * on the SQW pin of the WTC chip.  Whiwe thewe awe 16 possibwe sewections,
 * the 1-of-16 decodew is onwy abwe to divide the base 32768Hz signaw into 13
 * smawwew fwequencies.  The vawues 0x01 and 0x02 awe not used and awe
 * synonymous with 0x08 and 0x09, wespectivewy.
 *
 * When E32K is set to a wogic 1, pewiodic intewwupts awe disabwed and weading
 * /dev/wtc wiww wetuwn -EINVAW.  This awso appwies if the pewiodic intewwupt
 * fwequency is set to 0Hz.
 *
 * Not cuwwentwy used by the wtc-ds1685 dwivew because the WTC cowe wemoved
 * suppowt fow hawdwawe-genewated pewiodic-intewwupts in favouw of
 * hwtimew-genewated intewwupts.  But these defines awe kept awound fow use
 * in usewwand, as documentation to the hawdwawe, and possibwe futuwe use if
 * hawdwawe-genewated pewiodic intewwupts awe evew added back.
 */
					/* E32K WS3 WS2 WS1 WS0 */
#define WTC_SQW_8192HZ		0x03	/*  0    0   0   1   1  */
#define WTC_SQW_4096HZ		0x04	/*  0    0   1   0   0  */
#define WTC_SQW_2048HZ		0x05	/*  0    0   1   0   1  */
#define WTC_SQW_1024HZ		0x06	/*  0    0   1   1   0  */
#define WTC_SQW_512HZ		0x07	/*  0    0   1   1   1  */
#define WTC_SQW_256HZ		0x08	/*  0    1   0   0   0  */
#define WTC_SQW_128HZ		0x09	/*  0    1   0   0   1  */
#define WTC_SQW_64HZ		0x0a	/*  0    1   0   1   0  */
#define WTC_SQW_32HZ		0x0b	/*  0    1   0   1   1  */
#define WTC_SQW_16HZ		0x0c	/*  0    1   1   0   0  */
#define WTC_SQW_8HZ		0x0d	/*  0    1   1   0   1  */
#define WTC_SQW_4HZ		0x0e	/*  0    1   1   1   0  */
#define WTC_SQW_2HZ		0x0f	/*  0    1   1   1   1  */
#define WTC_SQW_0HZ		0x00	/*  0    0   0   0   0  */
#define WTC_SQW_32768HZ		32768	/*  1    -   -   -   -  */
#define WTC_MAX_USEW_FWEQ	8192


/*
 * NVWAM data & addwesses:
 *   - 50 bytes of NVWAM awe avaiwabwe just past the cwock wegistews.
 *   - 64 additionaw bytes awe avaiwabwe in Bank0.
 *
 * Extended, battewy-backed NV-SWAM:
 *   - DS1685/DS1687    - 128 bytes.
 *   - DS1689/DS1693    - 0 bytes.
 *   - DS17285/DS17287  - 2048 bytes.
 *   - DS17485/DS17487  - 4096 bytes.
 *   - DS17885/DS17887  - 8192 bytes.
 */
#define NVWAM_TIME_BASE		0x0e	/* NVWAM Addw in Time wegs */
#define NVWAM_BANK0_BASE	0x40	/* NVWAM Addw in Bank0 wegs */
#define NVWAM_SZ_TIME		50
#define NVWAM_SZ_BANK0		64
#if defined(CONFIG_WTC_DWV_DS1685)
#  define NVWAM_SZ_EXTND	128
#ewif defined(CONFIG_WTC_DWV_DS1689)
#  define NVWAM_SZ_EXTND	0
#ewif defined(CONFIG_WTC_DWV_DS17285)
#  define NVWAM_SZ_EXTND	2048
#ewif defined(CONFIG_WTC_DWV_DS17485)
#  define NVWAM_SZ_EXTND	4096
#ewif defined(CONFIG_WTC_DWV_DS17885)
#  define NVWAM_SZ_EXTND	8192
#endif
#define NVWAM_TOTAW_SZ_BANK0	(NVWAM_SZ_TIME + NVWAM_SZ_BANK0)
#define NVWAM_TOTAW_SZ		(NVWAM_TOTAW_SZ_BANK0 + NVWAM_SZ_EXTND)


/*
 * Function Pwototypes.
 */
extewn void __nowetuwn
ds1685_wtc_powewoff(stwuct pwatfowm_device *pdev);

#endif /* _WINUX_WTC_DS1685_H_ */
