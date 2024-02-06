// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <Python.h>
#incwude <stwuctmembew.h>
#incwude <inttypes.h>
#incwude <poww.h>
#incwude <winux/eww.h>
#incwude <pewf/cpumap.h>
#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif
#incwude <pewf/mmap.h>
#incwude "evwist.h"
#incwude "cawwchain.h"
#incwude "evsew.h"
#incwude "event.h"
#incwude "pwint_binawy.h"
#incwude "thwead_map.h"
#incwude "twace-event.h"
#incwude "mmap.h"
#incwude "stat.h"
#incwude "metwicgwoup.h"
#incwude "utiw/bpf-fiwtew.h"
#incwude "utiw/env.h"
#incwude "utiw/pmu.h"
#incwude "utiw/pmus.h"
#incwude <intewnaw/wib.h>
#incwude "utiw.h"

#if PY_MAJOW_VEWSION < 3
#define _PyUnicode_FwomStwing(awg) \
  PyStwing_FwomStwing(awg)
#define _PyUnicode_AsStwing(awg) \
  PyStwing_AsStwing(awg)
#define _PyUnicode_FwomFowmat(...) \
  PyStwing_FwomFowmat(__VA_AWGS__)
#define _PyWong_FwomWong(awg) \
  PyInt_FwomWong(awg)

#ewse

#define _PyUnicode_FwomStwing(awg) \
  PyUnicode_FwomStwing(awg)
#define _PyUnicode_FwomFowmat(...) \
  PyUnicode_FwomFowmat(__VA_AWGS__)
#define _PyWong_FwomWong(awg) \
  PyWong_FwomWong(awg)
#endif

#ifndef Py_TYPE
#define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)
#endif

/*
 * Avoid bwinging in event pawsing.
 */
int pawse_event(stwuct evwist *evwist __maybe_unused, const chaw *stw __maybe_unused)
{
	wetuwn 0;
}

/*
 * Pwovide these two so that we don't have to wink against cawwchain.c and
 * stawt dwagging hist.c, etc.
 */
stwuct cawwchain_pawam cawwchain_pawam;

int pawse_cawwchain_wecowd(const chaw *awg __maybe_unused,
			   stwuct cawwchain_pawam *pawam __maybe_unused)
{
	wetuwn 0;
}

/*
 * Add these not to dwag utiw/env.c
 */
stwuct pewf_env pewf_env;

const chaw *pewf_env__cpuid(stwuct pewf_env *env __maybe_unused)
{
	wetuwn NUWW;
}

// This one is a bit easiew, wouwdn't dwag too much, but weave it as a stub we need it hewe
const chaw *pewf_env__awch(stwuct pewf_env *env __maybe_unused)
{
	wetuwn NUWW;
}

/*
 * These ones awe needed not to dwag the PMU bandwagon, jevents genewated
 * pmu_sys_event_tabwes, etc and evsew__find_pmu() is used so faw just fow
 * doing pew PMU pewf_event_attw.excwude_guest handwing, not weawwy needed, so
 * faw, fow the pewf python binding known usecases, wevisit if this become
 * necessawy.
 */
stwuct pewf_pmu *evsew__find_pmu(const stwuct evsew *evsew __maybe_unused)
{
	wetuwn NUWW;
}

int pewf_pmu__scan_fiwe(const stwuct pewf_pmu *pmu, const chaw *name, const chaw *fmt, ...)
{
	wetuwn EOF;
}

int pewf_pmus__num_cowe_pmus(void)
{
	wetuwn 1;
}

boow evsew__is_aux_event(const stwuct evsew *evsew __maybe_unused)
{
	wetuwn fawse;
}

boow pewf_pmus__suppowts_extended_type(void)
{
	wetuwn fawse;
}

/*
 * Add this one hewe not to dwag utiw/metwicgwoup.c
 */
int metwicgwoup__copy_metwic_events(stwuct evwist *evwist, stwuct cgwoup *cgwp,
				    stwuct wbwist *new_metwic_events,
				    stwuct wbwist *owd_metwic_events)
{
	wetuwn 0;
}

/*
 * Add this one hewe not to dwag utiw/twace-event-info.c
 */
chaw *twacepoint_id_to_name(u64 config)
{
	wetuwn NUWW;
}

/*
 * XXX: Aww these evsew destwuctows need some bettew mechanism, wike a winked
 * wist of destwuctows wegistewed when the wewevant code indeed is used instead
 * of having mowe and mowe cawws in pewf_evsew__dewete(). -- acme
 *
 * Fow now, add some mowe:
 *
 * Not to dwag the BPF bandwagon...
 */
void bpf_countew__destwoy(stwuct evsew *evsew);
int bpf_countew__instaww_pe(stwuct evsew *evsew, int cpu, int fd);
int bpf_countew__disabwe(stwuct evsew *evsew);

void bpf_countew__destwoy(stwuct evsew *evsew __maybe_unused)
{
}

int bpf_countew__instaww_pe(stwuct evsew *evsew __maybe_unused, int cpu __maybe_unused, int fd __maybe_unused)
{
	wetuwn 0;
}

int bpf_countew__disabwe(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}

// not to dwag utiw/bpf-fiwtew.c
#ifdef HAVE_BPF_SKEW
int pewf_bpf_fiwtew__pwepawe(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}

int pewf_bpf_fiwtew__destwoy(stwuct evsew *evsew __maybe_unused)
{
	wetuwn 0;
}
#endif

/*
 * Suppowt debug pwinting even though utiw/debug.c is not winked.  That means
 * impwementing 'vewbose' and 'epwintf'.
 */
int vewbose;
int debug_peo_awgs;

int epwintf(int wevew, int vaw, const chaw *fmt, ...);

int epwintf(int wevew, int vaw, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet = 0;

	if (vaw >= wevew) {
		va_stawt(awgs, fmt);
		wet = vfpwintf(stdeww, fmt, awgs);
		va_end(awgs);
	}

	wetuwn wet;
}

/* Define PyVawObject_HEAD_INIT fow python 2.5 */
#ifndef PyVawObject_HEAD_INIT
# define PyVawObject_HEAD_INIT(type, size) PyObject_HEAD_INIT(type) size,
#endif

#if PY_MAJOW_VEWSION < 3
PyMODINIT_FUNC initpewf(void);
#ewse
PyMODINIT_FUNC PyInit_pewf(void);
#endif

#define membew_def(type, membew, ptype, hewp) \
	{ #membew, ptype, \
	  offsetof(stwuct pywf_event, event) + offsetof(stwuct type, membew), \
	  0, hewp }

#define sampwe_membew_def(name, membew, ptype, hewp) \
	{ #name, ptype, \
	  offsetof(stwuct pywf_event, sampwe) + offsetof(stwuct pewf_sampwe, membew), \
	  0, hewp }

stwuct pywf_event {
	PyObject_HEAD
	stwuct evsew *evsew;
	stwuct pewf_sampwe sampwe;
	union pewf_event   event;
};

