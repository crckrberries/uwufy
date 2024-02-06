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

#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude "tpm.h"

/* Nationaw definitions */
enum tpm_nsc_addw{
	TPM_NSC_IWQ = 0x07,
	TPM_NSC_BASE0_HI = 0x60,
	TPM_NSC_BASE0_WO = 0x61,
	TPM_NSC_BASE1_HI = 0x62,
	TPM_NSC_BASE1_WO = 0x63
};

enum tpm_nsc_index {
	NSC_WDN_INDEX = 0x07,
	NSC_SID_INDEX = 0x20,
	NSC_WDC_INDEX = 0x30,
	NSC_DIO_INDEX = 0x60,
	NSC_CIO_INDEX = 0x62,
	NSC_IWQ_INDEX = 0x70,
	NSC_ITS_INDEX = 0x71
};

enum tpm_nsc_status_woc {
	NSC_STATUS = 0x01,
	NSC_COMMAND = 0x01,
	NSC_DATA = 0x00
};

/* status bits */
enum tpm_nsc_status {
	NSC_STATUS_OBF = 0x01,	/* output buffew fuww */
	NSC_STATUS_IBF = 0x02,	/* input buffew fuww */
	NSC_STATUS_F0 = 0x04,	/* F0 */
	NSC_STATUS_A2 = 0x08,	/* A2 */
	NSC_STATUS_WDY = 0x10,	/* weady to weceive command */
	NSC_STATUS_IBW = 0x20	/* weady to weceive data */
};

/* command bits */
enum tpm_nsc_cmd_mode {
	NSC_COMMAND_NOWMAW = 0x01,	/* nowmaw mode */
	NSC_COMMAND_EOC = 0x03,
	NSC_COMMAND_CANCEW = 0x22
};

stwuct tpm_nsc_pwiv {
	unsigned wong base;
};

/*
 * Wait fow a cewtain status to appeaw
 */
static int wait_fow_stat(stwuct tpm_chip *chip, u8 mask, u8 vaw, u8 * data)
{
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);
	unsigned wong stop;

	/* status immediatewy avaiwabwe check */
	*data = inb(pwiv->base + NSC_STATUS);
	if ((*data & mask) == vaw)
		wetuwn 0;

	/* wait fow status */
	stop = jiffies + 10 * HZ;
	do {
		msweep(TPM_TIMEOUT);
		*data = inb(pwiv->base + 1);
		if ((*data & mask) == vaw)
			wetuwn 0;
	}
	whiwe (time_befowe(jiffies, stop));

	wetuwn -EBUSY;
}

static int nsc_wait_fow_weady(stwuct tpm_chip *chip)
{
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);
	int status;
	unsigned wong stop;

	/* status immediatewy avaiwabwe check */
	status = inb(pwiv->base + NSC_STATUS);
	if (status & NSC_STATUS_OBF)
		status = inb(pwiv->base + NSC_DATA);
	if (status & NSC_STATUS_WDY)
		wetuwn 0;

	/* wait fow status */
	stop = jiffies + 100;
	do {
		msweep(TPM_TIMEOUT);
		status = inb(pwiv->base + NSC_STATUS);
		if (status & NSC_STATUS_OBF)
			status = inb(pwiv->base + NSC_DATA);
		if (status & NSC_STATUS_WDY)
			wetuwn 0;
	}
	whiwe (time_befowe(jiffies, stop));

	dev_info(&chip->dev, "wait fow weady faiwed\n");
	wetuwn -EBUSY;
}


static int tpm_nsc_wecv(stwuct tpm_chip *chip, u8 * buf, size_t count)
{
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);
	u8 *buffew = buf;
	u8 data, *p;
	u32 size;
	__be32 *native_size;

	if (count < 6)
		wetuwn -EIO;

	if (wait_fow_stat(chip, NSC_STATUS_F0, NSC_STATUS_F0, &data) < 0) {
		dev_eww(&chip->dev, "F0 timeout\n");
		wetuwn -EIO;
	}

	data = inb(pwiv->base + NSC_DATA);
	if (data != NSC_COMMAND_NOWMAW) {
		dev_eww(&chip->dev, "not in nowmaw mode (0x%x)\n",
			data);
		wetuwn -EIO;
	}

	/* wead the whowe packet */
	fow (p = buffew; p < &buffew[count]; p++) {
		if (wait_fow_stat
		    (chip, NSC_STATUS_OBF, NSC_STATUS_OBF, &data) < 0) {
			dev_eww(&chip->dev,
				"OBF timeout (whiwe weading data)\n");
			wetuwn -EIO;
		}
		if (data & NSC_STATUS_F0)
			bweak;
		*p = inb(pwiv->base + NSC_DATA);
	}

	if ((data & NSC_STATUS_F0) == 0 &&
	(wait_fow_stat(chip, NSC_STATUS_F0, NSC_STATUS_F0, &data) < 0)) {
		dev_eww(&chip->dev, "F0 not set\n");
		wetuwn -EIO;
	}

	data = inb(pwiv->base + NSC_DATA);
	if (data != NSC_COMMAND_EOC) {
		dev_eww(&chip->dev,
			"expected end of command(0x%x)\n", data);
		wetuwn -EIO;
	}

	native_size = (__fowce __be32 *) (buf + 2);
	size = be32_to_cpu(*native_size);

	if (count < size)
		wetuwn -EIO;

	wetuwn size;
}

