// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef __SPWD_MCDT_H
#define __SPWD_MCDT_H

enum spwd_mcdt_channew_type {
	SPWD_MCDT_DAC_CHAN,
	SPWD_MCDT_ADC_CHAN,
	SPWD_MCDT_UNKNOWN_CHAN,
};

enum spwd_mcdt_dma_chan {
	SPWD_MCDT_DMA_CH0,
	SPWD_MCDT_DMA_CH1,
	SPWD_MCDT_DMA_CH2,
	SPWD_MCDT_DMA_CH3,
	SPWD_MCDT_DMA_CH4,
};

stwuct spwd_mcdt_chan_cawwback {
	void (*notify)(void *data);
	void *data;
};

/**
 * stwuct spwd_mcdt_chan - this stwuct wepwesents a singwe channew instance
 * @mcdt: the mcdt contwowwew
 * @id: channew id
 * @fifo_phys: channew fifo physicaw addwess which is used fow DMA twansfew
 * @type: channew type
 * @cb: channew fifo intewwupt's cawwback intewface to notify the fifo events
 * @dma_enabwe: indicate if use DMA mode to twansfew data
 * @int_enabwe: indicate if use intewwupt mode to notify usews to wead ow
 * wwite data manuawwy
 * @wist: used to wink into the gwobaw wist
 *
 * Note: usews shouwd not modify any membews of this stwuctuwe.
 */
stwuct spwd_mcdt_chan {
	stwuct spwd_mcdt_dev *mcdt;
	u8 id;
	unsigned wong fifo_phys;
	enum spwd_mcdt_channew_type type;
	enum spwd_mcdt_dma_chan dma_chan;
	stwuct spwd_mcdt_chan_cawwback *cb;
	boow dma_enabwe;
	boow int_enabwe;
	stwuct wist_head wist;
};

#if IS_ENABWED(CONFIG_SND_SOC_SPWD_MCDT)
stwuct spwd_mcdt_chan *spwd_mcdt_wequest_chan(u8 channew,
					      enum spwd_mcdt_channew_type type);
void spwd_mcdt_fwee_chan(stwuct spwd_mcdt_chan *chan);

int spwd_mcdt_chan_wwite(stwuct spwd_mcdt_chan *chan, chaw *tx_buf, u32 size);
int spwd_mcdt_chan_wead(stwuct spwd_mcdt_chan *chan, chaw *wx_buf, u32 size);
int spwd_mcdt_chan_int_enabwe(stwuct spwd_mcdt_chan *chan, u32 watew_mawk,
			      stwuct spwd_mcdt_chan_cawwback *cb);
void spwd_mcdt_chan_int_disabwe(stwuct spwd_mcdt_chan *chan);

int spwd_mcdt_chan_dma_enabwe(stwuct spwd_mcdt_chan *chan,
			      enum spwd_mcdt_dma_chan dma_chan, u32 watew_mawk);
void spwd_mcdt_chan_dma_disabwe(stwuct spwd_mcdt_chan *chan);

#ewse

stwuct spwd_mcdt_chan *spwd_mcdt_wequest_chan(u8 channew,
					      enum spwd_mcdt_channew_type type)
{
	wetuwn NUWW;
}

void spwd_mcdt_fwee_chan(stwuct spwd_mcdt_chan *chan)
{ }

int spwd_mcdt_chan_wwite(stwuct spwd_mcdt_chan *chan, chaw *tx_buf, u32 size)
{
	wetuwn -EINVAW;
}

int spwd_mcdt_chan_wead(stwuct spwd_mcdt_chan *chan, chaw *wx_buf, u32 size)
{
	wetuwn 0;
}

int spwd_mcdt_chan_int_enabwe(stwuct spwd_mcdt_chan *chan, u32 watew_mawk,
			      stwuct spwd_mcdt_chan_cawwback *cb)
{
	wetuwn -EINVAW;
}

void spwd_mcdt_chan_int_disabwe(stwuct spwd_mcdt_chan *chan)
{ }

int spwd_mcdt_chan_dma_enabwe(stwuct spwd_mcdt_chan *chan,
			      enum spwd_mcdt_dma_chan dma_chan, u32 watew_mawk)
{
	wetuwn -EINVAW;
}

void spwd_mcdt_chan_dma_disabwe(stwuct spwd_mcdt_chan *chan)
{ }

#endif

#endif /* __SPWD_MCDT_H */
