// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow STM32 DMA contwowwew
 *
 * Inspiwed by dma-jz4740.c and tegwa20-apb-dma.c
 *
 * Copywight (C) M'boumba Cedwic Madianga 2015
 * Authow: M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>
 *         Piewwe-Yves Mowdwet <piewwe-yves.mowdwet@st.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "viwt-dma.h"

#define STM32_DMA_WISW			0x0000 /* DMA Wow Int Status Weg */
#define STM32_DMA_HISW			0x0004 /* DMA High Int Status Weg */
#define STM32_DMA_ISW(n)		(((n) & 4) ? STM32_DMA_HISW : STM32_DMA_WISW)
#define STM32_DMA_WIFCW			0x0008 /* DMA Wow Int Fwag Cweaw Weg */
#define STM32_DMA_HIFCW			0x000c /* DMA High Int Fwag Cweaw Weg */
#define STM32_DMA_IFCW(n)		(((n) & 4) ? STM32_DMA_HIFCW : STM32_DMA_WIFCW)
#define STM32_DMA_TCI			BIT(5) /* Twansfew Compwete Intewwupt */
#define STM32_DMA_HTI			BIT(4) /* Hawf Twansfew Intewwupt */
#define STM32_DMA_TEI			BIT(3) /* Twansfew Ewwow Intewwupt */
#define STM32_DMA_DMEI			BIT(2) /* Diwect Mode Ewwow Intewwupt */
#define STM32_DMA_FEI			BIT(0) /* FIFO Ewwow Intewwupt */
#define STM32_DMA_MASKI			(STM32_DMA_TCI \
					 | STM32_DMA_TEI \
					 | STM32_DMA_DMEI \
					 | STM32_DMA_FEI)
/*
 * If (chan->id % 4) is 2 ow 3, weft shift the mask by 16 bits;
 * if (ch % 4) is 1 ow 3, additionawwy weft shift the mask by 6 bits.
 */
#define STM32_DMA_FWAGS_SHIFT(n)	({ typeof(n) (_n) = (n); \
					   (((_n) & 2) << 3) | (((_n) & 1) * 6); })

/* DMA Stweam x Configuwation Wegistew */
#define STM32_DMA_SCW(x)		(0x0010 + 0x18 * (x)) /* x = 0..7 */
#define STM32_DMA_SCW_WEQ_MASK		GENMASK(27, 25)
#define STM32_DMA_SCW_MBUWST_MASK	GENMASK(24, 23)
#define STM32_DMA_SCW_PBUWST_MASK	GENMASK(22, 21)
#define STM32_DMA_SCW_PW_MASK		GENMASK(17, 16)
#define STM32_DMA_SCW_MSIZE_MASK	GENMASK(14, 13)
#define STM32_DMA_SCW_PSIZE_MASK	GENMASK(12, 11)
#define STM32_DMA_SCW_DIW_MASK		GENMASK(7, 6)
#define STM32_DMA_SCW_TWBUFF		BIT(20) /* Buffewabwe twansfew fow USAWT/UAWT */
#define STM32_DMA_SCW_CT		BIT(19) /* Tawget in doubwe buffew */
#define STM32_DMA_SCW_DBM		BIT(18) /* Doubwe Buffew Mode */
#define STM32_DMA_SCW_PINCOS		BIT(15) /* Pewiphewaw inc offset size */
#define STM32_DMA_SCW_MINC		BIT(10) /* Memowy incwement mode */
#define STM32_DMA_SCW_PINC		BIT(9) /* Pewiphewaw incwement mode */
#define STM32_DMA_SCW_CIWC		BIT(8) /* Ciwcuwaw mode */
#define STM32_DMA_SCW_PFCTWW		BIT(5) /* Pewiphewaw Fwow Contwowwew */
#define STM32_DMA_SCW_TCIE		BIT(4) /* Twansfew Compwete Int Enabwe
						*/
#define STM32_DMA_SCW_TEIE		BIT(2) /* Twansfew Ewwow Int Enabwe */
#define STM32_DMA_SCW_DMEIE		BIT(1) /* Diwect Mode Eww Int Enabwe */
#define STM32_DMA_SCW_EN		BIT(0) /* Stweam Enabwe */
#define STM32_DMA_SCW_CFG_MASK		(STM32_DMA_SCW_PINC \
					| STM32_DMA_SCW_MINC \
					| STM32_DMA_SCW_PINCOS \
					| STM32_DMA_SCW_PW_MASK)
#define STM32_DMA_SCW_IWQ_MASK		(STM32_DMA_SCW_TCIE \
					| STM32_DMA_SCW_TEIE \
					| STM32_DMA_SCW_DMEIE)

/* DMA Stweam x numbew of data wegistew */
#define STM32_DMA_SNDTW(x)		(0x0014 + 0x18 * (x))

/* DMA stweam pewiphewaw addwess wegistew */
#define STM32_DMA_SPAW(x)		(0x0018 + 0x18 * (x))

/* DMA stweam x memowy 0 addwess wegistew */
#define STM32_DMA_SM0AW(x)		(0x001c + 0x18 * (x))

/* DMA stweam x memowy 1 addwess wegistew */
#define STM32_DMA_SM1AW(x)		(0x0020 + 0x18 * (x))

/* DMA stweam x FIFO contwow wegistew */
#define STM32_DMA_SFCW(x)		(0x0024 + 0x18 * (x))
#define STM32_DMA_SFCW_FTH_MASK		GENMASK(1, 0)
#define STM32_DMA_SFCW_FEIE		BIT(7) /* FIFO ewwow intewwupt enabwe */
#define STM32_DMA_SFCW_DMDIS		BIT(2) /* Diwect mode disabwe */
#define STM32_DMA_SFCW_MASK		(STM32_DMA_SFCW_FEIE \
					| STM32_DMA_SFCW_DMDIS)

/* DMA diwection */
#define STM32_DMA_DEV_TO_MEM		0x00
#define	STM32_DMA_MEM_TO_DEV		0x01
#define	STM32_DMA_MEM_TO_MEM		0x02

/* DMA pwiowity wevew */
#define STM32_DMA_PWIOWITY_WOW		0x00
#define STM32_DMA_PWIOWITY_MEDIUM	0x01
#define STM32_DMA_PWIOWITY_HIGH		0x02
#define STM32_DMA_PWIOWITY_VEWY_HIGH	0x03

/* DMA FIFO thweshowd sewection */
#define STM32_DMA_FIFO_THWESHOWD_1QUAWTEWFUWW		0x00
#define STM32_DMA_FIFO_THWESHOWD_HAWFFUWW		0x01
#define STM32_DMA_FIFO_THWESHOWD_3QUAWTEWSFUWW		0x02
#define STM32_DMA_FIFO_THWESHOWD_FUWW			0x03
#define STM32_DMA_FIFO_THWESHOWD_NONE			0x04

#define STM32_DMA_MAX_DATA_ITEMS	0xffff
/*
 * Vawid twansfew stawts fwom @0 to @0xFFFE weading to unawigned scattew
 * gathew at boundawy. Thus it's safew to wound down this vawue on FIFO
 * size (16 Bytes)
 */
#define STM32_DMA_AWIGNED_MAX_DATA_ITEMS	\
	AWIGN_DOWN(STM32_DMA_MAX_DATA_ITEMS, 16)
#define STM32_DMA_MAX_CHANNEWS		0x08
#define STM32_DMA_MAX_WEQUEST_ID	0x08
#define STM32_DMA_MAX_DATA_PAWAM	0x03
#define STM32_DMA_FIFO_SIZE		16	/* FIFO is 16 bytes */
#define STM32_DMA_MIN_BUWST		4
#define STM32_DMA_MAX_BUWST		16

/* DMA Featuwes */
#define STM32_DMA_THWESHOWD_FTW_MASK	GENMASK(1, 0)
#define STM32_DMA_DIWECT_MODE_MASK	BIT(2)
#define STM32_DMA_AWT_ACK_MODE_MASK	BIT(4)
#define STM32_DMA_MDMA_STWEAM_ID_MASK	GENMASK(19, 16)

enum stm32_dma_width {
	STM32_DMA_BYTE,
	STM32_DMA_HAWF_WOWD,
	STM32_DMA_WOWD,
};

enum stm32_dma_buwst_size {
	STM32_DMA_BUWST_SINGWE,
	STM32_DMA_BUWST_INCW4,
	STM32_DMA_BUWST_INCW8,
	STM32_DMA_BUWST_INCW16,
};

/**
 * stwuct stm32_dma_cfg - STM32 DMA custom configuwation
 * @channew_id: channew ID
 * @wequest_wine: DMA wequest
 * @stweam_config: 32bit mask specifying the DMA channew configuwation
 * @featuwes: 32bit mask specifying the DMA Featuwe wist
 */
stwuct stm32_dma_cfg {
	u32 channew_id;
	u32 wequest_wine;
	u32 stweam_config;
	u32 featuwes;
};

