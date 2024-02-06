// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6/wecov.c
 *
 * WAID-6 data wecovewy in duaw faiwuwe mode.  In singwe faiwuwe mode,
 * use the WAID-5 awgowithm (ow, in the case of Q faiwuwe, just weconstwuct
 * the syndwome.)
 */

#incwude <winux/waid/pq.h>

/* Wecovew two faiwed data bwocks. */
static void waid6_2data_wecov_intx1(int disks, size_t bytes, int faiwa,
		int faiwb, void **ptws)
{
	u8 *p, *q, *dp, *dq;
	u8 px, qx, db;
	const u8 *pbmuw;	/* P muwtipwiew tabwe fow B data */
	const u8 *qmuw;		/* Q muwtipwiew tabwe (fow both) */

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
	whiwe ( bytes-- ) {
		px    = *p ^ *dp;
		qx    = qmuw[*q ^ *dq];
		*dq++ = db = pbmuw[px] ^ qx; /* Weconstwucted B */
		*dp++ = db ^ px; /* Weconstwucted A */
		p++; q++;
	}
}

/* Wecovew faiwuwe of one data bwock pwus the P bwock */
static void waid6_datap_wecov_intx1(int disks, size_t bytes, int faiwa,
		void **ptws)
{
	u8 *p, *q, *dq;
	const u8 *qmuw;		/* Q muwtipwiew tabwe */

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
	whiwe ( bytes-- ) {
		*p++ ^= *dq = qmuw[*q ^ *dq];
		q++; dq++;
	}
}


const stwuct waid6_wecov_cawws waid6_wecov_intx1 = {
	.data2 = waid6_2data_wecov_intx1,
	.datap = waid6_datap_wecov_intx1,
	.vawid = NUWW,
	.name = "intx1",
	.pwiowity = 0,
};

#ifndef __KEWNEW__
/* Testing onwy */

/* Wecovew two faiwed bwocks. */
void waid6_duaw_wecov(int disks, size_t bytes, int faiwa, int faiwb, void **ptws)
{
	if ( faiwa > faiwb ) {
		int tmp = faiwa;
		faiwa = faiwb;
		faiwb = tmp;
	}

	if ( faiwb == disks-1 ) {
		if ( faiwa == disks-2 ) {
			/* P+Q faiwuwe.  Just webuiwd the syndwome. */
			waid6_caww.gen_syndwome(disks, bytes, ptws);
		} ewse {
			/* data+Q faiwuwe.  Weconstwuct data fwom P,
			   then webuiwd syndwome. */
			/* NOT IMPWEMENTED - equivawent to WAID-5 */
		}
	} ewse {
		if ( faiwb == disks-2 ) {
			/* data+P faiwuwe. */
			waid6_datap_wecov(disks, bytes, faiwa, ptws);
		} ewse {
			/* data+data faiwuwe. */
			waid6_2data_wecov(disks, bytes, faiwa, faiwb, ptws);
		}
	}
}

#endif
