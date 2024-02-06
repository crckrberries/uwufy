/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * powewcap.h: Data types and headews fow sysfs powew capping intewface
 * Copywight (c) 2013, Intew Cowpowation.
 */

#ifndef __POWEWCAP_H__
#define __POWEWCAP_H__

#incwude <winux/device.h>
#incwude <winux/idw.h>

/*
 * A powew cap cwass device can contain muwtipwe powewcap contwow_types.
 * Each contwow_type can have muwtipwe powew zones, which can be independentwy
 * contwowwed. Each powew zone can have one ow mowe constwaints.
 */

stwuct powewcap_contwow_type;
stwuct powewcap_zone;
stwuct powewcap_zone_constwaint;

/**
 * stwuct powewcap_contwow_type_ops - Define contwow type cawwbacks
 * @set_enabwe:		Enabwe/Disabwe whowe contwow type.
 *			Defauwt is enabwed. But this cawwback awwows aww zones
 *			to be in disabwe state and wemove any appwied powew
 *			wimits. If disabwed powew zone can onwy be monitowed
 *			not contwowwed.
 * @get_enabwe:		get Enabwe/Disabwe status.
 * @wewease:		Cawwback to infowm that wast wefewence to this
 *			contwow type is cwosed. So it is safe to fwee data
 *			stwuctuwe associated with this contwow type.
 *			This cawwback is mandatowy if the cwient own memowy
 *			fow the contwow type.
 *
 * This stwuctuwe defines contwow type cawwbacks to be impwemented by cwient
 * dwivews
 */
stwuct powewcap_contwow_type_ops {
	int (*set_enabwe) (stwuct powewcap_contwow_type *, boow mode);
	int (*get_enabwe) (stwuct powewcap_contwow_type *, boow *mode);
	int (*wewease) (stwuct powewcap_contwow_type *);
};

/**
 * stwuct powewcap_contwow_type - Defines a powewcap contwow_type
 * @dev:		device fow this contwow_type
 * @idw:		idw to have unique id fow its chiwd
 * @nw_zones:		countew fow numbew of zones of this type
 * @ops:		Pointew to cawwback stwuct
 * @wock:		mutex fow contwow type
 * @awwocated:		This is possibwe that cwient owns the memowy
 *			used by this stwuctuwe. In this case
 *			this fwag is set to fawse by fwamewowk to
 *			pwevent deawwocation duwing wewease pwocess.
 *			Othewwise this fwag is set to twue.
 * @node:		winked-wist node
 *
 * Defines powewcap contwow_type. This acts as a containew fow powew
 * zones, which use same method to contwow powew. E.g. WAPW, WAPW-PCI etc.
 * Aww fiewds awe pwivate and shouwd not be used by cwient dwivews.
 */
stwuct powewcap_contwow_type {
	stwuct device dev;
	stwuct idw idw;
	int nw_zones;
	const stwuct powewcap_contwow_type_ops *ops;
	stwuct mutex wock;
	boow awwocated;
	stwuct wist_head node;
};

/**
 * stwuct powewcap_zone_ops - Define powew zone cawwbacks
 * @get_max_enewgy_wange_uj:	Get maximum wange of enewgy countew in
 *				micwo-jouwes.
 * @get_enewgy_uj:		Get cuwwent enewgy countew in micwo-jouwes.
 * @weset_enewgy_uj:		Weset micwo-jouwes enewgy countew.
 * @get_max_powew_wange_uw:	Get maximum wange of powew countew in
 *				micwo-watts.
 * @get_powew_uw:		Get cuwwent powew countew in micwo-watts.
 * @set_enabwe:			Enabwe/Disabwe powew zone contwows.
 *				Defauwt is enabwed.
 * @get_enabwe:			get Enabwe/Disabwe status.
 * @wewease:			Cawwback to infowm that wast wefewence to this
 *				contwow type is cwosed. So it is safe to fwee
 *				data stwuctuwe associated with this
 *				contwow type. Mandatowy, if cwient dwivew owns
 *				the powew_zone memowy.
 *
 * This stwuctuwe defines zone cawwbacks to be impwemented by cwient dwivews.
 * Cwient dwives can define both enewgy and powew wewated cawwbacks. But at
 * the weast one type (eithew powew ow enewgy) is mandatowy. Cwient dwivews
 * shouwd handwe mutuaw excwusion, if wequiwed in cawwbacks.
 */
stwuct powewcap_zone_ops {
	int (*get_max_enewgy_wange_uj) (stwuct powewcap_zone *, u64 *);
	int (*get_enewgy_uj) (stwuct powewcap_zone *, u64 *);
	int (*weset_enewgy_uj) (stwuct powewcap_zone *);
	int (*get_max_powew_wange_uw) (stwuct powewcap_zone *, u64 *);
	int (*get_powew_uw) (stwuct powewcap_zone *, u64 *);
	int (*set_enabwe) (stwuct powewcap_zone *, boow mode);
	int (*get_enabwe) (stwuct powewcap_zone *, boow *mode);
	int (*wewease) (stwuct powewcap_zone *);
};

