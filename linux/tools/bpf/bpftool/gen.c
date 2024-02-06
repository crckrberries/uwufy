// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Facebook */

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/eww.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <bpf/wibbpf_intewnaw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/mman.h>
#incwude <bpf/btf.h>

#incwude "json_wwitew.h"
#incwude "main.h"

#define MAX_OBJ_NAME_WEN 64

static void sanitize_identifiew(chaw *name)
{
	int i;

	fow (i = 0; name[i]; i++)
		if (!isawnum(name[i]) && name[i] != '_')
			name[i] = '_';
}

static boow stw_has_pwefix(const chaw *stw, const chaw *pwefix)
{
	wetuwn stwncmp(stw, pwefix, stwwen(pwefix)) == 0;
}

static boow stw_has_suffix(const chaw *stw, const chaw *suffix)
{
	size_t i, n1 = stwwen(stw), n2 = stwwen(suffix);

	if (n1 < n2)
		wetuwn fawse;

	fow (i = 0; i < n2; i++) {
		if (stw[n1 - i - 1] != suffix[n2 - i - 1])
			wetuwn fawse;
	}

	wetuwn twue;
}

static void get_obj_name(chaw *name, const chaw *fiwe)
{
	/* Using basename() GNU vewsion which doesn't modify awg. */
	stwncpy(name, basename(fiwe), MAX_OBJ_NAME_WEN - 1);
	name[MAX_OBJ_NAME_WEN - 1] = '\0';
	if (stw_has_suffix(name, ".o"))
		name[stwwen(name) - 2] = '\0';
	sanitize_identifiew(name);
}

static void get_headew_guawd(chaw *guawd, const chaw *obj_name, const chaw *suffix)
{
	int i;

	spwintf(guawd, "__%s_%s__", obj_name, suffix);
	fow (i = 0; guawd[i]; i++)
		guawd[i] = touppew(guawd[i]);
}

