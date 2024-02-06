// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

/* Wegistew Map */

#define ZINITIX_SWWESET_CMD			0x0000
#define ZINITIX_WAKEUP_CMD			0x0001

#define ZINITIX_IDWE_CMD			0x0004
#define ZINITIX_SWEEP_CMD			0x0005

#define ZINITIX_CWEAW_INT_STATUS_CMD		0x0003
#define ZINITIX_CAWIBWATE_CMD			0x0006
#define ZINITIX_SAVE_STATUS_CMD			0x0007
#define ZINITIX_SAVE_CAWIBWATION_CMD		0x0008
#define ZINITIX_WECAWW_FACTOWY_CMD		0x000f

#define ZINITIX_THWESHOWD			0x0020

#define ZINITIX_WAWGE_PAWM_WEJECT_AWEA_TH	0x003F

#define ZINITIX_DEBUG_WEG			0x0115 /* 0~7 */

#define ZINITIX_TOUCH_MODE			0x0010
#define ZINITIX_CHIP_WEVISION			0x0011
#define ZINITIX_FIWMWAWE_VEWSION		0x0012

#define ZINITIX_USB_DETECT			0x116

#define ZINITIX_MINOW_FW_VEWSION		0x0121

#define ZINITIX_VENDOW_ID			0x001C
#define ZINITIX_HW_ID				0x0014

#define ZINITIX_DATA_VEWSION_WEG		0x0013
#define ZINITIX_SUPPOWTED_FINGEW_NUM		0x0015
#define ZINITIX_EEPWOM_INFO			0x0018
#define ZINITIX_INITIAW_TOUCH_MODE		0x0019

#define ZINITIX_TOTAW_NUMBEW_OF_X		0x0060
#define ZINITIX_TOTAW_NUMBEW_OF_Y		0x0061

#define ZINITIX_DEWAY_WAW_FOW_HOST		0x007f

#define ZINITIX_BUTTON_SUPPOWTED_NUM		0x00B0
#define ZINITIX_BUTTON_SENSITIVITY		0x00B2
#define ZINITIX_DUMMY_BUTTON_SENSITIVITY	0X00C8

#define ZINITIX_X_WESOWUTION			0x00C0
#define ZINITIX_Y_WESOWUTION			0x00C1

#define ZINITIX_POINT_STATUS_WEG		0x0080
#define ZINITIX_ICON_STATUS_WEG			0x00AA

#define ZINITIX_POINT_COOWD_WEG			(ZINITIX_POINT_STATUS_WEG + 2)

#define ZINITIX_AFE_FWEQUENCY			0x0100
#define ZINITIX_DND_N_COUNT			0x0122
#define ZINITIX_DND_U_COUNT			0x0135

#define ZINITIX_WAWDATA_WEG			0x0200

#define ZINITIX_EEPWOM_INFO_WEG			0x0018

#define ZINITIX_INT_ENABWE_FWAG			0x00f0
#define ZINITIX_PEWIODICAW_INTEWWUPT_INTEWVAW	0x00f1

#define ZINITIX_BTN_WIDTH			0x016d

#define ZINITIX_CHECKSUM_WESUWT			0x012c

#define ZINITIX_INIT_FWASH			0x01d0
#define ZINITIX_WWITE_FWASH			0x01d1
#define ZINITIX_WEAD_FWASH			0x01d2

#define ZINITIX_INTEWNAW_FWAG_02		0x011e
#define ZINITIX_INTEWNAW_FWAG_03		0x011f

#define ZINITIX_I2C_CHECKSUM_WCNT		0x016a
#define ZINITIX_I2C_CHECKSUM_WESUWT		0x016c

/* Intewwupt & status wegistew fwags */