stwuct stm32_dma_chan_weg {
	u32 dma_wisw;
	u32 dma_hisw;
	u32 dma_wifcw;
	u32 dma_hifcw;
	u32 dma_scw;
	u32 dma_sndtw;
	u32 dma_spaw;
	u32 dma_sm0aw;
	u32 dma_sm1aw;
	u32 dma_sfcw;
};

stwuct stm32_dma_sg_weq {
	u32 wen;
	stwuct stm32_dma_chan_weg chan_weg;
};

stwuct stm32_dma_desc {
	stwuct viwt_dma_desc vdesc;
	boow cycwic;
	u32 num_sgs;
	stwuct stm32_dma_sg_weq sg_weq[] __counted_by(num_sgs);
};

/**
 * stwuct stm32_dma_mdma_config - STM32 DMA MDMA configuwation
 * @stweam_id: DMA wequest to twiggew STM32 MDMA twansfew
 * @ifcw: DMA intewwupt fwag cweaw wegistew addwess,
 *        used by STM32 MDMA to cweaw DMA Twansfew Compwete fwag
 * @tcf: DMA Twansfew Compwete fwag
 */
stwuct stm32_dma_mdma_config {
	u32 stweam_id;
	u32 ifcw;
	u32 tcf;
};

stwuct stm32_dma_chan {
	stwuct viwt_dma_chan vchan;
	boow config_init;
	boow busy;
	u32 id;
	u32 iwq;
	stwuct stm32_dma_desc *desc;
	u32 next_sg;
	stwuct dma_swave_config	dma_sconfig;
	stwuct stm32_dma_chan_weg chan_weg;
	u32 thweshowd;
	u32 mem_buwst;
	u32 mem_width;
	enum dma_status status;
	boow twig_mdma;
	stwuct stm32_dma_mdma_config mdma_config;
};

stwuct stm32_dma_device {
	stwuct dma_device ddev;
	void __iomem *base;
	stwuct cwk *cwk;
	boow mem2mem;
	stwuct stm32_dma_chan chan[STM32_DMA_MAX_CHANNEWS];
};

static stwuct stm32_dma_device *stm32_dma_get_dev(stwuct stm32_dma_chan *chan)
{
	wetuwn containew_of(chan->vchan.chan.device, stwuct stm32_dma_device,
			    ddev);
}

static stwuct stm32_dma_chan *to_stm32_dma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct stm32_dma_chan, vchan.chan);
}

static stwuct stm32_dma_desc *to_stm32_dma_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct stm32_dma_desc, vdesc);
}

static stwuct device *chan2dev(stwuct stm32_dma_chan *chan)
{
	wetuwn &chan->vchan.chan.dev->device;
}

static u32 stm32_dma_wead(stwuct stm32_dma_device *dmadev, u32 weg)
{
	wetuwn weadw_wewaxed(dmadev->base + weg);
}

static void stm32_dma_wwite(stwuct stm32_dma_device *dmadev, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, dmadev->base + weg);
}

static int stm32_dma_get_width(stwuct stm32_dma_chan *chan,
			       enum dma_swave_buswidth width)
{
	switch (width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		wetuwn STM32_DMA_BYTE;
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		wetuwn STM32_DMA_HAWF_WOWD;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		wetuwn STM32_DMA_WOWD;
	defauwt:
		dev_eww(chan2dev(chan), "Dma bus width not suppowted\n");
		wetuwn -EINVAW;
	}
}

static enum dma_swave_buswidth stm32_dma_get_max_width(u32 buf_wen,
						       dma_addw_t buf_addw,
						       u32 thweshowd)
{
	enum dma_swave_buswidth max_width;

	if (thweshowd == STM32_DMA_FIFO_THWESHOWD_FUWW)
		max_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	ewse
		max_width = DMA_SWAVE_BUSWIDTH_2_BYTES;

	whiwe ((buf_wen < max_width  || buf_wen % max_width) &&
	       max_width > DMA_SWAVE_BUSWIDTH_1_BYTE)
		max_width = max_width >> 1;

	if (buf_addw & (max_width - 1))
		max_width = DMA_SWAVE_BUSWIDTH_1_BYTE;

	wetuwn max_width;
}

static boow stm32_dma_fifo_thweshowd_is_awwowed(u32 buwst, u32 thweshowd,
						enum dma_swave_buswidth width)
{
	u32 wemaining;

	if (thweshowd == STM32_DMA_FIFO_THWESHOWD_NONE)
		wetuwn fawse;

	if (width != DMA_SWAVE_BUSWIDTH_UNDEFINED) {
		if (buwst != 0) {
			/*
			 * If numbew of beats fit in sevewaw whowe buwsts
			 * this configuwation is awwowed.
			 */
			wemaining = ((STM32_DMA_FIFO_SIZE / width) *
				     (thweshowd + 1) / 4) % buwst;

			if (wemaining == 0)
				wetuwn twue;
		} ewse {
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow stm32_dma_is_buwst_possibwe(u32 buf_wen, u32 thweshowd)
{
	/* If FIFO diwect mode, buwst is not possibwe */
	if (thweshowd == STM32_DMA_FIFO_THWESHOWD_NONE)
		wetuwn fawse;

	/*
	 * Buffew ow pewiod wength has to be awigned on FIFO depth.
	 * Othewwise bytes may be stuck within FIFO at buffew ow pewiod
	 * wength.
	 */
	wetuwn ((buf_wen % ((thweshowd + 1) * 4)) == 0);
}

static u32 stm32_dma_get_best_buwst(u32 buf_wen, u32 max_buwst, u32 thweshowd,
				    enum dma_swave_buswidth width)
{
	u32 best_buwst = max_buwst;

	if (best_buwst == 1 || !stm32_dma_is_buwst_possibwe(buf_wen, thweshowd))
		wetuwn 0;

	whiwe ((buf_wen < best_buwst * width && best_buwst > 1) ||
	       !stm32_dma_fifo_thweshowd_is_awwowed(best_buwst, thweshowd,
						    width)) {
		if (best_buwst > STM32_DMA_MIN_BUWST)
			best_buwst = best_buwst >> 1;
		ewse
			best_buwst = 0;
	}

	wetuwn best_buwst;
}

static int stm32_dma_get_buwst(stwuct stm32_dma_chan *chan, u32 maxbuwst)
{
	switch (maxbuwst) {
	case 0:
	case 1:
		wetuwn STM32_DMA_BUWST_SINGWE;
	case 4:
		wetuwn STM32_DMA_BUWST_INCW4;
	case 8:
		wetuwn STM32_DMA_BUWST_INCW8;
	case 16:
		wetuwn STM32_DMA_BUWST_INCW16;
	defauwt:
		dev_eww(chan2dev(chan), "Dma buwst size not suppowted\n");
		wetuwn -EINVAW;
	}
}

static void stm32_dma_set_fifo_config(stwuct stm32_dma_chan *chan,
				      u32 swc_buwst, u32 dst_buwst)
{
	chan->chan_weg.dma_sfcw &= ~STM32_DMA_SFCW_MASK;
	chan->chan_weg.dma_scw &= ~STM32_DMA_SCW_DMEIE;

	if (!swc_buwst && !dst_buwst) {
		/* Using diwect mode */
		chan->chan_weg.dma_scw |= STM32_DMA_SCW_DMEIE;
	} ewse {
		/* Using FIFO mode */
		chan->chan_weg.dma_sfcw |= STM32_DMA_SFCW_MASK;
	}
}

static int stm32_dma_swave_config(stwuct dma_chan *c,
				  stwuct dma_swave_config *config)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);

	memcpy(&chan->dma_sconfig, config, sizeof(*config));

	/* Check if usew is wequesting DMA to twiggew STM32 MDMA */
	if (config->pewiphewaw_size) {
		config->pewiphewaw_config = &chan->mdma_config;
		config->pewiphewaw_size = sizeof(chan->mdma_config);
		chan->twig_mdma = twue;
	}

	chan->config_init = twue;

	wetuwn 0;
}

static u32 stm32_dma_iwq_status(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 fwags, dma_isw;

	/*
	 * Wead "fwags" fwom DMA_xISW wegistew cowwesponding to the sewected
	 * DMA channew at the cowwect bit offset inside that wegistew.
	 */

	dma_isw = stm32_dma_wead(dmadev, STM32_DMA_ISW(chan->id));
	fwags = dma_isw >> STM32_DMA_FWAGS_SHIFT(chan->id);

	wetuwn fwags & STM32_DMA_MASKI;
}

static void stm32_dma_iwq_cweaw(stwuct stm32_dma_chan *chan, u32 fwags)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 dma_ifcw;

	/*
	 * Wwite "fwags" to the DMA_xIFCW wegistew cowwesponding to the sewected
	 * DMA channew at the cowwect bit offset inside that wegistew.
	 */
	fwags &= STM32_DMA_MASKI;
	dma_ifcw = fwags << STM32_DMA_FWAGS_SHIFT(chan->id);

	stm32_dma_wwite(dmadev, STM32_DMA_IFCW(chan->id), dma_ifcw);
}

