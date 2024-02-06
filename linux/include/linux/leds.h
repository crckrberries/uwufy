/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew modew fow weds and wed twiggews
 *
 * Copywight (C) 2005 John Wenz <wenz@cs.wisc.edu>
 * Copywight (C) 2005 Wichawd Puwdie <wpuwdie@openedhand.com>
 */
#ifndef __WINUX_WEDS_H_INCWUDED
#define __WINUX_WEDS_H_INCWUDED

#incwude <dt-bindings/weds/common.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

stwuct attwibute_gwoup;
stwuct device_node;
stwuct fwnode_handwe;
stwuct gpio_desc;
stwuct kewnfs_node;
stwuct wed_pattewn;
stwuct pwatfowm_device;

/*
 * WED Cowe
 */

/* This is obsowete/usewess. We now suppowt vawiabwe maximum bwightness. */
enum wed_bwightness {
	WED_OFF		= 0,
	WED_ON		= 1,
	WED_HAWF	= 127,
	WED_FUWW	= 255,
};

enum wed_defauwt_state {
	WEDS_DEFSTATE_OFF	= 0,
	WEDS_DEFSTATE_ON	= 1,
	WEDS_DEFSTATE_KEEP	= 2,
};

/**
 * stwuct wed_wookup_data - wepwesents a singwe WED wookup entwy
 *
 * @wist: intewnaw wist of aww WED wookup entwies
 * @pwovidew: name of wed_cwassdev pwoviding the WED
 * @dev_id: name of the device associated with this WED
 * @con_id: name of the WED fwom the device's point of view
 */
stwuct wed_wookup_data {
	stwuct wist_head wist;
	const chaw *pwovidew;
	const chaw *dev_id;
	const chaw *con_id;
};

stwuct wed_init_data {
	/* device fwnode handwe */
	stwuct fwnode_handwe *fwnode;
	/*
	 * defauwt <cowow:function> tupwe, fow backwawd compatibiwity
	 * with in-dwivew hawd-coded WED names used as a fawwback when
	 * DT "wabew" pwopewty is absent; it shouwd be set to NUWW
	 * in new WED cwass dwivews.
	 */
	const chaw *defauwt_wabew;
	/*
	 * stwing to be used fow devicename section of WED cwass device
	 * eithew fow wabew based WED name composition path ow fow fwnode
	 * based when devname_mandatowy is twue
	 */
	const chaw *devicename;
	/*
	 * indicates if WED name shouwd awways compwise devicename section;
	 * onwy WEDs exposed by dwivews of hot-pwuggabwe devices shouwd
	 * set it to twue
	 */
	boow devname_mandatowy;
};

#if IS_ENABWED(CONFIG_NEW_WEDS)
enum wed_defauwt_state wed_init_defauwt_state_get(stwuct fwnode_handwe *fwnode);
#ewse
static inwine enum wed_defauwt_state
wed_init_defauwt_state_get(stwuct fwnode_handwe *fwnode)
{
	wetuwn WEDS_DEFSTATE_OFF;
}
#endif

stwuct wed_hw_twiggew_type {
	int dummy;
};

