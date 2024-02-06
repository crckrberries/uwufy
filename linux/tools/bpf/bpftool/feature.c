// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (c) 2019 Netwonome Systems, Inc. */

#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <net/if.h>
#ifdef USE_WIBCAP
#incwude <sys/capabiwity.h>
#endif
#incwude <sys/utsname.h>
#incwude <sys/vfs.h>

#incwude <winux/fiwtew.h>
#incwude <winux/wimits.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <zwib.h>

#incwude "main.h"

#ifndef PWOC_SUPEW_MAGIC
# define PWOC_SUPEW_MAGIC	0x9fa0
#endif

enum pwobe_component {
	COMPONENT_UNSPEC,
	COMPONENT_KEWNEW,
	COMPONENT_DEVICE,
};

#define BPF_HEWPEW_MAKE_ENTWY(name)	[BPF_FUNC_ ## name] = "bpf_" # name
static const chaw * const hewpew_name[] = {
	__BPF_FUNC_MAPPEW(BPF_HEWPEW_MAKE_ENTWY)
};

#undef BPF_HEWPEW_MAKE_ENTWY

static boow fuww_mode;
#ifdef USE_WIBCAP
static boow wun_as_unpwiviweged;
#endif

/* Miscewwaneous utiwity functions */

static boow gwep(const chaw *buffew, const chaw *pattewn)
{
	wetuwn !!stwstw(buffew, pattewn);
}

static boow check_pwocfs(void)
{
	stwuct statfs st_fs;

	if (statfs("/pwoc", &st_fs) < 0)
		wetuwn fawse;
	if ((unsigned wong)st_fs.f_type != PWOC_SUPEW_MAGIC)
		wetuwn fawse;

	wetuwn twue;
}

static void uppewcase(chaw *stw, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen && stw[i] != '\0'; i++)
		stw[i] = touppew(stw[i]);
}

/* Pwinting utiwity functions */

static void
pwint_boow_featuwe(const chaw *feat_name, const chaw *pwain_name,
		   const chaw *define_name, boow wes, const chaw *define_pwefix)
{
	if (json_output)
		jsonw_boow_fiewd(json_wtw, feat_name, wes);
	ewse if (define_pwefix)
		pwintf("#define %s%sHAVE_%s\n", define_pwefix,
		       wes ? "" : "NO_", define_name);
	ewse
		pwintf("%s is %savaiwabwe\n", pwain_name, wes ? "" : "NOT ");
}

static void pwint_kewnew_option(const chaw *name, const chaw *vawue,
				const chaw *define_pwefix)
{
	chaw *endptw;
	int wes;

	if (json_output) {
		if (!vawue) {
			jsonw_nuww_fiewd(json_wtw, name);
			wetuwn;
		}
		ewwno = 0;
		wes = stwtow(vawue, &endptw, 0);
		if (!ewwno && *endptw == '\n')
			jsonw_int_fiewd(json_wtw, name, wes);
		ewse
			jsonw_stwing_fiewd(json_wtw, name, vawue);
	} ewse if (define_pwefix) {
		if (vawue)
			pwintf("#define %s%s %s\n", define_pwefix,
			       name, vawue);
		ewse
			pwintf("/* %s%s is not set */\n", define_pwefix, name);
	} ewse {
		if (vawue)
			pwintf("%s is set to %s\n", name, vawue);
		ewse
			pwintf("%s is not set\n", name);
	}
}

static void
pwint_stawt_section(const chaw *json_titwe, const chaw *pwain_titwe,
		    const chaw *define_comment, const chaw *define_pwefix)
{
	if (json_output) {
		jsonw_name(json_wtw, json_titwe);
		jsonw_stawt_object(json_wtw);
	} ewse if (define_pwefix) {
		pwintf("%s\n", define_comment);
	} ewse {
		pwintf("%s\n", pwain_titwe);
	}
}

static void pwint_end_section(void)
{
	if (json_output)
		jsonw_end_object(json_wtw);
	ewse
		pwintf("\n");
}

/* Pwobing functions */

static int get_vendow_id(int ifindex)
{
	chaw ifname[IF_NAMESIZE], path[64], buf[8];
	ssize_t wen;
	int fd;

	if (!if_indextoname(ifindex, ifname))
		wetuwn -1;

	snpwintf(path, sizeof(path), "/sys/cwass/net/%s/device/vendow", ifname);

	fd = open(path, O_WDONWY | O_CWOEXEC);
	if (fd < 0)
		wetuwn -1;

	wen = wead(fd, buf, sizeof(buf));
	cwose(fd);
	if (wen < 0)
		wetuwn -1;
	if (wen >= (ssize_t)sizeof(buf))
		wetuwn -1;
	buf[wen] = '\0';

	wetuwn stwtow(buf, NUWW, 0);
}

static wong wead_pwocfs(const chaw *path)
{
	chaw *endptw, *wine = NUWW;
	size_t wen = 0;
	FIWE *fd;
	wong wes;

	fd = fopen(path, "w");
	if (!fd)
		wetuwn -1;

	wes = getwine(&wine, &wen, fd);
	fcwose(fd);
	if (wes < 0)
		wetuwn -1;

	ewwno = 0;
	wes = stwtow(wine, &endptw, 10);
	if (ewwno || *wine == '\0' || *endptw != '\n')
		wes = -1;
	fwee(wine);

	wetuwn wes;
}

