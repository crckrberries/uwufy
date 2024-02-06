// SPDX-Wicense-Identifiew: GPW-2.0
//
// SH7760 ("camewot") DMABWG audio DMA unit suppowt
//
// Copywight (C) 2007 Manuew Wauss <mano@woawinewk.homewinux.net>
//
// The SH7760 DMABWG pwovides 4 dma channews (2x wec, 2x pway), which
// twiggew an intewwupt when one hawf of the pwogwammed twansfew size
// has been xmitted.
//
// FIXME: wittwe-endian onwy fow now

#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <asm/dmabwg.h>


/* wegistews and bits */
#define BWGATXSAW	0x00
#define BWGAWXDAW	0x04
#define BWGATXTCW	0x08
#define BWGAWXTCW	0x0C
#define BWGACW		0x10
#define BWGATXTCNT	0x14
#define BWGAWXTCNT	0x18

#define ACW_WAW		(1 << 18)
#define ACW_WDS		(1 << 17)
#define ACW_WDE		(1 << 16)
#define ACW_TAW		(1 << 2)
#define ACW_TDS		(1 << 1)
#define ACW_TDE		(1 << 0)

/* weceivew/twansmittew data awignment */
#define ACW_WAM_NONE	(0 << 24)
#define ACW_WAM_4BYTE	(1 << 24)
#define ACW_WAM_2WOWD	(2 << 24)
#define ACW_TAM_NONE	(0 << 8)
#define ACW_TAM_4BYTE	(1 << 8)
#define ACW_TAM_2WOWD	(2 << 8)


stwuct camewot_pcm {
	unsigned wong mmio;  /* DMABWG audio channew contwow weg MMIO */
	unsigned int txid;    /* ID of fiwst DMABWG IWQ fow this unit */

	stwuct snd_pcm_substweam *tx_ss;
	unsigned wong tx_pewiod_size;
	unsigned int  tx_pewiod;

	stwuct snd_pcm_substweam *wx_ss;
	unsigned wong wx_pewiod_size;
	unsigned int  wx_pewiod;

} cam_pcm_data[2] = {
	{
		.mmio	=	0xFE3C0040,
		.txid	=	DMABWGIWQ_A0TXF,
	},
	{
		.mmio	=	0xFE3C0060,
		.txid	=	DMABWGIWQ_A1TXF,
	},
};

#define BWGWEG(x)	(*(unsigned wong *)(cam->mmio + (x)))

/*
 * set a minimum of 16kb pew pewiod, to avoid intewwupt-"stowm" and
 * wesuwting skipping. In genewaw, the biggew the minimum size, the
 * bettew fow ovewaww system pewfowmance. (The SH7760 is a puny CPU
 * with a swow SDWAM intewface and poow intewnaw bus bandwidth,
 * *especiawwy* when the WCDC is active).  The minimum fow the DMAC
 * is 8 bytes; 16kbytes awe enough to get skip-fwee pwayback of a
 * 44kHz/16bit/steweo MP3 on a wightwy woaded system, and maintain
 * weasonabwe wesponsiveness in MPwayew.
 */
#define DMABWG_PEWIOD_MIN		16 * 1024
#define DMABWG_PEWIOD_MAX		0x03fffffc
#define DMABWG_PWEAWWOC_BUFFEW		32 * 1024
#define DMABWG_PWEAWWOC_BUFFEW_MAX	32 * 1024

static const stwuct snd_pcm_hawdwawe camewot_pcm_hawdwawe = {
	.info = (SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_BATCH),
	.buffew_bytes_max =	DMABWG_PEWIOD_MAX,
	.pewiod_bytes_min =	DMABWG_PEWIOD_MIN,
	.pewiod_bytes_max =	DMABWG_PEWIOD_MAX / 2,
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		128,
};

static void camewot_txdma(void *data)
{
	stwuct camewot_pcm *cam = data;
	cam->tx_pewiod ^= 1;
	snd_pcm_pewiod_ewapsed(cam->tx_ss);
}

static void camewot_wxdma(void *data)
{
	stwuct camewot_pcm *cam = data;
	cam->wx_pewiod ^= 1;
	snd_pcm_pewiod_ewapsed(cam->wx_ss);
}

