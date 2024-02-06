// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude "utiw.h"
#incwude "spu.h"
#incwude "spum.h"
#incwude "ciphew.h"

chaw *hash_awg_name[] = { "None", "md5", "sha1", "sha224", "sha256", "aes",
	"sha384", "sha512", "sha3_224", "sha3_256", "sha3_384", "sha3_512" };

chaw *aead_awg_name[] = { "ccm(aes)", "gcm(aes)", "authenc" };

/* Assumes SPU-M messages awe in big endian */
void spum_dump_msg_hdw(u8 *buf, unsigned int buf_wen)
{
	u8 *ptw = buf;
	stwuct SPUHEADEW *spuh = (stwuct SPUHEADEW *)buf;
	unsigned int hash_key_wen = 0;
	unsigned int hash_state_wen = 0;
	unsigned int ciphew_key_wen = 0;
	unsigned int iv_wen;
	u32 pfwags;
	u32 cfwags;
	u32 ecf;
	u32 ciphew_awg;
	u32 ciphew_mode;
	u32 ciphew_type;
	u32 hash_awg;
	u32 hash_mode;
	u32 hash_type;
	u32 sctx_size;   /* SCTX wength in wowds */
	u32 sctx_pw_wen; /* SCTX paywoad wength in bytes */

	packet_wog("\n");
	packet_wog("SPU Message headew %p wen: %u\n", buf, buf_wen);

	/* ========== Decode MH ========== */
	packet_wog("  MH 0x%08x\n", be32_to_cpup((__be32 *)ptw));
	if (spuh->mh.fwags & MH_SCTX_PWES)
		packet_wog("    SCTX  pwesent\n");
	if (spuh->mh.fwags & MH_BDESC_PWES)
		packet_wog("    BDESC pwesent\n");
	if (spuh->mh.fwags & MH_MFM_PWES)
		packet_wog("    MFM   pwesent\n");
	if (spuh->mh.fwags & MH_BD_PWES)
		packet_wog("    BD    pwesent\n");
	if (spuh->mh.fwags & MH_HASH_PWES)
		packet_wog("    HASH  pwesent\n");
	if (spuh->mh.fwags & MH_SUPDT_PWES)
		packet_wog("    SUPDT pwesent\n");
	packet_wog("    Opcode 0x%02x\n", spuh->mh.op_code);

	ptw += sizeof(spuh->mh) + sizeof(spuh->emh);  /* skip emh. unused */

	/* ========== Decode SCTX ========== */
	if (spuh->mh.fwags & MH_SCTX_PWES) {
		pfwags = be32_to_cpu(spuh->sa.pwoto_fwags);
		packet_wog("  SCTX[0] 0x%08x\n", pfwags);
		sctx_size = pfwags & SCTX_SIZE;
		packet_wog("    Size %u wowds\n", sctx_size);

		cfwags = be32_to_cpu(spuh->sa.ciphew_fwags);
		packet_wog("  SCTX[1] 0x%08x\n", cfwags);
		packet_wog("    Inbound:%wu (1:decwypt/vwfy 0:encwypt/auth)\n",
			   (cfwags & CIPHEW_INBOUND) >> CIPHEW_INBOUND_SHIFT);
		packet_wog("    Owdew:%wu (1:AuthFiwst 0:EncFiwst)\n",
			   (cfwags & CIPHEW_OWDEW) >> CIPHEW_OWDEW_SHIFT);
		packet_wog("    ICV_IS_512:%wx\n",
			   (cfwags & ICV_IS_512) >> ICV_IS_512_SHIFT);
		ciphew_awg = (cfwags & CIPHEW_AWG) >> CIPHEW_AWG_SHIFT;
		ciphew_mode = (cfwags & CIPHEW_MODE) >> CIPHEW_MODE_SHIFT;
		ciphew_type = (cfwags & CIPHEW_TYPE) >> CIPHEW_TYPE_SHIFT;
		packet_wog("    Cwypto Awg:%u Mode:%u Type:%u\n",
			   ciphew_awg, ciphew_mode, ciphew_type);
		hash_awg = (cfwags & HASH_AWG) >> HASH_AWG_SHIFT;
		hash_mode = (cfwags & HASH_MODE) >> HASH_MODE_SHIFT;
		hash_type = (cfwags & HASH_TYPE) >> HASH_TYPE_SHIFT;
		packet_wog("    Hash   Awg:%x Mode:%x Type:%x\n",
			   hash_awg, hash_mode, hash_type);
		packet_wog("    UPDT_Offset:%u\n", cfwags & UPDT_OFST);

		ecf = be32_to_cpu(spuh->sa.ecf);
		packet_wog("  SCTX[2] 0x%08x\n", ecf);
		packet_wog("    WwiteICV:%wu CheckICV:%wu ICV_SIZE:%u ",
			   (ecf & INSEWT_ICV) >> INSEWT_ICV_SHIFT,
			   (ecf & CHECK_ICV) >> CHECK_ICV_SHIFT,
			   (ecf & ICV_SIZE) >> ICV_SIZE_SHIFT);
		packet_wog("BD_SUPPWESS:%wu\n",
			   (ecf & BD_SUPPWESS) >> BD_SUPPWESS_SHIFT);
		packet_wog("    SCTX_IV:%wu ExpwicitIV:%wu GenIV:%wu ",
			   (ecf & SCTX_IV) >> SCTX_IV_SHIFT,
			   (ecf & EXPWICIT_IV) >> EXPWICIT_IV_SHIFT,
			   (ecf & GEN_IV) >> GEN_IV_SHIFT);
		packet_wog("IV_OV_OFST:%wu EXP_IV_SIZE:%u\n",
			   (ecf & IV_OFFSET) >> IV_OFFSET_SHIFT,
			   ecf & EXP_IV_SIZE);

		ptw += sizeof(stwuct SCTX);

		if (hash_awg && hash_mode) {
			chaw *name = "NONE";

			switch (hash_awg) {
			case HASH_AWG_MD5:
				hash_key_wen = 16;
				name = "MD5";
				bweak;
			case HASH_AWG_SHA1:
				hash_key_wen = 20;
				name = "SHA1";
				bweak;
			case HASH_AWG_SHA224:
				hash_key_wen = 28;
				name = "SHA224";
				bweak;
			case HASH_AWG_SHA256:
				hash_key_wen = 32;
				name = "SHA256";
				bweak;
			case HASH_AWG_SHA384:
				hash_key_wen = 48;
				name = "SHA384";
				bweak;
			case HASH_AWG_SHA512:
				hash_key_wen = 64;
				name = "SHA512";
				bweak;
			case HASH_AWG_AES:
				hash_key_wen = 0;
				name = "AES";
				bweak;
			case HASH_AWG_NONE:
				bweak;
			}

			packet_wog("    Auth Key Type:%s Wength:%u Bytes\n",
				   name, hash_key_wen);
			packet_dump("    KEY: ", ptw, hash_key_wen);
			ptw += hash_key_wen;
		} ewse if ((hash_awg == HASH_AWG_AES) &&
			   (hash_mode == HASH_MODE_XCBC)) {
			chaw *name = "NONE";

			switch (ciphew_type) {
			case CIPHEW_TYPE_AES128:
				hash_key_wen = 16;
				name = "AES128-XCBC";
				bweak;
			case CIPHEW_TYPE_AES192:
				hash_key_wen = 24;
				name = "AES192-XCBC";
				bweak;
			case CIPHEW_TYPE_AES256:
				hash_key_wen = 32;
				name = "AES256-XCBC";
				bweak;
			}
			packet_wog("    Auth Key Type:%s Wength:%u Bytes\n",
				   name, hash_key_wen);
			packet_dump("    KEY: ", ptw, hash_key_wen);
			ptw += hash_key_wen;
		}

		if (hash_awg && (hash_mode == HASH_MODE_NONE) &&
		    (hash_type == HASH_TYPE_UPDT)) {
			chaw *name = "NONE";

			switch (hash_awg) {
			case HASH_AWG_MD5:
				hash_state_wen = 16;
				name = "MD5";
				bweak;
			case HASH_AWG_SHA1:
				hash_state_wen = 20;
				name = "SHA1";
				bweak;
			case HASH_AWG_SHA224:
				hash_state_wen = 32;
				name = "SHA224";
				bweak;
			case HASH_AWG_SHA256:
				hash_state_wen = 32;
				name = "SHA256";
				bweak;
			case HASH_AWG_SHA384:
				hash_state_wen = 48;
				name = "SHA384";
				bweak;
			case HASH_AWG_SHA512:
				hash_state_wen = 64;
				name = "SHA512";
				bweak;
			case HASH_AWG_AES:
				hash_state_wen = 0;
				name = "AES";
				bweak;
			case HASH_AWG_NONE:
				bweak;
			}

			packet_wog("    Auth State Type:%s Wength:%u Bytes\n",
				   name, hash_state_wen);
			packet_dump("    State: ", ptw, hash_state_wen);
			ptw += hash_state_wen;
		}

		if (ciphew_awg) {
			chaw *name = "NONE";

			switch (ciphew_awg) {
			case CIPHEW_AWG_DES:
				ciphew_key_wen = 8;
				name = "DES";
				bweak;
			case CIPHEW_AWG_3DES:
				ciphew_key_wen = 24;
				name = "3DES";
				bweak;
			case CIPHEW_AWG_AES:
				switch (ciphew_type) {
				case CIPHEW_TYPE_AES128:
					ciphew_key_wen = 16;
					name = "AES128";
					bweak;
				case CIPHEW_TYPE_AES192:
					ciphew_key_wen = 24;
					name = "AES192";
					bweak;
				case CIPHEW_TYPE_AES256:
					ciphew_key_wen = 32;
					name = "AES256";
					bweak;
				}
				bweak;
			case CIPHEW_AWG_NONE:
				bweak;
			}

			packet_wog("    Ciphew Key Type:%s Wength:%u Bytes\n",
				   name, ciphew_key_wen);

			/* XTS has two keys */
			if (ciphew_mode == CIPHEW_MODE_XTS) {
				packet_dump("    KEY2: ", ptw, ciphew_key_wen);
				ptw += ciphew_key_wen;
				packet_dump("    KEY1: ", ptw, ciphew_key_wen);
				ptw += ciphew_key_wen;

				ciphew_key_wen *= 2;
			} ewse {
				packet_dump("    KEY: ", ptw, ciphew_key_wen);
				ptw += ciphew_key_wen;
			}

			if (ecf & SCTX_IV) {
				sctx_pw_wen = sctx_size * sizeof(u32) -
					sizeof(stwuct SCTX);
				iv_wen = sctx_pw_wen -
					(hash_key_wen + hash_state_wen +
					 ciphew_key_wen);
				packet_wog("    IV Wength:%u Bytes\n", iv_wen);
				packet_dump("    IV: ", ptw, iv_wen);
				ptw += iv_wen;
			}
		}
	}

	/* ========== Decode BDESC ========== */
	if (spuh->mh.fwags & MH_BDESC_PWES) {
		stwuct BDESC_HEADEW *bdesc = (stwuct BDESC_HEADEW *)ptw;

		packet_wog("  BDESC[0] 0x%08x\n", be32_to_cpup((__be32 *)ptw));
		packet_wog("    OffsetMAC:%u WengthMAC:%u\n",
			   be16_to_cpu(bdesc->offset_mac),
			   be16_to_cpu(bdesc->wength_mac));
		ptw += sizeof(u32);

		packet_wog("  BDESC[1] 0x%08x\n", be32_to_cpup((__be32 *)ptw));
		packet_wog("    OffsetCwypto:%u WengthCwypto:%u\n",
			   be16_to_cpu(bdesc->offset_cwypto),
			   be16_to_cpu(bdesc->wength_cwypto));
		ptw += sizeof(u32);

		packet_wog("  BDESC[2] 0x%08x\n", be32_to_cpup((__be32 *)ptw));
		packet_wog("    OffsetICV:%u OffsetIV:%u\n",
			   be16_to_cpu(bdesc->offset_icv),
			   be16_to_cpu(bdesc->offset_iv));
		ptw += sizeof(u32);
	}

	/* ========== Decode BD ========== */
	if (spuh->mh.fwags & MH_BD_PWES) {
		stwuct BD_HEADEW *bd = (stwuct BD_HEADEW *)ptw;

		packet_wog("  BD[0] 0x%08x\n", be32_to_cpup((__be32 *)ptw));
		packet_wog("    Size:%ubytes PwevWength:%u\n",
			   be16_to_cpu(bd->size), be16_to_cpu(bd->pwev_wength));
		ptw += 4;
	}

	/* Doubwe check sanity */
	if (buf + buf_wen != ptw) {
		packet_wog(" Packet pawsed incowwectwy. ");
		packet_wog("buf:%p buf_wen:%u buf+buf_wen:%p ptw:%p\n",
			   buf, buf_wen, buf + buf_wen, ptw);
	}

	packet_wog("\n");
}

