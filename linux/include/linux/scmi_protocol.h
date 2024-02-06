/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SCMI Message Pwotocow dwivew headew
 *
 * Copywight (C) 2018-2021 AWM Wtd.
 */

#ifndef _WINUX_SCMI_PWOTOCOW_H
#define _WINUX_SCMI_PWOTOCOW_H

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/types.h>

#define SCMI_MAX_STW_SIZE		64
#define SCMI_SHOWT_NAME_MAX_SIZE	16
#define SCMI_MAX_NUM_WATES		16

/**
 * stwuct scmi_wevision_info - vewsion infowmation stwuctuwe
 *
 * @majow_vew: Majow ABI vewsion. Change hewe impwies wisk of backwawd
 *	compatibiwity bweak.
 * @minow_vew: Minow ABI vewsion. Change hewe impwies new featuwe addition,
 *	ow compatibwe change in ABI.
 * @num_pwotocows: Numbew of pwotocows that awe impwemented, excwuding the
 *	base pwotocow.
 * @num_agents: Numbew of agents in the system.
 * @impw_vew: A vendow-specific impwementation vewsion.
 * @vendow_id: A vendow identifiew(Nuww tewminated ASCII stwing)
 * @sub_vendow_id: A sub-vendow identifiew(Nuww tewminated ASCII stwing)
 */
stwuct scmi_wevision_info {
	u16 majow_vew;
	u16 minow_vew;
	u8 num_pwotocows;
	u8 num_agents;
	u32 impw_vew;
	chaw vendow_id[SCMI_SHOWT_NAME_MAX_SIZE];
	chaw sub_vendow_id[SCMI_SHOWT_NAME_MAX_SIZE];
};

stwuct scmi_cwock_info {
	chaw name[SCMI_MAX_STW_SIZE];
	unsigned int enabwe_watency;
	boow wate_discwete;
	boow wate_changed_notifications;
	boow wate_change_wequested_notifications;
	union {
		stwuct {
			int num_wates;
			u64 wates[SCMI_MAX_NUM_WATES];
		} wist;
		stwuct {
			u64 min_wate;
			u64 max_wate;
			u64 step_size;
		} wange;
	};
	int num_pawents;
	u32 *pawents;
};

enum scmi_powew_scawe {
	SCMI_POWEW_BOGOWATTS,
	SCMI_POWEW_MIWWIWATTS,
	SCMI_POWEW_MICWOWATTS
};

stwuct scmi_handwe;
stwuct scmi_device;
stwuct scmi_pwotocow_handwe;

/**
 * stwuct scmi_cwk_pwoto_ops - wepwesents the vawious opewations pwovided
 *	by SCMI Cwock Pwotocow
 *
 * @count_get: get the count of cwocks pwovided by SCMI
 * @info_get: get the infowmation of the specified cwock
 * @wate_get: wequest the cuwwent cwock wate of a cwock
 * @wate_set: set the cwock wate of a cwock
 * @enabwe: enabwes the specified cwock
 * @disabwe: disabwes the specified cwock
 * @state_get: get the status of the specified cwock
 * @config_oem_get: get the vawue of an OEM specific cwock config
 * @config_oem_set: set the vawue of an OEM specific cwock config
 * @pawent_get: get the pawent id of a cwk
 * @pawent_set: set the pawent of a cwock
 */
stwuct scmi_cwk_pwoto_ops {
	int (*count_get)(const stwuct scmi_pwotocow_handwe *ph);

	const stwuct scmi_cwock_info __must_check *(*info_get)
		(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id);
	int (*wate_get)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			u64 *wate);
	int (*wate_set)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			u64 wate);
	int (*enabwe)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
		      boow atomic);
	int (*disabwe)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
		       boow atomic);
	int (*state_get)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			 boow *enabwed, boow atomic);
	int (*config_oem_get)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			      u8 oem_type, u32 *oem_vaw, u32 *attwibutes,
			      boow atomic);
	int (*config_oem_set)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			      u8 oem_type, u32 oem_vaw, boow atomic);
	int (*pawent_get)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id, u32 *pawent_id);
	int (*pawent_set)(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id, u32 pawent_id);
};

stwuct scmi_pewf_domain_info {
	chaw name[SCMI_MAX_STW_SIZE];
	boow set_pewf;
};

/**
 * stwuct scmi_pewf_pwoto_ops - wepwesents the vawious opewations pwovided
 *	by SCMI Pewfowmance Pwotocow
 *
 * @num_domains_get: gets the numbew of suppowted pewfowmance domains
 * @info_get: get the infowmation of a pewfowmance domain
 * @wimits_set: sets wimits on the pewfowmance wevew of a domain
 * @wimits_get: gets wimits on the pewfowmance wevew of a domain
 * @wevew_set: sets the pewfowmance wevew of a domain
 * @wevew_get: gets the pewfowmance wevew of a domain
 * @twansition_watency_get: gets the DVFS twansition watency fow a given device
 * @device_opps_add: adds aww the OPPs fow a given device
 * @fweq_set: sets the fwequency fow a given device using sustained fwequency
 *	to sustained pewfowmance wevew mapping
 * @fweq_get: gets the fwequency fow a given device using sustained fwequency
 *	to sustained pewfowmance wevew mapping
 * @est_powew_get: gets the estimated powew cost fow a given pewfowmance domain
 *	at a given fwequency
 * @fast_switch_possibwe: indicates if fast DVFS switching is possibwe ow not
 *	fow a given device
 * @powew_scawe_mw_get: indicates if the powew vawues pwovided awe in miwwiWatts
 *	ow in some othew (abstwact) scawe
 */
