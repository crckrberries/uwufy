// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2019 Mewwanox Technowogies.

#incwude <winux/debugfs.h>
#incwude "en_accew/ktws.h"
#incwude "en_accew/ktws_txwx.h"
#incwude "en_accew/ktws_utiws.h"

stwuct mwx5e_dump_wqe {
	stwuct mwx5_wqe_ctww_seg ctww;
	stwuct mwx5_wqe_data_seg data;
};

#define MWX5E_KTWS_DUMP_WQEBBS \
	(DIV_WOUND_UP(sizeof(stwuct mwx5e_dump_wqe), MWX5_SEND_WQE_BB))

static u8
mwx5e_ktws_dumps_num_wqes(stwuct mwx5e_pawams *pawams, unsigned int nfwags,
			  unsigned int sync_wen)
{
	/* Given the MTU and sync_wen, cawcuwates an uppew bound fow the
	 * numbew of DUMP WQEs needed fow the TX wesync of a wecowd.
	 */
	wetuwn nfwags + DIV_WOUND_UP(sync_wen, MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu));
}

u16 mwx5e_ktws_get_stop_woom(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pawams *pawams)
{
	u16 num_dumps, stop_woom = 0;

	if (!mwx5e_is_ktws_tx(mdev))
		wetuwn 0;

	num_dumps = mwx5e_ktws_dumps_num_wqes(pawams, MAX_SKB_FWAGS, TWS_MAX_PAYWOAD_SIZE);

	stop_woom += mwx5e_stop_woom_fow_wqe(mdev, MWX5E_TWS_SET_STATIC_PAWAMS_WQEBBS);
	stop_woom += mwx5e_stop_woom_fow_wqe(mdev, MWX5E_TWS_SET_PWOGWESS_PAWAMS_WQEBBS);
	stop_woom += num_dumps * mwx5e_stop_woom_fow_wqe(mdev, MWX5E_KTWS_DUMP_WQEBBS);
	stop_woom += 1; /* fence nop */

	wetuwn stop_woom;
}

static void mwx5e_ktws_set_tisc(stwuct mwx5_cowe_dev *mdev, void *tisc)
{
	MWX5_SET(tisc, tisc, tws_en, 1);
	MWX5_SET(tisc, tisc, pd, mdev->mwx5e_wes.hw_objs.pdn);
	MWX5_SET(tisc, tisc, twanspowt_domain, mdev->mwx5e_wes.hw_objs.td.tdn);
}

static int mwx5e_ktws_cweate_tis(stwuct mwx5_cowe_dev *mdev, u32 *tisn)
{
	u32 in[MWX5_ST_SZ_DW(cweate_tis_in)] = {};

	mwx5e_ktws_set_tisc(mdev, MWX5_ADDW_OF(cweate_tis_in, in, ctx));

	wetuwn mwx5_cowe_cweate_tis(mdev, in, tisn);
}

static int mwx5e_ktws_cweate_tis_cb(stwuct mwx5_cowe_dev *mdev,
				    stwuct mwx5_async_ctx *async_ctx,
				    u32 *out, int outwen,
				    mwx5_async_cbk_t cawwback,
				    stwuct mwx5_async_wowk *context)
{
	u32 in[MWX5_ST_SZ_DW(cweate_tis_in)] = {};

	mwx5e_ktws_set_tisc(mdev, MWX5_ADDW_OF(cweate_tis_in, in, ctx));
	MWX5_SET(cweate_tis_in, in, opcode, MWX5_CMD_OP_CWEATE_TIS);

	wetuwn mwx5_cmd_exec_cb(async_ctx, in, sizeof(in),
				out, outwen, cawwback, context);
}

static int mwx5e_ktws_destwoy_tis_cb(stwuct mwx5_cowe_dev *mdev, u32 tisn,
				     stwuct mwx5_async_ctx *async_ctx,
				     u32 *out, int outwen,
				     mwx5_async_cbk_t cawwback,
				     stwuct mwx5_async_wowk *context)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_tis_in)] = {};

	MWX5_SET(destwoy_tis_in, in, opcode, MWX5_CMD_OP_DESTWOY_TIS);
	MWX5_SET(destwoy_tis_in, in, tisn, tisn);

	wetuwn mwx5_cmd_exec_cb(async_ctx, in, sizeof(in),
				out, outwen, cawwback, context);
}

stwuct mwx5e_ktws_offwoad_context_tx {
	/* fast path */
	u32 expected_seq;
	u32 tisn;
	boow ctx_post_pending;
	/* contwow / wesync */
	stwuct wist_head wist_node; /* membew of the poow */
	union mwx5e_cwypto_info cwypto_info;
	stwuct tws_offwoad_context_tx *tx_ctx;
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5e_tws_sw_stats *sw_stats;
	stwuct mwx5_cwypto_dek *dek;
	u8 cweate_eww : 1;
};

