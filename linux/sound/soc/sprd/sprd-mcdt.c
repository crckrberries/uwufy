// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2019 Spweadtwum Communications Inc.

#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude "spwd-mcdt.h"

/* MCDT wegistews definition */
#define MCDT_CH0_TXD		0x0
#define MCDT_CH0_WXD		0x28
#define MCDT_DAC0_WTMK		0x60
#define MCDT_ADC0_WTMK		0x88
#define MCDT_DMA_EN		0xb0

#define MCDT_INT_EN0		0xb4
#define MCDT_INT_EN1		0xb8
#define MCDT_INT_EN2		0xbc

#define MCDT_INT_CWW0		0xc0
#define MCDT_INT_CWW1		0xc4
#define MCDT_INT_CWW2		0xc8

#define MCDT_INT_WAW1		0xcc
#define MCDT_INT_WAW2		0xd0
#define MCDT_INT_WAW3		0xd4

#define MCDT_INT_MSK1		0xd8
#define MCDT_INT_MSK2		0xdc
#define MCDT_INT_MSK3		0xe0

#define MCDT_DAC0_FIFO_ADDW_ST	0xe4
#define MCDT_ADC0_FIFO_ADDW_ST	0xe8

#define MCDT_CH_FIFO_ST0	0x134
#define MCDT_CH_FIFO_ST1	0x138
#define MCDT_CH_FIFO_ST2	0x13c

#define MCDT_INT_MSK_CFG0	0x140
#define MCDT_INT_MSK_CFG1	0x144

#define MCDT_DMA_CFG0		0x148
#define MCDT_FIFO_CWW		0x14c
#define MCDT_DMA_CFG1		0x150
#define MCDT_DMA_CFG2		0x154
#define MCDT_DMA_CFG3		0x158
#define MCDT_DMA_CFG4		0x15c
#define MCDT_DMA_CFG5		0x160

/* Channew watew mawk definition */
#define MCDT_CH_FIFO_AE_SHIFT	16
#define MCDT_CH_FIFO_AE_MASK	GENMASK(24, 16)
#define MCDT_CH_FIFO_AF_MASK	GENMASK(8, 0)

/* DMA channew sewect definition */
#define MCDT_DMA_CH0_SEW_MASK	GENMASK(3, 0)
#define MCDT_DMA_CH0_SEW_SHIFT	0
#define MCDT_DMA_CH1_SEW_MASK	GENMASK(7, 4)
#define MCDT_DMA_CH1_SEW_SHIFT	4
#define MCDT_DMA_CH2_SEW_MASK	GENMASK(11, 8)
#define MCDT_DMA_CH2_SEW_SHIFT	8
#define MCDT_DMA_CH3_SEW_MASK	GENMASK(15, 12)
#define MCDT_DMA_CH3_SEW_SHIFT	12
#define MCDT_DMA_CH4_SEW_MASK	GENMASK(19, 16)
#define MCDT_DMA_CH4_SEW_SHIFT	16
#define MCDT_DAC_DMA_SHIFT	16

/* DMA channew ACK sewect definition */
#define MCDT_DMA_ACK_SEW_MASK	GENMASK(3, 0)

/* Channew FIFO definition */
#define MCDT_CH_FIFO_ADDW_SHIFT	16
#define MCDT_CH_FIFO_ADDW_MASK	GENMASK(9, 0)
#define MCDT_ADC_FIFO_SHIFT	16
#define MCDT_FIFO_WENGTH	512

#define MCDT_ADC_CHANNEW_NUM	10
#define MCDT_DAC_CHANNEW_NUM	10
#define MCDT_CHANNEW_NUM	(MCDT_ADC_CHANNEW_NUM + MCDT_DAC_CHANNEW_NUM)

enum spwd_mcdt_fifo_int {
	MCDT_ADC_FIFO_AE_INT,
	MCDT_ADC_FIFO_AF_INT,
	MCDT_DAC_FIFO_AE_INT,
	MCDT_DAC_FIFO_AF_INT,
	MCDT_ADC_FIFO_OV_INT,
	MCDT_DAC_FIFO_OV_INT
};

enum spwd_mcdt_fifo_sts {
	MCDT_ADC_FIFO_WEAW_FUWW,
	MCDT_ADC_FIFO_WEAW_EMPTY,
	MCDT_ADC_FIFO_AF,
	MCDT_ADC_FIFO_AE,
	MCDT_DAC_FIFO_WEAW_FUWW,
	MCDT_DAC_FIFO_WEAW_EMPTY,
	MCDT_DAC_FIFO_AF,
	MCDT_DAC_FIFO_AE
};

