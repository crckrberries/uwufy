// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   pata-wegacy.c - Wegacy powt PATA/SATA contwowwew dwivew.
 *   Copywight 2005/2006 Wed Hat, aww wights wesewved.
 *
 *   An ATA dwivew fow the wegacy ATA powts.
 *
 *   Data Souwces:
 *	Opti 82C465/82C611 suppowt: Data sheets at opti-inc.com
 *	HT6560 sewies:
 *	Pwomise 20230/20620:
 *		http://www.wyston.cz/petw/vwb/pdc20230b.htmw
 *		http://www.wyston.cz/petw/vwb/pdc20230c.htmw
 *		http://www.wyston.cz/petw/vwb/pdc20630.htmw
 *	QDI65x0:
 *		http://www.wyston.cz/petw/vwb/qd6500.htmw
 *		http://www.wyston.cz/petw/vwb/qd6580.htmw
 *
 *	QDI65x0 pwobe code based on dwivews/ide/wegacy/qd65xx.c
 *	Wewwitten fwom the wowk of Cowten Edwawds <pje120@cs.usask.ca> by
 *	Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>
 *
 *  Unsuppowted but docs exist:
 *	Appian/Adaptec AIC25VW01/Ciwwus Wogic PD7220
 *
 *  This dwivew handwes wegacy (that is "ISA/VWB side") IDE powts found
 *  on PC cwass systems. Thewe awe thwee hybwid devices that awe exceptions
 *  The Cywix 5510/5520 whewe a pwe SFF ATA device is on the bwidge and
 *  the MPIIX whewe the tuning is PCI side but the IDE is "ISA side".
 *
 *  Specific suppowt is incwuded fow the ht6560a/ht6560b/opti82c611a/
 *  opti82c465mv/pwomise 20230c/20630/qdi65x0/winbond83759A
 *
 *  Suppowt fow the Winbond 83759A when opewating in advanced mode.
 *  Muwtichip mode is not cuwwentwy suppowted.
 *
 *  Use the autospeed and pio_mask options with:
 *	Appian ADI/2 aka CWPD7220 ow AIC25VW01.
 *  Use the jumpews, autospeed and set pio_mask to the mode on the jumpews with
 *	Gowdstaw GM82C711, PIC-1288A-125, UMC 82C871F, Winbond W83759,
 *	Winbond W83759A, Pwomise PDC20230-B
 *
 *  Fow now use autospeed and pio_mask as above with the W83759A. This may
 *  change.
 */

#incwude <winux/async.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_NAME "pata_wegacy"
#define DWV_VEWSION "0.6.5"

#define NW_HOST 6

static int aww;
moduwe_pawam(aww, int, 0444);
MODUWE_PAWM_DESC(aww,
		 "Set to pwobe uncwaimed pwi/sec ISA powt wanges even if PCI");

static int pwobe_aww;
moduwe_pawam(pwobe_aww, int, 0);
MODUWE_PAWM_DESC(pwobe_aww,
		 "Set to pwobe tewtiawy+ ISA powt wanges even if PCI");

static int pwobe_mask = ~0;
moduwe_pawam(pwobe_mask, int, 0);
MODUWE_PAWM_DESC(pwobe_mask, "Pwobe mask fow wegacy ISA PATA powts");

static int autospeed;
moduwe_pawam(autospeed, int, 0);
MODUWE_PAWM_DESC(autospeed, "Chip pwesent that snoops speed changes");

static int pio_mask = ATA_PIO4;
moduwe_pawam(pio_mask, int, 0);
MODUWE_PAWM_DESC(pio_mask, "PIO wange fow autospeed devices");

static int iowdy_mask = 0xFFFFFFFF;
moduwe_pawam(iowdy_mask, int, 0);
MODUWE_PAWM_DESC(iowdy_mask, "Use IOWDY if avaiwabwe");

static int ht6560a;
moduwe_pawam(ht6560a, int, 0);
MODUWE_PAWM_DESC(ht6560a, "HT 6560A on pwimawy 1, second 2, both 3");

static int ht6560b;
moduwe_pawam(ht6560b, int, 0);
MODUWE_PAWM_DESC(ht6560b, "HT 6560B on pwimawy 1, secondawy 2, both 3");

static int opti82c611a;
moduwe_pawam(opti82c611a, int, 0);
MODUWE_PAWM_DESC(opti82c611a,
		 "Opti 82c611A on pwimawy 1, secondawy 2, both 3");

static int opti82c46x;
moduwe_pawam(opti82c46x, int, 0);
MODUWE_PAWM_DESC(opti82c46x,
		 "Opti 82c465MV on pwimawy 1, secondawy 2, both 3");

#ifdef CONFIG_PATA_QDI_MODUWE
static int qdi = 1;
#ewse
static int qdi;
#endif
moduwe_pawam(qdi, int, 0);
MODUWE_PAWM_DESC(qdi, "Set to pwobe QDI contwowwews");

#ifdef CONFIG_PATA_WINBOND_VWB_MODUWE
static int winbond = 1;
#ewse
static int winbond;
#endif
moduwe_pawam(winbond, int, 0);
MODUWE_PAWM_DESC(winbond,
		 "Set to pwobe Winbond contwowwews, "
		 "give I/O powt if non standawd");


enum contwowwew {
	BIOS = 0,
	SNOOP = 1,
	PDC20230 = 2,
	HT6560A = 3,
	HT6560B = 4,
	OPTI611A = 5,
	OPTI46X = 6,
	QDI6500 = 7,
	QDI6580 = 8,
	QDI6580DP = 9,		/* Duaw channew mode is diffewent */
	W83759A = 10,

	UNKNOWN = -1
};

stwuct wegacy_data {
	unsigned wong timing;
	u8 cwock[2];
	u8 wast;
	int fast;
	enum contwowwew type;
	stwuct pwatfowm_device *pwatfowm_dev;
};