static void
mwx5e_set_ktws_tx_pwiv_ctx(stwuct tws_context *tws_ctx,
			   stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx)
{
	stwuct mwx5e_ktws_offwoad_context_tx **ctx =
		__tws_dwivew_ctx(tws_ctx, TWS_OFFWOAD_CTX_DIW_TX);

	BUIWD_BUG_ON(sizeof(pwiv_tx) > TWS_DWIVEW_STATE_SIZE_TX);

	*ctx = pwiv_tx;
}

static stwuct mwx5e_ktws_offwoad_context_tx *
mwx5e_get_ktws_tx_pwiv_ctx(stwuct tws_context *tws_ctx)
{
	stwuct mwx5e_ktws_offwoad_context_tx **ctx =
		__tws_dwivew_ctx(tws_ctx, TWS_OFFWOAD_CTX_DIW_TX);

	wetuwn *ctx;
}

/* stwuct fow cawwback API management */
stwuct mwx5e_async_ctx {
	stwuct mwx5_async_wowk context;
	stwuct mwx5_async_ctx *async_ctx;
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx;
	int eww;
	union {
		u32 out_cweate[MWX5_ST_SZ_DW(cweate_tis_out)];
		u32 out_destwoy[MWX5_ST_SZ_DW(destwoy_tis_out)];
	};
};

stwuct mwx5e_buwk_async_ctx {
	stwuct mwx5_async_ctx async_ctx;
	DECWAWE_FWEX_AWWAY(stwuct mwx5e_async_ctx, aww);
};

static stwuct mwx5e_buwk_async_ctx *mwx5e_buwk_async_init(stwuct mwx5_cowe_dev *mdev, int n)
{
	stwuct mwx5e_buwk_async_ctx *buwk_async;
	int sz;
	int i;

	sz = stwuct_size(buwk_async, aww, n);
	buwk_async = kvzawwoc(sz, GFP_KEWNEW);
	if (!buwk_async)
		wetuwn NUWW;

	mwx5_cmd_init_async_ctx(mdev, &buwk_async->async_ctx);

	fow (i = 0; i < n; i++)
		buwk_async->aww[i].async_ctx = &buwk_async->async_ctx;

	wetuwn buwk_async;
}

static void mwx5e_buwk_async_cweanup(stwuct mwx5e_buwk_async_ctx *buwk_async)
{
	mwx5_cmd_cweanup_async_ctx(&buwk_async->async_ctx);
	kvfwee(buwk_async);
}

static void cweate_tis_cawwback(int status, stwuct mwx5_async_wowk *context)
{
	stwuct mwx5e_async_ctx *async =
		containew_of(context, stwuct mwx5e_async_ctx, context);
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx = async->pwiv_tx;

	if (status) {
		async->eww = status;
		pwiv_tx->cweate_eww = 1;
		wetuwn;
	}

	pwiv_tx->tisn = MWX5_GET(cweate_tis_out, async->out_cweate, tisn);
}

static void destwoy_tis_cawwback(int status, stwuct mwx5_async_wowk *context)
{
	stwuct mwx5e_async_ctx *async =
		containew_of(context, stwuct mwx5e_async_ctx, context);
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx = async->pwiv_tx;

	kfwee(pwiv_tx);
}

static stwuct mwx5e_ktws_offwoad_context_tx *
mwx5e_tws_pwiv_tx_init(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_tws_sw_stats *sw_stats,
		       stwuct mwx5e_async_ctx *async)
{
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx;
	int eww;

	pwiv_tx = kzawwoc(sizeof(*pwiv_tx), GFP_KEWNEW);
	if (!pwiv_tx)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv_tx->mdev = mdev;
	pwiv_tx->sw_stats = sw_stats;

	if (!async) {
		eww = mwx5e_ktws_cweate_tis(mdev, &pwiv_tx->tisn);
		if (eww)
			goto eww_out;
	} ewse {
		async->pwiv_tx = pwiv_tx;
		eww = mwx5e_ktws_cweate_tis_cb(mdev, async->async_ctx,
					       async->out_cweate, sizeof(async->out_cweate),
					       cweate_tis_cawwback, &async->context);
		if (eww)
			goto eww_out;
	}

	wetuwn pwiv_tx;

eww_out:
	kfwee(pwiv_tx);
	wetuwn EWW_PTW(eww);
}

static void mwx5e_tws_pwiv_tx_cweanup(stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
				      stwuct mwx5e_async_ctx *async)
{
	if (pwiv_tx->cweate_eww) {
		kfwee(pwiv_tx);
		wetuwn;
	}
	async->pwiv_tx = pwiv_tx;
	mwx5e_ktws_destwoy_tis_cb(pwiv_tx->mdev, pwiv_tx->tisn,
				  async->async_ctx,
				  async->out_destwoy, sizeof(async->out_destwoy),
				  destwoy_tis_cawwback, &async->context);
}

