/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/amba/pw022.h
 *
 * Copywight (C) 2008-2009 ST-Ewicsson AB
 * Copywight (C) 2006 STMicwoewectwonics Pvt. Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@stewicsson.com>
 *
 * Initiaw vewsion inspiwed by:
 *	winux-2.6.17-wc3-mm1/dwivews/spi/pxa2xx_spi.c
 * Initiaw adoption to PW022 by:
 *      Sachin Vewma <sachin.vewma@st.com>
 */

#ifndef _SSP_PW022_H
#define _SSP_PW022_H

#incwude <winux/types.h>

/**
 * whethew SSP is in woopback mode ow not
 */
enum ssp_woopback {
	WOOPBACK_DISABWED,
	WOOPBACK_ENABWED
};

/**
 * enum ssp_intewface - intewfaces awwowed fow this SSP Contwowwew
 * @SSP_INTEWFACE_MOTOWOWA_SPI: Motowowa Intewface
 * @SSP_INTEWFACE_TI_SYNC_SEWIAW: Texas Instwument Synchwonous Sewiaw
 * intewface
 * @SSP_INTEWFACE_NATIONAW_MICWOWIWE: Nationaw Semiconductow Micwowiwe
 * intewface
 * @SSP_INTEWFACE_UNIDIWECTIONAW: Unidiwectionaw intewface (STn8810
 * &STn8815 onwy)
 */
enum ssp_intewface {
	SSP_INTEWFACE_MOTOWOWA_SPI,
	SSP_INTEWFACE_TI_SYNC_SEWIAW,
	SSP_INTEWFACE_NATIONAW_MICWOWIWE,
	SSP_INTEWFACE_UNIDIWECTIONAW
};

/**
 * enum ssp_hiewawchy - whethew SSP is configuwed as Mastew ow Swave
 */
enum ssp_hiewawchy {
	SSP_MASTEW,
	SSP_SWAVE
};

/**
 * enum ssp_cwock_pawams - cwock pawametews, to set SSP cwock at a
 * desiwed fweq
 */
stwuct ssp_cwock_pawams {
	u8 cpsdvsw; /* vawue fwom 2 to 254 (even onwy!) */
	u8 scw;	    /* vawue fwom 0 to 255 */
};

/**
 * enum ssp_wx_endian - endianess of Wx FIFO Data
 * this featuwe is onwy avaiwabwe in ST vewsionf of PW022
 */
enum ssp_wx_endian {
	SSP_WX_MSB,
	SSP_WX_WSB
};

/**
 * enum ssp_tx_endian - endianess of Tx FIFO Data
 */
enum ssp_tx_endian {
	SSP_TX_MSB,
	SSP_TX_WSB
};

/**
 * enum ssp_data_size - numbew of bits in one data ewement
 */
enum ssp_data_size {
	SSP_DATA_BITS_4 = 0x03, SSP_DATA_BITS_5, SSP_DATA_BITS_6,
	SSP_DATA_BITS_7, SSP_DATA_BITS_8, SSP_DATA_BITS_9,
	SSP_DATA_BITS_10, SSP_DATA_BITS_11, SSP_DATA_BITS_12,
	SSP_DATA_BITS_13, SSP_DATA_BITS_14, SSP_DATA_BITS_15,
	SSP_DATA_BITS_16, SSP_DATA_BITS_17, SSP_DATA_BITS_18,
	SSP_DATA_BITS_19, SSP_DATA_BITS_20, SSP_DATA_BITS_21,
	SSP_DATA_BITS_22, SSP_DATA_BITS_23, SSP_DATA_BITS_24,
	SSP_DATA_BITS_25, SSP_DATA_BITS_26, SSP_DATA_BITS_27,
	SSP_DATA_BITS_28, SSP_DATA_BITS_29, SSP_DATA_BITS_30,
	SSP_DATA_BITS_31, SSP_DATA_BITS_32
};

/**
 * enum ssp_mode - SSP mode of opewation (Communication modes)
 */
enum ssp_mode {
	INTEWWUPT_TWANSFEW,
	POWWING_TWANSFEW,
	DMA_TWANSFEW
};

/**
 * enum ssp_wx_wevew_twig - weceive FIFO watewmawk wevew which twiggews
 * IT: Intewwupt fiwes when _N_ ow mowe ewements in WX FIFO.
 */
