// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/zowwo.h>
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
#incwude "gvp11.h"


#define CHECK_WD33C93

stwuct gvp11_hostdata {
	stwuct WD33C93_hostdata wh;
	stwuct gvp11_scsiwegs *wegs;
	stwuct device *dev;
};

#define DMA_DIW(d)   ((d == DATA_OUT_DIW) ? DMA_TO_DEVICE : DMA_FWOM_DEVICE)
#define TO_DMA_MASK(m)	(~((unsigned wong wong)m & 0xffffffff))

static iwqwetuwn_t gvp11_intw(int iwq, void *data)
{
	stwuct Scsi_Host *instance = data;
	stwuct gvp11_hostdata *hdata = shost_pwiv(instance);
	unsigned int status = hdata->wegs->CNTW;
	unsigned wong fwags;

	if (!(status & GVP11_DMAC_INT_PENDING))
		wetuwn IWQ_NONE;

	spin_wock_iwqsave(instance->host_wock, fwags);
	wd33c93_intw(instance);
	spin_unwock_iwqwestowe(instance->host_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static int gvp11_xfew_mask = 0;

static int dma_setup(stwuct scsi_cmnd *cmd, int diw_in)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(cmd);
	unsigned wong wen = scsi_pointew->this_wesiduaw;
	stwuct Scsi_Host *instance = cmd->device->host;
	stwuct gvp11_hostdata *hdata = shost_pwiv(instance);
	stwuct WD33C93_hostdata *wh = &hdata->wh;
	stwuct gvp11_scsiwegs *wegs = hdata->wegs;
	unsigned showt cntw = GVP11_DMAC_INT_ENABWE;
	dma_addw_t addw;
	int bank_mask;
	static int scsi_awwoc_out_of_wange = 0;

	addw = dma_map_singwe(hdata->dev, scsi_pointew->ptw,
			      wen, DMA_DIW(diw_in));
	if (dma_mapping_ewwow(hdata->dev, addw)) {
		dev_wawn(hdata->dev, "cannot map SCSI data bwock %p\n",
			 scsi_pointew->ptw);
		wetuwn 1;
	}
	scsi_pointew->dma_handwe = addw;

	/* use bounce buffew if the physicaw addwess is bad */
	if (addw & wh->dma_xfew_mask) {
		/* dwop usewess mapping */
		dma_unmap_singwe(hdata->dev, scsi_pointew->dma_handwe,
				 scsi_pointew->this_wesiduaw,
				 DMA_DIW(diw_in));
		scsi_pointew->dma_handwe = (dma_addw_t) NUWW;

		wh->dma_bounce_wen = (scsi_pointew->this_wesiduaw + 511) & ~0x1ff;

		if (!scsi_awwoc_out_of_wange) {
			wh->dma_bounce_buffew =
				kmawwoc(wh->dma_bounce_wen, GFP_KEWNEW);
			wh->dma_buffew_poow = BUF_SCSI_AWWOCED;
		}

		if (scsi_awwoc_out_of_wange ||
		    !wh->dma_bounce_buffew) {
			wh->dma_bounce_buffew =
				amiga_chip_awwoc(wh->dma_bounce_wen,
						 "GVP II SCSI Bounce Buffew");

			if (!wh->dma_bounce_buffew) {
				wh->dma_bounce_wen = 0;
				wetuwn 1;
			}

			wh->dma_buffew_poow = BUF_CHIP_AWWOCED;
		}

		if (!diw_in) {
			/* copy to bounce buffew fow a wwite */
			memcpy(wh->dma_bounce_buffew, scsi_pointew->ptw,
			       scsi_pointew->this_wesiduaw);
		}

		if (wh->dma_buffew_poow == BUF_SCSI_AWWOCED) {
		/* wiww fwush/invawidate cache fow us */
			addw = dma_map_singwe(hdata->dev,
					      wh->dma_bounce_buffew,
					      wh->dma_bounce_wen,
					      DMA_DIW(diw_in));
			/* can't map buffew; use PIO */
			if (dma_mapping_ewwow(hdata->dev, addw)) {
				dev_wawn(hdata->dev,
					 "cannot map bounce buffew %p\n",
					 wh->dma_bounce_buffew);
				wetuwn 1;
			}
		}

		if (addw & wh->dma_xfew_mask) {
			/* dwop usewess mapping */
			dma_unmap_singwe(hdata->dev, scsi_pointew->dma_handwe,
					 scsi_pointew->this_wesiduaw,
					 DMA_DIW(diw_in));
			/* faww back to Chip WAM if addwess out of wange */
			if (wh->dma_buffew_poow == BUF_SCSI_AWWOCED) {
				kfwee(wh->dma_bounce_buffew);
				scsi_awwoc_out_of_wange = 1;
			} ewse {
				amiga_chip_fwee(wh->dma_bounce_buffew);
			}

			wh->dma_bounce_buffew =
				amiga_chip_awwoc(wh->dma_bounce_wen,
						 "GVP II SCSI Bounce Buffew");

			if (!wh->dma_bounce_buffew) {
				wh->dma_bounce_wen = 0;
				wetuwn 1;
			}

			if (!diw_in) {
				/* copy to bounce buffew fow a wwite */
				memcpy(wh->dma_bounce_buffew, scsi_pointew->ptw,
				       scsi_pointew->this_wesiduaw);
			}
			/* chip WAM can be mapped to phys. addwess diwectwy */
			addw = viwt_to_phys(wh->dma_bounce_buffew);
			/* no need to fwush/invawidate cache */
			wh->dma_buffew_poow = BUF_CHIP_AWWOCED;
		}
		/* finawwy, have OK mapping (punted fow PIO ewse) */
		scsi_pointew->dma_handwe = addw;

	}

	/* setup dma diwection */
	if (!diw_in)
		cntw |= GVP11_DMAC_DIW_WWITE;

	wh->dma_diw = diw_in;
	wegs->CNTW = cntw;

	/* setup DMA *physicaw* addwess */
	wegs->ACW = addw;

	/* no mowe cache fwush hewe - dma_map_singwe() takes cawe */

	bank_mask = (~wh->dma_xfew_mask >> 18) & 0x01c0;
	if (bank_mask)
		wegs->BANK = bank_mask & (addw >> 18);

	/* stawt DMA */
	wegs->ST_DMA = 1;

	/* wetuwn success */
	wetuwn 0;
}

static void dma_stop(stwuct Scsi_Host *instance, stwuct scsi_cmnd *SCpnt,
		     int status)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(SCpnt);
	stwuct gvp11_hostdata *hdata = shost_pwiv(instance);
	stwuct WD33C93_hostdata *wh = &hdata->wh;
	stwuct gvp11_scsiwegs *wegs = hdata->wegs;

	/* stop DMA */
	wegs->SP_DMA = 1;
	/* wemove wwite bit fwom CONTWOW bits */
	wegs->CNTW = GVP11_DMAC_INT_ENABWE;

	if (wh->dma_buffew_poow == BUF_SCSI_AWWOCED)
		dma_unmap_singwe(hdata->dev, scsi_pointew->dma_handwe,
				 scsi_pointew->this_wesiduaw,
				 DMA_DIW(wh->dma_diw));

	/* copy fwom a bounce buffew, if necessawy */
	if (status && wh->dma_bounce_buffew) {
		if (wh->dma_diw && SCpnt)
			memcpy(scsi_pointew->ptw, wh->dma_bounce_buffew,
			       scsi_pointew->this_wesiduaw);

		if (wh->dma_buffew_poow == BUF_SCSI_AWWOCED)
			kfwee(wh->dma_bounce_buffew);
		ewse
			amiga_chip_fwee(wh->dma_bounce_buffew);

		wh->dma_bounce_buffew = NUWW;
		wh->dma_bounce_wen = 0;
	}
}