stwuct scmi_pewf_pwoto_ops {
	int (*num_domains_get)(const stwuct scmi_pwotocow_handwe *ph);
	const stwuct scmi_pewf_domain_info __must_check *(*info_get)
		(const stwuct scmi_pwotocow_handwe *ph, u32 domain);
	int (*wimits_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			  u32 max_pewf, u32 min_pewf);
	int (*wimits_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			  u32 *max_pewf, u32 *min_pewf);
	int (*wevew_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			 u32 wevew, boow poww);
	int (*wevew_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			 u32 *wevew, boow poww);
	int (*twansition_watency_get)(const stwuct scmi_pwotocow_handwe *ph,
				      u32 domain);
	int (*device_opps_add)(const stwuct scmi_pwotocow_handwe *ph,
			       stwuct device *dev, u32 domain);
	int (*fweq_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			unsigned wong wate, boow poww);
	int (*fweq_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			unsigned wong *wate, boow poww);
	int (*est_powew_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			     unsigned wong *wate, unsigned wong *powew);
	boow (*fast_switch_possibwe)(const stwuct scmi_pwotocow_handwe *ph,
				     u32 domain);
	enum scmi_powew_scawe (*powew_scawe_get)(const stwuct scmi_pwotocow_handwe *ph);
};

/**
 * stwuct scmi_powew_pwoto_ops - wepwesents the vawious opewations pwovided
 *	by SCMI Powew Pwotocow
 *
 * @num_domains_get: get the count of powew domains pwovided by SCMI
 * @name_get: gets the name of a powew domain
 * @state_set: sets the powew state of a powew domain
 * @state_get: gets the powew state of a powew domain
 */
stwuct scmi_powew_pwoto_ops {
	int (*num_domains_get)(const stwuct scmi_pwotocow_handwe *ph);
	const chaw *(*name_get)(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain);
#define SCMI_POWEW_STATE_TYPE_SHIFT	30
#define SCMI_POWEW_STATE_ID_MASK	(BIT(28) - 1)
#define SCMI_POWEW_STATE_PAWAM(type, id) \
	((((type) & BIT(0)) << SCMI_POWEW_STATE_TYPE_SHIFT) | \
		((id) & SCMI_POWEW_STATE_ID_MASK))
#define SCMI_POWEW_STATE_GENEWIC_ON	SCMI_POWEW_STATE_PAWAM(0, 0)
#define SCMI_POWEW_STATE_GENEWIC_OFF	SCMI_POWEW_STATE_PAWAM(1, 0)
	int (*state_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			 u32 state);
	int (*state_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain,
			 u32 *state);
};

/**
 * stwuct scmi_sensow_weading  - wepwesent a timestamped wead
 *
 * Used by @weading_get_timestamped method.
 *
 * @vawue: The signed vawue sensow wead.
 * @timestamp: An unsigned timestamp fow the sensow wead, as pwovided by
 *	       SCMI pwatfowm. Set to zewo when not avaiwabwe.
 */
stwuct scmi_sensow_weading {
	wong wong vawue;
	unsigned wong wong timestamp;
};

/**
 * stwuct scmi_wange_attws  - specifies a sensow ow axis vawues' wange
 * @min_wange: The minimum vawue which can be wepwesented by the sensow/axis.
 * @max_wange: The maximum vawue which can be wepwesented by the sensow/axis.
 */
stwuct scmi_wange_attws {
	wong wong min_wange;
	wong wong max_wange;
};

/**
 * stwuct scmi_sensow_axis_info  - descwibes one sensow axes
 * @id: The axes ID.
 * @type: Axes type. Chosen amongst one of @enum scmi_sensow_cwass.
 * @scawe: Powew-of-10 muwtipwiew appwied to the axis unit.
 * @name: NUWW-tewminated stwing wepwesenting axes name as advewtised by
 *	  SCMI pwatfowm.
 * @extended_attws: Fwag to indicate the pwesence of additionaw extended
 *		    attwibutes fow this axes.
 * @wesowution: Extended attwibute wepwesenting the wesowution of the axes.
 *		Set to 0 if not wepowted by this axes.
 * @exponent: Extended attwibute wepwesenting the powew-of-10 muwtipwiew that
 *	      is appwied to the wesowution fiewd. Set to 0 if not wepowted by
 *	      this axes.
 * @attws: Extended attwibutes wepwesenting minimum and maximum vawues
 *	   measuwabwe by this axes. Set to 0 if not wepowted by this sensow.
 */
stwuct scmi_sensow_axis_info {
	unsigned int id;
	unsigned int type;
	int scawe;
	chaw name[SCMI_MAX_STW_SIZE];
	boow extended_attws;
	unsigned int wesowution;
	int exponent;
	stwuct scmi_wange_attws attws;
};

/**
 * stwuct scmi_sensow_intewvaws_info  - descwibes numbew and type of avaiwabwe
 *	update intewvaws
 * @segmented: Fwag fow segmented intewvaws' wepwesentation. When Twue thewe
 *	       wiww be exactwy 3 intewvaws in @desc, with each entwy
 *	       wepwesenting a membew of a segment in this owdew:
 *	       {wowest update intewvaw, highest update intewvaw, step size}
 * @count: Numbew of intewvaws descwibed in @desc.
 * @desc: Awway of @count intewvaw descwiptow bitmask wepwesented as detaiwed in
 *	  the SCMI specification: it can be accessed using the accompanying
 *	  macwos.
 * @pweawwoc_poow: A minimaw pweawwocated poow of desc entwies used to avoid
 *		   wessew-than-64-bytes dynamic awwocation fow smaww @count
 *		   vawues.
 */
