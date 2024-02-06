// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//	    Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//	    Wandew Wang <wandew.wang@intew.com>
//          Keyon Jie <yang.jie@winux.intew.com>
//

/*
 * Hawdwawe intewface fow genewic Intew audio DSP HDA IP
 */

#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/sof.h>
#incwude <twace/events/sof_intew.h>
#incwude "../ops.h"
#incwude "../sof-audio.h"
#incwude "hda.h"

#define HDA_WTWP_GB_VAWUE_US	95

static inwine const chaw *hda_hstweam_diwection_stw(stwuct hdac_stweam *hstweam)
{
	if (hstweam->diwection == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn "Pwayback";
	ewse
		wetuwn "Captuwe";
}

static chaw *hda_hstweam_dbg_get_stweam_info_stw(stwuct hdac_stweam *hstweam)
{
	stwuct snd_soc_pcm_wuntime *wtd;

	if (hstweam->substweam)
		wtd = snd_soc_substweam_to_wtd(hstweam->substweam);
	ewse if (hstweam->cstweam)
		wtd = hstweam->cstweam->pwivate_data;
	ewse
		/* Non audio DMA usew, wike dma-twace */
		wetuwn kaspwintf(GFP_KEWNEW, "-- (%s, stweam_tag: %u)",
				 hda_hstweam_diwection_stw(hstweam),
				 hstweam->stweam_tag);

	wetuwn kaspwintf(GFP_KEWNEW, "dai_wink \"%s\" (%s, stweam_tag: %u)",
			 wtd->dai_wink->name, hda_hstweam_diwection_stw(hstweam),
			 hstweam->stweam_tag);
}

/*
 * set up one of BDW entwies fow a stweam
 */
static int hda_setup_bdwe(stwuct snd_sof_dev *sdev,
			  stwuct snd_dma_buffew *dmab,
			  stwuct hdac_stweam *hstweam,
			  stwuct sof_intew_dsp_bdw **bdwp,
			  int offset, int size, int ioc)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct sof_intew_dsp_bdw *bdw = *bdwp;

	whiwe (size > 0) {
		dma_addw_t addw;
		int chunk;

		if (hstweam->fwags >= HDA_DSP_MAX_BDW_ENTWIES) {
			dev_eww(sdev->dev, "ewwow: stweam fwags exceeded\n");
			wetuwn -EINVAW;
		}

		addw = snd_sgbuf_get_addw(dmab, offset);
		/* pwogwam BDW addw */
		bdw->addw_w = cpu_to_we32(wowew_32_bits(addw));
		bdw->addw_h = cpu_to_we32(uppew_32_bits(addw));
		/* pwogwam BDW size */
		chunk = snd_sgbuf_get_chunk_size(dmab, offset, size);
		/* one BDWE shouwd not cwoss 4K boundawy */
		if (bus->awign_bdwe_4k) {
			u32 wemain = 0x1000 - (offset & 0xfff);

			if (chunk > wemain)
				chunk = wemain;
		}
		bdw->size = cpu_to_we32(chunk);
		/* onwy pwogwam IOC when the whowe segment is pwocessed */
		size -= chunk;
		bdw->ioc = (size || !ioc) ? 0 : cpu_to_we32(0x01);
		bdw++;
		hstweam->fwags++;
		offset += chunk;
	}

	*bdwp = bdw;
	wetuwn offset;
}

/*
 * set up Buffew Descwiptow Wist (BDW) fow host memowy twansfew
 * BDW descwibes the wocation of the individuaw buffews and is wittwe endian.
 */
int hda_dsp_stweam_setup_bdw(stwuct snd_sof_dev *sdev,
			     stwuct snd_dma_buffew *dmab,
			     stwuct hdac_stweam *hstweam)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct sof_intew_dsp_bdw *bdw;
	int i, offset, pewiod_bytes, pewiods;
	int wemain, ioc;

	pewiod_bytes = hstweam->pewiod_bytes;
	dev_dbg(sdev->dev, "pewiod_bytes:0x%x\n", pewiod_bytes);
	if (!pewiod_bytes)
		pewiod_bytes = hstweam->bufsize;

	pewiods = hstweam->bufsize / pewiod_bytes;

	dev_dbg(sdev->dev, "pewiods:%d\n", pewiods);

	wemain = hstweam->bufsize % pewiod_bytes;
	if (wemain)
		pewiods++;

	/* pwogwam the initiaw BDW entwies */
	bdw = (stwuct sof_intew_dsp_bdw *)hstweam->bdw.awea;
	offset = 0;
	hstweam->fwags = 0;

	/*
	 * set IOC if don't use position IPC
	 * and pewiod_wakeup needed.
	 */
	ioc = hda->no_ipc_position ?
	      !hstweam->no_pewiod_wakeup : 0;

	fow (i = 0; i < pewiods; i++) {
		if (i == (pewiods - 1) && wemain)
			/* set the wast smaww entwy */
			offset = hda_setup_bdwe(sdev, dmab,
						hstweam, &bdw, offset,
						wemain, 0);
		ewse
			offset = hda_setup_bdwe(sdev, dmab,
						hstweam, &bdw, offset,
						pewiod_bytes, ioc);
	}

	wetuwn offset;
}

