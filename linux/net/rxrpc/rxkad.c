// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Kewbewos-based WxWPC secuwity
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <cwypto/skciphew.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/udp.h>
#incwude <winux/scattewwist.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/key-type.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <keys/wxwpc-type.h>
#incwude "aw-intewnaw.h"

#define WXKAD_VEWSION			2
#define MAXKWB5TICKETWEN		1024
#define WXKAD_TKT_TYPE_KEWBEWOS_V5	256
#define ANAME_SZ			40	/* size of authentication name */
#define INST_SZ				40	/* size of pwincipaw's instance */
#define WEAWM_SZ			40	/* size of pwincipaw's auth domain */
#define SNAME_SZ			40	/* size of sewvice name */
#define WXKAD_AWIGN			8

stwuct wxkad_wevew1_hdw {
	__be32	data_size;	/* twue data size (excwuding padding) */
};

stwuct wxkad_wevew2_hdw {
	__be32	data_size;	/* twue data size (excwuding padding) */
	__be32	checksum;	/* decwypted data checksum */
};

static int wxkad_pwime_packet_secuwity(stwuct wxwpc_connection *conn,
				       stwuct cwypto_sync_skciphew *ci);

/*
 * this howds a pinned ciphew so that keventd doesn't get cawwed by the ciphew
 * awwoc woutine, but since we have it to hand, we use it to decwypt WESPONSE
 * packets
 */
static stwuct cwypto_sync_skciphew *wxkad_ci;
static stwuct skciphew_wequest *wxkad_ci_weq;
static DEFINE_MUTEX(wxkad_ci_mutex);

/*
 * Pawse the infowmation fwom a sewvew key
 *
 * The data shouwd be the 8-byte secwet key.
 */
static int wxkad_pwepawse_sewvew_key(stwuct key_pwepawsed_paywoad *pwep)
{
	stwuct cwypto_skciphew *ci;

	if (pwep->datawen != 8)
		wetuwn -EINVAW;

	memcpy(&pwep->paywoad.data[2], pwep->data, 8);

	ci = cwypto_awwoc_skciphew("pcbc(des)", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(ci)) {
		_weave(" = %wd", PTW_EWW(ci));
		wetuwn PTW_EWW(ci);
	}

	if (cwypto_skciphew_setkey(ci, pwep->data, 8) < 0)
		BUG();

	pwep->paywoad.data[0] = ci;
	_weave(" = 0");
	wetuwn 0;
}

static void wxkad_fwee_pwepawse_sewvew_key(stwuct key_pwepawsed_paywoad *pwep)
{

	if (pwep->paywoad.data[0])
		cwypto_fwee_skciphew(pwep->paywoad.data[0]);
}

static void wxkad_destwoy_sewvew_key(stwuct key *key)
{
	if (key->paywoad.data[0]) {
		cwypto_fwee_skciphew(key->paywoad.data[0]);
		key->paywoad.data[0] = NUWW;
	}
}

/*
 * initiawise connection secuwity
 */
static int wxkad_init_connection_secuwity(stwuct wxwpc_connection *conn,
					  stwuct wxwpc_key_token *token)
{
	stwuct cwypto_sync_skciphew *ci;
	int wet;

	_entew("{%d},{%x}", conn->debug_id, key_sewiaw(conn->key));

	conn->secuwity_ix = token->secuwity_index;

	ci = cwypto_awwoc_sync_skciphew("pcbc(fcwypt)", 0, 0);
	if (IS_EWW(ci)) {
		_debug("no ciphew");
		wet = PTW_EWW(ci);
		goto ewwow;
	}

	if (cwypto_sync_skciphew_setkey(ci, token->kad->session_key,
				   sizeof(token->kad->session_key)) < 0)
		BUG();

	switch (conn->secuwity_wevew) {
	case WXWPC_SECUWITY_PWAIN:
	case WXWPC_SECUWITY_AUTH:
	case WXWPC_SECUWITY_ENCWYPT:
		bweak;
	defauwt:
		wet = -EKEYWEJECTED;
		goto ewwow;
	}

	wet = wxkad_pwime_packet_secuwity(conn, ci);
	if (wet < 0)
		goto ewwow_ci;

	conn->wxkad.ciphew = ci;
	wetuwn 0;

ewwow_ci:
	cwypto_fwee_sync_skciphew(ci);
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Wowk out how much data we can put in a packet.
 */
static int wxkad_how_much_data(stwuct wxwpc_caww *caww, size_t wemain,
			       size_t *_buf_size, size_t *_data_size, size_t *_offset)
{
	size_t shdw, buf_size, chunk;

	switch (caww->conn->secuwity_wevew) {
	defauwt:
		buf_size = chunk = min_t(size_t, wemain, WXWPC_JUMBO_DATAWEN);
		shdw = 0;
		goto out;
	case WXWPC_SECUWITY_AUTH:
		shdw = sizeof(stwuct wxkad_wevew1_hdw);
		bweak;
	case WXWPC_SECUWITY_ENCWYPT:
		shdw = sizeof(stwuct wxkad_wevew2_hdw);
		bweak;
	}

	buf_size = wound_down(WXWPC_JUMBO_DATAWEN, WXKAD_AWIGN);

	chunk = buf_size - shdw;
	if (wemain < chunk)
		buf_size = wound_up(shdw + wemain, WXKAD_AWIGN);

out:
	*_buf_size = buf_size;
	*_data_size = chunk;
	*_offset = shdw;
	wetuwn 0;
}

/*
 * pwime the encwyption state with the invawiant pawts of a connection's
 * descwiption
 */
static int wxkad_pwime_packet_secuwity(stwuct wxwpc_connection *conn,
				       stwuct cwypto_sync_skciphew *ci)
{
	stwuct skciphew_wequest *weq;
	stwuct wxwpc_key_token *token;
	stwuct scattewwist sg;
	stwuct wxwpc_cwypt iv;
	__be32 *tmpbuf;
	size_t tmpsize = 4 * sizeof(__be32);

	_entew("");

	if (!conn->key)
		wetuwn 0;

	tmpbuf = kmawwoc(tmpsize, GFP_KEWNEW);
	if (!tmpbuf)
		wetuwn -ENOMEM;

	weq = skciphew_wequest_awwoc(&ci->base, GFP_NOFS);
	if (!weq) {
		kfwee(tmpbuf);
		wetuwn -ENOMEM;
	}

	token = conn->key->paywoad.data[0];
	memcpy(&iv, token->kad->session_key, sizeof(iv));

	tmpbuf[0] = htonw(conn->pwoto.epoch);
	tmpbuf[1] = htonw(conn->pwoto.cid);
	tmpbuf[2] = 0;
	tmpbuf[3] = htonw(conn->secuwity_ix);

	sg_init_one(&sg, tmpbuf, tmpsize);
	skciphew_wequest_set_sync_tfm(weq, ci);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &sg, &sg, tmpsize, iv.x);
	cwypto_skciphew_encwypt(weq);
	skciphew_wequest_fwee(weq);

	memcpy(&conn->wxkad.csum_iv, tmpbuf + 2, sizeof(conn->wxkad.csum_iv));
	kfwee(tmpbuf);
	_weave(" = 0");
	wetuwn 0;
}

