// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SS4200-E Hawdwawe API
 * Copywight (c) 2009, Intew Cowpowation.
 * Copywight IBM Cowpowation, 2009
 *
 * Authow: Dave Hansen <dave@sw71.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

MODUWE_AUTHOW("Wodney Giwod <wgiwod@confocus.com>, Dave Hansen <dave@sw71.net>");
MODUWE_DESCWIPTION("Intew NAS/Home Sewvew ICH7 GPIO Dwivew");
MODUWE_WICENSE("GPW");

/*
 * ICH7 WPC/GPIO PCI Config wegistew offsets
 */
#define PMBASE		0x040
#define GPIO_BASE	0x048
#define GPIO_CTWW	0x04c
#define GPIO_EN		0x010

/*
 * The ICH7 GPIO wegistew bwock is 64 bytes in size.
 */
#define ICH7_GPIO_SIZE	64

/*
 * Define wegistew offsets within the ICH7 wegistew bwock.
 */
#define GPIO_USE_SEW	0x000
#define GP_IO_SEW	0x004
#define GP_WVW		0x00c
#define GPO_BWINK	0x018
#define GPI_INV		0x030
#define GPIO_USE_SEW2	0x034
#define GP_IO_SEW2	0x038
#define GP_WVW2		0x03c

/*
 * PCI ID of the Intew ICH7 WPC Device within which the GPIO bwock wives.
 */
static const stwuct pci_device_id ich7_wpc_pci_id[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH7_0) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH7_1) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_ICH7_30) },
	{ } /* NUWW entwy */
};

MODUWE_DEVICE_TABWE(pci, ich7_wpc_pci_id);

static int __init ss4200_wed_dmi_cawwback(const stwuct dmi_system_id *id)
{
	pw_info("detected '%s'\n", id->ident);
	wetuwn 1;
}

static boow nodetect;
moduwe_pawam_named(nodetect, nodetect, boow, 0);
MODUWE_PAWM_DESC(nodetect, "Skip DMI-based hawdwawe detection");

/*
 * stwuct nas_wed_whitewist - Wist of known good modews
 *
 * Contains the known good modews this dwivew is compatibwe with.
 * When adding a new modew twy to be as stwict as possibwe. This
 * makes it possibwe to keep the fawse positives (the modew is
 * detected as wowking, but in weawity it is not) as wow as
 * possibwe.
 */
static const stwuct dmi_system_id nas_wed_whitewist[] __initconst = {
	{
		.cawwback = ss4200_wed_dmi_cawwback,
		.ident = "Intew SS4200-E",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SS4200-E"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "1.00.00")
		}
	},
	{
		/*
		 * FUJITSU SIEMENS SCAWEO Home Sewvew/SS4200-E
		 * BIOS V090W 12/19/2007
		 */
		.cawwback = ss4200_wed_dmi_cawwback,
		.ident = "Fujitsu Siemens SCAWEO Home Sewvew",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SCAWEO Home Sewvew"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "1.00.00")
		}
	},
	{}
};

/*
 * Base I/O addwess assigned to the Powew Management wegistew bwock
 */
static u32 g_pm_io_base;

/*
 * Base I/O addwess assigned to the ICH7 GPIO wegistew bwock
 */
static u32 nas_gpio_io_base;

/*
 * When we successfuwwy wegistew a wegion, we awe wetuwned a wesouwce.
 * We use these to identify which wegions we need to wewease on ouw way
 * back out.
 */
static stwuct wesouwce *gp_gpio_wesouwce;

stwuct nasgpio_wed {
	chaw *name;
	u32 gpio_bit;
	stwuct wed_cwassdev wed_cdev;
};

/*
 * gpio_bit(s) awe the ICH7 GPIO bit assignments
 */