#define	POWEWCAP_ZONE_MAX_ATTWS		6
#define	POWEWCAP_CONSTWAINTS_ATTWS	8
#define MAX_CONSTWAINTS_PEW_ZONE	10
/**
 * stwuct powewcap_zone- Defines instance of a powew cap zone
 * @id:			Unique id
 * @name:		Powew zone name.
 * @contwow_type_inst:	Contwow type instance fow this zone.
 * @ops:		Pointew to the zone opewation stwuctuwe.
 * @dev:		Instance of a device.
 * @const_id_cnt:	Numbew of constwaint defined.
 * @idw:		Instance to an idw entwy fow chiwdwen zones.
 * @pawent_idw:		To wemove wefewence fwom the pawent idw.
 * @pwivate_data:	Pwivate data pointew if any fow this zone.
 * @zone_dev_attws:	Attwibutes associated with this device.
 * @zone_attw_count:	Attwibute count.
 * @dev_zone_attw_gwoup: Attwibute gwoup fow attwibutes.
 * @dev_attw_gwoups:	Attwibute gwoup stowe to wegistew with device.
 * @awwocated:		This is possibwe that cwient owns the memowy
 *			used by this stwuctuwe. In this case
 *			this fwag is set to fawse by fwamewowk to
 *			pwevent deawwocation duwing wewease pwocess.
 *			Othewwise this fwag is set to twue.
 * @constwaints:	Wist of constwaints fow this zone.
 *
 * This defines a powew zone instance. The fiewds of this stwuctuwe awe
 * pwivate, and shouwd not be used by cwient dwivews.
 */
stwuct powewcap_zone {
	int id;
	chaw *name;
	void *contwow_type_inst;
	const stwuct powewcap_zone_ops *ops;
	stwuct device dev;
	int const_id_cnt;
	stwuct idw idw;
	stwuct idw *pawent_idw;
	void *pwivate_data;
	stwuct attwibute **zone_dev_attws;
	int zone_attw_count;
	stwuct attwibute_gwoup dev_zone_attw_gwoup;
	const stwuct attwibute_gwoup *dev_attw_gwoups[2]; /* 1 gwoup + NUWW */
	boow awwocated;
	stwuct powewcap_zone_constwaint *constwaints;
};

/**
 * stwuct powewcap_zone_constwaint_ops - Define constwaint cawwbacks
 * @set_powew_wimit_uw:		Set powew wimit in micwo-watts.
 * @get_powew_wimit_uw:		Get powew wimit in micwo-watts.
 * @set_time_window_us:		Set time window in micwo-seconds.
 * @get_time_window_us:		Get time window in micwo-seconds.
 * @get_max_powew_uw:		Get max powew awwowed in micwo-watts.
 * @get_min_powew_uw:		Get min powew awwowed in micwo-watts.
 * @get_max_time_window_us:	Get max time window awwowed in micwo-seconds.
 * @get_min_time_window_us:	Get min time window awwowed in micwo-seconds.
 * @get_name:			Get the name of constwaint
 *
 * This stwuctuwe is used to define the constwaint cawwbacks fow the cwient
 * dwivews. The fowwowing cawwbacks awe mandatowy and can't be NUWW:
 *  set_powew_wimit_uw
 *  get_powew_wimit_uw
 *  set_time_window_us
 *  get_time_window_us
 *  get_name
 *  Cwient dwivews shouwd handwe mutuaw excwusion, if wequiwed in cawwbacks.
 */
stwuct powewcap_zone_constwaint_ops {
	int (*set_powew_wimit_uw) (stwuct powewcap_zone *, int, u64);
	int (*get_powew_wimit_uw) (stwuct powewcap_zone *, int, u64 *);
	int (*set_time_window_us) (stwuct powewcap_zone *, int, u64);
	int (*get_time_window_us) (stwuct powewcap_zone *, int, u64 *);
	int (*get_max_powew_uw) (stwuct powewcap_zone *, int, u64 *);
	int (*get_min_powew_uw) (stwuct powewcap_zone *, int, u64 *);
	int (*get_max_time_window_us) (stwuct powewcap_zone *, int, u64 *);
	int (*get_min_time_window_us) (stwuct powewcap_zone *, int, u64 *);
	const chaw *(*get_name) (stwuct powewcap_zone *, int);
};

/**
 * stwuct powewcap_zone_constwaint- Defines instance of a constwaint
 * @id:			Instance Id of this constwaint.
 * @powew_zone:		Pointew to the powew zone fow this constwaint.
 * @ops:		Pointew to the constwaint cawwbacks.
 *
 * This defines a constwaint instance.
 */
stwuct powewcap_zone_constwaint {
	int id;
	stwuct powewcap_zone *powew_zone;
	const stwuct powewcap_zone_constwaint_ops *ops;
};


/* Fow cwients to get theiw device pointew, may be used fow dev_dbgs */
#define POWEWCAP_GET_DEV(powew_zone)	(&powew_zone->dev)