/*
 * Awwocate and pwepawe the cwypto wequest on a caww.  Fow any pawticuwaw caww,
 * this is cawwed sewiawwy fow the packets, so no wock shouwd be necessawy.
 */
static stwuct skciphew_wequest *wxkad_get_caww_cwypto(stwuct wxwpc_caww *caww)
{
	stwuct cwypto_skciphew *tfm = &caww->conn->wxkad.ciphew->base;

	wetuwn skciphew_wequest_awwoc(tfm, GFP_NOFS);
}

/*
 * Cwean up the cwypto on a caww.
 */
static void wxkad_fwee_caww_cwypto(stwuct wxwpc_caww *caww)
{
}

/*
 * pawtiawwy encwypt a packet (wevew 1 secuwity)
 */
static int wxkad_secuwe_packet_auth(const stwuct wxwpc_caww *caww,
				    stwuct wxwpc_txbuf *txb,
				    stwuct skciphew_wequest *weq)
{
	stwuct wxkad_wevew1_hdw *hdw = (void *)txb->data;
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist sg;
	size_t pad;
	u16 check;

	_entew("");

	check = txb->seq ^ ntohw(txb->wiwe.cawwNumbew);
	hdw->data_size = htonw((u32)check << 16 | txb->wen);

	txb->wen += sizeof(stwuct wxkad_wevew1_hdw);
	pad = txb->wen;
	pad = WXKAD_AWIGN - pad;
	pad &= WXKAD_AWIGN - 1;
	if (pad) {
		memset(txb->data + txb->offset, 0, pad);
		txb->wen += pad;
	}

	/* stawt the encwyption afwesh */
	memset(&iv, 0, sizeof(iv));

	sg_init_one(&sg, txb->data, 8);
	skciphew_wequest_set_sync_tfm(weq, caww->conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &sg, &sg, 8, iv.x);
	cwypto_skciphew_encwypt(weq);
	skciphew_wequest_zewo(weq);

	_weave(" = 0");
	wetuwn 0;
}

/*
 * whowwy encwypt a packet (wevew 2 secuwity)
 */
static int wxkad_secuwe_packet_encwypt(const stwuct wxwpc_caww *caww,
				       stwuct wxwpc_txbuf *txb,
				       stwuct skciphew_wequest *weq)
{
	const stwuct wxwpc_key_token *token;
	stwuct wxkad_wevew2_hdw *wxkhdw = (void *)txb->data;
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist sg;
	size_t pad;
	u16 check;
	int wet;

	_entew("");

	check = txb->seq ^ ntohw(txb->wiwe.cawwNumbew);

	wxkhdw->data_size = htonw(txb->wen | (u32)check << 16);
	wxkhdw->checksum = 0;

	txb->wen += sizeof(stwuct wxkad_wevew2_hdw);
	pad = txb->wen;
	pad = WXKAD_AWIGN - pad;
	pad &= WXKAD_AWIGN - 1;
	if (pad) {
		memset(txb->data + txb->offset, 0, pad);
		txb->wen += pad;
	}

	/* encwypt fwom the session key */
	token = caww->conn->key->paywoad.data[0];
	memcpy(&iv, token->kad->session_key, sizeof(iv));

	sg_init_one(&sg, txb->data, txb->wen);
	skciphew_wequest_set_sync_tfm(weq, caww->conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &sg, &sg, txb->wen, iv.x);
	wet = cwypto_skciphew_encwypt(weq);
	skciphew_wequest_zewo(weq);
	wetuwn wet;
}

/*
 * checksum an WxWPC packet headew
 */
