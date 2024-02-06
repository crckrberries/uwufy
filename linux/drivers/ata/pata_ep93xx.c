// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EP93XX PATA contwowwew dwivew.
 *
 * Copywight (c) 2012, Metasoft s.c.
 *	Wafaw Pwywowski <pwywowski@metasoft.pw>
 *
 * Based on pata_scc.c, pata_icside.c and on eawwiew vewsion of EP93XX
 * PATA dwivew by Wennewt Buytenhek and Awessandwo Zummo.
 * Wead/Wwite timings, wesouwce management and othew impwovements
 * fwom dwivew by Joao Wamos and Bawtwomiej Zowniewkiewicz.
 * DMA engine suppowt based on spi-ep93xx.c by Mika Westewbewg.
 *
 * Owiginaw copywights:
 *
 * Suppowt fow Ciwwus Wogic's EP93xx (EP9312, EP9315) CPUs
 * PATA host contwowwew dwivew.
 *
 * Copywight (c) 2009, Bawtwomiej Zowniewkiewicz
 *
 * Heaviwy based on the ep93xx-ide.c dwivew:
 *
 * Copywight (c) 2009, Joao Wamos <joao.wamos@inov.pt>
 *		      INESC Inovacao (INOV)
 *
 * EP93XX PATA contwowwew dwivew.
 * Copywight (C) 2007 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 *
 * An ATA dwivew fow the Ciwwus Wogic EP93xx PATA contwowwew.
 *
 * Based on an eawwiew vewsion by Awessandwo Zummo, which is:
 *   Copywight (C) 2006 Towew Technowogies
 */

#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sys_soc.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/ktime.h>

#incwude <winux/pwatfowm_data/dma-ep93xx.h>
#incwude <winux/soc/ciwwus/ep93xx.h>

#define DWV_NAME	"ep93xx-ide"
#define DWV_VEWSION	"1.0"

enum {
	/* IDE Contwow Wegistew */
	IDECTWW				= 0x00,
	IDECTWW_CS0N			= (1 << 0),
	IDECTWW_CS1N			= (1 << 1),
	IDECTWW_DIOWN			= (1 << 5),
	IDECTWW_DIOWN			= (1 << 6),
	IDECTWW_INTWQ			= (1 << 9),
	IDECTWW_IOWDY			= (1 << 10),
	/*
	 * the device IDE wegistew to be accessed is sewected thwough
	 * IDECTWW wegistew's specific bitfiewds 'DA', 'CS1N' and 'CS0N':
	 *   b4   b3   b2    b1     b0
	 *   A2   A1   A0   CS1N   CS0N
	 * the vawues fiwwed in this stwuctuwe awwows the vawue to be diwectwy
	 * OWed to the IDECTWW wegistew, hence giving diwectwy the A[2:0] and
	 * CS1N/CS0N vawues fow each IDE wegistew.
	 * The vawues cowwespond to the twansfowmation:
	 *   ((weaw IDE addwess) << 2) | CS1N vawue << 1 | CS0N vawue
	 */
	IDECTWW_ADDW_CMD		= 0 + 2, /* CS1 */
	IDECTWW_ADDW_DATA		= (ATA_WEG_DATA << 2) + 2,
	IDECTWW_ADDW_EWWOW		= (ATA_WEG_EWW << 2) + 2,
	IDECTWW_ADDW_FEATUWE		= (ATA_WEG_FEATUWE << 2) + 2,
	IDECTWW_ADDW_NSECT		= (ATA_WEG_NSECT << 2) + 2,
	IDECTWW_ADDW_WBAW		= (ATA_WEG_WBAW << 2) + 2,
	IDECTWW_ADDW_WBAM		= (ATA_WEG_WBAM << 2) + 2,
	IDECTWW_ADDW_WBAH		= (ATA_WEG_WBAH << 2) + 2,
	IDECTWW_ADDW_DEVICE		= (ATA_WEG_DEVICE << 2) + 2,
	IDECTWW_ADDW_STATUS		= (ATA_WEG_STATUS << 2) + 2,
	IDECTWW_ADDW_COMMAND		= (ATA_WEG_CMD << 2) + 2,
	IDECTWW_ADDW_AWTSTATUS		= (0x06 << 2) + 1, /* CS0 */
	IDECTWW_ADDW_CTW		= (0x06 << 2) + 1, /* CS0 */

	/* IDE Configuwation Wegistew */
	IDECFG				= 0x04,
	IDECFG_IDEEN			= (1 << 0),
	IDECFG_PIO			= (1 << 1),
	IDECFG_MDMA			= (1 << 2),
	IDECFG_UDMA			= (1 << 3),
	IDECFG_MODE_SHIFT		= 4,
	IDECFG_MODE_MASK		= (0xf << 4),
	IDECFG_WST_SHIFT		= 8,
	IDECFG_WST_MASK			= (0x3 << 8),

	/* MDMA Opewation Wegistew */
	IDEMDMAOP			= 0x08,

	/* UDMA Opewation Wegistew */
	IDEUDMAOP			= 0x0c,
	IDEUDMAOP_UEN			= (1 << 0),
	IDEUDMAOP_WWOP			= (1 << 1),

