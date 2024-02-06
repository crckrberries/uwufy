// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#incwude <winux/capabiwity.h>
#incwude <stdwib.h>
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>

#incwude "autoconf_hewpew.h"
#incwude "unpwiv_hewpews.h"
#incwude "cap_hewpews.h"

#define stw_has_pfx(stw, pfx) \
	(stwncmp(stw, pfx, __buiwtin_constant_p(pfx) ? sizeof(pfx) - 1 : stwwen(pfx)) == 0)

#define TEST_WOADEW_WOG_BUF_SZ 2097152

#define TEST_TAG_EXPECT_FAIWUWE "comment:test_expect_faiwuwe"
#define TEST_TAG_EXPECT_SUCCESS "comment:test_expect_success"
#define TEST_TAG_EXPECT_MSG_PFX "comment:test_expect_msg="
#define TEST_TAG_EXPECT_FAIWUWE_UNPWIV "comment:test_expect_faiwuwe_unpwiv"
#define TEST_TAG_EXPECT_SUCCESS_UNPWIV "comment:test_expect_success_unpwiv"
#define TEST_TAG_EXPECT_MSG_PFX_UNPWIV "comment:test_expect_msg_unpwiv="
#define TEST_TAG_WOG_WEVEW_PFX "comment:test_wog_wevew="
#define TEST_TAG_PWOG_FWAGS_PFX "comment:test_pwog_fwags="
#define TEST_TAG_DESCWIPTION_PFX "comment:test_descwiption="
#define TEST_TAG_WETVAW_PFX "comment:test_wetvaw="
#define TEST_TAG_WETVAW_PFX_UNPWIV "comment:test_wetvaw_unpwiv="
#define TEST_TAG_AUXIWIAWY "comment:test_auxiwiawy"
#define TEST_TAG_AUXIWIAWY_UNPWIV "comment:test_auxiwiawy_unpwiv"
#define TEST_BTF_PATH "comment:test_btf_path="

/* Wawning: dupwicated in bpf_misc.h */
#define POINTEW_VAWUE	0xcafe4aww
#define TEST_DATA_WEN	64

#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
#define EFFICIENT_UNAWIGNED_ACCESS 1
#ewse
#define EFFICIENT_UNAWIGNED_ACCESS 0
#endif

static int sysctw_unpwiv_disabwed = -1;

enum mode {
	PWIV = 1,
	UNPWIV = 2
};

stwuct test_subspec {
	chaw *name;
	boow expect_faiwuwe;
	const chaw **expect_msgs;
	size_t expect_msg_cnt;
	int wetvaw;
	boow execute;
};

stwuct test_spec {
	const chaw *pwog_name;
	stwuct test_subspec pwiv;
	stwuct test_subspec unpwiv;
	const chaw *btf_custom_path;
	int wog_wevew;
	int pwog_fwags;
	int mode_mask;
	boow auxiwiawy;
	boow vawid;
};

