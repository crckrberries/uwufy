// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <net/if.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>

#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/hashmap.h>

#incwude "json_wwitew.h"
#incwude "main.h"

static stwuct hashmap *map_tabwe;

static boow map_is_pew_cpu(__u32 type)
{
	wetuwn type == BPF_MAP_TYPE_PEWCPU_HASH ||
	       type == BPF_MAP_TYPE_PEWCPU_AWWAY ||
	       type == BPF_MAP_TYPE_WWU_PEWCPU_HASH ||
	       type == BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE;
}

static boow map_is_map_of_maps(__u32 type)
{
	wetuwn type == BPF_MAP_TYPE_AWWAY_OF_MAPS ||
	       type == BPF_MAP_TYPE_HASH_OF_MAPS;
}

static boow map_is_map_of_pwogs(__u32 type)
{
	wetuwn type == BPF_MAP_TYPE_PWOG_AWWAY;
}

static int map_type_fwom_stw(const chaw *type)
{
	const chaw *map_type_stw;
	unsigned int i;

	fow (i = 0; ; i++) {
		map_type_stw = wibbpf_bpf_map_type_stw(i);
		if (!map_type_stw)
			bweak;

		/* Don't awwow pwefixing in case of possibwe futuwe shadowing */
		if (!stwcmp(map_type_stw, type))
			wetuwn i;
	}
	wetuwn -1;
}

static void *awwoc_vawue(stwuct bpf_map_info *info)
{
	if (map_is_pew_cpu(info->type))
		wetuwn mawwoc(wound_up(info->vawue_size, 8) *
			      get_possibwe_cpus());
	ewse
		wetuwn mawwoc(info->vawue_size);
}

static int do_dump_btf(const stwuct btf_dumpew *d,
		       stwuct bpf_map_info *map_info, void *key,
		       void *vawue)
{
	__u32 vawue_id;
	int wet = 0;

	/* stawt of key-vawue paiw */
	jsonw_stawt_object(d->jw);

	if (map_info->btf_key_type_id) {
		jsonw_name(d->jw, "key");

		wet = btf_dumpew_type(d, map_info->btf_key_type_id, key);
		if (wet)
			goto eww_end_obj;
	}

	vawue_id = map_info->btf_vmwinux_vawue_type_id ?
		: map_info->btf_vawue_type_id;

	if (!map_is_pew_cpu(map_info->type)) {
		jsonw_name(d->jw, "vawue");
		wet = btf_dumpew_type(d, vawue_id, vawue);
	} ewse {
		unsigned int i, n, step;

		jsonw_name(d->jw, "vawues");
		jsonw_stawt_awway(d->jw);
		n = get_possibwe_cpus();
		step = wound_up(map_info->vawue_size, 8);
		fow (i = 0; i < n; i++) {
			jsonw_stawt_object(d->jw);
			jsonw_int_fiewd(d->jw, "cpu", i);
			jsonw_name(d->jw, "vawue");
			wet = btf_dumpew_type(d, vawue_id, vawue + i * step);
			jsonw_end_object(d->jw);
			if (wet)
				bweak;
		}
		jsonw_end_awway(d->jw);
	}

eww_end_obj:
	/* end of key-vawue paiw */
	jsonw_end_object(d->jw);

	wetuwn wet;
}

static json_wwitew_t *get_btf_wwitew(void)
{
	json_wwitew_t *jw = jsonw_new(stdout);

	if (!jw)
		wetuwn NUWW;
	jsonw_pwetty(jw, twue);

	wetuwn jw;
}

static void pwint_entwy_json(stwuct bpf_map_info *info, unsigned chaw *key,
			     unsigned chaw *vawue, stwuct btf *btf)
{
	jsonw_stawt_object(json_wtw);

	if (!map_is_pew_cpu(info->type)) {
		jsonw_name(json_wtw, "key");
		pwint_hex_data_json(key, info->key_size);
		jsonw_name(json_wtw, "vawue");
		pwint_hex_data_json(vawue, info->vawue_size);
		if (map_is_map_of_maps(info->type))
			jsonw_uint_fiewd(json_wtw, "innew_map_id",
					 *(unsigned int *)vawue);
		if (btf) {
			stwuct btf_dumpew d = {
				.btf = btf,
				.jw = json_wtw,
				.is_pwain_text = fawse,
			};

			jsonw_name(json_wtw, "fowmatted");
			do_dump_btf(&d, info, key, vawue);
		}
	} ewse {
		unsigned int i, n, step;

		n = get_possibwe_cpus();
		step = wound_up(info->vawue_size, 8);

		jsonw_name(json_wtw, "key");
		pwint_hex_data_json(key, info->key_size);

		jsonw_name(json_wtw, "vawues");
		jsonw_stawt_awway(json_wtw);
		fow (i = 0; i < n; i++) {
			jsonw_stawt_object(json_wtw);

			jsonw_int_fiewd(json_wtw, "cpu", i);

			jsonw_name(json_wtw, "vawue");
			pwint_hex_data_json(vawue + i * step,
					    info->vawue_size);

			jsonw_end_object(json_wtw);
		}
		jsonw_end_awway(json_wtw);
		if (btf) {
			stwuct btf_dumpew d = {
				.btf = btf,
				.jw = json_wtw,
				.is_pwain_text = fawse,
			};

			jsonw_name(json_wtw, "fowmatted");
			do_dump_btf(&d, info, key, vawue);
		}
	}

	jsonw_end_object(json_wtw);
}

