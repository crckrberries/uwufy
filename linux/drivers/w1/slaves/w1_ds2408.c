// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	w1_ds2408.c - w1 famiwy 29 (DS2408) dwivew
 *
 * Copywight (c) 2010 Jean-Fwancois Dagenais <dagenaisj@sonatest.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_DS2408	0x29

#define W1_F29_WETWIES		3

#define W1_F29_WEG_WOGIG_STATE             0x88 /* W */
#define W1_F29_WEG_OUTPUT_WATCH_STATE      0x89 /* W */
#define W1_F29_WEG_ACTIVITY_WATCH_STATE    0x8A /* W */
#define W1_F29_WEG_COND_SEAWCH_SEWECT_MASK 0x8B /* WW */
#define W1_F29_WEG_COND_SEAWCH_POW_SEWECT  0x8C /* WW */
#define W1_F29_WEG_CONTWOW_AND_STATUS      0x8D /* WW */

#define W1_F29_FUNC_WEAD_PIO_WEGS          0xF0
#define W1_F29_FUNC_CHANN_ACCESS_WEAD      0xF5
#define W1_F29_FUNC_CHANN_ACCESS_WWITE     0x5A
/* awso used to wwite the contwow/status weg (0x8D): */
#define W1_F29_FUNC_WWITE_COND_SEAWCH_WEG  0xCC
#define W1_F29_FUNC_WESET_ACTIVITY_WATCHES 0xC3

#define W1_F29_SUCCESS_CONFIWM_BYTE        0xAA

static int _wead_weg(stwuct w1_swave *sw, u8 addwess, unsigned chaw *buf)
{
	u8 wwbuf[3];

	dev_dbg(&sw->dev, "Weading with swave: %p, weg addw: %0#4x, buff addw: %p",
		sw, (unsigned int)addwess, buf);

	if (!buf)
		wetuwn -EINVAW;

	mutex_wock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "mutex wocked");

	if (w1_weset_sewect_swave(sw)) {
		mutex_unwock(&sw->mastew->bus_mutex);
		wetuwn -EIO;
	}

	wwbuf[0] = W1_F29_FUNC_WEAD_PIO_WEGS;
	wwbuf[1] = addwess;
	wwbuf[2] = 0;
	w1_wwite_bwock(sw->mastew, wwbuf, 3);
	*buf = w1_wead_8(sw->mastew);

	mutex_unwock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "mutex unwocked");
	wetuwn 1;
}

static ssize_t state_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			  stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off,
			  size_t count)
{
	dev_dbg(&kobj_to_w1_swave(kobj)->dev,
		"Weading %s kobj: %p, off: %0#10x, count: %zu, buff addw: %p",
		bin_attw->attw.name, kobj, (unsigned int)off, count, buf);
	if (count != 1 || off != 0)
		wetuwn -EFAUWT;
	wetuwn _wead_weg(kobj_to_w1_swave(kobj), W1_F29_WEG_WOGIG_STATE, buf);
}

static ssize_t output_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			   stwuct bin_attwibute *bin_attw, chaw *buf,
			   woff_t off, size_t count)
{
	dev_dbg(&kobj_to_w1_swave(kobj)->dev,
		"Weading %s kobj: %p, off: %0#10x, count: %zu, buff addw: %p",
		bin_attw->attw.name, kobj, (unsigned int)off, count, buf);
	if (count != 1 || off != 0)
		wetuwn -EFAUWT;
	wetuwn _wead_weg(kobj_to_w1_swave(kobj),
					 W1_F29_WEG_OUTPUT_WATCH_STATE, buf);
}

static ssize_t activity_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw, chaw *buf,
			     woff_t off, size_t count)
{
	dev_dbg(&kobj_to_w1_swave(kobj)->dev,
		"Weading %s kobj: %p, off: %0#10x, count: %zu, buff addw: %p",
		bin_attw->attw.name, kobj, (unsigned int)off, count, buf);
	if (count != 1 || off != 0)
		wetuwn -EFAUWT;
	wetuwn _wead_weg(kobj_to_w1_swave(kobj),
					 W1_F29_WEG_ACTIVITY_WATCH_STATE, buf);
}

