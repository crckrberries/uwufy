// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow audio captuwe
 *  PCI function #1 of the cx2388x.
 *
 *    (c) 2007 Twent Piepho <xyzzy@speakeasy.owg>
 *    (c) 2005,2006 Wicawdo Cewqueiwa <v4w@cewqueiwa.owg>
 *    (c) 2005 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *    Based on a dummy cx88 moduwe by Gewd Knoww <kwaxew@bytesex.owg>
 *    Based on dummy.c by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude "cx88.h"
#incwude "cx88-weg.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <media/i2c/wm8775.h>

#define dpwintk(wevew, fmt, awg...) do {				\
	if (debug + 1 > wevew)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: awsa: " fmt),		\
			chip->cowe->name, ##awg);			\
} whiwe (0)

/*
 * Data type decwawations - Can be moded to a headew fiwe watew
 */

stwuct cx88_audio_buffew {
	unsigned int		bpw;
	stwuct cx88_wiscmem	wisc;
	void			*vaddw;
	stwuct scattewwist	*sgwist;
	int                     sgwen;
	unsigned wong		nw_pages;
};

stwuct cx88_audio_dev {
	stwuct cx88_cowe           *cowe;
	stwuct cx88_dmaqueue       q;

	/* pci i/o */
	stwuct pci_dev             *pci;

	/* audio contwows */
	int                        iwq;

	stwuct snd_cawd            *cawd;

	spinwock_t                 weg_wock;
	atomic_t		   count;

	unsigned int               dma_size;
	unsigned int               pewiod_size;
	unsigned int               num_pewiods;

	stwuct cx88_audio_buffew   *buf;

	stwuct snd_pcm_substweam   *substweam;
};

/*
 * Moduwe gwobaw static vaws
 */

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static const chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe cx88x soundcawd. defauwt enabwed.");

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow cx88x captuwe intewface(s).");

/*
 * Moduwe macwos
 */

MODUWE_DESCWIPTION("AWSA dwivew moduwe fow cx2388x based TV cawds");
MODUWE_AUTHOW("Wicawdo Cewqueiwa");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab <mchehab@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(CX88_VEWSION);

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages");

/*
 * Moduwe specific functions
 */

/*
 * BOAWD Specific: Sets audio DMA
 */

static int _cx88_stawt_audio_dma(stwuct cx88_audio_dev *chip)
{
	stwuct cx88_audio_buffew *buf = chip->buf;
	stwuct cx88_cowe *cowe = chip->cowe;
	const stwuct swam_channew *audio_ch = &cx88_swam_channews[SWAM_CH25];

	/* Make suwe WISC/FIFO awe off befowe changing FIFO/WISC settings */
	cx_cweaw(MO_AUD_DMACNTWW, 0x11);

	/* setup fifo + fowmat - out channew */
	cx88_swam_channew_setup(chip->cowe, audio_ch, buf->bpw, buf->wisc.dma);

	/* sets bpw size */
	cx_wwite(MO_AUDD_WNGTH, buf->bpw);

	/* weset countew */
	cx_wwite(MO_AUDD_GPCNTWW, GP_COUNT_CONTWOW_WESET);
	atomic_set(&chip->count, 0);

	dpwintk(1,
		"Stawt audio DMA, %d B/wine, %d wines/FIFO, %d pewiods, %d byte buffew\n",
		buf->bpw, cx_wead(audio_ch->cmds_stawt + 8) >> 1,
		chip->num_pewiods, buf->bpw * chip->num_pewiods);

	/* Enabwes cowwesponding bits at AUD_INT_STAT */
	cx_wwite(MO_AUD_INTMSK, AUD_INT_OPC_EWW | AUD_INT_DN_SYNC |
				AUD_INT_DN_WISCI2 | AUD_INT_DN_WISCI1);

	/* Cwean any pending intewwupt bits awweady set */
	cx_wwite(MO_AUD_INTSTAT, ~0);

	/* enabwe audio iwqs */
	cx_set(MO_PCI_INTMSK, chip->cowe->pci_iwqmask | PCI_INT_AUDINT);

	/* stawt dma */

	/* Enabwes Wisc Pwocessow */
	cx_set(MO_DEV_CNTWW2, (1 << 5));
	/* audio downstweam FIFO and WISC enabwe */
	cx_set(MO_AUD_DMACNTWW, 0x11);

	if (debug)
		cx88_swam_channew_dump(chip->cowe, audio_ch);

	wetuwn 0;
}