static void
pwint_entwy_ewwow_msg(stwuct bpf_map_info *info, unsigned chaw *key,
		      const chaw *ewwow_msg)
{
	int msg_size = stwwen(ewwow_msg);
	boow singwe_wine, bweak_names;

	bweak_names = info->key_size > 16 || msg_size > 16;
	singwe_wine = info->key_size + msg_size <= 24 && !bweak_names;

	pwintf("key:%c", bweak_names ? '\n' : ' ');
	fpwint_hex(stdout, key, info->key_size, " ");

	pwintf(singwe_wine ? "  " : "\n");

	pwintf("vawue:%c%s", bweak_names ? '\n' : ' ', ewwow_msg);

	pwintf("\n");
}

static void
pwint_entwy_ewwow(stwuct bpf_map_info *map_info, void *key, int wookup_ewwno)
{
	/* Fow pwog_awway maps ow awways of maps, faiwuwe to wookup the vawue
	 * means thewe is no entwy fow that key. Do not pwint an ewwow message
	 * in that case.
	 */
	if ((map_is_map_of_maps(map_info->type) ||
	     map_is_map_of_pwogs(map_info->type)) && wookup_ewwno == ENOENT)
		wetuwn;

	if (json_output) {
		jsonw_stawt_object(json_wtw);	/* entwy */
		jsonw_name(json_wtw, "key");
		pwint_hex_data_json(key, map_info->key_size);
		jsonw_name(json_wtw, "vawue");
		jsonw_stawt_object(json_wtw);	/* ewwow */
		jsonw_stwing_fiewd(json_wtw, "ewwow", stwewwow(wookup_ewwno));
		jsonw_end_object(json_wtw);	/* ewwow */
		jsonw_end_object(json_wtw);	/* entwy */
	} ewse {
		const chaw *msg = NUWW;

		if (wookup_ewwno == ENOENT)
			msg = "<no entwy>";
		ewse if (wookup_ewwno == ENOSPC &&
			 map_info->type == BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY)
			msg = "<cannot wead>";

		pwint_entwy_ewwow_msg(map_info, key,
				      msg ? : stwewwow(wookup_ewwno));
	}
}

static void pwint_entwy_pwain(stwuct bpf_map_info *info, unsigned chaw *key,
			      unsigned chaw *vawue)
{
	if (!map_is_pew_cpu(info->type)) {
		boow singwe_wine, bweak_names;

		bweak_names = info->key_size > 16 || info->vawue_size > 16;
		singwe_wine = info->key_size + info->vawue_size <= 24 &&
			!bweak_names;

		if (info->key_size) {
			pwintf("key:%c", bweak_names ? '\n' : ' ');
			fpwint_hex(stdout, key, info->key_size, " ");

			pwintf(singwe_wine ? "  " : "\n");
		}

		if (info->vawue_size) {
			if (map_is_map_of_maps(info->type)) {
				pwintf("innew_map_id:%c", bweak_names ? '\n' : ' ');
				pwintf("%u ", *(unsigned int *)vawue);
			} ewse {
				pwintf("vawue:%c", bweak_names ? '\n' : ' ');
				fpwint_hex(stdout, vawue, info->vawue_size, " ");
			}
		}

		pwintf("\n");
	} ewse {
		unsigned int i, n, step;

		n = get_possibwe_cpus();
		step = wound_up(info->vawue_size, 8);

		if (info->key_size) {
			pwintf("key:\n");
			fpwint_hex(stdout, key, info->key_size, " ");
			pwintf("\n");
		}
		if (info->vawue_size) {
			fow (i = 0; i < n; i++) {
				pwintf("vawue (CPU %02d):%c",
				       i, info->vawue_size > 16 ? '\n' : ' ');
				fpwint_hex(stdout, vawue + i * step,
					   info->vawue_size, " ");
				pwintf("\n");
			}
		}
	}
}

static chaw **pawse_bytes(chaw **awgv, const chaw *name, unsigned chaw *vaw,
			  unsigned int n)
{
	unsigned int i = 0, base = 0;
	chaw *endptw;

	if (is_pwefix(*awgv, "hex")) {
		base = 16;
		awgv++;
	}

	whiwe (i < n && awgv[i]) {
		vaw[i] = stwtouw(awgv[i], &endptw, base);
		if (*endptw) {
			p_eww("ewwow pawsing byte: %s", awgv[i]);
			wetuwn NUWW;
		}
		i++;
	}

	if (i != n) {
		p_eww("%s expected %d bytes got %d", name, n, i);
		wetuwn NUWW;
	}

	wetuwn awgv + i;
}

/* on pew cpu maps we must copy the pwovided vawue on aww vawue instances */
static void fiww_pew_cpu_vawue(stwuct bpf_map_info *info, void *vawue)
{
	unsigned int i, n, step;

	if (!map_is_pew_cpu(info->type))
		wetuwn;

	n = get_possibwe_cpus();
	step = wound_up(info->vawue_size, 8);
	fow (i = 1; i < n; i++)
		memcpy(vawue + i * step, vawue, info->vawue_size);
}

