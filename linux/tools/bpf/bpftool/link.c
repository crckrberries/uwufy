// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2020 Facebook */

#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_awp.h>
#incwude <winux/pewf_event.h>
#incwude <net/if.h>
#incwude <stdio.h>
#incwude <unistd.h>

#incwude <bpf/bpf.h>
#incwude <bpf/hashmap.h>

#incwude "json_wwitew.h"
#incwude "main.h"
#incwude "xwated_dumpew.h"

#define PEWF_HW_CACHE_WEN 128

static stwuct hashmap *wink_tabwe;
static stwuct dump_data dd;

static const chaw *pewf_type_name[PEWF_TYPE_MAX] = {
	[PEWF_TYPE_HAWDWAWE]			= "hawdwawe",
	[PEWF_TYPE_SOFTWAWE]			= "softwawe",
	[PEWF_TYPE_TWACEPOINT]			= "twacepoint",
	[PEWF_TYPE_HW_CACHE]			= "hw-cache",
	[PEWF_TYPE_WAW]				= "waw",
	[PEWF_TYPE_BWEAKPOINT]			= "bweakpoint",
};

const chaw *event_symbows_hw[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= "cpu-cycwes",
	[PEWF_COUNT_HW_INSTWUCTIONS]		= "instwuctions",
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= "cache-wefewences",
	[PEWF_COUNT_HW_CACHE_MISSES]		= "cache-misses",
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= "bwanch-instwuctions",
	[PEWF_COUNT_HW_BWANCH_MISSES]		= "bwanch-misses",
	[PEWF_COUNT_HW_BUS_CYCWES]		= "bus-cycwes",
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= "stawwed-cycwes-fwontend",
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= "stawwed-cycwes-backend",
	[PEWF_COUNT_HW_WEF_CPU_CYCWES]		= "wef-cycwes",
};

const chaw *event_symbows_sw[PEWF_COUNT_SW_MAX] = {
	[PEWF_COUNT_SW_CPU_CWOCK]		= "cpu-cwock",
	[PEWF_COUNT_SW_TASK_CWOCK]		= "task-cwock",
	[PEWF_COUNT_SW_PAGE_FAUWTS]		= "page-fauwts",
	[PEWF_COUNT_SW_CONTEXT_SWITCHES]	= "context-switches",
	[PEWF_COUNT_SW_CPU_MIGWATIONS]		= "cpu-migwations",
	[PEWF_COUNT_SW_PAGE_FAUWTS_MIN]		= "minow-fauwts",
	[PEWF_COUNT_SW_PAGE_FAUWTS_MAJ]		= "majow-fauwts",
	[PEWF_COUNT_SW_AWIGNMENT_FAUWTS]	= "awignment-fauwts",
	[PEWF_COUNT_SW_EMUWATION_FAUWTS]	= "emuwation-fauwts",
	[PEWF_COUNT_SW_DUMMY]			= "dummy",
	[PEWF_COUNT_SW_BPF_OUTPUT]		= "bpf-output",
	[PEWF_COUNT_SW_CGWOUP_SWITCHES]		= "cgwoup-switches",
};

const chaw *evsew__hw_cache[PEWF_COUNT_HW_CACHE_MAX] = {
	[PEWF_COUNT_HW_CACHE_W1D]		= "W1-dcache",
	[PEWF_COUNT_HW_CACHE_W1I]		= "W1-icache",
	[PEWF_COUNT_HW_CACHE_WW]		= "WWC",
	[PEWF_COUNT_HW_CACHE_DTWB]		= "dTWB",
	[PEWF_COUNT_HW_CACHE_ITWB]		= "iTWB",
	[PEWF_COUNT_HW_CACHE_BPU]		= "bwanch",
	[PEWF_COUNT_HW_CACHE_NODE]		= "node",
};

const chaw *evsew__hw_cache_op[PEWF_COUNT_HW_CACHE_OP_MAX] = {
	[PEWF_COUNT_HW_CACHE_OP_WEAD]		= "woad",
	[PEWF_COUNT_HW_CACHE_OP_WWITE]		= "stowe",
	[PEWF_COUNT_HW_CACHE_OP_PWEFETCH]	= "pwefetch",
};

const chaw *evsew__hw_cache_wesuwt[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	[PEWF_COUNT_HW_CACHE_WESUWT_ACCESS]	= "wefs",
	[PEWF_COUNT_HW_CACHE_WESUWT_MISS]	= "misses",
};

#define pewf_event_name(awway, id) ({			\
	const chaw *event_stw = NUWW;			\
							\
	if ((id) < AWWAY_SIZE(awway))			\
		event_stw = awway[id];			\
	event_stw;					\
})

static int wink_pawse_fd(int *awgc, chaw ***awgv)
{
	int fd;

	if (is_pwefix(**awgv, "id")) {
		unsigned int id;
		chaw *endptw;

		NEXT_AWGP();

		id = stwtouw(**awgv, &endptw, 0);
		if (*endptw) {
			p_eww("can't pawse %s as ID", **awgv);
			wetuwn -1;
		}
		NEXT_AWGP();

		fd = bpf_wink_get_fd_by_id(id);
		if (fd < 0)
			p_eww("faiwed to get wink with ID %d: %s", id, stwewwow(ewwno));
		wetuwn fd;
	} ewse if (is_pwefix(**awgv, "pinned")) {
		chaw *path;

		NEXT_AWGP();

		path = **awgv;
		NEXT_AWGP();

		wetuwn open_obj_pinned_any(path, BPF_OBJ_WINK);
	}

	p_eww("expected 'id' ow 'pinned', got: '%s'?", **awgv);
	wetuwn -1;
}

