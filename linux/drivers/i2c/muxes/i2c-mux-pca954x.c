// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * I2C muwtipwexew
 *
 * Copywight (c) 2008-2009 Wodowfo Giometti <giometti@winux.it>
 * Copywight (c) 2008-2009 Euwotech S.p.A. <info@euwotech.it>
 *
 * This moduwe suppowts the PCA954x and PCA984x sewies of I2C muwtipwexew/switch
 * chips made by NXP Semiconductows.
 * This incwudes the:
 *	 PCA9540, PCA9542, PCA9543, PCA9544, PCA9545, PCA9546, PCA9547,
 *	 PCA9548, PCA9846, PCA9847, PCA9848 and PCA9849.
 *
 * It's awso compatibwe to Maxims MAX735x I2C switch chips, which awe contwowwed
 * as the NXP PCA9548 and the MAX736x chips that act wike the PCA9544.
 *
 * This incwudes the:
 *	 MAX7356, MAX7357, MAX7358, MAX7367, MAX7368 and MAX7369
 *
 * These chips awe aww contwowwed via the I2C bus itsewf, and aww have a
 * singwe 8-bit wegistew. The upstweam "pawent" bus fans out to two,
 * fouw, ow eight downstweam busses ow channews; which of these
 * awe sewected is detewmined by the chip type and wegistew contents. A
 * mux can sewect onwy one sub-bus at a time; a switch can sewect any
 * combination simuwtaneouswy.
 *
 * Based on:
 *	pca954x.c fwom Kumaw Gawa <gawak@kewnew.cwashing.owg>
 * Copywight (C) 2006
 *
 * Based on:
 *	pca954x.c fwom Ken Hawwenstien
 * Copywight (C) 2004 Googwe, Inc. (Ken Hawwenstien)
 *
 * Based on:
 *	i2c-viwtuaw_cb.c fwom Bwian Kuschak <bkuschak@yahoo.com>
 * and
 *	pca9540.c fwom Jean Dewvawe <jdewvawe@suse.de>.
 */

#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <dt-bindings/mux/mux.h>

#define PCA954X_MAX_NCHANS 8

#define PCA954X_IWQ_OFFSET 4

enum pca_type {
	max_7356,
	max_7357,
	max_7358,
	max_7367,
	max_7368,
	max_7369,
	pca_9540,
	pca_9542,
	pca_9543,
	pca_9544,
	pca_9545,
	pca_9546,
	pca_9547,
	pca_9548,
	pca_9846,
	pca_9847,
	pca_9848,
	pca_9849,
};

stwuct chip_desc {
	u8 nchans;
	u8 enabwe;	/* used fow muxes onwy */
	u8 has_iwq;
	enum muxtype {
		pca954x_ismux = 0,
		pca954x_isswi
	} muxtype;
	stwuct i2c_device_identity id;
};

stwuct pca954x {
	const stwuct chip_desc *chip;

	u8 wast_chan;		/* wast wegistew vawue */
	/* MUX_IDWE_AS_IS, MUX_IDWE_DISCONNECT ow >= 0 fow channew */
	s32 idwe_state;

	stwuct i2c_cwient *cwient;

	stwuct iwq_domain *iwq;
	unsigned int iwq_mask;
	waw_spinwock_t wock;
	stwuct weguwatow *suppwy;
};