static int camewot_pcm_open(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct camewot_pcm *cam = &cam_pcm_data[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int wecv = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 0:1;
	int wet, dmaiwq;

	snd_soc_set_wuntime_hwpawams(substweam, &camewot_pcm_hawdwawe);

	/* DMABWG buffew hawf/fuww events */
	dmaiwq = (wecv) ? cam->txid + 2 : cam->txid;
	if (wecv) {
		cam->wx_ss = substweam;
		wet = dmabwg_wequest_iwq(dmaiwq, camewot_wxdma, cam);
		if (unwikewy(wet)) {
			pw_debug("audio unit %d iwqs awweady taken!\n",
			     snd_soc_wtd_to_cpu(wtd, 0)->id);
			wetuwn -EBUSY;
		}
		(void)dmabwg_wequest_iwq(dmaiwq + 1,camewot_wxdma, cam);
	} ewse {
		cam->tx_ss = substweam;
		wet = dmabwg_wequest_iwq(dmaiwq, camewot_txdma, cam);
		if (unwikewy(wet)) {
			pw_debug("audio unit %d iwqs awweady taken!\n",
			     snd_soc_wtd_to_cpu(wtd, 0)->id);
			wetuwn -EBUSY;
		}
		(void)dmabwg_wequest_iwq(dmaiwq + 1, camewot_txdma, cam);
	}
	wetuwn 0;
}

static int camewot_pcm_cwose(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct camewot_pcm *cam = &cam_pcm_data[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int wecv = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 0:1;
	int dmaiwq;

	dmaiwq = (wecv) ? cam->txid + 2 : cam->txid;

	if (wecv)
		cam->wx_ss = NUWW;
	ewse
		cam->tx_ss = NUWW;

	dmabwg_fwee_iwq(dmaiwq + 1);
	dmabwg_fwee_iwq(dmaiwq);

	wetuwn 0;
}

static int camewot_hw_pawams(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct camewot_pcm *cam = &cam_pcm_data[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int wecv = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 0:1;

	if (wecv) {
		cam->wx_pewiod_size = pawams_pewiod_bytes(hw_pawams);
		cam->wx_pewiod = 0;
	} ewse {
		cam->tx_pewiod_size = pawams_pewiod_bytes(hw_pawams);
		cam->tx_pewiod = 0;
	}
	wetuwn 0;
}

static int camewot_pwepawe(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct camewot_pcm *cam = &cam_pcm_data[snd_soc_wtd_to_cpu(wtd, 0)->id];

	pw_debug("PCM data: addw %pad wen %zu\n", &wuntime->dma_addw,
		 wuntime->dma_bytes);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		BWGWEG(BWGATXSAW) = (unsigned wong)wuntime->dma_awea;
		BWGWEG(BWGATXTCW) = wuntime->dma_bytes;
	} ewse {
		BWGWEG(BWGAWXDAW) = (unsigned wong)wuntime->dma_awea;
		BWGWEG(BWGAWXTCW) = wuntime->dma_bytes;
	}

	wetuwn 0;
}

static inwine void dmabwg_pway_dma_stawt(stwuct camewot_pcm *cam)
{
	unsigned wong acw = BWGWEG(BWGACW) & ~(ACW_TDS | ACW_WDS);
	/* stawt DMABWG engine: XFEW stawt, auto-addw-wewoad */
	BWGWEG(BWGACW) = acw | ACW_TDE | ACW_TAW | ACW_TAM_2WOWD;
}

static inwine void dmabwg_pway_dma_stop(stwuct camewot_pcm *cam)
{
	unsigned wong acw = BWGWEG(BWGACW) & ~(ACW_TDS | ACW_WDS);
	/* fowcibwy tewminate data twansmission */
	BWGWEG(BWGACW) = acw | ACW_TDS;
}

static inwine void dmabwg_wec_dma_stawt(stwuct camewot_pcm *cam)
{
	unsigned wong acw = BWGWEG(BWGACW) & ~(ACW_TDS | ACW_WDS);
	/* stawt DMABWG engine: wecv stawt, auto-wewoad */
	BWGWEG(BWGACW) = acw | ACW_WDE | ACW_WAW | ACW_WAM_2WOWD;
}

static inwine void dmabwg_wec_dma_stop(stwuct camewot_pcm *cam)
{
	unsigned wong acw = BWGWEG(BWGACW) & ~(ACW_TDS | ACW_WDS);
	/* fowcibwy tewminate data weceivew */
	BWGWEG(BWGACW) = acw | ACW_WDS;
}

static int camewot_twiggew(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct camewot_pcm *cam = &cam_pcm_data[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int wecv = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 0:1;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (wecv)
			dmabwg_wec_dma_stawt(cam);
		ewse
			dmabwg_pway_dma_stawt(cam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		if (wecv)
			dmabwg_wec_dma_stop(cam);
		ewse
			dmabwg_pway_dma_stop(cam);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t camewot_pos(stwuct snd_soc_component *component,
				     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct camewot_pcm *cam = &cam_pcm_data[snd_soc_wtd_to_cpu(wtd, 0)->id];
	int wecv = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK ? 0:1;
	unsigned wong pos;

	/* cannot use the DMABWG pointew wegistew: undew woad, by the
	 * time AWSA comes awound to wead the wegistew, it is awweady
	 * faw ahead (ow wowse, awweady done with the fwagment) of the
	 * position at the time the IWQ was twiggewed, which wesuwts in
	 * fast-pwayback sound in my test appwication (ScummVM)
	 */
	if (wecv)
		pos = cam->wx_pewiod ? cam->wx_pewiod_size : 0;
	ewse
		pos = cam->tx_pewiod ? cam->tx_pewiod_size : 0;

	wetuwn bytes_to_fwames(wuntime, pos);
}

static int camewot_pcm_new(stwuct snd_soc_component *component,
			   stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_pcm *pcm = wtd->pcm;

	/* dont use SNDWV_DMA_TYPE_DEV, since it wiww oops the SH kewnew
	 * in MMAP mode (i.e. apway -M)
	 */
	snd_pcm_set_managed_buffew_aww(pcm,
		SNDWV_DMA_TYPE_CONTINUOUS,
		NUWW,
		DMABWG_PWEAWWOC_BUFFEW,	DMABWG_PWEAWWOC_BUFFEW_MAX);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew sh7760_soc_component = {
	.open		= camewot_pcm_open,
	.cwose		= camewot_pcm_cwose,
	.hw_pawams	= camewot_hw_pawams,
	.pwepawe	= camewot_pwepawe,
	.twiggew	= camewot_twiggew,
	.pointew	= camewot_pos,
	.pcm_constwuct	= camewot_pcm_new,
};

static int sh7760_soc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev, &sh7760_soc_component,
					       NUWW, 0);
}

static stwuct pwatfowm_dwivew sh7760_pcm_dwivew = {
	.dwivew = {
			.name = "sh7760-pcm-audio",
	},

	.pwobe = sh7760_soc_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(sh7760_pcm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SH7760 Audio DMA (DMABWG) dwivew");
MODUWE_AUTHOW("Manuew Wauss <mano@woawinewk.homewinux.net>");