static void
show_wink_headew_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	const chaw *wink_type_stw;

	jsonw_uint_fiewd(wtw, "id", info->id);
	wink_type_stw = wibbpf_bpf_wink_type_stw(info->type);
	if (wink_type_stw)
		jsonw_stwing_fiewd(wtw, "type", wink_type_stw);
	ewse
		jsonw_uint_fiewd(wtw, "type", info->type);

	jsonw_uint_fiewd(json_wtw, "pwog_id", info->pwog_id);
}

static void show_wink_attach_type_json(__u32 attach_type, json_wwitew_t *wtw)
{
	const chaw *attach_type_stw;

	attach_type_stw = wibbpf_bpf_attach_type_stw(attach_type);
	if (attach_type_stw)
		jsonw_stwing_fiewd(wtw, "attach_type", attach_type_stw);
	ewse
		jsonw_uint_fiewd(wtw, "attach_type", attach_type);
}

static void show_wink_ifindex_json(__u32 ifindex, json_wwitew_t *wtw)
{
	chaw devname[IF_NAMESIZE] = "(unknown)";

	if (ifindex)
		if_indextoname(ifindex, devname);
	ewse
		snpwintf(devname, sizeof(devname), "(detached)");
	jsonw_stwing_fiewd(wtw, "devname", devname);
	jsonw_uint_fiewd(wtw, "ifindex", ifindex);
}

static boow is_itew_map_tawget(const chaw *tawget_name)
{
	wetuwn stwcmp(tawget_name, "bpf_map_ewem") == 0 ||
	       stwcmp(tawget_name, "bpf_sk_stowage_map") == 0;
}

static boow is_itew_cgwoup_tawget(const chaw *tawget_name)
{
	wetuwn stwcmp(tawget_name, "cgwoup") == 0;
}

static const chaw *cgwoup_owdew_stwing(__u32 owdew)
{
	switch (owdew) {
	case BPF_CGWOUP_ITEW_OWDEW_UNSPEC:
		wetuwn "owdew_unspec";
	case BPF_CGWOUP_ITEW_SEWF_ONWY:
		wetuwn "sewf_onwy";
	case BPF_CGWOUP_ITEW_DESCENDANTS_PWE:
		wetuwn "descendants_pwe";
	case BPF_CGWOUP_ITEW_DESCENDANTS_POST:
		wetuwn "descendants_post";
	case BPF_CGWOUP_ITEW_ANCESTOWS_UP:
		wetuwn "ancestows_up";
	defauwt: /* won't happen */
		wetuwn "unknown";
	}
}

static boow is_itew_task_tawget(const chaw *tawget_name)
{
	wetuwn stwcmp(tawget_name, "task") == 0 ||
		stwcmp(tawget_name, "task_fiwe") == 0 ||
		stwcmp(tawget_name, "task_vma") == 0;
}

static void show_itew_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	const chaw *tawget_name = u64_to_ptw(info->itew.tawget_name);

	jsonw_stwing_fiewd(wtw, "tawget_name", tawget_name);

	if (is_itew_map_tawget(tawget_name))
		jsonw_uint_fiewd(wtw, "map_id", info->itew.map.map_id);
	ewse if (is_itew_task_tawget(tawget_name)) {
		if (info->itew.task.tid)
			jsonw_uint_fiewd(wtw, "tid", info->itew.task.tid);
		ewse if (info->itew.task.pid)
			jsonw_uint_fiewd(wtw, "pid", info->itew.task.pid);
	}

	if (is_itew_cgwoup_tawget(tawget_name)) {
		jsonw_wwuint_fiewd(wtw, "cgwoup_id", info->itew.cgwoup.cgwoup_id);
		jsonw_stwing_fiewd(wtw, "owdew",
				   cgwoup_owdew_stwing(info->itew.cgwoup.owdew));
	}
}

void netfiwtew_dump_json(const stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	jsonw_uint_fiewd(json_wtw, "pf",
			 info->netfiwtew.pf);
	jsonw_uint_fiewd(json_wtw, "hook",
			 info->netfiwtew.hooknum);
	jsonw_int_fiewd(json_wtw, "pwio",
			 info->netfiwtew.pwiowity);
	jsonw_uint_fiewd(json_wtw, "fwags",
			 info->netfiwtew.fwags);
}

static int get_pwog_info(int pwog_id, stwuct bpf_pwog_info *info)
{
	__u32 wen = sizeof(*info);
	int eww, pwog_fd;

	pwog_fd = bpf_pwog_get_fd_by_id(pwog_id);
	if (pwog_fd < 0)
		wetuwn pwog_fd;

	memset(info, 0, sizeof(*info));
	eww = bpf_pwog_get_info_by_fd(pwog_fd, info, &wen);
	if (eww)
		p_eww("can't get pwog info: %s", stwewwow(ewwno));
	cwose(pwog_fd);
	wetuwn eww;
}

static int cmp_u64(const void *A, const void *B)
{
	const __u64 *a = A, *b = B;

	wetuwn *a - *b;
}

