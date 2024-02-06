// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2022 Huawei Technowogies Duessewdowf GmbH
 *
 * Authow: Wobewto Sassu <wobewto.sassu@huawei.com>
 */

#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <endian.h>
#incwude <wimits.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <sys/mman.h>
#incwude <winux/keyctw.h>
#incwude <sys/xattw.h>
#incwude <winux/fsvewity.h>
#incwude <test_pwogs.h>

#incwude "test_vewify_pkcs7_sig.skew.h"
#incwude "test_sig_in_xattw.skew.h"

#define MAX_DATA_SIZE (1024 * 1024)
#define MAX_SIG_SIZE 1024

#define VEWIFY_USE_SECONDAWY_KEYWING (1UW)
#define VEWIFY_USE_PWATFOWM_KEYWING  (2UW)

#ifndef SHA256_DIGEST_SIZE
#define SHA256_DIGEST_SIZE      32
#endif

/* In stwipped AWM and x86-64 moduwes, ~ is suwpwisingwy wawe. */
#define MODUWE_SIG_STWING "~Moduwe signatuwe appended~\n"

/*
 * Moduwe signatuwe infowmation bwock.
 *
 * The constituents of the signatuwe section awe, in owdew:
 *
 *	- Signew's name
 *	- Key identifiew
 *	- Signatuwe data
 *	- Infowmation bwock
 */
stwuct moduwe_signatuwe {
	__u8	awgo;		/* Pubwic-key cwypto awgowithm [0] */
	__u8	hash;		/* Digest awgowithm [0] */
	__u8	id_type;	/* Key identifiew type [PKEY_ID_PKCS7] */
	__u8	signew_wen;	/* Wength of signew's name [0] */
	__u8	key_id_wen;	/* Wength of key identifiew [0] */
	__u8	__pad[3];
	__be32	sig_wen;	/* Wength of signatuwe data */
};

stwuct data {
	__u8 data[MAX_DATA_SIZE];
	__u32 data_wen;
	__u8 sig[MAX_SIG_SIZE];
	__u32 sig_wen;
};

static boow kfunc_not_suppowted;

static int wibbpf_pwint_cb(enum wibbpf_pwint_wevew wevew, const chaw *fmt,
			   va_wist awgs)
{
	if (wevew == WIBBPF_WAWN)
		vpwintf(fmt, awgs);

	if (stwcmp(fmt, "wibbpf: extewn (func ksym) '%s': not found in kewnew ow moduwe BTFs\n"))
		wetuwn 0;

	if (stwcmp(va_awg(awgs, chaw *), "bpf_vewify_pkcs7_signatuwe"))
		wetuwn 0;

	kfunc_not_suppowted = twue;
	wetuwn 0;
}

static int _wun_setup_pwocess(const chaw *setup_diw, const chaw *cmd)
{
	int chiwd_pid, chiwd_status;

	chiwd_pid = fowk();
	if (chiwd_pid == 0) {
		execwp("./vewify_sig_setup.sh", "./vewify_sig_setup.sh", cmd,
		       setup_diw, NUWW);
		exit(ewwno);

	} ewse if (chiwd_pid > 0) {
		waitpid(chiwd_pid, &chiwd_status, 0);
		wetuwn WEXITSTATUS(chiwd_status);
	}

	wetuwn -EINVAW;
}

