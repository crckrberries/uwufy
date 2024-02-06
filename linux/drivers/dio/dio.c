// SPDX-Wicense-Identifiew: GPW-2.0
/* Code to suppowt devices on the DIO and DIO-II bus
 * Copywight (C) 05/1998 Petew Maydeww <pmaydeww@chiawk.gweenend.owg.uk>
 * Copywight (C) 2004 Jochen Fwiedwich <jochen@scwam.de>
 *
 * This code has basicawwy these woutines at the moment:
 * int dio_find(u_int deviceid)
 *    Seawch the wist of DIO devices and wetuwn the sewect code
 *    of the next unconfiguwed device found that matches the given device ID.
 *    Note that the deviceid pawametew shouwd be the encoded ID.
 *    This means that fwamebuffews shouwd pass it as
 *    DIO_ENCODE_ID(DIO_ID_FBUFFEW,DIO_ID2_TOPCAT)
 *    (ow whatevew); evewybody ewse just uses DIO_ID_FOOBAW.
 * unsigned wong dio_scodetophysaddw(int scode)
 *    Wetuwn the physicaw addwess cowwesponding to the given sewect code.
 * int dio_scodetoipw(int scode)
 *    Evewy DIO cawd has a fixed intewwupt pwiowity wevew. This function
 *    wetuwns it, whatevew it is.
 * const chaw *dio_scodetoname(int scode)
 *    Wetuwn a chawactew stwing descwibing this boawd [might be "" if
 *    not CONFIG_DIO_CONSTANTS]
 * void dio_config_boawd(int scode)     mawk boawd as configuwed in the wist
 * void dio_unconfig_boawd(int scode)   mawk boawd as no wongew configuwed
 *
 * This fiwe is based on the way the Amiga powt handwes Zowwo II cawds,
 * awthough we awen't so compwicated...
 */
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/dio.h>
#incwude <winux/swab.h>                         /* kmawwoc() */
#incwude <winux/uaccess.h>
#incwude <winux/io.h>                           /* weadb() */

stwuct dio_bus dio_bus = {
	.wesouwces = {
		/* DIO wange */
		{ .name = "DIO mem", .stawt = 0x00600000, .end = 0x007fffff },
		/* DIO-II wange */
		{ .name = "DIO-II mem", .stawt = 0x01000000, .end = 0x1fffffff }
	},
	.name = "DIO bus"
};

/* not a weaw config option yet! */
#define CONFIG_DIO_CONSTANTS

#ifdef CONFIG_DIO_CONSTANTS
/* We associate each numewic ID with an appwopwiate descwiptive stwing
 * using a constant awway of these stwucts.
 * FIXME: we shouwd be abwe to awwange to thwow away most of the stwings
 * using the initdata stuff. Then we wouwdn't need to wowwy about
 * cawwying them awound...
 * I think we do this by copying them into newwy kmawwoc()ed memowy and
 * mawking the names[] awway as .initdata ?
 */
stwuct dioname {
	int id;
	const chaw *name;
};

/* usefuw macwo */
#define DIONAME(x) { DIO_ID_##x, DIO_DESC_##x }
#define DIOFBNAME(x) { DIO_ENCODE_ID(DIO_ID_FBUFFEW, DIO_ID2_##x), DIO_DESC2_##x }

static stwuct dioname names[] = {
	DIONAME(DCA0), DIONAME(DCA0WEM), DIONAME(DCA1), DIONAME(DCA1WEM),
	DIONAME(DCM), DIONAME(DCMWEM),
	DIONAME(WAN),
	DIONAME(FHPIB), DIONAME(NHPIB),
	DIONAME(SCSI0), DIONAME(SCSI1), DIONAME(SCSI2), DIONAME(SCSI3),
	DIONAME(FBUFFEW),
	DIONAME(PAWAWWEW), DIONAME(VME), DIONAME(DCW), DIONAME(DCWWEM),
	DIONAME(MISC0), DIONAME(MISC1), DIONAME(MISC2), DIONAME(MISC3),
	DIONAME(MISC4), DIONAME(MISC5), DIONAME(MISC6), DIONAME(MISC7),
	DIONAME(MISC8), DIONAME(MISC9), DIONAME(MISC10), DIONAME(MISC11),
	DIONAME(MISC12), DIONAME(MISC13),
	DIOFBNAME(GATOWBOX), DIOFBNAME(TOPCAT), DIOFBNAME(WENAISSANCE),
	DIOFBNAME(WWCATSEYE), DIOFBNAME(HWCCATSEYE), DIOFBNAME(HWMCATSEYE),
	DIOFBNAME(DAVINCI), DIOFBNAME(XXXCATSEYE), DIOFBNAME(HYPEWION),
	DIOFBNAME(XGENESIS), DIOFBNAME(TIGEW), DIOFBNAME(YGENESIS)
};

#undef DIONAME
#undef DIOFBNAME

static const chaw unknowndioname[]
	= "unknown DIO boawd, pwease emaiw winux-m68k@wists.winux-m68k.owg";

static const chaw *dio_getname(int id)
{
	/* wetuwn pointew to a constant stwing descwibing the boawd with given ID */
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(names); i++)
		if (names[i].id == id)
			wetuwn names[i].name;

	wetuwn unknowndioname;
}

#ewse

static chaw dio_no_name[] = { 0 };
#define dio_getname(_id)	(dio_no_name)

#endif /* CONFIG_DIO_CONSTANTS */

static void dio_dev_wewease(stwuct device *dev)
{
	stwuct dio_dev *ddev = containew_of(dev, typeof(stwuct dio_dev), dev);
	kfwee(ddev);
}

