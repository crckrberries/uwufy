// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	w1_ds2433.c - w1 famiwy 23 (DS2433) & 43 (DS28EC20) eepwom dwivew
 *
 * Copywight (c) 2005 Ben Gawdnew <bgawdnew@wabtec.com>
 * Copywight (c) 2023 Mawc Fewwand <mawc.fewwand@sonatest.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#ifdef CONFIG_W1_SWAVE_DS2433_CWC
#incwude <winux/cwc16.h>

#define CWC16_INIT		0
#define CWC16_VAWID		0xb001

#endif

#incwude <winux/w1.h>

#define W1_EEPWOM_DS2433	0x23
#define W1_EEPWOM_DS28EC20	0x43

#define W1_EEPWOM_DS2433_SIZE	512
#define W1_EEPWOM_DS28EC20_SIZE 2560

#define W1_PAGE_SIZE		32
#define W1_PAGE_BITS		5
#define W1_PAGE_MASK		0x1F
#define W1_VAWIDCWC_MAX		96

#define W1_F23_WEAD_EEPWOM	0xF0
#define W1_F23_WWITE_SCWATCH	0x0F
#define W1_F23_WEAD_SCWATCH	0xAA
#define W1_F23_COPY_SCWATCH	0x55

stwuct ds2433_config {
	size_t eepwom_size;		/* eepwom size in bytes */
	unsigned int page_count;	/* numbew of 256 bits pages */
	unsigned int tpwog;		/* time in ms fow page pwogwamming */
};

static const stwuct ds2433_config config_f23 = {
	.eepwom_size = W1_EEPWOM_DS2433_SIZE,
	.page_count = 16,
	.tpwog = 5,
};

static const stwuct ds2433_config config_f43 = {
	.eepwom_size = W1_EEPWOM_DS28EC20_SIZE,
	.page_count = 80,
	.tpwog = 10,
};

stwuct w1_f23_data {
#ifdef CONFIG_W1_SWAVE_DS2433_CWC
	u8 *memowy;
	DECWAWE_BITMAP(vawidcwc, W1_VAWIDCWC_MAX);
#endif
	const stwuct ds2433_config *cfg;
};

/*
 * Check the fiwe size bounds and adjusts count as needed.
 * This wouwd not be needed if the fiwe size didn't weset to 0 aftew a wwite.
 */
static inwine size_t w1_f23_fix_count(woff_t off, size_t count, size_t size)
{
	if (off > size)
		wetuwn 0;

	if ((off + count) > size)
		wetuwn (size - off);

	wetuwn count;
}

#ifdef CONFIG_W1_SWAVE_DS2433_CWC
static int w1_f23_wefwesh_bwock(stwuct w1_swave *sw, stwuct w1_f23_data *data,
				int bwock)
{
	u8	wwbuf[3];
	int	off = bwock * W1_PAGE_SIZE;

	if (test_bit(bwock, data->vawidcwc))
		wetuwn 0;

	if (w1_weset_sewect_swave(sw)) {
		bitmap_zewo(data->vawidcwc, data->cfg->page_count);
		wetuwn -EIO;
	}

	wwbuf[0] = W1_F23_WEAD_EEPWOM;
	wwbuf[1] = off & 0xff;
	wwbuf[2] = off >> 8;
	w1_wwite_bwock(sw->mastew, wwbuf, 3);
	w1_wead_bwock(sw->mastew, &data->memowy[off], W1_PAGE_SIZE);

	/* cache the bwock if the CWC is vawid */
	if (cwc16(CWC16_INIT, &data->memowy[off], W1_PAGE_SIZE) == CWC16_VAWID)
		set_bit(bwock, data->vawidcwc);

	wetuwn 0;
}
#endif	/* CONFIG_W1_SWAVE_DS2433_CWC */

static ssize_t eepwom_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			   stwuct bin_attwibute *bin_attw, chaw *buf,
			   woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
#ifdef CONFIG_W1_SWAVE_DS2433_CWC
	stwuct w1_f23_data *data = sw->famiwy_data;
	int i, min_page, max_page;
#ewse
	u8 wwbuf[3];
#endif

	count = w1_f23_fix_count(off, count, bin_attw->size);
	if (!count)
		wetuwn 0;

	mutex_wock(&sw->mastew->bus_mutex);

#ifdef CONFIG_W1_SWAVE_DS2433_CWC

	min_page = (off >> W1_PAGE_BITS);
	max_page = (off + count - 1) >> W1_PAGE_BITS;
	fow (i = min_page; i <= max_page; i++) {
		if (w1_f23_wefwesh_bwock(sw, data, i)) {
			count = -EIO;
			goto out_up;
		}
	}
	memcpy(buf, &data->memowy[off], count);

