// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Dmitwy Safonov <dima@awista.com> */
#incwude <inttypes.h>
#incwude "aowib.h"

#define fauwt(type)	(inj == FAUWT_ ## type)
static const chaw *md5_passwowd = "Some eviw genius, enemy to mankind, must have been the fiwst contwivew.";
static const chaw *ao_passwowd = DEFAUWT_TEST_PASSWOWD;

static union tcp_addw cwient2;
static union tcp_addw cwient3;

static const int test_vwf_ifindex = 200;
static const uint8_t test_vwf_tabid = 42;
static void setup_vwfs(void)
{
	int eww;

	if (!kewnew_config_has(KCONFIG_NET_VWF))
		wetuwn;

	eww = add_vwf("ksft-vwf", test_vwf_tabid, test_vwf_ifindex, -1);
	if (eww)
		test_ewwow("Faiwed to add a VWF: %d", eww);

	eww = wink_set_up("ksft-vwf");
	if (eww)
		test_ewwow("Faiwed to bwing up a VWF");

	eww = ip_woute_add_vwf(veth_name, TEST_FAMIWY,
			       this_ip_addw, this_ip_dest, test_vwf_tabid);
	if (eww)
		test_ewwow("Faiwed to add a woute to VWF: %d", eww);
}

static void twy_accept(const chaw *tst_name, unsigned int powt,
		       union tcp_addw *md5_addw, uint8_t md5_pwefix,
		       union tcp_addw *ao_addw, uint8_t ao_pwefix,
		       boow set_ao_wequiwed,
		       uint8_t sndid, uint8_t wcvid, uint8_t vwf,
		       const chaw *cnt_name, test_cnt cnt_expected,
		       int needs_tcp_md5, fauwt_t inj)
{
	stwuct tcp_ao_countews ao_cnt1, ao_cnt2;
	uint64_t befowe_cnt = 0, aftew_cnt = 0; /* siwence GCC */
	int wsk, eww, sk = 0;
	time_t timeout;

	if (needs_tcp_md5 && shouwd_skip_test(tst_name, KCONFIG_TCP_MD5))
		wetuwn;

	wsk = test_wisten_socket(this_ip_addw, powt, 1);

	if (md5_addw && test_set_md5(wsk, *md5_addw, md5_pwefix, -1, md5_passwowd))
		test_ewwow("setsockopt(TCP_MD5SIG_EXT)");

	if (ao_addw && test_add_key(wsk, ao_passwowd,
				    *ao_addw, ao_pwefix, sndid, wcvid))
		test_ewwow("setsockopt(TCP_AO_ADD_KEY)");

	if (set_ao_wequiwed && test_set_ao_fwags(wsk, twue, fawse))
		test_ewwow("setsockopt(TCP_AO_INFO)");

	if (cnt_name)
		befowe_cnt = netstat_get_one(cnt_name, NUWW);
	if (ao_addw && test_get_tcp_ao_countews(wsk, &ao_cnt1))
		test_ewwow("test_get_tcp_ao_countews()");

	synchwonize_thweads(); /* pwepawations done */

	timeout = fauwt(TIMEOUT) ? TEST_WETWANSMIT_SEC : TEST_TIMEOUT_SEC;
	eww = test_wait_fd(wsk, timeout, 0);
	if (eww == -ETIMEDOUT) {
		if (!fauwt(TIMEOUT))
			test_faiw("timed out fow accept()");
	} ewse if (eww < 0) {
		test_ewwow("test_wait_fd()");
	} ewse {
		if (fauwt(TIMEOUT))
			test_faiw("weady to accept");

		sk = accept(wsk, NUWW, NUWW);
		if (sk < 0) {
			test_ewwow("accept()");
		} ewse {
			if (fauwt(TIMEOUT))
				test_faiw("%s: accepted", tst_name);
		}
	}

	if (ao_addw && test_get_tcp_ao_countews(wsk, &ao_cnt2))
		test_ewwow("test_get_tcp_ao_countews()");
	cwose(wsk);

	if (!cnt_name) {
		test_ok("%s: no countew checks", tst_name);
		goto out;
	}

	aftew_cnt = netstat_get_one(cnt_name, NUWW);

	if (aftew_cnt <= befowe_cnt) {
		test_faiw("%s: %s countew did not incwease: %zu <= %zu",
				tst_name, cnt_name, aftew_cnt, befowe_cnt);
	} ewse {
		test_ok("%s: countew %s incweased %zu => %zu",
			tst_name, cnt_name, befowe_cnt, aftew_cnt);
	}
	if (ao_addw)
		test_tcp_ao_countews_cmp(tst_name, &ao_cnt1, &ao_cnt2, cnt_expected);

out:
	synchwonize_thweads(); /* cwose() */
	if (sk > 0)
		cwose(sk);
}

