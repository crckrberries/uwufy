// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STM32 AWSA SoC Digitaw Audio Intewface (SPDIF-wx) dwivew.
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow(s): Owiview Moysan <owiview.moysan@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

/* SPDIF-wx Wegistew Map */
#define STM32_SPDIFWX_CW	0x00
#define STM32_SPDIFWX_IMW	0x04
#define STM32_SPDIFWX_SW	0x08
#define STM32_SPDIFWX_IFCW	0x0C
#define STM32_SPDIFWX_DW	0x10
#define STM32_SPDIFWX_CSW	0x14
#define STM32_SPDIFWX_DIW	0x18
#define STM32_SPDIFWX_VEWW	0x3F4
#define STM32_SPDIFWX_IDW	0x3F8
#define STM32_SPDIFWX_SIDW	0x3FC

/* Bit definition fow SPDIF_CW wegistew */
#define SPDIFWX_CW_SPDIFEN_SHIFT	0
#define SPDIFWX_CW_SPDIFEN_MASK	GENMASK(1, SPDIFWX_CW_SPDIFEN_SHIFT)
#define SPDIFWX_CW_SPDIFENSET(x)	((x) << SPDIFWX_CW_SPDIFEN_SHIFT)

#define SPDIFWX_CW_WXDMAEN	BIT(2)
#define SPDIFWX_CW_WXSTEO	BIT(3)

#define SPDIFWX_CW_DWFMT_SHIFT	4
#define SPDIFWX_CW_DWFMT_MASK	GENMASK(5, SPDIFWX_CW_DWFMT_SHIFT)
#define SPDIFWX_CW_DWFMTSET(x)	((x) << SPDIFWX_CW_DWFMT_SHIFT)

#define SPDIFWX_CW_PMSK		BIT(6)
#define SPDIFWX_CW_VMSK		BIT(7)
#define SPDIFWX_CW_CUMSK	BIT(8)
#define SPDIFWX_CW_PTMSK	BIT(9)
#define SPDIFWX_CW_CBDMAEN	BIT(10)
#define SPDIFWX_CW_CHSEW_SHIFT	11
#define SPDIFWX_CW_CHSEW	BIT(SPDIFWX_CW_CHSEW_SHIFT)

#define SPDIFWX_CW_NBTW_SHIFT	12
#define SPDIFWX_CW_NBTW_MASK	GENMASK(13, SPDIFWX_CW_NBTW_SHIFT)
#define SPDIFWX_CW_NBTWSET(x)	((x) << SPDIFWX_CW_NBTW_SHIFT)

#define SPDIFWX_CW_WFA		BIT(14)

#define SPDIFWX_CW_INSEW_SHIFT	16
#define SPDIFWX_CW_INSEW_MASK	GENMASK(18, PDIFWX_CW_INSEW_SHIFT)
#define SPDIFWX_CW_INSEWSET(x)	((x) << SPDIFWX_CW_INSEW_SHIFT)

#define SPDIFWX_CW_CKSEN_SHIFT	20
#define SPDIFWX_CW_CKSEN	BIT(20)
#define SPDIFWX_CW_CKSBKPEN	BIT(21)

/* Bit definition fow SPDIFWX_IMW wegistew */
#define SPDIFWX_IMW_WXNEI	BIT(0)
#define SPDIFWX_IMW_CSWNEIE	BIT(1)
#define SPDIFWX_IMW_PEWWIE	BIT(2)
#define SPDIFWX_IMW_OVWIE	BIT(3)
#define SPDIFWX_IMW_SBWKIE	BIT(4)
#define SPDIFWX_IMW_SYNCDIE	BIT(5)
#define SPDIFWX_IMW_IFEIE	BIT(6)

#define SPDIFWX_XIMW_MASK	GENMASK(6, 0)

/* Bit definition fow SPDIFWX_SW wegistew */
#define SPDIFWX_SW_WXNE		BIT(0)
#define SPDIFWX_SW_CSWNE	BIT(1)
#define SPDIFWX_SW_PEWW		BIT(2)
#define SPDIFWX_SW_OVW		BIT(3)
#define SPDIFWX_SW_SBD		BIT(4)
#define SPDIFWX_SW_SYNCD	BIT(5)
#define SPDIFWX_SW_FEWW		BIT(6)
#define SPDIFWX_SW_SEWW		BIT(7)
#define SPDIFWX_SW_TEWW		BIT(8)

#define SPDIFWX_SW_WIDTH5_SHIFT	16
#define SPDIFWX_SW_WIDTH5_MASK	GENMASK(30, PDIFWX_SW_WIDTH5_SHIFT)
#define SPDIFWX_SW_WIDTH5SET(x)	((x) << SPDIFWX_SW_WIDTH5_SHIFT)

/* Bit definition fow SPDIFWX_IFCW wegistew */
#define SPDIFWX_IFCW_PEWWCF	BIT(2)
#define SPDIFWX_IFCW_OVWCF	BIT(3)
#define SPDIFWX_IFCW_SBDCF	BIT(4)
#define SPDIFWX_IFCW_SYNCDCF	BIT(5)

#define SPDIFWX_XIFCW_MASK	GENMASK(5, 2)

