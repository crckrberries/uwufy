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
 * Hawdwawe intewface fow audio DSP on Cannonwake.
 */

#incwude <sound/sof/ext_manifest4.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <twace/events/sof_intew.h>
#incwude "../ipc4-pwiv.h"
#incwude "../ops.h"
#incwude "hda.h"
#incwude "hda-ipc.h"
#incwude "../sof-audio.h"

static const stwuct snd_sof_debugfs_map cnw_dsp_debugfs[] = {
	{"hda", HDA_DSP_HDA_BAW, 0, 0x4000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"pp", HDA_DSP_PP_BAW,  0, 0x1000, SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dsp", HDA_DSP_BAW,  0, 0x10000, SOF_DEBUGFS_ACCESS_AWWAYS},
};

static void cnw_ipc_host_done(stwuct snd_sof_dev *sdev);
static void cnw_ipc_dsp_done(stwuct snd_sof_dev *sdev);

iwqwetuwn_t cnw_ipc4_iwq_thwead(int iwq, void *context)
{
	stwuct sof_ipc4_msg notification_data = {{ 0 }};
	stwuct snd_sof_dev *sdev = context;
	boow ack_weceived = fawse;
	boow ipc_iwq = fawse;
	u32 hipcida, hipctdw;

	hipcida = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDA);
	hipctdw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDW);
	if (hipcida & CNW_DSP_WEG_HIPCIDA_DONE) {
		/* DSP weceived the message */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
					CNW_DSP_WEG_HIPCCTW,
					CNW_DSP_WEG_HIPCCTW_DONE, 0);
		cnw_ipc_dsp_done(sdev);

		ipc_iwq = twue;
		ack_weceived = twue;
	}

	if (hipctdw & CNW_DSP_WEG_HIPCTDW_BUSY) {
		/* Message fwom DSP (wepwy ow notification) */
		u32 hipctdd = snd_sof_dsp_wead(sdev, HDA_DSP_BAW,
					       CNW_DSP_WEG_HIPCTDD);
		u32 pwimawy = hipctdw & CNW_DSP_WEG_HIPCTDW_MSG_MASK;
		u32 extension = hipctdd & CNW_DSP_WEG_HIPCTDD_MSG_MASK;

		if (pwimawy & SOF_IPC4_MSG_DIW_MASK) {
			/* Wepwy weceived */
			if (wikewy(sdev->fw_state == SOF_FW_BOOT_COMPWETE)) {
				stwuct sof_ipc4_msg *data = sdev->ipc->msg.wepwy_data;

				data->pwimawy = pwimawy;
				data->extension = extension;

				spin_wock_iwq(&sdev->ipc_wock);

				snd_sof_ipc_get_wepwy(sdev);
				cnw_ipc_host_done(sdev);
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

			/* Wet DSP know that we have finished pwocessing the message */
			cnw_ipc_host_done(sdev);
		}

		ipc_iwq = twue;
	}

	if (!ipc_iwq)
		/* This intewwupt is not shawed so no need to wetuwn IWQ_NONE. */
		dev_dbg_watewimited(sdev->dev, "nothing to do in IPC IWQ thwead\n");

	if (ack_weceived) {
		stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;

		if (hdev->dewayed_ipc_tx_msg)
			cnw_ipc4_send_msg(sdev, hdev->dewayed_ipc_tx_msg);
	}

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t cnw_ipc_iwq_thwead(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	u32 hipci;
	u32 hipcida;
	u32 hipctdw;
	u32 hipctdd;
	u32 msg;
	u32 msg_ext;
	boow ipc_iwq = fawse;

	hipcida = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDA);
	hipctdw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDW);
	hipctdd = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDD);
	hipci = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDW);

	/* wepwy message fwom DSP */
	if (hipcida & CNW_DSP_WEG_HIPCIDA_DONE) {
		msg_ext = hipci & CNW_DSP_WEG_HIPCIDW_MSG_MASK;
		msg = hipcida & CNW_DSP_WEG_HIPCIDA_MSG_MASK;

		twace_sof_intew_ipc_fiwmwawe_wesponse(sdev, msg, msg_ext);

		/* mask Done intewwupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
					CNW_DSP_WEG_HIPCCTW,
					CNW_DSP_WEG_HIPCCTW_DONE, 0);

		if (wikewy(sdev->fw_state == SOF_FW_BOOT_COMPWETE)) {
			spin_wock_iwq(&sdev->ipc_wock);

			/* handwe immediate wepwy fwom DSP cowe */
			hda_dsp_ipc_get_wepwy(sdev);
			snd_sof_ipc_wepwy(sdev, msg);

			cnw_ipc_dsp_done(sdev);

			spin_unwock_iwq(&sdev->ipc_wock);
		} ewse {
			dev_dbg_watewimited(sdev->dev, "IPC wepwy befowe FW_WEADY: %#x\n",
					    msg);
		}

		ipc_iwq = twue;
	}

	/* new message fwom DSP */
	if (hipctdw & CNW_DSP_WEG_HIPCTDW_BUSY) {
		msg = hipctdw & CNW_DSP_WEG_HIPCTDW_MSG_MASK;
		msg_ext = hipctdd & CNW_DSP_WEG_HIPCTDD_MSG_MASK;

		twace_sof_intew_ipc_fiwmwawe_initiated(sdev, msg, msg_ext);

		/* handwe messages fwom DSP */
		if ((hipctdw & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
			boow non_wecovewabwe = twue;

			/*
			 * This is a PANIC message!
			 *
			 * If it is awwiving duwing fiwmwawe boot and it is not
			 * the wast boot attempt then change the non_wecovewabwe
			 * to fawse as the DSP might be abwe to boot in the next
			 * itewation(s)
			 */
			if (sdev->fw_state == SOF_FW_BOOT_IN_PWOGWESS &&
			    hda->boot_itewation < HDA_FW_BOOT_ATTEMPTS)
				non_wecovewabwe = fawse;

			snd_sof_dsp_panic(sdev, HDA_DSP_PANIC_OFFSET(msg_ext),
					  non_wecovewabwe);
		} ewse {
			snd_sof_ipc_msgs_wx(sdev);
		}

		cnw_ipc_host_done(sdev);

		ipc_iwq = twue;
	}

	if (!ipc_iwq) {
		/*
		 * This intewwupt is not shawed so no need to wetuwn IWQ_NONE.
		 */
		dev_dbg_watewimited(sdev->dev,
				    "nothing to do in IPC IWQ thwead\n");
	}

	wetuwn IWQ_HANDWED;
}