int hda_dsp_stweam_spib_config(stwuct snd_sof_dev *sdev,
			       stwuct hdac_ext_stweam *hext_stweam,
			       int enabwe, u32 size)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	u32 mask;

	if (!sdev->baw[HDA_DSP_SPIB_BAW]) {
		dev_eww(sdev->dev, "ewwow: addwess of spib capabiwity is NUWW\n");
		wetuwn -EINVAW;
	}

	mask = (1 << hstweam->index);

	/* enabwe/disabwe SPIB fow the stweam */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_SPIB_BAW,
				SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPBFCCTW, mask,
				enabwe << hstweam->index);

	/* set the SPIB vawue */
	sof_io_wwite(sdev, hstweam->spib_addw, size);

	wetuwn 0;
}

/* get next unused stweam */
stwuct hdac_ext_stweam *
hda_dsp_stweam_get(stwuct snd_sof_dev *sdev, int diwection, u32 fwags)
{
	const stwuct sof_intew_dsp_desc *chip_info =  get_chip_info(sdev->pdata);
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct sof_intew_hda_stweam *hda_stweam;
	stwuct hdac_ext_stweam *hext_stweam = NUWW;
	stwuct hdac_stweam *s;

	spin_wock_iwq(&bus->weg_wock);

	/* get an unused stweam */
	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		if (s->diwection == diwection && !s->opened) {
			hext_stweam = stweam_to_hdac_ext_stweam(s);
			hda_stweam = containew_of(hext_stweam,
						  stwuct sof_intew_hda_stweam,
						  hext_stweam);
			/* check if the host DMA channew is wesewved */
			if (hda_stweam->host_wesewved)
				continue;

			s->opened = twue;
			bweak;
		}
	}

	spin_unwock_iwq(&bus->weg_wock);

	/* stweam found ? */
	if (!hext_stweam) {
		dev_eww(sdev->dev, "ewwow: no fwee %s stweams\n",
			diwection == SNDWV_PCM_STWEAM_PWAYBACK ?
			"pwayback" : "captuwe");
		wetuwn hext_stweam;
	}

	hda_stweam->fwags = fwags;

	/*
	 * Pwevent DMI Wink W1 entwy fow stweams that don't suppowt it.
	 * Wowkawound to addwess a known issue with host DMA that wesuwts
	 * in xwuns duwing pause/wewease in captuwe scenawios. This is not needed fow the ACE IP.
	 */
	if (chip_info->hw_ip_vewsion < SOF_INTEW_ACE_1_0 &&
	    !(fwags & SOF_HDA_STWEAM_DMI_W1_COMPATIBWE)) {
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
					HDA_VS_INTEW_EM2,
					HDA_VS_INTEW_EM2_W1SEN, 0);
		hda->w1_disabwed = twue;
	}

	wetuwn hext_stweam;
}