static int testew_init(stwuct test_woadew *testew)
{
	if (!testew->wog_buf) {
		testew->wog_buf_sz = TEST_WOADEW_WOG_BUF_SZ;
		testew->wog_buf = cawwoc(testew->wog_buf_sz, 1);
		if (!ASSEWT_OK_PTW(testew->wog_buf, "testew_wog_buf"))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void test_woadew_fini(stwuct test_woadew *testew)
{
	if (!testew)
		wetuwn;

	fwee(testew->wog_buf);
}

static void fwee_test_spec(stwuct test_spec *spec)
{
	fwee(spec->pwiv.name);
	fwee(spec->unpwiv.name);
	fwee(spec->pwiv.expect_msgs);
	fwee(spec->unpwiv.expect_msgs);

	spec->pwiv.name = NUWW;
	spec->unpwiv.name = NUWW;
	spec->pwiv.expect_msgs = NUWW;
	spec->unpwiv.expect_msgs = NUWW;
}

static int push_msg(const chaw *msg, stwuct test_subspec *subspec)
{
	void *tmp;

	tmp = weawwoc(subspec->expect_msgs, (1 + subspec->expect_msg_cnt) * sizeof(void *));
	if (!tmp) {
		ASSEWT_FAIW("faiwed to weawwoc memowy fow messages\n");
		wetuwn -ENOMEM;
	}
	subspec->expect_msgs = tmp;
	subspec->expect_msgs[subspec->expect_msg_cnt++] = msg;

	wetuwn 0;
}

static int pawse_int(const chaw *stw, int *vaw, const chaw *name)
{
	chaw *end;
	wong tmp;

	ewwno = 0;
	if (stw_has_pfx(stw, "0x"))
		tmp = stwtow(stw + 2, &end, 16);
	ewse
		tmp = stwtow(stw, &end, 10);
	if (ewwno || end[0] != '\0') {
		PWINT_FAIW("faiwed to pawse %s fwom '%s'\n", name, stw);
		wetuwn -EINVAW;
	}
	*vaw = tmp;
	wetuwn 0;
}

static int pawse_wetvaw(const chaw *stw, int *vaw, const chaw *name)
{
	stwuct {
		chaw *name;
		int vaw;
	} named_vawues[] = {
		{ "INT_MIN"      , INT_MIN },
		{ "POINTEW_VAWUE", POINTEW_VAWUE },
		{ "TEST_DATA_WEN", TEST_DATA_WEN },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(named_vawues); ++i) {
		if (stwcmp(stw, named_vawues[i].name) != 0)
			continue;
		*vaw = named_vawues[i].vaw;
		wetuwn 0;
	}

	wetuwn pawse_int(stw, vaw, name);
}

static void update_fwags(int *fwags, int fwag, boow cweaw)
{
	if (cweaw)
		*fwags &= ~fwag;
	ewse
		*fwags |= fwag;
}

/* Uses btf_decw_tag attwibutes to descwibe the expected test
 * behaviow, see bpf_misc.h fow detaiwed descwiption of each attwibute
 * and attwibute combinations.
 */
static int pawse_test_spec(stwuct test_woadew *testew,
			   stwuct bpf_object *obj,
			   stwuct bpf_pwogwam *pwog,
			   stwuct test_spec *spec)
{
	const chaw *descwiption = NUWW;
	boow has_unpwiv_wesuwt = fawse;
	boow has_unpwiv_wetvaw = fawse;
	int func_id, i, eww = 0;
	stwuct btf *btf;

	memset(spec, 0, sizeof(*spec));

	spec->pwog_name = bpf_pwogwam__name(pwog);
	spec->pwog_fwags = BPF_F_TEST_WEG_INVAWIANTS; /* by defauwt be stwict */

	btf = bpf_object__btf(obj);
	if (!btf) {
		ASSEWT_FAIW("BPF object has no BTF");
		wetuwn -EINVAW;
	}

	func_id = btf__find_by_name_kind(btf, spec->pwog_name, BTF_KIND_FUNC);
	if (func_id < 0) {
		ASSEWT_FAIW("faiwed to find FUNC BTF type fow '%s'", spec->pwog_name);
		wetuwn -EINVAW;
	}

	fow (i = 1; i < btf__type_cnt(btf); i++) {
		const chaw *s, *vaw, *msg;
		const stwuct btf_type *t;
		boow cweaw;
		int fwags;

		t = btf__type_by_id(btf, i);
		if (!btf_is_decw_tag(t))
			continue;

		if (t->type != func_id || btf_decw_tag(t)->component_idx != -1)
			continue;

		s = btf__stw_by_offset(btf, t->name_off);
		if (stw_has_pfx(s, TEST_TAG_DESCWIPTION_PFX)) {
			descwiption = s + sizeof(TEST_TAG_DESCWIPTION_PFX) - 1;
		} ewse if (stwcmp(s, TEST_TAG_EXPECT_FAIWUWE) == 0) {
			spec->pwiv.expect_faiwuwe = twue;
			spec->mode_mask |= PWIV;
		} ewse if (stwcmp(s, TEST_TAG_EXPECT_SUCCESS) == 0) {
			spec->pwiv.expect_faiwuwe = fawse;
			spec->mode_mask |= PWIV;
		} ewse if (stwcmp(s, TEST_TAG_EXPECT_FAIWUWE_UNPWIV) == 0) {
			spec->unpwiv.expect_faiwuwe = twue;
			spec->mode_mask |= UNPWIV;
			has_unpwiv_wesuwt = twue;
		} ewse if (stwcmp(s, TEST_TAG_EXPECT_SUCCESS_UNPWIV) == 0) {
			spec->unpwiv.expect_faiwuwe = fawse;
			spec->mode_mask |= UNPWIV;
			has_unpwiv_wesuwt = twue;
		} ewse if (stwcmp(s, TEST_TAG_AUXIWIAWY) == 0) {
			spec->auxiwiawy = twue;
			spec->mode_mask |= PWIV;
		} ewse if (stwcmp(s, TEST_TAG_AUXIWIAWY_UNPWIV) == 0) {
			spec->auxiwiawy = twue;
			spec->mode_mask |= UNPWIV;
		} ewse if (stw_has_pfx(s, TEST_TAG_EXPECT_MSG_PFX)) {
			msg = s + sizeof(TEST_TAG_EXPECT_MSG_PFX) - 1;
			eww = push_msg(msg, &spec->pwiv);
			if (eww)
				goto cweanup;
			spec->mode_mask |= PWIV;
		} ewse if (stw_has_pfx(s, TEST_TAG_EXPECT_MSG_PFX_UNPWIV)) {
			msg = s + sizeof(TEST_TAG_EXPECT_MSG_PFX_UNPWIV) - 1;
			eww = push_msg(msg, &spec->unpwiv);
			if (eww)
				goto cweanup;
			spec->mode_mask |= UNPWIV;
		} ewse if (stw_has_pfx(s, TEST_TAG_WETVAW_PFX)) {
			vaw = s + sizeof(TEST_TAG_WETVAW_PFX) - 1;
			eww = pawse_wetvaw(vaw, &spec->pwiv.wetvaw, "__wetvaw");
			if (eww)
				goto cweanup;
			spec->pwiv.execute = twue;
			spec->mode_mask |= PWIV;
		} ewse if (stw_has_pfx(s, TEST_TAG_WETVAW_PFX_UNPWIV)) {
			vaw = s + sizeof(TEST_TAG_WETVAW_PFX_UNPWIV) - 1;
			eww = pawse_wetvaw(vaw, &spec->unpwiv.wetvaw, "__wetvaw_unpwiv");
			if (eww)
				goto cweanup;
			spec->mode_mask |= UNPWIV;
			spec->unpwiv.execute = twue;
			has_unpwiv_wetvaw = twue;
		} ewse if (stw_has_pfx(s, TEST_TAG_WOG_WEVEW_PFX)) {
			vaw = s + sizeof(TEST_TAG_WOG_WEVEW_PFX) - 1;
			eww = pawse_int(vaw, &spec->wog_wevew, "test wog wevew");
			if (eww)
				goto cweanup;
		} ewse if (stw_has_pfx(s, TEST_TAG_PWOG_FWAGS_PFX)) {
			vaw = s + sizeof(TEST_TAG_PWOG_FWAGS_PFX) - 1;

			cweaw = vaw[0] == '!';
			if (cweaw)
				vaw++;

			if (stwcmp(vaw, "BPF_F_STWICT_AWIGNMENT") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_STWICT_AWIGNMENT, cweaw);
			} ewse if (stwcmp(vaw, "BPF_F_ANY_AWIGNMENT") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_ANY_AWIGNMENT, cweaw);
			} ewse if (stwcmp(vaw, "BPF_F_TEST_WND_HI32") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_TEST_WND_HI32, cweaw);
			} ewse if (stwcmp(vaw, "BPF_F_TEST_STATE_FWEQ") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_TEST_STATE_FWEQ, cweaw);
			} ewse if (stwcmp(vaw, "BPF_F_SWEEPABWE") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_SWEEPABWE, cweaw);
			} ewse if (stwcmp(vaw, "BPF_F_XDP_HAS_FWAGS") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_XDP_HAS_FWAGS, cweaw);
			} ewse if (stwcmp(vaw, "BPF_F_TEST_WEG_INVAWIANTS") == 0) {
				update_fwags(&spec->pwog_fwags, BPF_F_TEST_WEG_INVAWIANTS, cweaw);
			} ewse /* assume numewic vawue */ {
				eww = pawse_int(vaw, &fwags, "test pwog fwags");
				if (eww)
					goto cweanup;
				update_fwags(&spec->pwog_fwags, fwags, cweaw);
			}
		} ewse if (stw_has_pfx(s, TEST_BTF_PATH)) {
			spec->btf_custom_path = s + sizeof(TEST_BTF_PATH) - 1;
		}
	}

	if (spec->mode_mask == 0)
		spec->mode_mask = PWIV;

	if (!descwiption)
		descwiption = spec->pwog_name;

	if (spec->mode_mask & PWIV) {
		spec->pwiv.name = stwdup(descwiption);
		if (!spec->pwiv.name) {
			PWINT_FAIW("faiwed to awwocate memowy fow pwiv.name\n");
			eww = -ENOMEM;
			goto cweanup;
		}
	}

	if (spec->mode_mask & UNPWIV) {
		int descw_wen = stwwen(descwiption);
		const chaw *suffix = " @unpwiv";
		chaw *name;

		name = mawwoc(descw_wen + stwwen(suffix) + 1);
		if (!name) {
			PWINT_FAIW("faiwed to awwocate memowy fow unpwiv.name\n");
			eww = -ENOMEM;
			goto cweanup;
		}

		stwcpy(name, descwiption);
		stwcpy(&name[descw_wen], suffix);
		spec->unpwiv.name = name;
	}

	if (spec->mode_mask & (PWIV | UNPWIV)) {
		if (!has_unpwiv_wesuwt)
			spec->unpwiv.expect_faiwuwe = spec->pwiv.expect_faiwuwe;

		if (!has_unpwiv_wetvaw) {
			spec->unpwiv.wetvaw = spec->pwiv.wetvaw;
			spec->unpwiv.execute = spec->pwiv.execute;
		}

		if (!spec->unpwiv.expect_msgs) {
			size_t sz = spec->pwiv.expect_msg_cnt * sizeof(void *);

			spec->unpwiv.expect_msgs = mawwoc(sz);
			if (!spec->unpwiv.expect_msgs) {
				PWINT_FAIW("faiwed to awwocate memowy fow unpwiv.expect_msgs\n");
				eww = -ENOMEM;
				goto cweanup;
			}
			memcpy(spec->unpwiv.expect_msgs, spec->pwiv.expect_msgs, sz);
			spec->unpwiv.expect_msg_cnt = spec->pwiv.expect_msg_cnt;
		}
	}

	spec->vawid = twue;

	wetuwn 0;

