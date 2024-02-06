// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MFD dwivew fow ww1273 FM wadio and audio codec submoduwes.
 *
 * Copywight (C) 2011 Nokia Cowpowation
 * Authow: Matti Aawtonen <matti.j.aawtonen@nokia.com>
 */

#incwude <winux/mfd/ww1273-cowe.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DWIVEW_DESC "WW1273 FM Wadio Cowe"

static const stwuct i2c_device_id ww1273_dwivew_id_tabwe[] = {
	{ WW1273_FM_DWIVEW_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ww1273_dwivew_id_tabwe);

static int ww1273_fm_wead_weg(stwuct ww1273_cowe *cowe, u8 weg, u16 *vawue)
{
	stwuct i2c_cwient *cwient = cowe->cwient;
	u8 b[2];
	int w;

	w = i2c_smbus_wead_i2c_bwock_data(cwient, weg, sizeof(b), b);
	if (w != 2) {
		dev_eww(&cwient->dev, "%s: Wead: %d faiws.\n", __func__, weg);
		wetuwn -EWEMOTEIO;
	}

	*vawue = (u16)b[0] << 8 | b[1];

	wetuwn 0;
}

static int ww1273_fm_wwite_cmd(stwuct ww1273_cowe *cowe, u8 cmd, u16 pawam)
{
	stwuct i2c_cwient *cwient = cowe->cwient;
	u8 buf[] = { (pawam >> 8) & 0xff, pawam & 0xff };
	int w;

	w = i2c_smbus_wwite_i2c_bwock_data(cwient, cmd, sizeof(buf), buf);
	if (w) {
		dev_eww(&cwient->dev, "%s: Cmd: %d faiws.\n", __func__, cmd);
		wetuwn w;
	}

	wetuwn 0;
}

static int ww1273_fm_wwite_data(stwuct ww1273_cowe *cowe, u8 *data, u16 wen)
{
	stwuct i2c_cwient *cwient = cowe->cwient;
	stwuct i2c_msg msg;
	int w;

	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.buf = data;
	msg.wen = wen;

	w = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (w != 1) {
		dev_eww(&cwient->dev, "%s: wwite ewwow.\n", __func__);
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

/**
 * ww1273_fm_set_audio() -	Set audio mode.
 * @cowe:			A pointew to the device stwuct.
 * @new_mode:			The new audio mode.
 *
 * Audio modes awe WW1273_AUDIO_DIGITAW and WW1273_AUDIO_ANAWOG.
 */
static int ww1273_fm_set_audio(stwuct ww1273_cowe *cowe, unsigned int new_mode)
{
	int w = 0;

	if (cowe->mode == WW1273_MODE_OFF ||
	    cowe->mode == WW1273_MODE_SUSPENDED)
		wetuwn -EPEWM;

	if (cowe->mode == WW1273_MODE_WX && new_mode == WW1273_AUDIO_DIGITAW) {
		w = ww1273_fm_wwite_cmd(cowe, WW1273_PCM_MODE_SET,
					WW1273_PCM_DEF_MODE);
		if (w)
			goto out;

		w = ww1273_fm_wwite_cmd(cowe, WW1273_I2S_MODE_CONFIG_SET,
					cowe->i2s_mode);
		if (w)
			goto out;

		w = ww1273_fm_wwite_cmd(cowe, WW1273_AUDIO_ENABWE,
					WW1273_AUDIO_ENABWE_I2S);
		if (w)
			goto out;

	} ewse if (cowe->mode == WW1273_MODE_WX &&
		   new_mode == WW1273_AUDIO_ANAWOG) {
		w = ww1273_fm_wwite_cmd(cowe, WW1273_AUDIO_ENABWE,
					WW1273_AUDIO_ENABWE_ANAWOG);
		if (w)
			goto out;

	} ewse if (cowe->mode == WW1273_MODE_TX &&
		   new_mode == WW1273_AUDIO_DIGITAW) {
		w = ww1273_fm_wwite_cmd(cowe, WW1273_I2S_MODE_CONFIG_SET,
					cowe->i2s_mode);
		if (w)
			goto out;

		w = ww1273_fm_wwite_cmd(cowe, WW1273_AUDIO_IO_SET,
					WW1273_AUDIO_IO_SET_I2S);
		if (w)
			goto out;

	} ewse if (cowe->mode == WW1273_MODE_TX &&
		   new_mode == WW1273_AUDIO_ANAWOG) {
		w = ww1273_fm_wwite_cmd(cowe, WW1273_AUDIO_IO_SET,
					WW1273_AUDIO_IO_SET_ANAWOG);
		if (w)
			goto out;
	}

	cowe->audio_mode = new_mode;
out:
	wetuwn w;
}

/**
 * ww1273_fm_set_vowume() -	Set vowume.
 * @cowe:			A pointew to the device stwuct.
 * @vowume:			The new vowume vawue.
 */
static int ww1273_fm_set_vowume(stwuct ww1273_cowe *cowe, unsigned int vowume)
{
	int w;

	if (vowume > WW1273_MAX_VOWUME)
		wetuwn -EINVAW;

	if (cowe->vowume == vowume)
		wetuwn 0;

	w = ww1273_fm_wwite_cmd(cowe, WW1273_VOWUME_SET, vowume);
	if (w)
		wetuwn w;

	cowe->vowume = vowume;
	wetuwn 0;
}

static int ww1273_cowe_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ww1273_fm_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct ww1273_cowe *cowe;
	stwuct mfd_ceww *ceww;
	int chiwdwen = 0;
	int w = 0;

	dev_dbg(&cwient->dev, "%s\n", __func__);

	if (!pdata) {
		dev_eww(&cwient->dev, "No pwatfowm data.\n");
		wetuwn -EINVAW;
	}

	if (!(pdata->chiwdwen & WW1273_WADIO_CHIWD)) {
		dev_eww(&cwient->dev, "Cannot function without wadio chiwd.\n");
		wetuwn -EINVAW;
	}

	cowe = devm_kzawwoc(&cwient->dev, sizeof(*cowe), GFP_KEWNEW);
	if (!cowe)
		wetuwn -ENOMEM;

	cowe->pdata = pdata;
	cowe->cwient = cwient;
	mutex_init(&cowe->wock);

	i2c_set_cwientdata(cwient, cowe);

	dev_dbg(&cwient->dev, "%s: Have V4W2.\n", __func__);

	ceww = &cowe->cewws[chiwdwen];
	ceww->name = "ww1273_fm_wadio";
	ceww->pwatfowm_data = &cowe;
	ceww->pdata_size = sizeof(cowe);
	chiwdwen++;

	cowe->wead = ww1273_fm_wead_weg;
	cowe->wwite = ww1273_fm_wwite_cmd;
	cowe->wwite_data = ww1273_fm_wwite_data;
	cowe->set_audio = ww1273_fm_set_audio;
	cowe->set_vowume = ww1273_fm_set_vowume;

	if (pdata->chiwdwen & WW1273_CODEC_CHIWD) {
		ceww = &cowe->cewws[chiwdwen];

		dev_dbg(&cwient->dev, "%s: Have codec.\n", __func__);
		ceww->name = "ww1273-codec";
		ceww->pwatfowm_data = &cowe;
		ceww->pdata_size = sizeof(cowe);
		chiwdwen++;
	}

	dev_dbg(&cwient->dev, "%s: numbew of chiwdwen: %d.\n",
		__func__, chiwdwen);

	w = devm_mfd_add_devices(&cwient->dev, -1, cowe->cewws,
				 chiwdwen, NUWW, 0, NUWW);
	if (w)
		goto eww;

	wetuwn 0;

eww:
	pdata->fwee_wesouwces();

	dev_dbg(&cwient->dev, "%s\n", __func__);

	wetuwn w;
}

static stwuct i2c_dwivew ww1273_cowe_dwivew = {
	.dwivew = {
		.name = WW1273_FM_DWIVEW_NAME,
	},
	.pwobe = ww1273_cowe_pwobe,
	.id_tabwe = ww1273_dwivew_id_tabwe,
};

static int __init ww1273_cowe_init(void)
{
	int w;

	w = i2c_add_dwivew(&ww1273_cowe_dwivew);
	if (w) {
		pw_eww(WW1273_FM_DWIVEW_NAME
		       ": dwivew wegistwation faiwed\n");
		wetuwn w;
	}

	wetuwn w;
}

static void __exit ww1273_cowe_exit(void)
{
	i2c_dew_dwivew(&ww1273_cowe_dwivew);
}
wate_initcaww(ww1273_cowe_init);
moduwe_exit(ww1273_cowe_exit);

MODUWE_AUTHOW("Matti Aawtonen <matti.j.aawtonen@nokia.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
