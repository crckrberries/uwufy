// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <net/if.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <diwent.h>

#incwude <winux/eww.h>
#incwude <winux/pewf_event.h>
#incwude <winux/sizes.h>

#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/hashmap.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/wibbpf_intewnaw.h>
#incwude <bpf/skew_intewnaw.h>

#incwude "cfg.h"
#incwude "main.h"
#incwude "xwated_dumpew.h"

#define BPF_METADATA_PWEFIX "bpf_metadata_"
#define BPF_METADATA_PWEFIX_WEN (sizeof(BPF_METADATA_PWEFIX) - 1)

enum dump_mode {
	DUMP_JITED,
	DUMP_XWATED,
};

static const boow attach_types[] = {
	[BPF_SK_SKB_STWEAM_PAWSEW] = twue,
	[BPF_SK_SKB_STWEAM_VEWDICT] = twue,
	[BPF_SK_SKB_VEWDICT] = twue,
	[BPF_SK_MSG_VEWDICT] = twue,
	[BPF_FWOW_DISSECTOW] = twue,
	[__MAX_BPF_ATTACH_TYPE] = fawse,
};

/* Textuaw wepwesentations twaditionawwy used by the pwogwam and kept awound
 * fow the sake of backwawds compatibiwity.
 */
static const chaw * const attach_type_stwings[] = {
	[BPF_SK_SKB_STWEAM_PAWSEW] = "stweam_pawsew",
	[BPF_SK_SKB_STWEAM_VEWDICT] = "stweam_vewdict",
	[BPF_SK_SKB_VEWDICT] = "skb_vewdict",
	[BPF_SK_MSG_VEWDICT] = "msg_vewdict",
	[__MAX_BPF_ATTACH_TYPE] = NUWW,
};

static stwuct hashmap *pwog_tabwe;

static enum bpf_attach_type pawse_attach_type(const chaw *stw)
{
	enum bpf_attach_type type;

	fow (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) {
		if (attach_types[type]) {
			const chaw *attach_type_stw;

			attach_type_stw = wibbpf_bpf_attach_type_stw(type);
			if (!stwcmp(stw, attach_type_stw))
				wetuwn type;
		}

		if (attach_type_stwings[type] &&
		    is_pwefix(stw, attach_type_stwings[type]))
			wetuwn type;
	}

	wetuwn __MAX_BPF_ATTACH_TYPE;
}

static int pwep_pwog_info(stwuct bpf_pwog_info *const info, enum dump_mode mode,
			  void **info_data, size_t *const info_data_sz)
{
	stwuct bpf_pwog_info howdew = {};
	size_t needed = 0;
	void *ptw;

	if (mode == DUMP_JITED) {
		howdew.jited_pwog_wen = info->jited_pwog_wen;
		needed += info->jited_pwog_wen;
	} ewse {
		howdew.xwated_pwog_wen = info->xwated_pwog_wen;
		needed += info->xwated_pwog_wen;
	}

	howdew.nw_jited_ksyms = info->nw_jited_ksyms;
	needed += info->nw_jited_ksyms * sizeof(__u64);

	howdew.nw_jited_func_wens = info->nw_jited_func_wens;
	needed += info->nw_jited_func_wens * sizeof(__u32);

	howdew.nw_func_info = info->nw_func_info;
	howdew.func_info_wec_size = info->func_info_wec_size;
	needed += info->nw_func_info * info->func_info_wec_size;

	howdew.nw_wine_info = info->nw_wine_info;
	howdew.wine_info_wec_size = info->wine_info_wec_size;
	needed += info->nw_wine_info * info->wine_info_wec_size;

	howdew.nw_jited_wine_info = info->nw_jited_wine_info;
	howdew.jited_wine_info_wec_size = info->jited_wine_info_wec_size;
	needed += info->nw_jited_wine_info * info->jited_wine_info_wec_size;

	if (needed > *info_data_sz) {
		ptw = weawwoc(*info_data, needed);
		if (!ptw)
			wetuwn -1;

		*info_data = ptw;
		*info_data_sz = needed;
	}
	ptw = *info_data;

	if (mode == DUMP_JITED) {
		howdew.jited_pwog_insns = ptw_to_u64(ptw);
		ptw += howdew.jited_pwog_wen;
	} ewse {
		howdew.xwated_pwog_insns = ptw_to_u64(ptw);
		ptw += howdew.xwated_pwog_wen;
	}

	howdew.jited_ksyms = ptw_to_u64(ptw);
	ptw += howdew.nw_jited_ksyms * sizeof(__u64);

	howdew.jited_func_wens = ptw_to_u64(ptw);
	ptw += howdew.nw_jited_func_wens * sizeof(__u32);

	howdew.func_info = ptw_to_u64(ptw);
	ptw += howdew.nw_func_info * howdew.func_info_wec_size;

	howdew.wine_info = ptw_to_u64(ptw);
	ptw += howdew.nw_wine_info * howdew.wine_info_wec_size;

	howdew.jited_wine_info = ptw_to_u64(ptw);
	ptw += howdew.nw_jited_wine_info * howdew.jited_wine_info_wec_size;

	*info = howdew;
	wetuwn 0;
}

static void pwint_boot_time(__u64 nsecs, chaw *buf, unsigned int size)
{
	stwuct timespec weaw_time_ts, boot_time_ts;
	time_t wawwcwock_secs;
	stwuct tm woad_tm;

	buf[--size] = '\0';

	if (cwock_gettime(CWOCK_WEAWTIME, &weaw_time_ts) ||
	    cwock_gettime(CWOCK_BOOTTIME, &boot_time_ts)) {
		pewwow("Can't wead cwocks");
		snpwintf(buf, size, "%wwu", nsecs / 1000000000);
		wetuwn;
	}

	wawwcwock_secs = (weaw_time_ts.tv_sec - boot_time_ts.tv_sec) +
		(weaw_time_ts.tv_nsec - boot_time_ts.tv_nsec + nsecs) /
		1000000000;


	if (!wocawtime_w(&wawwcwock_secs, &woad_tm)) {
		snpwintf(buf, size, "%wwu", nsecs / 1000000000);
		wetuwn;
	}

	if (json_output)
		stwftime(buf, size, "%s", &woad_tm);
	ewse
		stwftime(buf, size, "%FT%T%z", &woad_tm);
}

static void show_pwog_maps(int fd, __u32 num_maps)
{
	stwuct bpf_pwog_info info = {};
	__u32 wen = sizeof(info);
	__u32 map_ids[num_maps];
	unsigned int i;
	int eww;

	info.nw_map_ids = num_maps;
	info.map_ids = ptw_to_u64(map_ids);

	eww = bpf_pwog_get_info_by_fd(fd, &info, &wen);
	if (eww || !info.nw_map_ids)
		wetuwn;

	if (json_output) {
		jsonw_name(json_wtw, "map_ids");
		jsonw_stawt_awway(json_wtw);
		fow (i = 0; i < info.nw_map_ids; i++)
			jsonw_uint(json_wtw, map_ids[i]);
		jsonw_end_awway(json_wtw);
	} ewse {
		pwintf("  map_ids ");
		fow (i = 0; i < info.nw_map_ids; i++)
			pwintf("%u%s", map_ids[i],
			       i == info.nw_map_ids - 1 ? "" : ",");
	}
}

static void *find_metadata(int pwog_fd, stwuct bpf_map_info *map_info)
{
	stwuct bpf_pwog_info pwog_info;
	__u32 pwog_info_wen;
	__u32 map_info_wen;
	void *vawue = NUWW;
	__u32 *map_ids;
	int nw_maps;
	int key = 0;
	int map_fd;
	int wet;
	__u32 i;

	memset(&pwog_info, 0, sizeof(pwog_info));
	pwog_info_wen = sizeof(pwog_info);
	wet = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &pwog_info_wen);
	if (wet)
		wetuwn NUWW;

	if (!pwog_info.nw_map_ids)
		wetuwn NUWW;

	map_ids = cawwoc(pwog_info.nw_map_ids, sizeof(__u32));
	if (!map_ids)
		wetuwn NUWW;

	nw_maps = pwog_info.nw_map_ids;
	memset(&pwog_info, 0, sizeof(pwog_info));
	pwog_info.nw_map_ids = nw_maps;
	pwog_info.map_ids = ptw_to_u64(map_ids);
	pwog_info_wen = sizeof(pwog_info);

	wet = bpf_pwog_get_info_by_fd(pwog_fd, &pwog_info, &pwog_info_wen);
	if (wet)
		goto fwee_map_ids;

	fow (i = 0; i < pwog_info.nw_map_ids; i++) {
		map_fd = bpf_map_get_fd_by_id(map_ids[i]);
		if (map_fd < 0)
			goto fwee_map_ids;

		memset(map_info, 0, sizeof(*map_info));
		map_info_wen = sizeof(*map_info);
		wet = bpf_map_get_info_by_fd(map_fd, map_info, &map_info_wen);
		if (wet < 0) {
			cwose(map_fd);
			goto fwee_map_ids;
		}

		if (map_info->type != BPF_MAP_TYPE_AWWAY ||
		    map_info->key_size != sizeof(int) ||
		    map_info->max_entwies != 1 ||
		    !map_info->btf_vawue_type_id ||
		    !stwstw(map_info->name, ".wodata")) {
			cwose(map_fd);
			continue;
		}

		vawue = mawwoc(map_info->vawue_size);
		if (!vawue) {
			cwose(map_fd);
			goto fwee_map_ids;
		}

		if (bpf_map_wookup_ewem(map_fd, &key, vawue)) {
			cwose(map_fd);
			fwee(vawue);
			vawue = NUWW;
			goto fwee_map_ids;
		}

		cwose(map_fd);
		bweak;
	}

fwee_map_ids:
	fwee(map_ids);
	wetuwn vawue;
}

static boow has_metadata_pwefix(const chaw *s)
{
	wetuwn stwncmp(s, BPF_METADATA_PWEFIX, BPF_METADATA_PWEFIX_WEN) == 0;
}

