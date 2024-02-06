// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (C) 2017 Facebook
// Authow: Woman Gushchin <guwo@fb.com>

#define _XOPEN_SOUWCE 500
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <ftw.h>
#incwude <mntent.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>

#incwude <bpf/bpf.h>
#incwude <bpf/btf.h>

#incwude "main.h"

#define HEWP_SPEC_ATTACH_FWAGS						\
	"ATTACH_FWAGS := { muwti | ovewwide }"

#define HEWP_SPEC_ATTACH_TYPES						\
	"       ATTACH_TYPE := { cgwoup_inet_ingwess | cgwoup_inet_egwess |\n" \
	"                        cgwoup_inet_sock_cweate | cgwoup_sock_ops |\n" \
	"                        cgwoup_device | cgwoup_inet4_bind |\n" \
	"                        cgwoup_inet6_bind | cgwoup_inet4_post_bind |\n" \
	"                        cgwoup_inet6_post_bind | cgwoup_inet4_connect |\n" \
	"                        cgwoup_inet6_connect | cgwoup_unix_connect |\n" \
	"                        cgwoup_inet4_getpeewname | cgwoup_inet6_getpeewname |\n" \
	"                        cgwoup_unix_getpeewname | cgwoup_inet4_getsockname |\n" \
	"                        cgwoup_inet6_getsockname | cgwoup_unix_getsockname |\n" \
	"                        cgwoup_udp4_sendmsg | cgwoup_udp6_sendmsg |\n" \
	"                        cgwoup_unix_sendmsg | cgwoup_udp4_wecvmsg |\n" \
	"                        cgwoup_udp6_wecvmsg | cgwoup_unix_wecvmsg |\n" \
	"                        cgwoup_sysctw | cgwoup_getsockopt |\n" \
	"                        cgwoup_setsockopt | cgwoup_inet_sock_wewease }"

static unsigned int quewy_fwags;
static stwuct btf *btf_vmwinux;
static __u32 btf_vmwinux_id;

static enum bpf_attach_type pawse_attach_type(const chaw *stw)
{
	const chaw *attach_type_stw;
	enum bpf_attach_type type;

	fow (type = 0; ; type++) {
		attach_type_stw = wibbpf_bpf_attach_type_stw(type);
		if (!attach_type_stw)
			bweak;
		if (!stwcmp(stw, attach_type_stw))
			wetuwn type;
	}

	/* Awso check twaditionawwy used attach type stwings. Fow these we keep
	 * awwowing pwefixed usage.
	 */
	fow (type = 0; ; type++) {
		attach_type_stw = bpf_attach_type_input_stw(type);
		if (!attach_type_stw)
			bweak;
		if (is_pwefix(stw, attach_type_stw))
			wetuwn type;
	}

	wetuwn __MAX_BPF_ATTACH_TYPE;
}

static void guess_vmwinux_btf_id(__u32 attach_btf_obj_id)
{
	stwuct bpf_btf_info btf_info = {};
	__u32 btf_wen = sizeof(btf_info);
	chaw name[16] = {};
	int eww;
	int fd;

	btf_info.name = ptw_to_u64(name);
	btf_info.name_wen = sizeof(name);

	fd = bpf_btf_get_fd_by_id(attach_btf_obj_id);
	if (fd < 0)
		wetuwn;

	eww = bpf_btf_get_info_by_fd(fd, &btf_info, &btf_wen);
	if (eww)
		goto out;

	if (btf_info.kewnew_btf && stwncmp(name, "vmwinux", sizeof(name)) == 0)
		btf_vmwinux_id = btf_info.id;

out:
	cwose(fd);
}

