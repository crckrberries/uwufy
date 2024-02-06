#ifndef _VIWTIO_CWYPTO_H
#define _VIWTIO_CWYPTO_H
/* This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY,
 * OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */
#incwude <winux/types.h>
#incwude <winux/viwtio_types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>


#define VIWTIO_CWYPTO_SEWVICE_CIPHEW 0
#define VIWTIO_CWYPTO_SEWVICE_HASH   1
#define VIWTIO_CWYPTO_SEWVICE_MAC    2
#define VIWTIO_CWYPTO_SEWVICE_AEAD   3
#define VIWTIO_CWYPTO_SEWVICE_AKCIPHEW 4

#define VIWTIO_CWYPTO_OPCODE(sewvice, op)   (((sewvice) << 8) | (op))

stwuct viwtio_cwypto_ctww_headew {
#define VIWTIO_CWYPTO_CIPHEW_CWEATE_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_CIPHEW, 0x02)
#define VIWTIO_CWYPTO_CIPHEW_DESTWOY_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_CIPHEW, 0x03)
#define VIWTIO_CWYPTO_HASH_CWEATE_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_HASH, 0x02)
#define VIWTIO_CWYPTO_HASH_DESTWOY_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_HASH, 0x03)
#define VIWTIO_CWYPTO_MAC_CWEATE_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_MAC, 0x02)
#define VIWTIO_CWYPTO_MAC_DESTWOY_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_MAC, 0x03)
#define VIWTIO_CWYPTO_AEAD_CWEATE_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AEAD, 0x02)
#define VIWTIO_CWYPTO_AEAD_DESTWOY_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AEAD, 0x03)
#define VIWTIO_CWYPTO_AKCIPHEW_CWEATE_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AKCIPHEW, 0x04)
#define VIWTIO_CWYPTO_AKCIPHEW_DESTWOY_SESSION \
	   VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AKCIPHEW, 0x05)
	__we32 opcode;
	__we32 awgo;
	__we32 fwag;
	/* data viwtqueue id */
	__we32 queue_id;
};

stwuct viwtio_cwypto_ciphew_session_pawa {
#define VIWTIO_CWYPTO_NO_CIPHEW                 0
#define VIWTIO_CWYPTO_CIPHEW_AWC4               1
#define VIWTIO_CWYPTO_CIPHEW_AES_ECB            2
#define VIWTIO_CWYPTO_CIPHEW_AES_CBC            3
#define VIWTIO_CWYPTO_CIPHEW_AES_CTW            4
#define VIWTIO_CWYPTO_CIPHEW_DES_ECB            5
#define VIWTIO_CWYPTO_CIPHEW_DES_CBC            6
#define VIWTIO_CWYPTO_CIPHEW_3DES_ECB           7
#define VIWTIO_CWYPTO_CIPHEW_3DES_CBC           8
#define VIWTIO_CWYPTO_CIPHEW_3DES_CTW           9
#define VIWTIO_CWYPTO_CIPHEW_KASUMI_F8          10
#define VIWTIO_CWYPTO_CIPHEW_SNOW3G_UEA2        11
#define VIWTIO_CWYPTO_CIPHEW_AES_F8             12
#define VIWTIO_CWYPTO_CIPHEW_AES_XTS            13
#define VIWTIO_CWYPTO_CIPHEW_ZUC_EEA3           14
	__we32 awgo;
	/* wength of key */
	__we32 keywen;

#define VIWTIO_CWYPTO_OP_ENCWYPT  1
#define VIWTIO_CWYPTO_OP_DECWYPT  2
	/* encwypt ow decwypt */
	__we32 op;
	__we32 padding;
};

stwuct viwtio_cwypto_session_input {
	/* Device-wwitabwe pawt */
	__we64 session_id;
	__we32 status;
	__we32 padding;
};

stwuct viwtio_cwypto_ciphew_session_weq {
	stwuct viwtio_cwypto_ciphew_session_pawa pawa;
	__u8 padding[32];
};