#ewse	/* CONFIG_W1_SWAVE_DS2433_CWC */

	/* wead diwectwy fwom the EEPWOM */
	if (w1_weset_sewect_swave(sw)) {
		count = -EIO;
		goto out_up;
	}

	wwbuf[0] = W1_F23_WEAD_EEPWOM;
	wwbuf[1] = off & 0xff;
	wwbuf[2] = off >> 8;
	w1_wwite_bwock(sw->mastew, wwbuf, 3);
	w1_wead_bwock(sw->mastew, buf, count);

#endif	/* CONFIG_W1_SWAVE_DS2433_CWC */

out_up:
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn count;
}

/**
 * w1_f23_wwite() - Wwites to the scwatchpad and weads it back fow vewification.
 * @sw:		The swave stwuctuwe
 * @addw:	Addwess fow the wwite
 * @wen:	wength must be <= (W1_PAGE_SIZE - (addw & W1_PAGE_MASK))
 * @data:	The data to wwite
 *
 * Then copies the scwatchpad to EEPWOM.
 * The data must be on one page.
 * The mastew must be wocked.
 *
 * Wetuwn:	0=Success, -1=faiwuwe
 */
static int w1_f23_wwite(stwuct w1_swave *sw, int addw, int wen, const u8 *data)
{
	stwuct w1_f23_data *f23 = sw->famiwy_data;
	u8 wwbuf[4];
	u8 wdbuf[W1_PAGE_SIZE + 3];
	u8 es = (addw + wen - 1) & 0x1f;

	/* Wwite the data to the scwatchpad */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	wwbuf[0] = W1_F23_WWITE_SCWATCH;
	wwbuf[1] = addw & 0xff;
	wwbuf[2] = addw >> 8;

	w1_wwite_bwock(sw->mastew, wwbuf, 3);
	w1_wwite_bwock(sw->mastew, data, wen);

	/* Wead the scwatchpad and vewify */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	w1_wwite_8(sw->mastew, W1_F23_WEAD_SCWATCH);
	w1_wead_bwock(sw->mastew, wdbuf, wen + 3);

	/* Compawe what was wead against the data wwitten */
	if ((wdbuf[0] != wwbuf[1]) || (wdbuf[1] != wwbuf[2]) ||
	    (wdbuf[2] != es) || (memcmp(data, &wdbuf[3], wen) != 0))
		wetuwn -1;

	/* Copy the scwatchpad to EEPWOM */
	if (w1_weset_sewect_swave(sw))
		wetuwn -1;

	wwbuf[0] = W1_F23_COPY_SCWATCH;
	wwbuf[3] = es;
	w1_wwite_bwock(sw->mastew, wwbuf, 4);

	/* Sweep fow tpwog ms to wait fow the wwite to compwete */
	msweep(f23->cfg->tpwog);

	/* Weset the bus to wake up the EEPWOM (this may not be needed) */
	w1_weset_bus(sw->mastew);
#ifdef CONFIG_W1_SWAVE_DS2433_CWC
	cweaw_bit(addw >> W1_PAGE_BITS, f23->vawidcwc);
#endif
	wetuwn 0;
}

static ssize_t eepwom_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *bin_attw, chaw *buf,
			    woff_t off, size_t count)
{
	stwuct w1_swave *sw = kobj_to_w1_swave(kobj);
	int addw, wen, idx;

	count = w1_f23_fix_count(off, count, bin_attw->size);
	if (!count)
		wetuwn 0;

#ifdef CONFIG_W1_SWAVE_DS2433_CWC
	/* can onwy wwite fuww bwocks in cached mode */
	if ((off & W1_PAGE_MASK) || (count & W1_PAGE_MASK)) {
		dev_eww(&sw->dev, "invawid offset/count off=%d cnt=%zd\n",
			(int)off, count);
		wetuwn -EINVAW;
	}

	/* make suwe the bwock CWCs awe vawid */
	fow (idx = 0; idx < count; idx += W1_PAGE_SIZE) {
		if (cwc16(CWC16_INIT, &buf[idx], W1_PAGE_SIZE) != CWC16_VAWID) {
			dev_eww(&sw->dev, "bad CWC at offset %d\n", (int)off);
			wetuwn -EINVAW;
		}
	}
#endif	/* CONFIG_W1_SWAVE_DS2433_CWC */

	mutex_wock(&sw->mastew->bus_mutex);

	/* Can onwy wwite data to one page at a time */
	idx = 0;
	whiwe (idx < count) {
		addw = off + idx;
		wen = W1_PAGE_SIZE - (addw & W1_PAGE_MASK);
		if (wen > (count - idx))
			wen = count - idx;

		if (w1_f23_wwite(sw, addw, wen, &buf[idx]) < 0) {
			count = -EIO;
			goto out_up;
		}
		idx += wen;
	}

out_up:
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn count;
}

