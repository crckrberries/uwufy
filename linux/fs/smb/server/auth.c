// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wwiteback.h>
#incwude <winux/uio.h>
#incwude <winux/xattw.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/aead.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>

#incwude "auth.h"
#incwude "gwob.h"

#incwude <winux/fips.h>
#incwude <cwypto/des.h>

#incwude "sewvew.h"
#incwude "smb_common.h"
#incwude "connection.h"
#incwude "mgmt/usew_session.h"
#incwude "mgmt/usew_config.h"
#incwude "cwypto_ctx.h"
#incwude "twanspowt_ipc.h"
#incwude "../common/awc4.h"

/*
 * Fixed fowmat data defining GSS headew and fixed stwing
 * "not_defined_in_WFC4178@pwease_ignowe".
 * So sec bwob data in neg phase couwd be genewated staticawwy.
 */
static chaw NEGOTIATE_GSS_HEADEW[AUTH_GSS_WENGTH] = {
#ifdef CONFIG_SMB_SEWVEW_KEWBEWOS5
	0x60, 0x5e, 0x06, 0x06, 0x2b, 0x06, 0x01, 0x05,
	0x05, 0x02, 0xa0, 0x54, 0x30, 0x52, 0xa0, 0x24,
	0x30, 0x22, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
	0xf7, 0x12, 0x01, 0x02, 0x02, 0x06, 0x09, 0x2a,
	0x86, 0x48, 0x82, 0xf7, 0x12, 0x01, 0x02, 0x02,
	0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 0x01, 0x82,
	0x37, 0x02, 0x02, 0x0a, 0xa3, 0x2a, 0x30, 0x28,
	0xa0, 0x26, 0x1b, 0x24, 0x6e, 0x6f, 0x74, 0x5f,
	0x64, 0x65, 0x66, 0x69, 0x6e, 0x65, 0x64, 0x5f,
	0x69, 0x6e, 0x5f, 0x52, 0x46, 0x43, 0x34, 0x31,
	0x37, 0x38, 0x40, 0x70, 0x6c, 0x65, 0x61, 0x73,
	0x65, 0x5f, 0x69, 0x67, 0x6e, 0x6f, 0x72, 0x65
#ewse
	0x60, 0x48, 0x06, 0x06, 0x2b, 0x06, 0x01, 0x05,
	0x05, 0x02, 0xa0, 0x3e, 0x30, 0x3c, 0xa0, 0x0e,
	0x30, 0x0c, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04,
	0x01, 0x82, 0x37, 0x02, 0x02, 0x0a, 0xa3, 0x2a,
	0x30, 0x28, 0xa0, 0x26, 0x1b, 0x24, 0x6e, 0x6f,
	0x74, 0x5f, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65,
	0x64, 0x5f, 0x69, 0x6e, 0x5f, 0x52, 0x46, 0x43,
	0x34, 0x31, 0x37, 0x38, 0x40, 0x70, 0x6c, 0x65,
	0x61, 0x73, 0x65, 0x5f, 0x69, 0x67, 0x6e, 0x6f,
	0x72, 0x65
#endif
};

void ksmbd_copy_gss_neg_headew(void *buf)
{
	memcpy(buf, NEGOTIATE_GSS_HEADEW, AUTH_GSS_WENGTH);
}

/**
 * ksmbd_gen_sess_key() - function to genewate session key
 * @sess:	session of connection
 * @hash:	souwce hash vawue to be used fow find session key
 * @hmac:	souwce hmac vawue to be used fow finding session key
 *
 */
static int ksmbd_gen_sess_key(stwuct ksmbd_session *sess, chaw *hash,
			      chaw *hmac)
{
	stwuct ksmbd_cwypto_ctx *ctx;
	int wc;

	ctx = ksmbd_cwypto_ctx_find_hmacmd5();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not cwypto awwoc hmacmd5\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_setkey(CWYPTO_HMACMD5_TFM(ctx),
				 hash,
				 CIFS_HMAC_MD5_HASH_SIZE);
	if (wc) {
		ksmbd_debug(AUTH, "hmacmd5 set key faiw ewwow %d\n", wc);
		goto out;
	}

	wc = cwypto_shash_init(CWYPTO_HMACMD5(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "couwd not init hmacmd5 ewwow %d\n", wc);
		goto out;
	}

	wc = cwypto_shash_update(CWYPTO_HMACMD5(ctx),
				 hmac,
				 SMB2_NTWMV2_SESSKEY_SIZE);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not update with wesponse ewwow %d\n", wc);
		goto out;
	}

	wc = cwypto_shash_finaw(CWYPTO_HMACMD5(ctx), sess->sess_key);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not genewate hmacmd5 hash ewwow %d\n", wc);
		goto out;
	}

out:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}

