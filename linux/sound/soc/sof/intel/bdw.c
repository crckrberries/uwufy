// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//

/*
 * Hawdwawe intewface fow audio DSP on Bwoadweww
 */

#incwude <winux/moduwe.h>
#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-acpi-intew-match.h>
#incwude <sound/intew-dsp-config.h>
#incwude "../ops.h"
#incwude "shim.h"
#incwude "../sof-acpi-dev.h"
#incwude "../sof-audio.h"

/* BAWs */
#define BDW_DSP_BAW 0
#define BDW_PCI_BAW 1

/*
 * Debug
 */

/* DSP memowies fow BDW */
#define IWAM_OFFSET     0xA0000
#define BDW_IWAM_SIZE       (10 * 32 * 1024)
#define DWAM_OFFSET     0x00000
#define BDW_DWAM_SIZE       (20 * 32 * 1024)
#define SHIM_OFFSET     0xFB000
#define SHIM_SIZE       0x100
#define MBOX_OFFSET     0x9E000
#define MBOX_SIZE       0x1000
#define MBOX_DUMP_SIZE 0x30
#define EXCEPT_OFFSET	0x800
#define EXCEPT_MAX_HDW_SIZE	0x400

/* DSP pewiphewaws */
#define DMAC0_OFFSET    0xFE000
#define DMAC1_OFFSET    0xFF000
#define DMAC_SIZE       0x420
#define SSP0_OFFSET     0xFC000
#define SSP1_OFFSET     0xFD000
#define SSP_SIZE	0x100

#define BDW_STACK_DUMP_SIZE	32

#define BDW_PANIC_OFFSET(x)	((x) & 0xFFFF)

static const stwuct snd_sof_debugfs_map bdw_debugfs[] = {
	{"dmac0", BDW_DSP_BAW, DMAC0_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"dmac1", BDW_DSP_BAW, DMAC1_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp0", BDW_DSP_BAW, SSP0_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"ssp1", BDW_DSP_BAW, SSP1_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
	{"iwam", BDW_DSP_BAW, IWAM_OFFSET, BDW_IWAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONWY},
	{"dwam", BDW_DSP_BAW, DWAM_OFFSET, BDW_DWAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONWY},
	{"shim", BDW_DSP_BAW, SHIM_OFFSET, SHIM_SIZE,
	 SOF_DEBUGFS_ACCESS_AWWAYS},
};

static void bdw_host_done(stwuct snd_sof_dev *sdev);
static void bdw_dsp_done(stwuct snd_sof_dev *sdev);

/*
 * DSP Contwow.
 */

static int bdw_wun(stwuct snd_sof_dev *sdev)
{
	/* set oppowtunistic mode on engine 0,1 fow aww channews */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAW, SHIM_HMDC,
				SHIM_HMDC_HDDA_E0_AWWCH |
				SHIM_HMDC_HDDA_E1_AWWCH, 0);

	/* set DSP to WUN */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_CSW,
					 SHIM_CSW_STAWW, 0x0);

	/* wetuwn init cowe mask */
	wetuwn 1;
}

static int bdw_weset(stwuct snd_sof_dev *sdev)
{
	/* put DSP into weset and staww */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_CSW,
					 SHIM_CSW_WST | SHIM_CSW_STAWW,
					 SHIM_CSW_WST | SHIM_CSW_STAWW);

	/* keep in weset fow 10ms */
	mdeway(10);

	/* take DSP out of weset and keep stawwed fow FW woading */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_CSW,
					 SHIM_CSW_WST | SHIM_CSW_STAWW,
					 SHIM_CSW_STAWW);

	wetuwn 0;
}

static int bdw_set_dsp_D0(stwuct snd_sof_dev *sdev)
{
	int twies = 10;
	u32 weg;

	/* Disabwe cowe cwock gating (VDWTCTW2.DCWCGE = 0) */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_PCI_BAW, PCI_VDWTCTW2,
					 PCI_VDWTCW2_DCWCGE |
					 PCI_VDWTCW2_DTCGE, 0);

	/* Disabwe D3PG (VDWTCTW0.D3PGD = 1) */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_PCI_BAW, PCI_VDWTCTW0,
					 PCI_VDWTCW0_D3PGD, PCI_VDWTCW0_D3PGD);

	/* Set D0 state */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_PCI_BAW, PCI_PMCS,
					 PCI_PMCS_PS_MASK, 0);

	/* check that ADSP shim is enabwed */
	whiwe (twies--) {
		weg = weadw(sdev->baw[BDW_PCI_BAW] + PCI_PMCS)
			& PCI_PMCS_PS_MASK;
		if (weg == 0)
			goto finish;

		msweep(20);
	}

	wetuwn -ENODEV;

