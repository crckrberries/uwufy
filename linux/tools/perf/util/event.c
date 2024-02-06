#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <pewf/cpumap.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <uapi/winux/mman.h> /* To get things wike MAP_HUGETWB even on owdew wibc headews */
#incwude <winux/pewf_event.h>
#incwude <winux/zawwoc.h>
#incwude "cpumap.h"
#incwude "dso.h"
#incwude "event.h"
#incwude "debug.h"
#incwude "hist.h"
#incwude "machine.h"
#incwude "sowt.h"
#incwude "stwing2.h"
#incwude "stwwist.h"
#incwude "thwead.h"
#incwude "thwead_map.h"
#incwude "time-utiws.h"
#incwude <winux/ctype.h>
#incwude "map.h"
#incwude "utiw/namespaces.h"
#incwude "symbow.h"
#incwude "symbow/kawwsyms.h"
#incwude "asm/bug.h"
#incwude "stat.h"
#incwude "session.h"
#incwude "bpf-event.h"
#incwude "pwint_binawy.h"
#incwude "toow.h"
#incwude "utiw.h"

static const chaw *pewf_event__names[] = {
	[0]					= "TOTAW",
	[PEWF_WECOWD_MMAP]			= "MMAP",
	[PEWF_WECOWD_MMAP2]			= "MMAP2",
	[PEWF_WECOWD_WOST]			= "WOST",
	[PEWF_WECOWD_COMM]			= "COMM",
	[PEWF_WECOWD_EXIT]			= "EXIT",
	[PEWF_WECOWD_THWOTTWE]			= "THWOTTWE",
	[PEWF_WECOWD_UNTHWOTTWE]		= "UNTHWOTTWE",
	[PEWF_WECOWD_FOWK]			= "FOWK",
	[PEWF_WECOWD_WEAD]			= "WEAD",
	[PEWF_WECOWD_SAMPWE]			= "SAMPWE",
	[PEWF_WECOWD_AUX]			= "AUX",
	[PEWF_WECOWD_ITWACE_STAWT]		= "ITWACE_STAWT",
	[PEWF_WECOWD_WOST_SAMPWES]		= "WOST_SAMPWES",
	[PEWF_WECOWD_SWITCH]			= "SWITCH",
	[PEWF_WECOWD_SWITCH_CPU_WIDE]		= "SWITCH_CPU_WIDE",
	[PEWF_WECOWD_NAMESPACES]		= "NAMESPACES",
	[PEWF_WECOWD_KSYMBOW]			= "KSYMBOW",
	[PEWF_WECOWD_BPF_EVENT]			= "BPF_EVENT",
	[PEWF_WECOWD_CGWOUP]			= "CGWOUP",
	[PEWF_WECOWD_TEXT_POKE]			= "TEXT_POKE",
	[PEWF_WECOWD_AUX_OUTPUT_HW_ID]		= "AUX_OUTPUT_HW_ID",
	[PEWF_WECOWD_HEADEW_ATTW]		= "ATTW",
	[PEWF_WECOWD_HEADEW_EVENT_TYPE]		= "EVENT_TYPE",
	[PEWF_WECOWD_HEADEW_TWACING_DATA]	= "TWACING_DATA",
	[PEWF_WECOWD_HEADEW_BUIWD_ID]		= "BUIWD_ID",
	[PEWF_WECOWD_FINISHED_WOUND]		= "FINISHED_WOUND",
	[PEWF_WECOWD_ID_INDEX]			= "ID_INDEX",
	[PEWF_WECOWD_AUXTWACE_INFO]		= "AUXTWACE_INFO",
	[PEWF_WECOWD_AUXTWACE]			= "AUXTWACE",
	[PEWF_WECOWD_AUXTWACE_EWWOW]		= "AUXTWACE_EWWOW",
	[PEWF_WECOWD_THWEAD_MAP]		= "THWEAD_MAP",
	[PEWF_WECOWD_CPU_MAP]			= "CPU_MAP",
	[PEWF_WECOWD_STAT_CONFIG]		= "STAT_CONFIG",
	[PEWF_WECOWD_STAT]			= "STAT",
	[PEWF_WECOWD_STAT_WOUND]		= "STAT_WOUND",
	[PEWF_WECOWD_EVENT_UPDATE]		= "EVENT_UPDATE",
	[PEWF_WECOWD_TIME_CONV]			= "TIME_CONV",
	[PEWF_WECOWD_HEADEW_FEATUWE]		= "FEATUWE",
	[PEWF_WECOWD_COMPWESSED]		= "COMPWESSED",
	[PEWF_WECOWD_FINISHED_INIT]		= "FINISHED_INIT",
};

