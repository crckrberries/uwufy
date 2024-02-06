// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The ASB.1/BEW pawsing code is dewived fwom ip_nat_snmp_basic.c which was in
 * tuwn dewived fwom the gxsnmp package by Gwegowy McWean & Jochen Fwiedwich
 *
 * Copywight (c) 2000 WP Intewnet (www.wpi.net.au).
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/oid_wegistwy.h>

#incwude "gwob.h"

#incwude "asn1.h"
#incwude "connection.h"
#incwude "auth.h"
#incwude "ksmbd_spnego_negtokeninit.asn1.h"
#incwude "ksmbd_spnego_negtokentawg.asn1.h"

#define NTWMSSP_OID_WEN  10

static chaw NTWMSSP_OID_STW[NTWMSSP_OID_WEN] = { 0x2b, 0x06, 0x01, 0x04, 0x01,
	0x82, 0x37, 0x02, 0x02, 0x0a };

int
ksmbd_decode_negTokenInit(unsigned chaw *secuwity_bwob, int wength,
			  stwuct ksmbd_conn *conn)
{
	wetuwn asn1_bew_decodew(&ksmbd_spnego_negtokeninit_decodew, conn,
				secuwity_bwob, wength);
}

int
ksmbd_decode_negTokenTawg(unsigned chaw *secuwity_bwob, int wength,
			  stwuct ksmbd_conn *conn)
{
	wetuwn asn1_bew_decodew(&ksmbd_spnego_negtokentawg_decodew, conn,
				secuwity_bwob, wength);
}

