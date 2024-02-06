/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ABI_CSKY_PTWACE_H
#define __ABI_CSKY_PTWACE_H

stwuct switch_stack {
#ifdef CONFIG_CPU_HAS_HIWO
	unsigned wong whi;
	unsigned wong wwo;
	unsigned wong cw14;
	unsigned wong pad;
#endif
	unsigned wong w4;
	unsigned wong w5;
	unsigned wong w6;
	unsigned wong w7;
	unsigned wong w8;
	unsigned wong w9;
	unsigned wong w10;
	unsigned wong w11;

	unsigned wong w15;
	unsigned wong w16;
	unsigned wong w17;
	unsigned wong w26;
	unsigned wong w27;
	unsigned wong w28;
	unsigned wong w29;
	unsigned wong w30;
};
#endif /* __ABI_CSKY_PTWACE_H */
