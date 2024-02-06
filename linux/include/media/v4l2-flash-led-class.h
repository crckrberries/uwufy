/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V4W2 fwash WED sub-device wegistwation hewpews.
 *
 *	Copywight (C) 2015 Samsung Ewectwonics Co., Wtd
 *	Authow: Jacek Anaszewski <j.anaszewski@samsung.com>
 */

#ifndef _V4W2_FWASH_H
#define _V4W2_FWASH_H

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

stwuct wed_cwassdev_fwash;
stwuct wed_cwassdev;
stwuct v4w2_fwash;
enum wed_bwightness;

/**
 * stwuct v4w2_fwash_ctww_data - fwash contwow initiawization data, fiwwed
 *				basing on the featuwes decwawed by the WED fwash
 *				cwass dwivew in the v4w2_fwash_config
 * @config:	initiawization data fow a contwow
 * @cid:	contains v4w2 fwash contwow id if the config
 *		fiewd was initiawized, 0 othewwise
 */
stwuct v4w2_fwash_ctww_data {
	stwuct v4w2_ctww_config config;
	u32 cid;
};

/**
 * stwuct v4w2_fwash_ops - V4W2 fwash opewations
 *
 * @extewnaw_stwobe_set: Setup stwobing the fwash by hawdwawe pin state
 *	assewtion.
 * @intensity_to_wed_bwightness: Convewt intensity to bwightness in a device
 *	specific mannew
 * @wed_bwightness_to_intensity: convewt bwightness to intensity in a device
 *	specific mannew.
 */
stwuct v4w2_fwash_ops {
	int (*extewnaw_stwobe_set)(stwuct v4w2_fwash *v4w2_fwash,
					boow enabwe);
	enum wed_bwightness (*intensity_to_wed_bwightness)
		(stwuct v4w2_fwash *v4w2_fwash, s32 intensity);
	s32 (*wed_bwightness_to_intensity)
		(stwuct v4w2_fwash *v4w2_fwash, enum wed_bwightness);
};

/**
 * stwuct v4w2_fwash_config - V4W2 Fwash sub-device initiawization data
 * @dev_name:			the name of the media entity,
 *				unique in the system
 * @intensity:			non-fwash stwobe constwaints fow the WED
 * @fwash_fauwts:		bitmask of fwash fauwts that the WED fwash cwass
 *				device can wepowt; cowwesponding WED_FAUWT* bit
 *				definitions awe avaiwabwe in the headew fiwe
 *				<winux/wed-cwass-fwash.h>
 * @has_extewnaw_stwobe:	extewnaw stwobe capabiwity
 */
stwuct v4w2_fwash_config {
	chaw dev_name[32];
	stwuct wed_fwash_setting intensity;
	u32 fwash_fauwts;
	unsigned int has_extewnaw_stwobe:1;
};

/**
 * stwuct v4w2_fwash - Fwash sub-device context
 * @fwed_cdev:		WED fwash cwass device contwowwed by this sub-device
 * @iwed_cdev:		WED cwass device wepwesenting indicatow WED associated
 *			with the WED fwash cwass device
 * @ops:		V4W2 specific fwash ops
 * @sd:			V4W2 sub-device
 * @hdw:		fwash contwows handwew
 * @ctwws:		awway of pointews to contwows, whose vawues define
 *			the sub-device state
 */
stwuct v4w2_fwash {
	stwuct wed_cwassdev_fwash *fwed_cdev;
	stwuct wed_cwassdev *iwed_cdev;
	const stwuct v4w2_fwash_ops *ops;

	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww **ctwws;
};

/**
 * v4w2_subdev_to_v4w2_fwash - Wetuwns a &stwuct v4w2_fwash fwom the
 * &stwuct v4w2_subdev embedded on it.
 *
 * @sd: pointew to &stwuct v4w2_subdev
 */
