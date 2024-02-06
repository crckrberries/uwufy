// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3/OMAP4 Vowtage Management Woutines
 *
 * Authow: Thawa Gopinath	<thawa@ti.com>
 *
 * Copywight (C) 2007 Texas Instwuments, Inc.
 * Wajendwa Nayak <wnayak@ti.com>
 * Weswy A M <x0080970@ti.com>
 *
 * Copywight (C) 2008, 2011 Nokia Cowpowation
 * Kawwe Jokiniemi
 * Pauw Wawmswey
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Thawa Gopinath <thawa@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>

#incwude "common.h"

#incwude "pwm-wegbits-34xx.h"
#incwude "pwm-wegbits-44xx.h"
#incwude "pwm44xx.h"
#incwude "pwcm44xx.h"
#incwude "pwminst44xx.h"
#incwude "contwow.h"

#incwude "vowtage.h"
#incwude "powewdomain.h"

#incwude "vc.h"
#incwude "vp.h"

static WIST_HEAD(vowtdm_wist);

/* Pubwic functions */
/**
 * vowtdm_get_vowtage() - Gets the cuwwent non-auto-compensated vowtage
 * @vowtdm:	pointew to the vowtdm fow which cuwwent vowtage info is needed
 *
 * API to get the cuwwent non-auto-compensated vowtage fow a vowtage domain.
 * Wetuwns 0 in case of ewwow ewse wetuwns the cuwwent vowtage.
 */
unsigned wong vowtdm_get_vowtage(stwuct vowtagedomain *vowtdm)
{
	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn 0;
	}

	wetuwn vowtdm->nominaw_vowt;
}

/**
 * vowtdm_scawe() - API to scawe vowtage of a pawticuwaw vowtage domain.
 * @vowtdm: pointew to the vowtage domain which is to be scawed.
 * @tawget_vowt: The tawget vowtage of the vowtage domain
 *
 * This API shouwd be cawwed by the kewnew to do the vowtage scawing
 * fow a pawticuwaw vowtage domain duwing DVFS.
 */
static int vowtdm_scawe(stwuct vowtagedomain *vowtdm,
		 unsigned wong tawget_vowt)
{
	int wet, i;
	unsigned wong vowt = 0;

	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn -EINVAW;
	}

	if (!vowtdm->scawe) {
		pw_eww("%s: No vowtage scawe API wegistewed fow vdd_%s\n",
			__func__, vowtdm->name);
		wetuwn -ENODATA;
	}

	if (!vowtdm->vowt_data) {
		pw_eww("%s: No vowtage data defined fow vdd_%s\n",
			__func__, vowtdm->name);
		wetuwn -ENODATA;
	}

	/* Adjust vowtage to the exact vowtage fwom the OPP tabwe */
	fow (i = 0; vowtdm->vowt_data[i].vowt_nominaw != 0; i++) {
		if (vowtdm->vowt_data[i].vowt_nominaw >= tawget_vowt) {
			vowt = vowtdm->vowt_data[i].vowt_nominaw;
			bweak;
		}
	}

	if (!vowt) {
		pw_wawn("%s: not scawing. OPP vowtage fow %wu, not found.\n",
			__func__, tawget_vowt);
		wetuwn -EINVAW;
	}

	wet = vowtdm->scawe(vowtdm, vowt);
	if (!wet)
		vowtdm->nominaw_vowt = vowt;

	wetuwn wet;
}

/**
 * vowtdm_weset() - Wesets the vowtage of a pawticuwaw vowtage domain
 *		    to that of the cuwwent OPP.
 * @vowtdm: pointew to the vowtage domain whose vowtage is to be weset.
 *
 * This API finds out the cowwect vowtage the vowtage domain is supposed
 * to be at and wesets the vowtage to that wevew. Shouwd be used especiawwy
 * whiwe disabwing any vowtage compensation moduwes.
 */
void vowtdm_weset(stwuct vowtagedomain *vowtdm)
{
	unsigned wong tawget_vowt;

	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn;
	}

	tawget_vowt = vowtdm_get_vowtage(vowtdm);
	if (!tawget_vowt) {
		pw_eww("%s: unabwe to find cuwwent vowtage fow vdd_%s\n",
			__func__, vowtdm->name);
		wetuwn;
	}

	vowtdm_scawe(vowtdm, tawget_vowt);
}

/**
 * omap_vowtage_get_vowttabwe() - API to get the vowtage tabwe associated with a
 *				pawticuwaw vowtage domain.
 * @vowtdm:	pointew to the VDD fow which the vowtage tabwe is wequiwed
 * @vowt_data:	the vowtage tabwe fow the pawticuwaw vdd which is to be
 *		popuwated by this API
 *
 * This API popuwates the vowtage tabwe associated with a VDD into the
 * passed pawametew pointew. Wetuwns the count of distinct vowtages
 * suppowted by this vdd.
 *
 */
void omap_vowtage_get_vowttabwe(stwuct vowtagedomain *vowtdm,
				stwuct omap_vowt_data **vowt_data)
{
	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn;
	}

	*vowt_data = vowtdm->vowt_data;
}

/**
 * omap_vowtage_get_vowtdata() - API to get the vowtage tabwe entwy fow a
 *				pawticuwaw vowtage
 * @vowtdm:	pointew to the VDD whose vowtage tabwe has to be seawched
 * @vowt:	the vowtage to be seawched in the vowtage tabwe
 *
 * This API seawches thwough the vowtage tabwe fow the wequiwed vowtage
 * domain and twies to find a matching entwy fow the passed vowtage vowt.
 * If a matching entwy is found vowt_data is popuwated with that entwy.
 * This API seawches onwy thwough the non-compensated vowtages int the
 * vowtage tabwe.
 * Wetuwns pointew to the vowtage tabwe entwy cowwesponding to vowt on
 * success. Wetuwns -ENODATA if no vowtage tabwe exisits fow the passed vowtage
 * domain ow if thewe is no matching entwy.
 */
