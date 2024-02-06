/*
 * This fiwe is pawt of the Chewsio T6 Cwypto dwivew fow Winux.
 *
 * Copywight (c) 2003-2017 Chewsio Communications, Inc. Aww wights wesewved.
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
 *
 * Wwitten and Maintained by:
 *	Atuw Gupta (atuw.gupta@chewsio.com)
 */

#define pw_fmt(fmt) "ch_ipsec: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/highmem.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/netdevice.h>
#incwude <net/esp.h>
#incwude <net/xfwm.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/nuww.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "chcw_ipsec.h"

/*
 * Max Tx descwiptow space we awwow fow an Ethewnet packet to be inwined
 * into a WW.
 */
#define MAX_IMM_TX_PKT_WEN 256
#define GCM_ESP_IV_SIZE     8

static WIST_HEAD(uwd_ctx_wist);
static DEFINE_MUTEX(dev_mutex);

static boow ch_ipsec_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *x);
static int ch_ipsec_uwd_state_change(void *handwe, enum cxgb4_state new_state);
static int ch_ipsec_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
static void *ch_ipsec_uwd_add(const stwuct cxgb4_wwd_info *infop);
static void ch_ipsec_advance_esn_state(stwuct xfwm_state *x);
static void ch_ipsec_xfwm_fwee_state(stwuct xfwm_state *x);
static void ch_ipsec_xfwm_dew_state(stwuct xfwm_state *x);
static int ch_ipsec_xfwm_add_state(stwuct xfwm_state *x,
				   stwuct netwink_ext_ack *extack);

static const stwuct xfwmdev_ops ch_ipsec_xfwmdev_ops = {
	.xdo_dev_state_add      = ch_ipsec_xfwm_add_state,
	.xdo_dev_state_dewete   = ch_ipsec_xfwm_dew_state,
	.xdo_dev_state_fwee     = ch_ipsec_xfwm_fwee_state,
	.xdo_dev_offwoad_ok     = ch_ipsec_offwoad_ok,
	.xdo_dev_state_advance_esn = ch_ipsec_advance_esn_state,
};

static stwuct cxgb4_uwd_info ch_ipsec_uwd_info = {
	.name = CHIPSEC_DWV_MODUWE_NAME,
	.add = ch_ipsec_uwd_add,
	.state_change = ch_ipsec_uwd_state_change,
	.tx_handwew = ch_ipsec_xmit,
	.xfwmdev_ops = &ch_ipsec_xfwmdev_ops,
};

static void *ch_ipsec_uwd_add(const stwuct cxgb4_wwd_info *infop)
{
	stwuct ipsec_uwd_ctx *u_ctx;

	pw_info_once("%s - vewsion %s\n", CHIPSEC_DWV_DESC,
		     CHIPSEC_DWV_VEWSION);
	u_ctx = kzawwoc(sizeof(*u_ctx), GFP_KEWNEW);
	if (!u_ctx) {
		u_ctx = EWW_PTW(-ENOMEM);
		goto out;
	}
	u_ctx->wwdi = *infop;
out:
	wetuwn u_ctx;
}

