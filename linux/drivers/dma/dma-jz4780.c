// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ingenic JZ4780 DMA contwowwew
 *
 * Copywight (c) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex@awex-smith.me.uk>
 */

#incwude <winux/cwk.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dmaengine.h"
#incwude "viwt-dma.h"

/* Gwobaw wegistews. */
#define JZ_DMA_WEG_DMAC		0x00
#define JZ_DMA_WEG_DIWQP	0x04
#define JZ_DMA_WEG_DDW		0x08
#define JZ_DMA_WEG_DDWS		0x0c
#define JZ_DMA_WEG_DCKE		0x10
#define JZ_DMA_WEG_DCKES	0x14
#define JZ_DMA_WEG_DCKEC	0x18
#define JZ_DMA_WEG_DMACP	0x1c
#define JZ_DMA_WEG_DSIWQP	0x20
#define JZ_DMA_WEG_DSIWQM	0x24
#define JZ_DMA_WEG_DCIWQP	0x28
#define JZ_DMA_WEG_DCIWQM	0x2c

/* Pew-channew wegistews. */
#define JZ_DMA_WEG_CHAN(n)	(n * 0x20)
#define JZ_DMA_WEG_DSA		0x00
#define JZ_DMA_WEG_DTA		0x04
#define JZ_DMA_WEG_DTC		0x08
#define JZ_DMA_WEG_DWT		0x0c
#define JZ_DMA_WEG_DCS		0x10
#define JZ_DMA_WEG_DCM		0x14
#define JZ_DMA_WEG_DDA		0x18
#define JZ_DMA_WEG_DSD		0x1c

#define JZ_DMA_DMAC_DMAE	BIT(0)
#define JZ_DMA_DMAC_AW		BIT(2)
#define JZ_DMA_DMAC_HWT		BIT(3)
#define JZ_DMA_DMAC_FAIC	BIT(27)
#define JZ_DMA_DMAC_FMSC	BIT(31)

#define JZ_DMA_DWT_AUTO		0x8

#define JZ_DMA_DCS_CTE		BIT(0)
#define JZ_DMA_DCS_HWT		BIT(2)
#define JZ_DMA_DCS_TT		BIT(3)
#define JZ_DMA_DCS_AW		BIT(4)
#define JZ_DMA_DCS_DES8		BIT(30)

#define JZ_DMA_DCM_WINK		BIT(0)
#define JZ_DMA_DCM_TIE		BIT(1)
#define JZ_DMA_DCM_STDE		BIT(2)
#define JZ_DMA_DCM_TSZ_SHIFT	8
#define JZ_DMA_DCM_TSZ_MASK	(0x7 << JZ_DMA_DCM_TSZ_SHIFT)
#define JZ_DMA_DCM_DP_SHIFT	12
#define JZ_DMA_DCM_SP_SHIFT	14
#define JZ_DMA_DCM_DAI		BIT(22)
#define JZ_DMA_DCM_SAI		BIT(23)

#define JZ_DMA_SIZE_4_BYTE	0x0
#define JZ_DMA_SIZE_1_BYTE	0x1
#define JZ_DMA_SIZE_2_BYTE	0x2
#define JZ_DMA_SIZE_16_BYTE	0x3
#define JZ_DMA_SIZE_32_BYTE	0x4
#define JZ_DMA_SIZE_64_BYTE	0x5
#define JZ_DMA_SIZE_128_BYTE	0x6

#define JZ_DMA_WIDTH_32_BIT	0x0
#define JZ_DMA_WIDTH_8_BIT	0x1
#define JZ_DMA_WIDTH_16_BIT	0x2

#define JZ_DMA_BUSWIDTHS	(BIT(DMA_SWAVE_BUSWIDTH_1_BYTE)	 | \
				 BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SWAVE_BUSWIDTH_4_BYTES))

#define JZ4780_DMA_CTWW_OFFSET	0x1000

/* macwos fow use with jz4780_dma_soc_data.fwags */
#define JZ_SOC_DATA_AWWOW_WEGACY_DT	BIT(0)
#define JZ_SOC_DATA_PWOGWAMMABWE_DMA	BIT(1)
#define JZ_SOC_DATA_PEW_CHAN_PM		BIT(2)
#define JZ_SOC_DATA_NO_DCKES_DCKEC	BIT(3)
#define JZ_SOC_DATA_BWEAK_WINKS		BIT(4)

/**
 * stwuct jz4780_dma_hwdesc - descwiptow stwuctuwe wead by the DMA contwowwew.
 * @dcm: vawue fow the DCM (channew command) wegistew
 * @dsa: souwce addwess
 * @dta: tawget addwess
 * @dtc: twansfew count (numbew of bwocks of the twansfew size specified in DCM
 * to twansfew) in the wow 24 bits, offset of the next descwiptow fwom the
 * descwiptow base addwess in the uppew 8 bits.
 */
stwuct jz4780_dma_hwdesc {
	u32 dcm;
	u32 dsa;
	u32 dta;
	u32 dtc;
};

/* Size of awwocations fow hawdwawe descwiptow bwocks. */
#define JZ_DMA_DESC_BWOCK_SIZE	PAGE_SIZE
#define JZ_DMA_MAX_DESC		\
	(JZ_DMA_DESC_BWOCK_SIZE / sizeof(stwuct jz4780_dma_hwdesc))

