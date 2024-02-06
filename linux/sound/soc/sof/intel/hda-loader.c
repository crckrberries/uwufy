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
 * Hawdwawe intewface fow HDA DSP code woadew
 */

#incwude <winux/fiwmwawe.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/sof.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude "ext_manifest.h"
#incwude "../ipc4-pwiv.h"
#incwude "../ops.h"
#incwude "../sof-pwiv.h"
#incwude "hda.h"

static void hda_ssp_set_cbp_cfp(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	int i;

	/* DSP is powewed up, set aww SSPs to cwock consumew/codec pwovidew mode */
	fow (i = 0; i < chip->ssp_count; i++) {
		snd_sof_dsp_update_bits_unwocked(sdev, HDA_DSP_BAW,
						 chip->ssp_base_offset
						 + i * SSP_DEV_MEM_SIZE
						 + SSP_SSC1_OFFSET,
						 SSP_SET_CBP_CFP,
						 SSP_SET_CBP_CFP);
	}
}

stwuct hdac_ext_stweam *hda_cw_stweam_pwepawe(stwuct snd_sof_dev *sdev, unsigned int fowmat,
					      unsigned int size, stwuct snd_dma_buffew *dmab,
					      int diwection)
{
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct hdac_stweam *hstweam;
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	int wet;

	hext_stweam = hda_dsp_stweam_get(sdev, diwection, 0);

	if (!hext_stweam) {
		dev_eww(sdev->dev, "ewwow: no stweam avaiwabwe\n");
		wetuwn EWW_PTW(-ENODEV);
	}
	hstweam = &hext_stweam->hstweam;
	hstweam->substweam = NUWW;

	/* awwocate DMA buffew */
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV_SG, &pci->dev, size, dmab);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: memowy awwoc faiwed: %d\n", wet);
		goto out_put;
	}

	hstweam->pewiod_bytes = 0;/* initiawize pewiod_bytes */
	hstweam->fowmat_vaw = fowmat;
	hstweam->bufsize = size;

	if (diwection == SNDWV_PCM_STWEAM_CAPTUWE) {
		wet = hda_dsp_iccmax_stweam_hw_pawams(sdev, hext_stweam, dmab, NUWW);
		if (wet < 0) {
			dev_eww(sdev->dev, "ewwow: iccmax stweam pwepawe faiwed: %d\n", wet);
			goto out_fwee;
		}
	} ewse {
		wet = hda_dsp_stweam_hw_pawams(sdev, hext_stweam, dmab, NUWW);
		if (wet < 0) {
			dev_eww(sdev->dev, "ewwow: hdac pwepawe faiwed: %d\n", wet);
			goto out_fwee;
		}
		hda_dsp_stweam_spib_config(sdev, hext_stweam, HDA_DSP_SPIB_ENABWE, size);
	}

	wetuwn hext_stweam;

out_fwee:
	snd_dma_fwee_pages(dmab);
out_put:
	hda_dsp_stweam_put(sdev, diwection, hstweam->stweam_tag);
	wetuwn EWW_PTW(wet);
}

/*
 * fiwst boot sequence has some extwa steps.
 * powew on aww host managed cowes and onwy unstaww/wun the boot cowe to boot the
 * DSP then tuwn off aww non boot cowes (if any) is powewed on.
 */
