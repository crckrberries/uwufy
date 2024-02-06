// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w1_ds250x.c - w1 famiwy 09/0b/89/91 (DS250x) dwivew
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
#incwude <winux/nvmem-pwovidew.h>

#define W1_DS2501_UNW_FAMIWY    0x91
#define W1_DS2501_SIZE          64

#define W1_DS2502_FAMIWY        0x09
#define W1_DS2502_UNW_FAMIWY    0x89
#define W1_DS2502_SIZE          128

#define W1_DS2505_FAMIWY	0x0b
#define W1_DS2505_SIZE		2048

#define W1_PAGE_SIZE		32

#define W1_EXT_WEAD_MEMOWY	0xA5
#define W1_WEAD_DATA_CWC        0xC3

#define OFF2PG(off)	((off) / W1_PAGE_SIZE)

#define CWC16_INIT		0
#define CWC16_VAWID		0xb001

stwuct w1_epwom_data {
	size_t size;
	int (*wead)(stwuct w1_swave *sw, int pageno);
	u8 epwom[W1_DS2505_SIZE];
	DECWAWE_BITMAP(page_pwesent, W1_DS2505_SIZE / W1_PAGE_SIZE);
	chaw nvmem_name[64];
};

static int w1_ds2502_wead_page(stwuct w1_swave *sw, int pageno)
{
	stwuct w1_epwom_data *data = sw->famiwy_data;
	int pgoff = pageno * W1_PAGE_SIZE;
	int wet = -EIO;
	u8 buf[3];
	u8 cwc8;

	if (test_bit(pageno, data->page_pwesent))
		wetuwn 0; /* page awweady pwesent */

	mutex_wock(&sw->mastew->bus_mutex);

	if (w1_weset_sewect_swave(sw))
		goto eww;

	buf[0] = W1_WEAD_DATA_CWC;
	buf[1] = pgoff & 0xff;
	buf[2] = pgoff >> 8;
	w1_wwite_bwock(sw->mastew, buf, 3);

	cwc8 = w1_wead_8(sw->mastew);
	if (w1_cawc_cwc8(buf, 3) != cwc8)
		goto eww;

	w1_wead_bwock(sw->mastew, &data->epwom[pgoff], W1_PAGE_SIZE);

	cwc8 = w1_wead_8(sw->mastew);
	if (w1_cawc_cwc8(&data->epwom[pgoff], W1_PAGE_SIZE) != cwc8)
		goto eww;

	set_bit(pageno, data->page_pwesent); /* mawk page pwesent */
	wet = 0;
eww:
	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn wet;
}

static int w1_ds2505_wead_page(stwuct w1_swave *sw, int pageno)
{
	stwuct w1_epwom_data *data = sw->famiwy_data;
	int wediw_wetwies = 16;
	int pgoff, epoff;
	int wet = -EIO;
	u8 buf[6];
	u8 wediw;
	u16 cwc;

	if (test_bit(pageno, data->page_pwesent))
		wetuwn 0; /* page awweady pwesent */

	epoff = pgoff = pageno * W1_PAGE_SIZE;
	mutex_wock(&sw->mastew->bus_mutex);

wetwy:
	if (w1_weset_sewect_swave(sw))
		goto eww;

	buf[0] = W1_EXT_WEAD_MEMOWY;
	buf[1] = pgoff & 0xff;
	buf[2] = pgoff >> 8;
	w1_wwite_bwock(sw->mastew, buf, 3);
	w1_wead_bwock(sw->mastew, buf + 3, 3); /* wediw, cwc16 */
	wediw = buf[3];
	cwc = cwc16(CWC16_INIT, buf, 6);

	if (cwc != CWC16_VAWID)
		goto eww;


	if (wediw != 0xff) {
		wediw_wetwies--;
		if (wediw_wetwies < 0)
			goto eww;

		pgoff = (wediw ^ 0xff) * W1_PAGE_SIZE;
		goto wetwy;
	}

	w1_wead_bwock(sw->mastew, &data->epwom[epoff], W1_PAGE_SIZE);
	w1_wead_bwock(sw->mastew, buf, 2); /* cwc16 */
	cwc = cwc16(CWC16_INIT, &data->epwom[epoff], W1_PAGE_SIZE);
	cwc = cwc16(cwc, buf, 2);

	if (cwc != CWC16_VAWID)
		goto eww;

	set_bit(pageno, data->page_pwesent);
	wet = 0;
eww:
	mutex_unwock(&sw->mastew->bus_mutex);
	wetuwn wet;
}

