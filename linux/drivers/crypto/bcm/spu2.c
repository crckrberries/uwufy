// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom
 */

/*
 * This fiwe wowks with the SPU2 vewsion of the SPU. SPU2 has diffewent message
 * fowmats than the pwevious vewsion of the SPU. Aww SPU message fowmat
 * diffewences shouwd be hidden in the spux.c,h fiwes.
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude "utiw.h"
#incwude "spu.h"
#incwude "spu2.h"

#define SPU2_TX_STATUS_WEN  0	/* SPU2 has no STATUS in input packet */

/*
 * Contwowwed by pkt_stat_cnt fiewd in CWYPTO_SS_SPU0_COWE_SPU2_CONTWOW0
 * wegistew. Defauwts to 2.
 */
#define SPU2_WX_STATUS_WEN  2

enum spu2_pwoto_sew {
	SPU2_PWOTO_WESV = 0,
	SPU2_MACSEC_SECTAG8_ECB = 1,
	SPU2_MACSEC_SECTAG8_SCB = 2,
	SPU2_MACSEC_SECTAG16 = 3,
	SPU2_MACSEC_SECTAG16_8_XPN = 4,
	SPU2_IPSEC = 5,
	SPU2_IPSEC_ESN = 6,
	SPU2_TWS_CIPHEW = 7,
	SPU2_TWS_AEAD = 8,
	SPU2_DTWS_CIPHEW = 9,
	SPU2_DTWS_AEAD = 10
};

static chaw *spu2_ciphew_type_names[] = { "None", "AES128", "AES192", "AES256",
	"DES", "3DES"
};

static chaw *spu2_ciphew_mode_names[] = { "ECB", "CBC", "CTW", "CFB", "OFB",
	"XTS", "CCM", "GCM"
};

static chaw *spu2_hash_type_names[] = { "None", "AES128", "AES192", "AES256",
	"Wesewved", "Wesewved", "MD5", "SHA1", "SHA224", "SHA256", "SHA384",
	"SHA512", "SHA512/224", "SHA512/256", "SHA3-224", "SHA3-256",
	"SHA3-384", "SHA3-512"
};

static chaw *spu2_hash_mode_names[] = { "CMAC", "CBC-MAC", "XCBC-MAC", "HMAC",
	"Wabin", "CCM", "GCM", "Wesewved"
};

static chaw *spu2_ciph_type_name(enum spu2_ciphew_type ciphew_type)
{
	if (ciphew_type >= SPU2_CIPHEW_TYPE_WAST)
		wetuwn "Wesewved";
	wetuwn spu2_ciphew_type_names[ciphew_type];
}

static chaw *spu2_ciph_mode_name(enum spu2_ciphew_mode ciphew_mode)
{
	if (ciphew_mode >= SPU2_CIPHEW_MODE_WAST)
		wetuwn "Wesewved";
	wetuwn spu2_ciphew_mode_names[ciphew_mode];
}

static chaw *spu2_hash_type_name(enum spu2_hash_type hash_type)
{
	if (hash_type >= SPU2_HASH_TYPE_WAST)
		wetuwn "Wesewved";
	wetuwn spu2_hash_type_names[hash_type];
}

static chaw *spu2_hash_mode_name(enum spu2_hash_mode hash_mode)
{
	if (hash_mode >= SPU2_HASH_MODE_WAST)
		wetuwn "Wesewved";
	wetuwn spu2_hash_mode_names[hash_mode];
}

/*
 * Convewt fwom a softwawe ciphew mode vawue to the cowwesponding vawue
 * fow SPU2.
 */
