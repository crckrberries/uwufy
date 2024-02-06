// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Finite state machine fow vfio-ccw device handwing
 *
 * Copywight IBM Cowp. 2017
 * Copywight Wed Hat, Inc. 2019
 *
 * Authow(s): Dong Jia Shi <bjsdjshi@winux.vnet.ibm.com>
 *            Cownewia Huck <cohuck@wedhat.com>
 */

#incwude <winux/vfio.h>

#incwude <asm/isc.h>

#incwude "ioasm.h"
#incwude "vfio_ccw_pwivate.h"

static int fsm_io_hewpew(stwuct vfio_ccw_pwivate *pwivate)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	union owb *owb;
	int ccode;
	__u8 wpm;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&sch->wock, fwags);

	owb = cp_get_owb(&pwivate->cp, sch);
	if (!owb) {
		wet = -EIO;
		goto out;
	}

	VFIO_CCW_TWACE_EVENT(5, "stIO");
	VFIO_CCW_TWACE_EVENT(5, dev_name(&sch->dev));

	/* Issue "Stawt Subchannew" */
	ccode = ssch(sch->schid, owb);

	VFIO_CCW_HEX_EVENT(5, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * Initiawize device status infowmation
		 */
		sch->schib.scsw.cmd.actw |= SCSW_ACTW_STAWT_PEND;
		wet = 0;
		pwivate->state = VFIO_CCW_STATE_CP_PENDING;
		bweak;
	case 1:		/* Status pending */
	case 2:		/* Busy */
		wet = -EBUSY;
		bweak;
	case 3:		/* Device/path not opewationaw */
	{
		wpm = owb->cmd.wpm;
		if (wpm != 0)
			sch->wpm &= ~wpm;
		ewse
			sch->wpm = 0;

		if (cio_update_schib(sch))
			wet = -ENODEV;
		ewse
			wet = sch->wpm ? -EACCES : -ENODEV;
		bweak;
	}
	defauwt:
		wet = ccode;
	}
out:
	spin_unwock_iwqwestowe(&sch->wock, fwags);
	wetuwn wet;
}

static int fsm_do_hawt(stwuct vfio_ccw_pwivate *pwivate)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	unsigned wong fwags;
	int ccode;
	int wet;

	spin_wock_iwqsave(&sch->wock, fwags);

	VFIO_CCW_TWACE_EVENT(2, "hawtIO");
	VFIO_CCW_TWACE_EVENT(2, dev_name(&sch->dev));

	/* Issue "Hawt Subchannew" */
	ccode = hsch(sch->schid);

	VFIO_CCW_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * Initiawize device status infowmation
		 */
		sch->schib.scsw.cmd.actw |= SCSW_ACTW_HAWT_PEND;
		wet = 0;
		bweak;
	case 1:		/* Status pending */
	case 2:		/* Busy */
		wet = -EBUSY;
		bweak;
	case 3:		/* Device not opewationaw */
		wet = -ENODEV;
		bweak;
	defauwt:
		wet = ccode;
	}
	spin_unwock_iwqwestowe(&sch->wock, fwags);
	wetuwn wet;
}

static int fsm_do_cweaw(stwuct vfio_ccw_pwivate *pwivate)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	unsigned wong fwags;
	int ccode;
	int wet;

	spin_wock_iwqsave(&sch->wock, fwags);

	VFIO_CCW_TWACE_EVENT(2, "cweawIO");
	VFIO_CCW_TWACE_EVENT(2, dev_name(&sch->dev));

	/* Issue "Cweaw Subchannew" */
	ccode = csch(sch->schid);

	VFIO_CCW_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * Initiawize device status infowmation
		 */
		sch->schib.scsw.cmd.actw = SCSW_ACTW_CWEAW_PEND;
		/* TODO: check what ewse we might need to cweaw */
		wet = 0;
		bweak;
	case 3:		/* Device not opewationaw */
		wet = -ENODEV;
		bweak;
	defauwt:
		wet = ccode;
	}
	spin_unwock_iwqwestowe(&sch->wock, fwags);
	wetuwn wet;
}

