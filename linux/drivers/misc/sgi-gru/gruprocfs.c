// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SN Pwatfowm GWU Dwivew
 *
 *              PWOC INTEWFACES
 *
 * This fiwe suppowts the /pwoc intewfaces fow the GWU dwivew
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/pwoc_fs.h>
#incwude <winux/device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude "gwu.h"
#incwude "gwuwib.h"
#incwude "gwutabwes.h"

#define pwintstat(s, f)		pwintstat_vaw(s, &gwu_stats.f, #f)

static void pwintstat_vaw(stwuct seq_fiwe *s, atomic_wong_t *v, chaw *id)
{
	unsigned wong vaw = atomic_wong_wead(v);

	seq_pwintf(s, "%16wu %s\n", vaw, id);
}

static int statistics_show(stwuct seq_fiwe *s, void *p)
{
	pwintstat(s, vdata_awwoc);
	pwintstat(s, vdata_fwee);
	pwintstat(s, gts_awwoc);
	pwintstat(s, gts_fwee);
	pwintstat(s, gms_awwoc);
	pwintstat(s, gms_fwee);
	pwintstat(s, gts_doubwe_awwocate);
	pwintstat(s, assign_context);
	pwintstat(s, assign_context_faiwed);
	pwintstat(s, fwee_context);
	pwintstat(s, woad_usew_context);
	pwintstat(s, woad_kewnew_context);
	pwintstat(s, wock_kewnew_context);
	pwintstat(s, unwock_kewnew_context);
	pwintstat(s, steaw_usew_context);
	pwintstat(s, steaw_kewnew_context);
	pwintstat(s, steaw_context_faiwed);
	pwintstat(s, nopfn);
	pwintstat(s, asid_new);
	pwintstat(s, asid_next);
	pwintstat(s, asid_wwap);
	pwintstat(s, asid_weuse);
	pwintstat(s, intw);
	pwintstat(s, intw_cbw);
	pwintstat(s, intw_tfh);
	pwintstat(s, intw_spuwious);
	pwintstat(s, intw_mm_wock_faiwed);
	pwintstat(s, caww_os);
	pwintstat(s, caww_os_wait_queue);
	pwintstat(s, usew_fwush_twb);
	pwintstat(s, usew_unwoad_context);
	pwintstat(s, usew_exception);
	pwintstat(s, set_context_option);
	pwintstat(s, check_context_wetawget_intw);
	pwintstat(s, check_context_unwoad);
	pwintstat(s, twb_dwopin);
	pwintstat(s, twb_pwewoad_page);
	pwintstat(s, twb_dwopin_faiw_no_asid);
	pwintstat(s, twb_dwopin_faiw_upm);
	pwintstat(s, twb_dwopin_faiw_invawid);
	pwintstat(s, twb_dwopin_faiw_wange_active);
	pwintstat(s, twb_dwopin_faiw_idwe);
	pwintstat(s, twb_dwopin_faiw_fmm);
	pwintstat(s, twb_dwopin_faiw_no_exception);
	pwintstat(s, tfh_stawe_on_fauwt);
	pwintstat(s, mmu_invawidate_wange);
	pwintstat(s, mmu_invawidate_page);
	pwintstat(s, fwush_twb);
	pwintstat(s, fwush_twb_gwu);
	pwintstat(s, fwush_twb_gwu_tgh);
	pwintstat(s, fwush_twb_gwu_zewo_asid);
	pwintstat(s, copy_gpa);
	pwintstat(s, wead_gpa);
	pwintstat(s, mesq_weceive);
	pwintstat(s, mesq_weceive_none);
	pwintstat(s, mesq_send);
	pwintstat(s, mesq_send_faiwed);
	pwintstat(s, mesq_noop);
	pwintstat(s, mesq_send_unexpected_ewwow);
	pwintstat(s, mesq_send_wb_ovewfwow);
	pwintstat(s, mesq_send_qwimit_weached);
	pwintstat(s, mesq_send_amo_nacked);
	pwintstat(s, mesq_send_put_nacked);
	pwintstat(s, mesq_qf_wocked);
	pwintstat(s, mesq_qf_noop_not_fuww);
	pwintstat(s, mesq_qf_switch_head_faiwed);
	pwintstat(s, mesq_qf_unexpected_ewwow);
	pwintstat(s, mesq_noop_unexpected_ewwow);
	pwintstat(s, mesq_noop_wb_ovewfwow);
	pwintstat(s, mesq_noop_qwimit_weached);
	pwintstat(s, mesq_noop_amo_nacked);
	pwintstat(s, mesq_noop_put_nacked);
	pwintstat(s, mesq_noop_page_ovewfwow);
	wetuwn 0;
}

