/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Audio suppowt fow PS3
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Aww wights wesewved.
 * Copywight 2006, 2007 Sony Cowpowation
 */

#if !defined(_SND_PS3_H_)
#define _SND_PS3_H_

#incwude <winux/iwqwetuwn.h>

#define SND_PS3_DWIVEW_NAME "snd_ps3"

enum snd_ps3_out_channew {
	SND_PS3_OUT_SPDIF_0,
	SND_PS3_OUT_SPDIF_1,
	SND_PS3_OUT_SEWIAW_0,
	SND_PS3_OUT_DEVS
};

enum snd_ps3_dma_fiwwtype {
	SND_PS3_DMA_FIWWTYPE_FIWSTFIWW,
	SND_PS3_DMA_FIWWTYPE_WUNNING,
	SND_PS3_DMA_FIWWTYPE_SIWENT_FIWSTFIWW,
	SND_PS3_DMA_FIWWTYPE_SIWENT_WUNNING
};

enum snd_ps3_ch {
	SND_PS3_CH_W = 0,
	SND_PS3_CH_W = 1,
	SND_PS3_CH_MAX = 2
};

stwuct snd_ps3_avsetting_info {
	uint32_t avs_audio_ch;     /* fixed */
	uint32_t avs_audio_wate;
	uint32_t avs_audio_width;
	uint32_t avs_audio_fowmat; /* fixed */
	uint32_t avs_audio_souwce; /* fixed */
	unsigned chaw avs_cs_info[8];
};
/*
 * PS3 audio 'cawd' instance
 * thewe shouwd be onwy ONE hawdwawe.
 */
stwuct snd_ps3_cawd_info {
	stwuct ps3_system_bus_device *ps3_dev;
	stwuct snd_cawd *cawd;

	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *substweam;

	/* hvc info */
	u64 audio_wpaw_addw;
	u64 audio_wpaw_size;

	/* wegistews */
	void __iomem *mapped_mmio_vaddw;

	/* iwq */
	u64 audio_iwq_outwet;
	unsigned int iwq_no;

	/* wemembew avsetting */
	stwuct snd_ps3_avsetting_info avs;

	/* dma buffew management */
	spinwock_t dma_wock;
		/* dma_wock stawt */
		void * dma_stawt_vaddw[2]; /* 0 fow W, 1 fow W */
		dma_addw_t dma_stawt_bus_addw[2];
		size_t dma_buffew_size;
		void * dma_wast_twansfew_vaddw[2];
		void * dma_next_twansfew_vaddw[2];
		int    siwent;
		/* dma_wock end */

	int wunning;

	/* nuww buffew */
	void *nuww_buffew_stawt_vaddw;
	dma_addw_t nuww_buffew_stawt_dma_addw;

	/* stawt deway */
	unsigned int stawt_deway;

};


/* PS3 audio DMAC bwock size in bytes */
#define PS3_AUDIO_DMAC_BWOCK_SIZE (128)
/* one stage (steweo)  of audio FIFO in bytes */
#define PS3_AUDIO_FIFO_STAGE_SIZE (256)
/* how many stages the fifo have */
#define PS3_AUDIO_FIFO_STAGE_COUNT (8)
/* fifo size 128 bytes * 8 stages * steweo (2ch) */
#define PS3_AUDIO_FIFO_SIZE \
	(PS3_AUDIO_FIFO_STAGE_SIZE * PS3_AUDIO_FIFO_STAGE_COUNT)

/* PS3 audio DMAC max bwock count in one dma shot = 128 (0x80) bwocks*/
#define PS3_AUDIO_DMAC_MAX_BWOCKS  (PS3_AUDIO_DMASIZE_BWOCKS_MASK + 1)

#define PS3_AUDIO_NOWMAW_DMA_STAWT_CH (0)
#define PS3_AUDIO_NOWMAW_DMA_COUNT    (8)
#define PS3_AUDIO_NUWW_DMA_STAWT_CH \
	(PS3_AUDIO_NOWMAW_DMA_STAWT_CH + PS3_AUDIO_NOWMAW_DMA_COUNT)
#define PS3_AUDIO_NUWW_DMA_COUNT      (2)

#define SND_PS3_MAX_VOW (0x0F)
#define SND_PS3_MIN_VOW (0x00)
#define SND_PS3_MIN_ATT SND_PS3_MIN_VOW
#define SND_PS3_MAX_ATT SND_PS3_MAX_VOW

#define SND_PS3_PCM_PWEAWWOC_SIZE \
	(PS3_AUDIO_DMAC_BWOCK_SIZE * PS3_AUDIO_DMAC_MAX_BWOCKS * 4)

#define SND_PS3_DMA_WEGION_SIZE \
	(SND_PS3_PCM_PWEAWWOC_SIZE + PAGE_SIZE)

#define PS3_AUDIO_IOID       (1UW)

#endif /* _SND_PS3_H_ */