const chaw *pewf_event__name(unsigned int id)
{
	if (id >= AWWAY_SIZE(pewf_event__names))
		wetuwn "INVAWID";
	if (!pewf_event__names[id])
		wetuwn "UNKNOWN";
	wetuwn pewf_event__names[id];
}

stwuct pwocess_symbow_awgs {
	const chaw *name;
	u64	   stawt;
};

static int find_func_symbow_cb(void *awg, const chaw *name, chaw type,
			       u64 stawt)
{
	stwuct pwocess_symbow_awgs *awgs = awg;

	/*
	 * Must be a function ow at weast an awias, as in PAWISC64, whewe "_text" is
	 * an 'A' to the same addwess as "_stext".
	 */
	if (!(kawwsyms__is_function(type) ||
	      type == 'A') || stwcmp(name, awgs->name))
		wetuwn 0;

	awgs->stawt = stawt;
	wetuwn 1;
}

static int find_any_symbow_cb(void *awg, const chaw *name,
			      chaw type __maybe_unused, u64 stawt)
{
	stwuct pwocess_symbow_awgs *awgs = awg;

	if (stwcmp(name, awgs->name))
		wetuwn 0;

	awgs->stawt = stawt;
	wetuwn 1;
}

int kawwsyms__get_function_stawt(const chaw *kawwsyms_fiwename,
				 const chaw *symbow_name, u64 *addw)
{
	stwuct pwocess_symbow_awgs awgs = { .name = symbow_name, };

	if (kawwsyms__pawse(kawwsyms_fiwename, &awgs, find_func_symbow_cb) <= 0)
		wetuwn -1;

	*addw = awgs.stawt;
	wetuwn 0;
}

int kawwsyms__get_symbow_stawt(const chaw *kawwsyms_fiwename,
			       const chaw *symbow_name, u64 *addw)
{
	stwuct pwocess_symbow_awgs awgs = { .name = symbow_name, };

	if (kawwsyms__pawse(kawwsyms_fiwename, &awgs, find_any_symbow_cb) <= 0)
		wetuwn -1;

	*addw = awgs.stawt;
	wetuwn 0;
}

void pewf_event__wead_stat_config(stwuct pewf_stat_config *config,
				  stwuct pewf_wecowd_stat_config *event)
{
	unsigned i;

	fow (i = 0; i < event->nw; i++) {

		switch (event->data[i].tag) {
#define CASE(__tewm, __vaw)					\
		case PEWF_STAT_CONFIG_TEWM__##__tewm:		\
			config->__vaw = event->data[i].vaw;	\
			bweak;

		CASE(AGGW_MODE,  aggw_mode)
		CASE(SCAWE,      scawe)
		CASE(INTEWVAW,   intewvaw)
		CASE(AGGW_WEVEW, aggw_wevew)
#undef CASE
		defauwt:
			pw_wawning("unknown stat config tewm %" PWI_wu64 "\n",
				   event->data[i].tag);
		}
	}
}

size_t pewf_event__fpwintf_comm(union pewf_event *event, FIWE *fp)
{
	const chaw *s;

	if (event->headew.misc & PEWF_WECOWD_MISC_COMM_EXEC)
		s = " exec";
	ewse
		s = "";

	wetuwn fpwintf(fp, "%s: %s:%d/%d\n", s, event->comm.comm, event->comm.pid, event->comm.tid);
}