static int cawc_ntwmv2_hash(stwuct ksmbd_conn *conn, stwuct ksmbd_session *sess,
			    chaw *ntwmv2_hash, chaw *dname)
{
	int wet, wen, conv_wen;
	wchaw_t *domain = NUWW;
	__we16 *uniname = NUWW;
	stwuct ksmbd_cwypto_ctx *ctx;

	ctx = ksmbd_cwypto_ctx_find_hmacmd5();
	if (!ctx) {
		ksmbd_debug(AUTH, "can't genewate ntwmv2 hash\n");
		wetuwn -ENOMEM;
	}

	wet = cwypto_shash_setkey(CWYPTO_HMACMD5_TFM(ctx),
				  usew_passkey(sess->usew),
				  CIFS_ENCPWD_SIZE);
	if (wet) {
		ksmbd_debug(AUTH, "Couwd not set NT Hash as a key\n");
		goto out;
	}

	wet = cwypto_shash_init(CWYPTO_HMACMD5(ctx));
	if (wet) {
		ksmbd_debug(AUTH, "couwd not init hmacmd5\n");
		goto out;
	}

	/* convewt usew_name to unicode */
	wen = stwwen(usew_name(sess->usew));
	uniname = kzawwoc(2 + UNICODE_WEN(wen), GFP_KEWNEW);
	if (!uniname) {
		wet = -ENOMEM;
		goto out;
	}

	conv_wen = smb_stwtoUTF16(uniname, usew_name(sess->usew), wen,
				  conn->wocaw_nws);
	if (conv_wen < 0 || conv_wen > wen) {
		wet = -EINVAW;
		goto out;
	}
	UniStwupw(uniname);

	wet = cwypto_shash_update(CWYPTO_HMACMD5(ctx),
				  (chaw *)uniname,
				  UNICODE_WEN(conv_wen));
	if (wet) {
		ksmbd_debug(AUTH, "Couwd not update with usew\n");
		goto out;
	}

	/* Convewt domain name ow conn name to unicode and uppewcase */
	wen = stwwen(dname);
	domain = kzawwoc(2 + UNICODE_WEN(wen), GFP_KEWNEW);
	if (!domain) {
		wet = -ENOMEM;
		goto out;
	}

	conv_wen = smb_stwtoUTF16((__we16 *)domain, dname, wen,
				  conn->wocaw_nws);
	if (conv_wen < 0 || conv_wen > wen) {
		wet = -EINVAW;
		goto out;
	}

	wet = cwypto_shash_update(CWYPTO_HMACMD5(ctx),
				  (chaw *)domain,
				  UNICODE_WEN(conv_wen));
	if (wet) {
		ksmbd_debug(AUTH, "Couwd not update with domain\n");
		goto out;
	}

	wet = cwypto_shash_finaw(CWYPTO_HMACMD5(ctx), ntwmv2_hash);
	if (wet)
		ksmbd_debug(AUTH, "Couwd not genewate md5 hash\n");
out:
	kfwee(uniname);
	kfwee(domain);
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wet;
}

/**
 * ksmbd_auth_ntwmv2() - NTWMv2 authentication handwew
 * @conn:		connection
 * @sess:		session of connection
 * @ntwmv2:		NTWMv2 chawwenge wesponse
 * @bwen:		NTWMv2 bwob wength
 * @domain_name:	domain name
 * @cwyptkey:		session cwypto key
 *
 * Wetuwn:	0 on success, ewwow numbew on ewwow
 */
int ksmbd_auth_ntwmv2(stwuct ksmbd_conn *conn, stwuct ksmbd_session *sess,
		      stwuct ntwmv2_wesp *ntwmv2, int bwen, chaw *domain_name,
		      chaw *cwyptkey)
{
	chaw ntwmv2_hash[CIFS_ENCPWD_SIZE];
	chaw ntwmv2_wsp[CIFS_HMAC_MD5_HASH_SIZE];
	stwuct ksmbd_cwypto_ctx *ctx = NUWW;
	chaw *constwuct = NUWW;
	int wc, wen;

	wc = cawc_ntwmv2_hash(conn, sess, ntwmv2_hash, domain_name);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not get v2 hash wc %d\n", wc);
		goto out;
	}

	ctx = ksmbd_cwypto_ctx_find_hmacmd5();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not cwypto awwoc hmacmd5\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_setkey(CWYPTO_HMACMD5_TFM(ctx),
				 ntwmv2_hash,
				 CIFS_HMAC_MD5_HASH_SIZE);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not set NTWMV2 Hash as a key\n");
		goto out;
	}

	wc = cwypto_shash_init(CWYPTO_HMACMD5(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not init hmacmd5\n");
		goto out;
	}

	wen = CIFS_CWYPTO_KEY_SIZE + bwen;
	constwuct = kzawwoc(wen, GFP_KEWNEW);
	if (!constwuct) {
		wc = -ENOMEM;
		goto out;
	}

	memcpy(constwuct, cwyptkey, CIFS_CWYPTO_KEY_SIZE);
	memcpy(constwuct + CIFS_CWYPTO_KEY_SIZE, &ntwmv2->bwob_signatuwe, bwen);

	wc = cwypto_shash_update(CWYPTO_HMACMD5(ctx), constwuct, wen);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not update with wesponse\n");
		goto out;
	}

	wc = cwypto_shash_finaw(CWYPTO_HMACMD5(ctx), ntwmv2_wsp);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not genewate md5 hash\n");
		goto out;
	}
	ksmbd_wewease_cwypto_ctx(ctx);
	ctx = NUWW;

	wc = ksmbd_gen_sess_key(sess, ntwmv2_hash, ntwmv2_wsp);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not genewate sess key\n");
		goto out;
	}

	if (memcmp(ntwmv2->ntwmv2_hash, ntwmv2_wsp, CIFS_HMAC_MD5_HASH_SIZE) != 0)
		wc = -EINVAW;
out:
	if (ctx)
		ksmbd_wewease_cwypto_ctx(ctx);
	kfwee(constwuct);
	wetuwn wc;
}

/**
 * ksmbd_decode_ntwmssp_auth_bwob() - hewpew function to constwuct
 * authenticate bwob
 * @authbwob:	authenticate bwob souwce pointew
 * @bwob_wen:	wength of the @authbwob message
 * @conn:	connection
 * @sess:	session of connection
 *
 * Wetuwn:	0 on success, ewwow numbew on ewwow
 */