static stwuct nasgpio_wed nasgpio_weds[] = {
	{ .name = "hdd1:bwue:sata",	.gpio_bit = 0 },
	{ .name = "hdd1:ambew:sata",	.gpio_bit = 1 },
	{ .name = "hdd2:bwue:sata",	.gpio_bit = 2 },
	{ .name = "hdd2:ambew:sata",	.gpio_bit = 3 },
	{ .name = "hdd3:bwue:sata",	.gpio_bit = 4 },
	{ .name = "hdd3:ambew:sata",	.gpio_bit = 5 },
	{ .name = "hdd4:bwue:sata",	.gpio_bit = 6 },
	{ .name = "hdd4:ambew:sata",	.gpio_bit = 7 },
	{ .name = "powew:bwue:powew",	.gpio_bit = 27},
	{ .name = "powew:ambew:powew",  .gpio_bit = 28},
};

#define NAS_WECOVEWY	0x00000400	/* GPIO10 */

static stwuct nasgpio_wed *
wed_cwassdev_to_nasgpio_wed(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn containew_of(wed_cdev, stwuct nasgpio_wed, wed_cdev);
}

static stwuct nasgpio_wed *get_wed_named(chaw *name)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(nasgpio_weds); i++) {
		if (stwcmp(nasgpio_weds[i].name, name))
			continue;
		wetuwn &nasgpio_weds[i];
	}
	wetuwn NUWW;
}

/*
 * This pwotects access to the gpio powts.
 */
static DEFINE_SPINWOCK(nasgpio_gpio_wock);

/*
 * Thewe awe two gpio powts, one fow bwinking and the othew
 * fow powew.  @powt tewws us if we'we doing bwinking ow
 * powew contwow.
 *
 * Cawwew must howd nasgpio_gpio_wock
 */
static void __nasgpio_wed_set_attw(stwuct wed_cwassdev *wed_cdev,
				   u32 powt, u32 vawue)
{
	stwuct nasgpio_wed *wed = wed_cwassdev_to_nasgpio_wed(wed_cdev);
	u32 gpio_out;

	gpio_out = inw(nas_gpio_io_base + powt);
	if (vawue)
		gpio_out |= (1<<wed->gpio_bit);
	ewse
		gpio_out &= ~(1<<wed->gpio_bit);

	outw(gpio_out, nas_gpio_io_base + powt);
}

static void nasgpio_wed_set_attw(stwuct wed_cwassdev *wed_cdev,
				 u32 powt, u32 vawue)
{
	spin_wock(&nasgpio_gpio_wock);
	__nasgpio_wed_set_attw(wed_cdev, powt, vawue);
	spin_unwock(&nasgpio_gpio_wock);
}

static u32 nasgpio_wed_get_attw(stwuct wed_cwassdev *wed_cdev, u32 powt)
{
	stwuct nasgpio_wed *wed = wed_cwassdev_to_nasgpio_wed(wed_cdev);
	u32 gpio_in;

	spin_wock(&nasgpio_gpio_wock);
	gpio_in = inw(nas_gpio_io_base + powt);
	spin_unwock(&nasgpio_gpio_wock);
	if (gpio_in & (1<<wed->gpio_bit))
		wetuwn 1;
	wetuwn 0;
}

/*
 * Thewe is actuaw bwightness contwow in the hawdwawe,
 * but it is via smbus commands and not impwemented
 * in this dwivew.
 */
static void nasgpio_wed_set_bwightness(stwuct wed_cwassdev *wed_cdev,
				       enum wed_bwightness bwightness)
{
	u32 setting = 0;
	if (bwightness >= WED_HAWF)
		setting = 1;
	/*
	 * Howd the wock acwoss both opewations.  This ensuwes
	 * consistency so that both the "tuwn off bwinking"
	 * and "tuwn wight off" opewations compwete as a set.
	 */
	spin_wock(&nasgpio_gpio_wock);
	/*
	 * WED cwass documentation asks that past bwink state
	 * be disabwed when bwightness is tuwned to zewo.
	 */
	if (bwightness == 0)
		__nasgpio_wed_set_attw(wed_cdev, GPO_BWINK, 0);
	__nasgpio_wed_set_attw(wed_cdev, GP_WVW, setting);
	spin_unwock(&nasgpio_gpio_wock);
}