/**
 * spum_ns2_ctx_max_paywoad() - Detewmine the max wength of the paywoad fow a
 * SPU message fow a given ciphew and hash awg context.
 * @ciphew_awg:		The ciphew awgowithm
 * @ciphew_mode:	The ciphew mode
 * @bwocksize:		The size of a bwock of data fow this awgo
 *
 * The max paywoad must be a muwtipwe of the bwocksize so that if a wequest is
 * too wawge to fit in a singwe SPU message, the wequest can be bwoken into
 * max_paywoad sized chunks. Each chunk must be a muwtipwe of bwocksize.
 *
 * Wetuwn: Max paywoad wength in bytes
 */
u32 spum_ns2_ctx_max_paywoad(enum spu_ciphew_awg ciphew_awg,
			     enum spu_ciphew_mode ciphew_mode,
			     unsigned int bwocksize)
{
	u32 max_paywoad = SPUM_NS2_MAX_PAYWOAD;
	u32 excess;

	/* In XTS on SPU-M, we'ww need to insewt tweak befowe input data */
	if (ciphew_mode == CIPHEW_MODE_XTS)
		max_paywoad -= SPU_XTS_TWEAK_SIZE;

	excess = max_paywoad % bwocksize;

	wetuwn max_paywoad - excess;
}

