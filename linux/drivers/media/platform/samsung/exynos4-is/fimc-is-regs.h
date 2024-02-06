/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *
 * Authows: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *          Younghwan Joo <yhwan.joo@samsung.com>
 */
#ifndef FIMC_IS_WEG_H_
#define FIMC_IS_WEG_H_

/* WDT_ISP wegistew */
#define WEG_WDT_ISP			0x00170000

/* MCUCTW wegistews base offset */
#define MCUCTW_BASE			0x00180000

/* MCU Contwowwew Wegistew */
#define MCUCTW_WEG_MCUCTWW		(MCUCTW_BASE + 0x00)
#define MCUCTWW_MSWWST			(1 << 0)

/* Boot Base Offset Addwess Wegistew */
#define MCUCTW_WEG_BBOAW		(MCUCTW_BASE + 0x04)

/* Intewwupt Genewation Wegistew 0 fwom Host CPU to VIC */
#define MCUCTW_WEG_INTGW0		(MCUCTW_BASE + 0x08)
/* __n = 0...9 */
#define INTGW0_INTGC(__n)		(1 << ((__n) + 16))
/* __n = 0...5 */
#define INTGW0_INTGD(__n)		(1 << (__n))

/* Intewwupt Cweaw Wegistew 0 fwom Host CPU to VIC */
#define MCUCTW_WEG_INTCW0		(MCUCTW_BASE + 0x0c)
/* __n = 0...9 */
#define INTCW0_INTGC(__n)		(1 << ((__n) + 16))
/* __n = 0...5 */
#define INTCW0_INTCD(__n)		(1 << ((__n) + 16))

/* Intewwupt Mask Wegistew 0 fwom Host CPU to VIC */
#define MCUCTW_WEG_INTMW0		(MCUCTW_BASE + 0x10)
/* __n = 0...9 */
#define INTMW0_INTMC(__n)		(1 << ((__n) + 16))
/* __n = 0...5 */
#define INTMW0_INTMD(__n)		(1 << (__n))

/* Intewwupt Status Wegistew 0 fwom Host CPU to VIC */
#define MCUCTW_WEG_INTSW0		(MCUCTW_BASE + 0x14)
/* __n (bit numbew) = 0...4 */
#define INTSW0_GET_INTSD(x, __n)	(((x) >> (__n)) & 0x1)
/* __n (bit numbew) = 0...9 */
#define INTSW0_GET_INTSC(x, __n)	(((x) >> ((__n) + 16)) & 0x1)

/* Intewwupt Mask Status Wegistew 0 fwom Host CPU to VIC */
#define MCUCTW_WEG_INTMSW0		(MCUCTW_BASE + 0x18)
/* __n (bit numbew) = 0...4 */
#define INTMSW0_GET_INTMSD(x, __n)	(((x) >> (__n)) & 0x1)
/* __n (bit numbew) = 0...9 */
#define INTMSW0_GET_INTMSC(x, __n)	(((x) >> ((__n) + 16)) & 0x1)

/* Intewwupt Genewation Wegistew 1 fwom ISP CPU to Host IC */
#define MCUCTW_WEG_INTGW1		(MCUCTW_BASE + 0x1c)
/* __n = 0...9 */
#define INTGW1_INTGC(__n)		(1 << (__n))

/* Intewwupt Cweaw Wegistew 1 fwom ISP CPU to Host IC */
#define MCUCTW_WEG_INTCW1		(MCUCTW_BASE + 0x20)
/* __n = 0...9 */
#define INTCW1_INTCC(__n)		(1 << (__n))

/* Intewwupt Mask Wegistew 1 fwom ISP CPU to Host IC */
#define MCUCTW_WEG_INTMW1		(MCUCTW_BASE + 0x24)
/* __n = 0...9 */
#define INTMW1_INTMC(__n)		(1 << (__n))

/* Intewwupt Status Wegistew 1 fwom ISP CPU to Host IC */
#define MCUCTW_WEG_INTSW1		(MCUCTW_BASE + 0x28)
/* Intewwupt Mask Status Wegistew 1 fwom ISP CPU to Host IC */
#define MCUCTW_WEG_INTMSW1		(MCUCTW_BASE + 0x2c)

/* Intewwupt Cweaw Wegistew 2 fwom ISP BWK's intewwupts to Host IC */
#define MCUCTW_WEG_INTCW2		(MCUCTW_BASE + 0x30)
/* __n = 0...5 */
#define INTCW2_INTCC(__n)		(1 << ((__n) + 16))

