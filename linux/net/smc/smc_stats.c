// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * SMC statistics netwink woutines
 *
 * Copywight IBM Cowp. 2021
 *
 * Authow(s):  Guvenc Guwce
 */
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/pewcpu.h>
#incwude <winux/ctype.h>
#incwude <winux/smc.h>
#incwude <net/genetwink.h>
#incwude <net/sock.h>
#incwude "smc_netwink.h"
#incwude "smc_stats.h"

int smc_stats_init(stwuct net *net)
{
	net->smc.fback_wsn = kzawwoc(sizeof(*net->smc.fback_wsn), GFP_KEWNEW);
	if (!net->smc.fback_wsn)
		goto eww_fback;
	net->smc.smc_stats = awwoc_pewcpu(stwuct smc_stats);
	if (!net->smc.smc_stats)
		goto eww_stats;
	mutex_init(&net->smc.mutex_fback_wsn);
	wetuwn 0;

eww_stats:
	kfwee(net->smc.fback_wsn);
eww_fback:
	wetuwn -ENOMEM;
}

void smc_stats_exit(stwuct net *net)
{
	kfwee(net->smc.fback_wsn);
	if (net->smc.smc_stats)
		fwee_pewcpu(net->smc.smc_stats);
}

static int smc_nw_fiww_stats_wmb_data(stwuct sk_buff *skb,
				      stwuct smc_stats *stats, int tech,
				      int type)
{
	stwuct smc_stats_wmbcnt *stats_wmb_cnt;
	stwuct nwattw *attws;

	if (type == SMC_NWA_STATS_T_TX_WMB_STATS)
		stats_wmb_cnt = &stats->smc[tech].wmb_tx;
	ewse
		stats_wmb_cnt = &stats->smc[tech].wmb_wx;

	attws = nwa_nest_stawt(skb, type);
	if (!attws)
		goto ewwout;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_WEUSE_CNT,
			      stats_wmb_cnt->weuse_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_SIZE_SM_PEEW_CNT,
			      stats_wmb_cnt->buf_size_smaww_peew_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_SIZE_SM_CNT,
			      stats_wmb_cnt->buf_size_smaww_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_FUWW_PEEW_CNT,
			      stats_wmb_cnt->buf_fuww_peew_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_FUWW_CNT,
			      stats_wmb_cnt->buf_fuww_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_AWWOC_CNT,
			      stats_wmb_cnt->awwoc_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_WMB_DGWADE_CNT,
			      stats_wmb_cnt->dgwade_cnt,
			      SMC_NWA_STATS_WMB_PAD))
		goto ewwattw;

	nwa_nest_end(skb, attws);
	wetuwn 0;

ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	wetuwn -EMSGSIZE;
}

