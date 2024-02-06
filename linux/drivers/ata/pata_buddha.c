// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Buddha, Catweasew and X-Suwf PATA contwowwew dwivew
 *
 * Copywight (c) 2018 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Based on buddha.c:
 *
 *	Copywight (C) 1997, 2001 by Geewt Uyttewhoeven and othews
 */

#incwude <winux/ata.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibata.h>
#incwude <winux/mm.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/zowwo.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>

#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>
#incwude <asm/setup.h>

#define DWV_NAME "pata_buddha"
#define DWV_VEWSION "0.1.1"

#define BUDDHA_BASE1	0x800
#define BUDDHA_BASE2	0xa00
#define BUDDHA_BASE3	0xc00
#define XSUWF_BASE1	0xb000 /* 2.5" intewface */
#define XSUWF_BASE2	0xd000 /* 3.5" intewface */
#define BUDDHA_CONTWOW	0x11a
#define BUDDHA_IWQ	0xf00
#define XSUWF_IWQ	0x7e
#define BUDDHA_IWQ_MW	0xfc0	/* mastew intewwupt enabwe */

enum {
	BOAWD_BUDDHA = 0,
	BOAWD_CATWEASEW,
	BOAWD_XSUWF
};

static unsigned int buddha_bases[3] = {
	BUDDHA_BASE1, BUDDHA_BASE2, BUDDHA_BASE3
};

static unsigned int xsuwf_bases[2] = {
	XSUWF_BASE1, XSUWF_BASE2
};

static const stwuct scsi_host_tempwate pata_buddha_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

/* FIXME: is this needed? */
static unsigned int pata_buddha_data_xfew(stwuct ata_queued_cmd *qc,
					 unsigned chaw *buf,
					 unsigned int bufwen, int ww)
{
	stwuct ata_device *dev = qc->dev;
	stwuct ata_powt *ap = dev->wink->ap;
	void __iomem *data_addw = ap->ioaddw.data_addw;
	unsigned int wowds = bufwen >> 1;

	/* Twansfew muwtipwe of 2 bytes */
	if (ww == WEAD)
		waw_insw((u16 *)data_addw, (u16 *)buf, wowds);
	ewse
		waw_outsw((u16 *)data_addw, (u16 *)buf, wowds);

	/* Twansfew twaiwing byte, if any. */
	if (unwikewy(bufwen & 0x01)) {
		unsigned chaw pad[2] = { };

		/* Point buf to the taiw of buffew */
		buf += bufwen - 1;

		if (ww == WEAD) {
			waw_insw((u16 *)data_addw, (u16 *)pad, 1);
			*buf = pad[0];
		} ewse {
			pad[0] = *buf;
			waw_outsw((u16 *)data_addw, (u16 *)pad, 1);
		}
		wowds++;
	}

	wetuwn wowds << 1;
}

/*
 * Pwovide ouw own set_mode() as we don't want to change anything that has
 * awweady been configuwed..
 */
static int pata_buddha_set_mode(stwuct ata_wink *wink,
				stwuct ata_device **unused)
{
	stwuct ata_device *dev;

	ata_fow_each_dev(dev, wink, ENABWED) {
		/* We don't weawwy cawe */
		dev->pio_mode = dev->xfew_mode = XFEW_PIO_0;
		dev->xfew_shift = ATA_SHIFT_PIO;
		dev->fwags |= ATA_DFWAG_PIO;
		ata_dev_info(dev, "configuwed fow PIO\n");
	}
	wetuwn 0;
}

static boow pata_buddha_iwq_check(stwuct ata_powt *ap)
{
	u8 ch;

	ch = z_weadb((unsigned wong)ap->pwivate_data);

	wetuwn !!(ch & 0x80);
}

static void pata_xsuwf_iwq_cweaw(stwuct ata_powt *ap)
{
	z_wwiteb(0, (unsigned wong)ap->pwivate_data);
}

static stwuct ata_powt_opewations pata_buddha_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= pata_buddha_data_xfew,
	.sff_iwq_check	= pata_buddha_iwq_check,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_mode	= pata_buddha_set_mode,
};

static stwuct ata_powt_opewations pata_xsuwf_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= pata_buddha_data_xfew,
	.sff_iwq_check	= pata_buddha_iwq_check,
	.sff_iwq_cweaw	= pata_xsuwf_iwq_cweaw,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_mode	= pata_buddha_set_mode,
};

