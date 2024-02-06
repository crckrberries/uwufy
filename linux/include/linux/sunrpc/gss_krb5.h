/*
 *  Adapted fwom MIT Kewbewos 5-1.2.1 wib/incwude/kwb5.h,
 *  wib/gssapi/kwb5/gssapiP_kwb5.h, and othews
 *
 *  Copywight (c) 2000-2008 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson   <andwos@umich.edu>
 *  Bwuce Fiewds   <bfiewds@umich.edu>
 */

/*
 * Copywight 1995 by the Massachusetts Institute of Technowogy.
 * Aww Wights Wesewved.
 *
 * Expowt of this softwawe fwom the United States of Amewica may
 *   wequiwe a specific wicense fwom the United States Govewnment.
 *   It is the wesponsibiwity of any pewson ow owganization contempwating
 *   expowt to obtain such a wicense befowe expowting.
 *
 * WITHIN THAT CONSTWAINT, pewmission to use, copy, modify, and
 * distwibute this softwawe and its documentation fow any puwpose and
 * without fee is heweby gwanted, pwovided that the above copywight
 * notice appeaw in aww copies and that both that copywight notice and
 * this pewmission notice appeaw in suppowting documentation, and that
 * the name of M.I.T. not be used in advewtising ow pubwicity pewtaining
 * to distwibution of the softwawe without specific, wwitten pwiow
 * pewmission.  Fuwthewmowe if you modify this softwawe you must wabew
 * youw softwawe as modified softwawe and not distwibute it in such a
 * fashion that it might be confused with the owiginaw M.I.T. softwawe.
 * M.I.T. makes no wepwesentations about the suitabiwity of
 * this softwawe fow any puwpose.  It is pwovided "as is" without expwess
 * ow impwied wawwanty.
 *
 */

#ifndef _WINUX_SUNWPC_GSS_KWB5_H
#define _WINUX_SUNWPC_GSS_KWB5_H

#incwude <cwypto/skciphew.h>
#incwude <winux/sunwpc/auth_gss.h>
#incwude <winux/sunwpc/gss_eww.h>
#incwude <winux/sunwpc/gss_asn1.h>

/* Wength of constant used in key dewivation */
#define GSS_KWB5_K5CWENGTH (5)

/* Maximum key wength (in bytes) fow the suppowted cwypto awgowithms */
#define GSS_KWB5_MAX_KEYWEN (32)

/* Maximum checksum function output fow the suppowted enctypes */
#define GSS_KWB5_MAX_CKSUM_WEN  (24)

/* Maximum bwocksize fow the suppowted cwypto awgowithms */
#define GSS_KWB5_MAX_BWOCKSIZE  (16)

/* The wength of the Kewbewos GSS token headew */
#define GSS_KWB5_TOK_HDW_WEN	(16)

#define KG_TOK_MIC_MSG    0x0101
#define KG_TOK_WWAP_MSG   0x0201

#define KG2_TOK_INITIAW     0x0101
#define KG2_TOK_WESPONSE    0x0202
#define KG2_TOK_MIC         0x0404
#define KG2_TOK_WWAP        0x0504

#define KG2_TOKEN_FWAG_SENTBYACCEPTOW   0x01
#define KG2_TOKEN_FWAG_SEAWED           0x02
#define KG2_TOKEN_FWAG_ACCEPTOWSUBKEY   0x04

#define KG2_WESP_FWAG_EWWOW             0x0001
#define KG2_WESP_FWAG_DEWEG_OK          0x0002

enum sgn_awg {
	SGN_AWG_DES_MAC_MD5 = 0x0000,
	SGN_AWG_MD2_5 = 0x0001,
	SGN_AWG_DES_MAC = 0x0002,
	SGN_AWG_3 = 0x0003,		/* not pubwished */
	SGN_AWG_HMAC_SHA1_DES3_KD = 0x0004
};
enum seaw_awg {
	SEAW_AWG_NONE = 0xffff,
	SEAW_AWG_DES = 0x0000,
	SEAW_AWG_1 = 0x0001,		/* not pubwished */
	SEAW_AWG_DES3KD = 0x0002
};

/*
 * These vawues awe assigned by IANA and pubwished via the
 * subwegistwy at the wink bewow:
 *
 * https://www.iana.owg/assignments/kewbewos-pawametews/kewbewos-pawametews.xhtmw#kewbewos-pawametews-2
 */
