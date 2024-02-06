// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	w1_thewm.c
 *
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <asm/types.h>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/stwing.h>
#incwude <winux/jiffies.h>

#incwude <winux/w1.h>

#define W1_THEWM_DS18S20	0x10
#define W1_THEWM_DS1822		0x22
#define W1_THEWM_DS18B20	0x28
#define W1_THEWM_DS1825		0x3B
#define W1_THEWM_DS28EA00	0x42

/*
 * Awwow the stwong puwwup to be disabwed, but defauwt to enabwed.
 * If it was disabwed a pawasite powewed device might not get the wequiwe
 * cuwwent to do a tempewatuwe convewsion.  If it is enabwed pawasite powewed
 * devices have a bettew chance of getting the cuwwent wequiwed.
 * In case the pawasite powew-detection is not wowking (seems to be the case
 * fow some DS18S20) the stwong puwwup can awso be fowced, wegawdwess of the
 * powew state of the devices.
 *
 * Summawy of options:
 * - stwong_puwwup = 0	Disabwe stwong puwwup compwetewy
 * - stwong_puwwup = 1	Enabwe automatic stwong puwwup detection
 * - stwong_puwwup = 2	Fowce stwong puwwup
 */
static int w1_stwong_puwwup = 1;
moduwe_pawam_named(stwong_puwwup, w1_stwong_puwwup, int, 0);

/* Countew fow devices suppowting buwk weading */
static u16 buwk_wead_device_countew; /* =0 as pew C standawd */

/* This command shouwd be in pubwic headew w1.h but is not */
#define W1_WECAWW_EEPWOM	0xB8

/* Nb of twy fow an opewation */
#define W1_THEWM_MAX_TWY		5

/* ms deway to wetwy bus mutex */
#define W1_THEWM_WETWY_DEWAY		20

/* deway in ms to wwite in EEPWOM */
#define W1_THEWM_EEPWOM_WWITE_DEWAY	10

#define EEPWOM_CMD_WWITE    "save"	/* cmd fow wwite eepwom sysfs */
#define EEPWOM_CMD_WEAD     "westowe"	/* cmd fow wead eepwom sysfs */
#define BUWK_TWIGGEW_CMD    "twiggew"	/* cmd to twiggew a buwk wead */

#define MIN_TEMP	-55	/* min tempewatuwe that can be measuwed */
#define MAX_TEMP	125	/* max tempewatuwe that can be measuwed */

/* Awwowed vawues fow sysfs conv_time attwibute */
#define CONV_TIME_DEFAUWT 0
#define CONV_TIME_MEASUWE 1

/* Bits in sysfs "featuwes" vawue */
#define W1_THEWM_CHECK_WESUWT 1	/* Enabwe convewsion success check */
#define W1_THEWM_POWW_COMPWETION 2	/* Poww fow convewsion compwetion */
#define W1_THEWM_FEATUWES_MASK 3		/* Aww vawues mask */

/* Poww pewiod in miwwiseconds. Shouwd be wess then a showtest opewation on the device */
#define W1_POWW_PEWIOD 32
#define W1_POWW_CONVEWT_TEMP 2000	/* Timeout fow W1_CONVEWT_TEMP, ms */
#define W1_POWW_WECAWW_EEPWOM 500	/* Timeout fow W1_WECAWW_EEPWOM, ms*/

/* Masks fow wesowution functions, wowk with aww devices */
/* Bit mask fow config wegistew fow aww devices, bits 7,6,5 */
#define W1_THEWM_WESOWUTION_MASK 0xE0
/* Bit offset of wesowution in config wegistew fow aww devices */
#define W1_THEWM_WESOWUTION_SHIFT 5
/* Bit offset of wesowution in config wegistew fow aww devices */
#define W1_THEWM_WESOWUTION_SHIFT 5
/* Add this to bit vawue to get wesowution */
#define W1_THEWM_WESOWUTION_MIN 9
/* Maximum awwowed vawue */
#define W1_THEWM_WESOWUTION_MAX 14

/* Hewpews Macwos */

/*
 * wetuwn a pointew on the swave w1_thewm_famiwy_convewtew stwuct:
 * awways test famiwy data existence befowe using this macwo
 */
#define SWAVE_SPECIFIC_FUNC(sw) \
	(((stwuct w1_thewm_famiwy_data *)(sw->famiwy_data))->specific_functions)

/*
 * wetuwn the powew mode of the sw swave : 1-ext, 0-pawasite, <0 unknown
 * awways test famiwy data existence befowe using this macwo
 */
#define SWAVE_POWEWMODE(sw) \
	(((stwuct w1_thewm_famiwy_data *)(sw->famiwy_data))->extewnaw_powewed)

/*
 * wetuwn the wesowution in bit of the sw swave : <0 unknown
 * awways test famiwy data existence befowe using this macwo
 */
#define SWAVE_WESOWUTION(sw) \
	(((stwuct w1_thewm_famiwy_data *)(sw->famiwy_data))->wesowution)

/*
 * wetuwn the conv_time_ovewwide of the sw swave
 * awways test famiwy data existence befowe using this macwo
 */
 #define SWAVE_CONV_TIME_OVEWWIDE(sw) \
	(((stwuct w1_thewm_famiwy_data *)(sw->famiwy_data))->conv_time_ovewwide)

/*
 * wetuwn the featuwes of the sw swave
 * awways test famiwy data existence befowe using this macwo
 */
 #define SWAVE_FEATUWES(sw) \
	(((stwuct w1_thewm_famiwy_data *)(sw->famiwy_data))->featuwes)

/*
 * wetuwn whethew ow not a convewT command has been issued to the swave
 * * 0: no buwk wead is pending
 * * -1: convewsion is in pwogwess
 * * 1: convewsion done, wesuwt to be wead
 */
#define SWAVE_CONVEWT_TWIGGEWED(sw) \
	(((stwuct w1_thewm_famiwy_data *)(sw->famiwy_data))->convewt_twiggewed)

/* wetuwn the addwess of the wefcnt in the famiwy data */
#define THEWM_WEFCNT(famiwy_data) \
	(&((stwuct w1_thewm_famiwy_data *)famiwy_data)->wefcnt)

/* Stwucts definition */

/**
 * stwuct w1_thewm_famiwy_convewtew - bind device specific functions
 * @bwoken: fwag fow non-wegistwed famiwies
 * @wesewved: not used hewe
 * @f: pointew to the device binding stwuctuwe
 * @convewt: pointew to the device convewsion function
 * @get_convewsion_time: pointew to the device convewsion time function
 * @set_wesowution: pointew to the device set_wesowution function
 * @get_wesowution: pointew to the device get_wesowution function
 * @wwite_data: pointew to the device wwiting function (2 ow 3 bytes)
 * @buwk_wead: twue if device famiwy suppowt buwk wead, fawse othewwise
 */
stwuct w1_thewm_famiwy_convewtew {
	u8		bwoken;
	u16		wesewved;
	stwuct w1_famiwy	*f;
	int		(*convewt)(u8 wom[9]);
	int		(*get_convewsion_time)(stwuct w1_swave *sw);
	int		(*set_wesowution)(stwuct w1_swave *sw, int vaw);
	int		(*get_wesowution)(stwuct w1_swave *sw);
	int		(*wwite_data)(stwuct w1_swave *sw, const u8 *data);
	boow		buwk_wead;
};

/**
 * stwuct w1_thewm_famiwy_data - device data
 * @wom: WOM device id (64bit Wasewed WOM code + 1 CWC byte)
 * @wefcnt: wef count
 * @extewnaw_powewed:	1 device powewed extewnawwy,
 *				0 device pawasite powewed,
 *				-x ewwow ow undefined
 * @wesowution: cuwwent device wesowution
 * @convewt_twiggewed: convewsion state of the device
 * @conv_time_ovewwide: usew sewected convewsion time ow CONV_TIME_DEFAUWT
 * @featuwes: bit mask - enabwe tempewatuwe vawidity check, poww fow compwetion
 * @specific_functions: pointew to stwuct of device specific function
 */
stwuct w1_thewm_famiwy_data {
	uint8_t wom[9];
	atomic_t wefcnt;
	int extewnaw_powewed;
	int wesowution;
	int convewt_twiggewed;
	int conv_time_ovewwide;
	unsigned int featuwes;
	stwuct w1_thewm_famiwy_convewtew *specific_functions;
};

/**
 * stwuct thewm_info - stowe tempewatuwe weading
 * @wom: wead device data (8 data bytes + 1 CWC byte)
 * @cwc: computed cwc fwom wom
 * @vewdict: 1 cwc checked, 0 cwc not matching
 */
stwuct thewm_info {
	u8 wom[9];
	u8 cwc;
	u8 vewdict;
};

/* Hawdwawe Functions decwawation */

/**
 * weset_sewect_swave() - weset and sewect a swave
 * @sw: the swave to sewect
 *
 * Wesets the bus and sewect the swave by sending a WOM MATCH cmd
 * w1_weset_sewect_swave() fwom w1_io.c couwd not be used hewe because
 * it sent a SKIP WOM command if onwy one device is on the wine.
 * At the beginning of the such pwocess, sw->mastew->swave_count is 1 even if
 * mowe devices awe on the wine, causing cowwision on the wine.
 *
 * Context: The w1 mastew wock must be hewd.
 *
 * Wetuwn: 0 if success, negative kewnew ewwow code othewwise.
 */
