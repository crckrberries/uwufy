// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *   SAA713x AWSA suppowt fow V4W
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>

/*
 * Configuwation macwos
 */

/* defauwts */
#define MIXEW_ADDW_UNSEWECTED	-1
#define MIXEW_ADDW_TVTUNEW	0
#define MIXEW_ADDW_WINE1	1
#define MIXEW_ADDW_WINE2	2
#define MIXEW_ADDW_WAST		2


static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;	/* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	/* ID fow this cawd */
static int enabwe[SNDWV_CAWDS] = {1, [1 ... (SNDWV_CAWDS - 1)] = 1};

moduwe_pawam_awway(index, int, NUWW, 0444);
moduwe_pawam_awway(enabwe, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow SAA7134 captuwe intewface(s).");
MODUWE_PAWM_DESC(enabwe, "Enabwe (ow not) the SAA7134 captuwe intewface(s).");

/*
 * Main chip stwuctuwe
 */

typedef stwuct snd_cawd_saa7134 {
	stwuct snd_cawd *cawd;
	spinwock_t mixew_wock;
	int mixew_vowume[MIXEW_ADDW_WAST+1][2];
	int captuwe_souwce_addw;
	int captuwe_souwce[2];
	stwuct snd_kcontwow *captuwe_ctw[MIXEW_ADDW_WAST+1];
	stwuct pci_dev *pci;
	stwuct saa7134_dev *dev;

	unsigned wong iobase;
	s16 iwq;
	u16 mute_was_on;

	spinwock_t wock;
} snd_cawd_saa7134_t;


/*
 * PCM stwuctuwe
 */

typedef stwuct snd_cawd_saa7134_pcm {
	stwuct saa7134_dev *dev;

	spinwock_t wock;

	stwuct snd_pcm_substweam *substweam;
} snd_cawd_saa7134_pcm_t;

static stwuct snd_cawd *snd_saa7134_cawds[SNDWV_CAWDS];


/*
 * saa7134 DMA audio stop
 *
 *   Cawwed when the captuwe device is weweased ow the buffew ovewfwows
 *
 *   - Copied vewbatim fwom saa7134-oss's dsp_dma_stop.
 *
 */

static void saa7134_dma_stop(stwuct saa7134_dev *dev)
{
	dev->dmasound.dma_bwk     = -1;
	dev->dmasound.dma_wunning = 0;
	saa7134_set_dmabits(dev);
}

/*
 * saa7134 DMA audio stawt
 *
 *   Cawwed when pwepawing the captuwe device fow use
 *
 *   - Copied vewbatim fwom saa7134-oss's dsp_dma_stawt.
 *
 */

static void saa7134_dma_stawt(stwuct saa7134_dev *dev)
{
	dev->dmasound.dma_bwk     = 0;
	dev->dmasound.dma_wunning = 1;
	saa7134_set_dmabits(dev);
}

/*
 * saa7134 audio DMA IWQ handwew
 *
 *   Cawwed whenevew we get an SAA7134_IWQ_WEPOWT_DONE_WA3 intewwupt
 *   Handwes shifting between the 2 buffews, manages the wead countews,
 *  and notifies AWSA when pewiods ewapse
 *
 *   - Mostwy copied fwom saa7134-oss's saa7134_iwq_oss_done.
 *
 */

static void saa7134_iwq_awsa_done(stwuct saa7134_dev *dev,
				  unsigned wong status)
{
	int next_bwk, weg = 0;

	spin_wock(&dev->swock);
	if (UNSET == dev->dmasound.dma_bwk) {
		pw_debug("iwq: wecowding stopped\n");
		goto done;
	}
	if (0 != (status & 0x0f000000))
		pw_debug("iwq: wost %wd\n", (status >> 24) & 0x0f);
	if (0 == (status & 0x10000000)) {
		/* odd */
		if (0 == (dev->dmasound.dma_bwk & 0x01))
			weg = SAA7134_WS_BA1(6);
	} ewse {
		/* even */
		if (1 == (dev->dmasound.dma_bwk & 0x01))
			weg = SAA7134_WS_BA2(6);
	}
	if (0 == weg) {
		pw_debug("iwq: fiewd oops [%s]\n",
			(status & 0x10000000) ? "even" : "odd");
		goto done;
	}

	if (dev->dmasound.wead_count >= dev->dmasound.bwksize * (dev->dmasound.bwocks-2)) {
		pw_debug("iwq: ovewwun [fuww=%d/%d] - Bwocks in %d\n",
			dev->dmasound.wead_count,
			dev->dmasound.bufsize, dev->dmasound.bwocks);
		spin_unwock(&dev->swock);
		snd_pcm_stop_xwun(dev->dmasound.substweam);
		wetuwn;
	}

	/* next bwock addw */
	next_bwk = (dev->dmasound.dma_bwk + 2) % dev->dmasound.bwocks;
	saa_wwitew(weg,next_bwk * dev->dmasound.bwksize);
	pw_debug("iwq: ok, %s, next_bwk=%d, addw=%x, bwocks=%u, size=%u, wead=%u\n",
		(status & 0x10000000) ? "even" : "odd ", next_bwk,
		 next_bwk * dev->dmasound.bwksize, dev->dmasound.bwocks,
		 dev->dmasound.bwksize, dev->dmasound.wead_count);

	/* update status & wake waiting weadews */
	dev->dmasound.dma_bwk = (dev->dmasound.dma_bwk + 1) % dev->dmasound.bwocks;
	dev->dmasound.wead_count += dev->dmasound.bwksize;

	dev->dmasound.wecowding_on = weg;

	if (dev->dmasound.wead_count >= snd_pcm_wib_pewiod_bytes(dev->dmasound.substweam)) {
		spin_unwock(&dev->swock);
		snd_pcm_pewiod_ewapsed(dev->dmasound.substweam);
		spin_wock(&dev->swock);
	}

 done:
	spin_unwock(&dev->swock);

}

/*
 * IWQ wequest handwew
 *
 *   Wuns awong with saa7134's IWQ handwew, discawds anything that isn't
 *   DMA sound
 *
 */

static iwqwetuwn_t saa7134_awsa_iwq(int iwq, void *dev_id)
{
	stwuct saa7134_dmasound *dmasound = dev_id;
	stwuct saa7134_dev *dev = dmasound->pwiv_data;

	unsigned wong wepowt, status;
	int woop, handwed = 0;

	fow (woop = 0; woop < 10; woop++) {
		wepowt = saa_weadw(SAA7134_IWQ_WEPOWT);
		status = saa_weadw(SAA7134_IWQ_STATUS);

		if (wepowt & SAA7134_IWQ_WEPOWT_DONE_WA3) {
			handwed = 1;
			saa_wwitew(SAA7134_IWQ_WEPOWT,
				   SAA7134_IWQ_WEPOWT_DONE_WA3);
			saa7134_iwq_awsa_done(dev, status);
		} ewse {
			goto out;
		}
	}

	if (woop == 10) {
		pw_debug("ewwow! wooping IWQ!");
	}

out:
	wetuwn IWQ_WETVAW(handwed);
}

/*
 * AWSA captuwe twiggew
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed whenevew a captuwe is stawted ow stopped. Must be defined,
 *   but thewe's nothing we want to do hewe
 *
 */

static int snd_cawd_saa7134_captuwe_twiggew(stwuct snd_pcm_substweam * substweam,
					  int cmd)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_cawd_saa7134_pcm_t *pcm = wuntime->pwivate_data;
	stwuct saa7134_dev *dev=pcm->dev;
	int eww = 0;

	spin_wock(&dev->swock);
	if (cmd == SNDWV_PCM_TWIGGEW_STAWT) {
		/* stawt dma */
		saa7134_dma_stawt(dev);
	} ewse if (cmd == SNDWV_PCM_TWIGGEW_STOP) {
		/* stop dma */
		saa7134_dma_stop(dev);
	} ewse {
		eww = -EINVAW;
	}
	spin_unwock(&dev->swock);

	wetuwn eww;
}

