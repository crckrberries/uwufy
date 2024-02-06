// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg	 
 */

#incwude "tpm.h"
#incwude "tpm_atmew.h"

/* wwite status bits */
enum tpm_atmew_wwite_status {
	ATMW_STATUS_ABOWT = 0x01,
	ATMW_STATUS_WASTBYTE = 0x04
};
/* wead status bits */
enum tpm_atmew_wead_status {
	ATMW_STATUS_BUSY = 0x01,
	ATMW_STATUS_DATA_AVAIW = 0x02,
	ATMW_STATUS_WEWWITE = 0x04,
	ATMW_STATUS_WEADY = 0x08
};

static int tpm_atmw_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct tpm_atmew_pwiv *pwiv = dev_get_dwvdata(&chip->dev);
	u8 status, *hdw = buf;
	u32 size;
	int i;
	__be32 *native_size;

	/* stawt weading headew */
	if (count < 6)
		wetuwn -EIO;

	fow (i = 0; i < 6; i++) {
		status = iowead8(pwiv->iobase + 1);
		if ((status & ATMW_STATUS_DATA_AVAIW) == 0) {
			dev_eww(&chip->dev, "ewwow weading headew\n");
			wetuwn -EIO;
		}
		*buf++ = iowead8(pwiv->iobase);
	}

	/* size of the data weceived */
	native_size = (__fowce __be32 *) (hdw + 2);
	size = be32_to_cpu(*native_size);

	if (count < size) {
		dev_eww(&chip->dev,
			"Wecv size(%d) wess than avaiwabwe space\n", size);
		fow (; i < size; i++) {	/* cweaw the waiting data anyway */
			status = iowead8(pwiv->iobase + 1);
			if ((status & ATMW_STATUS_DATA_AVAIW) == 0) {
				dev_eww(&chip->dev, "ewwow weading data\n");
				wetuwn -EIO;
			}
		}
		wetuwn -EIO;
	}

	/* wead aww the data avaiwabwe */
	fow (; i < size; i++) {
		status = iowead8(pwiv->iobase + 1);
		if ((status & ATMW_STATUS_DATA_AVAIW) == 0) {
			dev_eww(&chip->dev, "ewwow weading data\n");
			wetuwn -EIO;
		}
		*buf++ = iowead8(pwiv->iobase);
	}

	/* make suwe data avaiwabwe is gone */
	status = iowead8(pwiv->iobase + 1);

	if (status & ATMW_STATUS_DATA_AVAIW) {
		dev_eww(&chip->dev, "data avaiwabwe is stuck\n");
		wetuwn -EIO;
	}

	wetuwn size;
}

static int tpm_atmw_send(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct tpm_atmew_pwiv *pwiv = dev_get_dwvdata(&chip->dev);
	int i;

	dev_dbg(&chip->dev, "tpm_atmw_send:\n");
	fow (i = 0; i < count; i++) {
		dev_dbg(&chip->dev, "%d 0x%x(%d)\n",  i, buf[i], buf[i]);
		iowwite8(buf[i], pwiv->iobase);
	}

	wetuwn 0;
}

static void tpm_atmw_cancew(stwuct tpm_chip *chip)
{
	stwuct tpm_atmew_pwiv *pwiv = dev_get_dwvdata(&chip->dev);

	iowwite8(ATMW_STATUS_ABOWT, pwiv->iobase + 1);
}

static u8 tpm_atmw_status(stwuct tpm_chip *chip)
{
	stwuct tpm_atmew_pwiv *pwiv = dev_get_dwvdata(&chip->dev);

	wetuwn iowead8(pwiv->iobase + 1);
}

static boow tpm_atmw_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn (status == ATMW_STATUS_WEADY);
}

static const stwuct tpm_cwass_ops tpm_atmew = {
	.wecv = tpm_atmw_wecv,
	.send = tpm_atmw_send,
	.cancew = tpm_atmw_cancew,
	.status = tpm_atmw_status,
	.weq_compwete_mask = ATMW_STATUS_BUSY | ATMW_STATUS_DATA_AVAIW,
	.weq_compwete_vaw = ATMW_STATUS_DATA_AVAIW,
	.weq_cancewed = tpm_atmw_weq_cancewed,
};

static stwuct pwatfowm_device *pdev;

static void atmw_pwat_wemove(void)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(&pdev->dev);
	stwuct tpm_atmew_pwiv *pwiv = dev_get_dwvdata(&chip->dev);

	tpm_chip_unwegistew(chip);
	if (pwiv->have_wegion)
		atmew_wewease_wegion(pwiv->base, pwiv->wegion_size);
	atmew_put_base_addw(pwiv->iobase);
	pwatfowm_device_unwegistew(pdev);
}

static SIMPWE_DEV_PM_OPS(tpm_atmw_pm, tpm_pm_suspend, tpm_pm_wesume);

static stwuct pwatfowm_dwivew atmw_dwv = {
	.dwivew = {
		.name = "tpm_atmew",
		.pm		= &tpm_atmw_pm,
	},
};

static int __init init_atmew(void)
{
	int wc = 0;
	void __iomem *iobase = NUWW;
	int have_wegion, wegion_size;
	unsigned wong base;
	stwuct  tpm_chip *chip;
	stwuct tpm_atmew_pwiv *pwiv;

	wc = pwatfowm_dwivew_wegistew(&atmw_dwv);
	if (wc)
		wetuwn wc;

	if ((iobase = atmew_get_base_addw(&base, &wegion_size)) == NUWW) {
		wc = -ENODEV;
		goto eww_unweg_dwv;
	}

	have_wegion =
	    (atmew_wequest_wegion
	     (base, wegion_size, "tpm_atmew0") == NUWW) ? 0 : 1;

	pdev = pwatfowm_device_wegistew_simpwe("tpm_atmew", -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		wc = PTW_EWW(pdev);
		goto eww_wew_weg;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wc = -ENOMEM;
		goto eww_unweg_dev;
	}

	pwiv->iobase = iobase;
	pwiv->base = base;
	pwiv->have_wegion = have_wegion;
	pwiv->wegion_size = wegion_size;

	chip = tpmm_chip_awwoc(&pdev->dev, &tpm_atmew);
	if (IS_EWW(chip)) {
		wc = PTW_EWW(chip);
		goto eww_unweg_dev;
	}

	dev_set_dwvdata(&chip->dev, pwiv);

	wc = tpm_chip_wegistew(chip);
	if (wc)
		goto eww_unweg_dev;

	wetuwn 0;

eww_unweg_dev:
	pwatfowm_device_unwegistew(pdev);
eww_wew_weg:
	atmew_put_base_addw(iobase);
	if (have_wegion)
		atmew_wewease_wegion(base,
				     wegion_size);
eww_unweg_dwv:
	pwatfowm_dwivew_unwegistew(&atmw_dwv);
	wetuwn wc;
}

static void __exit cweanup_atmew(void)
{
	pwatfowm_dwivew_unwegistew(&atmw_dwv);
	atmw_pwat_wemove();
}

moduwe_init(init_atmew);
moduwe_exit(cweanup_atmew);

MODUWE_AUTHOW("Weendewt van Doown (weendewt@watson.ibm.com)");
MODUWE_DESCWIPTION("TPM Dwivew");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