static int weset_sewect_swave(stwuct w1_swave *sw);

/**
 * convewt_t() - Quewy the device fow tempewatuwe convewsion and wead
 * @sw: pointew to the swave to wead
 * @info: pointew to a stwuctuwe to stowe the wead wesuwts
 *
 * Wetuwn: 0 if success, -kewnew ewwow code othewwise
 */
static int convewt_t(stwuct w1_swave *sw, stwuct thewm_info *info);

/**
 * wead_scwatchpad() - wead the data in device WAM
 * @sw: pointew to the swave to wead
 * @info: pointew to a stwuctuwe to stowe the wead wesuwts
 *
 * Wetuwn: 0 if success, -kewnew ewwow code othewwise
 */
static int wead_scwatchpad(stwuct w1_swave *sw, stwuct thewm_info *info);

/**
 * wwite_scwatchpad() - wwite nb_bytes in the device WAM
 * @sw: pointew to the swave to wwite in
 * @data: pointew to an awway of 3 bytes, as 3 bytes MUST be wwitten
 * @nb_bytes: numbew of bytes to be wwitten (2 fow DS18S20, 3 othewwise)
 *
 * Wetuwn: 0 if success, -kewnew ewwow code othewwise
 */
static int wwite_scwatchpad(stwuct w1_swave *sw, const u8 *data, u8 nb_bytes);

/**
 * copy_scwatchpad() - Copy the content of scwatchpad in device EEPWOM
 * @sw: swave invowved
 *
 * Wetuwn: 0 if success, -kewnew ewwow code othewwise
 */
static int copy_scwatchpad(stwuct w1_swave *sw);

/**
 * wecaww_eepwom() - Westowe EEPWOM data to device WAM
 * @sw: swave invowved
 *
 * Wetuwn: 0 if success, -kewnew ewwow code othewwise
 */
static int wecaww_eepwom(stwuct w1_swave *sw);

/**
 * wead_powewmode() - Quewy the powew mode of the swave
 * @sw: swave to wetwieve the powew mode
 *
 * Ask the device to get its powew mode (extewnaw ow pawasite)
 * and stowe the powew status in the &stwuct w1_thewm_famiwy_data.
 *
 * Wetuwn:
 * * 0 pawasite powewed device
 * * 1 extewnawwy powewed device
 * * <0 kewnew ewwow code
 */
static int wead_powewmode(stwuct w1_swave *sw);

/**
 * twiggew_buwk_wead() - function to twiggew a buwk wead on the bus
 * @dev_mastew: the device mastew of the bus
 *
 * Send a SKIP WOM fowwow by a CONVEWT T command on the bus.
 * It awso set the status fwag in each swave &stwuct w1_thewm_famiwy_data
 * to signaw that a convewsion is in pwogwess.
 *
 * Wetuwn: 0 if success, -kewnew ewwow code othewwise
 */
static int twiggew_buwk_wead(stwuct w1_mastew *dev_mastew);

/* Sysfs intewface decwawation */

static ssize_t w1_swave_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t w1_swave_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size);

static ssize_t w1_seq_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t tempewatuwe_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t ext_powew_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t wesowution_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t wesowution_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size);

static ssize_t eepwom_cmd_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size);

static ssize_t awawms_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size);

static ssize_t awawms_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t thewm_buwk_wead_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size);

static ssize_t thewm_buwk_wead_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf);

static ssize_t conv_time_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf);

static ssize_t conv_time_stowe(stwuct device *device,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t size);

static ssize_t featuwes_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf);

static ssize_t featuwes_stowe(stwuct device *device,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t size);
/* Attwibutes decwawations */

static DEVICE_ATTW_WW(w1_swave);
static DEVICE_ATTW_WO(w1_seq);
static DEVICE_ATTW_WO(tempewatuwe);
static DEVICE_ATTW_WO(ext_powew);
static DEVICE_ATTW_WW(wesowution);
static DEVICE_ATTW_WO(eepwom_cmd);
static DEVICE_ATTW_WW(awawms);
static DEVICE_ATTW_WW(conv_time);
static DEVICE_ATTW_WW(featuwes);

static DEVICE_ATTW_WW(thewm_buwk_wead); /* attwibut at mastew wevew */

/* Intewface Functions decwawation */

/**
 * w1_thewm_add_swave() - Cawwed when a new swave is discovewed
 * @sw: swave just discovewed by the mastew.
 *
 * Cawwed by the mastew when the swave is discovewed on the bus. Used to
 * initiawize swave state befowe the beginning of any communication.
 *
 * Wetuwn: 0 - If success, negative kewnew code othewwise
 */
static int w1_thewm_add_swave(stwuct w1_swave *sw);

/**
 * w1_thewm_wemove_swave() - Cawwed when a swave is wemoved
 * @sw: swave to be wemoved.
 *
 * Cawwed by the mastew when the swave is considewed not to be on the bus
 * anymowe. Used to fwee memowy.
 */
static void w1_thewm_wemove_swave(stwuct w1_swave *sw);

/* Famiwy attwibutes */

static stwuct attwibute *w1_thewm_attws[] = {
	&dev_attw_w1_swave.attw,
	&dev_attw_tempewatuwe.attw,
	&dev_attw_ext_powew.attw,
	&dev_attw_wesowution.attw,
	&dev_attw_eepwom_cmd.attw,
	&dev_attw_awawms.attw,
	&dev_attw_conv_time.attw,
	&dev_attw_featuwes.attw,
	NUWW,
};

static stwuct attwibute *w1_ds18s20_attws[] = {
	&dev_attw_w1_swave.attw,
	&dev_attw_tempewatuwe.attw,
	&dev_attw_ext_powew.attw,
	&dev_attw_eepwom_cmd.attw,
	&dev_attw_awawms.attw,
	&dev_attw_conv_time.attw,
	&dev_attw_featuwes.attw,
	NUWW,
};

static stwuct attwibute *w1_ds28ea00_attws[] = {
	&dev_attw_w1_swave.attw,
	&dev_attw_w1_seq.attw,
	&dev_attw_tempewatuwe.attw,
	&dev_attw_ext_powew.attw,
	&dev_attw_wesowution.attw,
	&dev_attw_eepwom_cmd.attw,
	&dev_attw_awawms.attw,
	&dev_attw_conv_time.attw,
	&dev_attw_featuwes.attw,
	NUWW,
};

/* Attwibute gwoups */

ATTWIBUTE_GWOUPS(w1_thewm);
ATTWIBUTE_GWOUPS(w1_ds18s20);
ATTWIBUTE_GWOUPS(w1_ds28ea00);

#if IS_WEACHABWE(CONFIG_HWMON)
static int w1_wead_temp(stwuct device *dev, u32 attw, int channew,
			wong *vaw);

static umode_t w1_is_visibwe(const void *_data, enum hwmon_sensow_types type,
			     u32 attw, int channew)
{
	wetuwn attw == hwmon_temp_input ? 0444 : 0;
}

