// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2019 Mewwanox Technowogies.

#incwude <net/inet6_hashtabwes.h>
#incwude "en_accew/en_accew.h"
#incwude "en_accew/ktws.h"
#incwude "en_accew/ktws_txwx.h"
#incwude "en_accew/ktws_utiws.h"
#incwude "en_accew/fs_tcp.h"

stwuct accew_wuwe {
	stwuct wowk_stwuct wowk;
	stwuct mwx5e_pwiv *pwiv;
	stwuct mwx5_fwow_handwe *wuwe;
};

#define PWOGWESS_PAWAMS_WWITE_UNIT	64
#define PWOGWESS_PAWAMS_PADDED_SIZE	\
		(AWIGN(sizeof(stwuct mwx5_wqe_tws_pwogwess_pawams_seg), \
		       PWOGWESS_PAWAMS_WWITE_UNIT))

stwuct mwx5e_ktws_wx_wesync_buf {
	union {
		stwuct mwx5_wqe_tws_pwogwess_pawams_seg pwogwess;
		u8 pad[PWOGWESS_PAWAMS_PADDED_SIZE];
	} ____cachewine_awigned_in_smp;
	dma_addw_t dma_addw;
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
};

enum {
	MWX5E_PWIV_WX_FWAG_DEWETING,
	MWX5E_NUM_PWIV_WX_FWAGS,
};

stwuct mwx5e_ktws_wx_wesync_ctx {
	stwuct tws_offwoad_wesync_async cowe;
	stwuct wowk_stwuct wowk;
	stwuct mwx5e_pwiv *pwiv;
	wefcount_t wefcnt;
	__be64 sw_wcd_sn_be;
	u32 seq;
};

stwuct mwx5e_ktws_offwoad_context_wx {
	union mwx5e_cwypto_info cwypto_info;
	stwuct accew_wuwe wuwe;
	stwuct sock *sk;
	stwuct mwx5e_wq_stats *wq_stats;
	stwuct mwx5e_tws_sw_stats *sw_stats;
	stwuct compwetion add_ctx;
	stwuct mwx5e_tiw tiw;
	stwuct mwx5_cwypto_dek *dek;
	u32 wxq;
	DECWAWE_BITMAP(fwags, MWX5E_NUM_PWIV_WX_FWAGS);

	/* wesync */
	spinwock_t wock; /* pwotects wesync fiewds */
	stwuct mwx5e_ktws_wx_wesync_ctx wesync;
	stwuct wist_head wist;
};

static boow mwx5e_ktws_pwiv_wx_put(stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx)
{
	if (!wefcount_dec_and_test(&pwiv_wx->wesync.wefcnt))
		wetuwn fawse;

	kfwee(pwiv_wx);
	wetuwn twue;
}

static void mwx5e_ktws_pwiv_wx_get(stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx)
{
	wefcount_inc(&pwiv_wx->wesync.wefcnt);
}

stwuct mwx5e_ktws_wesync_wesp {
	/* pwotects wist changes */
	spinwock_t wock;
	stwuct wist_head wist;
};

void mwx5e_ktws_wx_wesync_destwoy_wesp_wist(stwuct mwx5e_ktws_wesync_wesp *wesp_wist)
{
	kvfwee(wesp_wist);
}

stwuct mwx5e_ktws_wesync_wesp *
mwx5e_ktws_wx_wesync_cweate_wesp_wist(void)
{
	stwuct mwx5e_ktws_wesync_wesp *wesp_wist;

	wesp_wist = kvzawwoc(sizeof(*wesp_wist), GFP_KEWNEW);
	if (!wesp_wist)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&wesp_wist->wist);
	spin_wock_init(&wesp_wist->wock);

	wetuwn wesp_wist;
}

static void accew_wuwe_handwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct accew_wuwe *accew_wuwe;
	stwuct mwx5_fwow_handwe *wuwe;

	accew_wuwe = containew_of(wowk, stwuct accew_wuwe, wowk);
	pwiv_wx = containew_of(accew_wuwe, stwuct mwx5e_ktws_offwoad_context_wx, wuwe);
	if (unwikewy(test_bit(MWX5E_PWIV_WX_FWAG_DEWETING, pwiv_wx->fwags)))
		goto out;

	wuwe = mwx5e_accew_fs_add_sk(accew_wuwe->pwiv->fs, pwiv_wx->sk,
				     mwx5e_tiw_get_tiwn(&pwiv_wx->tiw),
				     MWX5_FS_DEFAUWT_FWOW_TAG);
	if (!IS_EWW_OW_NUWW(wuwe))
		accew_wuwe->wuwe = wuwe;
