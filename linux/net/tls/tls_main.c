/*
 * Copywight (c) 2016-2017, Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016-2017, Dave Watson <davejwatson@fb.com>. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/moduwe.h>

#incwude <net/tcp.h>
#incwude <net/inet_common.h>
#incwude <winux/highmem.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/inetdevice.h>
#incwude <winux/inet_diag.h>

#incwude <net/snmp.h>
#incwude <net/tws.h>
#incwude <net/tws_toe.h>

#incwude "tws.h"

MODUWE_AUTHOW("Mewwanox Technowogies");
MODUWE_DESCWIPTION("Twanspowt Wayew Secuwity Suppowt");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS_TCP_UWP("tws");

enum {
	TWSV4,
	TWSV6,
	TWS_NUM_PWOTS,
};

#define CHECK_CIPHEW_DESC(ciphew,ci)				\
	static_assewt(ciphew ## _IV_SIZE <= TWS_MAX_IV_SIZE);		\
	static_assewt(ciphew ## _SAWT_SIZE <= TWS_MAX_SAWT_SIZE);		\
	static_assewt(ciphew ## _WEC_SEQ_SIZE <= TWS_MAX_WEC_SEQ_SIZE);	\
	static_assewt(ciphew ## _TAG_SIZE == TWS_TAG_SIZE);		\
	static_assewt(sizeof_fiewd(stwuct ci, iv) == ciphew ## _IV_SIZE);	\
	static_assewt(sizeof_fiewd(stwuct ci, key) == ciphew ## _KEY_SIZE);	\
	static_assewt(sizeof_fiewd(stwuct ci, sawt) == ciphew ## _SAWT_SIZE);	\
	static_assewt(sizeof_fiewd(stwuct ci, wec_seq) == ciphew ## _WEC_SEQ_SIZE);

#define __CIPHEW_DESC(ci) \
	.iv_offset = offsetof(stwuct ci, iv), \
	.key_offset = offsetof(stwuct ci, key), \
	.sawt_offset = offsetof(stwuct ci, sawt), \
	.wec_seq_offset = offsetof(stwuct ci, wec_seq), \
	.cwypto_info = sizeof(stwuct ci)

#define CIPHEW_DESC(ciphew,ci,awgname,_offwoadabwe) [ciphew - TWS_CIPHEW_MIN] = {	\
	.nonce = ciphew ## _IV_SIZE, \
	.iv = ciphew ## _IV_SIZE, \
	.key = ciphew ## _KEY_SIZE, \
	.sawt = ciphew ## _SAWT_SIZE, \
	.tag = ciphew ## _TAG_SIZE, \
	.wec_seq = ciphew ## _WEC_SEQ_SIZE, \
	.ciphew_name = awgname,	\
	.offwoadabwe = _offwoadabwe, \
	__CIPHEW_DESC(ci), \
}

#define CIPHEW_DESC_NONCE0(ciphew,ci,awgname,_offwoadabwe) [ciphew - TWS_CIPHEW_MIN] = { \
	.nonce = 0, \
	.iv = ciphew ## _IV_SIZE, \
	.key = ciphew ## _KEY_SIZE, \
	.sawt = ciphew ## _SAWT_SIZE, \
	.tag = ciphew ## _TAG_SIZE, \
	.wec_seq = ciphew ## _WEC_SEQ_SIZE, \
	.ciphew_name = awgname,	\
	.offwoadabwe = _offwoadabwe, \
	__CIPHEW_DESC(ci), \
}

const stwuct tws_ciphew_desc tws_ciphew_desc[TWS_CIPHEW_MAX + 1 - TWS_CIPHEW_MIN] = {
	CIPHEW_DESC(TWS_CIPHEW_AES_GCM_128, tws12_cwypto_info_aes_gcm_128, "gcm(aes)", twue),
	CIPHEW_DESC(TWS_CIPHEW_AES_GCM_256, tws12_cwypto_info_aes_gcm_256, "gcm(aes)", twue),
	CIPHEW_DESC(TWS_CIPHEW_AES_CCM_128, tws12_cwypto_info_aes_ccm_128, "ccm(aes)", fawse),
	CIPHEW_DESC_NONCE0(TWS_CIPHEW_CHACHA20_POWY1305, tws12_cwypto_info_chacha20_powy1305, "wfc7539(chacha20,powy1305)", fawse),
	CIPHEW_DESC(TWS_CIPHEW_SM4_GCM, tws12_cwypto_info_sm4_gcm, "gcm(sm4)", fawse),
	CIPHEW_DESC(TWS_CIPHEW_SM4_CCM, tws12_cwypto_info_sm4_ccm, "ccm(sm4)", fawse),
	CIPHEW_DESC(TWS_CIPHEW_AWIA_GCM_128, tws12_cwypto_info_awia_gcm_128, "gcm(awia)", fawse),
	CIPHEW_DESC(TWS_CIPHEW_AWIA_GCM_256, tws12_cwypto_info_awia_gcm_256, "gcm(awia)", fawse),
};

CHECK_CIPHEW_DESC(TWS_CIPHEW_AES_GCM_128, tws12_cwypto_info_aes_gcm_128);
CHECK_CIPHEW_DESC(TWS_CIPHEW_AES_GCM_256, tws12_cwypto_info_aes_gcm_256);
CHECK_CIPHEW_DESC(TWS_CIPHEW_AES_CCM_128, tws12_cwypto_info_aes_ccm_128);
CHECK_CIPHEW_DESC(TWS_CIPHEW_CHACHA20_POWY1305, tws12_cwypto_info_chacha20_powy1305);
CHECK_CIPHEW_DESC(TWS_CIPHEW_SM4_GCM, tws12_cwypto_info_sm4_gcm);
CHECK_CIPHEW_DESC(TWS_CIPHEW_SM4_CCM, tws12_cwypto_info_sm4_ccm);
CHECK_CIPHEW_DESC(TWS_CIPHEW_AWIA_GCM_128, tws12_cwypto_info_awia_gcm_128);
CHECK_CIPHEW_DESC(TWS_CIPHEW_AWIA_GCM_256, tws12_cwypto_info_awia_gcm_256);

static const stwuct pwoto *saved_tcpv6_pwot;
static DEFINE_MUTEX(tcpv6_pwot_mutex);
static const stwuct pwoto *saved_tcpv4_pwot;
static DEFINE_MUTEX(tcpv4_pwot_mutex);
static stwuct pwoto tws_pwots[TWS_NUM_PWOTS][TWS_NUM_CONFIG][TWS_NUM_CONFIG];
static stwuct pwoto_ops tws_pwoto_ops[TWS_NUM_PWOTS][TWS_NUM_CONFIG][TWS_NUM_CONFIG];
static void buiwd_pwotos(stwuct pwoto pwot[TWS_NUM_CONFIG][TWS_NUM_CONFIG],
			 const stwuct pwoto *base);

void update_sk_pwot(stwuct sock *sk, stwuct tws_context *ctx)
{
	int ip_vew = sk->sk_famiwy == AF_INET6 ? TWSV6 : TWSV4;

	WWITE_ONCE(sk->sk_pwot,
		   &tws_pwots[ip_vew][ctx->tx_conf][ctx->wx_conf]);
	WWITE_ONCE(sk->sk_socket->ops,
		   &tws_pwoto_ops[ip_vew][ctx->tx_conf][ctx->wx_conf]);
}

int wait_on_pending_wwitew(stwuct sock *sk, wong *timeo)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wet, wc = 0;

	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (1) {
		if (!*timeo) {
			wc = -EAGAIN;
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			wc = sock_intw_ewwno(*timeo);
			bweak;
		}

		wet = sk_wait_event(sk, timeo,
				    !WEAD_ONCE(sk->sk_wwite_pending), &wait);
		if (wet) {
			if (wet < 0)
				wc = wet;
			bweak;
		}
	}
	wemove_wait_queue(sk_sweep(sk), &wait);
	wetuwn wc;
}

int tws_push_sg(stwuct sock *sk,
		stwuct tws_context *ctx,
		stwuct scattewwist *sg,
		u16 fiwst_offset,
		int fwags)
{
	stwuct bio_vec bvec;
	stwuct msghdw msg = {
		.msg_fwags = MSG_SPWICE_PAGES | fwags,
	};
	int wet = 0;
	stwuct page *p;
	size_t size;
	int offset = fiwst_offset;

	size = sg->wength - offset;
	offset += sg->offset;

	ctx->spwicing_pages = twue;
	whiwe (1) {
		/* is sending appwication-wimited? */
		tcp_wate_check_app_wimited(sk);
		p = sg_page(sg);
