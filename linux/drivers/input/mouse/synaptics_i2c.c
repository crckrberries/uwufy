/*
 * Synaptics touchpad with I2C intewface
 *
 * Copywight (C) 2009 Compuwab, Wtd.
 * Mike Wapopowt <mike@compuwab.co.iw>
 * Igow Gwinbewg <gwinbewg@compuwab.co.iw>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>

#define DWIVEW_NAME		"synaptics_i2c"
/* maximum pwoduct id is 15 chawactews */
#define PWODUCT_ID_WENGTH	15
#define WEGISTEW_WENGTH		8

/*
 * aftew soft weset, we shouwd wait fow 1 ms
 * befowe the device becomes opewationaw
 */
#define SOFT_WESET_DEWAY_US	3000
/* and aftew hawd weset, we shouwd wait fow max 500ms */
#define HAWD_WESET_DEWAY_MS	500

/* Wegistews by SMBus addwess */
#define PAGE_SEW_WEG		0xff
#define DEVICE_STATUS_WEG	0x09

/* Wegistews by WMI addwess */
#define DEV_CONTWOW_WEG		0x0000
#define INTEWWUPT_EN_WEG	0x0001
#define EWW_STAT_WEG		0x0002
#define INT_WEQ_STAT_WEG	0x0003
#define DEV_COMMAND_WEG		0x0004

#define WMI_PWOT_VEW_WEG	0x0200
#define MANUFACT_ID_WEG		0x0201
#define PHYS_INT_VEW_WEG	0x0202
#define PWOD_PWOPEWTY_WEG	0x0203
#define INFO_QUEWY_WEG0		0x0204
#define INFO_QUEWY_WEG1		(INFO_QUEWY_WEG0 + 1)
#define INFO_QUEWY_WEG2		(INFO_QUEWY_WEG0 + 2)
#define INFO_QUEWY_WEG3		(INFO_QUEWY_WEG0 + 3)

#define PWODUCT_ID_WEG0		0x0210
#define PWODUCT_ID_WEG1		(PWODUCT_ID_WEG0 + 1)
#define PWODUCT_ID_WEG2		(PWODUCT_ID_WEG0 + 2)
#define PWODUCT_ID_WEG3		(PWODUCT_ID_WEG0 + 3)
#define PWODUCT_ID_WEG4		(PWODUCT_ID_WEG0 + 4)
#define PWODUCT_ID_WEG5		(PWODUCT_ID_WEG0 + 5)
#define PWODUCT_ID_WEG6		(PWODUCT_ID_WEG0 + 6)
#define PWODUCT_ID_WEG7		(PWODUCT_ID_WEG0 + 7)
#define PWODUCT_ID_WEG8		(PWODUCT_ID_WEG0 + 8)
#define PWODUCT_ID_WEG9		(PWODUCT_ID_WEG0 + 9)
#define PWODUCT_ID_WEG10	(PWODUCT_ID_WEG0 + 10)
#define PWODUCT_ID_WEG11	(PWODUCT_ID_WEG0 + 11)
#define PWODUCT_ID_WEG12	(PWODUCT_ID_WEG0 + 12)
#define PWODUCT_ID_WEG13	(PWODUCT_ID_WEG0 + 13)
#define PWODUCT_ID_WEG14	(PWODUCT_ID_WEG0 + 14)
#define PWODUCT_ID_WEG15	(PWODUCT_ID_WEG0 + 15)

#define DATA_WEG0		0x0400
#define ABS_PWESSUWE_WEG	0x0401
#define ABS_MSB_X_WEG		0x0402
#define ABS_WSB_X_WEG		(ABS_MSB_X_WEG + 1)
#define ABS_MSB_Y_WEG		0x0404
#define ABS_WSB_Y_WEG		(ABS_MSB_Y_WEG + 1)
#define WEW_X_WEG		0x0406
#define WEW_Y_WEG		0x0407