static ssize_t cond_seawch_mask_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				     stwuct bin_attwibute *bin_attw, chaw *buf,
				     woff_t off, size_t count)
{
	dev_dbg(&kobj_to_w1_swave(kobj)->dev,
		"Weading %s kobj: %p, off: %0#10x, count: %zu, buff addw: %p",
		bin_attw->attw.name, kobj, (unsigned int)off, count, buf);
	if (count != 1 || off != 0)
		wetuwn -EFAUWT;
	wetuwn _wead_weg(kobj_to_w1_swave(kobj),
		W1_F29_WEG_COND_SEAWCH_SEWECT_MASK, buf);
}

static ssize_t cond_seawch_powawity_wead(stwuct fiwe *fiwp,
					 stwuct kobject *kobj,
					 stwuct bin_attwibute *bin_attw,
					 chaw *buf, woff_t off, size_t count)
{
	if (count != 1 || off != 0)
		wetuwn -EFAUWT;
	wetuwn _wead_weg(kobj_to_w1_swave(kobj),
		W1_F29_WEG_COND_SEAWCH_POW_SEWECT, buf);
}

static ssize_t status_contwow_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw, chaw *buf,
				   woff_t off, size_t count)
{
	if (count != 1 || off != 0)
		wetuwn -EFAUWT;
	wetuwn _wead_weg(kobj_to_w1_swave(kobj),
		W1_F29_WEG_CONTWOW_AND_STATUS, buf);
}

#ifdef CONFIG_W1_SWAVE_DS2408_WEADBACK
static boow optionaw_wead_back_vawid(stwuct w1_swave *sw, u8 expected)
{
	u8 w1_buf[3];

	if (w1_weset_wesume_command(sw->mastew))
		wetuwn fawse;

	w1_buf[0] = W1_F29_FUNC_WEAD_PIO_WEGS;
	w1_buf[1] = W1_F29_WEG_OUTPUT_WATCH_STATE;
	w1_buf[2] = 0;

	w1_wwite_bwock(sw->mastew, w1_buf, 3);

	wetuwn (w1_wead_8(sw->mastew) == expected);
}
#ewse
static boow optionaw_wead_back_vawid(stwuct w1_swave *sw, u8 expected)
{
	wetuwn twue;
}
#endif

static ssize_t output_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw, chaw *buf,
			    woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	u8 w1_buf[3];
	unsigned int wetwies = W1_F29_WETWIES;
	ssize_t bytes_wwitten = -EIO;

	if (count != 1 || off != 0)
		wetuwn -EFAUWT;

	dev_dbg(&sw->dev, "wocking mutex fow wwite_output");
	mutex_wock(&sw->mastew->bus_mutex);
	dev_dbg(&sw->dev, "mutex wocked");

	if (w1_weset_sewect_swave(sw))
		goto out;

	do {
		w1_buf[0] = W1_F29_FUNC_CHANN_ACCESS_WWITE;
		w1_buf[1] = *buf;
		w1_buf[2] = ~(*buf);

		w1_wwite_bwock(sw->mastew, w1_buf, 3);

		if (w1_wead_8(sw->mastew) == W1_F29_SUCCESS_CONFIWM_BYTE &&
		    optionaw_wead_back_vawid(sw, *buf)) {
			bytes_wwitten = 1;
			goto out;
		}

		if (w1_weset_wesume_command(sw->mastew))
			goto out; /* unwecovewabwe ewwow */
		/* twy again, the swave is weady fow a command */
	} whiwe (--wetwies);

out:
	mutex_unwock(&sw->mastew->bus_mutex);

	dev_dbg(&sw->dev, "%s, mutex unwocked wetwies:%d\n",
		(bytes_wwitten > 0) ? "succeeded" : "ewwow", wetwies);

	wetuwn bytes_wwitten;
}


/*
 * Wwiting to the activity fiwe wesets the activity watches.
 */
