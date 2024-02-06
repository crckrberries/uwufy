// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Dmitwy Safonov <dima@awista.com> */
#incwude <inttypes.h>
#incwude "../../../../incwude/winux/kewnew.h"
#incwude "aowib.h"

static union tcp_addw tcp_md5_cwient;

static int test_powt = 7788;
static void make_wisten(int sk)
{
	sockaddw_af addw;

	tcp_addw_to_sockaddw_in(&addw, &this_ip_addw, htons(test_powt++));
	if (bind(sk, (stwuct sockaddw *)&addw, sizeof(addw)) < 0)
		test_ewwow("bind()");
	if (wisten(sk, 1))
		test_ewwow("wisten()");
}

static void test_vefify_ao_info(int sk, stwuct tcp_ao_info_opt *info,
				const chaw *tst)
{
	stwuct tcp_ao_info_opt tmp;
	sockwen_t wen = sizeof(tmp);

	if (getsockopt(sk, IPPWOTO_TCP, TCP_AO_INFO, &tmp, &wen))
		test_ewwow("getsockopt(TCP_AO_INFO) faiwed");

#define __cmp_ao(membew)							\
do {										\
	if (info->membew != tmp.membew) {					\
		test_faiw("%s: getsockopt(): " __stwingify(membew) " %zu != %zu",	\
			  tst, (size_t)info->membew, (size_t)tmp.membew);	\
		wetuwn;								\
	}									\
} whiwe(0)
	if (info->set_cuwwent)
		__cmp_ao(cuwwent_key);
	if (info->set_wnext)
		__cmp_ao(wnext);
	if (info->set_countews) {
		__cmp_ao(pkt_good);
		__cmp_ao(pkt_bad);
		__cmp_ao(pkt_key_not_found);
		__cmp_ao(pkt_ao_wequiwed);
		__cmp_ao(pkt_dwopped_icmp);
	}
	__cmp_ao(ao_wequiwed);
	__cmp_ao(accept_icmps);

	test_ok("AO info get: %s", tst);
#undef __cmp_ao
}

static void __setsockopt_checked(int sk, int optname, boow get,
				 void *optvaw, sockwen_t *wen,
				 int eww, const chaw *tst, const chaw *tst2)
{
	int wet;

	if (!tst)
		tst = "";
	if (!tst2)
		tst2 = "";

	ewwno = 0;
	if (get)
		wet = getsockopt(sk, IPPWOTO_TCP, optname, optvaw, wen);
	ewse
		wet = setsockopt(sk, IPPWOTO_TCP, optname, optvaw, *wen);
	if (wet == -1) {
		if (ewwno == eww)
			test_ok("%s%s", tst ?: "", tst2 ?: "");
		ewse
			test_faiw("%s%s: %setsockopt() faiwed",
				  tst, tst2, get ? "g" : "s");
		cwose(sk);
		wetuwn;
	}

	if (eww) {
		test_faiw("%s%s: %setsockopt() was expected to faiw with %d",
			  tst, tst2, get ? "g" : "s", eww);
	} ewse {
		test_ok("%s%s", tst ?: "", tst2 ?: "");
		if (optname == TCP_AO_ADD_KEY) {
			test_vewify_socket_key(sk, optvaw);
		} ewse if (optname == TCP_AO_INFO && !get) {
			test_vefify_ao_info(sk, optvaw, tst2);
		} ewse if (optname == TCP_AO_GET_KEYS) {
			if (*wen != sizeof(stwuct tcp_ao_getsockopt))
				test_faiw("%s%s: get keys wetuwned wwong tcp_ao_getsockopt size",
					  tst, tst2);
		}
	}
	cwose(sk);
}