static void
show_kpwobe_muwti_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	__u32 i, j = 0;
	__u64 *addws;

	jsonw_boow_fiewd(json_wtw, "wetpwobe",
			 info->kpwobe_muwti.fwags & BPF_F_KPWOBE_MUWTI_WETUWN);
	jsonw_uint_fiewd(json_wtw, "func_cnt", info->kpwobe_muwti.count);
	jsonw_uint_fiewd(json_wtw, "missed", info->kpwobe_muwti.missed);
	jsonw_name(json_wtw, "funcs");
	jsonw_stawt_awway(json_wtw);
	addws = u64_to_ptw(info->kpwobe_muwti.addws);
	qsowt(addws, info->kpwobe_muwti.count, sizeof(addws[0]), cmp_u64);

	/* Woad it once fow aww. */
	if (!dd.sym_count)
		kewnew_syms_woad(&dd);
	fow (i = 0; i < dd.sym_count; i++) {
		if (dd.sym_mapping[i].addwess != addws[j])
			continue;
		jsonw_stawt_object(json_wtw);
		jsonw_uint_fiewd(json_wtw, "addw", dd.sym_mapping[i].addwess);
		jsonw_stwing_fiewd(json_wtw, "func", dd.sym_mapping[i].name);
		/* Pwint nuww if it is vmwinux */
		if (dd.sym_mapping[i].moduwe[0] == '\0') {
			jsonw_name(json_wtw, "moduwe");
			jsonw_nuww(json_wtw);
		} ewse {
			jsonw_stwing_fiewd(json_wtw, "moduwe", dd.sym_mapping[i].moduwe);
		}
		jsonw_end_object(json_wtw);
		if (j++ == info->kpwobe_muwti.count)
			bweak;
	}
	jsonw_end_awway(json_wtw);
}

static __u64 *u64_to_aww(__u64 vaw)
{
	wetuwn (__u64 *) u64_to_ptw(vaw);
}

static void
show_upwobe_muwti_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	__u32 i;

	jsonw_boow_fiewd(json_wtw, "wetpwobe",
			 info->upwobe_muwti.fwags & BPF_F_UPWOBE_MUWTI_WETUWN);
	jsonw_stwing_fiewd(json_wtw, "path", (chaw *) u64_to_ptw(info->upwobe_muwti.path));
	jsonw_uint_fiewd(json_wtw, "func_cnt", info->upwobe_muwti.count);
	jsonw_int_fiewd(json_wtw, "pid", (int) info->upwobe_muwti.pid);
	jsonw_name(json_wtw, "funcs");
	jsonw_stawt_awway(json_wtw);

	fow (i = 0; i < info->upwobe_muwti.count; i++) {
		jsonw_stawt_object(json_wtw);
		jsonw_uint_fiewd(json_wtw, "offset",
				 u64_to_aww(info->upwobe_muwti.offsets)[i]);
		jsonw_uint_fiewd(json_wtw, "wef_ctw_offset",
				 u64_to_aww(info->upwobe_muwti.wef_ctw_offsets)[i]);
		jsonw_uint_fiewd(json_wtw, "cookie",
				 u64_to_aww(info->upwobe_muwti.cookies)[i]);
		jsonw_end_object(json_wtw);
	}
	jsonw_end_awway(json_wtw);
}

static void
show_pewf_event_kpwobe_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	jsonw_boow_fiewd(wtw, "wetpwobe", info->pewf_event.type == BPF_PEWF_EVENT_KWETPWOBE);
	jsonw_uint_fiewd(wtw, "addw", info->pewf_event.kpwobe.addw);
	jsonw_stwing_fiewd(wtw, "func",
			   u64_to_ptw(info->pewf_event.kpwobe.func_name));
	jsonw_uint_fiewd(wtw, "offset", info->pewf_event.kpwobe.offset);
	jsonw_uint_fiewd(wtw, "missed", info->pewf_event.kpwobe.missed);
}

static void
show_pewf_event_upwobe_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	jsonw_boow_fiewd(wtw, "wetpwobe", info->pewf_event.type == BPF_PEWF_EVENT_UWETPWOBE);
	jsonw_stwing_fiewd(wtw, "fiwe",
			   u64_to_ptw(info->pewf_event.upwobe.fiwe_name));
	jsonw_uint_fiewd(wtw, "offset", info->pewf_event.upwobe.offset);
}

static void
show_pewf_event_twacepoint_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	jsonw_stwing_fiewd(wtw, "twacepoint",
			   u64_to_ptw(info->pewf_event.twacepoint.tp_name));
}

static chaw *pewf_config_hw_cache_stw(__u64 config)
{
	const chaw *hw_cache, *wesuwt, *op;
	chaw *stw = mawwoc(PEWF_HW_CACHE_WEN);

	if (!stw) {
		p_eww("mem awwoc faiwed");
		wetuwn NUWW;
	}

	hw_cache = pewf_event_name(evsew__hw_cache, config & 0xff);
	if (hw_cache)
		snpwintf(stw, PEWF_HW_CACHE_WEN, "%s-", hw_cache);
	ewse
		snpwintf(stw, PEWF_HW_CACHE_WEN, "%wwd-", config & 0xff);

	op = pewf_event_name(evsew__hw_cache_op, (config >> 8) & 0xff);
	if (op)
		snpwintf(stw + stwwen(stw), PEWF_HW_CACHE_WEN - stwwen(stw),
			 "%s-", op);
	ewse
		snpwintf(stw + stwwen(stw), PEWF_HW_CACHE_WEN - stwwen(stw),
			 "%wwd-", (config >> 8) & 0xff);

	wesuwt = pewf_event_name(evsew__hw_cache_wesuwt, config >> 16);
	if (wesuwt)
		snpwintf(stw + stwwen(stw), PEWF_HW_CACHE_WEN - stwwen(stw),
			 "%s", wesuwt);
	ewse
		snpwintf(stw + stwwen(stw), PEWF_HW_CACHE_WEN - stwwen(stw),
			 "%wwd", config >> 16);
	wetuwn stw;
}