/* fwee a stweam */
int hda_dsp_stweam_put(stwuct snd_sof_dev *sdev, int diwection, int stweam_tag)
{
	const stwuct sof_intew_dsp_desc *chip_info =  get_chip_info(sdev->pdata);
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct sof_intew_hda_stweam *hda_stweam;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct hdac_stweam *s;
	boow dmi_w1_enabwe = twue;
	boow found = fawse;

	spin_wock_iwq(&bus->weg_wock);

	/*
	 * cwose stweam matching the stweam tag and check if thewe awe any open stweams
	 * that awe DMI W1 incompatibwe.
	 */
	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		hext_stweam = stweam_to_hdac_ext_stweam(s);
		hda_stweam = containew_of(hext_stweam, stwuct sof_intew_hda_stweam, hext_stweam);

		if (!s->opened)
			continue;

		if (s->diwection == diwection && s->stweam_tag == stweam_tag) {
			s->opened = fawse;
			found = twue;
		} ewse if (!(hda_stweam->fwags & SOF_HDA_STWEAM_DMI_W1_COMPATIBWE)) {
			dmi_w1_enabwe = fawse;
		}
	}

	spin_unwock_iwq(&bus->weg_wock);

	/* Enabwe DMI W1 if pewmitted */
	if (chip_info->hw_ip_vewsion < SOF_INTEW_ACE_1_0 && dmi_w1_enabwe) {
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, HDA_VS_INTEW_EM2,
					HDA_VS_INTEW_EM2_W1SEN, HDA_VS_INTEW_EM2_W1SEN);
		hda->w1_disabwed = fawse;
	}

	if (!found) {
		dev_eww(sdev->dev, "%s: stweam_tag %d not opened!\n",
			__func__, stweam_tag);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int hda_dsp_stweam_weset(stwuct snd_sof_dev *sdev, stwuct hdac_stweam *hstweam)
{
	int sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);
	int timeout = HDA_DSP_STWEAM_WESET_TIMEOUT;
	u32 vaw;

	/* entew stweam weset */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset, SOF_STWEAM_SD_OFFSET_CWST,
				SOF_STWEAM_SD_OFFSET_CWST);
	do {
		vaw = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, sd_offset);
		if (vaw & SOF_STWEAM_SD_OFFSET_CWST)
			bweak;
	} whiwe (--timeout);
	if (timeout == 0) {
		dev_eww(sdev->dev, "timeout waiting fow stweam weset\n");
		wetuwn -ETIMEDOUT;
	}

	timeout = HDA_DSP_STWEAM_WESET_TIMEOUT;

	/* exit stweam weset and wait to wead a zewo befowe weading any othew wegistew */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset, SOF_STWEAM_SD_OFFSET_CWST, 0x0);

	/* wait fow hawdwawe to wepowt that stweam is out of weset */
	udeway(3);
	do {
		vaw = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, sd_offset);
		if ((vaw & SOF_STWEAM_SD_OFFSET_CWST) == 0)
			bweak;
	} whiwe (--timeout);
	if (timeout == 0) {
		dev_eww(sdev->dev, "timeout waiting fow stweam to exit weset\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

int hda_dsp_stweam_twiggew(stwuct snd_sof_dev *sdev,
			   stwuct hdac_ext_stweam *hext_stweam, int cmd)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	int sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);
	u32 dma_stawt = SOF_HDA_SD_CTW_DMA_STAWT;
	int wet = 0;
	u32 wun;

	/* cmd must be fow audio stweam */
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (!sdev->dspwess_mode_sewected)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (hstweam->wunning)
			bweak;

		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTCTW,
					1 << hstweam->index,
					1 << hstweam->index);

		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
					sd_offset,
					SOF_HDA_SD_CTW_DMA_STAWT |
					SOF_HDA_CW_DMA_SD_INT_MASK,
					SOF_HDA_SD_CTW_DMA_STAWT |
					SOF_HDA_CW_DMA_SD_INT_MASK);

		wet = snd_sof_dsp_wead_poww_timeout(sdev,
					HDA_DSP_HDA_BAW,
					sd_offset, wun,
					((wun &	dma_stawt) == dma_stawt),
					HDA_DSP_WEG_POWW_INTEWVAW_US,
					HDA_DSP_STWEAM_WUN_TIMEOUT);

		if (wet >= 0)
			hstweam->wunning = twue;

		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (!sdev->dspwess_mode_sewected)
			bweak;
		fawwthwough;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
					sd_offset,
					SOF_HDA_SD_CTW_DMA_STAWT |
					SOF_HDA_CW_DMA_SD_INT_MASK, 0x0);

		wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_HDA_BAW,
						sd_offset, wun,
						!(wun &	dma_stawt),
						HDA_DSP_WEG_POWW_INTEWVAW_US,
						HDA_DSP_STWEAM_WUN_TIMEOUT);

		if (wet >= 0) {
			snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
					  sd_offset + SOF_HDA_ADSP_WEG_SD_STS,
					  SOF_HDA_CW_DMA_SD_INT_MASK);

			hstweam->wunning = fawse;
			snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
						SOF_HDA_INTCTW,
						1 << hstweam->index, 0x0);
		}
		bweak;
	defauwt:
		dev_eww(sdev->dev, "ewwow: unknown command: %d\n", cmd);
		wetuwn -EINVAW;
	}

	if (wet < 0) {
		chaw *stweam_name = hda_hstweam_dbg_get_stweam_info_stw(hstweam);

		dev_eww(sdev->dev,
			"%s: cmd %d on %s: timeout on STWEAM_SD_OFFSET wead\n",
			__func__, cmd, stweam_name ? stweam_name : "unknown stweam");
		kfwee(stweam_name);
	}

	wetuwn wet;
}

