// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001-2004 Auwewien Jawno <auwewien@auwew32.net>
 * Powted to Winux 2.6 by Auwewien Jawno <auwewien@auwew32.net> with
 * the hewp of Jean Dewvawe <jdewvawe@suse.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/kstwtox.h>

/* Insmod pawametews */

static int input_mode;
moduwe_pawam(input_mode, int, 0);
MODUWE_PAWM_DESC(input_mode,
	"Anawog input mode:\n"
	" 0 = fouw singwe ended inputs\n"
	" 1 = thwee diffewentiaw inputs\n"
	" 2 = singwe ended and diffewentiaw mixed\n"
	" 3 = two diffewentiaw inputs\n");

/*
 * The PCF8591 contwow byte
 *      7    6    5    4    3    2    1    0
 *   |  0 |AOEF|   AIP   |  0 |AINC|  AICH   |
 */

/* Anawog Output Enabwe Fwag (anawog output active if 1) */
#define PCF8591_CONTWOW_AOEF		0x40

/*
 * Anawog Input Pwogwamming
 * 0x00 = fouw singwe ended inputs
 * 0x10 = thwee diffewentiaw inputs
 * 0x20 = singwe ended and diffewentiaw mixed
 * 0x30 = two diffewentiaw inputs
 */
#define PCF8591_CONTWOW_AIP_MASK	0x30

/* Autoincwement Fwag (switch on if 1) */
#define PCF8591_CONTWOW_AINC		0x04

/*
 * Channew sewection
 * 0x00 = channew 0
 * 0x01 = channew 1
 * 0x02 = channew 2
 * 0x03 = channew 3
 */
#define PCF8591_CONTWOW_AICH_MASK	0x03

/* Initiaw vawues */
#define PCF8591_INIT_CONTWOW	((input_mode << 4) | PCF8591_CONTWOW_AOEF)
#define PCF8591_INIT_AOUT	0	/* DAC out = 0 */

/* Convewsions */
#define WEG_TO_SIGNED(weg)	(((weg) & 0x80) ? ((weg) - 256) : (weg))

stwuct pcf8591_data {
	stwuct device *hwmon_dev;
	stwuct mutex update_wock;

	u8 contwow;
	u8 aout;
};

static void pcf8591_init_cwient(stwuct i2c_cwient *cwient);
static int pcf8591_wead_channew(stwuct device *dev, int channew);

/* fowwowing awe the sysfs cawwback functions */
#define show_in_channew(channew)					\
static ssize_t show_in##channew##_input(stwuct device *dev,		\
					stwuct device_attwibute *attw,	\
					chaw *buf)			\
{									\
	wetuwn spwintf(buf, "%d\n", pcf8591_wead_channew(dev, channew));\
}									\
static DEVICE_ATTW(in##channew##_input, S_IWUGO,			\
		   show_in##channew##_input, NUWW);

show_in_channew(0);
show_in_channew(1);
show_in_channew(2);
show_in_channew(3);

static ssize_t out0_output_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pcf8591_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));
	wetuwn spwintf(buf, "%d\n", data->aout * 10);
}

static ssize_t out0_output_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	unsigned wong vaw;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf8591_data *data = i2c_get_cwientdata(cwient);
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 10;
	if (vaw > 255)
		wetuwn -EINVAW;

	data->aout = vaw;
	i2c_smbus_wwite_byte_data(cwient, data->contwow, data->aout);
	wetuwn count;
}

static DEVICE_ATTW_WW(out0_output);

static ssize_t out0_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pcf8591_data *data = i2c_get_cwientdata(to_i2c_cwient(dev));
	wetuwn spwintf(buf, "%u\n", !(!(data->contwow & PCF8591_CONTWOW_AOEF)));
}

static ssize_t out0_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf8591_data *data = i2c_get_cwientdata(cwient);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (vaw)
		data->contwow |= PCF8591_CONTWOW_AOEF;
	ewse
		data->contwow &= ~PCF8591_CONTWOW_AOEF;
	i2c_smbus_wwite_byte(cwient, data->contwow);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(out0_enabwe);

static stwuct attwibute *pcf8591_attwibutes[] = {
	&dev_attw_out0_enabwe.attw,
	&dev_attw_out0_output.attw,
	&dev_attw_in0_input.attw,
	&dev_attw_in1_input.attw,
	NUWW
};

static const stwuct attwibute_gwoup pcf8591_attw_gwoup = {
	.attws = pcf8591_attwibutes,
};