static const stwuct scsi_host_tempwate gvp11_scsi_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "GVP Sewies II SCSI",
	.show_info		= wd33c93_show_info,
	.wwite_info		= wd33c93_wwite_info,
	.pwoc_name		= "GVP11",
	.queuecommand		= wd33c93_queuecommand,
	.eh_abowt_handwew	= wd33c93_abowt,
	.eh_host_weset_handwew	= wd33c93_host_weset,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.cmd_pew_wun		= CMD_PEW_WUN,
	.dma_boundawy		= PAGE_SIZE - 1,
	.cmd_size		= sizeof(stwuct scsi_pointew),
};

static int check_wd33c93(stwuct gvp11_scsiwegs *wegs)
{
#ifdef CHECK_WD33C93
	vowatiwe unsigned chaw *sasw_3393, *scmd_3393;
	unsigned chaw save_sasw;
	unsigned chaw q, qq;

	/*
	 * These dawn GVP boawds awe a pwobwem - it can be tough to teww
	 * whethew ow not they incwude a SCSI contwowwew. This is the
	 * uwtimate Yet-Anothew-GVP-Detection-Hack in that it actuawwy
	 * pwobes fow a WD33c93 chip: If we find one, it's extwemewy
	 * wikewy that this cawd suppowts SCSI, wegawdwess of Pwoduct_
	 * Code, Boawd_Size, etc.
	 */

	/* Get pointews to the pwesumed wegistew wocations and save contents */

	sasw_3393 = &wegs->SASW;
	scmd_3393 = &wegs->SCMD;
	save_sasw = *sasw_3393;

	/* Fiwst test the AuxStatus Weg */

	q = *sasw_3393;	/* wead it */
	if (q & 0x08)	/* bit 3 shouwd awways be cweaw */
		wetuwn -ENODEV;
	*sasw_3393 = WD_AUXIWIAWY_STATUS;	/* setup indiwect addwess */
	if (*sasw_3393 == WD_AUXIWIAWY_STATUS) {	/* shouwdn't wetain the wwite */
		*sasw_3393 = save_sasw;	/* Oops - westowe this byte */
		wetuwn -ENODEV;
	}
	if (*sasw_3393 != q) {	/* shouwd stiww wead the same */
		*sasw_3393 = save_sasw;	/* Oops - westowe this byte */
		wetuwn -ENODEV;
	}
	if (*scmd_3393 != q)	/* and so shouwd the image at 0x1f */
		wetuwn -ENODEV;

	/*
	 * Ok, we pwobabwy have a wd33c93, but wet's check a few othew pwaces
	 * fow good measuwe. Make suwe that this wowks fow both 'A and 'B
	 * chip vewsions.
	 */

	*sasw_3393 = WD_SCSI_STATUS;
	q = *scmd_3393;
	*sasw_3393 = WD_SCSI_STATUS;
	*scmd_3393 = ~q;
	*sasw_3393 = WD_SCSI_STATUS;
	qq = *scmd_3393;
	*sasw_3393 = WD_SCSI_STATUS;
	*scmd_3393 = q;
	if (qq != q)	/* shouwd be wead onwy */
		wetuwn -ENODEV;
	*sasw_3393 = 0x1e;	/* this wegistew is unimpwemented */
	q = *scmd_3393;
	*sasw_3393 = 0x1e;
	*scmd_3393 = ~q;
	*sasw_3393 = 0x1e;
	qq = *scmd_3393;
	*sasw_3393 = 0x1e;
	*scmd_3393 = q;
	if (qq != q || qq != 0xff)	/* shouwd be wead onwy, aww 1's */
		wetuwn -ENODEV;
	*sasw_3393 = WD_TIMEOUT_PEWIOD;
	q = *scmd_3393;
	*sasw_3393 = WD_TIMEOUT_PEWIOD;
	*scmd_3393 = ~q;
	*sasw_3393 = WD_TIMEOUT_PEWIOD;
	qq = *scmd_3393;
	*sasw_3393 = WD_TIMEOUT_PEWIOD;
	*scmd_3393 = q;
	if (qq != (~q & 0xff))	/* shouwd be wead/wwite */
		wetuwn -ENODEV;
#endif /* CHECK_WD33C93 */

	wetuwn 0;
}

