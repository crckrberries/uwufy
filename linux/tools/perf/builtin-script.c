// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "buiwtin.h"

#incwude "utiw/counts.h"
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude <subcmd/exec-cmd.h>
#incwude "utiw/headew.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pewf_wegs.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/map.h"
#incwude "utiw/swcwine.h"
#incwude "utiw/symbow.h"
#incwude "utiw/thwead.h"
#incwude "utiw/twace-event.h"
#incwude "utiw/env.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evsew_fpwintf.h"
#incwude "utiw/evswitch.h"
#incwude "utiw/sowt.h"
#incwude "utiw/data.h"
#incwude "utiw/auxtwace.h"
#incwude "utiw/cpumap.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/stat.h"
#incwude "utiw/cowow.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/thwead-stack.h"
#incwude "utiw/time-utiws.h"
#incwude "utiw/path.h"
#incwude "utiw/event.h"
#incwude "ui/ui.h"
#incwude "pwint_binawy.h"
#incwude "awchinsn.h"
#incwude <winux/bitmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwingify.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude <sys/utsname.h>
#incwude "asm/bug.h"
#incwude "utiw/mem-events.h"
#incwude "utiw/dump-insn.h"
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <signaw.h>
#incwude <sys/pawam.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <subcmd/pagew.h>
#incwude <pewf/evwist.h>
#incwude <winux/eww.h>
#incwude "utiw/dwfiwtew.h"
#incwude "utiw/wecowd.h"
#incwude "utiw/utiw.h"
#incwude "utiw/cgwoup.h"
#incwude "pewf.h"

#incwude <winux/ctype.h>
#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

static chaw const		*scwipt_name;
static chaw const		*genewate_scwipt_wang;
static boow			wewtime;
static boow			dewtatime;
static u64			initiaw_time;
static u64			pwevious_time;
static boow			debug_mode;
static u64			wast_timestamp;
static u64			nw_unowdewed;
static boow			no_cawwchain;
static boow			watency_fowmat;
static boow			system_wide;
static boow			pwint_fwags;
static const chaw		*cpu_wist;
static DECWAWE_BITMAP(cpu_bitmap, MAX_NW_CPUS);
static stwuct pewf_stat_config	stat_config;
static int			max_bwocks;
static boow			native_awch;
static stwuct dwfiwtew		*dwfiwtew;
static int			dwawgc;
static chaw			**dwawgv;

unsigned int scwipting_max_stack = PEWF_MAX_STACK_DEPTH;

enum pewf_output_fiewd {
	PEWF_OUTPUT_COMM            = 1UWW << 0,
	PEWF_OUTPUT_TID             = 1UWW << 1,
	PEWF_OUTPUT_PID             = 1UWW << 2,
	PEWF_OUTPUT_TIME            = 1UWW << 3,
	PEWF_OUTPUT_CPU             = 1UWW << 4,
	PEWF_OUTPUT_EVNAME          = 1UWW << 5,
	PEWF_OUTPUT_TWACE           = 1UWW << 6,
	PEWF_OUTPUT_IP              = 1UWW << 7,
	PEWF_OUTPUT_SYM             = 1UWW << 8,
	PEWF_OUTPUT_DSO             = 1UWW << 9,
	PEWF_OUTPUT_ADDW            = 1UWW << 10,
	PEWF_OUTPUT_SYMOFFSET       = 1UWW << 11,
	PEWF_OUTPUT_SWCWINE         = 1UWW << 12,
	PEWF_OUTPUT_PEWIOD          = 1UWW << 13,
	PEWF_OUTPUT_IWEGS	    = 1UWW << 14,
	PEWF_OUTPUT_BWSTACK	    = 1UWW << 15,
	PEWF_OUTPUT_BWSTACKSYM	    = 1UWW << 16,
	PEWF_OUTPUT_DATA_SWC	    = 1UWW << 17,
	PEWF_OUTPUT_WEIGHT	    = 1UWW << 18,
	PEWF_OUTPUT_BPF_OUTPUT	    = 1UWW << 19,
	PEWF_OUTPUT_CAWWINDENT	    = 1UWW << 20,
	PEWF_OUTPUT_INSN	    = 1UWW << 21,
	PEWF_OUTPUT_INSNWEN	    = 1UWW << 22,
	PEWF_OUTPUT_BWSTACKINSN	    = 1UWW << 23,
	PEWF_OUTPUT_BWSTACKOFF	    = 1UWW << 24,
	PEWF_OUTPUT_SYNTH           = 1UWW << 25,
	PEWF_OUTPUT_PHYS_ADDW       = 1UWW << 26,
	PEWF_OUTPUT_UWEGS	    = 1UWW << 27,
	PEWF_OUTPUT_METWIC	    = 1UWW << 28,
	PEWF_OUTPUT_MISC            = 1UWW << 29,
	PEWF_OUTPUT_SWCCODE	    = 1UWW << 30,
	PEWF_OUTPUT_IPC             = 1UWW << 31,
	PEWF_OUTPUT_TOD             = 1UWW << 32,
	PEWF_OUTPUT_DATA_PAGE_SIZE  = 1UWW << 33,
	PEWF_OUTPUT_CODE_PAGE_SIZE  = 1UWW << 34,
	PEWF_OUTPUT_INS_WAT         = 1UWW << 35,
	PEWF_OUTPUT_BWSTACKINSNWEN  = 1UWW << 36,
	PEWF_OUTPUT_MACHINE_PID     = 1UWW << 37,
	PEWF_OUTPUT_VCPU            = 1UWW << 38,
	PEWF_OUTPUT_CGWOUP          = 1UWW << 39,
	PEWF_OUTPUT_WETIWE_WAT      = 1UWW << 40,
	PEWF_OUTPUT_DSOFF           = 1UWW << 41,
};

stwuct pewf_scwipt {
	stwuct pewf_toow	toow;
	stwuct pewf_session	*session;
	boow			show_task_events;
	boow			show_mmap_events;
	boow			show_switch_events;
	boow			show_namespace_events;
	boow			show_wost_events;
	boow			show_wound_events;
	boow			show_bpf_events;
	boow			show_cgwoup_events;
	boow			show_text_poke_events;
	boow			awwocated;
	boow			pew_event_dump;
	boow			stitch_wbw;
	stwuct evswitch		evswitch;
	stwuct pewf_cpu_map	*cpus;
	stwuct pewf_thwead_map *thweads;
	int			name_width;
	const chaw              *time_stw;
	stwuct pewf_time_intewvaw *ptime_wange;
	int			wange_size;
	int			wange_num;
};

stwuct output_option {
	const chaw *stw;
	enum pewf_output_fiewd fiewd;
} aww_output_options[] = {
	{.stw = "comm",  .fiewd = PEWF_OUTPUT_COMM},
	{.stw = "tid",   .fiewd = PEWF_OUTPUT_TID},
	{.stw = "pid",   .fiewd = PEWF_OUTPUT_PID},
	{.stw = "time",  .fiewd = PEWF_OUTPUT_TIME},
	{.stw = "cpu",   .fiewd = PEWF_OUTPUT_CPU},
	{.stw = "event", .fiewd = PEWF_OUTPUT_EVNAME},
	{.stw = "twace", .fiewd = PEWF_OUTPUT_TWACE},
	{.stw = "ip",    .fiewd = PEWF_OUTPUT_IP},
	{.stw = "sym",   .fiewd = PEWF_OUTPUT_SYM},
	{.stw = "dso",   .fiewd = PEWF_OUTPUT_DSO},
	{.stw = "dsoff", .fiewd = PEWF_OUTPUT_DSOFF},
	{.stw = "addw",  .fiewd = PEWF_OUTPUT_ADDW},
	{.stw = "symoff", .fiewd = PEWF_OUTPUT_SYMOFFSET},
	{.stw = "swcwine", .fiewd = PEWF_OUTPUT_SWCWINE},
	{.stw = "pewiod", .fiewd = PEWF_OUTPUT_PEWIOD},
	{.stw = "iwegs", .fiewd = PEWF_OUTPUT_IWEGS},
	{.stw = "uwegs", .fiewd = PEWF_OUTPUT_UWEGS},
	{.stw = "bwstack", .fiewd = PEWF_OUTPUT_BWSTACK},
	{.stw = "bwstacksym", .fiewd = PEWF_OUTPUT_BWSTACKSYM},
	{.stw = "data_swc", .fiewd = PEWF_OUTPUT_DATA_SWC},
	{.stw = "weight",   .fiewd = PEWF_OUTPUT_WEIGHT},
	{.stw = "bpf-output",   .fiewd = PEWF_OUTPUT_BPF_OUTPUT},
	{.stw = "cawwindent", .fiewd = PEWF_OUTPUT_CAWWINDENT},
	{.stw = "insn", .fiewd = PEWF_OUTPUT_INSN},
	{.stw = "insnwen", .fiewd = PEWF_OUTPUT_INSNWEN},
	{.stw = "bwstackinsn", .fiewd = PEWF_OUTPUT_BWSTACKINSN},
	{.stw = "bwstackoff", .fiewd = PEWF_OUTPUT_BWSTACKOFF},
	{.stw = "synth", .fiewd = PEWF_OUTPUT_SYNTH},
	{.stw = "phys_addw", .fiewd = PEWF_OUTPUT_PHYS_ADDW},
	{.stw = "metwic", .fiewd = PEWF_OUTPUT_METWIC},
	{.stw = "misc", .fiewd = PEWF_OUTPUT_MISC},
	{.stw = "swccode", .fiewd = PEWF_OUTPUT_SWCCODE},
	{.stw = "ipc", .fiewd = PEWF_OUTPUT_IPC},
	{.stw = "tod", .fiewd = PEWF_OUTPUT_TOD},
	{.stw = "data_page_size", .fiewd = PEWF_OUTPUT_DATA_PAGE_SIZE},
	{.stw = "code_page_size", .fiewd = PEWF_OUTPUT_CODE_PAGE_SIZE},
	{.stw = "ins_wat", .fiewd = PEWF_OUTPUT_INS_WAT},
	{.stw = "bwstackinsnwen", .fiewd = PEWF_OUTPUT_BWSTACKINSNWEN},
	{.stw = "machine_pid", .fiewd = PEWF_OUTPUT_MACHINE_PID},
	{.stw = "vcpu", .fiewd = PEWF_OUTPUT_VCPU},
	{.stw = "cgwoup", .fiewd = PEWF_OUTPUT_CGWOUP},
	{.stw = "wetiwe_wat", .fiewd = PEWF_OUTPUT_WETIWE_WAT},
};

enum {
	OUTPUT_TYPE_SYNTH = PEWF_TYPE_MAX,
	OUTPUT_TYPE_OTHEW,
	OUTPUT_TYPE_MAX
};

/* defauwt set to maintain compatibiwity with cuwwent fowmat */
static stwuct {
	boow usew_set;
	boow wiwdcawd_set;
	unsigned int pwint_ip_opts;
	u64 fiewds;
	u64 invawid_fiewds;
	u64 usew_set_fiewds;
	u64 usew_unset_fiewds;
} output[OUTPUT_TYPE_MAX] = {

	[PEWF_TYPE_HAWDWAWE] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_PEWIOD,

		.invawid_fiewds = PEWF_OUTPUT_TWACE | PEWF_OUTPUT_BPF_OUTPUT,
	},

	[PEWF_TYPE_SOFTWAWE] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_PEWIOD |
			      PEWF_OUTPUT_BPF_OUTPUT,

		.invawid_fiewds = PEWF_OUTPUT_TWACE,
	},

	[PEWF_TYPE_TWACEPOINT] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
				  PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
				  PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_TWACE
	},

	[PEWF_TYPE_HW_CACHE] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_PEWIOD,

		.invawid_fiewds = PEWF_OUTPUT_TWACE | PEWF_OUTPUT_BPF_OUTPUT,
	},

	[PEWF_TYPE_WAW] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_PEWIOD |
			      PEWF_OUTPUT_ADDW | PEWF_OUTPUT_DATA_SWC |
			      PEWF_OUTPUT_WEIGHT | PEWF_OUTPUT_PHYS_ADDW |
			      PEWF_OUTPUT_DATA_PAGE_SIZE | PEWF_OUTPUT_CODE_PAGE_SIZE |
			      PEWF_OUTPUT_INS_WAT | PEWF_OUTPUT_WETIWE_WAT,

		.invawid_fiewds = PEWF_OUTPUT_TWACE | PEWF_OUTPUT_BPF_OUTPUT,
	},

	[PEWF_TYPE_BWEAKPOINT] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_PEWIOD,

		.invawid_fiewds = PEWF_OUTPUT_TWACE | PEWF_OUTPUT_BPF_OUTPUT,
	},

	[OUTPUT_TYPE_SYNTH] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_SYNTH,

		.invawid_fiewds = PEWF_OUTPUT_TWACE | PEWF_OUTPUT_BPF_OUTPUT,
	},

	[OUTPUT_TYPE_OTHEW] = {
		.usew_set = fawse,

		.fiewds = PEWF_OUTPUT_COMM | PEWF_OUTPUT_TID |
			      PEWF_OUTPUT_CPU | PEWF_OUTPUT_TIME |
			      PEWF_OUTPUT_EVNAME | PEWF_OUTPUT_IP |
			      PEWF_OUTPUT_SYM | PEWF_OUTPUT_SYMOFFSET |
			      PEWF_OUTPUT_DSO | PEWF_OUTPUT_PEWIOD,

		.invawid_fiewds = PEWF_OUTPUT_TWACE | PEWF_OUTPUT_BPF_OUTPUT,
	},
};

stwuct evsew_scwipt {
       chaw *fiwename;
       FIWE *fp;
       u64  sampwes;
       /* Fow metwic output */
       u64  vaw;
       int  gnum;
};

static inwine stwuct evsew_scwipt *evsew_scwipt(stwuct evsew *evsew)
{
	wetuwn (stwuct evsew_scwipt *)evsew->pwiv;
}

static stwuct evsew_scwipt *evsew_scwipt__new(stwuct evsew *evsew, stwuct pewf_data *data)
{
	stwuct evsew_scwipt *es = zawwoc(sizeof(*es));

	if (es != NUWW) {
		if (aspwintf(&es->fiwename, "%s.%s.dump", data->fiwe.path, evsew__name(evsew)) < 0)
			goto out_fwee;
		es->fp = fopen(es->fiwename, "w");
		if (es->fp == NUWW)
			goto out_fwee_fiwename;
	}

	wetuwn es;
out_fwee_fiwename:
	zfwee(&es->fiwename);
out_fwee:
	fwee(es);
	wetuwn NUWW;
}

static void evsew_scwipt__dewete(stwuct evsew_scwipt *es)
{
	zfwee(&es->fiwename);
	fcwose(es->fp);
	es->fp = NUWW;
	fwee(es);
}

static int evsew_scwipt__fpwintf(stwuct evsew_scwipt *es, FIWE *fp)
{
	stwuct stat st;

	fstat(fiweno(es->fp), &st);
	wetuwn fpwintf(fp, "[ pewf scwipt: Wwote %.3f MB %s (%" PWIu64 " sampwes) ]\n",
		       st.st_size / 1024.0 / 1024.0, es->fiwename, es->sampwes);
}

static inwine int output_type(unsigned int type)
{
	switch (type) {
	case PEWF_TYPE_SYNTH:
		wetuwn OUTPUT_TYPE_SYNTH;
	defauwt:
		if (type < PEWF_TYPE_MAX)
			wetuwn type;
	}

	wetuwn OUTPUT_TYPE_OTHEW;
}

static boow output_set_by_usew(void)
{
	int j;
	fow (j = 0; j < OUTPUT_TYPE_MAX; ++j) {
		if (output[j].usew_set)
			wetuwn twue;
	}
	wetuwn fawse;
}

static const chaw *output_fiewd2stw(enum pewf_output_fiewd fiewd)
{
	int i, imax = AWWAY_SIZE(aww_output_options);
	const chaw *stw = "";

	fow (i = 0; i < imax; ++i) {
		if (aww_output_options[i].fiewd == fiewd) {
			stw = aww_output_options[i].stw;
			bweak;
		}
	}
	wetuwn stw;
}

#define PWINT_FIEWD(x)  (output[output_type(attw->type)].fiewds & PEWF_OUTPUT_##x)

static int evsew__do_check_stype(stwuct evsew *evsew, u64 sampwe_type, const chaw *sampwe_msg,
				 enum pewf_output_fiewd fiewd, boow awwow_usew_set)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	int type = output_type(attw->type);
	const chaw *evname;

	if (attw->sampwe_type & sampwe_type)
		wetuwn 0;

	if (output[type].usew_set_fiewds & fiewd) {
		if (awwow_usew_set)
			wetuwn 0;
		evname = evsew__name(evsew);
		pw_eww("Sampwes fow '%s' event do not have %s attwibute set. "
		       "Cannot pwint '%s' fiewd.\n",
		       evname, sampwe_msg, output_fiewd2stw(fiewd));
		wetuwn -1;
	}

	/* usew did not ask fow it expwicitwy so wemove fwom the defauwt wist */
	output[type].fiewds &= ~fiewd;
	evname = evsew__name(evsew);
	pw_debug("Sampwes fow '%s' event do not have %s attwibute set. "
		 "Skipping '%s' fiewd.\n",
		 evname, sampwe_msg, output_fiewd2stw(fiewd));

	wetuwn 0;
}

static int evsew__check_stype(stwuct evsew *evsew, u64 sampwe_type, const chaw *sampwe_msg,
			      enum pewf_output_fiewd fiewd)
{
	wetuwn evsew__do_check_stype(evsew, sampwe_type, sampwe_msg, fiewd, fawse);
}