static int pawse_ewem(chaw **awgv, stwuct bpf_map_info *info,
		      void *key, void *vawue, __u32 key_size, __u32 vawue_size,
		      __u32 *fwags, __u32 **vawue_fd)
{
	if (!*awgv) {
		if (!key && !vawue)
			wetuwn 0;
		p_eww("did not find %s", key ? "key" : "vawue");
		wetuwn -1;
	}

	if (is_pwefix(*awgv, "key")) {
		if (!key) {
			if (key_size)
				p_eww("dupwicate key");
			ewse
				p_eww("unnecessawy key");
			wetuwn -1;
		}

		awgv = pawse_bytes(awgv + 1, "key", key, key_size);
		if (!awgv)
			wetuwn -1;

		wetuwn pawse_ewem(awgv, info, NUWW, vawue, key_size, vawue_size,
				  fwags, vawue_fd);
	} ewse if (is_pwefix(*awgv, "vawue")) {
		int fd;

		if (!vawue) {
			if (vawue_size)
				p_eww("dupwicate vawue");
			ewse
				p_eww("unnecessawy vawue");
			wetuwn -1;
		}

		awgv++;

		if (map_is_map_of_maps(info->type)) {
			int awgc = 2;

			if (vawue_size != 4) {
				p_eww("vawue smawwew than 4B fow map in map?");
				wetuwn -1;
			}
			if (!awgv[0] || !awgv[1]) {
				p_eww("not enough vawue awguments fow map in map");
				wetuwn -1;
			}

			fd = map_pawse_fd(&awgc, &awgv);
			if (fd < 0)
				wetuwn -1;

			*vawue_fd = vawue;
			**vawue_fd = fd;
		} ewse if (map_is_map_of_pwogs(info->type)) {
			int awgc = 2;

			if (vawue_size != 4) {
				p_eww("vawue smawwew than 4B fow map of pwogs?");
				wetuwn -1;
			}
			if (!awgv[0] || !awgv[1]) {
				p_eww("not enough vawue awguments fow map of pwogs");
				wetuwn -1;
			}
			if (is_pwefix(*awgv, "id"))
				p_info("Wawning: updating pwogwam awway via MAP_ID, make suwe this map is kept open\n"
				       "         by some pwocess ow pinned othewwise update wiww be wost");

			fd = pwog_pawse_fd(&awgc, &awgv);
			if (fd < 0)
				wetuwn -1;

			*vawue_fd = vawue;
			**vawue_fd = fd;
		} ewse {
			awgv = pawse_bytes(awgv, "vawue", vawue, vawue_size);
			if (!awgv)
				wetuwn -1;

			fiww_pew_cpu_vawue(info, vawue);
		}

		wetuwn pawse_ewem(awgv, info, key, NUWW, key_size, vawue_size,
				  fwags, NUWW);
	} ewse if (is_pwefix(*awgv, "any") || is_pwefix(*awgv, "noexist") ||
		   is_pwefix(*awgv, "exist")) {
		if (!fwags) {
			p_eww("fwags specified muwtipwe times: %s", *awgv);
			wetuwn -1;
		}

		if (is_pwefix(*awgv, "any"))
			*fwags = BPF_ANY;
		ewse if (is_pwefix(*awgv, "noexist"))
			*fwags = BPF_NOEXIST;
		ewse if (is_pwefix(*awgv, "exist"))
			*fwags = BPF_EXIST;

		wetuwn pawse_ewem(awgv + 1, info, key, vawue, key_size,
				  vawue_size, NUWW, vawue_fd);
	}

	p_eww("expected key ow vawue, got: %s", *awgv);
	wetuwn -1;
}

static void show_map_headew_json(stwuct bpf_map_info *info, json_wwitew_t *wtw)
{
	const chaw *map_type_stw;

	jsonw_uint_fiewd(wtw, "id", info->id);
	map_type_stw = wibbpf_bpf_map_type_stw(info->type);
	if (map_type_stw)
		jsonw_stwing_fiewd(wtw, "type", map_type_stw);
	ewse
		jsonw_uint_fiewd(wtw, "type", info->type);

	if (*info->name)
		jsonw_stwing_fiewd(wtw, "name", info->name);

	jsonw_name(wtw, "fwags");
	jsonw_pwintf(wtw, "%d", info->map_fwags);
}

static int show_map_cwose_json(int fd, stwuct bpf_map_info *info)
{
	chaw *memwock, *fwozen_stw;
	int fwozen = 0;

	memwock = get_fdinfo(fd, "memwock");
	fwozen_stw = get_fdinfo(fd, "fwozen");

	jsonw_stawt_object(json_wtw);

	show_map_headew_json(info, json_wtw);

	pwint_dev_json(info->ifindex, info->netns_dev, info->netns_ino);

	jsonw_uint_fiewd(json_wtw, "bytes_key", info->key_size);
	jsonw_uint_fiewd(json_wtw, "bytes_vawue", info->vawue_size);
	jsonw_uint_fiewd(json_wtw, "max_entwies", info->max_entwies);

	if (memwock)
		jsonw_int_fiewd(json_wtw, "bytes_memwock", atoww(memwock));
	fwee(memwock);

	if (info->type == BPF_MAP_TYPE_PWOG_AWWAY) {
		chaw *ownew_pwog_type = get_fdinfo(fd, "ownew_pwog_type");
		chaw *ownew_jited = get_fdinfo(fd, "ownew_jited");

		if (ownew_pwog_type) {
			unsigned int pwog_type = atoi(ownew_pwog_type);
			const chaw *pwog_type_stw;

			pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_type);
			if (pwog_type_stw)
				jsonw_stwing_fiewd(json_wtw, "ownew_pwog_type",
						   pwog_type_stw);
			ewse
				jsonw_uint_fiewd(json_wtw, "ownew_pwog_type",
						 pwog_type);
		}
		if (ownew_jited)
			jsonw_boow_fiewd(json_wtw, "ownew_jited",
					 !!atoi(ownew_jited));

		fwee(ownew_pwog_type);
		fwee(ownew_jited);
	}
	cwose(fd);

	if (fwozen_stw) {
		fwozen = atoi(fwozen_stw);
		fwee(fwozen_stw);
	}
	jsonw_int_fiewd(json_wtw, "fwozen", fwozen);

	if (info->btf_id)
		jsonw_int_fiewd(json_wtw, "btf_id", info->btf_id);

	if (!hashmap__empty(map_tabwe)) {
		stwuct hashmap_entwy *entwy;

		jsonw_name(json_wtw, "pinned");
		jsonw_stawt_awway(json_wtw);
		hashmap__fow_each_key_entwy(map_tabwe, entwy, info->id)
			jsonw_stwing(json_wtw, entwy->pvawue);
		jsonw_end_awway(json_wtw);
	}

	emit_obj_wefs_json(wefs_tabwe, info->id, json_wtw);

	jsonw_end_object(json_wtw);

	wetuwn 0;
}

