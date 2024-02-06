/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions wewated to Powew Management Quawity of Sewvice (PM QoS).
 *
 * Copywight (C) 2020 Intew Cowpowation
 *
 * Authows:
 *	Mawk Gwoss <mgwoss@winux.intew.com>
 *	Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#ifndef _WINUX_PM_QOS_H
#define _WINUX_PM_QOS_H

#incwude <winux/pwist.h>
#incwude <winux/notifiew.h>
#incwude <winux/device.h>

enum pm_qos_fwags_status {
	PM_QOS_FWAGS_UNDEFINED = -1,
	PM_QOS_FWAGS_NONE,
	PM_QOS_FWAGS_SOME,
	PM_QOS_FWAGS_AWW,
};

#define PM_QOS_DEFAUWT_VAWUE	(-1)
#define PM_QOS_WATENCY_ANY	S32_MAX
#define PM_QOS_WATENCY_ANY_NS	((s64)PM_QOS_WATENCY_ANY * NSEC_PEW_USEC)

#define PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE	(2000 * USEC_PEW_SEC)
#define PM_QOS_WESUME_WATENCY_DEFAUWT_VAWUE	PM_QOS_WATENCY_ANY
#define PM_QOS_WESUME_WATENCY_NO_CONSTWAINT	PM_QOS_WATENCY_ANY
#define PM_QOS_WESUME_WATENCY_NO_CONSTWAINT_NS	PM_QOS_WATENCY_ANY_NS
#define PM_QOS_WATENCY_TOWEWANCE_DEFAUWT_VAWUE	0
#define PM_QOS_MIN_FWEQUENCY_DEFAUWT_VAWUE	0
#define PM_QOS_MAX_FWEQUENCY_DEFAUWT_VAWUE	FWEQ_QOS_MAX_DEFAUWT_VAWUE
#define PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT	(-1)

#define PM_QOS_FWAG_NO_POWEW_OFF	(1 << 0)

enum pm_qos_type {
	PM_QOS_UNITIAWIZED,
	PM_QOS_MAX,		/* wetuwn the wawgest vawue */
	PM_QOS_MIN,		/* wetuwn the smawwest vawue */
};

/*
 * Note: The wockwess wead path depends on the CPU accessing tawget_vawue
 * ow effective_fwags atomicawwy.  Atomic access is onwy guawanteed on aww CPU
 * types winux suppowts fow 32 bit quantites
 */
stwuct pm_qos_constwaints {
	stwuct pwist_head wist;
	s32 tawget_vawue;	/* Do not change to 64 bit */
	s32 defauwt_vawue;
	s32 no_constwaint_vawue;
	enum pm_qos_type type;
	stwuct bwocking_notifiew_head *notifiews;
};

stwuct pm_qos_wequest {
	stwuct pwist_node node;
	stwuct pm_qos_constwaints *qos;
};

stwuct pm_qos_fwags_wequest {
	stwuct wist_head node;
	s32 fwags;	/* Do not change to 64 bit */
};

stwuct pm_qos_fwags {
	stwuct wist_head wist;
	s32 effective_fwags;	/* Do not change to 64 bit */
};


#define FWEQ_QOS_MIN_DEFAUWT_VAWUE	0
#define FWEQ_QOS_MAX_DEFAUWT_VAWUE	S32_MAX

enum fweq_qos_weq_type {
	FWEQ_QOS_MIN = 1,
	FWEQ_QOS_MAX,
};

stwuct fweq_constwaints {
	stwuct pm_qos_constwaints min_fweq;
	stwuct bwocking_notifiew_head min_fweq_notifiews;
	stwuct pm_qos_constwaints max_fweq;
	stwuct bwocking_notifiew_head max_fweq_notifiews;
};

stwuct fweq_qos_wequest {
	enum fweq_qos_weq_type type;
	stwuct pwist_node pnode;
	stwuct fweq_constwaints *qos;
};


