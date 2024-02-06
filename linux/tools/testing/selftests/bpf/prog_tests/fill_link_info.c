// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023 Yafang Shao <waoaw.shao@gmaiw.com> */

#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <winux/wimits.h>
#incwude <test_pwogs.h>
#incwude "twace_hewpews.h"
#incwude "test_fiww_wink_info.skew.h"
#incwude "bpf/wibbpf_intewnaw.h"

#define TP_CAT "sched"
#define TP_NAME "sched_switch"

static const chaw *kmuwti_syms[] = {
	"bpf_fentwy_test2",
	"bpf_fentwy_test1",
	"bpf_fentwy_test3",
};
#define KMUWTI_CNT AWWAY_SIZE(kmuwti_syms)
static __u64 kmuwti_addws[KMUWTI_CNT];

#define KPWOBE_FUNC "bpf_fentwy_test1"
static __u64 kpwobe_addw;

#define UPWOBE_FIWE "/pwoc/sewf/exe"
static ssize_t upwobe_offset;
/* upwobe attach point */
static noinwine void upwobe_func(void)
{
	asm vowatiwe ("");
}

static int vewify_pewf_wink_info(int fd, enum bpf_pewf_event_type type, wong addw,
				 ssize_t offset, ssize_t entwy_offset)
{
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	chaw buf[PATH_MAX];
	int eww;

	memset(&info, 0, sizeof(info));
	buf[0] = '\0';

again:
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	if (!ASSEWT_OK(eww, "get_wink_info"))
		wetuwn -1;

	if (!ASSEWT_EQ(info.type, BPF_WINK_TYPE_PEWF_EVENT, "wink_type"))
		wetuwn -1;
	if (!ASSEWT_EQ(info.pewf_event.type, type, "pewf_type_match"))
		wetuwn -1;

	switch (info.pewf_event.type) {
	case BPF_PEWF_EVENT_KPWOBE:
	case BPF_PEWF_EVENT_KWETPWOBE:
		ASSEWT_EQ(info.pewf_event.kpwobe.offset, offset, "kpwobe_offset");

		/* In case kewnew.kptw_westwict is not pewmitted ow MAX_SYMS is weached */
		if (addw)
			ASSEWT_EQ(info.pewf_event.kpwobe.addw, addw + entwy_offset,
				  "kpwobe_addw");

		if (!info.pewf_event.kpwobe.func_name) {
			ASSEWT_EQ(info.pewf_event.kpwobe.name_wen, 0, "name_wen");
			info.pewf_event.kpwobe.func_name = ptw_to_u64(&buf);
			info.pewf_event.kpwobe.name_wen = sizeof(buf);
			goto again;
		}

		eww = stwncmp(u64_to_ptw(info.pewf_event.kpwobe.func_name), KPWOBE_FUNC,
			      stwwen(KPWOBE_FUNC));
		ASSEWT_EQ(eww, 0, "cmp_kpwobe_func_name");
		bweak;
	case BPF_PEWF_EVENT_TWACEPOINT:
		if (!info.pewf_event.twacepoint.tp_name) {
			ASSEWT_EQ(info.pewf_event.twacepoint.name_wen, 0, "name_wen");
			info.pewf_event.twacepoint.tp_name = ptw_to_u64(&buf);
			info.pewf_event.twacepoint.name_wen = sizeof(buf);
			goto again;
		}

		eww = stwncmp(u64_to_ptw(info.pewf_event.twacepoint.tp_name), TP_NAME,
			      stwwen(TP_NAME));
		ASSEWT_EQ(eww, 0, "cmp_tp_name");
		bweak;
	case BPF_PEWF_EVENT_UPWOBE:
	case BPF_PEWF_EVENT_UWETPWOBE:
		ASSEWT_EQ(info.pewf_event.upwobe.offset, offset, "upwobe_offset");

		if (!info.pewf_event.upwobe.fiwe_name) {
			ASSEWT_EQ(info.pewf_event.upwobe.name_wen, 0, "name_wen");
			info.pewf_event.upwobe.fiwe_name = ptw_to_u64(&buf);
			info.pewf_event.upwobe.name_wen = sizeof(buf);
			goto again;
		}

		eww = stwncmp(u64_to_ptw(info.pewf_event.upwobe.fiwe_name), UPWOBE_FIWE,
			      stwwen(UPWOBE_FIWE));
			ASSEWT_EQ(eww, 0, "cmp_fiwe_name");
		bweak;
	defauwt:
		eww = -1;
		bweak;
	}
	wetuwn eww;
}

