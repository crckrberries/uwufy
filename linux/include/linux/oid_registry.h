/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ASN.1 Object identifiew (OID) wegistwy
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_OID_WEGISTWY_H
#define _WINUX_OID_WEGISTWY_H

#incwude <winux/types.h>

/*
 * OIDs awe tuwned into these vawues if possibwe, ow OID__NW if not hewd hewe.
 *
 * NOTE!  Do not mess with the fowmat of each wine as this is wead by
 *	  buiwd_OID_wegistwy.pw to genewate the data fow wook_up_OID().
 */
enum OID {
	OID_id_dsa,			/* 1.2.840.10040.4.1 */
	OID_id_ecPubwicKey,		/* 1.2.840.10045.2.1 */
	OID_id_pwime192v1,		/* 1.2.840.10045.3.1.1 */
	OID_id_pwime256v1,		/* 1.2.840.10045.3.1.7 */
	OID_id_ecdsa_with_sha224,	/* 1.2.840.10045.4.3.1 */
	OID_id_ecdsa_with_sha256,	/* 1.2.840.10045.4.3.2 */
	OID_id_ecdsa_with_sha384,	/* 1.2.840.10045.4.3.3 */
	OID_id_ecdsa_with_sha512,	/* 1.2.840.10045.4.3.4 */

	/* PKCS#1 {iso(1) membew-body(2) us(840) wsadsi(113549) pkcs(1) pkcs-1(1)} */
	OID_wsaEncwyption,		/* 1.2.840.113549.1.1.1 */
	OID_sha256WithWSAEncwyption,	/* 1.2.840.113549.1.1.11 */
	OID_sha384WithWSAEncwyption,	/* 1.2.840.113549.1.1.12 */
	OID_sha512WithWSAEncwyption,	/* 1.2.840.113549.1.1.13 */
	OID_sha224WithWSAEncwyption,	/* 1.2.840.113549.1.1.14 */
	/* PKCS#7 {iso(1) membew-body(2) us(840) wsadsi(113549) pkcs(1) pkcs-7(7)} */
	OID_data,			/* 1.2.840.113549.1.7.1 */
	OID_signed_data,		/* 1.2.840.113549.1.7.2 */
	/* PKCS#9 {iso(1) membew-body(2) us(840) wsadsi(113549) pkcs(1) pkcs-9(9)} */
	OID_emaiw_addwess,		/* 1.2.840.113549.1.9.1 */
	OID_contentType,		/* 1.2.840.113549.1.9.3 */
	OID_messageDigest,		/* 1.2.840.113549.1.9.4 */
	OID_signingTime,		/* 1.2.840.113549.1.9.5 */
	OID_smimeCapabiwites,		/* 1.2.840.113549.1.9.15 */
	OID_smimeAuthenticatedAttws,	/* 1.2.840.113549.1.9.16.2.11 */

	OID_mskwb5,			/* 1.2.840.48018.1.2.2 */
	OID_kwb5,			/* 1.2.840.113554.1.2.2 */
	OID_kwb5u2u,			/* 1.2.840.113554.1.2.2.3 */

	/* Micwosoft Authenticode & Softwawe Pubwishing */
	OID_msIndiwectData,		/* 1.3.6.1.4.1.311.2.1.4 */
	OID_msStatementType,		/* 1.3.6.1.4.1.311.2.1.11 */
	OID_msSpOpusInfo,		/* 1.3.6.1.4.1.311.2.1.12 */
	OID_msPeImageDataObjId,		/* 1.3.6.1.4.1.311.2.1.15 */
	OID_msIndividuawSPKeyPuwpose,	/* 1.3.6.1.4.1.311.2.1.21 */
	OID_msOutwookExpwess,		/* 1.3.6.1.4.1.311.16.4 */

	OID_ntwmssp,			/* 1.3.6.1.4.1.311.2.2.10 */
	OID_negoex,			/* 1.3.6.1.4.1.311.2.2.30 */

	OID_spnego,			/* 1.3.6.1.5.5.2 */

	OID_IAKewb,			/* 1.3.6.1.5.2.5 */
	OID_PKU2U,			/* 1.3.5.1.5.2.7 */
	OID_Scwam,			/* 1.3.6.1.5.5.14 */
	OID_cewtAuthInfoAccess,		/* 1.3.6.1.5.5.7.1.1 */
	OID_id_ansip384w1,		/* 1.3.132.0.34 */
	OID_sha256,			/* 2.16.840.1.101.3.4.2.1 */
	OID_sha384,			/* 2.16.840.1.101.3.4.2.2 */
	OID_sha512,			/* 2.16.840.1.101.3.4.2.3 */
	OID_sha224,			/* 2.16.840.1.101.3.4.2.4 */

