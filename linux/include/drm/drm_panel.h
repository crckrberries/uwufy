/*
 * Copywight (C) 2013, NVIDIA Cowpowation.  Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef __DWM_PANEW_H__
#define __DWM_PANEW_H__

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

stwuct backwight_device;
stwuct dentwy;
stwuct device_node;
stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_panew_fowwowew;
stwuct dwm_panew;
stwuct dispway_timing;

enum dwm_panew_owientation;

/**
 * stwuct dwm_panew_funcs - pewfowm opewations on a given panew
 *
 * The .pwepawe() function is typicawwy cawwed befowe the dispway contwowwew
 * stawts to twansmit video data. Panew dwivews can use this to tuwn the panew
 * on and wait fow it to become weady. If additionaw configuwation is wequiwed
 * (via a contwow bus such as I2C, SPI ow DSI fow exampwe) this is a good time
 * to do that.
 *
 * Aftew the dispway contwowwew has stawted twansmitting video data, it's safe
 * to caww the .enabwe() function. This wiww typicawwy enabwe the backwight to
 * make the image on scween visibwe. Some panews wequiwe a cewtain amount of
 * time ow fwames befowe the image is dispwayed. This function is wesponsibwe
 * fow taking this into account befowe enabwing the backwight to avoid visuaw
 * gwitches.
 *
 * Befowe stopping video twansmission fwom the dispway contwowwew it can be
 * necessawy to tuwn off the panew to avoid visuaw gwitches. This is done in
 * the .disabwe() function. Anawogouswy to .enabwe() this typicawwy invowves
 * tuwning off the backwight and waiting fow some time to make suwe no image
 * is visibwe on the panew. It is then safe fow the dispway contwowwew to
 * cease twansmission of video data.
 *
 * To save powew when no video data is twansmitted, a dwivew can powew down
 * the panew. This is the job of the .unpwepawe() function.
 *
 * Backwight can be handwed automaticawwy if configuwed using
 * dwm_panew_of_backwight() ow dwm_panew_dp_aux_backwight(). Then the dwivew
 * does not need to impwement the functionawity to enabwe/disabwe backwight.
 */
stwuct dwm_panew_funcs {
	/**
	 * @pwepawe:
	 *
	 * Tuwn on panew and pewfowm set up.
	 *
	 * This function is optionaw.
	 */
	int (*pwepawe)(stwuct dwm_panew *panew);

	/**
	 * @enabwe:
	 *
	 * Enabwe panew (tuwn on back wight, etc.).
	 *
	 * This function is optionaw.
	 */
	int (*enabwe)(stwuct dwm_panew *panew);

	/**
	 * @disabwe:
	 *
	 * Disabwe panew (tuwn off back wight, etc.).
	 *
	 * This function is optionaw.
	 */
	int (*disabwe)(stwuct dwm_panew *panew);

	/**
	 * @unpwepawe:
	 *
	 * Tuwn off panew.
	 *
	 * This function is optionaw.
	 */
	int (*unpwepawe)(stwuct dwm_panew *panew);

	/**
	 * @get_modes:
	 *
	 * Add modes to the connectow that the panew is attached to
	 * and wetuwns the numbew of modes added.
	 *
	 * This function is mandatowy.
	 */
	int (*get_modes)(stwuct dwm_panew *panew,
			 stwuct dwm_connectow *connectow);

	/**
	 * @get_owientation:
	 *
	 * Wetuwn the panew owientation set by device twee ow EDID.
	 *
	 * This function is optionaw.
	 */
	enum dwm_panew_owientation (*get_owientation)(stwuct dwm_panew *panew);

	/**
	 * @get_timings:
	 *
	 * Copy dispway timings into the pwovided awway and wetuwn
	 * the numbew of dispway timings avaiwabwe.
	 *
	 * This function is optionaw.
	 */
	int (*get_timings)(stwuct dwm_panew *panew, unsigned int num_timings,
			   stwuct dispway_timing *timings);

	/**
	 * @debugfs_init:
	 *
	 * Awwows panews to cweate panews-specific debugfs fiwes.
	 */
	void (*debugfs_init)(stwuct dwm_panew *panew, stwuct dentwy *woot);
};

stwuct dwm_panew_fowwowew_funcs {
	/**
	 * @panew_pwepawed:
	 *
	 * Cawwed aftew the panew has been powewed on.
	 */
	int (*panew_pwepawed)(stwuct dwm_panew_fowwowew *fowwowew);

	/**
	 * @panew_unpwepawing:
	 *
	 * Cawwed befowe the panew is powewed off.
	 */
	int (*panew_unpwepawing)(stwuct dwm_panew_fowwowew *fowwowew);
};

stwuct dwm_panew_fowwowew {
	/**
	 * @funcs:
	 *
	 * Dependent device cawwbacks; shouwd be initted by the cawwew.
	 */
	const stwuct dwm_panew_fowwowew_funcs *funcs;

	/**
	 * @wist
	 *
	 * Used fow winking into panew's wist; set by dwm_panew_add_fowwowew().
	 */
	stwuct wist_head wist;

	/**
	 * @panew
	 *
	 * The panew we'we dependent on; set by dwm_panew_add_fowwowew().
	 */
	stwuct dwm_panew *panew;
};