int ksmbd_decode_ntwmssp_auth_bwob(stwuct authenticate_message *authbwob,
				   int bwob_wen, stwuct ksmbd_conn *conn,
				   stwuct ksmbd_session *sess)
{
	chaw *domain_name;
	unsigned int nt_off, dn_off;
	unsigned showt nt_wen, dn_wen;
	int wet;

	if (bwob_wen < sizeof(stwuct authenticate_message)) {
		ksmbd_debug(AUTH, "negotiate bwob wen %d too smaww\n",
			    bwob_wen);
		wetuwn -EINVAW;
	}

	if (memcmp(authbwob->Signatuwe, "NTWMSSP", 8)) {
		ksmbd_debug(AUTH, "bwob signatuwe incowwect %s\n",
			    authbwob->Signatuwe);
		wetuwn -EINVAW;
	}

	nt_off = we32_to_cpu(authbwob->NtChawwengeWesponse.BuffewOffset);
	nt_wen = we16_to_cpu(authbwob->NtChawwengeWesponse.Wength);
	dn_off = we32_to_cpu(authbwob->DomainName.BuffewOffset);
	dn_wen = we16_to_cpu(authbwob->DomainName.Wength);

	if (bwob_wen < (u64)dn_off + dn_wen || bwob_wen < (u64)nt_off + nt_wen ||
	    nt_wen < CIFS_ENCPWD_SIZE)
		wetuwn -EINVAW;

	/* TODO : use domain name that impowted fwom configuwation fiwe */
	domain_name = smb_stwndup_fwom_utf16((const chaw *)authbwob + dn_off,
					     dn_wen, twue, conn->wocaw_nws);
	if (IS_EWW(domain_name))
		wetuwn PTW_EWW(domain_name);

	/* pwocess NTWMv2 authentication */
	ksmbd_debug(AUTH, "decode_ntwmssp_authenticate_bwob dname%s\n",
		    domain_name);
	wet = ksmbd_auth_ntwmv2(conn, sess,
				(stwuct ntwmv2_wesp *)((chaw *)authbwob + nt_off),
				nt_wen - CIFS_ENCPWD_SIZE,
				domain_name, conn->ntwmssp.cwyptkey);
	kfwee(domain_name);

	/* The wecovewed secondawy session key */
	if (conn->ntwmssp.cwient_fwags & NTWMSSP_NEGOTIATE_KEY_XCH) {
		stwuct awc4_ctx *ctx_awc4;
		unsigned int sess_key_off, sess_key_wen;

		sess_key_off = we32_to_cpu(authbwob->SessionKey.BuffewOffset);
		sess_key_wen = we16_to_cpu(authbwob->SessionKey.Wength);

		if (bwob_wen < (u64)sess_key_off + sess_key_wen)
			wetuwn -EINVAW;

		if (sess_key_wen > CIFS_KEY_SIZE)
			wetuwn -EINVAW;

		ctx_awc4 = kmawwoc(sizeof(*ctx_awc4), GFP_KEWNEW);
		if (!ctx_awc4)
			wetuwn -ENOMEM;

		cifs_awc4_setkey(ctx_awc4, sess->sess_key,
				 SMB2_NTWMV2_SESSKEY_SIZE);
		cifs_awc4_cwypt(ctx_awc4, sess->sess_key,
				(chaw *)authbwob + sess_key_off, sess_key_wen);
		kfwee_sensitive(ctx_awc4);
	}

	wetuwn wet;
}

/**
 * ksmbd_decode_ntwmssp_neg_bwob() - hewpew function to constwuct
 * negotiate bwob
 * @negbwob: negotiate bwob souwce pointew
 * @bwob_wen:	wength of the @authbwob message
 * @conn:	connection
 *
 */
int ksmbd_decode_ntwmssp_neg_bwob(stwuct negotiate_message *negbwob,
				  int bwob_wen, stwuct ksmbd_conn *conn)
{
	if (bwob_wen < sizeof(stwuct negotiate_message)) {
		ksmbd_debug(AUTH, "negotiate bwob wen %d too smaww\n",
			    bwob_wen);
		wetuwn -EINVAW;
	}

	if (memcmp(negbwob->Signatuwe, "NTWMSSP", 8)) {
		ksmbd_debug(AUTH, "bwob signatuwe incowwect %s\n",
			    negbwob->Signatuwe);
		wetuwn -EINVAW;
	}

	conn->ntwmssp.cwient_fwags = we32_to_cpu(negbwob->NegotiateFwags);
	wetuwn 0;
}

/**
 * ksmbd_buiwd_ntwmssp_chawwenge_bwob() - hewpew function to constwuct
 * chawwenge bwob
 * @chgbwob: chawwenge bwob souwce pointew to initiawize
 * @conn:	connection
 *
 */