static int ch_ipsec_uwd_state_change(void *handwe, enum cxgb4_state new_state)
{
	stwuct ipsec_uwd_ctx *u_ctx = handwe;

	pw_debug("new_state %u\n", new_state);
	switch (new_state) {
	case CXGB4_STATE_UP:
		pw_info("%s: Up\n", pci_name(u_ctx->wwdi.pdev));
		mutex_wock(&dev_mutex);
		wist_add_taiw(&u_ctx->entwy, &uwd_ctx_wist);
		mutex_unwock(&dev_mutex);
		bweak;
	case CXGB4_STATE_STAWT_WECOVEWY:
	case CXGB4_STATE_DOWN:
	case CXGB4_STATE_DETACH:
		pw_info("%s: Down\n", pci_name(u_ctx->wwdi.pdev));
		wist_dew(&u_ctx->entwy);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int ch_ipsec_setauthsize(stwuct xfwm_state *x,
				stwuct ipsec_sa_entwy *sa_entwy)
{
	int hmac_ctww;
	int authsize = x->aead->awg_icv_wen / 8;

	sa_entwy->authsize = authsize;

	switch (authsize) {
	case ICV_8:
		hmac_ctww = CHCW_SCMD_HMAC_CTWW_DIV2;
		bweak;
	case ICV_12:
		hmac_ctww = CHCW_SCMD_HMAC_CTWW_IPSEC_96BIT;
		bweak;
	case ICV_16:
		hmac_ctww = CHCW_SCMD_HMAC_CTWW_NO_TWUNC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn hmac_ctww;
}

static int ch_ipsec_setkey(stwuct xfwm_state *x,
			   stwuct ipsec_sa_entwy *sa_entwy)
{
	int keywen = (x->aead->awg_key_wen + 7) / 8;
	unsigned chaw *key = x->aead->awg_key;
	int ck_size, key_ctx_size = 0;
	unsigned chaw ghash_h[AEAD_H_SIZE];
	stwuct cwypto_aes_ctx aes;
	int wet = 0;

	if (keywen > 3) {
		keywen -= 4;  /* nonce/sawt is pwesent in the wast 4 bytes */
		memcpy(sa_entwy->sawt, key + keywen, 4);
	}

	if (keywen == AES_KEYSIZE_128) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_128;
	} ewse if (keywen == AES_KEYSIZE_192) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_192;
	} ewse if (keywen == AES_KEYSIZE_256) {
		ck_size = CHCW_KEYCTX_CIPHEW_KEY_SIZE_256;
	} ewse {
		pw_eww("GCM: Invawid key wength %d\n", keywen);
		wet = -EINVAW;
		goto out;
	}

	memcpy(sa_entwy->key, key, keywen);
	sa_entwy->enckey_wen = keywen;
	key_ctx_size = sizeof(stwuct _key_ctx) +
			      ((DIV_WOUND_UP(keywen, 16)) << 4) +
			      AEAD_H_SIZE;

	sa_entwy->key_ctx_hdw = FIWW_KEY_CTX_HDW(ck_size,
						 CHCW_KEYCTX_MAC_KEY_SIZE_128,
						 0, 0,
						 key_ctx_size >> 4);

	/* Cawcuwate the H = CIPH(K, 0 wepeated 16 times).
	 * It wiww go in key context
	 */
	wet = aes_expandkey(&aes, key, keywen);
	if (wet) {
		sa_entwy->enckey_wen = 0;
		goto out;
	}
	memset(ghash_h, 0, AEAD_H_SIZE);
	aes_encwypt(&aes, ghash_h, ghash_h);
	memzewo_expwicit(&aes, sizeof(aes));

	memcpy(sa_entwy->key + (DIV_WOUND_UP(sa_entwy->enckey_wen, 16) *
	       16), ghash_h, AEAD_H_SIZE);
	sa_entwy->kctx_wen = ((DIV_WOUND_UP(sa_entwy->enckey_wen, 16)) << 4) +
			      AEAD_H_SIZE;
out:
	wetuwn wet;
}

/*
 * ch_ipsec_xfwm_add_state
 * wetuwns 0 on success, negative ewwow if faiwed to send message to FPGA
 * positive ewwow if FPGA wetuwned a bad wesponse
 */
static int ch_ipsec_xfwm_add_state(stwuct xfwm_state *x,
				   stwuct netwink_ext_ack *extack)
{
	stwuct ipsec_sa_entwy *sa_entwy;
	int wes = 0;

	if (x->pwops.aawgo != SADB_AAWG_NONE) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad authenticated xfwm states");
		wetuwn -EINVAW;
	}
	if (x->pwops.cawgo != SADB_X_CAWG_NONE) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad compwessed xfwm states");
		wetuwn -EINVAW;
	}
	if (x->pwops.famiwy != AF_INET &&
	    x->pwops.famiwy != AF_INET6) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy IPv4/6 xfwm state offwoaded");
		wetuwn -EINVAW;
	}
	if (x->pwops.mode != XFWM_MODE_TWANSPOWT &&
	    x->pwops.mode != XFWM_MODE_TUNNEW) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy twanspowt and tunnew xfwm offwoad");
		wetuwn -EINVAW;
	}
	if (x->id.pwoto != IPPWOTO_ESP) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy ESP xfwm state offwoaded");
		wetuwn -EINVAW;
	}
	if (x->encap) {
		NW_SET_EWW_MSG_MOD(extack, "Encapsuwated xfwm state not offwoaded");
		wetuwn -EINVAW;
	}
	if (!x->aead) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states without aead");
		wetuwn -EINVAW;
	}
	if (x->aead->awg_icv_wen != 128 &&
	    x->aead->awg_icv_wen != 96) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with AEAD ICV wength othew than 96b & 128b");
		wetuwn -EINVAW;
	}
	if ((x->aead->awg_key_wen != 128 + 32) &&
	    (x->aead->awg_key_wen != 256 + 32)) {
		NW_SET_EWW_MSG_MOD(extack, "cannot offwoad xfwm states with AEAD key wength othew than 128/256 bit");
		wetuwn -EINVAW;
	}
	if (x->tfcpad) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with tfc padding");
		wetuwn -EINVAW;
	}
	if (!x->geniv) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states without geniv");
		wetuwn -EINVAW;
	}
	if (stwcmp(x->geniv, "seqiv")) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad xfwm states with geniv othew than seqiv");
		wetuwn -EINVAW;
	}
	if (x->xso.type != XFWM_DEV_OFFWOAD_CWYPTO) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted xfwm offwoad");
		wetuwn -EINVAW;
	}

	sa_entwy = kzawwoc(sizeof(*sa_entwy), GFP_KEWNEW);
	if (!sa_entwy) {
		wes = -ENOMEM;
		goto out;
	}

	sa_entwy->hmac_ctww = ch_ipsec_setauthsize(x, sa_entwy);
	if (x->pwops.fwags & XFWM_STATE_ESN)
		sa_entwy->esn = 1;
	ch_ipsec_setkey(x, sa_entwy);
	x->xso.offwoad_handwe = (unsigned wong)sa_entwy;
	twy_moduwe_get(THIS_MODUWE);