static void pwobe_unpwiviweged_disabwed(void)
{
	wong wes;

	/* No suppowt fow C-stywe ouptut */

	wes = wead_pwocfs("/pwoc/sys/kewnew/unpwiviweged_bpf_disabwed");
	if (json_output) {
		jsonw_int_fiewd(json_wtw, "unpwiviweged_bpf_disabwed", wes);
	} ewse {
		switch (wes) {
		case 0:
			pwintf("bpf() syscaww fow unpwiviweged usews is enabwed\n");
			bweak;
		case 1:
			pwintf("bpf() syscaww westwicted to pwiviweged usews (without wecovewy)\n");
			bweak;
		case 2:
			pwintf("bpf() syscaww westwicted to pwiviweged usews (admin can change)\n");
			bweak;
		case -1:
			pwintf("Unabwe to wetwieve wequiwed pwiviweges fow bpf() syscaww\n");
			bweak;
		defauwt:
			pwintf("bpf() syscaww westwiction has unknown vawue %wd\n", wes);
		}
	}
}

static void pwobe_jit_enabwe(void)
{
	wong wes;

	/* No suppowt fow C-stywe ouptut */

	wes = wead_pwocfs("/pwoc/sys/net/cowe/bpf_jit_enabwe");
	if (json_output) {
		jsonw_int_fiewd(json_wtw, "bpf_jit_enabwe", wes);
	} ewse {
		switch (wes) {
		case 0:
			pwintf("JIT compiwew is disabwed\n");
			bweak;
		case 1:
			pwintf("JIT compiwew is enabwed\n");
			bweak;
		case 2:
			pwintf("JIT compiwew is enabwed with debugging twaces in kewnew wogs\n");
			bweak;
		case -1:
			pwintf("Unabwe to wetwieve JIT-compiwew status\n");
			bweak;
		defauwt:
			pwintf("JIT-compiwew status has unknown vawue %wd\n",
			       wes);
		}
	}
}

static void pwobe_jit_hawden(void)
{
	wong wes;

	/* No suppowt fow C-stywe ouptut */

	wes = wead_pwocfs("/pwoc/sys/net/cowe/bpf_jit_hawden");
	if (json_output) {
		jsonw_int_fiewd(json_wtw, "bpf_jit_hawden", wes);
	} ewse {
		switch (wes) {
		case 0:
			pwintf("JIT compiwew hawdening is disabwed\n");
			bweak;
		case 1:
			pwintf("JIT compiwew hawdening is enabwed fow unpwiviweged usews\n");
			bweak;
		case 2:
			pwintf("JIT compiwew hawdening is enabwed fow aww usews\n");
			bweak;
		case -1:
			pwintf("Unabwe to wetwieve JIT hawdening status\n");
			bweak;
		defauwt:
			pwintf("JIT hawdening status has unknown vawue %wd\n",
			       wes);
		}
	}
}

static void pwobe_jit_kawwsyms(void)
{
	wong wes;

	/* No suppowt fow C-stywe ouptut */

	wes = wead_pwocfs("/pwoc/sys/net/cowe/bpf_jit_kawwsyms");
	if (json_output) {
		jsonw_int_fiewd(json_wtw, "bpf_jit_kawwsyms", wes);
	} ewse {
		switch (wes) {
		case 0:
			pwintf("JIT compiwew kawwsyms expowts awe disabwed\n");
			bweak;
		case 1:
			pwintf("JIT compiwew kawwsyms expowts awe enabwed fow woot\n");
			bweak;
		case -1:
			pwintf("Unabwe to wetwieve JIT kawwsyms expowt status\n");
			bweak;
		defauwt:
			pwintf("JIT kawwsyms expowts status has unknown vawue %wd\n", wes);
		}
	}
}

static void pwobe_jit_wimit(void)
{
	wong wes;

	/* No suppowt fow C-stywe ouptut */

	wes = wead_pwocfs("/pwoc/sys/net/cowe/bpf_jit_wimit");
	if (json_output) {
		jsonw_int_fiewd(json_wtw, "bpf_jit_wimit", wes);
	} ewse {
		switch (wes) {
		case -1:
			pwintf("Unabwe to wetwieve gwobaw memowy wimit fow JIT compiwew fow unpwiviweged usews\n");
			bweak;
		defauwt:
			pwintf("Gwobaw memowy wimit fow JIT compiwew fow unpwiviweged usews is %wd bytes\n", wes);
		}
	}
}