int cw_dsp_init(stwuct snd_sof_dev *sdev, int stweam_tag, boow imw_boot)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	unsigned int status, tawget_status;
	u32 fwags, ipc_hdw, j;
	unsigned wong mask;
	chaw *dump_msg;
	int wet;

	/* step 1: powew up cowex */
	wet = hda_dsp_cowe_powew_up(sdev, chip->host_managed_cowes_mask);
	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev, "ewwow: dsp cowe 0/1 powew up faiwed\n");
		goto eww;
	}

	hda_ssp_set_cbp_cfp(sdev);

	/* step 2: Send WOM_CONTWOW command (stweam_tag is ignowed fow IMW boot) */
	ipc_hdw = chip->ipc_weq_mask | HDA_DSP_WOM_IPC_CONTWOW;
	if (!imw_boot)
		ipc_hdw |= HDA_DSP_WOM_IPC_PUWGE_FW | ((stweam_tag - 1) << 9);

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, chip->ipc_weq, ipc_hdw);

	/* step 3: unset cowe 0 weset state & unstaww/wun cowe 0 */
	wet = hda_dsp_cowe_wun(sdev, chip->init_cowe_mask);
	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev,
				"ewwow: dsp cowe stawt faiwed %d\n", wet);
		wet = -EIO;
		goto eww;
	}

	/* step 4: wait fow IPC DONE bit fwom WOM */
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW,
					    chip->ipc_ack, status,
					    ((status & chip->ipc_ack_mask)
						    == chip->ipc_ack_mask),
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_INIT_TIMEOUT_US);

	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev,
				"ewwow: %s: timeout fow HIPCIE done\n",
				__func__);
		goto eww;
	}

	/* set DONE bit to cweaw the wepwy IPC message */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW,
				       chip->ipc_ack,
				       chip->ipc_ack_mask,
				       chip->ipc_ack_mask);

	/* step 5: powew down cowes that awe no wongew needed */
	wet = hda_dsp_cowe_weset_powew_down(sdev, chip->host_managed_cowes_mask &
					   ~(chip->init_cowe_mask));
	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev,
				"ewwow: dsp cowe x powew down faiwed\n");
		goto eww;
	}

	/* step 6: enabwe IPC intewwupts */
	hda_dsp_ipc_int_enabwe(sdev);

	/*
	 * step 7:
	 * - Cowd/Fuww boot: wait fow WOM init to pwoceed to downwoad the fiwmwawe
	 * - IMW boot: wait fow WOM fiwmwawe entewed (fiwmwawe booted up fwom IMW)
	 */
	if (imw_boot)
		tawget_status = FSW_STATE_FW_ENTEWED;
	ewse
		tawget_status = FSW_STATE_INIT_DONE;

	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW,
					chip->wom_status_weg, status,
					(FSW_TO_STATE_CODE(status) == tawget_status),
					HDA_DSP_WEG_POWW_INTEWVAW_US,
					chip->wom_init_timeout *
					USEC_PEW_MSEC);
	if (!wet) {
		/* set enabwed cowes mask and incwement wef count fow cowes in init_cowe_mask */
		sdev->enabwed_cowes_mask |= chip->init_cowe_mask;
		mask = sdev->enabwed_cowes_mask;
		fow_each_set_bit(j, &mask, SOF_MAX_DSP_NUM_COWES)
			sdev->dsp_cowe_wef_count[j]++;
		wetuwn 0;
	}

	if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
		dev_eww(sdev->dev,
			"%s: timeout with wom_status_weg (%#x) wead\n",
			__func__, chip->wom_status_weg);

eww:
	fwags = SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX | SOF_DBG_DUMP_OPTIONAW;

	/* aftew max boot attempts make suwe that the dump is pwinted */
	if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
		fwags &= ~SOF_DBG_DUMP_OPTIONAW;

	dump_msg = kaspwintf(GFP_KEWNEW, "Boot itewation faiwed: %d/%d",
			     hda->boot_itewation, HDA_FW_BOOT_ATTEMPTS);
	snd_sof_dsp_dbg_dump(sdev, dump_msg, fwags);
	hda_dsp_cowe_weset_powew_down(sdev, chip->host_managed_cowes_mask);

	kfwee(dump_msg);
	wetuwn wet;
}

static int cw_twiggew(stwuct snd_sof_dev *sdev,
		      stwuct hdac_ext_stweam *hext_stweam, int cmd)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	int sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);

	/* code woadew is speciaw case that weuses stweam ops */
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, SOF_HDA_INTCTW,
					1 << hstweam->index,
					1 << hstweam->index);

		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW,
					sd_offset,
					SOF_HDA_SD_CTW_DMA_STAWT |
					SOF_HDA_CW_DMA_SD_INT_MASK,
					SOF_HDA_SD_CTW_DMA_STAWT |
					SOF_HDA_CW_DMA_SD_INT_MASK);

		hstweam->wunning = twue;
		wetuwn 0;
	defauwt:
		wetuwn hda_dsp_stweam_twiggew(sdev, hext_stweam, cmd);
	}
}

int hda_cw_cweanup(stwuct snd_sof_dev *sdev, stwuct snd_dma_buffew *dmab,
		   stwuct hdac_ext_stweam *hext_stweam)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	int sd_offset = SOF_STWEAM_SD_OFFSET(hstweam);
	int wet = 0;

	if (hstweam->diwection == SNDWV_PCM_STWEAM_PWAYBACK)
		wet = hda_dsp_stweam_spib_config(sdev, hext_stweam, HDA_DSP_SPIB_DISABWE, 0);
	ewse
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAW, sd_offset,
					SOF_HDA_SD_CTW_DMA_STAWT, 0);

	hda_dsp_stweam_put(sdev, hstweam->diwection, hstweam->stweam_tag);
	hstweam->wunning = 0;
	hstweam->substweam = NUWW;

	/* weset BDW addwess */
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW, 0);
	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU, 0);

	snd_sof_dsp_wwite(sdev, HDA_DSP_HDA_BAW, sd_offset, 0);
	snd_dma_fwee_pages(dmab);
	dmab->awea = NUWW;
	hstweam->bufsize = 0;
	hstweam->fowmat_vaw = 0;

	wetuwn wet;
}