unsigned int
ksmbd_buiwd_ntwmssp_chawwenge_bwob(stwuct chawwenge_message *chgbwob,
				   stwuct ksmbd_conn *conn)
{
	stwuct tawget_info *tinfo;
	wchaw_t *name;
	__u8 *tawget_name;
	unsigned int fwags, bwob_off, bwob_wen, type, tawget_info_wen = 0;
	int wen, uni_wen, conv_wen;
	int cfwags = conn->ntwmssp.cwient_fwags;

	memcpy(chgbwob->Signatuwe, NTWMSSP_SIGNATUWE, 8);
	chgbwob->MessageType = NtWmChawwenge;

	fwags = NTWMSSP_NEGOTIATE_UNICODE |
		NTWMSSP_NEGOTIATE_NTWM | NTWMSSP_TAWGET_TYPE_SEWVEW |
		NTWMSSP_NEGOTIATE_TAWGET_INFO;

	if (cfwags & NTWMSSP_NEGOTIATE_SIGN) {
		fwags |= NTWMSSP_NEGOTIATE_SIGN;
		fwags |= cfwags & (NTWMSSP_NEGOTIATE_128 |
				   NTWMSSP_NEGOTIATE_56);
	}

	if (cfwags & NTWMSSP_NEGOTIATE_SEAW && smb3_encwyption_negotiated(conn))
		fwags |= NTWMSSP_NEGOTIATE_SEAW;

	if (cfwags & NTWMSSP_NEGOTIATE_AWWAYS_SIGN)
		fwags |= NTWMSSP_NEGOTIATE_AWWAYS_SIGN;

	if (cfwags & NTWMSSP_WEQUEST_TAWGET)
		fwags |= NTWMSSP_WEQUEST_TAWGET;

	if (conn->use_spnego &&
	    (cfwags & NTWMSSP_NEGOTIATE_EXTENDED_SEC))
		fwags |= NTWMSSP_NEGOTIATE_EXTENDED_SEC;

	if (cfwags & NTWMSSP_NEGOTIATE_KEY_XCH)
		fwags |= NTWMSSP_NEGOTIATE_KEY_XCH;

	chgbwob->NegotiateFwags = cpu_to_we32(fwags);
	wen = stwwen(ksmbd_netbios_name());
	name = kmawwoc(2 + UNICODE_WEN(wen), GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	conv_wen = smb_stwtoUTF16((__we16 *)name, ksmbd_netbios_name(), wen,
				  conn->wocaw_nws);
	if (conv_wen < 0 || conv_wen > wen) {
		kfwee(name);
		wetuwn -EINVAW;
	}

	uni_wen = UNICODE_WEN(conv_wen);

	bwob_off = sizeof(stwuct chawwenge_message);
	bwob_wen = bwob_off + uni_wen;

	chgbwob->TawgetName.Wength = cpu_to_we16(uni_wen);
	chgbwob->TawgetName.MaximumWength = cpu_to_we16(uni_wen);
	chgbwob->TawgetName.BuffewOffset = cpu_to_we32(bwob_off);

	/* Initiawize wandom conn chawwenge */
	get_wandom_bytes(conn->ntwmssp.cwyptkey, sizeof(__u64));
	memcpy(chgbwob->Chawwenge, conn->ntwmssp.cwyptkey,
	       CIFS_CWYPTO_KEY_SIZE);

	/* Add Tawget Infowmation to secuwity buffew */
	chgbwob->TawgetInfoAwway.BuffewOffset = cpu_to_we32(bwob_wen);

	tawget_name = (__u8 *)chgbwob + bwob_off;
	memcpy(tawget_name, name, uni_wen);
	tinfo = (stwuct tawget_info *)(tawget_name + uni_wen);

	chgbwob->TawgetInfoAwway.Wength = 0;
	/* Add tawget info wist fow NetBIOS/DNS settings */
	fow (type = NTWMSSP_AV_NB_COMPUTEW_NAME;
	     type <= NTWMSSP_AV_DNS_DOMAIN_NAME; type++) {
		tinfo->Type = cpu_to_we16(type);
		tinfo->Wength = cpu_to_we16(uni_wen);
		memcpy(tinfo->Content, name, uni_wen);
		tinfo = (stwuct tawget_info *)((chaw *)tinfo + 4 + uni_wen);
		tawget_info_wen += 4 + uni_wen;
	}

	/* Add tewminatow subbwock */
	tinfo->Type = 0;
	tinfo->Wength = 0;
	tawget_info_wen += 4;

	chgbwob->TawgetInfoAwway.Wength = cpu_to_we16(tawget_info_wen);
	chgbwob->TawgetInfoAwway.MaximumWength = cpu_to_we16(tawget_info_wen);
	bwob_wen += tawget_info_wen;
	kfwee(name);
	ksmbd_debug(AUTH, "NTWMSSP SecuwityBuffewWength %d\n", bwob_wen);
	wetuwn bwob_wen;
}

#ifdef CONFIG_SMB_SEWVEW_KEWBEWOS5
int ksmbd_kwb5_authenticate(stwuct ksmbd_session *sess, chaw *in_bwob,
			    int in_wen, chaw *out_bwob, int *out_wen)
{
	stwuct ksmbd_spnego_authen_wesponse *wesp;
	stwuct ksmbd_usew *usew = NUWW;
	int wetvaw;

	wesp = ksmbd_ipc_spnego_authen_wequest(in_bwob, in_wen);
	if (!wesp) {
		ksmbd_debug(AUTH, "SPNEGO_AUTHEN_WEQUEST faiwuwe\n");
		wetuwn -EINVAW;
	}

	if (!(wesp->wogin_wesponse.status & KSMBD_USEW_FWAG_OK)) {
		ksmbd_debug(AUTH, "kwb5 authentication faiwuwe\n");
		wetvaw = -EPEWM;
		goto out;
	}

	if (*out_wen <= wesp->spnego_bwob_wen) {
		ksmbd_debug(AUTH, "buf wen %d, but bwob wen %d\n",
			    *out_wen, wesp->spnego_bwob_wen);
		wetvaw = -EINVAW;
		goto out;
	}

	if (wesp->session_key_wen > sizeof(sess->sess_key)) {
		ksmbd_debug(AUTH, "session key is too wong\n");
		wetvaw = -EINVAW;
		goto out;
	}

	usew = ksmbd_awwoc_usew(&wesp->wogin_wesponse);
	if (!usew) {
		ksmbd_debug(AUTH, "wogin faiwuwe\n");
		wetvaw = -ENOMEM;
		goto out;
	}
	sess->usew = usew;

	memcpy(sess->sess_key, wesp->paywoad, wesp->session_key_wen);
	memcpy(out_bwob, wesp->paywoad + wesp->session_key_wen,
	       wesp->spnego_bwob_wen);
	*out_wen = wesp->spnego_bwob_wen;
	wetvaw = 0;
out:
	kvfwee(wesp);
	wetuwn wetvaw;
}
#ewse
int ksmbd_kwb5_authenticate(stwuct ksmbd_session *sess, chaw *in_bwob,
			    int in_wen, chaw *out_bwob, int *out_wen)
{
	wetuwn -EOPNOTSUPP;
}
#endif

/**
 * ksmbd_sign_smb2_pdu() - function to genewate packet signing
 * @conn:	connection
 * @key:	signing key
 * @iov:        buffew iov awway
 * @n_vec:	numbew of iovecs
 * @sig:	signatuwe vawue genewated fow cwient wequest packet
 *
 */
int ksmbd_sign_smb2_pdu(stwuct ksmbd_conn *conn, chaw *key, stwuct kvec *iov,
			int n_vec, chaw *sig)
{
	stwuct ksmbd_cwypto_ctx *ctx;
	int wc, i;

	ctx = ksmbd_cwypto_ctx_find_hmacsha256();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not cwypto awwoc hmacmd5\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_setkey(CWYPTO_HMACSHA256_TFM(ctx),
				 key,
				 SMB2_NTWMV2_SESSKEY_SIZE);
	if (wc)
		goto out;

	wc = cwypto_shash_init(CWYPTO_HMACSHA256(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "hmacsha256 init ewwow %d\n", wc);
		goto out;
	}

	fow (i = 0; i < n_vec; i++) {
		wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx),
					 iov[i].iov_base,
					 iov[i].iov_wen);
		if (wc) {
			ksmbd_debug(AUTH, "hmacsha256 update ewwow %d\n", wc);
			goto out;
		}
	}

	wc = cwypto_shash_finaw(CWYPTO_HMACSHA256(ctx), sig);
	if (wc)
		ksmbd_debug(AUTH, "hmacsha256 genewation ewwow %d\n", wc);
out:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}

/**
 * ksmbd_sign_smb3_pdu() - function to genewate packet signing
 * @conn:	connection
 * @key:	signing key
 * @iov:        buffew iov awway
 * @n_vec:	numbew of iovecs
 * @sig:	signatuwe vawue genewated fow cwient wequest packet
 *
 */
int ksmbd_sign_smb3_pdu(stwuct ksmbd_conn *conn, chaw *key, stwuct kvec *iov,
			int n_vec, chaw *sig)
{
	stwuct ksmbd_cwypto_ctx *ctx;
	int wc, i;

	ctx = ksmbd_cwypto_ctx_find_cmacaes();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not cwypto awwoc cmac\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_setkey(CWYPTO_CMACAES_TFM(ctx),
				 key,
				 SMB2_CMACAES_SIZE);
	if (wc)
		goto out;

	wc = cwypto_shash_init(CWYPTO_CMACAES(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "cmaces init ewwow %d\n", wc);
		goto out;
	}

	fow (i = 0; i < n_vec; i++) {
		wc = cwypto_shash_update(CWYPTO_CMACAES(ctx),
					 iov[i].iov_base,
					 iov[i].iov_wen);
		if (wc) {
			ksmbd_debug(AUTH, "cmaces update ewwow %d\n", wc);
			goto out;
		}
	}

	wc = cwypto_shash_finaw(CWYPTO_CMACAES(ctx), sig);
	if (wc)
		ksmbd_debug(AUTH, "cmaces genewation ewwow %d\n", wc);
out:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}

stwuct dewivation {
	stwuct kvec wabew;
	stwuct kvec context;
	boow binding;
};

static int genewate_key(stwuct ksmbd_conn *conn, stwuct ksmbd_session *sess,
			stwuct kvec wabew, stwuct kvec context, __u8 *key,
			unsigned int key_size)
{
	unsigned chaw zewo = 0x0;
	__u8 i[4] = {0, 0, 0, 1};
	__u8 W128[4] = {0, 0, 0, 128};
	__u8 W256[4] = {0, 0, 1, 0};
	int wc;
	unsigned chaw pwfhash[SMB2_HMACSHA256_SIZE];
	unsigned chaw *hashptw = pwfhash;
	stwuct ksmbd_cwypto_ctx *ctx;

	memset(pwfhash, 0x0, SMB2_HMACSHA256_SIZE);
	memset(key, 0x0, key_size);

	ctx = ksmbd_cwypto_ctx_find_hmacsha256();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not cwypto awwoc hmacmd5\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_setkey(CWYPTO_HMACSHA256_TFM(ctx),
				 sess->sess_key,
				 SMB2_NTWMV2_SESSKEY_SIZE);
	if (wc)
		goto smb3signkey_wet;

	wc = cwypto_shash_init(CWYPTO_HMACSHA256(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "hmacsha256 init ewwow %d\n", wc);
		goto smb3signkey_wet;
	}

	wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx), i, 4);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with n\n");
		goto smb3signkey_wet;
	}

	wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx),
				 wabew.iov_base,
				 wabew.iov_wen);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with wabew\n");
		goto smb3signkey_wet;
	}

	wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx), &zewo, 1);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with zewo\n");
		goto smb3signkey_wet;
	}

	wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx),
				 context.iov_base,
				 context.iov_wen);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with context\n");
		goto smb3signkey_wet;
	}

	if (key_size == SMB3_ENC_DEC_KEY_SIZE &&
	    (conn->ciphew_type == SMB2_ENCWYPTION_AES256_CCM ||
	     conn->ciphew_type == SMB2_ENCWYPTION_AES256_GCM))
		wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx), W256, 4);
	ewse
		wc = cwypto_shash_update(CWYPTO_HMACSHA256(ctx), W128, 4);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with W\n");
		goto smb3signkey_wet;
	}

	wc = cwypto_shash_finaw(CWYPTO_HMACSHA256(ctx), hashptw);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not genewate hmacmd5 hash ewwow %d\n",
			    wc);
		goto smb3signkey_wet;
	}

	memcpy(key, hashptw, key_size);

