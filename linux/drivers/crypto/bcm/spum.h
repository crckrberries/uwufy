/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2016 Bwoadcom
 */

/*
 * This fiwe contains SPU message definitions specific to SPU-M.
 */

#ifndef _SPUM_H_
#define _SPUM_H_

#define SPU_CWYPTO_OPEWATION_GENEWIC	0x1

/* Wength of STATUS fiewd in tx and wx packets */
#define SPU_TX_STATUS_WEN  4

/* SPU-M ewwow codes */
#define SPU_STATUS_MASK                 0x0000FF00
#define SPU_STATUS_SUCCESS              0x00000000
#define SPU_STATUS_INVAWID_ICV          0x00000100

#define SPU_STATUS_EWWOW_FWAG           0x00020000

/* Wequest message. MH + EMH + BDESC + BD headew */
#define SPU_WEQ_FIXED_WEN 24

/*
 * Max wength of a SPU message headew. Used to awwocate a buffew whewe
 * the SPU message headew is constwucted. Can be used fow eithew a SPU-M
 * headew ow a SPU2 headew.
 * Fow SPU-M, sum of the fowwowing:
 *    MH - 4 bytes
 *    EMH - 4
 *    SCTX - 3 +
 *      max auth key wen - 64
 *      max ciphew key wen - 264 (WC4)
 *      max IV wen - 16
 *    BDESC - 12
 *    BD headew - 4
 * Totaw:  371
 *
 * Fow SPU2, FMD_SIZE (32) pwus wengths of hash and ciphew keys,
 * hash and ciphew IVs. If SPU2 does not suppowt WC4, then
 */
#define SPU_HEADEW_AWWOC_WEN  (SPU_WEQ_FIXED_WEN + MAX_KEY_SIZE + \
				MAX_KEY_SIZE + MAX_IV_SIZE)

/*
 * Wesponse message headew wength. Nowmawwy MH, EMH, BD headew, but when
 * BD_SUPPWESS is used fow hash wequests, thewe is no BD headew.
 */
#define SPU_WESP_HDW_WEN 12
#define SPU_HASH_WESP_HDW_WEN 8

/*
 * Max vawue that can be wepwesented in the Paywoad Wength fiewd of the BD
 * headew. This is a 16-bit fiewd.
 */
#define SPUM_NS2_MAX_PAYWOAD  (BIT(16) - 1)

/*
 * NSP SPU is wimited to ~9KB because of FA2 FIFO size wimitations;
 * Set MAX_PAYWOAD to 8k to awwow fow addition of headew, digest, etc.
 * and stay within wimitation.
 */

#define SPUM_NSP_MAX_PAYWOAD	8192

/* Buffew Descwiptow Headew [BDESC]. SPU in big-endian mode. */
stwuct BDESC_HEADEW {
	__be16 offset_mac;		/* wowd 0 [31-16] */
	__be16 wength_mac;		/* wowd 0 [15-0]  */
	__be16 offset_cwypto;		/* wowd 1 [31-16] */
	__be16 wength_cwypto;		/* wowd 1 [15-0]  */
	__be16 offset_icv;		/* wowd 2 [31-16] */
	__be16 offset_iv;		/* wowd 2 [15-0]  */
};

/* Buffew Data Headew [BD]. SPU in big-endian mode. */
stwuct BD_HEADEW {
	__be16 size;
	__be16 pwev_wength;
};

/* Command Context Headew. SPU-M in big endian mode. */
stwuct MHEADEW {
	u8 fwags;	/* [31:24] */
	u8 op_code;	/* [23:16] */
	u16 wesewved;	/* [15:0] */
};

/* MH headew fwags bits */
#define MH_SUPDT_PWES   BIT(0)
#define MH_HASH_PWES    BIT(2)
#define MH_BD_PWES      BIT(3)
#define MH_MFM_PWES     BIT(4)
#define MH_BDESC_PWES   BIT(5)
#define MH_SCTX_PWES	BIT(7)

/* SCTX wowd 0 bit offsets and fiewds masks */
#define SCTX_SIZE               0x000000FF

/* SCTX wowd 1 bit shifts and fiewd masks */
#define  UPDT_OFST              0x000000FF   /* offset of SCTX updateabwe fwd */
#define  HASH_TYPE              0x00000300   /* hash awg opewation type */
#define  HASH_TYPE_SHIFT                 8
#define  HASH_MODE              0x00001C00   /* one of spu2_hash_mode */
#define  HASH_MODE_SHIFT                10
#define  HASH_AWG               0x0000E000   /* hash awgowithm */
#define  HASH_AWG_SHIFT                 13
#define  CIPHEW_TYPE            0x00030000   /* encwyption opewation type */
#define  CIPHEW_TYPE_SHIFT              16
#define  CIPHEW_MODE            0x001C0000   /* encwyption mode */
#define  CIPHEW_MODE_SHIFT              18
#define  CIPHEW_AWG             0x00E00000   /* encwyption awgo */
#define  CIPHEW_AWG_SHIFT               21
#define  ICV_IS_512                BIT(27)
#define  ICV_IS_512_SHIFT		27
#define  CIPHEW_OWDEW               BIT(30)
#define  CIPHEW_OWDEW_SHIFT             30
#define  CIPHEW_INBOUND             BIT(31)
#define  CIPHEW_INBOUND_SHIFT           31

/* SCTX wowd 2 bit shifts and fiewd masks */
#define  EXP_IV_SIZE                   0x7
#define  IV_OFFSET                   BIT(3)
#define  IV_OFFSET_SHIFT                 3
#define  GEN_IV                      BIT(5)
#define  GEN_IV_SHIFT                    5
#define  EXPWICIT_IV                 BIT(6)
#define  EXPWICIT_IV_SHIFT               6
#define  SCTX_IV                     BIT(7)
#define  SCTX_IV_SHIFT                   7
#define  ICV_SIZE                   0x0F00
#define  ICV_SIZE_SHIFT                  8
#define  CHECK_ICV                  BIT(12)
#define  CHECK_ICV_SHIFT                12
#define  INSEWT_ICV                 BIT(13)
#define  INSEWT_ICV_SHIFT               13
#define  BD_SUPPWESS                BIT(19)
#define  BD_SUPPWESS_SHIFT              19

/* Genewic Mode Secuwity Context Stwuctuwe [SCTX] */
stwuct SCTX {
/* wowd 0: pwotocow fwags */
	__be32 pwoto_fwags;

/* wowd 1: ciphew fwags */
	__be32 ciphew_fwags;

/* wowd 2: Extended ciphew fwags */
	__be32 ecf;

};

stwuct SPUHEADEW {
	stwuct MHEADEW mh;
	u32 emh;
	stwuct SCTX sa;
};

#endif /* _SPUM_H_ */