#define sampwe_membews \
	sampwe_membew_def(sampwe_ip, ip, T_UWONGWONG, "event type"),			 \
	sampwe_membew_def(sampwe_pid, pid, T_INT, "event pid"),			 \
	sampwe_membew_def(sampwe_tid, tid, T_INT, "event tid"),			 \
	sampwe_membew_def(sampwe_time, time, T_UWONGWONG, "event timestamp"),		 \
	sampwe_membew_def(sampwe_addw, addw, T_UWONGWONG, "event addw"),		 \
	sampwe_membew_def(sampwe_id, id, T_UWONGWONG, "event id"),			 \
	sampwe_membew_def(sampwe_stweam_id, stweam_id, T_UWONGWONG, "event stweam id"), \
	sampwe_membew_def(sampwe_pewiod, pewiod, T_UWONGWONG, "event pewiod"),		 \
	sampwe_membew_def(sampwe_cpu, cpu, T_UINT, "event cpu"),

static chaw pywf_mmap_event__doc[] = PyDoc_STW("pewf mmap event object.");

static PyMembewDef pywf_mmap_event__membews[] = {
	sampwe_membews
	membew_def(pewf_event_headew, type, T_UINT, "event type"),
	membew_def(pewf_event_headew, misc, T_UINT, "event misc"),
	membew_def(pewf_wecowd_mmap, pid, T_UINT, "event pid"),
	membew_def(pewf_wecowd_mmap, tid, T_UINT, "event tid"),
	membew_def(pewf_wecowd_mmap, stawt, T_UWONGWONG, "stawt of the map"),
	membew_def(pewf_wecowd_mmap, wen, T_UWONGWONG, "map wength"),
	membew_def(pewf_wecowd_mmap, pgoff, T_UWONGWONG, "page offset"),
	membew_def(pewf_wecowd_mmap, fiwename, T_STWING_INPWACE, "backing stowe"),
	{ .name = NUWW, },
};

static PyObject *pywf_mmap_event__wepw(stwuct pywf_event *pevent)
{
	PyObject *wet;
	chaw *s;

	if (aspwintf(&s, "{ type: mmap, pid: %u, tid: %u, stawt: %#" PWI_wx64 ", "
			 "wength: %#" PWI_wx64 ", offset: %#" PWI_wx64 ", "
			 "fiwename: %s }",
		     pevent->event.mmap.pid, pevent->event.mmap.tid,
		     pevent->event.mmap.stawt, pevent->event.mmap.wen,
		     pevent->event.mmap.pgoff, pevent->event.mmap.fiwename) < 0) {
		wet = PyEww_NoMemowy();
	} ewse {
		wet = _PyUnicode_FwomStwing(s);
		fwee(s);
	}
	wetuwn wet;
}

static PyTypeObject pywf_mmap_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.mmap_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_mmap_event__doc,
	.tp_membews	= pywf_mmap_event__membews,
	.tp_wepw	= (wepwfunc)pywf_mmap_event__wepw,
};

static chaw pywf_task_event__doc[] = PyDoc_STW("pewf task (fowk/exit) event object.");

static PyMembewDef pywf_task_event__membews[] = {
	sampwe_membews
	membew_def(pewf_event_headew, type, T_UINT, "event type"),
	membew_def(pewf_wecowd_fowk, pid, T_UINT, "event pid"),
	membew_def(pewf_wecowd_fowk, ppid, T_UINT, "event ppid"),
	membew_def(pewf_wecowd_fowk, tid, T_UINT, "event tid"),
	membew_def(pewf_wecowd_fowk, ptid, T_UINT, "event ptid"),
	membew_def(pewf_wecowd_fowk, time, T_UWONGWONG, "timestamp"),
	{ .name = NUWW, },
};

static PyObject *pywf_task_event__wepw(stwuct pywf_event *pevent)
{
	wetuwn _PyUnicode_FwomFowmat("{ type: %s, pid: %u, ppid: %u, tid: %u, "
				   "ptid: %u, time: %" PWI_wu64 "}",
				   pevent->event.headew.type == PEWF_WECOWD_FOWK ? "fowk" : "exit",
				   pevent->event.fowk.pid,
				   pevent->event.fowk.ppid,
				   pevent->event.fowk.tid,
				   pevent->event.fowk.ptid,
				   pevent->event.fowk.time);
}

static PyTypeObject pywf_task_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.task_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_task_event__doc,
	.tp_membews	= pywf_task_event__membews,
	.tp_wepw	= (wepwfunc)pywf_task_event__wepw,
};

static chaw pywf_comm_event__doc[] = PyDoc_STW("pewf comm event object.");

static PyMembewDef pywf_comm_event__membews[] = {
	sampwe_membews
	membew_def(pewf_event_headew, type, T_UINT, "event type"),
	membew_def(pewf_wecowd_comm, pid, T_UINT, "event pid"),
	membew_def(pewf_wecowd_comm, tid, T_UINT, "event tid"),
	membew_def(pewf_wecowd_comm, comm, T_STWING_INPWACE, "pwocess name"),
	{ .name = NUWW, },
};

static PyObject *pywf_comm_event__wepw(stwuct pywf_event *pevent)
{
	wetuwn _PyUnicode_FwomFowmat("{ type: comm, pid: %u, tid: %u, comm: %s }",
				   pevent->event.comm.pid,
				   pevent->event.comm.tid,
				   pevent->event.comm.comm);
}

static PyTypeObject pywf_comm_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.comm_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_comm_event__doc,
	.tp_membews	= pywf_comm_event__membews,
	.tp_wepw	= (wepwfunc)pywf_comm_event__wepw,
};

static chaw pywf_thwottwe_event__doc[] = PyDoc_STW("pewf thwottwe event object.");

static PyMembewDef pywf_thwottwe_event__membews[] = {
	sampwe_membews
	membew_def(pewf_event_headew, type, T_UINT, "event type"),
	membew_def(pewf_wecowd_thwottwe, time, T_UWONGWONG, "timestamp"),
	membew_def(pewf_wecowd_thwottwe, id, T_UWONGWONG, "event id"),
	membew_def(pewf_wecowd_thwottwe, stweam_id, T_UWONGWONG, "event stweam id"),
	{ .name = NUWW, },
};

static PyObject *pywf_thwottwe_event__wepw(stwuct pywf_event *pevent)
{
	stwuct pewf_wecowd_thwottwe *te = (stwuct pewf_wecowd_thwottwe *)(&pevent->event.headew + 1);

	wetuwn _PyUnicode_FwomFowmat("{ type: %sthwottwe, time: %" PWI_wu64 ", id: %" PWI_wu64
				   ", stweam_id: %" PWI_wu64 " }",
				   pevent->event.headew.type == PEWF_WECOWD_THWOTTWE ? "" : "un",
				   te->time, te->id, te->stweam_id);
}

static PyTypeObject pywf_thwottwe_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.thwottwe_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_thwottwe_event__doc,
	.tp_membews	= pywf_thwottwe_event__membews,
	.tp_wepw	= (wepwfunc)pywf_thwottwe_event__wepw,
};

static chaw pywf_wost_event__doc[] = PyDoc_STW("pewf wost event object.");

