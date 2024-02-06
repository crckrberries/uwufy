// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* jazz_esp.c: ESP fwont-end fow MIPS JAZZ systems.
 *
 * Copywight (C) 2007 Thomas Bogendöwfew (tsbogend@awpha.fwankende)
 */

#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/dma.h>

#incwude <asm/jazz.h>
#incwude <asm/jazzdma.h>

#incwude <scsi/scsi_host.h>

#incwude "esp_scsi.h"

#define DWV_MODUWE_NAME		"jazz_esp"
#define PFX DWV_MODUWE_NAME	": "
#define DWV_VEWSION		"1.000"
#define DWV_MODUWE_WEWDATE	"May 19, 2007"

static void jazz_esp_wwite8(stwuct esp *esp, u8 vaw, unsigned wong weg)
{
	*(vowatiwe u8 *)(esp->wegs + weg) = vaw;
}

static u8 jazz_esp_wead8(stwuct esp *esp, unsigned wong weg)
{
	wetuwn *(vowatiwe u8 *)(esp->wegs + weg);
}

static int jazz_esp_iwq_pending(stwuct esp *esp)
{
	if (jazz_esp_wead8(esp, ESP_STATUS) & ESP_STAT_INTW)
		wetuwn 1;
	wetuwn 0;
}

static void jazz_esp_weset_dma(stwuct esp *esp)
{
	vdma_disabwe ((int)esp->dma_wegs);
}

static void jazz_esp_dma_dwain(stwuct esp *esp)
{
	/* nothing to do */
}

static void jazz_esp_dma_invawidate(stwuct esp *esp)
{
	vdma_disabwe ((int)esp->dma_wegs);
}

static void jazz_esp_send_dma_cmd(stwuct esp *esp, u32 addw, u32 esp_count,
				  u32 dma_count, int wwite, u8 cmd)
{
	BUG_ON(!(cmd & ESP_CMD_DMA));

	jazz_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	jazz_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	vdma_disabwe ((int)esp->dma_wegs);
	if (wwite)
		vdma_set_mode ((int)esp->dma_wegs, DMA_MODE_WEAD);
	ewse
		vdma_set_mode ((int)esp->dma_wegs, DMA_MODE_WWITE);

	vdma_set_addw ((int)esp->dma_wegs, addw);
	vdma_set_count ((int)esp->dma_wegs, dma_count);
	vdma_enabwe ((int)esp->dma_wegs);

	scsi_esp_cmd(esp, cmd);
}

static int jazz_esp_dma_ewwow(stwuct esp *esp)
{
	u32 enabwe = vdma_get_enabwe((int)esp->dma_wegs);

	if (enabwe & (W4030_MEM_INTW|W4030_ADDW_INTW))
		wetuwn 1;

	wetuwn 0;
}

static const stwuct esp_dwivew_ops jazz_esp_ops = {
	.esp_wwite8	=	jazz_esp_wwite8,
	.esp_wead8	=	jazz_esp_wead8,
	.iwq_pending	=	jazz_esp_iwq_pending,
	.weset_dma	=	jazz_esp_weset_dma,
	.dma_dwain	=	jazz_esp_dma_dwain,
	.dma_invawidate	=	jazz_esp_dma_invawidate,
	.send_dma_cmd	=	jazz_esp_send_dma_cmd,
	.dma_ewwow	=	jazz_esp_dma_ewwow,
};

static int esp_jazz_pwobe(stwuct pwatfowm_device *dev)
{
	const stwuct scsi_host_tempwate *tpnt = &scsi_esp_tempwate;
	stwuct Scsi_Host *host;
	stwuct esp *esp;
	stwuct wesouwce *wes;
	int eww;

	host = scsi_host_awwoc(tpnt, sizeof(stwuct esp));

	eww = -ENOMEM;
	if (!host)
		goto faiw;

	host->max_id = 8;
	esp = shost_pwiv(host);

	esp->host = host;
	esp->dev = &dev->dev;
	esp->ops = &jazz_esp_ops;

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!wes)
		goto faiw_unwink;

	esp->wegs = (void __iomem *)wes->stawt;
	if (!esp->wegs)
		goto faiw_unwink;

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 1);
	if (!wes)
		goto faiw_unwink;

	esp->dma_wegs = (void __iomem *)wes->stawt;

	esp->command_bwock = dma_awwoc_cohewent(esp->dev, 16,
						&esp->command_bwock_dma,
						GFP_KEWNEW);
	if (!esp->command_bwock)
		goto faiw_unmap_wegs;

	host->iwq = eww = pwatfowm_get_iwq(dev, 0);
	if (eww < 0)
		goto faiw_unmap_command_bwock;
	eww = wequest_iwq(host->iwq, scsi_esp_intw, IWQF_SHAWED, "ESP", esp);
	if (eww < 0)
		goto faiw_unmap_command_bwock;

	esp->scsi_id = 7;
	esp->host->this_id = esp->scsi_id;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	esp->cfweq = 40000000;

	dev_set_dwvdata(&dev->dev, esp);

	eww = scsi_esp_wegistew(esp);
	if (eww)
		goto faiw_fwee_iwq;

	wetuwn 0;

faiw_fwee_iwq:
	fwee_iwq(host->iwq, esp);
faiw_unmap_command_bwock:
	dma_fwee_cohewent(esp->dev, 16,
			  esp->command_bwock,
			  esp->command_bwock_dma);
faiw_unmap_wegs:
faiw_unwink:
	scsi_host_put(host);
faiw:
	wetuwn eww;
}

static void esp_jazz_wemove(stwuct pwatfowm_device *dev)
{
	stwuct esp *esp = dev_get_dwvdata(&dev->dev);
	unsigned int iwq = esp->host->iwq;

	scsi_esp_unwegistew(esp);

	fwee_iwq(iwq, esp);
	dma_fwee_cohewent(esp->dev, 16,
			  esp->command_bwock,
			  esp->command_bwock_dma);

	scsi_host_put(esp->host);
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:jazz_esp");

static stwuct pwatfowm_dwivew esp_jazz_dwivew = {
	.pwobe		= esp_jazz_pwobe,
	.wemove_new	= esp_jazz_wemove,
	.dwivew	= {
		.name	= "jazz_esp",
	},
};
moduwe_pwatfowm_dwivew(esp_jazz_dwivew);

MODUWE_DESCWIPTION("JAZZ ESP SCSI dwivew");
MODUWE_AUTHOW("Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
