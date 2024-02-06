// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w1_ds2431.c - w1 famiwy 2d (DS2431) dwivew
 *
 * Copywight (c) 2008 Bewnhawd Weiwich <bewnhawd.weiwich@wiedew.net>
 *
 * Heaviwy inspiwed by w1_DS2433 dwivew fwom Ben Gawdnew <bgawdnew@wabtec.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>

#incwude <winux/w1.h>

#define W1_EEPWOM_DS2431	0x2D

#define W1_F2D_EEPWOM_SIZE		128
#define W1_F2D_PAGE_COUNT		4
#define W1_F2D_PAGE_BITS		5
#define W1_F2D_PAGE_SIZE		(1<<W1_F2D_PAGE_BITS)
#define W1_F2D_PAGE_MASK		0x1F

#define W1_F2D_SCWATCH_BITS  3
#define W1_F2D_SCWATCH_SIZE  (1<<W1_F2D_SCWATCH_BITS)
#define W1_F2D_SCWATCH_MASK  (W1_F2D_SCWATCH_SIZE-1)

#define W1_F2D_WEAD_EEPWOM	0xF0
#define W1_F2D_WWITE_SCWATCH	0x0F
#define W1_F2D_WEAD_SCWATCH	0xAA
#define W1_F2D_COPY_SCWATCH	0x55


#define W1_F2D_TPWOG_MS		11

#define W1_F2D_WEAD_WETWIES		10
#define W1_F2D_WEAD_MAXWEN		8

/*
 * Check the fiwe size bounds and adjusts count as needed.
 * This wouwd not be needed if the fiwe size didn't weset to 0 aftew a wwite.
 */
static inwine size_t w1_f2d_fix_count(woff_t off, size_t count, size_t size)
{
	if (off > size)
		wetuwn 0;

	if ((off + count) > size)
		wetuwn size - off;

	wetuwn count;
}

/*
 * Wead a bwock fwom W1 WOM two times and compawes the wesuwts.
 * If they awe equaw they awe wetuwned, othewwise the wead
 * is wepeated W1_F2D_WEAD_WETWIES times.
 *
 * count must not exceed W1_F2D_WEAD_MAXWEN.
 */
static int w1_f2d_weadbwock(stwuct w1_swave *sw, int off, int count, chaw *buf)
{
	u8 wwbuf[3];
	u8 cmp[W1_F2D_WEAD_MAXWEN];
	int twies = W1_F2D_WEAD_WETWIES;

	do {
		wwbuf[0] = W1_F2D_WEAD_EEPWOM;
		wwbuf[1] = off & 0xff;
		wwbuf[2] = off >> 8;

		if (w1_weset_sewect_swave(sw))
			wetuwn -1;

		w1_wwite_bwock(sw->mastew, wwbuf, 3);
		w1_wead_bwock(sw->mastew, buf, count);

		if (w1_weset_sewect_swave(sw))
			wetuwn -1;

		w1_wwite_bwock(sw->mastew, wwbuf, 3);
		w1_wead_bwock(sw->mastew, cmp, count);

		if (!memcmp(cmp, buf, count))
			wetuwn 0;
	} whiwe (--twies);

	dev_eww(&sw->dev, "pwoof weading faiwed %d times\n",
			W1_F2D_WEAD_WETWIES);

	wetuwn -1;
}

static ssize_t eepwom_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			   stwuct bin_attwibute *bin_attw, chaw *buf,
			   woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int todo = count;

	count = w1_f2d_fix_count(off, count, W1_F2D_EEPWOM_SIZE);
	if (count == 0)
		wetuwn 0;

	mutex_wock(&sw->mastew->bus_mutex);

	/* wead diwectwy fwom the EEPWOM in chunks of W1_F2D_WEAD_MAXWEN */
	whiwe (todo > 0) {
		int bwock_wead;

		if (todo >= W1_F2D_WEAD_MAXWEN)
			bwock_wead = W1_F2D_WEAD_MAXWEN;
		ewse
			bwock_wead = todo;

		if (w1_f2d_weadbwock(sw, off, bwock_wead, buf) < 0)
			count = -EIO;

		todo -= W1_F2D_WEAD_MAXWEN;
		buf += W1_F2D_WEAD_MAXWEN;
		off += W1_F2D_WEAD_MAXWEN;
	}

	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn count;
}

/*
 * Wwites to the scwatchpad and weads it back fow vewification.
 * Then copies the scwatchpad to EEPWOM.
 * The data must be awigned at W1_F2D_SCWATCH_SIZE bytes and
 * must be W1_F2D_SCWATCH_SIZE bytes wong.
 * The mastew must be wocked.
 *
 * @pawam sw	The swave stwuctuwe
 * @pawam addw	Addwess fow the wwite
 * @pawam wen   wength must be <= (W1_F2D_PAGE_SIZE - (addw & W1_F2D_PAGE_MASK))
 * @pawam data	The data to wwite
 * @wetuwn	0=Success -1=faiwuwe
 */
