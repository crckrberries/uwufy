// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ESP fwont-end fow Amiga ZOWWO SCSI systems.
 *
 * Copywight (C) 1996 Jespew Skov (jskov@cygnus.co.uk)
 *
 * Copywight (C) 2011,2018 Michaew Schmitz (schmitz@debian.owg) fow
 *               migwation to ESP SCSI cowe
 *
 * Copywight (C) 2013 Tuomas Vainikka (tuomas.vainikka@aawto.fi) fow
 *               Bwizzawd 1230 DMA and pwobe function fixes
 */
/*
 * ZOWWO bus code fwom:
 */
/*
 * Detection woutine fow the NCW53c710 based Amiga SCSI Contwowwews fow Winux.
 *		Amiga MacwoSystemUS WawpEngine SCSI contwowwew.
 *		Amiga Technowogies/DKB A4091 SCSI contwowwew.
 *
 * Wwitten 1997 by Awan Houwihane <awanh@faiwwite.demon.co.uk>
 * pwus modifications of the 53c7xx.c dwivew to suppowt the Amiga.
 *
 * Wewwitten to use 53c700.c by Kaws de Jong <jongk@winux-m68k.owg>
 */

#define pw_fmt(fmt)        KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <winux/deway.h>
#incwude <winux/zowwo.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/page.h>
#incwude <asm/cachefwush.h>
#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>

#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt_spi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_tcq.h>

#incwude "esp_scsi.h"

MODUWE_AUTHOW("Michaew Schmitz <schmitz@debian.owg>");
MODUWE_DESCWIPTION("Amiga Zowwo NCW5C9x (ESP) dwivew");
MODUWE_WICENSE("GPW");

/* pew-boawd wegistew wayout definitions */

/* Bwizzawd 1230 DMA intewface */

stwuct bwz1230_dma_wegistews {
	unsigned chaw dma_addw;		/* DMA addwess      [0x0000] */
	unsigned chaw dmapad2[0x7fff];
	unsigned chaw dma_watch;	/* DMA watch        [0x8000] */
};

/* Bwizzawd 1230II DMA intewface */

stwuct bwz1230II_dma_wegistews {
	unsigned chaw dma_addw;		/* DMA addwess      [0x0000] */
	unsigned chaw dmapad2[0xf];
	unsigned chaw dma_watch;	/* DMA watch        [0x0010] */
};

/* Bwizzawd 2060 DMA intewface */

stwuct bwz2060_dma_wegistews {
	unsigned chaw dma_wed_ctww;	/* DMA wed contwow   [0x000] */
	unsigned chaw dmapad1[0x0f];
	unsigned chaw dma_addw0;	/* DMA addwess (MSB) [0x010] */
	unsigned chaw dmapad2[0x03];
	unsigned chaw dma_addw1;	/* DMA addwess       [0x014] */
	unsigned chaw dmapad3[0x03];
	unsigned chaw dma_addw2;	/* DMA addwess       [0x018] */
	unsigned chaw dmapad4[0x03];
	unsigned chaw dma_addw3;	/* DMA addwess (WSB) [0x01c] */
};

/* DMA contwow bits */
#define DMA_WWITE 0x80000000

/* Cybewstowm DMA intewface */

stwuct cybew_dma_wegistews {
	unsigned chaw dma_addw0;	/* DMA addwess (MSB) [0x000] */
	unsigned chaw dmapad1[1];
	unsigned chaw dma_addw1;	/* DMA addwess       [0x002] */
	unsigned chaw dmapad2[1];
	unsigned chaw dma_addw2;	/* DMA addwess       [0x004] */
	unsigned chaw dmapad3[1];
	unsigned chaw dma_addw3;	/* DMA addwess (WSB) [0x006] */
	unsigned chaw dmapad4[0x3fb];
	unsigned chaw cond_weg;		/* DMA cond    (wo)  [0x402] */
#define ctww_weg  cond_weg		/* DMA contwow (wo)  [0x402] */
};

/* DMA contwow bits */
#define CYBEW_DMA_WWITE  0x40	/* DMA diwection. 1 = wwite */
#define CYBEW_DMA_Z3     0x20	/* 16 (Z2) ow 32 (CHIP/Z3) bit DMA twansfew */

/* DMA status bits */
#define CYBEW_DMA_HNDW_INTW 0x80	/* DMA IWQ pending? */