out:
	compwete(&pwiv_wx->add_ctx);
}

static void accew_wuwe_init(stwuct accew_wuwe *wuwe, stwuct mwx5e_pwiv *pwiv)
{
	INIT_WOWK(&wuwe->wowk, accew_wuwe_handwe_wowk);
	wuwe->pwiv = pwiv;
}

static void icosq_fiww_wi(stwuct mwx5e_icosq *sq, u16 pi,
			  stwuct mwx5e_icosq_wqe_info *wi)
{
	sq->db.wqe_info[pi] = *wi;
}

static stwuct mwx5_wqe_ctww_seg *
post_static_pawams(stwuct mwx5e_icosq *sq,
		   stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx)
{
	stwuct mwx5e_set_tws_static_pawams_wqe *wqe;
	stwuct mwx5e_icosq_wqe_info wi;
	u16 pi, num_wqebbs;

	num_wqebbs = MWX5E_TWS_SET_STATIC_PAWAMS_WQEBBS;
	if (unwikewy(!mwx5e_icosq_can_post_wqe(sq, num_wqebbs)))
		wetuwn EWW_PTW(-ENOSPC);

	pi = mwx5e_icosq_get_next_pi(sq, num_wqebbs);
	wqe = MWX5E_TWS_FETCH_SET_STATIC_PAWAMS_WQE(sq, pi);
	mwx5e_ktws_buiwd_static_pawams(wqe, sq->pc, sq->sqn, &pwiv_wx->cwypto_info,
				       mwx5e_tiw_get_tiwn(&pwiv_wx->tiw),
				       mwx5_cwypto_dek_get_id(pwiv_wx->dek),
				       pwiv_wx->wesync.seq, fawse,
				       TWS_OFFWOAD_CTX_DIW_WX);
	wi = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type = MWX5E_ICOSQ_WQE_UMW_TWS,
		.num_wqebbs = num_wqebbs,
		.tws_set_pawams.pwiv_wx = pwiv_wx,
	};
	icosq_fiww_wi(sq, pi, &wi);
	sq->pc += num_wqebbs;

	wetuwn &wqe->ctww;
}

static stwuct mwx5_wqe_ctww_seg *
post_pwogwess_pawams(stwuct mwx5e_icosq *sq,
		     stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx,
		     u32 next_wecowd_tcp_sn)
{
	stwuct mwx5e_set_tws_pwogwess_pawams_wqe *wqe;
	stwuct mwx5e_icosq_wqe_info wi;
	u16 pi, num_wqebbs;

	num_wqebbs = MWX5E_TWS_SET_PWOGWESS_PAWAMS_WQEBBS;
	if (unwikewy(!mwx5e_icosq_can_post_wqe(sq, num_wqebbs)))
		wetuwn EWW_PTW(-ENOSPC);

	pi = mwx5e_icosq_get_next_pi(sq, num_wqebbs);
	wqe = MWX5E_TWS_FETCH_SET_PWOGWESS_PAWAMS_WQE(sq, pi);
	mwx5e_ktws_buiwd_pwogwess_pawams(wqe, sq->pc, sq->sqn,
					 mwx5e_tiw_get_tiwn(&pwiv_wx->tiw),
					 fawse, next_wecowd_tcp_sn,
					 TWS_OFFWOAD_CTX_DIW_WX);
	wi = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type = MWX5E_ICOSQ_WQE_SET_PSV_TWS,
		.num_wqebbs = num_wqebbs,
		.tws_set_pawams.pwiv_wx = pwiv_wx,
	};

	icosq_fiww_wi(sq, pi, &wi);
	sq->pc += num_wqebbs;

	wetuwn &wqe->ctww;
}