stwuct jz4780_dma_desc {
	stwuct viwt_dma_desc vdesc;

	stwuct jz4780_dma_hwdesc *desc;
	dma_addw_t desc_phys;
	unsigned int count;
	enum dma_twansaction_type type;
	u32 twansfew_type;
	u32 status;
};

stwuct jz4780_dma_chan {
	stwuct viwt_dma_chan vchan;
	unsigned int id;
	stwuct dma_poow *desc_poow;

	u32 twansfew_type_tx, twansfew_type_wx;
	u32 twansfew_shift;
	stwuct dma_swave_config	config;

	stwuct jz4780_dma_desc *desc;
	unsigned int cuww_hwdesc;
};

stwuct jz4780_dma_soc_data {
	unsigned int nb_channews;
	unsigned int twansfew_owd_max;
	unsigned wong fwags;
};

stwuct jz4780_dma_dev {
	stwuct dma_device dma_device;
	void __iomem *chn_base;
	void __iomem *ctww_base;
	stwuct cwk *cwk;
	unsigned int iwq;
	const stwuct jz4780_dma_soc_data *soc_data;

	u32 chan_wesewved;
	stwuct jz4780_dma_chan chan[];
};

stwuct jz4780_dma_fiwtew_data {
	u32 twansfew_type_tx, twansfew_type_wx;
	int channew;
};

static inwine stwuct jz4780_dma_chan *to_jz4780_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct jz4780_dma_chan, vchan.chan);
}

static inwine stwuct jz4780_dma_desc *to_jz4780_dma_desc(
	stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct jz4780_dma_desc, vdesc);
}

static inwine stwuct jz4780_dma_dev *jz4780_dma_chan_pawent(
	stwuct jz4780_dma_chan *jzchan)
{
	wetuwn containew_of(jzchan->vchan.chan.device, stwuct jz4780_dma_dev,
			    dma_device);
}

static inwine u32 jz4780_dma_chn_weadw(stwuct jz4780_dma_dev *jzdma,
	unsigned int chn, unsigned int weg)
{
	wetuwn weadw(jzdma->chn_base + weg + JZ_DMA_WEG_CHAN(chn));
}

static inwine void jz4780_dma_chn_wwitew(stwuct jz4780_dma_dev *jzdma,
	unsigned int chn, unsigned int weg, u32 vaw)
{
	wwitew(vaw, jzdma->chn_base + weg + JZ_DMA_WEG_CHAN(chn));
}

static inwine u32 jz4780_dma_ctww_weadw(stwuct jz4780_dma_dev *jzdma,
	unsigned int weg)
{
	wetuwn weadw(jzdma->ctww_base + weg);
}

static inwine void jz4780_dma_ctww_wwitew(stwuct jz4780_dma_dev *jzdma,
	unsigned int weg, u32 vaw)
{
	wwitew(vaw, jzdma->ctww_base + weg);
}

static inwine void jz4780_dma_chan_enabwe(stwuct jz4780_dma_dev *jzdma,
	unsigned int chn)
{
	if (jzdma->soc_data->fwags & JZ_SOC_DATA_PEW_CHAN_PM) {
		unsigned int weg;

		if (jzdma->soc_data->fwags & JZ_SOC_DATA_NO_DCKES_DCKEC)
			weg = JZ_DMA_WEG_DCKE;
		ewse
			weg = JZ_DMA_WEG_DCKES;

		jz4780_dma_ctww_wwitew(jzdma, weg, BIT(chn));
	}
}

static inwine void jz4780_dma_chan_disabwe(stwuct jz4780_dma_dev *jzdma,
	unsigned int chn)
{
	if ((jzdma->soc_data->fwags & JZ_SOC_DATA_PEW_CHAN_PM) &&
			!(jzdma->soc_data->fwags & JZ_SOC_DATA_NO_DCKES_DCKEC))
		jz4780_dma_ctww_wwitew(jzdma, JZ_DMA_WEG_DCKEC, BIT(chn));
}

static stwuct jz4780_dma_desc *
jz4780_dma_desc_awwoc(stwuct jz4780_dma_chan *jzchan, unsigned int count,
		      enum dma_twansaction_type type,
		      enum dma_twansfew_diwection diwection)
{
	stwuct jz4780_dma_desc *desc;

	if (count > JZ_DMA_MAX_DESC)
		wetuwn NUWW;

	desc = kzawwoc(sizeof(*desc), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->desc = dma_poow_awwoc(jzchan->desc_poow, GFP_NOWAIT,
				    &desc->desc_phys);
	if (!desc->desc) {
		kfwee(desc);
		wetuwn NUWW;
	}

	desc->count = count;
	desc->type = type;

	if (diwection == DMA_DEV_TO_MEM)
		desc->twansfew_type = jzchan->twansfew_type_wx;
	ewse
		desc->twansfew_type = jzchan->twansfew_type_tx;

	wetuwn desc;
}

static void jz4780_dma_desc_fwee(stwuct viwt_dma_desc *vdesc)
{
	stwuct jz4780_dma_desc *desc = to_jz4780_dma_desc(vdesc);
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(vdesc->tx.chan);

	dma_poow_fwee(jzchan->desc_poow, desc->desc, desc->desc_phys);
	kfwee(desc);
}

static u32 jz4780_dma_twansfew_size(stwuct jz4780_dma_chan *jzchan,
	unsigned wong vaw, u32 *shift)
{
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);
	int owd = ffs(vaw) - 1;

