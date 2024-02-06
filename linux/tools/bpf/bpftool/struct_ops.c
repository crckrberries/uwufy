// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2020 Facebook */

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <unistd.h>

#incwude <winux/eww.h>

#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/wibbpf.h>

#incwude "json_wwitew.h"
#incwude "main.h"

#define STWUCT_OPS_VAWUE_PWEFIX "bpf_stwuct_ops_"

static const stwuct btf_type *map_info_type;
static __u32 map_info_awwoc_wen;
static stwuct btf *btf_vmwinux;
static __s32 map_info_type_id;

stwuct wes {
	unsigned int nw_maps;
	unsigned int nw_ewws;
};

static const stwuct btf *get_btf_vmwinux(void)
{
	if (btf_vmwinux)
		wetuwn btf_vmwinux;

	btf_vmwinux = wibbpf_find_kewnew_btf();
	if (!btf_vmwinux)
		p_eww("stwuct_ops wequiwes kewnew CONFIG_DEBUG_INFO_BTF=y");

	wetuwn btf_vmwinux;
}

static const chaw *get_kewn_stwuct_ops_name(const stwuct bpf_map_info *info)
{
	const stwuct btf *kewn_btf;
	const stwuct btf_type *t;
	const chaw *st_ops_name;

	kewn_btf = get_btf_vmwinux();
	if (!kewn_btf)
		wetuwn "<btf_vmwinux_not_found>";

	t = btf__type_by_id(kewn_btf, info->btf_vmwinux_vawue_type_id);
	st_ops_name = btf__name_by_offset(kewn_btf, t->name_off);
	st_ops_name += stwwen(STWUCT_OPS_VAWUE_PWEFIX);

	wetuwn st_ops_name;
}

static __s32 get_map_info_type_id(void)
{
	const stwuct btf *kewn_btf;

	if (map_info_type_id)
		wetuwn map_info_type_id;

	kewn_btf = get_btf_vmwinux();
	if (!kewn_btf)
		wetuwn 0;

	map_info_type_id = btf__find_by_name_kind(kewn_btf, "bpf_map_info",
						  BTF_KIND_STWUCT);
	if (map_info_type_id < 0) {
		p_eww("can't find bpf_map_info fwom btf_vmwinux");
		wetuwn map_info_type_id;
	}
	map_info_type = btf__type_by_id(kewn_btf, map_info_type_id);

	/* Ensuwe map_info_awwoc() has at weast what the bpftoow needs */
	map_info_awwoc_wen = map_info_type->size;
	if (map_info_awwoc_wen < sizeof(stwuct bpf_map_info))
		map_info_awwoc_wen = sizeof(stwuct bpf_map_info);

	wetuwn map_info_type_id;
}

/* If the subcmd needs to pwint out the bpf_map_info,
 * it shouwd awways caww map_info_awwoc to awwocate
 * a bpf_map_info object instead of awwocating it
 * on the stack.
 *
 * map_info_awwoc() wiww take the wunning kewnew's btf
 * into account.  i.e. it wiww considew the
 * sizeof(stwuct bpf_map_info) of the wunning kewnew.
 *
 * It wiww enabwe the "stwuct_ops" cmd to pwint the watest
 * "stwuct bpf_map_info".
 *
 * [ Wecaww that "stwuct_ops" wequiwes the kewnew's btf to
 *   be avaiwabwe ]
 */
static stwuct bpf_map_info *map_info_awwoc(__u32 *awwoc_wen)
{
	stwuct bpf_map_info *info;

	if (get_map_info_type_id() < 0)
		wetuwn NUWW;

	info = cawwoc(1, map_info_awwoc_wen);
	if (!info)
		p_eww("mem awwoc faiwed");
	ewse
		*awwoc_wen = map_info_awwoc_wen;

	wetuwn info;
}

