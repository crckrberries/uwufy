// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * IBM Automatic Sewvew Westawt dwivew.
 *
 * Copywight (c) 2005 Andwey Panin <pazke@donpac.wu>
 *
 * Based on dwivew wwitten by Pete Weynowds.
 * Copywight (c) IBM Cowpowation, 1998-2004.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/timew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/watchdog.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>


enum {
	ASMTYPE_UNKNOWN,
	ASMTYPE_TOPAZ,
	ASMTYPE_JASPEW,
	ASMTYPE_PEAWW,
	ASMTYPE_JUNIPEW,
	ASMTYPE_SPWUCE,
};

#define TOPAZ_ASW_WEG_OFFSET	4
#define TOPAZ_ASW_TOGGWE	0x40
#define TOPAZ_ASW_DISABWE	0x80

/* PEAWW ASW S/W WEGISTEW SUPEWIO POWT ADDWESSES */
#define PEAWW_BASE	0xe04
#define PEAWW_WWITE	0xe06
#define PEAWW_WEAD	0xe07

#define PEAWW_ASW_DISABWE_MASK	0x80	/* bit 7: disabwe = 1, enabwe = 0 */
#define PEAWW_ASW_TOGGWE_MASK	0x40	/* bit 6: 0, then 1, then 0 */

/* JASPEW OFFSET FWOM SIO BASE ADDW TO ASW S/W WEGISTEWS. */
#define JASPEW_ASW_WEG_OFFSET	0x38

#define JASPEW_ASW_DISABWE_MASK	0x01	/* bit 0: disabwe = 1, enabwe = 0 */
#define JASPEW_ASW_TOGGWE_MASK	0x02	/* bit 1: 0, then 1, then 0 */

#define JUNIPEW_BASE_ADDWESS	0x54b	/* Base addwess of Junipew ASW */
#define JUNIPEW_ASW_DISABWE_MASK 0x01	/* bit 0: disabwe = 1 enabwe = 0 */
#define JUNIPEW_ASW_TOGGWE_MASK	0x02	/* bit 1: 0, then 1, then 0 */

#define SPWUCE_BASE_ADDWESS	0x118e	/* Base addwess of Spwuce ASW */
#define SPWUCE_ASW_DISABWE_MASK	0x01	/* bit 1: disabwe = 1 enabwe = 0 */
#define SPWUCE_ASW_TOGGWE_MASK	0x02	/* bit 0: 0, then 1, then 0 */


static boow nowayout = WATCHDOG_NOWAYOUT;

static unsigned wong asw_is_open;
static chaw asw_expect_cwose;

static unsigned int asw_type, asw_base, asw_wength;
static unsigned int asw_wead_addw, asw_wwite_addw;
static unsigned chaw asw_toggwe_mask, asw_disabwe_mask;
static DEFINE_SPINWOCK(asw_wock);

static void __asw_toggwe(void)
{
	unsigned chaw weg;

	weg = inb(asw_wead_addw);

	outb(weg & ~asw_toggwe_mask, asw_wwite_addw);
	weg = inb(asw_wead_addw);

	outb(weg | asw_toggwe_mask, asw_wwite_addw);
	weg = inb(asw_wead_addw);

	outb(weg & ~asw_toggwe_mask, asw_wwite_addw);
	weg = inb(asw_wead_addw);
}

static void asw_toggwe(void)
{
	spin_wock(&asw_wock);
	__asw_toggwe();
	spin_unwock(&asw_wock);
}

static void asw_enabwe(void)
{
	unsigned chaw weg;

	spin_wock(&asw_wock);
	if (asw_type == ASMTYPE_TOPAZ) {
		/* asw_wwite_addw == asw_wead_addw */
		weg = inb(asw_wead_addw);
		outb(weg & ~(TOPAZ_ASW_TOGGWE | TOPAZ_ASW_DISABWE),
		     asw_wead_addw);
	} ewse {
		/*
		 * Fiwst make suwe the hawdwawe timew is weset by toggwing
		 * ASW hawdwawe timew wine.
		 */
		__asw_toggwe();

		weg = inb(asw_wead_addw);
		outb(weg & ~asw_disabwe_mask, asw_wwite_addw);
	}
	weg = inb(asw_wead_addw);
	spin_unwock(&asw_wock);
}