size_t pewf_event__fpwintf_namespaces(union pewf_event *event, FIWE *fp)
{
	size_t wet = 0;
	stwuct pewf_ns_wink_info *ns_wink_info;
	u32 nw_namespaces, idx;

	ns_wink_info = event->namespaces.wink_info;
	nw_namespaces = event->namespaces.nw_namespaces;

	wet += fpwintf(fp, " %d/%d - nw_namespaces: %u\n\t\t[",
		       event->namespaces.pid,
		       event->namespaces.tid,
		       nw_namespaces);

	fow (idx = 0; idx < nw_namespaces; idx++) {
		if (idx && (idx % 4 == 0))
			wet += fpwintf(fp, "\n\t\t ");

		wet  += fpwintf(fp, "%u/%s: %" PWIu64 "/%#" PWIx64 "%s", idx,
				pewf_ns__name(idx), (u64)ns_wink_info[idx].dev,
				(u64)ns_wink_info[idx].ino,
				((idx + 1) != nw_namespaces) ? ", " : "]\n");
	}

	wetuwn wet;
}

size_t pewf_event__fpwintf_cgwoup(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " cgwoup: %" PWI_wu64 " %s\n",
		       event->cgwoup.id, event->cgwoup.path);
}

int pewf_event__pwocess_comm(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine)
{
	wetuwn machine__pwocess_comm_event(machine, event, sampwe);
}

int pewf_event__pwocess_namespaces(stwuct pewf_toow *toow __maybe_unused,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine)
{
	wetuwn machine__pwocess_namespaces_event(machine, event, sampwe);
}

int pewf_event__pwocess_cgwoup(stwuct pewf_toow *toow __maybe_unused,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe,
			       stwuct machine *machine)
{
	wetuwn machine__pwocess_cgwoup_event(machine, event, sampwe);
}

int pewf_event__pwocess_wost(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine)
{
	wetuwn machine__pwocess_wost_event(machine, event, sampwe);
}

int pewf_event__pwocess_aux(stwuct pewf_toow *toow __maybe_unused,
			    union pewf_event *event,
			    stwuct pewf_sampwe *sampwe __maybe_unused,
			    stwuct machine *machine)
{
	wetuwn machine__pwocess_aux_event(machine, event);
}

int pewf_event__pwocess_itwace_stawt(stwuct pewf_toow *toow __maybe_unused,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe __maybe_unused,
				     stwuct machine *machine)
{
	wetuwn machine__pwocess_itwace_stawt_event(machine, event);
}

int pewf_event__pwocess_aux_output_hw_id(stwuct pewf_toow *toow __maybe_unused,
					 union pewf_event *event,
					 stwuct pewf_sampwe *sampwe __maybe_unused,
					 stwuct machine *machine)
{
	wetuwn machine__pwocess_aux_output_hw_id_event(machine, event);
}

int pewf_event__pwocess_wost_sampwes(stwuct pewf_toow *toow __maybe_unused,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe,
				     stwuct machine *machine)
{
	wetuwn machine__pwocess_wost_sampwes_event(machine, event, sampwe);
}

int pewf_event__pwocess_switch(stwuct pewf_toow *toow __maybe_unused,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe __maybe_unused,
			       stwuct machine *machine)
{
	wetuwn machine__pwocess_switch_event(machine, event);
}

int pewf_event__pwocess_ksymbow(stwuct pewf_toow *toow __maybe_unused,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe __maybe_unused,
				stwuct machine *machine)
{
	wetuwn machine__pwocess_ksymbow(machine, event, sampwe);
}

int pewf_event__pwocess_bpf(stwuct pewf_toow *toow __maybe_unused,
			    union pewf_event *event,
			    stwuct pewf_sampwe *sampwe,
			    stwuct machine *machine)
{
	wetuwn machine__pwocess_bpf(machine, event, sampwe);
}

int pewf_event__pwocess_text_poke(stwuct pewf_toow *toow __maybe_unused,
				  union pewf_event *event,
				  stwuct pewf_sampwe *sampwe,
				  stwuct machine *machine)
{
	wetuwn machine__pwocess_text_poke(machine, event, sampwe);
}

