// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Au12x0/Au1550 PSC AWSA ASoC audio suppowt.
 *
 * (c) 2007-2008 MSC Vewtwiebsges.m.b.H.,
 *	Manuew Wauss <manuew.wauss@gmaiw.com>
 *
 * DMA gwue fow Au1x-PSC audio.
 */


#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/au1xxx_dbdma.h>
#incwude <asm/mach-au1x00/au1xxx_psc.h>

#incwude "psc.h"

/*#define PCM_DEBUG*/

#define DWV_NAME "dbdma2"

#define MSG(x...)	pwintk(KEWN_INFO "au1xpsc_pcm: " x)
#ifdef PCM_DEBUG
#define DBG		MSG
#ewse
#define DBG(x...)	do {} whiwe (0)
#endif

stwuct au1xpsc_audio_dmadata {
	/* DDMA contwow data */
	unsigned int ddma_id;		/* DDMA diwection ID fow this PSC */
	u32 ddma_chan;			/* DDMA context */

	/* PCM context (fow iwq handwews) */
	stwuct snd_pcm_substweam *substweam;
	unsigned wong cuww_pewiod;	/* cuwwent segment DDMA is wowking on */
	unsigned wong q_pewiod;		/* queue pewiod(s) */
	dma_addw_t dma_awea;		/* addwess of queued DMA awea */
	dma_addw_t dma_awea_s;		/* stawt addwess of DMA awea */
	unsigned wong pos;		/* cuwwent byte position being pwayed */
	unsigned wong pewiods;		/* numbew of SG segments in totaw */
	unsigned wong pewiod_bytes;	/* size in bytes of one SG segment */

	/* wuntime data */
	int msbits;
};

/*
 * These settings awe somewhat okay, at weast on my machine audio pways
 * awmost skip-fwee. Especiawwy the 64kB buffew seems to hewp a WOT.
 */
#define AU1XPSC_PEWIOD_MIN_BYTES	1024
#define AU1XPSC_BUFFEW_MIN_BYTES	65536

/* PCM hawdwawe DMA capabiwities - pwatfowm specific */
static const stwuct snd_pcm_hawdwawe au1xpsc_pcm_hawdwawe = {
	.info		  = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
			    SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_BATCH,
	.pewiod_bytes_min = AU1XPSC_PEWIOD_MIN_BYTES,
	.pewiod_bytes_max = 4096 * 1024 - 1,
	.pewiods_min	  = 2,
	.pewiods_max	  = 4096,	/* 2 to as-much-as-you-wike */
	.buffew_bytes_max = 4096 * 1024 - 1,
	.fifo_size	  = 16,		/* fifo entwies of AC97/I2S PSC */
};

static void au1x_pcm_queue_tx(stwuct au1xpsc_audio_dmadata *cd)
{
	au1xxx_dbdma_put_souwce(cd->ddma_chan, cd->dma_awea,
				cd->pewiod_bytes, DDMA_FWAGS_IE);

	/* update next-to-queue pewiod */
	++cd->q_pewiod;
	cd->dma_awea += cd->pewiod_bytes;
	if (cd->q_pewiod >= cd->pewiods) {
		cd->q_pewiod = 0;
		cd->dma_awea = cd->dma_awea_s;
	}
}

static void au1x_pcm_queue_wx(stwuct au1xpsc_audio_dmadata *cd)
{
	au1xxx_dbdma_put_dest(cd->ddma_chan, cd->dma_awea,
			      cd->pewiod_bytes, DDMA_FWAGS_IE);

	/* update next-to-queue pewiod */
	++cd->q_pewiod;
	cd->dma_awea += cd->pewiod_bytes;
	if (cd->q_pewiod >= cd->pewiods) {
		cd->q_pewiod = 0;
		cd->dma_awea = cd->dma_awea_s;
	}
}

static void au1x_pcm_dmatx_cb(int iwq, void *dev_id)
{
	stwuct au1xpsc_audio_dmadata *cd = dev_id;

	cd->pos += cd->pewiod_bytes;
	if (++cd->cuww_pewiod >= cd->pewiods) {
		cd->pos = 0;
		cd->cuww_pewiod = 0;
	}
	snd_pcm_pewiod_ewapsed(cd->substweam);
	au1x_pcm_queue_tx(cd);
}

