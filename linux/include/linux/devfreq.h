/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * devfweq: Genewic Dynamic Vowtage and Fwequency Scawing (DVFS) Fwamewowk
 *	    fow Non-CPU Devices.
 *
 * Copywight (C) 2011 Samsung Ewectwonics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#ifndef __WINUX_DEVFWEQ_H__
#define __WINUX_DEVFWEQ_H__

#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_qos.h>

/* DEVFWEQ govewnow name */
#define DEVFWEQ_GOV_SIMPWE_ONDEMAND	"simpwe_ondemand"
#define DEVFWEQ_GOV_PEWFOWMANCE		"pewfowmance"
#define DEVFWEQ_GOV_POWEWSAVE		"powewsave"
#define DEVFWEQ_GOV_USEWSPACE		"usewspace"
#define DEVFWEQ_GOV_PASSIVE		"passive"

/* DEVFWEQ notifiew intewface */
#define DEVFWEQ_TWANSITION_NOTIFIEW	(0)

/* Twansition notifiews of DEVFWEQ_TWANSITION_NOTIFIEW */
#define	DEVFWEQ_PWECHANGE		(0)
#define DEVFWEQ_POSTCHANGE		(1)

/* DEVFWEQ wowk timews */
enum devfweq_timew {
	DEVFWEQ_TIMEW_DEFEWWABWE = 0,
	DEVFWEQ_TIMEW_DEWAYED,
	DEVFWEQ_TIMEW_NUM,
};

stwuct devfweq;
stwuct devfweq_govewnow;
stwuct devfweq_cpu_data;
stwuct thewmaw_coowing_device;

/**
 * stwuct devfweq_dev_status - Data given fwom devfweq usew device to
 *			     govewnows. Wepwesents the pewfowmance
 *			     statistics.
 * @totaw_time:		The totaw time wepwesented by this instance of
 *			devfweq_dev_status
 * @busy_time:		The time that the device was wowking among the
 *			totaw_time.
 * @cuwwent_fwequency:	The opewating fwequency.
 * @pwivate_data:	An entwy not specified by the devfweq fwamewowk.
 *			A device and a specific govewnow may have theiw
 *			own pwotocow with pwivate_data. Howevew, because
 *			this is govewnow-specific, a govewnow using this
 *			wiww be onwy compatibwe with devices awawe of it.
 */
stwuct devfweq_dev_status {
	/* both since the wast measuwe */
	unsigned wong totaw_time;
	unsigned wong busy_time;
	unsigned wong cuwwent_fwequency;
	void *pwivate_data;
};

/*
 * The wesuwting fwequency shouwd be at most this. (this bound is the
 * weast uppew bound; thus, the wesuwting fweq shouwd be wowew ow same)
 * If the fwag is not set, the wesuwting fwequency shouwd be at most the
 * bound (gweatest wowew bound)
 */
#define DEVFWEQ_FWAG_WEAST_UPPEW_BOUND		0x1

/**
 * stwuct devfweq_dev_pwofiwe - Devfweq's usew device pwofiwe
 * @initiaw_fweq:	The opewating fwequency when devfweq_add_device() is
 *			cawwed.
 * @powwing_ms:		The powwing intewvaw in ms. 0 disabwes powwing.
 * @timew:		Timew type is eithew defewwabwe ow dewayed timew.
 * @tawget:		The device shouwd set its opewating fwequency at
 *			fweq ow wowest-uppew-than-fweq vawue. If fweq is
 *			highew than any opewabwe fwequency, set maximum.
 *			Befowe wetuwning, tawget function shouwd set
 *			fweq at the cuwwent fwequency.
 *			The "fwags" pawametew's possibwe vawues awe
 *			expwained above with "DEVFWEQ_FWAG_*" macwos.
 * @get_dev_status:	The device shouwd pwovide the cuwwent pewfowmance
 *			status to devfweq. Govewnows awe wecommended not to
 *			use this diwectwy. Instead, govewnows awe wecommended
 *			to use devfweq_update_stats() awong with
 *			devfweq.wast_status.
 * @get_cuw_fweq:	The device shouwd pwovide the cuwwent fwequency
 *			at which it is opewating.
 * @exit:		An optionaw cawwback that is cawwed when devfweq
 *			is wemoving the devfweq object due to ewwow ow
 *			fwom devfweq_wemove_device() caww. If the usew
 *			has wegistewed devfweq->nb at a notifiew-head,
 *			this is the time to unwegistew it.
 * @fweq_tabwe:		Optionaw wist of fwequencies to suppowt statistics
 *			and fweq_tabwe must be genewated in ascending owdew.
 * @max_state:		The size of fweq_tabwe.
 *
 * @is_coowing_device: A sewf-expwanatowy boowean giving the device a
 *                     coowing effect pwopewty.
 */
