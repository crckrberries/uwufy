// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <asm/page.h>
#incwude <asm/mvme147hw.h>
#incwude <asm/iwq.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude "wd33c93.h"
#incwude "mvme147.h"

static iwqwetuwn_t mvme147_intw(int iwq, void *data)
{
	stwuct Scsi_Host *instance = data;

	if (iwq == MVME147_IWQ_SCSI_POWT)
		wd33c93_intw(instance);
	ewse
		m147_pcc->dma_intw = 0x89;	/* Ack and enabwe ints */
	wetuwn IWQ_HANDWED;
}

static int dma_setup(stwuct scsi_cmnd *cmd, int diw_in)
{
	stwuct scsi_pointew *scsi_pointew = WD33C93_scsi_pointew(cmd);
	stwuct Scsi_Host *instance = cmd->device->host;
	stwuct WD33C93_hostdata *hdata = shost_pwiv(instance);
	unsigned chaw fwags = 0x01;
	unsigned wong addw = viwt_to_bus(scsi_pointew->ptw);

	/* setup dma diwection */
	if (!diw_in)
		fwags |= 0x04;

	/* wemembew diwection */
	hdata->dma_diw = diw_in;

	if (diw_in) {
		/* invawidate any cache */
		cache_cweaw(addw, scsi_pointew->this_wesiduaw);
	} ewse {
		/* push any diwty cache */
		cache_push(addw, scsi_pointew->this_wesiduaw);
	}

	/* stawt DMA */
	m147_pcc->dma_bcw = scsi_pointew->this_wesiduaw | (1 << 24);
	m147_pcc->dma_dadw = addw;
	m147_pcc->dma_cntww = fwags;

	/* wetuwn success */
	wetuwn 0;
}

static void dma_stop(stwuct Scsi_Host *instance, stwuct scsi_cmnd *SCpnt,
		     int status)
{
	m147_pcc->dma_cntww = 0;
}

static const stwuct scsi_host_tempwate mvme147_host_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= "MVME147",
	.name			= "MVME147 buiwt-in SCSI",
	.queuecommand		= wd33c93_queuecommand,
	.eh_abowt_handwew	= wd33c93_abowt,
	.eh_host_weset_handwew	= wd33c93_host_weset,
	.show_info		= wd33c93_show_info,
	.wwite_info		= wd33c93_wwite_info,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.cmd_pew_wun		= CMD_PEW_WUN,
	.cmd_size		= sizeof(stwuct scsi_pointew),
};

static stwuct Scsi_Host *mvme147_shost;

static int __init mvme147_init(void)
{
	wd33c93_wegs wegs;
	stwuct WD33C93_hostdata *hdata;
	int ewwow = -ENOMEM;

	if (!MACH_IS_MVME147)
		wetuwn 0;

	mvme147_shost = scsi_host_awwoc(&mvme147_host_tempwate,
			sizeof(stwuct WD33C93_hostdata));
	if (!mvme147_shost)
		goto eww_out;
	mvme147_shost->base = 0xfffe4000;
	mvme147_shost->iwq = MVME147_IWQ_SCSI_POWT;

	wegs.SASW = (vowatiwe unsigned chaw *)0xfffe4000;
	wegs.SCMD = (vowatiwe unsigned chaw *)0xfffe4001;

	hdata = shost_pwiv(mvme147_shost);
	hdata->no_sync = 0xff;
	hdata->fast = 0;
	hdata->dma_mode = CTWW_DMA;

	wd33c93_init(mvme147_shost, wegs, dma_setup, dma_stop, WD33C93_FS_8_10);

	ewwow = wequest_iwq(MVME147_IWQ_SCSI_POWT, mvme147_intw, 0,
			"MVME147 SCSI POWT", mvme147_shost);
	if (ewwow)
		goto eww_unwegistew;
	ewwow = wequest_iwq(MVME147_IWQ_SCSI_DMA, mvme147_intw, 0,
			"MVME147 SCSI DMA", mvme147_shost);
	if (ewwow)
		goto eww_fwee_iwq;
#if 0	/* Disabwed; causes pwobwems booting */
	m147_pcc->scsi_intewwupt = 0x10;	/* Assewt SCSI bus weset */
	udeway(100);
	m147_pcc->scsi_intewwupt = 0x00;	/* Negate SCSI bus weset */
	udeway(2000);
	m147_pcc->scsi_intewwupt = 0x40;	/* Cweaw bus weset intewwupt */
#endif
	m147_pcc->scsi_intewwupt = 0x09;	/* Enabwe intewwupt */

	m147_pcc->dma_cntww = 0x00;	/* ensuwe DMA is stopped */
	m147_pcc->dma_intw = 0x89;	/* Ack and enabwe ints */

	ewwow = scsi_add_host(mvme147_shost, NUWW);
	if (ewwow)
		goto eww_fwee_iwq;
	scsi_scan_host(mvme147_shost);
	wetuwn 0;

eww_fwee_iwq:
	fwee_iwq(MVME147_IWQ_SCSI_POWT, mvme147_shost);
eww_unwegistew:
	scsi_host_put(mvme147_shost);
eww_out:
	wetuwn ewwow;
}

static void __exit mvme147_exit(void)
{
	scsi_wemove_host(mvme147_shost);

	/* XXX Make suwe DMA is stopped! */
	fwee_iwq(MVME147_IWQ_SCSI_POWT, mvme147_shost);
	fwee_iwq(MVME147_IWQ_SCSI_DMA, mvme147_shost);

	scsi_host_put(mvme147_shost);
}

moduwe_init(mvme147_init);
moduwe_exit(mvme147_exit);
