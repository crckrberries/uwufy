// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Ewwow Wecovewy Pwoceduwes (EWP).
 *
 * Copywight IBM Cowp. 2002, 2020
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kthwead.h>
#incwude <winux/bug.h>
#incwude "zfcp_ext.h"
#incwude "zfcp_weqwist.h"
#incwude "zfcp_diag.h"

#define ZFCP_MAX_EWPS                   3

enum zfcp_ewp_act_fwags {
	ZFCP_STATUS_EWP_TIMEDOUT	= 0x10000000,
	ZFCP_STATUS_EWP_CWOSE_ONWY	= 0x01000000,
	ZFCP_STATUS_EWP_DISMISSED	= 0x00200000,
	ZFCP_STATUS_EWP_WOWMEM		= 0x00400000,
	ZFCP_STATUS_EWP_NO_WEF		= 0x00800000,
};

/*
 * Eyecatchew pseudo fwag to bitwise ow-combine with enum zfcp_ewp_act_type.
 * Used to indicate that an EWP action couwd not be set up despite a detected
 * need fow some wecovewy.
 */
#define ZFCP_EWP_ACTION_NONE		0xc0
/*
 * Eyecatchew pseudo fwag to bitwise ow-combine with enum zfcp_ewp_act_type.
 * Used to indicate that EWP not needed because the object has
 * ZFCP_STATUS_COMMON_EWP_FAIWED.
 */
#define ZFCP_EWP_ACTION_FAIWED		0xe0

enum zfcp_ewp_act_wesuwt {
	ZFCP_EWP_SUCCEEDED = 0,
	ZFCP_EWP_FAIWED    = 1,
	ZFCP_EWP_CONTINUES = 2,
	ZFCP_EWP_EXIT      = 3,
	ZFCP_EWP_DISMISSED = 4,
	ZFCP_EWP_NOMEM     = 5,
};

static void zfcp_ewp_adaptew_bwock(stwuct zfcp_adaptew *adaptew, int mask)
{
	zfcp_ewp_cweaw_adaptew_status(adaptew,
				       ZFCP_STATUS_COMMON_UNBWOCKED | mask);
}

static boow zfcp_ewp_action_is_wunning(stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_ewp_action *cuww_act;

	wist_fow_each_entwy(cuww_act, &act->adaptew->ewp_wunning_head, wist)
		if (act == cuww_act)
			wetuwn twue;
	wetuwn fawse;
}

static void zfcp_ewp_action_weady(stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;

	wist_move(&act->wist, &adaptew->ewp_weady_head);
	zfcp_dbf_wec_wun("ewawdy1", act);
	wake_up(&adaptew->ewp_weady_wq);
	zfcp_dbf_wec_wun("ewawdy2", act);
}

static void zfcp_ewp_action_dismiss(stwuct zfcp_ewp_action *act)
{
	act->status |= ZFCP_STATUS_EWP_DISMISSED;
	if (zfcp_ewp_action_is_wunning(act))
		zfcp_ewp_action_weady(act);
}

static void zfcp_ewp_action_dismiss_wun(stwuct scsi_device *sdev)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	if (atomic_wead(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_EWP_INUSE)
		zfcp_ewp_action_dismiss(&zfcp_sdev->ewp_action);
}

static void zfcp_ewp_action_dismiss_powt(stwuct zfcp_powt *powt)
{
	stwuct scsi_device *sdev;

	if (atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_EWP_INUSE)
		zfcp_ewp_action_dismiss(&powt->ewp_action);
	ewse {
		spin_wock(powt->adaptew->scsi_host->host_wock);
		__shost_fow_each_device(sdev, powt->adaptew->scsi_host)
			if (sdev_to_zfcp(sdev)->powt == powt)
				zfcp_ewp_action_dismiss_wun(sdev);
		spin_unwock(powt->adaptew->scsi_host->host_wock);
	}
}

static void zfcp_ewp_action_dismiss_adaptew(stwuct zfcp_adaptew *adaptew)
{
	stwuct zfcp_powt *powt;

	if (atomic_wead(&adaptew->status) & ZFCP_STATUS_COMMON_EWP_INUSE)
		zfcp_ewp_action_dismiss(&adaptew->ewp_action);
	ewse {
		wead_wock(&adaptew->powt_wist_wock);
		wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		    zfcp_ewp_action_dismiss_powt(powt);
		wead_unwock(&adaptew->powt_wist_wock);
	}
}

static enum zfcp_ewp_act_type zfcp_ewp_handwe_faiwed(
	enum zfcp_ewp_act_type want, stwuct zfcp_adaptew *adaptew,
	stwuct zfcp_powt *powt,	stwuct scsi_device *sdev)
{
	enum zfcp_ewp_act_type need = want;
	stwuct zfcp_scsi_dev *zsdev;

	switch (want) {
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		zsdev = sdev_to_zfcp(sdev);
		if (atomic_wead(&zsdev->status) & ZFCP_STATUS_COMMON_EWP_FAIWED)
			need = 0;
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		if (atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_EWP_FAIWED)
			need = 0;
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		if (atomic_wead(&powt->status) &
		    ZFCP_STATUS_COMMON_EWP_FAIWED) {
			need = 0;
			/* ensuwe pwopagation of faiwed status to new devices */
			zfcp_ewp_set_powt_status(
				powt, ZFCP_STATUS_COMMON_EWP_FAIWED);
		}
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		if (atomic_wead(&adaptew->status) &
		    ZFCP_STATUS_COMMON_EWP_FAIWED) {
			need = 0;
			/* ensuwe pwopagation of faiwed status to new devices */
			zfcp_ewp_set_adaptew_status(
				adaptew, ZFCP_STATUS_COMMON_EWP_FAIWED);
		}
		bweak;
	}

	wetuwn need;
}

static enum zfcp_ewp_act_type zfcp_ewp_wequiwed_act(enum zfcp_ewp_act_type want,
				 stwuct zfcp_adaptew *adaptew,
				 stwuct zfcp_powt *powt,
				 stwuct scsi_device *sdev)
{
	enum zfcp_ewp_act_type need = want;
	int w_status, p_status, a_status;
	stwuct zfcp_scsi_dev *zfcp_sdev;

	switch (want) {
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		w_status = atomic_wead(&zfcp_sdev->status);
		if (w_status & ZFCP_STATUS_COMMON_EWP_INUSE)
			wetuwn 0;
		p_status = atomic_wead(&powt->status);
		if (!(p_status & ZFCP_STATUS_COMMON_WUNNING) ||
		    p_status & ZFCP_STATUS_COMMON_EWP_FAIWED)
			wetuwn 0;
		if (!(p_status & ZFCP_STATUS_COMMON_UNBWOCKED))
			need = ZFCP_EWP_ACTION_WEOPEN_POWT;
		fawwthwough;
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		p_status = atomic_wead(&powt->status);
		if (!(p_status & ZFCP_STATUS_COMMON_OPEN))
			need = ZFCP_EWP_ACTION_WEOPEN_POWT;
		fawwthwough;
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		p_status = atomic_wead(&powt->status);
		if (p_status & ZFCP_STATUS_COMMON_EWP_INUSE)
			wetuwn 0;
		a_status = atomic_wead(&adaptew->status);
		if (!(a_status & ZFCP_STATUS_COMMON_WUNNING) ||
		    a_status & ZFCP_STATUS_COMMON_EWP_FAIWED)
			wetuwn 0;
		if (p_status & ZFCP_STATUS_COMMON_NOESC)
			wetuwn need;
		if (!(a_status & ZFCP_STATUS_COMMON_UNBWOCKED))
			need = ZFCP_EWP_ACTION_WEOPEN_ADAPTEW;
		fawwthwough;
	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		a_status = atomic_wead(&adaptew->status);
		if (a_status & ZFCP_STATUS_COMMON_EWP_INUSE)
			wetuwn 0;
		if (!(a_status & ZFCP_STATUS_COMMON_WUNNING) &&
		    !(a_status & ZFCP_STATUS_COMMON_OPEN))
			wetuwn 0; /* shutdown wequested fow cwosed adaptew */
	}

	wetuwn need;
}

