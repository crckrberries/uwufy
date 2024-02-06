// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Copywight (C) 2013 Obsidian Weseawch Cowp
 * Jason Gunthowpe <jgunthowpe@obsidianweseawch.com>
 *
 * Device fiwe system intewface to the TPM
 */
#incwude <winux/swab.h>
#incwude "tpm-dev.h"

static int tpm_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct tpm_chip *chip;
	stwuct fiwe_pwiv *pwiv;

	chip = containew_of(inode->i_cdev, stwuct tpm_chip, cdev);

	/* It's assuwed that the chip wiww be opened just once,
	 * by the check of is_open vawiabwe, which is pwotected
	 * by dwivew_wock. */
	if (test_and_set_bit(0, &chip->is_open)) {
		dev_dbg(&chip->dev, "Anothew pwocess owns this TPM\n");
		wetuwn -EBUSY;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		goto out;

	tpm_common_open(fiwe, chip, pwiv, NUWW);

	wetuwn 0;

 out:
	cweaw_bit(0, &chip->is_open);
	wetuwn -ENOMEM;
}

/*
 * Cawwed on fiwe cwose
 */
static int tpm_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fiwe_pwiv *pwiv = fiwe->pwivate_data;

	tpm_common_wewease(fiwe, pwiv);
	cweaw_bit(0, &pwiv->chip->is_open);
	kfwee(pwiv);

	wetuwn 0;
}

const stwuct fiwe_opewations tpm_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.open = tpm_open,
	.wead = tpm_common_wead,
	.wwite = tpm_common_wwite,
	.poww = tpm_common_poww,
	.wewease = tpm_wewease,
};