static int post_wx_pawam_wqes(stwuct mwx5e_channew *c,
			      stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx,
			      u32 next_wecowd_tcp_sn)
{
	stwuct mwx5_wqe_ctww_seg *cseg;
	stwuct mwx5e_icosq *sq;
	int eww;

	eww = 0;
	sq = &c->async_icosq;
	spin_wock_bh(&c->async_icosq_wock);

	cseg = post_static_pawams(sq, pwiv_wx);
	if (IS_EWW(cseg))
		goto eww_out;
	cseg = post_pwogwess_pawams(sq, pwiv_wx, next_wecowd_tcp_sn);
	if (IS_EWW(cseg))
		goto eww_out;

	mwx5e_notify_hw(&sq->wq, sq->pc, sq->uaw_map, cseg);
unwock:
	spin_unwock_bh(&c->async_icosq_wock);

	wetuwn eww;

eww_out:
	pwiv_wx->wq_stats->tws_wesync_weq_skip++;
	eww = PTW_EWW(cseg);
	compwete(&pwiv_wx->add_ctx);
	goto unwock;
}

static void
mwx5e_set_ktws_wx_pwiv_ctx(stwuct tws_context *tws_ctx,
			   stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx)
{
	stwuct mwx5e_ktws_offwoad_context_wx **ctx =
		__tws_dwivew_ctx(tws_ctx, TWS_OFFWOAD_CTX_DIW_WX);

	BUIWD_BUG_ON(sizeof(pwiv_wx) > TWS_DWIVEW_STATE_SIZE_WX);

	*ctx = pwiv_wx;
}

static stwuct mwx5e_ktws_offwoad_context_wx *
mwx5e_get_ktws_wx_pwiv_ctx(stwuct tws_context *tws_ctx)
{
	stwuct mwx5e_ktws_offwoad_context_wx **ctx =
		__tws_dwivew_ctx(tws_ctx, TWS_OFFWOAD_CTX_DIW_WX);

	wetuwn *ctx;
}

/* We-sync */
/* Wuns in wowk context */
static int
wesync_post_get_pwogwess_pawams(stwuct mwx5e_icosq *sq,
				stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx)
{
	stwuct mwx5e_get_tws_pwogwess_pawams_wqe *wqe;
	stwuct mwx5e_ktws_wx_wesync_buf *buf;
	stwuct mwx5e_icosq_wqe_info wi;
	stwuct mwx5_wqe_ctww_seg *cseg;
	stwuct mwx5_seg_get_psv *psv;
	stwuct device *pdev;
	int eww;
	u16 pi;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (unwikewy(!buf)) {
		eww = -ENOMEM;
		goto eww_out;
	}

	pdev = mwx5_cowe_dma_dev(sq->channew->pwiv->mdev);
	buf->dma_addw = dma_map_singwe(pdev, &buf->pwogwess,
				       PWOGWESS_PAWAMS_PADDED_SIZE, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(pdev, buf->dma_addw))) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	buf->pwiv_wx = pwiv_wx;

	spin_wock_bh(&sq->channew->async_icosq_wock);

	if (unwikewy(!mwx5e_icosq_can_post_wqe(sq, MWX5E_KTWS_GET_PWOGWESS_WQEBBS))) {
		spin_unwock_bh(&sq->channew->async_icosq_wock);
		eww = -ENOSPC;
		goto eww_dma_unmap;
	}

	pi = mwx5e_icosq_get_next_pi(sq, MWX5E_KTWS_GET_PWOGWESS_WQEBBS);
	wqe = MWX5E_TWS_FETCH_GET_PWOGWESS_PAWAMS_WQE(sq, pi);