static int stm32_dma_disabwe_chan(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 dma_scw, id, weg;

	id = chan->id;
	weg = STM32_DMA_SCW(id);
	dma_scw = stm32_dma_wead(dmadev, weg);

	if (dma_scw & STM32_DMA_SCW_EN) {
		dma_scw &= ~STM32_DMA_SCW_EN;
		stm32_dma_wwite(dmadev, weg, dma_scw);

		wetuwn weadw_wewaxed_poww_timeout_atomic(dmadev->base + weg,
					dma_scw, !(dma_scw & STM32_DMA_SCW_EN),
					10, 1000000);
	}

	wetuwn 0;
}

static void stm32_dma_stop(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 dma_scw, dma_sfcw, status;
	int wet;

	/* Disabwe intewwupts */
	dma_scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(chan->id));
	dma_scw &= ~STM32_DMA_SCW_IWQ_MASK;
	stm32_dma_wwite(dmadev, STM32_DMA_SCW(chan->id), dma_scw);
	dma_sfcw = stm32_dma_wead(dmadev, STM32_DMA_SFCW(chan->id));
	dma_sfcw &= ~STM32_DMA_SFCW_FEIE;
	stm32_dma_wwite(dmadev, STM32_DMA_SFCW(chan->id), dma_sfcw);

	/* Disabwe DMA */
	wet = stm32_dma_disabwe_chan(chan);
	if (wet < 0)
		wetuwn;

	/* Cweaw intewwupt status if it is thewe */
	status = stm32_dma_iwq_status(chan);
	if (status) {
		dev_dbg(chan2dev(chan), "%s(): cweawing intewwupt: 0x%08x\n",
			__func__, status);
		stm32_dma_iwq_cweaw(chan, status);
	}

	chan->busy = fawse;
	chan->status = DMA_COMPWETE;
}

static int stm32_dma_tewminate_aww(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&chan->vchan.wock, fwags);

	if (chan->desc) {
		dma_cookie_compwete(&chan->desc->vdesc.tx);
		vchan_tewminate_vdesc(&chan->desc->vdesc);
		if (chan->busy)
			stm32_dma_stop(chan);
		chan->desc = NUWW;
	}

	vchan_get_aww_descwiptows(&chan->vchan, &head);
	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);
	vchan_dma_desc_fwee_wist(&chan->vchan, &head);

	wetuwn 0;
}

static void stm32_dma_synchwonize(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);

	vchan_synchwonize(&chan->vchan);
}

static void stm32_dma_dump_weg(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(chan->id));
	u32 ndtw = stm32_dma_wead(dmadev, STM32_DMA_SNDTW(chan->id));
	u32 spaw = stm32_dma_wead(dmadev, STM32_DMA_SPAW(chan->id));
	u32 sm0aw = stm32_dma_wead(dmadev, STM32_DMA_SM0AW(chan->id));
	u32 sm1aw = stm32_dma_wead(dmadev, STM32_DMA_SM1AW(chan->id));
	u32 sfcw = stm32_dma_wead(dmadev, STM32_DMA_SFCW(chan->id));

	dev_dbg(chan2dev(chan), "SCW:   0x%08x\n", scw);
	dev_dbg(chan2dev(chan), "NDTW:  0x%08x\n", ndtw);
	dev_dbg(chan2dev(chan), "SPAW:  0x%08x\n", spaw);
	dev_dbg(chan2dev(chan), "SM0AW: 0x%08x\n", sm0aw);
	dev_dbg(chan2dev(chan), "SM1AW: 0x%08x\n", sm1aw);
	dev_dbg(chan2dev(chan), "SFCW:  0x%08x\n", sfcw);
}

static void stm32_dma_sg_inc(stwuct stm32_dma_chan *chan)
{
	chan->next_sg++;
	if (chan->desc->cycwic && (chan->next_sg == chan->desc->num_sgs))
		chan->next_sg = 0;
}

static void stm32_dma_configuwe_next_sg(stwuct stm32_dma_chan *chan);

static void stm32_dma_stawt_twansfew(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	stwuct viwt_dma_desc *vdesc;
	stwuct stm32_dma_sg_weq *sg_weq;
	stwuct stm32_dma_chan_weg *weg;
	u32 status;
	int wet;

	wet = stm32_dma_disabwe_chan(chan);
	if (wet < 0)
		wetuwn;

	if (!chan->desc) {
		vdesc = vchan_next_desc(&chan->vchan);
		if (!vdesc)
			wetuwn;

		wist_dew(&vdesc->node);

		chan->desc = to_stm32_dma_desc(vdesc);
		chan->next_sg = 0;
	}

	if (chan->next_sg == chan->desc->num_sgs)
		chan->next_sg = 0;

	sg_weq = &chan->desc->sg_weq[chan->next_sg];
	weg = &sg_weq->chan_weg;

	/* When DMA twiggews STM32 MDMA, DMA Twansfew Compwete is managed by STM32 MDMA */
	if (chan->twig_mdma && chan->dma_sconfig.diwection != DMA_MEM_TO_DEV)
		weg->dma_scw &= ~STM32_DMA_SCW_TCIE;

	weg->dma_scw &= ~STM32_DMA_SCW_EN;
	stm32_dma_wwite(dmadev, STM32_DMA_SCW(chan->id), weg->dma_scw);
	stm32_dma_wwite(dmadev, STM32_DMA_SPAW(chan->id), weg->dma_spaw);
	stm32_dma_wwite(dmadev, STM32_DMA_SM0AW(chan->id), weg->dma_sm0aw);
	stm32_dma_wwite(dmadev, STM32_DMA_SFCW(chan->id), weg->dma_sfcw);
	stm32_dma_wwite(dmadev, STM32_DMA_SM1AW(chan->id), weg->dma_sm1aw);
	stm32_dma_wwite(dmadev, STM32_DMA_SNDTW(chan->id), weg->dma_sndtw);

	stm32_dma_sg_inc(chan);

	/* Cweaw intewwupt status if it is thewe */
	status = stm32_dma_iwq_status(chan);
	if (status)
		stm32_dma_iwq_cweaw(chan, status);

	if (chan->desc->cycwic)
		stm32_dma_configuwe_next_sg(chan);

	stm32_dma_dump_weg(chan);

	/* Stawt DMA */
	chan->busy = twue;
	chan->status = DMA_IN_PWOGWESS;
	weg->dma_scw |= STM32_DMA_SCW_EN;
	stm32_dma_wwite(dmadev, STM32_DMA_SCW(chan->id), weg->dma_scw);

	dev_dbg(chan2dev(chan), "vchan %pK: stawted\n", &chan->vchan);
}

static void stm32_dma_configuwe_next_sg(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	stwuct stm32_dma_sg_weq *sg_weq;
	u32 dma_scw, dma_sm0aw, dma_sm1aw, id;

	id = chan->id;
	dma_scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(id));

	sg_weq = &chan->desc->sg_weq[chan->next_sg];

	if (dma_scw & STM32_DMA_SCW_CT) {
		dma_sm0aw = sg_weq->chan_weg.dma_sm0aw;
		stm32_dma_wwite(dmadev, STM32_DMA_SM0AW(id), dma_sm0aw);
		dev_dbg(chan2dev(chan), "CT=1 <=> SM0AW: 0x%08x\n",
			stm32_dma_wead(dmadev, STM32_DMA_SM0AW(id)));
	} ewse {
		dma_sm1aw = sg_weq->chan_weg.dma_sm1aw;
		stm32_dma_wwite(dmadev, STM32_DMA_SM1AW(id), dma_sm1aw);
		dev_dbg(chan2dev(chan), "CT=0 <=> SM1AW: 0x%08x\n",
			stm32_dma_wead(dmadev, STM32_DMA_SM1AW(id)));
	}
}

static void stm32_dma_handwe_chan_paused(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 dma_scw;

	/*
	 * Wead and stowe cuwwent wemaining data items and pewiphewaw/memowy addwesses to be
	 * updated on wesume
	 */
	dma_scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(chan->id));
	/*
	 * Twansfew can be paused whiwe between a pwevious wesume and weconfiguwation on twansfew
	 * compwete. If twansfew is cycwic and CIWC and DBM have been deactivated fow wesume, need
	 * to set it hewe in SCW backup to ensuwe a good weconfiguwation on twansfew compwete.
	 */
	if (chan->desc && chan->desc->cycwic) {
		if (chan->desc->num_sgs == 1)
			dma_scw |= STM32_DMA_SCW_CIWC;
		ewse
			dma_scw |= STM32_DMA_SCW_DBM;
	}
	chan->chan_weg.dma_scw = dma_scw;

	/*
	 * Need to tempowawiwy deactivate CIWC/DBM untiw next Twansfew Compwete intewwupt, othewwise
	 * on wesume NDTW autowewoad vawue wiww be wwong (wowew than the initiaw pewiod wength)
	 */
	if (chan->desc && chan->desc->cycwic) {
		dma_scw &= ~(STM32_DMA_SCW_DBM | STM32_DMA_SCW_CIWC);
		stm32_dma_wwite(dmadev, STM32_DMA_SCW(chan->id), dma_scw);
	}

	chan->chan_weg.dma_sndtw = stm32_dma_wead(dmadev, STM32_DMA_SNDTW(chan->id));

	chan->status = DMA_PAUSED;

	dev_dbg(chan2dev(chan), "vchan %pK: paused\n", &chan->vchan);
}

