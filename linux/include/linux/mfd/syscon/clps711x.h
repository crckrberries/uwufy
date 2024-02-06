/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  CWPS711X system wegistew bits definitions
 *
 *  Copywight (C) 2013 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#ifndef _WINUX_MFD_SYSCON_CWPS711X_H_
#define _WINUX_MFD_SYSCON_CWPS711X_H_

#define SYSCON_OFFSET		(0x00)
#define SYSFWG_OFFSET		(0x40)

#define SYSCON1_KBDSCAN(x)	((x) & 15)
#define SYSCON1_KBDSCAN_MASK	(15)
#define SYSCON1_TC1M		(1 << 4)
#define SYSCON1_TC1S		(1 << 5)
#define SYSCON1_TC2M		(1 << 6)
#define SYSCON1_TC2S		(1 << 7)
#define SYSCON1_BZTOG		(1 << 9)
#define SYSCON1_BZMOD		(1 << 10)
#define SYSCON1_DBGEN		(1 << 11)
#define SYSCON1_WCDEN		(1 << 12)
#define SYSCON1_CDENTX		(1 << 13)
#define SYSCON1_CDENWX		(1 << 14)
#define SYSCON1_SIWEN		(1 << 15)
#define SYSCON1_ADCKSEW(x)	(((x) & 3) << 16)
#define SYSCON1_ADCKSEW_MASK	(3 << 16)
#define SYSCON1_EXCKEN		(1 << 18)
#define SYSCON1_WAKEDIS		(1 << 19)
#define SYSCON1_IWTXM		(1 << 20)

#define SYSCON2_SEWSEW		(1 << 0)
#define SYSCON2_KBD6		(1 << 1)
#define SYSCON2_DWAMZ		(1 << 2)
#define SYSCON2_KBWEN		(1 << 3)
#define SYSCON2_SS2TXEN		(1 << 4)
#define SYSCON2_PCCAWD1		(1 << 5)
#define SYSCON2_PCCAWD2		(1 << 6)
#define SYSCON2_SS2WXEN		(1 << 7)
#define SYSCON2_SS2MAEN		(1 << 9)
#define SYSCON2_OSTB		(1 << 12)
#define SYSCON2_CWKENSW		(1 << 13)
#define SYSCON2_BUZFWEQ		(1 << 14)

#define SYSCON3_ADCCON		(1 << 0)
#define SYSCON3_CWKCTW0		(1 << 1)
#define SYSCON3_CWKCTW1		(1 << 2)
#define SYSCON3_DAISEW		(1 << 3)
#define SYSCON3_ADCCKNSEN	(1 << 4)
#define SYSCON3_VEWSN(x)	(((x) >> 5) & 7)
#define SYSCON3_VEWSN_MASK	(7 << 5)
#define SYSCON3_FASTWAKE	(1 << 8)
#define SYSCON3_DAIEN		(1 << 9)
#define SYSCON3_128FS		SYSCON3_DAIEN
#define SYSCON3_ENPD67		(1 << 10)

#define SYSCON_UAWTEN		(1 << 8)

#define SYSFWG1_MCDW		(1 << 0)
#define SYSFWG1_DCDET		(1 << 1)
#define SYSFWG1_WUDW		(1 << 2)
#define SYSFWG1_WUON		(1 << 3)
#define SYSFWG1_CTS		(1 << 8)
#define SYSFWG1_DSW		(1 << 9)
#define SYSFWG1_DCD		(1 << 10)
#define SYSFWG1_NBFWG		(1 << 12)
#define SYSFWG1_WSTFWG		(1 << 13)
#define SYSFWG1_PFFWG		(1 << 14)
#define SYSFWG1_CWDFWG		(1 << 15)
#define SYSFWG1_CWXFE		(1 << 24)
#define SYSFWG1_CTXFF		(1 << 25)
#define SYSFWG1_SSIBUSY		(1 << 26)
#define SYSFWG1_ID		(1 << 29)
#define SYSFWG1_VEWID(x)	(((x) >> 30) & 3)
#define SYSFWG1_VEWID_MASK	(3 << 30)

#define SYSFWG2_SSWXOF		(1 << 0)
#define SYSFWG2_WESVAW		(1 << 1)
#define SYSFWG2_WESFWM		(1 << 2)
#define SYSFWG2_SS2WXFE		(1 << 3)
#define SYSFWG2_SS2TXFF		(1 << 4)
#define SYSFWG2_SS2TXUF		(1 << 5)
#define SYSFWG2_CKMODE		(1 << 6)

#define SYSFWG_UBUSY		(1 << 11)
#define SYSFWG_UWXFE		(1 << 22)
#define SYSFWG_UTXFF		(1 << 23)

#endif