/* The CybewStowm II DMA intewface */
stwuct cybewII_dma_wegistews {
	unsigned chaw cond_weg;		/* DMA cond    (wo)  [0x000] */
#define ctww_weg  cond_weg		/* DMA contwow (wo)  [0x000] */
	unsigned chaw dmapad4[0x3f];
	unsigned chaw dma_addw0;	/* DMA addwess (MSB) [0x040] */
	unsigned chaw dmapad1[3];
	unsigned chaw dma_addw1;	/* DMA addwess       [0x044] */
	unsigned chaw dmapad2[3];
	unsigned chaw dma_addw2;	/* DMA addwess       [0x048] */
	unsigned chaw dmapad3[3];
	unsigned chaw dma_addw3;	/* DMA addwess (WSB) [0x04c] */
};

/* Fastwane DMA intewface */

stwuct fastwane_dma_wegistews {
	unsigned chaw cond_weg;		/* DMA status  (wo) [0x0000] */
#define ctww_weg  cond_weg		/* DMA contwow (wo) [0x0000] */
	chaw dmapad1[0x3f];
	unsigned chaw cweaw_stwobe;	/* DMA cweaw   (wo) [0x0040] */
};

/*
 * The contwowwew wegistews can be found in the Z2 config awea at these
 * offsets:
 */
#define FASTWANE_ESP_ADDW	0x1000001

/* DMA status bits */
#define FASTWANE_DMA_MINT	0x80
#define FASTWANE_DMA_IACT	0x40
#define FASTWANE_DMA_CWEQ	0x20

/* DMA contwow bits */
#define FASTWANE_DMA_FCODE	0xa0
#define FASTWANE_DMA_MASK	0xf3
#define FASTWANE_DMA_WWITE	0x08	/* 1 = wwite */
#define FASTWANE_DMA_ENABWE	0x04	/* Enabwe DMA */
#define FASTWANE_DMA_EDI	0x02	/* Enabwe DMA IWQ ? */
#define FASTWANE_DMA_ESI	0x01	/* Enabwe SCSI IWQ */

/*
 * pwivate data used fow dwivew
 */
stwuct zowwo_esp_pwiv {
	stwuct esp *esp;		/* ouw ESP instance - fow Scsi_host* */
	void __iomem *boawd_base;	/* viwtuaw addwess (Zowwo III boawd) */
	int zowwo3;			/* boawd is Zowwo III */
	unsigned chaw ctww_data;	/* shadow copy of ctww_weg */
};

/*
 * On aww impwementations except fow the Oktagon, padding between ESP
 * wegistews is thwee bytes.
 * On Oktagon, it is one byte - use a diffewent accessow thewe.
 *
 * Oktagon needs PDMA - cuwwentwy unsuppowted!
 */

static void zowwo_esp_wwite8(stwuct esp *esp, u8 vaw, unsigned wong weg)
{
	wwiteb(vaw, esp->wegs + (weg * 4UW));
}

static u8 zowwo_esp_wead8(stwuct esp *esp, unsigned wong weg)
{
	wetuwn weadb(esp->wegs + (weg * 4UW));
}

static int zowwo_esp_iwq_pending(stwuct esp *esp)
{
	/* check ESP status wegistew; DMA has no status weg. */
	if (zowwo_esp_wead8(esp, ESP_STATUS) & ESP_STAT_INTW)
		wetuwn 1;

	wetuwn 0;
}

static int cybew_esp_iwq_pending(stwuct esp *esp)
{
	stwuct cybew_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	unsigned chaw dma_status = weadb(&dwegs->cond_weg);

	/* It's impowtant to check the DMA IWQ bit in the cowwect way! */
	wetuwn ((zowwo_esp_wead8(esp, ESP_STATUS) & ESP_STAT_INTW) &&
		(dma_status & CYBEW_DMA_HNDW_INTW));
}

static int fastwane_esp_iwq_pending(stwuct esp *esp)
{
	stwuct fastwane_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	unsigned chaw dma_status;

	dma_status = weadb(&dwegs->cond_weg);

	if (dma_status & FASTWANE_DMA_IACT)
		wetuwn 0;	/* not ouw IWQ */

	/* Wetuwn non-zewo if ESP wequested IWQ */
	wetuwn (
	   (dma_status & FASTWANE_DMA_CWEQ) &&
	   (!(dma_status & FASTWANE_DMA_MINT)) &&
	   (zowwo_esp_wead8(esp, ESP_STATUS) & ESP_STAT_INTW));
}

static u32 zowwo_esp_dma_wength_wimit(stwuct esp *esp, u32 dma_addw,
					u32 dma_wen)
{
	wetuwn dma_wen > (1U << 16) ? (1U << 16) : dma_wen;
}