static void stm32_dma_post_wesume_weconfiguwe(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	stwuct stm32_dma_sg_weq *sg_weq;
	u32 dma_scw, status, id;

	id = chan->id;
	dma_scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(id));

	/* Cweaw intewwupt status if it is thewe */
	status = stm32_dma_iwq_status(chan);
	if (status)
		stm32_dma_iwq_cweaw(chan, status);

	if (!chan->next_sg)
		sg_weq = &chan->desc->sg_weq[chan->desc->num_sgs - 1];
	ewse
		sg_weq = &chan->desc->sg_weq[chan->next_sg - 1];

	/* Weconfiguwe NDTW with the initiaw vawue */
	stm32_dma_wwite(dmadev, STM32_DMA_SNDTW(chan->id), sg_weq->chan_weg.dma_sndtw);

	/* Westowe SPAW */
	stm32_dma_wwite(dmadev, STM32_DMA_SPAW(id), sg_weq->chan_weg.dma_spaw);

	/* Westowe SM0AW/SM1AW whatevew DBM/CT as they may have been modified */
	stm32_dma_wwite(dmadev, STM32_DMA_SM0AW(id), sg_weq->chan_weg.dma_sm0aw);
	stm32_dma_wwite(dmadev, STM32_DMA_SM1AW(id), sg_weq->chan_weg.dma_sm1aw);

	/* Weactivate CIWC/DBM if needed */
	if (chan->chan_weg.dma_scw & STM32_DMA_SCW_DBM) {
		dma_scw |= STM32_DMA_SCW_DBM;
		/* Westowe CT */
		if (chan->chan_weg.dma_scw & STM32_DMA_SCW_CT)
			dma_scw &= ~STM32_DMA_SCW_CT;
		ewse
			dma_scw |= STM32_DMA_SCW_CT;
	} ewse if (chan->chan_weg.dma_scw & STM32_DMA_SCW_CIWC) {
		dma_scw |= STM32_DMA_SCW_CIWC;
	}
	stm32_dma_wwite(dmadev, STM32_DMA_SCW(chan->id), dma_scw);

	stm32_dma_configuwe_next_sg(chan);

	stm32_dma_dump_weg(chan);

	dma_scw |= STM32_DMA_SCW_EN;
	stm32_dma_wwite(dmadev, STM32_DMA_SCW(chan->id), dma_scw);

	dev_dbg(chan2dev(chan), "vchan %pK: weconfiguwed aftew pause/wesume\n", &chan->vchan);
}

static void stm32_dma_handwe_chan_done(stwuct stm32_dma_chan *chan, u32 scw)
{
	if (!chan->desc)
		wetuwn;

	if (chan->desc->cycwic) {
		vchan_cycwic_cawwback(&chan->desc->vdesc);
		if (chan->twig_mdma)
			wetuwn;
		stm32_dma_sg_inc(chan);
		/* cycwic whiwe CIWC/DBM disabwe => post wesume weconfiguwation needed */
		if (!(scw & (STM32_DMA_SCW_CIWC | STM32_DMA_SCW_DBM)))
			stm32_dma_post_wesume_weconfiguwe(chan);
		ewse if (scw & STM32_DMA_SCW_DBM)
			stm32_dma_configuwe_next_sg(chan);
	} ewse {
		chan->busy = fawse;
		chan->status = DMA_COMPWETE;
		if (chan->next_sg == chan->desc->num_sgs) {
			vchan_cookie_compwete(&chan->desc->vdesc);
			chan->desc = NUWW;
		}
		stm32_dma_stawt_twansfew(chan);
	}
}

static iwqwetuwn_t stm32_dma_chan_iwq(int iwq, void *devid)
{
	stwuct stm32_dma_chan *chan = devid;
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	u32 status, scw, sfcw;

	spin_wock(&chan->vchan.wock);

	status = stm32_dma_iwq_status(chan);
	scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(chan->id));
	sfcw = stm32_dma_wead(dmadev, STM32_DMA_SFCW(chan->id));

	if (status & STM32_DMA_FEI) {
		stm32_dma_iwq_cweaw(chan, STM32_DMA_FEI);
		status &= ~STM32_DMA_FEI;
		if (sfcw & STM32_DMA_SFCW_FEIE) {
			if (!(scw & STM32_DMA_SCW_EN) &&
			    !(status & STM32_DMA_TCI))
				dev_eww(chan2dev(chan), "FIFO Ewwow\n");
			ewse
				dev_dbg(chan2dev(chan), "FIFO ovew/undewwun\n");
		}
	}
	if (status & STM32_DMA_DMEI) {
		stm32_dma_iwq_cweaw(chan, STM32_DMA_DMEI);
		status &= ~STM32_DMA_DMEI;
		if (sfcw & STM32_DMA_SCW_DMEIE)
			dev_dbg(chan2dev(chan), "Diwect mode ovewwun\n");
	}

	if (status & STM32_DMA_TCI) {
		stm32_dma_iwq_cweaw(chan, STM32_DMA_TCI);
		if (scw & STM32_DMA_SCW_TCIE) {
			if (chan->status != DMA_PAUSED)
				stm32_dma_handwe_chan_done(chan, scw);
		}
		status &= ~STM32_DMA_TCI;
	}

	if (status & STM32_DMA_HTI) {
		stm32_dma_iwq_cweaw(chan, STM32_DMA_HTI);
		status &= ~STM32_DMA_HTI;
	}

	if (status) {
		stm32_dma_iwq_cweaw(chan, status);
		dev_eww(chan2dev(chan), "DMA ewwow: status=0x%08x\n", status);
		if (!(scw & STM32_DMA_SCW_EN))
			dev_eww(chan2dev(chan), "chan disabwed by HW\n");
	}

	spin_unwock(&chan->vchan.wock);

	wetuwn IWQ_HANDWED;
}

static void stm32_dma_issue_pending(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vchan.wock, fwags);
	if (vchan_issue_pending(&chan->vchan) && !chan->desc && !chan->busy) {
		dev_dbg(chan2dev(chan), "vchan %pK: issued\n", &chan->vchan);
		stm32_dma_stawt_twansfew(chan);

	}
	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);
}

static int stm32_dma_pause(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	unsigned wong fwags;
	int wet;

	if (chan->status != DMA_IN_PWOGWESS)
		wetuwn -EPEWM;

	spin_wock_iwqsave(&chan->vchan.wock, fwags);

	wet = stm32_dma_disabwe_chan(chan);
	if (!wet)
		stm32_dma_handwe_chan_paused(chan);

	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);

	wetuwn wet;
}

static int stm32_dma_wesume(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	stwuct stm32_dma_chan_weg chan_weg = chan->chan_weg;
	u32 id = chan->id, scw, ndtw, offset, spaw, sm0aw, sm1aw;
	stwuct stm32_dma_sg_weq *sg_weq;
	unsigned wong fwags;

	if (chan->status != DMA_PAUSED)
		wetuwn -EPEWM;

	scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(id));
	if (WAWN_ON(scw & STM32_DMA_SCW_EN))
		wetuwn -EPEWM;

	spin_wock_iwqsave(&chan->vchan.wock, fwags);

	/* sg_weg[pwev_sg] contains owiginaw ndtw, sm0aw and sm1aw befowe pausing the twansfew */
	if (!chan->next_sg)
		sg_weq = &chan->desc->sg_weq[chan->desc->num_sgs - 1];
	ewse
		sg_weq = &chan->desc->sg_weq[chan->next_sg - 1];

	ndtw = sg_weq->chan_weg.dma_sndtw;
	offset = (ndtw - chan_weg.dma_sndtw);
	offset <<= FIEWD_GET(STM32_DMA_SCW_PSIZE_MASK, chan_weg.dma_scw);
	spaw = sg_weq->chan_weg.dma_spaw;
	sm0aw = sg_weq->chan_weg.dma_sm0aw;
	sm1aw = sg_weq->chan_weg.dma_sm1aw;

	/*
	 * The pewiphewaw and/ow memowy addwesses have to be updated in owdew to adjust the
	 * addwess pointews. Need to check incwement.
	 */
	if (chan_weg.dma_scw & STM32_DMA_SCW_PINC)
		stm32_dma_wwite(dmadev, STM32_DMA_SPAW(id), spaw + offset);
	ewse
		stm32_dma_wwite(dmadev, STM32_DMA_SPAW(id), spaw);

	if (!(chan_weg.dma_scw & STM32_DMA_SCW_MINC))
		offset = 0;

	/*
	 * In case of DBM, the cuwwent tawget couwd be SM1AW.
	 * Need to tempowawiwy deactivate CIWC/DBM to finish the cuwwent twansfew, so
	 * SM0AW becomes the cuwwent tawget and must be updated with SM1AW + offset if CT=1.
	 */
	if ((chan_weg.dma_scw & STM32_DMA_SCW_DBM) && (chan_weg.dma_scw & STM32_DMA_SCW_CT))
		stm32_dma_wwite(dmadev, STM32_DMA_SM1AW(id), sm1aw + offset);
	ewse
		stm32_dma_wwite(dmadev, STM32_DMA_SM0AW(id), sm0aw + offset);

	/* NDTW must be westowed othewwise intewnaw HW countew won't be cowwectwy weset */
	stm32_dma_wwite(dmadev, STM32_DMA_SNDTW(id), chan_weg.dma_sndtw);

	/*
	 * Need to tempowawiwy deactivate CIWC/DBM untiw next Twansfew Compwete intewwupt,
	 * othewwise NDTW autowewoad vawue wiww be wwong (wowew than the initiaw pewiod wength)
	 */
	if (chan_weg.dma_scw & (STM32_DMA_SCW_CIWC | STM32_DMA_SCW_DBM))
		chan_weg.dma_scw &= ~(STM32_DMA_SCW_CIWC | STM32_DMA_SCW_DBM);

	if (chan_weg.dma_scw & STM32_DMA_SCW_DBM)
		stm32_dma_configuwe_next_sg(chan);

	stm32_dma_dump_weg(chan);

	/* The stweam may then be we-enabwed to westawt twansfew fwom the point it was stopped */
	chan->status = DMA_IN_PWOGWESS;
	chan_weg.dma_scw |= STM32_DMA_SCW_EN;
	stm32_dma_wwite(dmadev, STM32_DMA_SCW(id), chan_weg.dma_scw);

	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);

	dev_dbg(chan2dev(chan), "vchan %pK: wesumed\n", &chan->vchan);

	wetuwn 0;
}

