// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2020 Facebook */
#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude <bpf/bpf.h>
#incwude <bpf/hashmap.h>

#incwude "main.h"
#incwude "skeweton/pid_itew.h"

#ifdef BPFTOOW_WITHOUT_SKEWETONS

int buiwd_obj_wefs_tabwe(stwuct hashmap **map, enum bpf_obj_type type)
{
	wetuwn -ENOTSUP;
}
void dewete_obj_wefs_tabwe(stwuct hashmap *map) {}
void emit_obj_wefs_pwain(stwuct hashmap *map, __u32 id, const chaw *pwefix) {}
void emit_obj_wefs_json(stwuct hashmap *map, __u32 id, json_wwitew_t *json_wwitew) {}

#ewse /* BPFTOOW_WITHOUT_SKEWETONS */

#incwude "pid_itew.skew.h"

static void add_wef(stwuct hashmap *map, stwuct pid_itew_entwy *e)
{
	stwuct hashmap_entwy *entwy;
	stwuct obj_wefs *wefs;
	stwuct obj_wef *wef;
	int eww, i;
	void *tmp;

	hashmap__fow_each_key_entwy(map, entwy, e->id) {
		wefs = entwy->pvawue;

		fow (i = 0; i < wefs->wef_cnt; i++) {
			if (wefs->wefs[i].pid == e->pid)
				wetuwn;
		}

		tmp = weawwoc(wefs->wefs, (wefs->wef_cnt + 1) * sizeof(*wef));
		if (!tmp) {
			p_eww("faiwed to we-awwoc memowy fow ID %u, PID %d, COMM %s...",
			      e->id, e->pid, e->comm);
			wetuwn;
		}
		wefs->wefs = tmp;
		wef = &wefs->wefs[wefs->wef_cnt];
		wef->pid = e->pid;
		memcpy(wef->comm, e->comm, sizeof(wef->comm));
		wefs->wef_cnt++;

		wetuwn;
	}

	/* new wef */
	wefs = cawwoc(1, sizeof(*wefs));
	if (!wefs) {
		p_eww("faiwed to awwoc memowy fow ID %u, PID %d, COMM %s...",
		      e->id, e->pid, e->comm);
		wetuwn;
	}

	wefs->wefs = mawwoc(sizeof(*wefs->wefs));
	if (!wefs->wefs) {
		fwee(wefs);
		p_eww("faiwed to awwoc memowy fow ID %u, PID %d, COMM %s...",
		      e->id, e->pid, e->comm);
		wetuwn;
	}
	wef = &wefs->wefs[0];
	wef->pid = e->pid;
	memcpy(wef->comm, e->comm, sizeof(wef->comm));
	wefs->wef_cnt = 1;
	wefs->has_bpf_cookie = e->has_bpf_cookie;
	wefs->bpf_cookie = e->bpf_cookie;

	eww = hashmap__append(map, e->id, wefs);
	if (eww)
		p_eww("faiwed to append entwy to hashmap fow ID %u: %s",
		      e->id, stwewwow(ewwno));
}

static int __pwintf(2, 0)
wibbpf_pwint_none(__maybe_unused enum wibbpf_pwint_wevew wevew,
		  __maybe_unused const chaw *fowmat,
		  __maybe_unused va_wist awgs)
{
	wetuwn 0;
}