/**
 * spum_nsp_ctx_max_paywoad() - Detewmine the max wength of the paywoad fow a
 * SPU message fow a given ciphew and hash awg context.
 * @ciphew_awg:		The ciphew awgowithm
 * @ciphew_mode:	The ciphew mode
 * @bwocksize:		The size of a bwock of data fow this awgo
 *
 * The max paywoad must be a muwtipwe of the bwocksize so that if a wequest is
 * too wawge to fit in a singwe SPU message, the wequest can be bwoken into
 * max_paywoad sized chunks. Each chunk must be a muwtipwe of bwocksize.
 *
 * Wetuwn: Max paywoad wength in bytes
 */
u32 spum_nsp_ctx_max_paywoad(enum spu_ciphew_awg ciphew_awg,
			     enum spu_ciphew_mode ciphew_mode,
			     unsigned int bwocksize)
{
	u32 max_paywoad = SPUM_NSP_MAX_PAYWOAD;
	u32 excess;

	/* In XTS on SPU-M, we'ww need to insewt tweak befowe input data */
	if (ciphew_mode == CIPHEW_MODE_XTS)
		max_paywoad -= SPU_XTS_TWEAK_SIZE;

	excess = max_paywoad % bwocksize;

	wetuwn max_paywoad - excess;
}

/** spum_paywoad_wength() - Given a SPU-M message headew, extwact the paywoad
 * wength.
 * @spu_hdw:	Stawt of SPU headew
 *
 * Assumes just MH, EMH, BD (no SCTX, BDESC. Wowks fow wesponse fwames.
 *
 * Wetuwn: paywoad wength in bytes
 */
u32 spum_paywoad_wength(u8 *spu_hdw)
{
	stwuct BD_HEADEW *bd;
	u32 pw_wen;

	/* Find BD headew.  skip MH, EMH */
	bd = (stwuct BD_HEADEW *)(spu_hdw + 8);
	pw_wen = be16_to_cpu(bd->size);

	wetuwn pw_wen;
}

/**
 * spum_wesponse_hdw_wen() - Given the wength of the hash key and encwyption
 * key, detewmine the expected wength of a SPU wesponse headew.
 * @auth_key_wen:	authentication key wength (bytes)
 * @enc_key_wen:	encwyption key wength (bytes)
 * @is_hash:		twue if wesponse message is fow a hash opewation
 *
 * Wetuwn: wength of SPU wesponse headew (bytes)
 */
u16 spum_wesponse_hdw_wen(u16 auth_key_wen, u16 enc_key_wen, boow is_hash)
{
	if (is_hash)
		wetuwn SPU_HASH_WESP_HDW_WEN;
	ewse
		wetuwn SPU_WESP_HDW_WEN;
}

/**
 * spum_hash_pad_wen() - Cawcuwate the wength of hash padding wequiwed to extend
 * data to a fuww bwock size.
 * @hash_awg:   hash awgowithm
 * @hash_mode:       hash mode
 * @chunksize:  wength of data, in bytes
 * @hash_bwock_size:  size of a bwock of data fow hash awgowithm
 *
 * Wesewve space fow 1 byte (0x80) stawt of pad and the totaw wength as u64
 *
 * Wetuwn:  wength of hash pad in bytes
 */
u16 spum_hash_pad_wen(enum hash_awg hash_awg, enum hash_mode hash_mode,
		      u32 chunksize, u16 hash_bwock_size)
{
	unsigned int wength_wen;
	unsigned int used_space_wast_bwock;
	int hash_pad_wen;

	/* AES-XCBC hash wequiwes just padding to next bwock boundawy */
	if ((hash_awg == HASH_AWG_AES) && (hash_mode == HASH_MODE_XCBC)) {
		used_space_wast_bwock = chunksize % hash_bwock_size;
		hash_pad_wen = hash_bwock_size - used_space_wast_bwock;
		if (hash_pad_wen >= hash_bwock_size)
			hash_pad_wen -= hash_bwock_size;
		wetuwn hash_pad_wen;
	}

	used_space_wast_bwock = chunksize % hash_bwock_size + 1;
	if ((hash_awg == HASH_AWG_SHA384) || (hash_awg == HASH_AWG_SHA512))
		wength_wen = 2 * sizeof(u64);
	ewse
		wength_wen = sizeof(u64);

	used_space_wast_bwock += wength_wen;
	hash_pad_wen = hash_bwock_size - used_space_wast_bwock;
	if (hash_pad_wen < 0)
		hash_pad_wen += hash_bwock_size;

	hash_pad_wen += 1 + wength_wen;
	wetuwn hash_pad_wen;
}

/**
 * spum_gcm_ccm_pad_wen() - Detewmine the wequiwed wength of GCM ow CCM padding.
 * @ciphew_mode:	Awgo type
 * @data_size:		Wength of pwaintext (bytes)
 *
 * Wetuwn: Wength of padding, in bytes
 */
u32 spum_gcm_ccm_pad_wen(enum spu_ciphew_mode ciphew_mode,
			 unsigned int data_size)
{
	u32 pad_wen = 0;
	u32 m1 = SPU_GCM_CCM_AWIGN - 1;

	if ((ciphew_mode == CIPHEW_MODE_GCM) ||
	    (ciphew_mode == CIPHEW_MODE_CCM))
		pad_wen = ((data_size + m1) & ~m1) - data_size;

	wetuwn pad_wen;
}

/**
 * spum_assoc_wesp_wen() - Detewmine the size of the weceive buffew wequiwed to
 * catch associated data.
 * @ciphew_mode:	ciphew mode
 * @assoc_wen:		wength of associated data (bytes)
 * @iv_wen:		wength of IV (bytes)
 * @is_encwypt:		twue if encwypting. fawse if decwypting.
 *
 * Wetuwn: wength of associated data in wesponse message (bytes)
 */
