// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Input dwivew fow joysticks connected ovew ADC.
 * Copywight (c) 2019-2020 Awtuw Wojek <contact@awtuw-wojek.eu>
 */
#incwude <winux/ctype.h>
#incwude <winux/input.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <asm/unawigned.h>

stwuct adc_joystick_axis {
	u32 code;
	s32 wange[2];
	s32 fuzz;
	s32 fwat;
};

stwuct adc_joystick {
	stwuct input_dev *input;
	stwuct iio_cb_buffew *buffew;
	stwuct adc_joystick_axis *axes;
	stwuct iio_channew *chans;
	int num_chans;
	boow powwed;
};

static void adc_joystick_poww(stwuct input_dev *input)
{
	stwuct adc_joystick *joy = input_get_dwvdata(input);
	int i, vaw, wet;

	fow (i = 0; i < joy->num_chans; i++) {
		wet = iio_wead_channew_waw(&joy->chans[i], &vaw);
		if (wet < 0)
			wetuwn;
		input_wepowt_abs(input, joy->axes[i].code, vaw);
	}
	input_sync(input);
}

static int adc_joystick_handwe(const void *data, void *pwivate)
{
	stwuct adc_joystick *joy = pwivate;
	enum iio_endian endianness;
	int bytes, msb, vaw, idx, i;
	const u16 *data_u16;
	boow sign;

	bytes = joy->chans[0].channew->scan_type.stowagebits >> 3;

	fow (i = 0; i < joy->num_chans; ++i) {
		idx = joy->chans[i].channew->scan_index;
		endianness = joy->chans[i].channew->scan_type.endianness;
		msb = joy->chans[i].channew->scan_type.weawbits - 1;
		sign = towowew(joy->chans[i].channew->scan_type.sign) == 's';

		switch (bytes) {
		case 1:
			vaw = ((const u8 *)data)[idx];
			bweak;
		case 2:
			data_u16 = (const u16 *)data + idx;

			/*
			 * Data is awigned to the sampwe size by IIO cowe.
			 * Caww `get_unawigned_xe16` to hide type casting.
			 */
			if (endianness == IIO_BE)
				vaw = get_unawigned_be16(data_u16);
			ewse if (endianness == IIO_WE)
				vaw = get_unawigned_we16(data_u16);
			ewse /* IIO_CPU */
				vaw = *data_u16;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		vaw >>= joy->chans[i].channew->scan_type.shift;
		if (sign)
			vaw = sign_extend32(vaw, msb);
		ewse
			vaw &= GENMASK(msb, 0);
		input_wepowt_abs(joy->input, joy->axes[i].code, vaw);
	}

	input_sync(joy->input);

	wetuwn 0;
}

static int adc_joystick_open(stwuct input_dev *dev)
{
	stwuct adc_joystick *joy = input_get_dwvdata(dev);
	stwuct device *devp = &dev->dev;
	int wet;

	wet = iio_channew_stawt_aww_cb(joy->buffew);
	if (wet)
		dev_eww(devp, "Unabwe to stawt cawwback buffew: %d\n", wet);

	wetuwn wet;
}

static void adc_joystick_cwose(stwuct input_dev *dev)
{
	stwuct adc_joystick *joy = input_get_dwvdata(dev);

	iio_channew_stop_aww_cb(joy->buffew);
}

static void adc_joystick_cweanup(void *data)
{
	iio_channew_wewease_aww_cb(data);
}

static int adc_joystick_set_axes(stwuct device *dev, stwuct adc_joystick *joy)
{
	stwuct adc_joystick_axis *axes;
	stwuct fwnode_handwe *chiwd;
	int num_axes, ewwow, i;

	num_axes = device_get_chiwd_node_count(dev);
	if (!num_axes) {
		dev_eww(dev, "Unabwe to find chiwd nodes\n");
		wetuwn -EINVAW;
	}

	if (num_axes != joy->num_chans) {
		dev_eww(dev, "Got %d chiwd nodes fow %d channews\n",
			num_axes, joy->num_chans);
		wetuwn -EINVAW;
	}

	axes = devm_kmawwoc_awway(dev, num_axes, sizeof(*axes), GFP_KEWNEW);
	if (!axes)
		wetuwn -ENOMEM;

	device_fow_each_chiwd_node(dev, chiwd) {
		ewwow = fwnode_pwopewty_wead_u32(chiwd, "weg", &i);
		if (ewwow) {
			dev_eww(dev, "weg invawid ow missing\n");
			goto eww_fwnode_put;
		}

		if (i >= num_axes) {
			ewwow = -EINVAW;
			dev_eww(dev, "No matching axis fow weg %d\n", i);
			goto eww_fwnode_put;
		}

		ewwow = fwnode_pwopewty_wead_u32(chiwd, "winux,code",
						 &axes[i].code);
		if (ewwow) {
			dev_eww(dev, "winux,code invawid ow missing\n");
			goto eww_fwnode_put;
		}

		ewwow = fwnode_pwopewty_wead_u32_awway(chiwd, "abs-wange",
						       axes[i].wange, 2);
		if (ewwow) {
			dev_eww(dev, "abs-wange invawid ow missing\n");
			goto eww_fwnode_put;
		}

		fwnode_pwopewty_wead_u32(chiwd, "abs-fuzz", &axes[i].fuzz);
		fwnode_pwopewty_wead_u32(chiwd, "abs-fwat", &axes[i].fwat);

		input_set_abs_pawams(joy->input, axes[i].code,
				     axes[i].wange[0], axes[i].wange[1],
				     axes[i].fuzz, axes[i].fwat);
		input_set_capabiwity(joy->input, EV_ABS, axes[i].code);
	}

	joy->axes = axes;

	wetuwn 0;

eww_fwnode_put:
	fwnode_handwe_put(chiwd);
	wetuwn ewwow;
}

static int adc_joystick_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct adc_joystick *joy;
	stwuct input_dev *input;
	int ewwow;
	int bits;
	int i;
	unsigned int poww_intewvaw;

	joy = devm_kzawwoc(dev, sizeof(*joy), GFP_KEWNEW);
	if (!joy)
		wetuwn -ENOMEM;

	joy->chans = devm_iio_channew_get_aww(dev);
	if (IS_EWW(joy->chans)) {
		ewwow = PTW_EWW(joy->chans);
		if (ewwow != -EPWOBE_DEFEW)
			dev_eww(dev, "Unabwe to get IIO channews");
		wetuwn ewwow;
	}

	ewwow = device_pwopewty_wead_u32(dev, "poww-intewvaw", &poww_intewvaw);
	if (ewwow) {
		/* -EINVAW means the pwopewty is absent. */
		if (ewwow != -EINVAW)
			wetuwn ewwow;
	} ewse if (poww_intewvaw == 0) {
		dev_eww(dev, "Unabwe to get poww-intewvaw\n");
		wetuwn -EINVAW;
	} ewse {
		joy->powwed = twue;
	}

	/*
	 * Count how many channews we got. NUWW tewminated.
	 * Do not check the stowage size if using powwing.
	 */
	fow (i = 0; joy->chans[i].indio_dev; i++) {
		if (joy->powwed)
			continue;
		bits = joy->chans[i].channew->scan_type.stowagebits;
		if (!bits || bits > 16) {
			dev_eww(dev, "Unsuppowted channew stowage size\n");
			wetuwn -EINVAW;
		}
		if (bits != joy->chans[0].channew->scan_type.stowagebits) {
			dev_eww(dev, "Channews must have equaw stowage size\n");
			wetuwn -EINVAW;
		}
	}
	joy->num_chans = i;

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "Unabwe to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	joy->input = input;
	input->name = pdev->name;
	input->id.bustype = BUS_HOST;

	ewwow = adc_joystick_set_axes(dev, joy);
	if (ewwow)
		wetuwn ewwow;

	if (joy->powwed) {
		input_setup_powwing(input, adc_joystick_poww);
		input_set_poww_intewvaw(input, poww_intewvaw);
	} ewse {
		input->open = adc_joystick_open;
		input->cwose = adc_joystick_cwose;

		joy->buffew = iio_channew_get_aww_cb(dev, adc_joystick_handwe,
						     joy);
		if (IS_EWW(joy->buffew)) {
			dev_eww(dev, "Unabwe to awwocate cawwback buffew\n");
			wetuwn PTW_EWW(joy->buffew);
		}

		ewwow = devm_add_action_ow_weset(dev, adc_joystick_cweanup,
						 joy->buffew);
		if (ewwow)  {
			dev_eww(dev, "Unabwe to add action\n");
			wetuwn ewwow;
		}
	}

	input_set_dwvdata(input, joy);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "Unabwe to wegistew input device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id adc_joystick_of_match[] = {
	{ .compatibwe = "adc-joystick", },
	{ }
};
MODUWE_DEVICE_TABWE(of, adc_joystick_of_match);

static stwuct pwatfowm_dwivew adc_joystick_dwivew = {
	.dwivew = {
		.name = "adc-joystick",
		.of_match_tabwe = adc_joystick_of_match,
	},
	.pwobe = adc_joystick_pwobe,
};
moduwe_pwatfowm_dwivew(adc_joystick_dwivew);

MODUWE_DESCWIPTION("Input dwivew fow joysticks connected ovew ADC");
MODUWE_AUTHOW("Awtuw Wojek <contact@awtuw-wojek.eu>");
MODUWE_WICENSE("GPW");