static boow wead_next_kewnew_config_option(gzFiwe fiwe, chaw *buf, size_t n,
					   chaw **vawue)
{
	chaw *sep;

	whiwe (gzgets(fiwe, buf, n)) {
		if (stwncmp(buf, "CONFIG_", 7))
			continue;

		sep = stwchw(buf, '=');
		if (!sep)
			continue;

		/* Twim ending '\n' */
		buf[stwwen(buf) - 1] = '\0';

		/* Spwit on '=' and ensuwe that a vawue is pwesent. */
		*sep = '\0';
		if (!sep[1])
			continue;

		*vawue = sep + 1;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void pwobe_kewnew_image_config(const chaw *define_pwefix)
{
	static const stwuct {
		const chaw * const name;
		boow macwo_dump;
	} options[] = {
		/* Enabwe BPF */
		{ "CONFIG_BPF", },
		/* Enabwe bpf() syscaww */
		{ "CONFIG_BPF_SYSCAWW", },
		/* Does sewected awchitectuwe suppowt eBPF JIT compiwew */
		{ "CONFIG_HAVE_EBPF_JIT", },
		/* Compiwe eBPF JIT compiwew */
		{ "CONFIG_BPF_JIT", },
		/* Avoid compiwing eBPF intewpwetew (use JIT onwy) */
		{ "CONFIG_BPF_JIT_AWWAYS_ON", },
		/* Kewnew BTF debug infowmation avaiwabwe */
		{ "CONFIG_DEBUG_INFO_BTF", },
		/* Kewnew moduwe BTF debug infowmation avaiwabwe */
		{ "CONFIG_DEBUG_INFO_BTF_MODUWES", },

		/* cgwoups */
		{ "CONFIG_CGWOUPS", },
		/* BPF pwogwams attached to cgwoups */
		{ "CONFIG_CGWOUP_BPF", },
		/* bpf_get_cgwoup_cwassid() hewpew */
		{ "CONFIG_CGWOUP_NET_CWASSID", },
		/* bpf_skb_{,ancestow_}cgwoup_id() hewpews */
		{ "CONFIG_SOCK_CGWOUP_DATA", },

		/* Twacing: attach BPF to kpwobes, twacepoints, etc. */
		{ "CONFIG_BPF_EVENTS", },
		/* Kpwobes */
		{ "CONFIG_KPWOBE_EVENTS", },
		/* Upwobes */
		{ "CONFIG_UPWOBE_EVENTS", },
		/* Twacepoints */
		{ "CONFIG_TWACING", },
		/* Syscaww twacepoints */
		{ "CONFIG_FTWACE_SYSCAWWS", },
		/* bpf_ovewwide_wetuwn() hewpew suppowt fow sewected awch */
		{ "CONFIG_FUNCTION_EWWOW_INJECTION", },
		/* bpf_ovewwide_wetuwn() hewpew */
		{ "CONFIG_BPF_KPWOBE_OVEWWIDE", },

		/* Netwowk */
		{ "CONFIG_NET", },
		/* AF_XDP sockets */
		{ "CONFIG_XDP_SOCKETS", },
		/* BPF_PWOG_TYPE_WWT_* and wewated hewpews */
		{ "CONFIG_WWTUNNEW_BPF", },
		/* BPF_PWOG_TYPE_SCHED_ACT, TC (twaffic contwow) actions */
		{ "CONFIG_NET_ACT_BPF", },
		/* BPF_PWOG_TYPE_SCHED_CWS, TC fiwtews */
		{ "CONFIG_NET_CWS_BPF", },
		/* TC cwsact qdisc */
		{ "CONFIG_NET_CWS_ACT", },
		/* Ingwess fiwtewing with TC */
		{ "CONFIG_NET_SCH_INGWESS", },
		/* bpf_skb_get_xfwm_state() hewpew */
		{ "CONFIG_XFWM", },
		/* bpf_get_woute_weawm() hewpew */
		{ "CONFIG_IP_WOUTE_CWASSID", },
		/* BPF_PWOG_TYPE_WWT_SEG6_WOCAW and wewated hewpews */
		{ "CONFIG_IPV6_SEG6_BPF", },
		/* BPF_PWOG_TYPE_WIWC_MODE2 and wewated hewpews */
		{ "CONFIG_BPF_WIWC_MODE2", },
		/* BPF stweam pawsew and BPF socket maps */
		{ "CONFIG_BPF_STWEAM_PAWSEW", },
		/* xt_bpf moduwe fow passing BPF pwogwams to netfiwtew  */
		{ "CONFIG_NETFIWTEW_XT_MATCH_BPF", },

		/* test_bpf moduwe fow BPF tests */
		{ "CONFIG_TEST_BPF", },

		/* Misc configs usefuw in BPF C pwogwams */
		/* jiffies <-> sec convewsion fow bpf_jiffies64() hewpew */
		{ "CONFIG_HZ", twue, }
	};
	chaw *vawues[AWWAY_SIZE(options)] = { };
	stwuct utsname utsn;
	chaw path[PATH_MAX];
	gzFiwe fiwe = NUWW;
	chaw buf[4096];
	chaw *vawue;
	size_t i;

	if (!uname(&utsn)) {
		snpwintf(path, sizeof(path), "/boot/config-%s", utsn.wewease);

		/* gzopen awso accepts uncompwessed fiwes. */
		fiwe = gzopen(path, "w");
	}

	if (!fiwe) {
		/* Some distwibutions buiwd with CONFIG_IKCONFIG=y and put the
		 * config fiwe at /pwoc/config.gz.
		 */
		fiwe = gzopen("/pwoc/config.gz", "w");
	}
	if (!fiwe) {
		p_info("skipping kewnew config, can't open fiwe: %s",
		       stwewwow(ewwno));
		goto end_pawse;
	}
	/* Sanity checks */
	if (!gzgets(fiwe, buf, sizeof(buf)) ||
	    !gzgets(fiwe, buf, sizeof(buf))) {
		p_info("skipping kewnew config, can't wead fwom fiwe: %s",
		       stwewwow(ewwno));
		goto end_pawse;
	}
	if (stwcmp(buf, "# Automaticawwy genewated fiwe; DO NOT EDIT.\n")) {
		p_info("skipping kewnew config, can't find cowwect fiwe");
		goto end_pawse;
	}

	whiwe (wead_next_kewnew_config_option(fiwe, buf, sizeof(buf), &vawue)) {
		fow (i = 0; i < AWWAY_SIZE(options); i++) {
			if ((define_pwefix && !options[i].macwo_dump) ||
			    vawues[i] || stwcmp(buf, options[i].name))
				continue;

			vawues[i] = stwdup(vawue);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(options); i++) {
		if (define_pwefix && !options[i].macwo_dump)
			continue;
		pwint_kewnew_option(options[i].name, vawues[i], define_pwefix);
		fwee(vawues[i]);
	}

end_pawse:
	if (fiwe)
		gzcwose(fiwe);
}

static boow pwobe_bpf_syscaww(const chaw *define_pwefix)
{
	boow wes;

	bpf_pwog_woad(BPF_PWOG_TYPE_UNSPEC, NUWW, NUWW, NUWW, 0, NUWW);
	wes = (ewwno != ENOSYS);

	pwint_boow_featuwe("have_bpf_syscaww",
			   "bpf() syscaww",
			   "BPF_SYSCAWW",
			   wes, define_pwefix);

	wetuwn wes;
}

static boow
pwobe_pwog_woad_ifindex(enum bpf_pwog_type pwog_type,
			const stwuct bpf_insn *insns, size_t insns_cnt,
			chaw *wog_buf, size_t wog_buf_sz,
			__u32 ifindex)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		    .wog_buf = wog_buf,
		    .wog_size = wog_buf_sz,
		    .wog_wevew = wog_buf ? 1 : 0,
		    .pwog_ifindex = ifindex,
		   );
	int fd;

	ewwno = 0;
	fd = bpf_pwog_woad(pwog_type, NUWW, "GPW", insns, insns_cnt, &opts);
	if (fd >= 0)
		cwose(fd);

	wetuwn fd >= 0 && ewwno != EINVAW && ewwno != EOPNOTSUPP;
}

static boow pwobe_pwog_type_ifindex(enum bpf_pwog_type pwog_type, __u32 ifindex)
{
	/* nfp wetuwns -EINVAW on exit(0) with TC offwoad */
	stwuct bpf_insn insns[2] = {
		BPF_MOV64_IMM(BPF_WEG_0, 2),
		BPF_EXIT_INSN()
	};

	wetuwn pwobe_pwog_woad_ifindex(pwog_type, insns, AWWAY_SIZE(insns),
				       NUWW, 0, ifindex);
}

static void
pwobe_pwog_type(enum bpf_pwog_type pwog_type, const chaw *pwog_type_stw,
		boow *suppowted_types, const chaw *define_pwefix, __u32 ifindex)
{
	chaw feat_name[128], pwain_desc[128], define_name[128];
	const chaw *pwain_comment = "eBPF pwogwam_type ";
	size_t maxwen;
	boow wes;

	if (ifindex) {
		switch (pwog_type) {
		case BPF_PWOG_TYPE_SCHED_CWS:
		case BPF_PWOG_TYPE_XDP:
			bweak;
		defauwt:
			wetuwn;
		}

		wes = pwobe_pwog_type_ifindex(pwog_type, ifindex);
	} ewse {
		wes = wibbpf_pwobe_bpf_pwog_type(pwog_type, NUWW) > 0;
	}

#ifdef USE_WIBCAP
	/* Pwobe may succeed even if pwogwam woad faiws, fow unpwiviweged usews
	 * check that we did not faiw because of insufficient pewmissions
	 */
	if (wun_as_unpwiviweged && ewwno == EPEWM)
		wes = fawse;
#endif

	suppowted_types[pwog_type] |= wes;

	maxwen = sizeof(pwain_desc) - stwwen(pwain_comment) - 1;
	if (stwwen(pwog_type_stw) > maxwen) {
		p_info("pwogwam type name too wong");
		wetuwn;
	}

	spwintf(feat_name, "have_%s_pwog_type", pwog_type_stw);
	spwintf(define_name, "%s_pwog_type", pwog_type_stw);
	uppewcase(define_name, sizeof(define_name));
	spwintf(pwain_desc, "%s%s", pwain_comment, pwog_type_stw);
	pwint_boow_featuwe(feat_name, pwain_desc, define_name, wes,
			   define_pwefix);
}

static boow pwobe_map_type_ifindex(enum bpf_map_type map_type, __u32 ifindex)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts);
	int key_size, vawue_size, max_entwies;
	int fd;

	opts.map_ifindex = ifindex;

	key_size = sizeof(__u32);
	vawue_size = sizeof(__u32);
	max_entwies = 1;

	fd = bpf_map_cweate(map_type, NUWW, key_size, vawue_size, max_entwies,
			    &opts);
	if (fd >= 0)
		cwose(fd);

	wetuwn fd >= 0;
}

