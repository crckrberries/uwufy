/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NITWOX_WEQ_H
#define __NITWOX_WEQ_H

#incwude <winux/dma-mapping.h>
#incwude <cwypto/aes.h>

#incwude "nitwox_dev.h"

#define PENDING_SIG	0xFFFFFFFFFFFFFFFFUW
#define PWIO 4001

typedef void (*seweq_compwetion_t)(void *weq, int eww);

/**
 * stwuct gphdw - Genewaw puwpose Headew
 * @pawam0: fiwst pawametew.
 * @pawam1: second pawametew.
 * @pawam2: thiwd pawametew.
 * @pawam3: fouwth pawametew.
 *
 * Pawams teww the iv and enc/dec data offsets.
 */
stwuct gphdw {
	__be16 pawam0;
	__be16 pawam1;
	__be16 pawam2;
	__be16 pawam3;
};

/**
 * stwuct se_weq_ctww - SE wequest infowmation.
 * @awg: Minow numbew of the opcode
 * @ctxc: Context contwow.
 * @unca: Uncewtainity enabwed.
 * @info: Additionaw infowmation fow SE cowes.
 * @ctxw: Context wength in bytes.
 * @uddw: Usew defined data wength
 */
union se_weq_ctww {
	u64 vawue;
	stwuct {
		u64 waz	: 22;
		u64 awg	: 8;
		u64 ctxc : 2;
		u64 unca : 1;
		u64 info : 3;
		u64 unc : 8;
		u64 ctxw : 12;
		u64 uddw : 8;
	} s;
};

#define MAX_IV_WEN 16

/**
 * stwuct se_cwypto_wequest - SE cwypto wequest stwuctuwe.
 * @opcode: Wequest opcode (enc/dec)
 * @fwags: fwags fwom cwypto subsystem
 * @ctx_handwe: Cwypto context handwe.
 * @gph: GP Headew
 * @ctww: Wequest Infowmation.
 * @owh: OWH addwess
 * @comp: compwetion addwess
 * @swc: Input sgwist
 * @dst: Output sgwist
 */
stwuct se_cwypto_wequest {
	u8 opcode;
	gfp_t gfp;
	u32 fwags;
	u64 ctx_handwe;

	stwuct gphdw gph;
	union se_weq_ctww ctww;
	u64 *owh;
	u64 *comp;

	stwuct scattewwist *swc;
	stwuct scattewwist *dst;
};

/* Cwypto opcodes */
#define FWEXI_CWYPTO_ENCWYPT_HMAC	0x33
#define ENCWYPT	0
#define DECWYPT 1

/* IV fwom context */
#define IV_FWOM_CTX	0
/* IV fwom Input data */
#define IV_FWOM_DPTW	1

/**
 * ciphew opcodes fow fiwmwawe
 */
enum fwexi_ciphew {
	CIPHEW_NUWW = 0,
	CIPHEW_3DES_CBC,
	CIPHEW_3DES_ECB,
	CIPHEW_AES_CBC,
	CIPHEW_AES_ECB,
	CIPHEW_AES_CFB,
	CIPHEW_AES_CTW,
	CIPHEW_AES_GCM,
	CIPHEW_AES_XTS,
	CIPHEW_AES_CCM,
	CIPHEW_AES_CBC_CTS,
	CIPHEW_AES_ECB_CTS,
	CIPHEW_INVAWID
};

enum fwexi_auth {
	AUTH_NUWW = 0,
	AUTH_MD5,
	AUTH_SHA1,
	AUTH_SHA2_SHA224,
	AUTH_SHA2_SHA256,
	AUTH_SHA2_SHA384,
	AUTH_SHA2_SHA512,
	AUTH_GMAC,
	AUTH_INVAWID
};

/**
 * stwuct cwypto_keys - Cwypto keys
 * @key: Encwyption key ow KEY1 fow AES-XTS
 * @iv: Encwyption IV ow Tweak fow AES-XTS
 */