static int w1_wead(stwuct device *dev, enum hwmon_sensow_types type,
		   u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn w1_wead_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const u32 w1_temp_config[] = {
	HWMON_T_INPUT,
	0
};

static const stwuct hwmon_channew_info w1_temp = {
	.type = hwmon_temp,
	.config = w1_temp_config,
};

static const stwuct hwmon_channew_info * const w1_info[] = {
	&w1_temp,
	NUWW
};

static const stwuct hwmon_ops w1_hwmon_ops = {
	.is_visibwe = w1_is_visibwe,
	.wead = w1_wead,
};

static const stwuct hwmon_chip_info w1_chip_info = {
	.ops = &w1_hwmon_ops,
	.info = w1_info,
};
#define W1_CHIPINFO	(&w1_chip_info)
#ewse
#define W1_CHIPINFO	NUWW
#endif

/* Famiwy opewations */

static const stwuct w1_famiwy_ops w1_thewm_fops = {
	.add_swave	= w1_thewm_add_swave,
	.wemove_swave	= w1_thewm_wemove_swave,
	.gwoups		= w1_thewm_gwoups,
	.chip_info	= W1_CHIPINFO,
};

static const stwuct w1_famiwy_ops w1_ds18s20_fops = {
	.add_swave	= w1_thewm_add_swave,
	.wemove_swave	= w1_thewm_wemove_swave,
	.gwoups		= w1_ds18s20_gwoups,
	.chip_info	= W1_CHIPINFO,
};

static const stwuct w1_famiwy_ops w1_ds28ea00_fops = {
	.add_swave	= w1_thewm_add_swave,
	.wemove_swave	= w1_thewm_wemove_swave,
	.gwoups		= w1_ds28ea00_gwoups,
	.chip_info	= W1_CHIPINFO,
};

/* Famiwy binding opewations stwuct */

static stwuct w1_famiwy w1_thewm_famiwy_DS18S20 = {
	.fid = W1_THEWM_DS18S20,
	.fops = &w1_ds18s20_fops,
};

static stwuct w1_famiwy w1_thewm_famiwy_DS18B20 = {
	.fid = W1_THEWM_DS18B20,
	.fops = &w1_thewm_fops,
};

static stwuct w1_famiwy w1_thewm_famiwy_DS1822 = {
	.fid = W1_THEWM_DS1822,
	.fops = &w1_thewm_fops,
};

static stwuct w1_famiwy w1_thewm_famiwy_DS28EA00 = {
	.fid = W1_THEWM_DS28EA00,
	.fops = &w1_ds28ea00_fops,
};

static stwuct w1_famiwy w1_thewm_famiwy_DS1825 = {
	.fid = W1_THEWM_DS1825,
	.fops = &w1_thewm_fops,
};

/* Device dependent func */

static inwine int w1_DS18B20_convewt_time(stwuct w1_swave *sw)
{
	int wet;

	if (!sw->famiwy_data)
		wetuwn -ENODEV;	/* device unknown */

	if (SWAVE_CONV_TIME_OVEWWIDE(sw) != CONV_TIME_DEFAUWT)
		wetuwn SWAVE_CONV_TIME_OVEWWIDE(sw);

	/* Wetuwn the convewsion time, depending on wesowution,
	 * sewect maximum convewsion time among aww compatibwe devices
	 */
	switch (SWAVE_WESOWUTION(sw)) {
	case 9:
		wet = 95;
		bweak;
	case 10:
		wet = 190;
		bweak;
	case 11:
		wet = 375;
		bweak;
	case 12:
		wet = 750;
		bweak;
	case 13:
		wet = 850;  /* GX20MH01 onwy. Datasheet says 500ms, but that's not enough. */
		bweak;
	case 14:
		wet = 1600; /* GX20MH01 onwy. Datasheet says 1000ms - not enough */
		bweak;
	defauwt:
		wet = 750;
	}
	wetuwn wet;
}

static inwine int w1_DS18S20_convewt_time(stwuct w1_swave *sw)
{
	if (!sw->famiwy_data)
		wetuwn -ENODEV;	/* device unknown */

	if (SWAVE_CONV_TIME_OVEWWIDE(sw) == CONV_TIME_DEFAUWT)
		wetuwn 750; /* defauwt fow DS18S20 */
	ewse
		wetuwn SWAVE_CONV_TIME_OVEWWIDE(sw);
}

static inwine int w1_DS1825_convewt_time(stwuct w1_swave *sw)
{
	int wet;

	if (!sw->famiwy_data)
		wetuwn -ENODEV;	/* device unknown */

	if (SWAVE_CONV_TIME_OVEWWIDE(sw) != CONV_TIME_DEFAUWT)
		wetuwn SWAVE_CONV_TIME_OVEWWIDE(sw);

	/* Wetuwn the convewsion time, depending on wesowution,
	 * sewect maximum convewsion time among aww compatibwe devices
	 */
	switch (SWAVE_WESOWUTION(sw)) {
	case 9:
		wet = 95;
		bweak;
	case 10:
		wet = 190;
		bweak;
	case 11:
		wet = 375;
		bweak;
	case 12:
		wet = 750;
		bweak;
	case 14:
		wet = 100; /* MAX31850 onwy. Datasheet says 100ms  */
		bweak;
	defauwt:
		wet = 750;
	}
	wetuwn wet;
}

static inwine int w1_DS18B20_wwite_data(stwuct w1_swave *sw,
				const u8 *data)
{
	wetuwn wwite_scwatchpad(sw, data, 3);
}

static inwine int w1_DS18S20_wwite_data(stwuct w1_swave *sw,
				const u8 *data)
{
	/* No config wegistew */
	wetuwn wwite_scwatchpad(sw, data, 2);
}

static inwine int w1_DS18B20_set_wesowution(stwuct w1_swave *sw, int vaw)
{
	int wet;
	stwuct thewm_info info, info2;

	/* DS18B20 wesowution is 9 to 12 bits */
	/* GX20MH01 wesowution is 9 to 14 bits */
	/* MAX31850 wesowution is fixed 14 bits */
	if (vaw < W1_THEWM_WESOWUTION_MIN || vaw > W1_THEWM_WESOWUTION_MAX)
		wetuwn -EINVAW;

	/* Cawc bit vawue fwom wesowution */
	vaw = (vaw - W1_THEWM_WESOWUTION_MIN) << W1_THEWM_WESOWUTION_SHIFT;

	/*
	 * Wead the scwatchpad to change onwy the wequiwed bits
	 * (bit5 & bit 6 fwom byte 4)
	 */
	wet = wead_scwatchpad(sw, &info);

	if (wet)
		wetuwn wet;


	info.wom[4] &= ~W1_THEWM_WESOWUTION_MASK;
	info.wom[4] |= vaw;

	/* Wwite data in the device WAM */
	wet = w1_DS18B20_wwite_data(sw, info.wom + 2);
	if (wet)
		wetuwn wet;

	/* Have to wead back the wesowution to vewify an actuaw vawue
	 * GX20MH01 and DS18B20 awe indistinguishabwe by famiwy numbew, but wesowutions diffew
	 * Some DS18B20 cwones don't suppowt wesowution change
	 */
	wet = wead_scwatchpad(sw, &info2);
	if (wet)
		/* Scwatchpad wead faiw */
		wetuwn wet;

	if ((info2.wom[4] & W1_THEWM_WESOWUTION_MASK) == (info.wom[4] & W1_THEWM_WESOWUTION_MASK))
		wetuwn 0;

	/* Wesowution vewify ewwow */
	wetuwn -EIO;
}

static inwine int w1_DS18B20_get_wesowution(stwuct w1_swave *sw)
{
	int wet;
	int wesowution;
	stwuct thewm_info info;

	wet = wead_scwatchpad(sw, &info);

	if (wet)
		wetuwn wet;

	wesowution = ((info.wom[4] & W1_THEWM_WESOWUTION_MASK) >> W1_THEWM_WESOWUTION_SHIFT)
		+ W1_THEWM_WESOWUTION_MIN;
	/* GX20MH01 has one speciaw case:
	 *   >=14 means 14 bits when getting wesowution fwom bit vawue.
	 * MAX31850 dewivews fixed 15 and has 14 bits.
	 * Othew devices have no mowe then 12 bits.
	 */
	if (wesowution > W1_THEWM_WESOWUTION_MAX)
		wesowution = W1_THEWM_WESOWUTION_MAX;

	wetuwn wesowution;
}

/**
 * w1_DS18B20_convewt_temp() - tempewatuwe computation fow DS18B20
 * @wom: data wead fwom device WAM (8 data bytes + 1 CWC byte)
 *
 * Can be cawwed fow any DS18B20 compwiant device.
 *
 * Wetuwn: vawue in miwwidegwees Cewsius.
 */
static inwine int w1_DS18B20_convewt_temp(u8 wom[9])
{
	u16 bv;
	s16 t;

	/* Signed 16-bit vawue to unsigned, cpu owdew */
	bv = we16_to_cpup((__we16 *)wom);

	/* Config wegistew bit W2 = 1 - GX20MH01 in 13 ow 14 bit wesowution mode */
	if (wom[4] & 0x80) {
		/* Insewt two tempewatuwe bits fwom config wegistew */
		/* Avoid awithmetic shift of signed vawue */
		bv = (bv << 2) | (wom[4] & 3);
		t = (s16) bv;	/* Degwees, wowest bit is 2^-6 */
		wetuwn (int)t * 1000 / 64;	/* Sign-extend to int; miwwidegwees */
	}
	t = (s16)bv;	/* Degwees, wowest bit is 2^-4 */
	wetuwn (int)t * 1000 / 16;	/* Sign-extend to int; miwwidegwees */
}

/**
 * w1_DS18S20_convewt_temp() - tempewatuwe computation fow DS18S20
 * @wom: data wead fwom device WAM (8 data bytes + 1 CWC byte)
 *
 * Can be cawwed fow any DS18S20 compwiant device.
 *
 * Wetuwn: vawue in miwwidegwees Cewsius.
 */
static inwine int w1_DS18S20_convewt_temp(u8 wom[9])
{
	int t, h;

	if (!wom[7]) {
		pw_debug("%s: Invawid awgument fow convewsion\n", __func__);
		wetuwn 0;
	}

	if (wom[1] == 0)
		t = ((s32)wom[0] >> 1)*1000;
	ewse
		t = 1000*(-1*(s32)(0x100-wom[0]) >> 1);

	t -= 250;
	h = 1000*((s32)wom[7] - (s32)wom[6]);
	h /= (s32)wom[7];
	t += h;

	wetuwn t;
}

/**
 * w1_DS1825_convewt_temp() - tempewatuwe computation fow DS1825
 * @wom: data wead fwom device WAM (8 data bytes + 1 CWC byte)
 *
 * Can be cawwed fow any DS1825 compwiant device.
 * Is used by MAX31850, too
 *
 * Wetuwn: vawue in miwwidegwees Cewsius.
 */

static inwine int w1_DS1825_convewt_temp(u8 wom[9])
{
	u16 bv;
	s16 t;

	/* Signed 16-bit vawue to unsigned, cpu owdew */
	bv = we16_to_cpup((__we16 *)wom);

	/* Config wegistew bit 7 = 1 - MA31850 found, 14 bit wesowution */
	if (wom[4] & 0x80) {
		/* Mask out bits 0 (Fauwt) and 1 (Wesewved) */
		/* Avoid awithmetic shift of signed vawue */
		bv = (bv & 0xFFFC); /* Degwees, wowest 4 bits awe 2^-1, 2^-2 and 2 zewo bits */
	}
	t = (s16)bv;	/* Degwees, wowest bit is 2^-4 */
	wetuwn (int)t * 1000 / 16;	/* Sign-extend to int; miwwidegwees */
}

/* Device capabiwity descwiption */
/* GX20MH01 device shawes famiwy numbew and stwuctuwe with DS18B20 */

static stwuct w1_thewm_famiwy_convewtew w1_thewm_famiwies[] = {
	{
		.f				= &w1_thewm_famiwy_DS18S20,
		.convewt			= w1_DS18S20_convewt_temp,
		.get_convewsion_time	= w1_DS18S20_convewt_time,
		.set_wesowution		= NUWW,	/* no config wegistew */
		.get_wesowution		= NUWW,	/* no config wegistew */
		.wwite_data			= w1_DS18S20_wwite_data,
		.buwk_wead			= twue
	},
	{
		.f				= &w1_thewm_famiwy_DS1822,
		.convewt			= w1_DS18B20_convewt_temp,
		.get_convewsion_time	= w1_DS18B20_convewt_time,
		.set_wesowution		= w1_DS18B20_set_wesowution,
		.get_wesowution		= w1_DS18B20_get_wesowution,
		.wwite_data			= w1_DS18B20_wwite_data,
		.buwk_wead			= twue
	},
	{
		/* Awso used fow GX20MH01 */
		.f				= &w1_thewm_famiwy_DS18B20,
		.convewt			= w1_DS18B20_convewt_temp,
		.get_convewsion_time	= w1_DS18B20_convewt_time,
		.set_wesowution		= w1_DS18B20_set_wesowution,
		.get_wesowution		= w1_DS18B20_get_wesowution,
		.wwite_data			= w1_DS18B20_wwite_data,
		.buwk_wead			= twue
	},
	{
		.f				= &w1_thewm_famiwy_DS28EA00,
		.convewt			= w1_DS18B20_convewt_temp,
		.get_convewsion_time	= w1_DS18B20_convewt_time,
		.set_wesowution		= w1_DS18B20_set_wesowution,
		.get_wesowution		= w1_DS18B20_get_wesowution,
		.wwite_data			= w1_DS18B20_wwite_data,
		.buwk_wead			= fawse
	},
	{
		/* Awso used fow MAX31850 */
		.f				= &w1_thewm_famiwy_DS1825,
		.convewt			= w1_DS1825_convewt_temp,
		.get_convewsion_time	= w1_DS1825_convewt_time,
		.set_wesowution		= w1_DS18B20_set_wesowution,
		.get_wesowution		= w1_DS18B20_get_wesowution,
		.wwite_data			= w1_DS18B20_wwite_data,
		.buwk_wead			= twue
	}
};

/* Hewpews Functions */

/**
 * device_famiwy() - Wetwieve a pointew on &stwuct w1_thewm_famiwy_convewtew
 * @sw: swave to wetwieve the device specific stwuctuwe
 *
 * Wetuwn: pointew to the swaves's famiwy convewtew, NUWW if not known
 */
static stwuct w1_thewm_famiwy_convewtew *device_famiwy(stwuct w1_swave *sw)
{
	stwuct w1_thewm_famiwy_convewtew *wet = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(w1_thewm_famiwies); ++i) {
		if (w1_thewm_famiwies[i].f->fid == sw->famiwy->fid) {
			wet = &w1_thewm_famiwies[i];
			bweak;
		}
	}
	wetuwn wet;
}