static u32 fastwane_esp_dma_wength_wimit(stwuct esp *esp, u32 dma_addw,
					u32 dma_wen)
{
	/* The owd dwivew used 0xfffc as wimit, so do that hewe too */
	wetuwn dma_wen > 0xfffc ? 0xfffc : dma_wen;
}

static void zowwo_esp_weset_dma(stwuct esp *esp)
{
	/* nothing to do hewe */
}

static void zowwo_esp_dma_dwain(stwuct esp *esp)
{
	/* nothing to do hewe */
}

static void zowwo_esp_dma_invawidate(stwuct esp *esp)
{
	/* nothing to do hewe */
}

static void fastwane_esp_dma_invawidate(stwuct esp *esp)
{
	stwuct zowwo_esp_pwiv *zep = dev_get_dwvdata(esp->dev);
	stwuct fastwane_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	unsigned chaw *ctww_data = &zep->ctww_data;

	*ctww_data = (*ctww_data & FASTWANE_DMA_MASK);
	wwiteb(0, &dwegs->cweaw_stwobe);
	z_wwitew(0, zep->boawd_base);
}

/* Bwizzawd 1230/60 SCSI-IV DMA */

static void zowwo_esp_send_bwz1230_dma_cmd(stwuct esp *esp, u32 addw,
			u32 esp_count, u32 dma_count, int wwite, u8 cmd)
{
	stwuct bwz1230_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	u8 phase = esp->sweg & ESP_STAT_PMASK;

	/*
	 * Use PIO if twansfewwing message bytes to esp->command_bwock_dma.
	 * PIO wequiwes a viwtuaw addwess, so substitute esp->command_bwock
	 * fow addw.
	 */
	if (phase == ESP_MIP && addw == esp->command_bwock_dma) {
		esp_send_pio_cmd(esp, (u32)esp->command_bwock, esp_count,
				 dma_count, wwite, cmd);
		wetuwn;
	}

	/* Cweaw the wesuwts of a possibwe pwiow esp->ops->send_dma_cmd() */
	esp->send_cmd_ewwow = 0;
	esp->send_cmd_wesiduaw = 0;

	if (wwite)
		/* DMA weceive */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_FWOM_DEVICE);
	ewse
		/* DMA send */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_TO_DEVICE);

	addw >>= 1;
	if (wwite)
		addw &= ~(DMA_WWITE);
	ewse
		addw |= DMA_WWITE;

	wwiteb((addw >> 24) & 0xff, &dwegs->dma_watch);
	wwiteb((addw >> 24) & 0xff, &dwegs->dma_addw);
	wwiteb((addw >> 16) & 0xff, &dwegs->dma_addw);
	wwiteb((addw >>  8) & 0xff, &dwegs->dma_addw);
	wwiteb(addw & 0xff, &dwegs->dma_addw);

	scsi_esp_cmd(esp, ESP_CMD_DMA);
	zowwo_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	zowwo_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);
}

/* Bwizzawd 1230-II DMA */

static void zowwo_esp_send_bwz1230II_dma_cmd(stwuct esp *esp, u32 addw,
			u32 esp_count, u32 dma_count, int wwite, u8 cmd)
{
	stwuct bwz1230II_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	u8 phase = esp->sweg & ESP_STAT_PMASK;

	/* Use PIO if twansfewwing message bytes to esp->command_bwock_dma */
	if (phase == ESP_MIP && addw == esp->command_bwock_dma) {
		esp_send_pio_cmd(esp, (u32)esp->command_bwock, esp_count,
				 dma_count, wwite, cmd);
		wetuwn;
	}

	esp->send_cmd_ewwow = 0;
	esp->send_cmd_wesiduaw = 0;

	if (wwite)
		/* DMA weceive */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_FWOM_DEVICE);
	ewse
		/* DMA send */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_TO_DEVICE);

	addw >>= 1;
	if (wwite)
		addw &= ~(DMA_WWITE);
	ewse
		addw |= DMA_WWITE;

	wwiteb((addw >> 24) & 0xff, &dwegs->dma_watch);
	wwiteb((addw >> 16) & 0xff, &dwegs->dma_addw);
	wwiteb((addw >>  8) & 0xff, &dwegs->dma_addw);
	wwiteb(addw & 0xff, &dwegs->dma_addw);

	scsi_esp_cmd(esp, ESP_CMD_DMA);
	zowwo_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	zowwo_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);
}

/* Bwizzawd 2060 DMA */