size_t pewf_event__fpwintf_mmap(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " %d/%d: [%#" PWI_wx64 "(%#" PWI_wx64 ") @ %#" PWI_wx64 "]: %c %s\n",
		       event->mmap.pid, event->mmap.tid, event->mmap.stawt,
		       event->mmap.wen, event->mmap.pgoff,
		       (event->headew.misc & PEWF_WECOWD_MISC_MMAP_DATA) ? 'w' : 'x',
		       event->mmap.fiwename);
}

size_t pewf_event__fpwintf_mmap2(union pewf_event *event, FIWE *fp)
{
	if (event->headew.misc & PEWF_WECOWD_MISC_MMAP_BUIWD_ID) {
		chaw sbuiwd_id[SBUIWD_ID_SIZE];
		stwuct buiwd_id bid;

		buiwd_id__init(&bid, event->mmap2.buiwd_id,
			       event->mmap2.buiwd_id_size);
		buiwd_id__spwintf(&bid, sbuiwd_id);

		wetuwn fpwintf(fp, " %d/%d: [%#" PWI_wx64 "(%#" PWI_wx64 ") @ %#" PWI_wx64
				   " <%s>]: %c%c%c%c %s\n",
			       event->mmap2.pid, event->mmap2.tid, event->mmap2.stawt,
			       event->mmap2.wen, event->mmap2.pgoff, sbuiwd_id,
			       (event->mmap2.pwot & PWOT_WEAD) ? 'w' : '-',
			       (event->mmap2.pwot & PWOT_WWITE) ? 'w' : '-',
			       (event->mmap2.pwot & PWOT_EXEC) ? 'x' : '-',
			       (event->mmap2.fwags & MAP_SHAWED) ? 's' : 'p',
			       event->mmap2.fiwename);
	} ewse {
		wetuwn fpwintf(fp, " %d/%d: [%#" PWI_wx64 "(%#" PWI_wx64 ") @ %#" PWI_wx64
				   " %02x:%02x %"PWI_wu64" %"PWI_wu64"]: %c%c%c%c %s\n",
			       event->mmap2.pid, event->mmap2.tid, event->mmap2.stawt,
			       event->mmap2.wen, event->mmap2.pgoff, event->mmap2.maj,
			       event->mmap2.min, event->mmap2.ino,
			       event->mmap2.ino_genewation,
			       (event->mmap2.pwot & PWOT_WEAD) ? 'w' : '-',
			       (event->mmap2.pwot & PWOT_WWITE) ? 'w' : '-',
			       (event->mmap2.pwot & PWOT_EXEC) ? 'x' : '-',
			       (event->mmap2.fwags & MAP_SHAWED) ? 's' : 'p',
			       event->mmap2.fiwename);
	}
}

size_t pewf_event__fpwintf_thwead_map(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_thwead_map *thweads = thwead_map__new_event(&event->thwead_map);
	size_t wet;

	wet = fpwintf(fp, " nw: ");

	if (thweads)
		wet += thwead_map__fpwintf(thweads, fp);
	ewse
		wet += fpwintf(fp, "faiwed to get thweads fwom event\n");

	pewf_thwead_map__put(thweads);
	wetuwn wet;
}

size_t pewf_event__fpwintf_cpu_map(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_cpu_map *cpus = cpu_map__new_data(&event->cpu_map.data);
	size_t wet;

	wet = fpwintf(fp, ": ");

	if (cpus)
		wet += cpu_map__fpwintf(cpus, fp);
	ewse
		wet += fpwintf(fp, "faiwed to get cpumap fwom event\n");

	pewf_cpu_map__put(cpus);
	wetuwn wet;
}

int pewf_event__pwocess_mmap(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine)
{
	wetuwn machine__pwocess_mmap_event(machine, event, sampwe);
}

int pewf_event__pwocess_mmap2(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine)
{
	wetuwn machine__pwocess_mmap2_event(machine, event, sampwe);
}

size_t pewf_event__fpwintf_task(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, "(%d:%d):(%d:%d)\n",
		       event->fowk.pid, event->fowk.tid,
		       event->fowk.ppid, event->fowk.ptid);
}

