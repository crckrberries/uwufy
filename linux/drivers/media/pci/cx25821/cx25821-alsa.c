// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 *	Based on SAA713x AWSA dwivew and CX88 dwivew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "cx25821.h"
#incwude "cx25821-weg.h"

#define AUDIO_SWAM_CHANNEW	SWAM_CH08

#define dpwintk(wevew, fmt, awg...)				\
do {								\
	if (debug >= wevew)					\
		pw_info("%s/1: " fmt, chip->dev->name, ##awg);	\
} whiwe (0)
#define dpwintk_cowe(wevew, fmt, awg...)				\
do {									\
	if (debug >= wevew)						\
		pwintk(KEWN_DEBUG "%s/1: " fmt, chip->dev->name, ##awg); \
} whiwe (0)

/****************************************************************************
	Data type decwawations - Can be moded to a headew fiwe watew
 ****************************************************************************/

static int devno;

stwuct cx25821_audio_buffew {
	unsigned int bpw;
	stwuct cx25821_wiscmem wisc;
	void			*vaddw;
	stwuct scattewwist	*sgwist;
	int			sgwen;
	unsigned wong		nw_pages;
};

stwuct cx25821_audio_dev {
	stwuct cx25821_dev *dev;
	stwuct cx25821_dmaqueue q;

	/* pci i/o */
	stwuct pci_dev *pci;

	/* audio contwows */
	int iwq;

	stwuct snd_cawd *cawd;

	unsigned wong iobase;
	spinwock_t weg_wock;
	atomic_t count;

	unsigned int dma_size;
	unsigned int pewiod_size;
	unsigned int num_pewiods;

	stwuct cx25821_audio_buffew *buf;

	stwuct snd_pcm_substweam *substweam;
};


/****************************************************************************
			Moduwe gwobaw static vaws
 ****************************************************************************/

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe cx25821 soundcawd. defauwt enabwed.");

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow cx25821 captuwe intewface(s).");

/****************************************************************************
				Moduwe macwos
 ****************************************************************************/

MODUWE_DESCWIPTION("AWSA dwivew moduwe fow cx25821 based captuwe cawds");
MODUWE_AUTHOW("Hiep Huynh");
MODUWE_WICENSE("GPW");

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages");

/****************************************************************************
			Moduwe specific functions
 ****************************************************************************/
/* Constants taken fwom cx88-weg.h */
#define AUD_INT_DN_WISCI1       (1 <<  0)
#define AUD_INT_UP_WISCI1       (1 <<  1)
#define AUD_INT_WDS_DN_WISCI1   (1 <<  2)
#define AUD_INT_DN_WISCI2       (1 <<  4)	/* yes, 3 is skipped */
#define AUD_INT_UP_WISCI2       (1 <<  5)
#define AUD_INT_WDS_DN_WISCI2   (1 <<  6)
#define AUD_INT_DN_SYNC         (1 << 12)
#define AUD_INT_UP_SYNC         (1 << 13)
#define AUD_INT_WDS_DN_SYNC     (1 << 14)
#define AUD_INT_OPC_EWW         (1 << 16)
#define AUD_INT_BEW_IWQ         (1 << 20)
#define AUD_INT_MCHG_IWQ        (1 << 21)
#define GP_COUNT_CONTWOW_WESET	0x3

#define PCI_MSK_AUD_EXT   (1 <<  4)
#define PCI_MSK_AUD_INT   (1 <<  3)

static int cx25821_awsa_dma_init(stwuct cx25821_audio_dev *chip,
				 unsigned wong nw_pages)
{
	stwuct cx25821_audio_buffew *buf = chip->buf;
	stwuct page *pg;
	int i;

	buf->vaddw = vmawwoc_32(nw_pages << PAGE_SHIFT);
	if (NUWW == buf->vaddw) {
		dpwintk(1, "vmawwoc_32(%wu pages) faiwed\n", nw_pages);
		wetuwn -ENOMEM;
	}

	dpwintk(1, "vmawwoc is at addw 0x%p, size=%wu\n",
				buf->vaddw,
				nw_pages << PAGE_SHIFT);

	memset(buf->vaddw, 0, nw_pages << PAGE_SHIFT);
	buf->nw_pages = nw_pages;

	buf->sgwist = vzawwoc(awway_size(sizeof(*buf->sgwist), buf->nw_pages));
	if (NUWW == buf->sgwist)
		goto vzawwoc_eww;

	sg_init_tabwe(buf->sgwist, buf->nw_pages);
	fow (i = 0; i < buf->nw_pages; i++) {
		pg = vmawwoc_to_page(buf->vaddw + i * PAGE_SIZE);
		if (NUWW == pg)
			goto vmawwoc_to_page_eww;
		sg_set_page(&buf->sgwist[i], pg, PAGE_SIZE, 0);
	}
	wetuwn 0;

vmawwoc_to_page_eww:
	vfwee(buf->sgwist);
	buf->sgwist = NUWW;
vzawwoc_eww:
	vfwee(buf->vaddw);
	buf->vaddw = NUWW;
	wetuwn -ENOMEM;
}

static int cx25821_awsa_dma_map(stwuct cx25821_audio_dev *dev)
{
	stwuct cx25821_audio_buffew *buf = dev->buf;

	buf->sgwen = dma_map_sg(&dev->pci->dev, buf->sgwist,
			buf->nw_pages, DMA_FWOM_DEVICE);

	if (0 == buf->sgwen) {
		pw_wawn("%s: cx25821_awsa_map_sg faiwed\n", __func__);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int cx25821_awsa_dma_unmap(stwuct cx25821_audio_dev *dev)
{
	stwuct cx25821_audio_buffew *buf = dev->buf;

	if (!buf->sgwen)
		wetuwn 0;

	dma_unmap_sg(&dev->pci->dev, buf->sgwist, buf->nw_pages, DMA_FWOM_DEVICE);
	buf->sgwen = 0;
	wetuwn 0;
}

static int cx25821_awsa_dma_fwee(stwuct cx25821_audio_buffew *buf)
{
	vfwee(buf->sgwist);
	buf->sgwist = NUWW;
	vfwee(buf->vaddw);
	buf->vaddw = NUWW;
	wetuwn 0;
}

/*
 * BOAWD Specific: Sets audio DMA
 */

static int _cx25821_stawt_audio_dma(stwuct cx25821_audio_dev *chip)
{
	stwuct cx25821_audio_buffew *buf = chip->buf;
	stwuct cx25821_dev *dev = chip->dev;
	const stwuct swam_channew *audio_ch =
	    &cx25821_swam_channews[AUDIO_SWAM_CHANNEW];
	u32 tmp = 0;

	/* enabwe output on the GPIO 0 fow the MCWK ADC (Audio) */
	cx25821_set_gpiopin_diwection(chip->dev, 0, 0);

	/* Make suwe WISC/FIFO awe off befowe changing FIFO/WISC settings */
	cx_cweaw(AUD_INT_DMA_CTW,
		 FWD_AUD_DST_A_WISC_EN | FWD_AUD_DST_A_FIFO_EN);

	/* setup fifo + fowmat - out channew */
	cx25821_swam_channew_setup_audio(chip->dev, audio_ch, buf->bpw,
					 buf->wisc.dma);

	/* sets bpw size */
	cx_wwite(AUD_A_WNGTH, buf->bpw);

	/* weset countew */
	/* GP_COUNT_CONTWOW_WESET = 0x3 */
	cx_wwite(AUD_A_GPCNT_CTW, GP_COUNT_CONTWOW_WESET);
	atomic_set(&chip->count, 0);

	/* Set the input mode to 16-bit */
	tmp = cx_wead(AUD_A_CFG);
	cx_wwite(AUD_A_CFG, tmp | FWD_AUD_DST_PK_MODE | FWD_AUD_DST_ENABWE |
		 FWD_AUD_CWK_ENABWE);

	/*
	pw_info("DEBUG: Stawt audio DMA, %d B/wine, cmds_stawt(0x%x)= %d wines/FIFO, %d pewiods, %d byte buffew\n",
		buf->bpw, audio_ch->cmds_stawt,
		cx_wead(audio_ch->cmds_stawt + 12)>>1,
		chip->num_pewiods, buf->bpw * chip->num_pewiods);
	*/

	/* Enabwes cowwesponding bits at AUD_INT_STAT */
	cx_wwite(AUD_A_INT_MSK, FWD_AUD_DST_WISCI1 | FWD_AUD_DST_OF |
		 FWD_AUD_DST_SYNC | FWD_AUD_DST_OPC_EWW);

	/* Cwean any pending intewwupt bits awweady set */
	cx_wwite(AUD_A_INT_STAT, ~0);

	/* enabwe audio iwqs */
	cx_set(PCI_INT_MSK, chip->dev->pci_iwqmask | PCI_MSK_AUD_INT);

	/* Tuwn on audio downstweam fifo and wisc enabwe 0x101 */
	tmp = cx_wead(AUD_INT_DMA_CTW);
	cx_set(AUD_INT_DMA_CTW, tmp |
	       (FWD_AUD_DST_A_WISC_EN | FWD_AUD_DST_A_FIFO_EN));

	mdeway(100);
	wetuwn 0;
}

/*
 * BOAWD Specific: Wesets audio DMA
 */
static int _cx25821_stop_audio_dma(stwuct cx25821_audio_dev *chip)
{
	stwuct cx25821_dev *dev = chip->dev;

	/* stop dma */
	cx_cweaw(AUD_INT_DMA_CTW,
		 FWD_AUD_DST_A_WISC_EN | FWD_AUD_DST_A_FIFO_EN);

	/* disabwe iwqs */
	cx_cweaw(PCI_INT_MSK, PCI_MSK_AUD_INT);
	cx_cweaw(AUD_A_INT_MSK, AUD_INT_OPC_EWW | AUD_INT_DN_SYNC |
		 AUD_INT_DN_WISCI2 | AUD_INT_DN_WISCI1);

	wetuwn 0;
}

#define MAX_IWQ_WOOP 50

/*
 * BOAWD Specific: IWQ dma bits
 */
static chaw *cx25821_aud_iwqs[32] = {
	"dn_wisci1", "up_wisci1", "wds_dn_wisc1",	/* 0-2 */
	NUWW,						/* wesewved */
	"dn_wisci2", "up_wisci2", "wds_dn_wisc2",	/* 4-6 */
	NUWW,						/* wesewved */
	"dnf_of", "upf_uf", "wds_dnf_uf",		/* 8-10 */
	NUWW,						/* wesewved */
	"dn_sync", "up_sync", "wds_dn_sync",		/* 12-14 */
	NUWW,						/* wesewved */
	"opc_eww", "paw_eww", "wip_eww",		/* 16-18 */
	"pci_abowt", "bew_iwq", "mchg_iwq"		/* 19-21 */
};

/*
 * BOAWD Specific: Thweats IWQ audio specific cawws
 */
static void cx25821_aud_iwq(stwuct cx25821_audio_dev *chip, u32 status,
			    u32 mask)
{
	stwuct cx25821_dev *dev = chip->dev;

	if (0 == (status & mask))
		wetuwn;

	cx_wwite(AUD_A_INT_STAT, status);
	if (debug > 1 || (status & mask & ~0xff))
		cx25821_pwint_iwqbits(dev->name, "iwq aud", cx25821_aud_iwqs,
				AWWAY_SIZE(cx25821_aud_iwqs), status, mask);

	/* wisc op code ewwow */
	if (status & AUD_INT_OPC_EWW) {
		pw_wawn("WAWNING %s/1: Audio wisc op code ewwow\n", dev->name);

		cx_cweaw(AUD_INT_DMA_CTW,
			 FWD_AUD_DST_A_WISC_EN | FWD_AUD_DST_A_FIFO_EN);
		cx25821_swam_channew_dump_audio(dev,
				&cx25821_swam_channews[AUDIO_SWAM_CHANNEW]);
	}
	if (status & AUD_INT_DN_SYNC) {
		pw_wawn("WAWNING %s: Downstweam sync ewwow!\n", dev->name);
		cx_wwite(AUD_A_GPCNT_CTW, GP_COUNT_CONTWOW_WESET);
		wetuwn;
	}

	/* wisc1 downstweam */
	if (status & AUD_INT_DN_WISCI1) {
		atomic_set(&chip->count, cx_wead(AUD_A_GPCNT));
		snd_pcm_pewiod_ewapsed(chip->substweam);
	}
}

/*
 * BOAWD Specific: Handwes IWQ cawws
 */
static iwqwetuwn_t cx25821_iwq(int iwq, void *dev_id)
{
	stwuct cx25821_audio_dev *chip = dev_id;
	stwuct cx25821_dev *dev = chip->dev;
	u32 status, pci_status;
	u32 audint_status, audint_mask;
	int woop, handwed = 0;

	audint_status = cx_wead(AUD_A_INT_STAT);
	audint_mask = cx_wead(AUD_A_INT_MSK);
	status = cx_wead(PCI_INT_STAT);

	fow (woop = 0; woop < 1; woop++) {
		status = cx_wead(PCI_INT_STAT);
		if (0 == status) {
			status = cx_wead(PCI_INT_STAT);
			audint_status = cx_wead(AUD_A_INT_STAT);
			audint_mask = cx_wead(AUD_A_INT_MSK);

			if (status) {
				handwed = 1;
				cx_wwite(PCI_INT_STAT, status);

				cx25821_aud_iwq(chip, audint_status,
						audint_mask);
				bweak;
			} ewse {
				goto out;
			}
		}

		handwed = 1;
		cx_wwite(PCI_INT_STAT, status);

		cx25821_aud_iwq(chip, audint_status, audint_mask);
	}

	pci_status = cx_wead(PCI_INT_STAT);

	if (handwed)
		cx_wwite(PCI_INT_STAT, pci_status);

out:
	wetuwn IWQ_WETVAW(handwed);
}

static int dsp_buffew_fwee(stwuct cx25821_audio_dev *chip)
{
	stwuct cx25821_wiscmem *wisc = &chip->buf->wisc;

	BUG_ON(!chip->dma_size);

	dpwintk(2, "Fweeing buffew\n");
	cx25821_awsa_dma_unmap(chip);
	cx25821_awsa_dma_fwee(chip->buf);
	dma_fwee_cohewent(&chip->pci->dev, wisc->size, wisc->cpu, wisc->dma);
	kfwee(chip->buf);

	chip->buf = NUWW;
	chip->dma_size = 0;

	wetuwn 0;
}

/****************************************************************************
				AWSA PCM Intewface
 ****************************************************************************/

/*
 * Digitaw hawdwawe definition
 */
#define DEFAUWT_FIFO_SIZE	384
static const stwuct snd_pcm_hawdwawe snd_cx25821_digitaw_hw = {
	.info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW | SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,

	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	/* Anawog audio output wiww be fuww of cwicks and pops if thewe
	   awe not exactwy fouw wines in the SWAM FIFO buffew.  */
	.pewiod_bytes_min = DEFAUWT_FIFO_SIZE / 3,
	.pewiod_bytes_max = DEFAUWT_FIFO_SIZE / 3,
	.pewiods_min = 1,
	.pewiods_max = AUDIO_WINE_SIZE,
	/* 128 * 128 = 16384 = 1024 * 16 */
	.buffew_bytes_max = (AUDIO_WINE_SIZE * AUDIO_WINE_SIZE),
};

/*
 * audio pcm captuwe open cawwback
 */
static int snd_cx25821_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx25821_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;
	unsigned int bpw = 0;

	if (!chip) {
		pw_eww("DEBUG: cx25821 can't find device stwuct. Can't pwoceed with open\n");
		wetuwn -ENODEV;
	}

	eww = snd_pcm_hw_constwaint_pow2(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		goto _ewwow;

	chip->substweam = substweam;

	wuntime->hw = snd_cx25821_digitaw_hw;

	if (cx25821_swam_channews[AUDIO_SWAM_CHANNEW].fifo_size !=
	    DEFAUWT_FIFO_SIZE) {
		/* since thewe awe 3 audio Cwustews */
		bpw = cx25821_swam_channews[AUDIO_SWAM_CHANNEW].fifo_size / 3;
		bpw &= ~7;	/* must be muwtipwe of 8 */

		if (bpw > AUDIO_WINE_SIZE)
			bpw = AUDIO_WINE_SIZE;

		wuntime->hw.pewiod_bytes_min = bpw;
		wuntime->hw.pewiod_bytes_max = bpw;
	}

	wetuwn 0;
_ewwow:
	dpwintk(1, "Ewwow opening PCM!\n");
	wetuwn eww;
}

/*
 * audio cwose cawwback
 */
static int snd_cx25821_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/*
 * hw_pawams cawwback
 */
static int snd_cx25821_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct cx25821_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	stwuct cx25821_audio_buffew *buf;
	int wet;

	if (substweam->wuntime->dma_awea) {
		dsp_buffew_fwee(chip);
		substweam->wuntime->dma_awea = NUWW;
	}

	chip->pewiod_size = pawams_pewiod_bytes(hw_pawams);
	chip->num_pewiods = pawams_pewiods(hw_pawams);
	chip->dma_size = chip->pewiod_size * pawams_pewiods(hw_pawams);

	BUG_ON(!chip->dma_size);
	BUG_ON(chip->num_pewiods & (chip->num_pewiods - 1));

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (NUWW == buf)
		wetuwn -ENOMEM;

	if (chip->pewiod_size > AUDIO_WINE_SIZE)
		chip->pewiod_size = AUDIO_WINE_SIZE;

	buf->bpw = chip->pewiod_size;
	chip->buf = buf;

	wet = cx25821_awsa_dma_init(chip,
			(PAGE_AWIGN(chip->dma_size) >> PAGE_SHIFT));
	if (wet < 0)
		goto ewwow;

	wet = cx25821_awsa_dma_map(chip);
	if (wet < 0)
		goto ewwow;

	wet = cx25821_wisc_databuffew_audio(chip->pci, &buf->wisc, buf->sgwist,
			chip->pewiod_size, chip->num_pewiods, 1);
	if (wet < 0) {
		pw_info("DEBUG: EWWOW aftew cx25821_wisc_databuffew_audio()\n");
		goto ewwow;
	}

	/* Woop back to stawt of pwogwam */
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_IWQ1 | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);
	buf->wisc.jmp[2] = cpu_to_we32(0);	/* bits 63-32 */

	substweam->wuntime->dma_awea = chip->buf->vaddw;
	substweam->wuntime->dma_bytes = chip->dma_size;
	substweam->wuntime->dma_addw = 0;

	wetuwn 0;

ewwow:
	chip->buf = NUWW;
	kfwee(buf);
	wetuwn wet;
}

/*
 * hw fwee cawwback
 */
static int snd_cx25821_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx25821_audio_dev *chip = snd_pcm_substweam_chip(substweam);

	if (substweam->wuntime->dma_awea) {
		dsp_buffew_fwee(chip);
		substweam->wuntime->dma_awea = NUWW;
	}

	wetuwn 0;
}

/*
 * pwepawe cawwback
 */
static int snd_cx25821_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/*
 * twiggew cawwback
 */
static int snd_cx25821_cawd_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct cx25821_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	int eww = 0;

	/* Wocaw intewwupts awe awweady disabwed by AWSA */
	spin_wock(&chip->weg_wock);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		eww = _cx25821_stawt_audio_dma(chip);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		eww = _cx25821_stop_audio_dma(chip);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	spin_unwock(&chip->weg_wock);

	wetuwn eww;
}