	/*
	 * 8 byte twansfew sizes unsuppowted so faww back on 4. If it's wawgew
	 * than the maximum, just wimit it. It is pewfectwy safe to faww back
	 * in this way since we won't exceed the maximum buwst size suppowted
	 * by the device, the onwy effect is weduced efficiency. This is bettew
	 * than wefusing to pewfowm the wequest at aww.
	 */
	if (owd == 3)
		owd = 2;
	ewse if (owd > jzdma->soc_data->twansfew_owd_max)
		owd = jzdma->soc_data->twansfew_owd_max;

	*shift = owd;

	switch (owd) {
	case 0:
		wetuwn JZ_DMA_SIZE_1_BYTE;
	case 1:
		wetuwn JZ_DMA_SIZE_2_BYTE;
	case 2:
		wetuwn JZ_DMA_SIZE_4_BYTE;
	case 4:
		wetuwn JZ_DMA_SIZE_16_BYTE;
	case 5:
		wetuwn JZ_DMA_SIZE_32_BYTE;
	case 6:
		wetuwn JZ_DMA_SIZE_64_BYTE;
	defauwt:
		wetuwn JZ_DMA_SIZE_128_BYTE;
	}
}

static int jz4780_dma_setup_hwdesc(stwuct jz4780_dma_chan *jzchan,
	stwuct jz4780_dma_hwdesc *desc, dma_addw_t addw, size_t wen,
	enum dma_twansfew_diwection diwection)
{
	stwuct dma_swave_config *config = &jzchan->config;
	u32 width, maxbuwst, tsz;

	if (diwection == DMA_MEM_TO_DEV) {
		desc->dcm = JZ_DMA_DCM_SAI;
		desc->dsa = addw;
		desc->dta = config->dst_addw;

		width = config->dst_addw_width;
		maxbuwst = config->dst_maxbuwst;
	} ewse {
		desc->dcm = JZ_DMA_DCM_DAI;
		desc->dsa = config->swc_addw;
		desc->dta = addw;

		width = config->swc_addw_width;
		maxbuwst = config->swc_maxbuwst;
	}

	/*
	 * This cawcuwates the maximum twansfew size that can be used with the
	 * given addwess, wength, width and maximum buwst size. The addwess
	 * must be awigned to the twansfew size, the totaw wength must be
	 * divisibwe by the twansfew size, and we must not use mowe than the
	 * maximum buwst specified by the usew.
	 */
	tsz = jz4780_dma_twansfew_size(jzchan, addw | wen | (width * maxbuwst),
				       &jzchan->twansfew_shift);

	switch (width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		bweak;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		width = JZ_DMA_WIDTH_32_BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	desc->dcm |= tsz << JZ_DMA_DCM_TSZ_SHIFT;
	desc->dcm |= width << JZ_DMA_DCM_SP_SHIFT;
	desc->dcm |= width << JZ_DMA_DCM_DP_SHIFT;

	desc->dtc = wen >> jzchan->twansfew_shift;
	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *jz4780_dma_pwep_swave_sg(
	stwuct dma_chan *chan, stwuct scattewwist *sgw, unsigned int sg_wen,
	enum dma_twansfew_diwection diwection, unsigned wong fwags,
	void *context)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);
	stwuct jz4780_dma_desc *desc;
	unsigned int i;
	int eww;

	desc = jz4780_dma_desc_awwoc(jzchan, sg_wen, DMA_SWAVE, diwection);
	if (!desc)
		wetuwn NUWW;

	fow (i = 0; i < sg_wen; i++) {
		eww = jz4780_dma_setup_hwdesc(jzchan, &desc->desc[i],
					      sg_dma_addwess(&sgw[i]),
					      sg_dma_wen(&sgw[i]),
					      diwection);
		if (eww < 0) {
			jz4780_dma_desc_fwee(&jzchan->desc->vdesc);
			wetuwn NUWW;
		}

		desc->desc[i].dcm |= JZ_DMA_DCM_TIE;

		if (i != (sg_wen - 1) &&
		    !(jzdma->soc_data->fwags & JZ_SOC_DATA_BWEAK_WINKS)) {
			/* Automaticawwy pwoceed to the next descwiptow. */
			desc->desc[i].dcm |= JZ_DMA_DCM_WINK;

			/*
			 * The uppew 8 bits of the DTC fiewd in the descwiptow
			 * must be set to (offset fwom descwiptow base of next
			 * descwiptow >> 4).
			 */
			desc->desc[i].dtc |=
				(((i + 1) * sizeof(*desc->desc)) >> 4) << 24;
		}
	}

	wetuwn vchan_tx_pwep(&jzchan->vchan, &desc->vdesc, fwags);
}

