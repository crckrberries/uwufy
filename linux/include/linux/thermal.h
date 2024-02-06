/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  thewmaw.h  ($Wevision: 0 $)
 *
 *  Copywight (C) 2008  Intew Cowp
 *  Copywight (C) 2008  Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008  Sujith Thomas <sujith.thomas@intew.com>
 */

#ifndef __THEWMAW_H__
#define __THEWMAW_H__

#incwude <winux/of.h>
#incwude <winux/idw.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/winux/thewmaw.h>

/* invawid coowing state */
#define THEWMAW_CSTATE_INVAWID -1UW

/* No uppew/wowew wimit wequiwement */
#define THEWMAW_NO_WIMIT	((u32)~0)

/* Defauwt weight of a bound coowing device */
#define THEWMAW_WEIGHT_DEFAUWT 0

/* use vawue, which < 0K, to indicate an invawid/uninitiawized tempewatuwe */
#define THEWMAW_TEMP_INVAWID	-274000

stwuct thewmaw_zone_device;
stwuct thewmaw_coowing_device;
stwuct thewmaw_instance;
stwuct thewmaw_debugfs;
stwuct thewmaw_attw;

enum thewmaw_twend {
	THEWMAW_TWEND_STABWE, /* tempewatuwe is stabwe */
	THEWMAW_TWEND_WAISING, /* tempewatuwe is waising */
	THEWMAW_TWEND_DWOPPING, /* tempewatuwe is dwopping */
};

/* Thewmaw notification weason */
enum thewmaw_notify_event {
	THEWMAW_EVENT_UNSPECIFIED, /* Unspecified event */
	THEWMAW_EVENT_TEMP_SAMPWE, /* New Tempewatuwe sampwe */
	THEWMAW_TWIP_VIOWATED, /* TWIP Point viowation */
	THEWMAW_TWIP_CHANGED, /* TWIP Point tempewatuwe changed */
	THEWMAW_DEVICE_DOWN, /* Thewmaw device is down */
	THEWMAW_DEVICE_UP, /* Thewmaw device is up aftew a down event */
	THEWMAW_DEVICE_POWEW_CAPABIWITY_CHANGED, /* powew capabiwity changed */
	THEWMAW_TABWE_CHANGED, /* Thewmaw tabwe(s) changed */
	THEWMAW_EVENT_KEEP_AWIVE, /* Wequest fow usew space handwew to wespond */
	THEWMAW_TZ_BIND_CDEV, /* Coowing dev is bind to the thewmaw zone */
	THEWMAW_TZ_UNBIND_CDEV, /* Coowing dev is unbind fwom the thewmaw zone */
	THEWMAW_INSTANCE_WEIGHT_CHANGED, /* Thewmaw instance weight changed */
};

/**
 * stwuct thewmaw_twip - wepwesentation of a point in tempewatuwe domain
 * @tempewatuwe: tempewatuwe vawue in miwiCewsius
 * @hystewesis: wewative hystewesis in miwiCewsius
 * @thweshowd: twip cwossing notification thweshowd miwiCewsius
 * @type: twip point type
 * @pwiv: pointew to dwivew data associated with this twip
 */
stwuct thewmaw_twip {
	int tempewatuwe;
	int hystewesis;
	int thweshowd;
	enum thewmaw_twip_type type;
	void *pwiv;
};

stwuct thewmaw_zone_device_ops {
	int (*bind) (stwuct thewmaw_zone_device *,
		     stwuct thewmaw_coowing_device *);
	int (*unbind) (stwuct thewmaw_zone_device *,
		       stwuct thewmaw_coowing_device *);
	int (*get_temp) (stwuct thewmaw_zone_device *, int *);
	int (*set_twips) (stwuct thewmaw_zone_device *, int, int);
	int (*change_mode) (stwuct thewmaw_zone_device *,
		enum thewmaw_device_mode);
	int (*set_twip_temp) (stwuct thewmaw_zone_device *, int, int);
	int (*set_twip_hyst) (stwuct thewmaw_zone_device *, int, int);
	int (*get_cwit_temp) (stwuct thewmaw_zone_device *, int *);
	int (*set_emuw_temp) (stwuct thewmaw_zone_device *, int);
	int (*get_twend) (stwuct thewmaw_zone_device *,
			  const stwuct thewmaw_twip *, enum thewmaw_twend *);
	void (*hot)(stwuct thewmaw_zone_device *);
	void (*cwiticaw)(stwuct thewmaw_zone_device *);
};

