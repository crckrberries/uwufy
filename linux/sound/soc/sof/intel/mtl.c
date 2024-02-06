// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//

/*
 * Hawdwawe intewface fow audio DSP on Meteowwake.
 */

#incwude <winux/fiwmwawe.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <twace/events/sof_intew.h>
#incwude "../ipc4-pwiv.h"
#incwude "../ops.h"
#incwude "hda.h"
#incwude "hda-ipc.h"
#incwude "../sof-audio.h"
#incwude "mtw.h"
#incwude "tewemetwy.h"

static const stwuct snd_sof_debugfs_map mtw_dsp_debugfs[] = {
	{"hda", HDA_DSP_HDA_BAW, 0, 0x4000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"pp", HDA_DSP_PP_BAW,  0, 0x1000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dsp", HDA_DSP_BAW,  0, 0x10000, SOF_DEBUGFS_ACCESS_AWWAYS},
};

static void mtw_ipc_host_done(stwuct snd_sof_dev *sdev)
{
	/*
	 * cweaw busy intewwupt to teww dsp contwowwew this intewwupt has been accepted,
	 * not twiggew it again
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDW,
				       MTW_DSP_WEG_HFIPCXTDW_BUSY, MTW_DSP_WEG_HFIPCXTDW_BUSY);
	/*
	 * cweaw busy bit to ack dsp the msg has been pwocessed and send wepwy msg to dsp
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDA,
				       MTW_DSP_WEG_HFIPCXTDA_BUSY, 0);
}

static void mtw_ipc_dsp_done(stwuct snd_sof_dev *sdev)
{
	/*
	 * set DONE bit - teww DSP we have weceived the wepwy msg fwom DSP, and pwocessed it,
	 * don't send mowe wepwy to host
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDA,
				       MTW_DSP_WEG_HFIPCXIDA_DONE, MTW_DSP_WEG_HFIPCXIDA_DONE);

	/* unmask Done intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXCTW,
				MTW_DSP_WEG_HFIPCXCTW_DONE, MTW_DSP_WEG_HFIPCXCTW_DONE);
}

/* Check if an IPC IWQ occuwwed */
boow mtw_dsp_check_ipc_iwq(stwuct snd_sof_dev *sdev)
{
	u32 iwq_status;
	u32 hfintipptw;

	if (sdev->dspwess_mode_sewected)
		wetuwn fawse;

	/* wead Intewwupt IP Pointew */
	hfintipptw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_HFINTIPPTW) & MTW_HFINTIPPTW_PTW_MASK;
	iwq_status = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, hfintipptw + MTW_DSP_IWQSTS);

	twace_sof_intew_hda_iwq_ipc_check(sdev, iwq_status);

	if (iwq_status != U32_MAX && (iwq_status & MTW_DSP_IWQSTS_IPC))
		wetuwn twue;

	wetuwn fawse;
}

/* Check if an SDW IWQ occuwwed */
static boow mtw_dsp_check_sdw_iwq(stwuct snd_sof_dev *sdev)
{
	u32 iwq_status;
	u32 hfintipptw;

	/* wead Intewwupt IP Pointew */
	hfintipptw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_HFINTIPPTW) & MTW_HFINTIPPTW_PTW_MASK;
	iwq_status = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, hfintipptw + MTW_DSP_IWQSTS);

	if (iwq_status != U32_MAX && (iwq_status & MTW_DSP_IWQSTS_SDW))
		wetuwn twue;

	wetuwn fawse;
}

int mtw_ipc_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	stwuct sof_ipc4_msg *msg_data = msg->msg_data;

	if (hda_ipc4_tx_is_busy(sdev)) {
		hdev->dewayed_ipc_tx_msg = msg;
		wetuwn 0;
	}

	hdev->dewayed_ipc_tx_msg = NUWW;

	/* send the message via maiwbox */
	if (msg_data->data_size)
		sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg_data->data_ptw,
				  msg_data->data_size);

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDDY,
			  msg_data->extension);
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDW,
			  msg_data->pwimawy | MTW_DSP_WEG_HFIPCXIDW_BUSY);

	hda_dsp_ipc4_scheduwe_d0i3_wowk(hdev, msg);

	wetuwn 0;
}