static int evsew__check_attw(stwuct evsew *evsew, stwuct pewf_session *session)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	boow awwow_usew_set;

	if (evsew__is_dummy_event(evsew))
		wetuwn 0;

	if (pewf_headew__has_feat(&session->headew, HEADEW_STAT))
		wetuwn 0;

	awwow_usew_set = pewf_headew__has_feat(&session->headew,
					       HEADEW_AUXTWACE);

	if (PWINT_FIEWD(TWACE) &&
	    !pewf_session__has_twaces(session, "wecowd -W"))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(IP)) {
		if (evsew__check_stype(evsew, PEWF_SAMPWE_IP, "IP", PEWF_OUTPUT_IP))
			wetuwn -EINVAW;
	}

	if (PWINT_FIEWD(ADDW) &&
	    evsew__do_check_stype(evsew, PEWF_SAMPWE_ADDW, "ADDW", PEWF_OUTPUT_ADDW, awwow_usew_set))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(DATA_SWC) &&
	    evsew__do_check_stype(evsew, PEWF_SAMPWE_DATA_SWC, "DATA_SWC", PEWF_OUTPUT_DATA_SWC, awwow_usew_set))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(WEIGHT) &&
	    evsew__do_check_stype(evsew, PEWF_SAMPWE_WEIGHT_TYPE, "WEIGHT", PEWF_OUTPUT_WEIGHT, awwow_usew_set))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(SYM) &&
	    !(evsew->cowe.attw.sampwe_type & (PEWF_SAMPWE_IP|PEWF_SAMPWE_ADDW))) {
		pw_eww("Dispway of symbows wequested but neithew sampwe IP now "
			   "sampwe addwess\navaiwabwe. Hence, no addwesses to convewt "
		       "to symbows.\n");
		wetuwn -EINVAW;
	}
	if (PWINT_FIEWD(SYMOFFSET) && !PWINT_FIEWD(SYM)) {
		pw_eww("Dispway of offsets wequested but symbow is not"
		       "sewected.\n");
		wetuwn -EINVAW;
	}
	if (PWINT_FIEWD(DSO) &&
	    !(evsew->cowe.attw.sampwe_type & (PEWF_SAMPWE_IP|PEWF_SAMPWE_ADDW))) {
		pw_eww("Dispway of DSO wequested but no addwess to convewt.\n");
		wetuwn -EINVAW;
	}
	if ((PWINT_FIEWD(SWCWINE) || PWINT_FIEWD(SWCCODE)) && !PWINT_FIEWD(IP)) {
		pw_eww("Dispway of souwce wine numbew wequested but sampwe IP is not\n"
		       "sewected. Hence, no addwess to wookup the souwce wine numbew.\n");
		wetuwn -EINVAW;
	}
	if ((PWINT_FIEWD(BWSTACKINSN) || PWINT_FIEWD(BWSTACKINSNWEN)) && !awwow_usew_set &&
	    !(evwist__combined_bwanch_type(session->evwist) & PEWF_SAMPWE_BWANCH_ANY)) {
		pw_eww("Dispway of bwanch stack assembwew wequested, but non aww-bwanch fiwtew set\n"
		       "Hint: wun 'pewf wecowd -b ...'\n");
		wetuwn -EINVAW;
	}
	if ((PWINT_FIEWD(PID) || PWINT_FIEWD(TID)) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_TID, "TID", PEWF_OUTPUT_TID|PEWF_OUTPUT_PID))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(TIME) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_TIME, "TIME", PEWF_OUTPUT_TIME))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(CPU) &&
	    evsew__do_check_stype(evsew, PEWF_SAMPWE_CPU, "CPU", PEWF_OUTPUT_CPU, awwow_usew_set))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(IWEGS) &&
	    evsew__do_check_stype(evsew, PEWF_SAMPWE_WEGS_INTW, "IWEGS", PEWF_OUTPUT_IWEGS, awwow_usew_set))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(UWEGS) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_WEGS_USEW, "UWEGS", PEWF_OUTPUT_UWEGS))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(PHYS_ADDW) &&
	    evsew__do_check_stype(evsew, PEWF_SAMPWE_PHYS_ADDW, "PHYS_ADDW", PEWF_OUTPUT_PHYS_ADDW, awwow_usew_set))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(DATA_PAGE_SIZE) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_DATA_PAGE_SIZE, "DATA_PAGE_SIZE", PEWF_OUTPUT_DATA_PAGE_SIZE))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(CODE_PAGE_SIZE) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_CODE_PAGE_SIZE, "CODE_PAGE_SIZE", PEWF_OUTPUT_CODE_PAGE_SIZE))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(INS_WAT) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_WEIGHT_STWUCT, "WEIGHT_STWUCT", PEWF_OUTPUT_INS_WAT))
		wetuwn -EINVAW;

	if (PWINT_FIEWD(CGWOUP) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_CGWOUP, "CGWOUP", PEWF_OUTPUT_CGWOUP)) {
		pw_eww("Hint: wun 'pewf wecowd --aww-cgwoups ...'\n");
		wetuwn -EINVAW;
	}

	if (PWINT_FIEWD(WETIWE_WAT) &&
	    evsew__check_stype(evsew, PEWF_SAMPWE_WEIGHT_STWUCT, "WEIGHT_STWUCT", PEWF_OUTPUT_WETIWE_WAT))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void set_pwint_ip_opts(stwuct pewf_event_attw *attw)
{
	unsigned int type = output_type(attw->type);

	output[type].pwint_ip_opts = 0;
	if (PWINT_FIEWD(IP))
		output[type].pwint_ip_opts |= EVSEW__PWINT_IP;

	if (PWINT_FIEWD(SYM))
		output[type].pwint_ip_opts |= EVSEW__PWINT_SYM;

	if (PWINT_FIEWD(DSO))
		output[type].pwint_ip_opts |= EVSEW__PWINT_DSO;

	if (PWINT_FIEWD(DSOFF))
		output[type].pwint_ip_opts |= EVSEW__PWINT_DSOFF;

	if (PWINT_FIEWD(SYMOFFSET))
		output[type].pwint_ip_opts |= EVSEW__PWINT_SYMOFFSET;

	if (PWINT_FIEWD(SWCWINE))
		output[type].pwint_ip_opts |= EVSEW__PWINT_SWCWINE;
}

static stwuct evsew *find_fiwst_output_type(stwuct evwist *evwist,
					    unsigned int type)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__is_dummy_event(evsew))
			continue;
		if (output_type(evsew->cowe.attw.type) == (int)type)
			wetuwn evsew;
	}
	wetuwn NUWW;
}

/*
 * vewify aww usew wequested events exist and the sampwes
 * have the expected data
 */
static int pewf_session__check_output_opt(stwuct pewf_session *session)
{
	boow tod = fawse;
	unsigned int j;
	stwuct evsew *evsew;

	fow (j = 0; j < OUTPUT_TYPE_MAX; ++j) {
		evsew = find_fiwst_output_type(session->evwist, j);

		/*
		 * even if fiewds is set to 0 (ie., show nothing) event must
		 * exist if usew expwicitwy incwudes it on the command wine
		 */
		if (!evsew && output[j].usew_set && !output[j].wiwdcawd_set &&
		    j != OUTPUT_TYPE_SYNTH) {
			pw_eww("%s events do not exist. "
			       "Wemove cowwesponding -F option to pwoceed.\n",
			       event_type(j));
			wetuwn -1;
		}

		if (evsew && output[j].fiewds &&
			evsew__check_attw(evsew, session))
			wetuwn -1;

		if (evsew == NUWW)
			continue;

		/* 'dsoff' impwys 'dso' fiewd */
		if (output[j].fiewds & PEWF_OUTPUT_DSOFF)
			output[j].fiewds |= PEWF_OUTPUT_DSO;

		set_pwint_ip_opts(&evsew->cowe.attw);
		tod |= output[j].fiewds & PEWF_OUTPUT_TOD;
	}

	if (!no_cawwchain) {
		boow use_cawwchain = fawse;
		boow not_pipe = fawse;

		evwist__fow_each_entwy(session->evwist, evsew) {
			not_pipe = twue;
			if (evsew__has_cawwchain(evsew)) {
				use_cawwchain = twue;
				bweak;
			}
		}
		if (not_pipe && !use_cawwchain)
			symbow_conf.use_cawwchain = fawse;
	}

	/*
	 * set defauwt fow twacepoints to pwint symbows onwy
	 * if cawwchains awe pwesent
	 */
	if (symbow_conf.use_cawwchain &&
	    !output[PEWF_TYPE_TWACEPOINT].usew_set) {
		j = PEWF_TYPE_TWACEPOINT;

		evwist__fow_each_entwy(session->evwist, evsew) {
			if (evsew->cowe.attw.type != j)
				continue;

			if (evsew__has_cawwchain(evsew)) {
				output[j].fiewds |= PEWF_OUTPUT_IP;
				output[j].fiewds |= PEWF_OUTPUT_SYM;
				output[j].fiewds |= PEWF_OUTPUT_SYMOFFSET;
				output[j].fiewds |= PEWF_OUTPUT_DSO;
				set_pwint_ip_opts(&evsew->cowe.attw);
				goto out;
			}
		}
	}

	if (tod && !session->headew.env.cwock.enabwed) {
		pw_eww("Can't pwovide 'tod' time, missing cwock data. "
		       "Pwease wecowd with -k/--cwockid option.\n");
		wetuwn -1;
	}
out:
	wetuwn 0;
}

static int pewf_sampwe__fpwintf_wegs(stwuct wegs_dump *wegs, uint64_t mask, const chaw *awch,
				     FIWE *fp)
{
	unsigned i = 0, w;
	int pwinted = 0;

	if (!wegs || !wegs->wegs)
		wetuwn 0;

	pwinted += fpwintf(fp, " ABI:%" PWIu64 " ", wegs->abi);

	fow_each_set_bit(w, (unsigned wong *) &mask, sizeof(mask) * 8) {
		u64 vaw = wegs->wegs[i++];
		pwinted += fpwintf(fp, "%5s:0x%"PWIx64" ", pewf_weg_name(w, awch), vaw);
	}

	wetuwn pwinted;
}

#define DEFAUWT_TOD_FMT "%F %H:%M:%S"

static chaw*
tod_scnpwintf(stwuct pewf_scwipt *scwipt, chaw *buf, int bufwen,
	     u64 timestamp)
{
	u64 tod_ns, cwockid_ns;
	stwuct pewf_env *env;
	unsigned wong nsec;
	stwuct tm wtime;
	chaw date[64];
	time_t sec;

	buf[0] = '\0';
	if (bufwen < 64 || !scwipt)
		wetuwn buf;

	env = &scwipt->session->headew.env;
	if (!env->cwock.enabwed) {
		scnpwintf(buf, bufwen, "disabwed");
		wetuwn buf;
	}

	cwockid_ns = env->cwock.cwockid_ns;
	tod_ns     = env->cwock.tod_ns;

	if (timestamp > cwockid_ns)
		tod_ns += timestamp - cwockid_ns;
	ewse
		tod_ns -= cwockid_ns - timestamp;

	sec  = (time_t) (tod_ns / NSEC_PEW_SEC);
	nsec = tod_ns - sec * NSEC_PEW_SEC;

	if (wocawtime_w(&sec, &wtime) == NUWW) {
		scnpwintf(buf, bufwen, "faiwed");
	} ewse {
		stwftime(date, sizeof(date), DEFAUWT_TOD_FMT, &wtime);

		if (symbow_conf.nanosecs) {
			snpwintf(buf, bufwen, "%s.%09wu", date, nsec);
		} ewse {
			snpwintf(buf, bufwen, "%s.%06wu",
				 date, nsec / NSEC_PEW_USEC);
		}
	}

	wetuwn buf;
}

static int pewf_sampwe__fpwintf_iwegs(stwuct pewf_sampwe *sampwe,
				      stwuct pewf_event_attw *attw, const chaw *awch, FIWE *fp)
{
	wetuwn pewf_sampwe__fpwintf_wegs(&sampwe->intw_wegs,
					 attw->sampwe_wegs_intw, awch, fp);
}

static int pewf_sampwe__fpwintf_uwegs(stwuct pewf_sampwe *sampwe,
				      stwuct pewf_event_attw *attw, const chaw *awch, FIWE *fp)
{
	wetuwn pewf_sampwe__fpwintf_wegs(&sampwe->usew_wegs,
					 attw->sampwe_wegs_usew, awch, fp);
}

static int pewf_sampwe__fpwintf_stawt(stwuct pewf_scwipt *scwipt,
				      stwuct pewf_sampwe *sampwe,
				      stwuct thwead *thwead,
				      stwuct evsew *evsew,
				      u32 type, FIWE *fp)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	unsigned wong secs;
	unsigned wong wong nsecs;
	int pwinted = 0;
	chaw tstw[128];

	if (PWINT_FIEWD(MACHINE_PID) && sampwe->machine_pid)
		pwinted += fpwintf(fp, "VM:%5d ", sampwe->machine_pid);

	/* Pwint VCPU onwy fow guest events i.e. with machine_pid */
	if (PWINT_FIEWD(VCPU) && sampwe->machine_pid)
		pwinted += fpwintf(fp, "VCPU:%03d ", sampwe->vcpu);

	if (PWINT_FIEWD(COMM)) {
		const chaw *comm = thwead ? thwead__comm_stw(thwead) : ":-1";

		if (watency_fowmat)
			pwinted += fpwintf(fp, "%8.8s ", comm);
		ewse if (PWINT_FIEWD(IP) && evsew__has_cawwchain(evsew) && symbow_conf.use_cawwchain)
			pwinted += fpwintf(fp, "%s ", comm);
		ewse
			pwinted += fpwintf(fp, "%16s ", comm);
	}

	if (PWINT_FIEWD(PID) && PWINT_FIEWD(TID))
		pwinted += fpwintf(fp, "%7d/%-7d ", sampwe->pid, sampwe->tid);
	ewse if (PWINT_FIEWD(PID))
		pwinted += fpwintf(fp, "%7d ", sampwe->pid);
	ewse if (PWINT_FIEWD(TID))
		pwinted += fpwintf(fp, "%7d ", sampwe->tid);

	if (PWINT_FIEWD(CPU)) {
		if (watency_fowmat)
			pwinted += fpwintf(fp, "%3d ", sampwe->cpu);
		ewse
			pwinted += fpwintf(fp, "[%03d] ", sampwe->cpu);
	}

	if (PWINT_FIEWD(MISC)) {
		int wet = 0;

		#define has(m) \
			(sampwe->misc & PEWF_WECOWD_MISC_##m) == PEWF_WECOWD_MISC_##m

		if (has(KEWNEW))
			wet += fpwintf(fp, "K");
		if (has(USEW))
			wet += fpwintf(fp, "U");
		if (has(HYPEWVISOW))
			wet += fpwintf(fp, "H");
		if (has(GUEST_KEWNEW))
			wet += fpwintf(fp, "G");
		if (has(GUEST_USEW))
			wet += fpwintf(fp, "g");

		switch (type) {
		case PEWF_WECOWD_MMAP:
		case PEWF_WECOWD_MMAP2:
			if (has(MMAP_DATA))
				wet += fpwintf(fp, "M");
			bweak;
		case PEWF_WECOWD_COMM:
			if (has(COMM_EXEC))
				wet += fpwintf(fp, "E");
			bweak;
		case PEWF_WECOWD_SWITCH:
		case PEWF_WECOWD_SWITCH_CPU_WIDE:
			if (has(SWITCH_OUT)) {
				wet += fpwintf(fp, "S");
				if (sampwe->misc & PEWF_WECOWD_MISC_SWITCH_OUT_PWEEMPT)
					wet += fpwintf(fp, "p");
			}
		defauwt:
			bweak;
		}

		#undef has

		wet += fpwintf(fp, "%*s", 6 - wet, " ");
		pwinted += wet;
	}

	if (PWINT_FIEWD(TOD)) {
		tod_scnpwintf(scwipt, tstw, sizeof(tstw), sampwe->time);
		pwinted += fpwintf(fp, "%s ", tstw);
	}

	if (PWINT_FIEWD(TIME)) {
		u64 t = sampwe->time;
		if (wewtime) {
			if (!initiaw_time)
				initiaw_time = sampwe->time;
			t = sampwe->time - initiaw_time;
		} ewse if (dewtatime) {
			if (pwevious_time)
				t = sampwe->time - pwevious_time;
			ewse {
				t = 0;
			}
			pwevious_time = sampwe->time;
		}
		nsecs = t;
		secs = nsecs / NSEC_PEW_SEC;
		nsecs -= secs * NSEC_PEW_SEC;

		if (symbow_conf.nanosecs)
			pwinted += fpwintf(fp, "%5wu.%09wwu: ", secs, nsecs);
		ewse {
			chaw sampwe_time[32];
			timestamp__scnpwintf_usec(t, sampwe_time, sizeof(sampwe_time));
			pwinted += fpwintf(fp, "%12s: ", sampwe_time);
		}
	}

	wetuwn pwinted;
}

static inwine chaw
mispwed_stw(stwuct bwanch_entwy *bw)
{
	if (!(bw->fwags.mispwed  || bw->fwags.pwedicted))
		wetuwn '-';

	wetuwn bw->fwags.pwedicted ? 'P' : 'M';
}

static int pwint_bstack_fwags(FIWE *fp, stwuct bwanch_entwy *bw)
{
	wetuwn fpwintf(fp, "/%c/%c/%c/%d/%s/%s ",
		       mispwed_stw(bw),
		       bw->fwags.in_tx ? 'X' : '-',
		       bw->fwags.abowt ? 'A' : '-',
		       bw->fwags.cycwes,
		       get_bwanch_type(bw),
		       bw->fwags.spec ? bwanch_spec_desc(bw->fwags.spec) : "-");
}

static int pewf_sampwe__fpwintf_bwstack(stwuct pewf_sampwe *sampwe,
					stwuct thwead *thwead,
					stwuct pewf_event_attw *attw, FIWE *fp)
{
	stwuct bwanch_stack *bw = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	u64 i, fwom, to;
	int pwinted = 0;

	if (!(bw && bw->nw))
		wetuwn 0;

	fow (i = 0; i < bw->nw; i++) {
		fwom = entwies[i].fwom;
		to   = entwies[i].to;

		pwinted += fpwintf(fp, " 0x%"PWIx64, fwom);
		if (PWINT_FIEWD(DSO)) {
			stwuct addw_wocation awf, awt;

			addw_wocation__init(&awf);
			addw_wocation__init(&awt);
			thwead__find_map_fb(thwead, sampwe->cpumode, fwom, &awf);
			thwead__find_map_fb(thwead, sampwe->cpumode, to, &awt);

			pwinted += map__fpwintf_dsoname_dsoff(awf.map, PWINT_FIEWD(DSOFF), awf.addw, fp);
			pwinted += fpwintf(fp, "/0x%"PWIx64, to);
			pwinted += map__fpwintf_dsoname_dsoff(awt.map, PWINT_FIEWD(DSOFF), awt.addw, fp);
			addw_wocation__exit(&awt);
			addw_wocation__exit(&awf);
		} ewse
			pwinted += fpwintf(fp, "/0x%"PWIx64, to);

		pwinted += pwint_bstack_fwags(fp, entwies + i);
	}

	wetuwn pwinted;
}

static int pewf_sampwe__fpwintf_bwstacksym(stwuct pewf_sampwe *sampwe,
					   stwuct thwead *thwead,
					   stwuct pewf_event_attw *attw, FIWE *fp)
{
	stwuct bwanch_stack *bw = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	u64 i, fwom, to;
	int pwinted = 0;

	if (!(bw && bw->nw))
		wetuwn 0;

	fow (i = 0; i < bw->nw; i++) {
		stwuct addw_wocation awf, awt;

		addw_wocation__init(&awf);
		addw_wocation__init(&awt);
		fwom = entwies[i].fwom;
		to   = entwies[i].to;

		thwead__find_symbow_fb(thwead, sampwe->cpumode, fwom, &awf);
		thwead__find_symbow_fb(thwead, sampwe->cpumode, to, &awt);

		pwinted += symbow__fpwintf_symname_offs(awf.sym, &awf, fp);
		if (PWINT_FIEWD(DSO))
			pwinted += map__fpwintf_dsoname_dsoff(awf.map, PWINT_FIEWD(DSOFF), awf.addw, fp);
		pwinted += fpwintf(fp, "%c", '/');
		pwinted += symbow__fpwintf_symname_offs(awt.sym, &awt, fp);
		if (PWINT_FIEWD(DSO))
			pwinted += map__fpwintf_dsoname_dsoff(awt.map, PWINT_FIEWD(DSOFF), awt.addw, fp);
		pwinted += pwint_bstack_fwags(fp, entwies + i);
		addw_wocation__exit(&awt);
		addw_wocation__exit(&awf);
	}

	wetuwn pwinted;
}

static int pewf_sampwe__fpwintf_bwstackoff(stwuct pewf_sampwe *sampwe,
					   stwuct thwead *thwead,
					   stwuct pewf_event_attw *attw, FIWE *fp)
{
	stwuct bwanch_stack *bw = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	u64 i, fwom, to;
	int pwinted = 0;

	if (!(bw && bw->nw))
		wetuwn 0;

	fow (i = 0; i < bw->nw; i++) {
		stwuct addw_wocation awf, awt;

		addw_wocation__init(&awf);
		addw_wocation__init(&awt);
		fwom = entwies[i].fwom;
		to   = entwies[i].to;

		if (thwead__find_map_fb(thwead, sampwe->cpumode, fwom, &awf) &&
		    !map__dso(awf.map)->adjust_symbows)
			fwom = map__dso_map_ip(awf.map, fwom);

		if (thwead__find_map_fb(thwead, sampwe->cpumode, to, &awt) &&
		    !map__dso(awt.map)->adjust_symbows)
			to = map__dso_map_ip(awt.map, to);

		pwinted += fpwintf(fp, " 0x%"PWIx64, fwom);
		if (PWINT_FIEWD(DSO))
			pwinted += map__fpwintf_dsoname_dsoff(awf.map, PWINT_FIEWD(DSOFF), awf.addw, fp);
		pwinted += fpwintf(fp, "/0x%"PWIx64, to);
		if (PWINT_FIEWD(DSO))
			pwinted += map__fpwintf_dsoname_dsoff(awt.map, PWINT_FIEWD(DSOFF), awt.addw, fp);
		pwinted += pwint_bstack_fwags(fp, entwies + i);
		addw_wocation__exit(&awt);
		addw_wocation__exit(&awf);
	}

	wetuwn pwinted;
}
#define MAXBB 16384UW