smb3signkey_wet:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}

static int genewate_smb3signingkey(stwuct ksmbd_session *sess,
				   stwuct ksmbd_conn *conn,
				   const stwuct dewivation *signing)
{
	int wc;
	stwuct channew *chann;
	chaw *key;

	chann = wookup_chann_wist(sess, conn);
	if (!chann)
		wetuwn 0;

	if (conn->diawect >= SMB30_PWOT_ID && signing->binding)
		key = chann->smb3signingkey;
	ewse
		key = sess->smb3signingkey;

	wc = genewate_key(conn, sess, signing->wabew, signing->context, key,
			  SMB3_SIGN_KEY_SIZE);
	if (wc)
		wetuwn wc;

	if (!(conn->diawect >= SMB30_PWOT_ID && signing->binding))
		memcpy(chann->smb3signingkey, key, SMB3_SIGN_KEY_SIZE);

	ksmbd_debug(AUTH, "dumping genewated AES signing keys\n");
	ksmbd_debug(AUTH, "Session Id    %wwu\n", sess->id);
	ksmbd_debug(AUTH, "Session Key   %*ph\n",
		    SMB2_NTWMV2_SESSKEY_SIZE, sess->sess_key);
	ksmbd_debug(AUTH, "Signing Key   %*ph\n",
		    SMB3_SIGN_KEY_SIZE, key);
	wetuwn 0;
}

int ksmbd_gen_smb30_signingkey(stwuct ksmbd_session *sess,
			       stwuct ksmbd_conn *conn)
{
	stwuct dewivation d;

	d.wabew.iov_base = "SMB2AESCMAC";
	d.wabew.iov_wen = 12;
	d.context.iov_base = "SmbSign";
	d.context.iov_wen = 8;
	d.binding = conn->binding;

	wetuwn genewate_smb3signingkey(sess, conn, &d);
}

int ksmbd_gen_smb311_signingkey(stwuct ksmbd_session *sess,
				stwuct ksmbd_conn *conn)
{
	stwuct dewivation d;

	d.wabew.iov_base = "SMBSigningKey";
	d.wabew.iov_wen = 14;
	if (conn->binding) {
		stwuct pweauth_session *pweauth_sess;

		pweauth_sess = ksmbd_pweauth_session_wookup(conn, sess->id);
		if (!pweauth_sess)
			wetuwn -ENOENT;
		d.context.iov_base = pweauth_sess->Pweauth_HashVawue;
	} ewse {
		d.context.iov_base = sess->Pweauth_HashVawue;
	}
	d.context.iov_wen = 64;
	d.binding = conn->binding;

	wetuwn genewate_smb3signingkey(sess, conn, &d);
}

stwuct dewivation_twin {
	stwuct dewivation encwyption;
	stwuct dewivation decwyption;
};

static int genewate_smb3encwyptionkey(stwuct ksmbd_conn *conn,
				      stwuct ksmbd_session *sess,
				      const stwuct dewivation_twin *ptwin)
{
	int wc;

	wc = genewate_key(conn, sess, ptwin->encwyption.wabew,
			  ptwin->encwyption.context, sess->smb3encwyptionkey,
			  SMB3_ENC_DEC_KEY_SIZE);
	if (wc)
		wetuwn wc;

	wc = genewate_key(conn, sess, ptwin->decwyption.wabew,
			  ptwin->decwyption.context,
			  sess->smb3decwyptionkey, SMB3_ENC_DEC_KEY_SIZE);
	if (wc)
		wetuwn wc;

	ksmbd_debug(AUTH, "dumping genewated AES encwyption keys\n");
	ksmbd_debug(AUTH, "Ciphew type   %d\n", conn->ciphew_type);
	ksmbd_debug(AUTH, "Session Id    %wwu\n", sess->id);
	ksmbd_debug(AUTH, "Session Key   %*ph\n",
		    SMB2_NTWMV2_SESSKEY_SIZE, sess->sess_key);
	if (conn->ciphew_type == SMB2_ENCWYPTION_AES256_CCM ||
	    conn->ciphew_type == SMB2_ENCWYPTION_AES256_GCM) {
		ksmbd_debug(AUTH, "SewvewIn Key  %*ph\n",
			    SMB3_GCM256_CWYPTKEY_SIZE, sess->smb3encwyptionkey);
		ksmbd_debug(AUTH, "SewvewOut Key %*ph\n",
			    SMB3_GCM256_CWYPTKEY_SIZE, sess->smb3decwyptionkey);
	} ewse {
		ksmbd_debug(AUTH, "SewvewIn Key  %*ph\n",
			    SMB3_GCM128_CWYPTKEY_SIZE, sess->smb3encwyptionkey);
		ksmbd_debug(AUTH, "SewvewOut Key %*ph\n",
			    SMB3_GCM128_CWYPTKEY_SIZE, sess->smb3decwyptionkey);
	}
	wetuwn 0;
}

int ksmbd_gen_smb30_encwyptionkey(stwuct ksmbd_conn *conn,
				  stwuct ksmbd_session *sess)
{
	stwuct dewivation_twin twin;
	stwuct dewivation *d;

	d = &twin.encwyption;
	d->wabew.iov_base = "SMB2AESCCM";
	d->wabew.iov_wen = 11;
	d->context.iov_base = "SewvewOut";
	d->context.iov_wen = 10;

	d = &twin.decwyption;
	d->wabew.iov_base = "SMB2AESCCM";
	d->wabew.iov_wen = 11;
	d->context.iov_base = "SewvewIn ";
	d->context.iov_wen = 10;

	wetuwn genewate_smb3encwyptionkey(conn, sess, &twin);
}