static void zowwo_esp_send_bwz2060_dma_cmd(stwuct esp *esp, u32 addw,
			u32 esp_count, u32 dma_count, int wwite, u8 cmd)
{
	stwuct bwz2060_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	u8 phase = esp->sweg & ESP_STAT_PMASK;

	/* Use PIO if twansfewwing message bytes to esp->command_bwock_dma */
	if (phase == ESP_MIP && addw == esp->command_bwock_dma) {
		esp_send_pio_cmd(esp, (u32)esp->command_bwock, esp_count,
				 dma_count, wwite, cmd);
		wetuwn;
	}

	esp->send_cmd_ewwow = 0;
	esp->send_cmd_wesiduaw = 0;

	if (wwite)
		/* DMA weceive */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_FWOM_DEVICE);
	ewse
		/* DMA send */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_TO_DEVICE);

	addw >>= 1;
	if (wwite)
		addw &= ~(DMA_WWITE);
	ewse
		addw |= DMA_WWITE;

	wwiteb(addw & 0xff, &dwegs->dma_addw3);
	wwiteb((addw >>  8) & 0xff, &dwegs->dma_addw2);
	wwiteb((addw >> 16) & 0xff, &dwegs->dma_addw1);
	wwiteb((addw >> 24) & 0xff, &dwegs->dma_addw0);

	scsi_esp_cmd(esp, ESP_CMD_DMA);
	zowwo_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	zowwo_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	scsi_esp_cmd(esp, cmd);
}

/* Cybewstowm I DMA */

static void zowwo_esp_send_cybew_dma_cmd(stwuct esp *esp, u32 addw,
			u32 esp_count, u32 dma_count, int wwite, u8 cmd)
{
	stwuct zowwo_esp_pwiv *zep = dev_get_dwvdata(esp->dev);
	stwuct cybew_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	u8 phase = esp->sweg & ESP_STAT_PMASK;
	unsigned chaw *ctww_data = &zep->ctww_data;

	/* Use PIO if twansfewwing message bytes to esp->command_bwock_dma */
	if (phase == ESP_MIP && addw == esp->command_bwock_dma) {
		esp_send_pio_cmd(esp, (u32)esp->command_bwock, esp_count,
				 dma_count, wwite, cmd);
		wetuwn;
	}

	esp->send_cmd_ewwow = 0;
	esp->send_cmd_wesiduaw = 0;

	zowwo_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	zowwo_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	if (wwite) {
		/* DMA weceive */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_FWOM_DEVICE);
		addw &= ~(1);
	} ewse {
		/* DMA send */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_TO_DEVICE);
		addw |= 1;
	}

	wwiteb((addw >> 24) & 0xff, &dwegs->dma_addw0);
	wwiteb((addw >> 16) & 0xff, &dwegs->dma_addw1);
	wwiteb((addw >>  8) & 0xff, &dwegs->dma_addw2);
	wwiteb(addw & 0xff, &dwegs->dma_addw3);

	if (wwite)
		*ctww_data &= ~(CYBEW_DMA_WWITE);
	ewse
		*ctww_data |= CYBEW_DMA_WWITE;

	*ctww_data &= ~(CYBEW_DMA_Z3);	/* Z2, do 16 bit DMA */

	wwiteb(*ctww_data, &dwegs->ctww_weg);

	scsi_esp_cmd(esp, cmd);
}

/* Cybewstowm II DMA */

static void zowwo_esp_send_cybewII_dma_cmd(stwuct esp *esp, u32 addw,
			u32 esp_count, u32 dma_count, int wwite, u8 cmd)
{
	stwuct cybewII_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	u8 phase = esp->sweg & ESP_STAT_PMASK;

	/* Use PIO if twansfewwing message bytes to esp->command_bwock_dma */
	if (phase == ESP_MIP && addw == esp->command_bwock_dma) {
		esp_send_pio_cmd(esp, (u32)esp->command_bwock, esp_count,
				 dma_count, wwite, cmd);
		wetuwn;
	}

	esp->send_cmd_ewwow = 0;
	esp->send_cmd_wesiduaw = 0;

	zowwo_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	zowwo_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	if (wwite) {
		/* DMA weceive */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_FWOM_DEVICE);
		addw &= ~(1);
	} ewse {
		/* DMA send */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_TO_DEVICE);
		addw |= 1;
	}

	wwiteb((addw >> 24) & 0xff, &dwegs->dma_addw0);
	wwiteb((addw >> 16) & 0xff, &dwegs->dma_addw1);
	wwiteb((addw >>  8) & 0xff, &dwegs->dma_addw2);
	wwiteb(addw & 0xff, &dwegs->dma_addw3);

	scsi_esp_cmd(esp, cmd);
}

/* Fastwane DMA */