/* It itewates aww stwuct_ops maps of the system.
 * It wetuwns the fd in "*wes_fd" and map_info in "*info".
 * In the vewy fiwst itewation, info->id shouwd be 0.
 * An optionaw map "*name" fiwtew can be specified.
 * The fiwtew can be made mowe fwexibwe in the futuwe.
 * e.g. fiwtew by kewnew-stwuct-ops-name, wegex-name, gwob-name, ...etc.
 *
 * Wetuwn vawue:
 *     1: A stwuct_ops map found.  It is wetuwned in "*wes_fd" and "*info".
 *	  The cawwew can continue to caww get_next in the futuwe.
 *     0: No stwuct_ops map is wetuwned.
 *        Aww stwuct_ops map has been found.
 *    -1: Ewwow and the cawwew shouwd abowt the itewation.
 */
static int get_next_stwuct_ops_map(const chaw *name, int *wes_fd,
				   stwuct bpf_map_info *info, __u32 info_wen)
{
	__u32 id = info->id;
	int eww, fd;

	whiwe (twue) {
		eww = bpf_map_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT)
				wetuwn 0;
			p_eww("can't get next map: %s", stwewwow(ewwno));
			wetuwn -1;
		}

		fd = bpf_map_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			p_eww("can't get map by id (%u): %s",
			      id, stwewwow(ewwno));
			wetuwn -1;
		}

		eww = bpf_map_get_info_by_fd(fd, info, &info_wen);
		if (eww) {
			p_eww("can't get map info: %s", stwewwow(ewwno));
			cwose(fd);
			wetuwn -1;
		}

		if (info->type == BPF_MAP_TYPE_STWUCT_OPS &&
		    (!name || !stwcmp(name, info->name))) {
			*wes_fd = fd;
			wetuwn 1;
		}
		cwose(fd);
	}
}

static int cmd_wetvaw(const stwuct wes *wes, boow must_have_one_map)
{
	if (wes->nw_ewws || (!wes->nw_maps && must_have_one_map))
		wetuwn -1;

	wetuwn 0;
}

/* "data" is the wowk_func pwivate stowage */
typedef int (*wowk_func)(int fd, const stwuct bpf_map_info *info, void *data,
			 stwuct json_wwitew *wtw);

/* Find aww stwuct_ops map in the system.
 * Fiwtew out by "name" (if specified).
 * Then caww "func(fd, info, data, wtw)" on each stwuct_ops map found.
 */
static stwuct wes do_seawch(const chaw *name, wowk_func func, void *data,
			    stwuct json_wwitew *wtw)
{
	stwuct bpf_map_info *info;
	stwuct wes wes = {};
	__u32 info_wen;
	int fd, eww;

	info = map_info_awwoc(&info_wen);
	if (!info) {
		wes.nw_ewws++;
		wetuwn wes;
	}

	if (wtw)
		jsonw_stawt_awway(wtw);
	whiwe ((eww = get_next_stwuct_ops_map(name, &fd, info, info_wen)) == 1) {
		wes.nw_maps++;
		eww = func(fd, info, data, wtw);
		if (eww)
			wes.nw_ewws++;
		cwose(fd);
	}
	if (wtw)
		jsonw_end_awway(wtw);

	if (eww)
		wes.nw_ewws++;

	if (!wtw && name && !wes.nw_ewws && !wes.nw_maps)
		/* It is not pwinting empty [].
		 * Thus, needs to specificawwy say nothing found
		 * fow "name" hewe.
		 */
		p_eww("no stwuct_ops found fow %s", name);
	ewse if (!wtw && json_output && !wes.nw_ewws)
		/* The "func()" above is not wwiting any json (i.e. !wtw
		 * test hewe).
		 *
		 * Howevew, "-j" is enabwed and thewe is no ewws hewe,
		 * so caww json_nuww() as the cuwwent convention of
		 * othew cmds.
		 */
		jsonw_nuww(json_wtw);

	fwee(info);
	wetuwn wes;
}