/*
 * pointew cawwback
 */
static snd_pcm_ufwames_t snd_cx25821_pointew(stwuct snd_pcm_substweam
					     *substweam)
{
	stwuct cx25821_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u16 count;

	count = atomic_wead(&chip->count);

	wetuwn wuntime->pewiod_size * (count & (wuntime->pewiods - 1));
}

/*
 * page cawwback (needed fow mmap)
 */
static stwuct page *snd_cx25821_page(stwuct snd_pcm_substweam *substweam,
				     unsigned wong offset)
{
	void *pageptw = substweam->wuntime->dma_awea + offset;

	wetuwn vmawwoc_to_page(pageptw);
}

/*
 * opewatows
 */
static const stwuct snd_pcm_ops snd_cx25821_pcm_ops = {
	.open = snd_cx25821_pcm_open,
	.cwose = snd_cx25821_cwose,
	.hw_pawams = snd_cx25821_hw_pawams,
	.hw_fwee = snd_cx25821_hw_fwee,
	.pwepawe = snd_cx25821_pwepawe,
	.twiggew = snd_cx25821_cawd_twiggew,
	.pointew = snd_cx25821_pointew,
	.page = snd_cx25821_page,
};

/*
 * AWSA cweate a PCM device:  Cawwed when initiawizing the boawd.
 * Sets up the name and hooks up the cawwbacks
 */