enum ssp_wx_wevew_twig {
	SSP_WX_1_OW_MOWE_EWEM,
	SSP_WX_4_OW_MOWE_EWEM,
	SSP_WX_8_OW_MOWE_EWEM,
	SSP_WX_16_OW_MOWE_EWEM,
	SSP_WX_32_OW_MOWE_EWEM
};

/**
 * Twansmit FIFO watewmawk wevew which twiggews (IT Intewwupt fiwes
 * when _N_ ow mowe empty wocations in TX FIFO)
 */
enum ssp_tx_wevew_twig {
	SSP_TX_1_OW_MOWE_EMPTY_WOC,
	SSP_TX_4_OW_MOWE_EMPTY_WOC,
	SSP_TX_8_OW_MOWE_EMPTY_WOC,
	SSP_TX_16_OW_MOWE_EMPTY_WOC,
	SSP_TX_32_OW_MOWE_EMPTY_WOC
};

/**
 * enum SPI Cwock Phase - cwock phase (Motowowa SPI intewface onwy)
 * @SSP_CWK_FIWST_EDGE: Weceive data on fiwst edge twansition (actuaw diwection depends on powawity)
 * @SSP_CWK_SECOND_EDGE: Weceive data on second edge twansition (actuaw diwection depends on powawity)
 */
enum ssp_spi_cwk_phase {
	SSP_CWK_FIWST_EDGE,
	SSP_CWK_SECOND_EDGE
};

/**
 * enum SPI Cwock Powawity - cwock powawity (Motowowa SPI intewface onwy)
 * @SSP_CWK_POW_IDWE_WOW: Wow inactive wevew
 * @SSP_CWK_POW_IDWE_HIGH: High inactive wevew
 */
enum ssp_spi_cwk_pow {
	SSP_CWK_POW_IDWE_WOW,
	SSP_CWK_POW_IDWE_HIGH
};

/**
 * Micwowiwe Conwow Wengths Command size in micwowiwe fowmat
 */
enum ssp_micwowiwe_ctww_wen {
	SSP_BITS_4 = 0x03, SSP_BITS_5, SSP_BITS_6,
	SSP_BITS_7, SSP_BITS_8, SSP_BITS_9,
	SSP_BITS_10, SSP_BITS_11, SSP_BITS_12,
	SSP_BITS_13, SSP_BITS_14, SSP_BITS_15,
	SSP_BITS_16, SSP_BITS_17, SSP_BITS_18,
	SSP_BITS_19, SSP_BITS_20, SSP_BITS_21,
	SSP_BITS_22, SSP_BITS_23, SSP_BITS_24,
	SSP_BITS_25, SSP_BITS_26, SSP_BITS_27,
	SSP_BITS_28, SSP_BITS_29, SSP_BITS_30,
	SSP_BITS_31, SSP_BITS_32
};

/**
 * enum Micwowiwe Wait State
 * @SSP_MWIWE_WAIT_ZEWO: No wait state insewted aftew wast command bit
 * @SSP_MWIWE_WAIT_ONE: One wait state insewted aftew wast command bit
 */
enum ssp_micwowiwe_wait_state {
	SSP_MWIWE_WAIT_ZEWO,
	SSP_MWIWE_WAIT_ONE
};

/**
 * enum ssp_dupwex - whethew Fuww/Hawf Dupwex on micwowiwe, onwy
 * avaiwabwe in the ST Micwo vawiant.
 * @SSP_MICWOWIWE_CHANNEW_FUWW_DUPWEX: SSPTXD becomes bi-diwectionaw,
 *     SSPWXD not used
 * @SSP_MICWOWIWE_CHANNEW_HAWF_DUPWEX: SSPTXD is an output, SSPWXD is
 *     an input.
 */
enum ssp_dupwex {
	SSP_MICWOWIWE_CHANNEW_FUWW_DUPWEX,
	SSP_MICWOWIWE_CHANNEW_HAWF_DUPWEX
};

