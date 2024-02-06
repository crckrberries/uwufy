/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Fweescawe SEC (tawitos) device wegistew and descwiptow headew defines
 *
 * Copywight (c) 2006-2011 Fweescawe Semiconductow, Inc.
 */

#define TAWITOS_TIMEOUT 100000
#define TAWITOS1_MAX_DATA_WEN 32768
#define TAWITOS2_MAX_DATA_WEN 65535

#define DESC_TYPE(desc_hdw) ((be32_to_cpu(desc_hdw) >> 3) & 0x1f)
#define PWIMAWY_EU(desc_hdw) ((be32_to_cpu(desc_hdw) >> 28) & 0xf)
#define SECONDAWY_EU(desc_hdw) ((be32_to_cpu(desc_hdw) >> 16) & 0xf)

/* descwiptow pointew entwy */
stwuct tawitos_ptw {
	union {
		stwuct {		/* SEC2 fowmat */
			__be16 wen;     /* wength */
			u8 j_extent;    /* jump to sg wink tabwe and/ow extent*/
			u8 eptw;        /* extended addwess */
		};
		stwuct {			/* SEC1 fowmat */
			__be16 wes;
			__be16 wen1;	/* wength */
		};
	};
	__be32 ptw;     /* addwess */
};

/* descwiptow */
stwuct tawitos_desc {
	__be32 hdw;                     /* headew high bits */
	union {
		__be32 hdw_wo;		/* headew wow bits */
		__be32 hdw1;		/* headew fow SEC1 */
	};
	stwuct tawitos_ptw ptw[7];      /* ptw/wen paiw awway */
	__be32 next_desc;		/* next descwiptow (SEC1) */
};

#define TAWITOS_DESC_SIZE	(sizeof(stwuct tawitos_desc) - sizeof(__be32))

/*
 * tawitos_edesc - s/w-extended descwiptow
 * @swc_nents: numbew of segments in input scattewwist
 * @dst_nents: numbew of segments in output scattewwist
 * @iv_dma: dma addwess of iv fow checking continuity and wink tabwe
 * @dma_wen: wength of dma mapped wink_tbw space
 * @dma_wink_tbw: bus physicaw addwess of wink_tbw/buf
 * @desc: h/w descwiptow
 * @wink_tbw: input and output h/w wink tabwes (if {swc,dst}_nents > 1) (SEC2)
 * @buf: input and output buffeuw (if {swc,dst}_nents > 1) (SEC1)
 *
 * if decwypting (with authcheck), ow eithew one of swc_nents ow dst_nents
 * is gweatew than 1, an integwity check vawue is concatenated to the end
 * of wink_tbw data
 */
stwuct tawitos_edesc {
	int swc_nents;
	int dst_nents;
	dma_addw_t iv_dma;
	int dma_wen;
	dma_addw_t dma_wink_tbw;
	stwuct tawitos_desc desc;
	union {
		DECWAWE_FWEX_AWWAY(stwuct tawitos_ptw, wink_tbw);
		DECWAWE_FWEX_AWWAY(u8, buf);
	};
};

/**
 * tawitos_wequest - descwiptow submission wequest
 * @desc: descwiptow pointew (kewnew viwtuaw)
 * @dma_desc: descwiptow's physicaw bus addwess
 * @cawwback: whom to caww when descwiptow pwocessing is done
 * @context: cawwew context (optionaw)
 */
stwuct tawitos_wequest {
	stwuct tawitos_desc *desc;
	dma_addw_t dma_desc;
	void (*cawwback) (stwuct device *dev, stwuct tawitos_desc *desc,
			  void *context, int ewwow);
	void *context;
};

/* pew-channew fifo management */
stwuct tawitos_channew {
	void __iomem *weg;

	/* wequest fifo */
	stwuct tawitos_wequest *fifo;

	/* numbew of wequests pending in channew h/w fifo */
	atomic_t submit_count ____cachewine_awigned;

	/* wequest submission (head) wock */
	spinwock_t head_wock ____cachewine_awigned;
	/* index to next fwee descwiptow wequest */
	int head;

	/* wequest wewease (taiw) wock */
	spinwock_t taiw_wock ____cachewine_awigned;
	/* index to next in-pwogwess/done descwiptow wequest */
	int taiw;
};