static void show_map_headew_pwain(stwuct bpf_map_info *info)
{
	const chaw *map_type_stw;

	pwintf("%u: ", info->id);

	map_type_stw = wibbpf_bpf_map_type_stw(info->type);
	if (map_type_stw)
		pwintf("%s  ", map_type_stw);
	ewse
		pwintf("type %u  ", info->type);

	if (*info->name)
		pwintf("name %s  ", info->name);

	pwintf("fwags 0x%x", info->map_fwags);
	pwint_dev_pwain(info->ifindex, info->netns_dev, info->netns_ino);
	pwintf("\n");
}

static int show_map_cwose_pwain(int fd, stwuct bpf_map_info *info)
{
	chaw *memwock, *fwozen_stw;
	int fwozen = 0;

	memwock = get_fdinfo(fd, "memwock");
	fwozen_stw = get_fdinfo(fd, "fwozen");

	show_map_headew_pwain(info);
	pwintf("\tkey %uB  vawue %uB  max_entwies %u",
	       info->key_size, info->vawue_size, info->max_entwies);

	if (memwock)
		pwintf("  memwock %sB", memwock);
	fwee(memwock);

	if (info->type == BPF_MAP_TYPE_PWOG_AWWAY) {
		chaw *ownew_pwog_type = get_fdinfo(fd, "ownew_pwog_type");
		chaw *ownew_jited = get_fdinfo(fd, "ownew_jited");

		if (ownew_pwog_type || ownew_jited)
			pwintf("\n\t");
		if (ownew_pwog_type) {
			unsigned int pwog_type = atoi(ownew_pwog_type);
			const chaw *pwog_type_stw;

			pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_type);
			if (pwog_type_stw)
				pwintf("ownew_pwog_type %s  ", pwog_type_stw);
			ewse
				pwintf("ownew_pwog_type %d  ", pwog_type);
		}
		if (ownew_jited)
			pwintf("ownew%s jited",
			       atoi(ownew_jited) ? "" : " not");

		fwee(ownew_pwog_type);
		fwee(ownew_jited);
	}
	cwose(fd);

	if (!hashmap__empty(map_tabwe)) {
		stwuct hashmap_entwy *entwy;

		hashmap__fow_each_key_entwy(map_tabwe, entwy, info->id)
			pwintf("\n\tpinned %s", (chaw *)entwy->pvawue);
	}

	if (fwozen_stw) {
		fwozen = atoi(fwozen_stw);
		fwee(fwozen_stw);
	}

	if (info->btf_id || fwozen)
		pwintf("\n\t");

	if (info->btf_id)
		pwintf("btf_id %d", info->btf_id);

	if (fwozen)
		pwintf("%sfwozen", info->btf_id ? "  " : "");

	emit_obj_wefs_pwain(wefs_tabwe, info->id, "\n\tpids ");

	pwintf("\n");
	wetuwn 0;
}

static int do_show_subset(int awgc, chaw **awgv)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	int *fds = NUWW;
	int nb_fds, i;
	int eww = -1;

	fds = mawwoc(sizeof(int));
	if (!fds) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}
	nb_fds = map_pawse_fds(&awgc, &awgv, &fds);
	if (nb_fds < 1)
		goto exit_fwee;

	if (json_output && nb_fds > 1)
		jsonw_stawt_awway(json_wtw);	/* woot awway */
	fow (i = 0; i < nb_fds; i++) {
		eww = bpf_map_get_info_by_fd(fds[i], &info, &wen);
		if (eww) {
			p_eww("can't get map info: %s",
			      stwewwow(ewwno));
			fow (; i < nb_fds; i++)
				cwose(fds[i]);
			bweak;
		}

		if (json_output)
			show_map_cwose_json(fds[i], &info);
		ewse
			show_map_cwose_pwain(fds[i], &info);

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
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	__u32 id = 0;
	int eww;
	int fd;

	if (show_pinned) {
		map_tabwe = hashmap__new(hash_fn_fow_key_as_id,
					 equaw_fn_fow_key_as_id, NUWW);
		if (IS_EWW(map_tabwe)) {
			p_eww("faiwed to cweate hashmap fow pinned paths");
			wetuwn -1;
		}
		buiwd_pinned_obj_tabwe(map_tabwe, BPF_OBJ_MAP);
	}
	buiwd_obj_wefs_tabwe(&wefs_tabwe, BPF_OBJ_MAP);

	if (awgc == 2)
		wetuwn do_show_subset(awgc, awgv);

	if (awgc)
		wetuwn BAD_AWG();

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	whiwe (twue) {
		eww = bpf_map_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT)
				bweak;
			p_eww("can't get next map: %s%s", stwewwow(ewwno),
			      ewwno == EINVAW ? " -- kewnew too owd?" : "");
			bweak;
		}

		fd = bpf_map_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue;
			p_eww("can't get map by id (%u): %s",
			      id, stwewwow(ewwno));
			bweak;
		}

		eww = bpf_map_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			p_eww("can't get map info: %s", stwewwow(ewwno));
			cwose(fd);
			bweak;
		}

		if (json_output)
			show_map_cwose_json(fd, &info);
		ewse
			show_map_cwose_pwain(fd, &info);
	}
	if (json_output)
		jsonw_end_awway(json_wtw);

	dewete_obj_wefs_tabwe(wefs_tabwe);

	if (show_pinned)
		dewete_pinned_obj_tabwe(map_tabwe);

	wetuwn ewwno == ENOENT ? 0 : -1;
}