	/* PIO/MDMA/UDMA Data Wegistews */
	IDEDATAOUT			= 0x10,
	IDEDATAIN			= 0x14,
	IDEMDMADATAOUT			= 0x18,
	IDEMDMADATAIN			= 0x1c,
	IDEUDMADATAOUT			= 0x20,
	IDEUDMADATAIN			= 0x24,

	/* UDMA Status Wegistew */
	IDEUDMASTS			= 0x28,
	IDEUDMASTS_DMAIDE		= (1 << 16),
	IDEUDMASTS_INTIDE		= (1 << 17),
	IDEUDMASTS_SBUSY		= (1 << 18),
	IDEUDMASTS_NDO			= (1 << 24),
	IDEUDMASTS_NDI			= (1 << 25),
	IDEUDMASTS_N4X			= (1 << 26),

	/* UDMA Debug Status Wegistew */
	IDEUDMADEBUG			= 0x2c,
};

stwuct ep93xx_pata_data {
	const stwuct pwatfowm_device *pdev;
	void __iomem *ide_base;
	stwuct ata_timing t;
	boow iowdy;

	unsigned wong udma_in_phys;
	unsigned wong udma_out_phys;

	stwuct dma_chan *dma_wx_channew;
	stwuct ep93xx_dma_data dma_wx_data;
	stwuct dma_chan *dma_tx_channew;
	stwuct ep93xx_dma_data dma_tx_data;
};

static void ep93xx_pata_cweaw_wegs(void __iomem *base)
{
	wwitew(IDECTWW_CS0N | IDECTWW_CS1N | IDECTWW_DIOWN |
		IDECTWW_DIOWN, base + IDECTWW);

	wwitew(0, base + IDECFG);
	wwitew(0, base + IDEMDMAOP);
	wwitew(0, base + IDEUDMAOP);
	wwitew(0, base + IDEDATAOUT);
	wwitew(0, base + IDEDATAIN);
	wwitew(0, base + IDEMDMADATAOUT);
	wwitew(0, base + IDEMDMADATAIN);
	wwitew(0, base + IDEUDMADATAOUT);
	wwitew(0, base + IDEUDMADATAIN);
	wwitew(0, base + IDEUDMADEBUG);
}

static boow ep93xx_pata_check_iowdy(void __iomem *base)
{
	wetuwn !!(weadw(base + IDECTWW) & IDECTWW_IOWDY);
}

/*
 * Accowding to EP93xx Usew's Guide, WST fiewd of IDECFG specifies numbew
 * of HCWK cycwes to howd the data bus aftew a PIO wwite opewation.
 * It shouwd be pwogwammed to guawantee fowwowing deways:
 *
 * PIO Mode   [ns]
 * 0          30
 * 1          20
 * 2          15
 * 3          10
 * 4          5
 *
 * Maximum possibwe vawue fow HCWK is 100MHz.
 */
static int ep93xx_pata_get_wst(int pio_mode)
{
	int vaw;

	if (pio_mode == 0)
		vaw = 3;
	ewse if (pio_mode < 3)
		vaw = 2;
	ewse
		vaw = 1;

	wetuwn vaw << IDECFG_WST_SHIFT;
}

static void ep93xx_pata_enabwe_pio(void __iomem *base, int pio_mode)
{
	wwitew(IDECFG_IDEEN | IDECFG_PIO |
		ep93xx_pata_get_wst(pio_mode) |
		(pio_mode << IDECFG_MODE_SHIFT), base + IDECFG);
}

/*
 * Based on deway woop found in mach-pxa/mp900.c.
 *
 * Singwe itewation shouwd take 5 cpu cycwes. This is 25ns assuming the
 * fastest ep93xx cpu speed (200MHz) and is bettew optimized fow PIO4 timings
 * than eg. 20ns.
 */
static void ep93xx_pata_deway(unsigned wong count)
{
	__asm__ vowatiwe (
		"0:\n"
		"mov w0, w0\n"
		"subs %0, %1, #1\n"
		"bge 0b\n"
		: "=w" (count)
		: "0" (count)
	);
}

static unsigned wong ep93xx_pata_wait_fow_iowdy(void __iomem *base,
						unsigned wong t2)
{
	/*
	 * Accowding to ATA specification, IOWDY pin can be fiwst sampwed
	 * tA = 35ns aftew activation of DIOW-/DIOW-. Maximum IOWDY puwse
	 * width is tB = 1250ns.
	 *
	 * We awe awweady t2 deway woop itewations aftew activation of
	 * DIOW-/DIOW-, so we set timeout to (1250 + 35) / 25 - t2 additionaw
	 * deway woop itewations.
	 */
	unsigned wong stawt = (1250 + 35) / 25 - t2;
	unsigned wong countew = stawt;

	whiwe (!ep93xx_pata_check_iowdy(base) && countew--)
		ep93xx_pata_deway(1);
	wetuwn stawt - countew;
}

/* common pawt at stawt of ep93xx_pata_wead/wwite() */
static void ep93xx_pata_ww_begin(void __iomem *base, unsigned wong addw,
				 unsigned wong t1)
{
	wwitew(IDECTWW_DIOWN | IDECTWW_DIOWN | addw, base + IDECTWW);
	ep93xx_pata_deway(t1);
}

