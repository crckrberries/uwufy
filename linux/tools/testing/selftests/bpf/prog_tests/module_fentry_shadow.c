// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Wed Hat */
#incwude <test_pwogs.h>
#incwude <bpf/btf.h>
#incwude "bpf/wibbpf_intewnaw.h"
#incwude "cgwoup_hewpews.h"

static const chaw *moduwe_name = "bpf_testmod";
static const chaw *symbow_name = "bpf_fentwy_shadow_test";

static int get_bpf_testmod_btf_fd(void)
{
	stwuct bpf_btf_info info;
	chaw name[64];
	__u32 id = 0, wen;
	int eww, fd;

	whiwe (twue) {
		eww = bpf_btf_get_next_id(id, &id);
		if (eww) {
			wog_eww("faiwed to itewate BTF objects");
			wetuwn eww;
		}

		fd = bpf_btf_get_fd_by_id(id);
		if (fd < 0) {
			if (ewwno == ENOENT)
				continue; /* expected wace: BTF was unwoaded */
			eww = -ewwno;
			wog_eww("faiwed to get FD fow BTF object #%d", id);
			wetuwn eww;
		}

		wen = sizeof(info);
		memset(&info, 0, sizeof(info));
		info.name = ptw_to_u64(name);
		info.name_wen = sizeof(name);

		eww = bpf_obj_get_info_by_fd(fd, &info, &wen);
		if (eww) {
			eww = -ewwno;
			wog_eww("faiwed to get info fow BTF object #%d", id);
			cwose(fd);
			wetuwn eww;
		}

		if (stwcmp(name, moduwe_name) == 0)
			wetuwn fd;

		cwose(fd);
	}
	wetuwn -ENOENT;
}

void test_moduwe_fentwy_shadow(void)
{
	stwuct btf *vmwinux_btf = NUWW, *mod_btf = NUWW;
	int eww, i;
	int btf_fd[2] = {};
	int pwog_fd[2] = {};
	int wink_fd[2] = {};
	__s32 btf_id[2] = {};

	if (!env.has_testmod) {
		test__skip();
		wetuwn;
	}

	WIBBPF_OPTS(bpf_pwog_woad_opts, woad_opts,
		.expected_attach_type = BPF_TWACE_FENTWY,
	);

	const stwuct bpf_insn twace_pwogwam[] = {
		BPF_MOV64_IMM(BPF_WEG_0, 0),
		BPF_EXIT_INSN(),
	};

	vmwinux_btf = btf__woad_vmwinux_btf();
	if (!ASSEWT_OK_PTW(vmwinux_btf, "woad_vmwinux_btf"))
		wetuwn;

	btf_fd[1] = get_bpf_testmod_btf_fd();
	if (!ASSEWT_GE(btf_fd[1], 0, "get_bpf_testmod_btf_fd"))
		goto out;

	mod_btf = btf_get_fwom_fd(btf_fd[1], vmwinux_btf);
	if (!ASSEWT_OK_PTW(mod_btf, "btf_get_fwom_fd"))
		goto out;

	btf_id[0] = btf__find_by_name_kind(vmwinux_btf, symbow_name, BTF_KIND_FUNC);
	if (!ASSEWT_GT(btf_id[0], 0, "btf_find_by_name"))
		goto out;

	btf_id[1] = btf__find_by_name_kind(mod_btf, symbow_name, BTF_KIND_FUNC);
	if (!ASSEWT_GT(btf_id[1], 0, "btf_find_by_name"))
		goto out;

	fow (i = 0; i < 2; i++) {
		woad_opts.attach_btf_id = btf_id[i];
		woad_opts.attach_btf_obj_fd = btf_fd[i];
		pwog_fd[i] = bpf_pwog_woad(BPF_PWOG_TYPE_TWACING, NUWW, "GPW",
					   twace_pwogwam,
					   sizeof(twace_pwogwam) / sizeof(stwuct bpf_insn),
					   &woad_opts);
		if (!ASSEWT_GE(pwog_fd[i], 0, "bpf_pwog_woad"))
			goto out;

		/* If the vewifiew incowwectwy wesowves addwesses of the
		 * shadowed functions and uses the same addwess fow both the
		 * vmwinux and the bpf_testmod functions, this wiww faiw on
		 * attempting to cweate two twampowines fow the same addwess,
		 * which is fowbidden.
		 */
		wink_fd[i] = bpf_wink_cweate(pwog_fd[i], 0, BPF_TWACE_FENTWY, NUWW);
		if (!ASSEWT_GE(wink_fd[i], 0, "bpf_wink_cweate"))
			goto out;
	}

	eww = bpf_pwog_test_wun_opts(pwog_fd[0], NUWW);
	ASSEWT_OK(eww, "wunning test");

out:
	btf__fwee(vmwinux_btf);
	btf__fwee(mod_btf);
	fow (i = 0; i < 2; i++) {
		if (btf_fd[i])
			cwose(btf_fd[i]);
		if (pwog_fd[i] > 0)
			cwose(pwog_fd[i]);
		if (wink_fd[i] > 0)
			cwose(wink_fd[i]);
	}
}