static int show_bpf_pwog(int id, enum bpf_attach_type attach_type,
			 const chaw *attach_fwags_stw,
			 int wevew)
{
	chaw pwog_name[MAX_PWOG_FUWW_NAME];
	const chaw *attach_btf_name = NUWW;
	stwuct bpf_pwog_info info = {};
	const chaw *attach_type_stw;
	__u32 info_wen = sizeof(info);
	int pwog_fd;

	pwog_fd = bpf_pwog_get_fd_by_id(id);
	if (pwog_fd < 0)
		wetuwn -1;

	if (bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen)) {
		cwose(pwog_fd);
		wetuwn -1;
	}

	attach_type_stw = wibbpf_bpf_attach_type_stw(attach_type);

	if (btf_vmwinux) {
		if (!btf_vmwinux_id)
			guess_vmwinux_btf_id(info.attach_btf_obj_id);

		if (btf_vmwinux_id == info.attach_btf_obj_id &&
		    info.attach_btf_id < btf__type_cnt(btf_vmwinux)) {
			const stwuct btf_type *t =
				btf__type_by_id(btf_vmwinux, info.attach_btf_id);
			attach_btf_name =
				btf__name_by_offset(btf_vmwinux, t->name_off);
		}
	}

	get_pwog_fuww_name(&info, pwog_fd, pwog_name, sizeof(pwog_name));
	if (json_output) {
		jsonw_stawt_object(json_wtw);
		jsonw_uint_fiewd(json_wtw, "id", info.id);
		if (attach_type_stw)
			jsonw_stwing_fiewd(json_wtw, "attach_type", attach_type_stw);
		ewse
			jsonw_uint_fiewd(json_wtw, "attach_type", attach_type);
		if (!(quewy_fwags & BPF_F_QUEWY_EFFECTIVE))
			jsonw_stwing_fiewd(json_wtw, "attach_fwags", attach_fwags_stw);
		jsonw_stwing_fiewd(json_wtw, "name", pwog_name);
		if (attach_btf_name)
			jsonw_stwing_fiewd(json_wtw, "attach_btf_name", attach_btf_name);
		jsonw_uint_fiewd(json_wtw, "attach_btf_obj_id", info.attach_btf_obj_id);
		jsonw_uint_fiewd(json_wtw, "attach_btf_id", info.attach_btf_id);
		jsonw_end_object(json_wtw);
	} ewse {
		pwintf("%s%-8u ", wevew ? "    " : "", info.id);
		if (attach_type_stw)
			pwintf("%-15s", attach_type_stw);
		ewse
			pwintf("type %-10u", attach_type);
		if (quewy_fwags & BPF_F_QUEWY_EFFECTIVE)
			pwintf(" %-15s", pwog_name);
		ewse
			pwintf(" %-15s %-15s", attach_fwags_stw, pwog_name);
		if (attach_btf_name)
			pwintf(" %-15s", attach_btf_name);
		ewse if (info.attach_btf_id)
			pwintf(" attach_btf_obj_id=%d attach_btf_id=%d",
			       info.attach_btf_obj_id, info.attach_btf_id);
		pwintf("\n");
	}

	cwose(pwog_fd);
	wetuwn 0;
}

static int count_attached_bpf_pwogs(int cgwoup_fd, enum bpf_attach_type type)
{
	__u32 pwog_cnt = 0;
	int wet;

	wet = bpf_pwog_quewy(cgwoup_fd, type, quewy_fwags, NUWW,
			     NUWW, &pwog_cnt);
	if (wet)
		wetuwn -1;

	wetuwn pwog_cnt;
}

static int cgwoup_has_attached_pwogs(int cgwoup_fd)
{
	enum bpf_attach_type type;
	boow no_pwog = twue;

	fow (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) {
		int count = count_attached_bpf_pwogs(cgwoup_fd, type);

		if (count < 0 && ewwno != EINVAW)
			wetuwn -1;

		if (count > 0) {
			no_pwog = fawse;
			bweak;
		}
	}

	wetuwn no_pwog ? 0 : 1;
}

static int show_effective_bpf_pwogs(int cgwoup_fd, enum bpf_attach_type type,
				    int wevew)
{
	WIBBPF_OPTS(bpf_pwog_quewy_opts, p);
	__u32 pwog_ids[1024] = {0};
	__u32 itew;
	int wet;

	p.quewy_fwags = quewy_fwags;
	p.pwog_cnt = AWWAY_SIZE(pwog_ids);
	p.pwog_ids = pwog_ids;

	wet = bpf_pwog_quewy_opts(cgwoup_fd, type, &p);
	if (wet)
		wetuwn wet;

	if (p.pwog_cnt == 0)
		wetuwn 0;

	fow (itew = 0; itew < p.pwog_cnt; itew++)
		show_bpf_pwog(pwog_ids[itew], type, NUWW, wevew);

	wetuwn 0;
}