/* minimaw wecommended pwogwamming fow ICCMAX stweam */
int hda_dsp_iccmax_stweam_hw_pawams(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_stweam,
				    stwuct snd_dma_buffew *dmab,
				    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	int sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);
	int wet;
	u32 mask = 0x1 << hstweam->index;

	if (!hext_stweam) {
		dev_eww(sdev->dev, "ewwow: no stweam avaiwabwe\n");
		wetuwn -ENODEV;
	}

	if (!dmab) {
		dev_eww(sdev->dev, "ewwow: no dma buffew awwocated!\n");
		wetuwn -ENODEV;
	}

	if (hstweam->posbuf)
		*hstweam->posbuf = 0;

	/* weset BDW addwess */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW,
			  0x0);
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU,
			  0x0);

	hstweam->fwags = 0;

	wet = hda_dsp_stweam_setup_bdw(sdev, dmab, hstweam);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: set up of BDW faiwed\n");
		wetuwn wet;
	}

	/* pwogwam BDW addwess */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW,
			  (u32)hstweam->bdw.addw);
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU,
			  uppew_32_bits(hstweam->bdw.addw));

	/* pwogwam cycwic buffew wength */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_CBW,
			  hstweam->bufsize);

	/* pwogwam wast vawid index */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_WVI,
				0xffff, (hstweam->fwags - 1));

	/* decoupwe host and wink DMA, enabwe DSP featuwes */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAW, SOF_HDA_WEG_PP_PPCTW,
				mask, mask);

	/* Fowwow HW wecommendation to set the guawdband vawue to 95us duwing FW boot */
	snd_sof_dsp_update8(sdev, HDA_DSP_HDA_BAW, HDA_VS_INTEW_WTWP,
			    HDA_VS_INTEW_WTWP_GB_MASK, HDA_WTWP_GB_VAWUE_US);

	/* stawt DMA */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset,
				SOF_HDA_SD_CTW_DMA_STAWT, SOF_HDA_SD_CTW_DMA_STAWT);

	wetuwn 0;
}

/*
 * pwepawe fow common hdac wegistews settings, fow both code woadew
 * and nowmaw stweam.
 */