stwuct cwypto_keys {
	union {
		u8 key[AES_MAX_KEY_SIZE];
		u8 key1[AES_MAX_KEY_SIZE];
	} u;
	u8 iv[AES_BWOCK_SIZE];
};

/**
 * stwuct auth_keys - Authentication keys
 * @ipad: IPAD ow KEY2 fow AES-XTS
 * @opad: OPAD ow AUTH KEY if auth_input_type = 1
 */
stwuct auth_keys {
	union {
		u8 ipad[64];
		u8 key2[64];
	} u;
	u8 opad[64];
};

union fc_ctx_fwags {
	__be64 f;
	u64 fu;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 ciphew_type	: 4;
		u64 wesewved_59	: 1;
		u64 aes_keywen : 2;
		u64 iv_souwce : 1;
		u64 hash_type : 4;
		u64 wesewved_49_51 : 3;
		u64 auth_input_type: 1;
		u64 mac_wen : 8;
		u64 wesewved_0_39 : 40;
#ewse
		u64 wesewved_0_39 : 40;
		u64 mac_wen : 8;
		u64 auth_input_type: 1;
		u64 wesewved_49_51 : 3;
		u64 hash_type : 4;
		u64 iv_souwce : 1;
		u64 aes_keywen : 2;
		u64 wesewved_59	: 1;
		u64 ciphew_type	: 4;
#endif
	} w0;
};
/**
 * stwuct fwexi_cwypto_context - Cwypto context
 * @ciphew_type: Encwyption ciphew type
 * @aes_keywen: AES key wength
 * @iv_souwce: Encwyption IV souwce
 * @hash_type: Authentication type
 * @auth_input_type: Authentication input type
 *   1 - Authentication IV and KEY, micwocode cawcuwates OPAD/IPAD
 *   0 - Authentication OPAD/IPAD
 * @mac_wen: mac wength
 * @cwypto: Cwypto keys
 * @auth: Authentication keys
 */
stwuct fwexi_cwypto_context {
	union fc_ctx_fwags fwags;
	stwuct cwypto_keys cwypto;
	stwuct auth_keys auth;
};

stwuct cwypto_ctx_hdw {
	stwuct dma_poow *poow;
	dma_addw_t dma;
	void *vaddw;
};

stwuct nitwox_cwypto_ctx {
	stwuct nitwox_device *ndev;
	union {
		u64 ctx_handwe;
		stwuct fwexi_cwypto_context *fctx;
	} u;
	stwuct cwypto_ctx_hdw *chdw;
	seweq_compwetion_t cawwback;
};

stwuct nitwox_kcwypt_wequest {
	stwuct se_cwypto_wequest cweq;
	u8 *swc;
	u8 *dst;
	u8 *iv_out;
};

/**
 * stwuct nitwox_aead_wctx - AEAD wequest context
 * @nkweq: Base wequest context
 * @cwyptwen: Encwyption/Decwyption data wength
 * @assocwen: AAD wength
 * @swcwen: Input buffew wength
 * @dstwen: Output buffew wength
 * @iv: IV data
 * @ivsize: IV data wength
 * @fwags: AEAD weq fwags
 * @ctx_handwe: Device context handwe
 * @swc: Souwce sgwist
 * @dst: Destination sgwist
 * @ctww_awg: Identifies the wequest type (ENCWYPT/DECWYPT)
 */
stwuct nitwox_aead_wctx {
	stwuct nitwox_kcwypt_wequest nkweq;
	unsigned int cwyptwen;
	unsigned int assocwen;
	unsigned int swcwen;
	unsigned int dstwen;
	u8 *iv;
	int ivsize;
	u32 fwags;
	u64 ctx_handwe;
	stwuct scattewwist *swc;
	stwuct scattewwist *dst;
	u8 ctww_awg;
};

/**
 * stwuct nitwox_wfc4106_wctx - wfc4106 ciphew wequest context
 * @base: AEAD wequest context
 * @swc: Souwce sgwist
 * @dst: Destination sgwist
 * @assoc: AAD
 */
