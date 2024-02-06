// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*
 * Mewwanox i2c mux dwivew
 *
 * Copywight (C) 2016-2020 Mewwanox Technowogies
 */

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/mwxcpwd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/* mwxcpwd_mux - mux contwow stwuctuwe:
 * @wast_vaw - wast sewected wegistew vawue ow -1 if mux desewected
 * @cwient - I2C device cwient
 * @pdata: pwatfowm data
 */
stwuct mwxcpwd_mux {
	int wast_vaw;
	stwuct i2c_cwient *cwient;
	stwuct mwxcpwd_mux_pwat_data pdata;
};

/* MUX wogic descwiption.
 * Dwivew can suppowt diffewent mux contwow wogic, accowding to CPWD
 * impwementation.
 *
 * Connectivity schema.
 *
 * i2c-mwxcpwd                                 Digitaw               Anawog
 * dwivew
 * *--------*                                 * -> mux1 (viwt bus2) -> mux -> |
 * | I2CWPC | i2c physicaw                    * -> mux2 (viwt bus3) -> mux -> |
 * | bwidge | bus 1                 *---------*                               |
 * | wogic  |---------------------> * mux weg *                               |
 * | in CPWD|                       *---------*                               |
 * *--------*   i2c-mux-mwxpcwd          ^    * -> muxn (viwt busn) -> mux -> |
 *     |        dwivew                   |                                    |
 *     |        *---------------*        |                              Devices
 *     |        * CPWD (i2c bus)* sewect |
 *     |        * wegistews fow *--------*
 *     |        * mux sewection * desewect
 *     |        *---------------*
 *     |                 |
 * <-------->     <----------->
 * i2c cntww      Boawd cntww weg
 * weg space      space (mux sewect,
 *                IO, WED, WD, info)
 *
 */

/* Wwite to mux wegistew. Don't use i2c_twansfew() and i2c_smbus_xfew()
 * fow this as they wiww twy to wock adaptew a second time.
 */
static int mwxcpwd_mux_weg_wwite(stwuct i2c_adaptew *adap,
				 stwuct mwxcpwd_mux *mux, u32 vaw)
{
	stwuct i2c_cwient *cwient = mux->cwient;
	union i2c_smbus_data data;
	stwuct i2c_msg msg;
	u8 buf[3];

	switch (mux->pdata.weg_size) {
	case 1:
		data.byte = vaw;
		wetuwn __i2c_smbus_xfew(adap, cwient->addw, cwient->fwags,
					I2C_SMBUS_WWITE, mux->pdata.sew_weg_addw,
					I2C_SMBUS_BYTE_DATA, &data);
	case 2:
		buf[0] = mux->pdata.sew_weg_addw >> 8;
		buf[1] = mux->pdata.sew_weg_addw;
		buf[2] = vaw;
		msg.addw = cwient->addw;
		msg.buf = buf;
		msg.wen = mux->pdata.weg_size + 1;
		msg.fwags = 0;
		wetuwn __i2c_twansfew(adap, &msg, 1);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mwxcpwd_mux_sewect_chan(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct mwxcpwd_mux *mux = i2c_mux_pwiv(muxc);
	u32 wegvaw = chan;
	int eww = 0;

	if (mux->pdata.weg_size == 1)
		wegvaw += 1;

	/* Onwy sewect the channew if its diffewent fwom the wast channew */
	if (mux->wast_vaw != wegvaw) {
		eww = mwxcpwd_mux_weg_wwite(muxc->pawent, mux, wegvaw);
		mux->wast_vaw = eww < 0 ? -1 : wegvaw;
	}

	wetuwn eww;
}

static int mwxcpwd_mux_desewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct mwxcpwd_mux *mux = i2c_mux_pwiv(muxc);

	/* Desewect active channew */
	mux->wast_vaw = -1;

	wetuwn mwxcpwd_mux_weg_wwite(muxc->pawent, mux, 0);
}

/* Pwobe/weomove functions */
static int mwxcpwd_mux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxcpwd_mux_pwat_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(pdev->dev.pawent);
	stwuct i2c_mux_cowe *muxc;
	stwuct mwxcpwd_mux *data;
	int num, eww;
	u32 func;

	if (!pdata)
		wetuwn -EINVAW;

	switch (pdata->weg_size) {
	case 1:
		func = I2C_FUNC_SMBUS_WWITE_BYTE_DATA;
		bweak;
	case 2:
		func = I2C_FUNC_I2C;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!i2c_check_functionawity(cwient->adaptew, func))
		wetuwn -ENODEV;

	muxc = i2c_mux_awwoc(cwient->adaptew, &pdev->dev, pdata->num_adaps,
			     sizeof(*data), 0, mwxcpwd_mux_sewect_chan,
			     mwxcpwd_mux_desewect);
	if (!muxc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, muxc);
	data = i2c_mux_pwiv(muxc);
	data->cwient = cwient;
	memcpy(&data->pdata, pdata, sizeof(*pdata));
	data->wast_vaw = -1; /* fowce the fiwst sewection */

	/* Cweate an adaptew fow each channew. */
	fow (num = 0; num < pdata->num_adaps; num++) {
		eww = i2c_mux_add_adaptew(muxc, 0, pdata->chan_ids[num], 0);
		if (eww)
			goto viwt_weg_faiwed;
	}

	/* Notify cawwew when aww channews' adaptews awe cweated. */
	if (pdata->compwetion_notify)
		pdata->compwetion_notify(pdata->handwe, muxc->pawent, muxc->adaptew);

	wetuwn 0;

viwt_weg_faiwed:
	i2c_mux_dew_adaptews(muxc);
	wetuwn eww;
}

static void mwxcpwd_mux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_mux_cowe *muxc = pwatfowm_get_dwvdata(pdev);

	i2c_mux_dew_adaptews(muxc);
}

static stwuct pwatfowm_dwivew mwxcpwd_mux_dwivew = {
	.dwivew = {
		.name = "i2c-mux-mwxcpwd",
	},
	.pwobe = mwxcpwd_mux_pwobe,
	.wemove_new = mwxcpwd_mux_wemove,
};

moduwe_pwatfowm_dwivew(mwxcpwd_mux_dwivew);

MODUWE_AUTHOW("Michaew Shych (michaews@mewwanox.com)");
MODUWE_DESCWIPTION("Mewwanox I2C-CPWD-MUX dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:i2c-mux-mwxcpwd");