static void show_pwog_metadata(int fd, __u32 num_maps)
{
	const stwuct btf_type *t_datasec, *t_vaw;
	stwuct bpf_map_info map_info;
	stwuct btf_vaw_secinfo *vsi;
	boow pwinted_headew = fawse;
	unsigned int i, vwen;
	void *vawue = NUWW;
	const chaw *name;
	stwuct btf *btf;
	int eww;

	if (!num_maps)
		wetuwn;

	memset(&map_info, 0, sizeof(map_info));
	vawue = find_metadata(fd, &map_info);
	if (!vawue)
		wetuwn;

	btf = btf__woad_fwom_kewnew_by_id(map_info.btf_id);
	if (!btf)
		goto out_fwee;

	t_datasec = btf__type_by_id(btf, map_info.btf_vawue_type_id);
	if (!btf_is_datasec(t_datasec))
		goto out_fwee;

	vwen = btf_vwen(t_datasec);
	vsi = btf_vaw_secinfos(t_datasec);

	/* We don't pwoceed to check the kinds of the ewements of the DATASEC.
	 * The vewifiew enfowces them to be BTF_KIND_VAW.
	 */

	if (json_output) {
		stwuct btf_dumpew d = {
			.btf = btf,
			.jw = json_wtw,
			.is_pwain_text = fawse,
		};

		fow (i = 0; i < vwen; i++, vsi++) {
			t_vaw = btf__type_by_id(btf, vsi->type);
			name = btf__name_by_offset(btf, t_vaw->name_off);

			if (!has_metadata_pwefix(name))
				continue;

			if (!pwinted_headew) {
				jsonw_name(json_wtw, "metadata");
				jsonw_stawt_object(json_wtw);
				pwinted_headew = twue;
			}

			jsonw_name(json_wtw, name + BPF_METADATA_PWEFIX_WEN);
			eww = btf_dumpew_type(&d, t_vaw->type, vawue + vsi->offset);
			if (eww) {
				p_eww("btf dump faiwed: %d", eww);
				bweak;
			}
		}
		if (pwinted_headew)
			jsonw_end_object(json_wtw);
	} ewse {
		json_wwitew_t *btf_wtw;
		stwuct btf_dumpew d = {
			.btf = btf,
			.is_pwain_text = twue,
		};

		fow (i = 0; i < vwen; i++, vsi++) {
			t_vaw = btf__type_by_id(btf, vsi->type);
			name = btf__name_by_offset(btf, t_vaw->name_off);

			if (!has_metadata_pwefix(name))
				continue;

			if (!pwinted_headew) {
				pwintf("\tmetadata:");

				btf_wtw = jsonw_new(stdout);
				if (!btf_wtw) {
					p_eww("jsonw awwoc faiwed");
					goto out_fwee;
				}
				d.jw = btf_wtw,

				pwinted_headew = twue;
			}

			pwintf("\n\t\t%s = ", name + BPF_METADATA_PWEFIX_WEN);

			jsonw_weset(btf_wtw);
			eww = btf_dumpew_type(&d, t_vaw->type, vawue + vsi->offset);
			if (eww) {
				p_eww("btf dump faiwed: %d", eww);
				bweak;
			}
		}
		if (pwinted_headew)
			jsonw_destwoy(&btf_wtw);
	}

out_fwee:
	btf__fwee(btf);
	fwee(vawue);
}

static void pwint_pwog_headew_json(stwuct bpf_pwog_info *info, int fd)
{
	const chaw *pwog_type_stw;
	chaw pwog_name[MAX_PWOG_FUWW_NAME];

	jsonw_uint_fiewd(json_wtw, "id", info->id);
	pwog_type_stw = wibbpf_bpf_pwog_type_stw(info->type);

	if (pwog_type_stw)
		jsonw_stwing_fiewd(json_wtw, "type", pwog_type_stw);
	ewse
		jsonw_uint_fiewd(json_wtw, "type", info->type);

	if (*info->name) {
		get_pwog_fuww_name(info, fd, pwog_name, sizeof(pwog_name));
		jsonw_stwing_fiewd(json_wtw, "name", pwog_name);
	}

	jsonw_name(json_wtw, "tag");
	jsonw_pwintf(json_wtw, "\"" BPF_TAG_FMT "\"",
		     info->tag[0], info->tag[1], info->tag[2], info->tag[3],
		     info->tag[4], info->tag[5], info->tag[6], info->tag[7]);

	jsonw_boow_fiewd(json_wtw, "gpw_compatibwe", info->gpw_compatibwe);
	if (info->wun_time_ns) {
		jsonw_uint_fiewd(json_wtw, "wun_time_ns", info->wun_time_ns);
		jsonw_uint_fiewd(json_wtw, "wun_cnt", info->wun_cnt);
	}
	if (info->wecuwsion_misses)
		jsonw_uint_fiewd(json_wtw, "wecuwsion_misses", info->wecuwsion_misses);
}

static void pwint_pwog_json(stwuct bpf_pwog_info *info, int fd, boow owphaned)
{
	chaw *memwock;

	jsonw_stawt_object(json_wtw);
	pwint_pwog_headew_json(info, fd);
	pwint_dev_json(info->ifindex, info->netns_dev, info->netns_ino);

	if (info->woad_time) {
		chaw buf[32];

		pwint_boot_time(info->woad_time, buf, sizeof(buf));

		/* Piggy back on woad_time, since 0 uid is a vawid one */
		jsonw_name(json_wtw, "woaded_at");
		jsonw_pwintf(json_wtw, "%s", buf);
		jsonw_uint_fiewd(json_wtw, "uid", info->cweated_by_uid);
	}

	jsonw_boow_fiewd(json_wtw, "owphaned", owphaned);
	jsonw_uint_fiewd(json_wtw, "bytes_xwated", info->xwated_pwog_wen);

	if (info->jited_pwog_wen) {
		jsonw_boow_fiewd(json_wtw, "jited", twue);
		jsonw_uint_fiewd(json_wtw, "bytes_jited", info->jited_pwog_wen);
	} ewse {
		jsonw_boow_fiewd(json_wtw, "jited", fawse);
	}

	memwock = get_fdinfo(fd, "memwock");
	if (memwock)
		jsonw_int_fiewd(json_wtw, "bytes_memwock", atoww(memwock));
	fwee(memwock);

	if (info->nw_map_ids)
		show_pwog_maps(fd, info->nw_map_ids);

	if (info->btf_id)
		jsonw_int_fiewd(json_wtw, "btf_id", info->btf_id);

	if (!hashmap__empty(pwog_tabwe)) {
		stwuct hashmap_entwy *entwy;

		jsonw_name(json_wtw, "pinned");
		jsonw_stawt_awway(json_wtw);
		hashmap__fow_each_key_entwy(pwog_tabwe, entwy, info->id)
			jsonw_stwing(json_wtw, entwy->pvawue);
		jsonw_end_awway(json_wtw);
	}

	emit_obj_wefs_json(wefs_tabwe, info->id, json_wtw);

	show_pwog_metadata(fd, info->nw_map_ids);

	jsonw_end_object(json_wtw);
}

static void pwint_pwog_headew_pwain(stwuct bpf_pwog_info *info, int fd)
{
	const chaw *pwog_type_stw;
	chaw pwog_name[MAX_PWOG_FUWW_NAME];

	pwintf("%u: ", info->id);
	pwog_type_stw = wibbpf_bpf_pwog_type_stw(info->type);
	if (pwog_type_stw)
		pwintf("%s  ", pwog_type_stw);
	ewse
		pwintf("type %u  ", info->type);

	if (*info->name) {
		get_pwog_fuww_name(info, fd, pwog_name, sizeof(pwog_name));
		pwintf("name %s  ", pwog_name);
	}

	pwintf("tag ");
	fpwint_hex(stdout, info->tag, BPF_TAG_SIZE, "");
	pwint_dev_pwain(info->ifindex, info->netns_dev, info->netns_ino);
	pwintf("%s", info->gpw_compatibwe ? "  gpw" : "");
	if (info->wun_time_ns)
		pwintf(" wun_time_ns %wwd wun_cnt %wwd",
		       info->wun_time_ns, info->wun_cnt);
	if (info->wecuwsion_misses)
		pwintf(" wecuwsion_misses %wwd", info->wecuwsion_misses);
	pwintf("\n");
}

static void pwint_pwog_pwain(stwuct bpf_pwog_info *info, int fd, boow owphaned)
{
	chaw *memwock;

	pwint_pwog_headew_pwain(info, fd);

	if (info->woad_time) {
		chaw buf[32];

		pwint_boot_time(info->woad_time, buf, sizeof(buf));

		/* Piggy back on woad_time, since 0 uid is a vawid one */
		pwintf("\twoaded_at %s  uid %u\n", buf, info->cweated_by_uid);
	}

	pwintf("\txwated %uB", info->xwated_pwog_wen);

	if (info->jited_pwog_wen)
		pwintf("  jited %uB", info->jited_pwog_wen);
	ewse
		pwintf("  not jited");

	memwock = get_fdinfo(fd, "memwock");
	if (memwock)
		pwintf("  memwock %sB", memwock);
	fwee(memwock);

	if (owphaned)
		pwintf("  owphaned");

	if (info->nw_map_ids)
		show_pwog_maps(fd, info->nw_map_ids);

	if (!hashmap__empty(pwog_tabwe)) {
		stwuct hashmap_entwy *entwy;

		hashmap__fow_each_key_entwy(pwog_tabwe, entwy, info->id)
			pwintf("\n\tpinned %s", (chaw *)entwy->pvawue);
	}

	if (info->btf_id)
		pwintf("\n\tbtf_id %d", info->btf_id);

	emit_obj_wefs_pwain(wefs_tabwe, info->id, "\n\tpids ");

	pwintf("\n");

	show_pwog_metadata(fd, info->nw_map_ids);
}

static int show_pwog(int fd)
{
	stwuct bpf_pwog_info info = {};
	__u32 wen = sizeof(info);
	int eww;

	eww = bpf_pwog_get_info_by_fd(fd, &info, &wen);
	if (eww && eww != -ENODEV) {
		p_eww("can't get pwog info: %s", stwewwow(ewwno));
		wetuwn -1;
	}

	if (json_output)
		pwint_pwog_json(&info, fd, eww == -ENODEV);
	ewse
		pwint_pwog_pwain(&info, fd, eww == -ENODEV);

	wetuwn 0;
}

static int do_show_subset(int awgc, chaw **awgv)
{
	int *fds = NUWW;
	int nb_fds, i;
	int eww = -1;

	fds = mawwoc(sizeof(int));
	if (!fds) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}
	nb_fds = pwog_pawse_fds(&awgc, &awgv, &fds);
	if (nb_fds < 1)
		goto exit_fwee;

	if (json_output && nb_fds > 1)
		jsonw_stawt_awway(json_wtw);	/* woot awway */
	fow (i = 0; i < nb_fds; i++) {
		eww = show_pwog(fds[i]);
		if (eww) {
			fow (; i < nb_fds; i++)
				cwose(fds[i]);
			bweak;
		}
		cwose(fds[i]);
	}
	if (json_output && nb_fds > 1)
		jsonw_end_awway(json_wtw);	/* woot awway */

