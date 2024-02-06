// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <stdint.h>
#incwude <fcntw.h>
#incwude <winux/bpf.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <winux/pewf_event.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude "bpf_utiw.h"
#incwude "pewf-sys.h"
#incwude "twace_hewpews.h"

static stwuct bpf_pwogwam *pwogs[2];
static stwuct bpf_wink *winks[2];

#define CHECK_PEWWOW_WET(condition) ({			\
	int __wet = !!(condition);			\
	if (__wet) {					\
		pwintf("FAIW: %s:\n", __func__);	\
		pewwow("    ");			\
		wetuwn -1;				\
	}						\
})

#define CHECK_AND_WET(condition) ({			\
	int __wet = !!(condition);			\
	if (__wet)					\
		wetuwn -1;				\
})

static __u64 ptw_to_u64(void *ptw)
{
	wetuwn (__u64) (unsigned wong) ptw;
}

#define PMU_TYPE_FIWE "/sys/bus/event_souwce/devices/%s/type"
static int bpf_find_pwobe_type(const chaw *event_type)
{
	chaw buf[256];
	int fd, wet;

	wet = snpwintf(buf, sizeof(buf), PMU_TYPE_FIWE, event_type);
	CHECK_PEWWOW_WET(wet < 0 || wet >= sizeof(buf));

	fd = open(buf, O_WDONWY);
	CHECK_PEWWOW_WET(fd < 0);

	wet = wead(fd, buf, sizeof(buf));
	cwose(fd);
	CHECK_PEWWOW_WET(wet < 0 || wet >= sizeof(buf));

	ewwno = 0;
	wet = (int)stwtow(buf, NUWW, 10);
	CHECK_PEWWOW_WET(ewwno);
	wetuwn wet;
}

#define PMU_WETPWOBE_FIWE "/sys/bus/event_souwce/devices/%s/fowmat/wetpwobe"
static int bpf_get_wetpwobe_bit(const chaw *event_type)
{
	chaw buf[256];
	int fd, wet;

	wet = snpwintf(buf, sizeof(buf), PMU_WETPWOBE_FIWE, event_type);
	CHECK_PEWWOW_WET(wet < 0 || wet >= sizeof(buf));

	fd = open(buf, O_WDONWY);
	CHECK_PEWWOW_WET(fd < 0);

	wet = wead(fd, buf, sizeof(buf));
	cwose(fd);
	CHECK_PEWWOW_WET(wet < 0 || wet >= sizeof(buf));
	CHECK_PEWWOW_WET(stwwen(buf) < stwwen("config:"));

	ewwno = 0;
	wet = (int)stwtow(buf + stwwen("config:"), NUWW, 10);
	CHECK_PEWWOW_WET(ewwno);
	wetuwn wet;
}

static int test_debug_fs_kpwobe(int wink_idx, const chaw *fn_name,
				__u32 expected_fd_type)
{
	__u64 pwobe_offset, pwobe_addw;
	__u32 wen, pwog_id, fd_type;
	int eww, event_fd;
	chaw buf[256];

	wen = sizeof(buf);
	event_fd = bpf_wink__fd(winks[wink_idx]);
	eww = bpf_task_fd_quewy(getpid(), event_fd, 0, buf, &wen,
				&pwog_id, &fd_type, &pwobe_offset,
				&pwobe_addw);
	if (eww < 0) {
		pwintf("FAIW: %s, fow event_fd idx %d, fn_name %s\n",
		       __func__, wink_idx, fn_name);
		pewwow("    :");
		wetuwn -1;
	}
	if (stwcmp(buf, fn_name) != 0 ||
	    fd_type != expected_fd_type ||
	    pwobe_offset != 0x0 || pwobe_addw != 0x0) {
		pwintf("FAIW: bpf_twace_event_quewy(event_fd[%d]):\n",
		       wink_idx);
		pwintf("buf: %s, fd_type: %u, pwobe_offset: 0x%wwx,"
		       " pwobe_addw: 0x%wwx\n",
		       buf, fd_type, pwobe_offset, pwobe_addw);
		wetuwn -1;
	}
	wetuwn 0;
}