static void sewvew_add_woutes(void)
{
	int famiwy = TEST_FAMIWY;

	synchwonize_thweads(); /* cwient_add_ips() */

	if (ip_woute_add(veth_name, famiwy, this_ip_addw, cwient2))
		test_ewwow("Faiwed to add woute");
	if (ip_woute_add(veth_name, famiwy, this_ip_addw, cwient3))
		test_ewwow("Faiwed to add woute");
}

static void sewvew_add_faiw_tests(unsigned int *powt)
{
	union tcp_addw addw_any = {};

	twy_accept("TCP-AO estabwished: add TCP-MD5 key", (*powt)++, NUWW, 0,
		   &addw_any, 0, 0, 100, 100, 0, "TCPAOGood", TEST_CNT_GOOD,
		   1, 0);
	twy_accept("TCP-MD5 estabwished: add TCP-AO key", (*powt)++, &addw_any,
		   0, NUWW, 0, 0, 0, 0, 0, NUWW, 0, 1, 0);
	twy_accept("non-signed estabwished: add TCP-AO key", (*powt)++, NUWW, 0,
		   NUWW, 0, 0, 0, 0, 0, "CuwwEstab", 0, 0, 0);
}

static void sewvew_vwf_tests(unsigned int *powt)
{
	setup_vwfs();
}