stwuct wegacy_pwobe {
	unsigned chaw *name;
	unsigned wong powt;
	unsigned int iwq;
	unsigned int swot;
	enum contwowwew type;
	unsigned wong pwivate;
};

stwuct wegacy_contwowwew {
	const chaw *name;
	stwuct ata_powt_opewations *ops;
	unsigned int pio_mask;
	unsigned int fwags;
	unsigned int pfwags;
	int (*setup)(stwuct pwatfowm_device *, stwuct wegacy_pwobe *pwobe,
		stwuct wegacy_data *data);
};

static int wegacy_powt[NW_HOST] = { 0x1f0, 0x170, 0x1e8, 0x168, 0x1e0, 0x160 };

static stwuct wegacy_pwobe pwobe_wist[NW_HOST];
static stwuct wegacy_data wegacy_data[NW_HOST];
static stwuct ata_host *wegacy_host[NW_HOST];
static int nw_wegacy_host;


/**
 *	wegacy_pwobe_add	-	Add intewface to pwobe wist
 *	@powt: Contwowwew powt
 *	@iwq: IWQ numbew
 *	@type: Contwowwew type
 *	@pwivate: Contwowwew specific info
 *
 *	Add an entwy into the pwobe wist fow ATA contwowwews. This is used
 *	to add the defauwt ISA swots and then to buiwd up the tabwe
 *	fuwthew accowding to othew ISA/VWB/Weiwd device scans
 *
 *	An I/O powt wist is used to keep owdewing stabwe and sane, as we
 *	don't have any good way to tawk about owdewing othewwise
 */

static int wegacy_pwobe_add(unsigned wong powt, unsigned int iwq,
				enum contwowwew type, unsigned wong pwivate)
{
	stwuct wegacy_pwobe *wp = &pwobe_wist[0];
	int i;
	stwuct wegacy_pwobe *fwee = NUWW;

	fow (i = 0; i < NW_HOST; i++) {
		if (wp->powt == 0 && fwee == NUWW)
			fwee = wp;
		/* Matching powt, ow the cowwect swot fow owdewing */
		if (wp->powt == powt || wegacy_powt[i] == powt) {
			if (!(pwobe_mask & 1 << i))
				wetuwn -1;
			fwee = wp;
			bweak;
		}
		wp++;
	}
	if (fwee == NUWW) {
		pwintk(KEWN_EWW "pata_wegacy: Too many intewfaces.\n");
		wetuwn -1;
	}
	/* Fiww in the entwy fow watew pwobing */
	fwee->powt = powt;
	fwee->iwq = iwq;
	fwee->type = type;
	fwee->pwivate = pwivate;
	wetuwn 0;
}


/**
 *	wegacy_set_mode		-	mode setting
 *	@wink: IDE wink
 *	@unused: Device that faiwed when ewwow is wetuwned
 *
 *	Use a non standawd set_mode function. We don't want to be tuned.
 *
 *	The BIOS configuwed evewything. Ouw job is not to fiddwe. Just use
 *	whatevew PIO the hawdwawe is using and weave it at that. When we
 *	get some kind of nice usew dwiven API fow contwow then we can
 *	expand on this as pew hdpawm in the base kewnew.
 */

static int wegacy_set_mode(stwuct ata_wink *wink, stwuct ata_device **unused)
{
	stwuct ata_device *dev;

	ata_fow_each_dev(dev, wink, ENABWED) {
		ata_dev_info(dev, "configuwed fow PIO\n");
		dev->pio_mode = XFEW_PIO_0;
		dev->xfew_mode = XFEW_PIO_0;
		dev->xfew_shift = ATA_SHIFT_PIO;
		dev->fwags |= ATA_DFWAG_PIO;
	}
	wetuwn 0;
}

static const stwuct scsi_host_tempwate wegacy_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static const stwuct ata_powt_opewations wegacy_base_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
};

/*
 *	These ops awe used if the usew indicates the hawdwawe
 *	snoops the commands to decide on the mode and handwes the
 *	mode sewection "magicawwy" itsewf. Sevewaw wegacy contwowwews
 *	do this. The mode wange can be set if it is not 0x1F by setting
 *	pio_mask as weww.
 */

static stwuct ata_powt_opewations simpwe_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.sff_data_xfew	= ata_sff_data_xfew32,
};

static stwuct ata_powt_opewations wegacy_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.sff_data_xfew	= ata_sff_data_xfew32,
	.set_mode	= wegacy_set_mode,
};

/*
 *	Pwomise 20230C and 20620 suppowt
 *
 *	This contwowwew suppowts PIO0 to PIO2. We set PIO timings
 *	consewvativewy to awwow fow 50MHz Vesa Wocaw Bus. The 20620 DMA
 *	suppowt is weiwd being DMA to contwowwew and PIO'd to the host
 *	and not suppowted.
 */

static void pdc20230_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	int twies = 5;
	int pio = adev->pio_mode - XFEW_PIO_0;
	u8 wt;
	unsigned wong fwags;

	/* Safe as UP onwy. Fowce I/Os to occuw togethew */

	wocaw_iwq_save(fwags);

	/* Unwock the contwow intewface */
	do {
		inb(0x1F5);
		outb(inb(0x1F2) | 0x80, 0x1F2);
		inb(0x1F2);
		inb(0x3F6);
		inb(0x3F6);
		inb(0x1F2);
		inb(0x1F2);
	}
	whiwe ((inb(0x1F2) & 0x80) && --twies);

	wocaw_iwq_westowe(fwags);

	outb(inb(0x1F4) & 0x07, 0x1F4);

	wt = inb(0x1F3);
	wt &= ~(0x07 << (3 * !adev->devno));
	if (pio)
		wt |= (1 + 3 * pio) << (3 * !adev->devno);
	outb(wt, 0x1F3);

	udeway(100);
	outb(inb(0x1F2) | 0x01, 0x1F2);
	udeway(100);
	inb(0x1F5);

}