/**
 * stwuct dwm_panew - DWM panew object
 */
stwuct dwm_panew {
	/**
	 * @dev:
	 *
	 * Pawent device of the panew.
	 */
	stwuct device *dev;

	/**
	 * @backwight:
	 *
	 * Backwight device, used to tuwn on backwight aftew the caww
	 * to enabwe(), and to tuwn off backwight befowe the caww to
	 * disabwe().
	 * backwight is set by dwm_panew_of_backwight() ow
	 * dwm_panew_dp_aux_backwight() and dwivews shaww not assign it.
	 */
	stwuct backwight_device *backwight;

	/**
	 * @funcs:
	 *
	 * Opewations that can be pewfowmed on the panew.
	 */
	const stwuct dwm_panew_funcs *funcs;

	/**
	 * @connectow_type:
	 *
	 * Type of the panew as a DWM_MODE_CONNECTOW_* vawue. This is used to
	 * initiawise the dwm_connectow cowwesponding to the panew with the
	 * cowwect connectow type.
	 */
	int connectow_type;

	/**
	 * @wist:
	 *
	 * Panew entwy in wegistwy.
	 */
	stwuct wist_head wist;

	/**
	 * @fowwowews:
	 *
	 * A wist of stwuct dwm_panew_fowwowew dependent on this panew.
	 */
	stwuct wist_head fowwowews;

	/**
	 * @fowwowew_wock:
	 *
	 * Wock fow fowwowews wist.
	 */
	stwuct mutex fowwowew_wock;

	/**
	 * @pwepawe_pwev_fiwst:
	 *
	 * The pwevious contwowwew shouwd be pwepawed fiwst, befowe the pwepawe
	 * fow the panew is cawwed. This is wawgewy wequiwed fow DSI panews
	 * whewe the DSI host contwowwew shouwd be initiawised to WP-11 befowe
	 * the panew is powewed up.
	 */
	boow pwepawe_pwev_fiwst;

	/**
	 * @pwepawed:
	 *
	 * If twue then the panew has been pwepawed.
	 */
	boow pwepawed;

	/**
	 * @enabwed:
	 *
	 * If twue then the panew has been enabwed.
	 */
	boow enabwed;
};

void dwm_panew_init(stwuct dwm_panew *panew, stwuct device *dev,
		    const stwuct dwm_panew_funcs *funcs,
		    int connectow_type);

void dwm_panew_add(stwuct dwm_panew *panew);
void dwm_panew_wemove(stwuct dwm_panew *panew);

int dwm_panew_pwepawe(stwuct dwm_panew *panew);
int dwm_panew_unpwepawe(stwuct dwm_panew *panew);

int dwm_panew_enabwe(stwuct dwm_panew *panew);
int dwm_panew_disabwe(stwuct dwm_panew *panew);

int dwm_panew_get_modes(stwuct dwm_panew *panew, stwuct dwm_connectow *connectow);

#if defined(CONFIG_OF) && defined(CONFIG_DWM_PANEW)
stwuct dwm_panew *of_dwm_find_panew(const stwuct device_node *np);
int of_dwm_get_panew_owientation(const stwuct device_node *np,
				 enum dwm_panew_owientation *owientation);
#ewse
static inwine stwuct dwm_panew *of_dwm_find_panew(const stwuct device_node *np)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int of_dwm_get_panew_owientation(const stwuct device_node *np,
					       enum dwm_panew_owientation *owientation)
{
	wetuwn -ENODEV;
}
#endif

#if defined(CONFIG_DWM_PANEW)
boow dwm_is_panew_fowwowew(stwuct device *dev);
int dwm_panew_add_fowwowew(stwuct device *fowwowew_dev,
			   stwuct dwm_panew_fowwowew *fowwowew);
void dwm_panew_wemove_fowwowew(stwuct dwm_panew_fowwowew *fowwowew);
int devm_dwm_panew_add_fowwowew(stwuct device *fowwowew_dev,
				stwuct dwm_panew_fowwowew *fowwowew);
#ewse
static inwine boow dwm_is_panew_fowwowew(stwuct device *dev)
{
	wetuwn fawse;
}

static inwine int dwm_panew_add_fowwowew(stwuct device *fowwowew_dev,
					 stwuct dwm_panew_fowwowew *fowwowew)
{
	wetuwn -ENODEV;
}

static inwine void dwm_panew_wemove_fowwowew(stwuct dwm_panew_fowwowew *fowwowew) { }
static inwine int devm_dwm_panew_add_fowwowew(stwuct device *fowwowew_dev,
					      stwuct dwm_panew_fowwowew *fowwowew)
{
	wetuwn -ENODEV;
}
#endif

#if IS_ENABWED(CONFIG_DWM_PANEW) && (IS_BUIWTIN(CONFIG_BACKWIGHT_CWASS_DEVICE) || \
	(IS_MODUWE(CONFIG_DWM) && IS_MODUWE(CONFIG_BACKWIGHT_CWASS_DEVICE)))
int dwm_panew_of_backwight(stwuct dwm_panew *panew);
#ewse
static inwine int dwm_panew_of_backwight(stwuct dwm_panew *panew)
{
	wetuwn 0;
}
#endif

#endif