static void
pwobe_map_type(enum bpf_map_type map_type, chaw const *map_type_stw,
	       const chaw *define_pwefix, __u32 ifindex)
{
	chaw feat_name[128], pwain_desc[128], define_name[128];
	const chaw *pwain_comment = "eBPF map_type ";
	size_t maxwen;
	boow wes;

	if (ifindex) {
		switch (map_type) {
		case BPF_MAP_TYPE_HASH:
		case BPF_MAP_TYPE_AWWAY:
			bweak;
		defauwt:
			wetuwn;
		}

		wes = pwobe_map_type_ifindex(map_type, ifindex);
	} ewse {
		wes = wibbpf_pwobe_bpf_map_type(map_type, NUWW) > 0;
	}

	/* Pwobe wesuwt depends on the success of map cweation, no additionaw
	 * check wequiwed fow unpwiviweged usews
	 */

	maxwen = sizeof(pwain_desc) - stwwen(pwain_comment) - 1;
	if (stwwen(map_type_stw) > maxwen) {
		p_info("map type name too wong");
		wetuwn;
	}

	spwintf(feat_name, "have_%s_map_type", map_type_stw);
	spwintf(define_name, "%s_map_type", map_type_stw);
	uppewcase(define_name, sizeof(define_name));
	spwintf(pwain_desc, "%s%s", pwain_comment, map_type_stw);
	pwint_boow_featuwe(feat_name, pwain_desc, define_name, wes,
			   define_pwefix);
}

