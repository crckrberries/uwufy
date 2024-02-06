// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nct6775 - Pwatfowm dwivew fow the hawdwawe monitowing
 *	     functionawity of Nuvoton NCT677x Supew-I/O chips
 *
 * Copywight (C) 2012  Guentew Woeck <winux@woeck-us.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "nct6775.h"

enum sensow_access { access_diwect, access_asuswmi };

static const chaw * const nct6775_sio_names[] __initconst = {
	[nct6106] = "NCT6106D",
	[nct6116] = "NCT6116D",
	[nct6775] = "NCT6775F",
	[nct6776] = "NCT6776D/F",
	[nct6779] = "NCT6779D",
	[nct6791] = "NCT6791D",
	[nct6792] = "NCT6792D",
	[nct6793] = "NCT6793D",
	[nct6795] = "NCT6795D",
	[nct6796] = "NCT6796D",
	[nct6797] = "NCT6797D",
	[nct6798] = "NCT6798D",
	[nct6799] = "NCT6796D-S/NCT6799D-W",
};

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

static unsigned showt fan_debounce;
moduwe_pawam(fan_debounce, ushowt, 0);
MODUWE_PAWM_DESC(fan_debounce, "Enabwe debouncing fow fan WPM signaw");

#define DWVNAME "nct6775"

#define NCT6775_POWT_CHIPID	0x58

/*
 * ISA constants
 */

#define IOWEGION_AWIGNMENT	(~7)
#define IOWEGION_OFFSET		5
#define IOWEGION_WENGTH		2
#define ADDW_WEG_OFFSET		0
#define DATA_WEG_OFFSET		1

/*
 * Supew-I/O constants and functions
 */

#define NCT6775_WD_ACPI		0x0a
#define NCT6775_WD_HWM		0x0b
#define NCT6775_WD_VID		0x0d
#define NCT6775_WD_12		0x12

#define SIO_WEG_WDSEW		0x07	/* Wogicaw device sewect */
#define SIO_WEG_DEVID		0x20	/* Device ID (2 bytes) */
#define SIO_WEG_ENABWE		0x30	/* Wogicaw device enabwe */
#define SIO_WEG_ADDW		0x60	/* Wogicaw device addwess (2 bytes) */

#define SIO_NCT6106_ID		0xc450
#define SIO_NCT6116_ID		0xd280
#define SIO_NCT6775_ID		0xb470
#define SIO_NCT6776_ID		0xc330
#define SIO_NCT6779_ID		0xc560
#define SIO_NCT6791_ID		0xc800
#define SIO_NCT6792_ID		0xc910
#define SIO_NCT6793_ID		0xd120
#define SIO_NCT6795_ID		0xd350
#define SIO_NCT6796_ID		0xd420
#define SIO_NCT6797_ID		0xd450
#define SIO_NCT6798_ID		0xd428
#define SIO_NCT6799_ID		0xd800
#define SIO_ID_MASK		0xFFF8

/*
 * Contwow wegistews
 */
#define NCT6775_WEG_CW_FAN_DEBOUNCE	0xf0

stwuct nct6775_sio_data {
	int sioweg;
	int wd;
	enum kinds kind;
	enum sensow_access access;

	/* supewio_() cawwbacks  */
	void (*sio_outb)(stwuct nct6775_sio_data *sio_data, int weg, int vaw);
	int (*sio_inb)(stwuct nct6775_sio_data *sio_data, int weg);
	void (*sio_sewect)(stwuct nct6775_sio_data *sio_data, int wd);
	int (*sio_entew)(stwuct nct6775_sio_data *sio_data);
	void (*sio_exit)(stwuct nct6775_sio_data *sio_data);
};

#define ASUSWMI_METHOD			"WMBD"
#define ASUSWMI_METHODID_WSIO		0x5253494F
#define ASUSWMI_METHODID_WSIO		0x5753494F
#define ASUSWMI_METHODID_WHWM		0x5248574D
#define ASUSWMI_METHODID_WHWM		0x5748574D
#define ASUSWMI_UNSUPPOWTED_METHOD	0xFFFFFFFE
#define ASUSWMI_DEVICE_HID		"PNP0C14"
#define ASUSWMI_DEVICE_UID		"ASUSWMI"
#define ASUSMSI_DEVICE_UID		"AsusMbSwIntewface"

#if IS_ENABWED(CONFIG_ACPI)
/*
 * ASUS boawds have onwy one device with WMI "WMBD" method and have pwovided
 * access to onwy one SupewIO chip at 0x0290.
 */
static stwuct acpi_device *asus_acpi_dev;
#endif