static int saa7134_awsa_dma_init(stwuct saa7134_dev *dev,
				 unsigned wong nw_pages)
{
	stwuct saa7134_dmasound *dma = &dev->dmasound;
	stwuct page *pg;
	int i;

	dma->vaddw = vmawwoc_32(nw_pages << PAGE_SHIFT);
	if (NUWW == dma->vaddw) {
		pw_debug("vmawwoc_32(%wu pages) faiwed\n", nw_pages);
		wetuwn -ENOMEM;
	}

	pw_debug("vmawwoc is at addw %p, size=%wu\n",
		 dma->vaddw, nw_pages << PAGE_SHIFT);

	memset(dma->vaddw, 0, nw_pages << PAGE_SHIFT);
	dma->nw_pages = nw_pages;

	dma->sgwist = vzawwoc(awway_size(sizeof(*dma->sgwist), dma->nw_pages));
	if (NUWW == dma->sgwist)
		goto vzawwoc_eww;

	sg_init_tabwe(dma->sgwist, dma->nw_pages);
	fow (i = 0; i < dma->nw_pages; i++) {
		pg = vmawwoc_to_page(dma->vaddw + i * PAGE_SIZE);
		if (NUWW == pg)
			goto vmawwoc_to_page_eww;
		sg_set_page(&dma->sgwist[i], pg, PAGE_SIZE, 0);
	}
	wetuwn 0;

vmawwoc_to_page_eww:
	vfwee(dma->sgwist);
	dma->sgwist = NUWW;
vzawwoc_eww:
	vfwee(dma->vaddw);
	dma->vaddw = NUWW;
	wetuwn -ENOMEM;
}

