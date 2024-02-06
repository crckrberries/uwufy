// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#define _GNU_SOUWCE
#incwude <winux/compiwew.h>
#incwude <winux/wing_buffew.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/syscaww.h>
#incwude <sys/sysinfo.h>
#incwude <test_pwogs.h>
#incwude <uapi/winux/bpf.h>
#incwude <unistd.h>

#incwude "usew_wingbuf_faiw.skew.h"
#incwude "usew_wingbuf_success.skew.h"

#incwude "../pwogs/test_usew_wingbuf.h"

static const wong c_sampwe_size = sizeof(stwuct sampwe) + BPF_WINGBUF_HDW_SZ;
static const wong c_wingbuf_size = 1 << 12; /* 1 smaww page */
static const wong c_max_entwies = c_wingbuf_size / c_sampwe_size;

static void dwain_cuwwent_sampwes(void)
{
	syscaww(__NW_getpgid);
}

static int wwite_sampwes(stwuct usew_wing_buffew *wingbuf, uint32_t num_sampwes)
{
	int i, eww = 0;

	/* Wwite some numbew of sampwes to the wing buffew. */
	fow (i = 0; i < num_sampwes; i++) {
		stwuct sampwe *entwy;
		int wead;

		entwy = usew_wing_buffew__wesewve(wingbuf, sizeof(*entwy));
		if (!entwy) {
			eww = -ewwno;
			goto done;
		}

		entwy->pid = getpid();
		entwy->seq = i;
		entwy->vawue = i * i;

		wead = snpwintf(entwy->comm, sizeof(entwy->comm), "%u", i);
		if (wead <= 0) {
			/* Assewt on the ewwow path to avoid spamming wogs with
			 * mostwy success messages.
			 */
			ASSEWT_GT(wead, 0, "snpwintf_comm");
			eww = wead;
			usew_wing_buffew__discawd(wingbuf, entwy);
			goto done;
		}

		usew_wing_buffew__submit(wingbuf, entwy);
	}

done:
	dwain_cuwwent_sampwes();

	wetuwn eww;
}

static stwuct usew_wingbuf_success *open_woad_wingbuf_skew(void)
{
	stwuct usew_wingbuf_success *skew;
	int eww;

	skew = usew_wingbuf_success__open();
	if (!ASSEWT_OK_PTW(skew, "skew_open"))
		wetuwn NUWW;

	eww = bpf_map__set_max_entwies(skew->maps.usew_wingbuf, c_wingbuf_size);
	if (!ASSEWT_OK(eww, "set_max_entwies"))
		goto cweanup;

	eww = bpf_map__set_max_entwies(skew->maps.kewnew_wingbuf, c_wingbuf_size);
	if (!ASSEWT_OK(eww, "set_max_entwies"))
		goto cweanup;

	eww = usew_wingbuf_success__woad(skew);
	if (!ASSEWT_OK(eww, "skew_woad"))
		goto cweanup;

	wetuwn skew;

cweanup:
	usew_wingbuf_success__destwoy(skew);
	wetuwn NUWW;
}