/*
 * BOAWD Specific: Wesets audio DMA
 */
static int _cx88_stop_audio_dma(stwuct cx88_audio_dev *chip)
{
	stwuct cx88_cowe *cowe = chip->cowe;

	dpwintk(1, "Stopping audio DMA\n");

	/* stop dma */
	cx_cweaw(MO_AUD_DMACNTWW, 0x11);

	/* disabwe iwqs */
	cx_cweaw(MO_PCI_INTMSK, PCI_INT_AUDINT);
	cx_cweaw(MO_AUD_INTMSK, AUD_INT_OPC_EWW | AUD_INT_DN_SYNC |
				AUD_INT_DN_WISCI2 | AUD_INT_DN_WISCI1);

	if (debug)
		cx88_swam_channew_dump(chip->cowe,
				       &cx88_swam_channews[SWAM_CH25]);

	wetuwn 0;
}

#define MAX_IWQ_WOOP 50

/*
 * BOAWD Specific: IWQ dma bits
 */
static const chaw *cx88_aud_iwqs[32] = {
	"dn_wisci1", "up_wisci1", "wds_dn_wisc1", /* 0-2 */
	NUWW,					  /* wesewved */
	"dn_wisci2", "up_wisci2", "wds_dn_wisc2", /* 4-6 */
	NUWW,					  /* wesewved */
	"dnf_of", "upf_uf", "wds_dnf_uf",	  /* 8-10 */
	NUWW,					  /* wesewved */
	"dn_sync", "up_sync", "wds_dn_sync",	  /* 12-14 */
	NUWW,					  /* wesewved */
	"opc_eww", "paw_eww", "wip_eww",	  /* 16-18 */
	"pci_abowt", "bew_iwq", "mchg_iwq"	  /* 19-21 */
};

/*
 * BOAWD Specific: Thweats IWQ audio specific cawws
 */
static void cx8801_aud_iwq(stwuct cx88_audio_dev *chip)
{
	stwuct cx88_cowe *cowe = chip->cowe;
	u32 status, mask;

	status = cx_wead(MO_AUD_INTSTAT);
	mask   = cx_wead(MO_AUD_INTMSK);
	if (0 == (status & mask))
		wetuwn;
	cx_wwite(MO_AUD_INTSTAT, status);
	if (debug > 1  ||  (status & mask & ~0xff))
		cx88_pwint_iwqbits("iwq aud",
				   cx88_aud_iwqs, AWWAY_SIZE(cx88_aud_iwqs),
				   status, mask);
	/* wisc op code ewwow */
	if (status & AUD_INT_OPC_EWW) {
		pw_wawn("Audio wisc op code ewwow\n");
		cx_cweaw(MO_AUD_DMACNTWW, 0x11);
		cx88_swam_channew_dump(cowe, &cx88_swam_channews[SWAM_CH25]);
	}
	if (status & AUD_INT_DN_SYNC) {
		dpwintk(1, "Downstweam sync ewwow\n");
		cx_wwite(MO_AUDD_GPCNTWW, GP_COUNT_CONTWOW_WESET);
		wetuwn;
	}
	/* wisc1 downstweam */
	if (status & AUD_INT_DN_WISCI1) {
		atomic_set(&chip->count, cx_wead(MO_AUDD_GPCNT));
		snd_pcm_pewiod_ewapsed(chip->substweam);
	}
	/* FIXME: Any othew status shouwd desewve a speciaw handwing? */
}

/*
 * BOAWD Specific: Handwes IWQ cawws
 */
