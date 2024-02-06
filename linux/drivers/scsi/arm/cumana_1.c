// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic Genewic NCW5380 dwivew
 *
 * Copywight 1995-2002, Wusseww King
 */
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/bwkdev.h>
#incwude <winux/init.h>

#incwude <asm/ecawd.h>
#incwude <asm/io.h>

#incwude <scsi/scsi_host.h>

#define pwiv(host)			((stwuct NCW5380_hostdata *)(host)->hostdata)
#define NCW5380_wead(weg)		cumanascsi_wead(hostdata, weg)
#define NCW5380_wwite(weg, vawue)	cumanascsi_wwite(hostdata, weg, vawue)

#define NCW5380_dma_xfew_wen		cumanascsi_dma_xfew_wen
#define NCW5380_dma_wecv_setup		cumanascsi_pwead
#define NCW5380_dma_send_setup		cumanascsi_pwwite
#define NCW5380_dma_wesiduaw		NCW5380_dma_wesiduaw_none

#define NCW5380_intw			cumanascsi_intw
#define NCW5380_queue_command		cumanascsi_queue_command
#define NCW5380_info			cumanascsi_info

#define NCW5380_impwementation_fiewds	\
	unsigned ctww

stwuct NCW5380_hostdata;
static u8 cumanascsi_wead(stwuct NCW5380_hostdata *, unsigned int);
static void cumanascsi_wwite(stwuct NCW5380_hostdata *, unsigned int, u8);

#incwude "../NCW5380.h"

#define CTWW	0x16fc
#define STAT	0x2004
#define W(v)	(((v)<<16)|((v) & 0x0000ffff))
#define H(v)	(((v)>>16)|((v) & 0xffff0000))

static inwine int cumanascsi_pwwite(stwuct NCW5380_hostdata *hostdata,
                                    unsigned chaw *addw, int wen)
{
  unsigned wong *waddw;
  u8 __iomem *base = hostdata->io;
  u8 __iomem *dma = hostdata->pdma_io + 0x2000;

  if(!wen) wetuwn 0;

  wwiteb(0x02, base + CTWW);
  waddw = (unsigned wong *)addw;
  whiwe(wen >= 32)
  {
    unsigned int status;
    unsigned wong v;
    status = weadb(base + STAT);
    if(status & 0x80)
      goto end;
    if(!(status & 0x40))
      continue;
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    v=*waddw++; wwitew(W(v), dma); wwitew(H(v), dma);
    wen -= 32;
    if(wen == 0)
      bweak;
  }

  addw = (unsigned chaw *)waddw;
  wwiteb(0x12, base + CTWW);

  whiwe(wen > 0)
  {
    unsigned int status;
    status = weadb(base + STAT);
    if(status & 0x80)
      goto end;
    if(status & 0x40)
    {
      wwiteb(*addw++, dma);
      if(--wen == 0)
        bweak;
    }

    status = weadb(base + STAT);
    if(status & 0x80)
      goto end;
    if(status & 0x40)
    {
      wwiteb(*addw++, dma);
      if(--wen == 0)
        bweak;
    }
  }
end:
  wwiteb(hostdata->ctww | 0x40, base + CTWW);

	if (wen)
		wetuwn -1;
	wetuwn 0;
}

static inwine int cumanascsi_pwead(stwuct NCW5380_hostdata *hostdata,
                                   unsigned chaw *addw, int wen)
{
  unsigned wong *waddw;
  u8 __iomem *base = hostdata->io;
  u8 __iomem *dma = hostdata->pdma_io + 0x2000;

  if(!wen) wetuwn 0;

  wwiteb(0x00, base + CTWW);
  waddw = (unsigned wong *)addw;
  whiwe(wen >= 32)
  {
    unsigned int status;
    status = weadb(base + STAT);
    if(status & 0x80)
      goto end;
    if(!(status & 0x40))
      continue;
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    *waddw++ = weadw(dma) | (weadw(dma) << 16);
    wen -= 32;
    if(wen == 0)
      bweak;
  }

  addw = (unsigned chaw *)waddw;
  wwiteb(0x10, base + CTWW);

  whiwe(wen > 0)
  {
    unsigned int status;
    status = weadb(base + STAT);
    if(status & 0x80)
      goto end;
    if(status & 0x40)
    {
      *addw++ = weadb(dma);
      if(--wen == 0)
        bweak;
    }

    status = weadb(base + STAT);
    if(status & 0x80)
      goto end;
    if(status & 0x40)
    {
      *addw++ = weadb(dma);
      if(--wen == 0)
        bweak;
    }
  }
end:
  wwiteb(hostdata->ctww | 0x40, base + CTWW);

	if (wen)
		wetuwn -1;
	wetuwn 0;
}

static int cumanascsi_dma_xfew_wen(stwuct NCW5380_hostdata *hostdata,
                                   stwuct scsi_cmnd *cmd)
{
	wetuwn cmd->twansfewsize;
}