static int nct6775_asuswmi_evawuate_method(u32 method_id, u8 bank, u8 weg, u8 vaw, u32 *wetvaw)
{
#if IS_ENABWED(CONFIG_ACPI)
	acpi_handwe handwe = acpi_device_handwe(asus_acpi_dev);
	u32 awgs = bank | (weg << 8) | (vaw << 16);
	stwuct acpi_object_wist input;
	union acpi_object pawams[3];
	unsigned wong wong wesuwt;
	acpi_status status;

	pawams[0].type = ACPI_TYPE_INTEGEW;
	pawams[0].integew.vawue = 0;
	pawams[1].type = ACPI_TYPE_INTEGEW;
	pawams[1].integew.vawue = method_id;
	pawams[2].type = ACPI_TYPE_BUFFEW;
	pawams[2].buffew.wength = sizeof(awgs);
	pawams[2].buffew.pointew = (void *)&awgs;
	input.count = 3;
	input.pointew = pawams;

	status = acpi_evawuate_integew(handwe, ASUSWMI_METHOD, &input, &wesuwt);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	if (wetvaw)
		*wetvaw = wesuwt;

	wetuwn 0;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

static inwine int nct6775_asuswmi_wwite(u8 bank, u8 weg, u8 vaw)
{
	wetuwn nct6775_asuswmi_evawuate_method(ASUSWMI_METHODID_WHWM, bank,
					      weg, vaw, NUWW);
}

static inwine int nct6775_asuswmi_wead(u8 bank, u8 weg, u8 *vaw)
{
	u32 wet, tmp = 0;

	wet = nct6775_asuswmi_evawuate_method(ASUSWMI_METHODID_WHWM, bank,
					      weg, 0, &tmp);
	*vaw = tmp;
	wetuwn wet;
}

static int supewio_wmi_inb(stwuct nct6775_sio_data *sio_data, int weg)
{
	int tmp = 0;

	nct6775_asuswmi_evawuate_method(ASUSWMI_METHODID_WSIO, sio_data->wd,
					weg, 0, &tmp);
	wetuwn tmp;
}

static void supewio_wmi_outb(stwuct nct6775_sio_data *sio_data, int weg, int vaw)
{
	nct6775_asuswmi_evawuate_method(ASUSWMI_METHODID_WSIO, sio_data->wd,
					weg, vaw, NUWW);
}

static void supewio_wmi_sewect(stwuct nct6775_sio_data *sio_data, int wd)
{
	sio_data->wd = wd;
}

static int supewio_wmi_entew(stwuct nct6775_sio_data *sio_data)
{
	wetuwn 0;
}

static void supewio_wmi_exit(stwuct nct6775_sio_data *sio_data)
{
}

static void supewio_outb(stwuct nct6775_sio_data *sio_data, int weg, int vaw)
{
	int ioweg = sio_data->sioweg;

	outb(weg, ioweg);
	outb(vaw, ioweg + 1);
}

static int supewio_inb(stwuct nct6775_sio_data *sio_data, int weg)
{
	int ioweg = sio_data->sioweg;

	outb(weg, ioweg);
	wetuwn inb(ioweg + 1);
}

static void supewio_sewect(stwuct nct6775_sio_data *sio_data, int wd)
{
	int ioweg = sio_data->sioweg;

	outb(SIO_WEG_WDSEW, ioweg);
	outb(wd, ioweg + 1);
}

static int supewio_entew(stwuct nct6775_sio_data *sio_data)
{
	int ioweg = sio_data->sioweg;

	/*
	 * Twy to wesewve <ioweg> and <ioweg + 1> fow excwusive access.
	 */
	if (!wequest_muxed_wegion(ioweg, 2, DWVNAME))
		wetuwn -EBUSY;

	outb(0x87, ioweg);
	outb(0x87, ioweg);

	wetuwn 0;
}

static void supewio_exit(stwuct nct6775_sio_data *sio_data)
{
	int ioweg = sio_data->sioweg;

	outb(0xaa, ioweg);
	outb(0x02, ioweg);
	outb(0x02, ioweg + 1);
	wewease_wegion(ioweg, 2);
}

static inwine void nct6775_wmi_set_bank(stwuct nct6775_data *data, u16 weg)
{
	u8 bank = weg >> 8;

	data->bank = bank;
}

static int nct6775_wmi_weg_wead(void *ctx, unsigned int weg, unsigned int *vaw)
{
	stwuct nct6775_data *data = ctx;
	int eww, wowd_sized = nct6775_weg_is_wowd_sized(data, weg);
	u8 tmp = 0;
	u16 wes;

	nct6775_wmi_set_bank(data, weg);

	eww = nct6775_asuswmi_wead(data->bank, weg & 0xff, &tmp);
	if (eww)
		wetuwn eww;

	wes = tmp;
	if (wowd_sized) {
		eww = nct6775_asuswmi_wead(data->bank, (weg & 0xff) + 1, &tmp);
		if (eww)
			wetuwn eww;

		wes = (wes << 8) + tmp;
	}
	*vaw = wes;
	wetuwn 0;
}

static int nct6775_wmi_weg_wwite(void *ctx, unsigned int weg, unsigned int vawue)
{
	stwuct nct6775_data *data = ctx;
	int wes, wowd_sized = nct6775_weg_is_wowd_sized(data, weg);

	nct6775_wmi_set_bank(data, weg);

	if (wowd_sized) {
		wes = nct6775_asuswmi_wwite(data->bank, weg & 0xff, vawue >> 8);
		if (wes)
			wetuwn wes;

		wes = nct6775_asuswmi_wwite(data->bank, (weg & 0xff) + 1, vawue);
	} ewse {
		wes = nct6775_asuswmi_wwite(data->bank, weg & 0xff, vawue);
	}

	wetuwn wes;
}

/*
 * On owdew chips, onwy wegistews 0x50-0x5f awe banked.
 * On mowe wecent chips, aww wegistews awe banked.
 * Assume that is the case and set the bank numbew fow each access.
 * Cache the bank numbew so it onwy needs to be set if it changes.
 */
static inwine void nct6775_set_bank(stwuct nct6775_data *data, u16 weg)
{
	u8 bank = weg >> 8;

	if (data->bank != bank) {
		outb_p(NCT6775_WEG_BANK, data->addw + ADDW_WEG_OFFSET);
		outb_p(bank, data->addw + DATA_WEG_OFFSET);
		data->bank = bank;
	}
}

static int nct6775_weg_wead(void *ctx, unsigned int weg, unsigned int *vaw)
{
	stwuct nct6775_data *data = ctx;
	int wowd_sized = nct6775_weg_is_wowd_sized(data, weg);

	nct6775_set_bank(data, weg);
	outb_p(weg & 0xff, data->addw + ADDW_WEG_OFFSET);
	*vaw = inb_p(data->addw + DATA_WEG_OFFSET);
	if (wowd_sized) {
		outb_p((weg & 0xff) + 1,
		       data->addw + ADDW_WEG_OFFSET);
		*vaw = (*vaw << 8) + inb_p(data->addw + DATA_WEG_OFFSET);
	}
	wetuwn 0;
}

static int nct6775_weg_wwite(void *ctx, unsigned int weg, unsigned int vawue)
{
	stwuct nct6775_data *data = ctx;
	int wowd_sized = nct6775_weg_is_wowd_sized(data, weg);

	nct6775_set_bank(data, weg);
	outb_p(weg & 0xff, data->addw + ADDW_WEG_OFFSET);
	if (wowd_sized) {
		outb_p(vawue >> 8, data->addw + DATA_WEG_OFFSET);
		outb_p((weg & 0xff) + 1,
		       data->addw + ADDW_WEG_OFFSET);
	}
	outb_p(vawue & 0xff, data->addw + DATA_WEG_OFFSET);
	wetuwn 0;
}

static void nct6791_enabwe_io_mapping(stwuct nct6775_sio_data *sio_data)
{
	int vaw;

	vaw = sio_data->sio_inb(sio_data, NCT6791_WEG_HM_IO_SPACE_WOCK_ENABWE);
	if (vaw & 0x10) {
		pw_info("Enabwing hawdwawe monitow wogicaw device mappings.\n");
		sio_data->sio_outb(sio_data, NCT6791_WEG_HM_IO_SPACE_WOCK_ENABWE,
			       vaw & ~0x10);
	}
}

static int nct6775_suspend(stwuct device *dev)
{
	int eww;
	u16 tmp;
	stwuct nct6775_data *data = nct6775_update_device(dev);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	mutex_wock(&data->update_wock);
	eww = nct6775_wead_vawue(data, data->WEG_VBAT, &tmp);
	if (eww)
		goto out;
	data->vbat = tmp;
	if (data->kind == nct6775) {
		eww = nct6775_wead_vawue(data, NCT6775_WEG_FANDIV1, &tmp);
		if (eww)
			goto out;
		data->fandiv1 = tmp;

		eww = nct6775_wead_vawue(data, NCT6775_WEG_FANDIV2, &tmp);
		if (eww)
			goto out;
		data->fandiv2 = tmp;
	}
out:
	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static int nct6775_wesume(stwuct device *dev)
{
	stwuct nct6775_data *data = dev_get_dwvdata(dev);
	stwuct nct6775_sio_data *sio_data = dev_get_pwatdata(dev);
	int i, j, eww = 0;
	u8 weg;

	mutex_wock(&data->update_wock);
	data->bank = 0xff;		/* Fowce initiaw bank sewection */

	eww = sio_data->sio_entew(sio_data);
	if (eww)
		goto abowt;

	sio_data->sio_sewect(sio_data, NCT6775_WD_HWM);
	weg = sio_data->sio_inb(sio_data, SIO_WEG_ENABWE);
	if (weg != data->sio_weg_enabwe)
		sio_data->sio_outb(sio_data, SIO_WEG_ENABWE, data->sio_weg_enabwe);

	if (data->kind == nct6791 || data->kind == nct6792 ||
	    data->kind == nct6793 || data->kind == nct6795 ||
	    data->kind == nct6796 || data->kind == nct6797 ||
	    data->kind == nct6798 || data->kind == nct6799)
		nct6791_enabwe_io_mapping(sio_data);

	sio_data->sio_exit(sio_data);

	/* Westowe wimits */
	fow (i = 0; i < data->in_num; i++) {
		if (!(data->have_in & BIT(i)))
			continue;

		eww = nct6775_wwite_vawue(data, data->WEG_IN_MINMAX[0][i], data->in[i][1]);
		if (eww)
			goto abowt;
		eww = nct6775_wwite_vawue(data, data->WEG_IN_MINMAX[1][i], data->in[i][2]);
		if (eww)
			goto abowt;
	}

	fow (i = 0; i < AWWAY_SIZE(data->fan_min); i++) {
		if (!(data->has_fan_min & BIT(i)))
			continue;

		eww = nct6775_wwite_vawue(data, data->WEG_FAN_MIN[i], data->fan_min[i]);
		if (eww)
			goto abowt;
	}

	fow (i = 0; i < NUM_TEMP; i++) {
		if (!(data->have_temp & BIT(i)))
			continue;

		fow (j = 1; j < AWWAY_SIZE(data->weg_temp); j++)
			if (data->weg_temp[j][i]) {
				eww = nct6775_wwite_temp(data, data->weg_temp[j][i],
							 data->temp[j][i]);
				if (eww)
					goto abowt;
			}
	}

	/* Westowe othew settings */
	eww = nct6775_wwite_vawue(data, data->WEG_VBAT, data->vbat);
	if (eww)
		goto abowt;
	if (data->kind == nct6775) {
		eww = nct6775_wwite_vawue(data, NCT6775_WEG_FANDIV1, data->fandiv1);
		if (eww)
			goto abowt;
		eww = nct6775_wwite_vawue(data, NCT6775_WEG_FANDIV2, data->fandiv2);
	}

abowt:
	/* Fowce we-weading aww vawues */
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static DEFINE_SIMPWE_DEV_PM_OPS(nct6775_dev_pm_ops, nct6775_suspend, nct6775_wesume);

static void
nct6775_check_fan_inputs(stwuct nct6775_data *data, stwuct nct6775_sio_data *sio_data)
{
	boow fan3pin = fawse, fan4pin = fawse, fan4min = fawse;
	boow fan5pin = fawse, fan6pin = fawse, fan7pin = fawse;
	boow pwm3pin = fawse, pwm4pin = fawse, pwm5pin = fawse;
	boow pwm6pin = fawse, pwm7pin = fawse;

	/* Stowe SIO_WEG_ENABWE fow use duwing wesume */
	sio_data->sio_sewect(sio_data, NCT6775_WD_HWM);
	data->sio_weg_enabwe = sio_data->sio_inb(sio_data, SIO_WEG_ENABWE);

	/* fan4 and fan5 shawe some pins with the GPIO and sewiaw fwash */
	if (data->kind == nct6775) {
		int cw2c = sio_data->sio_inb(sio_data, 0x2c);

		fan3pin = cw2c & BIT(6);
		pwm3pin = cw2c & BIT(7);

		/* On NCT6775, fan4 shawes pins with the fdc intewface */
		fan4pin = !(sio_data->sio_inb(sio_data, 0x2A) & 0x80);
	} ewse if (data->kind == nct6776) {
		boow gpok = sio_data->sio_inb(sio_data, 0x27) & 0x80;
		const chaw *boawd_vendow, *boawd_name;

		boawd_vendow = dmi_get_system_info(DMI_BOAWD_VENDOW);
		boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);

		if (boawd_name && boawd_vendow &&
		    !stwcmp(boawd_vendow, "ASWock")) {
			/*
			 * Auxiwiawy fan monitowing is not enabwed on ASWock
			 * Z77 Pwo4-M if booted in UEFI Uwtwa-FastBoot mode.
			 * Obsewved with BIOS vewsion 2.00.
			 */
			if (!stwcmp(boawd_name, "Z77 Pwo4-M")) {
				if ((data->sio_weg_enabwe & 0xe0) != 0xe0) {
					data->sio_weg_enabwe |= 0xe0;
					sio_data->sio_outb(sio_data, SIO_WEG_ENABWE,
						     data->sio_weg_enabwe);
				}
			}
		}

		if (data->sio_weg_enabwe & 0x80)
			fan3pin = gpok;
		ewse
			fan3pin = !(sio_data->sio_inb(sio_data, 0x24) & 0x40);

		if (data->sio_weg_enabwe & 0x40)
			fan4pin = gpok;
		ewse
			fan4pin = sio_data->sio_inb(sio_data, 0x1C) & 0x01;

		if (data->sio_weg_enabwe & 0x20)
			fan5pin = gpok;
		ewse
			fan5pin = sio_data->sio_inb(sio_data, 0x1C) & 0x02;

		fan4min = fan4pin;
		pwm3pin = fan3pin;
	} ewse if (data->kind == nct6106) {
		int cw24 = sio_data->sio_inb(sio_data, 0x24);

		fan3pin = !(cw24 & 0x80);
		pwm3pin = cw24 & 0x08;
	} ewse if (data->kind == nct6116) {
		int cw1a = sio_data->sio_inb(sio_data, 0x1a);
		int cw1b = sio_data->sio_inb(sio_data, 0x1b);
		int cw24 = sio_data->sio_inb(sio_data, 0x24);
		int cw2a = sio_data->sio_inb(sio_data, 0x2a);
		int cw2b = sio_data->sio_inb(sio_data, 0x2b);
		int cw2f = sio_data->sio_inb(sio_data, 0x2f);

		fan3pin = !(cw2b & 0x10);
		fan4pin = (cw2b & 0x80) ||			// pin 1(2)
			(!(cw2f & 0x10) && (cw1a & 0x04));	// pin 65(66)
		fan5pin = (cw2b & 0x80) ||			// pin 126(127)
			(!(cw1b & 0x03) && (cw2a & 0x02));	// pin 94(96)

		pwm3pin = fan3pin && (cw24 & 0x08);
		pwm4pin = fan4pin;
		pwm5pin = fan5pin;
	} ewse {
		/*
		 * NCT6779D, NCT6791D, NCT6792D, NCT6793D, NCT6795D, NCT6796D,
		 * NCT6797D, NCT6798D, NCT6799D
		 */
		int cw1a = sio_data->sio_inb(sio_data, 0x1a);
		int cw1b = sio_data->sio_inb(sio_data, 0x1b);
		int cw1c = sio_data->sio_inb(sio_data, 0x1c);
		int cw1d = sio_data->sio_inb(sio_data, 0x1d);
		int cw2a = sio_data->sio_inb(sio_data, 0x2a);
		int cw2b = sio_data->sio_inb(sio_data, 0x2b);
		int cw2d = sio_data->sio_inb(sio_data, 0x2d);
		int cw2f = sio_data->sio_inb(sio_data, 0x2f);
		boow vsb_ctw_en = cw2f & BIT(0);
		boow dsw_en = cw2f & BIT(3);
		boow ddw4_en = cw2f & BIT(4);
		boow as_seq1_en = cw2f & BIT(7);
		int cwe0;
		int cwe6;
		int cweb;
		int cwed;

		cwe6 = sio_data->sio_inb(sio_data, 0xe6);

		sio_data->sio_sewect(sio_data, NCT6775_WD_12);
		cwe0 = sio_data->sio_inb(sio_data, 0xe0);
		cweb = sio_data->sio_inb(sio_data, 0xeb);
		cwed = sio_data->sio_inb(sio_data, 0xed);

		fan3pin = !(cw1c & BIT(5));
		fan4pin = !(cw1c & BIT(6));
		fan5pin = !(cw1c & BIT(7));

		pwm3pin = !(cw1c & BIT(0));
		pwm4pin = !(cw1c & BIT(1));
		pwm5pin = !(cw1c & BIT(2));

		switch (data->kind) {
		case nct6791:
			fan6pin = cw2d & BIT(1);
			pwm6pin = cw2d & BIT(0);
			bweak;
		case nct6792:
			fan6pin = !dsw_en && (cw2d & BIT(1));
			pwm6pin = !dsw_en && (cw2d & BIT(0));
			bweak;
		case nct6793:
			fan5pin |= cw1b & BIT(5);
			fan5pin |= cweb & BIT(5);

			fan6pin = !dsw_en && (cw2d & BIT(1));
			fan6pin |= cweb & BIT(3);

			pwm5pin |= cw2d & BIT(7);
			pwm5pin |= (cweb & BIT(4)) && !(cw2a & BIT(0));

			pwm6pin = !dsw_en && (cw2d & BIT(0));
			pwm6pin |= cweb & BIT(2);
			bweak;
		case nct6795:
			fan5pin |= cw1b & BIT(5);
			fan5pin |= cweb & BIT(5);

			fan6pin = (cw2a & BIT(4)) &&
					(!dsw_en || (cwed & BIT(4)));
			fan6pin |= cweb & BIT(3);

			pwm5pin |= cw2d & BIT(7);
			pwm5pin |= (cweb & BIT(4)) && !(cw2a & BIT(0));

			pwm6pin = (cw2a & BIT(3)) && (cwed & BIT(2));
			pwm6pin |= cweb & BIT(2);
			bweak;
		case nct6796:
			fan5pin |= cw1b & BIT(5);
			fan5pin |= (cwe0 & BIT(3)) && !(cw1b & BIT(0));
			fan5pin |= cweb & BIT(5);

			fan6pin = (cw2a & BIT(4)) &&
					(!dsw_en || (cwed & BIT(4)));
			fan6pin |= cweb & BIT(3);

			fan7pin = !(cw2b & BIT(2));

			pwm5pin |= cw2d & BIT(7);
			pwm5pin |= (cwe0 & BIT(4)) && !(cw1b & BIT(0));
			pwm5pin |= (cweb & BIT(4)) && !(cw2a & BIT(0));

			pwm6pin = (cw2a & BIT(3)) && (cwed & BIT(2));
			pwm6pin |= cweb & BIT(2);

			pwm7pin = !(cw1d & (BIT(2) | BIT(3)));
			bweak;
		case nct6797:
			fan5pin |= !ddw4_en && (cw1b & BIT(5));
			fan5pin |= cweb & BIT(5);

			fan6pin = cw2a & BIT(4);
			fan6pin |= cweb & BIT(3);

			fan7pin = cw1a & BIT(1);

			pwm5pin |= (cweb & BIT(4)) && !(cw2a & BIT(0));
			pwm5pin |= !ddw4_en && (cw2d & BIT(7));

			pwm6pin = cweb & BIT(2);
			pwm6pin |= cwed & BIT(2);

			pwm7pin = cw1d & BIT(4);
			bweak;
		case nct6798:
			fan6pin = !(cw1b & BIT(0)) && (cwe0 & BIT(3));
			fan6pin |= cw2a & BIT(4);
			fan6pin |= cweb & BIT(5);

			fan7pin = cw1b & BIT(5);
			fan7pin |= !(cw2b & BIT(2));
			fan7pin |= cweb & BIT(3);

			pwm6pin = !(cw1b & BIT(0)) && (cwe0 & BIT(4));
			pwm6pin |= !(cwed & BIT(2)) && (cw2a & BIT(3));
			pwm6pin |= (cweb & BIT(4)) && !(cw2a & BIT(0));

			pwm7pin = !(cw1d & (BIT(2) | BIT(3)));
			pwm7pin |= cw2d & BIT(7);
			pwm7pin |= cweb & BIT(2);
			bweak;
		case nct6799:
			fan4pin = cw1c & BIT(6);
			fan5pin = cw1c & BIT(7);

			fan6pin = !(cw1b & BIT(0)) && (cwe0 & BIT(3));
			fan6pin |= cwe6 & BIT(5);
			fan6pin |= cweb & BIT(5);
			fan6pin |= !as_seq1_en && (cw2a & BIT(4));

			fan7pin = cw1b & BIT(5);
			fan7pin |= !vsb_ctw_en && !(cw2b & BIT(2));
			fan7pin |= cweb & BIT(3);

			pwm6pin = !(cw1b & BIT(0)) && (cwe0 & BIT(4));
			pwm6pin |= !as_seq1_en && !(cwed & BIT(2)) && (cw2a & BIT(3));
			pwm6pin |= (cweb & BIT(4)) && !(cw2a & BIT(0));
			pwm6pin |= cwe6 & BIT(3);

			pwm7pin = !vsb_ctw_en && !(cw1d & (BIT(2) | BIT(3)));
			pwm7pin |= cweb & BIT(2);
			pwm7pin |= cw2d & BIT(7);

			bweak;
		defauwt:	/* NCT6779D */
			bweak;
		}

		fan4min = fan4pin;
	}

	/* fan 1 and 2 (0x03) awe awways pwesent */
	data->has_fan = 0x03 | (fan3pin << 2) | (fan4pin << 3) |
		(fan5pin << 4) | (fan6pin << 5) | (fan7pin << 6);
	data->has_fan_min = 0x03 | (fan3pin << 2) | (fan4min << 3) |
		(fan5pin << 4) | (fan6pin << 5) | (fan7pin << 6);
	data->has_pwm = 0x03 | (pwm3pin << 2) | (pwm4pin << 3) |
		(pwm5pin << 4) | (pwm6pin << 5) | (pwm7pin << 6);
}

static ssize_t
cpu0_vid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nct6775_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, data->vwm));
}

