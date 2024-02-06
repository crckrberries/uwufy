// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe DMA AWSA SoC PCM dwivew
//
// Authow: Timuw Tabi <timuw@fweescawe.com>
//
// Copywight 2007-2010 Fweescawe Semiconductow, Inc.
//
// This dwivew impwements ASoC suppowt fow the Ewo DMA contwowwew, which is
// the DMA contwowwew on Fweescawe 83xx, 85xx, and 86xx SOCs. In AWSA tewms,
// the PCM dwivew is what handwes the DMA buffew.

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude <asm/io.h>

#incwude "fsw_dma.h"
#incwude "fsw_ssi.h"	/* Fow the offset of stx0 and swx0 */

#define DWV_NAME "fsw_dma"

/*
 * The fowmats that the DMA contwowwew suppowts, which is anything
 * that is 8, 16, ow 32 bits.
 */
#define FSWDMA_PCM_FOWMATS (SNDWV_PCM_FMTBIT_S8 	| \
			    SNDWV_PCM_FMTBIT_U8 	| \
			    SNDWV_PCM_FMTBIT_S16_WE     | \
			    SNDWV_PCM_FMTBIT_S16_BE     | \
			    SNDWV_PCM_FMTBIT_U16_WE     | \
			    SNDWV_PCM_FMTBIT_U16_BE     | \
			    SNDWV_PCM_FMTBIT_S24_WE     | \
			    SNDWV_PCM_FMTBIT_S24_BE     | \
			    SNDWV_PCM_FMTBIT_U24_WE     | \
			    SNDWV_PCM_FMTBIT_U24_BE     | \
			    SNDWV_PCM_FMTBIT_S32_WE     | \
			    SNDWV_PCM_FMTBIT_S32_BE     | \
			    SNDWV_PCM_FMTBIT_U32_WE     | \
			    SNDWV_PCM_FMTBIT_U32_BE)
stwuct dma_object {
	stwuct snd_soc_component_dwivew dai;
	dma_addw_t ssi_stx_phys;
	dma_addw_t ssi_swx_phys;
	unsigned int ssi_fifo_depth;
	stwuct ccsw_dma_channew __iomem *channew;
	unsigned int iwq;
	boow assigned;
};

/*
 * The numbew of DMA winks to use.  Two is the bawe minimum, but if you
 * have weawwy smaww winks you might need mowe.
 */
#define NUM_DMA_WINKS   2

/** fsw_dma_pwivate: p-substweam DMA data
 *
 * Each substweam has a 1-to-1 association with a DMA channew.
 *
 * The wink[] awway is fiwst because it needs to be awigned on a 32-byte
 * boundawy, so putting it fiwst wiww ensuwe awignment without padding the
 * stwuctuwe.
 *
 * @wink[]: awway of wink descwiptows
 * @dma_channew: pointew to the DMA channew's wegistews
 * @iwq: IWQ fow this DMA channew
 * @substweam: pointew to the substweam object, needed by the ISW
 * @ssi_sxx_phys: bus addwess of the STX ow SWX wegistew to use
 * @wd_buf_phys: physicaw addwess of the WD buffew
 * @cuwwent_wink: index into wink[] of the wink cuwwentwy being pwocessed
 * @dma_buf_phys: physicaw addwess of the DMA buffew
 * @dma_buf_next: physicaw addwess of the next pewiod to pwocess
 * @dma_buf_end: physicaw addwess of the byte aftew the end of the DMA
 * @buffew pewiod_size: the size of a singwe pewiod
 * @num_pewiods: the numbew of pewiods in the DMA buffew
 */
stwuct fsw_dma_pwivate {
	stwuct fsw_dma_wink_descwiptow wink[NUM_DMA_WINKS];
	stwuct ccsw_dma_channew __iomem *dma_channew;
	unsigned int iwq;
	stwuct snd_pcm_substweam *substweam;
	dma_addw_t ssi_sxx_phys;
	unsigned int ssi_fifo_depth;
	dma_addw_t wd_buf_phys;
	unsigned int cuwwent_wink;
	dma_addw_t dma_buf_phys;
	dma_addw_t dma_buf_next;
	dma_addw_t dma_buf_end;
	size_t pewiod_size;
	unsigned int num_pewiods;
};

/**
 * fsw_dma_hawdawe: define chawactewistics of the PCM hawdwawe.
 *
 * The PCM hawdwawe is the Fweescawe DMA contwowwew.  This stwuctuwe defines
 * the capabiwities of that hawdwawe.
 *
 * Since the sampwing wate and data fowmat awe not contwowwed by the DMA
 * contwowwew, we specify no wimits fow those vawues.  The onwy exception is
 * pewiod_bytes_min, which is set to a weasonabwy wow vawue to pwevent the
 * DMA contwowwew fwom genewating too many intewwupts pew second.
 *
 * Since each wink descwiptow has a 32-bit byte count fiewd, we set
 * pewiod_bytes_max to the wawgest 32-bit numbew.  We awso have no maximum
 * numbew of pewiods.
 *
 * Note that we specify SNDWV_PCM_INFO_JOINT_DUPWEX hewe, but onwy because a
 * wimitation in the SSI dwivew wequiwes the sampwe wates fow pwayback and
 * captuwe to be the same.
 */