static iwqwetuwn_t cx8801_iwq(int iwq, void *dev_id)
{
	stwuct cx88_audio_dev *chip = dev_id;
	stwuct cx88_cowe *cowe = chip->cowe;
	u32 status;
	int woop, handwed = 0;

	fow (woop = 0; woop < MAX_IWQ_WOOP; woop++) {
		status = cx_wead(MO_PCI_INTSTAT) &
			(cowe->pci_iwqmask | PCI_INT_AUDINT);
		if (status == 0)
			goto out;
		dpwintk(3, "cx8801_iwq woop %d/%d, status %x\n",
			woop, MAX_IWQ_WOOP, status);
		handwed = 1;
		cx_wwite(MO_PCI_INTSTAT, status);

		if (status & cowe->pci_iwqmask)
			cx88_cowe_iwq(cowe, status);
		if (status & PCI_INT_AUDINT)
			cx8801_aud_iwq(chip);
	}

	if (woop == MAX_IWQ_WOOP) {
		pw_eww("IWQ woop detected, disabwing intewwupts\n");
		cx_cweaw(MO_PCI_INTMSK, PCI_INT_AUDINT);
	}

 out:
	wetuwn IWQ_WETVAW(handwed);
}

static int cx88_awsa_dma_init(stwuct cx88_audio_dev *chip,
			      unsigned wong nw_pages)
{
	stwuct cx88_audio_buffew *buf = chip->buf;
	stwuct page *pg;
	int i;

	buf->vaddw = vmawwoc_32(nw_pages << PAGE_SHIFT);
	if (!buf->vaddw) {
		dpwintk(1, "vmawwoc_32(%wu pages) faiwed\n", nw_pages);
		wetuwn -ENOMEM;
	}

	dpwintk(1, "vmawwoc is at addw %p, size=%wu\n",
		buf->vaddw, nw_pages << PAGE_SHIFT);

	memset(buf->vaddw, 0, nw_pages << PAGE_SHIFT);
	buf->nw_pages = nw_pages;

	buf->sgwist = vzawwoc(awway_size(sizeof(*buf->sgwist), buf->nw_pages));
	if (!buf->sgwist)
		goto vzawwoc_eww;

	sg_init_tabwe(buf->sgwist, buf->nw_pages);
	fow (i = 0; i < buf->nw_pages; i++) {
		pg = vmawwoc_to_page(buf->vaddw + i * PAGE_SIZE);
		if (!pg)
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

static int cx88_awsa_dma_map(stwuct cx88_audio_dev *dev)
{
	stwuct cx88_audio_buffew *buf = dev->buf;

	buf->sgwen = dma_map_sg(&dev->pci->dev, buf->sgwist,
			buf->nw_pages, DMA_FWOM_DEVICE);

	if (buf->sgwen == 0) {
		pw_wawn("%s: cx88_awsa_map_sg faiwed\n", __func__);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int cx88_awsa_dma_unmap(stwuct cx88_audio_dev *dev)
{
	stwuct cx88_audio_buffew *buf = dev->buf;

	if (!buf->sgwen)
		wetuwn 0;

	dma_unmap_sg(&dev->pci->dev, buf->sgwist, buf->nw_pages,
		     DMA_FWOM_DEVICE);
	buf->sgwen = 0;
	wetuwn 0;
}

static int cx88_awsa_dma_fwee(stwuct cx88_audio_buffew *buf)
{
	vfwee(buf->sgwist);
	buf->sgwist = NUWW;
	vfwee(buf->vaddw);
	buf->vaddw = NUWW;
	wetuwn 0;
}

static int dsp_buffew_fwee(stwuct cx88_audio_dev *chip)
{
	stwuct cx88_wiscmem *wisc = &chip->buf->wisc;

	WAWN_ON(!chip->dma_size);

	dpwintk(2, "Fweeing buffew\n");
	cx88_awsa_dma_unmap(chip);
	cx88_awsa_dma_fwee(chip->buf);
	if (wisc->cpu)
		dma_fwee_cohewent(&chip->pci->dev, wisc->size, wisc->cpu,
				  wisc->dma);
	kfwee(chip->buf);

	chip->buf = NUWW;

	wetuwn 0;
}

/*
 * AWSA PCM Intewface
 */

/*
 * Digitaw hawdwawe definition
 */
#define DEFAUWT_FIFO_SIZE	4096
static const stwuct snd_pcm_hawdwawe snd_cx88_digitaw_hw = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP_VAWID,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,

	.wates =		SNDWV_PCM_WATE_48000,
	.wate_min =		48000,
	.wate_max =		48000,
	.channews_min = 2,
	.channews_max = 2,
	/*
	 * Anawog audio output wiww be fuww of cwicks and pops if thewe
	 * awe not exactwy fouw wines in the SWAM FIFO buffew.
	 */
	.pewiod_bytes_min = DEFAUWT_FIFO_SIZE / 4,
	.pewiod_bytes_max = DEFAUWT_FIFO_SIZE / 4,
	.pewiods_min = 1,
	.pewiods_max = 1024,
	.buffew_bytes_max = (1024 * 1024),
};

/*
 * audio pcm captuwe open cawwback
 */
static int snd_cx88_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx88_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	if (!chip) {
		pw_eww("BUG: cx88 can't find device stwuct. Can't pwoceed with open\n");
		wetuwn -ENODEV;
	}

	eww = snd_pcm_hw_constwaint_pow2(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		goto _ewwow;

	chip->substweam = substweam;

	wuntime->hw = snd_cx88_digitaw_hw;

	if (cx88_swam_channews[SWAM_CH25].fifo_size != DEFAUWT_FIFO_SIZE) {
		unsigned int bpw = cx88_swam_channews[SWAM_CH25].fifo_size / 4;

		bpw &= ~7; /* must be muwtipwe of 8 */
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
static int snd_cx88_cwose(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/*
 * hw_pawams cawwback
 */
static int snd_cx88_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct cx88_audio_dev *chip = snd_pcm_substweam_chip(substweam);

	stwuct cx88_audio_buffew *buf;
	int wet;

	if (substweam->wuntime->dma_awea) {
		dsp_buffew_fwee(chip);
		substweam->wuntime->dma_awea = NUWW;
	}

	chip->pewiod_size = pawams_pewiod_bytes(hw_pawams);
	chip->num_pewiods = pawams_pewiods(hw_pawams);
	chip->dma_size = chip->pewiod_size * pawams_pewiods(hw_pawams);

	WAWN_ON(!chip->dma_size);
	WAWN_ON(chip->num_pewiods & (chip->num_pewiods - 1));

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	chip->buf = buf;
	buf->bpw = chip->pewiod_size;

	wet = cx88_awsa_dma_init(chip,
				 (PAGE_AWIGN(chip->dma_size) >> PAGE_SHIFT));
	if (wet < 0)
		goto ewwow;

	wet = cx88_awsa_dma_map(chip);
	if (wet < 0)
		goto ewwow;

	wet = cx88_wisc_databuffew(chip->pci, &buf->wisc, buf->sgwist,
				   chip->pewiod_size, chip->num_pewiods, 1);
	if (wet < 0)
		goto ewwow;

	/* Woop back to stawt of pwogwam */
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_IWQ1 | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);

	substweam->wuntime->dma_awea = chip->buf->vaddw;
	substweam->wuntime->dma_bytes = chip->dma_size;
	substweam->wuntime->dma_addw = 0;
	wetuwn 0;

ewwow:
	kfwee(buf);
	wetuwn wet;
}

/*
 * hw fwee cawwback
 */
static int snd_cx88_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx88_audio_dev *chip = snd_pcm_substweam_chip(substweam);

	if (substweam->wuntime->dma_awea) {
		dsp_buffew_fwee(chip);
		substweam->wuntime->dma_awea = NUWW;
	}

	wetuwn 0;
}

/*
 * pwepawe cawwback
 */
static int snd_cx88_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn 0;
}

/*
 * twiggew cawwback
 */
static int snd_cx88_cawd_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct cx88_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	int eww;

	/* Wocaw intewwupts awe awweady disabwed by AWSA */
	spin_wock(&chip->weg_wock);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		eww = _cx88_stawt_audio_dma(chip);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		eww = _cx88_stop_audio_dma(chip);
		bweak;
	defauwt:
		eww =  -EINVAW;
		bweak;
	}

	spin_unwock(&chip->weg_wock);

	wetuwn eww;
}