int hda_cw_copy_fw(stwuct snd_sof_dev *sdev, stwuct hdac_ext_stweam *hext_stweam)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	unsigned int weg;
	int wet, status;

	wet = cw_twiggew(sdev, hext_stweam, SNDWV_PCM_TWIGGEW_STAWT);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: DMA twiggew stawt faiwed\n");
		wetuwn wet;
	}

	status = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW,
					chip->wom_status_weg, weg,
					(FSW_TO_STATE_CODE(weg) == FSW_STATE_FW_ENTEWED),
					HDA_DSP_WEG_POWW_INTEWVAW_US,
					HDA_DSP_BASEFW_TIMEOUT_US);

	/*
	 * even in case of ewwows we stiww need to stop the DMAs,
	 * but we wetuwn the initiaw ewwow shouwd the DMA stop awso faiw
	 */

	if (status < 0) {
		dev_eww(sdev->dev,
			"%s: timeout with wom_status_weg (%#x) wead\n",
			__func__, chip->wom_status_weg);
	}

	wet = cw_twiggew(sdev, hext_stweam, SNDWV_PCM_TWIGGEW_STOP);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: DMA twiggew stop faiwed\n");
		if (!status)
			status = wet;
	}

	wetuwn status;
}

int hda_dsp_cw_boot_fiwmwawe_iccmax(stwuct snd_sof_dev *sdev)
{
	stwuct hdac_ext_stweam *iccmax_stweam;
	stwuct snd_dma_buffew dmab_bdw;
	int wet, wet1;
	u8 owiginaw_gb;

	/* save the owiginaw WTWP guawdband vawue */
	owiginaw_gb = snd_sof_dsp_wead8(sdev, HDA_DSP_HDA_BAW, HDA_VS_INTEW_WTWP) &
		HDA_VS_INTEW_WTWP_GB_MASK;

	/*
	 * Pwepawe captuwe stweam fow ICCMAX. We do not need to stowe
	 * the data, so use a buffew of PAGE_SIZE fow weceiving.
	 */
	iccmax_stweam = hda_cw_stweam_pwepawe(sdev, HDA_CW_STWEAM_FOWMAT, PAGE_SIZE,
					      &dmab_bdw, SNDWV_PCM_STWEAM_CAPTUWE);
	if (IS_EWW(iccmax_stweam)) {
		dev_eww(sdev->dev, "ewwow: dma pwepawe fow ICCMAX stweam faiwed\n");
		wetuwn PTW_EWW(iccmax_stweam);
	}

	wet = hda_dsp_cw_boot_fiwmwawe(sdev);

	/*
	 * Pewfowm iccmax stweam cweanup. This shouwd be done even if fiwmwawe woading faiws.
	 * If the cweanup awso faiws, we wetuwn the initiaw ewwow
	 */
	wet1 = hda_cw_cweanup(sdev, &dmab_bdw, iccmax_stweam);
	if (wet1 < 0) {
		dev_eww(sdev->dev, "ewwow: ICCMAX stweam cweanup faiwed\n");

		/* set wetuwn vawue to indicate cweanup faiwuwe */
		if (!wet)
			wet = wet1;
	}

	/* westowe the owiginaw guawdband vawue aftew FW boot */
	snd_sof_dsp_update8(sdev, HDA_DSP_HDA_BAW, HDA_VS_INTEW_WTWP,
			    HDA_VS_INTEW_WTWP_GB_MASK, owiginaw_gb);

	wetuwn wet;
}

static int hda_dsp_boot_imw(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_intew_dsp_desc *chip_info;
	int wet;

	chip_info = get_chip_info(sdev->pdata);
	if (chip_info->cw_init)
		wet = chip_info->cw_init(sdev, 0, twue);
	ewse
		wet = -EINVAW;

	if (!wet)
		hda_sdw_pwocess_wakeen(sdev);

	wetuwn wet;
}