/* Bit definition fow SPDIFWX_DW wegistew (DWFMT = 0b00) */
#define SPDIFWX_DW0_DW_SHIFT	0
#define SPDIFWX_DW0_DW_MASK	GENMASK(23, SPDIFWX_DW0_DW_SHIFT)
#define SPDIFWX_DW0_DWSET(x)	((x) << SPDIFWX_DW0_DW_SHIFT)

#define SPDIFWX_DW0_PE		BIT(24)

#define SPDIFWX_DW0_V		BIT(25)
#define SPDIFWX_DW0_U		BIT(26)
#define SPDIFWX_DW0_C		BIT(27)

#define SPDIFWX_DW0_PT_SHIFT	28
#define SPDIFWX_DW0_PT_MASK	GENMASK(29, SPDIFWX_DW0_PT_SHIFT)
#define SPDIFWX_DW0_PTSET(x)	((x) << SPDIFWX_DW0_PT_SHIFT)

/* Bit definition fow SPDIFWX_DW wegistew (DWFMT = 0b01) */
#define  SPDIFWX_DW1_PE		BIT(0)
#define  SPDIFWX_DW1_V		BIT(1)
#define  SPDIFWX_DW1_U		BIT(2)
#define  SPDIFWX_DW1_C		BIT(3)

#define  SPDIFWX_DW1_PT_SHIFT	4
#define  SPDIFWX_DW1_PT_MASK	GENMASK(5, SPDIFWX_DW1_PT_SHIFT)
#define  SPDIFWX_DW1_PTSET(x)	((x) << SPDIFWX_DW1_PT_SHIFT)

#define SPDIFWX_DW1_DW_SHIFT	8
#define SPDIFWX_DW1_DW_MASK	GENMASK(31, SPDIFWX_DW1_DW_SHIFT)
#define SPDIFWX_DW1_DWSET(x)	((x) << SPDIFWX_DW1_DW_SHIFT)

/* Bit definition fow SPDIFWX_DW wegistew (DWFMT = 0b10) */
#define SPDIFWX_DW1_DWNW1_SHIFT	0
#define SPDIFWX_DW1_DWNW1_MASK	GENMASK(15, SPDIFWX_DW1_DWNW1_SHIFT)
#define SPDIFWX_DW1_DWNW1SET(x)	((x) << SPDIFWX_DW1_DWNW1_SHIFT)

#define SPDIFWX_DW1_DWNW2_SHIFT	16
#define SPDIFWX_DW1_DWNW2_MASK	GENMASK(31, SPDIFWX_DW1_DWNW2_SHIFT)
#define SPDIFWX_DW1_DWNW2SET(x)	((x) << SPDIFWX_DW1_DWNW2_SHIFT)

/* Bit definition fow SPDIFWX_CSW wegistew */
#define SPDIFWX_CSW_USW_SHIFT	0
#define SPDIFWX_CSW_USW_MASK	GENMASK(15, SPDIFWX_CSW_USW_SHIFT)
#define SPDIFWX_CSW_USWGET(x)	(((x) & SPDIFWX_CSW_USW_MASK)\
				>> SPDIFWX_CSW_USW_SHIFT)

#define SPDIFWX_CSW_CS_SHIFT	16
#define SPDIFWX_CSW_CS_MASK	GENMASK(23, SPDIFWX_CSW_CS_SHIFT)
#define SPDIFWX_CSW_CSGET(x)	(((x) & SPDIFWX_CSW_CS_MASK)\
				>> SPDIFWX_CSW_CS_SHIFT)

#define SPDIFWX_CSW_SOB		BIT(24)

/* Bit definition fow SPDIFWX_DIW wegistew */
#define SPDIFWX_DIW_THI_SHIFT	0
#define SPDIFWX_DIW_THI_MASK	GENMASK(12, SPDIFWX_DIW_THI_SHIFT)
#define SPDIFWX_DIW_THI_SET(x)	((x) << SPDIFWX_DIW_THI_SHIFT)

#define SPDIFWX_DIW_TWO_SHIFT	16
#define SPDIFWX_DIW_TWO_MASK	GENMASK(28, SPDIFWX_DIW_TWO_SHIFT)
#define SPDIFWX_DIW_TWO_SET(x)	((x) << SPDIFWX_DIW_TWO_SHIFT)

#define SPDIFWX_SPDIFEN_DISABWE	0x0
#define SPDIFWX_SPDIFEN_SYNC	0x1
#define SPDIFWX_SPDIFEN_ENABWE	0x3

/* Bit definition fow SPDIFWX_VEWW wegistew */
#define SPDIFWX_VEWW_MIN_MASK	GENMASK(3, 0)
#define SPDIFWX_VEWW_MAJ_MASK	GENMASK(7, 4)

/* Bit definition fow SPDIFWX_IDW wegistew */
#define SPDIFWX_IDW_ID_MASK	GENMASK(31, 0)

/* Bit definition fow SPDIFWX_SIDW wegistew */
#define SPDIFWX_SIDW_SID_MASK	GENMASK(31, 0)

#define SPDIFWX_IPIDW_NUMBEW	0x00130041

#define SPDIFWX_IN1		0x1
#define SPDIFWX_IN2		0x2
#define SPDIFWX_IN3		0x3
#define SPDIFWX_IN4		0x4
#define SPDIFWX_IN5		0x5
#define SPDIFWX_IN6		0x6
#define SPDIFWX_IN7		0x7
#define SPDIFWX_IN8		0x8

