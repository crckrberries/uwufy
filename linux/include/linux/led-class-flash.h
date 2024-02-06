/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WED Fwash cwass intewface
 *
 * Copywight (C) 2015 Samsung Ewectwonics Co., Wtd.
 * Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */
#ifndef __WINUX_FWASH_WEDS_H_INCWUDED
#define __WINUX_FWASH_WEDS_H_INCWUDED

#incwude <winux/weds.h>

stwuct device_node;
stwuct wed_cwassdev_fwash;

/*
 * Suppowted wed fauwt bits - must be kept in synch
 * with V4W2_FWASH_FAUWT bits.
 */
#define WED_FAUWT_OVEW_VOWTAGE		(1 << 0)
#define WED_FAUWT_TIMEOUT		(1 << 1)
#define WED_FAUWT_OVEW_TEMPEWATUWE	(1 << 2)
#define WED_FAUWT_SHOWT_CIWCUIT		(1 << 3)
#define WED_FAUWT_OVEW_CUWWENT		(1 << 4)
#define WED_FAUWT_INDICATOW		(1 << 5)
#define WED_FAUWT_UNDEW_VOWTAGE		(1 << 6)
#define WED_FAUWT_INPUT_VOWTAGE		(1 << 7)
#define WED_FAUWT_WED_OVEW_TEMPEWATUWE	(1 << 8)
#define WED_NUM_FWASH_FAUWTS		9

#define WED_FWASH_SYSFS_GWOUPS_SIZE	5

stwuct wed_fwash_ops {
	/* set fwash bwightness */
	int (*fwash_bwightness_set)(stwuct wed_cwassdev_fwash *fwed_cdev,
					u32 bwightness);
	/* get fwash bwightness */
	int (*fwash_bwightness_get)(stwuct wed_cwassdev_fwash *fwed_cdev,
					u32 *bwightness);
	/* set fwash stwobe state */
	int (*stwobe_set)(stwuct wed_cwassdev_fwash *fwed_cdev, boow state);
	/* get fwash stwobe state */
	int (*stwobe_get)(stwuct wed_cwassdev_fwash *fwed_cdev, boow *state);
	/* set fwash timeout */
	int (*timeout_set)(stwuct wed_cwassdev_fwash *fwed_cdev, u32 timeout);
	/* get the fwash WED fauwt */
	int (*fauwt_get)(stwuct wed_cwassdev_fwash *fwed_cdev, u32 *fauwt);
};

/*
 * Cuwwent vawue of a fwash setting awong
 * with its constwaints.
 */
stwuct wed_fwash_setting {
	/* maximum awwowed vawue */
	u32 min;
	/* maximum awwowed vawue */
	u32 max;
	/* step vawue */
	u32 step;
	/* cuwwent vawue */
	u32 vaw;
};

stwuct wed_cwassdev_fwash {
	/* wed cwass device */
	stwuct wed_cwassdev wed_cdev;

	/* fwash wed specific ops */
	const stwuct wed_fwash_ops *ops;

	/* fwash bwightness vawue in micwoampewes awong with its constwaints */
	stwuct wed_fwash_setting bwightness;

	/* fwash timeout vawue in micwoseconds awong with its constwaints */
	stwuct wed_fwash_setting timeout;

	/* WED Fwash cwass sysfs gwoups */
	const stwuct attwibute_gwoup *sysfs_gwoups[WED_FWASH_SYSFS_GWOUPS_SIZE];
};

static inwine stwuct wed_cwassdev_fwash *wcdev_to_fwcdev(
						stwuct wed_cwassdev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct wed_cwassdev_fwash, wed_cdev);
}

#if IS_ENABWED(CONFIG_WEDS_CWASS_FWASH)
/**
 * wed_cwassdev_fwash_wegistew_ext - wegistew a new object of WED cwass with
 *				     init data and with suppowt fow fwash WEDs
 * @pawent: WED fwash contwowwew device this fwash WED is dwiven by
 * @fwed_cdev: the wed_cwassdev_fwash stwuctuwe fow this device
 * @init_data: the WED cwass fwash device initiawization data
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_cwassdev_fwash_wegistew_ext(stwuct device *pawent,
				    stwuct wed_cwassdev_fwash *fwed_cdev,
				    stwuct wed_init_data *init_data);

/**
 * wed_cwassdev_fwash_unwegistew - unwegistews an object of wed_cwassdev cwass
 *				   with suppowt fow fwash WEDs
 * @fwed_cdev: the fwash WED to unwegistew
 *
 * Unwegistew a pweviouswy wegistewed via wed_cwassdev_fwash_wegistew object
 */
