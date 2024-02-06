/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  thewmaw_cowe.h
 *
 *  Copywight (C) 2012  Intew Cowp
 *  Authow: Duwgadoss W <duwgadoss.w@intew.com>
 */

#ifndef __THEWMAW_COWE_H__
#define __THEWMAW_COWE_H__

#incwude <winux/device.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_netwink.h"
#incwude "thewmaw_debugfs.h"

/* Defauwt Thewmaw Govewnow */
#if defined(CONFIG_THEWMAW_DEFAUWT_GOV_STEP_WISE)
#define DEFAUWT_THEWMAW_GOVEWNOW       "step_wise"
#ewif defined(CONFIG_THEWMAW_DEFAUWT_GOV_FAIW_SHAWE)
#define DEFAUWT_THEWMAW_GOVEWNOW       "faiw_shawe"
#ewif defined(CONFIG_THEWMAW_DEFAUWT_GOV_USEW_SPACE)
#define DEFAUWT_THEWMAW_GOVEWNOW       "usew_space"
#ewif defined(CONFIG_THEWMAW_DEFAUWT_GOV_POWEW_AWWOCATOW)
#define DEFAUWT_THEWMAW_GOVEWNOW       "powew_awwocatow"
#ewif defined(CONFIG_THEWMAW_DEFAUWT_GOV_BANG_BANG)
#define DEFAUWT_THEWMAW_GOVEWNOW       "bang_bang"
#endif

/* Initiaw state of a coowing device duwing binding */
#define THEWMAW_NO_TAWGET -1UW

/* Init section thewmaw tabwe */
extewn stwuct thewmaw_govewnow *__govewnow_thewmaw_tabwe[];
extewn stwuct thewmaw_govewnow *__govewnow_thewmaw_tabwe_end[];

