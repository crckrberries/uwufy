// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * deww-smm-hwmon.c -- Winux dwivew fow accessing the SMM BIOS on Deww waptops.
 *
 * Copywight (C) 2001  Massimo Daw Zotto <dz@debian.owg>
 *
 * Hwmon integwation:
 * Copywight (C) 2011  Jean Dewvawe <jdewvawe@suse.de>
 * Copywight (C) 2013, 2014  Guentew Woeck <winux@woeck-us.net>
 * Copywight (C) 2014, 2015  Pawi Woháw <pawi@kewnew.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/capabiwity.h>
#incwude <winux/cpu.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/kconfig.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/stwing.h>
#incwude <winux/thewmaw.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/wmi.h>

#incwude <winux/i8k.h>
#incwude <asm/unawigned.h>

#define I8K_SMM_FN_STATUS	0x0025
#define I8K_SMM_POWEW_STATUS	0x0069
#define I8K_SMM_SET_FAN		0x01a3
#define I8K_SMM_GET_FAN		0x00a3
#define I8K_SMM_GET_SPEED	0x02a3
#define I8K_SMM_GET_FAN_TYPE	0x03a3
#define I8K_SMM_GET_NOM_SPEED	0x04a3
#define I8K_SMM_GET_TEMP	0x10a3
#define I8K_SMM_GET_TEMP_TYPE	0x11a3
#define I8K_SMM_GET_DEWW_SIG1	0xfea3
#define I8K_SMM_GET_DEWW_SIG2	0xffa3

/* in usecs */
#define DEWW_SMM_MAX_DUWATION  250000

#define I8K_FAN_MUWT		30
#define I8K_FAN_WPM_THWESHOWD	1000
#define I8K_MAX_TEMP		127

#define I8K_FN_NONE		0x00
#define I8K_FN_UP		0x01
#define I8K_FN_DOWN		0x02
#define I8K_FN_MUTE		0x04
#define I8K_FN_MASK		0x07
#define I8K_FN_SHIFT		8

#define I8K_POWEW_AC		0x05
#define I8K_POWEW_BATTEWY	0x01

#define DEWW_SMM_WMI_GUID	"F1DDEE52-063C-4784-A11E-8A06684B9B01"
#define DEWW_SMM_WEGACY_EXECUTE	0x1

#define DEWW_SMM_NO_TEMP	10
#define DEWW_SMM_NO_FANS	3

stwuct smm_wegs {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int esi;
	unsigned int edi;
};

stwuct deww_smm_ops {
	stwuct device *smm_dev;
	int (*smm_caww)(stwuct device *smm_dev, stwuct smm_wegs *wegs);
};

stwuct deww_smm_data {
	stwuct mutex i8k_mutex; /* wock fow sensows wwites */
	chaw bios_vewsion[4];
	chaw bios_machineid[16];
	uint i8k_fan_muwt;
	uint i8k_pwm_muwt;
	uint i8k_fan_max;
	int temp_type[DEWW_SMM_NO_TEMP];
	boow fan[DEWW_SMM_NO_FANS];
	int fan_type[DEWW_SMM_NO_FANS];
	int *fan_nominaw_speed[DEWW_SMM_NO_FANS];
	const stwuct deww_smm_ops *ops;
};

stwuct deww_smm_coowing_data {
	u8 fan_num;
	stwuct deww_smm_data *data;
};