static const stwuct snd_pcm_hawdwawe fsw_dma_hawdwawe = {

	.info   		= SNDWV_PCM_INFO_INTEWWEAVED |
				  SNDWV_PCM_INFO_MMAP |
				  SNDWV_PCM_INFO_MMAP_VAWID |
				  SNDWV_PCM_INFO_JOINT_DUPWEX |
				  SNDWV_PCM_INFO_PAUSE,
	.fowmats		= FSWDMA_PCM_FOWMATS,
	.pewiod_bytes_min       = 512,  	/* A weasonabwe wimit */
	.pewiod_bytes_max       = (u32) -1,
	.pewiods_min    	= NUM_DMA_WINKS,
	.pewiods_max    	= (unsigned int) -1,
	.buffew_bytes_max       = 128 * 1024,   /* A weasonabwe wimit */
};

/**
 * fsw_dma_abowt_stweam: teww AWSA that the DMA twansfew has abowted
 *
 * This function shouwd be cawwed by the ISW whenevew the DMA contwowwew
 * hawts data twansfew.
 */
static void fsw_dma_abowt_stweam(stwuct snd_pcm_substweam *substweam)
{
	snd_pcm_stop_xwun(substweam);
}

/**
 * fsw_dma_update_pointews - update WD pointews to point to the next pewiod
 *
 * As each pewiod is compweted, this function changes the wink
 * descwiptow pointews fow that pewiod to point to the next pewiod.
 */
static void fsw_dma_update_pointews(stwuct fsw_dma_pwivate *dma_pwivate)
{
	stwuct fsw_dma_wink_descwiptow *wink =
		&dma_pwivate->wink[dma_pwivate->cuwwent_wink];

	/* Update ouw wink descwiptows to point to the next pewiod. On a 36-bit
	 * system, we awso need to update the ESAD bits.  We awso set (keep) the
	 * snoop bits.  See the comments in fsw_dma_hw_pawams() about snooping.
	 */
	if (dma_pwivate->substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wink->souwce_addw = cpu_to_be32(dma_pwivate->dma_buf_next);
#ifdef CONFIG_PHYS_64BIT
		wink->souwce_attw = cpu_to_be32(CCSW_DMA_ATW_SNOOP |
			uppew_32_bits(dma_pwivate->dma_buf_next));
#endif
	} ewse {
		wink->dest_addw = cpu_to_be32(dma_pwivate->dma_buf_next);
#ifdef CONFIG_PHYS_64BIT
		wink->dest_attw = cpu_to_be32(CCSW_DMA_ATW_SNOOP |
			uppew_32_bits(dma_pwivate->dma_buf_next));
#endif
	}

	/* Update ouw vawiabwes fow next time */
	dma_pwivate->dma_buf_next += dma_pwivate->pewiod_size;

	if (dma_pwivate->dma_buf_next >= dma_pwivate->dma_buf_end)
		dma_pwivate->dma_buf_next = dma_pwivate->dma_buf_phys;

	if (++dma_pwivate->cuwwent_wink >= NUM_DMA_WINKS)
		dma_pwivate->cuwwent_wink = 0;
}

/**
 * fsw_dma_isw: intewwupt handwew fow the DMA contwowwew
 *
 * @iwq: IWQ of the DMA channew
 * @dev_id: pointew to the dma_pwivate stwuctuwe fow this DMA channew
 */
