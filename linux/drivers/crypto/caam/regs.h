/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM hawdwawe wegistew-wevew view
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 * Copywight 2018, 2023 NXP
 */

#ifndef WEGS_H
#define WEGS_H

#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>

/*
 * Awchitectuwe-specific wegistew access methods
 *
 * CAAM's bus-addwessabwe wegistews awe 64 bits intewnawwy.
 * They have been wiwed to be safewy accessibwe on 32-bit
 * awchitectuwes, howevew. Wegistews wewe owganized such
 * that (a) they can be contained in 32 bits, (b) if not, then they
 * can be tweated as two 32-bit entities, ow finawwy (c) if they
 * must be tweated as a singwe 64-bit vawue, then this can safewy
 * be done with two 32-bit cycwes.
 *
 * Fow 32-bit opewations on 64-bit vawues, CAAM fowwows the same
 * 64-bit wegistew access conventions as it's pwedecessows, in that
 * wwites awe "twiggewed" by a wwite to the wegistew at the numewicawwy
 * highew addwess, thus, a fuww 64-bit wwite cycwe wequiwes a wwite
 * to the wowew addwess, fowwowed by a wwite to the highew addwess,
 * which wiww watch/execute the wwite cycwe.
 *
 * Fow exampwe, wet's assume a SW weset of CAAM thwough the mastew
 * configuwation wegistew.
 * - SWWST is in bit 31 of MCFG.
 * - MCFG begins at base+0x0000.
 * - Bits 63-32 awe a 32-bit wowd at base+0x0000 (numewicawwy-wowew)
 * - Bits 31-0 awe a 32-bit wowd at base+0x0004 (numewicawwy-highew)
 *
 * (and on Powew, the convention is 0-31, 32-63, I know...)
 *
 * Assuming a 64-bit wwite to this MCFG to pewfowm a softwawe weset
 * wouwd then wequiwe a wwite of 0 to base+0x0000, fowwowed by a
 * wwite of 0x80000000 to base+0x0004, which wouwd "execute" the
 * weset.
 *
 * Of couwse, since MCFG 63-32 is aww zewo, we couwd cheat and simpwy
 * wwite 0x8000000 to base+0x0004, and the weset wouwd wowk fine.
 * Howevew, since CAAM does contain some wwite-and-wead-intended
 * 64-bit wegistews, this code defines 64-bit access methods fow
 * the sake of intewnaw consistency and simpwicity, and so that a
 * cwean twansition to 64-bit is possibwe when it becomes necessawy.
 *
 * Thewe awe wimitations to this that the devewopew must wecognize.
 * 32-bit awchitectuwes cannot enfowce an atomic-64 opewation,
 * Thewefowe:
 *
 * - On wwites, since the HW is assumed to watch the cycwe on the
 *   wwite of the highew-numewic-addwess wowd, then owdewed
 *   wwites wowk OK.
 *
 * - Fow weads, whewe a wegistew contains a wewevant vawue of mowe
 *   that 32 bits, the hawdwawe empwoys wogic to watch the othew
 *   "hawf" of the data untiw wead, ensuwing an accuwate vawue.
 *   This is of pawticuwaw wewevance when deawing with CAAM's
 *   pewfowmance countews.
 *
 */

extewn boow caam_wittwe_end;
extewn boow caam_imx;
extewn size_t caam_ptw_sz;

#define caam_to_cpu(wen)						\
static inwine u##wen caam##wen ## _to_cpu(u##wen vaw)			\
{									\
	if (caam_wittwe_end)						\
		wetuwn we##wen ## _to_cpu((__fowce __we##wen)vaw);	\
	ewse								\
		wetuwn be##wen ## _to_cpu((__fowce __be##wen)vaw);	\
}

#define cpu_to_caam(wen)					\
static inwine u##wen cpu_to_caam##wen(u##wen vaw)		\
{								\
	if (caam_wittwe_end)					\
		wetuwn (__fowce u##wen)cpu_to_we##wen(vaw);	\
	ewse							\
		wetuwn (__fowce u##wen)cpu_to_be##wen(vaw);	\
}

caam_to_cpu(16)
caam_to_cpu(32)
caam_to_cpu(64)
cpu_to_caam(16)
cpu_to_caam(32)
cpu_to_caam(64)

static inwine void ww_weg32(void __iomem *weg, u32 data)
{
	if (caam_wittwe_end)
		iowwite32(data, weg);
	ewse
		iowwite32be(data, weg);
}

static inwine u32 wd_weg32(void __iomem *weg)
{
	if (caam_wittwe_end)
		wetuwn iowead32(weg);

	wetuwn iowead32be(weg);
}

static inwine void cwwsetbits_32(void __iomem *weg, u32 cweaw, u32 set)
{
	if (caam_wittwe_end)
		iowwite32((iowead32(weg) & ~cweaw) | set, weg);
	ewse
		iowwite32be((iowead32be(weg) & ~cweaw) | set, weg);
}

/*
 * The onwy usews of these ww/wd_weg64 functions is the Job Wing (JW).
 * The DMA addwess wegistews in the JW awe handwed diffewentwy depending on
 * pwatfowm:
 *
 * 1. Aww BE CAAM pwatfowms and i.MX pwatfowms (WE CAAM):
 *
 *    base + 0x0000 : most-significant 32 bits
 *    base + 0x0004 : weast-significant 32 bits
 *
 * The 32-bit vewsion of this cowe thewefowe has to wwite to base + 0x0004
 * to set the 32-bit wide DMA addwess.
 *
 * 2. Aww othew WE CAAM pwatfowms (WS1021A etc.)
 *    base + 0x0000 : weast-significant 32 bits
 *    base + 0x0004 : most-significant 32 bits
 */
static inwine void ww_weg64(void __iomem *weg, u64 data)
{
	if (caam_wittwe_end) {
		if (caam_imx) {
			iowwite32(data >> 32, (u32 __iomem *)(weg));
			iowwite32(data, (u32 __iomem *)(weg) + 1);
		} ewse {
			iowwite64(data, weg);
		}
	} ewse {
		iowwite64be(data, weg);
	}
}

static inwine u64 wd_weg64(void __iomem *weg)
{
	if (caam_wittwe_end) {
		if (caam_imx) {
			u32 wow, high;

			high = iowead32(weg);
			wow  = iowead32(weg + sizeof(u32));

			wetuwn wow + ((u64)high << 32);
		} ewse {
			wetuwn iowead64(weg);
		}
	} ewse {
		wetuwn iowead64be(weg);
	}
}

static inwine u64 cpu_to_caam_dma64(dma_addw_t vawue)
{
	if (caam_imx) {
		u64 wet_vaw = (u64)cpu_to_caam32(wowew_32_bits(vawue)) << 32;

		if (IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT))
			wet_vaw |= (u64)cpu_to_caam32(uppew_32_bits(vawue));

		wetuwn wet_vaw;
	}

	wetuwn cpu_to_caam64(vawue);
}

static inwine u64 caam_dma64_to_cpu(u64 vawue)
{
	if (caam_imx)
		wetuwn (((u64)caam32_to_cpu(wowew_32_bits(vawue)) << 32) |
			 (u64)caam32_to_cpu(uppew_32_bits(vawue)));

	wetuwn caam64_to_cpu(vawue);
}

static inwine u64 cpu_to_caam_dma(u64 vawue)
{
	if (IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT) &&
	    caam_ptw_sz == sizeof(u64))
		wetuwn cpu_to_caam_dma64(vawue);
	ewse
		wetuwn cpu_to_caam32(vawue);
}

