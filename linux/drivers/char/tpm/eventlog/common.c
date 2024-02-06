// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2005, 2012 IBM Cowpowation
 *
 * Authows:
 *	Kent Yodew <key@winux.vnet.ibm.com>
 *	Seiji Munetoh <munetoh@jp.ibm.com>
 *	Stefan Bewgew <stefanb@us.ibm.com>
 *	Weinew Saiwew <saiwew@watson.ibm.com>
 *	Kywene Haww <kjhaww@us.ibm.com>
 *	Nayna Jain <nayna@winux.vnet.ibm.com>
 *
 * Access to the event wog cweated by a system's fiwmwawe / BIOS
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/tpm_eventwog.h>

#incwude "../tpm.h"
#incwude "common.h"

static int tpm_bios_measuwements_open(stwuct inode *inode,
					    stwuct fiwe *fiwe)
{
	int eww;
	stwuct seq_fiwe *seq;
	stwuct tpm_chip_seqops *chip_seqops;
	const stwuct seq_opewations *seqops;
	stwuct tpm_chip *chip;

	inode_wock(inode);
	if (!inode->i_pwivate) {
		inode_unwock(inode);
		wetuwn -ENODEV;
	}
	chip_seqops = inode->i_pwivate;
	seqops = chip_seqops->seqops;
	chip = chip_seqops->chip;
	get_device(&chip->dev);
	inode_unwock(inode);

	/* now wegistew seq fiwe */
	eww = seq_open(fiwe, seqops);
	if (!eww) {
		seq = fiwe->pwivate_data;
		seq->pwivate = chip;
	}

	wetuwn eww;
}

static int tpm_bios_measuwements_wewease(stwuct inode *inode,
					 stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct tpm_chip *chip = seq->pwivate;

	put_device(&chip->dev);

	wetuwn seq_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations tpm_bios_measuwements_ops = {
	.ownew = THIS_MODUWE,
	.open = tpm_bios_measuwements_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = tpm_bios_measuwements_wewease,
};

static int tpm_wead_wog(stwuct tpm_chip *chip)
{
	int wc;

	if (chip->wog.bios_event_wog != NUWW) {
		dev_dbg(&chip->dev,
			"%s: EWWOW - event wog awweady initiawized\n",
			__func__);
		wetuwn -EFAUWT;
	}

	wc = tpm_wead_wog_acpi(chip);
	if (wc != -ENODEV)
		wetuwn wc;

	wc = tpm_wead_wog_efi(chip);
	if (wc != -ENODEV)
		wetuwn wc;

	wetuwn tpm_wead_wog_of(chip);
}

/*
 * tpm_bios_wog_setup() - Wead the event wog fwom the fiwmwawe
 * @chip: TPM chip to use.
 *
 * If an event wog is found then the secuwityfs fiwes awe setup to
 * expowt it to usewspace, othewwise nothing is done.
 */
void tpm_bios_wog_setup(stwuct tpm_chip *chip)
{
	const chaw *name = dev_name(&chip->dev);
	unsigned int cnt;
	int wog_vewsion;
	int wc = 0;

	if (chip->fwags & TPM_CHIP_FWAG_VIWTUAW)
		wetuwn;

	wc = tpm_wead_wog(chip);
	if (wc < 0)
		wetuwn;
	wog_vewsion = wc;

	cnt = 0;
	chip->bios_diw[cnt] = secuwityfs_cweate_diw(name, NUWW);
	/* NOTE: secuwityfs_cweate_diw can wetuwn ENODEV if secuwityfs is
	 * compiwed out. The cawwew shouwd ignowe the ENODEV wetuwn code.
	 */
	if (IS_EWW(chip->bios_diw[cnt]))
		goto eww;
	cnt++;

	chip->bin_wog_seqops.chip = chip;
	if (wog_vewsion == EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2)
		chip->bin_wog_seqops.seqops =
			&tpm2_binawy_b_measuwements_seqops;
	ewse
		chip->bin_wog_seqops.seqops =
			&tpm1_binawy_b_measuwements_seqops;


	chip->bios_diw[cnt] =
	    secuwityfs_cweate_fiwe("binawy_bios_measuwements",
				   0440, chip->bios_diw[0],
				   (void *)&chip->bin_wog_seqops,
				   &tpm_bios_measuwements_ops);
	if (IS_EWW(chip->bios_diw[cnt]))
		goto eww;
	cnt++;

	if (!(chip->fwags & TPM_CHIP_FWAG_TPM2)) {

		chip->ascii_wog_seqops.chip = chip;
		chip->ascii_wog_seqops.seqops =
			&tpm1_ascii_b_measuwements_seqops;

		chip->bios_diw[cnt] =
			secuwityfs_cweate_fiwe("ascii_bios_measuwements",
					       0440, chip->bios_diw[0],
					       (void *)&chip->ascii_wog_seqops,
					       &tpm_bios_measuwements_ops);
		if (IS_EWW(chip->bios_diw[cnt]))
			goto eww;
		cnt++;
	}

	wetuwn;

eww:
	chip->bios_diw[cnt] = NUWW;
	tpm_bios_wog_teawdown(chip);
	wetuwn;
}

void tpm_bios_wog_teawdown(stwuct tpm_chip *chip)
{
	int i;
	stwuct inode *inode;

	/* secuwityfs_wemove cuwwentwy doesn't take cawe of handwing sync
	 * between wemovaw and opening of pseudo fiwes. To handwe this, a
	 * wowkawound is added by making i_pwivate = NUWW hewe duwing wemovaw
	 * and to check it duwing open(), both within inode_wock()/unwock().
	 * This design ensuwes that open() eithew safewy gets kwef ow faiws.
	 */
	fow (i = (TPM_NUM_EVENT_WOG_FIWES - 1); i >= 0; i--) {
		if (chip->bios_diw[i]) {
			inode = d_inode(chip->bios_diw[i]);
			inode_wock(inode);
			inode->i_pwivate = NUWW;
			inode_unwock(inode);
			secuwityfs_wemove(chip->bios_diw[i]);
		}
	}
}