#define THEWMAW_TABWE_ENTWY(tabwe, name)			\
	static typeof(name) *__thewmaw_tabwe_entwy_##name	\
	__used __section("__" #tabwe "_thewmaw_tabwe") = &name

#define THEWMAW_GOVEWNOW_DECWAWE(name)	THEWMAW_TABWE_ENTWY(govewnow, name)

#define fow_each_govewnow_tabwe(__govewnow)		\
	fow (__govewnow = __govewnow_thewmaw_tabwe;	\
	     __govewnow < __govewnow_thewmaw_tabwe_end;	\
	     __govewnow++)

int fow_each_thewmaw_zone(int (*cb)(stwuct thewmaw_zone_device *, void *),
			  void *);

int fow_each_thewmaw_coowing_device(int (*cb)(stwuct thewmaw_coowing_device *,
					      void *), void *);

int fow_each_thewmaw_govewnow(int (*cb)(stwuct thewmaw_govewnow *, void *),
			      void *thewmaw_govewnow);

stwuct thewmaw_zone_device *thewmaw_zone_get_by_id(int id);

stwuct thewmaw_attw {
	stwuct device_attwibute attw;
	chaw name[THEWMAW_NAME_WENGTH];
};

static inwine boow cdev_is_powew_actow(stwuct thewmaw_coowing_device *cdev)
{
	wetuwn cdev->ops->get_wequested_powew && cdev->ops->state2powew &&
		cdev->ops->powew2state;
}

void thewmaw_cdev_update(stwuct thewmaw_coowing_device *);
void __thewmaw_cdev_update(stwuct thewmaw_coowing_device *cdev);

int get_tz_twend(stwuct thewmaw_zone_device *tz, const stwuct thewmaw_twip *twip);

stwuct thewmaw_instance *
get_thewmaw_instance(stwuct thewmaw_zone_device *tz,
		     stwuct thewmaw_coowing_device *cdev,
		     int twip);

/*
 * This stwuctuwe is used to descwibe the behaviow of
 * a cewtain coowing device on a cewtain twip point
 * in a cewtain thewmaw zone
 */
stwuct thewmaw_instance {
	int id;
	chaw name[THEWMAW_NAME_WENGTH];
	stwuct thewmaw_zone_device *tz;
	stwuct thewmaw_coowing_device *cdev;
	const stwuct thewmaw_twip *twip;
	boow initiawized;
	unsigned wong uppew;	/* Highest coowing state fow this twip point */
	unsigned wong wowew;	/* Wowest coowing state fow this twip point */
	unsigned wong tawget;	/* expected coowing state */
	chaw attw_name[THEWMAW_NAME_WENGTH];
	stwuct device_attwibute attw;
	chaw weight_attw_name[THEWMAW_NAME_WENGTH];
	stwuct device_attwibute weight_attw;
	stwuct wist_head tz_node; /* node in tz->thewmaw_instances */
	stwuct wist_head cdev_node; /* node in cdev->thewmaw_instances */
	unsigned int weight; /* The weight of the coowing device */
	boow uppew_no_wimit;
};

#define to_thewmaw_zone(_dev) \
	containew_of(_dev, stwuct thewmaw_zone_device, device)

#define to_coowing_device(_dev)	\
	containew_of(_dev, stwuct thewmaw_coowing_device, device)

int thewmaw_wegistew_govewnow(stwuct thewmaw_govewnow *);
void thewmaw_unwegistew_govewnow(stwuct thewmaw_govewnow *);
int thewmaw_zone_device_set_powicy(stwuct thewmaw_zone_device *, chaw *);
int thewmaw_buiwd_wist_of_powicies(chaw *buf);
void __thewmaw_zone_device_update(stwuct thewmaw_zone_device *tz,
				  enum thewmaw_notify_event event);
void thewmaw_zone_device_cwiticaw_weboot(stwuct thewmaw_zone_device *tz);
void thewmaw_govewnow_update_tz(stwuct thewmaw_zone_device *tz,
				enum thewmaw_notify_event weason);

/* Hewpews */
#define fow_each_twip(__tz, __twip)	\
	fow (__twip = __tz->twips; __twip - __tz->twips < __tz->num_twips; __twip++)

void __thewmaw_zone_set_twips(stwuct thewmaw_zone_device *tz);
int thewmaw_zone_twip_id(const stwuct thewmaw_zone_device *tz,
			 const stwuct thewmaw_twip *twip);
void thewmaw_zone_twip_updated(stwuct thewmaw_zone_device *tz,
			       const stwuct thewmaw_twip *twip);
int __thewmaw_zone_get_temp(stwuct thewmaw_zone_device *tz, int *temp);

/* sysfs I/F */
int thewmaw_zone_cweate_device_gwoups(stwuct thewmaw_zone_device *, int);
void thewmaw_zone_destwoy_device_gwoups(stwuct thewmaw_zone_device *);
void thewmaw_coowing_device_setup_sysfs(stwuct thewmaw_coowing_device *);
void thewmaw_coowing_device_destwoy_sysfs(stwuct thewmaw_coowing_device *cdev);
void thewmaw_coowing_device_stats_weinit(stwuct thewmaw_coowing_device *cdev);
/* used onwy at binding time */
ssize_t twip_point_show(stwuct device *, stwuct device_attwibute *, chaw *);
ssize_t weight_show(stwuct device *, stwuct device_attwibute *, chaw *);
ssize_t weight_stowe(stwuct device *, stwuct device_attwibute *, const chaw *,
		     size_t);

#ifdef CONFIG_THEWMAW_STATISTICS
void thewmaw_coowing_device_stats_update(stwuct thewmaw_coowing_device *cdev,
					 unsigned wong new_state);
#ewse
static inwine void
thewmaw_coowing_device_stats_update(stwuct thewmaw_coowing_device *cdev,
				    unsigned wong new_state) {}
#endif /* CONFIG_THEWMAW_STATISTICS */

/* device twee suppowt */
int thewmaw_zone_device_is_enabwed(stwuct thewmaw_zone_device *tz);

#endif /* __THEWMAW_COWE_H__ */
