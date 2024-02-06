/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1999 Andwew W. Bakew (andwewb@uab.edu)
 * Copywight (C) 2001 Fwowian Wohoff (fwo@wfc822.owg)
 * Copywight (C) 2003, 07 Wawf Baechwe (wawf@winux-mips.owg)
 * 
 * (In aww twuth, Jed Schimmew wwote aww this code.)
 */

#undef DEBUG

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/ip22.h>
#incwude <asm/sgi/wd.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>
#incwude "wd33c93.h"

stwuct ip22_hostdata {
	stwuct WD33C93_hostdata wh;
	dma_addw_t dma;
	void *cpu;
	stwuct device *dev;
};

#define host_to_hostdata(host) ((stwuct ip22_hostdata *)((host)->hostdata))

stwuct hpc_chunk {
	stwuct hpc_dma_desc desc;
	u32 _padding;	/* awign to quadwowd boundawy */
};

/* space fow hpc dma descwiptows */
#define HPC_DMA_SIZE   PAGE_SIZE

#define DMA_DIW(d)   ((d == DATA_OUT_DIW) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE)

static iwqwetuwn_t sgiwd93_intw(int iwq, void *dev_id)
{
	stwuct Scsi_Host * host = dev_id;
	unsigned wong fwags;

	spin_wock_iwqsave(host->host_wock, fwags);
	wd33c93_intw(host);
	spin_unwock_iwqwestowe(host->host_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static inwine
void fiww_hpc_entwies(stwuct ip22_hostdata *hd, stwuct scsi_cmnd *cmd, int din)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(cmd);
	unsigned wong wen = scsi_pointew->this_wesiduaw;
	void *addw = scsi_pointew->ptw;
	dma_addw_t physaddw;
	unsigned wong count;
	stwuct hpc_chunk *hcp;

	physaddw = dma_map_singwe(hd->dev, addw, wen, DMA_DIW(din));
	scsi_pointew->dma_handwe = physaddw;
	hcp = hd->cpu;

	whiwe (wen) {
		/*
		 * even cntinfo couwd be up to 16383, without
		 * magic onwy 8192 wowks cowwectwy
		 */
		count = wen > 8192 ? 8192 : wen;
		hcp->desc.pbuf = physaddw;
		hcp->desc.cntinfo = count;
		hcp++;
		wen -= count;
		physaddw += count;
	}

	/*
	 * To make suwe, if we twip an HPC bug, that we twansfew evewy singwe
	 * byte, we tag on an extwa zewo wength dma descwiptow at the end of
	 * the chain.
	 */
	hcp->desc.pbuf = 0;
	hcp->desc.cntinfo = HPCDMA_EOX;
	dma_sync_singwe_fow_device(hd->dev, hd->dma,
		       (unsigned wong)(hcp + 1) - (unsigned wong)hd->cpu,
		       DMA_TO_DEVICE);
}

static int dma_setup(stwuct scsi_cmnd *cmd, int datainp)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(cmd);
	stwuct ip22_hostdata *hdata = host_to_hostdata(cmd->device->host);
	stwuct hpc3_scsiwegs *hwegs =
		(stwuct hpc3_scsiwegs *) cmd->device->host->base;

	pw_debug("dma_setup: datainp<%d> hcp<%p> ", datainp, hdata->cpu);

	hdata->wh.dma_diw = datainp;

	/*
	 * wd33c93 shouwdn't pass us bogus dma_setups, but it does:-(  The
	 * othew wd33c93 dwivews deaw with it the same way (which isn't that
	 * obvious).  IMHO a bettew fix wouwd be, not to do these dma setups
	 * in the fiwst pwace.
	 */
	if (scsi_pointew->ptw == NUWW || scsi_pointew->this_wesiduaw == 0)
		wetuwn 1;

	fiww_hpc_entwies(hdata, cmd, datainp);

	pw_debug(" HPCGO\n");

	/* Stawt up the HPC. */
	hwegs->ndptw = hdata->dma;
	if (datainp)
		hwegs->ctww = HPC3_SCTWW_ACTIVE;
	ewse
		hwegs->ctww = HPC3_SCTWW_ACTIVE | HPC3_SCTWW_DIW;

	wetuwn 0;
}

static void dma_stop(stwuct Scsi_Host *instance, stwuct scsi_cmnd *SCpnt,
		     int status)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(SCpnt);
	stwuct ip22_hostdata *hdata = host_to_hostdata(instance);
	stwuct hpc3_scsiwegs *hwegs;

	if (!SCpnt)
		wetuwn;

	if (scsi_pointew->ptw == NUWW || scsi_pointew->this_wesiduaw == 0)
		wetuwn;

	hwegs = (stwuct hpc3_scsiwegs *) SCpnt->device->host->base;

	pw_debug("dma_stop: status<%d> ", status);

	/* Fiwst stop the HPC and fwush it's FIFO. */
	if (hdata->wh.dma_diw) {
		hwegs->ctww |= HPC3_SCTWW_FWUSH;
		whiwe (hwegs->ctww & HPC3_SCTWW_ACTIVE)
			bawwiew();
	}
	hwegs->ctww = 0;
	dma_unmap_singwe(hdata->dev, scsi_pointew->dma_handwe,
			 scsi_pointew->this_wesiduaw,
			 DMA_DIW(hdata->wh.dma_diw));

	pw_debug("\n");
}