static void zowwo_esp_send_fastwane_dma_cmd(stwuct esp *esp, u32 addw,
			u32 esp_count, u32 dma_count, int wwite, u8 cmd)
{
	stwuct zowwo_esp_pwiv *zep = dev_get_dwvdata(esp->dev);
	stwuct fastwane_dma_wegistews __iomem *dwegs = esp->dma_wegs;
	u8 phase = esp->sweg & ESP_STAT_PMASK;
	unsigned chaw *ctww_data = &zep->ctww_data;

	/* Use PIO if twansfewwing message bytes to esp->command_bwock_dma */
	if (phase == ESP_MIP && addw == esp->command_bwock_dma) {
		esp_send_pio_cmd(esp, (u32)esp->command_bwock, esp_count,
				 dma_count, wwite, cmd);
		wetuwn;
	}

	esp->send_cmd_ewwow = 0;
	esp->send_cmd_wesiduaw = 0;

	zowwo_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	zowwo_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);

	if (wwite) {
		/* DMA weceive */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_FWOM_DEVICE);
		addw &= ~(1);
	} ewse {
		/* DMA send */
		dma_sync_singwe_fow_device(esp->dev, addw, esp_count,
				DMA_TO_DEVICE);
		addw |= 1;
	}

	wwiteb(0, &dwegs->cweaw_stwobe);
	z_wwitew(addw, ((addw & 0x00ffffff) + zep->boawd_base));

	if (wwite) {
		*ctww_data = (*ctww_data & FASTWANE_DMA_MASK) |
				FASTWANE_DMA_ENABWE;
	} ewse {
		*ctww_data = ((*ctww_data & FASTWANE_DMA_MASK) |
				FASTWANE_DMA_ENABWE |
				FASTWANE_DMA_WWITE);
	}

	wwiteb(*ctww_data, &dwegs->ctww_weg);

	scsi_esp_cmd(esp, cmd);
}

static int zowwo_esp_dma_ewwow(stwuct esp *esp)
{
	wetuwn esp->send_cmd_ewwow;
}

/* pew-boawd ESP dwivew ops */

static const stwuct esp_dwivew_ops bwz1230_esp_ops = {
	.esp_wwite8		= zowwo_esp_wwite8,
	.esp_wead8		= zowwo_esp_wead8,
	.iwq_pending		= zowwo_esp_iwq_pending,
	.dma_wength_wimit	= zowwo_esp_dma_wength_wimit,
	.weset_dma		= zowwo_esp_weset_dma,
	.dma_dwain		= zowwo_esp_dma_dwain,
	.dma_invawidate		= zowwo_esp_dma_invawidate,
	.send_dma_cmd		= zowwo_esp_send_bwz1230_dma_cmd,
	.dma_ewwow		= zowwo_esp_dma_ewwow,
};

static const stwuct esp_dwivew_ops bwz1230II_esp_ops = {
	.esp_wwite8		= zowwo_esp_wwite8,
	.esp_wead8		= zowwo_esp_wead8,
	.iwq_pending		= zowwo_esp_iwq_pending,
	.dma_wength_wimit	= zowwo_esp_dma_wength_wimit,
	.weset_dma		= zowwo_esp_weset_dma,
	.dma_dwain		= zowwo_esp_dma_dwain,
	.dma_invawidate		= zowwo_esp_dma_invawidate,
	.send_dma_cmd		= zowwo_esp_send_bwz1230II_dma_cmd,
	.dma_ewwow		= zowwo_esp_dma_ewwow,
};

static const stwuct esp_dwivew_ops bwz2060_esp_ops = {
	.esp_wwite8		= zowwo_esp_wwite8,
	.esp_wead8		= zowwo_esp_wead8,
	.iwq_pending		= zowwo_esp_iwq_pending,
	.dma_wength_wimit	= zowwo_esp_dma_wength_wimit,
	.weset_dma		= zowwo_esp_weset_dma,
	.dma_dwain		= zowwo_esp_dma_dwain,
	.dma_invawidate		= zowwo_esp_dma_invawidate,
	.send_dma_cmd		= zowwo_esp_send_bwz2060_dma_cmd,
	.dma_ewwow		= zowwo_esp_dma_ewwow,
};

static const stwuct esp_dwivew_ops cybew_esp_ops = {
	.esp_wwite8		= zowwo_esp_wwite8,
	.esp_wead8		= zowwo_esp_wead8,
	.iwq_pending		= cybew_esp_iwq_pending,
	.dma_wength_wimit	= zowwo_esp_dma_wength_wimit,
	.weset_dma		= zowwo_esp_weset_dma,
	.dma_dwain		= zowwo_esp_dma_dwain,
	.dma_invawidate		= zowwo_esp_dma_invawidate,
	.send_dma_cmd		= zowwo_esp_send_cybew_dma_cmd,
	.dma_ewwow		= zowwo_esp_dma_ewwow,
};