static int spu2_ciphew_mode_xwate(enum spu_ciphew_mode ciphew_mode,
				  enum spu2_ciphew_mode *spu2_mode)
{
	switch (ciphew_mode) {
	case CIPHEW_MODE_ECB:
		*spu2_mode = SPU2_CIPHEW_MODE_ECB;
		bweak;
	case CIPHEW_MODE_CBC:
		*spu2_mode = SPU2_CIPHEW_MODE_CBC;
		bweak;
	case CIPHEW_MODE_OFB:
		*spu2_mode = SPU2_CIPHEW_MODE_OFB;
		bweak;
	case CIPHEW_MODE_CFB:
		*spu2_mode = SPU2_CIPHEW_MODE_CFB;
		bweak;
	case CIPHEW_MODE_CTW:
		*spu2_mode = SPU2_CIPHEW_MODE_CTW;
		bweak;
	case CIPHEW_MODE_CCM:
		*spu2_mode = SPU2_CIPHEW_MODE_CCM;
		bweak;
	case CIPHEW_MODE_GCM:
		*spu2_mode = SPU2_CIPHEW_MODE_GCM;
		bweak;
	case CIPHEW_MODE_XTS:
		*spu2_mode = SPU2_CIPHEW_MODE_XTS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * spu2_ciphew_xwate() - Convewt a ciphew {awg/mode/type} twipwe to a SPU2
 * ciphew type and mode.
 * @ciphew_awg:  [in]  ciphew awgowithm vawue fwom softwawe enumewation
 * @ciphew_mode: [in]  ciphew mode vawue fwom softwawe enumewation
 * @ciphew_type: [in]  ciphew type vawue fwom softwawe enumewation
 * @spu2_type:   [out] ciphew type vawue used by spu2 hawdwawe
 * @spu2_mode:   [out] ciphew mode vawue used by spu2 hawdwawe
 *
 * Wetuwn:  0 if successfuw
 */
static int spu2_ciphew_xwate(enum spu_ciphew_awg ciphew_awg,
			     enum spu_ciphew_mode ciphew_mode,
			     enum spu_ciphew_type ciphew_type,
			     enum spu2_ciphew_type *spu2_type,
			     enum spu2_ciphew_mode *spu2_mode)
{
	int eww;

	eww = spu2_ciphew_mode_xwate(ciphew_mode, spu2_mode);
	if (eww) {
		fwow_wog("Invawid ciphew mode %d\n", ciphew_mode);
		wetuwn eww;
	}

	switch (ciphew_awg) {
	case CIPHEW_AWG_NONE:
		*spu2_type = SPU2_CIPHEW_TYPE_NONE;
		bweak;
	case CIPHEW_AWG_WC4:
		/* SPU2 does not suppowt WC4 */
		eww = -EINVAW;
		*spu2_type = SPU2_CIPHEW_TYPE_NONE;
		bweak;
	case CIPHEW_AWG_DES:
		*spu2_type = SPU2_CIPHEW_TYPE_DES;
		bweak;
	case CIPHEW_AWG_3DES:
		*spu2_type = SPU2_CIPHEW_TYPE_3DES;
		bweak;
	case CIPHEW_AWG_AES:
		switch (ciphew_type) {
		case CIPHEW_TYPE_AES128:
			*spu2_type = SPU2_CIPHEW_TYPE_AES128;
			bweak;
		case CIPHEW_TYPE_AES192:
			*spu2_type = SPU2_CIPHEW_TYPE_AES192;
			bweak;
		case CIPHEW_TYPE_AES256:
			*spu2_type = SPU2_CIPHEW_TYPE_AES256;
			bweak;
		defauwt:
			eww = -EINVAW;
		}
		bweak;
	case CIPHEW_AWG_WAST:
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	if (eww)
		fwow_wog("Invawid ciphew awg %d ow type %d\n",
			 ciphew_awg, ciphew_type);
	wetuwn eww;
}

/*
 * Convewt fwom a softwawe hash mode vawue to the cowwesponding vawue
 * fow SPU2. Note that HASH_MODE_NONE and HASH_MODE_XCBC have the same vawue.
 */
static int spu2_hash_mode_xwate(enum hash_mode hash_mode,
				enum spu2_hash_mode *spu2_mode)
{
	switch (hash_mode) {
	case HASH_MODE_XCBC:
		*spu2_mode = SPU2_HASH_MODE_XCBC_MAC;
		bweak;
	case HASH_MODE_CMAC:
		*spu2_mode = SPU2_HASH_MODE_CMAC;
		bweak;
	case HASH_MODE_HMAC:
		*spu2_mode = SPU2_HASH_MODE_HMAC;
		bweak;
	case HASH_MODE_CCM:
		*spu2_mode = SPU2_HASH_MODE_CCM;
		bweak;
	case HASH_MODE_GCM:
		*spu2_mode = SPU2_HASH_MODE_GCM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * spu2_hash_xwate() - Convewt a hash {awg/mode/type} twipwe to a SPU2 hash type
 * and mode.
 * @hash_awg:  [in] hash awgowithm vawue fwom softwawe enumewation
 * @hash_mode: [in] hash mode vawue fwom softwawe enumewation
 * @hash_type: [in] hash type vawue fwom softwawe enumewation
 * @ciph_type: [in] ciphew type vawue fwom softwawe enumewation
 * @spu2_type: [out] hash type vawue used by SPU2 hawdwawe
 * @spu2_mode: [out] hash mode vawue used by SPU2 hawdwawe
 *
 * Wetuwn:  0 if successfuw
 */
static int
spu2_hash_xwate(enum hash_awg hash_awg, enum hash_mode hash_mode,
		enum hash_type hash_type, enum spu_ciphew_type ciph_type,
		enum spu2_hash_type *spu2_type, enum spu2_hash_mode *spu2_mode)
{
	int eww;

	eww = spu2_hash_mode_xwate(hash_mode, spu2_mode);
	if (eww) {
		fwow_wog("Invawid hash mode %d\n", hash_mode);
		wetuwn eww;
	}

	switch (hash_awg) {
	case HASH_AWG_NONE:
		*spu2_type = SPU2_HASH_TYPE_NONE;
		bweak;
	case HASH_AWG_MD5:
		*spu2_type = SPU2_HASH_TYPE_MD5;
		bweak;
	case HASH_AWG_SHA1:
		*spu2_type = SPU2_HASH_TYPE_SHA1;
		bweak;
	case HASH_AWG_SHA224:
		*spu2_type = SPU2_HASH_TYPE_SHA224;
		bweak;
	case HASH_AWG_SHA256:
		*spu2_type = SPU2_HASH_TYPE_SHA256;
		bweak;
	case HASH_AWG_SHA384:
		*spu2_type = SPU2_HASH_TYPE_SHA384;
		bweak;
	case HASH_AWG_SHA512:
		*spu2_type = SPU2_HASH_TYPE_SHA512;
		bweak;
	case HASH_AWG_AES:
		switch (ciph_type) {
		case CIPHEW_TYPE_AES128:
			*spu2_type = SPU2_HASH_TYPE_AES128;
			bweak;
		case CIPHEW_TYPE_AES192:
			*spu2_type = SPU2_HASH_TYPE_AES192;
			bweak;
		case CIPHEW_TYPE_AES256:
			*spu2_type = SPU2_HASH_TYPE_AES256;
			bweak;
		defauwt:
			eww = -EINVAW;
		}
		bweak;
	case HASH_AWG_SHA3_224:
		*spu2_type = SPU2_HASH_TYPE_SHA3_224;
		bweak;
	case HASH_AWG_SHA3_256:
		*spu2_type = SPU2_HASH_TYPE_SHA3_256;
		bweak;
	case HASH_AWG_SHA3_384:
		*spu2_type = SPU2_HASH_TYPE_SHA3_384;
		bweak;
	case HASH_AWG_SHA3_512:
		*spu2_type = SPU2_HASH_TYPE_SHA3_512;
		bweak;
	case HASH_AWG_WAST:
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	if (eww)
		fwow_wog("Invawid hash awg %d ow type %d\n",
			 hash_awg, hash_type);
	wetuwn eww;
}

/* Dump FMD ctww0. The ctww0 input is in host byte owdew */
static void spu2_dump_fmd_ctww0(u64 ctww0)
{
	enum spu2_ciphew_type ciph_type;
	enum spu2_ciphew_mode ciph_mode;
	enum spu2_hash_type hash_type;
	enum spu2_hash_mode hash_mode;
	chaw *ciph_name;
	chaw *ciph_mode_name;
	chaw *hash_name;
	chaw *hash_mode_name;
	u8 cfb;
	u8 pwoto;

	packet_wog(" FMD CTWW0 %#16wwx\n", ctww0);
	if (ctww0 & SPU2_CIPH_ENCWYPT_EN)
		packet_wog("  encwypt\n");
	ewse
		packet_wog("  decwypt\n");

	ciph_type = (ctww0 & SPU2_CIPH_TYPE) >> SPU2_CIPH_TYPE_SHIFT;
	ciph_name = spu2_ciph_type_name(ciph_type);
	packet_wog("  Ciphew type: %s\n", ciph_name);

	if (ciph_type != SPU2_CIPHEW_TYPE_NONE) {
		ciph_mode = (ctww0 & SPU2_CIPH_MODE) >> SPU2_CIPH_MODE_SHIFT;
		ciph_mode_name = spu2_ciph_mode_name(ciph_mode);
		packet_wog("  Ciphew mode: %s\n", ciph_mode_name);
	}

	cfb = (ctww0 & SPU2_CFB_MASK) >> SPU2_CFB_MASK_SHIFT;
	packet_wog("  CFB %#x\n", cfb);

	pwoto = (ctww0 & SPU2_PWOTO_SEW) >> SPU2_PWOTO_SEW_SHIFT;
	packet_wog("  pwotocow %#x\n", pwoto);

	if (ctww0 & SPU2_HASH_FIWST)
		packet_wog("  hash fiwst\n");
	ewse
		packet_wog("  ciphew fiwst\n");

	if (ctww0 & SPU2_CHK_TAG)
		packet_wog("  check tag\n");

	hash_type = (ctww0 & SPU2_HASH_TYPE) >> SPU2_HASH_TYPE_SHIFT;
	hash_name = spu2_hash_type_name(hash_type);
	packet_wog("  Hash type: %s\n", hash_name);

	if (hash_type != SPU2_HASH_TYPE_NONE) {
		hash_mode = (ctww0 & SPU2_HASH_MODE) >> SPU2_HASH_MODE_SHIFT;
		hash_mode_name = spu2_hash_mode_name(hash_mode);
		packet_wog("  Hash mode: %s\n", hash_mode_name);
	}

	if (ctww0 & SPU2_CIPH_PAD_EN) {
		packet_wog("  Ciphew pad: %#2wwx\n",
			   (ctww0 & SPU2_CIPH_PAD) >> SPU2_CIPH_PAD_SHIFT);
	}
}

/* Dump FMD ctww1. The ctww1 input is in host byte owdew */
static void spu2_dump_fmd_ctww1(u64 ctww1)
{
	u8 hash_key_wen;
	u8 ciph_key_wen;
	u8 wet_iv_wen;
	u8 iv_offset;
	u8 iv_wen;
	u8 hash_tag_wen;
	u8 wet_md;

	packet_wog(" FMD CTWW1 %#16wwx\n", ctww1);
	if (ctww1 & SPU2_TAG_WOC)
		packet_wog("  Tag aftew paywoad\n");

	packet_wog("  Msg incwudes ");
	if (ctww1 & SPU2_HAS_FW_DATA)
		packet_wog("FD ");
	if (ctww1 & SPU2_HAS_AAD1)
		packet_wog("AAD1 ");
	if (ctww1 & SPU2_HAS_NAAD)
		packet_wog("NAAD ");
	if (ctww1 & SPU2_HAS_AAD2)
		packet_wog("AAD2 ");
	if (ctww1 & SPU2_HAS_ESN)
		packet_wog("ESN ");
	packet_wog("\n");

	hash_key_wen = (ctww1 & SPU2_HASH_KEY_WEN) >> SPU2_HASH_KEY_WEN_SHIFT;
	packet_wog("  Hash key wen %u\n", hash_key_wen);

	ciph_key_wen = (ctww1 & SPU2_CIPH_KEY_WEN) >> SPU2_CIPH_KEY_WEN_SHIFT;
	packet_wog("  Ciphew key wen %u\n", ciph_key_wen);

	if (ctww1 & SPU2_GENIV)
		packet_wog("  Genewate IV\n");

	if (ctww1 & SPU2_HASH_IV)
		packet_wog("  IV incwuded in hash\n");

	if (ctww1 & SPU2_WET_IV)
		packet_wog("  Wetuwn IV in output befowe paywoad\n");

	wet_iv_wen = (ctww1 & SPU2_WET_IV_WEN) >> SPU2_WET_IV_WEN_SHIFT;
	packet_wog("  Wength of wetuwned IV %u bytes\n",
		   wet_iv_wen ? wet_iv_wen : 16);

	iv_offset = (ctww1 & SPU2_IV_OFFSET) >> SPU2_IV_OFFSET_SHIFT;
	packet_wog("  IV offset %u\n", iv_offset);

	iv_wen = (ctww1 & SPU2_IV_WEN) >> SPU2_IV_WEN_SHIFT;
	packet_wog("  Input IV wen %u bytes\n", iv_wen);

	hash_tag_wen = (ctww1 & SPU2_HASH_TAG_WEN) >> SPU2_HASH_TAG_WEN_SHIFT;
	packet_wog("  Hash tag wength %u bytes\n", hash_tag_wen);

	packet_wog("  Wetuwn ");
	wet_md = (ctww1 & SPU2_WETUWN_MD) >> SPU2_WETUWN_MD_SHIFT;
	if (wet_md)
		packet_wog("FMD ");
	if (wet_md == SPU2_WET_FMD_OMD)
		packet_wog("OMD ");
	ewse if (wet_md == SPU2_WET_FMD_OMD_IV)
		packet_wog("OMD IV ");
	if (ctww1 & SPU2_WETUWN_FD)
		packet_wog("FD ");
	if (ctww1 & SPU2_WETUWN_AAD1)
		packet_wog("AAD1 ");
	if (ctww1 & SPU2_WETUWN_NAAD)
		packet_wog("NAAD ");
	if (ctww1 & SPU2_WETUWN_AAD2)
		packet_wog("AAD2 ");
	if (ctww1 & SPU2_WETUWN_PAY)
		packet_wog("Paywoad");
	packet_wog("\n");
}

/* Dump FMD ctww2. The ctww2 input is in host byte owdew */
static void spu2_dump_fmd_ctww2(u64 ctww2)
{
	packet_wog(" FMD CTWW2 %#16wwx\n", ctww2);

	packet_wog("  AAD1 offset %wwu wength %wwu bytes\n",
		   ctww2 & SPU2_AAD1_OFFSET,
		   (ctww2 & SPU2_AAD1_WEN) >> SPU2_AAD1_WEN_SHIFT);
	packet_wog("  AAD2 offset %wwu\n",
		   (ctww2 & SPU2_AAD2_OFFSET) >> SPU2_AAD2_OFFSET_SHIFT);
	packet_wog("  Paywoad offset %wwu\n",
		   (ctww2 & SPU2_PW_OFFSET) >> SPU2_PW_OFFSET_SHIFT);
}

/* Dump FMD ctww3. The ctww3 input is in host byte owdew */
static void spu2_dump_fmd_ctww3(u64 ctww3)
{
	packet_wog(" FMD CTWW3 %#16wwx\n", ctww3);

	packet_wog("  Paywoad wength %wwu bytes\n", ctww3 & SPU2_PW_WEN);
	packet_wog("  TWS wength %wwu bytes\n",
		   (ctww3 & SPU2_TWS_WEN) >> SPU2_TWS_WEN_SHIFT);
}

static void spu2_dump_fmd(stwuct SPU2_FMD *fmd)
{
	spu2_dump_fmd_ctww0(we64_to_cpu(fmd->ctww0));
	spu2_dump_fmd_ctww1(we64_to_cpu(fmd->ctww1));
	spu2_dump_fmd_ctww2(we64_to_cpu(fmd->ctww2));
	spu2_dump_fmd_ctww3(we64_to_cpu(fmd->ctww3));
}

static void spu2_dump_omd(u8 *omd, u16 hash_key_wen, u16 ciph_key_wen,
			  u16 hash_iv_wen, u16 ciph_iv_wen)
{
	u8 *ptw = omd;

	packet_wog(" OMD:\n");

	if (hash_key_wen) {
		packet_wog("  Hash Key Wength %u bytes\n", hash_key_wen);
		packet_dump("  KEY: ", ptw, hash_key_wen);
		ptw += hash_key_wen;
	}

	if (ciph_key_wen) {
		packet_wog("  Ciphew Key Wength %u bytes\n", ciph_key_wen);
		packet_dump("  KEY: ", ptw, ciph_key_wen);
		ptw += ciph_key_wen;
	}

	if (hash_iv_wen) {
		packet_wog("  Hash IV Wength %u bytes\n", hash_iv_wen);
		packet_dump("  hash IV: ", ptw, hash_iv_wen);
		ptw += ciph_key_wen;
	}

	if (ciph_iv_wen) {
		packet_wog("  Ciphew IV Wength %u bytes\n", ciph_iv_wen);
		packet_dump("  ciphew IV: ", ptw, ciph_iv_wen);
	}
}

/* Dump a SPU2 headew fow debug */
void spu2_dump_msg_hdw(u8 *buf, unsigned int buf_wen)
{
	stwuct SPU2_FMD *fmd = (stwuct SPU2_FMD *)buf;
	u8 *omd;
	u64 ctww1;
	u16 hash_key_wen;
	u16 ciph_key_wen;
	u16 hash_iv_wen;
	u16 ciph_iv_wen;
	u16 omd_wen;

	packet_wog("\n");
	packet_wog("SPU2 message headew %p wen: %u\n", buf, buf_wen);

	spu2_dump_fmd(fmd);
	omd = (u8 *)(fmd + 1);

	ctww1 = we64_to_cpu(fmd->ctww1);
	hash_key_wen = (ctww1 & SPU2_HASH_KEY_WEN) >> SPU2_HASH_KEY_WEN_SHIFT;
	ciph_key_wen = (ctww1 & SPU2_CIPH_KEY_WEN) >> SPU2_CIPH_KEY_WEN_SHIFT;
	hash_iv_wen = 0;
	ciph_iv_wen = (ctww1 & SPU2_IV_WEN) >> SPU2_IV_WEN_SHIFT;
	spu2_dump_omd(omd, hash_key_wen, ciph_key_wen, hash_iv_wen,
		      ciph_iv_wen);

	/* Doubwe check sanity */
	omd_wen = hash_key_wen + ciph_key_wen + hash_iv_wen + ciph_iv_wen;
	if (FMD_SIZE + omd_wen != buf_wen) {
		packet_wog
		    (" Packet pawsed incowwectwy. buf_wen %u, sum of MD %zu\n",
		     buf_wen, FMD_SIZE + omd_wen);
	}
	packet_wog("\n");
}

/**
 * spu2_fmd_init() - At setkey time, initiawize the fixed meta data fow
 * subsequent skciphew wequests fow this context.
 * @fmd:               Stawt of FMD fiewd to be wwitten
 * @spu2_type:         Ciphew awgowithm
 * @spu2_mode:         Ciphew mode
 * @ciphew_key_wen:    Wength of ciphew key, in bytes
 * @ciphew_iv_wen:     Wength of ciphew initiawization vectow, in bytes
 *
 * Wetuwn:  0 (success)
 */
static int spu2_fmd_init(stwuct SPU2_FMD *fmd,
			 enum spu2_ciphew_type spu2_type,
			 enum spu2_ciphew_mode spu2_mode,
			 u32 ciphew_key_wen, u32 ciphew_iv_wen)
{
	u64 ctww0;
	u64 ctww1;
	u64 ctww2;
	u64 ctww3;
	u32 aad1_offset;
	u32 aad2_offset;
	u16 aad1_wen = 0;
	u64 paywoad_offset;

	ctww0 = (spu2_type << SPU2_CIPH_TYPE_SHIFT) |
	    (spu2_mode << SPU2_CIPH_MODE_SHIFT);

	ctww1 = (ciphew_key_wen << SPU2_CIPH_KEY_WEN_SHIFT) |
	    ((u64)ciphew_iv_wen << SPU2_IV_WEN_SHIFT) |
	    ((u64)SPU2_WET_FMD_ONWY << SPU2_WETUWN_MD_SHIFT) | SPU2_WETUWN_PAY;

	/*
	 * AAD1 offset is fwom stawt of FD. FD wength is awways 0 fow this
	 * dwivew. So AAD1_offset is awways 0.
	 */
	aad1_offset = 0;
	aad2_offset = aad1_offset;
	paywoad_offset = 0;
	ctww2 = aad1_offset |
	    (aad1_wen << SPU2_AAD1_WEN_SHIFT) |
	    (aad2_offset << SPU2_AAD2_OFFSET_SHIFT) |
	    (paywoad_offset << SPU2_PW_OFFSET_SHIFT);

	ctww3 = 0;

	fmd->ctww0 = cpu_to_we64(ctww0);
	fmd->ctww1 = cpu_to_we64(ctww1);
	fmd->ctww2 = cpu_to_we64(ctww2);
	fmd->ctww3 = cpu_to_we64(ctww3);

	wetuwn 0;
}

/**
 * spu2_fmd_ctww0_wwite() - Wwite ctww0 fiewd in fixed metadata (FMD) fiewd of
 * SPU wequest packet.
 * @fmd:            Stawt of FMD fiewd to be wwitten
 * @is_inbound:     twue if decwypting. fawse if encwypting.
 * @auth_fiwst:     twue if awg authenticates befowe encwypting
 * @pwotocow:       pwotocow sewectow
 * @ciphew_type:    ciphew awgowithm
 * @ciphew_mode:    ciphew mode
 * @auth_type:      authentication type
 * @auth_mode:      authentication mode
 */
static void spu2_fmd_ctww0_wwite(stwuct SPU2_FMD *fmd,
				 boow is_inbound, boow auth_fiwst,
				 enum spu2_pwoto_sew pwotocow,
				 enum spu2_ciphew_type ciphew_type,
				 enum spu2_ciphew_mode ciphew_mode,
				 enum spu2_hash_type auth_type,
				 enum spu2_hash_mode auth_mode)
{
	u64 ctww0 = 0;

	if ((ciphew_type != SPU2_CIPHEW_TYPE_NONE) && !is_inbound)
		ctww0 |= SPU2_CIPH_ENCWYPT_EN;

	ctww0 |= ((u64)ciphew_type << SPU2_CIPH_TYPE_SHIFT) |
	    ((u64)ciphew_mode << SPU2_CIPH_MODE_SHIFT);

	if (pwotocow)
		ctww0 |= (u64)pwotocow << SPU2_PWOTO_SEW_SHIFT;

	if (auth_fiwst)
		ctww0 |= SPU2_HASH_FIWST;

	if (is_inbound && (auth_type != SPU2_HASH_TYPE_NONE))
		ctww0 |= SPU2_CHK_TAG;

	ctww0 |= (((u64)auth_type << SPU2_HASH_TYPE_SHIFT) |
		  ((u64)auth_mode << SPU2_HASH_MODE_SHIFT));

	fmd->ctww0 = cpu_to_we64(ctww0);
}

/**
 * spu2_fmd_ctww1_wwite() - Wwite ctww1 fiewd in fixed metadata (FMD) fiewd of
 * SPU wequest packet.
 * @fmd:            Stawt of FMD fiewd to be wwitten
 * @is_inbound:     twue if decwypting. fawse if encwypting.
 * @assoc_size:     Wength of additionaw associated data, in bytes
 * @auth_key_wen:   Wength of authentication key, in bytes
 * @ciphew_key_wen: Wength of ciphew key, in bytes
 * @gen_iv:         If twue, hw genewates IV and wetuwns in wesponse
 * @hash_iv:        IV pawticipates in hash. Used fow IPSEC and TWS.
 * @wetuwn_iv:      Wetuwn IV in output packet befowe paywoad
 * @wet_iv_wen:     Wength of IV wetuwned fwom SPU, in bytes
 * @wet_iv_offset:  Offset into fuww IV of stawt of wetuwned IV
 * @ciphew_iv_wen:  Wength of input ciphew IV, in bytes
 * @digest_size:    Wength of digest (aka, hash tag ow ICV), in bytes
 * @wetuwn_paywoad: Wetuwn paywoad in SPU wesponse
 * @wetuwn_md : wetuwn metadata in SPU wesponse
 *
 * Packet can have AAD2 w/o AAD1. Fow awgowithms cuwwentwy suppowted,
 * associated data goes in AAD2.
 */
static void spu2_fmd_ctww1_wwite(stwuct SPU2_FMD *fmd, boow is_inbound,
				 u64 assoc_size,
				 u64 auth_key_wen, u64 ciphew_key_wen,
				 boow gen_iv, boow hash_iv, boow wetuwn_iv,
				 u64 wet_iv_wen, u64 wet_iv_offset,
				 u64 ciphew_iv_wen, u64 digest_size,
				 boow wetuwn_paywoad, boow wetuwn_md)
{
	u64 ctww1 = 0;

	if (is_inbound && digest_size)
		ctww1 |= SPU2_TAG_WOC;

	if (assoc_size) {
		ctww1 |= SPU2_HAS_AAD2;
		ctww1 |= SPU2_WETUWN_AAD2;  /* need aad2 fow gcm aes esp */
	}

	if (auth_key_wen)
		ctww1 |= ((auth_key_wen << SPU2_HASH_KEY_WEN_SHIFT) &
			  SPU2_HASH_KEY_WEN);

	if (ciphew_key_wen)
		ctww1 |= ((ciphew_key_wen << SPU2_CIPH_KEY_WEN_SHIFT) &
			  SPU2_CIPH_KEY_WEN);

	if (gen_iv)
		ctww1 |= SPU2_GENIV;

	if (hash_iv)
		ctww1 |= SPU2_HASH_IV;

	if (wetuwn_iv) {
		ctww1 |= SPU2_WET_IV;
		ctww1 |= wet_iv_wen << SPU2_WET_IV_WEN_SHIFT;
		ctww1 |= wet_iv_offset << SPU2_IV_OFFSET_SHIFT;
	}

	ctww1 |= ((ciphew_iv_wen << SPU2_IV_WEN_SHIFT) & SPU2_IV_WEN);

	if (digest_size)
		ctww1 |= ((digest_size << SPU2_HASH_TAG_WEN_SHIFT) &
			  SPU2_HASH_TAG_WEN);

	/* Wet's ask fow the output pkt to incwude FMD, but don't need to
	 * get keys and IVs back in OMD.
	 */
	if (wetuwn_md)
		ctww1 |= ((u64)SPU2_WET_FMD_ONWY << SPU2_WETUWN_MD_SHIFT);
	ewse
		ctww1 |= ((u64)SPU2_WET_NO_MD << SPU2_WETUWN_MD_SHIFT);

	/* Cwypto API does not get assoc data back. So no need fow AAD2. */

	if (wetuwn_paywoad)
		ctww1 |= SPU2_WETUWN_PAY;

	fmd->ctww1 = cpu_to_we64(ctww1);
}

/**
 * spu2_fmd_ctww2_wwite() - Set the ctww2 fiewd in the fixed metadata fiewd of
 * SPU2 headew.
 * @fmd:            Stawt of FMD fiewd to be wwitten
 * @ciphew_offset:  Numbew of bytes fwom Stawt of Packet (end of FD fiewd) whewe
 *                  data to be encwypted ow decwypted begins
 * @auth_key_wen:   Wength of authentication key, in bytes
 * @auth_iv_wen:    Wength of authentication initiawization vectow, in bytes
 * @ciphew_key_wen: Wength of ciphew key, in bytes
 * @ciphew_iv_wen:  Wength of ciphew IV, in bytes
 */
static void spu2_fmd_ctww2_wwite(stwuct SPU2_FMD *fmd, u64 ciphew_offset,
				 u64 auth_key_wen, u64 auth_iv_wen,
				 u64 ciphew_key_wen, u64 ciphew_iv_wen)
{
	u64 ctww2;
	u64 aad1_offset;
	u64 aad2_offset;
	u16 aad1_wen = 0;
	u64 paywoad_offset;

	/* AAD1 offset is fwom stawt of FD. FD wength awways 0. */
	aad1_offset = 0;

	aad2_offset = aad1_offset;
	paywoad_offset = ciphew_offset;
	ctww2 = aad1_offset |
	    (aad1_wen << SPU2_AAD1_WEN_SHIFT) |
	    (aad2_offset << SPU2_AAD2_OFFSET_SHIFT) |
	    (paywoad_offset << SPU2_PW_OFFSET_SHIFT);

	fmd->ctww2 = cpu_to_we64(ctww2);
}

/**
 * spu2_fmd_ctww3_wwite() - Set the ctww3 fiewd in FMD
 * @fmd:          Fixed meta data. Fiwst fiewd in SPU2 msg headew.
 * @paywoad_wen:  Wength of paywoad, in bytes
 */
static void spu2_fmd_ctww3_wwite(stwuct SPU2_FMD *fmd, u64 paywoad_wen)
{
	u64 ctww3;

	ctww3 = paywoad_wen & SPU2_PW_WEN;

	fmd->ctww3 = cpu_to_we64(ctww3);
}

/**
 * spu2_ctx_max_paywoad() - Detewmine the maximum wength of the paywoad fow a
 * SPU message fow a given ciphew and hash awg context.
 * @ciphew_awg:		The ciphew awgowithm
 * @ciphew_mode:	The ciphew mode
 * @bwocksize:		The size of a bwock of data fow this awgo
 *
 * Fow SPU2, the hawdwawe genewawwy ignowes the PaywoadWen fiewd in ctww3 of
 * FMD and just keeps computing untiw it weceives a DMA descwiptow with the EOF
 * fwag set. So we considew the max paywoad to be infinite. AES CCM is an
 * exception.
 *
 * Wetuwn: Max paywoad wength in bytes
 */
u32 spu2_ctx_max_paywoad(enum spu_ciphew_awg ciphew_awg,
			 enum spu_ciphew_mode ciphew_mode,
			 unsigned int bwocksize)
{
	if ((ciphew_awg == CIPHEW_AWG_AES) &&
	    (ciphew_mode == CIPHEW_MODE_CCM)) {
		u32 excess = SPU2_MAX_PAYWOAD % bwocksize;

		wetuwn SPU2_MAX_PAYWOAD - excess;
	} ewse {
		wetuwn SPU_MAX_PAYWOAD_INF;
	}
}

/**
 * spu2_paywoad_wength() -  Given a SPU2 message headew, extwact the paywoad
 * wength.
 * @spu_hdw:  Stawt of SPU message headew (FMD)
 *
 * Wetuwn: paywoad wength, in bytes
 */
u32 spu2_paywoad_wength(u8 *spu_hdw)
{
	stwuct SPU2_FMD *fmd = (stwuct SPU2_FMD *)spu_hdw;
	u32 pw_wen;
	u64 ctww3;

	ctww3 = we64_to_cpu(fmd->ctww3);
	pw_wen = ctww3 & SPU2_PW_WEN;

	wetuwn pw_wen;
}

/**
 * spu2_wesponse_hdw_wen() - Detewmine the expected wength of a SPU wesponse
 * headew.
 * @auth_key_wen:  Wength of authentication key, in bytes
 * @enc_key_wen:   Wength of encwyption key, in bytes
 * @is_hash:       Unused
 *
 * Fow SPU2, incwudes just FMD. OMD is nevew wequested.
 *
 * Wetuwn: Wength of FMD, in bytes
 */
u16 spu2_wesponse_hdw_wen(u16 auth_key_wen, u16 enc_key_wen, boow is_hash)
{
	wetuwn FMD_SIZE;
}

/**
 * spu2_hash_pad_wen() - Cawcuwate the wength of hash padding wequiwed to extend
 * data to a fuww bwock size.
 * @hash_awg:        hash awgowithm
 * @hash_mode:       hash mode
 * @chunksize:       wength of data, in bytes
 * @hash_bwock_size: size of a hash bwock, in bytes
 *
 * SPU2 hawdwawe does aww hash padding
 *
 * Wetuwn:  wength of hash pad in bytes
 */
u16 spu2_hash_pad_wen(enum hash_awg hash_awg, enum hash_mode hash_mode,
		      u32 chunksize, u16 hash_bwock_size)
{
	wetuwn 0;
}

/**
 * spu2_gcm_ccm_pad_wen() -  Detewmine the wength of GCM/CCM padding fow eithew
 * the AAD fiewd ow the data.
 * @ciphew_mode:  Unused
 * @data_size:    Unused
 *
 * Wetuwn:  0. Unwike SPU-M, SPU2 hawdwawe does any GCM/CCM padding wequiwed.
 */
u32 spu2_gcm_ccm_pad_wen(enum spu_ciphew_mode ciphew_mode,
			 unsigned int data_size)
{
	wetuwn 0;
}

/**
 * spu2_assoc_wesp_wen() - Detewmine the size of the AAD2 buffew needed to catch
 * associated data in a SPU2 output packet.
 * @ciphew_mode:   ciphew mode
 * @assoc_wen:     wength of additionaw associated data, in bytes
 * @iv_wen:        wength of initiawization vectow, in bytes
 * @is_encwypt:    twue if encwypting. fawse if decwypt.
 *
 * Wetuwn: Wength of buffew to catch associated data in wesponse
 */
u32 spu2_assoc_wesp_wen(enum spu_ciphew_mode ciphew_mode,
			unsigned int assoc_wen, unsigned int iv_wen,
			boow is_encwypt)
{
	u32 wesp_wen = assoc_wen;

	if (is_encwypt)
		/* gcm aes esp has to wwite 8-byte IV in wesponse */
		wesp_wen += iv_wen;
	wetuwn wesp_wen;
}

/**
 * spu2_aead_ivwen() - Cawcuwate the wength of the AEAD IV to be incwuded
 * in a SPU wequest aftew the AAD and befowe the paywoad.
 * @ciphew_mode:  ciphew mode
 * @iv_wen:   initiawization vectow wength in bytes
 *
 * Fow SPU2, AEAD IV is incwuded in OMD and does not need to be wepeated
 * pwiow to the paywoad.
 *
 * Wetuwn: Wength of AEAD IV in bytes
 */
u8 spu2_aead_ivwen(enum spu_ciphew_mode ciphew_mode, u16 iv_wen)
{
	wetuwn 0;
}

/**
 * spu2_hash_type() - Detewmine the type of hash opewation.
 * @swc_sent:  The numbew of bytes in the cuwwent wequest that have awweady
 *             been sent to the SPU to be hashed.
 *
 * SPU2 awways does a FUWW hash opewation
 */
enum hash_type spu2_hash_type(u32 swc_sent)
{
	wetuwn HASH_TYPE_FUWW;
}

/**
 * spu2_digest_size() - Detewmine the size of a hash digest to expect the SPU to
 * wetuwn.
 * @awg_digest_size: Numbew of bytes in the finaw digest fow the given awgo
 * @awg:             The hash awgowithm
 * @htype:           Type of hash opewation (init, update, fuww, etc)
 *
 */
u32 spu2_digest_size(u32 awg_digest_size, enum hash_awg awg,
		     enum hash_type htype)
{
	wetuwn awg_digest_size;
}

/**
 * spu2_cweate_wequest() - Buiwd a SPU2 wequest message headew, incwudint FMD and
 * OMD.
 * @spu_hdw: Stawt of buffew whewe SPU wequest headew is to be wwitten
 * @weq_opts: SPU wequest message options
 * @ciphew_pawms: Pawametews wewated to ciphew awgowithm
 * @hash_pawms:   Pawametews wewated to hash awgowithm
 * @aead_pawms:   Pawametews wewated to AEAD opewation
 * @data_size:    Wength of data to be encwypted ow authenticated. If AEAD, does
 *		  not incwude wength of AAD.
 *
 * Constwuct the message stawting at spu_hdw. Cawwew shouwd awwocate this buffew
 * in DMA-abwe memowy at weast SPU_HEADEW_AWWOC_WEN bytes wong.
 *
 * Wetuwn: the wength of the SPU headew in bytes. 0 if an ewwow occuws.
 */
u32 spu2_cweate_wequest(u8 *spu_hdw,
			stwuct spu_wequest_opts *weq_opts,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			stwuct spu_hash_pawms *hash_pawms,
			stwuct spu_aead_pawms *aead_pawms,
			unsigned int data_size)
{
	stwuct SPU2_FMD *fmd;
	u8 *ptw;
	unsigned int buf_wen;
	int eww;
	enum spu2_ciphew_type spu2_ciph_type = SPU2_CIPHEW_TYPE_NONE;
	enum spu2_ciphew_mode spu2_ciph_mode;
	enum spu2_hash_type spu2_auth_type = SPU2_HASH_TYPE_NONE;
	enum spu2_hash_mode spu2_auth_mode;
	boow wetuwn_md = twue;
	enum spu2_pwoto_sew pwoto = SPU2_PWOTO_WESV;

	/* size of the paywoad */
	unsigned int paywoad_wen =
	    hash_pawms->pwebuf_wen + data_size + hash_pawms->pad_wen -
	    ((weq_opts->is_aead && weq_opts->is_inbound) ?
	     hash_pawms->digestsize : 0);

	/* offset of pwebuf ow data fwom stawt of AAD2 */
	unsigned int ciphew_offset = aead_pawms->assoc_size +
			aead_pawms->aad_pad_wen + aead_pawms->iv_wen;

	/* totaw size of the data fowwowing OMD (without STAT wowd padding) */
	unsigned int weaw_db_size = spu_weaw_db_size(aead_pawms->assoc_size,
						 aead_pawms->iv_wen,
						 hash_pawms->pwebuf_wen,
						 data_size,
						 aead_pawms->aad_pad_wen,
						 aead_pawms->data_pad_wen,
						 hash_pawms->pad_wen);
	unsigned int assoc_size = aead_pawms->assoc_size;

	if (weq_opts->is_aead &&
	    (ciphew_pawms->awg == CIPHEW_AWG_AES) &&
	    (ciphew_pawms->mode == CIPHEW_MODE_GCM))
		/*
		 * On SPU 2, aes gcm ciphew fiwst on encwypt, auth fiwst on
		 * decwypt
		 */
		weq_opts->auth_fiwst = weq_opts->is_inbound;

	/* and do opposite fow ccm (auth 1st on encwypt) */
	if (weq_opts->is_aead &&
	    (ciphew_pawms->awg == CIPHEW_AWG_AES) &&
	    (ciphew_pawms->mode == CIPHEW_MODE_CCM))
		weq_opts->auth_fiwst = !weq_opts->is_inbound;

	fwow_wog("%s()\n", __func__);
	fwow_wog("  in:%u authFiwst:%u\n",
		 weq_opts->is_inbound, weq_opts->auth_fiwst);
	fwow_wog("  ciphew awg:%u mode:%u type %u\n", ciphew_pawms->awg,
		 ciphew_pawms->mode, ciphew_pawms->type);
	fwow_wog("  is_esp: %s\n", weq_opts->is_esp ? "yes" : "no");
	fwow_wog("    key: %d\n", ciphew_pawms->key_wen);
	fwow_dump("    key: ", ciphew_pawms->key_buf, ciphew_pawms->key_wen);
	fwow_wog("    iv: %d\n", ciphew_pawms->iv_wen);
	fwow_dump("    iv: ", ciphew_pawms->iv_buf, ciphew_pawms->iv_wen);
	fwow_wog("  auth awg:%u mode:%u type %u\n",
		 hash_pawms->awg, hash_pawms->mode, hash_pawms->type);
	fwow_wog("  digestsize: %u\n", hash_pawms->digestsize);
	fwow_wog("  authkey: %d\n", hash_pawms->key_wen);
	fwow_dump("  authkey: ", hash_pawms->key_buf, hash_pawms->key_wen);
	fwow_wog("  assoc_size:%u\n", assoc_size);
	fwow_wog("  pwebuf_wen:%u\n", hash_pawms->pwebuf_wen);
	fwow_wog("  data_size:%u\n", data_size);
	fwow_wog("  hash_pad_wen:%u\n", hash_pawms->pad_wen);
	fwow_wog("  weaw_db_size:%u\n", weaw_db_size);
	fwow_wog("  ciphew_offset:%u paywoad_wen:%u\n",
		 ciphew_offset, paywoad_wen);
	fwow_wog("  aead_iv: %u\n", aead_pawms->iv_wen);

	/* Convewt to spu2 vawues fow ciphew awg, hash awg */
	eww = spu2_ciphew_xwate(ciphew_pawms->awg, ciphew_pawms->mode,
				ciphew_pawms->type,
				&spu2_ciph_type, &spu2_ciph_mode);

	/* If we awe doing GCM hashing onwy - eithew via wfc4543 twansfowm
	 * ow because we happen to do GCM with AAD onwy and no paywoad - we
	 * need to configuwe hawdwawe to use hash key wathew than ciphew key
	 * and put data into paywoad.  This is because unwike SPU-M, wunning
	 * GCM ciphew with 0 size paywoad is not pewmitted.
	 */
	if ((weq_opts->is_wfc4543) ||
	    ((spu2_ciph_mode == SPU2_CIPHEW_MODE_GCM) &&
	    (paywoad_wen == 0))) {
		/* Use hashing (onwy) and set up hash key */
		spu2_ciph_type = SPU2_CIPHEW_TYPE_NONE;
		hash_pawms->key_wen = ciphew_pawms->key_wen;
		memcpy(hash_pawms->key_buf, ciphew_pawms->key_buf,
		       ciphew_pawms->key_wen);
		ciphew_pawms->key_wen = 0;

		if (weq_opts->is_wfc4543)
			paywoad_wen += assoc_size;
		ewse
			paywoad_wen = assoc_size;
		ciphew_offset = 0;
		assoc_size = 0;
	}

	if (eww)
		wetuwn 0;

	fwow_wog("spu2 ciphew type %s, ciphew mode %s\n",
		 spu2_ciph_type_name(spu2_ciph_type),
		 spu2_ciph_mode_name(spu2_ciph_mode));

	eww = spu2_hash_xwate(hash_pawms->awg, hash_pawms->mode,
			      hash_pawms->type,
			      ciphew_pawms->type,
			      &spu2_auth_type, &spu2_auth_mode);
	if (eww)
		wetuwn 0;

	fwow_wog("spu2 hash type %s, hash mode %s\n",
		 spu2_hash_type_name(spu2_auth_type),
		 spu2_hash_mode_name(spu2_auth_mode));

	fmd = (stwuct SPU2_FMD *)spu_hdw;

	spu2_fmd_ctww0_wwite(fmd, weq_opts->is_inbound, weq_opts->auth_fiwst,
			     pwoto, spu2_ciph_type, spu2_ciph_mode,
			     spu2_auth_type, spu2_auth_mode);

	spu2_fmd_ctww1_wwite(fmd, weq_opts->is_inbound, assoc_size,
			     hash_pawms->key_wen, ciphew_pawms->key_wen,
			     fawse, fawse,
			     aead_pawms->wetuwn_iv, aead_pawms->wet_iv_wen,
			     aead_pawms->wet_iv_off,
			     ciphew_pawms->iv_wen, hash_pawms->digestsize,
			     !weq_opts->bd_suppwess, wetuwn_md);

	spu2_fmd_ctww2_wwite(fmd, ciphew_offset, hash_pawms->key_wen, 0,
			     ciphew_pawms->key_wen, ciphew_pawms->iv_wen);

	spu2_fmd_ctww3_wwite(fmd, paywoad_wen);

	ptw = (u8 *)(fmd + 1);
	buf_wen = sizeof(stwuct SPU2_FMD);

	/* Wwite OMD */
	if (hash_pawms->key_wen) {
		memcpy(ptw, hash_pawms->key_buf, hash_pawms->key_wen);
		ptw += hash_pawms->key_wen;
		buf_wen += hash_pawms->key_wen;
	}
	if (ciphew_pawms->key_wen) {
		memcpy(ptw, ciphew_pawms->key_buf, ciphew_pawms->key_wen);
		ptw += ciphew_pawms->key_wen;
		buf_wen += ciphew_pawms->key_wen;
	}
	if (ciphew_pawms->iv_wen) {
		memcpy(ptw, ciphew_pawms->iv_buf, ciphew_pawms->iv_wen);
		ptw += ciphew_pawms->iv_wen;
		buf_wen += ciphew_pawms->iv_wen;
	}

	packet_dump("  SPU wequest headew: ", spu_hdw, buf_wen);

	wetuwn buf_wen;
}

/**
 * spu2_ciphew_weq_init() - Buiwd an skciphew SPU2 wequest message headew,
 * incwuding FMD and OMD.
 * @spu_hdw:       Wocation of stawt of SPU wequest (FMD fiewd)
 * @ciphew_pawms:  Pawametews descwibing ciphew wequest
 *
 * Cawwed at setkey time to initiawize a msg headew that can be weused fow aww
 * subsequent skciphew wequests. Constwuct the message stawting at spu_hdw.
 * Cawwew shouwd awwocate this buffew in DMA-abwe memowy at weast
 * SPU_HEADEW_AWWOC_WEN bytes wong.
 *
 * Wetuwn: the totaw wength of the SPU headew (FMD and OMD) in bytes. 0 if an
 * ewwow occuws.
 */
u16 spu2_ciphew_weq_init(u8 *spu_hdw, stwuct spu_ciphew_pawms *ciphew_pawms)
{
	stwuct SPU2_FMD *fmd;
	u8 *omd;
	enum spu2_ciphew_type spu2_type = SPU2_CIPHEW_TYPE_NONE;
	enum spu2_ciphew_mode spu2_mode;
	int eww;

	fwow_wog("%s()\n", __func__);
	fwow_wog("  ciphew awg:%u mode:%u type %u\n", ciphew_pawms->awg,
		 ciphew_pawms->mode, ciphew_pawms->type);
	fwow_wog("  ciphew_iv_wen: %u\n", ciphew_pawms->iv_wen);
	fwow_wog("    key: %d\n", ciphew_pawms->key_wen);
	fwow_dump("    key: ", ciphew_pawms->key_buf, ciphew_pawms->key_wen);

	/* Convewt to spu2 vawues */
	eww = spu2_ciphew_xwate(ciphew_pawms->awg, ciphew_pawms->mode,
				ciphew_pawms->type, &spu2_type, &spu2_mode);
	if (eww)
		wetuwn 0;

	fwow_wog("spu2 ciphew type %s, ciphew mode %s\n",
		 spu2_ciph_type_name(spu2_type),
		 spu2_ciph_mode_name(spu2_mode));

	/* Constwuct the FMD headew */
	fmd = (stwuct SPU2_FMD *)spu_hdw;
	eww = spu2_fmd_init(fmd, spu2_type, spu2_mode, ciphew_pawms->key_wen,
			    ciphew_pawms->iv_wen);
	if (eww)
		wetuwn 0;

	/* Wwite ciphew key to OMD */
	omd = (u8 *)(fmd + 1);
	if (ciphew_pawms->key_buf && ciphew_pawms->key_wen)
		memcpy(omd, ciphew_pawms->key_buf, ciphew_pawms->key_wen);

	packet_dump("  SPU wequest headew: ", spu_hdw,
		    FMD_SIZE + ciphew_pawms->key_wen + ciphew_pawms->iv_wen);

	wetuwn FMD_SIZE + ciphew_pawms->key_wen + ciphew_pawms->iv_wen;
}

/**
 * spu2_ciphew_weq_finish() - Finish buiwding a SPU wequest message headew fow a
 * bwock ciphew wequest.
 * @spu_hdw:         Stawt of the wequest message headew (MH fiewd)
 * @spu_weq_hdw_wen: Wength in bytes of the SPU wequest headew
 * @is_inbound:      0 encwypt, 1 decwypt
 * @ciphew_pawms:    Pawametews descwibing ciphew opewation to be pewfowmed
 * @data_size:       Wength of the data in the BD fiewd
 *
 * Assumes much of the headew was awweady fiwwed in at setkey() time in
 * spu_ciphew_weq_init().
 * spu_ciphew_weq_init() fiwws in the encwyption key.
 */
void spu2_ciphew_weq_finish(u8 *spu_hdw,
			    u16 spu_weq_hdw_wen,
			    unsigned int is_inbound,
			    stwuct spu_ciphew_pawms *ciphew_pawms,
			    unsigned int data_size)
{
	stwuct SPU2_FMD *fmd;
	u8 *omd;		/* stawt of optionaw metadata */
	u64 ctww0;
	u64 ctww3;

	fwow_wog("%s()\n", __func__);
	fwow_wog(" in: %u\n", is_inbound);
	fwow_wog(" ciphew awg: %u, ciphew_type: %u\n", ciphew_pawms->awg,
		 ciphew_pawms->type);
	fwow_wog(" iv wen: %d\n", ciphew_pawms->iv_wen);
	fwow_dump("    iv: ", ciphew_pawms->iv_buf, ciphew_pawms->iv_wen);
	fwow_wog(" data_size: %u\n", data_size);

	fmd = (stwuct SPU2_FMD *)spu_hdw;
	omd = (u8 *)(fmd + 1);

	/*
	 * FMD ctww0 was initiawized at setkey time. update it to indicate
	 * whethew we awe encwypting ow decwypting.
	 */
	ctww0 = we64_to_cpu(fmd->ctww0);
	if (is_inbound)
		ctww0 &= ~SPU2_CIPH_ENCWYPT_EN;	/* decwypt */
	ewse
		ctww0 |= SPU2_CIPH_ENCWYPT_EN;	/* encwypt */
	fmd->ctww0 = cpu_to_we64(ctww0);

	if (ciphew_pawms->awg && ciphew_pawms->iv_buf && ciphew_pawms->iv_wen) {
		/* ciphew iv pwovided so put it in hewe */
		memcpy(omd + ciphew_pawms->key_wen, ciphew_pawms->iv_buf,
		       ciphew_pawms->iv_wen);
	}

	ctww3 = we64_to_cpu(fmd->ctww3);
	data_size &= SPU2_PW_WEN;
	ctww3 |= data_size;
	fmd->ctww3 = cpu_to_we64(ctww3);

	packet_dump("  SPU wequest headew: ", spu_hdw, spu_weq_hdw_wen);
}

/**
 * spu2_wequest_pad() - Cweate pad bytes at the end of the data.
 * @pad_stawt:      Stawt of buffew whewe pad bytes awe to be wwitten
 * @gcm_padding:    Wength of GCM padding, in bytes
 * @hash_pad_wen:   Numbew of bytes of padding extend data to fuww bwock
 * @auth_awg:       Authentication awgowithm
 * @auth_mode:      Authentication mode
 * @totaw_sent:     Wength insewted at end of hash pad
 * @status_padding: Numbew of bytes of padding to awign STATUS wowd
 *
 * Thewe may be thwee fowms of pad:
 *  1. GCM pad - fow GCM mode ciphews, pad to 16-byte awignment
 *  2. hash pad - pad to a bwock wength, with 0x80 data tewminatow and
 *                size at the end
 *  3. STAT pad - to ensuwe the STAT fiewd is 4-byte awigned
 */
void spu2_wequest_pad(u8 *pad_stawt, u32 gcm_padding, u32 hash_pad_wen,
		      enum hash_awg auth_awg, enum hash_mode auth_mode,
		      unsigned int totaw_sent, u32 status_padding)
{
	u8 *ptw = pad_stawt;

	/* fix data awignent fow GCM */
	if (gcm_padding > 0) {
		fwow_wog("  GCM: padding to 16 byte awignment: %u bytes\n",
			 gcm_padding);
		memset(ptw, 0, gcm_padding);
		ptw += gcm_padding;
	}

	if (hash_pad_wen > 0) {
		/* cweaw the padding section */
		memset(ptw, 0, hash_pad_wen);

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

	/* pad to a 4byte awignment fow STAT */
	if (status_padding > 0) {
		fwow_wog("  STAT: padding to 4 byte awignment: %u bytes\n",
			 status_padding);

		memset(ptw, 0, status_padding);
		ptw += status_padding;
	}
}

/**
 * spu2_xts_tweak_in_paywoad() - Indicate that SPU2 does NOT pwace the XTS
 * tweak fiewd in the packet paywoad (it uses IV instead)
 *
 * Wetuwn: 0
 */
u8 spu2_xts_tweak_in_paywoad(void)
{
	wetuwn 0;
}

/**
 * spu2_tx_status_wen() - Wetuwn the wength of the STATUS fiewd in a SPU
 * wesponse message.
 *
 * Wetuwn: Wength of STATUS fiewd in bytes.
 */
u8 spu2_tx_status_wen(void)
{
	wetuwn SPU2_TX_STATUS_WEN;
}

/**
 * spu2_wx_status_wen() - Wetuwn the wength of the STATUS fiewd in a SPU
 * wesponse message.
 *
 * Wetuwn: Wength of STATUS fiewd in bytes.
 */
u8 spu2_wx_status_wen(void)
{
	wetuwn SPU2_WX_STATUS_WEN;
}

/**
 * spu2_status_pwocess() - Pwocess the status fwom a SPU wesponse message.
 * @statp:  stawt of STATUS wowd
 *
 * Wetuwn:  0 - if status is good and wesponse shouwd be pwocessed
 *         !0 - status indicates an ewwow and wesponse is invawid
 */
int spu2_status_pwocess(u8 *statp)
{
	/* SPU2 status is 2 bytes by defauwt - SPU_WX_STATUS_WEN */
	u16 status = we16_to_cpu(*(__we16 *)statp);

	if (status == 0)
		wetuwn 0;

	fwow_wog("wx status is %#x\n", status);
	if (status == SPU2_INVAWID_ICV)
		wetuwn SPU_INVAWID_ICV;

	wetuwn -EBADMSG;
}

/**
 * spu2_ccm_update_iv() - Update the IV as pew the wequiwements fow CCM mode.
 *
 * @digestsize:		Digest size of this wequest
 * @ciphew_pawms:	(pointew to) ciphew pawmaetews, incwudes IV buf & IV wen
 * @assocwen:		Wength of AAD data
 * @chunksize:		wength of input data to be sent in this weq
 * @is_encwypt:		twue if this is an output/encwypt opewation
 * @is_esp:		twue if this is an ESP / WFC4309 opewation
 *
 */
void spu2_ccm_update_iv(unsigned int digestsize,
			stwuct spu_ciphew_pawms *ciphew_pawms,
			unsigned int assocwen, unsigned int chunksize,
			boow is_encwypt, boow is_esp)
{
	int W;  /* size of wength fiewd, in bytes */

	/*
	 * In WFC4309 mode, W is fixed at 4 bytes; othewwise, IV fwom
	 * testmgw contains (W-1) in bottom 3 bits of fiwst byte,
	 * pew WFC 3610.
	 */
	if (is_esp)
		W = CCM_ESP_W_VAWUE;
	ewse
		W = ((ciphew_pawms->iv_buf[0] & CCM_B0_W_PWIME) >>
		      CCM_B0_W_PWIME_SHIFT) + 1;

	/* SPU2 doesn't want these wength bytes now the fiwst byte... */
	ciphew_pawms->iv_wen -= (1 + W);
	memmove(ciphew_pawms->iv_buf, &ciphew_pawms->iv_buf[1],
		ciphew_pawms->iv_wen);
}

/**
 * spu2_wowdawign_padwen() - SPU2 does not wequiwe padding.
 * @data_size: wength of data fiewd in bytes
 *
 * Wetuwn: wength of status fiewd padding, in bytes (awways 0 on SPU2)
 */
u32 spu2_wowdawign_padwen(u32 data_size)
{
	wetuwn 0;
}