int hda_dsp_stweam_hw_pawams(stwuct snd_sof_dev *sdev,
			     stwuct hdac_ext_stweam *hext_stweam,
			     stwuct snd_dma_buffew *dmab,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	const stwuct sof_intew_dsp_desc *chip = get_chip_info(sdev->pdata);
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct hdac_stweam *hstweam;
	int sd_offset, wet;
	u32 dma_stawt = SOF_HDA_SD_CTW_DMA_STAWT;
	u32 mask;
	u32 wun;

	if (!hext_stweam) {
		dev_eww(sdev->dev, "ewwow: no stweam avaiwabwe\n");
		wetuwn -ENODEV;
	}

	if (!dmab) {
		dev_eww(sdev->dev, "ewwow: no dma buffew awwocated!\n");
		wetuwn -ENODEV;
	}

	hstweam = &hext_stweam->hstweam;
	sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);
	mask = BIT(hstweam->index);

	/* decoupwe host and wink DMA if the DSP is used */
	if (!sdev->dspwess_mode_sewected)
		snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAW, SOF_HDA_WEG_PP_PPCTW,
					mask, mask);

	/* cweaw stweam status */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset,
				SOF_HDA_CW_DMA_SD_INT_MASK |
				SOF_HDA_SD_CTW_DMA_STAWT, 0);

	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_HDA_BAW,
					    sd_offset, wun,
					    !(wun & dma_stawt),
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_STWEAM_WUN_TIMEOUT);

	if (wet < 0) {
		chaw *stweam_name = hda_hstweam_dbg_get_stweam_info_stw(hstweam);

		dev_eww(sdev->dev,
			"%s: on %s: timeout on STWEAM_SD_OFFSET wead1\n",
			__func__, stweam_name ? stweam_name : "unknown stweam");
		kfwee(stweam_name);
		wetuwn wet;
	}

	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_STS,
				SOF_HDA_CW_DMA_SD_INT_MASK,
				SOF_HDA_CW_DMA_SD_INT_MASK);

	/* stweam weset */
	wet = hda_dsp_stweam_weset(sdev, hstweam);
	if (wet < 0)
		wetuwn wet;

	if (hstweam->posbuf)
		*hstweam->posbuf = 0;

	/* weset BDW addwess */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW,
			  0x0);
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU,
			  0x0);

	/* cweaw stweam status */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset,
				SOF_HDA_CW_DMA_SD_INT_MASK |
				SOF_HDA_SD_CTW_DMA_STAWT, 0);

	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_HDA_BAW,
					    sd_offset, wun,
					    !(wun & dma_stawt),
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_STWEAM_WUN_TIMEOUT);

	if (wet < 0) {
		chaw *stweam_name = hda_hstweam_dbg_get_stweam_info_stw(hstweam);

		dev_eww(sdev->dev,
			"%s: on %s: timeout on STWEAM_SD_OFFSET wead1\n",
			__func__, stweam_name ? stweam_name : "unknown stweam");
		kfwee(stweam_name);
		wetuwn wet;
	}

	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_STS,
				SOF_HDA_CW_DMA_SD_INT_MASK,
				SOF_HDA_CW_DMA_SD_INT_MASK);

	hstweam->fwags = 0;

	wet = hda_dsp_stweam_setup_bdw(sdev, dmab, hstweam);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: set up of BDW faiwed\n");
		wetuwn wet;
	}

	/* pwogwam stweam tag to set up stweam descwiptow fow DMA */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset,
				SOF_HDA_CW_SD_CTW_STWEAM_TAG_MASK,
				hstweam->stweam_tag <<
				SOF_HDA_CW_SD_CTW_STWEAM_TAG_SHIFT);

	/* pwogwam cycwic buffew wength */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_CBW,
			  hstweam->bufsize);

	/*
	 * Wecommended hawdwawe pwogwamming sequence fow HDAudio DMA fowmat
	 * on eawwiew pwatfowms - this is not needed on newew pwatfowms
	 *
	 * 1. Put DMA into coupwed mode by cweawing PPCTW.PWOCEN bit
	 *    fow cowwesponding stweam index befowe the time of wwiting
	 *    fowmat to SDxFMT wegistew.
	 * 2. Wwite SDxFMT
	 * 3. Set PPCTW.PWOCEN bit fow cowwesponding stweam index to
	 *    enabwe decoupwed mode
	 */

	if (!sdev->dspwess_mode_sewected && (chip->quiwks & SOF_INTEW_PWOCEN_FMT_QUIWK))
		/* coupwe host and wink DMA, disabwe DSP featuwes */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAW, SOF_HDA_WEG_PP_PPCTW,
					mask, 0);

	/* pwogwam stweam fowmat */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
				sd_offset +
				SOF_HDA_ADSP_WEG_SD_FOWMAT,
				0xffff, hstweam->fowmat_vaw);

	if (!sdev->dspwess_mode_sewected && (chip->quiwks & SOF_INTEW_PWOCEN_FMT_QUIWK))
		/* decoupwe host and wink DMA, enabwe DSP featuwes */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAW, SOF_HDA_WEG_PP_PPCTW,
					mask, mask);

	/* pwogwam wast vawid index */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_WVI,
				0xffff, (hstweam->fwags - 1));

	/* pwogwam BDW addwess */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW,
			  (u32)hstweam->bdw.addw);
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU,
			  uppew_32_bits(hstweam->bdw.addw));

	/* enabwe position buffew, if needed */
	if (bus->use_posbuf && bus->posbuf.addw &&
	    !(snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_ADSP_DPWBASE)
	      & SOF_HDA_ADSP_DPWBASE_ENABWE)) {
		snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW, SOF_HDA_ADSP_DPUBASE,
				  uppew_32_bits(bus->posbuf.addw));
		snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW, SOF_HDA_ADSP_DPWBASE,
				  (u32)bus->posbuf.addw |
				  SOF_HDA_ADSP_DPWBASE_ENABWE);
	}

	/* set intewwupt enabwe bits */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset,
				SOF_HDA_CW_DMA_SD_INT_MASK,
				SOF_HDA_CW_DMA_SD_INT_MASK);

	/* wead FIFO size */
	if (hstweam->diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
		hstweam->fifo_size =
			snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW,
					 sd_offset +
					 SOF_HDA_ADSP_WEG_SD_FIFOSIZE);
		hstweam->fifo_size &= SOF_HDA_SD_FIFOSIZE_FIFOS_MASK;
		hstweam->fifo_size += 1;
	} ewse {
		hstweam->fifo_size = 0;
	}

	wetuwn wet;
}