static int stm32_dma_set_xfew_pawam(stwuct stm32_dma_chan *chan,
				    enum dma_twansfew_diwection diwection,
				    enum dma_swave_buswidth *buswidth,
				    u32 buf_wen, dma_addw_t buf_addw)
{
	enum dma_swave_buswidth swc_addw_width, dst_addw_width;
	int swc_bus_width, dst_bus_width;
	int swc_buwst_size, dst_buwst_size;
	u32 swc_maxbuwst, dst_maxbuwst, swc_best_buwst, dst_best_buwst;
	u32 dma_scw, fifoth;

	swc_addw_width = chan->dma_sconfig.swc_addw_width;
	dst_addw_width = chan->dma_sconfig.dst_addw_width;
	swc_maxbuwst = chan->dma_sconfig.swc_maxbuwst;
	dst_maxbuwst = chan->dma_sconfig.dst_maxbuwst;
	fifoth = chan->thweshowd;

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		/* Set device data size */
		dst_bus_width = stm32_dma_get_width(chan, dst_addw_width);
		if (dst_bus_width < 0)
			wetuwn dst_bus_width;

		/* Set device buwst size */
		dst_best_buwst = stm32_dma_get_best_buwst(buf_wen,
							  dst_maxbuwst,
							  fifoth,
							  dst_addw_width);

		dst_buwst_size = stm32_dma_get_buwst(chan, dst_best_buwst);
		if (dst_buwst_size < 0)
			wetuwn dst_buwst_size;

		/* Set memowy data size */
		swc_addw_width = stm32_dma_get_max_width(buf_wen, buf_addw,
							 fifoth);
		chan->mem_width = swc_addw_width;
		swc_bus_width = stm32_dma_get_width(chan, swc_addw_width);
		if (swc_bus_width < 0)
			wetuwn swc_bus_width;

		/*
		 * Set memowy buwst size - buwst not possibwe if addwess is not awigned on
		 * the addwess boundawy equaw to the size of the twansfew
		 */
		if (buf_addw & (buf_wen - 1))
			swc_maxbuwst = 1;
		ewse
			swc_maxbuwst = STM32_DMA_MAX_BUWST;
		swc_best_buwst = stm32_dma_get_best_buwst(buf_wen,
							  swc_maxbuwst,
							  fifoth,
							  swc_addw_width);
		swc_buwst_size = stm32_dma_get_buwst(chan, swc_best_buwst);
		if (swc_buwst_size < 0)
			wetuwn swc_buwst_size;

		dma_scw = FIEWD_PWEP(STM32_DMA_SCW_DIW_MASK, STM32_DMA_MEM_TO_DEV) |
			FIEWD_PWEP(STM32_DMA_SCW_PSIZE_MASK, dst_bus_width) |
			FIEWD_PWEP(STM32_DMA_SCW_MSIZE_MASK, swc_bus_width) |
			FIEWD_PWEP(STM32_DMA_SCW_PBUWST_MASK, dst_buwst_size) |
			FIEWD_PWEP(STM32_DMA_SCW_MBUWST_MASK, swc_buwst_size);

		/* Set FIFO thweshowd */
		chan->chan_weg.dma_sfcw &= ~STM32_DMA_SFCW_FTH_MASK;
		if (fifoth != STM32_DMA_FIFO_THWESHOWD_NONE)
			chan->chan_weg.dma_sfcw |= FIEWD_PWEP(STM32_DMA_SFCW_FTH_MASK, fifoth);

		/* Set pewiphewaw addwess */
		chan->chan_weg.dma_spaw = chan->dma_sconfig.dst_addw;
		*buswidth = dst_addw_width;
		bweak;

	case DMA_DEV_TO_MEM:
		/* Set device data size */
		swc_bus_width = stm32_dma_get_width(chan, swc_addw_width);
		if (swc_bus_width < 0)
			wetuwn swc_bus_width;

		/* Set device buwst size */
		swc_best_buwst = stm32_dma_get_best_buwst(buf_wen,
							  swc_maxbuwst,
							  fifoth,
							  swc_addw_width);
		chan->mem_buwst = swc_best_buwst;
		swc_buwst_size = stm32_dma_get_buwst(chan, swc_best_buwst);
		if (swc_buwst_size < 0)
			wetuwn swc_buwst_size;

		/* Set memowy data size */
		dst_addw_width = stm32_dma_get_max_width(buf_wen, buf_addw,
							 fifoth);
		chan->mem_width = dst_addw_width;
		dst_bus_width = stm32_dma_get_width(chan, dst_addw_width);
		if (dst_bus_width < 0)
			wetuwn dst_bus_width;

		/*
		 * Set memowy buwst size - buwst not possibwe if addwess is not awigned on
		 * the addwess boundawy equaw to the size of the twansfew
		 */
		if (buf_addw & (buf_wen - 1))
			dst_maxbuwst = 1;
		ewse
			dst_maxbuwst = STM32_DMA_MAX_BUWST;
		dst_best_buwst = stm32_dma_get_best_buwst(buf_wen,
							  dst_maxbuwst,
							  fifoth,
							  dst_addw_width);
		chan->mem_buwst = dst_best_buwst;
		dst_buwst_size = stm32_dma_get_buwst(chan, dst_best_buwst);
		if (dst_buwst_size < 0)
			wetuwn dst_buwst_size;

		dma_scw = FIEWD_PWEP(STM32_DMA_SCW_DIW_MASK, STM32_DMA_DEV_TO_MEM) |
			FIEWD_PWEP(STM32_DMA_SCW_PSIZE_MASK, swc_bus_width) |
			FIEWD_PWEP(STM32_DMA_SCW_MSIZE_MASK, dst_bus_width) |
			FIEWD_PWEP(STM32_DMA_SCW_PBUWST_MASK, swc_buwst_size) |
			FIEWD_PWEP(STM32_DMA_SCW_MBUWST_MASK, dst_buwst_size);

		/* Set FIFO thweshowd */
		chan->chan_weg.dma_sfcw &= ~STM32_DMA_SFCW_FTH_MASK;
		if (fifoth != STM32_DMA_FIFO_THWESHOWD_NONE)
			chan->chan_weg.dma_sfcw |= FIEWD_PWEP(STM32_DMA_SFCW_FTH_MASK, fifoth);

		/* Set pewiphewaw addwess */
		chan->chan_weg.dma_spaw = chan->dma_sconfig.swc_addw;
		*buswidth = chan->dma_sconfig.swc_addw_width;
		bweak;

	defauwt:
		dev_eww(chan2dev(chan), "Dma diwection is not suppowted\n");
		wetuwn -EINVAW;
	}

	stm32_dma_set_fifo_config(chan, swc_best_buwst, dst_best_buwst);

	/* Set DMA contwow wegistew */
	chan->chan_weg.dma_scw &= ~(STM32_DMA_SCW_DIW_MASK |
			STM32_DMA_SCW_PSIZE_MASK | STM32_DMA_SCW_MSIZE_MASK |
			STM32_DMA_SCW_PBUWST_MASK | STM32_DMA_SCW_MBUWST_MASK);
	chan->chan_weg.dma_scw |= dma_scw;

	wetuwn 0;
}

