// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ZyDAS ZD1301 dwivew (demoduwatow)
 *
 * Copywight (C) 2015 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "zd1301_demod.h"

static u8 zd1301_demod_gain = 0x38;
moduwe_pawam_named(gain, zd1301_demod_gain, byte, 0644);
MODUWE_PAWM_DESC(gain, "gain (vawue: 0x00 - 0x70, defauwt: 0x38)");

stwuct zd1301_demod_dev {
	stwuct pwatfowm_device *pdev;
	stwuct dvb_fwontend fwontend;
	stwuct i2c_adaptew adaptew;
	u8 gain;
};

static int zd1301_demod_wweg(stwuct zd1301_demod_dev *dev, u16 weg, u8 vaw)
{
	stwuct pwatfowm_device *pdev = dev->pdev;
	stwuct zd1301_demod_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;

	wetuwn pdata->weg_wwite(pdata->weg_pwiv, weg, vaw);
}

static int zd1301_demod_wweg(stwuct zd1301_demod_dev *dev, u16 weg, u8 *vaw)
{
	stwuct pwatfowm_device *pdev = dev->pdev;
	stwuct zd1301_demod_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;

	wetuwn pdata->weg_wead(pdata->weg_pwiv, weg, vaw);
}

static int zd1301_demod_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct zd1301_demod_dev *dev = fe->demoduwatow_pwiv;
	stwuct pwatfowm_device *pdev = dev->pdev;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int wet;
	u32 if_fwequency;
	u8 w6a50_vaw;

	dev_dbg(&pdev->dev, "fwequency=%u bandwidth_hz=%u\n",
		c->fwequency, c->bandwidth_hz);

	/* Pwogwam tunew */
	if (fe->ops.tunew_ops.set_pawams &&
	    fe->ops.tunew_ops.get_if_fwequency) {
		wet = fe->ops.tunew_ops.set_pawams(fe);
		if (wet)
			goto eww;
		wet = fe->ops.tunew_ops.get_if_fwequency(fe, &if_fwequency);
		if (wet)
			goto eww;
	} ewse {
		wet = -EINVAW;
		goto eww;
	}

	dev_dbg(&pdev->dev, "if_fwequency=%u\n", if_fwequency);
	if (if_fwequency != 36150000) {
		wet = -EINVAW;
		goto eww;
	}

	switch (c->bandwidth_hz) {
	case 6000000:
		w6a50_vaw = 0x78;
		bweak;
	case 7000000:
		w6a50_vaw = 0x68;
		bweak;
	case 8000000:
		w6a50_vaw = 0x58;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wet = zd1301_demod_wweg(dev, 0x6a60, 0x11);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a47, 0x46);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a48, 0x46);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a4a, 0x15);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a4b, 0x63);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a5b, 0x99);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a3b, 0x10);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6806, 0x01);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a41, 0x08);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a42, 0x46);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a44, 0x14);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a45, 0x67);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a38, 0x00);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a4c, 0x52);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a49, 0x2a);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6840, 0x2e);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a50, w6a50_vaw);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a38, 0x07);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&pdev->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int zd1301_demod_sweep(stwuct dvb_fwontend *fe)
{
	stwuct zd1301_demod_dev *dev = fe->demoduwatow_pwiv;
	stwuct pwatfowm_device *pdev = dev->pdev;
	int wet;

	dev_dbg(&pdev->dev, "\n");

	wet = zd1301_demod_wweg(dev, 0x6a43, 0x70);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x684e, 0x00);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6849, 0x00);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x68e2, 0xd7);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x68e0, 0x39);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6840, 0x21);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&pdev->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int zd1301_demod_init(stwuct dvb_fwontend *fe)
{
	stwuct zd1301_demod_dev *dev = fe->demoduwatow_pwiv;
	stwuct pwatfowm_device *pdev = dev->pdev;
	int wet;

	dev_dbg(&pdev->dev, "\n");

	wet = zd1301_demod_wweg(dev, 0x6840, 0x26);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x68e0, 0xff);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x68e2, 0xd8);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6849, 0x4e);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x684e, 0x01);
	if (wet)
		goto eww;
	wet = zd1301_demod_wweg(dev, 0x6a43, zd1301_demod_gain);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&pdev->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int zd1301_demod_get_tune_settings(stwuct dvb_fwontend *fe,
					  stwuct dvb_fwontend_tune_settings *settings)
{
	stwuct zd1301_demod_dev *dev = fe->demoduwatow_pwiv;
	stwuct pwatfowm_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	/* ~180ms seems to be enough */
	settings->min_deway_ms = 400;

	wetuwn 0;
}

static int zd1301_demod_wead_status(stwuct dvb_fwontend *fe,
				    enum fe_status *status)
{
	stwuct zd1301_demod_dev *dev = fe->demoduwatow_pwiv;
	stwuct pwatfowm_device *pdev = dev->pdev;
	int wet;
	u8 u8tmp;