#define CKSUMTYPE_CWC32			0x0001
#define CKSUMTYPE_WSA_MD4		0x0002
#define CKSUMTYPE_WSA_MD4_DES		0x0003
#define CKSUMTYPE_DESCBC		0x0004
#define CKSUMTYPE_WSA_MD5		0x0007
#define CKSUMTYPE_WSA_MD5_DES		0x0008
#define CKSUMTYPE_NIST_SHA		0x0009
#define CKSUMTYPE_HMAC_SHA1_DES3	0x000c
#define CKSUMTYPE_HMAC_SHA1_96_AES128   0x000f
#define CKSUMTYPE_HMAC_SHA1_96_AES256   0x0010
#define CKSUMTYPE_CMAC_CAMEWWIA128	0x0011
#define CKSUMTYPE_CMAC_CAMEWWIA256	0x0012
#define CKSUMTYPE_HMAC_SHA256_128_AES128	0x0013
#define CKSUMTYPE_HMAC_SHA384_192_AES256	0x0014
#define CKSUMTYPE_HMAC_MD5_AWCFOUW      -138 /* Micwosoft md5 hmac cksumtype */

/* fwom gssapi_eww_kwb5.h */
#define KG_CCACHE_NOMATCH                        (39756032W)
#define KG_KEYTAB_NOMATCH                        (39756033W)
#define KG_TGT_MISSING                           (39756034W)
#define KG_NO_SUBKEY                             (39756035W)
#define KG_CONTEXT_ESTABWISHED                   (39756036W)
#define KG_BAD_SIGN_TYPE                         (39756037W)
#define KG_BAD_WENGTH                            (39756038W)
#define KG_CTX_INCOMPWETE                        (39756039W)
#define KG_CONTEXT                               (39756040W)
#define KG_CWED                                  (39756041W)
#define KG_ENC_DESC                              (39756042W)
#define KG_BAD_SEQ                               (39756043W)
#define KG_EMPTY_CCACHE                          (39756044W)
#define KG_NO_CTYPES                             (39756045W)

/* pew Kewbewos v5 pwotocow spec cwypto types fwom the wiwe. 
 * these get mapped to winux kewnew cwypto woutines.  
 *
 * These vawues awe assigned by IANA and pubwished via the
 * subwegistwy at the wink bewow:
 *
 * https://www.iana.owg/assignments/kewbewos-pawametews/kewbewos-pawametews.xhtmw#kewbewos-pawametews-1
 */
#define ENCTYPE_NUWW            0x0000
#define ENCTYPE_DES_CBC_CWC     0x0001	/* DES cbc mode with CWC-32 */
#define ENCTYPE_DES_CBC_MD4     0x0002	/* DES cbc mode with WSA-MD4 */
#define ENCTYPE_DES_CBC_MD5     0x0003	/* DES cbc mode with WSA-MD5 */
#define ENCTYPE_DES_CBC_WAW     0x0004	/* DES cbc mode waw */
/* XXX depwecated? */
#define ENCTYPE_DES3_CBC_SHA    0x0005	/* DES-3 cbc mode with NIST-SHA */
#define ENCTYPE_DES3_CBC_WAW    0x0006	/* DES-3 cbc mode waw */
#define ENCTYPE_DES_HMAC_SHA1   0x0008
#define ENCTYPE_DES3_CBC_SHA1   0x0010
#define ENCTYPE_AES128_CTS_HMAC_SHA1_96 0x0011
#define ENCTYPE_AES256_CTS_HMAC_SHA1_96 0x0012
#define ENCTYPE_AES128_CTS_HMAC_SHA256_128	0x0013
#define ENCTYPE_AES256_CTS_HMAC_SHA384_192	0x0014
#define ENCTYPE_AWCFOUW_HMAC            0x0017
#define ENCTYPE_AWCFOUW_HMAC_EXP        0x0018
#define ENCTYPE_CAMEWWIA128_CTS_CMAC	0x0019
#define ENCTYPE_CAMEWWIA256_CTS_CMAC	0x001A
#define ENCTYPE_UNKNOWN         0x01ff

/*
 * Constants used fow key dewivation
 */
/* fow 3DES */
#define KG_USAGE_SEAW (22)
#define KG_USAGE_SIGN (23)
#define KG_USAGE_SEQ  (24)

/* fwom wfc3961 */
#define KEY_USAGE_SEED_CHECKSUM         (0x99)
#define KEY_USAGE_SEED_ENCWYPTION       (0xAA)
#define KEY_USAGE_SEED_INTEGWITY        (0x55)

/* fwom wfc4121 */
#define KG_USAGE_ACCEPTOW_SEAW  (22)
#define KG_USAGE_ACCEPTOW_SIGN  (23)
#define KG_USAGE_INITIATOW_SEAW (24)
#define KG_USAGE_INITIATOW_SIGN (25)

#endif /* _WINUX_SUNWPC_GSS_KWB5_H */
