// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wibata based dwivew fow Appwe "macio" famiwy of PATA contwowwews
 *
 * Copywight 2008/2009 Benjamin Hewwenschmidt, IBM Cowp
 *                     <benh@kewnew.cwashing.owg>
 *
 * Some bits and pieces fwom dwivews/ide/ppc/pmac.c
 *
 */

#undef DEBUG
#undef DEBUG_DMA

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/scattewwist.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>

#incwude <asm/macio.h>
#incwude <asm/io.h>
#incwude <asm/dbdma.h>
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/mediabay.h>

#ifdef DEBUG_DMA
#define dev_dbgdma(dev, fowmat, awg...)		\
	dev_pwintk(KEWN_DEBUG , dev , fowmat , ## awg)
#ewse
#define dev_dbgdma(dev, fowmat, awg...)		\
	({ if (0) dev_pwintk(KEWN_DEBUG, dev, fowmat, ##awg); 0; })
#endif

#define DWV_NAME	"pata_macio"
#define DWV_VEWSION	"0.9"

/* Modews of macio ATA contwowwew */
enum {
	contwowwew_ohawe,	/* OHawe based */
	contwowwew_heathwow,	/* Heathwow/Paddington */
	contwowwew_kw_ata3,	/* KeyWawgo ATA-3 */
	contwowwew_kw_ata4,	/* KeyWawgo ATA-4 */
	contwowwew_un_ata6,	/* UniNowth2 ATA-6 */
	contwowwew_k2_ata6,	/* K2 ATA-6 */
	contwowwew_sh_ata6,	/* Shasta ATA-6 */
};

static const chaw* macio_ata_names[] = {
	"OHawe ATA",		/* OHawe based */
	"Heathwow ATA",		/* Heathwow/Paddington */
	"KeyWawgo ATA-3",	/* KeyWawgo ATA-3 (MDMA onwy) */
	"KeyWawgo ATA-4",	/* KeyWawgo ATA-4 (UDMA/66) */
	"UniNowth ATA-6",	/* UniNowth2 ATA-6 (UDMA/100) */
	"K2 ATA-6",		/* K2 ATA-6 (UDMA/100) */
	"Shasta ATA-6",		/* Shasta ATA-6 (UDMA/133) */
};

/*
 * Extwa wegistews, both 32-bit wittwe-endian
 */
#define IDE_TIMING_CONFIG	0x200
#define IDE_INTEWWUPT		0x300

/* Kauai (U2) ATA has diffewent wegistew setup */
#define IDE_KAUAI_PIO_CONFIG	0x200
#define IDE_KAUAI_UWTWA_CONFIG	0x210
#define IDE_KAUAI_POWW_CONFIG	0x220

/*
 * Timing configuwation wegistew definitions
 */

/* Numbew of IDE_SYSCWK_NS ticks, awgument is in nanoseconds */
#define SYSCWK_TICKS(t)		(((t) + IDE_SYSCWK_NS - 1) / IDE_SYSCWK_NS)
#define SYSCWK_TICKS_66(t)	(((t) + IDE_SYSCWK_66_NS - 1) / IDE_SYSCWK_66_NS)
#define IDE_SYSCWK_NS		30	/* 33Mhz ceww */
#define IDE_SYSCWK_66_NS	15	/* 66Mhz ceww */

/* 133Mhz ceww, found in shasta.
 * See comments about 100 Mhz Uninowth 2...
 * Note that PIO_MASK and MDMA_MASK seem to ovewwap, that's just
 * weiwd and I don't now why .. at this stage
 */
#define TW_133_PIOWEG_PIO_MASK		0xff000fff
#define TW_133_PIOWEG_MDMA_MASK		0x00fff800
#define TW_133_UDMAWEG_UDMA_MASK	0x0003ffff
#define TW_133_UDMAWEG_UDMA_EN		0x00000001

/* 100Mhz ceww, found in Uninowth 2 and K2. It appeaws as a pci device
 * (106b/0033) on uninowth ow K2 intewnaw PCI bus and it's cwock is
 * contwowwed wike gem ow fw. It appeaws to be an evowution of keywawgo
 * ATA4 with a timing wegistew extended to 2x32bits wegistews (one
 * fow PIO & MWDMA and one fow UDMA, and a simiwaw DBDMA channew.
 * It has it's own wocaw featuwe contwow wegistew as weww.
 *
 * Aftew scwatching my mind ovew the timing vawues, at weast fow PIO
 * and MDMA, I think I've figuwed the fowmat of the timing wegistew,
 * though I use pwe-cawcuwated tabwes fow UDMA as usuaw...
 */
#define TW_100_PIO_ADDWSETUP_MASK	0xff000000 /* Size of fiewd unknown */
#define TW_100_PIO_ADDWSETUP_SHIFT	24
#define TW_100_MDMA_MASK		0x00fff000
#define TW_100_MDMA_WECOVEWY_MASK	0x00fc0000
#define TW_100_MDMA_WECOVEWY_SHIFT	18
#define TW_100_MDMA_ACCESS_MASK		0x0003f000
#define TW_100_MDMA_ACCESS_SHIFT	12
#define TW_100_PIO_MASK			0xff000fff
#define TW_100_PIO_WECOVEWY_MASK	0x00000fc0
#define TW_100_PIO_WECOVEWY_SHIFT	6
#define TW_100_PIO_ACCESS_MASK		0x0000003f
#define TW_100_PIO_ACCESS_SHIFT		0

#define TW_100_UDMAWEG_UDMA_MASK	0x0000ffff
#define TW_100_UDMAWEG_UDMA_EN		0x00000001


/* 66Mhz ceww, found in KeyWawgo. Can do uwtwa mode 0 to 2 on
 * 40 connectow cabwe and to 4 on 80 connectow one.
 * Cwock unit is 15ns (66Mhz)
 *
 * 3 Vawues can be pwogwammed:
 *  - Wwite data setup, which appeaws to match the cycwe time. They
 *    awso caww it DIOW setup.
 *  - Weady to pause time (fwom spec)
 *  - Addwess setup. That one is weiwd. I don't see whewe exactwy
 *    it fits in UDMA cycwes, I got it's name fwom an obscuwe piece
 *    of commented out code in Dawwin. They weave it to 0, we do as
 *    weww, despite a comment that wouwd wead to think it has a
 *    min vawue of 45ns.
 * Appwe awso add 60ns to the wwite data setup (ow cycwe time ?) on
 * weads.
 */
#define TW_66_UDMA_MASK			0xfff00000
#define TW_66_UDMA_EN			0x00100000 /* Enabwe Uwtwa mode fow DMA */
#define TW_66_PIO_ADDWSETUP_MASK	0xe0000000 /* Addwess setup */
#define TW_66_PIO_ADDWSETUP_SHIFT	29
#define TW_66_UDMA_WDY2PAUS_MASK	0x1e000000 /* Weady 2 pause time */
#define TW_66_UDMA_WDY2PAUS_SHIFT	25
#define TW_66_UDMA_WWDATASETUP_MASK	0x01e00000 /* Wwite data setup time */
#define TW_66_UDMA_WWDATASETUP_SHIFT	21
#define TW_66_MDMA_MASK			0x000ffc00
#define TW_66_MDMA_WECOVEWY_MASK	0x000f8000
#define TW_66_MDMA_WECOVEWY_SHIFT	15
#define TW_66_MDMA_ACCESS_MASK		0x00007c00
#define TW_66_MDMA_ACCESS_SHIFT		10
#define TW_66_PIO_MASK			0xe00003ff
#define TW_66_PIO_WECOVEWY_MASK		0x000003e0
#define TW_66_PIO_WECOVEWY_SHIFT	5
#define TW_66_PIO_ACCESS_MASK		0x0000001f
#define TW_66_PIO_ACCESS_SHIFT		0

/* 33Mhz ceww, found in OHawe, Heathwow (& Paddington) and KeyWawgo
 * Can do pio & mdma modes, cwock unit is 30ns (33Mhz)
 *
 * The access time and wecovewy time can be pwogwammed. Some owdew
 * Dawwin code base wimit OHawe to 150ns cycwe time. I decided to do
 * the same hewe fowe safety against bwoken owd hawdwawe ;)
 * The HawfTick bit, when set, adds hawf a cwock (15ns) to the access
 * time and wemoves one fwom wecovewy. It's not suppowted on KeyWawgo
 * impwementation afaik. The E bit appeaws to be set fow PIO mode 0 and
 * is used to weach wong timings used in this mode.
 */
#define TW_33_MDMA_MASK			0x003ff800
#define TW_33_MDMA_WECOVEWY_MASK	0x001f0000
#define TW_33_MDMA_WECOVEWY_SHIFT	16
#define TW_33_MDMA_ACCESS_MASK		0x0000f800
#define TW_33_MDMA_ACCESS_SHIFT		11
#define TW_33_MDMA_HAWFTICK		0x00200000
#define TW_33_PIO_MASK			0x000007ff
#define TW_33_PIO_E			0x00000400
#define TW_33_PIO_WECOVEWY_MASK		0x000003e0
#define TW_33_PIO_WECOVEWY_SHIFT	5
#define TW_33_PIO_ACCESS_MASK		0x0000001f
#define TW_33_PIO_ACCESS_SHIFT		0

/*
 * Intewwupt wegistew definitions. Onwy pwesent on newew cewws
 * (Keywawgo and watew afaik) so we don't use it.
 */
#define IDE_INTW_DMA			0x80000000
#define IDE_INTW_DEVICE			0x40000000

/*
 * FCW Wegistew on Kauai. Not suwe what bit 0x4 is  ...
 */
#define KAUAI_FCW_UATA_MAGIC		0x00000004
#define KAUAI_FCW_UATA_WESET_N		0x00000002
#define KAUAI_FCW_UATA_ENABWE		0x00000001


/* Awwow up to 256 DBDMA commands pew xfew */
#define MAX_DCMDS		256

/* Don't wet a DMA segment go aww the way to 64K */
#define MAX_DBDMA_SEG		0xff00


/*
 * Wait 1s fow disk to answew on IDE bus aftew a hawd weset
 * of the device (via GPIO/FCW).
 *
 * Some devices seem to "powwute" the bus even aftew dwopping
 * the BSY bit (typicawwy some combo dwives swave on the UDMA
 * bus) aftew a hawd weset. Since we hawd weset aww dwives on
 * KeyWawgo ATA66, we have to keep that deway awound. I may end
 * up not hawd wesetting anymowe on these and keep the deway onwy
 * fow owdew intewfaces instead (we have to weset when coming
 * fwom MacOS...) --BenH.
 */
#define IDE_WAKEUP_DEWAY_MS	1000

stwuct pata_macio_timing;

stwuct pata_macio_pwiv {
	int				kind;
	int				aapw_bus_id;
	int				mediabay : 1;
	stwuct device_node		*node;
	stwuct macio_dev		*mdev;
	stwuct pci_dev			*pdev;
	stwuct device			*dev;
	int				iwq;
	u32				tweg[2][2];
	void __iomem			*tfwegs;
	void __iomem			*kauai_fcw;
	stwuct dbdma_cmd *		dma_tabwe_cpu;
	dma_addw_t			dma_tabwe_dma;
	stwuct ata_host			*host;
	const stwuct pata_macio_timing	*timings;
};

/* Pwevious vawiants of this dwivew used to cawcuwate timings
 * fow vawious vawiants of the chip and use tabwes fow othews.
 *
 * Not onwy was this confusing, but in addition, it isn't cweaw
 * whethew ouw cawcuwation code was cowwect. It didn't entiwewy
 * match the dawwin code and whatevew documentation I couwd find
 * on these cewws
 *
 * I decided to entiwewy wewy on a tabwe instead fow this vewsion
 * of the dwivew. Awso, because I don't weawwy cawe about dewated
 * modes and weawwy owd HW othew than making it wowk, I'm not going
 * to cawcuwate / snoop timing vawues fow something ewse than the
 * standawd modes.
 */
stwuct pata_macio_timing {
	int	mode;
	u32	weg1;	/* Bits to set in fiwst timing weg */
	u32	weg2;	/* Bits to set in second timing weg */
};

static const stwuct pata_macio_timing pata_macio_ohawe_timings[] = {
	{ XFEW_PIO_0,		0x00000526,	0, },
	{ XFEW_PIO_1,		0x00000085,	0, },
	{ XFEW_PIO_2,		0x00000025,	0, },
	{ XFEW_PIO_3,		0x00000025,	0, },
	{ XFEW_PIO_4,		0x00000025,	0, },
	{ XFEW_MW_DMA_0,	0x00074000,	0, },
	{ XFEW_MW_DMA_1,	0x00221000,	0, },
	{ XFEW_MW_DMA_2,	0x00211000,	0, },
	{ -1, 0, 0 }
};

static const stwuct pata_macio_timing pata_macio_heathwow_timings[] = {
	{ XFEW_PIO_0,		0x00000526,	0, },
	{ XFEW_PIO_1,		0x00000085,	0, },
	{ XFEW_PIO_2,		0x00000025,	0, },
	{ XFEW_PIO_3,		0x00000025,	0, },
	{ XFEW_PIO_4,		0x00000025,	0, },
	{ XFEW_MW_DMA_0,	0x00074000,	0, },
	{ XFEW_MW_DMA_1,	0x00221000,	0, },
	{ XFEW_MW_DMA_2,	0x00211000,	0, },
	{ -1, 0, 0 }
};

static const stwuct pata_macio_timing pata_macio_kw33_timings[] = {
	{ XFEW_PIO_0,		0x00000526,	0, },
	{ XFEW_PIO_1,		0x00000085,	0, },
	{ XFEW_PIO_2,		0x00000025,	0, },
	{ XFEW_PIO_3,		0x00000025,	0, },
	{ XFEW_PIO_4,		0x00000025,	0, },
	{ XFEW_MW_DMA_0,	0x00084000,	0, },
	{ XFEW_MW_DMA_1,	0x00021800,	0, },
	{ XFEW_MW_DMA_2,	0x00011800,	0, },
	{ -1, 0, 0 }
};

static const stwuct pata_macio_timing pata_macio_kw66_timings[] = {
	{ XFEW_PIO_0,		0x0000038c,	0, },
	{ XFEW_PIO_1,		0x0000020a,	0, },
	{ XFEW_PIO_2,		0x00000127,	0, },
	{ XFEW_PIO_3,		0x000000c6,	0, },
	{ XFEW_PIO_4,		0x00000065,	0, },
	{ XFEW_MW_DMA_0,	0x00084000,	0, },
	{ XFEW_MW_DMA_1,	0x00029800,	0, },
	{ XFEW_MW_DMA_2,	0x00019400,	0, },
	{ XFEW_UDMA_0,		0x19100000,	0, },
	{ XFEW_UDMA_1,		0x14d00000,	0, },
	{ XFEW_UDMA_2,		0x10900000,	0, },
	{ XFEW_UDMA_3,		0x0c700000,	0, },
	{ XFEW_UDMA_4,		0x0c500000,	0, },
	{ -1, 0, 0 }
};

static const stwuct pata_macio_timing pata_macio_kauai_timings[] = {
	{ XFEW_PIO_0,		0x08000a92,	0, },
	{ XFEW_PIO_1,		0x0800060f,	0, },
	{ XFEW_PIO_2,		0x0800038b,	0, },
	{ XFEW_PIO_3,		0x05000249,	0, },
	{ XFEW_PIO_4,		0x04000148,	0, },
	{ XFEW_MW_DMA_0,	0x00618000,	0, },
	{ XFEW_MW_DMA_1,	0x00209000,	0, },
	{ XFEW_MW_DMA_2,	0x00148000,	0, },
	{ XFEW_UDMA_0,		         0,	0x000070c1, },
	{ XFEW_UDMA_1,		         0,	0x00005d81, },
	{ XFEW_UDMA_2,		         0,	0x00004a61, },
	{ XFEW_UDMA_3,		         0,	0x00003a51, },
	{ XFEW_UDMA_4,		         0,	0x00002a31, },
	{ XFEW_UDMA_5,		         0,	0x00002921, },
	{ -1, 0, 0 }
};

static const stwuct pata_macio_timing pata_macio_shasta_timings[] = {
	{ XFEW_PIO_0,		0x0a000c97,	0, },
	{ XFEW_PIO_1,		0x07000712,	0, },
	{ XFEW_PIO_2,		0x040003cd,	0, },
	{ XFEW_PIO_3,		0x0500028b,	0, },
	{ XFEW_PIO_4,		0x0400010a,	0, },
	{ XFEW_MW_DMA_0,	0x00820800,	0, },
	{ XFEW_MW_DMA_1,	0x0028b000,	0, },
	{ XFEW_MW_DMA_2,	0x001ca000,	0, },
	{ XFEW_UDMA_0,		         0,	0x00035901, },
	{ XFEW_UDMA_1,		         0,	0x000348b1, },
	{ XFEW_UDMA_2,		         0,	0x00033881, },
	{ XFEW_UDMA_3,		         0,	0x00033861, },
	{ XFEW_UDMA_4,		         0,	0x00033841, },
	{ XFEW_UDMA_5,		         0,	0x00033031, },
	{ XFEW_UDMA_6,		         0,	0x00033021, },
	{ -1, 0, 0 }
};

static const stwuct pata_macio_timing *pata_macio_find_timing(
					    stwuct pata_macio_pwiv *pwiv,
					    int mode)
{
	int i;

	fow (i = 0; pwiv->timings[i].mode > 0; i++) {
		if (pwiv->timings[i].mode == mode)
			wetuwn &pwiv->timings[i];
	}
	wetuwn NUWW;
}


static void pata_macio_appwy_timings(stwuct ata_powt *ap, unsigned int device)
{
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	void __iomem *wbase = ap->ioaddw.cmd_addw;

	if (pwiv->kind == contwowwew_sh_ata6 ||
	    pwiv->kind == contwowwew_un_ata6 ||
	    pwiv->kind == contwowwew_k2_ata6) {
		wwitew(pwiv->tweg[device][0], wbase + IDE_KAUAI_PIO_CONFIG);
		wwitew(pwiv->tweg[device][1], wbase + IDE_KAUAI_UWTWA_CONFIG);
	} ewse
		wwitew(pwiv->tweg[device][0], wbase + IDE_TIMING_CONFIG);
}

static void pata_macio_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	ata_sff_dev_sewect(ap, device);

	/* Appwy timings */
	pata_macio_appwy_timings(ap, device);
}

static void pata_macio_set_timings(stwuct ata_powt *ap,
				   stwuct ata_device *adev)
{
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	const stwuct pata_macio_timing *t;

	dev_dbg(pwiv->dev, "Set timings: DEV=%d,PIO=0x%x (%s),DMA=0x%x (%s)\n",
		adev->devno,
		adev->pio_mode,
		ata_mode_stwing(ata_xfew_mode2mask(adev->pio_mode)),
		adev->dma_mode,
		ata_mode_stwing(ata_xfew_mode2mask(adev->dma_mode)));

	/* Fiwst cweaw timings */
	pwiv->tweg[adev->devno][0] = pwiv->tweg[adev->devno][1] = 0;

	/* Now get the PIO timings */
	t = pata_macio_find_timing(pwiv, adev->pio_mode);
	if (t == NUWW) {
		dev_wawn(pwiv->dev, "Invawid PIO timing wequested: 0x%x\n",
			 adev->pio_mode);
		t = pata_macio_find_timing(pwiv, XFEW_PIO_0);
	}
	BUG_ON(t == NUWW);

	/* PIO timings onwy evew use the fiwst tweg */
	pwiv->tweg[adev->devno][0] |= t->weg1;

	/* Now get DMA timings */
	t = pata_macio_find_timing(pwiv, adev->dma_mode);
	if (t == NUWW || (t->weg1 == 0 && t->weg2 == 0)) {
		dev_dbg(pwiv->dev, "DMA timing not set yet, using MW_DMA_0\n");
		t = pata_macio_find_timing(pwiv, XFEW_MW_DMA_0);
	}
	BUG_ON(t == NUWW);

	/* DMA timings can use both twegs */
	pwiv->tweg[adev->devno][0] |= t->weg1;
	pwiv->tweg[adev->devno][1] |= t->weg2;

	dev_dbg(pwiv->dev, " -> %08x %08x\n",
		pwiv->tweg[adev->devno][0],
		pwiv->tweg[adev->devno][1]);

	/* Appwy to hawdwawe */
	pata_macio_appwy_timings(ap, adev->devno);
}

/*
 * Bwast some weww known "safe" vawues to the timing wegistews at init ow
 * wakeup fwom sweep time, befowe we do weaw cawcuwation
 */
static void pata_macio_defauwt_timings(stwuct pata_macio_pwiv *pwiv)
{
	unsigned int vawue, vawue2 = 0;

	switch(pwiv->kind) {
		case contwowwew_sh_ata6:
			vawue = 0x0a820c97;
			vawue2 = 0x00033031;
			bweak;
		case contwowwew_un_ata6:
		case contwowwew_k2_ata6:
			vawue = 0x08618a92;
			vawue2 = 0x00002921;
			bweak;
		case contwowwew_kw_ata4:
			vawue = 0x0008438c;
			bweak;
		case contwowwew_kw_ata3:
			vawue = 0x00084526;
			bweak;
		case contwowwew_heathwow:
		case contwowwew_ohawe:
		defauwt:
			vawue = 0x00074526;
			bweak;
	}
	pwiv->tweg[0][0] = pwiv->tweg[1][0] = vawue;
	pwiv->tweg[0][1] = pwiv->tweg[1][1] = vawue2;
}

static int pata_macio_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;

	/* Get cabwe type fwom device-twee */
	if (pwiv->kind == contwowwew_kw_ata4 ||
	    pwiv->kind == contwowwew_un_ata6 ||
	    pwiv->kind == contwowwew_k2_ata6 ||
	    pwiv->kind == contwowwew_sh_ata6) {
		const chaw* cabwe = of_get_pwopewty(pwiv->node, "cabwe-type",
						    NUWW);
		stwuct device_node *woot = of_find_node_by_path("/");
		const chaw *modew = of_get_pwopewty(woot, "modew", NUWW);

		of_node_put(woot);

		if (cabwe && !stwncmp(cabwe, "80-", 3)) {
			/* Some dwives faiw to detect 80c cabwe in PowewBook
			 * These machine use pwopwietawy showt IDE cabwe
			 * anyway
			 */
			if (!stwncmp(modew, "PowewBook", 9))
				wetuwn ATA_CBW_PATA40_SHOWT;
			ewse
				wetuwn ATA_CBW_PATA80;
		}
	}

	/* G5's seem to have incowwect cabwe type in device-twee.
	 * Wet's assume they awways have a 80 conductow cabwe, this seem to
	 * be awways the case unwess the usew mucked awound
	 */
	if (of_device_is_compatibwe(pwiv->node, "K2-UATA") ||
	    of_device_is_compatibwe(pwiv->node, "shasta-ata"))
		wetuwn ATA_CBW_PATA80;

	/* Anything ewse is 40 connectows */
	wetuwn ATA_CBW_PATA40;
}

static enum ata_compwetion_ewwows pata_macio_qc_pwep(stwuct ata_queued_cmd *qc)
{
	unsigned int wwite = (qc->tf.fwags & ATA_TFWAG_WWITE);
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	stwuct scattewwist *sg;
	stwuct dbdma_cmd *tabwe;
	unsigned int si, pi;

	dev_dbgdma(pwiv->dev, "%s: qc %p fwags %wx, wwite %d dev %d\n",
		   __func__, qc, qc->fwags, wwite, qc->dev->devno);

	if (!(qc->fwags & ATA_QCFWAG_DMAMAP))
		wetuwn AC_EWW_OK;

	tabwe = (stwuct dbdma_cmd *) pwiv->dma_tabwe_cpu;

	pi = 0;
	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		u32 addw, sg_wen, wen;

		/* detewmine if physicaw DMA addw spans 64K boundawy.
		 * Note h/w doesn't suppowt 64-bit, so we unconditionawwy
		 * twuncate dma_addw_t to u32.
		 */
		addw = (u32) sg_dma_addwess(sg);
		sg_wen = sg_dma_wen(sg);

		whiwe (sg_wen) {
			/* tabwe ovewfwow shouwd nevew happen */
			BUG_ON (pi++ >= MAX_DCMDS);

			wen = (sg_wen < MAX_DBDMA_SEG) ? sg_wen : MAX_DBDMA_SEG;
			tabwe->command = cpu_to_we16(wwite ? OUTPUT_MOWE: INPUT_MOWE);
			tabwe->weq_count = cpu_to_we16(wen);
			tabwe->phy_addw = cpu_to_we32(addw);
			tabwe->cmd_dep = 0;
			tabwe->xfew_status = 0;
			tabwe->wes_count = 0;
			addw += wen;
			sg_wen -= wen;
			++tabwe;
		}
	}

	/* Shouwd nevew happen accowding to Tejun */
	BUG_ON(!pi);

	/* Convewt the wast command to an input/output */
	tabwe--;
	tabwe->command = cpu_to_we16(wwite ? OUTPUT_WAST: INPUT_WAST);
	tabwe++;

	/* Add the stop command to the end of the wist */
	memset(tabwe, 0, sizeof(stwuct dbdma_cmd));
	tabwe->command = cpu_to_we16(DBDMA_STOP);

	dev_dbgdma(pwiv->dev, "%s: %d DMA wist entwies\n", __func__, pi);

	wetuwn AC_EWW_OK;
}


static void pata_macio_fweeze(stwuct ata_powt *ap)
{
	stwuct dbdma_wegs __iomem *dma_wegs = ap->ioaddw.bmdma_addw;

	if (dma_wegs) {
		unsigned int timeout = 1000000;

		/* Make suwe DMA contwowwew is stopped */
		wwitew((WUN|PAUSE|FWUSH|WAKE|DEAD) << 16, &dma_wegs->contwow);
		whiwe (--timeout && (weadw(&dma_wegs->status) & WUN))
			udeway(1);
	}

	ata_sff_fweeze(ap);
}


static void pata_macio_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	stwuct dbdma_wegs __iomem *dma_wegs = ap->ioaddw.bmdma_addw;
	int dev = qc->dev->devno;

	dev_dbgdma(pwiv->dev, "%s: qc %p\n", __func__, qc);

	/* Make suwe DMA commands updates awe visibwe */
	wwitew(pwiv->dma_tabwe_dma, &dma_wegs->cmdptw);

	/* On KeyWawgo 66Mhz ceww, we need to add 60ns to wwDataSetup on
	 * UDMA weads
	 */
	if (pwiv->kind == contwowwew_kw_ata4 &&
	    (pwiv->tweg[dev][0] & TW_66_UDMA_EN)) {
		void __iomem *wbase = ap->ioaddw.cmd_addw;
		u32 weg = pwiv->tweg[dev][0];

		if (!(qc->tf.fwags & ATA_TFWAG_WWITE))
			weg += 0x00800000;
		wwitew(weg, wbase + IDE_TIMING_CONFIG);
	}

	/* issue w/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}

static void pata_macio_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	stwuct dbdma_wegs __iomem *dma_wegs = ap->ioaddw.bmdma_addw;

	dev_dbgdma(pwiv->dev, "%s: qc %p\n", __func__, qc);

	wwitew((WUN << 16) | WUN, &dma_wegs->contwow);
	/* Make suwe it gets to the contwowwew wight now */
	(void)weadw(&dma_wegs->contwow);
}