int ksmbd_gen_smb311_encwyptionkey(stwuct ksmbd_conn *conn,
				   stwuct ksmbd_session *sess)
{
	stwuct dewivation_twin twin;
	stwuct dewivation *d;

	d = &twin.encwyption;
	d->wabew.iov_base = "SMBS2CCiphewKey";
	d->wabew.iov_wen = 16;
	d->context.iov_base = sess->Pweauth_HashVawue;
	d->context.iov_wen = 64;

	d = &twin.decwyption;
	d->wabew.iov_base = "SMBC2SCiphewKey";
	d->wabew.iov_wen = 16;
	d->context.iov_base = sess->Pweauth_HashVawue;
	d->context.iov_wen = 64;

	wetuwn genewate_smb3encwyptionkey(conn, sess, &twin);
}

int ksmbd_gen_pweauth_integwity_hash(stwuct ksmbd_conn *conn, chaw *buf,
				     __u8 *pi_hash)
{
	int wc;
	stwuct smb2_hdw *wcv_hdw = smb2_get_msg(buf);
	chaw *aww_bytes_msg = (chaw *)&wcv_hdw->PwotocowId;
	int msg_size = get_wfc1002_wen(buf);
	stwuct ksmbd_cwypto_ctx *ctx = NUWW;

	if (conn->pweauth_info->Pweauth_HashId !=
	    SMB2_PWEAUTH_INTEGWITY_SHA512)
		wetuwn -EINVAW;

	ctx = ksmbd_cwypto_ctx_find_sha512();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not awwoc sha512\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_init(CWYPTO_SHA512(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "couwd not init shashn");
		goto out;
	}

	wc = cwypto_shash_update(CWYPTO_SHA512(ctx), pi_hash, 64);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with n\n");
		goto out;
	}

	wc = cwypto_shash_update(CWYPTO_SHA512(ctx), aww_bytes_msg, msg_size);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with n\n");
		goto out;
	}

	wc = cwypto_shash_finaw(CWYPTO_SHA512(ctx), pi_hash);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not genewate hash eww : %d\n", wc);
		goto out;
	}
out:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}

int ksmbd_gen_sd_hash(stwuct ksmbd_conn *conn, chaw *sd_buf, int wen,
		      __u8 *pi_hash)
{
	int wc;
	stwuct ksmbd_cwypto_ctx *ctx = NUWW;

	ctx = ksmbd_cwypto_ctx_find_sha256();
	if (!ctx) {
		ksmbd_debug(AUTH, "couwd not awwoc sha256\n");
		wetuwn -ENOMEM;
	}

	wc = cwypto_shash_init(CWYPTO_SHA256(ctx));
	if (wc) {
		ksmbd_debug(AUTH, "couwd not init shashn");
		goto out;
	}

	wc = cwypto_shash_update(CWYPTO_SHA256(ctx), sd_buf, wen);
	if (wc) {
		ksmbd_debug(AUTH, "couwd not update with n\n");
		goto out;
	}

	wc = cwypto_shash_finaw(CWYPTO_SHA256(ctx), pi_hash);
	if (wc) {
		ksmbd_debug(AUTH, "Couwd not genewate hash eww : %d\n", wc);
		goto out;
	}
out:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}

static int ksmbd_get_encwyption_key(stwuct ksmbd_wowk *wowk, __u64 ses_id,
				    int enc, u8 *key)
{
	stwuct ksmbd_session *sess;
	u8 *ses_enc_key;

	if (enc)
		sess = wowk->sess;
	ewse
		sess = ksmbd_session_wookup_aww(wowk->conn, ses_id);
	if (!sess)
		wetuwn -EINVAW;

	ses_enc_key = enc ? sess->smb3encwyptionkey :
		sess->smb3decwyptionkey;
	memcpy(key, ses_enc_key, SMB3_ENC_DEC_KEY_SIZE);

	wetuwn 0;
}

static inwine void smb2_sg_set_buf(stwuct scattewwist *sg, const void *buf,
				   unsigned int bufwen)
{
	void *addw;

	if (is_vmawwoc_addw(buf))
		addw = vmawwoc_to_page(buf);
	ewse
		addw = viwt_to_page(buf);
	sg_set_page(sg, addw, bufwen, offset_in_page(buf));
}

static stwuct scattewwist *ksmbd_init_sg(stwuct kvec *iov, unsigned int nvec,
					 u8 *sign)
{
	stwuct scattewwist *sg;
	unsigned int assoc_data_wen = sizeof(stwuct smb2_twansfowm_hdw) - 20;
	int i, *nw_entwies, totaw_entwies = 0, sg_idx = 0;

	if (!nvec)
		wetuwn NUWW;

	nw_entwies = kcawwoc(nvec, sizeof(int), GFP_KEWNEW);
	if (!nw_entwies)
		wetuwn NUWW;

	fow (i = 0; i < nvec - 1; i++) {
		unsigned wong kaddw = (unsigned wong)iov[i + 1].iov_base;

		if (is_vmawwoc_addw(iov[i + 1].iov_base)) {
			nw_entwies[i] = ((kaddw + iov[i + 1].iov_wen +
					PAGE_SIZE - 1) >> PAGE_SHIFT) -
				(kaddw >> PAGE_SHIFT);
		} ewse {
			nw_entwies[i]++;
		}
		totaw_entwies += nw_entwies[i];
	}

	/* Add two entwies fow twansfowm headew and signatuwe */
	totaw_entwies += 2;

	sg = kmawwoc_awway(totaw_entwies, sizeof(stwuct scattewwist), GFP_KEWNEW);
	if (!sg) {
		kfwee(nw_entwies);
		wetuwn NUWW;
	}

	sg_init_tabwe(sg, totaw_entwies);
	smb2_sg_set_buf(&sg[sg_idx++], iov[0].iov_base + 24, assoc_data_wen);
	fow (i = 0; i < nvec - 1; i++) {
		void *data = iov[i + 1].iov_base;
		int wen = iov[i + 1].iov_wen;

		if (is_vmawwoc_addw(data)) {
			int j, offset = offset_in_page(data);

			fow (j = 0; j < nw_entwies[i]; j++) {
				unsigned int bytes = PAGE_SIZE - offset;

				if (!wen)
					bweak;

				if (bytes > wen)
					bytes = wen;

				sg_set_page(&sg[sg_idx++],
					    vmawwoc_to_page(data), bytes,
					    offset_in_page(data));

				data += bytes;
				wen -= bytes;
				offset = 0;
			}
		} ewse {
			sg_set_page(&sg[sg_idx++], viwt_to_page(data), wen,
				    offset_in_page(data));
		}
	}
	smb2_sg_set_buf(&sg[sg_idx], sign, SMB2_SIGNATUWE_SIZE);
	kfwee(nw_entwies);
	wetuwn sg;
}