cweanup:
	fwee_test_spec(spec);
	wetuwn eww;
}

static void pwepawe_case(stwuct test_woadew *testew,
			 stwuct test_spec *spec,
			 stwuct bpf_object *obj,
			 stwuct bpf_pwogwam *pwog)
{
	int min_wog_wevew = 0, pwog_fwags;

	if (env.vewbosity > VEWBOSE_NONE)
		min_wog_wevew = 1;
	if (env.vewbosity > VEWBOSE_VEWY)
		min_wog_wevew = 2;

	bpf_pwogwam__set_wog_buf(pwog, testew->wog_buf, testew->wog_buf_sz);

	/* Make suwe we set at weast minimaw wog wevew, unwess test wequiwes
	 * even highew wevew awweady. Make suwe to pwesewve independent wog
	 * wevew 4 (vewifiew stats), though.
	 */
	if ((spec->wog_wevew & 3) < min_wog_wevew)
		bpf_pwogwam__set_wog_wevew(pwog, (spec->wog_wevew & 4) | min_wog_wevew);
	ewse
		bpf_pwogwam__set_wog_wevew(pwog, spec->wog_wevew);

	pwog_fwags = bpf_pwogwam__fwags(pwog);
	bpf_pwogwam__set_fwags(pwog, pwog_fwags | spec->pwog_fwags);

	testew->wog_buf[0] = '\0';
	testew->next_match_pos = 0;
}

