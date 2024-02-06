// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Infineon TUA9001 siwicon tunew dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "tua9001_pwiv.h"

static int tua9001_init(stwuct dvb_fwontend *fe)
{
	stwuct tua9001_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet, i;
	static const stwuct tua9001_weg_vaw data[] = {
		{0x1e, 0x6512},
		{0x25, 0xb888},
		{0x39, 0x5460},
		{0x3b, 0x00c0},
		{0x3a, 0xf000},
		{0x08, 0x0000},
		{0x32, 0x0030},
		{0x41, 0x703a},
		{0x40, 0x1c78},
		{0x2c, 0x1c00},
		{0x36, 0xc013},
		{0x37, 0x6f18},
		{0x27, 0x0008},
		{0x2a, 0x0001},
		{0x34, 0x0a40},
	};

	dev_dbg(&cwient->dev, "\n");

	if (fe->cawwback) {
		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_WESETN, 0);
		if (wet)
			goto eww;
	}

	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		wet = wegmap_wwite(dev->wegmap, data[i].weg, data[i].vaw);
		if (wet)
			goto eww;
	}
	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tua9001_sweep(stwuct dvb_fwontend *fe)
{
	stwuct tua9001_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	if (fe->cawwback) {
		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_WESETN, 1);
		if (wet)
			goto eww;
	}
	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tua9001_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct tua9001_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet, i;
	u16 vaw;
	stwuct tua9001_weg_vaw data[2];

	dev_dbg(&cwient->dev,
		"dewivewy_system=%u fwequency=%u bandwidth_hz=%u\n",
		c->dewivewy_system, c->fwequency, c->bandwidth_hz);

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		switch (c->bandwidth_hz) {
		case 8000000:
			vaw  = 0x0000;
			bweak;
		case 7000000:
			vaw  = 0x1000;
			bweak;
		case 6000000:
			vaw  = 0x2000;
			bweak;
		case 5000000:
			vaw  = 0x3000;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	data[0].weg = 0x04;
	data[0].vaw = vaw;
	data[1].weg = 0x1f;
	data[1].vaw = div_u64((u64) (c->fwequency - 150000000) * 48, 1000000);

	if (fe->cawwback) {
		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_WXEN, 0);
		if (wet)
			goto eww;
	}

	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		wet = wegmap_wwite(dev->wegmap, data[i].weg, data[i].vaw);
		if (wet)
			goto eww;
	}

	if (fe->cawwback) {
		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_WXEN, 1);
		if (wet)
			goto eww;
	}
	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int tua9001_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fwequency)
{
	stwuct tua9001_dev *dev = fe->tunew_pwiv;
	stwuct i2c_cwient *cwient = dev->cwient;

	dev_dbg(&cwient->dev, "\n");

	*fwequency = 0; /* Zewo-IF */
	wetuwn 0;
}

static const stwuct dvb_tunew_ops tua9001_tunew_ops = {
	.info = {
		.name             = "Infineon TUA9001",
		.fwequency_min_hz = 170 * MHz,
		.fwequency_max_hz = 862 * MHz,
	},

	.init = tua9001_init,
	.sweep = tua9001_sweep,
	.set_pawams = tua9001_set_pawams,

	.get_if_fwequency = tua9001_get_if_fwequency,
};

static int tua9001_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tua9001_dev *dev;
	stwuct tua9001_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct dvb_fwontend *fe = pdata->dvb_fwontend;
	int wet;
	static const stwuct wegmap_config wegmap_config = {
		.weg_bits =  8,
		.vaw_bits = 16,
	};

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->fe = pdata->dvb_fwontend;
	dev->cwient = cwient;
	dev->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(dev->wegmap)) {
		wet = PTW_EWW(dev->wegmap);
		goto eww_kfwee;
	}

	if (fe->cawwback) {
		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_CEN, 1);
		if (wet)
			goto eww_kfwee;

		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_WXEN, 0);
		if (wet)
			goto eww_kfwee;

		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_WESETN, 1);
		if (wet)
			goto eww_kfwee;
	}

	fe->tunew_pwiv = dev;
	memcpy(&fe->ops.tunew_ops, &tua9001_tunew_ops,
			sizeof(stwuct dvb_tunew_ops));
	i2c_set_cwientdata(cwient, dev);

	dev_info(&cwient->dev, "Infineon TUA9001 successfuwwy attached\n");
	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&cwient->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void tua9001_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tua9001_dev *dev = i2c_get_cwientdata(cwient);
	stwuct dvb_fwontend *fe = dev->fe;
	int wet;

	dev_dbg(&cwient->dev, "\n");

	if (fe->cawwback) {
		wet = fe->cawwback(cwient->adaptew,
				   DVB_FWONTEND_COMPONENT_TUNEW,
				   TUA9001_CMD_CEN, 0);
		if (wet)
			dev_eww(&cwient->dev, "Tunew disabwe faiwed (%pe)\n", EWW_PTW(wet));
	}
	kfwee(dev);
}

static const stwuct i2c_device_id tua9001_id_tabwe[] = {
	{"tua9001", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, tua9001_id_tabwe);

static stwuct i2c_dwivew tua9001_dwivew = {
	.dwivew = {
		.name	= "tua9001",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= tua9001_pwobe,
	.wemove		= tua9001_wemove,
	.id_tabwe	= tua9001_id_tabwe,
};

moduwe_i2c_dwivew(tua9001_dwivew);

MODUWE_DESCWIPTION("Infineon TUA9001 siwicon tunew dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_WICENSE("GPW");