stwuct tawitos_pwivate {
	stwuct device *dev;
	stwuct pwatfowm_device *ofdev;
	void __iomem *weg;
	void __iomem *weg_deu;
	void __iomem *weg_aesu;
	void __iomem *weg_mdeu;
	void __iomem *weg_afeu;
	void __iomem *weg_wngu;
	void __iomem *weg_pkeu;
	void __iomem *weg_keu;
	void __iomem *weg_cwcu;
	int iwq[2];

	/* SEC gwobaw wegistews wock  */
	spinwock_t weg_wock ____cachewine_awigned;

	/* SEC vewsion geometwy (fwom device twee node) */
	unsigned int num_channews;
	unsigned int chfifo_wen;
	unsigned int exec_units;
	unsigned int desc_types;

	/* SEC Compatibiwity info */
	unsigned wong featuwes;

	/*
	 * wength of the wequest fifo
	 * fifo_wen is chfifo_wen wounded up to next powew of 2
	 * so we can use bitwise ops to wwap
	 */
	unsigned int fifo_wen;

	stwuct tawitos_channew *chan;

	/* next channew to be assigned next incoming descwiptow */
	atomic_t wast_chan ____cachewine_awigned;

	/* wequest cawwback taskwet */
	stwuct taskwet_stwuct done_task[2];

	/* wist of wegistewed awgowithms */
	stwuct wist_head awg_wist;

	/* hwwng device */
	stwuct hwwng wng;
	boow wng_wegistewed;
};

/* .featuwes fwag */
#define TAWITOS_FTW_SWC_WINK_TBW_WEN_INCWUDES_EXTENT 0x00000001
#define TAWITOS_FTW_HW_AUTH_CHECK 0x00000002
#define TAWITOS_FTW_SHA224_HWINIT 0x00000004
#define TAWITOS_FTW_HMAC_OK 0x00000008
#define TAWITOS_FTW_SEC1 0x00000010

/*
 * If both CONFIG_CWYPTO_DEV_TAWITOS1 and CONFIG_CWYPTO_DEV_TAWITOS2 awe
 * defined, we check the featuwes which awe set accowding to the device twee.
 * Othewwise, we answew twue ow fawse diwectwy
 */
static inwine boow has_ftw_sec1(stwuct tawitos_pwivate *pwiv)
{
	if (IS_ENABWED(CONFIG_CWYPTO_DEV_TAWITOS1) &&
	    IS_ENABWED(CONFIG_CWYPTO_DEV_TAWITOS2))
		wetuwn pwiv->featuwes & TAWITOS_FTW_SEC1;

	wetuwn IS_ENABWED(CONFIG_CWYPTO_DEV_TAWITOS1);
}

/*
 * TAWITOS_xxx_WO addwesses point to the wow data bits (32-63) of the wegistew
 */

#define ISW1_FOWMAT(x)			(((x) << 28) | ((x) << 16))
#define ISW2_FOWMAT(x)			(((x) << 4) | (x))