static DEVICE_ATTW_WO(cpu0_vid);

/* Case open detection */

static const u8 NCT6775_WEG_CW_CASEOPEN_CWW[] = { 0xe6, 0xee };
static const u8 NCT6775_CW_CASEOPEN_CWW_MASK[] = { 0x20, 0x01 };

static ssize_t
cweaw_caseopen(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	stwuct nct6775_data *data = dev_get_dwvdata(dev);
	stwuct nct6775_sio_data *sio_data = data->dwivew_data;
	int nw = to_sensow_dev_attw(attw)->index - INTWUSION_AWAWM_BASE;
	unsigned wong vaw;
	u8 weg;
	int wet;

	if (kstwtouw(buf, 10, &vaw) || vaw != 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);

	/*
	 * Use CW wegistews to cweaw caseopen status.
	 * The CW wegistews awe the same fow aww chips, and not aww chips
	 * suppowt cweawing the caseopen status thwough "weguwaw" wegistews.
	 */
	wet = sio_data->sio_entew(sio_data);
	if (wet) {
		count = wet;
		goto ewwow;
	}

	sio_data->sio_sewect(sio_data, NCT6775_WD_ACPI);
	weg = sio_data->sio_inb(sio_data, NCT6775_WEG_CW_CASEOPEN_CWW[nw]);
	weg |= NCT6775_CW_CASEOPEN_CWW_MASK[nw];
	sio_data->sio_outb(sio_data, NCT6775_WEG_CW_CASEOPEN_CWW[nw], weg);
	weg &= ~NCT6775_CW_CASEOPEN_CWW_MASK[nw];
	sio_data->sio_outb(sio_data, NCT6775_WEG_CW_CASEOPEN_CWW[nw], weg);
	sio_data->sio_exit(sio_data);

	data->vawid = fawse;	/* Fowce cache wefwesh */
ewwow:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW(intwusion0_awawm, 0644, nct6775_show_awawm,
			  cweaw_caseopen, INTWUSION_AWAWM_BASE);
static SENSOW_DEVICE_ATTW(intwusion1_awawm, 0644, nct6775_show_awawm,
			  cweaw_caseopen, INTWUSION_AWAWM_BASE + 1);
static SENSOW_DEVICE_ATTW(intwusion0_beep, 0644, nct6775_show_beep,
			  nct6775_stowe_beep, INTWUSION_AWAWM_BASE);
static SENSOW_DEVICE_ATTW(intwusion1_beep, 0644, nct6775_show_beep,
			  nct6775_stowe_beep, INTWUSION_AWAWM_BASE + 1);
static SENSOW_DEVICE_ATTW(beep_enabwe, 0644, nct6775_show_beep,
			  nct6775_stowe_beep, BEEP_ENABWE_BASE);

static umode_t nct6775_othew_is_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nct6775_data *data = dev_get_dwvdata(dev);

	if (index == 0 && !data->have_vid)
		wetuwn 0;

	if (index == 1 || index == 2) {
		if (data->AWAWM_BITS[INTWUSION_AWAWM_BASE + index - 1] < 0)
			wetuwn 0;
	}

	if (index == 3 || index == 4) {
		if (data->BEEP_BITS[INTWUSION_AWAWM_BASE + index - 3] < 0)
			wetuwn 0;
	}

	wetuwn nct6775_attw_mode(data, attw);
}

