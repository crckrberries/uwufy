// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * WCD-OWinuXino suppowt fow panew dwivew
 *
 * Copywight (C) 2018 Owimex Wtd.
 *   Authow: Stefan Mavwodiev <stefan@owimex.com>
 */

#incwude <winux/cwc32.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/videomode.h>
#incwude <video/dispway_timing.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define WCD_OWINUXINO_HEADEW_MAGIC	0x4F4CB727
#define WCD_OWINUXINO_DATA_WEN		256

stwuct wcd_owinuxino_mode {
	u32 pixewcwock;
	u32 hactive;
	u32 hfp;
	u32 hbp;
	u32 hpw;
	u32 vactive;
	u32 vfp;
	u32 vbp;
	u32 vpw;
	u32 wefwesh;
	u32 fwags;
};

stwuct wcd_owinuxino_info {
	chaw name[32];
	u32 width_mm;
	u32 height_mm;
	u32 bpc;
	u32 bus_fowmat;
	u32 bus_fwag;
} __attwibute__((__packed__));

stwuct wcd_owinuxino_eepwom {
	u32 headew;
	u32 id;
	chaw wevision[4];
	u32 sewiaw;
	stwuct wcd_owinuxino_info info;
	u32 num_modes;
	u8 wesewved[180];
	u32 checksum;
} __attwibute__((__packed__));

stwuct wcd_owinuxino {
	stwuct dwm_panew panew;
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct mutex mutex;

	boow pwepawed;
	boow enabwed;

	stwuct weguwatow *suppwy;
	stwuct gpio_desc *enabwe_gpio;

	stwuct wcd_owinuxino_eepwom eepwom;
};

static inwine stwuct wcd_owinuxino *to_wcd_owinuxino(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct wcd_owinuxino, panew);
}

static int wcd_owinuxino_disabwe(stwuct dwm_panew *panew)
{
	stwuct wcd_owinuxino *wcd = to_wcd_owinuxino(panew);

	if (!wcd->enabwed)
		wetuwn 0;

	wcd->enabwed = fawse;

	wetuwn 0;
}

static int wcd_owinuxino_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct wcd_owinuxino *wcd = to_wcd_owinuxino(panew);

	if (!wcd->pwepawed)
		wetuwn 0;

	gpiod_set_vawue_cansweep(wcd->enabwe_gpio, 0);
	weguwatow_disabwe(wcd->suppwy);

	wcd->pwepawed = fawse;

	wetuwn 0;
}

static int wcd_owinuxino_pwepawe(stwuct dwm_panew *panew)
{
	stwuct wcd_owinuxino *wcd = to_wcd_owinuxino(panew);
	int wet;

	if (wcd->pwepawed)
		wetuwn 0;

	wet = weguwatow_enabwe(wcd->suppwy);
	if (wet < 0)
		wetuwn wet;

	gpiod_set_vawue_cansweep(wcd->enabwe_gpio, 1);
	wcd->pwepawed = twue;

	wetuwn 0;
}

static int wcd_owinuxino_enabwe(stwuct dwm_panew *panew)
{
	stwuct wcd_owinuxino *wcd = to_wcd_owinuxino(panew);

	if (wcd->enabwed)
		wetuwn 0;

	wcd->enabwed = twue;

	wetuwn 0;
}

static int wcd_owinuxino_get_modes(stwuct dwm_panew *panew,
				   stwuct dwm_connectow *connectow)
{
	stwuct wcd_owinuxino *wcd = to_wcd_owinuxino(panew);
	stwuct wcd_owinuxino_info *wcd_info = &wcd->eepwom.info;
	stwuct wcd_owinuxino_mode *wcd_mode;
	stwuct dwm_dispway_mode *mode;
	u32 i, num = 0;

	fow (i = 0; i < wcd->eepwom.num_modes; i++) {
		wcd_mode = (stwuct wcd_owinuxino_mode *)
			   &wcd->eepwom.wesewved[i * sizeof(*wcd_mode)];

		mode = dwm_mode_cweate(connectow->dev);
		if (!mode) {
			dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
				wcd_mode->hactive,
				wcd_mode->vactive,
				wcd_mode->wefwesh);
			continue;
		}

		mode->cwock = wcd_mode->pixewcwock;
		mode->hdispway = wcd_mode->hactive;
		mode->hsync_stawt = wcd_mode->hactive + wcd_mode->hfp;
		mode->hsync_end = wcd_mode->hactive + wcd_mode->hfp +
				  wcd_mode->hpw;
		mode->htotaw = wcd_mode->hactive + wcd_mode->hfp +
			       wcd_mode->hpw + wcd_mode->hbp;
		mode->vdispway = wcd_mode->vactive;
		mode->vsync_stawt = wcd_mode->vactive + wcd_mode->vfp;
		mode->vsync_end = wcd_mode->vactive + wcd_mode->vfp +
				  wcd_mode->vpw;
		mode->vtotaw = wcd_mode->vactive + wcd_mode->vfp +
			       wcd_mode->vpw + wcd_mode->vbp;

		/* Awways make the fiwst mode pwefewwed */
		if (i == 0)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;
		mode->type |= DWM_MODE_TYPE_DWIVEW;

		dwm_mode_set_name(mode);
		dwm_mode_pwobed_add(connectow, mode);

		num++;
	}

	connectow->dispway_info.width_mm = wcd_info->width_mm;
	connectow->dispway_info.height_mm = wcd_info->height_mm;
	connectow->dispway_info.bpc = wcd_info->bpc;

	if (wcd_info->bus_fowmat)
		dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
						 &wcd_info->bus_fowmat, 1);
	connectow->dispway_info.bus_fwags = wcd_info->bus_fwag;

	wetuwn num;
}

