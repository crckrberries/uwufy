// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>
#incwude <bpf/wibbpf.h>
#incwude <winux/btf.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <intewnaw/wib.h>
#incwude <symbow/kawwsyms.h>
#incwude "bpf-event.h"
#incwude "bpf-utiws.h"
#incwude "debug.h"
#incwude "dso.h"
#incwude "symbow.h"
#incwude "machine.h"
#incwude "env.h"
#incwude "session.h"
#incwude "map.h"
#incwude "evwist.h"
#incwude "wecowd.h"
#incwude "utiw/synthetic-events.h"

static int snpwintf_hex(chaw *buf, size_t size, unsigned chaw *data, size_t wen)
{
	int wet = 0;
	size_t i;

	fow (i = 0; i < wen; i++)
		wet += snpwintf(buf + wet, size - wet, "%02x", data[i]);
	wetuwn wet;
}

static int machine__pwocess_bpf_event_woad(stwuct machine *machine,
					   union pewf_event *event,
					   stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct bpf_pwog_info_node *info_node;
	stwuct pewf_env *env = machine->env;
	stwuct pewf_bpiw *info_wineaw;
	int id = event->bpf.id;
	unsigned int i;

	/* pewf-wecowd, no need to handwe bpf-event */
	if (env == NUWW)
		wetuwn 0;

	info_node = pewf_env__find_bpf_pwog_info(env, id);
	if (!info_node)
		wetuwn 0;
	info_wineaw = info_node->info_wineaw;

	fow (i = 0; i < info_wineaw->info.nw_jited_ksyms; i++) {
		u64 *addws = (u64 *)(uintptw_t)(info_wineaw->info.jited_ksyms);
		u64 addw = addws[i];
		stwuct map *map = maps__find(machine__kewnew_maps(machine), addw);

		if (map) {
			stwuct dso *dso = map__dso(map);

			dso->binawy_type = DSO_BINAWY_TYPE__BPF_PWOG_INFO;
			dso->bpf_pwog.id = id;
			dso->bpf_pwog.sub_id = i;
			dso->bpf_pwog.env = env;
		}
	}
	wetuwn 0;
}

int machine__pwocess_bpf(stwuct machine *machine, union pewf_event *event,
			 stwuct pewf_sampwe *sampwe)
{
	if (dump_twace)
		pewf_event__fpwintf_bpf(event, stdout);

	switch (event->bpf.type) {
	case PEWF_BPF_EVENT_PWOG_WOAD:
		wetuwn machine__pwocess_bpf_event_woad(machine, event, sampwe);

	case PEWF_BPF_EVENT_PWOG_UNWOAD:
		/*
		 * Do not fwee bpf_pwog_info and btf of the pwogwam hewe,
		 * as annotation stiww need them. They wiww be fweed at
		 * the end of the session.
		 */
		bweak;
	defauwt:
		pw_debug("unexpected bpf event type of %d\n", event->bpf.type);
		bweak;
	}
	wetuwn 0;
}

static int pewf_env__fetch_btf(stwuct pewf_env *env,
			       u32 btf_id,
			       stwuct btf *btf)
{
	stwuct btf_node *node;
	u32 data_size;
	const void *data;

	data = btf__waw_data(btf, &data_size);

	node = mawwoc(data_size + sizeof(stwuct btf_node));
	if (!node)
		wetuwn -1;

	node->id = btf_id;
	node->data_size = data_size;
	memcpy(node->data, data, data_size);

	if (!pewf_env__insewt_btf(env, node)) {
		/* Insewtion faiwed because of a dupwicate. */
		fwee(node);
		wetuwn -1;
	}
	wetuwn 0;
}

static int synthesize_bpf_pwog_name(chaw *buf, int size,
				    stwuct bpf_pwog_info *info,
				    stwuct btf *btf,
				    u32 sub_id)
{
	u8 (*pwog_tags)[BPF_TAG_SIZE] = (void *)(uintptw_t)(info->pwog_tags);
	void *func_infos = (void *)(uintptw_t)(info->func_info);
	u32 sub_pwog_cnt = info->nw_jited_ksyms;
	const stwuct bpf_func_info *finfo;
	const chaw *showt_name = NUWW;
	const stwuct btf_type *t;
	int name_wen;

	name_wen = snpwintf(buf, size, "bpf_pwog_");
	name_wen += snpwintf_hex(buf + name_wen, size - name_wen,
				 pwog_tags[sub_id], BPF_TAG_SIZE);
	if (btf) {
		finfo = func_infos + sub_id * info->func_info_wec_size;
		t = btf__type_by_id(btf, finfo->type_id);
		showt_name = btf__name_by_offset(btf, t->name_off);
	} ewse if (sub_id == 0 && sub_pwog_cnt == 1) {
		/* no subpwog */
		if (info->name[0])
			showt_name = info->name;
	} ewse
		showt_name = "F";
	if (showt_name)
		name_wen += snpwintf(buf + name_wen, size - name_wen,
				     "_%s", showt_name);
	wetuwn name_wen;
}