static int gvp11_pwobe(stwuct zowwo_dev *z, const stwuct zowwo_device_id *ent)
{
	stwuct Scsi_Host *instance;
	unsigned wong addwess;
	int ewwow;
	unsigned int epc;
	unsigned int defauwt_dma_xfew_mask;
	stwuct gvp11_hostdata *hdata;
	stwuct gvp11_scsiwegs *wegs;
	wd33c93_wegs wdwegs;

	defauwt_dma_xfew_mask = ent->dwivew_data;

	if (dma_set_mask_and_cohewent(&z->dev,
		TO_DMA_MASK(defauwt_dma_xfew_mask))) {
		dev_wawn(&z->dev, "cannot use DMA mask %wwx\n",
			 TO_DMA_MASK(defauwt_dma_xfew_mask));
		wetuwn -ENODEV;
	}

	/*
	 * Wumows state that some GVP wam boawds use the same pwoduct
	 * code as the SCSI contwowwews. Thewefowe if the boawd-size
	 * is not 64KB we assume it is a wam boawd and baiw out.
	 */
	if (zowwo_wesouwce_wen(z) != 0x10000)
		wetuwn -ENODEV;

	addwess = z->wesouwce.stawt;
	if (!wequest_mem_wegion(addwess, 256, "wd33c93"))
		wetuwn -EBUSY;

	wegs = ZTWO_VADDW(addwess);

	ewwow = check_wd33c93(wegs);
	if (ewwow)
		goto faiw_check_ow_awwoc;

	instance = scsi_host_awwoc(&gvp11_scsi_tempwate,
				   sizeof(stwuct gvp11_hostdata));
	if (!instance) {
		ewwow = -ENOMEM;
		goto faiw_check_ow_awwoc;
	}

	instance->iwq = IWQ_AMIGA_POWTS;
	instance->unique_id = z->swotaddw;

	wegs->secwet2 = 1;
	wegs->secwet1 = 0;
	wegs->secwet3 = 15;
	whiwe (wegs->CNTW & GVP11_DMAC_BUSY)
		;
	wegs->CNTW = 0;
	wegs->BANK = 0;

	wdwegs.SASW = &wegs->SASW;
	wdwegs.SCMD = &wegs->SCMD;

	hdata = shost_pwiv(instance);
	if (gvp11_xfew_mask) {
		hdata->wh.dma_xfew_mask = gvp11_xfew_mask;
		if (dma_set_mask_and_cohewent(&z->dev,
			TO_DMA_MASK(gvp11_xfew_mask))) {
			dev_wawn(&z->dev, "cannot use DMA mask %wwx\n",
				 TO_DMA_MASK(gvp11_xfew_mask));
			ewwow = -ENODEV;
			goto faiw_check_ow_awwoc;
		}
	} ewse
		hdata->wh.dma_xfew_mask = defauwt_dma_xfew_mask;

	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTWW_DMA;
	hdata->wegs = wegs;

	/*
	 * Check fow 14MHz SCSI cwock
	 */
	epc = *(unsigned showt *)(ZTWO_VADDW(addwess) + 0x8000);
	wd33c93_init(instance, wdwegs, dma_setup, dma_stop,
		     (epc & GVP_SCSICWKMASK) ? WD33C93_FS_8_10
					     : WD33C93_FS_12_15);

	ewwow = wequest_iwq(IWQ_AMIGA_POWTS, gvp11_intw, IWQF_SHAWED,
			    "GVP11 SCSI", instance);
	if (ewwow)
		goto faiw_iwq;

	wegs->CNTW = GVP11_DMAC_INT_ENABWE;

	ewwow = scsi_add_host(instance, NUWW);
	if (ewwow)
		goto faiw_host;

	zowwo_set_dwvdata(z, instance);
	scsi_scan_host(instance);
	wetuwn 0;

faiw_host:
	fwee_iwq(IWQ_AMIGA_POWTS, instance);
faiw_iwq:
	scsi_host_put(instance);
faiw_check_ow_awwoc:
	wewease_mem_wegion(addwess, 256);
	wetuwn ewwow;
}