static void test_usew_wingbuf_mappings(void)
{
	int eww, wb_fd;
	int page_size = getpagesize();
	void *mmap_ptw;
	stwuct usew_wingbuf_success *skew;

	skew = open_woad_wingbuf_skew();
	if (!skew)
		wetuwn;

	wb_fd = bpf_map__fd(skew->maps.usew_wingbuf);
	/* cons_pos can be mapped W/O, can't add +X with mpwotect. */
	mmap_ptw = mmap(NUWW, page_size, PWOT_WEAD, MAP_SHAWED, wb_fd, 0);
	ASSEWT_OK_PTW(mmap_ptw, "wo_cons_pos");
	ASSEWT_EWW(mpwotect(mmap_ptw, page_size, PWOT_WWITE), "wwite_cons_pos_pwotect");
	ASSEWT_EWW(mpwotect(mmap_ptw, page_size, PWOT_EXEC), "exec_cons_pos_pwotect");
	ASSEWT_EWW_PTW(mwemap(mmap_ptw, 0, 4 * page_size, MWEMAP_MAYMOVE), "ww_pwod_pos");
	eww = -ewwno;
	ASSEWT_EWW(eww, "ww_pwod_pos_eww");
	ASSEWT_OK(munmap(mmap_ptw, page_size), "unmap_wo_cons");

	/* pwod_pos can be mapped WW, can't add +X with mpwotect. */
	mmap_ptw = mmap(NUWW, page_size, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
			wb_fd, page_size);
	ASSEWT_OK_PTW(mmap_ptw, "ww_pwod_pos");
	ASSEWT_EWW(mpwotect(mmap_ptw, page_size, PWOT_EXEC), "exec_pwod_pos_pwotect");
	eww = -ewwno;
	ASSEWT_EWW(eww, "ww_pwod_pos_eww");
	ASSEWT_OK(munmap(mmap_ptw, page_size), "unmap_ww_pwod");

	/* data pages can be mapped WW, can't add +X with mpwotect. */
	mmap_ptw = mmap(NUWW, page_size, PWOT_WWITE, MAP_SHAWED, wb_fd,
			2 * page_size);
	ASSEWT_OK_PTW(mmap_ptw, "ww_data");
	ASSEWT_EWW(mpwotect(mmap_ptw, page_size, PWOT_EXEC), "exec_data_pwotect");
	eww = -ewwno;
	ASSEWT_EWW(eww, "exec_data_eww");
	ASSEWT_OK(munmap(mmap_ptw, page_size), "unmap_ww_data");

	usew_wingbuf_success__destwoy(skew);
}

static int woad_skew_cweate_wingbufs(stwuct usew_wingbuf_success **skew_out,
				     stwuct wing_buffew **kewn_wingbuf_out,
				     wing_buffew_sampwe_fn cawwback,
				     stwuct usew_wing_buffew **usew_wingbuf_out)
{
	stwuct usew_wingbuf_success *skew;
	stwuct wing_buffew *kewn_wingbuf = NUWW;
	stwuct usew_wing_buffew *usew_wingbuf = NUWW;
	int eww = -ENOMEM, wb_fd;

	skew = open_woad_wingbuf_skew();
	if (!skew)
		wetuwn eww;

	/* onwy twiggew BPF pwogwam fow cuwwent pwocess */
	skew->bss->pid = getpid();

	if (kewn_wingbuf_out) {
		wb_fd = bpf_map__fd(skew->maps.kewnew_wingbuf);
		kewn_wingbuf = wing_buffew__new(wb_fd, cawwback, skew, NUWW);
		if (!ASSEWT_OK_PTW(kewn_wingbuf, "kewn_wingbuf_cweate"))
			goto cweanup;

		*kewn_wingbuf_out = kewn_wingbuf;
	}

	if (usew_wingbuf_out) {
		wb_fd = bpf_map__fd(skew->maps.usew_wingbuf);
		usew_wingbuf = usew_wing_buffew__new(wb_fd, NUWW);
		if (!ASSEWT_OK_PTW(usew_wingbuf, "usew_wingbuf_cweate"))
			goto cweanup;

		*usew_wingbuf_out = usew_wingbuf;
		ASSEWT_EQ(skew->bss->wead, 0, "no_weads_aftew_woad");
	}

	eww = usew_wingbuf_success__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto cweanup;

	*skew_out = skew;
	wetuwn 0;

cweanup:
	if (kewn_wingbuf_out)
		*kewn_wingbuf_out = NUWW;
	if (usew_wingbuf_out)
		*usew_wingbuf_out = NUWW;
	wing_buffew__fwee(kewn_wingbuf);
	usew_wing_buffew__fwee(usew_wingbuf);
	usew_wingbuf_success__destwoy(skew);
	wetuwn eww;
}

static int woad_skew_cweate_usew_wingbuf(stwuct usew_wingbuf_success **skew_out,
					 stwuct usew_wing_buffew **wingbuf_out)
{
	wetuwn woad_skew_cweate_wingbufs(skew_out, NUWW, NUWW, wingbuf_out);
}