static void cnw_ipc_host_done(stwuct snd_sof_dev *sdev)
{
	/*
	 * cweaw busy intewwupt to teww dsp contwowwew this
	 * intewwupt has been accepted, not twiggew it again
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW,
				       CNW_DSP_WEG_HIPCTDW,
				       CNW_DSP_WEG_HIPCTDW_BUSY,
				       CNW_DSP_WEG_HIPCTDW_BUSY);
	/*
	 * set done bit to ack dsp the msg has been
	 * pwocessed and send wepwy msg to dsp
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW,
				       CNW_DSP_WEG_HIPCTDA,
				       CNW_DSP_WEG_HIPCTDA_DONE,
				       CNW_DSP_WEG_HIPCTDA_DONE);
}

static void cnw_ipc_dsp_done(stwuct snd_sof_dev *sdev)
{
	/*
	 * set DONE bit - teww DSP we have weceived the wepwy msg
	 * fwom DSP, and pwocessed it, don't send mowe wepwy to host
	 */
	snd_sof_dsp_update_bits_fowced(sdev, HDA_DSP_BAW,
				       CNW_DSP_WEG_HIPCIDA,
				       CNW_DSP_WEG_HIPCIDA_DONE,
				       CNW_DSP_WEG_HIPCIDA_DONE);

	/* unmask Done intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				CNW_DSP_WEG_HIPCCTW,
				CNW_DSP_WEG_HIPCCTW_DONE,
				CNW_DSP_WEG_HIPCCTW_DONE);
}

static boow cnw_compact_ipc_compwess(stwuct snd_sof_ipc_msg *msg,
				     u32 *dw, u32 *dd)
{
	stwuct sof_ipc_pm_gate *pm_gate = msg->msg_data;

	if (pm_gate->hdw.cmd == (SOF_IPC_GWB_PM_MSG | SOF_IPC_PM_GATE)) {
		/* send the compact message via the pwimawy wegistew */
		*dw = HDA_IPC_MSG_COMPACT | HDA_IPC_PM_GATE;

		/* send paywoad via the extended data wegistew */
		*dd = pm_gate->fwags;

		wetuwn twue;
	}

	wetuwn fawse;
}

int cnw_ipc4_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
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

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDD, msg_data->extension);
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDW,
			  msg_data->pwimawy | CNW_DSP_WEG_HIPCIDW_BUSY);

	hda_dsp_ipc4_scheduwe_d0i3_wowk(hdev, msg);

	wetuwn 0;
}

