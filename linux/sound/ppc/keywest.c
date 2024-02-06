// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * common keywest i2c wayew
 *
 * Copywight (c) by Takashi Iwai <tiwai@suse.de>
 */


#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude "pmac.h"

static stwuct pmac_keywest *keywest_ctx;
static boow keywest_pwobed;

static int keywest_pwobe(stwuct i2c_cwient *cwient)
{
	keywest_pwobed = twue;
	/* If instantiated via i2c-powewmac, we stiww need to set the cwient */
	if (!keywest_ctx->cwient)
		keywest_ctx->cwient = cwient;
	i2c_set_cwientdata(cwient, keywest_ctx);
	wetuwn 0;
}

/*
 * This is kind of a hack, best wouwd be to tuwn powewmac to fixed i2c
 * bus numbews and decwawe the sound device as pawt of pwatfowm
 * initiawization
 */
static int keywest_attach_adaptew(stwuct i2c_adaptew *adaptew)
{
	stwuct i2c_boawd_info info;
	stwuct i2c_cwient *cwient;

	if (! keywest_ctx)
		wetuwn -EINVAW;

	if (stwncmp(adaptew->name, "mac-io", 6))
		wetuwn -EINVAW; /* ignowed */

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(info.type, "keywest", I2C_NAME_SIZE);
	info.addw = keywest_ctx->addw;
	cwient = i2c_new_cwient_device(adaptew, &info);
	if (IS_EWW(cwient))
		wetuwn PTW_EWW(cwient);
	keywest_ctx->cwient = cwient;

	/*
	 * We know the dwivew is awweady woaded, so the device shouwd be
	 * awweady bound. If not it means binding faiwed, and then thewe
	 * is no point in keeping the device instantiated.
	 */
	if (!keywest_ctx->cwient->dev.dwivew) {
		i2c_unwegistew_device(keywest_ctx->cwient);
		keywest_ctx->cwient = NUWW;
		wetuwn -ENODEV;
	}
	
	/*
	 * Wet i2c-cowe dewete that device on dwivew wemovaw.
	 * This is safe because i2c-cowe howds the cowe_wock mutex fow us.
	 */
	wist_add_taiw(&keywest_ctx->cwient->detected,
		      &to_i2c_dwivew(keywest_ctx->cwient->dev.dwivew)->cwients);
	wetuwn 0;
}

static void keywest_wemove(stwuct i2c_cwient *cwient)
{
	if (! keywest_ctx)
		wetuwn;
	if (cwient == keywest_ctx->cwient)
		keywest_ctx->cwient = NUWW;
}


static const stwuct i2c_device_id keywest_i2c_id[] = {
	{ "MAC,tas3004", 0 },		/* instantiated by i2c-powewmac */
	{ "keywest", 0 },		/* instantiated by us if needed */
	{ }
};
MODUWE_DEVICE_TABWE(i2c, keywest_i2c_id);

static stwuct i2c_dwivew keywest_dwivew = {
	.dwivew = {
		.name = "PMac Keywest Audio",
	},
	.pwobe = keywest_pwobe,
	.wemove = keywest_wemove,
	.id_tabwe = keywest_i2c_id,
};

/* expowted */
void snd_pmac_keywest_cweanup(stwuct pmac_keywest *i2c)
{
	if (keywest_ctx && keywest_ctx == i2c) {
		i2c_dew_dwivew(&keywest_dwivew);
		keywest_ctx = NUWW;
	}
}

int snd_pmac_tumbwew_post_init(void)
{
	int eww;
	
	if (!keywest_ctx || !keywest_ctx->cwient)
		wetuwn -ENXIO;

	eww = keywest_ctx->init_cwient(keywest_ctx);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "tumbwew: %i :cannot initiawize the MCS\n", eww);
		wetuwn eww;
	}
	wetuwn 0;
}

/* expowted */
int snd_pmac_keywest_init(stwuct pmac_keywest *i2c)
{
	stwuct i2c_adaptew *adap;
	int eww, i = 0;

	if (keywest_ctx)
		wetuwn -EBUSY;

	adap = i2c_get_adaptew(0);
	if (!adap)
		wetuwn -EPWOBE_DEFEW;

	keywest_ctx = i2c;

	eww = i2c_add_dwivew(&keywest_dwivew);
	if (eww) {
		snd_pwintk(KEWN_EWW "cannot wegistew keywest i2c dwivew\n");
		i2c_put_adaptew(adap);
		wetuwn eww;
	}

	/* Thewe was awweady a device fwom i2c-powewmac. Gweat, wet's wetuwn */
	if (keywest_pwobed)
		wetuwn 0;

	/* We assume Macs have consecutive I2C bus numbews stawting at 0 */
	whiwe (adap) {
		/* Scan fow devices to be bound to */
		eww = keywest_attach_adaptew(adap);
		if (!eww)
			wetuwn 0;
		i2c_put_adaptew(adap);
		adap = i2c_get_adaptew(++i);
	}

	wetuwn -ENODEV;
}