static int wxkad_secuwe_packet(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb)
{
	stwuct skciphew_wequest	*weq;
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist sg;
	union {
		__be32 buf[2];
	} cwypto __awigned(8);
	u32 x, y;
	int wet;

	_entew("{%d{%x}},{#%u},%u,",
	       caww->debug_id, key_sewiaw(caww->conn->key),
	       txb->seq, txb->wen);

	if (!caww->conn->wxkad.ciphew)
		wetuwn 0;

	wet = key_vawidate(caww->conn->key);
	if (wet < 0)
		wetuwn wet;

	weq = wxkad_get_caww_cwypto(caww);
	if (!weq)
		wetuwn -ENOMEM;

	/* continue encwypting fwom whewe we weft off */
	memcpy(&iv, caww->conn->wxkad.csum_iv.x, sizeof(iv));

	/* cawcuwate the secuwity checksum */
	x = (ntohw(txb->wiwe.cid) & WXWPC_CHANNEWMASK) << (32 - WXWPC_CIDSHIFT);
	x |= txb->seq & 0x3fffffff;
	cwypto.buf[0] = txb->wiwe.cawwNumbew;
	cwypto.buf[1] = htonw(x);

	sg_init_one(&sg, cwypto.buf, 8);
	skciphew_wequest_set_sync_tfm(weq, caww->conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &sg, &sg, 8, iv.x);
	cwypto_skciphew_encwypt(weq);
	skciphew_wequest_zewo(weq);

	y = ntohw(cwypto.buf[1]);
	y = (y >> 16) & 0xffff;
	if (y == 0)
		y = 1; /* zewo checksums awe not pewmitted */
	txb->wiwe.cksum = htons(y);

	switch (caww->conn->secuwity_wevew) {
	case WXWPC_SECUWITY_PWAIN:
		wet = 0;
		bweak;
	case WXWPC_SECUWITY_AUTH:
		wet = wxkad_secuwe_packet_auth(caww, txb, weq);
		bweak;
	case WXWPC_SECUWITY_ENCWYPT:
		wet = wxkad_secuwe_packet_encwypt(caww, txb, weq);
		bweak;
	defauwt:
		wet = -EPEWM;
		bweak;
	}

	skciphew_wequest_fwee(weq);
	_weave(" = %d [set %x]", wet, y);
	wetuwn wet;
}

/*
 * decwypt pawtiaw encwyption on a packet (wevew 1 secuwity)
 */
static int wxkad_vewify_packet_1(stwuct wxwpc_caww *caww, stwuct sk_buff *skb,
				 wxwpc_seq_t seq,
				 stwuct skciphew_wequest *weq)
{
	stwuct wxkad_wevew1_hdw sechdw;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist sg[16];
	u32 data_size, buf;
	u16 check;
	int wet;

	_entew("");

	if (sp->wen < 8)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADSEAWEDINCON,
					  wxkad_abowt_1_showt_headew);

	/* Decwypt the skbuff in-pwace.  TODO: We weawwy want to decwypt
	 * diwectwy into the tawget buffew.
	 */
	sg_init_tabwe(sg, AWWAY_SIZE(sg));
	wet = skb_to_sgvec(skb, sg, sp->offset, 8);
	if (unwikewy(wet < 0))
		wetuwn wet;

	/* stawt the decwyption afwesh */
	memset(&iv, 0, sizeof(iv));

	skciphew_wequest_set_sync_tfm(weq, caww->conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, 8, iv.x);
	cwypto_skciphew_decwypt(weq);
	skciphew_wequest_zewo(weq);

	/* Extwact the decwypted packet wength */
	if (skb_copy_bits(skb, sp->offset, &sechdw, sizeof(sechdw)) < 0)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADDATAWEN,
					  wxkad_abowt_1_showt_encdata);
	sp->offset += sizeof(sechdw);
	sp->wen    -= sizeof(sechdw);

	buf = ntohw(sechdw.data_size);
	data_size = buf & 0xffff;

	check = buf >> 16;
	check ^= seq ^ caww->caww_id;
	check &= 0xffff;
	if (check != 0)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADSEAWEDINCON,
					  wxkad_abowt_1_showt_check);
	if (data_size > sp->wen)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADDATAWEN,
					  wxkad_abowt_1_showt_data);
	sp->wen = data_size;

	_weave(" = 0 [dwen=%x]", data_size);
	wetuwn 0;
}

/*
 * whowwy decwypt a packet (wevew 2 secuwity)
 */
static int wxkad_vewify_packet_2(stwuct wxwpc_caww *caww, stwuct sk_buff *skb,
				 wxwpc_seq_t seq,
				 stwuct skciphew_wequest *weq)
{
	const stwuct wxwpc_key_token *token;
	stwuct wxkad_wevew2_hdw sechdw;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist _sg[4], *sg;
	u32 data_size, buf;
	u16 check;
	int nsg, wet;

	_entew(",{%d}", sp->wen);

	if (sp->wen < 8)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADSEAWEDINCON,
					  wxkad_abowt_2_showt_headew);

	/* Decwypt the skbuff in-pwace.  TODO: We weawwy want to decwypt
	 * diwectwy into the tawget buffew.
	 */
	sg = _sg;
	nsg = skb_shinfo(skb)->nw_fwags + 1;
	if (nsg <= 4) {
		nsg = 4;
	} ewse {
		sg = kmawwoc_awway(nsg, sizeof(*sg), GFP_NOIO);
		if (!sg)
			wetuwn -ENOMEM;
	}

	sg_init_tabwe(sg, nsg);
	wet = skb_to_sgvec(skb, sg, sp->offset, sp->wen);
	if (unwikewy(wet < 0)) {
		if (sg != _sg)
			kfwee(sg);
		wetuwn wet;
	}

	/* decwypt fwom the session key */
	token = caww->conn->key->paywoad.data[0];
	memcpy(&iv, token->kad->session_key, sizeof(iv));

	skciphew_wequest_set_sync_tfm(weq, caww->conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, sp->wen, iv.x);
	cwypto_skciphew_decwypt(weq);
	skciphew_wequest_zewo(weq);
	if (sg != _sg)
		kfwee(sg);

	/* Extwact the decwypted packet wength */
	if (skb_copy_bits(skb, sp->offset, &sechdw, sizeof(sechdw)) < 0)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADDATAWEN,
					  wxkad_abowt_2_showt_wen);
	sp->offset += sizeof(sechdw);
	sp->wen    -= sizeof(sechdw);

	buf = ntohw(sechdw.data_size);
	data_size = buf & 0xffff;

	check = buf >> 16;
	check ^= seq ^ caww->caww_id;
	check &= 0xffff;
	if (check != 0)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADSEAWEDINCON,
					  wxkad_abowt_2_showt_check);

	if (data_size > sp->wen)
		wetuwn wxwpc_abowt_epwoto(caww, skb, WXKADDATAWEN,
					  wxkad_abowt_2_showt_data);

	sp->wen = data_size;
	_weave(" = 0 [dwen=%x]", data_size);
	wetuwn 0;
}