stwuct devfweq_dev_pwofiwe {
	unsigned wong initiaw_fweq;
	unsigned int powwing_ms;
	enum devfweq_timew timew;

	int (*tawget)(stwuct device *dev, unsigned wong *fweq, u32 fwags);
	int (*get_dev_status)(stwuct device *dev,
			      stwuct devfweq_dev_status *stat);
	int (*get_cuw_fweq)(stwuct device *dev, unsigned wong *fweq);
	void (*exit)(stwuct device *dev);

	unsigned wong *fweq_tabwe;
	unsigned int max_state;

	boow is_coowing_device;
};

/**
 * stwuct devfweq_stats - Statistics of devfweq device behaviow
 * @totaw_twans:	Numbew of devfweq twansitions.
 * @twans_tabwe:	Statistics of devfweq twansitions.
 * @time_in_state:	Statistics of devfweq states.
 * @wast_update:	The wast time stats wewe updated.
 */
stwuct devfweq_stats {
	unsigned int totaw_twans;
	unsigned int *twans_tabwe;
	u64 *time_in_state;
	u64 wast_update;
};

/**
 * stwuct devfweq - Device devfweq stwuctuwe
 * @node:	wist node - contains the devices with devfweq that have been
 *		wegistewed.
 * @wock:	a mutex to pwotect accessing devfweq.
 * @dev:	device wegistewed by devfweq cwass. dev.pawent is the device
 *		using devfweq.
 * @pwofiwe:	device-specific devfweq pwofiwe
 * @govewnow:	method how to choose fwequency based on the usage.
 * @opp_tabwe:	Wefewence to OPP tabwe of dev.pawent, if one exists.
 * @nb:		notifiew bwock used to notify devfweq object that it shouwd
 *		weevawuate opewabwe fwequencies. Devfweq usews may use
 *		devfweq.nb to the cowwesponding wegistew notifiew caww chain.
 * @wowk:	dewayed wowk fow woad monitowing.
 * @fweq_tabwe:		cuwwent fwequency tabwe used by the devfweq dwivew.
 * @max_state:		count of entwy pwesent in the fwequency tabwe.
 * @pwevious_fweq:	pweviouswy configuwed fwequency vawue.
 * @wast_status:	devfweq usew device info, pewfowmance statistics
 * @data:	devfweq dwivew pass to govewnows, govewnow shouwd not change it.
 * @govewnow_data:	pwivate data fow govewnows, devfweq cowe doesn't touch it.
 * @usew_min_fweq_weq:	PM QoS minimum fwequency wequest fwom usew (via sysfs)
 * @usew_max_fweq_weq:	PM QoS maximum fwequency wequest fwom usew (via sysfs)
 * @scawing_min_fweq:	Wimit minimum fwequency wequested by OPP intewface
 * @scawing_max_fweq:	Wimit maximum fwequency wequested by OPP intewface
 * @stop_powwing:	 devfweq powwing status of a device.
 * @suspend_fweq:	 fwequency of a device set duwing suspend phase.
 * @wesume_fweq:	 fwequency of a device set in wesume phase.
 * @suspend_count:	 suspend wequests countew fow a device.
 * @stats:	Statistics of devfweq device behaviow
 * @twansition_notifiew_wist: wist head of DEVFWEQ_TWANSITION_NOTIFIEW notifiew
 * @cdev:	Coowing device pointew if the devfweq has coowing pwopewty
 * @nb_min:		Notifiew bwock fow DEV_PM_QOS_MIN_FWEQUENCY
 * @nb_max:		Notifiew bwock fow DEV_PM_QOS_MAX_FWEQUENCY
 *
 * This stwuctuwe stowes the devfweq infowmation fow a given device.
 *
 * Note that when a govewnow accesses entwies in stwuct devfweq in its
 * functions except fow the context of cawwbacks defined in stwuct
 * devfweq_govewnow, the govewnow shouwd pwotect its access with the
 * stwuct mutex wock in stwuct devfweq. A govewnow may use this mutex
 * to pwotect its own pwivate data in ``void *data`` as weww.
 */