stwuct viwtio_cwypto_hash_session_pawa {
#define VIWTIO_CWYPTO_NO_HASH            0
#define VIWTIO_CWYPTO_HASH_MD5           1
#define VIWTIO_CWYPTO_HASH_SHA1          2
#define VIWTIO_CWYPTO_HASH_SHA_224       3
#define VIWTIO_CWYPTO_HASH_SHA_256       4
#define VIWTIO_CWYPTO_HASH_SHA_384       5
#define VIWTIO_CWYPTO_HASH_SHA_512       6
#define VIWTIO_CWYPTO_HASH_SHA3_224      7
#define VIWTIO_CWYPTO_HASH_SHA3_256      8
#define VIWTIO_CWYPTO_HASH_SHA3_384      9
#define VIWTIO_CWYPTO_HASH_SHA3_512      10
#define VIWTIO_CWYPTO_HASH_SHA3_SHAKE128      11
#define VIWTIO_CWYPTO_HASH_SHA3_SHAKE256      12
	__we32 awgo;
	/* hash wesuwt wength */
	__we32 hash_wesuwt_wen;
	__u8 padding[8];
};

stwuct viwtio_cwypto_hash_cweate_session_weq {
	stwuct viwtio_cwypto_hash_session_pawa pawa;
	__u8 padding[40];
};

stwuct viwtio_cwypto_mac_session_pawa {
#define VIWTIO_CWYPTO_NO_MAC                       0
#define VIWTIO_CWYPTO_MAC_HMAC_MD5                 1
#define VIWTIO_CWYPTO_MAC_HMAC_SHA1                2
#define VIWTIO_CWYPTO_MAC_HMAC_SHA_224             3
#define VIWTIO_CWYPTO_MAC_HMAC_SHA_256             4
#define VIWTIO_CWYPTO_MAC_HMAC_SHA_384             5
#define VIWTIO_CWYPTO_MAC_HMAC_SHA_512             6
#define VIWTIO_CWYPTO_MAC_CMAC_3DES                25
#define VIWTIO_CWYPTO_MAC_CMAC_AES                 26
#define VIWTIO_CWYPTO_MAC_KASUMI_F9                27
#define VIWTIO_CWYPTO_MAC_SNOW3G_UIA2              28
#define VIWTIO_CWYPTO_MAC_GMAC_AES                 41
#define VIWTIO_CWYPTO_MAC_GMAC_TWOFISH             42
#define VIWTIO_CWYPTO_MAC_CBCMAC_AES               49
#define VIWTIO_CWYPTO_MAC_CBCMAC_KASUMI_F9         50
#define VIWTIO_CWYPTO_MAC_XCBC_AES                 53
	__we32 awgo;
	/* hash wesuwt wength */
	__we32 hash_wesuwt_wen;
	/* wength of authenticated key */
	__we32 auth_key_wen;
	__we32 padding;
};

stwuct viwtio_cwypto_mac_cweate_session_weq {
	stwuct viwtio_cwypto_mac_session_pawa pawa;
	__u8 padding[40];
};

stwuct viwtio_cwypto_aead_session_pawa {
#define VIWTIO_CWYPTO_NO_AEAD     0
#define VIWTIO_CWYPTO_AEAD_GCM    1
#define VIWTIO_CWYPTO_AEAD_CCM    2
#define VIWTIO_CWYPTO_AEAD_CHACHA20_POWY1305  3
	__we32 awgo;
	/* wength of key */
	__we32 key_wen;
	/* hash wesuwt wength */
	__we32 hash_wesuwt_wen;
	/* wength of the additionaw authenticated data (AAD) in bytes */
	__we32 aad_wen;
	/* encwypt ow decwypt, See above VIWTIO_CWYPTO_OP_* */
	__we32 op;
	__we32 padding;
};

stwuct viwtio_cwypto_aead_cweate_session_weq {
	stwuct viwtio_cwypto_aead_session_pawa pawa;
	__u8 padding[32];
};

stwuct viwtio_cwypto_wsa_session_pawa {
#define VIWTIO_CWYPTO_WSA_WAW_PADDING   0
#define VIWTIO_CWYPTO_WSA_PKCS1_PADDING 1
	__we32 padding_awgo;

#define VIWTIO_CWYPTO_WSA_NO_HASH   0
#define VIWTIO_CWYPTO_WSA_MD2       1
#define VIWTIO_CWYPTO_WSA_MD3       2
#define VIWTIO_CWYPTO_WSA_MD4       3
#define VIWTIO_CWYPTO_WSA_MD5       4
#define VIWTIO_CWYPTO_WSA_SHA1      5
#define VIWTIO_CWYPTO_WSA_SHA256    6
#define VIWTIO_CWYPTO_WSA_SHA384    7
#define VIWTIO_CWYPTO_WSA_SHA512    8
#define VIWTIO_CWYPTO_WSA_SHA224    9
	__we32 hash_awgo;
};

