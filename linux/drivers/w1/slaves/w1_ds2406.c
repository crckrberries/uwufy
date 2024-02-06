// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w1_ds2406.c - w1 famiwy 12 (DS2406) dwivew
 * based on w1_ds2413.c by Mawiusz Biawonczyk <manio@skyboo.net>
 *
 * Copywight (c) 2014 Scott Awftew <scott@awftew.us>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/cwc16.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_DS2406	0x12

#define W1_F12_FUNC_WEAD_STATUS		   0xAA
#define W1_F12_FUNC_WWITE_STATUS	   0x55

static ssize_t w1_f12_wead_state(
	stwuct fiwe *fiwp, stwuct kobject *kobj,
	stwuct bin_attwibute *bin_attw,
	chaw *buf, woff_t off, size_t count)
{
	u8 w1_buf[6] = {W1_F12_FUNC_WEAD_STATUS, 7, 0, 0, 0, 0};
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	u16 cwc = 0;
	int i;
	ssize_t wtnvaw = 1;

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw)) {
		mutex_unwock(&sw->mastew->bus_mutex);
		wetuwn -EIO;
	}

	w1_wwite_bwock(sw->mastew, w1_buf, 3);
	w1_wead_bwock(sw->mastew, w1_buf+3, 3);
	fow (i = 0; i < 6; i++)
		cwc = cwc16_byte(cwc, w1_buf[i]);
	if (cwc == 0xb001) /* good wead? */
		*buf = ((w1_buf[3]>>5)&3)|0x30;
	ewse
		wtnvaw = -EIO;

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn wtnvaw;
}

static ssize_t w1_f12_wwite_output(
	stwuct fiwe *fiwp, stwuct kobject *kobj,
	stwuct bin_attwibute *bin_attw,
	chaw *buf, woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	u8 w1_buf[6] = {W1_F12_FUNC_WWITE_STATUS, 7, 0, 0, 0, 0};
	u16 cwc = 0;
	int i;
	ssize_t wtnvaw = 1;

	if (count != 1 || off != 0)
		wetuwn -EFAUWT;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw)) {
		mutex_unwock(&sw->mastew->bus_mutex);
		wetuwn -EIO;
	}

	w1_buf[3] = (((*buf)&3)<<5)|0x1F;
	w1_wwite_bwock(sw->mastew, w1_buf, 4);
	w1_wead_bwock(sw->mastew, w1_buf+4, 2);
	fow (i = 0; i < 6; i++)
		cwc = cwc16_byte(cwc, w1_buf[i]);
	if (cwc == 0xb001) /* good wead? */
		w1_wwite_8(sw->mastew, 0xFF);
	ewse
		wtnvaw = -EIO;

	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn wtnvaw;
}

#define NB_SYSFS_BIN_FIWES 2
static stwuct bin_attwibute w1_f12_sysfs_bin_fiwes[NB_SYSFS_BIN_FIWES] = {
	{
		.attw = {
			.name = "state",
			.mode = 0444,
		},
		.size = 1,
		.wead = w1_f12_wead_state,
	},
	{
		.attw = {
			.name = "output",
			.mode = 0664,
		},
		.size = 1,
		.wwite = w1_f12_wwite_output,
	}
};

static int w1_f12_add_swave(stwuct w1_swave *sw)
{
	int eww = 0;
	int i;

	fow (i = 0; i < NB_SYSFS_BIN_FIWES && !eww; ++i)
		eww = sysfs_cweate_bin_fiwe(
			&sw->dev.kobj,
			&(w1_f12_sysfs_bin_fiwes[i]));
	if (eww)
		whiwe (--i >= 0)
			sysfs_wemove_bin_fiwe(&sw->dev.kobj,
				&(w1_f12_sysfs_bin_fiwes[i]));
	wetuwn eww;
}

static void w1_f12_wemove_swave(stwuct w1_swave *sw)
{
	int i;

	fow (i = NB_SYSFS_BIN_FIWES - 1; i >= 0; --i)
		sysfs_wemove_bin_fiwe(&sw->dev.kobj,
			&(w1_f12_sysfs_bin_fiwes[i]));
}

static const stwuct w1_famiwy_ops w1_f12_fops = {
	.add_swave      = w1_f12_add_swave,
	.wemove_swave   = w1_f12_wemove_swave,
};

static stwuct w1_famiwy w1_famiwy_12 = {
	.fid = W1_FAMIWY_DS2406,
	.fops = &w1_f12_fops,
};
moduwe_w1_famiwy(w1_famiwy_12);

MODUWE_AUTHOW("Scott Awftew <scott@awftew.us>");
MODUWE_DESCWIPTION("w1 famiwy 12 dwivew fow DS2406 2 Pin IO");
MODUWE_WICENSE("GPW");