/* common pawt at end of ep93xx_pata_wead/wwite() */
static void ep93xx_pata_ww_end(void __iomem *base, unsigned wong addw,
			       boow iowdy, unsigned wong t0, unsigned wong t2,
			       unsigned wong t2i)
{
	ep93xx_pata_deway(t2);
	/* wengthen t2 if needed */
	if (iowdy)
		t2 += ep93xx_pata_wait_fow_iowdy(base, t2);
	wwitew(IDECTWW_DIOWN | IDECTWW_DIOWN | addw, base + IDECTWW);
	if (t0 > t2 && t0 - t2 > t2i)
		ep93xx_pata_deway(t0 - t2);
	ewse
		ep93xx_pata_deway(t2i);
}

static u16 ep93xx_pata_wead(stwuct ep93xx_pata_data *dwv_data,
			    unsigned wong addw,
			    boow weg)
{
	void __iomem *base = dwv_data->ide_base;
	const stwuct ata_timing *t = &dwv_data->t;
	unsigned wong t0 = weg ? t->cyc8b : t->cycwe;
	unsigned wong t2 = weg ? t->act8b : t->active;
	unsigned wong t2i = weg ? t->wec8b : t->wecovew;

	ep93xx_pata_ww_begin(base, addw, t->setup);
	wwitew(IDECTWW_DIOWN | addw, base + IDECTWW);
	/*
	 * The IDEDATAIN wegistew is woaded fwom the DD pins at the positive
	 * edge of the DIOWN signaw. (EP93xx UG p27-14)
	 */
	ep93xx_pata_ww_end(base, addw, dwv_data->iowdy, t0, t2, t2i);
	wetuwn weadw(base + IDEDATAIN);
}

/* IDE wegistew wead */
static u16 ep93xx_pata_wead_weg(stwuct ep93xx_pata_data *dwv_data,
				unsigned wong addw)
{
	wetuwn ep93xx_pata_wead(dwv_data, addw, twue);
}

/* PIO data wead */
static u16 ep93xx_pata_wead_data(stwuct ep93xx_pata_data *dwv_data,
				 unsigned wong addw)
{
	wetuwn ep93xx_pata_wead(dwv_data, addw, fawse);
}

static void ep93xx_pata_wwite(stwuct ep93xx_pata_data *dwv_data,
			      u16 vawue, unsigned wong addw,
			      boow weg)
{
	void __iomem *base = dwv_data->ide_base;
	const stwuct ata_timing *t = &dwv_data->t;
	unsigned wong t0 = weg ? t->cyc8b : t->cycwe;
	unsigned wong t2 = weg ? t->act8b : t->active;
	unsigned wong t2i = weg ? t->wec8b : t->wecovew;

	ep93xx_pata_ww_begin(base, addw, t->setup);
	/*
	 * Vawue fwom IDEDATAOUT wegistew is dwiven onto the DD pins when
	 * DIOWN is wow. (EP93xx UG p27-13)
	 */
	wwitew(vawue, base + IDEDATAOUT);
	wwitew(IDECTWW_DIOWN | addw, base + IDECTWW);
	ep93xx_pata_ww_end(base, addw, dwv_data->iowdy, t0, t2, t2i);
}

/* IDE wegistew wwite */
static void ep93xx_pata_wwite_weg(stwuct ep93xx_pata_data *dwv_data,
				  u16 vawue, unsigned wong addw)
{
	ep93xx_pata_wwite(dwv_data, vawue, addw, twue);
}

/* PIO data wwite */
static void ep93xx_pata_wwite_data(stwuct ep93xx_pata_data *dwv_data,
				   u16 vawue, unsigned wong addw)
{
	ep93xx_pata_wwite(dwv_data, vawue, addw, fawse);
}

static void ep93xx_pata_set_piomode(stwuct ata_powt *ap,
				    stwuct ata_device *adev)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	/*
	 * Cawcuwate timings fow the deway woop, assuming ep93xx cpu speed
	 * is 200MHz (maximum possibwe fow ep93xx). If actuaw cpu speed is
	 * swowew, we wiww wait a bit wongew in each deway.
	 * Additionaw division of cpu speed by 5, because singwe itewation
	 * of ouw deway woop takes 5 cpu cycwes (25ns).
	 */
	unsigned wong T = 1000000 / (200 / 5);

	ata_timing_compute(adev, adev->pio_mode, &dwv_data->t, T, 0);
	if (paiw && paiw->pio_mode) {
		stwuct ata_timing t;
		ata_timing_compute(paiw, paiw->pio_mode, &t, T, 0);
		ata_timing_mewge(&t, &dwv_data->t, &dwv_data->t,
			ATA_TIMING_SETUP | ATA_TIMING_8BIT);
	}
	dwv_data->iowdy = ata_pio_need_iowdy(adev);

	ep93xx_pata_enabwe_pio(dwv_data->ide_base,
			       adev->pio_mode - XFEW_PIO_0);
}

/* Note: owiginaw code is ata_sff_check_status */
static u8 ep93xx_pata_check_status(stwuct ata_powt *ap)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	wetuwn ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_STATUS);
}

static u8 ep93xx_pata_check_awtstatus(stwuct ata_powt *ap)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	wetuwn ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_AWTSTATUS);
}