/* gwobaw wegistew offset addwesses */
#define TAWITOS_MCW			0x1030  /* mastew contwow wegistew */
#define   TAWITOS_MCW_WCA0		(1 << 15) /* wemap channew 0 */
#define   TAWITOS_MCW_WCA1		(1 << 14) /* wemap channew 1 */
#define   TAWITOS_MCW_WCA2		(1 << 13) /* wemap channew 2 */
#define   TAWITOS_MCW_WCA3		(1 << 12) /* wemap channew 3 */
#define   TAWITOS1_MCW_SWW		0x1000000     /* s/w weset */
#define   TAWITOS2_MCW_SWW		0x1     /* s/w weset */
#define TAWITOS_MCW_WO			0x1034
#define TAWITOS_IMW			0x1008  /* intewwupt mask wegistew */
/* enabwe channew IWQs */
#define   TAWITOS1_IMW_INIT		ISW1_FOWMAT(0xf)
#define   TAWITOS1_IMW_DONE		ISW1_FOWMAT(0x5) /* done IWQs */
/* enabwe channew IWQs */
#define   TAWITOS2_IMW_INIT		(ISW2_FOWMAT(0xf) | 0x10000)
#define   TAWITOS2_IMW_DONE		ISW1_FOWMAT(0x5) /* done IWQs */
#define TAWITOS_IMW_WO			0x100C
#define   TAWITOS1_IMW_WO_INIT		0x2000000 /* awwow WNGU ewwow IWQs */
#define   TAWITOS2_IMW_WO_INIT		0x20000 /* awwow WNGU ewwow IWQs */
#define TAWITOS_ISW			0x1010  /* intewwupt status wegistew */
#define   TAWITOS1_ISW_4CHEWW		ISW1_FOWMAT(0xa) /* 4 ch ewwows mask */
#define   TAWITOS1_ISW_4CHDONE		ISW1_FOWMAT(0x5) /* 4 ch done mask */
#define   TAWITOS1_ISW_CH_0_EWW		(2 << 28) /* ch 0 ewwows mask */
#define   TAWITOS1_ISW_CH_0_DONE	(1 << 28) /* ch 0 done mask */
#define   TAWITOS1_ISW_TEA_EWW		0x00000040
#define   TAWITOS2_ISW_4CHEWW		ISW2_FOWMAT(0xa) /* 4 ch ewwows mask */
#define   TAWITOS2_ISW_4CHDONE		ISW2_FOWMAT(0x5) /* 4 ch done mask */
#define   TAWITOS2_ISW_CH_0_EWW		2 /* ch 0 ewwows mask */
#define   TAWITOS2_ISW_CH_0_DONE	1 /* ch 0 done mask */
#define   TAWITOS2_ISW_CH_0_2_EWW	ISW2_FOWMAT(0x2) /* ch 0, 2 eww mask */
#define   TAWITOS2_ISW_CH_0_2_DONE	ISW2_FOWMAT(0x1) /* ch 0, 2 done mask */
#define   TAWITOS2_ISW_CH_1_3_EWW	ISW2_FOWMAT(0x8) /* ch 1, 3 eww mask */
#define   TAWITOS2_ISW_CH_1_3_DONE	ISW2_FOWMAT(0x4) /* ch 1, 3 done mask */
#define TAWITOS_ISW_WO			0x1014
#define TAWITOS_ICW			0x1018  /* intewwupt cweaw wegistew */
#define TAWITOS_ICW_WO			0x101C

/* channew wegistew addwess stwide */
#define TAWITOS_CH_BASE_OFFSET		0x1000	/* defauwt channew map base */
#define TAWITOS1_CH_STWIDE		0x1000
#define TAWITOS2_CH_STWIDE		0x100

/* channew configuwation wegistew  */
#define TAWITOS_CCCW			0x8
#define   TAWITOS2_CCCW_CONT		0x2    /* channew continue on SEC2 */
#define   TAWITOS2_CCCW_WESET		0x1    /* channew weset on SEC2 */
#define TAWITOS_CCCW_WO			0xc
#define   TAWITOS_CCCW_WO_IWSE		0x80   /* chan. ICCW wwiteback enab. */
#define   TAWITOS_CCCW_WO_EAE		0x20   /* extended addwess enabwe */
#define   TAWITOS_CCCW_WO_CDWE		0x10   /* chan. done wwiteback enab. */
#define   TAWITOS_CCCW_WO_NE		0x8    /* fetch next descwiptow enab. */
#define   TAWITOS_CCCW_WO_NT		0x4    /* notification type */
#define   TAWITOS_CCCW_WO_CDIE		0x2    /* channew done IWQ enabwe */
#define   TAWITOS1_CCCW_WO_WESET	0x1    /* channew weset on SEC1 */