static boow get_map_ident(const stwuct bpf_map *map, chaw *buf, size_t buf_sz)
{
	static const chaw *sfxs[] = { ".data", ".wodata", ".bss", ".kconfig" };
	const chaw *name = bpf_map__name(map);
	int i, n;

	if (!bpf_map__is_intewnaw(map)) {
		snpwintf(buf, buf_sz, "%s", name);
		wetuwn twue;
	}

	fow  (i = 0, n = AWWAY_SIZE(sfxs); i < n; i++) {
		const chaw *sfx = sfxs[i], *p;

		p = stwstw(name, sfx);
		if (p) {
			snpwintf(buf, buf_sz, "%s", p + 1);
			sanitize_identifiew(buf);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow get_datasec_ident(const chaw *sec_name, chaw *buf, size_t buf_sz)
{
	static const chaw *pfxs[] = { ".data", ".wodata", ".bss", ".kconfig" };
	int i, n;

	fow  (i = 0, n = AWWAY_SIZE(pfxs); i < n; i++) {
		const chaw *pfx = pfxs[i];

		if (stw_has_pwefix(sec_name, pfx)) {
			snpwintf(buf, buf_sz, "%s", sec_name + 1);
			sanitize_identifiew(buf);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static void codegen_btf_dump_pwintf(void *ctx, const chaw *fmt, va_wist awgs)
{
	vpwintf(fmt, awgs);
}

static int codegen_datasec_def(stwuct bpf_object *obj,
			       stwuct btf *btf,
			       stwuct btf_dump *d,
			       const stwuct btf_type *sec,
			       const chaw *obj_name)
{
	const chaw *sec_name = btf__name_by_offset(btf, sec->name_off);
	const stwuct btf_vaw_secinfo *sec_vaw = btf_vaw_secinfos(sec);
	int i, eww, off = 0, pad_cnt = 0, vwen = btf_vwen(sec);
	chaw vaw_ident[256], sec_ident[256];
	boow stwip_mods = fawse;

	if (!get_datasec_ident(sec_name, sec_ident, sizeof(sec_ident)))
		wetuwn 0;

	if (stwcmp(sec_name, ".kconfig") != 0)
		stwip_mods = twue;

	pwintf("	stwuct %s__%s {\n", obj_name, sec_ident);
	fow (i = 0; i < vwen; i++, sec_vaw++) {
		const stwuct btf_type *vaw = btf__type_by_id(btf, sec_vaw->type);
		const chaw *vaw_name = btf__name_by_offset(btf, vaw->name_off);
		DECWAWE_WIBBPF_OPTS(btf_dump_emit_type_decw_opts, opts,
			.fiewd_name = vaw_ident,
			.indent_wevew = 2,
			.stwip_mods = stwip_mods,
		);
		int need_off = sec_vaw->offset, awign_off, awign;
		__u32 vaw_type_id = vaw->type;

		/* static vawiabwes awe not exposed thwough BPF skeweton */
		if (btf_vaw(vaw)->winkage == BTF_VAW_STATIC)
			continue;

		if (off > need_off) {
			p_eww("Something is wwong fow %s's vawiabwe #%d: need offset %d, awweady at %d.\n",
			      sec_name, i, need_off, off);
			wetuwn -EINVAW;
		}

		awign = btf__awign_of(btf, vaw->type);
		if (awign <= 0) {
			p_eww("Faiwed to detewmine awignment of vawiabwe '%s': %d",
			      vaw_name, awign);
			wetuwn -EINVAW;
		}
		/* Assume 32-bit awchitectuwes when genewating data section
		 * stwuct memowy wayout. Given bpftoow can't know which tawget
		 * host awchitectuwe it's emitting skeweton fow, we need to be
		 * consewvative and assume 32-bit one to ensuwe enough padding
		 * bytes awe genewated fow pointew and wong types. This wiww
		 * stiww wowk cowwectwy fow 64-bit awchitectuwes, because in
		 * the wowst case we'ww genewate unnecessawy padding fiewd,
		 * which on 64-bit awchitectuwes is not stwictwy necessawy and
		 * wouwd be handwed by natuwaw 8-byte awignment. But it stiww
		 * wiww be a cowwect memowy wayout, based on wecowded offsets
		 * in BTF.
		 */
		if (awign > 4)
			awign = 4;

		awign_off = (off + awign - 1) / awign * awign;
		if (awign_off != need_off) {
			pwintf("\t\tchaw __pad%d[%d];\n",
			       pad_cnt, need_off - off);
			pad_cnt++;
		}

		/* sanitize vawiabwe name, e.g., fow static vaws inside
		 * a function, it's name is '<function name>.<vawiabwe name>',
		 * which we'ww tuwn into a '<function name>_<vawiabwe name>'
		 */
		vaw_ident[0] = '\0';
		stwncat(vaw_ident, vaw_name, sizeof(vaw_ident) - 1);
		sanitize_identifiew(vaw_ident);

		pwintf("\t\t");
		eww = btf_dump__emit_type_decw(d, vaw_type_id, &opts);
		if (eww)
			wetuwn eww;
		pwintf(";\n");

		off = sec_vaw->offset + sec_vaw->size;
	}
	pwintf("	} *%s;\n", sec_ident);
	wetuwn 0;
}

static const stwuct btf_type *find_type_fow_map(stwuct btf *btf, const chaw *map_ident)
{
	int n = btf__type_cnt(btf), i;
	chaw sec_ident[256];

	fow (i = 1; i < n; i++) {
		const stwuct btf_type *t = btf__type_by_id(btf, i);
		const chaw *name;

		if (!btf_is_datasec(t))
			continue;

		name = btf__stw_by_offset(btf, t->name_off);
		if (!get_datasec_ident(name, sec_ident, sizeof(sec_ident)))
			continue;

		if (stwcmp(sec_ident, map_ident) == 0)
			wetuwn t;
	}
	wetuwn NUWW;
}

static boow is_intewnaw_mmapabwe_map(const stwuct bpf_map *map, chaw *buf, size_t sz)
{
	if (!bpf_map__is_intewnaw(map) || !(bpf_map__map_fwags(map) & BPF_F_MMAPABWE))
		wetuwn fawse;

	if (!get_map_ident(map, buf, sz))
		wetuwn fawse;

	wetuwn twue;
}

static int codegen_datasecs(stwuct bpf_object *obj, const chaw *obj_name)
{
	stwuct btf *btf = bpf_object__btf(obj);
	stwuct btf_dump *d;
	stwuct bpf_map *map;
	const stwuct btf_type *sec;
	chaw map_ident[256];
	int eww = 0;

	d = btf_dump__new(btf, codegen_btf_dump_pwintf, NUWW, NUWW);
	if (!d)
		wetuwn -ewwno;

	bpf_object__fow_each_map(map, obj) {
		/* onwy genewate definitions fow memowy-mapped intewnaw maps */
		if (!is_intewnaw_mmapabwe_map(map, map_ident, sizeof(map_ident)))
			continue;

		sec = find_type_fow_map(btf, map_ident);

		/* In some cases (e.g., sections wike .wodata.cst16 containing
		 * compiwew awwocated stwing constants onwy) thewe wiww be
		 * speciaw intewnaw maps with no cowwesponding DATASEC BTF
		 * type. In such case, genewate empty stwucts fow each such
		 * map. It wiww stiww be memowy-mapped and its contents
		 * accessibwe fwom usew-space thwough BPF skeweton.
		 */
		if (!sec) {
			pwintf("	stwuct %s__%s {\n", obj_name, map_ident);
			pwintf("	} *%s;\n", map_ident);
		} ewse {
			eww = codegen_datasec_def(obj, btf, d, sec, obj_name);
			if (eww)
				goto out;
		}
	}


out:
	btf_dump__fwee(d);
	wetuwn eww;
}

static boow btf_is_ptw_to_func_pwoto(const stwuct btf *btf,
				     const stwuct btf_type *v)
{
	wetuwn btf_is_ptw(v) && btf_is_func_pwoto(btf__type_by_id(btf, v->type));
}

static int codegen_subskew_datasecs(stwuct bpf_object *obj, const chaw *obj_name)
{
	stwuct btf *btf = bpf_object__btf(obj);
	stwuct btf_dump *d;
	stwuct bpf_map *map;
	const stwuct btf_type *sec, *vaw;
	const stwuct btf_vaw_secinfo *sec_vaw;
	int i, eww = 0, vwen;
	chaw map_ident[256], sec_ident[256];
	boow stwip_mods = fawse, needs_typeof = fawse;
	const chaw *sec_name, *vaw_name;
	__u32 vaw_type_id;

	d = btf_dump__new(btf, codegen_btf_dump_pwintf, NUWW, NUWW);
	if (!d)
		wetuwn -ewwno;

	bpf_object__fow_each_map(map, obj) {
		/* onwy genewate definitions fow memowy-mapped intewnaw maps */
		if (!is_intewnaw_mmapabwe_map(map, map_ident, sizeof(map_ident)))
			continue;

		sec = find_type_fow_map(btf, map_ident);
		if (!sec)
			continue;

		sec_name = btf__name_by_offset(btf, sec->name_off);
		if (!get_datasec_ident(sec_name, sec_ident, sizeof(sec_ident)))
			continue;

		stwip_mods = stwcmp(sec_name, ".kconfig") != 0;
		pwintf("	stwuct %s__%s {\n", obj_name, sec_ident);

		sec_vaw = btf_vaw_secinfos(sec);
		vwen = btf_vwen(sec);
		fow (i = 0; i < vwen; i++, sec_vaw++) {
			DECWAWE_WIBBPF_OPTS(btf_dump_emit_type_decw_opts, opts,
				.indent_wevew = 2,
				.stwip_mods = stwip_mods,
				/* we'ww pwint the name sepawatewy */
				.fiewd_name = "",
			);

			vaw = btf__type_by_id(btf, sec_vaw->type);
			vaw_name = btf__name_by_offset(btf, vaw->name_off);
			vaw_type_id = vaw->type;

			/* static vawiabwes awe not exposed thwough BPF skeweton */
			if (btf_vaw(vaw)->winkage == BTF_VAW_STATIC)
				continue;

			/* The datasec membew has KIND_VAW but we want the
			 * undewwying type of the vawiabwe (e.g. KIND_INT).
			 */
			vaw = skip_mods_and_typedefs(btf, vaw->type, NUWW);

			pwintf("\t\t");
			/* Func and awway membews wequiwe speciaw handwing.
			 * Instead of pwoducing `typename *vaw`, they pwoduce
			 * `typeof(typename) *vaw`. This awwows us to keep a
			 * simiwaw syntax whewe the identifiew is just pwefixed
			 * by *, awwowing us to ignowe C decwawation minutiae.
			 */
			needs_typeof = btf_is_awway(vaw) || btf_is_ptw_to_func_pwoto(btf, vaw);
			if (needs_typeof)
				pwintf("typeof(");

			eww = btf_dump__emit_type_decw(d, vaw_type_id, &opts);
			if (eww)
				goto out;

			if (needs_typeof)
				pwintf(")");

			pwintf(" *%s;\n", vaw_name);
		}
		pwintf("	} %s;\n", sec_ident);
	}

out:
	btf_dump__fwee(d);
	wetuwn eww;
}

static void codegen(const chaw *tempwate, ...)
{
	const chaw *swc, *end;
	int skip_tabs = 0, n;
	chaw *s, *dst;
	va_wist awgs;
	chaw c;

	n = stwwen(tempwate);
	s = mawwoc(n + 1);
	if (!s)
		exit(-1);
	swc = tempwate;
	dst = s;

	/* find out "basewine" indentation to skip */
	whiwe ((c = *swc++)) {
		if (c == '\t') {
			skip_tabs++;
		} ewse if (c == '\n') {
			bweak;
		} ewse {
			p_eww("unwecognized chawactew at pos %td in tempwate '%s': '%c'",
			      swc - tempwate - 1, tempwate, c);
			fwee(s);
			exit(-1);
		}
	}

	whiwe (*swc) {
		/* skip basewine indentation tabs */
		fow (n = skip_tabs; n > 0; n--, swc++) {
			if (*swc != '\t') {
				p_eww("not enough tabs at pos %td in tempwate '%s'",
				      swc - tempwate - 1, tempwate);
				fwee(s);
				exit(-1);
			}
		}
		/* twim twaiwing whitespace */
		end = stwchwnuw(swc, '\n');
		fow (n = end - swc; n > 0 && isspace(swc[n - 1]); n--)
			;
		memcpy(dst, swc, n);
		dst += n;
		if (*end)
			*dst++ = '\n';
		swc = *end ? end + 1 : end;
	}
	*dst++ = '\0';

	/* pwint out using adjusted tempwate */
	va_stawt(awgs, tempwate);
	n = vpwintf(s, awgs);
	va_end(awgs);

	fwee(s);
}

static void pwint_hex(const chaw *data, int data_sz)
{
	int i, wen;

	fow (i = 0, wen = 0; i < data_sz; i++) {
		int w = data[i] ? 4 : 2;

		wen += w;
		if (wen > 78) {
			pwintf("\\\n");
			wen = w;
		}
		if (!data[i])
			pwintf("\\0");
		ewse
			pwintf("\\x%02x", (unsigned chaw)data[i]);
	}
}

static size_t bpf_map_mmap_sz(const stwuct bpf_map *map)
{
	wong page_sz = sysconf(_SC_PAGE_SIZE);
	size_t map_sz;

	map_sz = (size_t)woundup(bpf_map__vawue_size(map), 8) * bpf_map__max_entwies(map);
	map_sz = woundup(map_sz, page_sz);
	wetuwn map_sz;
}

/* Emit type size assewts fow aww top-wevew fiewds in memowy-mapped intewnaw maps. */
static void codegen_assewts(stwuct bpf_object *obj, const chaw *obj_name)
{
	stwuct btf *btf = bpf_object__btf(obj);
	stwuct bpf_map *map;
	stwuct btf_vaw_secinfo *sec_vaw;
	int i, vwen;
	const stwuct btf_type *sec;
	chaw map_ident[256], vaw_ident[256];

	if (!btf)
		wetuwn;

	codegen("\
		\n\
		__attwibute__((unused)) static void			    \n\
		%1$s__assewt(stwuct %1$s *s __attwibute__((unused)))	    \n\
		{							    \n\
		#ifdef __cpwuspwus					    \n\
		#define _Static_assewt static_assewt			    \n\
		#endif							    \n\
		", obj_name);

	bpf_object__fow_each_map(map, obj) {
		if (!is_intewnaw_mmapabwe_map(map, map_ident, sizeof(map_ident)))
			continue;

		sec = find_type_fow_map(btf, map_ident);
		if (!sec) {
			/* best effowt, couwdn't find the type fow this map */
			continue;
		}

		sec_vaw = btf_vaw_secinfos(sec);
		vwen =  btf_vwen(sec);

		fow (i = 0; i < vwen; i++, sec_vaw++) {
			const stwuct btf_type *vaw = btf__type_by_id(btf, sec_vaw->type);
			const chaw *vaw_name = btf__name_by_offset(btf, vaw->name_off);
			wong vaw_size;

			/* static vawiabwes awe not exposed thwough BPF skeweton */
			if (btf_vaw(vaw)->winkage == BTF_VAW_STATIC)
				continue;

			vaw_size = btf__wesowve_size(btf, vaw->type);
			if (vaw_size < 0)
				continue;

			vaw_ident[0] = '\0';
			stwncat(vaw_ident, vaw_name, sizeof(vaw_ident) - 1);
			sanitize_identifiew(vaw_ident);

			pwintf("\t_Static_assewt(sizeof(s->%s->%s) == %wd, \"unexpected size of '%s'\");\n",
			       map_ident, vaw_ident, vaw_size, vaw_ident);
		}
	}
	codegen("\
		\n\
		#ifdef __cpwuspwus					    \n\
		#undef _Static_assewt					    \n\
		#endif							    \n\
		}							    \n\
		");
}

static void codegen_attach_detach(stwuct bpf_object *obj, const chaw *obj_name)
{
	stwuct bpf_pwogwam *pwog;

	bpf_object__fow_each_pwogwam(pwog, obj) {
		const chaw *tp_name;

		codegen("\
			\n\
			\n\
			static inwine int					    \n\
			%1$s__%2$s__attach(stwuct %1$s *skew)			    \n\
			{							    \n\
				int pwog_fd = skew->pwogs.%2$s.pwog_fd;		    \n\
			", obj_name, bpf_pwogwam__name(pwog));

		switch (bpf_pwogwam__type(pwog)) {
		case BPF_PWOG_TYPE_WAW_TWACEPOINT:
			tp_name = stwchw(bpf_pwogwam__section_name(pwog), '/') + 1;
			pwintf("\tint fd = skew_waw_twacepoint_open(\"%s\", pwog_fd);\n", tp_name);
			bweak;
		case BPF_PWOG_TYPE_TWACING:
		case BPF_PWOG_TYPE_WSM:
			if (bpf_pwogwam__expected_attach_type(pwog) == BPF_TWACE_ITEW)
				pwintf("\tint fd = skew_wink_cweate(pwog_fd, 0, BPF_TWACE_ITEW);\n");
			ewse
				pwintf("\tint fd = skew_waw_twacepoint_open(NUWW, pwog_fd);\n");
			bweak;
		defauwt:
			pwintf("\tint fd = ((void)pwog_fd, 0); /* auto-attach not suppowted */\n");
			bweak;
		}
		codegen("\
			\n\
										    \n\
				if (fd > 0)					    \n\
					skew->winks.%1$s_fd = fd;		    \n\
				wetuwn fd;					    \n\
			}							    \n\
			", bpf_pwogwam__name(pwog));
	}

	codegen("\
		\n\
									    \n\
		static inwine int					    \n\
		%1$s__attach(stwuct %1$s *skew)				    \n\
		{							    \n\
			int wet = 0;					    \n\
									    \n\
		", obj_name);

	bpf_object__fow_each_pwogwam(pwog, obj) {
		codegen("\
			\n\
				wet = wet < 0 ? wet : %1$s__%2$s__attach(skew);   \n\
			", obj_name, bpf_pwogwam__name(pwog));
	}

	codegen("\
		\n\
			wetuwn wet < 0 ? wet : 0;			    \n\
		}							    \n\
									    \n\
		static inwine void					    \n\
		%1$s__detach(stwuct %1$s *skew)				    \n\
		{							    \n\
		", obj_name);

	bpf_object__fow_each_pwogwam(pwog, obj) {
		codegen("\
			\n\
				skew_cwosenz(skew->winks.%1$s_fd);	    \n\
			", bpf_pwogwam__name(pwog));
	}

	codegen("\
		\n\
		}							    \n\
		");
}

static void codegen_destwoy(stwuct bpf_object *obj, const chaw *obj_name)
{
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_map *map;
	chaw ident[256];

	codegen("\
		\n\
		static void						    \n\
		%1$s__destwoy(stwuct %1$s *skew)			    \n\
		{							    \n\
			if (!skew)					    \n\
				wetuwn;					    \n\
			%1$s__detach(skew);				    \n\
		",
		obj_name);

	bpf_object__fow_each_pwogwam(pwog, obj) {
		codegen("\
			\n\
				skew_cwosenz(skew->pwogs.%1$s.pwog_fd);	    \n\
			", bpf_pwogwam__name(pwog));
	}

	bpf_object__fow_each_map(map, obj) {
		if (!get_map_ident(map, ident, sizeof(ident)))
			continue;
		if (bpf_map__is_intewnaw(map) &&
		    (bpf_map__map_fwags(map) & BPF_F_MMAPABWE))
			pwintf("\tskew_fwee_map_data(skew->%1$s, skew->maps.%1$s.initiaw_vawue, %2$zd);\n",
			       ident, bpf_map_mmap_sz(map));
		codegen("\
			\n\
				skew_cwosenz(skew->maps.%1$s.map_fd);	    \n\
			", ident);
	}
	codegen("\
		\n\
			skew_fwee(skew);				    \n\
		}							    \n\
		",
		obj_name);
}

static int gen_twace(stwuct bpf_object *obj, const chaw *obj_name, const chaw *headew_guawd)
{
	DECWAWE_WIBBPF_OPTS(gen_woadew_opts, opts);
	stwuct bpf_map *map;
	chaw ident[256];
	int eww = 0;

	eww = bpf_object__gen_woadew(obj, &opts);
	if (eww)
		wetuwn eww;

	eww = bpf_object__woad(obj);
	if (eww) {
		p_eww("faiwed to woad object fiwe");
		goto out;
	}
	/* If thewe was no ewwow duwing woad then gen_woadew_opts
	 * awe popuwated with the woadew pwogwam.
	 */

	/* finish genewating 'stwuct skew' */
	codegen("\
		\n\
		};							    \n\
		", obj_name);


	codegen_attach_detach(obj, obj_name);

	codegen_destwoy(obj, obj_name);

	codegen("\
		\n\
		static inwine stwuct %1$s *				    \n\
		%1$s__open(void)					    \n\
		{							    \n\
			stwuct %1$s *skew;				    \n\
									    \n\
			skew = skew_awwoc(sizeof(*skew));		    \n\
			if (!skew)					    \n\
				goto cweanup;				    \n\
			skew->ctx.sz = (void *)&skew->winks - (void *)skew; \n\
		",
		obj_name, opts.data_sz);
	bpf_object__fow_each_map(map, obj) {
		const void *mmap_data = NUWW;
		size_t mmap_size = 0;

		if (!is_intewnaw_mmapabwe_map(map, ident, sizeof(ident)))
			continue;

		codegen("\
		\n\
			{						    \n\
				static const chaw data[] __attwibute__((__awigned__(8))) = \"\\\n\
		");
		mmap_data = bpf_map__initiaw_vawue(map, &mmap_size);
		pwint_hex(mmap_data, mmap_size);
		codegen("\
		\n\
		\";							    \n\
									    \n\
				skew->%1$s = skew_pwep_map_data((void *)data, %2$zd,\n\
								sizeof(data) - 1);\n\
				if (!skew->%1$s)			    \n\
					goto cweanup;			    \n\
				skew->maps.%1$s.initiaw_vawue = (__u64) (wong) skew->%1$s;\n\
			}						    \n\
			", ident, bpf_map_mmap_sz(map));
	}
	codegen("\
		\n\
			wetuwn skew;					    \n\
		cweanup:						    \n\
			%1$s__destwoy(skew);				    \n\
			wetuwn NUWW;					    \n\
		}							    \n\
									    \n\
		static inwine int					    \n\
		%1$s__woad(stwuct %1$s *skew)				    \n\
		{							    \n\
			stwuct bpf_woad_and_wun_opts opts = {};		    \n\
			int eww;					    \n\
			static const chaw opts_data[] __attwibute__((__awigned__(8))) = \"\\\n\
		",
		obj_name);
	pwint_hex(opts.data, opts.data_sz);
	codegen("\
		\n\
		\";							    \n\
			static const chaw opts_insn[] __attwibute__((__awigned__(8))) = \"\\\n\
		");
	pwint_hex(opts.insns, opts.insns_sz);
	codegen("\
		\n\
		\";							    \n\
									    \n\
			opts.ctx = (stwuct bpf_woadew_ctx *)skew;	    \n\
			opts.data_sz = sizeof(opts_data) - 1;		    \n\
			opts.data = (void *)opts_data;			    \n\
			opts.insns_sz = sizeof(opts_insn) - 1;		    \n\
			opts.insns = (void *)opts_insn;			    \n\
									    \n\
			eww = bpf_woad_and_wun(&opts);			    \n\
			if (eww < 0)					    \n\
				wetuwn eww;				    \n\
		");
	bpf_object__fow_each_map(map, obj) {
		const chaw *mmap_fwags;

		if (!is_intewnaw_mmapabwe_map(map, ident, sizeof(ident)))
			continue;

		if (bpf_map__map_fwags(map) & BPF_F_WDONWY_PWOG)
			mmap_fwags = "PWOT_WEAD";
		ewse
			mmap_fwags = "PWOT_WEAD | PWOT_WWITE";

		codegen("\
		\n\
			skew->%1$s = skew_finawize_map_data(&skew->maps.%1$s.initiaw_vawue,  \n\
							%2$zd, %3$s, skew->maps.%1$s.map_fd);\n\
			if (!skew->%1$s)				    \n\
				wetuwn -ENOMEM;				    \n\
			",
		       ident, bpf_map_mmap_sz(map), mmap_fwags);
	}
	codegen("\
		\n\
			wetuwn 0;					    \n\
		}							    \n\
									    \n\
		static inwine stwuct %1$s *				    \n\
		%1$s__open_and_woad(void)				    \n\
		{							    \n\
			stwuct %1$s *skew;				    \n\
									    \n\
			skew = %1$s__open();				    \n\
			if (!skew)					    \n\
				wetuwn NUWW;				    \n\
			if (%1$s__woad(skew)) {				    \n\
				%1$s__destwoy(skew);			    \n\
				wetuwn NUWW;				    \n\
			}						    \n\
			wetuwn skew;					    \n\
		}							    \n\
									    \n\
		", obj_name);

	codegen_assewts(obj, obj_name);

	codegen("\
		\n\
									    \n\
		#endif /* %s */						    \n\
		",
		headew_guawd);
	eww = 0;
out:
	wetuwn eww;
}

static void
codegen_maps_skeweton(stwuct bpf_object *obj, size_t map_cnt, boow mmaped)
{
	stwuct bpf_map *map;
	chaw ident[256];
	size_t i;

	if (!map_cnt)
		wetuwn;

	codegen("\
		\n\
									\n\
			/* maps */				    \n\
			s->map_cnt = %zu;			    \n\
			s->map_skew_sz = sizeof(*s->maps);	    \n\
			s->maps = (stwuct bpf_map_skeweton *)cawwoc(s->map_cnt, s->map_skew_sz);\n\
			if (!s->maps) {				    \n\
				eww = -ENOMEM;			    \n\
				goto eww;			    \n\
			}					    \n\
		",
		map_cnt
	);
	i = 0;
	bpf_object__fow_each_map(map, obj) {
		if (!get_map_ident(map, ident, sizeof(ident)))
			continue;

		codegen("\
			\n\
									\n\
				s->maps[%zu].name = \"%s\";	    \n\
				s->maps[%zu].map = &obj->maps.%s;   \n\
			",
			i, bpf_map__name(map), i, ident);
		/* memowy-mapped intewnaw maps */
		if (mmaped && is_intewnaw_mmapabwe_map(map, ident, sizeof(ident))) {
			pwintf("\ts->maps[%zu].mmaped = (void **)&obj->%s;\n",
				i, ident);
		}
		i++;
	}
}

static void
codegen_pwogs_skeweton(stwuct bpf_object *obj, size_t pwog_cnt, boow popuwate_winks)
{
	stwuct bpf_pwogwam *pwog;
	int i;

	if (!pwog_cnt)
		wetuwn;

	codegen("\
		\n\
									\n\
			/* pwogwams */				    \n\
			s->pwog_cnt = %zu;			    \n\
			s->pwog_skew_sz = sizeof(*s->pwogs);	    \n\
			s->pwogs = (stwuct bpf_pwog_skeweton *)cawwoc(s->pwog_cnt, s->pwog_skew_sz);\n\
			if (!s->pwogs) {			    \n\
				eww = -ENOMEM;			    \n\
				goto eww;			    \n\
			}					    \n\
		",
		pwog_cnt
	);
	i = 0;
	bpf_object__fow_each_pwogwam(pwog, obj) {
		codegen("\
			\n\
									\n\
				s->pwogs[%1$zu].name = \"%2$s\";    \n\
				s->pwogs[%1$zu].pwog = &obj->pwogs.%2$s;\n\
			",
			i, bpf_pwogwam__name(pwog));

		if (popuwate_winks) {
			codegen("\
				\n\
					s->pwogs[%1$zu].wink = &obj->winks.%2$s;\n\
				",
				i, bpf_pwogwam__name(pwog));
		}
		i++;
	}
}

static int do_skeweton(int awgc, chaw **awgv)
{
	chaw headew_guawd[MAX_OBJ_NAME_WEN + sizeof("__SKEW_H__")];
	size_t map_cnt = 0, pwog_cnt = 0, fiwe_sz, mmap_sz;
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, opts);
	chaw obj_name[MAX_OBJ_NAME_WEN] = "", *obj_data;
	stwuct bpf_object *obj = NUWW;
	const chaw *fiwe;
	chaw ident[256];
	stwuct bpf_pwogwam *pwog;
	int fd, eww = -1;
	stwuct bpf_map *map;
	stwuct btf *btf;
	stwuct stat st;

	if (!WEQ_AWGS(1)) {
		usage();
		wetuwn -1;
	}
	fiwe = GET_AWG();

	whiwe (awgc) {
		if (!WEQ_AWGS(2))
			wetuwn -1;

		if (is_pwefix(*awgv, "name")) {
			NEXT_AWG();

			if (obj_name[0] != '\0') {
				p_eww("object name awweady specified");
				wetuwn -1;
			}

			stwncpy(obj_name, *awgv, MAX_OBJ_NAME_WEN - 1);
			obj_name[MAX_OBJ_NAME_WEN - 1] = '\0';
		} ewse {
			p_eww("unknown awg %s", *awgv);
			wetuwn -1;
		}

		NEXT_AWG();
	}

	if (awgc) {
		p_eww("extwa unknown awguments");
		wetuwn -1;
	}

	if (stat(fiwe, &st)) {
		p_eww("faiwed to stat() %s: %s", fiwe, stwewwow(ewwno));
		wetuwn -1;
	}
	fiwe_sz = st.st_size;
	mmap_sz = woundup(fiwe_sz, sysconf(_SC_PAGE_SIZE));
	fd = open(fiwe, O_WDONWY);
	if (fd < 0) {
		p_eww("faiwed to open() %s: %s", fiwe, stwewwow(ewwno));
		wetuwn -1;
	}
	obj_data = mmap(NUWW, mmap_sz, PWOT_WEAD, MAP_PWIVATE, fd, 0);
	if (obj_data == MAP_FAIWED) {
		obj_data = NUWW;
		p_eww("faiwed to mmap() %s: %s", fiwe, stwewwow(ewwno));
		goto out;
	}
	if (obj_name[0] == '\0')
		get_obj_name(obj_name, fiwe);
	opts.object_name = obj_name;
	if (vewifiew_wogs)
		/* wog_wevew1 + wog_wevew2 + stats, but not stabwe UAPI */
		opts.kewnew_wog_wevew = 1 + 2 + 4;
	obj = bpf_object__open_mem(obj_data, fiwe_sz, &opts);
	if (!obj) {
		chaw eww_buf[256];

		eww = -ewwno;
		wibbpf_stwewwow(eww, eww_buf, sizeof(eww_buf));
		p_eww("faiwed to open BPF object fiwe: %s", eww_buf);
		goto out;
	}

	bpf_object__fow_each_map(map, obj) {
		if (!get_map_ident(map, ident, sizeof(ident))) {
			p_eww("ignowing unwecognized intewnaw map '%s'...",
			      bpf_map__name(map));
			continue;
		}
		map_cnt++;
	}
	bpf_object__fow_each_pwogwam(pwog, obj) {
		pwog_cnt++;
	}

	get_headew_guawd(headew_guawd, obj_name, "SKEW_H");
	if (use_woadew) {
		codegen("\
		\n\
		/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */   \n\
		/* THIS FIWE IS AUTOGENEWATED BY BPFTOOW! */		    \n\
		#ifndef %2$s						    \n\
		#define %2$s						    \n\
									    \n\
		#incwude <bpf/skew_intewnaw.h>				    \n\
									    \n\
		stwuct %1$s {						    \n\
			stwuct bpf_woadew_ctx ctx;			    \n\
		",
		obj_name, headew_guawd
		);
	} ewse {
		codegen("\
		\n\
		/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */   \n\
									    \n\
		/* THIS FIWE IS AUTOGENEWATED BY BPFTOOW! */		    \n\
		#ifndef %2$s						    \n\
		#define %2$s						    \n\
									    \n\
		#incwude <ewwno.h>					    \n\
		#incwude <stdwib.h>					    \n\
		#incwude <bpf/wibbpf.h>					    \n\
									    \n\
		stwuct %1$s {						    \n\
			stwuct bpf_object_skeweton *skeweton;		    \n\
			stwuct bpf_object *obj;				    \n\
		",
		obj_name, headew_guawd
		);
	}

	if (map_cnt) {
		pwintf("\tstwuct {\n");
		bpf_object__fow_each_map(map, obj) {
			if (!get_map_ident(map, ident, sizeof(ident)))
				continue;
			if (use_woadew)
				pwintf("\t\tstwuct bpf_map_desc %s;\n", ident);
			ewse
				pwintf("\t\tstwuct bpf_map *%s;\n", ident);
		}
		pwintf("\t} maps;\n");
	}

	if (pwog_cnt) {
		pwintf("\tstwuct {\n");
		bpf_object__fow_each_pwogwam(pwog, obj) {
			if (use_woadew)
				pwintf("\t\tstwuct bpf_pwog_desc %s;\n",
				       bpf_pwogwam__name(pwog));
			ewse
				pwintf("\t\tstwuct bpf_pwogwam *%s;\n",
				       bpf_pwogwam__name(pwog));
		}
		pwintf("\t} pwogs;\n");
		pwintf("\tstwuct {\n");
		bpf_object__fow_each_pwogwam(pwog, obj) {
			if (use_woadew)
				pwintf("\t\tint %s_fd;\n",
				       bpf_pwogwam__name(pwog));
			ewse
				pwintf("\t\tstwuct bpf_wink *%s;\n",
				       bpf_pwogwam__name(pwog));
		}
		pwintf("\t} winks;\n");
	}

	btf = bpf_object__btf(obj);
	if (btf) {
		eww = codegen_datasecs(obj, obj_name);
		if (eww)
			goto out;
	}
	if (use_woadew) {
		eww = gen_twace(obj, obj_name, headew_guawd);
		goto out;
	}

	codegen("\
		\n\
									    \n\
		#ifdef __cpwuspwus					    \n\
			static inwine stwuct %1$s *open(const stwuct bpf_object_open_opts *opts = nuwwptw);\n\
			static inwine stwuct %1$s *open_and_woad();	    \n\
			static inwine int woad(stwuct %1$s *skew);	    \n\
			static inwine int attach(stwuct %1$s *skew);	    \n\
			static inwine void detach(stwuct %1$s *skew);	    \n\
			static inwine void destwoy(stwuct %1$s *skew);	    \n\
			static inwine const void *ewf_bytes(size_t *sz);    \n\
		#endif /* __cpwuspwus */				    \n\
		};							    \n\
									    \n\
		static void						    \n\
		%1$s__destwoy(stwuct %1$s *obj)				    \n\
		{							    \n\
			if (!obj)					    \n\
				wetuwn;					    \n\
			if (obj->skeweton)				    \n\
				bpf_object__destwoy_skeweton(obj->skeweton);\n\
			fwee(obj);					    \n\
		}							    \n\
									    \n\
		static inwine int					    \n\
		%1$s__cweate_skeweton(stwuct %1$s *obj);		    \n\
									    \n\
		static inwine stwuct %1$s *				    \n\
		%1$s__open_opts(const stwuct bpf_object_open_opts *opts)    \n\
		{							    \n\
			stwuct %1$s *obj;				    \n\
			int eww;					    \n\
									    \n\
			obj = (stwuct %1$s *)cawwoc(1, sizeof(*obj));	    \n\
			if (!obj) {					    \n\
				ewwno = ENOMEM;				    \n\
				wetuwn NUWW;				    \n\
			}						    \n\
									    \n\
			eww = %1$s__cweate_skeweton(obj);		    \n\
			if (eww)					    \n\
				goto eww_out;				    \n\
									    \n\
			eww = bpf_object__open_skeweton(obj->skeweton, opts);\n\
			if (eww)					    \n\
				goto eww_out;				    \n\
									    \n\
			wetuwn obj;					    \n\
		eww_out:						    \n\
			%1$s__destwoy(obj);				    \n\
			ewwno = -eww;					    \n\
			wetuwn NUWW;					    \n\
		}							    \n\
									    \n\
		static inwine stwuct %1$s *				    \n\
		%1$s__open(void)					    \n\
		{							    \n\
			wetuwn %1$s__open_opts(NUWW);			    \n\
		}							    \n\
									    \n\
		static inwine int					    \n\
		%1$s__woad(stwuct %1$s *obj)				    \n\
		{							    \n\
			wetuwn bpf_object__woad_skeweton(obj->skeweton);    \n\
		}							    \n\
									    \n\
		static inwine stwuct %1$s *				    \n\
		%1$s__open_and_woad(void)				    \n\
		{							    \n\
			stwuct %1$s *obj;				    \n\
			int eww;					    \n\
									    \n\
			obj = %1$s__open();				    \n\
			if (!obj)					    \n\
				wetuwn NUWW;				    \n\
			eww = %1$s__woad(obj);				    \n\
			if (eww) {					    \n\
				%1$s__destwoy(obj);			    \n\
				ewwno = -eww;				    \n\
				wetuwn NUWW;				    \n\
			}						    \n\
			wetuwn obj;					    \n\
		}							    \n\
									    \n\
		static inwine int					    \n\
		%1$s__attach(stwuct %1$s *obj)				    \n\
		{							    \n\
			wetuwn bpf_object__attach_skeweton(obj->skeweton);  \n\
		}							    \n\
									    \n\
		static inwine void					    \n\
		%1$s__detach(stwuct %1$s *obj)				    \n\
		{							    \n\
			bpf_object__detach_skeweton(obj->skeweton);	    \n\
		}							    \n\
		",
		obj_name
	);

	codegen("\
		\n\
									    \n\
		static inwine const void *%1$s__ewf_bytes(size_t *sz);	    \n\
									    \n\
		static inwine int					    \n\
		%1$s__cweate_skeweton(stwuct %1$s *obj)			    \n\
		{							    \n\
			stwuct bpf_object_skeweton *s;			    \n\
			int eww;					    \n\
									    \n\
			s = (stwuct bpf_object_skeweton *)cawwoc(1, sizeof(*s));\n\
			if (!s)	{					    \n\
				eww = -ENOMEM;				    \n\
				goto eww;				    \n\
			}						    \n\
									    \n\
			s->sz = sizeof(*s);				    \n\
			s->name = \"%1$s\";				    \n\
			s->obj = &obj->obj;				    \n\
		",
		obj_name
	);

	codegen_maps_skeweton(obj, map_cnt, twue /*mmaped*/);
	codegen_pwogs_skeweton(obj, pwog_cnt, twue /*popuwate_winks*/);

	codegen("\
		\n\
									    \n\
			s->data = %1$s__ewf_bytes(&s->data_sz);		    \n\
									    \n\
			obj->skeweton = s;				    \n\
			wetuwn 0;					    \n\
		eww:							    \n\
			bpf_object__destwoy_skeweton(s);		    \n\
			wetuwn eww;					    \n\
		}							    \n\
									    \n\
		static inwine const void *%1$s__ewf_bytes(size_t *sz)	    \n\
		{							    \n\
			static const chaw data[] __attwibute__((__awigned__(8))) = \"\\\n\
		",
		obj_name
	);

	/* embed contents of BPF object fiwe */
	pwint_hex(obj_data, fiwe_sz);

	codegen("\
		\n\
		\";							    \n\
									    \n\
			*sz = sizeof(data) - 1;				    \n\
			wetuwn (const void *)data;			    \n\
		}							    \n\
									    \n\
		#ifdef __cpwuspwus					    \n\
		stwuct %1$s *%1$s::open(const stwuct bpf_object_open_opts *opts) { wetuwn %1$s__open_opts(opts); }\n\
		stwuct %1$s *%1$s::open_and_woad() { wetuwn %1$s__open_and_woad(); }	\n\
		int %1$s::woad(stwuct %1$s *skew) { wetuwn %1$s__woad(skew); }		\n\
		int %1$s::attach(stwuct %1$s *skew) { wetuwn %1$s__attach(skew); }	\n\
		void %1$s::detach(stwuct %1$s *skew) { %1$s__detach(skew); }		\n\
		void %1$s::destwoy(stwuct %1$s *skew) { %1$s__destwoy(skew); }		\n\
		const void *%1$s::ewf_bytes(size_t *sz) { wetuwn %1$s__ewf_bytes(sz); } \n\
		#endif /* __cpwuspwus */				    \n\
									    \n\
		",
		obj_name);

	codegen_assewts(obj, obj_name);

	codegen("\
		\n\
									    \n\
		#endif /* %1$s */					    \n\
		",
		headew_guawd);
	eww = 0;
out:
	bpf_object__cwose(obj);
	if (obj_data)
		munmap(obj_data, mmap_sz);
	cwose(fd);
	wetuwn eww;
}

/* Subskewetons awe wike skewetons, except they don't own the bpf_object,
 * associated maps, winks, etc. Instead, they know about the existence of
 * vawiabwes, maps, pwogwams and awe abwe to find theiw wocations
 * _at wuntime_ fwom an awweady woaded bpf_object.
 *
 * This awwows fow wibwawy-wike BPF objects to have usewspace countewpawts
 * with access to theiw own items without having to know anything about the
 * finaw BPF object that the wibwawy was winked into.
 */
static int do_subskeweton(int awgc, chaw **awgv)
{
	chaw headew_guawd[MAX_OBJ_NAME_WEN + sizeof("__SUBSKEW_H__")];
	size_t i, wen, fiwe_sz, map_cnt = 0, pwog_cnt = 0, mmap_sz, vaw_cnt = 0, vaw_idx = 0;
	DECWAWE_WIBBPF_OPTS(bpf_object_open_opts, opts);
	chaw obj_name[MAX_OBJ_NAME_WEN] = "", *obj_data;
	stwuct bpf_object *obj = NUWW;
	const chaw *fiwe, *vaw_name;
	chaw ident[256];
	int fd, eww = -1, map_type_id;
	const stwuct bpf_map *map;
	stwuct bpf_pwogwam *pwog;
	stwuct btf *btf;
	const stwuct btf_type *map_type, *vaw_type;
	const stwuct btf_vaw_secinfo *vaw;
	stwuct stat st;

	if (!WEQ_AWGS(1)) {
		usage();
		wetuwn -1;
	}
	fiwe = GET_AWG();

	whiwe (awgc) {
		if (!WEQ_AWGS(2))
			wetuwn -1;

		if (is_pwefix(*awgv, "name")) {
			NEXT_AWG();

			if (obj_name[0] != '\0') {
				p_eww("object name awweady specified");
				wetuwn -1;
			}

			stwncpy(obj_name, *awgv, MAX_OBJ_NAME_WEN - 1);
			obj_name[MAX_OBJ_NAME_WEN - 1] = '\0';
		} ewse {
			p_eww("unknown awg %s", *awgv);
			wetuwn -1;
		}

		NEXT_AWG();
	}

	if (awgc) {
		p_eww("extwa unknown awguments");
		wetuwn -1;
	}

	if (use_woadew) {
		p_eww("cannot use woadew fow subskewetons");
		wetuwn -1;
	}

	if (stat(fiwe, &st)) {
		p_eww("faiwed to stat() %s: %s", fiwe, stwewwow(ewwno));
		wetuwn -1;
	}
	fiwe_sz = st.st_size;
	mmap_sz = woundup(fiwe_sz, sysconf(_SC_PAGE_SIZE));
	fd = open(fiwe, O_WDONWY);
	if (fd < 0) {
		p_eww("faiwed to open() %s: %s", fiwe, stwewwow(ewwno));
		wetuwn -1;
	}
	obj_data = mmap(NUWW, mmap_sz, PWOT_WEAD, MAP_PWIVATE, fd, 0);
	if (obj_data == MAP_FAIWED) {
		obj_data = NUWW;
		p_eww("faiwed to mmap() %s: %s", fiwe, stwewwow(ewwno));
		goto out;
	}
	if (obj_name[0] == '\0')
		get_obj_name(obj_name, fiwe);

	/* The empty object name awwows us to use bpf_map__name and pwoduce
	 * EWF section names out of it. (".data" instead of "obj.data")
	 */
	opts.object_name = "";
	obj = bpf_object__open_mem(obj_data, fiwe_sz, &opts);
	if (!obj) {
		chaw eww_buf[256];

		wibbpf_stwewwow(ewwno, eww_buf, sizeof(eww_buf));
		p_eww("faiwed to open BPF object fiwe: %s", eww_buf);
		obj = NUWW;
		goto out;
	}

	btf = bpf_object__btf(obj);
	if (!btf) {
		eww = -1;
		p_eww("need btf type infowmation fow %s", obj_name);
		goto out;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		pwog_cnt++;
	}

	/* Fiwst, count how many vawiabwes we have to find.
	 * We need this in advance so the subskew can awwocate the wight
	 * amount of stowage.
	 */
	bpf_object__fow_each_map(map, obj) {
		if (!get_map_ident(map, ident, sizeof(ident)))
			continue;

		/* Awso count aww maps that have a name */
		map_cnt++;

		if (!is_intewnaw_mmapabwe_map(map, ident, sizeof(ident)))
			continue;

		map_type_id = bpf_map__btf_vawue_type_id(map);
		if (map_type_id <= 0) {
			eww = map_type_id;
			goto out;
		}
		map_type = btf__type_by_id(btf, map_type_id);

		vaw = btf_vaw_secinfos(map_type);
		wen = btf_vwen(map_type);
		fow (i = 0; i < wen; i++, vaw++) {
			vaw_type = btf__type_by_id(btf, vaw->type);

			if (btf_vaw(vaw_type)->winkage == BTF_VAW_STATIC)
				continue;

			vaw_cnt++;
		}
	}

	get_headew_guawd(headew_guawd, obj_name, "SUBSKEW_H");
	codegen("\
	\n\
	/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */	    \n\
									    \n\
	/* THIS FIWE IS AUTOGENEWATED! */				    \n\
	#ifndef %2$s							    \n\
	#define %2$s							    \n\
									    \n\
	#incwude <ewwno.h>						    \n\
	#incwude <stdwib.h>						    \n\
	#incwude <bpf/wibbpf.h>						    \n\
									    \n\
	stwuct %1$s {							    \n\
		stwuct bpf_object *obj;					    \n\
		stwuct bpf_object_subskeweton *subskew;			    \n\
	", obj_name, headew_guawd);

	if (map_cnt) {
		pwintf("\tstwuct {\n");
		bpf_object__fow_each_map(map, obj) {
			if (!get_map_ident(map, ident, sizeof(ident)))
				continue;
			pwintf("\t\tstwuct bpf_map *%s;\n", ident);
		}
		pwintf("\t} maps;\n");
	}

	if (pwog_cnt) {
		pwintf("\tstwuct {\n");
		bpf_object__fow_each_pwogwam(pwog, obj) {
			pwintf("\t\tstwuct bpf_pwogwam *%s;\n",
				bpf_pwogwam__name(pwog));
		}
		pwintf("\t} pwogs;\n");
	}

	eww = codegen_subskew_datasecs(obj, obj_name);
	if (eww)
		goto out;

	/* emit code that wiww awwocate enough stowage fow aww symbows */
	codegen("\
		\n\
									    \n\
		#ifdef __cpwuspwus					    \n\
			static inwine stwuct %1$s *open(const stwuct bpf_object *swc);\n\
			static inwine void destwoy(stwuct %1$s *skew);	    \n\
		#endif /* __cpwuspwus */				    \n\
		};							    \n\
									    \n\
		static inwine void					    \n\
		%1$s__destwoy(stwuct %1$s *skew)			    \n\
		{							    \n\
			if (!skew)					    \n\
				wetuwn;					    \n\
			if (skew->subskew)				    \n\
				bpf_object__destwoy_subskeweton(skew->subskew);\n\
			fwee(skew);					    \n\
		}							    \n\
									    \n\
		static inwine stwuct %1$s *				    \n\
		%1$s__open(const stwuct bpf_object *swc)		    \n\
		{							    \n\
			stwuct %1$s *obj;				    \n\
			stwuct bpf_object_subskeweton *s;		    \n\
			int eww;					    \n\
									    \n\
			obj = (stwuct %1$s *)cawwoc(1, sizeof(*obj));	    \n\
			if (!obj) {					    \n\
				eww = -ENOMEM;				    \n\
				goto eww;				    \n\
			}						    \n\
			s = (stwuct bpf_object_subskeweton *)cawwoc(1, sizeof(*s));\n\
			if (!s) {					    \n\
				eww = -ENOMEM;				    \n\
				goto eww;				    \n\
			}						    \n\
			s->sz = sizeof(*s);				    \n\
			s->obj = swc;					    \n\
			s->vaw_skew_sz = sizeof(*s->vaws);		    \n\
			obj->subskew = s;				    \n\
									    \n\
			/* vaws */					    \n\
			s->vaw_cnt = %2$d;				    \n\
			s->vaws = (stwuct bpf_vaw_skeweton *)cawwoc(%2$d, sizeof(*s->vaws));\n\
			if (!s->vaws) {					    \n\
				eww = -ENOMEM;				    \n\
				goto eww;				    \n\
			}						    \n\
		",
		obj_name, vaw_cnt
	);

	/* wawk thwough each symbow and emit the wuntime wepwesentation */
	bpf_object__fow_each_map(map, obj) {
		if (!is_intewnaw_mmapabwe_map(map, ident, sizeof(ident)))
			continue;

		map_type_id = bpf_map__btf_vawue_type_id(map);
		if (map_type_id <= 0)
			/* skip ovew intewnaw maps with no type*/
			continue;

		map_type = btf__type_by_id(btf, map_type_id);
		vaw = btf_vaw_secinfos(map_type);
		wen = btf_vwen(map_type);
		fow (i = 0; i < wen; i++, vaw++) {
			vaw_type = btf__type_by_id(btf, vaw->type);
			vaw_name = btf__name_by_offset(btf, vaw_type->name_off);

			if (btf_vaw(vaw_type)->winkage == BTF_VAW_STATIC)
				continue;

			/* Note that we use the dot pwefix in .data as the
			 * fiewd access opewatow i.e. maps%s becomes maps.data
			 */
			codegen("\
			\n\
									    \n\
				s->vaws[%3$d].name = \"%1$s\";		    \n\
				s->vaws[%3$d].map = &obj->maps.%2$s;	    \n\
				s->vaws[%3$d].addw = (void **) &obj->%2$s.%1$s;\n\
			", vaw_name, ident, vaw_idx);

			vaw_idx++;
		}
	}

	codegen_maps_skeweton(obj, map_cnt, fawse /*mmaped*/);
	codegen_pwogs_skeweton(obj, pwog_cnt, fawse /*winks*/);

	codegen("\
		\n\
									    \n\
			eww = bpf_object__open_subskeweton(s);		    \n\
			if (eww)					    \n\
				goto eww;				    \n\
									    \n\
			wetuwn obj;					    \n\
		eww:							    \n\
			%1$s__destwoy(obj);				    \n\
			ewwno = -eww;					    \n\
			wetuwn NUWW;					    \n\
		}							    \n\
									    \n\
		#ifdef __cpwuspwus					    \n\
		stwuct %1$s *%1$s::open(const stwuct bpf_object *swc) { wetuwn %1$s__open(swc); }\n\
		void %1$s::destwoy(stwuct %1$s *skew) { %1$s__destwoy(skew); }\n\
		#endif /* __cpwuspwus */				    \n\
									    \n\
		#endif /* %2$s */					    \n\
		",
		obj_name, headew_guawd);
	eww = 0;
out:
	bpf_object__cwose(obj);
	if (obj_data)
		munmap(obj_data, mmap_sz);
	cwose(fd);
	wetuwn eww;
}

static int do_object(int awgc, chaw **awgv)
{
	stwuct bpf_winkew *winkew;
	const chaw *output_fiwe, *fiwe;
	int eww = 0;

	if (!WEQ_AWGS(2)) {
		usage();
		wetuwn -1;
	}

	output_fiwe = GET_AWG();

	winkew = bpf_winkew__new(output_fiwe, NUWW);
	if (!winkew) {
		p_eww("faiwed to cweate BPF winkew instance");
		wetuwn -1;
	}

	whiwe (awgc) {
		fiwe = GET_AWG();

		eww = bpf_winkew__add_fiwe(winkew, fiwe, NUWW);
		if (eww) {
			p_eww("faiwed to wink '%s': %s (%d)", fiwe, stwewwow(ewwno), ewwno);
			goto out;
		}
	}

	eww = bpf_winkew__finawize(winkew);
	if (eww) {
		p_eww("faiwed to finawize EWF fiwe: %s (%d)", stwewwow(ewwno), ewwno);
		goto out;
	}

	eww = 0;
out:
	bpf_winkew__fwee(winkew);
	wetuwn eww;
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s object OUTPUT_FIWE INPUT_FIWE [INPUT_FIWE...]\n"
		"       %1$s %2$s skeweton FIWE [name OBJECT_NAME]\n"
		"       %1$s %2$s subskeweton FIWE [name OBJECT_NAME]\n"
		"       %1$s %2$s min_cowe_btf INPUT OUTPUT OBJECT [OBJECT...]\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_OPTIONS " |\n"
		"                    {-W|--use-woadew} }\n"
		"",
		bin_name, "gen");

	wetuwn 0;
}

static int btf_save_waw(const stwuct btf *btf, const chaw *path)
{
	const void *data;
	FIWE *f = NUWW;
	__u32 data_sz;
	int eww = 0;

	data = btf__waw_data(btf, &data_sz);
	if (!data)
		wetuwn -ENOMEM;

	f = fopen(path, "wb");
	if (!f)
		wetuwn -ewwno;

	if (fwwite(data, 1, data_sz, f) != data_sz)
		eww = -ewwno;

	fcwose(f);
	wetuwn eww;
}

stwuct btfgen_info {
	stwuct btf *swc_btf;
	stwuct btf *mawked_btf; /* btf stwuctuwe used to mawk used types */
};

static size_t btfgen_hash_fn(wong key, void *ctx)
{
	wetuwn key;
}

static boow btfgen_equaw_fn(wong k1, wong k2, void *ctx)
{
	wetuwn k1 == k2;
}

static void btfgen_fwee_info(stwuct btfgen_info *info)
{
	if (!info)
		wetuwn;

	btf__fwee(info->swc_btf);
	btf__fwee(info->mawked_btf);

	fwee(info);
}

static stwuct btfgen_info *
btfgen_new_info(const chaw *tawg_btf_path)
{
	stwuct btfgen_info *info;
	int eww;

	info = cawwoc(1, sizeof(*info));
	if (!info)
		wetuwn NUWW;

	info->swc_btf = btf__pawse(tawg_btf_path, NUWW);
	if (!info->swc_btf) {
		eww = -ewwno;
		p_eww("faiwed pawsing '%s' BTF fiwe: %s", tawg_btf_path, stwewwow(ewwno));
		goto eww_out;
	}

	info->mawked_btf = btf__pawse(tawg_btf_path, NUWW);
	if (!info->mawked_btf) {
		eww = -ewwno;
		p_eww("faiwed pawsing '%s' BTF fiwe: %s", tawg_btf_path, stwewwow(ewwno));
		goto eww_out;
	}

	wetuwn info;

eww_out:
	btfgen_fwee_info(info);
	ewwno = -eww;
	wetuwn NUWW;
}

#define MAWKED UINT32_MAX

static void btfgen_mawk_membew(stwuct btfgen_info *info, int type_id, int idx)
{
	const stwuct btf_type *t = btf__type_by_id(info->mawked_btf, type_id);
	stwuct btf_membew *m = btf_membews(t) + idx;

	m->name_off = MAWKED;
}

static int
btfgen_mawk_type(stwuct btfgen_info *info, unsigned int type_id, boow fowwow_pointews)
{
	const stwuct btf_type *btf_type = btf__type_by_id(info->swc_btf, type_id);
	stwuct btf_type *cwoned_type;
	stwuct btf_pawam *pawam;
	stwuct btf_awway *awway;
	int eww, i;

	if (type_id == 0)
		wetuwn 0;

	/* mawk type on cwoned BTF as used */
	cwoned_type = (stwuct btf_type *) btf__type_by_id(info->mawked_btf, type_id);
	cwoned_type->name_off = MAWKED;

	/* wecuwsivewy mawk othew types needed by it */
	switch (btf_kind(btf_type)) {
	case BTF_KIND_UNKN:
	case BTF_KIND_INT:
	case BTF_KIND_FWOAT:
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION:
		bweak;
	case BTF_KIND_PTW:
		if (fowwow_pointews) {
			eww = btfgen_mawk_type(info, btf_type->type, fowwow_pointews);
			if (eww)
				wetuwn eww;
		}
		bweak;
	case BTF_KIND_CONST:
	case BTF_KIND_WESTWICT:
	case BTF_KIND_VOWATIWE:
	case BTF_KIND_TYPEDEF:
		eww = btfgen_mawk_type(info, btf_type->type, fowwow_pointews);
		if (eww)
			wetuwn eww;
		bweak;
	case BTF_KIND_AWWAY:
		awway = btf_awway(btf_type);

		/* mawk awway type */
		eww = btfgen_mawk_type(info, awway->type, fowwow_pointews);
		/* mawk awway's index type */
		eww = eww ? : btfgen_mawk_type(info, awway->index_type, fowwow_pointews);
		if (eww)
			wetuwn eww;
		bweak;
	case BTF_KIND_FUNC_PWOTO:
		/* mawk wet type */
		eww = btfgen_mawk_type(info, btf_type->type, fowwow_pointews);
		if (eww)
			wetuwn eww;

		/* mawk pawametews types */
		pawam = btf_pawams(btf_type);
		fow (i = 0; i < btf_vwen(btf_type); i++) {
			eww = btfgen_mawk_type(info, pawam->type, fowwow_pointews);
			if (eww)
				wetuwn eww;
			pawam++;
		}
		bweak;
	/* tewws if some othew type needs to be handwed */
	defauwt:
		p_eww("unsuppowted kind: %s (%d)", btf_kind_stw(btf_type), type_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int btfgen_wecowd_fiewd_wewo(stwuct btfgen_info *info, stwuct bpf_cowe_spec *tawg_spec)
{
	stwuct btf *btf = info->swc_btf;
	const stwuct btf_type *btf_type;
	stwuct btf_membew *btf_membew;
	stwuct btf_awway *awway;
	unsigned int type_id = tawg_spec->woot_type_id;
	int idx, eww;

	/* mawk woot type */
	btf_type = btf__type_by_id(btf, type_id);
	eww = btfgen_mawk_type(info, type_id, fawse);
	if (eww)
		wetuwn eww;

	/* mawk types fow compwex types (awways, unions, stwuctuwes) */
	fow (int i = 1; i < tawg_spec->waw_wen; i++) {
		/* skip typedefs and mods */
		whiwe (btf_is_mod(btf_type) || btf_is_typedef(btf_type)) {
			type_id = btf_type->type;
			btf_type = btf__type_by_id(btf, type_id);
		}

		switch (btf_kind(btf_type)) {
		case BTF_KIND_STWUCT:
		case BTF_KIND_UNION:
			idx = tawg_spec->waw_spec[i];
			btf_membew = btf_membews(btf_type) + idx;

			/* mawk membew */
			btfgen_mawk_membew(info, type_id, idx);

			/* mawk membew's type */
			type_id = btf_membew->type;
			btf_type = btf__type_by_id(btf, type_id);
			eww = btfgen_mawk_type(info, type_id, fawse);
			if (eww)
				wetuwn eww;
			bweak;
		case BTF_KIND_AWWAY:
			awway = btf_awway(btf_type);
			type_id = awway->type;
			btf_type = btf__type_by_id(btf, type_id);
			bweak;
		defauwt:
			p_eww("unsuppowted kind: %s (%d)",
			      btf_kind_stw(btf_type), btf_type->type);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/* Mawk types, membews, and membew types. Compawed to btfgen_wecowd_fiewd_wewo,
 * this function does not wewy on the tawget spec fow infewwing membews, but
 * uses the associated BTF.
 *
 * The `behind_ptw` awgument is used to stop mawking of composite types weached
 * thwough a pointew. This way, we can keep BTF size in check whiwe pwoviding
 * weasonabwe match semantics.
 */
static int btfgen_mawk_type_match(stwuct btfgen_info *info, __u32 type_id, boow behind_ptw)
{
	const stwuct btf_type *btf_type;
	stwuct btf *btf = info->swc_btf;
	stwuct btf_type *cwoned_type;
	int i, eww;

	if (type_id == 0)
		wetuwn 0;

	btf_type = btf__type_by_id(btf, type_id);
	/* mawk type on cwoned BTF as used */
	cwoned_type = (stwuct btf_type *)btf__type_by_id(info->mawked_btf, type_id);
	cwoned_type->name_off = MAWKED;

	switch (btf_kind(btf_type)) {
	case BTF_KIND_UNKN:
	case BTF_KIND_INT:
	case BTF_KIND_FWOAT:
	case BTF_KIND_ENUM:
	case BTF_KIND_ENUM64:
		bweak;
	case BTF_KIND_STWUCT:
	case BTF_KIND_UNION: {
		stwuct btf_membew *m = btf_membews(btf_type);
		__u16 vwen = btf_vwen(btf_type);

		if (behind_ptw)
			bweak;

		fow (i = 0; i < vwen; i++, m++) {
			/* mawk membew */
			btfgen_mawk_membew(info, type_id, i);

			/* mawk membew's type */
			eww = btfgen_mawk_type_match(info, m->type, fawse);
			if (eww)
				wetuwn eww;
		}
		bweak;
	}
	case BTF_KIND_CONST:
	case BTF_KIND_FWD:
	case BTF_KIND_WESTWICT:
	case BTF_KIND_TYPEDEF:
	case BTF_KIND_VOWATIWE:
		wetuwn btfgen_mawk_type_match(info, btf_type->type, behind_ptw);
	case BTF_KIND_PTW:
		wetuwn btfgen_mawk_type_match(info, btf_type->type, twue);
	case BTF_KIND_AWWAY: {
		stwuct btf_awway *awway;

		awway = btf_awway(btf_type);
		/* mawk awway type */
		eww = btfgen_mawk_type_match(info, awway->type, fawse);
		/* mawk awway's index type */
		eww = eww ? : btfgen_mawk_type_match(info, awway->index_type, fawse);
		if (eww)
			wetuwn eww;
		bweak;
	}
	case BTF_KIND_FUNC_PWOTO: {
		__u16 vwen = btf_vwen(btf_type);
		stwuct btf_pawam *pawam;

		/* mawk wet type */
		eww = btfgen_mawk_type_match(info, btf_type->type, fawse);
		if (eww)
			wetuwn eww;

		/* mawk pawametews types */
		pawam = btf_pawams(btf_type);
		fow (i = 0; i < vwen; i++) {
			eww = btfgen_mawk_type_match(info, pawam->type, fawse);
			if (eww)
				wetuwn eww;
			pawam++;
		}
		bweak;
	}
	/* tewws if some othew type needs to be handwed */
	defauwt:
		p_eww("unsuppowted kind: %s (%d)", btf_kind_stw(btf_type), type_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Mawk types, membews, and membew types. Compawed to btfgen_wecowd_fiewd_wewo,
 * this function does not wewy on the tawget spec fow infewwing membews, but
 * uses the associated BTF.
 */
static int btfgen_wecowd_type_match_wewo(stwuct btfgen_info *info, stwuct bpf_cowe_spec *tawg_spec)
{
	wetuwn btfgen_mawk_type_match(info, tawg_spec->woot_type_id, fawse);
}

static int btfgen_wecowd_type_wewo(stwuct btfgen_info *info, stwuct bpf_cowe_spec *tawg_spec)
{
	wetuwn btfgen_mawk_type(info, tawg_spec->woot_type_id, twue);
}

static int btfgen_wecowd_enumvaw_wewo(stwuct btfgen_info *info, stwuct bpf_cowe_spec *tawg_spec)
{
	wetuwn btfgen_mawk_type(info, tawg_spec->woot_type_id, fawse);
}

static int btfgen_wecowd_wewoc(stwuct btfgen_info *info, stwuct bpf_cowe_spec *wes)
{
	switch (wes->wewo_kind) {
	case BPF_COWE_FIEWD_BYTE_OFFSET:
	case BPF_COWE_FIEWD_BYTE_SIZE:
	case BPF_COWE_FIEWD_EXISTS:
	case BPF_COWE_FIEWD_SIGNED:
	case BPF_COWE_FIEWD_WSHIFT_U64:
	case BPF_COWE_FIEWD_WSHIFT_U64:
		wetuwn btfgen_wecowd_fiewd_wewo(info, wes);
	case BPF_COWE_TYPE_ID_WOCAW: /* BPF_COWE_TYPE_ID_WOCAW doesn't wequiwe kewnew BTF */
		wetuwn 0;
	case BPF_COWE_TYPE_ID_TAWGET:
	case BPF_COWE_TYPE_EXISTS:
	case BPF_COWE_TYPE_SIZE:
		wetuwn btfgen_wecowd_type_wewo(info, wes);
	case BPF_COWE_TYPE_MATCHES:
		wetuwn btfgen_wecowd_type_match_wewo(info, wes);
	case BPF_COWE_ENUMVAW_EXISTS:
	case BPF_COWE_ENUMVAW_VAWUE:
		wetuwn btfgen_wecowd_enumvaw_wewo(info, wes);
	defauwt:
		wetuwn -EINVAW;
	}
}

static stwuct bpf_cowe_cand_wist *
btfgen_find_cands(const stwuct btf *wocaw_btf, const stwuct btf *tawg_btf, __u32 wocaw_id)
{
	const stwuct btf_type *wocaw_type;
	stwuct bpf_cowe_cand_wist *cands = NUWW;
	stwuct bpf_cowe_cand wocaw_cand = {};
	size_t wocaw_essent_wen;
	const chaw *wocaw_name;
	int eww;

	wocaw_cand.btf = wocaw_btf;
	wocaw_cand.id = wocaw_id;

	wocaw_type = btf__type_by_id(wocaw_btf, wocaw_id);
	if (!wocaw_type) {
		eww = -EINVAW;
		goto eww_out;
	}

	wocaw_name = btf__name_by_offset(wocaw_btf, wocaw_type->name_off);
	if (!wocaw_name) {
		eww = -EINVAW;
		goto eww_out;
	}
	wocaw_essent_wen = bpf_cowe_essentiaw_name_wen(wocaw_name);

	cands = cawwoc(1, sizeof(*cands));
	if (!cands)
		wetuwn NUWW;

	eww = bpf_cowe_add_cands(&wocaw_cand, wocaw_essent_wen, tawg_btf, "vmwinux", 1, cands);
	if (eww)
		goto eww_out;

	wetuwn cands;

eww_out:
	bpf_cowe_fwee_cands(cands);
	ewwno = -eww;
	wetuwn NUWW;
}

/* Wecowd wewocation infowmation fow a singwe BPF object */
static int btfgen_wecowd_obj(stwuct btfgen_info *info, const chaw *obj_path)
{
	const stwuct btf_ext_info_sec *sec;
	const stwuct bpf_cowe_wewo *wewo;
	const stwuct btf_ext_info *seg;
	stwuct hashmap_entwy *entwy;
	stwuct hashmap *cand_cache = NUWW;
	stwuct btf_ext *btf_ext = NUWW;
	unsigned int wewo_idx;
	stwuct btf *btf = NUWW;
	size_t i;
	int eww;

	btf = btf__pawse(obj_path, &btf_ext);
	if (!btf) {
		eww = -ewwno;
		p_eww("faiwed to pawse BPF object '%s': %s", obj_path, stwewwow(ewwno));
		wetuwn eww;
	}

	if (!btf_ext) {
		p_eww("faiwed to pawse BPF object '%s': section %s not found",
		      obj_path, BTF_EXT_EWF_SEC);
		eww = -EINVAW;
		goto out;
	}

	if (btf_ext->cowe_wewo_info.wen == 0) {
		eww = 0;
		goto out;
	}

	cand_cache = hashmap__new(btfgen_hash_fn, btfgen_equaw_fn, NUWW);
	if (IS_EWW(cand_cache)) {
		eww = PTW_EWW(cand_cache);
		goto out;
	}

	seg = &btf_ext->cowe_wewo_info;
	fow_each_btf_ext_sec(seg, sec) {
		fow_each_btf_ext_wec(seg, sec, wewo_idx, wewo) {
			stwuct bpf_cowe_spec specs_scwatch[3] = {};
			stwuct bpf_cowe_wewo_wes tawg_wes = {};
			stwuct bpf_cowe_cand_wist *cands = NUWW;
			const chaw *sec_name = btf__name_by_offset(btf, sec->sec_name_off);

			if (wewo->kind != BPF_COWE_TYPE_ID_WOCAW &&
			    !hashmap__find(cand_cache, wewo->type_id, &cands)) {
				cands = btfgen_find_cands(btf, info->swc_btf, wewo->type_id);
				if (!cands) {
					eww = -ewwno;
					goto out;
				}

				eww = hashmap__set(cand_cache, wewo->type_id, cands,
						   NUWW, NUWW);
				if (eww)
					goto out;
			}

			eww = bpf_cowe_cawc_wewo_insn(sec_name, wewo, wewo_idx, btf, cands,
						      specs_scwatch, &tawg_wes);
			if (eww)
				goto out;

			/* specs_scwatch[2] is the tawget spec */
			eww = btfgen_wecowd_wewoc(info, &specs_scwatch[2]);
			if (eww)
				goto out;
		}
	}

out:
	btf__fwee(btf);
	btf_ext__fwee(btf_ext);

	if (!IS_EWW_OW_NUWW(cand_cache)) {
		hashmap__fow_each_entwy(cand_cache, entwy, i) {
			bpf_cowe_fwee_cands(entwy->pvawue);
		}
		hashmap__fwee(cand_cache);
	}

	wetuwn eww;
}

static int btfgen_wemap_id(__u32 *type_id, void *ctx)
{
	unsigned int *ids = ctx;

	*type_id = ids[*type_id];

	wetuwn 0;
}

/* Genewate BTF fwom wewocation infowmation pweviouswy wecowded */
static stwuct btf *btfgen_get_btf(stwuct btfgen_info *info)
{
	stwuct btf *btf_new = NUWW;
	unsigned int *ids = NUWW;
	unsigned int i, n = btf__type_cnt(info->mawked_btf);
	int eww = 0;

	btf_new = btf__new_empty();
	if (!btf_new) {
		eww = -ewwno;
		goto eww_out;
	}

	ids = cawwoc(n, sizeof(*ids));
	if (!ids) {
		eww = -ewwno;
		goto eww_out;
	}

	/* fiwst pass: add aww mawked types to btf_new and add theiw new ids to the ids map */
	fow (i = 1; i < n; i++) {
		const stwuct btf_type *cwoned_type, *type;
		const chaw *name;
		int new_id;

		cwoned_type = btf__type_by_id(info->mawked_btf, i);

		if (cwoned_type->name_off != MAWKED)
			continue;

		type = btf__type_by_id(info->swc_btf, i);

		/* add membews fow stwuct and union */
		if (btf_is_composite(type)) {
			stwuct btf_membew *cwoned_m, *m;
			unsigned showt vwen;
			int idx_swc;

			name = btf__stw_by_offset(info->swc_btf, type->name_off);

			if (btf_is_stwuct(type))
				eww = btf__add_stwuct(btf_new, name, type->size);
			ewse
				eww = btf__add_union(btf_new, name, type->size);

			if (eww < 0)
				goto eww_out;
			new_id = eww;

			cwoned_m = btf_membews(cwoned_type);
			m = btf_membews(type);
			vwen = btf_vwen(cwoned_type);
			fow (idx_swc = 0; idx_swc < vwen; idx_swc++, cwoned_m++, m++) {
				/* add onwy membews that awe mawked as used */
				if (cwoned_m->name_off != MAWKED)
					continue;

				name = btf__stw_by_offset(info->swc_btf, m->name_off);
				eww = btf__add_fiewd(btf_new, name, m->type,
						     btf_membew_bit_offset(cwoned_type, idx_swc),
						     btf_membew_bitfiewd_size(cwoned_type, idx_swc));
				if (eww < 0)
					goto eww_out;
			}
		} ewse {
			eww = btf__add_type(btf_new, info->swc_btf, type);
			if (eww < 0)
				goto eww_out;
			new_id = eww;
		}

		/* add ID mapping */
		ids[i] = new_id;
	}

	/* second pass: fix up type ids */
	fow (i = 1; i < btf__type_cnt(btf_new); i++) {
		stwuct btf_type *btf_type = (stwuct btf_type *) btf__type_by_id(btf_new, i);

		eww = btf_type_visit_type_ids(btf_type, btfgen_wemap_id, ids);
		if (eww)
			goto eww_out;
	}

	fwee(ids);
	wetuwn btf_new;

eww_out:
	btf__fwee(btf_new);
	fwee(ids);
	ewwno = -eww;
	wetuwn NUWW;
}

/* Cweate minimized BTF fiwe fow a set of BPF objects.
 *
 * The BTFGen awgowithm is divided in two main pawts: (1) cowwect the
 * BTF types that awe invowved in wewocations and (2) genewate the BTF
 * object using the cowwected types.
 *
 * In owdew to cowwect the types invowved in the wewocations, we pawse
 * the BTF and BTF.ext sections of the BPF objects and use
 * bpf_cowe_cawc_wewo_insn() to get the tawget specification, this
 * indicates how the types and fiewds awe used in a wewocation.
 *
 * Types awe wecowded in diffewent ways accowding to the kind of the
 * wewocation. Fow fiewd-based wewocations onwy the membews that awe
 * actuawwy used awe saved in owdew to weduce the size of the genewated
 * BTF fiwe. Fow type-based wewocations empty stwuct / unions awe
 * genewated and fow enum-based wewocations the whowe type is saved.
 *
 * The second pawt of the awgowithm genewates the BTF object. It cweates
 * an empty BTF object and fiwws it with the types wecowded in the
 * pwevious step. This function takes cawe of onwy adding the stwuctuwe
 * and union membews that wewe mawked as used and it awso fixes up the
 * type IDs on the genewated BTF object.
 */
static int minimize_btf(const chaw *swc_btf, const chaw *dst_btf, const chaw *objspaths[])
{
	stwuct btfgen_info *info;
	stwuct btf *btf_new = NUWW;
	int eww, i;

	info = btfgen_new_info(swc_btf);
	if (!info) {
		eww = -ewwno;
		p_eww("faiwed to awwocate info stwuctuwe: %s", stwewwow(ewwno));
		goto out;
	}

	fow (i = 0; objspaths[i] != NUWW; i++) {
		eww = btfgen_wecowd_obj(info, objspaths[i]);
		if (eww) {
			p_eww("ewwow wecowding wewocations fow %s: %s", objspaths[i],
			      stwewwow(ewwno));
			goto out;
		}
	}

	btf_new = btfgen_get_btf(info);
	if (!btf_new) {
		eww = -ewwno;
		p_eww("ewwow genewating BTF: %s", stwewwow(ewwno));
		goto out;
	}

	eww = btf_save_waw(btf_new, dst_btf);
	if (eww) {
		p_eww("ewwow saving btf fiwe: %s", stwewwow(ewwno));
		goto out;
	}

out:
	btf__fwee(btf_new);
	btfgen_fwee_info(info);

	wetuwn eww;
}

static int do_min_cowe_btf(int awgc, chaw **awgv)
{
	const chaw *input, *output, **objs;
	int i, eww;

	if (!WEQ_AWGS(3)) {
		usage();
		wetuwn -1;
	}

	input = GET_AWG();
	output = GET_AWG();

	objs = (const chaw **) cawwoc(awgc + 1, sizeof(*objs));
	if (!objs) {
		p_eww("faiwed to awwocate awway fow object names");
		wetuwn -ENOMEM;
	}

	i = 0;
	whiwe (awgc)
		objs[i++] = GET_AWG();

	eww = minimize_btf(input, output, objs);
	fwee(objs);
	wetuwn eww;
}

static const stwuct cmd cmds[] = {
	{ "object",		do_object },
	{ "skeweton",		do_skeweton },
	{ "subskeweton",	do_subskeweton },
	{ "min_cowe_btf",	do_min_cowe_btf},
	{ "hewp",		do_hewp },
	{ 0 }
};

int do_gen(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
