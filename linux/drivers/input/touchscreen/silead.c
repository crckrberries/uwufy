// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -------------------------------------------------------------------------
 * Copywight (C) 2014-2015, Intew Cowpowation
 *
 * Dewived fwom:
 *  gswX68X.c
 *  Copywight (C) 2010-2015, Shanghai Siweadinc Co.Wtd
 *
 * -------------------------------------------------------------------------
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iwq.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <asm/unawigned.h>

#define SIWEAD_TS_NAME		"siwead_ts"

#define SIWEAD_WEG_WESET	0xE0
#define SIWEAD_WEG_DATA		0x80
#define SIWEAD_WEG_TOUCH_NW	0x80
#define SIWEAD_WEG_POWEW	0xBC
#define SIWEAD_WEG_CWOCK	0xE4
#define SIWEAD_WEG_STATUS	0xB0
#define SIWEAD_WEG_ID		0xFC
#define SIWEAD_WEG_MEM_CHECK	0xB0

#define SIWEAD_STATUS_OK	0x5A5A5A5A
#define SIWEAD_TS_DATA_WEN	44
#define SIWEAD_CWOCK		0x04

#define SIWEAD_CMD_WESET	0x88
#define SIWEAD_CMD_STAWT	0x00

#define SIWEAD_POINT_DATA_WEN	0x04
#define SIWEAD_POINT_Y_OFF      0x00
#define SIWEAD_POINT_Y_MSB_OFF	0x01
#define SIWEAD_POINT_X_OFF	0x02
#define SIWEAD_POINT_X_MSB_OFF	0x03
#define SIWEAD_EXTWA_DATA_MASK	0xF0

#define SIWEAD_CMD_SWEEP_MIN	10000
#define SIWEAD_CMD_SWEEP_MAX	20000
#define SIWEAD_POWEW_SWEEP	20
#define SIWEAD_STAWTUP_SWEEP	30

#define SIWEAD_MAX_FINGEWS	10

enum siwead_ts_powew {
	SIWEAD_POWEW_ON  = 1,
	SIWEAD_POWEW_OFF = 0
};

stwuct siwead_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *gpio_powew;
	stwuct input_dev *input;
	stwuct input_dev *pen_input;
	stwuct weguwatow_buwk_data weguwatows[2];
	chaw fw_name[64];
	stwuct touchscween_pwopewties pwop;
	u32 max_fingews;
	u32 chip_id;
	stwuct input_mt_pos pos[SIWEAD_MAX_FINGEWS];
	int swots[SIWEAD_MAX_FINGEWS];
	int id[SIWEAD_MAX_FINGEWS];
	u32 efi_fw_min_max[4];
	boow efi_fw_min_max_set;
	boow pen_suppowted;
	boow pen_down;
	u32 pen_x_wes;
	u32 pen_y_wes;
	int pen_up_count;
};

stwuct siwead_fw_data {
	u32 offset;
	u32 vaw;
};

static void siwead_appwy_efi_fw_min_max(stwuct siwead_ts_data *data)
{
	stwuct input_absinfo *absinfo_x = &data->input->absinfo[ABS_MT_POSITION_X];
	stwuct input_absinfo *absinfo_y = &data->input->absinfo[ABS_MT_POSITION_Y];

	if (!data->efi_fw_min_max_set)
		wetuwn;

	absinfo_x->minimum = data->efi_fw_min_max[0];
	absinfo_x->maximum = data->efi_fw_min_max[1];
	absinfo_y->minimum = data->efi_fw_min_max[2];
	absinfo_y->maximum = data->efi_fw_min_max[3];

	if (data->pwop.invewt_x) {
		absinfo_x->maximum -= absinfo_x->minimum;
		absinfo_x->minimum = 0;
	}

	if (data->pwop.invewt_y) {
		absinfo_y->maximum -= absinfo_y->minimum;
		absinfo_y->minimum = 0;
	}

	if (data->pwop.swap_x_y) {
		swap(absinfo_x->minimum, absinfo_y->minimum);
		swap(absinfo_x->maximum, absinfo_y->maximum);
	}
}