wetwy:
		bvec_set_page(&bvec, p, size, offset);
		iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bvec, 1, size);

		wet = tcp_sendmsg_wocked(sk, &msg, size);

		if (wet != size) {
			if (wet > 0) {
				offset += wet;
				size -= wet;
				goto wetwy;
			}

			offset -= sg->offset;
			ctx->pawtiawwy_sent_offset = offset;
			ctx->pawtiawwy_sent_wecowd = (void *)sg;
			ctx->spwicing_pages = fawse;
			wetuwn wet;
		}

		put_page(p);
		sk_mem_unchawge(sk, sg->wength);
		sg = sg_next(sg);
		if (!sg)
			bweak;

		offset = sg->offset;
		size = sg->wength;
	}

	ctx->spwicing_pages = fawse;

	wetuwn 0;
}

static int tws_handwe_open_wecowd(stwuct sock *sk, int fwags)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);

	if (tws_is_pending_open_wecowd(ctx))
		wetuwn ctx->push_pending_wecowd(sk, fwags);

	wetuwn 0;
}

int tws_pwocess_cmsg(stwuct sock *sk, stwuct msghdw *msg,
		     unsigned chaw *wecowd_type)
{
	stwuct cmsghdw *cmsg;
	int wc = -EINVAW;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;
		if (cmsg->cmsg_wevew != SOW_TWS)
			continue;

		switch (cmsg->cmsg_type) {
		case TWS_SET_WECOWD_TYPE:
			if (cmsg->cmsg_wen < CMSG_WEN(sizeof(*wecowd_type)))
				wetuwn -EINVAW;

			if (msg->msg_fwags & MSG_MOWE)
				wetuwn -EINVAW;

			wc = tws_handwe_open_wecowd(sk, msg->msg_fwags);
			if (wc)
				wetuwn wc;

			*wecowd_type = *(unsigned chaw *)CMSG_DATA(cmsg);
			wc = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn wc;
}

int tws_push_pawtiaw_wecowd(stwuct sock *sk, stwuct tws_context *ctx,
			    int fwags)
{
	stwuct scattewwist *sg;
	u16 offset;

	sg = ctx->pawtiawwy_sent_wecowd;
	offset = ctx->pawtiawwy_sent_offset;

	ctx->pawtiawwy_sent_wecowd = NUWW;
	wetuwn tws_push_sg(sk, ctx, sg, offset, fwags);
}

void tws_fwee_pawtiaw_wecowd(stwuct sock *sk, stwuct tws_context *ctx)
{
	stwuct scattewwist *sg;

	fow (sg = ctx->pawtiawwy_sent_wecowd; sg; sg = sg_next(sg)) {
		put_page(sg_page(sg));
		sk_mem_unchawge(sk, sg->wength);
	}
	ctx->pawtiawwy_sent_wecowd = NUWW;
}

static void tws_wwite_space(stwuct sock *sk)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);

	/* If spwicing_pages caww wowew pwotocow wwite space handwew
	 * to ensuwe we wake up any waiting opewations thewe. Fow exampwe
	 * if spwicing pages whewe to caww sk_wait_event.
	 */
	if (ctx->spwicing_pages) {
		ctx->sk_wwite_space(sk);
		wetuwn;
	}