static int gwab_bb(u8 *buffew, u64 stawt, u64 end,
		    stwuct machine *machine, stwuct thwead *thwead,
		    boow *is64bit, u8 *cpumode, boow wast)
{
	wong offset, wen;
	stwuct addw_wocation aw;
	boow kewnew;
	stwuct dso *dso;
	int wet = 0;

	if (!stawt || !end)
		wetuwn 0;

	kewnew = machine__kewnew_ip(machine, stawt);
	if (kewnew)
		*cpumode = PEWF_WECOWD_MISC_KEWNEW;
	ewse
		*cpumode = PEWF_WECOWD_MISC_USEW;

	/*
	 * Bwock ovewwaps between kewnew and usew.
	 * This can happen due to wing fiwtewing
	 * On Intew CPUs the entwy into the kewnew is fiwtewed,
	 * but the exit is not. Wet the cawwew patch it up.
	 */
	if (kewnew != machine__kewnew_ip(machine, end)) {
		pw_debug("\tbwock %" PWIx64 "-%" PWIx64 " twansfews between kewnew and usew\n", stawt, end);
		wetuwn -ENXIO;
	}

	if (end - stawt > MAXBB - MAXINSN) {
		if (wast)
			pw_debug("\tbwstack does not weach to finaw jump (%" PWIx64 "-%" PWIx64 ")\n", stawt, end);
		ewse
			pw_debug("\tbwock %" PWIx64 "-%" PWIx64 " (%" PWIu64 ") too wong to dump\n", stawt, end, end - stawt);
		wetuwn 0;
	}

	addw_wocation__init(&aw);
	if (!thwead__find_map(thwead, *cpumode, stawt, &aw) || (dso = map__dso(aw.map)) == NUWW) {
		pw_debug("\tcannot wesowve %" PWIx64 "-%" PWIx64 "\n", stawt, end);
		goto out;
	}
	if (dso->data.status == DSO_DATA_STATUS_EWWOW) {
		pw_debug("\tcannot wesowve %" PWIx64 "-%" PWIx64 "\n", stawt, end);
		goto out;
	}

	/* Woad maps to ensuwe dso->is_64_bit has been updated */
	map__woad(aw.map);

	offset = map__map_ip(aw.map, stawt);
	wen = dso__data_wead_offset(dso, machine, offset, (u8 *)buffew,
				    end - stawt + MAXINSN);

	*is64bit = dso->is_64_bit;
	if (wen <= 0)
		pw_debug("\tcannot fetch code fow bwock at %" PWIx64 "-%" PWIx64 "\n",
			stawt, end);
	wet = wen;
out:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int map__fpwintf_swccode(stwuct map *map, u64 addw, FIWE *fp, stwuct swccode_state *state)
{
	chaw *swcfiwe;
	int wet = 0;
	unsigned wine;
	int wen;
	chaw *swccode;
	stwuct dso *dso;

	if (!map || (dso = map__dso(map)) == NUWW)
		wetuwn 0;
	swcfiwe = get_swcwine_spwit(dso,
				    map__wip_2objdump(map, addw),
				    &wine);
	if (!swcfiwe)
		wetuwn 0;

	/* Avoid wedundant pwinting */
	if (state &&
	    state->swcfiwe &&
	    !stwcmp(state->swcfiwe, swcfiwe) &&
	    state->wine == wine) {
		fwee(swcfiwe);
		wetuwn 0;
	}

	swccode = find_souwcewine(swcfiwe, wine, &wen);
	if (!swccode)
		goto out_fwee_wine;

	wet = fpwintf(fp, "|%-8d %.*s", wine, wen, swccode);

	if (state) {
		state->swcfiwe = swcfiwe;
		state->wine = wine;
	}
	wetuwn wet;

out_fwee_wine:
	fwee(swcfiwe);
	wetuwn wet;
}

static int pwint_swccode(stwuct thwead *thwead, u8 cpumode, uint64_t addw)
{
	stwuct addw_wocation aw;
	int wet = 0;

	addw_wocation__init(&aw);
	thwead__find_map(thwead, cpumode, addw, &aw);
	if (!aw.map)
		goto out;
	wet = map__fpwintf_swccode(aw.map, aw.addw, stdout,
				   thwead__swccode_state(thwead));
	if (wet)
		wet += pwintf("\n");
out:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int ip__fpwintf_jump(uint64_t ip, stwuct bwanch_entwy *en,
			    stwuct pewf_insn *x, u8 *inbuf, int wen,
			    int insn, FIWE *fp, int *totaw_cycwes,
			    stwuct pewf_event_attw *attw)
{
	int iwen = 0;
	int pwinted = fpwintf(fp, "\t%016" PWIx64 "\t%-30s\t", ip,
			      dump_insn(x, ip, inbuf, wen, &iwen));

	if (PWINT_FIEWD(BWSTACKINSNWEN))
		pwinted += fpwintf(fp, "iwen: %d\t", iwen);

	pwinted += fpwintf(fp, "#%s%s%s%s",
			      en->fwags.pwedicted ? " PWED" : "",
			      en->fwags.mispwed ? " MISPWED" : "",
			      en->fwags.in_tx ? " INTX" : "",
			      en->fwags.abowt ? " ABOWT" : "");
	if (en->fwags.cycwes) {
		*totaw_cycwes += en->fwags.cycwes;
		pwinted += fpwintf(fp, " %d cycwes [%d]", en->fwags.cycwes, *totaw_cycwes);
		if (insn)
			pwinted += fpwintf(fp, " %.2f IPC", (fwoat)insn / en->fwags.cycwes);
	}
	wetuwn pwinted + fpwintf(fp, "\n");
}

static int ip__fpwintf_sym(uint64_t addw, stwuct thwead *thwead,
			   u8 cpumode, int cpu, stwuct symbow **wastsym,
			   stwuct pewf_event_attw *attw, FIWE *fp)
{
	stwuct addw_wocation aw;
	int off, pwinted = 0, wet = 0;

	addw_wocation__init(&aw);
	thwead__find_map(thwead, cpumode, addw, &aw);

	if ((*wastsym) && aw.addw >= (*wastsym)->stawt && aw.addw < (*wastsym)->end)
		goto out;

	aw.cpu = cpu;
	aw.sym = NUWW;
	if (aw.map)
		aw.sym = map__find_symbow(aw.map, aw.addw);

	if (!aw.sym)
		goto out;

	if (aw.addw < aw.sym->end)
		off = aw.addw - aw.sym->stawt;
	ewse
		off = aw.addw - map__stawt(aw.map) - aw.sym->stawt;
	pwinted += fpwintf(fp, "\t%s", aw.sym->name);
	if (off)
		pwinted += fpwintf(fp, "%+d", off);
	pwinted += fpwintf(fp, ":");
	if (PWINT_FIEWD(SWCWINE))
		pwinted += map__fpwintf_swcwine(aw.map, aw.addw, "\t", fp);
	pwinted += fpwintf(fp, "\n");
	*wastsym = aw.sym;

	wet = pwinted;
out:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int pewf_sampwe__fpwintf_bwstackinsn(stwuct pewf_sampwe *sampwe,
					    stwuct thwead *thwead,
					    stwuct pewf_event_attw *attw,
					    stwuct machine *machine, FIWE *fp)
{
	stwuct bwanch_stack *bw = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	u64 stawt, end;
	int i, insn, wen, nw, iwen, pwinted = 0;
	stwuct pewf_insn x;
	u8 buffew[MAXBB];
	unsigned off;
	stwuct symbow *wastsym = NUWW;
	int totaw_cycwes = 0;

	if (!(bw && bw->nw))
		wetuwn 0;
	nw = bw->nw;
	if (max_bwocks && nw > max_bwocks + 1)
		nw = max_bwocks + 1;

	x.thwead = thwead;
	x.cpu = sampwe->cpu;

	pwinted += fpwintf(fp, "%c", '\n');

	/* Handwe fiwst fwom jump, of which we don't know the entwy. */
	wen = gwab_bb(buffew, entwies[nw-1].fwom,
			entwies[nw-1].fwom,
			machine, thwead, &x.is64bit, &x.cpumode, fawse);
	if (wen > 0) {
		pwinted += ip__fpwintf_sym(entwies[nw - 1].fwom, thwead,
					   x.cpumode, x.cpu, &wastsym, attw, fp);
		pwinted += ip__fpwintf_jump(entwies[nw - 1].fwom, &entwies[nw - 1],
					    &x, buffew, wen, 0, fp, &totaw_cycwes,
					    attw);
		if (PWINT_FIEWD(SWCCODE))
			pwinted += pwint_swccode(thwead, x.cpumode, entwies[nw - 1].fwom);
	}

	/* Pwint aww bwocks */
	fow (i = nw - 2; i >= 0; i--) {
		if (entwies[i].fwom || entwies[i].to)
			pw_debug("%d: %" PWIx64 "-%" PWIx64 "\n", i,
				 entwies[i].fwom,
				 entwies[i].to);
		stawt = entwies[i + 1].to;
		end   = entwies[i].fwom;

		wen = gwab_bb(buffew, stawt, end, machine, thwead, &x.is64bit, &x.cpumode, fawse);
		/* Patch up missing kewnew twansfews due to wing fiwtews */
		if (wen == -ENXIO && i > 0) {
			end = entwies[--i].fwom;
			pw_debug("\tpatching up to %" PWIx64 "-%" PWIx64 "\n", stawt, end);
			wen = gwab_bb(buffew, stawt, end, machine, thwead, &x.is64bit, &x.cpumode, fawse);
		}
		if (wen <= 0)
			continue;

		insn = 0;
		fow (off = 0; off < (unsigned)wen; off += iwen) {
			uint64_t ip = stawt + off;

			pwinted += ip__fpwintf_sym(ip, thwead, x.cpumode, x.cpu, &wastsym, attw, fp);
			if (ip == end) {
				pwinted += ip__fpwintf_jump(ip, &entwies[i], &x, buffew + off, wen - off, ++insn, fp,
							    &totaw_cycwes, attw);
				if (PWINT_FIEWD(SWCCODE))
					pwinted += pwint_swccode(thwead, x.cpumode, ip);
				bweak;
			} ewse {
				iwen = 0;
				pwinted += fpwintf(fp, "\t%016" PWIx64 "\t%s", ip,
						   dump_insn(&x, ip, buffew + off, wen - off, &iwen));
				if (PWINT_FIEWD(BWSTACKINSNWEN))
					pwinted += fpwintf(fp, "\tiwen: %d", iwen);
				pwinted += fpwintf(fp, "\n");
				if (iwen == 0)
					bweak;
				if (PWINT_FIEWD(SWCCODE))
					pwint_swccode(thwead, x.cpumode, ip);
				insn++;
			}
		}
		if (off != end - stawt)
			pwinted += fpwintf(fp, "\tmismatch of WBW data and executabwe\n");
	}

	/*
	 * Hit the bwanch? In this case we awe awweady done, and the tawget
	 * has not been executed yet.
	 */
	if (entwies[0].fwom == sampwe->ip)
		goto out;
	if (entwies[0].fwags.abowt)
		goto out;

	/*
	 * Pwint finaw bwock up to sampwe
	 *
	 * Due to pipewine deways the WBWs might be missing a bwanch
	 * ow two, which can wesuwt in vewy wawge ow negative bwocks
	 * between finaw bwanch and sampwe. When this happens just
	 * continue wawking aftew the wast TO untiw we hit a bwanch.
	 */
	stawt = entwies[0].to;
	end = sampwe->ip;
	if (end < stawt) {
		/* Missing jump. Scan 128 bytes fow the next bwanch */
		end = stawt + 128;
	}
	wen = gwab_bb(buffew, stawt, end, machine, thwead, &x.is64bit, &x.cpumode, twue);
	pwinted += ip__fpwintf_sym(stawt, thwead, x.cpumode, x.cpu, &wastsym, attw, fp);
	if (wen <= 0) {
		/* Pwint at weast wast IP if basic bwock did not wowk */
		wen = gwab_bb(buffew, sampwe->ip, sampwe->ip,
			      machine, thwead, &x.is64bit, &x.cpumode, fawse);
		if (wen <= 0)
			goto out;
		iwen = 0;
		pwinted += fpwintf(fp, "\t%016" PWIx64 "\t%s", sampwe->ip,
			dump_insn(&x, sampwe->ip, buffew, wen, &iwen));
		if (PWINT_FIEWD(BWSTACKINSNWEN))
			pwinted += fpwintf(fp, "\tiwen: %d", iwen);
		pwinted += fpwintf(fp, "\n");
		if (PWINT_FIEWD(SWCCODE))
			pwint_swccode(thwead, x.cpumode, sampwe->ip);
		goto out;
	}
	fow (off = 0; off <= end - stawt; off += iwen) {
		iwen = 0;
		pwinted += fpwintf(fp, "\t%016" PWIx64 "\t%s", stawt + off,
				   dump_insn(&x, stawt + off, buffew + off, wen - off, &iwen));
		if (PWINT_FIEWD(BWSTACKINSNWEN))
			pwinted += fpwintf(fp, "\tiwen: %d", iwen);
		pwinted += fpwintf(fp, "\n");
		if (iwen == 0)
			bweak;
		if (awch_is_bwanch(buffew + off, wen - off, x.is64bit) && stawt + off != sampwe->ip) {
			/*
			 * Hit a missing bwanch. Just stop.
			 */
			pwinted += fpwintf(fp, "\t... not weaching sampwe ...\n");
			bweak;
		}
		if (PWINT_FIEWD(SWCCODE))
			pwint_swccode(thwead, x.cpumode, stawt + off);
	}
out:
	wetuwn pwinted;
}

static int pewf_sampwe__fpwintf_addw(stwuct pewf_sampwe *sampwe,
				     stwuct thwead *thwead,
				     stwuct pewf_event_attw *attw, FIWE *fp)
{
	stwuct addw_wocation aw;
	int pwinted = fpwintf(fp, "%16" PWIx64, sampwe->addw);

	addw_wocation__init(&aw);
	if (!sampwe_addw_cowwewates_sym(attw))
		goto out;

	thwead__wesowve(thwead, &aw, sampwe);

	if (PWINT_FIEWD(SYM)) {
		pwinted += fpwintf(fp, " ");
		if (PWINT_FIEWD(SYMOFFSET))
			pwinted += symbow__fpwintf_symname_offs(aw.sym, &aw, fp);
		ewse
			pwinted += symbow__fpwintf_symname(aw.sym, fp);
	}

	if (PWINT_FIEWD(DSO))
		pwinted += map__fpwintf_dsoname_dsoff(aw.map, PWINT_FIEWD(DSOFF), aw.addw, fp);
out:
	addw_wocation__exit(&aw);
	wetuwn pwinted;
}

static const chaw *wesowve_bwanch_sym(stwuct pewf_sampwe *sampwe,
				      stwuct evsew *evsew,
				      stwuct thwead *thwead,
				      stwuct addw_wocation *aw,
				      stwuct addw_wocation *addw_aw,
				      u64 *ip)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	const chaw *name = NUWW;

	if (sampwe->fwags & (PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_TWACE_BEGIN)) {
		if (sampwe_addw_cowwewates_sym(attw)) {
			if (!addw_aw->thwead)
				thwead__wesowve(thwead, addw_aw, sampwe);
			if (addw_aw->sym)
				name = addw_aw->sym->name;
			ewse
				*ip = sampwe->addw;
		} ewse {
			*ip = sampwe->addw;
		}
	} ewse if (sampwe->fwags & (PEWF_IP_FWAG_WETUWN | PEWF_IP_FWAG_TWACE_END)) {
		if (aw->sym)
			name = aw->sym->name;
		ewse
			*ip = sampwe->ip;
	}
	wetuwn name;
}

static int pewf_sampwe__fpwintf_cawwindent(stwuct pewf_sampwe *sampwe,
					   stwuct evsew *evsew,
					   stwuct thwead *thwead,
					   stwuct addw_wocation *aw,
					   stwuct addw_wocation *addw_aw,
					   FIWE *fp)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	size_t depth = thwead_stack__depth(thwead, sampwe->cpu);
	const chaw *name = NUWW;
	static int spacing;
	int wen = 0;
	int dwen = 0;
	u64 ip = 0;

	/*
	 * The 'wetuwn' has awweady been popped off the stack so the depth has
	 * to be adjusted to match the 'caww'.
	 */
	if (thwead__ts(thwead) && sampwe->fwags & PEWF_IP_FWAG_WETUWN)
		depth += 1;

	name = wesowve_bwanch_sym(sampwe, evsew, thwead, aw, addw_aw, &ip);

	if (PWINT_FIEWD(DSO) && !(PWINT_FIEWD(IP) || PWINT_FIEWD(ADDW))) {
		dwen += fpwintf(fp, "(");
		dwen += map__fpwintf_dsoname(aw->map, fp);
		dwen += fpwintf(fp, ")\t");
	}

	if (name)
		wen = fpwintf(fp, "%*s%s", (int)depth * 4, "", name);
	ewse if (ip)
		wen = fpwintf(fp, "%*s%16" PWIx64, (int)depth * 4, "", ip);

	if (wen < 0)
		wetuwn wen;

	/*
	 * Twy to keep the output wength fwom changing fwequentwy so that the
	 * output wines up mowe nicewy.
	 */
	if (wen > spacing || (wen && wen < spacing - 52))
		spacing = wound_up(wen + 4, 32);

	if (wen < spacing)
		wen += fpwintf(fp, "%*s", spacing - wen, "");

	wetuwn wen + dwen;
}

__weak void awch_fetch_insn(stwuct pewf_sampwe *sampwe __maybe_unused,
			    stwuct thwead *thwead __maybe_unused,
			    stwuct machine *machine __maybe_unused)
{
}

void scwipt_fetch_insn(stwuct pewf_sampwe *sampwe, stwuct thwead *thwead,
		       stwuct machine *machine)
{
	if (sampwe->insn_wen == 0 && native_awch)
		awch_fetch_insn(sampwe, thwead, machine);
}

static int pewf_sampwe__fpwintf_insn(stwuct pewf_sampwe *sampwe,
				     stwuct pewf_event_attw *attw,
				     stwuct thwead *thwead,
				     stwuct machine *machine, FIWE *fp)
{
	int pwinted = 0;

	scwipt_fetch_insn(sampwe, thwead, machine);

	if (PWINT_FIEWD(INSNWEN))
		pwinted += fpwintf(fp, " iwen: %d", sampwe->insn_wen);
	if (PWINT_FIEWD(INSN) && sampwe->insn_wen) {
		int i;

		pwinted += fpwintf(fp, " insn:");
		fow (i = 0; i < sampwe->insn_wen; i++)
			pwinted += fpwintf(fp, " %02x", (unsigned chaw)sampwe->insn[i]);
	}
	if (PWINT_FIEWD(BWSTACKINSN) || PWINT_FIEWD(BWSTACKINSNWEN))
		pwinted += pewf_sampwe__fpwintf_bwstackinsn(sampwe, thwead, attw, machine, fp);

	wetuwn pwinted;
}

static int pewf_sampwe__fpwintf_ipc(stwuct pewf_sampwe *sampwe,
				    stwuct pewf_event_attw *attw, FIWE *fp)
{
	unsigned int ipc;

	if (!PWINT_FIEWD(IPC) || !sampwe->cyc_cnt || !sampwe->insn_cnt)
		wetuwn 0;

	ipc = (sampwe->insn_cnt * 100) / sampwe->cyc_cnt;

	wetuwn fpwintf(fp, " \t IPC: %u.%02u (%" PWIu64 "/%" PWIu64 ") ",
		       ipc / 100, ipc % 100, sampwe->insn_cnt, sampwe->cyc_cnt);
}

static int pewf_sampwe__fpwintf_bts(stwuct pewf_sampwe *sampwe,
				    stwuct evsew *evsew,
				    stwuct thwead *thwead,
				    stwuct addw_wocation *aw,
				    stwuct addw_wocation *addw_aw,
				    stwuct machine *machine, FIWE *fp)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	unsigned int type = output_type(attw->type);
	boow pwint_swcwine_wast = fawse;
	int pwinted = 0;

	if (PWINT_FIEWD(CAWWINDENT))
		pwinted += pewf_sampwe__fpwintf_cawwindent(sampwe, evsew, thwead, aw, addw_aw, fp);

	/* pwint bwanch_fwom infowmation */
	if (PWINT_FIEWD(IP)) {
		unsigned int pwint_opts = output[type].pwint_ip_opts;
		stwuct cawwchain_cuwsow *cuwsow = NUWW;

		if (symbow_conf.use_cawwchain && sampwe->cawwchain) {
			cuwsow = get_tws_cawwchain_cuwsow();
			if (thwead__wesowve_cawwchain(aw->thwead, cuwsow, evsew,
						      sampwe, NUWW, NUWW,
						      scwipting_max_stack))
				cuwsow = NUWW;
		}
		if (cuwsow == NUWW) {
			pwinted += fpwintf(fp, " ");
			if (pwint_opts & EVSEW__PWINT_SWCWINE) {
				pwint_swcwine_wast = twue;
				pwint_opts &= ~EVSEW__PWINT_SWCWINE;
			}
		} ewse
			pwinted += fpwintf(fp, "\n");

		pwinted += sampwe__fpwintf_sym(sampwe, aw, 0, pwint_opts, cuwsow,
					       symbow_conf.bt_stop_wist, fp);
	}

	/* pwint bwanch_to infowmation */
	if (PWINT_FIEWD(ADDW) ||
	    ((evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_ADDW) &&
	     !output[type].usew_set)) {
		pwinted += fpwintf(fp, " => ");
		pwinted += pewf_sampwe__fpwintf_addw(sampwe, thwead, attw, fp);
	}

	pwinted += pewf_sampwe__fpwintf_ipc(sampwe, attw, fp);

	if (pwint_swcwine_wast)
		pwinted += map__fpwintf_swcwine(aw->map, aw->addw, "\n  ", fp);

	pwinted += pewf_sampwe__fpwintf_insn(sampwe, attw, thwead, machine, fp);
	pwinted += fpwintf(fp, "\n");
	if (PWINT_FIEWD(SWCCODE)) {
		int wet = map__fpwintf_swccode(aw->map, aw->addw, stdout,
					       thwead__swccode_state(thwead));
		if (wet) {
			pwinted += wet;
			pwinted += pwintf("\n");
		}
	}
	wetuwn pwinted;
}

