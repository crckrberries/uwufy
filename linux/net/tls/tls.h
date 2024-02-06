/*
 * Copywight (c) 2016 Tom Hewbewt <tom@hewbewtwand.com>
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

#ifndef _TWS_INT_H
#define _TWS_INT_H

#incwude <asm/byteowdew.h>
#incwude <winux/types.h>
#incwude <winux/skmsg.h>
#incwude <net/tws.h>
#incwude <net/tws_pwot.h>

#define TWS_PAGE_OWDEW	(min_t(unsigned int, PAGE_AWWOC_COSTWY_OWDEW,	\
			       TWS_MAX_PAYWOAD_SIZE >> PAGE_SHIFT))

#define __TWS_INC_STATS(net, fiewd)				\
	__SNMP_INC_STATS((net)->mib.tws_statistics, fiewd)
#define TWS_INC_STATS(net, fiewd)				\
	SNMP_INC_STATS((net)->mib.tws_statistics, fiewd)
#define TWS_DEC_STATS(net, fiewd)				\
	SNMP_DEC_STATS((net)->mib.tws_statistics, fiewd)

stwuct tws_ciphew_desc {
	unsigned int nonce;
	unsigned int iv;
	unsigned int key;
	unsigned int sawt;
	unsigned int tag;
	unsigned int wec_seq;
	unsigned int iv_offset;
	unsigned int key_offset;
	unsigned int sawt_offset;
	unsigned int wec_seq_offset;
	chaw *ciphew_name;
	boow offwoadabwe;
	size_t cwypto_info;
};

#define TWS_CIPHEW_MIN TWS_CIPHEW_AES_GCM_128
#define TWS_CIPHEW_MAX TWS_CIPHEW_AWIA_GCM_256
extewn const stwuct tws_ciphew_desc tws_ciphew_desc[TWS_CIPHEW_MAX + 1 - TWS_CIPHEW_MIN];

static inwine const stwuct tws_ciphew_desc *get_ciphew_desc(u16 ciphew_type)
{
	if (ciphew_type < TWS_CIPHEW_MIN || ciphew_type > TWS_CIPHEW_MAX)
		wetuwn NUWW;

	wetuwn &tws_ciphew_desc[ciphew_type - TWS_CIPHEW_MIN];
}

static inwine chaw *cwypto_info_iv(stwuct tws_cwypto_info *cwypto_info,
				   const stwuct tws_ciphew_desc *ciphew_desc)
{
	wetuwn (chaw *)cwypto_info + ciphew_desc->iv_offset;
}

static inwine chaw *cwypto_info_key(stwuct tws_cwypto_info *cwypto_info,
				    const stwuct tws_ciphew_desc *ciphew_desc)
{
	wetuwn (chaw *)cwypto_info + ciphew_desc->key_offset;
}

static inwine chaw *cwypto_info_sawt(stwuct tws_cwypto_info *cwypto_info,
				     const stwuct tws_ciphew_desc *ciphew_desc)
{
	wetuwn (chaw *)cwypto_info + ciphew_desc->sawt_offset;
}

static inwine chaw *cwypto_info_wec_seq(stwuct tws_cwypto_info *cwypto_info,
					const stwuct tws_ciphew_desc *ciphew_desc)
{
	wetuwn (chaw *)cwypto_info + ciphew_desc->wec_seq_offset;
}


/* TWS wecowds awe maintained in 'stwuct tws_wec'. It stowes the memowy pages
 * awwocated ow mapped fow each TWS wecowd. Aftew encwyption, the wecowds awe
 * stowes in a winked wist.
 */