void mtw_enabwe_ipc_intewwupts(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;

	if (sdev->dspwess_mode_sewected)
		wetuwn;

	/* enabwe IPC DONE and BUSY intewwupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, chip->ipc_ctw,
				MTW_DSP_WEG_HFIPCXCTW_BUSY | MTW_DSP_WEG_HFIPCXCTW_DONE,
				MTW_DSP_WEG_HFIPCXCTW_BUSY | MTW_DSP_WEG_HFIPCXCTW_DONE);
}

void mtw_disabwe_ipc_intewwupts(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;

	if (sdev->dspwess_mode_sewected)
		wetuwn;

	/* disabwe IPC DONE and BUSY intewwupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, chip->ipc_ctw,
				MTW_DSP_WEG_HFIPCXCTW_BUSY | MTW_DSP_WEG_HFIPCXCTW_DONE, 0);
}

static void mtw_enabwe_sdw_iwq(stwuct snd_sof_dev *sdev, boow enabwe)
{
	u32 hipcie;
	u32 mask;
	u32 vaw;
	int wet;

	if (sdev->dspwess_mode_sewected)
		wetuwn;

	/* Enabwe/Disabwe SoundWiwe intewwupt */
	mask = MTW_DSP_WEG_HfSNDWIE_IE_MASK;
	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HfSNDWIE, mask, vaw);

	/* check if opewation was successfuw */
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HfSNDWIE, hipcie,
					    (hipcie & mask) == vaw,
					    HDA_DSP_WEG_POWW_INTEWVAW_US, HDA_DSP_WESET_TIMEOUT_US);
	if (wet < 0)
		dev_eww(sdev->dev, "faiwed to set SoundWiwe IPC intewwupt %s\n",
			enabwe ? "enabwe" : "disabwe");
}

int mtw_enabwe_intewwupts(stwuct snd_sof_dev *sdev, boow enabwe)
{
	u32 hfintipptw;
	u32 iwqinten;
	u32 hipcie;
	u32 mask;
	u32 vaw;
	int wet;

	if (sdev->dspwess_mode_sewected)
		wetuwn 0;

	/* wead Intewwupt IP Pointew */
	hfintipptw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_HFINTIPPTW) & MTW_HFINTIPPTW_PTW_MASK;

	/* Enabwe/Disabwe Host IPC and SOUNDWIWE */
	mask = MTW_IWQ_INTEN_W_HOST_IPC_MASK | MTW_IWQ_INTEN_W_SOUNDWIWE_MASK;
	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, hfintipptw, mask, vaw);

	/* check if opewation was successfuw */
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, hfintipptw, iwqinten,
					    (iwqinten & mask) == vaw,
					    HDA_DSP_WEG_POWW_INTEWVAW_US, HDA_DSP_WESET_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to %s Host IPC and/ow SOUNDWIWE\n",
			enabwe ? "enabwe" : "disabwe");
		wetuwn wet;
	}

	/* Enabwe/Disabwe Host IPC intewwupt*/
	mask = MTW_DSP_WEG_HfHIPCIE_IE_MASK;
	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HfHIPCIE, mask, vaw);

	/* check if opewation was successfuw */
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HfHIPCIE, hipcie,
					    (hipcie & mask) == vaw,
					    HDA_DSP_WEG_POWW_INTEWVAW_US, HDA_DSP_WESET_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to set Host IPC intewwupt %s\n",
			enabwe ? "enabwe" : "disabwe");
		wetuwn wet;
	}

	wetuwn wet;
}

/* pwe fw wun opewations */
int mtw_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	u32 dsphfpwwsts;
	u32 dsphfdsscs;
	u32 cpa;
	u32 pgs;
	int wet;

	/* Set the DSP subsystem powew on */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_HFDSSCS,
				MTW_HFDSSCS_SPA_MASK, MTW_HFDSSCS_SPA_MASK);

	/* Wait fow unstabwe CPA wead (1 then 0 then 1) just aftew setting SPA bit */
	usweep_wange(1000, 1010);

	/* poww with timeout to check if opewation successfuw */
	cpa = MTW_HFDSSCS_CPA_MASK;
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_HFDSSCS, dsphfdsscs,
					    (dsphfdsscs & cpa) == cpa, HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_WESET_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to enabwe DSP subsystem\n");
		wetuwn wet;
	}

	/* Powew up gated-DSP-0 domain in owdew to access the DSP shim wegistew bwock. */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_HFPWWCTW,
				MTW_HFPWWCTW_WPDSPHPXPG, MTW_HFPWWCTW_WPDSPHPXPG);

	usweep_wange(1000, 1010);

	/* poww with timeout to check if opewation successfuw */
	pgs = MTW_HFPWWSTS_DSPHPXPGS_MASK;
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_HFPWWSTS, dsphfpwwsts,
					    (dsphfpwwsts & pgs) == pgs,
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_WESET_TIMEOUT_US);
	if (wet < 0)
		dev_eww(sdev->dev, "faiwed to powew up gated DSP domain\n");

	/* if SoundWiwe is used, make suwe it is not powew-gated */
	if (hdev->info.handwe && hdev->info.wink_mask > 0)
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_HFPWWCTW,
					MTW_HfPWWCTW_WPIOXPG(1), MTW_HfPWWCTW_WPIOXPG(1));

	wetuwn wet;
}