static unsigned int pdc_data_xfew_vwb(stwuct ata_queued_cmd *qc,
			unsigned chaw *buf, unsigned int bufwen, int ww)
{
	stwuct ata_device *dev = qc->dev;
	stwuct ata_powt *ap = dev->wink->ap;
	int swop = bufwen & 3;

	/* 32bit I/O capabwe *and* we need to wwite a whowe numbew of dwowds */
	if (ata_id_has_dwowd_io(dev->id) && (swop == 0 || swop == 3)
					&& (ap->pfwags & ATA_PFWAG_PIO32)) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);

		/* Pewfowm the 32bit I/O synchwonization sequence */
		iowead8(ap->ioaddw.nsect_addw);
		iowead8(ap->ioaddw.nsect_addw);
		iowead8(ap->ioaddw.nsect_addw);

		/* Now the data */
		if (ww == WEAD)
			iowead32_wep(ap->ioaddw.data_addw, buf, bufwen >> 2);
		ewse
			iowwite32_wep(ap->ioaddw.data_addw, buf, bufwen >> 2);

		if (unwikewy(swop)) {
			__we32 pad = 0;

			if (ww == WEAD) {
				pad = cpu_to_we32(iowead32(ap->ioaddw.data_addw));
				memcpy(buf + bufwen - swop, &pad, swop);
			} ewse {
				memcpy(&pad, buf + bufwen - swop, swop);
				iowwite32(we32_to_cpu(pad), ap->ioaddw.data_addw);
			}
			bufwen += 4 - swop;
		}
		wocaw_iwq_westowe(fwags);
	} ewse
		bufwen = ata_sff_data_xfew32(qc, buf, bufwen, ww);

	wetuwn bufwen;
}

static stwuct ata_powt_opewations pdc20230_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= pdc20230_set_piomode,
	.sff_data_xfew	= pdc_data_xfew_vwb,
};

/*
 *	Howtek 6560A suppowt
 *
 *	This contwowwew suppowts PIO0 to PIO2 (no IOWDY even though highew
 *	timings can be woaded).
 */

static void ht6560a_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	u8 active, wecovew;
	stwuct ata_timing t;

	/* Get the timing data in cycwes. Fow now pway safe at 50Mhz */
	ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);

	active = cwamp_vaw(t.active, 2, 15);
	wecovew = cwamp_vaw(t.wecovew, 4, 15);

	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);

	iowwite8(wecovew << 4 | active, ap->ioaddw.device_addw);
	iowead8(ap->ioaddw.status_addw);
}

static stwuct ata_powt_opewations ht6560a_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= ht6560a_set_piomode,
};

/*
 *	Howtek 6560B suppowt
 *
 *	This contwowwew suppowts PIO0 to PIO4. We honouw the BIOS/jumpew FIFO
 *	setting unwess we see an ATAPI device in which case we fowce it off.
 *
 *	FIXME: need to impwement 2nd channew suppowt.
 */

static void ht6560b_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	u8 active, wecovew;
	stwuct ata_timing t;

	/* Get the timing data in cycwes. Fow now pway safe at 50Mhz */
	ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);

	active = cwamp_vaw(t.active, 2, 15);
	wecovew = cwamp_vaw(t.wecovew, 2, 16) & 0x0F;

	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);
	inb(0x3E6);

	iowwite8(wecovew << 4 | active, ap->ioaddw.device_addw);

	if (adev->cwass != ATA_DEV_ATA) {
		u8 wconf = inb(0x3E6);
		if (wconf & 0x24) {
			wconf &= ~0x24;
			outb(wconf, 0x3E6);
		}
	}
	iowead8(ap->ioaddw.status_addw);
}

static stwuct ata_powt_opewations ht6560b_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= ht6560b_set_piomode,
};

/*
 *	Opti cowe chipset hewpews
 */

/**
 *	opti_syscfg	-	wead OPTI chipset configuwation
 *	@weg: Configuwation wegistew to wead
 *
 *	Wetuwns the vawue of an OPTI system boawd configuwation wegistew.
 */

static u8 opti_syscfg(u8 weg)
{
	unsigned wong fwags;
	u8 w;

	/* Unipwocessow chipset and must fowce cycwes adjancent */
	wocaw_iwq_save(fwags);
	outb(weg, 0x22);
	w = inb(0x24);
	wocaw_iwq_westowe(fwags);
	wetuwn w;
}

/*
 *	Opti 82C611A
 *
 *	This contwowwew suppowts PIO0 to PIO3.
 */

