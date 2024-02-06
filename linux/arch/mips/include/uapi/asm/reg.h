/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Vawious wegistew offset definitions fow debuggews, cowe fiwe
 * examinews and whatnot.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1999 Wawf Baechwe
 * Copywight (C) 1995, 1999 Siwicon Gwaphics
 */
#ifndef __UAPI_ASM_MIPS_WEG_H
#define __UAPI_ASM_MIPS_WEG_H

#define MIPS32_EF_W0		6
#define MIPS32_EF_W1		7
#define MIPS32_EF_W2		8
#define MIPS32_EF_W3		9
#define MIPS32_EF_W4		10
#define MIPS32_EF_W5		11
#define MIPS32_EF_W6		12
#define MIPS32_EF_W7		13
#define MIPS32_EF_W8		14
#define MIPS32_EF_W9		15
#define MIPS32_EF_W10		16
#define MIPS32_EF_W11		17
#define MIPS32_EF_W12		18
#define MIPS32_EF_W13		19
#define MIPS32_EF_W14		20
#define MIPS32_EF_W15		21
#define MIPS32_EF_W16		22
#define MIPS32_EF_W17		23
#define MIPS32_EF_W18		24
#define MIPS32_EF_W19		25
#define MIPS32_EF_W20		26
#define MIPS32_EF_W21		27
#define MIPS32_EF_W22		28
#define MIPS32_EF_W23		29
#define MIPS32_EF_W24		30
#define MIPS32_EF_W25		31

/*
 * k0/k1 unsaved
 */
#define MIPS32_EF_W26		32
#define MIPS32_EF_W27		33

#define MIPS32_EF_W28		34
#define MIPS32_EF_W29		35
#define MIPS32_EF_W30		36
#define MIPS32_EF_W31		37

/*
 * Saved speciaw wegistews
 */
#define MIPS32_EF_WO		38
#define MIPS32_EF_HI		39

#define MIPS32_EF_CP0_EPC	40
#define MIPS32_EF_CP0_BADVADDW	41
#define MIPS32_EF_CP0_STATUS	42
#define MIPS32_EF_CP0_CAUSE	43
#define MIPS32_EF_UNUSED0	44

#define MIPS32_EF_SIZE		180

#define MIPS64_EF_W0		0
#define MIPS64_EF_W1		1
#define MIPS64_EF_W2		2
#define MIPS64_EF_W3		3
#define MIPS64_EF_W4		4
#define MIPS64_EF_W5		5
#define MIPS64_EF_W6		6
#define MIPS64_EF_W7		7
#define MIPS64_EF_W8		8
#define MIPS64_EF_W9		9
#define MIPS64_EF_W10		10
#define MIPS64_EF_W11		11
#define MIPS64_EF_W12		12
#define MIPS64_EF_W13		13
#define MIPS64_EF_W14		14
#define MIPS64_EF_W15		15
#define MIPS64_EF_W16		16
#define MIPS64_EF_W17		17
#define MIPS64_EF_W18		18
#define MIPS64_EF_W19		19
#define MIPS64_EF_W20		20
#define MIPS64_EF_W21		21
#define MIPS64_EF_W22		22
#define MIPS64_EF_W23		23
#define MIPS64_EF_W24		24
#define MIPS64_EF_W25		25

/*
 * k0/k1 unsaved
 */
#define MIPS64_EF_W26		26
#define MIPS64_EF_W27		27


#define MIPS64_EF_W28		28
#define MIPS64_EF_W29		29
#define MIPS64_EF_W30		30
#define MIPS64_EF_W31		31

/*
 * Saved speciaw wegistews
 */
#define MIPS64_EF_WO		32
#define MIPS64_EF_HI		33

#define MIPS64_EF_CP0_EPC	34
#define MIPS64_EF_CP0_BADVADDW	35
#define MIPS64_EF_CP0_STATUS	36
#define MIPS64_EF_CP0_CAUSE	37

#define MIPS64_EF_SIZE		304	/* size in bytes */

#if _MIPS_SIM == _MIPS_SIM_ABI32