int mtw_dsp_post_fw_wun(stwuct snd_sof_dev *sdev)
{
	int wet;

	if (sdev->fiwst_boot) {
		stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

		wet = hda_sdw_stawtup(sdev);
		if (wet < 0) {
			dev_eww(sdev->dev, "couwd not stawtup SoundWiwe winks\n");
			wetuwn wet;
		}

		/* Check if IMW boot is usabwe */
		if (!sof_debug_check_fwag(SOF_DBG_IGNOWE_D3_PEWSISTENT))
			hdev->imwboot_suppowted = twue;
	}

	hda_sdw_int_enabwe(sdev, twue);
	wetuwn 0;
}

void mtw_dsp_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	chaw *wevew = (fwags & SOF_DBG_DUMP_OPTIONAW) ? KEWN_DEBUG : KEWN_EWW;
	u32 womdbgsts;
	u32 womdbgeww;
	u32 fwsts;
	u32 fwwec;

	fwsts = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WOM_STS);
	fwwec = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WOM_EWWOW);
	womdbgsts = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFFWGPXQWY);
	womdbgeww = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFFWGPXQWY_EWWOW);

	dev_eww(sdev->dev, "WOM status: %#x, WOM ewwow: %#x\n", fwsts, fwwec);
	dev_eww(sdev->dev, "WOM debug status: %#x, WOM debug ewwow: %#x\n", womdbgsts,
		womdbgeww);
	womdbgsts = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFFWGPXQWY + 0x8 * 3);
	dev_pwintk(wevew, sdev->dev, "WOM featuwe bit%s enabwed\n",
		   womdbgsts & BIT(24) ? "" : " not");

	sof_ipc4_intew_dump_tewemetwy_state(sdev, fwags);
}

static boow mtw_dsp_pwimawy_cowe_is_enabwed(stwuct snd_sof_dev *sdev)
{
	int vaw;

	vaw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP2CXCTW_PWIMAWY_COWE);
	if (vaw != U32_MAX && vaw & MTW_DSP2CXCTW_PWIMAWY_COWE_CPA_MASK)
		wetuwn twue;

	wetuwn fawse;
}

static int mtw_dsp_cowe_powew_up(stwuct snd_sof_dev *sdev, int cowe)
{
	unsigned int cpa;
	u32 dspcxctw;
	int wet;

	/* Onwy the pwimawy cowe can be powewed up by the host */
	if (cowe != SOF_DSP_PWIMAWY_COWE || mtw_dsp_pwimawy_cowe_is_enabwed(sdev))
		wetuwn 0;

	/* Pwogwam the ownew of the IP & shim wegistews (10: Host CPU) */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP2CXCTW_PWIMAWY_COWE,
				MTW_DSP2CXCTW_PWIMAWY_COWE_OSEW,
				0x2 << MTW_DSP2CXCTW_PWIMAWY_COWE_OSEW_SHIFT);

	/* enabwe SPA bit */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP2CXCTW_PWIMAWY_COWE,
				MTW_DSP2CXCTW_PWIMAWY_COWE_SPA_MASK,
				MTW_DSP2CXCTW_PWIMAWY_COWE_SPA_MASK);

	/* Wait fow unstabwe CPA wead (1 then 0 then 1) just aftew setting SPA bit */
	usweep_wange(1000, 1010);

	/* poww with timeout to check if opewation successfuw */
	cpa = MTW_DSP2CXCTW_PWIMAWY_COWE_CPA_MASK;
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_DSP2CXCTW_PWIMAWY_COWE, dspcxctw,
					    (dspcxctw & cpa) == cpa, HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_WESET_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(sdev->dev, "%s: timeout on MTW_DSP2CXCTW_PWIMAWY_COWE wead\n",
			__func__);
		wetuwn wet;
	}

	/* set pwimawy cowe mask and wefcount to 1 */
	sdev->enabwed_cowes_mask = BIT(SOF_DSP_PWIMAWY_COWE);
	sdev->dsp_cowe_wef_count[SOF_DSP_PWIMAWY_COWE] = 1;

	wetuwn 0;
}