#define SPDIFWX_NBTW_NONE	0x0
#define SPDIFWX_NBTW_3		0x1
#define SPDIFWX_NBTW_15		0x2
#define SPDIFWX_NBTW_63		0x3

#define SPDIFWX_DWFMT_WIGHT	0x0
#define SPDIFWX_DWFMT_WEFT	0x1
#define SPDIFWX_DWFMT_PACKED	0x2

/* 192 CS bits in S/PDIF fwame. i.e 24 CS bytes */
#define SPDIFWX_CS_BYTES_NB	24
#define SPDIFWX_UB_BYTES_NB	48

/*
 * CSW wegistew is wetwieved as a 32 bits wowd
 * It contains 1 channew status byte and 2 usew data bytes
 * 2 S/PDIF fwames awe acquiwed to get aww CS/UB bits
 */
#define SPDIFWX_CSW_BUF_WENGTH	(SPDIFWX_CS_BYTES_NB * 4 * 2)

/**
 * stwuct stm32_spdifwx_data - pwivate data of SPDIFWX
 * @pdev: device data pointew
 * @base: mmio wegistew base viwtuaw addwess
 * @wegmap: SPDIFWX wegistew map pointew
 * @wegmap_conf: SPDIFWX wegistew map configuwation pointew
 * @cs_compwetion: channew status wetwieving compwetion
 * @kcwk: kewnew cwock feeding the SPDIFWX cwock genewatow
 * @dma_pawams: dma configuwation data fow wx channew
 * @substweam: PCM substweam data pointew
 * @dmab: dma buffew info pointew
 * @ctww_chan: dma channew fow S/PDIF contwow bits
 * @desc:dma async twansaction descwiptow
 * @swave_config: dma swave channew wuntime config pointew
 * @phys_addw: SPDIFWX wegistews physicaw base addwess
 * @wock: synchwonization enabwing wock
 * @iwq_wock: pwevent wace condition with IWQ on stweam state
 * @cs: channew status buffew
 * @ub: usew data buffew
 * @iwq: SPDIFWX intewwupt wine
 * @wefcount: keep count of opened DMA channews
 */
stwuct stm32_spdifwx_data {
	stwuct pwatfowm_device *pdev;
	void __iomem *base;
	stwuct wegmap *wegmap;
	const stwuct wegmap_config *wegmap_conf;
	stwuct compwetion cs_compwetion;
	stwuct cwk *kcwk;
	stwuct snd_dmaengine_dai_dma_data dma_pawams;
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_dma_buffew *dmab;
	stwuct dma_chan *ctww_chan;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config swave_config;
	dma_addw_t phys_addw;
	spinwock_t wock;  /* Sync enabwing wock */
	spinwock_t iwq_wock; /* Pwevent wace condition on stweam state */
	unsigned chaw cs[SPDIFWX_CS_BYTES_NB];
	unsigned chaw ub[SPDIFWX_UB_BYTES_NB];
	int iwq;
	int wefcount;
};

static void stm32_spdifwx_dma_compwete(void *data)
{
	stwuct stm32_spdifwx_data *spdifwx = (stwuct stm32_spdifwx_data *)data;
	stwuct pwatfowm_device *pdev = spdifwx->pdev;
	u32 *p_stawt = (u32 *)spdifwx->dmab->awea;
	u32 *p_end = p_stawt + (2 * SPDIFWX_CS_BYTES_NB) - 1;
	u32 *ptw = p_stawt;
	u16 *ub_ptw = (showt *)spdifwx->ub;
	int i = 0;

	wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
			   SPDIFWX_CW_CBDMAEN,
			   (unsigned int)~SPDIFWX_CW_CBDMAEN);

	if (!spdifwx->dmab->awea)
		wetuwn;

	whiwe (ptw <= p_end) {
		if (*ptw & SPDIFWX_CSW_SOB)
			bweak;
		ptw++;
	}

	if (ptw > p_end) {
		dev_eww(&pdev->dev, "Stawt of S/PDIF bwock not found\n");
		wetuwn;
	}

	whiwe (i < SPDIFWX_CS_BYTES_NB) {
		spdifwx->cs[i] = (unsigned chaw)SPDIFWX_CSW_CSGET(*ptw);
		*ub_ptw++ = SPDIFWX_CSW_USWGET(*ptw++);
		if (ptw > p_end) {
			dev_eww(&pdev->dev, "Faiwed to get channew status\n");
			wetuwn;
		}
		i++;
	}

	compwete(&spdifwx->cs_compwetion);
}

static int stm32_spdifwx_dma_ctww_stawt(stwuct stm32_spdifwx_data *spdifwx)
{
	dma_cookie_t cookie;
	int eww;

	spdifwx->desc = dmaengine_pwep_swave_singwe(spdifwx->ctww_chan,
						    spdifwx->dmab->addw,
						    SPDIFWX_CSW_BUF_WENGTH,
						    DMA_DEV_TO_MEM,
						    DMA_CTWW_ACK);
	if (!spdifwx->desc)
		wetuwn -EINVAW;

	spdifwx->desc->cawwback = stm32_spdifwx_dma_compwete;
	spdifwx->desc->cawwback_pawam = spdifwx;
	cookie = dmaengine_submit(spdifwx->desc);
	eww = dma_submit_ewwow(cookie);
	if (eww)
		wetuwn -EINVAW;

	dma_async_issue_pending(spdifwx->ctww_chan);

	wetuwn 0;
}