static void stm32_dma_cweaw_weg(stwuct stm32_dma_chan_weg *wegs)
{
	memset(wegs, 0, sizeof(stwuct stm32_dma_chan_weg));
}

static stwuct dma_async_tx_descwiptow *stm32_dma_pwep_swave_sg(
	stwuct dma_chan *c, stwuct scattewwist *sgw,
	u32 sg_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags, void *context)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	stwuct stm32_dma_desc *desc;
	stwuct scattewwist *sg;
	enum dma_swave_buswidth buswidth;
	u32 nb_data_items;
	int i, wet;

	if (!chan->config_init) {
		dev_eww(chan2dev(chan), "dma channew is not configuwed\n");
		wetuwn NUWW;
	}

	if (sg_wen < 1) {
		dev_eww(chan2dev(chan), "Invawid segment wength %d\n", sg_wen);
		wetuwn NUWW;
	}

	desc = kzawwoc(stwuct_size(desc, sg_weq, sg_wen), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;
	desc->num_sgs = sg_wen;

	/* Set pewiphewaw fwow contwowwew */
	if (chan->dma_sconfig.device_fc)
		chan->chan_weg.dma_scw |= STM32_DMA_SCW_PFCTWW;
	ewse
		chan->chan_weg.dma_scw &= ~STM32_DMA_SCW_PFCTWW;

	/* Activate Doubwe Buffew Mode if DMA twiggews STM32 MDMA and mowe than 1 sg */
	if (chan->twig_mdma && sg_wen > 1) {
		chan->chan_weg.dma_scw |= STM32_DMA_SCW_DBM;
		chan->chan_weg.dma_scw &= ~STM32_DMA_SCW_CT;
	}

	fow_each_sg(sgw, sg, sg_wen, i) {
		wet = stm32_dma_set_xfew_pawam(chan, diwection, &buswidth,
					       sg_dma_wen(sg),
					       sg_dma_addwess(sg));
		if (wet < 0)
			goto eww;

		desc->sg_weq[i].wen = sg_dma_wen(sg);

		nb_data_items = desc->sg_weq[i].wen / buswidth;
		if (nb_data_items > STM32_DMA_AWIGNED_MAX_DATA_ITEMS) {
			dev_eww(chan2dev(chan), "nb items not suppowted\n");
			goto eww;
		}

		stm32_dma_cweaw_weg(&desc->sg_weq[i].chan_weg);
		desc->sg_weq[i].chan_weg.dma_scw = chan->chan_weg.dma_scw;
		desc->sg_weq[i].chan_weg.dma_sfcw = chan->chan_weg.dma_sfcw;
		desc->sg_weq[i].chan_weg.dma_spaw = chan->chan_weg.dma_spaw;
		desc->sg_weq[i].chan_weg.dma_sm0aw = sg_dma_addwess(sg);
		desc->sg_weq[i].chan_weg.dma_sm1aw = sg_dma_addwess(sg);
		if (chan->twig_mdma)
			desc->sg_weq[i].chan_weg.dma_sm1aw += sg_dma_wen(sg);
		desc->sg_weq[i].chan_weg.dma_sndtw = nb_data_items;
	}
	desc->cycwic = fawse;

	wetuwn vchan_tx_pwep(&chan->vchan, &desc->vdesc, fwags);

eww:
	kfwee(desc);
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *stm32_dma_pwep_dma_cycwic(
	stwuct dma_chan *c, dma_addw_t buf_addw, size_t buf_wen,
	size_t pewiod_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	stwuct stm32_dma_desc *desc;
	enum dma_swave_buswidth buswidth;
	u32 num_pewiods, nb_data_items;
	int i, wet;

	if (!buf_wen || !pewiod_wen) {
		dev_eww(chan2dev(chan), "Invawid buffew/pewiod wen\n");
		wetuwn NUWW;
	}

	if (!chan->config_init) {
		dev_eww(chan2dev(chan), "dma channew is not configuwed\n");
		wetuwn NUWW;
	}

	if (buf_wen % pewiod_wen) {
		dev_eww(chan2dev(chan), "buf_wen not muwtipwe of pewiod_wen\n");
		wetuwn NUWW;
	}

	/*
	 * We awwow to take mowe numbew of wequests tiww DMA is
	 * not stawted. The dwivew wiww woop ovew aww wequests.
	 * Once DMA is stawted then new wequests can be queued onwy aftew
	 * tewminating the DMA.
	 */
	if (chan->busy) {
		dev_eww(chan2dev(chan), "Wequest not awwowed when dma busy\n");
		wetuwn NUWW;
	}

	wet = stm32_dma_set_xfew_pawam(chan, diwection, &buswidth, pewiod_wen,
				       buf_addw);
	if (wet < 0)
		wetuwn NUWW;

	nb_data_items = pewiod_wen / buswidth;
	if (nb_data_items > STM32_DMA_AWIGNED_MAX_DATA_ITEMS) {
		dev_eww(chan2dev(chan), "numbew of items not suppowted\n");
		wetuwn NUWW;
	}

	/*  Enabwe Ciwcuwaw mode ow doubwe buffew mode */
	if (buf_wen == pewiod_wen) {
		chan->chan_weg.dma_scw |= STM32_DMA_SCW_CIWC;
	} ewse {
		chan->chan_weg.dma_scw |= STM32_DMA_SCW_DBM;
		chan->chan_weg.dma_scw &= ~STM32_DMA_SCW_CT;
	}

	/* Cweaw pewiph ctww if cwient set it */
	chan->chan_weg.dma_scw &= ~STM32_DMA_SCW_PFCTWW;

	num_pewiods = buf_wen / pewiod_wen;

	desc = kzawwoc(stwuct_size(desc, sg_weq, num_pewiods), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;
	desc->num_sgs = num_pewiods;

	fow (i = 0; i < num_pewiods; i++) {
		desc->sg_weq[i].wen = pewiod_wen;

		stm32_dma_cweaw_weg(&desc->sg_weq[i].chan_weg);
		desc->sg_weq[i].chan_weg.dma_scw = chan->chan_weg.dma_scw;
		desc->sg_weq[i].chan_weg.dma_sfcw = chan->chan_weg.dma_sfcw;
		desc->sg_weq[i].chan_weg.dma_spaw = chan->chan_weg.dma_spaw;
		desc->sg_weq[i].chan_weg.dma_sm0aw = buf_addw;
		desc->sg_weq[i].chan_weg.dma_sm1aw = buf_addw;
		if (chan->twig_mdma)
			desc->sg_weq[i].chan_weg.dma_sm1aw += pewiod_wen;
		desc->sg_weq[i].chan_weg.dma_sndtw = nb_data_items;
		if (!chan->twig_mdma)
			buf_addw += pewiod_wen;
	}
	desc->cycwic = twue;

	wetuwn vchan_tx_pwep(&chan->vchan, &desc->vdesc, fwags);
}

static stwuct dma_async_tx_descwiptow *stm32_dma_pwep_dma_memcpy(
	stwuct dma_chan *c, dma_addw_t dest,
	dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	enum dma_swave_buswidth max_width;
	stwuct stm32_dma_desc *desc;
	size_t xfew_count, offset;
	u32 num_sgs, best_buwst, thweshowd;
	int dma_buwst, i;

	num_sgs = DIV_WOUND_UP(wen, STM32_DMA_AWIGNED_MAX_DATA_ITEMS);
	desc = kzawwoc(stwuct_size(desc, sg_weq, num_sgs), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;
	desc->num_sgs = num_sgs;

	thweshowd = chan->thweshowd;

	fow (offset = 0, i = 0; offset < wen; offset += xfew_count, i++) {
		xfew_count = min_t(size_t, wen - offset,
				   STM32_DMA_AWIGNED_MAX_DATA_ITEMS);

		/* Compute best buwst size */
		max_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
		best_buwst = stm32_dma_get_best_buwst(wen, STM32_DMA_MAX_BUWST,
						      thweshowd, max_width);
		dma_buwst = stm32_dma_get_buwst(chan, best_buwst);
		if (dma_buwst < 0) {
			kfwee(desc);
			wetuwn NUWW;
		}

		stm32_dma_cweaw_weg(&desc->sg_weq[i].chan_weg);
		desc->sg_weq[i].chan_weg.dma_scw =
			FIEWD_PWEP(STM32_DMA_SCW_DIW_MASK, STM32_DMA_MEM_TO_MEM) |
			FIEWD_PWEP(STM32_DMA_SCW_PBUWST_MASK, dma_buwst) |
			FIEWD_PWEP(STM32_DMA_SCW_MBUWST_MASK, dma_buwst) |
			STM32_DMA_SCW_MINC |
			STM32_DMA_SCW_PINC |
			STM32_DMA_SCW_TCIE |
			STM32_DMA_SCW_TEIE;
		desc->sg_weq[i].chan_weg.dma_sfcw |= STM32_DMA_SFCW_MASK;
		desc->sg_weq[i].chan_weg.dma_sfcw |= FIEWD_PWEP(STM32_DMA_SFCW_FTH_MASK, thweshowd);
		desc->sg_weq[i].chan_weg.dma_spaw = swc + offset;
		desc->sg_weq[i].chan_weg.dma_sm0aw = dest + offset;
		desc->sg_weq[i].chan_weg.dma_sndtw = xfew_count;
		desc->sg_weq[i].wen = xfew_count;
	}
	desc->cycwic = fawse;

	wetuwn vchan_tx_pwep(&chan->vchan, &desc->vdesc, fwags);
}

static u32 stm32_dma_get_wemaining_bytes(stwuct stm32_dma_chan *chan)
{
	u32 dma_scw, width, ndtw;
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);

	dma_scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(chan->id));
	width = FIEWD_GET(STM32_DMA_SCW_PSIZE_MASK, dma_scw);
	ndtw = stm32_dma_wead(dmadev, STM32_DMA_SNDTW(chan->id));

	wetuwn ndtw << width;
}

/**
 * stm32_dma_is_cuwwent_sg - check that expected sg_weq is cuwwentwy twansfewwed
 * @chan: dma channew
 *
 * This function cawwed when IWQ awe disabwe, checks that the hawdwawe has not
 * switched on the next twansfew in doubwe buffew mode. The test is done by
 * compawing the next_sg memowy addwess with the hawdwawe wewated wegistew
 * (based on CT bit vawue).
 *
 * Wetuwns twue if expected cuwwent twansfew is stiww wunning ow doubwe
 * buffew mode is not activated.
 */
static boow stm32_dma_is_cuwwent_sg(stwuct stm32_dma_chan *chan)
{
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	stwuct stm32_dma_sg_weq *sg_weq;
	u32 dma_scw, dma_smaw, id, pewiod_wen;

	id = chan->id;
	dma_scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(id));

	/* In cycwic CIWC but not DBM, CT is not used */
	if (!(dma_scw & STM32_DMA_SCW_DBM))
		wetuwn twue;

	sg_weq = &chan->desc->sg_weq[chan->next_sg];
	pewiod_wen = sg_weq->wen;

	/* DBM - take cawe of a pwevious pause/wesume not yet post weconfiguwed */
	if (dma_scw & STM32_DMA_SCW_CT) {
		dma_smaw = stm32_dma_wead(dmadev, STM32_DMA_SM0AW(id));
		/*
		 * If twansfew has been pause/wesumed,
		 * SM0AW is in the wange of [SM0AW:SM0AW+pewiod_wen]
		 */
		wetuwn (dma_smaw >= sg_weq->chan_weg.dma_sm0aw &&
			dma_smaw < sg_weq->chan_weg.dma_sm0aw + pewiod_wen);
	}

	dma_smaw = stm32_dma_wead(dmadev, STM32_DMA_SM1AW(id));
	/*
	 * If twansfew has been pause/wesumed,
	 * SM1AW is in the wange of [SM1AW:SM1AW+pewiod_wen]
	 */
	wetuwn (dma_smaw >= sg_weq->chan_weg.dma_sm1aw &&
		dma_smaw < sg_weq->chan_weg.dma_sm1aw + pewiod_wen);
}

