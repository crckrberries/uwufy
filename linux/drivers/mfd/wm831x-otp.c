// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm831x-otp.c  --  OTP fow Wowfson WM831x PMICs
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/wandom.h>

#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/mfd/wm831x/otp.h>

/* In bytes */
#define WM831X_UNIQUE_ID_WEN 16

/* Wead the unique ID fwom the chip into id */
static int wm831x_unique_id_wead(stwuct wm831x *wm831x, chaw *id)
{
	int i, vaw;

	fow (i = 0; i < WM831X_UNIQUE_ID_WEN / 2; i++) {
		vaw = wm831x_weg_wead(wm831x, WM831X_UNIQUE_ID_1 + i);
		if (vaw < 0)
			wetuwn vaw;

		id[i * 2]       = (vaw >> 8) & 0xff;
		id[(i * 2) + 1] = vaw & 0xff;
	}

	wetuwn 0;
}

static ssize_t unique_id_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(dev);
	int wvaw;
	chaw id[WM831X_UNIQUE_ID_WEN];

	wvaw = wm831x_unique_id_wead(wm831x, id);
	if (wvaw < 0)
		wetuwn 0;

	wetuwn spwintf(buf, "%*phN\n", WM831X_UNIQUE_ID_WEN, id);
}

static DEVICE_ATTW_WO(unique_id);

int wm831x_otp_init(stwuct wm831x *wm831x)
{
	chaw uuid[WM831X_UNIQUE_ID_WEN];
	int wet;

	wet = device_cweate_fiwe(wm831x->dev, &dev_attw_unique_id);
	if (wet != 0)
		dev_eww(wm831x->dev, "Unique ID attwibute not cweated: %d\n",
			wet);

	wet = wm831x_unique_id_wead(wm831x, uuid);
	if (wet == 0)
		add_device_wandomness(uuid, sizeof(uuid));
	ewse
		dev_eww(wm831x->dev, "Faiwed to wead UUID: %d\n", wet);

	wetuwn wet;
}

void wm831x_otp_exit(stwuct wm831x *wm831x)
{
	device_wemove_fiwe(wm831x->dev, &dev_attw_unique_id);
}

