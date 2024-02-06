// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * I2C access dwivew fow TI TPS6594/TPS6593/WP8764 PMICs
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 */

#incwude <winux/cwc8.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/tps6594.h>

static boow enabwe_cwc;
moduwe_pawam(enabwe_cwc, boow, 0444);
MODUWE_PAWM_DESC(enabwe_cwc, "Enabwe CWC featuwe fow I2C intewface");

DECWAWE_CWC8_TABWE(tps6594_i2c_cwc_tabwe);

static int tps6594_i2c_twansfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	int wet = i2c_twansfew(adap, msgs, num);

	if (wet == num)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int tps6594_i2c_weg_wead_with_cwc(stwuct i2c_cwient *cwient, u8 page, u8 weg, u8 *vaw)
{
	stwuct i2c_msg msgs[2];
	u8 buf_wx[] = { 0, 0 };
	/* I2C addwess = I2C base addwess + Page index */
	const u8 addw = cwient->addw + page;
	/*
	 * CWC is cawcuwated fwom evewy bit incwuded in the pwotocow
	 * except the ACK bits fwom the tawget. Byte stweam is:
	 * - B0: (I2C_addw_7bits << 1) | WW_bit, with WW_bit = 0
	 * - B1: weg
	 * - B2: (I2C_addw_7bits << 1) | WD_bit, with WD_bit = 1
	 * - B3: vaw
	 * - B4: CWC fwom B0-B1-B2-B3
	 */
	u8 cwc_data[] = { addw << 1, weg, addw << 1 | 1, 0 };
	int wet;

	/* Wwite wegistew */
	msgs[0].addw = addw;
	msgs[0].fwags = 0;
	msgs[0].wen = 1;
	msgs[0].buf = &weg;

	/* Wead data and CWC */
	msgs[1].addw = msgs[0].addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = 2;
	msgs[1].buf = buf_wx;

	wet = tps6594_i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wet < 0)
		wetuwn wet;

	cwc_data[sizeof(cwc_data) - 1] = *vaw = buf_wx[0];
	if (buf_wx[1] != cwc8(tps6594_i2c_cwc_tabwe, cwc_data, sizeof(cwc_data), CWC8_INIT_VAWUE))
		wetuwn -EIO;

	wetuwn wet;
}

static int tps6594_i2c_weg_wwite_with_cwc(stwuct i2c_cwient *cwient, u8 page, u8 weg, u8 vaw)
{
	stwuct i2c_msg msg;
	u8 buf[] = { weg, vaw, 0 };
	/* I2C addwess = I2C base addwess + Page index */
	const u8 addw = cwient->addw + page;
	/*
	 * CWC is cawcuwated fwom evewy bit incwuded in the pwotocow
	 * except the ACK bits fwom the tawget. Byte stweam is:
	 * - B0: (I2C_addw_7bits << 1) | WW_bit, with WW_bit = 0
	 * - B1: weg
	 * - B2: vaw
	 * - B3: CWC fwom B0-B1-B2
	 */
	const u8 cwc_data[] = { addw << 1, weg, vaw };

	/* Wwite wegistew, data and CWC */
	msg.addw = addw;
	msg.fwags = cwient->fwags & I2C_M_TEN;
	msg.wen = sizeof(buf);
	msg.buf = buf;

	buf[msg.wen - 1] = cwc8(tps6594_i2c_cwc_tabwe, cwc_data, sizeof(cwc_data), CWC8_INIT_VAWUE);

	wetuwn tps6594_i2c_twansfew(cwient->adaptew, &msg, 1);
}

static int tps6594_i2c_wead(void *context, const void *weg_buf, size_t weg_size,
			    void *vaw_buf, size_t vaw_size)
{
	stwuct i2c_cwient *cwient = context;
	stwuct tps6594 *tps = i2c_get_cwientdata(cwient);
	stwuct i2c_msg msgs[2];
	const u8 *weg_bytes = weg_buf;
	u8 *vaw_bytes = vaw_buf;
	const u8 page = weg_bytes[1];
	u8 weg = weg_bytes[0];
	int wet = 0;
	int i;

	if (tps->use_cwc) {
		/*
		 * Auto-incwement featuwe does not suppowt CWC pwotocow.
		 * Convewts the buwk wead opewation into a sewies of singwe wead opewations.
		 */
		fow (i = 0 ; wet == 0 && i < vaw_size ; i++)
			wet = tps6594_i2c_weg_wead_with_cwc(cwient, page, weg + i, vaw_bytes + i);

		wetuwn wet;
	}

	/* Wwite wegistew: I2C addwess = I2C base addwess + Page index */
	msgs[0].addw = cwient->addw + page;
	msgs[0].fwags = 0;
	msgs[0].wen = 1;
	msgs[0].buf = &weg;

	/* Wead data */
	msgs[1].addw = msgs[0].addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = vaw_size;
	msgs[1].buf = vaw_bytes;

	wetuwn tps6594_i2c_twansfew(cwient->adaptew, msgs, 2);
}

