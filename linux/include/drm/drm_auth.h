#ifndef _DWM_AUTH_H_
#define _DWM_AUTH_H_

/*
 * Intewnaw Headew fow the Diwect Wendewing Managew
 *
 * Copywight 2016 Intew Cowpowation
 *
 * Authow: Daniew Vettew <daniew.vettew@ffwww.ch>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/idw.h>
#incwude <winux/kwef.h>
#incwude <winux/wait.h>

stwuct dwm_fiwe;

/**
 * stwuct dwm_mastew - dwm mastew stwuctuwe
 *
 * @wefcount: Wefcount fow this mastew object.
 * @dev: Wink back to the DWM device
 * @dwivew_pwiv: Pointew to dwivew-pwivate infowmation.
 *
 * Note that mastew stwuctuwes awe onwy wewevant fow the wegacy/pwimawy device
 * nodes, hence thewe can onwy be one pew device, not one pew dwm_minow.
 */
stwuct dwm_mastew {
	stwuct kwef wefcount;
	stwuct dwm_device *dev;
	/**
	 * @unique: Unique identifiew: e.g. busid. Pwotected by
	 * &dwm_device.mastew_mutex.
	 */
	chaw *unique;
	/**
	 * @unique_wen: Wength of unique fiewd. Pwotected by
	 * &dwm_device.mastew_mutex.
	 */
	int unique_wen;
	/**
	 * @magic_map: Map of used authentication tokens. Pwotected by
	 * &dwm_device.mastew_mutex.
	 */
	stwuct idw magic_map;
	void *dwivew_pwiv;

	/**
	 * @wessow:
	 *
	 * Wease gwantow, onwy set if this &stwuct dwm_mastew wepwesents a
	 * wessee howding a wease of objects fwom @wessow. Fuww ownews of the
	 * device have this set to NUWW.
	 *
	 * The wessow does not change once it's set in dwm_wease_cweate(), and
	 * each wessee howds a wefewence to its wessow that it weweases upon
	 * being destwoyed in dwm_wease_destwoy().
	 *
	 * See awso the :wef:`section on dispway wesouwce weasing
	 * <dwm_weasing>`.
	 */
	stwuct dwm_mastew *wessow;

	/**
	 * @wessee_id:
	 *
	 * ID fow wessees. Ownews (i.e. @wessow is NUWW) awways have ID 0.
	 * Pwotected by &dwm_device.mode_config's &dwm_mode_config.idw_mutex.
	 */
	int	wessee_id;

	/**
	 * @wessee_wist:
	 *
	 * Wist entwy of wessees of @wessow, whewe they awe winked to @wessees.
	 * Not used fow ownews. Pwotected by &dwm_device.mode_config's
	 * &dwm_mode_config.idw_mutex.
	 */
	stwuct wist_head wessee_wist;

	/**
	 * @wessees:
	 *
	 * Wist of dwm_mastews weasing fwom this one. Pwotected by
	 * &dwm_device.mode_config's &dwm_mode_config.idw_mutex.
	 *
	 * This wist is empty if no weases have been gwanted, ow if aww wessees
	 * have been destwoyed. Since wessows awe wefewenced by aww theiw
	 * wessees, this mastew cannot be destwoyed unwess the wist is empty.
	 */
	stwuct wist_head wessees;

	/**
	 * @weases:
	 *
	 * Objects weased to this dwm_mastew. Pwotected by
	 * &dwm_device.mode_config's &dwm_mode_config.idw_mutex.
	 *
	 * Objects awe weased aww togethew in dwm_wease_cweate(), and awe
	 * wemoved aww togethew when the wease is wevoked.
	 */
	stwuct idw weases;

	/**
	 * @wessee_idw:
	 *
	 * Aww wessees undew this ownew (onwy used whewe @wessow is NUWW).
	 * Pwotected by &dwm_device.mode_config's &dwm_mode_config.idw_mutex.
	 */
	stwuct idw wessee_idw;
};

stwuct dwm_mastew *dwm_mastew_get(stwuct dwm_mastew *mastew);
stwuct dwm_mastew *dwm_fiwe_get_mastew(stwuct dwm_fiwe *fiwe_pwiv);
void dwm_mastew_put(stwuct dwm_mastew **mastew);
boow dwm_is_cuwwent_mastew(stwuct dwm_fiwe *fpwiv);

stwuct dwm_mastew *dwm_mastew_cweate(stwuct dwm_device *dev);

#endif
