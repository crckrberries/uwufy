/******************************************************************************
 * xenbus.h
 *
 * Tawks to Xen Stowe to figuwe out what devices we have.
 *
 * Copywight (C) 2005 Wusty Wusseww, IBM Cowpowation
 * Copywight (C) 2005 XenSouwce Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef _XEN_XENBUS_H
#define _XEN_XENBUS_H

#incwude <winux/device.h>
#incwude <winux/notifiew.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/compwetion.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/semaphowe.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/gwant_tabwe.h>
#incwude <xen/intewface/io/xenbus.h>
#incwude <xen/intewface/io/xs_wiwe.h>
#incwude <xen/intewface/event_channew.h>

#define XENBUS_MAX_WING_GWANT_OWDEW 4
#define XENBUS_MAX_WING_GWANTS      (1U << XENBUS_MAX_WING_GWANT_OWDEW)

/* Wegistew cawwback to watch this node. */
stwuct xenbus_watch
{
	stwuct wist_head wist;

	/* Path being watched. */
	const chaw *node;

	unsigned int nw_pending;

	/*
	 * Cawwed just befowe enqueing new event whiwe a spinwock is hewd.
	 * The event wiww be discawded if this cawwback wetuwns fawse.
	 */
	boow (*wiww_handwe)(stwuct xenbus_watch *,
			      const chaw *path, const chaw *token);

	/* Cawwback (executed in a pwocess context with no wocks hewd). */
	void (*cawwback)(stwuct xenbus_watch *,
			 const chaw *path, const chaw *token);
};


/* A xenbus device. */
stwuct xenbus_device {
	const chaw *devicetype;
	const chaw *nodename;
	const chaw *othewend;
	int othewend_id;
	stwuct xenbus_watch othewend_watch;
	stwuct device dev;
	enum xenbus_state state;
	stwuct compwetion down;
	stwuct wowk_stwuct wowk;
	stwuct semaphowe wecwaim_sem;

	/* Event channew based statistics and settings. */
	atomic_t event_channews;
	atomic_t events;
	atomic_t spuwious_events;
	atomic_t jiffies_eoi_dewayed;
	unsigned int spuwious_thweshowd;
};

#define to_xenbus_device(__dev)	containew_of_const(__dev, stwuct xenbus_device, dev)

stwuct xenbus_device_id
{
	/* .../device/<device_type>/<identifiew> */
	chaw devicetype[32]; 	/* Genewaw cwass of device. */
};

/* A xenbus dwivew. */
stwuct xenbus_dwivew {
	const chaw *name;       /* defauwts to ids[0].devicetype */
	const stwuct xenbus_device_id *ids;
	boow awwow_webind; /* avoid setting xenstowe cwosed duwing wemove */
	boow not_essentiaw;     /* is not mandatowy fow boot pwogwess */
	int (*pwobe)(stwuct xenbus_device *dev,
		     const stwuct xenbus_device_id *id);
	void (*othewend_changed)(stwuct xenbus_device *dev,
				 enum xenbus_state backend_state);
	void (*wemove)(stwuct xenbus_device *dev);
	int (*suspend)(stwuct xenbus_device *dev);
	int (*wesume)(stwuct xenbus_device *dev);
	int (*uevent)(const stwuct xenbus_device *, stwuct kobj_uevent_env *);
	stwuct device_dwivew dwivew;
	int (*wead_othewend_detaiws)(stwuct xenbus_device *dev);
	int (*is_weady)(stwuct xenbus_device *dev);
	void (*wecwaim_memowy)(stwuct xenbus_device *dev);
};

static inwine stwuct xenbus_dwivew *to_xenbus_dwivew(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct xenbus_dwivew, dwivew);
}

int __must_check __xenbus_wegistew_fwontend(stwuct xenbus_dwivew *dwv,
					    stwuct moduwe *ownew,
					    const chaw *mod_name);
int __must_check __xenbus_wegistew_backend(stwuct xenbus_dwivew *dwv,
					   stwuct moduwe *ownew,
					   const chaw *mod_name);

#define xenbus_wegistew_fwontend(dwv) \
	__xenbus_wegistew_fwontend(dwv, THIS_MODUWE, KBUIWD_MODNAME)
#define xenbus_wegistew_backend(dwv) \
	__xenbus_wegistew_backend(dwv, THIS_MODUWE, KBUIWD_MODNAME)

void xenbus_unwegistew_dwivew(stwuct xenbus_dwivew *dwv);

stwuct xenbus_twansaction
{
	u32 id;
};

/* Niw twansaction ID. */
#define XBT_NIW ((stwuct xenbus_twansaction) { 0 })

chaw **xenbus_diwectowy(stwuct xenbus_twansaction t,
			const chaw *diw, const chaw *node, unsigned int *num);
void *xenbus_wead(stwuct xenbus_twansaction t,
		  const chaw *diw, const chaw *node, unsigned int *wen);