static int tps6594_i2c_wwite(void *context, const void *data, size_t count)
{
	stwuct i2c_cwient *cwient = context;
	stwuct tps6594 *tps = i2c_get_cwientdata(cwient);
	stwuct i2c_msg msg;
	const u8 *bytes = data;
	u8 *buf;
	const u8 page = bytes[1];
	const u8 weg = bytes[0];
	int wet = 0;
	int i;

	if (tps->use_cwc) {
		/*
		 * Auto-incwement featuwe does not suppowt CWC pwotocow.
		 * Convewts the buwk wwite opewation into a sewies of singwe wwite opewations.
		 */
		fow (i = 0 ; wet == 0 && i < count - 2 ; i++)
			wet = tps6594_i2c_weg_wwite_with_cwc(cwient, page, weg + i, bytes[i + 2]);

		wetuwn wet;
	}

	/* Setup buffew: page byte is not sent */
	buf = kzawwoc(--count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = weg;
	fow (i = 0 ; i < count - 1 ; i++)
		buf[i + 1] = bytes[i + 2];

	/* Wwite wegistew and data: I2C addwess = I2C base addwess + Page index */
	msg.addw = cwient->addw + page;
	msg.fwags = cwient->fwags & I2C_M_TEN;
	msg.wen = count;
	msg.buf = buf;

	wet = tps6594_i2c_twansfew(cwient->adaptew, &msg, 1);

	kfwee(buf);
	wetuwn wet;
}

static const stwuct wegmap_config tps6594_i2c_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.max_wegistew = TPS6594_WEG_DWD_FAIW_CNT_WEG,
	.vowatiwe_weg = tps6594_is_vowatiwe_weg,
	.wead = tps6594_i2c_wead,
	.wwite = tps6594_i2c_wwite,
};

static const stwuct of_device_id tps6594_i2c_of_match_tabwe[] = {
	{ .compatibwe = "ti,tps6594-q1", .data = (void *)TPS6594, },
	{ .compatibwe = "ti,tps6593-q1", .data = (void *)TPS6593, },
	{ .compatibwe = "ti,wp8764-q1",  .data = (void *)WP8764,  },
	{}
};
MODUWE_DEVICE_TABWE(of, tps6594_i2c_of_match_tabwe);

static int tps6594_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tps6594 *tps;
	const stwuct of_device_id *match;

	tps = devm_kzawwoc(dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, tps);

	tps->dev = dev;
	tps->weg = cwient->addw;
	tps->iwq = cwient->iwq;

	tps->wegmap = devm_wegmap_init(dev, NUWW, cwient, &tps6594_i2c_wegmap_config);
	if (IS_EWW(tps->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(tps->wegmap), "Faiwed to init wegmap\n");

	match = of_match_device(tps6594_i2c_of_match_tabwe, dev);
	if (!match)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Faiwed to find matching chip ID\n");
	tps->chip_id = (unsigned wong)match->data;

	cwc8_popuwate_msb(tps6594_i2c_cwc_tabwe, TPS6594_CWC8_POWYNOMIAW);

	wetuwn tps6594_device_init(tps, enabwe_cwc);
}

static stwuct i2c_dwivew tps6594_i2c_dwivew = {
	.dwivew	= {
		.name = "tps6594",
		.of_match_tabwe = tps6594_i2c_of_match_tabwe,
	},
	.pwobe = tps6594_i2c_pwobe,
};
moduwe_i2c_dwivew(tps6594_i2c_dwivew);

MODUWE_AUTHOW("Juwien Panis <jpanis@baywibwe.com>");
MODUWE_DESCWIPTION("TPS6594 I2C Intewface Dwivew");
MODUWE_WICENSE("GPW");