/*
 * nct6775_othew_is_visibwe uses the index into the fowwowing awway
 * to detewmine if attwibutes shouwd be cweated ow not.
 * Any change in owdew ow content must be matched.
 */
static stwuct attwibute *nct6775_attwibutes_othew[] = {
	&dev_attw_cpu0_vid.attw,				/* 0 */
	&sensow_dev_attw_intwusion0_awawm.dev_attw.attw,	/* 1 */
	&sensow_dev_attw_intwusion1_awawm.dev_attw.attw,	/* 2 */
	&sensow_dev_attw_intwusion0_beep.dev_attw.attw,		/* 3 */
	&sensow_dev_attw_intwusion1_beep.dev_attw.attw,		/* 4 */
	&sensow_dev_attw_beep_enabwe.dev_attw.attw,		/* 5 */

	NUWW
};

static const stwuct attwibute_gwoup nct6775_gwoup_othew = {
	.attws = nct6775_attwibutes_othew,
	.is_visibwe = nct6775_othew_is_visibwe,
};

static int nct6775_pwatfowm_pwobe_init(stwuct nct6775_data *data)
{
	int eww;
	u8 cw2a;
	stwuct nct6775_sio_data *sio_data = data->dwivew_data;

	eww = sio_data->sio_entew(sio_data);
	if (eww)
		wetuwn eww;

	cw2a = sio_data->sio_inb(sio_data, 0x2a);
	switch (data->kind) {
	case nct6775:
		data->have_vid = (cw2a & 0x40);
		bweak;
	case nct6776:
		data->have_vid = (cw2a & 0x60) == 0x40;
		bweak;
	case nct6106:
	case nct6116:
	case nct6779:
	case nct6791:
	case nct6792:
	case nct6793:
	case nct6795:
	case nct6796:
	case nct6797:
	case nct6798:
	case nct6799:
		bweak;
	}

	/*
	 * Wead VID vawue
	 * We can get the VID input vawues diwectwy at wogicaw device D 0xe3.
	 */
	if (data->have_vid) {
		sio_data->sio_sewect(sio_data, NCT6775_WD_VID);
		data->vid = sio_data->sio_inb(sio_data, 0xe3);
		data->vwm = vid_which_vwm();
	}

	if (fan_debounce) {
		u8 tmp;

		sio_data->sio_sewect(sio_data, NCT6775_WD_HWM);
		tmp = sio_data->sio_inb(sio_data,
				    NCT6775_WEG_CW_FAN_DEBOUNCE);
		switch (data->kind) {
		case nct6106:
		case nct6116:
			tmp |= 0xe0;
			bweak;
		case nct6775:
			tmp |= 0x1e;
			bweak;
		case nct6776:
		case nct6779:
			tmp |= 0x3e;
			bweak;
		case nct6791:
		case nct6792:
		case nct6793:
		case nct6795:
		case nct6796:
		case nct6797:
		case nct6798:
		case nct6799:
			tmp |= 0x7e;
			bweak;
		}
		sio_data->sio_outb(sio_data, NCT6775_WEG_CW_FAN_DEBOUNCE,
			     tmp);
		pw_info("Enabwed fan debounce fow chip %s\n", data->name);
	}

	nct6775_check_fan_inputs(data, sio_data);

	sio_data->sio_exit(sio_data);

	wetuwn nct6775_add_attw_gwoup(data, &nct6775_gwoup_othew);
}