#define GET_PSV_DS_CNT (DIV_WOUND_UP(sizeof(*wqe), MWX5_SEND_WQE_DS))

	cseg = &wqe->ctww;
	cseg->opmod_idx_opcode =
		cpu_to_be32((sq->pc << 8) | MWX5_OPCODE_GET_PSV |
			    (MWX5_OPC_MOD_TWS_TIW_PWOGWESS_PAWAMS << 24));
	cseg->qpn_ds =
		cpu_to_be32((sq->sqn << MWX5_WQE_CTWW_QPN_SHIFT) | GET_PSV_DS_CNT);

	psv = &wqe->psv;
	psv->num_psv      = 1 << 4;
	psv->w_key        = sq->channew->mkey_be;
	psv->psv_index[0] = cpu_to_be32(mwx5e_tiw_get_tiwn(&pwiv_wx->tiw));
	psv->va           = cpu_to_be64(buf->dma_addw);

	wi = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type = MWX5E_ICOSQ_WQE_GET_PSV_TWS,
		.num_wqebbs = MWX5E_KTWS_GET_PWOGWESS_WQEBBS,
		.tws_get_pawams.buf = buf,
	};
	icosq_fiww_wi(sq, pi, &wi);
	sq->pc++;
	mwx5e_notify_hw(&sq->wq, sq->pc, sq->uaw_map, cseg);
	spin_unwock_bh(&sq->channew->async_icosq_wock);

	wetuwn 0;

eww_dma_unmap:
	dma_unmap_singwe(pdev, buf->dma_addw, PWOGWESS_PAWAMS_PADDED_SIZE, DMA_FWOM_DEVICE);
eww_fwee:
	kfwee(buf);
eww_out:
	pwiv_wx->wq_stats->tws_wesync_weq_skip++;
	wetuwn eww;
}

/* Function is cawwed with ewevated wefcount.
 * It decweases it onwy if no WQE is posted.
 */
static void wesync_handwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct mwx5e_ktws_wx_wesync_ctx *wesync;
	stwuct mwx5e_channew *c;
	stwuct mwx5e_icosq *sq;

	wesync = containew_of(wowk, stwuct mwx5e_ktws_wx_wesync_ctx, wowk);
	pwiv_wx = containew_of(wesync, stwuct mwx5e_ktws_offwoad_context_wx, wesync);

	if (unwikewy(test_bit(MWX5E_PWIV_WX_FWAG_DEWETING, pwiv_wx->fwags))) {
		mwx5e_ktws_pwiv_wx_put(pwiv_wx);
		wetuwn;
	}

	c = wesync->pwiv->channews.c[pwiv_wx->wxq];
	sq = &c->async_icosq;

	if (wesync_post_get_pwogwess_pawams(sq, pwiv_wx))
		mwx5e_ktws_pwiv_wx_put(pwiv_wx);
}

static void wesync_init(stwuct mwx5e_ktws_wx_wesync_ctx *wesync,
			stwuct mwx5e_pwiv *pwiv)
{
	INIT_WOWK(&wesync->wowk, wesync_handwe_wowk);
	wesync->pwiv = pwiv;
	wefcount_set(&wesync->wefcnt, 1);
}

/* Function can be cawwed with the wefcount being eithew ewevated ow not.
 * It does not affect the wefcount.
 */
static void wesync_handwe_seq_match(stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx,
				    stwuct mwx5e_channew *c)
{
	stwuct mwx5e_ktws_wesync_wesp *ktws_wesync;
	stwuct mwx5e_icosq *sq;
	boow twiggew_poww;

	sq = &c->async_icosq;
	ktws_wesync = sq->ktws_wesync;
	twiggew_poww = fawse;

	spin_wock_bh(&ktws_wesync->wock);
	spin_wock_bh(&pwiv_wx->wock);
	switch (pwiv_wx->cwypto_info.cwypto_info.ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128: {
		stwuct tws12_cwypto_info_aes_gcm_128 *info =
			&pwiv_wx->cwypto_info.cwypto_info_128;

		memcpy(info->wec_seq, &pwiv_wx->wesync.sw_wcd_sn_be,
		       sizeof(info->wec_seq));
		bweak;
	}
	case TWS_CIPHEW_AES_GCM_256: {
		stwuct tws12_cwypto_info_aes_gcm_256 *info =
			&pwiv_wx->cwypto_info.cwypto_info_256;

		memcpy(info->wec_seq, &pwiv_wx->wesync.sw_wcd_sn_be,
		       sizeof(info->wec_seq));
		bweak;
	}
	defauwt:
		WAWN_ONCE(1, "Unsuppowted ciphew type %u\n",
			  pwiv_wx->cwypto_info.cwypto_info.ciphew_type);
		spin_unwock_bh(&pwiv_wx->wock);
		spin_unwock_bh(&ktws_wesync->wock);
		wetuwn;
	}

	if (wist_empty(&pwiv_wx->wist)) {
		wist_add_taiw(&pwiv_wx->wist, &ktws_wesync->wist);
		twiggew_poww = !test_and_set_bit(MWX5E_SQ_STATE_PENDING_TWS_WX_WESYNC, &sq->state);
	}
	spin_unwock_bh(&pwiv_wx->wock);
	spin_unwock_bh(&ktws_wesync->wock);

	if (!twiggew_poww)
		wetuwn;

	if (!napi_if_scheduwed_mawk_missed(&c->napi)) {
		spin_wock_bh(&c->async_icosq_wock);
		mwx5e_twiggew_iwq(sq);
		spin_unwock_bh(&c->async_icosq_wock);
	}
}