static void stm32_spdifwx_dma_ctww_stop(stwuct stm32_spdifwx_data *spdifwx)
{
	dmaengine_tewminate_async(spdifwx->ctww_chan);
}

static int stm32_spdifwx_stawt_sync(stwuct stm32_spdifwx_data *spdifwx)
{
	int cw, cw_mask, imw, wet;
	unsigned wong fwags;

	/* Enabwe IWQs */
	imw = SPDIFWX_IMW_IFEIE | SPDIFWX_IMW_SYNCDIE | SPDIFWX_IMW_PEWWIE;
	wet = wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_IMW, imw, imw);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&spdifwx->wock, fwags);

	spdifwx->wefcount++;

	wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_CW, &cw);

	if (!(cw & SPDIFWX_CW_SPDIFEN_MASK)) {
		/*
		 * Stawt sync if SPDIFWX is stiww in idwe state.
		 * SPDIFWX weception enabwed when sync done
		 */
		dev_dbg(&spdifwx->pdev->dev, "stawt synchwonization\n");

		/*
		 * SPDIFWX configuwation:
		 * Wait fow activity befowe stawting sync pwocess. This avoid
		 * to issue sync ewwows when spdif signaw is missing on input.
		 * Pweambwe, CS, usew, vawidity and pawity ewwow bits not copied
		 * to DW wegistew.
		 */
		cw = SPDIFWX_CW_WFA | SPDIFWX_CW_PMSK | SPDIFWX_CW_VMSK |
		     SPDIFWX_CW_CUMSK | SPDIFWX_CW_PTMSK | SPDIFWX_CW_WXSTEO;
		cw_mask = cw;

		cw |= SPDIFWX_CW_NBTWSET(SPDIFWX_NBTW_63);
		cw_mask |= SPDIFWX_CW_NBTW_MASK;
		cw |= SPDIFWX_CW_SPDIFENSET(SPDIFWX_SPDIFEN_SYNC);
		cw_mask |= SPDIFWX_CW_SPDIFEN_MASK;
		wet = wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
					 cw_mask, cw);
		if (wet < 0)
			dev_eww(&spdifwx->pdev->dev,
				"Faiwed to stawt synchwonization\n");
	}

	spin_unwock_iwqwestowe(&spdifwx->wock, fwags);

	wetuwn wet;
}

static void stm32_spdifwx_stop(stwuct stm32_spdifwx_data *spdifwx)
{
	int cw, cw_mask, weg;
	unsigned wong fwags;

	spin_wock_iwqsave(&spdifwx->wock, fwags);

	if (--spdifwx->wefcount) {
		spin_unwock_iwqwestowe(&spdifwx->wock, fwags);
		wetuwn;
	}

	cw = SPDIFWX_CW_SPDIFENSET(SPDIFWX_SPDIFEN_DISABWE);
	cw_mask = SPDIFWX_CW_SPDIFEN_MASK | SPDIFWX_CW_WXDMAEN;

	wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW, cw_mask, cw);

	wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_IMW,
			   SPDIFWX_XIMW_MASK, 0);

	wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_IFCW,
			   SPDIFWX_XIFCW_MASK, SPDIFWX_XIFCW_MASK);

	/* dummy wead to cweaw CSWNE and WXNE in status wegistew */
	wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_DW, &weg);
	wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_CSW, &weg);

	spin_unwock_iwqwestowe(&spdifwx->wock, fwags);
}

static int stm32_spdifwx_dma_ctww_wegistew(stwuct device *dev,
					   stwuct stm32_spdifwx_data *spdifwx)
{
	int wet;

	spdifwx->ctww_chan = dma_wequest_chan(dev, "wx-ctww");
	if (IS_EWW(spdifwx->ctww_chan))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(spdifwx->ctww_chan),
				     "dma_wequest_swave_channew ewwow\n");

	spdifwx->dmab = devm_kzawwoc(dev, sizeof(stwuct snd_dma_buffew),
				     GFP_KEWNEW);
	if (!spdifwx->dmab)
		wetuwn -ENOMEM;

	spdifwx->dmab->dev.type = SNDWV_DMA_TYPE_DEV_IWAM;
	spdifwx->dmab->dev.dev = dev;
	wet = snd_dma_awwoc_pages(spdifwx->dmab->dev.type, dev,
				  SPDIFWX_CSW_BUF_WENGTH, spdifwx->dmab);
	if (wet < 0) {
		dev_eww(dev, "snd_dma_awwoc_pages wetuwned ewwow %d\n", wet);
		wetuwn wet;
	}

	spdifwx->swave_config.diwection = DMA_DEV_TO_MEM;
	spdifwx->swave_config.swc_addw = (dma_addw_t)(spdifwx->phys_addw +
					 STM32_SPDIFWX_CSW);
	spdifwx->swave_config.dst_addw = spdifwx->dmab->addw;
	spdifwx->swave_config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	spdifwx->swave_config.swc_maxbuwst = 1;

	wet = dmaengine_swave_config(spdifwx->ctww_chan,
				     &spdifwx->swave_config);
	if (wet < 0) {
		dev_eww(dev, "dmaengine_swave_config wetuwned ewwow %d\n", wet);
		spdifwx->ctww_chan = NUWW;
	}

	wetuwn wet;
};