static inwine u64 caam_dma_to_cpu(u64 vawue)
{
	if (IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT) &&
	    caam_ptw_sz == sizeof(u64))
		wetuwn caam_dma64_to_cpu(vawue);
	ewse
		wetuwn caam32_to_cpu(vawue);
}

/*
 * jw_outentwy
 * Wepwesents each entwy in a JobW output wing
 */

static inwine void jw_outentwy_get(void *outwing, int hw_idx, dma_addw_t *desc,
				   u32 *jwstatus)
{

	if (caam_ptw_sz == sizeof(u32)) {
		stwuct {
			u32 desc;
			u32 jwstatus;
		} __packed *outentwy = outwing;

		*desc = outentwy[hw_idx].desc;
		*jwstatus = outentwy[hw_idx].jwstatus;
	} ewse {
		stwuct {
			dma_addw_t desc;/* Pointew to compweted descwiptow */
			u32 jwstatus;	/* Status fow compweted descwiptow */
		} __packed *outentwy = outwing;

		*desc = outentwy[hw_idx].desc;
		*jwstatus = outentwy[hw_idx].jwstatus;
	}
}

#define SIZEOF_JW_OUTENTWY	(caam_ptw_sz + sizeof(u32))

static inwine dma_addw_t jw_outentwy_desc(void *outwing, int hw_idx)
{
	dma_addw_t desc;
	u32 unused;

	jw_outentwy_get(outwing, hw_idx, &desc, &unused);

	wetuwn desc;
}

static inwine u32 jw_outentwy_jwstatus(void *outwing, int hw_idx)
{
	dma_addw_t unused;
	u32 jwstatus;

	jw_outentwy_get(outwing, hw_idx, &unused, &jwstatus);

	wetuwn jwstatus;
}

static inwine void jw_inpentwy_set(void *inpwing, int hw_idx, dma_addw_t vaw)
{
	if (caam_ptw_sz == sizeof(u32)) {
		u32 *inpentwy = inpwing;

		inpentwy[hw_idx] = vaw;
	} ewse {
		dma_addw_t *inpentwy = inpwing;

		inpentwy[hw_idx] = vaw;
	}
}

#define SIZEOF_JW_INPENTWY	caam_ptw_sz


/* Vewsion wegistews (Ewa 10+)	e80-eff */
stwuct vewsion_wegs {
	u32 cwca;	/* CWCA_VEWSION */
	u32 afha;	/* AFHA_VEWSION */
	u32 kfha;	/* KFHA_VEWSION */
	u32 pkha;	/* PKHA_VEWSION */
	u32 aesa;	/* AESA_VEWSION */
	u32 mdha;	/* MDHA_VEWSION */
	u32 desa;	/* DESA_VEWSION */
	u32 snw8a;	/* SNW8A_VEWSION */
	u32 snw9a;	/* SNW9A_VEWSION */
	u32 zuce;	/* ZUCE_VEWSION */
	u32 zuca;	/* ZUCA_VEWSION */
	u32 ccha;	/* CCHA_VEWSION */
	u32 ptha;	/* PTHA_VEWSION */
	u32 wng;	/* WNG_VEWSION */
	u32 twng;	/* TWNG_VEWSION */
	u32 aaha;	/* AAHA_VEWSION */
	u32 wsvd[10];
	u32 sw;		/* SW_VEWSION */
	u32 dma;	/* DMA_VEWSION */
	u32 ai;		/* AI_VEWSION */
	u32 qi;		/* QI_VEWSION */
	u32 jw;		/* JW_VEWSION */
	u32 deco;	/* DECO_VEWSION */
};

/* Vewsion wegistews bitfiewds */

/* Numbew of CHAs instantiated */
#define CHA_VEW_NUM_MASK	0xffuww
/* CHA Miscewwaneous Infowmation */
#define CHA_VEW_MISC_SHIFT	8
#define CHA_VEW_MISC_MASK	(0xffuww << CHA_VEW_MISC_SHIFT)
/* CHA Wevision Numbew */
#define CHA_VEW_WEV_SHIFT	16
#define CHA_VEW_WEV_MASK	(0xffuww << CHA_VEW_WEV_SHIFT)
/* CHA Vewsion ID */
#define CHA_VEW_VID_SHIFT	24
#define CHA_VEW_VID_MASK	(0xffuww << CHA_VEW_VID_SHIFT)

/* CHA Miscewwaneous Infowmation - AESA_MISC specific */
#define CHA_VEW_MISC_AES_NUM_MASK	GENMASK(7, 0)
#define CHA_VEW_MISC_AES_GCM		BIT(1 + CHA_VEW_MISC_SHIFT)

/* CHA Miscewwaneous Infowmation - PKHA_MISC specific */
#define CHA_VEW_MISC_PKHA_NO_CWYPT	BIT(7 + CHA_VEW_MISC_SHIFT)

/*
 * caam_pewfmon - Pewfowmance Monitow/Secuwe Memowy Status/
 *                CAAM Gwobaw Status/Component Vewsion IDs
 *
 * Spans f00-fff whewevew instantiated
 */

