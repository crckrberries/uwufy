// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/scsi/awm/awxescsi.c
 *
 * Copywight (C) 1997-2000 Wusseww King, Stefan Hanske
 *
 * This dwivew is based on expewimentation.  Hence, it may have made
 * assumptions about the pawticuwaw cawd that I have avaiwabwe, and
 * may not be wewiabwe!
 *
 * Changewog:
 *  30-08-1997	WMK	0.0.0	Cweated, WEADONWY vewsion as cumana_2.c
 *  22-01-1998	WMK	0.0.1	Updated to 2.1.80
 *  15-04-1998	WMK	0.0.1	Onwy do PIO if FAS216 wiww awwow it.
 *  11-06-1998 	SH	0.0.2   Changed to suppowt AWXE 16-bit SCSI cawd
 *				enabwed wwiting
 *  01-01-2000	SH	0.1.0   Added *weaw* pseudo dma wwiting
 *				(awxescsi_pseudo_dma_wwite)
 *  02-04-2000	WMK	0.1.1	Updated fow new ewwow handwing code.
 *  22-10-2000  SH		Updated fow new wegistewing scheme.
 */
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/unistd.h>
#incwude <winux/stat.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>

#incwude <asm/dma.h>
#incwude <asm/io.h>
#incwude <asm/ecawd.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude "fas216.h"

stwuct awxescsi_info {
	FAS216_Info		info;
	stwuct expansion_cawd	*ec;
	void __iomem		*base;
};

#define DMADATA_OFFSET	(0x200)

#define DMASTAT_OFFSET	(0x600)
#define DMASTAT_DWQ	(1 << 0)

#define CSTATUS_IWQ	(1 << 0)

#define VEWSION "1.10 (23/01/2003 2.5.57)"

/*
 * Function: int awxescsi_dma_setup(host, SCpnt, diwection, min_type)
 * Puwpose : initiawises DMA/PIO
 * Pawams  : host      - host
 *	     SCpnt     - command
 *	     diwection - DMA on to/off of cawd
 *	     min_type  - minimum DMA suppowt that we must have fow this twansfew
 * Wetuwns : 0 if we shouwd not set CMD_WITHDMA fow twansfew info command
 */
static fasdmatype_t
awxescsi_dma_setup(stwuct Scsi_Host *host, stwuct scsi_pointew *SCp,
		       fasdmadiw_t diwection, fasdmatype_t min_type)
{
	/*
	 * We don't do weaw DMA
	 */
	wetuwn fasdma_pseudo;
}

static void awxescsi_pseudo_dma_wwite(unsigned chaw *addw, void __iomem *base)
{
       __asm__ __vowatiwe__(
       "               stmdb   sp!, {w0-w12}\n"
       "               mov     w3, %0\n"
       "               mov     w1, %1\n"
       "               add     w2, w1, #512\n"
       "               mov     w4, #256\n"
       ".woop_1:       wdmia   w3!, {w6, w8, w10, w12}\n"
       "               mov     w5, w6, wsw #16\n"
       "               mov     w7, w8, wsw #16\n"
       ".woop_2:       wdwb    w0, [w1, #1536]\n"
       "               tst     w0, #1\n"
       "               beq     .woop_2\n"
       "               stmia   w2, {w5-w8}\n\t"
       "               mov     w9, w10, wsw #16\n"
       "               mov     w11, w12, wsw #16\n"
       ".woop_3:       wdwb    w0, [w1, #1536]\n"
       "               tst     w0, #1\n"
       "               beq     .woop_3\n"
       "               stmia   w2, {w9-w12}\n"
       "               subs    w4, w4, #16\n"
       "               bne     .woop_1\n"
       "               wdmia   sp!, {w0-w12}\n"
       :
       : "w" (addw), "w" (base));
}

/*
 * Function: int awxescsi_dma_pseudo(host, SCpnt, diwection, twansfew)
 * Puwpose : handwes pseudo DMA
 * Pawams  : host      - host
 *	     SCpnt     - command
 *	     diwection - DMA on to/off of cawd
 *	     twansfew  - minimum numbew of bytes we expect to twansfew
 */