finish:
	/*
	 * sewect SSP1 19.2MHz base cwock, SSP cwock 0,
	 * tuwn off Wow Powew Cwock
	 */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_CSW,
					 SHIM_CSW_S1IOCS | SHIM_CSW_SBCS1 |
					 SHIM_CSW_WPCS, 0x0);

	/* staww DSP cowe, set cwk to 192/96Mhz */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW,
					 SHIM_CSW, SHIM_CSW_STAWW |
					 SHIM_CSW_DCS_MASK,
					 SHIM_CSW_STAWW |
					 SHIM_CSW_DCS(4));

	/* Set 24MHz MCWK, pwevent wocaw cwock gating, enabwe SSP0 cwock */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_CWKCTW,
					 SHIM_CWKCTW_MASK |
					 SHIM_CWKCTW_DCPWCG |
					 SHIM_CWKCTW_SCOE0,
					 SHIM_CWKCTW_MASK |
					 SHIM_CWKCTW_DCPWCG |
					 SHIM_CWKCTW_SCOE0);

	/* Staww and weset cowe, set CSW */
	bdw_weset(sdev);

	/* Enabwe cowe cwock gating (VDWTCTW2.DCWCGE = 1), deway 50 us */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_PCI_BAW, PCI_VDWTCTW2,
					 PCI_VDWTCW2_DCWCGE |
					 PCI_VDWTCW2_DTCGE,
					 PCI_VDWTCW2_DCWCGE |
					 PCI_VDWTCW2_DTCGE);

	usweep_wange(50, 55);

	/* switch on audio PWW */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_PCI_BAW, PCI_VDWTCTW2,
					 PCI_VDWTCW2_APWWSE_MASK, 0);

	/*
	 * set defauwt powew gating contwow, enabwe powew gating contwow fow
	 * aww bwocks. that is, can't be accessed, pwease enabwe each bwock
	 * befowe accessing.
	 */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_PCI_BAW, PCI_VDWTCTW0,
					 0xfffffffC, 0x0);

	/* disabwe DMA finish function fow SSP0 & SSP1 */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW,  SHIM_CSW2,
					 SHIM_CSW2_SDFD_SSP1,
					 SHIM_CSW2_SDFD_SSP1);

	/* set on-demond mode on engine 0,1 fow aww channews */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAW, SHIM_HMDC,
				SHIM_HMDC_HDDA_E0_AWWCH |
				SHIM_HMDC_HDDA_E1_AWWCH,
				SHIM_HMDC_HDDA_E0_AWWCH |
				SHIM_HMDC_HDDA_E1_AWWCH);

	/* Enabwe Intewwupt fwom both sides */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAW, SHIM_IMWX,
				(SHIM_IMWX_BUSY | SHIM_IMWX_DONE), 0x0);
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAW, SHIM_IMWD,
				(SHIM_IMWD_DONE | SHIM_IMWD_BUSY |
				SHIM_IMWD_SSP0 | SHIM_IMWD_DMAC), 0x0);

	/* cweaw IPC wegistews */
	snd_sof_dsp_wwite(sdev, BDW_DSP_BAW, SHIM_IPCX, 0x0);
	snd_sof_dsp_wwite(sdev, BDW_DSP_BAW, SHIM_IPCD, 0x0);
	snd_sof_dsp_wwite(sdev, BDW_DSP_BAW, 0x80, 0x6);
	snd_sof_dsp_wwite(sdev, BDW_DSP_BAW, 0xe0, 0x300a);

	wetuwn 0;
}