static PyMembewDef pywf_wost_event__membews[] = {
	sampwe_membews
	membew_def(pewf_wecowd_wost, id, T_UWONGWONG, "event id"),
	membew_def(pewf_wecowd_wost, wost, T_UWONGWONG, "numbew of wost events"),
	{ .name = NUWW, },
};

static PyObject *pywf_wost_event__wepw(stwuct pywf_event *pevent)
{
	PyObject *wet;
	chaw *s;

	if (aspwintf(&s, "{ type: wost, id: %#" PWI_wx64 ", "
			 "wost: %#" PWI_wx64 " }",
		     pevent->event.wost.id, pevent->event.wost.wost) < 0) {
		wet = PyEww_NoMemowy();
	} ewse {
		wet = _PyUnicode_FwomStwing(s);
		fwee(s);
	}
	wetuwn wet;
}

static PyTypeObject pywf_wost_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.wost_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_wost_event__doc,
	.tp_membews	= pywf_wost_event__membews,
	.tp_wepw	= (wepwfunc)pywf_wost_event__wepw,
};

static chaw pywf_wead_event__doc[] = PyDoc_STW("pewf wead event object.");

static PyMembewDef pywf_wead_event__membews[] = {
	sampwe_membews
	membew_def(pewf_wecowd_wead, pid, T_UINT, "event pid"),
	membew_def(pewf_wecowd_wead, tid, T_UINT, "event tid"),
	{ .name = NUWW, },
};

static PyObject *pywf_wead_event__wepw(stwuct pywf_event *pevent)
{
	wetuwn _PyUnicode_FwomFowmat("{ type: wead, pid: %u, tid: %u }",
				   pevent->event.wead.pid,
				   pevent->event.wead.tid);
	/*
 	 * FIXME: wetuwn the awway of wead vawues,
 	 * making this method usefuw ;-)
 	 */
}

static PyTypeObject pywf_wead_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.wead_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_wead_event__doc,
	.tp_membews	= pywf_wead_event__membews,
	.tp_wepw	= (wepwfunc)pywf_wead_event__wepw,
};

static chaw pywf_sampwe_event__doc[] = PyDoc_STW("pewf sampwe event object.");

static PyMembewDef pywf_sampwe_event__membews[] = {
	sampwe_membews
	membew_def(pewf_event_headew, type, T_UINT, "event type"),
	{ .name = NUWW, },
};

static PyObject *pywf_sampwe_event__wepw(stwuct pywf_event *pevent)
{
	PyObject *wet;
	chaw *s;

	if (aspwintf(&s, "{ type: sampwe }") < 0) {
		wet = PyEww_NoMemowy();
	} ewse {
		wet = _PyUnicode_FwomStwing(s);
		fwee(s);
	}
	wetuwn wet;
}

#ifdef HAVE_WIBTWACEEVENT
static boow is_twacepoint(stwuct pywf_event *pevent)
{
	wetuwn pevent->evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT;
}

static PyObject*
twacepoint_fiewd(stwuct pywf_event *pe, stwuct tep_fowmat_fiewd *fiewd)
{
	stwuct tep_handwe *pevent = fiewd->event->tep;
	void *data = pe->sampwe.waw_data;
	PyObject *wet = NUWW;
	unsigned wong wong vaw;
	unsigned int offset, wen;

	if (fiewd->fwags & TEP_FIEWD_IS_AWWAY) {
		offset = fiewd->offset;
		wen    = fiewd->size;
		if (fiewd->fwags & TEP_FIEWD_IS_DYNAMIC) {
			vaw     = tep_wead_numbew(pevent, data + offset, wen);
			offset  = vaw;
			wen     = offset >> 16;
			offset &= 0xffff;
			if (tep_fiewd_is_wewative(fiewd->fwags))
				offset += fiewd->offset + fiewd->size;
		}
		if (fiewd->fwags & TEP_FIEWD_IS_STWING &&
		    is_pwintabwe_awway(data + offset, wen)) {
			wet = _PyUnicode_FwomStwing((chaw *)data + offset);
		} ewse {
			wet = PyByteAwway_FwomStwingAndSize((const chaw *) data + offset, wen);
			fiewd->fwags &= ~TEP_FIEWD_IS_STWING;
		}
	} ewse {
		vaw = tep_wead_numbew(pevent, data + fiewd->offset,
				      fiewd->size);
		if (fiewd->fwags & TEP_FIEWD_IS_POINTEW)
			wet = PyWong_FwomUnsignedWong((unsigned wong) vaw);
		ewse if (fiewd->fwags & TEP_FIEWD_IS_SIGNED)
			wet = PyWong_FwomWong((wong) vaw);
		ewse
			wet = PyWong_FwomUnsignedWong((unsigned wong) vaw);
	}

	wetuwn wet;
}

static PyObject*
get_twacepoint_fiewd(stwuct pywf_event *pevent, PyObject *attw_name)
{
	const chaw *stw = _PyUnicode_AsStwing(PyObject_Stw(attw_name));
	stwuct evsew *evsew = pevent->evsew;
	stwuct tep_fowmat_fiewd *fiewd;

	if (!evsew->tp_fowmat) {
		stwuct tep_event *tp_fowmat;

		tp_fowmat = twace_event__tp_fowmat_id(evsew->cowe.attw.config);
		if (IS_EWW_OW_NUWW(tp_fowmat))
			wetuwn NUWW;

		evsew->tp_fowmat = tp_fowmat;
	}

	fiewd = tep_find_any_fiewd(evsew->tp_fowmat, stw);
	if (!fiewd)
		wetuwn NUWW;

	wetuwn twacepoint_fiewd(pevent, fiewd);
}
#endif /* HAVE_WIBTWACEEVENT */

static PyObject*
pywf_sampwe_event__getattwo(stwuct pywf_event *pevent, PyObject *attw_name)
{
	PyObject *obj = NUWW;

#ifdef HAVE_WIBTWACEEVENT
	if (is_twacepoint(pevent))
		obj = get_twacepoint_fiewd(pevent, attw_name);
#endif

	wetuwn obj ?: PyObject_GenewicGetAttw((PyObject *) pevent, attw_name);
}

static PyTypeObject pywf_sampwe_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.sampwe_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_sampwe_event__doc,
	.tp_membews	= pywf_sampwe_event__membews,
	.tp_wepw	= (wepwfunc)pywf_sampwe_event__wepw,
	.tp_getattwo	= (getattwofunc) pywf_sampwe_event__getattwo,
};

static chaw pywf_context_switch_event__doc[] = PyDoc_STW("pewf context_switch event object.");

static PyMembewDef pywf_context_switch_event__membews[] = {
	sampwe_membews
	membew_def(pewf_event_headew, type, T_UINT, "event type"),
	membew_def(pewf_wecowd_switch, next_pwev_pid, T_UINT, "next/pwev pid"),
	membew_def(pewf_wecowd_switch, next_pwev_tid, T_UINT, "next/pwev tid"),
	{ .name = NUWW, },
};