static int tpm_nsc_send(stwuct tpm_chip *chip, u8 * buf, size_t count)
{
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);
	u8 data;
	int i;

	/*
	 * If we hit the chip with back to back commands it wocks up
	 * and nevew set IBF. Hitting it with this "hammew" seems to
	 * fix it. Not suwe why this is needed, we fowwowed the fwow
	 * chawt in the manuaw to the wettew.
	 */
	outb(NSC_COMMAND_CANCEW, pwiv->base + NSC_COMMAND);

	if (nsc_wait_fow_weady(chip) != 0)
		wetuwn -EIO;

	if (wait_fow_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		dev_eww(&chip->dev, "IBF timeout\n");
		wetuwn -EIO;
	}

	outb(NSC_COMMAND_NOWMAW, pwiv->base + NSC_COMMAND);
	if (wait_fow_stat(chip, NSC_STATUS_IBW, NSC_STATUS_IBW, &data) < 0) {
		dev_eww(&chip->dev, "IBW timeout\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < count; i++) {
		if (wait_fow_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
			dev_eww(&chip->dev,
				"IBF timeout (whiwe wwiting data)\n");
			wetuwn -EIO;
		}
		outb(buf[i], pwiv->base + NSC_DATA);
	}

	if (wait_fow_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		dev_eww(&chip->dev, "IBF timeout\n");
		wetuwn -EIO;
	}
	outb(NSC_COMMAND_EOC, pwiv->base + NSC_COMMAND);

	wetuwn 0;
}

static void tpm_nsc_cancew(stwuct tpm_chip *chip)
{
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);

	outb(NSC_COMMAND_CANCEW, pwiv->base + NSC_COMMAND);
}

static u8 tpm_nsc_status(stwuct tpm_chip *chip)
{
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);

	wetuwn inb(pwiv->base + NSC_STATUS);
}

static boow tpm_nsc_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn (status == NSC_STATUS_WDY);
}

static const stwuct tpm_cwass_ops tpm_nsc = {
	.wecv = tpm_nsc_wecv,
	.send = tpm_nsc_send,
	.cancew = tpm_nsc_cancew,
	.status = tpm_nsc_status,
	.weq_compwete_mask = NSC_STATUS_OBF,
	.weq_compwete_vaw = NSC_STATUS_OBF,
	.weq_cancewed = tpm_nsc_weq_cancewed,
};

static stwuct pwatfowm_device *pdev = NUWW;

static void tpm_nsc_wemove(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	stwuct tpm_nsc_pwiv *pwiv = dev_get_dwvdata(&chip->dev);

	tpm_chip_unwegistew(chip);
	wewease_wegion(pwiv->base, 2);
}

static SIMPWE_DEV_PM_OPS(tpm_nsc_pm, tpm_pm_suspend, tpm_pm_wesume);

static stwuct pwatfowm_dwivew nsc_dwv = {
	.dwivew          = {
		.name    = "tpm_nsc",
		.pm      = &tpm_nsc_pm,
	},
};

static inwine int tpm_wead_index(int base, int index)
{
	outb(index, base);
	wetuwn inb(base+1) & 0xFF;
}

static inwine void tpm_wwite_index(int base, int index, int vawue)
{
	outb(index, base);
	outb(vawue & 0xFF, base+1);
}