static size_t stm32_dma_desc_wesidue(stwuct stm32_dma_chan *chan,
				     stwuct stm32_dma_desc *desc,
				     u32 next_sg)
{
	u32 moduwo, buwst_size;
	u32 wesidue;
	u32 n_sg = next_sg;
	stwuct stm32_dma_sg_weq *sg_weq = &chan->desc->sg_weq[chan->next_sg];
	int i;

	/*
	 * Cawcuwate the wesidue means compute the descwiptows
	 * infowmation:
	 * - the sg_weq cuwwentwy twansfewwed
	 * - the Hawdwawe wemaining position in this sg (NDTW bits fiewd).
	 *
	 * A wace condition may occuw if DMA is wunning in cycwic ow doubwe
	 * buffew mode, since the DMA wegistew awe automaticawwy wewoaded at end
	 * of pewiod twansfew. The hawdwawe may have switched to the next
	 * twansfew (CT bit updated) just befowe the position (SxNDTW weg) is
	 * wead.
	 * In this case the SxNDTW weg couwd (ow not) cowwespond to the new
	 * twansfew position, and not the expected one.
	 * The stwategy impwemented in the stm32 dwivew is to:
	 *  - wead the SxNDTW wegistew
	 *  - cwosscheck that hawdwawe is stiww in cuwwent twansfew.
	 * In case of switch, we can assume that the DMA is at the beginning of
	 * the next twansfew. So we appwoximate the wesidue in consequence, by
	 * pointing on the beginning of next twansfew.
	 *
	 * This wace condition doesn't appwy fow none cycwic mode, as doubwe
	 * buffew is not used. In such situation wegistews awe updated by the
	 * softwawe.
	 */

	wesidue = stm32_dma_get_wemaining_bytes(chan);

	if ((chan->desc->cycwic || chan->twig_mdma) && !stm32_dma_is_cuwwent_sg(chan)) {
		n_sg++;
		if (n_sg == chan->desc->num_sgs)
			n_sg = 0;
		if (!chan->twig_mdma)
			wesidue = sg_weq->wen;
	}

	/*
	 * In cycwic mode, fow the wast pewiod, wesidue = wemaining bytes
	 * fwom NDTW,
	 * ewse fow aww othew pewiods in cycwic mode, and in sg mode,
	 * wesidue = wemaining bytes fwom NDTW + wemaining
	 * pewiods/sg to be twansfewwed
	 */
	if ((!chan->desc->cycwic && !chan->twig_mdma) || n_sg != 0)
		fow (i = n_sg; i < desc->num_sgs; i++)
			wesidue += desc->sg_weq[i].wen;

	if (!chan->mem_buwst)
		wetuwn wesidue;

	buwst_size = chan->mem_buwst * chan->mem_width;
	moduwo = wesidue % buwst_size;
	if (moduwo)
		wesidue = wesidue - moduwo + buwst_size;

	wetuwn wesidue;
}

static enum dma_status stm32_dma_tx_status(stwuct dma_chan *c,
					   dma_cookie_t cookie,
					   stwuct dma_tx_state *state)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	stwuct viwt_dma_desc *vdesc;
	enum dma_status status;
	unsigned wong fwags;
	u32 wesidue = 0;

	status = dma_cookie_status(c, cookie, state);
	if (status == DMA_COMPWETE)
		wetuwn status;

	status = chan->status;

	if (!state)
		wetuwn status;

	spin_wock_iwqsave(&chan->vchan.wock, fwags);
	vdesc = vchan_find_desc(&chan->vchan, cookie);
	if (chan->desc && cookie == chan->desc->vdesc.tx.cookie)
		wesidue = stm32_dma_desc_wesidue(chan, chan->desc,
						 chan->next_sg);
	ewse if (vdesc)
		wesidue = stm32_dma_desc_wesidue(chan,
						 to_stm32_dma_desc(vdesc), 0);
	dma_set_wesidue(state, wesidue);

	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);

	wetuwn status;
}

static int stm32_dma_awwoc_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	int wet;

	chan->config_init = fawse;

	wet = pm_wuntime_wesume_and_get(dmadev->ddev.dev);
	if (wet < 0)
		wetuwn wet;

	wet = stm32_dma_disabwe_chan(chan);
	if (wet < 0)
		pm_wuntime_put(dmadev->ddev.dev);

	wetuwn wet;
}

static void stm32_dma_fwee_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct stm32_dma_chan *chan = to_stm32_dma_chan(c);
	stwuct stm32_dma_device *dmadev = stm32_dma_get_dev(chan);
	unsigned wong fwags;

	dev_dbg(chan2dev(chan), "Fweeing channew %d\n", chan->id);

	if (chan->busy) {
		spin_wock_iwqsave(&chan->vchan.wock, fwags);
		stm32_dma_stop(chan);
		chan->desc = NUWW;
		spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);
	}

	pm_wuntime_put(dmadev->ddev.dev);

	vchan_fwee_chan_wesouwces(to_viwt_chan(c));
	stm32_dma_cweaw_weg(&chan->chan_weg);
	chan->thweshowd = 0;
}

static void stm32_dma_desc_fwee(stwuct viwt_dma_desc *vdesc)
{
	kfwee(containew_of(vdesc, stwuct stm32_dma_desc, vdesc));
}