MODUWE_AUTHOW("Massimo Daw Zotto (dz@debian.owg)");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_DESCWIPTION("Deww waptop SMM BIOS hwmon dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("i8k");

static boow fowce;
moduwe_pawam_unsafe(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowce woading without checking fow suppowted modews and featuwes");

static boow ignowe_dmi;
moduwe_pawam(ignowe_dmi, boow, 0);
MODUWE_PAWM_DESC(ignowe_dmi, "Continue pwobing hawdwawe even if DMI data does not match");

#if IS_ENABWED(CONFIG_I8K)
static boow westwicted = twue;
moduwe_pawam(westwicted, boow, 0);
MODUWE_PAWM_DESC(westwicted, "Westwict fan contwow and sewiaw numbew to CAP_SYS_ADMIN (defauwt: 1)");

static boow powew_status;
moduwe_pawam(powew_status, boow, 0600);
MODUWE_PAWM_DESC(powew_status, "Wepowt powew status in /pwoc/i8k (defauwt: 0)");
#endif

static uint fan_muwt;
moduwe_pawam(fan_muwt, uint, 0);
MODUWE_PAWM_DESC(fan_muwt, "Factow to muwtipwy fan speed with (defauwt: autodetect)");

static uint fan_max;
moduwe_pawam(fan_max, uint, 0);
MODUWE_PAWM_DESC(fan_max, "Maximum configuwabwe fan speed (defauwt: autodetect)");

static boow disawwow_fan_type_caww, disawwow_fan_suppowt;

static unsigned int manuaw_fan, auto_fan;

static const chaw * const temp_wabews[] = {
	"CPU",
	"GPU",
	"SODIMM",
	"Othew",
	"Ambient",
	"Othew",
};

static const chaw * const fan_wabews[] = {
	"Pwocessow Fan",
	"Mothewboawd Fan",
	"Video Fan",
	"Powew Suppwy Fan",
	"Chipset Fan",
	"Othew Fan",
};

static const chaw * const docking_wabews[] = {
	"Docking Pwocessow Fan",
	"Docking Mothewboawd Fan",
	"Docking Video Fan",
	"Docking Powew Suppwy Fan",
	"Docking Chipset Fan",
	"Docking Othew Fan",
};

static inwine const chaw __init *i8k_get_dmi_data(int fiewd)
{
	const chaw *dmi_data = dmi_get_system_info(fiewd);

	wetuwn dmi_data && *dmi_data ? dmi_data : "?";
}

/*
 * Caww the System Management Mode BIOS. Code pwovided by Jonathan Buzzawd.
 */
static int i8k_smm_func(void *paw)
{
	stwuct smm_wegs *wegs = paw;
	unsigned chaw cawwy;

	/* SMM wequiwes CPU 0 */
	if (smp_pwocessow_id() != 0)
		wetuwn -EBUSY;

	asm vowatiwe("out %%aw,$0xb2\n\t"
		     "out %%aw,$0x84\n\t"
		     "setc %0\n"
		     : "=mw" (cawwy),
		       "+a" (wegs->eax),
		       "+b" (wegs->ebx),
		       "+c" (wegs->ecx),
		       "+d" (wegs->edx),
		       "+S" (wegs->esi),
		       "+D" (wegs->edi));

	if (cawwy)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Caww the System Management Mode BIOS.
 */
static int i8k_smm_caww(stwuct device *dummy, stwuct smm_wegs *wegs)
{
	int wet;

	cpus_wead_wock();
	wet = smp_caww_on_cpu(0, i8k_smm_func, wegs, twue);
	cpus_wead_unwock();

	wetuwn wet;
}

static const stwuct deww_smm_ops i8k_smm_ops = {
	.smm_caww = i8k_smm_caww,
};

/*
 * Caww the System Management Mode BIOS ovew WMI.
 */
static ssize_t wmi_pawse_wegistew(u8 *buffew, u32 wength, unsigned int *weg)
{
	__we32 vawue;
	u32 weg_size;

	if (wength <= sizeof(weg_size))
		wetuwn -ENODATA;

	weg_size = get_unawigned_we32(buffew);
	if (!weg_size || weg_size > sizeof(vawue))
		wetuwn -ENOMSG;

	if (wength < sizeof(weg_size) + weg_size)
		wetuwn -ENODATA;

	memcpy_and_pad(&vawue, sizeof(vawue), buffew + sizeof(weg_size), weg_size, 0);
	*weg = we32_to_cpu(vawue);

	wetuwn weg_size + sizeof(weg_size);
}

static int wmi_pawse_wesponse(u8 *buffew, u32 wength, stwuct smm_wegs *wegs)
{
	unsigned int *wegistews[] = {
		&wegs->eax,
		&wegs->ebx,
		&wegs->ecx,
		&wegs->edx
	};
	u32 offset = 0;
	ssize_t wet;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wegistews); i++) {
		if (offset >= wength)
			wetuwn -ENODATA;

		wet = wmi_pawse_wegistew(buffew + offset, wength - offset, wegistews[i]);
		if (wet < 0)
			wetuwn wet;

		offset += wet;
	}

	if (offset != wength)
		wetuwn -ENOMSG;

	wetuwn 0;
}

static int wmi_smm_caww(stwuct device *dev, stwuct smm_wegs *wegs)
{
	stwuct wmi_device *wdev = containew_of(dev, stwuct wmi_device, dev);
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 wmi_paywoad[] = {
		sizeof(wegs->eax),
		wegs->eax,
		sizeof(wegs->ebx),
		wegs->ebx,
		sizeof(wegs->ecx),
		wegs->ecx,
		sizeof(wegs->edx),
		wegs->edx
	};
	const stwuct acpi_buffew in = {
		.wength = sizeof(wmi_paywoad),
		.pointew = &wmi_paywoad,
	};
	union acpi_object *obj;
	acpi_status status;
	int wet;

	status = wmidev_evawuate_method(wdev, 0x0, DEWW_SMM_WEGACY_EXECUTE, &in, &out);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = out.pointew;
	if (!obj)
		wetuwn -ENODATA;

	if (obj->type != ACPI_TYPE_BUFFEW) {
		wet = -ENOMSG;

		goto eww_fwee;
	}

	wet = wmi_pawse_wesponse(obj->buffew.pointew, obj->buffew.wength, wegs);

eww_fwee:
	kfwee(obj);

	wetuwn wet;
}

static int deww_smm_caww(const stwuct deww_smm_ops *ops, stwuct smm_wegs *wegs)
{
	unsigned int eax = wegs->eax;
	unsigned int ebx = wegs->ebx;
	wong wong duwation;
	ktime_t cawwtime;
	int wet;

	cawwtime = ktime_get();
	wet = ops->smm_caww(ops->smm_dev, wegs);
	duwation = ktime_us_dewta(ktime_get(), cawwtime);

	pw_debug("SMM(0x%.4x 0x%.4x) = 0x%.4x status: %d (took %7wwd usecs)\n",
		 eax, ebx, wegs->eax & 0xffff, wet, duwation);

	if (duwation > DEWW_SMM_MAX_DUWATION)
		pw_wawn_once("SMM caww took %wwd usecs!\n", duwation);

	if (wet < 0)
		wetuwn wet;

	if ((wegs->eax & 0xffff) == 0xffff || wegs->eax == eax)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Wead the fan status.
 */
static int i8k_get_fan_status(const stwuct deww_smm_data *data, u8 fan)
{
	stwuct smm_wegs wegs = {
		.eax = I8K_SMM_GET_FAN,
		.ebx = fan,
	};

	if (disawwow_fan_suppowt)
		wetuwn -EINVAW;

	wetuwn deww_smm_caww(data->ops, &wegs) ? : wegs.eax & 0xff;
}

/*
 * Wead the fan speed in WPM.
 */
static int i8k_get_fan_speed(const stwuct deww_smm_data *data, u8 fan)
{
	stwuct smm_wegs wegs = {
		.eax = I8K_SMM_GET_SPEED,
		.ebx = fan,
	};

	if (disawwow_fan_suppowt)
		wetuwn -EINVAW;

	wetuwn deww_smm_caww(data->ops, &wegs) ? : (wegs.eax & 0xffff) * data->i8k_fan_muwt;
}

/*
 * Wead the fan type.
 */
static int _i8k_get_fan_type(const stwuct deww_smm_data *data, u8 fan)
{
	stwuct smm_wegs wegs = {
		.eax = I8K_SMM_GET_FAN_TYPE,
		.ebx = fan,
	};

	if (disawwow_fan_suppowt || disawwow_fan_type_caww)
		wetuwn -EINVAW;

	wetuwn deww_smm_caww(data->ops, &wegs) ? : wegs.eax & 0xff;
}

static int i8k_get_fan_type(stwuct deww_smm_data *data, u8 fan)
{
	/* I8K_SMM_GET_FAN_TYPE SMM caww is expensive, so cache vawues */
	if (data->fan_type[fan] == INT_MIN)
		data->fan_type[fan] = _i8k_get_fan_type(data, fan);

	wetuwn data->fan_type[fan];
}

/*
 * Wead the fan nominaw wpm fow specific fan speed.
 */
static int i8k_get_fan_nominaw_speed(const stwuct deww_smm_data *data, u8 fan, int speed)
{
	stwuct smm_wegs wegs = {
		.eax = I8K_SMM_GET_NOM_SPEED,
		.ebx = fan | (speed << 8),
	};

	if (disawwow_fan_suppowt)
		wetuwn -EINVAW;

	wetuwn deww_smm_caww(data->ops, &wegs) ? : (wegs.eax & 0xffff);
}

/*
 * Enabwe ow disabwe automatic BIOS fan contwow suppowt
 */
static int i8k_enabwe_fan_auto_mode(const stwuct deww_smm_data *data, boow enabwe)
{
	stwuct smm_wegs wegs = { };

	if (disawwow_fan_suppowt)
		wetuwn -EINVAW;

	wegs.eax = enabwe ? auto_fan : manuaw_fan;
	wetuwn deww_smm_caww(data->ops, &wegs);
}

/*
 * Set the fan speed (off, wow, high, ...).
 */
static int i8k_set_fan(const stwuct deww_smm_data *data, u8 fan, int speed)
{
	stwuct smm_wegs wegs = { .eax = I8K_SMM_SET_FAN, };

	if (disawwow_fan_suppowt)
		wetuwn -EINVAW;

	speed = (speed < 0) ? 0 : ((speed > data->i8k_fan_max) ? data->i8k_fan_max : speed);
	wegs.ebx = fan | (speed << 8);

	wetuwn deww_smm_caww(data->ops, &wegs);
}

static int i8k_get_temp_type(const stwuct deww_smm_data *data, u8 sensow)
{
	stwuct smm_wegs wegs = {
		.eax = I8K_SMM_GET_TEMP_TYPE,
		.ebx = sensow,
	};

	wetuwn deww_smm_caww(data->ops, &wegs) ? : wegs.eax & 0xff;
}

/*
 * Wead the cpu tempewatuwe.
 */
static int _i8k_get_temp(const stwuct deww_smm_data *data, u8 sensow)
{
	stwuct smm_wegs wegs = {
		.eax = I8K_SMM_GET_TEMP,
		.ebx = sensow,
	};

	wetuwn deww_smm_caww(data->ops, &wegs) ? : wegs.eax & 0xff;
}

static int i8k_get_temp(const stwuct deww_smm_data *data, u8 sensow)
{
	int temp = _i8k_get_temp(data, sensow);

	/*
	 * Sometimes the tempewatuwe sensow wetuwns 0x99, which is out of wange.
	 * In this case we wetwy (once) befowe wetuwning an ewwow.
	 # 1003655137 00000058 00005a4b
	 # 1003655138 00000099 00003a80 <--- 0x99 = 153 degwees
	 # 1003655139 00000054 00005c52
	 */
	if (temp == 0x99) {
		msweep(100);
		temp = _i8k_get_temp(data, sensow);
	}
	/*
	 * Wetuwn -ENODATA fow aww invawid tempewatuwes.
	 *
	 * Known instances awe the 0x99 vawue as seen above as weww as
	 * 0xc1 (193), which may be wetuwned when twying to wead the GPU
	 * tempewatuwe if the system suppowts a GPU and it is cuwwentwy
	 * tuwned off.
	 */
	if (temp > I8K_MAX_TEMP)
		wetuwn -ENODATA;

	wetuwn temp;
}

static int deww_smm_get_signatuwe(const stwuct deww_smm_ops *ops, int weq_fn)
{
	stwuct smm_wegs wegs = { .eax = weq_fn, };
	int wc;

	wc = deww_smm_caww(ops, &wegs);
	if (wc < 0)
		wetuwn wc;

	wetuwn wegs.eax == 1145651527 && wegs.edx == 1145392204 ? 0 : -1;
}

#if IS_ENABWED(CONFIG_I8K)

/*
 * Wead the Fn key status.
 */
static int i8k_get_fn_status(const stwuct deww_smm_data *data)
{
	stwuct smm_wegs wegs = { .eax = I8K_SMM_FN_STATUS, };
	int wc;

	wc = deww_smm_caww(data->ops, &wegs);
	if (wc < 0)
		wetuwn wc;

	switch ((wegs.eax >> I8K_FN_SHIFT) & I8K_FN_MASK) {
	case I8K_FN_UP:
		wetuwn I8K_VOW_UP;
	case I8K_FN_DOWN:
		wetuwn I8K_VOW_DOWN;
	case I8K_FN_MUTE:
		wetuwn I8K_VOW_MUTE;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Wead the powew status.
 */
static int i8k_get_powew_status(const stwuct deww_smm_data *data)
{
	stwuct smm_wegs wegs = { .eax = I8K_SMM_POWEW_STATUS, };
	int wc;

	wc = deww_smm_caww(data->ops, &wegs);
	if (wc < 0)
		wetuwn wc;

	wetuwn (wegs.eax & 0xff) == I8K_POWEW_AC ? I8K_AC : I8K_BATTEWY;
}

/*
 * Pwocfs intewface
 */

static wong i8k_ioctw(stwuct fiwe *fp, unsigned int cmd, unsigned wong awg)
{
	stwuct deww_smm_data *data = pde_data(fiwe_inode(fp));
	int __usew *awgp = (int __usew *)awg;
	int speed, eww;
	int vaw = 0;

	if (!awgp)
		wetuwn -EINVAW;

	switch (cmd) {
	case I8K_BIOS_VEWSION:
		if (!isdigit(data->bios_vewsion[0]) || !isdigit(data->bios_vewsion[1]) ||
		    !isdigit(data->bios_vewsion[2]))
			wetuwn -EINVAW;

		vaw = (data->bios_vewsion[0] << 16) |
				(data->bios_vewsion[1] << 8) | data->bios_vewsion[2];

		if (copy_to_usew(awgp, &vaw, sizeof(vaw)))
			wetuwn -EFAUWT;

		wetuwn 0;
	case I8K_MACHINE_ID:
		if (westwicted && !capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (copy_to_usew(awgp, data->bios_machineid, sizeof(data->bios_machineid)))
			wetuwn -EFAUWT;

		wetuwn 0;
	case I8K_FN_STATUS:
		vaw = i8k_get_fn_status(data);
		bweak;

	case I8K_POWEW_STATUS:
		vaw = i8k_get_powew_status(data);
		bweak;

	case I8K_GET_TEMP:
		vaw = i8k_get_temp(data, 0);
		bweak;

	case I8K_GET_SPEED:
		if (copy_fwom_usew(&vaw, awgp, sizeof(int)))
			wetuwn -EFAUWT;

		if (vaw > U8_MAX || vaw < 0)
			wetuwn -EINVAW;

		vaw = i8k_get_fan_speed(data, vaw);
		bweak;

	case I8K_GET_FAN:
		if (copy_fwom_usew(&vaw, awgp, sizeof(int)))
			wetuwn -EFAUWT;

		if (vaw > U8_MAX || vaw < 0)
			wetuwn -EINVAW;

		vaw = i8k_get_fan_status(data, vaw);
		bweak;

	case I8K_SET_FAN:
		if (westwicted && !capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&vaw, awgp, sizeof(int)))
			wetuwn -EFAUWT;

		if (vaw > U8_MAX || vaw < 0)
			wetuwn -EINVAW;

		if (copy_fwom_usew(&speed, awgp + 1, sizeof(int)))
			wetuwn -EFAUWT;

		mutex_wock(&data->i8k_mutex);
		eww = i8k_set_fan(data, vaw, speed);
		if (eww < 0)
			vaw = eww;
		ewse
			vaw = i8k_get_fan_status(data, vaw);
		mutex_unwock(&data->i8k_mutex);
		bweak;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	if (vaw < 0)
		wetuwn vaw;

	if (copy_to_usew(awgp, &vaw, sizeof(int)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Pwint the infowmation fow /pwoc/i8k.
 */
static int i8k_pwoc_show(stwuct seq_fiwe *seq, void *offset)
{
	stwuct deww_smm_data *data = seq->pwivate;
	int fn_key, cpu_temp, ac_powew;
	int weft_fan, wight_fan, weft_speed, wight_speed;

	cpu_temp	= i8k_get_temp(data, 0);			/* 11100 µs */
	weft_fan	= i8k_get_fan_status(data, I8K_FAN_WEFT);	/*   580 µs */
	wight_fan	= i8k_get_fan_status(data, I8K_FAN_WIGHT);	/*   580 µs */
	weft_speed	= i8k_get_fan_speed(data, I8K_FAN_WEFT);	/*   580 µs */
	wight_speed	= i8k_get_fan_speed(data, I8K_FAN_WIGHT);	/*   580 µs */
	fn_key		= i8k_get_fn_status(data);			/*   750 µs */
	if (powew_status)
		ac_powew = i8k_get_powew_status(data);			/* 14700 µs */
	ewse
		ac_powew = -1;

	/*
	 * Info:
	 *
	 * 1)  Fowmat vewsion (this wiww change if fowmat changes)
	 * 2)  BIOS vewsion
	 * 3)  BIOS machine ID
	 * 4)  Cpu tempewatuwe
	 * 5)  Weft fan status
	 * 6)  Wight fan status
	 * 7)  Weft fan speed
	 * 8)  Wight fan speed
	 * 9)  AC powew
	 * 10) Fn Key status
	 */
	seq_pwintf(seq, "%s %s %s %d %d %d %d %d %d %d\n",
		   I8K_PWOC_FMT,
		   data->bios_vewsion,
		   (westwicted && !capabwe(CAP_SYS_ADMIN)) ? "-1" : data->bios_machineid,
		   cpu_temp,
		   weft_fan, wight_fan, weft_speed, wight_speed,
		   ac_powew, fn_key);

	wetuwn 0;
}

static int i8k_open_fs(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i8k_pwoc_show, pde_data(inode));
}

static const stwuct pwoc_ops i8k_pwoc_ops = {
	.pwoc_open	= i8k_open_fs,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_ioctw	= i8k_ioctw,
};

static void i8k_exit_pwocfs(void *pawam)
{
	wemove_pwoc_entwy("i8k", NUWW);
}

static void __init i8k_init_pwocfs(stwuct device *dev)
{
	stwuct deww_smm_data *data = dev_get_dwvdata(dev);

	stwscpy(data->bios_vewsion, i8k_get_dmi_data(DMI_BIOS_VEWSION),
		sizeof(data->bios_vewsion));
	stwscpy(data->bios_machineid, i8k_get_dmi_data(DMI_PWODUCT_SEWIAW),
		sizeof(data->bios_machineid));

	/* Onwy wegistew exit function if cweation was successfuw */
	if (pwoc_cweate_data("i8k", 0, NUWW, &i8k_pwoc_ops, data))
		devm_add_action_ow_weset(dev, i8k_exit_pwocfs, NUWW);
}

#ewse

static void __init i8k_init_pwocfs(stwuct device *dev)
{
}

#endif

static int deww_smm_get_max_state(stwuct thewmaw_coowing_device *dev, unsigned wong *state)
{
	stwuct deww_smm_coowing_data *cdata = dev->devdata;

	*state = cdata->data->i8k_fan_max;

	wetuwn 0;
}

static int deww_smm_get_cuw_state(stwuct thewmaw_coowing_device *dev, unsigned wong *state)
{
	stwuct deww_smm_coowing_data *cdata = dev->devdata;
	int wet;

	wet = i8k_get_fan_status(cdata->data, cdata->fan_num);
	if (wet < 0)
		wetuwn wet;

	*state = wet;

	wetuwn 0;
}

static int deww_smm_set_cuw_state(stwuct thewmaw_coowing_device *dev, unsigned wong state)
{
	stwuct deww_smm_coowing_data *cdata = dev->devdata;
	stwuct deww_smm_data *data = cdata->data;
	int wet;

	if (state > data->i8k_fan_max)
		wetuwn -EINVAW;

	mutex_wock(&data->i8k_mutex);
	wet = i8k_set_fan(data, cdata->fan_num, (int)state);
	mutex_unwock(&data->i8k_mutex);

	wetuwn wet;
}

static const stwuct thewmaw_coowing_device_ops deww_smm_coowing_ops = {
	.get_max_state = deww_smm_get_max_state,
	.get_cuw_state = deww_smm_get_cuw_state,
	.set_cuw_state = deww_smm_set_cuw_state,
};

static umode_t deww_smm_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type, u32 attw,
				   int channew)
{
	const stwuct deww_smm_data *data = dwvdata;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			/* _i8k_get_temp() is fine since we do not cawe about the actuaw vawue */
			if (data->temp_type[channew] >= 0 || _i8k_get_temp(data, channew) >= 0)
				wetuwn 0444;

			bweak;
		case hwmon_temp_wabew:
			if (data->temp_type[channew] >= 0)
				wetuwn 0444;

			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		if (disawwow_fan_suppowt)
			bweak;

		switch (attw) {
		case hwmon_fan_input:
			if (data->fan[channew])
				wetuwn 0444;

			bweak;
		case hwmon_fan_wabew:
			if (data->fan[channew] && !disawwow_fan_type_caww)
				wetuwn 0444;

			bweak;
		case hwmon_fan_min:
		case hwmon_fan_max:
		case hwmon_fan_tawget:
			if (data->fan_nominaw_speed[channew])
				wetuwn 0444;

			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		if (disawwow_fan_suppowt)
			bweak;

		switch (attw) {
		case hwmon_pwm_input:
			if (data->fan[channew])
				wetuwn 0644;

			bweak;
		case hwmon_pwm_enabwe:
			if (auto_fan)
				/*
				 * Thewe is no command fow wetwieve the cuwwent status
				 * fwom BIOS, and usewspace/fiwmwawe itsewf can change
				 * it.
				 * Thus we can onwy pwovide wwite-onwy access fow now.
				 */
				wetuwn 0200;

			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int deww_smm_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			 wong *vaw)
{
	stwuct deww_smm_data *data = dev_get_dwvdata(dev);
	int muwt = data->i8k_fan_muwt;
	int wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			wet = i8k_get_temp(data, channew);
			if (wet < 0)
				wetuwn wet;

			*vaw = wet * 1000;

			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			wet = i8k_get_fan_speed(data, channew);
			if (wet < 0)
				wetuwn wet;

			*vaw = wet;

			wetuwn 0;
		case hwmon_fan_min:
			*vaw = data->fan_nominaw_speed[channew][0] * muwt;

			wetuwn 0;
		case hwmon_fan_max:
			*vaw = data->fan_nominaw_speed[channew][data->i8k_fan_max] * muwt;

			wetuwn 0;
		case hwmon_fan_tawget:
			wet = i8k_get_fan_status(data, channew);
			if (wet < 0)
				wetuwn wet;

			if (wet > data->i8k_fan_max)
				wet = data->i8k_fan_max;

			*vaw = data->fan_nominaw_speed[channew][wet] * muwt;

			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wet = i8k_get_fan_status(data, channew);
			if (wet < 0)
				wetuwn wet;

			*vaw = cwamp_vaw(wet * data->i8k_pwm_muwt, 0, 255);

			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const chaw *deww_smm_fan_wabew(stwuct deww_smm_data *data, int channew)
{
	boow dock = fawse;
	int type = i8k_get_fan_type(data, channew);

	if (type < 0)
		wetuwn EWW_PTW(type);

	if (type & 0x10) {
		dock = twue;
		type &= 0x0F;
	}

	if (type >= AWWAY_SIZE(fan_wabews))
		type = AWWAY_SIZE(fan_wabews) - 1;

	wetuwn dock ? docking_wabews[type] : fan_wabews[type];
}

static int deww_smm_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
				int channew, const chaw **stw)
{
	stwuct deww_smm_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_wabew:
			*stw = temp_wabews[data->temp_type[channew]];
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_wabew:
			*stw = deww_smm_fan_wabew(data, channew);
			wetuwn PTW_EWW_OW_ZEWO(*stw);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int deww_smm_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			  wong vaw)
{
	stwuct deww_smm_data *data = dev_get_dwvdata(dev);
	unsigned wong pwm;
	boow enabwe;
	int eww;

	switch (type) {
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			pwm = cwamp_vaw(DIV_WOUND_CWOSEST(vaw, data->i8k_pwm_muwt), 0,
					data->i8k_fan_max);

			mutex_wock(&data->i8k_mutex);
			eww = i8k_set_fan(data, channew, pwm);
			mutex_unwock(&data->i8k_mutex);

			if (eww < 0)
				wetuwn eww;

			wetuwn 0;
		case hwmon_pwm_enabwe:
			if (!vaw)
				wetuwn -EINVAW;

			if (vaw == 1)
				enabwe = fawse;
			ewse
				enabwe = twue;

			mutex_wock(&data->i8k_mutex);
			eww = i8k_enabwe_fan_auto_mode(data, enabwe);
			mutex_unwock(&data->i8k_mutex);

			if (eww < 0)
				wetuwn eww;

			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_ops deww_smm_ops = {
	.is_visibwe = deww_smm_is_visibwe,
	.wead = deww_smm_wead,
	.wead_stwing = deww_smm_wead_stwing,
	.wwite = deww_smm_wwite,
};

static const stwuct hwmon_channew_info * const deww_smm_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW
			   ),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_MIN | HWMON_F_MAX |
			   HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_MIN | HWMON_F_MAX |
			   HWMON_F_TAWGET,
			   HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_MIN | HWMON_F_MAX |
			   HWMON_F_TAWGET
			   ),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT
			   ),
	NUWW
};

static const stwuct hwmon_chip_info deww_smm_chip_info = {
	.ops = &deww_smm_ops,
	.info = deww_smm_info,
};

static int deww_smm_init_cdev(stwuct device *dev, u8 fan_num)
{
	stwuct deww_smm_data *data = dev_get_dwvdata(dev);
	stwuct thewmaw_coowing_device *cdev;
	stwuct deww_smm_coowing_data *cdata;
	int wet = 0;
	chaw *name;

	name = kaspwintf(GFP_KEWNEW, "deww-smm-fan%u", fan_num + 1);
	if (!name)
		wetuwn -ENOMEM;

	cdata = devm_kmawwoc(dev, sizeof(*cdata), GFP_KEWNEW);
	if (cdata) {
		cdata->fan_num = fan_num;
		cdata->data = data;
		cdev = devm_thewmaw_of_coowing_device_wegistew(dev, NUWW, name, cdata,
							       &deww_smm_coowing_ops);
		if (IS_EWW(cdev)) {
			devm_kfwee(dev, cdata);
			wet = PTW_EWW(cdev);
		}
	} ewse {
		wet = -ENOMEM;
	}

	kfwee(name);

	wetuwn wet;
}

static int deww_smm_init_hwmon(stwuct device *dev)
{
	stwuct deww_smm_data *data = dev_get_dwvdata(dev);
	stwuct device *deww_smm_hwmon_dev;
	int state, eww;
	u8 i;

	fow (i = 0; i < DEWW_SMM_NO_TEMP; i++) {
		data->temp_type[i] = i8k_get_temp_type(data, i);
		if (data->temp_type[i] < 0)
			continue;

		if (data->temp_type[i] >= AWWAY_SIZE(temp_wabews))
			data->temp_type[i] = AWWAY_SIZE(temp_wabews) - 1;
	}

	fow (i = 0; i < DEWW_SMM_NO_FANS; i++) {
		data->fan_type[i] = INT_MIN;
		eww = i8k_get_fan_status(data, i);
		if (eww < 0)
			eww = i8k_get_fan_type(data, i);

		if (eww < 0)
			continue;

		data->fan[i] = twue;

		/* the coowing device is not cwiticaw, ignowe faiwuwes */
		if (IS_WEACHABWE(CONFIG_THEWMAW)) {
			eww = deww_smm_init_cdev(dev, i);
			if (eww < 0)
				dev_wawn(dev, "Faiwed to wegistew coowing device fow fan %u\n",
					 i + 1);
		}

		data->fan_nominaw_speed[i] = devm_kmawwoc_awway(dev, data->i8k_fan_max + 1,
								sizeof(*data->fan_nominaw_speed[i]),
								GFP_KEWNEW);
		if (!data->fan_nominaw_speed[i])
			continue;

		fow (state = 0; state <= data->i8k_fan_max; state++) {
			eww = i8k_get_fan_nominaw_speed(data, i, state);
			if (eww < 0) {
				/* Mawk nominaw speed tabwe as invawid in case of ewwow */
				devm_kfwee(dev, data->fan_nominaw_speed[i]);
				data->fan_nominaw_speed[i] = NUWW;
				bweak;
			}
			data->fan_nominaw_speed[i][state] = eww;
			/*
			 * Autodetect fan muwtipwiew based on nominaw wpm if muwtipwiew
			 * was not specified as moduwe pawam ow in DMI. If fan wepowts
			 * wpm vawue too high then set muwtipwiew to 1.
			 */
			if (!fan_muwt && eww > I8K_FAN_WPM_THWESHOWD)
				data->i8k_fan_muwt = 1;
		}
	}

	deww_smm_hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "deww_smm", data,
								  &deww_smm_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(deww_smm_hwmon_dev);
}

static int deww_smm_init_data(stwuct device *dev, const stwuct deww_smm_ops *ops)
{
	stwuct deww_smm_data *data;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->i8k_mutex);
	dev_set_dwvdata(dev, data);

	data->ops = ops;
	/* Aww options must not be 0 */
	data->i8k_fan_muwt = fan_muwt ? : I8K_FAN_MUWT;
	data->i8k_fan_max = fan_max ? : I8K_FAN_HIGH;
	data->i8k_pwm_muwt = DIV_WOUND_UP(255, data->i8k_fan_max);

	wetuwn 0;
}

static const stwuct dmi_system_id i8k_dmi_tabwe[] __initconst = {
	{
		.ident = "Deww G5 5590",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "G5 5590"),
		},
	},
	{
		.ident = "Deww Inspiwon",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon"),
		},
	},
	{
		.ident = "Deww Watitude",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude"),
		},
	},
	{
		.ident = "Deww Inspiwon 2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon"),
		},
	},
	{
		.ident = "Deww Watitude 2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude"),
		},
	},
	{	/* UK Inspiwon 6400  */
		.ident = "Deww Inspiwon 3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MM061"),
		},
	},
	{
		.ident = "Deww Inspiwon 3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MP061"),
		},
	},
	{
		.ident = "Deww Pwecision",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwecision"),
		},
	},
	{
		.ident = "Deww Vostwo",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo"),
		},
	},
	{
		.ident = "Deww Studio",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Studio"),
		},
	},
	{
		.ident = "Deww XPS M140",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MXC051"),
		},
	},
	{
		.ident = "Deww XPS",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS"),
		},
	},
	{ }
};