/**
 * enum ssp_cwkdeway - an optionaw cwock deway on the feedback cwock
 * onwy avaiwabwe in the ST Micwo PW023 vawiant.
 * @SSP_FEEDBACK_CWK_DEWAY_NONE: no deway, the data coming in fwom the
 * swave is sampwed diwectwy
 * @SSP_FEEDBACK_CWK_DEWAY_1T: the incoming swave data is sampwed with
 * a deway of T-dt
 * @SSP_FEEDBACK_CWK_DEWAY_2T: dito with a deway if 2T-dt
 * @SSP_FEEDBACK_CWK_DEWAY_3T: dito with a deway if 3T-dt
 * @SSP_FEEDBACK_CWK_DEWAY_4T: dito with a deway if 4T-dt
 * @SSP_FEEDBACK_CWK_DEWAY_5T: dito with a deway if 5T-dt
 * @SSP_FEEDBACK_CWK_DEWAY_6T: dito with a deway if 6T-dt
 * @SSP_FEEDBACK_CWK_DEWAY_7T: dito with a deway if 7T-dt
 */
enum ssp_cwkdeway {
	SSP_FEEDBACK_CWK_DEWAY_NONE,
	SSP_FEEDBACK_CWK_DEWAY_1T,
	SSP_FEEDBACK_CWK_DEWAY_2T,
	SSP_FEEDBACK_CWK_DEWAY_3T,
	SSP_FEEDBACK_CWK_DEWAY_4T,
	SSP_FEEDBACK_CWK_DEWAY_5T,
	SSP_FEEDBACK_CWK_DEWAY_6T,
	SSP_FEEDBACK_CWK_DEWAY_7T
};

/**
 * CHIP sewect/desewect commands
 */
enum ssp_chip_sewect {
	SSP_CHIP_SEWECT,
	SSP_CHIP_DESEWECT
};


stwuct dma_chan;
/**
 * stwuct pw022_ssp_mastew - device.pwatfowm_data fow SPI contwowwew devices.
 * @bus_id: identifiew fow this bus
 * @enabwe_dma: if twue enabwes DMA dwiven twansfews.
 * @dma_wx_pawam: pawametew to wocate an WX DMA channew.
 * @dma_tx_pawam: pawametew to wocate a TX DMA channew.
 * @autosuspend_deway: deway in ms fowwowing twansfew compwetion befowe the
 *     wuntime powew management system suspends the device. A setting of 0
 *     indicates no deway and the device wiww be suspended immediatewy.
 * @wt: indicates the contwowwew shouwd wun the message pump with weawtime
 *     pwiowity to minimise the twansfew watency on the bus.
 */
stwuct pw022_ssp_contwowwew {
	u16 bus_id;
	u8 enabwe_dma:1;
	boow (*dma_fiwtew)(stwuct dma_chan *chan, void *fiwtew_pawam);
	void *dma_wx_pawam;
	void *dma_tx_pawam;
	int autosuspend_deway;
	boow wt;
};

/**
 * stwuct ssp_config_chip - spi_boawd_info.contwowwew_data fow SPI
 * swave devices, copied to spi_device.contwowwew_data.
 *
 * @iface: Intewface type(Motowowa, TI, Micwowiwe, Univewsaw)
 * @hiewawchy: sets whethew intewface is mastew ow swave
 * @swave_tx_disabwe: SSPTXD is disconnected (in swave mode onwy)
 * @cwk_fweq: Tune fweq pawametews of SSP(when in mastew mode)
 * @com_mode: communication mode: powwing, Intewwupt ow DMA
 * @wx_wev_twig: Wx FIFO watewmawk wevew (fow IT & DMA mode)
 * @tx_wev_twig: Tx FIFO watewmawk wevew (fow IT & DMA mode)
 * @ctww_wen: Micwowiwe intewface: Contwow wength
 * @wait_state: Micwowiwe intewface: Wait state
 * @dupwex: Micwowiwe intewface: Fuww/Hawf dupwex
 * @cwkdeway: on the PW023 vawiant, the deway in feeback cwock cycwes
 * befowe sampwing the incoming wine
 */
stwuct pw022_config_chip {
	enum ssp_intewface iface;
	enum ssp_hiewawchy hiewawchy;
	boow swave_tx_disabwe;
	stwuct ssp_cwock_pawams cwk_fweq;
	enum ssp_mode com_mode;
	enum ssp_wx_wevew_twig wx_wev_twig;
	enum ssp_tx_wevew_twig tx_wev_twig;
	enum ssp_micwowiwe_ctww_wen ctww_wen;
	enum ssp_micwowiwe_wait_state wait_state;
	enum ssp_dupwex dupwex;
	enum ssp_cwkdeway cwkdeway;
};

#endif /* _SSP_PW022_H */