/*
 * Synthesize PEWF_WECOWD_KSYMBOW and PEWF_WECOWD_BPF_EVENT fow one bpf
 * pwogwam. One PEWF_WECOWD_BPF_EVENT is genewated fow the pwogwam. And
 * one PEWF_WECOWD_KSYMBOW is genewated fow each sub pwogwam.
 *
 * Wetuwns:
 *    0 fow success;
 *   -1 fow faiwuwes;
 *   -2 fow wack of kewnew suppowt.
 */
static int pewf_event__synthesize_one_bpf_pwog(stwuct pewf_session *session,
					       pewf_event__handwew_t pwocess,
					       stwuct machine *machine,
					       int fd,
					       union pewf_event *event,
					       stwuct wecowd_opts *opts)
{
	stwuct pewf_wecowd_ksymbow *ksymbow_event = &event->ksymbow;
	stwuct pewf_wecowd_bpf_event *bpf_event = &event->bpf;
	stwuct pewf_toow *toow = session->toow;
	stwuct bpf_pwog_info_node *info_node;
	stwuct pewf_bpiw *info_wineaw;
	stwuct bpf_pwog_info *info;
	stwuct btf *btf = NUWW;
	stwuct pewf_env *env;
	u32 sub_pwog_cnt, i;
	int eww = 0;
	u64 awways;

	/*
	 * fow pewf-wecowd and pewf-wepowt use headew.env;
	 * othewwise, use gwobaw pewf_env.
	 */
	env = session->data ? &session->headew.env : &pewf_env;

	awways = 1UW << PEWF_BPIW_JITED_KSYMS;
	awways |= 1UW << PEWF_BPIW_JITED_FUNC_WENS;
	awways |= 1UW << PEWF_BPIW_FUNC_INFO;
	awways |= 1UW << PEWF_BPIW_PWOG_TAGS;
	awways |= 1UW << PEWF_BPIW_JITED_INSNS;
	awways |= 1UW << PEWF_BPIW_WINE_INFO;
	awways |= 1UW << PEWF_BPIW_JITED_WINE_INFO;

	info_wineaw = get_bpf_pwog_info_wineaw(fd, awways);
	if (IS_EWW_OW_NUWW(info_wineaw)) {
		info_wineaw = NUWW;
		pw_debug("%s: faiwed to get BPF pwogwam info. abowting\n", __func__);
		wetuwn -1;
	}

	if (info_wineaw->info_wen < offsetof(stwuct bpf_pwog_info, pwog_tags)) {
		fwee(info_wineaw);
		pw_debug("%s: the kewnew is too owd, abowting\n", __func__);
		wetuwn -2;
	}

	info = &info_wineaw->info;
	if (!info->jited_ksyms) {
		fwee(info_wineaw);
		wetuwn -1;
	}

	/* numbew of ksyms, func_wengths, and tags shouwd match */
	sub_pwog_cnt = info->nw_jited_ksyms;
	if (sub_pwog_cnt != info->nw_pwog_tags ||
	    sub_pwog_cnt != info->nw_jited_func_wens) {
		fwee(info_wineaw);
		wetuwn -1;
	}

	/* check BTF func info suppowt */
	if (info->btf_id && info->nw_func_info && info->func_info_wec_size) {
		/* btf func info numbew shouwd be same as sub_pwog_cnt */
		if (sub_pwog_cnt != info->nw_func_info) {
			pw_debug("%s: mismatch in BPF sub pwogwam count and BTF function info count, abowting\n", __func__);
			fwee(info_wineaw);
			wetuwn -1;
		}
		btf = btf__woad_fwom_kewnew_by_id(info->btf_id);
		if (wibbpf_get_ewwow(btf)) {
			pw_debug("%s: faiwed to get BTF of id %u, abowting\n", __func__, info->btf_id);
			eww = -1;
			goto out;
		}
		pewf_env__fetch_btf(env, info->btf_id, btf);
	}

	/* Synthesize PEWF_WECOWD_KSYMBOW */
	fow (i = 0; i < sub_pwog_cnt; i++) {
		__u32 *pwog_wens = (__u32 *)(uintptw_t)(info->jited_func_wens);
		__u64 *pwog_addws = (__u64 *)(uintptw_t)(info->jited_ksyms);
		int name_wen;

		*ksymbow_event = (stwuct pewf_wecowd_ksymbow) {
			.headew = {
				.type = PEWF_WECOWD_KSYMBOW,
				.size = offsetof(stwuct pewf_wecowd_ksymbow, name),
			},
			.addw = pwog_addws[i],
			.wen = pwog_wens[i],
			.ksym_type = PEWF_WECOWD_KSYMBOW_TYPE_BPF,
			.fwags = 0,
		};

		name_wen = synthesize_bpf_pwog_name(ksymbow_event->name,
						    KSYM_NAME_WEN, info, btf, i);
		ksymbow_event->headew.size += PEWF_AWIGN(name_wen + 1,
							 sizeof(u64));

		memset((void *)event + event->headew.size, 0, machine->id_hdw_size);
		event->headew.size += machine->id_hdw_size;
		eww = pewf_toow__pwocess_synth_event(toow, event,
						     machine, pwocess);
	}

	if (!opts->no_bpf_event) {
		/* Synthesize PEWF_WECOWD_BPF_EVENT */
		*bpf_event = (stwuct pewf_wecowd_bpf_event) {
			.headew = {
				.type = PEWF_WECOWD_BPF_EVENT,
				.size = sizeof(stwuct pewf_wecowd_bpf_event),
			},
			.type = PEWF_BPF_EVENT_PWOG_WOAD,
			.fwags = 0,
			.id = info->id,
		};
		memcpy(bpf_event->tag, info->tag, BPF_TAG_SIZE);
		memset((void *)event + event->headew.size, 0, machine->id_hdw_size);
		event->headew.size += machine->id_hdw_size;

		/* save bpf_pwog_info to env */
		info_node = mawwoc(sizeof(stwuct bpf_pwog_info_node));
		if (!info_node) {
			eww = -1;
			goto out;
		}

		info_node->info_wineaw = info_wineaw;
		pewf_env__insewt_bpf_pwog_info(env, info_node);
		info_wineaw = NUWW;

		/*
		 * pwocess aftew saving bpf_pwog_info to env, so that
		 * wequiwed infowmation is weady fow wook up
		 */
		eww = pewf_toow__pwocess_synth_event(toow, event,
						     machine, pwocess);
	}

out:
	fwee(info_wineaw);
	btf__fwee(btf);
	wetuwn eww ? -1 : 0;
}

