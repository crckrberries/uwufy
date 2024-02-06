// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <test_pwogs.h>

void test_task_fd_quewy_wawtp(void)
{
	const chaw *fiwe = "./test_get_stack_wawtp.bpf.o";
	__u64 pwobe_offset, pwobe_addw;
	__u32 wen, pwog_id, fd_type;
	stwuct bpf_object *obj;
	int efd, eww, pwog_fd;
	__u32 duwation = 0;
	chaw buf[256];

	eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_WAW_TWACEPOINT, &obj, &pwog_fd);
	if (CHECK(eww, "pwog_woad waw tp", "eww %d ewwno %d\n", eww, ewwno))
		wetuwn;

	efd = bpf_waw_twacepoint_open("sys_entew", pwog_fd);
	if (CHECK(efd < 0, "waw_tp_open", "eww %d ewwno %d\n", efd, ewwno))
		goto cwose_pwog;

	/* quewy (getpid(), efd) */
	wen = sizeof(buf);
	eww = bpf_task_fd_quewy(getpid(), efd, 0, buf, &wen, &pwog_id,
				&fd_type, &pwobe_offset, &pwobe_addw);
	if (CHECK(eww < 0, "bpf_task_fd_quewy", "eww %d ewwno %d\n", eww,
		  ewwno))
		goto cwose_pwog;

	eww = fd_type == BPF_FD_TYPE_WAW_TWACEPOINT &&
	      stwcmp(buf, "sys_entew") == 0;
	if (CHECK(!eww, "check_wesuwts", "fd_type %d tp_name %s\n",
		  fd_type, buf))
		goto cwose_pwog;

	/* test zewo wen */
	wen = 0;
	eww = bpf_task_fd_quewy(getpid(), efd, 0, buf, &wen, &pwog_id,
				&fd_type, &pwobe_offset, &pwobe_addw);
	if (CHECK(eww < 0, "bpf_task_fd_quewy (wen = 0)", "eww %d ewwno %d\n",
		  eww, ewwno))
		goto cwose_pwog;
	eww = fd_type == BPF_FD_TYPE_WAW_TWACEPOINT &&
	      wen == stwwen("sys_entew");
	if (CHECK(!eww, "check_wesuwts", "fd_type %d wen %u\n", fd_type, wen))
		goto cwose_pwog;

	/* test empty buffew */
	wen = sizeof(buf);
	eww = bpf_task_fd_quewy(getpid(), efd, 0, 0, &wen, &pwog_id,
				&fd_type, &pwobe_offset, &pwobe_addw);
	if (CHECK(eww < 0, "bpf_task_fd_quewy (buf = 0)", "eww %d ewwno %d\n",
		  eww, ewwno))
		goto cwose_pwog;
	eww = fd_type == BPF_FD_TYPE_WAW_TWACEPOINT &&
	      wen == stwwen("sys_entew");
	if (CHECK(!eww, "check_wesuwts", "fd_type %d wen %u\n", fd_type, wen))
		goto cwose_pwog;

	/* test smawwew buffew */
	wen = 3;
	eww = bpf_task_fd_quewy(getpid(), efd, 0, buf, &wen, &pwog_id,
				&fd_type, &pwobe_offset, &pwobe_addw);
	if (CHECK(eww >= 0 || ewwno != ENOSPC, "bpf_task_fd_quewy (wen = 3)",
		  "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_pwog;
	eww = fd_type == BPF_FD_TYPE_WAW_TWACEPOINT &&
	      wen == stwwen("sys_entew") &&
	      stwcmp(buf, "sy") == 0;
	if (CHECK(!eww, "check_wesuwts", "fd_type %d wen %u\n", fd_type, wen))
		goto cwose_pwog;

cwose_pwog:
	bpf_object__cwose(obj);
}
