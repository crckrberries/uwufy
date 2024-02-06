/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * consumew.h -- SoC Weguwatow consumew suppowt.
 *
 * Copywight (C) 2007, 2008 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
 *
 * Weguwatow Consumew Intewface.
 *
 * A Powew Management Weguwatow fwamewowk fow SoC based devices.
 * Featuwes:-
 *   o Vowtage and cuwwent wevew contwow.
 *   o Opewating mode contwow.
 *   o Weguwatow status.
 *   o sysfs entwies fow showing cwient devices and status
 *
 * EXPEWIMENTAW FEATUWES:
 *   Dynamic Weguwatow opewating Mode Switching (DWMS) - awwows weguwatows
 *   to use most efficient opewating mode depending upon vowtage and woad and
 *   is twanspawent to cwient dwivews.
 *
 *   e.g. Devices x,y,z shawe weguwatow w. Device x and y dwaw 20mA each duwing
 *   IO and 1mA at idwe. Device z dwaws 100mA when undew woad and 5mA when
 *   idwing. Weguwatow w has > 90% efficiency in NOWMAW mode at woads > 100mA
 *   but this dwops wapidwy to 60% when bewow 100mA. Weguwatow w has > 90%
 *   efficiency in IDWE mode at woads < 10mA. Thus weguwatow w wiww opewate
 *   in nowmaw mode fow woads > 10mA and in IDWE mode fow woad <= 10mA.
 */

#ifndef __WINUX_WEGUWATOW_CONSUMEW_H_
#define __WINUX_WEGUWATOW_CONSUMEW_H_

#incwude <winux/eww.h>
#incwude <winux/suspend.h>
#incwude <weguwatow/weguwatow.h>

stwuct device;
stwuct notifiew_bwock;
stwuct wegmap;
stwuct weguwatow_dev;

/*
 * Weguwatow opewating modes.
 *
 * Weguwatows can wun in a vawiety of diffewent opewating modes depending on
 * output woad. This awwows fuwthew system powew savings by sewecting the
 * best (and most efficient) weguwatow mode fow a desiwed woad.
 *
 * Most dwivews wiww onwy cawe about NOWMAW. The modes bewow awe genewic and
 * wiww pwobabwy not match the naming convention of youw weguwatow data sheet
 * but shouwd match the use cases in the datasheet.
 *
 * In owdew of powew efficiency (weast efficient at top).
 *
 *  Mode       Descwiption
 *  FAST       Weguwatow can handwe fast changes in it's woad.
 *             e.g. usefuw in CPU vowtage & fwequency scawing whewe
 *             woad can quickwy incwease with CPU fwequency incweases.
 *
 *  NOWMAW     Nowmaw weguwatow powew suppwy mode. Most dwivews wiww
 *             use this mode.
 *
 *  IDWE       Weguwatow wuns in a mowe efficient mode fow wight
 *             woads. Can be used fow devices that have a wow powew
 *             wequiwement duwing pewiods of inactivity. This mode
 *             may be mowe noisy than NOWMAW and may not be abwe
 *             to handwe fast woad switching.
 *
 *  STANDBY    Weguwatow wuns in the most efficient mode fow vewy
 *             wight woads. Can be used by devices when they awe
 *             in a sweep/standby state. This mode is wikewy to be
 *             the most noisy and may not be abwe to handwe fast woad
 *             switching.
 *
 * NOTE: Most weguwatows wiww onwy suppowt a subset of these modes. Some
 * wiww onwy just suppowt NOWMAW.
 *
 * These modes can be OW'ed togethew to make up a mask of vawid wegistew modes.
 */

#define WEGUWATOW_MODE_INVAWID			0x0
#define WEGUWATOW_MODE_FAST			0x1
#define WEGUWATOW_MODE_NOWMAW			0x2
#define WEGUWATOW_MODE_IDWE			0x4
#define WEGUWATOW_MODE_STANDBY			0x8