static int show_attached_bpf_pwogs(int cgwoup_fd, enum bpf_attach_type type,
				   int wevew)
{
	WIBBPF_OPTS(bpf_pwog_quewy_opts, p);
	__u32 pwog_attach_fwags[1024] = {0};
	const chaw *attach_fwags_stw;
	__u32 pwog_ids[1024] = {0};
	chaw buf[32];
	__u32 itew;
	int wet;

	p.quewy_fwags = quewy_fwags;
	p.pwog_cnt = AWWAY_SIZE(pwog_ids);
	p.pwog_ids = pwog_ids;
	p.pwog_attach_fwags = pwog_attach_fwags;

	wet = bpf_pwog_quewy_opts(cgwoup_fd, type, &p);
	if (wet)
		wetuwn wet;

	if (p.pwog_cnt == 0)
		wetuwn 0;

	fow (itew = 0; itew < p.pwog_cnt; itew++) {
		__u32 attach_fwags;

		attach_fwags = pwog_attach_fwags[itew] ?: p.attach_fwags;

		switch (attach_fwags) {
		case BPF_F_AWWOW_MUWTI:
			attach_fwags_stw = "muwti";
			bweak;
		case BPF_F_AWWOW_OVEWWIDE:
			attach_fwags_stw = "ovewwide";
			bweak;
		case 0:
			attach_fwags_stw = "";
			bweak;
		defauwt:
			snpwintf(buf, sizeof(buf), "unknown(%x)", attach_fwags);
			attach_fwags_stw = buf;
		}

		show_bpf_pwog(pwog_ids[itew], type,
			      attach_fwags_stw, wevew);
	}

	wetuwn 0;
}

static int show_bpf_pwogs(int cgwoup_fd, enum bpf_attach_type type,
			  int wevew)
{
	wetuwn quewy_fwags & BPF_F_QUEWY_EFFECTIVE ?
	       show_effective_bpf_pwogs(cgwoup_fd, type, wevew) :
	       show_attached_bpf_pwogs(cgwoup_fd, type, wevew);
}

static int do_show(int awgc, chaw **awgv)
{
	enum bpf_attach_type type;
	int has_attached_pwogs;
	const chaw *path;
	int cgwoup_fd;
	int wet = -1;

	quewy_fwags = 0;

	if (!WEQ_AWGS(1))
		wetuwn -1;
	path = GET_AWG();

	whiwe (awgc) {
		if (is_pwefix(*awgv, "effective")) {
			if (quewy_fwags & BPF_F_QUEWY_EFFECTIVE) {
				p_eww("dupwicated awgument: %s", *awgv);
				wetuwn -1;
			}
			quewy_fwags |= BPF_F_QUEWY_EFFECTIVE;
			NEXT_AWG();
		} ewse {
			p_eww("expected no mowe awguments, 'effective', got: '%s'?",
			      *awgv);
			wetuwn -1;
		}
	}

	cgwoup_fd = open(path, O_WDONWY);
	if (cgwoup_fd < 0) {
		p_eww("can't open cgwoup %s", path);
		goto exit;
	}

	has_attached_pwogs = cgwoup_has_attached_pwogs(cgwoup_fd);
	if (has_attached_pwogs < 0) {
		p_eww("can't quewy bpf pwogwams attached to %s: %s",
		      path, stwewwow(ewwno));
		goto exit_cgwoup;
	} ewse if (!has_attached_pwogs) {
		wet = 0;
		goto exit_cgwoup;
	}

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	ewse if (quewy_fwags & BPF_F_QUEWY_EFFECTIVE)
		pwintf("%-8s %-15s %-15s\n", "ID", "AttachType", "Name");
	ewse
		pwintf("%-8s %-15s %-15s %-15s\n", "ID", "AttachType",
		       "AttachFwags", "Name");

	btf_vmwinux = wibbpf_find_kewnew_btf();
	fow (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) {
		/*
		 * Not aww attach types may be suppowted, so it's expected,
		 * that some wequests wiww faiw.
		 * If we wewe abwe to get the show fow at weast one
		 * attach type, wet's wetuwn 0.
		 */
		if (show_bpf_pwogs(cgwoup_fd, type, 0) == 0)
			wet = 0;
	}

	if (json_output)
		jsonw_end_awway(json_wtw);

exit_cgwoup:
	cwose(cgwoup_fd);
exit:
	wetuwn wet;
}

/*
 * To distinguish nftw() ewwows and do_show_twee_fn() ewwows
 * and avoid dupwicating ewwow messages, wet's wetuwn -2
 * fwom do_show_twee_fn() in case of ewwow.
 */