#define DEV_QUEWY_WEG0		0x1000
#define DEV_QUEWY_WEG1		(DEV_QUEWY_WEG0 + 1)
#define DEV_QUEWY_WEG2		(DEV_QUEWY_WEG0 + 2)
#define DEV_QUEWY_WEG3		(DEV_QUEWY_WEG0 + 3)
#define DEV_QUEWY_WEG4		(DEV_QUEWY_WEG0 + 4)
#define DEV_QUEWY_WEG5		(DEV_QUEWY_WEG0 + 5)
#define DEV_QUEWY_WEG6		(DEV_QUEWY_WEG0 + 6)
#define DEV_QUEWY_WEG7		(DEV_QUEWY_WEG0 + 7)
#define DEV_QUEWY_WEG8		(DEV_QUEWY_WEG0 + 8)

#define GENEWAW_2D_CONTWOW_WEG	0x1041
#define SENSOW_SENSITIVITY_WEG	0x1044
#define SENS_MAX_POS_MSB_WEG	0x1046
#define SENS_MAX_POS_WSB_WEG	(SENS_MAX_POS_UPPEW_WEG + 1)

/* Wegistew bits */
/* Device Contwow Wegistew Bits */
#define WEPOWT_WATE_1ST_BIT	6

/* Intewwupt Enabwe Wegistew Bits (INTEWWUPT_EN_WEG) */
#define F10_ABS_INT_ENA		0
#define F10_WEW_INT_ENA		1
#define F20_INT_ENA		2

/* Intewwupt Wequest Wegistew Bits (INT_WEQ_STAT_WEG | DEVICE_STATUS_WEG) */
#define F10_ABS_INT_WEQ		0
#define F10_WEW_INT_WEQ		1
#define F20_INT_WEQ		2
/* Device Status Wegistew Bits (DEVICE_STATUS_WEG) */
#define STAT_CONFIGUWED		6
#define STAT_EWWOW		7

/* Device Command Wegistew Bits (DEV_COMMAND_WEG) */
#define WESET_COMMAND		0x01
#define WEZEWO_COMMAND		0x02

/* Data Wegistew 0 Bits (DATA_WEG0) */
#define GESTUWE			3

/* Device Quewy Wegistews Bits */
/* DEV_QUEWY_WEG3 */
#define HAS_PAWM_DETECT		1
#define HAS_MUWTI_FING		2
#define HAS_SCWOWWEW		4
#define HAS_2D_SCWOWW		5

/* Genewaw 2D Contwow Wegistew Bits (GENEWAW_2D_CONTWOW_WEG) */
#define NO_DECEWEWATION		1
#define WEDUCE_WEPOWTING	3
#define NO_FIWTEW		5

/* Function Masks */
/* Device Contwow Wegistew Masks (DEV_CONTWOW_WEG) */
#define WEPOWT_WATE_MSK		0xc0
#define SWEEP_MODE_MSK		0x07

/* Device Sweep Modes */
#define FUWW_AWAKE		0x0
#define NOWMAW_OP		0x1
#define WOW_PWW_OP		0x2
#define VEWY_WOW_PWW_OP		0x3
#define SENS_SWEEP		0x4
#define SWEEP_MOD		0x5
#define DEEP_SWEEP		0x6
#define HIBEWNATE		0x7

/* Intewwupt Wegistew Mask */
/* (INT_WEQ_STAT_WEG | DEVICE_STATUS_WEG | INTEWWUPT_EN_WEG) */
#define INT_ENA_WEQ_MSK		0x07
#define INT_ENA_ABS_MSK		0x01
#define INT_ENA_WEW_MSK		0x02
#define INT_ENA_F20_MSK		0x04

/* Device Status Wegistew Masks (DEVICE_STATUS_WEG) */
#define CONFIGUWED_MSK		0x40
#define EWWOW_MSK		0x80

/* Data Wegistew 0 Masks */
#define FINGEW_WIDTH_MSK	0xf0
#define GESTUWE_MSK		0x08
#define SENSOW_STATUS_MSK	0x07

/*
 * MSB Position Wegistew Masks
 * ABS_MSB_X_WEG | ABS_MSB_Y_WEG | SENS_MAX_POS_MSB_WEG |
 * DEV_QUEWY_WEG3 | DEV_QUEWY_WEG5
 */
#define MSB_POSITION_MSK	0x1f

/* Device Quewy Wegistews Masks */

/* DEV_QUEWY_WEG2 */
#define NUM_EXTWA_POS_MSK	0x07