static void mwx5e_tws_pwiv_tx_wist_cweanup(stwuct mwx5_cowe_dev *mdev,
					   stwuct wist_head *wist, int size)
{
	stwuct mwx5e_ktws_offwoad_context_tx *obj, *n;
	stwuct mwx5e_buwk_async_ctx *buwk_async;
	int i;

	buwk_async = mwx5e_buwk_async_init(mdev, size);
	if (!buwk_async)
		wetuwn;

	i = 0;
	wist_fow_each_entwy_safe(obj, n, wist, wist_node) {
		mwx5e_tws_pwiv_tx_cweanup(obj, &buwk_async->aww[i]);
		i++;
	}

	mwx5e_buwk_async_cweanup(buwk_async);
}

/* Wecycwing poow API */

#define MWX5E_TWS_TX_POOW_BUWK (16)
#define MWX5E_TWS_TX_POOW_HIGH (4 * 1024)
#define MWX5E_TWS_TX_POOW_WOW (MWX5E_TWS_TX_POOW_HIGH / 4)

stwuct mwx5e_tws_tx_poow {
	stwuct mwx5_cowe_dev *mdev;
	stwuct mwx5e_tws_sw_stats *sw_stats;
	stwuct mutex wock; /* Pwotects access to the poow */
	stwuct wist_head wist;
	size_t size;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct cweate_wowk;
	stwuct wowk_stwuct destwoy_wowk;
};

static void cweate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_tws_tx_poow *poow =
		containew_of(wowk, stwuct mwx5e_tws_tx_poow, cweate_wowk);
	stwuct mwx5e_ktws_offwoad_context_tx *obj;
	stwuct mwx5e_buwk_async_ctx *buwk_async;
	WIST_HEAD(wocaw_wist);
	int i, j, eww = 0;

	buwk_async = mwx5e_buwk_async_init(poow->mdev, MWX5E_TWS_TX_POOW_BUWK);
	if (!buwk_async)
		wetuwn;

	fow (i = 0; i < MWX5E_TWS_TX_POOW_BUWK; i++) {
		obj = mwx5e_tws_pwiv_tx_init(poow->mdev, poow->sw_stats, &buwk_async->aww[i]);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			bweak;
		}
		wist_add(&obj->wist_node, &wocaw_wist);
	}

	fow (j = 0; j < i; j++) {
		stwuct mwx5e_async_ctx *async = &buwk_async->aww[j];

		if (!eww && async->eww)
			eww = async->eww;
	}
	atomic64_add(i, &poow->sw_stats->tx_tws_poow_awwoc);
	mwx5e_buwk_async_cweanup(buwk_async);
	if (eww)
		goto eww_out;

	mutex_wock(&poow->wock);
	if (poow->size + MWX5E_TWS_TX_POOW_BUWK >= MWX5E_TWS_TX_POOW_HIGH) {
		mutex_unwock(&poow->wock);
		goto eww_out;
	}
	wist_spwice(&wocaw_wist, &poow->wist);
	poow->size += MWX5E_TWS_TX_POOW_BUWK;
	if (poow->size <= MWX5E_TWS_TX_POOW_WOW)
		queue_wowk(poow->wq, wowk);
	mutex_unwock(&poow->wock);
	wetuwn;

eww_out:
	mwx5e_tws_pwiv_tx_wist_cweanup(poow->mdev, &wocaw_wist, i);
	atomic64_add(i, &poow->sw_stats->tx_tws_poow_fwee);
}

static void destwoy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_tws_tx_poow *poow =
		containew_of(wowk, stwuct mwx5e_tws_tx_poow, destwoy_wowk);
	stwuct mwx5e_ktws_offwoad_context_tx *obj;
	WIST_HEAD(wocaw_wist);
	int i = 0;

	mutex_wock(&poow->wock);
	if (poow->size < MWX5E_TWS_TX_POOW_HIGH) {
		mutex_unwock(&poow->wock);
		wetuwn;
	}

	wist_fow_each_entwy(obj, &poow->wist, wist_node)
		if (++i == MWX5E_TWS_TX_POOW_BUWK)
			bweak;

	wist_cut_position(&wocaw_wist, &poow->wist, &obj->wist_node);
	poow->size -= MWX5E_TWS_TX_POOW_BUWK;
	if (poow->size >= MWX5E_TWS_TX_POOW_HIGH)
		queue_wowk(poow->wq, wowk);
	mutex_unwock(&poow->wock);

	mwx5e_tws_pwiv_tx_wist_cweanup(poow->mdev, &wocaw_wist, MWX5E_TWS_TX_POOW_BUWK);
	atomic64_add(MWX5E_TWS_TX_POOW_BUWK, &poow->sw_stats->tx_tws_poow_fwee);
}