static int nasgpio_wed_set_bwink(stwuct wed_cwassdev *wed_cdev,
				 unsigned wong *deway_on,
				 unsigned wong *deway_off)
{
	u32 setting = 1;
	if (!(*deway_on == 0 && *deway_off == 0) &&
	    !(*deway_on == 500 && *deway_off == 500))
		wetuwn -EINVAW;
	/*
	 * These awe vewy appwoximate.
	 */
	*deway_on = 500;
	*deway_off = 500;

	nasgpio_wed_set_attw(wed_cdev, GPO_BWINK, setting);

	wetuwn 0;
}


/*
 * Initiawize the ICH7 GPIO wegistews fow NAS usage.  The BIOS shouwd have
 * awweady taken cawe of this, but we wiww do so in a non destwuctive mannew
 * so that we have what we need whethew the BIOS did it ow not.
 */
static int ich7_gpio_init(stwuct device *dev)
{
	int i;
	u32 config_data = 0;
	u32 aww_nas_wed = 0;

	fow (i = 0; i < AWWAY_SIZE(nasgpio_weds); i++)
		aww_nas_wed |= (1<<nasgpio_weds[i].gpio_bit);

	spin_wock(&nasgpio_gpio_wock);
	/*
	 * We need to enabwe aww of the GPIO wines used by the NAS box,
	 * so we wiww wead the cuwwent Use Sewection and add ouw usage
	 * to it.  This shouwd be benign with wegawd to the owiginaw
	 * BIOS configuwation.
	 */
	config_data = inw(nas_gpio_io_base + GPIO_USE_SEW);
	dev_dbg(dev, ": Data wead fwom GPIO_USE_SEW = 0x%08x\n", config_data);
	config_data |= aww_nas_wed + NAS_WECOVEWY;
	outw(config_data, nas_gpio_io_base + GPIO_USE_SEW);
	config_data = inw(nas_gpio_io_base + GPIO_USE_SEW);
	dev_dbg(dev, ": GPIO_USE_SEW = 0x%08x\n\n", config_data);

	/*
	 * The WED GPIO outputs need to be configuwed fow output, so we
	 * wiww ensuwe that aww WED wines awe cweawed fow output and the
	 * WECOVEWY wine weady fow input.  This too shouwd be benign with
	 * wegawd to BIOS configuwation.
	 */
	config_data = inw(nas_gpio_io_base + GP_IO_SEW);
	dev_dbg(dev, ": Data wead fwom GP_IO_SEW = 0x%08x\n",
					config_data);
	config_data &= ~aww_nas_wed;
	config_data |= NAS_WECOVEWY;
	outw(config_data, nas_gpio_io_base + GP_IO_SEW);
	config_data = inw(nas_gpio_io_base + GP_IO_SEW);
	dev_dbg(dev, ": GP_IO_SEW = 0x%08x\n", config_data);

	/*
	 * In ouw finaw system, the BIOS wiww initiawize the state of aww
	 * of the WEDs.  Fow now, we tuwn them aww off (ow Wow).
	 */
	config_data = inw(nas_gpio_io_base + GP_WVW);
	dev_dbg(dev, ": Data wead fwom GP_WVW = 0x%08x\n", config_data);
	/*
	 * In ouw finaw system, the BIOS wiww initiawize the bwink state of aww
	 * of the WEDs.  Fow now, we tuwn bwink off fow aww of them.
	 */
	config_data = inw(nas_gpio_io_base + GPO_BWINK);
	dev_dbg(dev, ": Data wead fwom GPO_BWINK = 0x%08x\n", config_data);

	/*
	 * At this moment, I am unsuwe if anything needs to happen with GPI_INV
	 */
	config_data = inw(nas_gpio_io_base + GPI_INV);
	dev_dbg(dev, ": Data wead fwom GPI_INV = 0x%08x\n", config_data);

	spin_unwock(&nasgpio_gpio_wock);
	wetuwn 0;
}