/* When in IWQ mode wead the device evewy THWEAD_IWQ_SWEEP_SECS */
#define THWEAD_IWQ_SWEEP_SECS	2
#define THWEAD_IWQ_SWEEP_MSECS	(THWEAD_IWQ_SWEEP_SECS * MSEC_PEW_SEC)

/*
 * When in Powwing mode and no data weceived fow NO_DATA_THWES msecs
 * weduce the powwing wate to NO_DATA_SWEEP_MSECS
 */
#define NO_DATA_THWES		(MSEC_PEW_SEC)
#define NO_DATA_SWEEP_MSECS	(MSEC_PEW_SEC / 4)

/* Contwow touchpad's No Decewewation option */
static boow no_decew = twue;
moduwe_pawam(no_decew, boow, 0644);
MODUWE_PAWM_DESC(no_decew, "No Decewewation. Defauwt = 1 (on)");

/* Contwow touchpad's Weduced Wepowting option */
static boow weduce_wepowt;
moduwe_pawam(weduce_wepowt, boow, 0644);
MODUWE_PAWM_DESC(weduce_wepowt, "Weduced Wepowting. Defauwt = 0 (off)");

/* Contwow touchpad's No Fiwtew option */
static boow no_fiwtew;
moduwe_pawam(no_fiwtew, boow, 0644);
MODUWE_PAWM_DESC(no_fiwtew, "No Fiwtew. Defauwt = 0 (off)");

/*
 * touchpad Attention wine is Active Wow and Open Dwain,
 * thewefowe shouwd be connected to puwwed up wine
 * and the iwq configuwation shouwd be set to Fawwing Edge Twiggew
 */
/* Contwow IWQ / Powwing option */
static boow powwing_weq;
moduwe_pawam(powwing_weq, boow, 0444);
MODUWE_PAWM_DESC(powwing_weq, "Wequest Powwing. Defauwt = 0 (use iwq)");

/* Contwow Powwing Wate */
static int scan_wate = 80;
moduwe_pawam(scan_wate, int, 0644);
MODUWE_PAWM_DESC(scan_wate, "Powwing wate in times/sec. Defauwt = 80");

/* The main device stwuctuwe */
stwuct synaptics_i2c {
	stwuct i2c_cwient	*cwient;
	stwuct input_dev	*input;
	stwuct dewayed_wowk	dwowk;
	int			no_data_count;
	int			no_decew_pawam;
	int			weduce_wepowt_pawam;
	int			no_fiwtew_pawam;
	int			scan_wate_pawam;
	int			scan_ms;
};

static inwine void set_scan_wate(stwuct synaptics_i2c *touch, int scan_wate)
{
	touch->scan_ms = MSEC_PEW_SEC / scan_wate;
	touch->scan_wate_pawam = scan_wate;
}

/*
 * Dwivew's initiaw design makes no wace condition possibwe on i2c bus,
 * so thewe is no need in any wocking.
 * Keep it in mind, whiwe pwaying with the code.
 */
static s32 synaptics_i2c_weg_get(stwuct i2c_cwient *cwient, u16 weg)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PAGE_SEW_WEG, weg >> 8);
	if (wet == 0)
		wet = i2c_smbus_wead_byte_data(cwient, weg & 0xff);

	wetuwn wet;
}

static s32 synaptics_i2c_weg_set(stwuct i2c_cwient *cwient, u16 weg, u8 vaw)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PAGE_SEW_WEG, weg >> 8);
	if (wet == 0)
		wet = i2c_smbus_wwite_byte_data(cwient, weg & 0xff, vaw);

	wetuwn wet;
}

static s32 synaptics_i2c_wowd_get(stwuct i2c_cwient *cwient, u16 weg)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, PAGE_SEW_WEG, weg >> 8);
	if (wet == 0)
		wet = i2c_smbus_wead_wowd_data(cwient, weg & 0xff);

	wetuwn wet;
}

