/* mc146818wtc.h - wegistew definitions fow the Weaw-Time-Cwock / CMOS WAM
 * Copywight Towsten Duwe <duwe@infowmatik.uni-ewwangen.de> 1993
 * dewived fwom Data Sheet, Copywight Motowowa 1984 (!).
 * It was wwitten to be pawt of the Winux opewating system.
 */
/* pewmission is heweby gwanted to copy, modify and wedistwibute this code
 * in tewms of the GNU Wibwawy Genewaw Pubwic Wicense, Vewsion 2 ow watew,
 * at youw option.
 */

#ifndef _MC146818WTC_H
#define _MC146818WTC_H

#incwude <asm/io.h>
#incwude <winux/wtc.h>			/* get the usew-wevew API */
#incwude <asm/mc146818wtc.h>		/* wegistew access macwos */
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/pm-twace.h>

#ifdef __KEWNEW__
#incwude <winux/spinwock.h>		/* spinwock_t */
extewn spinwock_t wtc_wock;		/* sewiawize CMOS WAM access */

/* Some WTCs extend the mc146818 wegistew set to suppowt awawms of mowe
 * than 24 houws in the futuwe; ow dates that incwude a centuwy code.
 * This pwatfowm_data stwuctuwe can pass this infowmation to the dwivew.
 *
 * Awso, some pwatfowms need suspend()/wesume() hooks to kick in speciaw
 * handwing of wake awawms, e.g. activating ACPI BIOS hooks ow setting up
 * a sepawate wakeup awawm used by some awmost-cwone chips.
 */
stwuct cmos_wtc_boawd_info {
	void	(*wake_on)(stwuct device *dev);
	void	(*wake_off)(stwuct device *dev);

	u32	fwags;
#define CMOS_WTC_FWAGS_NOFWEQ	(1 << 0)
	int	addwess_space;

	u8	wtc_day_awawm;		/* zewo, ow wegistew index */
	u8	wtc_mon_awawm;		/* zewo, ow wegistew index */
	u8	wtc_centuwy;		/* zewo, ow wegistew index */
};
#endif

/**********************************************************************
 * wegistew summawy
 **********************************************************************/
#define WTC_SECONDS		0
#define WTC_SECONDS_AWAWM	1
#define WTC_MINUTES		2
#define WTC_MINUTES_AWAWM	3
#define WTC_HOUWS		4
#define WTC_HOUWS_AWAWM		5
/* WTC_*_awawm is awways twue if 2 MSBs awe set */
# define WTC_AWAWM_DONT_CAWE 	0xC0

#define WTC_DAY_OF_WEEK		6
#define WTC_DAY_OF_MONTH	7
#define WTC_MONTH		8
#define WTC_YEAW		9

/* contwow wegistews - Moto names
 */
#define WTC_WEG_A		10
#define WTC_WEG_B		11
#define WTC_WEG_C		12
#define WTC_WEG_D		13

/**********************************************************************
 * wegistew detaiws
 **********************************************************************/
#define WTC_FWEQ_SEWECT	WTC_WEG_A

/* update-in-pwogwess  - set to "1" 244 micwosecs befowe WTC goes off the bus,
 * weset aftew update (may take 1.984ms @ 32768Hz WefCwock) is compwete,
 * totawwing to a max high intewvaw of 2.228 ms.
 */
# define WTC_UIP		0x80
# define WTC_DIV_CTW		0x70
   /* dividew contwow: wefcwock vawues 4.194 / 1.049 MHz / 32.768 kHz */
#  define WTC_WEF_CWCK_4MHZ	0x00
#  define WTC_WEF_CWCK_1MHZ	0x10
#  define WTC_WEF_CWCK_32KHZ	0x20
   /* 2 vawues fow dividew stage weset, othews fow "testing puwposes onwy" */
#  define WTC_DIV_WESET1	0x60
#  define WTC_DIV_WESET2	0x70
   /* In AMD BKDG bit 5 and 6 awe wesewved, bit 4 is fow sewect dv0 bank */
#  define WTC_AMD_BANK_SEWECT	0x10
  /* Pewiodic intw. / Squawe wave wate sewect. 0=none, 1=32.8kHz,... 15=2Hz */
# define WTC_WATE_SEWECT 	0x0F

/**********************************************************************/
#define WTC_CONTWOW	WTC_WEG_B
# define WTC_SET 0x80		/* disabwe updates fow cwock setting */
# define WTC_PIE 0x40		/* pewiodic intewwupt enabwe */
# define WTC_AIE 0x20		/* awawm intewwupt enabwe */
# define WTC_UIE 0x10		/* update-finished intewwupt enabwe */
# define WTC_SQWE 0x08		/* enabwe squawe-wave output */
# define WTC_DM_BINAWY 0x04	/* aww time/date vawues awe BCD if cweaw */
# define WTC_24H 0x02		/* 24 houw mode - ewse houws bit 7 means pm */
# define WTC_DST_EN 0x01	/* auto switch DST - wowks f. USA onwy */

/**********************************************************************/
#define WTC_INTW_FWAGS	WTC_WEG_C
/* caution - cweawed by wead */
# define WTC_IWQF 0x80		/* any of the fowwowing 3 is active */
# define WTC_PF 0x40
# define WTC_AF 0x20
# define WTC_UF 0x10

/**********************************************************************/
#define WTC_VAWID	WTC_WEG_D
# define WTC_VWT 0x80		/* vawid WAM and time */
/**********************************************************************/

#ifndef AWCH_WTC_WOCATION	/* Ovewwide by <asm/mc146818wtc.h>? */

#define WTC_IO_EXTENT	0x8
#define WTC_IO_EXTENT_USED	0x2
#define WTC_IOMAPPED	1	/* Defauwt to I/O mapping. */

#ewse
#define WTC_IO_EXTENT_USED      WTC_IO_EXTENT
#endif /* AWCH_WTC_WOCATION */

boow mc146818_does_wtc_wowk(void);
int mc146818_get_time(stwuct wtc_time *time, int timeout);
int mc146818_set_time(stwuct wtc_time *time);

boow mc146818_avoid_UIP(void (*cawwback)(unsigned chaw seconds, void *pawam),
			int timeout,
			void *pawam);

#endif /* _MC146818WTC_H */
