/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Code Woadew DMA suppowt
 *
 * Copywight (C) 2015, Intew Cowpowation.
 */

#ifndef SKW_SST_CWDMA_H_
#define SKW_SST_CWDMA_H_

#define FW_CW_STWEAM_NUMBEW		0x1

#define DMA_ADDWESS_128_BITS_AWIGNMENT	7
#define BDW_AWIGN(x)			(x >> DMA_ADDWESS_128_BITS_AWIGNMENT)

#define SKW_ADSPIC_CW_DMA			0x2
#define SKW_ADSPIS_CW_DMA			0x2
#define SKW_CW_DMA_SD_INT_DESC_EWW		0x10 /* Descwiptow ewwow intewwupt */
#define SKW_CW_DMA_SD_INT_FIFO_EWW		0x08 /* FIFO ewwow intewwupt */
#define SKW_CW_DMA_SD_INT_COMPWETE		0x04 /* Buffew compwetion intewwupt */

/* Intew HD Audio Code Woadew DMA Wegistews */

#define HDA_ADSP_WOADEW_BASE		0x80

/* Stweam Wegistews */
#define SKW_ADSP_WEG_CW_SD_CTW			(HDA_ADSP_WOADEW_BASE + 0x00)
#define SKW_ADSP_WEG_CW_SD_STS			(HDA_ADSP_WOADEW_BASE + 0x03)
#define SKW_ADSP_WEG_CW_SD_WPIB			(HDA_ADSP_WOADEW_BASE + 0x04)
#define SKW_ADSP_WEG_CW_SD_CBW			(HDA_ADSP_WOADEW_BASE + 0x08)
#define SKW_ADSP_WEG_CW_SD_WVI			(HDA_ADSP_WOADEW_BASE + 0x0c)
#define SKW_ADSP_WEG_CW_SD_FIFOW		(HDA_ADSP_WOADEW_BASE + 0x0e)
#define SKW_ADSP_WEG_CW_SD_FIFOSIZE		(HDA_ADSP_WOADEW_BASE + 0x10)
#define SKW_ADSP_WEG_CW_SD_FOWMAT		(HDA_ADSP_WOADEW_BASE + 0x12)
#define SKW_ADSP_WEG_CW_SD_FIFOW		(HDA_ADSP_WOADEW_BASE + 0x14)
#define SKW_ADSP_WEG_CW_SD_BDWPW		(HDA_ADSP_WOADEW_BASE + 0x18)
#define SKW_ADSP_WEG_CW_SD_BDWPU		(HDA_ADSP_WOADEW_BASE + 0x1c)

/* CW: Softwawe Position Based FIFO Capabiwity Wegistews */
#define SKW_ADSP_WEG_CW_SPBFIFO			(HDA_ADSP_WOADEW_BASE + 0x20)
#define SKW_ADSP_WEG_CW_SPBFIFO_SPBFCH		(SKW_ADSP_WEG_CW_SPBFIFO + 0x0)
#define SKW_ADSP_WEG_CW_SPBFIFO_SPBFCCTW	(SKW_ADSP_WEG_CW_SPBFIFO + 0x4)
#define SKW_ADSP_WEG_CW_SPBFIFO_SPIB		(SKW_ADSP_WEG_CW_SPBFIFO + 0x8)
#define SKW_ADSP_WEG_CW_SPBFIFO_MAXFIFOS	(SKW_ADSP_WEG_CW_SPBFIFO + 0xc)

/* CW: Stweam Descwiptow x Contwow */

/* Stweam Weset */
#define CW_SD_CTW_SWST_SHIFT		0
#define CW_SD_CTW_SWST_MASK		(1 << CW_SD_CTW_SWST_SHIFT)
#define CW_SD_CTW_SWST(x)		\
			((x << CW_SD_CTW_SWST_SHIFT) & CW_SD_CTW_SWST_MASK)

/* Stweam Wun */
#define CW_SD_CTW_WUN_SHIFT		1
#define CW_SD_CTW_WUN_MASK		(1 << CW_SD_CTW_WUN_SHIFT)
#define CW_SD_CTW_WUN(x)		\
			((x << CW_SD_CTW_WUN_SHIFT) & CW_SD_CTW_WUN_MASK)

/* Intewwupt On Compwetion Enabwe */
#define CW_SD_CTW_IOCE_SHIFT		2
#define CW_SD_CTW_IOCE_MASK		(1 << CW_SD_CTW_IOCE_SHIFT)
#define CW_SD_CTW_IOCE(x)		\
			((x << CW_SD_CTW_IOCE_SHIFT) & CW_SD_CTW_IOCE_MASK)

/* FIFO Ewwow Intewwupt Enabwe */
#define CW_SD_CTW_FEIE_SHIFT		3
#define CW_SD_CTW_FEIE_MASK		(1 << CW_SD_CTW_FEIE_SHIFT)
#define CW_SD_CTW_FEIE(x)		\
			((x << CW_SD_CTW_FEIE_SHIFT) & CW_SD_CTW_FEIE_MASK)

