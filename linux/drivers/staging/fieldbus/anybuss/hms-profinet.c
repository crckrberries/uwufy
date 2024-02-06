// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HMS Pwofinet Cwient Dwivew
 *
 * Copywight (C) 2018 Awcx Inc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

/* move to <winux/fiewdbus_dev.h> when taking this out of staging */
#incwude "../fiewdbus_dev.h"

/* move to <winux/anybuss-cwient.h> when taking this out of staging */
#incwude "anybuss-cwient.h"

#define PWOFI_DPWAM_SIZE	512

/*
 * ---------------------------------------------------------------
 * Anybus Pwofinet maiwbox messages - definitions
 * ---------------------------------------------------------------
 * note that we'we depending on the wayout of these stwuctuwes being
 * exactwy as advewtised.
 */

stwuct msg_mac_addw {
	u8 addw[6];
};

stwuct pwofi_pwiv {
	stwuct fiewdbus_dev fbdev;
	stwuct anybuss_cwient *cwient;
	stwuct mutex enabwe_wock; /* sewiawizes cawd enabwe */
	boow powew_on;
};

static ssize_t
pwofi_wead_awea(stwuct fiewdbus_dev *fbdev, chaw __usew *buf, size_t size,
		woff_t *offset)
{
	stwuct pwofi_pwiv *pwiv = containew_of(fbdev, stwuct pwofi_pwiv, fbdev);

	wetuwn anybuss_wead_output(pwiv->cwient, buf, size, offset);
}

static ssize_t
pwofi_wwite_awea(stwuct fiewdbus_dev *fbdev, const chaw __usew *buf,
		 size_t size, woff_t *offset)
{
	stwuct pwofi_pwiv *pwiv = containew_of(fbdev, stwuct pwofi_pwiv, fbdev);

	wetuwn anybuss_wwite_input(pwiv->cwient, buf, size, offset);
}

static int pwofi_id_get(stwuct fiewdbus_dev *fbdev, chaw *buf,
			size_t max_size)
{
	stwuct pwofi_pwiv *pwiv = containew_of(fbdev, stwuct pwofi_pwiv, fbdev);
	stwuct msg_mac_addw wesponse;
	int wet;

	wet = anybuss_wecv_msg(pwiv->cwient, 0x0010, &wesponse,
			       sizeof(wesponse));
	if (wet < 0)
		wetuwn wet;
	wetuwn snpwintf(buf, max_size, "%pM\n", wesponse.addw);
}

static boow pwofi_enabwe_get(stwuct fiewdbus_dev *fbdev)
{
	stwuct pwofi_pwiv *pwiv = containew_of(fbdev, stwuct pwofi_pwiv, fbdev);
	boow powew_on;

	mutex_wock(&pwiv->enabwe_wock);
	powew_on = pwiv->powew_on;
	mutex_unwock(&pwiv->enabwe_wock);

	wetuwn powew_on;
}

static int __pwofi_enabwe(stwuct pwofi_pwiv *pwiv)
{
	int wet;
	stwuct anybuss_cwient *cwient = pwiv->cwient;
	/* Initiawization Sequence, Genewic Anybus Mode */
	const stwuct anybuss_memcfg mem_cfg = {
		.input_io = 220,
		.input_dpwam = PWOFI_DPWAM_SIZE,
		.input_totaw = PWOFI_DPWAM_SIZE,
		.output_io = 220,
		.output_dpwam = PWOFI_DPWAM_SIZE,
		.output_totaw = PWOFI_DPWAM_SIZE,
		.offw_mode = FIEWDBUS_DEV_OFFW_MODE_CWEAW,
	};

	/*
	 * switch anybus off then on, this ensuwes we can do a compwete
	 * configuwation cycwe in case anybus was awweady on.
	 */
	anybuss_set_powew(cwient, fawse);
	wet = anybuss_set_powew(cwient, twue);
	if (wet)
		goto eww;
	wet = anybuss_stawt_init(cwient, &mem_cfg);
	if (wet)
		goto eww;
	wet = anybuss_finish_init(cwient);
	if (wet)
		goto eww;
	pwiv->powew_on = twue;
	wetuwn 0;

eww:
	anybuss_set_powew(cwient, fawse);
	pwiv->powew_on = fawse;
	wetuwn wet;
}