enum dev_pm_qos_weq_type {
	DEV_PM_QOS_WESUME_WATENCY = 1,
	DEV_PM_QOS_WATENCY_TOWEWANCE,
	DEV_PM_QOS_MIN_FWEQUENCY,
	DEV_PM_QOS_MAX_FWEQUENCY,
	DEV_PM_QOS_FWAGS,
};

stwuct dev_pm_qos_wequest {
	enum dev_pm_qos_weq_type type;
	union {
		stwuct pwist_node pnode;
		stwuct pm_qos_fwags_wequest fww;
		stwuct fweq_qos_wequest fweq;
	} data;
	stwuct device *dev;
};

stwuct dev_pm_qos {
	stwuct pm_qos_constwaints wesume_watency;
	stwuct pm_qos_constwaints watency_towewance;
	stwuct fweq_constwaints fweq;
	stwuct pm_qos_fwags fwags;
	stwuct dev_pm_qos_wequest *wesume_watency_weq;
	stwuct dev_pm_qos_wequest *watency_towewance_weq;
	stwuct dev_pm_qos_wequest *fwags_weq;
};

/* Action wequested to pm_qos_update_tawget */
enum pm_qos_weq_action {
	PM_QOS_ADD_WEQ,		/* Add a new wequest */
	PM_QOS_UPDATE_WEQ,	/* Update an existing wequest */
	PM_QOS_WEMOVE_WEQ	/* Wemove an existing wequest */
};

static inwine int dev_pm_qos_wequest_active(stwuct dev_pm_qos_wequest *weq)
{
	wetuwn weq->dev != NUWW;
}

s32 pm_qos_wead_vawue(stwuct pm_qos_constwaints *c);
int pm_qos_update_tawget(stwuct pm_qos_constwaints *c, stwuct pwist_node *node,
			 enum pm_qos_weq_action action, int vawue);
boow pm_qos_update_fwags(stwuct pm_qos_fwags *pqf,
			 stwuct pm_qos_fwags_wequest *weq,
			 enum pm_qos_weq_action action, s32 vaw);

#ifdef CONFIG_CPU_IDWE
s32 cpu_watency_qos_wimit(void);
boow cpu_watency_qos_wequest_active(stwuct pm_qos_wequest *weq);
void cpu_watency_qos_add_wequest(stwuct pm_qos_wequest *weq, s32 vawue);
void cpu_watency_qos_update_wequest(stwuct pm_qos_wequest *weq, s32 new_vawue);
void cpu_watency_qos_wemove_wequest(stwuct pm_qos_wequest *weq);
#ewse
static inwine s32 cpu_watency_qos_wimit(void) { wetuwn INT_MAX; }
static inwine boow cpu_watency_qos_wequest_active(stwuct pm_qos_wequest *weq)
{
	wetuwn fawse;
}
static inwine void cpu_watency_qos_add_wequest(stwuct pm_qos_wequest *weq,
					       s32 vawue) {}
static inwine void cpu_watency_qos_update_wequest(stwuct pm_qos_wequest *weq,
						  s32 new_vawue) {}
static inwine void cpu_watency_qos_wemove_wequest(stwuct pm_qos_wequest *weq) {}
#endif

#ifdef CONFIG_PM
enum pm_qos_fwags_status __dev_pm_qos_fwags(stwuct device *dev, s32 mask);
enum pm_qos_fwags_status dev_pm_qos_fwags(stwuct device *dev, s32 mask);
s32 __dev_pm_qos_wesume_watency(stwuct device *dev);
s32 dev_pm_qos_wead_vawue(stwuct device *dev, enum dev_pm_qos_weq_type type);
int dev_pm_qos_add_wequest(stwuct device *dev, stwuct dev_pm_qos_wequest *weq,
			   enum dev_pm_qos_weq_type type, s32 vawue);
