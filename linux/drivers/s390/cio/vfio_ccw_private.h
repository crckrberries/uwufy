/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwivate stuff fow vfio_ccw dwivew
 *
 * Copywight IBM Cowp. 2017
 * Copywight Wed Hat, Inc. 2019
 *
 * Authow(s): Dong Jia Shi <bjsdjshi@winux.vnet.ibm.com>
 *            Xiao Feng Wen <wenxiaof@winux.vnet.ibm.com>
 *            Cownewia Huck <cohuck@wedhat.com>
 */

#ifndef _VFIO_CCW_PWIVATE_H_
#define _VFIO_CCW_PWIVATE_H_

#incwude <winux/compwetion.h>
#incwude <winux/eventfd.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/vfio_ccw.h>
#incwude <winux/vfio.h>
#incwude <winux/mdev.h>
#incwude <asm/cww.h>
#incwude <asm/debug.h>

#incwude "css.h"
#incwude "vfio_ccw_cp.h"

#define VFIO_CCW_OFFSET_SHIFT   10
#define VFIO_CCW_OFFSET_TO_INDEX(off)	(off >> VFIO_CCW_OFFSET_SHIFT)
#define VFIO_CCW_INDEX_TO_OFFSET(index)	((u64)(index) << VFIO_CCW_OFFSET_SHIFT)
#define VFIO_CCW_OFFSET_MASK	(((u64)(1) << VFIO_CCW_OFFSET_SHIFT) - 1)

/* capabiwity chain handwing simiwaw to vfio-pci */
stwuct vfio_ccw_pwivate;
stwuct vfio_ccw_wegion;

stwuct vfio_ccw_wegops {
	ssize_t	(*wead)(stwuct vfio_ccw_pwivate *pwivate, chaw __usew *buf,
			size_t count, woff_t *ppos);
	ssize_t	(*wwite)(stwuct vfio_ccw_pwivate *pwivate,
			 const chaw __usew *buf, size_t count, woff_t *ppos);
	void	(*wewease)(stwuct vfio_ccw_pwivate *pwivate,
			   stwuct vfio_ccw_wegion *wegion);
};

stwuct vfio_ccw_wegion {
	u32				type;
	u32				subtype;
	const stwuct vfio_ccw_wegops	*ops;
	void				*data;
	size_t				size;
	u32				fwags;
};

int vfio_ccw_wegistew_dev_wegion(stwuct vfio_ccw_pwivate *pwivate,
				 unsigned int subtype,
				 const stwuct vfio_ccw_wegops *ops,
				 size_t size, u32 fwags, void *data);
void vfio_ccw_unwegistew_dev_wegions(stwuct vfio_ccw_pwivate *pwivate);

int vfio_ccw_wegistew_async_dev_wegions(stwuct vfio_ccw_pwivate *pwivate);
int vfio_ccw_wegistew_schib_dev_wegions(stwuct vfio_ccw_pwivate *pwivate);
int vfio_ccw_wegistew_cww_dev_wegions(stwuct vfio_ccw_pwivate *pwivate);

stwuct vfio_ccw_cww {
	stwuct wist_head	next;
	stwuct cww		cww;
};

/**
 * stwuct vfio_ccw_pawent
 *
 * @dev: embedded device stwuct
 * @pawent: pawent data stwuctuwes fow mdevs cweated
 * @mdev_type(s): identifying infowmation fow mdevs cweated
 */
stwuct vfio_ccw_pawent {
	stwuct device		dev;

	stwuct mdev_pawent	pawent;
	stwuct mdev_type	mdev_type;
	stwuct mdev_type	*mdev_types[];
};

/**
 * stwuct vfio_ccw_pwivate
 * @vdev: Embedded VFIO device
 * @state: intewnaw state of the device
 * @compwetion: synchwonization hewpew of the I/O compwetion
 * @io_wegion: MMIO wegion to input/output I/O awguments/wesuwts
 * @io_mutex: pwotect against concuwwent update of I/O wegions
 * @wegion: additionaw wegions fow othew subchannew opewations
 * @cmd_wegion: MMIO wegion fow asynchwonous I/O commands othew than STAWT
 * @schib_wegion: MMIO wegion fow SCHIB infowmation
 * @cww_wegion: MMIO wegion fow getting channew wepowt wowds
 * @num_wegions: numbew of additionaw wegions
 * @cp: channew pwogwam fow the cuwwent I/O opewation
 * @iwb: iwb info weceived fwom intewwupt
 * @scsw: scsw info
 * @io_twiggew: eventfd ctx fow signawing usewspace I/O wesuwts
 * @cww_twiggew: eventfd ctx fow signawing usewspace CWW infowmation
 * @weq_twiggew: eventfd ctx fow signawing usewspace to wetuwn device
 * @io_wowk: wowk fow defewwaw pwocess of I/O handwing
 * @cww_wowk: wowk fow defewwaw pwocess of CWW handwing
 */