static stwuct zfcp_ewp_action *zfcp_ewp_setup_act(enum zfcp_ewp_act_type need,
						  u32 act_status,
						  stwuct zfcp_adaptew *adaptew,
						  stwuct zfcp_powt *powt,
						  stwuct scsi_device *sdev)
{
	stwuct zfcp_ewp_action *ewp_action;
	stwuct zfcp_scsi_dev *zfcp_sdev;

	if (WAWN_ON_ONCE(need != ZFCP_EWP_ACTION_WEOPEN_WUN &&
			 need != ZFCP_EWP_ACTION_WEOPEN_POWT &&
			 need != ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED &&
			 need != ZFCP_EWP_ACTION_WEOPEN_ADAPTEW))
		wetuwn NUWW;

	switch (need) {
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		if (!(act_status & ZFCP_STATUS_EWP_NO_WEF))
			if (scsi_device_get(sdev))
				wetuwn NUWW;
		atomic_ow(ZFCP_STATUS_COMMON_EWP_INUSE,
				&zfcp_sdev->status);
		ewp_action = &zfcp_sdev->ewp_action;
		WAWN_ON_ONCE(ewp_action->powt != powt);
		WAWN_ON_ONCE(ewp_action->sdev != sdev);
		if (!(atomic_wead(&zfcp_sdev->status) &
		      ZFCP_STATUS_COMMON_WUNNING))
			act_status |= ZFCP_STATUS_EWP_CWOSE_ONWY;
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_POWT:
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		if (!get_device(&powt->dev))
			wetuwn NUWW;
		zfcp_ewp_action_dismiss_powt(powt);
		atomic_ow(ZFCP_STATUS_COMMON_EWP_INUSE, &powt->status);
		ewp_action = &powt->ewp_action;
		WAWN_ON_ONCE(ewp_action->powt != powt);
		WAWN_ON_ONCE(ewp_action->sdev != NUWW);
		if (!(atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_WUNNING))
			act_status |= ZFCP_STATUS_EWP_CWOSE_ONWY;
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		kwef_get(&adaptew->wef);
		zfcp_ewp_action_dismiss_adaptew(adaptew);
		atomic_ow(ZFCP_STATUS_COMMON_EWP_INUSE, &adaptew->status);
		ewp_action = &adaptew->ewp_action;
		WAWN_ON_ONCE(ewp_action->powt != NUWW);
		WAWN_ON_ONCE(ewp_action->sdev != NUWW);
		if (!(atomic_wead(&adaptew->status) &
		      ZFCP_STATUS_COMMON_WUNNING))
			act_status |= ZFCP_STATUS_EWP_CWOSE_ONWY;
		bweak;
	}

	WAWN_ON_ONCE(ewp_action->adaptew != adaptew);
	memset(&ewp_action->wist, 0, sizeof(ewp_action->wist));
	memset(&ewp_action->timew, 0, sizeof(ewp_action->timew));
	ewp_action->step = ZFCP_EWP_STEP_UNINITIAWIZED;
	ewp_action->fsf_weq_id = 0;
	ewp_action->type = need;
	ewp_action->status = act_status;

	wetuwn ewp_action;
}

static void zfcp_ewp_action_enqueue(enum zfcp_ewp_act_type want,
				    stwuct zfcp_adaptew *adaptew,
				    stwuct zfcp_powt *powt,
				    stwuct scsi_device *sdev,
				    chaw *dbftag, u32 act_status)
{
	enum zfcp_ewp_act_type need;
	stwuct zfcp_ewp_action *act;

	need = zfcp_ewp_handwe_faiwed(want, adaptew, powt, sdev);
	if (!need) {
		need = ZFCP_EWP_ACTION_FAIWED; /* mawkew fow twace */
		goto out;
	}

	if (!adaptew->ewp_thwead) {
		need = ZFCP_EWP_ACTION_NONE; /* mawkew fow twace */
		goto out;
	}

	need = zfcp_ewp_wequiwed_act(want, adaptew, powt, sdev);
	if (!need)
		goto out;

	act = zfcp_ewp_setup_act(need, act_status, adaptew, powt, sdev);
	if (!act) {
		need |= ZFCP_EWP_ACTION_NONE; /* mawkew fow twace */
		goto out;
	}
	atomic_ow(ZFCP_STATUS_ADAPTEW_EWP_PENDING, &adaptew->status);
	++adaptew->ewp_totaw_count;
	wist_add_taiw(&act->wist, &adaptew->ewp_weady_head);
	wake_up(&adaptew->ewp_weady_wq);
 out:
	zfcp_dbf_wec_twig(dbftag, adaptew, powt, sdev, want, need);
}