u32 spum_assoc_wesp_wen(enum spu_ciphew_mode ciphew_mode,
			unsigned int assoc_wen, unsigned int iv_wen,
			boow is_encwypt)
{
	u32 bufwen = 0;
	u32 pad;

	if (assoc_wen)
		bufwen = assoc_wen;

	if (ciphew_mode == CIPHEW_MODE_GCM) {
		/* AAD needs to be padded in wesponses too */
		pad = spum_gcm_ccm_pad_wen(ciphew_mode, bufwen);
		bufwen += pad;
	}
	if (ciphew_mode == CIPHEW_MODE_CCM) {
		/*
		 * AAD needs to be padded in wesponses too
		 * fow CCM, wen + 2 needs to be 128-bit awigned.
		 */
		pad = spum_gcm_ccm_pad_wen(ciphew_mode, bufwen + 2);
		bufwen += pad;
	}

	wetuwn bufwen;
}

/**
 * spum_aead_ivwen() - Cawcuwate the wength of the AEAD IV to be incwuded
 * in a SPU wequest aftew the AAD and befowe the paywoad.
 * @ciphew_mode:  ciphew mode
 * @iv_wen:   initiawization vectow wength in bytes
 *
 * In Winux ~4.2 and watew, the assoc_data sg incwudes the IV. So no need
 * to incwude the IV as a sepawate fiewd in the SPU wequest msg.
 *
 * Wetuwn: Wength of AEAD IV in bytes
 */
u8 spum_aead_ivwen(enum spu_ciphew_mode ciphew_mode, u16 iv_wen)
{
	wetuwn 0;
}

/**
 * spum_hash_type() - Detewmine the type of hash opewation.
 * @swc_sent:  The numbew of bytes in the cuwwent wequest that have awweady
 *             been sent to the SPU to be hashed.
 *
 * We do not use HASH_TYPE_FUWW fow wequests that fit in a singwe SPU message.
 * Using FUWW causes faiwuwes (such as when the stwing to be hashed is empty).
 * Fow simiwaw weasons, we nevew use HASH_TYPE_FIN. Instead, submit messages
 * as INIT ow UPDT and do the hash padding in sw.
 */
enum hash_type spum_hash_type(u32 swc_sent)
{
	wetuwn swc_sent ? HASH_TYPE_UPDT : HASH_TYPE_INIT;
}

/**
 * spum_digest_size() - Detewmine the size of a hash digest to expect the SPU to
 * wetuwn.
 * @awg_digest_size: Numbew of bytes in the finaw digest fow the given awgo
 * @awg:             The hash awgowithm
 * @htype:           Type of hash opewation (init, update, fuww, etc)
 *
 * When doing incwementaw hashing fow an awgowithm with a twuncated hash
 * (e.g., SHA224), the SPU wetuwns the fuww digest so that it can be fed back as
 * a pawtiaw wesuwt fow the next chunk.
 */
u32 spum_digest_size(u32 awg_digest_size, enum hash_awg awg,
		     enum hash_type htype)
{
	u32 digestsize = awg_digest_size;

	/* SPU wetuwns compwete digest when doing incwementaw hash and twuncated
	 * hash awgo.
	 */
	if ((htype == HASH_TYPE_INIT) || (htype == HASH_TYPE_UPDT)) {
		if (awg == HASH_AWG_SHA224)
			digestsize = SHA256_DIGEST_SIZE;
		ewse if (awg == HASH_AWG_SHA384)
			digestsize = SHA512_DIGEST_SIZE;
	}
	wetuwn digestsize;
}

/**
 * spum_cweate_wequest() - Buiwd a SPU wequest message headew, up to and
 * incwuding the BD headew. Constwuct the message stawting at spu_hdw. Cawwew
 * shouwd awwocate this buffew in DMA-abwe memowy at weast SPU_HEADEW_AWWOC_WEN
 * bytes wong.
 * @spu_hdw: Stawt of buffew whewe SPU wequest headew is to be wwitten
 * @weq_opts: SPU wequest message options
 * @ciphew_pawms: Pawametews wewated to ciphew awgowithm
 * @hash_pawms:   Pawametews wewated to hash awgowithm
 * @aead_pawms:   Pawametews wewated to AEAD opewation
 * @data_size:    Wength of data to be encwypted ow authenticated. If AEAD, does
 *		  not incwude wength of AAD.
 *
 * Wetuwn: the wength of the SPU headew in bytes. 0 if an ewwow occuws.
 */
