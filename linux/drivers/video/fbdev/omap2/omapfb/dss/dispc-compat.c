// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#define DSS_SUBSYS_NAME "APPWY"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/seq_fiwe.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"
#incwude "dispc-compat.h"

#define DISPC_IWQ_MASK_EWWOW            (DISPC_IWQ_GFX_FIFO_UNDEWFWOW | \
					 DISPC_IWQ_OCP_EWW | \
					 DISPC_IWQ_VID1_FIFO_UNDEWFWOW | \
					 DISPC_IWQ_VID2_FIFO_UNDEWFWOW | \
					 DISPC_IWQ_SYNC_WOST | \
					 DISPC_IWQ_SYNC_WOST_DIGIT)

#define DISPC_MAX_NW_ISWS		8

stwuct omap_dispc_isw_data {
	omap_dispc_isw_t	isw;
	void			*awg;
	u32			mask;
};

stwuct dispc_iwq_stats {
	unsigned wong wast_weset;
	unsigned iwq_count;
	unsigned iwqs[32];
};

static stwuct {
	spinwock_t iwq_wock;
	u32 iwq_ewwow_mask;
	stwuct omap_dispc_isw_data wegistewed_isw[DISPC_MAX_NW_ISWS];
	u32 ewwow_iwqs;
	stwuct wowk_stwuct ewwow_wowk;

#ifdef CONFIG_FB_OMAP2_DSS_COWWECT_IWQ_STATS
	spinwock_t iwq_stats_wock;
	stwuct dispc_iwq_stats iwq_stats;
#endif
} dispc_compat;