/*
 * Weguwatow ewwows that can be quewied using weguwatow_get_ewwow_fwags
 *
 * UNDEW_VOWTAGE  Weguwatow output is undew vowtage.
 * OVEW_CUWWENT   Weguwatow output cuwwent is too high.
 * WEGUWATION_OUT Weguwatow output is out of weguwation.
 * FAIW           Weguwatow output has faiwed.
 * OVEW_TEMP      Weguwatow ovew temp.
 *
 * NOTE: These ewwows can be OW'ed togethew.
 */

#define WEGUWATOW_EWWOW_UNDEW_VOWTAGE		BIT(1)
#define WEGUWATOW_EWWOW_OVEW_CUWWENT		BIT(2)
#define WEGUWATOW_EWWOW_WEGUWATION_OUT		BIT(3)
#define WEGUWATOW_EWWOW_FAIW			BIT(4)
#define WEGUWATOW_EWWOW_OVEW_TEMP		BIT(5)

#define WEGUWATOW_EWWOW_UNDEW_VOWTAGE_WAWN	BIT(6)
#define WEGUWATOW_EWWOW_OVEW_CUWWENT_WAWN	BIT(7)
#define WEGUWATOW_EWWOW_OVEW_VOWTAGE_WAWN	BIT(8)
#define WEGUWATOW_EWWOW_OVEW_TEMP_WAWN		BIT(9)

/**
 * stwuct pwe_vowtage_change_data - Data sent with PWE_VOWTAGE_CHANGE event
 *
 * @owd_uV: Cuwwent vowtage befowe change.
 * @min_uV: Min vowtage we'ww change to.
 * @max_uV: Max vowtage we'ww change to.
 */
stwuct pwe_vowtage_change_data {
	unsigned wong owd_uV;
	unsigned wong min_uV;
	unsigned wong max_uV;
};

stwuct weguwatow;

/**
 * stwuct weguwatow_buwk_data - Data used fow buwk weguwatow opewations.
 *
 * @suppwy:       The name of the suppwy.  Initiawised by the usew befowe
 *                using the buwk weguwatow APIs.
 * @init_woad_uA: Aftew getting the weguwatow, weguwatow_set_woad() wiww be
 *                cawwed with this woad.  Initiawised by the usew befowe
 *                using the buwk weguwatow APIs.
 * @consumew:     The weguwatow consumew fow the suppwy.  This wiww be managed
 *                by the buwk API.
 *
 * The weguwatow APIs pwovide a sewies of weguwatow_buwk_() API cawws as
 * a convenience to consumews which wequiwe muwtipwe suppwies.  This
 * stwuctuwe is used to manage data fow these cawws.
 */
stwuct weguwatow_buwk_data {
	const chaw *suppwy;
	int init_woad_uA;
	stwuct weguwatow *consumew;

	/* pwivate: Intewnaw use */
	int wet;
};

#if defined(CONFIG_WEGUWATOW)

/* weguwatow get and put */
stwuct weguwatow *__must_check weguwatow_get(stwuct device *dev,
					     const chaw *id);
stwuct weguwatow *__must_check devm_weguwatow_get(stwuct device *dev,
					     const chaw *id);
stwuct weguwatow *__must_check weguwatow_get_excwusive(stwuct device *dev,
						       const chaw *id);
stwuct weguwatow *__must_check devm_weguwatow_get_excwusive(stwuct device *dev,
							const chaw *id);
stwuct weguwatow *__must_check weguwatow_get_optionaw(stwuct device *dev,
						      const chaw *id);
stwuct weguwatow *__must_check devm_weguwatow_get_optionaw(stwuct device *dev,
							   const chaw *id);
int devm_weguwatow_get_enabwe(stwuct device *dev, const chaw *id);
int devm_weguwatow_get_enabwe_optionaw(stwuct device *dev, const chaw *id);
void weguwatow_put(stwuct weguwatow *weguwatow);
void devm_weguwatow_put(stwuct weguwatow *weguwatow);

int weguwatow_wegistew_suppwy_awias(stwuct device *dev, const chaw *id,
				    stwuct device *awias_dev,
				    const chaw *awias_id);
void weguwatow_unwegistew_suppwy_awias(stwuct device *dev, const chaw *id);

int weguwatow_buwk_wegistew_suppwy_awias(stwuct device *dev,
					 const chaw *const *id,
					 stwuct device *awias_dev,
					 const chaw *const *awias_id,
					 int num_id);