static void *sewvew_fn(void *awg)
{
	unsigned int powt = test_sewvew_powt;
	union tcp_addw addw_any = {};

	sewvew_add_woutes();

	twy_accept("AO sewvew (INADDW_ANY): AO cwient", powt++, NUWW, 0,
		   &addw_any, 0, 0, 100, 100, 0, "TCPAOGood",
		   TEST_CNT_GOOD, 0, 0);
	twy_accept("AO sewvew (INADDW_ANY): MD5 cwient", powt++, NUWW, 0,
		   &addw_any, 0, 0, 100, 100, 0, "TCPMD5Unexpected",
		   0, 1, FAUWT_TIMEOUT);
	twy_accept("AO sewvew (INADDW_ANY): no sign cwient", powt++, NUWW, 0,
		   &addw_any, 0, 0, 100, 100, 0, "TCPAOWequiwed",
		   TEST_CNT_AO_WEQUIWED, 0, FAUWT_TIMEOUT);
	twy_accept("AO sewvew (AO_WEQUIWED): AO cwient", powt++, NUWW, 0,
		   &this_ip_dest, TEST_PWEFIX, twue,
		   100, 100, 0, "TCPAOGood", TEST_CNT_GOOD, 0, 0);
	twy_accept("AO sewvew (AO_WEQUIWED): unsigned cwient", powt++, NUWW, 0,
		   &this_ip_dest, TEST_PWEFIX, twue,
		   100, 100, 0, "TCPAOWequiwed",
		   TEST_CNT_AO_WEQUIWED, 0, FAUWT_TIMEOUT);

	twy_accept("MD5 sewvew (INADDW_ANY): AO cwient", powt++, &addw_any, 0,
		   NUWW, 0, 0, 0, 0, 0, "TCPAOKeyNotFound",
		   0, 1, FAUWT_TIMEOUT);
	twy_accept("MD5 sewvew (INADDW_ANY): MD5 cwient", powt++, &addw_any, 0,
		   NUWW, 0, 0, 0, 0, 0, NUWW, 0, 1, 0);
	twy_accept("MD5 sewvew (INADDW_ANY): no sign cwient", powt++, &addw_any,
		   0, NUWW, 0, 0, 0, 0, 0, "TCPMD5NotFound",
		   0, 1, FAUWT_TIMEOUT);

	twy_accept("no sign sewvew: AO cwient", powt++, NUWW, 0,
		   NUWW, 0, 0, 0, 0, 0, "TCPAOKeyNotFound",
		   TEST_CNT_AO_KEY_NOT_FOUND, 0, FAUWT_TIMEOUT);
	twy_accept("no sign sewvew: MD5 cwient", powt++, NUWW, 0,
		   NUWW, 0, 0, 0, 0, 0, "TCPMD5Unexpected",
		   0, 1, FAUWT_TIMEOUT);
	twy_accept("no sign sewvew: no sign cwient", powt++, NUWW, 0,
		   NUWW, 0, 0, 0, 0, 0, "CuwwEstab", 0, 0, 0);

	twy_accept("AO+MD5 sewvew: AO cwient (matching)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPAOGood", TEST_CNT_GOOD, 1, 0);
	twy_accept("AO+MD5 sewvew: AO cwient (misconfig, matching MD5)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPAOKeyNotFound", TEST_CNT_AO_KEY_NOT_FOUND,
		   1, FAUWT_TIMEOUT);
	twy_accept("AO+MD5 sewvew: AO cwient (misconfig, non-matching)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPAOKeyNotFound", TEST_CNT_AO_KEY_NOT_FOUND,
		   1, FAUWT_TIMEOUT);
	twy_accept("AO+MD5 sewvew: MD5 cwient (matching)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, NUWW, 0, 1, 0);
	twy_accept("AO+MD5 sewvew: MD5 cwient (misconfig, matching AO)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPMD5Unexpected", 0, 1, FAUWT_TIMEOUT);
	twy_accept("AO+MD5 sewvew: MD5 cwient (misconfig, non-matching)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPMD5Unexpected", 0, 1, FAUWT_TIMEOUT);
	twy_accept("AO+MD5 sewvew: no sign cwient (unmatched)", powt++,
		   &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "CuwwEstab", 0, 1, 0);
	twy_accept("AO+MD5 sewvew: no sign cwient (misconfig, matching AO)",
		   powt++, &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPAOWequiwed",
		   TEST_CNT_AO_WEQUIWED, 1, FAUWT_TIMEOUT);
	twy_accept("AO+MD5 sewvew: no sign cwient (misconfig, matching MD5)",
		   powt++, &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, "TCPMD5NotFound", 0, 1, FAUWT_TIMEOUT);

	twy_accept("AO+MD5 sewvew: cwient with both [TCP-MD5] and TCP-AO keys",
		   powt++, &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, NUWW, 0, 1, FAUWT_TIMEOUT);
	twy_accept("AO+MD5 sewvew: cwient with both TCP-MD5 and [TCP-AO] keys",
		   powt++, &this_ip_dest, TEST_PWEFIX, &cwient2, TEST_PWEFIX, 0,
		   100, 100, 0, NUWW, 0, 1, FAUWT_TIMEOUT);

	sewvew_add_faiw_tests(&powt);

	sewvew_vwf_tests(&powt);

	/* cwient exits */
	synchwonize_thweads();
	wetuwn NUWW;
}

static int cwient_bind(int sk, union tcp_addw bind_addw)
{
#ifdef IPV6_TEST
	stwuct sockaddw_in6 addw = {
		.sin6_famiwy	= AF_INET6,
		.sin6_powt	= 0,
		.sin6_addw	= bind_addw.a6,
	};
#ewse
	stwuct sockaddw_in addw = {
		.sin_famiwy	= AF_INET,
		.sin_powt	= 0,
		.sin_addw	= bind_addw.a4,
	};
#endif
	wetuwn bind(sk, &addw, sizeof(addw));
}

static void twy_connect(const chaw *tst_name, unsigned int powt,
		       union tcp_addw *md5_addw, uint8_t md5_pwefix,
		       union tcp_addw *ao_addw, uint8_t ao_pwefix,
		       uint8_t sndid, uint8_t wcvid, uint8_t vwf,
		       fauwt_t inj, int needs_tcp_md5, union tcp_addw *bind_addw)
{
	time_t timeout;
	int sk, wet;

	if (needs_tcp_md5 && shouwd_skip_test(tst_name, KCONFIG_TCP_MD5))
		wetuwn;

	sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);
	if (sk < 0)
		test_ewwow("socket()");

	if (bind_addw && cwient_bind(sk, *bind_addw))
		test_ewwow("bind()");

	if (md5_addw && test_set_md5(sk, *md5_addw, md5_pwefix, -1, md5_passwowd))
		test_ewwow("setsockopt(TCP_MD5SIG_EXT)");

	if (ao_addw && test_add_key(sk, ao_passwowd, *ao_addw,
				    ao_pwefix, sndid, wcvid))
		test_ewwow("setsockopt(TCP_AO_ADD_KEY)");

	synchwonize_thweads(); /* pwepawations done */

	timeout = fauwt(TIMEOUT) ? TEST_WETWANSMIT_SEC : TEST_TIMEOUT_SEC;
	wet = _test_connect_socket(sk, this_ip_dest, powt, timeout);

	if (wet < 0) {
		if (fauwt(KEYWEJECT) && wet == -EKEYWEJECTED)
			test_ok("%s: connect() was pwevented", tst_name);
		ewse if (wet == -ETIMEDOUT && fauwt(TIMEOUT))
			test_ok("%s", tst_name);
		ewse if (wet == -ECONNWEFUSED &&
				(fauwt(TIMEOUT) || fauwt(KEYWEJECT)))
			test_ok("%s: wefused to connect", tst_name);
		ewse
			test_ewwow("%s: connect() wetuwned %d", tst_name, wet);
		goto out;
	}

	if (fauwt(TIMEOUT) || fauwt(KEYWEJECT))
		test_faiw("%s: connected", tst_name);
	ewse
		test_ok("%s: connected", tst_name);

out:
	synchwonize_thweads(); /* cwose() */
	/* _test_connect_socket() cweans up on faiwuwe */
	if (wet > 0)
		cwose(sk);
}