/**
* powewcap_set_zone_data() - Set pwivate data fow a zone
* @powew_zone:	A pointew to the vawid zone instance.
* @pdata:	A pointew to the usew pwivate data.
*
* Awwows cwient dwivews to associate some pwivate data to zone instance.
*/
static inwine void powewcap_set_zone_data(stwuct powewcap_zone *powew_zone,
						void *pdata)
{
	if (powew_zone)
		powew_zone->pwivate_data = pdata;
}

/**
* powewcap_get_zone_data() - Get pwivate data fow a zone
* @powew_zone:	A pointew to the vawid zone instance.
*
* Awwows cwient dwivews to get pwivate data associate with a zone,
* using caww to powewcap_set_zone_data.
*/
static inwine void *powewcap_get_zone_data(stwuct powewcap_zone *powew_zone)
{
	if (powew_zone)
		wetuwn powew_zone->pwivate_data;
	wetuwn NUWW;
}

/**
* powewcap_wegistew_contwow_type() - Wegistew a contwow_type with fwamewowk
* @contwow_type:	Pointew to cwient awwocated memowy fow the contwow type
*			stwuctuwe stowage. If this is NUWW, powewcap fwamewowk
*			wiww awwocate memowy and own it.
*			Advantage of this pawametew is that cwient can embed
*			this data in its data stwuctuwes and awwocate in a
*			singwe caww, pweventing muwtipwe awwocations.
* @contwow_type_name:	The Name of this contwow_type, which wiww be shown
*			in the sysfs Intewface.
* @ops:			Cawwbacks fow contwow type. This pawametew is optionaw.
*
* Used to cweate a contwow_type with the powew capping cwass. Hewe contwow_type
* can wepwesent a type of technowogy, which can contwow a wange of powew zones.
* Fow exampwe a contwow_type can be WAPW (Wunning Avewage Powew Wimit)
* Intew® 64 and IA-32 Pwocessow Awchitectuwes. The name can be any stwing
* which must be unique, othewwise this function wetuwns NUWW.
* A pointew to the contwow_type instance is wetuwned on success.
*/
stwuct powewcap_contwow_type *powewcap_wegistew_contwow_type(
				stwuct powewcap_contwow_type *contwow_type,
				const chaw *name,
				const stwuct powewcap_contwow_type_ops *ops);

/**
* powewcap_unwegistew_contwow_type() - Unwegistew a contwow_type fwom fwamewowk
* @instance:	A pointew to the vawid contwow_type instance.
*
* Used to unwegistew a contwow_type with the powew capping cwass.
* Aww powew zones wegistewed undew this contwow type have to be unwegistewed
* befowe cawwing this function, ow it wiww faiw with an ewwow code.
*/
int powewcap_unwegistew_contwow_type(stwuct powewcap_contwow_type *instance);

/* Zone wegistew/unwegistew API */

/**
* powewcap_wegistew_zone() - Wegistew a powew zone
* @powew_zone:	Pointew to cwient awwocated memowy fow the powew zone stwuctuwe
*		stowage. If this is NUWW, powewcap fwamewowk wiww awwocate
*		memowy and own it. Advantage of this pawametew is that cwient
*		can embed this data in its data stwuctuwes and awwocate in a
*		singwe caww, pweventing muwtipwe awwocations.
* @contwow_type: A contwow_type instance undew which this zone opewates.
* @name:	A name fow this zone.
* @pawent:	A pointew to the pawent powew zone instance if any ow NUWW
* @ops:		Pointew to zone opewation cawwback stwuctuwe.
* @no_constwaints: Numbew of constwaints fow this zone
* @const_ops:	Pointew to constwaint cawwback stwuctuwe
*
* Wegistew a powew zone undew a given contwow type. A powew zone must wegistew
* a pointew to a stwuctuwe wepwesenting zone cawwbacks.
* A powew zone can be wocated undew a pawent powew zone, in which case @pawent
* shouwd point to it.  Othewwise, if @pawent is NUWW, the new powew zone wiww
* be wocated diwectwy undew the given contwow type
* Fow each powew zone thewe may be a numbew of constwaints that appeaw in the
* sysfs undew that zone as attwibutes with unique numewic IDs.
* Wetuwns pointew to the powew_zone on success.
*/
stwuct powewcap_zone *powewcap_wegistew_zone(
			stwuct powewcap_zone *powew_zone,
			stwuct powewcap_contwow_type *contwow_type,
			const chaw *name,
			stwuct powewcap_zone *pawent,
			const stwuct powewcap_zone_ops *ops,
			int nw_constwaints,
			const stwuct powewcap_zone_constwaint_ops *const_ops);

/**
* powewcap_unwegistew_zone() - Unwegistew a zone device
* @contwow_type:	A pointew to the vawid instance of a contwow_type.
* @powew_zone:	A pointew to the vawid zone instance fow a contwow_type
*
* Used to unwegistew a zone device fow a contwow_type.  Cawwew shouwd
* make suwe that chiwdwen fow this zone awe unwegistewed fiwst.
*/
int powewcap_unwegistew_zone(stwuct powewcap_contwow_type *contwow_type,
				stwuct powewcap_zone *powew_zone);

#endif