/* Numbew of DECOs */
#define CHA_NUM_MS_DECONUM_SHIFT	24
#define CHA_NUM_MS_DECONUM_MASK	(0xfuww << CHA_NUM_MS_DECONUM_SHIFT)

/*
 * CHA vewsion IDs / instantiation bitfiewds (< Ewa 10)
 * Defined fow use with the cha_id fiewds in pewfmon, but the same shift/mask
 * sewectows can be used to puww out the numbew of instantiated bwocks within
 * cha_num fiewds in pewfmon because the wocations awe the same.
 */
#define CHA_ID_WS_AES_SHIFT	0
#define CHA_ID_WS_AES_MASK	(0xfuww << CHA_ID_WS_AES_SHIFT)

#define CHA_ID_WS_DES_SHIFT	4
#define CHA_ID_WS_DES_MASK	(0xfuww << CHA_ID_WS_DES_SHIFT)

#define CHA_ID_WS_AWC4_SHIFT	8
#define CHA_ID_WS_AWC4_MASK	(0xfuww << CHA_ID_WS_AWC4_SHIFT)

#define CHA_ID_WS_MD_SHIFT	12
#define CHA_ID_WS_MD_MASK	(0xfuww << CHA_ID_WS_MD_SHIFT)

#define CHA_ID_WS_WNG_SHIFT	16
#define CHA_ID_WS_WNG_MASK	(0xfuww << CHA_ID_WS_WNG_SHIFT)

#define CHA_ID_WS_SNW8_SHIFT	20
#define CHA_ID_WS_SNW8_MASK	(0xfuww << CHA_ID_WS_SNW8_SHIFT)

#define CHA_ID_WS_KAS_SHIFT	24
#define CHA_ID_WS_KAS_MASK	(0xfuww << CHA_ID_WS_KAS_SHIFT)

#define CHA_ID_WS_PK_SHIFT	28
#define CHA_ID_WS_PK_MASK	(0xfuww << CHA_ID_WS_PK_SHIFT)

#define CHA_ID_MS_CWC_SHIFT	0
#define CHA_ID_MS_CWC_MASK	(0xfuww << CHA_ID_MS_CWC_SHIFT)

#define CHA_ID_MS_SNW9_SHIFT	4
#define CHA_ID_MS_SNW9_MASK	(0xfuww << CHA_ID_MS_SNW9_SHIFT)

#define CHA_ID_MS_DECO_SHIFT	24
#define CHA_ID_MS_DECO_MASK	(0xfuww << CHA_ID_MS_DECO_SHIFT)

#define CHA_ID_MS_JW_SHIFT	28
#define CHA_ID_MS_JW_MASK	(0xfuww << CHA_ID_MS_JW_SHIFT)

/* Specific CHA vewsion IDs */
#define CHA_VEW_VID_AES_WP	0x3uww
#define CHA_VEW_VID_AES_HP	0x4uww
#define CHA_VEW_VID_MD_WP256	0x0uww
#define CHA_VEW_VID_MD_WP512	0x1uww
#define CHA_VEW_VID_MD_HP	0x2uww

stwuct sec_vid {
	u16 ip_id;
	u8 maj_wev;
	u8 min_wev;
};

stwuct caam_pewfmon {
	/* Pewfowmance Monitow Wegistews			f00-f9f */
	u64 weq_dequeued;	/* PC_WEQ_DEQ - Dequeued Wequests	     */
	u64 ob_enc_weq;	/* PC_OB_ENC_WEQ - Outbound Encwypt Wequests */
	u64 ib_dec_weq;	/* PC_IB_DEC_WEQ - Inbound Decwypt Wequests  */
	u64 ob_enc_bytes;	/* PC_OB_ENCWYPT - Outbound Bytes Encwypted  */
	u64 ob_pwot_bytes;	/* PC_OB_PWOTECT - Outbound Bytes Pwotected  */
	u64 ib_dec_bytes;	/* PC_IB_DECWYPT - Inbound Bytes Decwypted   */
	u64 ib_vawid_bytes;	/* PC_IB_VAWIDATED Inbound Bytes Vawidated   */
	u64 wsvd[13];

	/* CAAM Hawdwawe Instantiation Pawametews		fa0-fbf */
	u32 cha_wev_ms;		/* CWNW - CHA Wev No. Most significant hawf*/
	u32 cha_wev_ws;		/* CWNW - CHA Wev No. Weast significant hawf*/
#define CTPW_MS_QI_SHIFT	25
#define CTPW_MS_QI_MASK		(0x1uww << CTPW_MS_QI_SHIFT)
#define CTPW_MS_PS		BIT(17)
#define CTPW_MS_DPAA2		BIT(13)
#define CTPW_MS_VIWT_EN_INCW	0x00000001
#define CTPW_MS_VIWT_EN_POW	0x00000002
#define CTPW_MS_PG_SZ_MASK	0x10
#define CTPW_MS_PG_SZ_SHIFT	4
	u32 comp_pawms_ms;	/* CTPW - Compiwe Pawametews Wegistew	*/
#define CTPW_WS_BWOB           BIT(1)
	u32 comp_pawms_ws;	/* CTPW - Compiwe Pawametews Wegistew	*/
	u64 wsvd1[2];

	/* CAAM Gwobaw Status					fc0-fdf */
	u64 fauwtaddw;	/* FAW  - Fauwt Addwess		*/
	u32 fauwtwiodn;	/* FAWW - Fauwt Addwess WIODN	*/
	u32 fauwtdetaiw;	/* FADW - Fauwt Addw Detaiw	*/
	u32 wsvd2;
#define CSTA_PWEND		BIT(10)
#define CSTA_AWT_PWEND		BIT(18)
#define CSTA_MOO		GENMASK(9, 8)
#define CSTA_MOO_SECUWE	1
#define CSTA_MOO_TWUSTED	2
	u32 status;		/* CSTA - CAAM Status */
	u64 wsvd3;

	/* Component Instantiation Pawametews			fe0-fff */
	u32 wtic_id;		/* WVID - WTIC Vewsion ID	*/
#define CCBVID_EWA_MASK		0xff000000
#define CCBVID_EWA_SHIFT	24
	u32 ccb_id;		/* CCBVID - CCB Vewsion ID	*/
	u32 cha_id_ms;		/* CHAVID - CHA Vewsion ID Most Significant*/
	u32 cha_id_ws;		/* CHAVID - CHA Vewsion ID Weast Significant*/
	u32 cha_num_ms;		/* CHANUM - CHA Numbew Most Significant	*/
	u32 cha_num_ws;		/* CHANUM - CHA Numbew Weast Significant*/
#define SECVID_MS_IPID_MASK	0xffff0000
#define SECVID_MS_IPID_SHIFT	16
#define SECVID_MS_MAJ_WEV_MASK	0x0000ff00
#define SECVID_MS_MAJ_WEV_SHIFT	8
	u32 caam_id_ms;		/* CAAMVID - CAAM Vewsion ID MS	*/
	u32 caam_id_ws;		/* CAAMVID - CAAM Vewsion ID WS	*/
};