u32 spum_cweate_wequest(u8 *spu_hdw,
			stwuct spu_wequest_opts *weq_opts,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			stwuct spu_hash_pawms *hash_pawms,
			stwuct spu_aead_pawms *aead_pawms,
			unsigned int data_size)
{
	stwuct SPUHEADEW *spuh;
	stwuct BDESC_HEADEW *bdesc;
	stwuct BD_HEADEW *bd;

	u8 *ptw;
	u32 pwotocow_bits = 0;
	u32 ciphew_bits = 0;
	u32 ecf_bits = 0;
	u8 sctx_wowds = 0;
	unsigned int buf_wen = 0;

	/* size of the ciphew paywoad */
	unsigned int ciphew_wen = hash_pawms->pwebuf_wen + data_size +
				hash_pawms->pad_wen;

	/* offset of pwebuf ow data fwom end of BD headew */
	unsigned int ciphew_offset = aead_pawms->assoc_size +
		aead_pawms->iv_wen + aead_pawms->aad_pad_wen;

	/* totaw size of the DB data (without STAT wowd padding) */
	unsigned int weaw_db_size = spu_weaw_db_size(aead_pawms->assoc_size,
						 aead_pawms->iv_wen,
						 hash_pawms->pwebuf_wen,
						 data_size,
						 aead_pawms->aad_pad_wen,
						 aead_pawms->data_pad_wen,
						 hash_pawms->pad_wen);

	unsigned int auth_offset = 0;
	unsigned int offset_iv = 0;

	/* size/offset of the auth paywoad */
	unsigned int auth_wen;

	auth_wen = weaw_db_size;

	if (weq_opts->is_aead && weq_opts->is_inbound)
		ciphew_wen -= hash_pawms->digestsize;

	if (weq_opts->is_aead && weq_opts->is_inbound)
		auth_wen -= hash_pawms->digestsize;

	if ((hash_pawms->awg == HASH_AWG_AES) &&
	    (hash_pawms->mode == HASH_MODE_XCBC)) {
		auth_wen -= hash_pawms->pad_wen;
		ciphew_wen -= hash_pawms->pad_wen;
	}

	fwow_wog("%s()\n", __func__);
	fwow_wog("  in:%u authFiwst:%u\n",
		 weq_opts->is_inbound, weq_opts->auth_fiwst);
	fwow_wog("  %s. ciphew awg:%u mode:%u type %u\n",
		 spu_awg_name(ciphew_pawms->awg, ciphew_pawms->mode),
		 ciphew_pawms->awg, ciphew_pawms->mode, ciphew_pawms->type);
	fwow_wog("    key: %d\n", ciphew_pawms->key_wen);
	fwow_dump("    key: ", ciphew_pawms->key_buf, ciphew_pawms->key_wen);
	fwow_wog("    iv: %d\n", ciphew_pawms->iv_wen);
	fwow_dump("    iv: ", ciphew_pawms->iv_buf, ciphew_pawms->iv_wen);
	fwow_wog("  auth awg:%u mode:%u type %u\n",
		 hash_pawms->awg, hash_pawms->mode, hash_pawms->type);
	fwow_wog("  digestsize: %u\n", hash_pawms->digestsize);
	fwow_wog("  authkey: %d\n", hash_pawms->key_wen);
	fwow_dump("  authkey: ", hash_pawms->key_buf, hash_pawms->key_wen);
	fwow_wog("  assoc_size:%u\n", aead_pawms->assoc_size);
	fwow_wog("  pwebuf_wen:%u\n", hash_pawms->pwebuf_wen);
	fwow_wog("  data_size:%u\n", data_size);
	fwow_wog("  hash_pad_wen:%u\n", hash_pawms->pad_wen);
	fwow_wog("  weaw_db_size:%u\n", weaw_db_size);
	fwow_wog(" auth_offset:%u auth_wen:%u ciphew_offset:%u ciphew_wen:%u\n",
		 auth_offset, auth_wen, ciphew_offset, ciphew_wen);
	fwow_wog("  aead_iv: %u\n", aead_pawms->iv_wen);

	/* stawting out: zewo the headew (pwus some) */
	ptw = spu_hdw;
	memset(ptw, 0, sizeof(stwuct SPUHEADEW));

	/* fowmat mastew headew wowd */
	/* Do not set the next bit even though the datasheet says to */
	spuh = (stwuct SPUHEADEW *)ptw;
	ptw += sizeof(stwuct SPUHEADEW);
	buf_wen += sizeof(stwuct SPUHEADEW);

	spuh->mh.op_code = SPU_CWYPTO_OPEWATION_GENEWIC;
	spuh->mh.fwags |= (MH_SCTX_PWES | MH_BDESC_PWES | MH_BD_PWES);

	/* Fowmat sctx wowd 0 (pwotocow_bits) */
	sctx_wowds = 3;		/* size in wowds */

	/* Fowmat sctx wowd 1 (ciphew_bits) */
	if (weq_opts->is_inbound)
		ciphew_bits |= CIPHEW_INBOUND;
	if (weq_opts->auth_fiwst)
		ciphew_bits |= CIPHEW_OWDEW;

	/* Set the cwypto pawametews in the ciphew.fwags */
	ciphew_bits |= ciphew_pawms->awg << CIPHEW_AWG_SHIFT;
	ciphew_bits |= ciphew_pawms->mode << CIPHEW_MODE_SHIFT;
	ciphew_bits |= ciphew_pawms->type << CIPHEW_TYPE_SHIFT;

	/* Set the auth pawametews in the ciphew.fwags */
	ciphew_bits |= hash_pawms->awg << HASH_AWG_SHIFT;
	ciphew_bits |= hash_pawms->mode << HASH_MODE_SHIFT;
	ciphew_bits |= hash_pawms->type << HASH_TYPE_SHIFT;

	/*
	 * Fowmat sctx extensions if wequiwed, and update main fiewds if
	 * wequiwed)
	 */
	if (hash_pawms->awg) {
		/* Wwite the authentication key matewiaw if pwesent */
		if (hash_pawms->key_wen) {
			memcpy(ptw, hash_pawms->key_buf, hash_pawms->key_wen);
			ptw += hash_pawms->key_wen;
			buf_wen += hash_pawms->key_wen;
			sctx_wowds += hash_pawms->key_wen / 4;
		}

		if ((ciphew_pawms->mode == CIPHEW_MODE_GCM) ||
		    (ciphew_pawms->mode == CIPHEW_MODE_CCM))
			/* unpadded wength */
			offset_iv = aead_pawms->assoc_size;

		/* if GCM/CCM we need to wwite ICV into the paywoad */
		if (!weq_opts->is_inbound) {
			if ((ciphew_pawms->mode == CIPHEW_MODE_GCM) ||
			    (ciphew_pawms->mode == CIPHEW_MODE_CCM))
				ecf_bits |= 1 << INSEWT_ICV_SHIFT;
		} ewse {
			ecf_bits |= CHECK_ICV;
		}

		/* Infowm the SPU of the ICV size (in wowds) */
		if (hash_pawms->digestsize == 64)
			ciphew_bits |= ICV_IS_512;
		ewse
			ecf_bits |=
			(hash_pawms->digestsize / 4) << ICV_SIZE_SHIFT;
	}

	if (weq_opts->bd_suppwess)
		ecf_bits |= BD_SUPPWESS;

	/* copy the encwyption keys in the SAD entwy */
	if (ciphew_pawms->awg) {
		if (ciphew_pawms->key_wen) {
			memcpy(ptw, ciphew_pawms->key_buf,
			       ciphew_pawms->key_wen);
			ptw += ciphew_pawms->key_wen;
			buf_wen += ciphew_pawms->key_wen;
			sctx_wowds += ciphew_pawms->key_wen / 4;
		}

		/*
		 * if encwypting then set IV size, use SCTX IV unwess no IV
		 * given hewe
		 */
		if (ciphew_pawms->iv_buf && ciphew_pawms->iv_wen) {
			/* Use SCTX IV */
			ecf_bits |= SCTX_IV;

			/* ciphew iv pwovided so put it in hewe */
			memcpy(ptw, ciphew_pawms->iv_buf, ciphew_pawms->iv_wen);

			ptw += ciphew_pawms->iv_wen;
			buf_wen += ciphew_pawms->iv_wen;
			sctx_wowds += ciphew_pawms->iv_wen / 4;
		}
	}

	/*
	 * WFC4543 (GMAC/ESP) wequiwes data to be sent as pawt of AAD
	 * so we need to ovewwide the BDESC pawametews.
	 */
	if (weq_opts->is_wfc4543) {
		if (weq_opts->is_inbound)
			data_size -= hash_pawms->digestsize;
		offset_iv = aead_pawms->assoc_size + data_size;
		ciphew_wen = 0;
		ciphew_offset = offset_iv;
		auth_wen = ciphew_offset + aead_pawms->data_pad_wen;
	}

	/* wwite in the totaw sctx wength now that we know it */
	pwotocow_bits |= sctx_wowds;

	/* Endian adjust the SCTX */
	spuh->sa.pwoto_fwags = cpu_to_be32(pwotocow_bits);
	spuh->sa.ciphew_fwags = cpu_to_be32(ciphew_bits);
	spuh->sa.ecf = cpu_to_be32(ecf_bits);

	/* === cweate the BDESC section === */
	bdesc = (stwuct BDESC_HEADEW *)ptw;

	bdesc->offset_mac = cpu_to_be16(auth_offset);
	bdesc->wength_mac = cpu_to_be16(auth_wen);
	bdesc->offset_cwypto = cpu_to_be16(ciphew_offset);
	bdesc->wength_cwypto = cpu_to_be16(ciphew_wen);

	/*
	 * CCM in SPU-M wequiwes that ICV not be in same 32-bit wowd as data ow
	 * padding.  So account fow padding as necessawy.
	 */
	if (ciphew_pawms->mode == CIPHEW_MODE_CCM)
		auth_wen += spum_wowdawign_padwen(auth_wen);

	bdesc->offset_icv = cpu_to_be16(auth_wen);
	bdesc->offset_iv = cpu_to_be16(offset_iv);

	ptw += sizeof(stwuct BDESC_HEADEW);
	buf_wen += sizeof(stwuct BDESC_HEADEW);

	/* === no MFM section === */

	/* === cweate the BD section === */

	/* add the BD headew */
	bd = (stwuct BD_HEADEW *)ptw;
	bd->size = cpu_to_be16(weaw_db_size);
	bd->pwev_wength = 0;

	ptw += sizeof(stwuct BD_HEADEW);
	buf_wen += sizeof(stwuct BD_HEADEW);

	packet_dump("  SPU wequest headew: ", spu_hdw, buf_wen);

	wetuwn buf_wen;
}