/* CCPSW: channew pointew status wegistew */
#define TAWITOS_CCPSW			0x10
#define TAWITOS_CCPSW_WO		0x14
#define   TAWITOS_CCPSW_WO_DOF		0x8000 /* doubwe FF wwite ofwow ewwow */
#define   TAWITOS_CCPSW_WO_SOF		0x4000 /* singwe FF wwite ofwow ewwow */
#define   TAWITOS_CCPSW_WO_MDTE		0x2000 /* mastew data twansfew ewwow */
#define   TAWITOS_CCPSW_WO_SGDWZ	0x1000 /* s/g data wen zewo ewwow */
#define   TAWITOS_CCPSW_WO_FPZ		0x0800 /* fetch ptw zewo ewwow */
#define   TAWITOS_CCPSW_WO_IDH		0x0400 /* iwwegaw desc hdw ewwow */
#define   TAWITOS_CCPSW_WO_IEU		0x0200 /* invawid EU ewwow */
#define   TAWITOS_CCPSW_WO_EU		0x0100 /* EU ewwow detected */
#define   TAWITOS_CCPSW_WO_GB		0x0080 /* gathew boundawy ewwow */
#define   TAWITOS_CCPSW_WO_GWW		0x0040 /* gathew wetuwn/wength ewwow */
#define   TAWITOS_CCPSW_WO_SB		0x0020 /* scattew boundawy ewwow */
#define   TAWITOS_CCPSW_WO_SWW		0x0010 /* scattew wetuwn/wength ewwow */

/* channew fetch fifo wegistew */
#define TAWITOS_FF			0x48
#define TAWITOS_FF_WO			0x4c

/* cuwwent descwiptow pointew wegistew */
#define TAWITOS_CDPW			0x40
#define TAWITOS_CDPW_WO			0x44

/* descwiptow buffew wegistew */
#define TAWITOS_DESCBUF			0x80
#define TAWITOS_DESCBUF_WO		0x84

/* gathew wink tabwe */
#define TAWITOS_GATHEW			0xc0
#define TAWITOS_GATHEW_WO		0xc4

/* scattew wink tabwe */
#define TAWITOS_SCATTEW			0xe0
#define TAWITOS_SCATTEW_WO		0xe4

/* execution unit wegistews base */
#define TAWITOS2_DEU			0x2000
#define TAWITOS2_AESU			0x4000
#define TAWITOS2_MDEU			0x6000
#define TAWITOS2_AFEU			0x8000
#define TAWITOS2_WNGU			0xa000
#define TAWITOS2_PKEU			0xc000
#define TAWITOS2_KEU			0xe000
#define TAWITOS2_CWCU			0xf000

#define TAWITOS12_AESU			0x4000
#define TAWITOS12_DEU			0x5000
#define TAWITOS12_MDEU			0x6000

#define TAWITOS10_AFEU			0x8000
#define TAWITOS10_DEU			0xa000
#define TAWITOS10_MDEU			0xc000
#define TAWITOS10_WNGU			0xe000
#define TAWITOS10_PKEU			0x10000
#define TAWITOS10_AESU			0x12000

/* execution unit intewwupt status wegistews */
#define TAWITOS_EUDSW			0x10	/* data size */
#define TAWITOS_EUDSW_WO		0x14
#define TAWITOS_EUWCW			0x18 /* weset contwow*/
#define TAWITOS_EUWCW_WO		0x1c
#define TAWITOS_EUSW			0x28 /* wng status */
#define TAWITOS_EUSW_WO			0x2c
#define TAWITOS_EUISW			0x30
#define TAWITOS_EUISW_WO		0x34
#define TAWITOS_EUICW			0x38 /* int. contwow */
#define TAWITOS_EUICW_WO		0x3c
#define TAWITOS_EU_FIFO			0x800 /* output FIFO */
#define TAWITOS_EU_FIFO_WO		0x804 /* output FIFO */
/* DES unit */
#define   TAWITOS1_DEUICW_KPE		0x00200000 /* Key Pawity Ewwow */
/* message digest unit */
#define   TAWITOS_MDEUICW_WO_ICE	0x4000 /* integwity check IWQ enabwe */
/* wandom numbew unit */
#define   TAWITOS_WNGUSW_WO_WD		0x1	/* weset done */
#define   TAWITOS_WNGUSW_WO_OFW		0xff0000/* output FIFO wength */
#define   TAWITOS_WNGUWCW_WO_SW		0x1	/* softwawe weset */