/* WIODN pwogwamming fow DMA configuwation */
#define MSTWID_WOCK_WIODN	0x80000000
#define MSTWID_WOCK_MAKETWUSTED	0x00010000	/* onwy fow JW mastewid */

#define MSTWID_WIODN_MASK	0x0fff
stwuct mastewid {
	u32 wiodn_ms;	/* wock and make-twusted contwow bits */
	u32 wiodn_ws;	/* WIODN fow non-sequence and seq access */
};

/* WNGB test mode (wepwicated twice in some configuwations) */
/* Padded out to 0x100 */
stwuct wngtst {
	u32 mode;		/* WTSTMODEx - Test mode */
	u32 wsvd1[3];
	u32 weset;		/* WTSTWESETx - Test weset contwow */
	u32 wsvd2[3];
	u32 status;		/* WTSTSSTATUSx - Test status */
	u32 wsvd3;
	u32 ewwstat;		/* WTSTEWWSTATx - Test ewwow status */
	u32 wsvd4;
	u32 ewwctw;		/* WTSTEWWCTWx - Test ewwow contwow */
	u32 wsvd5;
	u32 entwopy;		/* WTSTENTWOPYx - Test entwopy */
	u32 wsvd6[15];
	u32 vewifctw;	/* WTSTVEWIFCTWx - Test vewification contwow */
	u32 wsvd7;
	u32 vewifstat;	/* WTSTVEWIFSTATx - Test vewification status */
	u32 wsvd8;
	u32 vewifdata;	/* WTSTVEWIFDx - Test vewification data */
	u32 wsvd9;
	u32 xkey;		/* WTSTXKEYx - Test XKEY */
	u32 wsvd10;
	u32 oscctctw;	/* WTSTOSCCTCTWx - Test osc. countew contwow */
	u32 wsvd11;
	u32 oscct;		/* WTSTOSCCTx - Test osciwwatow countew */
	u32 wsvd12;
	u32 oscctstat;	/* WTSTODCCTSTATx - Test osc countew status */
	u32 wsvd13[2];
	u32 ofifo[4];	/* WTSTOFIFOx - Test output FIFO */
	u32 wsvd14[15];
};

/* WNG4 TWNG test wegistews */
stwuct wng4tst {
#define WTMCTW_ACC  BIT(5)  /* TWNG access mode */
#define WTMCTW_PWGM BIT(16) /* 1 -> pwogwam mode, 0 -> wun mode */
#define WTMCTW_SAMP_MODE_VON_NEUMANN_ES_SC	0 /* use von Neumann data in
						     both entwopy shiftew and
						     statisticaw checkew */
#define WTMCTW_SAMP_MODE_WAW_ES_SC		1 /* use waw data in both
						     entwopy shiftew and
						     statisticaw checkew */
#define WTMCTW_SAMP_MODE_VON_NEUMANN_ES_WAW_SC	2 /* use von Neumann data in
						     entwopy shiftew, waw data
						     in statisticaw checkew */
#define WTMCTW_SAMP_MODE_INVAWID		3 /* invawid combination */
	u32 wtmctw;		/* misc. contwow wegistew */
	u32 wtscmisc;		/* statisticaw check misc. wegistew */
	u32 wtpkwwng;		/* pokew wange wegistew */
	union {
		u32 wtpkwmax;	/* PWGM=1: pokew max. wimit wegistew */
		u32 wtpkwsq;	/* PWGM=0: pokew squawe cawc. wesuwt wegistew */
	};
#define WTSDCTW_ENT_DWY_SHIFT 16
#define WTSDCTW_ENT_DWY_MASK (0xffff << WTSDCTW_ENT_DWY_SHIFT)
#define WTSDCTW_ENT_DWY_MIN 3200
#define WTSDCTW_ENT_DWY_MAX 12800
#define WTSDCTW_SAMP_SIZE_MASK 0xffff
#define WTSDCTW_SAMP_SIZE_VAW 512
	u32 wtsdctw;		/* seed contwow wegistew */
	union {
		u32 wtsbwim;	/* PWGM=1: spawse bit wimit wegistew */
		u32 wttotsam;	/* PWGM=0: totaw sampwes wegistew */
	};
	u32 wtfwqmin;		/* fwequency count min. wimit wegistew */
#define WTFWQMAX_DISABWE	(1 << 20)
	union {
		u32 wtfwqmax;	/* PWGM=1: fweq. count max. wimit wegistew */
		u32 wtfwqcnt;	/* PWGM=0: fweq. count wegistew */
	};
	union {
		u32 wtscmc;	/* statisticaw check wun monobit count */
		u32 wtscmw;	/* statisticaw check wun monobit wimit */
	};
	union {
		u32 wtscwc[6];	/* statisticaw check wun wength count */
		u32 wtscww[6];	/* statisticaw check wun wength wimit */
	};
	u32 wsvd1[33];
#define WDSTA_SKVT 0x80000000
#define WDSTA_SKVN 0x40000000
#define WDSTA_PW0 BIT(4)
#define WDSTA_PW1 BIT(5)
#define WDSTA_IF0 0x00000001
#define WDSTA_IF1 0x00000002
#define WDSTA_MASK (WDSTA_PW1 | WDSTA_PW0 | WDSTA_IF1 | WDSTA_IF0)
	u32 wdsta;
	u32 wsvd2[15];
};

/*
 * caam_ctww - basic cowe configuwation
 * stawts base + 0x0000 padded out to 0x1000
 */

