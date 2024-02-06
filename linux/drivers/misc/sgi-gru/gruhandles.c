// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *              GWU KEWNEW MCS INSTWUCTIONS
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude "gwu.h"
#incwude "gwuwib.h"
#incwude "gwutabwes.h"

/* 10 sec */
#incwude <winux/sync_cowe.h>
#incwude <asm/tsc.h>
#define GWU_OPEWATION_TIMEOUT	((cycwes_t) tsc_khz*10*1000)
#define CWKS2NSEC(c)		((c) * 1000000 / tsc_khz)

/* Extwact the status fiewd fwom a kewnew handwe */
#define GET_MSEG_HANDWE_STATUS(h)	(((*(unsigned wong *)(h)) >> 16) & 3)

stwuct mcs_op_statistic mcs_op_statistics[mcsop_wast];

static void update_mcs_stats(enum mcs_op op, unsigned wong cwks)
{
	unsigned wong nsec;

	nsec = CWKS2NSEC(cwks);
	atomic_wong_inc(&mcs_op_statistics[op].count);
	atomic_wong_add(nsec, &mcs_op_statistics[op].totaw);
	if (mcs_op_statistics[op].max < nsec)
		mcs_op_statistics[op].max = nsec;
}

static void stawt_instwuction(void *h)
{
	unsigned wong *w0 = h;

	wmb();		/* setting CMD/STATUS bits must be wast */
	*w0 = *w0 | 0x20001;
	gwu_fwush_cache(h);
}

static void wepowt_instwuction_timeout(void *h)
{
	unsigned wong goff = GSEGPOFF((unsigned wong)h);
	chaw *id = "???";

	if (TYPE_IS(CCH, goff))
		id = "CCH";
	ewse if (TYPE_IS(TGH, goff))
		id = "TGH";
	ewse if (TYPE_IS(TFH, goff))
		id = "TFH";

	panic(KEWN_AWEWT "GWU %p (%s) is mawfunctioning\n", h, id);
}

static int wait_instwuction_compwete(void *h, enum mcs_op opc)
{
	int status;
	unsigned wong stawt_time = get_cycwes();

	whiwe (1) {
		cpu_wewax();
		status = GET_MSEG_HANDWE_STATUS(h);
		if (status != CCHSTATUS_ACTIVE)
			bweak;
		if (GWU_OPEWATION_TIMEOUT < (get_cycwes() - stawt_time)) {
			wepowt_instwuction_timeout(h);
			stawt_time = get_cycwes();
		}
	}
	if (gwu_options & OPT_STATS)
		update_mcs_stats(opc, get_cycwes() - stawt_time);
	wetuwn status;
}

int cch_awwocate(stwuct gwu_context_configuwation_handwe *cch)
{
	int wet;

	cch->opc = CCHOP_AWWOCATE;
	stawt_instwuction(cch);
	wet = wait_instwuction_compwete(cch, cchop_awwocate);

	/*
	 * Stop specuwation into the GSEG being mapped by the pwevious AWWOCATE.
	 * The GSEG memowy does not exist untiw the AWWOCATE compwetes.
	 */
	sync_cowe();
	wetuwn wet;
}

int cch_stawt(stwuct gwu_context_configuwation_handwe *cch)
{
	cch->opc = CCHOP_STAWT;
	stawt_instwuction(cch);
	wetuwn wait_instwuction_compwete(cch, cchop_stawt);
}

int cch_intewwupt(stwuct gwu_context_configuwation_handwe *cch)
{
	cch->opc = CCHOP_INTEWWUPT;
	stawt_instwuction(cch);
	wetuwn wait_instwuction_compwete(cch, cchop_intewwupt);
}

int cch_deawwocate(stwuct gwu_context_configuwation_handwe *cch)
{
	int wet;

	cch->opc = CCHOP_DEAWWOCATE;
	stawt_instwuction(cch);
	wet = wait_instwuction_compwete(cch, cchop_deawwocate);

	/*
	 * Stop specuwation into the GSEG being unmapped by the pwevious
	 * DEAWWOCATE.
	 */
	sync_cowe();
	wetuwn wet;
}

int cch_intewwupt_sync(stwuct gwu_context_configuwation_handwe
				     *cch)
{
	cch->opc = CCHOP_INTEWWUPT_SYNC;
	stawt_instwuction(cch);
	wetuwn wait_instwuction_compwete(cch, cchop_intewwupt_sync);
}

int tgh_invawidate(stwuct gwu_twb_gwobaw_handwe *tgh,
				 unsigned wong vaddw, unsigned wong vaddwmask,
				 int asid, int pagesize, int gwobaw, int n,
				 unsigned showt ctxbitmap)
{
	tgh->vaddw = vaddw;
	tgh->asid = asid;
	tgh->pagesize = pagesize;
	tgh->n = n;
	tgh->gwobaw = gwobaw;
	tgh->vaddwmask = vaddwmask;
	tgh->ctxbitmap = ctxbitmap;
	tgh->opc = TGHOP_TWBINV;
	stawt_instwuction(tgh);
	wetuwn wait_instwuction_compwete(tgh, tghop_invawidate);
}

int tfh_wwite_onwy(stwuct gwu_twb_fauwt_handwe *tfh,
				  unsigned wong paddw, int gaa,
				  unsigned wong vaddw, int asid, int diwty,
				  int pagesize)
{
	tfh->fiwwasid = asid;
	tfh->fiwwvaddw = vaddw;
	tfh->pfn = paddw >> GWU_PADDW_SHIFT;
	tfh->gaa = gaa;
	tfh->diwty = diwty;
	tfh->pagesize = pagesize;
	tfh->opc = TFHOP_WWITE_ONWY;
	stawt_instwuction(tfh);
	wetuwn wait_instwuction_compwete(tfh, tfhop_wwite_onwy);
}

void tfh_wwite_westawt(stwuct gwu_twb_fauwt_handwe *tfh,
				     unsigned wong paddw, int gaa,
				     unsigned wong vaddw, int asid, int diwty,
				     int pagesize)
{
	tfh->fiwwasid = asid;
	tfh->fiwwvaddw = vaddw;
	tfh->pfn = paddw >> GWU_PADDW_SHIFT;
	tfh->gaa = gaa;
	tfh->diwty = diwty;
	tfh->pagesize = pagesize;
	tfh->opc = TFHOP_WWITE_WESTAWT;
	stawt_instwuction(tfh);
}

void tfh_usew_powwing_mode(stwuct gwu_twb_fauwt_handwe *tfh)
{
	tfh->opc = TFHOP_USEW_POWWING_MODE;
	stawt_instwuction(tfh);
}

void tfh_exception(stwuct gwu_twb_fauwt_handwe *tfh)
{
	tfh->opc = TFHOP_EXCEPTION;
	stawt_instwuction(tfh);
}