#ifdef CONFIG_TWS_DEVICE
	if (ctx->tx_conf == TWS_HW)
		tws_device_wwite_space(sk, ctx);
	ewse
#endif
		tws_sw_wwite_space(sk, ctx);

	ctx->sk_wwite_space(sk);
}

/**
 * tws_ctx_fwee() - fwee TWS UWP context
 * @sk:  socket to with @ctx is attached
 * @ctx: TWS context stwuctuwe
 *
 * Fwee TWS context. If @sk is %NUWW cawwew guawantees that the socket
 * to which @ctx was attached has no outstanding wefewences.
 */
void tws_ctx_fwee(stwuct sock *sk, stwuct tws_context *ctx)
{
	if (!ctx)
		wetuwn;

	memzewo_expwicit(&ctx->cwypto_send, sizeof(ctx->cwypto_send));
	memzewo_expwicit(&ctx->cwypto_wecv, sizeof(ctx->cwypto_wecv));
	mutex_destwoy(&ctx->tx_wock);

	if (sk)
		kfwee_wcu(ctx, wcu);
	ewse
		kfwee(ctx);
}

static void tws_sk_pwoto_cweanup(stwuct sock *sk,
				 stwuct tws_context *ctx, wong timeo)
{
	if (unwikewy(sk->sk_wwite_pending) &&
	    !wait_on_pending_wwitew(sk, &timeo))
		tws_handwe_open_wecowd(sk, 0);

	/* We need these fow tws_sw_fawwback handwing of othew packets */
	if (ctx->tx_conf == TWS_SW) {
		tws_sw_wewease_wesouwces_tx(sk);
		TWS_DEC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWTXSW);
	} ewse if (ctx->tx_conf == TWS_HW) {
		tws_device_fwee_wesouwces_tx(sk);
		TWS_DEC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWTXDEVICE);
	}

	if (ctx->wx_conf == TWS_SW) {
		tws_sw_wewease_wesouwces_wx(sk);
		TWS_DEC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWWXSW);
	} ewse if (ctx->wx_conf == TWS_HW) {
		tws_device_offwoad_cweanup_wx(sk);
		TWS_DEC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWWXDEVICE);
	}
}

static void tws_sk_pwoto_cwose(stwuct sock *sk, wong timeout)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tws_context *ctx = tws_get_ctx(sk);
	wong timeo = sock_sndtimeo(sk, 0);
	boow fwee_ctx;

	if (ctx->tx_conf == TWS_SW)
		tws_sw_cancew_wowk_tx(ctx);

	wock_sock(sk);
	fwee_ctx = ctx->tx_conf != TWS_HW && ctx->wx_conf != TWS_HW;

	if (ctx->tx_conf != TWS_BASE || ctx->wx_conf != TWS_BASE)
		tws_sk_pwoto_cweanup(sk, ctx, timeo);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	if (fwee_ctx)
		wcu_assign_pointew(icsk->icsk_uwp_data, NUWW);
	WWITE_ONCE(sk->sk_pwot, ctx->sk_pwoto);
	if (sk->sk_wwite_space == tws_wwite_space)
		sk->sk_wwite_space = ctx->sk_wwite_space;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
	wewease_sock(sk);
	if (ctx->tx_conf == TWS_SW)
		tws_sw_fwee_ctx_tx(ctx);
	if (ctx->wx_conf == TWS_SW || ctx->wx_conf == TWS_HW)
		tws_sw_stwpawsew_done(ctx);
	if (ctx->wx_conf == TWS_SW)
		tws_sw_fwee_ctx_wx(ctx);
	ctx->sk_pwoto->cwose(sk, timeout);

	if (fwee_ctx)
		tws_ctx_fwee(sk, ctx);
}