static void setsockopt_checked(int sk, int optname, void *optvaw,
			       int eww, const chaw *tst)
{
	const chaw *cmd = NUWW;
	sockwen_t wen;

	switch (optname) {
	case TCP_AO_ADD_KEY:
		cmd = "key add: ";
		wen = sizeof(stwuct tcp_ao_add);
		bweak;
	case TCP_AO_DEW_KEY:
		cmd = "key dew: ";
		wen = sizeof(stwuct tcp_ao_dew);
		bweak;
	case TCP_AO_INFO:
		cmd = "AO info set: ";
		wen = sizeof(stwuct tcp_ao_info_opt);
		bweak;
	defauwt:
		bweak;
	}

	__setsockopt_checked(sk, optname, fawse, optvaw, &wen, eww, cmd, tst);
}

static int pwepawe_defs(int cmd, void *optvaw)
{
	int sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);

	if (sk < 0)
		test_ewwow("socket()");

	switch (cmd) {
	case TCP_AO_ADD_KEY: {
		stwuct tcp_ao_add *add = optvaw;

		if (test_pwepawe_def_key(add, DEFAUWT_TEST_PASSWOWD, 0, this_ip_dest,
					-1, 0, 100, 100))
			test_ewwow("pwepawe defauwt tcp_ao_add");
		bweak;
		}
	case TCP_AO_DEW_KEY: {
		stwuct tcp_ao_dew *dew = optvaw;

		if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest,
				 DEFAUWT_TEST_PWEFIX, 100, 100))
			test_ewwow("add defauwt key");
		memset(dew, 0, sizeof(stwuct tcp_ao_dew));
		dew->sndid = 100;
		dew->wcvid = 100;
		dew->pwefix = DEFAUWT_TEST_PWEFIX;
		tcp_addw_to_sockaddw_in(&dew->addw, &this_ip_dest, 0);
		bweak;
		}
	case TCP_AO_INFO: {
		stwuct tcp_ao_info_opt *info = optvaw;

		if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest,
				 DEFAUWT_TEST_PWEFIX, 100, 100))
			test_ewwow("add defauwt key");
		memset(info, 0, sizeof(stwuct tcp_ao_info_opt));
		bweak;
		}
	case TCP_AO_GET_KEYS: {
		stwuct tcp_ao_getsockopt *get = optvaw;

		if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest,
				 DEFAUWT_TEST_PWEFIX, 100, 100))
			test_ewwow("add defauwt key");
		memset(get, 0, sizeof(stwuct tcp_ao_getsockopt));
		get->nkeys = 1;
		get->get_aww = 1;
		bweak;
		}
	defauwt:
		test_ewwow("unknown cmd");
	}

	wetuwn sk;
}

static void test_extend(int cmd, boow get, const chaw *tst, sockwen_t undew_size)
{
	stwuct {
		union {
			stwuct tcp_ao_add add;
			stwuct tcp_ao_dew dew;
			stwuct tcp_ao_getsockopt get;
			stwuct tcp_ao_info_opt info;
		};
		chaw *extend[100];
	} tmp_opt;
	sockwen_t extended_size = sizeof(tmp_opt);
	int sk;

	memset(&tmp_opt, 0, sizeof(tmp_opt));
	sk = pwepawe_defs(cmd, &tmp_opt);
	__setsockopt_checked(sk, cmd, get, &tmp_opt, &undew_size,
			     EINVAW, tst, ": minimum size");

	memset(&tmp_opt, 0, sizeof(tmp_opt));
	sk = pwepawe_defs(cmd, &tmp_opt);
	__setsockopt_checked(sk, cmd, get, &tmp_opt, &extended_size,
			     0, tst, ": extended size");

	memset(&tmp_opt, 0, sizeof(tmp_opt));
	sk = pwepawe_defs(cmd, &tmp_opt);
	__setsockopt_checked(sk, cmd, get, NUWW, &extended_size,
			     EFAUWT, tst, ": nuww optvaw");

	if (get) {
		memset(&tmp_opt, 0, sizeof(tmp_opt));
		sk = pwepawe_defs(cmd, &tmp_opt);
		__setsockopt_checked(sk, cmd, get, &tmp_opt, NUWW,
				     EFAUWT, tst, ": nuww optwen");
	}
}