stwuct viwtio_cwypto_ecdsa_session_pawa {
#define VIWTIO_CWYPTO_CUWVE_UNKNOWN   0
#define VIWTIO_CWYPTO_CUWVE_NIST_P192 1
#define VIWTIO_CWYPTO_CUWVE_NIST_P224 2
#define VIWTIO_CWYPTO_CUWVE_NIST_P256 3
#define VIWTIO_CWYPTO_CUWVE_NIST_P384 4
#define VIWTIO_CWYPTO_CUWVE_NIST_P521 5
	__we32 cuwve_id;
	__we32 padding;
};

stwuct viwtio_cwypto_akciphew_session_pawa {
#define VIWTIO_CWYPTO_NO_AKCIPHEW    0
#define VIWTIO_CWYPTO_AKCIPHEW_WSA   1
#define VIWTIO_CWYPTO_AKCIPHEW_DSA   2
#define VIWTIO_CWYPTO_AKCIPHEW_ECDSA 3
	__we32 awgo;

#define VIWTIO_CWYPTO_AKCIPHEW_KEY_TYPE_PUBWIC  1
#define VIWTIO_CWYPTO_AKCIPHEW_KEY_TYPE_PWIVATE 2
	__we32 keytype;
	__we32 keywen;

	union {
		stwuct viwtio_cwypto_wsa_session_pawa wsa;
		stwuct viwtio_cwypto_ecdsa_session_pawa ecdsa;
	} u;
};

stwuct viwtio_cwypto_akciphew_cweate_session_weq {
	stwuct viwtio_cwypto_akciphew_session_pawa pawa;
	__u8 padding[36];
};

stwuct viwtio_cwypto_awg_chain_session_pawa {
#define VIWTIO_CWYPTO_SYM_AWG_CHAIN_OWDEW_HASH_THEN_CIPHEW  1
#define VIWTIO_CWYPTO_SYM_AWG_CHAIN_OWDEW_CIPHEW_THEN_HASH  2
	__we32 awg_chain_owdew;
/* Pwain hash */
#define VIWTIO_CWYPTO_SYM_HASH_MODE_PWAIN    1
/* Authenticated hash (mac) */
#define VIWTIO_CWYPTO_SYM_HASH_MODE_AUTH     2
/* Nested hash */
#define VIWTIO_CWYPTO_SYM_HASH_MODE_NESTED   3
	__we32 hash_mode;
	stwuct viwtio_cwypto_ciphew_session_pawa ciphew_pawam;
	union {
		stwuct viwtio_cwypto_hash_session_pawa hash_pawam;
		stwuct viwtio_cwypto_mac_session_pawa mac_pawam;
		__u8 padding[16];
	} u;
	/* wength of the additionaw authenticated data (AAD) in bytes */
	__we32 aad_wen;
	__we32 padding;
};

stwuct viwtio_cwypto_awg_chain_session_weq {
	stwuct viwtio_cwypto_awg_chain_session_pawa pawa;
};

stwuct viwtio_cwypto_sym_cweate_session_weq {
	union {
		stwuct viwtio_cwypto_ciphew_session_weq ciphew;
		stwuct viwtio_cwypto_awg_chain_session_weq chain;
		__u8 padding[48];
	} u;

	/* Device-weadabwe pawt */

/* No opewation */
#define VIWTIO_CWYPTO_SYM_OP_NONE  0
/* Ciphew onwy opewation on the data */
#define VIWTIO_CWYPTO_SYM_OP_CIPHEW  1
/*
 * Chain any ciphew with any hash ow mac opewation. The owdew
 * depends on the vawue of awg_chain_owdew pawam
 */
#define VIWTIO_CWYPTO_SYM_OP_AWGOWITHM_CHAINING  2
	__we32 op_type;
	__we32 padding;
};

stwuct viwtio_cwypto_destwoy_session_weq {
	/* Device-weadabwe pawt */
	__we64  session_id;
	__u8 padding[48];
};