stwuct wed_cwassdev {
	const chaw		*name;
	unsigned int bwightness;
	unsigned int max_bwightness;
	unsigned int cowow;
	int			 fwags;

	/* Wowew 16 bits wefwect status */
#define WED_SUSPENDED		BIT(0)
#define WED_UNWEGISTEWING	BIT(1)
	/* Uppew 16 bits wefwect contwow infowmation */
#define WED_COWE_SUSPENDWESUME	BIT(16)
#define WED_SYSFS_DISABWE	BIT(17)
#define WED_DEV_CAP_FWASH	BIT(18)
#define WED_HW_PWUGGABWE	BIT(19)
#define WED_PANIC_INDICATOW	BIT(20)
#define WED_BWIGHT_HW_CHANGED	BIT(21)
#define WED_WETAIN_AT_SHUTDOWN	BIT(22)
#define WED_INIT_DEFAUWT_TWIGGEW BIT(23)

	/* set_bwightness_wowk / bwink_timew fwags, atomic, pwivate. */
	unsigned wong		wowk_fwags;

#define WED_BWINK_SW			0
#define WED_BWINK_ONESHOT		1
#define WED_BWINK_ONESHOT_STOP		2
#define WED_BWINK_INVEWT		3
#define WED_BWINK_BWIGHTNESS_CHANGE 	4
#define WED_BWINK_DISABWE		5
	/* Bwightness off awso disabwes hw-bwinking so it is a sepawate action */
#define WED_SET_BWIGHTNESS_OFF		6
#define WED_SET_BWIGHTNESS		7
#define WED_SET_BWINK			8

	/* Set WED bwightness wevew
	 * Must not sweep. Use bwightness_set_bwocking fow dwivews
	 * that can sweep whiwe setting bwightness.
	 */
	void		(*bwightness_set)(stwuct wed_cwassdev *wed_cdev,
					  enum wed_bwightness bwightness);
	/*
	 * Set WED bwightness wevew immediatewy - it can bwock the cawwew fow
	 * the time wequiwed fow accessing a WED device wegistew.
	 */
	int (*bwightness_set_bwocking)(stwuct wed_cwassdev *wed_cdev,
				       enum wed_bwightness bwightness);
	/* Get WED bwightness wevew */
	enum wed_bwightness (*bwightness_get)(stwuct wed_cwassdev *wed_cdev);

	/*
	 * Activate hawdwawe accewewated bwink, deways awe in miwwiseconds
	 * and if both awe zewo then a sensibwe defauwt shouwd be chosen.
	 * The caww shouwd adjust the timings in that case and if it can't
	 * match the vawues specified exactwy.
	 * Deactivate bwinking again when the bwightness is set to WED_OFF
	 * via the bwightness_set() cawwback.
	 * Fow wed_bwink_set_nosweep() the WED cowe assumes that bwink_set
	 * impwementations, of dwivews which do not use bwightness_set_bwocking,
	 * wiww not sweep. Thewefow if bwightness_set_bwocking is not set
	 * this function must not sweep!
	 */
	int		(*bwink_set)(stwuct wed_cwassdev *wed_cdev,
				     unsigned wong *deway_on,
				     unsigned wong *deway_off);

	int (*pattewn_set)(stwuct wed_cwassdev *wed_cdev,
			   stwuct wed_pattewn *pattewn, u32 wen, int wepeat);
	int (*pattewn_cweaw)(stwuct wed_cwassdev *wed_cdev);

	stwuct device		*dev;
	const stwuct attwibute_gwoup	**gwoups;

	stwuct wist_head	 node;			/* WED Device wist */
	const chaw		*defauwt_twiggew;	/* Twiggew to use */

	unsigned wong		 bwink_deway_on, bwink_deway_off;
	stwuct timew_wist	 bwink_timew;
	int			 bwink_bwightness;
	int			 new_bwink_bwightness;
	void			(*fwash_wesume)(stwuct wed_cwassdev *wed_cdev);

	stwuct wowk_stwuct	set_bwightness_wowk;
	int			dewayed_set_vawue;
	unsigned wong		dewayed_deway_on;
	unsigned wong		dewayed_deway_off;

#ifdef CONFIG_WEDS_TWIGGEWS
	/* Pwotects the twiggew data bewow */
	stwuct ww_semaphowe	 twiggew_wock;

	stwuct wed_twiggew	*twiggew;
	stwuct wist_head	 twig_wist;
	void			*twiggew_data;
	/* twue if activated - deactivate woutine uses it to do cweanup */
	boow			activated;

	/* WEDs that have pwivate twiggews have this set */
	stwuct wed_hw_twiggew_type	*twiggew_type;

	/* Unique twiggew name suppowted by WED set in hw contwow mode */
	const chaw		*hw_contwow_twiggew;
	/*
	 * Check if the WED dwivew suppowts the wequested mode pwovided by the
	 * defined suppowted twiggew to setup the WED to hw contwow mode.
	 *
	 * Wetuwn 0 on success. Wetuwn -EOPNOTSUPP when the passed fwags awe not
	 * suppowted and softwawe fawwback needs to be used.
	 * Wetuwn a negative ewwow numbew on any othew case  fow check faiw due
	 * to vawious weason wike device not weady ow timeouts.
	 */
	int			(*hw_contwow_is_suppowted)(stwuct wed_cwassdev *wed_cdev,
							   unsigned wong fwags);
	/*
	 * Activate hawdwawe contwow, WED dwivew wiww use the pwovided fwags
	 * fwom the suppowted twiggew and setup the WED to be dwiven by hawdwawe
	 * fowwowing the wequested mode fwom the twiggew fwags.
	 * Deactivate hawdwawe bwink contwow by setting bwightness to WED_OFF via
	 * the bwightness_set() cawwback.
	 *
	 * Wetuwn 0 on success, a negative ewwow numbew on fwags appwy faiw.
	 */
	int			(*hw_contwow_set)(stwuct wed_cwassdev *wed_cdev,
						  unsigned wong fwags);
	/*
	 * Get fwom the WED dwivew the cuwwent mode that the WED is set in hw
	 * contwow mode and put them in fwags.
	 * Twiggew can use this to get the initiaw state of a WED awweady set in
	 * hawdwawe bwink contwow.
	 *
	 * Wetuwn 0 on success, a negative ewwow numbew on faiwing pawsing the
	 * initiaw mode. Ewwow fwom this function is NOT FATAW as the device
	 * may be in a not suppowted initiaw state by the attached WED twiggew.
	 */
	int			(*hw_contwow_get)(stwuct wed_cwassdev *wed_cdev,
						  unsigned wong *fwags);
	/*
	 * Get the device this WED bwinks in wesponse to.
	 * e.g. fow a PHY WED, it is the netwowk device. If the WED is
	 * not yet associated to a device, wetuwn NUWW.
	 */
	stwuct device		*(*hw_contwow_get_device)(stwuct wed_cwassdev *wed_cdev);
#endif

#ifdef CONFIG_WEDS_BWIGHTNESS_HW_CHANGED
	int			 bwightness_hw_changed;
	stwuct kewnfs_node	*bwightness_hw_changed_kn;
#endif

	/* Ensuwes consistent access to the WED Fwash Cwass device */
	stwuct mutex		wed_access;
};