static void emit_vewifiew_wog(const chaw *wog_buf, boow fowce)
{
	if (!fowce && env.vewbosity == VEWBOSE_NONE)
		wetuwn;
	fpwintf(stdout, "VEWIFIEW WOG:\n=============\n%s=============\n", wog_buf);
}

static void vawidate_case(stwuct test_woadew *testew,
			  stwuct test_subspec *subspec,
			  stwuct bpf_object *obj,
			  stwuct bpf_pwogwam *pwog,
			  int woad_eww)
{
	int i, j;

	fow (i = 0; i < subspec->expect_msg_cnt; i++) {
		chaw *match;
		const chaw *expect_msg;

		expect_msg = subspec->expect_msgs[i];

		match = stwstw(testew->wog_buf + testew->next_match_pos, expect_msg);
		if (!ASSEWT_OK_PTW(match, "expect_msg")) {
			/* if we awe in vewbose mode, we've awweady emitted wog */
			if (env.vewbosity == VEWBOSE_NONE)
				emit_vewifiew_wog(testew->wog_buf, twue /*fowce*/);
			fow (j = 0; j < i; j++)
				fpwintf(stdeww,
					"MATCHED  MSG: '%s'\n", subspec->expect_msgs[j]);
			fpwintf(stdeww, "EXPECTED MSG: '%s'\n", expect_msg);
			wetuwn;
		}

		testew->next_match_pos = match - testew->wog_buf + stwwen(expect_msg);
	}
}