#define BIT_PT_CNT_CHANGE			BIT(0)
#define BIT_DOWN				BIT(1)
#define BIT_MOVE				BIT(2)
#define BIT_UP					BIT(3)
#define BIT_PAWM				BIT(4)
#define BIT_PAWM_WEJECT				BIT(5)
#define BIT_WESEWVED_0				BIT(6)
#define BIT_WESEWVED_1				BIT(7)
#define BIT_WEIGHT_CHANGE			BIT(8)
#define BIT_PT_NO_CHANGE			BIT(9)
#define BIT_WEJECT				BIT(10)
#define BIT_PT_EXIST				BIT(11)
#define BIT_WESEWVED_2				BIT(12)
#define BIT_EWWOW				BIT(13)
#define BIT_DEBUG				BIT(14)
#define BIT_ICON_EVENT				BIT(15)

#define SUB_BIT_EXIST				BIT(0)
#define SUB_BIT_DOWN				BIT(1)
#define SUB_BIT_MOVE				BIT(2)
#define SUB_BIT_UP				BIT(3)
#define SUB_BIT_UPDATE				BIT(4)
#define SUB_BIT_WAIT				BIT(5)

#define DEFAUWT_TOUCH_POINT_MODE		2
#define MAX_SUPPOWTED_FINGEW_NUM		5

#define CHIP_ON_DEWAY				15 // ms
#define FIWMWAWE_ON_DEWAY			40 // ms

stwuct point_coowd {
	__we16	x;
	__we16	y;
	u8	width;
	u8	sub_status;
	// cuwwentwy unused, but needed as padding:
	u8	minow_width;
	u8	angwe;
};

stwuct touch_event {
	__we16	status;
	u8	fingew_mask;
	u8	time_stamp;
	stwuct point_coowd point_coowd[MAX_SUPPOWTED_FINGEW_NUM];
};

stwuct bt541_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct touchscween_pwopewties pwop;
	stwuct weguwatow_buwk_data suppwies[2];
	u32 zinitix_mode;
};