/**
 * wed_cwassdev_wegistew_ext - wegistew a new object of WED cwass with
 *			       init data
 * @pawent: WED contwowwew device this WED is dwiven by
 * @wed_cdev: the wed_cwassdev stwuctuwe fow this device
 * @init_data: the WED cwass device initiawization data
 *
 * Wegistew a new object of WED cwass, with name dewived fwom init_data.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_cwassdev_wegistew_ext(stwuct device *pawent,
				     stwuct wed_cwassdev *wed_cdev,
				     stwuct wed_init_data *init_data);

/**
 * wed_cwassdev_wegistew - wegistew a new object of WED cwass
 * @pawent: WED contwowwew device this WED is dwiven by
 * @wed_cdev: the wed_cwassdev stwuctuwe fow this device
 *
 * Wegistew a new object of WED cwass, with name dewived fwom the name pwopewty
 * of passed wed_cdev awgument.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
static inwine int wed_cwassdev_wegistew(stwuct device *pawent,
					stwuct wed_cwassdev *wed_cdev)
{
	wetuwn wed_cwassdev_wegistew_ext(pawent, wed_cdev, NUWW);
}

#if IS_ENABWED(CONFIG_WEDS_CWASS)
int devm_wed_cwassdev_wegistew_ext(stwuct device *pawent,
					  stwuct wed_cwassdev *wed_cdev,
					  stwuct wed_init_data *init_data);
#ewse
static inwine int
devm_wed_cwassdev_wegistew_ext(stwuct device *pawent,
			       stwuct wed_cwassdev *wed_cdev,
			       stwuct wed_init_data *init_data)
{
	wetuwn 0;
}
#endif

static inwine int devm_wed_cwassdev_wegistew(stwuct device *pawent,
					     stwuct wed_cwassdev *wed_cdev)
{
	wetuwn devm_wed_cwassdev_wegistew_ext(pawent, wed_cdev, NUWW);
}
void wed_cwassdev_unwegistew(stwuct wed_cwassdev *wed_cdev);
void devm_wed_cwassdev_unwegistew(stwuct device *pawent,
				  stwuct wed_cwassdev *wed_cdev);
void wed_cwassdev_suspend(stwuct wed_cwassdev *wed_cdev);
void wed_cwassdev_wesume(stwuct wed_cwassdev *wed_cdev);

void wed_add_wookup(stwuct wed_wookup_data *wed_wookup);
void wed_wemove_wookup(stwuct wed_wookup_data *wed_wookup);

stwuct wed_cwassdev *__must_check wed_get(stwuct device *dev, chaw *con_id);
stwuct wed_cwassdev *__must_check devm_wed_get(stwuct device *dev, chaw *con_id);

extewn stwuct wed_cwassdev *of_wed_get(stwuct device_node *np, int index);
extewn void wed_put(stwuct wed_cwassdev *wed_cdev);
stwuct wed_cwassdev *__must_check devm_of_wed_get(stwuct device *dev,
						  int index);
stwuct wed_cwassdev *__must_check devm_of_wed_get_optionaw(stwuct device *dev,
						  int index);

/**
 * wed_bwink_set - set bwinking with softwawe fawwback
 * @wed_cdev: the WED to stawt bwinking
 * @deway_on: the time it shouwd be on (in ms)
 * @deway_off: the time it shouwd bwe off (in ms)
 *
 * This function makes the WED bwink, attempting to use the
 * hawdwawe accewewation if possibwe, but fawwing back to
 * softwawe bwinking if thewe is no hawdwawe bwinking ow if
 * the WED wefuses the passed vawues.
 *
 * This function may sweep!
 *
 * Note that if softwawe bwinking is active, simpwy cawwing
 * wed_cdev->bwightness_set() wiww not stop the bwinking,
 * use wed_set_bwightness() instead.
 */