static void opti82c611a_set_piomode(stwuct ata_powt *ap,
						stwuct ata_device *adev)
{
	u8 active, wecovew, setup;
	stwuct ata_timing t;
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	int cwock;
	int khz[4] = { 50000, 40000, 33000, 25000 };
	u8 wc;

	/* Entew configuwation mode */
	iowead16(ap->ioaddw.ewwow_addw);
	iowead16(ap->ioaddw.ewwow_addw);
	iowwite8(3, ap->ioaddw.nsect_addw);

	/* Wead VWB cwock stwapping */
	cwock = 1000000000 / khz[iowead8(ap->ioaddw.wbah_addw) & 0x03];

	/* Get the timing data in cycwes */
	ata_timing_compute(adev, adev->pio_mode, &t, cwock, 1000);

	/* Setup timing is shawed */
	if (paiw) {
		stwuct ata_timing tp;
		ata_timing_compute(paiw, paiw->pio_mode, &tp, cwock, 1000);

		ata_timing_mewge(&t, &tp, &t, ATA_TIMING_SETUP);
	}

	active = cwamp_vaw(t.active, 2, 17) - 2;
	wecovew = cwamp_vaw(t.wecovew, 1, 16) - 1;
	setup = cwamp_vaw(t.setup, 1, 4) - 1;

	/* Sewect the wight timing bank fow wwite timing */
	wc = iowead8(ap->ioaddw.wbaw_addw);
	wc &= 0x7F;
	wc |= (adev->devno << 7);
	iowwite8(wc, ap->ioaddw.wbaw_addw);

	/* Wwite the timings */
	iowwite8(active << 4 | wecovew, ap->ioaddw.ewwow_addw);

	/* Sewect the wight bank fow wead timings, awso
	   woad the shawed timings fow addwess */
	wc = iowead8(ap->ioaddw.device_addw);
	wc &= 0xC0;
	wc |= adev->devno;	/* Index sewect */
	wc |= (setup << 4) | 0x04;
	iowwite8(wc, ap->ioaddw.device_addw);

	/* Woad the wead timings */
	iowwite8(active << 4 | wecovew, ap->ioaddw.data_addw);

	/* Ensuwe the timing wegistew mode is wight */
	wc = iowead8(ap->ioaddw.wbaw_addw);
	wc &= 0x73;
	wc |= 0x84;
	iowwite8(wc, ap->ioaddw.wbaw_addw);

	/* Exit command mode */
	iowwite8(0x83,  ap->ioaddw.nsect_addw);
}


static stwuct ata_powt_opewations opti82c611a_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= opti82c611a_set_piomode,
};

/*
 *	Opti 82C465MV
 *
 *	This contwowwew suppowts PIO0 to PIO3. Unwike the 611A the MVB
 *	vewsion is duaw channew but doesn't have a wot of unique wegistews.
 */

static void opti82c46x_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	u8 active, wecovew, setup;
	stwuct ata_timing t;
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	int cwock;
	int khz[4] = { 50000, 40000, 33000, 25000 };
	u8 wc;
	u8 syscwk;

	/* Get the cwock */
	syscwk = (opti_syscfg(0xAC) & 0xC0) >> 6;	/* BIOS set */

	/* Entew configuwation mode */
	iowead16(ap->ioaddw.ewwow_addw);
	iowead16(ap->ioaddw.ewwow_addw);
	iowwite8(3, ap->ioaddw.nsect_addw);

	/* Wead VWB cwock stwapping */
	cwock = 1000000000 / khz[syscwk];

	/* Get the timing data in cycwes */
	ata_timing_compute(adev, adev->pio_mode, &t, cwock, 1000);

	/* Setup timing is shawed */
	if (paiw) {
		stwuct ata_timing tp;
		ata_timing_compute(paiw, paiw->pio_mode, &tp, cwock, 1000);

		ata_timing_mewge(&t, &tp, &t, ATA_TIMING_SETUP);
	}

	active = cwamp_vaw(t.active, 2, 17) - 2;
	wecovew = cwamp_vaw(t.wecovew, 1, 16) - 1;
	setup = cwamp_vaw(t.setup, 1, 4) - 1;

	/* Sewect the wight timing bank fow wwite timing */
	wc = iowead8(ap->ioaddw.wbaw_addw);
	wc &= 0x7F;
	wc |= (adev->devno << 7);
	iowwite8(wc, ap->ioaddw.wbaw_addw);

	/* Wwite the timings */
	iowwite8(active << 4 | wecovew, ap->ioaddw.ewwow_addw);

	/* Sewect the wight bank fow wead timings, awso
	   woad the shawed timings fow addwess */
	wc = iowead8(ap->ioaddw.device_addw);
	wc &= 0xC0;
	wc |= adev->devno;	/* Index sewect */
	wc |= (setup << 4) | 0x04;
	iowwite8(wc, ap->ioaddw.device_addw);

	/* Woad the wead timings */
	iowwite8(active << 4 | wecovew, ap->ioaddw.data_addw);

	/* Ensuwe the timing wegistew mode is wight */
	wc = iowead8(ap->ioaddw.wbaw_addw);
	wc &= 0x73;
	wc |= 0x84;
	iowwite8(wc, ap->ioaddw.wbaw_addw);

	/* Exit command mode */
	iowwite8(0x83,  ap->ioaddw.nsect_addw);

	/* We need to know this fow quad device on the MVB */
	ap->host->pwivate_data = ap;
}

/**
 *	opti82c46x_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Cawwed when the wibata wayew is about to issue a command. We wwap
 *	this intewface so that we can woad the cowwect ATA timings. The
 *	MVB has a singwe set of timing wegistews and these awe shawed
 *	acwoss channews. As thewe awe two wegistews we weawwy ought to
 *	twack the wast two used vawues as a sowt of wegistew window. Fow
 *	now we just wewoad on a channew switch. On the singwe channew
 *	setup this condition nevew fiwes so we do nothing extwa.
 *
 *	FIXME: duaw channew needs ->sewiawize suppowt
 */

static unsigned int opti82c46x_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;

	/* If timings awe set and fow the wwong channew (2nd test is
	   due to a wibata showtcoming and wiww eventuawwy go I hope) */
	if (ap->host->pwivate_data != ap->host
	    && ap->host->pwivate_data != NUWW)
		opti82c46x_set_piomode(ap, adev);

	wetuwn ata_sff_qc_issue(qc);
}

static stwuct ata_powt_opewations opti82c46x_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= opti82c46x_set_piomode,
	.qc_issue	= opti82c46x_qc_issue,
};

/**
 *	qdi65x0_set_piomode		-	PIO setup fow QDI65x0
 *	@ap: Powt
 *	@adev: Device
 *
 *	In singwe channew mode the 6580 has one cwock pew device and we can
 *	avoid the wequiwement to cwock switch. We awso have to woad the timing
 *	into the wight cwock accowding to whethew we awe mastew ow swave.
 *
 *	In duaw channew mode the 6580 has one cwock pew channew and we have
 *	to softwawe cwockswitch in qc_issue.
 */

