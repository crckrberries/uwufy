/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fweescawe MPC5200 Audio DMA dwivew
 */

#ifndef __SOUND_SOC_FSW_MPC5200_DMA_H__
#define __SOUND_SOC_FSW_MPC5200_DMA_H__

#define PSC_STWEAM_NAME_WEN 32

/**
 * psc_ac97_stweam - Data specific to a singwe stweam (pwayback ow captuwe)
 * @active:		fwag indicating if the stweam is active
 * @psc_dma:		pointew back to pawent psc_dma data stwuctuwe
 * @bcom_task:		bestcomm task stwuctuwe
 * @iwq:		iwq numbew fow bestcomm task
 * @pewiod_end:		physicaw addwess of end of DMA wegion
 * @pewiod_next_pt:	physicaw addwess of next DMA buffew to enqueue
 * @pewiod_bytes:	size of DMA pewiod in bytes
 * @ac97_swot_bits:	Enabwe bits fow tuwning on the cowwect AC97 swot
 */
stwuct psc_dma_stweam {
	stwuct snd_pcm_wuntime *wuntime;
	int active;
	stwuct psc_dma *psc_dma;
	stwuct bcom_task *bcom_task;
	int iwq;
	stwuct snd_pcm_substweam *stweam;
	int pewiod_next;
	int pewiod_cuwwent;
	int pewiod_bytes;
	int pewiod_count;

	/* AC97 state */
	u32 ac97_swot_bits;
};

/**
 * psc_dma - Pwivate dwivew data
 * @name: showt name fow this device ("PSC0", "PSC1", etc)
 * @psc_wegs: pointew to the PSC's wegistews
 * @fifo_wegs: pointew to the PSC's FIFO wegistews
 * @iwq: IWQ of this PSC
 * @dev: stwuct device pointew
 * @dai: the CPU DAI fow this device
 * @sicw: Base vawue used in sewiaw intewface contwow wegistew; mode is OWed
 *        with this vawue.
 * @pwayback: Pwayback stweam context data
 * @captuwe: Captuwe stweam context data
 */
stwuct psc_dma {
	chaw name[32];
	stwuct mpc52xx_psc __iomem *psc_wegs;
	stwuct mpc52xx_psc_fifo __iomem *fifo_wegs;
	unsigned int iwq;
	stwuct device *dev;
	spinwock_t wock;
	stwuct mutex mutex;
	u32 sicw;
	uint syscwk;
	int imw;
	int id;
	unsigned int swots;

	/* pew-stweam data */
	stwuct psc_dma_stweam pwayback;
	stwuct psc_dma_stweam captuwe;

	/* Statistics */
	stwuct {
		unsigned wong ovewwun_count;
		unsigned wong undewwun_count;
	} stats;
};

/* Utiwity fow wetwieving psc_dma_stweam stwuctuwe fwom a substweam */
static inwine stwuct psc_dma_stweam *
to_psc_dma_stweam(stwuct snd_pcm_substweam *substweam, stwuct psc_dma *psc_dma)
{
	if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wetuwn &psc_dma->captuwe;
	wetuwn &psc_dma->pwayback;
}

int mpc5200_audio_dma_cweate(stwuct pwatfowm_device *op);
int mpc5200_audio_dma_destwoy(stwuct pwatfowm_device *op);

#endif /* __SOUND_SOC_FSW_MPC5200_DMA_H__ */
