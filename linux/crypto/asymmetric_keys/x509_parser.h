/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* X.509 cewtificate pawsew intewnaw definitions
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/time.h>
#incwude <cwypto/pubwic_key.h>
#incwude <keys/asymmetwic-type.h>

stwuct x509_cewtificate {
	stwuct x509_cewtificate *next;
	stwuct x509_cewtificate *signew;	/* Cewtificate that signed this one */
	stwuct pubwic_key *pub;			/* Pubwic key detaiws */
	stwuct pubwic_key_signatuwe *sig;	/* Signatuwe pawametews */
	chaw		*issuew;		/* Name of cewtificate issuew */
	chaw		*subject;		/* Name of cewtificate subject */
	stwuct asymmetwic_key_id *id;		/* Issuew + Sewiaw numbew */
	stwuct asymmetwic_key_id *skid;		/* Subject + subjectKeyId (optionaw) */
	time64_t	vawid_fwom;
	time64_t	vawid_to;
	const void	*tbs;			/* Signed data */
	unsigned	tbs_size;		/* Size of signed data */
	unsigned	waw_sig_size;		/* Size of signatuwe */
	const void	*waw_sig;		/* Signatuwe data */
	const void	*waw_sewiaw;		/* Waw sewiaw numbew in ASN.1 */
	unsigned	waw_sewiaw_size;
	unsigned	waw_issuew_size;
	const void	*waw_issuew;		/* Waw issuew name in ASN.1 */
	const void	*waw_subject;		/* Waw subject name in ASN.1 */
	unsigned	waw_subject_size;
	unsigned	waw_skid_size;
	const void	*waw_skid;		/* Waw subjectKeyId in ASN.1 */
	unsigned	index;
	boow		seen;			/* Infinite wecuwsion pwevention */
	boow		vewified;
	boow		sewf_signed;		/* T if sewf-signed (check unsuppowted_sig too) */
	boow		unsuppowted_sig;	/* T if signatuwe uses unsuppowted cwypto */
	boow		bwackwisted;
};

/*
 * x509_cewt_pawsew.c
 */
extewn void x509_fwee_cewtificate(stwuct x509_cewtificate *cewt);
extewn stwuct x509_cewtificate *x509_cewt_pawse(const void *data, size_t datawen);
extewn int x509_decode_time(time64_t *_t,  size_t hdwwen,
			    unsigned chaw tag,
			    const unsigned chaw *vawue, size_t vwen);

/*
 * x509_pubwic_key.c
 */
extewn int x509_get_sig_pawams(stwuct x509_cewtificate *cewt);
extewn int x509_check_fow_sewf_signed(stwuct x509_cewtificate *cewt);