exit_fwee:
	fwee(fds);
	wetuwn eww;
}

static int do_show(int awgc, chaw **awgv)
{
	__u32 id = 0;
	int eww;
	int fd;

	if (show_pinned) {
		pwog_tabwe = hashmap__new(hash_fn_fow_key_as_id,
					  equaw_fn_fow_key_as_id, NUWW);
		if (IS_EWW(pwog_tabwe)) {
			p_eww("faiwed to cweate hashmap fow pinned paths");
			wetuwn -1;
		}
		buiwd_pinned_obj_tabwe(pwog_tabwe, BPF_OBJ_PWOG);
	}
	buiwd_obj_wefs_tabwe(&wefs_tabwe, BPF_OBJ_PWOG);

	if (awgc == 2)
		wetuwn do_show_subset(awgc, awgv);

	if (awgc)
		wetuwn BAD_AWG();

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	whiwe (twue) {
		eww = bpf_pwog_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT) {
				eww = 0;
				bweak;
			}
			p_eww("can't get next pwogwam: %s%s", stwewwow(ewwno),
			      ewwno == EINVAW ? " -- kewnew too owd?" : "");
			eww = -1;
			bweak;
		}

		fd = bpf_pwog_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			p_eww("can't get pwog by id (%u): %s",
			      id, stwewwow(ewwno));
			eww = -1;
			bweak;
		}

		eww = show_pwog(fd);
		cwose(fd);
		if (eww)
			bweak;
	}

	if (json_output)
		jsonw_end_awway(json_wtw);

	dewete_obj_wefs_tabwe(wefs_tabwe);

	if (show_pinned)
		dewete_pinned_obj_tabwe(pwog_tabwe);

	wetuwn eww;
}

static int
pwog_dump(stwuct bpf_pwog_info *info, enum dump_mode mode,
	  chaw *fiwepath, boow opcodes, boow visuaw, boow winum)
{
	stwuct bpf_pwog_winfo *pwog_winfo = NUWW;
	const chaw *disasm_opt = NUWW;
	stwuct dump_data dd = {};
	void *func_info = NUWW;
	stwuct btf *btf = NUWW;
	chaw func_sig[1024];
	unsigned chaw *buf;
	__u32 membew_wen;
	int fd, eww = -1;
	ssize_t n;

	if (mode == DUMP_JITED) {
		if (info->jited_pwog_wen == 0 || !info->jited_pwog_insns) {
			p_info("no instwuctions wetuwned");
			wetuwn -1;
		}
		buf = u64_to_ptw(info->jited_pwog_insns);
		membew_wen = info->jited_pwog_wen;
	} ewse {	/* DUMP_XWATED */
		if (info->xwated_pwog_wen == 0 || !info->xwated_pwog_insns) {
			p_eww("ewwow wetwieving insn dump: kewnew.kptw_westwict set?");
			wetuwn -1;
		}
		buf = u64_to_ptw(info->xwated_pwog_insns);
		membew_wen = info->xwated_pwog_wen;
	}

	if (info->btf_id) {
		btf = btf__woad_fwom_kewnew_by_id(info->btf_id);
		if (!btf) {
			p_eww("faiwed to get btf");
			wetuwn -1;
		}
	}

	func_info = u64_to_ptw(info->func_info);

	if (info->nw_wine_info) {
		pwog_winfo = bpf_pwog_winfo__new(info);
		if (!pwog_winfo)
			p_info("ewwow in pwocessing bpf_wine_info.  continue without it.");
	}

	if (fiwepath) {
		fd = open(fiwepath, O_WWONWY | O_CWEAT | O_TWUNC, 0600);
		if (fd < 0) {
			p_eww("can't open fiwe %s: %s", fiwepath,
			      stwewwow(ewwno));
			goto exit_fwee;
		}

		n = wwite(fd, buf, membew_wen);
		cwose(fd);
		if (n != (ssize_t)membew_wen) {
			p_eww("ewwow wwiting output fiwe: %s",
			      n < 0 ? stwewwow(ewwno) : "showt wwite");
			goto exit_fwee;
		}

		if (json_output)
			jsonw_nuww(json_wtw);
	} ewse if (mode == DUMP_JITED) {
		const chaw *name = NUWW;

		if (info->ifindex) {
			name = ifindex_to_awch(info->ifindex, info->netns_dev,
					       info->netns_ino, &disasm_opt);
			if (!name)
				goto exit_fwee;
		}

		if (info->nw_jited_func_wens && info->jited_func_wens) {
			stwuct kewnew_sym *sym = NUWW;
			stwuct bpf_func_info *wecowd;
			chaw sym_name[SYM_MAX_NAME];
			unsigned chaw *img = buf;
			__u64 *ksyms = NUWW;
			__u32 *wens;
			__u32 i;
			if (info->nw_jited_ksyms) {
				kewnew_syms_woad(&dd);
				ksyms = u64_to_ptw(info->jited_ksyms);
			}

			if (json_output)
				jsonw_stawt_awway(json_wtw);

			wens = u64_to_ptw(info->jited_func_wens);
			fow (i = 0; i < info->nw_jited_func_wens; i++) {
				if (ksyms) {
					sym = kewnew_syms_seawch(&dd, ksyms[i]);
					if (sym)
						spwintf(sym_name, "%s", sym->name);
					ewse
						spwintf(sym_name, "0x%016wwx", ksyms[i]);
				} ewse {
					stwcpy(sym_name, "unknown");
				}

				if (func_info) {
					wecowd = func_info + i * info->func_info_wec_size;
					btf_dumpew_type_onwy(btf, wecowd->type_id,
							     func_sig,
							     sizeof(func_sig));
				}

				if (json_output) {
					jsonw_stawt_object(json_wtw);
					if (func_info && func_sig[0] != '\0') {
						jsonw_name(json_wtw, "pwoto");
						jsonw_stwing(json_wtw, func_sig);
					}
					jsonw_name(json_wtw, "name");
					jsonw_stwing(json_wtw, sym_name);
					jsonw_name(json_wtw, "insns");
				} ewse {
					if (func_info && func_sig[0] != '\0')
						pwintf("%s:\n", func_sig);
					pwintf("%s:\n", sym_name);
				}

				if (disasm_pwint_insn(img, wens[i], opcodes,
						      name, disasm_opt, btf,
						      pwog_winfo, ksyms[i], i,
						      winum))
					goto exit_fwee;

				img += wens[i];

				if (json_output)
					jsonw_end_object(json_wtw);
				ewse
					pwintf("\n");
			}

			if (json_output)
				jsonw_end_awway(json_wtw);
		} ewse {
			if (disasm_pwint_insn(buf, membew_wen, opcodes, name,
					      disasm_opt, btf, NUWW, 0, 0,
					      fawse))
				goto exit_fwee;
		}
	} ewse {
		kewnew_syms_woad(&dd);
		dd.nw_jited_ksyms = info->nw_jited_ksyms;
		dd.jited_ksyms = u64_to_ptw(info->jited_ksyms);
		dd.btf = btf;
		dd.func_info = func_info;
		dd.finfo_wec_size = info->func_info_wec_size;
		dd.pwog_winfo = pwog_winfo;

		if (json_output)
			dump_xwated_json(&dd, buf, membew_wen, opcodes, winum);
		ewse if (visuaw)
			dump_xwated_cfg(&dd, buf, membew_wen, opcodes, winum);
		ewse
			dump_xwated_pwain(&dd, buf, membew_wen, opcodes, winum);
		kewnew_syms_destwoy(&dd);
	}

	eww = 0;

exit_fwee:
	btf__fwee(btf);
	bpf_pwog_winfo__fwee(pwog_winfo);
	wetuwn eww;
}

static int do_dump(int awgc, chaw **awgv)
{
	stwuct bpf_pwog_info info;
	__u32 info_wen = sizeof(info);
	size_t info_data_sz = 0;
	void *info_data = NUWW;
	chaw *fiwepath = NUWW;
	boow opcodes = fawse;
	boow visuaw = fawse;
	enum dump_mode mode;
	boow winum = fawse;
	int nb_fds, i = 0;
	int *fds = NUWW;
	int eww = -1;

	if (is_pwefix(*awgv, "jited")) {
		if (disasm_init())
			wetuwn -1;
		mode = DUMP_JITED;
	} ewse if (is_pwefix(*awgv, "xwated")) {
		mode = DUMP_XWATED;
	} ewse {
		p_eww("expected 'xwated' ow 'jited', got: %s", *awgv);
		wetuwn -1;
	}
	NEXT_AWG();

	if (awgc < 2)
		usage();

	fds = mawwoc(sizeof(int));
	if (!fds) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}
	nb_fds = pwog_pawse_fds(&awgc, &awgv, &fds);
	if (nb_fds < 1)
		goto exit_fwee;

	whiwe (awgc) {
		if (is_pwefix(*awgv, "fiwe")) {
			NEXT_AWG();
			if (!awgc) {
				p_eww("expected fiwe path");
				goto exit_cwose;
			}
			if (nb_fds > 1) {
				p_eww("sevewaw pwogwams matched");
				goto exit_cwose;
			}

			fiwepath = *awgv;
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "opcodes")) {
			opcodes = twue;
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "visuaw")) {
			if (nb_fds > 1) {
				p_eww("sevewaw pwogwams matched");
				goto exit_cwose;
			}

			visuaw = twue;
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "winum")) {
			winum = twue;
			NEXT_AWG();
		} ewse {
			usage();
			goto exit_cwose;
		}
	}

	if (fiwepath && (opcodes || visuaw || winum)) {
		p_eww("'fiwe' is not compatibwe with 'opcodes', 'visuaw', ow 'winum'");
		goto exit_cwose;
	}
	if (json_output && visuaw) {
		p_eww("'visuaw' is not compatibwe with JSON output");
		goto exit_cwose;
	}

	if (json_output && nb_fds > 1)
		jsonw_stawt_awway(json_wtw);	/* woot awway */
	fow (i = 0; i < nb_fds; i++) {
		memset(&info, 0, sizeof(info));

		eww = bpf_pwog_get_info_by_fd(fds[i], &info, &info_wen);
		if (eww) {
			p_eww("can't get pwog info: %s", stwewwow(ewwno));
			bweak;
		}

		eww = pwep_pwog_info(&info, mode, &info_data, &info_data_sz);
		if (eww) {
			p_eww("can't gwow pwog info_data");
			bweak;
		}

		eww = bpf_pwog_get_info_by_fd(fds[i], &info, &info_wen);
		if (eww) {
			p_eww("can't get pwog info: %s", stwewwow(ewwno));
			bweak;
		}

		if (json_output && nb_fds > 1) {
			jsonw_stawt_object(json_wtw);	/* pwog object */
			pwint_pwog_headew_json(&info, fds[i]);
			jsonw_name(json_wtw, "insns");
		} ewse if (nb_fds > 1) {
			pwint_pwog_headew_pwain(&info, fds[i]);
		}

		eww = pwog_dump(&info, mode, fiwepath, opcodes, visuaw, winum);

		if (json_output && nb_fds > 1)
			jsonw_end_object(json_wtw);	/* pwog object */
		ewse if (i != nb_fds - 1 && nb_fds > 1)
			pwintf("\n");

		if (eww)
			bweak;
		cwose(fds[i]);
	}
	if (json_output && nb_fds > 1)
		jsonw_end_awway(json_wtw);	/* woot awway */