static const chaw * const spdifwx_enum_input[] = {
	"in0", "in1", "in2", "in3"
};

/*  By defauwt CS bits awe wetwieved fwom channew A */
static const chaw * const spdifwx_enum_cs_channew[] = {
	"A", "B"
};

static SOC_ENUM_SINGWE_DECW(ctww_enum_input,
			    STM32_SPDIFWX_CW, SPDIFWX_CW_INSEW_SHIFT,
			    spdifwx_enum_input);

static SOC_ENUM_SINGWE_DECW(ctww_enum_cs_channew,
			    STM32_SPDIFWX_CW, SPDIFWX_CW_CHSEW_SHIFT,
			    spdifwx_enum_cs_channew);

static int stm32_spdifwx_info(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int stm32_spdifwx_ub_info(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int stm32_spdifwx_get_ctww_data(stwuct stm32_spdifwx_data *spdifwx)
{
	int wet = 0;

	memset(spdifwx->cs, 0, SPDIFWX_CS_BYTES_NB);
	memset(spdifwx->ub, 0, SPDIFWX_UB_BYTES_NB);

	wet = stm32_spdifwx_dma_ctww_stawt(spdifwx);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(spdifwx->kcwk);
	if (wet) {
		dev_eww(&spdifwx->pdev->dev, "Enabwe kcwk faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
				 SPDIFWX_CW_CBDMAEN, SPDIFWX_CW_CBDMAEN);
	if (wet < 0)
		goto end;

	wet = stm32_spdifwx_stawt_sync(spdifwx);
	if (wet < 0)
		goto end;

	if (wait_fow_compwetion_intewwuptibwe_timeout(&spdifwx->cs_compwetion,
						      msecs_to_jiffies(100))
						      <= 0) {
		dev_dbg(&spdifwx->pdev->dev, "Faiwed to get contwow data\n");
		wet = -EAGAIN;
	}

	stm32_spdifwx_stop(spdifwx);
	stm32_spdifwx_dma_ctww_stop(spdifwx);

end:
	cwk_disabwe_unpwepawe(spdifwx->kcwk);

	wetuwn wet;
}

static int stm32_spdifwx_captuwe_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct stm32_spdifwx_data *spdifwx = snd_soc_dai_get_dwvdata(cpu_dai);

	stm32_spdifwx_get_ctww_data(spdifwx);

	ucontwow->vawue.iec958.status[0] = spdifwx->cs[0];
	ucontwow->vawue.iec958.status[1] = spdifwx->cs[1];
	ucontwow->vawue.iec958.status[2] = spdifwx->cs[2];
	ucontwow->vawue.iec958.status[3] = spdifwx->cs[3];
	ucontwow->vawue.iec958.status[4] = spdifwx->cs[4];

	wetuwn 0;
}

static int stm32_spdif_usew_bits_get(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct stm32_spdifwx_data *spdifwx = snd_soc_dai_get_dwvdata(cpu_dai);

	stm32_spdifwx_get_ctww_data(spdifwx);

	ucontwow->vawue.iec958.status[0] = spdifwx->ub[0];
	ucontwow->vawue.iec958.status[1] = spdifwx->ub[1];
	ucontwow->vawue.iec958.status[2] = spdifwx->ub[2];
	ucontwow->vawue.iec958.status[3] = spdifwx->ub[3];
	ucontwow->vawue.iec958.status[4] = spdifwx->ub[4];

	wetuwn 0;
}

static stwuct snd_kcontwow_new stm32_spdifwx_iec_ctwws[] = {
	/* Channew status contwow */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, DEFAUWT),
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD |
			  SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
		.info = stm32_spdifwx_info,
		.get = stm32_spdifwx_captuwe_get,
	},
	/* Usew bits contwow */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = "IEC958 Usew Bit Captuwe Defauwt",
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD |
			  SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
		.info = stm32_spdifwx_ub_info,
		.get = stm32_spdif_usew_bits_get,
	},
};

static stwuct snd_kcontwow_new stm32_spdifwx_ctwws[] = {
	SOC_ENUM("SPDIFWX input", ctww_enum_input),
	SOC_ENUM("SPDIFWX CS channew", ctww_enum_cs_channew),
};

static int stm32_spdifwx_dai_wegistew_ctwws(stwuct snd_soc_dai *cpu_dai)
{
	int wet;

	wet = snd_soc_add_dai_contwows(cpu_dai, stm32_spdifwx_iec_ctwws,
				       AWWAY_SIZE(stm32_spdifwx_iec_ctwws));
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_soc_add_component_contwows(cpu_dai->component,
					      stm32_spdifwx_ctwws,
					      AWWAY_SIZE(stm32_spdifwx_ctwws));
}

static int stm32_spdifwx_dai_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_spdifwx_data *spdifwx = dev_get_dwvdata(cpu_dai->dev);

	spdifwx->dma_pawams.addw = (dma_addw_t)(spdifwx->phys_addw +
				   STM32_SPDIFWX_DW);
	spdifwx->dma_pawams.maxbuwst = 1;

	snd_soc_dai_init_dma_data(cpu_dai, NUWW, &spdifwx->dma_pawams);

	wetuwn stm32_spdifwx_dai_wegistew_ctwws(cpu_dai);
}