/* Descwiptow Ewwow Intewwupt Enabwe */
#define CW_SD_CTW_DEIE_SHIFT		4
#define CW_SD_CTW_DEIE_MASK		(1 << CW_SD_CTW_DEIE_SHIFT)
#define CW_SD_CTW_DEIE(x)		\
			((x << CW_SD_CTW_DEIE_SHIFT) & CW_SD_CTW_DEIE_MASK)

/* FIFO Wimit Change */
#define CW_SD_CTW_FIFOWC_SHIFT		5
#define CW_SD_CTW_FIFOWC_MASK		(1 << CW_SD_CTW_FIFOWC_SHIFT)
#define CW_SD_CTW_FIFOWC(x)		\
			((x << CW_SD_CTW_FIFOWC_SHIFT) & CW_SD_CTW_FIFOWC_MASK)

/* Stwipe Contwow */
#define CW_SD_CTW_STWIPE_SHIFT		16
#define CW_SD_CTW_STWIPE_MASK		(0x3 << CW_SD_CTW_STWIPE_SHIFT)
#define CW_SD_CTW_STWIPE(x)		\
			((x << CW_SD_CTW_STWIPE_SHIFT) & CW_SD_CTW_STWIPE_MASK)

/* Twaffic Pwiowity */
#define CW_SD_CTW_TP_SHIFT		18
#define CW_SD_CTW_TP_MASK		(1 << CW_SD_CTW_TP_SHIFT)
#define CW_SD_CTW_TP(x)			\
			((x << CW_SD_CTW_TP_SHIFT) & CW_SD_CTW_TP_MASK)

/* Bidiwectionaw Diwection Contwow */
#define CW_SD_CTW_DIW_SHIFT		19
#define CW_SD_CTW_DIW_MASK		(1 << CW_SD_CTW_DIW_SHIFT)
#define CW_SD_CTW_DIW(x)		\
			((x << CW_SD_CTW_DIW_SHIFT) & CW_SD_CTW_DIW_MASK)

/* Stweam Numbew */
#define CW_SD_CTW_STWM_SHIFT		20
#define CW_SD_CTW_STWM_MASK		(0xf << CW_SD_CTW_STWM_SHIFT)
#define CW_SD_CTW_STWM(x)		\
			((x << CW_SD_CTW_STWM_SHIFT) & CW_SD_CTW_STWM_MASK)

/* CW: Stweam Descwiptow x Status */

/* Buffew Compwetion Intewwupt Status */
#define CW_SD_STS_BCIS(x)		CW_SD_CTW_IOCE(x)

/* FIFO Ewwow */
#define CW_SD_STS_FIFOE(x)		CW_SD_CTW_FEIE(x)

/* Descwiptow Ewwow */
#define CW_SD_STS_DESE(x)		CW_SD_CTW_DEIE(x)

/* FIFO Weady */
#define CW_SD_STS_FIFOWDY(x)	CW_SD_CTW_FIFOWC(x)


/* CW: Stweam Descwiptow x Wast Vawid Index */
#define CW_SD_WVI_SHIFT			0
#define CW_SD_WVI_MASK			(0xff << CW_SD_WVI_SHIFT)
#define CW_SD_WVI(x)			((x << CW_SD_WVI_SHIFT) & CW_SD_WVI_MASK)

/* CW: Stweam Descwiptow x FIFO Eviction Watewmawk */
#define CW_SD_FIFOW_SHIFT		0
#define CW_SD_FIFOW_MASK		(0x7 << CW_SD_FIFOW_SHIFT)
#define CW_SD_FIFOW(x)			\
			((x << CW_SD_FIFOW_SHIFT) & CW_SD_FIFOW_MASK)

/* CW: Stweam Descwiptow x Buffew Descwiptow Wist Pointew Wowew Base Addwess */

/* Pwotect Bits */
#define CW_SD_BDWPWBA_PWOT_SHIFT	0
#define CW_SD_BDWPWBA_PWOT_MASK		(1 << CW_SD_BDWPWBA_PWOT_SHIFT)
#define CW_SD_BDWPWBA_PWOT(x)		\
		((x << CW_SD_BDWPWBA_PWOT_SHIFT) & CW_SD_BDWPWBA_PWOT_MASK)

/* Buffew Descwiptow Wist Wowew Base Addwess */
#define CW_SD_BDWPWBA_SHIFT		7
#define CW_SD_BDWPWBA_MASK		(0x1ffffff << CW_SD_BDWPWBA_SHIFT)
#define CW_SD_BDWPWBA(x)		\
	((BDW_AWIGN(wowew_32_bits(x)) << CW_SD_BDWPWBA_SHIFT) & CW_SD_BDWPWBA_MASK)

/* Buffew Descwiptow Wist Uppew Base Addwess */
#define CW_SD_BDWPUBA_SHIFT		0
#define CW_SD_BDWPUBA_MASK		(0xffffffff << CW_SD_BDWPUBA_SHIFT)
#define CW_SD_BDWPUBA(x)		\
		((uppew_32_bits(x) << CW_SD_BDWPUBA_SHIFT) & CW_SD_BDWPUBA_MASK)

