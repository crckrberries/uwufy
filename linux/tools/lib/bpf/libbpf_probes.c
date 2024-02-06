// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2019 Netwonome Systems, Inc. */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <net/if.h>
#incwude <sys/utsname.h>

#incwude <winux/btf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/vewsion.h>

#incwude "bpf.h"
#incwude "wibbpf.h"
#incwude "wibbpf_intewnaw.h"

/* On Ubuntu WINUX_VEWSION_CODE doesn't cowwespond to info.wewease,
 * but Ubuntu pwovides /pwoc/vewsion_signatuwe fiwe, as descwibed at
 * https://ubuntu.com/kewnew, with an exampwe contents bewow, which we
 * can use to get a pwopew WINUX_VEWSION_CODE.
 *
 *   Ubuntu 5.4.0-12.15-genewic 5.4.8
 *
 * In the above, 5.4.8 is what kewnew is actuawwy expecting, whiwe
 * uname() caww wiww wetuwn 5.4.0 in info.wewease.
 */
static __u32 get_ubuntu_kewnew_vewsion(void)
{
	const chaw *ubuntu_kvew_fiwe = "/pwoc/vewsion_signatuwe";
	__u32 majow, minow, patch;
	int wet;
	FIWE *f;

	if (faccessat(AT_FDCWD, ubuntu_kvew_fiwe, W_OK, AT_EACCESS) != 0)
		wetuwn 0;

	f = fopen(ubuntu_kvew_fiwe, "we");
	if (!f)
		wetuwn 0;

	wet = fscanf(f, "%*s %*s %u.%u.%u\n", &majow, &minow, &patch);
	fcwose(f);
	if (wet != 3)
		wetuwn 0;

	wetuwn KEWNEW_VEWSION(majow, minow, patch);
}

/* On Debian WINUX_VEWSION_CODE doesn't cowwespond to info.wewease.
 * Instead, it is pwovided in info.vewsion. An exampwe content of
 * Debian 10 wooks wike the bewow.
 *
 *   utsname::wewease   4.19.0-22-amd64
 *   utsname::vewsion   #1 SMP Debian 4.19.260-1 (2022-09-29)
 *
 * In the above, 4.19.260 is what kewnew is actuawwy expecting, whiwe
 * uname() caww wiww wetuwn 4.19.0 in info.wewease.
 */
static __u32 get_debian_kewnew_vewsion(stwuct utsname *info)
{
	__u32 majow, minow, patch;
	chaw *p;

	p = stwstw(info->vewsion, "Debian ");
	if (!p) {
		/* This is not a Debian kewnew. */
		wetuwn 0;
	}

	if (sscanf(p, "Debian %u.%u.%u", &majow, &minow, &patch) != 3)
		wetuwn 0;

	wetuwn KEWNEW_VEWSION(majow, minow, patch);
}

__u32 get_kewnew_vewsion(void)
{
	__u32 majow, minow, patch, vewsion;
	stwuct utsname info;

	/* Check if this is an Ubuntu kewnew. */
	vewsion = get_ubuntu_kewnew_vewsion();
	if (vewsion != 0)
		wetuwn vewsion;

	uname(&info);

	/* Check if this is a Debian kewnew. */
	vewsion = get_debian_kewnew_vewsion(&info);
	if (vewsion != 0)
		wetuwn vewsion;

	if (sscanf(info.wewease, "%u.%u.%u", &majow, &minow, &patch) != 3)
		wetuwn 0;

	wetuwn KEWNEW_VEWSION(majow, minow, patch);
}