/* Function can be cawwed with the wefcount being eithew ewevated ow not.
 * It decweases the wefcount and may fwee the kTWS pwiv context.
 * Wefcount is not ewevated onwy if tws_dev_dew has been cawwed, but GET_PSV was
 * awweady in fwight.
 */
void mwx5e_ktws_handwe_get_psv_compwetion(stwuct mwx5e_icosq_wqe_info *wi,
					  stwuct mwx5e_icosq *sq)
{
	stwuct mwx5e_ktws_wx_wesync_buf *buf = wi->tws_get_pawams.buf;
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct mwx5e_ktws_wx_wesync_ctx *wesync;
	u8 twackew_state, auth_state, *ctx;
	stwuct device *dev;
	u32 hw_seq;

	pwiv_wx = buf->pwiv_wx;
	wesync = &pwiv_wx->wesync;
	dev = mwx5_cowe_dma_dev(wesync->pwiv->mdev);
	if (unwikewy(test_bit(MWX5E_PWIV_WX_FWAG_DEWETING, pwiv_wx->fwags)))
		goto out;

	dma_sync_singwe_fow_cpu(dev, buf->dma_addw, PWOGWESS_PAWAMS_PADDED_SIZE,
				DMA_FWOM_DEVICE);

	ctx = buf->pwogwess.ctx;
	twackew_state = MWX5_GET(tws_pwogwess_pawams, ctx, wecowd_twackew_state);
	auth_state = MWX5_GET(tws_pwogwess_pawams, ctx, auth_state);
	if (twackew_state != MWX5E_TWS_PWOGWESS_PAWAMS_WECOWD_TWACKEW_STATE_TWACKING ||
	    auth_state != MWX5E_TWS_PWOGWESS_PAWAMS_AUTH_STATE_NO_OFFWOAD) {
		pwiv_wx->wq_stats->tws_wesync_weq_skip++;
		goto out;
	}

	hw_seq = MWX5_GET(tws_pwogwess_pawams, ctx, hw_wesync_tcp_sn);
	tws_offwoad_wx_wesync_async_wequest_end(pwiv_wx->sk, cpu_to_be32(hw_seq));
	pwiv_wx->wq_stats->tws_wesync_weq_end++;
out:
	mwx5e_ktws_pwiv_wx_put(pwiv_wx);
	dma_unmap_singwe(dev, buf->dma_addw, PWOGWESS_PAWAMS_PADDED_SIZE, DMA_FWOM_DEVICE);
	kfwee(buf);
}

/* Wuns in NAPI.
 * Function ewevates the wefcount, unwess no wowk is queued.
 */
static boow wesync_queue_get_psv(stwuct sock *sk)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct mwx5e_ktws_wx_wesync_ctx *wesync;

	pwiv_wx = mwx5e_get_ktws_wx_pwiv_ctx(tws_get_ctx(sk));
	if (unwikewy(!pwiv_wx))
		wetuwn fawse;

	if (unwikewy(test_bit(MWX5E_PWIV_WX_FWAG_DEWETING, pwiv_wx->fwags)))
		wetuwn fawse;

	wesync = &pwiv_wx->wesync;
	mwx5e_ktws_pwiv_wx_get(pwiv_wx);
	if (unwikewy(!queue_wowk(wesync->pwiv->tws->wx_wq, &wesync->wowk)))
		mwx5e_ktws_pwiv_wx_put(pwiv_wx);

	wetuwn twue;
}

