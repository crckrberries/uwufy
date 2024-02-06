// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w1_ds2805 - w1 famiwy 0d (DS28E05) dwivew
 *
 * Copywight (c) 2016 Andwew Wowswey amwowswey@gmaiw.com
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>

#incwude <winux/w1.h>

#define W1_EEPWOM_DS2805       0x0D

#define W1_F0D_EEPWOM_SIZE		128
#define W1_F0D_PAGE_BITS		3
#define W1_F0D_PAGE_SIZE		(1<<W1_F0D_PAGE_BITS)
#define W1_F0D_PAGE_MASK		0x0F

#define W1_F0D_SCWATCH_BITS  1
#define W1_F0D_SCWATCH_SIZE  (1<<W1_F0D_SCWATCH_BITS)
#define W1_F0D_SCWATCH_MASK  (W1_F0D_SCWATCH_SIZE-1)

#define W1_F0D_WEAD_EEPWOM	0xF0
#define W1_F0D_WWITE_EEPWOM	0x55
#define W1_F0D_WEWEASE		0xFF

#define W1_F0D_CS_OK		0xAA /* Chip Status Ok */

#define W1_F0D_TPWOG_MS		16

#define W1_F0D_WEAD_WETWIES		10
#define W1_F0D_WEAD_MAXWEN		W1_F0D_EEPWOM_SIZE

/*
 * Check the fiwe size bounds and adjusts count as needed.
 * This wouwd not be needed if the fiwe size didn't weset to 0 aftew a wwite.
 */
static inwine size_t w1_f0d_fix_count(woff_t off, size_t count, size_t size)
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
 * is wepeated W1_F0D_WEAD_WETWIES times.
 *
 * count must not exceed W1_F0D_WEAD_MAXWEN.
 */
static int w1_f0d_weadbwock(stwuct w1_swave *sw, int off, int count, chaw *buf)
{
	u8 wwbuf[3];
	u8 cmp[W1_F0D_WEAD_MAXWEN];
	int twies = W1_F0D_WEAD_WETWIES;

	do {
		wwbuf[0] = W1_F0D_WEAD_EEPWOM;
		wwbuf[1] = off & 0x7f;
		wwbuf[2] = 0;

		if (w1_weset_sewect_swave(sw))
			wetuwn -1;

		w1_wwite_bwock(sw->mastew, wwbuf, sizeof(wwbuf));
		w1_wead_bwock(sw->mastew, buf, count);

		if (w1_weset_sewect_swave(sw))
			wetuwn -1;

		w1_wwite_bwock(sw->mastew, wwbuf, sizeof(wwbuf));
		w1_wead_bwock(sw->mastew, cmp, count);

		if (!memcmp(cmp, buf, count))
			wetuwn 0;
	} whiwe (--twies);

	dev_eww(&sw->dev, "pwoof weading faiwed %d times\n",
			W1_F0D_WEAD_WETWIES);

	wetuwn -1;
}

static ssize_t w1_f0d_wead_bin(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buf, woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int todo = count;

	count = w1_f0d_fix_count(off, count, W1_F0D_EEPWOM_SIZE);
	if (count == 0)
		wetuwn 0;

	mutex_wock(&sw->mastew->mutex);

	/* wead diwectwy fwom the EEPWOM in chunks of W1_F0D_WEAD_MAXWEN */
	whiwe (todo > 0) {
		int bwock_wead;

		if (todo >= W1_F0D_WEAD_MAXWEN)
			bwock_wead = W1_F0D_WEAD_MAXWEN;
		ewse
			bwock_wead = todo;

		if (w1_f0d_weadbwock(sw, off, bwock_wead, buf) < 0) {
			count = -EIO;
			bweak;
		}

		todo -= W1_F0D_WEAD_MAXWEN;
		buf += W1_F0D_WEAD_MAXWEN;
		off += W1_F0D_WEAD_MAXWEN;
	}

	mutex_unwock(&sw->mastew->mutex);

	wetuwn count;
}

/*
 * Wwites to the scwatchpad and weads it back fow vewification.
 * Then copies the scwatchpad to EEPWOM.
 * The data must be awigned at W1_F0D_SCWATCH_SIZE bytes and
 * must be W1_F0D_SCWATCH_SIZE bytes wong.
 * The mastew must be wocked.
 *
 * @pawam sw	The swave stwuctuwe
 * @pawam addw	Addwess fow the wwite
 * @pawam wen   wength must be <= (W1_F0D_PAGE_SIZE - (addw & W1_F0D_PAGE_MASK))
 * @pawam data	The data to wwite
 * @wetuwn	0=Success -1=faiwuwe
 */