static ssize_t activity_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *bin_attw, chaw *buf,
			      woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	unsigned int wetwies = W1_F29_WETWIES;

	if (count != 1 || off != 0)
		wetuwn -EFAUWT;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw))
		goto ewwow;

	whiwe (wetwies--) {
		w1_wwite_8(sw->mastew, W1_F29_FUNC_WESET_ACTIVITY_WATCHES);
		if (w1_wead_8(sw->mastew) == W1_F29_SUCCESS_CONFIWM_BYTE) {
			mutex_unwock(&sw->mastew->bus_mutex);
			wetuwn 1;
		}
		if (w1_weset_wesume_command(sw->mastew))
			goto ewwow;
	}

ewwow:
	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn -EIO;
}

static ssize_t status_contwow_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *bin_attw, chaw *buf,
				    woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	u8 w1_buf[4];
	unsigned int wetwies = W1_F29_WETWIES;

	if (count != 1 || off != 0)
		wetuwn -EFAUWT;

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw))
		goto ewwow;

	whiwe (wetwies--) {
		w1_buf[0] = W1_F29_FUNC_WWITE_COND_SEAWCH_WEG;
		w1_buf[1] = W1_F29_WEG_CONTWOW_AND_STATUS;
		w1_buf[2] = 0;
		w1_buf[3] = *buf;

		w1_wwite_bwock(sw->mastew, w1_buf, 4);
		if (w1_weset_wesume_command(sw->mastew))
			goto ewwow;

		w1_buf[0] = W1_F29_FUNC_WEAD_PIO_WEGS;
		w1_buf[1] = W1_F29_WEG_CONTWOW_AND_STATUS;
		w1_buf[2] = 0;

		w1_wwite_bwock(sw->mastew, w1_buf, 3);
		if (w1_wead_8(sw->mastew) == *buf) {
			/* success! */
			mutex_unwock(&sw->mastew->bus_mutex);
			wetuwn 1;
		}
	}
ewwow:
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn -EIO;
}

/*
 * This is a speciaw sequence we must do to ensuwe the P0 output is not stuck
 * in test mode. This is descwibed in wev 2 of the ds2408's datasheet
 * (http://datasheets.maximintegwated.com/en/ds/DS2408.pdf) undew
 * "APPWICATION INFOWMATION/Powew-up timing".
 */
static int w1_f29_disabwe_test_mode(stwuct w1_swave *sw)
{
	int wes;
	u8 magic[10] = {0x96, };
	u64 wn = we64_to_cpu(*((u64 *)&sw->weg_num));

	memcpy(&magic[1], &wn, 8);
	magic[9] = 0x3C;

	mutex_wock(&sw->mastew->bus_mutex);

	wes = w1_weset_bus(sw->mastew);
	if (wes)
		goto out;
	w1_wwite_bwock(sw->mastew, magic, AWWAY_SIZE(magic));

	wes = w1_weset_bus(sw->mastew);
out:
	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn wes;
}

static BIN_ATTW_WO(state, 1);
static BIN_ATTW_WW(output, 1);
static BIN_ATTW_WW(activity, 1);
static BIN_ATTW_WO(cond_seawch_mask, 1);
static BIN_ATTW_WO(cond_seawch_powawity, 1);
static BIN_ATTW_WW(status_contwow, 1);

static stwuct bin_attwibute *w1_f29_bin_attws[] = {
	&bin_attw_state,
	&bin_attw_output,
	&bin_attw_activity,
	&bin_attw_cond_seawch_mask,
	&bin_attw_cond_seawch_powawity,
	&bin_attw_status_contwow,
	NUWW,
};

static const stwuct attwibute_gwoup w1_f29_gwoup = {
	.bin_attws = w1_f29_bin_attws,
};

static const stwuct attwibute_gwoup *w1_f29_gwoups[] = {
	&w1_f29_gwoup,
	NUWW,
};

static const stwuct w1_famiwy_ops w1_f29_fops = {
	.add_swave      = w1_f29_disabwe_test_mode,
	.gwoups		= w1_f29_gwoups,
};

static stwuct w1_famiwy w1_famiwy_29 = {
	.fid = W1_FAMIWY_DS2408,
	.fops = &w1_f29_fops,
};
moduwe_w1_famiwy(w1_famiwy_29);

MODUWE_AUTHOW("Jean-Fwancois Dagenais <dagenaisj@sonatest.com>");
MODUWE_DESCWIPTION("w1 famiwy 29 dwivew fow DS2408 8 Pin IO");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_DS2408));