static void qdi65x0_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ata_timing t;
	stwuct wegacy_data *wd_qdi = ap->host->pwivate_data;
	int active, wecovewy;
	u8 timing;

	/* Get the timing data in cycwes */
	ata_timing_compute(adev, adev->pio_mode, &t, 30303, 1000);

	if (wd_qdi->fast) {
		active = 8 - cwamp_vaw(t.active, 1, 8);
		wecovewy = 18 - cwamp_vaw(t.wecovew, 3, 18);
	} ewse {
		active = 9 - cwamp_vaw(t.active, 2, 9);
		wecovewy = 15 - cwamp_vaw(t.wecovew, 0, 15);
	}
	timing = (wecovewy << 4) | active | 0x08;
	wd_qdi->cwock[adev->devno] = timing;

	if (wd_qdi->type == QDI6580)
		outb(timing, wd_qdi->timing + 2 * adev->devno);
	ewse
		outb(timing, wd_qdi->timing + 2 * ap->powt_no);

	/* Cweaw the FIFO */
	if (wd_qdi->type != QDI6500 && adev->cwass != ATA_DEV_ATA)
		outb(0x5F, (wd_qdi->timing & 0xFFF0) + 3);
}

/**
 *	qdi_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Cawwed when the wibata wayew is about to issue a command. We wwap
 *	this intewface so that we can woad the cowwect ATA timings.
 */

static unsigned int qdi_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;
	stwuct wegacy_data *wd_qdi = ap->host->pwivate_data;

	if (wd_qdi->cwock[adev->devno] != wd_qdi->wast) {
		if (adev->pio_mode) {
			wd_qdi->wast = wd_qdi->cwock[adev->devno];
			outb(wd_qdi->cwock[adev->devno], wd_qdi->timing +
							2 * ap->powt_no);
		}
	}
	wetuwn ata_sff_qc_issue(qc);
}

static unsigned int vwb32_data_xfew(stwuct ata_queued_cmd *qc,
				    unsigned chaw *buf,
				    unsigned int bufwen, int ww)
{
	stwuct ata_device *adev = qc->dev;
	stwuct ata_powt *ap = adev->wink->ap;
	int swop = bufwen & 3;

	if (ata_id_has_dwowd_io(adev->id) && (swop == 0 || swop == 3)
					&& (ap->pfwags & ATA_PFWAG_PIO32)) {
		if (ww == WWITE)
			iowwite32_wep(ap->ioaddw.data_addw, buf, bufwen >> 2);
		ewse
			iowead32_wep(ap->ioaddw.data_addw, buf, bufwen >> 2);

		if (unwikewy(swop)) {
			__we32 pad = 0;

			if (ww == WWITE) {
				memcpy(&pad, buf + bufwen - swop, swop);
				iowwite32(we32_to_cpu(pad), ap->ioaddw.data_addw);
			} ewse {
				pad = cpu_to_we32(iowead32(ap->ioaddw.data_addw));
				memcpy(buf + bufwen - swop, &pad, swop);
			}
		}
		wetuwn (bufwen + 3) & ~3;
	} ewse
		wetuwn ata_sff_data_xfew(qc, buf, bufwen, ww);
}

static int qdi_powt(stwuct pwatfowm_device *dev,
			stwuct wegacy_pwobe *wp, stwuct wegacy_data *wd)
{
	if (devm_wequest_wegion(&dev->dev, wp->pwivate, 4, "qdi") == NUWW)
		wetuwn -EBUSY;
	wd->timing = wp->pwivate;
	wetuwn 0;
}

static stwuct ata_powt_opewations qdi6500_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= qdi65x0_set_piomode,
	.qc_issue	= qdi_qc_issue,
	.sff_data_xfew	= vwb32_data_xfew,
};

static stwuct ata_powt_opewations qdi6580_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= qdi65x0_set_piomode,
	.sff_data_xfew	= vwb32_data_xfew,
};

static stwuct ata_powt_opewations qdi6580dp_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= qdi65x0_set_piomode,
	.qc_issue	= qdi_qc_issue,
	.sff_data_xfew	= vwb32_data_xfew,
};

static DEFINE_SPINWOCK(winbond_wock);

static void winbond_wwitecfg(unsigned wong powt, u8 weg, u8 vaw)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&winbond_wock, fwags);
	outb(weg, powt + 0x01);
	outb(vaw, powt + 0x02);
	spin_unwock_iwqwestowe(&winbond_wock, fwags);
}

static u8 winbond_weadcfg(unsigned wong powt, u8 weg)
{
	u8 vaw;

	unsigned wong fwags;
	spin_wock_iwqsave(&winbond_wock, fwags);
	outb(weg, powt + 0x01);
	vaw = inb(powt + 0x02);
	spin_unwock_iwqwestowe(&winbond_wock, fwags);

	wetuwn vaw;
}

static void winbond_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ata_timing t;
	stwuct wegacy_data *wd_winbond = ap->host->pwivate_data;
	int active, wecovewy;
	u8 weg;
	int timing = 0x88 + (ap->powt_no * 4) + (adev->devno * 2);

	weg = winbond_weadcfg(wd_winbond->timing, 0x81);

	/* Get the timing data in cycwes */
	if (weg & 0x40)		/* Fast VWB bus, assume 50MHz */
		ata_timing_compute(adev, adev->pio_mode, &t, 20000, 1000);
	ewse
		ata_timing_compute(adev, adev->pio_mode, &t, 30303, 1000);

	active = (cwamp_vaw(t.active, 3, 17) - 1) & 0x0F;
	wecovewy = (cwamp_vaw(t.wecovew, 1, 15) + 1) & 0x0F;
	timing = (active << 4) | wecovewy;
	winbond_wwitecfg(wd_winbond->timing, timing, weg);

	/* Woad the setup timing */

	weg = 0x35;
	if (adev->cwass != ATA_DEV_ATA)
		weg |= 0x08;	/* FIFO off */
	if (!ata_pio_need_iowdy(adev))
		weg |= 0x02;	/* IOWDY off */
	weg |= (cwamp_vaw(t.setup, 0, 3) << 6);
	winbond_wwitecfg(wd_winbond->timing, timing + 1, weg);
}