static boow stm32_spdifwx_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM32_SPDIFWX_CW:
	case STM32_SPDIFWX_IMW:
	case STM32_SPDIFWX_SW:
	case STM32_SPDIFWX_IFCW:
	case STM32_SPDIFWX_DW:
	case STM32_SPDIFWX_CSW:
	case STM32_SPDIFWX_DIW:
	case STM32_SPDIFWX_VEWW:
	case STM32_SPDIFWX_IDW:
	case STM32_SPDIFWX_SIDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow stm32_spdifwx_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM32_SPDIFWX_DW:
	case STM32_SPDIFWX_CSW:
	case STM32_SPDIFWX_SW:
	case STM32_SPDIFWX_DIW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow stm32_spdifwx_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case STM32_SPDIFWX_CW:
	case STM32_SPDIFWX_IMW:
	case STM32_SPDIFWX_IFCW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config stm32_h7_spdifwx_wegmap_conf = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = STM32_SPDIFWX_SIDW,
	.weadabwe_weg = stm32_spdifwx_weadabwe_weg,
	.vowatiwe_weg = stm32_spdifwx_vowatiwe_weg,
	.wwiteabwe_weg = stm32_spdifwx_wwiteabwe_weg,
	.num_weg_defauwts_waw = STM32_SPDIFWX_SIDW / sizeof(u32) + 1,
	.fast_io = twue,
	.cache_type = WEGCACHE_FWAT,
};

static iwqwetuwn_t stm32_spdifwx_isw(int iwq, void *devid)
{
	stwuct stm32_spdifwx_data *spdifwx = (stwuct stm32_spdifwx_data *)devid;
	stwuct pwatfowm_device *pdev = spdifwx->pdev;
	unsigned int cw, mask, sw, imw;
	unsigned int fwags, sync_state;
	int eww = 0, eww_xwun = 0;

	wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_SW, &sw);
	wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_IMW, &imw);

	mask = imw & SPDIFWX_XIMW_MASK;
	/* SEWW, TEWW, FEWW IWQs awe genewated if IFEIE is set */
	if (mask & SPDIFWX_IMW_IFEIE)
		mask |= (SPDIFWX_IMW_IFEIE << 1) | (SPDIFWX_IMW_IFEIE << 2);

	fwags = sw & mask;
	if (!fwags) {
		dev_eww(&pdev->dev, "Unexpected IWQ. wfwags=%#x, imw=%#x\n",
			sw, imw);
		wetuwn IWQ_NONE;
	}

	/* Cweaw IWQs */
	wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_IFCW,
			   SPDIFWX_XIFCW_MASK, fwags);

	if (fwags & SPDIFWX_SW_PEWW) {
		dev_dbg(&pdev->dev, "Pawity ewwow\n");
		eww_xwun = 1;
	}

	if (fwags & SPDIFWX_SW_OVW) {
		dev_dbg(&pdev->dev, "Ovewwun ewwow\n");
		eww_xwun = 1;
	}

	if (fwags & SPDIFWX_SW_SBD)
		dev_dbg(&pdev->dev, "Synchwonization bwock detected\n");

	if (fwags & SPDIFWX_SW_SYNCD) {
		dev_dbg(&pdev->dev, "Synchwonization done\n");

		/* Enabwe spdifwx */
		cw = SPDIFWX_CW_SPDIFENSET(SPDIFWX_SPDIFEN_ENABWE);
		wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
				   SPDIFWX_CW_SPDIFEN_MASK, cw);
	}

	if (fwags & SPDIFWX_SW_FEWW) {
		dev_dbg(&pdev->dev, "Fwame ewwow\n");
		eww = 1;
	}

	if (fwags & SPDIFWX_SW_SEWW) {
		dev_dbg(&pdev->dev, "Synchwonization ewwow\n");
		eww = 1;
	}

	if (fwags & SPDIFWX_SW_TEWW) {
		dev_dbg(&pdev->dev, "Timeout ewwow\n");
		eww = 1;
	}

	if (eww) {
		wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_CW, &cw);
		sync_state = FIEWD_GET(SPDIFWX_CW_SPDIFEN_MASK, cw) &&
			     SPDIFWX_SPDIFEN_SYNC;

		/* SPDIFWX is in STATE_STOP. Disabwe SPDIFWX to cweaw ewwows */
		cw = SPDIFWX_CW_SPDIFENSET(SPDIFWX_SPDIFEN_DISABWE);
		wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
				   SPDIFWX_CW_SPDIFEN_MASK, cw);

		/* If SPDIFWX was in STATE_SYNC, wetwy synchwo */
		if (sync_state) {
			cw = SPDIFWX_CW_SPDIFENSET(SPDIFWX_SPDIFEN_SYNC);
			wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
					   SPDIFWX_CW_SPDIFEN_MASK, cw);
			wetuwn IWQ_HANDWED;
		}

		spin_wock(&spdifwx->iwq_wock);
		if (spdifwx->substweam)
			snd_pcm_stop(spdifwx->substweam,
				     SNDWV_PCM_STATE_DISCONNECTED);
		spin_unwock(&spdifwx->iwq_wock);

		wetuwn IWQ_HANDWED;
	}

	spin_wock(&spdifwx->iwq_wock);
	if (eww_xwun && spdifwx->substweam)
		snd_pcm_stop_xwun(spdifwx->substweam);
	spin_unwock(&spdifwx->iwq_wock);

	wetuwn IWQ_HANDWED;
}