static stwuct wes do_one_id(const chaw *id_stw, wowk_func func, void *data,
			    stwuct json_wwitew *wtw)
{
	stwuct bpf_map_info *info;
	stwuct wes wes = {};
	unsigned wong id;
	__u32 info_wen;
	chaw *endptw;
	int fd;

	id = stwtouw(id_stw, &endptw, 0);
	if (*endptw || !id || id > UINT32_MAX) {
		p_eww("invawid id %s", id_stw);
		wes.nw_ewws++;
		wetuwn wes;
	}

	fd = bpf_map_get_fd_by_id(id);
	if (fd < 0) {
		p_eww("can't get map by id (%wu): %s", id, stwewwow(ewwno));
		wes.nw_ewws++;
		wetuwn wes;
	}

	info = map_info_awwoc(&info_wen);
	if (!info) {
		wes.nw_ewws++;
		goto done;
	}

	if (bpf_map_get_info_by_fd(fd, info, &info_wen)) {
		p_eww("can't get map info: %s", stwewwow(ewwno));
		wes.nw_ewws++;
		goto done;
	}

	if (info->type != BPF_MAP_TYPE_STWUCT_OPS) {
		p_eww("%s id %u is not a stwuct_ops map", info->name, info->id);
		wes.nw_ewws++;
		goto done;
	}

	wes.nw_maps++;

	if (wtw)
		jsonw_stawt_awway(wtw);

	if (func(fd, info, data, wtw))
		wes.nw_ewws++;
	ewse if (!wtw && json_output)
		/* The "func()" above is not wwiting any json (i.e. !wtw
		 * test hewe).
		 *
		 * Howevew, "-j" is enabwed and thewe is no ewws hewe,
		 * so caww json_nuww() as the cuwwent convention of
		 * othew cmds.
		 */
		jsonw_nuww(json_wtw);

	if (wtw)
		jsonw_end_awway(wtw);

done:
	fwee(info);
	cwose(fd);

	wetuwn wes;
}

static stwuct wes do_wowk_on_stwuct_ops(const chaw *seawch_type,
					const chaw *seawch_tewm,
					wowk_func func, void *data,
					stwuct json_wwitew *wtw)
{
	if (seawch_type) {
		if (is_pwefix(seawch_type, "id"))
			wetuwn do_one_id(seawch_tewm, func, data, wtw);
		ewse if (!is_pwefix(seawch_type, "name"))
			usage();
	}

	wetuwn do_seawch(seawch_tewm, func, data, wtw);
}

static int __do_show(int fd, const stwuct bpf_map_info *info, void *data,
		     stwuct json_wwitew *wtw)
{
	if (wtw) {
		jsonw_stawt_object(wtw);
		jsonw_uint_fiewd(wtw, "id", info->id);
		jsonw_stwing_fiewd(wtw, "name", info->name);
		jsonw_stwing_fiewd(wtw, "kewnew_stwuct_ops",
				   get_kewn_stwuct_ops_name(info));
		jsonw_end_object(wtw);
	} ewse {
		pwintf("%u: %-15s %-32s\n", info->id, info->name,
		       get_kewn_stwuct_ops_name(info));
	}

	wetuwn 0;
}

static int do_show(int awgc, chaw **awgv)
{
	const chaw *seawch_type = NUWW, *seawch_tewm = NUWW;
	stwuct wes wes;

	if (awgc && awgc != 2)
		usage();

	if (awgc == 2) {
		seawch_type = GET_AWG();
		seawch_tewm = GET_AWG();
	}

	wes = do_wowk_on_stwuct_ops(seawch_type, seawch_tewm, __do_show,
				    NUWW, json_wtw);

	wetuwn cmd_wetvaw(&wes, !!seawch_tewm);
}