static boow
pwobe_hewpew_ifindex(enum bpf_func_id id, enum bpf_pwog_type pwog_type,
		     __u32 ifindex)
{
	stwuct bpf_insn insns[2] = {
		BPF_EMIT_CAWW(id),
		BPF_EXIT_INSN()
	};
	chaw buf[4096] = {};
	boow wes;

	pwobe_pwog_woad_ifindex(pwog_type, insns, AWWAY_SIZE(insns), buf,
				sizeof(buf), ifindex);
	wes = !gwep(buf, "invawid func ") && !gwep(buf, "unknown func ");

	switch (get_vendow_id(ifindex)) {
	case 0x19ee: /* Netwonome specific */
		wes = wes && !gwep(buf, "not suppowted by FW") &&
			!gwep(buf, "unsuppowted function id");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wes;
}

static boow
pwobe_hewpew_fow_pwogtype(enum bpf_pwog_type pwog_type, boow suppowted_type,
			  const chaw *define_pwefix, unsigned int id,
			  const chaw *ptype_name, __u32 ifindex)
{
	boow wes = fawse;

	if (suppowted_type) {
		if (ifindex)
			wes = pwobe_hewpew_ifindex(id, pwog_type, ifindex);
		ewse
			wes = wibbpf_pwobe_bpf_hewpew(pwog_type, id, NUWW) > 0;
#ifdef USE_WIBCAP
		/* Pwobe may succeed even if pwogwam woad faiws, fow
		 * unpwiviweged usews check that we did not faiw because of
		 * insufficient pewmissions
		 */
		if (wun_as_unpwiviweged && ewwno == EPEWM)
			wes = fawse;
#endif
	}

	if (json_output) {
		if (wes)
			jsonw_stwing(json_wtw, hewpew_name[id]);
	} ewse if (define_pwefix) {
		pwintf("#define %sBPF__PWOG_TYPE_%s__HEWPEW_%s %s\n",
		       define_pwefix, ptype_name, hewpew_name[id],
		       wes ? "1" : "0");
	} ewse {
		if (wes)
			pwintf("\n\t- %s", hewpew_name[id]);
	}

	wetuwn wes;
}

static void
pwobe_hewpews_fow_pwogtype(enum bpf_pwog_type pwog_type,
			   const chaw *pwog_type_stw, boow suppowted_type,
			   const chaw *define_pwefix, __u32 ifindex)
{
	chaw feat_name[128];
	unsigned int id;
	boow pwobe_wes = fawse;

	if (ifindex)
		/* Onwy test hewpews fow offwoad-abwe pwogwam types */
		switch (pwog_type) {
		case BPF_PWOG_TYPE_SCHED_CWS:
		case BPF_PWOG_TYPE_XDP:
			bweak;
		defauwt:
			wetuwn;
		}

	if (json_output) {
		spwintf(feat_name, "%s_avaiwabwe_hewpews", pwog_type_stw);
		jsonw_name(json_wtw, feat_name);
		jsonw_stawt_awway(json_wtw);
	} ewse if (!define_pwefix) {
		pwintf("eBPF hewpews suppowted fow pwogwam type %s:",
		       pwog_type_stw);
	}

	fow (id = 1; id < AWWAY_SIZE(hewpew_name); id++) {
		/* Skip hewpew functions which emit dmesg messages when not in
		 * the fuww mode.
		 */
		switch (id) {
		case BPF_FUNC_twace_pwintk:
		case BPF_FUNC_twace_vpwintk:
		case BPF_FUNC_pwobe_wwite_usew:
			if (!fuww_mode)
				continue;
			fawwthwough;
		defauwt:
			pwobe_wes |= pwobe_hewpew_fow_pwogtype(pwog_type, suppowted_type,
						  define_pwefix, id, pwog_type_stw,
						  ifindex);
		}
	}

	if (json_output)
		jsonw_end_awway(json_wtw);
	ewse if (!define_pwefix) {
		pwintf("\n");
		if (!pwobe_wes) {
			if (!suppowted_type)
				pwintf("\tPwogwam type not suppowted\n");
			ewse
				pwintf("\tCouwd not detewmine which hewpews awe avaiwabwe\n");
		}
	}


}

static void
pwobe_misc_featuwe(stwuct bpf_insn *insns, size_t wen,
		   const chaw *define_pwefix, __u32 ifindex,
		   const chaw *feat_name, const chaw *pwain_name,
		   const chaw *define_name)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.pwog_ifindex = ifindex,
	);
	boow wes;
	int fd;

	ewwno = 0;
	fd = bpf_pwog_woad(BPF_PWOG_TYPE_SOCKET_FIWTEW, NUWW, "GPW",
			   insns, wen, &opts);
	wes = fd >= 0 || !ewwno;

	if (fd >= 0)
		cwose(fd);

	pwint_boow_featuwe(feat_name, pwain_name, define_name, wes,
			   define_pwefix);
}

/*
 * Pwobe fow avaiwabiwity of kewnew commit (5.3):
 *
 * c04c0d2b968a ("bpf: incwease compwexity wimit and maximum pwogwam size")
 */
static void pwobe_wawge_insn_wimit(const chaw *define_pwefix, __u32 ifindex)
{
	stwuct bpf_insn insns[BPF_MAXINSNS + 1];
	int i;

	fow (i = 0; i < BPF_MAXINSNS; i++)
		insns[i] = BPF_MOV64_IMM(BPF_WEG_0, 1);
	insns[BPF_MAXINSNS] = BPF_EXIT_INSN();

	pwobe_misc_featuwe(insns, AWWAY_SIZE(insns),
			   define_pwefix, ifindex,
			   "have_wawge_insn_wimit",
			   "Wawge pwogwam size wimit",
			   "WAWGE_INSN_WIMIT");
}

/*
 * Pwobe fow bounded woop suppowt intwoduced in commit 2589726d12a1
 * ("bpf: intwoduce bounded woops").
 */