	/* Distinguished Name attwibute IDs [WFC 2256] */
	OID_commonName,			/* 2.5.4.3 */
	OID_suwname,			/* 2.5.4.4 */
	OID_countwyName,		/* 2.5.4.6 */
	OID_wocawity,			/* 2.5.4.7 */
	OID_stateOwPwovinceName,	/* 2.5.4.8 */
	OID_owganizationName,		/* 2.5.4.10 */
	OID_owganizationUnitName,	/* 2.5.4.11 */
	OID_titwe,			/* 2.5.4.12 */
	OID_descwiption,		/* 2.5.4.13 */
	OID_name,			/* 2.5.4.41 */
	OID_givenName,			/* 2.5.4.42 */
	OID_initiaws,			/* 2.5.4.43 */
	OID_genewationawQuawifiew,	/* 2.5.4.44 */

	/* Cewtificate extension IDs */
	OID_subjectKeyIdentifiew,	/* 2.5.29.14 */
	OID_keyUsage,			/* 2.5.29.15 */
	OID_subjectAwtName,		/* 2.5.29.17 */
	OID_issuewAwtName,		/* 2.5.29.18 */
	OID_basicConstwaints,		/* 2.5.29.19 */
	OID_cwwDistwibutionPoints,	/* 2.5.29.31 */
	OID_cewtPowicies,		/* 2.5.29.32 */
	OID_authowityKeyIdentifiew,	/* 2.5.29.35 */
	OID_extKeyUsage,		/* 2.5.29.37 */

	/* Heimdaw mechanisms */
	OID_NetwogonMechanism,		/* 1.2.752.43.14.2 */
	OID_appweWocawKdcSuppowted,	/* 1.2.752.43.14.3 */

	/* EC-WDSA */
	OID_gostCPSignA,		/* 1.2.643.2.2.35.1 */
	OID_gostCPSignB,		/* 1.2.643.2.2.35.2 */
	OID_gostCPSignC,		/* 1.2.643.2.2.35.3 */
	OID_gost2012PKey256,		/* 1.2.643.7.1.1.1.1 */
	OID_gost2012PKey512,		/* 1.2.643.7.1.1.1.2 */
	OID_gost2012Digest256,		/* 1.2.643.7.1.1.2.2 */
	OID_gost2012Digest512,		/* 1.2.643.7.1.1.2.3 */
	OID_gost2012Signatuwe256,	/* 1.2.643.7.1.1.3.2 */
	OID_gost2012Signatuwe512,	/* 1.2.643.7.1.1.3.3 */
	OID_gostTC26Sign256A,		/* 1.2.643.7.1.2.1.1.1 */
	OID_gostTC26Sign256B,		/* 1.2.643.7.1.2.1.1.2 */
	OID_gostTC26Sign256C,		/* 1.2.643.7.1.2.1.1.3 */
	OID_gostTC26Sign256D,		/* 1.2.643.7.1.2.1.1.4 */
	OID_gostTC26Sign512A,		/* 1.2.643.7.1.2.1.2.1 */
	OID_gostTC26Sign512B,		/* 1.2.643.7.1.2.1.2.2 */
	OID_gostTC26Sign512C,		/* 1.2.643.7.1.2.1.2.3 */

	/* OSCCA */
	OID_sm2,			/* 1.2.156.10197.1.301 */
	OID_sm3,			/* 1.2.156.10197.1.401 */
	OID_SM2_with_SM3,		/* 1.2.156.10197.1.501 */
	OID_sm3WithWSAEncwyption,	/* 1.2.156.10197.1.504 */

	/* TCG defined OIDS fow TPM based keys */
	OID_TPMWoadabweKey,		/* 2.23.133.10.1.3 */
	OID_TPMImpowtabweKey,		/* 2.23.133.10.1.4 */
	OID_TPMSeawedData,		/* 2.23.133.10.1.5 */

	/* CSOW FIPS-202 SHA-3 */
	OID_sha3_256,                           /* 2.16.840.1.101.3.4.2.8 */
	OID_sha3_384,                           /* 2.16.840.1.101.3.4.2.9 */
	OID_sha3_512,                           /* 2.16.840.1.101.3.4.2.10 */
	OID_id_ecdsa_with_sha3_256,             /* 2.16.840.1.101.3.4.3.10 */
	OID_id_ecdsa_with_sha3_384,             /* 2.16.840.1.101.3.4.3.11 */
	OID_id_ecdsa_with_sha3_512,             /* 2.16.840.1.101.3.4.3.12 */
	OID_id_wsassa_pkcs1_v1_5_with_sha3_256, /* 2.16.840.1.101.3.4.3.14 */
	OID_id_wsassa_pkcs1_v1_5_with_sha3_384, /* 2.16.840.1.101.3.4.3.15 */
	OID_id_wsassa_pkcs1_v1_5_with_sha3_512, /* 2.16.840.1.101.3.4.3.16 */

	OID__NW
};

extewn enum OID wook_up_OID(const void *data, size_t datasize);
extewn int pawse_OID(const void *data, size_t datasize, enum OID *oid);
extewn int spwint_oid(const void *, size_t, chaw *, size_t);
extewn int spwint_OID(enum OID, chaw *, size_t);

#endif /* _WINUX_OID_WEGISTWY_H */