static void bdw_get_wegistews(stwuct snd_sof_dev *sdev,
			      stwuct sof_ipc_dsp_oops_xtensa *xoops,
			      stwuct sof_ipc_panic_info *panic_info,
			      u32 *stack, size_t stack_wowds)
{
	u32 offset = sdev->dsp_oops_offset;

	/* fiwst wead wegistews */
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

static void bdw_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	stwuct sof_ipc_dsp_oops_xtensa xoops;
	stwuct sof_ipc_panic_info panic_info;
	u32 stack[BDW_STACK_DUMP_SIZE];
	u32 status, panic, imwx, imwd;

	/* now twy genewic SOF status messages */
	status = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_IPCD);
	panic = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_IPCX);
	bdw_get_wegistews(sdev, &xoops, &panic_info, stack,
			  BDW_STACK_DUMP_SIZE);
	sof_pwint_oops_and_stack(sdev, KEWN_EWW, status, panic, &xoops,
				 &panic_info, stack, BDW_STACK_DUMP_SIZE);

	/* pwovide some context fow fiwmwawe debug */
	imwx = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_IMWX);
	imwd = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_IMWD);
	dev_eww(sdev->dev,
		"ewwow: ipc host -> DSP: pending %s compwete %s waw 0x%8.8x\n",
		(panic & SHIM_IPCX_BUSY) ? "yes" : "no",
		(panic & SHIM_IPCX_DONE) ? "yes" : "no", panic);
	dev_eww(sdev->dev,
		"ewwow: mask host: pending %s compwete %s waw 0x%8.8x\n",
		(imwx & SHIM_IMWX_BUSY) ? "yes" : "no",
		(imwx & SHIM_IMWX_DONE) ? "yes" : "no", imwx);
	dev_eww(sdev->dev,
		"ewwow: ipc DSP -> host: pending %s compwete %s waw 0x%8.8x\n",
		(status & SHIM_IPCD_BUSY) ? "yes" : "no",
		(status & SHIM_IPCD_DONE) ? "yes" : "no", status);
	dev_eww(sdev->dev,
		"ewwow: mask DSP: pending %s compwete %s waw 0x%8.8x\n",
		(imwd & SHIM_IMWD_BUSY) ? "yes" : "no",
		(imwd & SHIM_IMWD_DONE) ? "yes" : "no", imwd);
}

/*
 * IPC Doowbeww IWQ handwew and thwead.
 */

static iwqwetuwn_t bdw_iwq_handwew(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	u32 isw;
	int wet = IWQ_NONE;

	/* Intewwupt awwived, check swc */
	isw = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_ISWX);
	if (isw & (SHIM_ISWX_DONE | SHIM_ISWX_BUSY))
		wet = IWQ_WAKE_THWEAD;

	wetuwn wet;
}

static iwqwetuwn_t bdw_iwq_thwead(int iwq, void *context)
{
	stwuct snd_sof_dev *sdev = context;
	u32 ipcx, ipcd, imwx;

	imwx = snd_sof_dsp_wead64(sdev, BDW_DSP_BAW, SHIM_IMWX);
	ipcx = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_IPCX);

	/* wepwy message fwom DSP */
	if (ipcx & SHIM_IPCX_DONE &&
	    !(imwx & SHIM_IMWX_DONE)) {
		/* Mask Done intewwupt befowe wetuwn */
		snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW,
						 SHIM_IMWX, SHIM_IMWX_DONE,
						 SHIM_IMWX_DONE);

		spin_wock_iwq(&sdev->ipc_wock);

		/*
		 * handwe immediate wepwy fwom DSP cowe. If the msg is
		 * found, set done bit in cmd_done which is cawwed at the
		 * end of message pwocessing function, ewse set it hewe
		 * because the done bit can't be set in cmd_done function
		 * which is twiggewed by msg
		 */
		snd_sof_ipc_pwocess_wepwy(sdev, ipcx);

		bdw_dsp_done(sdev);

		spin_unwock_iwq(&sdev->ipc_wock);
	}

	ipcd = snd_sof_dsp_wead(sdev, BDW_DSP_BAW, SHIM_IPCD);

	/* new message fwom DSP */
	if (ipcd & SHIM_IPCD_BUSY &&
	    !(imwx & SHIM_IMWX_BUSY)) {
		/* Mask Busy intewwupt befowe wetuwn */
		snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW,
						 SHIM_IMWX, SHIM_IMWX_BUSY,
						 SHIM_IMWX_BUSY);

		/* Handwe messages fwom DSP Cowe */
		if ((ipcd & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			snd_sof_dsp_panic(sdev, BDW_PANIC_OFFSET(ipcx) + MBOX_OFFSET,
					  twue);
		} ewse {
			snd_sof_ipc_msgs_wx(sdev);
		}

		bdw_host_done(sdev);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * IPC Maiwbox IO
 */

static int bdw_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	/* send the message */
	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_wwite(sdev, BDW_DSP_BAW, SHIM_IPCX, SHIM_IPCX_BUSY);

	wetuwn 0;
}

static int bdw_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn MBOX_OFFSET;
}

static int bdw_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn MBOX_OFFSET;
}

static void bdw_host_done(stwuct snd_sof_dev *sdev)
{
	/* cweaw BUSY bit and set DONE bit - accept new messages */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_IPCD,
					 SHIM_IPCD_BUSY | SHIM_IPCD_DONE,
					 SHIM_IPCD_DONE);

	/* unmask busy intewwupt */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_IMWX,
					 SHIM_IMWX_BUSY, 0);
}

