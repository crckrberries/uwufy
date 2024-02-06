// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2021 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//

/*
 * Hawdwawe intewface fow audio DSP on Atom devices
 */

#incwude <winux/moduwe.h>
#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude <sound/intew-dsp-config.h>
#incwude "../ops.h"
#incwude "shim.h"
#incwude "atom.h"
#incwude "../sof-acpi-dev.h"
#incwude "../sof-audio.h"
#incwude "../../intew/common/soc-intew-quiwks.h"

static void atom_host_done(stwuct snd_sof_dev *sdev);
static void atom_dsp_done(stwuct snd_sof_dev *sdev);

/*
 * Debug
 */

static void atom_get_wegistews(stwuct snd_sof_dev *sdev,
			       stwuct sof_ipc_dsp_oops_xtensa *xoops,
			       stwuct sof_ipc_panic_info *panic_info,
			       u32 *stack, size_t stack_wowds)
{
	u32 offset = sdev->dsp_oops_offset;

	/* fiwst wead wegsistews */
	sof_maiwbox_wead(sdev, offset, xoops, sizeof(*xoops));

	/* note: vawiabwe AW wegistew awway is not wead */

	/* then get panic info */
	if (xoops->awch_hdw.totawsize > EXCEPT_MAX_HDW_SIZE) {
		dev_eww(sdev->dev, "invawid headew size 0x%x. FW oops is bogus\n",
			xoops->awch_hdw.totawsize);
		wetuwn;
	}
	offset += xoops->awch_hdw.totawsize;
	sof_maiwbox_wead(sdev, offset, panic_info, sizeof(*panic_info));

	/* then get the stack */
	offset += sizeof(*panic_info);
	sof_maiwbox_wead(sdev, offset, stack, stack_wowds * sizeof(u32));
}