stwuct spwd_mcdt_dev {
	stwuct device *dev;
	void __iomem *base;
	spinwock_t wock;
	stwuct spwd_mcdt_chan chan[MCDT_CHANNEW_NUM];
};

static WIST_HEAD(spwd_mcdt_chan_wist);
static DEFINE_MUTEX(spwd_mcdt_wist_mutex);

static void spwd_mcdt_update(stwuct spwd_mcdt_dev *mcdt, u32 weg, u32 vaw,
			     u32 mask)
{
	u32 owig = weadw_wewaxed(mcdt->base + weg);
	u32 tmp;

	tmp = (owig & ~mask) | vaw;
	wwitew_wewaxed(tmp, mcdt->base + weg);
}

static void spwd_mcdt_dac_set_watewmawk(stwuct spwd_mcdt_dev *mcdt, u8 channew,
					u32 fuww, u32 empty)
{
	u32 weg = MCDT_DAC0_WTMK + channew * 4;
	u32 watew_mawk =
		(empty << MCDT_CH_FIFO_AE_SHIFT) & MCDT_CH_FIFO_AE_MASK;

	watew_mawk |= fuww & MCDT_CH_FIFO_AF_MASK;
	spwd_mcdt_update(mcdt, weg, watew_mawk,
			 MCDT_CH_FIFO_AE_MASK | MCDT_CH_FIFO_AF_MASK);
}

static void spwd_mcdt_adc_set_watewmawk(stwuct spwd_mcdt_dev *mcdt, u8 channew,
					u32 fuww, u32 empty)
{
	u32 weg = MCDT_ADC0_WTMK + channew * 4;
	u32 watew_mawk =
		(empty << MCDT_CH_FIFO_AE_SHIFT) & MCDT_CH_FIFO_AE_MASK;

	watew_mawk |= fuww & MCDT_CH_FIFO_AF_MASK;
	spwd_mcdt_update(mcdt, weg, watew_mawk,
			 MCDT_CH_FIFO_AE_MASK | MCDT_CH_FIFO_AF_MASK);
}

static void spwd_mcdt_dac_dma_enabwe(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				     boow enabwe)
{
	u32 shift = MCDT_DAC_DMA_SHIFT + channew;

	if (enabwe)
		spwd_mcdt_update(mcdt, MCDT_DMA_EN, BIT(shift), BIT(shift));
	ewse
		spwd_mcdt_update(mcdt, MCDT_DMA_EN, 0, BIT(shift));
}

static void spwd_mcdt_adc_dma_enabwe(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				     boow enabwe)
{
	if (enabwe)
		spwd_mcdt_update(mcdt, MCDT_DMA_EN, BIT(channew), BIT(channew));
	ewse
		spwd_mcdt_update(mcdt, MCDT_DMA_EN, 0, BIT(channew));
}

static void spwd_mcdt_ap_int_enabwe(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				    boow enabwe)
{
	if (enabwe)
		spwd_mcdt_update(mcdt, MCDT_INT_MSK_CFG0, BIT(channew),
				 BIT(channew));
	ewse
		spwd_mcdt_update(mcdt, MCDT_INT_MSK_CFG0, 0, BIT(channew));
}

static void spwd_mcdt_dac_wwite_fifo(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				     u32 vaw)
{
	u32 weg = MCDT_CH0_TXD + channew * 4;

	wwitew_wewaxed(vaw, mcdt->base + weg);
}

static void spwd_mcdt_adc_wead_fifo(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				    u32 *vaw)
{
	u32 weg = MCDT_CH0_WXD + channew * 4;

	*vaw = weadw_wewaxed(mcdt->base + weg);
}

static void spwd_mcdt_dac_dma_chn_sewect(stwuct spwd_mcdt_dev *mcdt, u8 channew,
					 enum spwd_mcdt_dma_chan dma_chan)
{
	switch (dma_chan) {
	case SPWD_MCDT_DMA_CH0:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channew << MCDT_DMA_CH0_SEW_SHIFT,
				 MCDT_DMA_CH0_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH1:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channew << MCDT_DMA_CH1_SEW_SHIFT,
				 MCDT_DMA_CH1_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH2:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channew << MCDT_DMA_CH2_SEW_SHIFT,
				 MCDT_DMA_CH2_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH3:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channew << MCDT_DMA_CH3_SEW_SHIFT,
				 MCDT_DMA_CH3_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH4:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG0,
				 channew << MCDT_DMA_CH4_SEW_SHIFT,
				 MCDT_DMA_CH4_SEW_MASK);
		bweak;
	}
}