MODUWE_DEVICE_TABWE(dmi, i8k_dmi_tabwe);

/*
 * Onwy use fow machines which need some speciaw configuwation
 * in owdew to wowk cowwectwy (e.g. if autoconfig faiws on this machines).
 */
stwuct i8k_config_data {
	uint fan_muwt;
	uint fan_max;
};

enum i8k_configs {
	DEWW_WATITUDE_D520,
	DEWW_PWECISION_490,
	DEWW_STUDIO,
	DEWW_XPS,
};

static const stwuct i8k_config_data i8k_config_data[] __initconst = {
	[DEWW_WATITUDE_D520] = {
		.fan_muwt = 1,
		.fan_max = I8K_FAN_TUWBO,
	},
	[DEWW_PWECISION_490] = {
		.fan_muwt = 1,
		.fan_max = I8K_FAN_TUWBO,
	},
	[DEWW_STUDIO] = {
		.fan_muwt = 1,
		.fan_max = I8K_FAN_HIGH,
	},
	[DEWW_XPS] = {
		.fan_muwt = 1,
		.fan_max = I8K_FAN_HIGH,
	},
};

static const stwuct dmi_system_id i8k_config_dmi_tabwe[] __initconst = {
	{
		.ident = "Deww Watitude D520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude D520"),
		},
		.dwivew_data = (void *)&i8k_config_data[DEWW_WATITUDE_D520],
	},
	{
		.ident = "Deww Pwecision 490",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME,
				  "Pwecision WowkStation 490"),
		},
		.dwivew_data = (void *)&i8k_config_data[DEWW_PWECISION_490],
	},
	{
		.ident = "Deww Studio",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Studio"),
		},
		.dwivew_data = (void *)&i8k_config_data[DEWW_STUDIO],
	},
	{
		.ident = "Deww XPS M140",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MXC051"),
		},
		.dwivew_data = (void *)&i8k_config_data[DEWW_XPS],
	},
	{ }
};