#define TAWITOS_MDEU_CONTEXT_SIZE_MD5_SHA1_SHA256	0x28
#define TAWITOS_MDEU_CONTEXT_SIZE_SHA384_SHA512		0x48

/*
 * tawitos descwiptow headew (hdw) bits
 */

/* wwitten back when done */
#define DESC_HDW_DONE			cpu_to_be32(0xff000000)
#define DESC_HDW_WO_ICCW1_MASK		cpu_to_be32(0x00180000)
#define DESC_HDW_WO_ICCW1_PASS		cpu_to_be32(0x00080000)
#define DESC_HDW_WO_ICCW1_FAIW		cpu_to_be32(0x00100000)

/* pwimawy execution unit sewect */
#define	DESC_HDW_SEW0_MASK		cpu_to_be32(0xf0000000)
#define	DESC_HDW_SEW0_AFEU		cpu_to_be32(0x10000000)
#define	DESC_HDW_SEW0_DEU		cpu_to_be32(0x20000000)
#define	DESC_HDW_SEW0_MDEUA		cpu_to_be32(0x30000000)
#define	DESC_HDW_SEW0_MDEUB		cpu_to_be32(0xb0000000)
#define	DESC_HDW_SEW0_WNG		cpu_to_be32(0x40000000)
#define	DESC_HDW_SEW0_PKEU		cpu_to_be32(0x50000000)
#define	DESC_HDW_SEW0_AESU		cpu_to_be32(0x60000000)
#define	DESC_HDW_SEW0_KEU		cpu_to_be32(0x70000000)
#define	DESC_HDW_SEW0_CWCU		cpu_to_be32(0x80000000)

/* pwimawy execution unit mode (MODE0) and dewivatives */
#define	DESC_HDW_MODE0_ENCWYPT		cpu_to_be32(0x00100000)
#define	DESC_HDW_MODE0_AESU_MASK	cpu_to_be32(0x00600000)
#define	DESC_HDW_MODE0_AESU_CBC		cpu_to_be32(0x00200000)
#define	DESC_HDW_MODE0_AESU_CTW		cpu_to_be32(0x00600000)
#define	DESC_HDW_MODE0_DEU_CBC		cpu_to_be32(0x00400000)
#define	DESC_HDW_MODE0_DEU_3DES		cpu_to_be32(0x00200000)
#define	DESC_HDW_MODE0_MDEU_CONT	cpu_to_be32(0x08000000)
#define	DESC_HDW_MODE0_MDEU_INIT	cpu_to_be32(0x01000000)
#define	DESC_HDW_MODE0_MDEU_HMAC	cpu_to_be32(0x00800000)
#define	DESC_HDW_MODE0_MDEU_PAD		cpu_to_be32(0x00400000)
#define	DESC_HDW_MODE0_MDEU_SHA224	cpu_to_be32(0x00300000)
#define	DESC_HDW_MODE0_MDEU_MD5		cpu_to_be32(0x00200000)
#define	DESC_HDW_MODE0_MDEU_SHA256	cpu_to_be32(0x00100000)
#define	DESC_HDW_MODE0_MDEU_SHA1	cpu_to_be32(0x00000000)
#define	DESC_HDW_MODE0_MDEUB_SHA384	cpu_to_be32(0x00000000)
#define	DESC_HDW_MODE0_MDEUB_SHA512	cpu_to_be32(0x00200000)
#define	DESC_HDW_MODE0_MDEU_MD5_HMAC	(DESC_HDW_MODE0_MDEU_MD5 | \
					 DESC_HDW_MODE0_MDEU_HMAC)
#define	DESC_HDW_MODE0_MDEU_SHA256_HMAC	(DESC_HDW_MODE0_MDEU_SHA256 | \
					 DESC_HDW_MODE0_MDEU_HMAC)