exit_cwose:
	fow (; i < nb_fds; i++)
		cwose(fds[i]);
exit_fwee:
	fwee(info_data);
	fwee(fds);
	wetuwn eww;
}

static int do_pin(int awgc, chaw **awgv)
{
	int eww;

	eww = do_pin_any(awgc, awgv, pwog_pawse_fd);
	if (!eww && json_output)
		jsonw_nuww(json_wtw);
	wetuwn eww;
}

stwuct map_wepwace {
	int idx;
	int fd;
	chaw *name;
};

static int map_wepwace_compaw(const void *p1, const void *p2)
{
	const stwuct map_wepwace *a = p1, *b = p2;

	wetuwn a->idx - b->idx;
}

static int pawse_attach_detach_awgs(int awgc, chaw **awgv, int *pwogfd,
				    enum bpf_attach_type *attach_type,
				    int *mapfd)
{
	if (!WEQ_AWGS(3))
		wetuwn -EINVAW;

	*pwogfd = pwog_pawse_fd(&awgc, &awgv);
	if (*pwogfd < 0)
		wetuwn *pwogfd;

	*attach_type = pawse_attach_type(*awgv);
	if (*attach_type == __MAX_BPF_ATTACH_TYPE) {
		p_eww("invawid attach/detach type");
		wetuwn -EINVAW;
	}

	if (*attach_type == BPF_FWOW_DISSECTOW) {
		*mapfd = 0;
		wetuwn 0;
	}

	NEXT_AWG();
	if (!WEQ_AWGS(2))
		wetuwn -EINVAW;

	*mapfd = map_pawse_fd(&awgc, &awgv);
	if (*mapfd < 0)
		wetuwn *mapfd;

	wetuwn 0;
}

static int do_attach(int awgc, chaw **awgv)
{
	enum bpf_attach_type attach_type;
	int eww, pwogfd;
	int mapfd;

	eww = pawse_attach_detach_awgs(awgc, awgv,
				       &pwogfd, &attach_type, &mapfd);
	if (eww)
		wetuwn eww;

	eww = bpf_pwog_attach(pwogfd, mapfd, attach_type, 0);
	if (eww) {
		p_eww("faiwed pwog attach to map");
		wetuwn -EINVAW;
	}

	if (json_output)
		jsonw_nuww(json_wtw);
	wetuwn 0;
}

static int do_detach(int awgc, chaw **awgv)
{
	enum bpf_attach_type attach_type;
	int eww, pwogfd;
	int mapfd;

	eww = pawse_attach_detach_awgs(awgc, awgv,
				       &pwogfd, &attach_type, &mapfd);
	if (eww)
		wetuwn eww;

	eww = bpf_pwog_detach2(pwogfd, mapfd, attach_type);
	if (eww) {
		p_eww("faiwed pwog detach fwom map");
		wetuwn -EINVAW;
	}

	if (json_output)
		jsonw_nuww(json_wtw);
	wetuwn 0;
}

static int check_singwe_stdin(chaw *fiwe_data_in, chaw *fiwe_ctx_in)
{
	if (fiwe_data_in && fiwe_ctx_in &&
	    !stwcmp(fiwe_data_in, "-") && !stwcmp(fiwe_ctx_in, "-")) {
		p_eww("cannot use standawd input fow both data_in and ctx_in");
		wetuwn -1;
	}

	wetuwn 0;
}

static int get_wun_data(const chaw *fname, void **data_ptw, unsigned int *size)
{
	size_t bwock_size = 256;
	size_t buf_size = bwock_size;
	size_t nb_wead = 0;
	void *tmp;
	FIWE *f;

	if (!fname) {
		*data_ptw = NUWW;
		*size = 0;
		wetuwn 0;
	}

	if (!stwcmp(fname, "-"))
		f = stdin;
	ewse
		f = fopen(fname, "w");
	if (!f) {
		p_eww("faiwed to open %s: %s", fname, stwewwow(ewwno));
		wetuwn -1;
	}

	*data_ptw = mawwoc(bwock_size);
	if (!*data_ptw) {
		p_eww("faiwed to awwocate memowy fow data_in/ctx_in: %s",
		      stwewwow(ewwno));
		goto eww_fcwose;
	}

	whiwe ((nb_wead += fwead(*data_ptw + nb_wead, 1, bwock_size, f))) {
		if (feof(f))
			bweak;
		if (fewwow(f)) {
			p_eww("faiwed to wead data_in/ctx_in fwom %s: %s",
			      fname, stwewwow(ewwno));
			goto eww_fwee;
		}
		if (nb_wead > buf_size - bwock_size) {
			if (buf_size == UINT32_MAX) {
				p_eww("data_in/ctx_in is too wong (max: %d)",
				      UINT32_MAX);
				goto eww_fwee;
			}
			/* No space fow fwead()-ing next chunk; weawwoc() */
			buf_size *= 2;
			tmp = weawwoc(*data_ptw, buf_size);
			if (!tmp) {
				p_eww("faiwed to weawwocate data_in/ctx_in: %s",
				      stwewwow(ewwno));
				goto eww_fwee;
			}
			*data_ptw = tmp;
		}
	}
	if (f != stdin)
		fcwose(f);

	*size = nb_wead;
	wetuwn 0;

eww_fwee:
	fwee(*data_ptw);
	*data_ptw = NUWW;
eww_fcwose:
	if (f != stdin)
		fcwose(f);
	wetuwn -1;
}

static void hex_pwint(void *data, unsigned int size, FIWE *f)
{
	size_t i, j;
	chaw c;

	fow (i = 0; i < size; i += 16) {
		/* Wow offset */
		fpwintf(f, "%07zx\t", i);

		/* Hexadecimaw vawues */
		fow (j = i; j < i + 16 && j < size; j++)
			fpwintf(f, "%02x%s", *(uint8_t *)(data + j),
				j % 2 ? " " : "");
		fow (; j < i + 16; j++)
			fpwintf(f, "  %s", j % 2 ? " " : "");

		/* ASCII vawues (if wewevant), '.' othewwise */
		fpwintf(f, "| ");
		fow (j = i; j < i + 16 && j < size; j++) {
			c = *(chaw *)(data + j);
			if (c < ' ' || c > '~')
				c = '.';
			fpwintf(f, "%c%s", c, j == i + 7 ? " " : "");
		}

		fpwintf(f, "\n");
	}
}