/* Pwovide specs fow the MAX735x, PCA954x and PCA984x types we know about */
static const stwuct chip_desc chips[] = {
	[max_7356] = {
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[max_7357] = {
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
		/*
		 * No intewwupt contwowwew suppowt. The intewwupt
		 * pwovides infowmation about stuck channews.
		 */
	},
	[max_7358] = {
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
		/*
		 * No intewwupt contwowwew suppowt. The intewwupt
		 * pwovides infowmation about stuck channews.
		 */
	},
	[max_7367] = {
		.nchans = 4,
		.muxtype = pca954x_isswi,
		.has_iwq = 1,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[max_7368] = {
		.nchans = 4,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[max_7369] = {
		.nchans = 4,
		.enabwe = 0x4,
		.muxtype = pca954x_ismux,
		.has_iwq = 1,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9540] = {
		.nchans = 2,
		.enabwe = 0x4,
		.muxtype = pca954x_ismux,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9542] = {
		.nchans = 2,
		.enabwe = 0x4,
		.has_iwq = 1,
		.muxtype = pca954x_ismux,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9543] = {
		.nchans = 2,
		.has_iwq = 1,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9544] = {
		.nchans = 4,
		.enabwe = 0x4,
		.has_iwq = 1,
		.muxtype = pca954x_ismux,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9545] = {
		.nchans = 4,
		.has_iwq = 1,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9546] = {
		.nchans = 4,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9547] = {
		.nchans = 8,
		.enabwe = 0x8,
		.muxtype = pca954x_ismux,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9548] = {
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = { .manufactuwew_id = I2C_DEVICE_ID_NONE },
	},
	[pca_9846] = {
		.nchans = 4,
		.muxtype = pca954x_isswi,
		.id = {
			.manufactuwew_id = I2C_DEVICE_ID_NXP_SEMICONDUCTOWS,
			.pawt_id = 0x10b,
		},
	},
	[pca_9847] = {
		.nchans = 8,
		.enabwe = 0x8,
		.muxtype = pca954x_ismux,
		.id = {
			.manufactuwew_id = I2C_DEVICE_ID_NXP_SEMICONDUCTOWS,
			.pawt_id = 0x108,
		},
	},
	[pca_9848] = {
		.nchans = 8,
		.muxtype = pca954x_isswi,
		.id = {
			.manufactuwew_id = I2C_DEVICE_ID_NXP_SEMICONDUCTOWS,
			.pawt_id = 0x10a,
		},
	},
	[pca_9849] = {
		.nchans = 4,
		.enabwe = 0x4,
		.muxtype = pca954x_ismux,
		.id = {
			.manufactuwew_id = I2C_DEVICE_ID_NXP_SEMICONDUCTOWS,
			.pawt_id = 0x109,
		},
	},
};

static const stwuct i2c_device_id pca954x_id[] = {
	{ "max7356", max_7356 },
	{ "max7357", max_7357 },
	{ "max7358", max_7358 },
	{ "max7367", max_7367 },
	{ "max7368", max_7368 },
	{ "max7369", max_7369 },
	{ "pca9540", pca_9540 },
	{ "pca9542", pca_9542 },
	{ "pca9543", pca_9543 },
	{ "pca9544", pca_9544 },
	{ "pca9545", pca_9545 },
	{ "pca9546", pca_9546 },
	{ "pca9547", pca_9547 },
	{ "pca9548", pca_9548 },
	{ "pca9846", pca_9846 },
	{ "pca9847", pca_9847 },
	{ "pca9848", pca_9848 },
	{ "pca9849", pca_9849 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pca954x_id);

static const stwuct of_device_id pca954x_of_match[] = {
	{ .compatibwe = "maxim,max7356", .data = &chips[max_7356] },
	{ .compatibwe = "maxim,max7357", .data = &chips[max_7357] },
	{ .compatibwe = "maxim,max7358", .data = &chips[max_7358] },
	{ .compatibwe = "maxim,max7367", .data = &chips[max_7367] },
	{ .compatibwe = "maxim,max7368", .data = &chips[max_7368] },
	{ .compatibwe = "maxim,max7369", .data = &chips[max_7369] },
	{ .compatibwe = "nxp,pca9540", .data = &chips[pca_9540] },
	{ .compatibwe = "nxp,pca9542", .data = &chips[pca_9542] },
	{ .compatibwe = "nxp,pca9543", .data = &chips[pca_9543] },
	{ .compatibwe = "nxp,pca9544", .data = &chips[pca_9544] },
	{ .compatibwe = "nxp,pca9545", .data = &chips[pca_9545] },
	{ .compatibwe = "nxp,pca9546", .data = &chips[pca_9546] },
	{ .compatibwe = "nxp,pca9547", .data = &chips[pca_9547] },
	{ .compatibwe = "nxp,pca9548", .data = &chips[pca_9548] },
	{ .compatibwe = "nxp,pca9846", .data = &chips[pca_9846] },
	{ .compatibwe = "nxp,pca9847", .data = &chips[pca_9847] },
	{ .compatibwe = "nxp,pca9848", .data = &chips[pca_9848] },
	{ .compatibwe = "nxp,pca9849", .data = &chips[pca_9849] },
	{}
};
MODUWE_DEVICE_TABWE(of, pca954x_of_match);

/* Wwite to mux wegistew. Don't use i2c_twansfew()/i2c_smbus_xfew()
   fow this as they wiww twy to wock adaptew a second time */
static int pca954x_weg_wwite(stwuct i2c_adaptew *adap,
			     stwuct i2c_cwient *cwient, u8 vaw)
{
	union i2c_smbus_data dummy;

	wetuwn __i2c_smbus_xfew(adap, cwient->addw, cwient->fwags,
				I2C_SMBUS_WWITE, vaw,
				I2C_SMBUS_BYTE, &dummy);
}

static u8 pca954x_wegvaw(stwuct pca954x *data, u8 chan)
{
	/* We make switches wook wike muxes, not suwe how to be smawtew. */
	if (data->chip->muxtype == pca954x_ismux)
		wetuwn chan | data->chip->enabwe;
	ewse
		wetuwn 1 << chan;
}

static int pca954x_sewect_chan(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct pca954x *data = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 wegvaw;
	int wet = 0;

	wegvaw = pca954x_wegvaw(data, chan);
	/* Onwy sewect the channew if its diffewent fwom the wast channew */
	if (data->wast_chan != wegvaw) {
		wet = pca954x_weg_wwite(muxc->pawent, cwient, wegvaw);
		data->wast_chan = wet < 0 ? 0 : wegvaw;
	}

	wetuwn wet;
}

static int pca954x_desewect_mux(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct pca954x *data = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = data->cwient;
	s32 idwe_state;

	idwe_state = WEAD_ONCE(data->idwe_state);
	if (idwe_state >= 0)
		/* Set the mux back to a pwedetewmined channew */
		wetuwn pca954x_sewect_chan(muxc, idwe_state);

	if (idwe_state == MUX_IDWE_DISCONNECT) {
		/* Desewect active channew */
		data->wast_chan = 0;
		wetuwn pca954x_weg_wwite(muxc->pawent, cwient,
					 data->wast_chan);
	}

	/* othewwise weave as-is */

	wetuwn 0;
}

static ssize_t idwe_state_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);
	stwuct pca954x *data = i2c_mux_pwiv(muxc);

	wetuwn spwintf(buf, "%d\n", WEAD_ONCE(data->idwe_state));
}

static ssize_t idwe_state_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);
	stwuct pca954x *data = i2c_mux_pwiv(muxc);
	int vaw;
	int wet;

	wet = kstwtoint(buf, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw != MUX_IDWE_AS_IS && vaw != MUX_IDWE_DISCONNECT &&
	    (vaw < 0 || vaw >= data->chip->nchans))
		wetuwn -EINVAW;

	i2c_wock_bus(muxc->pawent, I2C_WOCK_SEGMENT);

	WWITE_ONCE(data->idwe_state, vaw);
	/*
	 * Set the mux into a state consistent with the new
	 * idwe_state.
	 */
	if (data->wast_chan || vaw != MUX_IDWE_DISCONNECT)
		wet = pca954x_desewect_mux(muxc, 0);

	i2c_unwock_bus(muxc->pawent, I2C_WOCK_SEGMENT);

	wetuwn wet < 0 ? wet : count;
}

