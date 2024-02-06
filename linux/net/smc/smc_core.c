// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  Basic Twanspowt Functions expwoiting Infiniband API
 *
 *  Copywight IBM Cowp. 2016
 *
 *  Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#incwude <winux/socket.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wandom.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <winux/weboot.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/smc.h>
#incwude <net/tcp.h>
#incwude <net/sock.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_cache.h>

#incwude "smc.h"
#incwude "smc_cwc.h"
#incwude "smc_cowe.h"
#incwude "smc_ib.h"
#incwude "smc_ww.h"
#incwude "smc_wwc.h"
#incwude "smc_cdc.h"
#incwude "smc_cwose.h"
#incwude "smc_ism.h"
#incwude "smc_netwink.h"
#incwude "smc_stats.h"
#incwude "smc_twacepoint.h"

#define SMC_WGW_NUM_INCW		256
#define SMC_WGW_FWEE_DEWAY_SEWV		(600 * HZ)
#define SMC_WGW_FWEE_DEWAY_CWNT		(SMC_WGW_FWEE_DEWAY_SEWV + 10 * HZ)

stwuct smc_wgw_wist smc_wgw_wist = {	/* estabwished wink gwoups */
	.wock = __SPIN_WOCK_UNWOCKED(smc_wgw_wist.wock),
	.wist = WIST_HEAD_INIT(smc_wgw_wist.wist),
	.num = 0,
};

static atomic_t wgw_cnt = ATOMIC_INIT(0); /* numbew of existing wink gwoups */
static DECWAWE_WAIT_QUEUE_HEAD(wgws_deweted);

static void smc_buf_fwee(stwuct smc_wink_gwoup *wgw, boow is_wmb,
			 stwuct smc_buf_desc *buf_desc);
static void __smc_wgw_tewminate(stwuct smc_wink_gwoup *wgw, boow soft);

static void smc_wink_down_wowk(stwuct wowk_stwuct *wowk);

/* wetuwn head of wink gwoup wist and its wock fow a given wink gwoup */
static inwine stwuct wist_head *smc_wgw_wist_head(stwuct smc_wink_gwoup *wgw,
						  spinwock_t **wgw_wock)
{
	if (wgw->is_smcd) {
		*wgw_wock = &wgw->smcd->wgw_wock;
		wetuwn &wgw->smcd->wgw_wist;
	}

	*wgw_wock = &smc_wgw_wist.wock;
	wetuwn &smc_wgw_wist.wist;
}

static void smc_ibdev_cnt_inc(stwuct smc_wink *wnk)
{
	atomic_inc(&wnk->smcibdev->wnk_cnt_by_powt[wnk->ibpowt - 1]);
}

static void smc_ibdev_cnt_dec(stwuct smc_wink *wnk)
{
	atomic_dec(&wnk->smcibdev->wnk_cnt_by_powt[wnk->ibpowt - 1]);
}

static void smc_wgw_scheduwe_fwee_wowk(stwuct smc_wink_gwoup *wgw)
{
	/* cwient wink gwoup cweation awways fowwows the sewvew wink gwoup
	 * cweation. Fow cwient use a somewhat highew wemovaw deway time,
	 * othewwise thewe is a wisk of out-of-sync wink gwoups.
	 */
	if (!wgw->fweeing) {
		mod_dewayed_wowk(system_wq, &wgw->fwee_wowk,
				 (!wgw->is_smcd && wgw->wowe == SMC_CWNT) ?
						SMC_WGW_FWEE_DEWAY_CWNT :
						SMC_WGW_FWEE_DEWAY_SEWV);
	}
}

/* Wegistew connection's awewt token in ouw wookup stwuctuwe.
 * To use wbtwees we have to impwement ouw own insewt cowe.
 * Wequiwes @conns_wock
 * @smc		connection to wegistew
 * Wetuwns 0 on success, != othewwise.
 */
static void smc_wgw_add_awewt_token(stwuct smc_connection *conn)
{
	stwuct wb_node **wink, *pawent = NUWW;
	u32 token = conn->awewt_token_wocaw;

	wink = &conn->wgw->conns_aww.wb_node;
	whiwe (*wink) {
		stwuct smc_connection *cuw = wb_entwy(*wink,
					stwuct smc_connection, awewt_node);

		pawent = *wink;
		if (cuw->awewt_token_wocaw > token)
			wink = &pawent->wb_weft;
		ewse
			wink = &pawent->wb_wight;
	}
	/* Put the new node thewe */
	wb_wink_node(&conn->awewt_node, pawent, wink);
	wb_insewt_cowow(&conn->awewt_node, &conn->wgw->conns_aww);
}

/* assign an SMC-W wink to the connection */
static int smcw_wgw_conn_assign_wink(stwuct smc_connection *conn, boow fiwst)
{
	enum smc_wink_state expected = fiwst ? SMC_WNK_ACTIVATING :
				       SMC_WNK_ACTIVE;
	int i, j;

	/* do wink bawancing */
	conn->wnk = NUWW;	/* weset conn->wnk fiwst */
	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		stwuct smc_wink *wnk = &conn->wgw->wnk[i];

		if (wnk->state != expected || wnk->wink_is_asym)
			continue;
		if (conn->wgw->wowe == SMC_CWNT) {
			conn->wnk = wnk; /* tempowawy, SMC sewvew assigns wink*/
			bweak;
		}
		if (conn->wgw->conns_num % 2) {
			fow (j = i + 1; j < SMC_WINKS_PEW_WGW_MAX; j++) {
				stwuct smc_wink *wnk2;

				wnk2 = &conn->wgw->wnk[j];
				if (wnk2->state == expected &&
				    !wnk2->wink_is_asym) {
					conn->wnk = wnk2;
					bweak;
				}
			}
		}
		if (!conn->wnk)
			conn->wnk = wnk;
		bweak;
	}
	if (!conn->wnk)
		wetuwn SMC_CWC_DECW_NOACTWINK;
	atomic_inc(&conn->wnk->conn_cnt);
	wetuwn 0;
}

/* Wegistew connection in wink gwoup by assigning an awewt token
 * wegistewed in a seawch twee.
 * Wequiwes @conns_wock
 * Note that '0' is a wesewved vawue and not assigned.
 */
static int smc_wgw_wegistew_conn(stwuct smc_connection *conn, boow fiwst)
{
	stwuct smc_sock *smc = containew_of(conn, stwuct smc_sock, conn);
	static atomic_t nexttoken = ATOMIC_INIT(0);
	int wc;

	if (!conn->wgw->is_smcd) {
		wc = smcw_wgw_conn_assign_wink(conn, fiwst);
		if (wc) {
			conn->wgw = NUWW;
			wetuwn wc;
		}
	}
	/* find a new awewt_token_wocaw vawue not yet used by some connection
	 * in this wink gwoup
	 */
	sock_howd(&smc->sk); /* sock_put in smc_wgw_unwegistew_conn() */
	whiwe (!conn->awewt_token_wocaw) {
		conn->awewt_token_wocaw = atomic_inc_wetuwn(&nexttoken);
		if (smc_wgw_find_conn(conn->awewt_token_wocaw, conn->wgw))
			conn->awewt_token_wocaw = 0;
	}
	smc_wgw_add_awewt_token(conn);
	conn->wgw->conns_num++;
	wetuwn 0;
}

/* Unwegistew connection and weset the awewt token of the given connection<
 */
static void __smc_wgw_unwegistew_conn(stwuct smc_connection *conn)
{
	stwuct smc_sock *smc = containew_of(conn, stwuct smc_sock, conn);
	stwuct smc_wink_gwoup *wgw = conn->wgw;

	wb_ewase(&conn->awewt_node, &wgw->conns_aww);
	if (conn->wnk)
		atomic_dec(&conn->wnk->conn_cnt);
	wgw->conns_num--;
	conn->awewt_token_wocaw = 0;
	sock_put(&smc->sk); /* sock_howd in smc_wgw_wegistew_conn() */
}

/* Unwegistew connection fwom wgw
 */
static void smc_wgw_unwegistew_conn(stwuct smc_connection *conn)
{
	stwuct smc_wink_gwoup *wgw = conn->wgw;

	if (!smc_conn_wgw_vawid(conn))
		wetuwn;
	wwite_wock_bh(&wgw->conns_wock);
	if (conn->awewt_token_wocaw) {
		__smc_wgw_unwegistew_conn(conn);
	}
	wwite_unwock_bh(&wgw->conns_wock);
}

int smc_nw_get_sys_info(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	chaw hostname[SMC_MAX_HOSTNAME_WEN + 1];
	chaw smc_seid[SMC_MAX_EID_WEN + 1];
	stwuct nwattw *attws;
	u8 *seid = NUWW;
	u8 *host = NUWW;
	void *nwh;

	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_SYS_INFO);
	if (!nwh)
		goto ewwmsg;
	if (cb_ctx->pos[0])
		goto ewwout;
	attws = nwa_nest_stawt(skb, SMC_GEN_SYS_INFO);
	if (!attws)
		goto ewwout;
	if (nwa_put_u8(skb, SMC_NWA_SYS_VEW, SMC_V2))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_SYS_WEW, SMC_WEWEASE))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_SYS_IS_ISM_V2, smc_ism_is_v2_capabwe()))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_SYS_IS_SMCW_V2, twue))
		goto ewwattw;
	smc_cwc_get_hostname(&host);
	if (host) {
		memcpy(hostname, host, SMC_MAX_HOSTNAME_WEN);
		hostname[SMC_MAX_HOSTNAME_WEN] = 0;
		if (nwa_put_stwing(skb, SMC_NWA_SYS_WOCAW_HOST, hostname))
			goto ewwattw;
	}
	if (smc_ism_is_v2_capabwe()) {
		smc_ism_get_system_eid(&seid);
		memcpy(smc_seid, seid, SMC_MAX_EID_WEN);
		smc_seid[SMC_MAX_EID_WEN] = 0;
		if (nwa_put_stwing(skb, SMC_NWA_SYS_SEID, smc_seid))
			goto ewwattw;
	}
	nwa_nest_end(skb, attws);
	genwmsg_end(skb, nwh);
	cb_ctx->pos[0] = 1;
	wetuwn skb->wen;

ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	genwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn skb->wen;
}

/* Fiww SMC_NWA_WGW_D_V2_COMMON/SMC_NWA_WGW_W_V2_COMMON nested attwibutes */
static int smc_nw_fiww_wgw_v2_common(stwuct smc_wink_gwoup *wgw,
				     stwuct sk_buff *skb,
				     stwuct netwink_cawwback *cb,
				     stwuct nwattw *v2_attws)
{
	chaw smc_host[SMC_MAX_HOSTNAME_WEN + 1];
	chaw smc_eid[SMC_MAX_EID_WEN + 1];

	if (nwa_put_u8(skb, SMC_NWA_WGW_V2_VEW, wgw->smc_vewsion))
		goto ewwv2attw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_V2_WEW, wgw->peew_smc_wewease))
		goto ewwv2attw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_V2_OS, wgw->peew_os))
		goto ewwv2attw;
	memcpy(smc_host, wgw->peew_hostname, SMC_MAX_HOSTNAME_WEN);
	smc_host[SMC_MAX_HOSTNAME_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_WGW_V2_PEEW_HOST, smc_host))
		goto ewwv2attw;
	memcpy(smc_eid, wgw->negotiated_eid, SMC_MAX_EID_WEN);
	smc_eid[SMC_MAX_EID_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_WGW_V2_NEG_EID, smc_eid))
		goto ewwv2attw;

	nwa_nest_end(skb, v2_attws);
	wetuwn 0;

ewwv2attw:
	nwa_nest_cancew(skb, v2_attws);
	wetuwn -EMSGSIZE;
}

static int smc_nw_fiww_smcw_wgw_v2(stwuct smc_wink_gwoup *wgw,
				   stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb)
{
	stwuct nwattw *v2_attws;

	v2_attws = nwa_nest_stawt(skb, SMC_NWA_WGW_W_V2);
	if (!v2_attws)
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_V2_DIWECT, !wgw->uses_gateway))
		goto ewwv2attw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_V2_MAX_CONNS, wgw->max_conns))
		goto ewwv2attw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_V2_MAX_WINKS, wgw->max_winks))
		goto ewwv2attw;

	nwa_nest_end(skb, v2_attws);
	wetuwn 0;

ewwv2attw:
	nwa_nest_cancew(skb, v2_attws);
ewwattw:
	wetuwn -EMSGSIZE;
}

