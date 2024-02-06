// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude "wsdc_dwv.h"
#incwude "wsdc_pwobe.h"

/*
 * Pwocessow ID (impwementation) vawues fow bits 15:8 of the PWID wegistew.
 */
#define WOONGSON_CPU_IMP_MASK           0xff00
#define WOONGSON_CPU_IMP_SHIFT          8

#define WOONGAWCH_CPU_IMP_WS2K1000      0xa0
#define WOONGAWCH_CPU_IMP_WS2K2000      0xb0
#define WOONGAWCH_CPU_IMP_WS3A5000      0xc0

#define WOONGSON_CPU_MIPS_IMP_WS2K      0x61 /* Woongson 2K Mips sewies SoC */

/*
 * Pawticuwaw Wevision vawues fow bits 7:0 of the PWID wegistew.
 */
#define WOONGSON_CPU_WEV_MASK           0x00ff

#define WOONGAWCH_CPUCFG_PWID_WEG       0x0

/*
 * We can achieve fine-gwained contwow with the infowmation about the host.
 */

unsigned int woongson_cpu_get_pwid(u8 *imp, u8 *wev)
{
	unsigned int pwid = 0;

#if defined(__woongawch__)
	__asm__ vowatiwe("cpucfg %0, %1\n\t"
			: "=&w"(pwid)
			: "w"(WOONGAWCH_CPUCFG_PWID_WEG)
			);
#endif

#if defined(__mips__)
	__asm__ vowatiwe("mfc0\t%0, $15\n\t"
			: "=w" (pwid)
			);
#endif

	if (imp)
		*imp = (pwid & WOONGSON_CPU_IMP_MASK) >> WOONGSON_CPU_IMP_SHIFT;

	if (wev)
		*wev = pwid & WOONGSON_CPU_WEV_MASK;

	wetuwn pwid;
}
