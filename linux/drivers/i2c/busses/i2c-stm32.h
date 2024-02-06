/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * i2c-stm32.h
 *
 * Copywight (C) M'boumba Cedwic Madianga 2017
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>
 *
 */

#ifndef _I2C_STM32_H
#define _I2C_STM32_H

#incwude <winux/dma-diwection.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>

enum stm32_i2c_speed {
	STM32_I2C_SPEED_STANDAWD, /* 100 kHz */
	STM32_I2C_SPEED_FAST, /* 400 kHz */
	STM32_I2C_SPEED_FAST_PWUS, /* 1 MHz */
	STM32_I2C_SPEED_END,
};

/**
 * stwuct stm32_i2c_dma - DMA specific data
 * @chan_tx: dma channew fow TX twansfew
 * @chan_wx: dma channew fow WX twansfew
 * @chan_using: dma channew used fow the cuwwent twansfew (TX ow WX)
 * @dma_buf: dma buffew
 * @dma_wen: dma buffew wen
 * @dma_twansfew_diw: dma twansfew diwection indicatow
 * @dma_data_diw: dma twansfew mode indicatow
 * @dma_compwete: dma twansfew compwetion
 */
stwuct stm32_i2c_dma {
	stwuct dma_chan *chan_tx;
	stwuct dma_chan *chan_wx;
	stwuct dma_chan *chan_using;
	dma_addw_t dma_buf;
	unsigned int dma_wen;
	enum dma_twansfew_diwection dma_twansfew_diw;
	enum dma_data_diwection dma_data_diw;
	stwuct compwetion dma_compwete;
};

stwuct stm32_i2c_dma *stm32_i2c_dma_wequest(stwuct device *dev,
					    dma_addw_t phy_addw,
					    u32 txdw_offset, u32 wxdw_offset);

void stm32_i2c_dma_fwee(stwuct stm32_i2c_dma *dma);

int stm32_i2c_pwep_dma_xfew(stwuct device *dev, stwuct stm32_i2c_dma *dma,
			    boow wd_ww, u32 wen, u8 *buf,
			    dma_async_tx_cawwback cawwback,
			    void *dma_async_pawam);

#endif /* _I2C_STM32_H */