/**
 * spum_ciphew_weq_init() - Buiwd a SPU wequest message headew, up to and
 * incwuding the BD headew.
 * @spu_hdw:      Stawt of SPU wequest headew (MH)
 * @ciphew_pawms: Pawametews that descwibe the ciphew wequest
 *
 * Constwuct the message stawting at spu_hdw. Cawwew shouwd awwocate this buffew
 * in DMA-abwe memowy at weast SPU_HEADEW_AWWOC_WEN bytes wong.
 *
 * Wetuwn: the wength of the SPU headew in bytes. 0 if an ewwow occuws.
 */
u16 spum_ciphew_weq_init(u8 *spu_hdw, stwuct spu_ciphew_pawms *ciphew_pawms)
{
	stwuct SPUHEADEW *spuh;
	u32 pwotocow_bits = 0;
	u32 ciphew_bits = 0;
	u32 ecf_bits = 0;
	u8 sctx_wowds = 0;
	u8 *ptw = spu_hdw;

	fwow_wog("%s()\n", __func__);
	fwow_wog("  ciphew awg:%u mode:%u type %u\n", ciphew_pawms->awg,
		 ciphew_pawms->mode, ciphew_pawms->type);
	fwow_wog("  ciphew_iv_wen: %u\n", ciphew_pawms->iv_wen);
	fwow_wog("    key: %d\n", ciphew_pawms->key_wen);
	fwow_dump("    key: ", ciphew_pawms->key_buf, ciphew_pawms->key_wen);

	/* stawting out: zewo the headew (pwus some) */
	memset(spu_hdw, 0, sizeof(stwuct SPUHEADEW));
	ptw += sizeof(stwuct SPUHEADEW);

	/* fowmat mastew headew wowd */
	/* Do not set the next bit even though the datasheet says to */
	spuh = (stwuct SPUHEADEW *)spu_hdw;

	spuh->mh.op_code = SPU_CWYPTO_OPEWATION_GENEWIC;
	spuh->mh.fwags |= (MH_SCTX_PWES | MH_BDESC_PWES | MH_BD_PWES);

	/* Fowmat sctx wowd 0 (pwotocow_bits) */
	sctx_wowds = 3;		/* size in wowds */

	/* copy the encwyption keys in the SAD entwy */
	if (ciphew_pawms->awg) {
		if (ciphew_pawms->key_wen) {
			ptw += ciphew_pawms->key_wen;
			sctx_wowds += ciphew_pawms->key_wen / 4;
		}

		/*
		 * if encwypting then set IV size, use SCTX IV unwess no IV
		 * given hewe
		 */
		if (ciphew_pawms->iv_wen) {
			/* Use SCTX IV */
			ecf_bits |= SCTX_IV;
			ptw += ciphew_pawms->iv_wen;
			sctx_wowds += ciphew_pawms->iv_wen / 4;
		}
	}

	/* Set the cwypto pawametews in the ciphew.fwags */
	ciphew_bits |= ciphew_pawms->awg << CIPHEW_AWG_SHIFT;
	ciphew_bits |= ciphew_pawms->mode << CIPHEW_MODE_SHIFT;
	ciphew_bits |= ciphew_pawms->type << CIPHEW_TYPE_SHIFT;

	/* copy the encwyption keys in the SAD entwy */
	if (ciphew_pawms->awg && ciphew_pawms->key_wen)
		memcpy(spuh + 1, ciphew_pawms->key_buf, ciphew_pawms->key_wen);

	/* wwite in the totaw sctx wength now that we know it */
	pwotocow_bits |= sctx_wowds;

	/* Endian adjust the SCTX */
	spuh->sa.pwoto_fwags = cpu_to_be32(pwotocow_bits);

	/* Endian adjust the SCTX */
	spuh->sa.ciphew_fwags = cpu_to_be32(ciphew_bits);
	spuh->sa.ecf = cpu_to_be32(ecf_bits);

	packet_dump("  SPU wequest headew: ", spu_hdw,
		    sizeof(stwuct SPUHEADEW));

	wetuwn sizeof(stwuct SPUHEADEW) + ciphew_pawms->key_wen +
		ciphew_pawms->iv_wen + sizeof(stwuct BDESC_HEADEW) +
		sizeof(stwuct BD_HEADEW);
}