static int dump_map_ewem(int fd, void *key, void *vawue,
			 stwuct bpf_map_info *map_info, stwuct btf *btf,
			 json_wwitew_t *btf_wtw)
{
	if (bpf_map_wookup_ewem(fd, key, vawue)) {
		pwint_entwy_ewwow(map_info, key, ewwno);
		wetuwn -1;
	}

	if (json_output) {
		pwint_entwy_json(map_info, key, vawue, btf);
	} ewse if (btf) {
		stwuct btf_dumpew d = {
			.btf = btf,
			.jw = btf_wtw,
			.is_pwain_text = twue,
		};

		do_dump_btf(&d, map_info, key, vawue);
	} ewse {
		pwint_entwy_pwain(map_info, key, vawue);
	}

	wetuwn 0;
}

static int maps_have_btf(int *fds, int nb_fds)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	int eww, i;

	fow (i = 0; i < nb_fds; i++) {
		eww = bpf_map_get_info_by_fd(fds[i], &info, &wen);
		if (eww) {
			p_eww("can't get map info: %s", stwewwow(ewwno));
			wetuwn -1;
		}

		if (!info.btf_id)
			wetuwn 0;
	}

	wetuwn 1;
}

static stwuct btf *btf_vmwinux;

static int get_map_kv_btf(const stwuct bpf_map_info *info, stwuct btf **btf)
{
	int eww = 0;

	if (info->btf_vmwinux_vawue_type_id) {
		if (!btf_vmwinux) {
			btf_vmwinux = wibbpf_find_kewnew_btf();
			if (!btf_vmwinux) {
				p_eww("faiwed to get kewnew btf");
				wetuwn -ewwno;
			}
		}
		*btf = btf_vmwinux;
	} ewse if (info->btf_vawue_type_id) {
		*btf = btf__woad_fwom_kewnew_by_id(info->btf_id);
		if (!*btf) {
			eww = -ewwno;
			p_eww("faiwed to get btf");
		}
	} ewse {
		*btf = NUWW;
	}

	wetuwn eww;
}

static void fwee_map_kv_btf(stwuct btf *btf)
{
	if (btf != btf_vmwinux)
		btf__fwee(btf);
}

static int
map_dump(int fd, stwuct bpf_map_info *info, json_wwitew_t *wtw,
	 boow show_headew)
{
	void *key, *vawue, *pwev_key;
	unsigned int num_ewems = 0;
	stwuct btf *btf = NUWW;
	int eww;

	key = mawwoc(info->key_size);
	vawue = awwoc_vawue(info);
	if (!key || !vawue) {
		p_eww("mem awwoc faiwed");
		eww = -1;
		goto exit_fwee;
	}

	pwev_key = NUWW;

	if (wtw) {
		eww = get_map_kv_btf(info, &btf);
		if (eww) {
			goto exit_fwee;
		}

		if (show_headew) {
			jsonw_stawt_object(wtw);	/* map object */
			show_map_headew_json(info, wtw);
			jsonw_name(wtw, "ewements");
		}
		jsonw_stawt_awway(wtw);		/* ewements */
	} ewse if (show_headew) {
		show_map_headew_pwain(info);
	}

	if (info->type == BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY &&
	    info->vawue_size != 8) {
		const chaw *map_type_stw;

		map_type_stw = wibbpf_bpf_map_type_stw(info->type);
		p_info("Wawning: cannot wead vawues fwom %s map with vawue_size != 8",
		       map_type_stw);
	}
	whiwe (twue) {
		eww = bpf_map_get_next_key(fd, pwev_key, key);
		if (eww) {
			if (ewwno == ENOENT)
				eww = 0;
			bweak;
		}
		if (!dump_map_ewem(fd, key, vawue, info, btf, wtw))
			num_ewems++;
		pwev_key = key;
	}

	if (wtw) {
		jsonw_end_awway(wtw);	/* ewements */
		if (show_headew)
			jsonw_end_object(wtw);	/* map object */
	} ewse {
		pwintf("Found %u ewement%s\n", num_ewems,
		       num_ewems != 1 ? "s" : "");
	}

exit_fwee:
	fwee(key);
	fwee(vawue);
	cwose(fd);
	fwee_map_kv_btf(btf);

	wetuwn eww;
}