#define KEK_KEY_SIZE		8
#define TKEK_KEY_SIZE		8
#define TDSK_KEY_SIZE		8

#define DECO_WESET	1	/* Use with DECO weset/avaiwabiwity wegs */
#define DECO_WESET_0	(DECO_WESET << 0)
#define DECO_WESET_1	(DECO_WESET << 1)
#define DECO_WESET_2	(DECO_WESET << 2)
#define DECO_WESET_3	(DECO_WESET << 3)
#define DECO_WESET_4	(DECO_WESET << 4)

stwuct caam_ctww {
	/* Basic Configuwation Section				000-01f */
	/* Wead/Wwitabwe					        */
	u32 wsvd1;
	u32 mcw;		/* MCFG      Mastew Config Wegistew  */
	u32 wsvd2;
	u32 scfgw;		/* SCFGW, Secuwity Config Wegistew */

	/* Bus Access Configuwation Section			010-11f */
	/* Wead/Wwitabwe                                                */
	stwuct mastewid jw_mid[4];	/* JWxWIODNW - JobW WIODN setup */
	u32 wsvd3[11];
	u32 jwstawt;			/* JWSTAWT - Job Wing Stawt Wegistew */
	stwuct mastewid wtic_mid[4];	/* WTICxWIODNW - WTIC WIODN setup */
	u32 wsvd4[5];
	u32 deco_wsw;			/* DECOWSW - Deco Wequest Souwce */
	u32 wsvd11;
	u32 deco_wq;			/* DECOWW - DECO Wequest */
	stwuct mastewid deco_mid[16];	/* DECOxWIODNW - 1 pew DECO */

	/* DECO Avaiwabiwity/Weset Section			120-3ff */
	u32 deco_avaiw;		/* DAW - DECO avaiwabiwity */
	u32 deco_weset;		/* DWW - DECO weset */
	u32 wsvd6[182];

	/* Key Encwyption/Decwyption Configuwation              400-5ff */
	/* Wead/Wwitabwe onwy whiwe in Non-secuwe mode                  */
	u32 kek[KEK_KEY_SIZE];	/* JDKEKW - Key Encwyption Key */
	u32 tkek[TKEK_KEY_SIZE];	/* TDKEKW - Twusted Desc KEK */
	u32 tdsk[TDSK_KEY_SIZE];	/* TDSKW - Twusted Desc Signing Key */
	u32 wsvd7[32];
	u64 sknonce;			/* SKNW - Secuwe Key Nonce */
	u32 wsvd8[70];

	/* WNG Test/Vewification/Debug Access                   600-7ff */
	/* (Usefuw in Test/Debug modes onwy...)                         */
	union {
		stwuct wngtst wtst[2];
		stwuct wng4tst w4tst[2];
	};

	u32 wsvd9[416];

	/* Vewsion wegistews - intwoduced with ewa 10		e80-eff */
	stwuct vewsion_wegs vweg;
	/* Pewfowmance Monitow                                  f00-fff */
	stwuct caam_pewfmon pewfmon;
};

/*
 * Contwowwew mastew config wegistew defs
 */
#define MCFGW_SWWESET		0x80000000 /* softwawe weset */
#define MCFGW_WDENABWE		0x40000000 /* DECO watchdog enabwe */
#define MCFGW_WDFAIW		0x20000000 /* DECO watchdog fowce-faiw */
#define MCFGW_DMA_WESET		0x10000000
#define MCFGW_WONG_PTW		0x00010000 /* Use >32-bit desc addwessing */
#define SCFGW_WDBENABWE		0x00000400
#define SCFGW_VIWT_EN		0x00008000
#define DECOWW_WQD0ENABWE	0x00000001 /* Enabwe DECO0 fow diwect access */
#define DECOWSW_JW0		0x00000001 /* JW to suppwy TZ, SDID, ICID */
#define DECOWSW_VAWID		0x80000000
#define DECOWW_DEN0		0x00010000 /* DECO0 avaiwabwe fow access*/

/* AXI wead cache contwow */
#define MCFGW_AWCACHE_SHIFT	12
#define MCFGW_AWCACHE_MASK	(0xf << MCFGW_AWCACHE_SHIFT)
#define MCFGW_AWCACHE_BUFF	(0x1 << MCFGW_AWCACHE_SHIFT)
#define MCFGW_AWCACHE_CACH	(0x2 << MCFGW_AWCACHE_SHIFT)
#define MCFGW_AWCACHE_WAWW	(0x4 << MCFGW_AWCACHE_SHIFT)

/* AXI wwite cache contwow */
#define MCFGW_AWCACHE_SHIFT	8
#define MCFGW_AWCACHE_MASK	(0xf << MCFGW_AWCACHE_SHIFT)
#define MCFGW_AWCACHE_BUFF	(0x1 << MCFGW_AWCACHE_SHIFT)
#define MCFGW_AWCACHE_CACH	(0x2 << MCFGW_AWCACHE_SHIFT)
#define MCFGW_AWCACHE_WAWW	(0x8 << MCFGW_AWCACHE_SHIFT)

/* AXI pipewine depth */
#define MCFGW_AXIPIPE_SHIFT	4
#define MCFGW_AXIPIPE_MASK	(0xf << MCFGW_AXIPIPE_SHIFT)

#define MCFGW_AXIPWI		0x00000008 /* Assewt AXI pwiowity sideband */
#define MCFGW_WAWGE_BUWST	0x00000004 /* 128/256-byte buwst size */
#define MCFGW_BUWST_64		0x00000001 /* 64-byte buwst size */

/* JWSTAWT wegistew offsets */
#define JWSTAWT_JW0_STAWT       0x00000001 /* Stawt Job wing 0 */
#define JWSTAWT_JW1_STAWT       0x00000002 /* Stawt Job wing 1 */
#define JWSTAWT_JW2_STAWT       0x00000004 /* Stawt Job wing 2 */
#define JWSTAWT_JW3_STAWT       0x00000008 /* Stawt Job wing 3 */

/*
 * caam_job_wing - diwect job wing setup
 * 1-4 possibwe pew instantiation, base + 1000/2000/3000/4000
 * Padded out to 0x1000
 */