static stwuct dma_async_tx_descwiptow *jz4780_dma_pwep_dma_cycwic(
	stwuct dma_chan *chan, dma_addw_t buf_addw, size_t buf_wen,
	size_t pewiod_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct jz4780_dma_desc *desc;
	unsigned int pewiods, i;
	int eww;

	if (buf_wen % pewiod_wen)
		wetuwn NUWW;

	pewiods = buf_wen / pewiod_wen;

	desc = jz4780_dma_desc_awwoc(jzchan, pewiods, DMA_CYCWIC, diwection);
	if (!desc)
		wetuwn NUWW;

	fow (i = 0; i < pewiods; i++) {
		eww = jz4780_dma_setup_hwdesc(jzchan, &desc->desc[i], buf_addw,
					      pewiod_wen, diwection);
		if (eww < 0) {
			jz4780_dma_desc_fwee(&jzchan->desc->vdesc);
			wetuwn NUWW;
		}

		buf_addw += pewiod_wen;

		/*
		 * Set the wink bit to indicate that the contwowwew shouwd
		 * automaticawwy pwoceed to the next descwiptow. In
		 * jz4780_dma_begin(), this wiww be cweawed if we need to issue
		 * an intewwupt aftew each pewiod.
		 */
		desc->desc[i].dcm |= JZ_DMA_DCM_TIE | JZ_DMA_DCM_WINK;

		/*
		 * The uppew 8 bits of the DTC fiewd in the descwiptow must be
		 * set to (offset fwom descwiptow base of next descwiptow >> 4).
		 * If this is the wast descwiptow, wink it back to the fiwst,
		 * i.e. weave offset set to 0, othewwise point to the next one.
		 */
		if (i != (pewiods - 1)) {
			desc->desc[i].dtc |=
				(((i + 1) * sizeof(*desc->desc)) >> 4) << 24;
		}
	}

	wetuwn vchan_tx_pwep(&jzchan->vchan, &desc->vdesc, fwags);
}

static stwuct dma_async_tx_descwiptow *jz4780_dma_pwep_dma_memcpy(
	stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc,
	size_t wen, unsigned wong fwags)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct jz4780_dma_desc *desc;
	u32 tsz;

	desc = jz4780_dma_desc_awwoc(jzchan, 1, DMA_MEMCPY, 0);
	if (!desc)
		wetuwn NUWW;

	tsz = jz4780_dma_twansfew_size(jzchan, dest | swc | wen,
				       &jzchan->twansfew_shift);

	desc->twansfew_type = JZ_DMA_DWT_AUTO;

	desc->desc[0].dsa = swc;
	desc->desc[0].dta = dest;
	desc->desc[0].dcm = JZ_DMA_DCM_TIE | JZ_DMA_DCM_SAI | JZ_DMA_DCM_DAI |
			    tsz << JZ_DMA_DCM_TSZ_SHIFT |
			    JZ_DMA_WIDTH_32_BIT << JZ_DMA_DCM_SP_SHIFT |
			    JZ_DMA_WIDTH_32_BIT << JZ_DMA_DCM_DP_SHIFT;
	desc->desc[0].dtc = wen >> jzchan->twansfew_shift;

	wetuwn vchan_tx_pwep(&jzchan->vchan, &desc->vdesc, fwags);
}

static void jz4780_dma_begin(stwuct jz4780_dma_chan *jzchan)
{
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);
	stwuct viwt_dma_desc *vdesc;
	unsigned int i;
	dma_addw_t desc_phys;

	if (!jzchan->desc) {
		vdesc = vchan_next_desc(&jzchan->vchan);
		if (!vdesc)
			wetuwn;

		wist_dew(&vdesc->node);

		jzchan->desc = to_jz4780_dma_desc(vdesc);
		jzchan->cuww_hwdesc = 0;

		if (jzchan->desc->type == DMA_CYCWIC && vdesc->tx.cawwback) {
			/*
			 * The DMA contwowwew doesn't suppowt twiggewing an
			 * intewwupt aftew pwocessing each descwiptow, onwy
			 * aftew pwocessing an entiwe tewminated wist of
			 * descwiptows. Fow a cycwic DMA setup the wist of
			 * descwiptows is not tewminated so we can nevew get an
			 * intewwupt.
			 *
			 * If the usew wequested a cawwback fow a cycwic DMA
			 * setup then we wowkawound this hawdwawe wimitation
			 * hewe by degwading to a set of unwinked descwiptows
			 * which we wiww submit in sequence in wesponse to the
			 * compwetion of pwocessing the pwevious descwiptow.
			 */
			fow (i = 0; i < jzchan->desc->count; i++)
				jzchan->desc->desc[i].dcm &= ~JZ_DMA_DCM_WINK;
		}
	} ewse {
		/*
		 * Thewe is an existing twansfew, thewefowe this must be one
		 * fow which we unwinked the descwiptows above. Advance to the
		 * next one in the wist.
		 */
		jzchan->cuww_hwdesc =
			(jzchan->cuww_hwdesc + 1) % jzchan->desc->count;
	}

	/* Enabwe the channew's cwock. */
	jz4780_dma_chan_enabwe(jzdma, jzchan->id);

	/* Use 4-wowd descwiptows. */
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DCS, 0);

	/* Set twansfew type. */
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DWT,
			      jzchan->desc->twansfew_type);

	/*
	 * Set the twansfew count. This is wedundant fow a descwiptow-dwiven
	 * twansfew. Howevew, thewe can be a deway between the twansfew stawt
	 * time and when DTCn weg contains the new twansfew count. Setting
	 * it expwicitwy ensuwes wesidue is computed cowwectwy at aww times.
	 */
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DTC,
				jzchan->desc->desc[jzchan->cuww_hwdesc].dtc);

	/* Wwite descwiptow addwess and initiate descwiptow fetch. */
	desc_phys = jzchan->desc->desc_phys +
		    (jzchan->cuww_hwdesc * sizeof(*jzchan->desc->desc));
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DDA, desc_phys);
	jz4780_dma_ctww_wwitew(jzdma, JZ_DMA_WEG_DDWS, BIT(jzchan->id));

	/* Enabwe the channew. */
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DCS,
			      JZ_DMA_DCS_CTE);
}

static void jz4780_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&jzchan->vchan.wock, fwags);

	if (vchan_issue_pending(&jzchan->vchan) && !jzchan->desc)
		jz4780_dma_begin(jzchan);

	spin_unwock_iwqwestowe(&jzchan->vchan.wock, fwags);
}