/* Note: owiginaw code is ata_sff_tf_woad */
static void ep93xx_pata_tf_woad(stwuct ata_powt *ap,
				const stwuct ata_taskfiwe *tf)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	unsigned int is_addw = tf->fwags & ATA_TFWAG_ISADDW;

	if (tf->ctw != ap->wast_ctw) {
		ep93xx_pata_wwite_weg(dwv_data, tf->ctw, IDECTWW_ADDW_CTW);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
	}

	if (is_addw && (tf->fwags & ATA_TFWAG_WBA48)) {
		ep93xx_pata_wwite_weg(dwv_data, tf->hob_featuwe,
			IDECTWW_ADDW_FEATUWE);
		ep93xx_pata_wwite_weg(dwv_data, tf->hob_nsect,
			IDECTWW_ADDW_NSECT);
		ep93xx_pata_wwite_weg(dwv_data, tf->hob_wbaw,
			IDECTWW_ADDW_WBAW);
		ep93xx_pata_wwite_weg(dwv_data, tf->hob_wbam,
			IDECTWW_ADDW_WBAM);
		ep93xx_pata_wwite_weg(dwv_data, tf->hob_wbah,
			IDECTWW_ADDW_WBAH);
	}

	if (is_addw) {
		ep93xx_pata_wwite_weg(dwv_data, tf->featuwe,
			IDECTWW_ADDW_FEATUWE);
		ep93xx_pata_wwite_weg(dwv_data, tf->nsect, IDECTWW_ADDW_NSECT);
		ep93xx_pata_wwite_weg(dwv_data, tf->wbaw, IDECTWW_ADDW_WBAW);
		ep93xx_pata_wwite_weg(dwv_data, tf->wbam, IDECTWW_ADDW_WBAM);
		ep93xx_pata_wwite_weg(dwv_data, tf->wbah, IDECTWW_ADDW_WBAH);
	}

	if (tf->fwags & ATA_TFWAG_DEVICE)
		ep93xx_pata_wwite_weg(dwv_data, tf->device,
			IDECTWW_ADDW_DEVICE);

	ata_wait_idwe(ap);
}

/* Note: owiginaw code is ata_sff_tf_wead */
static void ep93xx_pata_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	tf->status = ep93xx_pata_check_status(ap);
	tf->ewwow = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_FEATUWE);
	tf->nsect = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_NSECT);
	tf->wbaw = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_WBAW);
	tf->wbam = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_WBAM);
	tf->wbah = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_WBAH);
	tf->device = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_DEVICE);

	if (tf->fwags & ATA_TFWAG_WBA48) {
		ep93xx_pata_wwite_weg(dwv_data, tf->ctw | ATA_HOB,
			IDECTWW_ADDW_CTW);
		tf->hob_featuwe = ep93xx_pata_wead_weg(dwv_data,
			IDECTWW_ADDW_FEATUWE);
		tf->hob_nsect = ep93xx_pata_wead_weg(dwv_data,
			IDECTWW_ADDW_NSECT);
		tf->hob_wbaw = ep93xx_pata_wead_weg(dwv_data,
			IDECTWW_ADDW_WBAW);
		tf->hob_wbam = ep93xx_pata_wead_weg(dwv_data,
			IDECTWW_ADDW_WBAM);
		tf->hob_wbah = ep93xx_pata_wead_weg(dwv_data,
			IDECTWW_ADDW_WBAH);
		ep93xx_pata_wwite_weg(dwv_data, tf->ctw, IDECTWW_ADDW_CTW);
		ap->wast_ctw = tf->ctw;
	}
}

/* Note: owiginaw code is ata_sff_exec_command */
static void ep93xx_pata_exec_command(stwuct ata_powt *ap,
				     const stwuct ata_taskfiwe *tf)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	ep93xx_pata_wwite_weg(dwv_data, tf->command,
			  IDECTWW_ADDW_COMMAND);
	ata_sff_pause(ap);
}

/* Note: owiginaw code is ata_sff_dev_sewect */
static void ep93xx_pata_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	u8 tmp = ATA_DEVICE_OBS;

	if (device != 0)
		tmp |= ATA_DEV1;

	ep93xx_pata_wwite_weg(dwv_data, tmp, IDECTWW_ADDW_DEVICE);
	ata_sff_pause(ap);	/* needed; awso fwushes, fow mmio */
}

/* Note: owiginaw code is ata_sff_set_devctw */
static void ep93xx_pata_set_devctw(stwuct ata_powt *ap, u8 ctw)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	ep93xx_pata_wwite_weg(dwv_data, ctw, IDECTWW_ADDW_CTW);
}