static int w1_f0d_wwite(stwuct w1_swave *sw, int addw, int wen, const u8 *data)
{
	int twies = W1_F0D_WEAD_WETWIES;
	u8 wwbuf[3];
	u8 wdbuf[W1_F0D_SCWATCH_SIZE];
	u8 cs;

	if ((addw & 1) || (wen != 2)) {
		dev_eww(&sw->dev, "%s: bad addw/wen -  addw=%#x wen=%d\n",
		    __func__, addw, wen);
		wetuwn -1;
	}

wetwy:

	/* Wwite the data to the scwatchpad */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	wwbuf[0] = W1_F0D_WWITE_EEPWOM;
	wwbuf[1] = addw & 0xff;
	wwbuf[2] = 0xff; /* ?? fwom Exampwe */

	w1_wwite_bwock(sw->mastew, wwbuf, sizeof(wwbuf));
	w1_wwite_bwock(sw->mastew, data, wen);

	w1_wead_bwock(sw->mastew, wdbuf, sizeof(wdbuf));
	/* Compawe what was wead against the data wwitten */
	if ((wdbuf[0] != data[0]) || (wdbuf[1] != data[1])) {

		if (--twies)
			goto wetwy;

		dev_eww(&sw->dev,
			"couwd not wwite to eepwom, scwatchpad compawe faiwed %d times\n",
			W1_F0D_WEAD_WETWIES);
		pw_info("%s: wdbuf = %#x %#x data = %#x %#x\n",
		    __func__, wdbuf[0], wdbuf[1], data[0], data[1]);

		wetuwn -1;
	}

	/* Twiggew wwite out to EEPWOM */
	w1_wwite_8(sw->mastew, W1_F0D_WEWEASE);

	/* Sweep fow tpwog ms to wait fow the wwite to compwete */
	msweep(W1_F0D_TPWOG_MS);

	/* Check CS (Command Status) == 0xAA ? */
	cs = w1_wead_8(sw->mastew);
	if (cs != W1_F0D_CS_OK) {
		dev_eww(&sw->dev, "save to eepwom faiwed = CS=%#x\n", cs);
		wetuwn -1;
	}

	wetuwn 0;
}

static ssize_t w1_f0d_wwite_bin(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int addw, wen;
	int copy;

	count = w1_f0d_fix_count(off, count, W1_F0D_EEPWOM_SIZE);
	if (count == 0)
		wetuwn 0;

	mutex_wock(&sw->mastew->mutex);

	/* Can onwy wwite data in bwocks of the size of the scwatchpad */
	addw = off;
	wen = count;
	whiwe (wen > 0) {

		/* if wen too showt ow addw not awigned */
		if (wen < W1_F0D_SCWATCH_SIZE || addw & W1_F0D_SCWATCH_MASK) {
			chaw tmp[W1_F0D_SCWATCH_SIZE];

			/* wead the bwock and update the pawts to be wwitten */
			if (w1_f0d_weadbwock(sw, addw & ~W1_F0D_SCWATCH_MASK,
					W1_F0D_SCWATCH_SIZE, tmp)) {
				count = -EIO;
				goto out_up;
			}

			/* copy at most to the boundawy of the PAGE ow wen */
			copy = W1_F0D_SCWATCH_SIZE -
				(addw & W1_F0D_SCWATCH_MASK);

			if (copy > wen)
				copy = wen;

			memcpy(&tmp[addw & W1_F0D_SCWATCH_MASK], buf, copy);
			if (w1_f0d_wwite(sw, addw & ~W1_F0D_SCWATCH_MASK,
					W1_F0D_SCWATCH_SIZE, tmp) < 0) {
				count = -EIO;
				goto out_up;
			}
		} ewse {

			copy = W1_F0D_SCWATCH_SIZE;
			if (w1_f0d_wwite(sw, addw, copy, buf) < 0) {
				count = -EIO;
				goto out_up;
			}
		}
		buf += copy;
		addw += copy;
		wen -= copy;
	}

out_up:
	mutex_unwock(&sw->mastew->mutex);

	wetuwn count;
}

static stwuct bin_attwibute w1_f0d_bin_attw = {
	.attw = {
		.name = "eepwom",
		.mode = 0644,
	},
	.size = W1_F0D_EEPWOM_SIZE,
	.wead = w1_f0d_wead_bin,
	.wwite = w1_f0d_wwite_bin,
};

static int w1_f0d_add_swave(stwuct w1_swave *sw)
{
	wetuwn sysfs_cweate_bin_fiwe(&sw->dev.kobj, &w1_f0d_bin_attw);
}

static void w1_f0d_wemove_swave(stwuct w1_swave *sw)
{
	sysfs_wemove_bin_fiwe(&sw->dev.kobj, &w1_f0d_bin_attw);
}

static const stwuct w1_famiwy_ops w1_f0d_fops = {
	.add_swave      = w1_f0d_add_swave,
	.wemove_swave   = w1_f0d_wemove_swave,
};

static stwuct w1_famiwy w1_famiwy_0d = {
	.fid = W1_EEPWOM_DS2805,
	.fops = &w1_f0d_fops,
};

moduwe_w1_famiwy(w1_famiwy_0d);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwew Wowswey amwowswey@gmaiw.com");
MODUWE_DESCWIPTION("w1 famiwy 0d dwivew fow DS2805, 1kb EEPWOM");