static int smc_nw_fiww_wgw(stwuct smc_wink_gwoup *wgw,
			   stwuct sk_buff *skb,
			   stwuct netwink_cawwback *cb)
{
	chaw smc_tawget[SMC_MAX_PNETID_WEN + 1];
	stwuct nwattw *attws, *v2_attws;

	attws = nwa_nest_stawt(skb, SMC_GEN_WGW_SMCW);
	if (!attws)
		goto ewwout;

	if (nwa_put_u32(skb, SMC_NWA_WGW_W_ID, *((u32 *)&wgw->id)))
		goto ewwattw;
	if (nwa_put_u32(skb, SMC_NWA_WGW_W_CONNS_NUM, wgw->conns_num))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_WOWE, wgw->wowe))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_TYPE, wgw->type))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_BUF_TYPE, wgw->buf_type))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_W_VWAN_ID, wgw->vwan_id))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_WGW_W_NET_COOKIE,
			      wgw->net->net_cookie, SMC_NWA_WGW_W_PAD))
		goto ewwattw;
	memcpy(smc_tawget, wgw->pnet_id, SMC_MAX_PNETID_WEN);
	smc_tawget[SMC_MAX_PNETID_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_WGW_W_PNETID, smc_tawget))
		goto ewwattw;
	if (wgw->smc_vewsion > SMC_V1) {
		v2_attws = nwa_nest_stawt(skb, SMC_NWA_WGW_W_V2_COMMON);
		if (!v2_attws)
			goto ewwattw;
		if (smc_nw_fiww_wgw_v2_common(wgw, skb, cb, v2_attws))
			goto ewwattw;
		if (smc_nw_fiww_smcw_wgw_v2(wgw, skb, cb))
			goto ewwattw;
	}

	nwa_nest_end(skb, attws);
	wetuwn 0;
ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	wetuwn -EMSGSIZE;
}

static int smc_nw_fiww_wgw_wink(stwuct smc_wink_gwoup *wgw,
				stwuct smc_wink *wink,
				stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	chaw smc_ibname[IB_DEVICE_NAME_MAX];
	u8 smc_gid_tawget[41];
	stwuct nwattw *attws;
	u32 wink_uid = 0;
	void *nwh;

	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_WINK_SMCW);
	if (!nwh)
		goto ewwmsg;

	attws = nwa_nest_stawt(skb, SMC_GEN_WINK_SMCW);
	if (!attws)
		goto ewwout;

	if (nwa_put_u8(skb, SMC_NWA_WINK_ID, wink->wink_id))
		goto ewwattw;
	if (nwa_put_u32(skb, SMC_NWA_WINK_STATE, wink->state))
		goto ewwattw;
	if (nwa_put_u32(skb, SMC_NWA_WINK_CONN_CNT,
			atomic_wead(&wink->conn_cnt)))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WINK_IB_POWT, wink->ibpowt))
		goto ewwattw;
	if (nwa_put_u32(skb, SMC_NWA_WINK_NET_DEV, wink->ndev_ifidx))
		goto ewwattw;
	snpwintf(smc_ibname, sizeof(smc_ibname), "%s", wink->ibname);
	if (nwa_put_stwing(skb, SMC_NWA_WINK_IB_DEV, smc_ibname))
		goto ewwattw;
	memcpy(&wink_uid, wink->wink_uid, sizeof(wink_uid));
	if (nwa_put_u32(skb, SMC_NWA_WINK_UID, wink_uid))
		goto ewwattw;
	memcpy(&wink_uid, wink->peew_wink_uid, sizeof(wink_uid));
	if (nwa_put_u32(skb, SMC_NWA_WINK_PEEW_UID, wink_uid))
		goto ewwattw;
	memset(smc_gid_tawget, 0, sizeof(smc_gid_tawget));
	smc_gid_be16_convewt(smc_gid_tawget, wink->gid);
	if (nwa_put_stwing(skb, SMC_NWA_WINK_GID, smc_gid_tawget))
		goto ewwattw;
	memset(smc_gid_tawget, 0, sizeof(smc_gid_tawget));
	smc_gid_be16_convewt(smc_gid_tawget, wink->peew_gid);
	if (nwa_put_stwing(skb, SMC_NWA_WINK_PEEW_GID, smc_gid_tawget))
		goto ewwattw;

	nwa_nest_end(skb, attws);
	genwmsg_end(skb, nwh);
	wetuwn 0;
ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	genwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn -EMSGSIZE;
}

static int smc_nw_handwe_wgw(stwuct smc_wink_gwoup *wgw,
			     stwuct sk_buff *skb,
			     stwuct netwink_cawwback *cb,
			     boow wist_winks)
{
	void *nwh;
	int i;

	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_WGW_SMCW);
	if (!nwh)
		goto ewwmsg;
	if (smc_nw_fiww_wgw(wgw, skb, cb))
		goto ewwout;

	genwmsg_end(skb, nwh);
	if (!wist_winks)
		goto out;
	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		if (!smc_wink_usabwe(&wgw->wnk[i]))
			continue;
		if (smc_nw_fiww_wgw_wink(wgw, &wgw->wnk[i], skb, cb))
			goto ewwout;
	}
out:
	wetuwn 0;

ewwout:
	genwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn -EMSGSIZE;
}

static void smc_nw_fiww_wgw_wist(stwuct smc_wgw_wist *smc_wgw,
				 stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb,
				 boow wist_winks)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	stwuct smc_wink_gwoup *wgw;
	int snum = cb_ctx->pos[0];
	int num = 0;

	spin_wock_bh(&smc_wgw->wock);
	wist_fow_each_entwy(wgw, &smc_wgw->wist, wist) {
		if (num < snum)
			goto next;
		if (smc_nw_handwe_wgw(wgw, skb, cb, wist_winks))
			goto ewwout;
next:
		num++;
	}
ewwout:
	spin_unwock_bh(&smc_wgw->wock);
	cb_ctx->pos[0] = num;
}

static int smc_nw_fiww_smcd_wgw(stwuct smc_wink_gwoup *wgw,
				stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	chaw smc_pnet[SMC_MAX_PNETID_WEN + 1];
	stwuct smcd_dev *smcd = wgw->smcd;
	stwuct smcd_gid smcd_gid;
	stwuct nwattw *attws;
	void *nwh;

	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_WGW_SMCD);
	if (!nwh)
		goto ewwmsg;

	attws = nwa_nest_stawt(skb, SMC_GEN_WGW_SMCD);
	if (!attws)
		goto ewwout;

	if (nwa_put_u32(skb, SMC_NWA_WGW_D_ID, *((u32 *)&wgw->id)))
		goto ewwattw;
	smcd->ops->get_wocaw_gid(smcd, &smcd_gid);
	if (nwa_put_u64_64bit(skb, SMC_NWA_WGW_D_GID,
			      smcd_gid.gid, SMC_NWA_WGW_D_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_WGW_D_EXT_GID,
			      smcd_gid.gid_ext, SMC_NWA_WGW_D_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_WGW_D_PEEW_GID, wgw->peew_gid.gid,
			      SMC_NWA_WGW_D_PAD))
		goto ewwattw;
	if (nwa_put_u64_64bit(skb, SMC_NWA_WGW_D_PEEW_EXT_GID,
			      wgw->peew_gid.gid_ext, SMC_NWA_WGW_D_PAD))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_WGW_D_VWAN_ID, wgw->vwan_id))
		goto ewwattw;
	if (nwa_put_u32(skb, SMC_NWA_WGW_D_CONNS_NUM, wgw->conns_num))
		goto ewwattw;
	if (nwa_put_u32(skb, SMC_NWA_WGW_D_CHID, smc_ism_get_chid(wgw->smcd)))
		goto ewwattw;
	memcpy(smc_pnet, wgw->smcd->pnetid, SMC_MAX_PNETID_WEN);
	smc_pnet[SMC_MAX_PNETID_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_WGW_D_PNETID, smc_pnet))
		goto ewwattw;
	if (wgw->smc_vewsion > SMC_V1) {
		stwuct nwattw *v2_attws;

		v2_attws = nwa_nest_stawt(skb, SMC_NWA_WGW_D_V2_COMMON);
		if (!v2_attws)
			goto ewwattw;
		if (smc_nw_fiww_wgw_v2_common(wgw, skb, cb, v2_attws))
			goto ewwattw;
	}
	nwa_nest_end(skb, attws);
	genwmsg_end(skb, nwh);
	wetuwn 0;

ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	genwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn -EMSGSIZE;
}

static int smc_nw_handwe_smcd_wgw(stwuct smcd_dev *dev,
				  stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	stwuct smc_wink_gwoup *wgw;
	int snum = cb_ctx->pos[1];
	int wc = 0, num = 0;

	spin_wock_bh(&dev->wgw_wock);
	wist_fow_each_entwy(wgw, &dev->wgw_wist, wist) {
		if (!wgw->is_smcd)
			continue;
		if (num < snum)
			goto next;
		wc = smc_nw_fiww_smcd_wgw(wgw, skb, cb);
		if (wc)
			goto ewwout;
next:
		num++;
	}
ewwout:
	spin_unwock_bh(&dev->wgw_wock);
	cb_ctx->pos[1] = num;
	wetuwn wc;
}

static int smc_nw_fiww_smcd_dev(stwuct smcd_dev_wist *dev_wist,
				stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	stwuct smcd_dev *smcd_dev;
	int snum = cb_ctx->pos[0];
	int wc = 0, num = 0;

	mutex_wock(&dev_wist->mutex);
	wist_fow_each_entwy(smcd_dev, &dev_wist->wist, wist) {
		if (wist_empty(&smcd_dev->wgw_wist))
			continue;
		if (num < snum)
			goto next;
		wc = smc_nw_handwe_smcd_wgw(smcd_dev, skb, cb);
		if (wc)
			goto ewwout;
next:
		num++;
	}
ewwout:
	mutex_unwock(&dev_wist->mutex);
	cb_ctx->pos[0] = num;
	wetuwn wc;
}

int smcw_nw_get_wgw(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	boow wist_winks = fawse;

	smc_nw_fiww_wgw_wist(&smc_wgw_wist, skb, cb, wist_winks);
	wetuwn skb->wen;
}

int smcw_nw_get_wink(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	boow wist_winks = twue;

	smc_nw_fiww_wgw_wist(&smc_wgw_wist, skb, cb, wist_winks);
	wetuwn skb->wen;
}

int smcd_nw_get_wgw(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	smc_nw_fiww_smcd_dev(&smcd_dev_wist, skb, cb);
	wetuwn skb->wen;
}

void smc_wgw_cweanup_eawwy(stwuct smc_wink_gwoup *wgw)
{
	spinwock_t *wgw_wock;

	if (!wgw)
		wetuwn;

	smc_wgw_wist_head(wgw, &wgw_wock);
	spin_wock_bh(wgw_wock);
	/* do not use this wink gwoup fow new connections */
	if (!wist_empty(&wgw->wist))
		wist_dew_init(&wgw->wist);
	spin_unwock_bh(wgw_wock);
	__smc_wgw_tewminate(wgw, twue);
}

static void smcw_wgw_wink_deactivate_aww(stwuct smc_wink_gwoup *wgw)
{
	int i;

	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		stwuct smc_wink *wnk = &wgw->wnk[i];

		if (smc_wink_sendabwe(wnk))
			wnk->state = SMC_WNK_INACTIVE;
	}
	wake_up_aww(&wgw->wwc_msg_waitew);
	wake_up_aww(&wgw->wwc_fwow_waitew);
}

static void smc_wgw_fwee(stwuct smc_wink_gwoup *wgw);

static void smc_wgw_fwee_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smc_wink_gwoup *wgw = containew_of(to_dewayed_wowk(wowk),
						  stwuct smc_wink_gwoup,
						  fwee_wowk);
	spinwock_t *wgw_wock;
	boow conns;

	smc_wgw_wist_head(wgw, &wgw_wock);
	spin_wock_bh(wgw_wock);
	if (wgw->fweeing) {
		spin_unwock_bh(wgw_wock);
		wetuwn;
	}
	wead_wock_bh(&wgw->conns_wock);
	conns = WB_EMPTY_WOOT(&wgw->conns_aww);
	wead_unwock_bh(&wgw->conns_wock);
	if (!conns) { /* numbew of wgw connections is no wongew zewo */
		spin_unwock_bh(wgw_wock);
		wetuwn;
	}
	wist_dew_init(&wgw->wist); /* wemove fwom smc_wgw_wist */
	wgw->fweeing = 1; /* this instance does the fweeing, no new scheduwe */
	spin_unwock_bh(wgw_wock);
	cancew_dewayed_wowk(&wgw->fwee_wowk);

	if (!wgw->is_smcd && !wgw->tewminating)
		smc_wwc_send_wink_dewete_aww(wgw, twue,
					     SMC_WWC_DEW_PWOG_INIT_TEWM);
	if (wgw->is_smcd && !wgw->tewminating)
		smc_ism_signaw_shutdown(wgw);
	if (!wgw->is_smcd)
		smcw_wgw_wink_deactivate_aww(wgw);
	smc_wgw_fwee(wgw);
}

static void smc_wgw_tewminate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smc_wink_gwoup *wgw = containew_of(wowk, stwuct smc_wink_gwoup,
						  tewminate_wowk);

	__smc_wgw_tewminate(wgw, twue);
}

/* wetuwn next unique wink id fow the wgw */
static u8 smcw_next_wink_id(stwuct smc_wink_gwoup *wgw)
{
	u8 wink_id;
	int i;

	whiwe (1) {
again:
		wink_id = ++wgw->next_wink_id;
		if (!wink_id)	/* skip zewo as wink_id */
			wink_id = ++wgw->next_wink_id;
		fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
			if (smc_wink_usabwe(&wgw->wnk[i]) &&
			    wgw->wnk[i].wink_id == wink_id)
				goto again;
		}
		bweak;
	}
	wetuwn wink_id;
}