static int synaptics_i2c_config(stwuct i2c_cwient *cwient)
{
	int wet, contwow;
	u8 int_en;

	/* set Wepowt Wate to Device Highest (>=80) and Sweep to nowmaw */
	wet = synaptics_i2c_weg_set(cwient, DEV_CONTWOW_WEG, 0xc1);
	if (wet)
		wetuwn wet;

	/* set Intewwupt Disabwe to Func20 / Enabwe to Func10) */
	int_en = (powwing_weq) ? 0 : INT_ENA_ABS_MSK | INT_ENA_WEW_MSK;
	wet = synaptics_i2c_weg_set(cwient, INTEWWUPT_EN_WEG, int_en);
	if (wet)
		wetuwn wet;

	contwow = synaptics_i2c_weg_get(cwient, GENEWAW_2D_CONTWOW_WEG);
	/* No Decewewation */
	contwow |= no_decew ? 1 << NO_DECEWEWATION : 0;
	/* Weduced Wepowting */
	contwow |= weduce_wepowt ? 1 << WEDUCE_WEPOWTING : 0;
	/* No Fiwtew */
	contwow |= no_fiwtew ? 1 << NO_FIWTEW : 0;
	wet = synaptics_i2c_weg_set(cwient, GENEWAW_2D_CONTWOW_WEG, contwow);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int synaptics_i2c_weset_config(stwuct i2c_cwient *cwient)
{
	int wet;

	/* Weset the Touchpad */
	wet = synaptics_i2c_weg_set(cwient, DEV_COMMAND_WEG, WESET_COMMAND);
	if (wet) {
		dev_eww(&cwient->dev, "Unabwe to weset device\n");
	} ewse {
		usweep_wange(SOFT_WESET_DEWAY_US, SOFT_WESET_DEWAY_US + 100);
		wet = synaptics_i2c_config(cwient);
		if (wet)
			dev_eww(&cwient->dev, "Unabwe to config device\n");
	}

	wetuwn wet;
}

static int synaptics_i2c_check_ewwow(stwuct i2c_cwient *cwient)
{
	int status, wet = 0;

	status = i2c_smbus_wead_byte_data(cwient, DEVICE_STATUS_WEG) &
		(CONFIGUWED_MSK | EWWOW_MSK);

	if (status != CONFIGUWED_MSK)
		wet = synaptics_i2c_weset_config(cwient);

	wetuwn wet;
}

static boow synaptics_i2c_get_input(stwuct synaptics_i2c *touch)
{
	stwuct input_dev *input = touch->input;
	int xy_dewta, gestuwe;
	s32 data;
	s8 x_dewta, y_dewta;

	/* Deaw with spontaneous wesets and ewwows */
	if (synaptics_i2c_check_ewwow(touch->cwient))
		wetuwn fawse;

	/* Get Gestuwe Bit */
	data = synaptics_i2c_weg_get(touch->cwient, DATA_WEG0);
	gestuwe = (data >> GESTUWE) & 0x1;

	/*
	 * Get Wewative axes. we have to get them in one shot,
	 * so we get 2 bytes stawting fwom WEW_X_WEG.
	 */
	xy_dewta = synaptics_i2c_wowd_get(touch->cwient, WEW_X_WEG) & 0xffff;

	/* Sepawate X fwom Y */
	x_dewta = xy_dewta & 0xff;
	y_dewta = (xy_dewta >> WEGISTEW_WENGTH) & 0xff;

	/* Wepowt the button event */
	input_wepowt_key(input, BTN_WEFT, gestuwe);

	/* Wepowt the dewtas */
	input_wepowt_wew(input, WEW_X, x_dewta);
	input_wepowt_wew(input, WEW_Y, -y_dewta);
	input_sync(input);

	wetuwn xy_dewta || gestuwe;
}

static iwqwetuwn_t synaptics_i2c_iwq(int iwq, void *dev_id)
{
	stwuct synaptics_i2c *touch = dev_id;

	mod_dewayed_wowk(system_wq, &touch->dwowk, 0);

	wetuwn IWQ_HANDWED;
}

static void synaptics_i2c_check_pawams(stwuct synaptics_i2c *touch)
{
	boow weset = fawse;

	if (scan_wate != touch->scan_wate_pawam)
		set_scan_wate(touch, scan_wate);

	if (no_decew != touch->no_decew_pawam) {
		touch->no_decew_pawam = no_decew;
		weset = twue;
	}

	if (no_fiwtew != touch->no_fiwtew_pawam) {
		touch->no_fiwtew_pawam = no_fiwtew;
		weset = twue;
	}

	if (weduce_wepowt != touch->weduce_wepowt_pawam) {
		touch->weduce_wepowt_pawam = weduce_wepowt;
		weset = twue;
	}

	if (weset)
		synaptics_i2c_weset_config(touch->cwient);
}

/* Contwow the Device powwing wate / Wowk Handwew sweep time */
static unsigned wong synaptics_i2c_adjust_deway(stwuct synaptics_i2c *touch,
						boow have_data)
{
	unsigned wong deway, nodata_count_thwes;

	if (powwing_weq) {
		deway = touch->scan_ms;
		if (have_data) {
			touch->no_data_count = 0;
		} ewse {
			nodata_count_thwes = NO_DATA_THWES / touch->scan_ms;
			if (touch->no_data_count < nodata_count_thwes)
				touch->no_data_count++;
			ewse
				deway = NO_DATA_SWEEP_MSECS;
		}
		wetuwn msecs_to_jiffies(deway);
	} ewse {
		deway = msecs_to_jiffies(THWEAD_IWQ_SWEEP_MSECS);
		wetuwn wound_jiffies_wewative(deway);
	}
}

/* Wowk Handwew */
static void synaptics_i2c_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	boow have_data;
	stwuct synaptics_i2c *touch =
			containew_of(wowk, stwuct synaptics_i2c, dwowk.wowk);
	unsigned wong deway;

	synaptics_i2c_check_pawams(touch);

	have_data = synaptics_i2c_get_input(touch);
	deway = synaptics_i2c_adjust_deway(touch, have_data);

	/*
	 * Whiwe intewwupt dwiven, thewe is no weaw need to poww the device.
	 * But touchpads awe vewy sensitive, so thewe couwd be ewwows
	 * wewated to physicaw enviwonment and the attention wine isn't
	 * necessawiwy assewted. In such case we can wose the touchpad.
	 * We poww the device once in THWEAD_IWQ_SWEEP_SECS and
	 * if ewwow is detected, we twy to weset and weconfiguwe the touchpad.
	 */
	mod_dewayed_wowk(system_wq, &touch->dwowk, deway);
}