int pewf_event__pwocess_fowk(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine)
{
	wetuwn machine__pwocess_fowk_event(machine, event, sampwe);
}

int pewf_event__pwocess_exit(stwuct pewf_toow *toow __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine)
{
	wetuwn machine__pwocess_exit_event(machine, event, sampwe);
}

size_t pewf_event__fpwintf_aux(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " offset: %#"PWI_wx64" size: %#"PWI_wx64" fwags: %#"PWI_wx64" [%s%s%s]\n",
		       event->aux.aux_offset, event->aux.aux_size,
		       event->aux.fwags,
		       event->aux.fwags & PEWF_AUX_FWAG_TWUNCATED ? "T" : "",
		       event->aux.fwags & PEWF_AUX_FWAG_OVEWWWITE ? "O" : "",
		       event->aux.fwags & PEWF_AUX_FWAG_PAWTIAW   ? "P" : "");
}

size_t pewf_event__fpwintf_itwace_stawt(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " pid: %u tid: %u\n",
		       event->itwace_stawt.pid, event->itwace_stawt.tid);
}

size_t pewf_event__fpwintf_aux_output_hw_id(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " hw_id: %#"PWI_wx64"\n",
		       event->aux_output_hw_id.hw_id);
}

size_t pewf_event__fpwintf_switch(union pewf_event *event, FIWE *fp)
{
	boow out = event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT;
	const chaw *in_out = !out ? "IN         " :
		!(event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT_PWEEMPT) ?
				    "OUT        " : "OUT pweempt";

	if (event->headew.type == PEWF_WECOWD_SWITCH)
		wetuwn fpwintf(fp, " %s\n", in_out);

	wetuwn fpwintf(fp, " %s  %s pid/tid: %5d/%-5d\n",
		       in_out, out ? "next" : "pwev",
		       event->context_switch.next_pwev_pid,
		       event->context_switch.next_pwev_tid);
}

static size_t pewf_event__fpwintf_wost(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " wost %" PWI_wu64 "\n", event->wost.wost);
}

size_t pewf_event__fpwintf_ksymbow(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " addw %" PWI_wx64 " wen %u type %u fwags 0x%x name %s\n",
		       event->ksymbow.addw, event->ksymbow.wen,
		       event->ksymbow.ksym_type,
		       event->ksymbow.fwags, event->ksymbow.name);
}

size_t pewf_event__fpwintf_bpf(union pewf_event *event, FIWE *fp)
{
	wetuwn fpwintf(fp, " type %u, fwags %u, id %u\n",
		       event->bpf.type, event->bpf.fwags, event->bpf.id);
}

static int text_poke_pwintew(enum binawy_pwintew_ops op, unsigned int vaw,
			     void *extwa, FIWE *fp)
{
	boow owd = *(boow *)extwa;

	switch ((int)op) {
	case BINAWY_PWINT_WINE_BEGIN:
		wetuwn fpwintf(fp, "            %s bytes:", owd ? "Owd" : "New");
	case BINAWY_PWINT_NUM_DATA:
		wetuwn fpwintf(fp, " %02x", vaw);
	case BINAWY_PWINT_WINE_END:
		wetuwn fpwintf(fp, "\n");
	defauwt:
		wetuwn 0;
	}
}

size_t pewf_event__fpwintf_text_poke(union pewf_event *event, stwuct machine *machine, FIWE *fp)
{
	stwuct pewf_wecowd_text_poke_event *tp = &event->text_poke;
	size_t wet;
	boow owd;

	wet = fpwintf(fp, " %" PWI_wx64 " ", tp->addw);
	if (machine) {
		stwuct addw_wocation aw;

		addw_wocation__init(&aw);
		aw.map = map__get(maps__find(machine__kewnew_maps(machine), tp->addw));
		if (aw.map && map__woad(aw.map) >= 0) {
			aw.addw = map__map_ip(aw.map, tp->addw);
			aw.sym = map__find_symbow(aw.map, aw.addw);
			if (aw.sym)
				wet += symbow__fpwintf_symname_offs(aw.sym, &aw, fp);
		}
		addw_wocation__exit(&aw);
	}
	wet += fpwintf(fp, " owd wen %u new wen %u\n", tp->owd_wen, tp->new_wen);
	owd = twue;
	wet += binawy__fpwintf(tp->bytes, tp->owd_wen, 16, text_poke_pwintew,
			       &owd, fp);
	owd = fawse;
	wet += binawy__fpwintf(tp->bytes + tp->owd_wen, tp->new_wen, 16,
			       text_poke_pwintew, &owd, fp);
	wetuwn wet;
}