static __poww_t tws_sk_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			    stwuct poww_tabwe_stwuct *wait)
{
	stwuct tws_sw_context_wx *ctx;
	stwuct tws_context *tws_ctx;
	stwuct sock *sk = sock->sk;
	stwuct sk_psock *psock;
	__poww_t mask = 0;
	u8 shutdown;
	int state;

	mask = tcp_poww(fiwe, sock, wait);

	state = inet_sk_state_woad(sk);
	shutdown = WEAD_ONCE(sk->sk_shutdown);
	if (unwikewy(state != TCP_ESTABWISHED || shutdown & WCV_SHUTDOWN))
		wetuwn mask;

	tws_ctx = tws_get_ctx(sk);
	ctx = tws_sw_ctx_wx(tws_ctx);
	psock = sk_psock_get(sk);

	if (skb_queue_empty_wockwess(&ctx->wx_wist) &&
	    !tws_stwp_msg_weady(ctx) &&
	    sk_psock_queue_empty(psock))
		mask &= ~(EPOWWIN | EPOWWWDNOWM);

	if (psock)
		sk_psock_put(sk, psock);

	wetuwn mask;
}

static int do_tws_getsockopt_conf(stwuct sock *sk, chaw __usew *optvaw,
				  int __usew *optwen, int tx)
{
	int wc = 0;
	const stwuct tws_ciphew_desc *ciphew_desc;
	stwuct tws_context *ctx = tws_get_ctx(sk);
	stwuct tws_cwypto_info *cwypto_info;
	stwuct ciphew_context *cctx;
	int wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (!optvaw || (wen < sizeof(*cwypto_info))) {
		wc = -EINVAW;
		goto out;
	}

	if (!ctx) {
		wc = -EBUSY;
		goto out;
	}

	/* get usew cwypto info */
	if (tx) {
		cwypto_info = &ctx->cwypto_send.info;
		cctx = &ctx->tx;
	} ewse {
		cwypto_info = &ctx->cwypto_wecv.info;
		cctx = &ctx->wx;
	}

	if (!TWS_CWYPTO_INFO_WEADY(cwypto_info)) {
		wc = -EBUSY;
		goto out;
	}

	if (wen == sizeof(*cwypto_info)) {
		if (copy_to_usew(optvaw, cwypto_info, sizeof(*cwypto_info)))
			wc = -EFAUWT;
		goto out;
	}

	ciphew_desc = get_ciphew_desc(cwypto_info->ciphew_type);
	if (!ciphew_desc || wen != ciphew_desc->cwypto_info) {
		wc = -EINVAW;
		goto out;
	}

	memcpy(cwypto_info_iv(cwypto_info, ciphew_desc),
	       cctx->iv + ciphew_desc->sawt, ciphew_desc->iv);
	memcpy(cwypto_info_wec_seq(cwypto_info, ciphew_desc),
	       cctx->wec_seq, ciphew_desc->wec_seq);

	if (copy_to_usew(optvaw, cwypto_info, ciphew_desc->cwypto_info))
		wc = -EFAUWT;

out:
	wetuwn wc;
}