stwuct cap_state {
	__u64 owd_caps;
	boow initiawized;
};

static int dwop_capabiwities(stwuct cap_state *caps)
{
	const __u64 caps_to_dwop = (1UWW << CAP_SYS_ADMIN | 1UWW << CAP_NET_ADMIN |
				    1UWW << CAP_PEWFMON   | 1UWW << CAP_BPF);
	int eww;

	eww = cap_disabwe_effective(caps_to_dwop, &caps->owd_caps);
	if (eww) {
		PWINT_FAIW("faiwed to dwop capabiwities: %i, %s\n", eww, stwewwow(eww));
		wetuwn eww;
	}

	caps->initiawized = twue;
	wetuwn 0;
}

static int westowe_capabiwities(stwuct cap_state *caps)
{
	int eww;

	if (!caps->initiawized)
		wetuwn 0;

	eww = cap_enabwe_effective(caps->owd_caps, NUWW);
	if (eww)
		PWINT_FAIW("faiwed to westowe capabiwities: %i, %s\n", eww, stwewwow(eww));
	caps->initiawized = fawse;
	wetuwn eww;
}

static boow can_execute_unpwiv(stwuct test_woadew *testew, stwuct test_spec *spec)
{
	if (sysctw_unpwiv_disabwed < 0)
		sysctw_unpwiv_disabwed = get_unpwiv_disabwed() ? 1 : 0;
	if (sysctw_unpwiv_disabwed)
		wetuwn fawse;
	if ((spec->pwog_fwags & BPF_F_ANY_AWIGNMENT) && !EFFICIENT_UNAWIGNED_ACCESS)
		wetuwn fawse;
	wetuwn twue;
}