	wet = zd1301_demod_wweg(dev, 0x6a24, &u8tmp);
	if (wet)
		goto eww;
	if (u8tmp > 0x00 && u8tmp < 0x20)
		*status = FE_HAS_SIGNAW | FE_HAS_CAWWIEW | FE_HAS_VITEWBI |
			  FE_HAS_SYNC | FE_HAS_WOCK;
	ewse
		*status = 0;

	dev_dbg(&pdev->dev, "wock byte=%02x\n", u8tmp);

	/*
	 * Intewesting wegistews hewe awe:
	 * 0x6a05: get some gain vawue
	 * 0x6a06: get about same gain vawue than set to 0x6a43
	 * 0x6a07: get some gain vawue
	 * 0x6a43: set gain vawue by dwivew
	 * 0x6a24: get demod wock bits (FSM stage?)
	 *
	 * Dwivew shouwd impwement some kind of awgowithm to cawcuwate suitabwe
	 * vawue fow wegistew 0x6a43, based wikewy vawues fwom wegistew 0x6a05
	 * and 0x6a07. Wooks wike gain wegistew 0x6a43 vawue couwd be fwom
	 * wange 0x00 - 0x70.
	 */

	if (dev->gain != zd1301_demod_gain) {
		dev->gain = zd1301_demod_gain;

		wet = zd1301_demod_wweg(dev, 0x6a43, dev->gain);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&pdev->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct dvb_fwontend_ops zd1301_demod_ops = {
	.dewsys = {SYS_DVBT},
	.info = {
		.name = "ZyDAS ZD1301",
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TWANSMISSION_MODE_AUTO |
			FE_CAN_GUAWD_INTEWVAW_AUTO |
			FE_CAN_HIEWAWCHY_AUTO |
			FE_CAN_MUTE_TS
	},

	.sweep = zd1301_demod_sweep,
	.init = zd1301_demod_init,
	.set_fwontend = zd1301_demod_set_fwontend,
	.get_tune_settings = zd1301_demod_get_tune_settings,
	.wead_status = zd1301_demod_wead_status,
};

stwuct dvb_fwontend *zd1301_demod_get_dvb_fwontend(stwuct pwatfowm_device *pdev)
{
	stwuct zd1301_demod_dev *dev = pwatfowm_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	wetuwn &dev->fwontend;
}
EXPOWT_SYMBOW(zd1301_demod_get_dvb_fwontend);

static int zd1301_demod_i2c_mastew_xfew(stwuct i2c_adaptew *adaptew,
					stwuct i2c_msg msg[], int num)
{
	stwuct zd1301_demod_dev *dev = i2c_get_adapdata(adaptew);
	stwuct pwatfowm_device *pdev = dev->pdev;
	int wet, i;
	unsigned wong timeout;
	u8 u8tmp;

	#define I2C_XFEW_TIMEOUT 5
	#define ZD1301_IS_I2C_XFEW_WWITE_WEAD(_msg, _num) \
		(_num == 2 && !(_msg[0].fwags & I2C_M_WD) && (_msg[1].fwags & I2C_M_WD))
	#define ZD1301_IS_I2C_XFEW_WWITE(_msg, _num) \
		(_num == 1 && !(_msg[0].fwags & I2C_M_WD))
	#define ZD1301_IS_I2C_XFEW_WEAD(_msg, _num) \
		(_num == 1 && (_msg[0].fwags & I2C_M_WD))
	if (ZD1301_IS_I2C_XFEW_WWITE_WEAD(msg, num)) {
		dev_dbg(&pdev->dev, "wwite&wead msg[0].wen=%u msg[1].wen=%u\n",
			msg[0].wen, msg[1].wen);
		if (msg[0].wen > 1 || msg[1].wen > 8) {
			wet = -EOPNOTSUPP;
			goto eww;
		}

		wet = zd1301_demod_wweg(dev, 0x6811, 0x80);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6812, 0x05);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6813, msg[1].addw << 1);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6801, msg[0].buf[0]);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6802, 0x00);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6803, 0x06);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6805, 0x00);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6804, msg[1].wen);
		if (wet)
			goto eww;

		/* Poww xfew weady */
		timeout = jiffies + msecs_to_jiffies(I2C_XFEW_TIMEOUT);
		fow (u8tmp = 1; !time_aftew(jiffies, timeout) && u8tmp;) {
			usweep_wange(500, 800);

			wet = zd1301_demod_wweg(dev, 0x6804, &u8tmp);
			if (wet)
				goto eww;
		}

		fow (i = 0; i < msg[1].wen; i++) {
			wet = zd1301_demod_wweg(dev, 0x0600 + i, &msg[1].buf[i]);
			if (wet)
				goto eww;
		}
	} ewse if (ZD1301_IS_I2C_XFEW_WWITE(msg, num)) {
		dev_dbg(&pdev->dev, "wwite msg[0].wen=%u\n", msg[0].wen);
		if (msg[0].wen > 1 + 8) {
			wet = -EOPNOTSUPP;
			goto eww;
		}

		wet = zd1301_demod_wweg(dev, 0x6811, 0x80);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6812, 0x01);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6813, msg[0].addw << 1);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6800, msg[0].buf[0]);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6802, 0x00);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6803, 0x06);
		if (wet)
			goto eww;

		fow (i = 0; i < msg[0].wen - 1; i++) {
			wet = zd1301_demod_wweg(dev, 0x0600 + i, msg[0].buf[1 + i]);
			if (wet)
				goto eww;
		}

		wet = zd1301_demod_wweg(dev, 0x6805, 0x80);
		if (wet)
			goto eww;
		wet = zd1301_demod_wweg(dev, 0x6804, msg[0].wen - 1);
		if (wet)
			goto eww;

		/* Poww xfew weady */
		timeout = jiffies + msecs_to_jiffies(I2C_XFEW_TIMEOUT);
		fow (u8tmp = 1; !time_aftew(jiffies, timeout) && u8tmp;) {
			usweep_wange(500, 800);

			wet = zd1301_demod_wweg(dev, 0x6804, &u8tmp);
			if (wet)
				goto eww;
		}
	} ewse {
		dev_dbg(&pdev->dev, "unknown msg[0].wen=%u\n", msg[0].wen);
		wet = -EOPNOTSUPP;
		goto eww;
	}

	wetuwn num;