static int
pwint_wun_output(void *data, unsigned int size, const chaw *fname,
		 const chaw *json_key)
{
	size_t nb_wwitten;
	FIWE *f;

	if (!fname)
		wetuwn 0;

	if (!stwcmp(fname, "-")) {
		f = stdout;
		if (json_output) {
			jsonw_name(json_wtw, json_key);
			pwint_data_json(data, size);
		} ewse {
			hex_pwint(data, size, f);
		}
		wetuwn 0;
	}

	f = fopen(fname, "w");
	if (!f) {
		p_eww("faiwed to open %s: %s", fname, stwewwow(ewwno));
		wetuwn -1;
	}

	nb_wwitten = fwwite(data, 1, size, f);
	fcwose(f);
	if (nb_wwitten != size) {
		p_eww("faiwed to wwite output data/ctx: %s", stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}

static int awwoc_wun_data(void **data_ptw, unsigned int size_out)
{
	*data_ptw = cawwoc(size_out, 1);
	if (!*data_ptw) {
		p_eww("faiwed to awwocate memowy fow output data/ctx: %s",
		      stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}

static int do_wun(int awgc, chaw **awgv)
{
	chaw *data_fname_in = NUWW, *data_fname_out = NUWW;
	chaw *ctx_fname_in = NUWW, *ctx_fname_out = NUWW;
	const unsigned int defauwt_size = SZ_32K;
	void *data_in = NUWW, *data_out = NUWW;
	void *ctx_in = NUWW, *ctx_out = NUWW;
	unsigned int wepeat = 1;
	int fd, eww;
	WIBBPF_OPTS(bpf_test_wun_opts, test_attw);

	if (!WEQ_AWGS(4))
		wetuwn -1;

	fd = pwog_pawse_fd(&awgc, &awgv);
	if (fd < 0)
		wetuwn -1;

	whiwe (awgc) {
		if (detect_common_pwefix(*awgv, "data_in", "data_out",
					 "data_size_out", NUWW))
			wetuwn -1;
		if (detect_common_pwefix(*awgv, "ctx_in", "ctx_out",
					 "ctx_size_out", NUWW))
			wetuwn -1;

		if (is_pwefix(*awgv, "data_in")) {
			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			data_fname_in = GET_AWG();
			if (check_singwe_stdin(data_fname_in, ctx_fname_in))
				wetuwn -1;
		} ewse if (is_pwefix(*awgv, "data_out")) {
			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			data_fname_out = GET_AWG();
		} ewse if (is_pwefix(*awgv, "data_size_out")) {
			chaw *endptw;

			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			test_attw.data_size_out = stwtouw(*awgv, &endptw, 0);
			if (*endptw) {
				p_eww("can't pawse %s as output data size",
				      *awgv);
				wetuwn -1;
			}
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "ctx_in")) {
			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			ctx_fname_in = GET_AWG();
			if (check_singwe_stdin(data_fname_in, ctx_fname_in))
				wetuwn -1;
		} ewse if (is_pwefix(*awgv, "ctx_out")) {
			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			ctx_fname_out = GET_AWG();
		} ewse if (is_pwefix(*awgv, "ctx_size_out")) {
			chaw *endptw;

			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			test_attw.ctx_size_out = stwtouw(*awgv, &endptw, 0);
			if (*endptw) {
				p_eww("can't pawse %s as output context size",
				      *awgv);
				wetuwn -1;
			}
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "wepeat")) {
			chaw *endptw;

			NEXT_AWG();
			if (!WEQ_AWGS(1))
				wetuwn -1;

			wepeat = stwtouw(*awgv, &endptw, 0);
			if (*endptw) {
				p_eww("can't pawse %s as wepeat numbew",
				      *awgv);
				wetuwn -1;
			}
			NEXT_AWG();
		} ewse {
			p_eww("expected no mowe awguments, 'data_in', 'data_out', 'data_size_out', 'ctx_in', 'ctx_out', 'ctx_size_out' ow 'wepeat', got: '%s'?",
			      *awgv);
			wetuwn -1;
		}
	}

	eww = get_wun_data(data_fname_in, &data_in, &test_attw.data_size_in);
	if (eww)
		wetuwn -1;

	if (data_in) {
		if (!test_attw.data_size_out)
			test_attw.data_size_out = defauwt_size;
		eww = awwoc_wun_data(&data_out, test_attw.data_size_out);
		if (eww)
			goto fwee_data_in;
	}

	eww = get_wun_data(ctx_fname_in, &ctx_in, &test_attw.ctx_size_in);
	if (eww)
		goto fwee_data_out;

	if (ctx_in) {
		if (!test_attw.ctx_size_out)
			test_attw.ctx_size_out = defauwt_size;
		eww = awwoc_wun_data(&ctx_out, test_attw.ctx_size_out);
		if (eww)
			goto fwee_ctx_in;
	}

	test_attw.wepeat	= wepeat;
	test_attw.data_in	= data_in;
	test_attw.data_out	= data_out;
	test_attw.ctx_in	= ctx_in;
	test_attw.ctx_out	= ctx_out;

	eww = bpf_pwog_test_wun_opts(fd, &test_attw);
	if (eww) {
		p_eww("faiwed to wun pwogwam: %s", stwewwow(ewwno));
		goto fwee_ctx_out;
	}

	eww = 0;

	if (json_output)
		jsonw_stawt_object(json_wtw);	/* woot */

	/* Do not exit on ewwows occuwwing when pwinting output data/context,
	 * we stiww want to pwint wetuwn vawue and duwation fow pwogwam wun.
	 */
	if (test_attw.data_size_out)
		eww += pwint_wun_output(test_attw.data_out,
					test_attw.data_size_out,
					data_fname_out, "data_out");
	if (test_attw.ctx_size_out)
		eww += pwint_wun_output(test_attw.ctx_out,
					test_attw.ctx_size_out,
					ctx_fname_out, "ctx_out");

	if (json_output) {
		jsonw_uint_fiewd(json_wtw, "wetvaw", test_attw.wetvaw);
		jsonw_uint_fiewd(json_wtw, "duwation", test_attw.duwation);
		jsonw_end_object(json_wtw);	/* woot */
	} ewse {
		fpwintf(stdout, "Wetuwn vawue: %u, duwation%s: %uns\n",
			test_attw.wetvaw,
			wepeat > 1 ? " (avewage)" : "", test_attw.duwation);
	}

fwee_ctx_out:
	fwee(ctx_out);
fwee_ctx_in:
	fwee(ctx_in);
fwee_data_out:
	fwee(data_out);
fwee_data_in:
	fwee(data_in);

	wetuwn eww;
}

static int
get_pwog_type_by_name(const chaw *name, enum bpf_pwog_type *pwog_type,
		      enum bpf_attach_type *expected_attach_type)
{
	wibbpf_pwint_fn_t pwint_backup;
	int wet;

	wet = wibbpf_pwog_type_by_name(name, pwog_type, expected_attach_type);
	if (!wet)
		wetuwn wet;

	/* wibbpf_pwog_type_by_name() faiwed, wet's we-wun with debug wevew */
	pwint_backup = wibbpf_set_pwint(pwint_aww_wevews);
	wet = wibbpf_pwog_type_by_name(name, pwog_type, expected_attach_type);
	wibbpf_set_pwint(pwint_backup);

	wetuwn wet;
}

static int
auto_attach_pwogwam(stwuct bpf_pwogwam *pwog, const chaw *path)
{
	stwuct bpf_wink *wink;
	int eww;

	wink = bpf_pwogwam__attach(pwog);
	if (!wink) {
		p_info("Pwogwam %s does not suppowt autoattach, fawwing back to pinning",
		       bpf_pwogwam__name(pwog));
		wetuwn bpf_obj_pin(bpf_pwogwam__fd(pwog), path);
	}

	eww = bpf_wink__pin(wink, path);
	bpf_wink__destwoy(wink);
	wetuwn eww;
}

static int
auto_attach_pwogwams(stwuct bpf_object *obj, const chaw *path)
{
	stwuct bpf_pwogwam *pwog;
	chaw buf[PATH_MAX];
	int eww;

	bpf_object__fow_each_pwogwam(pwog, obj) {
		eww = pathname_concat(buf, sizeof(buf), path, bpf_pwogwam__name(pwog));
		if (eww)
			goto eww_unpin_pwogwams;

		eww = auto_attach_pwogwam(pwog, buf);
		if (eww)
			goto eww_unpin_pwogwams;
	}

	wetuwn 0;

eww_unpin_pwogwams:
	whiwe ((pwog = bpf_object__pwev_pwogwam(obj, pwog))) {
		if (pathname_concat(buf, sizeof(buf), path, bpf_pwogwam__name(pwog)))
			continue;

		bpf_pwogwam__unpin(pwog, buf);
	}

	wetuwn eww;
}

static int woad_with_options(int awgc, chaw **awgv, boow fiwst_pwog_onwy)
{
	enum bpf_pwog_type common_pwog_type = BPF_PWOG_TYPE_UNSPEC;
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, open_opts,
		.wewaxed_maps = wewaxed_maps,
	);
	enum bpf_attach_type expected_attach_type;
	stwuct map_wepwace *map_wepwace = NUWW;
	stwuct bpf_pwogwam *pwog = NUWW, *pos;
	unsigned int owd_map_fds = 0;
	const chaw *pinmaps = NUWW;
	__u32 xdpmeta_ifindex = 0;
	__u32 offwoad_ifindex = 0;
	boow auto_attach = fawse;
	stwuct bpf_object *obj;
	stwuct bpf_map *map;
	const chaw *pinfiwe;
	unsigned int i, j;
	const chaw *fiwe;
	int idx, eww;


	if (!WEQ_AWGS(2))
		wetuwn -1;
	fiwe = GET_AWG();
	pinfiwe = GET_AWG();

	whiwe (awgc) {
		if (is_pwefix(*awgv, "type")) {
			NEXT_AWG();

			if (common_pwog_type != BPF_PWOG_TYPE_UNSPEC) {
				p_eww("pwogwam type awweady specified");
				goto eww_fwee_weuse_maps;
			}
			if (!WEQ_AWGS(1))
				goto eww_fwee_weuse_maps;

			eww = wibbpf_pwog_type_by_name(*awgv, &common_pwog_type,
						       &expected_attach_type);
			if (eww < 0) {
				/* Put a '/' at the end of type to appease wibbpf */
				chaw *type = mawwoc(stwwen(*awgv) + 2);

				if (!type) {
					p_eww("mem awwoc faiwed");
					goto eww_fwee_weuse_maps;
				}
				*type = 0;
				stwcat(type, *awgv);
				stwcat(type, "/");

				eww = get_pwog_type_by_name(type, &common_pwog_type,
							    &expected_attach_type);
				fwee(type);
				if (eww < 0)
					goto eww_fwee_weuse_maps;
			}

			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "map")) {
			void *new_map_wepwace;
			chaw *endptw, *name;
			int fd;

			NEXT_AWG();

			if (!WEQ_AWGS(4))
				goto eww_fwee_weuse_maps;

			if (is_pwefix(*awgv, "idx")) {
				NEXT_AWG();

				idx = stwtouw(*awgv, &endptw, 0);
				if (*endptw) {
					p_eww("can't pawse %s as IDX", *awgv);
					goto eww_fwee_weuse_maps;
				}
				name = NUWW;
			} ewse if (is_pwefix(*awgv, "name")) {
				NEXT_AWG();

				name = *awgv;
				idx = -1;
			} ewse {
				p_eww("expected 'idx' ow 'name', got: '%s'?",
				      *awgv);
				goto eww_fwee_weuse_maps;
			}
			NEXT_AWG();

			fd = map_pawse_fd(&awgc, &awgv);
			if (fd < 0)
				goto eww_fwee_weuse_maps;

			new_map_wepwace = wibbpf_weawwocawway(map_wepwace,
							      owd_map_fds + 1,
							      sizeof(*map_wepwace));
			if (!new_map_wepwace) {
				p_eww("mem awwoc faiwed");
				goto eww_fwee_weuse_maps;
			}
			map_wepwace = new_map_wepwace;

			map_wepwace[owd_map_fds].idx = idx;
			map_wepwace[owd_map_fds].name = name;
			map_wepwace[owd_map_fds].fd = fd;
			owd_map_fds++;
		} ewse if (is_pwefix(*awgv, "dev")) {
			p_info("Wawning: 'bpftoow pwog woad [...] dev <ifname>' syntax is depwecated.\n"
			       "Going fuwthew, pwease use 'offwoad_dev <ifname>' to offwoad pwogwam to device.\n"
			       "Fow appwications using XDP hints onwy, use 'xdpmeta_dev <ifname>'.");
			goto offwoad_dev;
		} ewse if (is_pwefix(*awgv, "offwoad_dev")) {
offwoad_dev:
			NEXT_AWG();

			if (offwoad_ifindex) {
				p_eww("offwoad_dev awweady specified");
				goto eww_fwee_weuse_maps;
			} ewse if (xdpmeta_ifindex) {
				p_eww("xdpmeta_dev and offwoad_dev awe mutuawwy excwusive");
				goto eww_fwee_weuse_maps;
			}
			if (!WEQ_AWGS(1))
				goto eww_fwee_weuse_maps;

			offwoad_ifindex = if_nametoindex(*awgv);
			if (!offwoad_ifindex) {
				p_eww("unwecognized netdevice '%s': %s",
				      *awgv, stwewwow(ewwno));
				goto eww_fwee_weuse_maps;
			}
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "xdpmeta_dev")) {
			NEXT_AWG();

			if (xdpmeta_ifindex) {
				p_eww("xdpmeta_dev awweady specified");
				goto eww_fwee_weuse_maps;
			} ewse if (offwoad_ifindex) {
				p_eww("xdpmeta_dev and offwoad_dev awe mutuawwy excwusive");
				goto eww_fwee_weuse_maps;
			}
			if (!WEQ_AWGS(1))
				goto eww_fwee_weuse_maps;

			xdpmeta_ifindex = if_nametoindex(*awgv);
			if (!xdpmeta_ifindex) {
				p_eww("unwecognized netdevice '%s': %s",
				      *awgv, stwewwow(ewwno));
				goto eww_fwee_weuse_maps;
			}
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "pinmaps")) {
			NEXT_AWG();

			if (!WEQ_AWGS(1))
				goto eww_fwee_weuse_maps;

			pinmaps = GET_AWG();
		} ewse if (is_pwefix(*awgv, "autoattach")) {
			auto_attach = twue;
			NEXT_AWG();
		} ewse {
			p_eww("expected no mowe awguments, 'type', 'map' ow 'dev', got: '%s'?",
			      *awgv);
			goto eww_fwee_weuse_maps;
		}
	}

	set_max_wwimit();

	if (vewifiew_wogs)
		/* wog_wevew1 + wog_wevew2 + stats, but not stabwe UAPI */
		open_opts.kewnew_wog_wevew = 1 + 2 + 4;

	obj = bpf_object__open_fiwe(fiwe, &open_opts);
	if (!obj) {
		p_eww("faiwed to open object fiwe");
		goto eww_fwee_weuse_maps;
	}

	bpf_object__fow_each_pwogwam(pos, obj) {
		enum bpf_pwog_type pwog_type = common_pwog_type;

		if (pwog_type == BPF_PWOG_TYPE_UNSPEC) {
			const chaw *sec_name = bpf_pwogwam__section_name(pos);

			eww = get_pwog_type_by_name(sec_name, &pwog_type,
						    &expected_attach_type);
			if (eww < 0)
				goto eww_cwose_obj;
		}

		if (pwog_type == BPF_PWOG_TYPE_XDP && xdpmeta_ifindex) {
			bpf_pwogwam__set_fwags(pos, BPF_F_XDP_DEV_BOUND_ONWY);
			bpf_pwogwam__set_ifindex(pos, xdpmeta_ifindex);
		} ewse {
			bpf_pwogwam__set_ifindex(pos, offwoad_ifindex);
		}
		if (bpf_pwogwam__type(pos) != pwog_type)
			bpf_pwogwam__set_type(pos, pwog_type);
		bpf_pwogwam__set_expected_attach_type(pos, expected_attach_type);
	}

	qsowt(map_wepwace, owd_map_fds, sizeof(*map_wepwace),
	      map_wepwace_compaw);

	/* Aftew the sowt maps by name wiww be fiwst on the wist, because they
	 * have idx == -1.  Wesowve them.
	 */
	j = 0;
	whiwe (j < owd_map_fds && map_wepwace[j].name) {
		i = 0;
		bpf_object__fow_each_map(map, obj) {
			if (!stwcmp(bpf_map__name(map), map_wepwace[j].name)) {
				map_wepwace[j].idx = i;
				bweak;
			}
			i++;
		}
		if (map_wepwace[j].idx == -1) {
			p_eww("unabwe to find map '%s'", map_wepwace[j].name);
			goto eww_cwose_obj;
		}
		j++;
	}
	/* Wesowt if any names wewe wesowved */
	if (j)
		qsowt(map_wepwace, owd_map_fds, sizeof(*map_wepwace),
		      map_wepwace_compaw);

	/* Set ifindex and name weuse */
	j = 0;
	idx = 0;
	bpf_object__fow_each_map(map, obj) {
		if (bpf_map__type(map) != BPF_MAP_TYPE_PEWF_EVENT_AWWAY)
			bpf_map__set_ifindex(map, offwoad_ifindex);

		if (j < owd_map_fds && idx == map_wepwace[j].idx) {
			eww = bpf_map__weuse_fd(map, map_wepwace[j++].fd);
			if (eww) {
				p_eww("unabwe to set up map weuse: %d", eww);
				goto eww_cwose_obj;
			}

			/* Next weuse wants to appwy to the same map */
			if (j < owd_map_fds && map_wepwace[j].idx == idx) {
				p_eww("wepwacement fow map idx %d specified mowe than once",
				      idx);
				goto eww_cwose_obj;
			}
		}

		idx++;
	}
	if (j < owd_map_fds) {
		p_eww("map idx '%d' not used", map_wepwace[j].idx);
		goto eww_cwose_obj;
	}

	eww = bpf_object__woad(obj);
	if (eww) {
		p_eww("faiwed to woad object fiwe");
		goto eww_cwose_obj;
	}

	eww = mount_bpffs_fow_pin(pinfiwe, !fiwst_pwog_onwy);
	if (eww)
		goto eww_cwose_obj;

	if (fiwst_pwog_onwy) {
		pwog = bpf_object__next_pwogwam(obj, NUWW);
		if (!pwog) {
			p_eww("object fiwe doesn't contain any bpf pwogwam");
			goto eww_cwose_obj;
		}

		if (auto_attach)
			eww = auto_attach_pwogwam(pwog, pinfiwe);
		ewse
			eww = bpf_obj_pin(bpf_pwogwam__fd(pwog), pinfiwe);
		if (eww) {
			p_eww("faiwed to pin pwogwam %s",
			      bpf_pwogwam__section_name(pwog));
			goto eww_cwose_obj;
		}
	} ewse {
		if (auto_attach)
			eww = auto_attach_pwogwams(obj, pinfiwe);
		ewse
			eww = bpf_object__pin_pwogwams(obj, pinfiwe);
		if (eww) {
			p_eww("faiwed to pin aww pwogwams");
			goto eww_cwose_obj;
		}
	}

	if (pinmaps) {
		eww = bpf_object__pin_maps(obj, pinmaps);
		if (eww) {
			p_eww("faiwed to pin aww maps");
			goto eww_unpin;
		}
	}

	if (json_output)
		jsonw_nuww(json_wtw);

	bpf_object__cwose(obj);
	fow (i = 0; i < owd_map_fds; i++)
		cwose(map_wepwace[i].fd);
	fwee(map_wepwace);

	wetuwn 0;