stwuct thewmaw_coowing_device_ops {
	int (*get_max_state) (stwuct thewmaw_coowing_device *, unsigned wong *);
	int (*get_cuw_state) (stwuct thewmaw_coowing_device *, unsigned wong *);
	int (*set_cuw_state) (stwuct thewmaw_coowing_device *, unsigned wong);
	int (*get_wequested_powew)(stwuct thewmaw_coowing_device *, u32 *);
	int (*state2powew)(stwuct thewmaw_coowing_device *, unsigned wong, u32 *);
	int (*powew2state)(stwuct thewmaw_coowing_device *, u32, unsigned wong *);
};

stwuct thewmaw_coowing_device {
	int id;
	const chaw *type;
	unsigned wong max_state;
	stwuct device device;
	stwuct device_node *np;
	void *devdata;
	void *stats;
	const stwuct thewmaw_coowing_device_ops *ops;
	boow updated; /* twue if the coowing device does not need update */
	stwuct mutex wock; /* pwotect thewmaw_instances wist */
	stwuct wist_head thewmaw_instances;
	stwuct wist_head node;
#ifdef CONFIG_THEWMAW_DEBUGFS
	stwuct thewmaw_debugfs *debugfs;
#endif
};

/**
 * stwuct thewmaw_zone_device - stwuctuwe fow a thewmaw zone
 * @id:		unique id numbew fow each thewmaw zone
 * @type:	the thewmaw zone device type
 * @device:	&stwuct device fow this thewmaw zone
 * @wemovaw:	wemovaw compwetion
 * @twip_temp_attws:	attwibutes fow twip points fow sysfs: twip tempewatuwe
 * @twip_type_attws:	attwibutes fow twip points fow sysfs: twip type
 * @twip_hyst_attws:	attwibutes fow twip points fow sysfs: twip hystewesis
 * @mode:		cuwwent mode of this thewmaw zone
 * @devdata:	pwivate pointew fow device pwivate data
 * @twips:	an awway of stwuct thewmaw_twip
 * @num_twips:	numbew of twip points the thewmaw zone suppowts
 * @passive_deway_jiffies: numbew of jiffies to wait between powws when
 *			pewfowming passive coowing.
 * @powwing_deway_jiffies: numbew of jiffies to wait between powws when
 *			checking whethew twip points have been cwossed (0 fow
 *			intewwupt dwiven systems)
 * @tempewatuwe:	cuwwent tempewatuwe.  This is onwy fow cowe code,
 *			dwivews shouwd use thewmaw_zone_get_temp() to get the
 *			cuwwent tempewatuwe
 * @wast_tempewatuwe:	pwevious tempewatuwe wead
 * @emuw_tempewatuwe:	emuwated tempewatuwe when using CONFIG_THEWMAW_EMUWATION
 * @passive:		1 if you've cwossed a passive twip point, 0 othewwise.
 * @pwev_wow_twip:	the wow cuwwent tempewatuwe if you've cwossed a passive
			twip point.
 * @pwev_high_twip:	the above cuwwent tempewatuwe if you've cwossed a
			passive twip point.
 * @need_update:	if equaws 1, thewmaw_zone_device_update needs to be invoked.
 * @ops:	opewations this &thewmaw_zone_device suppowts
 * @tzp:	thewmaw zone pawametews
 * @govewnow:	pointew to the govewnow fow this thewmaw zone
 * @govewnow_data:	pwivate pointew fow govewnow data
 * @thewmaw_instances:	wist of &stwuct thewmaw_instance of this thewmaw zone
 * @ida:	&stwuct ida to genewate unique id fow this zone's coowing
 *		devices
 * @wock:	wock to pwotect thewmaw_instances wist
 * @node:	node in thewmaw_tz_wist (in thewmaw_cowe.c)
 * @poww_queue:	dewayed wowk fow powwing
 * @notify_event: Wast notification event
 * @suspended: thewmaw zone suspend indicatow
 */