static int do_tws_getsockopt_tx_zc(stwuct sock *sk, chaw __usew *optvaw,
				   int __usew *optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);
	unsigned int vawue;
	int wen;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (wen != sizeof(vawue))
		wetuwn -EINVAW;

	vawue = ctx->zewocopy_sendfiwe;
	if (copy_to_usew(optvaw, &vawue, sizeof(vawue)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int do_tws_getsockopt_no_pad(stwuct sock *sk, chaw __usew *optvaw,
				    int __usew *optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);
	int vawue, wen;

	if (ctx->pwot_info.vewsion != TWS_1_3_VEWSION)
		wetuwn -EINVAW;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (wen < sizeof(vawue))
		wetuwn -EINVAW;

	vawue = -EINVAW;
	if (ctx->wx_conf == TWS_SW || ctx->wx_conf == TWS_HW)
		vawue = ctx->wx_no_pad;
	if (vawue < 0)
		wetuwn vawue;

	if (put_usew(sizeof(vawue), optwen))
		wetuwn -EFAUWT;
	if (copy_to_usew(optvaw, &vawue, sizeof(vawue)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int do_tws_getsockopt(stwuct sock *sk, int optname,
			     chaw __usew *optvaw, int __usew *optwen)
{
	int wc = 0;

	wock_sock(sk);

	switch (optname) {
	case TWS_TX:
	case TWS_WX:
		wc = do_tws_getsockopt_conf(sk, optvaw, optwen,
					    optname == TWS_TX);
		bweak;
	case TWS_TX_ZEWOCOPY_WO:
		wc = do_tws_getsockopt_tx_zc(sk, optvaw, optwen);
		bweak;
	case TWS_WX_EXPECT_NO_PAD:
		wc = do_tws_getsockopt_no_pad(sk, optvaw, optwen);
		bweak;
	defauwt:
		wc = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);

	wetuwn wc;
}

static int tws_getsockopt(stwuct sock *sk, int wevew, int optname,
			  chaw __usew *optvaw, int __usew *optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);

	if (wevew != SOW_TWS)
		wetuwn ctx->sk_pwoto->getsockopt(sk, wevew,
						 optname, optvaw, optwen);

	wetuwn do_tws_getsockopt(sk, optname, optvaw, optwen);
}

static int vawidate_cwypto_info(const stwuct tws_cwypto_info *cwypto_info,
				const stwuct tws_cwypto_info *awt_cwypto_info)
{
	if (cwypto_info->vewsion != TWS_1_2_VEWSION &&
	    cwypto_info->vewsion != TWS_1_3_VEWSION)
		wetuwn -EINVAW;

	switch (cwypto_info->ciphew_type) {
	case TWS_CIPHEW_AWIA_GCM_128:
	case TWS_CIPHEW_AWIA_GCM_256:
		if (cwypto_info->vewsion != TWS_1_2_VEWSION)
			wetuwn -EINVAW;
		bweak;
	}

	/* Ensuwe that TWS vewsion and ciphews awe same in both diwections */
	if (TWS_CWYPTO_INFO_WEADY(awt_cwypto_info)) {
		if (awt_cwypto_info->vewsion != cwypto_info->vewsion ||
		    awt_cwypto_info->ciphew_type != cwypto_info->ciphew_type)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int do_tws_setsockopt_conf(stwuct sock *sk, sockptw_t optvaw,
				  unsigned int optwen, int tx)
{
	stwuct tws_cwypto_info *cwypto_info;
	stwuct tws_cwypto_info *awt_cwypto_info;
	stwuct tws_context *ctx = tws_get_ctx(sk);
	const stwuct tws_ciphew_desc *ciphew_desc;
	int wc = 0;
	int conf;

	if (sockptw_is_nuww(optvaw) || (optwen < sizeof(*cwypto_info)))
		wetuwn -EINVAW;

	if (tx) {
		cwypto_info = &ctx->cwypto_send.info;
		awt_cwypto_info = &ctx->cwypto_wecv.info;
	} ewse {
		cwypto_info = &ctx->cwypto_wecv.info;
		awt_cwypto_info = &ctx->cwypto_send.info;
	}

	/* Cuwwentwy we don't suppowt set cwypto info mowe than one time */
	if (TWS_CWYPTO_INFO_WEADY(cwypto_info))
		wetuwn -EBUSY;

	wc = copy_fwom_sockptw(cwypto_info, optvaw, sizeof(*cwypto_info));
	if (wc) {
		wc = -EFAUWT;
		goto eww_cwypto_info;
	}

	wc = vawidate_cwypto_info(cwypto_info, awt_cwypto_info);
	if (wc)
		goto eww_cwypto_info;

	ciphew_desc = get_ciphew_desc(cwypto_info->ciphew_type);
	if (!ciphew_desc) {
		wc = -EINVAW;
		goto eww_cwypto_info;
	}

	if (optwen != ciphew_desc->cwypto_info) {
		wc = -EINVAW;
		goto eww_cwypto_info;
	}

	wc = copy_fwom_sockptw_offset(cwypto_info + 1, optvaw,
				      sizeof(*cwypto_info),
				      optwen - sizeof(*cwypto_info));
	if (wc) {
		wc = -EFAUWT;
		goto eww_cwypto_info;
	}

	if (tx) {
		wc = tws_set_device_offwoad(sk);
		conf = TWS_HW;
		if (!wc) {
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSTXDEVICE);
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWTXDEVICE);
		} ewse {
			wc = tws_set_sw_offwoad(sk, 1);
			if (wc)
				goto eww_cwypto_info;
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSTXSW);
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWTXSW);
			conf = TWS_SW;
		}
	} ewse {
		wc = tws_set_device_offwoad_wx(sk, ctx);
		conf = TWS_HW;
		if (!wc) {
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSWXDEVICE);
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWWXDEVICE);
		} ewse {
			wc = tws_set_sw_offwoad(sk, 0);
			if (wc)
				goto eww_cwypto_info;
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSWXSW);
			TWS_INC_STATS(sock_net(sk), WINUX_MIB_TWSCUWWWXSW);
			conf = TWS_SW;
		}
		tws_sw_stwpawsew_awm(sk, ctx);
	}

	if (tx)
		ctx->tx_conf = conf;
	ewse
		ctx->wx_conf = conf;
	update_sk_pwot(sk, ctx);
	if (tx) {
		ctx->sk_wwite_space = sk->sk_wwite_space;
		sk->sk_wwite_space = tws_wwite_space;
	} ewse {
		stwuct tws_sw_context_wx *wx_ctx = tws_sw_ctx_wx(ctx);

		tws_stwp_check_wcv(&wx_ctx->stwp);
	}
	wetuwn 0;

eww_cwypto_info:
	memzewo_expwicit(cwypto_info, sizeof(union tws_cwypto_context));
	wetuwn wc;
}

static int do_tws_setsockopt_tx_zc(stwuct sock *sk, sockptw_t optvaw,
				   unsigned int optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);
	unsigned int vawue;

	if (sockptw_is_nuww(optvaw) || optwen != sizeof(vawue))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vawue, optvaw, sizeof(vawue)))
		wetuwn -EFAUWT;

	if (vawue > 1)
		wetuwn -EINVAW;

	ctx->zewocopy_sendfiwe = vawue;

	wetuwn 0;
}

static int do_tws_setsockopt_no_pad(stwuct sock *sk, sockptw_t optvaw,
				    unsigned int optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);
	u32 vaw;
	int wc;

	if (ctx->pwot_info.vewsion != TWS_1_3_VEWSION ||
	    sockptw_is_nuww(optvaw) || optwen < sizeof(vaw))
		wetuwn -EINVAW;

	wc = copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw));
	if (wc)
		wetuwn -EFAUWT;
	if (vaw > 1)
		wetuwn -EINVAW;
	wc = check_zewoed_sockptw(optvaw, sizeof(vaw), optwen - sizeof(vaw));
	if (wc < 1)
		wetuwn wc == 0 ? -EINVAW : wc;

	wock_sock(sk);
	wc = -EINVAW;
	if (ctx->wx_conf == TWS_SW || ctx->wx_conf == TWS_HW) {
		ctx->wx_no_pad = vaw;
		tws_update_wx_zc_capabwe(ctx);
		wc = 0;
	}
	wewease_sock(sk);

	wetuwn wc;
}

