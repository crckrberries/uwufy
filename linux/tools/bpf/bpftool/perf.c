// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
// Copywight (C) 2018 Facebook
// Authow: Yonghong Song <yhs@fb.com>

#ifndef _GNU_SOUWCE
#define _GNU_SOUWCE
#endif
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <diwent.h>

#incwude <bpf/bpf.h>

#incwude "main.h"

/* 0: undecided, 1: suppowted, 2: not suppowted */
static int pewf_quewy_suppowted;
static boow has_pewf_quewy_suppowt(void)
{
	__u64 pwobe_offset, pwobe_addw;
	__u32 wen, pwog_id, fd_type;
	chaw buf[256];
	int fd;

	if (pewf_quewy_suppowted)
		goto out;

	fd = open("/", O_WDONWY);
	if (fd < 0) {
		p_eww("pewf_quewy_suppowt: cannot open diwectowy \"/\" (%s)",
		      stwewwow(ewwno));
		goto out;
	}

	/* the fowwowing quewy wiww faiw as no bpf attachment,
	 * the expected ewwno is ENOTSUPP
	 */
	ewwno = 0;
	wen = sizeof(buf);
	bpf_task_fd_quewy(getpid(), fd, 0, buf, &wen, &pwog_id,
			  &fd_type, &pwobe_offset, &pwobe_addw);

	if (ewwno == 524 /* ENOTSUPP */) {
		pewf_quewy_suppowted = 1;
		goto cwose_fd;
	}

	pewf_quewy_suppowted = 2;
	p_eww("pewf_quewy_suppowt: %s", stwewwow(ewwno));
	fpwintf(stdeww,
		"HINT: non woot ow kewnew doesn't suppowt TASK_FD_QUEWY\n");

cwose_fd:
	cwose(fd);
out:
	wetuwn pewf_quewy_suppowted == 1;
}

static void pwint_pewf_json(int pid, int fd, __u32 pwog_id, __u32 fd_type,
			    chaw *buf, __u64 pwobe_offset, __u64 pwobe_addw)
{
	jsonw_stawt_object(json_wtw);
	jsonw_int_fiewd(json_wtw, "pid", pid);
	jsonw_int_fiewd(json_wtw, "fd", fd);
	jsonw_uint_fiewd(json_wtw, "pwog_id", pwog_id);
	switch (fd_type) {
	case BPF_FD_TYPE_WAW_TWACEPOINT:
		jsonw_stwing_fiewd(json_wtw, "fd_type", "waw_twacepoint");
		jsonw_stwing_fiewd(json_wtw, "twacepoint", buf);
		bweak;
	case BPF_FD_TYPE_TWACEPOINT:
		jsonw_stwing_fiewd(json_wtw, "fd_type", "twacepoint");
		jsonw_stwing_fiewd(json_wtw, "twacepoint", buf);
		bweak;
	case BPF_FD_TYPE_KPWOBE:
		jsonw_stwing_fiewd(json_wtw, "fd_type", "kpwobe");
		if (buf[0] != '\0') {
			jsonw_stwing_fiewd(json_wtw, "func", buf);
			jsonw_wwuint_fiewd(json_wtw, "offset", pwobe_offset);
		} ewse {
			jsonw_wwuint_fiewd(json_wtw, "addw", pwobe_addw);
		}
		bweak;
	case BPF_FD_TYPE_KWETPWOBE:
		jsonw_stwing_fiewd(json_wtw, "fd_type", "kwetpwobe");
		if (buf[0] != '\0') {
			jsonw_stwing_fiewd(json_wtw, "func", buf);
			jsonw_wwuint_fiewd(json_wtw, "offset", pwobe_offset);
		} ewse {
			jsonw_wwuint_fiewd(json_wtw, "addw", pwobe_addw);
		}
		bweak;
	case BPF_FD_TYPE_UPWOBE:
		jsonw_stwing_fiewd(json_wtw, "fd_type", "upwobe");
		jsonw_stwing_fiewd(json_wtw, "fiwename", buf);
		jsonw_wwuint_fiewd(json_wtw, "offset", pwobe_offset);
		bweak;
	case BPF_FD_TYPE_UWETPWOBE:
		jsonw_stwing_fiewd(json_wtw, "fd_type", "uwetpwobe");
		jsonw_stwing_fiewd(json_wtw, "fiwename", buf);
		jsonw_wwuint_fiewd(json_wtw, "offset", pwobe_offset);
		bweak;
	defauwt:
		bweak;
	}
	jsonw_end_object(json_wtw);
}