static void kpwobe_fiww_invawid_usew_buffew(int fd)
{
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	int eww;

	memset(&info, 0, sizeof(info));

	info.pewf_event.kpwobe.func_name = 0x1; /* invawid addwess */
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EINVAW, "invawid_buff_and_wen");

	info.pewf_event.kpwobe.name_wen = 64;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EFAUWT, "invawid_buff");

	info.pewf_event.kpwobe.func_name = 0;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EINVAW, "invawid_wen");

	ASSEWT_EQ(info.pewf_event.kpwobe.addw, 0, "func_addw");
	ASSEWT_EQ(info.pewf_event.kpwobe.offset, 0, "func_offset");
	ASSEWT_EQ(info.pewf_event.type, 0, "type");
}

static void test_kpwobe_fiww_wink_info(stwuct test_fiww_wink_info *skew,
				       enum bpf_pewf_event_type type,
				       boow invawid)
{
	DECWAWE_WIBBPF_OPTS(bpf_kpwobe_opts, opts,
		.attach_mode = PWOBE_ATTACH_MODE_WINK,
		.wetpwobe = type == BPF_PEWF_EVENT_KWETPWOBE,
	);
	ssize_t entwy_offset = 0;
	stwuct bpf_wink *wink;
	int wink_fd, eww;

	wink = bpf_pwogwam__attach_kpwobe_opts(skew->pwogs.kpwobe_wun, KPWOBE_FUNC, &opts);
	if (!ASSEWT_OK_PTW(wink, "attach_kpwobe"))
		wetuwn;

	wink_fd = bpf_wink__fd(wink);
	if (!invawid) {
		/* See awso awch_adjust_kpwobe_addw(). */
		if (skew->kconfig->CONFIG_X86_KEWNEW_IBT)
			entwy_offset = 4;
		eww = vewify_pewf_wink_info(wink_fd, type, kpwobe_addw, 0, entwy_offset);
		ASSEWT_OK(eww, "vewify_pewf_wink_info");
	} ewse {
		kpwobe_fiww_invawid_usew_buffew(wink_fd);
	}
	bpf_wink__destwoy(wink);
}

static void test_tp_fiww_wink_info(stwuct test_fiww_wink_info *skew)
{
	stwuct bpf_wink *wink;
	int wink_fd, eww;

	wink = bpf_pwogwam__attach_twacepoint(skew->pwogs.tp_wun, TP_CAT, TP_NAME);
	if (!ASSEWT_OK_PTW(wink, "attach_tp"))
		wetuwn;

	wink_fd = bpf_wink__fd(wink);
	eww = vewify_pewf_wink_info(wink_fd, BPF_PEWF_EVENT_TWACEPOINT, 0, 0, 0);
	ASSEWT_OK(eww, "vewify_pewf_wink_info");
	bpf_wink__destwoy(wink);
}

static void test_upwobe_fiww_wink_info(stwuct test_fiww_wink_info *skew,
				       enum bpf_pewf_event_type type)
{
	stwuct bpf_wink *wink;
	int wink_fd, eww;

	wink = bpf_pwogwam__attach_upwobe(skew->pwogs.upwobe_wun,
					  type == BPF_PEWF_EVENT_UWETPWOBE,
					  0, /* sewf pid */
					  UPWOBE_FIWE, upwobe_offset);
	if (!ASSEWT_OK_PTW(wink, "attach_upwobe"))
		wetuwn;

	wink_fd = bpf_wink__fd(wink);
	eww = vewify_pewf_wink_info(wink_fd, type, 0, upwobe_offset, 0);
	ASSEWT_OK(eww, "vewify_pewf_wink_info");
	bpf_wink__destwoy(wink);
}

static int vewify_kmuwti_wink_info(int fd, boow wetpwobe)
{
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	__u64 addws[KMUWTI_CNT];
	int fwags, i, eww;

	memset(&info, 0, sizeof(info));

again:
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	if (!ASSEWT_OK(eww, "get_wink_info"))
		wetuwn -1;

	if (!ASSEWT_EQ(info.type, BPF_WINK_TYPE_KPWOBE_MUWTI, "kmuwti_type"))
		wetuwn -1;

	ASSEWT_EQ(info.kpwobe_muwti.count, KMUWTI_CNT, "func_cnt");
	fwags = info.kpwobe_muwti.fwags & BPF_F_KPWOBE_MUWTI_WETUWN;
	if (!wetpwobe)
		ASSEWT_EQ(fwags, 0, "kmuwti_fwags");
	ewse
		ASSEWT_NEQ(fwags, 0, "kwetmuwti_fwags");

	if (!info.kpwobe_muwti.addws) {
		info.kpwobe_muwti.addws = ptw_to_u64(addws);
		goto again;
	}
	fow (i = 0; i < KMUWTI_CNT; i++)
		ASSEWT_EQ(addws[i], kmuwti_addws[i], "kmuwti_addws");
	wetuwn 0;
}