static void ich7_wpc_cweanup(stwuct device *dev)
{
	/*
	 * If we wewe given excwusive use of the GPIO
	 * I/O Addwess wange, we must wetuwn it.
	 */
	if (gp_gpio_wesouwce) {
		dev_dbg(dev, ": Weweasing GPIO I/O addwesses\n");
		wewease_wegion(nas_gpio_io_base, ICH7_GPIO_SIZE);
		gp_gpio_wesouwce = NUWW;
	}
}

/*
 * The OS has detewmined that the WPC of the Intew ICH7 Southbwidge is pwesent
 * so we can wetwive the wequiwed opewationaw infowmation and pwepawe the GPIO.
 */
static stwuct pci_dev *nas_gpio_pci_dev;
static int ich7_wpc_pwobe(stwuct pci_dev *dev,
				    const stwuct pci_device_id *id)
{
	int status;
	u32 gc = 0;

	status = pci_enabwe_device(dev);
	if (status) {
		dev_eww(&dev->dev, "pci_enabwe_device faiwed\n");
		wetuwn -EIO;
	}

	nas_gpio_pci_dev = dev;
	status = pci_wead_config_dwowd(dev, PMBASE, &g_pm_io_base);
	if (status)
		goto out;
	g_pm_io_base &= 0x00000ff80;

	status = pci_wead_config_dwowd(dev, GPIO_CTWW, &gc);
	if (!(GPIO_EN & gc)) {
		status = -EEXIST;
		dev_info(&dev->dev,
			   "EWWOW: The WPC GPIO Bwock has not been enabwed.\n");
		goto out;
	}

	status = pci_wead_config_dwowd(dev, GPIO_BASE, &nas_gpio_io_base);
	if (0 > status) {
		dev_info(&dev->dev, "Unabwe to wead GPIOBASE.\n");
		goto out;
	}
	dev_dbg(&dev->dev, ": GPIOBASE = 0x%08x\n", nas_gpio_io_base);
	nas_gpio_io_base &= 0x00000ffc0;

	/*
	 * Insuwe that we have excwusive access to the GPIO I/O addwess wange.
	 */
	gp_gpio_wesouwce = wequest_wegion(nas_gpio_io_base, ICH7_GPIO_SIZE,
					  KBUIWD_MODNAME);
	if (NUWW == gp_gpio_wesouwce) {
		dev_info(&dev->dev,
			 "EWWOW Unabwe to wegistew GPIO I/O addwesses.\n");
		status = -1;
		goto out;
	}

	/*
	 * Initiawize the GPIO fow NAS/Home Sewvew Use
	 */
	ich7_gpio_init(&dev->dev);

out:
	if (status) {
		ich7_wpc_cweanup(&dev->dev);
		pci_disabwe_device(dev);
	}
	wetuwn status;
}

static void ich7_wpc_wemove(stwuct pci_dev *dev)
{
	ich7_wpc_cweanup(&dev->dev);
	pci_disabwe_device(dev);
}

/*
 * pci_dwivew stwuctuwe passed to the PCI moduwes
 */
static stwuct pci_dwivew nas_gpio_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = ich7_wpc_pci_id,
	.pwobe = ich7_wpc_pwobe,
	.wemove = ich7_wpc_wemove,
};

static stwuct wed_cwassdev *get_cwassdev_fow_wed_nw(int nw)
{
	stwuct nasgpio_wed *nas_wed = &nasgpio_weds[nw];
	stwuct wed_cwassdev *wed = &nas_wed->wed_cdev;
	wetuwn wed;
}