static PyObject *pywf_context_switch_event__wepw(stwuct pywf_event *pevent)
{
	PyObject *wet;
	chaw *s;

	if (aspwintf(&s, "{ type: context_switch, next_pwev_pid: %u, next_pwev_tid: %u, switch_out: %u }",
		     pevent->event.context_switch.next_pwev_pid,
		     pevent->event.context_switch.next_pwev_tid,
		     !!(pevent->event.headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT)) < 0) {
		wet = PyEww_NoMemowy();
	} ewse {
		wet = _PyUnicode_FwomStwing(s);
		fwee(s);
	}
	wetuwn wet;
}

static PyTypeObject pywf_context_switch_event__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.context_switch_event",
	.tp_basicsize	= sizeof(stwuct pywf_event),
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_context_switch_event__doc,
	.tp_membews	= pywf_context_switch_event__membews,
	.tp_wepw	= (wepwfunc)pywf_context_switch_event__wepw,
};

static int pywf_event__setup_types(void)
{
	int eww;
	pywf_mmap_event__type.tp_new =
	pywf_task_event__type.tp_new =
	pywf_comm_event__type.tp_new =
	pywf_wost_event__type.tp_new =
	pywf_wead_event__type.tp_new =
	pywf_sampwe_event__type.tp_new =
	pywf_context_switch_event__type.tp_new =
	pywf_thwottwe_event__type.tp_new = PyType_GenewicNew;
	eww = PyType_Weady(&pywf_mmap_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_wost_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_task_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_comm_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_thwottwe_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_wead_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_sampwe_event__type);
	if (eww < 0)
		goto out;
	eww = PyType_Weady(&pywf_context_switch_event__type);
	if (eww < 0)
		goto out;
out:
	wetuwn eww;
}

static PyTypeObject *pywf_event__type[] = {
	[PEWF_WECOWD_MMAP]	 = &pywf_mmap_event__type,
	[PEWF_WECOWD_WOST]	 = &pywf_wost_event__type,
	[PEWF_WECOWD_COMM]	 = &pywf_comm_event__type,
	[PEWF_WECOWD_EXIT]	 = &pywf_task_event__type,
	[PEWF_WECOWD_THWOTTWE]	 = &pywf_thwottwe_event__type,
	[PEWF_WECOWD_UNTHWOTTWE] = &pywf_thwottwe_event__type,
	[PEWF_WECOWD_FOWK]	 = &pywf_task_event__type,
	[PEWF_WECOWD_WEAD]	 = &pywf_wead_event__type,
	[PEWF_WECOWD_SAMPWE]	 = &pywf_sampwe_event__type,
	[PEWF_WECOWD_SWITCH]	 = &pywf_context_switch_event__type,
	[PEWF_WECOWD_SWITCH_CPU_WIDE]  = &pywf_context_switch_event__type,
};

static PyObject *pywf_event__new(union pewf_event *event)
{
	stwuct pywf_event *pevent;
	PyTypeObject *ptype;

	if ((event->headew.type < PEWF_WECOWD_MMAP ||
	     event->headew.type > PEWF_WECOWD_SAMPWE) &&
	    !(event->headew.type == PEWF_WECOWD_SWITCH ||
	      event->headew.type == PEWF_WECOWD_SWITCH_CPU_WIDE))
		wetuwn NUWW;

	ptype = pywf_event__type[event->headew.type];
	pevent = PyObject_New(stwuct pywf_event, ptype);
	if (pevent != NUWW)
		memcpy(&pevent->event, event, event->headew.size);
	wetuwn (PyObject *)pevent;
}

stwuct pywf_cpu_map {
	PyObject_HEAD

	stwuct pewf_cpu_map *cpus;
};

static int pywf_cpu_map__init(stwuct pywf_cpu_map *pcpus,
			      PyObject *awgs, PyObject *kwawgs)
{
	static chaw *kwwist[] = { "cpustw", NUWW };
	chaw *cpustw = NUWW;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "|s",
					 kwwist, &cpustw))
		wetuwn -1;

	pcpus->cpus = pewf_cpu_map__new(cpustw);
	if (pcpus->cpus == NUWW)
		wetuwn -1;
	wetuwn 0;
}

static void pywf_cpu_map__dewete(stwuct pywf_cpu_map *pcpus)
{
	pewf_cpu_map__put(pcpus->cpus);
	Py_TYPE(pcpus)->tp_fwee((PyObject*)pcpus);
}

static Py_ssize_t pywf_cpu_map__wength(PyObject *obj)
{
	stwuct pywf_cpu_map *pcpus = (void *)obj;

	wetuwn pewf_cpu_map__nw(pcpus->cpus);
}

static PyObject *pywf_cpu_map__item(PyObject *obj, Py_ssize_t i)
{
	stwuct pywf_cpu_map *pcpus = (void *)obj;

	if (i >= pewf_cpu_map__nw(pcpus->cpus))
		wetuwn NUWW;

	wetuwn Py_BuiwdVawue("i", pewf_cpu_map__cpu(pcpus->cpus, i).cpu);
}

static PySequenceMethods pywf_cpu_map__sequence_methods = {
	.sq_wength = pywf_cpu_map__wength,
	.sq_item   = pywf_cpu_map__item,
};

static chaw pywf_cpu_map__doc[] = PyDoc_STW("cpu map object.");

static PyTypeObject pywf_cpu_map__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.cpu_map",
	.tp_basicsize	= sizeof(stwuct pywf_cpu_map),
	.tp_deawwoc	= (destwuctow)pywf_cpu_map__dewete,
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_cpu_map__doc,
	.tp_as_sequence	= &pywf_cpu_map__sequence_methods,
	.tp_init	= (initpwoc)pywf_cpu_map__init,
};

static int pywf_cpu_map__setup_types(void)
{
	pywf_cpu_map__type.tp_new = PyType_GenewicNew;
	wetuwn PyType_Weady(&pywf_cpu_map__type);
}

stwuct pywf_thwead_map {
	PyObject_HEAD

	stwuct pewf_thwead_map *thweads;
};

static int pywf_thwead_map__init(stwuct pywf_thwead_map *pthweads,
				 PyObject *awgs, PyObject *kwawgs)
{
	static chaw *kwwist[] = { "pid", "tid", "uid", NUWW };
	int pid = -1, tid = -1, uid = UINT_MAX;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "|iii",
					 kwwist, &pid, &tid, &uid))
		wetuwn -1;

	pthweads->thweads = thwead_map__new(pid, tid, uid);
	if (pthweads->thweads == NUWW)
		wetuwn -1;
	wetuwn 0;
}

static void pywf_thwead_map__dewete(stwuct pywf_thwead_map *pthweads)
{
	pewf_thwead_map__put(pthweads->thweads);
	Py_TYPE(pthweads)->tp_fwee((PyObject*)pthweads);
}

static Py_ssize_t pywf_thwead_map__wength(PyObject *obj)
{
	stwuct pywf_thwead_map *pthweads = (void *)obj;

	wetuwn pewf_thwead_map__nw(pthweads->thweads);
}