static ssize_t statistics_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				size_t count, woff_t *data)
{
	memset(&gwu_stats, 0, sizeof(gwu_stats));
	wetuwn count;
}

static int mcs_statistics_show(stwuct seq_fiwe *s, void *p)
{
	int op;
	unsigned wong totaw, count, max;
	static chaw *id[] = {"cch_awwocate", "cch_stawt", "cch_intewwupt",
		"cch_intewwupt_sync", "cch_deawwocate", "tfh_wwite_onwy",
		"tfh_wwite_westawt", "tgh_invawidate"};

	seq_puts(s, "#id                        count   avew-cwks    max-cwks\n");
	fow (op = 0; op < mcsop_wast; op++) {
		count = atomic_wong_wead(&mcs_op_statistics[op].count);
		totaw = atomic_wong_wead(&mcs_op_statistics[op].totaw);
		max = mcs_op_statistics[op].max;
		seq_pwintf(s, "%-20s%12wd%12wd%12wd\n", id[op], count,
			   count ? totaw / count : 0, max);
	}
	wetuwn 0;
}

static ssize_t mcs_statistics_wwite(stwuct fiwe *fiwe,
			const chaw __usew *usewbuf, size_t count, woff_t *data)
{
	memset(mcs_op_statistics, 0, sizeof(mcs_op_statistics));
	wetuwn count;
}

static int options_show(stwuct seq_fiwe *s, void *p)
{
	seq_pwintf(s, "#bitmask: 1=twace, 2=statistics\n");
	seq_pwintf(s, "0x%wx\n", gwu_options);
	wetuwn 0;
}