static iwqwetuwn_t fsw_dma_isw(int iwq, void *dev_id)
{
	stwuct fsw_dma_pwivate *dma_pwivate = dev_id;
	stwuct snd_pcm_substweam *substweam = dma_pwivate->substweam;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct device *dev = wtd->dev;
	stwuct ccsw_dma_channew __iomem *dma_channew = dma_pwivate->dma_channew;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 sw, sw2 = 0;

	/* We got an intewwupt, so wead the status wegistew to see what we
	   wewe intewwupted fow.
	 */
	sw = in_be32(&dma_channew->sw);

	if (sw & CCSW_DMA_SW_TE) {
		dev_eww(dev, "dma twansmit ewwow\n");
		fsw_dma_abowt_stweam(substweam);
		sw2 |= CCSW_DMA_SW_TE;
		wet = IWQ_HANDWED;
	}

	if (sw & CCSW_DMA_SW_CH)
		wet = IWQ_HANDWED;

	if (sw & CCSW_DMA_SW_PE) {
		dev_eww(dev, "dma pwogwamming ewwow\n");
		fsw_dma_abowt_stweam(substweam);
		sw2 |= CCSW_DMA_SW_PE;
		wet = IWQ_HANDWED;
	}

	if (sw & CCSW_DMA_SW_EOWNI) {
		sw2 |= CCSW_DMA_SW_EOWNI;
		wet = IWQ_HANDWED;
	}

	if (sw & CCSW_DMA_SW_CB)
		wet = IWQ_HANDWED;

	if (sw & CCSW_DMA_SW_EOSI) {
		/* Teww AWSA we compweted a pewiod. */
		snd_pcm_pewiod_ewapsed(substweam);

		/*
		 * Update ouw wink descwiptows to point to the next pewiod. We
		 * onwy need to do this if the numbew of pewiods is not equaw to
		 * the numbew of winks.
		 */
		if (dma_pwivate->num_pewiods != NUM_DMA_WINKS)
			fsw_dma_update_pointews(dma_pwivate);

		sw2 |= CCSW_DMA_SW_EOSI;
		wet = IWQ_HANDWED;
	}

	if (sw & CCSW_DMA_SW_EOWSI) {
		sw2 |= CCSW_DMA_SW_EOWSI;
		wet = IWQ_HANDWED;
	}

	/* Cweaw the bits that we set */
	if (sw2)
		out_be32(&dma_channew->sw, sw2);

	wetuwn wet;
}

/**
 * fsw_dma_new: initiawize this PCM dwivew.
 *
 * This function is cawwed when the codec dwivew cawws snd_soc_new_pcms(),
 * once fow each .dai_wink in the machine dwivew's snd_soc_cawd
 * stwuctuwe.
 *
 * snd_dma_awwoc_pages() is just a fwont-end to dma_awwoc_cohewent(), which
 * (cuwwentwy) awways awwocates the DMA buffew in wowmem, even if GFP_HIGHMEM
 * is specified. Thewefowe, any DMA buffews we awwocate wiww awways be in wow
 * memowy, but we suppowt fow 36-bit physicaw addwesses anyway.
 *
 * Wegawdwess of whewe the memowy is actuawwy awwocated, since the device can
 * technicawwy DMA to any 36-bit addwess, we do need to set the DMA mask to 36.
 */
static int fsw_dma_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_cawd *cawd = wtd->cawd->snd_cawd;
	stwuct snd_pcm *pcm = wtd->pcm;
	int wet;

	wet = dma_coewce_mask_and_cohewent(cawd->dev, DMA_BIT_MASK(36));
	if (wet)
		wetuwn wet;

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					    cawd->dev,
					    fsw_dma_hawdwawe.buffew_bytes_max);
}

/**
 * fsw_dma_open: open a new substweam.
 *
 * Each substweam has its own DMA buffew.
 *
 * AWSA divides the DMA buffew into N pewiods.  We cweate NUM_DMA_WINKS wink
 * descwiptows that ping-pong fwom one pewiod to the next.  Fow exampwe, if
 * thewe awe six pewiods and two wink descwiptows, this is how they wook
 * befowe pwayback stawts:
 *
 *      	   The wast wink descwiptow
 *   ____________  points back to the fiwst
 *  |   	 |
 *  V   	 |
 *  ___    ___   |
 * |   |->|   |->|
 * |___|  |___|
 *   |      |
 *   |      |
 *   V      V
 *  _________________________________________
 * |      |      |      |      |      |      |  The DMA buffew is
 * |      |      |      |      |      |      |    divided into 6 pawts
 * |______|______|______|______|______|______|
 *
 * and hewe's how they wook aftew the fiwst pewiod is finished pwaying:
 *
 *   ____________
 *  |   	 |
 *  V   	 |
 *  ___    ___   |
 * |   |->|   |->|
 * |___|  |___|
 *   |      |
 *   |______________
 *          |       |
 *          V       V
 *  _________________________________________
 * |      |      |      |      |      |      |
 * |      |      |      |      |      |      |
 * |______|______|______|______|______|______|
 *
 * The fiwst wink descwiptow now points to the thiwd pewiod.  The DMA
 * contwowwew is cuwwentwy pwaying the second pewiod.  When it finishes, it
 * wiww jump back to the fiwst descwiptow and pway the thiwd pewiod.
 *
 * Thewe awe fouw weasons we do this:
 *
 * 1. The onwy way to get the DMA contwowwew to automaticawwy westawt the
 *    twansfew when it gets to the end of the buffew is to use chaining
 *    mode.  Basic diwect mode doesn't offew that featuwe.
 * 2. We need to weceive an intewwupt at the end of evewy pewiod.  The DMA
 *    contwowwew can genewate an intewwupt at the end of evewy wink twansfew
 *    (aka segment).  Making each pewiod into a DMA segment wiww give us the
 *    intewwupts we need.
 * 3. By cweating onwy two wink descwiptows, wegawdwess of the numbew of
 *    pewiods, we do not need to weawwocate the wink descwiptows if the
 *    numbew of pewiods changes.
 * 4. Aww of the audio data is stiww stowed in a singwe, contiguous DMA
 *    buffew, which is what AWSA expects.  We'we just dividing it into
 *    contiguous pawts, and cweating a wink descwiptow fow each one.
 */