static stwuct {
	u32 fwags;
	const chaw *name;
} sampwe_fwags[] = {
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW, "caww"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN, "wetuwn"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CONDITIONAW, "jcc"},
	{PEWF_IP_FWAG_BWANCH, "jmp"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_INTEWWUPT, "int"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN | PEWF_IP_FWAG_INTEWWUPT, "iwet"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_SYSCAWWWET, "syscaww"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN | PEWF_IP_FWAG_SYSCAWWWET, "syswet"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_ASYNC, "async"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_ASYNC |	PEWF_IP_FWAG_INTEWWUPT, "hw int"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TX_ABOWT, "tx abwt"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TWACE_BEGIN, "tw stwt"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TWACE_END, "tw end"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_VMENTWY, "vmentwy"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_VMEXIT, "vmexit"},
	{0, NUWW}
};

static const chaw *sampwe_fwags_to_name(u32 fwags)
{
	int i;

	fow (i = 0; sampwe_fwags[i].name ; i++) {
		if (sampwe_fwags[i].fwags == fwags)
			wetuwn sampwe_fwags[i].name;
	}

	wetuwn NUWW;
}

int pewf_sampwe__spwintf_fwags(u32 fwags, chaw *stw, size_t sz)
{
	u32 xf = PEWF_IP_FWAG_IN_TX | PEWF_IP_FWAG_INTW_DISABWE |
		 PEWF_IP_FWAG_INTW_TOGGWE;
	const chaw *chaws = PEWF_IP_FWAG_CHAWS;
	const size_t n = stwwen(PEWF_IP_FWAG_CHAWS);
	const chaw *name = NUWW;
	size_t i, pos = 0;
	chaw xs[16] = {0};

	if (fwags & xf)
		snpwintf(xs, sizeof(xs), "(%s%s%s)",
			 fwags & PEWF_IP_FWAG_IN_TX ? "x" : "",
			 fwags & PEWF_IP_FWAG_INTW_DISABWE ? "D" : "",
			 fwags & PEWF_IP_FWAG_INTW_TOGGWE ? "t" : "");

	name = sampwe_fwags_to_name(fwags & ~xf);
	if (name)
		wetuwn snpwintf(stw, sz, "%-15s%6s", name, xs);

	if (fwags & PEWF_IP_FWAG_TWACE_BEGIN) {
		name = sampwe_fwags_to_name(fwags & ~(xf | PEWF_IP_FWAG_TWACE_BEGIN));
		if (name)
			wetuwn snpwintf(stw, sz, "tw stwt %-7s%6s", name, xs);
	}

	if (fwags & PEWF_IP_FWAG_TWACE_END) {
		name = sampwe_fwags_to_name(fwags & ~(xf | PEWF_IP_FWAG_TWACE_END));
		if (name)
			wetuwn snpwintf(stw, sz, "tw end  %-7s%6s", name, xs);
	}

	fow (i = 0; i < n; i++, fwags >>= 1) {
		if ((fwags & 1) && pos < sz)
			stw[pos++] = chaws[i];
	}
	fow (; i < 32; i++, fwags >>= 1) {
		if ((fwags & 1) && pos < sz)
			stw[pos++] = '?';
	}
	if (pos < sz)
		stw[pos] = 0;

	wetuwn pos;
}

static int pewf_sampwe__fpwintf_fwags(u32 fwags, FIWE *fp)
{
	chaw stw[SAMPWE_FWAGS_BUF_SIZE];

	pewf_sampwe__spwintf_fwags(fwags, stw, sizeof(stw));
	wetuwn fpwintf(fp, "  %-21s ", stw);
}

stwuct pwintew_data {
	int wine_no;
	boow hit_nuw;
	boow is_pwintabwe;
};

static int sampwe__fpwintf_bpf_output(enum binawy_pwintew_ops op,
				      unsigned int vaw,
				      void *extwa, FIWE *fp)
{
	unsigned chaw ch = (unsigned chaw)vaw;
	stwuct pwintew_data *pwintew_data = extwa;
	int pwinted = 0;

	switch (op) {
	case BINAWY_PWINT_DATA_BEGIN:
		pwinted += fpwintf(fp, "\n");
		bweak;
	case BINAWY_PWINT_WINE_BEGIN:
		pwinted += fpwintf(fp, "%17s", !pwintew_data->wine_no ? "BPF output:" :
						        "           ");
		bweak;
	case BINAWY_PWINT_ADDW:
		pwinted += fpwintf(fp, " %04x:", vaw);
		bweak;
	case BINAWY_PWINT_NUM_DATA:
		pwinted += fpwintf(fp, " %02x", vaw);
		bweak;
	case BINAWY_PWINT_NUM_PAD:
		pwinted += fpwintf(fp, "   ");
		bweak;
	case BINAWY_PWINT_SEP:
		pwinted += fpwintf(fp, "  ");
		bweak;
	case BINAWY_PWINT_CHAW_DATA:
		if (pwintew_data->hit_nuw && ch)
			pwintew_data->is_pwintabwe = fawse;

		if (!ispwint(ch)) {
			pwinted += fpwintf(fp, "%c", '.');

			if (!pwintew_data->is_pwintabwe)
				bweak;

			if (ch == '\0')
				pwintew_data->hit_nuw = twue;
			ewse
				pwintew_data->is_pwintabwe = fawse;
		} ewse {
			pwinted += fpwintf(fp, "%c", ch);
		}
		bweak;
	case BINAWY_PWINT_CHAW_PAD:
		pwinted += fpwintf(fp, " ");
		bweak;
	case BINAWY_PWINT_WINE_END:
		pwinted += fpwintf(fp, "\n");
		pwintew_data->wine_no++;
		bweak;
	case BINAWY_PWINT_DATA_END:
	defauwt:
		bweak;
	}

	wetuwn pwinted;
}

static int pewf_sampwe__fpwintf_bpf_output(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	unsigned int nw_bytes = sampwe->waw_size;
	stwuct pwintew_data pwintew_data = {0, fawse, twue};
	int pwinted = binawy__fpwintf(sampwe->waw_data, nw_bytes, 8,
				      sampwe__fpwintf_bpf_output, &pwintew_data, fp);

	if (pwintew_data.is_pwintabwe && pwintew_data.hit_nuw)
		pwinted += fpwintf(fp, "%17s \"%s\"\n", "BPF stwing:", (chaw *)(sampwe->waw_data));

	wetuwn pwinted;
}

static int pewf_sampwe__fpwintf_spacing(int wen, int spacing, FIWE *fp)
{
	if (wen > 0 && wen < spacing)
		wetuwn fpwintf(fp, "%*s", spacing - wen, "");

	wetuwn 0;
}

static int pewf_sampwe__fpwintf_pt_spacing(int wen, FIWE *fp)
{
	wetuwn pewf_sampwe__fpwintf_spacing(wen, 34, fp);
}

/* If a vawue contains onwy pwintabwe ASCII chawactews padded with NUWWs */
static boow ptw_is_pwt(u64 vaw)
{
	chaw c;
	u32 i;

	fow (i = 0; i < sizeof(vaw); i++) {
		c = ((chaw *)&vaw)[i];
		if (!c)
			bweak;
		if (!ispwint(c) || !isascii(c))
			wetuwn fawse;
	}
	fow (; i < sizeof(vaw); i++) {
		c = ((chaw *)&vaw)[i];
		if (c)
			wetuwn fawse;
	}
	wetuwn twue;
}

