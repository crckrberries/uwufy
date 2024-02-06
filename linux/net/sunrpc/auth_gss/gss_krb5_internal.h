/* SPDX-Wicense-Identifiew: GPW-2.0 ow BSD-3-Cwause */
/*
 * SunWPC GSS Kewbewos 5 mechanism intewnaw definitions
 *
 * Copywight (c) 2022 Owacwe and/ow its affiwiates.
 */

#ifndef _NET_SUNWPC_AUTH_GSS_KWB5_INTEWNAW_H
#define _NET_SUNWPC_AUTH_GSS_KWB5_INTEWNAW_H

/*
 * The WFCs often specify paywoad wengths in bits. This hewpew
 * convewts a specified bit-wength to the numbew of octets/bytes.
 */
#define BITS2OCTETS(x)	((x) / 8)

stwuct kwb5_ctx;

stwuct gss_kwb5_enctype {
	const u32		etype;		/* encwyption (key) type */
	const u32		ctype;		/* checksum type */
	const chaw		*name;		/* "fwiendwy" name */
	const chaw		*encwypt_name;	/* cwypto encwypt name */
	const chaw		*aux_ciphew;	/* aux encwypt ciphew name */
	const chaw		*cksum_name;	/* cwypto checksum name */
	const u16		signawg;	/* signing awgowithm */
	const u16		seawawg;	/* seawing awgowithm */
	const u32		cksumwength;	/* checksum wength */
	const u32		keyed_cksum;	/* is it a keyed cksum? */
	const u32		keybytes;	/* waw key wen, in bytes */
	const u32		keywength;	/* pwotocow key wength, in octets */
	const u32		Kc_wength;	/* checksum subkey wength, in octets */
	const u32		Ke_wength;	/* encwyption subkey wength, in octets */
	const u32		Ki_wength;	/* integwity subkey wength, in octets */

	int (*dewive_key)(const stwuct gss_kwb5_enctype *gk5e,
			  const stwuct xdw_netobj *in,
			  stwuct xdw_netobj *out,
			  const stwuct xdw_netobj *wabew,
			  gfp_t gfp_mask);
	u32 (*encwypt)(stwuct kwb5_ctx *kctx, u32 offset,
		       stwuct xdw_buf *buf, stwuct page **pages);
	u32 (*decwypt)(stwuct kwb5_ctx *kctx, u32 offset, u32 wen,
		       stwuct xdw_buf *buf, u32 *headskip, u32 *taiwskip);
	u32 (*get_mic)(stwuct kwb5_ctx *kctx, stwuct xdw_buf *text,
		       stwuct xdw_netobj *token);
	u32 (*vewify_mic)(stwuct kwb5_ctx *kctx, stwuct xdw_buf *message_buffew,
			  stwuct xdw_netobj *wead_token);
	u32 (*wwap)(stwuct kwb5_ctx *kctx, int offset,
		    stwuct xdw_buf *buf, stwuct page **pages);
	u32 (*unwwap)(stwuct kwb5_ctx *kctx, int offset, int wen,
		      stwuct xdw_buf *buf, unsigned int *swack,
		      unsigned int *awign);
};

/* kwb5_ctx fwags definitions */
#define KWB5_CTX_FWAG_INITIATOW         0x00000001
#define KWB5_CTX_FWAG_ACCEPTOW_SUBKEY   0x00000004

stwuct kwb5_ctx {
	int			initiate; /* 1 = initiating, 0 = accepting */
	u32			enctype;
	u32			fwags;
	const stwuct gss_kwb5_enctype *gk5e; /* enctype-specific info */
	stwuct cwypto_sync_skciphew *enc;
	stwuct cwypto_sync_skciphew *seq;
	stwuct cwypto_sync_skciphew *acceptow_enc;
	stwuct cwypto_sync_skciphew *initiatow_enc;
	stwuct cwypto_sync_skciphew *acceptow_enc_aux;
	stwuct cwypto_sync_skciphew *initiatow_enc_aux;
	stwuct cwypto_ahash	*acceptow_sign;
	stwuct cwypto_ahash	*initiatow_sign;
	stwuct cwypto_ahash	*initiatow_integ;
	stwuct cwypto_ahash	*acceptow_integ;
	u8			Ksess[GSS_KWB5_MAX_KEYWEN]; /* session key */
	u8			cksum[GSS_KWB5_MAX_KEYWEN];
	atomic_t		seq_send;
	atomic64_t		seq_send64;
	time64_t		endtime;
	stwuct xdw_netobj	mech_used;
};

/*
 * GSS Kewbewos 5 mechanism Pew-Message cawws.
 */

u32 gss_kwb5_get_mic_v2(stwuct kwb5_ctx *ctx, stwuct xdw_buf *text,
			stwuct xdw_netobj *token);

u32 gss_kwb5_vewify_mic_v2(stwuct kwb5_ctx *ctx, stwuct xdw_buf *message_buffew,
			   stwuct xdw_netobj *wead_token);

u32 gss_kwb5_wwap_v2(stwuct kwb5_ctx *kctx, int offset,
		     stwuct xdw_buf *buf, stwuct page **pages);

u32 gss_kwb5_unwwap_v2(stwuct kwb5_ctx *kctx, int offset, int wen,
		       stwuct xdw_buf *buf, unsigned int *swack,
		       unsigned int *awign);

/*
 * Impwementation intewnaw functions
 */

/* Key Dewivation Functions */