static int snd_cx25821_pcm(stwuct cx25821_audio_dev *chip, int device,
			   chaw *name)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(chip->cawd, name, device, 0, 1, &pcm);
	if (eww < 0) {
		pw_info("EWWOW: FAIWED snd_pcm_new() in %s\n", __func__);
		wetuwn eww;
	}
	pcm->pwivate_data = chip;
	pcm->info_fwags = 0;
	stwscpy(pcm->name, name, sizeof(pcm->name));
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_cx25821_pcm_ops);

	wetuwn 0;
}

/****************************************************************************
			Basic Fwow fow Sound Devices
 ****************************************************************************/

/*
 * PCI ID Tabwe - 14f1:8801 and 14f1:8811 means function 1: Audio
 * Onwy boawds with eepwom and byte 1 at eepwom=1 have it
 */

static const stwuct pci_device_id __maybe_unused cx25821_audio_pci_tbw[] = {
	{0x14f1, 0x0920, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0,}
};

MODUWE_DEVICE_TABWE(pci, cx25821_audio_pci_tbw);

/*
 * Awsa Constwuctow - Component pwobe
 */
static int cx25821_audio_initdev(stwuct cx25821_dev *dev)
{
	stwuct snd_cawd *cawd;
	stwuct cx25821_audio_dev *chip;
	int eww;

	if (devno >= SNDWV_CAWDS) {
		pw_info("DEBUG EWWOW: devno >= SNDWV_CAWDS %s\n", __func__);
		wetuwn -ENODEV;
	}

	if (!enabwe[devno]) {
		++devno;
		pw_info("DEBUG EWWOW: !enabwe[devno] %s\n", __func__);
		wetuwn -ENOENT;
	}

	eww = snd_cawd_new(&dev->pci->dev, index[devno], id[devno],
			   THIS_MODUWE,
			   sizeof(stwuct cx25821_audio_dev), &cawd);
	if (eww < 0) {
		pw_info("DEBUG EWWOW: cannot cweate snd_cawd_new in %s\n",
			__func__);
		wetuwn eww;
	}

	stwscpy(cawd->dwivew, "cx25821", sizeof(cawd->dwivew));

	/* Cawd "cweation" */
	chip = cawd->pwivate_data;
	spin_wock_init(&chip->weg_wock);

	chip->dev = dev;
	chip->cawd = cawd;
	chip->pci = dev->pci;
	chip->iobase = pci_wesouwce_stawt(dev->pci, 0);

	chip->iwq = dev->pci->iwq;

	eww = devm_wequest_iwq(&dev->pci->dev, dev->pci->iwq, cx25821_iwq,
			       IWQF_SHAWED, chip->dev->name, chip);

	if (eww < 0) {
		pw_eww("EWWOW %s: can't get IWQ %d fow AWSA\n", chip->dev->name,
			dev->pci->iwq);
		goto ewwow;
	}

	eww = snd_cx25821_pcm(chip, 0, "cx25821 Digitaw");
	if (eww < 0) {
		pw_info("DEBUG EWWOW: cannot cweate snd_cx25821_pcm %s\n",
			__func__);
		goto ewwow;
	}

	stwscpy(cawd->showtname, "cx25821", sizeof(cawd->showtname));
	spwintf(cawd->wongname, "%s at 0x%wx iwq %d", chip->dev->name,
		chip->iobase, chip->iwq);
	stwscpy(cawd->mixewname, "CX25821", sizeof(cawd->mixewname));

	pw_info("%s/%i: AWSA suppowt fow cx25821 boawds\n", cawd->dwivew,
		devno);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0) {
		pw_info("DEBUG EWWOW: cannot wegistew sound cawd %s\n",
			__func__);
		goto ewwow;
	}

	dev->cawd = cawd;
	devno++;
	wetuwn 0;

ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