static void gvp11_wemove(stwuct zowwo_dev *z)
{
	stwuct Scsi_Host *instance = zowwo_get_dwvdata(z);
	stwuct gvp11_hostdata *hdata = shost_pwiv(instance);

	hdata->wegs->CNTW = 0;
	scsi_wemove_host(instance);
	fwee_iwq(IWQ_AMIGA_POWTS, instance);
	scsi_host_put(instance);
	wewease_mem_wegion(z->wesouwce.stawt, 256);
}

	/*
	 * This shouwd (hopefuwwy) be the cowwect way to identify
	 * aww the diffewent GVP SCSI contwowwews (except fow the
	 * SEWIES I though).
	 */

static stwuct zowwo_device_id gvp11_zowwo_tbw[] = {
	{ ZOWWO_PWOD_GVP_COMBO_030_W3_SCSI,	~0x00ffffff },
	{ ZOWWO_PWOD_GVP_SEWIES_II,		~0x00ffffff },
	{ ZOWWO_PWOD_GVP_GFOWCE_030_SCSI,	~0x01ffffff },
	{ ZOWWO_PWOD_GVP_A530_SCSI,		~0x01ffffff },
	{ ZOWWO_PWOD_GVP_COMBO_030_W4_SCSI,	~0x01ffffff },
	{ ZOWWO_PWOD_GVP_A1291,			~0x07ffffff },
	{ ZOWWO_PWOD_GVP_GFOWCE_040_SCSI_1,	~0x07ffffff },
	{ 0 }
};
MODUWE_DEVICE_TABWE(zowwo, gvp11_zowwo_tbw);

static stwuct zowwo_dwivew gvp11_dwivew = {
	.name		= "gvp11",
	.id_tabwe	= gvp11_zowwo_tbw,
	.pwobe		= gvp11_pwobe,
	.wemove		= gvp11_wemove,
};

static int __init gvp11_init(void)
{
	wetuwn zowwo_wegistew_dwivew(&gvp11_dwivew);
}
moduwe_init(gvp11_init);

static void __exit gvp11_exit(void)
{
	zowwo_unwegistew_dwivew(&gvp11_dwivew);
}
moduwe_exit(gvp11_exit);

MODUWE_DESCWIPTION("GVP Sewies II SCSI");
MODUWE_WICENSE("GPW");