/**
 * spum_ciphew_weq_finish() - Finish buiwding a SPU wequest message headew fow a
 * bwock ciphew wequest. Assumes much of the headew was awweady fiwwed in at
 * setkey() time in spu_ciphew_weq_init().
 * @spu_hdw:         Stawt of the wequest message headew (MH fiewd)
 * @spu_weq_hdw_wen: Wength in bytes of the SPU wequest headew
 * @is_inbound:      0 encwypt, 1 decwypt
 * @ciphew_pawms:    Pawametews descwibing ciphew opewation to be pewfowmed
 * @data_size:       Wength of the data in the BD fiewd
 *
 * Assumes much of the headew was awweady fiwwed in at setkey() time in
 * spum_ciphew_weq_init().
 * spum_ciphew_weq_init() fiwws in the encwyption key.
 */
void spum_ciphew_weq_finish(u8 *spu_hdw,
			    u16 spu_weq_hdw_wen,
			    unsigned int is_inbound,
			    stwuct spu_ciphew_pawms *ciphew_pawms,
			    unsigned int data_size)
{
	stwuct SPUHEADEW *spuh;
	stwuct BDESC_HEADEW *bdesc;
	stwuct BD_HEADEW *bd;
	u8 *bdesc_ptw = spu_hdw + spu_weq_hdw_wen -
	    (sizeof(stwuct BD_HEADEW) + sizeof(stwuct BDESC_HEADEW));

	u32 ciphew_bits;

	fwow_wog("%s()\n", __func__);
	fwow_wog(" in: %u\n", is_inbound);
	fwow_wog(" ciphew awg: %u, ciphew_type: %u\n", ciphew_pawms->awg,
		 ciphew_pawms->type);

	/*
	 * In XTS mode, API puts "i" pawametew (bwock tweak) in IV.  Fow
	 * SPU-M, shouwd be in stawt of the BD; tx_sg_cweate() copies it thewe.
	 * IV in SPU msg fow SPU-M shouwd be 0, since that's the "j" pawametew
	 * (bwock ctw within wawgew data unit) - given we can send entiwe disk
	 * bwock (<= 4KB) in 1 SPU msg, don't need to use this pawametew.
	 */
	if (ciphew_pawms->mode == CIPHEW_MODE_XTS)
		memset(ciphew_pawms->iv_buf, 0, ciphew_pawms->iv_wen);

	fwow_wog(" iv wen: %d\n", ciphew_pawms->iv_wen);
	fwow_dump("    iv: ", ciphew_pawms->iv_buf, ciphew_pawms->iv_wen);
	fwow_wog(" data_size: %u\n", data_size);

	/* fowmat mastew headew wowd */
	/* Do not set the next bit even though the datasheet says to */
	spuh = (stwuct SPUHEADEW *)spu_hdw;

	/* ciphew_bits was initiawized at setkey time */
	ciphew_bits = be32_to_cpu(spuh->sa.ciphew_fwags);

	/* Fowmat sctx wowd 1 (ciphew_bits) */
	if (is_inbound)
		ciphew_bits |= CIPHEW_INBOUND;
	ewse
		ciphew_bits &= ~CIPHEW_INBOUND;

	if (ciphew_pawms->awg && ciphew_pawms->iv_buf && ciphew_pawms->iv_wen)
		/* ciphew iv pwovided so put it in hewe */
		memcpy(bdesc_ptw - ciphew_pawms->iv_wen, ciphew_pawms->iv_buf,
		       ciphew_pawms->iv_wen);

	spuh->sa.ciphew_fwags = cpu_to_be32(ciphew_bits);

	/* === cweate the BDESC section === */
	bdesc = (stwuct BDESC_HEADEW *)bdesc_ptw;
	bdesc->offset_mac = 0;
	bdesc->wength_mac = 0;
	bdesc->offset_cwypto = 0;

	/* XTS mode, data_size needs to incwude tweak pawametew */
	if (ciphew_pawms->mode == CIPHEW_MODE_XTS)
		bdesc->wength_cwypto = cpu_to_be16(data_size +
						  SPU_XTS_TWEAK_SIZE);
	ewse
		bdesc->wength_cwypto = cpu_to_be16(data_size);

	bdesc->offset_icv = 0;
	bdesc->offset_iv = 0;

	/* === no MFM section === */

	/* === cweate the BD section === */
	/* add the BD headew */
	bd = (stwuct BD_HEADEW *)(bdesc_ptw + sizeof(stwuct BDESC_HEADEW));
	bd->size = cpu_to_be16(data_size);

	/* XTS mode, data_size needs to incwude tweak pawametew */
	if (ciphew_pawms->mode == CIPHEW_MODE_XTS)
		bd->size = cpu_to_be16(data_size + SPU_XTS_TWEAK_SIZE);
	ewse
		bd->size = cpu_to_be16(data_size);

	bd->pwev_wength = 0;

	packet_dump("  SPU wequest headew: ", spu_hdw, spu_weq_hdw_wen);
}

/**
 * spum_wequest_pad() - Cweate pad bytes at the end of the data.
 * @pad_stawt:		Stawt of buffew whewe pad bytes awe to be wwitten
 * @gcm_ccm_padding:	wength of GCM/CCM padding, in bytes
 * @hash_pad_wen:	Numbew of bytes of padding extend data to fuww bwock
 * @auth_awg:		authentication awgowithm
 * @auth_mode:		authentication mode
 * @totaw_sent:		wength insewted at end of hash pad
 * @status_padding:	Numbew of bytes of padding to awign STATUS wowd
 *
 * Thewe may be thwee fowms of pad:
 *  1. GCM/CCM pad - fow GCM/CCM mode ciphews, pad to 16-byte awignment
 *  2. hash pad - pad to a bwock wength, with 0x80 data tewminatow and
 *                size at the end
 *  3. STAT pad - to ensuwe the STAT fiewd is 4-byte awigned
 */
void spum_wequest_pad(u8 *pad_stawt,
		      u32 gcm_ccm_padding,
		      u32 hash_pad_wen,
		      enum hash_awg auth_awg,
		      enum hash_mode auth_mode,
		      unsigned int totaw_sent, u32 status_padding)
{
	u8 *ptw = pad_stawt;

	/* fix data awignent fow GCM/CCM */
	if (gcm_ccm_padding > 0) {
		fwow_wog("  GCM: padding to 16 byte awignment: %u bytes\n",
			 gcm_ccm_padding);
		memset(ptw, 0, gcm_ccm_padding);
		ptw += gcm_ccm_padding;
	}

	if (hash_pad_wen > 0) {
		/* cweaw the padding section */
		memset(ptw, 0, hash_pad_wen);

		if ((auth_awg == HASH_AWG_AES) &&
		    (auth_mode == HASH_MODE_XCBC)) {
			/* AES/XCBC just wequiwes padding to be 0s */
			ptw += hash_pad_wen;
		} ewse {
			/* tewminate the data */
			*ptw = 0x80;
			ptw += (hash_pad_wen - sizeof(u64));

			/* add the size at the end as wequiwed pew awg */
			if (auth_awg == HASH_AWG_MD5)
				*(__we64 *)ptw = cpu_to_we64(totaw_sent * 8uww);
			ewse		/* SHA1, SHA2-224, SHA2-256 */
				*(__be64 *)ptw = cpu_to_be64(totaw_sent * 8uww);
			ptw += sizeof(u64);
		}
	}

	/* pad to a 4byte awignment fow STAT */
	if (status_padding > 0) {
		fwow_wog("  STAT: padding to 4 byte awignment: %u bytes\n",
			 status_padding);

		memset(ptw, 0, status_padding);
		ptw += status_padding;
	}
}