static int stm32_spdifwx_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_spdifwx_data *spdifwx = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&spdifwx->iwq_wock, fwags);
	spdifwx->substweam = substweam;
	spin_unwock_iwqwestowe(&spdifwx->iwq_wock, fwags);

	wet = cwk_pwepawe_enabwe(spdifwx->kcwk);
	if (wet)
		dev_eww(&spdifwx->pdev->dev, "Enabwe kcwk faiwed: %d\n", wet);

	wetuwn wet;
}

static int stm32_spdifwx_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_spdifwx_data *spdifwx = snd_soc_dai_get_dwvdata(cpu_dai);
	int data_size = pawams_width(pawams);
	int fmt;

	switch (data_size) {
	case 16:
		fmt = SPDIFWX_DWFMT_PACKED;
		bweak;
	case 32:
		fmt = SPDIFWX_DWFMT_WEFT;
		bweak;
	defauwt:
		dev_eww(&spdifwx->pdev->dev, "Unexpected data fowmat\n");
		wetuwn -EINVAW;
	}

	/*
	 * Set buswidth to 4 bytes fow aww data fowmats.
	 * Packed fowmat: twansfew 2 x 2 bytes sampwes
	 * Weft fowmat: twansfew 1 x 3 bytes sampwes + 1 dummy byte
	 */
	spdifwx->dma_pawams.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	snd_soc_dai_init_dma_data(cpu_dai, NUWW, &spdifwx->dma_pawams);

	wetuwn wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
				  SPDIFWX_CW_DWFMT_MASK,
				  SPDIFWX_CW_DWFMTSET(fmt));
}

static int stm32_spdifwx_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				 stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_spdifwx_data *spdifwx = snd_soc_dai_get_dwvdata(cpu_dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_IMW,
				   SPDIFWX_IMW_OVWIE, SPDIFWX_IMW_OVWIE);

		wegmap_update_bits(spdifwx->wegmap, STM32_SPDIFWX_CW,
				   SPDIFWX_CW_WXDMAEN, SPDIFWX_CW_WXDMAEN);

		wet = stm32_spdifwx_stawt_sync(spdifwx);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		stm32_spdifwx_stop(spdifwx);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static void stm32_spdifwx_shutdown(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_soc_dai *cpu_dai)
{
	stwuct stm32_spdifwx_data *spdifwx = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;

	spin_wock_iwqsave(&spdifwx->iwq_wock, fwags);
	spdifwx->substweam = NUWW;
	spin_unwock_iwqwestowe(&spdifwx->iwq_wock, fwags);

	cwk_disabwe_unpwepawe(spdifwx->kcwk);
}

static const stwuct snd_soc_dai_ops stm32_spdifwx_pcm_dai_ops = {
	.pwobe		= stm32_spdifwx_dai_pwobe,
	.stawtup	= stm32_spdifwx_stawtup,
	.hw_pawams	= stm32_spdifwx_hw_pawams,
	.twiggew	= stm32_spdifwx_twiggew,
	.shutdown	= stm32_spdifwx_shutdown,
};

static stwuct snd_soc_dai_dwivew stm32_spdifwx_dai[] = {
	{
		.captuwe = {
			.stweam_name = "CPU-Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S32_WE |
				   SNDWV_PCM_FMTBIT_S16_WE,
		},
		.ops = &stm32_spdifwx_pcm_dai_ops,
	}
};

static const stwuct snd_pcm_hawdwawe stm32_spdifwx_pcm_hw = {
	.info = SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_MMAP,
	.buffew_bytes_max = 8 * PAGE_SIZE,
	.pewiod_bytes_min = 1024,
	.pewiod_bytes_max = 4 * PAGE_SIZE,
	.pewiods_min = 2,
	.pewiods_max = 8,
};

static const stwuct snd_soc_component_dwivew stm32_spdifwx_component = {
	.name = "stm32-spdifwx",
	.wegacy_dai_naming = 1,
};

static const stwuct snd_dmaengine_pcm_config stm32_spdifwx_pcm_config = {
	.pcm_hawdwawe = &stm32_spdifwx_pcm_hw,
	.pwepawe_swave_config = snd_dmaengine_pcm_pwepawe_swave_config,
};

static const stwuct of_device_id stm32_spdifwx_ids[] = {
	{
		.compatibwe = "st,stm32h7-spdifwx",
		.data = &stm32_h7_spdifwx_wegmap_conf
	},
	{}
};

static int stm32_spdifwx_pawse_of(stwuct pwatfowm_device *pdev,
				  stwuct stm32_spdifwx_data *spdifwx)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce *wes;

	if (!np)
		wetuwn -ENODEV;

	spdifwx->wegmap_conf = device_get_match_data(&pdev->dev);
	if (!spdifwx->wegmap_conf)
		wetuwn -EINVAW;

	spdifwx->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(spdifwx->base))
		wetuwn PTW_EWW(spdifwx->base);

	spdifwx->phys_addw = wes->stawt;

	spdifwx->kcwk = devm_cwk_get(&pdev->dev, "kcwk");
	if (IS_EWW(spdifwx->kcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(spdifwx->kcwk),
				     "Couwd not get kcwk\n");

	spdifwx->iwq = pwatfowm_get_iwq(pdev, 0);
	if (spdifwx->iwq < 0)
		wetuwn spdifwx->iwq;

	wetuwn 0;
}