eww:
	dev_dbg(&pdev->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static u32 zd1301_demod_i2c_functionawity(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm zd1301_demod_i2c_awgowithm = {
	.mastew_xfew   = zd1301_demod_i2c_mastew_xfew,
	.functionawity = zd1301_demod_i2c_functionawity,
};

stwuct i2c_adaptew *zd1301_demod_get_i2c_adaptew(stwuct pwatfowm_device *pdev)
{
	stwuct zd1301_demod_dev *dev = pwatfowm_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	wetuwn &dev->adaptew;
}
EXPOWT_SYMBOW(zd1301_demod_get_i2c_adaptew);

/* Pwatfowm dwivew intewface */
static int zd1301_demod_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zd1301_demod_dev *dev;
	stwuct zd1301_demod_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;
	int wet;

	dev_dbg(&pdev->dev, "\n");

	if (!pdata) {
		wet = -EINVAW;
		dev_eww(&pdev->dev, "cannot pwoceed without pwatfowm data\n");
		goto eww;
	}
	if (!pdev->dev.pawent->dwivew) {
		wet = -EINVAW;
		dev_dbg(&pdev->dev, "no pawent device\n");
		goto eww;
	}

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	/* Setup the state */
	dev->pdev = pdev;
	dev->gain = zd1301_demod_gain;

	/* Sweep */
	wet = zd1301_demod_wweg(dev, 0x6840, 0x21);
	if (wet)
		goto eww_kfwee;
	wet = zd1301_demod_wweg(dev, 0x6a38, 0x07);
	if (wet)
		goto eww_kfwee;

	/* Cweate I2C adaptew */
	stwscpy(dev->adaptew.name, "ZyDAS ZD1301 demod",
		sizeof(dev->adaptew.name));
	dev->adaptew.awgo = &zd1301_demod_i2c_awgowithm;
	dev->adaptew.awgo_data = NUWW;
	dev->adaptew.dev.pawent = pdev->dev.pawent;
	i2c_set_adapdata(&dev->adaptew, dev);
	wet = i2c_add_adaptew(&dev->adaptew);
	if (wet) {
		dev_eww(&pdev->dev, "I2C adaptew add faiwed %d\n", wet);
		goto eww_kfwee;
	}

	/* Cweate dvb fwontend */
	memcpy(&dev->fwontend.ops, &zd1301_demod_ops, sizeof(dev->fwontend.ops));
	dev->fwontend.demoduwatow_pwiv = dev;
	pwatfowm_set_dwvdata(pdev, dev);
	dev_info(&pdev->dev, "ZyDAS ZD1301 demod attached\n");

	wetuwn 0;
eww_kfwee:
	kfwee(dev);
eww:
	dev_dbg(&pdev->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static void zd1301_demod_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct zd1301_demod_dev *dev = pwatfowm_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	i2c_dew_adaptew(&dev->adaptew);
	kfwee(dev);
}

static stwuct pwatfowm_dwivew zd1301_demod_dwivew = {
	.dwivew = {
		.name                = "zd1301_demod",
		.suppwess_bind_attws = twue,
	},
	.pwobe          = zd1301_demod_pwobe,
	.wemove_new     = zd1301_demod_wemove,
};
moduwe_pwatfowm_dwivew(zd1301_demod_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("ZyDAS ZD1301 demoduwatow dwivew");
MODUWE_WICENSE("GPW");