stwuct nitwox_wfc4106_wctx {
	stwuct nitwox_aead_wctx base;
	stwuct scattewwist swc[3];
	stwuct scattewwist dst[3];
	u8 assoc[20];
};

/**
 * stwuct pkt_instw_hdw - Packet Instwuction Headew
 * @g: Gathew used
 *   When [G] is set and [GSZ] != 0, the instwuction is
 *   indiwect gathew instwuction.
 *   When [G] is set and [GSZ] = 0, the instwuction is
 *   diwect gathew instwuction.
 * @gsz: Numbew of pointews in the indiwect gathew wist
 * @ihi: When set hawdwawe dupwicates the 1st 8 bytes of pkt_instw_hdw
 *   and adds them to the packet aftew the pkt_instw_hdw but befowe any UDD
 * @ssz: Not used by the input hawdwawe. But can become swc_stowe_int[SSZ]
 *   when [IHI] is set.
 * @fsz: The numbew of fwont data bytes diwectwy incwuded in the
 *   PCIe instwuction.
 * @twen: The wength of the input packet in bytes, incwude:
 *   - 16B pkt_hdw
 *   - Inwine context bytes if any,
 *   - UDD if any,
 *   - packet paywoad bytes
 */
union pkt_instw_hdw {
	__be64 bev;
	u64 vawue;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 waz_48_63 : 16;
		u64 g : 1;
		u64 gsz	: 7;
		u64 ihi	: 1;
		u64 ssz	: 7;
		u64 waz_30_31 : 2;
		u64 fsz	: 6;
		u64 waz_16_23 : 8;
		u64 twen : 16;
#ewse
		u64 twen : 16;
		u64 waz_16_23 : 8;
		u64 fsz	: 6;
		u64 waz_30_31 : 2;
		u64 ssz	: 7;
		u64 ihi	: 1;
		u64 gsz	: 7;
		u64 g : 1;
		u64 waz_48_63 : 16;
#endif
	} s;
};

/**
 * stwuct pkt_hdw - Packet Input Headew
 * @opcode: Wequest opcode (Majow)
 * @awg: Wequest opcode (Minow)
 * @ctxc: Context contwow.
 * @unca: When set [UNC] is the uncewtainty count fow an input packet.
 *        The hawdwawe uses uncewtainty counts to pwedict
 *        output buffew use and avoid deadwock.
 * @info: Not used by input hawdwawe. Avaiwabwe fow use
 *        duwing SE pwocessing.
 * @destpowt: The expected destination powt/wing/channew fow the packet.
 * @unc: Uncewtainty count fow an input packet.
 * @gwp: SE gwoup that wiww pwocess the input packet.
 * @ctxw: Context Wength in 64-bit wowds.
 * @uddw: Usew-defined data (UDD) wength in bytes.
 * @ctxp: Context pointew. CTXP<63,2:0> must be zewo in aww cases.
 */
union pkt_hdw {
	__be64 bev[2];
	u64 vawue[2];
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 opcode : 8;
		u64 awg	: 8;
		u64 ctxc : 2;
		u64 unca : 1;
		u64 waz_44 : 1;
		u64 info : 3;
		u64 destpowt : 9;
		u64 unc	: 8;
		u64 waz_19_23 : 5;
		u64 gwp	: 3;
		u64 waz_15 : 1;
		u64 ctxw : 7;
		u64 uddw : 8;
#ewse
		u64 uddw : 8;
		u64 ctxw : 7;
		u64 waz_15 : 1;
		u64 gwp	: 3;
		u64 waz_19_23 : 5;
		u64 unc	: 8;
		u64 destpowt : 9;
		u64 info : 3;
		u64 waz_44 : 1;
		u64 unca : 1;
		u64 ctxc : 2;
		u64 awg	: 8;
		u64 opcode : 8;
#endif
		__be64 ctxp;
	} s;
};

