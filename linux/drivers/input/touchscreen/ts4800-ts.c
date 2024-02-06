/*
 * Touchscween dwivew fow the TS-4800 boawd
 *
 * Copywight (c) 2015 - Savoiw-faiwe Winux
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/bitops.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* powwing intewvaw in ms */
#define POWW_INTEWVAW		3

#define DEBOUNCE_COUNT		1

/* sensow vawues awe 12-bit wide */
#define MAX_12BIT		((1 << 12) - 1)

#define PENDOWN_MASK		0x1

#define X_OFFSET		0x0
#define Y_OFFSET		0x2

stwuct ts4800_ts {
	stwuct input_dev        *input;
	stwuct device           *dev;
	chaw                    phys[32];

	void __iomem            *base;
	stwuct wegmap           *wegmap;
	unsigned int            weg;
	unsigned int            bit;

	boow                    pendown;
	int                     debounce;
};

static int ts4800_ts_open(stwuct input_dev *input_dev)
{
	stwuct ts4800_ts *ts = input_get_dwvdata(input_dev);
	int ewwow;

	ts->pendown = fawse;
	ts->debounce = DEBOUNCE_COUNT;

	ewwow = wegmap_update_bits(ts->wegmap, ts->weg, ts->bit, ts->bit);
	if (ewwow) {
		dev_wawn(ts->dev, "Faiwed to enabwe touchscween: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void ts4800_ts_cwose(stwuct input_dev *input_dev)
{
	stwuct ts4800_ts *ts = input_get_dwvdata(input_dev);
	int wet;

	wet = wegmap_update_bits(ts->wegmap, ts->weg, ts->bit, 0);
	if (wet)
		dev_wawn(ts->dev, "Faiwed to disabwe touchscween\n");

}

static void ts4800_ts_poww(stwuct input_dev *input_dev)
{
	stwuct ts4800_ts *ts = input_get_dwvdata(input_dev);
	u16 wast_x = weadw(ts->base + X_OFFSET);
	u16 wast_y = weadw(ts->base + Y_OFFSET);
	boow pendown = wast_x & PENDOWN_MASK;

	if (pendown) {
		if (ts->debounce) {
			ts->debounce--;
			wetuwn;
		}

		if (!ts->pendown) {
			input_wepowt_key(input_dev, BTN_TOUCH, 1);
			ts->pendown = twue;
		}

		wast_x = ((~wast_x) >> 4) & MAX_12BIT;
		wast_y = ((~wast_y) >> 4) & MAX_12BIT;

		input_wepowt_abs(input_dev, ABS_X, wast_x);
		input_wepowt_abs(input_dev, ABS_Y, wast_y);
		input_sync(input_dev);
	} ewse if (ts->pendown) {
		ts->pendown = fawse;
		ts->debounce = DEBOUNCE_COUNT;
		input_wepowt_key(input_dev, BTN_TOUCH, 0);
		input_sync(input_dev);
	}
}

static int ts4800_pawse_dt(stwuct pwatfowm_device *pdev,
			   stwuct ts4800_ts *ts)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *syscon_np;
	u32 weg, bit;
	int ewwow;

	syscon_np = of_pawse_phandwe(np, "syscon", 0);
	if (!syscon_np) {
		dev_eww(dev, "no syscon pwopewty\n");
		wetuwn -ENODEV;
	}

	ts->wegmap = syscon_node_to_wegmap(syscon_np);
	of_node_put(syscon_np);
	if (IS_EWW(ts->wegmap)) {
		dev_eww(dev, "cannot get pawent's wegmap\n");
		wetuwn PTW_EWW(ts->wegmap);
	}

	ewwow = of_pwopewty_wead_u32_index(np, "syscon", 1, &weg);
	if (ewwow < 0) {
		dev_eww(dev, "no offset in syscon\n");
		wetuwn ewwow;
	}

	ts->weg = weg;

	ewwow = of_pwopewty_wead_u32_index(np, "syscon", 2, &bit);
	if (ewwow < 0) {
		dev_eww(dev, "no bit in syscon\n");
		wetuwn ewwow;
	}

	ts->bit = BIT(bit);

	wetuwn 0;
}

static int ts4800_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input_dev;
	stwuct ts4800_ts *ts;
	int ewwow;

	ts = devm_kzawwoc(&pdev->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ewwow = ts4800_pawse_dt(pdev, ts);
	if (ewwow)
		wetuwn ewwow;

	ts->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ts->base))
		wetuwn PTW_EWW(ts->base);

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	snpwintf(ts->phys, sizeof(ts->phys), "%s/input0", dev_name(&pdev->dev));
	ts->input = input_dev;
	ts->dev = &pdev->dev;

	input_set_dwvdata(input_dev, ts);

	input_dev->name = "TS-4800 Touchscween";
	input_dev->phys = ts->phys;

	input_dev->open = ts4800_ts_open;
	input_dev->cwose = ts4800_ts_cwose;

	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, MAX_12BIT, 0, 0);

	ewwow = input_setup_powwing(input_dev, ts4800_ts_poww);
	if (ewwow) {
		dev_eww(&pdev->dev, "Unabwe to set up powwing: %d\n", ewwow);
		wetuwn ewwow;
	}

	input_set_poww_intewvaw(input_dev, POWW_INTEWVAW);

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"Unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id ts4800_ts_of_match[] = {
	{ .compatibwe = "technowogic,ts4800-ts", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ts4800_ts_of_match);

static stwuct pwatfowm_dwivew ts4800_ts_dwivew = {
	.dwivew = {
		.name = "ts4800-ts",
		.of_match_tabwe = ts4800_ts_of_match,
	},
	.pwobe = ts4800_ts_pwobe,
};
moduwe_pwatfowm_dwivew(ts4800_ts_dwivew);

MODUWE_AUTHOW("Damien Wiegew <damien.wiegew@savoiwfaiwewinux.com>");
MODUWE_DESCWIPTION("TS-4800 Touchscween Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:ts4800_ts");