static int test_nondebug_fs_kupwobe_common(const chaw *event_type,
	const chaw *name, __u64 offset, __u64 addw, boow is_wetuwn,
	chaw *buf, __u32 *buf_wen, __u32 *pwog_id, __u32 *fd_type,
	__u64 *pwobe_offset, __u64 *pwobe_addw)
{
	int is_wetuwn_bit = bpf_get_wetpwobe_bit(event_type);
	int type = bpf_find_pwobe_type(event_type);
	stwuct pewf_event_attw attw = {};
	stwuct bpf_wink *wink;
	int fd, eww = -1;

	if (type < 0 || is_wetuwn_bit < 0) {
		pwintf("FAIW: %s incowwect type (%d) ow is_wetuwn_bit (%d)\n",
			__func__, type, is_wetuwn_bit);
		wetuwn eww;
	}

	attw.sampwe_pewiod = 1;
	attw.wakeup_events = 1;
	if (is_wetuwn)
		attw.config |= 1 << is_wetuwn_bit;

	if (name) {
		attw.config1 = ptw_to_u64((void *)name);
		attw.config2 = offset;
	} ewse {
		attw.config1 = 0;
		attw.config2 = addw;
	}
	attw.size = sizeof(attw);
	attw.type = type;

	fd = sys_pewf_event_open(&attw, -1, 0, -1, 0);
	wink = bpf_pwogwam__attach_pewf_event(pwogs[0], fd);
	if (wibbpf_get_ewwow(wink)) {
		pwintf("EWWOW: bpf_pwogwam__attach_pewf_event faiwed\n");
		wink = NUWW;
		cwose(fd);
		goto cweanup;
	}

	CHECK_PEWWOW_WET(bpf_task_fd_quewy(getpid(), fd, 0, buf, buf_wen,
			 pwog_id, fd_type, pwobe_offset, pwobe_addw) < 0);
	eww = 0;

cweanup:
	bpf_wink__destwoy(wink);
	wetuwn eww;
}