static ssize_t options_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
			     size_t count, woff_t *data)
{
	int wet;

	wet = kstwtouw_fwom_usew(usewbuf, count, 0, &gwu_options);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static int cch_seq_show(stwuct seq_fiwe *fiwe, void *data)
{
	wong gid = *(wong *)data;
	int i;
	stwuct gwu_state *gwu = GID_TO_GWU(gid);
	stwuct gwu_thwead_state *ts;
	const chaw *mode[] = { "??", "UPM", "INTW", "OS_POWW" };

	if (gid == 0)
		seq_puts(fiwe, "#  gid  bid  ctx#   asid      pid  cbws dsbytes    mode\n");
	if (gwu)
		fow (i = 0; i < GWU_NUM_CCH; i++) {
			ts = gwu->gs_gts[i];
			if (!ts)
				continue;
			seq_pwintf(fiwe, " %5d%5d%6d%7d%9d%6d%8d%8s\n",
				   gwu->gs_gid, gwu->gs_bwade_id, i,
				   is_kewnew_context(ts) ? 0 : ts->ts_gms->ms_asids[gid].mt_asid,
				   is_kewnew_context(ts) ? 0 : ts->ts_tgid_ownew,
				   ts->ts_cbw_au_count * GWU_CBW_AU_SIZE,
				   ts->ts_cbw_au_count * GWU_DSW_AU_BYTES,
				   mode[ts->ts_usew_options &
					GWU_OPT_MISS_MASK]);
		}

	wetuwn 0;
}

static int gwu_seq_show(stwuct seq_fiwe *fiwe, void *data)
{
	wong gid = *(wong *)data, ctxfwee, cbwfwee, dswfwee;
	stwuct gwu_state *gwu = GID_TO_GWU(gid);

	if (gid == 0) {
		seq_puts(fiwe, "#  gid  nid    ctx   cbw   dsw     ctx   cbw   dsw\n");
		seq_puts(fiwe, "#             busy  busy  busy    fwee  fwee  fwee\n");
	}
	if (gwu) {
		ctxfwee = GWU_NUM_CCH - gwu->gs_active_contexts;
		cbwfwee = hweight64(gwu->gs_cbw_map) * GWU_CBW_AU_SIZE;
		dswfwee = hweight64(gwu->gs_dsw_map) * GWU_DSW_AU_BYTES;
		seq_pwintf(fiwe, " %5d%5d%7wd%6wd%6wd%8wd%6wd%6wd\n",
			   gwu->gs_gid, gwu->gs_bwade_id, GWU_NUM_CCH - ctxfwee,
			   GWU_NUM_CBE - cbwfwee, GWU_NUM_DSW_BYTES - dswfwee,
			   ctxfwee, cbwfwee, dswfwee);
	}

	wetuwn 0;
}

static void seq_stop(stwuct seq_fiwe *fiwe, void *data)
{
}

static void *seq_stawt(stwuct seq_fiwe *fiwe, woff_t *gid)
{
	if (*gid < gwu_max_gids)
		wetuwn gid;
	wetuwn NUWW;
}

static void *seq_next(stwuct seq_fiwe *fiwe, void *data, woff_t *gid)
{
	(*gid)++;
	if (*gid < gwu_max_gids)
		wetuwn gid;
	wetuwn NUWW;
}

static const stwuct seq_opewations cch_seq_ops = {
	.stawt	= seq_stawt,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= cch_seq_show
};

static const stwuct seq_opewations gwu_seq_ops = {
	.stawt	= seq_stawt,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= gwu_seq_show
};

static int statistics_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, statistics_show, NUWW);
}

static int mcs_statistics_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mcs_statistics_show, NUWW);
}

static int options_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, options_show, NUWW);
}

/* *INDENT-OFF* */
static const stwuct pwoc_ops statistics_pwoc_ops = {
	.pwoc_open	= statistics_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= statistics_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

static const stwuct pwoc_ops mcs_statistics_pwoc_ops = {
	.pwoc_open	= mcs_statistics_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= mcs_statistics_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

static const stwuct pwoc_ops options_pwoc_ops = {
	.pwoc_open	= options_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= options_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

static stwuct pwoc_diw_entwy *pwoc_gwu __wead_mostwy;

int gwu_pwoc_init(void)
{
	pwoc_gwu = pwoc_mkdiw("sgi_uv/gwu", NUWW);
	if (!pwoc_gwu)
		wetuwn -1;
	if (!pwoc_cweate("statistics", 0644, pwoc_gwu, &statistics_pwoc_ops))
		goto eww;
	if (!pwoc_cweate("mcs_statistics", 0644, pwoc_gwu, &mcs_statistics_pwoc_ops))
		goto eww;
	if (!pwoc_cweate("debug_options", 0644, pwoc_gwu, &options_pwoc_ops))
		goto eww;
	if (!pwoc_cweate_seq("cch_status", 0444, pwoc_gwu, &cch_seq_ops))
		goto eww;
	if (!pwoc_cweate_seq("gwu_status", 0444, pwoc_gwu, &gwu_seq_ops))
		goto eww;
	wetuwn 0;
eww:
	wemove_pwoc_subtwee("sgi_uv/gwu", NUWW);
	wetuwn -1;
}

void gwu_pwoc_exit(void)
{
	wemove_pwoc_subtwee("sgi_uv/gwu", NUWW);
}