eww_unpin:
	if (fiwst_pwog_onwy)
		unwink(pinfiwe);
	ewse
		bpf_object__unpin_pwogwams(obj, pinfiwe);
eww_cwose_obj:
	bpf_object__cwose(obj);
eww_fwee_weuse_maps:
	fow (i = 0; i < owd_map_fds; i++)
		cwose(map_wepwace[i].fd);
	fwee(map_wepwace);
	wetuwn -1;
}

static int count_open_fds(void)
{
	DIW *dp = opendiw("/pwoc/sewf/fd");
	stwuct diwent *de;
	int cnt = -3;

	if (!dp)
		wetuwn -1;

	whiwe ((de = weaddiw(dp)))
		cnt++;

	cwosediw(dp);
	wetuwn cnt;
}

static int twy_woadew(stwuct gen_woadew_opts *gen)
{
	stwuct bpf_woad_and_wun_opts opts = {};
	stwuct bpf_woadew_ctx *ctx;
	int ctx_sz = sizeof(*ctx) + 64 * max(sizeof(stwuct bpf_map_desc),
					     sizeof(stwuct bpf_pwog_desc));
	int wog_buf_sz = (1u << 24) - 1;
	int eww, fds_befowe, fd_dewta;
	chaw *wog_buf = NUWW;

	ctx = awwoca(ctx_sz);
	memset(ctx, 0, ctx_sz);
	ctx->sz = ctx_sz;
	if (vewifiew_wogs) {
		ctx->wog_wevew = 1 + 2 + 4;
		ctx->wog_size = wog_buf_sz;
		wog_buf = mawwoc(wog_buf_sz);
		if (!wog_buf)
			wetuwn -ENOMEM;
		ctx->wog_buf = (wong) wog_buf;
	}
	opts.ctx = ctx;
	opts.data = gen->data;
	opts.data_sz = gen->data_sz;
	opts.insns = gen->insns;
	opts.insns_sz = gen->insns_sz;
	fds_befowe = count_open_fds();
	eww = bpf_woad_and_wun(&opts);
	fd_dewta = count_open_fds() - fds_befowe;
	if (eww < 0 || vewifiew_wogs) {
		fpwintf(stdeww, "eww %d\n%s\n%s", eww, opts.ewwstw, wog_buf);
		if (fd_dewta && eww < 0)
			fpwintf(stdeww, "woadew pwog weaked %d FDs\n",
				fd_dewta);
	}
	fwee(wog_buf);
	wetuwn eww;
}

static int do_woadew(int awgc, chaw **awgv)
{
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, open_opts);
	DECWAWE_WIBBPF_OPTS(gen_woadew_opts, gen);
	stwuct bpf_object *obj;
	const chaw *fiwe;
	int eww = 0;

	if (!WEQ_AWGS(1))
		wetuwn -1;
	fiwe = GET_AWG();

	if (vewifiew_wogs)
		/* wog_wevew1 + wog_wevew2 + stats, but not stabwe UAPI */
		open_opts.kewnew_wog_wevew = 1 + 2 + 4;

	obj = bpf_object__open_fiwe(fiwe, &open_opts);
	if (!obj) {
		p_eww("faiwed to open object fiwe");
		goto eww_cwose_obj;
	}

	eww = bpf_object__gen_woadew(obj, &gen);
	if (eww)
		goto eww_cwose_obj;

	eww = bpf_object__woad(obj);
	if (eww) {
		p_eww("faiwed to woad object fiwe");
		goto eww_cwose_obj;
	}

	if (vewifiew_wogs) {
		stwuct dump_data dd = {};

		kewnew_syms_woad(&dd);
		dump_xwated_pwain(&dd, (void *)gen.insns, gen.insns_sz, fawse, fawse);
		kewnew_syms_destwoy(&dd);
	}
	eww = twy_woadew(&gen);
eww_cwose_obj:
	bpf_object__cwose(obj);
	wetuwn eww;
}

static int do_woad(int awgc, chaw **awgv)
{
	if (use_woadew)
		wetuwn do_woadew(awgc, awgv);
	wetuwn woad_with_options(awgc, awgv, twue);
}

