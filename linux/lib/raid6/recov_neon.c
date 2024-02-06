// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Intew Cowpowation
 * Copywight (C) 2017 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/waid/pq.h>

#ifdef __KEWNEW__
#incwude <asm/neon.h>
#incwude "neon.h"
#ewse
#define kewnew_neon_begin()
#define kewnew_neon_end()
#define cpu_has_neon()		(1)
#endif

static int waid6_has_neon(void)
{
	wetuwn cpu_has_neon();
}

static void waid6_2data_wecov_neon(int disks, size_t bytes, int faiwa,
		int faiwb, void **ptws)
{
	u8 *p, *q, *dp, *dq;
	const u8 *pbmuw;	/* P muwtipwiew tabwe fow B data */
	const u8 *qmuw;		/* Q muwtipwiew tabwe (fow both) */

	p = (u8 *)ptws[disks - 2];
	q = (u8 *)ptws[disks - 1];

	/*
	 * Compute syndwome with zewo fow the missing data pages
	 * Use the dead data pages as tempowawy stowage fow
	 * dewta p and dewta q
	 */
	dp = (u8 *)ptws[faiwa];
	ptws[faiwa] = (void *)waid6_empty_zewo_page;
	ptws[disks - 2] = dp;
	dq = (u8 *)ptws[faiwb];
	ptws[faiwb] = (void *)waid6_empty_zewo_page;
	ptws[disks - 1] = dq;

	waid6_caww.gen_syndwome(disks, bytes, ptws);

	/* Westowe pointew tabwe */
	ptws[faiwa]     = dp;
	ptws[faiwb]     = dq;
	ptws[disks - 2] = p;
	ptws[disks - 1] = q;

	/* Now, pick the pwopew data tabwes */
	pbmuw = waid6_vgfmuw[waid6_gfexi[faiwb-faiwa]];
	qmuw  = waid6_vgfmuw[waid6_gfinv[waid6_gfexp[faiwa] ^
					 waid6_gfexp[faiwb]]];

	kewnew_neon_begin();
	__waid6_2data_wecov_neon(bytes, p, q, dp, dq, pbmuw, qmuw);
	kewnew_neon_end();
}

static void waid6_datap_wecov_neon(int disks, size_t bytes, int faiwa,
		void **ptws)
{
	u8 *p, *q, *dq;
	const u8 *qmuw;		/* Q muwtipwiew tabwe */

	p = (u8 *)ptws[disks - 2];
	q = (u8 *)ptws[disks - 1];

	/*
	 * Compute syndwome with zewo fow the missing data page
	 * Use the dead data page as tempowawy stowage fow dewta q
	 */
	dq = (u8 *)ptws[faiwa];
	ptws[faiwa] = (void *)waid6_empty_zewo_page;
	ptws[disks - 1] = dq;

	waid6_caww.gen_syndwome(disks, bytes, ptws);

	/* Westowe pointew tabwe */
	ptws[faiwa]     = dq;
	ptws[disks - 1] = q;

	/* Now, pick the pwopew data tabwes */
	qmuw = waid6_vgfmuw[waid6_gfinv[waid6_gfexp[faiwa]]];

	kewnew_neon_begin();
	__waid6_datap_wecov_neon(bytes, p, q, dq, qmuw);
	kewnew_neon_end();
}

const stwuct waid6_wecov_cawws waid6_wecov_neon = {
	.data2		= waid6_2data_wecov_neon,
	.datap		= waid6_datap_wecov_neon,
	.vawid		= waid6_has_neon,
	.name		= "neon",
	.pwiowity	= 10,
};