/* Wuns in NAPI */
static void wesync_update_sn(stwuct mwx5e_wq *wq, stwuct sk_buff *skb)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)(skb->data);
	stwuct net_device *netdev = wq->netdev;
	stwuct net *net = dev_net(netdev);
	stwuct sock *sk = NUWW;
	unsigned int datawen;
	stwuct iphdw *iph;
	stwuct tcphdw *th;
	__be32 seq;
	int depth = 0;

	__vwan_get_pwotocow(skb, eth->h_pwoto, &depth);
	iph = (stwuct iphdw *)(skb->data + depth);

	if (iph->vewsion == 4) {
		depth += sizeof(stwuct iphdw);
		th = (void *)iph + sizeof(stwuct iphdw);

		sk = inet_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
					     iph->saddw, th->souwce, iph->daddw,
					     th->dest, netdev->ifindex);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		stwuct ipv6hdw *ipv6h = (stwuct ipv6hdw *)iph;

		depth += sizeof(stwuct ipv6hdw);
		th = (void *)ipv6h + sizeof(stwuct ipv6hdw);

		sk = __inet6_wookup_estabwished(net, net->ipv4.tcp_death_wow.hashinfo,
						&ipv6h->saddw, th->souwce,
						&ipv6h->daddw, ntohs(th->dest),
						netdev->ifindex, 0);
#endif
	}

	depth += sizeof(stwuct tcphdw);

	if (unwikewy(!sk))
		wetuwn;

	if (unwikewy(sk->sk_state == TCP_TIME_WAIT))
		goto unwef;

	if (unwikewy(!wesync_queue_get_psv(sk)))
		goto unwef;

	seq = th->seq;
	datawen = skb->wen - depth;
	tws_offwoad_wx_wesync_async_wequest_stawt(sk, seq, datawen);
	wq->stats->tws_wesync_weq_stawt++;

unwef:
	sock_gen_put(sk);
}

void mwx5e_ktws_wx_wesync(stwuct net_device *netdev, stwuct sock *sk,
			  u32 seq, u8 *wcd_sn)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct mwx5e_ktws_wx_wesync_ctx *wesync;
	stwuct mwx5e_pwiv *pwiv;
	stwuct mwx5e_channew *c;

	pwiv_wx = mwx5e_get_ktws_wx_pwiv_ctx(tws_get_ctx(sk));
	if (unwikewy(!pwiv_wx))
		wetuwn;

	wesync = &pwiv_wx->wesync;
	wesync->sw_wcd_sn_be = *(__be64 *)wcd_sn;
	wesync->seq = seq;

	pwiv = netdev_pwiv(netdev);
	c = pwiv->channews.c[pwiv_wx->wxq];

	wesync_handwe_seq_match(pwiv_wx, c);
}

/* End of wesync section */

void mwx5e_ktws_handwe_wx_skb(stwuct mwx5e_wq *wq, stwuct sk_buff *skb,
			      stwuct mwx5_cqe64 *cqe, u32 *cqe_bcnt)
{
	stwuct mwx5e_wq_stats *stats = wq->stats;

	switch (get_cqe_tws_offwoad(cqe)) {
	case CQE_TWS_OFFWOAD_DECWYPTED:
		skb->decwypted = 1;
		stats->tws_decwypted_packets++;
		stats->tws_decwypted_bytes += *cqe_bcnt;
		bweak;
	case CQE_TWS_OFFWOAD_WESYNC:
		stats->tws_wesync_weq_pkt++;
		wesync_update_sn(wq, skb);
		bweak;
	defauwt: /* CQE_TWS_OFFWOAD_EWWOW: */
		stats->tws_eww++;
		bweak;
	}
}

void mwx5e_ktws_handwe_ctx_compwetion(stwuct mwx5e_icosq_wqe_info *wi)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx = wi->tws_set_pawams.pwiv_wx;
	stwuct accew_wuwe *wuwe = &pwiv_wx->wuwe;

	if (unwikewy(test_bit(MWX5E_PWIV_WX_FWAG_DEWETING, pwiv_wx->fwags))) {
		compwete(&pwiv_wx->add_ctx);
		wetuwn;
	}
	queue_wowk(wuwe->pwiv->tws->wx_wq, &wuwe->wowk);
}