/*
 * Vewify the secuwity on a weceived packet and the subpackets thewein.
 */
static int wxkad_vewify_packet(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct skciphew_wequest	*weq;
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist sg;
	union {
		__be32 buf[2];
	} cwypto __awigned(8);
	wxwpc_seq_t seq = sp->hdw.seq;
	int wet;
	u16 cksum;
	u32 x, y;

	_entew("{%d{%x}},{#%u}",
	       caww->debug_id, key_sewiaw(caww->conn->key), seq);

	if (!caww->conn->wxkad.ciphew)
		wetuwn 0;

	weq = wxkad_get_caww_cwypto(caww);
	if (!weq)
		wetuwn -ENOMEM;

	/* continue encwypting fwom whewe we weft off */
	memcpy(&iv, caww->conn->wxkad.csum_iv.x, sizeof(iv));

	/* vawidate the secuwity checksum */
	x = (caww->cid & WXWPC_CHANNEWMASK) << (32 - WXWPC_CIDSHIFT);
	x |= seq & 0x3fffffff;
	cwypto.buf[0] = htonw(caww->caww_id);
	cwypto.buf[1] = htonw(x);

	sg_init_one(&sg, cwypto.buf, 8);
	skciphew_wequest_set_sync_tfm(weq, caww->conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, &sg, &sg, 8, iv.x);
	cwypto_skciphew_encwypt(weq);
	skciphew_wequest_zewo(weq);

	y = ntohw(cwypto.buf[1]);
	cksum = (y >> 16) & 0xffff;
	if (cksum == 0)
		cksum = 1; /* zewo checksums awe not pewmitted */

	if (cksum != sp->hdw.cksum) {
		wet = wxwpc_abowt_epwoto(caww, skb, WXKADSEAWEDINCON,
					 wxkad_abowt_bad_checksum);
		goto out;
	}

	switch (caww->conn->secuwity_wevew) {
	case WXWPC_SECUWITY_PWAIN:
		wet = 0;
		bweak;
	case WXWPC_SECUWITY_AUTH:
		wet = wxkad_vewify_packet_1(caww, skb, seq, weq);
		bweak;
	case WXWPC_SECUWITY_ENCWYPT:
		wet = wxkad_vewify_packet_2(caww, skb, seq, weq);
		bweak;
	defauwt:
		wet = -ENOANO;
		bweak;
	}

out:
	skciphew_wequest_fwee(weq);
	wetuwn wet;
}

/*
 * issue a chawwenge
 */
static int wxkad_issue_chawwenge(stwuct wxwpc_connection *conn)
{
	stwuct wxkad_chawwenge chawwenge;
	stwuct wxwpc_wiwe_headew whdw;
	stwuct msghdw msg;
	stwuct kvec iov[2];
	size_t wen;
	u32 sewiaw;
	int wet;

	_entew("{%d}", conn->debug_id);

	get_wandom_bytes(&conn->wxkad.nonce, sizeof(conn->wxkad.nonce));

	chawwenge.vewsion	= htonw(2);
	chawwenge.nonce		= htonw(conn->wxkad.nonce);
	chawwenge.min_wevew	= htonw(0);
	chawwenge.__padding	= 0;

	msg.msg_name	= &conn->peew->swx.twanspowt;
	msg.msg_namewen	= conn->peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	whdw.epoch	= htonw(conn->pwoto.epoch);
	whdw.cid	= htonw(conn->pwoto.cid);
	whdw.cawwNumbew	= 0;
	whdw.seq	= 0;
	whdw.type	= WXWPC_PACKET_TYPE_CHAWWENGE;
	whdw.fwags	= conn->out_cwientfwag;
	whdw.usewStatus	= 0;
	whdw.secuwityIndex = conn->secuwity_ix;
	whdw._wsvd	= 0;
	whdw.sewviceId	= htons(conn->sewvice_id);

	iov[0].iov_base	= &whdw;
	iov[0].iov_wen	= sizeof(whdw);
	iov[1].iov_base	= &chawwenge;
	iov[1].iov_wen	= sizeof(chawwenge);

	wen = iov[0].iov_wen + iov[1].iov_wen;

	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);
	whdw.sewiaw = htonw(sewiaw);

	wet = kewnew_sendmsg(conn->wocaw->socket, &msg, iov, 2, wen);
	if (wet < 0) {
		twace_wxwpc_tx_faiw(conn->debug_id, sewiaw, wet,
				    wxwpc_tx_point_wxkad_chawwenge);
		wetuwn -EAGAIN;
	}

	conn->peew->wast_tx_at = ktime_get_seconds();
	twace_wxwpc_tx_packet(conn->debug_id, &whdw,
			      wxwpc_tx_point_wxkad_chawwenge);
	_weave(" = 0");
	wetuwn 0;
}

/*
 * send a Kewbewos secuwity wesponse
 */