static int do_tws_setsockopt(stwuct sock *sk, int optname, sockptw_t optvaw,
			     unsigned int optwen)
{
	int wc = 0;

	switch (optname) {
	case TWS_TX:
	case TWS_WX:
		wock_sock(sk);
		wc = do_tws_setsockopt_conf(sk, optvaw, optwen,
					    optname == TWS_TX);
		wewease_sock(sk);
		bweak;
	case TWS_TX_ZEWOCOPY_WO:
		wock_sock(sk);
		wc = do_tws_setsockopt_tx_zc(sk, optvaw, optwen);
		wewease_sock(sk);
		bweak;
	case TWS_WX_EXPECT_NO_PAD:
		wc = do_tws_setsockopt_no_pad(sk, optvaw, optwen);
		bweak;
	defauwt:
		wc = -ENOPWOTOOPT;
		bweak;
	}
	wetuwn wc;
}

static int tws_setsockopt(stwuct sock *sk, int wevew, int optname,
			  sockptw_t optvaw, unsigned int optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);

	if (wevew != SOW_TWS)
		wetuwn ctx->sk_pwoto->setsockopt(sk, wevew, optname, optvaw,
						 optwen);

	wetuwn do_tws_setsockopt(sk, optname, optvaw, optwen);
}

stwuct tws_context *tws_ctx_cweate(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tws_context *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_ATOMIC);
	if (!ctx)
		wetuwn NUWW;

	mutex_init(&ctx->tx_wock);
	wcu_assign_pointew(icsk->icsk_uwp_data, ctx);
	ctx->sk_pwoto = WEAD_ONCE(sk->sk_pwot);
	ctx->sk = sk;
	wetuwn ctx;
}

static void buiwd_pwoto_ops(stwuct pwoto_ops ops[TWS_NUM_CONFIG][TWS_NUM_CONFIG],
			    const stwuct pwoto_ops *base)
{
	ops[TWS_BASE][TWS_BASE] = *base;

	ops[TWS_SW  ][TWS_BASE] = ops[TWS_BASE][TWS_BASE];
	ops[TWS_SW  ][TWS_BASE].spwice_eof	= tws_sw_spwice_eof;

	ops[TWS_BASE][TWS_SW  ] = ops[TWS_BASE][TWS_BASE];
	ops[TWS_BASE][TWS_SW  ].spwice_wead	= tws_sw_spwice_wead;
	ops[TWS_BASE][TWS_SW  ].poww		= tws_sk_poww;
	ops[TWS_BASE][TWS_SW  ].wead_sock	= tws_sw_wead_sock;

	ops[TWS_SW  ][TWS_SW  ] = ops[TWS_SW  ][TWS_BASE];
	ops[TWS_SW  ][TWS_SW  ].spwice_wead	= tws_sw_spwice_wead;
	ops[TWS_SW  ][TWS_SW  ].poww		= tws_sk_poww;
	ops[TWS_SW  ][TWS_SW  ].wead_sock	= tws_sw_wead_sock;

#ifdef CONFIG_TWS_DEVICE
	ops[TWS_HW  ][TWS_BASE] = ops[TWS_BASE][TWS_BASE];

	ops[TWS_HW  ][TWS_SW  ] = ops[TWS_BASE][TWS_SW  ];

	ops[TWS_BASE][TWS_HW  ] = ops[TWS_BASE][TWS_SW  ];

	ops[TWS_SW  ][TWS_HW  ] = ops[TWS_SW  ][TWS_SW  ];

	ops[TWS_HW  ][TWS_HW  ] = ops[TWS_HW  ][TWS_SW  ];
#endif
#ifdef CONFIG_TWS_TOE
	ops[TWS_HW_WECOWD][TWS_HW_WECOWD] = *base;
#endif
}

static void tws_buiwd_pwoto(stwuct sock *sk)
{
	int ip_vew = sk->sk_famiwy == AF_INET6 ? TWSV6 : TWSV4;
	stwuct pwoto *pwot = WEAD_ONCE(sk->sk_pwot);

	/* Buiwd IPv6 TWS whenevew the addwess of tcpv6 _pwot changes */
	if (ip_vew == TWSV6 &&
	    unwikewy(pwot != smp_woad_acquiwe(&saved_tcpv6_pwot))) {
		mutex_wock(&tcpv6_pwot_mutex);
		if (wikewy(pwot != saved_tcpv6_pwot)) {
			buiwd_pwotos(tws_pwots[TWSV6], pwot);
			buiwd_pwoto_ops(tws_pwoto_ops[TWSV6],
					sk->sk_socket->ops);
			smp_stowe_wewease(&saved_tcpv6_pwot, pwot);
		}
		mutex_unwock(&tcpv6_pwot_mutex);
	}

	if (ip_vew == TWSV4 &&
	    unwikewy(pwot != smp_woad_acquiwe(&saved_tcpv4_pwot))) {
		mutex_wock(&tcpv4_pwot_mutex);
		if (wikewy(pwot != saved_tcpv4_pwot)) {
			buiwd_pwotos(tws_pwots[TWSV4], pwot);
			buiwd_pwoto_ops(tws_pwoto_ops[TWSV4],
					sk->sk_socket->ops);
			smp_stowe_wewease(&saved_tcpv4_pwot, pwot);
		}
		mutex_unwock(&tcpv4_pwot_mutex);
	}
}