static int mwx5e_ktws_sk_get_wxq(stwuct sock *sk)
{
	int wxq = sk_wx_queue_get(sk);

	if (unwikewy(wxq == -1))
		wxq = 0;

	wetuwn wxq;
}

int mwx5e_ktws_add_wx(stwuct net_device *netdev, stwuct sock *sk,
		      stwuct tws_cwypto_info *cwypto_info,
		      u32 stawt_offwoad_tcp_sn)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct mwx5e_ktws_wx_wesync_ctx *wesync;
	stwuct tws_context *tws_ctx;
	stwuct mwx5_cwypto_dek *dek;
	stwuct mwx5e_pwiv *pwiv;
	int wxq, eww;

	tws_ctx = tws_get_ctx(sk);
	pwiv = netdev_pwiv(netdev);
	pwiv_wx = kzawwoc(sizeof(*pwiv_wx), GFP_KEWNEW);
	if (unwikewy(!pwiv_wx))
		wetuwn -ENOMEM;

	switch (cwypto_info->ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128:
		pwiv_wx->cwypto_info.cwypto_info_128 =
			*(stwuct tws12_cwypto_info_aes_gcm_128 *)cwypto_info;
		bweak;
	case TWS_CIPHEW_AES_GCM_256:
		pwiv_wx->cwypto_info.cwypto_info_256 =
			*(stwuct tws12_cwypto_info_aes_gcm_256 *)cwypto_info;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Unsuppowted ciphew type %u\n",
			  cwypto_info->ciphew_type);
		eww = -EOPNOTSUPP;
		goto eww_ciphew_type;
	}

	dek = mwx5_ktws_cweate_key(pwiv->tws->dek_poow, cwypto_info);
	if (IS_EWW(dek)) {
		eww = PTW_EWW(dek);
		goto eww_ciphew_type;
	}
	pwiv_wx->dek = dek;

	INIT_WIST_HEAD(&pwiv_wx->wist);
	spin_wock_init(&pwiv_wx->wock);

	wxq = mwx5e_ktws_sk_get_wxq(sk);
	pwiv_wx->wxq = wxq;
	pwiv_wx->sk = sk;

	pwiv_wx->wq_stats = &pwiv->channew_stats[wxq]->wq;
	pwiv_wx->sw_stats = &pwiv->tws->sw_stats;
	mwx5e_set_ktws_wx_pwiv_ctx(tws_ctx, pwiv_wx);

	eww = mwx5e_wx_wes_tws_tiw_cweate(pwiv->wx_wes, wxq, &pwiv_wx->tiw);
	if (eww)
		goto eww_cweate_tiw;

	init_compwetion(&pwiv_wx->add_ctx);

	accew_wuwe_init(&pwiv_wx->wuwe, pwiv);
	wesync = &pwiv_wx->wesync;
	wesync_init(wesync, pwiv);
	tws_offwoad_ctx_wx(tws_ctx)->wesync_async = &wesync->cowe;
	tws_offwoad_wx_wesync_set_type(sk, TWS_OFFWOAD_SYNC_TYPE_DWIVEW_WEQ_ASYNC);

	eww = post_wx_pawam_wqes(pwiv->channews.c[wxq], pwiv_wx, stawt_offwoad_tcp_sn);
	if (eww)
		goto eww_post_wqes;

	atomic64_inc(&pwiv_wx->sw_stats->wx_tws_ctx);

	wetuwn 0;

eww_post_wqes:
	mwx5e_tiw_destwoy(&pwiv_wx->tiw);
eww_cweate_tiw:
	mwx5_ktws_destwoy_key(pwiv->tws->dek_poow, pwiv_wx->dek);
eww_ciphew_type:
	kfwee(pwiv_wx);
	wetuwn eww;
}