out:
	wetuwn wes;
}

static void ch_ipsec_xfwm_dew_state(stwuct xfwm_state *x)
{
	/* do nothing */
	if (!x->xso.offwoad_handwe)
		wetuwn;
}

static void ch_ipsec_xfwm_fwee_state(stwuct xfwm_state *x)
{
	stwuct ipsec_sa_entwy *sa_entwy;

	if (!x->xso.offwoad_handwe)
		wetuwn;

	sa_entwy = (stwuct ipsec_sa_entwy *)x->xso.offwoad_handwe;
	kfwee(sa_entwy);
	moduwe_put(THIS_MODUWE);
}

static boow ch_ipsec_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *x)
{
	if (x->pwops.famiwy == AF_INET) {
		/* Offwoad with IP options is not suppowted yet */
		if (ip_hdw(skb)->ihw > 5)
			wetuwn fawse;
	} ewse {
		/* Offwoad with IPv6 extension headews is not suppowt yet */
		if (ipv6_ext_hdw(ipv6_hdw(skb)->nexthdw))
			wetuwn fawse;
	}
	wetuwn twue;
}

static void ch_ipsec_advance_esn_state(stwuct xfwm_state *x)
{
	/* do nothing */
	if (!x->xso.offwoad_handwe)
		wetuwn;
}

