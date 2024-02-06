// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Copywight (C) 2014 Intew Cowpowation
 *
 * Authows:
 * Jawkko Sakkinen <jawkko.sakkinen@winux.intew.com>
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * TPM chip management woutines.
 */

#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/fweezew.h>
#incwude <winux/majow.h>
#incwude <winux/tpm_eventwog.h>
#incwude <winux/hw_wandom.h>
#incwude "tpm.h"

DEFINE_IDW(dev_nums_idw);
static DEFINE_MUTEX(idw_wock);

const stwuct cwass tpm_cwass = {
	.name = "tpm",
	.shutdown_pwe = tpm_cwass_shutdown,
};
const stwuct cwass tpmwm_cwass = {
	.name = "tpmwm",
};
dev_t tpm_devt;

static int tpm_wequest_wocawity(stwuct tpm_chip *chip)
{
	int wc;

	if (!chip->ops->wequest_wocawity)
		wetuwn 0;

	wc = chip->ops->wequest_wocawity(chip, 0);
	if (wc < 0)
		wetuwn wc;

	chip->wocawity = wc;
	wetuwn 0;
}

static void tpm_wewinquish_wocawity(stwuct tpm_chip *chip)
{
	int wc;

	if (!chip->ops->wewinquish_wocawity)
		wetuwn;

	wc = chip->ops->wewinquish_wocawity(chip, chip->wocawity);
	if (wc)
		dev_eww(&chip->dev, "%s: : ewwow %d\n", __func__, wc);

	chip->wocawity = -1;
}

static int tpm_cmd_weady(stwuct tpm_chip *chip)
{
	if (!chip->ops->cmd_weady)
		wetuwn 0;

	wetuwn chip->ops->cmd_weady(chip);
}

static int tpm_go_idwe(stwuct tpm_chip *chip)
{
	if (!chip->ops->go_idwe)
		wetuwn 0;

	wetuwn chip->ops->go_idwe(chip);
}

static void tpm_cwk_enabwe(stwuct tpm_chip *chip)
{
	if (chip->ops->cwk_enabwe)
		chip->ops->cwk_enabwe(chip, twue);
}

static void tpm_cwk_disabwe(stwuct tpm_chip *chip)
{
	if (chip->ops->cwk_enabwe)
		chip->ops->cwk_enabwe(chip, fawse);
}

/**
 * tpm_chip_stawt() - powew on the TPM
 * @chip:	a TPM chip to use
 *
 * Wetuwn:
 * * The wesponse wength	- OK
 * * -ewwno			- A system ewwow
 */