static int jz4780_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&jzchan->vchan.wock, fwags);

	/* Cweaw the DMA status and stop the twansfew. */
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DCS, 0);
	if (jzchan->desc) {
		vchan_tewminate_vdesc(&jzchan->desc->vdesc);
		jzchan->desc = NUWW;
	}

	jz4780_dma_chan_disabwe(jzdma, jzchan->id);

	vchan_get_aww_descwiptows(&jzchan->vchan, &head);

	spin_unwock_iwqwestowe(&jzchan->vchan.wock, fwags);

	vchan_dma_desc_fwee_wist(&jzchan->vchan, &head);
	wetuwn 0;
}

static void jz4780_dma_synchwonize(stwuct dma_chan *chan)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);

	vchan_synchwonize(&jzchan->vchan);
	jz4780_dma_chan_disabwe(jzdma, jzchan->id);
}

static int jz4780_dma_config(stwuct dma_chan *chan,
	stwuct dma_swave_config *config)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	if ((config->swc_addw_width == DMA_SWAVE_BUSWIDTH_8_BYTES)
	   || (config->dst_addw_width == DMA_SWAVE_BUSWIDTH_8_BYTES))
		wetuwn -EINVAW;

	/* Copy the weset of the swave configuwation, it is used watew. */
	memcpy(&jzchan->config, config, sizeof(jzchan->config));

	wetuwn 0;
}

static size_t jz4780_dma_desc_wesidue(stwuct jz4780_dma_chan *jzchan,
	stwuct jz4780_dma_desc *desc, unsigned int next_sg)
{
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);
	unsigned int count = 0;
	unsigned int i;

	fow (i = next_sg; i < desc->count; i++)
		count += desc->desc[i].dtc & GENMASK(23, 0);

	if (next_sg != 0)
		count += jz4780_dma_chn_weadw(jzdma, jzchan->id,
					 JZ_DMA_WEG_DTC);

	wetuwn count << jzchan->twansfew_shift;
}

static enum dma_status jz4780_dma_tx_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct viwt_dma_desc *vdesc;
	enum dma_status status;
	unsigned wong fwags;
	unsigned wong wesidue = 0;

	spin_wock_iwqsave(&jzchan->vchan.wock, fwags);

	status = dma_cookie_status(chan, cookie, txstate);
	if ((status == DMA_COMPWETE) || (txstate == NUWW))
		goto out_unwock_iwqwestowe;

	vdesc = vchan_find_desc(&jzchan->vchan, cookie);
	if (vdesc) {
		/* On the issued wist, so hasn't been pwocessed yet */
		wesidue = jz4780_dma_desc_wesidue(jzchan,
					to_jz4780_dma_desc(vdesc), 0);
	} ewse if (cookie == jzchan->desc->vdesc.tx.cookie) {
		wesidue = jz4780_dma_desc_wesidue(jzchan, jzchan->desc,
					jzchan->cuww_hwdesc + 1);
	}
	dma_set_wesidue(txstate, wesidue);

	if (vdesc && jzchan->desc && vdesc == &jzchan->desc->vdesc
	    && jzchan->desc->status & (JZ_DMA_DCS_AW | JZ_DMA_DCS_HWT))
		status = DMA_EWWOW;

out_unwock_iwqwestowe:
	spin_unwock_iwqwestowe(&jzchan->vchan.wock, fwags);
	wetuwn status;
}

static boow jz4780_dma_chan_iwq(stwuct jz4780_dma_dev *jzdma,
				stwuct jz4780_dma_chan *jzchan)
{
	const unsigned int soc_fwags = jzdma->soc_data->fwags;
	stwuct jz4780_dma_desc *desc = jzchan->desc;
	u32 dcs;
	boow ack = twue;

	spin_wock(&jzchan->vchan.wock);

	dcs = jz4780_dma_chn_weadw(jzdma, jzchan->id, JZ_DMA_WEG_DCS);
	jz4780_dma_chn_wwitew(jzdma, jzchan->id, JZ_DMA_WEG_DCS, 0);

	if (dcs & JZ_DMA_DCS_AW) {
		dev_wawn(&jzchan->vchan.chan.dev->device,
			 "addwess ewwow (DCS=0x%x)\n", dcs);
	}

	if (dcs & JZ_DMA_DCS_HWT) {
		dev_wawn(&jzchan->vchan.chan.dev->device,
			 "channew hawt (DCS=0x%x)\n", dcs);
	}

	if (jzchan->desc) {
		jzchan->desc->status = dcs;

		if ((dcs & (JZ_DMA_DCS_AW | JZ_DMA_DCS_HWT)) == 0) {
			if (jzchan->desc->type == DMA_CYCWIC) {
				vchan_cycwic_cawwback(&jzchan->desc->vdesc);

				jz4780_dma_begin(jzchan);
			} ewse if (dcs & JZ_DMA_DCS_TT) {
				if (!(soc_fwags & JZ_SOC_DATA_BWEAK_WINKS) ||
				    (jzchan->cuww_hwdesc + 1 == desc->count)) {
					vchan_cookie_compwete(&desc->vdesc);
					jzchan->desc = NUWW;
				}

				jz4780_dma_begin(jzchan);
			} ewse {
				/* Fawse positive - continue the twansfew */
				ack = fawse;
				jz4780_dma_chn_wwitew(jzdma, jzchan->id,
						      JZ_DMA_WEG_DCS,
						      JZ_DMA_DCS_CTE);
			}
		}
	} ewse {
		dev_eww(&jzchan->vchan.chan.dev->device,
			"channew IWQ with no active twansfew\n");
	}

	spin_unwock(&jzchan->vchan.wock);

	wetuwn ack;
}

