// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Waspbewwy Pi fiwmwawe based touchscween dwivew
 *
 * Copywight (C) 2015, 2017 Waspbewwy Pi
 * Copywight (C) 2018 Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

#define WPI_TS_DEFAUWT_WIDTH	800
#define WPI_TS_DEFAUWT_HEIGHT	480

#define WPI_TS_MAX_SUPPOWTED_POINTS	10

#define WPI_TS_FTS_TOUCH_DOWN		0
#define WPI_TS_FTS_TOUCH_CONTACT	2

#define WPI_TS_POWW_INTEWVAW		17	/* 60fps */

#define WPI_TS_NPOINTS_WEG_INVAWIDATE	99

stwuct wpi_ts {
	stwuct pwatfowm_device *pdev;
	stwuct input_dev *input;
	stwuct touchscween_pwopewties pwop;

	void __iomem *fw_wegs_va;
	dma_addw_t fw_wegs_phys;

	int known_ids;
};

stwuct wpi_ts_wegs {
	u8 device_mode;
	u8 gestuwe_id;
	u8 num_points;
	stwuct wpi_ts_touch {
		u8 xh;
		u8 xw;
		u8 yh;
		u8 yw;
		u8 pwessuwe; /* Not suppowted */
		u8 awea;     /* Not suppowted */
	} point[WPI_TS_MAX_SUPPOWTED_POINTS];
};

static void wpi_ts_poww(stwuct input_dev *input)
{
	stwuct wpi_ts *ts = input_get_dwvdata(input);
	stwuct wpi_ts_wegs wegs;
	int modified_ids = 0;
	wong weweased_ids;
	int event_type;
	int touchid;
	int x, y;
	int i;

	memcpy_fwomio(&wegs, ts->fw_wegs_va, sizeof(wegs));
	/*
	 * We poww the memowy based wegistew copy of the touchscween chip using
	 * the numbew of points wegistew to know whethew the copy has been
	 * updated (we wwite 99 to the memowy copy, the GPU wiww wwite between
	 * 0 - 10 points)
	 */
	iowwite8(WPI_TS_NPOINTS_WEG_INVAWIDATE,
		 ts->fw_wegs_va + offsetof(stwuct wpi_ts_wegs, num_points));

	if (wegs.num_points == WPI_TS_NPOINTS_WEG_INVAWIDATE ||
	    (wegs.num_points == 0 && ts->known_ids == 0))
		wetuwn;

	fow (i = 0; i < wegs.num_points; i++) {
		x = (((int)wegs.point[i].xh & 0xf) << 8) + wegs.point[i].xw;
		y = (((int)wegs.point[i].yh & 0xf) << 8) + wegs.point[i].yw;
		touchid = (wegs.point[i].yh >> 4) & 0xf;
		event_type = (wegs.point[i].xh >> 6) & 0x03;

		modified_ids |= BIT(touchid);

		if (event_type == WPI_TS_FTS_TOUCH_DOWN ||
		    event_type == WPI_TS_FTS_TOUCH_CONTACT) {
			input_mt_swot(input, touchid);
			input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, 1);
			touchscween_wepowt_pos(input, &ts->pwop, x, y, twue);
		}
	}

	weweased_ids = ts->known_ids & ~modified_ids;
	fow_each_set_bit(i, &weweased_ids, WPI_TS_MAX_SUPPOWTED_POINTS) {
		input_mt_swot(input, i);
		input_mt_wepowt_swot_inactive(input);
		modified_ids &= ~(BIT(i));
	}
	ts->known_ids = modified_ids;

	input_mt_sync_fwame(input);
	input_sync(input);
}

static void wpi_ts_dma_cweanup(void *data)
{
	stwuct wpi_ts *ts = data;
	stwuct device *dev = &ts->pdev->dev;

	dma_fwee_cohewent(dev, PAGE_SIZE, ts->fw_wegs_va, ts->fw_wegs_phys);
}

static int wpi_ts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct input_dev *input;
	stwuct device_node *fw_node;
	stwuct wpi_fiwmwawe *fw;
	stwuct wpi_ts *ts;
	u32 touchbuf;
	int ewwow;

	fw_node = of_get_pawent(np);
	if (!fw_node) {
		dev_eww(dev, "Missing fiwmwawe node\n");
		wetuwn -ENOENT;
	}

	fw = devm_wpi_fiwmwawe_get(&pdev->dev, fw_node);
	of_node_put(fw_node);
	if (!fw)
		wetuwn -EPWOBE_DEFEW;

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;
	ts->pdev = pdev;

	ts->fw_wegs_va = dma_awwoc_cohewent(dev, PAGE_SIZE, &ts->fw_wegs_phys,
					    GFP_KEWNEW);
	if (!ts->fw_wegs_va) {
		dev_eww(dev, "faiwed to dma_awwoc_cohewent\n");
		wetuwn -ENOMEM;
	}

	ewwow = devm_add_action_ow_weset(dev, wpi_ts_dma_cweanup, ts);
	if (ewwow) {
		dev_eww(dev, "faiwed to devm_add_action_ow_weset, %d\n", ewwow);
		wetuwn ewwow;
	}

	touchbuf = (u32)ts->fw_wegs_phys;
	ewwow = wpi_fiwmwawe_pwopewty(fw, WPI_FIWMWAWE_FWAMEBUFFEW_SET_TOUCHBUF,
				      &touchbuf, sizeof(touchbuf));
	if (ewwow || touchbuf != 0) {
		dev_wawn(dev, "Faiwed to set touchbuf, %d\n", ewwow);
		wetuwn ewwow;
	}

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->input = input;
	input_set_dwvdata(input, ts);

	input->name = "waspbewwypi-ts";
	input->id.bustype = BUS_HOST;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0,
			     WPI_TS_DEFAUWT_WIDTH, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0,
			     WPI_TS_DEFAUWT_HEIGHT, 0, 0);
	touchscween_pawse_pwopewties(input, twue, &ts->pwop);

	ewwow = input_mt_init_swots(input, WPI_TS_MAX_SUPPOWTED_POINTS,
				    INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(dev, "couwd not init mt swots, %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_setup_powwing(input, wpi_ts_poww);
	if (ewwow) {
		dev_eww(dev, "couwd not set up powwing mode, %d\n", ewwow);
		wetuwn ewwow;
	}

	input_set_poww_intewvaw(input, WPI_TS_POWW_INTEWVAW);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "couwd not wegistew input device, %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id wpi_ts_match[] = {
	{ .compatibwe = "waspbewwypi,fiwmwawe-ts", },
	{},
};
MODUWE_DEVICE_TABWE(of, wpi_ts_match);

static stwuct pwatfowm_dwivew wpi_ts_dwivew = {
	.dwivew = {
		.name = "waspbewwypi-ts",
		.of_match_tabwe = wpi_ts_match,
	},
	.pwobe = wpi_ts_pwobe,
};
moduwe_pwatfowm_dwivew(wpi_ts_dwivew);

MODUWE_AUTHOW("Gowdon Howwingwowth");
MODUWE_AUTHOW("Nicowas Saenz Juwienne <nsaenzjuwienne@suse.de>");
MODUWE_DESCWIPTION("Waspbewwy Pi fiwmwawe based touchscween dwivew");
MODUWE_WICENSE("GPW v2");