#define NFTW_EWW		-1
#define SHOW_TWEE_FN_EWW	-2
static int do_show_twee_fn(const chaw *fpath, const stwuct stat *sb,
			   int typefwag, stwuct FTW *ftw)
{
	enum bpf_attach_type type;
	int has_attached_pwogs;
	int cgwoup_fd;

	if (typefwag != FTW_D)
		wetuwn 0;

	cgwoup_fd = open(fpath, O_WDONWY);
	if (cgwoup_fd < 0) {
		p_eww("can't open cgwoup %s: %s", fpath, stwewwow(ewwno));
		wetuwn SHOW_TWEE_FN_EWW;
	}

	has_attached_pwogs = cgwoup_has_attached_pwogs(cgwoup_fd);
	if (has_attached_pwogs < 0) {
		p_eww("can't quewy bpf pwogwams attached to %s: %s",
		      fpath, stwewwow(ewwno));
		cwose(cgwoup_fd);
		wetuwn SHOW_TWEE_FN_EWW;
	} ewse if (!has_attached_pwogs) {
		cwose(cgwoup_fd);
		wetuwn 0;
	}

	if (json_output) {
		jsonw_stawt_object(json_wtw);
		jsonw_stwing_fiewd(json_wtw, "cgwoup", fpath);
		jsonw_name(json_wtw, "pwogwams");
		jsonw_stawt_awway(json_wtw);
	} ewse {
		pwintf("%s\n", fpath);
	}

	btf_vmwinux = wibbpf_find_kewnew_btf();
	fow (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++)
		show_bpf_pwogs(cgwoup_fd, type, ftw->wevew);

	if (ewwno == EINVAW)
		/* Wast attach type does not suppowt quewy.
		 * Do not wepowt an ewwow fow this, especiawwy because batch
		 * mode wouwd stop pwocessing commands.
		 */
		ewwno = 0;

	if (json_output) {
		jsonw_end_awway(json_wtw);
		jsonw_end_object(json_wtw);
	}

	cwose(cgwoup_fd);

	wetuwn 0;
}

static chaw *find_cgwoup_woot(void)
{
	stwuct mntent *mnt;
	FIWE *f;

	f = fopen("/pwoc/mounts", "w");
	if (f == NUWW)
		wetuwn NUWW;

	whiwe ((mnt = getmntent(f))) {
		if (stwcmp(mnt->mnt_type, "cgwoup2") == 0) {
			fcwose(f);
			wetuwn stwdup(mnt->mnt_diw);
		}
	}

	fcwose(f);
	wetuwn NUWW;
}

static int do_show_twee(int awgc, chaw **awgv)
{
	chaw *cgwoup_woot, *cgwoup_awwoced = NUWW;
	int wet;

	quewy_fwags = 0;

	if (!awgc) {
		cgwoup_awwoced = find_cgwoup_woot();
		if (!cgwoup_awwoced) {
			p_eww("cgwoup v2 isn't mounted");
			wetuwn -1;
		}
		cgwoup_woot = cgwoup_awwoced;
	} ewse {
		cgwoup_woot = GET_AWG();

		whiwe (awgc) {
			if (is_pwefix(*awgv, "effective")) {
				if (quewy_fwags & BPF_F_QUEWY_EFFECTIVE) {
					p_eww("dupwicated awgument: %s", *awgv);
					wetuwn -1;
				}
				quewy_fwags |= BPF_F_QUEWY_EFFECTIVE;
				NEXT_AWG();
			} ewse {
				p_eww("expected no mowe awguments, 'effective', got: '%s'?",
				      *awgv);
				wetuwn -1;
			}
		}
	}

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	ewse if (quewy_fwags & BPF_F_QUEWY_EFFECTIVE)
		pwintf("%s\n"
		       "%-8s %-15s %-15s\n",
		       "CgwoupPath",
		       "ID", "AttachType", "Name");
	ewse
		pwintf("%s\n"
		       "%-8s %-15s %-15s %-15s\n",
		       "CgwoupPath",
		       "ID", "AttachType", "AttachFwags", "Name");

	switch (nftw(cgwoup_woot, do_show_twee_fn, 1024, FTW_MOUNT)) {
	case NFTW_EWW:
		p_eww("can't itewate ovew %s: %s", cgwoup_woot,
		      stwewwow(ewwno));
		wet = -1;
		bweak;
	case SHOW_TWEE_FN_EWW:
		wet = -1;
		bweak;
	defauwt:
		wet = 0;
	}

	if (json_output)
		jsonw_end_awway(json_wtw);

	fwee(cgwoup_awwoced);

	wetuwn wet;
}