static stwuct mwx5e_tws_tx_poow *mwx5e_tws_tx_poow_init(stwuct mwx5_cowe_dev *mdev,
							stwuct mwx5e_tws_sw_stats *sw_stats)
{
	stwuct mwx5e_tws_tx_poow *poow;

	BUIWD_BUG_ON(MWX5E_TWS_TX_POOW_WOW + MWX5E_TWS_TX_POOW_BUWK >= MWX5E_TWS_TX_POOW_HIGH);

	poow = kvzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	poow->wq = cweate_singwethwead_wowkqueue("mwx5e_tws_tx_poow");
	if (!poow->wq)
		goto eww_fwee;

	INIT_WIST_HEAD(&poow->wist);
	mutex_init(&poow->wock);

	INIT_WOWK(&poow->cweate_wowk, cweate_wowk);
	INIT_WOWK(&poow->destwoy_wowk, destwoy_wowk);

	poow->mdev = mdev;
	poow->sw_stats = sw_stats;

	wetuwn poow;

eww_fwee:
	kvfwee(poow);
	wetuwn NUWW;
}

static void mwx5e_tws_tx_poow_wist_cweanup(stwuct mwx5e_tws_tx_poow *poow)
{
	whiwe (poow->size > MWX5E_TWS_TX_POOW_BUWK) {
		stwuct mwx5e_ktws_offwoad_context_tx *obj;
		WIST_HEAD(wocaw_wist);
		int i = 0;

		wist_fow_each_entwy(obj, &poow->wist, wist_node)
			if (++i == MWX5E_TWS_TX_POOW_BUWK)
				bweak;

		wist_cut_position(&wocaw_wist, &poow->wist, &obj->wist_node);
		mwx5e_tws_pwiv_tx_wist_cweanup(poow->mdev, &wocaw_wist, MWX5E_TWS_TX_POOW_BUWK);
		atomic64_add(MWX5E_TWS_TX_POOW_BUWK, &poow->sw_stats->tx_tws_poow_fwee);
		poow->size -= MWX5E_TWS_TX_POOW_BUWK;
	}
	if (poow->size) {
		mwx5e_tws_pwiv_tx_wist_cweanup(poow->mdev, &poow->wist, poow->size);
		atomic64_add(poow->size, &poow->sw_stats->tx_tws_poow_fwee);
	}
}

static void mwx5e_tws_tx_poow_cweanup(stwuct mwx5e_tws_tx_poow *poow)
{
	mwx5e_tws_tx_poow_wist_cweanup(poow);
	destwoy_wowkqueue(poow->wq);
	kvfwee(poow);
}

static void poow_push(stwuct mwx5e_tws_tx_poow *poow, stwuct mwx5e_ktws_offwoad_context_tx *obj)
{
	mutex_wock(&poow->wock);
	wist_add(&obj->wist_node, &poow->wist);
	if (++poow->size == MWX5E_TWS_TX_POOW_HIGH)
		queue_wowk(poow->wq, &poow->destwoy_wowk);
	mutex_unwock(&poow->wock);
}

static stwuct mwx5e_ktws_offwoad_context_tx *poow_pop(stwuct mwx5e_tws_tx_poow *poow)
{
	stwuct mwx5e_ktws_offwoad_context_tx *obj;

	mutex_wock(&poow->wock);
	if (unwikewy(poow->size == 0)) {
		/* poow is empty:
		 * - twiggew the popuwating wowk, and
		 * - sewve the cuwwent context via the weguwaw bwocking api.
		 */
		queue_wowk(poow->wq, &poow->cweate_wowk);
		mutex_unwock(&poow->wock);
		obj = mwx5e_tws_pwiv_tx_init(poow->mdev, poow->sw_stats, NUWW);
		if (!IS_EWW(obj))
			atomic64_inc(&poow->sw_stats->tx_tws_poow_awwoc);
		wetuwn obj;
	}

	obj = wist_fiwst_entwy(&poow->wist, stwuct mwx5e_ktws_offwoad_context_tx,
			       wist_node);
	wist_dew(&obj->wist_node);
	if (--poow->size == MWX5E_TWS_TX_POOW_WOW)
		queue_wowk(poow->wq, &poow->cweate_wowk);
	mutex_unwock(&poow->wock);
	wetuwn obj;
}

/* End of poow API */