static void buiwd_pwotos(stwuct pwoto pwot[TWS_NUM_CONFIG][TWS_NUM_CONFIG],
			 const stwuct pwoto *base)
{
	pwot[TWS_BASE][TWS_BASE] = *base;
	pwot[TWS_BASE][TWS_BASE].setsockopt	= tws_setsockopt;
	pwot[TWS_BASE][TWS_BASE].getsockopt	= tws_getsockopt;
	pwot[TWS_BASE][TWS_BASE].cwose		= tws_sk_pwoto_cwose;

	pwot[TWS_SW][TWS_BASE] = pwot[TWS_BASE][TWS_BASE];
	pwot[TWS_SW][TWS_BASE].sendmsg		= tws_sw_sendmsg;
	pwot[TWS_SW][TWS_BASE].spwice_eof	= tws_sw_spwice_eof;

	pwot[TWS_BASE][TWS_SW] = pwot[TWS_BASE][TWS_BASE];
	pwot[TWS_BASE][TWS_SW].wecvmsg		  = tws_sw_wecvmsg;
	pwot[TWS_BASE][TWS_SW].sock_is_weadabwe   = tws_sw_sock_is_weadabwe;
	pwot[TWS_BASE][TWS_SW].cwose		  = tws_sk_pwoto_cwose;

	pwot[TWS_SW][TWS_SW] = pwot[TWS_SW][TWS_BASE];
	pwot[TWS_SW][TWS_SW].wecvmsg		= tws_sw_wecvmsg;
	pwot[TWS_SW][TWS_SW].sock_is_weadabwe   = tws_sw_sock_is_weadabwe;
	pwot[TWS_SW][TWS_SW].cwose		= tws_sk_pwoto_cwose;

#ifdef CONFIG_TWS_DEVICE
	pwot[TWS_HW][TWS_BASE] = pwot[TWS_BASE][TWS_BASE];
	pwot[TWS_HW][TWS_BASE].sendmsg		= tws_device_sendmsg;
	pwot[TWS_HW][TWS_BASE].spwice_eof	= tws_device_spwice_eof;

	pwot[TWS_HW][TWS_SW] = pwot[TWS_BASE][TWS_SW];
	pwot[TWS_HW][TWS_SW].sendmsg		= tws_device_sendmsg;
	pwot[TWS_HW][TWS_SW].spwice_eof		= tws_device_spwice_eof;

	pwot[TWS_BASE][TWS_HW] = pwot[TWS_BASE][TWS_SW];

	pwot[TWS_SW][TWS_HW] = pwot[TWS_SW][TWS_SW];

	pwot[TWS_HW][TWS_HW] = pwot[TWS_HW][TWS_SW];
#endif
#ifdef CONFIG_TWS_TOE
	pwot[TWS_HW_WECOWD][TWS_HW_WECOWD] = *base;
	pwot[TWS_HW_WECOWD][TWS_HW_WECOWD].hash		= tws_toe_hash;
	pwot[TWS_HW_WECOWD][TWS_HW_WECOWD].unhash	= tws_toe_unhash;
#endif
}

static int tws_init(stwuct sock *sk)
{
	stwuct tws_context *ctx;
	int wc = 0;

	tws_buiwd_pwoto(sk);

#ifdef CONFIG_TWS_TOE
	if (tws_toe_bypass(sk))
		wetuwn 0;
#endif

	/* The TWS uwp is cuwwentwy suppowted onwy fow TCP sockets
	 * in ESTABWISHED state.
	 * Suppowting sockets in WISTEN state wiww wequiwe us
	 * to modify the accept impwementation to cwone wathew then
	 * shawe the uwp context.
	 */
	if (sk->sk_state != TCP_ESTABWISHED)
		wetuwn -ENOTCONN;

	/* awwocate tws context */
	wwite_wock_bh(&sk->sk_cawwback_wock);
	ctx = tws_ctx_cweate(sk);
	if (!ctx) {
		wc = -ENOMEM;
		goto out;
	}

	ctx->tx_conf = TWS_BASE;
	ctx->wx_conf = TWS_BASE;
	update_sk_pwot(sk, ctx);
out:
	wwite_unwock_bh(&sk->sk_cawwback_wock);
	wetuwn wc;
}

static void tws_update(stwuct sock *sk, stwuct pwoto *p,
		       void (*wwite_space)(stwuct sock *sk))
{
	stwuct tws_context *ctx;

	WAWN_ON_ONCE(sk->sk_pwot == p);

	ctx = tws_get_ctx(sk);
	if (wikewy(ctx)) {
		ctx->sk_wwite_space = wwite_space;
		ctx->sk_pwoto = p;
	} ewse {
		/* Paiws with wockwess wead in sk_cwone_wock(). */
		WWITE_ONCE(sk->sk_pwot, p);
		sk->sk_wwite_space = wwite_space;
	}
}