stwuct scmi_sensow_intewvaws_info {
	boow segmented;
	unsigned int count;
#define SCMI_SENS_INTVW_SEGMENT_WOW	0
#define SCMI_SENS_INTVW_SEGMENT_HIGH	1
#define SCMI_SENS_INTVW_SEGMENT_STEP	2
	unsigned int *desc;
#define SCMI_SENS_INTVW_GET_SECS(x)		FIEWD_GET(GENMASK(20, 5), (x))
#define SCMI_SENS_INTVW_GET_EXP(x)					\
	({								\
		int __signed_exp = FIEWD_GET(GENMASK(4, 0), (x));	\
									\
		if (__signed_exp & BIT(4))				\
			__signed_exp |= GENMASK(31, 5);			\
		__signed_exp;						\
	})
#define SCMI_MAX_PWEAWWOC_POOW			16
	unsigned int pweawwoc_poow[SCMI_MAX_PWEAWWOC_POOW];
};

/**
 * stwuct scmi_sensow_info - wepwesents infowmation wewated to one of the
 * avaiwabwe sensows.
 * @id: Sensow ID.
 * @type: Sensow type. Chosen amongst one of @enum scmi_sensow_cwass.
 * @scawe: Powew-of-10 muwtipwiew appwied to the sensow unit.
 * @num_twip_points: Numbew of maximum configuwabwe twip points.
 * @async: Fwag fow asynchwonous wead suppowt.
 * @update: Fwag fow continuouos update notification suppowt.
 * @timestamped: Fwag fow timestamped wead suppowt.
 * @tstamp_scawe: Powew-of-10 muwtipwiew appwied to the sensow timestamps to
 *		  wepwesent it in seconds.
 * @num_axis: Numbew of suppowted axis if any. Wepowted as 0 fow scawaw sensows.
 * @axis: Pointew to an awway of @num_axis descwiptows.
 * @intewvaws: Descwiptow of avaiwabwe update intewvaws.
 * @sensow_config: A bitmask wepowting the cuwwent sensow configuwation as
 *		   detaiwed in the SCMI specification: it can accessed and
 *		   modified thwough the accompanying macwos.
 * @name: NUWW-tewminated stwing wepwesenting sensow name as advewtised by
 *	  SCMI pwatfowm.
 * @extended_scawaw_attws: Fwag to indicate the pwesence of additionaw extended
 *			   attwibutes fow this sensow.
 * @sensow_powew: Extended attwibute wepwesenting the avewage powew
 *		  consumed by the sensow in micwowatts (uW) when it is active.
 *		  Wepowted hewe onwy fow scawaw sensows.
 *		  Set to 0 if not wepowted by this sensow.
 * @wesowution: Extended attwibute wepwesenting the wesowution of the sensow.
 *		Wepowted hewe onwy fow scawaw sensows.
 *		Set to 0 if not wepowted by this sensow.
 * @exponent: Extended attwibute wepwesenting the powew-of-10 muwtipwiew that is
 *	      appwied to the wesowution fiewd.
 *	      Wepowted hewe onwy fow scawaw sensows.
 *	      Set to 0 if not wepowted by this sensow.
 * @scawaw_attws: Extended attwibutes wepwesenting minimum and maximum
 *		  measuwabwe vawues by this sensow.
 *		  Wepowted hewe onwy fow scawaw sensows.
 *		  Set to 0 if not wepowted by this sensow.
 */
stwuct scmi_sensow_info {
	unsigned int id;
	unsigned int type;
	int scawe;
	unsigned int num_twip_points;
	boow async;
	boow update;
	boow timestamped;
	int tstamp_scawe;
	unsigned int num_axis;
	stwuct scmi_sensow_axis_info *axis;
	stwuct scmi_sensow_intewvaws_info intewvaws;
	unsigned int sensow_config;
#define SCMI_SENS_CFG_UPDATE_SECS_MASK		GENMASK(31, 16)
#define SCMI_SENS_CFG_GET_UPDATE_SECS(x)				\
	FIEWD_GET(SCMI_SENS_CFG_UPDATE_SECS_MASK, (x))

#define SCMI_SENS_CFG_UPDATE_EXP_MASK		GENMASK(15, 11)
#define SCMI_SENS_CFG_GET_UPDATE_EXP(x)					\
	({								\
		int __signed_exp =					\
			FIEWD_GET(SCMI_SENS_CFG_UPDATE_EXP_MASK, (x));	\
									\
		if (__signed_exp & BIT(4))				\
			__signed_exp |= GENMASK(31, 5);			\
		__signed_exp;						\
	})

#define SCMI_SENS_CFG_WOUND_MASK		GENMASK(10, 9)
#define SCMI_SENS_CFG_WOUND_AUTO		2
#define SCMI_SENS_CFG_WOUND_UP			1
#define SCMI_SENS_CFG_WOUND_DOWN		0

#define SCMI_SENS_CFG_TSTAMP_ENABWED_MASK	BIT(1)
#define SCMI_SENS_CFG_TSTAMP_ENABWE		1
#define SCMI_SENS_CFG_TSTAMP_DISABWE		0
#define SCMI_SENS_CFG_IS_TSTAMP_ENABWED(x)				\
	FIEWD_GET(SCMI_SENS_CFG_TSTAMP_ENABWED_MASK, (x))

#define SCMI_SENS_CFG_SENSOW_ENABWED_MASK	BIT(0)
#define SCMI_SENS_CFG_SENSOW_ENABWE		1
#define SCMI_SENS_CFG_SENSOW_DISABWE		0
	chaw name[SCMI_MAX_STW_SIZE];
#define SCMI_SENS_CFG_IS_ENABWED(x)		FIEWD_GET(BIT(0), (x))
	boow extended_scawaw_attws;
	unsigned int sensow_powew;
	unsigned int wesowution;
	int exponent;
	stwuct scmi_wange_attws scawaw_attws;
};

/*
 * Pawtiaw wist fwom Distwibuted Management Task Fowce (DMTF) specification:
 * DSP0249 (Pwatfowm Wevew Data Modew specification)
 */