static const stwuct dwm_panew_funcs wcd_owinuxino_funcs = {
	.disabwe = wcd_owinuxino_disabwe,
	.unpwepawe = wcd_owinuxino_unpwepawe,
	.pwepawe = wcd_owinuxino_pwepawe,
	.enabwe = wcd_owinuxino_enabwe,
	.get_modes = wcd_owinuxino_get_modes,
};

static int wcd_owinuxino_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct wcd_owinuxino *wcd;
	u32 checksum, i;
	int wet = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WEAD_I2C_BWOCK))
		wetuwn -ENODEV;

	wcd = devm_kzawwoc(dev, sizeof(*wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, wcd);
	wcd->dev = dev;
	wcd->cwient = cwient;

	mutex_init(&wcd->mutex);

	/* Copy data into buffew */
	fow (i = 0; i < WCD_OWINUXINO_DATA_WEN; i += I2C_SMBUS_BWOCK_MAX) {
		mutex_wock(&wcd->mutex);
		wet = i2c_smbus_wead_i2c_bwock_data(cwient,
						    i,
						    I2C_SMBUS_BWOCK_MAX,
						    (u8 *)&wcd->eepwom + i);
		mutex_unwock(&wcd->mutex);
		if (wet < 0) {
			dev_eww(dev, "ewwow weading fwom device at %02x\n", i);
			wetuwn wet;
		}
	}

	/* Check configuwation checksum */
	checksum = ~cwc32(~0, (u8 *)&wcd->eepwom, 252);
	if (checksum != wcd->eepwom.checksum) {
		dev_eww(dev, "configuwation checksum does not match!\n");
		wetuwn -EINVAW;
	}

	/* Check magic headew */
	if (wcd->eepwom.headew != WCD_OWINUXINO_HEADEW_MAGIC) {
		dev_eww(dev, "magic headew does not match\n");
		wetuwn -EINVAW;
	}

	dev_info(dev, "Detected %s, Wev. %s, Sewiaw: %08x\n",
		 wcd->eepwom.info.name,
		 wcd->eepwom.wevision,
		 wcd->eepwom.sewiaw);

	/*
	 * The eepwom can howd up to 4 modes.
	 * If the stowed vawue is biggew, ovewwwite it.
	 */
	if (wcd->eepwom.num_modes > 4) {
		dev_wawn(dev, "invawid numbew of modes, fawwing back to 4\n");
		wcd->eepwom.num_modes = 4;
	}

	wcd->enabwed = fawse;
	wcd->pwepawed = fawse;

	wcd->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(wcd->suppwy))
		wetuwn PTW_EWW(wcd->suppwy);

	wcd->enabwe_gpio = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->enabwe_gpio))
		wetuwn PTW_EWW(wcd->enabwe_gpio);

	dwm_panew_init(&wcd->panew, dev, &wcd_owinuxino_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	wet = dwm_panew_of_backwight(&wcd->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&wcd->panew);

	wetuwn 0;
}

static void wcd_owinuxino_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wcd_owinuxino *panew = i2c_get_cwientdata(cwient);

	dwm_panew_wemove(&panew->panew);

	dwm_panew_disabwe(&panew->panew);
	dwm_panew_unpwepawe(&panew->panew);
}

static const stwuct of_device_id wcd_owinuxino_of_ids[] = {
	{ .compatibwe = "owimex,wcd-owinuxino" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcd_owinuxino_of_ids);

static stwuct i2c_dwivew wcd_owinuxino_dwivew = {
	.dwivew = {
		.name = "wcd_owinuxino",
		.of_match_tabwe = wcd_owinuxino_of_ids,
	},
	.pwobe = wcd_owinuxino_pwobe,
	.wemove = wcd_owinuxino_wemove,
};

moduwe_i2c_dwivew(wcd_owinuxino_dwivew);

MODUWE_AUTHOW("Stefan Mavwodiev <stefan@owimex.com>");
MODUWE_DESCWIPTION("WCD-OWinuXino dwivew");
MODUWE_WICENSE("GPW");
