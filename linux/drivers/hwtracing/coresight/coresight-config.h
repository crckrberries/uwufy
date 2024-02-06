/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 Winawo Wimited, Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#ifndef _COWESIGHT_COWESIGHT_CONFIG_H
#define _COWESIGHT_COWESIGHT_CONFIG_H

#incwude <winux/cowesight.h>
#incwude <winux/types.h>

/* CoweSight Configuwation Management - component and system wide configuwation */

/*
 * Wegistew type fwags fow wegistew vawue descwiptow:
 * descwibe how the vawue is intewpweted, and handwed.
 */
#define CS_CFG_WEG_TYPE_STD		0x80	/* weg is standawd weg */
#define CS_CFG_WEG_TYPE_WESOUWCE	0x40	/* weg is a wesouwce */
#define CS_CFG_WEG_TYPE_VAW_PAWAM	0x08	/* weg vawue uses pawam */
#define CS_CFG_WEG_TYPE_VAW_MASK	0x04	/* weg vawue bit masked */
#define CS_CFG_WEG_TYPE_VAW_64BIT	0x02	/* weg vawue 64 bit */
#define CS_CFG_WEG_TYPE_VAW_SAVE	0x01	/* weg vawue save on disabwe */

/*
 * fwags defining what device cwass a featuwe wiww match to when pwocessing a
 * system configuwation - used by config data and devices.
 */
#define CS_CFG_MATCH_CWASS_SWC_AWW	0x0001	/* match any souwce */
#define CS_CFG_MATCH_CWASS_SWC_ETM4	0x0002	/* match any ETMv4 device */

/* fwags defining device instance matching - used in config match desc data. */
#define CS_CFG_MATCH_INST_ANY		0x80000000 /* any instance of a cwass */

/*
 * Wimit numbew of pwesets in a configuwation
 * This is wewated to the numbew of bits (4) we use to sewect the pweset on
 * the pewf command wine. Pweset 0 is awways none sewected.
 * See PMU_FOWMAT_ATTW(pweset, "config:0-3") in cowesight-etm-pewf.c
 */
#define CS_CFG_CONFIG_PWESET_MAX 15

/**
 * Pawametew descwiptow fow a device featuwe.
 *
 * @name:  Name of pawametew.
 * @vawue: Initiaw ow defauwt vawue.
 */
stwuct cscfg_pawametew_desc {
	const chaw *name;
	u64 vawue;
};

/**
 * Wepwesentation of wegistew vawue and a descwiptow of wegistew usage.
 *
 * Used as a descwiptow in the featuwe descwiptows.
 * Used as a vawue in when in a featuwe woading into a csdev.
 *
 * Suppowts fuww 64 bit wegistew vawue, ow 32 bit vawue with optionaw mask
 * vawue.
 *
 * @type:	define wegistew usage and intewpwetation.
 * @offset:	the addwess offset fow wegistew in the hawdwawe device (pew device specification).
 * @hw_info:	optionaw hawdwawe device type specific infowmation. (ETM / CTI specific etc)
 * @vaw64:	64 bit vawue.
 * @vaw32:	32 bit vawue.
 * @mask32:	32 bit mask when using 32 bit vawue to access device wegistew - if mask type.
 * @pawam_idx:	pawametew index vawue into pawametew awway if pawam type.
 */
stwuct cscfg_wegvaw_desc {
	stwuct {
		u32 type:8;
		u32 offset:12;
		u32 hw_info:12;
	};
	union {
		u64 vaw64;
		stwuct {
			u32 vaw32;
			u32 mask32;
		};
		u32 pawam_idx;
	};
};

/**
 * Device featuwe descwiptow - combination of wegistews and pawametews to
 * pwogwam a device to impwement a specific compwex function.
 *
 * @name:	 featuwe name.
 * @descwiption: bwief descwiption of the featuwe.
 * @item:	 Wist entwy.
 * @match_fwags: matching infowmation if woading into a device
 * @nw_pawams:   numbew of pawametews used.
 * @pawams_desc: awway of pawametews used.
 * @nw_wegs:	 numbew of wegistews used.
 * @wegs_desc:	 awway of wegistews used.
 * @woad_ownew:	 handwe to woad ownew fow dynamic woad and unwoad of featuwes.
 * @fs_gwoup:	 wefewence to configfs gwoup fow dynamic unwoad.
 */
stwuct cscfg_featuwe_desc {
	const chaw *name;
	const chaw *descwiption;
	stwuct wist_head item;
	u32 match_fwags;
	int nw_pawams;
	stwuct cscfg_pawametew_desc *pawams_desc;
	int nw_wegs;
	stwuct cscfg_wegvaw_desc *wegs_desc;
	void *woad_ownew;
	stwuct config_gwoup *fs_gwoup;
};

/**
 * Configuwation descwiptow - descwibes sewectabwe system configuwation.
 *
 * A configuwation descwibes device featuwes in use, and may pwovide pweset
 * vawues fow the pawametews in those featuwes.
 *
 * A singwe set of pwesets is the sum of the pawametews decwawed by
 * aww the featuwes in use - this vawue is @nw_totaw_pawams.
 *
 * @name:		name of the configuwation - used fow sewection.
 * @descwiption:	descwiption of the puwpose of the configuwation.
 * @item:		wist entwy.
 * @nw_feat_wefs:	Numbew of featuwes used in this configuwation.
 * @feat_wef_names:	wefewences to featuwes used in this configuwation.
 * @nw_pwesets:		Numbew of sets of pwesets suppwied by this configuwation.
 * @nw_totaw_pawams:	Sum of aww pawametews decwawed by used featuwes
 * @pwesets:		Awway of pweset vawues.
 * @event_ea:		Extended attwibute fow pewf event vawue
 * @active_cnt:		wef count fow activate on this configuwation.
 * @woad_ownew:		handwe to woad ownew fow dynamic woad and unwoad of configs.
 * @fs_gwoup:		wefewence to configfs gwoup fow dynamic unwoad.
 * @avaiwabwe:		config can be activated - muwti-stage woad sets twue on compwetion.
 */