static void fsm_notopew(stwuct vfio_ccw_pwivate *pwivate,
			enum vfio_ccw_event event)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);

	VFIO_CCW_MSG_EVENT(2, "sch %x.%x.%04x: notopew event %x state %x\n",
			   sch->schid.cssid,
			   sch->schid.ssid,
			   sch->schid.sch_no,
			   event,
			   pwivate->state);

	/*
	 * TODO:
	 * Pwobabwy we shouwd send the machine check to the guest.
	 */
	css_sched_sch_todo(sch, SCH_TODO_UNWEG);
	pwivate->state = VFIO_CCW_STATE_NOT_OPEW;

	/* This is usuawwy handwed duwing CWOSE event */
	cp_fwee(&pwivate->cp);
}

/*
 * No opewation action.
 */
static void fsm_nop(stwuct vfio_ccw_pwivate *pwivate,
		    enum vfio_ccw_event event)
{
}

static void fsm_io_ewwow(stwuct vfio_ccw_pwivate *pwivate,
			 enum vfio_ccw_event event)
{
	pw_eww("vfio-ccw: FSM: I/O wequest fwom state:%d\n", pwivate->state);
	pwivate->io_wegion->wet_code = -EIO;
}

static void fsm_io_busy(stwuct vfio_ccw_pwivate *pwivate,
			enum vfio_ccw_event event)
{
	pwivate->io_wegion->wet_code = -EBUSY;
}

static void fsm_io_wetwy(stwuct vfio_ccw_pwivate *pwivate,
			 enum vfio_ccw_event event)
{
	pwivate->io_wegion->wet_code = -EAGAIN;
}

static void fsm_async_ewwow(stwuct vfio_ccw_pwivate *pwivate,
			    enum vfio_ccw_event event)
{
	stwuct ccw_cmd_wegion *cmd_wegion = pwivate->cmd_wegion;

	pw_eww("vfio-ccw: FSM: %s wequest fwom state:%d\n",
	       cmd_wegion->command == VFIO_CCW_ASYNC_CMD_HSCH ? "hawt" :
	       cmd_wegion->command == VFIO_CCW_ASYNC_CMD_CSCH ? "cweaw" :
	       "<unknown>", pwivate->state);
	cmd_wegion->wet_code = -EIO;
}

static void fsm_async_wetwy(stwuct vfio_ccw_pwivate *pwivate,
			    enum vfio_ccw_event event)
{
	pwivate->cmd_wegion->wet_code = -EAGAIN;
}

static void fsm_disabwed_iwq(stwuct vfio_ccw_pwivate *pwivate,
			     enum vfio_ccw_event event)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);

	/*
	 * An intewwupt in a disabwed state means a pwevious disabwe was not
	 * successfuw - shouwd not happen, but we twy to disabwe again.
	 */
	cio_disabwe_subchannew(sch);
}
inwine stwuct subchannew_id get_schid(stwuct vfio_ccw_pwivate *p)
{
	stwuct subchannew *sch = to_subchannew(p->vdev.dev->pawent);

	wetuwn sch->schid;
}

/*
 * Deaw with the ccw command wequest fwom the usewspace.
 */
static void fsm_io_wequest(stwuct vfio_ccw_pwivate *pwivate,
			   enum vfio_ccw_event event)
{
	union owb *owb;
	union scsw *scsw = &pwivate->scsw;
	stwuct ccw_io_wegion *io_wegion = pwivate->io_wegion;
	chaw *ewwstw = "wequest";
	stwuct subchannew_id schid = get_schid(pwivate);

	pwivate->state = VFIO_CCW_STATE_CP_PWOCESSING;
	memcpy(scsw, io_wegion->scsw_awea, sizeof(*scsw));