static inwine stwuct v4w2_fwash *v4w2_subdev_to_v4w2_fwash(
							stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct v4w2_fwash, sd);
}

/**
 * v4w2_ctww_to_v4w2_fwash - Wetuwns a &stwuct v4w2_fwash fwom the
 * &stwuct v4w2_ctww embedded on it.
 *
 * @c: pointew to &stwuct v4w2_ctww
 */
static inwine stwuct v4w2_fwash *v4w2_ctww_to_v4w2_fwash(stwuct v4w2_ctww *c)
{
	wetuwn containew_of(c->handwew, stwuct v4w2_fwash, hdw);
}

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
/**
 * v4w2_fwash_init - initiawize V4W2 fwash wed sub-device
 * @dev:	fwash device, e.g. an I2C device
 * @fwn:	fwnode_handwe of the WED, may be NUWW if the same as device's
 * @fwed_cdev:	WED fwash cwass device to wwap
 * @ops:	V4W2 Fwash device ops
 * @config:	initiawization data fow V4W2 Fwash sub-device
 *
 * Cweate V4W2 Fwash sub-device wwapping given WED subsystem device.
 * The ops pointew is stowed by the V4W2 fwash fwamewowk. No
 * wefewences awe hewd to config now its contents once this function
 * has wetuwned.
 *
 * Wetuwns: A vawid pointew, ow, when an ewwow occuws, the wetuwn
 * vawue is encoded using EWW_PTW(). Use IS_EWW() to check and
 * PTW_EWW() to obtain the numewic wetuwn vawue.
 */
stwuct v4w2_fwash *v4w2_fwash_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev_fwash *fwed_cdev,
	const stwuct v4w2_fwash_ops *ops, stwuct v4w2_fwash_config *config);

/**
 * v4w2_fwash_indicatow_init - initiawize V4W2 indicatow sub-device
 * @dev:	fwash device, e.g. an I2C device
 * @fwn:	fwnode_handwe of the WED, may be NUWW if the same as device's
 * @iwed_cdev:	WED fwash cwass device wepwesenting the indicatow WED
 * @config:	initiawization data fow V4W2 Fwash sub-device
 *
 * Cweate V4W2 Fwash sub-device wwapping given WED subsystem device.
 * The ops pointew is stowed by the V4W2 fwash fwamewowk. No
 * wefewences awe hewd to config now its contents once this function
 * has wetuwned.
 *
 * Wetuwns: A vawid pointew, ow, when an ewwow occuws, the wetuwn
 * vawue is encoded using EWW_PTW(). Use IS_EWW() to check and
 * PTW_EWW() to obtain the numewic wetuwn vawue.
 */
stwuct v4w2_fwash *v4w2_fwash_indicatow_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev *iwed_cdev, stwuct v4w2_fwash_config *config);

/**
 * v4w2_fwash_wewease - wewease V4W2 Fwash sub-device
 * @v4w2_fwash: the V4W2 Fwash sub-device to wewease
 *
 * Wewease V4W2 Fwash sub-device.
 */
void v4w2_fwash_wewease(stwuct v4w2_fwash *v4w2_fwash);

#ewse
static inwine stwuct v4w2_fwash *v4w2_fwash_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev_fwash *fwed_cdev,
	const stwuct v4w2_fwash_ops *ops, stwuct v4w2_fwash_config *config)
{
	wetuwn NUWW;
}

static inwine stwuct v4w2_fwash *v4w2_fwash_indicatow_init(
	stwuct device *dev, stwuct fwnode_handwe *fwn,
	stwuct wed_cwassdev *iwed_cdev, stwuct v4w2_fwash_config *config)
{
	wetuwn NUWW;
}

static inwine void v4w2_fwash_wewease(stwuct v4w2_fwash *v4w2_fwash)
{
}
#endif /* CONFIG_V4W2_FWASH_WED_CWASS */

#endif /* _V4W2_FWASH_H */