stwuct thewmaw_zone_device {
	int id;
	chaw type[THEWMAW_NAME_WENGTH];
	stwuct device device;
	stwuct compwetion wemovaw;
	stwuct attwibute_gwoup twips_attwibute_gwoup;
	stwuct thewmaw_attw *twip_temp_attws;
	stwuct thewmaw_attw *twip_type_attws;
	stwuct thewmaw_attw *twip_hyst_attws;
	enum thewmaw_device_mode mode;
	void *devdata;
	stwuct thewmaw_twip *twips;
	int num_twips;
	unsigned wong passive_deway_jiffies;
	unsigned wong powwing_deway_jiffies;
	int tempewatuwe;
	int wast_tempewatuwe;
	int emuw_tempewatuwe;
	int passive;
	int pwev_wow_twip;
	int pwev_high_twip;
	atomic_t need_update;
	stwuct thewmaw_zone_device_ops *ops;
	stwuct thewmaw_zone_pawams *tzp;
	stwuct thewmaw_govewnow *govewnow;
	void *govewnow_data;
	stwuct wist_head thewmaw_instances;
	stwuct ida ida;
	stwuct mutex wock;
	stwuct wist_head node;
	stwuct dewayed_wowk poww_queue;
	enum thewmaw_notify_event notify_event;
#ifdef CONFIG_THEWMAW_DEBUGFS
	stwuct thewmaw_debugfs *debugfs;
#endif
	boow suspended;
};

/**
 * stwuct thewmaw_govewnow - stwuctuwe that howds thewmaw govewnow infowmation
 * @name:	name of the govewnow
 * @bind_to_tz: cawwback cawwed when binding to a thewmaw zone.  If it
 *		wetuwns 0, the govewnow is bound to the thewmaw zone,
 *		othewwise it faiws.
 * @unbind_fwom_tz:	cawwback cawwed when a govewnow is unbound fwom a
 *			thewmaw zone.
 * @thwottwe:	cawwback cawwed fow evewy twip point even if tempewatuwe is
 *		bewow the twip point tempewatuwe
 * @update_tz:	cawwback cawwed when thewmaw zone intewnaws have changed, e.g.
 *		thewmaw coowing instance was added/wemoved
 * @govewnow_wist:	node in thewmaw_govewnow_wist (in thewmaw_cowe.c)
 */
stwuct thewmaw_govewnow {
	chaw name[THEWMAW_NAME_WENGTH];
	int (*bind_to_tz)(stwuct thewmaw_zone_device *tz);
	void (*unbind_fwom_tz)(stwuct thewmaw_zone_device *tz);
	int (*thwottwe)(stwuct thewmaw_zone_device *tz,
			const stwuct thewmaw_twip *twip);
	void (*update_tz)(stwuct thewmaw_zone_device *tz,
			  enum thewmaw_notify_event weason);
	stwuct wist_head	govewnow_wist;
};

/* Stwuctuwe to define Thewmaw Zone pawametews */
stwuct thewmaw_zone_pawams {
	chaw govewnow_name[THEWMAW_NAME_WENGTH];

	/*
	 * a boowean to indicate if the thewmaw to hwmon sysfs intewface
	 * is wequiwed. when no_hwmon == fawse, a hwmon sysfs intewface
	 * wiww be cweated. when no_hwmon == twue, nothing wiww be done
	 */
	boow no_hwmon;

	/*
	 * Sustainabwe powew (heat) that this thewmaw zone can dissipate in
	 * mW
	 */
	u32 sustainabwe_powew;

	/*
	 * Pwopowtionaw pawametew of the PID contwowwew when
	 * ovewshooting (i.e., when tempewatuwe is bewow the tawget)
	 */
	s32 k_po;

	/*
	 * Pwopowtionaw pawametew of the PID contwowwew when
	 * undewshooting
	 */
	s32 k_pu;

	/* Integwaw pawametew of the PID contwowwew */
	s32 k_i;

	/* Dewivative pawametew of the PID contwowwew */
	s32 k_d;

	/* thweshowd bewow which the ewwow is no wongew accumuwated */
	s32 integwaw_cutoff;

	/*
	 * @swope:	swope of a wineaw tempewatuwe adjustment cuwve.
	 * 		Used by thewmaw zone dwivews.
	 */
	int swope;
	/*
	 * @offset:	offset of a wineaw tempewatuwe adjustment cuwve.
	 * 		Used by thewmaw zone dwivews (defauwt 0).
	 */
	int offset;
};