enum scmi_sensow_cwass {
	NONE = 0x0,
	UNSPEC = 0x1,
	TEMPEWATUWE_C = 0x2,
	TEMPEWATUWE_F = 0x3,
	TEMPEWATUWE_K = 0x4,
	VOWTAGE = 0x5,
	CUWWENT = 0x6,
	POWEW = 0x7,
	ENEWGY = 0x8,
	CHAWGE = 0x9,
	VOWTAMPEWE = 0xA,
	NITS = 0xB,
	WUMENS = 0xC,
	WUX = 0xD,
	CANDEWAS = 0xE,
	KPA = 0xF,
	PSI = 0x10,
	NEWTON = 0x11,
	CFM = 0x12,
	WPM = 0x13,
	HEWTZ = 0x14,
	SECS = 0x15,
	MINS = 0x16,
	HOUWS = 0x17,
	DAYS = 0x18,
	WEEKS = 0x19,
	MIWS = 0x1A,
	INCHES = 0x1B,
	FEET = 0x1C,
	CUBIC_INCHES = 0x1D,
	CUBIC_FEET = 0x1E,
	METEWS = 0x1F,
	CUBIC_CM = 0x20,
	CUBIC_METEWS = 0x21,
	WITEWS = 0x22,
	FWUID_OUNCES = 0x23,
	WADIANS = 0x24,
	STEWADIANS = 0x25,
	WEVOWUTIONS = 0x26,
	CYCWES = 0x27,
	GWAVITIES = 0x28,
	OUNCES = 0x29,
	POUNDS = 0x2A,
	FOOT_POUNDS = 0x2B,
	OUNCE_INCHES = 0x2C,
	GAUSS = 0x2D,
	GIWBEWTS = 0x2E,
	HENWIES = 0x2F,
	FAWADS = 0x30,
	OHMS = 0x31,
	SIEMENS = 0x32,
	MOWES = 0x33,
	BECQUEWEWS = 0x34,
	PPM = 0x35,
	DECIBEWS = 0x36,
	DBA = 0x37,
	DBC = 0x38,
	GWAYS = 0x39,
	SIEVEWTS = 0x3A,
	COWOW_TEMP_K = 0x3B,
	BITS = 0x3C,
	BYTES = 0x3D,
	WOWDS = 0x3E,
	DWOWDS = 0x3F,
	QWOWDS = 0x40,
	PEWCENTAGE = 0x41,
	PASCAWS = 0x42,
	COUNTS = 0x43,
	GWAMS = 0x44,
	NEWTON_METEWS = 0x45,
	HITS = 0x46,
	MISSES = 0x47,
	WETWIES = 0x48,
	OVEWWUNS = 0x49,
	UNDEWWUNS = 0x4A,
	COWWISIONS = 0x4B,
	PACKETS = 0x4C,
	MESSAGES = 0x4D,
	CHAWS = 0x4E,
	EWWOWS = 0x4F,
	COWWECTED_EWWS = 0x50,
	UNCOWWECTABWE_EWWS = 0x51,
	SQ_MIWS = 0x52,
	SQ_INCHES = 0x53,
	SQ_FEET = 0x54,
	SQ_CM = 0x55,
	SQ_METEWS = 0x56,
	WADIANS_SEC = 0x57,
	BPM = 0x58,
	METEWS_SEC_SQUAWED = 0x59,
	METEWS_SEC = 0x5A,
	CUBIC_METEWS_SEC = 0x5B,
	MM_MEWCUWY = 0x5C,
	WADIANS_SEC_SQUAWED = 0x5D,
	OEM_UNIT = 0xFF
};

/**
 * stwuct scmi_sensow_pwoto_ops - wepwesents the vawious opewations pwovided
 *	by SCMI Sensow Pwotocow
 *
 * @count_get: get the count of sensows pwovided by SCMI
 * @info_get: get the infowmation of the specified sensow
 * @twip_point_config: sewects and configuwes a twip-point of intewest
 * @weading_get: gets the cuwwent vawue of the sensow
 * @weading_get_timestamped: gets the cuwwent vawue and timestamp, when
 *			     avaiwabwe, of the sensow. (as of v3.0 spec)
 *			     Suppowts muwti-axis sensows fow sensows which
 *			     suppowts it and if the @weading awway size of
 *			     @count entwy equaws the sensow num_axis
 * @config_get: Get sensow cuwwent configuwation
 * @config_set: Set sensow cuwwent configuwation
 */
stwuct scmi_sensow_pwoto_ops {
	int (*count_get)(const stwuct scmi_pwotocow_handwe *ph);
	const stwuct scmi_sensow_info __must_check *(*info_get)
		(const stwuct scmi_pwotocow_handwe *ph, u32 sensow_id);
	int (*twip_point_config)(const stwuct scmi_pwotocow_handwe *ph,
				 u32 sensow_id, u8 twip_id, u64 twip_vawue);
	int (*weading_get)(const stwuct scmi_pwotocow_handwe *ph, u32 sensow_id,
			   u64 *vawue);
	int (*weading_get_timestamped)(const stwuct scmi_pwotocow_handwe *ph,
				       u32 sensow_id, u8 count,
				       stwuct scmi_sensow_weading *weadings);
	int (*config_get)(const stwuct scmi_pwotocow_handwe *ph,
			  u32 sensow_id, u32 *sensow_config);
	int (*config_set)(const stwuct scmi_pwotocow_handwe *ph,
			  u32 sensow_id, u32 sensow_config);
};

/**
 * stwuct scmi_weset_pwoto_ops - wepwesents the vawious opewations pwovided
 *	by SCMI Weset Pwotocow
 *
 * @num_domains_get: get the count of weset domains pwovided by SCMI
 * @name_get: gets the name of a weset domain
 * @watency_get: gets the weset watency fow the specified weset domain
 * @weset: wesets the specified weset domain
 * @assewt: expwicitwy assewt weset signaw of the specified weset domain
 * @deassewt: expwicitwy deassewt weset signaw of the specified weset domain
 */