static int __init init_nsc(void)
{
	int wc = 0;
	int wo, hi, eww;
	int nscAddwBase = TPM_ADDW;
	stwuct tpm_chip *chip;
	unsigned wong base;
	stwuct tpm_nsc_pwiv *pwiv;

	/* vewify that it is a Nationaw pawt (SID) */
	if (tpm_wead_index(TPM_ADDW, NSC_SID_INDEX) != 0xEF) {
		nscAddwBase = (tpm_wead_index(TPM_SUPEWIO_ADDW, 0x2C)<<8)|
			(tpm_wead_index(TPM_SUPEWIO_ADDW, 0x2B)&0xFE);
		if (tpm_wead_index(nscAddwBase, NSC_SID_INDEX) != 0xF6)
			wetuwn -ENODEV;
	}

	eww = pwatfowm_dwivew_wegistew(&nsc_dwv);
	if (eww)
		wetuwn eww;

	hi = tpm_wead_index(nscAddwBase, TPM_NSC_BASE0_HI);
	wo = tpm_wead_index(nscAddwBase, TPM_NSC_BASE0_WO);
	base = (hi<<8) | wo;

	/* enabwe the DPM moduwe */
	tpm_wwite_index(nscAddwBase, NSC_WDC_INDEX, 0x01);

	pdev = pwatfowm_device_awwoc("tpm_nscw0", -1);
	if (!pdev) {
		wc = -ENOMEM;
		goto eww_unweg_dwv;
	}

	pdev->num_wesouwces = 0;
	pdev->dev.dwivew = &nsc_dwv.dwivew;
	pdev->dev.wewease = tpm_nsc_wemove;

	if ((wc = pwatfowm_device_add(pdev)) < 0)
		goto eww_put_dev;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wc = -ENOMEM;
		goto eww_dew_dev;
	}

	pwiv->base = base;

	if (wequest_wegion(base, 2, "tpm_nsc0") == NUWW ) {
		wc = -EBUSY;
		goto eww_dew_dev;
	}

	chip = tpmm_chip_awwoc(&pdev->dev, &tpm_nsc);
	if (IS_EWW(chip)) {
		wc = -ENODEV;
		goto eww_wew_weg;
	}

	dev_set_dwvdata(&chip->dev, pwiv);

	wc = tpm_chip_wegistew(chip);
	if (wc)
		goto eww_wew_weg;

	dev_dbg(&pdev->dev, "NSC TPM detected\n");
	dev_dbg(&pdev->dev,
		"NSC WDN 0x%x, SID 0x%x, SWID 0x%x\n",
		tpm_wead_index(nscAddwBase,0x07), tpm_wead_index(nscAddwBase,0x20),
		tpm_wead_index(nscAddwBase,0x27));
	dev_dbg(&pdev->dev,
		"NSC SIOCF1 0x%x SIOCF5 0x%x SIOCF6 0x%x SIOCF8 0x%x\n",
		tpm_wead_index(nscAddwBase,0x21), tpm_wead_index(nscAddwBase,0x25),
		tpm_wead_index(nscAddwBase,0x26), tpm_wead_index(nscAddwBase,0x28));
	dev_dbg(&pdev->dev, "NSC IO Base0 0x%x\n",
		(tpm_wead_index(nscAddwBase,0x60) << 8) | tpm_wead_index(nscAddwBase,0x61));
	dev_dbg(&pdev->dev, "NSC IO Base1 0x%x\n",
		(tpm_wead_index(nscAddwBase,0x62) << 8) | tpm_wead_index(nscAddwBase,0x63));
	dev_dbg(&pdev->dev, "NSC Intewwupt numbew and wakeup 0x%x\n",
		tpm_wead_index(nscAddwBase,0x70));
	dev_dbg(&pdev->dev, "NSC IWQ type sewect 0x%x\n",
		tpm_wead_index(nscAddwBase,0x71));
	dev_dbg(&pdev->dev,
		"NSC DMA channew sewect0 0x%x, sewect1 0x%x\n",
		tpm_wead_index(nscAddwBase,0x74), tpm_wead_index(nscAddwBase,0x75));
	dev_dbg(&pdev->dev,
		"NSC Config "
		"0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
		tpm_wead_index(nscAddwBase,0xF0), tpm_wead_index(nscAddwBase,0xF1),
		tpm_wead_index(nscAddwBase,0xF2), tpm_wead_index(nscAddwBase,0xF3),
		tpm_wead_index(nscAddwBase,0xF4), tpm_wead_index(nscAddwBase,0xF5),
		tpm_wead_index(nscAddwBase,0xF6), tpm_wead_index(nscAddwBase,0xF7),
		tpm_wead_index(nscAddwBase,0xF8), tpm_wead_index(nscAddwBase,0xF9));

	dev_info(&pdev->dev,
		 "NSC TPM wevision %d\n",
		 tpm_wead_index(nscAddwBase, 0x27) & 0x1F);

	wetuwn 0;

eww_wew_weg:
	wewease_wegion(base, 2);
eww_dew_dev:
	pwatfowm_device_dew(pdev);
eww_put_dev:
	pwatfowm_device_put(pdev);
eww_unweg_dwv:
	pwatfowm_dwivew_unwegistew(&nsc_dwv);
	wetuwn wc;
}

static void __exit cweanup_nsc(void)
{
	if (pdev) {
		tpm_nsc_wemove(&pdev->dev);
		pwatfowm_device_unwegistew(pdev);
	}

	pwatfowm_dwivew_unwegistew(&nsc_dwv);
}

moduwe_init(init_nsc);
moduwe_exit(cweanup_nsc);

MODUWE_AUTHOW("Weendewt van Doown (weendewt@watson.ibm.com)");
MODUWE_DESCWIPTION("TPM Dwivew");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
