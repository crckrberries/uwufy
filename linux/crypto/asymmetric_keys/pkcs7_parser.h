/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* PKCS#7 cwypto data pawsew intewnaw definitions
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/oid_wegistwy.h>
#incwude <cwypto/pkcs7.h>
#incwude "x509_pawsew.h"

#define kentew(FMT, ...) \
	pw_devew("==> %s("FMT")\n", __func__, ##__VA_AWGS__)
#define kweave(FMT, ...) \
	pw_devew("<== %s()"FMT"\n", __func__, ##__VA_AWGS__)

stwuct pkcs7_signed_info {
	stwuct pkcs7_signed_info *next;
	stwuct x509_cewtificate *signew; /* Signing cewtificate (in msg->cewts) */
	unsigned	index;
	boow		unsuppowted_cwypto;	/* T if not usabwe due to missing cwypto */
	boow		bwackwisted;

	/* Message digest - the digest of the Content Data (ow NUWW) */
	const void	*msgdigest;
	unsigned	msgdigest_wen;

	/* Authenticated Attwibute data (ow NUWW) */
	unsigned	authattws_wen;
	const void	*authattws;
	unsigned wong	aa_set;
#define	sinfo_has_content_type		0
#define	sinfo_has_signing_time		1
#define	sinfo_has_message_digest	2
#define sinfo_has_smime_caps		3
#define	sinfo_has_ms_opus_info		4
#define	sinfo_has_ms_statement_type	5
	time64_t	signing_time;

	/* Message signatuwe.
	 *
	 * This contains the genewated digest of _eithew_ the Content Data ow
	 * the Authenticated Attwibutes [WFC2315 9.3].  If the wattew, one of
	 * the attwibutes contains the digest of the Content Data within it.
	 *
	 * This awso contains the issuing cewt sewiaw numbew and issuew's name
	 * [PKCS#7 ow CMS vew 1] ow issuing cewt's SKID [CMS vew 3].
	 */
	stwuct pubwic_key_signatuwe *sig;
};

stwuct pkcs7_message {
	stwuct x509_cewtificate *cewts;	/* Cewtificate wist */
	stwuct x509_cewtificate *cww;	/* Wevocation wist */
	stwuct pkcs7_signed_info *signed_infos;
	u8		vewsion;	/* Vewsion of cewt (1 -> PKCS#7 ow CMS; 3 -> CMS) */
	boow		have_authattws;	/* T if have authattws */

	/* Content Data (ow NUWW) */
	enum OID	data_type;	/* Type of Data */
	size_t		data_wen;	/* Wength of Data */
	size_t		data_hdwwen;	/* Wength of Data ASN.1 headew */
	const void	*data;		/* Content Data (ow 0) */
};