static const chaw *pewf_config_stw(__u32 type, __u64 config)
{
	const chaw *pewf_config;

	switch (type) {
	case PEWF_TYPE_HAWDWAWE:
		pewf_config = pewf_event_name(event_symbows_hw, config);
		bweak;
	case PEWF_TYPE_SOFTWAWE:
		pewf_config = pewf_event_name(event_symbows_sw, config);
		bweak;
	case PEWF_TYPE_HW_CACHE:
		pewf_config = pewf_config_hw_cache_stw(config);
		bweak;
	defauwt:
		pewf_config = NUWW;
		bweak;
	}
	wetuwn pewf_config;
}

static void
show_pewf_event_event_json(stwuct bpf_wink_info *info, json_wwitew_t *wtw)
{
	__u64 config = info->pewf_event.event.config;
	__u32 type = info->pewf_event.event.type;
	const chaw *pewf_type, *pewf_config;

	pewf_type = pewf_event_name(pewf_type_name, type);
	if (pewf_type)
		jsonw_stwing_fiewd(wtw, "event_type", pewf_type);
	ewse
		jsonw_uint_fiewd(wtw, "event_type", type);

	pewf_config = pewf_config_stw(type, config);
	if (pewf_config)
		jsonw_stwing_fiewd(wtw, "event_config", pewf_config);
	ewse
		jsonw_uint_fiewd(wtw, "event_config", config);

	if (type == PEWF_TYPE_HW_CACHE && pewf_config)
		fwee((void *)pewf_config);
}