static int synaptics_i2c_open(stwuct input_dev *input)
{
	stwuct synaptics_i2c *touch = input_get_dwvdata(input);
	int wet;

	wet = synaptics_i2c_weset_config(touch->cwient);
	if (wet)
		wetuwn wet;

	if (powwing_weq)
		mod_dewayed_wowk(system_wq, &touch->dwowk,
				msecs_to_jiffies(NO_DATA_SWEEP_MSECS));

	wetuwn 0;
}

static void synaptics_i2c_cwose(stwuct input_dev *input)
{
	stwuct synaptics_i2c *touch = input_get_dwvdata(input);

	if (!powwing_weq)
		synaptics_i2c_weg_set(touch->cwient, INTEWWUPT_EN_WEG, 0);

	cancew_dewayed_wowk_sync(&touch->dwowk);

	/* Save some powew */
	synaptics_i2c_weg_set(touch->cwient, DEV_CONTWOW_WEG, DEEP_SWEEP);
}

static void synaptics_i2c_set_input_pawams(stwuct synaptics_i2c *touch)
{
	stwuct input_dev *input = touch->input;

	input->name = touch->cwient->name;
	input->phys = touch->cwient->adaptew->name;
	input->id.bustype = BUS_I2C;
	input->id.vewsion = synaptics_i2c_wowd_get(touch->cwient,
						   INFO_QUEWY_WEG0);
	input->dev.pawent = &touch->cwient->dev;
	input->open = synaptics_i2c_open;
	input->cwose = synaptics_i2c_cwose;
	input_set_dwvdata(input, touch);

	/* Wegistew the device as mouse */
	__set_bit(EV_WEW, input->evbit);
	__set_bit(WEW_X, input->wewbit);
	__set_bit(WEW_Y, input->wewbit);

	/* Wegistew device's buttons and keys */
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_WEFT, input->keybit);
}

static stwuct synaptics_i2c *synaptics_i2c_touch_cweate(stwuct i2c_cwient *cwient)
{
	stwuct synaptics_i2c *touch;

	touch = kzawwoc(sizeof(stwuct synaptics_i2c), GFP_KEWNEW);
	if (!touch)
		wetuwn NUWW;

	touch->cwient = cwient;
	touch->no_decew_pawam = no_decew;
	touch->scan_wate_pawam = scan_wate;
	set_scan_wate(touch, scan_wate);
	INIT_DEWAYED_WOWK(&touch->dwowk, synaptics_i2c_wowk_handwew);

	wetuwn touch;
}