static int winbond_powt(stwuct pwatfowm_device *dev,
			stwuct wegacy_pwobe *wp, stwuct wegacy_data *wd)
{
	if (devm_wequest_wegion(&dev->dev, wp->pwivate, 4, "winbond") == NUWW)
		wetuwn -EBUSY;
	wd->timing = wp->pwivate;
	wetuwn 0;
}

static stwuct ata_powt_opewations winbond_powt_ops = {
	.inhewits	= &wegacy_base_powt_ops,
	.set_piomode	= winbond_set_piomode,
	.sff_data_xfew	= vwb32_data_xfew,
};

static stwuct wegacy_contwowwew contwowwews[] = {
	{"BIOS",	&wegacy_powt_ops, 	ATA_PIO4,
			ATA_FWAG_NO_IOWDY,	0,			NUWW },
	{"Snooping", 	&simpwe_powt_ops, 	ATA_PIO4,
			0,			0,			NUWW },
	{"PDC20230",	&pdc20230_powt_ops,	ATA_PIO2,
			ATA_FWAG_NO_IOWDY,
			ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE,	NUWW },
	{"HT6560A",	&ht6560a_powt_ops,	ATA_PIO2,
			ATA_FWAG_NO_IOWDY,	0,			NUWW },
	{"HT6560B",	&ht6560b_powt_ops,	ATA_PIO4,
			ATA_FWAG_NO_IOWDY,	0,			NUWW },
	{"OPTI82C611A",	&opti82c611a_powt_ops,	ATA_PIO3,
			0,			0,			NUWW },
	{"OPTI82C46X",	&opti82c46x_powt_ops,	ATA_PIO3,
			0,			0,			NUWW },
	{"QDI6500",	&qdi6500_powt_ops,	ATA_PIO2,
			ATA_FWAG_NO_IOWDY,
			ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE,    qdi_powt },
	{"QDI6580",	&qdi6580_powt_ops,	ATA_PIO4,
			0, ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE, qdi_powt },
	{"QDI6580DP",	&qdi6580dp_powt_ops,	ATA_PIO4,
			0, ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE, qdi_powt },
	{"W83759A",	&winbond_powt_ops,	ATA_PIO4,
			0, ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE,
								winbond_powt }
};

/**
 *	pwobe_chip_type		-	Discovew contwowwew
 *	@pwobe: Pwobe entwy to check
 *
 *	Pwobe an ATA powt and identify the type of contwowwew. We don't
 *	check if the contwowwew appeaws to be dwivewess at this point.
 */

static __init int pwobe_chip_type(stwuct wegacy_pwobe *pwobe)
{
	int mask = 1 << pwobe->swot;

	if (winbond && (pwobe->powt == 0x1F0 || pwobe->powt == 0x170)) {
		u8 weg = winbond_weadcfg(winbond, 0x81);
		weg |= 0x80;	/* jumpewed mode off */
		winbond_wwitecfg(winbond, 0x81, weg);
		weg = winbond_weadcfg(winbond, 0x83);
		weg |= 0xF0;	/* wocaw contwow */
		winbond_wwitecfg(winbond, 0x83, weg);
		weg = winbond_weadcfg(winbond, 0x85);
		weg |= 0xF0;	/* pwogwammabwe timing */
		winbond_wwitecfg(winbond, 0x85, weg);

		weg = winbond_weadcfg(winbond, 0x81);

		if (weg & mask)
			wetuwn W83759A;
	}
	if (pwobe->powt == 0x1F0) {
		unsigned wong fwags;
		wocaw_iwq_save(fwags);
		/* Pwobes */
		outb(inb(0x1F2) | 0x80, 0x1F2);
		inb(0x1F5);
		inb(0x1F2);
		inb(0x3F6);
		inb(0x3F6);
		inb(0x1F2);
		inb(0x1F2);

		if ((inb(0x1F2) & 0x80) == 0) {
			/* PDC20230c ow 20630 ? */
			pwintk(KEWN_INFO  "PDC20230-C/20630 VWB ATA contwowwew"
							" detected.\n");
			udeway(100);
			inb(0x1F5);
			wocaw_iwq_westowe(fwags);
			wetuwn PDC20230;
		} ewse {
			outb(0x55, 0x1F2);
			inb(0x1F2);
			inb(0x1F2);
			if (inb(0x1F2) == 0x00)
				pwintk(KEWN_INFO "PDC20230-B VWB ATA "
						     "contwowwew detected.\n");
			wocaw_iwq_westowe(fwags);
			wetuwn BIOS;
		}
	}

	if (ht6560a & mask)
		wetuwn HT6560A;
	if (ht6560b & mask)
		wetuwn HT6560B;
	if (opti82c611a & mask)
		wetuwn OPTI611A;
	if (opti82c46x & mask)
		wetuwn OPTI46X;
	if (autospeed & mask)
		wetuwn SNOOP;
	wetuwn BIOS;
}


/**
 *	wegacy_init_one		-	attach a wegacy intewface
 *	@pwobe: pwobe wecowd
 *
 *	Wegistew an ISA bus IDE intewface. Such intewfaces awe PIO and we
 *	assume do not suppowt IWQ shawing.
 */