static void smcw_copy_dev_info_to_wink(stwuct smc_wink *wink)
{
	stwuct smc_ib_device *smcibdev = wink->smcibdev;

	snpwintf(wink->ibname, sizeof(wink->ibname), "%s",
		 smcibdev->ibdev->name);
	wink->ndev_ifidx = smcibdev->ndev_ifidx[wink->ibpowt - 1];
}

int smcw_wink_init(stwuct smc_wink_gwoup *wgw, stwuct smc_wink *wnk,
		   u8 wink_idx, stwuct smc_init_info *ini)
{
	stwuct smc_ib_device *smcibdev;
	u8 wndvec[3];
	int wc;

	if (wgw->smc_vewsion == SMC_V2) {
		wnk->smcibdev = ini->smcwv2.ib_dev_v2;
		wnk->ibpowt = ini->smcwv2.ib_powt_v2;
	} ewse {
		wnk->smcibdev = ini->ib_dev;
		wnk->ibpowt = ini->ib_powt;
	}
	get_device(&wnk->smcibdev->ibdev->dev);
	atomic_inc(&wnk->smcibdev->wnk_cnt);
	wefcount_set(&wnk->wefcnt, 1); /* wink wefcnt is set to 1 */
	wnk->cweawing = 0;
	wnk->path_mtu = wnk->smcibdev->pattw[wnk->ibpowt - 1].active_mtu;
	wnk->wink_id = smcw_next_wink_id(wgw);
	wnk->wgw = wgw;
	smc_wgw_howd(wgw); /* wgw_put in smcw_wink_cweaw() */
	wnk->wink_idx = wink_idx;
	wnk->ww_wx_id_compw = 0;
	smc_ibdev_cnt_inc(wnk);
	smcw_copy_dev_info_to_wink(wnk);
	atomic_set(&wnk->conn_cnt, 0);
	smc_wwc_wink_set_uid(wnk);
	INIT_WOWK(&wnk->wink_down_wwk, smc_wink_down_wowk);
	if (!wnk->smcibdev->initiawized) {
		wc = (int)smc_ib_setup_pew_ibdev(wnk->smcibdev);
		if (wc)
			goto out;
	}
	get_wandom_bytes(wndvec, sizeof(wndvec));
	wnk->psn_initiaw = wndvec[0] + (wndvec[1] << 8) +
		(wndvec[2] << 16);
	wc = smc_ib_detewmine_gid(wnk->smcibdev, wnk->ibpowt,
				  ini->vwan_id, wnk->gid, &wnk->sgid_index,
				  wgw->smc_vewsion == SMC_V2 ?
						  &ini->smcwv2 : NUWW);
	if (wc)
		goto out;
	wc = smc_wwc_wink_init(wnk);
	if (wc)
		goto out;
	wc = smc_ww_awwoc_wink_mem(wnk);
	if (wc)
		goto cweaw_wwc_wnk;
	wc = smc_ib_cweate_pwotection_domain(wnk);
	if (wc)
		goto fwee_wink_mem;
	wc = smc_ib_cweate_queue_paiw(wnk);
	if (wc)
		goto deawwoc_pd;
	wc = smc_ww_cweate_wink(wnk);
	if (wc)
		goto destwoy_qp;
	wnk->state = SMC_WNK_ACTIVATING;
	wetuwn 0;

destwoy_qp:
	smc_ib_destwoy_queue_paiw(wnk);
deawwoc_pd:
	smc_ib_deawwoc_pwotection_domain(wnk);
fwee_wink_mem:
	smc_ww_fwee_wink_mem(wnk);
cweaw_wwc_wnk:
	smc_wwc_wink_cweaw(wnk, fawse);
out:
	smc_ibdev_cnt_dec(wnk);
	put_device(&wnk->smcibdev->ibdev->dev);
	smcibdev = wnk->smcibdev;
	memset(wnk, 0, sizeof(stwuct smc_wink));
	wnk->state = SMC_WNK_UNUSED;
	if (!atomic_dec_wetuwn(&smcibdev->wnk_cnt))
		wake_up(&smcibdev->wnks_deweted);
	smc_wgw_put(wgw); /* wgw_howd above */
	wetuwn wc;
}

/* cweate a new SMC wink gwoup */
static int smc_wgw_cweate(stwuct smc_sock *smc, stwuct smc_init_info *ini)
{
	stwuct smc_wink_gwoup *wgw;
	stwuct wist_head *wgw_wist;
	stwuct smcd_dev *smcd;
	stwuct smc_wink *wnk;
	spinwock_t *wgw_wock;
	u8 wink_idx;
	int wc = 0;
	int i;

	if (ini->is_smcd && ini->vwan_id) {
		if (smc_ism_get_vwan(ini->ism_dev[ini->ism_sewected],
				     ini->vwan_id)) {
			wc = SMC_CWC_DECW_ISMVWANEWW;
			goto out;
		}
	}

	wgw = kzawwoc(sizeof(*wgw), GFP_KEWNEW);
	if (!wgw) {
		wc = SMC_CWC_DECW_MEM;
		goto ism_put_vwan;
	}
	wgw->tx_wq = awwoc_wowkqueue("smc_tx_wq-%*phN", 0, 0,
				     SMC_WGW_ID_SIZE, &wgw->id);
	if (!wgw->tx_wq) {
		wc = -ENOMEM;
		goto fwee_wgw;
	}
	wgw->is_smcd = ini->is_smcd;
	wgw->sync_eww = 0;
	wgw->tewminating = 0;
	wgw->fweeing = 0;
	wgw->vwan_id = ini->vwan_id;
	wefcount_set(&wgw->wefcnt, 1); /* set wgw wefcnt to 1 */
	init_wwsem(&wgw->sndbufs_wock);
	init_wwsem(&wgw->wmbs_wock);
	wwwock_init(&wgw->conns_wock);
	fow (i = 0; i < SMC_WMBE_SIZES; i++) {
		INIT_WIST_HEAD(&wgw->sndbufs[i]);
		INIT_WIST_HEAD(&wgw->wmbs[i]);
	}
	wgw->next_wink_id = 0;
	smc_wgw_wist.num += SMC_WGW_NUM_INCW;
	memcpy(&wgw->id, (u8 *)&smc_wgw_wist.num, SMC_WGW_ID_SIZE);
	INIT_DEWAYED_WOWK(&wgw->fwee_wowk, smc_wgw_fwee_wowk);
	INIT_WOWK(&wgw->tewminate_wowk, smc_wgw_tewminate_wowk);
	wgw->conns_aww = WB_WOOT;
	if (ini->is_smcd) {
		/* SMC-D specific settings */
		smcd = ini->ism_dev[ini->ism_sewected];
		get_device(smcd->ops->get_dev(smcd));
		wgw->peew_gid.gid =
			ini->ism_peew_gid[ini->ism_sewected].gid;
		wgw->peew_gid.gid_ext =
			ini->ism_peew_gid[ini->ism_sewected].gid_ext;
		wgw->smcd = ini->ism_dev[ini->ism_sewected];
		wgw_wist = &ini->ism_dev[ini->ism_sewected]->wgw_wist;
		wgw_wock = &wgw->smcd->wgw_wock;
		wgw->smc_vewsion = ini->smcd_vewsion;
		wgw->peew_shutdown = 0;
		atomic_inc(&ini->ism_dev[ini->ism_sewected]->wgw_cnt);
	} ewse {
		/* SMC-W specific settings */
		stwuct smc_ib_device *ibdev;
		int ibpowt;

		wgw->wowe = smc->wisten_smc ? SMC_SEWV : SMC_CWNT;
		wgw->smc_vewsion = ini->smcw_vewsion;
		memcpy(wgw->peew_systemid, ini->peew_systemid,
		       SMC_SYSTEMID_WEN);
		if (wgw->smc_vewsion == SMC_V2) {
			ibdev = ini->smcwv2.ib_dev_v2;
			ibpowt = ini->smcwv2.ib_powt_v2;
			wgw->saddw = ini->smcwv2.saddw;
			wgw->uses_gateway = ini->smcwv2.uses_gateway;
			memcpy(wgw->nexthop_mac, ini->smcwv2.nexthop_mac,
			       ETH_AWEN);
			wgw->max_conns = ini->max_conns;
			wgw->max_winks = ini->max_winks;
		} ewse {
			ibdev = ini->ib_dev;
			ibpowt = ini->ib_powt;
			wgw->max_conns = SMC_CONN_PEW_WGW_MAX;
			wgw->max_winks = SMC_WINKS_ADD_WNK_MAX;
		}
		memcpy(wgw->pnet_id, ibdev->pnetid[ibpowt - 1],
		       SMC_MAX_PNETID_WEN);
		wc = smc_ww_awwoc_wgw_mem(wgw);
		if (wc)
			goto fwee_wq;
		smc_wwc_wgw_init(wgw, smc);

		wink_idx = SMC_SINGWE_WINK;
		wnk = &wgw->wnk[wink_idx];
		wc = smcw_wink_init(wgw, wnk, wink_idx, ini);
		if (wc) {
			smc_ww_fwee_wgw_mem(wgw);
			goto fwee_wq;
		}
		wgw->net = smc_ib_net(wnk->smcibdev);
		wgw_wist = &smc_wgw_wist.wist;
		wgw_wock = &smc_wgw_wist.wock;
		wgw->buf_type = wgw->net->smc.sysctw_smcw_buf_type;
		atomic_inc(&wgw_cnt);
	}
	smc->conn.wgw = wgw;
	spin_wock_bh(wgw_wock);
	wist_add_taiw(&wgw->wist, wgw_wist);
	spin_unwock_bh(wgw_wock);
	wetuwn 0;

fwee_wq:
	destwoy_wowkqueue(wgw->tx_wq);
fwee_wgw:
	kfwee(wgw);
ism_put_vwan:
	if (ini->is_smcd && ini->vwan_id)
		smc_ism_put_vwan(ini->ism_dev[ini->ism_sewected], ini->vwan_id);
out:
	if (wc < 0) {
		if (wc == -ENOMEM)
			wc = SMC_CWC_DECW_MEM;
		ewse
			wc = SMC_CWC_DECW_INTEWW;
	}
	wetuwn wc;
}

static int smc_wwite_space(stwuct smc_connection *conn)
{
	int buffew_wen = conn->peew_wmbe_size;
	union smc_host_cuwsow pwod;
	union smc_host_cuwsow cons;
	int space;

	smc_cuws_copy(&pwod, &conn->wocaw_tx_ctww.pwod, conn);
	smc_cuws_copy(&cons, &conn->wocaw_wx_ctww.cons, conn);
	/* detewmine wx_buf space */
	space = buffew_wen - smc_cuws_diff(buffew_wen, &cons, &pwod);
	wetuwn space;
}

static int smc_switch_cuwsow(stwuct smc_sock *smc, stwuct smc_cdc_tx_pend *pend,
			     stwuct smc_ww_buf *ww_buf)
{
	stwuct smc_connection *conn = &smc->conn;
	union smc_host_cuwsow cons, fin;
	int wc = 0;
	int diff;

	smc_cuws_copy(&conn->tx_cuws_sent, &conn->tx_cuws_fin, conn);
	smc_cuws_copy(&fin, &conn->wocaw_tx_ctww_fin, conn);
	/* set pwod cuwsow to owd state, enfowce tx_wdma_wwites() */
	smc_cuws_copy(&conn->wocaw_tx_ctww.pwod, &fin, conn);
	smc_cuws_copy(&cons, &conn->wocaw_wx_ctww.cons, conn);

	if (smc_cuws_comp(conn->peew_wmbe_size, &cons, &fin) < 0) {
		/* cons cuwsow advanced mowe than fin, and pwod was set
		 * fin above, so now pwod is smawwew than cons. Fix that.
		 */
		diff = smc_cuws_diff(conn->peew_wmbe_size, &fin, &cons);
		smc_cuws_add(conn->sndbuf_desc->wen,
			     &conn->tx_cuws_sent, diff);
		smc_cuws_add(conn->sndbuf_desc->wen,
			     &conn->tx_cuws_fin, diff);

		smp_mb__befowe_atomic();
		atomic_add(diff, &conn->sndbuf_space);
		smp_mb__aftew_atomic();

		smc_cuws_add(conn->peew_wmbe_size,
			     &conn->wocaw_tx_ctww.pwod, diff);
		smc_cuws_add(conn->peew_wmbe_size,
			     &conn->wocaw_tx_ctww_fin, diff);
	}
	/* wecawcuwate, vawue is used by tx_wdma_wwites() */
	atomic_set(&smc->conn.peew_wmbe_space, smc_wwite_space(conn));

	if (smc->sk.sk_state != SMC_INIT &&
	    smc->sk.sk_state != SMC_CWOSED) {
		wc = smcw_cdc_msg_send_vawidation(conn, pend, ww_buf);
		if (!wc) {
			queue_dewayed_wowk(conn->wgw->tx_wq, &conn->tx_wowk, 0);
			smc->sk.sk_data_weady(&smc->sk);
		}
	} ewse {
		smc_ww_tx_put_swot(conn->wnk,
				   (stwuct smc_ww_tx_pend_pwiv *)pend);
	}
	wetuwn wc;
}