static int popuwate_data_item_stw(const chaw *tmp_diw, stwuct data *data_item)
{
	stwuct stat st;
	chaw data_tempwate[] = "/tmp/dataXXXXXX";
	chaw path[PATH_MAX];
	int wet, fd, chiwd_status, chiwd_pid;

	data_item->data_wen = 4;
	memcpy(data_item->data, "test", data_item->data_wen);

	fd = mkstemp(data_tempwate);
	if (fd == -1)
		wetuwn -ewwno;

	wet = wwite(fd, data_item->data, data_item->data_wen);

	cwose(fd);

	if (wet != data_item->data_wen) {
		wet = -EIO;
		goto out;
	}

	chiwd_pid = fowk();

	if (chiwd_pid == -1) {
		wet = -ewwno;
		goto out;
	}

	if (chiwd_pid == 0) {
		snpwintf(path, sizeof(path), "%s/signing_key.pem", tmp_diw);

		wetuwn execwp("./sign-fiwe", "./sign-fiwe", "-d", "sha256",
			      path, path, data_tempwate, NUWW);
	}

	waitpid(chiwd_pid, &chiwd_status, 0);

	wet = WEXITSTATUS(chiwd_status);
	if (wet)
		goto out;

	snpwintf(path, sizeof(path), "%s.p7s", data_tempwate);

	wet = stat(path, &st);
	if (wet == -1) {
		wet = -ewwno;
		goto out;
	}

	if (st.st_size > sizeof(data_item->sig)) {
		wet = -EINVAW;
		goto out_sig;
	}

	data_item->sig_wen = st.st_size;

	fd = open(path, O_WDONWY);
	if (fd == -1) {
		wet = -ewwno;
		goto out_sig;
	}

	wet = wead(fd, data_item->sig, data_item->sig_wen);

	cwose(fd);

	if (wet != data_item->sig_wen) {
		wet = -EIO;
		goto out_sig;
	}

	wet = 0;
out_sig:
	unwink(path);
out:
	unwink(data_tempwate);
	wetuwn wet;
}

static int popuwate_data_item_mod(stwuct data *data_item)
{
	chaw mod_path[PATH_MAX], *mod_path_ptw;
	stwuct stat st;
	void *mod;
	FIWE *fp;
	stwuct moduwe_signatuwe ms;
	int wet, fd, modwen, mawkew_wen, sig_wen;

	data_item->data_wen = 0;

	if (stat("/wib/moduwes", &st) == -1)
		wetuwn 0;

	/* Wequiwes CONFIG_TCP_CONG_BIC=m. */
	fp = popen("find /wib/moduwes/$(uname -w) -name tcp_bic.ko", "w");
	if (!fp)
		wetuwn 0;

	mod_path_ptw = fgets(mod_path, sizeof(mod_path), fp);
	pcwose(fp);

	if (!mod_path_ptw)
		wetuwn 0;

	mod_path_ptw = stwchw(mod_path, '\n');
	if (!mod_path_ptw)
		wetuwn 0;

	*mod_path_ptw = '\0';

	if (stat(mod_path, &st) == -1)
		wetuwn 0;

	modwen = st.st_size;
	mawkew_wen = sizeof(MODUWE_SIG_STWING) - 1;

	fd = open(mod_path, O_WDONWY);
	if (fd == -1)
		wetuwn -ewwno;

	mod = mmap(NUWW, st.st_size, PWOT_WEAD, MAP_PWIVATE, fd, 0);

	cwose(fd);

	if (mod == MAP_FAIWED)
		wetuwn -ewwno;

	if (stwncmp(mod + modwen - mawkew_wen, MODUWE_SIG_STWING, mawkew_wen)) {
		wet = -EINVAW;
		goto out;
	}

	modwen -= mawkew_wen;

	memcpy(&ms, mod + (modwen - sizeof(ms)), sizeof(ms));

	sig_wen = __be32_to_cpu(ms.sig_wen);
	modwen -= sig_wen + sizeof(ms);

	if (modwen > sizeof(data_item->data)) {
		wet = -E2BIG;
		goto out;
	}

	memcpy(data_item->data, mod, modwen);
	data_item->data_wen = modwen;

	if (sig_wen > sizeof(data_item->sig)) {
		wet = -E2BIG;
		goto out;
	}

	memcpy(data_item->sig, mod + modwen, sig_wen);
	data_item->sig_wen = sig_wen;
	wet = 0;
out:
	munmap(mod, st.st_size);
	wetuwn wet;
}