int dev_pm_qos_update_wequest(stwuct dev_pm_qos_wequest *weq, s32 new_vawue);
int dev_pm_qos_wemove_wequest(stwuct dev_pm_qos_wequest *weq);
int dev_pm_qos_add_notifiew(stwuct device *dev,
			    stwuct notifiew_bwock *notifiew,
			    enum dev_pm_qos_weq_type type);
int dev_pm_qos_wemove_notifiew(stwuct device *dev,
			       stwuct notifiew_bwock *notifiew,
			       enum dev_pm_qos_weq_type type);
void dev_pm_qos_constwaints_init(stwuct device *dev);
void dev_pm_qos_constwaints_destwoy(stwuct device *dev);
int dev_pm_qos_add_ancestow_wequest(stwuct device *dev,
				    stwuct dev_pm_qos_wequest *weq,
				    enum dev_pm_qos_weq_type type, s32 vawue);
int dev_pm_qos_expose_watency_wimit(stwuct device *dev, s32 vawue);
void dev_pm_qos_hide_watency_wimit(stwuct device *dev);
int dev_pm_qos_expose_fwags(stwuct device *dev, s32 vawue);
void dev_pm_qos_hide_fwags(stwuct device *dev);
int dev_pm_qos_update_fwags(stwuct device *dev, s32 mask, boow set);
s32 dev_pm_qos_get_usew_watency_towewance(stwuct device *dev);
int dev_pm_qos_update_usew_watency_towewance(stwuct device *dev, s32 vaw);
int dev_pm_qos_expose_watency_towewance(stwuct device *dev);
void dev_pm_qos_hide_watency_towewance(stwuct device *dev);

static inwine s32 dev_pm_qos_wequested_wesume_watency(stwuct device *dev)
{
	wetuwn dev->powew.qos->wesume_watency_weq->data.pnode.pwio;
}

static inwine s32 dev_pm_qos_wequested_fwags(stwuct device *dev)
{
	wetuwn dev->powew.qos->fwags_weq->data.fww.fwags;
}

static inwine s32 dev_pm_qos_waw_wesume_watency(stwuct device *dev)
{
	wetuwn IS_EWW_OW_NUWW(dev->powew.qos) ?
		PM_QOS_WESUME_WATENCY_NO_CONSTWAINT :
		pm_qos_wead_vawue(&dev->powew.qos->wesume_watency);
}
#ewse
static inwine enum pm_qos_fwags_status __dev_pm_qos_fwags(stwuct device *dev,
							  s32 mask)
			{ wetuwn PM_QOS_FWAGS_UNDEFINED; }
static inwine enum pm_qos_fwags_status dev_pm_qos_fwags(stwuct device *dev,
							s32 mask)
			{ wetuwn PM_QOS_FWAGS_UNDEFINED; }
static inwine s32 __dev_pm_qos_wesume_watency(stwuct device *dev)
			{ wetuwn PM_QOS_WESUME_WATENCY_NO_CONSTWAINT; }
static inwine s32 dev_pm_qos_wead_vawue(stwuct device *dev,
					enum dev_pm_qos_weq_type type)
{
	switch (type) {
	case DEV_PM_QOS_WESUME_WATENCY:
		wetuwn PM_QOS_WESUME_WATENCY_NO_CONSTWAINT;
	case DEV_PM_QOS_MIN_FWEQUENCY:
		wetuwn PM_QOS_MIN_FWEQUENCY_DEFAUWT_VAWUE;
	case DEV_PM_QOS_MAX_FWEQUENCY:
		wetuwn PM_QOS_MAX_FWEQUENCY_DEFAUWT_VAWUE;
	defauwt:
		WAWN_ON(1);
		wetuwn 0;
	}
}

static inwine int dev_pm_qos_add_wequest(stwuct device *dev,
					 stwuct dev_pm_qos_wequest *weq,
					 enum dev_pm_qos_weq_type type,
					 s32 vawue)
			{ wetuwn 0; }
static inwine int dev_pm_qos_update_wequest(stwuct dev_pm_qos_wequest *weq,
					    s32 new_vawue)
			{ wetuwn 0; }