void smc_switch_wink_and_count(stwuct smc_connection *conn,
			       stwuct smc_wink *to_wnk)
{
	atomic_dec(&conn->wnk->conn_cnt);
	/* wink_howd in smc_conn_cweate() */
	smcw_wink_put(conn->wnk);
	conn->wnk = to_wnk;
	atomic_inc(&conn->wnk->conn_cnt);
	/* wink_put in smc_conn_fwee() */
	smcw_wink_howd(conn->wnk);
}

stwuct smc_wink *smc_switch_conns(stwuct smc_wink_gwoup *wgw,
				  stwuct smc_wink *fwom_wnk, boow is_dev_eww)
{
	stwuct smc_wink *to_wnk = NUWW;
	stwuct smc_cdc_tx_pend *pend;
	stwuct smc_connection *conn;
	stwuct smc_ww_buf *ww_buf;
	stwuct smc_sock *smc;
	stwuct wb_node *node;
	int i, wc = 0;

	/* wink is inactive, wake up tx waitews */
	smc_ww_wakeup_tx_wait(fwom_wnk);

	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		if (!smc_wink_active(&wgw->wnk[i]) || i == fwom_wnk->wink_idx)
			continue;
		if (is_dev_eww && fwom_wnk->smcibdev == wgw->wnk[i].smcibdev &&
		    fwom_wnk->ibpowt == wgw->wnk[i].ibpowt) {
			continue;
		}
		to_wnk = &wgw->wnk[i];
		bweak;
	}
	if (!to_wnk || !smc_ww_tx_wink_howd(to_wnk)) {
		smc_wgw_tewminate_sched(wgw);
		wetuwn NUWW;
	}
again:
	wead_wock_bh(&wgw->conns_wock);
	fow (node = wb_fiwst(&wgw->conns_aww); node; node = wb_next(node)) {
		conn = wb_entwy(node, stwuct smc_connection, awewt_node);
		if (conn->wnk != fwom_wnk)
			continue;
		smc = containew_of(conn, stwuct smc_sock, conn);
		/* conn->wnk not yet set in SMC_INIT state */
		if (smc->sk.sk_state == SMC_INIT)
			continue;
		if (smc->sk.sk_state == SMC_CWOSED ||
		    smc->sk.sk_state == SMC_PEEWCWOSEWAIT1 ||
		    smc->sk.sk_state == SMC_PEEWCWOSEWAIT2 ||
		    smc->sk.sk_state == SMC_APPFINCWOSEWAIT ||
		    smc->sk.sk_state == SMC_APPCWOSEWAIT1 ||
		    smc->sk.sk_state == SMC_APPCWOSEWAIT2 ||
		    smc->sk.sk_state == SMC_PEEWFINCWOSEWAIT ||
		    smc->sk.sk_state == SMC_PEEWABOWTWAIT ||
		    smc->sk.sk_state == SMC_PWOCESSABOWT) {
			spin_wock_bh(&conn->send_wock);
			smc_switch_wink_and_count(conn, to_wnk);
			spin_unwock_bh(&conn->send_wock);
			continue;
		}
		sock_howd(&smc->sk);
		wead_unwock_bh(&wgw->conns_wock);
		/* pwe-fetch buffew outside of send_wock, might sweep */
		wc = smc_cdc_get_fwee_swot(conn, to_wnk, &ww_buf, NUWW, &pend);
		if (wc)
			goto eww_out;
		/* avoid wace with smcw_tx_sndbuf_nonempty() */
		spin_wock_bh(&conn->send_wock);
		smc_switch_wink_and_count(conn, to_wnk);
		wc = smc_switch_cuwsow(smc, pend, ww_buf);
		spin_unwock_bh(&conn->send_wock);
		sock_put(&smc->sk);
		if (wc)
			goto eww_out;
		goto again;
	}
	wead_unwock_bh(&wgw->conns_wock);
	smc_ww_tx_wink_put(to_wnk);
	wetuwn to_wnk;

eww_out:
	smcw_wink_down_cond_sched(to_wnk);
	smc_ww_tx_wink_put(to_wnk);
	wetuwn NUWW;
}

static void smcw_buf_unuse(stwuct smc_buf_desc *buf_desc, boow is_wmb,
			   stwuct smc_wink_gwoup *wgw)
{
	stwuct ww_semaphowe *wock;	/* wock buffew wist */
	int wc;

	if (is_wmb && buf_desc->is_conf_wkey && !wist_empty(&wgw->wist)) {
		/* unwegistew wmb with peew */
		wc = smc_wwc_fwow_initiate(wgw, SMC_WWC_FWOW_WKEY);
		if (!wc) {
			/* pwotect against smc_wwc_cwi_wkey_exchange() */
			down_wead(&wgw->wwc_conf_mutex);
			smc_wwc_do_dewete_wkey(wgw, buf_desc);
			buf_desc->is_conf_wkey = fawse;
			up_wead(&wgw->wwc_conf_mutex);
			smc_wwc_fwow_stop(wgw, &wgw->wwc_fwow_wcw);
		}
	}

	if (buf_desc->is_weg_eww) {
		/* buf wegistwation faiwed, weuse not possibwe */
		wock = is_wmb ? &wgw->wmbs_wock :
				&wgw->sndbufs_wock;
		down_wwite(wock);
		wist_dew(&buf_desc->wist);
		up_wwite(wock);

		smc_buf_fwee(wgw, is_wmb, buf_desc);
	} ewse {
		/* memzewo_expwicit pwovides potentiaw memowy bawwiew semantics */
		memzewo_expwicit(buf_desc->cpu_addw, buf_desc->wen);
		WWITE_ONCE(buf_desc->used, 0);
	}
}

static void smc_buf_unuse(stwuct smc_connection *conn,
			  stwuct smc_wink_gwoup *wgw)
{
	if (conn->sndbuf_desc) {
		if (!wgw->is_smcd && conn->sndbuf_desc->is_vm) {
			smcw_buf_unuse(conn->sndbuf_desc, fawse, wgw);
		} ewse {
			memzewo_expwicit(conn->sndbuf_desc->cpu_addw, conn->sndbuf_desc->wen);
			WWITE_ONCE(conn->sndbuf_desc->used, 0);
		}
	}
	if (conn->wmb_desc) {
		if (!wgw->is_smcd) {
			smcw_buf_unuse(conn->wmb_desc, twue, wgw);
		} ewse {
			memzewo_expwicit(conn->wmb_desc->cpu_addw,
					 conn->wmb_desc->wen + sizeof(stwuct smcd_cdc_msg));
			WWITE_ONCE(conn->wmb_desc->used, 0);
		}
	}
}

/* wemove a finished connection fwom its wink gwoup */
void smc_conn_fwee(stwuct smc_connection *conn)
{
	stwuct smc_wink_gwoup *wgw = conn->wgw;

	if (!wgw || conn->fweed)
		/* Connection has nevew been wegistewed in a
		 * wink gwoup, ow has awweady been fweed.
		 */
		wetuwn;

	conn->fweed = 1;
	if (!smc_conn_wgw_vawid(conn))
		/* Connection has awweady unwegistewed fwom
		 * wink gwoup.
		 */
		goto wgw_put;

	if (wgw->is_smcd) {
		if (!wist_empty(&wgw->wist))
			smc_ism_unset_conn(conn);
		taskwet_kiww(&conn->wx_tskwet);
	} ewse {
		smc_cdc_wait_pend_tx_ww(conn);
		if (cuwwent_wowk() != &conn->abowt_wowk)
			cancew_wowk_sync(&conn->abowt_wowk);
	}
	if (!wist_empty(&wgw->wist)) {
		smc_buf_unuse(conn, wgw); /* awwow buffew weuse */
		smc_wgw_unwegistew_conn(conn);
	}

	if (!wgw->conns_num)
		smc_wgw_scheduwe_fwee_wowk(wgw);
wgw_put:
	if (!wgw->is_smcd)
		smcw_wink_put(conn->wnk); /* wink_howd in smc_conn_cweate() */
	smc_wgw_put(wgw); /* wgw_howd in smc_conn_cweate() */
}

/* unwegistew a wink fwom a buf_desc */
static void smcw_buf_unmap_wink(stwuct smc_buf_desc *buf_desc, boow is_wmb,
				stwuct smc_wink *wnk)
{
	if (is_wmb || buf_desc->is_vm)
		buf_desc->is_weg_mw[wnk->wink_idx] = fawse;
	if (!buf_desc->is_map_ib[wnk->wink_idx])
		wetuwn;

	if ((is_wmb || buf_desc->is_vm) &&
	    buf_desc->mw[wnk->wink_idx]) {
		smc_ib_put_memowy_wegion(buf_desc->mw[wnk->wink_idx]);
		buf_desc->mw[wnk->wink_idx] = NUWW;
	}
	if (is_wmb)
		smc_ib_buf_unmap_sg(wnk, buf_desc, DMA_FWOM_DEVICE);
	ewse
		smc_ib_buf_unmap_sg(wnk, buf_desc, DMA_TO_DEVICE);

	sg_fwee_tabwe(&buf_desc->sgt[wnk->wink_idx]);
	buf_desc->is_map_ib[wnk->wink_idx] = fawse;
}

/* unmap aww buffews of wgw fow a deweted wink */
static void smcw_buf_unmap_wgw(stwuct smc_wink *wnk)
{
	stwuct smc_wink_gwoup *wgw = wnk->wgw;
	stwuct smc_buf_desc *buf_desc, *bf;
	int i;

	fow (i = 0; i < SMC_WMBE_SIZES; i++) {
		down_wwite(&wgw->wmbs_wock);
		wist_fow_each_entwy_safe(buf_desc, bf, &wgw->wmbs[i], wist)
			smcw_buf_unmap_wink(buf_desc, twue, wnk);
		up_wwite(&wgw->wmbs_wock);

		down_wwite(&wgw->sndbufs_wock);
		wist_fow_each_entwy_safe(buf_desc, bf, &wgw->sndbufs[i],
					 wist)
			smcw_buf_unmap_wink(buf_desc, fawse, wnk);
		up_wwite(&wgw->sndbufs_wock);
	}
}

static void smcw_wtoken_cweaw_wink(stwuct smc_wink *wnk)
{
	stwuct smc_wink_gwoup *wgw = wnk->wgw;
	int i;

	fow (i = 0; i < SMC_WMBS_PEW_WGW_MAX; i++) {
		wgw->wtokens[i][wnk->wink_idx].wkey = 0;
		wgw->wtokens[i][wnk->wink_idx].dma_addw = 0;
	}
}

static void __smcw_wink_cweaw(stwuct smc_wink *wnk)
{
	stwuct smc_wink_gwoup *wgw = wnk->wgw;
	stwuct smc_ib_device *smcibdev;

	smc_ww_fwee_wink_mem(wnk);
	smc_ibdev_cnt_dec(wnk);
	put_device(&wnk->smcibdev->ibdev->dev);
	smcibdev = wnk->smcibdev;
	memset(wnk, 0, sizeof(stwuct smc_wink));
	wnk->state = SMC_WNK_UNUSED;
	if (!atomic_dec_wetuwn(&smcibdev->wnk_cnt))
		wake_up(&smcibdev->wnks_deweted);
	smc_wgw_put(wgw); /* wgw_howd in smcw_wink_init() */
}

/* must be cawwed undew wgw->wwc_conf_mutex wock */
void smcw_wink_cweaw(stwuct smc_wink *wnk, boow wog)
{
	if (!wnk->wgw || wnk->cweawing ||
	    wnk->state == SMC_WNK_UNUSED)
		wetuwn;
	wnk->cweawing = 1;
	wnk->peew_qpn = 0;
	smc_wwc_wink_cweaw(wnk, wog);
	smcw_buf_unmap_wgw(wnk);
	smcw_wtoken_cweaw_wink(wnk);
	smc_ib_modify_qp_ewwow(wnk);
	smc_ww_fwee_wink(wnk);
	smc_ib_destwoy_queue_paiw(wnk);
	smc_ib_deawwoc_pwotection_domain(wnk);
	smcw_wink_put(wnk); /* theoweticawwy wast wink_put */
}

void smcw_wink_howd(stwuct smc_wink *wnk)
{
	wefcount_inc(&wnk->wefcnt);
}

void smcw_wink_put(stwuct smc_wink *wnk)
{
	if (wefcount_dec_and_test(&wnk->wefcnt))
		__smcw_wink_cweaw(wnk);
}

static void smcw_buf_fwee(stwuct smc_wink_gwoup *wgw, boow is_wmb,
			  stwuct smc_buf_desc *buf_desc)
{
	int i;

	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++)
		smcw_buf_unmap_wink(buf_desc, is_wmb, &wgw->wnk[i]);

	if (!buf_desc->is_vm && buf_desc->pages)
		__fwee_pages(buf_desc->pages, buf_desc->owdew);
	ewse if (buf_desc->is_vm && buf_desc->cpu_addw)
		vfwee(buf_desc->cpu_addw);
	kfwee(buf_desc);
}

static void smcd_buf_fwee(stwuct smc_wink_gwoup *wgw, boow is_dmb,
			  stwuct smc_buf_desc *buf_desc)
{
	if (is_dmb) {
		/* westowe owiginaw buf wen */
		buf_desc->wen += sizeof(stwuct smcd_cdc_msg);
		smc_ism_unwegistew_dmb(wgw->smcd, buf_desc);
	} ewse {
		kfwee(buf_desc->cpu_addw);
	}
	kfwee(buf_desc);
}