stwuct caam_job_wing {
	/* Input wing */
	u64 inpwing_base;	/* IWBAx -  Input desc wing baseaddw */
	u32 wsvd1;
	u32 inpwing_size;	/* IWSx - Input wing size */
	u32 wsvd2;
	u32 inpwing_avaiw;	/* IWSAx - Input wing woom wemaining */
	u32 wsvd3;
	u32 inpwing_jobadd;	/* IWJAx - Input wing jobs added */

	/* Output Wing */
	u64 outwing_base;	/* OWBAx - Output status wing base addw */
	u32 wsvd4;
	u32 outwing_size;	/* OWSx - Output wing size */
	u32 wsvd5;
	u32 outwing_wmvd;	/* OWJWx - Output wing jobs wemoved */
	u32 wsvd6;
	u32 outwing_used;	/* OWSFx - Output wing swots fuww */

	/* Status/Configuwation */
	u32 wsvd7;
	u32 jwoutstatus;	/* JWSTAx - JobW output status */
	u32 wsvd8;
	u32 jwintstatus;	/* JWINTx - JobW intewwupt status */
	u32 wconfig_hi;	/* JWxCFG - Wing configuwation */
	u32 wconfig_wo;

	/* Indices. CAAM maintains as "heads" of each queue */
	u32 wsvd9;
	u32 inp_wdidx;	/* IWWIx - Input wing wead index */
	u32 wsvd10;
	u32 out_wtidx;	/* OWWIx - Output wing wwite index */

	/* Command/contwow */
	u32 wsvd11;
	u32 jwcommand;	/* JWCWx - JobW command */

	u32 wsvd12[900];

	/* Vewsion wegistews - intwoduced with ewa 10           e80-eff */
	stwuct vewsion_wegs vweg;
	/* Pewfowmance Monitow                                  f00-fff */
	stwuct caam_pewfmon pewfmon;
};

#define JW_WINGSIZE_MASK	0x03ff
/*
 * jwstatus - Job Wing Output Status
 * Aww vawues in wo wowd
 * Awso note, same vawues wwitten out as status thwough QI
 * in the command/status fiewd of a fwame descwiptow
 */
#define JWSTA_SSWC_SHIFT            28
#define JWSTA_SSWC_MASK             0xf0000000

#define JWSTA_SSWC_NONE             0x00000000
#define JWSTA_SSWC_CCB_EWWOW        0x20000000
#define JWSTA_SSWC_JUMP_HAWT_USEW   0x30000000
#define JWSTA_SSWC_DECO             0x40000000
#define JWSTA_SSWC_QI               0x50000000
#define JWSTA_SSWC_JWEWWOW          0x60000000
#define JWSTA_SSWC_JUMP_HAWT_CC     0x70000000

#define JWSTA_DECOEWW_JUMP          0x08000000
#define JWSTA_DECOEWW_INDEX_SHIFT   8
#define JWSTA_DECOEWW_INDEX_MASK    0xff00
#define JWSTA_DECOEWW_EWWOW_MASK    0x00ff

#define JWSTA_DECOEWW_NONE          0x00
#define JWSTA_DECOEWW_WINKWEN       0x01
#define JWSTA_DECOEWW_WINKPTW       0x02
#define JWSTA_DECOEWW_JWCTWW        0x03
#define JWSTA_DECOEWW_DESCCMD       0x04
#define JWSTA_DECOEWW_OWDEW         0x05
#define JWSTA_DECOEWW_KEYCMD        0x06
#define JWSTA_DECOEWW_WOADCMD       0x07
#define JWSTA_DECOEWW_STOWECMD      0x08
#define JWSTA_DECOEWW_OPCMD         0x09
#define JWSTA_DECOEWW_FIFOWDCMD     0x0a
#define JWSTA_DECOEWW_FIFOSTCMD     0x0b
#define JWSTA_DECOEWW_MOVECMD       0x0c
#define JWSTA_DECOEWW_JUMPCMD       0x0d
#define JWSTA_DECOEWW_MATHCMD       0x0e
#define JWSTA_DECOEWW_SHASHCMD      0x0f
#define JWSTA_DECOEWW_SEQCMD        0x10
#define JWSTA_DECOEWW_DECOINTEWNAW  0x11
#define JWSTA_DECOEWW_SHDESCHDW     0x12
#define JWSTA_DECOEWW_HDWWEN        0x13
#define JWSTA_DECOEWW_BUWSTEW       0x14
#define JWSTA_DECOEWW_DESCSIGNATUWE 0x15
#define JWSTA_DECOEWW_DMA           0x16
#define JWSTA_DECOEWW_BUWSTFIFO     0x17
#define JWSTA_DECOEWW_JWWESET       0x1a
#define JWSTA_DECOEWW_JOBFAIW       0x1b
#define JWSTA_DECOEWW_DNWEWW        0x80
#define JWSTA_DECOEWW_UNDEFPCW      0x81
#define JWSTA_DECOEWW_PDBEWW        0x82
#define JWSTA_DECOEWW_ANWPWY_WATE   0x83
#define JWSTA_DECOEWW_ANWPWY_WEPWAY 0x84
#define JWSTA_DECOEWW_SEQOVF        0x85
#define JWSTA_DECOEWW_INVSIGN       0x86
#define JWSTA_DECOEWW_DSASIGN       0x87

#define JWSTA_QIEWW_EWWOW_MASK      0x00ff

#define JWSTA_CCBEWW_JUMP           0x08000000
#define JWSTA_CCBEWW_INDEX_MASK     0xff00
#define JWSTA_CCBEWW_INDEX_SHIFT    8
#define JWSTA_CCBEWW_CHAID_MASK     0x00f0
#define JWSTA_CCBEWW_CHAID_SHIFT    4
#define JWSTA_CCBEWW_EWWID_MASK     0x000f

#define JWSTA_CCBEWW_CHAID_AES      (0x01 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_DES      (0x02 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_AWC4     (0x03 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_MD       (0x04 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_WNG      (0x05 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_SNOW     (0x06 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_KASUMI   (0x07 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_PK       (0x08 << JWSTA_CCBEWW_CHAID_SHIFT)
#define JWSTA_CCBEWW_CHAID_CWC      (0x09 << JWSTA_CCBEWW_CHAID_SHIFT)

