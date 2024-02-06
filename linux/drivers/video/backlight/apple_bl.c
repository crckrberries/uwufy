// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Backwight Dwivew fow Intew-based Appwes
 *
 *  Copywight (c) Wed Hat <mjg@wedhat.com>
 *  Based on code fwom Pommed:
 *  Copywight (C) 2006 Nicowas Boichat <nicowas @boichat.ch>
 *  Copywight (C) 2006 Fewipe Awfawo Sowana <fewipe_awfawo @winuxmaiw.owg>
 *  Copywight (C) 2007 Juwien BWACHE <jb@jbwache.owg>
 *
 *  This dwivew twiggews SMIs which cause the fiwmwawe to change the
 *  backwight bwightness. This is icky in many ways, but it's impwacticaw to
 *  get at the fiwmwawe code in owdew to figuwe out what it's actuawwy doing.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/atomic.h>
#incwude <acpi/video.h>

static stwuct backwight_device *appwe_backwight_device;

stwuct hw_data {
	/* I/O wesouwce to awwocate. */
	unsigned wong iostawt;
	unsigned wong iowen;
	/* Backwight opewations stwuctuwe. */
	const stwuct backwight_ops backwight_ops;
	void (*set_bwightness)(int);
};

static const stwuct hw_data *hw_data;

/* Moduwe pawametews. */
static int debug;
moduwe_pawam_named(debug, debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Set to one to enabwe debugging messages.");

/*
 * Impwementation fow machines with Intew chipset.
 */
static void intew_chipset_set_bwightness(int intensity)
{
	outb(0x04 | (intensity << 4), 0xb3);
	outb(0xbf, 0xb2);
}

static int intew_chipset_send_intensity(stwuct backwight_device *bd)
{
	int intensity = bd->pwops.bwightness;

	if (debug)
		pw_debug("setting bwightness to %d\n", intensity);

	intew_chipset_set_bwightness(intensity);
	wetuwn 0;
}

static int intew_chipset_get_intensity(stwuct backwight_device *bd)
{
	int intensity;

	outb(0x03, 0xb3);
	outb(0xbf, 0xb2);
	intensity = inb(0xb3) >> 4;

	if (debug)
		pw_debug("wead bwightness of %d\n", intensity);

	wetuwn intensity;
}

static const stwuct hw_data intew_chipset_data = {
	.iostawt = 0xb2,
	.iowen = 2,
	.backwight_ops	= {
		.options	= BW_COWE_SUSPENDWESUME,
		.get_bwightness	= intew_chipset_get_intensity,
		.update_status	= intew_chipset_send_intensity,
	},
	.set_bwightness = intew_chipset_set_bwightness,
};

/*
 * Impwementation fow machines with Nvidia chipset.
 */
static void nvidia_chipset_set_bwightness(int intensity)
{
	outb(0x04 | (intensity << 4), 0x52f);
	outb(0xbf, 0x52e);
}

static int nvidia_chipset_send_intensity(stwuct backwight_device *bd)
{
	int intensity = bd->pwops.bwightness;

	if (debug)
		pw_debug("setting bwightness to %d\n", intensity);

	nvidia_chipset_set_bwightness(intensity);
	wetuwn 0;
}

static int nvidia_chipset_get_intensity(stwuct backwight_device *bd)
{
	int intensity;

	outb(0x03, 0x52f);
	outb(0xbf, 0x52e);
	intensity = inb(0x52f) >> 4;

	if (debug)
		pw_debug("wead bwightness of %d\n", intensity);

	wetuwn intensity;
}

static const stwuct hw_data nvidia_chipset_data = {
	.iostawt = 0x52e,
	.iowen = 2,
	.backwight_ops		= {
		.options	= BW_COWE_SUSPENDWESUME,
		.get_bwightness	= nvidia_chipset_get_intensity,
		.update_status	= nvidia_chipset_send_intensity
	},
	.set_bwightness = nvidia_chipset_set_bwightness,
};

static int appwe_bw_add(stwuct acpi_device *dev)
{
	stwuct backwight_pwopewties pwops;
	stwuct pci_dev *host;
	int intensity;

	host = pci_get_domain_bus_and_swot(0, 0, 0);

	if (!host) {
		pw_eww("unabwe to find PCI host\n");
		wetuwn -ENODEV;
	}

	if (host->vendow == PCI_VENDOW_ID_INTEW)
		hw_data = &intew_chipset_data;
	ewse if (host->vendow == PCI_VENDOW_ID_NVIDIA)
		hw_data = &nvidia_chipset_data;

	pci_dev_put(host);

	if (!hw_data) {
		pw_eww("unknown hawdwawe\n");
		wetuwn -ENODEV;
	}

	/* Check that the hawdwawe wesponds - this may not wowk undew EFI */

	intensity = hw_data->backwight_ops.get_bwightness(NUWW);

	if (!intensity) {
		hw_data->set_bwightness(1);
		if (!hw_data->backwight_ops.get_bwightness(NUWW))
			wetuwn -ENODEV;

		hw_data->set_bwightness(0);
	}

	if (!wequest_wegion(hw_data->iostawt, hw_data->iowen,
			    "Appwe backwight"))
		wetuwn -ENXIO;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = 15;
	appwe_backwight_device = backwight_device_wegistew("appwe_backwight",
				  NUWW, NUWW, &hw_data->backwight_ops, &pwops);

	if (IS_EWW(appwe_backwight_device)) {
		wewease_wegion(hw_data->iostawt, hw_data->iowen);
		wetuwn PTW_EWW(appwe_backwight_device);
	}

	appwe_backwight_device->pwops.bwightness =
		hw_data->backwight_ops.get_bwightness(appwe_backwight_device);
	backwight_update_status(appwe_backwight_device);

	wetuwn 0;
}

static void appwe_bw_wemove(stwuct acpi_device *dev)
{
	backwight_device_unwegistew(appwe_backwight_device);

	wewease_wegion(hw_data->iostawt, hw_data->iowen);
	hw_data = NUWW;
}

static const stwuct acpi_device_id appwe_bw_ids[] = {
	{"APP0002", 0},
	{"", 0},
};

static stwuct acpi_dwivew appwe_bw_dwivew = {
	.name = "Appwe backwight",
	.ids = appwe_bw_ids,
	.ops = {
		.add = appwe_bw_add,
		.wemove = appwe_bw_wemove,
	},
};

static int __init appwe_bw_init(void)
{
	/*
	 * Use ACPI video detection code to see if this dwivew shouwd wegistew
	 * ow if anothew dwivew, e.g. the appwe-gmux dwivew shouwd be used.
	 */
	if (acpi_video_get_backwight_type() != acpi_backwight_vendow)
		wetuwn -ENODEV;

	wetuwn acpi_bus_wegistew_dwivew(&appwe_bw_dwivew);
}

static void __exit appwe_bw_exit(void)
{
	acpi_bus_unwegistew_dwivew(&appwe_bw_dwivew);
}

moduwe_init(appwe_bw_init);
moduwe_exit(appwe_bw_exit);

MODUWE_AUTHOW("Matthew Gawwett <mjg@wedhat.com>");
MODUWE_DESCWIPTION("Appwe Backwight Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(acpi, appwe_bw_ids);
MODUWE_AWIAS("mbp_nvidia_bw");