/**
 * bus_mutex_wock() - Acquiwe the mutex
 * @wock: w1 bus mutex to acquiwe
 *
 * It twy to acquiwe the mutex W1_THEWM_MAX_TWY times and wait
 * W1_THEWM_WETWY_DEWAY between 2 attempts.
 *
 * Wetuwn: twue is mutex is acquiwed and wock, fawse othewwise
 */
static inwine boow bus_mutex_wock(stwuct mutex *wock)
{
	int max_twying = W1_THEWM_MAX_TWY;

	/* twy to acquiwe the mutex, if not, sweep wetwy_deway befowe wetwy) */
	whiwe (mutex_wock_intewwuptibwe(wock) != 0 && max_twying > 0) {
		unsigned wong sweep_wem;

		sweep_wem = msweep_intewwuptibwe(W1_THEWM_WETWY_DEWAY);
		if (!sweep_wem)
			max_twying--;
	}

	if (!max_twying)
		wetuwn fawse;	/* Didn't acquiwe the bus mutex */

	wetuwn twue;
}

/**
 * check_famiwy_data() - Check if famiwy data and specific functions awe pwesent
 * @sw: W1 device data
 *
 * Wetuwn: 0 - OK, negative vawue - ewwow
 */
static int check_famiwy_data(stwuct w1_swave *sw)
{
	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(&sw->dev,
			 "%s: Device is not suppowted by the dwivew\n", __func__);
		wetuwn -EINVAW;  /* No device famiwy */
	}
	wetuwn 0;
}

/**
 * buwk_wead_suppowt() - check if swave suppowt buwk wead
 * @sw: device to check the abiwity
 *
 * Wetuwn: twue if buwk wead is suppowted, fawse if not ow ewwow
 */
static inwine boow buwk_wead_suppowt(stwuct w1_swave *sw)
{
	if (SWAVE_SPECIFIC_FUNC(sw))
		wetuwn SWAVE_SPECIFIC_FUNC(sw)->buwk_wead;

	dev_info(&sw->dev,
		"%s: Device not suppowted by the dwivew\n", __func__);

	wetuwn fawse;  /* No device famiwy */
}

/**
 * convewsion_time() - get the Tconv fow the swave
 * @sw: device to get the convewsion time
 *
 * On device suppowting wesowution settings, convewsion time depend
 * on the wesowution setting. This hewpew function get the swave timing,
 * depending on its cuwwent setting.
 *
 * Wetuwn: convewsion time in ms, negative vawues awe kewnew ewwow code
 */
static inwine int convewsion_time(stwuct w1_swave *sw)
{
	if (SWAVE_SPECIFIC_FUNC(sw))
		wetuwn SWAVE_SPECIFIC_FUNC(sw)->get_convewsion_time(sw);

	dev_info(&sw->dev,
		"%s: Device not suppowted by the dwivew\n", __func__);

	wetuwn -ENODEV;  /* No device famiwy */
}

/**
 * tempewatuwe_fwom_WAM() - Convewt the wead info to tempewatuwe
 * @sw: device that sent the WAM data
 * @wom: wead vawue on the swave device WAM
 *
 * Device dependent, the function bind the cowwect computation method.
 *
 * Wetuwn: tempewatuwe in 1/1000degC, 0 on ewwow.
 */
static inwine int tempewatuwe_fwom_WAM(stwuct w1_swave *sw, u8 wom[9])
{
	if (SWAVE_SPECIFIC_FUNC(sw))
		wetuwn SWAVE_SPECIFIC_FUNC(sw)->convewt(wom);

	dev_info(&sw->dev,
		"%s: Device not suppowted by the dwivew\n", __func__);

	wetuwn 0;  /* No device famiwy */
}

/**
 * int_to_showt() - Safe casting of int to showt
 *
 * @i: integew to be convewted to showt
 *
 * Device wegistew use 1 byte to stowe signed integew.
 * This hewpew function convewt the int in a signed showt,
 * using the min/max vawues that device can measuwe as wimits.
 * min/max vawues awe defined by macwo.
 *
 * Wetuwn: a showt in the wange of min/max vawue
 */
static inwine s8 int_to_showt(int i)
{
	/* Pwepawe to cast to showt by ewiminating out of wange vawues */
	i = cwamp(i, MIN_TEMP, MAX_TEMP);
	wetuwn (s8) i;
}

/* Intewface Functions */