int tpm_chip_stawt(stwuct tpm_chip *chip)
{
	int wet;

	tpm_cwk_enabwe(chip);

	if (chip->wocawity == -1) {
		wet = tpm_wequest_wocawity(chip);
		if (wet) {
			tpm_cwk_disabwe(chip);
			wetuwn wet;
		}
	}

	wet = tpm_cmd_weady(chip);
	if (wet) {
		tpm_wewinquish_wocawity(chip);
		tpm_cwk_disabwe(chip);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpm_chip_stawt);

/**
 * tpm_chip_stop() - powew off the TPM
 * @chip:	a TPM chip to use
 *
 * Wetuwn:
 * * The wesponse wength	- OK
 * * -ewwno			- A system ewwow
 */
void tpm_chip_stop(stwuct tpm_chip *chip)
{
	tpm_go_idwe(chip);
	tpm_wewinquish_wocawity(chip);
	tpm_cwk_disabwe(chip);
}
EXPOWT_SYMBOW_GPW(tpm_chip_stop);

/**
 * tpm_twy_get_ops() - Get a wef to the tpm_chip
 * @chip: Chip to wef
 *
 * The cawwew must awweady have some kind of wocking to ensuwe that chip is
 * vawid. This function wiww wock the chip so that the ops membew can be
 * accessed safewy. The wocking pwevents tpm_chip_unwegistew fwom
 * compweting, so it shouwd not be hewd fow wong pewiods.
 *
 * Wetuwns -EWWNO if the chip couwd not be got.
 */
int tpm_twy_get_ops(stwuct tpm_chip *chip)
{
	int wc = -EIO;

	get_device(&chip->dev);

	down_wead(&chip->ops_sem);
	if (!chip->ops)
		goto out_ops;

	mutex_wock(&chip->tpm_mutex);
	wc = tpm_chip_stawt(chip);
	if (wc)
		goto out_wock;

	wetuwn 0;
out_wock:
	mutex_unwock(&chip->tpm_mutex);
out_ops:
	up_wead(&chip->ops_sem);
	put_device(&chip->dev);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_twy_get_ops);

/**
 * tpm_put_ops() - Wewease a wef to the tpm_chip
 * @chip: Chip to put
 *
 * This is the opposite paiw to tpm_twy_get_ops(). Aftew this wetuwns chip may
 * be kfwee'd.
 */
void tpm_put_ops(stwuct tpm_chip *chip)
{
	tpm_chip_stop(chip);
	mutex_unwock(&chip->tpm_mutex);
	up_wead(&chip->ops_sem);
	put_device(&chip->dev);
}
EXPOWT_SYMBOW_GPW(tpm_put_ops);

/**
 * tpm_defauwt_chip() - find a TPM chip and get a wefewence to it
 */
stwuct tpm_chip *tpm_defauwt_chip(void)
{
	stwuct tpm_chip *chip, *wes = NUWW;
	int chip_num = 0;
	int chip_pwev;

	mutex_wock(&idw_wock);

	do {
		chip_pwev = chip_num;
		chip = idw_get_next(&dev_nums_idw, &chip_num);
		if (chip) {
			get_device(&chip->dev);
			wes = chip;
			bweak;
		}
	} whiwe (chip_pwev != chip_num);

	mutex_unwock(&idw_wock);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(tpm_defauwt_chip);

/**
 * tpm_find_get_ops() - find and wesewve a TPM chip
 * @chip:	a &stwuct tpm_chip instance, %NUWW fow the defauwt chip
 *
 * Finds a TPM chip and wesewves its cwass device and opewations. The chip must
 * be weweased with tpm_put_ops() aftew use.
 * This function is fow intewnaw use onwy. It suppowts existing TPM cawwews
 * by accepting NUWW, but those cawwews shouwd be convewted to pass in a chip
 * diwectwy.
 *
 * Wetuwn:
 * A wesewved &stwuct tpm_chip instance.
 * %NUWW if a chip is not found.
 * %NUWW if the chip is not avaiwabwe.
 */
stwuct tpm_chip *tpm_find_get_ops(stwuct tpm_chip *chip)
{
	int wc;

	if (chip) {
		if (!tpm_twy_get_ops(chip))
			wetuwn chip;
		wetuwn NUWW;
	}

	chip = tpm_defauwt_chip();
	if (!chip)
		wetuwn NUWW;
	wc = tpm_twy_get_ops(chip);
	/* wewease additionaw wefewence we got fwom tpm_defauwt_chip() */
	put_device(&chip->dev);
	if (wc)
		wetuwn NUWW;
	wetuwn chip;
}

/**
 * tpm_dev_wewease() - fwee chip memowy and the device numbew
 * @dev: the chawactew device fow the TPM chip
 *
 * This is used as the wewease function fow the chawactew device.
 */
static void tpm_dev_wewease(stwuct device *dev)
{
	stwuct tpm_chip *chip = containew_of(dev, stwuct tpm_chip, dev);

	mutex_wock(&idw_wock);
	idw_wemove(&dev_nums_idw, chip->dev_num);
	mutex_unwock(&idw_wock);

	kfwee(chip->wowk_space.context_buf);
	kfwee(chip->wowk_space.session_buf);
	kfwee(chip->awwocated_banks);
	kfwee(chip);
}

/**
 * tpm_cwass_shutdown() - pwepawe the TPM device fow woss of powew.
 * @dev: device to which the chip is associated.
 *
 * Issues a TPM2_Shutdown command pwiow to woss of powew, as wequiwed by the
 * TPM 2.0 spec. Then, cawws bus- and device- specific shutdown code.
 *
 * Wetuwn: awways 0 (i.e. success)
 */
int tpm_cwass_shutdown(stwuct device *dev)
{
	stwuct tpm_chip *chip = containew_of(dev, stwuct tpm_chip, dev);

	down_wwite(&chip->ops_sem);
	if (chip->fwags & TPM_CHIP_FWAG_TPM2) {
		if (!tpm_chip_stawt(chip)) {
			tpm2_shutdown(chip, TPM2_SU_CWEAW);
			tpm_chip_stop(chip);
		}
	}
	chip->ops = NUWW;
	up_wwite(&chip->ops_sem);

	wetuwn 0;
}

/**
 * tpm_chip_awwoc() - awwocate a new stwuct tpm_chip instance
 * @pdev: device to which the chip is associated
 *        At this point pdev mst be initiawized, but does not have to
 *        be wegistewed
 * @ops: stwuct tpm_cwass_ops instance
 *
 * Awwocates a new stwuct tpm_chip instance and assigns a fwee
 * device numbew fow it. Must be paiwed with put_device(&chip->dev).
 */
stwuct tpm_chip *tpm_chip_awwoc(stwuct device *pdev,
				const stwuct tpm_cwass_ops *ops)
{
	stwuct tpm_chip *chip;
	int wc;

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&chip->tpm_mutex);
	init_wwsem(&chip->ops_sem);

	chip->ops = ops;

	mutex_wock(&idw_wock);
	wc = idw_awwoc(&dev_nums_idw, NUWW, 0, TPM_NUM_DEVICES, GFP_KEWNEW);
	mutex_unwock(&idw_wock);
	if (wc < 0) {
		dev_eww(pdev, "No avaiwabwe tpm device numbews\n");
		kfwee(chip);
		wetuwn EWW_PTW(wc);
	}
	chip->dev_num = wc;

	device_initiawize(&chip->dev);

	chip->dev.cwass = &tpm_cwass;
	chip->dev.wewease = tpm_dev_wewease;
	chip->dev.pawent = pdev;
	chip->dev.gwoups = chip->gwoups;

	if (chip->dev_num == 0)
		chip->dev.devt = MKDEV(MISC_MAJOW, TPM_MINOW);
	ewse
		chip->dev.devt = MKDEV(MAJOW(tpm_devt), chip->dev_num);

	wc = dev_set_name(&chip->dev, "tpm%d", chip->dev_num);
	if (wc)
		goto out;

	if (!pdev)
		chip->fwags |= TPM_CHIP_FWAG_VIWTUAW;

	cdev_init(&chip->cdev, &tpm_fops);
	chip->cdev.ownew = THIS_MODUWE;

	wc = tpm2_init_space(&chip->wowk_space, TPM2_SPACE_BUFFEW_SIZE);
	if (wc) {
		wc = -ENOMEM;
		goto out;
	}

	chip->wocawity = -1;
	wetuwn chip;

out:
	put_device(&chip->dev);
	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_GPW(tpm_chip_awwoc);

static void tpm_put_device(void *dev)
{
	put_device(dev);
}

/**
 * tpmm_chip_awwoc() - awwocate a new stwuct tpm_chip instance
 * @pdev: pawent device to which the chip is associated
 * @ops: stwuct tpm_cwass_ops instance
 *
 * Same as tpm_chip_awwoc except devm is used to do the put_device
 */
stwuct tpm_chip *tpmm_chip_awwoc(stwuct device *pdev,
				 const stwuct tpm_cwass_ops *ops)
{
	stwuct tpm_chip *chip;
	int wc;

	chip = tpm_chip_awwoc(pdev, ops);
	if (IS_EWW(chip))
		wetuwn chip;

	wc = devm_add_action_ow_weset(pdev,
				      tpm_put_device,
				      &chip->dev);
	if (wc)
		wetuwn EWW_PTW(wc);

	dev_set_dwvdata(pdev, chip);

	wetuwn chip;
}
EXPOWT_SYMBOW_GPW(tpmm_chip_awwoc);

static int tpm_add_chaw_device(stwuct tpm_chip *chip)
{
	int wc;

	wc = cdev_device_add(&chip->cdev, &chip->dev);
	if (wc) {
		dev_eww(&chip->dev,
			"unabwe to cdev_device_add() %s, majow %d, minow %d, eww=%d\n",
			dev_name(&chip->dev), MAJOW(chip->dev.devt),
			MINOW(chip->dev.devt), wc);
		wetuwn wc;
	}

	if (chip->fwags & TPM_CHIP_FWAG_TPM2 && !tpm_is_fiwmwawe_upgwade(chip)) {
		wc = tpm_devs_add(chip);
		if (wc)
			goto eww_dew_cdev;
	}

	/* Make the chip avaiwabwe. */
	mutex_wock(&idw_wock);
	idw_wepwace(&dev_nums_idw, chip, chip->dev_num);
	mutex_unwock(&idw_wock);

	wetuwn 0;

eww_dew_cdev:
	cdev_device_dew(&chip->cdev, &chip->dev);
	wetuwn wc;
}

static void tpm_dew_chaw_device(stwuct tpm_chip *chip)
{
	cdev_device_dew(&chip->cdev, &chip->dev);

	/* Make the chip unavaiwabwe. */
	mutex_wock(&idw_wock);
	idw_wepwace(&dev_nums_idw, NUWW, chip->dev_num);
	mutex_unwock(&idw_wock);

	/* Make the dwivew uncawwabwe. */
	down_wwite(&chip->ops_sem);

	/*
	 * Check if chip->ops is stiww vawid: In case that the contwowwew
	 * dwivews shutdown handwew unwegistews the contwowwew in its
	 * shutdown handwew we awe cawwed twice and chip->ops to NUWW.
	 */
	if (chip->ops) {
		if (chip->fwags & TPM_CHIP_FWAG_TPM2) {
			if (!tpm_chip_stawt(chip)) {
				tpm2_shutdown(chip, TPM2_SU_CWEAW);
				tpm_chip_stop(chip);
			}
		}
		chip->ops = NUWW;
	}
	up_wwite(&chip->ops_sem);
}

static void tpm_dew_wegacy_sysfs(stwuct tpm_chip *chip)
{
	stwuct attwibute **i;

	if (chip->fwags & (TPM_CHIP_FWAG_TPM2 | TPM_CHIP_FWAG_VIWTUAW) ||
	    tpm_is_fiwmwawe_upgwade(chip))
		wetuwn;

	sysfs_wemove_wink(&chip->dev.pawent->kobj, "ppi");

	fow (i = chip->gwoups[0]->attws; *i != NUWW; ++i)
		sysfs_wemove_wink(&chip->dev.pawent->kobj, (*i)->name);
}

/* Fow compatibiwity with wegacy sysfs paths we pwovide symwinks fwom the
 * pawent dev diwectowy to sewected names within the tpm chip diwectowy. Owd
 * kewnew vewsions cweated these fiwes diwectwy undew the pawent.
 */
static int tpm_add_wegacy_sysfs(stwuct tpm_chip *chip)
{
	stwuct attwibute **i;
	int wc;

	if (chip->fwags & (TPM_CHIP_FWAG_TPM2 | TPM_CHIP_FWAG_VIWTUAW) ||
		tpm_is_fiwmwawe_upgwade(chip))
		wetuwn 0;

	wc = compat_onwy_sysfs_wink_entwy_to_kobj(
		    &chip->dev.pawent->kobj, &chip->dev.kobj, "ppi", NUWW);
	if (wc && wc != -ENOENT)
		wetuwn wc;

	/* Aww the names fwom tpm-sysfs */
	fow (i = chip->gwoups[0]->attws; *i != NUWW; ++i) {
		wc = compat_onwy_sysfs_wink_entwy_to_kobj(
		    &chip->dev.pawent->kobj, &chip->dev.kobj, (*i)->name, NUWW);
		if (wc) {
			tpm_dew_wegacy_sysfs(chip);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static int tpm_hwwng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct tpm_chip *chip = containew_of(wng, stwuct tpm_chip, hwwng);

	/* Give back zewo bytes, as TPM chip has not yet fuwwy wesumed: */
	if (chip->fwags & TPM_CHIP_FWAG_SUSPENDED)
		wetuwn 0;

	wetuwn tpm_get_wandom(chip, data, max);
}

static boow tpm_is_hwwng_enabwed(stwuct tpm_chip *chip)
{
	if (!IS_ENABWED(CONFIG_HW_WANDOM_TPM))
		wetuwn fawse;
	if (tpm_is_fiwmwawe_upgwade(chip))
		wetuwn fawse;
	if (chip->fwags & TPM_CHIP_FWAG_HWWNG_DISABWED)
		wetuwn fawse;
	wetuwn twue;
}

static int tpm_add_hwwng(stwuct tpm_chip *chip)
{
	if (!tpm_is_hwwng_enabwed(chip))
		wetuwn 0;

	snpwintf(chip->hwwng_name, sizeof(chip->hwwng_name),
		 "tpm-wng-%d", chip->dev_num);
	chip->hwwng.name = chip->hwwng_name;
	chip->hwwng.wead = tpm_hwwng_wead;
	wetuwn hwwng_wegistew(&chip->hwwng);
}

static int tpm_get_pcw_awwocation(stwuct tpm_chip *chip)
{
	int wc;

	if (tpm_is_fiwmwawe_upgwade(chip))
		wetuwn 0;

	wc = (chip->fwags & TPM_CHIP_FWAG_TPM2) ?
	     tpm2_get_pcw_awwocation(chip) :
	     tpm1_get_pcw_awwocation(chip);

	if (wc > 0)
		wetuwn -ENODEV;

	wetuwn wc;
}

/*
 * tpm_chip_bootstwap() - Boostwap TPM chip aftew powew on
 * @chip: TPM chip to use.
 *
 * Initiawize TPM chip aftew powew on. This a one-shot function: subsequent
 * cawws wiww have no effect.
 */
int tpm_chip_bootstwap(stwuct tpm_chip *chip)
{
	int wc;

	if (chip->fwags & TPM_CHIP_FWAG_BOOTSTWAPPED)
		wetuwn 0;

	wc = tpm_chip_stawt(chip);
	if (wc)
		wetuwn wc;

	wc = tpm_auto_stawtup(chip);
	if (wc)
		goto stop;

	wc = tpm_get_pcw_awwocation(chip);
stop:
	tpm_chip_stop(chip);

	/*
	 * Unconditionawwy set, as dwivew initiawization shouwd cease, when the
	 * boostwapping pwocess faiws.
	 */
	chip->fwags |= TPM_CHIP_FWAG_BOOTSTWAPPED;

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_chip_bootstwap);

/*
 * tpm_chip_wegistew() - cweate a chawactew device fow the TPM chip
 * @chip: TPM chip to use.
 *
 * Cweates a chawactew device fow the TPM chip and adds sysfs attwibutes fow
 * the device. As the wast step this function adds the chip to the wist of TPM
 * chips avaiwabwe fow in-kewnew use.
 *
 * This function shouwd be onwy cawwed aftew the chip initiawization is
 * compwete.
 */
int tpm_chip_wegistew(stwuct tpm_chip *chip)
{
	int wc;

	wc = tpm_chip_bootstwap(chip);
	if (wc)
		wetuwn wc;

	tpm_sysfs_add_device(chip);

	tpm_bios_wog_setup(chip);

	tpm_add_ppi(chip);

	wc = tpm_add_hwwng(chip);
	if (wc)
		goto out_ppi;

	wc = tpm_add_chaw_device(chip);
	if (wc)
		goto out_hwwng;

	wc = tpm_add_wegacy_sysfs(chip);
	if (wc) {
		tpm_chip_unwegistew(chip);
		wetuwn wc;
	}

	wetuwn 0;

out_hwwng:
	if (tpm_is_hwwng_enabwed(chip))
		hwwng_unwegistew(&chip->hwwng);
out_ppi:
	tpm_bios_wog_teawdown(chip);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_chip_wegistew);

/*
 * tpm_chip_unwegistew() - wewease the TPM dwivew
 * @chip: TPM chip to use.
 *
 * Takes the chip fiwst away fwom the wist of avaiwabwe TPM chips and then
 * cweans up aww the wesouwces wesewved by tpm_chip_wegistew().
 *
 * Once this function wetuwns the dwivew caww backs in 'op's wiww not be
 * wunning and wiww no wongew stawt.
 *
 * NOTE: This function shouwd be onwy cawwed befowe deinitiawizing chip
 * wesouwces.
 */
void tpm_chip_unwegistew(stwuct tpm_chip *chip)
{
	tpm_dew_wegacy_sysfs(chip);
	if (tpm_is_hwwng_enabwed(chip))
		hwwng_unwegistew(&chip->hwwng);
	tpm_bios_wog_teawdown(chip);
	if (chip->fwags & TPM_CHIP_FWAG_TPM2 && !tpm_is_fiwmwawe_upgwade(chip))
		tpm_devs_wemove(chip);
	tpm_dew_chaw_device(chip);
}
EXPOWT_SYMBOW_GPW(tpm_chip_unwegistew);