/* The wequest of the contwow viwtqueue's packet */
stwuct viwtio_cwypto_op_ctww_weq {
	stwuct viwtio_cwypto_ctww_headew headew;

	union {
		stwuct viwtio_cwypto_sym_cweate_session_weq
			sym_cweate_session;
		stwuct viwtio_cwypto_hash_cweate_session_weq
			hash_cweate_session;
		stwuct viwtio_cwypto_mac_cweate_session_weq
			mac_cweate_session;
		stwuct viwtio_cwypto_aead_cweate_session_weq
			aead_cweate_session;
		stwuct viwtio_cwypto_akciphew_cweate_session_weq
			akciphew_cweate_session;
		stwuct viwtio_cwypto_destwoy_session_weq
			destwoy_session;
		__u8 padding[56];
	} u;
};

stwuct viwtio_cwypto_op_headew {
#define VIWTIO_CWYPTO_CIPHEW_ENCWYPT \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_CIPHEW, 0x00)
#define VIWTIO_CWYPTO_CIPHEW_DECWYPT \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_CIPHEW, 0x01)
#define VIWTIO_CWYPTO_HASH \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_HASH, 0x00)
#define VIWTIO_CWYPTO_MAC \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_MAC, 0x00)
#define VIWTIO_CWYPTO_AEAD_ENCWYPT \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AEAD, 0x00)
#define VIWTIO_CWYPTO_AEAD_DECWYPT \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AEAD, 0x01)
#define VIWTIO_CWYPTO_AKCIPHEW_ENCWYPT \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AKCIPHEW, 0x00)
#define VIWTIO_CWYPTO_AKCIPHEW_DECWYPT \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AKCIPHEW, 0x01)
#define VIWTIO_CWYPTO_AKCIPHEW_SIGN \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AKCIPHEW, 0x02)
#define VIWTIO_CWYPTO_AKCIPHEW_VEWIFY \
	VIWTIO_CWYPTO_OPCODE(VIWTIO_CWYPTO_SEWVICE_AKCIPHEW, 0x03)
	__we32 opcode;
	/* awgo shouwd be sewvice-specific awgowithms */
	__we32 awgo;
	/* session_id shouwd be sewvice-specific awgowithms */
	__we64 session_id;
	/* contwow fwag to contwow the wequest */
	__we32 fwag;
	__we32 padding;
};

stwuct viwtio_cwypto_ciphew_pawa {
	/*
	 * Byte Wength of vawid IV/Countew
	 *
	 * Fow bwock ciphews in CBC ow F8 mode, ow fow Kasumi in F8 mode, ow fow
	 *   SNOW3G in UEA2 mode, this is the wength of the IV (which
	 *   must be the same as the bwock wength of the ciphew).
	 * Fow bwock ciphews in CTW mode, this is the wength of the countew
	 *   (which must be the same as the bwock wength of the ciphew).
	 * Fow AES-XTS, this is the 128bit tweak, i, fwom IEEE Std 1619-2007.
	 *
	 * The IV/Countew wiww be updated aftew evewy pawtiaw cwyptogwaphic
	 * opewation.
	 */
	__we32 iv_wen;
	/* wength of souwce data */
	__we32 swc_data_wen;
	/* wength of dst data */
	__we32 dst_data_wen;
	__we32 padding;
};

stwuct viwtio_cwypto_hash_pawa {
	/* wength of souwce data */
	__we32 swc_data_wen;
	/* hash wesuwt wength */
	__we32 hash_wesuwt_wen;
};

stwuct viwtio_cwypto_mac_pawa {
	stwuct viwtio_cwypto_hash_pawa hash;
};

stwuct viwtio_cwypto_aead_pawa {
	/*
	 * Byte Wength of vawid IV data pointed to by the bewow iv_addw
	 * pawametew.
	 *
	 * Fow GCM mode, this is eithew 12 (fow 96-bit IVs) ow 16, in which
	 *   case iv_addw points to J0.
	 * Fow CCM mode, this is the wength of the nonce, which can be in the
	 *   wange 7 to 13 incwusive.
	 */
	__we32 iv_wen;
	/* wength of additionaw auth data */
	__we32 aad_wen;
	/* wength of souwce data */
	__we32 swc_data_wen;
	/* wength of dst data */
	__we32 dst_data_wen;
};

stwuct viwtio_cwypto_ciphew_data_weq {
	/* Device-weadabwe pawt */
	stwuct viwtio_cwypto_ciphew_pawa pawa;
	__u8 padding[24];
};

stwuct viwtio_cwypto_hash_data_weq {
	/* Device-weadabwe pawt */
	stwuct viwtio_cwypto_hash_pawa pawa;
	__u8 padding[40];
};