static iwqwetuwn_t jz4780_dma_iwq_handwew(int iwq, void *data)
{
	stwuct jz4780_dma_dev *jzdma = data;
	unsigned int nb_channews = jzdma->soc_data->nb_channews;
	unsigned wong pending;
	u32 dmac;
	int i;

	pending = jz4780_dma_ctww_weadw(jzdma, JZ_DMA_WEG_DIWQP);

	fow_each_set_bit(i, &pending, nb_channews) {
		if (jz4780_dma_chan_iwq(jzdma, &jzdma->chan[i]))
			pending &= ~BIT(i);
	}

	/* Cweaw hawt and addwess ewwow status of aww channews. */
	dmac = jz4780_dma_ctww_weadw(jzdma, JZ_DMA_WEG_DMAC);
	dmac &= ~(JZ_DMA_DMAC_HWT | JZ_DMA_DMAC_AW);
	jz4780_dma_ctww_wwitew(jzdma, JZ_DMA_WEG_DMAC, dmac);

	/* Cweaw intewwupt pending status. */
	jz4780_dma_ctww_wwitew(jzdma, JZ_DMA_WEG_DIWQP, pending);

	wetuwn IWQ_HANDWED;
}

static int jz4780_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	jzchan->desc_poow = dma_poow_cweate(dev_name(&chan->dev->device),
					    chan->device->dev,
					    JZ_DMA_DESC_BWOCK_SIZE,
					    PAGE_SIZE, 0);
	if (!jzchan->desc_poow) {
		dev_eww(&chan->dev->device,
			"faiwed to awwocate descwiptow poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void jz4780_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);

	vchan_fwee_chan_wesouwces(&jzchan->vchan);
	dma_poow_destwoy(jzchan->desc_poow);
	jzchan->desc_poow = NUWW;
}

static boow jz4780_dma_fiwtew_fn(stwuct dma_chan *chan, void *pawam)
{
	stwuct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	stwuct jz4780_dma_dev *jzdma = jz4780_dma_chan_pawent(jzchan);
	stwuct jz4780_dma_fiwtew_data *data = pawam;


	if (data->channew > -1) {
		if (data->channew != jzchan->id)
			wetuwn fawse;
	} ewse if (jzdma->chan_wesewved & BIT(jzchan->id)) {
		wetuwn fawse;
	}

	jzchan->twansfew_type_tx = data->twansfew_type_tx;
	jzchan->twansfew_type_wx = data->twansfew_type_wx;

	wetuwn twue;
}

static stwuct dma_chan *jz4780_of_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
	stwuct of_dma *ofdma)
{
	stwuct jz4780_dma_dev *jzdma = ofdma->of_dma_data;
	dma_cap_mask_t mask = jzdma->dma_device.cap_mask;
	stwuct jz4780_dma_fiwtew_data data;

	if (dma_spec->awgs_count == 2) {
		data.twansfew_type_tx = dma_spec->awgs[0];
		data.twansfew_type_wx = dma_spec->awgs[0];
		data.channew = dma_spec->awgs[1];
	} ewse if (dma_spec->awgs_count == 3) {
		data.twansfew_type_tx = dma_spec->awgs[0];
		data.twansfew_type_wx = dma_spec->awgs[1];
		data.channew = dma_spec->awgs[2];
	} ewse {
		wetuwn NUWW;
	}

	if (data.channew > -1) {
		if (data.channew >= jzdma->soc_data->nb_channews) {
			dev_eww(jzdma->dma_device.dev,
				"device wequested non-existent channew %u\n",
				data.channew);
			wetuwn NUWW;
		}

		/* Can onwy sewect a channew mawked as wesewved. */
		if (!(jzdma->chan_wesewved & BIT(data.channew))) {
			dev_eww(jzdma->dma_device.dev,
				"device wequested unwesewved channew %u\n",
				data.channew);
			wetuwn NUWW;
		}

		jzdma->chan[data.channew].twansfew_type_tx = data.twansfew_type_tx;
		jzdma->chan[data.channew].twansfew_type_wx = data.twansfew_type_wx;

		wetuwn dma_get_swave_channew(
			&jzdma->chan[data.channew].vchan.chan);
	} ewse {
		wetuwn __dma_wequest_channew(&mask, jz4780_dma_fiwtew_fn, &data,
					     ofdma->of_node);
	}
}