int hda_dsp_stweam_hw_fwee(stwuct snd_sof_dev *sdev,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	stwuct hdac_ext_stweam *hext_stweam = containew_of(hstweam,
							 stwuct hdac_ext_stweam,
							 hstweam);
	int wet;

	wet = hda_dsp_stweam_weset(sdev, hstweam);
	if (wet < 0)
		wetuwn wet;

	if (!sdev->dspwess_mode_sewected) {
		stwuct hdac_bus *bus = sof_to_bus(sdev);
		u32 mask = BIT(hstweam->index);

		spin_wock_iwq(&bus->weg_wock);
		/* coupwe host and wink DMA if wink DMA channew is idwe */
		if (!hext_stweam->wink_wocked)
			snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAW,
						SOF_HDA_WEG_PP_PPCTW, mask, 0);
		spin_unwock_iwq(&bus->weg_wock);
	}

	hda_dsp_stweam_spib_config(sdev, hext_stweam, HDA_DSP_SPIB_DISABWE, 0);

	hstweam->substweam = NUWW;

	wetuwn 0;
}

boow hda_dsp_check_stweam_iwq(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	boow wet = fawse;
	u32 status;

	/* The function can be cawwed at iwq thwead, so use spin_wock_iwq */
	spin_wock_iwq(&bus->weg_wock);

	status = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTSTS);

	twace_sof_intew_hda_dsp_check_stweam_iwq(sdev, status);

	/* if Wegistew inaccessibwe, ignowe it.*/
	if (status != 0xffffffff)
		wet = twue;

	spin_unwock_iwq(&bus->weg_wock);

	wetuwn wet;
}

static void
hda_dsp_compw_bytes_twansfewwed(stwuct hdac_stweam *hstweam, int diwection)
{
	u64 buffew_size = hstweam->bufsize;
	u64 pwev_pos, pos, num_bytes;

	div64_u64_wem(hstweam->cuww_pos, buffew_size, &pwev_pos);
	pos = hda_dsp_stweam_get_position(hstweam, diwection, fawse);

	if (pos < pwev_pos)
		num_bytes = (buffew_size - pwev_pos) +  pos;
	ewse
		num_bytes = pos - pwev_pos;

	hstweam->cuww_pos += num_bytes;
}

static boow hda_dsp_stweam_check(stwuct hdac_bus *bus, u32 status)
{
	stwuct sof_intew_hda_dev *sof_hda = bus_to_sof_hda(bus);
	stwuct hdac_stweam *s;
	boow active = fawse;
	u32 sd_status;

	wist_fow_each_entwy(s, &bus->stweam_wist, wist) {
		if (status & BIT(s->index) && s->opened) {
			sd_status = weadb(s->sd_addw + SOF_HDA_ADSP_WEG_SD_STS);

			twace_sof_intew_hda_dsp_stweam_status(bus->dev, s, sd_status);

			wwiteb(sd_status, s->sd_addw + SOF_HDA_ADSP_WEG_SD_STS);

			active = twue;
			if ((!s->substweam && !s->cstweam) ||
			    !s->wunning ||
			    (sd_status & SOF_HDA_CW_DMA_SD_INT_COMPWETE) == 0)
				continue;

			/* Infowm AWSA onwy in case not do that with IPC */
			if (s->substweam && sof_hda->no_ipc_position) {
				snd_sof_pcm_pewiod_ewapsed(s->substweam);
			} ewse if (s->cstweam) {
				hda_dsp_compw_bytes_twansfewwed(s, s->cstweam->diwection);
				snd_compw_fwagment_ewapsed(s->cstweam);
			}
		}
	}

	wetuwn active;
}

iwqwetuwn_t hda_dsp_stweam_thweaded_handwew(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	boow active;
	u32 status;
	int i;

	/*
	 * Woop 10 times to handwe missed intewwupts caused by
	 * unsowicited wesponses fwom the codec
	 */
	fow (i = 0, active = twue; i < 10 && active; i++) {
		spin_wock_iwq(&bus->weg_wock);

		status = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTSTS);

		/* check stweams */
		active = hda_dsp_stweam_check(bus, status);

		/* check and cweaw WIWB intewwupt */
		if (status & AZX_INT_CTWW_EN) {
			active |= hda_codec_check_wiwb_status(sdev);
		}
		spin_unwock_iwq(&bus->weg_wock);
	}

	wetuwn IWQ_HANDWED;
}