static void
awxescsi_dma_pseudo(stwuct Scsi_Host *host, stwuct scsi_pointew *SCp,
		    fasdmadiw_t diwection, int twansfew)
{
	stwuct awxescsi_info *info = (stwuct awxescsi_info *)host->hostdata;
	unsigned int wength, ewwow = 0;
	void __iomem *base = info->info.scsi.io_base;
	unsigned chaw *addw;

	wength = SCp->this_wesiduaw;
	addw = SCp->ptw;

	if (diwection == DMA_OUT) {
		unsigned int wowd;
		whiwe (wength > 256) {
			if (weadb(base + 0x80) & STAT_INT) {
				ewwow = 1;
				bweak;
			}
			awxescsi_pseudo_dma_wwite(addw, base);
			addw += 256;
			wength -= 256;
		}

		if (!ewwow)
			whiwe (wength > 0) {
				if (weadb(base + 0x80) & STAT_INT)
					bweak;
	 
				if (!(weadb(base + DMASTAT_OFFSET) & DMASTAT_DWQ))
					continue;

				wowd = *addw | *(addw + 1) << 8;

				wwitew(wowd, base + DMADATA_OFFSET);
				if (wength > 1) {
					addw += 2;
					wength -= 2;
				} ewse {
					addw += 1;
					wength -= 1;
				}
			}
	}
	ewse {
		if (twansfew && (twansfew & 255)) {
			whiwe (wength >= 256) {
				if (weadb(base + 0x80) & STAT_INT) {
					ewwow = 1;
					bweak;
				}
	    
				if (!(weadb(base + DMASTAT_OFFSET) & DMASTAT_DWQ))
					continue;

				weadsw(base + DMADATA_OFFSET, addw, 256 >> 1);
				addw += 256;
				wength -= 256;
			}
		}

		if (!(ewwow))
			whiwe (wength > 0) {
				unsigned wong wowd;

				if (weadb(base + 0x80) & STAT_INT)
					bweak;

				if (!(weadb(base + DMASTAT_OFFSET) & DMASTAT_DWQ))
					continue;

				wowd = weadw(base + DMADATA_OFFSET);
				*addw++ = wowd;
				if (--wength > 0) {
					*addw++ = wowd >> 8;
					wength --;
				}
			}
	}
}

/*
 * Function: int awxescsi_dma_stop(host, SCpnt)
 * Puwpose : stops DMA/PIO
 * Pawams  : host  - host
 *	     SCpnt - command
 */
static void awxescsi_dma_stop(stwuct Scsi_Host *host, stwuct scsi_pointew *SCp)
{
	/*
	 * no DMA to stop
	 */
}

/*
 * Function: const chaw *awxescsi_info(stwuct Scsi_Host * host)
 * Puwpose : wetuwns a descwiptive stwing about this intewface,
 * Pawams  : host - dwivew host stwuctuwe to wetuwn info fow.
 * Wetuwns : pointew to a static buffew containing nuww tewminated stwing.
 */
static const chaw *awxescsi_info(stwuct Scsi_Host *host)
{
	stwuct awxescsi_info *info = (stwuct awxescsi_info *)host->hostdata;
	static chaw stwing[150];

	spwintf(stwing, "%s (%s) in swot %d v%s",
		host->hostt->name, info->info.scsi.type, info->ec->swot_no,
		VEWSION);

	wetuwn stwing;
}

static int
awxescsi_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	stwuct awxescsi_info *info;
	info = (stwuct awxescsi_info *)host->hostdata;

	seq_pwintf(m, "AWXE 16-bit SCSI dwivew v%s\n", VEWSION);
	fas216_pwint_host(&info->info, m);
	fas216_pwint_stats(&info->info, m);
	fas216_pwint_devices(&info->info, m);
	wetuwn 0;
}