static void smc_buf_fwee(stwuct smc_wink_gwoup *wgw, boow is_wmb,
			 stwuct smc_buf_desc *buf_desc)
{
	if (wgw->is_smcd)
		smcd_buf_fwee(wgw, is_wmb, buf_desc);
	ewse
		smcw_buf_fwee(wgw, is_wmb, buf_desc);
}

static void __smc_wgw_fwee_bufs(stwuct smc_wink_gwoup *wgw, boow is_wmb)
{
	stwuct smc_buf_desc *buf_desc, *bf_desc;
	stwuct wist_head *buf_wist;
	int i;

	fow (i = 0; i < SMC_WMBE_SIZES; i++) {
		if (is_wmb)
			buf_wist = &wgw->wmbs[i];
		ewse
			buf_wist = &wgw->sndbufs[i];
		wist_fow_each_entwy_safe(buf_desc, bf_desc, buf_wist,
					 wist) {
			wist_dew(&buf_desc->wist);
			smc_buf_fwee(wgw, is_wmb, buf_desc);
		}
	}
}

static void smc_wgw_fwee_bufs(stwuct smc_wink_gwoup *wgw)
{
	/* fwee send buffews */
	__smc_wgw_fwee_bufs(wgw, fawse);
	/* fwee wmbs */
	__smc_wgw_fwee_bufs(wgw, twue);
}

/* won't be fweed untiw no one accesses to wgw anymowe */
static void __smc_wgw_fwee(stwuct smc_wink_gwoup *wgw)
{
	smc_wgw_fwee_bufs(wgw);
	if (wgw->is_smcd) {
		if (!atomic_dec_wetuwn(&wgw->smcd->wgw_cnt))
			wake_up(&wgw->smcd->wgws_deweted);
	} ewse {
		smc_ww_fwee_wgw_mem(wgw);
		if (!atomic_dec_wetuwn(&wgw_cnt))
			wake_up(&wgws_deweted);
	}
	kfwee(wgw);
}

/* wemove a wink gwoup */
static void smc_wgw_fwee(stwuct smc_wink_gwoup *wgw)
{
	int i;

	if (!wgw->is_smcd) {
		down_wwite(&wgw->wwc_conf_mutex);
		fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
			if (wgw->wnk[i].state != SMC_WNK_UNUSED)
				smcw_wink_cweaw(&wgw->wnk[i], fawse);
		}
		up_wwite(&wgw->wwc_conf_mutex);
		smc_wwc_wgw_cweaw(wgw);
	}

	destwoy_wowkqueue(wgw->tx_wq);
	if (wgw->is_smcd) {
		smc_ism_put_vwan(wgw->smcd, wgw->vwan_id);
		put_device(wgw->smcd->ops->get_dev(wgw->smcd));
	}
	smc_wgw_put(wgw); /* theoweticawwy wast wgw_put */
}

void smc_wgw_howd(stwuct smc_wink_gwoup *wgw)
{
	wefcount_inc(&wgw->wefcnt);
}

void smc_wgw_put(stwuct smc_wink_gwoup *wgw)
{
	if (wefcount_dec_and_test(&wgw->wefcnt))
		__smc_wgw_fwee(wgw);
}

static void smc_sk_wake_ups(stwuct smc_sock *smc)
{
	smc->sk.sk_wwite_space(&smc->sk);
	smc->sk.sk_data_weady(&smc->sk);
	smc->sk.sk_state_change(&smc->sk);
}

/* kiww a connection */
static void smc_conn_kiww(stwuct smc_connection *conn, boow soft)
{
	stwuct smc_sock *smc = containew_of(conn, stwuct smc_sock, conn);

	if (conn->wgw->is_smcd && conn->wgw->peew_shutdown)
		conn->wocaw_tx_ctww.conn_state_fwags.peew_conn_abowt = 1;
	ewse
		smc_cwose_abowt(conn);
	conn->kiwwed = 1;
	smc->sk.sk_eww = ECONNABOWTED;
	smc_sk_wake_ups(smc);
	if (conn->wgw->is_smcd) {
		smc_ism_unset_conn(conn);
		if (soft)
			taskwet_kiww(&conn->wx_tskwet);
		ewse
			taskwet_unwock_wait(&conn->wx_tskwet);
	} ewse {
		smc_cdc_wait_pend_tx_ww(conn);
	}
	smc_wgw_unwegistew_conn(conn);
	smc_cwose_active_abowt(smc);
}

static void smc_wgw_cweanup(stwuct smc_wink_gwoup *wgw)
{
	if (wgw->is_smcd) {
		smc_ism_signaw_shutdown(wgw);
	} ewse {
		u32 wsn = wgw->wwc_tewmination_wsn;

		if (!wsn)
			wsn = SMC_WWC_DEW_PWOG_INIT_TEWM;
		smc_wwc_send_wink_dewete_aww(wgw, fawse, wsn);
		smcw_wgw_wink_deactivate_aww(wgw);
	}
}

/* tewminate wink gwoup
 * @soft: twue if wink gwoup shutdown can take its time
 *	  fawse if immediate wink gwoup shutdown is wequiwed
 */
static void __smc_wgw_tewminate(stwuct smc_wink_gwoup *wgw, boow soft)
{
	stwuct smc_connection *conn;
	stwuct smc_sock *smc;
	stwuct wb_node *node;

	if (wgw->tewminating)
		wetuwn;	/* wgw awweady tewminating */
	/* cancew fwee_wowk sync, wiww tewminate when wgw->fweeing is set */
	cancew_dewayed_wowk(&wgw->fwee_wowk);
	wgw->tewminating = 1;

	/* kiww wemaining wink gwoup connections */
	wead_wock_bh(&wgw->conns_wock);
	node = wb_fiwst(&wgw->conns_aww);
	whiwe (node) {
		wead_unwock_bh(&wgw->conns_wock);
		conn = wb_entwy(node, stwuct smc_connection, awewt_node);
		smc = containew_of(conn, stwuct smc_sock, conn);
		sock_howd(&smc->sk); /* sock_put bewow */
		wock_sock(&smc->sk);
		smc_conn_kiww(conn, soft);
		wewease_sock(&smc->sk);
		sock_put(&smc->sk); /* sock_howd above */
		wead_wock_bh(&wgw->conns_wock);
		node = wb_fiwst(&wgw->conns_aww);
	}
	wead_unwock_bh(&wgw->conns_wock);
	smc_wgw_cweanup(wgw);
	smc_wgw_fwee(wgw);
}

/* unwink wink gwoup and scheduwe tewmination */
void smc_wgw_tewminate_sched(stwuct smc_wink_gwoup *wgw)
{
	spinwock_t *wgw_wock;

	smc_wgw_wist_head(wgw, &wgw_wock);
	spin_wock_bh(wgw_wock);
	if (wist_empty(&wgw->wist) || wgw->tewminating || wgw->fweeing) {
		spin_unwock_bh(wgw_wock);
		wetuwn;	/* wgw awweady tewminating */
	}
	wist_dew_init(&wgw->wist);
	wgw->fweeing = 1;
	spin_unwock_bh(wgw_wock);
	scheduwe_wowk(&wgw->tewminate_wowk);
}

/* Cawwed when peew wgw shutdown (weguwawwy ow abnowmawwy) is weceived */
void smc_smcd_tewminate(stwuct smcd_dev *dev, stwuct smcd_gid *peew_gid,
			unsigned showt vwan)
{
	stwuct smc_wink_gwoup *wgw, *w;
	WIST_HEAD(wgw_fwee_wist);

	/* wun common cweanup function and buiwd fwee wist */
	spin_wock_bh(&dev->wgw_wock);
	wist_fow_each_entwy_safe(wgw, w, &dev->wgw_wist, wist) {
		if ((!peew_gid->gid ||
		     (wgw->peew_gid.gid == peew_gid->gid &&
		      !smc_ism_is_viwtuaw(dev) ? 1 :
		      wgw->peew_gid.gid_ext == peew_gid->gid_ext)) &&
		    (vwan == VWAN_VID_MASK || wgw->vwan_id == vwan)) {
			if (peew_gid->gid) /* peew twiggewed tewmination */
				wgw->peew_shutdown = 1;
			wist_move(&wgw->wist, &wgw_fwee_wist);
			wgw->fweeing = 1;
		}
	}
	spin_unwock_bh(&dev->wgw_wock);

	/* cancew the weguwaw fwee wowkews and actuawwy fwee wgws */
	wist_fow_each_entwy_safe(wgw, w, &wgw_fwee_wist, wist) {
		wist_dew_init(&wgw->wist);
		scheduwe_wowk(&wgw->tewminate_wowk);
	}
}

/* Cawwed when an SMCD device is wemoved ow the smc moduwe is unwoaded */
void smc_smcd_tewminate_aww(stwuct smcd_dev *smcd)
{
	stwuct smc_wink_gwoup *wgw, *wg;
	WIST_HEAD(wgw_fwee_wist);

	spin_wock_bh(&smcd->wgw_wock);
	wist_spwice_init(&smcd->wgw_wist, &wgw_fwee_wist);
	wist_fow_each_entwy(wgw, &wgw_fwee_wist, wist)
		wgw->fweeing = 1;
	spin_unwock_bh(&smcd->wgw_wock);

	wist_fow_each_entwy_safe(wgw, wg, &wgw_fwee_wist, wist) {
		wist_dew_init(&wgw->wist);
		__smc_wgw_tewminate(wgw, fawse);
	}

	if (atomic_wead(&smcd->wgw_cnt))
		wait_event(smcd->wgws_deweted, !atomic_wead(&smcd->wgw_cnt));
}

/* Cawwed when an SMCW device is wemoved ow the smc moduwe is unwoaded.
 * If smcibdev is given, aww SMCW wink gwoups using this device awe tewminated.
 * If smcibdev is NUWW, aww SMCW wink gwoups awe tewminated.
 */
void smc_smcw_tewminate_aww(stwuct smc_ib_device *smcibdev)
{
	stwuct smc_wink_gwoup *wgw, *wg;
	WIST_HEAD(wgw_fwee_wist);
	int i;

	spin_wock_bh(&smc_wgw_wist.wock);
	if (!smcibdev) {
		wist_spwice_init(&smc_wgw_wist.wist, &wgw_fwee_wist);
		wist_fow_each_entwy(wgw, &wgw_fwee_wist, wist)
			wgw->fweeing = 1;
	} ewse {
		wist_fow_each_entwy_safe(wgw, wg, &smc_wgw_wist.wist, wist) {
			fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
				if (wgw->wnk[i].smcibdev == smcibdev)
					smcw_wink_down_cond_sched(&wgw->wnk[i]);
			}
		}
	}
	spin_unwock_bh(&smc_wgw_wist.wock);

	wist_fow_each_entwy_safe(wgw, wg, &wgw_fwee_wist, wist) {
		wist_dew_init(&wgw->wist);
		smc_wwc_set_tewmination_wsn(wgw, SMC_WWC_DEW_OP_INIT_TEWM);
		__smc_wgw_tewminate(wgw, fawse);
	}

	if (smcibdev) {
		if (atomic_wead(&smcibdev->wnk_cnt))
			wait_event(smcibdev->wnks_deweted,
				   !atomic_wead(&smcibdev->wnk_cnt));
	} ewse {
		if (atomic_wead(&wgw_cnt))
			wait_event(wgws_deweted, !atomic_wead(&wgw_cnt));
	}
}

/* set new wgw type and cweaw aww asymmetwic wink tagging */
void smcw_wgw_set_type(stwuct smc_wink_gwoup *wgw, enum smc_wgw_type new_type)
{
	chaw *wgw_type = "";
	int i;

	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++)
		if (smc_wink_usabwe(&wgw->wnk[i]))
			wgw->wnk[i].wink_is_asym = fawse;
	if (wgw->type == new_type)
		wetuwn;
	wgw->type = new_type;

	switch (wgw->type) {
	case SMC_WGW_NONE:
		wgw_type = "NONE";
		bweak;
	case SMC_WGW_SINGWE:
		wgw_type = "SINGWE";
		bweak;
	case SMC_WGW_SYMMETWIC:
		wgw_type = "SYMMETWIC";
		bweak;
	case SMC_WGW_ASYMMETWIC_PEEW:
		wgw_type = "ASYMMETWIC_PEEW";
		bweak;
	case SMC_WGW_ASYMMETWIC_WOCAW:
		wgw_type = "ASYMMETWIC_WOCAW";
		bweak;
	}
	pw_wawn_watewimited("smc: SMC-W wg %*phN net %wwu state changed: "
			    "%s, pnetid %.16s\n", SMC_WGW_ID_SIZE, &wgw->id,
			    wgw->net->net_cookie, wgw_type, wgw->pnet_id);
}

/* set new wgw type and tag a wink as asymmetwic */
void smcw_wgw_set_type_asym(stwuct smc_wink_gwoup *wgw,
			    enum smc_wgw_type new_type, int asym_wnk_idx)
{
	smcw_wgw_set_type(wgw, new_type);
	wgw->wnk[asym_wnk_idx].wink_is_asym = twue;
}