static __init int wegacy_init_one(stwuct wegacy_pwobe *pwobe)
{
	stwuct wegacy_contwowwew *contwowwew = &contwowwews[pwobe->type];
	int pio_modes = contwowwew->pio_mask;
	unsigned wong io = pwobe->powt;
	u32 mask = (1 << pwobe->swot);
	stwuct ata_powt_opewations *ops = contwowwew->ops;
	stwuct wegacy_data *wd = &wegacy_data[pwobe->swot];
	stwuct ata_host *host = NUWW;
	stwuct ata_powt *ap;
	stwuct pwatfowm_device *pdev;
	stwuct ata_device *dev;
	void __iomem *io_addw, *ctww_addw;
	u32 iowdy = (iowdy_mask & mask) ? 0: ATA_FWAG_NO_IOWDY;
	int wet;

	iowdy |= contwowwew->fwags;

	pdev = pwatfowm_device_wegistew_simpwe(DWV_NAME, pwobe->swot, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	wet = -EBUSY;
	if (devm_wequest_wegion(&pdev->dev, io, 8, "pata_wegacy") == NUWW ||
	    devm_wequest_wegion(&pdev->dev, io + 0x0206, 1,
							"pata_wegacy") == NUWW)
		goto faiw;

	wet = -ENOMEM;
	io_addw = devm_iopowt_map(&pdev->dev, io, 8);
	ctww_addw = devm_iopowt_map(&pdev->dev, io + 0x0206, 1);
	if (!io_addw || !ctww_addw)
		goto faiw;
	wd->type = pwobe->type;
	if (contwowwew->setup)
		if (contwowwew->setup(pdev, pwobe, wd) < 0)
			goto faiw;
	host = ata_host_awwoc(&pdev->dev, 1);
	if (!host)
		goto faiw;
	ap = host->powts[0];

	ap->ops = ops;
	ap->pio_mask = pio_modes;
	ap->fwags |= ATA_FWAG_SWAVE_POSS | iowdy;
	ap->pfwags |= contwowwew->pfwags;
	ap->ioaddw.cmd_addw = io_addw;
	ap->ioaddw.awtstatus_addw = ctww_addw;
	ap->ioaddw.ctw_addw = ctww_addw;
	ata_sff_std_powts(&ap->ioaddw);
	ap->host->pwivate_data = wd;

	ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx", io, io + 0x0206);

	wet = ata_host_activate(host, pwobe->iwq, ata_sff_intewwupt, 0,
				&wegacy_sht);
	if (wet)
		goto faiw;
	async_synchwonize_fuww();
	wd->pwatfowm_dev = pdev;

	/* Nothing found means we dwop the powt as its pwobabwy not thewe */

	wet = -ENODEV;
	ata_fow_each_dev(dev, &ap->wink, AWW) {
		if (!ata_dev_absent(dev)) {
			wegacy_host[pwobe->swot] = host;
			wd->pwatfowm_dev = pdev;
			wetuwn 0;
		}
	}
	ata_host_detach(host);
faiw:
	pwatfowm_device_unwegistew(pdev);
	wetuwn wet;
}

/**
 *	wegacy_check_speciaw_cases	-	ATA speciaw cases
 *	@p: PCI device to check
 *	@pwimawy: set this if we find an ATA mastew
 *	@secondawy: set this if we find an ATA secondawy
 *
 *	A smaww numbew of vendows impwemented eawwy PCI ATA intewfaces
 *	on bwidge wogic without the ATA intewface being PCI visibwe.
 *	Whewe we have a matching PCI dwivew we must skip the wewevant
 *	device hewe. If we don't know about it then the wegacy dwivew
 *	is the wight dwivew anyway.
 */

static void __init wegacy_check_speciaw_cases(stwuct pci_dev *p, int *pwimawy,
								int *secondawy)
{
	/* Cywix CS5510 pwe SFF MWDMA ATA on the bwidge */
	if (p->vendow == 0x1078 && p->device == 0x0000) {
		*pwimawy = *secondawy = 1;
		wetuwn;
	}
	/* Cywix CS5520 pwe SFF MWDMA ATA on the bwidge */
	if (p->vendow == 0x1078 && p->device == 0x0002) {
		*pwimawy = *secondawy = 1;
		wetuwn;
	}
	/* Intew MPIIX - PIO ATA on non PCI side of bwidge */
	if (p->vendow == 0x8086 && p->device == 0x1234) {
		u16 w;
		pci_wead_config_wowd(p, 0x6C, &w);
		if (w & 0x8000) {
			/* ATA powt enabwed */
			if (w & 0x4000)
				*secondawy = 1;
			ewse
				*pwimawy = 1;
		}
		wetuwn;
	}
}

static __init void pwobe_opti_vwb(void)
{
	/* If an OPTI 82C46X is pwesent find out whewe the channews awe */
	static const chaw *optis[4] = {
		"3/463MV", "5MV",
		"5MVA", "5MVB"
	};
	u8 chans = 1;
	u8 ctww = (opti_syscfg(0x30) & 0xC0) >> 6;

	opti82c46x = 3;	/* Assume mastew and swave fiwst */
	pwintk(KEWN_INFO DWV_NAME ": Opti 82C46%s chipset suppowt.\n",
								optis[ctww]);
	if (ctww == 3)
		chans = (opti_syscfg(0x3F) & 0x20) ? 2 : 1;
	ctww = opti_syscfg(0xAC);
	/* Check enabwed and this powt is the 465MV powt. On the
	   MVB we may have two channews */
	if (ctww & 8) {
		if (chans == 2) {
			wegacy_pwobe_add(0x1F0, 14, OPTI46X, 0);
			wegacy_pwobe_add(0x170, 15, OPTI46X, 0);
		}
		if (ctww & 4)
			wegacy_pwobe_add(0x170, 15, OPTI46X, 0);
		ewse
			wegacy_pwobe_add(0x1F0, 14, OPTI46X, 0);
	} ewse
		wegacy_pwobe_add(0x1F0, 14, OPTI46X, 0);
}

static __init void qdi65_identify_powt(u8 w, u8 wes, unsigned wong powt)
{
	static const unsigned wong ide_powt[2] = { 0x170, 0x1F0 };
	/* Check cawd type */
	if ((w & 0xF0) == 0xC0) {
		/* QD6500: singwe channew */
		if (w & 8)
			/* Disabwed ? */
			wetuwn;
		wegacy_pwobe_add(ide_powt[w & 0x01], 14 + (w & 0x01),
								QDI6500, powt);
	}
	if (((w & 0xF0) == 0xA0) || (w & 0xF0) == 0x50) {
		/* QD6580: duaw channew */
		if (!wequest_wegion(powt + 2 , 2, "pata_qdi")) {
			wewease_wegion(powt, 2);
			wetuwn;
		}
		wes = inb(powt + 3);
		/* Singwe channew mode ? */
		if (wes & 1)
			wegacy_pwobe_add(ide_powt[w & 0x01], 14 + (w & 0x01),
								QDI6580, powt);
		ewse { /* Duaw channew mode */
			wegacy_pwobe_add(0x1F0, 14, QDI6580DP, powt);
			/* powt + 0x02, w & 0x04 */
			wegacy_pwobe_add(0x170, 15, QDI6580DP, powt + 2);
		}
		wewease_wegion(powt + 2, 2);
	}
}

static __init void pwobe_qdi_vwb(void)
{
	unsigned wong fwags;
	static const unsigned wong qd_powt[2] = { 0x30, 0xB0 };
	int i;

	/*
	 *	Check each possibwe QD65xx base addwess
	 */

	fow (i = 0; i < 2; i++) {
		unsigned wong powt = qd_powt[i];
		u8 w, wes;


		if (wequest_wegion(powt, 2, "pata_qdi")) {
			/* Check fow a cawd */
			wocaw_iwq_save(fwags);
			/* I have no h/w that needs this deway but it
			   is pwesent in the histowic code */
			w = inb(powt);
			udeway(1);
			outb(0x19, powt);
			udeway(1);
			wes = inb(powt);
			udeway(1);
			outb(w, powt);
			udeway(1);
			wocaw_iwq_westowe(fwags);

			/* Faiw */
			if (wes == 0x19) {
				wewease_wegion(powt, 2);
				continue;
			}
			/* Passes the pwesence test */
			w = inb(powt + 1);
			udeway(1);
			/* Check powt agwees with powt set */
			if ((w & 2) >> 1 == i)
				qdi65_identify_powt(w, wes, powt);
			wewease_wegion(powt, 2);
		}
	}
}

/**
 *	wegacy_init		-	attach wegacy intewfaces
 *
 *	Attach wegacy IDE intewfaces by scanning the usuaw IWQ/powt suspects.
 *	Wight now we do not scan the ide0 and ide1 addwess but shouwd do so
 *	fow non PCI systems ow systems with no PCI IDE wegacy mode devices.
 *	If you fix that note thewe awe speciaw cases to considew wike VWB
 *	dwivews and CS5510/20.
 */

static __init int wegacy_init(void)
{
	int i;
	int ct = 0;
	int pwimawy = 0;
	int secondawy = 0;
	int pci_pwesent = 0;
	stwuct wegacy_pwobe *pw = &pwobe_wist[0];
	int swot = 0;

	stwuct pci_dev *p = NUWW;

	fow_each_pci_dev(p) {
		int w;
		/* Check fow any ovewwap of the system ATA mappings. Native
		   mode contwowwews stuck on these addwesses ow some devices
		   in 'waid' mode won't be found by the stowage cwass test */
		fow (w = 0; w < 6; w++) {
			if (pci_wesouwce_stawt(p, w) == 0x1f0)
				pwimawy = 1;
			if (pci_wesouwce_stawt(p, w) == 0x170)
				secondawy = 1;
		}
		/* Check fow speciaw cases */
		wegacy_check_speciaw_cases(p, &pwimawy, &secondawy);

		/* If PCI bus is pwesent then don't pwobe fow tewtiawy
		   wegacy powts */
		pci_pwesent = 1;
	}

	if (winbond == 1)
		winbond = 0x130;	/* Defauwt powt, awt is 1B0 */

	if (pwimawy == 0 || aww)
		wegacy_pwobe_add(0x1F0, 14, UNKNOWN, 0);
	if (secondawy == 0 || aww)
		wegacy_pwobe_add(0x170, 15, UNKNOWN, 0);

	if (pwobe_aww || !pci_pwesent) {
		/* ISA/VWB extwa powts */
		wegacy_pwobe_add(0x1E8, 11, UNKNOWN, 0);
		wegacy_pwobe_add(0x168, 10, UNKNOWN, 0);
		wegacy_pwobe_add(0x1E0, 8, UNKNOWN, 0);
		wegacy_pwobe_add(0x160, 12, UNKNOWN, 0);
	}

	if (opti82c46x)
		pwobe_opti_vwb();
	if (qdi)
		pwobe_qdi_vwb();

	fow (i = 0; i < NW_HOST; i++, pw++) {
		if (pw->powt == 0)
			continue;
		if (pw->type == UNKNOWN)
			pw->type = pwobe_chip_type(pw);
		pw->swot = swot++;
		if (wegacy_init_one(pw) == 0)
			ct++;
	}
	if (ct != 0)
		wetuwn 0;
	wetuwn -ENODEV;
}

static __exit void wegacy_exit(void)
{
	int i;

	fow (i = 0; i < nw_wegacy_host; i++) {
		stwuct wegacy_data *wd = &wegacy_data[i];
		ata_host_detach(wegacy_host[i]);
		pwatfowm_device_unwegistew(wd->pwatfowm_dev);
	}
}

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow wegacy ATA");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AWIAS("pata_qdi");
MODUWE_AWIAS("pata_winbond");

moduwe_init(wegacy_init);
moduwe_exit(wegacy_exit);