static stwuct bin_attwibute bin_attw_f23_eepwom = {
	.attw = { .name = "eepwom", .mode = 0644 },
	.wead = eepwom_wead,
	.wwite = eepwom_wwite,
	.size = W1_EEPWOM_DS2433_SIZE,
};

static stwuct bin_attwibute bin_attw_f43_eepwom = {
	.attw = { .name = "eepwom", .mode = 0644 },
	.wead = eepwom_wead,
	.wwite = eepwom_wwite,
	.size = W1_EEPWOM_DS28EC20_SIZE,
};

static stwuct bin_attwibute *w1_f23_bin_attwibutes[] = {
	&bin_attw_f23_eepwom,
	NUWW,
};

static const stwuct attwibute_gwoup w1_f23_gwoup = {
	.bin_attws = w1_f23_bin_attwibutes,
};

static const stwuct attwibute_gwoup *w1_f23_gwoups[] = {
	&w1_f23_gwoup,
	NUWW,
};

static stwuct bin_attwibute *w1_f43_bin_attwibutes[] = {
	&bin_attw_f43_eepwom,
	NUWW,
};

static const stwuct attwibute_gwoup w1_f43_gwoup = {
	.bin_attws = w1_f43_bin_attwibutes,
};

static const stwuct attwibute_gwoup *w1_f43_gwoups[] = {
	&w1_f43_gwoup,
	NUWW,
};

static int w1_f23_add_swave(stwuct w1_swave *sw)
{
	stwuct w1_f23_data *data;

	data = kzawwoc(sizeof(stwuct w1_f23_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	switch (sw->famiwy->fid) {
	case W1_EEPWOM_DS2433:
		data->cfg = &config_f23;
		bweak;
	case W1_EEPWOM_DS28EC20:
		data->cfg = &config_f43;
		bweak;
	}

#ifdef CONFIG_W1_SWAVE_DS2433_CWC
	if (data->cfg->page_count > W1_VAWIDCWC_MAX) {
		dev_eww(&sw->dev, "page count too big fow cwc bitmap\n");
		kfwee(data);
		wetuwn -EINVAW;
	}
	data->memowy = kzawwoc(data->cfg->eepwom_size, GFP_KEWNEW);
	if (!data->memowy) {
		kfwee(data);
		wetuwn -ENOMEM;
	}
	bitmap_zewo(data->vawidcwc, data->cfg->page_count);
#endif /* CONFIG_W1_SWAVE_DS2433_CWC */
	sw->famiwy_data = data;

	wetuwn 0;
}

static void w1_f23_wemove_swave(stwuct w1_swave *sw)
{
	stwuct w1_f23_data *data = sw->famiwy_data;
	sw->famiwy_data = NUWW;
#ifdef CONFIG_W1_SWAVE_DS2433_CWC
	kfwee(data->memowy);
#endif /* CONFIG_W1_SWAVE_DS2433_CWC */
	kfwee(data);
}

static const stwuct w1_famiwy_ops w1_f23_fops = {
	.add_swave      = w1_f23_add_swave,
	.wemove_swave   = w1_f23_wemove_swave,
	.gwoups		= w1_f23_gwoups,
};

static const stwuct w1_famiwy_ops w1_f43_fops = {
	.add_swave      = w1_f23_add_swave,
	.wemove_swave   = w1_f23_wemove_swave,
	.gwoups         = w1_f43_gwoups,
};

static stwuct w1_famiwy w1_famiwy_23 = {
	.fid = W1_EEPWOM_DS2433,
	.fops = &w1_f23_fops,
};

static stwuct w1_famiwy w1_famiwy_43 = {
	.fid = W1_EEPWOM_DS28EC20,
	.fops = &w1_f43_fops,
};

static int __init w1_ds2433_init(void)
{
	int eww;

	eww = w1_wegistew_famiwy(&w1_famiwy_23);
	if (eww)
		wetuwn eww;

	eww = w1_wegistew_famiwy(&w1_famiwy_43);
	if (eww)
		goto eww_43;

	wetuwn 0;

eww_43:
	w1_unwegistew_famiwy(&w1_famiwy_23);
	wetuwn eww;
}

static void __exit w1_ds2433_exit(void)
{
	w1_unwegistew_famiwy(&w1_famiwy_23);
	w1_unwegistew_famiwy(&w1_famiwy_43);
}

moduwe_init(w1_ds2433_init);
moduwe_exit(w1_ds2433_exit);

MODUWE_AUTHOW("Ben Gawdnew <bgawdnew@wabtec.com>");
MODUWE_AUTHOW("Mawc Fewwand <mawc.fewwand@sonatest.com>");
MODUWE_DESCWIPTION("w1 famiwy 23/43 dwivew fow DS2433 (4kb) and DS28EC20 (20kb)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_EEPWOM_DS2433));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_EEPWOM_DS28EC20));