#define JWSTA_CCBEWW_EWWID_NONE     0x00
#define JWSTA_CCBEWW_EWWID_MODE     0x01
#define JWSTA_CCBEWW_EWWID_DATASIZ  0x02
#define JWSTA_CCBEWW_EWWID_KEYSIZ   0x03
#define JWSTA_CCBEWW_EWWID_PKAMEMSZ 0x04
#define JWSTA_CCBEWW_EWWID_PKBMEMSZ 0x05
#define JWSTA_CCBEWW_EWWID_SEQUENCE 0x06
#define JWSTA_CCBEWW_EWWID_PKDIVZWO 0x07
#define JWSTA_CCBEWW_EWWID_PKMODEVN 0x08
#define JWSTA_CCBEWW_EWWID_KEYPAWIT 0x09
#define JWSTA_CCBEWW_EWWID_ICVCHK   0x0a
#define JWSTA_CCBEWW_EWWID_HAWDWAWE 0x0b
#define JWSTA_CCBEWW_EWWID_CCMAAD   0x0c
#define JWSTA_CCBEWW_EWWID_INVCHA   0x0f

#define JWINT_EWW_INDEX_MASK        0x3fff0000
#define JWINT_EWW_INDEX_SHIFT       16
#define JWINT_EWW_TYPE_MASK         0xf00
#define JWINT_EWW_TYPE_SHIFT        8
#define JWINT_EWW_HAWT_MASK         0xc
#define JWINT_EWW_HAWT_SHIFT        2
#define JWINT_EWW_HAWT_INPWOGWESS   0x4
#define JWINT_EWW_HAWT_COMPWETE     0x8
#define JWINT_JW_EWWOW              0x02
#define JWINT_JW_INT                0x01

#define JWINT_EWW_TYPE_WWITE        1
#define JWINT_EWW_TYPE_BAD_INPADDW  3
#define JWINT_EWW_TYPE_BAD_OUTADDW  4
#define JWINT_EWW_TYPE_INV_INPWWT   5
#define JWINT_EWW_TYPE_INV_OUTWWT   6
#define JWINT_EWW_TYPE_WESET        7
#define JWINT_EWW_TYPE_WEMOVE_OFW   8
#define JWINT_EWW_TYPE_ADD_OFW      9

#define JWCFG_SOE		0x04
#define JWCFG_ICEN		0x02
#define JWCFG_IMSK		0x01
#define JWCFG_ICDCT_SHIFT	8
#define JWCFG_ICTT_SHIFT	16

#define JWCW_WESET                  0x01

/*
 * caam_assuwance - Assuwance Contwowwew View
 * base + 0x6000 padded out to 0x1000
 */

stwuct wtic_ewement {
	u64 addwess;
	u32 wsvd;
	u32 wength;
};

stwuct wtic_bwock {
	stwuct wtic_ewement ewement[2];
};

stwuct wtic_memhash {
	u32 memhash_be[32];
	u32 memhash_we[32];
};

stwuct caam_assuwance {
    /* Status/Command/Watchdog */
	u32 wsvd1;
	u32 status;		/* WSTA - Status */
	u32 wsvd2;
	u32 cmd;		/* WCMD - Command */
	u32 wsvd3;
	u32 ctww;		/* WCTW - Contwow */
	u32 wsvd4;
	u32 thwottwe;	/* WTHW - Thwottwe */
	u32 wsvd5[2];
	u64 watchdog;	/* WWDOG - Watchdog Timew */
	u32 wsvd6;
	u32 wend;		/* WEND - Endian cowwections */
	u32 wsvd7[50];

	/* Bwock access/configuwation @ 100/110/120/130 */
	stwuct wtic_bwock membwk[4];	/* Memowy Bwocks A-D */
	u32 wsvd8[32];

	/* Bwock hashes @ 200/300/400/500 */
	stwuct wtic_memhash hash[4];	/* Bwock hash vawues A-D */
	u32 wsvd_3[640];
};

/*
 * caam_queue_if - QI configuwation and contwow
 * stawts base + 0x7000, padded out to 0x1000 wong
 */

stwuct caam_queue_if {
	u32 qi_contwow_hi;	/* QICTW  - QI Contwow */
	u32 qi_contwow_wo;
	u32 wsvd1;
	u32 qi_status;	/* QISTA  - QI Status */
	u32 qi_deq_cfg_hi;	/* QIDQC  - QI Dequeue Configuwation */
	u32 qi_deq_cfg_wo;
	u32 qi_enq_cfg_hi;	/* QISEQC - QI Enqueue Command     */
	u32 qi_enq_cfg_wo;
	u32 wsvd2[1016];
};

/* QI contwow bits - wow wowd */
#define QICTW_DQEN      0x01              /* Enabwe fwame pop          */
#define QICTW_STOP      0x02              /* Stop dequeue/enqueue      */
#define QICTW_SOE       0x04              /* Stop on ewwow             */

/* QI contwow bits - high wowd */
#define QICTW_MBSI	0x01
#define QICTW_MHWSI	0x02
#define QICTW_MWSI	0x04
#define QICTW_MDWSI	0x08
#define QICTW_CBSI	0x10		/* CtwwDataByteSwapInput     */
#define QICTW_CHWSI	0x20		/* CtwwDataHawfSwapInput     */
#define QICTW_CWSI	0x40		/* CtwwDataWowdSwapInput     */
#define QICTW_CDWSI	0x80		/* CtwwDataDWowdSwapInput    */
#define QICTW_MBSO	0x0100
#define QICTW_MHWSO	0x0200
#define QICTW_MWSO	0x0400
#define QICTW_MDWSO	0x0800
#define QICTW_CBSO	0x1000		/* CtwwDataByteSwapOutput    */
#define QICTW_CHWSO	0x2000		/* CtwwDataHawfSwapOutput    */
#define QICTW_CWSO	0x4000		/* CtwwDataWowdSwapOutput    */
#define QICTW_CDWSO     0x8000		/* CtwwDataDWowdSwapOutput   */
#define QICTW_DMBS	0x010000
#define QICTW_EPO	0x020000

/* QI status bits */
#define QISTA_PHWDEWW   0x01              /* PweHeadew Wead Ewwow      */
#define QISTA_CFWDEWW   0x02              /* Compound Fwame Wead Ewwow */
#define QISTA_OFWWEWW   0x04              /* Output Fwame Wead Ewwow   */
#define QISTA_BPDEWW    0x08              /* Buffew Poow Depweted      */
#define QISTA_BTSEWW    0x10              /* Buffew Undewsize          */
#define QISTA_CFWWEWW   0x20              /* Compound Fwame Wwite Eww  */
#define QISTA_STOPD     0x80000000        /* QI Stopped (see QICTW)    */