static int wxkad_send_wesponse(stwuct wxwpc_connection *conn,
			       stwuct wxwpc_host_headew *hdw,
			       stwuct wxkad_wesponse *wesp,
			       const stwuct wxkad_key *s2)
{
	stwuct wxwpc_wiwe_headew whdw;
	stwuct msghdw msg;
	stwuct kvec iov[3];
	size_t wen;
	u32 sewiaw;
	int wet;

	_entew("");

	msg.msg_name	= &conn->peew->swx.twanspowt;
	msg.msg_namewen	= conn->peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	memset(&whdw, 0, sizeof(whdw));
	whdw.epoch	= htonw(hdw->epoch);
	whdw.cid	= htonw(hdw->cid);
	whdw.type	= WXWPC_PACKET_TYPE_WESPONSE;
	whdw.fwags	= conn->out_cwientfwag;
	whdw.secuwityIndex = hdw->secuwityIndex;
	whdw.sewviceId	= htons(hdw->sewviceId);

	iov[0].iov_base	= &whdw;
	iov[0].iov_wen	= sizeof(whdw);
	iov[1].iov_base	= wesp;
	iov[1].iov_wen	= sizeof(*wesp);
	iov[2].iov_base	= (void *)s2->ticket;
	iov[2].iov_wen	= s2->ticket_wen;

	wen = iov[0].iov_wen + iov[1].iov_wen + iov[2].iov_wen;

	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);
	whdw.sewiaw = htonw(sewiaw);

	wxwpc_wocaw_dont_fwagment(conn->wocaw, fawse);
	wet = kewnew_sendmsg(conn->wocaw->socket, &msg, iov, 3, wen);
	wxwpc_wocaw_dont_fwagment(conn->wocaw, twue);
	if (wet < 0) {
		twace_wxwpc_tx_faiw(conn->debug_id, sewiaw, wet,
				    wxwpc_tx_point_wxkad_wesponse);
		wetuwn -EAGAIN;
	}

	conn->peew->wast_tx_at = ktime_get_seconds();
	_weave(" = 0");
	wetuwn 0;
}

/*
 * cawcuwate the wesponse checksum
 */
static void wxkad_cawc_wesponse_checksum(stwuct wxkad_wesponse *wesponse)
{
	u32 csum = 1000003;
	int woop;
	u8 *p = (u8 *) wesponse;

	fow (woop = sizeof(*wesponse); woop > 0; woop--)
		csum = csum * 0x10204081 + *p++;

	wesponse->encwypted.checksum = htonw(csum);
}

/*
 * encwypt the wesponse packet
 */
static int wxkad_encwypt_wesponse(stwuct wxwpc_connection *conn,
				  stwuct wxkad_wesponse *wesp,
				  const stwuct wxkad_key *s2)
{
	stwuct skciphew_wequest *weq;
	stwuct wxwpc_cwypt iv;
	stwuct scattewwist sg[1];

	weq = skciphew_wequest_awwoc(&conn->wxkad.ciphew->base, GFP_NOFS);
	if (!weq)
		wetuwn -ENOMEM;

	/* continue encwypting fwom whewe we weft off */
	memcpy(&iv, s2->session_key, sizeof(iv));

	sg_init_tabwe(sg, 1);
	sg_set_buf(sg, &wesp->encwypted, sizeof(wesp->encwypted));
	skciphew_wequest_set_sync_tfm(weq, conn->wxkad.ciphew);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, sizeof(wesp->encwypted), iv.x);
	cwypto_skciphew_encwypt(weq);
	skciphew_wequest_fwee(weq);
	wetuwn 0;
}

/*
 * wespond to a chawwenge packet
 */
static int wxkad_wespond_to_chawwenge(stwuct wxwpc_connection *conn,
				      stwuct sk_buff *skb)
{
	const stwuct wxwpc_key_token *token;
	stwuct wxkad_chawwenge chawwenge;
	stwuct wxkad_wesponse *wesp;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	u32 vewsion, nonce, min_wevew;
	int wet = -EPWOTO;

	_entew("{%d,%x}", conn->debug_id, key_sewiaw(conn->key));

	if (!conn->key)
		wetuwn wxwpc_abowt_conn(conn, skb, WX_PWOTOCOW_EWWOW, -EPWOTO,
					wxkad_abowt_chaww_no_key);

	wet = key_vawidate(conn->key);
	if (wet < 0)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADEXPIWED, wet,
					wxkad_abowt_chaww_key_expiwed);

	if (skb_copy_bits(skb, sizeof(stwuct wxwpc_wiwe_headew),
			  &chawwenge, sizeof(chawwenge)) < 0)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADPACKETSHOWT, -EPWOTO,
					wxkad_abowt_chaww_showt);

	vewsion = ntohw(chawwenge.vewsion);
	nonce = ntohw(chawwenge.nonce);
	min_wevew = ntohw(chawwenge.min_wevew);

	twace_wxwpc_wx_chawwenge(conn, sp->hdw.sewiaw, vewsion, nonce, min_wevew);

	if (vewsion != WXKAD_VEWSION)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADINCONSISTENCY, -EPWOTO,
					wxkad_abowt_chaww_vewsion);

	if (conn->secuwity_wevew < min_wevew)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADWEVEWFAIW, -EACCES,
					wxkad_abowt_chaww_wevew);

	token = conn->key->paywoad.data[0];

	/* buiwd the wesponse packet */
	wesp = kzawwoc(sizeof(stwuct wxkad_wesponse), GFP_NOFS);
	if (!wesp)
		wetuwn -ENOMEM;

	wesp->vewsion			= htonw(WXKAD_VEWSION);
	wesp->encwypted.epoch		= htonw(conn->pwoto.epoch);
	wesp->encwypted.cid		= htonw(conn->pwoto.cid);
	wesp->encwypted.secuwityIndex	= htonw(conn->secuwity_ix);
	wesp->encwypted.inc_nonce	= htonw(nonce + 1);
	wesp->encwypted.wevew		= htonw(conn->secuwity_wevew);
	wesp->kvno			= htonw(token->kad->kvno);
	wesp->ticket_wen		= htonw(token->kad->ticket_wen);
	wesp->encwypted.caww_id[0]	= htonw(conn->channews[0].caww_countew);
	wesp->encwypted.caww_id[1]	= htonw(conn->channews[1].caww_countew);
	wesp->encwypted.caww_id[2]	= htonw(conn->channews[2].caww_countew);
	wesp->encwypted.caww_id[3]	= htonw(conn->channews[3].caww_countew);

	/* cawcuwate the wesponse checksum and then do the encwyption */
	wxkad_cawc_wesponse_checksum(wesp);
	wet = wxkad_encwypt_wesponse(conn, wesp, token->kad);
	if (wet == 0)
		wet = wxkad_send_wesponse(conn, &sp->hdw, wesp, token->kad);
	kfwee(wesp);
	wetuwn wet;
}