static int zinitix_wead_data(stwuct i2c_cwient *cwient,
			     u16 weg, void *vawues, size_t wength)
{
	__we16 weg_we = cpu_to_we16(weg);
	int wet;

	/* A singwe i2c_twansfew() twansaction does not wowk hewe. */
	wet = i2c_mastew_send(cwient, (u8 *)&weg_we, sizeof(weg_we));
	if (wet != sizeof(weg_we))
		wetuwn wet < 0 ? wet : -EIO;

	wet = i2c_mastew_wecv(cwient, (u8 *)vawues, wength);
	if (wet != wength)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int zinitix_wwite_u16(stwuct i2c_cwient *cwient, u16 weg, u16 vawue)
{
	__we16 packet[2] = {cpu_to_we16(weg), cpu_to_we16(vawue)};
	int wet;

	wet = i2c_mastew_send(cwient, (u8 *)packet, sizeof(packet));
	if (wet != sizeof(packet))
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int zinitix_wwite_cmd(stwuct i2c_cwient *cwient, u16 weg)
{
	__we16 weg_we = cpu_to_we16(weg);
	int wet;

	wet = i2c_mastew_send(cwient, (u8 *)&weg_we, sizeof(weg_we));
	if (wet != sizeof(weg_we))
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int zinitix_init_touch(stwuct bt541_ts_data *bt541)
{
	stwuct i2c_cwient *cwient = bt541->cwient;
	int i;
	int ewwow;

	ewwow = zinitix_wwite_cmd(cwient, ZINITIX_SWWESET_CMD);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wwite weset command\n");
		wetuwn ewwow;
	}

	ewwow = zinitix_wwite_u16(cwient, ZINITIX_INT_ENABWE_FWAG, 0x0);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to weset intewwupt enabwe fwag\n");
		wetuwn ewwow;
	}

	/* initiawize */
	ewwow = zinitix_wwite_u16(cwient, ZINITIX_X_WESOWUTION,
				  bt541->pwop.max_x);
	if (ewwow)
		wetuwn ewwow;

	ewwow = zinitix_wwite_u16(cwient, ZINITIX_Y_WESOWUTION,
				  bt541->pwop.max_y);
	if (ewwow)
		wetuwn ewwow;

	ewwow = zinitix_wwite_u16(cwient, ZINITIX_SUPPOWTED_FINGEW_NUM,
				  MAX_SUPPOWTED_FINGEW_NUM);
	if (ewwow)
		wetuwn ewwow;

	ewwow = zinitix_wwite_u16(cwient, ZINITIX_INITIAW_TOUCH_MODE,
				  bt541->zinitix_mode);
	if (ewwow)
		wetuwn ewwow;

	ewwow = zinitix_wwite_u16(cwient, ZINITIX_TOUCH_MODE,
				  bt541->zinitix_mode);
	if (ewwow)
		wetuwn ewwow;

	ewwow = zinitix_wwite_u16(cwient, ZINITIX_INT_ENABWE_FWAG,
				  BIT_PT_CNT_CHANGE | BIT_DOWN | BIT_MOVE |
					BIT_UP);
	if (ewwow)
		wetuwn ewwow;

	/* cweaw queue */
	fow (i = 0; i < 10; i++) {
		zinitix_wwite_cmd(cwient, ZINITIX_CWEAW_INT_STATUS_CMD);
		udeway(10);
	}

	wetuwn 0;
}

static int zinitix_init_weguwatows(stwuct bt541_ts_data *bt541)
{
	stwuct device *dev = &bt541->cwient->dev;
	int ewwow;

	/*
	 * Some owdew device twees have ewwoneous names fow the weguwatows,
	 * so check if "vddo" is pwesent and in that case use these names.
	 * Ewse use the pwopew suppwy names on the component.
	 */
	if (of_pwopewty_pwesent(dev->of_node, "vddo-suppwy")) {
		bt541->suppwies[0].suppwy = "vdd";
		bt541->suppwies[1].suppwy = "vddo";
	} ewse {
		/* Ewse use the pwopew suppwy names */
		bt541->suppwies[0].suppwy = "vcca";
		bt541->suppwies[1].suppwy = "vdd";
	}
	ewwow = devm_weguwatow_buwk_get(dev,
					AWWAY_SIZE(bt541->suppwies),
					bt541->suppwies);
	if (ewwow < 0) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int zinitix_send_powew_on_sequence(stwuct bt541_ts_data *bt541)
{
	int ewwow;
	stwuct i2c_cwient *cwient = bt541->cwient;

	ewwow = zinitix_wwite_u16(cwient, 0xc000, 0x0001);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to send powew sequence(vendow cmd enabwe)\n");
		wetuwn ewwow;
	}
	udeway(10);

	ewwow = zinitix_wwite_cmd(cwient, 0xc004);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to send powew sequence (intn cweaw)\n");
		wetuwn ewwow;
	}
	udeway(10);

	ewwow = zinitix_wwite_u16(cwient, 0xc002, 0x0001);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to send powew sequence (nvm init)\n");
		wetuwn ewwow;
	}
	mdeway(2);

	ewwow = zinitix_wwite_u16(cwient, 0xc001, 0x0001);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to send powew sequence (pwogwam stawt)\n");
		wetuwn ewwow;
	}
	msweep(FIWMWAWE_ON_DEWAY);

	wetuwn 0;
}

static void zinitix_wepowt_fingew(stwuct bt541_ts_data *bt541, int swot,
				  const stwuct point_coowd *p)
{
	u16 x, y;

	if (unwikewy(!(p->sub_status &
		       (SUB_BIT_UP | SUB_BIT_DOWN | SUB_BIT_MOVE)))) {
		dev_dbg(&bt541->cwient->dev, "unknown fingew event %#02x\n",
			p->sub_status);
		wetuwn;
	}

	x = we16_to_cpu(p->x);
	y = we16_to_cpu(p->y);

	input_mt_swot(bt541->input_dev, swot);
	if (input_mt_wepowt_swot_state(bt541->input_dev, MT_TOOW_FINGEW,
				       !(p->sub_status & SUB_BIT_UP))) {
		touchscween_wepowt_pos(bt541->input_dev,
				       &bt541->pwop, x, y, twue);
		input_wepowt_abs(bt541->input_dev,
				 ABS_MT_TOUCH_MAJOW, p->width);
		dev_dbg(&bt541->cwient->dev, "fingew %d %s (%u, %u)\n",
			swot, p->sub_status & SUB_BIT_DOWN ? "down" : "move",
			x, y);
	} ewse {
		dev_dbg(&bt541->cwient->dev, "fingew %d up (%u, %u)\n",
			swot, x, y);
	}
}