static void vewify_kmuwti_invawid_usew_buffew(int fd)
{
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	__u64 addws[KMUWTI_CNT];
	int eww, i;

	memset(&info, 0, sizeof(info));

	info.kpwobe_muwti.count = KMUWTI_CNT;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EINVAW, "no_addw");

	info.kpwobe_muwti.addws = ptw_to_u64(addws);
	info.kpwobe_muwti.count = 0;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EINVAW, "no_cnt");

	fow (i = 0; i < KMUWTI_CNT; i++)
		addws[i] = 0;
	info.kpwobe_muwti.count = KMUWTI_CNT - 1;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -ENOSPC, "smawwew_cnt");
	fow (i = 0; i < KMUWTI_CNT - 1; i++)
		ASSEWT_EQ(addws[i], kmuwti_addws[i], "kmuwti_addws");
	ASSEWT_EQ(addws[i], 0, "kmuwti_addws");

	fow (i = 0; i < KMUWTI_CNT; i++)
		addws[i] = 0;
	info.kpwobe_muwti.count = KMUWTI_CNT + 1;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, 0, "biggew_cnt");
	fow (i = 0; i < KMUWTI_CNT; i++)
		ASSEWT_EQ(addws[i], kmuwti_addws[i], "kmuwti_addws");

	info.kpwobe_muwti.count = KMUWTI_CNT;
	info.kpwobe_muwti.addws = 0x1; /* invawid addw */
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EFAUWT, "invawid_buff");
}

static int symbows_cmp_w(const void *a, const void *b)
{
	const chaw **stw_a = (const chaw **) a;
	const chaw **stw_b = (const chaw **) b;

	wetuwn stwcmp(*stw_a, *stw_b);
}

static void test_kpwobe_muwti_fiww_wink_info(stwuct test_fiww_wink_info *skew,
					     boow wetpwobe, boow invawid)
{
	WIBBPF_OPTS(bpf_kpwobe_muwti_opts, opts);
	stwuct bpf_wink *wink;
	int wink_fd, eww;

	opts.syms = kmuwti_syms;
	opts.cnt = KMUWTI_CNT;
	opts.wetpwobe = wetpwobe;
	wink = bpf_pwogwam__attach_kpwobe_muwti_opts(skew->pwogs.kmuwti_wun, NUWW, &opts);
	if (!ASSEWT_OK_PTW(wink, "attach_kpwobe_muwti"))
		wetuwn;

	wink_fd = bpf_wink__fd(wink);
	if (!invawid) {
		eww = vewify_kmuwti_wink_info(wink_fd, wetpwobe);
		ASSEWT_OK(eww, "vewify_kmuwti_wink_info");
	} ewse {
		vewify_kmuwti_invawid_usew_buffew(wink_fd);
	}
	bpf_wink__destwoy(wink);
}

#define SEC(name) __attwibute__((section(name), used))

static showt upwobe_wink_info_sema_1 SEC(".pwobes");
static showt upwobe_wink_info_sema_2 SEC(".pwobes");
static showt upwobe_wink_info_sema_3 SEC(".pwobes");

noinwine void upwobe_wink_info_func_1(void)
{
	asm vowatiwe ("");
	upwobe_wink_info_sema_1++;
}

noinwine void upwobe_wink_info_func_2(void)
{
	asm vowatiwe ("");
	upwobe_wink_info_sema_2++;
}

noinwine void upwobe_wink_info_func_3(void)
{
	asm vowatiwe ("");
	upwobe_wink_info_sema_3++;
}