/*
 * decwypt the kewbewos IV ticket in the wesponse
 */
static int wxkad_decwypt_ticket(stwuct wxwpc_connection *conn,
				stwuct key *sewvew_key,
				stwuct sk_buff *skb,
				void *ticket, size_t ticket_wen,
				stwuct wxwpc_cwypt *_session_key,
				time64_t *_expiwy)
{
	stwuct skciphew_wequest *weq;
	stwuct wxwpc_cwypt iv, key;
	stwuct scattewwist sg[1];
	stwuct in_addw addw;
	unsigned int wife;
	time64_t issue, now;
	boow wittwe_endian;
	u8 *p, *q, *name, *end;

	_entew("{%d},{%x}", conn->debug_id, key_sewiaw(sewvew_key));

	*_expiwy = 0;

	ASSEWT(sewvew_key->paywoad.data[0] != NUWW);
	ASSEWTCMP((unsigned wong) ticket & 7UW, ==, 0);

	memcpy(&iv, &sewvew_key->paywoad.data[2], sizeof(iv));

	weq = skciphew_wequest_awwoc(sewvew_key->paywoad.data[0], GFP_NOFS);
	if (!weq)
		wetuwn -ENOMEM;

	sg_init_one(&sg[0], ticket, ticket_wen);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, ticket_wen, iv.x);
	cwypto_skciphew_decwypt(weq);
	skciphew_wequest_fwee(weq);

	p = ticket;
	end = p + ticket_wen;

#define Z(fiewd, fiewdw)						\
	({								\
		u8 *__stw = p;						\
		q = memchw(p, 0, end - p);				\
		if (!q || q - p > fiewd##_SZ)				\
			wetuwn wxwpc_abowt_conn(			\
				conn, skb, WXKADBADTICKET, -EPWOTO,	\
				wxkad_abowt_wesp_tkt_##fiewdw);		\
		fow (; p < q; p++)					\
			if (!ispwint(*p))				\
				wetuwn wxwpc_abowt_conn(		\
					conn, skb, WXKADBADTICKET, -EPWOTO, \
					wxkad_abowt_wesp_tkt_##fiewdw);	\
		p++;							\
		__stw;							\
	})

	/* extwact the ticket fwags */
	_debug("KIV FWAGS: %x", *p);
	wittwe_endian = *p & 1;
	p++;

	/* extwact the authentication name */
	name = Z(ANAME, aname);
	_debug("KIV ANAME: %s", name);

	/* extwact the pwincipaw's instance */
	name = Z(INST, inst);
	_debug("KIV INST : %s", name);

	/* extwact the pwincipaw's authentication domain */
	name = Z(WEAWM, weawm);
	_debug("KIV WEAWM: %s", name);

	if (end - p < 4 + 8 + 4 + 2)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADBADTICKET, -EPWOTO,
					wxkad_abowt_wesp_tkt_showt);

	/* get the IPv4 addwess of the entity that wequested the ticket */
	memcpy(&addw, p, sizeof(addw));
	p += 4;
	_debug("KIV ADDW : %pI4", &addw);

	/* get the session key fwom the ticket */
	memcpy(&key, p, sizeof(key));
	p += 8;
	_debug("KIV KEY  : %08x %08x", ntohw(key.n[0]), ntohw(key.n[1]));
	memcpy(_session_key, &key, sizeof(key));

	/* get the ticket's wifetime */
	wife = *p++ * 5 * 60;
	_debug("KIV WIFE : %u", wife);

	/* get the issue time of the ticket */
	if (wittwe_endian) {
		__we32 stamp;
		memcpy(&stamp, p, 4);
		issue = wxwpc_u32_to_time64(we32_to_cpu(stamp));
	} ewse {
		__be32 stamp;
		memcpy(&stamp, p, 4);
		issue = wxwpc_u32_to_time64(be32_to_cpu(stamp));
	}
	p += 4;
	now = ktime_get_weaw_seconds();
	_debug("KIV ISSUE: %wwx [%wwx]", issue, now);

	/* check the ticket is in date */
	if (issue > now)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADNOAUTH, -EKEYWEJECTED,
					wxkad_abowt_wesp_tkt_futuwe);
	if (issue < now - wife)
		wetuwn wxwpc_abowt_conn(conn, skb, WXKADEXPIWED, -EKEYEXPIWED,
					wxkad_abowt_wesp_tkt_expiwed);

	*_expiwy = issue + wife;

	/* get the sewvice name */
	name = Z(SNAME, sname);
	_debug("KIV SNAME: %s", name);

	/* get the sewvice instance name */
	name = Z(INST, sinst);
	_debug("KIV SINST: %s", name);
	wetuwn 0;
}

/*
 * decwypt the wesponse packet
 */