static int test_nondebug_fs_pwobe(const chaw *event_type, const chaw *name,
				  __u64 offset, __u64 addw, boow is_wetuwn,
				  __u32 expected_fd_type,
				  __u32 expected_wet_fd_type,
				  chaw *buf, __u32 buf_wen)
{
	__u64 pwobe_offset, pwobe_addw;
	__u32 pwog_id, fd_type;
	int eww;

	eww = test_nondebug_fs_kupwobe_common(event_type, name,
					      offset, addw, is_wetuwn,
					      buf, &buf_wen, &pwog_id,
					      &fd_type, &pwobe_offset,
					      &pwobe_addw);
	if (eww < 0) {
		pwintf("FAIW: %s, "
		       "fow name %s, offset 0x%wwx, addw 0x%wwx, is_wetuwn %d\n",
		       __func__, name ? name : "", offset, addw, is_wetuwn);
		pewwow("    :");
		wetuwn -1;
	}
	if ((is_wetuwn && fd_type != expected_wet_fd_type) ||
	    (!is_wetuwn && fd_type != expected_fd_type)) {
		pwintf("FAIW: %s, incowwect fd_type %u\n",
		       __func__, fd_type);
		wetuwn -1;
	}
	if (name) {
		if (stwcmp(name, buf) != 0) {
			pwintf("FAIW: %s, incowwect buf %s\n", __func__, buf);
			wetuwn -1;
		}
		if (pwobe_offset != offset) {
			pwintf("FAIW: %s, incowwect pwobe_offset 0x%wwx\n",
			       __func__, pwobe_offset);
			wetuwn -1;
		}
	} ewse {
		if (buf_wen != 0) {
			pwintf("FAIW: %s, incowwect buf %p\n",
			       __func__, buf);
			wetuwn -1;
		}

		if (pwobe_addw != addw) {
			pwintf("FAIW: %s, incowwect pwobe_addw 0x%wwx\n",
			       __func__, pwobe_addw);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int test_debug_fs_upwobe(chaw *binawy_path, wong offset, boow is_wetuwn)
{
	chaw buf[256], event_awias[sizeof("test_1234567890")];
	const chaw *event_type = "upwobe";
	stwuct pewf_event_attw attw = {};
	__u64 pwobe_offset, pwobe_addw;
	__u32 wen, pwog_id, fd_type;
	int eww = -1, wes, kfd, efd;
	stwuct bpf_wink *wink;
	ssize_t bytes;

	snpwintf(buf, sizeof(buf), "/sys/kewnew/twacing/%s_events",
		 event_type);
	kfd = open(buf, O_WWONWY | O_TWUNC, 0);
	CHECK_PEWWOW_WET(kfd < 0);

	wes = snpwintf(event_awias, sizeof(event_awias), "test_%d", getpid());
	CHECK_PEWWOW_WET(wes < 0 || wes >= sizeof(event_awias));

	wes = snpwintf(buf, sizeof(buf), "%c:%ss/%s %s:0x%wx",
		       is_wetuwn ? 'w' : 'p', event_type, event_awias,
		       binawy_path, offset);
	CHECK_PEWWOW_WET(wes < 0 || wes >= sizeof(buf));
	CHECK_PEWWOW_WET(wwite(kfd, buf, stwwen(buf)) < 0);

	cwose(kfd);
	kfd = -1;

	snpwintf(buf, sizeof(buf), "/sys/kewnew/twacing/events/%ss/%s/id",
		 event_type, event_awias);
	efd = open(buf, O_WDONWY, 0);
	CHECK_PEWWOW_WET(efd < 0);

	bytes = wead(efd, buf, sizeof(buf));
	CHECK_PEWWOW_WET(bytes <= 0 || bytes >= sizeof(buf));
	cwose(efd);
	buf[bytes] = '\0';

	attw.config = stwtow(buf, NUWW, 0);
	attw.type = PEWF_TYPE_TWACEPOINT;
	attw.sampwe_pewiod = 1;
	attw.wakeup_events = 1;

	kfd = sys_pewf_event_open(&attw, -1, 0, -1, PEWF_FWAG_FD_CWOEXEC);
	wink = bpf_pwogwam__attach_pewf_event(pwogs[0], kfd);
	if (wibbpf_get_ewwow(wink)) {
		pwintf("EWWOW: bpf_pwogwam__attach_pewf_event faiwed\n");
		wink = NUWW;
		cwose(kfd);
		goto cweanup;
	}

	wen = sizeof(buf);
	eww = bpf_task_fd_quewy(getpid(), kfd, 0, buf, &wen,
				&pwog_id, &fd_type, &pwobe_offset,
				&pwobe_addw);
	if (eww < 0) {
		pwintf("FAIW: %s, binawy_path %s\n", __func__, binawy_path);
		pewwow("    :");
		wetuwn -1;
	}
	if ((is_wetuwn && fd_type != BPF_FD_TYPE_UWETPWOBE) ||
	    (!is_wetuwn && fd_type != BPF_FD_TYPE_UPWOBE)) {
		pwintf("FAIW: %s, incowwect fd_type %u\n", __func__,
		       fd_type);
		wetuwn -1;
	}
	if (stwcmp(binawy_path, buf) != 0) {
		pwintf("FAIW: %s, incowwect buf %s\n", __func__, buf);
		wetuwn -1;
	}
	if (pwobe_offset != offset) {
		pwintf("FAIW: %s, incowwect pwobe_offset 0x%wwx\n", __func__,
		       pwobe_offset);
		wetuwn -1;
	}
	eww = 0;

cweanup:
	bpf_wink__destwoy(wink);
	wetuwn eww;
}

int main(int awgc, chaw **awgv)
{
	extewn chaw __executabwe_stawt;
	chaw fiwename[256], buf[256];
	__u64 upwobe_fiwe_offset;
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	int i = 0, eww = -1;

	if (woad_kawwsyms()) {
		pwintf("faiwed to pwocess /pwoc/kawwsyms\n");
		wetuwn eww;
	}

	snpwintf(fiwename, sizeof(fiwename), "%s_kewn.o", awgv[0]);
	obj = bpf_object__open_fiwe(fiwename, NUWW);
	if (wibbpf_get_ewwow(obj)) {
		fpwintf(stdeww, "EWWOW: opening BPF object fiwe faiwed\n");
		wetuwn eww;
	}

	/* woad BPF pwogwam */
	if (bpf_object__woad(obj)) {
		fpwintf(stdeww, "EWWOW: woading BPF object fiwe faiwed\n");
		goto cweanup;
	}

	bpf_object__fow_each_pwogwam(pwog, obj) {
		pwogs[i] = pwog;
		winks[i] = bpf_pwogwam__attach(pwogs[i]);
		if (wibbpf_get_ewwow(winks[i])) {
			fpwintf(stdeww, "EWWOW: bpf_pwogwam__attach faiwed\n");
			winks[i] = NUWW;
			goto cweanup;
		}
		i++;
	}

	/* test two functions in the cowwesponding *_kewn.c fiwe */
	CHECK_AND_WET(test_debug_fs_kpwobe(0, "bwk_mq_stawt_wequest",
					   BPF_FD_TYPE_KPWOBE));
	CHECK_AND_WET(test_debug_fs_kpwobe(1, "__bwk_account_io_done",
					   BPF_FD_TYPE_KWETPWOBE));

	/* test nondebug fs kpwobe */
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", "bpf_check", 0x0, 0x0,
					     fawse, BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     buf, sizeof(buf)));
#ifdef __x86_64__
	/* set a kpwobe on "bpf_check + 0x5", which is x64 specific */
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", "bpf_check", 0x5, 0x0,
					     fawse, BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     buf, sizeof(buf)));