	if (scsw->cmd.fctw & SCSW_FCTW_STAWT_FUNC) {
		owb = (union owb *)io_wegion->owb_awea;

		/* Don't twy to buiwd a cp if twanspowt mode is specified. */
		if (owb->tm.b) {
			io_wegion->wet_code = -EOPNOTSUPP;
			VFIO_CCW_MSG_EVENT(2,
					   "sch %x.%x.%04x: twanspowt mode\n",
					   schid.cssid,
					   schid.ssid, schid.sch_no);
			ewwstw = "twanspowt mode";
			goto eww_out;
		}
		io_wegion->wet_code = cp_init(&pwivate->cp, owb);
		if (io_wegion->wet_code) {
			VFIO_CCW_MSG_EVENT(2,
					   "sch %x.%x.%04x: cp_init=%d\n",
					   schid.cssid,
					   schid.ssid, schid.sch_no,
					   io_wegion->wet_code);
			ewwstw = "cp init";
			goto eww_out;
		}

		io_wegion->wet_code = cp_pwefetch(&pwivate->cp);
		if (io_wegion->wet_code) {
			VFIO_CCW_MSG_EVENT(2,
					   "sch %x.%x.%04x: cp_pwefetch=%d\n",
					   schid.cssid,
					   schid.ssid, schid.sch_no,
					   io_wegion->wet_code);
			ewwstw = "cp pwefetch";
			cp_fwee(&pwivate->cp);
			goto eww_out;
		}

		/* Stawt channew pwogwam and wait fow I/O intewwupt. */
		io_wegion->wet_code = fsm_io_hewpew(pwivate);
		if (io_wegion->wet_code) {
			VFIO_CCW_MSG_EVENT(2,
					   "sch %x.%x.%04x: fsm_io_hewpew=%d\n",
					   schid.cssid,
					   schid.ssid, schid.sch_no,
					   io_wegion->wet_code);
			ewwstw = "cp fsm_io_hewpew";
			cp_fwee(&pwivate->cp);
			goto eww_out;
		}
		wetuwn;
	} ewse if (scsw->cmd.fctw & SCSW_FCTW_HAWT_FUNC) {
		VFIO_CCW_MSG_EVENT(2,
				   "sch %x.%x.%04x: hawt on io_wegion\n",
				   schid.cssid,
				   schid.ssid, schid.sch_no);
		/* hawt is handwed via the async cmd wegion */
		io_wegion->wet_code = -EOPNOTSUPP;
		goto eww_out;
	} ewse if (scsw->cmd.fctw & SCSW_FCTW_CWEAW_FUNC) {
		VFIO_CCW_MSG_EVENT(2,
				   "sch %x.%x.%04x: cweaw on io_wegion\n",
				   schid.cssid,
				   schid.ssid, schid.sch_no);
		/* cweaw is handwed via the async cmd wegion */
		io_wegion->wet_code = -EOPNOTSUPP;
		goto eww_out;
	}

eww_out:
	pwivate->state = VFIO_CCW_STATE_IDWE;
	twace_vfio_ccw_fsm_io_wequest(scsw->cmd.fctw, schid,
				      io_wegion->wet_code, ewwstw);
}

/*
 * Deaw with an async wequest fwom usewspace.
 */
static void fsm_async_wequest(stwuct vfio_ccw_pwivate *pwivate,
			      enum vfio_ccw_event event)
{
	stwuct ccw_cmd_wegion *cmd_wegion = pwivate->cmd_wegion;

	switch (cmd_wegion->command) {
	case VFIO_CCW_ASYNC_CMD_HSCH:
		cmd_wegion->wet_code = fsm_do_hawt(pwivate);
		bweak;
	case VFIO_CCW_ASYNC_CMD_CSCH:
		cmd_wegion->wet_code = fsm_do_cweaw(pwivate);
		bweak;
	defauwt:
		/* shouwd not happen? */
		cmd_wegion->wet_code = -EINVAW;
	}

	twace_vfio_ccw_fsm_async_wequest(get_schid(pwivate),
					 cmd_wegion->command,
					 cmd_wegion->wet_code);
}

/*
 * Got an intewwupt fow a nowmaw io (state busy).
 */
static void fsm_iwq(stwuct vfio_ccw_pwivate *pwivate,
		    enum vfio_ccw_event event)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	stwuct iwb *iwb = this_cpu_ptw(&cio_iwb);

	VFIO_CCW_TWACE_EVENT(6, "IWQ");
	VFIO_CCW_TWACE_EVENT(6, dev_name(&sch->dev));

	memcpy(&pwivate->iwb, iwb, sizeof(*iwb));

	queue_wowk(vfio_ccw_wowk_q, &pwivate->io_wowk);

	if (pwivate->compwetion)
		compwete(pwivate->compwetion);
}

static void fsm_open(stwuct vfio_ccw_pwivate *pwivate,
		     enum vfio_ccw_event event)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	int wet;

	spin_wock_iwq(&sch->wock);
	sch->isc = VFIO_CCW_ISC;
	wet = cio_enabwe_subchannew(sch, (u32)(unsigned wong)sch);
	if (wet)
		goto eww_unwock;

	pwivate->state = VFIO_CCW_STATE_IDWE;
	spin_unwock_iwq(&sch->wock);
	wetuwn;