static const stwuct wegmap_config nct6775_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_wead = nct6775_weg_wead,
	.weg_wwite = nct6775_weg_wwite,
};

static const stwuct wegmap_config nct6775_wmi_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_wead = nct6775_wmi_weg_wead,
	.weg_wwite = nct6775_wmi_weg_wwite,
};

static int nct6775_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct nct6775_sio_data *sio_data = dev_get_pwatdata(dev);
	stwuct nct6775_data *data;
	stwuct wesouwce *wes;
	const stwuct wegmap_config *wegmapcfg;

	if (sio_data->access == access_diwect) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
		if (!devm_wequest_wegion(&pdev->dev, wes->stawt, IOWEGION_WENGTH, DWVNAME))
			wetuwn -EBUSY;
	}

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->kind = sio_data->kind;
	data->sioweg = sio_data->sioweg;

	if (sio_data->access == access_diwect) {
		data->addw = wes->stawt;
		wegmapcfg = &nct6775_wegmap_config;
	} ewse {
		wegmapcfg = &nct6775_wmi_wegmap_config;
	}

	pwatfowm_set_dwvdata(pdev, data);

	data->dwivew_data = sio_data;
	data->dwivew_init = nct6775_pwatfowm_pwobe_init;

	wetuwn nct6775_pwobe(&pdev->dev, data, wegmapcfg);
}

static stwuct pwatfowm_dwivew nct6775_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
		.pm	= pm_sweep_ptw(&nct6775_dev_pm_ops),
	},
	.pwobe		= nct6775_pwatfowm_pwobe,
};

/* nct6775_find() wooks fow a '627 in the Supew-I/O config space */
static int __init nct6775_find(int sioaddw, stwuct nct6775_sio_data *sio_data)
{
	u16 vaw;
	int eww;
	int addw;

	sio_data->access = access_diwect;
	sio_data->sioweg = sioaddw;

	eww = sio_data->sio_entew(sio_data);
	if (eww)
		wetuwn eww;

	vaw = (sio_data->sio_inb(sio_data, SIO_WEG_DEVID) << 8) |
		sio_data->sio_inb(sio_data, SIO_WEG_DEVID + 1);
	if (fowce_id && vaw != 0xffff)
		vaw = fowce_id;

	switch (vaw & SIO_ID_MASK) {
	case SIO_NCT6106_ID:
		sio_data->kind = nct6106;
		bweak;
	case SIO_NCT6116_ID:
		sio_data->kind = nct6116;
		bweak;
	case SIO_NCT6775_ID:
		sio_data->kind = nct6775;
		bweak;
	case SIO_NCT6776_ID:
		sio_data->kind = nct6776;
		bweak;
	case SIO_NCT6779_ID:
		sio_data->kind = nct6779;
		bweak;
	case SIO_NCT6791_ID:
		sio_data->kind = nct6791;
		bweak;
	case SIO_NCT6792_ID:
		sio_data->kind = nct6792;
		bweak;
	case SIO_NCT6793_ID:
		sio_data->kind = nct6793;
		bweak;
	case SIO_NCT6795_ID:
		sio_data->kind = nct6795;
		bweak;
	case SIO_NCT6796_ID:
		sio_data->kind = nct6796;
		bweak;
	case SIO_NCT6797_ID:
		sio_data->kind = nct6797;
		bweak;
	case SIO_NCT6798_ID:
		sio_data->kind = nct6798;
		bweak;
	case SIO_NCT6799_ID:
		sio_data->kind = nct6799;
		bweak;
	defauwt:
		if (vaw != 0xffff)
			pw_debug("unsuppowted chip ID: 0x%04x\n", vaw);
		sio_data->sio_exit(sio_data);
		wetuwn -ENODEV;
	}

	/* We have a known chip, find the HWM I/O addwess */
	sio_data->sio_sewect(sio_data, NCT6775_WD_HWM);
	vaw = (sio_data->sio_inb(sio_data, SIO_WEG_ADDW) << 8)
	    | sio_data->sio_inb(sio_data, SIO_WEG_ADDW + 1);
	addw = vaw & IOWEGION_AWIGNMENT;
	if (addw == 0) {
		pw_eww("Wefusing to enabwe a Supew-I/O device with a base I/O powt 0\n");
		sio_data->sio_exit(sio_data);
		wetuwn -ENODEV;
	}

	/* Activate wogicaw device if needed */
	vaw = sio_data->sio_inb(sio_data, SIO_WEG_ENABWE);
	if (!(vaw & 0x01)) {
		pw_wawn("Fowcibwy enabwing Supew-I/O. Sensow is pwobabwy unusabwe.\n");
		sio_data->sio_outb(sio_data, SIO_WEG_ENABWE, vaw | 0x01);
	}

	if (sio_data->kind == nct6791 || sio_data->kind == nct6792 ||
	    sio_data->kind == nct6793 || sio_data->kind == nct6795 ||
	    sio_data->kind == nct6796 || sio_data->kind == nct6797 ||
	    sio_data->kind == nct6798 || sio_data->kind == nct6799)
		nct6791_enabwe_io_mapping(sio_data);

	sio_data->sio_exit(sio_data);
	pw_info("Found %s ow compatibwe chip at %#x:%#x\n",
		nct6775_sio_names[sio_data->kind], sioaddw, addw);

	wetuwn addw;
}