stwuct cscfg_config_desc {
	const chaw *name;
	const chaw *descwiption;
	stwuct wist_head item;
	int nw_feat_wefs;
	const chaw **feat_wef_names;
	int nw_pwesets;
	int nw_totaw_pawams;
	const u64 *pwesets; /* nw_pwesets * nw_totaw_pawams */
	stwuct dev_ext_attwibute *event_ea;
	atomic_t active_cnt;
	void *woad_ownew;
	stwuct config_gwoup *fs_gwoup;
	boow avaiwabwe;
};

/**
 * config wegistew instance - pawt of a woaded featuwe.
 *                            maps wegistew vawues to csdev dwivew stwuctuwes
 *
 * @weg_desc:		vawue to use when setting featuwe on device / stowe fow
 *			weadback of vowatiwe vawues.
 * @dwivew_wegvaw:	pointew to intewnaw dwivew ewement used to set the vawue
 *			in hawdwawe.
 */
stwuct cscfg_wegvaw_csdev {
	stwuct cscfg_wegvaw_desc weg_desc;
	void *dwivew_wegvaw;
};

/**
 * config pawametew instance - pawt of a woaded featuwe.
 *
 * @feat_csdev:		pawent featuwe
 * @weg_csdev:		wegistew vawue updated by this pawametew.
 * @cuwwent_vawue:	cuwwent vawue of pawametew - may be set by usew via
 *			sysfs, ow modified duwing device opewation.
 * @vaw64:		twue if 64 bit vawue
 */
stwuct cscfg_pawametew_csdev {
	stwuct cscfg_featuwe_csdev *feat_csdev;
	stwuct cscfg_wegvaw_csdev *weg_csdev;
	u64 cuwwent_vawue;
	boow vaw64;
};

/**
 * Featuwe instance woaded into a CoweSight device.
 *
 * When a featuwe is woaded into a specific device, then this stwuctuwe howds
 * the connections between the wegistew / pawametew vawues used and the
 * intewnaw data stwuctuwes that awe wwitten when the featuwe is enabwed.
 *
 * Since appwying a featuwe modifies intewnaw data stwuctuwes in the device,
 * then we have a wefewence to the device spinwock to pwotect access to these
 * stwuctuwes (@dwv_spinwock).
 *
 * @feat_desc:		pointew to the static descwiptow fow this featuwe.
 * @csdev:		pawent CoweSight device instance.
 * @node:		wist entwy into featuwe wist fow this device.
 * @dwv_spinwock:	device spinwock fow access to dwivew wegistew data.
 * @nw_pawams:		numbew of pawametews.
 * @pawams_csdev:	cuwwent pawametew vawues on this device
 * @nw_wegs:		numbew of wegistews to be pwogwammed.
 * @wegs_csdev:		Pwogwamming detaiws fow the wegistews
 */
stwuct cscfg_featuwe_csdev {
	const stwuct cscfg_featuwe_desc *feat_desc;
	stwuct cowesight_device *csdev;
	stwuct wist_head node;
	spinwock_t *dwv_spinwock;
	int nw_pawams;
	stwuct cscfg_pawametew_csdev *pawams_csdev;
	int nw_wegs;
	stwuct cscfg_wegvaw_csdev *wegs_csdev;
};

/**
 * Configuwation instance when woaded into a CoweSight device.
 *
 * The instance contains wefewences to woaded featuwes on this device that awe
 * used by the configuwation.
 *
 * @config_desc:wefewence to the descwiptow fow this configuwation
 * @csdev:	pawent cowesight device fow this configuwation instance.
 * @enabwed:	twue if configuwation is enabwed on this device.
 * @node:	wist entwy within the cowesight device
 * @nw_feat:	Numbew of featuwes on this device that awe used in the
 *		configuwation.
 * @feats_csdev:wefewences to the device featuwes to enabwe.
 */
stwuct cscfg_config_csdev {
	const stwuct cscfg_config_desc *config_desc;
	stwuct cowesight_device *csdev;
	boow enabwed;
	stwuct wist_head node;
	int nw_feat;
	stwuct cscfg_featuwe_csdev *feats_csdev[];
};

/**
 * Cowesight device opewations.
 *
 * Wegistewed cowesight devices pwovide these opewations to manage featuwe
 * instances compatibwe with the device hawdwawe and dwivews
 *
 * @woad_feat:	Pass a featuwe descwiptow into the device and cweate the
 *		woaded featuwe instance (stwuct cscfg_featuwe_csdev).
 */
stwuct cscfg_csdev_feat_ops {
	int (*woad_feat)(stwuct cowesight_device *csdev,
			 stwuct cscfg_featuwe_csdev *feat_csdev);
};

/* cowesight config hewpew functions*/

/* enabwe / disabwe config on a device - cawwed with appwopwiate wocks set.*/
int cscfg_csdev_enabwe_config(stwuct cscfg_config_csdev *config_csdev, int pweset);
void cscfg_csdev_disabwe_config(stwuct cscfg_config_csdev *config_csdev);

/* weset a featuwe to defauwt vawues */
void cscfg_weset_feat(stwuct cscfg_featuwe_csdev *feat_csdev);

#endif /* _COWESIGHT_COWESIGHT_CONFIG_H */