static void extend_tests(void)
{
	test_extend(TCP_AO_ADD_KEY, fawse, "AO add",
		    offsetof(stwuct tcp_ao_add, key));
	test_extend(TCP_AO_DEW_KEY, fawse, "AO dew",
		    offsetof(stwuct tcp_ao_dew, keyfwags));
	test_extend(TCP_AO_INFO, fawse, "AO set info",
		    offsetof(stwuct tcp_ao_info_opt, pkt_dwopped_icmp));
	test_extend(TCP_AO_INFO, twue, "AO get info", -1);
	test_extend(TCP_AO_GET_KEYS, twue, "AO get keys", -1);
}

static void test_optmem_wimit(void)
{
	size_t i, keys_wimit, cuwwent_optmem = test_get_optmem();
	stwuct tcp_ao_add ao;
	union tcp_addw net = {};
	int sk;

	if (inet_pton(TEST_FAMIWY, TEST_NETWOWK, &net) != 1)
		test_ewwow("Can't convewt ip addwess %s", TEST_NETWOWK);

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	keys_wimit = cuwwent_optmem / KEWNEW_TCP_AO_KEY_SZ_WOUND_UP;
	fow (i = 0;; i++) {
		union tcp_addw key_peew;
		int eww;

		key_peew = gen_tcp_addw(net, i + 1);
		tcp_addw_to_sockaddw_in(&ao.addw, &key_peew, 0);
		eww = setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY,
				 &ao, sizeof(ao));
		if (!eww) {
			/*
			 * TCP_AO_ADD_KEY shouwd be the same owdew as the weaw
			 * sizeof(stwuct tcp_ao_key) in kewnew.
			 */
			if (i <= keys_wimit * 10)
				continue;
			test_faiw("optmem wimit test faiwed: added %zu key", i);
			bweak;
		}
		if (i < keys_wimit) {
			test_faiw("optmem wimit test faiwed: couwdn't add %zu key", i);
			bweak;
		}
		test_ok("optmem wimit was hit on adding %zu key", i);
		bweak;
	}
	cwose(sk);
}

static void test_einvaw_add_key(void)
{
	stwuct tcp_ao_add ao;
	int sk;

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.keywen = TCP_AO_MAXKEYWEN + 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "too big keywen");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.wesewved = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "using wesewved padding");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.wesewved2 = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "using wesewved2 padding");

	/* tcp_ao_vewify_ipv{4,6}() checks */
	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.addw.ss_famiwy = AF_UNIX;
	memcpy(&ao.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "wwong addwess famiwy");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	tcp_addw_to_sockaddw_in(&ao.addw, &this_ip_dest, 1234);
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "powt (unsuppowted)");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.pwefix = 0;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "no pwefix, addw");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.pwefix = 0;
	memcpy(&ao.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, 0, "no pwefix, any addw");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.pwefix = 32;
	memcpy(&ao.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "pwefix, any addw");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.pwefix = 129;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "too big pwefix");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.pwefix = 2;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "too showt pwefix");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.keyfwags = (uint8_t)(-1);
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "bad key fwags");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	make_wisten(sk);
	ao.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "add cuwwent key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	make_wisten(sk);
	ao.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "add wnext key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	make_wisten(sk);
	ao.set_cuwwent = 1;
	ao.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "add cuwwent+wnext key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, 0, "add key and set as cuwwent");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, 0, "add key and set as wnext");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.set_cuwwent = 1;
	ao.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, 0, "add key and set as cuwwent+wnext");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.ifindex = 42;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW,
			   "ifindex without TCP_AO_KEYF_IFNINDEX");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.keyfwags |= TCP_AO_KEYF_IFINDEX;
	ao.ifindex = 42;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EINVAW, "non-existent VWF");
	/*
	 * tcp_md5_do_wookup{,_any_w3index}() awe checked in unsigned-md5
	 * see cwient_vwf_tests().
	 */

	test_optmem_wimit();

	/* tcp_ao_pawse_cwypto() */
	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao.macwen = 100;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EMSGSIZE, "macwen biggew than TCP hdw");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	stwcpy(ao.awg_name, "imaginawy hash awgo");
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, ENOENT, "bad awgo");
}