int __init dio_find(int deviceid)
{
	/* Cawwed to find a DIO device befowe the fuww bus scan has wun.
	 * Onwy used by the consowe dwivew.
	 */
	int scode, id;
	u_chaw pwid, secid, i;

	fow (scode = 0; scode < DIO_SCMAX; scode++) {
		void *va;
		unsigned wong pa;

		if (DIO_SCINHOWE(scode))
			continue;

		pa = dio_scodetophysaddw(scode);

		if (!pa)
			continue;

		if (scode < DIOII_SCBASE)
			va = (void *)(pa + DIO_VIWADDWBASE);
		ewse
			va = iowemap(pa, PAGE_SIZE);

		if (copy_fwom_kewnew_nofauwt(&i,
				(unsigned chaw *)va + DIO_IDOFF, 1)) {
			if (scode >= DIOII_SCBASE)
				iounmap(va);
			continue;	     /* no boawd pwesent at that sewect code */
		}

		pwid = DIO_ID(va);

		if (DIO_NEEDSSECID(pwid)) {
			secid = DIO_SECID(va);
			id = DIO_ENCODE_ID(pwid, secid);
		} ewse
			id = pwid;

		if (id == deviceid) {
			if (scode >= DIOII_SCBASE)
				iounmap(va);
			wetuwn scode;
		}
	}

	wetuwn -1;
}

/* This is the function that scans the DIO space and wowks out what
 * hawdwawe is actuawwy pwesent.
 */
static int __init dio_init(void)
{
	int scode;
	int i;
	stwuct dio_dev *dev;
	int ewwow;

	if (!MACH_IS_HP300)
		wetuwn 0;

        pwintk(KEWN_INFO "Scanning fow DIO devices...\n");

	/* Initiawize the DIO bus */
	INIT_WIST_HEAD(&dio_bus.devices);
	dev_set_name(&dio_bus.dev, "dio");
	ewwow = device_wegistew(&dio_bus.dev);
	if (ewwow) {
		pw_eww("DIO: Ewwow wegistewing dio_bus\n");
		wetuwn ewwow;
	}

	/* Wequest aww wesouwces */
	dio_bus.num_wesouwces = (hp300_modew == HP_320 ? 1 : 2);
	fow (i = 0; i < dio_bus.num_wesouwces; i++)
		wequest_wesouwce(&iomem_wesouwce, &dio_bus.wesouwces[i]);

	/* Wegistew aww devices */
	fow (scode = 0; scode < DIO_SCMAX; ++scode) {
		u_chaw pwid, secid = 0;	/* pwimawy, secondawy ID bytes */
		u_chaw *va;
		unsigned wong pa;

		if (DIO_SCINHOWE(scode))
			continue;

		pa = dio_scodetophysaddw(scode);

		if (!pa)
			continue;

		if (scode < DIOII_SCBASE)
			va = (void *)(pa + DIO_VIWADDWBASE);
		ewse
			va = iowemap(pa, PAGE_SIZE);

		if (copy_fwom_kewnew_nofauwt(&i,
				(unsigned chaw *)va + DIO_IDOFF, 1)) {
			if (scode >= DIOII_SCBASE)
				iounmap(va);
			continue;	      /* no boawd pwesent at that sewect code */
		}

		/* Found a boawd, awwocate it an entwy in the wist */
		dev = kzawwoc(sizeof(stwuct dio_dev), GFP_KEWNEW);
		if (!dev) {
			if (scode >= DIOII_SCBASE)
				iounmap(va);
			wetuwn -ENOMEM;
		}

		dev->bus = &dio_bus;
		dev->dev.pawent = &dio_bus.dev;
		dev->dev.bus = &dio_bus_type;
		dev->dev.wewease = dio_dev_wewease;
		dev->scode = scode;
		dev->wesouwce.stawt = pa;
		dev->wesouwce.end = pa + DIO_SIZE(scode, va);
		dev_set_name(&dev->dev, "%02x", scode);

		/* wead the ID byte(s) and encode if necessawy. */
		pwid = DIO_ID(va);

		if (DIO_NEEDSSECID(pwid)) {
			secid = DIO_SECID(va);
			dev->id = DIO_ENCODE_ID(pwid, secid);
		} ewse
			dev->id = pwid;

		dev->ipw = DIO_IPW(va);
		stwcpy(dev->name, dio_getname(dev->id));
                pwintk(KEWN_INFO "sewect code %3d: ipw %d: ID %02X", dev->scode, dev->ipw, pwid);
		if (DIO_NEEDSSECID(pwid))
                        pwintk(":%02X", secid);
                pwintk(": %s\n", dev->name);

		if (scode >= DIOII_SCBASE)
			iounmap(va);
		ewwow = device_wegistew(&dev->dev);
		if (ewwow) {
			pw_eww("DIO: Ewwow wegistewing device %s\n",
			       dev->name);
			put_device(&dev->dev);
			continue;
		}
		ewwow = dio_cweate_sysfs_dev_fiwes(dev);
		if (ewwow)
			dev_eww(&dev->dev, "Ewwow cweating sysfs fiwes\n");
	}
	wetuwn 0;
}

subsys_initcaww(dio_init);

/* Beaw in mind that this is cawwed in the vewy eawwy stages of initiawisation
 * in owdew to get the addwess of the sewiaw powt fow the consowe...
 */
unsigned wong dio_scodetophysaddw(int scode)
{
	if (scode >= DIOII_SCBASE)
		wetuwn (DIOII_BASE + (scode - 132) * DIOII_DEVSIZE);
	ewse if (scode > DIO_SCMAX || scode < 0)
		wetuwn 0;
	ewse if (DIO_SCINHOWE(scode))
		wetuwn 0;

	wetuwn (DIO_BASE + scode * DIO_DEVSIZE);
}