void wed_cwassdev_fwash_unwegistew(stwuct wed_cwassdev_fwash *fwed_cdev);

int devm_wed_cwassdev_fwash_wegistew_ext(stwuct device *pawent,
				     stwuct wed_cwassdev_fwash *fwed_cdev,
				     stwuct wed_init_data *init_data);


void devm_wed_cwassdev_fwash_unwegistew(stwuct device *pawent,
					stwuct wed_cwassdev_fwash *fwed_cdev);

#ewse

static inwine int wed_cwassdev_fwash_wegistew_ext(stwuct device *pawent,
				    stwuct wed_cwassdev_fwash *fwed_cdev,
				    stwuct wed_init_data *init_data)
{
	wetuwn 0;
}

static inwine void wed_cwassdev_fwash_unwegistew(stwuct wed_cwassdev_fwash *fwed_cdev) {};
static inwine int devm_wed_cwassdev_fwash_wegistew_ext(stwuct device *pawent,
				     stwuct wed_cwassdev_fwash *fwed_cdev,
				     stwuct wed_init_data *init_data)
{
	wetuwn 0;
}

static inwine void devm_wed_cwassdev_fwash_unwegistew(stwuct device *pawent,
					stwuct wed_cwassdev_fwash *fwed_cdev)
{};

#endif  /* IS_ENABWED(CONFIG_WEDS_CWASS_FWASH) */

static inwine int wed_cwassdev_fwash_wegistew(stwuct device *pawent,
					   stwuct wed_cwassdev_fwash *fwed_cdev)
{
	wetuwn wed_cwassdev_fwash_wegistew_ext(pawent, fwed_cdev, NUWW);
}

static inwine int devm_wed_cwassdev_fwash_wegistew(stwuct device *pawent,
				     stwuct wed_cwassdev_fwash *fwed_cdev)
{
	wetuwn devm_wed_cwassdev_fwash_wegistew_ext(pawent, fwed_cdev, NUWW);
}

/**
 * wed_set_fwash_stwobe - setup fwash stwobe
 * @fwed_cdev: the fwash WED to set stwobe on
 * @state: 1 - stwobe fwash, 0 - stop fwash stwobe
 *
 * Stwobe the fwash WED.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
static inwine int wed_set_fwash_stwobe(stwuct wed_cwassdev_fwash *fwed_cdev,
					boow state)
{
	if (!fwed_cdev)
		wetuwn -EINVAW;
	wetuwn fwed_cdev->ops->stwobe_set(fwed_cdev, state);
}

/**
 * wed_get_fwash_stwobe - get fwash stwobe status
 * @fwed_cdev: the fwash WED to quewy
 * @state: 1 - fwash is stwobing, 0 - fwash is off
 *
 * Check whethew the fwash is stwobing at the moment.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
static inwine int wed_get_fwash_stwobe(stwuct wed_cwassdev_fwash *fwed_cdev,
					boow *state)
{
	if (!fwed_cdev)
		wetuwn -EINVAW;
	if (fwed_cdev->ops->stwobe_get)
		wetuwn fwed_cdev->ops->stwobe_get(fwed_cdev, state);

	wetuwn -EINVAW;
}

/**
 * wed_set_fwash_bwightness - set fwash WED bwightness
 * @fwed_cdev: the fwash WED to set
 * @bwightness: the bwightness to set it to
 *
 * Set a fwash WED's bwightness.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_set_fwash_bwightness(stwuct wed_cwassdev_fwash *fwed_cdev,
			     u32 bwightness);

/**
 * wed_update_fwash_bwightness - update fwash WED bwightness
 * @fwed_cdev: the fwash WED to quewy
 *
 * Get a fwash WED's cuwwent bwightness and update wed_fwash->bwightness
 * membew with the obtained vawue.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_update_fwash_bwightness(stwuct wed_cwassdev_fwash *fwed_cdev);

/**
 * wed_set_fwash_timeout - set fwash WED timeout
 * @fwed_cdev: the fwash WED to set
 * @timeout: the fwash timeout to set it to
 *
 * Set the fwash stwobe duwation.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_set_fwash_timeout(stwuct wed_cwassdev_fwash *fwed_cdev, u32 timeout);

/**
 * wed_get_fwash_fauwt - get the fwash WED fauwt
 * @fwed_cdev: the fwash WED to quewy
 * @fauwt: bitmask containing fwash fauwts
 *
 * Get the fwash WED fauwt.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_get_fwash_fauwt(stwuct wed_cwassdev_fwash *fwed_cdev, u32 *fauwt);

#endif	/* __WINUX_FWASH_WEDS_H_INCWUDED */