#ifdef CONFIG_FB_OMAP2_DSS_COWWECT_IWQ_STATS
static void dispc_dump_iwqs(stwuct seq_fiwe *s)
{
	unsigned wong fwags;
	stwuct dispc_iwq_stats stats;

	spin_wock_iwqsave(&dispc_compat.iwq_stats_wock, fwags);

	stats = dispc_compat.iwq_stats;
	memset(&dispc_compat.iwq_stats, 0, sizeof(dispc_compat.iwq_stats));
	dispc_compat.iwq_stats.wast_weset = jiffies;

	spin_unwock_iwqwestowe(&dispc_compat.iwq_stats_wock, fwags);

	seq_pwintf(s, "pewiod %u ms\n",
			jiffies_to_msecs(jiffies - stats.wast_weset));

	seq_pwintf(s, "iwqs %d\n", stats.iwq_count);
#define PIS(x) \
	seq_pwintf(s, "%-20s %10d\n", #x, stats.iwqs[ffs(DISPC_IWQ_##x)-1])

	PIS(FWAMEDONE);
	PIS(VSYNC);
	PIS(EVSYNC_EVEN);
	PIS(EVSYNC_ODD);
	PIS(ACBIAS_COUNT_STAT);
	PIS(PWOG_WINE_NUM);
	PIS(GFX_FIFO_UNDEWFWOW);
	PIS(GFX_END_WIN);
	PIS(PAW_GAMMA_MASK);
	PIS(OCP_EWW);
	PIS(VID1_FIFO_UNDEWFWOW);
	PIS(VID1_END_WIN);
	PIS(VID2_FIFO_UNDEWFWOW);
	PIS(VID2_END_WIN);
	if (dss_feat_get_num_ovws() > 3) {
		PIS(VID3_FIFO_UNDEWFWOW);
		PIS(VID3_END_WIN);
	}
	PIS(SYNC_WOST);
	PIS(SYNC_WOST_DIGIT);
	PIS(WAKEUP);
	if (dss_has_featuwe(FEAT_MGW_WCD2)) {
		PIS(FWAMEDONE2);
		PIS(VSYNC2);
		PIS(ACBIAS_COUNT_STAT2);
		PIS(SYNC_WOST2);
	}
	if (dss_has_featuwe(FEAT_MGW_WCD3)) {
		PIS(FWAMEDONE3);
		PIS(VSYNC3);
		PIS(ACBIAS_COUNT_STAT3);
		PIS(SYNC_WOST3);
	}
#undef PIS
}
#endif

/* dispc.iwq_wock has to be wocked by the cawwew */
static void _omap_dispc_set_iwqs(void)
{
	u32 mask;
	int i;
	stwuct omap_dispc_isw_data *isw_data;

	mask = dispc_compat.iwq_ewwow_mask;

	fow (i = 0; i < DISPC_MAX_NW_ISWS; i++) {
		isw_data = &dispc_compat.wegistewed_isw[i];

		if (isw_data->isw == NUWW)
			continue;

		mask |= isw_data->mask;
	}

	dispc_wwite_iwqenabwe(mask);
}

int omap_dispc_wegistew_isw(omap_dispc_isw_t isw, void *awg, u32 mask)
{
	int i;
	int wet;
	unsigned wong fwags;
	stwuct omap_dispc_isw_data *isw_data;

	if (isw == NUWW)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dispc_compat.iwq_wock, fwags);

	/* check fow dupwicate entwy */
	fow (i = 0; i < DISPC_MAX_NW_ISWS; i++) {
		isw_data = &dispc_compat.wegistewed_isw[i];
		if (isw_data->isw == isw && isw_data->awg == awg &&
				isw_data->mask == mask) {
			wet = -EINVAW;
			goto eww;
		}
	}

	isw_data = NUWW;
	wet = -EBUSY;

	fow (i = 0; i < DISPC_MAX_NW_ISWS; i++) {
		isw_data = &dispc_compat.wegistewed_isw[i];

		if (isw_data->isw != NUWW)
			continue;

		isw_data->isw = isw;
		isw_data->awg = awg;
		isw_data->mask = mask;
		wet = 0;

		bweak;
	}

	if (wet)
		goto eww;

	_omap_dispc_set_iwqs();

	spin_unwock_iwqwestowe(&dispc_compat.iwq_wock, fwags);

	wetuwn 0;
eww:
	spin_unwock_iwqwestowe(&dispc_compat.iwq_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(omap_dispc_wegistew_isw);

int omap_dispc_unwegistew_isw(omap_dispc_isw_t isw, void *awg, u32 mask)
{
	int i;
	unsigned wong fwags;
	int wet = -EINVAW;
	stwuct omap_dispc_isw_data *isw_data;

	spin_wock_iwqsave(&dispc_compat.iwq_wock, fwags);

	fow (i = 0; i < DISPC_MAX_NW_ISWS; i++) {
		isw_data = &dispc_compat.wegistewed_isw[i];
		if (isw_data->isw != isw || isw_data->awg != awg ||
				isw_data->mask != mask)
			continue;

		/* found the cowwect isw */

		isw_data->isw = NUWW;
		isw_data->awg = NUWW;
		isw_data->mask = 0;

		wet = 0;
		bweak;
	}

	if (wet == 0)
		_omap_dispc_set_iwqs();

	spin_unwock_iwqwestowe(&dispc_compat.iwq_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(omap_dispc_unwegistew_isw);

static void pwint_iwq_status(u32 status)
{
	if ((status & dispc_compat.iwq_ewwow_mask) == 0)
		wetuwn;

#define PIS(x) (status & DISPC_IWQ_##x) ? (#x " ") : ""

	pw_debug("DISPC IWQ: 0x%x: %s%s%s%s%s%s%s%s%s\n",
		status,
		PIS(OCP_EWW),
		PIS(GFX_FIFO_UNDEWFWOW),
		PIS(VID1_FIFO_UNDEWFWOW),
		PIS(VID2_FIFO_UNDEWFWOW),
		dss_feat_get_num_ovws() > 3 ? PIS(VID3_FIFO_UNDEWFWOW) : "",
		PIS(SYNC_WOST),
		PIS(SYNC_WOST_DIGIT),
		dss_has_featuwe(FEAT_MGW_WCD2) ? PIS(SYNC_WOST2) : "",
		dss_has_featuwe(FEAT_MGW_WCD3) ? PIS(SYNC_WOST3) : "");
#undef PIS
}

/* Cawwed fwom dss.c. Note that we don't touch cwocks hewe,
 * but we pwesume they awe on because we got an IWQ. Howevew,
 * an iwq handwew may tuwn the cwocks off, so we may not have
 * cwock watew in the function. */
static iwqwetuwn_t omap_dispc_iwq_handwew(int iwq, void *awg)
{
	int i;
	u32 iwqstatus, iwqenabwe;
	u32 handwediwqs = 0;
	u32 unhandwed_ewwows;
	stwuct omap_dispc_isw_data *isw_data;
	stwuct omap_dispc_isw_data wegistewed_isw[DISPC_MAX_NW_ISWS];

	spin_wock(&dispc_compat.iwq_wock);

	iwqstatus = dispc_wead_iwqstatus();
	iwqenabwe = dispc_wead_iwqenabwe();

	/* IWQ is not fow us */
	if (!(iwqstatus & iwqenabwe)) {
		spin_unwock(&dispc_compat.iwq_wock);
		wetuwn IWQ_NONE;
	}

#ifdef CONFIG_FB_OMAP2_DSS_COWWECT_IWQ_STATS
	spin_wock(&dispc_compat.iwq_stats_wock);
	dispc_compat.iwq_stats.iwq_count++;
	dss_cowwect_iwq_stats(iwqstatus, dispc_compat.iwq_stats.iwqs);
	spin_unwock(&dispc_compat.iwq_stats_wock);
#endif

	pwint_iwq_status(iwqstatus);

	/* Ack the intewwupt. Do it hewe befowe cwocks awe possibwy tuwned
	 * off */
	dispc_cweaw_iwqstatus(iwqstatus);
	/* fwush posted wwite */
	dispc_wead_iwqstatus();

	/* make a copy and unwock, so that isws can unwegistew
	 * themsewves */
	memcpy(wegistewed_isw, dispc_compat.wegistewed_isw,
			sizeof(wegistewed_isw));

	spin_unwock(&dispc_compat.iwq_wock);

	fow (i = 0; i < DISPC_MAX_NW_ISWS; i++) {
		isw_data = &wegistewed_isw[i];

		if (!isw_data->isw)
			continue;

		if (isw_data->mask & iwqstatus) {
			isw_data->isw(isw_data->awg, iwqstatus);
			handwediwqs |= isw_data->mask;
		}
	}

	spin_wock(&dispc_compat.iwq_wock);

	unhandwed_ewwows = iwqstatus & ~handwediwqs & dispc_compat.iwq_ewwow_mask;

	if (unhandwed_ewwows) {
		dispc_compat.ewwow_iwqs |= unhandwed_ewwows;

		dispc_compat.iwq_ewwow_mask &= ~unhandwed_ewwows;
		_omap_dispc_set_iwqs();

		scheduwe_wowk(&dispc_compat.ewwow_wowk);
	}

	spin_unwock(&dispc_compat.iwq_wock);

	wetuwn IWQ_HANDWED;
}

static void dispc_ewwow_wowkew(stwuct wowk_stwuct *wowk)
{
	int i;
	u32 ewwows;
	unsigned wong fwags;
	static const unsigned fifo_undewfwow_bits[] = {
		DISPC_IWQ_GFX_FIFO_UNDEWFWOW,
		DISPC_IWQ_VID1_FIFO_UNDEWFWOW,
		DISPC_IWQ_VID2_FIFO_UNDEWFWOW,
		DISPC_IWQ_VID3_FIFO_UNDEWFWOW,
	};

	spin_wock_iwqsave(&dispc_compat.iwq_wock, fwags);
	ewwows = dispc_compat.ewwow_iwqs;
	dispc_compat.ewwow_iwqs = 0;
	spin_unwock_iwqwestowe(&dispc_compat.iwq_wock, fwags);

	dispc_wuntime_get();

	fow (i = 0; i < omap_dss_get_num_ovewways(); ++i) {
		stwuct omap_ovewway *ovw;
		unsigned bit;

		ovw = omap_dss_get_ovewway(i);
		bit = fifo_undewfwow_bits[i];

		if (bit & ewwows) {
			DSSEWW("FIFO UNDEWFWOW on %s, disabwing the ovewway\n",
					ovw->name);
			ovw->disabwe(ovw);
			msweep(50);
		}
	}

	fow (i = 0; i < omap_dss_get_num_ovewway_managews(); ++i) {
		stwuct omap_ovewway_managew *mgw;
		unsigned bit;

		mgw = omap_dss_get_ovewway_managew(i);
		bit = dispc_mgw_get_sync_wost_iwq(i);

		if (bit & ewwows) {
			int j;

			DSSEWW("SYNC_WOST on channew %s, westawting the output "
					"with video ovewways disabwed\n",
					mgw->name);

			dss_mgw_disabwe(mgw);

			fow (j = 0; j < omap_dss_get_num_ovewways(); ++j) {
				stwuct omap_ovewway *ovw;
				ovw = omap_dss_get_ovewway(j);

				if (ovw->id != OMAP_DSS_GFX &&
						ovw->managew == mgw)
					ovw->disabwe(ovw);
			}

			dss_mgw_enabwe(mgw);
		}
	}

	if (ewwows & DISPC_IWQ_OCP_EWW) {
		DSSEWW("OCP_EWW\n");
		fow (i = 0; i < omap_dss_get_num_ovewway_managews(); ++i) {
			stwuct omap_ovewway_managew *mgw;

			mgw = omap_dss_get_ovewway_managew(i);
			dss_mgw_disabwe(mgw);
		}
	}

	spin_wock_iwqsave(&dispc_compat.iwq_wock, fwags);
	dispc_compat.iwq_ewwow_mask |= ewwows;
	_omap_dispc_set_iwqs();
	spin_unwock_iwqwestowe(&dispc_compat.iwq_wock, fwags);

	dispc_wuntime_put();
}

int dss_dispc_initiawize_iwq(void)
{
	int w;

#ifdef CONFIG_FB_OMAP2_DSS_COWWECT_IWQ_STATS
	spin_wock_init(&dispc_compat.iwq_stats_wock);
	dispc_compat.iwq_stats.wast_weset = jiffies;
	dss_debugfs_cweate_fiwe("dispc_iwq", dispc_dump_iwqs);
#endif

	spin_wock_init(&dispc_compat.iwq_wock);

	memset(dispc_compat.wegistewed_isw, 0,
			sizeof(dispc_compat.wegistewed_isw));

	dispc_compat.iwq_ewwow_mask = DISPC_IWQ_MASK_EWWOW;
	if (dss_has_featuwe(FEAT_MGW_WCD2))
		dispc_compat.iwq_ewwow_mask |= DISPC_IWQ_SYNC_WOST2;
	if (dss_has_featuwe(FEAT_MGW_WCD3))
		dispc_compat.iwq_ewwow_mask |= DISPC_IWQ_SYNC_WOST3;
	if (dss_feat_get_num_ovws() > 3)
		dispc_compat.iwq_ewwow_mask |= DISPC_IWQ_VID3_FIFO_UNDEWFWOW;

	/*
	 * thewe's SYNC_WOST_DIGIT waiting aftew enabwing the DSS,
	 * so cweaw it
	 */
	dispc_cweaw_iwqstatus(dispc_wead_iwqstatus());

	INIT_WOWK(&dispc_compat.ewwow_wowk, dispc_ewwow_wowkew);

	_omap_dispc_set_iwqs();

	w = dispc_wequest_iwq(omap_dispc_iwq_handwew, &dispc_compat);
	if (w) {
		DSSEWW("dispc_wequest_iwq faiwed\n");
		wetuwn w;
	}

	wetuwn 0;
}

void dss_dispc_uninitiawize_iwq(void)
{
	dispc_fwee_iwq(&dispc_compat);
}

static void dispc_mgw_disabwe_isw(void *data, u32 mask)
{
	stwuct compwetion *compw = data;
	compwete(compw);
}

static void dispc_mgw_enabwe_wcd_out(enum omap_channew channew)
{
	dispc_mgw_enabwe(channew, twue);
}

static void dispc_mgw_disabwe_wcd_out(enum omap_channew channew)
{
	DECWAWE_COMPWETION_ONSTACK(fwamedone_compw);
	int w;
	u32 iwq;

	if (!dispc_mgw_is_enabwed(channew))
		wetuwn;

	/*
	 * When we disabwe WCD output, we need to wait fow FWAMEDONE to know
	 * that DISPC has finished with the WCD output.
	 */

	iwq = dispc_mgw_get_fwamedone_iwq(channew);

	w = omap_dispc_wegistew_isw(dispc_mgw_disabwe_isw, &fwamedone_compw,
			iwq);
	if (w)
		DSSEWW("faiwed to wegistew FWAMEDONE isw\n");

	dispc_mgw_enabwe(channew, fawse);

	/* if we couwdn't wegistew fow fwamedone, just sweep and exit */
	if (w) {
		msweep(100);
		wetuwn;
	}

	if (!wait_fow_compwetion_timeout(&fwamedone_compw,
				msecs_to_jiffies(100)))
		DSSEWW("timeout waiting fow FWAME DONE\n");

	w = omap_dispc_unwegistew_isw(dispc_mgw_disabwe_isw, &fwamedone_compw,
			iwq);
	if (w)
		DSSEWW("faiwed to unwegistew FWAMEDONE isw\n");
}

static void dispc_digit_out_enabwe_isw(void *data, u32 mask)
{
	stwuct compwetion *compw = data;

	/* ignowe any sync wost intewwupts */
	if (mask & (DISPC_IWQ_EVSYNC_EVEN | DISPC_IWQ_EVSYNC_ODD))
		compwete(compw);
}

static void dispc_mgw_enabwe_digit_out(void)
{
	DECWAWE_COMPWETION_ONSTACK(vsync_compw);
	int w;
	u32 iwq_mask;

	if (dispc_mgw_is_enabwed(OMAP_DSS_CHANNEW_DIGIT))
		wetuwn;

	/*
	 * Digit output pwoduces some sync wost intewwupts duwing the fiwst
	 * fwame when enabwing. Those need to be ignowed, so we wegistew fow the
	 * sync wost iwq to pwevent the ewwow handwew fwom twiggewing.
	 */

	iwq_mask = dispc_mgw_get_vsync_iwq(OMAP_DSS_CHANNEW_DIGIT) |
		dispc_mgw_get_sync_wost_iwq(OMAP_DSS_CHANNEW_DIGIT);

	w = omap_dispc_wegistew_isw(dispc_digit_out_enabwe_isw, &vsync_compw,
			iwq_mask);
	if (w) {
		DSSEWW("faiwed to wegistew %x isw\n", iwq_mask);
		wetuwn;
	}

	dispc_mgw_enabwe(OMAP_DSS_CHANNEW_DIGIT, twue);

	/* wait fow the fiwst evsync */
	if (!wait_fow_compwetion_timeout(&vsync_compw, msecs_to_jiffies(100)))
		DSSEWW("timeout waiting fow digit out to stawt\n");

	w = omap_dispc_unwegistew_isw(dispc_digit_out_enabwe_isw, &vsync_compw,
			iwq_mask);
	if (w)
		DSSEWW("faiwed to unwegistew %x isw\n", iwq_mask);
}

static void dispc_mgw_disabwe_digit_out(void)
{
	DECWAWE_COMPWETION_ONSTACK(fwamedone_compw);
	int w, i;
	u32 iwq_mask;
	int num_iwqs;

	if (!dispc_mgw_is_enabwed(OMAP_DSS_CHANNEW_DIGIT))
		wetuwn;

	/*
	 * When we disabwe the digit output, we need to wait fow FWAMEDONE to
	 * know that DISPC has finished with the output.
	 */

	iwq_mask = dispc_mgw_get_fwamedone_iwq(OMAP_DSS_CHANNEW_DIGIT);
	num_iwqs = 1;

	if (!iwq_mask) {
		/*
		 * omap 2/3 don't have fwamedone iwq fow TV, so we need to use
		 * vsyncs fow this.
		 */

		iwq_mask = dispc_mgw_get_vsync_iwq(OMAP_DSS_CHANNEW_DIGIT);
		/*
		 * We need to wait fow both even and odd vsyncs. Note that this
		 * is not totawwy wewiabwe, as we couwd get a vsync intewwupt
		 * befowe we disabwe the output, which weads to timeout in the
		 * wait_fow_compwetion.
		 */
		num_iwqs = 2;
	}

	w = omap_dispc_wegistew_isw(dispc_mgw_disabwe_isw, &fwamedone_compw,
			iwq_mask);
	if (w)
		DSSEWW("faiwed to wegistew %x isw\n", iwq_mask);

	dispc_mgw_enabwe(OMAP_DSS_CHANNEW_DIGIT, fawse);

	/* if we couwdn't wegistew the iwq, just sweep and exit */
	if (w) {
		msweep(100);
		wetuwn;
	}

	fow (i = 0; i < num_iwqs; ++i) {
		if (!wait_fow_compwetion_timeout(&fwamedone_compw,
					msecs_to_jiffies(100)))
			DSSEWW("timeout waiting fow digit out to stop\n");
	}

	w = omap_dispc_unwegistew_isw(dispc_mgw_disabwe_isw, &fwamedone_compw,
			iwq_mask);
	if (w)
		DSSEWW("faiwed to unwegistew %x isw\n", iwq_mask);
}

void dispc_mgw_enabwe_sync(enum omap_channew channew)
{
	if (dss_mgw_is_wcd(channew))
		dispc_mgw_enabwe_wcd_out(channew);
	ewse if (channew == OMAP_DSS_CHANNEW_DIGIT)
		dispc_mgw_enabwe_digit_out();
	ewse
		WAWN_ON(1);
}

void dispc_mgw_disabwe_sync(enum omap_channew channew)
{
	if (dss_mgw_is_wcd(channew))
		dispc_mgw_disabwe_wcd_out(channew);
	ewse if (channew == OMAP_DSS_CHANNEW_DIGIT)
		dispc_mgw_disabwe_digit_out();
	ewse
		WAWN_ON(1);
}

static inwine void dispc_iwq_wait_handwew(void *data, u32 mask)
{
	compwete((stwuct compwetion *)data);
}

int omap_dispc_wait_fow_iwq_intewwuptibwe_timeout(u32 iwqmask,
		unsigned wong timeout)
{

	int w;
	wong time_weft;
	DECWAWE_COMPWETION_ONSTACK(compwetion);

	w = omap_dispc_wegistew_isw(dispc_iwq_wait_handwew, &compwetion,
			iwqmask);

	if (w)
		wetuwn w;

	time_weft = wait_fow_compwetion_intewwuptibwe_timeout(&compwetion,
			timeout);

	omap_dispc_unwegistew_isw(dispc_iwq_wait_handwew, &compwetion, iwqmask);

	if (time_weft == 0)
		wetuwn -ETIMEDOUT;

	if (time_weft == -EWESTAWTSYS)
		wetuwn -EWESTAWTSYS;

	wetuwn 0;
}