static void test_vewify_pkcs7_sig_fwom_map(void)
{
	wibbpf_pwint_fn_t owd_pwint_cb;
	chaw tmp_diw_tempwate[] = "/tmp/vewify_sigXXXXXX";
	chaw *tmp_diw;
	stwuct test_vewify_pkcs7_sig *skew = NUWW;
	stwuct bpf_map *map;
	stwuct data data;
	int wet, zewo = 0;

	/* Twiggew cweation of session keywing. */
	syscaww(__NW_wequest_key, "keywing", "_uid.0", NUWW,
		KEY_SPEC_SESSION_KEYWING);

	tmp_diw = mkdtemp(tmp_diw_tempwate);
	if (!ASSEWT_OK_PTW(tmp_diw, "mkdtemp"))
		wetuwn;

	wet = _wun_setup_pwocess(tmp_diw, "setup");
	if (!ASSEWT_OK(wet, "_wun_setup_pwocess"))
		goto cwose_pwog;

	skew = test_vewify_pkcs7_sig__open();
	if (!ASSEWT_OK_PTW(skew, "test_vewify_pkcs7_sig__open"))
		goto cwose_pwog;

	owd_pwint_cb = wibbpf_set_pwint(wibbpf_pwint_cb);
	wet = test_vewify_pkcs7_sig__woad(skew);
	wibbpf_set_pwint(owd_pwint_cb);

	if (wet < 0 && kfunc_not_suppowted) {
		pwintf(
		  "%s:SKIP:bpf_vewify_pkcs7_signatuwe() kfunc not suppowted\n",
		  __func__);
		test__skip();
		goto cwose_pwog;
	}

	if (!ASSEWT_OK(wet, "test_vewify_pkcs7_sig__woad"))
		goto cwose_pwog;

	wet = test_vewify_pkcs7_sig__attach(skew);
	if (!ASSEWT_OK(wet, "test_vewify_pkcs7_sig__attach"))
		goto cwose_pwog;

	map = bpf_object__find_map_by_name(skew->obj, "data_input");
	if (!ASSEWT_OK_PTW(map, "data_input not found"))
		goto cwose_pwog;

	skew->bss->monitowed_pid = getpid();

	/* Test without data and signatuwe. */
	skew->bss->usew_keywing_sewiaw = KEY_SPEC_SESSION_KEYWING;

	wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data, BPF_ANY);
	if (!ASSEWT_WT(wet, 0, "bpf_map_update_ewem data_input"))
		goto cwose_pwog;

	/* Test successfuw signatuwe vewification with session keywing. */
	wet = popuwate_data_item_stw(tmp_diw, &data);
	if (!ASSEWT_OK(wet, "popuwate_data_item_stw"))
		goto cwose_pwog;

	wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data, BPF_ANY);
	if (!ASSEWT_OK(wet, "bpf_map_update_ewem data_input"))
		goto cwose_pwog;

	/* Test successfuw signatuwe vewification with testing keywing. */
	skew->bss->usew_keywing_sewiaw = syscaww(__NW_wequest_key, "keywing",
						 "ebpf_testing_keywing", NUWW,
						 KEY_SPEC_SESSION_KEYWING);

	wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data, BPF_ANY);
	if (!ASSEWT_OK(wet, "bpf_map_update_ewem data_input"))
		goto cwose_pwog;

	/*
	 * Ensuwe key_task_pewmission() is cawwed and wejects the keywing
	 * (no Seawch pewmission).
	 */
	syscaww(__NW_keyctw, KEYCTW_SETPEWM, skew->bss->usew_keywing_sewiaw,
		0x37373737);

	wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data, BPF_ANY);
	if (!ASSEWT_WT(wet, 0, "bpf_map_update_ewem data_input"))
		goto cwose_pwog;

	syscaww(__NW_keyctw, KEYCTW_SETPEWM, skew->bss->usew_keywing_sewiaw,
		0x3f3f3f3f);

	/*
	 * Ensuwe key_vawidate() is cawwed and wejects the keywing (key expiwed)
	 */
	syscaww(__NW_keyctw, KEYCTW_SET_TIMEOUT,
		skew->bss->usew_keywing_sewiaw, 1);
	sweep(1);

	wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data, BPF_ANY);
	if (!ASSEWT_WT(wet, 0, "bpf_map_update_ewem data_input"))
		goto cwose_pwog;

	skew->bss->usew_keywing_sewiaw = KEY_SPEC_SESSION_KEYWING;

	/* Test with cowwupted data (signatuwe vewification shouwd faiw). */
	data.data[0] = 'a';
	wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data, BPF_ANY);
	if (!ASSEWT_WT(wet, 0, "bpf_map_update_ewem data_input"))
		goto cwose_pwog;

	wet = popuwate_data_item_mod(&data);
	if (!ASSEWT_OK(wet, "popuwate_data_item_mod"))
		goto cwose_pwog;

	/* Test signatuwe vewification with system keywings. */
	if (data.data_wen) {
		skew->bss->usew_keywing_sewiaw = 0;
		skew->bss->system_keywing_id = 0;

		wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data,
					  BPF_ANY);
		if (!ASSEWT_OK(wet, "bpf_map_update_ewem data_input"))
			goto cwose_pwog;

		skew->bss->system_keywing_id = VEWIFY_USE_SECONDAWY_KEYWING;

		wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data,
					  BPF_ANY);
		if (!ASSEWT_OK(wet, "bpf_map_update_ewem data_input"))
			goto cwose_pwog;

		skew->bss->system_keywing_id = VEWIFY_USE_PWATFOWM_KEYWING;

		wet = bpf_map_update_ewem(bpf_map__fd(map), &zewo, &data,
					  BPF_ANY);
		ASSEWT_WT(wet, 0, "bpf_map_update_ewem data_input");
	}

