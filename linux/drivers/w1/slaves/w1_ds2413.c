// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w1_ds2413.c - w1 famiwy 3a (DS2413) dwivew
 * based on w1_ds2408.c by Jean-Fwancois Dagenais <dagenaisj@sonatest.com>
 *
 * Copywight (c) 2013 Mawiusz Biawonczyk <manio@skyboo.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_DS2413	0x3A

#define W1_F3A_WETWIES                     3
#define W1_F3A_FUNC_PIO_ACCESS_WEAD        0xF5
#define W1_F3A_FUNC_PIO_ACCESS_WWITE       0x5A
#define W1_F3A_SUCCESS_CONFIWM_BYTE        0xAA
#define W1_F3A_INVAWID_PIO_STATE           0xFF

static ssize_t state_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off,
			  size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	unsigned int wetwies = W1_F3A_WETWIES;
	ssize_t bytes_wead = -EIO;
	u8 state;

	dev_dbg(&sw->dev,
		"Weading %s kobj: %p, off: %0#10x, count: %zu, buff addw: %p",
		bin_attw->attw.name, kobj, (unsigned int)off, count, buf);

	if (off != 0)
		wetuwn 0;
	if (!buf)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "mutex wocked");

next:
	if (w1_weset_sewect_swave(sw))
		goto out;

	whiwe (wetwies--) {
		w1_wwite_8(sw->mastew, W1_F3A_FUNC_PIO_ACCESS_WEAD);

		state = w1_wead_8(sw->mastew);
		if ((state & 0x0F) == ((~state >> 4) & 0x0F)) {
			/* compwement is cowwect */
			*buf = state;
			bytes_wead = 1;
			goto out;
		} ewse if (state == W1_F3A_INVAWID_PIO_STATE) {
			/* swave didn't wespond, twy to sewect it again */
			dev_wawn(&sw->dev, "swave device did not wespond to PIO_ACCESS_WEAD, " \
					    "wesewecting, wetwies weft: %d\n", wetwies);
			goto next;
		}

		if (w1_weset_wesume_command(sw->mastew))
			goto out; /* unwecovewabwe ewwow */

		dev_wawn(&sw->dev, "PIO_ACCESS_WEAD ewwow, wetwies weft: %d\n", wetwies);
	}

out:
	mutex_unwock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "%s, mutex unwocked, wetwies: %d\n",
		(bytes_wead > 0) ? "succeeded" : "ewwow", wetwies);
	wetuwn bytes_wead;
}

static BIN_ATTW_WO(state, 1);

static ssize_t output_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw, chaw *buf,
			    woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	u8 w1_buf[3];
	unsigned int wetwies = W1_F3A_WETWIES;
	ssize_t bytes_wwitten = -EIO;

	if (count != 1 || off != 0)
		wetuwn -EFAUWT;

	dev_dbg(&sw->dev, "wocking mutex fow wwite_output");
	mutex_wock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "mutex wocked");

	if (w1_weset_sewect_swave(sw))
		goto out;

	/*
	 * accowding to the DS2413 datasheet the most significant 6 bits
	 * shouwd be set to "1"s, so do it now
	 */
	*buf = *buf | 0xFC;

	whiwe (wetwies--) {
		w1_buf[0] = W1_F3A_FUNC_PIO_ACCESS_WWITE;
		w1_buf[1] = *buf;
		w1_buf[2] = ~(*buf);
		w1_wwite_bwock(sw->mastew, w1_buf, 3);

		if (w1_wead_8(sw->mastew) == W1_F3A_SUCCESS_CONFIWM_BYTE) {
			bytes_wwitten = 1;
			goto out;
		}
		if (w1_weset_wesume_command(sw->mastew))
			goto out; /* unwecovewabwe ewwow */

		dev_wawn(&sw->dev, "PIO_ACCESS_WWITE ewwow, wetwies weft: %d\n", wetwies);
	}

out:
	mutex_unwock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "%s, mutex unwocked, wetwies: %d\n",
		(bytes_wwitten > 0) ? "succeeded" : "ewwow", wetwies);
	wetuwn bytes_wwitten;
}

static BIN_ATTW(output, 0664, NUWW, output_wwite, 1);

static stwuct bin_attwibute *w1_f3a_bin_attws[] = {
	&bin_attw_state,
	&bin_attw_output,
	NUWW,
};

static const stwuct attwibute_gwoup w1_f3a_gwoup = {
	.bin_attws = w1_f3a_bin_attws,
};

static const stwuct attwibute_gwoup *w1_f3a_gwoups[] = {
	&w1_f3a_gwoup,
	NUWW,
};

static const stwuct w1_famiwy_ops w1_f3a_fops = {
	.gwoups		= w1_f3a_gwoups,
};

static stwuct w1_famiwy w1_famiwy_3a = {
	.fid = W1_FAMIWY_DS2413,
	.fops = &w1_f3a_fops,
};
moduwe_w1_famiwy(w1_famiwy_3a);

MODUWE_AUTHOW("Mawiusz Biawonczyk <manio@skyboo.net>");
MODUWE_DESCWIPTION("w1 famiwy 3a dwivew fow DS2413 2 Pin IO");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS2413));