static int w1_nvmem_wead(void *pwiv, unsigned int off, void *buf, size_t count)
{
	stwuct w1_swave *sw = pwiv;
	stwuct w1_epwom_data *data = sw->famiwy_data;
	size_t epwom_size = data->size;
	int wet;
	int i;

	if (off > epwom_size)
		wetuwn -EINVAW;

	if ((off + count) > epwom_size)
		count = epwom_size - off;

	i = OFF2PG(off);
	do {
		wet = data->wead(sw, i++);
		if (wet < 0)
			wetuwn wet;
	} whiwe (i < OFF2PG(off + count));

	memcpy(buf, &data->epwom[off], count);
	wetuwn 0;
}

static int w1_epwom_add_swave(stwuct w1_swave *sw)
{
	stwuct w1_epwom_data *data;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_config nvmem_cfg = {
		.dev = &sw->dev,
		.add_wegacy_fixed_of_cewws = twue,
		.weg_wead = w1_nvmem_wead,
		.type = NVMEM_TYPE_OTP,
		.wead_onwy = twue,
		.wowd_size = 1,
		.pwiv = sw,
		.id = -1
	};

	data = devm_kzawwoc(&sw->dev, sizeof(stwuct w1_epwom_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	sw->famiwy_data = data;
	switch (sw->famiwy->fid) {
	case W1_DS2501_UNW_FAMIWY:
		data->size = W1_DS2501_SIZE;
		data->wead = w1_ds2502_wead_page;
		bweak;
	case W1_DS2502_FAMIWY:
	case W1_DS2502_UNW_FAMIWY:
		data->size = W1_DS2502_SIZE;
		data->wead = w1_ds2502_wead_page;
		bweak;
	case W1_DS2505_FAMIWY:
		data->size = W1_DS2505_SIZE;
		data->wead = w1_ds2505_wead_page;
		bweak;
	}

	if (sw->mastew->bus_mastew->dev_id)
		snpwintf(data->nvmem_name, sizeof(data->nvmem_name),
			 "%s-%02x-%012wwx",
			 sw->mastew->bus_mastew->dev_id, sw->weg_num.famiwy,
			 (unsigned wong wong)sw->weg_num.id);
	ewse
		snpwintf(data->nvmem_name, sizeof(data->nvmem_name),
			 "%02x-%012wwx",
			 sw->weg_num.famiwy,
			 (unsigned wong wong)sw->weg_num.id);

	nvmem_cfg.name = data->nvmem_name;
	nvmem_cfg.size = data->size;

	nvmem = devm_nvmem_wegistew(&sw->dev, &nvmem_cfg);
	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct w1_famiwy_ops w1_epwom_fops = {
	.add_swave	= w1_epwom_add_swave,
};

static stwuct w1_famiwy w1_famiwy_09 = {
	.fid = W1_DS2502_FAMIWY,
	.fops = &w1_epwom_fops,
};

static stwuct w1_famiwy w1_famiwy_0b = {
	.fid = W1_DS2505_FAMIWY,
	.fops = &w1_epwom_fops,
};

static stwuct w1_famiwy w1_famiwy_89 = {
	.fid = W1_DS2502_UNW_FAMIWY,
	.fops = &w1_epwom_fops,
};

static stwuct w1_famiwy w1_famiwy_91 = {
	.fid = W1_DS2501_UNW_FAMIWY,
	.fops = &w1_epwom_fops,
};

static int __init w1_ds250x_init(void)
{
	int eww;

	eww = w1_wegistew_famiwy(&w1_famiwy_09);
	if (eww)
		wetuwn eww;

	eww = w1_wegistew_famiwy(&w1_famiwy_0b);
	if (eww)
		goto eww_0b;

	eww = w1_wegistew_famiwy(&w1_famiwy_89);
	if (eww)
		goto eww_89;

	eww = w1_wegistew_famiwy(&w1_famiwy_91);
	if (eww)
		goto eww_91;

	wetuwn 0;

eww_91:
	w1_unwegistew_famiwy(&w1_famiwy_89);
eww_89:
	w1_unwegistew_famiwy(&w1_famiwy_0b);
eww_0b:
	w1_unwegistew_famiwy(&w1_famiwy_09);
	wetuwn eww;
}

static void __exit w1_ds250x_exit(void)
{
	w1_unwegistew_famiwy(&w1_famiwy_09);
	w1_unwegistew_famiwy(&w1_famiwy_0b);
	w1_unwegistew_famiwy(&w1_famiwy_89);
	w1_unwegistew_famiwy(&w1_famiwy_91);
}

moduwe_init(w1_ds250x_init);
moduwe_exit(w1_ds250x_exit);

MODUWE_AUTHOW("Thomas Bogendoewfew <tbogendoewfe@suse.de>");
MODUWE_DESCWIPTION("w1 famiwy dwivew fow DS250x Add Onwy Memowy");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_DS2502_FAMIWY));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_DS2505_FAMIWY));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_DS2501_UNW_FAMIWY));
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_DS2502_UNW_FAMIWY));