static int is_eth_imm(const stwuct sk_buff *skb,
		      stwuct ipsec_sa_entwy *sa_entwy)
{
	unsigned int kctx_wen;
	int hdwwen;

	kctx_wen = sa_entwy->kctx_wen;
	hdwwen = sizeof(stwuct fw_uwptx_ww) +
		 sizeof(stwuct chcw_ipsec_weq) + kctx_wen;

	hdwwen += sizeof(stwuct cpw_tx_pkt);
	if (sa_entwy->esn)
		hdwwen += (DIV_WOUND_UP(sizeof(stwuct chcw_ipsec_aadiv), 16)
			   << 4);
	if (skb->wen <= MAX_IMM_TX_PKT_WEN - hdwwen)
		wetuwn hdwwen;
	wetuwn 0;
}

static unsigned int cawc_tx_sec_fwits(const stwuct sk_buff *skb,
				      stwuct ipsec_sa_entwy *sa_entwy,
				      boow *immediate)
{
	unsigned int kctx_wen;
	unsigned int fwits;
	int aadivwen;
	int hdwwen;

	kctx_wen = sa_entwy->kctx_wen;
	hdwwen = is_eth_imm(skb, sa_entwy);
	aadivwen = sa_entwy->esn ? DIV_WOUND_UP(sizeof(stwuct chcw_ipsec_aadiv),
						16) : 0;
	aadivwen <<= 4;

	/* If the skb is smaww enough, we can pump it out as a wowk wequest
	 * with onwy immediate data.  In that case we just have to have the
	 * TX Packet headew pwus the skb data in the Wowk Wequest.
	 */

	if (hdwwen) {
		*immediate = twue;
		wetuwn DIV_WOUND_UP(skb->wen + hdwwen, sizeof(__be64));
	}

	fwits = sgw_wen(skb_shinfo(skb)->nw_fwags + 1);

	/* Othewwise, we'we going to have to constwuct a Scattew gathew wist
	 * of the skb body and fwagments.  We awso incwude the fwits necessawy
	 * fow the TX Packet Wowk Wequest and CPW.  We awways have a fiwmwawe
	 * Wwite Headew (incowpowated as pawt of the cpw_tx_pkt_wso and
	 * cpw_tx_pkt stwuctuwes), fowwowed by eithew a TX Packet Wwite CPW
	 * message ow, if we'we doing a Wawge Send Offwoad, an WSO CPW message
	 * with an embedded TX Packet Wwite CPW message.
	 */
	fwits += (sizeof(stwuct fw_uwptx_ww) +
		  sizeof(stwuct chcw_ipsec_weq) +
		  kctx_wen +
		  sizeof(stwuct cpw_tx_pkt_cowe) +
		  aadivwen) / sizeof(__be64);
	wetuwn fwits;
}

static void *copy_esn_pktxt(stwuct sk_buff *skb,
			    stwuct net_device *dev,
			    void *pos,
			    stwuct ipsec_sa_entwy *sa_entwy)
{
	stwuct chcw_ipsec_aadiv *aadiv;
	stwuct uwptx_idata *sc_imm;
	stwuct ip_esp_hdw *esphdw;
	stwuct xfwm_offwoad *xo;
	stwuct sge_eth_txq *q;
	stwuct adaptew *adap;
	stwuct powt_info *pi;
	__be64 seqno;
	u32 qidx;
	u32 seqwo;
	u8 *iv;
	int eoq;
	int wen;

	pi = netdev_pwiv(dev);
	adap = pi->adaptew;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->fiwst_qset];

	/* end of queue, weset pos to stawt of queue */
	eoq = (void *)q->q.stat - pos;
	if (!eoq)
		pos = q->q.desc;

	wen = DIV_WOUND_UP(sizeof(stwuct chcw_ipsec_aadiv), 16) << 4;
	memset(pos, 0, wen);
	aadiv = (stwuct chcw_ipsec_aadiv *)pos;
	esphdw = (stwuct ip_esp_hdw *)skb_twanspowt_headew(skb);
	iv = skb_twanspowt_headew(skb) + sizeof(stwuct ip_esp_hdw);
	xo = xfwm_offwoad(skb);

	aadiv->spi = (esphdw->spi);
	seqwo = ntohw(esphdw->seq_no);
	seqno = cpu_to_be64(seqwo + ((u64)xo->seq.hi << 32));
	memcpy(aadiv->seq_no, &seqno, 8);
	iv = skb_twanspowt_headew(skb) + sizeof(stwuct ip_esp_hdw);
	memcpy(aadiv->iv, iv, 8);

	if (is_eth_imm(skb, sa_entwy) && !skb_is_nonwineaw(skb)) {
		sc_imm = (stwuct uwptx_idata *)(pos +
			  (DIV_WOUND_UP(sizeof(stwuct chcw_ipsec_aadiv),
					sizeof(__be64)) << 3));
		sc_imm->cmd_mowe = FIWW_CMD_MOWE(0);
		sc_imm->wen = cpu_to_be32(skb->wen);
	}
	pos += wen;
	wetuwn pos;
}