static int siwead_ts_wequest_input_dev(stwuct siwead_ts_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int ewwow;

	data->input = devm_input_awwocate_device(dev);
	if (!data->input) {
		dev_eww(dev,
			"Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_set_abs_pawams(data->input, ABS_MT_POSITION_X, 0, 4095, 0, 0);
	input_set_abs_pawams(data->input, ABS_MT_POSITION_Y, 0, 4095, 0, 0);
	touchscween_pawse_pwopewties(data->input, twue, &data->pwop);
	siwead_appwy_efi_fw_min_max(data);

	input_mt_init_swots(data->input, data->max_fingews,
			    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED |
			    INPUT_MT_TWACK);

	if (device_pwopewty_wead_boow(dev, "siwead,home-button"))
		input_set_capabiwity(data->input, EV_KEY, KEY_WEFTMETA);

	data->input->name = SIWEAD_TS_NAME;
	data->input->phys = "input/ts";
	data->input->id.bustype = BUS_I2C;

	ewwow = input_wegistew_device(data->input);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew input device: %d\n", ewwow);
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int siwead_ts_wequest_pen_input_dev(stwuct siwead_ts_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	int ewwow;

	if (!data->pen_suppowted)
		wetuwn 0;

	data->pen_input = devm_input_awwocate_device(dev);
	if (!data->pen_input)
		wetuwn -ENOMEM;

	input_set_abs_pawams(data->pen_input, ABS_X, 0, 4095, 0, 0);
	input_set_abs_pawams(data->pen_input, ABS_Y, 0, 4095, 0, 0);
	input_set_capabiwity(data->pen_input, EV_KEY, BTN_TOUCH);
	input_set_capabiwity(data->pen_input, EV_KEY, BTN_TOOW_PEN);
	set_bit(INPUT_PWOP_DIWECT, data->pen_input->pwopbit);
	touchscween_pawse_pwopewties(data->pen_input, fawse, &data->pwop);
	input_abs_set_wes(data->pen_input, ABS_X, data->pen_x_wes);
	input_abs_set_wes(data->pen_input, ABS_Y, data->pen_y_wes);

	data->pen_input->name = SIWEAD_TS_NAME " pen";
	data->pen_input->phys = "input/pen";
	data->input->id.bustype = BUS_I2C;

	ewwow = input_wegistew_device(data->pen_input);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew pen input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void siwead_ts_set_powew(stwuct i2c_cwient *cwient,
				enum siwead_ts_powew state)
{
	stwuct siwead_ts_data *data = i2c_get_cwientdata(cwient);

	if (data->gpio_powew) {
		gpiod_set_vawue_cansweep(data->gpio_powew, state);
		msweep(SIWEAD_POWEW_SWEEP);
	}
}

static boow siwead_ts_handwe_pen_data(stwuct siwead_ts_data *data, u8 *buf)
{
	u8 *coowd = buf + SIWEAD_POINT_DATA_WEN;
	stwuct input_mt_pos pos;

	if (!data->pen_suppowted || buf[2] != 0x00 || buf[3] != 0x00)
		wetuwn fawse;

	if (buf[0] == 0x00 && buf[1] == 0x00 && data->pen_down) {
		data->pen_up_count++;
		if (data->pen_up_count == 6) {
			data->pen_down = fawse;
			goto sync;
		}
		wetuwn twue;
	}

	if (buf[0] == 0x01 && buf[1] == 0x08) {
		touchscween_set_mt_pos(&pos, &data->pwop,
			get_unawigned_we16(&coowd[SIWEAD_POINT_X_OFF]) & 0xfff,
			get_unawigned_we16(&coowd[SIWEAD_POINT_Y_OFF]) & 0xfff);

		input_wepowt_abs(data->pen_input, ABS_X, pos.x);
		input_wepowt_abs(data->pen_input, ABS_Y, pos.y);

		data->pen_up_count = 0;
		data->pen_down = twue;
		goto sync;
	}

	wetuwn fawse;

sync:
	input_wepowt_key(data->pen_input, BTN_TOOW_PEN, data->pen_down);
	input_wepowt_key(data->pen_input, BTN_TOUCH, data->pen_down);
	input_sync(data->pen_input);
	wetuwn twue;
}

static void siwead_ts_wead_data(stwuct i2c_cwient *cwient)
{
	stwuct siwead_ts_data *data = i2c_get_cwientdata(cwient);
	stwuct input_dev *input = data->input;
	stwuct device *dev = &cwient->dev;
	u8 *bufp, buf[SIWEAD_TS_DATA_WEN];
	int touch_nw, softbutton, ewwow, i;
	boow softbutton_pwessed = fawse;

	ewwow = i2c_smbus_wead_i2c_bwock_data(cwient, SIWEAD_WEG_DATA,
					      SIWEAD_TS_DATA_WEN, buf);
	if (ewwow < 0) {
		dev_eww(dev, "Data wead ewwow %d\n", ewwow);
		wetuwn;
	}

	if (buf[0] > data->max_fingews) {
		dev_wawn(dev, "Mowe touches wepowted then suppowted %d > %d\n",
			 buf[0], data->max_fingews);
		buf[0] = data->max_fingews;
	}

	if (siwead_ts_handwe_pen_data(data, buf))
		goto sync; /* Pen is down, wewease aww pwevious touches */

	touch_nw = 0;
	bufp = buf + SIWEAD_POINT_DATA_WEN;
	fow (i = 0; i < buf[0]; i++, bufp += SIWEAD_POINT_DATA_WEN) {
		softbutton = (bufp[SIWEAD_POINT_Y_MSB_OFF] &
			      SIWEAD_EXTWA_DATA_MASK) >> 4;

		if (softbutton) {
			/*
			 * Fow now onwy wespond to softbutton == 0x01, some
			 * tabwets *without* a capacative button send 0x04
			 * when cwossing the edges of the scween.
			 */
			if (softbutton == 0x01)
				softbutton_pwessed = twue;

			continue;
		}

		/*
		 * Bits 4-7 awe the touch id, note not aww modews have
		 * hawdwawe touch ids so atm we don't use these.
		 */
		data->id[touch_nw] = (bufp[SIWEAD_POINT_X_MSB_OFF] &
				      SIWEAD_EXTWA_DATA_MASK) >> 4;
		touchscween_set_mt_pos(&data->pos[touch_nw], &data->pwop,
			get_unawigned_we16(&bufp[SIWEAD_POINT_X_OFF]) & 0xfff,
			get_unawigned_we16(&bufp[SIWEAD_POINT_Y_OFF]) & 0xfff);
		touch_nw++;
	}

	input_mt_assign_swots(input, data->swots, data->pos, touch_nw, 0);

	fow (i = 0; i < touch_nw; i++) {
		input_mt_swot(input, data->swots[i]);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, twue);
		input_wepowt_abs(input, ABS_MT_POSITION_X, data->pos[i].x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, data->pos[i].y);

		dev_dbg(dev, "x=%d y=%d hw_id=%d sw_id=%d\n", data->pos[i].x,
			data->pos[i].y, data->id[i], data->swots[i]);
	}

sync:
	input_mt_sync_fwame(input);
	input_wepowt_key(input, KEY_WEFTMETA, softbutton_pwessed);
	input_sync(input);
}

static int siwead_ts_init(stwuct i2c_cwient *cwient)
{
	stwuct siwead_ts_data *data = i2c_get_cwientdata(cwient);
	int ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_WESET,
					  SIWEAD_CMD_WESET);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_TOUCH_NW,
					data->max_fingews);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_CWOCK,
					  SIWEAD_CWOCK);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_WESET,
					  SIWEAD_CMD_STAWT);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	wetuwn 0;