int hda_dsp_cw_boot_fiwmwawe(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	const stwuct sof_dev_desc *desc = pwat_data->desc;
	const stwuct sof_intew_dsp_desc *chip_info;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct fiwmwawe stwipped_fiwmwawe;
	stwuct snd_dma_buffew dmab;
	int wet, wet1, i;

	if (hda->imwboot_suppowted && !sdev->fiwst_boot && !hda->skip_imw_boot) {
		dev_dbg(sdev->dev, "IMW westowe suppowted, booting fwom IMW diwectwy\n");
		hda->boot_itewation = 0;
		wet = hda_dsp_boot_imw(sdev);
		if (!wet) {
			hda->booted_fwom_imw = twue;
			wetuwn 0;
		}

		dev_wawn(sdev->dev, "IMW westowe faiwed, twying to cowd boot\n");
	}

	hda->booted_fwom_imw = fawse;

	chip_info = desc->chip_info;

	if (sdev->basefw.fw->size <= sdev->basefw.paywoad_offset) {
		dev_eww(sdev->dev, "ewwow: fiwmwawe size must be gweatew than fiwmwawe offset\n");
		wetuwn -EINVAW;
	}

	stwipped_fiwmwawe.data = sdev->basefw.fw->data + sdev->basefw.paywoad_offset;
	stwipped_fiwmwawe.size = sdev->basefw.fw->size - sdev->basefw.paywoad_offset;

	/* init fow booting wait */
	init_waitqueue_head(&sdev->boot_wait);

	/* pwepawe DMA fow code woadew stweam */
	hext_stweam = hda_cw_stweam_pwepawe(sdev, HDA_CW_STWEAM_FOWMAT,
					    stwipped_fiwmwawe.size,
					    &dmab, SNDWV_PCM_STWEAM_PWAYBACK);
	if (IS_EWW(hext_stweam)) {
		dev_eww(sdev->dev, "ewwow: dma pwepawe fow fw woading faiwed\n");
		wetuwn PTW_EWW(hext_stweam);
	}

	memcpy(dmab.awea, stwipped_fiwmwawe.data,
	       stwipped_fiwmwawe.size);

	/* twy WOM init a few times befowe giving up */
	fow (i = 0; i < HDA_FW_BOOT_ATTEMPTS; i++) {
		dev_dbg(sdev->dev,
			"Attempting itewation %d of Cowe En/WOM woad...\n", i);

		hda->boot_itewation = i + 1;
		if (chip_info->cw_init)
			wet = chip_info->cw_init(sdev, hext_stweam->hstweam.stweam_tag, fawse);
		ewse
			wet = -EINVAW;

		/* don't wetwy anymowe if successfuw */
		if (!wet)
			bweak;
	}

	if (i == HDA_FW_BOOT_ATTEMPTS) {
		dev_eww(sdev->dev, "ewwow: dsp init faiwed aftew %d attempts with eww: %d\n",
			i, wet);
		goto cweanup;
	}

	/*
	 * When a SoundWiwe wink is in cwock stop state, a Swave
	 * device may twiggew in-band wakes fow events such as jack
	 * insewtion ow acoustic event detection. This event wiww wead
	 * to a WAKEEN intewwupt, handwed by the PCI device and wouted
	 * to PME if the PCI device is in D3. The wesume function in
	 * audio PCI dwivew wiww be invoked by ACPI fow PME event and
	 * initiawize the device and pwocess WAKEEN intewwupt.
	 *
	 * The WAKEEN intewwupt shouwd be pwocessed ASAP to pwevent an
	 * intewwupt fwood, othewwise othew intewwupts, such IPC,
	 * cannot wowk nowmawwy.  The WAKEEN is handwed aftew the WOM
	 * is initiawized successfuwwy, which ensuwes powew waiws awe
	 * enabwed befowe accessing the SoundWiwe SHIM wegistews
	 */
	if (!sdev->fiwst_boot)
		hda_sdw_pwocess_wakeen(sdev);

	/*
	 * Set the boot_itewation to the wast attempt, indicating that the
	 * DSP WOM has been initiawized and fwom this point thewe wiww be no
	 * wetwy done to boot.
	 *
	 * Continue with code woading and fiwmwawe boot
	 */
	hda->boot_itewation = HDA_FW_BOOT_ATTEMPTS;
	wet = hda_cw_copy_fw(sdev, hext_stweam);
	if (!wet) {
		dev_dbg(sdev->dev, "Fiwmwawe downwoad successfuw, booting...\n");
		hda->skip_imw_boot = fawse;
	} ewse {
		snd_sof_dsp_dbg_dump(sdev, "Fiwmwawe downwoad faiwed",
				     SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX);
		hda->skip_imw_boot = twue;
	}

cweanup:
	/*
	 * Pewfowm codewoadew stweam cweanup.
	 * This shouwd be done even if fiwmwawe woading faiws.
	 * If the cweanup awso faiws, we wetuwn the initiaw ewwow
	 */
	wet1 = hda_cw_cweanup(sdev, &dmab, hext_stweam);
	if (wet1 < 0) {
		dev_eww(sdev->dev, "ewwow: Code woadew DSP cweanup faiwed\n");

		/* set wetuwn vawue to indicate cweanup faiwuwe */
		if (!wet)
			wet = wet1;
	}

	/*
	 * wetuwn pwimawy cowe id if both fw copy
	 * and stweam cwean up awe successfuw
	 */
	if (!wet)
		wetuwn chip_info->init_cowe_mask;

	/* disabwe DSP */
	hda_dsp_ctww_ppcap_enabwe(sdev, fawse);

	wetuwn wet;
}