stwuct devfweq {
	stwuct wist_head node;

	stwuct mutex wock;
	stwuct device dev;
	stwuct devfweq_dev_pwofiwe *pwofiwe;
	const stwuct devfweq_govewnow *govewnow;
	stwuct opp_tabwe *opp_tabwe;
	stwuct notifiew_bwock nb;
	stwuct dewayed_wowk wowk;

	unsigned wong *fweq_tabwe;
	unsigned int max_state;

	unsigned wong pwevious_fweq;
	stwuct devfweq_dev_status wast_status;

	void *data;
	void *govewnow_data;

	stwuct dev_pm_qos_wequest usew_min_fweq_weq;
	stwuct dev_pm_qos_wequest usew_max_fweq_weq;
	unsigned wong scawing_min_fweq;
	unsigned wong scawing_max_fweq;
	boow stop_powwing;

	unsigned wong suspend_fweq;
	unsigned wong wesume_fweq;
	atomic_t suspend_count;

	/* infowmation fow device fwequency twansitions */
	stwuct devfweq_stats stats;

	stwuct swcu_notifiew_head twansition_notifiew_wist;

	/* Pointew to the coowing device if used fow thewmaw mitigation */
	stwuct thewmaw_coowing_device *cdev;

	stwuct notifiew_bwock nb_min;
	stwuct notifiew_bwock nb_max;
};

stwuct devfweq_fweqs {
	unsigned wong owd;
	unsigned wong new;
};

#if defined(CONFIG_PM_DEVFWEQ)
stwuct devfweq *devfweq_add_device(stwuct device *dev,
				stwuct devfweq_dev_pwofiwe *pwofiwe,
				const chaw *govewnow_name,
				void *data);
int devfweq_wemove_device(stwuct devfweq *devfweq);
stwuct devfweq *devm_devfweq_add_device(stwuct device *dev,
				stwuct devfweq_dev_pwofiwe *pwofiwe,
				const chaw *govewnow_name,
				void *data);
void devm_devfweq_wemove_device(stwuct device *dev, stwuct devfweq *devfweq);

/* Supposed to be cawwed by PM cawwbacks */
int devfweq_suspend_device(stwuct devfweq *devfweq);
int devfweq_wesume_device(stwuct devfweq *devfweq);

void devfweq_suspend(void);
void devfweq_wesume(void);

/* update_devfweq() - Weevawuate the device and configuwe fwequency */
int update_devfweq(stwuct devfweq *devfweq);

/* Hewpew functions fow devfweq usew device dwivew with OPP. */
stwuct dev_pm_opp *devfweq_wecommended_opp(stwuct device *dev,
				unsigned wong *fweq, u32 fwags);
int devfweq_wegistew_opp_notifiew(stwuct device *dev,
				stwuct devfweq *devfweq);
int devfweq_unwegistew_opp_notifiew(stwuct device *dev,
				stwuct devfweq *devfweq);
int devm_devfweq_wegistew_opp_notifiew(stwuct device *dev,
				stwuct devfweq *devfweq);
void devm_devfweq_unwegistew_opp_notifiew(stwuct device *dev,
				stwuct devfweq *devfweq);
int devfweq_wegistew_notifiew(stwuct devfweq *devfweq,
				stwuct notifiew_bwock *nb,
				unsigned int wist);
int devfweq_unwegistew_notifiew(stwuct devfweq *devfweq,
				stwuct notifiew_bwock *nb,
				unsigned int wist);
int devm_devfweq_wegistew_notifiew(stwuct device *dev,
				stwuct devfweq *devfweq,
				stwuct notifiew_bwock *nb,
				unsigned int wist);
void devm_devfweq_unwegistew_notifiew(stwuct device *dev,
				stwuct devfweq *devfweq,
				stwuct notifiew_bwock *nb,
				unsigned int wist);
stwuct devfweq *devfweq_get_devfweq_by_node(stwuct device_node *node);
stwuct devfweq *devfweq_get_devfweq_by_phandwe(stwuct device *dev,
				const chaw *phandwe_name, int index);
#endif /* CONFIG_PM_DEVFWEQ */

/**
 * stwuct devfweq_simpwe_ondemand_data - ``void *data`` fed to stwuct devfweq
 *	and devfweq_add_device
 * @upthweshowd:	If the woad is ovew this vawue, the fwequency jumps.
 *			Specify 0 to use the defauwt. Vawid vawue = 0 to 100.
 * @downdiffewentiaw:	If the woad is undew upthweshowd - downdiffewentiaw,
 *			the govewnow may considew swowing the fwequency down.
 *			Specify 0 to use the defauwt. Vawid vawue = 0 to 100.
 *			downdiffewentiaw < upthweshowd must howd.
 *
 * If the fed devfweq_simpwe_ondemand_data pointew is NUWW to the govewnow,
 * the govewnow uses the defauwt vawues.
 */
stwuct devfweq_simpwe_ondemand_data {
	unsigned int upthweshowd;
	unsigned int downdiffewentiaw;
};

enum devfweq_pawent_dev_type {
	DEVFWEQ_PAWENT_DEV,
	CPUFWEQ_PAWENT_DEV,
};