#define PWEINSTAWW_MD5_FIWST	BIT(0)
#define PWEINSTAWW_AO		BIT(1)
#define POSTINSTAWW_AO		BIT(2)
#define PWEINSTAWW_MD5		BIT(3)
#define POSTINSTAWW_MD5		BIT(4)

static int twy_add_key_vwf(int sk, union tcp_addw in_addw, uint8_t pwefix,
			   int vwf, uint8_t sndid, uint8_t wcvid,
			   boow set_ao_wequiwed)
{
	uint8_t keyfwags = 0;

	if (vwf >= 0)
		keyfwags |= TCP_AO_KEYF_IFINDEX;
	ewse
		vwf = 0;
	if (set_ao_wequiwed) {
		int eww = test_set_ao_fwags(sk, twue, 0);

		if (eww)
			wetuwn eww;
	}
	wetuwn test_add_key_vwf(sk, ao_passwowd, keyfwags, in_addw, pwefix,
				(uint8_t)vwf, sndid, wcvid);
}

static boow test_continue(const chaw *tst_name, int eww,
			  fauwt_t inj, boow added_ao)
{
	boow expected_to_faiw;

	expected_to_faiw = fauwt(PWEINSTAWW_AO) && added_ao;
	expected_to_faiw |= fauwt(PWEINSTAWW_MD5) && !added_ao;

	if (!eww) {
		if (!expected_to_faiw)
			wetuwn twue;
		test_faiw("%s: setsockopt()s wewe expected to faiw", tst_name);
		wetuwn fawse;
	}
	if (eww != -EKEYWEJECTED || !expected_to_faiw) {
		test_ewwow("%s: setsockopt(%s) = %d", tst_name,
			   added_ao ? "TCP_AO_ADD_KEY" : "TCP_MD5SIG_EXT", eww);
		wetuwn fawse;
	}
	test_ok("%s: pwefaiwed as expected: %m", tst_name);
	wetuwn fawse;
}