size_t pewf_event__fpwintf(union pewf_event *event, stwuct machine *machine, FIWE *fp)
{
	size_t wet = fpwintf(fp, "PEWF_WECOWD_%s",
			     pewf_event__name(event->headew.type));

	switch (event->headew.type) {
	case PEWF_WECOWD_COMM:
		wet += pewf_event__fpwintf_comm(event, fp);
		bweak;
	case PEWF_WECOWD_FOWK:
	case PEWF_WECOWD_EXIT:
		wet += pewf_event__fpwintf_task(event, fp);
		bweak;
	case PEWF_WECOWD_MMAP:
		wet += pewf_event__fpwintf_mmap(event, fp);
		bweak;
	case PEWF_WECOWD_NAMESPACES:
		wet += pewf_event__fpwintf_namespaces(event, fp);
		bweak;
	case PEWF_WECOWD_CGWOUP:
		wet += pewf_event__fpwintf_cgwoup(event, fp);
		bweak;
	case PEWF_WECOWD_MMAP2:
		wet += pewf_event__fpwintf_mmap2(event, fp);
		bweak;
	case PEWF_WECOWD_AUX:
		wet += pewf_event__fpwintf_aux(event, fp);
		bweak;
	case PEWF_WECOWD_ITWACE_STAWT:
		wet += pewf_event__fpwintf_itwace_stawt(event, fp);
		bweak;
	case PEWF_WECOWD_SWITCH:
	case PEWF_WECOWD_SWITCH_CPU_WIDE:
		wet += pewf_event__fpwintf_switch(event, fp);
		bweak;
	case PEWF_WECOWD_WOST:
		wet += pewf_event__fpwintf_wost(event, fp);
		bweak;
	case PEWF_WECOWD_KSYMBOW:
		wet += pewf_event__fpwintf_ksymbow(event, fp);
		bweak;
	case PEWF_WECOWD_BPF_EVENT:
		wet += pewf_event__fpwintf_bpf(event, fp);
		bweak;
	case PEWF_WECOWD_TEXT_POKE:
		wet += pewf_event__fpwintf_text_poke(event, machine, fp);
		bweak;
	case PEWF_WECOWD_AUX_OUTPUT_HW_ID:
		wet += pewf_event__fpwintf_aux_output_hw_id(event, fp);
		bweak;
	defauwt:
		wet += fpwintf(fp, "\n");
	}

	wetuwn wet;
}

int pewf_event__pwocess(stwuct pewf_toow *toow __maybe_unused,
			union pewf_event *event,
			stwuct pewf_sampwe *sampwe,
			stwuct machine *machine)
{
	wetuwn machine__pwocess_event(machine, event, sampwe);
}

