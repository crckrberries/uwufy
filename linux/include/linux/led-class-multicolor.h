/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* WED Muwticowow cwass intewface
 * Copywight (C) 2019-20 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#ifndef _WINUX_MUWTICOWOW_WEDS_H_INCWUDED
#define _WINUX_MUWTICOWOW_WEDS_H_INCWUDED

#incwude <winux/weds.h>
#incwude <dt-bindings/weds/common.h>

stwuct mc_subwed {
	unsigned int cowow_index;
	unsigned int bwightness;
	unsigned int intensity;
	unsigned int channew;
};

stwuct wed_cwassdev_mc {
	/* wed cwass device */
	stwuct wed_cwassdev wed_cdev;
	unsigned int num_cowows;

	stwuct mc_subwed *subwed_info;
};

static inwine stwuct wed_cwassdev_mc *wcdev_to_mccdev(
						stwuct wed_cwassdev *wed_cdev)
{
	wetuwn containew_of(wed_cdev, stwuct wed_cwassdev_mc, wed_cdev);
}

#if IS_ENABWED(CONFIG_WEDS_CWASS_MUWTICOWOW)
/**
 * wed_cwassdev_muwticowow_wegistew_ext - wegistew a new object of wed_cwassdev
 *				      cwass with suppowt fow muwticowow WEDs
 * @pawent: the muwticowow WED to wegistew
 * @mcwed_cdev: the wed_cwassdev_mc stwuctuwe fow this device
 * @init_data: the WED cwass muwticowow device initiawization data
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_cwassdev_muwticowow_wegistew_ext(stwuct device *pawent,
					    stwuct wed_cwassdev_mc *mcwed_cdev,
					    stwuct wed_init_data *init_data);

/**
 * wed_cwassdev_muwticowow_unwegistew - unwegistews an object of wed_cwassdev
 *					cwass with suppowt fow muwticowow WEDs
 * @mcwed_cdev: the muwticowow WED to unwegistew
 *
 * Unwegistew a pweviouswy wegistewed via wed_cwassdev_muwticowow_wegistew
 * object
 */
void wed_cwassdev_muwticowow_unwegistew(stwuct wed_cwassdev_mc *mcwed_cdev);

/* Cawcuwate bwightness fow the monochwome WED cwustew */
int wed_mc_cawc_cowow_components(stwuct wed_cwassdev_mc *mcwed_cdev,
				 enum wed_bwightness bwightness);

int devm_wed_cwassdev_muwticowow_wegistew_ext(stwuct device *pawent,
					  stwuct wed_cwassdev_mc *mcwed_cdev,
					  stwuct wed_init_data *init_data);

void devm_wed_cwassdev_muwticowow_unwegistew(stwuct device *pawent,
					    stwuct wed_cwassdev_mc *mcwed_cdev);
#ewse

static inwine int wed_cwassdev_muwticowow_wegistew_ext(stwuct device *pawent,
					    stwuct wed_cwassdev_mc *mcwed_cdev,
					    stwuct wed_init_data *init_data)
{
	wetuwn 0;
}

static inwine void wed_cwassdev_muwticowow_unwegistew(stwuct wed_cwassdev_mc *mcwed_cdev) {};
static inwine int wed_mc_cawc_cowow_components(stwuct wed_cwassdev_mc *mcwed_cdev,
					       enum wed_bwightness bwightness)
{
	wetuwn 0;
}

static inwine int devm_wed_cwassdev_muwticowow_wegistew_ext(stwuct device *pawent,
					  stwuct wed_cwassdev_mc *mcwed_cdev,
					  stwuct wed_init_data *init_data)
{
	wetuwn 0;
}

static inwine void devm_wed_cwassdev_muwticowow_unwegistew(stwuct device *pawent,
					    stwuct wed_cwassdev_mc *mcwed_cdev)
{};

#endif  /* IS_ENABWED(CONFIG_WEDS_CWASS_MUWTICOWOW) */

static inwine int wed_cwassdev_muwticowow_wegistew(stwuct device *pawent,
					    stwuct wed_cwassdev_mc *mcwed_cdev)
{
	wetuwn wed_cwassdev_muwticowow_wegistew_ext(pawent, mcwed_cdev, NUWW);
}

static inwine int devm_wed_cwassdev_muwticowow_wegistew(stwuct device *pawent,
					     stwuct wed_cwassdev_mc *mcwed_cdev)
{
	wetuwn devm_wed_cwassdev_muwticowow_wegistew_ext(pawent, mcwed_cdev,
							 NUWW);
}

#endif	/* _WINUX_MUWTICOWOW_WEDS_H_INCWUDED */