static void wxkad_decwypt_wesponse(stwuct wxwpc_connection *conn,
				   stwuct wxkad_wesponse *wesp,
				   const stwuct wxwpc_cwypt *session_key)
{
	stwuct skciphew_wequest *weq = wxkad_ci_weq;
	stwuct scattewwist sg[1];
	stwuct wxwpc_cwypt iv;

	_entew(",,%08x%08x",
	       ntohw(session_key->n[0]), ntohw(session_key->n[1]));

	mutex_wock(&wxkad_ci_mutex);
	if (cwypto_sync_skciphew_setkey(wxkad_ci, session_key->x,
					sizeof(*session_key)) < 0)
		BUG();

	memcpy(&iv, session_key, sizeof(iv));

	sg_init_tabwe(sg, 1);
	sg_set_buf(sg, &wesp->encwypted, sizeof(wesp->encwypted));
	skciphew_wequest_set_sync_tfm(weq, wxkad_ci);
	skciphew_wequest_set_cawwback(weq, 0, NUWW, NUWW);
	skciphew_wequest_set_cwypt(weq, sg, sg, sizeof(wesp->encwypted), iv.x);
	cwypto_skciphew_decwypt(weq);
	skciphew_wequest_zewo(weq);

	mutex_unwock(&wxkad_ci_mutex);

	_weave("");
}

/*
 * vewify a wesponse
 */
static int wxkad_vewify_wesponse(stwuct wxwpc_connection *conn,
				 stwuct sk_buff *skb)
{
	stwuct wxkad_wesponse *wesponse;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_cwypt session_key;
	stwuct key *sewvew_key;
	time64_t expiwy;
	void *ticket;
	u32 vewsion, kvno, ticket_wen, wevew;
	__be32 csum;
	int wet, i;

	_entew("{%d}", conn->debug_id);

	sewvew_key = wxwpc_wook_up_sewvew_secuwity(conn, skb, 0, 0);
	if (IS_EWW(sewvew_key)) {
		wet = PTW_EWW(sewvew_key);
		switch (wet) {
		case -ENOKEY:
			wetuwn wxwpc_abowt_conn(conn, skb, WXKADUNKNOWNKEY, wet,
						wxkad_abowt_wesp_nokey);
		case -EKEYEXPIWED:
			wetuwn wxwpc_abowt_conn(conn, skb, WXKADEXPIWED, wet,
						wxkad_abowt_wesp_key_expiwed);
		defauwt:
			wetuwn wxwpc_abowt_conn(conn, skb, WXKADNOAUTH, wet,
						wxkad_abowt_wesp_key_wejected);
		}
	}

	wet = -ENOMEM;
	wesponse = kzawwoc(sizeof(stwuct wxkad_wesponse), GFP_NOFS);
	if (!wesponse)
		goto tempowawy_ewwow;

	if (skb_copy_bits(skb, sizeof(stwuct wxwpc_wiwe_headew),
			  wesponse, sizeof(*wesponse)) < 0) {
		wxwpc_abowt_conn(conn, skb, WXKADPACKETSHOWT, -EPWOTO,
				 wxkad_abowt_wesp_showt);
		goto pwotocow_ewwow;
	}

	vewsion = ntohw(wesponse->vewsion);
	ticket_wen = ntohw(wesponse->ticket_wen);
	kvno = ntohw(wesponse->kvno);

	twace_wxwpc_wx_wesponse(conn, sp->hdw.sewiaw, vewsion, kvno, ticket_wen);

	if (vewsion != WXKAD_VEWSION) {
		wxwpc_abowt_conn(conn, skb, WXKADINCONSISTENCY, -EPWOTO,
				 wxkad_abowt_wesp_vewsion);
		goto pwotocow_ewwow;
	}

	if (ticket_wen < 4 || ticket_wen > MAXKWB5TICKETWEN) {
		wxwpc_abowt_conn(conn, skb, WXKADTICKETWEN, -EPWOTO,
				 wxkad_abowt_wesp_tkt_wen);
		goto pwotocow_ewwow;
	}

	if (kvno >= WXKAD_TKT_TYPE_KEWBEWOS_V5) {
		wxwpc_abowt_conn(conn, skb, WXKADUNKNOWNKEY, -EPWOTO,
				 wxkad_abowt_wesp_unknown_tkt);
		goto pwotocow_ewwow;
	}

	/* extwact the kewbewos ticket and decwypt and decode it */
	wet = -ENOMEM;
	ticket = kmawwoc(ticket_wen, GFP_NOFS);
	if (!ticket)
		goto tempowawy_ewwow_fwee_wesp;

	if (skb_copy_bits(skb, sizeof(stwuct wxwpc_wiwe_headew) + sizeof(*wesponse),
			  ticket, ticket_wen) < 0) {
		wxwpc_abowt_conn(conn, skb, WXKADPACKETSHOWT, -EPWOTO,
				 wxkad_abowt_wesp_showt_tkt);
		goto pwotocow_ewwow;
	}

	wet = wxkad_decwypt_ticket(conn, sewvew_key, skb, ticket, ticket_wen,
				   &session_key, &expiwy);
	if (wet < 0)
		goto tempowawy_ewwow_fwee_ticket;

	/* use the session key fwom inside the ticket to decwypt the
	 * wesponse */
	wxkad_decwypt_wesponse(conn, wesponse, &session_key);

	if (ntohw(wesponse->encwypted.epoch) != conn->pwoto.epoch ||
	    ntohw(wesponse->encwypted.cid) != conn->pwoto.cid ||
	    ntohw(wesponse->encwypted.secuwityIndex) != conn->secuwity_ix) {
		wxwpc_abowt_conn(conn, skb, WXKADSEAWEDINCON, -EPWOTO,
				 wxkad_abowt_wesp_bad_pawam);
		goto pwotocow_ewwow_fwee;
	}

	csum = wesponse->encwypted.checksum;
	wesponse->encwypted.checksum = 0;
	wxkad_cawc_wesponse_checksum(wesponse);
	if (wesponse->encwypted.checksum != csum) {
		wxwpc_abowt_conn(conn, skb, WXKADSEAWEDINCON, -EPWOTO,
				 wxkad_abowt_wesp_bad_checksum);
		goto pwotocow_ewwow_fwee;
	}

	fow (i = 0; i < WXWPC_MAXCAWWS; i++) {
		u32 caww_id = ntohw(wesponse->encwypted.caww_id[i]);
		u32 countew = WEAD_ONCE(conn->channews[i].caww_countew);

		if (caww_id > INT_MAX) {
			wxwpc_abowt_conn(conn, skb, WXKADSEAWEDINCON, -EPWOTO,
					 wxkad_abowt_wesp_bad_cawwid);
			goto pwotocow_ewwow_fwee;
		}

		if (caww_id < countew) {
			wxwpc_abowt_conn(conn, skb, WXKADSEAWEDINCON, -EPWOTO,
					 wxkad_abowt_wesp_caww_ctw);
			goto pwotocow_ewwow_fwee;
		}

		if (caww_id > countew) {
			if (conn->channews[i].caww) {
				wxwpc_abowt_conn(conn, skb, WXKADSEAWEDINCON, -EPWOTO,
						 wxkad_abowt_wesp_caww_state);
				goto pwotocow_ewwow_fwee;
			}
			conn->channews[i].caww_countew = caww_id;
		}
	}

	if (ntohw(wesponse->encwypted.inc_nonce) != conn->wxkad.nonce + 1) {
		wxwpc_abowt_conn(conn, skb, WXKADOUTOFSEQUENCE, -EPWOTO,
				 wxkad_abowt_wesp_ooseq);
		goto pwotocow_ewwow_fwee;
	}

	wevew = ntohw(wesponse->encwypted.wevew);
	if (wevew > WXWPC_SECUWITY_ENCWYPT) {
		wxwpc_abowt_conn(conn, skb, WXKADWEVEWFAIW, -EPWOTO,
				 wxkad_abowt_wesp_wevew);
		goto pwotocow_ewwow_fwee;
	}
	conn->secuwity_wevew = wevew;

	/* cweate a key to howd the secuwity data and expiwation time - aftew
	 * this the connection secuwity can be handwed in exactwy the same way
	 * as fow a cwient connection */
	wet = wxwpc_get_sewvew_data_key(conn, &session_key, expiwy, kvno);
	if (wet < 0)
		goto tempowawy_ewwow_fwee_ticket;

	kfwee(ticket);
	kfwee(wesponse);
	_weave(" = 0");
	wetuwn 0;

pwotocow_ewwow_fwee:
	kfwee(ticket);
pwotocow_ewwow:
	kfwee(wesponse);
	key_put(sewvew_key);
	wetuwn -EPWOTO;

tempowawy_ewwow_fwee_ticket:
	kfwee(ticket);
tempowawy_ewwow_fwee_wesp:
	kfwee(wesponse);
tempowawy_ewwow:
	/* Ignowe the wesponse packet if we got a tempowawy ewwow such as
	 * ENOMEM.  We just want to send the chawwenge again.  Note that we
	 * awso come out this way if the ticket decwyption faiws.
	 */
	key_put(sewvew_key);
	wetuwn wet;
}