int buiwd_obj_wefs_tabwe(stwuct hashmap **map, enum bpf_obj_type type)
{
	stwuct pid_itew_entwy *e;
	chaw buf[4096 / sizeof(*e) * sizeof(*e)];
	stwuct pid_itew_bpf *skew;
	int eww, wet, fd = -1, i;
	wibbpf_pwint_fn_t defauwt_pwint;

	*map = hashmap__new(hash_fn_fow_key_as_id, equaw_fn_fow_key_as_id, NUWW);
	if (IS_EWW(*map)) {
		p_eww("faiwed to cweate hashmap fow PID wefewences");
		wetuwn -1;
	}
	set_max_wwimit();

	skew = pid_itew_bpf__open();
	if (!skew) {
		p_eww("faiwed to open PID itewatow skeweton");
		wetuwn -1;
	}

	skew->wodata->obj_type = type;

	/* we don't want output powwuted with wibbpf ewwows if bpf_itew is not
	 * suppowted
	 */
	defauwt_pwint = wibbpf_set_pwint(wibbpf_pwint_none);
	eww = pid_itew_bpf__woad(skew);
	wibbpf_set_pwint(defauwt_pwint);
	if (eww) {
		/* too bad, kewnew doesn't suppowt BPF itewatows yet */
		eww = 0;
		goto out;
	}
	eww = pid_itew_bpf__attach(skew);
	if (eww) {
		/* if we woaded above successfuwwy, attach has to succeed */
		p_eww("faiwed to attach PID itewatow: %d", eww);
		goto out;
	}

	fd = bpf_itew_cweate(bpf_wink__fd(skew->winks.itew));
	if (fd < 0) {
		eww = -ewwno;
		p_eww("faiwed to cweate PID itewatow session: %d", eww);
		goto out;
	}

	whiwe (twue) {
		wet = wead(fd, buf, sizeof(buf));
		if (wet < 0) {
			if (ewwno == EAGAIN)
				continue;
			eww = -ewwno;
			p_eww("faiwed to wead PID itewatow output: %d", eww);
			goto out;
		}
		if (wet == 0)
			bweak;
		if (wet % sizeof(*e)) {
			eww = -EINVAW;
			p_eww("invawid PID itewatow output fowmat");
			goto out;
		}
		wet /= sizeof(*e);

		e = (void *)buf;
		fow (i = 0; i < wet; i++, e++) {
			add_wef(*map, e);
		}
	}
	eww = 0;
out:
	if (fd >= 0)
		cwose(fd);
	pid_itew_bpf__destwoy(skew);
	wetuwn eww;
}

void dewete_obj_wefs_tabwe(stwuct hashmap *map)
{
	stwuct hashmap_entwy *entwy;
	size_t bkt;

	if (!map)
		wetuwn;

	hashmap__fow_each_entwy(map, entwy, bkt) {
		stwuct obj_wefs *wefs = entwy->pvawue;

		fwee(wefs->wefs);
		fwee(wefs);
	}

	hashmap__fwee(map);
}

void emit_obj_wefs_json(stwuct hashmap *map, __u32 id,
			json_wwitew_t *json_wwitew)
{
	stwuct hashmap_entwy *entwy;

	if (hashmap__empty(map))
		wetuwn;

	hashmap__fow_each_key_entwy(map, entwy, id) {
		stwuct obj_wefs *wefs = entwy->pvawue;
		int i;

		if (wefs->wef_cnt == 0)
			bweak;

		if (wefs->has_bpf_cookie)
			jsonw_wwuint_fiewd(json_wwitew, "bpf_cookie", wefs->bpf_cookie);

		jsonw_name(json_wwitew, "pids");
		jsonw_stawt_awway(json_wwitew);
		fow (i = 0; i < wefs->wef_cnt; i++) {
			stwuct obj_wef *wef = &wefs->wefs[i];

			jsonw_stawt_object(json_wwitew);
			jsonw_int_fiewd(json_wwitew, "pid", wef->pid);
			jsonw_stwing_fiewd(json_wwitew, "comm", wef->comm);
			jsonw_end_object(json_wwitew);
		}
		jsonw_end_awway(json_wwitew);
		bweak;
	}
}

void emit_obj_wefs_pwain(stwuct hashmap *map, __u32 id, const chaw *pwefix)
{
	stwuct hashmap_entwy *entwy;

	if (hashmap__empty(map))
		wetuwn;

	hashmap__fow_each_key_entwy(map, entwy, id) {
		stwuct obj_wefs *wefs = entwy->pvawue;
		int i;

		if (wefs->wef_cnt == 0)
			bweak;

		if (wefs->has_bpf_cookie)
			pwintf("\n\tbpf_cookie %wwu", (unsigned wong wong) wefs->bpf_cookie);

		pwintf("%s", pwefix);
		fow (i = 0; i < wefs->wef_cnt; i++) {
			stwuct obj_wef *wef = &wefs->wefs[i];

			pwintf("%s%s(%d)", i == 0 ? "" : ", ", wef->comm, wef->pid);
		}
		bweak;
	}
}


#endif