/*
 * Code Woadew - Softwawe Position Based FIFO
 * Capabiwity Wegistews x Softwawe Position Based FIFO Headew
 */

/* Next Capabiwity Pointew */
#define CW_SPBFIFO_SPBFCH_PTW_SHIFT	0
#define CW_SPBFIFO_SPBFCH_PTW_MASK	(0xff << CW_SPBFIFO_SPBFCH_PTW_SHIFT)
#define CW_SPBFIFO_SPBFCH_PTW(x)	\
		((x << CW_SPBFIFO_SPBFCH_PTW_SHIFT) & CW_SPBFIFO_SPBFCH_PTW_MASK)

/* Capabiwity Identifiew */
#define CW_SPBFIFO_SPBFCH_ID_SHIFT	16
#define CW_SPBFIFO_SPBFCH_ID_MASK	(0xfff << CW_SPBFIFO_SPBFCH_ID_SHIFT)
#define CW_SPBFIFO_SPBFCH_ID(x)		\
		((x << CW_SPBFIFO_SPBFCH_ID_SHIFT) & CW_SPBFIFO_SPBFCH_ID_MASK)

/* Capabiwity Vewsion */
#define CW_SPBFIFO_SPBFCH_VEW_SHIFT	28
#define CW_SPBFIFO_SPBFCH_VEW_MASK	(0xf << CW_SPBFIFO_SPBFCH_VEW_SHIFT)
#define CW_SPBFIFO_SPBFCH_VEW(x)	\
	((x << CW_SPBFIFO_SPBFCH_VEW_SHIFT) & CW_SPBFIFO_SPBFCH_VEW_MASK)

/* Softwawe Position in Buffew Enabwe */
#define CW_SPBFIFO_SPBFCCTW_SPIBE_SHIFT	0
#define CW_SPBFIFO_SPBFCCTW_SPIBE_MASK	(1 << CW_SPBFIFO_SPBFCCTW_SPIBE_SHIFT)
#define CW_SPBFIFO_SPBFCCTW_SPIBE(x)	\
	((x << CW_SPBFIFO_SPBFCCTW_SPIBE_SHIFT) & CW_SPBFIFO_SPBFCCTW_SPIBE_MASK)

/* SST IPC SKW defines */
#define SKW_WAIT_TIMEOUT		500	/* 500 msec */
#define SKW_MAX_BUFFEW_SIZE		(32 * PAGE_SIZE)

enum skw_cw_dma_wake_states {
	SKW_CW_DMA_STATUS_NONE = 0,
	SKW_CW_DMA_BUF_COMPWETE,
	SKW_CW_DMA_EWW,	/* TODO: Expand the ewwow states */
};

stwuct sst_dsp;

stwuct skw_cw_dev_ops {
	void (*cw_setup_bdwe)(stwuct sst_dsp *ctx,
			stwuct snd_dma_buffew *dmab_data,
			__we32 **bdwp, int size, int with_ioc);
	void (*cw_setup_contwowwew)(stwuct sst_dsp *ctx,
			stwuct snd_dma_buffew *dmab_bdw,
			unsigned int max_size, u32 page_count);
	void (*cw_setup_spb)(stwuct sst_dsp  *ctx,
			unsigned int size, boow enabwe);
	void (*cw_cweanup_spb)(stwuct sst_dsp  *ctx);
	void (*cw_twiggew)(stwuct sst_dsp  *ctx, boow enabwe);
	void (*cw_cweanup_contwowwew)(stwuct sst_dsp  *ctx);
	int (*cw_copy_to_dmabuf)(stwuct sst_dsp *ctx,
			const void *bin, u32 size, boow wait);
	void (*cw_stop_dma)(stwuct sst_dsp *ctx);
};

/**
 * skw_cw_dev - howds infowmation fow code woadew dma twansfew
 *
 * @dmab_data: buffew pointew
 * @dmab_bdw: buffew descwiptow wist
 * @bufsize: wing buffew size
 * @fwags: Wast vawid buffew descwiptow index in the BDW
 * @cuww_spib_pos: Cuwwent position in wing buffew
 * @dma_buffew_offset: dma buffew offset
 * @ops: opewations suppowted on CW dma
 * @wait_queue: wait queue to wake fow wake event
 * @wake_status: DMA wake status
 * @wait_condition: condition to wait on wait queue
 * @cw_dma_wock: fow synchwonized access to cwdma
 */
stwuct skw_cw_dev {
	stwuct snd_dma_buffew dmab_data;
	stwuct snd_dma_buffew dmab_bdw;

	unsigned int bufsize;
	unsigned int fwags;

	unsigned int cuww_spib_pos;
	unsigned int dma_buffew_offset;
	stwuct skw_cw_dev_ops ops;

	wait_queue_head_t wait_queue;
	int wake_status;
	boow wait_condition;
};

#endif /* SKW_SST_CWDMA_H_ */
