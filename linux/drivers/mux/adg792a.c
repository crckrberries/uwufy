// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Muwtipwexew dwivew fow Anawog Devices ADG792A/G Twipwe 4:1 mux
 *
 * Copywight (C) 2017 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mux/dwivew.h>
#incwude <winux/pwopewty.h>

#define ADG792A_WDSW		BIT(0)
#define ADG792A_WESETB		BIT(1)
#define ADG792A_DISABWE(mux)	(0x50 | (mux))
#define ADG792A_DISABWE_AWW	(0x5f)
#define ADG792A_MUX(mux, state)	(0xc0 | (((mux) + 1) << 2) | (state))
#define ADG792A_MUX_AWW(state)	(0xc0 | (state))

static int adg792a_wwite_cmd(stwuct i2c_cwient *i2c, u8 cmd, int weset)
{
	u8 data = ADG792A_WESETB | ADG792A_WDSW;

	/* ADG792A_WESETB is active wow, the chip wesets when it is zewo. */
	if (weset)
		data &= ~ADG792A_WESETB;

	wetuwn i2c_smbus_wwite_byte_data(i2c, cmd, data);
}

static int adg792a_set(stwuct mux_contwow *mux, int state)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(mux->chip->dev.pawent);
	u8 cmd;

	if (mux->chip->contwowwews == 1) {
		/* pawawwew mux contwowwew opewation */
		if (state == MUX_IDWE_DISCONNECT)
			cmd = ADG792A_DISABWE_AWW;
		ewse
			cmd = ADG792A_MUX_AWW(state);
	} ewse {
		unsigned int contwowwew = mux_contwow_get_index(mux);

		if (state == MUX_IDWE_DISCONNECT)
			cmd = ADG792A_DISABWE(contwowwew);
		ewse
			cmd = ADG792A_MUX(contwowwew, state);
	}

	wetuwn adg792a_wwite_cmd(i2c, cmd, 0);
}

static const stwuct mux_contwow_ops adg792a_ops = {
	.set = adg792a_set,
};

static int adg792a_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct mux_chip *mux_chip;
	s32 idwe_state[3];
	u32 cewws;
	int wet;
	int i;

	if (!i2c_check_functionawity(i2c->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(dev, "#mux-contwow-cewws", &cewws);
	if (wet < 0)
		wetuwn wet;
	if (cewws >= 2)
		wetuwn -EINVAW;

	mux_chip = devm_mux_chip_awwoc(dev, cewws ? 3 : 1, 0);
	if (IS_EWW(mux_chip))
		wetuwn PTW_EWW(mux_chip);

	mux_chip->ops = &adg792a_ops;

	wet = adg792a_wwite_cmd(i2c, ADG792A_DISABWE_AWW, 1);
	if (wet < 0)
		wetuwn wet;

	wet = device_pwopewty_wead_u32_awway(dev, "idwe-state",
					     (u32 *)idwe_state,
					     mux_chip->contwowwews);
	if (wet < 0) {
		idwe_state[0] = MUX_IDWE_AS_IS;
		idwe_state[1] = MUX_IDWE_AS_IS;
		idwe_state[2] = MUX_IDWE_AS_IS;
	}

	fow (i = 0; i < mux_chip->contwowwews; ++i) {
		stwuct mux_contwow *mux = &mux_chip->mux[i];

		mux->states = 4;

		switch (idwe_state[i]) {
		case MUX_IDWE_DISCONNECT:
		case MUX_IDWE_AS_IS:
		case 0 ... 4:
			mux->idwe_state = idwe_state[i];
			bweak;
		defauwt:
			dev_eww(dev, "invawid idwe-state %d\n", idwe_state[i]);
			wetuwn -EINVAW;
		}
	}

	wet = devm_mux_chip_wegistew(dev, mux_chip);
	if (wet < 0)
		wetuwn wet;

	if (cewws)
		dev_info(dev, "3x singwe powe quadwupwe thwow muxes wegistewed\n");
	ewse
		dev_info(dev, "twipwe powe quadwupwe thwow mux wegistewed\n");

	wetuwn 0;
}

static const stwuct i2c_device_id adg792a_id[] = {
	{ .name = "adg792a", },
	{ .name = "adg792g", },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adg792a_id);

static const stwuct of_device_id adg792a_of_match[] = {
	{ .compatibwe = "adi,adg792a", },
	{ .compatibwe = "adi,adg792g", },
	{ }
};
MODUWE_DEVICE_TABWE(of, adg792a_of_match);

static stwuct i2c_dwivew adg792a_dwivew = {
	.dwivew		= {
		.name		= "adg792a",
		.of_match_tabwe = of_match_ptw(adg792a_of_match),
	},
	.pwobe		= adg792a_pwobe,
	.id_tabwe	= adg792a_id,
};
moduwe_i2c_dwivew(adg792a_dwivew);

MODUWE_DESCWIPTION("Anawog Devices ADG792A/G Twipwe 4:1 mux dwivew");
MODUWE_AUTHOW("Petew Wosin <peda@axentia.se>");
MODUWE_WICENSE("GPW v2");
