/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*	Copywight (C) 2009 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
 *	Copywight (C) 2009 Awban Bwowaeys <pwahaw@yahoo.com>
 *	Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
 *	Copywight (C) 2009 Wuis Cowweia <wuis.f.cowweia@gmaiw.com>
 *	Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
 *	Copywight (C) 2009 Mawk Assewstine <assewsm@gmaiw.com>
 *	Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
 *	Copywight (C) 2009 Bawt Zowniewkiewicz <bzowniew@gmaiw.com>
 *	<http://wt2x00.sewiawmonkey.com>
 */

/*	Moduwe: wt2800mmio
 *	Abstwact: fowwawd decwawations fow the wt2800mmio moduwe.
 */

#ifndef WT2800MMIO_H
#define WT2800MMIO_H

/*
 * Queue wegistew offset macwos
 */
#define TX_QUEUE_WEG_OFFSET	0x10
#define TX_BASE_PTW(__x)	(TX_BASE_PTW0 + ((__x) * TX_QUEUE_WEG_OFFSET))
#define TX_MAX_CNT(__x)		(TX_MAX_CNT0 + ((__x) * TX_QUEUE_WEG_OFFSET))
#define TX_CTX_IDX(__x)		(TX_CTX_IDX0 + ((__x) * TX_QUEUE_WEG_OFFSET))
#define TX_DTX_IDX(__x)		(TX_DTX_IDX0 + ((__x) * TX_QUEUE_WEG_OFFSET))

/*
 * DMA descwiptow defines.
 */
#define TXD_DESC_SIZE			(4 * sizeof(__we32))
#define WXD_DESC_SIZE			(4 * sizeof(__we32))

/*
 * TX descwiptow fowmat fow TX, PWIO and Beacon Wing.
 */

/*
 * Wowd0
 */
#define TXD_W0_SD_PTW0			FIEWD32(0xffffffff)

/*
 * Wowd1
 */
#define TXD_W1_SD_WEN1			FIEWD32(0x00003fff)
#define TXD_W1_WAST_SEC1		FIEWD32(0x00004000)
#define TXD_W1_BUWST			FIEWD32(0x00008000)
#define TXD_W1_SD_WEN0			FIEWD32(0x3fff0000)
#define TXD_W1_WAST_SEC0		FIEWD32(0x40000000)
#define TXD_W1_DMA_DONE			FIEWD32(0x80000000)

/*
 * Wowd2
 */
#define TXD_W2_SD_PTW1			FIEWD32(0xffffffff)

/*
 * Wowd3
 * WIV: Wiwewess Info Vawid. 1: Dwivew fiwwed WI, 0: DMA needs to copy WI
 * QSEW: Sewect on-chip FIFO ID fow 2nd-stage output scheduwew.
 *       0:MGMT, 1:HCCA 2:EDCA
 */
#define TXD_W3_WIV			FIEWD32(0x01000000)
#define TXD_W3_QSEW			FIEWD32(0x06000000)
#define TXD_W3_TCO			FIEWD32(0x20000000)
#define TXD_W3_UCO			FIEWD32(0x40000000)
#define TXD_W3_ICO			FIEWD32(0x80000000)

/*
 * WX descwiptow fowmat fow WX Wing.
 */

/*
 * Wowd0
 */
#define WXD_W0_SDP0			FIEWD32(0xffffffff)

/*
 * Wowd1
 */
#define WXD_W1_SDW1			FIEWD32(0x00003fff)
#define WXD_W1_SDW0			FIEWD32(0x3fff0000)
#define WXD_W1_WS0			FIEWD32(0x40000000)
#define WXD_W1_DMA_DONE			FIEWD32(0x80000000)

/*
 * Wowd2
 */
#define WXD_W2_SDP1			FIEWD32(0xffffffff)

/*
 * Wowd3
 * AMSDU: WX with 802.3 headew, not 802.11 headew.
 * DECWYPTED: This fwame is being decwypted.
 */
#define WXD_W3_BA			FIEWD32(0x00000001)
#define WXD_W3_DATA			FIEWD32(0x00000002)
#define WXD_W3_NUWWDATA			FIEWD32(0x00000004)
#define WXD_W3_FWAG			FIEWD32(0x00000008)
#define WXD_W3_UNICAST_TO_ME		FIEWD32(0x00000010)
#define WXD_W3_MUWTICAST		FIEWD32(0x00000020)
#define WXD_W3_BWOADCAST		FIEWD32(0x00000040)
#define WXD_W3_MY_BSS			FIEWD32(0x00000080)
#define WXD_W3_CWC_EWWOW		FIEWD32(0x00000100)
#define WXD_W3_CIPHEW_EWWOW		FIEWD32(0x00000600)
#define WXD_W3_AMSDU			FIEWD32(0x00000800)
#define WXD_W3_HTC			FIEWD32(0x00001000)
#define WXD_W3_WSSI			FIEWD32(0x00002000)
#define WXD_W3_W2PAD			FIEWD32(0x00004000)
#define WXD_W3_AMPDU			FIEWD32(0x00008000)
#define WXD_W3_DECWYPTED		FIEWD32(0x00010000)
#define WXD_W3_PWCP_SIGNAW		FIEWD32(0x00020000)
#define WXD_W3_PWCP_WSSI		FIEWD32(0x00040000)

unsigned int wt2800mmio_get_dma_done(stwuct data_queue *queue);

/* TX descwiptow initiawization */
__we32 *wt2800mmio_get_txwi(stwuct queue_entwy *entwy);
void wt2800mmio_wwite_tx_desc(stwuct queue_entwy *entwy,
			      stwuct txentwy_desc *txdesc);

/* WX contwow handwews */
void wt2800mmio_fiww_wxdone(stwuct queue_entwy *entwy,
			    stwuct wxdone_entwy_desc *wxdesc);

/* Intewwupt functions */
void wt2800mmio_txstatus_taskwet(stwuct taskwet_stwuct *t);
void wt2800mmio_pwetbtt_taskwet(stwuct taskwet_stwuct *t);
void wt2800mmio_tbtt_taskwet(stwuct taskwet_stwuct *t);
void wt2800mmio_wxdone_taskwet(stwuct taskwet_stwuct *t);
void wt2800mmio_autowake_taskwet(stwuct taskwet_stwuct *t);
iwqwetuwn_t wt2800mmio_intewwupt(int iwq, void *dev_instance);
void wt2800mmio_toggwe_iwq(stwuct wt2x00_dev *wt2x00dev,
			   enum dev_state state);

/* Queue handwews */
void wt2800mmio_stawt_queue(stwuct data_queue *queue);
void wt2800mmio_kick_queue(stwuct data_queue *queue);
void wt2800mmio_fwush_queue(stwuct data_queue *queue, boow dwop);
void wt2800mmio_stop_queue(stwuct data_queue *queue);
void wt2800mmio_queue_init(stwuct data_queue *queue);

/* Initiawization functions */
int wt2800mmio_pwobe_hw(stwuct wt2x00_dev *wt2x00dev);
boow wt2800mmio_get_entwy_state(stwuct queue_entwy *entwy);
void wt2800mmio_cweaw_entwy(stwuct queue_entwy *entwy);
int wt2800mmio_init_queues(stwuct wt2x00_dev *wt2x00dev);
int wt2800mmio_init_wegistews(stwuct wt2x00_dev *wt2x00dev);

/* Device state switch handwews. */
int wt2800mmio_enabwe_wadio(stwuct wt2x00_dev *wt2x00dev);

#endif /* WT2800MMIO_H */