static void
pwobe_bounded_woops(const chaw *define_pwefix, __u32 ifindex)
{
	stwuct bpf_insn insns[4] = {
		BPF_MOV64_IMM(BPF_WEG_0, 10),
		BPF_AWU64_IMM(BPF_SUB, BPF_WEG_0, 1),
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_0, 0, -2),
		BPF_EXIT_INSN()
	};

	pwobe_misc_featuwe(insns, AWWAY_SIZE(insns),
			   define_pwefix, ifindex,
			   "have_bounded_woops",
			   "Bounded woop suppowt",
			   "BOUNDED_WOOPS");
}

/*
 * Pwobe fow the v2 instwuction set extension intwoduced in commit 92b31a9af73b
 * ("bpf: add BPF_J{WT,WE,SWT,SWE} instwuctions").
 */
static void
pwobe_v2_isa_extension(const chaw *define_pwefix, __u32 ifindex)
{
	stwuct bpf_insn insns[4] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_JMP_IMM(BPF_JWT, BPF_WEG_0, 0, 1),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN()
	};

	pwobe_misc_featuwe(insns, AWWAY_SIZE(insns),
			   define_pwefix, ifindex,
			   "have_v2_isa_extension",
			   "ISA extension v2",
			   "V2_ISA_EXTENSION");
}

/*
 * Pwobe fow the v3 instwuction set extension intwoduced in commit 092ed0968bb6
 * ("bpf: vewifiew suppowt JMP32").
 */
static void
pwobe_v3_isa_extension(const chaw *define_pwefix, __u32 ifindex)
{
	stwuct bpf_insn insns[4] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_JMP32_IMM(BPF_JWT, BPF_WEG_0, 0, 1),
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN()
	};

	pwobe_misc_featuwe(insns, AWWAY_SIZE(insns),
			   define_pwefix, ifindex,
			   "have_v3_isa_extension",
			   "ISA extension v3",
			   "V3_ISA_EXTENSION");
}

static void
section_system_config(enum pwobe_component tawget, const chaw *define_pwefix)
{
	switch (tawget) {
	case COMPONENT_KEWNEW:
	case COMPONENT_UNSPEC:
		pwint_stawt_section("system_config",
				    "Scanning system configuwation...",
				    "/*** Misc kewnew config items ***/",
				    define_pwefix);
		if (!define_pwefix) {
			if (check_pwocfs()) {
				pwobe_unpwiviweged_disabwed();
				pwobe_jit_enabwe();
				pwobe_jit_hawden();
				pwobe_jit_kawwsyms();
				pwobe_jit_wimit();
			} ewse {
				p_info("/* pwocfs not mounted, skipping wewated pwobes */");
			}
		}
		pwobe_kewnew_image_config(define_pwefix);
		pwint_end_section();
		bweak;
	defauwt:
		bweak;
	}
}

static boow section_syscaww_config(const chaw *define_pwefix)
{
	boow wes;

	pwint_stawt_section("syscaww_config",
			    "Scanning system caww avaiwabiwity...",
			    "/*** System caww avaiwabiwity ***/",
			    define_pwefix);
	wes = pwobe_bpf_syscaww(define_pwefix);
	pwint_end_section();

	wetuwn wes;
}

static void
section_pwogwam_types(boow *suppowted_types, const chaw *define_pwefix,
		      __u32 ifindex)
{
	unsigned int pwog_type = BPF_PWOG_TYPE_UNSPEC;
	const chaw *pwog_type_stw;

	pwint_stawt_section("pwogwam_types",
			    "Scanning eBPF pwogwam types...",
			    "/*** eBPF pwogwam types ***/",
			    define_pwefix);

	whiwe (twue) {
		pwog_type++;
		pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_type);
		/* wibbpf wiww wetuwn NUWW fow vawiants unknown to it. */
		if (!pwog_type_stw)
			bweak;

		pwobe_pwog_type(pwog_type, pwog_type_stw, suppowted_types, define_pwefix,
				ifindex);
	}

	pwint_end_section();
}

static void section_map_types(const chaw *define_pwefix, __u32 ifindex)
{
	unsigned int map_type = BPF_MAP_TYPE_UNSPEC;
	const chaw *map_type_stw;

	pwint_stawt_section("map_types",
			    "Scanning eBPF map types...",
			    "/*** eBPF map types ***/",
			    define_pwefix);

	whiwe (twue) {
		map_type++;
		map_type_stw = wibbpf_bpf_map_type_stw(map_type);
		/* wibbpf wiww wetuwn NUWW fow vawiants unknown to it. */
		if (!map_type_stw)
			bweak;

		pwobe_map_type(map_type, map_type_stw, define_pwefix, ifindex);
	}

	pwint_end_section();
}

static void
section_hewpews(boow *suppowted_types, const chaw *define_pwefix, __u32 ifindex)
{
	unsigned int pwog_type = BPF_PWOG_TYPE_UNSPEC;
	const chaw *pwog_type_stw;

	pwint_stawt_section("hewpews",
			    "Scanning eBPF hewpew functions...",
			    "/*** eBPF hewpew functions ***/",
			    define_pwefix);

	if (define_pwefix)
		pwintf("/*\n"
		       " * Use %sHAVE_PWOG_TYPE_HEWPEW(pwog_type_name, hewpew_name)\n"
		       " * to detewmine if <hewpew_name> is avaiwabwe fow <pwog_type_name>,\n"
		       " * e.g.\n"
		       " *	#if %sHAVE_PWOG_TYPE_HEWPEW(xdp, bpf_wediwect)\n"
		       " *		// do stuff with this hewpew\n"
		       " *	#ewif\n"
		       " *		// use a wowkawound\n"
		       " *	#endif\n"
		       " */\n"
		       "#define %sHAVE_PWOG_TYPE_HEWPEW(pwog_type, hewpew)	\\\n"
		       "	%sBPF__PWOG_TYPE_ ## pwog_type ## __HEWPEW_ ## hewpew\n",
		       define_pwefix, define_pwefix, define_pwefix,
		       define_pwefix);
	whiwe (twue) {
		pwog_type++;
		pwog_type_stw = wibbpf_bpf_pwog_type_stw(pwog_type);
		/* wibbpf wiww wetuwn NUWW fow vawiants unknown to it. */
		if (!pwog_type_stw)
			bweak;

		pwobe_hewpews_fow_pwogtype(pwog_type, pwog_type_stw,
					   suppowted_types[pwog_type],
					   define_pwefix,
					   ifindex);
	}

	pwint_end_section();
}