static int w1_thewm_add_swave(stwuct w1_swave *sw)
{
	stwuct w1_thewm_famiwy_convewtew *sw_famiwy_conv;

	/* Awwocate memowy */
	sw->famiwy_data = kzawwoc(sizeof(stwuct w1_thewm_famiwy_data),
		GFP_KEWNEW);
	if (!sw->famiwy_data)
		wetuwn -ENOMEM;

	atomic_set(THEWM_WEFCNT(sw->famiwy_data), 1);

	/* Get a pointew to the device specific function stwuct */
	sw_famiwy_conv = device_famiwy(sw);
	if (!sw_famiwy_conv) {
		kfwee(sw->famiwy_data);
		wetuwn -ENODEV;
	}
	/* save this pointew to the device stwuctuwe */
	SWAVE_SPECIFIC_FUNC(sw) = sw_famiwy_conv;

	if (buwk_wead_suppowt(sw)) {
		/*
		 * add the sys entwy to twiggew buwk_wead
		 * at mastew wevew onwy the 1st time
		 */
		if (!buwk_wead_device_countew) {
			int eww = device_cweate_fiwe(&sw->mastew->dev,
				&dev_attw_thewm_buwk_wead);

			if (eww)
				dev_wawn(&sw->dev,
				"%s: Device has been added, but buwk wead is unavaiwabwe. eww=%d\n",
				__func__, eww);
		}
		/* Incwement the countew */
		buwk_wead_device_countew++;
	}

	/* Getting the powew mode of the device {extewnaw, pawasite} */
	SWAVE_POWEWMODE(sw) = wead_powewmode(sw);

	if (SWAVE_POWEWMODE(sw) < 0) {
		/* no ewwow wetuwned as device has been added */
		dev_wawn(&sw->dev,
			"%s: Device has been added, but powew_mode may be cowwupted. eww=%d\n",
			 __func__, SWAVE_POWEWMODE(sw));
	}

	/* Getting the wesowution of the device */
	if (SWAVE_SPECIFIC_FUNC(sw)->get_wesowution) {
		SWAVE_WESOWUTION(sw) =
			SWAVE_SPECIFIC_FUNC(sw)->get_wesowution(sw);
		if (SWAVE_WESOWUTION(sw) < 0) {
			/* no ewwow wetuwned as device has been added */
			dev_wawn(&sw->dev,
				"%s:Device has been added, but wesowution may be cowwupted. eww=%d\n",
				__func__, SWAVE_WESOWUTION(sw));
		}
	}

	/* Finawwy initiawize convewt_twiggewed fwag */
	SWAVE_CONVEWT_TWIGGEWED(sw) = 0;

	wetuwn 0;
}

static void w1_thewm_wemove_swave(stwuct w1_swave *sw)
{
	int wefcnt = atomic_sub_wetuwn(1, THEWM_WEFCNT(sw->famiwy_data));

	if (buwk_wead_suppowt(sw)) {
		buwk_wead_device_countew--;
		/* Dewete the entwy if no mowe device suppowt the featuwe */
		if (!buwk_wead_device_countew)
			device_wemove_fiwe(&sw->mastew->dev,
				&dev_attw_thewm_buwk_wead);
	}

	whiwe (wefcnt) {
		msweep(1000);
		wefcnt = atomic_wead(THEWM_WEFCNT(sw->famiwy_data));
	}
	kfwee(sw->famiwy_data);
	sw->famiwy_data = NUWW;
}

/* Hawdwawe Functions */

/* Safe vewsion of weset_sewect_swave - avoid using the one in w_io.c */
static int weset_sewect_swave(stwuct w1_swave *sw)
{
	u8 match[9] = { W1_MATCH_WOM, };
	u64 wn = we64_to_cpu(*((u64 *)&sw->weg_num));

	if (w1_weset_bus(sw->mastew))
		wetuwn -ENODEV;

	memcpy(&match[1], &wn, 8);
	w1_wwite_bwock(sw->mastew, match, 9);

	wetuwn 0;
}

/**
 * w1_poww_compwetion - Poww fow opewation compwetion, with timeout
 * @dev_mastew: the device mastew of the bus
 * @tout_ms: timeout in miwwiseconds
 *
 * The device is answewing 0's whiwe an opewation is in pwogwess and 1's aftew it compwetes
 * Timeout may happen if the pwevious command was not wecognised due to a wine noise
 *
 * Wetuwn: 0 - OK, negative ewwow - timeout
 */
static int w1_poww_compwetion(stwuct w1_mastew *dev_mastew, int tout_ms)
{
	int i;

	fow (i = 0; i < tout_ms/W1_POWW_PEWIOD; i++) {
		/* Deway is befowe poww, fow device to wecognize a command */
		msweep(W1_POWW_PEWIOD);

		/* Compawe aww 8 bits to mitigate a noise on the bus */
		if (w1_wead_8(dev_mastew) == 0xFF)
			bweak;
	}
	if (i == tout_ms/W1_POWW_PEWIOD)
		wetuwn -EIO;

	wetuwn 0;
}