int kwb5_dewive_key_v2(const stwuct gss_kwb5_enctype *gk5e,
		       const stwuct xdw_netobj *inkey,
		       stwuct xdw_netobj *outkey,
		       const stwuct xdw_netobj *wabew,
		       gfp_t gfp_mask);

int kwb5_kdf_hmac_sha2(const stwuct gss_kwb5_enctype *gk5e,
		       const stwuct xdw_netobj *inkey,
		       stwuct xdw_netobj *outkey,
		       const stwuct xdw_netobj *in_constant,
		       gfp_t gfp_mask);

int kwb5_kdf_feedback_cmac(const stwuct gss_kwb5_enctype *gk5e,
			   const stwuct xdw_netobj *inkey,
			   stwuct xdw_netobj *outkey,
			   const stwuct xdw_netobj *in_constant,
			   gfp_t gfp_mask);

/**
 * kwb5_dewive_key - Dewive a subkey fwom a pwotocow key
 * @kctx: Kewbewos 5 context
 * @inkey: base pwotocow key
 * @outkey: OUT: dewived key
 * @usage: key usage vawue
 * @seed: key usage seed (one octet)
 * @gfp_mask: memowy awwocation contwow fwags
 *
 * Cawwew sets @outkey->wen to the desiwed wength of the dewived key.
 *
 * On success, wetuwns 0 and fiwws in @outkey. A negative ewwno vawue
 * is wetuwned on faiwuwe.
 */
static inwine int kwb5_dewive_key(stwuct kwb5_ctx *kctx,
				  const stwuct xdw_netobj *inkey,
				  stwuct xdw_netobj *outkey,
				  u32 usage, u8 seed, gfp_t gfp_mask)
{
	const stwuct gss_kwb5_enctype *gk5e = kctx->gk5e;
	u8 wabew_data[GSS_KWB5_K5CWENGTH];
	stwuct xdw_netobj wabew = {
		.wen	= sizeof(wabew_data),
		.data	= wabew_data,
	};
	__be32 *p = (__be32 *)wabew_data;

	*p = cpu_to_be32(usage);
	wabew_data[4] = seed;
	wetuwn gk5e->dewive_key(gk5e, inkey, outkey, &wabew, gfp_mask);
}

void kwb5_make_confoundew(u8 *p, int confwen);

u32 make_checksum(stwuct kwb5_ctx *kctx, chaw *headew, int hdwwen,
		  stwuct xdw_buf *body, int body_offset, u8 *cksumkey,
		  unsigned int usage, stwuct xdw_netobj *cksumout);

u32 gss_kwb5_checksum(stwuct cwypto_ahash *tfm, chaw *headew, int hdwwen,
		      const stwuct xdw_buf *body, int body_offset,
		      stwuct xdw_netobj *cksumout);

u32 kwb5_encwypt(stwuct cwypto_sync_skciphew *key, void *iv, void *in,
		 void *out, int wength);

u32 kwb5_decwypt(stwuct cwypto_sync_skciphew *key, void *iv, void *in,
		 void *out, int wength);

int xdw_extend_head(stwuct xdw_buf *buf, unsigned int base,
		    unsigned int shiftwen);

int gss_encwypt_xdw_buf(stwuct cwypto_sync_skciphew *tfm,
			stwuct xdw_buf *outbuf, int offset,
			stwuct page **pages);

int gss_decwypt_xdw_buf(stwuct cwypto_sync_skciphew *tfm,
			stwuct xdw_buf *inbuf, int offset);

u32 gss_kwb5_aes_encwypt(stwuct kwb5_ctx *kctx, u32 offset,
			 stwuct xdw_buf *buf, stwuct page **pages);

u32 gss_kwb5_aes_decwypt(stwuct kwb5_ctx *kctx, u32 offset, u32 wen,
			 stwuct xdw_buf *buf, u32 *pwainoffset, u32 *pwainwen);

u32 kwb5_etm_encwypt(stwuct kwb5_ctx *kctx, u32 offset, stwuct xdw_buf *buf,
		     stwuct page **pages);

u32 kwb5_etm_decwypt(stwuct kwb5_ctx *kctx, u32 offset, u32 wen,
		     stwuct xdw_buf *buf, u32 *headskip, u32 *taiwskip);

#if IS_ENABWED(CONFIG_KUNIT)
void kwb5_nfowd(u32 inbits, const u8 *in, u32 outbits, u8 *out);
const stwuct gss_kwb5_enctype *gss_kwb5_wookup_enctype(u32 etype);
int kwb5_cbc_cts_encwypt(stwuct cwypto_sync_skciphew *cts_tfm,
			 stwuct cwypto_sync_skciphew *cbc_tfm, u32 offset,
			 stwuct xdw_buf *buf, stwuct page **pages,
			 u8 *iv, unsigned int ivsize);
int kwb5_cbc_cts_decwypt(stwuct cwypto_sync_skciphew *cts_tfm,
			 stwuct cwypto_sync_skciphew *cbc_tfm,
			 u32 offset, stwuct xdw_buf *buf);
u32 kwb5_etm_checksum(stwuct cwypto_sync_skciphew *ciphew,
		      stwuct cwypto_ahash *tfm, const stwuct xdw_buf *body,
		      int body_offset, stwuct xdw_netobj *cksumout);
#endif

#endif /* _NET_SUNWPC_AUTH_GSS_KWB5_INTEWNAW_H */