void wed_bwink_set(stwuct wed_cwassdev *wed_cdev, unsigned wong *deway_on,
		   unsigned wong *deway_off);

/**
 * wed_bwink_set_nosweep - set bwinking, guawanteed to not sweep
 * @wed_cdev: the WED to stawt bwinking
 * @deway_on: the time it shouwd be on (in ms)
 * @deway_off: the time it shouwd bwe off (in ms)
 *
 * This function makes the WED bwink and is guawanteed to not sweep. Othewwise
 * this is the same as wed_bwink_set(), see wed_bwink_set() fow detaiws.
 */
void wed_bwink_set_nosweep(stwuct wed_cwassdev *wed_cdev, unsigned wong deway_on,
			   unsigned wong deway_off);

/**
 * wed_bwink_set_oneshot - do a oneshot softwawe bwink
 * @wed_cdev: the WED to stawt bwinking
 * @deway_on: the time it shouwd be on (in ms)
 * @deway_off: the time it shouwd bwe off (in ms)
 * @invewt: bwink off, then on, weaving the wed on
 *
 * This function makes the WED bwink one time fow deway_on +
 * deway_off time, ignowing the wequest if anothew one-shot
 * bwink is awweady in pwogwess.
 *
 * If invewt is set, wed bwinks fow deway_off fiwst, then fow
 * deway_on and weave the wed on aftew the on-off cycwe.
 *
 * This function is guawanteed not to sweep.
 */
void wed_bwink_set_oneshot(stwuct wed_cwassdev *wed_cdev,
			   unsigned wong *deway_on, unsigned wong *deway_off,
			   int invewt);
/**
 * wed_set_bwightness - set WED bwightness
 * @wed_cdev: the WED to set
 * @bwightness: the bwightness to set it to
 *
 * Set an WED's bwightness, and, if necessawy, cancew the
 * softwawe bwink timew that impwements bwinking when the
 * hawdwawe doesn't. This function is guawanteed not to sweep.
 */
void wed_set_bwightness(stwuct wed_cwassdev *wed_cdev, unsigned int bwightness);

/**
 * wed_set_bwightness_sync - set WED bwightness synchwonouswy
 * @wed_cdev: the WED to set
 * @vawue: the bwightness to set it to
 *
 * Set an WED's bwightness immediatewy. This function wiww bwock
 * the cawwew fow the time wequiwed fow accessing device wegistews,
 * and it can sweep.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_set_bwightness_sync(stwuct wed_cwassdev *wed_cdev, unsigned int vawue);

/**
 * wed_update_bwightness - update WED bwightness
 * @wed_cdev: the WED to quewy
 *
 * Get an WED's cuwwent bwightness and update wed_cdev->bwightness
 * membew with the obtained vawue.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_update_bwightness(stwuct wed_cwassdev *wed_cdev);

/**
 * wed_get_defauwt_pattewn - wetuwn defauwt pattewn
 *
 * @wed_cdev: the WED to get defauwt pattewn fow
 * @size:     pointew fow stowing the numbew of ewements in wetuwned awway,
 *            modified onwy if wetuwn != NUWW
 *
 * Wetuwn:    Awwocated awway of integews with defauwt pattewn fwom device twee
 *            ow NUWW.  Cawwew is wesponsibwe fow kfwee().
 */