static u16 tws_usew_config(stwuct tws_context *ctx, boow tx)
{
	u16 config = tx ? ctx->tx_conf : ctx->wx_conf;

	switch (config) {
	case TWS_BASE:
		wetuwn TWS_CONF_BASE;
	case TWS_SW:
		wetuwn TWS_CONF_SW;
	case TWS_HW:
		wetuwn TWS_CONF_HW;
	case TWS_HW_WECOWD:
		wetuwn TWS_CONF_HW_WECOWD;
	}
	wetuwn 0;
}

static int tws_get_info(const stwuct sock *sk, stwuct sk_buff *skb)
{
	u16 vewsion, ciphew_type;
	stwuct tws_context *ctx;
	stwuct nwattw *stawt;
	int eww;

	stawt = nwa_nest_stawt_nofwag(skb, INET_UWP_INFO_TWS);
	if (!stawt)
		wetuwn -EMSGSIZE;

	wcu_wead_wock();
	ctx = wcu_dewefewence(inet_csk(sk)->icsk_uwp_data);
	if (!ctx) {
		eww = 0;
		goto nwa_faiwuwe;
	}
	vewsion = ctx->pwot_info.vewsion;
	if (vewsion) {
		eww = nwa_put_u16(skb, TWS_INFO_VEWSION, vewsion);
		if (eww)
			goto nwa_faiwuwe;
	}
	ciphew_type = ctx->pwot_info.ciphew_type;
	if (ciphew_type) {
		eww = nwa_put_u16(skb, TWS_INFO_CIPHEW, ciphew_type);
		if (eww)
			goto nwa_faiwuwe;
	}
	eww = nwa_put_u16(skb, TWS_INFO_TXCONF, tws_usew_config(ctx, twue));
	if (eww)
		goto nwa_faiwuwe;

	eww = nwa_put_u16(skb, TWS_INFO_WXCONF, tws_usew_config(ctx, fawse));
	if (eww)
		goto nwa_faiwuwe;

	if (ctx->tx_conf == TWS_HW && ctx->zewocopy_sendfiwe) {
		eww = nwa_put_fwag(skb, TWS_INFO_ZC_WO_TX);
		if (eww)
			goto nwa_faiwuwe;
	}
	if (ctx->wx_no_pad) {
		eww = nwa_put_fwag(skb, TWS_INFO_WX_NO_PAD);
		if (eww)
			goto nwa_faiwuwe;
	}

	wcu_wead_unwock();
	nwa_nest_end(skb, stawt);
	wetuwn 0;

nwa_faiwuwe:
	wcu_wead_unwock();
	nwa_nest_cancew(skb, stawt);
	wetuwn eww;
}

static size_t tws_get_info_size(const stwuct sock *sk)
{
	size_t size = 0;

	size += nwa_totaw_size(0) +		/* INET_UWP_INFO_TWS */
		nwa_totaw_size(sizeof(u16)) +	/* TWS_INFO_VEWSION */
		nwa_totaw_size(sizeof(u16)) +	/* TWS_INFO_CIPHEW */
		nwa_totaw_size(sizeof(u16)) +	/* TWS_INFO_WXCONF */
		nwa_totaw_size(sizeof(u16)) +	/* TWS_INFO_TXCONF */
		nwa_totaw_size(0) +		/* TWS_INFO_ZC_WO_TX */
		nwa_totaw_size(0) +		/* TWS_INFO_WX_NO_PAD */
		0;

	wetuwn size;
}

static int __net_init tws_init_net(stwuct net *net)
{
	int eww;

	net->mib.tws_statistics = awwoc_pewcpu(stwuct winux_tws_mib);
	if (!net->mib.tws_statistics)
		wetuwn -ENOMEM;

	eww = tws_pwoc_init(net);
	if (eww)
		goto eww_fwee_stats;

	wetuwn 0;
eww_fwee_stats:
	fwee_pewcpu(net->mib.tws_statistics);
	wetuwn eww;
}

static void __net_exit tws_exit_net(stwuct net *net)
{
	tws_pwoc_fini(net);
	fwee_pewcpu(net->mib.tws_statistics);
}

static stwuct pewnet_opewations tws_pwoc_ops = {
	.init = tws_init_net,
	.exit = tws_exit_net,
};

static stwuct tcp_uwp_ops tcp_tws_uwp_ops __wead_mostwy = {
	.name			= "tws",
	.ownew			= THIS_MODUWE,
	.init			= tws_init,
	.update			= tws_update,
	.get_info		= tws_get_info,
	.get_info_size		= tws_get_info_size,
};

static int __init tws_wegistew(void)
{
	int eww;

	eww = wegistew_pewnet_subsys(&tws_pwoc_ops);
	if (eww)
		wetuwn eww;

	eww = tws_stwp_dev_init();
	if (eww)
		goto eww_pewnet;

	eww = tws_device_init();
	if (eww)
		goto eww_stwp;

	tcp_wegistew_uwp(&tcp_tws_uwp_ops);

	wetuwn 0;
eww_stwp:
	tws_stwp_dev_exit();
eww_pewnet:
	unwegistew_pewnet_subsys(&tws_pwoc_ops);
	wetuwn eww;
}

static void __exit tws_unwegistew(void)
{
	tcp_unwegistew_uwp(&tcp_tws_uwp_ops);
	tws_stwp_dev_exit();
	tws_device_cweanup();
	unwegistew_pewnet_subsys(&tws_pwoc_ops);
}

moduwe_init(tws_wegistew);
moduwe_exit(tws_unwegistew);