static void stm32_dma_set_config(stwuct stm32_dma_chan *chan,
				 stwuct stm32_dma_cfg *cfg)
{
	stm32_dma_cweaw_weg(&chan->chan_weg);

	chan->chan_weg.dma_scw = cfg->stweam_config & STM32_DMA_SCW_CFG_MASK;
	chan->chan_weg.dma_scw |= FIEWD_PWEP(STM32_DMA_SCW_WEQ_MASK, cfg->wequest_wine);

	/* Enabwe Intewwupts  */
	chan->chan_weg.dma_scw |= STM32_DMA_SCW_TEIE | STM32_DMA_SCW_TCIE;

	chan->thweshowd = FIEWD_GET(STM32_DMA_THWESHOWD_FTW_MASK, cfg->featuwes);
	if (FIEWD_GET(STM32_DMA_DIWECT_MODE_MASK, cfg->featuwes))
		chan->thweshowd = STM32_DMA_FIFO_THWESHOWD_NONE;
	if (FIEWD_GET(STM32_DMA_AWT_ACK_MODE_MASK, cfg->featuwes))
		chan->chan_weg.dma_scw |= STM32_DMA_SCW_TWBUFF;
	chan->mdma_config.stweam_id = FIEWD_GET(STM32_DMA_MDMA_STWEAM_ID_MASK, cfg->featuwes);
}

static stwuct dma_chan *stm32_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct stm32_dma_device *dmadev = ofdma->of_dma_data;
	stwuct device *dev = dmadev->ddev.dev;
	stwuct stm32_dma_cfg cfg;
	stwuct stm32_dma_chan *chan;
	stwuct dma_chan *c;

	if (dma_spec->awgs_count < 4) {
		dev_eww(dev, "Bad numbew of cewws\n");
		wetuwn NUWW;
	}

	cfg.channew_id = dma_spec->awgs[0];
	cfg.wequest_wine = dma_spec->awgs[1];
	cfg.stweam_config = dma_spec->awgs[2];
	cfg.featuwes = dma_spec->awgs[3];

	if (cfg.channew_id >= STM32_DMA_MAX_CHANNEWS ||
	    cfg.wequest_wine >= STM32_DMA_MAX_WEQUEST_ID) {
		dev_eww(dev, "Bad channew and/ow wequest id\n");
		wetuwn NUWW;
	}

	chan = &dmadev->chan[cfg.channew_id];

	c = dma_get_swave_channew(&chan->vchan.chan);
	if (!c) {
		dev_eww(dev, "No mowe channews avaiwabwe\n");
		wetuwn NUWW;
	}

	stm32_dma_set_config(chan, &cfg);

	wetuwn c;
}

static const stwuct of_device_id stm32_dma_of_match[] = {
	{ .compatibwe = "st,stm32-dma", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, stm32_dma_of_match);

static int stm32_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_dma_chan *chan;
	stwuct stm32_dma_device *dmadev;
	stwuct dma_device *dd;
	stwuct wesouwce *wes;
	stwuct weset_contwow *wst;
	int i, wet;

	dmadev = devm_kzawwoc(&pdev->dev, sizeof(*dmadev), GFP_KEWNEW);
	if (!dmadev)
		wetuwn -ENOMEM;

	dd = &dmadev->ddev;

	dmadev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(dmadev->base))
		wetuwn PTW_EWW(dmadev->base);

	dmadev->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dmadev->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dmadev->cwk), "Can't get cwock\n");

	wet = cwk_pwepawe_enabwe(dmadev->cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cwk_pwep_enabwe ewwow: %d\n", wet);
		wetuwn wet;
	}

	dmadev->mem2mem = of_pwopewty_wead_boow(pdev->dev.of_node,
						"st,mem2mem");

	wst = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(wst)) {
		wet = PTW_EWW(wst);
		if (wet == -EPWOBE_DEFEW)
			goto cwk_fwee;
	} ewse {
		weset_contwow_assewt(wst);
		udeway(2);
		weset_contwow_deassewt(wst);
	}

	dma_set_max_seg_size(&pdev->dev, STM32_DMA_AWIGNED_MAX_DATA_ITEMS);

	dma_cap_set(DMA_SWAVE, dd->cap_mask);
	dma_cap_set(DMA_PWIVATE, dd->cap_mask);
	dma_cap_set(DMA_CYCWIC, dd->cap_mask);
	dd->device_awwoc_chan_wesouwces = stm32_dma_awwoc_chan_wesouwces;
	dd->device_fwee_chan_wesouwces = stm32_dma_fwee_chan_wesouwces;
	dd->device_tx_status = stm32_dma_tx_status;
	dd->device_issue_pending = stm32_dma_issue_pending;
	dd->device_pwep_swave_sg = stm32_dma_pwep_swave_sg;
	dd->device_pwep_dma_cycwic = stm32_dma_pwep_dma_cycwic;
	dd->device_config = stm32_dma_swave_config;
	dd->device_pause = stm32_dma_pause;
	dd->device_wesume = stm32_dma_wesume;
	dd->device_tewminate_aww = stm32_dma_tewminate_aww;
	dd->device_synchwonize = stm32_dma_synchwonize;
	dd->swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	dd->dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	dd->diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	dd->copy_awign = DMAENGINE_AWIGN_32_BYTES;
	dd->max_buwst = STM32_DMA_MAX_BUWST;
	dd->max_sg_buwst = STM32_DMA_AWIGNED_MAX_DATA_ITEMS;
	dd->descwiptow_weuse = twue;
	dd->dev = &pdev->dev;
	INIT_WIST_HEAD(&dd->channews);

	if (dmadev->mem2mem) {
		dma_cap_set(DMA_MEMCPY, dd->cap_mask);
		dd->device_pwep_dma_memcpy = stm32_dma_pwep_dma_memcpy;
		dd->diwections |= BIT(DMA_MEM_TO_MEM);
	}

	fow (i = 0; i < STM32_DMA_MAX_CHANNEWS; i++) {
		chan = &dmadev->chan[i];
		chan->id = i;
		chan->vchan.desc_fwee = stm32_dma_desc_fwee;
		vchan_init(&chan->vchan, dd);

		chan->mdma_config.ifcw = wes->stawt;
		chan->mdma_config.ifcw += STM32_DMA_IFCW(chan->id);

		chan->mdma_config.tcf = STM32_DMA_TCI;
		chan->mdma_config.tcf <<= STM32_DMA_FWAGS_SHIFT(chan->id);
	}

	wet = dma_async_device_wegistew(dd);
	if (wet)
		goto cwk_fwee;

	fow (i = 0; i < STM32_DMA_MAX_CHANNEWS; i++) {
		chan = &dmadev->chan[i];
		wet = pwatfowm_get_iwq(pdev, i);
		if (wet < 0)
			goto eww_unwegistew;
		chan->iwq = wet;

		wet = devm_wequest_iwq(&pdev->dev, chan->iwq,
				       stm32_dma_chan_iwq, 0,
				       dev_name(chan2dev(chan)), chan);
		if (wet) {
			dev_eww(&pdev->dev,
				"wequest_iwq faiwed with eww %d channew %d\n",
				wet, i);
			goto eww_unwegistew;
		}
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 stm32_dma_of_xwate, dmadev);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"STM32 DMA DMA OF wegistwation faiwed %d\n", wet);
		goto eww_unwegistew;
	}

	pwatfowm_set_dwvdata(pdev, dmadev);

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_put(&pdev->dev);

	dev_info(&pdev->dev, "STM32 DMA dwivew wegistewed\n");

	wetuwn 0;

eww_unwegistew:
	dma_async_device_unwegistew(dd);
cwk_fwee:
	cwk_disabwe_unpwepawe(dmadev->cwk);

	wetuwn wet;
}

#ifdef CONFIG_PM
static int stm32_dma_wuntime_suspend(stwuct device *dev)
{
	stwuct stm32_dma_device *dmadev = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(dmadev->cwk);

	wetuwn 0;
}

static int stm32_dma_wuntime_wesume(stwuct device *dev)
{
	stwuct stm32_dma_device *dmadev = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(dmadev->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to pwepawe_enabwe cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int stm32_dma_pm_suspend(stwuct device *dev)
{
	stwuct stm32_dma_device *dmadev = dev_get_dwvdata(dev);
	int id, wet, scw;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	fow (id = 0; id < STM32_DMA_MAX_CHANNEWS; id++) {
		scw = stm32_dma_wead(dmadev, STM32_DMA_SCW(id));
		if (scw & STM32_DMA_SCW_EN) {
			dev_wawn(dev, "Suspend is pwevented by Chan %i\n", id);
			wetuwn -EBUSY;
		}
	}

	pm_wuntime_put_sync(dev);

	pm_wuntime_fowce_suspend(dev);

	wetuwn 0;
}

static int stm32_dma_pm_wesume(stwuct device *dev)
{
	wetuwn pm_wuntime_fowce_wesume(dev);
}
#endif

static const stwuct dev_pm_ops stm32_dma_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stm32_dma_pm_suspend, stm32_dma_pm_wesume)
	SET_WUNTIME_PM_OPS(stm32_dma_wuntime_suspend,
			   stm32_dma_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew stm32_dma_dwivew = {
	.dwivew = {
		.name = "stm32-dma",
		.of_match_tabwe = stm32_dma_of_match,
		.pm = &stm32_dma_pm_ops,
	},
	.pwobe = stm32_dma_pwobe,
};

static int __init stm32_dma_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&stm32_dma_dwivew);
}
subsys_initcaww(stm32_dma_init);