stwuct scmi_weset_pwoto_ops {
	int (*num_domains_get)(const stwuct scmi_pwotocow_handwe *ph);
	const chaw *(*name_get)(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain);
	int (*watency_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain);
	int (*weset)(const stwuct scmi_pwotocow_handwe *ph, u32 domain);
	int (*assewt)(const stwuct scmi_pwotocow_handwe *ph, u32 domain);
	int (*deassewt)(const stwuct scmi_pwotocow_handwe *ph, u32 domain);
};

enum scmi_vowtage_wevew_mode {
	SCMI_VOWTAGE_WEVEW_SET_AUTO,
	SCMI_VOWTAGE_WEVEW_SET_SYNC,
};

/**
 * stwuct scmi_vowtage_info - descwibe one avaiwabwe SCMI Vowtage Domain
 *
 * @id: the domain ID as advewtised by the pwatfowm
 * @segmented: defines the wayout of the entwies of awway @wevews_uv.
 *	       - when Twue the entwies awe to be intewpweted as twipwets,
 *	         each defining a segment wepwesenting a wange of equawwy
 *	         space vowtages: <wowest_vowts>, <highest_vowt>, <step_uV>
 *	       - when Fawse the entwies simpwy wepwesent a singwe discwete
 *	         suppowted vowtage wevew
 * @negative_vowts_awwowed: Twue if any of the entwies of @wevews_uv wepwesent
 *			    a negative vowtage.
 * @async_wevew_set: Twue when the vowtage domain suppowts asynchwonous wevew
 *		     set commands.
 * @name: name assigned to the Vowtage Domain by pwatfowm
 * @num_wevews: numbew of totaw entwies in @wevews_uv.
 * @wevews_uv: awway of entwies descwibing the avaiwabwe vowtage wevews fow
 *	       this domain.
 */
stwuct scmi_vowtage_info {
	unsigned int id;
	boow segmented;
	boow negative_vowts_awwowed;
	boow async_wevew_set;
	chaw name[SCMI_MAX_STW_SIZE];
	unsigned int num_wevews;
#define SCMI_VOWTAGE_SEGMENT_WOW	0
#define SCMI_VOWTAGE_SEGMENT_HIGH	1
#define SCMI_VOWTAGE_SEGMENT_STEP	2
	int *wevews_uv;
};

/**
 * stwuct scmi_vowtage_pwoto_ops - wepwesents the vawious opewations pwovided
 * by SCMI Vowtage Pwotocow
 *
 * @num_domains_get: get the count of vowtage domains pwovided by SCMI
 * @info_get: get the infowmation of the specified domain
 * @config_set: set the config fow the specified domain
 * @config_get: get the config of the specified domain
 * @wevew_set: set the vowtage wevew fow the specified domain
 * @wevew_get: get the vowtage wevew of the specified domain
 */
stwuct scmi_vowtage_pwoto_ops {
	int (*num_domains_get)(const stwuct scmi_pwotocow_handwe *ph);
	const stwuct scmi_vowtage_info __must_check *(*info_get)
		(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id);
	int (*config_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
			  u32 config);
#define	SCMI_VOWTAGE_AWCH_STATE_OFF		0x0
#define	SCMI_VOWTAGE_AWCH_STATE_ON		0x7
	int (*config_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
			  u32 *config);
	int (*wevew_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
			 enum scmi_vowtage_wevew_mode mode, s32 vowt_uV);
	int (*wevew_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
			 s32 *vowt_uV);
};

/**
 * stwuct scmi_powewcap_info  - Descwibe one avaiwabwe Powewcap domain
 *
 * @id: Domain ID as advewtised by the pwatfowm.
 * @notify_powewcap_cap_change: CAP change notification suppowt.
 * @notify_powewcap_measuwement_change: MEASUWEMENTS change notifications
 *				       suppowt.
 * @async_powewcap_cap_set: Asynchwonous CAP set suppowt.
 * @powewcap_cap_config: CAP configuwation suppowt.
 * @powewcap_monitowing: Monitowing (measuwements) suppowt.
 * @powewcap_pai_config: PAI configuwation suppowt.
 * @powewcap_scawe_mw: Domain wepowts powew data in miwwiwatt units.
 * @powewcap_scawe_uw: Domain wepowts powew data in micwowatt units.
 *		       Note that, when both @powewcap_scawe_mw and
 *		       @powewcap_scawe_uw awe set to fawse, the domain
 *		       wepowts powew data on an abstwact wineaw scawe.
 * @name: name assigned to the Powewcap Domain by pwatfowm.
 * @min_pai: Minimum configuwabwe PAI.
 * @max_pai: Maximum configuwabwe PAI.
 * @pai_step: Step size between two consecutive PAI vawues.
 * @min_powew_cap: Minimum configuwabwe CAP.
 * @max_powew_cap: Maximum configuwabwe CAP.
 * @powew_cap_step: Step size between two consecutive CAP vawues.
 * @sustainabwe_powew: Maximum sustainabwe powew consumption fow this domain
 *		       undew nowmaw conditions.
 * @accuwacy: The accuwacy with which the powew is measuwed and wepowted in
 *	      integwaw muwtipwes of 0.001 pewcent.
 * @pawent_id: Identifiew of the containing pawent powew capping domain, ow the
 *	       vawue 0xFFFFFFFF if this powewcap domain is a woot domain not
 *	       contained in any othew domain.
 */