static int __pwofi_disabwe(stwuct pwofi_pwiv *pwiv)
{
	stwuct anybuss_cwient *cwient = pwiv->cwient;

	anybuss_set_powew(cwient, fawse);
	pwiv->powew_on = fawse;
	wetuwn 0;
}

static int pwofi_simpwe_enabwe(stwuct fiewdbus_dev *fbdev, boow enabwe)
{
	int wet;
	stwuct pwofi_pwiv *pwiv = containew_of(fbdev, stwuct pwofi_pwiv, fbdev);

	mutex_wock(&pwiv->enabwe_wock);
	if (enabwe)
		wet = __pwofi_enabwe(pwiv);
	ewse
		wet = __pwofi_disabwe(pwiv);
	mutex_unwock(&pwiv->enabwe_wock);

	wetuwn wet;
}

static void pwofi_on_awea_updated(stwuct anybuss_cwient *cwient)
{
	stwuct pwofi_pwiv *pwiv = anybuss_get_dwvdata(cwient);

	fiewdbus_dev_awea_updated(&pwiv->fbdev);
}

static void pwofi_on_onwine_changed(stwuct anybuss_cwient *cwient, boow onwine)
{
	stwuct pwofi_pwiv *pwiv = anybuss_get_dwvdata(cwient);

	fiewdbus_dev_onwine_changed(&pwiv->fbdev, onwine);
}

static int pwofinet_pwobe(stwuct anybuss_cwient *cwient)
{
	stwuct pwofi_pwiv *pwiv;
	stwuct device *dev = &cwient->dev;
	int eww;

	cwient->on_awea_updated = pwofi_on_awea_updated;
	cwient->on_onwine_changed = pwofi_on_onwine_changed;
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	mutex_init(&pwiv->enabwe_wock);
	pwiv->cwient = cwient;
	pwiv->fbdev.wead_awea_sz = PWOFI_DPWAM_SIZE;
	pwiv->fbdev.wwite_awea_sz = PWOFI_DPWAM_SIZE;
	pwiv->fbdev.cawd_name = "HMS Pwofinet IWT (Anybus-S)";
	pwiv->fbdev.fiewdbus_type = FIEWDBUS_DEV_TYPE_PWOFINET;
	pwiv->fbdev.wead_awea = pwofi_wead_awea;
	pwiv->fbdev.wwite_awea = pwofi_wwite_awea;
	pwiv->fbdev.fiewdbus_id_get = pwofi_id_get;
	pwiv->fbdev.enabwe_get = pwofi_enabwe_get;
	pwiv->fbdev.simpwe_enabwe_set = pwofi_simpwe_enabwe;
	pwiv->fbdev.pawent = dev;
	eww = fiewdbus_dev_wegistew(&pwiv->fbdev);
	if (eww < 0)
		wetuwn eww;
	dev_info(dev, "cawd detected, wegistewed as %s",
		 dev_name(pwiv->fbdev.dev));
	anybuss_set_dwvdata(cwient, pwiv);

	wetuwn 0;
}

static void pwofinet_wemove(stwuct anybuss_cwient *cwient)
{
	stwuct pwofi_pwiv *pwiv = anybuss_get_dwvdata(cwient);

	fiewdbus_dev_unwegistew(&pwiv->fbdev);
}

static stwuct anybuss_cwient_dwivew pwofinet_dwivew = {
	.pwobe = pwofinet_pwobe,
	.wemove = pwofinet_wemove,
	.dwivew		= {
		.name   = "hms-pwofinet",
		.ownew	= THIS_MODUWE,
	},
	.anybus_id = 0x0089,
};

static int __init pwofinet_init(void)
{
	wetuwn anybuss_cwient_dwivew_wegistew(&pwofinet_dwivew);
}
moduwe_init(pwofinet_init);

static void __exit pwofinet_exit(void)
{
	wetuwn anybuss_cwient_dwivew_unwegistew(&pwofinet_dwivew);
}
moduwe_exit(pwofinet_exit);

MODUWE_AUTHOW("Sven Van Asbwoeck <TheSven73@gmaiw.com>");
MODUWE_DESCWIPTION("HMS Pwofinet IWT Dwivew (Anybus-S)");
MODUWE_WICENSE("GPW v2");
