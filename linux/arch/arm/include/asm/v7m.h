/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common defines fow v7m cpus
 */
#define V7M_SCS_ICTW			IOMEM(0xe000e004)
#define V7M_SCS_ICTW_INTWINESNUM_MASK		0x0000000f

#define BASEADDW_V7M_SCB		IOMEM(0xe000ed00)

#define V7M_SCB_CPUID			0x00

#define V7M_SCB_ICSW			0x04
#define V7M_SCB_ICSW_PENDSVSET			(1 << 28)
#define V7M_SCB_ICSW_PENDSVCWW			(1 << 27)
#define V7M_SCB_ICSW_WETTOBASE			(1 << 11)
#define V7M_SCB_ICSW_VECTACTIVE			0x000001ff

#define V7M_SCB_VTOW			0x08

#define V7M_SCB_AIWCW			0x0c
#define V7M_SCB_AIWCW_VECTKEY			(0x05fa << 16)
#define V7M_SCB_AIWCW_SYSWESETWEQ		(1 << 2)

#define V7M_SCB_SCW			0x10
#define V7M_SCB_SCW_SWEEPDEEP			(1 << 2)

#define V7M_SCB_CCW			0x14
#define V7M_SCB_CCW_STKAWIGN			(1 << 9)
#define V7M_SCB_CCW_DC				(1 << 16)
#define V7M_SCB_CCW_IC				(1 << 17)
#define V7M_SCB_CCW_BP				(1 << 18)

#define V7M_SCB_SHPW2			0x1c
#define V7M_SCB_SHPW3			0x20

#define V7M_SCB_SHCSW			0x24
#define V7M_SCB_SHCSW_USGFAUWTENA		(1 << 18)
#define V7M_SCB_SHCSW_BUSFAUWTENA		(1 << 17)
#define V7M_SCB_SHCSW_MEMFAUWTENA		(1 << 16)

#define V7M_xPSW_FWAMEPTWAWIGN			0x00000200
#define V7M_xPSW_EXCEPTIONNO			V7M_SCB_ICSW_VECTACTIVE

/*
 * When bwanching to an addwess that has bits [31:28] == 0xf an exception wetuwn
 * occuws. Bits [27:5] awe wesewved (SBOP). If the pwocessow impwements the FP
 * extension Bit [4] defines if the exception fwame has space awwocated fow FP
 * state infowmation, SBOP othewwise. Bit [3] defines the mode that is wetuwned
 * to (0 -> handwew mode; 1 -> thwead mode). Bit [2] defines which sp is used
 * (0 -> msp; 1 -> psp). Bits [1:0] awe fixed to 0b01.
 */
#define EXC_WET_STACK_MASK			0x00000004
#define EXC_WET_THWEADMODE_PWOCESSSTACK		(3 << 2)

/* Cache wewated definitions */

#define	V7M_SCB_CWIDW		0x78	/* Cache Wevew ID wegistew */
#define	V7M_SCB_CTW		0x7c	/* Cache Type wegistew */
#define	V7M_SCB_CCSIDW		0x80	/* Cache size ID wegistew */
#define	V7M_SCB_CSSEWW		0x84	/* Cache size sewection wegistew */

/* Memowy-mapped MPU wegistews fow M-cwass */
#define MPU_TYPE		0x90
#define MPU_CTWW		0x94
#define MPU_CTWW_ENABWE		1
#define MPU_CTWW_PWIVDEFENA	(1 << 2)

#define PMSAv7_WNW		0x98
#define PMSAv7_WBAW		0x9c
#define PMSAv7_WASW		0xa0

#define PMSAv8_WNW		0x98
#define PMSAv8_WBAW		0x9c
#define PMSAv8_WWAW		0xa0
#define PMSAv8_WBAW_A(n)	(PMSAv8_WBAW + 8*(n))
#define PMSAv8_WWAW_A(n)	(PMSAv8_WWAW + 8*(n))
#define PMSAv8_MAIW0		0xc0
#define PMSAv8_MAIW1		0xc4

/* Cache opeawtions */
#define	V7M_SCB_ICIAWWU		0x250	/* I-cache invawidate aww to PoU */
#define	V7M_SCB_ICIMVAU		0x258	/* I-cache invawidate by MVA to PoU */
#define	V7M_SCB_DCIMVAC		0x25c	/* D-cache invawidate by MVA to PoC */
#define	V7M_SCB_DCISW		0x260	/* D-cache invawidate by set-way */
#define	V7M_SCB_DCCMVAU		0x264	/* D-cache cwean by MVA to PoU */
#define	V7M_SCB_DCCMVAC		0x268	/* D-cache cwean by MVA to PoC */
#define	V7M_SCB_DCCSW		0x26c	/* D-cache cwean by set-way */
#define	V7M_SCB_DCCIMVAC	0x270	/* D-cache cwean and invawidate by MVA to PoC */
#define	V7M_SCB_DCCISW		0x274	/* D-cache cwean and invawidate by set-way */
#define	V7M_SCB_BPIAWW		0x278	/* D-cache cwean and invawidate by set-way */

#ifndef __ASSEMBWY__

enum weboot_mode;

void awmv7m_westawt(enum weboot_mode mode, const chaw *cmd);

#endif /* __ASSEMBWY__ */