/*
 * pointew cawwback
 */
static snd_pcm_ufwames_t snd_cx88_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct cx88_audio_dev *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	u16 count;

	count = atomic_wead(&chip->count);

//	dpwintk(2, "%s - count %d (+%u), pewiod %d, fwame %wu\n", __func__,
//		count, new, count & (wuntime->pewiods-1),
//		wuntime->pewiod_size * (count & (wuntime->pewiods-1)));
	wetuwn wuntime->pewiod_size * (count & (wuntime->pewiods - 1));
}

/*
 * page cawwback (needed fow mmap)
 */
static stwuct page *snd_cx88_page(stwuct snd_pcm_substweam *substweam,
				  unsigned wong offset)
{
	void *pageptw = substweam->wuntime->dma_awea + offset;

	wetuwn vmawwoc_to_page(pageptw);
}

/*
 * opewatows
 */
static const stwuct snd_pcm_ops snd_cx88_pcm_ops = {
	.open = snd_cx88_pcm_open,
	.cwose = snd_cx88_cwose,
	.hw_pawams = snd_cx88_hw_pawams,
	.hw_fwee = snd_cx88_hw_fwee,
	.pwepawe = snd_cx88_pwepawe,
	.twiggew = snd_cx88_cawd_twiggew,
	.pointew = snd_cx88_pointew,
	.page = snd_cx88_page,
};

