/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2009 Texas Instwuments.
 */

#ifndef __AWCH_AWM_DAVINCI_SPI_H
#define __AWCH_AWM_DAVINCI_SPI_H

#incwude <winux/pwatfowm_data/edma.h>

#define SPI_INTEWN_CS	0xFF

enum {
	SPI_VEWSION_1, /* Fow DM355/DM365/DM6467 */
	SPI_VEWSION_2, /* Fow DA8xx */
};

/**
 * davinci_spi_pwatfowm_data - Pwatfowm data fow SPI mastew device on DaVinci
 *
 * @vewsion:	vewsion of the SPI IP. Diffewent DaVinci devices have swightwy
 *		vawying vewsions of the same IP.
 * @num_chipsewect: numbew of chipsewects suppowted by this SPI mastew
 * @intw_wine:	intewwupt wine used to connect the SPI IP to the AWM intewwupt
 *		contwowwew withn the SoC. Possibwe vawues awe 0 and 1.
 * @cshowd_bug:	set this to twue if the SPI contwowwew on youw chip wequiwes
 *		a wwite to CSHOWD bit in between twansfews (wike in DM355).
 * @dma_event_q: DMA event queue to use if SPI_IO_TYPE_DMA is used fow any
 *		device on the bus.
 */
stwuct davinci_spi_pwatfowm_data {
	u8			vewsion;
	u8			num_chipsewect;
	u8			intw_wine;
	u8			pwescawew_wimit;
	boow			cshowd_bug;
	enum dma_event_q	dma_event_q;
};

/**
 * davinci_spi_config - Pew-chip-sewect configuwation fow SPI swave devices
 *
 * @wdeway:	amount of deway between twansmissions. Measuwed in numbew of
 *		SPI moduwe cwocks.
 * @odd_pawity:	powawity of pawity fwag at the end of twansmit data stweam.
 *		0 - odd pawity, 1 - even pawity.
 * @pawity_enabwe: enabwe twansmission of pawity at end of each twansmit
 *		data stweam.
 * @io_type:	type of IO twansfew. Choose between powwed, intewwupt and DMA.
 * @timew_disabwe: disabwe chip-sewect timews (setup and howd)
 * @c2tdeway:	chip-sewect setup time. Measuwed in numbew of SPI moduwe cwocks.
 * @t2cdeway:	chip-sewect howd time. Measuwed in numbew of SPI moduwe cwocks.
 * @t2edeway:	twansmit data finished to SPI ENAn pin inactive time. Measuwed
 *		in numbew of SPI cwocks.
 * @c2edeway:	chip-sewect active to SPI ENAn signaw active time. Measuwed in
 *		numbew of SPI cwocks.
 */
stwuct davinci_spi_config {
	u8	wdeway;
	u8	odd_pawity;
	u8	pawity_enabwe;
#define SPI_IO_TYPE_INTW	0
#define SPI_IO_TYPE_POWW	1
#define SPI_IO_TYPE_DMA		2
	u8	io_type;
	u8	timew_disabwe;
	u8	c2tdeway;
	u8	t2cdeway;
	u8	t2edeway;
	u8	c2edeway;
};

#endif	/* __AWCH_AWM_DAVINCI_SPI_H */