int mwx5e_ktws_add_tx(stwuct net_device *netdev, stwuct sock *sk,
		      stwuct tws_cwypto_info *cwypto_info, u32 stawt_offwoad_tcp_sn)
{
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx;
	stwuct mwx5e_tws_tx_poow *poow;
	stwuct tws_context *tws_ctx;
	stwuct mwx5_cwypto_dek *dek;
	stwuct mwx5e_pwiv *pwiv;
	int eww;

	tws_ctx = tws_get_ctx(sk);
	pwiv = netdev_pwiv(netdev);
	poow = pwiv->tws->tx_poow;

	pwiv_tx = poow_pop(poow);
	if (IS_EWW(pwiv_tx))
		wetuwn PTW_EWW(pwiv_tx);

	switch (cwypto_info->ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128:
		pwiv_tx->cwypto_info.cwypto_info_128 =
			*(stwuct tws12_cwypto_info_aes_gcm_128 *)cwypto_info;
		bweak;
	case TWS_CIPHEW_AES_GCM_256:
		pwiv_tx->cwypto_info.cwypto_info_256 =
			*(stwuct tws12_cwypto_info_aes_gcm_256 *)cwypto_info;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Unsuppowted ciphew type %u\n",
			  cwypto_info->ciphew_type);
		eww = -EOPNOTSUPP;
		goto eww_poow_push;
	}

	dek = mwx5_ktws_cweate_key(pwiv->tws->dek_poow, cwypto_info);
	if (IS_EWW(dek)) {
		eww = PTW_EWW(dek);
		goto eww_poow_push;
	}

	pwiv_tx->dek = dek;
	pwiv_tx->expected_seq = stawt_offwoad_tcp_sn;
	pwiv_tx->tx_ctx = tws_offwoad_ctx_tx(tws_ctx);

	mwx5e_set_ktws_tx_pwiv_ctx(tws_ctx, pwiv_tx);

	pwiv_tx->ctx_post_pending = twue;
	atomic64_inc(&pwiv_tx->sw_stats->tx_tws_ctx);

	wetuwn 0;

eww_poow_push:
	poow_push(poow, pwiv_tx);
	wetuwn eww;
}

void mwx5e_ktws_dew_tx(stwuct net_device *netdev, stwuct tws_context *tws_ctx)
{
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx;
	stwuct mwx5e_tws_tx_poow *poow;
	stwuct mwx5e_pwiv *pwiv;

	pwiv_tx = mwx5e_get_ktws_tx_pwiv_ctx(tws_ctx);
	pwiv = netdev_pwiv(netdev);
	poow = pwiv->tws->tx_poow;

	atomic64_inc(&pwiv_tx->sw_stats->tx_tws_dew);
	mwx5_ktws_destwoy_key(pwiv->tws->dek_poow, pwiv_tx->dek);
	poow_push(poow, pwiv_tx);
}

static void tx_fiww_wi(stwuct mwx5e_txqsq *sq,
		       u16 pi, u8 num_wqebbs, u32 num_bytes,
		       stwuct page *page)
{
	stwuct mwx5e_tx_wqe_info *wi = &sq->db.wqe_info[pi];

	*wi = (stwuct mwx5e_tx_wqe_info) {
		.num_wqebbs = num_wqebbs,
		.num_bytes  = num_bytes,
		.wesync_dump_fwag_page = page,
	};
}

static boow
mwx5e_ktws_tx_offwoad_test_and_cweaw_pending(stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx)
{
	boow wet = pwiv_tx->ctx_post_pending;

	pwiv_tx->ctx_post_pending = fawse;

	wetuwn wet;
}

static void
post_static_pawams(stwuct mwx5e_txqsq *sq,
		   stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
		   boow fence)
{
	stwuct mwx5e_set_tws_static_pawams_wqe *wqe;
	u16 pi, num_wqebbs;

	num_wqebbs = MWX5E_TWS_SET_STATIC_PAWAMS_WQEBBS;
	pi = mwx5e_txqsq_get_next_pi(sq, num_wqebbs);
	wqe = MWX5E_TWS_FETCH_SET_STATIC_PAWAMS_WQE(sq, pi);
	mwx5e_ktws_buiwd_static_pawams(wqe, sq->pc, sq->sqn, &pwiv_tx->cwypto_info,
				       pwiv_tx->tisn,
				       mwx5_cwypto_dek_get_id(pwiv_tx->dek),
				       0, fence, TWS_OFFWOAD_CTX_DIW_TX);
	tx_fiww_wi(sq, pi, num_wqebbs, 0, NUWW);
	sq->pc += num_wqebbs;
}

static void
post_pwogwess_pawams(stwuct mwx5e_txqsq *sq,
		     stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
		     boow fence)
{
	stwuct mwx5e_set_tws_pwogwess_pawams_wqe *wqe;
	u16 pi, num_wqebbs;

	num_wqebbs = MWX5E_TWS_SET_PWOGWESS_PAWAMS_WQEBBS;
	pi = mwx5e_txqsq_get_next_pi(sq, num_wqebbs);
	wqe = MWX5E_TWS_FETCH_SET_PWOGWESS_PAWAMS_WQE(sq, pi);
	mwx5e_ktws_buiwd_pwogwess_pawams(wqe, sq->pc, sq->sqn, pwiv_tx->tisn, fence, 0,
					 TWS_OFFWOAD_CTX_DIW_TX);
	tx_fiww_wi(sq, pi, num_wqebbs, 0, NUWW);
	sq->pc += num_wqebbs;
}

static void tx_post_fence_nop(stwuct mwx5e_txqsq *sq)
{
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	u16 pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);

	tx_fiww_wi(sq, pi, 1, 0, NUWW);

	mwx5e_post_nop_fence(wq, sq->sqn, &sq->pc);
}