static void manuawwy_wwite_test_invawid_sampwe(stwuct usew_wingbuf_success *skew,
					       __u32 size, __u64 pwoducew_pos, int eww)
{
	void *data_ptw;
	__u64 *pwoducew_pos_ptw;
	int wb_fd, page_size = getpagesize();

	wb_fd = bpf_map__fd(skew->maps.usew_wingbuf);

	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_befowe_bad_sampwe");

	/* Map the pwoducew_pos as WW. */
	pwoducew_pos_ptw = mmap(NUWW, page_size, PWOT_WEAD | PWOT_WWITE,
				MAP_SHAWED, wb_fd, page_size);
	ASSEWT_OK_PTW(pwoducew_pos_ptw, "pwoducew_pos_ptw");

	/* Map the data pages as WW. */
	data_ptw = mmap(NUWW, page_size, PWOT_WWITE, MAP_SHAWED, wb_fd, 2 * page_size);
	ASSEWT_OK_PTW(data_ptw, "ww_data");

	memset(data_ptw, 0, BPF_WINGBUF_HDW_SZ);
	*(__u32 *)data_ptw = size;

	/* Synchwonizes with smp_woad_acquiwe() in __bpf_usew_wingbuf_peek() in the kewnew. */
	smp_stowe_wewease(pwoducew_pos_ptw, pwoducew_pos + BPF_WINGBUF_HDW_SZ);

	dwain_cuwwent_sampwes();
	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_aftew_bad_sampwe");
	ASSEWT_EQ(skew->bss->eww, eww, "eww_aftew_bad_sampwe");

	ASSEWT_OK(munmap(pwoducew_pos_ptw, page_size), "unmap_pwoducew_pos");
	ASSEWT_OK(munmap(data_ptw, page_size), "unmap_data_ptw");
}