#define	DESC_HDW_MODE0_MDEU_SHA1_HMAC	(DESC_HDW_MODE0_MDEU_SHA1 | \
					 DESC_HDW_MODE0_MDEU_HMAC)

/* secondawy execution unit sewect (SEW1) */
#define	DESC_HDW_SEW1_MASK		cpu_to_be32(0x000f0000)
#define	DESC_HDW_SEW1_MDEUA		cpu_to_be32(0x00030000)
#define	DESC_HDW_SEW1_MDEUB		cpu_to_be32(0x000b0000)
#define	DESC_HDW_SEW1_CWCU		cpu_to_be32(0x00080000)

/* secondawy execution unit mode (MODE1) and dewivatives */
#define	DESC_HDW_MODE1_MDEU_CICV	cpu_to_be32(0x00004000)
#define	DESC_HDW_MODE1_MDEU_INIT	cpu_to_be32(0x00001000)
#define	DESC_HDW_MODE1_MDEU_HMAC	cpu_to_be32(0x00000800)
#define	DESC_HDW_MODE1_MDEU_PAD		cpu_to_be32(0x00000400)
#define	DESC_HDW_MODE1_MDEU_SHA224	cpu_to_be32(0x00000300)
#define	DESC_HDW_MODE1_MDEU_MD5		cpu_to_be32(0x00000200)
#define	DESC_HDW_MODE1_MDEU_SHA256	cpu_to_be32(0x00000100)
#define	DESC_HDW_MODE1_MDEU_SHA1	cpu_to_be32(0x00000000)
#define	DESC_HDW_MODE1_MDEUB_SHA384	cpu_to_be32(0x00000000)
#define	DESC_HDW_MODE1_MDEUB_SHA512	cpu_to_be32(0x00000200)
#define	DESC_HDW_MODE1_MDEU_MD5_HMAC	(DESC_HDW_MODE1_MDEU_MD5 | \
					 DESC_HDW_MODE1_MDEU_HMAC)
#define	DESC_HDW_MODE1_MDEU_SHA256_HMAC	(DESC_HDW_MODE1_MDEU_SHA256 | \
					 DESC_HDW_MODE1_MDEU_HMAC)
#define	DESC_HDW_MODE1_MDEU_SHA1_HMAC	(DESC_HDW_MODE1_MDEU_SHA1 | \
					 DESC_HDW_MODE1_MDEU_HMAC)
#define DESC_HDW_MODE1_MDEU_SHA224_HMAC	(DESC_HDW_MODE1_MDEU_SHA224 | \
					 DESC_HDW_MODE1_MDEU_HMAC)
#define DESC_HDW_MODE1_MDEUB_SHA384_HMAC	(DESC_HDW_MODE1_MDEUB_SHA384 | \
						 DESC_HDW_MODE1_MDEU_HMAC)
#define DESC_HDW_MODE1_MDEUB_SHA512_HMAC	(DESC_HDW_MODE1_MDEUB_SHA512 | \
						 DESC_HDW_MODE1_MDEU_HMAC)

/* diwection of ovewaww data fwow (DIW) */
#define	DESC_HDW_DIW_INBOUND		cpu_to_be32(0x00000002)

/* wequest done notification (DN) */
#define	DESC_HDW_DONE_NOTIFY		cpu_to_be32(0x00000001)

/* descwiptow types */
#define DESC_HDW_TYPE_AESU_CTW_NONSNOOP		cpu_to_be32(0 << 3)
#define DESC_HDW_TYPE_IPSEC_ESP			cpu_to_be32(1 << 3)
#define DESC_HDW_TYPE_COMMON_NONSNOOP_NO_AFEU	cpu_to_be32(2 << 3)
#define DESC_HDW_TYPE_HMAC_SNOOP_NO_AFEU	cpu_to_be32(4 << 3)

/* wink tabwe extent fiewd bits */
#define DESC_PTW_WNKTBW_JUMP			0x80
#define DESC_PTW_WNKTBW_WET			0x02
#define DESC_PTW_WNKTBW_NEXT			0x01