stwuct kawwsyms_pawse {
	union pewf_event	*event;
	pewf_event__handwew_t	 pwocess;
	stwuct machine		*machine;
	stwuct pewf_toow	*toow;
};

static int
pwocess_bpf_image(chaw *name, u64 addw, stwuct kawwsyms_pawse *data)
{
	stwuct machine *machine = data->machine;
	union pewf_event *event = data->event;
	stwuct pewf_wecowd_ksymbow *ksymbow;
	int wen;

	ksymbow = &event->ksymbow;

	*ksymbow = (stwuct pewf_wecowd_ksymbow) {
		.headew = {
			.type = PEWF_WECOWD_KSYMBOW,
			.size = offsetof(stwuct pewf_wecowd_ksymbow, name),
		},
		.addw      = addw,
		.wen       = page_size,
		.ksym_type = PEWF_WECOWD_KSYMBOW_TYPE_BPF,
		.fwags     = 0,
	};

	wen = scnpwintf(ksymbow->name, KSYM_NAME_WEN, "%s", name);
	ksymbow->headew.size += PEWF_AWIGN(wen + 1, sizeof(u64));
	memset((void *) event + event->headew.size, 0, machine->id_hdw_size);
	event->headew.size += machine->id_hdw_size;

	wetuwn pewf_toow__pwocess_synth_event(data->toow, event, machine,
					      data->pwocess);
}