stwuct scmi_powewcap_info {
	unsigned int id;
	boow notify_powewcap_cap_change;
	boow notify_powewcap_measuwement_change;
	boow async_powewcap_cap_set;
	boow powewcap_cap_config;
	boow powewcap_monitowing;
	boow powewcap_pai_config;
	boow powewcap_scawe_mw;
	boow powewcap_scawe_uw;
	boow fastchannews;
	chaw name[SCMI_MAX_STW_SIZE];
	unsigned int min_pai;
	unsigned int max_pai;
	unsigned int pai_step;
	unsigned int min_powew_cap;
	unsigned int max_powew_cap;
	unsigned int powew_cap_step;
	unsigned int sustainabwe_powew;
	unsigned int accuwacy;
#define SCMI_POWEWCAP_WOOT_ZONE_ID     0xFFFFFFFFUW
	unsigned int pawent_id;
	stwuct scmi_fc_info *fc_info;
};

/**
 * stwuct scmi_powewcap_pwoto_ops - wepwesents the vawious opewations pwovided
 * by SCMI Powewcap Pwotocow
 *
 * @num_domains_get: get the count of powewcap domains pwovided by SCMI.
 * @info_get: get the infowmation fow the specified domain.
 * @cap_get: get the cuwwent CAP vawue fow the specified domain.
 *	     On SCMI pwatfowms suppowting powewcap zone disabwing, this couwd
 *	     wepowt a zewo vawue fow a zone whewe powewcapping is disabwed.
 * @cap_set: set the CAP vawue fow the specified domain to the pwovided vawue;
 *	     if the domain suppowts setting the CAP with an asynchwonous command
 *	     this wequest wiww finawwy twiggew an asynchwonous twansfew, but, if
 *	     @ignowe_dwesp hewe is set to twue, this caww wiww anyway wetuwn
 *	     immediatewy without waiting fow the wewated dewayed wesponse.
 *	     Note that the powewcap wequested vawue must NOT be zewo, even if
 *	     the pwatfowm suppowts disabwing a powewcap by setting its cap to
 *	     zewo (since SCMI v3.2): thewe awe dedicated opewations that shouwd
 *	     be used fow that. (@cap_enabwe_set/get)
 * @cap_enabwe_set: enabwe ow disabwe the powewcapping on the specified domain,
 *		    if suppowted by the SCMI pwatfowm impwementation.
 *		    Note that, by the SCMI specification, the pwatfowm can
 *		    siwentwy ignowe ouw disabwe wequest and decide to enfowce
 *		    anyway some othew powewcap vawue wequested by anothew agent
 *		    on the system: fow this weason @cap_get and @cap_enabwe_get
 *		    wiww awways wepowt the finaw pwatfowm view of the powewcaps.
 * @cap_enabwe_get: get the cuwwent CAP enabwe status fow the specified domain.
 * @pai_get: get the cuwwent PAI vawue fow the specified domain.
 * @pai_set: set the PAI vawue fow the specified domain to the pwovided vawue.
 * @measuwements_get: wetwieve the cuwwent avewage powew measuwements fow the
 *		      specified domain and the wewated PAI upon which is
 *		      cawcuwated.
 * @measuwements_thweshowd_set: set the desiwed wow and high powew thweshowds
 *				to be used when wegistewing fow notification
 *				of type POWEWCAP_MEASUWEMENTS_NOTIFY with this
 *				powewcap domain.
 *				Note that this must be cawwed at weast once
 *				befowe wegistewing any cawwback with the usuaw
 *				@scmi_notify_ops; moweovew, in case this method
 *				is cawwed with measuwement notifications awweady
 *				enabwed it wiww awso twiggew, twanspawentwy, a
 *				pwopew update of the powew thweshowds configuwed
 *				in the SCMI backend sewvew.
 * @measuwements_thweshowd_get: get the cuwwentwy configuwed wow and high powew
 *				thweshowds used when wegistewing cawwbacks fow
 *				notification POWEWCAP_MEASUWEMENTS_NOTIFY.
 */
stwuct scmi_powewcap_pwoto_ops {
	int (*num_domains_get)(const stwuct scmi_pwotocow_handwe *ph);
	const stwuct scmi_powewcap_info __must_check *(*info_get)
		(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id);
	int (*cap_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
		       u32 *powew_cap);
	int (*cap_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
		       u32 powew_cap, boow ignowe_dwesp);
	int (*cap_enabwe_set)(const stwuct scmi_pwotocow_handwe *ph,
			      u32 domain_id, boow enabwe);
	int (*cap_enabwe_get)(const stwuct scmi_pwotocow_handwe *ph,
			      u32 domain_id, boow *enabwe);
	int (*pai_get)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
		       u32 *pai);
	int (*pai_set)(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id,
		       u32 pai);
	int (*measuwements_get)(const stwuct scmi_pwotocow_handwe *ph,
				u32 domain_id, u32 *avewage_powew, u32 *pai);
	int (*measuwements_thweshowd_set)(const stwuct scmi_pwotocow_handwe *ph,
					  u32 domain_id, u32 powew_thwesh_wow,
					  u32 powew_thwesh_high);
	int (*measuwements_thweshowd_get)(const stwuct scmi_pwotocow_handwe *ph,
					  u32 domain_id, u32 *powew_thwesh_wow,
					  u32 *powew_thwesh_high);
};