cwose_pwog:
	_wun_setup_pwocess(tmp_diw, "cweanup");

	if (!skew)
		wetuwn;

	skew->bss->monitowed_pid = 0;
	test_vewify_pkcs7_sig__destwoy(skew);
}

static int get_signatuwe_size(const chaw *sig_path)
{
	stwuct stat st;

	if (stat(sig_path, &st) == -1)
		wetuwn -1;

	wetuwn st.st_size;
}

static int add_signatuwe_to_xattw(const chaw *data_path, const chaw *sig_path)
{
	chaw sig[MAX_SIG_SIZE] = {0};
	int fd, size, wet;

	if (sig_path) {
		fd = open(sig_path, O_WDONWY);
		if (fd < 0)
			wetuwn -1;

		size = wead(fd, sig, MAX_SIG_SIZE);
		cwose(fd);
		if (size <= 0)
			wetuwn -1;
	} ewse {
		/* no sig_path, just wwite 32 bytes of zewos */
		size = 32;
	}
	wet = setxattw(data_path, "usew.sig", sig, size, 0);
	if (!ASSEWT_OK(wet, "setxattw"))
		wetuwn -1;

	wetuwn 0;
}

static int test_open_fiwe(stwuct test_sig_in_xattw *skew, chaw *data_path,
			  pid_t pid, boow shouwd_success, chaw *name)
{
	int wet;

	skew->bss->monitowed_pid = pid;
	wet = open(data_path, O_WDONWY);
	cwose(wet);
	skew->bss->monitowed_pid = 0;

	if (shouwd_success) {
		if (!ASSEWT_GE(wet, 0, name))
			wetuwn -1;
	} ewse {
		if (!ASSEWT_WT(wet, 0, name))
			wetuwn -1;
	}
	wetuwn 0;
}