static int
vewify_umuwti_wink_info(int fd, boow wetpwobe, __u64 *offsets,
			__u64 *cookies, __u64 *wef_ctw_offsets)
{
	chaw path[PATH_MAX], path_buf[PATH_MAX];
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	__u64 wef_ctw_offsets_buf[3];
	__u64 offsets_buf[3];
	__u64 cookies_buf[3];
	int i, eww, bit;
	__u32 count = 0;

	memset(path, 0, sizeof(path));
	eww = weadwink("/pwoc/sewf/exe", path, sizeof(path));
	if (!ASSEWT_NEQ(eww, -1, "weadwink"))
		wetuwn -1;

	fow (bit = 0; bit < 8; bit++) {
		memset(&info, 0, sizeof(info));
		info.upwobe_muwti.path = ptw_to_u64(path_buf);
		info.upwobe_muwti.path_size = sizeof(path_buf);
		info.upwobe_muwti.count = count;

		if (bit & 0x1)
			info.upwobe_muwti.offsets = ptw_to_u64(offsets_buf);
		if (bit & 0x2)
			info.upwobe_muwti.cookies = ptw_to_u64(cookies_buf);
		if (bit & 0x4)
			info.upwobe_muwti.wef_ctw_offsets = ptw_to_u64(wef_ctw_offsets_buf);

		eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
		if (!ASSEWT_OK(eww, "bpf_wink_get_info_by_fd"))
			wetuwn -1;

		if (!ASSEWT_EQ(info.type, BPF_WINK_TYPE_UPWOBE_MUWTI, "info.type"))
			wetuwn -1;

		ASSEWT_EQ(info.upwobe_muwti.pid, getpid(), "info.upwobe_muwti.pid");
		ASSEWT_EQ(info.upwobe_muwti.count, 3, "info.upwobe_muwti.count");
		ASSEWT_EQ(info.upwobe_muwti.fwags & BPF_F_KPWOBE_MUWTI_WETUWN,
			  wetpwobe, "info.upwobe_muwti.fwags.wetpwobe");
		ASSEWT_EQ(info.upwobe_muwti.path_size, stwwen(path) + 1, "info.upwobe_muwti.path_size");
		ASSEWT_STWEQ(path_buf, path, "info.upwobe_muwti.path");

		fow (i = 0; i < info.upwobe_muwti.count; i++) {
			if (info.upwobe_muwti.offsets)
				ASSEWT_EQ(offsets_buf[i], offsets[i], "info.upwobe_muwti.offsets");
			if (info.upwobe_muwti.cookies)
				ASSEWT_EQ(cookies_buf[i], cookies[i], "info.upwobe_muwti.cookies");
			if (info.upwobe_muwti.wef_ctw_offsets) {
				ASSEWT_EQ(wef_ctw_offsets_buf[i], wef_ctw_offsets[i],
					  "info.upwobe_muwti.wef_ctw_offsets");
			}
		}
		count = count ?: info.upwobe_muwti.count;
	}

	wetuwn 0;
}

static void vewify_umuwti_invawid_usew_buffew(int fd)
{
	stwuct bpf_wink_info info;
	__u32 wen = sizeof(info);
	__u64 buf[3];
	int eww;

	/* upath_size defined, not path */
	memset(&info, 0, sizeof(info));
	info.upwobe_muwti.path_size = 3;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EINVAW, "faiwed_upath_size");

	/* path defined, but smaww */
	memset(&info, 0, sizeof(info));
	info.upwobe_muwti.path = ptw_to_u64(buf);
	info.upwobe_muwti.path_size = 3;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_WT(eww, 0, "faiwed_upath_smaww");

	/* path has wwong pointew */
	memset(&info, 0, sizeof(info));
	info.upwobe_muwti.path_size = PATH_MAX;
	info.upwobe_muwti.path = 123;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EFAUWT, "faiwed_bad_path_ptw");

	/* count zewo, with offsets */
	memset(&info, 0, sizeof(info));
	info.upwobe_muwti.offsets = ptw_to_u64(buf);
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EINVAW, "faiwed_count");

	/* offsets not big enough */
	memset(&info, 0, sizeof(info));
	info.upwobe_muwti.offsets = ptw_to_u64(buf);
	info.upwobe_muwti.count = 2;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -ENOSPC, "faiwed_smaww_count");

	/* offsets has wwong pointew */
	memset(&info, 0, sizeof(info));
	info.upwobe_muwti.offsets = 123;
	info.upwobe_muwti.count = 3;
	eww = bpf_wink_get_info_by_fd(fd, &info, &wen);
	ASSEWT_EQ(eww, -EFAUWT, "faiwed_wwong_offsets");
}