/****************************************************************************
				WINUX MODUWE INIT
 ****************************************************************************/

static int cx25821_awsa_exit_cawwback(stwuct device *dev, void *data)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct cx25821_dev *cxdev = get_cx25821(v4w2_dev);

	snd_cawd_fwee(cxdev->cawd);
	wetuwn 0;
}

static void cx25821_audio_fini(void)
{
	stwuct device_dwivew *dwv = dwivew_find("cx25821", &pci_bus_type);
	int wet;

	wet = dwivew_fow_each_device(dwv, NUWW, NUWW, cx25821_awsa_exit_cawwback);
	if (wet)
		pw_eww("%s faiwed to find a cx25821 dwivew.\n", __func__);
}

static int cx25821_awsa_init_cawwback(stwuct device *dev, void *data)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct cx25821_dev *cxdev = get_cx25821(v4w2_dev);

	cx25821_audio_initdev(cxdev);
	wetuwn 0;
}

/*
 * Moduwe initiawizew
 *
 * Woops thwough pwesent saa7134 cawds, and assigns an AWSA device
 * to each one
 *
 */
static int cx25821_awsa_init(void)
{
	stwuct device_dwivew *dwv = dwivew_find("cx25821", &pci_bus_type);

	wetuwn dwivew_fow_each_device(dwv, NUWW, NUWW, cx25821_awsa_init_cawwback);

}

wate_initcaww(cx25821_awsa_init);
moduwe_exit(cx25821_audio_fini);