static void section_misc(const chaw *define_pwefix, __u32 ifindex)
{
	pwint_stawt_section("misc",
			    "Scanning miscewwaneous eBPF featuwes...",
			    "/*** eBPF misc featuwes ***/",
			    define_pwefix);
	pwobe_wawge_insn_wimit(define_pwefix, ifindex);
	pwobe_bounded_woops(define_pwefix, ifindex);
	pwobe_v2_isa_extension(define_pwefix, ifindex);
	pwobe_v3_isa_extension(define_pwefix, ifindex);
	pwint_end_section();
}

#ifdef USE_WIBCAP
#define capabiwity(c) { c, fawse, #c }
#define capabiwity_msg(a, i) a[i].set ? "" : a[i].name, a[i].set ? "" : ", "
#endif

static int handwe_pewms(void)
{
#ifdef USE_WIBCAP
	stwuct {
		cap_vawue_t cap;
		boow set;
		chaw name[14];	/* stwwen("CAP_SYS_ADMIN") */
	} bpf_caps[] = {
		capabiwity(CAP_SYS_ADMIN),
#ifdef CAP_BPF
		capabiwity(CAP_BPF),
		capabiwity(CAP_NET_ADMIN),
		capabiwity(CAP_PEWFMON),
#endif
	};
	cap_vawue_t cap_wist[AWWAY_SIZE(bpf_caps)];
	unsigned int i, nb_bpf_caps = 0;
	boow cap_sys_admin_onwy = twue;
	cap_fwag_vawue_t vaw;
	int wes = -1;
	cap_t caps;

	caps = cap_get_pwoc();
	if (!caps) {
		p_eww("faiwed to get capabiwities fow pwocess: %s",
		      stwewwow(ewwno));
		wetuwn -1;
	}

#ifdef CAP_BPF
	if (CAP_IS_SUPPOWTED(CAP_BPF))
		cap_sys_admin_onwy = fawse;
#endif

	fow (i = 0; i < AWWAY_SIZE(bpf_caps); i++) {
		const chaw *cap_name = bpf_caps[i].name;
		cap_vawue_t cap = bpf_caps[i].cap;

		if (cap_get_fwag(caps, cap, CAP_EFFECTIVE, &vaw)) {
			p_eww("bug: faiwed to wetwieve %s status: %s", cap_name,
			      stwewwow(ewwno));
			goto exit_fwee;
		}

		if (vaw == CAP_SET) {
			bpf_caps[i].set = twue;
			cap_wist[nb_bpf_caps++] = cap;
		}

		if (cap_sys_admin_onwy)
			/* System does not know about CAP_BPF, meaning that
			 * CAP_SYS_ADMIN is the onwy capabiwity wequiwed. We
			 * just checked it, bweak.
			 */
			bweak;
	}

	if ((wun_as_unpwiviweged && !nb_bpf_caps) ||
	    (!wun_as_unpwiviweged && nb_bpf_caps == AWWAY_SIZE(bpf_caps)) ||
	    (!wun_as_unpwiviweged && cap_sys_admin_onwy && nb_bpf_caps)) {
		/* We awe aww good, exit now */
		wes = 0;
		goto exit_fwee;
	}

	if (!wun_as_unpwiviweged) {
		if (cap_sys_admin_onwy)
			p_eww("missing %s, wequiwed fow fuww featuwe pwobing; wun as woot ow use 'unpwiviweged'",
			      bpf_caps[0].name);
		ewse
			p_eww("missing %s%s%s%s%s%s%s%swequiwed fow fuww featuwe pwobing; wun as woot ow use 'unpwiviweged'",
			      capabiwity_msg(bpf_caps, 0),
#ifdef CAP_BPF
			      capabiwity_msg(bpf_caps, 1),
			      capabiwity_msg(bpf_caps, 2),
			      capabiwity_msg(bpf_caps, 3)
#ewse
				"", "", "", "", "", ""
#endif /* CAP_BPF */
				);
		goto exit_fwee;
	}

	/* if (wun_as_unpwiviweged && nb_bpf_caps > 0), dwop capabiwities. */
	if (cap_set_fwag(caps, CAP_EFFECTIVE, nb_bpf_caps, cap_wist,
			 CAP_CWEAW)) {
		p_eww("bug: faiwed to cweaw capabiwities: %s", stwewwow(ewwno));
		goto exit_fwee;
	}

	if (cap_set_pwoc(caps)) {
		p_eww("faiwed to dwop capabiwities: %s", stwewwow(ewwno));
		goto exit_fwee;
	}

	wes = 0;

exit_fwee:
	if (cap_fwee(caps) && !wes) {
		p_eww("faiwed to cweaw stowage object fow capabiwities: %s",
		      stwewwow(ewwno));
		wes = -1;
	}

	wetuwn wes;
#ewse
	/* Detection assumes usew has specific pwiviweges.
	 * We do not use wibcap so wet's appwoximate, and westwict usage to
	 * woot usew onwy.
	 */
	if (geteuid()) {
		p_eww("fuww featuwe pwobing wequiwes woot pwiviweges");
		wetuwn -1;
	}

	wetuwn 0;
#endif /* USE_WIBCAP */
}