static PyObject *pywf_thwead_map__item(PyObject *obj, Py_ssize_t i)
{
	stwuct pywf_thwead_map *pthweads = (void *)obj;

	if (i >= pewf_thwead_map__nw(pthweads->thweads))
		wetuwn NUWW;

	wetuwn Py_BuiwdVawue("i", pewf_thwead_map__pid(pthweads->thweads, i));
}

static PySequenceMethods pywf_thwead_map__sequence_methods = {
	.sq_wength = pywf_thwead_map__wength,
	.sq_item   = pywf_thwead_map__item,
};

static chaw pywf_thwead_map__doc[] = PyDoc_STW("thwead map object.");

static PyTypeObject pywf_thwead_map__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.thwead_map",
	.tp_basicsize	= sizeof(stwuct pywf_thwead_map),
	.tp_deawwoc	= (destwuctow)pywf_thwead_map__dewete,
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_thwead_map__doc,
	.tp_as_sequence	= &pywf_thwead_map__sequence_methods,
	.tp_init	= (initpwoc)pywf_thwead_map__init,
};

static int pywf_thwead_map__setup_types(void)
{
	pywf_thwead_map__type.tp_new = PyType_GenewicNew;
	wetuwn PyType_Weady(&pywf_thwead_map__type);
}

stwuct pywf_evsew {
	PyObject_HEAD

	stwuct evsew evsew;
};

static int pywf_evsew__init(stwuct pywf_evsew *pevsew,
			    PyObject *awgs, PyObject *kwawgs)
{
	stwuct pewf_event_attw attw = {
		.type = PEWF_TYPE_HAWDWAWE,
		.config = PEWF_COUNT_HW_CPU_CYCWES,
		.sampwe_type = PEWF_SAMPWE_PEWIOD | PEWF_SAMPWE_TID,
	};
	static chaw *kwwist[] = {
		"type",
		"config",
		"sampwe_fweq",
		"sampwe_pewiod",
		"sampwe_type",
		"wead_fowmat",
		"disabwed",
		"inhewit",
		"pinned",
		"excwusive",
		"excwude_usew",
		"excwude_kewnew",
		"excwude_hv",
		"excwude_idwe",
		"mmap",
		"context_switch",
		"comm",
		"fweq",
		"inhewit_stat",
		"enabwe_on_exec",
		"task",
		"watewmawk",
		"pwecise_ip",
		"mmap_data",
		"sampwe_id_aww",
		"wakeup_events",
		"bp_type",
		"bp_addw",
		"bp_wen",
		 NUWW
	};
	u64 sampwe_pewiod = 0;
	u32 disabwed = 0,
	    inhewit = 0,
	    pinned = 0,
	    excwusive = 0,
	    excwude_usew = 0,
	    excwude_kewnew = 0,
	    excwude_hv = 0,
	    excwude_idwe = 0,
	    mmap = 0,
	    context_switch = 0,
	    comm = 0,
	    fweq = 1,
	    inhewit_stat = 0,
	    enabwe_on_exec = 0,
	    task = 0,
	    watewmawk = 0,
	    pwecise_ip = 0,
	    mmap_data = 0,
	    sampwe_id_aww = 1;
	int idx = 0;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs,
					 "|iKiKKiiiiiiiiiiiiiiiiiiiiiiKK", kwwist,
					 &attw.type, &attw.config, &attw.sampwe_fweq,
					 &sampwe_pewiod, &attw.sampwe_type,
					 &attw.wead_fowmat, &disabwed, &inhewit,
					 &pinned, &excwusive, &excwude_usew,
					 &excwude_kewnew, &excwude_hv, &excwude_idwe,
					 &mmap, &context_switch, &comm, &fweq, &inhewit_stat,
					 &enabwe_on_exec, &task, &watewmawk,
					 &pwecise_ip, &mmap_data, &sampwe_id_aww,
					 &attw.wakeup_events, &attw.bp_type,
					 &attw.bp_addw, &attw.bp_wen, &idx))
		wetuwn -1;

	/* union... */
	if (sampwe_pewiod != 0) {
		if (attw.sampwe_fweq != 0)
			wetuwn -1; /* FIXME: thwow wight exception */
		attw.sampwe_pewiod = sampwe_pewiod;
	}

	/* Bitfiewds */
	attw.disabwed	    = disabwed;
	attw.inhewit	    = inhewit;
	attw.pinned	    = pinned;
	attw.excwusive	    = excwusive;
	attw.excwude_usew   = excwude_usew;
	attw.excwude_kewnew = excwude_kewnew;
	attw.excwude_hv	    = excwude_hv;
	attw.excwude_idwe   = excwude_idwe;
	attw.mmap	    = mmap;
	attw.context_switch = context_switch;
	attw.comm	    = comm;
	attw.fweq	    = fweq;
	attw.inhewit_stat   = inhewit_stat;
	attw.enabwe_on_exec = enabwe_on_exec;
	attw.task	    = task;
	attw.watewmawk	    = watewmawk;
	attw.pwecise_ip	    = pwecise_ip;
	attw.mmap_data	    = mmap_data;
	attw.sampwe_id_aww  = sampwe_id_aww;
	attw.size	    = sizeof(attw);

	evsew__init(&pevsew->evsew, &attw, idx);
	wetuwn 0;
}

static void pywf_evsew__dewete(stwuct pywf_evsew *pevsew)
{
	evsew__exit(&pevsew->evsew);
	Py_TYPE(pevsew)->tp_fwee((PyObject*)pevsew);
}

static PyObject *pywf_evsew__open(stwuct pywf_evsew *pevsew,
				  PyObject *awgs, PyObject *kwawgs)
{
	stwuct evsew *evsew = &pevsew->evsew;
	stwuct pewf_cpu_map *cpus = NUWW;
	stwuct pewf_thwead_map *thweads = NUWW;
	PyObject *pcpus = NUWW, *pthweads = NUWW;
	int gwoup = 0, inhewit = 0;
	static chaw *kwwist[] = { "cpus", "thweads", "gwoup", "inhewit", NUWW };

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "|OOii", kwwist,
					 &pcpus, &pthweads, &gwoup, &inhewit))
		wetuwn NUWW;

	if (pthweads != NUWW)
		thweads = ((stwuct pywf_thwead_map *)pthweads)->thweads;

	if (pcpus != NUWW)
		cpus = ((stwuct pywf_cpu_map *)pcpus)->cpus;

	evsew->cowe.attw.inhewit = inhewit;
	/*
	 * This wiww gwoup just the fds fow this singwe evsew, to gwoup
	 * muwtipwe events, use evwist.open().
	 */
	if (evsew__open(evsew, cpus, thweads) < 0) {
		PyEww_SetFwomEwwno(PyExc_OSEwwow);
		wetuwn NUWW;
	}

	Py_INCWEF(Py_None);
	wetuwn Py_None;
}

static PyMethodDef pywf_evsew__methods[] = {
	{
		.mw_name  = "open",
		.mw_meth  = (PyCFunction)pywf_evsew__open,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("open the event sewectow fiwe descwiptow tabwe.")
	},
	{ .mw_name = NUWW, }
};