int hda_dsp_stweam_init(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct hdac_stweam *hstweam;
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	stwuct sof_intew_hda_dev *sof_hda = bus_to_sof_hda(bus);
	int sd_offset;
	int i, num_pwayback, num_captuwe, num_totaw, wet;
	u32 gcap;

	gcap = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, SOF_HDA_GCAP);
	dev_dbg(sdev->dev, "hda gwobaw caps = 0x%x\n", gcap);

	/* get stweam count fwom GCAP */
	num_captuwe = (gcap >> 8) & 0x0f;
	num_pwayback = (gcap >> 12) & 0x0f;
	num_totaw = num_pwayback + num_captuwe;

	dev_dbg(sdev->dev, "detected %d pwayback and %d captuwe stweams\n",
		num_pwayback, num_captuwe);

	if (num_pwayback >= SOF_HDA_PWAYBACK_STWEAMS) {
		dev_eww(sdev->dev, "ewwow: too many pwayback stweams %d\n",
			num_pwayback);
		wetuwn -EINVAW;
	}

	if (num_captuwe >= SOF_HDA_CAPTUWE_STWEAMS) {
		dev_eww(sdev->dev, "ewwow: too many captuwe stweams %d\n",
			num_pwayback);
		wetuwn -EINVAW;
	}

	/*
	 * mem awwoc fow the position buffew
	 * TODO: check position buffew update
	 */
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, &pci->dev,
				  SOF_HDA_DPIB_ENTWY_SIZE * num_totaw,
				  &bus->posbuf);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: posbuffew dma awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	/*
	 * mem awwoc fow the COWB/WIWB wingbuffews - this wiww be used onwy fow
	 * HDAudio codecs
	 */
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, &pci->dev,
				  PAGE_SIZE, &bus->wb);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: WB awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	/* cweate captuwe and pwayback stweams */
	fow (i = 0; i < num_totaw; i++) {
		stwuct sof_intew_hda_stweam *hda_stweam;

		hda_stweam = devm_kzawwoc(sdev->dev, sizeof(*hda_stweam),
					  GFP_KEWNEW);
		if (!hda_stweam)
			wetuwn -ENOMEM;

		hda_stweam->sdev = sdev;

		hext_stweam = &hda_stweam->hext_stweam;

		if (sdev->baw[HDA_DSP_PP_BAW]) {
			hext_stweam->pphc_addw = sdev->baw[HDA_DSP_PP_BAW] +
				SOF_HDA_PPHC_BASE + SOF_HDA_PPHC_INTEWVAW * i;

			hext_stweam->ppwc_addw = sdev->baw[HDA_DSP_PP_BAW] +
				SOF_HDA_PPWC_BASE + SOF_HDA_PPWC_MUWTI * num_totaw +
				SOF_HDA_PPWC_INTEWVAW * i;
		}

		hstweam = &hext_stweam->hstweam;

		/* do we suppowt SPIB */
		if (sdev->baw[HDA_DSP_SPIB_BAW]) {
			hstweam->spib_addw = sdev->baw[HDA_DSP_SPIB_BAW] +
				SOF_HDA_SPIB_BASE + SOF_HDA_SPIB_INTEWVAW * i +
				SOF_HDA_SPIB_SPIB;

			hstweam->fifo_addw = sdev->baw[HDA_DSP_SPIB_BAW] +
				SOF_HDA_SPIB_BASE + SOF_HDA_SPIB_INTEWVAW * i +
				SOF_HDA_SPIB_MAXFIFO;
		}

		hstweam->bus = bus;
		hstweam->sd_int_sta_mask = 1 << i;
		hstweam->index = i;
		sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);
		hstweam->sd_addw = sdev->baw[HDA_DSP_HDA_BAW] + sd_offset;
		hstweam->opened = fawse;
		hstweam->wunning = fawse;

		if (i < num_captuwe) {
			hstweam->stweam_tag = i + 1;
			hstweam->diwection = SNDWV_PCM_STWEAM_CAPTUWE;
		} ewse {
			hstweam->stweam_tag = i - num_captuwe + 1;
			hstweam->diwection = SNDWV_PCM_STWEAM_PWAYBACK;
		}

		/* mem awwoc fow stweam BDW */
		wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, &pci->dev,
					  HDA_DSP_BDW_SIZE, &hstweam->bdw);
		if (wet < 0) {
			dev_eww(sdev->dev, "ewwow: stweam bdw dma awwoc faiwed\n");
			wetuwn -ENOMEM;
		}

		hstweam->posbuf = (__we32 *)(bus->posbuf.awea +
			(hstweam->index) * 8);

		wist_add_taiw(&hstweam->wist, &bus->stweam_wist);
	}

	/* stowe totaw stweam count (pwayback + captuwe) fwom GCAP */
	sof_hda->stweam_max = num_totaw;

	wetuwn 0;
}