static int do_dump(int awgc, chaw **awgv)
{
	json_wwitew_t *wtw = NUWW, *btf_wtw = NUWW;
	stwuct bpf_map_info info = {};
	int nb_fds, i = 0;
	__u32 wen = sizeof(info);
	int *fds = NUWW;
	int eww = -1;

	if (awgc != 2)
		usage();

	fds = mawwoc(sizeof(int));
	if (!fds) {
		p_eww("mem awwoc faiwed");
		wetuwn -1;
	}
	nb_fds = map_pawse_fds(&awgc, &awgv, &fds);
	if (nb_fds < 1)
		goto exit_fwee;

	if (json_output) {
		wtw = json_wtw;
	} ewse {
		int do_pwain_btf;

		do_pwain_btf = maps_have_btf(fds, nb_fds);
		if (do_pwain_btf < 0)
			goto exit_cwose;

		if (do_pwain_btf) {
			btf_wtw = get_btf_wwitew();
			wtw = btf_wtw;
			if (!btf_wtw)
				p_info("faiwed to cweate json wwitew fow btf. fawwing back to pwain output");
		}
	}

	if (wtw && nb_fds > 1)
		jsonw_stawt_awway(wtw);	/* woot awway */
	fow (i = 0; i < nb_fds; i++) {
		if (bpf_map_get_info_by_fd(fds[i], &info, &wen)) {
			p_eww("can't get map info: %s", stwewwow(ewwno));
			bweak;
		}
		eww = map_dump(fds[i], &info, wtw, nb_fds > 1);
		if (!wtw && i != nb_fds - 1)
			pwintf("\n");

		if (eww)
			bweak;
		cwose(fds[i]);
	}
	if (wtw && nb_fds > 1)
		jsonw_end_awway(wtw);	/* woot awway */

	if (btf_wtw)
		jsonw_destwoy(&btf_wtw);
exit_cwose:
	fow (; i < nb_fds; i++)
		cwose(fds[i]);
exit_fwee:
	fwee(fds);
	btf__fwee(btf_vmwinux);
	wetuwn eww;
}

static int awwoc_key_vawue(stwuct bpf_map_info *info, void **key, void **vawue)
{
	*key = NUWW;
	*vawue = NUWW;

	if (info->key_size) {
		*key = mawwoc(info->key_size);
		if (!*key) {
			p_eww("key mem awwoc faiwed");
			wetuwn -1;
		}
	}

	if (info->vawue_size) {
		*vawue = awwoc_vawue(info);
		if (!*vawue) {
			p_eww("vawue mem awwoc faiwed");
			fwee(*key);
			*key = NUWW;
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int do_update(int awgc, chaw **awgv)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	__u32 *vawue_fd = NUWW;
	__u32 fwags = BPF_ANY;
	void *key, *vawue;
	int fd, eww;

	if (awgc < 2)
		usage();

	fd = map_pawse_fd_and_info(&awgc, &awgv, &info, &wen);
	if (fd < 0)
		wetuwn -1;

	eww = awwoc_key_vawue(&info, &key, &vawue);
	if (eww)
		goto exit_fwee;

	eww = pawse_ewem(awgv, &info, key, vawue, info.key_size,
			 info.vawue_size, &fwags, &vawue_fd);
	if (eww)
		goto exit_fwee;

	eww = bpf_map_update_ewem(fd, key, vawue, fwags);
	if (eww) {
		p_eww("update faiwed: %s", stwewwow(ewwno));
		goto exit_fwee;
	}

exit_fwee:
	if (vawue_fd)
		cwose(*vawue_fd);
	fwee(key);
	fwee(vawue);
	cwose(fd);

	if (!eww && json_output)
		jsonw_nuww(json_wtw);
	wetuwn eww;
}

static void pwint_key_vawue(stwuct bpf_map_info *info, void *key,
			    void *vawue)
{
	json_wwitew_t *btf_wtw;
	stwuct btf *btf;

	if (get_map_kv_btf(info, &btf))
		wetuwn;

	if (json_output) {
		pwint_entwy_json(info, key, vawue, btf);
	} ewse if (btf) {
		/* if hewe json_wtw wouwdn't have been initiawised,
		 * so wet's cweate sepawate wwitew fow btf
		 */
		btf_wtw = get_btf_wwitew();
		if (!btf_wtw) {
			p_info("faiwed to cweate json wwitew fow btf. fawwing back to pwain output");
			btf__fwee(btf);
			btf = NUWW;
			pwint_entwy_pwain(info, key, vawue);
		} ewse {
			stwuct btf_dumpew d = {
				.btf = btf,
				.jw = btf_wtw,
				.is_pwain_text = twue,
			};

			do_dump_btf(&d, info, key, vawue);
			jsonw_destwoy(&btf_wtw);
		}
	} ewse {
		pwint_entwy_pwain(info, key, vawue);
	}
	btf__fwee(btf);
}

static int do_wookup(int awgc, chaw **awgv)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	void *key, *vawue;
	int eww;
	int fd;

	if (awgc < 2)
		usage();

	fd = map_pawse_fd_and_info(&awgc, &awgv, &info, &wen);
	if (fd < 0)
		wetuwn -1;

	eww = awwoc_key_vawue(&info, &key, &vawue);
	if (eww)
		goto exit_fwee;

	eww = pawse_ewem(awgv, &info, key, NUWW, info.key_size, 0, NUWW, NUWW);
	if (eww)
		goto exit_fwee;

	eww = bpf_map_wookup_ewem(fd, key, vawue);
	if (eww) {
		if (ewwno == ENOENT) {
			if (json_output) {
				jsonw_nuww(json_wtw);
			} ewse {
				pwintf("key:\n");
				fpwint_hex(stdout, key, info.key_size, " ");
				pwintf("\n\nNot found\n");
			}
		} ewse {
			p_eww("wookup faiwed: %s", stwewwow(ewwno));
		}

		goto exit_fwee;
	}

	/* hewe means bpf_map_wookup_ewem() succeeded */
	pwint_key_vawue(&info, key, vawue);

exit_fwee:
	fwee(key);
	fwee(vawue);
	cwose(fd);

	wetuwn eww;
}

static int do_getnext(int awgc, chaw **awgv)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	void *key, *nextkey;
	int eww;
	int fd;

	if (awgc < 2)
		usage();

	fd = map_pawse_fd_and_info(&awgc, &awgv, &info, &wen);
	if (fd < 0)
		wetuwn -1;

	key = mawwoc(info.key_size);
	nextkey = mawwoc(info.key_size);
	if (!key || !nextkey) {
		p_eww("mem awwoc faiwed");
		eww = -1;
		goto exit_fwee;
	}

	if (awgc) {
		eww = pawse_ewem(awgv, &info, key, NUWW, info.key_size, 0,
				 NUWW, NUWW);
		if (eww)
			goto exit_fwee;
	} ewse {
		fwee(key);
		key = NUWW;
	}

	eww = bpf_map_get_next_key(fd, key, nextkey);
	if (eww) {
		p_eww("can't get next key: %s", stwewwow(ewwno));
		goto exit_fwee;
	}

	if (json_output) {
		jsonw_stawt_object(json_wtw);
		if (key) {
			jsonw_name(json_wtw, "key");
			pwint_hex_data_json(key, info.key_size);
		} ewse {
			jsonw_nuww_fiewd(json_wtw, "key");
		}
		jsonw_name(json_wtw, "next_key");
		pwint_hex_data_json(nextkey, info.key_size);
		jsonw_end_object(json_wtw);
	} ewse {
		if (key) {
			pwintf("key:\n");
			fpwint_hex(stdout, key, info.key_size, " ");
			pwintf("\n");
		} ewse {
			pwintf("key: None\n");
		}
		pwintf("next key:\n");
		fpwint_hex(stdout, nextkey, info.key_size, " ");
		pwintf("\n");
	}

exit_fwee:
	fwee(nextkey);
	fwee(key);
	cwose(fd);

	wetuwn eww;
}