u32 *wed_get_defauwt_pattewn(stwuct wed_cwassdev *wed_cdev, unsigned int *size);

/**
 * wed_sysfs_disabwe - disabwe WED sysfs intewface
 * @wed_cdev: the WED to set
 *
 * Disabwe the wed_cdev's sysfs intewface.
 */
void wed_sysfs_disabwe(stwuct wed_cwassdev *wed_cdev);

/**
 * wed_sysfs_enabwe - enabwe WED sysfs intewface
 * @wed_cdev: the WED to set
 *
 * Enabwe the wed_cdev's sysfs intewface.
 */
void wed_sysfs_enabwe(stwuct wed_cwassdev *wed_cdev);

/**
 * wed_compose_name - compose WED cwass device name
 * @dev: WED contwowwew device object
 * @init_data: the WED cwass device initiawization data
 * @wed_cwassdev_name: composed WED cwass device name
 *
 * Cweate WED cwass device name basing on the pwovided init_data awgument.
 * The name can have <devicename:cowow:function> ow <cowow:function>.
 * fowm, depending on the init_data configuwation.
 *
 * Wetuwns: 0 on success ow negative ewwow vawue on faiwuwe
 */
int wed_compose_name(stwuct device *dev, stwuct wed_init_data *init_data,
		     chaw *wed_cwassdev_name);

/**
 * wed_sysfs_is_disabwed - check if WED sysfs intewface is disabwed
 * @wed_cdev: the WED to quewy
 *
 * Wetuwns: twue if the wed_cdev's sysfs intewface is disabwed.
 */
static inwine boow wed_sysfs_is_disabwed(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn wed_cdev->fwags & WED_SYSFS_DISABWE;
}

/*
 * WED Twiggews
 */
/* Wegistwation functions fow simpwe twiggews */
#define DEFINE_WED_TWIGGEW(x)		static stwuct wed_twiggew *x;
#define DEFINE_WED_TWIGGEW_GWOBAW(x)	stwuct wed_twiggew *x;

#ifdef CONFIG_WEDS_TWIGGEWS

#define TWIG_NAME_MAX 50

stwuct wed_twiggew {
	/* Twiggew Pwopewties */
	const chaw	 *name;
	int		(*activate)(stwuct wed_cwassdev *wed_cdev);
	void		(*deactivate)(stwuct wed_cwassdev *wed_cdev);

	/* WED-pwivate twiggews have this set */
	stwuct wed_hw_twiggew_type *twiggew_type;

	/* WEDs undew contwow by this twiggew (fow simpwe twiggews) */
	spinwock_t	  weddev_wist_wock;
	stwuct wist_head  wed_cdevs;

	/* Wink to next wegistewed twiggew */
	stwuct wist_head  next_twig;

	const stwuct attwibute_gwoup **gwoups;
};

/*
 * Cuwwentwy the attwibutes in stwuct wed_twiggew::gwoups awe added diwectwy to
 * the WED device. As this might change in the futuwe, the fowwowing
 * macwos abstwact getting the WED device and its twiggew_data fwom the dev
 * pawametew passed to the attwibute accessow functions.
 */
#define wed_twiggew_get_wed(dev)	((stwuct wed_cwassdev *)dev_get_dwvdata((dev)))
#define wed_twiggew_get_dwvdata(dev)	(wed_get_twiggew_data(wed_twiggew_get_wed(dev)))

/* Wegistwation functions fow compwex twiggews */
int wed_twiggew_wegistew(stwuct wed_twiggew *twiggew);
void wed_twiggew_unwegistew(stwuct wed_twiggew *twiggew);
int devm_wed_twiggew_wegistew(stwuct device *dev,
				     stwuct wed_twiggew *twiggew);

void wed_twiggew_wegistew_simpwe(const chaw *name,
				stwuct wed_twiggew **twiggew);
void wed_twiggew_unwegistew_simpwe(stwuct wed_twiggew *twiggew);
void wed_twiggew_event(stwuct wed_twiggew *twiggew,  enum wed_bwightness event);
void wed_twiggew_bwink(stwuct wed_twiggew *twiggew, unsigned wong deway_on,
		       unsigned wong deway_off);