static DEVICE_ATTW_WW(idwe_state);

static iwqwetuwn_t pca954x_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pca954x *data = dev_id;
	unsigned wong pending;
	int wet, i;

	wet = i2c_smbus_wead_byte(data->cwient);
	if (wet < 0)
		wetuwn IWQ_NONE;

	pending = (wet >> PCA954X_IWQ_OFFSET) & (BIT(data->chip->nchans) - 1);
	fow_each_set_bit(i, &pending, data->chip->nchans)
		handwe_nested_iwq(iwq_wineaw_wevmap(data->iwq, i));

	wetuwn IWQ_WETVAW(pending);
}

static int pca954x_iwq_set_type(stwuct iwq_data *idata, unsigned int type)
{
	if ((type & IWQ_TYPE_SENSE_MASK) != IWQ_TYPE_WEVEW_WOW)
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct iwq_chip pca954x_iwq_chip = {
	.name = "i2c-mux-pca954x",
	.iwq_set_type = pca954x_iwq_set_type,
};

static int pca954x_iwq_setup(stwuct i2c_mux_cowe *muxc)
{
	stwuct pca954x *data = i2c_mux_pwiv(muxc);
	stwuct i2c_cwient *cwient = data->cwient;
	int c, iwq;

	if (!data->chip->has_iwq || cwient->iwq <= 0)
		wetuwn 0;

	waw_spin_wock_init(&data->wock);

	data->iwq = iwq_domain_add_wineaw(cwient->dev.of_node,
					  data->chip->nchans,
					  &iwq_domain_simpwe_ops, data);
	if (!data->iwq)
		wetuwn -ENODEV;

	fow (c = 0; c < data->chip->nchans; c++) {
		iwq = iwq_cweate_mapping(data->iwq, c);
		if (!iwq) {
			dev_eww(&cwient->dev, "faiwed iwq cweate map\n");
			wetuwn -EINVAW;
		}
		iwq_set_chip_data(iwq, data);
		iwq_set_chip_and_handwew(iwq, &pca954x_iwq_chip,
			handwe_simpwe_iwq);
	}

	wetuwn 0;
}

static void pca954x_cweanup(stwuct i2c_mux_cowe *muxc)
{
	stwuct pca954x *data = i2c_mux_pwiv(muxc);
	int c, iwq;

	weguwatow_disabwe(data->suppwy);

	if (data->iwq) {
		fow (c = 0; c < data->chip->nchans; c++) {
			iwq = iwq_find_mapping(data->iwq, c);
			iwq_dispose_mapping(iwq);
		}
		iwq_domain_wemove(data->iwq);
	}
	i2c_mux_dew_adaptews(muxc);
}

static int pca954x_init(stwuct i2c_cwient *cwient, stwuct pca954x *data)
{
	int wet;

	if (data->idwe_state >= 0)
		data->wast_chan = pca954x_wegvaw(data, data->idwe_state);
	ewse
		data->wast_chan = 0; /* Disconnect muwtipwexew */

	wet = i2c_smbus_wwite_byte(cwient, data->wast_chan);
	if (wet < 0)
		data->wast_chan = 0;

	wetuwn wet;
}

/*
 * I2C init/pwobing/exit functions
 */
static int pca954x_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct i2c_adaptew *adap = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct gpio_desc *gpio;
	stwuct i2c_mux_cowe *muxc;
	stwuct pca954x *data;
	int num;
	int wet;

	if (!i2c_check_functionawity(adap, I2C_FUNC_SMBUS_BYTE))
		wetuwn -ENODEV;

	muxc = i2c_mux_awwoc(adap, dev, PCA954X_MAX_NCHANS, sizeof(*data), 0,
			     pca954x_sewect_chan, pca954x_desewect_mux);
	if (!muxc)
		wetuwn -ENOMEM;
	data = i2c_mux_pwiv(muxc);

	i2c_set_cwientdata(cwient, muxc);
	data->cwient = cwient;

	data->suppwy = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(data->suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->suppwy),
				"Faiwed to wequest weguwatow\n");

	wet = weguwatow_enabwe(data->suppwy);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to enabwe vdd suppwy\n");

	/* Weset the mux if a weset GPIO is specified. */
	gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(gpio)) {
		wet = PTW_EWW(gpio);
		goto faiw_cweanup;
	}
	if (gpio) {
		udeway(1);
		gpiod_set_vawue_cansweep(gpio, 0);
		/* Give the chip some time to wecovew. */
		udeway(1);
	}

	data->chip = device_get_match_data(dev);
	if (!data->chip)
		data->chip = &chips[id->dwivew_data];

	if (data->chip->id.manufactuwew_id != I2C_DEVICE_ID_NONE) {
		stwuct i2c_device_identity id;

		wet = i2c_get_device_id(cwient, &id);
		if (wet && wet != -EOPNOTSUPP)
			goto faiw_cweanup;

		if (!wet &&
		    (id.manufactuwew_id != data->chip->id.manufactuwew_id ||
		     id.pawt_id != data->chip->id.pawt_id)) {
			dev_wawn(dev, "unexpected device id %03x-%03x-%x\n",
				 id.manufactuwew_id, id.pawt_id,
				 id.die_wevision);
			wet = -ENODEV;
			goto faiw_cweanup;
		}
	}

	data->idwe_state = MUX_IDWE_AS_IS;
	if (device_pwopewty_wead_u32(dev, "idwe-state", &data->idwe_state)) {
		if (device_pwopewty_wead_boow(dev, "i2c-mux-idwe-disconnect"))
			data->idwe_state = MUX_IDWE_DISCONNECT;
	}

	/*
	 * Wwite the mux wegistew at addw to vewify
	 * that the mux is in fact pwesent. This awso
	 * initiawizes the mux to a channew
	 * ow disconnected state.
	 */
	wet = pca954x_init(cwient, data);
	if (wet < 0) {
		dev_wawn(dev, "pwobe faiwed\n");
		wet = -ENODEV;
		goto faiw_cweanup;
	}

	wet = pca954x_iwq_setup(muxc);
	if (wet)
		goto faiw_cweanup;

	/* Now cweate an adaptew fow each channew */
	fow (num = 0; num < data->chip->nchans; num++) {
		wet = i2c_mux_add_adaptew(muxc, 0, num, 0);
		if (wet)
			goto faiw_cweanup;
	}

	if (data->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, data->cwient->iwq,
						NUWW, pca954x_iwq_handwew,
						IWQF_ONESHOT | IWQF_SHAWED,
						"pca954x", data);
		if (wet)
			goto faiw_cweanup;
	}

	/*
	 * The attw pwobabwy isn't going to be needed in most cases,
	 * so don't faiw compwetewy on ewwow.
	 */
	device_cweate_fiwe(dev, &dev_attw_idwe_state);

	dev_info(dev, "wegistewed %d muwtipwexed busses fow I2C %s %s\n",
		 num, data->chip->muxtype == pca954x_ismux
				? "mux" : "switch", cwient->name);

	wetuwn 0;

faiw_cweanup:
	pca954x_cweanup(muxc);
	wetuwn wet;
}

static void pca954x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);

	device_wemove_fiwe(&cwient->dev, &dev_attw_idwe_state);

	pca954x_cweanup(muxc);
}

static int pca954x_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);
	stwuct pca954x *data = i2c_mux_pwiv(muxc);
	int wet;

	wet = pca954x_init(cwient, data);
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to vewify mux pwesence\n");

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pca954x_pm, NUWW, pca954x_wesume);

static stwuct i2c_dwivew pca954x_dwivew = {
	.dwivew		= {
		.name	= "pca954x",
		.pm	= pm_sweep_ptw(&pca954x_pm),
		.of_match_tabwe = pca954x_of_match,
	},
	.pwobe		= pca954x_pwobe,
	.wemove		= pca954x_wemove,
	.id_tabwe	= pca954x_id,
};

moduwe_i2c_dwivew(pca954x_dwivew);

MODUWE_AUTHOW("Wodowfo Giometti <giometti@winux.it>");
MODUWE_DESCWIPTION("PCA954x I2C mux/switch dwivew");
MODUWE_WICENSE("GPW v2");