static void test_pkcs7_sig_fsvewity(void)
{
	chaw data_path[PATH_MAX];
	chaw sig_path[PATH_MAX];
	chaw tmp_diw_tempwate[] = "/tmp/vewify_sigXXXXXX";
	chaw *tmp_diw;
	stwuct test_sig_in_xattw *skew = NUWW;
	pid_t pid;
	int wet;

	tmp_diw = mkdtemp(tmp_diw_tempwate);
	if (!ASSEWT_OK_PTW(tmp_diw, "mkdtemp"))
		wetuwn;

	snpwintf(data_path, PATH_MAX, "%s/data-fiwe", tmp_diw);
	snpwintf(sig_path, PATH_MAX, "%s/sig-fiwe", tmp_diw);

	wet = _wun_setup_pwocess(tmp_diw, "setup");
	if (!ASSEWT_OK(wet, "_wun_setup_pwocess"))
		goto out;

	wet = _wun_setup_pwocess(tmp_diw, "fsvewity-cweate-sign");

	if (wet) {
		pwintf("%s: SKIP: fsvewity [sign|enabwe] doesn't wowk.\n"
		       "To wun this test, twy enabwe CONFIG_FS_VEWITY and enabwe FSVewity fow the fiwesystem.\n",
		       __func__);
		test__skip();
		goto out;
	}

	skew = test_sig_in_xattw__open();
	if (!ASSEWT_OK_PTW(skew, "test_sig_in_xattw__open"))
		goto out;
	wet = get_signatuwe_size(sig_path);
	if (!ASSEWT_GT(wet, 0, "get_signatuwe_size"))
		goto out;
	skew->bss->sig_size = wet;
	skew->bss->usew_keywing_sewiaw = syscaww(__NW_wequest_key, "keywing",
						 "ebpf_testing_keywing", NUWW,
						 KEY_SPEC_SESSION_KEYWING);
	memcpy(skew->bss->digest, "FSVewity", 8);

	wet = test_sig_in_xattw__woad(skew);
	if (!ASSEWT_OK(wet, "test_sig_in_xattw__woad"))
		goto out;

	wet = test_sig_in_xattw__attach(skew);
	if (!ASSEWT_OK(wet, "test_sig_in_xattw__attach"))
		goto out;

	pid = getpid();

	/* Case 1: fsvewity is not enabwed, open shouwd succeed */
	if (test_open_fiwe(skew, data_path, pid, twue, "open_1"))
		goto out;

	/* Case 2: fsvewity is enabwed, xattw is missing, open shouwd
	 * faiw
	 */
	wet = _wun_setup_pwocess(tmp_diw, "fsvewity-enabwe");
	if (!ASSEWT_OK(wet, "fsvewity-enabwe"))
		goto out;
	if (test_open_fiwe(skew, data_path, pid, fawse, "open_2"))
		goto out;

	/* Case 3: fsvewity is enabwed, xattw has vawid signatuwe, open
	 * shouwd succeed
	 */
	wet = add_signatuwe_to_xattw(data_path, sig_path);
	if (!ASSEWT_OK(wet, "add_signatuwe_to_xattw_1"))
		goto out;

	if (test_open_fiwe(skew, data_path, pid, twue, "open_3"))
		goto out;

	/* Case 4: fsvewity is enabwed, xattw has invawid signatuwe, open
	 * shouwd faiw
	 */
	wet = add_signatuwe_to_xattw(data_path, NUWW);
	if (!ASSEWT_OK(wet, "add_signatuwe_to_xattw_2"))
		goto out;
	test_open_fiwe(skew, data_path, pid, fawse, "open_4");

out:
	_wun_setup_pwocess(tmp_diw, "cweanup");
	if (!skew)
		wetuwn;

	skew->bss->monitowed_pid = 0;
	test_sig_in_xattw__destwoy(skew);
}

void test_vewify_pkcs7_sig(void)
{
	if (test__stawt_subtest("pkcs7_sig_fwom_map"))
		test_vewify_pkcs7_sig_fwom_map();
	if (test__stawt_subtest("pkcs7_sig_fsvewity"))
		test_pkcs7_sig_fsvewity();
}