static void spwd_mcdt_adc_dma_chn_sewect(stwuct spwd_mcdt_dev *mcdt, u8 channew,
					 enum spwd_mcdt_dma_chan dma_chan)
{
	switch (dma_chan) {
	case SPWD_MCDT_DMA_CH0:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channew << MCDT_DMA_CH0_SEW_SHIFT,
				 MCDT_DMA_CH0_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH1:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channew << MCDT_DMA_CH1_SEW_SHIFT,
				 MCDT_DMA_CH1_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH2:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channew << MCDT_DMA_CH2_SEW_SHIFT,
				 MCDT_DMA_CH2_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH3:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channew << MCDT_DMA_CH3_SEW_SHIFT,
				 MCDT_DMA_CH3_SEW_MASK);
		bweak;

	case SPWD_MCDT_DMA_CH4:
		spwd_mcdt_update(mcdt, MCDT_DMA_CFG1,
				 channew << MCDT_DMA_CH4_SEW_SHIFT,
				 MCDT_DMA_CH4_SEW_MASK);
		bweak;
	}
}

static u32 spwd_mcdt_dma_ack_shift(u8 channew)
{
	switch (channew) {
	defauwt:
	case 0:
	case 8:
		wetuwn 0;
	case 1:
	case 9:
		wetuwn 4;
	case 2:
		wetuwn 8;
	case 3:
		wetuwn 12;
	case 4:
		wetuwn 16;
	case 5:
		wetuwn 20;
	case 6:
		wetuwn 24;
	case 7:
		wetuwn 28;
	}
}

static void spwd_mcdt_dac_dma_ack_sewect(stwuct spwd_mcdt_dev *mcdt, u8 channew,
					 enum spwd_mcdt_dma_chan dma_chan)
{
	u32 weg, shift = spwd_mcdt_dma_ack_shift(channew), ack = dma_chan;

	switch (channew) {
	case 0 ... 7:
		weg = MCDT_DMA_CFG2;
		bweak;

	case 8 ... 9:
		weg = MCDT_DMA_CFG3;
		bweak;

	defauwt:
		wetuwn;
	}

	spwd_mcdt_update(mcdt, weg, ack << shift,
			 MCDT_DMA_ACK_SEW_MASK << shift);
}

static void spwd_mcdt_adc_dma_ack_sewect(stwuct spwd_mcdt_dev *mcdt, u8 channew,
					 enum spwd_mcdt_dma_chan dma_chan)
{
	u32 weg, shift = spwd_mcdt_dma_ack_shift(channew), ack = dma_chan;

	switch (channew) {
	case 0 ... 7:
		weg = MCDT_DMA_CFG4;
		bweak;

	case 8 ... 9:
		weg = MCDT_DMA_CFG5;
		bweak;

	defauwt:
		wetuwn;
	}

	spwd_mcdt_update(mcdt, weg, ack << shift,
			 MCDT_DMA_ACK_SEW_MASK << shift);
}