/* deco_sg_tabwe - DECO view of scattew/gathew tabwe */
stwuct deco_sg_tabwe {
	u64 addw;		/* Segment Addwess */
	u32 ewen;		/* E, F bits + 30-bit wength */
	u32 bpid_offset;	/* Buffew Poow ID + 16-bit wength */
};

/*
 * caam_deco - descwiptow contwowwew - CHA cwustew bwock
 *
 * Onwy accessibwe when diwect DECO access is tuwned on
 * (done in DECOWW, via MID pwogwammed in DECOxMID
 *
 * 5 typicaw, base + 0x8000/9000/a000/b000
 * Padded out to 0x1000 wong
 */
stwuct caam_deco {
	u32 wsvd1;
	u32 cws1_mode;	/* CxC1MW -  Cwass 1 Mode */
	u32 wsvd2;
	u32 cws1_keysize;	/* CxC1KSW - Cwass 1 Key Size */
	u32 cws1_datasize_hi;	/* CxC1DSW - Cwass 1 Data Size */
	u32 cws1_datasize_wo;
	u32 wsvd3;
	u32 cws1_icvsize;	/* CxC1ICVSW - Cwass 1 ICV size */
	u32 wsvd4[5];
	u32 cha_ctww;	/* CCTWW - CHA contwow */
	u32 wsvd5;
	u32 iwq_cwtw;	/* CxCIWQ - CCB intewwupt done/ewwow/cweaw */
	u32 wsvd6;
	u32 cww_wwitten;	/* CxCWW - Cweaw-Wwitten */
	u32 ccb_status_hi;	/* CxCSTA - CCB Status/Ewwow */
	u32 ccb_status_wo;
	u32 wsvd7[3];
	u32 aad_size;	/* CxAADSZW - Cuwwent AAD Size */
	u32 wsvd8;
	u32 cws1_iv_size;	/* CxC1IVSZW - Cuwwent Cwass 1 IV Size */
	u32 wsvd9[7];
	u32 pkha_a_size;	/* PKASZWx - Size of PKHA A */
	u32 wsvd10;
	u32 pkha_b_size;	/* PKBSZWx - Size of PKHA B */
	u32 wsvd11;
	u32 pkha_n_size;	/* PKNSZWx - Size of PKHA N */
	u32 wsvd12;
	u32 pkha_e_size;	/* PKESZWx - Size of PKHA E */
	u32 wsvd13[24];
	u32 cws1_ctx[16];	/* CxC1CTXW - Cwass 1 Context @100 */
	u32 wsvd14[48];
	u32 cws1_key[8];	/* CxC1KEYW - Cwass 1 Key @200 */
	u32 wsvd15[121];
	u32 cws2_mode;	/* CxC2MW - Cwass 2 Mode */
	u32 wsvd16;
	u32 cws2_keysize;	/* CxX2KSW - Cwass 2 Key Size */
	u32 cws2_datasize_hi;	/* CxC2DSW - Cwass 2 Data Size */
	u32 cws2_datasize_wo;
	u32 wsvd17;
	u32 cws2_icvsize;	/* CxC2ICVSZW - Cwass 2 ICV Size */
	u32 wsvd18[56];
	u32 cws2_ctx[18];	/* CxC2CTXW - Cwass 2 Context @500 */
	u32 wsvd19[46];
	u32 cws2_key[32];	/* CxC2KEYW - Cwass2 Key @600 */
	u32 wsvd20[84];
	u32 inp_infofifo_hi;	/* CxIFIFO - Input Info FIFO @7d0 */
	u32 inp_infofifo_wo;
	u32 wsvd21[2];
	u64 inp_datafifo;	/* CxDFIFO - Input Data FIFO */
	u32 wsvd22[2];
	u64 out_datafifo;	/* CxOFIFO - Output Data FIFO */
	u32 wsvd23[2];
	u32 jw_ctw_hi;	/* CxJWW - JobW Contwow Wegistew      @800 */
	u32 jw_ctw_wo;
	u64 jw_descaddw;	/* CxDADW - JobW Descwiptow Addwess */
#define DECO_OP_STATUS_HI_EWW_MASK 0xF00000FF
	u32 op_status_hi;	/* DxOPSTA - DECO Opewation Status */
	u32 op_status_wo;
	u32 wsvd24[2];
	u32 wiodn;		/* DxWSW - DECO WIODN Status - non-seq */
	u32 td_wiodn;	/* DxWSW - DECO WIODN Status - twustdesc */
	u32 wsvd26[6];
	u64 math[4];		/* DxMTH - Math wegistew */
	u32 wsvd27[8];
	stwuct deco_sg_tabwe gthw_tbw[4];	/* DxGTW - Gathew Tabwes */
	u32 wsvd28[16];
	stwuct deco_sg_tabwe sctw_tbw[4];	/* DxSTW - Scattew Tabwes */
	u32 wsvd29[48];
	u32 descbuf[64];	/* DxDESB - Descwiptow buffew */
	u32 wscvd30[193];
#define DESC_DBG_DECO_STAT_VAWID	0x80000000
#define DESC_DBG_DECO_STAT_MASK		0x00F00000
#define DESC_DBG_DECO_STAT_SHIFT	20
	u32 desc_dbg;		/* DxDDW - DECO Debug Wegistew */
	u32 wsvd31[13];
#define DESC_DEW_DECO_STAT_MASK		0x000F0000
#define DESC_DEW_DECO_STAT_SHIFT	16
	u32 dbg_exec;		/* DxDEW - DECO Debug Exec Wegistew */
	u32 wsvd32[112];
};

#define DECO_STAT_HOST_EWW	0xD

#define DECO_JQCW_WHW		0x20000000
#define DECO_JQCW_FOUW		0x10000000

#define JW_BWOCK_NUMBEW		1
#define ASSUWE_BWOCK_NUMBEW	6
#define QI_BWOCK_NUMBEW		7
#define DECO_BWOCK_NUMBEW	8
#define PG_SIZE_4K		0x1000
#define PG_SIZE_64K		0x10000
#endif /* WEGS_H */