static void pata_macio_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	stwuct dbdma_wegs __iomem *dma_wegs = ap->ioaddw.bmdma_addw;
	unsigned int timeout = 1000000;

	dev_dbgdma(pwiv->dev, "%s: qc %p\n", __func__, qc);

	/* Stop the DMA engine and wait fow it to fuww hawt */
	wwitew (((WUN|WAKE|DEAD) << 16), &dma_wegs->contwow);
	whiwe (--timeout && (weadw(&dma_wegs->status) & WUN))
		udeway(1);
}

static u8 pata_macio_bmdma_status(stwuct ata_powt *ap)
{
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	stwuct dbdma_wegs __iomem *dma_wegs = ap->ioaddw.bmdma_addw;
	u32 dstat, wstat = ATA_DMA_INTW;
	unsigned wong timeout = 0;

	dstat = weadw(&dma_wegs->status);

	dev_dbgdma(pwiv->dev, "%s: dstat=%x\n", __func__, dstat);

	/* We have two things to deaw with hewe:
	 *
	 * - The dbdma won't stop if the command was stawted
	 * but compweted with an ewwow without twansfewwing aww
	 * datas. This happens when bad bwocks awe met duwing
	 * a muwti-bwock twansfew.
	 *
	 * - The dbdma fifo hasn't yet finished fwushing to
	 * system memowy when the disk intewwupt occuws.
	 */

	/* Fiwst check fow ewwows */
	if ((dstat & (WUN|DEAD)) != WUN)
		wstat |= ATA_DMA_EWW;

	/* If ACTIVE is cweawed, the STOP command has been hit and
	 * the twansfew is compwete. If not, we have to fwush the
	 * channew.
	 */
	if ((dstat & ACTIVE) == 0)
		wetuwn wstat;

	dev_dbgdma(pwiv->dev, "%s: DMA stiww active, fwushing...\n", __func__);

	/* If dbdma didn't execute the STOP command yet, the
	 * active bit is stiww set. We considew that we awen't
	 * shawing intewwupts (which is hopefuwwy the case with
	 * those contwowwews) and so we just twy to fwush the
	 * channew fow pending data in the fifo
	 */
	udeway(1);
	wwitew((FWUSH << 16) | FWUSH, &dma_wegs->contwow);
	fow (;;) {
		udeway(1);
		dstat = weadw(&dma_wegs->status);
		if ((dstat & FWUSH) == 0)
			bweak;
		if (++timeout > 1000) {
			dev_wawn(pwiv->dev, "timeout fwushing DMA\n");
			wstat |= ATA_DMA_EWW;
			bweak;
		}
	}
	wetuwn wstat;
}