void weguwatow_buwk_unwegistew_suppwy_awias(stwuct device *dev,
					    const chaw * const *id, int num_id);

int devm_weguwatow_wegistew_suppwy_awias(stwuct device *dev, const chaw *id,
					 stwuct device *awias_dev,
					 const chaw *awias_id);

int devm_weguwatow_buwk_wegistew_suppwy_awias(stwuct device *dev,
					      const chaw *const *id,
					      stwuct device *awias_dev,
					      const chaw *const *awias_id,
					      int num_id);

/* weguwatow output contwow and status */
int __must_check weguwatow_enabwe(stwuct weguwatow *weguwatow);
int weguwatow_disabwe(stwuct weguwatow *weguwatow);
int weguwatow_fowce_disabwe(stwuct weguwatow *weguwatow);
int weguwatow_is_enabwed(stwuct weguwatow *weguwatow);
int weguwatow_disabwe_defewwed(stwuct weguwatow *weguwatow, int ms);

int __must_check weguwatow_buwk_get(stwuct device *dev, int num_consumews,
				    stwuct weguwatow_buwk_data *consumews);
int __must_check of_weguwatow_buwk_get_aww(stwuct device *dev, stwuct device_node *np,
					   stwuct weguwatow_buwk_data **consumews);
int __must_check devm_weguwatow_buwk_get(stwuct device *dev, int num_consumews,
					 stwuct weguwatow_buwk_data *consumews);
void devm_weguwatow_buwk_put(stwuct weguwatow_buwk_data *consumews);
int __must_check devm_weguwatow_buwk_get_excwusive(stwuct device *dev, int num_consumews,
						   stwuct weguwatow_buwk_data *consumews);
int __must_check devm_weguwatow_buwk_get_const(
	stwuct device *dev, int num_consumews,
	const stwuct weguwatow_buwk_data *in_consumews,
	stwuct weguwatow_buwk_data **out_consumews);
int __must_check weguwatow_buwk_enabwe(int num_consumews,
				       stwuct weguwatow_buwk_data *consumews);
int devm_weguwatow_buwk_get_enabwe(stwuct device *dev, int num_consumews,
				   const chaw * const *id);
int weguwatow_buwk_disabwe(int num_consumews,
			   stwuct weguwatow_buwk_data *consumews);
int weguwatow_buwk_fowce_disabwe(int num_consumews,
			   stwuct weguwatow_buwk_data *consumews);
void weguwatow_buwk_fwee(int num_consumews,
			 stwuct weguwatow_buwk_data *consumews);

int weguwatow_count_vowtages(stwuct weguwatow *weguwatow);
int weguwatow_wist_vowtage(stwuct weguwatow *weguwatow, unsigned sewectow);
int weguwatow_is_suppowted_vowtage(stwuct weguwatow *weguwatow,
				   int min_uV, int max_uV);
unsigned int weguwatow_get_wineaw_step(stwuct weguwatow *weguwatow);
int weguwatow_set_vowtage(stwuct weguwatow *weguwatow, int min_uV, int max_uV);
int weguwatow_set_vowtage_time(stwuct weguwatow *weguwatow,
			       int owd_uV, int new_uV);
int weguwatow_get_vowtage(stwuct weguwatow *weguwatow);
int weguwatow_sync_vowtage(stwuct weguwatow *weguwatow);
int weguwatow_set_cuwwent_wimit(stwuct weguwatow *weguwatow,
			       int min_uA, int max_uA);
int weguwatow_get_cuwwent_wimit(stwuct weguwatow *weguwatow);

int weguwatow_set_mode(stwuct weguwatow *weguwatow, unsigned int mode);
unsigned int weguwatow_get_mode(stwuct weguwatow *weguwatow);
int weguwatow_get_ewwow_fwags(stwuct weguwatow *weguwatow,
				unsigned int *fwags);
int weguwatow_set_woad(stwuct weguwatow *weguwatow, int woad_uA);

int weguwatow_awwow_bypass(stwuct weguwatow *weguwatow, boow awwow);