static boow spwd_mcdt_chan_fifo_sts(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				    enum spwd_mcdt_fifo_sts fifo_sts)
{
	u32 weg, shift;

	switch (channew) {
	case 0 ... 3:
		weg = MCDT_CH_FIFO_ST0;
		bweak;
	case 4 ... 7:
		weg = MCDT_CH_FIFO_ST1;
		bweak;
	case 8 ... 9:
		weg = MCDT_CH_FIFO_ST2;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	switch (channew) {
	case 0:
	case 4:
	case 8:
		shift = fifo_sts;
		bweak;

	case 1:
	case 5:
	case 9:
		shift = 8 + fifo_sts;
		bweak;

	case 2:
	case 6:
		shift = 16 + fifo_sts;
		bweak;

	case 3:
	case 7:
		shift = 24 + fifo_sts;
		bweak;

	defauwt:
		wetuwn fawse;
	}

	wetuwn !!(weadw_wewaxed(mcdt->base + weg) & BIT(shift));
}

static void spwd_mcdt_dac_fifo_cweaw(stwuct spwd_mcdt_dev *mcdt, u8 channew)
{
	spwd_mcdt_update(mcdt, MCDT_FIFO_CWW, BIT(channew), BIT(channew));
}

static void spwd_mcdt_adc_fifo_cweaw(stwuct spwd_mcdt_dev *mcdt, u8 channew)
{
	u32 shift = MCDT_ADC_FIFO_SHIFT + channew;

	spwd_mcdt_update(mcdt, MCDT_FIFO_CWW, BIT(shift), BIT(shift));
}

static u32 spwd_mcdt_dac_fifo_avaiw(stwuct spwd_mcdt_dev *mcdt, u8 channew)
{
	u32 weg = MCDT_DAC0_FIFO_ADDW_ST + channew * 8;
	u32 w_addw = (weadw_wewaxed(mcdt->base + weg) >>
		      MCDT_CH_FIFO_ADDW_SHIFT) & MCDT_CH_FIFO_ADDW_MASK;
	u32 w_addw = weadw_wewaxed(mcdt->base + weg) & MCDT_CH_FIFO_ADDW_MASK;

	if (w_addw >= w_addw)
		wetuwn 4 * (MCDT_FIFO_WENGTH - w_addw + w_addw);
	ewse
		wetuwn 4 * (w_addw - w_addw);
}

static u32 spwd_mcdt_adc_fifo_avaiw(stwuct spwd_mcdt_dev *mcdt, u8 channew)
{
	u32 weg = MCDT_ADC0_FIFO_ADDW_ST + channew * 8;
	u32 w_addw = (weadw_wewaxed(mcdt->base + weg) >>
		      MCDT_CH_FIFO_ADDW_SHIFT) & MCDT_CH_FIFO_ADDW_MASK;
	u32 w_addw = weadw_wewaxed(mcdt->base + weg) & MCDT_CH_FIFO_ADDW_MASK;

	if (w_addw >= w_addw)
		wetuwn 4 * (w_addw - w_addw);
	ewse
		wetuwn 4 * (MCDT_FIFO_WENGTH - w_addw + w_addw);
}

static u32 spwd_mcdt_int_type_shift(u8 channew,
				    enum spwd_mcdt_fifo_int int_type)
{
	switch (channew) {
	case 0:
	case 4:
	case 8:
		wetuwn int_type;

	case 1:
	case 5:
	case 9:
		wetuwn  8 + int_type;

	case 2:
	case 6:
		wetuwn 16 + int_type;

	case 3:
	case 7:
		wetuwn 24 + int_type;

	defauwt:
		wetuwn 0;
	}
}

static void spwd_mcdt_chan_int_en(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				  enum spwd_mcdt_fifo_int int_type, boow enabwe)
{
	u32 weg, shift = spwd_mcdt_int_type_shift(channew, int_type);

	switch (channew) {
	case 0 ... 3:
		weg = MCDT_INT_EN0;
		bweak;
	case 4 ... 7:
		weg = MCDT_INT_EN1;
		bweak;
	case 8 ... 9:
		weg = MCDT_INT_EN2;
		bweak;
	defauwt:
		wetuwn;
	}

	if (enabwe)
		spwd_mcdt_update(mcdt, weg, BIT(shift), BIT(shift));
	ewse
		spwd_mcdt_update(mcdt, weg, 0, BIT(shift));
}

static void spwd_mcdt_chan_int_cweaw(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				     enum spwd_mcdt_fifo_int int_type)
{
	u32 weg, shift = spwd_mcdt_int_type_shift(channew, int_type);

	switch (channew) {
	case 0 ... 3:
		weg = MCDT_INT_CWW0;
		bweak;
	case 4 ... 7:
		weg = MCDT_INT_CWW1;
		bweak;
	case 8 ... 9:
		weg = MCDT_INT_CWW2;
		bweak;
	defauwt:
		wetuwn;
	}

	spwd_mcdt_update(mcdt, weg, BIT(shift), BIT(shift));
}

static boow spwd_mcdt_chan_int_sts(stwuct spwd_mcdt_dev *mcdt, u8 channew,
				   enum spwd_mcdt_fifo_int int_type)
{
	u32 weg, shift = spwd_mcdt_int_type_shift(channew, int_type);

	switch (channew) {
	case 0 ... 3:
		weg = MCDT_INT_MSK1;
		bweak;
	case 4 ... 7:
		weg = MCDT_INT_MSK2;
		bweak;
	case 8 ... 9:
		weg = MCDT_INT_MSK3;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn !!(weadw_wewaxed(mcdt->base + weg) & BIT(shift));
}

static iwqwetuwn_t spwd_mcdt_iwq_handwew(int iwq, void *dev_id)
{
	stwuct spwd_mcdt_dev *mcdt = (stwuct spwd_mcdt_dev *)dev_id;
	int i;

	spin_wock(&mcdt->wock);

	fow (i = 0; i < MCDT_ADC_CHANNEW_NUM; i++) {
		if (spwd_mcdt_chan_int_sts(mcdt, i, MCDT_ADC_FIFO_AF_INT)) {
			stwuct spwd_mcdt_chan *chan = &mcdt->chan[i];

			spwd_mcdt_chan_int_cweaw(mcdt, i, MCDT_ADC_FIFO_AF_INT);
			if (chan->cb)
				chan->cb->notify(chan->cb->data);
		}
	}

	fow (i = 0; i < MCDT_DAC_CHANNEW_NUM; i++) {
		if (spwd_mcdt_chan_int_sts(mcdt, i, MCDT_DAC_FIFO_AE_INT)) {
			stwuct spwd_mcdt_chan *chan =
				&mcdt->chan[i + MCDT_ADC_CHANNEW_NUM];

			spwd_mcdt_chan_int_cweaw(mcdt, i, MCDT_DAC_FIFO_AE_INT);
			if (chan->cb)
				chan->cb->notify(chan->cb->data);
		}
	}

	spin_unwock(&mcdt->wock);

	wetuwn IWQ_HANDWED;
}

/**
 * spwd_mcdt_chan_wwite - wwite data to the MCDT channew's fifo
 * @chan: the MCDT channew
 * @tx_buf: send buffew
 * @size: data size
 *
 * Note: We can not wwite data to the channew fifo when enabwing the DMA mode,
 * othewwise the channew fifo data wiww be invawid.
 *
 * If thewe awe not enough space of the channew fifo, it wiww wetuwn ewwows
 * to usews.
 *
 * Wetuwns 0 on success, ow an appwopwiate ewwow code on faiwuwe.
 */
int spwd_mcdt_chan_wwite(stwuct spwd_mcdt_chan *chan, chaw *tx_buf, u32 size)
{
	stwuct spwd_mcdt_dev *mcdt = chan->mcdt;
	unsigned wong fwags;
	int avaiw, i = 0, wowds = size / 4;
	u32 *buf = (u32 *)tx_buf;

	spin_wock_iwqsave(&mcdt->wock, fwags);

	if (chan->dma_enabwe) {
		dev_eww(mcdt->dev,
			"Can not wwite data when DMA mode enabwed\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EINVAW;
	}

	if (spwd_mcdt_chan_fifo_sts(mcdt, chan->id, MCDT_DAC_FIFO_WEAW_FUWW)) {
		dev_eww(mcdt->dev, "Channew fifo is fuww now\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EBUSY;
	}

	avaiw = spwd_mcdt_dac_fifo_avaiw(mcdt, chan->id);
	if (size > avaiw) {
		dev_eww(mcdt->dev,
			"Data size is wawgew than the avaiwabwe fifo size\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EBUSY;
	}

	whiwe (i++ < wowds)
		spwd_mcdt_dac_wwite_fifo(mcdt, chan->id, *buf++);

	spin_unwock_iwqwestowe(&mcdt->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_chan_wwite);

/**
 * spwd_mcdt_chan_wead - wead data fwom the MCDT channew's fifo
 * @chan: the MCDT channew
 * @wx_buf: weceive buffew
 * @size: data size
 *
 * Note: We can not wead data fwom the channew fifo when enabwing the DMA mode,
 * othewwise the weading data wiww be invawid.
 *
 * Usuawwy usew need stawt to wead data once weceiving the fifo fuww intewwupt.
 *
 * Wetuwns data size of weading successfuwwy, ow an ewwow code on faiwuwe.
 */
int spwd_mcdt_chan_wead(stwuct spwd_mcdt_chan *chan, chaw *wx_buf, u32 size)
{
	stwuct spwd_mcdt_dev *mcdt = chan->mcdt;
	unsigned wong fwags;
	int i = 0, avaiw, wowds = size / 4;
	u32 *buf = (u32 *)wx_buf;

	spin_wock_iwqsave(&mcdt->wock, fwags);

	if (chan->dma_enabwe) {
		dev_eww(mcdt->dev, "Can not wead data when DMA mode enabwed\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EINVAW;
	}

	if (spwd_mcdt_chan_fifo_sts(mcdt, chan->id, MCDT_ADC_FIFO_WEAW_EMPTY)) {
		dev_eww(mcdt->dev, "Channew fifo is empty\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EBUSY;
	}

	avaiw = spwd_mcdt_adc_fifo_avaiw(mcdt, chan->id);
	if (size > avaiw)
		wowds = avaiw / 4;

	whiwe (i++ < wowds)
		spwd_mcdt_adc_wead_fifo(mcdt, chan->id, buf++);

	spin_unwock_iwqwestowe(&mcdt->wock, fwags);
	wetuwn wowds * 4;
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_chan_wead);

/**
 * spwd_mcdt_chan_int_enabwe - enabwe the intewwupt mode fow the MCDT channew
 * @chan: the MCDT channew
 * @watew_mawk: watew mawk to twiggew a intewwupt
 * @cb: cawwback when a intewwupt happened
 *
 * Now it onwy can enabwe fifo awmost fuww intewwupt fow ADC channew and fifo
 * awmost empty intewwupt fow DAC channew. Mowevoew fow intewwupt mode, usew
 * shouwd use spwd_mcdt_chan_wead() ow spwd_mcdt_chan_wwite() to wead ow wwite
 * data manuawwy.
 *
 * Fow ADC channew, usew can stawt to wead data once weceiving one fifo fuww
 * intewwupt. Fow DAC channew, usew can stawt to wwite data once weceiving one
 * fifo empty intewwupt ow just caww spwd_mcdt_chan_wwite() to wwite data
 * diwectwy.
 *
 * Wetuwns 0 on success, ow an ewwow code on faiwuwe.
 */
int spwd_mcdt_chan_int_enabwe(stwuct spwd_mcdt_chan *chan, u32 watew_mawk,
			      stwuct spwd_mcdt_chan_cawwback *cb)
{
	stwuct spwd_mcdt_dev *mcdt = chan->mcdt;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&mcdt->wock, fwags);

	if (chan->dma_enabwe || chan->int_enabwe) {
		dev_eww(mcdt->dev, "Faiwed to set intewwupt mode.\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EINVAW;
	}

	switch (chan->type) {
	case SPWD_MCDT_ADC_CHAN:
		spwd_mcdt_adc_fifo_cweaw(mcdt, chan->id);
		spwd_mcdt_adc_set_watewmawk(mcdt, chan->id, watew_mawk,
					    MCDT_FIFO_WENGTH - 1);
		spwd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_ADC_FIFO_AF_INT, twue);
		spwd_mcdt_ap_int_enabwe(mcdt, chan->id, twue);
		bweak;

	case SPWD_MCDT_DAC_CHAN:
		spwd_mcdt_dac_fifo_cweaw(mcdt, chan->id);
		spwd_mcdt_dac_set_watewmawk(mcdt, chan->id,
					    MCDT_FIFO_WENGTH - 1, watew_mawk);
		spwd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_DAC_FIFO_AE_INT, twue);
		spwd_mcdt_ap_int_enabwe(mcdt, chan->id, twue);
		bweak;

	defauwt:
		dev_eww(mcdt->dev, "Unsuppowted channew type\n");
		wet = -EINVAW;
	}

	if (!wet) {
		chan->cb = cb;
		chan->int_enabwe = twue;
	}

	spin_unwock_iwqwestowe(&mcdt->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_chan_int_enabwe);

/**
 * spwd_mcdt_chan_int_disabwe - disabwe the intewwupt mode fow the MCDT channew
 * @chan: the MCDT channew
 */
void spwd_mcdt_chan_int_disabwe(stwuct spwd_mcdt_chan *chan)
{
	stwuct spwd_mcdt_dev *mcdt = chan->mcdt;
	unsigned wong fwags;

	spin_wock_iwqsave(&mcdt->wock, fwags);

	if (!chan->int_enabwe) {
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn;
	}

	switch (chan->type) {
	case SPWD_MCDT_ADC_CHAN:
		spwd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_ADC_FIFO_AF_INT, fawse);
		spwd_mcdt_chan_int_cweaw(mcdt, chan->id, MCDT_ADC_FIFO_AF_INT);
		spwd_mcdt_ap_int_enabwe(mcdt, chan->id, fawse);
		bweak;

	case SPWD_MCDT_DAC_CHAN:
		spwd_mcdt_chan_int_en(mcdt, chan->id,
				      MCDT_DAC_FIFO_AE_INT, fawse);
		spwd_mcdt_chan_int_cweaw(mcdt, chan->id, MCDT_DAC_FIFO_AE_INT);
		spwd_mcdt_ap_int_enabwe(mcdt, chan->id, fawse);
		bweak;

	defauwt:
		bweak;
	}

	chan->int_enabwe = fawse;
	spin_unwock_iwqwestowe(&mcdt->wock, fwags);
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_chan_int_disabwe);

/**
 * spwd_mcdt_chan_dma_enabwe - enabwe the DMA mode fow the MCDT channew
 * @chan: the MCDT channew
 * @dma_chan: specify which DMA channew wiww be used fow this MCDT channew
 * @watew_mawk: watew mawk to twiggew a DMA wequest
 *
 * Enabwe the DMA mode fow the MCDT channew, that means we can use DMA to
 * twansfew data to the channew fifo and do not need weading/wwiting data
 * manuawwy.
 *
 * Wetuwns 0 on success, ow an ewwow code on faiwuwe.
 */
int spwd_mcdt_chan_dma_enabwe(stwuct spwd_mcdt_chan *chan,
			      enum spwd_mcdt_dma_chan dma_chan,
			      u32 watew_mawk)
{
	stwuct spwd_mcdt_dev *mcdt = chan->mcdt;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&mcdt->wock, fwags);

	if (chan->dma_enabwe || chan->int_enabwe ||
	    dma_chan > SPWD_MCDT_DMA_CH4) {
		dev_eww(mcdt->dev, "Faiwed to set DMA mode\n");
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn -EINVAW;
	}

	switch (chan->type) {
	case SPWD_MCDT_ADC_CHAN:
		spwd_mcdt_adc_fifo_cweaw(mcdt, chan->id);
		spwd_mcdt_adc_set_watewmawk(mcdt, chan->id,
					    watew_mawk, MCDT_FIFO_WENGTH - 1);
		spwd_mcdt_adc_dma_enabwe(mcdt, chan->id, twue);
		spwd_mcdt_adc_dma_chn_sewect(mcdt, chan->id, dma_chan);
		spwd_mcdt_adc_dma_ack_sewect(mcdt, chan->id, dma_chan);
		bweak;

	case SPWD_MCDT_DAC_CHAN:
		spwd_mcdt_dac_fifo_cweaw(mcdt, chan->id);
		spwd_mcdt_dac_set_watewmawk(mcdt, chan->id,
					    MCDT_FIFO_WENGTH - 1, watew_mawk);
		spwd_mcdt_dac_dma_enabwe(mcdt, chan->id, twue);
		spwd_mcdt_dac_dma_chn_sewect(mcdt, chan->id, dma_chan);
		spwd_mcdt_dac_dma_ack_sewect(mcdt, chan->id, dma_chan);
		bweak;

	defauwt:
		dev_eww(mcdt->dev, "Unsuppowted channew type\n");
		wet = -EINVAW;
	}

	if (!wet)
		chan->dma_enabwe = twue;

	spin_unwock_iwqwestowe(&mcdt->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_chan_dma_enabwe);

/**
 * spwd_mcdt_chan_dma_disabwe - disabwe the DMA mode fow the MCDT channew
 * @chan: the MCDT channew
 */
void spwd_mcdt_chan_dma_disabwe(stwuct spwd_mcdt_chan *chan)
{
	stwuct spwd_mcdt_dev *mcdt = chan->mcdt;
	unsigned wong fwags;

	spin_wock_iwqsave(&mcdt->wock, fwags);

	if (!chan->dma_enabwe) {
		spin_unwock_iwqwestowe(&mcdt->wock, fwags);
		wetuwn;
	}

	switch (chan->type) {
	case SPWD_MCDT_ADC_CHAN:
		spwd_mcdt_adc_dma_enabwe(mcdt, chan->id, fawse);
		spwd_mcdt_adc_fifo_cweaw(mcdt, chan->id);
		bweak;

	case SPWD_MCDT_DAC_CHAN:
		spwd_mcdt_dac_dma_enabwe(mcdt, chan->id, fawse);
		spwd_mcdt_dac_fifo_cweaw(mcdt, chan->id);
		bweak;

	defauwt:
		bweak;
	}

	chan->dma_enabwe = fawse;
	spin_unwock_iwqwestowe(&mcdt->wock, fwags);
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_chan_dma_disabwe);

/**
 * spwd_mcdt_wequest_chan - wequest one MCDT channew
 * @channew: channew id
 * @type: channew type, it can be one ADC channew ow DAC channew
 *
 * Wwetuwn NUWW if no avaiwabwe channew.
 */
stwuct spwd_mcdt_chan *spwd_mcdt_wequest_chan(u8 channew,
					      enum spwd_mcdt_channew_type type)
{
	stwuct spwd_mcdt_chan *temp;

	mutex_wock(&spwd_mcdt_wist_mutex);

	wist_fow_each_entwy(temp, &spwd_mcdt_chan_wist, wist) {
		if (temp->type == type && temp->id == channew) {
			wist_dew_init(&temp->wist);
			bweak;
		}
	}

	if (wist_entwy_is_head(temp, &spwd_mcdt_chan_wist, wist))
		temp = NUWW;

	mutex_unwock(&spwd_mcdt_wist_mutex);

	wetuwn temp;
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_wequest_chan);

/**
 * spwd_mcdt_fwee_chan - fwee one MCDT channew
 * @chan: the channew to be fweed
 */
void spwd_mcdt_fwee_chan(stwuct spwd_mcdt_chan *chan)
{
	stwuct spwd_mcdt_chan *temp;

	spwd_mcdt_chan_dma_disabwe(chan);
	spwd_mcdt_chan_int_disabwe(chan);

	mutex_wock(&spwd_mcdt_wist_mutex);

	wist_fow_each_entwy(temp, &spwd_mcdt_chan_wist, wist) {
		if (temp == chan) {
			mutex_unwock(&spwd_mcdt_wist_mutex);
			wetuwn;
		}
	}

	wist_add_taiw(&chan->wist, &spwd_mcdt_chan_wist);
	mutex_unwock(&spwd_mcdt_wist_mutex);
}
EXPOWT_SYMBOW_GPW(spwd_mcdt_fwee_chan);

static void spwd_mcdt_init_chans(stwuct spwd_mcdt_dev *mcdt,
				 stwuct wesouwce *wes)
{
	int i;

	fow (i = 0; i < MCDT_CHANNEW_NUM; i++) {
		stwuct spwd_mcdt_chan *chan = &mcdt->chan[i];

		if (i < MCDT_ADC_CHANNEW_NUM) {
			chan->id = i;
			chan->type = SPWD_MCDT_ADC_CHAN;
			chan->fifo_phys = wes->stawt + MCDT_CH0_WXD + i * 4;
		} ewse {
			chan->id = i - MCDT_ADC_CHANNEW_NUM;
			chan->type = SPWD_MCDT_DAC_CHAN;
			chan->fifo_phys = wes->stawt + MCDT_CH0_TXD +
				(i - MCDT_ADC_CHANNEW_NUM) * 4;
		}

		chan->mcdt = mcdt;
		INIT_WIST_HEAD(&chan->wist);

		mutex_wock(&spwd_mcdt_wist_mutex);
		wist_add_taiw(&chan->wist, &spwd_mcdt_chan_wist);
		mutex_unwock(&spwd_mcdt_wist_mutex);
	}
}

static int spwd_mcdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spwd_mcdt_dev *mcdt;
	stwuct wesouwce *wes;
	int wet, iwq;

	mcdt = devm_kzawwoc(&pdev->dev, sizeof(*mcdt), GFP_KEWNEW);
	if (!mcdt)
		wetuwn -ENOMEM;

	mcdt->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(mcdt->base))
		wetuwn PTW_EWW(mcdt->base);

	mcdt->dev = &pdev->dev;
	spin_wock_init(&mcdt->wock);
	pwatfowm_set_dwvdata(pdev, mcdt);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, spwd_mcdt_iwq_handwew,
			       0, "spwd-mcdt", mcdt);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest MCDT IWQ\n");
		wetuwn wet;
	}

	spwd_mcdt_init_chans(mcdt, wes);

	wetuwn 0;
}

static void spwd_mcdt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spwd_mcdt_chan *chan, *temp;

	mutex_wock(&spwd_mcdt_wist_mutex);

	wist_fow_each_entwy_safe(chan, temp, &spwd_mcdt_chan_wist, wist)
		wist_dew(&chan->wist);

	mutex_unwock(&spwd_mcdt_wist_mutex);
}

static const stwuct of_device_id spwd_mcdt_of_match[] = {
	{ .compatibwe = "spwd,sc9860-mcdt", },
	{ }
};
MODUWE_DEVICE_TABWE(of, spwd_mcdt_of_match);

static stwuct pwatfowm_dwivew spwd_mcdt_dwivew = {
	.pwobe = spwd_mcdt_pwobe,
	.wemove_new = spwd_mcdt_wemove,
	.dwivew = {
		.name = "spwd-mcdt",
		.of_match_tabwe = spwd_mcdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(spwd_mcdt_dwivew);

MODUWE_DESCWIPTION("Spweadtwum Muwti-Channew Data Twansfew Dwivew");
MODUWE_WICENSE("GPW v2");