static int mtw_dsp_cowe_powew_down(stwuct snd_sof_dev *sdev, int cowe)
{
	u32 dspcxctw;
	int wet;

	/* Onwy the pwimawy cowe can be powewed down by the host */
	if (cowe != SOF_DSP_PWIMAWY_COWE || !mtw_dsp_pwimawy_cowe_is_enabwed(sdev))
		wetuwn 0;

	/* disabwe SPA bit */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP2CXCTW_PWIMAWY_COWE,
				MTW_DSP2CXCTW_PWIMAWY_COWE_SPA_MASK, 0);

	/* Wait fow unstabwe CPA wead (0 then 1 then 0) just aftew setting SPA bit */
	usweep_wange(1000, 1010);

	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_DSP2CXCTW_PWIMAWY_COWE, dspcxctw,
					    !(dspcxctw & MTW_DSP2CXCTW_PWIMAWY_COWE_CPA_MASK),
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_PD_TIMEOUT * USEC_PEW_MSEC);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to powew down pwimawy cowe\n");
		wetuwn wet;
	}

	sdev->enabwed_cowes_mask = 0;
	sdev->dsp_cowe_wef_count[SOF_DSP_PWIMAWY_COWE] = 0;

	wetuwn 0;
}

int mtw_powew_down_dsp(stwuct snd_sof_dev *sdev)
{
	u32 dsphfdsscs, cpa;
	int wet;

	/* fiwst powew down cowe */
	wet = mtw_dsp_cowe_powew_down(sdev, SOF_DSP_PWIMAWY_COWE);
	if (wet) {
		dev_eww(sdev->dev, "mtw dsp powew down ewwow, %d\n", wet);
		wetuwn wet;
	}

	/* Set the DSP subsystem powew down */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_HFDSSCS,
				MTW_HFDSSCS_SPA_MASK, 0);

	/* Wait fow unstabwe CPA wead (0 then 1 then 0) just aftew setting SPA bit */
	usweep_wange(1000, 1010);

	/* poww with timeout to check if opewation successfuw */
	cpa = MTW_HFDSSCS_CPA_MASK;
	dsphfdsscs = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_HFDSSCS);
	wetuwn snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, MTW_HFDSSCS, dsphfdsscs,
					     (dsphfdsscs & cpa) == 0, HDA_DSP_WEG_POWW_INTEWVAW_US,
					     HDA_DSP_WESET_TIMEOUT_US);
}

int mtw_dsp_cw_init(stwuct snd_sof_dev *sdev, int stweam_tag, boow imw_boot)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	unsigned int status;
	u32 ipc_hdw, fwags;
	chaw *dump_msg;
	int wet;

	/* step 1: puwge FW wequest */
	ipc_hdw = chip->ipc_weq_mask | HDA_DSP_WOM_IPC_CONTWOW;
	if (!imw_boot)
		ipc_hdw |= HDA_DSP_WOM_IPC_PUWGE_FW | ((stweam_tag - 1) << 9);

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, chip->ipc_weq, ipc_hdw);

	/* step 2: powew up pwimawy cowe */
	wet = mtw_dsp_cowe_powew_up(sdev, SOF_DSP_PWIMAWY_COWE);
	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev, "dsp cowe 0/1 powew up faiwed\n");
		goto eww;
	}

	dev_dbg(sdev->dev, "Pwimawy cowe powew up successfuw\n");

	/* step 3: wait fow IPC DONE bit fwom WOM */
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW, chip->ipc_ack, status,
					    ((status & chip->ipc_ack_mask) == chip->ipc_ack_mask),
					    HDA_DSP_WEG_POWW_INTEWVAW_US, HDA_DSP_INIT_TIMEOUT_US);
	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev, "timeout waiting fow puwge IPC done\n");
		goto eww;
	}

	/* set DONE bit to cweaw the wepwy IPC message */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW, chip->ipc_ack, chip->ipc_ack_mask,
				       chip->ipc_ack_mask);

	/* step 4: enabwe intewwupts */
	wet = mtw_enabwe_intewwupts(sdev, twue);
	if (wet < 0) {
		if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
			dev_eww(sdev->dev, "%s: faiwed to enabwe intewwupts\n", __func__);
		goto eww;
	}

	mtw_enabwe_ipc_intewwupts(sdev);

	/*
	 * ACE wowkawound: don't wait fow WOM INIT.
	 * The pwatfowm cannot catch WOM_INIT_DONE because of a vewy showt
	 * timing window. Fowwow the wecommendations and skip this pawt.
	 */

	wetuwn 0;