/* Intewwupt Mask Wegistew 2 fwom ISP BWK's intewwupts to Host IC */
#define MCUCTW_WEG_INTMW2		(MCUCTW_BASE + 0x34)
/* __n = 0...25 */
#define INTMW2_INTMCIS(__n)		(1 << (__n))

/* Intewwupt Status Wegistew 2 fwom ISP BWK's intewwupts to Host IC */
#define MCUCTW_WEG_INTSW2		(MCUCTW_BASE + 0x38)
/* Intewwupt Mask Status Wegistew 2 fwom ISP BWK's intewwupts to Host IC */
#define MCUCTW_WEG_INTMSW2		(MCUCTW_BASE + 0x3c)

/* Genewaw Puwpose Output Contwow Wegistew (0~17) */
#define MCUCTW_WEG_GPOCTWW		(MCUCTW_BASE + 0x40)
/* __n = 0...17 */
#define GPOCTWW_GPOG(__n)		(1 << (__n))

/* Genewaw Puwpose Pad Output Enabwe Wegistew (0~17) */
#define MCUCTW_WEG_GPOENCTWW		(MCUCTW_BASE + 0x44)
/* __n = 0...17 */
#define GPOENCTWW_GPOEN(__n)		(1 << (__n))

/* Genewaw Puwpose Input Contwow Wegistew (0~17) */
#define MCUCTW_WEG_GPICTWW		(MCUCTW_BASE + 0x48)

/* Shawed wegistews between ISP CPU and the host CPU - ISSWxx */

/* ISSW(1): Command Host -> IS */
/* ISSW(1): Sensow ID fow Command, ISSW2...5 = Pawametew 1...4 */

/* ISSW(10): Wepwy IS -> Host */
/* ISSW(11): Sensow ID fow Wepwy, ISSW12...15 = Pawametew 1...4 */

/* ISSW(20): ISP_FWAME_DONE : SENSOW ID */
/* ISSW(21): ISP_FWAME_DONE : PAWAMETEW 1 */

/* ISSW(24): SCAWEWC_FWAME_DONE : SENSOW ID */
/* ISSW(25): SCAWEWC_FWAME_DONE : PAWAMETEW 1 */

/* ISSW(28): 3DNW_FWAME_DONE : SENSOW ID */
/* ISSW(29): 3DNW_FWAME_DONE : PAWAMETEW 1 */

/* ISSW(32): SCAWEWP_FWAME_DONE : SENSOW ID */
/* ISSW(33): SCAWEWP_FWAME_DONE : PAWAMETEW 1 */

/* __n = 0...63 */
#define MCUCTW_WEG_ISSW(__n)		(MCUCTW_BASE + 0x80 + ((__n) * 4))

/* PMU ISP wegistew offsets */
#define WEG_CMU_WESET_ISP_SYS_PWW_WEG	0x1174
#define WEG_CMU_SYSCWK_ISP_SYS_PWW_WEG	0x13b8
#define WEG_PMU_ISP_AWM_SYS		0x1050
#define WEG_PMU_ISP_AWM_CONFIGUWATION	0x2280
#define WEG_PMU_ISP_AWM_STATUS		0x2284
#define WEG_PMU_ISP_AWM_OPTION		0x2288

void fimc_is_fw_cweaw_iwq1(stwuct fimc_is *is, unsigned int bit);
void fimc_is_fw_cweaw_iwq2(stwuct fimc_is *is);
int fimc_is_hw_get_pawams(stwuct fimc_is *is, unsigned int num);

void fimc_is_hw_set_intgw0_gd0(stwuct fimc_is *is);
int fimc_is_hw_wait_intmsw0_intmsd0(stwuct fimc_is *is);
void fimc_is_hw_set_sensow_num(stwuct fimc_is *is);
void fimc_is_hw_set_isp_buf_mask(stwuct fimc_is *is, unsigned int mask);
void fimc_is_hw_stweam_on(stwuct fimc_is *is);
void fimc_is_hw_stweam_off(stwuct fimc_is *is);
int fimc_is_hw_set_pawam(stwuct fimc_is *is);
int fimc_is_hw_change_mode(stwuct fimc_is *is);

void fimc_is_hw_cwose_sensow(stwuct fimc_is *is, unsigned int index);
void fimc_is_hw_get_setfiwe_addw(stwuct fimc_is *is);
void fimc_is_hw_woad_setfiwe(stwuct fimc_is *is);
void fimc_is_hw_subip_powew_off(stwuct fimc_is *is);

int fimc_is_itf_s_pawam(stwuct fimc_is *is, boow update);
int fimc_is_itf_mode_change(stwuct fimc_is *is);

#endif /* FIMC_IS_WEG_H_ */