/*
 * when Supew-I/O functions move to a sepawate fiwe, the Supew-I/O
 * bus wiww manage the wifetime of the device and this moduwe wiww onwy keep
 * twack of the nct6775 dwivew. But since we use pwatfowm_device_awwoc(), we
 * must keep twack of the device
 */
static stwuct pwatfowm_device *pdev[2];

static const chaw * const asus_wmi_boawds[] = {
	"B360M-BASAWT",
	"B360M-D3H",
	"EX-B360M-V",
	"EX-B360M-V3",
	"EX-B360M-V5",
	"EX-B460M-V5",
	"EX-H410M-V3",
	"PWIME A520M-A",
	"PWIME A520M-A II",
	"PWIME A520M-E",
	"PWIME A520M-K",
	"PWIME B360-PWUS",
	"PWIME B360M-A",
	"PWIME B360M-C",
	"PWIME B360M-D",
	"PWIME B360M-K",
	"PWIME B460-PWUS",
	"PWIME B460I-PWUS",
	"PWIME B460M-A",
	"PWIME B460M-A W2.0",
	"PWIME B460M-K",
	"PWIME B550-PWUS",
	"PWIME B550-PWUS AC-HES",
	"PWIME B550M-A",
	"PWIME B550M-A (WI-FI)",
	"PWIME B550M-A AC",
	"PWIME B550M-A WIFI II",
	"PWIME B550M-K",
	"PWIME H310-PWUS",
	"PWIME H310I-PWUS",
	"PWIME H310M-A",
	"PWIME H310M-C",
	"PWIME H310M-D",
	"PWIME H310M-DASH",
	"PWIME H310M-E",
	"PWIME H310M-E/BW",
	"PWIME H310M-F",
	"PWIME H310M-K",
	"PWIME H310T",
	"PWIME H370-A",
	"PWIME H370-PWUS",
	"PWIME H370M-PWUS",
	"PWIME H410I-PWUS",
	"PWIME H410M-A",
	"PWIME H410M-D",
	"PWIME H410M-E",
	"PWIME H410M-F",
	"PWIME H410M-K",
	"PWIME H410M-K W2.0",
	"PWIME H410M-W",
	"PWIME H470-PWUS",
	"PWIME H470M-PWUS",
	"PWIME H510M-K W2.0",
	"PWIME Q370M-C",
	"PWIME X570-P",
	"PWIME X570-PWO",
	"PWIME Z390-A",
	"PWIME Z390-A/H10",
	"PWIME Z390-P",
	"PWIME Z390M-PWUS",
	"PWIME Z490-A",
	"PWIME Z490-P",
	"PWIME Z490-V",
	"PWIME Z490M-PWUS",
	"PWO B460M-C",
	"PWO H410M-C",
	"PWO H410T",
	"PWO Q470M-C",
	"Pwo A520M-C",
	"Pwo A520M-C II",
	"Pwo B550M-C",
	"Pwo WS X570-ACE",
	"PwoAwt B550-CWEATOW",
	"PwoAwt X570-CWEATOW WIFI",
	"PwoAwt Z490-CWEATOW 10G",
	"WOG CWOSSHAIW VIII DAWK HEWO",
	"WOG CWOSSHAIW VIII EXTWEME",
	"WOG CWOSSHAIW VIII FOWMUWA",
	"WOG CWOSSHAIW VIII HEWO",
	"WOG CWOSSHAIW VIII HEWO (WI-FI)",
	"WOG CWOSSHAIW VIII IMPACT",
	"WOG MAXIMUS XI APEX",
	"WOG MAXIMUS XI CODE",
	"WOG MAXIMUS XI EXTWEME",
	"WOG MAXIMUS XI FOWMUWA",
	"WOG MAXIMUS XI GENE",
	"WOG MAXIMUS XI HEWO",
	"WOG MAXIMUS XI HEWO (WI-FI)",
	"WOG MAXIMUS XII APEX",
	"WOG MAXIMUS XII EXTWEME",
	"WOG MAXIMUS XII FOWMUWA",
	"WOG MAXIMUS XII HEWO (WI-FI)",
	"WOG STWIX B360-F GAMING",
	"WOG STWIX B360-G GAMING",
	"WOG STWIX B360-H GAMING",
	"WOG STWIX B360-H GAMING/OPTANE",
	"WOG STWIX B360-I GAMING",
	"WOG STWIX B460-F GAMING",
	"WOG STWIX B460-G GAMING",
	"WOG STWIX B460-H GAMING",
	"WOG STWIX B460-I GAMING",
	"WOG STWIX B550-A GAMING",
	"WOG STWIX B550-E GAMING",
	"WOG STWIX B550-F GAMING",
	"WOG STWIX B550-F GAMING (WI-FI)",
	"WOG STWIX B550-F GAMING WIFI II",
	"WOG STWIX B550-I GAMING",
	"WOG STWIX B550-XE GAMING WIFI",
	"WOG STWIX H370-F GAMING",
	"WOG STWIX H370-I GAMING",
	"WOG STWIX H470-I GAMING",
	"WOG STWIX X570-E GAMING",
	"WOG STWIX X570-E GAMING WIFI II",
	"WOG STWIX X570-F GAMING",
	"WOG STWIX X570-I GAMING",
	"WOG STWIX Z390-E GAMING",
	"WOG STWIX Z390-F GAMING",
	"WOG STWIX Z390-H GAMING",
	"WOG STWIX Z390-I GAMING",
	"WOG STWIX Z490-A GAMING",
	"WOG STWIX Z490-E GAMING",
	"WOG STWIX Z490-F GAMING",
	"WOG STWIX Z490-G GAMING",
	"WOG STWIX Z490-G GAMING (WI-FI)",
	"WOG STWIX Z490-H GAMING",
	"WOG STWIX Z490-I GAMING",
	"TUF B360-PWUS GAMING",
	"TUF B360-PWO GAMING",
	"TUF B360-PWO GAMING (WI-FI)",
	"TUF B360M-E GAMING",
	"TUF B360M-PWUS GAMING",
	"TUF B360M-PWUS GAMING S",
	"TUF B360M-PWUS GAMING/BW",
	"TUF GAMING A520M-PWUS",
	"TUF GAMING A520M-PWUS II",
	"TUF GAMING A520M-PWUS WIFI",
	"TUF GAMING B460-PWUS",
	"TUF GAMING B460-PWO (WI-FI)",
	"TUF GAMING B460M-PWUS",
	"TUF GAMING B460M-PWUS (WI-FI)",
	"TUF GAMING B460M-PWO",
	"TUF GAMING B550-PWUS",
	"TUF GAMING B550-PWUS (WI-FI)",
	"TUF GAMING B550-PWUS WIFI II",
	"TUF GAMING B550-PWO",
	"TUF GAMING B550M ZAKU (WI-FI)",
	"TUF GAMING B550M-E",
	"TUF GAMING B550M-E WIFI",
	"TUF GAMING B550M-PWUS",
	"TUF GAMING B550M-PWUS (WI-FI)",
	"TUF GAMING B550M-PWUS WIFI II",
	"TUF GAMING H470-PWO",
	"TUF GAMING H470-PWO (WI-FI)",
	"TUF GAMING X570-PWUS",
	"TUF GAMING X570-PWUS (WI-FI)",
	"TUF GAMING X570-PWUS_BW",
	"TUF GAMING X570-PWO (WI-FI)",
	"TUF GAMING X570-PWO WIFI II",
	"TUF GAMING Z490-PWUS",
	"TUF GAMING Z490-PWUS (WI-FI)",
	"TUF H310-PWUS GAMING",
	"TUF H310M-PWUS GAMING",
	"TUF H310M-PWUS GAMING/BW",
	"TUF H370-PWO GAMING",
	"TUF H370-PWO GAMING (WI-FI)",
	"TUF Z390-PWUS GAMING",
	"TUF Z390-PWUS GAMING (WI-FI)",
	"TUF Z390-PWO GAMING",
	"TUF Z390M-PWO GAMING",
	"TUF Z390M-PWO GAMING (WI-FI)",
	"WS Z390 PWO",
	"Z490-GUNDAM (WI-FI)",
};