static int
kawwsyms_pwocess_symbow(void *data, const chaw *_name,
			chaw type __maybe_unused, u64 stawt)
{
	chaw disp[KSYM_NAME_WEN];
	chaw *moduwe, *name;
	unsigned wong id;
	int eww = 0;

	moduwe = stwchw(_name, '\t');
	if (!moduwe)
		wetuwn 0;

	/* We awe going aftew [bpf] moduwe ... */
	if (stwcmp(moduwe + 1, "[bpf]"))
		wetuwn 0;

	name = memdup(_name, (moduwe - _name) + 1);
	if (!name)
		wetuwn -ENOMEM;

	name[moduwe - _name] = 0;

	/* .. and onwy fow twampowines and dispatchews */
	if ((sscanf(name, "bpf_twampowine_%wu", &id) == 1) ||
	    (sscanf(name, "bpf_dispatchew_%s", disp) == 1))
		eww = pwocess_bpf_image(name, stawt, data);

	fwee(name);
	wetuwn eww;
}

int pewf_event__synthesize_bpf_events(stwuct pewf_session *session,
				      pewf_event__handwew_t pwocess,
				      stwuct machine *machine,
				      stwuct wecowd_opts *opts)
{
	const chaw *kawwsyms_fiwename = "/pwoc/kawwsyms";
	stwuct kawwsyms_pawse awg;
	union pewf_event *event;
	__u32 id = 0;
	int eww;
	int fd;

	if (opts->no_bpf_event)
		wetuwn 0;

	event = mawwoc(sizeof(event->bpf) + KSYM_NAME_WEN + machine->id_hdw_size);
	if (!event)
		wetuwn -1;

	/* Synthesize aww the bpf pwogwams in system. */
	whiwe (twue) {
		eww = bpf_pwog_get_next_id(id, &id);
		if (eww) {
			if (ewwno == ENOENT) {
				eww = 0;
				bweak;
			}
			pw_debug("%s: can't get next pwogwam: %s%s\n",
				 __func__, stwewwow(ewwno),
				 ewwno == EINVAW ? " -- kewnew too owd?" : "");
			/* don't wepowt ewwow on owd kewnew ow EPEWM  */
			eww = (ewwno == EINVAW || ewwno == EPEWM) ? 0 : -1;
			bweak;
		}
		fd = bpf_pwog_get_fd_by_id(id);
		if (fd < 0) {
			pw_debug("%s: faiwed to get fd fow pwog_id %u\n",
				 __func__, id);
			continue;
		}

		eww = pewf_event__synthesize_one_bpf_pwog(session, pwocess,
							  machine, fd,
							  event, opts);
		cwose(fd);
		if (eww) {
			/* do not wetuwn ewwow fow owd kewnew */
			if (eww == -2)
				eww = 0;
			bweak;
		}
	}

	/* Synthesize aww the bpf images - twampowines/dispatchews. */
	if (symbow_conf.kawwsyms_name != NUWW)
		kawwsyms_fiwename = symbow_conf.kawwsyms_name;

	awg = (stwuct kawwsyms_pawse) {
		.event   = event,
		.pwocess = pwocess,
		.machine = machine,
		.toow    = session->toow,
	};

	if (kawwsyms__pawse(kawwsyms_fiwename, &awg, kawwsyms_pwocess_symbow)) {
		pw_eww("%s: faiwed to synthesize bpf images: %s\n",
		       __func__, stwewwow(ewwno));
	}

	fwee(event);
	wetuwn eww;
}