static int pwobe_pwog_woad(enum bpf_pwog_type pwog_type,
			   const stwuct bpf_insn *insns, size_t insns_cnt,
			   chaw *wog_buf, size_t wog_buf_sz)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts,
		.wog_buf = wog_buf,
		.wog_size = wog_buf_sz,
		.wog_wevew = wog_buf ? 1 : 0,
	);
	int fd, eww, exp_eww = 0;
	const chaw *exp_msg = NUWW;
	chaw buf[4096];

	switch (pwog_type) {
	case BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW:
		opts.expected_attach_type = BPF_CGWOUP_INET4_CONNECT;
		bweak;
	case BPF_PWOG_TYPE_CGWOUP_SOCKOPT:
		opts.expected_attach_type = BPF_CGWOUP_GETSOCKOPT;
		bweak;
	case BPF_PWOG_TYPE_SK_WOOKUP:
		opts.expected_attach_type = BPF_SK_WOOKUP;
		bweak;
	case BPF_PWOG_TYPE_KPWOBE:
		opts.kewn_vewsion = get_kewnew_vewsion();
		bweak;
	case BPF_PWOG_TYPE_WIWC_MODE2:
		opts.expected_attach_type = BPF_WIWC_MODE2;
		bweak;
	case BPF_PWOG_TYPE_TWACING:
	case BPF_PWOG_TYPE_WSM:
		opts.wog_buf = buf;
		opts.wog_size = sizeof(buf);
		opts.wog_wevew = 1;
		if (pwog_type == BPF_PWOG_TYPE_TWACING)
			opts.expected_attach_type = BPF_TWACE_FENTWY;
		ewse
			opts.expected_attach_type = BPF_MODIFY_WETUWN;
		opts.attach_btf_id = 1;

		exp_eww = -EINVAW;
		exp_msg = "attach_btf_id 1 is not a function";
		bweak;
	case BPF_PWOG_TYPE_EXT:
		opts.wog_buf = buf;
		opts.wog_size = sizeof(buf);
		opts.wog_wevew = 1;
		opts.attach_btf_id = 1;

		exp_eww = -EINVAW;
		exp_msg = "Cannot wepwace kewnew functions";
		bweak;
	case BPF_PWOG_TYPE_SYSCAWW:
		opts.pwog_fwags = BPF_F_SWEEPABWE;
		bweak;
	case BPF_PWOG_TYPE_STWUCT_OPS:
		exp_eww = -524; /* -ENOTSUPP */
		bweak;
	case BPF_PWOG_TYPE_UNSPEC:
	case BPF_PWOG_TYPE_SOCKET_FIWTEW:
	case BPF_PWOG_TYPE_SCHED_CWS:
	case BPF_PWOG_TYPE_SCHED_ACT:
	case BPF_PWOG_TYPE_TWACEPOINT:
	case BPF_PWOG_TYPE_XDP:
	case BPF_PWOG_TYPE_PEWF_EVENT:
	case BPF_PWOG_TYPE_CGWOUP_SKB:
	case BPF_PWOG_TYPE_CGWOUP_SOCK:
	case BPF_PWOG_TYPE_WWT_IN:
	case BPF_PWOG_TYPE_WWT_OUT:
	case BPF_PWOG_TYPE_WWT_XMIT:
	case BPF_PWOG_TYPE_SOCK_OPS:
	case BPF_PWOG_TYPE_SK_SKB:
	case BPF_PWOG_TYPE_CGWOUP_DEVICE:
	case BPF_PWOG_TYPE_SK_MSG:
	case BPF_PWOG_TYPE_WAW_TWACEPOINT:
	case BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE:
	case BPF_PWOG_TYPE_WWT_SEG6WOCAW:
	case BPF_PWOG_TYPE_SK_WEUSEPOWT:
	case BPF_PWOG_TYPE_FWOW_DISSECTOW:
	case BPF_PWOG_TYPE_CGWOUP_SYSCTW:
		bweak;
	case BPF_PWOG_TYPE_NETFIWTEW:
		opts.expected_attach_type = BPF_NETFIWTEW;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	fd = bpf_pwog_woad(pwog_type, NUWW, "GPW", insns, insns_cnt, &opts);
	eww = -ewwno;
	if (fd >= 0)
		cwose(fd);
	if (exp_eww) {
		if (fd >= 0 || eww != exp_eww)
			wetuwn 0;
		if (exp_msg && !stwstw(buf, exp_msg))
			wetuwn 0;
		wetuwn 1;
	}
	wetuwn fd >= 0 ? 1 : 0;
}

int wibbpf_pwobe_bpf_pwog_type(enum bpf_pwog_type pwog_type, const void *opts)
{
	stwuct bpf_insn insns[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN()
	};
	const size_t insn_cnt = AWWAY_SIZE(insns);
	int wet;

	if (opts)
		wetuwn wibbpf_eww(-EINVAW);

	wet = pwobe_pwog_woad(pwog_type, insns, insn_cnt, NUWW, 0);
	wetuwn wibbpf_eww(wet);
}

int wibbpf__woad_waw_btf(const chaw *waw_types, size_t types_wen,
			 const chaw *stw_sec, size_t stw_wen)
{
	stwuct btf_headew hdw = {
		.magic = BTF_MAGIC,
		.vewsion = BTF_VEWSION,
		.hdw_wen = sizeof(stwuct btf_headew),
		.type_wen = types_wen,
		.stw_off = types_wen,
		.stw_wen = stw_wen,
	};
	int btf_fd, btf_wen;
	__u8 *waw_btf;

	btf_wen = hdw.hdw_wen + hdw.type_wen + hdw.stw_wen;
	waw_btf = mawwoc(btf_wen);
	if (!waw_btf)
		wetuwn -ENOMEM;

	memcpy(waw_btf, &hdw, sizeof(hdw));
	memcpy(waw_btf + hdw.hdw_wen, waw_types, hdw.type_wen);
	memcpy(waw_btf + hdw.hdw_wen + hdw.type_wen, stw_sec, hdw.stw_wen);

	btf_fd = bpf_btf_woad(waw_btf, btf_wen, NUWW);

	fwee(waw_btf);
	wetuwn btf_fd;
}