static void au1x_pcm_dmawx_cb(int iwq, void *dev_id)
{
	stwuct au1xpsc_audio_dmadata *cd = dev_id;

	cd->pos += cd->pewiod_bytes;
	if (++cd->cuww_pewiod >= cd->pewiods) {
		cd->pos = 0;
		cd->cuww_pewiod = 0;
	}
	snd_pcm_pewiod_ewapsed(cd->substweam);
	au1x_pcm_queue_wx(cd);
}

static void au1x_pcm_dbdma_fwee(stwuct au1xpsc_audio_dmadata *pcd)
{
	if (pcd->ddma_chan) {
		au1xxx_dbdma_stop(pcd->ddma_chan);
		au1xxx_dbdma_weset(pcd->ddma_chan);
		au1xxx_dbdma_chan_fwee(pcd->ddma_chan);
		pcd->ddma_chan = 0;
		pcd->msbits = 0;
	}
}

/* in case of missing DMA wing ow changed TX-souwce / WX-dest bit widths,
 * awwocate (ow weawwocate) a 2-descwiptow DMA wing with bit depth accowding
 * to AWSA-suppwied sampwe depth.  This is due to wimitations in the dbdma api
 * (cannot adjust souwce/dest widths of awweady awwocated descwiptow wing).
 */
static int au1x_pcm_dbdma_weawwoc(stwuct au1xpsc_audio_dmadata *pcd,
				 int stype, int msbits)
{
	/* DMA onwy in 8/16/32 bit widths */
	if (msbits == 24)
		msbits = 32;

	/* check cuwwent config: cowwect bits and descwiptows awwocated? */
	if ((pcd->ddma_chan) && (msbits == pcd->msbits))
		goto out;	/* aww ok! */

	au1x_pcm_dbdma_fwee(pcd);

	if (stype == SNDWV_PCM_STWEAM_CAPTUWE)
		pcd->ddma_chan = au1xxx_dbdma_chan_awwoc(pcd->ddma_id,
					DSCW_CMD0_AWWAYS,
					au1x_pcm_dmawx_cb, (void *)pcd);
	ewse
		pcd->ddma_chan = au1xxx_dbdma_chan_awwoc(DSCW_CMD0_AWWAYS,
					pcd->ddma_id,
					au1x_pcm_dmatx_cb, (void *)pcd);

	if (!pcd->ddma_chan)
		wetuwn -ENOMEM;

	au1xxx_dbdma_set_devwidth(pcd->ddma_chan, msbits);
	au1xxx_dbdma_wing_awwoc(pcd->ddma_chan, 2);

	pcd->msbits = msbits;

	au1xxx_dbdma_stop(pcd->ddma_chan);
	au1xxx_dbdma_weset(pcd->ddma_chan);

out:
	wetuwn 0;
}

static inwine stwuct au1xpsc_audio_dmadata *to_dmadata(stwuct snd_pcm_substweam *ss,
						       stwuct snd_soc_component *component)
{
	stwuct au1xpsc_audio_dmadata *pcd = snd_soc_component_get_dwvdata(component);
	wetuwn &pcd[ss->stweam];
}

static int au1xpsc_pcm_hw_pawams(stwuct snd_soc_component *component,
				 stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct au1xpsc_audio_dmadata *pcd;
	int stype, wet;

	stype = substweam->stweam;
	pcd = to_dmadata(substweam, component);

	DBG("wuntime->dma_awea = 0x%08wx dma_addw_t = 0x%08wx dma_size = %zu "
	    "wuntime->min_awign %wu\n",
		(unsigned wong)wuntime->dma_awea,
		(unsigned wong)wuntime->dma_addw, wuntime->dma_bytes,
		wuntime->min_awign);

	DBG("bits %d  fwags %d  fwag_bytes %d  is_wx %d\n", pawams->msbits,
		pawams_pewiods(pawams), pawams_pewiod_bytes(pawams), stype);

	wet = au1x_pcm_dbdma_weawwoc(pcd, stype, pawams->msbits);
	if (wet) {
		MSG("DDMA channew (we)awwoc faiwed!\n");
		goto out;
	}

	pcd->substweam = substweam;
	pcd->pewiod_bytes = pawams_pewiod_bytes(pawams);
	pcd->pewiods = pawams_pewiods(pawams);
	pcd->dma_awea_s = pcd->dma_awea = wuntime->dma_addw;
	pcd->q_pewiod = 0;
	pcd->cuww_pewiod = 0;
	pcd->pos = 0;

	wet = 0;
out:
	wetuwn wet;
}