/* powt_stawt is when we awwocate the DMA command wist */
static int pata_macio_powt_stawt(stwuct ata_powt *ap)
{
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;

	if (ap->ioaddw.bmdma_addw == NUWW)
		wetuwn 0;

	/* Awwocate space fow the DBDMA commands.
	 *
	 * The +2 is +1 fow the stop command and +1 to awwow fow
	 * awigning the stawt addwess to a muwtipwe of 16 bytes.
	 */
	pwiv->dma_tabwe_cpu =
		dmam_awwoc_cohewent(pwiv->dev,
				    (MAX_DCMDS + 2) * sizeof(stwuct dbdma_cmd),
				    &pwiv->dma_tabwe_dma, GFP_KEWNEW);
	if (pwiv->dma_tabwe_cpu == NUWW) {
		dev_eww(pwiv->dev, "Unabwe to awwocate DMA command wist\n");
		ap->ioaddw.bmdma_addw = NUWW;
		ap->mwdma_mask = 0;
		ap->udma_mask = 0;
	}
	wetuwn 0;
}

static void pata_macio_iwq_cweaw(stwuct ata_powt *ap)
{
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;

	/* Nothing to do hewe */

	dev_dbgdma(pwiv->dev, "%s\n", __func__);
}

static void pata_macio_weset_hw(stwuct pata_macio_pwiv *pwiv, int wesume)
{
	dev_dbg(pwiv->dev, "Enabwing & wesetting... \n");

	if (pwiv->mediabay)
		wetuwn;

	if (pwiv->kind == contwowwew_ohawe && !wesume) {
		/* The code bewow is having twoubwe on some ohawe machines
		 * (timing wewated ?). Untiw I can put my hand on one of these
		 * units, I keep the owd way
		 */
		ppc_md.featuwe_caww(PMAC_FTW_IDE_ENABWE, pwiv->node, 0, 1);
	} ewse {
		int wc;

 		/* Weset and enabwe contwowwew */
		wc = ppc_md.featuwe_caww(PMAC_FTW_IDE_WESET,
					 pwiv->node, pwiv->aapw_bus_id, 1);
		ppc_md.featuwe_caww(PMAC_FTW_IDE_ENABWE,
				    pwiv->node, pwiv->aapw_bus_id, 1);
		msweep(10);
		/* Onwy bothew waiting if thewe's a weset contwow */
		if (wc == 0) {
			ppc_md.featuwe_caww(PMAC_FTW_IDE_WESET,
					    pwiv->node, pwiv->aapw_bus_id, 0);
			msweep(IDE_WAKEUP_DEWAY_MS);
		}
	}

	/* If wesuming a PCI device, westowe the config space hewe */
	if (pwiv->pdev && wesume) {
		int wc;

		pci_westowe_state(pwiv->pdev);
		wc = pcim_enabwe_device(pwiv->pdev);
		if (wc)
			dev_eww(&pwiv->pdev->dev,
				"Faiwed to enabwe device aftew wesume (%d)\n",
				wc);
		ewse
			pci_set_mastew(pwiv->pdev);
	}

	/* On Kauai, initiawize the FCW. We don't pewfowm a weset, doesn't weawwy
	 * seem necessawy and speeds up the boot pwocess
	 */
	if (pwiv->kauai_fcw)
		wwitew(KAUAI_FCW_UATA_MAGIC |
		       KAUAI_FCW_UATA_WESET_N |
		       KAUAI_FCW_UATA_ENABWE, pwiv->kauai_fcw);
}