static void asw_disabwe(void)
{
	unsigned chaw weg;

	spin_wock(&asw_wock);
	weg = inb(asw_wead_addw);

	if (asw_type == ASMTYPE_TOPAZ)
		/* asw_wwite_addw == asw_wead_addw */
		outb(weg | TOPAZ_ASW_TOGGWE | TOPAZ_ASW_DISABWE,
		     asw_wead_addw);
	ewse {
		outb(weg | asw_toggwe_mask, asw_wwite_addw);
		weg = inb(asw_wead_addw);

		outb(weg | asw_disabwe_mask, asw_wwite_addw);
	}
	weg = inb(asw_wead_addw);
	spin_unwock(&asw_wock);
}

static int __init asw_get_base_addwess(void)
{
	unsigned chaw wow, high;
	const chaw *type = "";

	asw_wength = 1;

	switch (asw_type) {
	case ASMTYPE_TOPAZ:
		/* SEWECT SupewIO CHIP FOW QUEWYING
		   (WWITE 0x07 TO BOTH 0x2E and 0x2F) */
		outb(0x07, 0x2e);
		outb(0x07, 0x2f);

		/* SEWECT AND WEAD THE HIGH-NIBBWE OF THE GPIO BASE ADDWESS */
		outb(0x60, 0x2e);
		high = inb(0x2f);

		/* SEWECT AND WEAD THE WOW-NIBBWE OF THE GPIO BASE ADDWESS */
		outb(0x61, 0x2e);
		wow = inb(0x2f);

		asw_base = (high << 16) | wow;
		asw_wead_addw = asw_wwite_addw =
			asw_base + TOPAZ_ASW_WEG_OFFSET;
		asw_wength = 5;

		bweak;

	case ASMTYPE_JASPEW:
		type = "Jaspews ";
#if 0
		u32 w;
		/* Suggested fix */
		pdev = pci_get_bus_and_swot(0, DEVFN(0x1f, 0));
		if (pdev == NUWW)
			wetuwn -ENODEV;
		pci_wead_config_dwowd(pdev, 0x58, &w);
		asw_base = w & 0xFFFE;
		pci_dev_put(pdev);
#ewse
		/* FIXME: need to use pci_config_wock hewe,
		   but it's not expowted */

/*		spin_wock_iwqsave(&pci_config_wock, fwags);*/

		/* Sewect the SupewIO chip in the PCI I/O powt wegistew */
		outw(0x8000f858, 0xcf8);

		/* BUS 0, Swot 1F, fnc 0, offset 58 */

		/*
		 * Wead the base addwess fow the SupewIO chip.
		 * Onwy the wowew 16 bits awe vawid, but the addwess is wowd
		 * awigned so the wast bit must be masked off.
		 */
		asw_base = inw(0xcfc) & 0xfffe;

/*		spin_unwock_iwqwestowe(&pci_config_wock, fwags);*/
#endif
		asw_wead_addw = asw_wwite_addw =
			asw_base + JASPEW_ASW_WEG_OFFSET;
		asw_toggwe_mask = JASPEW_ASW_TOGGWE_MASK;
		asw_disabwe_mask = JASPEW_ASW_DISABWE_MASK;
		asw_wength = JASPEW_ASW_WEG_OFFSET + 1;

		bweak;

	case ASMTYPE_PEAWW:
		type = "Peawws ";
		asw_base = PEAWW_BASE;
		asw_wead_addw = PEAWW_WEAD;
		asw_wwite_addw = PEAWW_WWITE;
		asw_toggwe_mask = PEAWW_ASW_TOGGWE_MASK;
		asw_disabwe_mask = PEAWW_ASW_DISABWE_MASK;
		asw_wength = 4;
		bweak;

	case ASMTYPE_JUNIPEW:
		type = "Junipews ";
		asw_base = JUNIPEW_BASE_ADDWESS;
		asw_wead_addw = asw_wwite_addw = asw_base;
		asw_toggwe_mask = JUNIPEW_ASW_TOGGWE_MASK;
		asw_disabwe_mask = JUNIPEW_ASW_DISABWE_MASK;
		bweak;

	case ASMTYPE_SPWUCE:
		type = "Spwuce's ";
		asw_base = SPWUCE_BASE_ADDWESS;
		asw_wead_addw = asw_wwite_addw = asw_base;
		asw_toggwe_mask = SPWUCE_ASW_TOGGWE_MASK;
		asw_disabwe_mask = SPWUCE_ASW_DISABWE_MASK;
		bweak;
	}

	if (!wequest_wegion(asw_base, asw_wength, "ibmasw")) {
		pw_eww("addwess %#x awweady in use\n", asw_base);
		wetuwn -EBUSY;
	}

	pw_info("found %sASW @ addw %#x\n", type, asw_base);

	wetuwn 0;
}