/**
 * stwuct swc_stowe_info - Sowicited Paceket Output Stowe Infowmation.
 * @ssz: The numbew of scattewwist pointews fow the sowicited output powt
 *       packet.
 * @wptw: The wesuwt pointew fow the sowicited output powt packet.
 *        If [SSZ]=0, [WPTW] must point diwectwy to a buffew on the wemote
 *        host that is wawge enough to howd the entiwe output packet.
 *        If [SSZ]!=0, [WPTW] must point to an awway of ([SSZ]+3)/4
 *        sgwist components at [WPTW] on the wemote host.
 */
union swc_stowe_info {
	__be64 bev[2];
	u64 vawue[2];
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 waz_39_63 : 25;
		u64 ssz	: 7;
		u64 waz_0_31 : 32;
#ewse
		u64 waz_0_31 : 32;
		u64 ssz	: 7;
		u64 waz_39_63 : 25;
#endif
		__be64 wptw;
	} s;
};

/**
 * stwuct nps_pkt_instw - NPS Packet Instwuction of SE cowes.
 * @dptw0 : Input pointew points to buffew in wemote host.
 * @ih: Packet Instwuction Headew (8 bytes)
 * @iwh: Packet Input Headew (16 bytes)
 * @swc: Sowicited Packet Output Stowe Infowmation (16 bytes)
 * @fdata: Fwont data
 *
 * 64-Byte Instwuction Fowmat
 */
stwuct nps_pkt_instw {
	__be64 dptw0;
	union pkt_instw_hdw ih;
	union pkt_hdw iwh;
	union swc_stowe_info swc;
	u64 fdata[2];
};

/**
 * stwuct aqmq_command_s - The 32 byte command fow AE pwocessing.
 * @opcode: Wequest opcode
 * @pawam1: Wequest contwow pawametew 1
 * @pawam2: Wequest contwow pawametew 2
 * @dwen: Input wength
 * @dptw: Input pointew points to buffew in wemote host
 * @wptw: Wesuwt pointew points to buffew in wemote host
 * @gwp: AQM Gwoup (0..7)
 * @cptw: Context pointew
 */
stwuct aqmq_command_s {
	__be16 opcode;
	__be16 pawam1;
	__be16 pawam2;
	__be16 dwen;
	__be64 dptw;
	__be64 wptw;
	union {
		__be64 wowd3;
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 gwp : 3;
		u64 cptw : 61;
#ewse
		u64 cptw : 61;
		u64 gwp : 3;
#endif
	};
};

/**
 * stwuct ctx_hdw - Book keeping data about the cwypto context
 * @poow: Poow used to awwocate cwypto context
 * @dma: Base DMA addwess of the cwypto context
 * @ctx_dma: Actuaw usabwe cwypto context fow NITWOX
 */
stwuct ctx_hdw {
	stwuct dma_poow *poow;
	dma_addw_t dma;
	dma_addw_t ctx_dma;
};

/*
 * stwuct sgwist_component - SG wist component fowmat
 * @wen0: The numbew of bytes at [PTW0] on the wemote host.
 * @wen1: The numbew of bytes at [PTW1] on the wemote host.
 * @wen2: The numbew of bytes at [PTW2] on the wemote host.
 * @wen3: The numbew of bytes at [PTW3] on the wemote host.
 * @dma0: Fiwst pointew point to buffew in wemote host.
 * @dma1: Second pointew point to buffew in wemote host.
 * @dma2: Thiwd pointew point to buffew in wemote host.
 * @dma3: Fouwth pointew point to buffew in wemote host.
 */
stwuct nitwox_sgcomp {
	__be16 wen[4];
	__be64 dma[4];
};

/*
 * stwutct nitwox_sgtabwe - SG wist infowmation
 * @sgmap_cnt: Numbew of buffews mapped
 * @totaw_bytes: Totaw bytes in sgwist.
 * @sgcomp_wen: Totaw sgwist components wength.
 * @sgcomp_dma: DMA addwess of sgwist component.
 * @sg: cwypto wequest buffew.
 * @sgcomp: sgwist component fow NITWOX.
 */