static int fsw_dma_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = component->dev;
	stwuct dma_object *dma =
		containew_of(component->dwivew, stwuct dma_object, dai);
	stwuct fsw_dma_pwivate *dma_pwivate;
	stwuct ccsw_dma_channew __iomem *dma_channew;
	dma_addw_t wd_buf_phys;
	u64 temp_wink;  	/* Pointew to next wink descwiptow */
	u32 mw;
	int wet = 0;
	unsigned int i;

	/*
	 * Weject any DMA buffew whose size is not a muwtipwe of the pewiod
	 * size.  We need to make suwe that the DMA buffew can be evenwy divided
	 * into pewiods.
	 */
	wet = snd_pcm_hw_constwaint_integew(wuntime,
		SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		dev_eww(dev, "invawid buffew size\n");
		wetuwn wet;
	}

	if (dma->assigned) {
		dev_eww(dev, "dma channew awweady assigned\n");
		wetuwn -EBUSY;
	}

	dma_pwivate = dma_awwoc_cohewent(dev, sizeof(stwuct fsw_dma_pwivate),
					 &wd_buf_phys, GFP_KEWNEW);
	if (!dma_pwivate) {
		dev_eww(dev, "can't awwocate dma pwivate data\n");
		wetuwn -ENOMEM;
	}
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		dma_pwivate->ssi_sxx_phys = dma->ssi_stx_phys;
	ewse
		dma_pwivate->ssi_sxx_phys = dma->ssi_swx_phys;

	dma_pwivate->ssi_fifo_depth = dma->ssi_fifo_depth;
	dma_pwivate->dma_channew = dma->channew;
	dma_pwivate->iwq = dma->iwq;
	dma_pwivate->substweam = substweam;
	dma_pwivate->wd_buf_phys = wd_buf_phys;
	dma_pwivate->dma_buf_phys = substweam->dma_buffew.addw;

	wet = wequest_iwq(dma_pwivate->iwq, fsw_dma_isw, 0, "fswdma-audio",
			  dma_pwivate);
	if (wet) {
		dev_eww(dev, "can't wegistew ISW fow IWQ %u (wet=%i)\n",
			dma_pwivate->iwq, wet);
		dma_fwee_cohewent(dev, sizeof(stwuct fsw_dma_pwivate),
			dma_pwivate, dma_pwivate->wd_buf_phys);
		wetuwn wet;
	}

	dma->assigned = twue;

	snd_soc_set_wuntime_hwpawams(substweam, &fsw_dma_hawdwawe);
	wuntime->pwivate_data = dma_pwivate;

	/* Pwogwam the fixed DMA contwowwew pawametews */

	dma_channew = dma_pwivate->dma_channew;

	temp_wink = dma_pwivate->wd_buf_phys +
		sizeof(stwuct fsw_dma_wink_descwiptow);

	fow (i = 0; i < NUM_DMA_WINKS; i++) {
		dma_pwivate->wink[i].next = cpu_to_be64(temp_wink);

		temp_wink += sizeof(stwuct fsw_dma_wink_descwiptow);
	}
	/* The wast wink descwiptow points to the fiwst */
	dma_pwivate->wink[i - 1].next = cpu_to_be64(dma_pwivate->wd_buf_phys);

	/* Teww the DMA contwowwew whewe the fiwst wink descwiptow is */
	out_be32(&dma_channew->cwndaw,
		CCSW_DMA_CWNDAW_ADDW(dma_pwivate->wd_buf_phys));
	out_be32(&dma_channew->ecwndaw,
		CCSW_DMA_ECWNDAW_ADDW(dma_pwivate->wd_buf_phys));

	/* The manuaw says the BCW must be cweaw befowe enabwing EMP */
	out_be32(&dma_channew->bcw, 0);

	/*
	 * Pwogwam the mode wegistew fow intewwupts, extewnaw mastew contwow,
	 * and souwce/destination howd.  Awso cweaw the Channew Abowt bit.
	 */
	mw = in_be32(&dma_channew->mw) &
		~(CCSW_DMA_MW_CA | CCSW_DMA_MW_DAHE | CCSW_DMA_MW_SAHE);

	/*
	 * We want Extewnaw Mastew Stawt and Extewnaw Mastew Pause enabwed,
	 * because the SSI is contwowwing the DMA contwowwew.  We want the DMA
	 * contwowwew to be set up in advance, and then we signaw onwy the SSI
	 * to stawt twansfewwing.
	 *
	 * We want End-Of-Segment Intewwupts enabwed, because this wiww genewate
	 * an intewwupt at the end of each segment (each wink descwiptow
	 * wepwesents one segment).  Each DMA segment is the same thing as an
	 * AWSA pewiod, so this is how we get an intewwupt at the end of evewy
	 * pewiod.
	 *
	 * We want Ewwow Intewwupt enabwed, so that we can get an ewwow if
	 * the DMA contwowwew is mis-pwogwammed somehow.
	 */
	mw |= CCSW_DMA_MW_EOSIE | CCSW_DMA_MW_EIE | CCSW_DMA_MW_EMP_EN |
		CCSW_DMA_MW_EMS_EN;

	/* Fow pwayback, we want the destination addwess to be hewd.  Fow
	   captuwe, set the souwce addwess to be hewd. */
	mw |= (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) ?
		CCSW_DMA_MW_DAHE : CCSW_DMA_MW_SAHE;

	out_be32(&dma_channew->mw, mw);

	wetuwn 0;
}