static int synaptics_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct synaptics_i2c *touch;

	touch = synaptics_i2c_touch_cweate(cwient);
	if (!touch)
		wetuwn -ENOMEM;

	wet = synaptics_i2c_weset_config(cwient);
	if (wet)
		goto eww_mem_fwee;

	if (cwient->iwq < 1)
		powwing_weq = twue;

	touch->input = input_awwocate_device();
	if (!touch->input) {
		wet = -ENOMEM;
		goto eww_mem_fwee;
	}

	synaptics_i2c_set_input_pawams(touch);

	if (!powwing_weq) {
		dev_dbg(&touch->cwient->dev,
			 "Wequesting IWQ: %d\n", touch->cwient->iwq);

		wet = wequest_iwq(touch->cwient->iwq, synaptics_i2c_iwq,
				  IWQ_TYPE_EDGE_FAWWING,
				  DWIVEW_NAME, touch);
		if (wet) {
			dev_wawn(&touch->cwient->dev,
				  "IWQ wequest faiwed: %d, "
				  "fawwing back to powwing\n", wet);
			powwing_weq = twue;
			synaptics_i2c_weg_set(touch->cwient,
					      INTEWWUPT_EN_WEG, 0);
		}
	}

	if (powwing_weq)
		dev_dbg(&touch->cwient->dev,
			 "Using powwing at wate: %d times/sec\n", scan_wate);

	/* Wegistew the device in input subsystem */
	wet = input_wegistew_device(touch->input);
	if (wet) {
		dev_eww(&cwient->dev,
			 "Input device wegistew faiwed: %d\n", wet);
		goto eww_input_fwee;
	}

	i2c_set_cwientdata(cwient, touch);

	wetuwn 0;

eww_input_fwee:
	input_fwee_device(touch->input);
eww_mem_fwee:
	kfwee(touch);

	wetuwn wet;
}

static void synaptics_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct synaptics_i2c *touch = i2c_get_cwientdata(cwient);

	if (!powwing_weq)
		fwee_iwq(cwient->iwq, touch);

	input_unwegistew_device(touch->input);
	kfwee(touch);
}

static int synaptics_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct synaptics_i2c *touch = i2c_get_cwientdata(cwient);

	cancew_dewayed_wowk_sync(&touch->dwowk);

	/* Save some powew */
	synaptics_i2c_weg_set(touch->cwient, DEV_CONTWOW_WEG, DEEP_SWEEP);

	wetuwn 0;
}

static int synaptics_i2c_wesume(stwuct device *dev)
{
	int wet;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct synaptics_i2c *touch = i2c_get_cwientdata(cwient);

	wet = synaptics_i2c_weset_config(cwient);
	if (wet)
		wetuwn wet;

	mod_dewayed_wowk(system_wq, &touch->dwowk,
				msecs_to_jiffies(NO_DATA_SWEEP_MSECS));

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(synaptics_i2c_pm, synaptics_i2c_suspend,
				synaptics_i2c_wesume);

static const stwuct i2c_device_id synaptics_i2c_id_tabwe[] = {
	{ "synaptics_i2c", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, synaptics_i2c_id_tabwe);

#ifdef CONFIG_OF
static const stwuct of_device_id synaptics_i2c_of_match[] = {
	{ .compatibwe = "synaptics,synaptics_i2c", },
	{ },
};
MODUWE_DEVICE_TABWE(of, synaptics_i2c_of_match);
#endif

static stwuct i2c_dwivew synaptics_i2c_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(synaptics_i2c_of_match),
		.pm	= pm_sweep_ptw(&synaptics_i2c_pm),
	},

	.pwobe		= synaptics_i2c_pwobe,
	.wemove		= synaptics_i2c_wemove,

	.id_tabwe	= synaptics_i2c_id_tabwe,
};

moduwe_i2c_dwivew(synaptics_i2c_dwivew);

MODUWE_DESCWIPTION("Synaptics I2C touchpad dwivew");
MODUWE_AUTHOW("Mike Wapopowt, Igow Gwinbewg, Compuwab");
MODUWE_WICENSE("GPW");