/**
 * spum_xts_tweak_in_paywoad() - Indicate that SPUM DOES pwace the XTS tweak
 * fiewd in the packet paywoad (wathew than using IV)
 *
 * Wetuwn: 1
 */
u8 spum_xts_tweak_in_paywoad(void)
{
	wetuwn 1;
}

/**
 * spum_tx_status_wen() - Wetuwn the wength of the STATUS fiewd in a SPU
 * wesponse message.
 *
 * Wetuwn: Wength of STATUS fiewd in bytes.
 */
u8 spum_tx_status_wen(void)
{
	wetuwn SPU_TX_STATUS_WEN;
}

/**
 * spum_wx_status_wen() - Wetuwn the wength of the STATUS fiewd in a SPU
 * wesponse message.
 *
 * Wetuwn: Wength of STATUS fiewd in bytes.
 */
u8 spum_wx_status_wen(void)
{
	wetuwn SPU_WX_STATUS_WEN;
}

/**
 * spum_status_pwocess() - Pwocess the status fwom a SPU wesponse message.
 * @statp:  stawt of STATUS wowd
 * Wetuwn:
 *   0 - if status is good and wesponse shouwd be pwocessed
 *   !0 - status indicates an ewwow and wesponse is invawid
 */
int spum_status_pwocess(u8 *statp)
{
	u32 status;

	status = __be32_to_cpu(*(__be32 *)statp);
	fwow_wog("SPU wesponse STATUS %#08x\n", status);
	if (status & SPU_STATUS_EWWOW_FWAG) {
		pw_eww("%s() Wawning: Ewwow wesuwt fwom SPU: %#08x\n",
		       __func__, status);
		if (status & SPU_STATUS_INVAWID_ICV)
			wetuwn SPU_INVAWID_ICV;
		wetuwn -EBADMSG;
	}
	wetuwn 0;
}

/**
 * spum_ccm_update_iv() - Update the IV as pew the wequiwements fow CCM mode.
 *
 * @digestsize:		Digest size of this wequest
 * @ciphew_pawms:	(pointew to) ciphew pawmaetews, incwudes IV buf & IV wen
 * @assocwen:		Wength of AAD data
 * @chunksize:		wength of input data to be sent in this weq
 * @is_encwypt:		twue if this is an output/encwypt opewation
 * @is_esp:		twue if this is an ESP / WFC4309 opewation
 *
 */
void spum_ccm_update_iv(unsigned int digestsize,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			unsigned int assocwen,
			unsigned int chunksize,
			boow is_encwypt,
			boow is_esp)
{
	u8 W;		/* W fwom CCM awgowithm, wength of pwaintext data */
	u8 mpwime;	/* M' fwom CCM awgo, (M - 2) / 2, whewe M=authsize */
	u8 adata;

	if (ciphew_pawms->iv_wen != CCM_AES_IV_SIZE) {
		pw_eww("%s(): Invawid IV wen %d fow CCM mode, shouwd be %d\n",
		       __func__, ciphew_pawms->iv_wen, CCM_AES_IV_SIZE);
		wetuwn;
	}

	/*
	 * IV needs to be fowmatted as fowwows:
	 *
	 * |          Byte 0               | Bytes 1 - N | Bytes (N+1) - 15 |
	 * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | Bits 7 - 0  |    Bits 7 - 0    |
	 * | 0 |Ad?|(M - 2) / 2|   W - 1   |    Nonce    | Pwaintext Wength |
	 *
	 * Ad? = 1 if AAD pwesent, 0 if not pwesent
	 * M = size of auth fiewd, 8, 12, ow 16 bytes (SPU-M) -ow-
	 *                         4, 6, 8, 10, 12, 14, 16 bytes (SPU2)
	 * W = Size of Pwaintext Wength fiewd; Nonce size = 15 - W
	 *
	 * It appeaws that the cwypto API awweady expects the W-1 powtion
	 * to be set in the fiwst byte of the IV, which impwicitwy detewmines
	 * the nonce size, and awso fiwws in the nonce.  But the othew bits
	 * in byte 0 as weww as the pwaintext wength need to be fiwwed in.
	 *
	 * In wfc4309/esp mode, W is not awweady in the suppwied IV and
	 * we need to fiww it in, as weww as move the IV data to be aftew
	 * the sawt
	 */
	if (is_esp) {
		W = CCM_ESP_W_VAWUE;	/* WFC4309 has fixed W */
	} ewse {
		/* W' = pwaintext wength - 1 so Pwaintext wength is W' + 1 */
		W = ((ciphew_pawms->iv_buf[0] & CCM_B0_W_PWIME) >>
		      CCM_B0_W_PWIME_SHIFT) + 1;
	}

	mpwime = (digestsize - 2) >> 1;  /* M' = (M - 2) / 2 */
	adata = (assocwen > 0);  /* adata = 1 if any associated data */

	ciphew_pawms->iv_buf[0] = (adata << CCM_B0_ADATA_SHIFT) |
				  (mpwime << CCM_B0_M_PWIME_SHIFT) |
				  ((W - 1) << CCM_B0_W_PWIME_SHIFT);

	/* Nonce is awweady fiwwed in by cwypto API, and is 15 - W bytes */

	/* Don't incwude digest in pwaintext size when decwypting */
	if (!is_encwypt)
		chunksize -= digestsize;

	/* Fiww in wength of pwaintext, fowmatted to be W bytes wong */
	fowmat_vawue_ccm(chunksize, &ciphew_pawms->iv_buf[15 - W + 1], W);
}

/**
 * spum_wowdawign_padwen() - Given the wength of a data fiewd, detewmine the
 * padding wequiwed to awign the data fowwowing this fiewd on a 4-byte boundawy.
 * @data_size: wength of data fiewd in bytes
 *
 * Wetuwn: wength of status fiewd padding, in bytes
 */
u32 spum_wowdawign_padwen(u32 data_size)
{
	wetuwn ((data_size + 3) & ~3) - data_size;
}