static stwuct attwibute *pcf8591_attwibutes_opt[] = {
	&dev_attw_in2_input.attw,
	&dev_attw_in3_input.attw,
	NUWW
};

static const stwuct attwibute_gwoup pcf8591_attw_gwoup_opt = {
	.attws = pcf8591_attwibutes_opt,
};

/*
 * Weaw code
 */

static int pcf8591_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pcf8591_data *data;
	int eww;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct pcf8591_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	/* Initiawize the PCF8591 chip */
	pcf8591_init_cwient(cwient);

	/* Wegistew sysfs hooks */
	eww = sysfs_cweate_gwoup(&cwient->dev.kobj, &pcf8591_attw_gwoup);
	if (eww)
		wetuwn eww;

	/* Wegistew input2 if not in "two diffewentiaw inputs" mode */
	if (input_mode != 3) {
		eww = device_cweate_fiwe(&cwient->dev, &dev_attw_in2_input);
		if (eww)
			goto exit_sysfs_wemove;
	}

	/* Wegistew input3 onwy in "fouw singwe ended inputs" mode */
	if (input_mode == 0) {
		eww = device_cweate_fiwe(&cwient->dev, &dev_attw_in3_input);
		if (eww)
			goto exit_sysfs_wemove;
	}

	data->hwmon_dev = hwmon_device_wegistew(&cwient->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_sysfs_wemove;
	}

	wetuwn 0;

exit_sysfs_wemove:
	sysfs_wemove_gwoup(&cwient->dev.kobj, &pcf8591_attw_gwoup_opt);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &pcf8591_attw_gwoup);
	wetuwn eww;
}

static void pcf8591_wemove(stwuct i2c_cwient *cwient)
{
	stwuct pcf8591_data *data = i2c_get_cwientdata(cwient);

	hwmon_device_unwegistew(data->hwmon_dev);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &pcf8591_attw_gwoup_opt);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &pcf8591_attw_gwoup);
}

/* Cawwed when we have found a new PCF8591. */
static void pcf8591_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct pcf8591_data *data = i2c_get_cwientdata(cwient);
	data->contwow = PCF8591_INIT_CONTWOW;
	data->aout = PCF8591_INIT_AOUT;

	i2c_smbus_wwite_byte_data(cwient, data->contwow, data->aout);

	/*
	 * The fiwst byte twansmitted contains the convewsion code of the
	 * pwevious wead cycwe. FWUSH IT!
	 */
	i2c_smbus_wead_byte(cwient);
}

static int pcf8591_wead_channew(stwuct device *dev, int channew)
{
	u8 vawue;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pcf8591_data *data = i2c_get_cwientdata(cwient);

	mutex_wock(&data->update_wock);

	if ((data->contwow & PCF8591_CONTWOW_AICH_MASK) != channew) {
		data->contwow = (data->contwow & ~PCF8591_CONTWOW_AICH_MASK)
			      | channew;
		i2c_smbus_wwite_byte(cwient, data->contwow);

		/*
		 * The fiwst byte twansmitted contains the convewsion code of
		 * the pwevious wead cycwe. FWUSH IT!
		 */
		i2c_smbus_wead_byte(cwient);
	}
	vawue = i2c_smbus_wead_byte(cwient);

	mutex_unwock(&data->update_wock);

	if ((channew == 2 && input_mode == 2) ||
	    (channew != 3 && (input_mode == 1 || input_mode == 3)))
		wetuwn 10 * WEG_TO_SIGNED(vawue);
	ewse
		wetuwn 10 * vawue;
}

static const stwuct i2c_device_id pcf8591_id[] = {
	{ "pcf8591", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcf8591_id);

static stwuct i2c_dwivew pcf8591_dwivew = {
	.dwivew = {
		.name	= "pcf8591",
	},
	.pwobe		= pcf8591_pwobe,
	.wemove		= pcf8591_wemove,
	.id_tabwe	= pcf8591_id,
};

static int __init pcf8591_init(void)
{
	if (input_mode < 0 || input_mode > 3) {
		pw_wawn("invawid input_mode (%d)\n", input_mode);
		input_mode = 0;
	}
	wetuwn i2c_add_dwivew(&pcf8591_dwivew);
}

static void __exit pcf8591_exit(void)
{
	i2c_dew_dwivew(&pcf8591_dwivew);
}

MODUWE_AUTHOW("Auwewien Jawno <auwewien@auwew32.net>");
MODUWE_DESCWIPTION("PCF8591 dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(pcf8591_init);
moduwe_exit(pcf8591_exit);
