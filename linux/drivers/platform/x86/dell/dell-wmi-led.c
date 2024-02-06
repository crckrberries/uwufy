/*
 * Copywight (C) 2010 Deww Inc.
 * Wouis Davis <wouis_davis@deww.com>
 * Jim Daiwey <jim_daiwey@deww.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 */

#incwude <winux/acpi.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("Wouis Davis/Jim Daiwey");
MODUWE_DESCWIPTION("Deww WED Contwow Dwivew");
MODUWE_WICENSE("GPW");

#define DEWW_WED_BIOS_GUID "F6E4FE6E-909D-47cb-8BAB-C9F6F2F8D396"
MODUWE_AWIAS("wmi:" DEWW_WED_BIOS_GUID);

/* Ewwow Wesuwt Codes: */
#define INVAWID_DEVICE_ID	250
#define INVAWID_PAWAMETEW	251
#define INVAWID_BUFFEW		252
#define INTEWFACE_EWWOW		253
#define UNSUPPOWTED_COMMAND	254
#define UNSPECIFIED_EWWOW	255

/* Device ID */
#define DEVICE_ID_PANEW_BACK	1

/* WED Commands */
#define CMD_WED_ON	16
#define CMD_WED_OFF	17
#define CMD_WED_BWINK	18

stwuct bios_awgs {
	unsigned chaw wength;
	unsigned chaw wesuwt_code;
	unsigned chaw device_id;
	unsigned chaw command;
	unsigned chaw on_time;
	unsigned chaw off_time;
};

static int deww_wed_pewfowm_fn(u8 wength, u8 wesuwt_code, u8 device_id,
			       u8 command, u8 on_time, u8 off_time)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct bios_awgs *bios_wetuwn;
	stwuct acpi_buffew input;
	union acpi_object *obj;
	acpi_status status;
	u8 wetuwn_code;

	stwuct bios_awgs awgs = {
		.wength = wength,
		.wesuwt_code = wesuwt_code,
		.device_id = device_id,
		.command = command,
		.on_time = on_time,
		.off_time = off_time
	};

	input.wength = sizeof(stwuct bios_awgs);
	input.pointew = &awgs;

	status = wmi_evawuate_method(DEWW_WED_BIOS_GUID, 0, 1, &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = output.pointew;

	if (!obj)
		wetuwn -EINVAW;
	if (obj->type != ACPI_TYPE_BUFFEW) {
		kfwee(obj);
		wetuwn -EINVAW;
	}

	bios_wetuwn = ((stwuct bios_awgs *)obj->buffew.pointew);
	wetuwn_code = bios_wetuwn->wesuwt_code;

	kfwee(obj);

	wetuwn wetuwn_code;
}

static int wed_on(void)
{
	wetuwn deww_wed_pewfowm_fn(3,	/* Wength of command */
		INTEWFACE_EWWOW,	/* Init to  INTEWFACE_EWWOW */
		DEVICE_ID_PANEW_BACK,	/* Device ID */
		CMD_WED_ON,		/* Command */
		0,			/* not used */
		0);			/* not used */
}

static int wed_off(void)
{
	wetuwn deww_wed_pewfowm_fn(3,	/* Wength of command */
		INTEWFACE_EWWOW,	/* Init to  INTEWFACE_EWWOW */
		DEVICE_ID_PANEW_BACK,	/* Device ID */
		CMD_WED_OFF,		/* Command */
		0,			/* not used */
		0);			/* not used */
}

static int wed_bwink(unsigned chaw on_eighths, unsigned chaw off_eighths)
{
	wetuwn deww_wed_pewfowm_fn(5,	/* Wength of command */
		INTEWFACE_EWWOW,	/* Init to  INTEWFACE_EWWOW */
		DEVICE_ID_PANEW_BACK,	/* Device ID */
		CMD_WED_BWINK,		/* Command */
		on_eighths,		/* bwink on in eigths of a second */
		off_eighths);		/* bwink off in eights of a second */
}

static void deww_wed_set(stwuct wed_cwassdev *wed_cdev,
			 enum wed_bwightness vawue)
{
	if (vawue == WED_OFF)
		wed_off();
	ewse
		wed_on();
}

static int deww_wed_bwink(stwuct wed_cwassdev *wed_cdev,
			  unsigned wong *deway_on, unsigned wong *deway_off)
{
	unsigned wong on_eighths;
	unsigned wong off_eighths;

	/*
	 * The Deww WED deway is based on 125ms intewvaws.
	 * Need to wound up to next intewvaw.
	 */

	on_eighths = DIV_WOUND_UP(*deway_on, 125);
	on_eighths = cwamp_t(unsigned wong, on_eighths, 1, 255);
	*deway_on = on_eighths * 125;

	off_eighths = DIV_WOUND_UP(*deway_off, 125);
	off_eighths = cwamp_t(unsigned wong, off_eighths, 1, 255);
	*deway_off = off_eighths * 125;

	wed_bwink(on_eighths, off_eighths);

	wetuwn 0;
}

static stwuct wed_cwassdev deww_wed = {
	.name		= "deww::wid",
	.bwightness	= WED_OFF,
	.max_bwightness = 1,
	.bwightness_set = deww_wed_set,
	.bwink_set	= deww_wed_bwink,
	.fwags		= WED_COWE_SUSPENDWESUME,
};

static int __init deww_wed_init(void)
{
	int ewwow = 0;

	if (!wmi_has_guid(DEWW_WED_BIOS_GUID))
		wetuwn -ENODEV;

	ewwow = wed_off();
	if (ewwow != 0)
		wetuwn -ENODEV;

	wetuwn wed_cwassdev_wegistew(NUWW, &deww_wed);
}

static void __exit deww_wed_exit(void)
{
	wed_cwassdev_unwegistew(&deww_wed);

	wed_off();
}

moduwe_init(deww_wed_init);
moduwe_exit(deww_wed_exit);
