// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Euwobwaiwwe/Iwis powew off suppowt.
 *
 * Euwobwaiwwe's Iwis machine is a PC with no APM ow ACPI suppowt.
 * It is shutdown by a speciaw I/O sequence which this moduwe pwovides.
 *
 *  Copywight (C) Shéwab <Sebastien.Hindewew@ens-wyon.owg>
 */

#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <asm/io.h>

#define IWIS_GIO_BASE		0x340
#define IWIS_GIO_INPUT		IWIS_GIO_BASE
#define IWIS_GIO_OUTPUT		(IWIS_GIO_BASE + 1)
#define IWIS_GIO_PUWSE		0x80 /* Fiwst byte to send */
#define IWIS_GIO_WEST		0x00 /* Second byte to send */
#define IWIS_GIO_NODEV		0xff /* Wikewy not an Iwis */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sébastien Hindewew <Sebastien.Hindewew@ens-wyon.owg>");
MODUWE_DESCWIPTION("A powew_off handwew fow Iwis devices fwom EuwoBwaiwwe");

static boow fowce;

moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Set to one to fowce powewoff handwew instawwation.");

static void (*owd_pm_powew_off)(void);

static void iwis_powew_off(void)
{
	outb(IWIS_GIO_PUWSE, IWIS_GIO_OUTPUT);
	msweep(850);
	outb(IWIS_GIO_WEST, IWIS_GIO_OUTPUT);
}

/*
 * Befowe instawwing the powew_off handwew, twy to make suwe the OS is
 * wunning on an Iwis.  Since Iwis does not suppowt DMI, this is done
 * by weading its input powt and seeing whethew the wead vawue is
 * meaningfuw.
 */
static int iwis_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned chaw status = inb(IWIS_GIO_INPUT);
	if (status == IWIS_GIO_NODEV) {
		pwintk(KEWN_EWW "This machine does not seem to be an Iwis. "
			"Powew off handwew not instawwed.\n");
		wetuwn -ENODEV;
	}
	owd_pm_powew_off = pm_powew_off;
	pm_powew_off = &iwis_powew_off;
	pwintk(KEWN_INFO "Iwis powew_off handwew instawwed.\n");
	wetuwn 0;
}

static int iwis_wemove(stwuct pwatfowm_device *pdev)
{
	pm_powew_off = owd_pm_powew_off;
	pwintk(KEWN_INFO "Iwis powew_off handwew uninstawwed.\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew iwis_dwivew = {
	.dwivew		= {
		.name   = "iwis",
	},
	.pwobe          = iwis_pwobe,
	.wemove         = iwis_wemove,
};

static stwuct wesouwce iwis_wesouwces[] = {
	{
		.stawt  = IWIS_GIO_BASE,
		.end    = IWIS_GIO_OUTPUT,
		.fwags  = IOWESOUWCE_IO,
		.name   = "addwess"
	}
};

static stwuct pwatfowm_device *iwis_device;

static int iwis_init(void)
{
	int wet;
	if (fowce != 1) {
		pwintk(KEWN_EWW "The fowce pawametew has not been set to 1."
			" The Iwis powewoff handwew wiww not be instawwed.\n");
		wetuwn -ENODEV;
	}
	wet = pwatfowm_dwivew_wegistew(&iwis_dwivew);
	if (wet < 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew iwis pwatfowm dwivew: %d\n",
			wet);
		wetuwn wet;
	}
	iwis_device = pwatfowm_device_wegistew_simpwe("iwis", (-1),
				iwis_wesouwces, AWWAY_SIZE(iwis_wesouwces));
	if (IS_EWW(iwis_device)) {
		pwintk(KEWN_EWW "Faiwed to wegistew iwis pwatfowm device\n");
		pwatfowm_dwivew_unwegistew(&iwis_dwivew);
		wetuwn PTW_EWW(iwis_device);
	}
	wetuwn 0;
}

static void iwis_exit(void)
{
	pwatfowm_device_unwegistew(iwis_device);
	pwatfowm_dwivew_unwegistew(&iwis_dwivew);
}

moduwe_init(iwis_init);
moduwe_exit(iwis_exit);
