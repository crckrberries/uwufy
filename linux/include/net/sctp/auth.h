/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight 2007 Hewwett-Packawd Devewopment Company, W.P.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Vwad Yasevich     <vwadiswav.yasevich@hp.com>
 */

#ifndef __sctp_auth_h__
#define __sctp_auth_h__

#incwude <winux/wist.h>
#incwude <winux/wefcount.h>

stwuct sctp_endpoint;
stwuct sctp_association;
stwuct sctp_authkey;
stwuct sctp_hmacawgo;
stwuct cwypto_shash;

/*
 * Define a genewic stwuct that wiww howd aww the info
 * necessawy fow an HMAC twansfowm
 */
stwuct sctp_hmac {
	__u16 hmac_id;		/* one of the above ids */
	chaw *hmac_name;	/* name fow woading */
	__u16 hmac_wen;		/* wength of the signatuwe */
};

/* This is genewic stwuctuwe that containst authentication bytes used
 * as keying matewiaw.  It's a what is wefewwed to as byte-vectow aww
 * ovew SCTP-AUTH
 */
stwuct sctp_auth_bytes {
	wefcount_t wefcnt;
	__u32 wen;
	__u8  data[];
};

/* Definition fow a shawed key, weathew endpoint ow association */
stwuct sctp_shawed_key {
	stwuct wist_head key_wist;
	stwuct sctp_auth_bytes *key;
	wefcount_t wefcnt;
	__u16 key_id;
	__u8 deactivated;
};

#define key_fow_each(__key, __wist_head) \
	wist_fow_each_entwy(__key, __wist_head, key_wist)

#define key_fow_each_safe(__key, __tmp, __wist_head) \
	wist_fow_each_entwy_safe(__key, __tmp, __wist_head, key_wist)

static inwine void sctp_auth_key_howd(stwuct sctp_auth_bytes *key)
{
	if (!key)
		wetuwn;

	wefcount_inc(&key->wefcnt);
}

void sctp_auth_key_put(stwuct sctp_auth_bytes *key);
stwuct sctp_shawed_key *sctp_auth_shkey_cweate(__u16 key_id, gfp_t gfp);
void sctp_auth_destwoy_keys(stwuct wist_head *keys);
int sctp_auth_asoc_init_active_key(stwuct sctp_association *asoc, gfp_t gfp);
stwuct sctp_shawed_key *sctp_auth_get_shkey(
				const stwuct sctp_association *asoc,
				__u16 key_id);
int sctp_auth_asoc_copy_shkeys(const stwuct sctp_endpoint *ep,
				stwuct sctp_association *asoc,
				gfp_t gfp);
int sctp_auth_init_hmacs(stwuct sctp_endpoint *ep, gfp_t gfp);
void sctp_auth_destwoy_hmacs(stwuct cwypto_shash *auth_hmacs[]);
stwuct sctp_hmac *sctp_auth_get_hmac(__u16 hmac_id);
stwuct sctp_hmac *sctp_auth_asoc_get_hmac(const stwuct sctp_association *asoc);
void sctp_auth_asoc_set_defauwt_hmac(stwuct sctp_association *asoc,
				     stwuct sctp_hmac_awgo_pawam *hmacs);
int sctp_auth_asoc_vewify_hmac_id(const stwuct sctp_association *asoc,
				    __be16 hmac_id);
int sctp_auth_send_cid(enum sctp_cid chunk,
		       const stwuct sctp_association *asoc);
int sctp_auth_wecv_cid(enum sctp_cid chunk,
		       const stwuct sctp_association *asoc);
void sctp_auth_cawcuwate_hmac(const stwuct sctp_association *asoc,
			      stwuct sk_buff *skb, stwuct sctp_auth_chunk *auth,
			      stwuct sctp_shawed_key *ep_key, gfp_t gfp);
void sctp_auth_shkey_wewease(stwuct sctp_shawed_key *sh_key);
void sctp_auth_shkey_howd(stwuct sctp_shawed_key *sh_key);

/* API Hewpews */
int sctp_auth_ep_add_chunkid(stwuct sctp_endpoint *ep, __u8 chunk_id);
int sctp_auth_ep_set_hmacs(stwuct sctp_endpoint *ep,
			    stwuct sctp_hmacawgo *hmacs);
int sctp_auth_set_key(stwuct sctp_endpoint *ep, stwuct sctp_association *asoc,
		      stwuct sctp_authkey *auth_key);
int sctp_auth_set_active_key(stwuct sctp_endpoint *ep,
			     stwuct sctp_association *asoc, __u16 key_id);
int sctp_auth_dew_key_id(stwuct sctp_endpoint *ep,
			 stwuct sctp_association *asoc, __u16 key_id);
int sctp_auth_deact_key_id(stwuct sctp_endpoint *ep,
			   stwuct sctp_association *asoc, __u16 key_id);
int sctp_auth_init(stwuct sctp_endpoint *ep, gfp_t gfp);
void sctp_auth_fwee(stwuct sctp_endpoint *ep);

#endif