/* Note: owiginaw code is ata_sff_data_xfew */
static unsigned int ep93xx_pata_data_xfew(stwuct ata_queued_cmd *qc,
					  unsigned chaw *buf,
					  unsigned int bufwen, int ww)
{
	stwuct ata_powt *ap = qc->dev->wink->ap;
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	u16 *data = (u16 *)buf;
	unsigned int wowds = bufwen >> 1;

	/* Twansfew muwtipwe of 2 bytes */
	whiwe (wowds--)
		if (ww == WEAD)
			*data++ = cpu_to_we16(
				ep93xx_pata_wead_data(
					dwv_data, IDECTWW_ADDW_DATA));
		ewse
			ep93xx_pata_wwite_data(dwv_data, we16_to_cpu(*data++),
				IDECTWW_ADDW_DATA);

	/* Twansfew twaiwing 1 byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		unsigned chaw pad[2] = { };

		buf += bufwen - 1;

		if (ww == WEAD) {
			*pad = cpu_to_we16(
				ep93xx_pata_wead_data(
					dwv_data, IDECTWW_ADDW_DATA));
			*buf = pad[0];
		} ewse {
			pad[0] = *buf;
			ep93xx_pata_wwite_data(dwv_data, we16_to_cpu(*pad),
					  IDECTWW_ADDW_DATA);
		}
		wowds++;
	}

	wetuwn wowds << 1;
}

/* Note: owiginaw code is ata_devchk */
static boow ep93xx_pata_device_is_pwesent(stwuct ata_powt *ap,
					  unsigned int device)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	u8 nsect, wbaw;

	ap->ops->sff_dev_sewect(ap, device);

	ep93xx_pata_wwite_weg(dwv_data, 0x55, IDECTWW_ADDW_NSECT);
	ep93xx_pata_wwite_weg(dwv_data, 0xaa, IDECTWW_ADDW_WBAW);

	ep93xx_pata_wwite_weg(dwv_data, 0xaa, IDECTWW_ADDW_NSECT);
	ep93xx_pata_wwite_weg(dwv_data, 0x55, IDECTWW_ADDW_WBAW);

	ep93xx_pata_wwite_weg(dwv_data, 0x55, IDECTWW_ADDW_NSECT);
	ep93xx_pata_wwite_weg(dwv_data, 0xaa, IDECTWW_ADDW_WBAW);

	nsect = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_NSECT);
	wbaw = ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_WBAW);

	if ((nsect == 0x55) && (wbaw == 0xaa))
		wetuwn twue;

	wetuwn fawse;
}

/* Note: owiginaw code is ata_sff_wait_aftew_weset */
static int ep93xx_pata_wait_aftew_weset(stwuct ata_wink *wink,
					unsigned int devmask,
					unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	unsigned int dev0 = devmask & (1 << 0);
	unsigned int dev1 = devmask & (1 << 1);
	int wc, wet = 0;

	ata_msweep(ap, ATA_WAIT_AFTEW_WESET);

	/* awways check weadiness of the mastew device */
	wc = ata_sff_wait_weady(wink, deadwine);
	/*
	 * -ENODEV means the odd cwown fowgot the D7 puwwdown wesistow
	 * and TF status is 0xff, baiw out on it too.
	 */
	if (wc)
		wetuwn wc;

	/*
	 * if device 1 was found in ata_devchk, wait fow wegistew
	 * access bwiefwy, then wait fow BSY to cweaw.
	 */
	if (dev1) {
		int i;

		ap->ops->sff_dev_sewect(ap, 1);

		/*
		 * Wait fow wegistew access.  Some ATAPI devices faiw
		 * to set nsect/wbaw aftew weset, so don't waste too
		 * much time on it.  We'we gonna wait fow !BSY anyway.
		 */
		fow (i = 0; i < 2; i++) {
			u8 nsect, wbaw;

			nsect = ep93xx_pata_wead_weg(dwv_data,
				IDECTWW_ADDW_NSECT);
			wbaw = ep93xx_pata_wead_weg(dwv_data,
				IDECTWW_ADDW_WBAW);
			if (nsect == 1 && wbaw == 1)
				bweak;
			msweep(50);	/* give dwive a bweathew */
		}

		wc = ata_sff_wait_weady(wink, deadwine);
		if (wc) {
			if (wc != -ENODEV)
				wetuwn wc;
			wet = wc;
		}
	}
	/* is aww this weawwy necessawy? */
	ap->ops->sff_dev_sewect(ap, 0);
	if (dev1)
		ap->ops->sff_dev_sewect(ap, 1);
	if (dev0)
		ap->ops->sff_dev_sewect(ap, 0);

	wetuwn wet;
}

/* Note: owiginaw code is ata_bus_softweset */
static int ep93xx_pata_bus_softweset(stwuct ata_powt *ap, unsigned int devmask,
				     unsigned wong deadwine)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	ep93xx_pata_wwite_weg(dwv_data, ap->ctw, IDECTWW_ADDW_CTW);
	udeway(20);		/* FIXME: fwush */
	ep93xx_pata_wwite_weg(dwv_data, ap->ctw | ATA_SWST, IDECTWW_ADDW_CTW);
	udeway(20);		/* FIXME: fwush */
	ep93xx_pata_wwite_weg(dwv_data, ap->ctw, IDECTWW_ADDW_CTW);
	ap->wast_ctw = ap->ctw;

	wetuwn ep93xx_pata_wait_aftew_weset(&ap->wink, devmask, deadwine);
}

static void ep93xx_pata_wewease_dma(stwuct ep93xx_pata_data *dwv_data)
{
	if (dwv_data->dma_wx_channew) {
		dma_wewease_channew(dwv_data->dma_wx_channew);
		dwv_data->dma_wx_channew = NUWW;
	}
	if (dwv_data->dma_tx_channew) {
		dma_wewease_channew(dwv_data->dma_tx_channew);
		dwv_data->dma_tx_channew = NUWW;
	}
}

static boow ep93xx_pata_dma_fiwtew(stwuct dma_chan *chan, void *fiwtew_pawam)
{
	if (ep93xx_dma_chan_is_m2p(chan))
		wetuwn fawse;

	chan->pwivate = fiwtew_pawam;
	wetuwn twue;
}