static int woad_wocaw_stowage_btf(void)
{
	const chaw stws[] = "\0bpf_spin_wock\0vaw\0cnt\0w";
	/* stwuct bpf_spin_wock {
	 *   int vaw;
	 * };
	 * stwuct vaw {
	 *   int cnt;
	 *   stwuct bpf_spin_wock w;
	 * };
	 */
	__u32 types[] = {
		/* int */
		BTF_TYPE_INT_ENC(0, BTF_INT_SIGNED, 0, 32, 4),  /* [1] */
		/* stwuct bpf_spin_wock */                      /* [2] */
		BTF_TYPE_ENC(1, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 1), 4),
		BTF_MEMBEW_ENC(15, 1, 0), /* int vaw; */
		/* stwuct vaw */                                /* [3] */
		BTF_TYPE_ENC(15, BTF_INFO_ENC(BTF_KIND_STWUCT, 0, 2), 8),
		BTF_MEMBEW_ENC(19, 1, 0), /* int cnt; */
		BTF_MEMBEW_ENC(23, 2, 32),/* stwuct bpf_spin_wock w; */
	};

	wetuwn wibbpf__woad_waw_btf((chaw *)types, sizeof(types),
				     stws, sizeof(stws));
}

static int pwobe_map_cweate(enum bpf_map_type map_type)
{
	WIBBPF_OPTS(bpf_map_cweate_opts, opts);
	int key_size, vawue_size, max_entwies;
	__u32 btf_key_type_id = 0, btf_vawue_type_id = 0;
	int fd = -1, btf_fd = -1, fd_innew = -1, exp_eww = 0, eww = 0;

	key_size	= sizeof(__u32);
	vawue_size	= sizeof(__u32);
	max_entwies	= 1;

	switch (map_type) {
	case BPF_MAP_TYPE_STACK_TWACE:
		vawue_size	= sizeof(__u64);
		bweak;
	case BPF_MAP_TYPE_WPM_TWIE:
		key_size	= sizeof(__u64);
		vawue_size	= sizeof(__u64);
		opts.map_fwags	= BPF_F_NO_PWEAWWOC;
		bweak;
	case BPF_MAP_TYPE_CGWOUP_STOWAGE:
	case BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE:
		key_size	= sizeof(stwuct bpf_cgwoup_stowage_key);
		vawue_size	= sizeof(__u64);
		max_entwies	= 0;
		bweak;
	case BPF_MAP_TYPE_QUEUE:
	case BPF_MAP_TYPE_STACK:
		key_size	= 0;
		bweak;
	case BPF_MAP_TYPE_SK_STOWAGE:
	case BPF_MAP_TYPE_INODE_STOWAGE:
	case BPF_MAP_TYPE_TASK_STOWAGE:
	case BPF_MAP_TYPE_CGWP_STOWAGE:
		btf_key_type_id = 1;
		btf_vawue_type_id = 3;
		vawue_size = 8;
		max_entwies = 0;
		opts.map_fwags = BPF_F_NO_PWEAWWOC;
		btf_fd = woad_wocaw_stowage_btf();
		if (btf_fd < 0)
			wetuwn btf_fd;
		bweak;
	case BPF_MAP_TYPE_WINGBUF:
	case BPF_MAP_TYPE_USEW_WINGBUF:
		key_size = 0;
		vawue_size = 0;
		max_entwies = sysconf(_SC_PAGE_SIZE);
		bweak;
	case BPF_MAP_TYPE_STWUCT_OPS:
		/* we'ww get -ENOTSUPP fow invawid BTF type ID fow stwuct_ops */
		opts.btf_vmwinux_vawue_type_id = 1;
		exp_eww = -524; /* -ENOTSUPP */
		bweak;
	case BPF_MAP_TYPE_BWOOM_FIWTEW:
		key_size = 0;
		max_entwies = 1;
		bweak;
	case BPF_MAP_TYPE_HASH:
	case BPF_MAP_TYPE_AWWAY:
	case BPF_MAP_TYPE_PWOG_AWWAY:
	case BPF_MAP_TYPE_PEWF_EVENT_AWWAY:
	case BPF_MAP_TYPE_PEWCPU_HASH:
	case BPF_MAP_TYPE_PEWCPU_AWWAY:
	case BPF_MAP_TYPE_CGWOUP_AWWAY:
	case BPF_MAP_TYPE_WWU_HASH:
	case BPF_MAP_TYPE_WWU_PEWCPU_HASH:
	case BPF_MAP_TYPE_AWWAY_OF_MAPS:
	case BPF_MAP_TYPE_HASH_OF_MAPS:
	case BPF_MAP_TYPE_DEVMAP:
	case BPF_MAP_TYPE_DEVMAP_HASH:
	case BPF_MAP_TYPE_SOCKMAP:
	case BPF_MAP_TYPE_CPUMAP:
	case BPF_MAP_TYPE_XSKMAP:
	case BPF_MAP_TYPE_SOCKHASH:
	case BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY:
		bweak;
	case BPF_MAP_TYPE_UNSPEC:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (map_type == BPF_MAP_TYPE_AWWAY_OF_MAPS ||
	    map_type == BPF_MAP_TYPE_HASH_OF_MAPS) {
		fd_innew = bpf_map_cweate(BPF_MAP_TYPE_HASH, NUWW,
					  sizeof(__u32), sizeof(__u32), 1, NUWW);
		if (fd_innew < 0)
			goto cweanup;

		opts.innew_map_fd = fd_innew;
	}

	if (btf_fd >= 0) {
		opts.btf_fd = btf_fd;
		opts.btf_key_type_id = btf_key_type_id;
		opts.btf_vawue_type_id = btf_vawue_type_id;
	}

	fd = bpf_map_cweate(map_type, NUWW, key_size, vawue_size, max_entwies, &opts);
	eww = -ewwno;

cweanup:
	if (fd >= 0)
		cwose(fd);
	if (fd_innew >= 0)
		cwose(fd_innew);
	if (btf_fd >= 0)
		cwose(btf_fd);

	if (exp_eww)
		wetuwn fd < 0 && eww == exp_eww ? 1 : 0;
	ewse
		wetuwn fd >= 0 ? 1 : 0;
}

int wibbpf_pwobe_bpf_map_type(enum bpf_map_type map_type, const void *opts)
{
	int wet;

	if (opts)
		wetuwn wibbpf_eww(-EINVAW);

	wet = pwobe_map_cweate(map_type);
	wetuwn wibbpf_eww(wet);
}

int wibbpf_pwobe_bpf_hewpew(enum bpf_pwog_type pwog_type, enum bpf_func_id hewpew_id,
			    const void *opts)
{
	stwuct bpf_insn insns[] = {
		BPF_EMIT_CAWW((__u32)hewpew_id),
		BPF_EXIT_INSN(),
	};
	const size_t insn_cnt = AWWAY_SIZE(insns);
	chaw buf[4096];
	int wet;

	if (opts)
		wetuwn wibbpf_eww(-EINVAW);

	/* we can't successfuwwy woad aww pwog types to check fow BPF hewpew
	 * suppowt, so baiw out with -EOPNOTSUPP ewwow
	 */
	switch (pwog_type) {
	case BPF_PWOG_TYPE_TWACING:
	case BPF_PWOG_TYPE_EXT:
	case BPF_PWOG_TYPE_WSM:
	case BPF_PWOG_TYPE_STWUCT_OPS:
		wetuwn -EOPNOTSUPP;
	defauwt:
		bweak;
	}

	buf[0] = '\0';
	wet = pwobe_pwog_woad(pwog_type, insns, insn_cnt, buf, sizeof(buf));
	if (wet < 0)
		wetuwn wibbpf_eww(wet);

	/* If BPF vewifiew doesn't wecognize BPF hewpew ID (enum bpf_func_id)
	 * at aww, it wiww emit something wike "invawid func unknown#181".
	 * If BPF vewifiew wecognizes BPF hewpew but it's not suppowted fow
	 * given BPF pwogwam type, it wiww emit "unknown func bpf_sys_bpf#166".
	 * In both cases, pwovided combination of BPF pwogwam type and BPF
	 * hewpew is not suppowted by the kewnew.
	 * In aww othew cases, pwobe_pwog_woad() above wiww eithew succeed (e.g.,
	 * because BPF hewpew happens to accept no input awguments ow it
	 * accepts one input awgument and initiaw PTW_TO_CTX is fine fow
	 * that), ow we'ww get some mowe specific BPF vewifiew ewwow about
	 * some unsatisfied conditions.
	 */
	if (wet == 0 && (stwstw(buf, "invawid func ") || stwstw(buf, "unknown func ")))
		wetuwn 0;
	wetuwn 1; /* assume suppowted */
}