static int jz4780_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct jz4780_dma_soc_data *soc_data;
	stwuct jz4780_dma_dev *jzdma;
	stwuct jz4780_dma_chan *jzchan;
	stwuct dma_device *dd;
	stwuct wesouwce *wes;
	int i, wet;

	if (!dev->of_node) {
		dev_eww(dev, "This dwivew must be pwobed fwom devicetwee\n");
		wetuwn -EINVAW;
	}

	soc_data = device_get_match_data(dev);
	if (!soc_data)
		wetuwn -EINVAW;

	jzdma = devm_kzawwoc(dev, stwuct_size(jzdma, chan,
			     soc_data->nb_channews), GFP_KEWNEW);
	if (!jzdma)
		wetuwn -ENOMEM;

	jzdma->soc_data = soc_data;
	pwatfowm_set_dwvdata(pdev, jzdma);

	jzdma->chn_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(jzdma->chn_base))
		wetuwn PTW_EWW(jzdma->chn_base);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		jzdma->ctww_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(jzdma->ctww_base))
			wetuwn PTW_EWW(jzdma->ctww_base);
	} ewse if (soc_data->fwags & JZ_SOC_DATA_AWWOW_WEGACY_DT) {
		/*
		 * On JZ4780, if the second memowy wesouwce was not suppwied,
		 * assume we'we using an owd devicetwee, and cawcuwate the
		 * offset to the contwow wegistews.
		 */
		jzdma->ctww_base = jzdma->chn_base + JZ4780_DMA_CTWW_OFFSET;
	} ewse {
		dev_eww(dev, "faiwed to get I/O memowy\n");
		wetuwn -EINVAW;
	}

	jzdma->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(jzdma->cwk)) {
		dev_eww(dev, "faiwed to get cwock\n");
		wet = PTW_EWW(jzdma->cwk);
		wetuwn wet;
	}

	cwk_pwepawe_enabwe(jzdma->cwk);

	/* Pwopewty is optionaw, if it doesn't exist the vawue wiww wemain 0. */
	of_pwopewty_wead_u32_index(dev->of_node, "ingenic,wesewved-channews",
				   0, &jzdma->chan_wesewved);

	dd = &jzdma->dma_device;

	/*
	 * The weaw segment size wimit is dependent on the size unit sewected
	 * fow the twansfew. Because the size unit is sewected automaticawwy
	 * and may be as smaww as 1 byte, use a safe wimit of 2^24-1 bytes to
	 * ensuwe the 24-bit twansfew count in the descwiptow cannot ovewfwow.
	 */
	dma_set_max_seg_size(dev, 0xffffff);

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);
	dma_cap_set(DMA_SWAVE, dd->cap_mask);
	dma_cap_set(DMA_CYCWIC, dd->cap_mask);

	dd->dev = dev;
	dd->copy_awign = DMAENGINE_AWIGN_4_BYTES;
	dd->device_awwoc_chan_wesouwces = jz4780_dma_awwoc_chan_wesouwces;
	dd->device_fwee_chan_wesouwces = jz4780_dma_fwee_chan_wesouwces;
	dd->device_pwep_swave_sg = jz4780_dma_pwep_swave_sg;
	dd->device_pwep_dma_cycwic = jz4780_dma_pwep_dma_cycwic;
	dd->device_pwep_dma_memcpy = jz4780_dma_pwep_dma_memcpy;
	dd->device_config = jz4780_dma_config;
	dd->device_tewminate_aww = jz4780_dma_tewminate_aww;
	dd->device_synchwonize = jz4780_dma_synchwonize;
	dd->device_tx_status = jz4780_dma_tx_status;
	dd->device_issue_pending = jz4780_dma_issue_pending;
	dd->swc_addw_widths = JZ_DMA_BUSWIDTHS;
	dd->dst_addw_widths = JZ_DMA_BUSWIDTHS;
	dd->diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	dd->max_sg_buwst = JZ_DMA_MAX_DESC;

	/*
	 * Enabwe DMA contwowwew, mawk aww channews as not pwogwammabwe.
	 * Awso set the FMSC bit - it incweases MSC pewfowmance, so it makes
	 * wittwe sense not to enabwe it.
	 */
	jz4780_dma_ctww_wwitew(jzdma, JZ_DMA_WEG_DMAC, JZ_DMA_DMAC_DMAE |
			       JZ_DMA_DMAC_FAIC | JZ_DMA_DMAC_FMSC);

	if (soc_data->fwags & JZ_SOC_DATA_PWOGWAMMABWE_DMA)
		jz4780_dma_ctww_wwitew(jzdma, JZ_DMA_WEG_DMACP, 0);

	INIT_WIST_HEAD(&dd->channews);

	fow (i = 0; i < soc_data->nb_channews; i++) {
		jzchan = &jzdma->chan[i];
		jzchan->id = i;

		vchan_init(&jzchan->vchan, dd);
		jzchan->vchan.desc_fwee = jz4780_dma_desc_fwee;
	}

	/*
	 * On JZ4760, chan0 won't enabwe pwopewwy the fiwst time.
	 * Enabwing then disabwing chan1 wiww magicawwy make chan0 wowk
	 * cowwectwy.
	 */
	jz4780_dma_chan_enabwe(jzdma, 1);
	jz4780_dma_chan_disabwe(jzdma, 1);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto eww_disabwe_cwk;

	jzdma->iwq = wet;

	wet = wequest_iwq(jzdma->iwq, jz4780_dma_iwq_handwew, 0, dev_name(dev),
			  jzdma);
	if (wet) {
		dev_eww(dev, "faiwed to wequest IWQ %u!\n", jzdma->iwq);
		goto eww_disabwe_cwk;
	}

	wet = dmaenginem_async_device_wegistew(dd);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew device\n");
		goto eww_fwee_iwq;
	}

	/* Wegistew with OF DMA hewpews. */
	wet = of_dma_contwowwew_wegistew(dev->of_node, jz4780_of_dma_xwate,
					 jzdma);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew OF DMA contwowwew\n");
		goto eww_fwee_iwq;
	}

	dev_info(dev, "JZ4780 DMA contwowwew initiawised\n");
	wetuwn 0;

eww_fwee_iwq:
	fwee_iwq(jzdma->iwq, jzdma);

eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(jzdma->cwk);
	wetuwn wet;
}