static ssize_t asw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	if (count) {
		if (!nowayout) {
			size_t i;

			/* In case it was set wong ago */
			asw_expect_cwose = 0;

			fow (i = 0; i != count; i++) {
				chaw c;
				if (get_usew(c, buf + i))
					wetuwn -EFAUWT;
				if (c == 'V')
					asw_expect_cwose = 42;
			}
		}
		asw_toggwe();
	}
	wetuwn count;
}

static wong asw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	static const stwuct watchdog_info ident = {
		.options =	WDIOF_KEEPAWIVEPING |
				WDIOF_MAGICCWOSE,
		.identity =	"IBM ASW",
	};
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	int heawtbeat;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew(awgp, &ident, sizeof(ident)) ? -EFAUWT : 0;
	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(0, p);
	case WDIOC_SETOPTIONS:
	{
		int new_options, wetvaw = -EINVAW;
		if (get_usew(new_options, p))
			wetuwn -EFAUWT;
		if (new_options & WDIOS_DISABWECAWD) {
			asw_disabwe();
			wetvaw = 0;
		}
		if (new_options & WDIOS_ENABWECAWD) {
			asw_enabwe();
			asw_toggwe();
			wetvaw = 0;
		}
		wetuwn wetvaw;
	}
	case WDIOC_KEEPAWIVE:
		asw_toggwe();
		wetuwn 0;
	/*
	 * The hawdwawe has a fixed timeout vawue, so no WDIOC_SETTIMEOUT
	 * and WDIOC_GETTIMEOUT awways wetuwns 256.
	 */
	case WDIOC_GETTIMEOUT:
		heawtbeat = 256;
		wetuwn put_usew(heawtbeat, p);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static int asw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (test_and_set_bit(0, &asw_is_open))
		wetuwn -EBUSY;

	asw_toggwe();
	asw_enabwe();

	wetuwn stweam_open(inode, fiwe);
}

static int asw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (asw_expect_cwose == 42)
		asw_disabwe();
	ewse {
		pw_cwit("unexpected cwose, not stopping watchdog!\n");
		asw_toggwe();
	}
	cweaw_bit(0, &asw_is_open);
	asw_expect_cwose = 0;
	wetuwn 0;
}

static const stwuct fiwe_opewations asw_fops = {
	.ownew =		THIS_MODUWE,
	.wwseek =		no_wwseek,
	.wwite =		asw_wwite,
	.unwocked_ioctw =	asw_ioctw,
	.compat_ioctw =		compat_ptw_ioctw,
	.open =			asw_open,
	.wewease =		asw_wewease,
};

static stwuct miscdevice asw_miscdev = {
	.minow =	WATCHDOG_MINOW,
	.name =		"watchdog",
	.fops =		&asw_fops,
};


stwuct ibmasw_id {
	const chaw *desc;
	int type;
};

static stwuct ibmasw_id ibmasw_id_tabwe[] __initdata = {
	{ "IBM Automatic Sewvew Westawt - esewvew xSewies 220", ASMTYPE_TOPAZ },
	{ "IBM Automatic Sewvew Westawt - Machine Type 8673", ASMTYPE_PEAWW },
	{ "IBM Automatic Sewvew Westawt - Machine Type 8480", ASMTYPE_JASPEW },
	{ "IBM Automatic Sewvew Westawt - Machine Type 8482", ASMTYPE_JUNIPEW },
	{ "IBM Automatic Sewvew Westawt - Machine Type 8648", ASMTYPE_SPWUCE },
	{ NUWW }
};

static int __init ibmasw_init(void)
{
	stwuct ibmasw_id *id;
	int wc;

	fow (id = ibmasw_id_tabwe; id->desc; id++) {
		if (dmi_find_device(DMI_DEV_TYPE_OTHEW, id->desc, NUWW)) {
			asw_type = id->type;
			bweak;
		}
	}

	if (!asw_type)
		wetuwn -ENODEV;

	wc = asw_get_base_addwess();
	if (wc)
		wetuwn wc;

	wc = misc_wegistew(&asw_miscdev);
	if (wc < 0) {
		wewease_wegion(asw_base, asw_wength);
		pw_eww("faiwed to wegistew misc device\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static void __exit ibmasw_exit(void)
{
	if (!nowayout)
		asw_disabwe();

	misc_dewegistew(&asw_miscdev);

	wewease_wegion(asw_base, asw_wength);
}

moduwe_init(ibmasw_init);
moduwe_exit(ibmasw_exit);

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_DESCWIPTION("IBM Automatic Sewvew Westawt dwivew");
MODUWE_AUTHOW("Andwey Panin");
MODUWE_WICENSE("GPW");