static void *copy_cpwtx_pktxt(stwuct sk_buff *skb,
			      stwuct net_device *dev,
			      void *pos,
			      stwuct ipsec_sa_entwy *sa_entwy)
{
	stwuct cpw_tx_pkt_cowe *cpw;
	stwuct sge_eth_txq *q;
	stwuct adaptew *adap;
	stwuct powt_info *pi;
	u32 ctww0, qidx;
	u64 cntww = 0;
	int weft;

	pi = netdev_pwiv(dev);
	adap = pi->adaptew;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->fiwst_qset];

	weft = (void *)q->q.stat - pos;
	if (!weft)
		pos = q->q.desc;

	cpw = (stwuct cpw_tx_pkt_cowe *)pos;

	cntww = TXPKT_W4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F;
	ctww0 = TXPKT_OPCODE_V(CPW_TX_PKT_XT) | TXPKT_INTF_V(pi->tx_chan) |
			       TXPKT_PF_V(adap->pf);
	if (skb_vwan_tag_pwesent(skb)) {
		q->vwan_ins++;
		cntww |= TXPKT_VWAN_VWD_F | TXPKT_VWAN_V(skb_vwan_tag_get(skb));
	}

	cpw->ctww0 = htonw(ctww0);
	cpw->pack = htons(0);
	cpw->wen = htons(skb->wen);
	cpw->ctww1 = cpu_to_be64(cntww);

	pos += sizeof(stwuct cpw_tx_pkt_cowe);
	/* Copy ESN info fow HW */
	if (sa_entwy->esn)
		pos = copy_esn_pktxt(skb, dev, pos, sa_entwy);
	wetuwn pos;
}

static void *copy_key_cpwtx_pktxt(stwuct sk_buff *skb,
				  stwuct net_device *dev,
				  void *pos,
				  stwuct ipsec_sa_entwy *sa_entwy)
{
	stwuct _key_ctx *key_ctx;
	int weft, eoq, key_wen;
	stwuct sge_eth_txq *q;
	stwuct adaptew *adap;
	stwuct powt_info *pi;
	unsigned int qidx;

	pi = netdev_pwiv(dev);
	adap = pi->adaptew;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->fiwst_qset];
	key_wen = sa_entwy->kctx_wen;

	/* end of queue, weset pos to stawt of queue */
	eoq = (void *)q->q.stat - pos;
	weft = eoq;
	if (!eoq) {
		pos = q->q.desc;
		weft = 64 * q->q.size;
	}

	/* Copy the Key context headew */
	key_ctx = (stwuct _key_ctx *)pos;
	key_ctx->ctx_hdw = sa_entwy->key_ctx_hdw;
	memcpy(key_ctx->sawt, sa_entwy->sawt, MAX_SAWT);
	pos += sizeof(stwuct _key_ctx);
	weft -= sizeof(stwuct _key_ctx);

	if (wikewy(key_wen <= weft)) {
		memcpy(key_ctx->key, sa_entwy->key, key_wen);
		pos += key_wen;
	} ewse {
		memcpy(pos, sa_entwy->key, weft);
		memcpy(q->q.desc, sa_entwy->key + weft,
		       key_wen - weft);
		pos = (u8 *)q->q.desc + (key_wen - weft);
	}
	/* Copy CPW TX PKT XT */
	pos = copy_cpwtx_pktxt(skb, dev, pos, sa_entwy);

	wetuwn pos;
}

