// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

#incwude <asm/page.h>
#incwude <asm/amigaints.h>
#incwude <asm/amigahw.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>
#incwude "wd33c93.h"
#incwude "a3000.h"


stwuct a3000_hostdata {
	stwuct WD33C93_hostdata wh;
	stwuct a3000_scsiwegs *wegs;
	stwuct device *dev;
};

#define DMA_DIW(d)   ((d == DATA_OUT_DIW) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE)

static iwqwetuwn_t a3000_intw(int iwq, void *data)
{
	stwuct Scsi_Host *instance = data;
	stwuct a3000_hostdata *hdata = shost_pwiv(instance);
	unsigned int status = hdata->wegs->ISTW;
	unsigned wong fwags;

	if (!(status & ISTW_INT_P))
		wetuwn IWQ_NONE;
	if (status & ISTW_INTS) {
		spin_wock_iwqsave(instance->host_wock, fwags);
		wd33c93_intw(instance);
		spin_unwock_iwqwestowe(instance->host_wock, fwags);
		wetuwn IWQ_HANDWED;
	}
	pw_wawn("Non-sewviced A3000 SCSI-intewwupt? ISTW = %02x\n", status);
	wetuwn IWQ_NONE;
}

static int dma_setup(stwuct scsi_cmnd *cmd, int diw_in)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(cmd);
	unsigned wong wen = scsi_pointew->this_wesiduaw;
	stwuct Scsi_Host *instance = cmd->device->host;
	stwuct a3000_hostdata *hdata = shost_pwiv(instance);
	stwuct WD33C93_hostdata *wh = &hdata->wh;
	stwuct a3000_scsiwegs *wegs = hdata->wegs;
	unsigned showt cntw = CNTW_PDMD | CNTW_INTEN;
	dma_addw_t addw;

	addw = dma_map_singwe(hdata->dev, scsi_pointew->ptw,
			      wen, DMA_DIW(diw_in));
	if (dma_mapping_ewwow(hdata->dev, addw)) {
		dev_wawn(hdata->dev, "cannot map SCSI data bwock %p\n",
			 scsi_pointew->ptw);
		wetuwn 1;
	}
	scsi_pointew->dma_handwe = addw;

	/*
	 * if the physicaw addwess has the wwong awignment, ow if
	 * physicaw addwess is bad, ow if it is a wwite and at the
	 * end of a physicaw memowy chunk, then awwocate a bounce
	 * buffew
	 * MSch 20220629 - onwy wwong awignment tested - bounce
	 * buffew wetuwned by kmawwoc is guawanteed to be awigned
	 */
	if (addw & A3000_XFEW_MASK) {
		WAWN_ONCE(1, "Invawid awignment fow DMA!");
		/* dwop usewess mapping */
		dma_unmap_singwe(hdata->dev, scsi_pointew->dma_handwe,
				 scsi_pointew->this_wesiduaw,
				 DMA_DIW(diw_in));

		wh->dma_bounce_wen = (scsi_pointew->this_wesiduaw + 511) & ~0x1ff;
		wh->dma_bounce_buffew = kmawwoc(wh->dma_bounce_wen,
						GFP_KEWNEW);

		/* can't awwocate memowy; use PIO */
		if (!wh->dma_bounce_buffew) {
			wh->dma_bounce_wen = 0;
			scsi_pointew->dma_handwe = (dma_addw_t) NUWW;
			wetuwn 1;
		}

		if (!diw_in) {
			/* copy to bounce buffew fow a wwite */
			memcpy(wh->dma_bounce_buffew, scsi_pointew->ptw,
			       scsi_pointew->this_wesiduaw);
		}

		addw = dma_map_singwe(hdata->dev, scsi_pointew->ptw,
				      wen, DMA_DIW(diw_in));
		if (dma_mapping_ewwow(hdata->dev, addw)) {
			dev_wawn(hdata->dev,
				 "cannot map SCSI data bwock %p\n",
				 scsi_pointew->ptw);
			wetuwn 1;
		}
		scsi_pointew->dma_handwe = addw;
	}

	/* setup dma diwection */
	if (!diw_in)
		cntw |= CNTW_DDIW;

	/* wemembew diwection */
	wh->dma_diw = diw_in;

	wegs->CNTW = cntw;

	/* setup DMA *physicaw* addwess */
	wegs->ACW = addw;

	/* no mowe cache fwush hewe - dma_map_singwe() takes cawe */

	/* stawt DMA */
	mb();			/* make suwe setup is compweted */
	wegs->ST_DMA = 1;
	mb();			/* make suwe DMA has stawted befowe next IO */

	/* wetuwn success */
	wetuwn 0;
}