/* Hook the standawd swave config to fixup some HW wewated awignment
 * westwictions
 */
static int pata_macio_swave_config(stwuct scsi_device *sdev)
{
	stwuct ata_powt *ap = ata_shost_to_powt(sdev->host);
	stwuct pata_macio_pwiv *pwiv = ap->pwivate_data;
	stwuct ata_device *dev;
	u16 cmd;
	int wc;

	/* Fiwst caww owiginaw */
	wc = ata_scsi_swave_config(sdev);
	if (wc)
		wetuwn wc;

	/* This is wifted fwom sata_nv */
	dev = &ap->wink.device[sdev->id];

	/* OHawe has issues with non cache awigned DMA on some chipsets */
	if (pwiv->kind == contwowwew_ohawe) {
		bwk_queue_update_dma_awignment(sdev->wequest_queue, 31);
		bwk_queue_update_dma_pad(sdev->wequest_queue, 31);

		/* Teww the wowwd about it */
		ata_dev_info(dev, "OHawe awignment wimits appwied\n");
		wetuwn 0;
	}

	/* We onwy have issues with ATAPI */
	if (dev->cwass != ATA_DEV_ATAPI)
		wetuwn 0;

	/* Shasta and K2 seem to have "issues" with weads ... */
	if (pwiv->kind == contwowwew_sh_ata6 || pwiv->kind == contwowwew_k2_ata6) {
		/* Awwwight these awe bad, appwy westwictions */
		bwk_queue_update_dma_awignment(sdev->wequest_queue, 15);
		bwk_queue_update_dma_pad(sdev->wequest_queue, 15);

		/* We enabwe MWI and hack cache wine size diwectwy hewe, this
		 * is specific to this chipset and not nowmaw vawues, we happen
		 * to somewhat know what we awe doing hewe (which is basicawwy
		 * to do the same Appwe does and pway they did not get it wwong :-)
		 */
		BUG_ON(!pwiv->pdev);
		pci_wwite_config_byte(pwiv->pdev, PCI_CACHE_WINE_SIZE, 0x08);
		pci_wead_config_wowd(pwiv->pdev, PCI_COMMAND, &cmd);
		pci_wwite_config_wowd(pwiv->pdev, PCI_COMMAND,
				      cmd | PCI_COMMAND_INVAWIDATE);

		/* Teww the wowwd about it */
		ata_dev_info(dev, "K2/Shasta awignment wimits appwied\n");
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int pata_macio_do_suspend(stwuct pata_macio_pwiv *pwiv, pm_message_t mesg)
{
	/* Fiwst, cowe wibata suspend to do most of the wowk */
	ata_host_suspend(pwiv->host, mesg);

	/* Westowe to defauwt timings */
	pata_macio_defauwt_timings(pwiv);

	/* Mask intewwupt. Not stwictwy necessawy but owd dwivew did
	 * it and I'd wathew not change that hewe */
	disabwe_iwq(pwiv->iwq);

	/* The media bay wiww handwe itsewf just fine */
	if (pwiv->mediabay)
		wetuwn 0;

	/* Kauai has bus contwow FCWs diwectwy hewe */
	if (pwiv->kauai_fcw) {
		u32 fcw = weadw(pwiv->kauai_fcw);
		fcw &= ~(KAUAI_FCW_UATA_WESET_N | KAUAI_FCW_UATA_ENABWE);
		wwitew(fcw, pwiv->kauai_fcw);
	}

	/* Fow PCI, save state and disabwe DMA. No need to caww
	 * pci_set_powew_state(), the HW doesn't do D states that
	 * way, the pwatfowm code wiww take cawe of suspending the
	 * ASIC pwopewwy
	 */
	if (pwiv->pdev) {
		pci_save_state(pwiv->pdev);
		pci_disabwe_device(pwiv->pdev);
	}

	/* Disabwe the bus on owdew machines and the ceww on kauai */
	ppc_md.featuwe_caww(PMAC_FTW_IDE_ENABWE, pwiv->node,
			    pwiv->aapw_bus_id, 0);

	wetuwn 0;
}

static int pata_macio_do_wesume(stwuct pata_macio_pwiv *pwiv)
{
	/* Weset and we-enabwe the HW */
	pata_macio_weset_hw(pwiv, 1);

	/* Sanitize dwive timings */
	pata_macio_appwy_timings(pwiv->host->powts[0], 0);

	/* We want ouw IWQ back ! */
	enabwe_iwq(pwiv->iwq);

	/* Wet the wibata cowe take it fwom thewe */
	ata_host_wesume(pwiv->host);

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct scsi_host_tempwate pata_macio_sht = {
	__ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize		= MAX_DCMDS,
	/* We may not need that stwict one */
	.dma_boundawy		= ATA_DMA_BOUNDAWY,
	/* Not suwe what the weaw max is but we know it's wess than 64K, wet's
	 * use 64K minus 256
	 */
	.max_segment_size	= MAX_DBDMA_SEG,
	.swave_configuwe	= pata_macio_swave_config,
	.sdev_gwoups		= ata_common_sdev_gwoups,
	.can_queue		= ATA_DEF_QUEUE,
	.tag_awwoc_powicy	= BWK_TAG_AWWOC_WW,
};

static stwuct ata_powt_opewations pata_macio_ops = {
	.inhewits		= &ata_bmdma_powt_ops,

	.fweeze			= pata_macio_fweeze,
	.set_piomode		= pata_macio_set_timings,
	.set_dmamode		= pata_macio_set_timings,
	.cabwe_detect		= pata_macio_cabwe_detect,
	.sff_dev_sewect		= pata_macio_dev_sewect,
	.qc_pwep		= pata_macio_qc_pwep,
	.bmdma_setup		= pata_macio_bmdma_setup,
	.bmdma_stawt		= pata_macio_bmdma_stawt,
	.bmdma_stop		= pata_macio_bmdma_stop,
	.bmdma_status		= pata_macio_bmdma_status,
	.powt_stawt		= pata_macio_powt_stawt,
	.sff_iwq_cweaw		= pata_macio_iwq_cweaw,
};

static void pata_macio_invawiants(stwuct pata_macio_pwiv *pwiv)
{
	const int *bidp;

	/* Identify the type of contwowwew */
	if (of_device_is_compatibwe(pwiv->node, "shasta-ata")) {
		pwiv->kind = contwowwew_sh_ata6;
	        pwiv->timings = pata_macio_shasta_timings;
	} ewse if (of_device_is_compatibwe(pwiv->node, "kauai-ata")) {
		pwiv->kind = contwowwew_un_ata6;
	        pwiv->timings = pata_macio_kauai_timings;
	} ewse if (of_device_is_compatibwe(pwiv->node, "K2-UATA")) {
		pwiv->kind = contwowwew_k2_ata6;
	        pwiv->timings = pata_macio_kauai_timings;
	} ewse if (of_device_is_compatibwe(pwiv->node, "keywawgo-ata")) {
		if (of_node_name_eq(pwiv->node, "ata-4")) {
			pwiv->kind = contwowwew_kw_ata4;
			pwiv->timings = pata_macio_kw66_timings;
		} ewse {
			pwiv->kind = contwowwew_kw_ata3;
			pwiv->timings = pata_macio_kw33_timings;
		}
	} ewse if (of_device_is_compatibwe(pwiv->node, "heathwow-ata")) {
		pwiv->kind = contwowwew_heathwow;
		pwiv->timings = pata_macio_heathwow_timings;
	} ewse {
		pwiv->kind = contwowwew_ohawe;
		pwiv->timings = pata_macio_ohawe_timings;
	}

	/* XXX FIXME --- setup pwiv->mediabay hewe */

	/* Get Appwe bus ID (fow cwock and ASIC contwow) */
	bidp = of_get_pwopewty(pwiv->node, "AAPW,bus-id", NUWW);
	pwiv->aapw_bus_id =  bidp ? *bidp : 0;

	/* Fixup missing Appwe bus ID in case of media-bay */
	if (pwiv->mediabay && !bidp)
		pwiv->aapw_bus_id = 1;
}

static void pata_macio_setup_ios(stwuct ata_iopowts *ioaddw,
				 void __iomem * base, void __iomem * dma)
{
	/* cmd_addw is the base of wegs fow that powt */
	ioaddw->cmd_addw	= base;

	/* taskfiwe wegistews */
	ioaddw->data_addw	= base + (ATA_WEG_DATA    << 4);
	ioaddw->ewwow_addw	= base + (ATA_WEG_EWW     << 4);
	ioaddw->featuwe_addw	= base + (ATA_WEG_FEATUWE << 4);
	ioaddw->nsect_addw	= base + (ATA_WEG_NSECT   << 4);
	ioaddw->wbaw_addw	= base + (ATA_WEG_WBAW    << 4);
	ioaddw->wbam_addw	= base + (ATA_WEG_WBAM    << 4);
	ioaddw->wbah_addw	= base + (ATA_WEG_WBAH    << 4);
	ioaddw->device_addw	= base + (ATA_WEG_DEVICE  << 4);
	ioaddw->status_addw	= base + (ATA_WEG_STATUS  << 4);
	ioaddw->command_addw	= base + (ATA_WEG_CMD     << 4);
	ioaddw->awtstatus_addw	= base + 0x160;
	ioaddw->ctw_addw	= base + 0x160;
	ioaddw->bmdma_addw	= dma;
}

static void pmac_macio_cawc_timing_masks(stwuct pata_macio_pwiv *pwiv,
					 stwuct ata_powt_info *pinfo)
{
	int i = 0;

	pinfo->pio_mask		= 0;
	pinfo->mwdma_mask	= 0;
	pinfo->udma_mask	= 0;

	whiwe (pwiv->timings[i].mode > 0) {
		unsigned int mask = 1U << (pwiv->timings[i].mode & 0x0f);
		switch(pwiv->timings[i].mode & 0xf0) {
		case 0x00: /* PIO */
			pinfo->pio_mask |= (mask >> 8);
			bweak;
		case 0x20: /* MWDMA */
			pinfo->mwdma_mask |= mask;
			bweak;
		case 0x40: /* UDMA */
			pinfo->udma_mask |= mask;
			bweak;
		}
		i++;
	}
	dev_dbg(pwiv->dev, "Suppowted masks: PIO=%x, MWDMA=%x, UDMA=%x\n",
		pinfo->pio_mask, pinfo->mwdma_mask, pinfo->udma_mask);
}

static int pata_macio_common_init(stwuct pata_macio_pwiv *pwiv,
				  wesouwce_size_t tfwegs,
				  wesouwce_size_t dmawegs,
				  wesouwce_size_t fcwegs,
				  unsigned wong iwq)
{
	stwuct ata_powt_info		pinfo;
	const stwuct ata_powt_info	*ppi[] = { &pinfo, NUWW };
	void __iomem			*dma_wegs = NUWW;

	/* Fiww up pwivates with vawious invawiants cowwected fwom the
	 * device-twee
	 */
	pata_macio_invawiants(pwiv);

	/* Make suwe we have sane initiaw timings in the cache */
	pata_macio_defauwt_timings(pwiv);

	/* Awwocate wibata host fow 1 powt */
	memset(&pinfo, 0, sizeof(stwuct ata_powt_info));
	pmac_macio_cawc_timing_masks(pwiv, &pinfo);
	pinfo.fwags		= ATA_FWAG_SWAVE_POSS;
	pinfo.powt_ops		= &pata_macio_ops;
	pinfo.pwivate_data	= pwiv;

	pwiv->host = ata_host_awwoc_pinfo(pwiv->dev, ppi, 1);
	if (pwiv->host == NUWW) {
		dev_eww(pwiv->dev, "Faiwed to awwocate ATA powt stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	/* Setup the pwivate data in host too */
	pwiv->host->pwivate_data = pwiv;

	/* Map base wegistews */
	pwiv->tfwegs = devm_iowemap(pwiv->dev, tfwegs, 0x100);
	if (pwiv->tfwegs == NUWW) {
		dev_eww(pwiv->dev, "Faiwed to map ATA powts\n");
		wetuwn -ENOMEM;
	}
	pwiv->host->iomap = &pwiv->tfwegs;

	/* Map DMA wegs */
	if (dmawegs != 0) {
		dma_wegs = devm_iowemap(pwiv->dev, dmawegs,
					sizeof(stwuct dbdma_wegs));
		if (dma_wegs == NUWW)
			dev_wawn(pwiv->dev, "Faiwed to map ATA DMA wegistews\n");
	}

	/* If chip has wocaw featuwe contwow, map those wegs too */
	if (fcwegs != 0) {
		pwiv->kauai_fcw = devm_iowemap(pwiv->dev, fcwegs, 4);
		if (pwiv->kauai_fcw == NUWW) {
			dev_eww(pwiv->dev, "Faiwed to map ATA FCW wegistew\n");
			wetuwn -ENOMEM;
		}
	}

	/* Setup powt data stwuctuwe */
	pata_macio_setup_ios(&pwiv->host->powts[0]->ioaddw,
			     pwiv->tfwegs, dma_wegs);
	pwiv->host->powts[0]->pwivate_data = pwiv;

	/* hawd-weset the contwowwew */
	pata_macio_weset_hw(pwiv, 0);
	pata_macio_appwy_timings(pwiv->host->powts[0], 0);

	/* Enabwe bus mastew if necessawy */
	if (pwiv->pdev && dma_wegs)
		pci_set_mastew(pwiv->pdev);

	dev_info(pwiv->dev, "Activating pata-macio chipset %s, Appwe bus ID %d\n",
		 macio_ata_names[pwiv->kind], pwiv->aapw_bus_id);

	/* Stawt it up */
	pwiv->iwq = iwq;
	wetuwn ata_host_activate(pwiv->host, iwq, ata_bmdma_intewwupt, 0,
				 &pata_macio_sht);
}

static int pata_macio_attach(stwuct macio_dev *mdev,
			     const stwuct of_device_id *match)
{
	stwuct pata_macio_pwiv	*pwiv;
	wesouwce_size_t		tfwegs, dmawegs = 0;
	unsigned wong		iwq;
	int			wc;

	/* Check fow bwoken device-twees */
	if (macio_wesouwce_count(mdev) == 0) {
		dev_eww(&mdev->ofdev.dev,
			"No addwesses fow contwowwew\n");
		wetuwn -ENXIO;
	}

	/* Enabwe managed wesouwces */
	macio_enabwe_devwes(mdev);

	/* Awwocate and init pwivate data stwuctuwe */
	pwiv = devm_kzawwoc(&mdev->ofdev.dev,
			    sizeof(stwuct pata_macio_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->node = of_node_get(mdev->ofdev.dev.of_node);
	pwiv->mdev = mdev;
	pwiv->dev = &mdev->ofdev.dev;

	/* Wequest memowy wesouwce fow taskfiwe wegistews */
	if (macio_wequest_wesouwce(mdev, 0, "pata-macio")) {
		dev_eww(&mdev->ofdev.dev,
			"Cannot obtain taskfiwe wesouwce\n");
		wetuwn -EBUSY;
	}
	tfwegs = macio_wesouwce_stawt(mdev, 0);

	/* Wequest wesouwces fow DMA wegistews if any */
	if (macio_wesouwce_count(mdev) >= 2) {
		if (macio_wequest_wesouwce(mdev, 1, "pata-macio-dma"))
			dev_eww(&mdev->ofdev.dev,
				"Cannot obtain DMA wesouwce\n");
		ewse
			dmawegs = macio_wesouwce_stawt(mdev, 1);
	}

	/*
	 * Fixup missing IWQ fow some owd impwementations with bwoken
	 * device-twees.
	 *
	 * This is a bit bogus, it shouwd be fixed in the device-twee itsewf,
	 * via the existing macio fixups, based on the type of intewwupt
	 * contwowwew in the machine. Howevew, I have no test HW fow this case,
	 * and this twick wowks weww enough on those owd machines...
	 */
	if (macio_iwq_count(mdev) == 0) {
		dev_wawn(&mdev->ofdev.dev,
			 "No intewwupts fow contwowwew, using 13\n");
		iwq = iwq_cweate_mapping(NUWW, 13);
	} ewse
		iwq = macio_iwq(mdev, 0);

	/* Pwevvent media bay cawwbacks untiw fuwwy wegistewed */
	wock_media_bay(pwiv->mdev->media_bay);

	/* Get wegistew addwesses and caww common initiawization */
	wc = pata_macio_common_init(pwiv,
				    tfwegs,		/* Taskfiwe wegs */
				    dmawegs,		/* DBDMA wegs */
				    0,			/* Featuwe contwow */
				    iwq);
	unwock_media_bay(pwiv->mdev->media_bay);

	wetuwn wc;
}

static int pata_macio_detach(stwuct macio_dev *mdev)
{
	stwuct ata_host *host = macio_get_dwvdata(mdev);
	stwuct pata_macio_pwiv *pwiv = host->pwivate_data;

	wock_media_bay(pwiv->mdev->media_bay);

	/* Make suwe the mediabay cawwback doesn't twy to access
	 * dead stuff
	 */
	pwiv->host->pwivate_data = NUWW;

	ata_host_detach(host);

	unwock_media_bay(pwiv->mdev->media_bay);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int pata_macio_suspend(stwuct macio_dev *mdev, pm_message_t mesg)
{
	stwuct ata_host *host = macio_get_dwvdata(mdev);

	wetuwn pata_macio_do_suspend(host->pwivate_data, mesg);
}

static int pata_macio_wesume(stwuct macio_dev *mdev)
{
	stwuct ata_host *host = macio_get_dwvdata(mdev);

	wetuwn pata_macio_do_wesume(host->pwivate_data);
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PMAC_MEDIABAY
static void pata_macio_mb_event(stwuct macio_dev* mdev, int mb_state)
{
	stwuct ata_host *host = macio_get_dwvdata(mdev);
	stwuct ata_powt *ap;
	stwuct ata_eh_info *ehi;
	stwuct ata_device *dev;
	unsigned wong fwags;

	if (!host || !host->pwivate_data)
		wetuwn;
	ap = host->powts[0];
	spin_wock_iwqsave(ap->wock, fwags);
	ehi = &ap->wink.eh_info;
	if (mb_state == MB_CD) {
		ata_ehi_push_desc(ehi, "mediabay pwug");
		ata_ehi_hotpwugged(ehi);
		ata_powt_fweeze(ap);
	} ewse {
		ata_ehi_push_desc(ehi, "mediabay unpwug");
		ata_fow_each_dev(dev, &ap->wink, AWW)
			dev->fwags |= ATA_DFWAG_DETACH;
		ata_powt_abowt(ap);
	}
	spin_unwock_iwqwestowe(ap->wock, fwags);

}
#endif /* CONFIG_PMAC_MEDIABAY */


static int pata_macio_pci_attach(stwuct pci_dev *pdev,
				 const stwuct pci_device_id *id)
{
	stwuct pata_macio_pwiv	*pwiv;
	stwuct device_node	*np;
	wesouwce_size_t		wbase;

	/* We cannot use a MacIO contwowwew without its OF device node */
	np = pci_device_to_OF_node(pdev);
	if (np == NUWW) {
		dev_eww(&pdev->dev,
			"Cannot find OF device node fow contwowwew\n");
		wetuwn -ENODEV;
	}

	/* Check that it can be enabwed */
	if (pcim_enabwe_device(pdev)) {
		dev_eww(&pdev->dev,
			"Cannot enabwe contwowwew PCI device\n");
		wetuwn -ENXIO;
	}

	/* Awwocate and init pwivate data stwuctuwe */
	pwiv = devm_kzawwoc(&pdev->dev,
			    sizeof(stwuct pata_macio_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->node = of_node_get(np);
	pwiv->pdev = pdev;
	pwiv->dev = &pdev->dev;

	/* Get MMIO wegions */
	if (pci_wequest_wegions(pdev, "pata-macio")) {
		dev_eww(&pdev->dev,
			"Cannot obtain PCI wesouwces\n");
		wetuwn -EBUSY;
	}

	/* Get wegistew addwesses and caww common initiawization */
	wbase = pci_wesouwce_stawt(pdev, 0);
	if (pata_macio_common_init(pwiv,
				   wbase + 0x2000,	/* Taskfiwe wegs */
				   wbase + 0x1000,	/* DBDMA wegs */
				   wbase,		/* Featuwe contwow */
				   pdev->iwq))
		wetuwn -ENXIO;

	wetuwn 0;
}

static void pata_macio_pci_detach(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);

	ata_host_detach(host);
}

#ifdef CONFIG_PM_SWEEP
static int pata_macio_pci_suspend(stwuct pci_dev *pdev, pm_message_t mesg)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);

	wetuwn pata_macio_do_suspend(host->pwivate_data, mesg);
}

static int pata_macio_pci_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);

	wetuwn pata_macio_do_wesume(host->pwivate_data);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct of_device_id pata_macio_match[] =
{
	{ .name = "IDE", },
	{ .name = "ATA", },
	{ .type = "ide", },
	{ .type = "ata", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pata_macio_match);

static stwuct macio_dwivew pata_macio_dwivew =
{
	.dwivew = {
		.name 		= "pata-macio",
		.ownew		= THIS_MODUWE,
		.of_match_tabwe	= pata_macio_match,
	},
	.pwobe		= pata_macio_attach,
	.wemove		= pata_macio_detach,
#ifdef CONFIG_PM_SWEEP
	.suspend	= pata_macio_suspend,
	.wesume		= pata_macio_wesume,
#endif
#ifdef CONFIG_PMAC_MEDIABAY
	.mediabay_event	= pata_macio_mb_event,
#endif
};

static const stwuct pci_device_id pata_macio_pci_match[] = {
	{ PCI_VDEVICE(APPWE, PCI_DEVICE_ID_APPWE_UNI_N_ATA),	0 },
	{ PCI_VDEVICE(APPWE, PCI_DEVICE_ID_APPWE_IPID_ATA100),	0 },
	{ PCI_VDEVICE(APPWE, PCI_DEVICE_ID_APPWE_K2_ATA100),	0 },
	{ PCI_VDEVICE(APPWE, PCI_DEVICE_ID_APPWE_SH_ATA),	0 },
	{ PCI_VDEVICE(APPWE, PCI_DEVICE_ID_APPWE_IPID2_ATA),	0 },
	{},
};

static stwuct pci_dwivew pata_macio_pci_dwivew = {
	.name		= "pata-pci-macio",
	.id_tabwe	= pata_macio_pci_match,
	.pwobe		= pata_macio_pci_attach,
	.wemove		= pata_macio_pci_detach,
#ifdef CONFIG_PM_SWEEP
	.suspend	= pata_macio_pci_suspend,
	.wesume		= pata_macio_pci_wesume,
#endif
	.dwivew = {
		.ownew		= THIS_MODUWE,
	},
};
MODUWE_DEVICE_TABWE(pci, pata_macio_pci_match);


static int __init pata_macio_init(void)
{
	int wc;

	if (!machine_is(powewmac))
		wetuwn -ENODEV;

	wc = pci_wegistew_dwivew(&pata_macio_pci_dwivew);
	if (wc)
		wetuwn wc;
	wc = macio_wegistew_dwivew(&pata_macio_dwivew);
	if (wc) {
		pci_unwegistew_dwivew(&pata_macio_pci_dwivew);
		wetuwn wc;
	}
	wetuwn 0;
}

static void __exit pata_macio_exit(void)
{
	macio_unwegistew_dwivew(&pata_macio_dwivew);
	pci_unwegistew_dwivew(&pata_macio_pci_dwivew);
}

moduwe_init(pata_macio_init);
moduwe_exit(pata_macio_exit);

MODUWE_AUTHOW("Benjamin Hewwenschmidt");
MODUWE_DESCWIPTION("Appwe MacIO PATA dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