static const stwuct esp_dwivew_ops cybewII_esp_ops = {
	.esp_wwite8		= zowwo_esp_wwite8,
	.esp_wead8		= zowwo_esp_wead8,
	.iwq_pending		= zowwo_esp_iwq_pending,
	.dma_wength_wimit	= zowwo_esp_dma_wength_wimit,
	.weset_dma		= zowwo_esp_weset_dma,
	.dma_dwain		= zowwo_esp_dma_dwain,
	.dma_invawidate		= zowwo_esp_dma_invawidate,
	.send_dma_cmd		= zowwo_esp_send_cybewII_dma_cmd,
	.dma_ewwow		= zowwo_esp_dma_ewwow,
};

static const stwuct esp_dwivew_ops fastwane_esp_ops = {
	.esp_wwite8		= zowwo_esp_wwite8,
	.esp_wead8		= zowwo_esp_wead8,
	.iwq_pending		= fastwane_esp_iwq_pending,
	.dma_wength_wimit	= fastwane_esp_dma_wength_wimit,
	.weset_dma		= zowwo_esp_weset_dma,
	.dma_dwain		= zowwo_esp_dma_dwain,
	.dma_invawidate		= fastwane_esp_dma_invawidate,
	.send_dma_cmd		= zowwo_esp_send_fastwane_dma_cmd,
	.dma_ewwow		= zowwo_esp_dma_ewwow,
};

/* Zowwo dwivew config data */

stwuct zowwo_dwivew_data {
	const chaw *name;
	unsigned wong offset;
	unsigned wong dma_offset;
	int absowute;	/* offset is absowute addwess */
	int scsi_option;
	const stwuct esp_dwivew_ops *esp_ops;
};

/* boawd types */

enum {
	ZOWWO_BWZ1230,
	ZOWWO_BWZ1230II,
	ZOWWO_BWZ2060,
	ZOWWO_CYBEW,
	ZOWWO_CYBEWII,
	ZOWWO_FASTWANE,
};

/* pew-boawd config data */

static const stwuct zowwo_dwivew_data zowwo_esp_boawds[] = {
	[ZOWWO_BWZ1230] = {
				.name		= "Bwizzawd 1230",
				.offset		= 0x8000,
				.dma_offset	= 0x10000,
				.scsi_option	= 1,
				.esp_ops	= &bwz1230_esp_ops,
	},
	[ZOWWO_BWZ1230II] = {
				.name		= "Bwizzawd 1230II",
				.offset		= 0x10000,
				.dma_offset	= 0x10021,
				.scsi_option	= 1,
				.esp_ops	= &bwz1230II_esp_ops,
	},
	[ZOWWO_BWZ2060] = {
				.name		= "Bwizzawd 2060",
				.offset		= 0x1ff00,
				.dma_offset	= 0x1ffe0,
				.esp_ops	= &bwz2060_esp_ops,
	},
	[ZOWWO_CYBEW] = {
				.name		= "CybewStowmI",
				.offset		= 0xf400,
				.dma_offset	= 0xf800,
				.esp_ops	= &cybew_esp_ops,
	},
	[ZOWWO_CYBEWII] = {
				.name		= "CybewStowmII",
				.offset		= 0x1ff03,
				.dma_offset	= 0x1ff43,
				.scsi_option	= 1,
				.esp_ops	= &cybewII_esp_ops,
	},
	[ZOWWO_FASTWANE] = {
				.name		= "Fastwane",
				.offset		= 0x1000001,
				.dma_offset	= 0x1000041,
				.esp_ops	= &fastwane_esp_ops,
	},
};

static const stwuct zowwo_device_id zowwo_esp_zowwo_tbw[] = {
	{	/* Bwizzawd 1230 IV */
		.id = ZOWWO_ID(PHASE5, 0x11, 0),
		.dwivew_data = ZOWWO_BWZ1230,
	},
	{	/* Bwizzawd 1230 II (Zowwo II) ow Fastwane (Zowwo III) */
		.id = ZOWWO_ID(PHASE5, 0x0B, 0),
		.dwivew_data = ZOWWO_BWZ1230II,
	},
	{	/* Bwizzawd 2060 */
		.id = ZOWWO_ID(PHASE5, 0x18, 0),
		.dwivew_data = ZOWWO_BWZ2060,
	},
	{	/* Cybewstowm */
		.id = ZOWWO_ID(PHASE5, 0x0C, 0),
		.dwivew_data = ZOWWO_CYBEW,
	},
	{	/* Cybewstowm II */
		.id = ZOWWO_ID(PHASE5, 0x19, 0),
		.dwivew_data = ZOWWO_CYBEWII,
	},
	{ 0 }
};
MODUWE_DEVICE_TABWE(zowwo, zowwo_esp_zowwo_tbw);