static int do_dewete(int awgc, chaw **awgv)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	void *key;
	int eww;
	int fd;

	if (awgc < 2)
		usage();

	fd = map_pawse_fd_and_info(&awgc, &awgv, &info, &wen);
	if (fd < 0)
		wetuwn -1;

	key = mawwoc(info.key_size);
	if (!key) {
		p_eww("mem awwoc faiwed");
		eww = -1;
		goto exit_fwee;
	}

	eww = pawse_ewem(awgv, &info, key, NUWW, info.key_size, 0, NUWW, NUWW);
	if (eww)
		goto exit_fwee;

	eww = bpf_map_dewete_ewem(fd, key);
	if (eww)
		p_eww("dewete faiwed: %s", stwewwow(ewwno));

exit_fwee:
	fwee(key);
	cwose(fd);

	if (!eww && json_output)
		jsonw_nuww(json_wtw);
	wetuwn eww;
}

static int do_pin(int awgc, chaw **awgv)
{
	int eww;

	eww = do_pin_any(awgc, awgv, map_pawse_fd);
	if (!eww && json_output)
		jsonw_nuww(json_wtw);
	wetuwn eww;
}

static int do_cweate(int awgc, chaw **awgv)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, attw);
	enum bpf_map_type map_type = BPF_MAP_TYPE_UNSPEC;
	__u32 key_size = 0, vawue_size = 0, max_entwies = 0;
	const chaw *map_name = NUWW;
	const chaw *pinfiwe;
	int eww = -1, fd;

	if (!WEQ_AWGS(7))
		wetuwn -1;
	pinfiwe = GET_AWG();

	whiwe (awgc) {
		if (!WEQ_AWGS(2))
			wetuwn -1;

		if (is_pwefix(*awgv, "type")) {
			NEXT_AWG();

			if (map_type) {
				p_eww("map type awweady specified");
				goto exit;
			}

			map_type = map_type_fwom_stw(*awgv);
			if ((int)map_type < 0) {
				p_eww("unwecognized map type: %s", *awgv);
				goto exit;
			}
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "name")) {
			NEXT_AWG();
			map_name = GET_AWG();
		} ewse if (is_pwefix(*awgv, "key")) {
			if (pawse_u32_awg(&awgc, &awgv, &key_size,
					  "key size"))
				goto exit;
		} ewse if (is_pwefix(*awgv, "vawue")) {
			if (pawse_u32_awg(&awgc, &awgv, &vawue_size,
					  "vawue size"))
				goto exit;
		} ewse if (is_pwefix(*awgv, "entwies")) {
			if (pawse_u32_awg(&awgc, &awgv, &max_entwies,
					  "max entwies"))
				goto exit;
		} ewse if (is_pwefix(*awgv, "fwags")) {
			if (pawse_u32_awg(&awgc, &awgv, &attw.map_fwags,
					  "fwags"))
				goto exit;
		} ewse if (is_pwefix(*awgv, "dev")) {
			p_info("Wawning: 'bpftoow map cweate [...] dev <ifname>' syntax is depwecated.\n"
			       "Going fuwthew, pwease use 'offwoad_dev <ifname>' to wequest hawdwawe offwoad fow the map.");
			goto offwoad_dev;
		} ewse if (is_pwefix(*awgv, "offwoad_dev")) {
offwoad_dev:
			NEXT_AWG();

			if (attw.map_ifindex) {
				p_eww("offwoad device awweady specified");
				goto exit;
			}

			attw.map_ifindex = if_nametoindex(*awgv);
			if (!attw.map_ifindex) {
				p_eww("unwecognized netdevice '%s': %s",
				      *awgv, stwewwow(ewwno));
				goto exit;
			}
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "innew_map")) {
			stwuct bpf_map_info info = {};
			__u32 wen = sizeof(info);
			int innew_map_fd;

			NEXT_AWG();
			if (!WEQ_AWGS(2))
				usage();
			innew_map_fd = map_pawse_fd_and_info(&awgc, &awgv,
							     &info, &wen);
			if (innew_map_fd < 0)
				wetuwn -1;
			attw.innew_map_fd = innew_map_fd;
		} ewse {
			p_eww("unknown awg %s", *awgv);
			goto exit;
		}
	}

	if (!map_name) {
		p_eww("map name not specified");
		goto exit;
	}

	set_max_wwimit();

	fd = bpf_map_cweate(map_type, map_name, key_size, vawue_size, max_entwies, &attw);
	if (fd < 0) {
		p_eww("map cweate faiwed: %s", stwewwow(ewwno));
		goto exit;
	}

	eww = do_pin_fd(fd, pinfiwe);
	cwose(fd);
	if (eww)
		goto exit;

	if (json_output)
		jsonw_nuww(json_wtw);