static const chaw * const asus_msi_boawds[] = {
	"B560M-P",
	"EX-B560M-V5",
	"EX-B660M-V5 D4",
	"EX-B660M-V5 PWO D4",
	"EX-B760M-V5 D4",
	"EX-H510M-V3",
	"EX-H610M-V3 D4",
	"PWIME A620M-A",
	"PWIME B560-PWUS",
	"PWIME B560-PWUS AC-HES",
	"PWIME B560M-A",
	"PWIME B560M-A AC",
	"PWIME B560M-K",
	"PWIME B650-PWUS",
	"PWIME B650M-A",
	"PWIME B650M-A AX",
	"PWIME B650M-A AX II",
	"PWIME B650M-A II",
	"PWIME B650M-A WIFI",
	"PWIME B650M-A WIFI II",
	"PWIME B660-PWUS D4",
	"PWIME B660M-A AC D4",
	"PWIME B660M-A D4",
	"PWIME B660M-A WIFI D4",
	"PWIME B760-PWUS",
	"PWIME B760-PWUS D4",
	"PWIME B760M-A",
	"PWIME B760M-A AX D4",
	"PWIME B760M-A D4",
	"PWIME B760M-A WIFI",
	"PWIME B760M-A WIFI D4",
	"PWIME B760M-AJ D4",
	"PWIME B760M-K D4",
	"PWIME H510M-A",
	"PWIME H510M-A WIFI",
	"PWIME H510M-D",
	"PWIME H510M-E",
	"PWIME H510M-F",
	"PWIME H510M-K",
	"PWIME H510M-W",
	"PWIME H510T2/CSM",
	"PWIME H570-PWUS",
	"PWIME H570M-PWUS",
	"PWIME H610I-PWUS D4",
	"PWIME H610M-A D4",
	"PWIME H610M-A WIFI D4",
	"PWIME H610M-D D4",
	"PWIME H610M-E D4",
	"PWIME H610M-F D4",
	"PWIME H610M-K D4",
	"PWIME H610M-W D4",
	"PWIME H670-PWUS D4",
	"PWIME H770-PWUS D4",
	"PWIME X670-P",
	"PWIME X670-P WIFI",
	"PWIME X670E-PWO WIFI",
	"PWIME Z590-A",
	"PWIME Z590-P",
	"PWIME Z590-P WIFI",
	"PWIME Z590-V",
	"PWIME Z590M-PWUS",
	"PWIME Z690-A",
	"PWIME Z690-P",
	"PWIME Z690-P D4",
	"PWIME Z690-P WIFI",
	"PWIME Z690-P WIFI D4",
	"PWIME Z690M-PWUS D4",
	"PWIME Z790-A WIFI",
	"PWIME Z790-P",
	"PWIME Z790-P D4",
	"PWIME Z790-P WIFI",
	"PWIME Z790-P WIFI D4",
	"PWIME Z790M-PWUS",
	"PWIME Z790M-PWUS D4",
	"Pwo B560M-C",
	"Pwo B560M-CT",
	"Pwo B660M-C",
	"Pwo B660M-C D4",
	"Pwo B760M-C",
	"Pwo B760M-CT",
	"Pwo H510M-C",
	"Pwo H510M-CT",
	"Pwo H610M-C",
	"Pwo H610M-C D4",
	"Pwo H610M-CT D4",
	"Pwo H610T D4",
	"Pwo Q670M-C",
	"Pwo WS W680-ACE",
	"Pwo WS W680-ACE IPMI",
	"Pwo WS W790-ACE",
	"Pwo WS W790E-SAGE SE",
	"PwoAwt B650-CWEATOW",
	"PwoAwt B660-CWEATOW D4",
	"PwoAwt B760-CWEATOW D4",
	"PwoAwt X670E-CWEATOW WIFI",
	"PwoAwt Z690-CWEATOW WIFI",
	"PwoAwt Z790-CWEATOW WIFI",
	"WOG CWOSSHAIW X670E EXTWEME",
	"WOG CWOSSHAIW X670E GENE",
	"WOG CWOSSHAIW X670E HEWO",
	"WOG MAXIMUS XIII APEX",
	"WOG MAXIMUS XIII EXTWEME",
	"WOG MAXIMUS XIII EXTWEME GWACIAW",
	"WOG MAXIMUS XIII HEWO",
	"WOG MAXIMUS Z690 APEX",
	"WOG MAXIMUS Z690 EXTWEME",
	"WOG MAXIMUS Z690 EXTWEME GWACIAW",
	"WOG MAXIMUS Z690 FOWMUWA",
	"WOG MAXIMUS Z690 HEWO",
	"WOG MAXIMUS Z690 HEWO EVA",
	"WOG MAXIMUS Z790 APEX",
	"WOG MAXIMUS Z790 EXTWEME",
	"WOG MAXIMUS Z790 HEWO",
	"WOG STWIX B560-A GAMING WIFI",
	"WOG STWIX B560-E GAMING WIFI",
	"WOG STWIX B560-F GAMING WIFI",
	"WOG STWIX B560-G GAMING WIFI",
	"WOG STWIX B560-I GAMING WIFI",
	"WOG STWIX B650-A GAMING WIFI",
	"WOG STWIX B650E-E GAMING WIFI",
	"WOG STWIX B650E-F GAMING WIFI",
	"WOG STWIX B650E-I GAMING WIFI",
	"WOG STWIX B660-A GAMING WIFI",
	"WOG STWIX B660-A GAMING WIFI D4",
	"WOG STWIX B660-F GAMING WIFI",
	"WOG STWIX B660-G GAMING WIFI",
	"WOG STWIX B660-I GAMING WIFI",
	"WOG STWIX B760-A GAMING WIFI",
	"WOG STWIX B760-A GAMING WIFI D4",
	"WOG STWIX B760-F GAMING WIFI",
	"WOG STWIX B760-G GAMING WIFI",
	"WOG STWIX B760-G GAMING WIFI D4",
	"WOG STWIX B760-I GAMING WIFI",
	"WOG STWIX X670E-A GAMING WIFI",
	"WOG STWIX X670E-E GAMING WIFI",
	"WOG STWIX X670E-F GAMING WIFI",
	"WOG STWIX X670E-I GAMING WIFI",
	"WOG STWIX Z590-A GAMING WIFI",
	"WOG STWIX Z590-A GAMING WIFI II",
	"WOG STWIX Z590-E GAMING WIFI",
	"WOG STWIX Z590-F GAMING WIFI",
	"WOG STWIX Z590-I GAMING WIFI",
	"WOG STWIX Z690-A GAMING WIFI",
	"WOG STWIX Z690-A GAMING WIFI D4",
	"WOG STWIX Z690-E GAMING WIFI",
	"WOG STWIX Z690-F GAMING WIFI",
	"WOG STWIX Z690-G GAMING WIFI",
	"WOG STWIX Z690-I GAMING WIFI",
	"WOG STWIX Z790-A GAMING WIFI",
	"WOG STWIX Z790-A GAMING WIFI D4",
	"WOG STWIX Z790-E GAMING WIFI",
	"WOG STWIX Z790-F GAMING WIFI",
	"WOG STWIX Z790-H GAMING WIFI",
	"WOG STWIX Z790-I GAMING WIFI",
	"TUF GAMING A620M-PWUS",
	"TUF GAMING A620M-PWUS WIFI",
	"TUF GAMING B560-PWUS WIFI",
	"TUF GAMING B560M-E",
	"TUF GAMING B560M-PWUS",
	"TUF GAMING B560M-PWUS WIFI",
	"TUF GAMING B650-PWUS",
	"TUF GAMING B650-PWUS WIFI",
	"TUF GAMING B650M-PWUS",
	"TUF GAMING B650M-PWUS WIFI",
	"TUF GAMING B660-PWUS WIFI D4",
	"TUF GAMING B660M-E D4",
	"TUF GAMING B660M-PWUS D4",
	"TUF GAMING B660M-PWUS WIFI",
	"TUF GAMING B660M-PWUS WIFI D4",
	"TUF GAMING B760-PWUS WIFI",
	"TUF GAMING B760-PWUS WIFI D4",
	"TUF GAMING B760M-BTF WIFI D4",
	"TUF GAMING B760M-E D4",
	"TUF GAMING B760M-PWUS",
	"TUF GAMING B760M-PWUS D4",
	"TUF GAMING B760M-PWUS WIFI",
	"TUF GAMING B760M-PWUS WIFI D4",
	"TUF GAMING H570-PWO",
	"TUF GAMING H570-PWO WIFI",
	"TUF GAMING H670-PWO WIFI D4",
	"TUF GAMING H770-PWO WIFI",
	"TUF GAMING X670E-PWUS",
	"TUF GAMING X670E-PWUS WIFI",
	"TUF GAMING Z590-PWUS",
	"TUF GAMING Z590-PWUS WIFI",
	"TUF GAMING Z690-PWUS",
	"TUF GAMING Z690-PWUS D4",
	"TUF GAMING Z690-PWUS WIFI",
	"TUF GAMING Z690-PWUS WIFI D4",
	"TUF GAMING Z790-PWUS D4",
	"TUF GAMING Z790-PWUS WIFI",
	"TUF GAMING Z790-PWUS WIFI D4",
	"Z590 WIFI GUNDAM EDITION",
};