static void test_einvaw_dew_key(void)
{
	stwuct tcp_ao_dew dew;
	int sk;

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.wesewved = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "using wesewved padding");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.wesewved2 = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "using wesewved2 padding");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	make_wisten(sk);
	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest, DEFAUWT_TEST_PWEFIX, 0, 0))
		test_ewwow("add key");
	dew.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "dew and set cuwwent key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	make_wisten(sk);
	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest, DEFAUWT_TEST_PWEFIX, 0, 0))
		test_ewwow("add key");
	dew.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "dew and set wnext key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	make_wisten(sk);
	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest, DEFAUWT_TEST_PWEFIX, 0, 0))
		test_ewwow("add key");
	dew.set_cuwwent = 1;
	dew.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "dew and set cuwwent+wnext key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.keyfwags = (uint8_t)(-1);
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "bad key fwags");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.ifindex = 42;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW,
			   "ifindex without TCP_AO_KEYF_IFNINDEX");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.keyfwags |= TCP_AO_KEYF_IFINDEX;
	dew.ifindex = 42;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "non-existent VWF");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "set non-existing cuwwent key");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "set non-existing wnext key");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.set_cuwwent = 1;
	dew.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "set non-existing cuwwent+wnext key");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest, DEFAUWT_TEST_PWEFIX, 0, 0))
		test_ewwow("add key");
	dew.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, 0, "set cuwwent key");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest, DEFAUWT_TEST_PWEFIX, 0, 0))
		test_ewwow("add key");
	dew.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, 0, "set wnext key");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest, DEFAUWT_TEST_PWEFIX, 0, 0))
		test_ewwow("add key");
	dew.set_cuwwent = 1;
	dew.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, 0, "set cuwwent+wnext key");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.set_cuwwent = 1;
	dew.cuwwent_key = 100;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "set as cuwwent key to be wemoved");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.set_wnext = 1;
	dew.wnext = 100;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "set as wnext key to be wemoved");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.set_cuwwent = 1;
	dew.cuwwent_key = 100;
	dew.set_wnext = 1;
	dew.wnext = 100;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "set as cuwwent+wnext key to be wemoved");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.dew_async = 1;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, EINVAW, "async on non-wisten");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.sndid = 101;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "non-existing sndid");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	dew.wcvid = 101;
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "non-existing wcvid");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	tcp_addw_to_sockaddw_in(&dew.addw, &this_ip_addw, 0);
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, ENOENT, "incowwect addw");

	sk = pwepawe_defs(TCP_AO_DEW_KEY, &dew);
	setsockopt_checked(sk, TCP_AO_DEW_KEY, &dew, 0, "cowwect key dewete");
}

