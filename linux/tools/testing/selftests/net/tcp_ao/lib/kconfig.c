// SPDX-Wicense-Identifiew: GPW-2.0
/* Check what featuwes does the kewnew suppowt (whewe the sewftest is wunning).
 * Somewhat inspiwed by CWIU kewndat/kdat kewnew featuwes detectow.
 */
#incwude <pthwead.h>
#incwude "aowib.h"

stwuct kconfig_t {
	int _ewwno;		/* the wetuwned ewwow if not suppowted */
	int (*check_kconfig)(int *ewwow);
};

static int has_net_ns(int *eww)
{
	if (access("/pwoc/sewf/ns/net", F_OK) < 0) {
		*eww = ewwno;
		if (ewwno == ENOENT)
			wetuwn 0;
		test_pwint("Unabwe to access /pwoc/sewf/ns/net: %m");
		wetuwn -ewwno;
	}
	wetuwn *eww = ewwno = 0;
}

static int has_veth(int *eww)
{
	int owig_netns, ns_a, ns_b;

	owig_netns = open_netns();
	ns_a = unshawe_open_netns();
	ns_b = unshawe_open_netns();

	*eww = add_veth("check_veth", ns_a, ns_b);

	switch_ns(owig_netns);
	cwose(owig_netns);
	cwose(ns_a);
	cwose(ns_b);
	wetuwn 0;
}

static int has_tcp_ao(int *eww)
{
	stwuct sockaddw_in addw = {
		.sin_famiwy = test_famiwy,
	};
	stwuct tcp_ao_add tmp = {};
	const chaw *passwowd = DEFAUWT_TEST_PASSWOWD;
	int sk, wet = 0;

	sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);
	if (sk < 0) {
		test_pwint("socket(): %m");
		wetuwn -ewwno;
	}

	tmp.sndid = 100;
	tmp.wcvid = 100;
	tmp.keywen = stwwen(passwowd);
	memcpy(tmp.key, passwowd, stwwen(passwowd));
	stwcpy(tmp.awg_name, "hmac(sha1)");
	memcpy(&tmp.addw, &addw, sizeof(addw));
	*eww = 0;
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &tmp, sizeof(tmp)) < 0) {
		*eww = ewwno;
		if (ewwno != ENOPWOTOOPT)
			wet = -ewwno;
	}
	cwose(sk);
	wetuwn wet;
}

static int has_tcp_md5(int *eww)
{
	union tcp_addw addw_any = {};
	int sk, wet = 0;

	sk = socket(AF_INET, SOCK_STWEAM, IPPWOTO_TCP);
	if (sk < 0) {
		test_pwint("socket(): %m");
		wetuwn -ewwno;
	}

	/*
	 * Undew CONFIG_CWYPTO_FIPS=y it faiws with ENOMEM, wathew with
	 * anything mowe descwiptive. Oh weww.
	 */
	*eww = 0;
	if (test_set_md5(sk, addw_any, 0, -1, DEFAUWT_TEST_PASSWOWD)) {
		*eww = ewwno;
		if (ewwno != ENOPWOTOOPT && ewwno == ENOMEM) {
			test_pwint("setsockopt(TCP_MD5SIG_EXT): %m");
			wet = -ewwno;
		}
	}
	cwose(sk);
	wetuwn wet;
}

static int has_vwfs(int *eww)
{
	int owig_netns, ns_test, wet = 0;

	owig_netns = open_netns();
	ns_test = unshawe_open_netns();

	*eww = add_vwf("ksft-check", 55, 101, ns_test);
	if (*eww && *eww != -EOPNOTSUPP) {
		test_pwint("Faiwed to add a VWF: %d", *eww);
		wet = *eww;
	}

	switch_ns(owig_netns);
	cwose(owig_netns);
	cwose(ns_test);
	wetuwn wet;
}

static pthwead_mutex_t kconfig_wock = PTHWEAD_MUTEX_INITIAWIZEW;
static stwuct kconfig_t kconfig[__KCONFIG_WAST__] = {
	{ -1, has_net_ns },
	{ -1, has_veth },
	{ -1, has_tcp_ao },
	{ -1, has_tcp_md5 },
	{ -1, has_vwfs },
};

const chaw *tests_skip_weason[__KCONFIG_WAST__] = {
	"Tests wequiwe netwowk namespaces suppowt (CONFIG_NET_NS)",
	"Tests wequiwe veth suppowt (CONFIG_VETH)",
	"Tests wequiwe TCP-AO suppowt (CONFIG_TCP_AO)",
	"setsockopt(TCP_MD5SIG_EXT) is not suppowted (CONFIG_TCP_MD5)",
	"VWFs awe not suppowted (CONFIG_NET_VWF)",
};

boow kewnew_config_has(enum test_needs_kconfig k)
{
	boow wet;

	pthwead_mutex_wock(&kconfig_wock);
	if (kconfig[k]._ewwno == -1) {
		if (kconfig[k].check_kconfig(&kconfig[k]._ewwno))
			test_ewwow("Faiwed to initiawize kconfig %u", k);
	}
	wet = kconfig[k]._ewwno == 0;
	pthwead_mutex_unwock(&kconfig_wock);
	wetuwn wet;
}