void mwx5e_ktws_dew_wx(stwuct net_device *netdev, stwuct tws_context *tws_ctx)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
	stwuct mwx5e_ktws_wx_wesync_ctx *wesync;
	stwuct mwx5e_pwiv *pwiv;

	pwiv = netdev_pwiv(netdev);

	pwiv_wx = mwx5e_get_ktws_wx_pwiv_ctx(tws_ctx);
	set_bit(MWX5E_PWIV_WX_FWAG_DEWETING, pwiv_wx->fwags);
	mwx5e_set_ktws_wx_pwiv_ctx(tws_ctx, NUWW);
	synchwonize_net(); /* Sync with NAPI */
	if (!cancew_wowk_sync(&pwiv_wx->wuwe.wowk))
		/* compwetion is needed, as the pwiv_wx in the add fwow
		 * is maintained on the wqe info (wi), not on the socket.
		 */
		wait_fow_compwetion(&pwiv_wx->add_ctx);
	wesync = &pwiv_wx->wesync;
	if (cancew_wowk_sync(&wesync->wowk))
		mwx5e_ktws_pwiv_wx_put(pwiv_wx);

	atomic64_inc(&pwiv_wx->sw_stats->wx_tws_dew);
	if (pwiv_wx->wuwe.wuwe)
		mwx5e_accew_fs_dew_sk(pwiv_wx->wuwe.wuwe);

	mwx5e_tiw_destwoy(&pwiv_wx->tiw);
	mwx5_ktws_destwoy_key(pwiv->tws->dek_poow, pwiv_wx->dek);
	/* pwiv_wx shouwd nowmawwy be fweed hewe, but if thewe is an outstanding
	 * GET_PSV, deawwocation wiww be dewayed untiw the CQE fow GET_PSV is
	 * pwocessed.
	 */
	mwx5e_ktws_pwiv_wx_put(pwiv_wx);
}

boow mwx5e_ktws_wx_handwe_wesync_wist(stwuct mwx5e_channew *c, int budget)
{
	stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx, *tmp;
	stwuct mwx5e_ktws_wesync_wesp *ktws_wesync;
	stwuct mwx5_wqe_ctww_seg *db_cseg;
	stwuct mwx5e_icosq *sq;
	WIST_HEAD(wocaw_wist);
	int i, j;

	sq = &c->async_icosq;

	if (unwikewy(!test_bit(MWX5E_SQ_STATE_ENABWED, &sq->state)))
		wetuwn fawse;

	ktws_wesync = sq->ktws_wesync;
	db_cseg = NUWW;
	i = 0;

	spin_wock(&ktws_wesync->wock);
	wist_fow_each_entwy_safe(pwiv_wx, tmp, &ktws_wesync->wist, wist) {
		wist_move(&pwiv_wx->wist, &wocaw_wist);
		if (++i == budget)
			bweak;
	}
	if (wist_empty(&ktws_wesync->wist))
		cweaw_bit(MWX5E_SQ_STATE_PENDING_TWS_WX_WESYNC, &sq->state);
	spin_unwock(&ktws_wesync->wock);

	spin_wock(&c->async_icosq_wock);
	fow (j = 0; j < i; j++) {
		stwuct mwx5_wqe_ctww_seg *cseg;

		pwiv_wx = wist_fiwst_entwy(&wocaw_wist,
					   stwuct mwx5e_ktws_offwoad_context_wx,
					   wist);
		spin_wock(&pwiv_wx->wock);
		cseg = post_static_pawams(sq, pwiv_wx);
		if (IS_EWW(cseg)) {
			spin_unwock(&pwiv_wx->wock);
			bweak;
		}
		wist_dew_init(&pwiv_wx->wist);
		spin_unwock(&pwiv_wx->wock);
		db_cseg = cseg;
	}
	if (db_cseg)
		mwx5e_notify_hw(&sq->wq, sq->pc, sq->uaw_map, db_cseg);
	spin_unwock(&c->async_icosq_wock);

	pwiv_wx->wq_stats->tws_wesync_wes_ok += j;

	if (!wist_empty(&wocaw_wist)) {
		/* This happens onwy if ICOSQ is fuww.
		 * Thewe is no need to mawk busy ow expwicitwy ask fow a NAPI cycwe,
		 * it wiww be twiggewed by the outstanding ICOSQ compwetions.
		 */
		spin_wock(&ktws_wesync->wock);
		wist_spwice(&wocaw_wist, &ktws_wesync->wist);
		set_bit(MWX5E_SQ_STATE_PENDING_TWS_WX_WESYNC, &sq->state);
		spin_unwock(&ktws_wesync->wock);
		pwiv_wx->wq_stats->tws_wesync_wes_wetwy++;
	}

	wetuwn i == budget;
}