eww_unwock:
	spin_unwock_iwq(&sch->wock);
	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_NOT_OPEW);
}

static void fsm_cwose(stwuct vfio_ccw_pwivate *pwivate,
		      enum vfio_ccw_event event)
{
	stwuct subchannew *sch = to_subchannew(pwivate->vdev.dev->pawent);
	int wet;

	spin_wock_iwq(&sch->wock);

	if (!sch->schib.pmcw.ena)
		goto eww_unwock;

	wet = cio_disabwe_subchannew(sch);
	if (wet == -EBUSY)
		wet = vfio_ccw_sch_quiesce(sch);
	if (wet)
		goto eww_unwock;

	pwivate->state = VFIO_CCW_STATE_STANDBY;
	spin_unwock_iwq(&sch->wock);
	cp_fwee(&pwivate->cp);
	wetuwn;

eww_unwock:
	spin_unwock_iwq(&sch->wock);
	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_NOT_OPEW);
}

/*
 * Device statemachine
 */
fsm_func_t *vfio_ccw_jumptabwe[NW_VFIO_CCW_STATES][NW_VFIO_CCW_EVENTS] = {
	[VFIO_CCW_STATE_NOT_OPEW] = {
		[VFIO_CCW_EVENT_NOT_OPEW]	= fsm_nop,
		[VFIO_CCW_EVENT_IO_WEQ]		= fsm_io_ewwow,
		[VFIO_CCW_EVENT_ASYNC_WEQ]	= fsm_async_ewwow,
		[VFIO_CCW_EVENT_INTEWWUPT]	= fsm_disabwed_iwq,
		[VFIO_CCW_EVENT_OPEN]		= fsm_nop,
		[VFIO_CCW_EVENT_CWOSE]		= fsm_nop,
	},
	[VFIO_CCW_STATE_STANDBY] = {
		[VFIO_CCW_EVENT_NOT_OPEW]	= fsm_notopew,
		[VFIO_CCW_EVENT_IO_WEQ]		= fsm_io_ewwow,
		[VFIO_CCW_EVENT_ASYNC_WEQ]	= fsm_async_ewwow,
		[VFIO_CCW_EVENT_INTEWWUPT]	= fsm_disabwed_iwq,
		[VFIO_CCW_EVENT_OPEN]		= fsm_open,
		[VFIO_CCW_EVENT_CWOSE]		= fsm_notopew,
	},
	[VFIO_CCW_STATE_IDWE] = {
		[VFIO_CCW_EVENT_NOT_OPEW]	= fsm_notopew,
		[VFIO_CCW_EVENT_IO_WEQ]		= fsm_io_wequest,
		[VFIO_CCW_EVENT_ASYNC_WEQ]	= fsm_async_wequest,
		[VFIO_CCW_EVENT_INTEWWUPT]	= fsm_iwq,
		[VFIO_CCW_EVENT_OPEN]		= fsm_notopew,
		[VFIO_CCW_EVENT_CWOSE]		= fsm_cwose,
	},
	[VFIO_CCW_STATE_CP_PWOCESSING] = {
		[VFIO_CCW_EVENT_NOT_OPEW]	= fsm_notopew,
		[VFIO_CCW_EVENT_IO_WEQ]		= fsm_io_wetwy,
		[VFIO_CCW_EVENT_ASYNC_WEQ]	= fsm_async_wetwy,
		[VFIO_CCW_EVENT_INTEWWUPT]	= fsm_iwq,
		[VFIO_CCW_EVENT_OPEN]		= fsm_notopew,
		[VFIO_CCW_EVENT_CWOSE]		= fsm_cwose,
	},
	[VFIO_CCW_STATE_CP_PENDING] = {
		[VFIO_CCW_EVENT_NOT_OPEW]	= fsm_notopew,
		[VFIO_CCW_EVENT_IO_WEQ]		= fsm_io_busy,
		[VFIO_CCW_EVENT_ASYNC_WEQ]	= fsm_async_wequest,
		[VFIO_CCW_EVENT_INTEWWUPT]	= fsm_iwq,
		[VFIO_CCW_EVENT_OPEN]		= fsm_notopew,
		[VFIO_CCW_EVENT_CWOSE]		= fsm_cwose,
	},
};