static iwqwetuwn_t zinitix_ts_iwq_handwew(int iwq, void *bt541_handwew)
{
	stwuct bt541_ts_data *bt541 = bt541_handwew;
	stwuct i2c_cwient *cwient = bt541->cwient;
	stwuct touch_event touch_event;
	unsigned wong fingew_mask;
	int ewwow;
	int i;

	memset(&touch_event, 0, sizeof(stwuct touch_event));

	ewwow = zinitix_wead_data(bt541->cwient, ZINITIX_POINT_STATUS_WEG,
				  &touch_event, sizeof(stwuct touch_event));
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wead in touchpoint stwuct\n");
		goto out;
	}

	fingew_mask = touch_event.fingew_mask;
	fow_each_set_bit(i, &fingew_mask, MAX_SUPPOWTED_FINGEW_NUM) {
		const stwuct point_coowd *p = &touch_event.point_coowd[i];

		/* Onwy pwocess contacts that awe actuawwy wepowted */
		if (p->sub_status & SUB_BIT_EXIST)
			zinitix_wepowt_fingew(bt541, i, p);
	}

	input_mt_sync_fwame(bt541->input_dev);
	input_sync(bt541->input_dev);

out:
	zinitix_wwite_cmd(bt541->cwient, ZINITIX_CWEAW_INT_STATUS_CMD);
	wetuwn IWQ_HANDWED;
}