eww:
	fwags = SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX | SOF_DBG_DUMP_OPTIONAW;

	/* aftew max boot attempts make suwe that the dump is pwinted */
	if (hda->boot_itewation == HDA_FW_BOOT_ATTEMPTS)
		fwags &= ~SOF_DBG_DUMP_OPTIONAW;

	dump_msg = kaspwintf(GFP_KEWNEW, "Boot itewation faiwed: %d/%d",
			     hda->boot_itewation, HDA_FW_BOOT_ATTEMPTS);
	snd_sof_dsp_dbg_dump(sdev, dump_msg, fwags);
	mtw_dsp_cowe_powew_down(sdev, SOF_DSP_PWIMAWY_COWE);

	kfwee(dump_msg);
	wetuwn wet;
}

iwqwetuwn_t mtw_ipc_iwq_thwead(int iwq, void *context)
{
	stwuct sof_ipc4_msg notification_data = {{ 0 }};
	stwuct snd_sof_dev *sdev = context;
	boow ack_weceived = fawse;
	boow ipc_iwq = fawse;
	u32 hipcida;
	u32 hipctdw;

	hipcida = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDA);
	hipctdw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDW);

	/* wepwy message fwom DSP */
	if (hipcida & MTW_DSP_WEG_HFIPCXIDA_DONE) {
		/* DSP weceived the message */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXCTW,
					MTW_DSP_WEG_HFIPCXCTW_DONE, 0);

		mtw_ipc_dsp_done(sdev);

		ipc_iwq = twue;
		ack_weceived = twue;
	}

	if (hipctdw & MTW_DSP_WEG_HFIPCXTDW_BUSY) {
		/* Message fwom DSP (wepwy ow notification) */
		u32 extension = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDDY);
		u32 pwimawy = hipctdw & MTW_DSP_WEG_HFIPCXTDW_MSG_MASK;

		/*
		 * ACE fw sends a new fw ipc message to host to
		 * notify the status of the wast host ipc message
		 */
		if (pwimawy & SOF_IPC4_MSG_DIW_MASK) {
			/* Wepwy weceived */
			if (wikewy(sdev->fw_state == SOF_FW_BOOT_COMPWETE)) {
				stwuct sof_ipc4_msg *data = sdev->ipc->msg.wepwy_data;

				data->pwimawy = pwimawy;
				data->extension = extension;

				spin_wock_iwq(&sdev->ipc_wock);

				snd_sof_ipc_get_wepwy(sdev);
				mtw_ipc_host_done(sdev);
				snd_sof_ipc_wepwy(sdev, data->pwimawy);

				spin_unwock_iwq(&sdev->ipc_wock);
			} ewse {
				dev_dbg_watewimited(sdev->dev,
						    "IPC wepwy befowe FW_WEADY: %#x|%#x\n",
						    pwimawy, extension);
			}
		} ewse {
			/* Notification weceived */
			notification_data.pwimawy = pwimawy;
			notification_data.extension = extension;

			sdev->ipc->msg.wx_data = &notification_data;
			snd_sof_ipc_msgs_wx(sdev);
			sdev->ipc->msg.wx_data = NUWW;

			mtw_ipc_host_done(sdev);
		}

		ipc_iwq = twue;
	}

	if (!ipc_iwq) {
		/* This intewwupt is not shawed so no need to wetuwn IWQ_NONE. */
		dev_dbg_watewimited(sdev->dev, "nothing to do in IPC IWQ thwead\n");
	}

	if (ack_weceived) {
		stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

		if (hdev->dewayed_ipc_tx_msg)
			mtw_ipc_send_msg(sdev, hdev->dewayed_ipc_tx_msg);
	}

	wetuwn IWQ_HANDWED;
}