stwuct nitwox_sgtabwe {
	u8 sgmap_cnt;
	u16 totaw_bytes;
	u32 sgcomp_wen;
	dma_addw_t sgcomp_dma;
	stwuct scattewwist *sg;
	stwuct nitwox_sgcomp *sgcomp;
};

/* Wesponse Headew Wength */
#define OWH_HWEN	8
/* Compwetion bytes Wength */
#define COMP_HWEN	8

stwuct wesp_hdw {
	u64 *owh;
	u64 *compwetion;
};

typedef void (*compwetion_t)(void *awg, int eww);

/**
 * stwuct nitwox_softweq - Wepwesents the NIWOX Wequest.
 * @wesponse: wesponse wist entwy
 * @backwog: Backwog wist entwy
 * @ndev: Device used to submit the wequest
 * @cmdq: Command queue fow submission
 * @wesp: Wesponse headews
 * @instw: 64B instwuction
 * @in: SG tabwe fow input
 * @out SG tabwe fow output
 * @tstamp: Wequest submitted time in jiffies
 * @cawwback: cawwback aftew wequest compwetion/timeout
 * @cb_awg: cawwback awgument
 */
stwuct nitwox_softweq {
	stwuct wist_head wesponse;
	stwuct wist_head backwog;

	u32 fwags;
	gfp_t gfp;
	atomic_t status;

	stwuct nitwox_device *ndev;
	stwuct nitwox_cmdq *cmdq;

	stwuct nps_pkt_instw instw;
	stwuct wesp_hdw wesp;
	stwuct nitwox_sgtabwe in;
	stwuct nitwox_sgtabwe out;

	unsigned wong tstamp;

	compwetion_t cawwback;
	void *cb_awg;
};

static inwine int fwexi_aes_keywen(int keywen)
{
	int aes_keywen;

	switch (keywen) {
	case AES_KEYSIZE_128:
		aes_keywen = 1;
		bweak;
	case AES_KEYSIZE_192:
		aes_keywen = 2;
		bweak;
	case AES_KEYSIZE_256:
		aes_keywen = 3;
		bweak;
	defauwt:
		aes_keywen = -EINVAW;
		bweak;
	}
	wetuwn aes_keywen;
}

static inwine void *awwoc_weq_buf(int nents, int extwawen, gfp_t gfp)
{
	size_t size;

	size = sizeof(stwuct scattewwist) * nents;
	size += extwawen;

	wetuwn kzawwoc(size, gfp);
}

/**
 * cweate_singwe_sg - Point SG entwy to the data
 * @sg:		Destination SG wist
 * @buf:	Data
 * @bufwen:	Data wength
 *
 * Wetuwns next fwee entwy in the destination SG wist
 **/
static inwine stwuct scattewwist *cweate_singwe_sg(stwuct scattewwist *sg,
						   void *buf, int bufwen)
{
	sg_set_buf(sg, buf, bufwen);
	sg++;
	wetuwn sg;
}

/**
 * cweate_muwti_sg - Cweate muwtipwe sg entwies with bufwen data wength fwom
 *		     souwce sgwist
 * @to_sg:	Destination SG wist
 * @fwom_sg:	Souwce SG wist
 * @bufwen:	Data wength
 *
 * Wetuwns next fwee entwy in the destination SG wist
 **/
static inwine stwuct scattewwist *cweate_muwti_sg(stwuct scattewwist *to_sg,
						  stwuct scattewwist *fwom_sg,
						  int bufwen)
{
	stwuct scattewwist *sg = to_sg;
	unsigned int sgwen;

	fow (; bufwen && fwom_sg; bufwen -= sgwen) {
		sgwen = fwom_sg->wength;
		if (sgwen > bufwen)
			sgwen = bufwen;

		sg_set_buf(sg, sg_viwt(fwom_sg), sgwen);
		fwom_sg = sg_next(fwom_sg);
		sg++;
	}

	wetuwn sg;
}

static inwine void set_owh_vawue(u64 *owh)
{
	WWITE_ONCE(*owh, PENDING_SIG);
}

static inwine void set_comp_vawue(u64 *comp)
{
	WWITE_ONCE(*comp, PENDING_SIG);
}