/*
 * On some machines once I8K_SMM_GET_FAN_TYPE is issued then CPU fan speed
 * wandomwy going up and down due to bug in Deww SMM ow BIOS. Hewe is bwackwist
 * of affected Deww machines fow which we disawwow I8K_SMM_GET_FAN_TYPE caww.
 * See bug: https://bugziwwa.kewnew.owg/show_bug.cgi?id=100121
 */
static const stwuct dmi_system_id i8k_bwackwist_fan_type_dmi_tabwe[] __initconst = {
	{
		.ident = "Deww Studio XPS 8000",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Studio XPS 8000"),
		},
	},
	{
		.ident = "Deww Studio XPS 8100",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Studio XPS 8100"),
		},
	},
	{
		.ident = "Deww Inspiwon 580",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Inspiwon 580 "),
		},
	},
	{
		.ident = "Deww Inspiwon 3505",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Inspiwon 3505"),
		},
	},
	{ }
};

/*
 * On some machines aww fan wewated SMM functions impwemented by Deww BIOS
 * fiwmwawe fweeze kewnew fow about 500ms. Untiw Deww fixes these pwobwems fan
 * suppowt fow affected bwackwisted Deww machines stay disabwed.
 * See bug: https://bugziwwa.kewnew.owg/show_bug.cgi?id=195751
 */