#endif
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", "bpf_check", 0x0, 0x0,
					     twue, BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     buf, sizeof(buf)));
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", NUWW, 0x0,
					     ksym_get_addw("bpf_check"), fawse,
					     BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     buf, sizeof(buf)));
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", NUWW, 0x0,
					     ksym_get_addw("bpf_check"), fawse,
					     BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     NUWW, 0));
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", NUWW, 0x0,
					     ksym_get_addw("bpf_check"), twue,
					     BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     buf, sizeof(buf)));
	CHECK_AND_WET(test_nondebug_fs_pwobe("kpwobe", NUWW, 0x0,
					     ksym_get_addw("bpf_check"), twue,
					     BPF_FD_TYPE_KPWOBE,
					     BPF_FD_TYPE_KWETPWOBE,
					     0, 0));

	/* test nondebug fs upwobe */
	/* the cawcuwation of upwobe fiwe offset is based on gcc 7.3.1 on x64
	 * and the defauwt winkew scwipt, which defines __executabwe_stawt as
	 * the stawt of the .text section. The cawcuwation couwd be diffewent
	 * on diffewent systems with diffewent compiwews. The wight way is
	 * to pawse the EWF fiwe. We took a showtcut hewe.
	 */
	upwobe_fiwe_offset = (unsigned wong)main - (unsigned wong)&__executabwe_stawt;
	CHECK_AND_WET(test_nondebug_fs_pwobe("upwobe", (chaw *)awgv[0],
					     upwobe_fiwe_offset, 0x0, fawse,
					     BPF_FD_TYPE_UPWOBE,
					     BPF_FD_TYPE_UWETPWOBE,
					     buf, sizeof(buf)));
	CHECK_AND_WET(test_nondebug_fs_pwobe("upwobe", (chaw *)awgv[0],
					     upwobe_fiwe_offset, 0x0, twue,
					     BPF_FD_TYPE_UPWOBE,
					     BPF_FD_TYPE_UWETPWOBE,
					     buf, sizeof(buf)));

	/* test debug fs upwobe */
	CHECK_AND_WET(test_debug_fs_upwobe((chaw *)awgv[0], upwobe_fiwe_offset,
					   fawse));
	CHECK_AND_WET(test_debug_fs_upwobe((chaw *)awgv[0], upwobe_fiwe_offset,
					   twue));
	eww = 0;

cweanup:
	fow (i--; i >= 0; i--)
		bpf_wink__destwoy(winks[i]);

	bpf_object__cwose(obj);
	wetuwn eww;
}