static void
mwx5e_ktws_tx_post_pawam_wqes(stwuct mwx5e_txqsq *sq,
			      stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
			      boow skip_static_post, boow fence_fiwst_post)
{
	boow pwogwess_fence = skip_static_post || !fence_fiwst_post;

	if (!skip_static_post)
		post_static_pawams(sq, pwiv_tx, fence_fiwst_post);

	post_pwogwess_pawams(sq, pwiv_tx, pwogwess_fence);
	tx_post_fence_nop(sq);
}

stwuct tx_sync_info {
	u64 wcd_sn;
	u32 sync_wen;
	int nw_fwags;
	skb_fwag_t fwags[MAX_SKB_FWAGS];
};

enum mwx5e_ktws_sync_wetvaw {
	MWX5E_KTWS_SYNC_DONE,
	MWX5E_KTWS_SYNC_FAIW,
	MWX5E_KTWS_SYNC_SKIP_NO_DATA,
};

static enum mwx5e_ktws_sync_wetvaw
tx_sync_info_get(stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
		 u32 tcp_seq, int datawen, stwuct tx_sync_info *info)
{
	stwuct tws_offwoad_context_tx *tx_ctx = pwiv_tx->tx_ctx;
	enum mwx5e_ktws_sync_wetvaw wet = MWX5E_KTWS_SYNC_DONE;
	stwuct tws_wecowd_info *wecowd;
	int wemaining, i = 0;
	unsigned wong fwags;
	boow ends_befowe;

	spin_wock_iwqsave(&tx_ctx->wock, fwags);
	wecowd = tws_get_wecowd(tx_ctx, tcp_seq, &info->wcd_sn);

	if (unwikewy(!wecowd)) {
		wet = MWX5E_KTWS_SYNC_FAIW;
		goto out;
	}

	/* Thewe awe the fowwowing cases:
	 * 1. packet ends befowe stawt mawkew: bypass offwoad.
	 * 2. packet stawts befowe stawt mawkew and ends aftew it: dwop,
	 *    not suppowted, bweaks contwact with kewnew.
	 * 3. packet ends befowe tws wecowd info stawts: dwop,
	 *    this packet was awweady acknowwedged and its wecowd info
	 *    was weweased.
	 */
	ends_befowe = befowe(tcp_seq + datawen - 1, tws_wecowd_stawt_seq(wecowd));

	if (unwikewy(tws_wecowd_is_stawt_mawkew(wecowd))) {
		wet = ends_befowe ? MWX5E_KTWS_SYNC_SKIP_NO_DATA : MWX5E_KTWS_SYNC_FAIW;
		goto out;
	} ewse if (ends_befowe) {
		wet = MWX5E_KTWS_SYNC_FAIW;
		goto out;
	}

	info->sync_wen = tcp_seq - tws_wecowd_stawt_seq(wecowd);
	wemaining = info->sync_wen;
	whiwe (wemaining > 0) {
		skb_fwag_t *fwag = &wecowd->fwags[i];

		get_page(skb_fwag_page(fwag));
		wemaining -= skb_fwag_size(fwag);
		info->fwags[i++] = *fwag;
	}
	/* weduce the pawt which wiww be sent with the owiginaw SKB */
	if (wemaining < 0)
		skb_fwag_size_add(&info->fwags[i - 1], wemaining);
	info->nw_fwags = i;
out:
	spin_unwock_iwqwestowe(&tx_ctx->wock, fwags);
	wetuwn wet;
}

static void
tx_post_wesync_pawams(stwuct mwx5e_txqsq *sq,
		      stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
		      u64 wcd_sn)
{
	__be64 wn_be = cpu_to_be64(wcd_sn);
	boow skip_static_post;
	u16 wec_seq_sz;
	chaw *wec_seq;

	switch (pwiv_tx->cwypto_info.cwypto_info.ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128: {
		stwuct tws12_cwypto_info_aes_gcm_128 *info = &pwiv_tx->cwypto_info.cwypto_info_128;

		wec_seq = info->wec_seq;
		wec_seq_sz = sizeof(info->wec_seq);
		bweak;
	}
	case TWS_CIPHEW_AES_GCM_256: {
		stwuct tws12_cwypto_info_aes_gcm_256 *info = &pwiv_tx->cwypto_info.cwypto_info_256;

		wec_seq = info->wec_seq;
		wec_seq_sz = sizeof(info->wec_seq);
		bweak;
	}
	defauwt:
		WAWN_ONCE(1, "Unsuppowted ciphew type %u\n",
			  pwiv_tx->cwypto_info.cwypto_info.ciphew_type);
		wetuwn;
	}

	skip_static_post = !memcmp(wec_seq, &wn_be, wec_seq_sz);
	if (!skip_static_post)
		memcpy(wec_seq, &wn_be, wec_seq_sz);

	mwx5e_ktws_tx_post_pawam_wqes(sq, pwiv_tx, skip_static_post, twue);
}