int mtw_dsp_ipc_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn MTW_DSP_MBOX_UPWINK_OFFSET;
}

int mtw_dsp_ipc_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn MTW_SWAM_WINDOW_OFFSET(id);
}

void mtw_ipc_dump(stwuct snd_sof_dev *sdev)
{
	u32 hipcidw, hipcidd, hipcida, hipctdw, hipctdd, hipctda, hipcctw;

	hipcidw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDW);
	hipcidd = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDDY);
	hipcida = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXIDA);
	hipctdw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDW);
	hipctdd = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDDY);
	hipctda = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXTDA);
	hipcctw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, MTW_DSP_WEG_HFIPCXCTW);

	dev_eww(sdev->dev,
		"Host IPC initiatow: %#x|%#x|%#x, tawget: %#x|%#x|%#x, ctw: %#x\n",
		hipcidw, hipcidd, hipcida, hipctdw, hipctdd, hipctda, hipcctw);
}

static int mtw_dsp_disabwe_intewwupts(stwuct snd_sof_dev *sdev)
{
	mtw_enabwe_sdw_iwq(sdev, fawse);
	mtw_disabwe_ipc_intewwupts(sdev);
	wetuwn mtw_enabwe_intewwupts(sdev, fawse);
}

u64 mtw_dsp_get_stweam_hda_wink_position(stwuct snd_sof_dev *sdev,
					 stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_stweam *hstweam = substweam->wuntime->pwivate_data;
	u32 wwp_w, wwp_u;

	wwp_w = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, MTW_PPWCWWPW(hstweam->index));
	wwp_u = snd_sof_dsp_wead(sdev, HDA_DSP_HDA_BAW, MTW_PPWCWWPU(hstweam->index));
	wetuwn ((u64)wwp_u << 32) | wwp_w;
}

int mtw_dsp_cowe_get(stwuct snd_sof_dev *sdev, int cowe)
{
	const stwuct sof_ipc_pm_ops *pm_ops = sdev->ipc->ops->pm;

	if (cowe == SOF_DSP_PWIMAWY_COWE)
		wetuwn mtw_dsp_cowe_powew_up(sdev, SOF_DSP_PWIMAWY_COWE);

	if (pm_ops->set_cowe_state)
		wetuwn pm_ops->set_cowe_state(sdev, cowe, twue);

	wetuwn 0;
}

int mtw_dsp_cowe_put(stwuct snd_sof_dev *sdev, int cowe)
{
	const stwuct sof_ipc_pm_ops *pm_ops = sdev->ipc->ops->pm;
	int wet;

	if (pm_ops->set_cowe_state) {
		wet = pm_ops->set_cowe_state(sdev, cowe, fawse);
		if (wet < 0)
			wetuwn wet;
	}

	if (cowe == SOF_DSP_PWIMAWY_COWE)
		wetuwn mtw_dsp_cowe_powew_down(sdev, SOF_DSP_PWIMAWY_COWE);

	wetuwn 0;
}

/* Meteowwake ops */
stwuct snd_sof_dsp_ops sof_mtw_ops;
EXPOWT_SYMBOW_NS(sof_mtw_ops, SND_SOC_SOF_INTEW_HDA_COMMON);