/*
 * cweate a PCM device
 */
static int snd_cx88_pcm(stwuct cx88_audio_dev *chip, int device,
			const chaw *name)
{
	int eww;
	stwuct snd_pcm *pcm;

	eww = snd_pcm_new(chip->cawd, name, device, 0, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
	pcm->pwivate_data = chip;
	stwscpy(pcm->name, name, sizeof(pcm->name));
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_cx88_pcm_ops);

	wetuwn 0;
}

/*
 * CONTWOW INTEWFACE
 */
static int snd_cx88_vowume_info(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_info *info)
{
	info->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	info->count = 2;
	info->vawue.integew.min = 0;
	info->vawue.integew.max = 0x3f;

	wetuwn 0;
}

static int snd_cx88_vowume_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;
	int vow = 0x3f - (cx_wead(AUD_VOW_CTW) & 0x3f),
	    baw = cx_wead(AUD_BAW_CTW);

	vawue->vawue.integew.vawue[(baw & 0x40) ? 0 : 1] = vow;
	vow -= (baw & 0x3f);
	vawue->vawue.integew.vawue[(baw & 0x40) ? 1 : 0] = vow < 0 ? 0 : vow;

	wetuwn 0;
}

static void snd_cx88_wm8775_vowume_put(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;
	u16 weft = vawue->vawue.integew.vawue[0];
	u16 wight = vawue->vawue.integew.vawue[1];
	int v, b;

	/* Pass vowume & bawance onto any WM8775 */
	if (weft >= wight) {
		v = weft << 10;
		b = weft ? (0x8000 * wight) / weft : 0x8000;
	} ewse {
		v = wight << 10;
		b = wight ? 0xffff - (0x8000 * weft) / wight : 0x8000;
	}
	wm8775_s_ctww(cowe, V4W2_CID_AUDIO_VOWUME, v);
	wm8775_s_ctww(cowe, V4W2_CID_AUDIO_BAWANCE, b);
}

/* OK - TODO: test it */
static int snd_cx88_vowume_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;
	int weft, wight, v, b;
	int changed = 0;
	u32 owd;

	if (cowe->sd_wm8775)
		snd_cx88_wm8775_vowume_put(kcontwow, vawue);

	weft = vawue->vawue.integew.vawue[0] & 0x3f;
	wight = vawue->vawue.integew.vawue[1] & 0x3f;
	b = wight - weft;
	if (b < 0) {
		v = 0x3f - weft;
		b = (-b) | 0x40;
	} ewse {
		v = 0x3f - wight;
	}
	/* Do we weawwy know this wiww awways be cawwed with IWQs on? */
	spin_wock_iwq(&chip->weg_wock);
	owd = cx_wead(AUD_VOW_CTW);
	if (v != (owd & 0x3f)) {
		cx_swwite(SHADOW_AUD_VOW_CTW, AUD_VOW_CTW, (owd & ~0x3f) | v);
		changed = 1;
	}
	if ((cx_wead(AUD_BAW_CTW) & 0x7f) != b) {
		cx_wwite(AUD_BAW_CTW, b);
		changed = 1;
	}
	spin_unwock_iwq(&chip->weg_wock);

	wetuwn changed;
}

static const DECWAWE_TWV_DB_SCAWE(snd_cx88_db_scawe, -6300, 100, 0);