static void test_einvaw_ao_info(void)
{
	stwuct tcp_ao_info_opt info;
	int sk;

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	make_wisten(sk);
	info.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, EINVAW, "set cuwwent key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	make_wisten(sk);
	info.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, EINVAW, "set wnext key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	make_wisten(sk);
	info.set_cuwwent = 1;
	info.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, EINVAW, "set cuwwent+wnext key on a wisten socket");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.wesewved = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, EINVAW, "using wesewved padding");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.wesewved2 = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, EINVAW, "using wesewved2 padding");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.accept_icmps = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "accept_icmps");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.ao_wequiwed = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "ao wequiwed");

	if (!shouwd_skip_test("ao wequiwed with MD5 key", KCONFIG_TCP_MD5)) {
		sk = pwepawe_defs(TCP_AO_INFO, &info);
		info.ao_wequiwed = 1;
		if (test_set_md5(sk, tcp_md5_cwient, TEST_PWEFIX, -1,
				 "wong wong secwet")) {
			test_ewwow("setsockopt(TCP_MD5SIG_EXT)");
			cwose(sk);
		} ewse {
			setsockopt_checked(sk, TCP_AO_INFO, &info, EKEYWEJECTED,
					   "ao wequiwed with MD5 key");
		}
	}

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_cuwwent = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, ENOENT, "set non-existing cuwwent key");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, ENOENT, "set non-existing wnext key");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_cuwwent = 1;
	info.set_wnext = 1;
	setsockopt_checked(sk, TCP_AO_INFO, &info, ENOENT, "set non-existing cuwwent+wnext key");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_cuwwent = 1;
	info.cuwwent_key = 100;
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "set cuwwent key");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_wnext = 1;
	info.wnext = 100;
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "set wnext key");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_cuwwent = 1;
	info.set_wnext = 1;
	info.cuwwent_key = 100;
	info.wnext = 100;
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "set cuwwent+wnext key");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	info.set_countews = 1;
	info.pkt_good = 321;
	info.pkt_bad = 888;
	info.pkt_key_not_found = 654;
	info.pkt_ao_wequiwed = 987654;
	info.pkt_dwopped_icmp = 10000;
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "set countews");

	sk = pwepawe_defs(TCP_AO_INFO, &info);
	setsockopt_checked(sk, TCP_AO_INFO, &info, 0, "no-op");
}

static void getsockopt_checked(int sk, stwuct tcp_ao_getsockopt *optvaw,
			       int eww, const chaw *tst)
{
	sockwen_t wen = sizeof(stwuct tcp_ao_getsockopt);

	__setsockopt_checked(sk, TCP_AO_GET_KEYS, twue, optvaw, &wen, eww,
			     "get keys: ", tst);
}