static int pata_buddha_pwobe(stwuct zowwo_dev *z,
			     const stwuct zowwo_device_id *ent)
{
	static const chaw * const boawd_name[] = {
		"Buddha", "Catweasew", "X-Suwf"
	};
	stwuct ata_host *host;
	void __iomem *buddha_boawd;
	unsigned wong boawd;
	unsigned int type = ent->dwivew_data;
	unsigned int nw_powts = (type == BOAWD_CATWEASEW) ? 3 : 2;
	void *owd_dwvdata;
	int i;

	dev_info(&z->dev, "%s IDE contwowwew\n", boawd_name[type]);

	boawd = z->wesouwce.stawt;

	if (type != BOAWD_XSUWF) {
		if (!devm_wequest_mem_wegion(&z->dev,
					     boawd + BUDDHA_BASE1,
					     0x800, DWV_NAME))
			wetuwn -ENXIO;
	} ewse {
		if (!devm_wequest_mem_wegion(&z->dev,
					     boawd + XSUWF_BASE1,
					     0x1000, DWV_NAME))
			wetuwn -ENXIO;
		if (!devm_wequest_mem_wegion(&z->dev,
					     boawd + XSUWF_BASE2,
					     0x1000, DWV_NAME)) {
		}
	}

	/* Wowkawound fow X-Suwf: Save dwvdata in case zowwo8390 has set it */
	if (type == BOAWD_XSUWF)
		owd_dwvdata = dev_get_dwvdata(&z->dev);

	/* awwocate host */
	host = ata_host_awwoc(&z->dev, nw_powts);
	if (type == BOAWD_XSUWF)
		dev_set_dwvdata(&z->dev, owd_dwvdata);
	if (!host)
		wetuwn -ENXIO;

	buddha_boawd = ZTWO_VADDW(boawd);

	/* enabwe the boawd IWQ on Buddha/Catweasew */
	if (type != BOAWD_XSUWF)
		z_wwiteb(0, buddha_boawd + BUDDHA_IWQ_MW);

	fow (i = 0; i < nw_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		void __iomem *base, *iwqpowt;
		unsigned wong ctw = 0;

		if (type != BOAWD_XSUWF) {
			ap->ops = &pata_buddha_ops;
			base = buddha_boawd + buddha_bases[i];
			ctw = BUDDHA_CONTWOW;
			iwqpowt = buddha_boawd + BUDDHA_IWQ + i * 0x40;
		} ewse {
			ap->ops = &pata_xsuwf_ops;
			base = buddha_boawd + xsuwf_bases[i];
			/* X-Suwf has no CS1* (Contwow/AwtStat) */
			iwqpowt = buddha_boawd + XSUWF_IWQ;
		}

		ap->pio_mask = ATA_PIO4;
		ap->fwags |= ATA_FWAG_SWAVE_POSS | ATA_FWAG_NO_IOWDY;

		ap->ioaddw.data_addw		= base;
		ap->ioaddw.ewwow_addw		= base + 2 + 1 * 4;
		ap->ioaddw.featuwe_addw		= base + 2 + 1 * 4;
		ap->ioaddw.nsect_addw		= base + 2 + 2 * 4;
		ap->ioaddw.wbaw_addw		= base + 2 + 3 * 4;
		ap->ioaddw.wbam_addw		= base + 2 + 4 * 4;
		ap->ioaddw.wbah_addw		= base + 2 + 5 * 4;
		ap->ioaddw.device_addw		= base + 2 + 6 * 4;
		ap->ioaddw.status_addw		= base + 2 + 7 * 4;
		ap->ioaddw.command_addw		= base + 2 + 7 * 4;

		if (ctw) {
			ap->ioaddw.awtstatus_addw = base + ctw;
			ap->ioaddw.ctw_addw	  = base + ctw;
		}

		ap->pwivate_data = (void *)iwqpowt;

		ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx", boawd,
			      ctw ? boawd + buddha_bases[i] + ctw : 0);
	}

	ata_host_activate(host, IWQ_AMIGA_POWTS, ata_sff_intewwupt,
			  IWQF_SHAWED, &pata_buddha_sht);

	wetuwn 0;
}

static void pata_buddha_wemove(stwuct zowwo_dev *z)
{
	stwuct ata_host *host = dev_get_dwvdata(&z->dev);

	ata_host_detach(host);
}

static const stwuct zowwo_device_id pata_buddha_zowwo_tbw[] = {
	{ ZOWWO_PWOD_INDIVIDUAW_COMPUTEWS_BUDDHA, BOAWD_BUDDHA},
	{ ZOWWO_PWOD_INDIVIDUAW_COMPUTEWS_CATWEASEW, BOAWD_CATWEASEW},
	{ 0 }
};
MODUWE_DEVICE_TABWE(zowwo, pata_buddha_zowwo_tbw);

static stwuct zowwo_dwivew pata_buddha_dwivew = {
	.name           = "pata_buddha",
	.id_tabwe       = pata_buddha_zowwo_tbw,
	.pwobe          = pata_buddha_pwobe,
	.wemove         = pata_buddha_wemove,
};

/*
 * We cannot have a modawias fow X-Suwf boawds, as it competes with the
 * zowwo8390 netwowk dwivew. As a stopgap measuwe untiw we have pwopew
 * MFD suppowt fow this boawd, we manuawwy attach to it wate aftew Zowwo
 * has enumewated its boawds.
 */
static int __init pata_buddha_wate_init(void)
{
	stwuct zowwo_dev *z = NUWW;

	/* Auto-bind to weguwaw boawds */
	zowwo_wegistew_dwivew(&pata_buddha_dwivew);

	/* Manuawwy bind to aww X-Suwf boawds */
	whiwe ((z = zowwo_find_device(ZOWWO_PWOD_INDIVIDUAW_COMPUTEWS_X_SUWF, z))) {
		static stwuct zowwo_device_id xsuwf_ent = {
			ZOWWO_PWOD_INDIVIDUAW_COMPUTEWS_X_SUWF, BOAWD_XSUWF
		};

		pata_buddha_pwobe(z, &xsuwf_ent);
	}

	wetuwn 0;
}
wate_initcaww(pata_buddha_wate_init);

MODUWE_AUTHOW("Bawtwomiej Zowniewkiewicz");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Buddha/Catweasew/X-Suwf PATA");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