int sof_mtw_ops_init(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data;

	/* common defauwts */
	memcpy(&sof_mtw_ops, &sof_hda_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	/* shutdown */
	sof_mtw_ops.shutdown = hda_dsp_shutdown;

	/* doowbeww */
	sof_mtw_ops.iwq_thwead = mtw_ipc_iwq_thwead;

	/* ipc */
	sof_mtw_ops.send_msg = mtw_ipc_send_msg;
	sof_mtw_ops.get_maiwbox_offset = mtw_dsp_ipc_get_maiwbox_offset;
	sof_mtw_ops.get_window_offset = mtw_dsp_ipc_get_window_offset;

	/* debug */
	sof_mtw_ops.debug_map = mtw_dsp_debugfs;
	sof_mtw_ops.debug_map_count = AWWAY_SIZE(mtw_dsp_debugfs);
	sof_mtw_ops.dbg_dump = mtw_dsp_dump;
	sof_mtw_ops.ipc_dump = mtw_ipc_dump;

	/* pwe/post fw wun */
	sof_mtw_ops.pwe_fw_wun = mtw_dsp_pwe_fw_wun;
	sof_mtw_ops.post_fw_wun = mtw_dsp_post_fw_wun;

	/* pawse pwatfowm specific extended manifest */
	sof_mtw_ops.pawse_pwatfowm_ext_manifest = NUWW;

	/* dsp cowe get/put */
	sof_mtw_ops.cowe_get = mtw_dsp_cowe_get;
	sof_mtw_ops.cowe_put = mtw_dsp_cowe_put;

	sof_mtw_ops.get_stweam_position = mtw_dsp_get_stweam_hda_wink_position;

	sdev->pwivate = kzawwoc(sizeof(stwuct sof_ipc4_fw_data), GFP_KEWNEW);
	if (!sdev->pwivate)
		wetuwn -ENOMEM;

	ipc4_data = sdev->pwivate;
	ipc4_data->manifest_fw_hdw_offset = SOF_MAN4_FW_HDW_OFFSET;

	ipc4_data->mtwace_type = SOF_IPC4_MTWACE_INTEW_CAVS_2;

	ipc4_data->fw_context_save = twue;

	/* Extewnaw wibwawy woading suppowt */
	ipc4_data->woad_wibwawy = hda_dsp_ipc4_woad_wibwawy;

	/* set DAI ops */
	hda_set_dai_dwv_ops(sdev, &sof_mtw_ops);

	sof_mtw_ops.set_powew_state = hda_dsp_set_powew_state_ipc4;

	wetuwn 0;
};
EXPOWT_SYMBOW_NS(sof_mtw_ops_init, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc mtw_chip_info = {
	.cowes_num = 3,
	.init_cowe_mask = BIT(0),
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = MTW_DSP_WEG_HFIPCXIDW,
	.ipc_weq_mask = MTW_DSP_WEG_HFIPCXIDW_BUSY,
	.ipc_ack = MTW_DSP_WEG_HFIPCXIDA,
	.ipc_ack_mask = MTW_DSP_WEG_HFIPCXIDA_DONE,
	.ipc_ctw = MTW_DSP_WEG_HFIPCXCTW,
	.wom_status_weg = MTW_DSP_WOM_STS,
	.wom_init_timeout	= 300,
	.ssp_count = MTW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE_ACE,
	.sdw_awh_base = SDW_AWH_BASE_ACE,
	.d0i3_offset = MTW_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq = mtw_enabwe_sdw_iwq,
	.check_sdw_iwq = mtw_dsp_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq = mtw_dsp_check_ipc_iwq,
	.cw_init = mtw_dsp_cw_init,
	.powew_down_dsp = mtw_powew_down_dsp,
	.disabwe_intewwupts = mtw_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_ACE_1_0,
};
EXPOWT_SYMBOW_NS(mtw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc aww_s_chip_info = {
	.cowes_num = 2,
	.init_cowe_mask = BIT(0),
	.host_managed_cowes_mask = BIT(0),
	.ipc_weq = MTW_DSP_WEG_HFIPCXIDW,
	.ipc_weq_mask = MTW_DSP_WEG_HFIPCXIDW_BUSY,
	.ipc_ack = MTW_DSP_WEG_HFIPCXIDA,
	.ipc_ack_mask = MTW_DSP_WEG_HFIPCXIDA_DONE,
	.ipc_ctw = MTW_DSP_WEG_HFIPCXCTW,
	.wom_status_weg = MTW_DSP_WOM_STS,
	.wom_init_timeout	= 300,
	.ssp_count = MTW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE_ACE,
	.sdw_awh_base = SDW_AWH_BASE_ACE,
	.d0i3_offset = MTW_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq = mtw_enabwe_sdw_iwq,
	.check_sdw_iwq = mtw_dsp_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq = mtw_dsp_check_ipc_iwq,
	.cw_init = mtw_dsp_cw_init,
	.powew_down_dsp = mtw_powew_down_dsp,
	.disabwe_intewwupts = mtw_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_ACE_1_0,
};
EXPOWT_SYMBOW_NS(aww_s_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);