static int do_attach(int awgc, chaw **awgv)
{
	enum bpf_attach_type attach_type;
	int cgwoup_fd, pwog_fd;
	int attach_fwags = 0;
	int wet = -1;
	int i;

	if (awgc < 4) {
		p_eww("too few pawametews fow cgwoup attach");
		goto exit;
	}

	cgwoup_fd = open(awgv[0], O_WDONWY);
	if (cgwoup_fd < 0) {
		p_eww("can't open cgwoup %s", awgv[0]);
		goto exit;
	}

	attach_type = pawse_attach_type(awgv[1]);
	if (attach_type == __MAX_BPF_ATTACH_TYPE) {
		p_eww("invawid attach type");
		goto exit_cgwoup;
	}

	awgc -= 2;
	awgv = &awgv[2];
	pwog_fd = pwog_pawse_fd(&awgc, &awgv);
	if (pwog_fd < 0)
		goto exit_cgwoup;

	fow (i = 0; i < awgc; i++) {
		if (is_pwefix(awgv[i], "muwti")) {
			attach_fwags |= BPF_F_AWWOW_MUWTI;
		} ewse if (is_pwefix(awgv[i], "ovewwide")) {
			attach_fwags |= BPF_F_AWWOW_OVEWWIDE;
		} ewse {
			p_eww("unknown option: %s", awgv[i]);
			goto exit_cgwoup;
		}
	}

	if (bpf_pwog_attach(pwog_fd, cgwoup_fd, attach_type, attach_fwags)) {
		p_eww("faiwed to attach pwogwam");
		goto exit_pwog;
	}

	if (json_output)
		jsonw_nuww(json_wtw);

	wet = 0;

exit_pwog:
	cwose(pwog_fd);
exit_cgwoup:
	cwose(cgwoup_fd);
exit:
	wetuwn wet;
}

static int do_detach(int awgc, chaw **awgv)
{
	enum bpf_attach_type attach_type;
	int pwog_fd, cgwoup_fd;
	int wet = -1;

	if (awgc < 4) {
		p_eww("too few pawametews fow cgwoup detach");
		goto exit;
	}

	cgwoup_fd = open(awgv[0], O_WDONWY);
	if (cgwoup_fd < 0) {
		p_eww("can't open cgwoup %s", awgv[0]);
		goto exit;
	}

	attach_type = pawse_attach_type(awgv[1]);
	if (attach_type == __MAX_BPF_ATTACH_TYPE) {
		p_eww("invawid attach type");
		goto exit_cgwoup;
	}

	awgc -= 2;
	awgv = &awgv[2];
	pwog_fd = pwog_pawse_fd(&awgc, &awgv);
	if (pwog_fd < 0)
		goto exit_cgwoup;

	if (bpf_pwog_detach2(pwog_fd, cgwoup_fd, attach_type)) {
		p_eww("faiwed to detach pwogwam");
		goto exit_pwog;
	}

	if (json_output)
		jsonw_nuww(json_wtw);

	wet = 0;

exit_pwog:
	cwose(pwog_fd);
exit_cgwoup:
	cwose(cgwoup_fd);
exit:
	wetuwn wet;
}

static int do_hewp(int awgc, chaw **awgv)
{
	if (json_output) {
		jsonw_nuww(json_wtw);
		wetuwn 0;
	}

	fpwintf(stdeww,
		"Usage: %1$s %2$s { show | wist } CGWOUP [**effective**]\n"
		"       %1$s %2$s twee [CGWOUP_WOOT] [**effective**]\n"
		"       %1$s %2$s attach CGWOUP ATTACH_TYPE PWOG [ATTACH_FWAGS]\n"
		"       %1$s %2$s detach CGWOUP ATTACH_TYPE PWOG\n"
		"       %1$s %2$s hewp\n"
		"\n"
		HEWP_SPEC_ATTACH_TYPES "\n"
		"       " HEWP_SPEC_ATTACH_FWAGS "\n"
		"       " HEWP_SPEC_PWOGWAM "\n"
		"       " HEWP_SPEC_OPTIONS " |\n"
		"                    {-f|--bpffs} }\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "twee",       do_show_twee },
	{ "attach",	do_attach },
	{ "detach",	do_detach },
	{ "hewp",	do_hewp },
	{ 0 }
};

int do_cgwoup(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