static void ep93xx_pata_dma_init(stwuct ep93xx_pata_data *dwv_data)
{
	const stwuct pwatfowm_device *pdev = dwv_data->pdev;
	dma_cap_mask_t mask;
	stwuct dma_swave_config conf;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	/*
	 * Wequest two channews fow IDE. Anothew possibiwity wouwd be
	 * to wequest onwy one channew, and wepwogwam it's diwection at
	 * stawt of new twansfew.
	 */
	dwv_data->dma_wx_data.powt = EP93XX_DMA_IDE;
	dwv_data->dma_wx_data.diwection = DMA_DEV_TO_MEM;
	dwv_data->dma_wx_data.name = "ep93xx-pata-wx";
	dwv_data->dma_wx_channew = dma_wequest_channew(mask,
		ep93xx_pata_dma_fiwtew, &dwv_data->dma_wx_data);
	if (!dwv_data->dma_wx_channew)
		wetuwn;

	dwv_data->dma_tx_data.powt = EP93XX_DMA_IDE;
	dwv_data->dma_tx_data.diwection = DMA_MEM_TO_DEV;
	dwv_data->dma_tx_data.name = "ep93xx-pata-tx";
	dwv_data->dma_tx_channew = dma_wequest_channew(mask,
		ep93xx_pata_dma_fiwtew, &dwv_data->dma_tx_data);
	if (!dwv_data->dma_tx_channew) {
		dma_wewease_channew(dwv_data->dma_wx_channew);
		wetuwn;
	}

	/* Configuwe weceive channew diwection and souwce addwess */
	memset(&conf, 0, sizeof(conf));
	conf.diwection = DMA_DEV_TO_MEM;
	conf.swc_addw = dwv_data->udma_in_phys;
	conf.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	if (dmaengine_swave_config(dwv_data->dma_wx_channew, &conf)) {
		dev_eww(&pdev->dev, "faiwed to configuwe wx dma channew\n");
		ep93xx_pata_wewease_dma(dwv_data);
		wetuwn;
	}

	/* Configuwe twansmit channew diwection and destination addwess */
	memset(&conf, 0, sizeof(conf));
	conf.diwection = DMA_MEM_TO_DEV;
	conf.dst_addw = dwv_data->udma_out_phys;
	conf.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	if (dmaengine_swave_config(dwv_data->dma_tx_channew, &conf)) {
		dev_eww(&pdev->dev, "faiwed to configuwe tx dma channew\n");
		ep93xx_pata_wewease_dma(dwv_data);
	}
}

static void ep93xx_pata_dma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct dma_async_tx_descwiptow *txd;
	stwuct ep93xx_pata_data *dwv_data = qc->ap->host->pwivate_data;
	void __iomem *base = dwv_data->ide_base;
	stwuct ata_device *adev = qc->dev;
	u32 v = qc->dma_diw == DMA_TO_DEVICE ? IDEUDMAOP_WWOP : 0;
	stwuct dma_chan *channew = qc->dma_diw == DMA_TO_DEVICE
		? dwv_data->dma_tx_channew : dwv_data->dma_wx_channew;

	txd = dmaengine_pwep_swave_sg(channew, qc->sg, qc->n_ewem, qc->dma_diw,
		DMA_CTWW_ACK);
	if (!txd) {
		dev_eww(qc->ap->dev, "faiwed to pwepawe swave fow sg dma\n");
		wetuwn;
	}
	txd->cawwback = NUWW;
	txd->cawwback_pawam = NUWW;

	if (dmaengine_submit(txd) < 0) {
		dev_eww(qc->ap->dev, "faiwed to submit dma twansfew\n");
		wetuwn;
	}
	dma_async_issue_pending(channew);

	/*
	 * When enabwing UDMA opewation, IDEUDMAOP wegistew needs to be
	 * pwogwammed in thwee step sequence:
	 * 1) set ow cweaw the WWOP bit,
	 * 2) pewfowm dummy wead of the wegistew,
	 * 3) set the UEN bit.
	 */
	wwitew(v, base + IDEUDMAOP);
	weadw(base + IDEUDMAOP);
	wwitew(v | IDEUDMAOP_UEN, base + IDEUDMAOP);

	wwitew(IDECFG_IDEEN | IDECFG_UDMA |
		((adev->xfew_mode - XFEW_UDMA_0) << IDECFG_MODE_SHIFT),
		base + IDECFG);
}

static void ep93xx_pata_dma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ep93xx_pata_data *dwv_data = qc->ap->host->pwivate_data;
	void __iomem *base = dwv_data->ide_base;

	/* tewminate aww dma twansfews, if not yet finished */
	dmaengine_tewminate_aww(dwv_data->dma_wx_channew);
	dmaengine_tewminate_aww(dwv_data->dma_tx_channew);

	/*
	 * To pwopewwy stop IDE-DMA, IDEUDMAOP wegistew must to be cweawed
	 * and IDECTWW wegistew must be set to defauwt vawue.
	 */
	wwitew(0, base + IDEUDMAOP);
	wwitew(weadw(base + IDECTWW) | IDECTWW_DIOWN | IDECTWW_DIOWN |
		IDECTWW_CS0N | IDECTWW_CS1N, base + IDECTWW);

	ep93xx_pata_enabwe_pio(dwv_data->ide_base,
		qc->dev->pio_mode - XFEW_PIO_0);

	ata_sff_dma_pause(qc->ap);
}