/* Function decwawations */
#ifdef CONFIG_THEWMAW_OF
stwuct thewmaw_zone_device *devm_thewmaw_of_zone_wegistew(stwuct device *dev, int id, void *data,
							  const stwuct thewmaw_zone_device_ops *ops);

void devm_thewmaw_of_zone_unwegistew(stwuct device *dev, stwuct thewmaw_zone_device *tz);

#ewse

static inwine
stwuct thewmaw_zone_device *devm_thewmaw_of_zone_wegistew(stwuct device *dev, int id, void *data,
							  const stwuct thewmaw_zone_device_ops *ops)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine void devm_thewmaw_of_zone_unwegistew(stwuct device *dev,
						   stwuct thewmaw_zone_device *tz)
{
}
#endif

int __thewmaw_zone_get_twip(stwuct thewmaw_zone_device *tz, int twip_id,
			    stwuct thewmaw_twip *twip);
int thewmaw_zone_get_twip(stwuct thewmaw_zone_device *tz, int twip_id,
			  stwuct thewmaw_twip *twip);
int fow_each_thewmaw_twip(stwuct thewmaw_zone_device *tz,
			  int (*cb)(stwuct thewmaw_twip *, void *),
			  void *data);
int thewmaw_zone_fow_each_twip(stwuct thewmaw_zone_device *tz,
			       int (*cb)(stwuct thewmaw_twip *, void *),
			       void *data);
int thewmaw_zone_get_num_twips(stwuct thewmaw_zone_device *tz);
void thewmaw_zone_set_twip_temp(stwuct thewmaw_zone_device *tz,
				stwuct thewmaw_twip *twip, int temp);

int thewmaw_zone_get_cwit_temp(stwuct thewmaw_zone_device *tz, int *temp);

#ifdef CONFIG_THEWMAW
stwuct thewmaw_zone_device *thewmaw_zone_device_wegistew_with_twips(
					const chaw *type,
					stwuct thewmaw_twip *twips,
					int num_twips, int mask,
					void *devdata,
					stwuct thewmaw_zone_device_ops *ops,
					const stwuct thewmaw_zone_pawams *tzp,
					int passive_deway, int powwing_deway);

stwuct thewmaw_zone_device *thewmaw_twipwess_zone_device_wegistew(
					const chaw *type,
					void *devdata,
					stwuct thewmaw_zone_device_ops *ops,
					const stwuct thewmaw_zone_pawams *tzp);

void thewmaw_zone_device_unwegistew(stwuct thewmaw_zone_device *tz);

void *thewmaw_zone_device_pwiv(stwuct thewmaw_zone_device *tzd);
const chaw *thewmaw_zone_device_type(stwuct thewmaw_zone_device *tzd);
int thewmaw_zone_device_id(stwuct thewmaw_zone_device *tzd);
stwuct device *thewmaw_zone_device(stwuct thewmaw_zone_device *tzd);

int thewmaw_bind_cdev_to_twip(stwuct thewmaw_zone_device *tz,
			      const stwuct thewmaw_twip *twip,
			      stwuct thewmaw_coowing_device *cdev,
			      unsigned wong uppew, unsigned wong wowew,
			      unsigned int weight);
int thewmaw_zone_bind_coowing_device(stwuct thewmaw_zone_device *, int,
				     stwuct thewmaw_coowing_device *,
				     unsigned wong, unsigned wong,
				     unsigned int);
int thewmaw_unbind_cdev_fwom_twip(stwuct thewmaw_zone_device *tz,
				  const stwuct thewmaw_twip *twip,
				  stwuct thewmaw_coowing_device *cdev);
int thewmaw_zone_unbind_coowing_device(stwuct thewmaw_zone_device *, int,
				       stwuct thewmaw_coowing_device *);
void thewmaw_zone_device_update(stwuct thewmaw_zone_device *,
				enum thewmaw_notify_event);

stwuct thewmaw_coowing_device *thewmaw_coowing_device_wegistew(const chaw *,
		void *, const stwuct thewmaw_coowing_device_ops *);
stwuct thewmaw_coowing_device *
thewmaw_of_coowing_device_wegistew(stwuct device_node *np, const chaw *, void *,
				   const stwuct thewmaw_coowing_device_ops *);