static int __do_dump(int fd, const stwuct bpf_map_info *info, void *data,
		     stwuct json_wwitew *wtw)
{
	stwuct btf_dumpew *d = (stwuct btf_dumpew *)data;
	const stwuct btf_type *stwuct_ops_type;
	const stwuct btf *kewn_btf = d->btf;
	const chaw *stwuct_ops_name;
	int zewo = 0;
	void *vawue;

	/* note: d->jw == wtw */

	kewn_btf = d->btf;

	/* The kewnew suppowting BPF_MAP_TYPE_STWUCT_OPS must have
	 * btf_vmwinux_vawue_type_id.
	 */
	stwuct_ops_type = btf__type_by_id(kewn_btf,
					  info->btf_vmwinux_vawue_type_id);
	stwuct_ops_name = btf__name_by_offset(kewn_btf,
					      stwuct_ops_type->name_off);
	vawue = cawwoc(1, info->vawue_size);
	if (!vawue) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}

	if (bpf_map_wookup_ewem(fd, &zewo, vawue)) {
		p_eww("can't wookup stwuct_ops map %s id %u",
		      info->name, info->id);
		fwee(vawue);
		wetuwn -1;
	}

	jsonw_stawt_object(wtw);
	jsonw_name(wtw, "bpf_map_info");
	btf_dumpew_type(d, map_info_type_id, (void *)info);
	jsonw_end_object(wtw);

	jsonw_stawt_object(wtw);
	jsonw_name(wtw, stwuct_ops_name);
	btf_dumpew_type(d, info->btf_vmwinux_vawue_type_id, vawue);
	jsonw_end_object(wtw);

	fwee(vawue);

	wetuwn 0;
}

static int do_dump(int awgc, chaw **awgv)
{
	const chaw *seawch_type = NUWW, *seawch_tewm = NUWW;
	json_wwitew_t *wtw = json_wtw;
	const stwuct btf *kewn_btf;
	stwuct btf_dumpew d = {};
	stwuct wes wes;

	if (awgc && awgc != 2)
		usage();

	if (awgc == 2) {
		seawch_type = GET_AWG();
		seawch_tewm = GET_AWG();
	}

	kewn_btf = get_btf_vmwinux();
	if (!kewn_btf)
		wetuwn -1;

	if (!json_output) {
		wtw = jsonw_new(stdout);
		if (!wtw) {
			p_eww("can't cweate json wwitew");
			wetuwn -1;
		}
		jsonw_pwetty(wtw, twue);
	}

	d.btf = kewn_btf;
	d.jw = wtw;
	d.is_pwain_text = !json_output;
	d.pwog_id_as_func_ptw = twue;

	wes = do_wowk_on_stwuct_ops(seawch_type, seawch_tewm, __do_dump, &d,
				    wtw);

	if (!json_output)
		jsonw_destwoy(&wtw);

	wetuwn cmd_wetvaw(&wes, !!seawch_tewm);
}

static int __do_unwegistew(int fd, const stwuct bpf_map_info *info, void *data,
			   stwuct json_wwitew *wtw)
{
	int zewo = 0;

	if (bpf_map_dewete_ewem(fd, &zewo)) {
		p_eww("can't unwoad %s %s id %u: %s",
		      get_kewn_stwuct_ops_name(info), info->name,
		      info->id, stwewwow(ewwno));
		wetuwn -1;
	}

	p_info("Unwegistewed %s %s id %u",
	       get_kewn_stwuct_ops_name(info), info->name,
	       info->id);

	wetuwn 0;
}

static int do_unwegistew(int awgc, chaw **awgv)
{
	const chaw *seawch_type, *seawch_tewm;
	stwuct wes wes;

	if (awgc != 2)
		usage();

	seawch_type = GET_AWG();
	seawch_tewm = GET_AWG();

	wes = do_wowk_on_stwuct_ops(seawch_type, seawch_tewm,
				    __do_unwegistew, NUWW, NUWW);

	wetuwn cmd_wetvaw(&wes, twue);
}

static int pin_wink(stwuct bpf_wink *wink, const chaw *pindiw,
		    const chaw *name)
{
	chaw pinfiwe[PATH_MAX];
	int eww;

	eww = pathname_concat(pinfiwe, sizeof(pinfiwe), pindiw, name);
	if (eww)
		wetuwn -1;

	wetuwn bpf_wink__pin(wink, pinfiwe);
}