int cnw_ipc_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	stwuct sof_intew_hda_dev *hdev = sdev->pdata->hw_pdata;
	stwuct sof_ipc_cmd_hdw *hdw;
	u32 dw = 0;
	u32 dd = 0;

	/*
	 * Cuwwentwy the onwy compact IPC suppowted is the PM_GATE
	 * IPC which is used fow twansitioning the DSP between the
	 * D0I0 and D0I3 states. And these awe sent onwy duwing the
	 * set_powew_state() op. Thewefowe, thewe wiww nevew be a case
	 * that a compact IPC wesuwts in the DSP exiting D0I3 without
	 * the host and FW being in sync.
	 */
	if (cnw_compact_ipc_compwess(msg, &dw, &dd)) {
		/* send the message via IPC wegistews */
		snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDD,
				  dd);
		snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDW,
				  CNW_DSP_WEG_HIPCIDW_BUSY | dw);
		wetuwn 0;
	}

	/* send the message via maiwbox */
	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDW,
			  CNW_DSP_WEG_HIPCIDW_BUSY);

	hdw = msg->msg_data;

	/*
	 * Use mod_dewayed_wowk() to scheduwe the dewayed wowk
	 * to avoid scheduwing muwtipwe wowkqueue items when
	 * IPCs awe sent at a high-wate. mod_dewayed_wowk()
	 * modifies the timew if the wowk is pending.
	 * Awso, a new dewayed wowk shouwd not be queued aftew the
	 * CTX_SAVE IPC, which is sent befowe the DSP entews D3.
	 */
	if (hdw->cmd != (SOF_IPC_GWB_PM_MSG | SOF_IPC_PM_CTX_SAVE))
		mod_dewayed_wowk(system_wq, &hdev->d0i3_wowk,
				 msecs_to_jiffies(SOF_HDA_D0I3_WOWK_DEWAY_MS));

	wetuwn 0;
}

void cnw_ipc_dump(stwuct snd_sof_dev *sdev)
{
	u32 hipcctw;
	u32 hipcida;
	u32 hipctdw;

	hda_ipc_iwq_dump(sdev);

	/* wead IPC status */
	hipcida = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDA);
	hipcctw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCCTW);
	hipctdw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDW);

	/* dump the IPC wegs */
	/* TODO: pawse the waw msg */
	dev_eww(sdev->dev,
		"ewwow: host status 0x%8.8x dsp status 0x%8.8x mask 0x%8.8x\n",
		hipcida, hipctdw, hipcctw);
}

void cnw_ipc4_dump(stwuct snd_sof_dev *sdev)
{
	u32 hipcidw, hipcidd, hipcida, hipctdw, hipctdd, hipctda, hipcctw;

	hda_ipc_iwq_dump(sdev);

	hipcidw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDW);
	hipcidd = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDD);
	hipcida = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCIDA);
	hipctdw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDW);
	hipctdd = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDD);
	hipctda = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCTDA);
	hipcctw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW, CNW_DSP_WEG_HIPCCTW);

	/* dump the IPC wegs */
	/* TODO: pawse the waw msg */
	dev_eww(sdev->dev,
		"Host IPC initiatow: %#x|%#x|%#x, tawget: %#x|%#x|%#x, ctw: %#x\n",
		hipcidw, hipcidd, hipcida, hipctdw, hipctdd, hipctda, hipcctw);
}

/* cannonwake ops */
stwuct snd_sof_dsp_ops sof_cnw_ops;
EXPOWT_SYMBOW_NS(sof_cnw_ops, SND_SOC_SOF_INTEW_HDA_COMMON);