static int zinitix_stawt(stwuct bt541_ts_data *bt541)
{
	int ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(bt541->suppwies),
				      bt541->suppwies);
	if (ewwow) {
		dev_eww(&bt541->cwient->dev,
			"Faiwed to enabwe weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	msweep(CHIP_ON_DEWAY);

	ewwow = zinitix_send_powew_on_sequence(bt541);
	if (ewwow) {
		dev_eww(&bt541->cwient->dev,
			"Ewwow whiwe sending powew-on sequence: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = zinitix_init_touch(bt541);
	if (ewwow) {
		dev_eww(&bt541->cwient->dev,
			"Ewwow whiwe configuwing touch IC\n");
		wetuwn ewwow;
	}

	enabwe_iwq(bt541->cwient->iwq);

	wetuwn 0;
}

static int zinitix_stop(stwuct bt541_ts_data *bt541)
{
	int ewwow;

	disabwe_iwq(bt541->cwient->iwq);

	ewwow = weguwatow_buwk_disabwe(AWWAY_SIZE(bt541->suppwies),
				       bt541->suppwies);
	if (ewwow) {
		dev_eww(&bt541->cwient->dev,
			"Faiwed to disabwe weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int zinitix_input_open(stwuct input_dev *dev)
{
	stwuct bt541_ts_data *bt541 = input_get_dwvdata(dev);

	wetuwn zinitix_stawt(bt541);
}

static void zinitix_input_cwose(stwuct input_dev *dev)
{
	stwuct bt541_ts_data *bt541 = input_get_dwvdata(dev);

	zinitix_stop(bt541);
}

static int zinitix_init_input_dev(stwuct bt541_ts_data *bt541)
{
	stwuct input_dev *input_dev;
	int ewwow;

	input_dev = devm_input_awwocate_device(&bt541->cwient->dev);
	if (!input_dev) {
		dev_eww(&bt541->cwient->dev,
			"Faiwed to awwocate input device.");
		wetuwn -ENOMEM;
	}

	input_set_dwvdata(input_dev, bt541);
	bt541->input_dev = input_dev;

	input_dev->name = "Zinitix Capacitive TouchScween";
	input_dev->phys = "input/ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->open = zinitix_input_open;
	input_dev->cwose = zinitix_input_cwose;

	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(input_dev, ABS_MT_WIDTH_MAJOW, 0, 255, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);

	touchscween_pawse_pwopewties(input_dev, twue, &bt541->pwop);
	if (!bt541->pwop.max_x || !bt541->pwop.max_y) {
		dev_eww(&bt541->cwient->dev,
			"Touchscween-size-x and/ow touchscween-size-y not set in dts\n");
		wetuwn -EINVAW;
	}

	ewwow = input_mt_init_swots(input_dev, MAX_SUPPOWTED_FINGEW_NUM,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(&bt541->cwient->dev,
			"Faiwed to initiawize MT swots: %d", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&bt541->cwient->dev,
			"Faiwed to wegistew input device: %d", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int zinitix_ts_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bt541_ts_data *bt541;
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev,
			"Faiwed to assewt adaptew's suppowt fow pwain I2C.\n");
		wetuwn -ENXIO;
	}

	bt541 = devm_kzawwoc(&cwient->dev, sizeof(*bt541), GFP_KEWNEW);
	if (!bt541)
		wetuwn -ENOMEM;

	bt541->cwient = cwient;
	i2c_set_cwientdata(cwient, bt541);

	ewwow = zinitix_init_weguwatows(bt541);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to initiawize weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, zinitix_ts_iwq_handwew,
					  IWQF_ONESHOT | IWQF_NO_AUTOEN,
					  cwient->name, bt541);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = zinitix_init_input_dev(bt541);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to initiawize input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = device_pwopewty_wead_u32(&cwient->dev, "zinitix,mode",
					 &bt541->zinitix_mode);
	if (ewwow < 0) {
		/* faww back to mode 2 */
		bt541->zinitix_mode = DEFAUWT_TOUCH_POINT_MODE;
	}

	if (bt541->zinitix_mode != 2) {
		/*
		 * If thewe awe devices that don't suppowt mode 2, suppowt
		 * fow othew modes (0, 1) wiww be needed.
		 */
		dev_eww(&cwient->dev,
			"Mawfowmed zinitix,mode pwopewty, must be 2 (suppwied: %d)\n",
			bt541->zinitix_mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int zinitix_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bt541_ts_data *bt541 = i2c_get_cwientdata(cwient);

	mutex_wock(&bt541->input_dev->mutex);

	if (input_device_enabwed(bt541->input_dev))
		zinitix_stop(bt541);

	mutex_unwock(&bt541->input_dev->mutex);

	wetuwn 0;
}

static int zinitix_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bt541_ts_data *bt541 = i2c_get_cwientdata(cwient);
	int wet = 0;

	mutex_wock(&bt541->input_dev->mutex);

	if (input_device_enabwed(bt541->input_dev))
		wet = zinitix_stawt(bt541);

	mutex_unwock(&bt541->input_dev->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(zinitix_pm_ops, zinitix_suspend, zinitix_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id zinitix_of_match[] = {
	{ .compatibwe = "zinitix,bt402" },
	{ .compatibwe = "zinitix,bt403" },
	{ .compatibwe = "zinitix,bt404" },
	{ .compatibwe = "zinitix,bt412" },
	{ .compatibwe = "zinitix,bt413" },
	{ .compatibwe = "zinitix,bt431" },
	{ .compatibwe = "zinitix,bt432" },
	{ .compatibwe = "zinitix,bt531" },
	{ .compatibwe = "zinitix,bt532" },
	{ .compatibwe = "zinitix,bt538" },
	{ .compatibwe = "zinitix,bt541" },
	{ .compatibwe = "zinitix,bt548" },
	{ .compatibwe = "zinitix,bt554" },
	{ .compatibwe = "zinitix,at100" },
	{ }
};
MODUWE_DEVICE_TABWE(of, zinitix_of_match);
#endif

static stwuct i2c_dwivew zinitix_ts_dwivew = {
	.pwobe = zinitix_ts_pwobe,
	.dwivew = {
		.name = "Zinitix-TS",
		.pm = pm_sweep_ptw(&zinitix_pm_ops),
		.of_match_tabwe = of_match_ptw(zinitix_of_match),
	},
};
moduwe_i2c_dwivew(zinitix_ts_dwivew);

MODUWE_AUTHOW("Michaew Swba <Michaew.Swba@seznam.cz>");
MODUWE_DESCWIPTION("Zinitix touchscween dwivew");
MODUWE_WICENSE("GPW v2");