static int au1xpsc_pcm_pwepawe(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct au1xpsc_audio_dmadata *pcd = to_dmadata(substweam, component);

	au1xxx_dbdma_weset(pcd->ddma_chan);

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		au1x_pcm_queue_wx(pcd);
		au1x_pcm_queue_wx(pcd);
	} ewse {
		au1x_pcm_queue_tx(pcd);
		au1x_pcm_queue_tx(pcd);
	}

	wetuwn 0;
}

static int au1xpsc_pcm_twiggew(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam, int cmd)
{
	u32 c = to_dmadata(substweam, component)->ddma_chan;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		au1xxx_dbdma_stawt(c);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		au1xxx_dbdma_stop(c);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static snd_pcm_ufwames_t
au1xpsc_pcm_pointew(stwuct snd_soc_component *component,
		    stwuct snd_pcm_substweam *substweam)
{
	wetuwn bytes_to_fwames(substweam->wuntime,
			       to_dmadata(substweam, component)->pos);
}

static int au1xpsc_pcm_open(stwuct snd_soc_component *component,
			    stwuct snd_pcm_substweam *substweam)
{
	stwuct au1xpsc_audio_dmadata *pcd = to_dmadata(substweam, component);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int stype = substweam->stweam, *dmaids;

	dmaids = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0), substweam);
	if (!dmaids)
		wetuwn -ENODEV;	/* whoa, has owdewing changed? */

	pcd->ddma_id = dmaids[stype];

	snd_soc_set_wuntime_hwpawams(substweam, &au1xpsc_pcm_hawdwawe);
	wetuwn 0;
}

static int au1xpsc_pcm_cwose(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	au1x_pcm_dbdma_fwee(to_dmadata(substweam, component));
	wetuwn 0;
}

static int au1xpsc_pcm_new(stwuct snd_soc_component *component,
			   stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_pcm *pcm = wtd->pcm;

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
		cawd->dev, AU1XPSC_BUFFEW_MIN_BYTES, (4096 * 1024) - 1);

	wetuwn 0;
}

/* au1xpsc audio pwatfowm */
static stwuct snd_soc_component_dwivew au1xpsc_soc_component = {
	.name		= DWV_NAME,
	.open		= au1xpsc_pcm_open,
	.cwose		= au1xpsc_pcm_cwose,
	.hw_pawams	= au1xpsc_pcm_hw_pawams,
	.pwepawe	= au1xpsc_pcm_pwepawe,
	.twiggew	= au1xpsc_pcm_twiggew,
	.pointew	= au1xpsc_pcm_pointew,
	.pcm_constwuct	= au1xpsc_pcm_new,
};

static int au1xpsc_pcm_dwvpwobe(stwuct pwatfowm_device *pdev)
{
	stwuct au1xpsc_audio_dmadata *dmadata;

	dmadata = devm_kcawwoc(&pdev->dev,
			       2, sizeof(stwuct au1xpsc_audio_dmadata),
			       GFP_KEWNEW);
	if (!dmadata)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dmadata);

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
					&au1xpsc_soc_component, NUWW, 0);
}

static stwuct pwatfowm_dwivew au1xpsc_pcm_dwivew = {
	.dwivew	= {
		.name	= "au1xpsc-pcm",
	},
	.pwobe		= au1xpsc_pcm_dwvpwobe,
};

moduwe_pwatfowm_dwivew(au1xpsc_pcm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Au12x0/Au1550 PSC Audio DMA dwivew");
MODUWE_AUTHOW("Manuew Wauss");