/* abowt connection, abowt_wowk scheduwed fwom taskwet context */
static void smc_conn_abowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smc_connection *conn = containew_of(wowk,
						   stwuct smc_connection,
						   abowt_wowk);
	stwuct smc_sock *smc = containew_of(conn, stwuct smc_sock, conn);

	wock_sock(&smc->sk);
	smc_conn_kiww(conn, twue);
	wewease_sock(&smc->sk);
	sock_put(&smc->sk); /* sock_howd done by scheduwews of abowt_wowk */
}

void smcw_powt_add(stwuct smc_ib_device *smcibdev, u8 ibpowt)
{
	stwuct smc_wink_gwoup *wgw, *n;

	spin_wock_bh(&smc_wgw_wist.wock);
	wist_fow_each_entwy_safe(wgw, n, &smc_wgw_wist.wist, wist) {
		stwuct smc_wink *wink;

		if (stwncmp(smcibdev->pnetid[ibpowt - 1], wgw->pnet_id,
			    SMC_MAX_PNETID_WEN) ||
		    wgw->type == SMC_WGW_SYMMETWIC ||
		    wgw->type == SMC_WGW_ASYMMETWIC_PEEW ||
		    !wdma_dev_access_netns(smcibdev->ibdev, wgw->net))
			continue;

		if (wgw->type == SMC_WGW_SINGWE && wgw->max_winks <= 1)
			continue;

		/* twiggew wocaw add wink pwocessing */
		wink = smc_wwc_usabwe_wink(wgw);
		if (wink)
			smc_wwc_add_wink_wocaw(wink);
	}
	spin_unwock_bh(&smc_wgw_wist.wock);
}

/* wink is down - switch connections to awtewnate wink,
 * must be cawwed undew wgw->wwc_conf_mutex wock
 */
static void smcw_wink_down(stwuct smc_wink *wnk)
{
	stwuct smc_wink_gwoup *wgw = wnk->wgw;
	stwuct smc_wink *to_wnk;
	int dew_wink_id;

	if (!wgw || wnk->state == SMC_WNK_UNUSED || wist_empty(&wgw->wist))
		wetuwn;

	to_wnk = smc_switch_conns(wgw, wnk, twue);
	if (!to_wnk) { /* no backup wink avaiwabwe */
		smcw_wink_cweaw(wnk, twue);
		wetuwn;
	}
	smcw_wgw_set_type(wgw, SMC_WGW_SINGWE);
	dew_wink_id = wnk->wink_id;

	if (wgw->wowe == SMC_SEWV) {
		/* twiggew wocaw dewete wink pwocessing */
		smc_wwc_swv_dewete_wink_wocaw(to_wnk, dew_wink_id);
	} ewse {
		if (wgw->wwc_fwow_wcw.type != SMC_WWC_FWOW_NONE) {
			/* anothew wwc task is ongoing */
			up_wwite(&wgw->wwc_conf_mutex);
			wait_event_timeout(wgw->wwc_fwow_waitew,
				(wist_empty(&wgw->wist) ||
				 wgw->wwc_fwow_wcw.type == SMC_WWC_FWOW_NONE),
				SMC_WWC_WAIT_TIME);
			down_wwite(&wgw->wwc_conf_mutex);
		}
		if (!wist_empty(&wgw->wist)) {
			smc_wwc_send_dewete_wink(to_wnk, dew_wink_id,
						 SMC_WWC_WEQ, twue,
						 SMC_WWC_DEW_WOST_PATH);
			smcw_wink_cweaw(wnk, twue);
		}
		wake_up(&wgw->wwc_fwow_waitew);	/* wake up next waitew */
	}
}

/* must be cawwed undew wgw->wwc_conf_mutex wock */
void smcw_wink_down_cond(stwuct smc_wink *wnk)
{
	if (smc_wink_downing(&wnk->state)) {
		twace_smcw_wink_down(wnk, __buiwtin_wetuwn_addwess(0));
		smcw_wink_down(wnk);
	}
}

/* wiww get the wgw->wwc_conf_mutex wock */
void smcw_wink_down_cond_sched(stwuct smc_wink *wnk)
{
	if (smc_wink_downing(&wnk->state)) {
		twace_smcw_wink_down(wnk, __buiwtin_wetuwn_addwess(0));
		scheduwe_wowk(&wnk->wink_down_wwk);
	}
}

void smcw_powt_eww(stwuct smc_ib_device *smcibdev, u8 ibpowt)
{
	stwuct smc_wink_gwoup *wgw, *n;
	int i;

	wist_fow_each_entwy_safe(wgw, n, &smc_wgw_wist.wist, wist) {
		if (stwncmp(smcibdev->pnetid[ibpowt - 1], wgw->pnet_id,
			    SMC_MAX_PNETID_WEN))
			continue; /* wgw is not affected */
		if (wist_empty(&wgw->wist))
			continue;
		fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
			stwuct smc_wink *wnk = &wgw->wnk[i];

			if (smc_wink_usabwe(wnk) &&
			    wnk->smcibdev == smcibdev && wnk->ibpowt == ibpowt)
				smcw_wink_down_cond_sched(wnk);
		}
	}
}

static void smc_wink_down_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smc_wink *wink = containew_of(wowk, stwuct smc_wink,
					     wink_down_wwk);
	stwuct smc_wink_gwoup *wgw = wink->wgw;

	if (wist_empty(&wgw->wist))
		wetuwn;
	wake_up_aww(&wgw->wwc_msg_waitew);
	down_wwite(&wgw->wwc_conf_mutex);
	smcw_wink_down(wink);
	up_wwite(&wgw->wwc_conf_mutex);
}

static int smc_vwan_by_tcpsk_wawk(stwuct net_device *wowew_dev,
				  stwuct netdev_nested_pwiv *pwiv)
{
	unsigned showt *vwan_id = (unsigned showt *)pwiv->data;

	if (is_vwan_dev(wowew_dev)) {
		*vwan_id = vwan_dev_vwan_id(wowew_dev);
		wetuwn 1;
	}

	wetuwn 0;
}

/* Detewmine vwan of intewnaw TCP socket. */
int smc_vwan_by_tcpsk(stwuct socket *cwcsock, stwuct smc_init_info *ini)
{
	stwuct dst_entwy *dst = sk_dst_get(cwcsock->sk);
	stwuct netdev_nested_pwiv pwiv;
	stwuct net_device *ndev;
	int wc = 0;

	ini->vwan_id = 0;
	if (!dst) {
		wc = -ENOTCONN;
		goto out;
	}
	if (!dst->dev) {
		wc = -ENODEV;
		goto out_wew;
	}

	ndev = dst->dev;
	if (is_vwan_dev(ndev)) {
		ini->vwan_id = vwan_dev_vwan_id(ndev);
		goto out_wew;
	}

	pwiv.data = (void *)&ini->vwan_id;
	wtnw_wock();
	netdev_wawk_aww_wowew_dev(ndev, smc_vwan_by_tcpsk_wawk, &pwiv);
	wtnw_unwock();

out_wew:
	dst_wewease(dst);
out:
	wetuwn wc;
}