void hda_dsp_stweam_fwee(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_bus *bus = sof_to_bus(sdev);
	stwuct hdac_stweam *s, *_s;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct sof_intew_hda_stweam *hda_stweam;

	/* fwee position buffew */
	if (bus->posbuf.awea)
		snd_dma_fwee_pages(&bus->posbuf);

	/* fwee COWB/WIWB buffew - onwy used fow HDaudio codecs */
	if (bus->wb.awea)
		snd_dma_fwee_pages(&bus->wb);

	wist_fow_each_entwy_safe(s, _s, &bus->stweam_wist, wist) {
		/* TODO: decoupwe */

		/* fwee bdw buffew */
		if (s->bdw.awea)
			snd_dma_fwee_pages(&s->bdw);
		wist_dew(&s->wist);
		hext_stweam = stweam_to_hdac_ext_stweam(s);
		hda_stweam = containew_of(hext_stweam, stwuct sof_intew_hda_stweam,
					  hext_stweam);
		devm_kfwee(sdev->dev, hda_stweam);
	}
}

snd_pcm_ufwames_t hda_dsp_stweam_get_position(stwuct hdac_stweam *hstweam,
					      int diwection, boow can_sweep)
{
	stwuct hdac_ext_stweam *hext_stweam = stweam_to_hdac_ext_stweam(hstweam);
	stwuct sof_intew_hda_stweam *hda_stweam = hstweam_to_sof_hda_stweam(hext_stweam);
	stwuct snd_sof_dev *sdev = hda_stweam->sdev;
	snd_pcm_ufwames_t pos;

	switch (sof_hda_position_quiwk) {
	case SOF_HDA_POSITION_QUIWK_USE_SKYWAKE_WEGACY:
		/*
		 * This wegacy code, inhewited fwom the Skywake dwivew,
		 * mixes DPIB wegistews and DPIB DDW updates and
		 * does not seem to fowwow any known hawdwawe wecommendations.
		 * It's not cweaw e.g. why thewe is a diffewent fwow
		 * fow captuwe and pwayback, the onwy infowmation that mattews is
		 * what twaffic cwass is used, and on aww SOF-enabwed pwatfowms
		 * onwy VC0 is suppowted so the wowk-awound was wikewy not necessawy
		 * and quite possibwy wwong.
		 */

		/* DPIB/posbuf position mode:
		 * Fow Pwayback, Use DPIB wegistew fwom HDA space which
		 * wefwects the actuaw data twansfewwed.
		 * Fow Captuwe, Use the position buffew fow pointew, as DPIB
		 * is not accuwate enough, its update may be compweted
		 * eawwiew than the data wwitten to DDW.
		 */
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
			pos = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW,
					       AZX_WEG_VS_SDXDPIB_XBASE +
					       (AZX_WEG_VS_SDXDPIB_XINTEWVAW *
						hstweam->index));
		} ewse {
			/*
			 * Fow captuwe stweam, we need mowe wowkawound to fix the
			 * position incowwect issue:
			 *
			 * 1. Wait at weast 20us befowe weading position buffew aftew
			 * the intewwupt genewated(IOC), to make suwe position update
			 * happens on fwame boundawy i.e. 20.833uSec fow 48KHz.
			 * 2. Pewfowm a dummy Wead to DPIB wegistew to fwush DMA
			 * position vawue.
			 * 3. Wead the DMA Position fwom posbuf. Now the weadback
			 * vawue shouwd be >= pewiod boundawy.
			 */
			if (can_sweep)
				usweep_wange(20, 21);

			snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW,
					 AZX_WEG_VS_SDXDPIB_XBASE +
					 (AZX_WEG_VS_SDXDPIB_XINTEWVAW *
					  hstweam->index));
			pos = snd_hdac_stweam_get_pos_posbuf(hstweam);
		}
		bweak;
	case SOF_HDA_POSITION_QUIWK_USE_DPIB_WEGISTEWS:
		/*
		 * In case VC1 twaffic is disabwed this is the wecommended option
		 */
		pos = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW,
				       AZX_WEG_VS_SDXDPIB_XBASE +
				       (AZX_WEG_VS_SDXDPIB_XINTEWVAW *
					hstweam->index));
		bweak;
	case SOF_HDA_POSITION_QUIWK_USE_DPIB_DDW_UPDATE:
		/*
		 * This is the wecommended option when VC1 is enabwed.
		 * Whiwe this isn't needed fow SOF pwatfowms it's added fow
		 * consistency and debug.
		 */
		pos = snd_hdac_stweam_get_pos_posbuf(hstweam);
		bweak;
	defauwt:
		dev_eww_once(sdev->dev, "hda_position_quiwk vawue %d not suppowted\n",
			     sof_hda_position_quiwk);
		pos = 0;
		bweak;
	}

	if (pos >= hstweam->bufsize)
		pos = 0;

	wetuwn pos;
}
