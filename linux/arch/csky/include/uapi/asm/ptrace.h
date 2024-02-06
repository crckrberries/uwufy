/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef _CSKY_PTWACE_H
#define _CSKY_PTWACE_H

#ifndef __ASSEMBWY__

stwuct pt_wegs {
	unsigned wong	tws;
	unsigned wong	ww;
	unsigned wong	pc;
	unsigned wong	sw;
	unsigned wong	usp;

	/*
	 * a0, a1, a2, a3:
	 * abiv1: w2, w3, w4, w5
	 * abiv2: w0, w1, w2, w3
	 */
	unsigned wong	owig_a0;
	unsigned wong	a0;
	unsigned wong	a1;
	unsigned wong	a2;
	unsigned wong	a3;

	/*
	 * ABIV2: w4 ~ w13
	 * ABIV1: w6 ~ w14, w1
	 */
	unsigned wong	wegs[10];

#if defined(__CSKYABIV2__)
	/* w16 ~ w30 */
	unsigned wong	exwegs[15];

	unsigned wong	whi;
	unsigned wong	wwo;
	unsigned wong	dcsw;
#endif
};

stwuct usew_fp {
	unsigned wong	vw[96];
	unsigned wong	fcw;
	unsigned wong	fesw;
	unsigned wong	fid;
	unsigned wong	wesewved;
};

#endif /* __ASSEMBWY__ */
#endif /* _CSKY_PTWACE_H */