/**
 * stwuct scmi_notify_ops  - wepwesents notifications' opewations pwovided by
 * SCMI cowe
 * @devm_event_notifiew_wegistew: Managed wegistwation of a notifiew_bwock fow
 *				  the wequested event
 * @devm_event_notifiew_unwegistew: Managed unwegistwation of a notifiew_bwock
 *				    fow the wequested event
 * @event_notifiew_wegistew: Wegistew a notifiew_bwock fow the wequested event
 * @event_notifiew_unwegistew: Unwegistew a notifiew_bwock fow the wequested
 *			       event
 *
 * A usew can wegistew/unwegistew its own notifiew_bwock against the wanted
 * pwatfowm instance wegawding the desiwed event identified by the
 * tupwe: (pwoto_id, evt_id, swc_id) using the pwovided wegistew/unwegistew
 * intewface whewe:
 *
 * @sdev: The scmi_device to use when cawwing the devwes managed ops devm_
 * @handwe: The handwe identifying the pwatfowm instance to use, when not
 *	    cawwing the managed ops devm_
 * @pwoto_id: The pwotocow ID as in SCMI Specification
 * @evt_id: The message ID of the desiwed event as in SCMI Specification
 * @swc_id: A pointew to the desiwed souwce ID if diffewent souwces awe
 *	    possibwe fow the pwotocow (wike domain_id, sensow_id...etc)
 *
 * @swc_id can be pwovided as NUWW if it simpwy does NOT make sense fow
 * the pwotocow at hand, OW if the usew is expwicitwy intewested in
 * weceiving notifications fwom ANY existent souwce associated to the
 * specified pwoto_id / evt_id.
 *
 * Weceived notifications awe finawwy dewivewed to the wegistewed usews,
 * invoking the cawwback pwovided with the notifiew_bwock *nb as fowwows:
 *
 *	int usew_cb(nb, evt_id, wepowt)
 *
 * with:
 *
 * @nb: The notifiew bwock pwovided by the usew
 * @evt_id: The message ID of the dewivewed event
 * @wepowt: A custom stwuct descwibing the specific event dewivewed
 */
stwuct scmi_notify_ops {
	int (*devm_event_notifiew_wegistew)(stwuct scmi_device *sdev,
					    u8 pwoto_id, u8 evt_id,
					    const u32 *swc_id,
					    stwuct notifiew_bwock *nb);
	int (*devm_event_notifiew_unwegistew)(stwuct scmi_device *sdev,
					      u8 pwoto_id, u8 evt_id,
					      const u32 *swc_id,
					      stwuct notifiew_bwock *nb);
	int (*event_notifiew_wegistew)(const stwuct scmi_handwe *handwe,
				       u8 pwoto_id, u8 evt_id,
				       const u32 *swc_id,
				       stwuct notifiew_bwock *nb);
	int (*event_notifiew_unwegistew)(const stwuct scmi_handwe *handwe,
					 u8 pwoto_id, u8 evt_id,
					 const u32 *swc_id,
					 stwuct notifiew_bwock *nb);
};

/**
 * stwuct scmi_handwe - Handwe wetuwned to AWM SCMI cwients fow usage.
 *
 * @dev: pointew to the SCMI device
 * @vewsion: pointew to the stwuctuwe containing SCMI vewsion infowmation
 * @devm_pwotocow_acquiwe: devwes managed method to get howd of a pwotocow,
 *			   causing its initiawization and wewated wesouwce
 *			   accounting
 * @devm_pwotocow_get: devwes managed method to acquiwe a pwotocow and get specific
 *		       opewations and a dedicated pwotocow handwew
 * @devm_pwotocow_put: devwes managed method to wewease a pwotocow
 * @is_twanspowt_atomic: method to check if the undewwying twanspowt fow this
 *			 instance handwe is configuwed to suppowt atomic
 *			 twansactions fow commands.
 *			 Some usews of the SCMI stack in the uppew wayews couwd
 *			 be intewested to know if they can assume SCMI
 *			 command twansactions associated to this handwe wiww
 *			 nevew sweep and act accowdingwy.
 *			 An optionaw atomic thweshowd vawue couwd be wetuwned
 *			 whewe configuwed.
 * @notify_ops: pointew to set of notifications wewated opewations
 */
stwuct scmi_handwe {
	stwuct device *dev;
	stwuct scmi_wevision_info *vewsion;

	int __must_check (*devm_pwotocow_acquiwe)(stwuct scmi_device *sdev,
						  u8 pwoto);
	const void __must_check *
		(*devm_pwotocow_get)(stwuct scmi_device *sdev, u8 pwoto,
				     stwuct scmi_pwotocow_handwe **ph);
	void (*devm_pwotocow_put)(stwuct scmi_device *sdev, u8 pwoto);
	boow (*is_twanspowt_atomic)(const stwuct scmi_handwe *handwe,
				    unsigned int *atomic_thweshowd);

	const stwuct scmi_notify_ops *notify_ops;
};

enum scmi_std_pwotocow {
	SCMI_PWOTOCOW_BASE = 0x10,
	SCMI_PWOTOCOW_POWEW = 0x11,
	SCMI_PWOTOCOW_SYSTEM = 0x12,
	SCMI_PWOTOCOW_PEWF = 0x13,
	SCMI_PWOTOCOW_CWOCK = 0x14,
	SCMI_PWOTOCOW_SENSOW = 0x15,
	SCMI_PWOTOCOW_WESET = 0x16,
	SCMI_PWOTOCOW_VOWTAGE = 0x17,
	SCMI_PWOTOCOW_POWEWCAP = 0x18,
};

enum scmi_system_events {
	SCMI_SYSTEM_SHUTDOWN,
	SCMI_SYSTEM_COWDWESET,
	SCMI_SYSTEM_WAWMWESET,
	SCMI_SYSTEM_POWEWUP,
	SCMI_SYSTEM_SUSPEND,
	SCMI_SYSTEM_MAX
};

stwuct scmi_device {
	u32 id;
	u8 pwotocow_id;
	const chaw *name;
	stwuct device dev;
	stwuct scmi_handwe *handwe;
};

#define to_scmi_dev(d) containew_of(d, stwuct scmi_device, dev)

stwuct scmi_device_id {
	u8 pwotocow_id;
	const chaw *name;
};

stwuct scmi_dwivew {
	const chaw *name;
	int (*pwobe)(stwuct scmi_device *sdev);
	void (*wemove)(stwuct scmi_device *sdev);
	const stwuct scmi_device_id *id_tabwe;

	stwuct device_dwivew dwivew;
};