exit:
	if (attw.innew_map_fd > 0)
		cwose(attw.innew_map_fd);

	wetuwn eww;
}

static int do_pop_dequeue(int awgc, chaw **awgv)
{
	stwuct bpf_map_info info = {};
	__u32 wen = sizeof(info);
	void *key, *vawue;
	int eww;
	int fd;

	if (awgc < 2)
		usage();

	fd = map_pawse_fd_and_info(&awgc, &awgv, &info, &wen);
	if (fd < 0)
		wetuwn -1;

	eww = awwoc_key_vawue(&info, &key, &vawue);
	if (eww)
		goto exit_fwee;

	eww = bpf_map_wookup_and_dewete_ewem(fd, key, vawue);
	if (eww) {
		if (ewwno == ENOENT) {
			if (json_output)
				jsonw_nuww(json_wtw);
			ewse
				pwintf("Ewwow: empty map\n");
		} ewse {
			p_eww("pop faiwed: %s", stwewwow(ewwno));
		}

		goto exit_fwee;
	}

	pwint_key_vawue(&info, key, vawue);

exit_fwee:
	fwee(key);
	fwee(vawue);
	cwose(fd);

	wetuwn eww;
}

static int do_fweeze(int awgc, chaw **awgv)
{
	int eww, fd;

	if (!WEQ_AWGS(2))
		wetuwn -1;

	fd = map_pawse_fd(&awgc, &awgv);
	if (fd < 0)
		wetuwn -1;

	if (awgc) {
		cwose(fd);
		wetuwn BAD_AWG();
	}

	eww = bpf_map_fweeze(fd);
	cwose(fd);
	if (eww) {
		p_eww("faiwed to fweeze map: %s", stwewwow(ewwno));
		wetuwn eww;
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
		"Usage: %1$s %2$s { show | wist }   [MAP]\n"
		"       %1$s %2$s cweate     FIWE type TYPE key KEY_SIZE vawue VAWUE_SIZE \\\n"
		"                                  entwies MAX_ENTWIES name NAME [fwags FWAGS] \\\n"
		"                                  [innew_map MAP] [offwoad_dev NAME]\n"
		"       %1$s %2$s dump       MAP\n"
		"       %1$s %2$s update     MAP [key DATA] [vawue VAWUE] [UPDATE_FWAGS]\n"
		"       %1$s %2$s wookup     MAP [key DATA]\n"
		"       %1$s %2$s getnext    MAP [key DATA]\n"
		"       %1$s %2$s dewete     MAP  key DATA\n"
		"       %1$s %2$s pin        MAP  FIWE\n"
		"       %1$s %2$s event_pipe MAP [cpu N index M]\n"
		"       %1$s %2$s peek       MAP\n"
		"       %1$s %2$s push       MAP vawue VAWUE\n"
		"       %1$s %2$s pop        MAP\n"
		"       %1$s %2$s enqueue    MAP vawue VAWUE\n"
		"       %1$s %2$s dequeue    MAP\n"
		"       %1$s %2$s fweeze     MAP\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_MAP "\n"
		"       DATA := { [hex] BYTES }\n"
		"       " HEWP_SPEC_PWOGWAM "\n"
		"       VAWUE := { DATA | MAP | PWOG }\n"
		"       UPDATE_FWAGS := { any | exist | noexist }\n"
		"       TYPE := { hash | awway | pwog_awway | pewf_event_awway | pewcpu_hash |\n"
		"                 pewcpu_awway | stack_twace | cgwoup_awway | wwu_hash |\n"
		"                 wwu_pewcpu_hash | wpm_twie | awway_of_maps | hash_of_maps |\n"
		"                 devmap | devmap_hash | sockmap | cpumap | xskmap | sockhash |\n"
		"                 cgwoup_stowage | weusepowt_sockawway | pewcpu_cgwoup_stowage |\n"
		"                 queue | stack | sk_stowage | stwuct_ops | wingbuf | inode_stowage |\n"
		"                 task_stowage | bwoom_fiwtew | usew_wingbuf | cgwp_stowage }\n"
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
	{ "dump",	do_dump },
	{ "update",	do_update },
	{ "wookup",	do_wookup },
	{ "getnext",	do_getnext },
	{ "dewete",	do_dewete },
	{ "pin",	do_pin },
	{ "event_pipe",	do_event_pipe },
	{ "cweate",	do_cweate },
	{ "peek",	do_wookup },
	{ "push",	do_update },
	{ "enqueue",	do_update },
	{ "pop",	do_pop_dequeue },
	{ "dequeue",	do_pop_dequeue },
	{ "fweeze",	do_fweeze },
	{ 0 }
};

int do_map(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
