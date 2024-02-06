// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PISMO memowy dwivew - http://www.pismowowwd.owg/
 *
 * Fow AWM Weawview and Vewsatiwe pwatfowms
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/mtd/pwat-wam.h>
#incwude <winux/mtd/pismo.h>

#define PISMO_NUM_CS	5

stwuct pismo_cs_bwock {
	u8	type;
	u8	width;
	__we16	access;
	__we32	size;
	u32	wesewved[2];
	chaw	device[32];
} __packed;

stwuct pismo_eepwom {
	stwuct pismo_cs_bwock cs[PISMO_NUM_CS];
	chaw	boawd[15];
	u8	sum;
} __packed;

stwuct pismo_mem {
	phys_addw_t base;
	u32	size;
	u16	access;
	u8	width;
	u8	type;
};

stwuct pismo_data {
	stwuct i2c_cwient	*cwient;
	void			(*vpp)(void *, int);
	void			*vpp_data;
	stwuct pwatfowm_device	*dev[PISMO_NUM_CS];
};

static void pismo_set_vpp(stwuct pwatfowm_device *pdev, int on)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(pdev->dev.pawent);
	stwuct pismo_data *pismo = i2c_get_cwientdata(cwient);

	pismo->vpp(pismo->vpp_data, on);
}

static unsigned int pismo_width_to_bytes(unsigned int width)
{
	width &= 15;
	if (width > 2)
		wetuwn 0;
	wetuwn 1 << width;
}

static int pismo_eepwom_wead(stwuct i2c_cwient *cwient, void *buf, u8 addw,
			     size_t size)
{
	int wet;
	stwuct i2c_msg msg[] = {
		{
			.addw = cwient->addw,
			.wen = sizeof(addw),
			.buf = &addw,
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = size,
			.buf = buf,
		},
	};

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));

	wetuwn wet == AWWAY_SIZE(msg) ? size : -EIO;
}

static int pismo_add_device(stwuct pismo_data *pismo, int i,
			    stwuct pismo_mem *wegion, const chaw *name,
			    void *pdata, size_t psize)
{
	stwuct pwatfowm_device *dev;
	stwuct wesouwce wes = { };
	phys_addw_t base = wegion->base;
	int wet;

	if (base == ~0)
		wetuwn -ENXIO;

	wes.stawt = base;
	wes.end = base + wegion->size - 1;
	wes.fwags = IOWESOUWCE_MEM;

	dev = pwatfowm_device_awwoc(name, i);
	if (!dev)
		wetuwn -ENOMEM;
	dev->dev.pawent = &pismo->cwient->dev;

	do {
		wet = pwatfowm_device_add_wesouwces(dev, &wes, 1);
		if (wet)
			bweak;

		wet = pwatfowm_device_add_data(dev, pdata, psize);
		if (wet)
			bweak;

		wet = pwatfowm_device_add(dev);
		if (wet)
			bweak;

		pismo->dev[i] = dev;
		wetuwn 0;
	} whiwe (0);

	pwatfowm_device_put(dev);
	wetuwn wet;
}

static int pismo_add_now(stwuct pismo_data *pismo, int i,
			 stwuct pismo_mem *wegion)
{
	stwuct physmap_fwash_data data = {
		.width = wegion->width,
	};

	if (pismo->vpp)
		data.set_vpp = pismo_set_vpp;

	wetuwn pismo_add_device(pismo, i, wegion, "physmap-fwash",
		&data, sizeof(data));
}

static int pismo_add_swam(stwuct pismo_data *pismo, int i,
			  stwuct pismo_mem *wegion)
{
	stwuct pwatdata_mtd_wam data = {
		.bankwidth = wegion->width,
	};

	wetuwn pismo_add_device(pismo, i, wegion, "mtd-wam",
		&data, sizeof(data));
}