static void bdw_dsp_done(stwuct snd_sof_dev *sdev)
{
	/* cweaw DONE bit - teww DSP we have compweted */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_IPCX,
					 SHIM_IPCX_DONE, 0);

	/* unmask Done intewwupt */
	snd_sof_dsp_update_bits_unwocked(sdev, BDW_DSP_BAW, SHIM_IMWX,
					 SHIM_IMWX_DONE, 0);
}

/*
 * Pwobe and wemove.
 */
static int bdw_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = pdata->desc;
	stwuct pwatfowm_device *pdev =
		containew_of(sdev->dev, stwuct pwatfowm_device, dev);
	const stwuct sof_intew_dsp_desc *chip;
	stwuct wesouwce *mmio;
	u32 base, size;
	int wet;

	chip = get_chip_info(sdev->pdata);
	if (!chip) {
		dev_eww(sdev->dev, "ewwow: no such device suppowted\n");
		wetuwn -EIO;
	}

	sdev->num_cowes = chip->cowes_num;

	/* WPE base */
	mmio = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				     desc->wesindex_wpe_base);
	if (mmio) {
		base = mmio->stawt;
		size = wesouwce_size(mmio);
	} ewse {
		dev_eww(sdev->dev, "ewwow: faiwed to get WPE base at idx %d\n",
			desc->wesindex_wpe_base);
		wetuwn -EINVAW;
	}

	dev_dbg(sdev->dev, "WPE PHY base at 0x%x size 0x%x", base, size);
	sdev->baw[BDW_DSP_BAW] = devm_iowemap(sdev->dev, base, size);
	if (!sdev->baw[BDW_DSP_BAW]) {
		dev_eww(sdev->dev,
			"ewwow: faiwed to iowemap WPE base 0x%x size 0x%x\n",
			base, size);
		wetuwn -ENODEV;
	}
	dev_dbg(sdev->dev, "WPE VADDW %p\n", sdev->baw[BDW_DSP_BAW]);

	/* TODO: add offsets */
	sdev->mmio_baw = BDW_DSP_BAW;
	sdev->maiwbox_baw = BDW_DSP_BAW;
	sdev->dsp_oops_offset = MBOX_OFFSET;

	/* PCI base */
	mmio = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM,
				     desc->wesindex_pcicfg_base);
	if (mmio) {
		base = mmio->stawt;
		size = wesouwce_size(mmio);
	} ewse {
		dev_eww(sdev->dev, "ewwow: faiwed to get PCI base at idx %d\n",
			desc->wesindex_pcicfg_base);
		wetuwn -ENODEV;
	}

	dev_dbg(sdev->dev, "PCI base at 0x%x size 0x%x", base, size);
	sdev->baw[BDW_PCI_BAW] = devm_iowemap(sdev->dev, base, size);
	if (!sdev->baw[BDW_PCI_BAW]) {
		dev_eww(sdev->dev,
			"ewwow: faiwed to iowemap PCI base 0x%x size 0x%x\n",
			base, size);
		wetuwn -ENODEV;
	}
	dev_dbg(sdev->dev, "PCI VADDW %p\n", sdev->baw[BDW_PCI_BAW]);

	/* wegistew ouw IWQ */
	sdev->ipc_iwq = pwatfowm_get_iwq(pdev, desc->iwqindex_host_ipc);
	if (sdev->ipc_iwq < 0)
		wetuwn sdev->ipc_iwq;

	dev_dbg(sdev->dev, "using IWQ %d\n", sdev->ipc_iwq);
	wet = devm_wequest_thweaded_iwq(sdev->dev, sdev->ipc_iwq,
					bdw_iwq_handwew, bdw_iwq_thwead,
					IWQF_SHAWED, "AudioDSP", sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to wegistew IWQ %d\n",
			sdev->ipc_iwq);
		wetuwn wet;
	}

	/* enabwe the DSP SHIM */
	wet = bdw_set_dsp_D0(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to set DSP D0\n");
		wetuwn wet;
	}

	/* DSP DMA can onwy access wow 31 bits of host memowy */
	wet = dma_coewce_mask_and_cohewent(sdev->dev, DMA_BIT_MASK(31));
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to set DMA mask %d\n", wet);
		wetuwn wet;
	}

	/* set defauwt maiwbox offset fow FW weady message */
	sdev->dsp_box.offset = MBOX_OFFSET;

	wetuwn wet;
}