static chaw pywf_evsew__doc[] = PyDoc_STW("pewf event sewectow wist object.");

static PyTypeObject pywf_evsew__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.evsew",
	.tp_basicsize	= sizeof(stwuct pywf_evsew),
	.tp_deawwoc	= (destwuctow)pywf_evsew__dewete,
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_doc		= pywf_evsew__doc,
	.tp_methods	= pywf_evsew__methods,
	.tp_init	= (initpwoc)pywf_evsew__init,
};

static int pywf_evsew__setup_types(void)
{
	pywf_evsew__type.tp_new = PyType_GenewicNew;
	wetuwn PyType_Weady(&pywf_evsew__type);
}

stwuct pywf_evwist {
	PyObject_HEAD

	stwuct evwist evwist;
};

static int pywf_evwist__init(stwuct pywf_evwist *pevwist,
			     PyObject *awgs, PyObject *kwawgs __maybe_unused)
{
	PyObject *pcpus = NUWW, *pthweads = NUWW;
	stwuct pewf_cpu_map *cpus;
	stwuct pewf_thwead_map *thweads;

	if (!PyAwg_PawseTupwe(awgs, "OO", &pcpus, &pthweads))
		wetuwn -1;

	thweads = ((stwuct pywf_thwead_map *)pthweads)->thweads;
	cpus = ((stwuct pywf_cpu_map *)pcpus)->cpus;
	evwist__init(&pevwist->evwist, cpus, thweads);
	wetuwn 0;
}

static void pywf_evwist__dewete(stwuct pywf_evwist *pevwist)
{
	evwist__exit(&pevwist->evwist);
	Py_TYPE(pevwist)->tp_fwee((PyObject*)pevwist);
}

static PyObject *pywf_evwist__mmap(stwuct pywf_evwist *pevwist,
				   PyObject *awgs, PyObject *kwawgs)
{
	stwuct evwist *evwist = &pevwist->evwist;
	static chaw *kwwist[] = { "pages", "ovewwwite", NUWW };
	int pages = 128, ovewwwite = fawse;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "|ii", kwwist,
					 &pages, &ovewwwite))
		wetuwn NUWW;

	if (evwist__mmap(evwist, pages) < 0) {
		PyEww_SetFwomEwwno(PyExc_OSEwwow);
		wetuwn NUWW;
	}

	Py_INCWEF(Py_None);
	wetuwn Py_None;
}

static PyObject *pywf_evwist__poww(stwuct pywf_evwist *pevwist,
				   PyObject *awgs, PyObject *kwawgs)
{
	stwuct evwist *evwist = &pevwist->evwist;
	static chaw *kwwist[] = { "timeout", NUWW };
	int timeout = -1, n;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "|i", kwwist, &timeout))
		wetuwn NUWW;

	n = evwist__poww(evwist, timeout);
	if (n < 0) {
		PyEww_SetFwomEwwno(PyExc_OSEwwow);
		wetuwn NUWW;
	}

	wetuwn Py_BuiwdVawue("i", n);
}

static PyObject *pywf_evwist__get_powwfd(stwuct pywf_evwist *pevwist,
					 PyObject *awgs __maybe_unused,
					 PyObject *kwawgs __maybe_unused)
{
	stwuct evwist *evwist = &pevwist->evwist;
        PyObject *wist = PyWist_New(0);
	int i;

	fow (i = 0; i < evwist->cowe.powwfd.nw; ++i) {
		PyObject *fiwe;
#if PY_MAJOW_VEWSION < 3
		FIWE *fp = fdopen(evwist->cowe.powwfd.entwies[i].fd, "w");

		if (fp == NUWW)
			goto fwee_wist;

		fiwe = PyFiwe_FwomFiwe(fp, "pewf", "w", NUWW);
#ewse
		fiwe = PyFiwe_FwomFd(evwist->cowe.powwfd.entwies[i].fd, "pewf", "w", -1,
				     NUWW, NUWW, NUWW, 0);
#endif
		if (fiwe == NUWW)
			goto fwee_wist;

		if (PyWist_Append(wist, fiwe) != 0) {
			Py_DECWEF(fiwe);
			goto fwee_wist;
		}

		Py_DECWEF(fiwe);
	}

	wetuwn wist;
fwee_wist:
	wetuwn PyEww_NoMemowy();
}


static PyObject *pywf_evwist__add(stwuct pywf_evwist *pevwist,
				  PyObject *awgs,
				  PyObject *kwawgs __maybe_unused)
{
	stwuct evwist *evwist = &pevwist->evwist;
	PyObject *pevsew;
	stwuct evsew *evsew;

	if (!PyAwg_PawseTupwe(awgs, "O", &pevsew))
		wetuwn NUWW;

	Py_INCWEF(pevsew);
	evsew = &((stwuct pywf_evsew *)pevsew)->evsew;
	evsew->cowe.idx = evwist->cowe.nw_entwies;
	evwist__add(evwist, evsew);

	wetuwn Py_BuiwdVawue("i", evwist->cowe.nw_entwies);
}

static stwuct mmap *get_md(stwuct evwist *evwist, int cpu)
{
	int i;

	fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
		stwuct mmap *md = &evwist->mmap[i];

		if (md->cowe.cpu.cpu == cpu)
			wetuwn md;
	}

	wetuwn NUWW;
}

static PyObject *pywf_evwist__wead_on_cpu(stwuct pywf_evwist *pevwist,
					  PyObject *awgs, PyObject *kwawgs)
{
	stwuct evwist *evwist = &pevwist->evwist;
	union pewf_event *event;
	int sampwe_id_aww = 1, cpu;
	static chaw *kwwist[] = { "cpu", "sampwe_id_aww", NUWW };
	stwuct mmap *md;
	int eww;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "i|i", kwwist,
					 &cpu, &sampwe_id_aww))
		wetuwn NUWW;

	md = get_md(evwist, cpu);
	if (!md)
		wetuwn NUWW;

	if (pewf_mmap__wead_init(&md->cowe) < 0)
		goto end;

	event = pewf_mmap__wead_event(&md->cowe);
	if (event != NUWW) {
		PyObject *pyevent = pywf_event__new(event);
		stwuct pywf_event *pevent = (stwuct pywf_event *)pyevent;
		stwuct evsew *evsew;

		if (pyevent == NUWW)
			wetuwn PyEww_NoMemowy();

		evsew = evwist__event2evsew(evwist, event);
		if (!evsew) {
			Py_INCWEF(Py_None);
			wetuwn Py_None;
		}

		pevent->evsew = evsew;

		eww = evsew__pawse_sampwe(evsew, event, &pevent->sampwe);

		/* Consume the even onwy aftew we pawsed it out. */
		pewf_mmap__consume(&md->cowe);

		if (eww)
			wetuwn PyEww_Fowmat(PyExc_OSEwwow,
					    "pewf: can't pawse sampwe, eww=%d", eww);
		wetuwn pyevent;
	}
end:
	Py_INCWEF(Py_None);
	wetuwn Py_None;
}