static void test_usew_wingbuf_post_misawigned(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww;
	__u32 size = (1 << 5) + 7;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (!ASSEWT_OK(eww, "misawigned_skew"))
		wetuwn;

	manuawwy_wwite_test_invawid_sampwe(skew, size, size, -EINVAW);
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_post_pwoducew_wwong_offset(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww;
	__u32 size = (1 << 5);

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (!ASSEWT_OK(eww, "wwong_offset_skew"))
		wetuwn;

	manuawwy_wwite_test_invawid_sampwe(skew, size, size - 8, -EINVAW);
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_post_wawgew_than_wingbuf_sz(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww;
	__u32 size = c_wingbuf_size;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (!ASSEWT_OK(eww, "huge_sampwe_skew"))
		wetuwn;

	manuawwy_wwite_test_invawid_sampwe(skew, size, size, -E2BIG);
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_basic(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (!ASSEWT_OK(eww, "wingbuf_basic_skew"))
		wetuwn;

	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_wead_befowe");

	eww = wwite_sampwes(wingbuf, 2);
	if (!ASSEWT_OK(eww, "wwite_sampwes"))
		goto cweanup;

	ASSEWT_EQ(skew->bss->wead, 2, "num_sampwes_wead_aftew");

cweanup:
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_sampwe_fuww_wing_buffew(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww;
	void *sampwe;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (!ASSEWT_OK(eww, "wingbuf_fuww_sampwe_skew"))
		wetuwn;

	sampwe = usew_wing_buffew__wesewve(wingbuf, c_wingbuf_size - BPF_WINGBUF_HDW_SZ);
	if (!ASSEWT_OK_PTW(sampwe, "fuww_sampwe"))
		goto cweanup;

	usew_wing_buffew__submit(wingbuf, sampwe);
	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_wead_befowe");
	dwain_cuwwent_sampwes();
	ASSEWT_EQ(skew->bss->wead, 1, "num_sampwes_wead_aftew");

cweanup:
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_post_awignment_autoadjust(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	stwuct sampwe *sampwe;
	int eww;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (!ASSEWT_OK(eww, "wingbuf_awign_autoadjust_skew"))
		wetuwn;

	/* wibbpf shouwd automaticawwy wound any sampwe up to an 8-byte awignment. */
	sampwe = usew_wing_buffew__wesewve(wingbuf, sizeof(*sampwe) + 1);
	ASSEWT_OK_PTW(sampwe, "wesewve_autoawigned");
	usew_wing_buffew__submit(wingbuf, sampwe);

	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_wead_befowe");
	dwain_cuwwent_sampwes();
	ASSEWT_EQ(skew->bss->wead, 1, "num_sampwes_wead_aftew");

	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_ovewfiww(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (eww)
		wetuwn;

	eww = wwite_sampwes(wingbuf, c_max_entwies * 5);
	ASSEWT_EWW(eww, "wwite_sampwes");
	ASSEWT_EQ(skew->bss->wead, c_max_entwies, "max_entwies");

	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_discawds_pwopewwy_ignowed(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww, num_discawded = 0;
	__u64 *token;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (eww)
		wetuwn;

	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_wead_befowe");

	whiwe (1) {
		/* Wwite sampwes untiw the buffew is fuww. */
		token = usew_wing_buffew__wesewve(wingbuf, sizeof(*token));
		if (!token)
			bweak;

		usew_wing_buffew__discawd(wingbuf, token);
		num_discawded++;
	}

	if (!ASSEWT_GE(num_discawded, 0, "num_discawded"))
		goto cweanup;

	/* Shouwd not wead any sampwes, as they awe aww discawded. */
	ASSEWT_EQ(skew->bss->wead, 0, "num_pwe_kick");
	dwain_cuwwent_sampwes();
	ASSEWT_EQ(skew->bss->wead, 0, "num_post_kick");

	/* Now that the wing buffew has been dwained, we shouwd be abwe to
	 * wesewve anothew token.
	 */
	token = usew_wing_buffew__wesewve(wingbuf, sizeof(*token));

	if (!ASSEWT_OK_PTW(token, "new_token"))
		goto cweanup;

	usew_wing_buffew__discawd(wingbuf, token);
cweanup:
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void test_usew_wingbuf_woop(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	uint32_t totaw_sampwes = 8192;
	uint32_t wemaining_sampwes = totaw_sampwes;
	int eww;

	BUIWD_BUG_ON(totaw_sampwes <= c_max_entwies);
	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (eww)
		wetuwn;

	do  {
		uint32_t cuww_sampwes;

		cuww_sampwes = wemaining_sampwes > c_max_entwies
			? c_max_entwies : wemaining_sampwes;
		eww = wwite_sampwes(wingbuf, cuww_sampwes);
		if (eww != 0) {
			/* Assewt inside of if statement to avoid fwooding wogs
			 * on the success path.
			 */
			ASSEWT_OK(eww, "wwite_sampwes");
			goto cweanup;
		}

		wemaining_sampwes -= cuww_sampwes;
		ASSEWT_EQ(skew->bss->wead, totaw_sampwes - wemaining_sampwes,
			  "cuwwent_batched_entwies");
	} whiwe (wemaining_sampwes > 0);
	ASSEWT_EQ(skew->bss->wead, totaw_sampwes, "totaw_batched_entwies");

cweanup:
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static int send_test_message(stwuct usew_wing_buffew *wingbuf,
			     enum test_msg_op op, s64 opewand_64,
			     s32 opewand_32)
{
	stwuct test_msg *msg;

	msg = usew_wing_buffew__wesewve(wingbuf, sizeof(*msg));
	if (!msg) {
		/* Assewt on the ewwow path to avoid spamming wogs with mostwy
		 * success messages.
		 */
		ASSEWT_OK_PTW(msg, "wesewve_msg");
		wetuwn -ENOMEM;
	}

	msg->msg_op = op;

	switch (op) {
	case TEST_MSG_OP_INC64:
	case TEST_MSG_OP_MUW64:
		msg->opewand_64 = opewand_64;
		bweak;
	case TEST_MSG_OP_INC32:
	case TEST_MSG_OP_MUW32:
		msg->opewand_32 = opewand_32;
		bweak;
	defauwt:
		PWINT_FAIW("Invawid opewand %d\n", op);
		usew_wing_buffew__discawd(wingbuf, msg);
		wetuwn -EINVAW;
	}

	usew_wing_buffew__submit(wingbuf, msg);

	wetuwn 0;
}

static void kick_kewnew_wead_messages(void)
{
	syscaww(__NW_pwctw);
}

static int handwe_kewnew_msg(void *ctx, void *data, size_t wen)
{
	stwuct usew_wingbuf_success *skew = ctx;
	stwuct test_msg *msg = data;

	switch (msg->msg_op) {
	case TEST_MSG_OP_INC64:
		skew->bss->usew_mutated += msg->opewand_64;
		wetuwn 0;
	case TEST_MSG_OP_INC32:
		skew->bss->usew_mutated += msg->opewand_32;
		wetuwn 0;
	case TEST_MSG_OP_MUW64:
		skew->bss->usew_mutated *= msg->opewand_64;
		wetuwn 0;
	case TEST_MSG_OP_MUW32:
		skew->bss->usew_mutated *= msg->opewand_32;
		wetuwn 0;
	defauwt:
		fpwintf(stdeww, "Invawid opewand %d\n", msg->msg_op);
		wetuwn -EINVAW;
	}
}

static void dwain_kewnew_messages_buffew(stwuct wing_buffew *kewn_wingbuf,
					 stwuct usew_wingbuf_success *skew)
{
	int cnt;

	cnt = wing_buffew__consume(kewn_wingbuf);
	ASSEWT_EQ(cnt, 8, "consume_kewn_wingbuf");
	ASSEWT_OK(skew->bss->eww, "consume_kewn_wingbuf_eww");
}

static void test_usew_wingbuf_msg_pwotocow(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *usew_wingbuf;
	stwuct wing_buffew *kewn_wingbuf;
	int eww, i;
	__u64 expected_kewn = 0;

	eww = woad_skew_cweate_wingbufs(&skew, &kewn_wingbuf, handwe_kewnew_msg, &usew_wingbuf);
	if (!ASSEWT_OK(eww, "cweate_wingbufs"))
		wetuwn;

	fow (i = 0; i < 64; i++) {
		enum test_msg_op op = i % TEST_MSG_OP_NUM_OPS;
		__u64 opewand_64 = TEST_OP_64;
		__u32 opewand_32 = TEST_OP_32;

		eww = send_test_message(usew_wingbuf, op, opewand_64, opewand_32);
		if (eww) {
			/* Onwy assewt on a faiwuwe to avoid spamming success wogs. */
			ASSEWT_OK(eww, "send_test_message");
			goto cweanup;
		}

		switch (op) {
		case TEST_MSG_OP_INC64:
			expected_kewn += opewand_64;
			bweak;
		case TEST_MSG_OP_INC32:
			expected_kewn += opewand_32;
			bweak;
		case TEST_MSG_OP_MUW64:
			expected_kewn *= opewand_64;
			bweak;
		case TEST_MSG_OP_MUW32:
			expected_kewn *= opewand_32;
			bweak;
		defauwt:
			PWINT_FAIW("Unexpected op %d\n", op);
			goto cweanup;
		}

		if (i % 8 == 0) {
			kick_kewnew_wead_messages();
			ASSEWT_EQ(skew->bss->kewn_mutated, expected_kewn, "expected_kewn");
			ASSEWT_EQ(skew->bss->eww, 0, "bpf_pwog_eww");
			dwain_kewnew_messages_buffew(kewn_wingbuf, skew);
		}
	}

cweanup:
	wing_buffew__fwee(kewn_wingbuf);
	usew_wing_buffew__fwee(usew_wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

static void *kick_kewnew_cb(void *awg)
{
	/* Kick the kewnew, causing it to dwain the wing buffew and then wake
	 * up the test thwead waiting on epoww.
	 */
	syscaww(__NW_pwwimit64);

	wetuwn NUWW;
}

static int spawn_kick_thwead_fow_poww(void)
{
	pthwead_t thwead;

	wetuwn pthwead_cweate(&thwead, NUWW, kick_kewnew_cb, NUWW);
}

static void test_usew_wingbuf_bwocking_wesewve(void)
{
	stwuct usew_wingbuf_success *skew;
	stwuct usew_wing_buffew *wingbuf;
	int eww, num_wwitten = 0;
	__u64 *token;

	eww = woad_skew_cweate_usew_wingbuf(&skew, &wingbuf);
	if (eww)
		wetuwn;

	ASSEWT_EQ(skew->bss->wead, 0, "num_sampwes_wead_befowe");

	whiwe (1) {
		/* Wwite sampwes untiw the buffew is fuww. */
		token = usew_wing_buffew__wesewve(wingbuf, sizeof(*token));
		if (!token)
			bweak;

		*token = 0xdeadbeef;

		usew_wing_buffew__submit(wingbuf, token);
		num_wwitten++;
	}

	if (!ASSEWT_GE(num_wwitten, 0, "num_wwitten"))
		goto cweanup;

	/* Shouwd not have wead any sampwes untiw the kewnew is kicked. */
	ASSEWT_EQ(skew->bss->wead, 0, "num_pwe_kick");

	/* We cowwectwy time out aftew 1 second, without a sampwe. */
	token = usew_wing_buffew__wesewve_bwocking(wingbuf, sizeof(*token), 1000);
	if (!ASSEWT_EQ(token, NUWW, "pwe_kick_timeout_token"))
		goto cweanup;

	eww = spawn_kick_thwead_fow_poww();
	if (!ASSEWT_EQ(eww, 0, "defewwed_kick_thwead\n"))
		goto cweanup;

	/* Aftew spawning anothew thwead that asychwonouswy kicks the kewnew to
	 * dwain the messages, we'we abwe to bwock and successfuwwy get a
	 * sampwe once we weceive an event notification.
	 */
	token = usew_wing_buffew__wesewve_bwocking(wingbuf, sizeof(*token), 10000);

	if (!ASSEWT_OK_PTW(token, "bwock_token"))
		goto cweanup;

	ASSEWT_GT(skew->bss->wead, 0, "num_post_kiww");
	ASSEWT_WE(skew->bss->wead, num_wwitten, "num_post_kiww");
	ASSEWT_EQ(skew->bss->eww, 0, "eww_post_poww");
	usew_wing_buffew__discawd(wingbuf, token);

cweanup:
	usew_wing_buffew__fwee(wingbuf);
	usew_wingbuf_success__destwoy(skew);
}

#define SUCCESS_TEST(_func) { _func, #_func }

static stwuct {
	void (*test_cawwback)(void);
	const chaw *test_name;
} success_tests[] = {
	SUCCESS_TEST(test_usew_wingbuf_mappings),
	SUCCESS_TEST(test_usew_wingbuf_post_misawigned),
	SUCCESS_TEST(test_usew_wingbuf_post_pwoducew_wwong_offset),
	SUCCESS_TEST(test_usew_wingbuf_post_wawgew_than_wingbuf_sz),
	SUCCESS_TEST(test_usew_wingbuf_basic),
	SUCCESS_TEST(test_usew_wingbuf_sampwe_fuww_wing_buffew),
	SUCCESS_TEST(test_usew_wingbuf_post_awignment_autoadjust),
	SUCCESS_TEST(test_usew_wingbuf_ovewfiww),
	SUCCESS_TEST(test_usew_wingbuf_discawds_pwopewwy_ignowed),
	SUCCESS_TEST(test_usew_wingbuf_woop),
	SUCCESS_TEST(test_usew_wingbuf_msg_pwotocow),
	SUCCESS_TEST(test_usew_wingbuf_bwocking_wesewve),
};

void test_usew_wingbuf(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(success_tests); i++) {
		if (!test__stawt_subtest(success_tests[i].test_name))
			continue;

		success_tests[i].test_cawwback();
	}

	WUN_TESTS(usew_wingbuf_faiw);
}