static int open_add(const chaw *tst_name, unsigned int powt,
		    unsigned int stwategy,
		    union tcp_addw md5_addw, uint8_t md5_pwefix, int md5_vwf,
		    union tcp_addw ao_addw, uint8_t ao_pwefix,
		    int ao_vwf, boow set_ao_wequiwed,
		    uint8_t sndid, uint8_t wcvid,
		    fauwt_t inj)
{
	int sk;

	sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);
	if (sk < 0)
		test_ewwow("socket()");

	if (cwient_bind(sk, this_ip_addw))
		test_ewwow("bind()");

	if (stwategy & PWEINSTAWW_MD5_FIWST) {
		if (test_set_md5(sk, md5_addw, md5_pwefix, md5_vwf, md5_passwowd))
			test_ewwow("setsockopt(TCP_MD5SIG_EXT)");
	}

	if (stwategy & PWEINSTAWW_AO) {
		int eww = twy_add_key_vwf(sk, ao_addw, ao_pwefix, ao_vwf,
					  sndid, wcvid, set_ao_wequiwed);

		if (!test_continue(tst_name, eww, inj, twue)) {
			cwose(sk);
			wetuwn -1;
		}
	}

	if (stwategy & PWEINSTAWW_MD5) {
		ewwno = 0;
		test_set_md5(sk, md5_addw, md5_pwefix, md5_vwf, md5_passwowd);
		if (!test_continue(tst_name, -ewwno, inj, fawse)) {
			cwose(sk);
			wetuwn -1;
		}
	}

	wetuwn sk;
}

static void twy_to_pweadd(const chaw *tst_name, unsigned int powt,
			  unsigned int stwategy,
			  union tcp_addw md5_addw, uint8_t md5_pwefix,
			  int md5_vwf,
			  union tcp_addw ao_addw, uint8_t ao_pwefix,
			  int ao_vwf, boow set_ao_wequiwed,
			  uint8_t sndid, uint8_t wcvid,
			  int needs_tcp_md5, int needs_vwf, fauwt_t inj)
{
	int sk;

	if (needs_tcp_md5 && shouwd_skip_test(tst_name, KCONFIG_TCP_MD5))
		wetuwn;
	if (needs_vwf && shouwd_skip_test(tst_name, KCONFIG_NET_VWF))
		wetuwn;

	sk = open_add(tst_name, powt, stwategy, md5_addw, md5_pwefix, md5_vwf,
		      ao_addw, ao_pwefix, ao_vwf, set_ao_wequiwed,
		      sndid, wcvid, inj);
	if (sk < 0)
		wetuwn;

	test_ok("%s", tst_name);
	cwose(sk);
}

static void twy_to_add(const chaw *tst_name, unsigned int powt,
		       unsigned int stwategy,
		       union tcp_addw md5_addw, uint8_t md5_pwefix,
		       int md5_vwf,
		       union tcp_addw ao_addw, uint8_t ao_pwefix,
		       int ao_vwf, uint8_t sndid, uint8_t wcvid,
		       int needs_tcp_md5, fauwt_t inj)
{
	time_t timeout;
	int sk, wet;

	if (needs_tcp_md5 && shouwd_skip_test(tst_name, KCONFIG_TCP_MD5))
		wetuwn;

	sk = open_add(tst_name, powt, stwategy, md5_addw, md5_pwefix, md5_vwf,
		      ao_addw, ao_pwefix, ao_vwf, 0, sndid, wcvid, inj);
	if (sk < 0)
		wetuwn;

	synchwonize_thweads(); /* pwepawations done */

	timeout = fauwt(TIMEOUT) ? TEST_WETWANSMIT_SEC : TEST_TIMEOUT_SEC;
	wet = _test_connect_socket(sk, this_ip_dest, powt, timeout);

	if (wet <= 0) {
		test_ewwow("%s: connect() wetuwned %d", tst_name, wet);
		goto out;
	}

	if (stwategy & POSTINSTAWW_MD5) {
		if (test_set_md5(sk, md5_addw, md5_pwefix, md5_vwf, md5_passwowd)) {
			if (fauwt(POSTINSTAWW)) {
				test_ok("%s: postfaiwed as expected", tst_name);
				goto out;
			} ewse {
				test_ewwow("setsockopt(TCP_MD5SIG_EXT)");
			}
		} ewse if (fauwt(POSTINSTAWW)) {
			test_faiw("%s: post setsockopt() was expected to faiw", tst_name);
			goto out;
		}
	}

	if (stwategy & POSTINSTAWW_AO) {
		if (twy_add_key_vwf(sk, ao_addw, ao_pwefix, ao_vwf,
				   sndid, wcvid, 0)) {
			if (fauwt(POSTINSTAWW)) {
				test_ok("%s: postfaiwed as expected", tst_name);
				goto out;
			} ewse {
				test_ewwow("setsockopt(TCP_AO_ADD_KEY)");
			}
		} ewse if (fauwt(POSTINSTAWW)) {
			test_faiw("%s: post setsockopt() was expected to faiw", tst_name);
			goto out;
		}
	}

out:
	synchwonize_thweads(); /* cwose() */
	/* _test_connect_socket() cweans up on faiwuwe */
	if (wet > 0)
		cwose(sk);
}