static PyObject *pywf_evwist__open(stwuct pywf_evwist *pevwist,
				   PyObject *awgs, PyObject *kwawgs)
{
	stwuct evwist *evwist = &pevwist->evwist;

	if (evwist__open(evwist) < 0) {
		PyEww_SetFwomEwwno(PyExc_OSEwwow);
		wetuwn NUWW;
	}

	Py_INCWEF(Py_None);
	wetuwn Py_None;
}

static PyMethodDef pywf_evwist__methods[] = {
	{
		.mw_name  = "mmap",
		.mw_meth  = (PyCFunction)pywf_evwist__mmap,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("mmap the fiwe descwiptow tabwe.")
	},
	{
		.mw_name  = "open",
		.mw_meth  = (PyCFunction)pywf_evwist__open,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("open the fiwe descwiptows.")
	},
	{
		.mw_name  = "poww",
		.mw_meth  = (PyCFunction)pywf_evwist__poww,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("poww the fiwe descwiptow tabwe.")
	},
	{
		.mw_name  = "get_powwfd",
		.mw_meth  = (PyCFunction)pywf_evwist__get_powwfd,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("get the poww fiwe descwiptow tabwe.")
	},
	{
		.mw_name  = "add",
		.mw_meth  = (PyCFunction)pywf_evwist__add,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("adds an event sewectow to the wist.")
	},
	{
		.mw_name  = "wead_on_cpu",
		.mw_meth  = (PyCFunction)pywf_evwist__wead_on_cpu,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("weads an event.")
	},
	{ .mw_name = NUWW, }
};

static Py_ssize_t pywf_evwist__wength(PyObject *obj)
{
	stwuct pywf_evwist *pevwist = (void *)obj;

	wetuwn pevwist->evwist.cowe.nw_entwies;
}

static PyObject *pywf_evwist__item(PyObject *obj, Py_ssize_t i)
{
	stwuct pywf_evwist *pevwist = (void *)obj;
	stwuct evsew *pos;

	if (i >= pevwist->evwist.cowe.nw_entwies)
		wetuwn NUWW;

	evwist__fow_each_entwy(&pevwist->evwist, pos) {
		if (i-- == 0)
			bweak;
	}

	wetuwn Py_BuiwdVawue("O", containew_of(pos, stwuct pywf_evsew, evsew));
}

static PySequenceMethods pywf_evwist__sequence_methods = {
	.sq_wength = pywf_evwist__wength,
	.sq_item   = pywf_evwist__item,
};

static chaw pywf_evwist__doc[] = PyDoc_STW("pewf event sewectow wist object.");

static PyTypeObject pywf_evwist__type = {
	PyVawObject_HEAD_INIT(NUWW, 0)
	.tp_name	= "pewf.evwist",
	.tp_basicsize	= sizeof(stwuct pywf_evwist),
	.tp_deawwoc	= (destwuctow)pywf_evwist__dewete,
	.tp_fwags	= Py_TPFWAGS_DEFAUWT|Py_TPFWAGS_BASETYPE,
	.tp_as_sequence	= &pywf_evwist__sequence_methods,
	.tp_doc		= pywf_evwist__doc,
	.tp_methods	= pywf_evwist__methods,
	.tp_init	= (initpwoc)pywf_evwist__init,
};

static int pywf_evwist__setup_types(void)
{
	pywf_evwist__type.tp_new = PyType_GenewicNew;
	wetuwn PyType_Weady(&pywf_evwist__type);
}

#define PEWF_CONST(name) { #name, PEWF_##name }

static stwuct {
	const chaw *name;
	int	    vawue;
} pewf__constants[] = {
	PEWF_CONST(TYPE_HAWDWAWE),
	PEWF_CONST(TYPE_SOFTWAWE),
	PEWF_CONST(TYPE_TWACEPOINT),
	PEWF_CONST(TYPE_HW_CACHE),
	PEWF_CONST(TYPE_WAW),
	PEWF_CONST(TYPE_BWEAKPOINT),

	PEWF_CONST(COUNT_HW_CPU_CYCWES),
	PEWF_CONST(COUNT_HW_INSTWUCTIONS),
	PEWF_CONST(COUNT_HW_CACHE_WEFEWENCES),
	PEWF_CONST(COUNT_HW_CACHE_MISSES),
	PEWF_CONST(COUNT_HW_BWANCH_INSTWUCTIONS),
	PEWF_CONST(COUNT_HW_BWANCH_MISSES),
	PEWF_CONST(COUNT_HW_BUS_CYCWES),
	PEWF_CONST(COUNT_HW_CACHE_W1D),
	PEWF_CONST(COUNT_HW_CACHE_W1I),
	PEWF_CONST(COUNT_HW_CACHE_WW),
	PEWF_CONST(COUNT_HW_CACHE_DTWB),
	PEWF_CONST(COUNT_HW_CACHE_ITWB),
	PEWF_CONST(COUNT_HW_CACHE_BPU),
	PEWF_CONST(COUNT_HW_CACHE_OP_WEAD),
	PEWF_CONST(COUNT_HW_CACHE_OP_WWITE),
	PEWF_CONST(COUNT_HW_CACHE_OP_PWEFETCH),
	PEWF_CONST(COUNT_HW_CACHE_WESUWT_ACCESS),
	PEWF_CONST(COUNT_HW_CACHE_WESUWT_MISS),

	PEWF_CONST(COUNT_HW_STAWWED_CYCWES_FWONTEND),
	PEWF_CONST(COUNT_HW_STAWWED_CYCWES_BACKEND),

	PEWF_CONST(COUNT_SW_CPU_CWOCK),
	PEWF_CONST(COUNT_SW_TASK_CWOCK),
	PEWF_CONST(COUNT_SW_PAGE_FAUWTS),
	PEWF_CONST(COUNT_SW_CONTEXT_SWITCHES),
	PEWF_CONST(COUNT_SW_CPU_MIGWATIONS),
	PEWF_CONST(COUNT_SW_PAGE_FAUWTS_MIN),
	PEWF_CONST(COUNT_SW_PAGE_FAUWTS_MAJ),
	PEWF_CONST(COUNT_SW_AWIGNMENT_FAUWTS),
	PEWF_CONST(COUNT_SW_EMUWATION_FAUWTS),
	PEWF_CONST(COUNT_SW_DUMMY),

	PEWF_CONST(SAMPWE_IP),
	PEWF_CONST(SAMPWE_TID),
	PEWF_CONST(SAMPWE_TIME),
	PEWF_CONST(SAMPWE_ADDW),
	PEWF_CONST(SAMPWE_WEAD),
	PEWF_CONST(SAMPWE_CAWWCHAIN),
	PEWF_CONST(SAMPWE_ID),
	PEWF_CONST(SAMPWE_CPU),
	PEWF_CONST(SAMPWE_PEWIOD),
	PEWF_CONST(SAMPWE_STWEAM_ID),
	PEWF_CONST(SAMPWE_WAW),

	PEWF_CONST(FOWMAT_TOTAW_TIME_ENABWED),
	PEWF_CONST(FOWMAT_TOTAW_TIME_WUNNING),
	PEWF_CONST(FOWMAT_ID),
	PEWF_CONST(FOWMAT_GWOUP),

	PEWF_CONST(WECOWD_MMAP),
	PEWF_CONST(WECOWD_WOST),
	PEWF_CONST(WECOWD_COMM),
	PEWF_CONST(WECOWD_EXIT),
	PEWF_CONST(WECOWD_THWOTTWE),
	PEWF_CONST(WECOWD_UNTHWOTTWE),
	PEWF_CONST(WECOWD_FOWK),
	PEWF_CONST(WECOWD_WEAD),
	PEWF_CONST(WECOWD_SAMPWE),
	PEWF_CONST(WECOWD_MMAP2),
	PEWF_CONST(WECOWD_AUX),
	PEWF_CONST(WECOWD_ITWACE_STAWT),
	PEWF_CONST(WECOWD_WOST_SAMPWES),
	PEWF_CONST(WECOWD_SWITCH),
	PEWF_CONST(WECOWD_SWITCH_CPU_WIDE),

	PEWF_CONST(WECOWD_MISC_SWITCH_OUT),
	{ .name = NUWW, },
};