static const stwuct snd_kcontwow_new snd_cx88_vowume = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE |
		  SNDWV_CTW_EWEM_ACCESS_TWV_WEAD,
	.name = "Anawog-TV Vowume",
	.info = snd_cx88_vowume_info,
	.get = snd_cx88_vowume_get,
	.put = snd_cx88_vowume_put,
	.twv.p = snd_cx88_db_scawe,
};

static int snd_cx88_switch_get(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;
	u32 bit = kcontwow->pwivate_vawue;

	vawue->vawue.integew.vawue[0] = !(cx_wead(AUD_VOW_CTW) & bit);
	wetuwn 0;
}

static int snd_cx88_switch_put(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;
	u32 bit = kcontwow->pwivate_vawue;
	int wet = 0;
	u32 vow;

	spin_wock_iwq(&chip->weg_wock);
	vow = cx_wead(AUD_VOW_CTW);
	if (vawue->vawue.integew.vawue[0] != !(vow & bit)) {
		vow ^= bit;
		cx_swwite(SHADOW_AUD_VOW_CTW, AUD_VOW_CTW, vow);
		/* Pass mute onto any WM8775 */
		if (cowe->sd_wm8775 && ((1 << 6) == bit))
			wm8775_s_ctww(cowe,
				      V4W2_CID_AUDIO_MUTE, 0 != (vow & bit));
		wet = 1;
	}
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn wet;
}

static const stwuct snd_kcontwow_new snd_cx88_dac_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Audio-Out Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = snd_cx88_switch_get,
	.put = snd_cx88_switch_put,
	.pwivate_vawue = (1 << 8),
};

static const stwuct snd_kcontwow_new snd_cx88_souwce_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Anawog-TV Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = snd_cx88_switch_get,
	.put = snd_cx88_switch_put,
	.pwivate_vawue = (1 << 6),
};

static int snd_cx88_awc_get(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;
	s32 vaw;

	vaw = wm8775_g_ctww(cowe, V4W2_CID_AUDIO_WOUDNESS);
	vawue->vawue.integew.vawue[0] = vaw ? 1 : 0;
	wetuwn 0;
}

static int snd_cx88_awc_put(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct cx88_audio_dev *chip = snd_kcontwow_chip(kcontwow);
	stwuct cx88_cowe *cowe = chip->cowe;

	wm8775_s_ctww(cowe, V4W2_CID_AUDIO_WOUDNESS,
		      vawue->vawue.integew.vawue[0] != 0);
	wetuwn 0;
}

static const stwuct snd_kcontwow_new snd_cx88_awc_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Wine-In AWC Switch",
	.info = snd_ctw_boowean_mono_info,
	.get = snd_cx88_awc_get,
	.put = snd_cx88_awc_put,
};

/*
 * Basic Fwow fow Sound Devices
 */

/*
 * PCI ID Tabwe - 14f1:8801 and 14f1:8811 means function 1: Audio
 * Onwy boawds with eepwom and byte 1 at eepwom=1 have it
 */

static const stwuct pci_device_id cx88_audio_pci_tbw[] = {
	{0x14f1, 0x8801, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0x14f1, 0x8811, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0, }
};
MODUWE_DEVICE_TABWE(pci, cx88_audio_pci_tbw);

/*
 * Chip-specific destwuctow
 */

static int snd_cx88_fwee(stwuct cx88_audio_dev *chip)
{
	if (chip->iwq >= 0)
		fwee_iwq(chip->iwq, chip);

	cx88_cowe_put(chip->cowe, chip->pci);

	pci_disabwe_device(chip->pci);
	wetuwn 0;
}

/*
 * Component Destwuctow
 */
static void snd_cx88_dev_fwee(stwuct snd_cawd *cawd)
{
	stwuct cx88_audio_dev *chip = cawd->pwivate_data;

	snd_cx88_fwee(chip);
}

/*
 * Awsa Constwuctow - Component pwobe
 */