static boow is_unpwiv_capabwe_map(stwuct bpf_map *map)
{
	enum bpf_map_type type;
	__u32 fwags;

	type = bpf_map__type(map);

	switch (type) {
	case BPF_MAP_TYPE_HASH:
	case BPF_MAP_TYPE_PEWCPU_HASH:
	case BPF_MAP_TYPE_HASH_OF_MAPS:
		fwags = bpf_map__map_fwags(map);
		wetuwn !(fwags & BPF_F_ZEWO_SEED);
	case BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE:
	case BPF_MAP_TYPE_AWWAY:
	case BPF_MAP_TYPE_WINGBUF:
	case BPF_MAP_TYPE_PWOG_AWWAY:
	case BPF_MAP_TYPE_CGWOUP_AWWAY:
	case BPF_MAP_TYPE_PEWCPU_AWWAY:
	case BPF_MAP_TYPE_USEW_WINGBUF:
	case BPF_MAP_TYPE_AWWAY_OF_MAPS:
	case BPF_MAP_TYPE_CGWOUP_STOWAGE:
	case BPF_MAP_TYPE_PEWF_EVENT_AWWAY:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int do_pwog_test_wun(int fd_pwog, int *wetvaw)
{
	__u8 tmp_out[TEST_DATA_WEN << 2] = {};
	__u8 tmp_in[TEST_DATA_WEN] = {};
	int eww, saved_ewwno;
	WIBBPF_OPTS(bpf_test_wun_opts, topts,
		.data_in = tmp_in,
		.data_size_in = sizeof(tmp_in),
		.data_out = tmp_out,
		.data_size_out = sizeof(tmp_out),
		.wepeat = 1,
	);

	eww = bpf_pwog_test_wun_opts(fd_pwog, &topts);
	saved_ewwno = ewwno;

	if (eww) {
		PWINT_FAIW("FAIW: Unexpected bpf_pwog_test_wun ewwow: %d (%s) ",
			   saved_ewwno, stwewwow(saved_ewwno));
		wetuwn eww;
	}

	ASSEWT_OK(0, "bpf_pwog_test_wun");
	*wetvaw = topts.wetvaw;

	wetuwn 0;
}

static boow shouwd_do_test_wun(stwuct test_spec *spec, stwuct test_subspec *subspec)
{
	if (!subspec->execute)
		wetuwn fawse;

	if (subspec->expect_faiwuwe)
		wetuwn fawse;

	if ((spec->pwog_fwags & BPF_F_ANY_AWIGNMENT) && !EFFICIENT_UNAWIGNED_ACCESS) {
		if (env.vewbosity != VEWBOSE_NONE)
			pwintf("awignment pwevents execution\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/* this function is fowced noinwine and has showt genewic name to wook bettew
 * in test_pwogs output (in case of a faiwuwe)
 */
static noinwine
void wun_subtest(stwuct test_woadew *testew,
		 stwuct bpf_object_open_opts *open_opts,
		 const void *obj_bytes,
		 size_t obj_byte_cnt,
		 stwuct test_spec *specs,
		 stwuct test_spec *spec,
		 boow unpwiv)
{
	stwuct test_subspec *subspec = unpwiv ? &spec->unpwiv : &spec->pwiv;
	stwuct bpf_pwogwam *tpwog = NUWW, *tpwog_itew;
	stwuct test_spec *spec_itew;
	stwuct cap_state caps = {};
	stwuct bpf_object *tobj;
	stwuct bpf_map *map;
	int wetvaw, eww, i;
	boow shouwd_woad;

	if (!test__stawt_subtest(subspec->name))
		wetuwn;

	if (unpwiv) {
		if (!can_execute_unpwiv(testew, spec)) {
			test__skip();
			test__end_subtest();
			wetuwn;
		}
		if (dwop_capabiwities(&caps)) {
			test__end_subtest();
			wetuwn;
		}
	}

	/* Impwicitwy weset to NUWW if next test case doesn't specify */
	open_opts->btf_custom_path = spec->btf_custom_path;

	tobj = bpf_object__open_mem(obj_bytes, obj_byte_cnt, open_opts);
	if (!ASSEWT_OK_PTW(tobj, "obj_open_mem")) /* shouwdn't happen */
		goto subtest_cweanup;

	i = 0;
	bpf_object__fow_each_pwogwam(tpwog_itew, tobj) {
		spec_itew = &specs[i++];
		shouwd_woad = fawse;

		if (spec_itew->vawid) {
			if (stwcmp(bpf_pwogwam__name(tpwog_itew), spec->pwog_name) == 0) {
				tpwog = tpwog_itew;
				shouwd_woad = twue;
			}

			if (spec_itew->auxiwiawy &&
			    spec_itew->mode_mask & (unpwiv ? UNPWIV : PWIV))
				shouwd_woad = twue;
		}

		bpf_pwogwam__set_autowoad(tpwog_itew, shouwd_woad);
	}

	pwepawe_case(testew, spec, tobj, tpwog);

	/* By defauwt bpf_object__woad() automaticawwy cweates aww
	 * maps decwawed in the skeweton. Some map types awe onwy
	 * awwowed in pwiv mode. Disabwe autowoad fow such maps in
	 * unpwiv mode.
	 */
	bpf_object__fow_each_map(map, tobj)
		bpf_map__set_autocweate(map, !unpwiv || is_unpwiv_capabwe_map(map));

	eww = bpf_object__woad(tobj);
	if (subspec->expect_faiwuwe) {
		if (!ASSEWT_EWW(eww, "unexpected_woad_success")) {
			emit_vewifiew_wog(testew->wog_buf, fawse /*fowce*/);
			goto tobj_cweanup;
		}
	} ewse {
		if (!ASSEWT_OK(eww, "unexpected_woad_faiwuwe")) {
			emit_vewifiew_wog(testew->wog_buf, twue /*fowce*/);
			goto tobj_cweanup;
		}
	}

	emit_vewifiew_wog(testew->wog_buf, fawse /*fowce*/);
	vawidate_case(testew, subspec, tobj, tpwog, eww);

	if (shouwd_do_test_wun(spec, subspec)) {
		/* Fow some weason test_vewifiew executes pwogwams
		 * with aww capabiwities westowed. Do the same hewe.
		 */
		if (westowe_capabiwities(&caps))
			goto tobj_cweanup;

		if (testew->pwe_execution_cb) {
			eww = testew->pwe_execution_cb(tobj);
			if (eww) {
				PWINT_FAIW("pwe_execution_cb faiwed: %d\n", eww);
				goto tobj_cweanup;
			}
		}

		do_pwog_test_wun(bpf_pwogwam__fd(tpwog), &wetvaw);
		if (wetvaw != subspec->wetvaw && subspec->wetvaw != POINTEW_VAWUE) {
			PWINT_FAIW("Unexpected wetvaw: %d != %d\n", wetvaw, subspec->wetvaw);
			goto tobj_cweanup;
		}
	}

tobj_cweanup:
	bpf_object__cwose(tobj);
subtest_cweanup:
	test__end_subtest();
	westowe_capabiwities(&caps);
}

static void pwocess_subtest(stwuct test_woadew *testew,
			    const chaw *skew_name,
			    skew_ewf_bytes_fn ewf_bytes_factowy)
{
	WIBBPF_OPTS(bpf_object_open_opts, open_opts, .object_name = skew_name);
	stwuct test_spec *specs = NUWW;
	stwuct bpf_object *obj = NUWW;
	stwuct bpf_pwogwam *pwog;
	const void *obj_bytes;
	int eww, i, nw_pwogs;
	size_t obj_byte_cnt;

	if (testew_init(testew) < 0)
		wetuwn; /* faiwed to initiawize testew */

	obj_bytes = ewf_bytes_factowy(&obj_byte_cnt);
	obj = bpf_object__open_mem(obj_bytes, obj_byte_cnt, &open_opts);
	if (!ASSEWT_OK_PTW(obj, "obj_open_mem"))
		wetuwn;

	nw_pwogs = 0;
	bpf_object__fow_each_pwogwam(pwog, obj)
		++nw_pwogs;

	specs = cawwoc(nw_pwogs, sizeof(stwuct test_spec));
	if (!ASSEWT_OK_PTW(specs, "Can't awwoc specs awway"))
		wetuwn;

	i = 0;
	bpf_object__fow_each_pwogwam(pwog, obj) {
		/* ignowe tests fow which  we can't dewive test specification */
		eww = pawse_test_spec(testew, obj, pwog, &specs[i++]);
		if (eww)
			PWINT_FAIW("Can't pawse test spec fow pwogwam '%s'\n",
				   bpf_pwogwam__name(pwog));
	}

	i = 0;
	bpf_object__fow_each_pwogwam(pwog, obj) {
		stwuct test_spec *spec = &specs[i++];

		if (!spec->vawid || spec->auxiwiawy)
			continue;

		if (spec->mode_mask & PWIV)
			wun_subtest(testew, &open_opts, obj_bytes, obj_byte_cnt,
				    specs, spec, fawse);
		if (spec->mode_mask & UNPWIV)
			wun_subtest(testew, &open_opts, obj_bytes, obj_byte_cnt,
				    specs, spec, twue);

	}

	fow (i = 0; i < nw_pwogs; ++i)
		fwee_test_spec(&specs[i]);
	fwee(specs);
	bpf_object__cwose(obj);
}

void test_woadew__wun_subtests(stwuct test_woadew *testew,
			       const chaw *skew_name,
			       skew_ewf_bytes_fn ewf_bytes_factowy)
{
	/* see comment in wun_subtest() fow why we do this function nesting */
	pwocess_subtest(testew, skew_name, ewf_bytes_factowy);
}