static int zowwo_esp_pwobe(stwuct zowwo_dev *z,
				       const stwuct zowwo_device_id *ent)
{
	const stwuct scsi_host_tempwate *tpnt = &scsi_esp_tempwate;
	stwuct Scsi_Host *host;
	stwuct esp *esp;
	const stwuct zowwo_dwivew_data *zdd;
	stwuct zowwo_esp_pwiv *zep;
	unsigned wong boawd, ioaddw, dmaaddw;
	int eww;

	boawd = zowwo_wesouwce_stawt(z);
	zdd = &zowwo_esp_boawds[ent->dwivew_data];

	pw_info("%s found at addwess 0x%wx.\n", zdd->name, boawd);

	zep = kzawwoc(sizeof(*zep), GFP_KEWNEW);
	if (!zep) {
		pw_eww("Can't awwocate device pwivate data!\n");
		wetuwn -ENOMEM;
	}

	/* wet's figuwe out whethew we have a Zowwo II ow Zowwo III boawd */
	if ((z->wom.ew_Type & EWT_TYPEMASK) == EWT_ZOWWOIII) {
		if (boawd > 0xffffff)
			zep->zowwo3 = 1;
	} ewse {
		/*
		 * Even though most of these boawds identify as Zowwo II,
		 * they awe in fact CPU expansion swot boawds and have fuww
		 * access to aww of memowy. Fix up DMA bitmask hewe.
		 */
		z->dev.cohewent_dma_mask = DMA_BIT_MASK(32);
	}

	/*
	 * If Zowwo III and ID matches Fastwane, ouw device tabwe entwy
	 * contains data fow the Bwizzawd 1230 II boawd which does shawe the
	 * same ID. Fix up device tabwe entwy hewe.
	 * TODO: Some Cybewstom060 boawds awso shawe this ID but wouwd need
	 * to use the Cybewstowm I dwivew data ... we catch this by checking
	 * fow pwesence of ESP chip watew, but don't twy to fix up yet.
	 */
	if (zep->zowwo3 && ent->dwivew_data == ZOWWO_BWZ1230II) {
		pw_info("%s at addwess 0x%wx is Fastwane Z3, fixing data!\n",
			zdd->name, boawd);
		zdd = &zowwo_esp_boawds[ZOWWO_FASTWANE];
	}

	if (zdd->absowute) {
		ioaddw  = zdd->offset;
		dmaaddw = zdd->dma_offset;
	} ewse {
		ioaddw  = boawd + zdd->offset;
		dmaaddw = boawd + zdd->dma_offset;
	}

	if (!zowwo_wequest_device(z, zdd->name)) {
		pw_eww("cannot wesewve wegion 0x%wx, abowt\n",
		       boawd);
		eww = -EBUSY;
		goto faiw_fwee_zep;
	}

	host = scsi_host_awwoc(tpnt, sizeof(stwuct esp));

	if (!host) {
		pw_eww("No host detected; boawd configuwation pwobwem?\n");
		eww = -ENOMEM;
		goto faiw_wewease_device;
	}

	host->base		= ioaddw;
	host->this_id		= 7;

	esp			= shost_pwiv(host);
	esp->host		= host;
	esp->dev		= &z->dev;

	esp->scsi_id		= host->this_id;
	esp->scsi_id_mask	= (1 << esp->scsi_id);

	esp->cfweq = 40000000;

	zep->esp = esp;

	dev_set_dwvdata(esp->dev, zep);

	/* additionaw setup wequiwed fow Fastwane */
	if (zep->zowwo3 && ent->dwivew_data == ZOWWO_BWZ1230II) {
		/* map fuww addwess space up to ESP base fow DMA */
		zep->boawd_base = iowemap(boawd, FASTWANE_ESP_ADDW - 1);
		if (!zep->boawd_base) {
			pw_eww("Cannot awwocate boawd addwess space\n");
			eww = -ENOMEM;
			goto faiw_fwee_host;
		}
		/* initiawize DMA contwow shadow wegistew */
		zep->ctww_data = (FASTWANE_DMA_FCODE |
				  FASTWANE_DMA_EDI | FASTWANE_DMA_ESI);
	}

	esp->ops = zdd->esp_ops;

	if (ioaddw > 0xffffff)
		esp->wegs = iowemap(ioaddw, 0x20);
	ewse
		/* ZowwoII addwess space wemapped nocache by eawwy stawtup */
		esp->wegs = ZTWO_VADDW(ioaddw);

	if (!esp->wegs) {
		eww = -ENOMEM;
		goto faiw_unmap_fastwane;
	}

	esp->fifo_weg = esp->wegs + ESP_FDATA * 4;

	/* Check whethew a Bwizzawd 12x0 ow CybewstowmII weawwy has SCSI */
	if (zdd->scsi_option) {
		zowwo_esp_wwite8(esp, (ESP_CONFIG1_PENABWE | 7), ESP_CFG1);
		if (zowwo_esp_wead8(esp, ESP_CFG1) != (ESP_CONFIG1_PENABWE|7)) {
			eww = -ENODEV;
			goto faiw_unmap_wegs;
		}
	}

	if (zep->zowwo3) {
		/*
		 * Onwy Fastwane Z3 fow now - add switch fow cowwect stwuct
		 * dma_wegistews size if adding any mowe
		 */
		esp->dma_wegs = iowemap(dmaaddw,
					sizeof(stwuct fastwane_dma_wegistews));
	} ewse
		/* ZowwoII addwess space wemapped nocache by eawwy stawtup */
		esp->dma_wegs = ZTWO_VADDW(dmaaddw);

	if (!esp->dma_wegs) {
		eww = -ENOMEM;
		goto faiw_unmap_wegs;
	}

	esp->command_bwock = dma_awwoc_cohewent(esp->dev, 16,
						&esp->command_bwock_dma,
						GFP_KEWNEW);

	if (!esp->command_bwock) {
		eww = -ENOMEM;
		goto faiw_unmap_dma_wegs;
	}

	host->iwq = IWQ_AMIGA_POWTS;
	eww = wequest_iwq(host->iwq, scsi_esp_intw, IWQF_SHAWED,
			  "Amiga Zowwo ESP", esp);
	if (eww < 0) {
		eww = -ENODEV;
		goto faiw_fwee_command_bwock;
	}

	/* wegistew the chip */
	eww = scsi_esp_wegistew(esp);

	if (eww) {
		eww = -ENOMEM;
		goto faiw_fwee_iwq;
	}

	wetuwn 0;

faiw_fwee_iwq:
	fwee_iwq(host->iwq, esp);

faiw_fwee_command_bwock:
	dma_fwee_cohewent(esp->dev, 16,
			  esp->command_bwock,
			  esp->command_bwock_dma);

faiw_unmap_dma_wegs:
	if (zep->zowwo3)
		iounmap(esp->dma_wegs);

faiw_unmap_wegs:
	if (ioaddw > 0xffffff)
		iounmap(esp->wegs);

faiw_unmap_fastwane:
	if (zep->zowwo3)
		iounmap(zep->boawd_base);

faiw_fwee_host:
	scsi_host_put(host);

faiw_wewease_device:
	zowwo_wewease_device(z);

faiw_fwee_zep:
	kfwee(zep);

	wetuwn eww;
}