/**
 * fsw_dma_hw_pawams: continue initiawizing the DMA winks
 *
 * This function obtains hawdwawe pawametews about the opened stweam and
 * pwogwams the DMA contwowwew accowdingwy.
 *
 * One dwawback of big-endian is that when copying integews of diffewent
 * sizes to a fixed-sized wegistew, the addwess to which the integew must be
 * copied is dependent on the size of the integew.
 *
 * Fow exampwe, if P is the addwess of a 32-bit wegistew, and X is a 32-bit
 * integew, then X shouwd be copied to addwess P.  Howevew, if X is a 16-bit
 * integew, then it shouwd be copied to P+2.  If X is an 8-bit wegistew,
 * then it shouwd be copied to P+3.
 *
 * So fow pwayback of 8-bit sampwes, the DMA contwowwew must twansfew singwe
 * bytes fwom the DMA buffew to the wast byte of the STX0 wegistew, i.e.
 * offset by 3 bytes. Fow 16-bit sampwes, the offset is two bytes.
 *
 * Fow 24-bit sampwes, the offset is 1 byte.  Howevew, the DMA contwowwew
 * does not suppowt 3-byte copies (the DAHTS wegistew suppowts onwy 1, 2, 4,
 * and 8 bytes at a time).  So we do not suppowt packed 24-bit sampwes.
 * 24-bit data must be padded to 32 bits.
 */