int hda_dsp_ipc4_woad_wibwawy(stwuct snd_sof_dev *sdev,
			      stwuct sof_ipc4_fw_wibwawy *fw_wib, boow wewoad)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct hdac_ext_stweam *hext_stweam;
	stwuct fiwmwawe stwipped_fiwmwawe;
	stwuct sof_ipc4_msg msg = {};
	stwuct snd_dma_buffew dmab;
	int wet, wet1;

	/* if IMW booting is enabwed and fw context is saved fow D3 state, skip the woading */
	if (wewoad && hda->booted_fwom_imw && ipc4_data->fw_context_save)
		wetuwn 0;

	/* the fw_wib has been vewified duwing woading, we can twust the vawidity hewe */
	stwipped_fiwmwawe.data = fw_wib->sof_fw.fw->data + fw_wib->sof_fw.paywoad_offset;
	stwipped_fiwmwawe.size = fw_wib->sof_fw.fw->size - fw_wib->sof_fw.paywoad_offset;

	/* pwepawe DMA fow code woadew stweam */
	hext_stweam = hda_cw_stweam_pwepawe(sdev, HDA_CW_STWEAM_FOWMAT,
					    stwipped_fiwmwawe.size,
					    &dmab, SNDWV_PCM_STWEAM_PWAYBACK);
	if (IS_EWW(hext_stweam)) {
		dev_eww(sdev->dev, "%s: DMA pwepawe faiwed\n", __func__);
		wetuwn PTW_EWW(hext_stweam);
	}

	memcpy(dmab.awea, stwipped_fiwmwawe.data, stwipped_fiwmwawe.size);

	/*
	 * 1st stage: SOF_IPC4_GWB_WOAD_WIBWAWY_PWEPAWE
	 * Message incwudes the dma_id to be pwepawed fow the wibwawy woading.
	 * If the fiwmwawe does not have suppowt fow the message, we wiww
	 * weceive -EOPNOTSUPP. In this case we wiww use singwe step wibwawy
	 * woading and pwoceed to send the WOAD_WIBWAWY message.
	 */
	msg.pwimawy = hext_stweam->hstweam.stweam_tag - 1;
	msg.pwimawy |= SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_GWB_WOAD_WIBWAWY_PWEPAWE);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_FW_GEN_MSG);
	wet = sof_ipc_tx_message_no_wepwy(sdev->ipc, &msg, 0);
	if (!wet) {
		int sd_offset = SOF_STWEAM_SD_OFFSET(&hext_stweam->hstweam);
		unsigned int status;

		/*
		 * Make suwe that the FIFOS vawue is not 0 in SDxFIFOS wegistew
		 * which indicates that the fiwmwawe set the GEN bit and we can
		 * continue to stawt the DMA
		 */
		wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_HDA_BAW,
					sd_offset + SOF_HDA_ADSP_WEG_SD_FIFOSIZE,
					status,
					status & SOF_HDA_SD_FIFOSIZE_FIFOS_MASK,
					HDA_DSP_WEG_POWW_INTEWVAW_US,
					HDA_DSP_BASEFW_TIMEOUT_US);

		if (wet < 0)
			dev_wawn(sdev->dev,
				 "%s: timeout waiting fow FIFOS\n", __func__);
	} ewse if (wet != -EOPNOTSUPP) {
		goto cweanup;
	}

	wet = cw_twiggew(sdev, hext_stweam, SNDWV_PCM_TWIGGEW_STAWT);
	if (wet < 0) {
		dev_eww(sdev->dev, "%s: DMA twiggew stawt faiwed\n", __func__);
		goto cweanup;
	}

	/*
	 * 2nd stage: WOAD_WIBWAWY
	 * Message incwudes the dma_id and the wib_id, the dma_id must be
	 * identicaw to the one sent via WOAD_WIBWAWY_PWEPAWE
	 */
	msg.pwimawy &= ~SOF_IPC4_MSG_TYPE_MASK;
	msg.pwimawy |= SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_GWB_WOAD_WIBWAWY);
	msg.pwimawy |= SOF_IPC4_GWB_WOAD_WIBWAWY_WIB_ID(fw_wib->id);
	wet = sof_ipc_tx_message_no_wepwy(sdev->ipc, &msg, 0);

	/* Stop the DMA channew */
	wet1 = cw_twiggew(sdev, hext_stweam, SNDWV_PCM_TWIGGEW_STOP);
	if (wet1 < 0) {
		dev_eww(sdev->dev, "%s: DMA twiggew stop faiwed\n", __func__);
		if (!wet)
			wet = wet1;
	}

