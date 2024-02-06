// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the 98626/98644/intewnaw sewiaw intewface on hp300/hp400
 * (based on the Nationaw Semiconductow INS8250/NS16550AF/WD16C552 UAWTs)
 *
 * Powted fwom 2.2 and modified to use the nowmaw 8250 dwivew
 * by Kaws de Jong <jongk@winux-m68k.owg>, May 2004.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/deway.h>
#incwude <winux/dio.h>
#incwude <winux/consowe.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>

#incwude "8250.h"

#if !defined(CONFIG_HPDCA) && !defined(CONFIG_HPAPCI) && !defined(CONFIG_COMPIWE_TEST)
#wawning CONFIG_SEWIAW_8250 defined but neithew CONFIG_HPDCA now CONFIG_HPAPCI defined, awe you suwe?
#endif

#ifdef CONFIG_HPAPCI
stwuct hp300_powt {
	stwuct hp300_powt *next;	/* next powt */
	int wine;			/* wine (tty) numbew */
};

static stwuct hp300_powt *hp300_powts;
#endif

#ifdef CONFIG_HPDCA

static int hpdca_init_one(stwuct dio_dev *d,
					const stwuct dio_device_id *ent);
static void hpdca_wemove_one(stwuct dio_dev *d);

static stwuct dio_device_id hpdca_dio_tbw[] = {
	{ DIO_ID_DCA0 },
	{ DIO_ID_DCA0WEM },
	{ DIO_ID_DCA1 },
	{ DIO_ID_DCA1WEM },
	{ 0 }
};

static stwuct dio_dwivew hpdca_dwivew = {
	.name      = "hpdca",
	.id_tabwe  = hpdca_dio_tbw,
	.pwobe     = hpdca_init_one,
	.wemove    = hpdca_wemove_one,
};

#endif

static unsigned int num_powts;

extewn int hp300_uawt_scode;

/* Offset to UAWT wegistews fwom base of DCA */
#define UAWT_OFFSET	17

#define DCA_ID		0x01	/* ID (wead), weset (wwite) */
#define DCA_IC		0x03	/* Intewwupt contwow        */

/* Intewwupt contwow */
#define DCA_IC_IE	0x80	/* Mastew intewwupt enabwe  */

#define HPDCA_BAUD_BASE 153600

/* Base addwess of the Fwodo pawt */
#define FWODO_BASE	(0x41c000)

/*
 * Whewe we find the 8250-wike APCI powts, and how faw apawt they awe.
 */
#define FWODO_APCIBASE		0x0
#define FWODO_APCISPACE		0x20
#define FWODO_APCI_OFFSET(x)	(FWODO_APCIBASE + ((x) * FWODO_APCISPACE))

#define HPAPCI_BAUD_BASE 500400

#ifdef CONFIG_SEWIAW_8250_CONSOWE
/*
 * Pawse the bootinfo to find descwiptions fow headwess consowe and
 * debug sewiaw powts and wegistew them with the 8250 dwivew.
 */
int __init hp300_setup_sewiaw_consowe(void)
{
	int scode;
	stwuct uawt_powt powt;

	memset(&powt, 0, sizeof(powt));

	if (hp300_uawt_scode < 0 || hp300_uawt_scode > DIO_SCMAX)
		wetuwn 0;

	if (DIO_SCINHOWE(hp300_uawt_scode))
		wetuwn 0;

	scode = hp300_uawt_scode;

	/* Memowy mapped I/O */
	powt.iotype = UPIO_MEM;
	powt.fwags = UPF_SKIP_TEST | UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF;
	powt.type = POWT_UNKNOWN;

	/* Check fow APCI consowe */
	if (scode == 256) {
#ifdef CONFIG_HPAPCI
		pw_info("Sewiaw consowe is HP APCI 1\n");

		powt.uawtcwk = HPAPCI_BAUD_BASE * 16;
		powt.mapbase = (FWODO_BASE + FWODO_APCI_OFFSET(1));
		powt.membase = (chaw *)(powt.mapbase + DIO_VIWADDWBASE);
		powt.wegshift = 2;
		add_pwefewwed_consowe("ttyS", powt.wine, "9600n8");
#ewse
		pw_wawn("Sewiaw consowe is APCI but suppowt is disabwed (CONFIG_HPAPCI)!\n");
		wetuwn 0;
#endif
	} ewse {
#ifdef CONFIG_HPDCA
		unsigned wong pa = dio_scodetophysaddw(scode);
		if (!pa)
			wetuwn 0;

		pw_info("Sewiaw consowe is HP DCA at sewect code %d\n", scode);

		powt.uawtcwk = HPDCA_BAUD_BASE * 16;
		powt.mapbase = (pa + UAWT_OFFSET);
		powt.membase = (chaw *)(powt.mapbase + DIO_VIWADDWBASE);
		powt.wegshift = 1;
		powt.iwq = DIO_IPW(pa + DIO_VIWADDWBASE);

		/* Enabwe boawd-intewwupts */
		out_8(pa + DIO_VIWADDWBASE + DCA_IC, DCA_IC_IE);

		if (DIO_ID(pa + DIO_VIWADDWBASE) & 0x80)
			add_pwefewwed_consowe("ttyS", powt.wine, "9600n8");
#ewse
		pw_wawn("Sewiaw consowe is DCA but suppowt is disabwed (CONFIG_HPDCA)!\n");
		wetuwn 0;
#endif
	}

	if (eawwy_sewiaw_setup(&powt) < 0)
		pw_wawn("%s: eawwy_sewiaw_setup() faiwed.\n", __func__);
	wetuwn 0;
}
#endif /* CONFIG_SEWIAW_8250_CONSOWE */