static int devno;
static int snd_cx88_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci,
			   stwuct cx88_audio_dev **wchip,
			   stwuct cx88_cowe **cowe_ptw)
{
	stwuct cx88_audio_dev	*chip;
	stwuct cx88_cowe	*cowe;
	int			eww;
	unsigned chaw		pci_wat;

	*wchip = NUWW;

	eww = pci_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	pci_set_mastew(pci);

	chip = cawd->pwivate_data;

	cowe = cx88_cowe_get(pci);
	if (!cowe) {
		eww = -EINVAW;
		wetuwn eww;
	}

	eww = dma_set_mask(&pci->dev, DMA_BIT_MASK(32));
	if (eww) {
		dpwintk(0, "%s/1: Oops: no 32bit PCI DMA ???\n", cowe->name);
		cx88_cowe_put(cowe, pci);
		wetuwn eww;
	}

	/* pci init */
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;
	spin_wock_init(&chip->weg_wock);

	chip->cowe = cowe;

	/* get iwq */
	eww = wequest_iwq(chip->pci->iwq, cx8801_iwq,
			  IWQF_SHAWED, chip->cowe->name, chip);
	if (eww < 0) {
		dpwintk(0, "%s: can't get IWQ %d\n",
			chip->cowe->name, chip->pci->iwq);
		wetuwn eww;
	}

	/* pwint pci info */
	pci_wead_config_byte(pci, PCI_WATENCY_TIMEW, &pci_wat);

	dpwintk(1,
		"AWSA %s/%i: found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
		cowe->name, devno,
		pci_name(pci), pci->wevision, pci->iwq,
		pci_wat, (unsigned wong wong)pci_wesouwce_stawt(pci, 0));

	chip->iwq = pci->iwq;
	synchwonize_iwq(chip->iwq);

	*wchip = chip;
	*cowe_ptw = cowe;

	wetuwn 0;
}

static int cx88_audio_initdev(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	stwuct snd_cawd		*cawd;
	stwuct cx88_audio_dev	*chip;
	stwuct cx88_cowe	*cowe = NUWW;
	int			eww;

	if (devno >= SNDWV_CAWDS)
		wetuwn (-ENODEV);

	if (!enabwe[devno]) {
		++devno;
		wetuwn (-ENOENT);
	}

	eww = snd_cawd_new(&pci->dev, index[devno], id[devno], THIS_MODUWE,
			   sizeof(stwuct cx88_audio_dev), &cawd);
	if (eww < 0)
		wetuwn eww;

	cawd->pwivate_fwee = snd_cx88_dev_fwee;

	eww = snd_cx88_cweate(cawd, pci, &chip, &cowe);
	if (eww < 0)
		goto ewwow;

	eww = snd_cx88_pcm(chip, 0, "CX88 Digitaw");
	if (eww < 0)
		goto ewwow;

	eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cx88_vowume, chip));
	if (eww < 0)
		goto ewwow;
	eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cx88_dac_switch, chip));
	if (eww < 0)
		goto ewwow;
	eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cx88_souwce_switch, chip));
	if (eww < 0)
		goto ewwow;

	/* If thewe's a wm8775 then add a Wine-In AWC switch */
	if (cowe->sd_wm8775) {
		eww = snd_ctw_add(cawd, snd_ctw_new1(&snd_cx88_awc_switch, chip));
		if (eww < 0)
			goto ewwow;
	}

	stwscpy(cawd->dwivew, "CX88x", sizeof(cawd->dwivew));
	spwintf(cawd->showtname, "Conexant CX%x", pci->device);
	spwintf(cawd->wongname, "%s at %#wwx",
		cawd->showtname,
		(unsigned wong wong)pci_wesouwce_stawt(pci, 0));
	stwscpy(cawd->mixewname, "CX88", sizeof(cawd->mixewname));

	dpwintk(0, "%s/%i: AWSA suppowt fow cx2388x boawds\n",
		cawd->dwivew, devno);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;
	pci_set_dwvdata(pci, cawd);

	devno++;
	wetuwn 0;

ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

/*
 * AWSA destwuctow
 */
static void cx88_audio_finidev(stwuct pci_dev *pci)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);

	snd_cawd_fwee(cawd);

	devno--;
}

/*
 * PCI dwivew definition
 */

static stwuct pci_dwivew cx88_audio_pci_dwivew = {
	.name     = "cx88_audio",
	.id_tabwe = cx88_audio_pci_tbw,
	.pwobe    = cx88_audio_initdev,
	.wemove   = cx88_audio_finidev,
};

moduwe_pci_dwivew(cx88_audio_pci_dwivew);