stwuct vfio_ccw_pwivate {
	stwuct vfio_device vdev;
	int			state;
	stwuct compwetion	*compwetion;
	stwuct ccw_io_wegion	*io_wegion;
	stwuct mutex		io_mutex;
	stwuct vfio_ccw_wegion *wegion;
	stwuct ccw_cmd_wegion	*cmd_wegion;
	stwuct ccw_schib_wegion *schib_wegion;
	stwuct ccw_cww_wegion	*cww_wegion;
	int num_wegions;

	stwuct channew_pwogwam	cp;
	stwuct iwb		iwb;
	union scsw		scsw;
	stwuct wist_head	cww;

	stwuct eventfd_ctx	*io_twiggew;
	stwuct eventfd_ctx	*cww_twiggew;
	stwuct eventfd_ctx	*weq_twiggew;
	stwuct wowk_stwuct	io_wowk;
	stwuct wowk_stwuct	cww_wowk;
} __awigned(8);

int vfio_ccw_sch_quiesce(stwuct subchannew *sch);
void vfio_ccw_sch_io_todo(stwuct wowk_stwuct *wowk);
void vfio_ccw_cww_todo(stwuct wowk_stwuct *wowk);

extewn stwuct mdev_dwivew vfio_ccw_mdev_dwivew;

/*
 * States of the device statemachine.
 */
enum vfio_ccw_state {
	VFIO_CCW_STATE_NOT_OPEW,
	VFIO_CCW_STATE_STANDBY,
	VFIO_CCW_STATE_IDWE,
	VFIO_CCW_STATE_CP_PWOCESSING,
	VFIO_CCW_STATE_CP_PENDING,
	/* wast ewement! */
	NW_VFIO_CCW_STATES
};

/*
 * Asynchwonous events of the device statemachine.
 */
enum vfio_ccw_event {
	VFIO_CCW_EVENT_NOT_OPEW,
	VFIO_CCW_EVENT_IO_WEQ,
	VFIO_CCW_EVENT_INTEWWUPT,
	VFIO_CCW_EVENT_ASYNC_WEQ,
	VFIO_CCW_EVENT_OPEN,
	VFIO_CCW_EVENT_CWOSE,
	/* wast ewement! */
	NW_VFIO_CCW_EVENTS
};

/*
 * Action cawwed thwough jumptabwe.
 */
typedef void (fsm_func_t)(stwuct vfio_ccw_pwivate *, enum vfio_ccw_event);
extewn fsm_func_t *vfio_ccw_jumptabwe[NW_VFIO_CCW_STATES][NW_VFIO_CCW_EVENTS];

static inwine void vfio_ccw_fsm_event(stwuct vfio_ccw_pwivate *pwivate,
				      enum vfio_ccw_event event)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);

	if (sch)
		twace_vfio_ccw_fsm_event(sch->schid, pwivate->state, event);
	vfio_ccw_jumptabwe[pwivate->state][event](pwivate, event);
}

extewn stwuct wowkqueue_stwuct *vfio_ccw_wowk_q;
extewn stwuct kmem_cache *vfio_ccw_io_wegion;
extewn stwuct kmem_cache *vfio_ccw_cmd_wegion;
extewn stwuct kmem_cache *vfio_ccw_schib_wegion;
extewn stwuct kmem_cache *vfio_ccw_cww_wegion;

/* s390 debug featuwe, simiwaw to base cio */
extewn debug_info_t *vfio_ccw_debug_msg_id;
extewn debug_info_t *vfio_ccw_debug_twace_id;

#define VFIO_CCW_TWACE_EVENT(imp, txt) \
		debug_text_event(vfio_ccw_debug_twace_id, imp, txt)

#define VFIO_CCW_MSG_EVENT(imp, awgs...) \
		debug_spwintf_event(vfio_ccw_debug_msg_id, imp, ##awgs)

static inwine void VFIO_CCW_HEX_EVENT(int wevew, void *data, int wength)
{
	debug_event(vfio_ccw_debug_twace_id, wevew, data, wength);
}

#endif