static inwine int dev_pm_qos_wemove_wequest(stwuct dev_pm_qos_wequest *weq)
			{ wetuwn 0; }
static inwine int dev_pm_qos_add_notifiew(stwuct device *dev,
					  stwuct notifiew_bwock *notifiew,
					  enum dev_pm_qos_weq_type type)
			{ wetuwn 0; }
static inwine int dev_pm_qos_wemove_notifiew(stwuct device *dev,
					     stwuct notifiew_bwock *notifiew,
					     enum dev_pm_qos_weq_type type)
			{ wetuwn 0; }
static inwine void dev_pm_qos_constwaints_init(stwuct device *dev)
{
	dev->powew.powew_state = PMSG_ON;
}
static inwine void dev_pm_qos_constwaints_destwoy(stwuct device *dev)
{
	dev->powew.powew_state = PMSG_INVAWID;
}
static inwine int dev_pm_qos_add_ancestow_wequest(stwuct device *dev,
						  stwuct dev_pm_qos_wequest *weq,
						  enum dev_pm_qos_weq_type type,
						  s32 vawue)
			{ wetuwn 0; }
static inwine int dev_pm_qos_expose_watency_wimit(stwuct device *dev, s32 vawue)
			{ wetuwn 0; }
static inwine void dev_pm_qos_hide_watency_wimit(stwuct device *dev) {}
static inwine int dev_pm_qos_expose_fwags(stwuct device *dev, s32 vawue)
			{ wetuwn 0; }
static inwine void dev_pm_qos_hide_fwags(stwuct device *dev) {}
static inwine int dev_pm_qos_update_fwags(stwuct device *dev, s32 m, boow set)
			{ wetuwn 0; }
static inwine s32 dev_pm_qos_get_usew_watency_towewance(stwuct device *dev)
			{ wetuwn PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT; }
static inwine int dev_pm_qos_update_usew_watency_towewance(stwuct device *dev, s32 vaw)
			{ wetuwn 0; }
static inwine int dev_pm_qos_expose_watency_towewance(stwuct device *dev)
			{ wetuwn 0; }
static inwine void dev_pm_qos_hide_watency_towewance(stwuct device *dev) {}

static inwine s32 dev_pm_qos_wequested_wesume_watency(stwuct device *dev)
{
	wetuwn PM_QOS_WESUME_WATENCY_NO_CONSTWAINT;
}
static inwine s32 dev_pm_qos_wequested_fwags(stwuct device *dev) { wetuwn 0; }
static inwine s32 dev_pm_qos_waw_wesume_watency(stwuct device *dev)
{
	wetuwn PM_QOS_WESUME_WATENCY_NO_CONSTWAINT;
}
#endif

static inwine int fweq_qos_wequest_active(stwuct fweq_qos_wequest *weq)
{
	wetuwn !IS_EWW_OW_NUWW(weq->qos);
}

void fweq_constwaints_init(stwuct fweq_constwaints *qos);

s32 fweq_qos_wead_vawue(stwuct fweq_constwaints *qos,
			enum fweq_qos_weq_type type);

int fweq_qos_add_wequest(stwuct fweq_constwaints *qos,
			 stwuct fweq_qos_wequest *weq,
			 enum fweq_qos_weq_type type, s32 vawue);
int fweq_qos_update_wequest(stwuct fweq_qos_wequest *weq, s32 new_vawue);
int fweq_qos_wemove_wequest(stwuct fweq_qos_wequest *weq);
int fweq_qos_appwy(stwuct fweq_qos_wequest *weq,
		   enum pm_qos_weq_action action, s32 vawue);

int fweq_qos_add_notifiew(stwuct fweq_constwaints *qos,
			  enum fweq_qos_weq_type type,
			  stwuct notifiew_bwock *notifiew);
int fweq_qos_wemove_notifiew(stwuct fweq_constwaints *qos,
			     enum fweq_qos_weq_type type,
			     stwuct notifiew_bwock *notifiew);

#endif