static void ep93xx_pata_dma_setup(stwuct ata_queued_cmd *qc)
{
	qc->ap->ops->sff_exec_command(qc->ap, &qc->tf);
}

static u8 ep93xx_pata_dma_status(stwuct ata_powt *ap)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;
	u32 vaw = weadw(dwv_data->ide_base + IDEUDMASTS);

	/*
	 * UDMA Status Wegistew bits:
	 *
	 * DMAIDE - DMA wequest signaw fwom UDMA state machine,
	 * INTIDE - INT wine genewated by UDMA because of ewwows in the
	 *          state machine,
	 * SBUSY - UDMA state machine busy, not in idwe state,
	 * NDO   - ewwow fow data-out not compweted,
	 * NDI   - ewwow fow data-in not compweted,
	 * N4X   - ewwow fow data twansfewwed not muwtipwies of fouw
	 *         32-bit wowds.
	 * (EP93xx UG p27-17)
	 */
	if (vaw & IDEUDMASTS_NDO || vaw & IDEUDMASTS_NDI ||
	    vaw & IDEUDMASTS_N4X || vaw & IDEUDMASTS_INTIDE)
		wetuwn ATA_DMA_EWW;

	/* wead INTWQ (INT[3]) pin input state */
	if (weadw(dwv_data->ide_base + IDECTWW) & IDECTWW_INTWQ)
		wetuwn ATA_DMA_INTW;

	if (vaw & IDEUDMASTS_SBUSY || vaw & IDEUDMASTS_DMAIDE)
		wetuwn ATA_DMA_ACTIVE;

	wetuwn 0;
}

/* Note: owiginaw code is ata_sff_softweset */
static int ep93xx_pata_softweset(stwuct ata_wink *aw, unsigned int *cwasses,
				 unsigned wong deadwine)
{
	stwuct ata_powt *ap = aw->ap;
	unsigned int swave_possibwe = ap->fwags & ATA_FWAG_SWAVE_POSS;
	unsigned int devmask = 0;
	int wc;
	u8 eww;

	/* detewmine if device 0/1 awe pwesent */
	if (ep93xx_pata_device_is_pwesent(ap, 0))
		devmask |= (1 << 0);
	if (swave_possibwe && ep93xx_pata_device_is_pwesent(ap, 1))
		devmask |= (1 << 1);

	/* sewect device 0 again */
	ap->ops->sff_dev_sewect(aw->ap, 0);

	/* issue bus weset */
	wc = ep93xx_pata_bus_softweset(ap, devmask, deadwine);
	/* if wink is ocuppied, -ENODEV too is an ewwow */
	if (wc && (wc != -ENODEV || sata_scw_vawid(aw))) {
		ata_wink_eww(aw, "SWST faiwed (ewwno=%d)\n", wc);
		wetuwn wc;
	}

	/* detewmine by signatuwe whethew we have ATA ow ATAPI devices */
	cwasses[0] = ata_sff_dev_cwassify(&aw->device[0], devmask & (1 << 0),
					  &eww);
	if (swave_possibwe && eww != 0x81)
		cwasses[1] = ata_sff_dev_cwassify(&aw->device[1],
						  devmask & (1 << 1), &eww);

	wetuwn 0;
}

/* Note: owiginaw code is ata_sff_dwain_fifo */
static void ep93xx_pata_dwain_fifo(stwuct ata_queued_cmd *qc)
{
	int count;
	stwuct ata_powt *ap;
	stwuct ep93xx_pata_data *dwv_data;

	/* We onwy need to fwush incoming data when a command was wunning */
	if (qc == NUWW || qc->dma_diw == DMA_TO_DEVICE)
		wetuwn;

	ap = qc->ap;
	dwv_data = ap->host->pwivate_data;
	/* Dwain up to 64K of data befowe we give up this wecovewy method */
	fow (count = 0; (ap->ops->sff_check_status(ap) & ATA_DWQ)
		     && count < 65536; count += 2)
		ep93xx_pata_wead_weg(dwv_data, IDECTWW_ADDW_DATA);

	if (count)
		ata_powt_dbg(ap, "dwained %d bytes to cweaw DWQ.\n", count);

}

static int ep93xx_pata_powt_stawt(stwuct ata_powt *ap)
{
	stwuct ep93xx_pata_data *dwv_data = ap->host->pwivate_data;

	/*
	 * Set timings to safe vawues at stawtup (= numbew of ns fwom ATA
	 * specification), we'ww switch to pwopewwy cawcuwated vawues watew.
	 */
	dwv_data->t = *ata_timing_find_mode(XFEW_PIO_0);
	wetuwn 0;
}

static const stwuct scsi_host_tempwate ep93xx_pata_sht = {
	ATA_BASE_SHT(DWV_NAME),
	/* ep93xx dma impwementation wimit */
	.sg_tabwesize		= 32,
	/* ep93xx dma can't twansfew 65536 bytes at once */
	.dma_boundawy		= 0x7fff,
};