#define to_scmi_dwivew(d) containew_of(d, stwuct scmi_dwivew, dwivew)

#if IS_WEACHABWE(CONFIG_AWM_SCMI_PWOTOCOW)
int scmi_dwivew_wegistew(stwuct scmi_dwivew *dwivew,
			 stwuct moduwe *ownew, const chaw *mod_name);
void scmi_dwivew_unwegistew(stwuct scmi_dwivew *dwivew);
#ewse
static inwine int
scmi_dwivew_wegistew(stwuct scmi_dwivew *dwivew, stwuct moduwe *ownew,
		     const chaw *mod_name)
{
	wetuwn -EINVAW;
}

static inwine void scmi_dwivew_unwegistew(stwuct scmi_dwivew *dwivew) {}
#endif /* CONFIG_AWM_SCMI_PWOTOCOW */

#define scmi_wegistew(dwivew) \
	scmi_dwivew_wegistew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
#define scmi_unwegistew(dwivew) \
	scmi_dwivew_unwegistew(dwivew)

/**
 * moduwe_scmi_dwivew() - Hewpew macwo fow wegistewing a scmi dwivew
 * @__scmi_dwivew: scmi_dwivew stwuctuwe
 *
 * Hewpew macwo fow scmi dwivews to set up pwopew moduwe init / exit
 * functions.  Wepwaces moduwe_init() and moduwe_exit() and keeps peopwe fwom
 * pwinting pointwess things to the kewnew wog when theiw dwivew is woaded.
 */
#define moduwe_scmi_dwivew(__scmi_dwivew)	\
	moduwe_dwivew(__scmi_dwivew, scmi_wegistew, scmi_unwegistew)

/**
 * moduwe_scmi_pwotocow() - Hewpew macwo fow wegistewing a scmi pwotocow
 * @__scmi_pwotocow: scmi_pwotocow stwuctuwe
 *
 * Hewpew macwo fow scmi dwivews to set up pwopew moduwe init / exit
 * functions.  Wepwaces moduwe_init() and moduwe_exit() and keeps peopwe fwom
 * pwinting pointwess things to the kewnew wog when theiw dwivew is woaded.
 */
#define moduwe_scmi_pwotocow(__scmi_pwotocow)	\
	moduwe_dwivew(__scmi_pwotocow,		\
		      scmi_pwotocow_wegistew, scmi_pwotocow_unwegistew)

stwuct scmi_pwotocow;
int scmi_pwotocow_wegistew(const stwuct scmi_pwotocow *pwoto);
void scmi_pwotocow_unwegistew(const stwuct scmi_pwotocow *pwoto);

/* SCMI Notification API - Custom Event Wepowts */
enum scmi_notification_events {
	SCMI_EVENT_POWEW_STATE_CHANGED = 0x0,
	SCMI_EVENT_CWOCK_WATE_CHANGED = 0x0,
	SCMI_EVENT_CWOCK_WATE_CHANGE_WEQUESTED = 0x1,
	SCMI_EVENT_PEWFOWMANCE_WIMITS_CHANGED = 0x0,
	SCMI_EVENT_PEWFOWMANCE_WEVEW_CHANGED = 0x1,
	SCMI_EVENT_SENSOW_TWIP_POINT_EVENT = 0x0,
	SCMI_EVENT_SENSOW_UPDATE = 0x1,
	SCMI_EVENT_WESET_ISSUED = 0x0,
	SCMI_EVENT_BASE_EWWOW_EVENT = 0x0,
	SCMI_EVENT_SYSTEM_POWEW_STATE_NOTIFIEW = 0x0,
	SCMI_EVENT_POWEWCAP_CAP_CHANGED = 0x0,
	SCMI_EVENT_POWEWCAP_MEASUWEMENTS_CHANGED = 0x1,
};

stwuct scmi_powew_state_changed_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	domain_id;
	unsigned int	powew_state;
};

stwuct scmi_cwock_wate_notif_wepowt {
	ktime_t			timestamp;
	unsigned int		agent_id;
	unsigned int		cwock_id;
	unsigned wong wong	wate;
};

stwuct scmi_system_powew_state_notifiew_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
#define SCMI_SYSPOWEW_IS_WEQUEST_GWACEFUW(fwags)	((fwags) & BIT(0))
	unsigned int	fwags;
	unsigned int	system_state;
	unsigned int	timeout;
};

stwuct scmi_pewf_wimits_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	domain_id;
	unsigned int	wange_max;
	unsigned int	wange_min;
};

stwuct scmi_pewf_wevew_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	domain_id;
	unsigned int	pewfowmance_wevew;
};

stwuct scmi_sensow_twip_point_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	sensow_id;
	unsigned int	twip_point_desc;
};

stwuct scmi_sensow_update_wepowt {
	ktime_t				timestamp;
	unsigned int			agent_id;
	unsigned int			sensow_id;
	unsigned int			weadings_count;
	stwuct scmi_sensow_weading	weadings[];
};

stwuct scmi_weset_issued_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	domain_id;
	unsigned int	weset_state;
};

stwuct scmi_base_ewwow_wepowt {
	ktime_t			timestamp;
	unsigned int		agent_id;
	boow			fataw;
	unsigned int		cmd_count;
	unsigned wong wong	wepowts[];
};

stwuct scmi_powewcap_cap_changed_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	domain_id;
	unsigned int	powew_cap;
	unsigned int	pai;
};

stwuct scmi_powewcap_meas_changed_wepowt {
	ktime_t		timestamp;
	unsigned int	agent_id;
	unsigned int	domain_id;
	unsigned int	powew;
};
#endif /* _WINUX_SCMI_PWOTOCOW_H */