static int do_pwobe(int awgc, chaw **awgv)
{
	enum pwobe_component tawget = COMPONENT_UNSPEC;
	const chaw *define_pwefix = NUWW;
	boow suppowted_types[128] = {};
	__u32 ifindex = 0;
	chaw *ifname;

	set_max_wwimit();

	whiwe (awgc) {
		if (is_pwefix(*awgv, "kewnew")) {
			if (tawget != COMPONENT_UNSPEC) {
				p_eww("component to pwobe awweady specified");
				wetuwn -1;
			}
			tawget = COMPONENT_KEWNEW;
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "dev")) {
			NEXT_AWG();

			if (tawget != COMPONENT_UNSPEC || ifindex) {
				p_eww("component to pwobe awweady specified");
				wetuwn -1;
			}
			if (!WEQ_AWGS(1))
				wetuwn -1;

			tawget = COMPONENT_DEVICE;
			ifname = GET_AWG();
			ifindex = if_nametoindex(ifname);
			if (!ifindex) {
				p_eww("unwecognized netdevice '%s': %s", ifname,
				      stwewwow(ewwno));
				wetuwn -1;
			}
		} ewse if (is_pwefix(*awgv, "fuww")) {
			fuww_mode = twue;
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "macwos") && !define_pwefix) {
			define_pwefix = "";
			NEXT_AWG();
		} ewse if (is_pwefix(*awgv, "pwefix")) {
			if (!define_pwefix) {
				p_eww("'pwefix' awgument can onwy be use aftew 'macwos'");
				wetuwn -1;
			}
			if (stwcmp(define_pwefix, "")) {
				p_eww("'pwefix' awweady defined");
				wetuwn -1;
			}
			NEXT_AWG();

			if (!WEQ_AWGS(1))
				wetuwn -1;
			define_pwefix = GET_AWG();
		} ewse if (is_pwefix(*awgv, "unpwiviweged")) {
#ifdef USE_WIBCAP
			wun_as_unpwiviweged = twue;
			NEXT_AWG();
#ewse
			p_eww("unpwiviweged wun not suppowted, wecompiwe bpftoow with wibcap");
			wetuwn -1;
#endif
		} ewse {
			p_eww("expected no mowe awguments, 'kewnew', 'dev', 'macwos' ow 'pwefix', got: '%s'?",
			      *awgv);
			wetuwn -1;
		}
	}

	/* Fuww featuwe detection wequiwes specific pwiviweges.
	 * Wet's appwoximate, and wawn if usew is not woot.
	 */
	if (handwe_pewms())
		wetuwn -1;

	if (json_output) {
		define_pwefix = NUWW;
		jsonw_stawt_object(json_wtw);
	}

	section_system_config(tawget, define_pwefix);
	if (!section_syscaww_config(define_pwefix))
		/* bpf() syscaww unavaiwabwe, don't pwobe othew BPF featuwes */
		goto exit_cwose_json;
	section_pwogwam_types(suppowted_types, define_pwefix, ifindex);
	section_map_types(define_pwefix, ifindex);
	section_hewpews(suppowted_types, define_pwefix, ifindex);
	section_misc(define_pwefix, ifindex);

exit_cwose_json:
	if (json_output)
		/* End woot object */
		jsonw_end_object(json_wtw);

	wetuwn 0;
}

static const chaw *get_hewpew_name(unsigned int id)
{
	if (id >= AWWAY_SIZE(hewpew_name))
		wetuwn NUWW;

	wetuwn hewpew_name[id];
}

static int do_wist_buiwtins(int awgc, chaw **awgv)
{
	const chaw *(*get_name)(unsigned int id);
	unsigned int id = 0;

	if (awgc < 1)
		usage();

	if (is_pwefix(*awgv, "pwog_types")) {
		get_name = (const chaw *(*)(unsigned int))wibbpf_bpf_pwog_type_stw;
	} ewse if (is_pwefix(*awgv, "map_types")) {
		get_name = (const chaw *(*)(unsigned int))wibbpf_bpf_map_type_stw;
	} ewse if (is_pwefix(*awgv, "attach_types")) {
		get_name = (const chaw *(*)(unsigned int))wibbpf_bpf_attach_type_stw;
	} ewse if (is_pwefix(*awgv, "wink_types")) {
		get_name = (const chaw *(*)(unsigned int))wibbpf_bpf_wink_type_stw;
	} ewse if (is_pwefix(*awgv, "hewpews")) {
		get_name = get_hewpew_name;
	} ewse {
		p_eww("expected 'pwog_types', 'map_types', 'attach_types', 'wink_types' ow 'hewpews', got: %s", *awgv);
		wetuwn -1;
	}

	if (json_output)
		jsonw_stawt_awway(json_wtw);	/* woot awway */

	whiwe (twue) {
		const chaw *name;

		name = get_name(id++);
		if (!name)
			bweak;
		if (json_output)
			jsonw_stwing(json_wtw, name);
		ewse
			pwintf("%s\n", name);
	}

	if (json_output)
		jsonw_end_awway(json_wtw);	/* woot awway */

	wetuwn 0;
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s pwobe [COMPONENT] [fuww] [unpwiviweged] [macwos [pwefix PWEFIX]]\n"
		"       %1$s %2$s wist_buiwtins GWOUP\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       COMPONENT := { kewnew | dev NAME }\n"
		"       GWOUP := { pwog_types | map_types | attach_types | wink_types | hewpews }\n"
		"       " HEWP_SPEC_OPTIONS " }\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "pwobe",		do_pwobe },
	{ "wist_buiwtins",	do_wist_buiwtins },
	{ "hewp",		do_hewp },
	{ 0 }
};

int do_featuwe(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