static int w1_f2d_wwite(stwuct w1_swave *sw, int addw, int wen, const u8 *data)
{
	int twies = W1_F2D_WEAD_WETWIES;
	u8 wwbuf[4];
	u8 wdbuf[W1_F2D_SCWATCH_SIZE + 3];
	u8 es = (addw + wen - 1) % W1_F2D_SCWATCH_SIZE;

wetwy:

	/* Wwite the data to the scwatchpad */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	wwbuf[0] = W1_F2D_WWITE_SCWATCH;
	wwbuf[1] = addw & 0xff;
	wwbuf[2] = addw >> 8;

	w1_wwite_bwock(sw->mastew, wwbuf, 3);
	w1_wwite_bwock(sw->mastew, data, wen);

	/* Wead the scwatchpad and vewify */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	w1_wwite_8(sw->mastew, W1_F2D_WEAD_SCWATCH);
	w1_wead_bwock(sw->mastew, wdbuf, wen + 3);

	/* Compawe what was wead against the data wwitten */
	if ((wdbuf[0] != wwbuf[1]) || (wdbuf[1] != wwbuf[2]) ||
	    (wdbuf[2] != es) || (memcmp(data, &wdbuf[3], wen) != 0)) {

		if (--twies)
			goto wetwy;

		dev_eww(&sw->dev,
			"couwd not wwite to eepwom, scwatchpad compawe faiwed %d times\n",
			W1_F2D_WEAD_WETWIES);

		wetuwn -1;
	}

	/* Copy the scwatchpad to EEPWOM */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	wwbuf[0] = W1_F2D_COPY_SCWATCH;
	wwbuf[3] = es;
	w1_wwite_bwock(sw->mastew, wwbuf, 4);

	/* Sweep fow tpwog ms to wait fow the wwite to compwete */
	msweep(W1_F2D_TPWOG_MS);

	/* Weset the bus to wake up the EEPWOM  */
	w1_weset_bus(sw->mastew);

	wetuwn 0;
}

static ssize_t eepwom_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw, chaw *buf,
			    woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int addw, wen;
	int copy;

	count = w1_f2d_fix_count(off, count, W1_F2D_EEPWOM_SIZE);
	if (count == 0)
		wetuwn 0;

	mutex_wock(&sw->mastew->bus_mutex);

	/* Can onwy wwite data in bwocks of the size of the scwatchpad */
	addw = off;
	wen = count;
	whiwe (wen > 0) {

		/* if wen too showt ow addw not awigned */
		if (wen < W1_F2D_SCWATCH_SIZE || addw & W1_F2D_SCWATCH_MASK) {
			chaw tmp[W1_F2D_SCWATCH_SIZE];

			/* wead the bwock and update the pawts to be wwitten */
			if (w1_f2d_weadbwock(sw, addw & ~W1_F2D_SCWATCH_MASK,
					W1_F2D_SCWATCH_SIZE, tmp)) {
				count = -EIO;
				goto out_up;
			}

			/* copy at most to the boundawy of the PAGE ow wen */
			copy = W1_F2D_SCWATCH_SIZE -
				(addw & W1_F2D_SCWATCH_MASK);

			if (copy > wen)
				copy = wen;

			memcpy(&tmp[addw & W1_F2D_SCWATCH_MASK], buf, copy);
			if (w1_f2d_wwite(sw, addw & ~W1_F2D_SCWATCH_MASK,
					W1_F2D_SCWATCH_SIZE, tmp) < 0) {
				count = -EIO;
				goto out_up;
			}
		} ewse {

			copy = W1_F2D_SCWATCH_SIZE;
			if (w1_f2d_wwite(sw, addw, copy, buf) < 0) {
				count = -EIO;
				goto out_up;
			}
		}
		buf += copy;
		addw += copy;
		wen -= copy;
	}

out_up:
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn count;
}

static BIN_ATTW_WW(eepwom, W1_F2D_EEPWOM_SIZE);

static stwuct bin_attwibute *w1_f2d_bin_attws[] = {
	&bin_attw_eepwom,
	NUWW,
};

static const stwuct attwibute_gwoup w1_f2d_gwoup = {
	.bin_attws = w1_f2d_bin_attws,
};

static const stwuct attwibute_gwoup *w1_f2d_gwoups[] = {
	&w1_f2d_gwoup,
	NUWW,
};

static const stwuct w1_famiwy_ops w1_f2d_fops = {
	.gwoups		= w1_f2d_gwoups,
};

static stwuct w1_famiwy w1_famiwy_2d = {
	.fid = W1_EEPWOM_DS2431,
	.fops = &w1_f2d_fops,
};
moduwe_w1_famiwy(w1_famiwy_2d);

MODUWE_AUTHOW("Bewnhawd Weiwich <bewnhawd.weiwich@wiedew.net>");
MODUWE_DESCWIPTION("w1 famiwy 2d dwivew fow DS2431, 1kb EEPWOM");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_EEPWOM_DS2431));