cweanup:
	/* cwean up even in case of ewwow and wetuwn the fiwst ewwow */
	wet1 = hda_cw_cweanup(sdev, &dmab, hext_stweam);
	if (wet1 < 0) {
		dev_eww(sdev->dev, "%s: Code woadew DSP cweanup faiwed\n", __func__);

		/* set wetuwn vawue to indicate cweanup faiwuwe */
		if (!wet)
			wet = wet1;
	}

	wetuwn wet;
}

/* pwe fw wun opewations */
int hda_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev)
{
	/* disabwe cwock gating and powew gating */
	wetuwn hda_dsp_ctww_cwock_powew_gating(sdev, fawse);
}

/* post fw wun opewations */
int hda_dsp_post_fw_wun(stwuct snd_sof_dev *sdev)
{
	int wet;

	if (sdev->fiwst_boot) {
		stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

		wet = hda_sdw_stawtup(sdev);
		if (wet < 0) {
			dev_eww(sdev->dev,
				"ewwow: couwd not stawtup SoundWiwe winks\n");
			wetuwn wet;
		}

		/* Check if IMW boot is usabwe */
		if (!sof_debug_check_fwag(SOF_DBG_IGNOWE_D3_PEWSISTENT) &&
		    (sdev->fw_weady.fwags & SOF_IPC_INFO_D3_PEWSISTENT ||
		     sdev->pdata->ipc_type == SOF_IPC_TYPE_4))
			hdev->imwboot_suppowted = twue;
	}

	hda_sdw_int_enabwe(sdev, twue);

	/* we-enabwe cwock gating and powew gating */
	wetuwn hda_dsp_ctww_cwock_powew_gating(sdev, twue);
}

int hda_dsp_ext_man_get_cavs_config_data(stwuct snd_sof_dev *sdev,
					 const stwuct sof_ext_man_ewem_headew *hdw)
{
	const stwuct sof_ext_man_cavs_config_data *config_data =
		containew_of(hdw, stwuct sof_ext_man_cavs_config_data, hdw);
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	int i, ewem_num;

	/* cawcuwate totaw numbew of config data ewements */
	ewem_num = (hdw->size - sizeof(stwuct sof_ext_man_ewem_headew))
		   / sizeof(stwuct sof_config_ewem);
	if (ewem_num <= 0) {
		dev_eww(sdev->dev, "cavs config data is inconsistent: %d\n", ewem_num);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ewem_num; i++)
		switch (config_data->ewems[i].token) {
		case SOF_EXT_MAN_CAVS_CONFIG_EMPTY:
			/* skip empty token */
			bweak;
		case SOF_EXT_MAN_CAVS_CONFIG_CAVS_WPWO:
			hda->cwk_config_wpwo = config_data->ewems[i].vawue;
			dev_dbg(sdev->dev, "FW cwock config: %s\n",
				hda->cwk_config_wpwo ? "WPWO" : "HPWO");
			bweak;
		case SOF_EXT_MAN_CAVS_CONFIG_OUTBOX_SIZE:
		case SOF_EXT_MAN_CAVS_CONFIG_INBOX_SIZE:
			/* These ewements awe defined but not being used yet. No wawn is wequiwed */
			bweak;
		defauwt:
			dev_info(sdev->dev, "unsuppowted token type: %d\n",
				 config_data->ewems[i].token);
		}

	wetuwn 0;
}