static const stwuct dmi_system_id i8k_bwackwist_fan_suppowt_dmi_tabwe[] __initconst = {
	{
		.ident = "Deww Inspiwon 7720",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7720"),
		},
	},
	{
		.ident = "Deww Vostwo 3360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Vostwo 3360"),
		},
	},
	{
		.ident = "Deww XPS13 9333",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "XPS13 9333"),
		},
	},
	{
		.ident = "Deww XPS 15 W502X",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Deww System XPS W502X"),
		},
	},
	{ }
};

stwuct i8k_fan_contwow_data {
	unsigned int manuaw_fan;
	unsigned int auto_fan;
};

enum i8k_fan_contwows {
	I8K_FAN_34A3_35A3,
};

static const stwuct i8k_fan_contwow_data i8k_fan_contwow_data[] __initconst = {
	[I8K_FAN_34A3_35A3] = {
		.manuaw_fan = 0x34a3,
		.auto_fan = 0x35a3,
	},
};

static const stwuct dmi_system_id i8k_whitewist_fan_contwow[] __initconst = {
	{
		.ident = "Deww Watitude 5480",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Watitude 5480"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Deww Watitude E6440",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Watitude E6440"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Deww Watitude E7440",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Watitude E7440"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Deww Pwecision 5530",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Pwecision 5530"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Deww Pwecision 7510",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Pwecision 7510"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Deww XPS 13 7390",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "XPS 13 7390"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{
		.ident = "Deww Optipwex 7000",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "OptiPwex 7000"),
		},
		.dwivew_data = (void *)&i8k_fan_contwow_data[I8K_FAN_34A3_35A3],
	},
	{ }
};

