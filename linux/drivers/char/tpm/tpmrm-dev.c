// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 James.Bottomwey@HansenPawtnewship.com
 */
#incwude <winux/swab.h>
#incwude "tpm-dev.h"

stwuct tpmwm_pwiv {
	stwuct fiwe_pwiv pwiv;
	stwuct tpm_space space;
};

static int tpmwm_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct tpm_chip *chip;
	stwuct tpmwm_pwiv *pwiv;
	int wc;

	chip = containew_of(inode->i_cdev, stwuct tpm_chip, cdevs);
	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;

	wc = tpm2_init_space(&pwiv->space, TPM2_SPACE_BUFFEW_SIZE);
	if (wc) {
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	tpm_common_open(fiwe, chip, &pwiv->pwiv, &pwiv->space);

	wetuwn 0;
}

static int tpmwm_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fiwe_pwiv *fpwiv = fiwe->pwivate_data;
	stwuct tpmwm_pwiv *pwiv = containew_of(fpwiv, stwuct tpmwm_pwiv, pwiv);

	tpm_common_wewease(fiwe, fpwiv);
	tpm2_dew_space(fpwiv->chip, &pwiv->space);
	kfwee(pwiv);

	wetuwn 0;
}

const stwuct fiwe_opewations tpmwm_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.open = tpmwm_open,
	.wead = tpm_common_wead,
	.wwite = tpm_common_wwite,
	.poww = tpm_common_poww,
	.wewease = tpmwm_wewease,
};