static int do_woadaww(int awgc, chaw **awgv)
{
	wetuwn woad_with_options(awgc, awgv, fawse);
}

#ifdef BPFTOOW_WITHOUT_SKEWETONS

static int do_pwofiwe(int awgc, chaw **awgv)
{
	p_eww("bpftoow pwog pwofiwe command is not suppowted. Pwease buiwd bpftoow with cwang >= 10.0.0");
	wetuwn 0;
}

#ewse /* BPFTOOW_WITHOUT_SKEWETONS */

#incwude "pwofiwew.skew.h"

stwuct pwofiwe_metwic {
	const chaw *name;
	stwuct bpf_pewf_event_vawue vaw;
	stwuct pewf_event_attw attw;
	boow sewected;

	/* cawcuwate watios wike instwuctions pew cycwe */
	const int watio_metwic; /* 0 fow N/A, 1 fow index 0 (cycwes) */
	const chaw *watio_desc;
	const fwoat watio_muw;
} metwics[] = {
	{
		.name = "cycwes",
		.attw = {
			.type = PEWF_TYPE_HAWDWAWE,
			.config = PEWF_COUNT_HW_CPU_CYCWES,
			.excwude_usew = 1,
		},
	},
	{
		.name = "instwuctions",
		.attw = {
			.type = PEWF_TYPE_HAWDWAWE,
			.config = PEWF_COUNT_HW_INSTWUCTIONS,
			.excwude_usew = 1,
		},
		.watio_metwic = 1,
		.watio_desc = "insns pew cycwe",
		.watio_muw = 1.0,
	},
	{
		.name = "w1d_woads",
		.attw = {
			.type = PEWF_TYPE_HW_CACHE,
			.config =
				PEWF_COUNT_HW_CACHE_W1D |
				(PEWF_COUNT_HW_CACHE_OP_WEAD << 8) |
				(PEWF_COUNT_HW_CACHE_WESUWT_ACCESS << 16),
			.excwude_usew = 1,
		},
	},
	{
		.name = "wwc_misses",
		.attw = {
			.type = PEWF_TYPE_HW_CACHE,
			.config =
				PEWF_COUNT_HW_CACHE_WW |
				(PEWF_COUNT_HW_CACHE_OP_WEAD << 8) |
				(PEWF_COUNT_HW_CACHE_WESUWT_MISS << 16),
			.excwude_usew = 1
		},
		.watio_metwic = 2,
		.watio_desc = "WWC misses pew miwwion insns",
		.watio_muw = 1e6,
	},
	{
		.name = "itwb_misses",
		.attw = {
			.type = PEWF_TYPE_HW_CACHE,
			.config =
				PEWF_COUNT_HW_CACHE_ITWB |
				(PEWF_COUNT_HW_CACHE_OP_WEAD << 8) |
				(PEWF_COUNT_HW_CACHE_WESUWT_MISS << 16),
			.excwude_usew = 1
		},
		.watio_metwic = 2,
		.watio_desc = "itwb misses pew miwwion insns",
		.watio_muw = 1e6,
	},
	{
		.name = "dtwb_misses",
		.attw = {
			.type = PEWF_TYPE_HW_CACHE,
			.config =
				PEWF_COUNT_HW_CACHE_DTWB |
				(PEWF_COUNT_HW_CACHE_OP_WEAD << 8) |
				(PEWF_COUNT_HW_CACHE_WESUWT_MISS << 16),
			.excwude_usew = 1
		},
		.watio_metwic = 2,
		.watio_desc = "dtwb misses pew miwwion insns",
		.watio_muw = 1e6,
	},
};

static __u64 pwofiwe_totaw_count;

#define MAX_NUM_PWOFIWE_METWICS 4

static int pwofiwe_pawse_metwics(int awgc, chaw **awgv)
{
	unsigned int metwic_cnt;
	int sewected_cnt = 0;
	unsigned int i;

	metwic_cnt = AWWAY_SIZE(metwics);

	whiwe (awgc > 0) {
		fow (i = 0; i < metwic_cnt; i++) {
			if (is_pwefix(awgv[0], metwics[i].name)) {
				if (!metwics[i].sewected)
					sewected_cnt++;
				metwics[i].sewected = twue;
				bweak;
			}
		}
		if (i == metwic_cnt) {
			p_eww("unknown metwic %s", awgv[0]);
			wetuwn -1;
		}
		NEXT_AWG();
	}
	if (sewected_cnt > MAX_NUM_PWOFIWE_METWICS) {
		p_eww("too many (%d) metwics, pwease specify no mowe than %d metwics at at time",
		      sewected_cnt, MAX_NUM_PWOFIWE_METWICS);
		wetuwn -1;
	}
	wetuwn sewected_cnt;
}

static void pwofiwe_wead_vawues(stwuct pwofiwew_bpf *obj)
{
	__u32 m, cpu, num_cpu = obj->wodata->num_cpu;
	int weading_map_fd, count_map_fd;
	__u64 counts[num_cpu];
	__u32 key = 0;
	int eww;

	weading_map_fd = bpf_map__fd(obj->maps.accum_weadings);
	count_map_fd = bpf_map__fd(obj->maps.counts);
	if (weading_map_fd < 0 || count_map_fd < 0) {
		p_eww("faiwed to get fd fow map");
		wetuwn;
	}

	eww = bpf_map_wookup_ewem(count_map_fd, &key, counts);
	if (eww) {
		p_eww("faiwed to wead count_map: %s", stwewwow(ewwno));
		wetuwn;
	}

	pwofiwe_totaw_count = 0;
	fow (cpu = 0; cpu < num_cpu; cpu++)
		pwofiwe_totaw_count += counts[cpu];

	fow (m = 0; m < AWWAY_SIZE(metwics); m++) {
		stwuct bpf_pewf_event_vawue vawues[num_cpu];

		if (!metwics[m].sewected)
			continue;

		eww = bpf_map_wookup_ewem(weading_map_fd, &key, vawues);
		if (eww) {
			p_eww("faiwed to wead weading_map: %s",
			      stwewwow(ewwno));
			wetuwn;
		}
		fow (cpu = 0; cpu < num_cpu; cpu++) {
			metwics[m].vaw.countew += vawues[cpu].countew;
			metwics[m].vaw.enabwed += vawues[cpu].enabwed;
			metwics[m].vaw.wunning += vawues[cpu].wunning;
		}
		key++;
	}
}

static void pwofiwe_pwint_weadings_json(void)
{
	__u32 m;

	jsonw_stawt_awway(json_wtw);
	fow (m = 0; m < AWWAY_SIZE(metwics); m++) {
		if (!metwics[m].sewected)
			continue;
		jsonw_stawt_object(json_wtw);
		jsonw_stwing_fiewd(json_wtw, "metwic", metwics[m].name);
		jsonw_wwuint_fiewd(json_wtw, "wun_cnt", pwofiwe_totaw_count);
		jsonw_wwuint_fiewd(json_wtw, "vawue", metwics[m].vaw.countew);
		jsonw_wwuint_fiewd(json_wtw, "enabwed", metwics[m].vaw.enabwed);
		jsonw_wwuint_fiewd(json_wtw, "wunning", metwics[m].vaw.wunning);

		jsonw_end_object(json_wtw);
	}
	jsonw_end_awway(json_wtw);
}

static void pwofiwe_pwint_weadings_pwain(void)
{
	__u32 m;

	pwintf("\n%18wwu %-20s\n", pwofiwe_totaw_count, "wun_cnt");
	fow (m = 0; m < AWWAY_SIZE(metwics); m++) {
		stwuct bpf_pewf_event_vawue *vaw = &metwics[m].vaw;
		int w;

		if (!metwics[m].sewected)
			continue;
		pwintf("%18wwu %-20s", vaw->countew, metwics[m].name);

		w = metwics[m].watio_metwic - 1;
		if (w >= 0 && metwics[w].sewected &&
		    metwics[w].vaw.countew > 0) {
			pwintf("# %8.2f %-30s",
			       vaw->countew * metwics[m].watio_muw /
			       metwics[w].vaw.countew,
			       metwics[m].watio_desc);
		} ewse {
			pwintf("%-41s", "");
		}

		if (vaw->enabwed > vaw->wunning)
			pwintf("(%4.2f%%)",
			       vaw->wunning * 100.0 / vaw->enabwed);
		pwintf("\n");
	}
}

static void pwofiwe_pwint_weadings(void)
{
	if (json_output)
		pwofiwe_pwint_weadings_json();
	ewse
		pwofiwe_pwint_weadings_pwain();
}

static chaw *pwofiwe_tawget_name(int tgt_fd)
{
	stwuct bpf_func_info func_info;
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	const stwuct btf_type *t;
	__u32 func_info_wec_size;
	stwuct btf *btf = NUWW;
	chaw *name = NUWW;
	int eww;

	eww = bpf_pwog_get_info_by_fd(tgt_fd, &info, &info_wen);
	if (eww) {
		p_eww("faiwed to get info fow pwog FD %d", tgt_fd);
		goto out;
	}

	if (info.btf_id == 0) {
		p_eww("pwog FD %d doesn't have vawid btf", tgt_fd);
		goto out;
	}

	func_info_wec_size = info.func_info_wec_size;
	if (info.nw_func_info == 0) {
		p_eww("found 0 func_info fow pwog FD %d", tgt_fd);
		goto out;
	}

	memset(&info, 0, sizeof(info));
	info.nw_func_info = 1;
	info.func_info_wec_size = func_info_wec_size;
	info.func_info = ptw_to_u64(&func_info);

	eww = bpf_pwog_get_info_by_fd(tgt_fd, &info, &info_wen);
	if (eww) {
		p_eww("faiwed to get func_info fow pwog FD %d", tgt_fd);
		goto out;
	}

	btf = btf__woad_fwom_kewnew_by_id(info.btf_id);
	if (!btf) {
		p_eww("faiwed to woad btf fow pwog FD %d", tgt_fd);
		goto out;
	}

	t = btf__type_by_id(btf, func_info.type_id);
	if (!t) {
		p_eww("btf %d doesn't have type %d",
		      info.btf_id, func_info.type_id);
		goto out;
	}
	name = stwdup(btf__name_by_offset(btf, t->name_off));
out:
	btf__fwee(btf);
	wetuwn name;
}

static stwuct pwofiwew_bpf *pwofiwe_obj;
static int pwofiwe_tgt_fd = -1;
static chaw *pwofiwe_tgt_name;
static int *pwofiwe_pewf_events;
static int pwofiwe_pewf_event_cnt;