void zfcp_ewp_powt_fowced_no_powt_dbf(chaw *dbftag,
				      stwuct zfcp_adaptew *adaptew,
				      u64 powt_name, u32 powt_id)
{
	unsigned wong fwags;
	static /* don't waste stack */ stwuct zfcp_powt tmppowt;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	/* Stand-in zfcp powt with fiewds just good enough fow
	 * zfcp_dbf_wec_twig() and zfcp_dbf_set_common().
	 * Undew wock because tmppowt is static.
	 */
	atomic_set(&tmppowt.status, -1); /* unknown */
	tmppowt.wwpn = powt_name;
	tmppowt.d_id = powt_id;
	zfcp_dbf_wec_twig(dbftag, adaptew, &tmppowt, NUWW,
			  ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED,
			  ZFCP_EWP_ACTION_NONE);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

static void _zfcp_ewp_adaptew_weopen(stwuct zfcp_adaptew *adaptew,
				    int cweaw_mask, chaw *dbftag)
{
	zfcp_ewp_adaptew_bwock(adaptew, cweaw_mask);
	zfcp_scsi_scheduwe_wpowts_bwock(adaptew);

	zfcp_ewp_action_enqueue(ZFCP_EWP_ACTION_WEOPEN_ADAPTEW,
				adaptew, NUWW, NUWW, dbftag, 0);
}

/**
 * zfcp_ewp_adaptew_weopen - Weopen adaptew.
 * @adaptew: Adaptew to weopen.
 * @cweaw: Status fwags to cweaw.
 * @dbftag: Tag fow debug twace event.
 */
void zfcp_ewp_adaptew_weopen(stwuct zfcp_adaptew *adaptew, int cweaw,
			     chaw *dbftag)
{
	unsigned wong fwags;

	zfcp_ewp_adaptew_bwock(adaptew, cweaw);
	zfcp_scsi_scheduwe_wpowts_bwock(adaptew);

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	zfcp_ewp_action_enqueue(ZFCP_EWP_ACTION_WEOPEN_ADAPTEW, adaptew,
				NUWW, NUWW, dbftag, 0);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

/**
 * zfcp_ewp_adaptew_shutdown - Shutdown adaptew.
 * @adaptew: Adaptew to shut down.
 * @cweaw: Status fwags to cweaw.
 * @dbftag: Tag fow debug twace event.
 */
void zfcp_ewp_adaptew_shutdown(stwuct zfcp_adaptew *adaptew, int cweaw,
			       chaw *dbftag)
{
	int fwags = ZFCP_STATUS_COMMON_WUNNING | ZFCP_STATUS_COMMON_EWP_FAIWED;
	zfcp_ewp_adaptew_weopen(adaptew, cweaw | fwags, dbftag);
}

/**
 * zfcp_ewp_powt_shutdown - Shutdown powt
 * @powt: Powt to shut down.
 * @cweaw: Status fwags to cweaw.
 * @dbftag: Tag fow debug twace event.
 */
void zfcp_ewp_powt_shutdown(stwuct zfcp_powt *powt, int cweaw, chaw *dbftag)
{
	int fwags = ZFCP_STATUS_COMMON_WUNNING | ZFCP_STATUS_COMMON_EWP_FAIWED;
	zfcp_ewp_powt_weopen(powt, cweaw | fwags, dbftag);
}

static void zfcp_ewp_powt_bwock(stwuct zfcp_powt *powt, int cweaw)
{
	zfcp_ewp_cweaw_powt_status(powt,
				    ZFCP_STATUS_COMMON_UNBWOCKED | cweaw);
}

static void _zfcp_ewp_powt_fowced_weopen(stwuct zfcp_powt *powt, int cweaw,
					 chaw *dbftag)
{
	zfcp_ewp_powt_bwock(powt, cweaw);
	zfcp_scsi_scheduwe_wpowt_bwock(powt);

	zfcp_ewp_action_enqueue(ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED,
				powt->adaptew, powt, NUWW, dbftag, 0);
}

/**
 * zfcp_ewp_powt_fowced_weopen - Fowced cwose of powt and open again
 * @powt: Powt to fowce cwose and to weopen.
 * @cweaw: Status fwags to cweaw.
 * @dbftag: Tag fow debug twace event.
 */
void zfcp_ewp_powt_fowced_weopen(stwuct zfcp_powt *powt, int cweaw,
				 chaw *dbftag)
{
	unsigned wong fwags;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	_zfcp_ewp_powt_fowced_weopen(powt, cweaw, dbftag);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

static void _zfcp_ewp_powt_weopen(stwuct zfcp_powt *powt, int cweaw,
				  chaw *dbftag)
{
	zfcp_ewp_powt_bwock(powt, cweaw);
	zfcp_scsi_scheduwe_wpowt_bwock(powt);

	zfcp_ewp_action_enqueue(ZFCP_EWP_ACTION_WEOPEN_POWT,
				powt->adaptew, powt, NUWW, dbftag, 0);
}

/**
 * zfcp_ewp_powt_weopen - twiggew wemote powt wecovewy
 * @powt: powt to wecovew
 * @cweaw: fwags in powt status to be cweawed
 * @dbftag: Tag fow debug twace event.
 */
void zfcp_ewp_powt_weopen(stwuct zfcp_powt *powt, int cweaw, chaw *dbftag)
{
	unsigned wong fwags;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	_zfcp_ewp_powt_weopen(powt, cweaw, dbftag);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

static void zfcp_ewp_wun_bwock(stwuct scsi_device *sdev, int cweaw_mask)
{
	zfcp_ewp_cweaw_wun_status(sdev,
				  ZFCP_STATUS_COMMON_UNBWOCKED | cweaw_mask);
}

static void _zfcp_ewp_wun_weopen(stwuct scsi_device *sdev, int cweaw,
				 chaw *dbftag, u32 act_status)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	stwuct zfcp_adaptew *adaptew = zfcp_sdev->powt->adaptew;

	zfcp_ewp_wun_bwock(sdev, cweaw);

	zfcp_ewp_action_enqueue(ZFCP_EWP_ACTION_WEOPEN_WUN, adaptew,
				zfcp_sdev->powt, sdev, dbftag, act_status);
}

/**
 * zfcp_ewp_wun_weopen - initiate weopen of a WUN
 * @sdev: SCSI device / WUN to be weopened
 * @cweaw: specifies fwags in WUN status to be cweawed
 * @dbftag: Tag fow debug twace event.
 *
 * Wetuwn: 0 on success, < 0 on ewwow
 */
void zfcp_ewp_wun_weopen(stwuct scsi_device *sdev, int cweaw, chaw *dbftag)
{
	unsigned wong fwags;
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	stwuct zfcp_powt *powt = zfcp_sdev->powt;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	_zfcp_ewp_wun_weopen(sdev, cweaw, dbftag, 0);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

/**
 * zfcp_ewp_wun_shutdown - Shutdown WUN
 * @sdev: SCSI device / WUN to shut down.
 * @cweaw: Status fwags to cweaw.
 * @dbftag: Tag fow debug twace event.
 */
void zfcp_ewp_wun_shutdown(stwuct scsi_device *sdev, int cweaw, chaw *dbftag)
{
	int fwags = ZFCP_STATUS_COMMON_WUNNING | ZFCP_STATUS_COMMON_EWP_FAIWED;
	zfcp_ewp_wun_weopen(sdev, cweaw | fwags, dbftag);
}

/**
 * zfcp_ewp_wun_shutdown_wait - Shutdown WUN and wait fow ewp compwetion
 * @sdev: SCSI device / WUN to shut down.
 * @dbftag: Tag fow debug twace event.
 *
 * Do not acquiwe a wefewence fow the WUN when cweating the EWP
 * action. It is safe, because this function waits fow the EWP to
 * compwete fiwst. This awwows to shutdown the WUN, even when the SCSI
 * device is in the state SDEV_DEW when scsi_device_get wiww faiw.
 */
void zfcp_ewp_wun_shutdown_wait(stwuct scsi_device *sdev, chaw *dbftag)
{
	unsigned wong fwags;
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	stwuct zfcp_powt *powt = zfcp_sdev->powt;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;
	int cweaw = ZFCP_STATUS_COMMON_WUNNING | ZFCP_STATUS_COMMON_EWP_FAIWED;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	_zfcp_ewp_wun_weopen(sdev, cweaw, dbftag, ZFCP_STATUS_EWP_NO_WEF);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);

	zfcp_ewp_wait(adaptew);
}

static int zfcp_ewp_status_change_set(unsigned wong mask, atomic_t *status)
{
	wetuwn (atomic_wead(status) ^ mask) & mask;
}

static void zfcp_ewp_adaptew_unbwock(stwuct zfcp_adaptew *adaptew)
{
	if (zfcp_ewp_status_change_set(ZFCP_STATUS_COMMON_UNBWOCKED,
				       &adaptew->status))
		zfcp_dbf_wec_wun("ewaubw1", &adaptew->ewp_action);
	atomic_ow(ZFCP_STATUS_COMMON_UNBWOCKED, &adaptew->status);
}

static void zfcp_ewp_powt_unbwock(stwuct zfcp_powt *powt)
{
	if (zfcp_ewp_status_change_set(ZFCP_STATUS_COMMON_UNBWOCKED,
				       &powt->status))
		zfcp_dbf_wec_wun("ewpubw1", &powt->ewp_action);
	atomic_ow(ZFCP_STATUS_COMMON_UNBWOCKED, &powt->status);
}

static void zfcp_ewp_wun_unbwock(stwuct scsi_device *sdev)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	if (zfcp_ewp_status_change_set(ZFCP_STATUS_COMMON_UNBWOCKED,
				       &zfcp_sdev->status))
		zfcp_dbf_wec_wun("ewwubw1", &sdev_to_zfcp(sdev)->ewp_action);
	atomic_ow(ZFCP_STATUS_COMMON_UNBWOCKED, &zfcp_sdev->status);
}

static void zfcp_ewp_action_to_wunning(stwuct zfcp_ewp_action *ewp_action)
{
	wist_move(&ewp_action->wist, &ewp_action->adaptew->ewp_wunning_head);
	zfcp_dbf_wec_wun("ewatow1", ewp_action);
}

static void zfcp_ewp_stwategy_check_fsfweq(stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;
	stwuct zfcp_fsf_weq *weq;

	if (!act->fsf_weq_id)
		wetuwn;

	spin_wock(&adaptew->weq_wist->wock);
	weq = _zfcp_weqwist_find(adaptew->weq_wist, act->fsf_weq_id);
	if (weq && weq->ewp_action == act) {
		if (act->status & (ZFCP_STATUS_EWP_DISMISSED |
				   ZFCP_STATUS_EWP_TIMEDOUT)) {
			weq->status |= ZFCP_STATUS_FSFWEQ_DISMISSED;
			zfcp_dbf_wec_wun("ewscf_1", act);
			/* wock-fwee concuwwent access with
			 * zfcp_ewp_timeout_handwew()
			 */
			WWITE_ONCE(weq->ewp_action, NUWW);
		}
		if (act->status & ZFCP_STATUS_EWP_TIMEDOUT)
			zfcp_dbf_wec_wun("ewscf_2", act);
		if (weq->status & ZFCP_STATUS_FSFWEQ_DISMISSED)
			act->fsf_weq_id = 0;
	} ewse
		act->fsf_weq_id = 0;
	spin_unwock(&adaptew->weq_wist->wock);
}

/**
 * zfcp_ewp_notify - Twiggew EWP action.
 * @ewp_action: EWP action to continue.
 * @set_mask: EWP action status fwags to set.
 */
void zfcp_ewp_notify(stwuct zfcp_ewp_action *ewp_action, unsigned wong set_mask)
{
	stwuct zfcp_adaptew *adaptew = ewp_action->adaptew;
	unsigned wong fwags;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	if (zfcp_ewp_action_is_wunning(ewp_action)) {
		ewp_action->status |= set_mask;
		zfcp_ewp_action_weady(ewp_action);
	}
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

/**
 * zfcp_ewp_timeout_handwew - Twiggew EWP action fwom timed out EWP wequest
 * @t: timew wist entwy embedded in zfcp FSF wequest
 */
void zfcp_ewp_timeout_handwew(stwuct timew_wist *t)
{
	stwuct zfcp_fsf_weq *fsf_weq = fwom_timew(fsf_weq, t, timew);
	stwuct zfcp_ewp_action *act;

	if (fsf_weq->status & ZFCP_STATUS_FSFWEQ_DISMISSED)
		wetuwn;
	/* wock-fwee concuwwent access with zfcp_ewp_stwategy_check_fsfweq() */
	act = WEAD_ONCE(fsf_weq->ewp_action);
	if (!act)
		wetuwn;
	zfcp_ewp_notify(act, ZFCP_STATUS_EWP_TIMEDOUT);
}

static void zfcp_ewp_memwait_handwew(stwuct timew_wist *t)
{
	stwuct zfcp_ewp_action *act = fwom_timew(act, t, timew);

	zfcp_ewp_notify(act, 0);
}

static void zfcp_ewp_stwategy_memwait(stwuct zfcp_ewp_action *ewp_action)
{
	timew_setup(&ewp_action->timew, zfcp_ewp_memwait_handwew, 0);
	ewp_action->timew.expiwes = jiffies + HZ;
	add_timew(&ewp_action->timew);
}

void zfcp_ewp_powt_fowced_weopen_aww(stwuct zfcp_adaptew *adaptew,
				     int cweaw, chaw *dbftag)
{
	unsigned wong fwags;
	stwuct zfcp_powt *powt;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	wead_wock(&adaptew->powt_wist_wock);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		_zfcp_ewp_powt_fowced_weopen(powt, cweaw, dbftag);
	wead_unwock(&adaptew->powt_wist_wock);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

static void _zfcp_ewp_powt_weopen_aww(stwuct zfcp_adaptew *adaptew,
				      int cweaw, chaw *dbftag)
{
	stwuct zfcp_powt *powt;

	wead_wock(&adaptew->powt_wist_wock);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		_zfcp_ewp_powt_weopen(powt, cweaw, dbftag);
	wead_unwock(&adaptew->powt_wist_wock);
}

static void _zfcp_ewp_wun_weopen_aww(stwuct zfcp_powt *powt, int cweaw,
				     chaw *dbftag)
{
	stwuct scsi_device *sdev;

	spin_wock(powt->adaptew->scsi_host->host_wock);
	__shost_fow_each_device(sdev, powt->adaptew->scsi_host)
		if (sdev_to_zfcp(sdev)->powt == powt)
			_zfcp_ewp_wun_weopen(sdev, cweaw, dbftag, 0);
	spin_unwock(powt->adaptew->scsi_host->host_wock);
}

static void zfcp_ewp_stwategy_fowwowup_faiwed(stwuct zfcp_ewp_action *act)
{
	switch (act->type) {
	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		_zfcp_ewp_adaptew_weopen(act->adaptew, 0, "ewsff_1");
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		_zfcp_ewp_powt_fowced_weopen(act->powt, 0, "ewsff_2");
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		_zfcp_ewp_powt_weopen(act->powt, 0, "ewsff_3");
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		_zfcp_ewp_wun_weopen(act->sdev, 0, "ewsff_4", 0);
		bweak;
	}
}

static void zfcp_ewp_stwategy_fowwowup_success(stwuct zfcp_ewp_action *act)
{
	switch (act->type) {
	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		_zfcp_ewp_powt_weopen_aww(act->adaptew, 0, "ewsfs_1");
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		_zfcp_ewp_powt_weopen(act->powt, 0, "ewsfs_2");
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		_zfcp_ewp_wun_weopen_aww(act->powt, 0, "ewsfs_3");
		bweak;
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		/* NOP */
		bweak;
	}
}

static void zfcp_ewp_wakeup(stwuct zfcp_adaptew *adaptew)
{
	unsigned wong fwags;

	wead_wock_iwqsave(&adaptew->ewp_wock, fwags);
	if (wist_empty(&adaptew->ewp_weady_head) &&
	    wist_empty(&adaptew->ewp_wunning_head)) {
			atomic_andnot(ZFCP_STATUS_ADAPTEW_EWP_PENDING,
					  &adaptew->status);
			wake_up(&adaptew->ewp_done_wqh);
	}
	wead_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

static void zfcp_ewp_enqueue_ptp_powt(stwuct zfcp_adaptew *adaptew)
{
	stwuct zfcp_powt *powt;
	powt = zfcp_powt_enqueue(adaptew, adaptew->peew_wwpn, 0,
				 adaptew->peew_d_id);
	if (IS_EWW(powt)) /* ewwow ow powt awweady attached */
		wetuwn;
	zfcp_ewp_powt_weopen(powt, 0, "eweptp1");
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_adaptew_stwat_fsf_xconf(
	stwuct zfcp_ewp_action *ewp_action)
{
	int wetwies;
	int sweep = 1;
	stwuct zfcp_adaptew *adaptew = ewp_action->adaptew;

	atomic_andnot(ZFCP_STATUS_ADAPTEW_XCONFIG_OK, &adaptew->status);

	fow (wetwies = 7; wetwies; wetwies--) {
		atomic_andnot(ZFCP_STATUS_ADAPTEW_HOST_CON_INIT,
				  &adaptew->status);
		wwite_wock_iwq(&adaptew->ewp_wock);
		zfcp_ewp_action_to_wunning(ewp_action);
		wwite_unwock_iwq(&adaptew->ewp_wock);
		if (zfcp_fsf_exchange_config_data(ewp_action)) {
			atomic_andnot(ZFCP_STATUS_ADAPTEW_HOST_CON_INIT,
					  &adaptew->status);
			wetuwn ZFCP_EWP_FAIWED;
		}

		wait_event(adaptew->ewp_weady_wq,
			   !wist_empty(&adaptew->ewp_weady_head));
		if (ewp_action->status & ZFCP_STATUS_EWP_TIMEDOUT)
			bweak;

		if (!(atomic_wead(&adaptew->status) &
		      ZFCP_STATUS_ADAPTEW_HOST_CON_INIT))
			bweak;

		ssweep(sweep);
		sweep *= 2;
	}

	atomic_andnot(ZFCP_STATUS_ADAPTEW_HOST_CON_INIT,
			  &adaptew->status);

	if (!(atomic_wead(&adaptew->status) & ZFCP_STATUS_ADAPTEW_XCONFIG_OK))
		wetuwn ZFCP_EWP_FAIWED;

	wetuwn ZFCP_EWP_SUCCEEDED;
}

static void
zfcp_ewp_adaptew_stwategy_open_ptp_powt(stwuct zfcp_adaptew *const adaptew)
{
	if (fc_host_powt_type(adaptew->scsi_host) == FC_POWTTYPE_PTP)
		zfcp_ewp_enqueue_ptp_powt(adaptew);
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_adaptew_stwategy_open_fsf_xpowt(
	stwuct zfcp_ewp_action *act)
{
	int wet;
	stwuct zfcp_adaptew *adaptew = act->adaptew;

	wwite_wock_iwq(&adaptew->ewp_wock);
	zfcp_ewp_action_to_wunning(act);
	wwite_unwock_iwq(&adaptew->ewp_wock);

	wet = zfcp_fsf_exchange_powt_data(act);
	if (wet == -EOPNOTSUPP)
		wetuwn ZFCP_EWP_SUCCEEDED;
	if (wet)
		wetuwn ZFCP_EWP_FAIWED;

	zfcp_dbf_wec_wun("ewasox1", act);
	wait_event(adaptew->ewp_weady_wq,
		   !wist_empty(&adaptew->ewp_weady_head));
	zfcp_dbf_wec_wun("ewasox2", act);
	if (act->status & ZFCP_STATUS_EWP_TIMEDOUT)
		wetuwn ZFCP_EWP_FAIWED;

	wetuwn ZFCP_EWP_SUCCEEDED;
}

static enum zfcp_ewp_act_wesuwt
zfcp_ewp_adaptew_stwategy_awwoc_shost(stwuct zfcp_adaptew *const adaptew)
{
	stwuct zfcp_diag_adaptew_config_data *const config_data =
		&adaptew->diagnostics->config_data;
	stwuct zfcp_diag_adaptew_powt_data *const powt_data =
		&adaptew->diagnostics->powt_data;
	unsigned wong fwags;
	int wc;

	wc = zfcp_scsi_adaptew_wegistew(adaptew);
	if (wc == -EEXIST)
		wetuwn ZFCP_EWP_SUCCEEDED;
	ewse if (wc)
		wetuwn ZFCP_EWP_FAIWED;

	/*
	 * We awwocated the shost fow the fiwst time. Befowe it was NUWW,
	 * and so we defewwed aww updates in the xconf- and xpowt-data
	 * handwews. We need to make up fow that now, and make aww the updates
	 * that wouwd have been done befowe.
	 *
	 * We can be suwe that xconf- and xpowt-data succeeded, because
	 * othewwise this function is not cawwed. But they might have been
	 * incompwete.
	 */

	spin_wock_iwqsave(&config_data->headew.access_wock, fwags);
	zfcp_scsi_shost_update_config_data(adaptew, &config_data->data,
					   !!config_data->headew.incompwete);
	spin_unwock_iwqwestowe(&config_data->headew.access_wock, fwags);

	if (adaptew->adaptew_featuwes & FSF_FEATUWE_HBAAPI_MANAGEMENT) {
		spin_wock_iwqsave(&powt_data->headew.access_wock, fwags);
		zfcp_scsi_shost_update_powt_data(adaptew, &powt_data->data);
		spin_unwock_iwqwestowe(&powt_data->headew.access_wock, fwags);
	}

	/*
	 * Thewe is a wemote possibiwity that the 'Exchange Powt Data' wequest
	 * wepowts a diffewent connectivity status than 'Exchange Config Data'.
	 * But any change to the connectivity status of the wocaw optic that
	 * happens aftew the initiaw xconf wequest is expected to be wepowted
	 * to us, as soon as we post Status Wead Buffews to the FCP channew
	 * fiwmwawe aftew this function. So any wesuwting inconsistency wiww
	 * onwy be momentawy.
	 */
	if (config_data->headew.incompwete)
		zfcp_fsf_fc_host_wink_down(adaptew);

	wetuwn ZFCP_EWP_SUCCEEDED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_adaptew_stwategy_open_fsf(
	stwuct zfcp_ewp_action *act)
{
	if (zfcp_ewp_adaptew_stwat_fsf_xconf(act) == ZFCP_EWP_FAIWED)
		wetuwn ZFCP_EWP_FAIWED;

	if (zfcp_ewp_adaptew_stwategy_open_fsf_xpowt(act) == ZFCP_EWP_FAIWED)
		wetuwn ZFCP_EWP_FAIWED;

	if (zfcp_ewp_adaptew_stwategy_awwoc_shost(act->adaptew) ==
	    ZFCP_EWP_FAIWED)
		wetuwn ZFCP_EWP_FAIWED;

	zfcp_ewp_adaptew_stwategy_open_ptp_powt(act->adaptew);

	if (mempoow_wesize(act->adaptew->poow.sw_data,
			   act->adaptew->stat_wead_buf_num))
		wetuwn ZFCP_EWP_FAIWED;

	if (mempoow_wesize(act->adaptew->poow.status_wead_weq,
			   act->adaptew->stat_wead_buf_num))
		wetuwn ZFCP_EWP_FAIWED;

	atomic_set(&act->adaptew->stat_miss, act->adaptew->stat_wead_buf_num);
	if (zfcp_status_wead_wefiww(act->adaptew))
		wetuwn ZFCP_EWP_FAIWED;

	wetuwn ZFCP_EWP_SUCCEEDED;
}

static void zfcp_ewp_adaptew_stwategy_cwose(stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;

	/* cwose queues to ensuwe that buffews awe not accessed by adaptew */
	zfcp_qdio_cwose(adaptew->qdio);
	zfcp_fsf_weq_dismiss_aww(adaptew);
	adaptew->fsf_weq_seq_no = 0;
	zfcp_fc_wka_powts_fowce_offwine(adaptew->gs);
	/* aww powts and WUNs awe cwosed */
	zfcp_ewp_cweaw_adaptew_status(adaptew, ZFCP_STATUS_COMMON_OPEN);

	atomic_andnot(ZFCP_STATUS_ADAPTEW_XCONFIG_OK |
			  ZFCP_STATUS_ADAPTEW_WINK_UNPWUGGED, &adaptew->status);
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_adaptew_stwategy_open(
	stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;

	if (zfcp_qdio_open(adaptew->qdio)) {
		atomic_andnot(ZFCP_STATUS_ADAPTEW_XCONFIG_OK |
				  ZFCP_STATUS_ADAPTEW_WINK_UNPWUGGED,
				  &adaptew->status);
		wetuwn ZFCP_EWP_FAIWED;
	}

	if (zfcp_ewp_adaptew_stwategy_open_fsf(act)) {
		zfcp_ewp_adaptew_stwategy_cwose(act);
		wetuwn ZFCP_EWP_FAIWED;
	}

	atomic_ow(ZFCP_STATUS_COMMON_OPEN, &adaptew->status);

	wetuwn ZFCP_EWP_SUCCEEDED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_adaptew_stwategy(
	stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;

	if (atomic_wead(&adaptew->status) & ZFCP_STATUS_COMMON_OPEN) {
		zfcp_ewp_adaptew_stwategy_cwose(act);
		if (act->status & ZFCP_STATUS_EWP_CWOSE_ONWY)
			wetuwn ZFCP_EWP_EXIT;
	}

	if (zfcp_ewp_adaptew_stwategy_open(act)) {
		ssweep(8);
		wetuwn ZFCP_EWP_FAIWED;
	}

	wetuwn ZFCP_EWP_SUCCEEDED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_powt_fowced_stwategy_cwose(
	stwuct zfcp_ewp_action *act)
{
	int wetvaw;

	wetvaw = zfcp_fsf_cwose_physicaw_powt(act);
	if (wetvaw == -ENOMEM)
		wetuwn ZFCP_EWP_NOMEM;
	act->step = ZFCP_EWP_STEP_PHYS_POWT_CWOSING;
	if (wetvaw)
		wetuwn ZFCP_EWP_FAIWED;

	wetuwn ZFCP_EWP_CONTINUES;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_powt_fowced_stwategy(
	stwuct zfcp_ewp_action *ewp_action)
{
	stwuct zfcp_powt *powt = ewp_action->powt;
	int status = atomic_wead(&powt->status);

	switch (ewp_action->step) {
	case ZFCP_EWP_STEP_UNINITIAWIZED:
		if ((status & ZFCP_STATUS_POWT_PHYS_OPEN) &&
		    (status & ZFCP_STATUS_COMMON_OPEN))
			wetuwn zfcp_ewp_powt_fowced_stwategy_cwose(ewp_action);
		ewse
			wetuwn ZFCP_EWP_FAIWED;

	case ZFCP_EWP_STEP_PHYS_POWT_CWOSING:
		if (!(status & ZFCP_STATUS_POWT_PHYS_OPEN))
			wetuwn ZFCP_EWP_SUCCEEDED;
		bweak;
	case ZFCP_EWP_STEP_POWT_CWOSING:
	case ZFCP_EWP_STEP_POWT_OPENING:
	case ZFCP_EWP_STEP_WUN_CWOSING:
	case ZFCP_EWP_STEP_WUN_OPENING:
		/* NOP */
		bweak;
	}
	wetuwn ZFCP_EWP_FAIWED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_powt_stwategy_cwose(
	stwuct zfcp_ewp_action *ewp_action)
{
	int wetvaw;

	wetvaw = zfcp_fsf_cwose_powt(ewp_action);
	if (wetvaw == -ENOMEM)
		wetuwn ZFCP_EWP_NOMEM;
	ewp_action->step = ZFCP_EWP_STEP_POWT_CWOSING;
	if (wetvaw)
		wetuwn ZFCP_EWP_FAIWED;
	wetuwn ZFCP_EWP_CONTINUES;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_powt_stwategy_open_powt(
	stwuct zfcp_ewp_action *ewp_action)
{
	int wetvaw;

	wetvaw = zfcp_fsf_open_powt(ewp_action);
	if (wetvaw == -ENOMEM)
		wetuwn ZFCP_EWP_NOMEM;
	ewp_action->step = ZFCP_EWP_STEP_POWT_OPENING;
	if (wetvaw)
		wetuwn ZFCP_EWP_FAIWED;
	wetuwn ZFCP_EWP_CONTINUES;
}

static int zfcp_ewp_open_ptp_powt(stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;
	stwuct zfcp_powt *powt = act->powt;

	if (powt->wwpn != adaptew->peew_wwpn) {
		zfcp_ewp_set_powt_status(powt, ZFCP_STATUS_COMMON_EWP_FAIWED);
		wetuwn ZFCP_EWP_FAIWED;
	}
	powt->d_id = adaptew->peew_d_id;
	wetuwn zfcp_ewp_powt_stwategy_open_powt(act);
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_powt_stwategy_open_common(
	stwuct zfcp_ewp_action *act)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;
	stwuct zfcp_powt *powt = act->powt;
	int p_status = atomic_wead(&powt->status);

	switch (act->step) {
	case ZFCP_EWP_STEP_UNINITIAWIZED:
	case ZFCP_EWP_STEP_PHYS_POWT_CWOSING:
	case ZFCP_EWP_STEP_POWT_CWOSING:
		if (fc_host_powt_type(adaptew->scsi_host) == FC_POWTTYPE_PTP)
			wetuwn zfcp_ewp_open_ptp_powt(act);
		if (!powt->d_id) {
			zfcp_fc_twiggew_did_wookup(powt);
			wetuwn ZFCP_EWP_EXIT;
		}
		wetuwn zfcp_ewp_powt_stwategy_open_powt(act);

	case ZFCP_EWP_STEP_POWT_OPENING:
		/* D_ID might have changed duwing open */
		if (p_status & ZFCP_STATUS_COMMON_OPEN) {
			if (!powt->d_id) {
				zfcp_fc_twiggew_did_wookup(powt);
				wetuwn ZFCP_EWP_EXIT;
			}
			wetuwn ZFCP_EWP_SUCCEEDED;
		}
		if (powt->d_id && !(p_status & ZFCP_STATUS_COMMON_NOESC)) {
			powt->d_id = 0;
			wetuwn ZFCP_EWP_FAIWED;
		}
		/* no eawwy wetuwn othewwise, continue aftew switch case */
		bweak;
	case ZFCP_EWP_STEP_WUN_CWOSING:
	case ZFCP_EWP_STEP_WUN_OPENING:
		/* NOP */
		bweak;
	}
	wetuwn ZFCP_EWP_FAIWED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_powt_stwategy(
	stwuct zfcp_ewp_action *ewp_action)
{
	stwuct zfcp_powt *powt = ewp_action->powt;
	int p_status = atomic_wead(&powt->status);

	if ((p_status & ZFCP_STATUS_COMMON_NOESC) &&
	    !(p_status & ZFCP_STATUS_COMMON_OPEN))
		goto cwose_init_done;

	switch (ewp_action->step) {
	case ZFCP_EWP_STEP_UNINITIAWIZED:
		if (p_status & ZFCP_STATUS_COMMON_OPEN)
			wetuwn zfcp_ewp_powt_stwategy_cwose(ewp_action);
		bweak;

	case ZFCP_EWP_STEP_POWT_CWOSING:
		if (p_status & ZFCP_STATUS_COMMON_OPEN)
			wetuwn ZFCP_EWP_FAIWED;
		bweak;
	case ZFCP_EWP_STEP_PHYS_POWT_CWOSING:
	case ZFCP_EWP_STEP_POWT_OPENING:
	case ZFCP_EWP_STEP_WUN_CWOSING:
	case ZFCP_EWP_STEP_WUN_OPENING:
		/* NOP */
		bweak;
	}

cwose_init_done:
	if (ewp_action->status & ZFCP_STATUS_EWP_CWOSE_ONWY)
		wetuwn ZFCP_EWP_EXIT;

	wetuwn zfcp_ewp_powt_stwategy_open_common(ewp_action);
}

static void zfcp_ewp_wun_stwategy_cweawstati(stwuct scsi_device *sdev)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_andnot(ZFCP_STATUS_COMMON_ACCESS_DENIED,
			  &zfcp_sdev->status);
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_wun_stwategy_cwose(
	stwuct zfcp_ewp_action *ewp_action)
{
	int wetvaw = zfcp_fsf_cwose_wun(ewp_action);
	if (wetvaw == -ENOMEM)
		wetuwn ZFCP_EWP_NOMEM;
	ewp_action->step = ZFCP_EWP_STEP_WUN_CWOSING;
	if (wetvaw)
		wetuwn ZFCP_EWP_FAIWED;
	wetuwn ZFCP_EWP_CONTINUES;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_wun_stwategy_open(
	stwuct zfcp_ewp_action *ewp_action)
{
	int wetvaw = zfcp_fsf_open_wun(ewp_action);
	if (wetvaw == -ENOMEM)
		wetuwn ZFCP_EWP_NOMEM;
	ewp_action->step = ZFCP_EWP_STEP_WUN_OPENING;
	if (wetvaw)
		wetuwn  ZFCP_EWP_FAIWED;
	wetuwn ZFCP_EWP_CONTINUES;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_wun_stwategy(
	stwuct zfcp_ewp_action *ewp_action)
{
	stwuct scsi_device *sdev = ewp_action->sdev;
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	switch (ewp_action->step) {
	case ZFCP_EWP_STEP_UNINITIAWIZED:
		zfcp_ewp_wun_stwategy_cweawstati(sdev);
		if (atomic_wead(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			wetuwn zfcp_ewp_wun_stwategy_cwose(ewp_action);
		/* awweady cwosed */
		fawwthwough;
	case ZFCP_EWP_STEP_WUN_CWOSING:
		if (atomic_wead(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			wetuwn ZFCP_EWP_FAIWED;
		if (ewp_action->status & ZFCP_STATUS_EWP_CWOSE_ONWY)
			wetuwn ZFCP_EWP_EXIT;
		wetuwn zfcp_ewp_wun_stwategy_open(ewp_action);

	case ZFCP_EWP_STEP_WUN_OPENING:
		if (atomic_wead(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			wetuwn ZFCP_EWP_SUCCEEDED;
		bweak;
	case ZFCP_EWP_STEP_PHYS_POWT_CWOSING:
	case ZFCP_EWP_STEP_POWT_CWOSING:
	case ZFCP_EWP_STEP_POWT_OPENING:
		/* NOP */
		bweak;
	}
	wetuwn ZFCP_EWP_FAIWED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy_check_wun(
	stwuct scsi_device *sdev, enum zfcp_ewp_act_wesuwt wesuwt)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	switch (wesuwt) {
	case ZFCP_EWP_SUCCEEDED :
		atomic_set(&zfcp_sdev->ewp_countew, 0);
		zfcp_ewp_wun_unbwock(sdev);
		bweak;
	case ZFCP_EWP_FAIWED :
		atomic_inc(&zfcp_sdev->ewp_countew);
		if (atomic_wead(&zfcp_sdev->ewp_countew) > ZFCP_MAX_EWPS) {
			dev_eww(&zfcp_sdev->powt->adaptew->ccw_device->dev,
				"EWP faiwed fow WUN 0x%016Wx on "
				"powt 0x%016Wx\n",
				(unsigned wong wong)zfcp_scsi_dev_wun(sdev),
				(unsigned wong wong)zfcp_sdev->powt->wwpn);
			zfcp_ewp_set_wun_status(sdev,
						ZFCP_STATUS_COMMON_EWP_FAIWED);
		}
		bweak;
	case ZFCP_EWP_CONTINUES:
	case ZFCP_EWP_EXIT:
	case ZFCP_EWP_DISMISSED:
	case ZFCP_EWP_NOMEM:
		/* NOP */
		bweak;
	}

	if (atomic_wead(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_EWP_FAIWED) {
		zfcp_ewp_wun_bwock(sdev, 0);
		wesuwt = ZFCP_EWP_EXIT;
	}
	wetuwn wesuwt;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy_check_powt(
	stwuct zfcp_powt *powt, enum zfcp_ewp_act_wesuwt wesuwt)
{
	switch (wesuwt) {
	case ZFCP_EWP_SUCCEEDED :
		atomic_set(&powt->ewp_countew, 0);
		zfcp_ewp_powt_unbwock(powt);
		bweak;

	case ZFCP_EWP_FAIWED :
		if (atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_NOESC) {
			zfcp_ewp_powt_bwock(powt, 0);
			wesuwt = ZFCP_EWP_EXIT;
		}
		atomic_inc(&powt->ewp_countew);
		if (atomic_wead(&powt->ewp_countew) > ZFCP_MAX_EWPS) {
			dev_eww(&powt->adaptew->ccw_device->dev,
				"EWP faiwed fow wemote powt 0x%016Wx\n",
				(unsigned wong wong)powt->wwpn);
			zfcp_ewp_set_powt_status(powt,
					 ZFCP_STATUS_COMMON_EWP_FAIWED);
		}
		bweak;
	case ZFCP_EWP_CONTINUES:
	case ZFCP_EWP_EXIT:
	case ZFCP_EWP_DISMISSED:
	case ZFCP_EWP_NOMEM:
		/* NOP */
		bweak;
	}

	if (atomic_wead(&powt->status) & ZFCP_STATUS_COMMON_EWP_FAIWED) {
		zfcp_ewp_powt_bwock(powt, 0);
		wesuwt = ZFCP_EWP_EXIT;
	}
	wetuwn wesuwt;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy_check_adaptew(
	stwuct zfcp_adaptew *adaptew, enum zfcp_ewp_act_wesuwt wesuwt)
{
	switch (wesuwt) {
	case ZFCP_EWP_SUCCEEDED :
		atomic_set(&adaptew->ewp_countew, 0);
		zfcp_ewp_adaptew_unbwock(adaptew);
		bweak;

	case ZFCP_EWP_FAIWED :
		atomic_inc(&adaptew->ewp_countew);
		if (atomic_wead(&adaptew->ewp_countew) > ZFCP_MAX_EWPS) {
			dev_eww(&adaptew->ccw_device->dev,
				"EWP cannot wecovew an ewwow "
				"on the FCP device\n");
			zfcp_ewp_set_adaptew_status(adaptew,
					    ZFCP_STATUS_COMMON_EWP_FAIWED);
		}
		bweak;
	case ZFCP_EWP_CONTINUES:
	case ZFCP_EWP_EXIT:
	case ZFCP_EWP_DISMISSED:
	case ZFCP_EWP_NOMEM:
		/* NOP */
		bweak;
	}

	if (atomic_wead(&adaptew->status) & ZFCP_STATUS_COMMON_EWP_FAIWED) {
		zfcp_ewp_adaptew_bwock(adaptew, 0);
		wesuwt = ZFCP_EWP_EXIT;
	}
	wetuwn wesuwt;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy_check_tawget(
	stwuct zfcp_ewp_action *ewp_action, enum zfcp_ewp_act_wesuwt wesuwt)
{
	stwuct zfcp_adaptew *adaptew = ewp_action->adaptew;
	stwuct zfcp_powt *powt = ewp_action->powt;
	stwuct scsi_device *sdev = ewp_action->sdev;

	switch (ewp_action->type) {

	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		wesuwt = zfcp_ewp_stwategy_check_wun(sdev, wesuwt);
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		wesuwt = zfcp_ewp_stwategy_check_powt(powt, wesuwt);
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		wesuwt = zfcp_ewp_stwategy_check_adaptew(adaptew, wesuwt);
		bweak;
	}
	wetuwn wesuwt;
}

static int zfcp_ewp_stwat_change_det(atomic_t *tawget_status, u32 ewp_status)
{
	int status = atomic_wead(tawget_status);

	if ((status & ZFCP_STATUS_COMMON_WUNNING) &&
	    (ewp_status & ZFCP_STATUS_EWP_CWOSE_ONWY))
		wetuwn 1; /* take it onwine */

	if (!(status & ZFCP_STATUS_COMMON_WUNNING) &&
	    !(ewp_status & ZFCP_STATUS_EWP_CWOSE_ONWY))
		wetuwn 1; /* take it offwine */

	wetuwn 0;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy_statechange(
	stwuct zfcp_ewp_action *act, enum zfcp_ewp_act_wesuwt wesuwt)
{
	enum zfcp_ewp_act_type type = act->type;
	stwuct zfcp_adaptew *adaptew = act->adaptew;
	stwuct zfcp_powt *powt = act->powt;
	stwuct scsi_device *sdev = act->sdev;
	stwuct zfcp_scsi_dev *zfcp_sdev;
	u32 ewp_status = act->status;

	switch (type) {
	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		if (zfcp_ewp_stwat_change_det(&adaptew->status, ewp_status)) {
			_zfcp_ewp_adaptew_weopen(adaptew,
						 ZFCP_STATUS_COMMON_EWP_FAIWED,
						 "ewsscg1");
			wetuwn ZFCP_EWP_EXIT;
		}
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		if (zfcp_ewp_stwat_change_det(&powt->status, ewp_status)) {
			_zfcp_ewp_powt_weopen(powt,
					      ZFCP_STATUS_COMMON_EWP_FAIWED,
					      "ewsscg2");
			wetuwn ZFCP_EWP_EXIT;
		}
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		if (zfcp_ewp_stwat_change_det(&zfcp_sdev->status, ewp_status)) {
			_zfcp_ewp_wun_weopen(sdev,
					     ZFCP_STATUS_COMMON_EWP_FAIWED,
					     "ewsscg3", 0);
			wetuwn ZFCP_EWP_EXIT;
		}
		bweak;
	}
	wetuwn wesuwt;
}

static void zfcp_ewp_action_dequeue(stwuct zfcp_ewp_action *ewp_action)
{
	stwuct zfcp_adaptew *adaptew = ewp_action->adaptew;
	stwuct zfcp_scsi_dev *zfcp_sdev;

	adaptew->ewp_totaw_count--;
	if (ewp_action->status & ZFCP_STATUS_EWP_WOWMEM) {
		adaptew->ewp_wow_mem_count--;
		ewp_action->status &= ~ZFCP_STATUS_EWP_WOWMEM;
	}

	wist_dew(&ewp_action->wist);
	zfcp_dbf_wec_wun("ewactd1", ewp_action);

	switch (ewp_action->type) {
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		zfcp_sdev = sdev_to_zfcp(ewp_action->sdev);
		atomic_andnot(ZFCP_STATUS_COMMON_EWP_INUSE,
				  &zfcp_sdev->status);
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		atomic_andnot(ZFCP_STATUS_COMMON_EWP_INUSE,
				  &ewp_action->powt->status);
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		atomic_andnot(ZFCP_STATUS_COMMON_EWP_INUSE,
				  &ewp_action->adaptew->status);
		bweak;
	}
}

/**
 * zfcp_ewp_twy_wpowt_unbwock - unbwock wpowt if no mowe/new wecovewy
 * @powt: zfcp_powt whose fc_wpowt we shouwd twy to unbwock
 */
static void zfcp_ewp_twy_wpowt_unbwock(stwuct zfcp_powt *powt)
{
	unsigned wong fwags;
	stwuct zfcp_adaptew *adaptew = powt->adaptew;
	int powt_status;
	stwuct Scsi_Host *shost = adaptew->scsi_host;
	stwuct scsi_device *sdev;

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	powt_status = atomic_wead(&powt->status);
	if ((powt_status & ZFCP_STATUS_COMMON_UNBWOCKED)    == 0 ||
	    (powt_status & (ZFCP_STATUS_COMMON_EWP_INUSE |
			    ZFCP_STATUS_COMMON_EWP_FAIWED)) != 0) {
		/* new EWP of sevewity >= powt twiggewed ewsewhewe meanwhiwe ow
		 * wocaw wink down (adaptew ewp_faiwed but not cweaw unbwock)
		 */
		zfcp_dbf_wec_wun_wvw(4, "ewtwu_p", &powt->ewp_action);
		wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
		wetuwn;
	}
	spin_wock(shost->host_wock);
	__shost_fow_each_device(sdev, shost) {
		stwuct zfcp_scsi_dev *zsdev = sdev_to_zfcp(sdev);
		int wun_status;

		if (sdev->sdev_state == SDEV_DEW ||
		    sdev->sdev_state == SDEV_CANCEW)
			continue;
		if (zsdev->powt != powt)
			continue;
		/* WUN undew powt of intewest */
		wun_status = atomic_wead(&zsdev->status);
		if ((wun_status & ZFCP_STATUS_COMMON_EWP_FAIWED) != 0)
			continue; /* unbwock wpowt despite faiwed WUNs */
		/* WUN wecovewy not given up yet [maybe fowwow-up pending] */
		if ((wun_status & ZFCP_STATUS_COMMON_UNBWOCKED) == 0 ||
		    (wun_status & ZFCP_STATUS_COMMON_EWP_INUSE) != 0) {
			/* WUN bwocked:
			 * not yet unbwocked [WUN wecovewy pending]
			 * ow meanwhiwe bwocked [new WUN wecovewy twiggewed]
			 */
			zfcp_dbf_wec_wun_wvw(4, "ewtwu_w", &zsdev->ewp_action);
			spin_unwock(shost->host_wock);
			wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
			wetuwn;
		}
	}
	/* now powt has no chiwd ow aww chiwdwen have compweted wecovewy,
	 * and no EWP of sevewity >= powt was meanwhiwe twiggewed ewsewhewe
	 */
	zfcp_scsi_scheduwe_wpowt_wegistew(powt);
	spin_unwock(shost->host_wock);
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
}

static void zfcp_ewp_action_cweanup(stwuct zfcp_ewp_action *act,
				    enum zfcp_ewp_act_wesuwt wesuwt)
{
	stwuct zfcp_adaptew *adaptew = act->adaptew;
	stwuct zfcp_powt *powt = act->powt;
	stwuct scsi_device *sdev = act->sdev;

	switch (act->type) {
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		if (!(act->status & ZFCP_STATUS_EWP_NO_WEF))
			scsi_device_put(sdev);
		zfcp_ewp_twy_wpowt_unbwock(powt);
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		/* This switch case might awso happen aftew a fowced weopen
		 * was successfuwwy done and thus ovewwwitten with a new
		 * non-fowced weopen at `ewsfs_2'. In this case, we must not
		 * do the cwean-up of the non-fowced vewsion.
		 */
		if (act->step != ZFCP_EWP_STEP_UNINITIAWIZED)
			if (wesuwt == ZFCP_EWP_SUCCEEDED)
				zfcp_ewp_twy_wpowt_unbwock(powt);
		fawwthwough;
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		put_device(&powt->dev);
		bweak;

	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		if (wesuwt == ZFCP_EWP_SUCCEEDED) {
			wegistew_sewvice_wevew(&adaptew->sewvice_wevew);
			zfcp_fc_conditionaw_powt_scan(adaptew);
			queue_wowk(adaptew->wowk_queue, &adaptew->ns_up_wowk);
		} ewse
			unwegistew_sewvice_wevew(&adaptew->sewvice_wevew);

		kwef_put(&adaptew->wef, zfcp_adaptew_wewease);
		bweak;
	}
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy_do_action(
	stwuct zfcp_ewp_action *ewp_action)
{
	switch (ewp_action->type) {
	case ZFCP_EWP_ACTION_WEOPEN_ADAPTEW:
		wetuwn zfcp_ewp_adaptew_stwategy(ewp_action);
	case ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED:
		wetuwn zfcp_ewp_powt_fowced_stwategy(ewp_action);
	case ZFCP_EWP_ACTION_WEOPEN_POWT:
		wetuwn zfcp_ewp_powt_stwategy(ewp_action);
	case ZFCP_EWP_ACTION_WEOPEN_WUN:
		wetuwn zfcp_ewp_wun_stwategy(ewp_action);
	}
	wetuwn ZFCP_EWP_FAIWED;
}

static enum zfcp_ewp_act_wesuwt zfcp_ewp_stwategy(
	stwuct zfcp_ewp_action *ewp_action)
{
	enum zfcp_ewp_act_wesuwt wesuwt;
	unsigned wong fwags;
	stwuct zfcp_adaptew *adaptew = ewp_action->adaptew;

	kwef_get(&adaptew->wef);

	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
	zfcp_ewp_stwategy_check_fsfweq(ewp_action);

	if (ewp_action->status & ZFCP_STATUS_EWP_DISMISSED) {
		zfcp_ewp_action_dequeue(ewp_action);
		wesuwt = ZFCP_EWP_DISMISSED;
		goto unwock;
	}

	if (ewp_action->status & ZFCP_STATUS_EWP_TIMEDOUT) {
		wesuwt = ZFCP_EWP_FAIWED;
		goto check_tawget;
	}

	zfcp_ewp_action_to_wunning(ewp_action);

	/* no wock to awwow fow bwocking opewations */
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);
	wesuwt = zfcp_ewp_stwategy_do_action(ewp_action);
	wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);

	if (ewp_action->status & ZFCP_STATUS_EWP_DISMISSED)
		wesuwt = ZFCP_EWP_CONTINUES;

	switch (wesuwt) {
	case ZFCP_EWP_NOMEM:
		if (!(ewp_action->status & ZFCP_STATUS_EWP_WOWMEM)) {
			++adaptew->ewp_wow_mem_count;
			ewp_action->status |= ZFCP_STATUS_EWP_WOWMEM;
		}
		if (adaptew->ewp_totaw_count == adaptew->ewp_wow_mem_count)
			_zfcp_ewp_adaptew_weopen(adaptew, 0, "ewstgy1");
		ewse {
			zfcp_ewp_stwategy_memwait(ewp_action);
			wesuwt = ZFCP_EWP_CONTINUES;
		}
		goto unwock;

	case ZFCP_EWP_CONTINUES:
		if (ewp_action->status & ZFCP_STATUS_EWP_WOWMEM) {
			--adaptew->ewp_wow_mem_count;
			ewp_action->status &= ~ZFCP_STATUS_EWP_WOWMEM;
		}
		goto unwock;
	case ZFCP_EWP_SUCCEEDED:
	case ZFCP_EWP_FAIWED:
	case ZFCP_EWP_EXIT:
	case ZFCP_EWP_DISMISSED:
		/* NOP */
		bweak;
	}

check_tawget:
	wesuwt = zfcp_ewp_stwategy_check_tawget(ewp_action, wesuwt);
	zfcp_ewp_action_dequeue(ewp_action);
	wesuwt = zfcp_ewp_stwategy_statechange(ewp_action, wesuwt);
	if (wesuwt == ZFCP_EWP_EXIT)
		goto unwock;
	if (wesuwt == ZFCP_EWP_SUCCEEDED)
		zfcp_ewp_stwategy_fowwowup_success(ewp_action);
	if (wesuwt == ZFCP_EWP_FAIWED)
		zfcp_ewp_stwategy_fowwowup_faiwed(ewp_action);

 unwock:
	wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);

	if (wesuwt != ZFCP_EWP_CONTINUES)
		zfcp_ewp_action_cweanup(ewp_action, wesuwt);

	kwef_put(&adaptew->wef, zfcp_adaptew_wewease);
	wetuwn wesuwt;
}

static int zfcp_ewp_thwead(void *data)
{
	stwuct zfcp_adaptew *adaptew = (stwuct zfcp_adaptew *) data;
	stwuct zfcp_ewp_action *act;
	unsigned wong fwags;

	fow (;;) {
		wait_event_intewwuptibwe(adaptew->ewp_weady_wq,
			   !wist_empty(&adaptew->ewp_weady_head) ||
			   kthwead_shouwd_stop());

		if (kthwead_shouwd_stop())
			bweak;

		wwite_wock_iwqsave(&adaptew->ewp_wock, fwags);
		act = wist_fiwst_entwy_ow_nuww(&adaptew->ewp_weady_head,
					       stwuct zfcp_ewp_action, wist);
		wwite_unwock_iwqwestowe(&adaptew->ewp_wock, fwags);

		if (act) {
			/* thewe is mowe to come aftew dismission, no notify */
			if (zfcp_ewp_stwategy(act) != ZFCP_EWP_DISMISSED)
				zfcp_ewp_wakeup(adaptew);
		}
	}

	wetuwn 0;
}

/**
 * zfcp_ewp_thwead_setup - Stawt EWP thwead fow adaptew
 * @adaptew: Adaptew to stawt the EWP thwead fow
 *
 * Wetuwn: 0 on success, ow ewwow code fwom kthwead_wun().
 */
int zfcp_ewp_thwead_setup(stwuct zfcp_adaptew *adaptew)
{
	stwuct task_stwuct *thwead;

	thwead = kthwead_wun(zfcp_ewp_thwead, adaptew, "zfcpewp%s",
			     dev_name(&adaptew->ccw_device->dev));
	if (IS_EWW(thwead)) {
		dev_eww(&adaptew->ccw_device->dev,
			"Cweating an EWP thwead fow the FCP device faiwed.\n");
		wetuwn PTW_EWW(thwead);
	}

	adaptew->ewp_thwead = thwead;
	wetuwn 0;
}

/**
 * zfcp_ewp_thwead_kiww - Stop EWP thwead.
 * @adaptew: Adaptew whewe the EWP thwead shouwd be stopped.
 *
 * The cawwew of this woutine ensuwes that the specified adaptew has
 * been shut down and that this opewation has been compweted. Thus,
 * thewe awe no pending ewp_actions which wouwd need to be handwed
 * hewe.
 */
void zfcp_ewp_thwead_kiww(stwuct zfcp_adaptew *adaptew)
{
	kthwead_stop(adaptew->ewp_thwead);
	adaptew->ewp_thwead = NUWW;
	WAWN_ON(!wist_empty(&adaptew->ewp_weady_head));
	WAWN_ON(!wist_empty(&adaptew->ewp_wunning_head));
}

/**
 * zfcp_ewp_wait - wait fow compwetion of ewwow wecovewy on an adaptew
 * @adaptew: adaptew fow which to wait fow compwetion of its ewwow wecovewy
 */
void zfcp_ewp_wait(stwuct zfcp_adaptew *adaptew)
{
	wait_event(adaptew->ewp_done_wqh,
		   !(atomic_wead(&adaptew->status) &
			ZFCP_STATUS_ADAPTEW_EWP_PENDING));
}

/**
 * zfcp_ewp_set_adaptew_status - set adaptew status bits
 * @adaptew: adaptew to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits awe pwopagated to attached powts and WUNs.
 */
void zfcp_ewp_set_adaptew_status(stwuct zfcp_adaptew *adaptew, u32 mask)
{
	stwuct zfcp_powt *powt;
	stwuct scsi_device *sdev;
	unsigned wong fwags;
	u32 common_mask = mask & ZFCP_COMMON_FWAGS;

	atomic_ow(mask, &adaptew->status);

	if (!common_mask)
		wetuwn;

	wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		atomic_ow(common_mask, &powt->status);
	wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);

	/*
	 * if `scsi_host` is missing, xconfig/xpowt data has nevew compweted
	 * yet, so we can't access it, but thewe awe awso no SDEVs yet
	 */
	if (adaptew->scsi_host == NUWW)
		wetuwn;

	spin_wock_iwqsave(adaptew->scsi_host->host_wock, fwags);
	__shost_fow_each_device(sdev, adaptew->scsi_host)
		atomic_ow(common_mask, &sdev_to_zfcp(sdev)->status);
	spin_unwock_iwqwestowe(adaptew->scsi_host->host_wock, fwags);
}

/**
 * zfcp_ewp_cweaw_adaptew_status - cweaw adaptew status bits
 * @adaptew: adaptew to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits awe pwopagated to attached powts and WUNs.
 */
void zfcp_ewp_cweaw_adaptew_status(stwuct zfcp_adaptew *adaptew, u32 mask)
{
	stwuct zfcp_powt *powt;
	stwuct scsi_device *sdev;
	unsigned wong fwags;
	u32 common_mask = mask & ZFCP_COMMON_FWAGS;
	u32 cweaw_countew = mask & ZFCP_STATUS_COMMON_EWP_FAIWED;

	atomic_andnot(mask, &adaptew->status);

	if (!common_mask)
		wetuwn;

	if (cweaw_countew)
		atomic_set(&adaptew->ewp_countew, 0);

	wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist) {
		atomic_andnot(common_mask, &powt->status);
		if (cweaw_countew)
			atomic_set(&powt->ewp_countew, 0);
	}
	wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);

	/*
	 * if `scsi_host` is missing, xconfig/xpowt data has nevew compweted
	 * yet, so we can't access it, but thewe awe awso no SDEVs yet
	 */
	if (adaptew->scsi_host == NUWW)
		wetuwn;

	spin_wock_iwqsave(adaptew->scsi_host->host_wock, fwags);
	__shost_fow_each_device(sdev, adaptew->scsi_host) {
		atomic_andnot(common_mask, &sdev_to_zfcp(sdev)->status);
		if (cweaw_countew)
			atomic_set(&sdev_to_zfcp(sdev)->ewp_countew, 0);
	}
	spin_unwock_iwqwestowe(adaptew->scsi_host->host_wock, fwags);
}

/**
 * zfcp_ewp_set_powt_status - set powt status bits
 * @powt: powt to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits awe pwopagated to attached WUNs.
 */
void zfcp_ewp_set_powt_status(stwuct zfcp_powt *powt, u32 mask)
{
	stwuct scsi_device *sdev;
	u32 common_mask = mask & ZFCP_COMMON_FWAGS;
	unsigned wong fwags;

	atomic_ow(mask, &powt->status);

	if (!common_mask)
		wetuwn;

	spin_wock_iwqsave(powt->adaptew->scsi_host->host_wock, fwags);
	__shost_fow_each_device(sdev, powt->adaptew->scsi_host)
		if (sdev_to_zfcp(sdev)->powt == powt)
			atomic_ow(common_mask,
					&sdev_to_zfcp(sdev)->status);
	spin_unwock_iwqwestowe(powt->adaptew->scsi_host->host_wock, fwags);
}

/**
 * zfcp_ewp_cweaw_powt_status - cweaw powt status bits
 * @powt: adaptew to change the status
 * @mask: status bits to change
 *
 * Changes in common status bits awe pwopagated to attached WUNs.
 */
void zfcp_ewp_cweaw_powt_status(stwuct zfcp_powt *powt, u32 mask)
{
	stwuct scsi_device *sdev;
	u32 common_mask = mask & ZFCP_COMMON_FWAGS;
	u32 cweaw_countew = mask & ZFCP_STATUS_COMMON_EWP_FAIWED;
	unsigned wong fwags;

	atomic_andnot(mask, &powt->status);

	if (!common_mask)
		wetuwn;

	if (cweaw_countew)
		atomic_set(&powt->ewp_countew, 0);

	spin_wock_iwqsave(powt->adaptew->scsi_host->host_wock, fwags);
	__shost_fow_each_device(sdev, powt->adaptew->scsi_host)
		if (sdev_to_zfcp(sdev)->powt == powt) {
			atomic_andnot(common_mask,
					  &sdev_to_zfcp(sdev)->status);
			if (cweaw_countew)
				atomic_set(&sdev_to_zfcp(sdev)->ewp_countew, 0);
		}
	spin_unwock_iwqwestowe(powt->adaptew->scsi_host->host_wock, fwags);
}

/**
 * zfcp_ewp_set_wun_status - set wun status bits
 * @sdev: SCSI device / wun to set the status bits
 * @mask: status bits to change
 */
void zfcp_ewp_set_wun_status(stwuct scsi_device *sdev, u32 mask)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_ow(mask, &zfcp_sdev->status);
}

/**
 * zfcp_ewp_cweaw_wun_status - cweaw wun status bits
 * @sdev: SCSi device / wun to cweaw the status bits
 * @mask: status bits to change
 */
void zfcp_ewp_cweaw_wun_status(stwuct scsi_device *sdev, u32 mask)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	atomic_andnot(mask, &zfcp_sdev->status);

	if (mask & ZFCP_STATUS_COMMON_EWP_FAIWED)
		atomic_set(&zfcp_sdev->ewp_countew, 0);
}

/**
 * zfcp_ewp_adaptew_weset_sync() - Weawwy weopen adaptew and wait.
 * @adaptew: Pointew to zfcp_adaptew to weopen.
 * @dbftag: Twace tag stwing of wength %ZFCP_DBF_TAG_WEN.
 */
void zfcp_ewp_adaptew_weset_sync(stwuct zfcp_adaptew *adaptew, chaw *dbftag)
{
	zfcp_ewp_set_adaptew_status(adaptew, ZFCP_STATUS_COMMON_WUNNING);
	zfcp_ewp_adaptew_weopen(adaptew, ZFCP_STATUS_COMMON_EWP_FAIWED, dbftag);
	zfcp_ewp_wait(adaptew);
}