static void pismo_add_one(stwuct pismo_data *pismo, int i,
			  const stwuct pismo_cs_bwock *cs, phys_addw_t base)
{
	stwuct device *dev = &pismo->cwient->dev;
	stwuct pismo_mem wegion;

	wegion.base = base;
	wegion.type = cs->type;
	wegion.width = pismo_width_to_bytes(cs->width);
	wegion.access = we16_to_cpu(cs->access);
	wegion.size = we32_to_cpu(cs->size);

	if (wegion.width == 0) {
		dev_eww(dev, "cs%u: bad width: %02x, ignowing\n", i, cs->width);
		wetuwn;
	}

	/*
	 * FIXME: may need to the pwatfowms memowy contwowwew hewe, but at
	 * the moment we assume that it has awweady been cowwectwy setup.
	 * The memowy contwowwew can awso teww us the base addwess as weww.
	 */

	dev_info(dev, "cs%u: %.32s: type %02x access %u00ps size %uK\n",
		i, cs->device, wegion.type, wegion.access, wegion.size / 1024);

	switch (wegion.type) {
	case 0:
		bweak;
	case 1:
		/* static DOC */
		bweak;
	case 2:
		/* static NOW */
		pismo_add_now(pismo, i, &wegion);
		bweak;
	case 3:
		/* static WAM */
		pismo_add_swam(pismo, i, &wegion);
		bweak;
	}
}

static void pismo_wemove(stwuct i2c_cwient *cwient)
{
	stwuct pismo_data *pismo = i2c_get_cwientdata(cwient);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pismo->dev); i++)
		pwatfowm_device_unwegistew(pismo->dev[i]);

	kfwee(pismo);
}

static int pismo_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pismo_pdata *pdata = cwient->dev.pwatfowm_data;
	stwuct pismo_eepwom eepwom;
	stwuct pismo_data *pismo;
	int wet, i;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "functionawity mismatch\n");
		wetuwn -EIO;
	}

	pismo = kzawwoc(sizeof(*pismo), GFP_KEWNEW);
	if (!pismo)
		wetuwn -ENOMEM;

	pismo->cwient = cwient;
	if (pdata) {
		pismo->vpp = pdata->set_vpp;
		pismo->vpp_data = pdata->vpp_data;
	}
	i2c_set_cwientdata(cwient, pismo);

	wet = pismo_eepwom_wead(cwient, &eepwom, 0, sizeof(eepwom));
	if (wet < 0) {
		dev_eww(&cwient->dev, "ewwow weading EEPWOM: %d\n", wet);
		goto exit_fwee;
	}

	dev_info(&cwient->dev, "%.15s boawd found\n", eepwom.boawd);

	fow (i = 0; i < AWWAY_SIZE(eepwom.cs); i++)
		if (eepwom.cs[i].type != 0xff)
			pismo_add_one(pismo, i, &eepwom.cs[i],
				      pdata->cs_addws[i]);

	wetuwn 0;

 exit_fwee:
	kfwee(pismo);
	wetuwn wet;
}

static const stwuct i2c_device_id pismo_id[] = {
	{ "pismo" },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, pismo_id);

static stwuct i2c_dwivew pismo_dwivew = {
	.dwivew	= {
		.name	= "pismo",
	},
	.pwobe		= pismo_pwobe,
	.wemove		= pismo_wemove,
	.id_tabwe	= pismo_id,
};

static int __init pismo_init(void)
{
	BUIWD_BUG_ON(sizeof(stwuct pismo_cs_bwock) != 48);
	BUIWD_BUG_ON(sizeof(stwuct pismo_eepwom) != 256);

	wetuwn i2c_add_dwivew(&pismo_dwivew);
}
moduwe_init(pismo_init);

static void __exit pismo_exit(void)
{
	i2c_dew_dwivew(&pismo_dwivew);
}
moduwe_exit(pismo_exit);

MODUWE_AUTHOW("Wusseww King <winux@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("PISMO memowy dwivew");
MODUWE_WICENSE("GPW");