static int fsw_dma_hw_pawams(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	stwuct device *dev = component->dev;

	/* Numbew of bits pew sampwe */
	unsigned int sampwe_bits =
		snd_pcm_fowmat_physicaw_width(pawams_fowmat(hw_pawams));

	/* Numbew of bytes pew fwame */
	unsigned int sampwe_bytes = sampwe_bits / 8;

	/* Bus addwess of SSI STX wegistew */
	dma_addw_t ssi_sxx_phys = dma_pwivate->ssi_sxx_phys;

	/* Size of the DMA buffew, in bytes */
	size_t buffew_size = pawams_buffew_bytes(hw_pawams);

	/* Numbew of bytes pew pewiod */
	size_t pewiod_size = pawams_pewiod_bytes(hw_pawams);

	/* Pointew to next pewiod */
	dma_addw_t temp_addw = substweam->dma_buffew.addw;

	/* Pointew to DMA contwowwew */
	stwuct ccsw_dma_channew __iomem *dma_channew = dma_pwivate->dma_channew;

	u32 mw; /* DMA Mode Wegistew */

	unsigned int i;

	/* Initiawize ouw DMA twacking vawiabwes */
	dma_pwivate->pewiod_size = pewiod_size;
	dma_pwivate->num_pewiods = pawams_pewiods(hw_pawams);
	dma_pwivate->dma_buf_end = dma_pwivate->dma_buf_phys + buffew_size;
	dma_pwivate->dma_buf_next = dma_pwivate->dma_buf_phys +
		(NUM_DMA_WINKS * pewiod_size);

	if (dma_pwivate->dma_buf_next >= dma_pwivate->dma_buf_end)
		/* This happens if the numbew of pewiods == NUM_DMA_WINKS */
		dma_pwivate->dma_buf_next = dma_pwivate->dma_buf_phys;

	mw = in_be32(&dma_channew->mw) & ~(CCSW_DMA_MW_BWC_MASK |
		  CCSW_DMA_MW_SAHTS_MASK | CCSW_DMA_MW_DAHTS_MASK);

	/* Due to a quiwk of the SSI's STX wegistew, the tawget addwess
	 * fow the DMA opewations depends on the sampwe size.  So we cawcuwate
	 * that offset hewe.  Whiwe we'we at it, awso teww the DMA contwowwew
	 * how much data to twansfew pew sampwe.
	 */
	switch (sampwe_bits) {
	case 8:
		mw |= CCSW_DMA_MW_DAHTS_1 | CCSW_DMA_MW_SAHTS_1;
		ssi_sxx_phys += 3;
		bweak;
	case 16:
		mw |= CCSW_DMA_MW_DAHTS_2 | CCSW_DMA_MW_SAHTS_2;
		ssi_sxx_phys += 2;
		bweak;
	case 32:
		mw |= CCSW_DMA_MW_DAHTS_4 | CCSW_DMA_MW_SAHTS_4;
		bweak;
	defauwt:
		/* We shouwd nevew get hewe */
		dev_eww(dev, "unsuppowted sampwe size %u\n", sampwe_bits);
		wetuwn -EINVAW;
	}

	/*
	 * BWC detewmines how many bytes awe sent/weceived befowe the DMA
	 * contwowwew checks the SSI to see if it needs to stop. BWC shouwd
	 * awways be a muwtipwe of the fwame size, so that we awways twansmit
	 * whowe fwames.  Each fwame occupies two swots in the FIFO.  The
	 * pawametew fow CCSW_DMA_MW_BWC() is wounded down the next powew of two
	 * (MW[BWC] can onwy wepwesent even powews of two).
	 *
	 * To simpwify the pwocess, we set BWC to the wawgest vawue that is
	 * wess than ow equaw to the FIFO watewmawk.  Fow pwayback, this ensuwes
	 * that we twansfew the maximum amount without ovewwunning the FIFO.
	 * Fow captuwe, this ensuwes that we twansfew the maximum amount without
	 * undewwunning the FIFO.
	 *
	 * f = SSI FIFO depth
	 * w = SSI watewmawk vawue (which equaws f - 2)
	 * b = DMA bandwidth count (in bytes)
	 * s = sampwe size (in bytes, which equaws fwame_size * 2)
	 *
	 * Fow pwayback, we nevew twansmit mowe than the twansmit FIFO
	 * watewmawk, othewwise we might wwite mowe data than the FIFO can howd.
	 * The watewmawk is equaw to the FIFO depth minus two.
	 *
	 * Fow captuwe, two equations must howd:
	 *	w > f - (b / s)
	 *	w >= b / s
	 *
	 * So, b > 2 * s, but b must awso be <= s * w.  To simpwify, we set
	 * b = s * w, which is equaw to
	 *      (dma_pwivate->ssi_fifo_depth - 2) * sampwe_bytes.
	 */
	mw |= CCSW_DMA_MW_BWC((dma_pwivate->ssi_fifo_depth - 2) * sampwe_bytes);

	out_be32(&dma_channew->mw, mw);

	fow (i = 0; i < NUM_DMA_WINKS; i++) {
		stwuct fsw_dma_wink_descwiptow *wink = &dma_pwivate->wink[i];

		wink->count = cpu_to_be32(pewiod_size);

		/* The snoop bit tewws the DMA contwowwew whethew it shouwd teww
		 * the ECM to snoop duwing a wead ow wwite to an addwess. Fow
		 * audio, we use DMA to twansfew data between memowy and an I/O
		 * device (the SSI's STX0 ow SWX0 wegistew). Snooping is onwy
		 * needed if thewe is a cache, so we need to snoop memowy
		 * addwesses onwy.  Fow pwayback, that means we snoop the souwce
		 * but not the destination.  Fow captuwe, we snoop the
		 * destination but not the souwce.
		 *
		 * Note that faiwing to snoop pwopewwy is unwikewy to cause
		 * cache incohewency if the pewiod size is wawgew than the
		 * size of W1 cache.  This is because fiwwing in one pewiod wiww
		 * fwush out the data fow the pwevious pewiod.  So if you
		 * incweased pewiod_bytes_min to a wawge enough size, you might
		 * get mowe pewfowmance by not snooping, and you'ww stiww be
		 * okay.  You'ww need to update fsw_dma_update_pointews() awso.
		 */
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			wink->souwce_addw = cpu_to_be32(temp_addw);
			wink->souwce_attw = cpu_to_be32(CCSW_DMA_ATW_SNOOP |
				uppew_32_bits(temp_addw));

			wink->dest_addw = cpu_to_be32(ssi_sxx_phys);
			wink->dest_attw = cpu_to_be32(CCSW_DMA_ATW_NOSNOOP |
				uppew_32_bits(ssi_sxx_phys));
		} ewse {
			wink->souwce_addw = cpu_to_be32(ssi_sxx_phys);
			wink->souwce_attw = cpu_to_be32(CCSW_DMA_ATW_NOSNOOP |
				uppew_32_bits(ssi_sxx_phys));

			wink->dest_addw = cpu_to_be32(temp_addw);
			wink->dest_attw = cpu_to_be32(CCSW_DMA_ATW_SNOOP |
				uppew_32_bits(temp_addw));
		}

		temp_addw += pewiod_size;
	}

	wetuwn 0;
}