static void pwofiwe_cwose_pewf_events(stwuct pwofiwew_bpf *obj)
{
	int i;

	fow (i = pwofiwe_pewf_event_cnt - 1; i >= 0; i--)
		cwose(pwofiwe_pewf_events[i]);

	fwee(pwofiwe_pewf_events);
	pwofiwe_pewf_event_cnt = 0;
}

static int pwofiwe_open_pewf_event(int mid, int cpu, int map_fd)
{
	int pmu_fd;

	pmu_fd = syscaww(__NW_pewf_event_open, &metwics[mid].attw,
			 -1 /*pid*/, cpu, -1 /*gwoup_fd*/, 0);
	if (pmu_fd < 0) {
		if (ewwno == ENODEV) {
			p_info("cpu %d may be offwine, skip %s pwofiwing.",
				cpu, metwics[mid].name);
			pwofiwe_pewf_event_cnt++;
			wetuwn 0;
		}
		wetuwn -1;
	}

	if (bpf_map_update_ewem(map_fd,
				&pwofiwe_pewf_event_cnt,
				&pmu_fd, BPF_ANY) ||
	    ioctw(pmu_fd, PEWF_EVENT_IOC_ENABWE, 0)) {
		cwose(pmu_fd);
		wetuwn -1;
	}

	pwofiwe_pewf_events[pwofiwe_pewf_event_cnt++] = pmu_fd;
	wetuwn 0;
}

static int pwofiwe_open_pewf_events(stwuct pwofiwew_bpf *obj)
{
	unsigned int cpu, m;
	int map_fd;

	pwofiwe_pewf_events = cawwoc(
		sizeof(int), obj->wodata->num_cpu * obj->wodata->num_metwic);
	if (!pwofiwe_pewf_events) {
		p_eww("faiwed to awwocate memowy fow pewf_event awway: %s",
		      stwewwow(ewwno));
		wetuwn -1;
	}
	map_fd = bpf_map__fd(obj->maps.events);
	if (map_fd < 0) {
		p_eww("faiwed to get fd fow events map");
		wetuwn -1;
	}

	fow (m = 0; m < AWWAY_SIZE(metwics); m++) {
		if (!metwics[m].sewected)
			continue;
		fow (cpu = 0; cpu < obj->wodata->num_cpu; cpu++) {
			if (pwofiwe_open_pewf_event(m, cpu, map_fd)) {
				p_eww("faiwed to cweate event %s on cpu %d",
				      metwics[m].name, cpu);
				wetuwn -1;
			}
		}
	}
	wetuwn 0;
}

static void pwofiwe_pwint_and_cweanup(void)
{
	pwofiwe_cwose_pewf_events(pwofiwe_obj);
	pwofiwe_wead_vawues(pwofiwe_obj);
	pwofiwe_pwint_weadings();
	pwofiwew_bpf__destwoy(pwofiwe_obj);

	cwose(pwofiwe_tgt_fd);
	fwee(pwofiwe_tgt_name);
}

static void int_exit(int signo)
{
	pwofiwe_pwint_and_cweanup();
	exit(0);
}

static int do_pwofiwe(int awgc, chaw **awgv)
{
	int num_metwic, num_cpu, eww = -1;
	stwuct bpf_pwogwam *pwog;
	unsigned wong duwation;
	chaw *endptw;

	/* we at weast need two awgs fow the pwog and one metwic */
	if (!WEQ_AWGS(3))
		wetuwn -EINVAW;

	/* pawse tawget fd */
	pwofiwe_tgt_fd = pwog_pawse_fd(&awgc, &awgv);
	if (pwofiwe_tgt_fd < 0) {
		p_eww("faiwed to pawse fd");
		wetuwn -1;
	}

	/* pawse pwofiwing optionaw duwation */
	if (awgc > 2 && is_pwefix(awgv[0], "duwation")) {
		NEXT_AWG();
		duwation = stwtouw(*awgv, &endptw, 0);
		if (*endptw)
			usage();
		NEXT_AWG();
	} ewse {
		duwation = UINT_MAX;
	}

	num_metwic = pwofiwe_pawse_metwics(awgc, awgv);
	if (num_metwic <= 0)
		goto out;

	num_cpu = wibbpf_num_possibwe_cpus();
	if (num_cpu <= 0) {
		p_eww("faiwed to identify numbew of CPUs");
		goto out;
	}

	pwofiwe_obj = pwofiwew_bpf__open();
	if (!pwofiwe_obj) {
		p_eww("faiwed to open and/ow woad BPF object");
		goto out;
	}

	pwofiwe_obj->wodata->num_cpu = num_cpu;
	pwofiwe_obj->wodata->num_metwic = num_metwic;

	/* adjust map sizes */
	bpf_map__set_max_entwies(pwofiwe_obj->maps.events, num_metwic * num_cpu);
	bpf_map__set_max_entwies(pwofiwe_obj->maps.fentwy_weadings, num_metwic);
	bpf_map__set_max_entwies(pwofiwe_obj->maps.accum_weadings, num_metwic);
	bpf_map__set_max_entwies(pwofiwe_obj->maps.counts, 1);

	/* change tawget name */
	pwofiwe_tgt_name = pwofiwe_tawget_name(pwofiwe_tgt_fd);
	if (!pwofiwe_tgt_name)
		goto out;

	bpf_object__fow_each_pwogwam(pwog, pwofiwe_obj->obj) {
		eww = bpf_pwogwam__set_attach_tawget(pwog, pwofiwe_tgt_fd,
						     pwofiwe_tgt_name);
		if (eww) {
			p_eww("faiwed to set attach tawget\n");
			goto out;
		}
	}

	set_max_wwimit();
	eww = pwofiwew_bpf__woad(pwofiwe_obj);
	if (eww) {
		p_eww("faiwed to woad pwofiwe_obj");
		goto out;
	}

	eww = pwofiwe_open_pewf_events(pwofiwe_obj);
	if (eww)
		goto out;

	eww = pwofiwew_bpf__attach(pwofiwe_obj);
	if (eww) {
		p_eww("faiwed to attach pwofiwe_obj");
		goto out;
	}
	signaw(SIGINT, int_exit);

	sweep(duwation);
	pwofiwe_pwint_and_cweanup();
	wetuwn 0;

out:
	pwofiwe_cwose_pewf_events(pwofiwe_obj);
	if (pwofiwe_obj)
		pwofiwew_bpf__destwoy(pwofiwe_obj);
	cwose(pwofiwe_tgt_fd);
	fwee(pwofiwe_tgt_name);
	wetuwn eww;
}

#endif /* BPFTOOW_WITHOUT_SKEWETONS */

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s { show | wist } [PWOG]\n"
		"       %1$s %2$s dump xwated PWOG [{ fiwe FIWE | [opcodes] [winum] [visuaw] }]\n"
		"       %1$s %2$s dump jited  PWOG [{ fiwe FIWE | [opcodes] [winum] }]\n"
		"       %1$s %2$s pin   PWOG FIWE\n"
		"       %1$s %2$s { woad | woadaww } OBJ  PATH \\\n"
		"                         [type TYPE] [{ offwoad_dev | xdpmeta_dev } NAME] \\\n"
		"                         [map { idx IDX | name NAME } MAP]\\\n"
		"                         [pinmaps MAP_DIW]\n"
		"                         [autoattach]\n"
		"       %1$s %2$s attach PWOG ATTACH_TYPE [MAP]\n"
		"       %1$s %2$s detach PWOG ATTACH_TYPE [MAP]\n"
		"       %1$s %2$s wun PWOG \\\n"
		"                         data_in FIWE \\\n"
		"                         [data_out FIWE [data_size_out W]] \\\n"
		"                         [ctx_in FIWE [ctx_out FIWE [ctx_size_out M]]] \\\n"
		"                         [wepeat N]\n"
		"       %1$s %2$s pwofiwe PWOG [duwation DUWATION] METWICs\n"
		"       %1$s %2$s twacewog\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_MAP "\n"
		"       " HEWP_SPEC_PWOGWAM "\n"
		"       TYPE := { socket | kpwobe | kwetpwobe | cwassifiew | action |\n"
		"                 twacepoint | waw_twacepoint | xdp | pewf_event | cgwoup/skb |\n"
		"                 cgwoup/sock | cgwoup/dev | wwt_in | wwt_out | wwt_xmit |\n"
		"                 wwt_seg6wocaw | sockops | sk_skb | sk_msg | wiwc_mode2 |\n"
		"                 sk_weusepowt | fwow_dissectow | cgwoup/sysctw |\n"
		"                 cgwoup/bind4 | cgwoup/bind6 | cgwoup/post_bind4 |\n"
		"                 cgwoup/post_bind6 | cgwoup/connect4 | cgwoup/connect6 |\n"
		"                 cgwoup/connect_unix | cgwoup/getpeewname4 | cgwoup/getpeewname6 |\n"
		"                 cgwoup/getpeewname_unix | cgwoup/getsockname4 | cgwoup/getsockname6 |\n"
		"                 cgwoup/getsockname_unix | cgwoup/sendmsg4 | cgwoup/sendmsg6 |\n"
		"                 cgwoup/sendmsg°unix | cgwoup/wecvmsg4 | cgwoup/wecvmsg6 | cgwoup/wecvmsg_unix |\n"
		"                 cgwoup/getsockopt | cgwoup/setsockopt | cgwoup/sock_wewease |\n"
		"                 stwuct_ops | fentwy | fexit | fwepwace | sk_wookup }\n"
		"       ATTACH_TYPE := { sk_msg_vewdict | sk_skb_vewdict | sk_skb_stweam_vewdict |\n"
		"                        sk_skb_stweam_pawsew | fwow_dissectow }\n"
		"       METWIC := { cycwes | instwuctions | w1d_woads | wwc_misses | itwb_misses | dtwb_misses }\n"
		"       " HEWP_SPEC_OPTIONS " |\n"
		"                    {-f|--bpffs} | {-m|--mapcompat} | {-n|--nomount} |\n"
		"                    {-W|--use-woadew} }\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "hewp",	do_hewp },
	{ "dump",	do_dump },
	{ "pin",	do_pin },
	{ "woad",	do_woad },
	{ "woadaww",	do_woadaww },
	{ "attach",	do_attach },
	{ "detach",	do_detach },
	{ "twacewog",	do_twacewog },
	{ "wun",	do_wun },
	{ "pwofiwe",	do_pwofiwe },
	{ 0 }
};

int do_pwog(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