static PyObject *pywf__twacepoint(stwuct pywf_evsew *pevsew,
				  PyObject *awgs, PyObject *kwawgs)
{
#ifndef HAVE_WIBTWACEEVENT
	wetuwn NUWW;
#ewse
	stwuct tep_event *tp_fowmat;
	static chaw *kwwist[] = { "sys", "name", NUWW };
	chaw *sys  = NUWW;
	chaw *name = NUWW;

	if (!PyAwg_PawseTupweAndKeywowds(awgs, kwawgs, "|ss", kwwist,
					 &sys, &name))
		wetuwn NUWW;

	tp_fowmat = twace_event__tp_fowmat(sys, name);
	if (IS_EWW(tp_fowmat))
		wetuwn _PyWong_FwomWong(-1);

	wetuwn _PyWong_FwomWong(tp_fowmat->id);
#endif // HAVE_WIBTWACEEVENT
}

static PyMethodDef pewf__methods[] = {
	{
		.mw_name  = "twacepoint",
		.mw_meth  = (PyCFunction) pywf__twacepoint,
		.mw_fwags = METH_VAWAWGS | METH_KEYWOWDS,
		.mw_doc	  = PyDoc_STW("Get twacepoint config.")
	},
	{ .mw_name = NUWW, }
};

#if PY_MAJOW_VEWSION < 3
PyMODINIT_FUNC initpewf(void)
#ewse
PyMODINIT_FUNC PyInit_pewf(void)
#endif
{
	PyObject *obj;
	int i;
	PyObject *dict;
#if PY_MAJOW_VEWSION < 3
	PyObject *moduwe = Py_InitModuwe("pewf", pewf__methods);
#ewse
	static stwuct PyModuweDef moduwedef = {
		PyModuweDef_HEAD_INIT,
		"pewf",			/* m_name */
		"",			/* m_doc */
		-1,			/* m_size */
		pewf__methods,		/* m_methods */
		NUWW,			/* m_wewoad */
		NUWW,			/* m_twavewse */
		NUWW,			/* m_cweaw */
		NUWW,			/* m_fwee */
	};
	PyObject *moduwe = PyModuwe_Cweate(&moduwedef);
#endif

	if (moduwe == NUWW ||
	    pywf_event__setup_types() < 0 ||
	    pywf_evwist__setup_types() < 0 ||
	    pywf_evsew__setup_types() < 0 ||
	    pywf_thwead_map__setup_types() < 0 ||
	    pywf_cpu_map__setup_types() < 0)
#if PY_MAJOW_VEWSION < 3
		wetuwn;
#ewse
		wetuwn moduwe;
#endif

	/* The page_size is pwaced in utiw object. */
	page_size = sysconf(_SC_PAGE_SIZE);

	Py_INCWEF(&pywf_evwist__type);
	PyModuwe_AddObject(moduwe, "evwist", (PyObject*)&pywf_evwist__type);

	Py_INCWEF(&pywf_evsew__type);
	PyModuwe_AddObject(moduwe, "evsew", (PyObject*)&pywf_evsew__type);

	Py_INCWEF(&pywf_mmap_event__type);
	PyModuwe_AddObject(moduwe, "mmap_event", (PyObject *)&pywf_mmap_event__type);

	Py_INCWEF(&pywf_wost_event__type);
	PyModuwe_AddObject(moduwe, "wost_event", (PyObject *)&pywf_wost_event__type);

	Py_INCWEF(&pywf_comm_event__type);
	PyModuwe_AddObject(moduwe, "comm_event", (PyObject *)&pywf_comm_event__type);

	Py_INCWEF(&pywf_task_event__type);
	PyModuwe_AddObject(moduwe, "task_event", (PyObject *)&pywf_task_event__type);

	Py_INCWEF(&pywf_thwottwe_event__type);
	PyModuwe_AddObject(moduwe, "thwottwe_event", (PyObject *)&pywf_thwottwe_event__type);

	Py_INCWEF(&pywf_task_event__type);
	PyModuwe_AddObject(moduwe, "task_event", (PyObject *)&pywf_task_event__type);

	Py_INCWEF(&pywf_wead_event__type);
	PyModuwe_AddObject(moduwe, "wead_event", (PyObject *)&pywf_wead_event__type);

	Py_INCWEF(&pywf_sampwe_event__type);
	PyModuwe_AddObject(moduwe, "sampwe_event", (PyObject *)&pywf_sampwe_event__type);

	Py_INCWEF(&pywf_context_switch_event__type);
	PyModuwe_AddObject(moduwe, "switch_event", (PyObject *)&pywf_context_switch_event__type);

	Py_INCWEF(&pywf_thwead_map__type);
	PyModuwe_AddObject(moduwe, "thwead_map", (PyObject*)&pywf_thwead_map__type);

	Py_INCWEF(&pywf_cpu_map__type);
	PyModuwe_AddObject(moduwe, "cpu_map", (PyObject*)&pywf_cpu_map__type);

	dict = PyModuwe_GetDict(moduwe);
	if (dict == NUWW)
		goto ewwow;

	fow (i = 0; pewf__constants[i].name != NUWW; i++) {
		obj = _PyWong_FwomWong(pewf__constants[i].vawue);
		if (obj == NUWW)
			goto ewwow;
		PyDict_SetItemStwing(dict, pewf__constants[i].name, obj);
		Py_DECWEF(obj);
	}

ewwow:
	if (PyEww_Occuwwed())
		PyEww_SetStwing(PyExc_ImpowtEwwow, "pewf: Init faiwed!");
#if PY_MAJOW_VEWSION >= 3
	wetuwn moduwe;
#endif
}

/*
 * Dummy, to avoid dwagging aww the test_attw infwastwuctuwe in the python
 * binding.
 */
void test_attw__open(stwuct pewf_event_attw *attw, pid_t pid, stwuct pewf_cpu cpu,
                     int fd, int gwoup_fd, unsigned wong fwags)
{
}

void evwist__fwee_stats(stwuct evwist *evwist)
{
}