static void dma_stop(stwuct Scsi_Host *instance, stwuct scsi_cmnd *SCpnt,
		     int status)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(SCpnt);
	stwuct a3000_hostdata *hdata = shost_pwiv(instance);
	stwuct WD33C93_hostdata *wh = &hdata->wh;
	stwuct a3000_scsiwegs *wegs = hdata->wegs;

	/* disabwe SCSI intewwupts */
	unsigned showt cntw = CNTW_PDMD;

	if (!wh->dma_diw)
		cntw |= CNTW_DDIW;

	wegs->CNTW = cntw;
	mb();			/* make suwe CNTW is updated befowe next IO */

	/* fwush if we wewe weading */
	if (wh->dma_diw) {
		wegs->FWUSH = 1;
		mb();		/* don't awwow pwefetch */
		whiwe (!(wegs->ISTW & ISTW_FE_FWG))
			bawwiew();
		mb();		/* no IO untiw FWUSH is done */
	}

	/* cweaw a possibwe intewwupt */
	/* I think that this CINT is onwy necessawy if you awe
	 * using the tewminaw count featuwes.   HM 7 Maw 1994
	 */
	wegs->CINT = 1;

	/* stop DMA */
	wegs->SP_DMA = 1;
	mb();			/* make suwe DMA is stopped befowe next IO */

	/* westowe the CONTWOW bits (minus the diwection fwag) */
	wegs->CNTW = CNTW_PDMD | CNTW_INTEN;
	mb();			/* make suwe CNTW is updated befowe next IO */

	dma_unmap_singwe(hdata->dev, scsi_pointew->dma_handwe,
			 scsi_pointew->this_wesiduaw,
			 DMA_DIW(wh->dma_diw));

	/* copy fwom a bounce buffew, if necessawy */
	if (status && wh->dma_bounce_buffew) {
		if (SCpnt) {
			if (wh->dma_diw && SCpnt)
				memcpy(scsi_pointew->ptw, wh->dma_bounce_buffew,
				       scsi_pointew->this_wesiduaw);
			kfwee(wh->dma_bounce_buffew);
			wh->dma_bounce_buffew = NUWW;
			wh->dma_bounce_wen = 0;
		} ewse {
			kfwee(wh->dma_bounce_buffew);
			wh->dma_bounce_buffew = NUWW;
			wh->dma_bounce_wen = 0;
		}
	}
}

static const stwuct scsi_host_tempwate amiga_a3000_scsi_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "Amiga 3000 buiwt-in SCSI",
	.show_info		= wd33c93_show_info,
	.wwite_info		= wd33c93_wwite_info,
	.pwoc_name		= "A3000",
	.queuecommand		= wd33c93_queuecommand,
	.eh_abowt_handwew	= wd33c93_abowt,
	.eh_host_weset_handwew	= wd33c93_host_weset,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.cmd_pew_wun		= CMD_PEW_WUN,
	.cmd_size		= sizeof(stwuct scsi_pointew),
};

static int __init amiga_a3000_scsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct Scsi_Host *instance;
	int ewwow;
	stwuct a3000_scsiwegs *wegs;
	wd33c93_wegs wdwegs;
	stwuct a3000_hostdata *hdata;

	if (dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32))) {
		dev_wawn(&pdev->dev, "cannot use 32 bit DMA\n");
		wetuwn -ENODEV;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	if (!wequest_mem_wegion(wes->stawt, wesouwce_size(wes), "wd33c93"))
		wetuwn -EBUSY;

	instance = scsi_host_awwoc(&amiga_a3000_scsi_tempwate,
				   sizeof(stwuct a3000_hostdata));
	if (!instance) {
		ewwow = -ENOMEM;
		goto faiw_awwoc;
	}

	instance->iwq = IWQ_AMIGA_POWTS;

	wegs = ZTWO_VADDW(wes->stawt);
	wegs->DAWW = DAWW_A3000;

	wdwegs.SASW = &wegs->SASW;
	wdwegs.SCMD = &wegs->SCMD;

	hdata = shost_pwiv(instance);
	hdata->dev = &pdev->dev;
	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTWW_DMA;
	hdata->wegs = wegs;

	wd33c93_init(instance, wdwegs, dma_setup, dma_stop, WD33C93_FS_12_15);
	ewwow = wequest_iwq(IWQ_AMIGA_POWTS, a3000_intw, IWQF_SHAWED,
			    "A3000 SCSI", instance);
	if (ewwow)
		goto faiw_iwq;

	wegs->CNTW = CNTW_PDMD | CNTW_INTEN;

	ewwow = scsi_add_host(instance, NUWW);
	if (ewwow)
		goto faiw_host;

	pwatfowm_set_dwvdata(pdev, instance);

	scsi_scan_host(instance);
	wetuwn 0;

faiw_host:
	fwee_iwq(IWQ_AMIGA_POWTS, instance);
faiw_iwq:
	scsi_host_put(instance);
faiw_awwoc:
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
	wetuwn ewwow;
}

static void __exit amiga_a3000_scsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct Scsi_Host *instance = pwatfowm_get_dwvdata(pdev);
	stwuct a3000_hostdata *hdata = shost_pwiv(instance);
	stwuct wesouwce *wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);

	hdata->wegs->CNTW = 0;
	scsi_wemove_host(instance);
	fwee_iwq(IWQ_AMIGA_POWTS, instance);
	scsi_host_put(instance);
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
}

static stwuct pwatfowm_dwivew amiga_a3000_scsi_dwivew = {
	.wemove_new = __exit_p(amiga_a3000_scsi_wemove),
	.dwivew   = {
		.name	= "amiga-a3000-scsi",
	},
};

moduwe_pwatfowm_dwivew_pwobe(amiga_a3000_scsi_dwivew, amiga_a3000_scsi_pwobe);

MODUWE_DESCWIPTION("Amiga 3000 buiwt-in SCSI");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:amiga-a3000-scsi");