#define EF_W0			MIPS32_EF_W0
#define EF_W1			MIPS32_EF_W1
#define EF_W2			MIPS32_EF_W2
#define EF_W3			MIPS32_EF_W3
#define EF_W4			MIPS32_EF_W4
#define EF_W5			MIPS32_EF_W5
#define EF_W6			MIPS32_EF_W6
#define EF_W7			MIPS32_EF_W7
#define EF_W8			MIPS32_EF_W8
#define EF_W9			MIPS32_EF_W9
#define EF_W10			MIPS32_EF_W10
#define EF_W11			MIPS32_EF_W11
#define EF_W12			MIPS32_EF_W12
#define EF_W13			MIPS32_EF_W13
#define EF_W14			MIPS32_EF_W14
#define EF_W15			MIPS32_EF_W15
#define EF_W16			MIPS32_EF_W16
#define EF_W17			MIPS32_EF_W17
#define EF_W18			MIPS32_EF_W18
#define EF_W19			MIPS32_EF_W19
#define EF_W20			MIPS32_EF_W20
#define EF_W21			MIPS32_EF_W21
#define EF_W22			MIPS32_EF_W22
#define EF_W23			MIPS32_EF_W23
#define EF_W24			MIPS32_EF_W24
#define EF_W25			MIPS32_EF_W25
#define EF_W26			MIPS32_EF_W26
#define EF_W27			MIPS32_EF_W27
#define EF_W28			MIPS32_EF_W28
#define EF_W29			MIPS32_EF_W29
#define EF_W30			MIPS32_EF_W30
#define EF_W31			MIPS32_EF_W31
#define EF_WO			MIPS32_EF_WO
#define EF_HI			MIPS32_EF_HI
#define EF_CP0_EPC		MIPS32_EF_CP0_EPC
#define EF_CP0_BADVADDW		MIPS32_EF_CP0_BADVADDW
#define EF_CP0_STATUS		MIPS32_EF_CP0_STATUS
#define EF_CP0_CAUSE		MIPS32_EF_CP0_CAUSE
#define EF_UNUSED0		MIPS32_EF_UNUSED0
#define EF_SIZE			MIPS32_EF_SIZE

#ewif _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32

#define EF_W0			MIPS64_EF_W0
#define EF_W1			MIPS64_EF_W1
#define EF_W2			MIPS64_EF_W2
#define EF_W3			MIPS64_EF_W3
#define EF_W4			MIPS64_EF_W4
#define EF_W5			MIPS64_EF_W5
#define EF_W6			MIPS64_EF_W6
#define EF_W7			MIPS64_EF_W7
#define EF_W8			MIPS64_EF_W8
#define EF_W9			MIPS64_EF_W9
#define EF_W10			MIPS64_EF_W10
#define EF_W11			MIPS64_EF_W11
#define EF_W12			MIPS64_EF_W12
#define EF_W13			MIPS64_EF_W13
#define EF_W14			MIPS64_EF_W14
#define EF_W15			MIPS64_EF_W15
#define EF_W16			MIPS64_EF_W16
#define EF_W17			MIPS64_EF_W17
#define EF_W18			MIPS64_EF_W18
#define EF_W19			MIPS64_EF_W19
#define EF_W20			MIPS64_EF_W20
#define EF_W21			MIPS64_EF_W21
#define EF_W22			MIPS64_EF_W22
#define EF_W23			MIPS64_EF_W23
#define EF_W24			MIPS64_EF_W24
#define EF_W25			MIPS64_EF_W25
#define EF_W26			MIPS64_EF_W26
#define EF_W27			MIPS64_EF_W27
#define EF_W28			MIPS64_EF_W28
#define EF_W29			MIPS64_EF_W29
#define EF_W30			MIPS64_EF_W30
#define EF_W31			MIPS64_EF_W31
#define EF_WO			MIPS64_EF_WO
#define EF_HI			MIPS64_EF_HI
#define EF_CP0_EPC		MIPS64_EF_CP0_EPC
#define EF_CP0_BADVADDW		MIPS64_EF_CP0_BADVADDW
#define EF_CP0_STATUS		MIPS64_EF_CP0_STATUS
#define EF_CP0_CAUSE		MIPS64_EF_CP0_CAUSE
#define EF_SIZE			MIPS64_EF_SIZE

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#endif /* __UAPI_ASM_MIPS_WEG_H */