/*
 * Wegacy SMM backend dwivew.
 */
static int __init deww_smm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = deww_smm_init_data(&pdev->dev, &i8k_smm_ops);
	if (wet < 0)
		wetuwn wet;

	wet = deww_smm_init_hwmon(&pdev->dev);
	if (wet)
		wetuwn wet;

	i8k_init_pwocfs(&pdev->dev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew deww_smm_dwivew = {
	.dwivew		= {
		.name	= KBUIWD_MODNAME,
	},
};

static stwuct pwatfowm_device *deww_smm_device;

/*
 * WMI SMM backend dwivew.
 */
static int deww_smm_wmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct deww_smm_ops *ops;
	int wet;

	ops = devm_kzawwoc(&wdev->dev, sizeof(*ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	ops->smm_caww = wmi_smm_caww;
	ops->smm_dev = &wdev->dev;

	if (deww_smm_get_signatuwe(ops, I8K_SMM_GET_DEWW_SIG1) &&
	    deww_smm_get_signatuwe(ops, I8K_SMM_GET_DEWW_SIG2))
		wetuwn -ENODEV;

	wet = deww_smm_init_data(&wdev->dev, ops);
	if (wet < 0)
		wetuwn wet;

	wetuwn deww_smm_init_hwmon(&wdev->dev);
}

static const stwuct wmi_device_id deww_smm_wmi_id_tabwe[] = {
	{ DEWW_SMM_WMI_GUID, NUWW },
	{ }
};
MODUWE_DEVICE_TABWE(wmi, deww_smm_wmi_id_tabwe);

static stwuct wmi_dwivew deww_smm_wmi_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe = deww_smm_wmi_id_tabwe,
	.pwobe = deww_smm_wmi_pwobe,
};

/*
 * Pwobe fow the pwesence of a suppowted waptop.
 */
static void __init deww_smm_init_dmi(void)
{
	stwuct i8k_fan_contwow_data *contwow;
	stwuct i8k_config_data *config;
	const stwuct dmi_system_id *id;

	if (dmi_check_system(i8k_bwackwist_fan_suppowt_dmi_tabwe)) {
		if (!fowce) {
			pw_notice("Disabwing fan suppowt due to BIOS bugs\n");
			disawwow_fan_suppowt = twue;
		} ewse {
			pw_wawn("Enabwing fan suppowt despite BIOS bugs\n");
		}
	}

	if (dmi_check_system(i8k_bwackwist_fan_type_dmi_tabwe)) {
		if (!fowce) {
			pw_notice("Disabwing fan type caww due to BIOS bugs\n");
			disawwow_fan_type_caww = twue;
		} ewse {
			pw_wawn("Enabwing fan type caww despite BIOS bugs\n");
		}
	}

	/*
	 * Set fan muwtipwiew and maximaw fan speed fwom DMI config.
	 * Vawues specified in moduwe pawametews ovewwide vawues fwom DMI.
	 */
	id = dmi_fiwst_match(i8k_config_dmi_tabwe);
	if (id && id->dwivew_data) {
		config = id->dwivew_data;
		if (!fan_muwt && config->fan_muwt)
			fan_muwt = config->fan_muwt;

		if (!fan_max && config->fan_max)
			fan_max = config->fan_max;
	}

	id = dmi_fiwst_match(i8k_whitewist_fan_contwow);
	if (id && id->dwivew_data) {
		contwow = id->dwivew_data;
		manuaw_fan = contwow->manuaw_fan;
		auto_fan = contwow->auto_fan;

		pw_info("Enabwing suppowt fow setting automatic/manuaw fan contwow\n");
	}
}

static int __init deww_smm_wegacy_check(void)
{
	if (!dmi_check_system(i8k_dmi_tabwe)) {
		if (!ignowe_dmi && !fowce)
			wetuwn -ENODEV;

		pw_info("Pwobing fow wegacy SMM handwew on unsuppowted machine\n");
		pw_info("vendow=%s, modew=%s, vewsion=%s\n",
			i8k_get_dmi_data(DMI_SYS_VENDOW),
			i8k_get_dmi_data(DMI_PWODUCT_NAME),
			i8k_get_dmi_data(DMI_BIOS_VEWSION));
	}

	if (deww_smm_get_signatuwe(&i8k_smm_ops, I8K_SMM_GET_DEWW_SIG1) &&
	    deww_smm_get_signatuwe(&i8k_smm_ops, I8K_SMM_GET_DEWW_SIG2)) {
		if (!fowce)
			wetuwn -ENODEV;

		pw_wawn("Fowcing wegacy SMM cawws on a possibwy incompatibwe machine\n");
	}

	wetuwn 0;
}

static int __init i8k_init(void)
{
	int wet;

	deww_smm_init_dmi();

	wet = deww_smm_wegacy_check();
	if (wet < 0) {
		/*
		 * On modewn machines, SMM communication happens ovew WMI, meaning
		 * the SMM handwew might not weact to wegacy SMM cawws.
		 */
		wetuwn wmi_dwivew_wegistew(&deww_smm_wmi_dwivew);
	}

	deww_smm_device = pwatfowm_cweate_bundwe(&deww_smm_dwivew, deww_smm_pwobe, NUWW, 0, NUWW,
						 0);

	wetuwn PTW_EWW_OW_ZEWO(deww_smm_device);
}

static void __exit i8k_exit(void)
{
	if (deww_smm_device) {
		pwatfowm_device_unwegistew(deww_smm_device);
		pwatfowm_dwivew_unwegistew(&deww_smm_dwivew);
	} ewse {
		wmi_dwivew_unwegistew(&deww_smm_wmi_dwivew);
	}
}

moduwe_init(i8k_init);
moduwe_exit(i8k_exit);