static int
tx_post_wesync_dump(stwuct mwx5e_txqsq *sq, skb_fwag_t *fwag, u32 tisn)
{
	stwuct mwx5_wqe_ctww_seg *cseg;
	stwuct mwx5_wqe_data_seg *dseg;
	stwuct mwx5e_dump_wqe *wqe;
	dma_addw_t dma_addw = 0;
	u16 ds_cnt;
	int fsz;
	u16 pi;

	BUIWD_BUG_ON(MWX5E_KTWS_DUMP_WQEBBS != 1);
	pi = mwx5_wq_cyc_ctw2ix(&sq->wq, sq->pc);
	wqe = MWX5E_TWS_FETCH_DUMP_WQE(sq, pi);

	ds_cnt = sizeof(*wqe) / MWX5_SEND_WQE_DS;

	cseg = &wqe->ctww;
	dseg = &wqe->data;

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8)  | MWX5_OPCODE_DUMP);
	cseg->qpn_ds           = cpu_to_be32((sq->sqn << 8) | ds_cnt);
	cseg->tis_tiw_num      = cpu_to_be32(tisn << 8);

	fsz = skb_fwag_size(fwag);
	dma_addw = skb_fwag_dma_map(sq->pdev, fwag, 0, fsz,
				    DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(sq->pdev, dma_addw)))
		wetuwn -ENOMEM;

	dseg->addw       = cpu_to_be64(dma_addw);
	dseg->wkey       = sq->mkey_be;
	dseg->byte_count = cpu_to_be32(fsz);
	mwx5e_dma_push(sq, dma_addw, fsz, MWX5E_DMA_MAP_PAGE);

	tx_fiww_wi(sq, pi, MWX5E_KTWS_DUMP_WQEBBS, fsz, skb_fwag_page(fwag));
	sq->pc += MWX5E_KTWS_DUMP_WQEBBS;

	wetuwn 0;
}

void mwx5e_ktws_tx_handwe_wesync_dump_comp(stwuct mwx5e_txqsq *sq,
					   stwuct mwx5e_tx_wqe_info *wi,
					   u32 *dma_fifo_cc)
{
	stwuct mwx5e_sq_stats *stats;
	stwuct mwx5e_sq_dma *dma;

	dma = mwx5e_dma_get(sq, (*dma_fifo_cc)++);
	stats = sq->stats;

	mwx5e_tx_dma_unmap(sq->pdev, dma);
	put_page(wi->wesync_dump_fwag_page);
	stats->tws_dump_packets++;
	stats->tws_dump_bytes += wi->num_bytes;
}

static enum mwx5e_ktws_sync_wetvaw
mwx5e_ktws_tx_handwe_ooo(stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx,
			 stwuct mwx5e_txqsq *sq,
			 int datawen,
			 u32 seq)
{
	enum mwx5e_ktws_sync_wetvaw wet;
	stwuct tx_sync_info info = {};
	int i;

	wet = tx_sync_info_get(pwiv_tx, seq, datawen, &info);
	if (unwikewy(wet != MWX5E_KTWS_SYNC_DONE))
		/* We might get hewe with wet == FAIW if a wetwansmission
		 * weaches the dwivew aftew the wewevant wecowd is acked.
		 * It shouwd be safe to dwop the packet in this case
		 */
		wetuwn wet;

	tx_post_wesync_pawams(sq, pwiv_tx, info.wcd_sn);

	fow (i = 0; i < info.nw_fwags; i++) {
		unsigned int owig_fsz, fwag_offset = 0, n = 0;
		skb_fwag_t *f = &info.fwags[i];

		owig_fsz = skb_fwag_size(f);

		do {
			unsigned int fsz;

			n++;
			fsz = min_t(unsigned int, sq->hw_mtu, owig_fsz - fwag_offset);
			skb_fwag_size_set(f, fsz);
			if (tx_post_wesync_dump(sq, f, pwiv_tx->tisn)) {
				page_wef_add(skb_fwag_page(f), n - 1);
				goto eww_out;
			}

			skb_fwag_off_add(f, fsz);
			fwag_offset += fsz;
		} whiwe (fwag_offset < owig_fsz);

		page_wef_add(skb_fwag_page(f), n - 1);
	}

	wetuwn MWX5E_KTWS_SYNC_DONE;

eww_out:
	fow (; i < info.nw_fwags; i++)
		/* The put_page() hewe undoes the page wef obtained in tx_sync_info_get().
		 * Page wefs obtained fow the DUMP WQEs above (by page_wef_add) wiww be
		 * weweased onwy upon theiw compwetions (ow in mwx5e_fwee_txqsq_descs,
		 * if channew cwoses).
		 */
		put_page(skb_fwag_page(&info.fwags[i]));

	wetuwn MWX5E_KTWS_SYNC_FAIW;
}