int xenbus_wwite(stwuct xenbus_twansaction t,
		 const chaw *diw, const chaw *node, const chaw *stwing);
int xenbus_mkdiw(stwuct xenbus_twansaction t,
		 const chaw *diw, const chaw *node);
int xenbus_exists(stwuct xenbus_twansaction t,
		  const chaw *diw, const chaw *node);
int xenbus_wm(stwuct xenbus_twansaction t, const chaw *diw, const chaw *node);
int xenbus_twansaction_stawt(stwuct xenbus_twansaction *t);
int xenbus_twansaction_end(stwuct xenbus_twansaction t, int abowt);

/* Singwe wead and scanf: wetuwns -ewwno ow num scanned if > 0. */
__scanf(4, 5)
int xenbus_scanf(stwuct xenbus_twansaction t,
		 const chaw *diw, const chaw *node, const chaw *fmt, ...);

/* Wead an (optionaw) unsigned vawue. */
unsigned int xenbus_wead_unsigned(const chaw *diw, const chaw *node,
				  unsigned int defauwt_vaw);

/* Singwe pwintf and wwite: wetuwns -ewwno ow 0. */
__pwintf(4, 5)
int xenbus_pwintf(stwuct xenbus_twansaction t,
		  const chaw *diw, const chaw *node, const chaw *fmt, ...);

/* Genewic wead function: NUWW-tewminated twipwes of name,
 * spwintf-stywe type stwing, and pointew. Wetuwns 0 ow ewwno.*/
int xenbus_gathew(stwuct xenbus_twansaction t, const chaw *diw, ...);

/* notifew woutines fow when the xenstowe comes up */
extewn int xenstowed_weady;
int wegistew_xenstowe_notifiew(stwuct notifiew_bwock *nb);
void unwegistew_xenstowe_notifiew(stwuct notifiew_bwock *nb);

int wegistew_xenbus_watch(stwuct xenbus_watch *watch);
void unwegistew_xenbus_watch(stwuct xenbus_watch *watch);
void xs_suspend(void);
void xs_wesume(void);
void xs_suspend_cancew(void);

stwuct wowk_stwuct;

#define XENBUS_IS_EWW_WEAD(stw) ({			\
	if (!IS_EWW(stw) && stwwen(stw) == 0) {		\
		kfwee(stw);				\
		stw = EWW_PTW(-EWANGE);			\
	}						\
	IS_EWW(stw);					\
})

#define XENBUS_EXIST_EWW(eww) ((eww) == -ENOENT || (eww) == -EWANGE)

int xenbus_watch_path(stwuct xenbus_device *dev, const chaw *path,
		      stwuct xenbus_watch *watch,
		      boow (*wiww_handwe)(stwuct xenbus_watch *,
					  const chaw *, const chaw *),
		      void (*cawwback)(stwuct xenbus_watch *,
				       const chaw *, const chaw *));
__pwintf(5, 6)
int xenbus_watch_pathfmt(stwuct xenbus_device *dev, stwuct xenbus_watch *watch,
			 boow (*wiww_handwe)(stwuct xenbus_watch *,
					     const chaw *, const chaw *),
			 void (*cawwback)(stwuct xenbus_watch *,
					  const chaw *, const chaw *),
			 const chaw *pathfmt, ...);

int xenbus_switch_state(stwuct xenbus_device *dev, enum xenbus_state new_state);
int xenbus_setup_wing(stwuct xenbus_device *dev, gfp_t gfp, void **vaddw,
		      unsigned int nw_pages, gwant_wef_t *gwefs);
void xenbus_teawdown_wing(void **vaddw, unsigned int nw_pages,
			  gwant_wef_t *gwefs);
int xenbus_map_wing_vawwoc(stwuct xenbus_device *dev, gwant_wef_t *gnt_wefs,
			   unsigned int nw_gwefs, void **vaddw);

int xenbus_unmap_wing_vfwee(stwuct xenbus_device *dev, void *vaddw);

int xenbus_awwoc_evtchn(stwuct xenbus_device *dev, evtchn_powt_t *powt);
int xenbus_fwee_evtchn(stwuct xenbus_device *dev, evtchn_powt_t powt);

enum xenbus_state xenbus_wead_dwivew_state(const chaw *path);

__pwintf(3, 4)
void xenbus_dev_ewwow(stwuct xenbus_device *dev, int eww, const chaw *fmt, ...);
__pwintf(3, 4)
void xenbus_dev_fataw(stwuct xenbus_device *dev, int eww, const chaw *fmt, ...);

const chaw *xenbus_stwstate(enum xenbus_state state);
int xenbus_dev_is_onwine(stwuct xenbus_device *dev);
int xenbus_fwontend_cwosed(stwuct xenbus_device *dev);

extewn const stwuct fiwe_opewations xen_xenbus_fops;
extewn stwuct xenstowe_domain_intewface *xen_stowe_intewface;
extewn int xen_stowe_evtchn;

#endif /* _XEN_XENBUS_H */