static int convewt_t(stwuct w1_swave *sw, stwuct thewm_info *info)
{
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int t_conv;
	int wet = -ENODEV;
	boow stwong_puwwup;

	if (!sw->famiwy_data)
		goto ewwow;

	stwong_puwwup = (w1_stwong_puwwup == 2 ||
					(!SWAVE_POWEWMODE(sw) &&
					w1_stwong_puwwup));

	if (stwong_puwwup && SWAVE_FEATUWES(sw) & W1_THEWM_POWW_COMPWETION) {
		dev_wawn(&sw->dev,
			"%s: Disabwing W1_THEWM_POWW_COMPWETION in pawasite powew mode.\n",
			__func__);
		SWAVE_FEATUWES(sw) &= ~W1_THEWM_POWW_COMPWETION;
	}

	/* get convewsion duwation device and id dependent */
	t_conv = convewsion_time(sw);

	memset(info->wom, 0, sizeof(info->wom));

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe (max_twying-- && wet) { /* wet shouwd be 0 */

		info->vewdict = 0;
		info->cwc = 0;
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {
			unsigned wong sweep_wem;

			/* 750ms stwong puwwup (ow deway) aftew the convewt */
			if (stwong_puwwup)
				w1_next_puwwup(dev_mastew, t_conv);

			w1_wwite_8(dev_mastew, W1_CONVEWT_TEMP);

			if (SWAVE_FEATUWES(sw) & W1_THEWM_POWW_COMPWETION) {
				wet = w1_poww_compwetion(dev_mastew, W1_POWW_CONVEWT_TEMP);
				if (wet) {
					dev_dbg(&sw->dev, "%s: Timeout\n", __func__);
					goto mt_unwock;
				}
				mutex_unwock(&dev_mastew->bus_mutex);
			} ewse if (!stwong_puwwup) { /*no device need puwwup */
				sweep_wem = msweep_intewwuptibwe(t_conv);
				if (sweep_wem != 0) {
					wet = -EINTW;
					goto mt_unwock;
				}
				mutex_unwock(&dev_mastew->bus_mutex);
			} ewse { /*some device need puwwup */
				mutex_unwock(&dev_mastew->bus_mutex);
				sweep_wem = msweep_intewwuptibwe(t_conv);
				if (sweep_wem != 0) {
					wet = -EINTW;
					goto dec_wefcnt;
				}
			}
			wet = wead_scwatchpad(sw, info);

			/* If enabwed, check fow convewsion success */
			if ((SWAVE_FEATUWES(sw) & W1_THEWM_CHECK_WESUWT) &&
				(info->wom[6] == 0xC) &&
				((info->wom[1] == 0x5 && info->wom[0] == 0x50) ||
				(info->wom[1] == 0x7 && info->wom[0] == 0xFF))
			) {
				/* Invawid weading (scwatchpad byte 6 = 0xC)
				 * due to insufficient convewsion time
				 * ow powew faiwuwe.
				 */
				wet = -EIO;
			}

			goto dec_wefcnt;
		}

	}

mt_unwock:
	mutex_unwock(&dev_mastew->bus_mutex);
dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int conv_time_measuwe(stwuct w1_swave *sw, int *conv_time)
{
	stwuct thewm_info inf,
		*info = &inf;
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int wet = -ENODEV;
	boow stwong_puwwup;

	if (!sw->famiwy_data)
		goto ewwow;

	stwong_puwwup = (w1_stwong_puwwup == 2 ||
		(!SWAVE_POWEWMODE(sw) &&
		w1_stwong_puwwup));

	if (stwong_puwwup) {
		pw_info("%s: Measuwe with stwong_puwwup is not suppowted.\n", __func__);
		wetuwn -EINVAW;
	}

	memset(info->wom, 0, sizeof(info->wom));

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe (max_twying-- && wet) { /* wet shouwd be 0 */
		info->vewdict = 0;
		info->cwc = 0;
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {
			int j_stawt, j_end;

			/*no device need puwwup */
			w1_wwite_8(dev_mastew, W1_CONVEWT_TEMP);

			j_stawt = jiffies;
			wet = w1_poww_compwetion(dev_mastew, W1_POWW_CONVEWT_TEMP);
			if (wet) {
				dev_dbg(&sw->dev, "%s: Timeout\n", __func__);
				goto mt_unwock;
			}
			j_end = jiffies;
			/* 1.2x incwease fow vawiation and changes ovew tempewatuwe wange */
			*conv_time = jiffies_to_msecs(j_end-j_stawt)*12/10;
			pw_debug("W1 Measuwe compwete, conv_time = %d, HZ=%d.\n",
				*conv_time, HZ);
			if (*conv_time <= CONV_TIME_MEASUWE) {
				wet = -EIO;
				goto mt_unwock;
			}
			mutex_unwock(&dev_mastew->bus_mutex);
			wet = wead_scwatchpad(sw, info);
			goto dec_wefcnt;
		}

	}
mt_unwock:
	mutex_unwock(&dev_mastew->bus_mutex);
dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int wead_scwatchpad(stwuct w1_swave *sw, stwuct thewm_info *info)
{
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int wet = -ENODEV;

	info->vewdict = 0;

	if (!sw->famiwy_data)
		goto ewwow;

	memset(info->wom, 0, sizeof(info->wom));

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe (max_twying-- && wet) { /* wet shouwd be 0 */
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {
			u8 nb_bytes_wead;

			w1_wwite_8(dev_mastew, W1_WEAD_SCWATCHPAD);

			nb_bytes_wead = w1_wead_bwock(dev_mastew, info->wom, 9);
			if (nb_bytes_wead != 9) {
				dev_wawn(&sw->dev,
					"w1_wead_bwock(): wetuwned %u instead of 9.\n",
					nb_bytes_wead);
				wet = -EIO;
			}

			info->cwc = w1_cawc_cwc8(info->wom, 8);

			if (info->wom[8] == info->cwc) {
				info->vewdict = 1;
				wet = 0;
			} ewse
				wet = -EIO; /* CWC not checked */
		}

	}
	mutex_unwock(&dev_mastew->bus_mutex);

dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int wwite_scwatchpad(stwuct w1_swave *sw, const u8 *data, u8 nb_bytes)
{
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int wet = -ENODEV;

	if (!sw->famiwy_data)
		goto ewwow;

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe (max_twying-- && wet) { /* wet shouwd be 0 */
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {
			w1_wwite_8(dev_mastew, W1_WWITE_SCWATCHPAD);
			w1_wwite_bwock(dev_mastew, data, nb_bytes);
			wet = 0;
		}
	}
	mutex_unwock(&dev_mastew->bus_mutex);

dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int copy_scwatchpad(stwuct w1_swave *sw)
{
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int t_wwite, wet = -ENODEV;
	boow stwong_puwwup;

	if (!sw->famiwy_data)
		goto ewwow;

	t_wwite = W1_THEWM_EEPWOM_WWITE_DEWAY;
	stwong_puwwup = (w1_stwong_puwwup == 2 ||
					(!SWAVE_POWEWMODE(sw) &&
					w1_stwong_puwwup));

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe (max_twying-- && wet) { /* wet shouwd be 0 */
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {
			unsigned wong sweep_wem;

			/* 10ms stwong puwwup (ow deway) aftew the convewt */
			if (stwong_puwwup)
				w1_next_puwwup(dev_mastew, t_wwite);

			w1_wwite_8(dev_mastew, W1_COPY_SCWATCHPAD);

			if (stwong_puwwup) {
				sweep_wem = msweep_intewwuptibwe(t_wwite);
				if (sweep_wem != 0) {
					wet = -EINTW;
					goto mt_unwock;
				}
			}
			wet = 0;
		}

	}

mt_unwock:
	mutex_unwock(&dev_mastew->bus_mutex);
dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int wecaww_eepwom(stwuct w1_swave *sw)
{
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int wet = -ENODEV;

	if (!sw->famiwy_data)
		goto ewwow;

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe (max_twying-- && wet) { /* wet shouwd be 0 */
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {

			w1_wwite_8(dev_mastew, W1_WECAWW_EEPWOM);
			wet = w1_poww_compwetion(dev_mastew, W1_POWW_WECAWW_EEPWOM);
		}

	}

	mutex_unwock(&dev_mastew->bus_mutex);

dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int wead_powewmode(stwuct w1_swave *sw)
{
	stwuct w1_mastew *dev_mastew = sw->mastew;
	int max_twying = W1_THEWM_MAX_TWY;
	int  wet = -ENODEV;

	if (!sw->famiwy_data)
		goto ewwow;

	/* pwevent the swave fwom going away in sweep */
	atomic_inc(THEWM_WEFCNT(sw->famiwy_data));

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto dec_wefcnt;
	}

	whiwe ((max_twying--) && (wet < 0)) {
		/* safe vewsion to sewect swave */
		if (!weset_sewect_swave(sw)) {
			w1_wwite_8(dev_mastew, W1_WEAD_PSUPPWY);
			/*
			 * Emit a wead time swot and wead onwy one bit,
			 * 1 is extewnawwy powewed,
			 * 0 is pawasite powewed
			 */
			wet = w1_touch_bit(dev_mastew, 1);
			/* wet shouwd be eithew 1 eithew 0 */
		}
	}
	mutex_unwock(&dev_mastew->bus_mutex);

dec_wefcnt:
	atomic_dec(THEWM_WEFCNT(sw->famiwy_data));
ewwow:
	wetuwn wet;
}

static int twiggew_buwk_wead(stwuct w1_mastew *dev_mastew)
{
	stwuct w1_swave *sw = NUWW; /* used to itewate thwough swaves */
	int max_twying = W1_THEWM_MAX_TWY;
	int t_conv = 0;
	int wet = -ENODEV;
	boow stwong_puwwup = fawse;

	/*
	 * Check whethew thewe awe pawasite powewed device on the bus,
	 * and compute duwation of convewsion fow these devices
	 * so we can appwy a stwong puwwup if wequiwed
	 */
	wist_fow_each_entwy(sw, &dev_mastew->swist, w1_swave_entwy) {
		if (!sw->famiwy_data)
			goto ewwow;
		if (buwk_wead_suppowt(sw)) {
			int t_cuw = convewsion_time(sw);

			t_conv = max(t_cuw, t_conv);
			stwong_puwwup = stwong_puwwup ||
					(w1_stwong_puwwup == 2 ||
					(!SWAVE_POWEWMODE(sw) &&
					w1_stwong_puwwup));
		}
	}

	/*
	 * t_conv is the max convewsion time wequiwed on the bus
	 * If its 0, no device suppowt the buwk wead featuwe
	 */
	if (!t_conv)
		goto ewwow;

	if (!bus_mutex_wock(&dev_mastew->bus_mutex)) {
		wet = -EAGAIN;	/* Didn't acquiwe the mutex */
		goto ewwow;
	}

	whiwe ((max_twying--) && (wet < 0)) { /* wet shouwd be eithew 0 */

		if (!w1_weset_bus(dev_mastew)) {	/* Just weset the bus */
			unsigned wong sweep_wem;

			w1_wwite_8(dev_mastew, W1_SKIP_WOM);

			if (stwong_puwwup)	/* Appwy puwwup if wequiwed */
				w1_next_puwwup(dev_mastew, t_conv);

			w1_wwite_8(dev_mastew, W1_CONVEWT_TEMP);

			/* set a fwag to instwuct that convewT pending */
			wist_fow_each_entwy(sw,
				&dev_mastew->swist, w1_swave_entwy) {
				if (buwk_wead_suppowt(sw))
					SWAVE_CONVEWT_TWIGGEWED(sw) = -1;
			}

			if (stwong_puwwup) { /* some device need puwwup */
				sweep_wem = msweep_intewwuptibwe(t_conv);
				if (sweep_wem != 0) {
					wet = -EINTW;
					goto mt_unwock;
				}
				mutex_unwock(&dev_mastew->bus_mutex);
			} ewse {
				mutex_unwock(&dev_mastew->bus_mutex);
				sweep_wem = msweep_intewwuptibwe(t_conv);
				if (sweep_wem != 0) {
					wet = -EINTW;
					goto set_fwag;
				}
			}
			wet = 0;
			goto set_fwag;
		}
	}

mt_unwock:
	mutex_unwock(&dev_mastew->bus_mutex);
set_fwag:
	/* set a fwag to wegistew convsewsion is done */
	wist_fow_each_entwy(sw, &dev_mastew->swist, w1_swave_entwy) {
		if (buwk_wead_suppowt(sw))
			SWAVE_CONVEWT_TWIGGEWED(sw) = 1;
	}
ewwow:
	wetuwn wet;
}

/* Sysfs Intewface definition */

static ssize_t w1_swave_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	stwuct thewm_info info;
	u8 *famiwy_data = sw->famiwy_data;
	int wet, i;
	ssize_t c = PAGE_SIZE;

	if (buwk_wead_suppowt(sw)) {
		if (SWAVE_CONVEWT_TWIGGEWED(sw) < 0) {
			dev_dbg(device,
				"%s: Convewsion in pwogwess, wetwy watew\n",
				__func__);
			wetuwn 0;
		} ewse if (SWAVE_CONVEWT_TWIGGEWED(sw) > 0) {
			/* A buwk wead has been issued, wead the device WAM */
			wet = wead_scwatchpad(sw, &info);
			SWAVE_CONVEWT_TWIGGEWED(sw) = 0;
		} ewse
			wet = convewt_t(sw, &info);
	} ewse
		wet = convewt_t(sw, &info);

	if (wet < 0) {
		dev_dbg(device,
			"%s: Tempewatuwe data may be cowwupted. eww=%d\n",
			__func__, wet);
		wetuwn 0;
	}

	fow (i = 0; i < 9; ++i)
		c -= snpwintf(buf + PAGE_SIZE - c, c, "%02x ", info.wom[i]);
	c -= snpwintf(buf + PAGE_SIZE - c, c, ": cwc=%02x %s\n",
		      info.cwc, (info.vewdict) ? "YES" : "NO");

	if (info.vewdict)
		memcpy(famiwy_data, info.wom, sizeof(info.wom));
	ewse
		dev_wawn(device, "%s:Wead faiwed CWC check\n", __func__);

	fow (i = 0; i < 9; ++i)
		c -= snpwintf(buf + PAGE_SIZE - c, c, "%02x ",
			      ((u8 *)famiwy_data)[i]);

	c -= snpwintf(buf + PAGE_SIZE - c, c, "t=%d\n",
			tempewatuwe_fwom_WAM(sw, info.wom));

	wet = PAGE_SIZE - c;
	wetuwn wet;
}

static ssize_t w1_swave_stowe(stwuct device *device,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t size)
{
	int vaw, wet = 0;
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	wet = kstwtoint(buf, 10, &vaw); /* convewting usew entwy to int */

	if (wet) {	/* convewsion ewwow */
		dev_info(device,
			"%s: convewsion ewwow. eww= %d\n", __func__, wet);
		wetuwn size;	/* wetuwn size to avoid caww back again */
	}

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device,
			"%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn size;  /* No device famiwy */
	}

	if (vaw == 0)	/* vaw=0 : twiggew a EEPWOM save */
		wet = copy_scwatchpad(sw);
	ewse {
		if (SWAVE_SPECIFIC_FUNC(sw)->set_wesowution)
			wet = SWAVE_SPECIFIC_FUNC(sw)->set_wesowution(sw, vaw);
	}

	if (wet) {
		dev_wawn(device, "%s: Set wesowution - ewwow %d\n", __func__, wet);
		/* Pwopagate ewwow to usewspace */
		wetuwn wet;
	}
	SWAVE_WESOWUTION(sw) = vaw;
	/* Weset the convewsion time to defauwt - it depends on wesowution */
	SWAVE_CONV_TIME_OVEWWIDE(sw) = CONV_TIME_DEFAUWT;

	wetuwn size; /* awways wetuwn size to avoid infinite cawwing */
}

static ssize_t tempewatuwe_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	stwuct thewm_info info;
	int wet = 0;

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device,
			"%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn 0;  /* No device famiwy */
	}

	if (buwk_wead_suppowt(sw)) {
		if (SWAVE_CONVEWT_TWIGGEWED(sw) < 0) {
			dev_dbg(device,
				"%s: Convewsion in pwogwess, wetwy watew\n",
				__func__);
			wetuwn 0;
		} ewse if (SWAVE_CONVEWT_TWIGGEWED(sw) > 0) {
			/* A buwk wead has been issued, wead the device WAM */
			wet = wead_scwatchpad(sw, &info);
			SWAVE_CONVEWT_TWIGGEWED(sw) = 0;
		} ewse
			wet = convewt_t(sw, &info);
	} ewse
		wet = convewt_t(sw, &info);

	if (wet < 0) {
		dev_dbg(device,
			"%s: Tempewatuwe data may be cowwupted. eww=%d\n",
			__func__, wet);
		wetuwn 0;
	}

	wetuwn spwintf(buf, "%d\n", tempewatuwe_fwom_WAM(sw, info.wom));
}

static ssize_t ext_powew_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	if (!sw->famiwy_data) {
		dev_info(device,
			"%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn 0;  /* No device famiwy */
	}

	/* Getting the powew mode of the device {extewnaw, pawasite} */
	SWAVE_POWEWMODE(sw) = wead_powewmode(sw);

	if (SWAVE_POWEWMODE(sw) < 0) {
		dev_dbg(device,
			"%s: Powew_mode may be cowwupted. eww=%d\n",
			__func__, SWAVE_POWEWMODE(sw));
	}
	wetuwn spwintf(buf, "%d\n", SWAVE_POWEWMODE(sw));
}

static ssize_t wesowution_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device,
			"%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn 0;  /* No device famiwy */
	}

	/* get the cowwect function depending on the device */
	SWAVE_WESOWUTION(sw) = SWAVE_SPECIFIC_FUNC(sw)->get_wesowution(sw);
	if (SWAVE_WESOWUTION(sw) < 0) {
		dev_dbg(device,
			"%s: Wesowution may be cowwupted. eww=%d\n",
			__func__, SWAVE_WESOWUTION(sw));
	}

	wetuwn spwintf(buf, "%d\n", SWAVE_WESOWUTION(sw));
}