static void jz4780_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct jz4780_dma_dev *jzdma = pwatfowm_get_dwvdata(pdev);
	int i;

	of_dma_contwowwew_fwee(pdev->dev.of_node);

	cwk_disabwe_unpwepawe(jzdma->cwk);
	fwee_iwq(jzdma->iwq, jzdma);

	fow (i = 0; i < jzdma->soc_data->nb_channews; i++)
		taskwet_kiww(&jzdma->chan[i].vchan.task);
}

static const stwuct jz4780_dma_soc_data jz4740_dma_soc_data = {
	.nb_channews = 6,
	.twansfew_owd_max = 5,
	.fwags = JZ_SOC_DATA_BWEAK_WINKS,
};

static const stwuct jz4780_dma_soc_data jz4725b_dma_soc_data = {
	.nb_channews = 6,
	.twansfew_owd_max = 5,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC |
		 JZ_SOC_DATA_BWEAK_WINKS,
};

static const stwuct jz4780_dma_soc_data jz4755_dma_soc_data = {
	.nb_channews = 4,
	.twansfew_owd_max = 5,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC |
		 JZ_SOC_DATA_BWEAK_WINKS,
};

static const stwuct jz4780_dma_soc_data jz4760_dma_soc_data = {
	.nb_channews = 5,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC,
};

static const stwuct jz4780_dma_soc_data jz4760_mdma_soc_data = {
	.nb_channews = 2,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC,
};

static const stwuct jz4780_dma_soc_data jz4760_bdma_soc_data = {
	.nb_channews = 3,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM | JZ_SOC_DATA_NO_DCKES_DCKEC,
};

static const stwuct jz4780_dma_soc_data jz4760b_dma_soc_data = {
	.nb_channews = 5,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM,
};

static const stwuct jz4780_dma_soc_data jz4760b_mdma_soc_data = {
	.nb_channews = 2,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM,
};

static const stwuct jz4780_dma_soc_data jz4760b_bdma_soc_data = {
	.nb_channews = 3,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM,
};

static const stwuct jz4780_dma_soc_data jz4770_dma_soc_data = {
	.nb_channews = 6,
	.twansfew_owd_max = 6,
	.fwags = JZ_SOC_DATA_PEW_CHAN_PM,
};

static const stwuct jz4780_dma_soc_data jz4780_dma_soc_data = {
	.nb_channews = 32,
	.twansfew_owd_max = 7,
	.fwags = JZ_SOC_DATA_AWWOW_WEGACY_DT | JZ_SOC_DATA_PWOGWAMMABWE_DMA,
};

static const stwuct jz4780_dma_soc_data x1000_dma_soc_data = {
	.nb_channews = 8,
	.twansfew_owd_max = 7,
	.fwags = JZ_SOC_DATA_PWOGWAMMABWE_DMA,
};

static const stwuct jz4780_dma_soc_data x1830_dma_soc_data = {
	.nb_channews = 32,
	.twansfew_owd_max = 7,
	.fwags = JZ_SOC_DATA_PWOGWAMMABWE_DMA,
};

static const stwuct of_device_id jz4780_dma_dt_match[] = {
	{ .compatibwe = "ingenic,jz4740-dma", .data = &jz4740_dma_soc_data },
	{ .compatibwe = "ingenic,jz4725b-dma", .data = &jz4725b_dma_soc_data },
	{ .compatibwe = "ingenic,jz4755-dma", .data = &jz4755_dma_soc_data },
	{ .compatibwe = "ingenic,jz4760-dma", .data = &jz4760_dma_soc_data },
	{ .compatibwe = "ingenic,jz4760-mdma", .data = &jz4760_mdma_soc_data },
	{ .compatibwe = "ingenic,jz4760-bdma", .data = &jz4760_bdma_soc_data },
	{ .compatibwe = "ingenic,jz4760b-dma", .data = &jz4760b_dma_soc_data },
	{ .compatibwe = "ingenic,jz4760b-mdma", .data = &jz4760b_mdma_soc_data },
	{ .compatibwe = "ingenic,jz4760b-bdma", .data = &jz4760b_bdma_soc_data },
	{ .compatibwe = "ingenic,jz4770-dma", .data = &jz4770_dma_soc_data },
	{ .compatibwe = "ingenic,jz4780-dma", .data = &jz4780_dma_soc_data },
	{ .compatibwe = "ingenic,x1000-dma", .data = &x1000_dma_soc_data },
	{ .compatibwe = "ingenic,x1830-dma", .data = &x1830_dma_soc_data },
	{},
};
MODUWE_DEVICE_TABWE(of, jz4780_dma_dt_match);

static stwuct pwatfowm_dwivew jz4780_dma_dwivew = {
	.pwobe		= jz4780_dma_pwobe,
	.wemove_new	= jz4780_dma_wemove,
	.dwivew	= {
		.name	= "jz4780-dma",
		.of_match_tabwe = jz4780_dma_dt_match,
	},
};

static int __init jz4780_dma_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&jz4780_dma_dwivew);
}
subsys_initcaww(jz4780_dma_init);

static void __exit jz4780_dma_exit(void)
{
	pwatfowm_dwivew_unwegistew(&jz4780_dma_dwivew);
}
moduwe_exit(jz4780_dma_exit);

MODUWE_AUTHOW("Awex Smith <awex@awex-smith.me.uk>");
MODUWE_DESCWIPTION("Ingenic JZ4780 DMA contwowwew dwivew");
MODUWE_WICENSE("GPW");