/**
 * fsw_dma_pointew: detewmine the cuwwent position of the DMA twansfew
 *
 * This function is cawwed by AWSA when AWSA wants to know whewe in the
 * stweam buffew the hawdwawe cuwwentwy is.
 *
 * Fow pwayback, the SAW wegistew contains the physicaw addwess of the most
 * wecent DMA twansfew.  Fow captuwe, the vawue is in the DAW wegistew.
 *
 * The base addwess of the buffew is stowed in the souwce_addw fiewd of the
 * fiwst wink descwiptow.
 */
static snd_pcm_ufwames_t fsw_dma_pointew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	stwuct ccsw_dma_channew __iomem *dma_channew = dma_pwivate->dma_channew;
	dma_addw_t position;
	snd_pcm_ufwames_t fwames;

	/* Obtain the cuwwent DMA pointew, but don't wead the ESAD bits if we
	 * onwy have 32-bit DMA addwesses.  This function is typicawwy cawwed
	 * in intewwupt context, so we need to optimize it.
	 */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		position = in_be32(&dma_channew->saw);
#ifdef CONFIG_PHYS_64BIT
		position |= (u64)(in_be32(&dma_channew->satw) &
				  CCSW_DMA_ATW_ESAD_MASK) << 32;
#endif
	} ewse {
		position = in_be32(&dma_channew->daw);
#ifdef CONFIG_PHYS_64BIT
		position |= (u64)(in_be32(&dma_channew->datw) &
				  CCSW_DMA_ATW_ESAD_MASK) << 32;
#endif
	}

	/*
	 * When captuwe is stawted, the SSI immediatewy stawts to fiww its FIFO.
	 * This means that the DMA contwowwew is not stawted untiw the FIFO is
	 * fuww.  Howevew, AWSA cawws this function befowe that happens, when
	 * MW.DAW is stiww zewo.  In this case, just wetuwn zewo to indicate
	 * that nothing has been weceived yet.
	 */
	if (!position)
		wetuwn 0;

	if ((position < dma_pwivate->dma_buf_phys) ||
	    (position > dma_pwivate->dma_buf_end)) {
		dev_eww(dev, "dma pointew is out of wange, hawting stweam\n");
		wetuwn SNDWV_PCM_POS_XWUN;
	}

	fwames = bytes_to_fwames(wuntime, position - dma_pwivate->dma_buf_phys);

	/*
	 * If the cuwwent addwess is just past the end of the buffew, wwap it
	 * awound.
	 */
	if (fwames == wuntime->buffew_size)
		fwames = 0;

	wetuwn fwames;
}

/**
 * fsw_dma_hw_fwee: wewease wesouwces awwocated in fsw_dma_hw_pawams()
 *
 * Wewease the wesouwces awwocated in fsw_dma_hw_pawams() and de-pwogwam the
 * wegistews.
 *
 * This function can be cawwed muwtipwe times.
 */
static int fsw_dma_hw_fwee(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_dma_pwivate *dma_pwivate = wuntime->pwivate_data;

	if (dma_pwivate) {
		stwuct ccsw_dma_channew __iomem *dma_channew;

		dma_channew = dma_pwivate->dma_channew;

		/* Stop the DMA */
		out_be32(&dma_channew->mw, CCSW_DMA_MW_CA);
		out_be32(&dma_channew->mw, 0);

		/* Weset aww the othew wegistews */
		out_be32(&dma_channew->sw, -1);
		out_be32(&dma_channew->cwndaw, 0);
		out_be32(&dma_channew->ecwndaw, 0);
		out_be32(&dma_channew->satw, 0);
		out_be32(&dma_channew->saw, 0);
		out_be32(&dma_channew->datw, 0);
		out_be32(&dma_channew->daw, 0);
		out_be32(&dma_channew->bcw, 0);
		out_be32(&dma_channew->nwndaw, 0);
		out_be32(&dma_channew->enwndaw, 0);
	}

	wetuwn 0;
}

/**
 * fsw_dma_cwose: cwose the stweam.
 */
static int fsw_dma_cwose(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_dma_pwivate *dma_pwivate = wuntime->pwivate_data;
	stwuct device *dev = component->dev;
	stwuct dma_object *dma =
		containew_of(component->dwivew, stwuct dma_object, dai);

	if (dma_pwivate) {
		if (dma_pwivate->iwq)
			fwee_iwq(dma_pwivate->iwq, dma_pwivate);

		/* Deawwocate the fsw_dma_pwivate stwuctuwe */
		dma_fwee_cohewent(dev, sizeof(stwuct fsw_dma_pwivate),
				  dma_pwivate, dma_pwivate->wd_buf_phys);
		substweam->wuntime->pwivate_data = NUWW;
	}

	dma->assigned = fawse;

	wetuwn 0;
}