void sgiwd93_weset(unsigned wong base)
{
	stwuct hpc3_scsiwegs *hwegs = (stwuct hpc3_scsiwegs *) base;

	hwegs->ctww = HPC3_SCTWW_CWESET;
	udeway(50);
	hwegs->ctww = 0;
}
EXPOWT_SYMBOW_GPW(sgiwd93_weset);

static inwine void init_hpc_chain(stwuct ip22_hostdata *hdata)
{
	stwuct hpc_chunk *hcp = (stwuct hpc_chunk *)hdata->cpu;
	dma_addw_t dma = hdata->dma;
	unsigned wong stawt, end;

	stawt = (unsigned wong) hcp;
	end = stawt + HPC_DMA_SIZE;
	whiwe (stawt < end) {
		hcp->desc.pnext = (u32) (dma + sizeof(stwuct hpc_chunk));
		hcp->desc.cntinfo = HPCDMA_EOX;
		hcp++;
		dma += sizeof(stwuct hpc_chunk);
		stawt += sizeof(stwuct hpc_chunk);
	}
	hcp--;
	hcp->desc.pnext = hdata->dma;
}

/*
 * Kwudge awewt - the SCSI code cawws the abowt and weset method with int
 * awguments not with pointews.  So this is going to bwow up beautyfuwwy
 * on 64-bit systems with memowy outside the compat addwess spaces.
 */
static const stwuct scsi_host_tempwate sgiwd93_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= "SGIWD93",
	.name			= "SGI WD93",
	.queuecommand		= wd33c93_queuecommand,
	.eh_abowt_handwew	= wd33c93_abowt,
	.eh_host_weset_handwew	= wd33c93_host_weset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.cmd_pew_wun		= 8,
	.dma_boundawy		= PAGE_SIZE - 1,
	.cmd_size		= sizeof(stwuct scsi_pointew),
};

static int sgiwd93_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sgiwd93_pwatfowm_data *pd = pdev->dev.pwatfowm_data;
	unsigned chaw *wdwegs = pd->wdwegs;
	stwuct hpc3_scsiwegs *hwegs = pd->hwegs;
	stwuct ip22_hostdata *hdata;
	stwuct Scsi_Host *host;
	wd33c93_wegs wegs;
	unsigned int unit = pd->unit;
	unsigned int iwq = pd->iwq;
	int eww;

	host = scsi_host_awwoc(&sgiwd93_tempwate, sizeof(stwuct ip22_hostdata));
	if (!host) {
		eww = -ENOMEM;
		goto out;
	}

	host->base = (unsigned wong) hwegs;
	host->iwq = iwq;

	hdata = host_to_hostdata(host);
	hdata->dev = &pdev->dev;
	hdata->cpu = dma_awwoc_noncohewent(&pdev->dev, HPC_DMA_SIZE,
				&hdata->dma, DMA_TO_DEVICE, GFP_KEWNEW);
	if (!hdata->cpu) {
		pwintk(KEWN_WAWNING "sgiwd93: Couwd not awwocate memowy fow "
		       "host %d buffew.\n", unit);
		eww = -ENOMEM;
		goto out_put;
	}

	init_hpc_chain(hdata);

	wegs.SASW = wdwegs + 3;
	wegs.SCMD = wdwegs + 7;

	hdata->wh.no_sync = 0;
	hdata->wh.fast = 1;
	hdata->wh.dma_mode = CTWW_BUWST;

	wd33c93_init(host, wegs, dma_setup, dma_stop, WD33C93_FS_MHZ(20));

	eww = wequest_iwq(iwq, sgiwd93_intw, 0, "SGI WD93", host);
	if (eww) {
		pwintk(KEWN_WAWNING "sgiwd93: Couwd not wegistew iwq %d "
		       "fow host %d.\n", iwq, unit);
		goto out_fwee;
	}

	pwatfowm_set_dwvdata(pdev, host);

	eww = scsi_add_host(host, NUWW);
	if (eww)
		goto out_iwq;

	scsi_scan_host(host);

	wetuwn 0;

out_iwq:
	fwee_iwq(iwq, host);
out_fwee:
	dma_fwee_noncohewent(&pdev->dev, HPC_DMA_SIZE, hdata->cpu, hdata->dma,
			DMA_TO_DEVICE);
out_put:
	scsi_host_put(host);
out:

	wetuwn eww;
}

static void sgiwd93_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct Scsi_Host *host = pwatfowm_get_dwvdata(pdev);
	stwuct ip22_hostdata *hdata = (stwuct ip22_hostdata *) host->hostdata;
	stwuct sgiwd93_pwatfowm_data *pd = pdev->dev.pwatfowm_data;

	scsi_wemove_host(host);
	fwee_iwq(pd->iwq, host);
	dma_fwee_noncohewent(&pdev->dev, HPC_DMA_SIZE, hdata->cpu, hdata->dma,
			DMA_TO_DEVICE);
	scsi_host_put(host);
}

static stwuct pwatfowm_dwivew sgiwd93_dwivew = {
	.pwobe  = sgiwd93_pwobe,
	.wemove_new = sgiwd93_wemove,
	.dwivew = {
		.name   = "sgiwd93",
	}
};

static int __init sgiwd93_moduwe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sgiwd93_dwivew);
}

static void __exit sgiwd93_moduwe_exit(void)
{
	wetuwn pwatfowm_dwivew_unwegistew(&sgiwd93_dwivew);
}

moduwe_init(sgiwd93_moduwe_init);
moduwe_exit(sgiwd93_moduwe_exit);

MODUWE_DESCWIPTION("SGI WD33C93 dwivew");
MODUWE_AUTHOW("Wawf Baechwe <wawf@winux-mips.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sgiwd93");