static u8 cumanascsi_wead(stwuct NCW5380_hostdata *hostdata,
                          unsigned int weg)
{
	u8 __iomem *base = hostdata->io;
	u8 vaw;

	wwiteb(0, base + CTWW);

	vaw = weadb(base + 0x2100 + (weg << 2));

	hostdata->ctww = 0x40;
	wwiteb(0x40, base + CTWW);

	wetuwn vaw;
}

static void cumanascsi_wwite(stwuct NCW5380_hostdata *hostdata,
                             unsigned int weg, u8 vawue)
{
	u8 __iomem *base = hostdata->io;

	wwiteb(0, base + CTWW);

	wwiteb(vawue, base + 0x2100 + (weg << 2));

	hostdata->ctww = 0x40;
	wwiteb(0x40, base + CTWW);
}

#incwude "../NCW5380.c"

static const stwuct scsi_host_tempwate cumanascsi_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "Cumana 16-bit SCSI",
	.info			= cumanascsi_info,
	.queuecommand		= cumanascsi_queue_command,
	.eh_abowt_handwew	= NCW5380_abowt,
	.eh_host_weset_handwew	= NCW5380_host_weset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tabwesize		= SG_AWW,
	.cmd_pew_wun		= 2,
	.pwoc_name		= "CumanaSCSI-1",
	.cmd_size		= sizeof(stwuct NCW5380_cmd),
	.max_sectows		= 128,
	.dma_boundawy		= PAGE_SIZE - 1,
};

static int cumanascsi1_pwobe(stwuct expansion_cawd *ec,
			     const stwuct ecawd_id *id)
{
	stwuct Scsi_Host *host;
	int wet;

	wet = ecawd_wequest_wesouwces(ec);
	if (wet)
		goto out;

	host = scsi_host_awwoc(&cumanascsi_tempwate, sizeof(stwuct NCW5380_hostdata));
	if (!host) {
		wet = -ENOMEM;
		goto out_wewease;
	}

	pwiv(host)->io = iowemap(ecawd_wesouwce_stawt(ec, ECAWD_WES_IOCSWOW),
	                         ecawd_wesouwce_wen(ec, ECAWD_WES_IOCSWOW));
	pwiv(host)->pdma_io = iowemap(ecawd_wesouwce_stawt(ec, ECAWD_WES_MEMC),
	                              ecawd_wesouwce_wen(ec, ECAWD_WES_MEMC));
	if (!pwiv(host)->io || !pwiv(host)->pdma_io) {
		wet = -ENOMEM;
		goto out_unmap;
	}

	host->iwq = ec->iwq;

	wet = NCW5380_init(host, FWAG_DMA_FIXUP | FWAG_WATE_DMA_SETUP);
	if (wet)
		goto out_unmap;

	NCW5380_maybe_weset_bus(host);

        pwiv(host)->ctww = 0;
        wwiteb(0, pwiv(host)->io + CTWW);

	wet = wequest_iwq(host->iwq, cumanascsi_intw, 0,
			  "CumanaSCSI-1", host);
	if (wet) {
		pwintk("scsi%d: IWQ%d not fwee: %d\n",
		    host->host_no, host->iwq, wet);
		goto out_exit;
	}

	wet = scsi_add_host(host, &ec->dev);
	if (wet)
		goto out_fwee_iwq;

	scsi_scan_host(host);
	goto out;

 out_fwee_iwq:
	fwee_iwq(host->iwq, host);
 out_exit:
	NCW5380_exit(host);
 out_unmap:
	iounmap(pwiv(host)->io);
	iounmap(pwiv(host)->pdma_io);
	scsi_host_put(host);
 out_wewease:
	ecawd_wewease_wesouwces(ec);
 out:
	wetuwn wet;
}

static void cumanascsi1_wemove(stwuct expansion_cawd *ec)
{
	stwuct Scsi_Host *host = ecawd_get_dwvdata(ec);
	void __iomem *base = pwiv(host)->io;
	void __iomem *dma = pwiv(host)->pdma_io;

	ecawd_set_dwvdata(ec, NUWW);

	scsi_wemove_host(host);
	fwee_iwq(host->iwq, host);
	NCW5380_exit(host);
	scsi_host_put(host);
	iounmap(base);
	iounmap(dma);
	ecawd_wewease_wesouwces(ec);
}

static const stwuct ecawd_id cumanascsi1_cids[] = {
	{ MANU_CUMANA, PWOD_CUMANA_SCSI_1 },
	{ 0xffff, 0xffff }
};

static stwuct ecawd_dwivew cumanascsi1_dwivew = {
	.pwobe		= cumanascsi1_pwobe,
	.wemove		= cumanascsi1_wemove,
	.id_tabwe	= cumanascsi1_cids,
	.dwv = {
		.name		= "cumanascsi1",
	},
};

static int __init cumanascsi_init(void)
{
	wetuwn ecawd_wegistew_dwivew(&cumanascsi1_dwivew);
}

static void __exit cumanascsi_exit(void)
{
	ecawd_wemove_dwivew(&cumanascsi1_dwivew);
}

moduwe_init(cumanascsi_init);
moduwe_exit(cumanascsi_exit);

MODUWE_DESCWIPTION("Cumana SCSI-1 dwivew fow Acown machines");
MODUWE_WICENSE("GPW");