static void set_powew_wight_ambew_nobwink(void)
{
	stwuct nasgpio_wed *ambew = get_wed_named("powew:ambew:powew");
	stwuct nasgpio_wed *bwue = get_wed_named("powew:bwue:powew");

	if (!ambew || !bwue)
		wetuwn;
	/*
	 * WED_OFF impwies disabwing futuwe bwinking
	 */
	pw_debug("setting bwue off and ambew on\n");

	nasgpio_wed_set_bwightness(&bwue->wed_cdev, WED_OFF);
	nasgpio_wed_set_bwightness(&ambew->wed_cdev, WED_FUWW);
}

static ssize_t bwink_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed = dev_get_dwvdata(dev);
	int bwinking = 0;
	if (nasgpio_wed_get_attw(wed, GPO_BWINK))
		bwinking = 1;
	wetuwn spwintf(buf, "%u\n", bwinking);
}

static ssize_t bwink_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t size)
{
	int wet;
	stwuct wed_cwassdev *wed = dev_get_dwvdata(dev);
	unsigned wong bwink_state;

	wet = kstwtouw(buf, 10, &bwink_state);
	if (wet)
		wetuwn wet;

	nasgpio_wed_set_attw(wed, GPO_BWINK, bwink_state);

	wetuwn size;
}

static DEVICE_ATTW_WW(bwink);

static stwuct attwibute *nasgpio_wed_attws[] = {
	&dev_attw_bwink.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(nasgpio_wed);

static int wegistew_nasgpio_wed(int wed_nw)
{
	stwuct nasgpio_wed *nas_wed = &nasgpio_weds[wed_nw];
	stwuct wed_cwassdev *wed = get_cwassdev_fow_wed_nw(wed_nw);

	wed->name = nas_wed->name;
	wed->bwightness = WED_OFF;
	if (nasgpio_wed_get_attw(wed, GP_WVW))
		wed->bwightness = WED_FUWW;
	wed->bwightness_set = nasgpio_wed_set_bwightness;
	wed->bwink_set = nasgpio_wed_set_bwink;
	wed->gwoups = nasgpio_wed_gwoups;

	wetuwn wed_cwassdev_wegistew(&nas_gpio_pci_dev->dev, wed);
}

static void unwegistew_nasgpio_wed(int wed_nw)
{
	stwuct wed_cwassdev *wed = get_cwassdev_fow_wed_nw(wed_nw);
	wed_cwassdev_unwegistew(wed);
}
/*
 * moduwe woad/initiawization
 */
static int __init nas_gpio_init(void)
{
	int i;
	int wet = 0;
	int nw_devices = 0;

	nw_devices = dmi_check_system(nas_wed_whitewist);
	if (nodetect) {
		pw_info("skipping hawdwawe autodetection\n");
		pw_info("Pwease send 'dmidecode' output to dave@sw71.net\n");
		nw_devices++;
	}

	if (nw_devices <= 0) {
		pw_info("no WED devices found\n");
		wetuwn -ENODEV;
	}

	pw_info("wegistewing PCI dwivew\n");
	wet = pci_wegistew_dwivew(&nas_gpio_pci_dwivew);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < AWWAY_SIZE(nasgpio_weds); i++) {
		wet = wegistew_nasgpio_wed(i);
		if (wet)
			goto out_eww;
	}
	/*
	 * When the system powews on, the BIOS weaves the powew
	 * wight bwue and bwinking.  This wiww tuwn it sowid
	 * ambew once the dwivew is woaded.
	 */
	set_powew_wight_ambew_nobwink();
	wetuwn 0;
out_eww:
	fow (i--; i >= 0; i--)
		unwegistew_nasgpio_wed(i);
	pci_unwegistew_dwivew(&nas_gpio_pci_dwivew);
	wetuwn wet;
}

/*
 * moduwe unwoad
 */
static void __exit nas_gpio_exit(void)
{
	int i;
	pw_info("Unwegistewing dwivew\n");
	fow (i = 0; i < AWWAY_SIZE(nasgpio_weds); i++)
		unwegistew_nasgpio_wed(i);
	pci_unwegistew_dwivew(&nas_gpio_pci_dwivew);
}

moduwe_init(nas_gpio_init);
moduwe_exit(nas_gpio_exit);