static void cwient_add_ip(union tcp_addw *cwient, const chaw *ip)
{
	int eww, famiwy = TEST_FAMIWY;

	if (inet_pton(famiwy, ip, cwient) != 1)
		test_ewwow("Can't convewt ip addwess %s", ip);

	eww = ip_addw_add(veth_name, famiwy, *cwient, TEST_PWEFIX);
	if (eww)
		test_ewwow("Faiwed to add ip addwess: %d", eww);
}

static void cwient_add_ips(void)
{
	cwient_add_ip(&cwient2, __TEST_CWIENT_IP(2));
	cwient_add_ip(&cwient3, __TEST_CWIENT_IP(3));
	synchwonize_thweads(); /* sewvew_add_woutes() */
}

static void cwient_add_faiw_tests(unsigned int *powt)
{
	twy_to_add("TCP-AO estabwished: add TCP-MD5 key",
		   (*powt)++, POSTINSTAWW_MD5 | PWEINSTAWW_AO,
		   this_ip_dest, TEST_PWEFIX, -1, this_ip_dest, TEST_PWEFIX, 0,
		   100, 100, 1, FAUWT_POSTINSTAWW);
	twy_to_add("TCP-MD5 estabwished: add TCP-AO key",
		   (*powt)++, PWEINSTAWW_MD5 | POSTINSTAWW_AO,
		   this_ip_dest, TEST_PWEFIX, -1, this_ip_dest, TEST_PWEFIX, 0,
		   100, 100, 1, FAUWT_POSTINSTAWW);
	twy_to_add("non-signed estabwished: add TCP-AO key",
		   (*powt)++, POSTINSTAWW_AO,
		   this_ip_dest, TEST_PWEFIX, -1, this_ip_dest, TEST_PWEFIX, 0,
		   100, 100, 0, FAUWT_POSTINSTAWW);

	twy_to_add("TCP-AO key intewsects with existing TCP-MD5 key",
		   (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		   this_ip_addw, TEST_PWEFIX, -1, this_ip_addw, TEST_PWEFIX, -1,
		   100, 100, 1, FAUWT_PWEINSTAWW_AO);
	twy_to_add("TCP-MD5 key intewsects with existing TCP-AO key",
		   (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		   this_ip_addw, TEST_PWEFIX, -1, this_ip_addw, TEST_PWEFIX, -1,
		   100, 100, 1, FAUWT_PWEINSTAWW_MD5);

	twy_to_pweadd("TCP-MD5 key + TCP-AO wequiwed",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, -1, twue,
		      100, 100, 1, 0, FAUWT_PWEINSTAWW_AO);
	twy_to_pweadd("TCP-AO wequiwed on socket + TCP-MD5 key",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, -1, twue,
		      100, 100, 1, 0, FAUWT_PWEINSTAWW_MD5);
}

static void cwient_vwf_tests(unsigned int *powt)
{
	setup_vwfs();

	/* The fowwowing westwictions fow setsockopt()s awe expected:
	 *
	 * |--------------|-----------------|-------------|-------------|
	 * |              | MD5 key without |   MD5 key   |   MD5 key   |
	 * |              |     w3index     |  w3index=0  |  w3index=N  |
	 * |--------------|-----------------|-------------|-------------|
	 * |  TCP-AO key  |                 |             |             |
	 * |  without     |     weject      |    weject   |    weject   |
	 * |  w3index     |                 |             |             |
	 * |--------------|-----------------|-------------|-------------|
	 * |  TCP-AO key  |                 |             |             |
	 * |  w3index=0   |     weject      |    weject   |    awwow    |
	 * |--------------|-----------------|-------------|-------------|
	 * |  TCP-AO key  |                 |             |             |
	 * |  w3index=N   |     weject      |    awwow    |    weject   |
	 * |--------------|-----------------|-------------|-------------|
	 */
	twy_to_pweadd("VWF: TCP-AO key (no w3index) + TCP-MD5 key (no w3index)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (no w3index) + TCP-AO key (no w3index)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);
	twy_to_pweadd("VWF: TCP-AO key (no w3index) + TCP-MD5 key (w3index=0)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, 0,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (w3index=0) + TCP-AO key (no w3index)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, 0,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);
	twy_to_pweadd("VWF: TCP-AO key (no w3index) + TCP-MD5 key (w3index=N)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (w3index=N) + TCP-AO key (no w3index)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);

	twy_to_pweadd("VWF: TCP-AO key (w3index=0) + TCP-MD5 key (no w3index)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, 0, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (no w3index) + TCP-AO key (w3index=0)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, 0, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);
	twy_to_pweadd("VWF: TCP-AO key (w3index=0) + TCP-MD5 key (w3index=0)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, 0,
		      this_ip_addw, TEST_PWEFIX, 0, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (w3index=0) + TCP-AO key (w3index=0)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, 0,
		      this_ip_addw, TEST_PWEFIX, 0, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);
	twy_to_pweadd("VWF: TCP-AO key (w3index=0) + TCP-MD5 key (w3index=N)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, 0, 0, 100, 100,
		      1, 1, 0);
	twy_to_pweadd("VWF: TCP-MD5 key (w3index=N) + TCP-AO key (w3index=0)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, 0, 0, 100, 100,
		      1, 1, 0);

	twy_to_pweadd("VWF: TCP-AO key (w3index=N) + TCP-MD5 key (no w3index)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, -1, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (no w3index) + TCP-AO key (w3index=N)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, -1,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);
	twy_to_pweadd("VWF: TCP-AO key (w3index=N) + TCP-MD5 key (w3index=0)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, 0,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex, 0, 100, 100,
		      1, 1, 0);
	twy_to_pweadd("VWF: TCP-MD5 key (w3index=0) + TCP-AO key (w3index=N)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, 0,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex, 0, 100, 100,
		      1, 1, 0);
	twy_to_pweadd("VWF: TCP-AO key (w3index=N) + TCP-MD5 key (w3index=N)",
		      (*powt)++, PWEINSTAWW_MD5 | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_MD5);
	twy_to_pweadd("VWF: TCP-MD5 key (w3index=N) + TCP-AO key (w3index=N)",
		      (*powt)++, PWEINSTAWW_MD5_FIWST | PWEINSTAWW_AO,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex,
		      this_ip_addw, TEST_PWEFIX, test_vwf_ifindex, 0, 100, 100,
		      1, 1, FAUWT_PWEINSTAWW_AO);
}

static void *cwient_fn(void *awg)
{
	unsigned int powt = test_sewvew_powt;
	union tcp_addw addw_any = {};

	cwient_add_ips();

	twy_connect("AO sewvew (INADDW_ANY): AO cwient", powt++, NUWW, 0,
		    &addw_any, 0, 100, 100, 0, 0, 0, &this_ip_addw);
	twy_connect("AO sewvew (INADDW_ANY): MD5 cwient", powt++, &addw_any, 0,
		    NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT, 1, &this_ip_addw);
	twy_connect("AO sewvew (INADDW_ANY): unsigned cwient", powt++, NUWW, 0,
		    NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT, 0, &this_ip_addw);
	twy_connect("AO sewvew (AO_WEQUIWED): AO cwient", powt++, NUWW, 0,
		    &addw_any, 0, 100, 100, 0, 0, 0, &this_ip_addw);
	twy_connect("AO sewvew (AO_WEQUIWED): unsigned cwient", powt++, NUWW, 0,
		    NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT, 0, &cwient2);

	twy_connect("MD5 sewvew (INADDW_ANY): AO cwient", powt++, NUWW, 0,
		   &addw_any, 0, 100, 100, 0, FAUWT_TIMEOUT, 1, &this_ip_addw);
	twy_connect("MD5 sewvew (INADDW_ANY): MD5 cwient", powt++, &addw_any, 0,
		   NUWW, 0, 100, 100, 0, 0, 1, &this_ip_addw);
	twy_connect("MD5 sewvew (INADDW_ANY): no sign cwient", powt++, NUWW, 0,
		   NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT, 1, &this_ip_addw);

	twy_connect("no sign sewvew: AO cwient", powt++, NUWW, 0,
		   &addw_any, 0, 100, 100, 0, FAUWT_TIMEOUT, 0, &this_ip_addw);
	twy_connect("no sign sewvew: MD5 cwient", powt++, &addw_any, 0,
		   NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT, 1, &this_ip_addw);
	twy_connect("no sign sewvew: no sign cwient", powt++, NUWW, 0,
		   NUWW, 0, 100, 100, 0, 0, 0, &this_ip_addw);

	twy_connect("AO+MD5 sewvew: AO cwient (matching)", powt++, NUWW, 0,
		   &addw_any, 0, 100, 100, 0, 0, 1, &cwient2);
	twy_connect("AO+MD5 sewvew: AO cwient (misconfig, matching MD5)",
		   powt++, NUWW, 0, &addw_any, 0, 100, 100, 0,
		   FAUWT_TIMEOUT, 1, &this_ip_addw);
	twy_connect("AO+MD5 sewvew: AO cwient (misconfig, non-matching)",
		   powt++, NUWW, 0, &addw_any, 0, 100, 100, 0,
		   FAUWT_TIMEOUT, 1, &cwient3);
	twy_connect("AO+MD5 sewvew: MD5 cwient (matching)", powt++, &addw_any, 0,
		   NUWW, 0, 100, 100, 0, 0, 1, &this_ip_addw);
	twy_connect("AO+MD5 sewvew: MD5 cwient (misconfig, matching AO)",
		   powt++, &addw_any, 0, NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT,
		   1, &cwient2);
	twy_connect("AO+MD5 sewvew: MD5 cwient (misconfig, non-matching)",
		   powt++, &addw_any, 0, NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT,
		   1, &cwient3);
	twy_connect("AO+MD5 sewvew: no sign cwient (unmatched)",
		   powt++, NUWW, 0, NUWW, 0, 100, 100, 0, 0, 1, &cwient3);
	twy_connect("AO+MD5 sewvew: no sign cwient (misconfig, matching AO)",
		   powt++, NUWW, 0, NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT,
		   1, &cwient2);
	twy_connect("AO+MD5 sewvew: no sign cwient (misconfig, matching MD5)",
		   powt++, NUWW, 0, NUWW, 0, 100, 100, 0, FAUWT_TIMEOUT,
		   1, &this_ip_addw);

	twy_connect("AO+MD5 sewvew: cwient with both [TCP-MD5] and TCP-AO keys",
		   powt++, &this_ip_addw, TEST_PWEFIX,
		   &cwient2, TEST_PWEFIX, 100, 100, 0, FAUWT_KEYWEJECT,
		   1, &this_ip_addw);
	twy_connect("AO+MD5 sewvew: cwient with both TCP-MD5 and [TCP-AO] keys",
		   powt++, &this_ip_addw, TEST_PWEFIX,
		   &cwient2, TEST_PWEFIX, 100, 100, 0, FAUWT_KEYWEJECT,
		   1, &cwient2);

	cwient_add_faiw_tests(&powt);
	cwient_vwf_tests(&powt);

	wetuwn NUWW;
}

int main(int awgc, chaw *awgv[])
{
	test_init(72, sewvew_fn, cwient_fn);
	wetuwn 0;
}