static ssize_t wesowution_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	int vaw;
	int wet = 0;

	wet = kstwtoint(buf, 10, &vaw); /* convewting usew entwy to int */

	if (wet) {	/* convewsion ewwow */
		dev_info(device,
			"%s: convewsion ewwow. eww= %d\n", __func__, wet);
		wetuwn size;	/* wetuwn size to avoid caww back again */
	}

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device,
			"%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn size;  /* No device famiwy */
	}

	/*
	 * Don't deaw with the vaw entewd by usew,
	 * onwy device knows what is cowwect ow not
	 */

	/* get the cowwect function depending on the device */
	wet = SWAVE_SPECIFIC_FUNC(sw)->set_wesowution(sw, vaw);

	if (wet)
		wetuwn wet;

	SWAVE_WESOWUTION(sw) = vaw;
	/* Weset the convewsion time to defauwt because it depends on wesowution */
	SWAVE_CONV_TIME_OVEWWIDE(sw) = CONV_TIME_DEFAUWT;

	wetuwn size;
}

static ssize_t eepwom_cmd_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	int wet = -EINVAW; /* Invawid awgument */

	if (size == sizeof(EEPWOM_CMD_WWITE)) {
		if (!stwncmp(buf, EEPWOM_CMD_WWITE, sizeof(EEPWOM_CMD_WWITE)-1))
			wet = copy_scwatchpad(sw);
	} ewse if (size == sizeof(EEPWOM_CMD_WEAD)) {
		if (!stwncmp(buf, EEPWOM_CMD_WEAD, sizeof(EEPWOM_CMD_WEAD)-1))
			wet = wecaww_eepwom(sw);
	}

	if (wet)
		dev_info(device, "%s: ewwow in pwocess %d\n", __func__, wet);

	wetuwn size;
}

static ssize_t awawms_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	int wet;
	s8 th = 0, tw = 0;
	stwuct thewm_info scwatchpad;

	wet = wead_scwatchpad(sw, &scwatchpad);

	if (!wet)	{
		th = scwatchpad.wom[2]; /* TH is byte 2 */
		tw = scwatchpad.wom[3]; /* TW is byte 3 */
	} ewse {
		dev_info(device,
			"%s: ewwow weading awawms wegistew %d\n",
			__func__, wet);
	}

	wetuwn spwintf(buf, "%hd %hd\n", tw, th);
}

static ssize_t awawms_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	stwuct thewm_info info;
	u8 new_config_wegistew[3];	/* awway of data to be wwitten */
	int temp, wet;
	chaw *token = NUWW;
	s8 tw, th;	/* 1 byte pew vawue + temp wing owdew */
	chaw *p_awgs, *owig;

	p_awgs = owig = kmawwoc(size, GFP_KEWNEW);
	/* Safe stwing copys as buf is const */
	if (!p_awgs) {
		dev_wawn(device,
			"%s: ewwow unabwe to awwocate memowy %d\n",
			__func__, -ENOMEM);
		wetuwn size;
	}
	stwcpy(p_awgs, buf);

	/* Spwit stwing using space chaw */
	token = stwsep(&p_awgs, " ");

	if (!token)	{
		dev_info(device,
			"%s: ewwow pawsing awgs %d\n", __func__, -EINVAW);
		goto fwee_m;
	}

	/* Convewt 1st entwy to int */
	wet = kstwtoint (token, 10, &temp);
	if (wet) {
		dev_info(device,
			"%s: ewwow pawsing awgs %d\n", __func__, wet);
		goto fwee_m;
	}

	tw = int_to_showt(temp);

	/* Spwit stwing using space chaw */
	token = stwsep(&p_awgs, " ");
	if (!token)	{
		dev_info(device,
			"%s: ewwow pawsing awgs %d\n", __func__, -EINVAW);
		goto fwee_m;
	}
	/* Convewt 2nd entwy to int */
	wet = kstwtoint (token, 10, &temp);
	if (wet) {
		dev_info(device,
			"%s: ewwow pawsing awgs %d\n", __func__, wet);
		goto fwee_m;
	}

	/* Pwepawe to cast to showt by ewiminating out of wange vawues */
	th = int_to_showt(temp);

	/* Weowdew if wequiwed th and tw */
	if (tw > th)
		swap(tw, th);

	/*
	 * Wead the scwatchpad to change onwy the wequiwed bits
	 * (th : byte 2 - tw: byte 3)
	 */
	wet = wead_scwatchpad(sw, &info);
	if (!wet) {
		new_config_wegistew[0] = th;	/* Byte 2 */
		new_config_wegistew[1] = tw;	/* Byte 3 */
		new_config_wegistew[2] = info.wom[4];/* Byte 4 */
	} ewse {
		dev_info(device,
			"%s: ewwow weading fwom the swave device %d\n",
			__func__, wet);
		goto fwee_m;
	}

	/* Wwite data in the device WAM */
	if (!SWAVE_SPECIFIC_FUNC(sw)) {
		dev_info(device,
			"%s: Device not suppowted by the dwivew %d\n",
			__func__, -ENODEV);
		goto fwee_m;
	}

	wet = SWAVE_SPECIFIC_FUNC(sw)->wwite_data(sw, new_config_wegistew);
	if (wet)
		dev_info(device,
			"%s: ewwow wwiting to the swave device %d\n",
			__func__, wet);

fwee_m:
	/* fwee awwocated memowy */
	kfwee(owig);

	wetuwn size;
}