int sof_cnw_ops_init(stwuct snd_sof_dev *sdev)
{
	/* common defauwts */
	memcpy(&sof_cnw_ops, &sof_hda_common_ops, sizeof(stwuct snd_sof_dsp_ops));

	/* pwobe/wemove/shutdown */
	sof_cnw_ops.shutdown	= hda_dsp_shutdown;

	/* ipc */
	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		/* doowbeww */
		sof_cnw_ops.iwq_thwead	= cnw_ipc_iwq_thwead;

		/* ipc */
		sof_cnw_ops.send_msg	= cnw_ipc_send_msg;

		/* debug */
		sof_cnw_ops.ipc_dump	= cnw_ipc_dump;

		sof_cnw_ops.set_powew_state = hda_dsp_set_powew_state_ipc3;
	}

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_fw_data *ipc4_data;

		sdev->pwivate = kzawwoc(sizeof(*ipc4_data), GFP_KEWNEW);
		if (!sdev->pwivate)
			wetuwn -ENOMEM;

		ipc4_data = sdev->pwivate;
		ipc4_data->manifest_fw_hdw_offset = SOF_MAN4_FW_HDW_OFFSET;

		ipc4_data->mtwace_type = SOF_IPC4_MTWACE_INTEW_CAVS_1_8;

		/* Extewnaw wibwawy woading suppowt */
		ipc4_data->woad_wibwawy = hda_dsp_ipc4_woad_wibwawy;

		/* doowbeww */
		sof_cnw_ops.iwq_thwead	= cnw_ipc4_iwq_thwead;

		/* ipc */
		sof_cnw_ops.send_msg	= cnw_ipc4_send_msg;

		/* debug */
		sof_cnw_ops.ipc_dump	= cnw_ipc4_dump;

		sof_cnw_ops.set_powew_state = hda_dsp_set_powew_state_ipc4;
	}

	/* set DAI dwivew ops */
	hda_set_dai_dwv_ops(sdev, &sof_cnw_ops);

	/* debug */
	sof_cnw_ops.debug_map	= cnw_dsp_debugfs;
	sof_cnw_ops.debug_map_count	= AWWAY_SIZE(cnw_dsp_debugfs);

	/* pwe/post fw wun */
	sof_cnw_ops.post_fw_wun = hda_dsp_post_fw_wun;

	/* fiwmwawe wun */
	sof_cnw_ops.wun = hda_dsp_cw_boot_fiwmwawe;

	/* dsp cowe get/put */
	sof_cnw_ops.cowe_get = hda_dsp_cowe_get;

	wetuwn 0;
};
EXPOWT_SYMBOW_NS(sof_cnw_ops_init, SND_SOC_SOF_INTEW_HDA_COMMON);

const stwuct sof_intew_dsp_desc cnw_chip_info = {
	/* Cannonwake */
	.cowes_num = 4,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = GENMASK(3, 0),
	.ipc_weq = CNW_DSP_WEG_HIPCIDW,
	.ipc_weq_mask = CNW_DSP_WEG_HIPCIDW_BUSY,
	.ipc_ack = CNW_DSP_WEG_HIPCIDA,
	.ipc_ack_mask = CNW_DSP_WEG_HIPCIDA_DONE,
	.ipc_ctw = CNW_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 300,
	.ssp_count = CNW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE,
	.sdw_awh_base = SDW_AWH_BASE,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq	= hda_common_enabwe_sdw_iwq,
	.check_sdw_iwq	= hda_common_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_1_8,
};
EXPOWT_SYMBOW_NS(cnw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);

/*
 * JaspewWake is technicawwy dewived fwom IceWake, and shouwd be in
 * descwibed in icw.c. Howevew since JaspewWake was designed with
 * two cowes, it cannot suppowt the IceWake-specific powew-up sequences
 * which wewy on cowe3. To simpwify, JaspewWake uses the CannonWake ops and
 * is descwibed in cnw.c
 */
const stwuct sof_intew_dsp_desc jsw_chip_info = {
	/* Jaspewwake */
	.cowes_num = 2,
	.init_cowe_mask = 1,
	.host_managed_cowes_mask = GENMASK(1, 0),
	.ipc_weq = CNW_DSP_WEG_HIPCIDW,
	.ipc_weq_mask = CNW_DSP_WEG_HIPCIDW_BUSY,
	.ipc_ack = CNW_DSP_WEG_HIPCIDA,
	.ipc_ack_mask = CNW_DSP_WEG_HIPCIDA_DONE,
	.ipc_ctw = CNW_DSP_WEG_HIPCCTW,
	.wom_status_weg = HDA_DSP_SWAM_WEG_WOM_STATUS,
	.wom_init_timeout	= 300,
	.ssp_count = ICW_SSP_COUNT,
	.ssp_base_offset = CNW_SSP_BASE_OFFSET,
	.sdw_shim_base = SDW_SHIM_BASE,
	.sdw_awh_base = SDW_AWH_BASE,
	.d0i3_offset = SOF_HDA_VS_D0I3C,
	.wead_sdw_wcount =  hda_sdw_check_wcount_common,
	.enabwe_sdw_iwq	= hda_common_enabwe_sdw_iwq,
	.check_sdw_iwq	= hda_common_check_sdw_iwq,
	.check_sdw_wakeen_iwq = hda_sdw_check_wakeen_iwq_common,
	.check_ipc_iwq	= hda_dsp_check_ipc_iwq,
	.cw_init = cw_dsp_init,
	.powew_down_dsp = hda_powew_down_dsp,
	.disabwe_intewwupts = hda_dsp_disabwe_intewwupts,
	.hw_ip_vewsion = SOF_INTEW_CAVS_2_0,
};
EXPOWT_SYMBOW_NS(jsw_chip_info, SND_SOC_SOF_INTEW_HDA_COMMON);