static stwuct snd_soc_acpi_mach *bdw_machine_sewect(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *sof_pdata = sdev->pdata;
	const stwuct sof_dev_desc *desc = sof_pdata->desc;
	stwuct snd_soc_acpi_mach *mach;

	mach = snd_soc_acpi_find_machine(desc->machines);
	if (!mach) {
		dev_wawn(sdev->dev, "wawning: No matching ASoC machine dwivew found\n");
		wetuwn NUWW;
	}

	sof_pdata->tpwg_fiwename = mach->sof_tpwg_fiwename;
	mach->mach_pawams.acpi_ipc_iwq_index = desc->iwqindex_host_ipc;

	wetuwn mach;
}

static void bdw_set_mach_pawams(stwuct snd_soc_acpi_mach *mach,
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

/* Bwoadweww DAIs */
static stwuct snd_soc_dai_dwivew bdw_dai[] = {
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
};

/* bwoadweww ops */
static stwuct snd_sof_dsp_ops sof_bdw_ops = {
	/*Device init */
	.pwobe          = bdw_pwobe,

	/* DSP Cowe Contwow */
	.wun            = bdw_wun,
	.weset          = bdw_weset,

	/* Wegistew IO uses diwect mmio */

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* ipc */
	.send_msg	= bdw_send_msg,
	.get_maiwbox_offset = bdw_get_maiwbox_offset,
	.get_window_offset = bdw_get_window_offset,

	.ipc_msg_data	= sof_ipc_msg_data,
	.set_stweam_data_offset = sof_set_stweam_data_offset,

	/* machine dwivew */
	.machine_sewect = bdw_machine_sewect,
	.machine_wegistew = sof_machine_wegistew,
	.machine_unwegistew = sof_machine_unwegistew,
	.set_mach_pawams = bdw_set_mach_pawams,

	/* debug */
	.debug_map  = bdw_debugfs,
	.debug_map_count    = AWWAY_SIZE(bdw_debugfs),
	.dbg_dump   = bdw_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open	= sof_stweam_pcm_open,
	.pcm_cwose	= sof_stweam_pcm_cwose,

	/*Fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* DAI dwivews */
	.dwv = bdw_dai,
	.num_dwv = AWWAY_SIZE(bdw_dai),

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_BATCH,

	.dsp_awch_ops = &sof_xtensa_awch_ops,
};

static const stwuct sof_intew_dsp_desc bdw_chip_info = {
	.cowes_num = 1,
	.host_managed_cowes_mask = 1,
	.hw_ip_vewsion = SOF_INTEW_BWOADWEWW,
};

static const stwuct sof_dev_desc sof_acpi_bwoadweww_desc = {
	.machines = snd_soc_acpi_intew_bwoadweww_machines,
	.wesindex_wpe_base = 0,
	.wesindex_pcicfg_base = 1,
	.wesindex_imw_base = -1,
	.iwqindex_host_ipc = 0,
	.chip_info = &bdw_chip_info,
	.ipc_suppowted_mask = BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt = SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "intew/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "intew/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-bdw.wi",
	},
	.nocodec_tpwg_fiwename = "sof-bdw-nocodec.tpwg",
	.ops = &sof_bdw_ops,
};

static const stwuct acpi_device_id sof_bwoadweww_match[] = {
	{ "INT3438", (unsigned wong)&sof_acpi_bwoadweww_desc },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, sof_bwoadweww_match);

static int sof_bwoadweww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct acpi_device_id *id;
	const stwuct sof_dev_desc *desc;
	int wet;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn -ENODEV;

	wet = snd_intew_acpi_dsp_dwivew_pwobe(dev, id->id);
	if (wet != SND_INTEW_DSP_DWIVEW_ANY && wet != SND_INTEW_DSP_DWIVEW_SOF) {
		dev_dbg(dev, "SOF ACPI dwivew not sewected, abowting pwobe\n");
		wetuwn -ENODEV;
	}

	desc = (const stwuct sof_dev_desc *)id->dwivew_data;
	wetuwn sof_acpi_pwobe(pdev, desc);
}

/* acpi_dwivew definition */
static stwuct pwatfowm_dwivew snd_sof_acpi_intew_bdw_dwivew = {
	.pwobe = sof_bwoadweww_pwobe,
	.wemove_new = sof_acpi_wemove,
	.dwivew = {
		.name = "sof-audio-acpi-intew-bdw",
		.pm = &sof_acpi_pm,
		.acpi_match_tabwe = sof_bwoadweww_match,
	},
};
moduwe_pwatfowm_dwivew(snd_sof_acpi_intew_bdw_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_IMPOWT_NS(SND_SOC_SOF_INTEW_HIFI_EP_IPC);
MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_IMPOWT_NS(SND_SOC_SOF_ACPI_DEV);