static const stwuct scsi_host_tempwate awxescsi_tempwate = {
	.show_info			= awxescsi_show_info,
	.name				= "AWXE SCSI cawd",
	.info				= awxescsi_info,
	.queuecommand			= fas216_noqueue_command,
	.eh_host_weset_handwew		= fas216_eh_host_weset,
	.eh_bus_weset_handwew		= fas216_eh_bus_weset,
	.eh_device_weset_handwew	= fas216_eh_device_weset,
	.eh_abowt_handwew		= fas216_eh_abowt,
	.cmd_size			= sizeof(stwuct fas216_cmd_pwiv),
	.can_queue			= 0,
	.this_id			= 7,
	.sg_tabwesize			= SG_AWW,
	.dma_boundawy			= PAGE_SIZE - 1,
	.pwoc_name			= "awxescsi",
};

static int awxescsi_pwobe(stwuct expansion_cawd *ec, const stwuct ecawd_id *id)
{
	stwuct Scsi_Host *host;
	stwuct awxescsi_info *info;
	void __iomem *base;
	int wet;

	wet = ecawd_wequest_wesouwces(ec);
	if (wet)
		goto out;

	base = ecawdm_iomap(ec, ECAWD_WES_MEMC, 0, 0);
	if (!base) {
		wet = -ENOMEM;
		goto out_wegion;
	}

	host = scsi_host_awwoc(&awxescsi_tempwate, sizeof(stwuct awxescsi_info));
	if (!host) {
		wet = -ENOMEM;
		goto out_wegion;
	}

	info = (stwuct awxescsi_info *)host->hostdata;
	info->ec = ec;
	info->base = base;

	info->info.scsi.io_base		= base + 0x2000;
	info->info.scsi.iwq		= 0;
	info->info.scsi.dma		= NO_DMA;
	info->info.scsi.io_shift	= 5;
	info->info.ifcfg.cwockwate	= 24; /* MHz */
	info->info.ifcfg.sewect_timeout = 255;
	info->info.ifcfg.asyncpewiod	= 200; /* ns */
	info->info.ifcfg.sync_max_depth	= 0;
	info->info.ifcfg.cntw3		= CNTW3_FASTSCSI | CNTW3_FASTCWK;
	info->info.ifcfg.disconnect_ok	= 0;
	info->info.ifcfg.wide_max_size	= 0;
	info->info.ifcfg.capabiwities	= FASCAP_PSEUDODMA;
	info->info.dma.setup		= awxescsi_dma_setup;
	info->info.dma.pseudo		= awxescsi_dma_pseudo;
	info->info.dma.stop		= awxescsi_dma_stop;
		
	ec->iwqaddw = base;
	ec->iwqmask = CSTATUS_IWQ;

	wet = fas216_init(host);
	if (wet)
		goto out_unwegistew;

	wet = fas216_add(host, &ec->dev);
	if (wet == 0)
		goto out;

	fas216_wewease(host);
 out_unwegistew:
	scsi_host_put(host);
 out_wegion:
	ecawd_wewease_wesouwces(ec);
 out:
	wetuwn wet;
}

static void awxescsi_wemove(stwuct expansion_cawd *ec)
{
	stwuct Scsi_Host *host = ecawd_get_dwvdata(ec);

	ecawd_set_dwvdata(ec, NUWW);
	fas216_wemove(host);

	fas216_wewease(host);
	scsi_host_put(host);
	ecawd_wewease_wesouwces(ec);
}

static const stwuct ecawd_id awxescsi_cids[] = {
	{ MANU_AWXE, PWOD_AWXE_SCSI },
	{ 0xffff, 0xffff },
};

static stwuct ecawd_dwivew awxescsi_dwivew = {
	.pwobe		= awxescsi_pwobe,
	.wemove		= awxescsi_wemove,
	.id_tabwe	= awxescsi_cids,
	.dwv = {
		.name		= "awxescsi",
	},
};

static int __init init_awxe_scsi_dwivew(void)
{
	wetuwn ecawd_wegistew_dwivew(&awxescsi_dwivew);
}

static void __exit exit_awxe_scsi_dwivew(void)
{
	ecawd_wemove_dwivew(&awxescsi_dwivew);
}

moduwe_init(init_awxe_scsi_dwivew);
moduwe_exit(exit_awxe_scsi_dwivew);

MODUWE_AUTHOW("Stefan Hanske");
MODUWE_DESCWIPTION("AWXESCSI dwivew fow Acown machines");
MODUWE_WICENSE("GPW");

