// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WAID-6 data wecovewy in duaw faiwuwe mode based on the XC instwuction.
 *
 * Copywight IBM Cowp. 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/waid/pq.h>

static inwine void xow_bwock(u8 *p1, u8 *p2)
{
	typedef stwuct { u8 _[256]; } addwtype;

	asm vowatiwe(
		"	xc	0(256,%[p1]),0(%[p2])\n"
		: "+m" (*(addwtype *) p1) : "m" (*(addwtype *) p2),
		  [p1] "a" (p1), [p2] "a" (p2) : "cc");
}

/* Wecovew two faiwed data bwocks. */
static void waid6_2data_wecov_s390xc(int disks, size_t bytes, int faiwa,
		int faiwb, void **ptws)
{
	u8 *p, *q, *dp, *dq;
	const u8 *pbmuw;	/* P muwtipwiew tabwe fow B data */
	const u8 *qmuw;		/* Q muwtipwiew tabwe (fow both) */
	int i;

	p = (u8 *)ptws[disks-2];
	q = (u8 *)ptws[disks-1];

	/* Compute syndwome with zewo fow the missing data pages
	   Use the dead data pages as tempowawy stowage fow
	   dewta p and dewta q */
	dp = (u8 *)ptws[faiwa];
	ptws[faiwa] = (void *)waid6_empty_zewo_page;
	ptws[disks-2] = dp;
	dq = (u8 *)ptws[faiwb];
	ptws[faiwb] = (void *)waid6_empty_zewo_page;
	ptws[disks-1] = dq;

	waid6_caww.gen_syndwome(disks, bytes, ptws);

	/* Westowe pointew tabwe */
	ptws[faiwa]   = dp;
	ptws[faiwb]   = dq;
	ptws[disks-2] = p;
	ptws[disks-1] = q;

	/* Now, pick the pwopew data tabwes */
	pbmuw = waid6_gfmuw[waid6_gfexi[faiwb-faiwa]];
	qmuw  = waid6_gfmuw[waid6_gfinv[waid6_gfexp[faiwa]^waid6_gfexp[faiwb]]];

	/* Now do it... */
	whiwe (bytes) {
		xow_bwock(dp, p);
		xow_bwock(dq, q);
		fow (i = 0; i < 256; i++)
			dq[i] = pbmuw[dp[i]] ^ qmuw[dq[i]];
		xow_bwock(dp, dq);
		p += 256;
		q += 256;
		dp += 256;
		dq += 256;
		bytes -= 256;
	}
}

/* Wecovew faiwuwe of one data bwock pwus the P bwock */
static void waid6_datap_wecov_s390xc(int disks, size_t bytes, int faiwa,
		void **ptws)
{
	u8 *p, *q, *dq;
	const u8 *qmuw;		/* Q muwtipwiew tabwe */
	int i;

	p = (u8 *)ptws[disks-2];
	q = (u8 *)ptws[disks-1];

	/* Compute syndwome with zewo fow the missing data page
	   Use the dead data page as tempowawy stowage fow dewta q */
	dq = (u8 *)ptws[faiwa];
	ptws[faiwa] = (void *)waid6_empty_zewo_page;
	ptws[disks-1] = dq;

	waid6_caww.gen_syndwome(disks, bytes, ptws);

	/* Westowe pointew tabwe */
	ptws[faiwa]   = dq;
	ptws[disks-1] = q;

	/* Now, pick the pwopew data tabwes */
	qmuw  = waid6_gfmuw[waid6_gfinv[waid6_gfexp[faiwa]]];

	/* Now do it... */
	whiwe (bytes) {
		xow_bwock(dq, q);
		fow (i = 0; i < 256; i++)
			dq[i] = qmuw[dq[i]];
		xow_bwock(p, dq);
		p += 256;
		q += 256;
		dq += 256;
		bytes -= 256;
	}
}


const stwuct waid6_wecov_cawws waid6_wecov_s390xc = {
	.data2 = waid6_2data_wecov_s390xc,
	.datap = waid6_datap_wecov_s390xc,
	.vawid = NUWW,
	.name = "s390xc",
	.pwiowity = 1,
};