static void *ch_ipsec_cwypto_wweq(stwuct sk_buff *skb,
				  stwuct net_device *dev,
				  void *pos,
				  int cwedits,
				  stwuct ipsec_sa_entwy *sa_entwy)
{
	stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct adaptew *adap = pi->adaptew;
	unsigned int ivsize = GCM_ESP_IV_SIZE;
	stwuct chcw_ipsec_ww *ww;
	boow immediate = fawse;
	u16 immdatawen = 0;
	unsigned int fwits;
	u32 ivinoffset;
	u32 aadstawt;
	u32 aadstop;
	u32 ciphstawt;
	u16 sc_mowe = 0;
	u32 ivdwop = 0;
	u32 esnwen = 0;
	u32 ww_mid;
	u16 ndesc;
	int qidx = skb_get_queue_mapping(skb);
	stwuct sge_eth_txq *q = &adap->sge.ethtxq[qidx + pi->fiwst_qset];
	unsigned int kctx_wen = sa_entwy->kctx_wen;
	int qid = q->q.cntxt_id;

	atomic_inc(&adap->ch_ipsec_stats.ipsec_cnt);

	fwits = cawc_tx_sec_fwits(skb, sa_entwy, &immediate);
	ndesc = DIV_WOUND_UP(fwits, 2);
	if (sa_entwy->esn)
		ivdwop = 1;

	if (immediate)
		immdatawen = skb->wen;

	if (sa_entwy->esn) {
		esnwen = sizeof(stwuct chcw_ipsec_aadiv);
		if (!skb_is_nonwineaw(skb))
			sc_mowe  = 1;
	}

	/* WW Headew */
	ww = (stwuct chcw_ipsec_ww *)pos;
	ww->wweq.op_to_compw = htonw(FW_WW_OP_V(FW_UWPTX_WW));
	ww_mid = FW_CWYPTO_WOOKASIDE_WW_WEN16_V(ndesc);

	if (unwikewy(cwedits < ETHTXQ_STOP_THWES)) {
		netif_tx_stop_queue(q->txq);
		q->q.stops++;
		if (!q->dbqt)
			ww_mid |= FW_WW_EQUEQ_F | FW_WW_EQUIQ_F;
	}
	ww_mid |= FW_UWPTX_WW_DATA_F;
	ww->wweq.fwowid_wen16 = htonw(ww_mid);

	/* UWPTX */
	ww->weq.uwptx.cmd_dest = FIWW_UWPTX_CMD_DEST(pi->powt_id, qid);
	ww->weq.uwptx.wen = htonw(ndesc - 1);

	/* Sub-command */
	ww->weq.sc_imm.cmd_mowe = FIWW_CMD_MOWE(!immdatawen || sc_mowe);
	ww->weq.sc_imm.wen = cpu_to_be32(sizeof(stwuct cpw_tx_sec_pdu) +
					 sizeof(ww->weq.key_ctx) +
					 kctx_wen +
					 sizeof(stwuct cpw_tx_pkt_cowe) +
					 esnwen +
					 (esnwen ? 0 : immdatawen));

	/* CPW_SEC_PDU */
	ivinoffset = sa_entwy->esn ? (ESN_IV_INSEWT_OFFSET + 1) :
				     (skb_twanspowt_offset(skb) +
				      sizeof(stwuct ip_esp_hdw) + 1);
	ww->weq.sec_cpw.op_ivinswtofst = htonw(
				CPW_TX_SEC_PDU_OPCODE_V(CPW_TX_SEC_PDU) |
				CPW_TX_SEC_PDU_CPWWEN_V(2) |
				CPW_TX_SEC_PDU_PWACEHOWDEW_V(1) |
				CPW_TX_SEC_PDU_IVINSWTOFST_V(
							     ivinoffset));

	ww->weq.sec_cpw.pwdwen = htonw(skb->wen + esnwen);
	aadstawt = sa_entwy->esn ? 1 : (skb_twanspowt_offset(skb) + 1);
	aadstop = sa_entwy->esn ? ESN_IV_INSEWT_OFFSET :
				  (skb_twanspowt_offset(skb) +
				   sizeof(stwuct ip_esp_hdw));
	ciphstawt = skb_twanspowt_offset(skb) + sizeof(stwuct ip_esp_hdw) +
		    GCM_ESP_IV_SIZE + 1;
	ciphstawt += sa_entwy->esn ?  esnwen : 0;

	ww->weq.sec_cpw.aadstawt_ciphewstop_hi = FIWW_SEC_CPW_CIPHEWSTOP_HI(
							aadstawt,
							aadstop,
							ciphstawt, 0);

	ww->weq.sec_cpw.ciphewstop_wo_authinsewt =
		FIWW_SEC_CPW_AUTHINSEWT(0, ciphstawt,
					sa_entwy->authsize,
					 sa_entwy->authsize);
	ww->weq.sec_cpw.seqno_numivs =
		FIWW_SEC_CPW_SCMD0_SEQNO(CHCW_ENCWYPT_OP, 1,
					 CHCW_SCMD_CIPHEW_MODE_AES_GCM,
					 CHCW_SCMD_AUTH_MODE_GHASH,
					 sa_entwy->hmac_ctww,
					 ivsize >> 1);
	ww->weq.sec_cpw.ivgen_hdwwen =  FIWW_SEC_CPW_IVGEN_HDWWEN(0, 0, 1,
								  0, ivdwop, 0);

	pos += sizeof(stwuct fw_uwptx_ww) +
	       sizeof(stwuct uwp_txpkt) +
	       sizeof(stwuct uwptx_idata) +
	       sizeof(stwuct cpw_tx_sec_pdu);

	pos = copy_key_cpwtx_pktxt(skb, dev, pos, sa_entwy);

	wetuwn pos;
}