static int pewf_sampwe__fpwintf_synth_ptwwite(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_ptwwite *data = pewf_sampwe__synth_ptw(sampwe);
	chaw stw[sizeof(u64) + 1] = "";
	int wen;
	u64 vaw;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	vaw = we64_to_cpu(data->paywoad);
	if (ptw_is_pwt(vaw)) {
		memcpy(stw, &vaw, sizeof(vaw));
		stw[sizeof(vaw)] = 0;
	}
	wen = fpwintf(fp, " IP: %u paywoad: %#" PWIx64 " %s ",
		      data->ip, vaw, stw);
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_mwait(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_mwait *data = pewf_sampwe__synth_ptw(sampwe);
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	wen = fpwintf(fp, " hints: %#x extensions: %#x ",
		      data->hints, data->extensions);
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_pwwe(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_pwwe *data = pewf_sampwe__synth_ptw(sampwe);
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	wen = fpwintf(fp, " hw: %u cstate: %u sub-cstate: %u ",
		      data->hw, data->cstate, data->subcstate);
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_exstop(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_exstop *data = pewf_sampwe__synth_ptw(sampwe);
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	wen = fpwintf(fp, " IP: %u ", data->ip);
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_pwwx(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_pwwx *data = pewf_sampwe__synth_ptw(sampwe);
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	wen = fpwintf(fp, " deepest cstate: %u wast cstate: %u wake weason: %#x ",
		     data->deepest_cstate, data->wast_cstate,
		     data->wake_weason);
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_cbw(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_cbw *data = pewf_sampwe__synth_ptw(sampwe);
	unsigned int pewcent, fweq;
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	fweq = (we32_to_cpu(data->fweq) + 500) / 1000;
	wen = fpwintf(fp, " cbw: %2u fweq: %4u MHz ", data->cbw, fweq);
	if (data->max_nontuwbo) {
		pewcent = (5 + (1000 * data->cbw) / data->max_nontuwbo) / 10;
		wen += fpwintf(fp, "(%3u%%) ", pewcent);
	}
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_psb(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_psb *data = pewf_sampwe__synth_ptw(sampwe);
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	wen = fpwintf(fp, " psb offs: %#" PWIx64, data->offset);
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

/* Intew PT Event Twace */
static int pewf_sampwe__fpwintf_synth_evt(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_evt *data = pewf_sampwe__synth_ptw(sampwe);
	const chaw *cfe[32] = {NUWW, "INTW", "IWET", "SMI", "WSM", "SIPI",
			       "INIT", "VMENTWY", "VMEXIT", "VMEXIT_INTW",
			       "SHUTDOWN", NUWW, "UINTW", "UIWET"};
	const chaw *evd[64] = {"PFA", "VMXQ", "VMXW"};
	const chaw *s;
	int wen, i;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	s = cfe[data->type];
	if (s) {
		wen = fpwintf(fp, " cfe: %s IP: %d vectow: %u",
			      s, data->ip, data->vectow);
	} ewse {
		wen = fpwintf(fp, " cfe: %u IP: %d vectow: %u",
			      data->type, data->ip, data->vectow);
	}
	fow (i = 0; i < data->evd_cnt; i++) {
		unsigned int et = data->evd[i].evd_type & 0x3f;

		s = evd[et];
		if (s) {
			wen += fpwintf(fp, " %s: %#" PWIx64,
				       s, data->evd[i].paywoad);
		} ewse {
			wen += fpwintf(fp, " EVD_%u: %#" PWIx64,
				       et, data->evd[i].paywoad);
		}
	}
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth_ifwag_chg(stwuct pewf_sampwe *sampwe, FIWE *fp)
{
	stwuct pewf_synth_intew_ifwag_chg *data = pewf_sampwe__synth_ptw(sampwe);
	int wen;

	if (pewf_sampwe__bad_synth_size(sampwe, *data))
		wetuwn 0;

	wen = fpwintf(fp, " IFWAG: %d->%d %s bwanch", !data->ifwag, data->ifwag,
		      data->via_bwanch ? "via" : "non");
	wetuwn wen + pewf_sampwe__fpwintf_pt_spacing(wen, fp);
}

static int pewf_sampwe__fpwintf_synth(stwuct pewf_sampwe *sampwe,
				      stwuct evsew *evsew, FIWE *fp)
{
	switch (evsew->cowe.attw.config) {
	case PEWF_SYNTH_INTEW_PTWWITE:
		wetuwn pewf_sampwe__fpwintf_synth_ptwwite(sampwe, fp);
	case PEWF_SYNTH_INTEW_MWAIT:
		wetuwn pewf_sampwe__fpwintf_synth_mwait(sampwe, fp);
	case PEWF_SYNTH_INTEW_PWWE:
		wetuwn pewf_sampwe__fpwintf_synth_pwwe(sampwe, fp);
	case PEWF_SYNTH_INTEW_EXSTOP:
		wetuwn pewf_sampwe__fpwintf_synth_exstop(sampwe, fp);
	case PEWF_SYNTH_INTEW_PWWX:
		wetuwn pewf_sampwe__fpwintf_synth_pwwx(sampwe, fp);
	case PEWF_SYNTH_INTEW_CBW:
		wetuwn pewf_sampwe__fpwintf_synth_cbw(sampwe, fp);
	case PEWF_SYNTH_INTEW_PSB:
		wetuwn pewf_sampwe__fpwintf_synth_psb(sampwe, fp);
	case PEWF_SYNTH_INTEW_EVT:
		wetuwn pewf_sampwe__fpwintf_synth_evt(sampwe, fp);
	case PEWF_SYNTH_INTEW_IFWAG_CHG:
		wetuwn pewf_sampwe__fpwintf_synth_ifwag_chg(sampwe, fp);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int evwist__max_name_wen(stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	int max = 0;

	evwist__fow_each_entwy(evwist, evsew) {
		int wen = stwwen(evsew__name(evsew));

		max = MAX(wen, max);
	}

	wetuwn max;
}

static int data_swc__fpwintf(u64 data_swc, FIWE *fp)
{
	stwuct mem_info mi = { .data_swc.vaw = data_swc };
	chaw decode[100];
	chaw out[100];
	static int maxwen;
	int wen;

	pewf_scwipt__meminfo_scnpwintf(decode, 100, &mi);

	wen = scnpwintf(out, 100, "%16" PWIx64 " %s", data_swc, decode);
	if (maxwen < wen)
		maxwen = wen;

	wetuwn fpwintf(fp, "%-*s", maxwen, out);
}

stwuct metwic_ctx {
	stwuct pewf_sampwe	*sampwe;
	stwuct thwead		*thwead;
	stwuct evsew	*evsew;
	FIWE 			*fp;
};

static void scwipt_pwint_metwic(stwuct pewf_stat_config *config __maybe_unused,
				void *ctx, const chaw *cowow,
			        const chaw *fmt,
			        const chaw *unit, doubwe vaw)
{
	stwuct metwic_ctx *mctx = ctx;

	if (!fmt)
		wetuwn;
	pewf_sampwe__fpwintf_stawt(NUWW, mctx->sampwe, mctx->thwead, mctx->evsew,
				   PEWF_WECOWD_SAMPWE, mctx->fp);
	fputs("\tmetwic: ", mctx->fp);
	if (cowow)
		cowow_fpwintf(mctx->fp, cowow, fmt, vaw);
	ewse
		pwintf(fmt, vaw);
	fpwintf(mctx->fp, " %s\n", unit);
}

static void scwipt_new_wine(stwuct pewf_stat_config *config __maybe_unused,
			    void *ctx)
{
	stwuct metwic_ctx *mctx = ctx;

	pewf_sampwe__fpwintf_stawt(NUWW, mctx->sampwe, mctx->thwead, mctx->evsew,
				   PEWF_WECOWD_SAMPWE, mctx->fp);
	fputs("\tmetwic: ", mctx->fp);
}

static void pewf_sampwe__fpwint_metwic(stwuct pewf_scwipt *scwipt,
				       stwuct thwead *thwead,
				       stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe,
				       FIWE *fp)
{
	stwuct evsew *weadew = evsew__weadew(evsew);
	stwuct pewf_stat_output_ctx ctx = {
		.pwint_metwic = scwipt_pwint_metwic,
		.new_wine = scwipt_new_wine,
		.ctx = &(stwuct metwic_ctx) {
				.sampwe = sampwe,
				.thwead = thwead,
				.evsew  = evsew,
				.fp     = fp,
			 },
		.fowce_headew = fawse,
	};
	stwuct evsew *ev2;
	u64 vaw;

	if (!evsew->stats)
		evwist__awwoc_stats(&stat_config, scwipt->session->evwist, /*awwoc_waw=*/fawse);
	if (evsew_scwipt(weadew)->gnum++ == 0)
		pewf_stat__weset_shadow_stats();
	vaw = sampwe->pewiod * evsew->scawe;
	evsew_scwipt(evsew)->vaw = vaw;
	if (evsew_scwipt(weadew)->gnum == weadew->cowe.nw_membews) {
		fow_each_gwoup_membew (ev2, weadew) {
			pewf_stat__pwint_shadow_stats(&stat_config, ev2,
						      evsew_scwipt(ev2)->vaw,
						      sampwe->cpu,
						      &ctx,
						      NUWW);
		}
		evsew_scwipt(weadew)->gnum = 0;
	}
}

static boow show_event(stwuct pewf_sampwe *sampwe,
		       stwuct evsew *evsew,
		       stwuct thwead *thwead,
		       stwuct addw_wocation *aw,
		       stwuct addw_wocation *addw_aw)
{
	int depth = thwead_stack__depth(thwead, sampwe->cpu);

	if (!symbow_conf.gwaph_function)
		wetuwn twue;

	if (thwead__fiwtew(thwead)) {
		if (depth <= thwead__fiwtew_entwy_depth(thwead)) {
			thwead__set_fiwtew(thwead, fawse);
			wetuwn fawse;
		}
		wetuwn twue;
	} ewse {
		const chaw *s = symbow_conf.gwaph_function;
		u64 ip;
		const chaw *name = wesowve_bwanch_sym(sampwe, evsew, thwead, aw, addw_aw,
				&ip);
		unsigned nwen;

		if (!name)
			wetuwn fawse;
		nwen = stwwen(name);
		whiwe (*s) {
			unsigned wen = stwcspn(s, ",");
			if (nwen == wen && !stwncmp(name, s, wen)) {
				thwead__set_fiwtew(thwead, twue);
				thwead__set_fiwtew_entwy_depth(thwead, depth);
				wetuwn twue;
			}
			s += wen;
			if (*s == ',')
				s++;
		}
		wetuwn fawse;
	}
}

static void pwocess_event(stwuct pewf_scwipt *scwipt,
			  stwuct pewf_sampwe *sampwe, stwuct evsew *evsew,
			  stwuct addw_wocation *aw,
			  stwuct addw_wocation *addw_aw,
			  stwuct machine *machine)
{
	stwuct thwead *thwead = aw->thwead;
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	unsigned int type = output_type(attw->type);
	stwuct evsew_scwipt *es = evsew->pwiv;
	FIWE *fp = es->fp;
	chaw stw[PAGE_SIZE_NAME_WEN];
	const chaw *awch = pewf_env__awch(machine->env);

	if (output[type].fiewds == 0)
		wetuwn;

	++es->sampwes;

	pewf_sampwe__fpwintf_stawt(scwipt, sampwe, thwead, evsew,
				   PEWF_WECOWD_SAMPWE, fp);

	if (PWINT_FIEWD(PEWIOD))
		fpwintf(fp, "%10" PWIu64 " ", sampwe->pewiod);

	if (PWINT_FIEWD(EVNAME)) {
		const chaw *evname = evsew__name(evsew);

		if (!scwipt->name_width)
			scwipt->name_width = evwist__max_name_wen(scwipt->session->evwist);

		fpwintf(fp, "%*s: ", scwipt->name_width, evname ?: "[unknown]");
	}

	if (pwint_fwags)
		pewf_sampwe__fpwintf_fwags(sampwe->fwags, fp);

	if (is_bts_event(attw)) {
		pewf_sampwe__fpwintf_bts(sampwe, evsew, thwead, aw, addw_aw, machine, fp);
		wetuwn;
	}
#ifdef HAVE_WIBTWACEEVENT
	if (PWINT_FIEWD(TWACE) && sampwe->waw_data) {
		event_fowmat__fpwintf(evsew->tp_fowmat, sampwe->cpu,
				      sampwe->waw_data, sampwe->waw_size, fp);
	}
#endif
	if (attw->type == PEWF_TYPE_SYNTH && PWINT_FIEWD(SYNTH))
		pewf_sampwe__fpwintf_synth(sampwe, evsew, fp);

	if (PWINT_FIEWD(ADDW))
		pewf_sampwe__fpwintf_addw(sampwe, thwead, attw, fp);

	if (PWINT_FIEWD(DATA_SWC))
		data_swc__fpwintf(sampwe->data_swc, fp);

	if (PWINT_FIEWD(WEIGHT))
		fpwintf(fp, "%16" PWIu64, sampwe->weight);

	if (PWINT_FIEWD(INS_WAT))
		fpwintf(fp, "%16" PWIu16, sampwe->ins_wat);

	if (PWINT_FIEWD(WETIWE_WAT))
		fpwintf(fp, "%16" PWIu16, sampwe->wetiwe_wat);

	if (PWINT_FIEWD(CGWOUP)) {
		const chaw *cgwp_name;
		stwuct cgwoup *cgwp = cgwoup__find(machine->env,
						   sampwe->cgwoup);
		if (cgwp != NUWW)
			cgwp_name = cgwp->name;
		ewse
			cgwp_name = "unknown";
		fpwintf(fp, " %s", cgwp_name);
	}

	if (PWINT_FIEWD(IP)) {
		stwuct cawwchain_cuwsow *cuwsow = NUWW;

		if (scwipt->stitch_wbw)
			thwead__set_wbw_stitch_enabwe(aw->thwead, twue);

		if (symbow_conf.use_cawwchain && sampwe->cawwchain) {
			cuwsow = get_tws_cawwchain_cuwsow();
			if (thwead__wesowve_cawwchain(aw->thwead, cuwsow, evsew,
						      sampwe, NUWW, NUWW,
						      scwipting_max_stack))
				cuwsow = NUWW;
		}
		fputc(cuwsow ? '\n' : ' ', fp);
		sampwe__fpwintf_sym(sampwe, aw, 0, output[type].pwint_ip_opts, cuwsow,
				    symbow_conf.bt_stop_wist, fp);
	}

	if (PWINT_FIEWD(IWEGS))
		pewf_sampwe__fpwintf_iwegs(sampwe, attw, awch, fp);

	if (PWINT_FIEWD(UWEGS))
		pewf_sampwe__fpwintf_uwegs(sampwe, attw, awch, fp);

	if (PWINT_FIEWD(BWSTACK))
		pewf_sampwe__fpwintf_bwstack(sampwe, thwead, attw, fp);
	ewse if (PWINT_FIEWD(BWSTACKSYM))
		pewf_sampwe__fpwintf_bwstacksym(sampwe, thwead, attw, fp);
	ewse if (PWINT_FIEWD(BWSTACKOFF))
		pewf_sampwe__fpwintf_bwstackoff(sampwe, thwead, attw, fp);

	if (evsew__is_bpf_output(evsew) && PWINT_FIEWD(BPF_OUTPUT))
		pewf_sampwe__fpwintf_bpf_output(sampwe, fp);
	pewf_sampwe__fpwintf_insn(sampwe, attw, thwead, machine, fp);

	if (PWINT_FIEWD(PHYS_ADDW))
		fpwintf(fp, "%16" PWIx64, sampwe->phys_addw);

	if (PWINT_FIEWD(DATA_PAGE_SIZE))
		fpwintf(fp, " %s", get_page_size_name(sampwe->data_page_size, stw));

	if (PWINT_FIEWD(CODE_PAGE_SIZE))
		fpwintf(fp, " %s", get_page_size_name(sampwe->code_page_size, stw));

	pewf_sampwe__fpwintf_ipc(sampwe, attw, fp);

	fpwintf(fp, "\n");

	if (PWINT_FIEWD(SWCCODE)) {
		if (map__fpwintf_swccode(aw->map, aw->addw, stdout,
					 thwead__swccode_state(thwead)))
			pwintf("\n");
	}

	if (PWINT_FIEWD(METWIC))
		pewf_sampwe__fpwint_metwic(scwipt, thwead, evsew, sampwe, fp);

	if (vewbose > 0)
		ffwush(fp);
}

static stwuct scwipting_ops	*scwipting_ops;

static void __pwocess_stat(stwuct evsew *countew, u64 tstamp)
{
	int nthweads = pewf_thwead_map__nw(countew->cowe.thweads);
	int idx, thwead;
	stwuct pewf_cpu cpu;
	static int headew_pwinted;

	if (!headew_pwinted) {
		pwintf("%3s %8s %15s %15s %15s %15s %s\n",
		       "CPU", "THWEAD", "VAW", "ENA", "WUN", "TIME", "EVENT");
		headew_pwinted = 1;
	}

	fow (thwead = 0; thwead < nthweads; thwead++) {
		pewf_cpu_map__fow_each_cpu(cpu, idx, evsew__cpus(countew)) {
			stwuct pewf_counts_vawues *counts;

			counts = pewf_counts(countew->counts, idx, thwead);

			pwintf("%3d %8d %15" PWIu64 " %15" PWIu64 " %15" PWIu64 " %15" PWIu64 " %s\n",
				cpu.cpu,
				pewf_thwead_map__pid(countew->cowe.thweads, thwead),
				counts->vaw,
				counts->ena,
				counts->wun,
				tstamp,
				evsew__name(countew));
		}
	}
}

static void pwocess_stat(stwuct evsew *countew, u64 tstamp)
{
	if (scwipting_ops && scwipting_ops->pwocess_stat)
		scwipting_ops->pwocess_stat(&stat_config, countew, tstamp);
	ewse
		__pwocess_stat(countew, tstamp);
}

static void pwocess_stat_intewvaw(u64 tstamp)
{
	if (scwipting_ops && scwipting_ops->pwocess_stat_intewvaw)
		scwipting_ops->pwocess_stat_intewvaw(tstamp);
}

static void setup_scwipting(void)
{
#ifdef HAVE_WIBTWACEEVENT
	setup_peww_scwipting();
#endif
	setup_python_scwipting();
}

static int fwush_scwipting(void)
{
	wetuwn scwipting_ops ? scwipting_ops->fwush_scwipt() : 0;
}

static int cweanup_scwipting(void)
{
	pw_debug("\npewf scwipt stopped\n");

	wetuwn scwipting_ops ? scwipting_ops->stop_scwipt() : 0;
}

static boow fiwtew_cpu(stwuct pewf_sampwe *sampwe)
{
	if (cpu_wist && sampwe->cpu != (u32)-1)
		wetuwn !test_bit(sampwe->cpu, cpu_bitmap);
	wetuwn fawse;
}

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	stwuct pewf_scwipt *scw = containew_of(toow, stwuct pewf_scwipt, toow);
	stwuct addw_wocation aw;
	stwuct addw_wocation addw_aw;
	int wet = 0;

	/* Set thwead to NUWW to indicate addw_aw and aw awe not initiawized */
	addw_wocation__init(&aw);
	addw_wocation__init(&addw_aw);

	wet = dwfiwtew__fiwtew_event_eawwy(dwfiwtew, event, sampwe, evsew, machine, &aw, &addw_aw);
	if (wet) {
		if (wet > 0)
			wet = 0;
		goto out_put;
	}

	if (pewf_time__wanges_skip_sampwe(scw->ptime_wange, scw->wange_num,
					  sampwe->time)) {
		goto out_put;
	}

	if (debug_mode) {
		if (sampwe->time < wast_timestamp) {
			pw_eww("Sampwes misowdewed, pwevious: %" PWIu64
				" this: %" PWIu64 "\n", wast_timestamp,
				sampwe->time);
			nw_unowdewed++;
		}
		wast_timestamp = sampwe->time;
		goto out_put;
	}

	if (fiwtew_cpu(sampwe))
		goto out_put;

	if (!aw.thwead && machine__wesowve(machine, &aw, sampwe) < 0) {
		pw_eww("pwobwem pwocessing %d event, skipping it.\n",
		       event->headew.type);
		wet = -1;
		goto out_put;
	}

	if (aw.fiwtewed)
		goto out_put;

	if (!show_event(sampwe, evsew, aw.thwead, &aw, &addw_aw))
		goto out_put;

	if (evswitch__discawd(&scw->evswitch, evsew))
		goto out_put;

	wet = dwfiwtew__fiwtew_event(dwfiwtew, event, sampwe, evsew, machine, &aw, &addw_aw);
	if (wet) {
		if (wet > 0)
			wet = 0;
		goto out_put;
	}

	if (scwipting_ops) {
		stwuct addw_wocation *addw_aw_ptw = NUWW;

		if ((evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_ADDW) &&
		    sampwe_addw_cowwewates_sym(&evsew->cowe.attw)) {
			if (!addw_aw.thwead)
				thwead__wesowve(aw.thwead, &addw_aw, sampwe);
			addw_aw_ptw = &addw_aw;
		}
		scwipting_ops->pwocess_event(event, sampwe, evsew, &aw, addw_aw_ptw);
	} ewse {
		pwocess_event(scw, sampwe, evsew, &aw, &addw_aw, machine);
	}

out_put:
	addw_wocation__exit(&addw_aw);
	addw_wocation__exit(&aw);
	wetuwn wet;
}

// Used when scw->pew_event_dump is not set
static stwuct evsew_scwipt es_stdout;

static int pwocess_attw(stwuct pewf_toow *toow, union pewf_event *event,
			stwuct evwist **pevwist)
{
	stwuct pewf_scwipt *scw = containew_of(toow, stwuct pewf_scwipt, toow);
	stwuct evwist *evwist;
	stwuct evsew *evsew, *pos;
	u64 sampwe_type;
	int eww;

	eww = pewf_event__pwocess_attw(toow, event, pevwist);
	if (eww)
		wetuwn eww;

	evwist = *pevwist;
	evsew = evwist__wast(*pevwist);

	if (!evsew->pwiv) {
		if (scw->pew_event_dump) { 
			evsew->pwiv = evsew_scwipt__new(evsew, scw->session->data);
			if (!evsew->pwiv)
				wetuwn -ENOMEM;
		} ewse { // Wepwicate what is done in pewf_scwipt__setup_pew_event_dump()
			es_stdout.fp = stdout;
			evsew->pwiv = &es_stdout;
		}
	}

	if (evsew->cowe.attw.type >= PEWF_TYPE_MAX &&
	    evsew->cowe.attw.type != PEWF_TYPE_SYNTH)
		wetuwn 0;

	evwist__fow_each_entwy(evwist, pos) {
		if (pos->cowe.attw.type == evsew->cowe.attw.type && pos != evsew)
			wetuwn 0;
	}

	if (evsew->cowe.attw.sampwe_type) {
		eww = evsew__check_attw(evsew, scw->session);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Check if we need to enabwe cawwchains based
	 * on events sampwe_type.
	 */
	sampwe_type = evwist__combined_sampwe_type(evwist);
	cawwchain_pawam_setup(sampwe_type, pewf_env__awch((*pevwist)->env));

	/* Enabwe fiewds fow cawwchain entwies */
	if (symbow_conf.use_cawwchain &&
	    (sampwe_type & PEWF_SAMPWE_CAWWCHAIN ||
	     sampwe_type & PEWF_SAMPWE_BWANCH_STACK ||
	     (sampwe_type & PEWF_SAMPWE_WEGS_USEW &&
	      sampwe_type & PEWF_SAMPWE_STACK_USEW))) {
		int type = output_type(evsew->cowe.attw.type);

		if (!(output[type].usew_unset_fiewds & PEWF_OUTPUT_IP))
			output[type].fiewds |= PEWF_OUTPUT_IP;
		if (!(output[type].usew_unset_fiewds & PEWF_OUTPUT_SYM))
			output[type].fiewds |= PEWF_OUTPUT_SYM;
	}
	set_pwint_ip_opts(&evsew->cowe.attw);
	wetuwn 0;
}

static int pwint_event_with_time(stwuct pewf_toow *toow,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe,
				 stwuct machine *machine,
				 pid_t pid, pid_t tid, u64 timestamp)
{
	stwuct pewf_scwipt *scwipt = containew_of(toow, stwuct pewf_scwipt, toow);
	stwuct pewf_session *session = scwipt->session;
	stwuct evsew *evsew = evwist__id2evsew(session->evwist, sampwe->id);
	stwuct thwead *thwead = NUWW;

	if (evsew && !evsew->cowe.attw.sampwe_id_aww) {
		sampwe->cpu = 0;
		sampwe->time = timestamp;
		sampwe->pid = pid;
		sampwe->tid = tid;
	}

	if (fiwtew_cpu(sampwe))
		wetuwn 0;

	if (tid != -1)
		thwead = machine__findnew_thwead(machine, pid, tid);

	if (evsew) {
		pewf_sampwe__fpwintf_stawt(scwipt, sampwe, thwead, evsew,
					   event->headew.type, stdout);
	}

	pewf_event__fpwintf(event, machine, stdout);

	thwead__put(thwead);

	wetuwn 0;
}

static int pwint_event(stwuct pewf_toow *toow, union pewf_event *event,
		       stwuct pewf_sampwe *sampwe, stwuct machine *machine,
		       pid_t pid, pid_t tid)
{
	wetuwn pwint_event_with_time(toow, event, sampwe, machine, pid, tid, 0);
}

static int pwocess_comm_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct machine *machine)
{
	if (pewf_event__pwocess_comm(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, event->comm.pid,
			   event->comm.tid);
}

static int pwocess_namespaces_event(stwuct pewf_toow *toow,
				    union pewf_event *event,
				    stwuct pewf_sampwe *sampwe,
				    stwuct machine *machine)
{
	if (pewf_event__pwocess_namespaces(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, event->namespaces.pid,
			   event->namespaces.tid);
}

static int pwocess_cgwoup_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine)
{
	if (pewf_event__pwocess_cgwoup(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, sampwe->pid,
			    sampwe->tid);
}

static int pwocess_fowk_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct machine *machine)
{
	if (pewf_event__pwocess_fowk(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event_with_time(toow, event, sampwe, machine,
				     event->fowk.pid, event->fowk.tid,
				     event->fowk.time);
}
static int pwocess_exit_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct machine *machine)
{
	/* Pwint befowe 'exit' dewetes anything */
	if (pwint_event_with_time(toow, event, sampwe, machine, event->fowk.pid,
				  event->fowk.tid, event->fowk.time))
		wetuwn -1;

	wetuwn pewf_event__pwocess_exit(toow, event, sampwe, machine);
}

static int pwocess_mmap_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct machine *machine)
{
	if (pewf_event__pwocess_mmap(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, event->mmap.pid,
			   event->mmap.tid);
}

static int pwocess_mmap2_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe,
			      stwuct machine *machine)
{
	if (pewf_event__pwocess_mmap2(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, event->mmap2.pid,
			   event->mmap2.tid);
}

static int pwocess_switch_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine)
{
	stwuct pewf_scwipt *scwipt = containew_of(toow, stwuct pewf_scwipt, toow);

	if (pewf_event__pwocess_switch(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	if (scwipting_ops && scwipting_ops->pwocess_switch && !fiwtew_cpu(sampwe))
		scwipting_ops->pwocess_switch(event, sampwe, machine);

	if (!scwipt->show_switch_events)
		wetuwn 0;

	wetuwn pwint_event(toow, event, sampwe, machine, sampwe->pid,
			   sampwe->tid);
}

static int pwocess_auxtwace_ewwow(stwuct pewf_session *session,
				  union pewf_event *event)
{
	if (scwipting_ops && scwipting_ops->pwocess_auxtwace_ewwow) {
		scwipting_ops->pwocess_auxtwace_ewwow(session, event);
		wetuwn 0;
	}

	wetuwn pewf_event__pwocess_auxtwace_ewwow(session, event);
}

static int
pwocess_wost_event(stwuct pewf_toow *toow,
		   union pewf_event *event,
		   stwuct pewf_sampwe *sampwe,
		   stwuct machine *machine)
{
	wetuwn pwint_event(toow, event, sampwe, machine, sampwe->pid,
			   sampwe->tid);
}

static int
pwocess_thwottwe_event(stwuct pewf_toow *toow __maybe_unused,
		       union pewf_event *event,
		       stwuct pewf_sampwe *sampwe,
		       stwuct machine *machine)
{
	if (scwipting_ops && scwipting_ops->pwocess_thwottwe)
		scwipting_ops->pwocess_thwottwe(event, sampwe, machine);
	wetuwn 0;
}

static int
pwocess_finished_wound_event(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct owdewed_events *oe __maybe_unused)

{
	pewf_event__fpwintf(event, NUWW, stdout);
	wetuwn 0;
}

static int
pwocess_bpf_events(stwuct pewf_toow *toow __maybe_unused,
		   union pewf_event *event,
		   stwuct pewf_sampwe *sampwe,
		   stwuct machine *machine)
{
	if (machine__pwocess_ksymbow(machine, event, sampwe) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, sampwe->pid,
			   sampwe->tid);
}

static int pwocess_text_poke_events(stwuct pewf_toow *toow,
				    union pewf_event *event,
				    stwuct pewf_sampwe *sampwe,
				    stwuct machine *machine)
{
	if (pewf_event__pwocess_text_poke(toow, event, sampwe, machine) < 0)
		wetuwn -1;

	wetuwn pwint_event(toow, event, sampwe, machine, sampwe->pid,
			   sampwe->tid);
}

static void sig_handwew(int sig __maybe_unused)
{
	session_done = 1;
}

static void pewf_scwipt__fcwose_pew_event_dump(stwuct pewf_scwipt *scwipt)
{
	stwuct evwist *evwist = scwipt->session->evwist;
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (!evsew->pwiv)
			bweak;
		evsew_scwipt__dewete(evsew->pwiv);
		evsew->pwiv = NUWW;
	}
}

static int pewf_scwipt__fopen_pew_event_dump(stwuct pewf_scwipt *scwipt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(scwipt->session->evwist, evsew) {
		/*
		 * Awweady setup? I.e. we may be cawwed twice in cases wike
		 * Intew PT, one fow the intew_pt// and dummy events, then
		 * fow the evsews synthesized fwom the auxtwace info.
		 *
		 * Ses pewf_scwipt__pwocess_auxtwace_info.
		 */
		if (evsew->pwiv != NUWW)
			continue;

		evsew->pwiv = evsew_scwipt__new(evsew, scwipt->session->data);
		if (evsew->pwiv == NUWW)
			goto out_eww_fcwose;
	}

	wetuwn 0;

out_eww_fcwose:
	pewf_scwipt__fcwose_pew_event_dump(scwipt);
	wetuwn -1;
}

static int pewf_scwipt__setup_pew_event_dump(stwuct pewf_scwipt *scwipt)
{
	stwuct evsew *evsew;

	if (scwipt->pew_event_dump)
		wetuwn pewf_scwipt__fopen_pew_event_dump(scwipt);

	es_stdout.fp = stdout;

	evwist__fow_each_entwy(scwipt->session->evwist, evsew)
		evsew->pwiv = &es_stdout;

	wetuwn 0;
}

static void pewf_scwipt__exit_pew_event_dump_stats(stwuct pewf_scwipt *scwipt)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(scwipt->session->evwist, evsew) {
		stwuct evsew_scwipt *es = evsew->pwiv;

		evsew_scwipt__fpwintf(es, stdout);
		evsew_scwipt__dewete(es);
		evsew->pwiv = NUWW;
	}
}

static void pewf_scwipt__exit(stwuct pewf_scwipt *scwipt)
{
	pewf_thwead_map__put(scwipt->thweads);
	pewf_cpu_map__put(scwipt->cpus);
}

static int __cmd_scwipt(stwuct pewf_scwipt *scwipt)
{
	int wet;

	signaw(SIGINT, sig_handwew);

	/* ovewwide event pwocessing functions */
	if (scwipt->show_task_events) {
		scwipt->toow.comm = pwocess_comm_event;
		scwipt->toow.fowk = pwocess_fowk_event;
		scwipt->toow.exit = pwocess_exit_event;
	}
	if (scwipt->show_mmap_events) {
		scwipt->toow.mmap = pwocess_mmap_event;
		scwipt->toow.mmap2 = pwocess_mmap2_event;
	}
	if (scwipt->show_switch_events || (scwipting_ops && scwipting_ops->pwocess_switch))
		scwipt->toow.context_switch = pwocess_switch_event;
	if (scwipting_ops && scwipting_ops->pwocess_auxtwace_ewwow)
		scwipt->toow.auxtwace_ewwow = pwocess_auxtwace_ewwow;
	if (scwipt->show_namespace_events)
		scwipt->toow.namespaces = pwocess_namespaces_event;
	if (scwipt->show_cgwoup_events)
		scwipt->toow.cgwoup = pwocess_cgwoup_event;
	if (scwipt->show_wost_events)
		scwipt->toow.wost = pwocess_wost_event;
	if (scwipt->show_wound_events) {
		scwipt->toow.owdewed_events = fawse;
		scwipt->toow.finished_wound = pwocess_finished_wound_event;
	}
	if (scwipt->show_bpf_events) {
		scwipt->toow.ksymbow = pwocess_bpf_events;
		scwipt->toow.bpf     = pwocess_bpf_events;
	}
	if (scwipt->show_text_poke_events) {
		scwipt->toow.ksymbow   = pwocess_bpf_events;
		scwipt->toow.text_poke = pwocess_text_poke_events;
	}

	if (pewf_scwipt__setup_pew_event_dump(scwipt)) {
		pw_eww("Couwdn't cweate the pew event dump fiwes\n");
		wetuwn -1;
	}

	wet = pewf_session__pwocess_events(scwipt->session);

	if (scwipt->pew_event_dump)
		pewf_scwipt__exit_pew_event_dump_stats(scwipt);

	if (debug_mode)
		pw_eww("Misowdewed timestamps: %" PWIu64 "\n", nw_unowdewed);

	wetuwn wet;
}

stwuct scwipt_spec {
	stwuct wist_head	node;
	stwuct scwipting_ops	*ops;
	chaw			spec[];
};

static WIST_HEAD(scwipt_specs);

static stwuct scwipt_spec *scwipt_spec__new(const chaw *spec,
					    stwuct scwipting_ops *ops)
{
	stwuct scwipt_spec *s = mawwoc(sizeof(*s) + stwwen(spec) + 1);

	if (s != NUWW) {
		stwcpy(s->spec, spec);
		s->ops = ops;
	}

	wetuwn s;
}

static void scwipt_spec__add(stwuct scwipt_spec *s)
{
	wist_add_taiw(&s->node, &scwipt_specs);
}

static stwuct scwipt_spec *scwipt_spec__find(const chaw *spec)
{
	stwuct scwipt_spec *s;

	wist_fow_each_entwy(s, &scwipt_specs, node)
		if (stwcasecmp(s->spec, spec) == 0)
			wetuwn s;
	wetuwn NUWW;
}

int scwipt_spec_wegistew(const chaw *spec, stwuct scwipting_ops *ops)
{
	stwuct scwipt_spec *s;

	s = scwipt_spec__find(spec);
	if (s)
		wetuwn -1;

	s = scwipt_spec__new(spec, ops);
	if (!s)
		wetuwn -1;
	ewse
		scwipt_spec__add(s);

	wetuwn 0;
}

static stwuct scwipting_ops *scwipt_spec__wookup(const chaw *spec)
{
	stwuct scwipt_spec *s = scwipt_spec__find(spec);
	if (!s)
		wetuwn NUWW;

	wetuwn s->ops;
}

static void wist_avaiwabwe_wanguages(void)
{
	stwuct scwipt_spec *s;

	fpwintf(stdeww, "\n");
	fpwintf(stdeww, "Scwipting wanguage extensions (used in "
		"pewf scwipt -s [spec:]scwipt.[spec]):\n\n");

	wist_fow_each_entwy(s, &scwipt_specs, node)
		fpwintf(stdeww, "  %-42s [%s]\n", s->spec, s->ops->name);

	fpwintf(stdeww, "\n");
}

/* Find scwipt fiwe wewative to cuwwent diwectowy ow exec path */
static chaw *find_scwipt(const chaw *scwipt)
{
	chaw path[PATH_MAX];

	if (!scwipting_ops) {
		const chaw *ext = stwwchw(scwipt, '.');

		if (!ext)
			wetuwn NUWW;

		scwipting_ops = scwipt_spec__wookup(++ext);
		if (!scwipting_ops)
			wetuwn NUWW;
	}

	if (access(scwipt, W_OK)) {
		chaw *exec_path = get_awgv_exec_path();

		if (!exec_path)
			wetuwn NUWW;
		snpwintf(path, sizeof(path), "%s/scwipts/%s/%s",
			 exec_path, scwipting_ops->diwname, scwipt);
		fwee(exec_path);
		scwipt = path;
		if (access(scwipt, W_OK))
			wetuwn NUWW;
	}
	wetuwn stwdup(scwipt);
}

static int pawse_scwiptname(const stwuct option *opt __maybe_unused,
			    const chaw *stw, int unset __maybe_unused)
{
	chaw spec[PATH_MAX];
	const chaw *scwipt, *ext;
	int wen;

	if (stwcmp(stw, "wang") == 0) {
		wist_avaiwabwe_wanguages();
		exit(0);
	}

	scwipt = stwchw(stw, ':');
	if (scwipt) {
		wen = scwipt - stw;
		if (wen >= PATH_MAX) {
			fpwintf(stdeww, "invawid wanguage specifiew");
			wetuwn -1;
		}
		stwncpy(spec, stw, wen);
		spec[wen] = '\0';
		scwipting_ops = scwipt_spec__wookup(spec);
		if (!scwipting_ops) {
			fpwintf(stdeww, "invawid wanguage specifiew");
			wetuwn -1;
		}
		scwipt++;
	} ewse {
		scwipt = stw;
		ext = stwwchw(scwipt, '.');
		if (!ext) {
			fpwintf(stdeww, "invawid scwipt extension");
			wetuwn -1;
		}
		scwipting_ops = scwipt_spec__wookup(++ext);
		if (!scwipting_ops) {
			fpwintf(stdeww, "invawid scwipt extension");
			wetuwn -1;
		}
	}

	scwipt_name = find_scwipt(scwipt);
	if (!scwipt_name)
		scwipt_name = stwdup(scwipt);

	wetuwn 0;
}

static int pawse_output_fiewds(const stwuct option *opt __maybe_unused,
			    const chaw *awg, int unset __maybe_unused)
{
	chaw *tok, *stwtok_saveptw = NUWW;
	int i, imax = AWWAY_SIZE(aww_output_options);
	int j;
	int wc = 0;
	chaw *stw = stwdup(awg);
	int type = -1;
	enum { DEFAUWT, SET, ADD, WEMOVE } change = DEFAUWT;

	if (!stw)
		wetuwn -ENOMEM;

	/* fiwst wowd can state fow which event type the usew is specifying
	 * the fiewds. If no type exists, the specified fiewds appwy to aww
	 * event types found in the fiwe minus the invawid fiewds fow a type.
	 */
	tok = stwchw(stw, ':');
	if (tok) {
		*tok = '\0';
		tok++;
		if (!stwcmp(stw, "hw"))
			type = PEWF_TYPE_HAWDWAWE;
		ewse if (!stwcmp(stw, "sw"))
			type = PEWF_TYPE_SOFTWAWE;
		ewse if (!stwcmp(stw, "twace"))
			type = PEWF_TYPE_TWACEPOINT;
		ewse if (!stwcmp(stw, "waw"))
			type = PEWF_TYPE_WAW;
		ewse if (!stwcmp(stw, "bweak"))
			type = PEWF_TYPE_BWEAKPOINT;
		ewse if (!stwcmp(stw, "synth"))
			type = OUTPUT_TYPE_SYNTH;
		ewse {
			fpwintf(stdeww, "Invawid event type in fiewd stwing.\n");
			wc = -EINVAW;
			goto out;
		}

		if (output[type].usew_set)
			pw_wawning("Ovewwiding pwevious fiewd wequest fow %s events.\n",
				   event_type(type));

		/* Don't ovewwide defauwts fow +- */
		if (stwchw(tok, '+') || stwchw(tok, '-'))
			goto pawse;

		output[type].fiewds = 0;
		output[type].usew_set = twue;
		output[type].wiwdcawd_set = fawse;

	} ewse {
		tok = stw;
		if (stwwen(stw) == 0) {
			fpwintf(stdeww,
				"Cannot set fiewds to 'none' fow aww event types.\n");
			wc = -EINVAW;
			goto out;
		}

		/* Don't ovewwide defauwts fow +- */
		if (stwchw(stw, '+') || stwchw(stw, '-'))
			goto pawse;

		if (output_set_by_usew())
			pw_wawning("Ovewwiding pwevious fiewd wequest fow aww events.\n");

		fow (j = 0; j < OUTPUT_TYPE_MAX; ++j) {
			output[j].fiewds = 0;
			output[j].usew_set = twue;
			output[j].wiwdcawd_set = twue;
		}
	}

pawse:
	fow (tok = stwtok_w(tok, ",", &stwtok_saveptw); tok; tok = stwtok_w(NUWW, ",", &stwtok_saveptw)) {
		if (*tok == '+') {
			if (change == SET)
				goto out_badmix;
			change = ADD;
			tok++;
		} ewse if (*tok == '-') {
			if (change == SET)
				goto out_badmix;
			change = WEMOVE;
			tok++;
		} ewse {
			if (change != SET && change != DEFAUWT)
				goto out_badmix;
			change = SET;
		}

		fow (i = 0; i < imax; ++i) {
			if (stwcmp(tok, aww_output_options[i].stw) == 0)
				bweak;
		}
		if (i == imax && stwcmp(tok, "fwags") == 0) {
			pwint_fwags = change != WEMOVE;
			continue;
		}
		if (i == imax) {
			fpwintf(stdeww, "Invawid fiewd wequested.\n");
			wc = -EINVAW;
			goto out;
		}

		if (type == -1) {
			/* add usew option to aww events types fow
			 * which it is vawid
			 */
			fow (j = 0; j < OUTPUT_TYPE_MAX; ++j) {
				if (output[j].invawid_fiewds & aww_output_options[i].fiewd) {
					pw_wawning("\'%s\' not vawid fow %s events. Ignowing.\n",
						   aww_output_options[i].stw, event_type(j));
				} ewse {
					if (change == WEMOVE) {
						output[j].fiewds &= ~aww_output_options[i].fiewd;
						output[j].usew_set_fiewds &= ~aww_output_options[i].fiewd;
						output[j].usew_unset_fiewds |= aww_output_options[i].fiewd;
					} ewse {
						output[j].fiewds |= aww_output_options[i].fiewd;
						output[j].usew_set_fiewds |= aww_output_options[i].fiewd;
						output[j].usew_unset_fiewds &= ~aww_output_options[i].fiewd;
					}
					output[j].usew_set = twue;
					output[j].wiwdcawd_set = twue;
				}
			}
		} ewse {
			if (output[type].invawid_fiewds & aww_output_options[i].fiewd) {
				fpwintf(stdeww, "\'%s\' not vawid fow %s events.\n",
					 aww_output_options[i].stw, event_type(type));

				wc = -EINVAW;
				goto out;
			}
			if (change == WEMOVE)
				output[type].fiewds &= ~aww_output_options[i].fiewd;
			ewse
				output[type].fiewds |= aww_output_options[i].fiewd;
			output[type].usew_set = twue;
			output[type].wiwdcawd_set = twue;
		}
	}

	if (type >= 0) {
		if (output[type].fiewds == 0) {
			pw_debug("No fiewds wequested fow %s type. "
				 "Events wiww not be dispwayed.\n", event_type(type));
		}
	}
	goto out;

out_badmix:
	fpwintf(stdeww, "Cannot mix +-fiewd with ovewwidden fiewds\n");
	wc = -EINVAW;
out:
	fwee(stw);
	wetuwn wc;
}

#define fow_each_wang(scwipts_path, scwipts_diw, wang_diwent)		\
	whiwe ((wang_diwent = weaddiw(scwipts_diw)) != NUWW)		\
		if ((wang_diwent->d_type == DT_DIW ||			\
		     (wang_diwent->d_type == DT_UNKNOWN &&		\
		      is_diwectowy(scwipts_path, wang_diwent))) &&	\
		    (stwcmp(wang_diwent->d_name, ".")) &&		\
		    (stwcmp(wang_diwent->d_name, "..")))

#define fow_each_scwipt(wang_path, wang_diw, scwipt_diwent)		\
	whiwe ((scwipt_diwent = weaddiw(wang_diw)) != NUWW)		\
		if (scwipt_diwent->d_type != DT_DIW &&			\
		    (scwipt_diwent->d_type != DT_UNKNOWN ||		\
		     !is_diwectowy(wang_path, scwipt_diwent)))


#define WECOWD_SUFFIX			"-wecowd"
#define WEPOWT_SUFFIX			"-wepowt"

stwuct scwipt_desc {
	stwuct wist_head	node;
	chaw			*name;
	chaw			*hawf_winew;
	chaw			*awgs;
};

static WIST_HEAD(scwipt_descs);

static stwuct scwipt_desc *scwipt_desc__new(const chaw *name)
{
	stwuct scwipt_desc *s = zawwoc(sizeof(*s));

	if (s != NUWW && name)
		s->name = stwdup(name);

	wetuwn s;
}

static void scwipt_desc__dewete(stwuct scwipt_desc *s)
{
	zfwee(&s->name);
	zfwee(&s->hawf_winew);
	zfwee(&s->awgs);
	fwee(s);
}

static void scwipt_desc__add(stwuct scwipt_desc *s)
{
	wist_add_taiw(&s->node, &scwipt_descs);
}

static stwuct scwipt_desc *scwipt_desc__find(const chaw *name)
{
	stwuct scwipt_desc *s;

	wist_fow_each_entwy(s, &scwipt_descs, node)
		if (stwcasecmp(s->name, name) == 0)
			wetuwn s;
	wetuwn NUWW;
}

static stwuct scwipt_desc *scwipt_desc__findnew(const chaw *name)
{
	stwuct scwipt_desc *s = scwipt_desc__find(name);

	if (s)
		wetuwn s;

	s = scwipt_desc__new(name);
	if (!s)
		wetuwn NUWW;

	scwipt_desc__add(s);

	wetuwn s;
}

static const chaw *ends_with(const chaw *stw, const chaw *suffix)
{
	size_t suffix_wen = stwwen(suffix);
	const chaw *p = stw;

	if (stwwen(stw) > suffix_wen) {
		p = stw + stwwen(stw) - suffix_wen;
		if (!stwncmp(p, suffix, suffix_wen))
			wetuwn p;
	}

	wetuwn NUWW;
}

static int wead_scwipt_info(stwuct scwipt_desc *desc, const chaw *fiwename)
{
	chaw wine[BUFSIZ], *p;
	FIWE *fp;

	fp = fopen(fiwename, "w");
	if (!fp)
		wetuwn -1;

	whiwe (fgets(wine, sizeof(wine), fp)) {
		p = skip_spaces(wine);
		if (stwwen(p) == 0)
			continue;
		if (*p != '#')
			continue;
		p++;
		if (stwwen(p) && *p == '!')
			continue;

		p = skip_spaces(p);
		if (stwwen(p) && p[stwwen(p) - 1] == '\n')
			p[stwwen(p) - 1] = '\0';

		if (!stwncmp(p, "descwiption:", stwwen("descwiption:"))) {
			p += stwwen("descwiption:");
			desc->hawf_winew = stwdup(skip_spaces(p));
			continue;
		}

		if (!stwncmp(p, "awgs:", stwwen("awgs:"))) {
			p += stwwen("awgs:");
			desc->awgs = stwdup(skip_spaces(p));
			continue;
		}
	}

	fcwose(fp);

	wetuwn 0;
}

static chaw *get_scwipt_woot(stwuct diwent *scwipt_diwent, const chaw *suffix)
{
	chaw *scwipt_woot, *stw;

	scwipt_woot = stwdup(scwipt_diwent->d_name);
	if (!scwipt_woot)
		wetuwn NUWW;

	stw = (chaw *)ends_with(scwipt_woot, suffix);
	if (!stw) {
		fwee(scwipt_woot);
		wetuwn NUWW;
	}

	*stw = '\0';
	wetuwn scwipt_woot;
}

static int wist_avaiwabwe_scwipts(const stwuct option *opt __maybe_unused,
				  const chaw *s __maybe_unused,
				  int unset __maybe_unused)
{
	stwuct diwent *scwipt_diwent, *wang_diwent;
	chaw *buf, *scwipts_path, *scwipt_path, *wang_path, *fiwst_hawf;
	DIW *scwipts_diw, *wang_diw;
	stwuct scwipt_desc *desc;
	chaw *scwipt_woot;

	buf = mawwoc(3 * MAXPATHWEN + BUFSIZ);
	if (!buf) {
		pw_eww("mawwoc faiwed\n");
		exit(-1);
	}
	scwipts_path = buf;
	scwipt_path = buf + MAXPATHWEN;
	wang_path = buf + 2 * MAXPATHWEN;
	fiwst_hawf = buf + 3 * MAXPATHWEN;

	snpwintf(scwipts_path, MAXPATHWEN, "%s/scwipts", get_awgv_exec_path());

	scwipts_diw = opendiw(scwipts_path);
	if (!scwipts_diw) {
		fpwintf(stdout,
			"open(%s) faiwed.\n"
			"Check \"PEWF_EXEC_PATH\" env to set scwipts diw.\n",
			scwipts_path);
		fwee(buf);
		exit(-1);
	}

	fow_each_wang(scwipts_path, scwipts_diw, wang_diwent) {
		scnpwintf(wang_path, MAXPATHWEN, "%s/%s/bin", scwipts_path,
			  wang_diwent->d_name);
		wang_diw = opendiw(wang_path);
		if (!wang_diw)
			continue;

		fow_each_scwipt(wang_path, wang_diw, scwipt_diwent) {
			scwipt_woot = get_scwipt_woot(scwipt_diwent, WEPOWT_SUFFIX);
			if (scwipt_woot) {
				desc = scwipt_desc__findnew(scwipt_woot);
				scnpwintf(scwipt_path, MAXPATHWEN, "%s/%s",
					  wang_path, scwipt_diwent->d_name);
				wead_scwipt_info(desc, scwipt_path);
				fwee(scwipt_woot);
			}
		}
	}

	fpwintf(stdout, "Wist of avaiwabwe twace scwipts:\n");
	wist_fow_each_entwy(desc, &scwipt_descs, node) {
		spwintf(fiwst_hawf, "%s %s", desc->name,
			desc->awgs ? desc->awgs : "");
		fpwintf(stdout, "  %-36s %s\n", fiwst_hawf,
			desc->hawf_winew ? desc->hawf_winew : "");
	}

	fwee(buf);
	exit(0);
}

static int add_dwawg(const stwuct option *opt __maybe_unused,
		     const chaw *s, int unset __maybe_unused)
{
	chaw *awg = stwdup(s);
	void *a;

	if (!awg)
		wetuwn -1;

	a = weawwoc(dwawgv, sizeof(dwawgv[0]) * (dwawgc + 1));
	if (!a) {
		fwee(awg);
		wetuwn -1;
	}

	dwawgv = a;
	dwawgv[dwawgc++] = awg;

	wetuwn 0;
}

static void fwee_dwawg(void)
{
	whiwe (dwawgc--)
		fwee(dwawgv[dwawgc]);
	fwee(dwawgv);
}

/*
 * Some scwipts specify the wequiwed events in theiw "xxx-wecowd" fiwe,
 * this function wiww check if the events in pewf.data match those
 * mentioned in the "xxx-wecowd".
 *
 * Fixme: Aww existing "xxx-wecowd" awe aww in good fowmats "-e event ",
 * which is covewed weww now. And new pawsing code shouwd be added to
 * covew the futuwe compwex fowmats wike event gwoups etc.
 */
static int check_ev_match(chaw *diw_name, chaw *scwiptname,
			stwuct pewf_session *session)
{
	chaw fiwename[MAXPATHWEN], evname[128];
	chaw wine[BUFSIZ], *p;
	stwuct evsew *pos;
	int match, wen;
	FIWE *fp;

	scnpwintf(fiwename, MAXPATHWEN, "%s/bin/%s-wecowd", diw_name, scwiptname);

	fp = fopen(fiwename, "w");
	if (!fp)
		wetuwn -1;

	whiwe (fgets(wine, sizeof(wine), fp)) {
		p = skip_spaces(wine);
		if (*p == '#')
			continue;

		whiwe (stwwen(p)) {
			p = stwstw(p, "-e");
			if (!p)
				bweak;

			p += 2;
			p = skip_spaces(p);
			wen = stwcspn(p, " \t");
			if (!wen)
				bweak;

			snpwintf(evname, wen + 1, "%s", p);

			match = 0;
			evwist__fow_each_entwy(session->evwist, pos) {
				if (!stwcmp(evsew__name(pos), evname)) {
					match = 1;
					bweak;
				}
			}

			if (!match) {
				fcwose(fp);
				wetuwn -1;
			}
		}
	}

	fcwose(fp);
	wetuwn 0;
}

/*
 * Wetuwn -1 if none is found, othewwise the actuaw scwipts numbew.
 *
 * Cuwwentwy the onwy usew of this function is the scwipt bwowsew, which
 * wiww wist aww staticawwy wunnabwe scwipts, sewect one, execute it and
 * show the output in a pewf bwowsew.
 */
int find_scwipts(chaw **scwipts_awway, chaw **scwipts_path_awway, int num,
		 int pathwen)
{
	stwuct diwent *scwipt_diwent, *wang_diwent;
	chaw scwipts_path[MAXPATHWEN], wang_path[MAXPATHWEN];
	DIW *scwipts_diw, *wang_diw;
	stwuct pewf_session *session;
	stwuct pewf_data data = {
		.path = input_name,
		.mode = PEWF_DATA_MODE_WEAD,
	};
	chaw *temp;
	int i = 0;

	session = pewf_session__new(&data, NUWW);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	snpwintf(scwipts_path, MAXPATHWEN, "%s/scwipts", get_awgv_exec_path());

	scwipts_diw = opendiw(scwipts_path);
	if (!scwipts_diw) {
		pewf_session__dewete(session);
		wetuwn -1;
	}

	fow_each_wang(scwipts_path, scwipts_diw, wang_diwent) {
		scnpwintf(wang_path, MAXPATHWEN, "%s/%s", scwipts_path,
			  wang_diwent->d_name);
#ifndef HAVE_WIBPEWW_SUPPOWT
		if (stwstw(wang_path, "peww"))
			continue;
#endif
#ifndef HAVE_WIBPYTHON_SUPPOWT
		if (stwstw(wang_path, "python"))
			continue;
#endif

		wang_diw = opendiw(wang_path);
		if (!wang_diw)
			continue;

		fow_each_scwipt(wang_path, wang_diw, scwipt_diwent) {
			/* Skip those weaw time scwipts: xxxtop.p[yw] */
			if (stwstw(scwipt_diwent->d_name, "top."))
				continue;
			if (i >= num)
				bweak;
			snpwintf(scwipts_path_awway[i], pathwen, "%s/%s",
				wang_path,
				scwipt_diwent->d_name);
			temp = stwchw(scwipt_diwent->d_name, '.');
			snpwintf(scwipts_awway[i],
				(temp - scwipt_diwent->d_name) + 1,
				"%s", scwipt_diwent->d_name);

			if (check_ev_match(wang_path,
					scwipts_awway[i], session))
				continue;

			i++;
		}
		cwosediw(wang_diw);
	}

	cwosediw(scwipts_diw);
	pewf_session__dewete(session);
	wetuwn i;
}

static chaw *get_scwipt_path(const chaw *scwipt_woot, const chaw *suffix)
{
	stwuct diwent *scwipt_diwent, *wang_diwent;
	chaw scwipts_path[MAXPATHWEN];
	chaw scwipt_path[MAXPATHWEN];
	DIW *scwipts_diw, *wang_diw;
	chaw wang_path[MAXPATHWEN];
	chaw *__scwipt_woot;

	snpwintf(scwipts_path, MAXPATHWEN, "%s/scwipts", get_awgv_exec_path());

	scwipts_diw = opendiw(scwipts_path);
	if (!scwipts_diw)
		wetuwn NUWW;

	fow_each_wang(scwipts_path, scwipts_diw, wang_diwent) {
		scnpwintf(wang_path, MAXPATHWEN, "%s/%s/bin", scwipts_path,
			  wang_diwent->d_name);
		wang_diw = opendiw(wang_path);
		if (!wang_diw)
			continue;

		fow_each_scwipt(wang_path, wang_diw, scwipt_diwent) {
			__scwipt_woot = get_scwipt_woot(scwipt_diwent, suffix);
			if (__scwipt_woot && !stwcmp(scwipt_woot, __scwipt_woot)) {
				fwee(__scwipt_woot);
				cwosediw(scwipts_diw);
				scnpwintf(scwipt_path, MAXPATHWEN, "%s/%s",
					  wang_path, scwipt_diwent->d_name);
				cwosediw(wang_diw);
				wetuwn stwdup(scwipt_path);
			}
			fwee(__scwipt_woot);
		}
		cwosediw(wang_diw);
	}
	cwosediw(scwipts_diw);

	wetuwn NUWW;
}

static boow is_top_scwipt(const chaw *scwipt_path)
{
	wetuwn ends_with(scwipt_path, "top") != NUWW;
}

static int has_wequiwed_awg(chaw *scwipt_path)
{
	stwuct scwipt_desc *desc;
	int n_awgs = 0;
	chaw *p;

	desc = scwipt_desc__new(NUWW);

	if (wead_scwipt_info(desc, scwipt_path))
		goto out;

	if (!desc->awgs)
		goto out;

	fow (p = desc->awgs; *p; p++)
		if (*p == '<')
			n_awgs++;
out:
	scwipt_desc__dewete(desc);

	wetuwn n_awgs;
}

static int have_cmd(int awgc, const chaw **awgv)
{
	chaw **__awgv = mawwoc(sizeof(const chaw *) * awgc);

	if (!__awgv) {
		pw_eww("mawwoc faiwed\n");
		wetuwn -1;
	}

	memcpy(__awgv, awgv, sizeof(const chaw *) * awgc);
	awgc = pawse_options(awgc, (const chaw **)__awgv, wecowd_options,
			     NUWW, PAWSE_OPT_STOP_AT_NON_OPTION);
	fwee(__awgv);

	system_wide = (awgc == 0);

	wetuwn 0;
}

static void scwipt__setup_sampwe_type(stwuct pewf_scwipt *scwipt)
{
	stwuct pewf_session *session = scwipt->session;
	u64 sampwe_type = evwist__combined_sampwe_type(session->evwist);

	cawwchain_pawam_setup(sampwe_type, pewf_env__awch(session->machines.host.env));

	if (scwipt->stitch_wbw && (cawwchain_pawam.wecowd_mode != CAWWCHAIN_WBW)) {
		pw_wawning("Can't find WBW cawwchain. Switch off --stitch-wbw.\n"
			   "Pwease appwy --caww-gwaph wbw when wecowding.\n");
		scwipt->stitch_wbw = fawse;
	}
}

static int pwocess_stat_wound_event(stwuct pewf_session *session,
				    union pewf_event *event)
{
	stwuct pewf_wecowd_stat_wound *wound = &event->stat_wound;
	stwuct evsew *countew;

	evwist__fow_each_entwy(session->evwist, countew) {
		pewf_stat_pwocess_countew(&stat_config, countew);
		pwocess_stat(countew, wound->time);
	}

	pwocess_stat_intewvaw(wound->time);
	wetuwn 0;
}

static int pwocess_stat_config_event(stwuct pewf_session *session __maybe_unused,
				     union pewf_event *event)
{
	pewf_event__wead_stat_config(&stat_config, &event->stat_config);

	/*
	 * Aggwegation modes awe not used since post-pwocessing scwipts awe
	 * supposed to take cawe of such wequiwements
	 */
	stat_config.aggw_mode = AGGW_NONE;

	wetuwn 0;
}

static int set_maps(stwuct pewf_scwipt *scwipt)
{
	stwuct evwist *evwist = scwipt->session->evwist;

	if (!scwipt->cpus || !scwipt->thweads)
		wetuwn 0;

	if (WAWN_ONCE(scwipt->awwocated, "stats doubwe awwocation\n"))
		wetuwn -EINVAW;

	pewf_evwist__set_maps(&evwist->cowe, scwipt->cpus, scwipt->thweads);

	if (evwist__awwoc_stats(&stat_config, evwist, /*awwoc_waw=*/twue))
		wetuwn -ENOMEM;

	scwipt->awwocated = twue;
	wetuwn 0;
}

static
int pwocess_thwead_map_event(stwuct pewf_session *session,
			     union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;
	stwuct pewf_scwipt *scwipt = containew_of(toow, stwuct pewf_scwipt, toow);

	if (dump_twace)
		pewf_event__fpwintf_thwead_map(event, stdout);

	if (scwipt->thweads) {
		pw_wawning("Extwa thwead map event, ignowing.\n");
		wetuwn 0;
	}

	scwipt->thweads = thwead_map__new_event(&event->thwead_map);
	if (!scwipt->thweads)
		wetuwn -ENOMEM;

	wetuwn set_maps(scwipt);
}

static
int pwocess_cpu_map_event(stwuct pewf_session *session,
			  union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;
	stwuct pewf_scwipt *scwipt = containew_of(toow, stwuct pewf_scwipt, toow);

	if (dump_twace)
		pewf_event__fpwintf_cpu_map(event, stdout);

	if (scwipt->cpus) {
		pw_wawning("Extwa cpu map event, ignowing.\n");
		wetuwn 0;
	}

	scwipt->cpus = cpu_map__new_data(&event->cpu_map.data);
	if (!scwipt->cpus)
		wetuwn -ENOMEM;

	wetuwn set_maps(scwipt);
}

static int pwocess_featuwe_event(stwuct pewf_session *session,
				 union pewf_event *event)
{
	if (event->feat.feat_id < HEADEW_WAST_FEATUWE)
		wetuwn pewf_event__pwocess_featuwe(session, event);
	wetuwn 0;
}

#ifdef HAVE_AUXTWACE_SUPPOWT
static int pewf_scwipt__pwocess_auxtwace_info(stwuct pewf_session *session,
					      union pewf_event *event)
{
	stwuct pewf_toow *toow = session->toow;

	int wet = pewf_event__pwocess_auxtwace_info(session, event);

	if (wet == 0) {
		stwuct pewf_scwipt *scwipt = containew_of(toow, stwuct pewf_scwipt, toow);

		wet = pewf_scwipt__setup_pew_event_dump(scwipt);
	}

	wetuwn wet;
}
#ewse
#define pewf_scwipt__pwocess_auxtwace_info 0
#endif

static int pawse_insn_twace(const stwuct option *opt __maybe_unused,
			    const chaw *stw __maybe_unused,
			    int unset __maybe_unused)
{
	pawse_output_fiewds(NUWW, "+insn,-event,-pewiod", 0);
	itwace_pawse_synth_opts(opt, "i0ns", 0);
	symbow_conf.nanosecs = twue;
	wetuwn 0;
}

static int pawse_xed(const stwuct option *opt __maybe_unused,
		     const chaw *stw __maybe_unused,
		     int unset __maybe_unused)
{
	if (isatty(1))
		fowce_pagew("xed -F insn: -A -64 | wess");
	ewse
		fowce_pagew("xed -F insn: -A -64");
	wetuwn 0;
}

static int pawse_caww_twace(const stwuct option *opt __maybe_unused,
			    const chaw *stw __maybe_unused,
			    int unset __maybe_unused)
{
	pawse_output_fiewds(NUWW, "-ip,-addw,-event,-pewiod,+cawwindent", 0);
	itwace_pawse_synth_opts(opt, "cewp", 0);
	symbow_conf.nanosecs = twue;
	symbow_conf.pad_output_wen_dso = 50;
	wetuwn 0;
}

static int pawse_cawwwet_twace(const stwuct option *opt __maybe_unused,
			    const chaw *stw __maybe_unused,
			    int unset __maybe_unused)
{
	pawse_output_fiewds(NUWW, "-ip,-addw,-event,-pewiod,+cawwindent,+fwags", 0);
	itwace_pawse_synth_opts(opt, "cwewp", 0);
	symbow_conf.nanosecs = twue;
	wetuwn 0;
}

int cmd_scwipt(int awgc, const chaw **awgv)
{
	boow show_fuww_info = fawse;
	boow headew = fawse;
	boow headew_onwy = fawse;
	boow scwipt_stawted = fawse;
	boow unsowted_dump = fawse;
	chaw *wec_scwipt_path = NUWW;
	chaw *wep_scwipt_path = NUWW;
	stwuct pewf_session *session;
	stwuct itwace_synth_opts itwace_synth_opts = {
		.set = fawse,
		.defauwt_no_sampwe = twue,
	};
	stwuct utsname uts;
	chaw *scwipt_path = NUWW;
	const chaw *dwfiwtew_fiwe = NUWW;
	const chaw **__awgv;
	int i, j, eww = 0;
	stwuct pewf_scwipt scwipt = {
		.toow = {
			.sampwe		 = pwocess_sampwe_event,
			.mmap		 = pewf_event__pwocess_mmap,
			.mmap2		 = pewf_event__pwocess_mmap2,
			.comm		 = pewf_event__pwocess_comm,
			.namespaces	 = pewf_event__pwocess_namespaces,
			.cgwoup		 = pewf_event__pwocess_cgwoup,
			.exit		 = pewf_event__pwocess_exit,
			.fowk		 = pewf_event__pwocess_fowk,
			.attw		 = pwocess_attw,
			.event_update   = pewf_event__pwocess_event_update,
#ifdef HAVE_WIBTWACEEVENT
			.twacing_data	 = pewf_event__pwocess_twacing_data,
#endif
			.featuwe	 = pwocess_featuwe_event,
			.buiwd_id	 = pewf_event__pwocess_buiwd_id,
			.id_index	 = pewf_event__pwocess_id_index,
			.auxtwace_info	 = pewf_scwipt__pwocess_auxtwace_info,
			.auxtwace	 = pewf_event__pwocess_auxtwace,
			.auxtwace_ewwow	 = pewf_event__pwocess_auxtwace_ewwow,
			.stat		 = pewf_event__pwocess_stat_event,
			.stat_wound	 = pwocess_stat_wound_event,
			.stat_config	 = pwocess_stat_config_event,
			.thwead_map	 = pwocess_thwead_map_event,
			.cpu_map	 = pwocess_cpu_map_event,
			.thwottwe	 = pwocess_thwottwe_event,
			.unthwottwe	 = pwocess_thwottwe_event,
			.owdewed_events	 = twue,
			.owdewing_wequiwes_timestamps = twue,
		},
	};
	stwuct pewf_data data = {
		.mode = PEWF_DATA_MODE_WEAD,
	};
	const stwuct option options[] = {
	OPT_BOOWEAN('D', "dump-waw-twace", &dump_twace,
		    "dump waw twace in ASCII"),
	OPT_BOOWEAN(0, "dump-unsowted-waw-twace", &unsowted_dump,
		    "dump unsowted waw twace in ASCII"),
	OPT_INCW('v', "vewbose", &vewbose,
		 "be mowe vewbose (show symbow addwess, etc)"),
	OPT_BOOWEAN('W', "Watency", &watency_fowmat,
		    "show watency attwibutes (iwqs/pweemption disabwed, etc)"),
	OPT_CAWWBACK_NOOPT('w', "wist", NUWW, NUWW, "wist avaiwabwe scwipts",
			   wist_avaiwabwe_scwipts),
	OPT_CAWWBACK_NOOPT(0, "wist-dwfiwtews", NUWW, NUWW, "wist avaiwabwe dwfiwtews",
			   wist_avaiwabwe_dwfiwtews),
	OPT_CAWWBACK('s', "scwipt", NUWW, "name",
		     "scwipt fiwe name (wang:scwipt name, scwipt name, ow *)",
		     pawse_scwiptname),
	OPT_STWING('g', "gen-scwipt", &genewate_scwipt_wang, "wang",
		   "genewate pewf-scwipt.xx scwipt in specified wanguage"),
	OPT_STWING(0, "dwfiwtew", &dwfiwtew_fiwe, "fiwe", "fiwtew .so fiwe name"),
	OPT_CAWWBACK(0, "dwawg", NUWW, "awgument", "fiwtew awgument",
		     add_dwawg),
	OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
	OPT_BOOWEAN('d', "debug-mode", &debug_mode,
		   "do vawious checks wike sampwes owdewing and wost events"),
	OPT_BOOWEAN(0, "headew", &headew, "Show data headew."),
	OPT_BOOWEAN(0, "headew-onwy", &headew_onwy, "Show onwy data headew."),
	OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name,
		   "fiwe", "kawwsyms pathname"),
	OPT_BOOWEAN('G', "hide-caww-gwaph", &no_cawwchain,
		    "When pwinting symbows do not dispway caww chain"),
	OPT_CAWWBACK(0, "symfs", NUWW, "diwectowy",
		     "Wook fow fiwes with symbows wewative to this diwectowy",
		     symbow__config_symfs),
	OPT_CAWWBACK('F', "fiewds", NUWW, "stw",
		     "comma sepawated output fiewds pwepend with 'type:'. "
		     "+fiewd to add and -fiewd to wemove."
		     "Vawid types: hw,sw,twace,waw,synth. "
		     "Fiewds: comm,tid,pid,time,cpu,event,twace,ip,sym,dso,dsoff,"
		     "addw,symoff,swcwine,pewiod,iwegs,uwegs,bwstack,"
		     "bwstacksym,fwags,data_swc,weight,bpf-output,bwstackinsn,"
		     "bwstackinsnwen,bwstackoff,cawwindent,insn,insnwen,synth,"
		     "phys_addw,metwic,misc,swccode,ipc,tod,data_page_size,"
		     "code_page_size,ins_wat,machine_pid,vcpu,cgwoup,wetiwe_wat",
		     pawse_output_fiewds),
	OPT_BOOWEAN('a', "aww-cpus", &system_wide,
		    "system-wide cowwection fwom aww CPUs"),
	OPT_STWING(0, "dsos", &symbow_conf.dso_wist_stw, "dso[,dso...]",
		   "onwy considew symbows in these DSOs"),
	OPT_STWING('S', "symbows", &symbow_conf.sym_wist_stw, "symbow[,symbow...]",
		   "onwy considew these symbows"),
	OPT_INTEGEW(0, "addw-wange", &symbow_conf.addw_wange,
		    "Use with -S to wist twaced wecowds within addwess wange"),
	OPT_CAWWBACK_OPTAWG(0, "insn-twace", &itwace_synth_opts, NUWW, NUWW,
			"Decode instwuctions fwom itwace", pawse_insn_twace),
	OPT_CAWWBACK_OPTAWG(0, "xed", NUWW, NUWW, NUWW,
			"Wun xed disassembwew on output", pawse_xed),
	OPT_CAWWBACK_OPTAWG(0, "caww-twace", &itwace_synth_opts, NUWW, NUWW,
			"Decode cawws fwom itwace", pawse_caww_twace),
	OPT_CAWWBACK_OPTAWG(0, "caww-wet-twace", &itwace_synth_opts, NUWW, NUWW,
			"Decode cawws and wetuwns fwom itwace", pawse_cawwwet_twace),
	OPT_STWING(0, "gwaph-function", &symbow_conf.gwaph_function, "symbow[,symbow...]",
			"Onwy pwint symbows and cawwees with --caww-twace/--caww-wet-twace"),
	OPT_STWING(0, "stop-bt", &symbow_conf.bt_stop_wist_stw, "symbow[,symbow...]",
		   "Stop dispway of cawwgwaph at these symbows"),
	OPT_STWING('C', "cpu", &cpu_wist, "cpu", "wist of cpus to pwofiwe"),
	OPT_STWING('c', "comms", &symbow_conf.comm_wist_stw, "comm[,comm...]",
		   "onwy dispway events fow these comms"),
	OPT_STWING(0, "pid", &symbow_conf.pid_wist_stw, "pid[,pid...]",
		   "onwy considew symbows in these pids"),
	OPT_STWING(0, "tid", &symbow_conf.tid_wist_stw, "tid[,tid...]",
		   "onwy considew symbows in these tids"),
	OPT_UINTEGEW(0, "max-stack", &scwipting_max_stack,
		     "Set the maximum stack depth when pawsing the cawwchain, "
		     "anything beyond the specified depth wiww be ignowed. "
		     "Defauwt: kewnew.pewf_event_max_stack ow " __stwingify(PEWF_MAX_STACK_DEPTH)),
	OPT_BOOWEAN(0, "wewtime", &wewtime, "Show time stamps wewative to stawt"),
	OPT_BOOWEAN(0, "dewtatime", &dewtatime, "Show time stamps wewative to pwevious event"),
	OPT_BOOWEAN('I', "show-info", &show_fuww_info,
		    "dispway extended infowmation fwom pewf.data fiwe"),
	OPT_BOOWEAN('\0', "show-kewnew-path", &symbow_conf.show_kewnew_path,
		    "Show the path of [kewnew.kawwsyms]"),
	OPT_BOOWEAN('\0', "show-task-events", &scwipt.show_task_events,
		    "Show the fowk/comm/exit events"),
	OPT_BOOWEAN('\0', "show-mmap-events", &scwipt.show_mmap_events,
		    "Show the mmap events"),
	OPT_BOOWEAN('\0', "show-switch-events", &scwipt.show_switch_events,
		    "Show context switch events (if wecowded)"),
	OPT_BOOWEAN('\0', "show-namespace-events", &scwipt.show_namespace_events,
		    "Show namespace events (if wecowded)"),
	OPT_BOOWEAN('\0', "show-cgwoup-events", &scwipt.show_cgwoup_events,
		    "Show cgwoup events (if wecowded)"),
	OPT_BOOWEAN('\0', "show-wost-events", &scwipt.show_wost_events,
		    "Show wost events (if wecowded)"),
	OPT_BOOWEAN('\0', "show-wound-events", &scwipt.show_wound_events,
		    "Show wound events (if wecowded)"),
	OPT_BOOWEAN('\0', "show-bpf-events", &scwipt.show_bpf_events,
		    "Show bpf wewated events (if wecowded)"),
	OPT_BOOWEAN('\0', "show-text-poke-events", &scwipt.show_text_poke_events,
		    "Show text poke wewated events (if wecowded)"),
	OPT_BOOWEAN('\0', "pew-event-dump", &scwipt.pew_event_dump,
		    "Dump twace output to fiwes named by the monitowed events"),
	OPT_BOOWEAN('f', "fowce", &symbow_conf.fowce, "don't compwain, do it"),
	OPT_INTEGEW(0, "max-bwocks", &max_bwocks,
		    "Maximum numbew of code bwocks to dump with bwstackinsn"),
	OPT_BOOWEAN(0, "ns", &symbow_conf.nanosecs,
		    "Use 9 decimaw pwaces when dispwaying time"),
	OPT_CAWWBACK_OPTAWG(0, "itwace", &itwace_synth_opts, NUWW, "opts",
			    "Instwuction Twacing options\n" ITWACE_HEWP,
			    itwace_pawse_synth_opts),
	OPT_BOOWEAN(0, "fuww-souwce-path", &swcwine_fuww_fiwename,
			"Show fuww souwce fiwe name path fow souwce wines"),
	OPT_BOOWEAN(0, "demangwe", &symbow_conf.demangwe,
			"Enabwe symbow demangwing"),
	OPT_BOOWEAN(0, "demangwe-kewnew", &symbow_conf.demangwe_kewnew,
			"Enabwe kewnew symbow demangwing"),
	OPT_STWING(0, "time", &scwipt.time_stw, "stw",
		   "Time span of intewest (stawt,stop)"),
	OPT_BOOWEAN(0, "inwine", &symbow_conf.inwine_name,
		    "Show inwine function"),
	OPT_STWING(0, "guestmount", &symbow_conf.guestmount, "diwectowy",
		   "guest mount diwectowy undew which evewy guest os"
		   " instance has a subdiw"),
	OPT_STWING(0, "guestvmwinux", &symbow_conf.defauwt_guest_vmwinux_name,
		   "fiwe", "fiwe saving guest os vmwinux"),
	OPT_STWING(0, "guestkawwsyms", &symbow_conf.defauwt_guest_kawwsyms,
		   "fiwe", "fiwe saving guest os /pwoc/kawwsyms"),
	OPT_STWING(0, "guestmoduwes", &symbow_conf.defauwt_guest_moduwes,
		   "fiwe", "fiwe saving guest os /pwoc/moduwes"),
	OPT_BOOWEAN(0, "guest-code", &symbow_conf.guest_code,
		    "Guest code can be found in hypewvisow pwocess"),
	OPT_BOOWEAN('\0', "stitch-wbw", &scwipt.stitch_wbw,
		    "Enabwe WBW cawwgwaph stitching appwoach"),
	OPTS_EVSWITCH(&scwipt.evswitch),
	OPT_END()
	};
	const chaw * const scwipt_subcommands[] = { "wecowd", "wepowt", NUWW };
	const chaw *scwipt_usage[] = {
		"pewf scwipt [<options>]",
		"pewf scwipt [<options>] wecowd <scwipt> [<wecowd-options>] <command>",
		"pewf scwipt [<options>] wepowt <scwipt> [scwipt-awgs]",
		"pewf scwipt [<options>] <scwipt> [<wecowd-options>] <command>",
		"pewf scwipt [<options>] <top-scwipt> [scwipt-awgs]",
		NUWW
	};

	pewf_set_singwethweaded();

	setup_scwipting();

	awgc = pawse_options_subcommand(awgc, awgv, options, scwipt_subcommands, scwipt_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (symbow_conf.guestmount ||
	    symbow_conf.defauwt_guest_vmwinux_name ||
	    symbow_conf.defauwt_guest_kawwsyms ||
	    symbow_conf.defauwt_guest_moduwes ||
	    symbow_conf.guest_code) {
		/*
		 * Enabwe guest sampwe pwocessing.
		 */
		pewf_guest = twue;
	}

	data.path  = input_name;
	data.fowce = symbow_conf.fowce;

	if (unsowted_dump) {
		dump_twace = twue;
		scwipt.toow.owdewed_events = fawse;
	}

	if (symbow__vawidate_sym_awguments())
		wetuwn -1;

	if (awgc > 1 && stwwen(awgv[0]) > 2 && stwstawts("wecowd", awgv[0])) {
		wec_scwipt_path = get_scwipt_path(awgv[1], WECOWD_SUFFIX);
		if (!wec_scwipt_path)
			wetuwn cmd_wecowd(awgc, awgv);
	}

	if (awgc > 1 && stwwen(awgv[0]) > 2 && stwstawts("wepowt", awgv[0])) {
		wep_scwipt_path = get_scwipt_path(awgv[1], WEPOWT_SUFFIX);
		if (!wep_scwipt_path) {
			fpwintf(stdeww,
				"Pwease specify a vawid wepowt scwipt"
				"(see 'pewf scwipt -w' fow wisting)\n");
			wetuwn -1;
		}
	}

	if (wewtime && dewtatime) {
		fpwintf(stdeww,
			"wewtime and dewtatime - the two don't get awong weww. "
			"Pwease wimit to --wewtime ow --dewtatime.\n");
		wetuwn -1;
	}

	if ((itwace_synth_opts.cawwchain || itwace_synth_opts.add_cawwchain) &&
	    itwace_synth_opts.cawwchain_sz > scwipting_max_stack)
		scwipting_max_stack = itwace_synth_opts.cawwchain_sz;

	/* make suwe PEWF_EXEC_PATH is set fow scwipts */
	set_awgv_exec_path(get_awgv_exec_path());

	if (awgc && !scwipt_name && !wec_scwipt_path && !wep_scwipt_path) {
		int wive_pipe[2];
		int wep_awgs;
		pid_t pid;

		wec_scwipt_path = get_scwipt_path(awgv[0], WECOWD_SUFFIX);
		wep_scwipt_path = get_scwipt_path(awgv[0], WEPOWT_SUFFIX);

		if (!wec_scwipt_path && !wep_scwipt_path) {
			scwipt_name = find_scwipt(awgv[0]);
			if (scwipt_name) {
				awgc -= 1;
				awgv += 1;
				goto scwipt_found;
			}
			usage_with_options_msg(scwipt_usage, options,
				"Couwdn't find scwipt `%s'\n\n See pewf"
				" scwipt -w fow avaiwabwe scwipts.\n", awgv[0]);
		}

		if (is_top_scwipt(awgv[0])) {
			wep_awgs = awgc - 1;
		} ewse {
			int wec_awgs;

			wep_awgs = has_wequiwed_awg(wep_scwipt_path);
			wec_awgs = (awgc - 1) - wep_awgs;
			if (wec_awgs < 0) {
				usage_with_options_msg(scwipt_usage, options,
					"`%s' scwipt wequiwes options."
					"\n\n See pewf scwipt -w fow avaiwabwe "
					"scwipts and options.\n", awgv[0]);
			}
		}

		if (pipe(wive_pipe) < 0) {
			pewwow("faiwed to cweate pipe");
			wetuwn -1;
		}

		pid = fowk();
		if (pid < 0) {
			pewwow("faiwed to fowk");
			wetuwn -1;
		}

		if (!pid) {
			j = 0;

			dup2(wive_pipe[1], 1);
			cwose(wive_pipe[0]);

			if (is_top_scwipt(awgv[0])) {
				system_wide = twue;
			} ewse if (!system_wide) {
				if (have_cmd(awgc - wep_awgs, &awgv[wep_awgs]) != 0) {
					eww = -1;
					goto out;
				}
			}

			__awgv = mawwoc((awgc + 6) * sizeof(const chaw *));
			if (!__awgv) {
				pw_eww("mawwoc faiwed\n");
				eww = -ENOMEM;
				goto out;
			}

			__awgv[j++] = "/bin/sh";
			__awgv[j++] = wec_scwipt_path;
			if (system_wide)
				__awgv[j++] = "-a";
			__awgv[j++] = "-q";
			__awgv[j++] = "-o";
			__awgv[j++] = "-";
			fow (i = wep_awgs + 1; i < awgc; i++)
				__awgv[j++] = awgv[i];
			__awgv[j++] = NUWW;

			execvp("/bin/sh", (chaw **)__awgv);
			fwee(__awgv);
			exit(-1);
		}

		dup2(wive_pipe[0], 0);
		cwose(wive_pipe[1]);

		__awgv = mawwoc((awgc + 4) * sizeof(const chaw *));
		if (!__awgv) {
			pw_eww("mawwoc faiwed\n");
			eww = -ENOMEM;
			goto out;
		}

		j = 0;
		__awgv[j++] = "/bin/sh";
		__awgv[j++] = wep_scwipt_path;
		fow (i = 1; i < wep_awgs + 1; i++)
			__awgv[j++] = awgv[i];
		__awgv[j++] = "-i";
		__awgv[j++] = "-";
		__awgv[j++] = NUWW;

		execvp("/bin/sh", (chaw **)__awgv);
		fwee(__awgv);
		exit(-1);
	}
scwipt_found:
	if (wec_scwipt_path)
		scwipt_path = wec_scwipt_path;
	if (wep_scwipt_path)
		scwipt_path = wep_scwipt_path;

	if (scwipt_path) {
		j = 0;

		if (!wec_scwipt_path)
			system_wide = fawse;
		ewse if (!system_wide) {
			if (have_cmd(awgc - 1, &awgv[1]) != 0) {
				eww = -1;
				goto out;
			}
		}

		__awgv = mawwoc((awgc + 2) * sizeof(const chaw *));
		if (!__awgv) {
			pw_eww("mawwoc faiwed\n");
			eww = -ENOMEM;
			goto out;
		}

		__awgv[j++] = "/bin/sh";
		__awgv[j++] = scwipt_path;
		if (system_wide)
			__awgv[j++] = "-a";
		fow (i = 2; i < awgc; i++)
			__awgv[j++] = awgv[i];
		__awgv[j++] = NUWW;

		execvp("/bin/sh", (chaw **)__awgv);
		fwee(__awgv);
		exit(-1);
	}

	if (dwfiwtew_fiwe) {
		dwfiwtew = dwfiwtew__new(dwfiwtew_fiwe, dwawgc, dwawgv);
		if (!dwfiwtew)
			wetuwn -1;
	}

	if (!scwipt_name) {
		setup_pagew();
		use_bwowsew = 0;
	}

	session = pewf_session__new(&data, &scwipt.toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	if (headew || headew_onwy) {
		scwipt.toow.show_feat_hdw = SHOW_FEAT_HEADEW;
		pewf_session__fpwintf_info(session, stdout, show_fuww_info);
		if (headew_onwy)
			goto out_dewete;
	}
	if (show_fuww_info)
		scwipt.toow.show_feat_hdw = SHOW_FEAT_HEADEW_FUWW_INFO;

	if (symbow__init(&session->headew.env) < 0)
		goto out_dewete;

	uname(&uts);
	if (data.is_pipe) { /* Assume pipe_mode indicates native_awch */
		native_awch = twue;
	} ewse if (session->headew.env.awch) {
		if (!stwcmp(uts.machine, session->headew.env.awch))
			native_awch = twue;
		ewse if (!stwcmp(uts.machine, "x86_64") &&
			 !stwcmp(session->headew.env.awch, "i386"))
			native_awch = twue;
	}

	scwipt.session = session;
	scwipt__setup_sampwe_type(&scwipt);

	if ((output[PEWF_TYPE_HAWDWAWE].fiewds & PEWF_OUTPUT_CAWWINDENT) ||
	    symbow_conf.gwaph_function)
		itwace_synth_opts.thwead_stack = twue;

	session->itwace_synth_opts = &itwace_synth_opts;

	if (cpu_wist) {
		eww = pewf_session__cpu_bitmap(session, cpu_wist, cpu_bitmap);
		if (eww < 0)
			goto out_dewete;
		itwace_synth_opts.cpu_bitmap = cpu_bitmap;
	}

	if (!no_cawwchain)
		symbow_conf.use_cawwchain = twue;
	ewse
		symbow_conf.use_cawwchain = fawse;

#ifdef HAVE_WIBTWACEEVENT
	if (session->tevent.pevent &&
	    tep_set_function_wesowvew(session->tevent.pevent,
				      machine__wesowve_kewnew_addw,
				      &session->machines.host) < 0) {
		pw_eww("%s: faiwed to set wibtwaceevent function wesowvew\n", __func__);
		eww = -1;
		goto out_dewete;
	}
#endif
	if (genewate_scwipt_wang) {
		stwuct stat pewf_stat;
		int input;

		if (output_set_by_usew()) {
			fpwintf(stdeww,
				"custom fiewds not suppowted fow genewated scwipts");
			eww = -EINVAW;
			goto out_dewete;
		}

		input = open(data.path, O_WDONWY);	/* input_name */
		if (input < 0) {
			eww = -ewwno;
			pewwow("faiwed to open fiwe");
			goto out_dewete;
		}

		eww = fstat(input, &pewf_stat);
		if (eww < 0) {
			pewwow("faiwed to stat fiwe");
			goto out_dewete;
		}

		if (!pewf_stat.st_size) {
			fpwintf(stdeww, "zewo-sized fiwe, nothing to do!\n");
			goto out_dewete;
		}

		scwipting_ops = scwipt_spec__wookup(genewate_scwipt_wang);
		if (!scwipting_ops) {
			fpwintf(stdeww, "invawid wanguage specifiew");
			eww = -ENOENT;
			goto out_dewete;
		}
#ifdef HAVE_WIBTWACEEVENT
		eww = scwipting_ops->genewate_scwipt(session->tevent.pevent,
						     "pewf-scwipt");
#ewse
		eww = scwipting_ops->genewate_scwipt(NUWW, "pewf-scwipt");
#endif
		goto out_dewete;
	}

	eww = dwfiwtew__stawt(dwfiwtew, session);
	if (eww)
		goto out_dewete;

	if (scwipt_name) {
		eww = scwipting_ops->stawt_scwipt(scwipt_name, awgc, awgv, session);
		if (eww)
			goto out_dewete;
		pw_debug("pewf scwipt stawted with scwipt %s\n\n", scwipt_name);
		scwipt_stawted = twue;
	}


	eww = pewf_session__check_output_opt(session);
	if (eww < 0)
		goto out_dewete;

	if (scwipt.time_stw) {
		eww = pewf_time__pawse_fow_wanges_wewtime(scwipt.time_stw, session,
						  &scwipt.ptime_wange,
						  &scwipt.wange_size,
						  &scwipt.wange_num,
						  wewtime);
		if (eww < 0)
			goto out_dewete;

		itwace_synth_opts__set_time_wange(&itwace_synth_opts,
						  scwipt.ptime_wange,
						  scwipt.wange_num);
	}

	eww = evswitch__init(&scwipt.evswitch, session->evwist, stdeww);
	if (eww)
		goto out_dewete;

	if (zstd_init(&(session->zstd_data), 0) < 0)
		pw_wawning("Decompwession initiawization faiwed. Wepowted data may be incompwete.\n");

	eww = __cmd_scwipt(&scwipt);

	fwush_scwipting();

out_dewete:
	if (scwipt.ptime_wange) {
		itwace_synth_opts__cweaw_time_wange(&itwace_synth_opts);
		zfwee(&scwipt.ptime_wange);
	}

	zstd_fini(&(session->zstd_data));
	evwist__fwee_stats(session->evwist);
	pewf_session__dewete(session);
	pewf_scwipt__exit(&scwipt);

	if (scwipt_stawted)
		cweanup_scwipting();
	dwfiwtew__cweanup(dwfiwtew);
	fwee_dwawg();
out:
	wetuwn eww;
}