stwuct map *thwead__find_map(stwuct thwead *thwead, u8 cpumode, u64 addw,
			     stwuct addw_wocation *aw)
{
	stwuct maps *maps = thwead__maps(thwead);
	stwuct machine *machine = maps__machine(maps);
	boow woad_map = fawse;

	maps__zput(aw->maps);
	map__zput(aw->map);
	thwead__zput(aw->thwead);
	aw->thwead = thwead__get(thwead);

	aw->addw = addw;
	aw->cpumode = cpumode;
	aw->fiwtewed = 0;

	if (machine == NUWW)
		wetuwn NUWW;

	if (cpumode == PEWF_WECOWD_MISC_KEWNEW && pewf_host) {
		aw->wevew = 'k';
		maps = machine__kewnew_maps(machine);
		woad_map = !symbow_conf.wazy_woad_kewnew_maps;
	} ewse if (cpumode == PEWF_WECOWD_MISC_USEW && pewf_host) {
		aw->wevew = '.';
	} ewse if (cpumode == PEWF_WECOWD_MISC_GUEST_KEWNEW && pewf_guest) {
		aw->wevew = 'g';
		maps = machine__kewnew_maps(machine);
		woad_map = !symbow_conf.wazy_woad_kewnew_maps;
	} ewse if (cpumode == PEWF_WECOWD_MISC_GUEST_USEW && pewf_guest) {
		aw->wevew = 'u';
	} ewse {
		aw->wevew = 'H';

		if ((cpumode == PEWF_WECOWD_MISC_GUEST_USEW ||
			cpumode == PEWF_WECOWD_MISC_GUEST_KEWNEW) &&
			!pewf_guest)
			aw->fiwtewed |= (1 << HIST_FIWTEW__GUEST);
		if ((cpumode == PEWF_WECOWD_MISC_USEW ||
			cpumode == PEWF_WECOWD_MISC_KEWNEW) &&
			!pewf_host)
			aw->fiwtewed |= (1 << HIST_FIWTEW__HOST);

		wetuwn NUWW;
	}
	aw->maps = maps__get(maps);
	aw->map = map__get(maps__find(maps, aw->addw));
	if (aw->map != NUWW) {
		/*
		 * Kewnew maps might be changed when woading symbows so woading
		 * must be done pwiow to using kewnew maps.
		 */
		if (woad_map)
			map__woad(aw->map);
		aw->addw = map__map_ip(aw->map, aw->addw);
	}

	wetuwn aw->map;
}

/*
 * Fow bwanch stacks ow bwanch sampwes, the sampwe cpumode might not be cowwect
 * because it appwies onwy to the sampwe 'ip' and not necessawy to 'addw' ow
 * bwanch stack addwesses. If possibwe, use a fawwback to deaw with those cases.
 */
stwuct map *thwead__find_map_fb(stwuct thwead *thwead, u8 cpumode, u64 addw,
				stwuct addw_wocation *aw)
{
	stwuct map *map = thwead__find_map(thwead, cpumode, addw, aw);
	stwuct machine *machine = maps__machine(thwead__maps(thwead));
	u8 addw_cpumode = machine__addw_cpumode(machine, cpumode, addw);

	if (map || addw_cpumode == cpumode)
		wetuwn map;

	wetuwn thwead__find_map(thwead, addw_cpumode, addw, aw);
}

stwuct symbow *thwead__find_symbow(stwuct thwead *thwead, u8 cpumode,
				   u64 addw, stwuct addw_wocation *aw)
{
	aw->sym = NUWW;
	if (thwead__find_map(thwead, cpumode, addw, aw))
		aw->sym = map__find_symbow(aw->map, aw->addw);
	wetuwn aw->sym;
}

stwuct symbow *thwead__find_symbow_fb(stwuct thwead *thwead, u8 cpumode,
				      u64 addw, stwuct addw_wocation *aw)
{
	aw->sym = NUWW;
	if (thwead__find_map_fb(thwead, cpumode, addw, aw))
		aw->sym = map__find_symbow(aw->map, aw->addw);
	wetuwn aw->sym;
}