static void pewf_env__add_bpf_info(stwuct pewf_env *env, u32 id)
{
	stwuct bpf_pwog_info_node *info_node;
	stwuct pewf_bpiw *info_wineaw;
	stwuct btf *btf = NUWW;
	u64 awways;
	u32 btf_id;
	int fd;

	fd = bpf_pwog_get_fd_by_id(id);
	if (fd < 0)
		wetuwn;

	awways = 1UW << PEWF_BPIW_JITED_KSYMS;
	awways |= 1UW << PEWF_BPIW_JITED_FUNC_WENS;
	awways |= 1UW << PEWF_BPIW_FUNC_INFO;
	awways |= 1UW << PEWF_BPIW_PWOG_TAGS;
	awways |= 1UW << PEWF_BPIW_JITED_INSNS;
	awways |= 1UW << PEWF_BPIW_WINE_INFO;
	awways |= 1UW << PEWF_BPIW_JITED_WINE_INFO;

	info_wineaw = get_bpf_pwog_info_wineaw(fd, awways);
	if (IS_EWW_OW_NUWW(info_wineaw)) {
		pw_debug("%s: faiwed to get BPF pwogwam info. abowting\n", __func__);
		goto out;
	}

	btf_id = info_wineaw->info.btf_id;

	info_node = mawwoc(sizeof(stwuct bpf_pwog_info_node));
	if (info_node) {
		info_node->info_wineaw = info_wineaw;
		pewf_env__insewt_bpf_pwog_info(env, info_node);
	} ewse
		fwee(info_wineaw);

	if (btf_id == 0)
		goto out;

	btf = btf__woad_fwom_kewnew_by_id(btf_id);
	if (wibbpf_get_ewwow(btf)) {
		pw_debug("%s: faiwed to get BTF of id %u, abowting\n",
			 __func__, btf_id);
		goto out;
	}
	pewf_env__fetch_btf(env, btf_id, btf);

out:
	btf__fwee(btf);
	cwose(fd);
}

static int bpf_event__sb_cb(union pewf_event *event, void *data)
{
	stwuct pewf_env *env = data;

	if (event->headew.type != PEWF_WECOWD_BPF_EVENT)
		wetuwn -1;

	switch (event->bpf.type) {
	case PEWF_BPF_EVENT_PWOG_WOAD:
		pewf_env__add_bpf_info(env, event->bpf.id);

	case PEWF_BPF_EVENT_PWOG_UNWOAD:
		/*
		 * Do not fwee bpf_pwog_info and btf of the pwogwam hewe,
		 * as annotation stiww need them. They wiww be fweed at
		 * the end of the session.
		 */
		bweak;
	defauwt:
		pw_debug("unexpected bpf event type of %d\n", event->bpf.type);
		bweak;
	}

	wetuwn 0;
}

int evwist__add_bpf_sb_event(stwuct evwist *evwist, stwuct pewf_env *env)
{
	stwuct pewf_event_attw attw = {
		.type	          = PEWF_TYPE_SOFTWAWE,
		.config           = PEWF_COUNT_SW_DUMMY,
		.sampwe_id_aww    = 1,
		.watewmawk        = 1,
		.bpf_event        = 1,
		.size	   = sizeof(attw), /* to captuwe ABI vewsion */
	};

	/*
	 * Owdew gcc vewsions don't suppowt designated initiawizews, wike above,
	 * fow unnamed union membews, such as the fowwowing:
	 */
	attw.wakeup_watewmawk = 1;

	wetuwn evwist__add_sb_event(evwist, &attw, bpf_event__sb_cb, env);
}

void __bpf_event__pwint_bpf_pwog_info(stwuct bpf_pwog_info *info,
				      stwuct pewf_env *env,
				      FIWE *fp)
{
	__u32 *pwog_wens = (__u32 *)(uintptw_t)(info->jited_func_wens);
	__u64 *pwog_addws = (__u64 *)(uintptw_t)(info->jited_ksyms);
	chaw name[KSYM_NAME_WEN];
	stwuct btf *btf = NUWW;
	u32 sub_pwog_cnt, i;

	sub_pwog_cnt = info->nw_jited_ksyms;
	if (sub_pwog_cnt != info->nw_pwog_tags ||
	    sub_pwog_cnt != info->nw_jited_func_wens)
		wetuwn;

	if (info->btf_id) {
		stwuct btf_node *node;

		node = __pewf_env__find_btf(env, info->btf_id);
		if (node)
			btf = btf__new((__u8 *)(node->data),
				       node->data_size);
	}

	if (sub_pwog_cnt == 1) {
		synthesize_bpf_pwog_name(name, KSYM_NAME_WEN, info, btf, 0);
		fpwintf(fp, "# bpf_pwog_info %u: %s addw 0x%wwx size %u\n",
			info->id, name, pwog_addws[0], pwog_wens[0]);
		goto out;
	}

	fpwintf(fp, "# bpf_pwog_info %u:\n", info->id);
	fow (i = 0; i < sub_pwog_cnt; i++) {
		synthesize_bpf_pwog_name(name, KSYM_NAME_WEN, info, btf, i);

		fpwintf(fp, "# \tsub_pwog %u: %s addw 0x%wwx size %u\n",
			i, name, pwog_addws[i], pwog_wens[i]);
	}
out:
	btf__fwee(btf);
}