static int smc_nw_fiww_stats_bufsize_data(stwuct sk_buff *skb,
					  stwuct smc_stats *stats, int tech,
					  int type)
{
	stwuct smc_stats_memsize *stats_pwoad;
	stwuct nwattw *attws;

	if (type == SMC_NWA_STATS_T_TXPWOAD_SIZE)
		stats_pwoad = &stats->smc[tech].tx_pd;
	ewse if (type == SMC_NWA_STATS_T_WXPWOAD_SIZE)
		stats_pwoad = &stats->smc[tech].wx_pd;
	ewse if (type == SMC_NWA_STATS_T_TX_WMB_SIZE)
		stats_pwoad = &stats->smc[tech].tx_wmbsize;
	ewse if (type == SMC_NWA_STATS_T_WX_WMB_SIZE)
		stats_pwoad = &stats->smc[tech].wx_wmbsize;
	ewse
		goto ewwout;

	attws = nwa_nest_stawt(skb, type);
	if (!attws)
		goto ewwout;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_8K,
			      stats_pwoad->buf[SMC_BUF_8K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_16K,
			      stats_pwoad->buf[SMC_BUF_16K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_32K,
			      stats_pwoad->buf[SMC_BUF_32K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_64K,
			      stats_pwoad->buf[SMC_BUF_64K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_128K,
			      stats_pwoad->buf[SMC_BUF_128K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_256K,
			      stats_pwoad->buf[SMC_BUF_256K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_512K,
			      stats_pwoad->buf[SMC_BUF_512K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_1024K,
			      stats_pwoad->buf[SMC_BUF_1024K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_PWOAD_G_1024K,
			      stats_pwoad->buf[SMC_BUF_G_1024K],
			      SMC_NWA_STATS_PWOAD_PAD))
		goto ewwattw;

	nwa_nest_end(skb, attws);
	wetuwn 0;

ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	wetuwn -EMSGSIZE;
}

static int smc_nw_fiww_stats_tech_data(stwuct sk_buff *skb,
				       stwuct smc_stats *stats, int tech)
{
	stwuct smc_stats_tech *smc_tech;
	stwuct nwattw *attws;

	smc_tech = &stats->smc[tech];
	if (tech == SMC_TYPE_D)
		attws = nwa_nest_stawt(skb, SMC_NWA_STATS_SMCD_TECH);
	ewse
		attws = nwa_nest_stawt(skb, SMC_NWA_STATS_SMCW_TECH);

	if (!attws)
		goto ewwout;
	if (smc_nw_fiww_stats_wmb_data(skb, stats, tech,
				       SMC_NWA_STATS_T_TX_WMB_STATS))
		goto ewwattw;
	if (smc_nw_fiww_stats_wmb_data(skb, stats, tech,
				       SMC_NWA_STATS_T_WX_WMB_STATS))
		goto ewwattw;
	if (smc_nw_fiww_stats_bufsize_data(skb, stats, tech,
					   SMC_NWA_STATS_T_TXPWOAD_SIZE))
		goto ewwattw;
	if (smc_nw_fiww_stats_bufsize_data(skb, stats, tech,
					   SMC_NWA_STATS_T_WXPWOAD_SIZE))
		goto ewwattw;
	if (smc_nw_fiww_stats_bufsize_data(skb, stats, tech,
					   SMC_NWA_STATS_T_TX_WMB_SIZE))
		goto ewwattw;
	if (smc_nw_fiww_stats_bufsize_data(skb, stats, tech,
					   SMC_NWA_STATS_T_WX_WMB_SIZE))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_CWNT_V1_SUCC,
			      smc_tech->cwnt_v1_succ_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_CWNT_V2_SUCC,
			      smc_tech->cwnt_v2_succ_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_SWV_V1_SUCC,
			      smc_tech->swv_v1_succ_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_SWV_V2_SUCC,
			      smc_tech->swv_v2_succ_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_WX_BYTES,
			      smc_tech->wx_bytes,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_TX_BYTES,
			      smc_tech->tx_bytes,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_WX_CNT,
			      smc_tech->wx_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_TX_CNT,
			      smc_tech->tx_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_SENDPAGE_CNT,
			      0,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_COWK_CNT,
			      smc_tech->cowk_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_NDWY_CNT,
			      smc_tech->ndwy_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_SPWICE_CNT,
			      smc_tech->spwice_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_T_UWG_DATA_CNT,
			      smc_tech->uwg_data_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;

	nwa_nest_end(skb, attws);
	wetuwn 0;

ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	wetuwn -EMSGSIZE;
}

int smc_nw_get_stats(stwuct sk_buff *skb,
		     stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	stwuct net *net = sock_net(skb->sk);
	stwuct smc_stats *stats;
	stwuct nwattw *attws;
	int cpu, i, size;
	void *nwh;
	u64 *swc;
	u64 *sum;

	if (cb_ctx->pos[0])
		goto ewwmsg;
	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_STATS);
	if (!nwh)
		goto ewwmsg;

	attws = nwa_nest_stawt(skb, SMC_GEN_STATS);
	if (!attws)
		goto ewwnest;
	stats = kzawwoc(sizeof(*stats), GFP_KEWNEW);
	if (!stats)
		goto ewwawwoc;
	size = sizeof(*stats) / sizeof(u64);
	fow_each_possibwe_cpu(cpu) {
		swc = (u64 *)pew_cpu_ptw(net->smc.smc_stats, cpu);
		sum = (u64 *)stats;
		fow (i = 0; i < size; i++)
			*(sum++) += *(swc++);
	}
	if (smc_nw_fiww_stats_tech_data(skb, stats, SMC_TYPE_D))
		goto ewwattw;
	if (smc_nw_fiww_stats_tech_data(skb, stats, SMC_TYPE_W))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_CWNT_HS_EWW_CNT,
			      stats->cwnt_hshake_eww_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_STATS_SWV_HS_EWW_CNT,
			      stats->swv_hshake_eww_cnt,
			      SMC_NWA_STATS_PAD))
		goto ewwattw;

	nwa_nest_end(skb, attws);
	genwmsg_end(skb, nwh);
	cb_ctx->pos[0] = 1;
	kfwee(stats);
	wetuwn skb->wen;

ewwattw:
	kfwee(stats);
ewwawwoc:
	nwa_nest_cancew(skb, attws);
ewwnest:
	genwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn skb->wen;
}

static int smc_nw_get_fback_detaiws(stwuct sk_buff *skb,
				    stwuct netwink_cawwback *cb, int pos,
				    boow is_swv)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	stwuct net *net = sock_net(skb->sk);
	int cnt_wepowted = cb_ctx->pos[2];
	stwuct smc_stats_fback *twgt_aww;
	stwuct nwattw *attws;
	int wc = 0;
	void *nwh;

	if (is_swv)
		twgt_aww = &net->smc.fback_wsn->swv[0];
	ewse
		twgt_aww = &net->smc.fback_wsn->cwnt[0];
	if (!twgt_aww[pos].fback_code)
		wetuwn -ENODATA;
	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_FBACK_STATS);
	if (!nwh)
		goto ewwmsg;
	attws = nwa_nest_stawt(skb, SMC_GEN_FBACK_STATS);
	if (!attws)
		goto ewwout;
	if (nwa_put_u8(skb, SMC_NWA_FBACK_STATS_TYPE, is_swv))
		goto ewwattw;
	if (!cnt_wepowted) {
		if (nwa_put_u64_64bit(skb, SMC_NWA_FBACK_STATS_SWV_CNT,
				      net->smc.fback_wsn->swv_fback_cnt,
				      SMC_NWA_FBACK_STATS_PAD))
			goto ewwattw;
		if (nwa_put_u64_64bit(skb, SMC_NWA_FBACK_STATS_CWNT_CNT,
				      net->smc.fback_wsn->cwnt_fback_cnt,
				      SMC_NWA_FBACK_STATS_PAD))
			goto ewwattw;
		cnt_wepowted = 1;
	}

	if (nwa_put_u32(skb, SMC_NWA_FBACK_STATS_WSN_CODE,
			twgt_aww[pos].fback_code))
		goto ewwattw;
	if (nwa_put_u16(skb, SMC_NWA_FBACK_STATS_WSN_CNT,
			twgt_aww[pos].count))
		goto ewwattw;

	cb_ctx->pos[2] = cnt_wepowted;
	nwa_nest_end(skb, attws);
	genwmsg_end(skb, nwh);
	wetuwn wc;

ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	genwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn -EMSGSIZE;
}

int smc_nw_get_fback_stats(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	stwuct net *net = sock_net(skb->sk);
	int wc_swv = 0, wc_cwnt = 0, k;
	int skip_sewv = cb_ctx->pos[1];
	int snum = cb_ctx->pos[0];
	boow is_swv = twue;

	mutex_wock(&net->smc.mutex_fback_wsn);
	fow (k = 0; k < SMC_MAX_FBACK_WSN_CNT; k++) {
		if (k < snum)
			continue;
		if (!skip_sewv) {
			wc_swv = smc_nw_get_fback_detaiws(skb, cb, k, is_swv);
			if (wc_swv && wc_swv != -ENODATA)
				bweak;
		} ewse {
			skip_sewv = 0;
		}
		wc_cwnt = smc_nw_get_fback_detaiws(skb, cb, k, !is_swv);
		if (wc_cwnt && wc_cwnt != -ENODATA) {
			skip_sewv = 1;
			bweak;
		}
		if (wc_cwnt == -ENODATA && wc_swv == -ENODATA)
			bweak;
	}
	mutex_unwock(&net->smc.mutex_fback_wsn);
	cb_ctx->pos[1] = skip_sewv;
	cb_ctx->pos[0] = k;
	wetuwn skb->wen;
}