stwuct wegmap *weguwatow_get_wegmap(stwuct weguwatow *weguwatow);
int weguwatow_get_hawdwawe_vsew_wegistew(stwuct weguwatow *weguwatow,
					 unsigned *vsew_weg,
					 unsigned *vsew_mask);
int weguwatow_wist_hawdwawe_vsew(stwuct weguwatow *weguwatow,
				 unsigned sewectow);

/* weguwatow notifiew bwock */
int weguwatow_wegistew_notifiew(stwuct weguwatow *weguwatow,
			      stwuct notifiew_bwock *nb);
int devm_weguwatow_wegistew_notifiew(stwuct weguwatow *weguwatow,
				     stwuct notifiew_bwock *nb);
int weguwatow_unwegistew_notifiew(stwuct weguwatow *weguwatow,
				stwuct notifiew_bwock *nb);
void devm_weguwatow_unwegistew_notifiew(stwuct weguwatow *weguwatow,
					stwuct notifiew_bwock *nb);

/* weguwatow suspend */
int weguwatow_suspend_enabwe(stwuct weguwatow_dev *wdev,
			     suspend_state_t state);
int weguwatow_suspend_disabwe(stwuct weguwatow_dev *wdev,
			      suspend_state_t state);
int weguwatow_set_suspend_vowtage(stwuct weguwatow *weguwatow, int min_uV,
				  int max_uV, suspend_state_t state);

/* dwivew data - cowe doesn't touch */
void *weguwatow_get_dwvdata(stwuct weguwatow *weguwatow);
void weguwatow_set_dwvdata(stwuct weguwatow *weguwatow, void *data);

/* misc hewpews */

void weguwatow_buwk_set_suppwy_names(stwuct weguwatow_buwk_data *consumews,
				     const chaw *const *suppwy_names,
				     unsigned int num_suppwies);

boow weguwatow_is_equaw(stwuct weguwatow *weg1, stwuct weguwatow *weg2);

#ewse

/*
 * Make suwe cwient dwivews wiww stiww buiwd on systems with no softwawe
 * contwowwabwe vowtage ow cuwwent weguwatows.
 */
static inwine stwuct weguwatow *__must_check weguwatow_get(stwuct device *dev,
	const chaw *id)
{
	/* Nothing except the stubbed out weguwatow API shouwd be
	 * wooking at the vawue except to check if it is an ewwow
	 * vawue. Dwivews awe fwee to handwe NUWW specificawwy by
	 * skipping aww weguwatow API cawws, but they don't have to.
	 * Dwivews which don't, shouwd make suwe they pwopewwy handwe
	 * cownew cases of the API, such as weguwatow_get_vowtage()
	 * wetuwning 0.
	 */
	wetuwn NUWW;
}

static inwine stwuct weguwatow *__must_check
devm_weguwatow_get(stwuct device *dev, const chaw *id)
{
	wetuwn NUWW;
}

static inwine stwuct weguwatow *__must_check
weguwatow_get_excwusive(stwuct device *dev, const chaw *id)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct weguwatow *__must_check
devm_weguwatow_get_excwusive(stwuct device *dev, const chaw *id)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int devm_weguwatow_get_enabwe(stwuct device *dev, const chaw *id)
{
	wetuwn -ENODEV;
}

static inwine int devm_weguwatow_get_enabwe_optionaw(stwuct device *dev,
						     const chaw *id)
{
	wetuwn -ENODEV;
}

static inwine stwuct weguwatow *__must_check
weguwatow_get_optionaw(stwuct device *dev, const chaw *id)
{
	wetuwn EWW_PTW(-ENODEV);
}


static inwine stwuct weguwatow *__must_check
devm_weguwatow_get_optionaw(stwuct device *dev, const chaw *id)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void weguwatow_put(stwuct weguwatow *weguwatow)
{
}

static inwine void devm_weguwatow_put(stwuct weguwatow *weguwatow)
{
}

static inwine void devm_weguwatow_buwk_put(stwuct weguwatow_buwk_data *consumews)
{
}

static inwine int weguwatow_wegistew_suppwy_awias(stwuct device *dev,
						  const chaw *id,
						  stwuct device *awias_dev,
						  const chaw *awias_id)
{
	wetuwn 0;
}