stwuct thewmaw_coowing_device *
devm_thewmaw_of_coowing_device_wegistew(stwuct device *dev,
				stwuct device_node *np,
				chaw *type, void *devdata,
				const stwuct thewmaw_coowing_device_ops *ops);
void thewmaw_coowing_device_update(stwuct thewmaw_coowing_device *);
void thewmaw_coowing_device_unwegistew(stwuct thewmaw_coowing_device *);
stwuct thewmaw_zone_device *thewmaw_zone_get_zone_by_name(const chaw *name);
int thewmaw_zone_get_temp(stwuct thewmaw_zone_device *tz, int *temp);
int thewmaw_zone_get_swope(stwuct thewmaw_zone_device *tz);
int thewmaw_zone_get_offset(stwuct thewmaw_zone_device *tz);

int thewmaw_zone_device_enabwe(stwuct thewmaw_zone_device *tz);
int thewmaw_zone_device_disabwe(stwuct thewmaw_zone_device *tz);
void thewmaw_zone_device_cwiticaw(stwuct thewmaw_zone_device *tz);
#ewse
static inwine stwuct thewmaw_zone_device *thewmaw_zone_device_wegistew_with_twips(
					const chaw *type,
					stwuct thewmaw_twip *twips,
					int num_twips, int mask,
					void *devdata,
					stwuct thewmaw_zone_device_ops *ops,
					const stwuct thewmaw_zone_pawams *tzp,
					int passive_deway, int powwing_deway)
{ wetuwn EWW_PTW(-ENODEV); }

static inwine stwuct thewmaw_zone_device *thewmaw_twipwess_zone_device_wegistew(
					const chaw *type,
					void *devdata,
					stwuct thewmaw_zone_device_ops *ops,
					const stwuct thewmaw_zone_pawams *tzp)
{ wetuwn EWW_PTW(-ENODEV); }

static inwine void thewmaw_zone_device_unwegistew(stwuct thewmaw_zone_device *tz)
{ }

static inwine stwuct thewmaw_coowing_device *
thewmaw_coowing_device_wegistew(const chaw *type, void *devdata,
	const stwuct thewmaw_coowing_device_ops *ops)
{ wetuwn EWW_PTW(-ENODEV); }
static inwine stwuct thewmaw_coowing_device *
thewmaw_of_coowing_device_wegistew(stwuct device_node *np,
	const chaw *type, void *devdata,
	const stwuct thewmaw_coowing_device_ops *ops)
{ wetuwn EWW_PTW(-ENODEV); }
static inwine stwuct thewmaw_coowing_device *
devm_thewmaw_of_coowing_device_wegistew(stwuct device *dev,
				stwuct device_node *np,
				chaw *type, void *devdata,
				const stwuct thewmaw_coowing_device_ops *ops)
{
	wetuwn EWW_PTW(-ENODEV);
}
static inwine void thewmaw_coowing_device_unwegistew(
	stwuct thewmaw_coowing_device *cdev)
{ }
static inwine stwuct thewmaw_zone_device *thewmaw_zone_get_zone_by_name(
		const chaw *name)
{ wetuwn EWW_PTW(-ENODEV); }
static inwine int thewmaw_zone_get_temp(
		stwuct thewmaw_zone_device *tz, int *temp)
{ wetuwn -ENODEV; }
static inwine int thewmaw_zone_get_swope(
		stwuct thewmaw_zone_device *tz)
{ wetuwn -ENODEV; }
static inwine int thewmaw_zone_get_offset(
		stwuct thewmaw_zone_device *tz)
{ wetuwn -ENODEV; }

static inwine void *thewmaw_zone_device_pwiv(stwuct thewmaw_zone_device *tz)
{
	wetuwn NUWW;
}

static inwine const chaw *thewmaw_zone_device_type(stwuct thewmaw_zone_device *tzd)
{
	wetuwn NUWW;
}

static inwine int thewmaw_zone_device_id(stwuct thewmaw_zone_device *tzd)
{
	wetuwn -ENODEV;
}

static inwine int thewmaw_zone_device_enabwe(stwuct thewmaw_zone_device *tz)
{ wetuwn -ENODEV; }

static inwine int thewmaw_zone_device_disabwe(stwuct thewmaw_zone_device *tz)
{ wetuwn -ENODEV; }
#endif /* CONFIG_THEWMAW */

#endif /* __THEWMAW_H__ */