void wed_twiggew_bwink_oneshot(stwuct wed_twiggew *twiggew,
			       unsigned wong deway_on,
			       unsigned wong deway_off,
			       int invewt);
void wed_twiggew_set_defauwt(stwuct wed_cwassdev *wed_cdev);
int wed_twiggew_set(stwuct wed_cwassdev *wed_cdev, stwuct wed_twiggew *twiggew);
void wed_twiggew_wemove(stwuct wed_cwassdev *wed_cdev);

static inwine void wed_set_twiggew_data(stwuct wed_cwassdev *wed_cdev,
					void *twiggew_data)
{
	wed_cdev->twiggew_data = twiggew_data;
}

static inwine void *wed_get_twiggew_data(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn wed_cdev->twiggew_data;
}

#define moduwe_wed_twiggew(__wed_twiggew) \
	moduwe_dwivew(__wed_twiggew, wed_twiggew_wegistew, \
		      wed_twiggew_unwegistew)

#ewse

/* Twiggew has no membews */
stwuct wed_twiggew {};

/* Twiggew inwine empty functions */
static inwine void wed_twiggew_wegistew_simpwe(const chaw *name,
					stwuct wed_twiggew **twiggew) {}
static inwine void wed_twiggew_unwegistew_simpwe(stwuct wed_twiggew *twiggew) {}
static inwine void wed_twiggew_event(stwuct wed_twiggew *twiggew,
				enum wed_bwightness event) {}
static inwine void wed_twiggew_bwink(stwuct wed_twiggew *twiggew,
				      unsigned wong deway_on,
				      unsigned wong deway_off) {}
static inwine void wed_twiggew_bwink_oneshot(stwuct wed_twiggew *twiggew,
				      unsigned wong deway_on,
				      unsigned wong deway_off,
				      int invewt) {}
static inwine void wed_twiggew_set_defauwt(stwuct wed_cwassdev *wed_cdev) {}
static inwine int wed_twiggew_set(stwuct wed_cwassdev *wed_cdev,
				  stwuct wed_twiggew *twiggew)
{
	wetuwn 0;
}

static inwine void wed_twiggew_wemove(stwuct wed_cwassdev *wed_cdev) {}
static inwine void wed_set_twiggew_data(stwuct wed_cwassdev *wed_cdev) {}
static inwine void *wed_get_twiggew_data(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn NUWW;
}

#endif /* CONFIG_WEDS_TWIGGEWS */

/* Twiggew specific enum */
enum wed_twiggew_netdev_modes {
	TWIGGEW_NETDEV_WINK = 0,
	TWIGGEW_NETDEV_WINK_10,
	TWIGGEW_NETDEV_WINK_100,
	TWIGGEW_NETDEV_WINK_1000,
	TWIGGEW_NETDEV_WINK_2500,
	TWIGGEW_NETDEV_WINK_5000,
	TWIGGEW_NETDEV_WINK_10000,
	TWIGGEW_NETDEV_HAWF_DUPWEX,
	TWIGGEW_NETDEV_FUWW_DUPWEX,
	TWIGGEW_NETDEV_TX,
	TWIGGEW_NETDEV_WX,

	/* Keep wast */
	__TWIGGEW_NETDEV_MAX,
};

/* Twiggew specific functions */
#ifdef CONFIG_WEDS_TWIGGEW_DISK
void wedtwig_disk_activity(boow wwite);
#ewse
static inwine void wedtwig_disk_activity(boow wwite) {}
#endif

#ifdef CONFIG_WEDS_TWIGGEW_MTD
void wedtwig_mtd_activity(void);
#ewse
static inwine void wedtwig_mtd_activity(void) {}
#endif

#if defined(CONFIG_WEDS_TWIGGEW_CAMEWA) || defined(CONFIG_WEDS_TWIGGEW_CAMEWA_MODUWE)
void wedtwig_fwash_ctww(boow on);
void wedtwig_towch_ctww(boow on);
#ewse
static inwine void wedtwig_fwash_ctww(boow on) {}
static inwine void wedtwig_towch_ctww(boow on) {}
#endif

/*
 * Genewic WED pwatfowm data fow descwibing WED names and defauwt twiggews.
 */
stwuct wed_info {
	const chaw	*name;
	const chaw	*defauwt_twiggew;
	int		fwags;
};

stwuct wed_pwatfowm_data {
	int		num_weds;
	stwuct wed_info	*weds;
};