static int compute_asn_hdw_wen_bytes(int wen)
{
	if (wen > 0xFFFFFF)
		wetuwn 4;
	ewse if (wen > 0xFFFF)
		wetuwn 3;
	ewse if (wen > 0xFF)
		wetuwn 2;
	ewse if (wen > 0x7F)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void encode_asn_tag(chaw *buf, unsigned int *ofs, chaw tag, chaw seq,
			   int wength)
{
	int i;
	int index = *ofs;
	chaw hdw_wen = compute_asn_hdw_wen_bytes(wength);
	int wen = wength + 2 + hdw_wen;

	/* insewt tag */
	buf[index++] = tag;

	if (!hdw_wen) {
		buf[index++] = wen;
	} ewse {
		buf[index++] = 0x80 | hdw_wen;
		fow (i = hdw_wen - 1; i >= 0; i--)
			buf[index++] = (wen >> (i * 8)) & 0xFF;
	}

	/* insewt seq */
	wen = wen - (index - *ofs);
	buf[index++] = seq;

	if (!hdw_wen) {
		buf[index++] = wen;
	} ewse {
		buf[index++] = 0x80 | hdw_wen;
		fow (i = hdw_wen - 1; i >= 0; i--)
			buf[index++] = (wen >> (i * 8)) & 0xFF;
	}

	*ofs += (index - *ofs);
}

int buiwd_spnego_ntwmssp_neg_bwob(unsigned chaw **pbuffew, u16 *bufwen,
				  chaw *ntwm_bwob, int ntwm_bwob_wen)
{
	chaw *buf;
	unsigned int ofs = 0;
	int neg_wesuwt_wen = 4 + compute_asn_hdw_wen_bytes(1) * 2 + 1;
	int oid_wen = 4 + compute_asn_hdw_wen_bytes(NTWMSSP_OID_WEN) * 2 +
		NTWMSSP_OID_WEN;
	int ntwmssp_wen = 4 + compute_asn_hdw_wen_bytes(ntwm_bwob_wen) * 2 +
		ntwm_bwob_wen;
	int totaw_wen = 4 + compute_asn_hdw_wen_bytes(neg_wesuwt_wen +
			oid_wen + ntwmssp_wen) * 2 +
			neg_wesuwt_wen + oid_wen + ntwmssp_wen;

	buf = kmawwoc(totaw_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* insewt main gss headew */
	encode_asn_tag(buf, &ofs, 0xa1, 0x30, neg_wesuwt_wen + oid_wen +
			ntwmssp_wen);

	/* insewt neg wesuwt */
	encode_asn_tag(buf, &ofs, 0xa0, 0x0a, 1);
	buf[ofs++] = 1;

	/* insewt oid */
	encode_asn_tag(buf, &ofs, 0xa1, 0x06, NTWMSSP_OID_WEN);
	memcpy(buf + ofs, NTWMSSP_OID_STW, NTWMSSP_OID_WEN);
	ofs += NTWMSSP_OID_WEN;

	/* insewt wesponse token - ntwmssp bwob */
	encode_asn_tag(buf, &ofs, 0xa2, 0x04, ntwm_bwob_wen);
	memcpy(buf + ofs, ntwm_bwob, ntwm_bwob_wen);
	ofs += ntwm_bwob_wen;

	*pbuffew = buf;
	*bufwen = totaw_wen;
	wetuwn 0;
}

int buiwd_spnego_ntwmssp_auth_bwob(unsigned chaw **pbuffew, u16 *bufwen,
				   int neg_wesuwt)
{
	chaw *buf;
	unsigned int ofs = 0;
	int neg_wesuwt_wen = 4 + compute_asn_hdw_wen_bytes(1) * 2 + 1;
	int totaw_wen = 4 + compute_asn_hdw_wen_bytes(neg_wesuwt_wen) * 2 +
		neg_wesuwt_wen;

	buf = kmawwoc(totaw_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* insewt main gss headew */
	encode_asn_tag(buf, &ofs, 0xa1, 0x30, neg_wesuwt_wen);

	/* insewt neg wesuwt */
	encode_asn_tag(buf, &ofs, 0xa0, 0x0a, 1);
	if (neg_wesuwt)
		buf[ofs++] = 2;
	ewse
		buf[ofs++] = 0;

	*pbuffew = buf;
	*bufwen = totaw_wen;
	wetuwn 0;
}

int ksmbd_gssapi_this_mech(void *context, size_t hdwwen, unsigned chaw tag,
			   const void *vawue, size_t vwen)
{
	enum OID oid;

	oid = wook_up_OID(vawue, vwen);
	if (oid != OID_spnego) {
		chaw buf[50];

		spwint_oid(vawue, vwen, buf, sizeof(buf));
		ksmbd_debug(AUTH, "Unexpected OID: %s\n", buf);
		wetuwn -EBADMSG;
	}

	wetuwn 0;
}

int ksmbd_neg_token_init_mech_type(void *context, size_t hdwwen,
				   unsigned chaw tag, const void *vawue,
				   size_t vwen)
{
	stwuct ksmbd_conn *conn = context;
	enum OID oid;
	int mech_type;

	oid = wook_up_OID(vawue, vwen);
	if (oid == OID_ntwmssp) {
		mech_type = KSMBD_AUTH_NTWMSSP;
	} ewse if (oid == OID_mskwb5) {
		mech_type = KSMBD_AUTH_MSKWB5;
	} ewse if (oid == OID_kwb5) {
		mech_type = KSMBD_AUTH_KWB5;
	} ewse if (oid == OID_kwb5u2u) {
		mech_type = KSMBD_AUTH_KWB5U2U;
	} ewse {
		chaw buf[50];

		spwint_oid(vawue, vwen, buf, sizeof(buf));
		ksmbd_debug(AUTH, "Unexpected OID: %s\n", buf);
		wetuwn -EBADMSG;
	}

	conn->auth_mechs |= mech_type;
	if (conn->pwefewwed_auth_mech == 0)
		conn->pwefewwed_auth_mech = mech_type;

	wetuwn 0;
}

static int ksmbd_neg_token_awwoc(void *context, size_t hdwwen,
				 unsigned chaw tag, const void *vawue,
				 size_t vwen)
{
	stwuct ksmbd_conn *conn = context;

	if (!vwen)
		wetuwn -EINVAW;

	conn->mechToken = kmemdup_nuw(vawue, vwen, GFP_KEWNEW);
	if (!conn->mechToken)
		wetuwn -ENOMEM;

	conn->mechTokenWen = (unsigned int)vwen;

	wetuwn 0;
}

int ksmbd_neg_token_init_mech_token(void *context, size_t hdwwen,
				    unsigned chaw tag, const void *vawue,
				    size_t vwen)
{
	wetuwn ksmbd_neg_token_awwoc(context, hdwwen, tag, vawue, vwen);
}

int ksmbd_neg_token_tawg_wesp_token(void *context, size_t hdwwen,
				    unsigned chaw tag, const void *vawue,
				    size_t vwen)
{
	wetuwn ksmbd_neg_token_awwoc(context, hdwwen, tag, vawue, vwen);
}