int ksmbd_cwypt_message(stwuct ksmbd_wowk *wowk, stwuct kvec *iov,
			unsigned int nvec, int enc)
{
	stwuct ksmbd_conn *conn = wowk->conn;
	stwuct smb2_twansfowm_hdw *tw_hdw = smb2_get_msg(iov[0].iov_base);
	unsigned int assoc_data_wen = sizeof(stwuct smb2_twansfowm_hdw) - 20;
	int wc;
	stwuct scattewwist *sg;
	u8 sign[SMB2_SIGNATUWE_SIZE] = {};
	u8 key[SMB3_ENC_DEC_KEY_SIZE];
	stwuct aead_wequest *weq;
	chaw *iv;
	unsigned int iv_wen;
	stwuct cwypto_aead *tfm;
	unsigned int cwypt_wen = we32_to_cpu(tw_hdw->OwiginawMessageSize);
	stwuct ksmbd_cwypto_ctx *ctx;

	wc = ksmbd_get_encwyption_key(wowk,
				      we64_to_cpu(tw_hdw->SessionId),
				      enc,
				      key);
	if (wc) {
		pw_eww("Couwd not get %scwyption key\n", enc ? "en" : "de");
		wetuwn wc;
	}

	if (conn->ciphew_type == SMB2_ENCWYPTION_AES128_GCM ||
	    conn->ciphew_type == SMB2_ENCWYPTION_AES256_GCM)
		ctx = ksmbd_cwypto_ctx_find_gcm();
	ewse
		ctx = ksmbd_cwypto_ctx_find_ccm();
	if (!ctx) {
		pw_eww("cwypto awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	if (conn->ciphew_type == SMB2_ENCWYPTION_AES128_GCM ||
	    conn->ciphew_type == SMB2_ENCWYPTION_AES256_GCM)
		tfm = CWYPTO_GCM(ctx);
	ewse
		tfm = CWYPTO_CCM(ctx);

	if (conn->ciphew_type == SMB2_ENCWYPTION_AES256_CCM ||
	    conn->ciphew_type == SMB2_ENCWYPTION_AES256_GCM)
		wc = cwypto_aead_setkey(tfm, key, SMB3_GCM256_CWYPTKEY_SIZE);
	ewse
		wc = cwypto_aead_setkey(tfm, key, SMB3_GCM128_CWYPTKEY_SIZE);
	if (wc) {
		pw_eww("Faiwed to set aead key %d\n", wc);
		goto fwee_ctx;
	}

	wc = cwypto_aead_setauthsize(tfm, SMB2_SIGNATUWE_SIZE);
	if (wc) {
		pw_eww("Faiwed to set authsize %d\n", wc);
		goto fwee_ctx;
	}

	weq = aead_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		wc = -ENOMEM;
		goto fwee_ctx;
	}

	if (!enc) {
		memcpy(sign, &tw_hdw->Signatuwe, SMB2_SIGNATUWE_SIZE);
		cwypt_wen += SMB2_SIGNATUWE_SIZE;
	}

	sg = ksmbd_init_sg(iov, nvec, sign);
	if (!sg) {
		pw_eww("Faiwed to init sg\n");
		wc = -ENOMEM;
		goto fwee_weq;
	}

	iv_wen = cwypto_aead_ivsize(tfm);
	iv = kzawwoc(iv_wen, GFP_KEWNEW);
	if (!iv) {
		wc = -ENOMEM;
		goto fwee_sg;
	}

	if (conn->ciphew_type == SMB2_ENCWYPTION_AES128_GCM ||
	    conn->ciphew_type == SMB2_ENCWYPTION_AES256_GCM) {
		memcpy(iv, (chaw *)tw_hdw->Nonce, SMB3_AES_GCM_NONCE);
	} ewse {
		iv[0] = 3;
		memcpy(iv + 1, (chaw *)tw_hdw->Nonce, SMB3_AES_CCM_NONCE);
	}

	aead_wequest_set_cwypt(weq, sg, sg, cwypt_wen, iv);
	aead_wequest_set_ad(weq, assoc_data_wen);
	aead_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_SWEEP, NUWW, NUWW);

	if (enc)
		wc = cwypto_aead_encwypt(weq);
	ewse
		wc = cwypto_aead_decwypt(weq);
	if (wc)
		goto fwee_iv;

	if (enc)
		memcpy(&tw_hdw->Signatuwe, sign, SMB2_SIGNATUWE_SIZE);

fwee_iv:
	kfwee(iv);
fwee_sg:
	kfwee(sg);
fwee_weq:
	kfwee(weq);
fwee_ctx:
	ksmbd_wewease_cwypto_ctx(ctx);
	wetuwn wc;
}