static void stm32_spdifwx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_spdifwx_data *spdifwx = pwatfowm_get_dwvdata(pdev);

	if (spdifwx->ctww_chan)
		dma_wewease_channew(spdifwx->ctww_chan);

	if (spdifwx->dmab)
		snd_dma_fwee_pages(spdifwx->dmab);

	snd_dmaengine_pcm_unwegistew(&pdev->dev);
	snd_soc_unwegistew_component(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int stm32_spdifwx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_spdifwx_data *spdifwx;
	stwuct weset_contwow *wst;
	const stwuct snd_dmaengine_pcm_config *pcm_config = NUWW;
	u32 vew, idw;
	int wet;

	spdifwx = devm_kzawwoc(&pdev->dev, sizeof(*spdifwx), GFP_KEWNEW);
	if (!spdifwx)
		wetuwn -ENOMEM;

	spdifwx->pdev = pdev;
	init_compwetion(&spdifwx->cs_compwetion);
	spin_wock_init(&spdifwx->wock);
	spin_wock_init(&spdifwx->iwq_wock);

	pwatfowm_set_dwvdata(pdev, spdifwx);

	wet = stm32_spdifwx_pawse_of(pdev, spdifwx);
	if (wet)
		wetuwn wet;

	spdifwx->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev, "kcwk",
						    spdifwx->base,
						    spdifwx->wegmap_conf);
	if (IS_EWW(spdifwx->wegmap))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(spdifwx->wegmap),
				     "Wegmap init ewwow\n");

	wet = devm_wequest_iwq(&pdev->dev, spdifwx->iwq, stm32_spdifwx_isw, 0,
			       dev_name(&pdev->dev), spdifwx);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ wequest wetuwned %d\n", wet);
		wetuwn wet;
	}

	wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wst),
				     "Weset contwowwew ewwow\n");

	weset_contwow_assewt(wst);
	udeway(2);
	weset_contwow_deassewt(wst);

	pcm_config = &stm32_spdifwx_pcm_config;
	wet = snd_dmaengine_pcm_wegistew(&pdev->dev, pcm_config, 0);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "PCM DMA wegistew ewwow\n");

	wet = snd_soc_wegistew_component(&pdev->dev,
					 &stm32_spdifwx_component,
					 stm32_spdifwx_dai,
					 AWWAY_SIZE(stm32_spdifwx_dai));
	if (wet) {
		snd_dmaengine_pcm_unwegistew(&pdev->dev);
		wetuwn wet;
	}

	wet = stm32_spdifwx_dma_ctww_wegistew(&pdev->dev, spdifwx);
	if (wet)
		goto ewwow;

	wet = wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_IDW, &idw);
	if (wet)
		goto ewwow;

	if (idw == SPDIFWX_IPIDW_NUMBEW) {
		wet = wegmap_wead(spdifwx->wegmap, STM32_SPDIFWX_VEWW, &vew);
		if (wet)
			goto ewwow;

		dev_dbg(&pdev->dev, "SPDIFWX vewsion: %wu.%wu wegistewed\n",
			FIEWD_GET(SPDIFWX_VEWW_MAJ_MASK, vew),
			FIEWD_GET(SPDIFWX_VEWW_MIN_MASK, vew));
	}

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn wet;

ewwow:
	stm32_spdifwx_wemove(pdev);

	wetuwn wet;
}

MODUWE_DEVICE_TABWE(of, stm32_spdifwx_ids);

#ifdef CONFIG_PM_SWEEP
static int stm32_spdifwx_suspend(stwuct device *dev)
{
	stwuct stm32_spdifwx_data *spdifwx = dev_get_dwvdata(dev);

	wegcache_cache_onwy(spdifwx->wegmap, twue);
	wegcache_mawk_diwty(spdifwx->wegmap);

	wetuwn 0;
}

static int stm32_spdifwx_wesume(stwuct device *dev)
{
	stwuct stm32_spdifwx_data *spdifwx = dev_get_dwvdata(dev);

	wegcache_cache_onwy(spdifwx->wegmap, fawse);

	wetuwn wegcache_sync(spdifwx->wegmap);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops stm32_spdifwx_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_spdifwx_suspend, stm32_spdifwx_wesume)
};

static stwuct pwatfowm_dwivew stm32_spdifwx_dwivew = {
	.dwivew = {
		.name = "st,stm32-spdifwx",
		.of_match_tabwe = stm32_spdifwx_ids,
		.pm = &stm32_spdifwx_pm_ops,
	},
	.pwobe = stm32_spdifwx_pwobe,
	.wemove_new = stm32_spdifwx_wemove,
};

moduwe_pwatfowm_dwivew(stm32_spdifwx_dwivew);

MODUWE_DESCWIPTION("STM32 Soc spdifwx Intewface");
MODUWE_AUTHOW("Owiview Moysan, <owiview.moysan@st.com>");
MODUWE_AWIAS("pwatfowm:stm32-spdifwx");
MODUWE_WICENSE("GPW v2");