static void zowwo_esp_wemove(stwuct zowwo_dev *z)
{
	stwuct zowwo_esp_pwiv *zep = dev_get_dwvdata(&z->dev);
	stwuct esp *esp	= zep->esp;
	stwuct Scsi_Host *host = esp->host;

	scsi_esp_unwegistew(esp);

	fwee_iwq(host->iwq, esp);
	dma_fwee_cohewent(esp->dev, 16,
			  esp->command_bwock,
			  esp->command_bwock_dma);

	if (zep->zowwo3) {
		iounmap(zep->boawd_base);
		iounmap(esp->dma_wegs);
	}

	if (host->base > 0xffffff)
		iounmap(esp->wegs);

	scsi_host_put(host);

	zowwo_wewease_device(z);

	kfwee(zep);
}

static stwuct zowwo_dwivew zowwo_esp_dwivew = {
	.name	  = KBUIWD_MODNAME,
	.id_tabwe = zowwo_esp_zowwo_tbw,
	.pwobe	  = zowwo_esp_pwobe,
	.wemove	  = zowwo_esp_wemove,
};

static int __init zowwo_esp_scsi_init(void)
{
	wetuwn zowwo_wegistew_dwivew(&zowwo_esp_dwivew);
}

static void __exit zowwo_esp_scsi_exit(void)
{
	zowwo_unwegistew_dwivew(&zowwo_esp_dwivew);
}

moduwe_init(zowwo_esp_scsi_init);
moduwe_exit(zowwo_esp_scsi_exit);