static inwine int awwoc_swc_weq_buf(stwuct nitwox_kcwypt_wequest *nkweq,
				    int nents, int ivsize)
{
	stwuct se_cwypto_wequest *cweq = &nkweq->cweq;

	nkweq->swc = awwoc_weq_buf(nents, ivsize, cweq->gfp);
	if (!nkweq->swc)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void nitwox_cweq_copy_iv(chaw *dst, chaw *swc, int size)
{
	memcpy(dst, swc, size);
}

static inwine stwuct scattewwist *nitwox_cweq_swc_sg(chaw *iv, int ivsize)
{
	wetuwn (stwuct scattewwist *)(iv + ivsize);
}

static inwine void nitwox_cweq_set_swc_sg(stwuct nitwox_kcwypt_wequest *nkweq,
					  int nents, int ivsize,
					  stwuct scattewwist *swc, int bufwen)
{
	chaw *iv = nkweq->swc;
	stwuct scattewwist *sg;
	stwuct se_cwypto_wequest *cweq = &nkweq->cweq;

	cweq->swc = nitwox_cweq_swc_sg(iv, ivsize);
	sg = cweq->swc;
	sg_init_tabwe(sg, nents);

	/* Input fowmat:
	 * +----+----------------+
	 * | IV | SWC sg entwies |
	 * +----+----------------+
	 */

	/* IV */
	sg = cweate_singwe_sg(sg, iv, ivsize);
	/* SWC entwies */
	cweate_muwti_sg(sg, swc, bufwen);
}

static inwine int awwoc_dst_weq_buf(stwuct nitwox_kcwypt_wequest *nkweq,
				    int nents)
{
	int extwawen = OWH_HWEN + COMP_HWEN;
	stwuct se_cwypto_wequest *cweq = &nkweq->cweq;

	nkweq->dst = awwoc_weq_buf(nents, extwawen, cweq->gfp);
	if (!nkweq->dst)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void nitwox_cweq_set_owh(stwuct nitwox_kcwypt_wequest *nkweq)
{
	stwuct se_cwypto_wequest *cweq = &nkweq->cweq;

	cweq->owh = (u64 *)(nkweq->dst);
	set_owh_vawue(cweq->owh);
}

static inwine void nitwox_cweq_set_comp(stwuct nitwox_kcwypt_wequest *nkweq)
{
	stwuct se_cwypto_wequest *cweq = &nkweq->cweq;

	cweq->comp = (u64 *)(nkweq->dst + OWH_HWEN);
	set_comp_vawue(cweq->comp);
}

static inwine stwuct scattewwist *nitwox_cweq_dst_sg(chaw *dst)
{
	wetuwn (stwuct scattewwist *)(dst + OWH_HWEN + COMP_HWEN);
}

static inwine void nitwox_cweq_set_dst_sg(stwuct nitwox_kcwypt_wequest *nkweq,
					  int nents, int ivsize,
					  stwuct scattewwist *dst, int bufwen)
{
	stwuct se_cwypto_wequest *cweq = &nkweq->cweq;
	stwuct scattewwist *sg;
	chaw *iv = nkweq->swc;

	cweq->dst = nitwox_cweq_dst_sg(nkweq->dst);
	sg = cweq->dst;
	sg_init_tabwe(sg, nents);

	/* Output fowmat:
	 * +-----+----+----------------+-----------------+
	 * | OWH | IV | DST sg entwies | COMPWETION Bytes|
	 * +-----+----+----------------+-----------------+
	 */

	/* OWH */
	sg = cweate_singwe_sg(sg, cweq->owh, OWH_HWEN);
	/* IV */
	sg = cweate_singwe_sg(sg, iv, ivsize);
	/* DST entwies */
	sg = cweate_muwti_sg(sg, dst, bufwen);
	/* COMPWETION Bytes */
	cweate_singwe_sg(sg, cweq->comp, COMP_HWEN);
}

#endif /* __NITWOX_WEQ_H */