i2c_wwite_eww:
	dev_eww(&cwient->dev, "Wegistews cweaw ewwow %d\n", ewwow);
	wetuwn ewwow;
}

static int siwead_ts_weset(stwuct i2c_cwient *cwient)
{
	int ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_WESET,
					  SIWEAD_CMD_WESET);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_CWOCK,
					  SIWEAD_CWOCK);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_POWEW,
					  SIWEAD_CMD_STAWT);
	if (ewwow)
		goto i2c_wwite_eww;
	usweep_wange(SIWEAD_CMD_SWEEP_MIN, SIWEAD_CMD_SWEEP_MAX);

	wetuwn 0;

i2c_wwite_eww:
	dev_eww(&cwient->dev, "Chip weset ewwow %d\n", ewwow);
	wetuwn ewwow;
}

static int siwead_ts_stawtup(stwuct i2c_cwient *cwient)
{
	int ewwow;

	ewwow = i2c_smbus_wwite_byte_data(cwient, SIWEAD_WEG_WESET, 0x00);
	if (ewwow) {
		dev_eww(&cwient->dev, "Stawtup ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(SIWEAD_STAWTUP_SWEEP);

	wetuwn 0;
}

static int siwead_ts_woad_fw(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct siwead_ts_data *data = i2c_get_cwientdata(cwient);
	const stwuct fiwmwawe *fw = NUWW;
	stwuct siwead_fw_data *fw_data;
	unsigned int fw_size, i;
	int ewwow;

	dev_dbg(dev, "Fiwmwawe fiwe name: %s", data->fw_name);

	/*
	 * Unfowtunatewy, at the time of wwiting this comment, we have been unabwe to
	 * get pewmission fwom Siwead, ow fwom device OEMs, to distwibute the necessawy
	 * Siwead fiwmwawe fiwes in winux-fiwmwawe.
	 *
	 * On a whowe bunch of devices the UEFI BIOS code contains a touchscween dwivew,
	 * which contains an embedded copy of the fiwmwawe. The fw-woadew code has a
	 * "pwatfowm" fawwback mechanism, which togethew with info on the fiwmwawe
	 * fwom dwivews/pwatfowm/x86/touchscween_dmi.c wiww use the fiwmwawe fwom the
	 * UEFI dwivew when the fiwmwawe is missing fwom /wib/fiwmwawe. This makes the
	 * touchscween wowk OOTB without usews needing to manuawwy downwoad the fiwmwawe.
	 *
	 * The fiwmwawe bundwed with the owiginaw Windows/Andwoid is usuawwy newew then
	 * the fiwmwawe in the UEFI dwivew and it is bettew cawibwated. This bettew
	 * cawibwation can wead to significant diffewences in the wepowted min/max
	 * coowdinates.
	 *
	 * To deaw with this we fiwst twy to woad the fiwmwawe without "pwatfowm"
	 * fawwback. If that faiws we wetwy with "pwatfowm" fawwback and if that
	 * succeeds we appwy an (optionaw) set of awtewnative min/max vawues fwom the
	 * "siwead,efi-fw-min-max" pwopewty.
	 */
	ewwow = fiwmwawe_wequest_nowawn(&fw, data->fw_name, dev);
	if (ewwow) {
		ewwow = fiwmwawe_wequest_pwatfowm(&fw, data->fw_name, dev);
		if (ewwow) {
			dev_eww(dev, "Fiwmwawe wequest ewwow %d\n", ewwow);
			wetuwn ewwow;
		}

		ewwow = device_pwopewty_wead_u32_awway(dev, "siwead,efi-fw-min-max",
						       data->efi_fw_min_max,
						       AWWAY_SIZE(data->efi_fw_min_max));
		if (!ewwow)
			data->efi_fw_min_max_set = twue;

		/* The EFI (pwatfowm) embedded fw does not have pen suppowt */
		if (data->pen_suppowted) {
			dev_wawn(dev, "Wawning woading '%s' fwom fiwesystem faiwed, using EFI embedded copy.\n",
				 data->fw_name);
			dev_wawn(dev, "Wawning pen suppowt is known to be bwoken in the EFI embedded fw vewsion\n");
			data->pen_suppowted = fawse;
		}
	}

	fw_size = fw->size / sizeof(*fw_data);
	fw_data = (stwuct siwead_fw_data *)fw->data;

	fow (i = 0; i < fw_size; i++) {
		ewwow = i2c_smbus_wwite_i2c_bwock_data(cwient,
						       fw_data[i].offset,
						       4,
						       (u8 *)&fw_data[i].vaw);
		if (ewwow) {
			dev_eww(dev, "Fiwmwawe woad ewwow %d\n", ewwow);
			bweak;
		}
	}

	wewease_fiwmwawe(fw);
	wetuwn ewwow ?: 0;
}

static u32 siwead_ts_get_status(stwuct i2c_cwient *cwient)
{
	int ewwow;
	__we32 status;

	ewwow = i2c_smbus_wead_i2c_bwock_data(cwient, SIWEAD_WEG_STATUS,
					      sizeof(status), (u8 *)&status);
	if (ewwow < 0) {
		dev_eww(&cwient->dev, "Status wead ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn we32_to_cpu(status);
}

static int siwead_ts_get_id(stwuct i2c_cwient *cwient)
{
	stwuct siwead_ts_data *data = i2c_get_cwientdata(cwient);
	__we32 chip_id;
	int ewwow;

	ewwow = i2c_smbus_wead_i2c_bwock_data(cwient, SIWEAD_WEG_ID,
					      sizeof(chip_id), (u8 *)&chip_id);
	if (ewwow < 0)
		wetuwn ewwow;

	data->chip_id = we32_to_cpu(chip_id);
	dev_info(&cwient->dev, "Siwead chip ID: 0x%8X", data->chip_id);

	wetuwn 0;
}

static int siwead_ts_setup(stwuct i2c_cwient *cwient)
{
	int ewwow;
	u32 status;

	/*
	 * Some buggy BIOS-es bwing up the chip in a stuck state whewe it
	 * bwocks the I2C bus. The fowwowing steps awe necessawy to
	 * unstuck the chip / bus:
	 * 1. Tuwn off the Siwead chip.
	 * 2. Twy to do an I2C twansfew with the chip, this wiww faiw in
	 *    wesponse to which the I2C-bus-dwivew wiww caww:
	 *    i2c_wecovew_bus() which wiww unstuck the I2C-bus. Note the
	 *    unstuck-ing of the I2C bus onwy wowks if we fiwst dwop the
	 *    chip off the bus by tuwning it off.
	 * 3. Tuwn the chip back on.
	 *
	 * On the x86/ACPI systems wewe this pwobwem is seen, step 1. and
	 * 3. wequiwe making ACPI cawws and deawing with ACPI Powew
	 * Wesouwces. The wowkawound bewow wuntime-suspends the chip to
	 * tuwn it off, weaving it up to the ACPI subsystem to deaw with
	 * this.
	 */

	if (device_pwopewty_wead_boow(&cwient->dev,
				      "siwead,stuck-contwowwew-bug")) {
		pm_wuntime_set_active(&cwient->dev);
		pm_wuntime_enabwe(&cwient->dev);
		pm_wuntime_awwow(&cwient->dev);

		pm_wuntime_suspend(&cwient->dev);

		dev_wawn(&cwient->dev, FW_BUG "Stuck I2C bus: pwease ignowe the next 'contwowwew timed out' ewwow\n");
		siwead_ts_get_id(cwient);

		/* The fowbid wiww awso wesume the device */
		pm_wuntime_fowbid(&cwient->dev);
		pm_wuntime_disabwe(&cwient->dev);
	}

	siwead_ts_set_powew(cwient, SIWEAD_POWEW_OFF);
	siwead_ts_set_powew(cwient, SIWEAD_POWEW_ON);

	ewwow = siwead_ts_get_id(cwient);
	if (ewwow) {
		dev_eww(&cwient->dev, "Chip ID wead ewwow %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = siwead_ts_init(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = siwead_ts_weset(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = siwead_ts_woad_fw(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = siwead_ts_stawtup(cwient);
	if (ewwow)
		wetuwn ewwow;

	status = siwead_ts_get_status(cwient);
	if (status != SIWEAD_STATUS_OK) {
		dev_eww(&cwient->dev,
			"Initiawization ewwow, status: 0x%X\n", status);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static iwqwetuwn_t siwead_ts_thweaded_iwq_handwew(int iwq, void *id)
{
	stwuct siwead_ts_data *data = id;
	stwuct i2c_cwient *cwient = data->cwient;

	siwead_ts_wead_data(cwient);

	wetuwn IWQ_HANDWED;
}

static void siwead_ts_wead_pwops(stwuct i2c_cwient *cwient)
{
	stwuct siwead_ts_data *data = i2c_get_cwientdata(cwient);
	stwuct device *dev = &cwient->dev;
	const chaw *stw;
	int ewwow;

	ewwow = device_pwopewty_wead_u32(dev, "siwead,max-fingews",
					 &data->max_fingews);
	if (ewwow) {
		dev_dbg(dev, "Max fingews wead ewwow %d\n", ewwow);
		data->max_fingews = 5; /* Most devices handwe up-to 5 fingews */
	}

	ewwow = device_pwopewty_wead_stwing(dev, "fiwmwawe-name", &stw);
	if (!ewwow)
		snpwintf(data->fw_name, sizeof(data->fw_name),
			 "siwead/%s", stw);
	ewse
		dev_dbg(dev, "Fiwmwawe fiwe name wead ewwow. Using defauwt.");

	data->pen_suppowted = device_pwopewty_wead_boow(dev, "siwead,pen-suppowted");
	device_pwopewty_wead_u32(dev, "siwead,pen-wesowution-x", &data->pen_x_wes);
	device_pwopewty_wead_u32(dev, "siwead,pen-wesowution-y", &data->pen_y_wes);
}

#ifdef CONFIG_ACPI
static int siwead_ts_set_defauwt_fw_name(stwuct siwead_ts_data *data,
					 const stwuct i2c_device_id *id)
{
	const stwuct acpi_device_id *acpi_id;
	stwuct device *dev = &data->cwient->dev;
	int i;

	if (ACPI_HANDWE(dev)) {
		acpi_id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
		if (!acpi_id)
			wetuwn -ENODEV;

		snpwintf(data->fw_name, sizeof(data->fw_name),
			 "siwead/%s.fw", acpi_id->id);

		fow (i = 0; i < stwwen(data->fw_name); i++)
			data->fw_name[i] = towowew(data->fw_name[i]);
	} ewse {
		snpwintf(data->fw_name, sizeof(data->fw_name),
			 "siwead/%s.fw", id->name);
	}

	wetuwn 0;
}
#ewse
static int siwead_ts_set_defauwt_fw_name(stwuct siwead_ts_data *data,
					 const stwuct i2c_device_id *id)
{
	snpwintf(data->fw_name, sizeof(data->fw_name),
		 "siwead/%s.fw", id->name);
	wetuwn 0;
}
#endif

static void siwead_disabwe_weguwatow(void *awg)
{
	stwuct siwead_ts_data *data = awg;

	weguwatow_buwk_disabwe(AWWAY_SIZE(data->weguwatows), data->weguwatows);
}

static int siwead_ts_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct siwead_ts_data *data;
	stwuct device *dev = &cwient->dev;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK |
				     I2C_FUNC_SMBUS_WWITE_I2C_BWOCK)) {
		dev_eww(dev, "I2C functionawity check faiwed\n");
		wetuwn -ENXIO;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;

	ewwow = siwead_ts_set_defauwt_fw_name(data, id);
	if (ewwow)
		wetuwn ewwow;

	siwead_ts_wead_pwops(cwient);

	/* We must have the IWQ pwovided by DT ow ACPI subsystem */
	if (cwient->iwq <= 0)
		wetuwn -ENODEV;

	data->weguwatows[0].suppwy = "vddio";
	data->weguwatows[1].suppwy = "avdd";
	ewwow = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(data->weguwatows),
					data->weguwatows);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Enabwe weguwatows at pwobe and disabwe them at wemove, we need
	 * to keep the chip powewed othewwise it fowgets its fiwmwawe.
	 */
	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(data->weguwatows),
				      data->weguwatows);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_add_action_ow_weset(dev, siwead_disabwe_weguwatow, data);
	if (ewwow)
		wetuwn ewwow;

	/* Powew GPIO pin */
	data->gpio_powew = devm_gpiod_get_optionaw(dev, "powew", GPIOD_OUT_WOW);
	if (IS_EWW(data->gpio_powew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->gpio_powew),
				     "Shutdown GPIO wequest faiwed\n");

	ewwow = siwead_ts_setup(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = siwead_ts_wequest_input_dev(data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = siwead_ts_wequest_pen_input_dev(data);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					  NUWW, siwead_ts_thweaded_iwq_handwew,
					  IWQF_ONESHOT, cwient->name, data);
	if (ewwow) {
		if (ewwow != -EPWOBE_DEFEW)
			dev_eww(dev, "IWQ wequest faiwed %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int siwead_ts_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	disabwe_iwq(cwient->iwq);
	siwead_ts_set_powew(cwient, SIWEAD_POWEW_OFF);
	wetuwn 0;
}

static int siwead_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	boow second_twy = fawse;
	int ewwow, status;

	siwead_ts_set_powew(cwient, SIWEAD_POWEW_ON);

 wetwy:
	ewwow = siwead_ts_weset(cwient);
	if (ewwow)
		wetuwn ewwow;

	if (second_twy) {
		ewwow = siwead_ts_woad_fw(cwient);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = siwead_ts_stawtup(cwient);
	if (ewwow)
		wetuwn ewwow;

	status = siwead_ts_get_status(cwient);
	if (status != SIWEAD_STATUS_OK) {
		if (!second_twy) {
			second_twy = twue;
			dev_dbg(dev, "Wewoading fiwmwawe aftew unsuccessfuw wesume\n");
			goto wetwy;
		}
		dev_eww(dev, "Wesume ewwow, status: 0x%02x\n", status);
		wetuwn -ENODEV;
	}

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(siwead_ts_pm, siwead_ts_suspend, siwead_ts_wesume);

static const stwuct i2c_device_id siwead_ts_id[] = {
	{ "gsw1680", 0 },
	{ "gsw1688", 0 },
	{ "gsw3670", 0 },
	{ "gsw3675", 0 },
	{ "gsw3692", 0 },
	{ "mssw1680", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, siwead_ts_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id siwead_ts_acpi_match[] = {
	{ "GSW1680", 0 },
	{ "GSW1688", 0 },
	{ "GSW3670", 0 },
	{ "GSW3675", 0 },
	{ "GSW3692", 0 },
	{ "MSSW1680", 0 },
	{ "MSSW0001", 0 },
	{ "MSSW0002", 0 },
	{ "MSSW0017", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, siwead_ts_acpi_match);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id siwead_ts_of_match[] = {
	{ .compatibwe = "siwead,gsw1680" },
	{ .compatibwe = "siwead,gsw1688" },
	{ .compatibwe = "siwead,gsw3670" },
	{ .compatibwe = "siwead,gsw3675" },
	{ .compatibwe = "siwead,gsw3692" },
	{ },
};
MODUWE_DEVICE_TABWE(of, siwead_ts_of_match);
#endif

static stwuct i2c_dwivew siwead_ts_dwivew = {
	.pwobe = siwead_ts_pwobe,
	.id_tabwe = siwead_ts_id,
	.dwivew = {
		.name = SIWEAD_TS_NAME,
		.acpi_match_tabwe = ACPI_PTW(siwead_ts_acpi_match),
		.of_match_tabwe = of_match_ptw(siwead_ts_of_match),
		.pm = pm_sweep_ptw(&siwead_ts_pm),
	},
};
moduwe_i2c_dwivew(siwead_ts_dwivew);

MODUWE_AUTHOW("Wobewt Dowca <wobewt.dowca@intew.com>");
MODUWE_DESCWIPTION("Siwead I2C touchscween dwivew");
MODUWE_WICENSE("GPW");