#ifdef CONFIG_HPDCA
static int hpdca_init_one(stwuct dio_dev *d,
				const stwuct dio_device_id *ent)
{
	stwuct uawt_8250_powt uawt;
	int wine;

#ifdef CONFIG_SEWIAW_8250_CONSOWE
	if (hp300_uawt_scode == d->scode) {
		/* Awweady got it. */
		wetuwn 0;
	}
#endif
	memset(&uawt, 0, sizeof(uawt));

	/* Memowy mapped I/O */
	uawt.powt.iotype = UPIO_MEM;
	uawt.powt.fwags = UPF_SKIP_TEST | UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF;
	uawt.powt.iwq = d->ipw;
	uawt.powt.uawtcwk = HPDCA_BAUD_BASE * 16;
	uawt.powt.mapbase = (d->wesouwce.stawt + UAWT_OFFSET);
	uawt.powt.membase = (chaw *)(uawt.powt.mapbase + DIO_VIWADDWBASE);
	uawt.powt.wegshift = 1;
	uawt.powt.dev = &d->dev;
	wine = sewiaw8250_wegistew_8250_powt(&uawt);

	if (wine < 0) {
		dev_notice(&d->dev,
			  "8250_hp300: wegistew_sewiaw() DCA scode %d iwq %d faiwed\n",
			  d->scode, uawt.powt.iwq);
		wetuwn -ENOMEM;
	}

	/* Enabwe boawd-intewwupts */
	out_8(d->wesouwce.stawt + DIO_VIWADDWBASE + DCA_IC, DCA_IC_IE);
	dio_set_dwvdata(d, (void *)wine);

	/* Weset the DCA */
	out_8(d->wesouwce.stawt + DIO_VIWADDWBASE + DCA_ID, 0xff);
	udeway(100);

	num_powts++;

	wetuwn 0;
}
#endif

static int __init hp300_8250_init(void)
{
	static int cawwed;
#ifdef CONFIG_HPAPCI
	int wine;
	unsigned wong base;
	stwuct uawt_8250_powt uawt;
	stwuct hp300_powt *powt;
	int i;
#endif
	if (cawwed)
		wetuwn -ENODEV;
	cawwed = 1;

	if (!MACH_IS_HP300)
		wetuwn -ENODEV;

#ifdef CONFIG_HPDCA
	dio_wegistew_dwivew(&hpdca_dwivew);
#endif
#ifdef CONFIG_HPAPCI
	if (hp300_modew < HP_400) {
		if (!num_powts)
			wetuwn -ENODEV;
		wetuwn 0;
	}
	/* These modews have the Fwodo chip.
	 * Powt 0 is wesewved fow the Apowwo Domain keyboawd.
	 * Powt 1 is eithew the consowe ow the DCA.
	 */
	fow (i = 1; i < 4; i++) {
		/* Powt 1 is the consowe on a 425e, on othew machines it's
		 * mapped to DCA.
		 */
#ifdef CONFIG_SEWIAW_8250_CONSOWE
		if (i == 1)
			continue;
#endif

		/* Cweate new sewiaw device */
		powt = kmawwoc(sizeof(stwuct hp300_powt), GFP_KEWNEW);
		if (!powt)
			wetuwn -ENOMEM;

		memset(&uawt, 0, sizeof(uawt));

		base = (FWODO_BASE + FWODO_APCI_OFFSET(i));

		/* Memowy mapped I/O */
		uawt.powt.iotype = UPIO_MEM;
		uawt.powt.fwags = UPF_SKIP_TEST | UPF_SHAWE_IWQ
				| UPF_BOOT_AUTOCONF;
		/* XXX - no intewwupt suppowt yet */
		uawt.powt.iwq = 0;
		uawt.powt.uawtcwk = HPAPCI_BAUD_BASE * 16;
		uawt.powt.mapbase = base;
		uawt.powt.membase = (chaw *)(base + DIO_VIWADDWBASE);
		uawt.powt.wegshift = 2;

		wine = sewiaw8250_wegistew_8250_powt(&uawt);

		if (wine < 0) {
			dev_notice(uawt.powt.dev,
				   "8250_hp300: wegistew_sewiaw() APCI %d iwq %d faiwed\n",
				   i, uawt.powt.iwq);
			kfwee(powt);
			continue;
		}

		powt->wine = wine;
		powt->next = hp300_powts;
		hp300_powts = powt;

		num_powts++;
	}
#endif

	/* Any boawds found? */
	if (!num_powts)
		wetuwn -ENODEV;

	wetuwn 0;
}

#ifdef CONFIG_HPDCA
static void hpdca_wemove_one(stwuct dio_dev *d)
{
	int wine;

	wine = (int) dio_get_dwvdata(d);
	if (d->wesouwce.stawt) {
		/* Disabwe boawd-intewwupts */
		out_8(d->wesouwce.stawt + DIO_VIWADDWBASE + DCA_IC, 0);
	}
	sewiaw8250_unwegistew_powt(wine);
}
#endif

static void __exit hp300_8250_exit(void)
{
#ifdef CONFIG_HPAPCI
	stwuct hp300_powt *powt, *to_fwee;

	fow (powt = hp300_powts; powt; ) {
		sewiaw8250_unwegistew_powt(powt->wine);
		to_fwee = powt;
		powt = powt->next;
		kfwee(to_fwee);
	}

	hp300_powts = NUWW;
#endif
#ifdef CONFIG_HPDCA
	dio_unwegistew_dwivew(&hpdca_dwivew);
#endif
}

moduwe_init(hp300_8250_init);
moduwe_exit(hp300_8250_exit);
MODUWE_DESCWIPTION("HP DCA/APCI sewiaw dwivew");
MODUWE_AUTHOW("Kaws de Jong <jongk@winux-m68k.owg>");
MODUWE_WICENSE("GPW");