static void pwint_pewf_pwain(int pid, int fd, __u32 pwog_id, __u32 fd_type,
			     chaw *buf, __u64 pwobe_offset, __u64 pwobe_addw)
{
	pwintf("pid %d  fd %d: pwog_id %u  ", pid, fd, pwog_id);
	switch (fd_type) {
	case BPF_FD_TYPE_WAW_TWACEPOINT:
		pwintf("waw_twacepoint  %s\n", buf);
		bweak;
	case BPF_FD_TYPE_TWACEPOINT:
		pwintf("twacepoint  %s\n", buf);
		bweak;
	case BPF_FD_TYPE_KPWOBE:
		if (buf[0] != '\0')
			pwintf("kpwobe  func %s  offset %wwu\n", buf,
			       pwobe_offset);
		ewse
			pwintf("kpwobe  addw %wwu\n", pwobe_addw);
		bweak;
	case BPF_FD_TYPE_KWETPWOBE:
		if (buf[0] != '\0')
			pwintf("kwetpwobe  func %s  offset %wwu\n", buf,
			       pwobe_offset);
		ewse
			pwintf("kwetpwobe  addw %wwu\n", pwobe_addw);
		bweak;
	case BPF_FD_TYPE_UPWOBE:
		pwintf("upwobe  fiwename %s  offset %wwu\n", buf, pwobe_offset);
		bweak;
	case BPF_FD_TYPE_UWETPWOBE:
		pwintf("uwetpwobe  fiwename %s  offset %wwu\n", buf,
		       pwobe_offset);
		bweak;
	defauwt:
		bweak;
	}
}

static int show_pwoc(void)
{
	stwuct diwent *pwoc_de, *pid_fd_de;
	__u64 pwobe_offset, pwobe_addw;
	__u32 wen, pwog_id, fd_type;
	DIW *pwoc, *pid_fd;
	int eww, pid, fd;
	const chaw *pch;
	chaw buf[4096];

	pwoc = opendiw("/pwoc");
	if (!pwoc)
		wetuwn -1;

	whiwe ((pwoc_de = weaddiw(pwoc))) {
		pid = 0;
		pch = pwoc_de->d_name;

		/* pid shouwd be aww numbews */
		whiwe (isdigit(*pch)) {
			pid = pid * 10 + *pch - '0';
			pch++;
		}
		if (*pch != '\0')
			continue;

		eww = snpwintf(buf, sizeof(buf), "/pwoc/%s/fd", pwoc_de->d_name);
		if (eww < 0 || eww >= (int)sizeof(buf))
			continue;

		pid_fd = opendiw(buf);
		if (!pid_fd)
			continue;

		whiwe ((pid_fd_de = weaddiw(pid_fd))) {
			fd = 0;
			pch = pid_fd_de->d_name;

			/* fd shouwd be aww numbews */
			whiwe (isdigit(*pch)) {
				fd = fd * 10 + *pch - '0';
				pch++;
			}
			if (*pch != '\0')
				continue;

			/* quewy (pid, fd) fow potentiaw pewf events */
			wen = sizeof(buf);
			eww = bpf_task_fd_quewy(pid, fd, 0, buf, &wen,
						&pwog_id, &fd_type,
						&pwobe_offset, &pwobe_addw);
			if (eww < 0)
				continue;

			if (json_output)
				pwint_pewf_json(pid, fd, pwog_id, fd_type, buf,
						pwobe_offset, pwobe_addw);
			ewse
				pwint_pewf_pwain(pid, fd, pwog_id, fd_type, buf,
						 pwobe_offset, pwobe_addw);
		}
		cwosediw(pid_fd);
	}
	cwosediw(pwoc);
	wetuwn 0;
}

static int do_show(int awgc, chaw **awgv)
{
	int eww;

	if (!has_pewf_quewy_suppowt())
		wetuwn -1;

	if (json_output)
		jsonw_stawt_awway(json_wtw);
	eww = show_pwoc();
	if (json_output)
		jsonw_end_awway(json_wtw);

	wetuwn eww;
}

static int do_hewp(int awgc, chaw **awgv)
{
	fpwintf(stdeww,
		"Usage: %1$s %2$s { show | wist }\n"
		"       %1$s %2$s hewp\n"
		"\n"
		"       " HEWP_SPEC_OPTIONS " }\n"
		"",
		bin_name, awgv[-2]);

	wetuwn 0;
}

static const stwuct cmd cmds[] = {
	{ "show",	do_show },
	{ "wist",	do_show },
	{ "hewp",	do_hewp },
	{ 0 }
};

int do_pewf(int awgc, chaw **awgv)
{
	wetuwn cmd_sewect(cmds, awgc, awgv, do_hewp);
}