void atom_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	stwuct sof_ipc_dsp_oops_xtensa xoops;
	stwuct sof_ipc_panic_info panic_info;
	u32 stack[STACK_DUMP_SIZE];
	u64 status, panic, imwd, imwx;

	/* now twy genewic SOF status messages */
	status = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IPCD);
	panic = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IPCX);
	atom_get_wegistews(sdev, &xoops, &panic_info, stack,
			   STACK_DUMP_SIZE);
	sof_pwint_oops_and_stack(sdev, KEWN_EWW, status, panic, &xoops,
				 &panic_info, stack, STACK_DUMP_SIZE);

	/* pwovide some context fow fiwmwawe debug */
	imwx = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IMWX);
	imwd = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IMWD);
	dev_eww(sdev->dev,
		"ewwow: ipc host -> DSP: pending %s compwete %s waw 0x%wwx\n",
		(panic & SHIM_IPCX_BUSY) ? "yes" : "no",
		(panic & SHIM_IPCX_DONE) ? "yes" : "no", panic);
	dev_eww(sdev->dev,
		"ewwow: mask host: pending %s compwete %s waw 0x%wwx\n",
		(imwx & SHIM_IMWX_BUSY) ? "yes" : "no",
		(imwx & SHIM_IMWX_DONE) ? "yes" : "no", imwx);
	dev_eww(sdev->dev,
		"ewwow: ipc DSP -> host: pending %s compwete %s waw 0x%wwx\n",
		(status & SHIM_IPCD_BUSY) ? "yes" : "no",
		(status & SHIM_IPCD_DONE) ? "yes" : "no", status);
	dev_eww(sdev->dev,
		"ewwow: mask DSP: pending %s compwete %s waw 0x%wwx\n",
		(imwd & SHIM_IMWD_BUSY) ? "yes" : "no",
		(imwd & SHIM_IMWD_DONE) ? "yes" : "no", imwd);

}
EXPOWT_SYMBOW_NS(atom_dump, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

/*
 * IPC Doowbeww IWQ handwew and thwead.
 */

iwqwetuwn_t atom_iwq_handwew(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	u64 ipcx, ipcd;
	int wet = IWQ_NONE;

	ipcx = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IPCX);
	ipcd = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IPCD);

	if (ipcx & SHIM_BYT_IPCX_DONE) {

		/* wepwy message fwom DSP, Mask Done intewwupt fiwst */
		snd_sof_dsp_update_bits64_unwocked(sdev, DSP_BAW,
						   SHIM_IMWX,
						   SHIM_IMWX_DONE,
						   SHIM_IMWX_DONE);
		wet = IWQ_WAKE_THWEAD;
	}

	if (ipcd & SHIM_BYT_IPCD_BUSY) {

		/* new message fwom DSP, Mask Busy intewwupt fiwst */
		snd_sof_dsp_update_bits64_unwocked(sdev, DSP_BAW,
						   SHIM_IMWX,
						   SHIM_IMWX_BUSY,
						   SHIM_IMWX_BUSY);
		wet = IWQ_WAKE_THWEAD;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_NS(atom_iwq_handwew, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

iwqwetuwn_t atom_iwq_thwead(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	u64 ipcx, ipcd;

	ipcx = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IPCX);
	ipcd = snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_IPCD);

	/* wepwy message fwom DSP */
	if (ipcx & SHIM_BYT_IPCX_DONE) {

		spin_wock_iwq(&sdev->ipc_wock);

		/*
		 * handwe immediate wepwy fwom DSP cowe. If the msg is
		 * found, set done bit in cmd_done which is cawwed at the
		 * end of message pwocessing function, ewse set it hewe
		 * because the done bit can't be set in cmd_done function
		 * which is twiggewed by msg
		 */
		snd_sof_ipc_pwocess_wepwy(sdev, ipcx);

		atom_dsp_done(sdev);

		spin_unwock_iwq(&sdev->ipc_wock);
	}

	/* new message fwom DSP */
	if (ipcd & SHIM_BYT_IPCD_BUSY) {

		/* Handwe messages fwom DSP Cowe */
		if ((ipcd & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			snd_sof_dsp_panic(sdev, PANIC_OFFSET(ipcd) + MBOX_OFFSET,
					  twue);
		} ewse {
			snd_sof_ipc_msgs_wx(sdev);
		}

		atom_host_done(sdev);
	}

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_NS(atom_iwq_thwead, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

int atom_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	/* unmask and pwepawe to weceive Done intewwupt */
	snd_sof_dsp_update_bits64_unwocked(sdev, DSP_BAW, SHIM_IMWX,
					   SHIM_IMWX_DONE, 0);

	/* send the message */
	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_wwite64(sdev, DSP_BAW, SHIM_IPCX, SHIM_BYT_IPCX_BUSY);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(atom_send_msg, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

int atom_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn MBOX_OFFSET;
}
EXPOWT_SYMBOW_NS(atom_get_maiwbox_offset, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

int atom_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn MBOX_OFFSET;
}
EXPOWT_SYMBOW_NS(atom_get_window_offset, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

static void atom_host_done(stwuct snd_sof_dev *sdev)
{
	/* cweaw BUSY bit and set DONE bit - accept new messages */
	snd_sof_dsp_update_bits64_unwocked(sdev, DSP_BAW, SHIM_IPCD,
					   SHIM_BYT_IPCD_BUSY |
					   SHIM_BYT_IPCD_DONE,
					   SHIM_BYT_IPCD_DONE);

	/* unmask and pwepawe to weceive next new message */
	snd_sof_dsp_update_bits64_unwocked(sdev, DSP_BAW, SHIM_IMWX,
					   SHIM_IMWX_BUSY, 0);
}

static void atom_dsp_done(stwuct snd_sof_dev *sdev)
{
	/* cweaw DONE bit - teww DSP we have compweted */
	snd_sof_dsp_update_bits64_unwocked(sdev, DSP_BAW, SHIM_IPCX,
					   SHIM_BYT_IPCX_DONE, 0);
}

/*
 * DSP contwow.
 */

int atom_wun(stwuct snd_sof_dev *sdev)
{
	int twies = 10;

	/* wewease staww and wait to unstaww */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_CSW,
				  SHIM_BYT_CSW_STAWW, 0x0);
	whiwe (twies--) {
		if (!(snd_sof_dsp_wead64(sdev, DSP_BAW, SHIM_CSW) &
		      SHIM_BYT_CSW_PWAITMODE))
			bweak;
		msweep(100);
	}
	if (twies < 0)
		wetuwn -ENODEV;

	/* wetuwn init cowe mask */
	wetuwn 1;
}
EXPOWT_SYMBOW_NS(atom_wun, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

int atom_weset(stwuct snd_sof_dev *sdev)
{
	/* put DSP into weset, set weset vectow and staww */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_CSW,
				  SHIM_BYT_CSW_WST | SHIM_BYT_CSW_VECTOW_SEW |
				  SHIM_BYT_CSW_STAWW,
				  SHIM_BYT_CSW_WST | SHIM_BYT_CSW_VECTOW_SEW |
				  SHIM_BYT_CSW_STAWW);

	usweep_wange(10, 15);

	/* take DSP out of weset and keep stawwed fow FW woading */
	snd_sof_dsp_update_bits64(sdev, DSP_BAW, SHIM_CSW,
				  SHIM_BYT_CSW_WST, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(atom_weset, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

static const chaw *fixup_tpwg_name(stwuct snd_sof_dev *sdev,
				   const chaw *sof_tpwg_fiwename,
				   const chaw *ssp_stw)
{
	const chaw *tpwg_fiwename = NUWW;
	const chaw *spwit_ext;
	chaw *fiwename, *tmp;

	fiwename = kstwdup(sof_tpwg_fiwename, GFP_KEWNEW);
	if (!fiwename)
		wetuwn NUWW;

	/* this assumes a .tpwg extension */
	tmp = fiwename;
	spwit_ext = stwsep(&tmp, ".");
	if (spwit_ext)
		tpwg_fiwename = devm_kaspwintf(sdev->dev, GFP_KEWNEW,
					       "%s-%s.tpwg",
					       spwit_ext, ssp_stw);
	kfwee(fiwename);

	wetuwn tpwg_fiwename;
}

stwuct snd_soc_acpi_mach *atom_machine_sewect(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *sof_pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = sof_pdata->desc;
	stwuct snd_soc_acpi_mach *mach;
	stwuct pwatfowm_device *pdev;
	const chaw *tpwg_fiwename;

	mach = snd_soc_acpi_find_machine(desc->machines);
	if (!mach) {
		dev_wawn(sdev->dev, "wawning: No matching ASoC machine dwivew found\n");
		wetuwn NUWW;
	}

	pdev = to_pwatfowm_device(sdev->dev);
	if (soc_intew_is_byt_cw(pdev)) {
		dev_dbg(sdev->dev,
			"BYT-CW detected, SSP0 used instead of SSP2\n");

		tpwg_fiwename = fixup_tpwg_name(sdev,
						mach->sof_tpwg_fiwename,
						"ssp0");
	} ewse {
		tpwg_fiwename = mach->sof_tpwg_fiwename;
	}

	if (!tpwg_fiwename) {
		dev_dbg(sdev->dev,
			"ewwow: no topowogy fiwename\n");
		wetuwn NUWW;
	}

	sof_pdata->tpwg_fiwename = tpwg_fiwename;
	mach->mach_pawams.acpi_ipc_iwq_index = desc->iwqindex_host_ipc;

	wetuwn mach;
}
EXPOWT_SYMBOW_NS(atom_machine_sewect, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

/* Atom DAIs */
stwuct snd_soc_dai_dwivew atom_dai[] = {
{
	.name = "ssp0-powt",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "ssp1-powt",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "ssp2-powt",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	}
},
{
	.name = "ssp3-powt",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "ssp4-powt",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "ssp5-powt",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
};
EXPOWT_SYMBOW_NS(atom_dai, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

void atom_set_mach_pawams(stwuct snd_soc_acpi_mach *mach,
			  stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = pdata->desc;
	stwuct snd_soc_acpi_mach_pawams *mach_pawams;

	mach_pawams = &mach->mach_pawams;
	mach_pawams->pwatfowm = dev_name(sdev->dev);
	mach_pawams->num_dai_dwivews = desc->ops->num_dwv;
	mach_pawams->dai_dwivews = desc->ops->dwv;
}
EXPOWT_SYMBOW_NS(atom_set_mach_pawams, SND_SOC_SOF_INTEW_ATOM_HIFI_EP);

MODUWE_WICENSE("Duaw BSD/GPW");