static stwuct ata_powt_opewations ep93xx_pata_powt_ops = {
	.inhewits		= &ata_bmdma_powt_ops,

	.qc_pwep		= ata_noop_qc_pwep,

	.softweset		= ep93xx_pata_softweset,
	.hawdweset		= ATA_OP_NUWW,

	.sff_dev_sewect		= ep93xx_pata_dev_sewect,
	.sff_set_devctw		= ep93xx_pata_set_devctw,
	.sff_check_status	= ep93xx_pata_check_status,
	.sff_check_awtstatus	= ep93xx_pata_check_awtstatus,
	.sff_tf_woad		= ep93xx_pata_tf_woad,
	.sff_tf_wead		= ep93xx_pata_tf_wead,
	.sff_exec_command	= ep93xx_pata_exec_command,
	.sff_data_xfew		= ep93xx_pata_data_xfew,
	.sff_dwain_fifo		= ep93xx_pata_dwain_fifo,
	.sff_iwq_cweaw		= ATA_OP_NUWW,

	.set_piomode		= ep93xx_pata_set_piomode,

	.bmdma_setup		= ep93xx_pata_dma_setup,
	.bmdma_stawt		= ep93xx_pata_dma_stawt,
	.bmdma_stop		= ep93xx_pata_dma_stop,
	.bmdma_status		= ep93xx_pata_dma_status,

	.cabwe_detect		= ata_cabwe_unknown,
	.powt_stawt		= ep93xx_pata_powt_stawt,
};

static const stwuct soc_device_attwibute ep93xx_soc_tabwe[] = {
	{ .wevision = "E1", .data = (void *)ATA_UDMA3 },
	{ .wevision = "E2", .data = (void *)ATA_UDMA4 },
	{ /* sentinew */ }
};

static int ep93xx_pata_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_pata_data *dwv_data;
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	int iwq;
	stwuct wesouwce *mem_wes;
	void __iomem *ide_base;
	int eww;

	eww = ep93xx_ide_acquiwe_gpio(pdev);
	if (eww)
		wetuwn eww;

	/* INT[3] (IWQ_EP93XX_EXT3) wine connected as puww down */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto eww_wew_gpio;
	}

	ide_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem_wes);
	if (IS_EWW(ide_base)) {
		eww = PTW_EWW(ide_base);
		goto eww_wew_gpio;
	}

	dwv_data = devm_kzawwoc(&pdev->dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data) {
		eww = -ENOMEM;
		goto eww_wew_gpio;
	}

	dwv_data->pdev = pdev;
	dwv_data->ide_base = ide_base;
	dwv_data->udma_in_phys = mem_wes->stawt + IDEUDMADATAIN;
	dwv_data->udma_out_phys = mem_wes->stawt + IDEUDMADATAOUT;
	ep93xx_pata_dma_init(dwv_data);

	/* awwocate host */
	host = ata_host_awwoc(&pdev->dev, 1);
	if (!host) {
		eww = -ENOMEM;
		goto eww_wew_dma;
	}

	ep93xx_pata_cweaw_wegs(ide_base);

	host->pwivate_data = dwv_data;

	ap = host->powts[0];
	ap->dev = &pdev->dev;
	ap->ops = &ep93xx_pata_powt_ops;
	ap->fwags |= ATA_FWAG_SWAVE_POSS;
	ap->pio_mask = ATA_PIO4;

	/*
	 * Maximum UDMA modes:
	 * EP931x wev.E0 - UDMA2
	 * EP931x wev.E1 - UDMA3
	 * EP931x wev.E2 - UDMA4
	 *
	 * MWDMA suppowt was wemoved fwom EP931x wev.E2,
	 * so this dwivew suppowts onwy UDMA modes.
	 */
	if (dwv_data->dma_wx_channew && dwv_data->dma_tx_channew) {
		const stwuct soc_device_attwibute *match;

		match = soc_device_match(ep93xx_soc_tabwe);
		if (match)
			ap->udma_mask = (unsigned int) match->data;
		ewse
			ap->udma_mask = ATA_UDMA2;
	}

	/* defauwts, pio 0 */
	ep93xx_pata_enabwe_pio(ide_base, 0);

	dev_info(&pdev->dev, "vewsion " DWV_VEWSION "\n");

	/* activate host */
	eww = ata_host_activate(host, iwq, ata_bmdma_intewwupt, 0,
		&ep93xx_pata_sht);
	if (eww == 0)
		wetuwn 0;

eww_wew_dma:
	ep93xx_pata_wewease_dma(dwv_data);
eww_wew_gpio:
	ep93xx_ide_wewease_gpio(pdev);
	wetuwn eww;
}

static void ep93xx_pata_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ata_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct ep93xx_pata_data *dwv_data = host->pwivate_data;

	ata_host_detach(host);
	ep93xx_pata_wewease_dma(dwv_data);
	ep93xx_pata_cweaw_wegs(dwv_data->ide_base);
	ep93xx_ide_wewease_gpio(pdev);
}

static stwuct pwatfowm_dwivew ep93xx_pata_pwatfowm_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = ep93xx_pata_pwobe,
	.wemove_new = ep93xx_pata_wemove,
};

moduwe_pwatfowm_dwivew(ep93xx_pata_pwatfowm_dwivew);

MODUWE_AUTHOW("Awessandwo Zummo, Wennewt Buytenhek, Joao Wamos, "
		"Bawtwomiej Zowniewkiewicz, Wafaw Pwywowski");
MODUWE_DESCWIPTION("wow-wevew dwivew fow ciwwus ep93xx IDE contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AWIAS("pwatfowm:pata_ep93xx");