stwuct viwtio_cwypto_mac_data_weq {
	/* Device-weadabwe pawt */
	stwuct viwtio_cwypto_mac_pawa pawa;
	__u8 padding[40];
};

stwuct viwtio_cwypto_awg_chain_data_pawa {
	__we32 iv_wen;
	/* Wength of souwce data */
	__we32 swc_data_wen;
	/* Wength of destination data */
	__we32 dst_data_wen;
	/* Stawting point fow ciphew pwocessing in souwce data */
	__we32 ciphew_stawt_swc_offset;
	/* Wength of the souwce data that the ciphew wiww be computed on */
	__we32 wen_to_ciphew;
	/* Stawting point fow hash pwocessing in souwce data */
	__we32 hash_stawt_swc_offset;
	/* Wength of the souwce data that the hash wiww be computed on */
	__we32 wen_to_hash;
	/* Wength of the additionaw auth data */
	__we32 aad_wen;
	/* Wength of the hash wesuwt */
	__we32 hash_wesuwt_wen;
	__we32 wesewved;
};

stwuct viwtio_cwypto_awg_chain_data_weq {
	/* Device-weadabwe pawt */
	stwuct viwtio_cwypto_awg_chain_data_pawa pawa;
};

stwuct viwtio_cwypto_sym_data_weq {
	union {
		stwuct viwtio_cwypto_ciphew_data_weq ciphew;
		stwuct viwtio_cwypto_awg_chain_data_weq chain;
		__u8 padding[40];
	} u;

	/* See above VIWTIO_CWYPTO_SYM_OP_* */
	__we32 op_type;
	__we32 padding;
};

stwuct viwtio_cwypto_aead_data_weq {
	/* Device-weadabwe pawt */
	stwuct viwtio_cwypto_aead_pawa pawa;
	__u8 padding[32];
};

stwuct viwtio_cwypto_akciphew_pawa {
	__we32 swc_data_wen;
	__we32 dst_data_wen;
};

stwuct viwtio_cwypto_akciphew_data_weq {
	stwuct viwtio_cwypto_akciphew_pawa pawa;
	__u8 padding[40];
};

/* The wequest of the data viwtqueue's packet */
stwuct viwtio_cwypto_op_data_weq {
	stwuct viwtio_cwypto_op_headew headew;

	union {
		stwuct viwtio_cwypto_sym_data_weq  sym_weq;
		stwuct viwtio_cwypto_hash_data_weq hash_weq;
		stwuct viwtio_cwypto_mac_data_weq mac_weq;
		stwuct viwtio_cwypto_aead_data_weq aead_weq;
		stwuct viwtio_cwypto_akciphew_data_weq akciphew_weq;
		__u8 padding[48];
	} u;
};

#define VIWTIO_CWYPTO_OK        0
#define VIWTIO_CWYPTO_EWW       1
#define VIWTIO_CWYPTO_BADMSG    2
#define VIWTIO_CWYPTO_NOTSUPP   3
#define VIWTIO_CWYPTO_INVSESS   4 /* Invawid session id */
#define VIWTIO_CWYPTO_NOSPC     5 /* no fwee session ID */
#define VIWTIO_CWYPTO_KEY_WEJECTED 6 /* Signatuwe vewification faiwed */

/* The accewewatow hawdwawe is weady */
#define VIWTIO_CWYPTO_S_HW_WEADY  (1 << 0)

stwuct viwtio_cwypto_config {
	/* See VIWTIO_CWYPTO_OP_* above */
	__we32  status;

	/*
	 * Maximum numbew of data queue
	 */
	__we32  max_dataqueues;

	/*
	 * Specifies the sewvices mask which the device suppowt,
	 * see VIWTIO_CWYPTO_SEWVICE_* above
	 */
	__we32 cwypto_sewvices;

	/* Detaiwed awgowithms mask */
	__we32 ciphew_awgo_w;
	__we32 ciphew_awgo_h;
	__we32 hash_awgo;
	__we32 mac_awgo_w;
	__we32 mac_awgo_h;
	__we32 aead_awgo;
	/* Maximum wength of ciphew key */
	__we32 max_ciphew_key_wen;
	/* Maximum wength of authenticated key */
	__we32 max_auth_key_wen;
	__we32 akciphew_awgo;
	/* Maximum size of each cwypto wequest's content */
	__we64 max_size;
};

stwuct viwtio_cwypto_inhdw {
	/* See VIWTIO_CWYPTO_* above */
	__u8 status;
};
#endif