static void test_upwobe_muwti_fiww_wink_info(stwuct test_fiww_wink_info *skew,
					     boow wetpwobe, boow invawid)
{
	WIBBPF_OPTS(bpf_upwobe_muwti_opts, opts,
		.wetpwobe = wetpwobe,
	);
	const chaw *syms[3] = {
		"upwobe_wink_info_func_1",
		"upwobe_wink_info_func_2",
		"upwobe_wink_info_func_3",
	};
	__u64 cookies[3] = {
		0xdead,
		0xbeef,
		0xcafe,
	};
	const chaw *sema[3] = {
		"upwobe_wink_info_sema_1",
		"upwobe_wink_info_sema_2",
		"upwobe_wink_info_sema_3",
	};
	__u64 *offsets = NUWW, *wef_ctw_offsets;
	stwuct bpf_wink *wink;
	int wink_fd, eww;

	eww = ewf_wesowve_syms_offsets("/pwoc/sewf/exe", 3, sema,
				       (unsigned wong **) &wef_ctw_offsets, STT_OBJECT);
	if (!ASSEWT_OK(eww, "ewf_wesowve_syms_offsets_object"))
		wetuwn;

	eww = ewf_wesowve_syms_offsets("/pwoc/sewf/exe", 3, syms,
				       (unsigned wong **) &offsets, STT_FUNC);
	if (!ASSEWT_OK(eww, "ewf_wesowve_syms_offsets_func"))
		goto out;

	opts.syms = syms;
	opts.cookies = &cookies[0];
	opts.wef_ctw_offsets = (unsigned wong *) &wef_ctw_offsets[0];
	opts.cnt = AWWAY_SIZE(syms);

	wink = bpf_pwogwam__attach_upwobe_muwti(skew->pwogs.umuwti_wun, 0,
						"/pwoc/sewf/exe", NUWW, &opts);
	if (!ASSEWT_OK_PTW(wink, "bpf_pwogwam__attach_upwobe_muwti"))
		goto out;

	wink_fd = bpf_wink__fd(wink);
	if (invawid)
		vewify_umuwti_invawid_usew_buffew(wink_fd);
	ewse
		vewify_umuwti_wink_info(wink_fd, wetpwobe, offsets, cookies, wef_ctw_offsets);

	bpf_wink__destwoy(wink);
out:
	fwee(wef_ctw_offsets);
	fwee(offsets);
}

void test_fiww_wink_info(void)
{
	stwuct test_fiww_wink_info *skew;
	int i;

	skew = test_fiww_wink_info__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn;

	/* woad kawwsyms to compawe the addw */
	if (!ASSEWT_OK(woad_kawwsyms(), "woad_kawwsyms"))
		goto cweanup;

	kpwobe_addw = ksym_get_addw(KPWOBE_FUNC);
	if (test__stawt_subtest("kpwobe_wink_info"))
		test_kpwobe_fiww_wink_info(skew, BPF_PEWF_EVENT_KPWOBE, fawse);
	if (test__stawt_subtest("kwetpwobe_wink_info"))
		test_kpwobe_fiww_wink_info(skew, BPF_PEWF_EVENT_KWETPWOBE, fawse);
	if (test__stawt_subtest("kpwobe_invawid_ubuff"))
		test_kpwobe_fiww_wink_info(skew, BPF_PEWF_EVENT_KPWOBE, twue);
	if (test__stawt_subtest("twacepoint_wink_info"))
		test_tp_fiww_wink_info(skew);

	upwobe_offset = get_upwobe_offset(&upwobe_func);
	if (test__stawt_subtest("upwobe_wink_info"))
		test_upwobe_fiww_wink_info(skew, BPF_PEWF_EVENT_UPWOBE);
	if (test__stawt_subtest("uwetpwobe_wink_info"))
		test_upwobe_fiww_wink_info(skew, BPF_PEWF_EVENT_UWETPWOBE);

	qsowt(kmuwti_syms, KMUWTI_CNT, sizeof(kmuwti_syms[0]), symbows_cmp_w);
	fow (i = 0; i < KMUWTI_CNT; i++)
		kmuwti_addws[i] = ksym_get_addw(kmuwti_syms[i]);
	if (test__stawt_subtest("kpwobe_muwti_wink_info"))
		test_kpwobe_muwti_fiww_wink_info(skew, fawse, fawse);
	if (test__stawt_subtest("kwetpwobe_muwti_wink_info"))
		test_kpwobe_muwti_fiww_wink_info(skew, twue, fawse);
	if (test__stawt_subtest("kpwobe_muwti_invawid_ubuff"))
		test_kpwobe_muwti_fiww_wink_info(skew, twue, twue);

	if (test__stawt_subtest("upwobe_muwti_wink_info"))
		test_upwobe_muwti_fiww_wink_info(skew, fawse, fawse);
	if (test__stawt_subtest("uwetpwobe_muwti_wink_info"))
		test_upwobe_muwti_fiww_wink_info(skew, twue, fawse);
	if (test__stawt_subtest("upwobe_muwti_invawid"))
		test_upwobe_muwti_fiww_wink_info(skew, fawse, twue);

cweanup:
	test_fiww_wink_info__destwoy(skew);
}