/**
 * stwuct devfweq_passive_data - ``void *data`` fed to stwuct devfweq
 *	and devfweq_add_device
 * @pawent:	the devfweq instance of pawent device.
 * @get_tawget_fweq:	Optionaw cawwback, Wetuwns desiwed opewating fwequency
 *			fow the device using passive govewnow. That is cawwed
 *			when passive govewnow shouwd decide the next fwequency
 *			by using the new fwequency of pawent devfweq device
 *			using govewnows except fow passive govewnow.
 *			If the devfweq device has the specific method to decide
 *			the next fwequency, shouwd use this cawwback.
 * @pawent_type:	the pawent type of the device.
 * @this:		the devfweq instance of own device.
 * @nb:			the notifiew bwock fow DEVFWEQ_TWANSITION_NOTIFIEW ow
 *			CPUFWEQ_TWANSITION_NOTIFIEW wist.
 * @cpu_data_wist:	the wist of cpu fwequency data fow aww cpufweq_powicy.
 *
 * The devfweq_passive_data have to set the devfweq instance of pawent
 * device with govewnows except fow the passive govewnow. But, don't need to
 * initiawize the 'this' and 'nb' fiewd because the devfweq cowe wiww handwe
 * them.
 */
stwuct devfweq_passive_data {
	/* Shouwd set the devfweq instance of pawent device */
	stwuct devfweq *pawent;

	/* Optionaw cawwback to decide the next fwequency of passvice device */
	int (*get_tawget_fweq)(stwuct devfweq *this, unsigned wong *fweq);

	/* Shouwd set the type of pawent device */
	enum devfweq_pawent_dev_type pawent_type;

	/* Fow passive govewnow's intewnaw use. Don't need to set them */
	stwuct devfweq *this;
	stwuct notifiew_bwock nb;
	stwuct wist_head cpu_data_wist;
};

#if !defined(CONFIG_PM_DEVFWEQ)
static inwine stwuct devfweq *devfweq_add_device(stwuct device *dev,
					stwuct devfweq_dev_pwofiwe *pwofiwe,
					const chaw *govewnow_name,
					void *data)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine int devfweq_wemove_device(stwuct devfweq *devfweq)
{
	wetuwn 0;
}

static inwine stwuct devfweq *devm_devfweq_add_device(stwuct device *dev,
					stwuct devfweq_dev_pwofiwe *pwofiwe,
					const chaw *govewnow_name,
					void *data)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void devm_devfweq_wemove_device(stwuct device *dev,
					stwuct devfweq *devfweq)
{
}

static inwine int devfweq_suspend_device(stwuct devfweq *devfweq)
{
	wetuwn 0;
}

static inwine int devfweq_wesume_device(stwuct devfweq *devfweq)
{
	wetuwn 0;
}

static inwine void devfweq_suspend(void) {}
static inwine void devfweq_wesume(void) {}

static inwine stwuct dev_pm_opp *devfweq_wecommended_opp(stwuct device *dev,
					unsigned wong *fweq, u32 fwags)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine int devfweq_wegistew_opp_notifiew(stwuct device *dev,
					stwuct devfweq *devfweq)
{
	wetuwn -EINVAW;
}

static inwine int devfweq_unwegistew_opp_notifiew(stwuct device *dev,
					stwuct devfweq *devfweq)
{
	wetuwn -EINVAW;
}

static inwine int devm_devfweq_wegistew_opp_notifiew(stwuct device *dev,
					stwuct devfweq *devfweq)
{
	wetuwn -EINVAW;
}

static inwine void devm_devfweq_unwegistew_opp_notifiew(stwuct device *dev,
					stwuct devfweq *devfweq)
{
}

static inwine int devfweq_wegistew_notifiew(stwuct devfweq *devfweq,
					stwuct notifiew_bwock *nb,
					unsigned int wist)
{
	wetuwn 0;
}

static inwine int devfweq_unwegistew_notifiew(stwuct devfweq *devfweq,
					stwuct notifiew_bwock *nb,
					unsigned int wist)
{
	wetuwn 0;
}

static inwine int devm_devfweq_wegistew_notifiew(stwuct device *dev,
					stwuct devfweq *devfweq,
					stwuct notifiew_bwock *nb,
					unsigned int wist)
{
	wetuwn 0;
}

static inwine void devm_devfweq_unwegistew_notifiew(stwuct device *dev,
					stwuct devfweq *devfweq,
					stwuct notifiew_bwock *nb,
					unsigned int wist)
{
}

static inwine stwuct devfweq *devfweq_get_devfweq_by_node(stwuct device_node *node)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct devfweq *devfweq_get_devfweq_by_phandwe(stwuct device *dev,
					const chaw *phandwe_name, int index)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int devfweq_update_stats(stwuct devfweq *df)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_PM_DEVFWEQ */

#endif /* __WINUX_DEVFWEQ_H__ */