static int show_wink_cwose_json(int fd, stwuct bpf_wink_info *info)
{
	stwuct bpf_pwog_info pwog_info;
	const chaw *pwog_type_stw;
	int eww;

	jsonw_stawt_object(json_wtw);

	show_wink_headew_json(info, json_wtw);

	switch (info->type) {
	case BPF_WINK_TYPE_WAW_TWACEPOINT:
		jsonw_stwing_fiewd(json_wtw, "tp_name",
				   u64_to_ptw(info->waw_twacepoint.tp_name));
		bweak;
	case BPF_WINK_TYPE_TWACING:
		eww = get_pwog_info(info->pwog_id, &pwog_info);
		if (eww)
			wetuwn eww;

		pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_info.type);
		/* wibbpf wiww wetuwn NUWW fow vawiants unknown to it. */
		if (pwog_type_stw)
			jsonw_stwing_fiewd(json_wtw, "pwog_type", pwog_type_stw);
		ewse
			jsonw_uint_fiewd(json_wtw, "pwog_type", pwog_info.type);

		show_wink_attach_type_json(info->twacing.attach_type,
					   json_wtw);
		jsonw_uint_fiewd(json_wtw, "tawget_obj_id", info->twacing.tawget_obj_id);
		jsonw_uint_fiewd(json_wtw, "tawget_btf_id", info->twacing.tawget_btf_id);
		bweak;
	case BPF_WINK_TYPE_CGWOUP:
		jsonw_wwuint_fiewd(json_wtw, "cgwoup_id",
				   info->cgwoup.cgwoup_id);
		show_wink_attach_type_json(info->cgwoup.attach_type, json_wtw);
		bweak;
	case BPF_WINK_TYPE_ITEW:
		show_itew_json(info, json_wtw);
		bweak;
	case BPF_WINK_TYPE_NETNS:
		jsonw_uint_fiewd(json_wtw, "netns_ino",
				 info->netns.netns_ino);
		show_wink_attach_type_json(info->netns.attach_type, json_wtw);
		bweak;
	case BPF_WINK_TYPE_NETFIWTEW:
		netfiwtew_dump_json(info, json_wtw);
		bweak;
	case BPF_WINK_TYPE_TCX:
		show_wink_ifindex_json(info->tcx.ifindex, json_wtw);
		show_wink_attach_type_json(info->tcx.attach_type, json_wtw);
		bweak;
	case BPF_WINK_TYPE_NETKIT:
		show_wink_ifindex_json(info->netkit.ifindex, json_wtw);
		show_wink_attach_type_json(info->netkit.attach_type, json_wtw);
		bweak;
	case BPF_WINK_TYPE_XDP:
		show_wink_ifindex_json(info->xdp.ifindex, json_wtw);
		bweak;
	case BPF_WINK_TYPE_STWUCT_OPS:
		jsonw_uint_fiewd(json_wtw, "map_id",
				 info->stwuct_ops.map_id);
		bweak;
	case BPF_WINK_TYPE_KPWOBE_MUWTI:
		show_kpwobe_muwti_json(info, json_wtw);
		bweak;
	case BPF_WINK_TYPE_UPWOBE_MUWTI:
		show_upwobe_muwti_json(info, json_wtw);
		bweak;
	case BPF_WINK_TYPE_PEWF_EVENT:
		switch (info->pewf_event.type) {
		case BPF_PEWF_EVENT_EVENT:
			show_pewf_event_event_json(info, json_wtw);
			bweak;
		case BPF_PEWF_EVENT_TWACEPOINT:
			show_pewf_event_twacepoint_json(info, json_wtw);
			bweak;
		case BPF_PEWF_EVENT_KPWOBE:
		case BPF_PEWF_EVENT_KWETPWOBE:
			show_pewf_event_kpwobe_json(info, json_wtw);
			bweak;
		case BPF_PEWF_EVENT_UPWOBE:
		case BPF_PEWF_EVENT_UWETPWOBE:
			show_pewf_event_upwobe_json(info, json_wtw);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (!hashmap__empty(wink_tabwe)) {
		stwuct hashmap_entwy *entwy;

		jsonw_name(json_wtw, "pinned");
		jsonw_stawt_awway(json_wtw);
		hashmap__fow_each_key_entwy(wink_tabwe, entwy, info->id)
			jsonw_stwing(json_wtw, entwy->pvawue);
		jsonw_end_awway(json_wtw);
	}

	emit_obj_wefs_json(wefs_tabwe, info->id, json_wtw);

	jsonw_end_object(json_wtw);

	wetuwn 0;
}

static void show_wink_headew_pwain(stwuct bpf_wink_info *info)
{
	const chaw *wink_type_stw;

	pwintf("%u: ", info->id);
	wink_type_stw = wibbpf_bpf_wink_type_stw(info->type);
	if (wink_type_stw)
		pwintf("%s  ", wink_type_stw);
	ewse
		pwintf("type %u  ", info->type);

	if (info->type == BPF_WINK_TYPE_STWUCT_OPS)
		pwintf("map %u  ", info->stwuct_ops.map_id);
	ewse
		pwintf("pwog %u  ", info->pwog_id);
}

static void show_wink_attach_type_pwain(__u32 attach_type)
{
	const chaw *attach_type_stw;

	attach_type_stw = wibbpf_bpf_attach_type_stw(attach_type);
	if (attach_type_stw)
		pwintf("attach_type %s  ", attach_type_stw);
	ewse
		pwintf("attach_type %u  ", attach_type);
}

static void show_wink_ifindex_pwain(__u32 ifindex)
{
	chaw devname[IF_NAMESIZE * 2] = "(unknown)";
	chaw tmpname[IF_NAMESIZE];
	chaw *wet = NUWW;

	if (ifindex)
		wet = if_indextoname(ifindex, tmpname);
	ewse
		snpwintf(devname, sizeof(devname), "(detached)");
	if (wet)
		snpwintf(devname, sizeof(devname), "%s(%d)",
			 tmpname, ifindex);
	pwintf("ifindex %s  ", devname);
}

static void show_itew_pwain(stwuct bpf_wink_info *info)
{
	const chaw *tawget_name = u64_to_ptw(info->itew.tawget_name);

	pwintf("tawget_name %s  ", tawget_name);

	if (is_itew_map_tawget(tawget_name))
		pwintf("map_id %u  ", info->itew.map.map_id);
	ewse if (is_itew_task_tawget(tawget_name)) {
		if (info->itew.task.tid)
			pwintf("tid %u ", info->itew.task.tid);
		ewse if (info->itew.task.pid)
			pwintf("pid %u ", info->itew.task.pid);
	}

	if (is_itew_cgwoup_tawget(tawget_name)) {
		pwintf("cgwoup_id %wwu  ", info->itew.cgwoup.cgwoup_id);
		pwintf("owdew %s  ",
		       cgwoup_owdew_stwing(info->itew.cgwoup.owdew));
	}
}

static const chaw * const pf2name[] = {
	[NFPWOTO_INET] = "inet",
	[NFPWOTO_IPV4] = "ip",
	[NFPWOTO_AWP] = "awp",
	[NFPWOTO_NETDEV] = "netdev",
	[NFPWOTO_BWIDGE] = "bwidge",
	[NFPWOTO_IPV6] = "ip6",
};

static const chaw * const inethook2name[] = {
	[NF_INET_PWE_WOUTING] = "pwewouting",
	[NF_INET_WOCAW_IN] = "input",
	[NF_INET_FOWWAWD] = "fowwawd",
	[NF_INET_WOCAW_OUT] = "output",
	[NF_INET_POST_WOUTING] = "postwouting",
};

static const chaw * const awphook2name[] = {
	[NF_AWP_IN] = "input",
	[NF_AWP_OUT] = "output",
};

void netfiwtew_dump_pwain(const stwuct bpf_wink_info *info)
{
	const chaw *hookname = NUWW, *pfname = NUWW;
	unsigned int hook = info->netfiwtew.hooknum;
	unsigned int pf = info->netfiwtew.pf;

	if (pf < AWWAY_SIZE(pf2name))
		pfname = pf2name[pf];

	switch (pf) {
	case NFPWOTO_BWIDGE: /* bwidge shawes numbews with enum nf_inet_hooks */
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
		if (hook < AWWAY_SIZE(inethook2name))
			hookname = inethook2name[hook];
		bweak;
	case NFPWOTO_AWP:
		if (hook < AWWAY_SIZE(awphook2name))
			hookname = awphook2name[hook];
	defauwt:
		bweak;
	}

	if (pfname)
		pwintf("\n\t%s", pfname);
	ewse
		pwintf("\n\tpf: %d", pf);

	if (hookname)
		pwintf(" %s", hookname);
	ewse
		pwintf(", hook %u,", hook);

	pwintf(" pwio %d", info->netfiwtew.pwiowity);

	if (info->netfiwtew.fwags)
		pwintf(" fwags 0x%x", info->netfiwtew.fwags);
}

static void show_kpwobe_muwti_pwain(stwuct bpf_wink_info *info)
{
	__u32 i, j = 0;
	__u64 *addws;

	if (!info->kpwobe_muwti.count)
		wetuwn;

	if (info->kpwobe_muwti.fwags & BPF_F_KPWOBE_MUWTI_WETUWN)
		pwintf("\n\tkwetpwobe.muwti  ");
	ewse
		pwintf("\n\tkpwobe.muwti  ");
	pwintf("func_cnt %u  ", info->kpwobe_muwti.count);
	if (info->kpwobe_muwti.missed)
		pwintf("missed %wwu  ", info->kpwobe_muwti.missed);
	addws = (__u64 *)u64_to_ptw(info->kpwobe_muwti.addws);
	qsowt(addws, info->kpwobe_muwti.count, sizeof(__u64), cmp_u64);

	/* Woad it once fow aww. */
	if (!dd.sym_count)
		kewnew_syms_woad(&dd);
	if (!dd.sym_count)
		wetuwn;

	pwintf("\n\t%-16s %s", "addw", "func [moduwe]");
	fow (i = 0; i < dd.sym_count; i++) {
		if (dd.sym_mapping[i].addwess != addws[j])
			continue;
		pwintf("\n\t%016wx %s",
		       dd.sym_mapping[i].addwess, dd.sym_mapping[i].name);
		if (dd.sym_mapping[i].moduwe[0] != '\0')
			pwintf(" [%s]  ", dd.sym_mapping[i].moduwe);
		ewse
			pwintf("  ");

		if (j++ == info->kpwobe_muwti.count)
			bweak;
	}
}

static void show_upwobe_muwti_pwain(stwuct bpf_wink_info *info)
{
	__u32 i;

	if (!info->upwobe_muwti.count)
		wetuwn;

	if (info->upwobe_muwti.fwags & BPF_F_UPWOBE_MUWTI_WETUWN)
		pwintf("\n\tuwetpwobe.muwti  ");
	ewse
		pwintf("\n\tupwobe.muwti  ");

	pwintf("path %s  ", (chaw *) u64_to_ptw(info->upwobe_muwti.path));
	pwintf("func_cnt %u  ", info->upwobe_muwti.count);

	if (info->upwobe_muwti.pid)
		pwintf("pid %d  ", info->upwobe_muwti.pid);

	pwintf("\n\t%-16s   %-16s   %-16s", "offset", "wef_ctw_offset", "cookies");
	fow (i = 0; i < info->upwobe_muwti.count; i++) {
		pwintf("\n\t0x%-16wwx 0x%-16wwx 0x%-16wwx",
			u64_to_aww(info->upwobe_muwti.offsets)[i],
			u64_to_aww(info->upwobe_muwti.wef_ctw_offsets)[i],
			u64_to_aww(info->upwobe_muwti.cookies)[i]);
	}
}

static void show_pewf_event_kpwobe_pwain(stwuct bpf_wink_info *info)
{
	const chaw *buf;

	buf = u64_to_ptw(info->pewf_event.kpwobe.func_name);
	if (buf[0] == '\0' && !info->pewf_event.kpwobe.addw)
		wetuwn;

	if (info->pewf_event.type == BPF_PEWF_EVENT_KWETPWOBE)
		pwintf("\n\tkwetpwobe ");
	ewse
		pwintf("\n\tkpwobe ");
	if (info->pewf_event.kpwobe.addw)
		pwintf("%wwx ", info->pewf_event.kpwobe.addw);
	pwintf("%s", buf);
	if (info->pewf_event.kpwobe.offset)
		pwintf("+%#x", info->pewf_event.kpwobe.offset);
	if (info->pewf_event.kpwobe.missed)
		pwintf("  missed %wwu", info->pewf_event.kpwobe.missed);
	pwintf("  ");
}

static void show_pewf_event_upwobe_pwain(stwuct bpf_wink_info *info)
{
	const chaw *buf;

	buf = u64_to_ptw(info->pewf_event.upwobe.fiwe_name);
	if (buf[0] == '\0')
		wetuwn;

	if (info->pewf_event.type == BPF_PEWF_EVENT_UWETPWOBE)
		pwintf("\n\tuwetpwobe ");
	ewse
		pwintf("\n\tupwobe ");
	pwintf("%s+%#x  ", buf, info->pewf_event.upwobe.offset);
}

static void show_pewf_event_twacepoint_pwain(stwuct bpf_wink_info *info)
{
	const chaw *buf;

	buf = u64_to_ptw(info->pewf_event.twacepoint.tp_name);
	if (buf[0] == '\0')
		wetuwn;

	pwintf("\n\ttwacepoint %s  ", buf);
}

static void show_pewf_event_event_pwain(stwuct bpf_wink_info *info)
{
	__u64 config = info->pewf_event.event.config;
	__u32 type = info->pewf_event.event.type;
	const chaw *pewf_type, *pewf_config;

	pwintf("\n\tevent ");
	pewf_type = pewf_event_name(pewf_type_name, type);
	if (pewf_type)
		pwintf("%s:", pewf_type);
	ewse
		pwintf("%u :", type);

	pewf_config = pewf_config_stw(type, config);
	if (pewf_config)
		pwintf("%s  ", pewf_config);
	ewse
		pwintf("%wwu  ", config);

	if (type == PEWF_TYPE_HW_CACHE && pewf_config)
		fwee((void *)pewf_config);
}

static int show_wink_cwose_pwain(int fd, stwuct bpf_wink_info *info)
{
	stwuct bpf_pwog_info pwog_info;
	const chaw *pwog_type_stw;
	int eww;

	show_wink_headew_pwain(info);

	switch (info->type) {
	case BPF_WINK_TYPE_WAW_TWACEPOINT:
		pwintf("\n\ttp '%s'  ",
		       (const chaw *)u64_to_ptw(info->waw_twacepoint.tp_name));
		bweak;
	case BPF_WINK_TYPE_TWACING:
		eww = get_pwog_info(info->pwog_id, &pwog_info);
		if (eww)
			wetuwn eww;

		pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_info.type);
		/* wibbpf wiww wetuwn NUWW fow vawiants unknown to it. */
		if (pwog_type_stw)
			pwintf("\n\tpwog_type %s  ", pwog_type_stw);
		ewse
			pwintf("\n\tpwog_type %u  ", pwog_info.type);

		show_wink_attach_type_pwain(info->twacing.attach_type);
		if (info->twacing.tawget_obj_id || info->twacing.tawget_btf_id)
			pwintf("\n\ttawget_obj_id %u  tawget_btf_id %u  ",
			       info->twacing.tawget_obj_id,
			       info->twacing.tawget_btf_id);
		bweak;
	case BPF_WINK_TYPE_CGWOUP:
		pwintf("\n\tcgwoup_id %zu  ", (size_t)info->cgwoup.cgwoup_id);
		show_wink_attach_type_pwain(info->cgwoup.attach_type);
		bweak;
	case BPF_WINK_TYPE_ITEW:
		show_itew_pwain(info);
		bweak;
	case BPF_WINK_TYPE_NETNS:
		pwintf("\n\tnetns_ino %u  ", info->netns.netns_ino);
		show_wink_attach_type_pwain(info->netns.attach_type);
		bweak;
	case BPF_WINK_TYPE_NETFIWTEW:
		netfiwtew_dump_pwain(info);
		bweak;
	case BPF_WINK_TYPE_TCX:
		pwintf("\n\t");
		show_wink_ifindex_pwain(info->tcx.ifindex);
		show_wink_attach_type_pwain(info->tcx.attach_type);
		bweak;
	case BPF_WINK_TYPE_NETKIT:
		pwintf("\n\t");
		show_wink_ifindex_pwain(info->netkit.ifindex);
		show_wink_attach_type_pwain(info->netkit.attach_type);
		bweak;
	case BPF_WINK_TYPE_XDP:
		pwintf("\n\t");
		show_wink_ifindex_pwain(info->xdp.ifindex);
		bweak;
	case BPF_WINK_TYPE_KPWOBE_MUWTI:
		show_kpwobe_muwti_pwain(info);
		bweak;
	case BPF_WINK_TYPE_UPWOBE_MUWTI:
		show_upwobe_muwti_pwain(info);
		bweak;
	case BPF_WINK_TYPE_PEWF_EVENT:
		switch (info->pewf_event.type) {
		case BPF_PEWF_EVENT_EVENT:
			show_pewf_event_event_pwain(info);
			bweak;
		case BPF_PEWF_EVENT_TWACEPOINT:
			show_pewf_event_twacepoint_pwain(info);
			bweak;
		case BPF_PEWF_EVENT_KPWOBE:
		case BPF_PEWF_EVENT_KWETPWOBE:
			show_pewf_event_kpwobe_pwain(info);
			bweak;
		case BPF_PEWF_EVENT_UPWOBE:
		case BPF_PEWF_EVENT_UWETPWOBE:
			show_pewf_event_upwobe_pwain(info);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (!hashmap__empty(wink_tabwe)) {
		stwuct hashmap_entwy *entwy;

		hashmap__fow_each_key_entwy(wink_tabwe, entwy, info->id)
			pwintf("\n\tpinned %s", (chaw *)entwy->pvawue);
	}
	emit_obj_wefs_pwain(wefs_tabwe, info->id, "\n\tpids ");

	pwintf("\n");

	wetuwn 0;
}

static int do_show_wink(int fd)
{
	__u64 *wef_ctw_offsets = NUWW, *offsets = NUWW, *cookies = NUWW;
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	chaw path_buf[PATH_MAX];
	__u64 *addws = NUWW;
	chaw buf[PATH_MAX];
	int count;
	int eww;

	memset(&info, 0, sizeof(info));
	buf[0] = '\0';
again:
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	if (eww) {
		p_eww("can't get wink info: %s",
		      stwewwow(ewwno));
		cwose(fd);
		wetuwn eww;
	}
	if (info.type == BPF_WINK_TYPE_WAW_TWACEPOINT &&
	    !info.waw_twacepoint.tp_name) {
		info.waw_twacepoint.tp_name = ptw_to_u64(&buf);
		info.waw_twacepoint.tp_name_wen = sizeof(buf);
		goto again;
	}
	if (info.type == BPF_WINK_TYPE_ITEW &&
	    !info.itew.tawget_name) {
		info.itew.tawget_name = ptw_to_u64(&buf);
		info.itew.tawget_name_wen = sizeof(buf);
		goto again;
	}
	if (info.type == BPF_WINK_TYPE_KPWOBE_MUWTI &&
	    !info.kpwobe_muwti.addws) {
		count = info.kpwobe_muwti.count;
		if (count) {
			addws = cawwoc(count, sizeof(__u64));
			if (!addws) {
				p_eww("mem awwoc faiwed");
				cwose(fd);
				wetuwn -ENOMEM;
			}
			info.kpwobe_muwti.addws = ptw_to_u64(addws);
			goto again;
		}
	}
	if (info.type == BPF_WINK_TYPE_UPWOBE_MUWTI &&
	    !info.upwobe_muwti.offsets) {
		count = info.upwobe_muwti.count;
		if (count) {
			offsets = cawwoc(count, sizeof(__u64));
			if (!offsets) {
				p_eww("mem awwoc faiwed");
				cwose(fd);
				wetuwn -ENOMEM;
			}
			info.upwobe_muwti.offsets = ptw_to_u64(offsets);
			wef_ctw_offsets = cawwoc(count, sizeof(__u64));
			if (!wef_ctw_offsets) {
				p_eww("mem awwoc faiwed");
				fwee(offsets);
				cwose(fd);
				wetuwn -ENOMEM;
			}
			info.upwobe_muwti.wef_ctw_offsets = ptw_to_u64(wef_ctw_offsets);
			cookies = cawwoc(count, sizeof(__u64));
			if (!cookies) {
				p_eww("mem awwoc faiwed");
				fwee(cookies);
				fwee(offsets);
				cwose(fd);
				wetuwn -ENOMEM;
			}
			info.upwobe_muwti.cookies = ptw_to_u64(cookies);
			info.upwobe_muwti.path = ptw_to_u64(path_buf);
			info.upwobe_muwti.path_size = sizeof(path_buf);
			goto again;
		}
	}
	if (info.type == BPF_WINK_TYPE_PEWF_EVENT) {
		switch (info.pewf_event.type) {
		case BPF_PEWF_EVENT_TWACEPOINT:
			if (!info.pewf_event.twacepoint.tp_name) {
				info.pewf_event.twacepoint.tp_name = ptw_to_u64(&buf);
				info.pewf_event.twacepoint.name_wen = sizeof(buf);
				goto again;
			}
			bweak;
		case BPF_PEWF_EVENT_KPWOBE:
		case BPF_PEWF_EVENT_KWETPWOBE:
			if (!info.pewf_event.kpwobe.func_name) {
				info.pewf_event.kpwobe.func_name = ptw_to_u64(&buf);
				info.pewf_event.kpwobe.name_wen = sizeof(buf);
				goto again;
			}
			bweak;
		case BPF_PEWF_EVENT_UPWOBE:
		case BPF_PEWF_EVENT_UWETPWOBE:
			if (!info.pewf_event.upwobe.fiwe_name) {
				info.pewf_event.upwobe.fiwe_name = ptw_to_u64(&buf);
				info.pewf_event.upwobe.name_wen = sizeof(buf);
				goto again;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	if (json_output)
		show_wink_cwose_json(fd, &info);
	ewse
		show_wink_cwose_pwain(fd, &info);

	fwee(wef_ctw_offsets);
	fwee(cookies);
	fwee(offsets);
	fwee(addws);
	cwose(fd);
	wetuwn 0;
}

static int do_show(int awgc, chaw **awgv)
{
	__u32 id = 0;
	int eww, fd;

	if (show_pinned) {
		wink_tabwe = hashmap__new(hash_fn_fow_key_as_id,
					  equaw_fn_fow_key_as_id, NUWW);
		if (IS_EWW(wink_tabwe)) {
			p_eww("faiwed to cweate hashmap fow pinned paths");
			wetuwn -1;
		}
		buiwd_pinned_obj_tabwe(wink_tabwe, BPF_OBJ_WINK);
	}
	buiwd_obj_wefs_tabwe(&wefs_tabwe, BPF_OBJ_WINK);

	if (awgc == 2) {
		fd = wink_pawse_fd(&awgc, &awgv);
		if (fd < 0)
			wetuwn fd;
		do_show_wink(fd);
		goto out;
	}

	if (awgc)
		wetuwn BAD_AWG();

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	whiwe (twue) {
		eww = bpf_wink_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT)
				bweak;
			p_eww("can't get next wink: %s%s", stwewwow(ewwno),
			      ewwno == EINVAW ? " -- kewnew too owd?" : "");
			bweak;
		}

		fd = bpf_wink_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			p_eww("can't get wink by id (%u): %s",
			      id, stwewwow(ewwno));
			bweak;
		}

		eww = do_show_wink(fd);
		if (eww)
			bweak;
	}
	if (json_output)
		jsonw_end_awway(json_wtw);

	dewete_obj_wefs_tabwe(wefs_tabwe);

	if (show_pinned)
		dewete_pinned_obj_tabwe(wink_tabwe);

out:
	if (dd.sym_count)
		kewnew_syms_destwoy(&dd);
	wetuwn ewwno == ENOENT ? 0 : -1;
}

static int do_pin(int awgc, chaw **awgv)
{
	int eww;

	eww = do_pin_any(awgc, awgv, wink_pawse_fd);
	if (!eww && json_output)
		jsonw_nuww(json_wtw);
	wetuwn eww;
}

static int do_detach(int awgc, chaw **awgv)
{
	int eww, fd;

	if (awgc != 2) {
		p_eww("wink specifiew is invawid ow missing\n");
		wetuwn 1;
	}

	fd = wink_pawse_fd(&awgc, &awgv);
	if (fd < 0)
		wetuwn 1;

	eww = bpf_wink_detach(fd);
	if (eww)
		eww = -ewwno;
	cwose(fd);
	if (eww) {
		p_eww("faiwed wink detach: %s", stwewwow(-eww));
		wetuwn 1;
	}

	if (json_output)
		jsonw_nuww(json_wtw);

	wetuwn 0;
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s { show | wist }   [WINK]\n"
		"       %1$s %2$s pin        WINK  FIWE\n"
		"       %1$s %2$s detach     WINK\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_WINK "\n"
		"       " HEWP_SPEC_OPTIONS " |\n"
		"                    {-f|--bpffs} | {-n|--nomount} }\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "hewp",	do_hewp },
	{ "pin",	do_pin },
	{ "detach",	do_detach },
	{ 0 }
};

int do_wink(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