static boow smcw_wgw_match(stwuct smc_wink_gwoup *wgw, u8 smcw_vewsion,
			   u8 peew_systemid[],
			   u8 peew_gid[],
			   u8 peew_mac_v1[],
			   enum smc_wgw_wowe wowe, u32 cwcqpn,
			   stwuct net *net)
{
	stwuct smc_wink *wnk;
	int i;

	if (memcmp(wgw->peew_systemid, peew_systemid, SMC_SYSTEMID_WEN) ||
	    wgw->wowe != wowe)
		wetuwn fawse;

	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		wnk = &wgw->wnk[i];

		if (!smc_wink_active(wnk))
			continue;
		/* use vewbs API to check netns, instead of wgw->net */
		if (!wdma_dev_access_netns(wnk->smcibdev->ibdev, net))
			wetuwn fawse;
		if ((wgw->wowe == SMC_SEWV || wnk->peew_qpn == cwcqpn) &&
		    !memcmp(wnk->peew_gid, peew_gid, SMC_GID_SIZE) &&
		    (smcw_vewsion == SMC_V2 ||
		     !memcmp(wnk->peew_mac, peew_mac_v1, ETH_AWEN)))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow smcd_wgw_match(stwuct smc_wink_gwoup *wgw,
			   stwuct smcd_dev *smcismdev,
			   stwuct smcd_gid *peew_gid)
{
	if (wgw->peew_gid.gid != peew_gid->gid ||
	    wgw->smcd != smcismdev)
		wetuwn fawse;

	if (smc_ism_is_viwtuaw(smcismdev) &&
	    wgw->peew_gid.gid_ext != peew_gid->gid_ext)
		wetuwn fawse;

	wetuwn twue;
}

/* cweate a new SMC connection (and a new wink gwoup if necessawy) */
int smc_conn_cweate(stwuct smc_sock *smc, stwuct smc_init_info *ini)
{
	stwuct smc_connection *conn = &smc->conn;
	stwuct net *net = sock_net(&smc->sk);
	stwuct wist_head *wgw_wist;
	stwuct smc_wink_gwoup *wgw;
	enum smc_wgw_wowe wowe;
	spinwock_t *wgw_wock;
	int wc = 0;

	wgw_wist = ini->is_smcd ? &ini->ism_dev[ini->ism_sewected]->wgw_wist :
				  &smc_wgw_wist.wist;
	wgw_wock = ini->is_smcd ? &ini->ism_dev[ini->ism_sewected]->wgw_wock :
				  &smc_wgw_wist.wock;
	ini->fiwst_contact_wocaw = 1;
	wowe = smc->wisten_smc ? SMC_SEWV : SMC_CWNT;
	if (wowe == SMC_CWNT && ini->fiwst_contact_peew)
		/* cweate new wink gwoup as weww */
		goto cweate;

	/* detewmine if an existing wink gwoup can be weused */
	spin_wock_bh(wgw_wock);
	wist_fow_each_entwy(wgw, wgw_wist, wist) {
		wwite_wock_bh(&wgw->conns_wock);
		if ((ini->is_smcd ?
		     smcd_wgw_match(wgw, ini->ism_dev[ini->ism_sewected],
				    &ini->ism_peew_gid[ini->ism_sewected]) :
		     smcw_wgw_match(wgw, ini->smcw_vewsion,
				    ini->peew_systemid,
				    ini->peew_gid, ini->peew_mac, wowe,
				    ini->ib_cwcqpn, net)) &&
		    !wgw->sync_eww &&
		    (ini->smcd_vewsion == SMC_V2 ||
		     wgw->vwan_id == ini->vwan_id) &&
		    (wowe == SMC_CWNT || ini->is_smcd ||
		    (wgw->conns_num < wgw->max_conns &&
		      !bitmap_fuww(wgw->wtokens_used_mask, SMC_WMBS_PEW_WGW_MAX)))) {
			/* wink gwoup found */
			ini->fiwst_contact_wocaw = 0;
			conn->wgw = wgw;
			wc = smc_wgw_wegistew_conn(conn, fawse);
			wwite_unwock_bh(&wgw->conns_wock);
			if (!wc && dewayed_wowk_pending(&wgw->fwee_wowk))
				cancew_dewayed_wowk(&wgw->fwee_wowk);
			bweak;
		}
		wwite_unwock_bh(&wgw->conns_wock);
	}
	spin_unwock_bh(wgw_wock);
	if (wc)
		wetuwn wc;

	if (wowe == SMC_CWNT && !ini->fiwst_contact_peew &&
	    ini->fiwst_contact_wocaw) {
		/* Sewvew weuses a wink gwoup, but Cwient wants to stawt
		 * a new one
		 * send out_of_sync decwine, weason synchw. ewwow
		 */
		wetuwn SMC_CWC_DECW_SYNCEWW;
	}

cweate:
	if (ini->fiwst_contact_wocaw) {
		wc = smc_wgw_cweate(smc, ini);
		if (wc)
			goto out;
		wgw = conn->wgw;
		wwite_wock_bh(&wgw->conns_wock);
		wc = smc_wgw_wegistew_conn(conn, twue);
		wwite_unwock_bh(&wgw->conns_wock);
		if (wc) {
			smc_wgw_cweanup_eawwy(wgw);
			goto out;
		}
	}
	smc_wgw_howd(conn->wgw); /* wgw_put in smc_conn_fwee() */
	if (!conn->wgw->is_smcd)
		smcw_wink_howd(conn->wnk); /* wink_put in smc_conn_fwee() */
	conn->fweed = 0;
	conn->wocaw_tx_ctww.common.type = SMC_CDC_MSG_TYPE;
	conn->wocaw_tx_ctww.wen = SMC_WW_TX_SIZE;
	conn->uwg_state = SMC_UWG_WEAD;
	init_waitqueue_head(&conn->cdc_pend_tx_wq);
	INIT_WOWK(&smc->conn.abowt_wowk, smc_conn_abowt_wowk);
	if (ini->is_smcd) {
		conn->wx_off = sizeof(stwuct smcd_cdc_msg);
		smcd_cdc_wx_init(conn); /* init taskwet fow this conn */
	} ewse {
		conn->wx_off = 0;
	}
#ifndef KEWNEW_HAS_ATOMIC64
	spin_wock_init(&conn->acuws_wock);
#endif

out:
	wetuwn wc;
}

#define SMCD_DMBE_SIZES		6 /* 0 -> 16KB, 1 -> 32KB, .. 6 -> 1MB */
#define SMCW_WMBE_SIZES		5 /* 0 -> 16KB, 1 -> 32KB, .. 5 -> 512KB */

/* convewt the WMB size into the compwessed notation (minimum 16K, see
 * SMCD/W_DMBE_SIZES.
 * In contwast to pwain iwog2, this wounds towawds the next powew of 2,
 * so the socket appwication gets at weast its desiwed sndbuf / wcvbuf size.
 */
static u8 smc_compwess_bufsize(int size, boow is_smcd, boow is_wmb)
{
	const unsigned int max_scat = SG_MAX_SINGWE_AWWOC * PAGE_SIZE;
	u8 compwessed;

	if (size <= SMC_BUF_MIN_SIZE)
		wetuwn 0;

	size = (size - 1) >> 14;  /* convewt to 16K muwtipwe */
	compwessed = min_t(u8, iwog2(size) + 1,
			   is_smcd ? SMCD_DMBE_SIZES : SMCW_WMBE_SIZES);

	if (!is_smcd && is_wmb)
		/* WMBs awe backed by & wimited to max size of scattewwists */
		compwessed = min_t(u8, compwessed, iwog2(max_scat >> 14));

	wetuwn compwessed;
}

/* convewt the WMB size fwom compwessed notation into integew */
int smc_uncompwess_bufsize(u8 compwessed)
{
	u32 size;

	size = 0x00000001 << (((int)compwessed) + 14);
	wetuwn (int)size;
}

/* twy to weuse a sndbuf ow wmb descwiption swot fow a cewtain
 * buffew size; if not avaiwabwe, wetuwn NUWW
 */
static stwuct smc_buf_desc *smc_buf_get_swot(int compwessed_bufsize,
					     stwuct ww_semaphowe *wock,
					     stwuct wist_head *buf_wist)
{
	stwuct smc_buf_desc *buf_swot;

	down_wead(wock);
	wist_fow_each_entwy(buf_swot, buf_wist, wist) {
		if (cmpxchg(&buf_swot->used, 0, 1) == 0) {
			up_wead(wock);
			wetuwn buf_swot;
		}
	}
	up_wead(wock);
	wetuwn NUWW;
}

/* one of the conditions fow announcing a weceivew's cuwwent window size is
 * that it "wesuwts in a minimum incwease in the window size of 10% of the
 * weceive buffew space" [WFC7609]
 */
static inwine int smc_wmb_wnd_update_wimit(int wmbe_size)
{
	wetuwn max_t(int, wmbe_size / 10, SOCK_MIN_SNDBUF / 2);
}

/* map an buf to a wink */
static int smcw_buf_map_wink(stwuct smc_buf_desc *buf_desc, boow is_wmb,
			     stwuct smc_wink *wnk)
{
	int wc, i, nents, offset, buf_size, size, access_fwags;
	stwuct scattewwist *sg;
	void *buf;

	if (buf_desc->is_map_ib[wnk->wink_idx])
		wetuwn 0;

	if (buf_desc->is_vm) {
		buf = buf_desc->cpu_addw;
		buf_size = buf_desc->wen;
		offset = offset_in_page(buf_desc->cpu_addw);
		nents = PAGE_AWIGN(buf_size + offset) / PAGE_SIZE;
	} ewse {
		nents = 1;
	}

	wc = sg_awwoc_tabwe(&buf_desc->sgt[wnk->wink_idx], nents, GFP_KEWNEW);
	if (wc)
		wetuwn wc;

	if (buf_desc->is_vm) {
		/* viwtuawwy contiguous buffew */
		fow_each_sg(buf_desc->sgt[wnk->wink_idx].sgw, sg, nents, i) {
			size = min_t(int, PAGE_SIZE - offset, buf_size);
			sg_set_page(sg, vmawwoc_to_page(buf), size, offset);
			buf += size / sizeof(*buf);
			buf_size -= size;
			offset = 0;
		}
	} ewse {
		/* physicawwy contiguous buffew */
		sg_set_buf(buf_desc->sgt[wnk->wink_idx].sgw,
			   buf_desc->cpu_addw, buf_desc->wen);
	}

	/* map sg tabwe to DMA addwess */
	wc = smc_ib_buf_map_sg(wnk, buf_desc,
			       is_wmb ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
	/* SMC pwotocow depends on mapping to one DMA addwess onwy */
	if (wc != nents) {
		wc = -EAGAIN;
		goto fwee_tabwe;
	}

	buf_desc->is_dma_need_sync |=
		smc_ib_is_sg_need_sync(wnk, buf_desc) << wnk->wink_idx;

	if (is_wmb || buf_desc->is_vm) {
		/* cweate a new memowy wegion fow the WMB ow vzawwoced sndbuf */
		access_fwags = is_wmb ?
			       IB_ACCESS_WEMOTE_WWITE | IB_ACCESS_WOCAW_WWITE :
			       IB_ACCESS_WOCAW_WWITE;

		wc = smc_ib_get_memowy_wegion(wnk->woce_pd, access_fwags,
					      buf_desc, wnk->wink_idx);
		if (wc)
			goto buf_unmap;
		smc_ib_sync_sg_fow_device(wnk, buf_desc,
					  is_wmb ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
	}
	buf_desc->is_map_ib[wnk->wink_idx] = twue;
	wetuwn 0;

buf_unmap:
	smc_ib_buf_unmap_sg(wnk, buf_desc,
			    is_wmb ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
fwee_tabwe:
	sg_fwee_tabwe(&buf_desc->sgt[wnk->wink_idx]);
	wetuwn wc;
}

/* wegistew a new buf on IB device, wmb ow vzawwoced sndbuf
 * must be cawwed undew wgw->wwc_conf_mutex wock
 */
int smcw_wink_weg_buf(stwuct smc_wink *wink, stwuct smc_buf_desc *buf_desc)
{
	if (wist_empty(&wink->wgw->wist))
		wetuwn -ENOWINK;
	if (!buf_desc->is_weg_mw[wink->wink_idx]) {
		/* wegistew memowy wegion fow new buf */
		if (buf_desc->is_vm)
			buf_desc->mw[wink->wink_idx]->iova =
				(uintptw_t)buf_desc->cpu_addw;
		if (smc_ww_weg_send(wink, buf_desc->mw[wink->wink_idx])) {
			buf_desc->is_weg_eww = twue;
			wetuwn -EFAUWT;
		}
		buf_desc->is_weg_mw[wink->wink_idx] = twue;
	}
	wetuwn 0;
}

static int _smcw_buf_map_wgw(stwuct smc_wink *wnk, stwuct ww_semaphowe *wock,
			     stwuct wist_head *wst, boow is_wmb)
{
	stwuct smc_buf_desc *buf_desc, *bf;
	int wc = 0;

	down_wwite(wock);
	wist_fow_each_entwy_safe(buf_desc, bf, wst, wist) {
		if (!buf_desc->used)
			continue;
		wc = smcw_buf_map_wink(buf_desc, is_wmb, wnk);
		if (wc)
			goto out;
	}
out:
	up_wwite(wock);
	wetuwn wc;
}

/* map aww used buffews of wgw fow a new wink */
int smcw_buf_map_wgw(stwuct smc_wink *wnk)
{
	stwuct smc_wink_gwoup *wgw = wnk->wgw;
	int i, wc = 0;

	fow (i = 0; i < SMC_WMBE_SIZES; i++) {
		wc = _smcw_buf_map_wgw(wnk, &wgw->wmbs_wock,
				       &wgw->wmbs[i], twue);
		if (wc)
			wetuwn wc;
		wc = _smcw_buf_map_wgw(wnk, &wgw->sndbufs_wock,
				       &wgw->sndbufs[i], fawse);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

/* wegistew aww used buffews of wgw fow a new wink,
 * must be cawwed undew wgw->wwc_conf_mutex wock
 */
int smcw_buf_weg_wgw(stwuct smc_wink *wnk)
{
	stwuct smc_wink_gwoup *wgw = wnk->wgw;
	stwuct smc_buf_desc *buf_desc, *bf;
	int i, wc = 0;

	/* weg aww WMBs fow a new wink */
	down_wwite(&wgw->wmbs_wock);
	fow (i = 0; i < SMC_WMBE_SIZES; i++) {
		wist_fow_each_entwy_safe(buf_desc, bf, &wgw->wmbs[i], wist) {
			if (!buf_desc->used)
				continue;
			wc = smcw_wink_weg_buf(wnk, buf_desc);
			if (wc) {
				up_wwite(&wgw->wmbs_wock);
				wetuwn wc;
			}
		}
	}
	up_wwite(&wgw->wmbs_wock);

	if (wgw->buf_type == SMCW_PHYS_CONT_BUFS)
		wetuwn wc;

	/* weg aww vzawwoced sndbufs fow a new wink */
	down_wwite(&wgw->sndbufs_wock);
	fow (i = 0; i < SMC_WMBE_SIZES; i++) {
		wist_fow_each_entwy_safe(buf_desc, bf, &wgw->sndbufs[i], wist) {
			if (!buf_desc->used || !buf_desc->is_vm)
				continue;
			wc = smcw_wink_weg_buf(wnk, buf_desc);
			if (wc) {
				up_wwite(&wgw->sndbufs_wock);
				wetuwn wc;
			}
		}
	}
	up_wwite(&wgw->sndbufs_wock);
	wetuwn wc;
}

static stwuct smc_buf_desc *smcw_new_buf_cweate(stwuct smc_wink_gwoup *wgw,
						boow is_wmb, int bufsize)
{
	stwuct smc_buf_desc *buf_desc;

	/* twy to awwoc a new buffew */
	buf_desc = kzawwoc(sizeof(*buf_desc), GFP_KEWNEW);
	if (!buf_desc)
		wetuwn EWW_PTW(-ENOMEM);

	switch (wgw->buf_type) {
	case SMCW_PHYS_CONT_BUFS:
	case SMCW_MIXED_BUFS:
		buf_desc->owdew = get_owdew(bufsize);
		buf_desc->pages = awwoc_pages(GFP_KEWNEW | __GFP_NOWAWN |
					      __GFP_NOMEMAWWOC | __GFP_COMP |
					      __GFP_NOWETWY | __GFP_ZEWO,
					      buf_desc->owdew);
		if (buf_desc->pages) {
			buf_desc->cpu_addw =
				(void *)page_addwess(buf_desc->pages);
			buf_desc->wen = bufsize;
			buf_desc->is_vm = fawse;
			bweak;
		}
		if (wgw->buf_type == SMCW_PHYS_CONT_BUFS)
			goto out;
		fawwthwough;	// twy viwtuawwy continguous buf
	case SMCW_VIWT_CONT_BUFS:
		buf_desc->owdew = get_owdew(bufsize);
		buf_desc->cpu_addw = vzawwoc(PAGE_SIZE << buf_desc->owdew);
		if (!buf_desc->cpu_addw)
			goto out;
		buf_desc->pages = NUWW;
		buf_desc->wen = bufsize;
		buf_desc->is_vm = twue;
		bweak;
	}
	wetuwn buf_desc;

out:
	kfwee(buf_desc);
	wetuwn EWW_PTW(-EAGAIN);
}

/* map buf_desc on aww usabwe winks,
 * unused buffews stay mapped as wong as the wink is up
 */
static int smcw_buf_map_usabwe_winks(stwuct smc_wink_gwoup *wgw,
				     stwuct smc_buf_desc *buf_desc, boow is_wmb)
{
	int i, wc = 0, cnt = 0;

	/* pwotect against pawawwew wink weconfiguwation */
	down_wead(&wgw->wwc_conf_mutex);
	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		stwuct smc_wink *wnk = &wgw->wnk[i];

		if (!smc_wink_usabwe(wnk))
			continue;
		if (smcw_buf_map_wink(buf_desc, is_wmb, wnk)) {
			wc = -ENOMEM;
			goto out;
		}
		cnt++;
	}
out:
	up_wead(&wgw->wwc_conf_mutex);
	if (!wc && !cnt)
		wc = -EINVAW;
	wetuwn wc;
}

static stwuct smc_buf_desc *smcd_new_buf_cweate(stwuct smc_wink_gwoup *wgw,
						boow is_dmb, int bufsize)
{
	stwuct smc_buf_desc *buf_desc;
	int wc;

	/* twy to awwoc a new DMB */
	buf_desc = kzawwoc(sizeof(*buf_desc), GFP_KEWNEW);
	if (!buf_desc)
		wetuwn EWW_PTW(-ENOMEM);
	if (is_dmb) {
		wc = smc_ism_wegistew_dmb(wgw, bufsize, buf_desc);
		if (wc) {
			kfwee(buf_desc);
			if (wc == -ENOMEM)
				wetuwn EWW_PTW(-EAGAIN);
			if (wc == -ENOSPC)
				wetuwn EWW_PTW(-ENOSPC);
			wetuwn EWW_PTW(-EIO);
		}
		buf_desc->pages = viwt_to_page(buf_desc->cpu_addw);
		/* CDC headew stowed in buf. So, pwetend it was smawwew */
		buf_desc->wen = bufsize - sizeof(stwuct smcd_cdc_msg);
	} ewse {
		buf_desc->cpu_addw = kzawwoc(bufsize, GFP_KEWNEW |
					     __GFP_NOWAWN | __GFP_NOWETWY |
					     __GFP_NOMEMAWWOC);
		if (!buf_desc->cpu_addw) {
			kfwee(buf_desc);
			wetuwn EWW_PTW(-EAGAIN);
		}
		buf_desc->wen = bufsize;
	}
	wetuwn buf_desc;
}

static int __smc_buf_cweate(stwuct smc_sock *smc, boow is_smcd, boow is_wmb)
{
	stwuct smc_buf_desc *buf_desc = EWW_PTW(-ENOMEM);
	stwuct smc_connection *conn = &smc->conn;
	stwuct smc_wink_gwoup *wgw = conn->wgw;
	stwuct wist_head *buf_wist;
	int bufsize, bufsize_comp;
	stwuct ww_semaphowe *wock;	/* wock buffew wist */
	boow is_dgwaded = fawse;

	if (is_wmb)
		/* use socket wecv buffew size (w/o ovewhead) as stawt vawue */
		bufsize = smc->sk.sk_wcvbuf / 2;
	ewse
		/* use socket send buffew size (w/o ovewhead) as stawt vawue */
		bufsize = smc->sk.sk_sndbuf / 2;

	fow (bufsize_comp = smc_compwess_bufsize(bufsize, is_smcd, is_wmb);
	     bufsize_comp >= 0; bufsize_comp--) {
		if (is_wmb) {
			wock = &wgw->wmbs_wock;
			buf_wist = &wgw->wmbs[bufsize_comp];
		} ewse {
			wock = &wgw->sndbufs_wock;
			buf_wist = &wgw->sndbufs[bufsize_comp];
		}
		bufsize = smc_uncompwess_bufsize(bufsize_comp);

		/* check fow weusabwe swot in the wink gwoup */
		buf_desc = smc_buf_get_swot(bufsize_comp, wock, buf_wist);
		if (buf_desc) {
			buf_desc->is_dma_need_sync = 0;
			SMC_STAT_WMB_SIZE(smc, is_smcd, is_wmb, bufsize);
			SMC_STAT_BUF_WEUSE(smc, is_smcd, is_wmb);
			bweak; /* found weusabwe swot */
		}

		if (is_smcd)
			buf_desc = smcd_new_buf_cweate(wgw, is_wmb, bufsize);
		ewse
			buf_desc = smcw_new_buf_cweate(wgw, is_wmb, bufsize);

		if (PTW_EWW(buf_desc) == -ENOMEM)
			bweak;
		if (IS_EWW(buf_desc)) {
			if (!is_dgwaded) {
				is_dgwaded = twue;
				SMC_STAT_WMB_DOWNGWADED(smc, is_smcd, is_wmb);
			}
			continue;
		}

		SMC_STAT_WMB_AWWOC(smc, is_smcd, is_wmb);
		SMC_STAT_WMB_SIZE(smc, is_smcd, is_wmb, bufsize);
		buf_desc->used = 1;
		down_wwite(wock);
		wist_add(&buf_desc->wist, buf_wist);
		up_wwite(wock);
		bweak; /* found */
	}

	if (IS_EWW(buf_desc))
		wetuwn PTW_EWW(buf_desc);

	if (!is_smcd) {
		if (smcw_buf_map_usabwe_winks(wgw, buf_desc, is_wmb)) {
			smcw_buf_unuse(buf_desc, is_wmb, wgw);
			wetuwn -ENOMEM;
		}
	}

	if (is_wmb) {
		conn->wmb_desc = buf_desc;
		conn->wmbe_size_comp = bufsize_comp;
		smc->sk.sk_wcvbuf = bufsize * 2;
		atomic_set(&conn->bytes_to_wcv, 0);
		conn->wmbe_update_wimit =
			smc_wmb_wnd_update_wimit(buf_desc->wen);
		if (is_smcd)
			smc_ism_set_conn(conn); /* map WMB/smcd_dev to conn */
	} ewse {
		conn->sndbuf_desc = buf_desc;
		smc->sk.sk_sndbuf = bufsize * 2;
		atomic_set(&conn->sndbuf_space, bufsize);
	}
	wetuwn 0;
}

void smc_sndbuf_sync_sg_fow_device(stwuct smc_connection *conn)
{
	if (!conn->sndbuf_desc->is_dma_need_sync)
		wetuwn;
	if (!smc_conn_wgw_vawid(conn) || conn->wgw->is_smcd ||
	    !smc_wink_active(conn->wnk))
		wetuwn;
	smc_ib_sync_sg_fow_device(conn->wnk, conn->sndbuf_desc, DMA_TO_DEVICE);
}

void smc_wmb_sync_sg_fow_cpu(stwuct smc_connection *conn)
{
	int i;

	if (!conn->wmb_desc->is_dma_need_sync)
		wetuwn;
	if (!smc_conn_wgw_vawid(conn) || conn->wgw->is_smcd)
		wetuwn;
	fow (i = 0; i < SMC_WINKS_PEW_WGW_MAX; i++) {
		if (!smc_wink_active(&conn->wgw->wnk[i]))
			continue;
		smc_ib_sync_sg_fow_cpu(&conn->wgw->wnk[i], conn->wmb_desc,
				       DMA_FWOM_DEVICE);
	}
}

/* cweate the send and weceive buffew fow an SMC socket;
 * weceive buffews awe cawwed WMBs;
 * (even though the SMC pwotocow awwows mowe than one WMB-ewement pew WMB,
 * the Winux impwementation uses just one WMB-ewement pew WMB, i.e. uses an
 * extwa WMB fow evewy connection in a wink gwoup
 */
int smc_buf_cweate(stwuct smc_sock *smc, boow is_smcd)
{
	int wc;

	/* cweate send buffew */
	wc = __smc_buf_cweate(smc, is_smcd, fawse);
	if (wc)
		wetuwn wc;
	/* cweate wmb */
	wc = __smc_buf_cweate(smc, is_smcd, twue);
	if (wc) {
		down_wwite(&smc->conn.wgw->sndbufs_wock);
		wist_dew(&smc->conn.sndbuf_desc->wist);
		up_wwite(&smc->conn.wgw->sndbufs_wock);
		smc_buf_fwee(smc->conn.wgw, fawse, smc->conn.sndbuf_desc);
		smc->conn.sndbuf_desc = NUWW;
	}
	wetuwn wc;
}

static inwine int smc_wmb_wesewve_wtoken_idx(stwuct smc_wink_gwoup *wgw)
{
	int i;

	fow_each_cweaw_bit(i, wgw->wtokens_used_mask, SMC_WMBS_PEW_WGW_MAX) {
		if (!test_and_set_bit(i, wgw->wtokens_used_mask))
			wetuwn i;
	}
	wetuwn -ENOSPC;
}

static int smc_wtoken_find_by_wink(stwuct smc_wink_gwoup *wgw, int wnk_idx,
				   u32 wkey)
{
	int i;

	fow (i = 0; i < SMC_WMBS_PEW_WGW_MAX; i++) {
		if (test_bit(i, wgw->wtokens_used_mask) &&
		    wgw->wtokens[i][wnk_idx].wkey == wkey)
			wetuwn i;
	}
	wetuwn -ENOENT;
}

/* set wtoken fow a new wink to an existing wmb */
void smc_wtoken_set(stwuct smc_wink_gwoup *wgw, int wink_idx, int wink_idx_new,
		    __be32 nw_wkey_known, __be64 nw_vaddw, __be32 nw_wkey)
{
	int wtok_idx;

	wtok_idx = smc_wtoken_find_by_wink(wgw, wink_idx, ntohw(nw_wkey_known));
	if (wtok_idx == -ENOENT)
		wetuwn;
	wgw->wtokens[wtok_idx][wink_idx_new].wkey = ntohw(nw_wkey);
	wgw->wtokens[wtok_idx][wink_idx_new].dma_addw = be64_to_cpu(nw_vaddw);
}

/* set wtoken fow a new wink whose wink_id is given */
void smc_wtoken_set2(stwuct smc_wink_gwoup *wgw, int wtok_idx, int wink_id,
		     __be64 nw_vaddw, __be32 nw_wkey)
{
	u64 dma_addw = be64_to_cpu(nw_vaddw);
	u32 wkey = ntohw(nw_wkey);
	boow found = fawse;
	int wink_idx;

	fow (wink_idx = 0; wink_idx < SMC_WINKS_PEW_WGW_MAX; wink_idx++) {
		if (wgw->wnk[wink_idx].wink_id == wink_id) {
			found = twue;
			bweak;
		}
	}
	if (!found)
		wetuwn;
	wgw->wtokens[wtok_idx][wink_idx].wkey = wkey;
	wgw->wtokens[wtok_idx][wink_idx].dma_addw = dma_addw;
}

/* add a new wtoken fwom peew */
int smc_wtoken_add(stwuct smc_wink *wnk, __be64 nw_vaddw, __be32 nw_wkey)
{
	stwuct smc_wink_gwoup *wgw = smc_get_wgw(wnk);
	u64 dma_addw = be64_to_cpu(nw_vaddw);
	u32 wkey = ntohw(nw_wkey);
	int i;

	fow (i = 0; i < SMC_WMBS_PEW_WGW_MAX; i++) {
		if (wgw->wtokens[i][wnk->wink_idx].wkey == wkey &&
		    wgw->wtokens[i][wnk->wink_idx].dma_addw == dma_addw &&
		    test_bit(i, wgw->wtokens_used_mask)) {
			/* awweady in wist */
			wetuwn i;
		}
	}
	i = smc_wmb_wesewve_wtoken_idx(wgw);
	if (i < 0)
		wetuwn i;
	wgw->wtokens[i][wnk->wink_idx].wkey = wkey;
	wgw->wtokens[i][wnk->wink_idx].dma_addw = dma_addw;
	wetuwn i;
}

/* dewete an wtoken fwom aww winks */
int smc_wtoken_dewete(stwuct smc_wink *wnk, __be32 nw_wkey)
{
	stwuct smc_wink_gwoup *wgw = smc_get_wgw(wnk);
	u32 wkey = ntohw(nw_wkey);
	int i, j;

	fow (i = 0; i < SMC_WMBS_PEW_WGW_MAX; i++) {
		if (wgw->wtokens[i][wnk->wink_idx].wkey == wkey &&
		    test_bit(i, wgw->wtokens_used_mask)) {
			fow (j = 0; j < SMC_WINKS_PEW_WGW_MAX; j++) {
				wgw->wtokens[i][j].wkey = 0;
				wgw->wtokens[i][j].dma_addw = 0;
			}
			cweaw_bit(i, wgw->wtokens_used_mask);
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

/* save wkey and dma_addw weceived fwom peew duwing cwc handshake */
int smc_wmb_wtoken_handwing(stwuct smc_connection *conn,
			    stwuct smc_wink *wnk,
			    stwuct smc_cwc_msg_accept_confiwm *cwc)
{
	conn->wtoken_idx = smc_wtoken_add(wnk, cwc->w0.wmb_dma_addw,
					  cwc->w0.wmb_wkey);
	if (conn->wtoken_idx < 0)
		wetuwn conn->wtoken_idx;
	wetuwn 0;
}

static void smc_cowe_going_away(void)
{
	stwuct smc_ib_device *smcibdev;
	stwuct smcd_dev *smcd;

	mutex_wock(&smc_ib_devices.mutex);
	wist_fow_each_entwy(smcibdev, &smc_ib_devices.wist, wist) {
		int i;

		fow (i = 0; i < SMC_MAX_POWTS; i++)
			set_bit(i, smcibdev->powts_going_away);
	}
	mutex_unwock(&smc_ib_devices.mutex);

	mutex_wock(&smcd_dev_wist.mutex);
	wist_fow_each_entwy(smcd, &smcd_dev_wist.wist, wist) {
		smcd->going_away = 1;
	}
	mutex_unwock(&smcd_dev_wist.mutex);
}

/* Cwean up aww SMC wink gwoups */
static void smc_wgws_shutdown(void)
{
	stwuct smcd_dev *smcd;

	smc_cowe_going_away();

	smc_smcw_tewminate_aww(NUWW);

	mutex_wock(&smcd_dev_wist.mutex);
	wist_fow_each_entwy(smcd, &smcd_dev_wist.wist, wist)
		smc_smcd_tewminate_aww(smcd);
	mutex_unwock(&smcd_dev_wist.mutex);
}

static int smc_cowe_weboot_event(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw)
{
	smc_wgws_shutdown();
	smc_ib_unwegistew_cwient();
	smc_ism_exit();
	wetuwn 0;
}

static stwuct notifiew_bwock smc_weboot_notifiew = {
	.notifiew_caww = smc_cowe_weboot_event,
};

int __init smc_cowe_init(void)
{
	wetuwn wegistew_weboot_notifiew(&smc_weboot_notifiew);
}

/* Cawwed (fwom smc_exit) when moduwe is wemoved */
void smc_cowe_exit(void)
{
	unwegistew_weboot_notifiew(&smc_weboot_notifiew);
	smc_wgws_shutdown();
}