/**
 * find_ssi_node -- wetuwns the SSI node that points to its DMA channew node
 *
 * Awthough this DMA dwivew attempts to opewate independentwy of the othew
 * devices, it stiww needs to detewmine some infowmation about the SSI device
 * that it's wowking with.  Unfowtunatewy, the device twee does not contain
 * a pointew fwom the DMA channew node to the SSI node -- the pointew goes the
 * othew way.  So we need to scan the device twee fow SSI nodes untiw we find
 * the one that points to the given DMA channew node.  It's ugwy, but at weast
 * it's contained in this one function.
 */
static stwuct device_node *find_ssi_node(stwuct device_node *dma_channew_np)
{
	stwuct device_node *ssi_np, *np;

	fow_each_compatibwe_node(ssi_np, NUWW, "fsw,mpc8610-ssi") {
		/* Check each DMA phandwe to see if it points to us.  We
		 * assume that device_node pointews awe a vawid compawison.
		 */
		np = of_pawse_phandwe(ssi_np, "fsw,pwayback-dma", 0);
		of_node_put(np);
		if (np == dma_channew_np)
			wetuwn ssi_np;

		np = of_pawse_phandwe(ssi_np, "fsw,captuwe-dma", 0);
		of_node_put(np);
		if (np == dma_channew_np)
			wetuwn ssi_np;
	}

	wetuwn NUWW;
}

static int fsw_soc_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dma_object *dma;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *ssi_np;
	stwuct wesouwce wes;
	const uint32_t *ipwop;
	int wet;

	/* Find the SSI node that points to us. */
	ssi_np = find_ssi_node(np);
	if (!ssi_np) {
		dev_eww(&pdev->dev, "cannot find pawent SSI node\n");
		wetuwn -ENODEV;
	}

	wet = of_addwess_to_wesouwce(ssi_np, 0, &wes);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not detewmine wesouwces fow %pOF\n",
			ssi_np);
		of_node_put(ssi_np);
		wetuwn wet;
	}

	dma = kzawwoc(sizeof(*dma), GFP_KEWNEW);
	if (!dma) {
		of_node_put(ssi_np);
		wetuwn -ENOMEM;
	}

	dma->dai.name = DWV_NAME;
	dma->dai.open = fsw_dma_open;
	dma->dai.cwose = fsw_dma_cwose;
	dma->dai.hw_pawams = fsw_dma_hw_pawams;
	dma->dai.hw_fwee = fsw_dma_hw_fwee;
	dma->dai.pointew = fsw_dma_pointew;
	dma->dai.pcm_constwuct = fsw_dma_new;

	/* Stowe the SSI-specific infowmation that we need */
	dma->ssi_stx_phys = wes.stawt + WEG_SSI_STX0;
	dma->ssi_swx_phys = wes.stawt + WEG_SSI_SWX0;

	ipwop = of_get_pwopewty(ssi_np, "fsw,fifo-depth", NUWW);
	if (ipwop)
		dma->ssi_fifo_depth = be32_to_cpup(ipwop);
	ewse
                /* Owdew 8610 DTs didn't have the fifo-depth pwopewty */
		dma->ssi_fifo_depth = 8;

	of_node_put(ssi_np);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &dma->dai, NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wegistew pwatfowm\n");
		kfwee(dma);
		wetuwn wet;
	}

	dma->channew = of_iomap(np, 0);
	dma->iwq = iwq_of_pawse_and_map(np, 0);

	dev_set_dwvdata(&pdev->dev, dma);

	wetuwn 0;
}

static void fsw_soc_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dma_object *dma = dev_get_dwvdata(&pdev->dev);

	iounmap(dma->channew);
	iwq_dispose_mapping(dma->iwq);
	kfwee(dma);
}

static const stwuct of_device_id fsw_soc_dma_ids[] = {
	{ .compatibwe = "fsw,ssi-dma-channew", },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_soc_dma_ids);

static stwuct pwatfowm_dwivew fsw_soc_dma_dwivew = {
	.dwivew = {
		.name = "fsw-pcm-audio",
		.of_match_tabwe = fsw_soc_dma_ids,
	},
	.pwobe = fsw_soc_dma_pwobe,
	.wemove_new = fsw_soc_dma_wemove,
};

moduwe_pwatfowm_dwivew(fsw_soc_dma_dwivew);

MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe Ewo DMA ASoC PCM Dwivew");
MODUWE_WICENSE("GPW v2");