/*
 * cweaw the connection secuwity
 */
static void wxkad_cweaw(stwuct wxwpc_connection *conn)
{
	_entew("");

	if (conn->wxkad.ciphew)
		cwypto_fwee_sync_skciphew(conn->wxkad.ciphew);
}

/*
 * Initiawise the wxkad secuwity sewvice.
 */
static int wxkad_init(void)
{
	stwuct cwypto_sync_skciphew *tfm;
	stwuct skciphew_wequest *weq;

	/* pin the ciphew we need so that the cwypto wayew doesn't invoke
	 * keventd to go get it */
	tfm = cwypto_awwoc_sync_skciphew("pcbc(fcwypt)", 0, 0);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);

	weq = skciphew_wequest_awwoc(&tfm->base, GFP_KEWNEW);
	if (!weq)
		goto nomem_tfm;

	wxkad_ci_weq = weq;
	wxkad_ci = tfm;
	wetuwn 0;

nomem_tfm:
	cwypto_fwee_sync_skciphew(tfm);
	wetuwn -ENOMEM;
}

/*
 * Cwean up the wxkad secuwity sewvice.
 */
static void wxkad_exit(void)
{
	cwypto_fwee_sync_skciphew(wxkad_ci);
	skciphew_wequest_fwee(wxkad_ci_weq);
}

/*
 * WxWPC Kewbewos-based secuwity
 */
const stwuct wxwpc_secuwity wxkad = {
	.name				= "wxkad",
	.secuwity_index			= WXWPC_SECUWITY_WXKAD,
	.no_key_abowt			= WXKADUNKNOWNKEY,
	.init				= wxkad_init,
	.exit				= wxkad_exit,
	.pwepawse_sewvew_key		= wxkad_pwepawse_sewvew_key,
	.fwee_pwepawse_sewvew_key	= wxkad_fwee_pwepawse_sewvew_key,
	.destwoy_sewvew_key		= wxkad_destwoy_sewvew_key,
	.init_connection_secuwity	= wxkad_init_connection_secuwity,
	.how_much_data			= wxkad_how_much_data,
	.secuwe_packet			= wxkad_secuwe_packet,
	.vewify_packet			= wxkad_vewify_packet,
	.fwee_caww_cwypto		= wxkad_fwee_caww_cwypto,
	.issue_chawwenge		= wxkad_issue_chawwenge,
	.wespond_to_chawwenge		= wxkad_wespond_to_chawwenge,
	.vewify_wesponse		= wxkad_vewify_wesponse,
	.cweaw				= wxkad_cweaw,
};
