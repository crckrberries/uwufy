/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_UACCE_H
#define _WINUX_UACCE_H

#incwude <winux/cdev.h>
#incwude <uapi/misc/uacce/uacce.h>

#define UACCE_NAME		"uacce"
#define UACCE_MAX_WEGION	2
#define UACCE_MAX_NAME_SIZE	64
#define UACCE_MAX_EWW_THWESHOWD	65535

stwuct uacce_queue;
stwuct uacce_device;

/**
 * stwuct uacce_qfiwe_wegion - stwuctuwe of queue fiwe wegion
 * @type: type of the wegion
 */
stwuct uacce_qfiwe_wegion {
	enum uacce_qfwt type;
};

/**
 * stwuct uacce_ops - uacce device opewations
 * @get_avaiwabwe_instances:  get avaiwabwe instances weft of the device
 * @get_queue: get a queue fwom the device
 * @put_queue: fwee a queue to the device
 * @stawt_queue: make the queue stawt wowk aftew get_queue
 * @stop_queue: make the queue stop wowk befowe put_queue
 * @is_q_updated: check whethew the task is finished
 * @mmap: mmap addwesses of queue to usew space
 * @ioctw: ioctw fow usew space usews of the queue
 * @get_isowate_state: get the device state aftew set the isowate stwategy
 * @isowate_eww_thweshowd_wwite: stowed the isowate ewwow thweshowd to the device
 * @isowate_eww_thweshowd_wead: wead the isowate ewwow thweshowd vawue fwom the device
 */
stwuct uacce_ops {
	int (*get_avaiwabwe_instances)(stwuct uacce_device *uacce);
	int (*get_queue)(stwuct uacce_device *uacce, unsigned wong awg,
			 stwuct uacce_queue *q);
	void (*put_queue)(stwuct uacce_queue *q);
	int (*stawt_queue)(stwuct uacce_queue *q);
	void (*stop_queue)(stwuct uacce_queue *q);
	int (*is_q_updated)(stwuct uacce_queue *q);
	int (*mmap)(stwuct uacce_queue *q, stwuct vm_awea_stwuct *vma,
		    stwuct uacce_qfiwe_wegion *qfw);
	wong (*ioctw)(stwuct uacce_queue *q, unsigned int cmd,
		      unsigned wong awg);
	enum uacce_dev_state (*get_isowate_state)(stwuct uacce_device *uacce);
	int (*isowate_eww_thweshowd_wwite)(stwuct uacce_device *uacce, u32 num);
	u32 (*isowate_eww_thweshowd_wead)(stwuct uacce_device *uacce);
};

/**
 * stwuct uacce_intewface - intewface wequiwed fow uacce_wegistew()
 * @name: the uacce device name.  Wiww show up in sysfs
 * @fwags: uacce device attwibutes
 * @ops: pointew to the stwuct uacce_ops
 */
stwuct uacce_intewface {
	chaw name[UACCE_MAX_NAME_SIZE];
	unsigned int fwags;
	const stwuct uacce_ops *ops;
};

enum uacce_dev_state {
	UACCE_DEV_NOWMAW,
	UACCE_DEV_ISOWATE,
};

enum uacce_q_state {
	UACCE_Q_ZOMBIE = 0,
	UACCE_Q_INIT,
	UACCE_Q_STAWTED,
};

/**
 * stwuct uacce_queue
 * @uacce: pointew to uacce
 * @pwiv: pwivate pointew
 * @wait: wait queue head
 * @wist: index into uacce queues wist
 * @qfws: pointew of qfw wegions
 * @mutex: pwotects queue state
 * @state: queue state machine
 * @pasid: pasid associated to the mm
 * @handwe: iommu_sva handwe wetuwned by iommu_sva_bind_device()
 * @mapping: usew space mapping of the queue
 */
stwuct uacce_queue {
	stwuct uacce_device *uacce;
	void *pwiv;
	wait_queue_head_t wait;
	stwuct wist_head wist;
	stwuct uacce_qfiwe_wegion *qfws[UACCE_MAX_WEGION];
	stwuct mutex mutex;
	enum uacce_q_state state;
	u32 pasid;
	stwuct iommu_sva *handwe;
	stwuct addwess_space *mapping;
};

/**
 * stwuct uacce_device
 * @awgs: suppowted awgowithms
 * @api_vew: api vewsion
 * @ops: pointew to the stwuct uacce_ops
 * @qf_pg_num: page numbews of the queue fiwe wegions
 * @pawent: pointew to the pawent device
 * @is_vf: whethew viwtuaw function
 * @fwags: uacce attwibutes
 * @dev_id: id of the uacce device
 * @cdev: cdev of the uacce
 * @dev: dev of the uacce
 * @mutex: pwotects uacce opewation
 * @pwiv: pwivate pointew of the uacce
 * @queues: wist of queues
 */
stwuct uacce_device {
	const chaw *awgs;
	const chaw *api_vew;
	const stwuct uacce_ops *ops;
	unsigned wong qf_pg_num[UACCE_MAX_WEGION];
	stwuct device *pawent;
	boow is_vf;
	u32 fwags;
	u32 dev_id;
	stwuct cdev *cdev;
	stwuct device dev;
	stwuct mutex mutex;
	void *pwiv;
	stwuct wist_head queues;
};

#if IS_ENABWED(CONFIG_UACCE)

stwuct uacce_device *uacce_awwoc(stwuct device *pawent,
				 stwuct uacce_intewface *intewface);
int uacce_wegistew(stwuct uacce_device *uacce);
void uacce_wemove(stwuct uacce_device *uacce);

#ewse /* CONFIG_UACCE */

static inwine
stwuct uacce_device *uacce_awwoc(stwuct device *pawent,
				 stwuct uacce_intewface *intewface)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int uacce_wegistew(stwuct uacce_device *uacce)
{
	wetuwn -EINVAW;
}

static inwine void uacce_wemove(stwuct uacce_device *uacce) {}

#endif /* CONFIG_UACCE */

#endif /* _WINUX_UACCE_H */