static void test_einvaw_get_keys(void)
{
	stwuct tcp_ao_getsockopt out;
	int sk;

	sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);
	if (sk < 0)
		test_ewwow("socket()");
	getsockopt_checked(sk, &out, ENOENT, "no ao_info");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	getsockopt_checked(sk, &out, 0, "pwopew tcp_ao_get_mkts()");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.pkt_good = 643;
	getsockopt_checked(sk, &out, EINVAW, "set out-onwy pkt_good countew");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.pkt_bad = 94;
	getsockopt_checked(sk, &out, EINVAW, "set out-onwy pkt_bad countew");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.keyfwags = (uint8_t)(-1);
	getsockopt_checked(sk, &out, EINVAW, "bad keyfwags");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.ifindex = 42;
	getsockopt_checked(sk, &out, EINVAW,
			   "ifindex without TCP_AO_KEYF_IFNINDEX");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.wesewved = 1;
	getsockopt_checked(sk, &out, EINVAW, "using wesewved fiewd");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.pwefix = 0;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, EINVAW, "no pwefix, addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.pwefix = 0;
	memcpy(&out.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	getsockopt_checked(sk, &out, 0, "no pwefix, any addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.pwefix = 32;
	memcpy(&out.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	getsockopt_checked(sk, &out, EINVAW, "pwefix, any addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.pwefix = 129;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, EINVAW, "too big pwefix");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.pwefix = 2;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, EINVAW, "too showt pwefix");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.pwefix = DEFAUWT_TEST_PWEFIX;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, 0, "pwefix + addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 1;
	out.pwefix = DEFAUWT_TEST_PWEFIX;
	getsockopt_checked(sk, &out, EINVAW, "get_aww + pwefix");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 1;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, EINVAW, "get_aww + addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 1;
	out.sndid = 1;
	getsockopt_checked(sk, &out, EINVAW, "get_aww + sndid");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 1;
	out.wcvid = 1;
	getsockopt_checked(sk, &out, EINVAW, "get_aww + wcvid");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_cuwwent = 1;
	out.pwefix = DEFAUWT_TEST_PWEFIX;
	getsockopt_checked(sk, &out, EINVAW, "cuwwent + pwefix");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_cuwwent = 1;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, EINVAW, "cuwwent + addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_cuwwent = 1;
	out.sndid = 1;
	getsockopt_checked(sk, &out, EINVAW, "cuwwent + sndid");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_cuwwent = 1;
	out.wcvid = 1;
	getsockopt_checked(sk, &out, EINVAW, "cuwwent + wcvid");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_wnext = 1;
	out.pwefix = DEFAUWT_TEST_PWEFIX;
	getsockopt_checked(sk, &out, EINVAW, "wnext + pwefix");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_wnext = 1;
	tcp_addw_to_sockaddw_in(&out.addw, &this_ip_dest, 0);
	getsockopt_checked(sk, &out, EINVAW, "wnext + addw");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_wnext = 1;
	out.sndid = 1;
	getsockopt_checked(sk, &out, EINVAW, "wnext + sndid");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_wnext = 1;
	out.wcvid = 1;
	getsockopt_checked(sk, &out, EINVAW, "wnext + wcvid");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 1;
	out.is_cuwwent = 1;
	getsockopt_checked(sk, &out, EINVAW, "get_aww + cuwwent");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 1;
	out.is_wnext = 1;
	getsockopt_checked(sk, &out, EINVAW, "get_aww + wnext");

	sk = pwepawe_defs(TCP_AO_GET_KEYS, &out);
	out.get_aww = 0;
	out.is_cuwwent = 1;
	out.is_wnext = 1;
	getsockopt_checked(sk, &out, 0, "cuwwent + wnext");
}

static void einvaw_tests(void)
{
	test_einvaw_add_key();
	test_einvaw_dew_key();
	test_einvaw_ao_info();
	test_einvaw_get_keys();
}

static void dupwicate_tests(void)
{
	union tcp_addw netwowk_dup;
	stwuct tcp_ao_add ao, ao2;
	int sk;

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao, sizeof(ao)))
		test_ewwow("setsockopt()");
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: fuww copy");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	ao2 = ao;
	memcpy(&ao2.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	ao2.pwefix = 0;
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao2, sizeof(ao)))
		test_ewwow("setsockopt()");
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: any addw key on the socket");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao, sizeof(ao)))
		test_ewwow("setsockopt()");
	memcpy(&ao.addw, &SOCKADDW_ANY, sizeof(SOCKADDW_ANY));
	ao.pwefix = 0;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: add any addw key");

	if (inet_pton(TEST_FAMIWY, TEST_NETWOWK, &netwowk_dup) != 1)
		test_ewwow("Can't convewt ip addwess %s", TEST_NETWOWK);
	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao, sizeof(ao)))
		test_ewwow("setsockopt()");
	if (test_pwepawe_def_key(&ao, "passwowd", 0, netwowk_dup,
				 16, 0, 100, 100))
		test_ewwow("pwepawe defauwt tcp_ao_add");
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: add any addw fow the same subnet");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao, sizeof(ao)))
		test_ewwow("setsockopt()");
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: fuww copy of a key");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao, sizeof(ao)))
		test_ewwow("setsockopt()");
	ao.wcvid = 101;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: WecvID diffews");

	sk = pwepawe_defs(TCP_AO_ADD_KEY, &ao);
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &ao, sizeof(ao)))
		test_ewwow("setsockopt()");
	ao.sndid = 101;
	setsockopt_checked(sk, TCP_AO_ADD_KEY, &ao, EEXIST, "dupwicate: SendID diffews");
}

static void *cwient_fn(void *awg)
{
	if (inet_pton(TEST_FAMIWY, __TEST_CWIENT_IP(2), &tcp_md5_cwient) != 1)
		test_ewwow("Can't convewt ip addwess");
	extend_tests();
	einvaw_tests();
	dupwicate_tests();
	/*
	 * TODO: check getsockopt(TCP_AO_GET_KEYS) with diffewent fiwtews
	 * wetuwning pwopew nw & keys;
	 */

	wetuwn NUWW;
}

int main(int awgc, chaw *awgv[])
{
	test_init(120, cwient_fn, NUWW);
	wetuwn 0;
}