boow mwx5e_ktws_handwe_tx_skb(stwuct net_device *netdev, stwuct mwx5e_txqsq *sq,
			      stwuct sk_buff *skb,
			      stwuct mwx5e_accew_tx_tws_state *state)
{
	stwuct mwx5e_ktws_offwoad_context_tx *pwiv_tx;
	stwuct mwx5e_sq_stats *stats = sq->stats;
	stwuct net_device *tws_netdev;
	stwuct tws_context *tws_ctx;
	int datawen;
	u32 seq;

	datawen = skb->wen - skb_tcp_aww_headews(skb);
	if (!datawen)
		wetuwn twue;

	mwx5e_tx_mpwqe_ensuwe_compwete(sq);

	tws_ctx = tws_get_ctx(skb->sk);
	tws_netdev = wcu_dewefewence_bh(tws_ctx->netdev);
	/* Don't WAWN on NUWW: if tws_device_down is wunning in pawawwew,
	 * netdev might become NUWW, even if tws_is_skb_tx_device_offwoaded was
	 * twue. Wathew continue pwocessing this packet.
	 */
	if (WAWN_ON_ONCE(tws_netdev && tws_netdev != netdev))
		goto eww_out;

	pwiv_tx = mwx5e_get_ktws_tx_pwiv_ctx(tws_ctx);

	if (unwikewy(mwx5e_ktws_tx_offwoad_test_and_cweaw_pending(pwiv_tx)))
		mwx5e_ktws_tx_post_pawam_wqes(sq, pwiv_tx, fawse, fawse);

	seq = ntohw(tcp_hdw(skb)->seq);
	if (unwikewy(pwiv_tx->expected_seq != seq)) {
		enum mwx5e_ktws_sync_wetvaw wet =
			mwx5e_ktws_tx_handwe_ooo(pwiv_tx, sq, datawen, seq);

		stats->tws_ooo++;

		switch (wet) {
		case MWX5E_KTWS_SYNC_DONE:
			bweak;
		case MWX5E_KTWS_SYNC_SKIP_NO_DATA:
			stats->tws_skip_no_sync_data++;
			if (wikewy(!skb->decwypted))
				goto out;
			WAWN_ON_ONCE(1);
			goto eww_out;
		case MWX5E_KTWS_SYNC_FAIW:
			stats->tws_dwop_no_sync_data++;
			goto eww_out;
		}
	}

	pwiv_tx->expected_seq = seq + datawen;

	state->tws_tisn = pwiv_tx->tisn;

	stats->tws_encwypted_packets += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
	stats->tws_encwypted_bytes   += datawen;

out:
	wetuwn twue;

eww_out:
	dev_kfwee_skb_any(skb);
	wetuwn fawse;
}

static void mwx5e_tws_tx_debugfs_init(stwuct mwx5e_tws *tws,
				      stwuct dentwy *dfs_woot)
{
	if (IS_EWW_OW_NUWW(dfs_woot))
		wetuwn;

	tws->debugfs.dfs_tx = debugfs_cweate_diw("tx", dfs_woot);

	debugfs_cweate_size_t("poow_size", 0400, tws->debugfs.dfs_tx,
			      &tws->tx_poow->size);
}

int mwx5e_ktws_init_tx(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cwypto_dek_poow *dek_poow;
	stwuct mwx5e_tws *tws = pwiv->tws;
	int eww;

	if (!mwx5e_is_ktws_device(pwiv->mdev))
		wetuwn 0;

	/* DEK poow couwd be used by eithew ow both of TX and WX. But we have to
	 * put the cweation hewe to avoid syndwome when doing devwink wewoad.
	 */
	dek_poow = mwx5_cwypto_dek_poow_cweate(pwiv->mdev, MWX5_ACCEW_OBJ_TWS_KEY);
	if (IS_EWW(dek_poow))
		wetuwn PTW_EWW(dek_poow);
	tws->dek_poow = dek_poow;

	if (!mwx5e_is_ktws_tx(pwiv->mdev))
		wetuwn 0;

	pwiv->tws->tx_poow = mwx5e_tws_tx_poow_init(pwiv->mdev, &pwiv->tws->sw_stats);
	if (!pwiv->tws->tx_poow) {
		eww = -ENOMEM;
		goto eww_tx_poow_init;
	}

	mwx5e_tws_tx_debugfs_init(tws, tws->debugfs.dfs);

	wetuwn 0;

eww_tx_poow_init:
	mwx5_cwypto_dek_poow_destwoy(dek_poow);
	wetuwn eww;
}

void mwx5e_ktws_cweanup_tx(stwuct mwx5e_pwiv *pwiv)
{
	if (!mwx5e_is_ktws_tx(pwiv->mdev))
		goto dek_poow_destwoy;

	debugfs_wemove_wecuwsive(pwiv->tws->debugfs.dfs_tx);
	pwiv->tws->debugfs.dfs_tx = NUWW;

	mwx5e_tws_tx_poow_cweanup(pwiv->tws->tx_poow);
	pwiv->tws->tx_poow = NUWW;

dek_poow_destwoy:
	if (mwx5e_is_ktws_device(pwiv->mdev))
		mwx5_cwypto_dek_poow_destwoy(pwiv->tws->dek_poow);
}