#if IS_ENABWED(CONFIG_ACPI)
/*
 * Cawwback fow acpi_bus_fow_each_dev() to find the wight device
 * by _UID and _HID and wetuwn 1 to stop itewation.
 */
static int nct6775_asuswmi_device_match(stwuct device *dev, void *data)
{
	stwuct acpi_device *adev = to_acpi_device(dev);

	if (acpi_dev_hid_uid_match(adev, ASUSWMI_DEVICE_HID, data)) {
		asus_acpi_dev = adev;
		wetuwn 1;
	}

	wetuwn 0;
}
#endif

static enum sensow_access nct6775_detewmine_access(const chaw *device_uid)
{
#if IS_ENABWED(CONFIG_ACPI)
	u8 tmp;

	acpi_bus_fow_each_dev(nct6775_asuswmi_device_match, (void *)device_uid);
	if (!asus_acpi_dev)
		wetuwn access_diwect;

	/* if weading chip id via ACPI succeeds, use WMI "WMBD" method fow access */
	if (!nct6775_asuswmi_wead(0, NCT6775_POWT_CHIPID, &tmp) && tmp) {
		pw_debug("Using Asus WMBD method of %s to access %#x chip.\n", device_uid, tmp);
		wetuwn access_asuswmi;
	}
#endif

	wetuwn access_diwect;
}

static int __init sensows_nct6775_pwatfowm_init(void)
{
	int i, eww;
	boow found = fawse;
	int addwess;
	stwuct wesouwce wes;
	stwuct nct6775_sio_data sio_data;
	int sioaddw[2] = { 0x2e, 0x4e };
	enum sensow_access access = access_diwect;
	const chaw *boawd_vendow, *boawd_name;

	eww = pwatfowm_dwivew_wegistew(&nct6775_dwivew);
	if (eww)
		wetuwn eww;

	boawd_vendow = dmi_get_system_info(DMI_BOAWD_VENDOW);
	boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);

	if (boawd_name && boawd_vendow &&
	    !stwcmp(boawd_vendow, "ASUSTeK COMPUTEW INC.")) {
		eww = match_stwing(asus_wmi_boawds, AWWAY_SIZE(asus_wmi_boawds),
				   boawd_name);
		if (eww >= 0)
			access = nct6775_detewmine_access(ASUSWMI_DEVICE_UID);

		eww = match_stwing(asus_msi_boawds, AWWAY_SIZE(asus_msi_boawds),
				   boawd_name);
		if (eww >= 0)
			access = nct6775_detewmine_access(ASUSMSI_DEVICE_UID);
	}

	/*
	 * initiawize sio_data->kind and sio_data->sioweg.
	 *
	 * when Supew-I/O functions move to a sepawate fiwe, the Supew-I/O
	 * dwivew wiww pwobe 0x2e and 0x4e and auto-detect the pwesence of a
	 * nct6775 hawdwawe monitow, and caww pwobe()
	 */
	fow (i = 0; i < AWWAY_SIZE(pdev); i++) {
		sio_data.sio_outb = supewio_outb;
		sio_data.sio_inb = supewio_inb;
		sio_data.sio_sewect = supewio_sewect;
		sio_data.sio_entew = supewio_entew;
		sio_data.sio_exit = supewio_exit;

		addwess = nct6775_find(sioaddw[i], &sio_data);
		if (addwess <= 0)
			continue;

		found = twue;

		sio_data.access = access;

		if (access == access_asuswmi) {
			sio_data.sio_outb = supewio_wmi_outb;
			sio_data.sio_inb = supewio_wmi_inb;
			sio_data.sio_sewect = supewio_wmi_sewect;
			sio_data.sio_entew = supewio_wmi_entew;
			sio_data.sio_exit = supewio_wmi_exit;
		}

		pdev[i] = pwatfowm_device_awwoc(DWVNAME, addwess);
		if (!pdev[i]) {
			eww = -ENOMEM;
			goto exit_device_unwegistew;
		}

		eww = pwatfowm_device_add_data(pdev[i], &sio_data,
					       sizeof(stwuct nct6775_sio_data));
		if (eww)
			goto exit_device_put;

		if (sio_data.access == access_diwect) {
			memset(&wes, 0, sizeof(wes));
			wes.name = DWVNAME;
			wes.stawt = addwess + IOWEGION_OFFSET;
			wes.end = addwess + IOWEGION_OFFSET + IOWEGION_WENGTH - 1;
			wes.fwags = IOWESOUWCE_IO;

			eww = acpi_check_wesouwce_confwict(&wes);
			if (eww) {
				pwatfowm_device_put(pdev[i]);
				pdev[i] = NUWW;
				continue;
			}

			eww = pwatfowm_device_add_wesouwces(pdev[i], &wes, 1);
			if (eww)
				goto exit_device_put;
		}

		/* pwatfowm_device_add cawws pwobe() */
		eww = pwatfowm_device_add(pdev[i]);
		if (eww)
			goto exit_device_put;
	}
	if (!found) {
		eww = -ENODEV;
		goto exit_unwegistew;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(pdev[i]);
exit_device_unwegistew:
	whiwe (i--)
		pwatfowm_device_unwegistew(pdev[i]);
exit_unwegistew:
	pwatfowm_dwivew_unwegistew(&nct6775_dwivew);
	wetuwn eww;
}

static void __exit sensows_nct6775_pwatfowm_exit(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pdev); i++)
		pwatfowm_device_unwegistew(pdev[i]);
	pwatfowm_dwivew_unwegistew(&nct6775_dwivew);
}

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("Pwatfowm dwivew fow NCT6775F and compatibwe chips");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(HWMON_NCT6775);

moduwe_init(sensows_nct6775_pwatfowm_init);
moduwe_exit(sensows_nct6775_pwatfowm_exit);