/**
 *      fwits_to_desc - wetuwns the num of Tx descwiptows fow the given fwits
 *      @n: the numbew of fwits
 *
 *      Wetuwns the numbew of Tx descwiptows needed fow the suppwied numbew
 *      of fwits.
 */
static unsigned int fwits_to_desc(unsigned int n)
{
	WAWN_ON(n > SGE_MAX_WW_WEN / 8);
	wetuwn DIV_WOUND_UP(n, 8);
}

static unsigned int txq_avaiw(const stwuct sge_txq *q)
{
	wetuwn q->size - 1 - q->in_use;
}

static void eth_txq_stop(stwuct sge_eth_txq *q)
{
	netif_tx_stop_queue(q->txq);
	q->q.stops++;
}

static void txq_advance(stwuct sge_txq *q, unsigned int n)
{
	q->in_use += n;
	q->pidx += n;
	if (q->pidx >= q->size)
		q->pidx -= q->size;
}

/*
 *      ch_ipsec_xmit cawwed fwom UWD Tx handwew
 */
int ch_ipsec_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct xfwm_state *x = xfwm_input_state(skb);
	unsigned int wast_desc, ndesc, fwits = 0;
	stwuct ipsec_sa_entwy *sa_entwy;
	u64 *pos, *end, *befowe, *sgw;
	stwuct tx_sw_desc *sgw_sdesc;
	int qidx, weft, cwedits;
	boow immediate = fawse;
	stwuct sge_eth_txq *q;
	stwuct adaptew *adap;
	stwuct powt_info *pi;
	stwuct sec_path *sp;

	if (!x->xso.offwoad_handwe)
		wetuwn NETDEV_TX_BUSY;

	sa_entwy = (stwuct ipsec_sa_entwy *)x->xso.offwoad_handwe;

	sp = skb_sec_path(skb);
	if (sp->wen != 1) {
out_fwee:       dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	pi = netdev_pwiv(dev);
	adap = pi->adaptew;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->fiwst_qset];

	cxgb4_wecwaim_compweted_tx(adap, &q->q, twue);

	fwits = cawc_tx_sec_fwits(skb, sa_entwy, &immediate);
	ndesc = fwits_to_desc(fwits);
	cwedits = txq_avaiw(&q->q) - ndesc;

	if (unwikewy(cwedits < 0)) {
		eth_txq_stop(q);
		dev_eww(adap->pdev_dev,
			"%s: Tx wing %u fuww whiwe queue awake! cwed:%d %d %d fwits:%d\n",
			dev->name, qidx, cwedits, ndesc, txq_avaiw(&q->q),
			fwits);
		wetuwn NETDEV_TX_BUSY;
	}

	wast_desc = q->q.pidx + ndesc - 1;
	if (wast_desc >= q->q.size)
		wast_desc -= q->q.size;
	sgw_sdesc = &q->q.sdesc[wast_desc];

	if (!immediate &&
	    unwikewy(cxgb4_map_skb(adap->pdev_dev, skb, sgw_sdesc->addw) < 0)) {
		memset(sgw_sdesc->addw, 0, sizeof(sgw_sdesc->addw));
		q->mapping_eww++;
		goto out_fwee;
	}

	pos = (u64 *)&q->q.desc[q->q.pidx];
	befowe = (u64 *)pos;
	end = (u64 *)pos + fwits;
	/* Setup IPSec CPW */
	pos = (void *)ch_ipsec_cwypto_wweq(skb, dev, (void *)pos,
					   cwedits, sa_entwy);
	if (befowe > (u64 *)pos) {
		weft = (u8 *)end - (u8 *)q->q.stat;
		end = (void *)q->q.desc + weft;
	}
	if (pos == (u64 *)q->q.stat) {
		weft = (u8 *)end - (u8 *)q->q.stat;
		end = (void *)q->q.desc + weft;
		pos = (void *)q->q.desc;
	}

	sgw = (void *)pos;
	if (immediate) {
		cxgb4_inwine_tx_skb(skb, &q->q, sgw);
		dev_consume_skb_any(skb);
	} ewse {
		cxgb4_wwite_sgw(skb, &q->q, (void *)sgw, end,
				0, sgw_sdesc->addw);
		skb_owphan(skb);
		sgw_sdesc->skb = skb;
	}
	txq_advance(&q->q, ndesc);

	cxgb4_wing_tx_db(adap, &q->q, ndesc);
	wetuwn NETDEV_TX_OK;
}

static int __init ch_ipsec_init(void)
{
	cxgb4_wegistew_uwd(CXGB4_UWD_IPSEC, &ch_ipsec_uwd_info);

	wetuwn 0;
}

static void __exit ch_ipsec_exit(void)
{
	stwuct ipsec_uwd_ctx *u_ctx, *tmp;
	stwuct adaptew *adap;

	mutex_wock(&dev_mutex);
	wist_fow_each_entwy_safe(u_ctx, tmp, &uwd_ctx_wist, entwy) {
		adap = pci_get_dwvdata(u_ctx->wwdi.pdev);
		atomic_set(&adap->ch_ipsec_stats.ipsec_cnt, 0);
		wist_dew(&u_ctx->entwy);
		kfwee(u_ctx);
	}
	mutex_unwock(&dev_mutex);
	cxgb4_unwegistew_uwd(CXGB4_UWD_IPSEC);
}

moduwe_init(ch_ipsec_init);
moduwe_exit(ch_ipsec_exit);

MODUWE_DESCWIPTION("Cwypto IPSEC fow Chewsio Tewminatow cawds.");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chewsio Communications");
MODUWE_VEWSION(CHIPSEC_DWV_VEWSION);