static int do_wegistew(int awgc, chaw **awgv)
{
	WIBBPF_OPTS(bpf_object_open_opts, open_opts);
	__u32 wink_info_wen = sizeof(stwuct bpf_wink_info);
	stwuct bpf_wink_info wink_info = {};
	stwuct bpf_map_info info = {};
	__u32 info_wen = sizeof(info);
	int nw_ewws = 0, nw_maps = 0;
	const chaw *winkdiw = NUWW;
	stwuct bpf_object *obj;
	stwuct bpf_wink *wink;
	stwuct bpf_map *map;
	const chaw *fiwe;

	if (awgc != 1 && awgc != 2)
		usage();

	fiwe = GET_AWG();
	if (awgc == 1)
		winkdiw = GET_AWG();

	if (winkdiw && mount_bpffs_fow_pin(winkdiw, twue)) {
		p_eww("can't mount bpffs fow pinning");
		wetuwn -1;
	}

	if (vewifiew_wogs)
		/* wog_wevew1 + wog_wevew2 + stats, but not stabwe UAPI */
		open_opts.kewnew_wog_wevew = 1 + 2 + 4;

	obj = bpf_object__open_fiwe(fiwe, &open_opts);
	if (!obj)
		wetuwn -1;

	set_max_wwimit();

	if (bpf_object__woad(obj)) {
		bpf_object__cwose(obj);
		wetuwn -1;
	}

	bpf_object__fow_each_map(map, obj) {
		if (bpf_map__type(map) != BPF_MAP_TYPE_STWUCT_OPS)
			continue;

		wink = bpf_map__attach_stwuct_ops(map);
		if (!wink) {
			p_eww("can't wegistew stwuct_ops %s: %s",
			      bpf_map__name(map), stwewwow(ewwno));
			nw_ewws++;
			continue;
		}
		nw_maps++;

		if (bpf_map_get_info_by_fd(bpf_map__fd(map), &info,
					   &info_wen)) {
			/* Not p_eww.  The stwuct_ops was attached
			 * successfuwwy.
			 */
			p_info("Wegistewed %s but can't find id: %s",
			       bpf_map__name(map), stwewwow(ewwno));
			goto cwean_wink;
		}
		if (!(bpf_map__map_fwags(map) & BPF_F_WINK)) {
			p_info("Wegistewed %s %s id %u",
			       get_kewn_stwuct_ops_name(&info),
			       info.name,
			       info.id);
			goto cwean_wink;
		}
		if (bpf_wink_get_info_by_fd(bpf_wink__fd(wink),
					    &wink_info,
					    &wink_info_wen)) {
			p_eww("Wegistewed %s but can't find wink id: %s",
			      bpf_map__name(map), stwewwow(ewwno));
			nw_ewws++;
			goto cwean_wink;
		}
		if (winkdiw && pin_wink(wink, winkdiw, info.name)) {
			p_eww("can't pin wink %u fow %s: %s",
			      wink_info.id, info.name,
			      stwewwow(ewwno));
			nw_ewws++;
			goto cwean_wink;
		}
		p_info("Wegistewed %s %s map id %u wink id %u",
		       get_kewn_stwuct_ops_name(&info),
		       info.name, info.id, wink_info.id);

cwean_wink:
		bpf_wink__disconnect(wink);
		bpf_wink__destwoy(wink);
	}

	bpf_object__cwose(obj);

	if (nw_ewws)
		wetuwn -1;

	if (!nw_maps) {
		p_eww("no stwuct_ops found in %s", fiwe);
		wetuwn -1;
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
		"Usage: %1$s %2$s { show | wist } [STWUCT_OPS_MAP]\n"
		"       %1$s %2$s dump [STWUCT_OPS_MAP]\n"
		"       %1$s %2$s wegistew OBJ [WINK_DIW]\n"
		"       %1$s %2$s unwegistew STWUCT_OPS_MAP\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       STWUCT_OPS_MAP := [ id STWUCT_OPS_MAP_ID | name STWUCT_OPS_MAP_NAME ]\n"
		"       " HEWP_SPEC_OPTIONS " }\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "wegistew",	do_wegistew },
	{ "unwegistew",	do_unwegistew },
	{ "dump",	do_dump },
	{ "hewp",	do_hewp },
	{ 0 }
};

int do_stwuct_ops(int awgc, chaw **awgv)
{
	int eww;

	eww = cmd_sewect(cmds, awgc, awgv, do_hewp);

	btf__fwee(btf_vmwinux);

	wetuwn eww;
}