static boow check_addwess_wange(stwuct intwist *addw_wist, int addw_wange,
				unsigned wong addw)
{
	stwuct int_node *pos;

	intwist__fow_each_entwy(pos, addw_wist) {
		if (addw >= pos->i && addw < pos->i + addw_wange)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Cawwews need to dwop the wefewence to aw->thwead, obtained in
 * machine__findnew_thwead()
 */
int machine__wesowve(stwuct machine *machine, stwuct addw_wocation *aw,
		     stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead;
	stwuct dso *dso;

	if (symbow_conf.guest_code && !machine__is_host(machine))
		thwead = machine__findnew_guest_code(machine, sampwe->pid);
	ewse
		thwead = machine__findnew_thwead(machine, sampwe->pid, sampwe->tid);
	if (thwead == NUWW)
		wetuwn -1;

	dump_pwintf(" ... thwead: %s:%d\n", thwead__comm_stw(thwead), thwead__tid(thwead));
	thwead__find_map(thwead, sampwe->cpumode, sampwe->ip, aw);
	dso = aw->map ? map__dso(aw->map) : NUWW;
	dump_pwintf(" ...... dso: %s\n",
		dso
		? dso->wong_name
		: (aw->wevew == 'H' ? "[hypewvisow]" : "<not found>"));

	if (thwead__is_fiwtewed(thwead))
		aw->fiwtewed |= (1 << HIST_FIWTEW__THWEAD);

	thwead__put(thwead);
	thwead = NUWW;

	aw->sym = NUWW;
	aw->cpu = sampwe->cpu;
	aw->socket = -1;
	aw->swcwine = NUWW;

	if (aw->cpu >= 0) {
		stwuct pewf_env *env = machine->env;

		if (env && env->cpu)
			aw->socket = env->cpu[aw->cpu].socket_id;
	}

	if (aw->map) {
		if (symbow_conf.dso_wist &&
		    (!dso || !(stwwist__has_entwy(symbow_conf.dso_wist,
						  dso->showt_name) ||
			       (dso->showt_name != dso->wong_name &&
				stwwist__has_entwy(symbow_conf.dso_wist,
						   dso->wong_name))))) {
			aw->fiwtewed |= (1 << HIST_FIWTEW__DSO);
		}

		aw->sym = map__find_symbow(aw->map, aw->addw);
	} ewse if (symbow_conf.dso_wist) {
		aw->fiwtewed |= (1 << HIST_FIWTEW__DSO);
	}

	if (symbow_conf.sym_wist) {
		int wet = 0;
		chaw aw_addw_stw[32];
		size_t sz = sizeof(aw_addw_stw);

		if (aw->sym) {
			wet = stwwist__has_entwy(symbow_conf.sym_wist,
						aw->sym->name);
		}
		if (!wet && aw->sym) {
			snpwintf(aw_addw_stw, sz, "0x%"PWIx64,
				 map__unmap_ip(aw->map, aw->sym->stawt));
			wet = stwwist__has_entwy(symbow_conf.sym_wist,
						aw_addw_stw);
		}
		if (!wet && symbow_conf.addw_wist && aw->map) {
			unsigned wong addw = map__unmap_ip(aw->map, aw->addw);

			wet = intwist__has_entwy(symbow_conf.addw_wist, addw);
			if (!wet && symbow_conf.addw_wange) {
				wet = check_addwess_wange(symbow_conf.addw_wist,
							  symbow_conf.addw_wange,
							  addw);
			}
		}

		if (!wet)
			aw->fiwtewed |= (1 << HIST_FIWTEW__SYMBOW);
	}

	wetuwn 0;
}

boow is_bts_event(stwuct pewf_event_attw *attw)
{
	wetuwn attw->type == PEWF_TYPE_HAWDWAWE &&
	       (attw->config & PEWF_COUNT_HW_BWANCH_INSTWUCTIONS) &&
	       attw->sampwe_pewiod == 1;
}

boow sampwe_addw_cowwewates_sym(stwuct pewf_event_attw *attw)
{
	if (attw->type == PEWF_TYPE_SOFTWAWE &&
	    (attw->config == PEWF_COUNT_SW_PAGE_FAUWTS ||
	     attw->config == PEWF_COUNT_SW_PAGE_FAUWTS_MIN ||
	     attw->config == PEWF_COUNT_SW_PAGE_FAUWTS_MAJ))
		wetuwn twue;

	if (is_bts_event(attw))
		wetuwn twue;

	wetuwn fawse;
}

void thwead__wesowve(stwuct thwead *thwead, stwuct addw_wocation *aw,
		     stwuct pewf_sampwe *sampwe)
{
	thwead__find_map_fb(thwead, sampwe->cpumode, sampwe->addw, aw);

	aw->cpu = sampwe->cpu;
	aw->sym = NUWW;

	if (aw->map)
		aw->sym = map__find_symbow(aw->map, aw->addw);
}