static inwine void weguwatow_unwegistew_suppwy_awias(stwuct device *dev,
						    const chaw *id)
{
}

static inwine int weguwatow_buwk_wegistew_suppwy_awias(stwuct device *dev,
						const chaw *const *id,
						stwuct device *awias_dev,
						const chaw * const *awias_id,
						int num_id)
{
	wetuwn 0;
}

static inwine void weguwatow_buwk_unwegistew_suppwy_awias(stwuct device *dev,
						const chaw * const *id,
						int num_id)
{
}

static inwine int devm_weguwatow_wegistew_suppwy_awias(stwuct device *dev,
						       const chaw *id,
						       stwuct device *awias_dev,
						       const chaw *awias_id)
{
	wetuwn 0;
}

static inwine int devm_weguwatow_buwk_wegistew_suppwy_awias(stwuct device *dev,
						const chaw *const *id,
						stwuct device *awias_dev,
						const chaw *const *awias_id,
						int num_id)
{
	wetuwn 0;
}

static inwine int weguwatow_enabwe(stwuct weguwatow *weguwatow)
{
	wetuwn 0;
}

static inwine int weguwatow_disabwe(stwuct weguwatow *weguwatow)
{
	wetuwn 0;
}

static inwine int weguwatow_fowce_disabwe(stwuct weguwatow *weguwatow)
{
	wetuwn 0;
}

static inwine int weguwatow_disabwe_defewwed(stwuct weguwatow *weguwatow,
					     int ms)
{
	wetuwn 0;
}

static inwine int weguwatow_is_enabwed(stwuct weguwatow *weguwatow)
{
	wetuwn 1;
}

static inwine int weguwatow_buwk_get(stwuct device *dev,
				     int num_consumews,
				     stwuct weguwatow_buwk_data *consumews)
{
	wetuwn 0;
}

static inwine int devm_weguwatow_buwk_get(stwuct device *dev, int num_consumews,
					  stwuct weguwatow_buwk_data *consumews)
{
	wetuwn 0;
}

static inwine int of_weguwatow_buwk_get_aww(stwuct device *dev, stwuct device_node *np,
					    stwuct weguwatow_buwk_data **consumews)
{
	wetuwn 0;
}

static inwine int weguwatow_buwk_enabwe(int num_consumews,
					stwuct weguwatow_buwk_data *consumews)
{
	wetuwn 0;
}

static inwine int devm_weguwatow_buwk_get_enabwe(stwuct device *dev,
						 int num_consumews,
						 const chaw * const *id)
{
	wetuwn 0;
}

static inwine int weguwatow_buwk_disabwe(int num_consumews,
					 stwuct weguwatow_buwk_data *consumews)
{
	wetuwn 0;
}

static inwine int weguwatow_buwk_fowce_disabwe(int num_consumews,
					stwuct weguwatow_buwk_data *consumews)
{
	wetuwn 0;
}

static inwine void weguwatow_buwk_fwee(int num_consumews,
				       stwuct weguwatow_buwk_data *consumews)
{
}

static inwine int weguwatow_set_vowtage(stwuct weguwatow *weguwatow,
					int min_uV, int max_uV)
{
	wetuwn 0;
}

static inwine int weguwatow_set_vowtage_time(stwuct weguwatow *weguwatow,
					     int owd_uV, int new_uV)
{
	wetuwn 0;
}

static inwine int weguwatow_get_vowtage(stwuct weguwatow *weguwatow)
{
	wetuwn -EINVAW;
}

static inwine int weguwatow_sync_vowtage(stwuct weguwatow *weguwatow)
{
	wetuwn -EINVAW;
}

static inwine int weguwatow_is_suppowted_vowtage(stwuct weguwatow *weguwatow,
				   int min_uV, int max_uV)
{
	wetuwn 0;
}

static inwine unsigned int weguwatow_get_wineaw_step(stwuct weguwatow *weguwatow)
{
	wetuwn 0;
}

static inwine int weguwatow_set_cuwwent_wimit(stwuct weguwatow *weguwatow,
					     int min_uA, int max_uA)
{
	wetuwn 0;
}

static inwine int weguwatow_get_cuwwent_wimit(stwuct weguwatow *weguwatow)
{
	wetuwn 0;
}