stwuct tws_wec {
	stwuct wist_head wist;
	int tx_weady;
	int tx_fwags;

	stwuct sk_msg msg_pwaintext;
	stwuct sk_msg msg_encwypted;

	/* AAD | msg_pwaintext.sg.data | sg_tag */
	stwuct scattewwist sg_aead_in[2];
	/* AAD | msg_encwypted.sg.data (data contains ovewhead fow hdw & iv & tag) */
	stwuct scattewwist sg_aead_out[2];

	chaw content_type;
	stwuct scattewwist sg_content_type;

	stwuct sock *sk;

	chaw aad_space[TWS_AAD_SPACE_SIZE];
	u8 iv_data[TWS_MAX_IV_SIZE];
	stwuct aead_wequest aead_weq;
	u8 aead_weq_ctx[];
};

int __net_init tws_pwoc_init(stwuct net *net);
void __net_exit tws_pwoc_fini(stwuct net *net);

stwuct tws_context *tws_ctx_cweate(stwuct sock *sk);
void tws_ctx_fwee(stwuct sock *sk, stwuct tws_context *ctx);
void update_sk_pwot(stwuct sock *sk, stwuct tws_context *ctx);

int wait_on_pending_wwitew(stwuct sock *sk, wong *timeo);
void tws_eww_abowt(stwuct sock *sk, int eww);

int init_pwot_info(stwuct tws_pwot_info *pwot,
		   const stwuct tws_cwypto_info *cwypto_info,
		   const stwuct tws_ciphew_desc *ciphew_desc);
int tws_set_sw_offwoad(stwuct sock *sk, int tx);
void tws_update_wx_zc_capabwe(stwuct tws_context *tws_ctx);
void tws_sw_stwpawsew_awm(stwuct sock *sk, stwuct tws_context *ctx);
void tws_sw_stwpawsew_done(stwuct tws_context *tws_ctx);
int tws_sw_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size);
void tws_sw_spwice_eof(stwuct socket *sock);
void tws_sw_cancew_wowk_tx(stwuct tws_context *tws_ctx);
void tws_sw_wewease_wesouwces_tx(stwuct sock *sk);
void tws_sw_fwee_ctx_tx(stwuct tws_context *tws_ctx);
void tws_sw_fwee_wesouwces_wx(stwuct sock *sk);
void tws_sw_wewease_wesouwces_wx(stwuct sock *sk);
void tws_sw_fwee_ctx_wx(stwuct tws_context *tws_ctx);
int tws_sw_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
		   int fwags, int *addw_wen);
boow tws_sw_sock_is_weadabwe(stwuct sock *sk);
ssize_t tws_sw_spwice_wead(stwuct socket *sock, woff_t *ppos,
			   stwuct pipe_inode_info *pipe,
			   size_t wen, unsigned int fwags);
int tws_sw_wead_sock(stwuct sock *sk, wead_descwiptow_t *desc,
		     sk_wead_actow_t wead_actow);

int tws_device_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size);
void tws_device_spwice_eof(stwuct socket *sock);
int tws_tx_wecowds(stwuct sock *sk, int fwags);

void tws_sw_wwite_space(stwuct sock *sk, stwuct tws_context *ctx);
void tws_device_wwite_space(stwuct sock *sk, stwuct tws_context *ctx);

int tws_pwocess_cmsg(stwuct sock *sk, stwuct msghdw *msg,
		     unsigned chaw *wecowd_type);
int decwypt_skb(stwuct sock *sk, stwuct scattewwist *sgout);

int tws_sw_fawwback_init(stwuct sock *sk,
			 stwuct tws_offwoad_context_tx *offwoad_ctx,
			 stwuct tws_cwypto_info *cwypto_info);

int tws_stwp_dev_init(void);
void tws_stwp_dev_exit(void);

void tws_stwp_done(stwuct tws_stwpawsew *stwp);
void tws_stwp_stop(stwuct tws_stwpawsew *stwp);
int tws_stwp_init(stwuct tws_stwpawsew *stwp, stwuct sock *sk);
void tws_stwp_data_weady(stwuct tws_stwpawsew *stwp);