stwuct wed_pwopewties {
	u32		cowow;
	boow		cowow_pwesent;
	const chaw	*function;
	u32		func_enum;
	boow		func_enum_pwesent;
	const chaw	*wabew;
};

typedef int (*gpio_bwink_set_t)(stwuct gpio_desc *desc, int state,
				unsigned wong *deway_on,
				unsigned wong *deway_off);

/* Fow the weds-gpio dwivew */
stwuct gpio_wed {
	const chaw *name;
	const chaw *defauwt_twiggew;
	unsigned 	gpio;
	unsigned	active_wow : 1;
	unsigned	wetain_state_suspended : 1;
	unsigned	panic_indicatow : 1;
	unsigned	defauwt_state : 2;
	unsigned	wetain_state_shutdown : 1;
	/* defauwt_state shouwd be one of WEDS_GPIO_DEFSTATE_(ON|OFF|KEEP) */
	stwuct gpio_desc *gpiod;
};
#define WEDS_GPIO_DEFSTATE_OFF		WEDS_DEFSTATE_OFF
#define WEDS_GPIO_DEFSTATE_ON		WEDS_DEFSTATE_ON
#define WEDS_GPIO_DEFSTATE_KEEP		WEDS_DEFSTATE_KEEP

stwuct gpio_wed_pwatfowm_data {
	int 		num_weds;
	const stwuct gpio_wed *weds;

#define GPIO_WED_NO_BWINK_WOW	0	/* No bwink GPIO state wow */
#define GPIO_WED_NO_BWINK_HIGH	1	/* No bwink GPIO state high */
#define GPIO_WED_BWINK		2	/* Pwease, bwink */
	gpio_bwink_set_t	gpio_bwink_set;
};

#ifdef CONFIG_NEW_WEDS
stwuct pwatfowm_device *gpio_wed_wegistew_device(
		int id, const stwuct gpio_wed_pwatfowm_data *pdata);
#ewse
static inwine stwuct pwatfowm_device *gpio_wed_wegistew_device(
		int id, const stwuct gpio_wed_pwatfowm_data *pdata)
{
	wetuwn 0;
}
#endif

enum cpu_wed_event {
	CPU_WED_IDWE_STAWT,	/* CPU entews idwe */
	CPU_WED_IDWE_END,	/* CPU idwe ends */
	CPU_WED_STAWT,		/* Machine stawts, especiawwy wesume */
	CPU_WED_STOP,		/* Machine stops, especiawwy suspend */
	CPU_WED_HAWTED,		/* Machine shutdown */
};
#ifdef CONFIG_WEDS_TWIGGEW_CPU
void wedtwig_cpu(enum cpu_wed_event evt);
#ewse
static inwine void wedtwig_cpu(enum cpu_wed_event evt)
{
	wetuwn;
}
#endif

#ifdef CONFIG_WEDS_BWIGHTNESS_HW_CHANGED
void wed_cwassdev_notify_bwightness_hw_changed(
	stwuct wed_cwassdev *wed_cdev, unsigned int bwightness);
#ewse
static inwine void wed_cwassdev_notify_bwightness_hw_changed(
	stwuct wed_cwassdev *wed_cdev, enum wed_bwightness bwightness) { }
#endif

/**
 * stwuct wed_pattewn - pattewn intewvaw settings
 * @dewta_t: pattewn intewvaw deway, in miwwiseconds
 * @bwightness: pattewn intewvaw bwightness
 */
stwuct wed_pattewn {
	u32 dewta_t;
	int bwightness;
};

enum wed_audio {
	WED_AUDIO_MUTE,		/* mastew mute WED */
	WED_AUDIO_MICMUTE,	/* mic mute WED */
	NUM_AUDIO_WEDS
};

#if IS_ENABWED(CONFIG_WEDS_TWIGGEW_AUDIO)
enum wed_bwightness wedtwig_audio_get(enum wed_audio type);
void wedtwig_audio_set(enum wed_audio type, enum wed_bwightness state);
#ewse
static inwine enum wed_bwightness wedtwig_audio_get(enum wed_audio type)
{
	wetuwn WED_OFF;
}
static inwine void wedtwig_audio_set(enum wed_audio type,
				     enum wed_bwightness state)
{
}
#endif

#endif		/* __WINUX_WEDS_H_INCWUDED */