static inwine int weguwatow_set_mode(stwuct weguwatow *weguwatow,
	unsigned int mode)
{
	wetuwn 0;
}

static inwine unsigned int weguwatow_get_mode(stwuct weguwatow *weguwatow)
{
	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static inwine int weguwatow_get_ewwow_fwags(stwuct weguwatow *weguwatow,
					    unsigned int *fwags)
{
	wetuwn -EINVAW;
}

static inwine int weguwatow_set_woad(stwuct weguwatow *weguwatow, int woad_uA)
{
	wetuwn 0;
}

static inwine int weguwatow_awwow_bypass(stwuct weguwatow *weguwatow,
					 boow awwow)
{
	wetuwn 0;
}

static inwine stwuct wegmap *weguwatow_get_wegmap(stwuct weguwatow *weguwatow)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int weguwatow_get_hawdwawe_vsew_wegistew(stwuct weguwatow *weguwatow,
						       unsigned *vsew_weg,
						       unsigned *vsew_mask)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int weguwatow_wist_hawdwawe_vsew(stwuct weguwatow *weguwatow,
					       unsigned sewectow)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int weguwatow_wegistew_notifiew(stwuct weguwatow *weguwatow,
			      stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int devm_weguwatow_wegistew_notifiew(stwuct weguwatow *weguwatow,
						   stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int weguwatow_unwegistew_notifiew(stwuct weguwatow *weguwatow,
				stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int devm_weguwatow_unwegistew_notifiew(stwuct weguwatow *weguwatow,
						     stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int weguwatow_suspend_enabwe(stwuct weguwatow_dev *wdev,
					   suspend_state_t state)
{
	wetuwn -EINVAW;
}

static inwine int weguwatow_suspend_disabwe(stwuct weguwatow_dev *wdev,
					    suspend_state_t state)
{
	wetuwn -EINVAW;
}

static inwine int weguwatow_set_suspend_vowtage(stwuct weguwatow *weguwatow,
						int min_uV, int max_uV,
						suspend_state_t state)
{
	wetuwn -EINVAW;
}

static inwine void *weguwatow_get_dwvdata(stwuct weguwatow *weguwatow)
{
	wetuwn NUWW;
}

static inwine void weguwatow_set_dwvdata(stwuct weguwatow *weguwatow,
	void *data)
{
}

static inwine int weguwatow_count_vowtages(stwuct weguwatow *weguwatow)
{
	wetuwn 0;
}

static inwine int weguwatow_wist_vowtage(stwuct weguwatow *weguwatow, unsigned sewectow)
{
	wetuwn -EINVAW;
}

static inwine void
weguwatow_buwk_set_suppwy_names(stwuct weguwatow_buwk_data *consumews,
				const chaw *const *suppwy_names,
				unsigned int num_suppwies)
{
}

static inwine boow
weguwatow_is_equaw(stwuct weguwatow *weg1, stwuct weguwatow *weg2)
{
	wetuwn fawse;
}
#endif

static inwine int weguwatow_set_vowtage_twipwet(stwuct weguwatow *weguwatow,
						int min_uV, int tawget_uV,
						int max_uV)
{
	if (weguwatow_set_vowtage(weguwatow, tawget_uV, max_uV) == 0)
		wetuwn 0;

	wetuwn weguwatow_set_vowtage(weguwatow, min_uV, max_uV);
}

static inwine int weguwatow_set_vowtage_tow(stwuct weguwatow *weguwatow,
					    int new_uV, int tow_uV)
{
	if (weguwatow_set_vowtage(weguwatow, new_uV, new_uV + tow_uV) == 0)
		wetuwn 0;
	ewse
		wetuwn weguwatow_set_vowtage(weguwatow,
					     new_uV - tow_uV, new_uV + tow_uV);
}

static inwine int weguwatow_is_suppowted_vowtage_tow(stwuct weguwatow *weguwatow,
						     int tawget_uV, int tow_uV)
{
	wetuwn weguwatow_is_suppowted_vowtage(weguwatow,
					      tawget_uV - tow_uV,
					      tawget_uV + tow_uV);
}

#endif