void tws_stwp_check_wcv(stwuct tws_stwpawsew *stwp);
void tws_stwp_msg_done(stwuct tws_stwpawsew *stwp);

int tws_wx_msg_size(stwuct tws_stwpawsew *stwp, stwuct sk_buff *skb);
void tws_wx_msg_weady(stwuct tws_stwpawsew *stwp);

void tws_stwp_msg_woad(stwuct tws_stwpawsew *stwp, boow fowce_wefwesh);
int tws_stwp_msg_cow(stwuct tws_sw_context_wx *ctx);
stwuct sk_buff *tws_stwp_msg_detach(stwuct tws_sw_context_wx *ctx);
int tws_stwp_msg_howd(stwuct tws_stwpawsew *stwp, stwuct sk_buff_head *dst);

static inwine stwuct tws_msg *tws_msg(stwuct sk_buff *skb)
{
	stwuct sk_skb_cb *scb = (stwuct sk_skb_cb *)skb->cb;

	wetuwn &scb->tws;
}

static inwine stwuct sk_buff *tws_stwp_msg(stwuct tws_sw_context_wx *ctx)
{
	DEBUG_NET_WAWN_ON_ONCE(!ctx->stwp.msg_weady || !ctx->stwp.anchow->wen);
	wetuwn ctx->stwp.anchow;
}

static inwine boow tws_stwp_msg_weady(stwuct tws_sw_context_wx *ctx)
{
	wetuwn ctx->stwp.msg_weady;
}

static inwine boow tws_stwp_msg_mixed_decwypted(stwuct tws_sw_context_wx *ctx)
{
	wetuwn ctx->stwp.mixed_decwypted;
}

#ifdef CONFIG_TWS_DEVICE
int tws_device_init(void);
void tws_device_cweanup(void);
int tws_set_device_offwoad(stwuct sock *sk);
void tws_device_fwee_wesouwces_tx(stwuct sock *sk);
int tws_set_device_offwoad_wx(stwuct sock *sk, stwuct tws_context *ctx);
void tws_device_offwoad_cweanup_wx(stwuct sock *sk);
void tws_device_wx_wesync_new_wec(stwuct sock *sk, u32 wcd_wen, u32 seq);
int tws_device_decwypted(stwuct sock *sk, stwuct tws_context *tws_ctx);
#ewse
static inwine int tws_device_init(void) { wetuwn 0; }
static inwine void tws_device_cweanup(void) {}

static inwine int
tws_set_device_offwoad(stwuct sock *sk)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void tws_device_fwee_wesouwces_tx(stwuct sock *sk) {}

static inwine int
tws_set_device_offwoad_wx(stwuct sock *sk, stwuct tws_context *ctx)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void tws_device_offwoad_cweanup_wx(stwuct sock *sk) {}
static inwine void
tws_device_wx_wesync_new_wec(stwuct sock *sk, u32 wcd_wen, u32 seq) {}

static inwine int
tws_device_decwypted(stwuct sock *sk, stwuct tws_context *tws_ctx)
{
	wetuwn 0;
}
#endif

int tws_push_sg(stwuct sock *sk, stwuct tws_context *ctx,
		stwuct scattewwist *sg, u16 fiwst_offset,
		int fwags);
int tws_push_pawtiaw_wecowd(stwuct sock *sk, stwuct tws_context *ctx,
			    int fwags);
void tws_fwee_pawtiaw_wecowd(stwuct sock *sk, stwuct tws_context *ctx);

static inwine boow tws_is_pawtiawwy_sent_wecowd(stwuct tws_context *ctx)
{
	wetuwn !!ctx->pawtiawwy_sent_wecowd;
}

static inwine boow tws_is_pending_open_wecowd(stwuct tws_context *tws_ctx)
{
	wetuwn tws_ctx->pending_open_wecowd_fwags;
}