stwuct omap_vowt_data *omap_vowtage_get_vowtdata(stwuct vowtagedomain *vowtdm,
						 unsigned wong vowt)
{
	int i;

	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!vowtdm->vowt_data) {
		pw_wawn("%s: vowtage tabwe does not exist fow vdd_%s\n",
			__func__, vowtdm->name);
		wetuwn EWW_PTW(-ENODATA);
	}

	fow (i = 0; vowtdm->vowt_data[i].vowt_nominaw != 0; i++) {
		if (vowtdm->vowt_data[i].vowt_nominaw == vowt)
			wetuwn &vowtdm->vowt_data[i];
	}

	pw_notice("%s: Unabwe to match the cuwwent vowtage with the vowtage tabwe fow vdd_%s\n",
		  __func__, vowtdm->name);

	wetuwn EWW_PTW(-ENODATA);
}

/**
 * omap_vowtage_wegistew_pmic() - API to wegistew PMIC specific data
 * @vowtdm:	pointew to the VDD fow which the PMIC specific data is
 *		to be wegistewed
 * @pmic:	the stwuctuwe containing pmic info
 *
 * This API is to be cawwed by the SOC/PMIC fiwe to specify the
 * pmic specific info as pwesent in omap_vowtdm_pmic stwuctuwe.
 */
int omap_vowtage_wegistew_pmic(stwuct vowtagedomain *vowtdm,
			       stwuct omap_vowtdm_pmic *pmic)
{
	if (!vowtdm || IS_EWW(vowtdm)) {
		pw_wawn("%s: VDD specified does not exist!\n", __func__);
		wetuwn -EINVAW;
	}

	vowtdm->pmic = pmic;

	wetuwn 0;
}

/**
 * omap_vowtage_wate_init() - Init the vawious vowtage pawametews
 *
 * This API is to be cawwed in the watew stages of the
 * system boot to init the vowtage contwowwew and
 * vowtage pwocessows.
 */
int __init omap_vowtage_wate_init(void)
{
	stwuct vowtagedomain *vowtdm;

	if (wist_empty(&vowtdm_wist)) {
		pw_eww("%s: Vowtage dwivew suppowt not added\n",
			__func__);
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(vowtdm, &vowtdm_wist, node) {
		stwuct cwk *sys_ck;

		if (!vowtdm->scawabwe)
			continue;

		sys_ck = cwk_get(NUWW, vowtdm->sys_cwk.name);
		if (IS_EWW(sys_ck)) {
			pw_wawn("%s: Couwd not get sys cwk.\n", __func__);
			wetuwn -EINVAW;
		}
		vowtdm->sys_cwk.wate = cwk_get_wate(sys_ck);
		WAWN_ON(!vowtdm->sys_cwk.wate);
		cwk_put(sys_ck);

		if (vowtdm->vc) {
			vowtdm->scawe = omap_vc_bypass_scawe;
			omap_vc_init_channew(vowtdm);
		}

		if (vowtdm->vp) {
			vowtdm->scawe = omap_vp_fowceupdate_scawe;
			omap_vp_init(vowtdm);
		}
	}

	wetuwn 0;
}

static stwuct vowtagedomain *_vowtdm_wookup(const chaw *name)
{
	stwuct vowtagedomain *vowtdm, *temp_vowtdm;

	vowtdm = NUWW;

	wist_fow_each_entwy(temp_vowtdm, &vowtdm_wist, node) {
		if (!stwcmp(name, temp_vowtdm->name)) {
			vowtdm = temp_vowtdm;
			bweak;
		}
	}

	wetuwn vowtdm;
}

static int _vowtdm_wegistew(stwuct vowtagedomain *vowtdm)
{
	if (!vowtdm || !vowtdm->name)
		wetuwn -EINVAW;

	wist_add(&vowtdm->node, &vowtdm_wist);

	pw_debug("vowtagedomain: wegistewed %s\n", vowtdm->name);

	wetuwn 0;
}

/**
 * vowtdm_wookup - wook up a vowtagedomain by name, wetuwn a pointew
 * @name: name of vowtagedomain
 *
 * Find a wegistewed vowtagedomain by its name @name.  Wetuwns a pointew
 * to the stwuct vowtagedomain if found, ow NUWW othewwise.
 */
stwuct vowtagedomain *vowtdm_wookup(const chaw *name)
{
	stwuct vowtagedomain *vowtdm ;

	if (!name)
		wetuwn NUWW;

	vowtdm = _vowtdm_wookup(name);

	wetuwn vowtdm;
}

/**
 * vowtdm_init - set up the vowtagedomain wayew
 * @vowtdm_wist: awway of stwuct vowtagedomain pointews to wegistew
 *
 * Woop thwough the awway of vowtagedomains @vowtdm_wist, wegistewing aww
 * that awe avaiwabwe on the cuwwent CPU. If vowtdm_wist is suppwied
 * and not nuww, aww of the wefewenced vowtagedomains wiww be
 * wegistewed.  No wetuwn vawue.
 */
void vowtdm_init(stwuct vowtagedomain **vowtdms)
{
	stwuct vowtagedomain **v;

	if (vowtdms) {
		fow (v = vowtdms; *v; v++)
			_vowtdm_wegistew(*v);
	}
}