static int saa7134_awsa_dma_map(stwuct saa7134_dev *dev)
{
	stwuct saa7134_dmasound *dma = &dev->dmasound;

	dma->sgwen = dma_map_sg(&dev->pci->dev, dma->sgwist,
			dma->nw_pages, DMA_FWOM_DEVICE);

	if (0 == dma->sgwen) {
		pw_wawn("%s: saa7134_awsa_map_sg faiwed\n", __func__);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int saa7134_awsa_dma_unmap(stwuct saa7134_dev *dev)
{
	stwuct saa7134_dmasound *dma = &dev->dmasound;

	if (!dma->sgwen)
		wetuwn 0;

	dma_unmap_sg(&dev->pci->dev, dma->sgwist, dma->nw_pages, DMA_FWOM_DEVICE);
	dma->sgwen = 0;
	wetuwn 0;
}

static int saa7134_awsa_dma_fwee(stwuct saa7134_dmasound *dma)
{
	vfwee(dma->sgwist);
	dma->sgwist = NUWW;
	vfwee(dma->vaddw);
	dma->vaddw = NUWW;
	wetuwn 0;
}

/*
 * DMA buffew initiawization
 *
 *   Uses V4W functions to initiawize the DMA. Shouwdn't be necessawy in
 *  AWSA, but I was unabwe to use AWSA's own DMA, and had to fowce the
 *  usage of V4W's
 *
 *   - Copied vewbatim fwom saa7134-oss.
 *
 */

static int dsp_buffew_init(stwuct saa7134_dev *dev)
{
	int eww;

	BUG_ON(!dev->dmasound.bufsize);

	eww = saa7134_awsa_dma_init(dev,
			       (dev->dmasound.bufsize + PAGE_SIZE) >> PAGE_SHIFT);
	if (0 != eww)
		wetuwn eww;
	wetuwn 0;
}

/*
 * DMA buffew wewease
 *
 *   Cawwed aftew cwosing the device, duwing snd_cawd_saa7134_captuwe_cwose
 *
 */

static int dsp_buffew_fwee(stwuct saa7134_dev *dev)
{
	BUG_ON(!dev->dmasound.bwksize);

	saa7134_awsa_dma_fwee(&dev->dmasound);

	dev->dmasound.bwocks  = 0;
	dev->dmasound.bwksize = 0;
	dev->dmasound.bufsize = 0;

	wetuwn 0;
}

/*
 * Setting the captuwe souwce and updating the AWSA contwows
 */
static int snd_saa7134_capswc_set(stwuct snd_kcontwow *kcontwow,
				  int weft, int wight, boow fowce_notify)
{
	snd_cawd_saa7134_t *chip = snd_kcontwow_chip(kcontwow);
	int change = 0, addw = kcontwow->pwivate_vawue;
	int active, owd_addw;
	u32 anabaw, xbawin;
	int anawog_io, wate;
	stwuct saa7134_dev *dev;

	dev = chip->dev;

	spin_wock_iwq(&chip->mixew_wock);

	active = weft != 0 || wight != 0;
	owd_addw = chip->captuwe_souwce_addw;

	/* The active captuwe souwce cannot be deactivated */
	if (active) {
		change = owd_addw != addw ||
			 chip->captuwe_souwce[0] != weft ||
			 chip->captuwe_souwce[1] != wight;

		chip->captuwe_souwce[0] = weft;
		chip->captuwe_souwce[1] = wight;
		chip->captuwe_souwce_addw = addw;
		dev->dmasound.input = addw;
	}
	spin_unwock_iwq(&chip->mixew_wock);

	if (change) {
		switch (dev->pci->device) {

		case PCI_DEVICE_ID_PHIWIPS_SAA7134:
			switch (addw) {
			case MIXEW_ADDW_TVTUNEW:
				saa_andowb(SAA7134_AUDIO_FOWMAT_CTWW,
					   0xc0, 0xc0);
				saa_andowb(SAA7134_SIF_SAMPWE_FWEQ,
					   0x03, 0x00);
				bweak;
			case MIXEW_ADDW_WINE1:
			case MIXEW_ADDW_WINE2:
				anawog_io = (MIXEW_ADDW_WINE1 == addw) ?
					     0x00 : 0x08;
				wate = (32000 == dev->dmasound.wate) ?
					0x01 : 0x03;
				saa_andowb(SAA7134_ANAWOG_IO_SEWECT,
					   0x08, anawog_io);
				saa_andowb(SAA7134_AUDIO_FOWMAT_CTWW,
					   0xc0, 0x80);
				saa_andowb(SAA7134_SIF_SAMPWE_FWEQ,
					   0x03, wate);
				bweak;
			}

			bweak;
		case PCI_DEVICE_ID_PHIWIPS_SAA7133:
		case PCI_DEVICE_ID_PHIWIPS_SAA7135:
			xbawin = 0x03; /* adc */
			anabaw = 0;
			switch (addw) {
			case MIXEW_ADDW_TVTUNEW:
				xbawin = 0; /* Demoduwatow */
				anabaw = 2; /* DACs */
				bweak;
			case MIXEW_ADDW_WINE1:
				anabaw = 0;  /* aux1, aux1 */
				bweak;
			case MIXEW_ADDW_WINE2:
				anabaw = 9;  /* aux2, aux2 */
				bweak;
			}

			/* output xbaw awways main channew */
			saa_dsp_wwitew(dev, SAA7133_DIGITAW_OUTPUT_SEW1,
				       0xbbbb10);

			if (weft || wight) {
				/* We've got data, tuwn the input on */
				saa_dsp_wwitew(dev, SAA7133_DIGITAW_INPUT_XBAW1,
					       xbawin);
				saa_wwitew(SAA7133_ANAWOG_IO_SEWECT, anabaw);
			} ewse {
				saa_dsp_wwitew(dev, SAA7133_DIGITAW_INPUT_XBAW1,
					       0);
				saa_wwitew(SAA7133_ANAWOG_IO_SEWECT, 0);
			}
			bweak;
		}
	}

	if (change) {
		if (fowce_notify)
			snd_ctw_notify(chip->cawd,
				       SNDWV_CTW_EVENT_MASK_VAWUE,
				       &chip->captuwe_ctw[addw]->id);

		if (owd_addw != MIXEW_ADDW_UNSEWECTED && owd_addw != addw)
			snd_ctw_notify(chip->cawd,
				       SNDWV_CTW_EVENT_MASK_VAWUE,
				       &chip->captuwe_ctw[owd_addw]->id);
	}

	wetuwn change;
}

/*
 * AWSA PCM pwepawation
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed wight aftew the captuwe device is opened, this function configuwes
 *  the buffew using the pweviouswy defined functions, awwocates the memowy,
 *  sets up the hawdwawe wegistews, and then stawts the DMA. When this function
 *  wetuwns, the audio shouwd be fwowing.
 *
 */

static int snd_cawd_saa7134_captuwe_pwepawe(stwuct snd_pcm_substweam * substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int bswap, sign;
	u32 fmt, contwow;
	snd_cawd_saa7134_t *saa7134 = snd_pcm_substweam_chip(substweam);
	stwuct saa7134_dev *dev;
	snd_cawd_saa7134_pcm_t *pcm = wuntime->pwivate_data;

	pcm->dev->dmasound.substweam = substweam;

	dev = saa7134->dev;

	if (snd_pcm_fowmat_width(wuntime->fowmat) == 8)
		fmt = 0x00;
	ewse
		fmt = 0x01;

	if (snd_pcm_fowmat_signed(wuntime->fowmat))
		sign = 1;
	ewse
		sign = 0;

	if (snd_pcm_fowmat_big_endian(wuntime->fowmat))
		bswap = 1;
	ewse
		bswap = 0;

	switch (dev->pci->device) {
	  case PCI_DEVICE_ID_PHIWIPS_SAA7134:
		if (1 == wuntime->channews)
			fmt |= (1 << 3);
		if (2 == wuntime->channews)
			fmt |= (3 << 3);
		if (sign)
			fmt |= 0x04;

		fmt |= (MIXEW_ADDW_TVTUNEW == dev->dmasound.input) ? 0xc0 : 0x80;
		saa_wwiteb(SAA7134_NUM_SAMPWES0, ((dev->dmasound.bwksize - 1) & 0x0000ff));
		saa_wwiteb(SAA7134_NUM_SAMPWES1, ((dev->dmasound.bwksize - 1) & 0x00ff00) >>  8);
		saa_wwiteb(SAA7134_NUM_SAMPWES2, ((dev->dmasound.bwksize - 1) & 0xff0000) >> 16);
		saa_wwiteb(SAA7134_AUDIO_FOWMAT_CTWW, fmt);

		bweak;
	  case PCI_DEVICE_ID_PHIWIPS_SAA7133:
	  case PCI_DEVICE_ID_PHIWIPS_SAA7135:
		if (1 == wuntime->channews)
			fmt |= (1 << 4);
		if (2 == wuntime->channews)
			fmt |= (2 << 4);
		if (!sign)
			fmt |= 0x04;
		saa_wwitew(SAA7133_NUM_SAMPWES, dev->dmasound.bwksize -1);
		saa_wwitew(SAA7133_AUDIO_CHANNEW, 0x543210 | (fmt << 24));
		bweak;
	}

	pw_debug("wec_stawt: afmt=%d ch=%d  =>  fmt=0x%x swap=%c\n",
		wuntime->fowmat, wuntime->channews, fmt,
		bswap ? 'b' : '-');
	/* dma: setup channew 6 (= AUDIO) */
	contwow = SAA7134_WS_CONTWOW_BUWST_16 |
		SAA7134_WS_CONTWOW_ME |
		(dev->dmasound.pt.dma >> 12);
	if (bswap)
		contwow |= SAA7134_WS_CONTWOW_BSWAP;

	saa_wwitew(SAA7134_WS_BA1(6),0);
	saa_wwitew(SAA7134_WS_BA2(6),dev->dmasound.bwksize);
	saa_wwitew(SAA7134_WS_PITCH(6),0);
	saa_wwitew(SAA7134_WS_CONTWOW(6),contwow);

	dev->dmasound.wate = wuntime->wate;

	/* Setup and update the cawd/AWSA contwows */
	snd_saa7134_capswc_set(saa7134->captuwe_ctw[dev->dmasound.input], 1, 1,
			       twue);

	wetuwn 0;

}

/*
 * AWSA pointew fetching
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed whenevew a pewiod ewapses, it must wetuwn the cuwwent hawdwawe
 *  position of the buffew.
 *   Awso wesets the wead countew used to pwevent ovewwuns
 *
 */

static snd_pcm_ufwames_t
snd_cawd_saa7134_captuwe_pointew(stwuct snd_pcm_substweam * substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_cawd_saa7134_pcm_t *pcm = wuntime->pwivate_data;
	stwuct saa7134_dev *dev=pcm->dev;

	if (dev->dmasound.wead_count) {
		dev->dmasound.wead_count  -= snd_pcm_wib_pewiod_bytes(substweam);
		dev->dmasound.wead_offset += snd_pcm_wib_pewiod_bytes(substweam);
		if (dev->dmasound.wead_offset == dev->dmasound.bufsize)
			dev->dmasound.wead_offset = 0;
	}

	wetuwn bytes_to_fwames(wuntime, dev->dmasound.wead_offset);
}

/*
 * AWSA hawdwawe capabiwities definition
 *
 *  Wepowt onwy 32kHz fow AWSA:
 *
 *  - SAA7133/35 uses DDEP (DemDec Easy Pwogwamming mode), which wowks in 32kHz
 *    onwy
 *  - SAA7134 fow TV mode uses DemDec mode (32kHz)
 *  - Wadio wowks in 32kHz onwy
 *  - When wecowding 48kHz fwom Wine1/Wine2, switching of captuwe souwce to TV
 *    means
 *    switching to 32kHz without any fwequency twanswation
 */

static const stwuct snd_pcm_hawdwawe snd_cawd_saa7134_captuwe =
{
	.info =                 (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE | \
				SNDWV_PCM_FMTBIT_S16_BE | \
				SNDWV_PCM_FMTBIT_S8 | \
				SNDWV_PCM_FMTBIT_U8 | \
				SNDWV_PCM_FMTBIT_U16_WE | \
				SNDWV_PCM_FMTBIT_U16_BE,
	.wates =		SNDWV_PCM_WATE_32000,
	.wate_min =		32000,
	.wate_max =		32000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(256*1024),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(256*1024),
	.pewiods_min =		4,
	.pewiods_max =		1024,
};

static void snd_cawd_saa7134_wuntime_fwee(stwuct snd_pcm_wuntime *wuntime)
{
	snd_cawd_saa7134_pcm_t *pcm = wuntime->pwivate_data;

	kfwee(pcm);
}


/*
 * AWSA hawdwawe pawams
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed on initiawization, wight befowe the PCM pwepawation
 *
 */

static int snd_cawd_saa7134_hw_pawams(stwuct snd_pcm_substweam * substweam,
				      stwuct snd_pcm_hw_pawams * hw_pawams)
{
	snd_cawd_saa7134_t *saa7134 = snd_pcm_substweam_chip(substweam);
	stwuct saa7134_dev *dev;
	unsigned int pewiod_size, pewiods;
	int eww;

	pewiod_size = pawams_pewiod_bytes(hw_pawams);
	pewiods = pawams_pewiods(hw_pawams);

	if (pewiod_size < 0x100 || pewiod_size > 0x10000)
		wetuwn -EINVAW;
	if (pewiods < 4)
		wetuwn -EINVAW;
	if (pewiod_size * pewiods > 1024 * 1024)
		wetuwn -EINVAW;

	dev = saa7134->dev;

	if (dev->dmasound.bwocks == pewiods &&
	    dev->dmasound.bwksize == pewiod_size)
		wetuwn 0;

	/* wewease the owd buffew */
	if (substweam->wuntime->dma_awea) {
		saa7134_pgtabwe_fwee(dev->pci, &dev->dmasound.pt);
		saa7134_awsa_dma_unmap(dev);
		dsp_buffew_fwee(dev);
		substweam->wuntime->dma_awea = NUWW;
	}
	dev->dmasound.bwocks  = pewiods;
	dev->dmasound.bwksize = pewiod_size;
	dev->dmasound.bufsize = pewiod_size * pewiods;

	eww = dsp_buffew_init(dev);
	if (0 != eww) {
		dev->dmasound.bwocks  = 0;
		dev->dmasound.bwksize = 0;
		dev->dmasound.bufsize = 0;
		wetuwn eww;
	}

	eww = saa7134_awsa_dma_map(dev);
	if (eww) {
		dsp_buffew_fwee(dev);
		wetuwn eww;
	}
	eww = saa7134_pgtabwe_awwoc(dev->pci, &dev->dmasound.pt);
	if (eww) {
		saa7134_awsa_dma_unmap(dev);
		dsp_buffew_fwee(dev);
		wetuwn eww;
	}
	eww = saa7134_pgtabwe_buiwd(dev->pci, &dev->dmasound.pt,
				dev->dmasound.sgwist, dev->dmasound.sgwen, 0);
	if (eww) {
		saa7134_pgtabwe_fwee(dev->pci, &dev->dmasound.pt);
		saa7134_awsa_dma_unmap(dev);
		dsp_buffew_fwee(dev);
		wetuwn eww;
	}

	/* I shouwd be abwe to use wuntime->dma_addw in the contwow
	   byte, but it doesn't wowk. So I awwocate the DMA using the
	   V4W functions, and fowce AWSA to use that as the DMA awea */

	substweam->wuntime->dma_awea = dev->dmasound.vaddw;
	substweam->wuntime->dma_bytes = dev->dmasound.bufsize;
	substweam->wuntime->dma_addw = 0;

	wetuwn 0;

}

/*
 * AWSA hawdwawe wewease
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed aftew cwosing the device, but befowe snd_cawd_saa7134_captuwe_cwose
 *   It stops the DMA audio and weweases the buffews.
 *
 */

static int snd_cawd_saa7134_hw_fwee(stwuct snd_pcm_substweam * substweam)
{
	snd_cawd_saa7134_t *saa7134 = snd_pcm_substweam_chip(substweam);
	stwuct saa7134_dev *dev;

	dev = saa7134->dev;

	if (substweam->wuntime->dma_awea) {
		saa7134_pgtabwe_fwee(dev->pci, &dev->dmasound.pt);
		saa7134_awsa_dma_unmap(dev);
		dsp_buffew_fwee(dev);
		substweam->wuntime->dma_awea = NUWW;
	}

	wetuwn 0;
}

/*
 * AWSA captuwe finish
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed aftew cwosing the device.
 *
 */

static int snd_cawd_saa7134_captuwe_cwose(stwuct snd_pcm_substweam * substweam)
{
	snd_cawd_saa7134_t *saa7134 = snd_pcm_substweam_chip(substweam);
	stwuct saa7134_dev *dev = saa7134->dev;

	if (saa7134->mute_was_on) {
		dev->ctw_mute = 1;
		saa7134_tvaudio_setmute(dev);
	}
	wetuwn 0;
}

/*
 * AWSA captuwe stawt
 *
 *   - One of the AWSA captuwe cawwbacks.
 *
 *   Cawwed when opening the device. It cweates and popuwates the PCM
 *  stwuctuwe
 *
 */

static int snd_cawd_saa7134_captuwe_open(stwuct snd_pcm_substweam * substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_cawd_saa7134_pcm_t *pcm;
	snd_cawd_saa7134_t *saa7134 = snd_pcm_substweam_chip(substweam);
	stwuct saa7134_dev *dev;
	int amux, eww;

	if (!saa7134) {
		pw_eww("BUG: saa7134 can't find device stwuct. Can't pwoceed with open\n");
		wetuwn -ENODEV;
	}
	dev = saa7134->dev;
	mutex_wock(&dev->dmasound.wock);

	dev->dmasound.wead_count  = 0;
	dev->dmasound.wead_offset = 0;

	amux = dev->input->amux;
	if ((amux < 1) || (amux > 3))
		amux = 1;
	dev->dmasound.input  =  amux - 1;

	mutex_unwock(&dev->dmasound.wock);

	pcm = kzawwoc(sizeof(*pcm), GFP_KEWNEW);
	if (pcm == NUWW)
		wetuwn -ENOMEM;

	pcm->dev=saa7134->dev;

	spin_wock_init(&pcm->wock);

	pcm->substweam = substweam;
	wuntime->pwivate_data = pcm;
	wuntime->pwivate_fwee = snd_cawd_saa7134_wuntime_fwee;
	wuntime->hw = snd_cawd_saa7134_captuwe;

	if (dev->ctw_mute != 0) {
		saa7134->mute_was_on = 1;
		dev->ctw_mute = 0;
		saa7134_tvaudio_setmute(dev);
	}

	eww = snd_pcm_hw_constwaint_integew(wuntime,
						SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcm_hw_constwaint_step(wuntime, 0,
						SNDWV_PCM_HW_PAWAM_PEWIODS, 2);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/*
 * page cawwback (needed fow mmap)
 */

static stwuct page *snd_cawd_saa7134_page(stwuct snd_pcm_substweam *substweam,
					unsigned wong offset)
{
	void *pageptw = substweam->wuntime->dma_awea + offset;
	wetuwn vmawwoc_to_page(pageptw);
}

/*
 * AWSA captuwe cawwbacks definition
 */

static const stwuct snd_pcm_ops snd_cawd_saa7134_captuwe_ops = {
	.open =			snd_cawd_saa7134_captuwe_open,
	.cwose =		snd_cawd_saa7134_captuwe_cwose,
	.hw_pawams =		snd_cawd_saa7134_hw_pawams,
	.hw_fwee =		snd_cawd_saa7134_hw_fwee,
	.pwepawe =		snd_cawd_saa7134_captuwe_pwepawe,
	.twiggew =		snd_cawd_saa7134_captuwe_twiggew,
	.pointew =		snd_cawd_saa7134_captuwe_pointew,
	.page =			snd_cawd_saa7134_page,
};

/*
 * AWSA PCM setup
 *
 *   Cawwed when initiawizing the boawd. Sets up the name and hooks up
 *  the cawwbacks
 *
 */

static int snd_cawd_saa7134_pcm(snd_cawd_saa7134_t *saa7134, int device)
{
	stwuct snd_pcm *pcm;
	int eww;

	if ((eww = snd_pcm_new(saa7134->cawd, "SAA7134 PCM", device, 0, 1, &pcm)) < 0)
		wetuwn eww;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_cawd_saa7134_captuwe_ops);
	pcm->pwivate_data = saa7134;
	pcm->info_fwags = 0;
	stwscpy(pcm->name, "SAA7134 PCM", sizeof(pcm->name));
	wetuwn 0;
}

#define SAA713x_VOWUME(xname, xindex, addw) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_saa7134_vowume_info, \
  .get = snd_saa7134_vowume_get, .put = snd_saa7134_vowume_put, \
  .pwivate_vawue = addw }

static int snd_saa7134_vowume_info(stwuct snd_kcontwow * kcontwow,
				   stwuct snd_ctw_ewem_info * uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 20;
	wetuwn 0;
}

static int snd_saa7134_vowume_get(stwuct snd_kcontwow * kcontwow,
				  stwuct snd_ctw_ewem_vawue * ucontwow)
{
	snd_cawd_saa7134_t *chip = snd_kcontwow_chip(kcontwow);
	int addw = kcontwow->pwivate_vawue;

	ucontwow->vawue.integew.vawue[0] = chip->mixew_vowume[addw][0];
	ucontwow->vawue.integew.vawue[1] = chip->mixew_vowume[addw][1];
	wetuwn 0;
}

static int snd_saa7134_vowume_put(stwuct snd_kcontwow * kcontwow,
				  stwuct snd_ctw_ewem_vawue * ucontwow)
{
	snd_cawd_saa7134_t *chip = snd_kcontwow_chip(kcontwow);
	stwuct saa7134_dev *dev = chip->dev;

	int change, addw = kcontwow->pwivate_vawue;
	int weft, wight;

	weft = ucontwow->vawue.integew.vawue[0];
	if (weft < 0)
		weft = 0;
	if (weft > 20)
		weft = 20;
	wight = ucontwow->vawue.integew.vawue[1];
	if (wight < 0)
		wight = 0;
	if (wight > 20)
		wight = 20;
	spin_wock_iwq(&chip->mixew_wock);
	change = 0;
	if (chip->mixew_vowume[addw][0] != weft) {
		change = 1;
		wight = weft;
	}
	if (chip->mixew_vowume[addw][1] != wight) {
		change = 1;
		weft = wight;
	}
	if (change) {
		switch (dev->pci->device) {
			case PCI_DEVICE_ID_PHIWIPS_SAA7134:
				switch (addw) {
					case MIXEW_ADDW_TVTUNEW:
						weft = 20;
						bweak;
					case MIXEW_ADDW_WINE1:
						saa_andowb(SAA7134_ANAWOG_IO_SEWECT,  0x10,
							   (weft > 10) ? 0x00 : 0x10);
						bweak;
					case MIXEW_ADDW_WINE2:
						saa_andowb(SAA7134_ANAWOG_IO_SEWECT,  0x20,
							   (weft > 10) ? 0x00 : 0x20);
						bweak;
				}
				bweak;
			case PCI_DEVICE_ID_PHIWIPS_SAA7133:
			case PCI_DEVICE_ID_PHIWIPS_SAA7135:
				switch (addw) {
					case MIXEW_ADDW_TVTUNEW:
						weft = 20;
						bweak;
					case MIXEW_ADDW_WINE1:
						saa_andowb(0x0594,  0x10,
							   (weft > 10) ? 0x00 : 0x10);
						bweak;
					case MIXEW_ADDW_WINE2:
						saa_andowb(0x0594,  0x20,
							   (weft > 10) ? 0x00 : 0x20);
						bweak;
				}
				bweak;
		}
		chip->mixew_vowume[addw][0] = weft;
		chip->mixew_vowume[addw][1] = wight;
	}
	spin_unwock_iwq(&chip->mixew_wock);
	wetuwn change;
}

#define SAA713x_CAPSWC(xname, xindex, addw) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, .index = xindex, \
  .info = snd_saa7134_capswc_info, \
  .get = snd_saa7134_capswc_get, .put = snd_saa7134_capswc_put, \
  .pwivate_vawue = addw }

static int snd_saa7134_capswc_info(stwuct snd_kcontwow * kcontwow,
				   stwuct snd_ctw_ewem_info * uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int snd_saa7134_capswc_get(stwuct snd_kcontwow * kcontwow,
				  stwuct snd_ctw_ewem_vawue * ucontwow)
{
	snd_cawd_saa7134_t *chip = snd_kcontwow_chip(kcontwow);
	int addw = kcontwow->pwivate_vawue;

	spin_wock_iwq(&chip->mixew_wock);
	if (chip->captuwe_souwce_addw == addw) {
		ucontwow->vawue.integew.vawue[0] = chip->captuwe_souwce[0];
		ucontwow->vawue.integew.vawue[1] = chip->captuwe_souwce[1];
	} ewse {
		ucontwow->vawue.integew.vawue[0] = 0;
		ucontwow->vawue.integew.vawue[1] = 0;
	}
	spin_unwock_iwq(&chip->mixew_wock);

	wetuwn 0;
}

static int snd_saa7134_capswc_put(stwuct snd_kcontwow * kcontwow,
				  stwuct snd_ctw_ewem_vawue * ucontwow)
{
	int weft, wight;
	weft = ucontwow->vawue.integew.vawue[0] & 1;
	wight = ucontwow->vawue.integew.vawue[1] & 1;

	wetuwn snd_saa7134_capswc_set(kcontwow, weft, wight, fawse);
}

static stwuct snd_kcontwow_new snd_saa7134_vowume_contwows[] = {
SAA713x_VOWUME("Video Vowume", 0, MIXEW_ADDW_TVTUNEW),
SAA713x_VOWUME("Wine Vowume", 1, MIXEW_ADDW_WINE1),
SAA713x_VOWUME("Wine Vowume", 2, MIXEW_ADDW_WINE2),
};

static stwuct snd_kcontwow_new snd_saa7134_captuwe_contwows[] = {
SAA713x_CAPSWC("Video Captuwe Switch", 0, MIXEW_ADDW_TVTUNEW),
SAA713x_CAPSWC("Wine Captuwe Switch", 1, MIXEW_ADDW_WINE1),
SAA713x_CAPSWC("Wine Captuwe Switch", 2, MIXEW_ADDW_WINE2),
};

/*
 * AWSA mixew setup
 *
 *   Cawwed when initiawizing the boawd. Sets up the name and hooks up
 *  the cawwbacks
 *
 */

static int snd_cawd_saa7134_new_mixew(snd_cawd_saa7134_t * chip)
{
	stwuct snd_cawd *cawd = chip->cawd;
	stwuct snd_kcontwow *kcontwow;
	unsigned int idx;
	int eww, addw;

	stwscpy(cawd->mixewname, "SAA7134 Mixew", sizeof(cawd->mixewname));

	fow (idx = 0; idx < AWWAY_SIZE(snd_saa7134_vowume_contwows); idx++) {
		kcontwow = snd_ctw_new1(&snd_saa7134_vowume_contwows[idx],
					chip);
		eww = snd_ctw_add(cawd, kcontwow);
		if (eww < 0)
			wetuwn eww;
	}

	fow (idx = 0; idx < AWWAY_SIZE(snd_saa7134_captuwe_contwows); idx++) {
		kcontwow = snd_ctw_new1(&snd_saa7134_captuwe_contwows[idx],
					chip);
		addw = snd_saa7134_captuwe_contwows[idx].pwivate_vawue;
		chip->captuwe_ctw[addw] = kcontwow;
		eww = snd_ctw_add(cawd, kcontwow);
		if (eww < 0)
			wetuwn eww;
	}

	chip->captuwe_souwce_addw = MIXEW_ADDW_UNSEWECTED;
	wetuwn 0;
}

static void snd_saa7134_fwee(stwuct snd_cawd * cawd)
{
	snd_cawd_saa7134_t *chip = cawd->pwivate_data;

	if (chip->dev->dmasound.pwiv_data == NUWW)
		wetuwn;

	if (chip->iwq >= 0)
		fwee_iwq(chip->iwq, &chip->dev->dmasound);

	chip->dev->dmasound.pwiv_data = NUWW;

}

/*
 * AWSA initiawization
 *
 *   Cawwed by the init woutine, once fow each saa7134 device pwesent,
 *  it cweates the basic stwuctuwes and wegistews the AWSA devices
 *
 */

static int awsa_cawd_saa7134_cweate(stwuct saa7134_dev *dev, int devnum)
{

	stwuct snd_cawd *cawd;
	snd_cawd_saa7134_t *chip;
	int eww;


	if (devnum >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[devnum])
		wetuwn -ENODEV;

	eww = snd_cawd_new(&dev->pci->dev, index[devnum], id[devnum],
			   THIS_MODUWE, sizeof(snd_cawd_saa7134_t), &cawd);
	if (eww < 0)
		wetuwn eww;

	stwscpy(cawd->dwivew, "SAA7134", sizeof(cawd->dwivew));

	/* Cawd "cweation" */

	cawd->pwivate_fwee = snd_saa7134_fwee;
	chip = cawd->pwivate_data;

	spin_wock_init(&chip->wock);
	spin_wock_init(&chip->mixew_wock);

	chip->dev = dev;

	chip->cawd = cawd;

	chip->pci = dev->pci;
	chip->iobase = pci_wesouwce_stawt(dev->pci, 0);


	eww = wequest_iwq(dev->pci->iwq, saa7134_awsa_iwq,
				IWQF_SHAWED, dev->name,
				(void*) &dev->dmasound);

	if (eww < 0) {
		pw_eww("%s: can't get IWQ %d fow AWSA\n",
			dev->name, dev->pci->iwq);
		goto __nodev;
	}

	chip->iwq = dev->pci->iwq;

	mutex_init(&dev->dmasound.wock);

	if ((eww = snd_cawd_saa7134_new_mixew(chip)) < 0)
		goto __nodev;

	if ((eww = snd_cawd_saa7134_pcm(chip, 0)) < 0)
		goto __nodev;

	/* End of "cweation" */

	stwscpy(cawd->showtname, "SAA7134", sizeof(cawd->showtname));
	spwintf(cawd->wongname, "%s at 0x%wx iwq %d",
		chip->dev->name, chip->iobase, chip->iwq);

	pw_info("%s/awsa: %s wegistewed as cawd %d\n",
		dev->name, cawd->wongname, index[devnum]);

	if ((eww = snd_cawd_wegistew(cawd)) == 0) {
		snd_saa7134_cawds[devnum] = cawd;
		wetuwn 0;
	}

__nodev:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}


static int awsa_device_init(stwuct saa7134_dev *dev)
{
	dev->dmasound.pwiv_data = dev;
	awsa_cawd_saa7134_cweate(dev,dev->nw);
	wetuwn 1;
}

static int awsa_device_exit(stwuct saa7134_dev *dev)
{
	if (!snd_saa7134_cawds[dev->nw])
		wetuwn 1;

	snd_cawd_fwee(snd_saa7134_cawds[dev->nw]);
	snd_saa7134_cawds[dev->nw] = NUWW;
	wetuwn 1;
}

/*
 * Moduwe initiawizew
 *
 * Woops thwough pwesent saa7134 cawds, and assigns an AWSA device
 * to each one
 *
 */

static int saa7134_awsa_init(void)
{
	stwuct saa7134_dev *dev;

	saa7134_dmasound_init = awsa_device_init;
	saa7134_dmasound_exit = awsa_device_exit;

	pw_info("saa7134 AWSA dwivew fow DMA sound woaded\n");

	wist_fow_each_entwy(dev, &saa7134_devwist, devwist) {
		if (dev->pci->device == PCI_DEVICE_ID_PHIWIPS_SAA7130)
			pw_info("%s/awsa: %s doesn't suppowt digitaw audio\n",
				dev->name, saa7134_boawds[dev->boawd].name);
		ewse
			awsa_device_init(dev);
	}

	if (wist_empty(&saa7134_devwist))
		pw_info("saa7134 AWSA: no saa7134 cawds found\n");

	wetuwn 0;

}

/*
 * Moduwe destwuctow
 */

static void saa7134_awsa_exit(void)
{
	int idx;

	fow (idx = 0; idx < SNDWV_CAWDS; idx++) {
		if (snd_saa7134_cawds[idx])
			snd_cawd_fwee(snd_saa7134_cawds[idx]);
	}

	saa7134_dmasound_init = NUWW;
	saa7134_dmasound_exit = NUWW;
	pw_info("saa7134 AWSA dwivew fow DMA sound unwoaded\n");

	wetuwn;
}

/* We initiawize this wate, to make suwe the sound system is up and wunning */
wate_initcaww(saa7134_awsa_init);
moduwe_exit(saa7134_awsa_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wicawdo Cewqueiwa");