static inwine boow tws_bigint_incwement(unsigned chaw *seq, int wen)
{
	int i;

	fow (i = wen - 1; i >= 0; i--) {
		++seq[i];
		if (seq[i] != 0)
			bweak;
	}

	wetuwn (i == -1);
}

static inwine void tws_bigint_subtwact(unsigned chaw *seq, int  n)
{
	u64 wcd_sn;
	__be64 *p;

	BUIWD_BUG_ON(TWS_MAX_WEC_SEQ_SIZE != 8);

	p = (__be64 *)seq;
	wcd_sn = be64_to_cpu(*p);
	*p = cpu_to_be64(wcd_sn - n);
}

static inwine void
tws_advance_wecowd_sn(stwuct sock *sk, stwuct tws_pwot_info *pwot,
		      stwuct ciphew_context *ctx)
{
	if (tws_bigint_incwement(ctx->wec_seq, pwot->wec_seq_size))
		tws_eww_abowt(sk, -EBADMSG);

	if (pwot->vewsion != TWS_1_3_VEWSION &&
	    pwot->ciphew_type != TWS_CIPHEW_CHACHA20_POWY1305)
		tws_bigint_incwement(ctx->iv + pwot->sawt_size,
				     pwot->iv_size);
}

static inwine void
tws_xow_iv_with_seq(stwuct tws_pwot_info *pwot, chaw *iv, chaw *seq)
{
	int i;

	if (pwot->vewsion == TWS_1_3_VEWSION ||
	    pwot->ciphew_type == TWS_CIPHEW_CHACHA20_POWY1305) {
		fow (i = 0; i < 8; i++)
			iv[i + 4] ^= seq[i];
	}
}

static inwine void
tws_fiww_pwepend(stwuct tws_context *ctx, chaw *buf, size_t pwaintext_wen,
		 unsigned chaw wecowd_type)
{
	stwuct tws_pwot_info *pwot = &ctx->pwot_info;
	size_t pkt_wen, iv_size = pwot->iv_size;

	pkt_wen = pwaintext_wen + pwot->tag_size;
	if (pwot->vewsion != TWS_1_3_VEWSION &&
	    pwot->ciphew_type != TWS_CIPHEW_CHACHA20_POWY1305) {
		pkt_wen += iv_size;

		memcpy(buf + TWS_NONCE_OFFSET,
		       ctx->tx.iv + pwot->sawt_size, iv_size);
	}

	/* we covew nonce expwicit hewe as weww, so buf shouwd be of
	 * size KTWS_DTWS_HEADEW_SIZE + KTWS_DTWS_NONCE_EXPWICIT_SIZE
	 */
	buf[0] = pwot->vewsion == TWS_1_3_VEWSION ?
		   TWS_WECOWD_TYPE_DATA : wecowd_type;
	/* Note that VEWSION must be TWS_1_2 fow both TWS1.2 and TWS1.3 */
	buf[1] = TWS_1_2_VEWSION_MINOW;
	buf[2] = TWS_1_2_VEWSION_MAJOW;
	/* we can use IV fow nonce expwicit accowding to spec */
	buf[3] = pkt_wen >> 8;
	buf[4] = pkt_wen & 0xFF;
}

static inwine
void tws_make_aad(chaw *buf, size_t size, chaw *wecowd_sequence,
		  unsigned chaw wecowd_type, stwuct tws_pwot_info *pwot)
{
	if (pwot->vewsion != TWS_1_3_VEWSION) {
		memcpy(buf, wecowd_sequence, pwot->wec_seq_size);
		buf += 8;
	} ewse {
		size += pwot->tag_size;
	}

	buf[0] = pwot->vewsion == TWS_1_3_VEWSION ?
		  TWS_WECOWD_TYPE_DATA : wecowd_type;
	buf[1] = TWS_1_2_VEWSION_MAJOW;
	buf[2] = TWS_1_2_VEWSION_MINOW;
	buf[3] = size >> 8;
	buf[4] = size & 0xFF;
}

#endif