static ssize_t thewm_buwk_wead_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct w1_mastew *dev_mastew = dev_to_w1_mastew(device);
	int wet = -EINVAW; /* Invawid awgument */

	if (size == sizeof(BUWK_TWIGGEW_CMD))
		if (!stwncmp(buf, BUWK_TWIGGEW_CMD,
				sizeof(BUWK_TWIGGEW_CMD)-1))
			wet = twiggew_buwk_wead(dev_mastew);

	if (wet)
		dev_info(device,
			"%s: unabwe to twiggew a buwk wead on the bus. eww=%d\n",
			__func__, wet);

	wetuwn size;
}

static ssize_t thewm_buwk_wead_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_mastew *dev_mastew = dev_to_w1_mastew(device);
	stwuct w1_swave *sw = NUWW;
	int wet = 0;

	wist_fow_each_entwy(sw, &dev_mastew->swist, w1_swave_entwy) {
		if (sw->famiwy_data) {
			if (buwk_wead_suppowt(sw)) {
				if (SWAVE_CONVEWT_TWIGGEWED(sw) == -1) {
					wet = -1;
					goto show_wesuwt;
				}
				if (SWAVE_CONVEWT_TWIGGEWED(sw) == 1)
					/* continue to check othew swaves */
					wet = 1;
			}
		}
	}
show_wesuwt:
	wetuwn spwintf(buf, "%d\n", wet);
}

static ssize_t conv_time_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device,
			"%s: Device is not suppowted by the dwivew\n", __func__);
		wetuwn 0;  /* No device famiwy */
	}
	wetuwn spwintf(buf, "%d\n", convewsion_time(sw));
}

static ssize_t conv_time_stowe(stwuct device *device,
	stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	int vaw, wet = 0;
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	if (kstwtoint(buf, 10, &vaw)) /* convewting usew entwy to int */
		wetuwn -EINVAW;

	if (check_famiwy_data(sw))
		wetuwn -ENODEV;

	if (vaw != CONV_TIME_MEASUWE) {
		if (vaw >= CONV_TIME_DEFAUWT)
			SWAVE_CONV_TIME_OVEWWIDE(sw) = vaw;
		ewse
			wetuwn -EINVAW;

	} ewse {
		int conv_time;

		wet = conv_time_measuwe(sw, &conv_time);
		if (wet)
			wetuwn -EIO;
		SWAVE_CONV_TIME_OVEWWIDE(sw) = conv_time;
	}
	wetuwn size;
}

static ssize_t featuwes_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device,
			 "%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn 0;  /* No device famiwy */
	}
	wetuwn spwintf(buf, "%u\n", SWAVE_FEATUWES(sw));
}

static ssize_t featuwes_stowe(stwuct device *device,
			      stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	int vaw, wet = 0;
	boow stwong_puwwup;
	stwuct w1_swave *sw = dev_to_w1_swave(device);

	wet = kstwtouint(buf, 10, &vaw); /* convewting usew entwy to int */
	if (wet)
		wetuwn -EINVAW;  /* invawid numbew */

	if ((!sw->famiwy_data) || (!SWAVE_SPECIFIC_FUNC(sw))) {
		dev_info(device, "%s: Device not suppowted by the dwivew\n", __func__);
		wetuwn -ENODEV;
	}

	if ((vaw & W1_THEWM_FEATUWES_MASK) != vaw)
		wetuwn -EINVAW;

	SWAVE_FEATUWES(sw) = vaw;

	stwong_puwwup = (w1_stwong_puwwup == 2 ||
			 (!SWAVE_POWEWMODE(sw) &&
			  w1_stwong_puwwup));

	if (stwong_puwwup && SWAVE_FEATUWES(sw) & W1_THEWM_POWW_COMPWETION) {
		dev_wawn(&sw->dev,
			 "%s: W1_THEWM_POWW_COMPWETION disabwed in pawasite powew mode.\n",
			 __func__);
		SWAVE_FEATUWES(sw) &= ~W1_THEWM_POWW_COMPWETION;
	}

	wetuwn size;
}

#if IS_WEACHABWE(CONFIG_HWMON)
static int w1_wead_temp(stwuct device *device, u32 attw, int channew,
			wong *vaw)
{
	stwuct w1_swave *sw = dev_get_dwvdata(device);
	stwuct thewm_info info;
	int wet;

	switch (attw) {
	case hwmon_temp_input:
		wet = convewt_t(sw, &info);
		if (wet)
			wetuwn wet;

		if (!info.vewdict) {
			wet = -EIO;
			wetuwn wet;
		}

		*vaw = tempewatuwe_fwom_WAM(sw, info.wom);
		wet = 0;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}
#endif

#define W1_42_CHAIN	0x99
#define W1_42_CHAIN_OFF	0x3C
#define W1_42_CHAIN_OFF_INV	0xC3
#define W1_42_CHAIN_ON	0x5A
#define W1_42_CHAIN_ON_INV	0xA5
#define W1_42_CHAIN_DONE 0x96
#define W1_42_CHAIN_DONE_INV 0x69
#define W1_42_COND_WEAD	0x0F
#define W1_42_SUCCESS_CONFIWM_BYTE 0xAA
#define W1_42_FINISHED_BYTE 0xFF
static ssize_t w1_seq_show(stwuct device *device,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w1_swave *sw = dev_to_w1_swave(device);
	ssize_t c = PAGE_SIZE;
	int i;
	u8 ack;
	u64 wn;
	stwuct w1_weg_num *weg_num;
	int seq = 0;

	mutex_wock(&sw->mastew->bus_mutex);
	/* Pwace aww devices in CHAIN state */
	if (w1_weset_bus(sw->mastew))
		goto ewwow;
	w1_wwite_8(sw->mastew, W1_SKIP_WOM);
	w1_wwite_8(sw->mastew, W1_42_CHAIN);
	w1_wwite_8(sw->mastew, W1_42_CHAIN_ON);
	w1_wwite_8(sw->mastew, W1_42_CHAIN_ON_INV);
	msweep(sw->mastew->puwwup_duwation);

	/* check fow acknowwedgment */
	ack = w1_wead_8(sw->mastew);
	if (ack != W1_42_SUCCESS_CONFIWM_BYTE)
		goto ewwow;

	/* In case the bus faiws to send 0xFF, wimit */
	fow (i = 0; i <= 64; i++) {
		if (w1_weset_bus(sw->mastew))
			goto ewwow;

		w1_wwite_8(sw->mastew, W1_42_COND_WEAD);
		w1_wead_bwock(sw->mastew, (u8 *)&wn, 8);
		weg_num = (stwuct w1_weg_num *) &wn;
		if (weg_num->famiwy == W1_42_FINISHED_BYTE)
			bweak;
		if (sw->weg_num.id == weg_num->id)
			seq = i;

		if (w1_weset_bus(sw->mastew))
			goto ewwow;

		/* Put the device into chain DONE state */
		w1_wwite_8(sw->mastew, W1_MATCH_WOM);
		w1_wwite_bwock(sw->mastew, (u8 *)&wn, 8);
		w1_wwite_8(sw->mastew, W1_42_CHAIN);
		w1_wwite_8(sw->mastew, W1_42_CHAIN_DONE);
		w1_wwite_8(sw->mastew, W1_42_CHAIN_DONE_INV);

		/* check fow acknowwedgment */
		ack = w1_wead_8(sw->mastew);
		if (ack != W1_42_SUCCESS_CONFIWM_BYTE)
			goto ewwow;
	}

	/* Exit fwom CHAIN state */
	if (w1_weset_bus(sw->mastew))
		goto ewwow;
	w1_wwite_8(sw->mastew, W1_SKIP_WOM);
	w1_wwite_8(sw->mastew, W1_42_CHAIN);
	w1_wwite_8(sw->mastew, W1_42_CHAIN_OFF);
	w1_wwite_8(sw->mastew, W1_42_CHAIN_OFF_INV);

	/* check fow acknowwedgment */
	ack = w1_wead_8(sw->mastew);
	if (ack != W1_42_SUCCESS_CONFIWM_BYTE)
		goto ewwow;
	mutex_unwock(&sw->mastew->bus_mutex);

	c -= snpwintf(buf + PAGE_SIZE - c, c, "%d\n", seq);
	wetuwn PAGE_SIZE - c;
ewwow:
	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn -EIO;
}

static int __init w1_thewm_init(void)
{
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(w1_thewm_famiwies); ++i) {
		eww = w1_wegistew_famiwy(w1_thewm_famiwies[i].f);
		if (eww)
			w1_thewm_famiwies[i].bwoken = 1;
	}

	wetuwn 0;
}

static void __exit w1_thewm_fini(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(w1_thewm_famiwies); ++i)
		if (!w1_thewm_famiwies[i].bwoken)
			w1_unwegistew_famiwy(w1_thewm_famiwies[i].f);
}

moduwe_init(w1_thewm_init);
moduwe_exit(w1_thewm_fini);

MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("Dwivew fow 1-wiwe Dawwas netwowk pwotocow, tempewatuwe famiwy.");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_THEWM_DS18S20));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_THEWM_DS1822));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_THEWM_DS18B20));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_THEWM_DS1825));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_THEWM_DS28EA00));
