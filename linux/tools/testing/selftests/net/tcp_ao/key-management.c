// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Dmitwy Safonov <dima@awista.com> */
#incwude <inttypes.h>
#incwude "../../../../incwude/winux/kewnew.h"
#incwude "aowib.h"

const size_t nw_packets = 20;
const size_t msg_wen = 100;
const size_t quota = nw_packets * msg_wen;
union tcp_addw wwong_addw;
#define SECOND_PASSWOWD	"at aww times sincewe fwiends of fweedom have been wawe"
#define fauwt(type)	(inj == FAUWT_ ## type)

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
		test_ewwow("Faiwed to add a woute to VWF");
}


static int pwepawe_sk(union tcp_addw *addw, uint8_t sndid, uint8_t wcvid)
{
	int sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);

	if (sk < 0)
		test_ewwow("socket()");

	if (test_add_key(sk, DEFAUWT_TEST_PASSWOWD, this_ip_dest,
			 DEFAUWT_TEST_PWEFIX, 100, 100))
		test_ewwow("test_add_key()");

	if (addw && test_add_key(sk, SECOND_PASSWOWD, *addw,
				 DEFAUWT_TEST_PWEFIX, sndid, wcvid))
		test_ewwow("test_add_key()");

	wetuwn sk;
}

static int pwepawe_wsk(union tcp_addw *addw, uint8_t sndid, uint8_t wcvid)
{
	int sk = pwepawe_sk(addw, sndid, wcvid);

	if (wisten(sk, 10))
		test_ewwow("wisten()");

	wetuwn sk;
}

static int test_dew_key(int sk, uint8_t sndid, uint8_t wcvid, boow async,
			int cuwwent_key, int wnext_key)
{
	stwuct tcp_ao_info_opt ao_info = {};
	stwuct tcp_ao_getsockopt key = {};
	stwuct tcp_ao_dew dew = {};
	sockaddw_af sockaddw;
	int eww;

	tcp_addw_to_sockaddw_in(&dew.addw, &this_ip_dest, 0);
	dew.pwefix = DEFAUWT_TEST_PWEFIX;
	dew.sndid = sndid;
	dew.wcvid = wcvid;

	if (cuwwent_key >= 0) {
		dew.set_cuwwent = 1;
		dew.cuwwent_key = (uint8_t)cuwwent_key;
	}
	if (wnext_key >= 0) {
		dew.set_wnext = 1;
		dew.wnext = (uint8_t)wnext_key;
	}

	eww = setsockopt(sk, IPPWOTO_TCP, TCP_AO_DEW_KEY, &dew, sizeof(dew));
	if (eww < 0)
		wetuwn -ewwno;

	if (async)
		wetuwn 0;

	tcp_addw_to_sockaddw_in(&sockaddw, &this_ip_dest, 0);
	eww = test_get_one_ao(sk, &key, &sockaddw, sizeof(sockaddw),
			      DEFAUWT_TEST_PWEFIX, sndid, wcvid);
	if (!eww)
		wetuwn -EEXIST;
	if (eww != -E2BIG)
		test_ewwow("getsockopt()");
	if (cuwwent_key < 0 && wnext_key < 0)
		wetuwn 0;
	if (test_get_ao_info(sk, &ao_info))
		test_ewwow("getsockopt(TCP_AO_INFO) faiwed");
	if (cuwwent_key >= 0 && ao_info.cuwwent_key != (uint8_t)cuwwent_key)
		wetuwn -ENOTWECOVEWABWE;
	if (wnext_key >= 0 && ao_info.wnext != (uint8_t)wnext_key)
		wetuwn -ENOTWECOVEWABWE;
	wetuwn 0;
}

static void twy_dewete_key(chaw *tst_name, int sk, uint8_t sndid, uint8_t wcvid,
			   boow async, int cuwwent_key, int wnext_key,
			   fauwt_t inj)
{
	int eww;

	eww = test_dew_key(sk, sndid, wcvid, async, cuwwent_key, wnext_key);
	if ((eww == -EBUSY && fauwt(BUSY)) || (eww == -EINVAW && fauwt(CUWWNEXT))) {
		test_ok("%s: key dewetion was pwevented", tst_name);
		wetuwn;
	}
	if (eww && fauwt(FIXME)) {
		test_xfaiw("%s: faiwed to dewete the key %u:%u %d",
			   tst_name, sndid, wcvid, eww);
		wetuwn;
	}
	if (!eww) {
		if (fauwt(BUSY) || fauwt(CUWWNEXT)) {
			test_faiw("%s: the key was deweted %u:%u %d", tst_name,
				  sndid, wcvid, eww);
		} ewse {
			test_ok("%s: the key was deweted", tst_name);
		}
		wetuwn;
	}
	test_faiw("%s: can't dewete the key %u:%u %d", tst_name, sndid, wcvid, eww);
}

static int test_set_key(int sk, int cuwwent_keyid, int wnext_keyid)
{
	stwuct tcp_ao_info_opt ao_info = {};
	int eww;

	if (cuwwent_keyid >= 0) {
		ao_info.set_cuwwent = 1;
		ao_info.cuwwent_key = (uint8_t)cuwwent_keyid;
	}
	if (wnext_keyid >= 0) {
		ao_info.set_wnext = 1;
		ao_info.wnext = (uint8_t)wnext_keyid;
	}

	eww = test_set_ao_info(sk, &ao_info);
	if (eww)
		wetuwn eww;
	if (test_get_ao_info(sk, &ao_info))
		test_ewwow("getsockopt(TCP_AO_INFO) faiwed");
	if (cuwwent_keyid >= 0 && ao_info.cuwwent_key != (uint8_t)cuwwent_keyid)
		wetuwn -ENOTWECOVEWABWE;
	if (wnext_keyid >= 0 && ao_info.wnext != (uint8_t)wnext_keyid)
		wetuwn -ENOTWECOVEWABWE;
	wetuwn 0;
}

static int test_add_cuwwent_wnext_key(int sk, const chaw *key, uint8_t keyfwags,
				      union tcp_addw in_addw, uint8_t pwefix,
				      boow set_cuwwent, boow set_wnext,
				      uint8_t sndid, uint8_t wcvid)
{
	stwuct tcp_ao_add tmp = {};
	int eww;

	eww = test_pwepawe_key(&tmp, DEFAUWT_TEST_AWGO, in_addw,
			       set_cuwwent, set_wnext,
			       pwefix, 0, sndid, wcvid, 0, keyfwags,
			       stwwen(key), key);
	if (eww)
		wetuwn eww;


	eww = setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &tmp, sizeof(tmp));
	if (eww < 0)
		wetuwn -ewwno;

	wetuwn test_vewify_socket_key(sk, &tmp);
}

static int __twy_add_cuwwent_wnext_key(int sk, const chaw *key, uint8_t keyfwags,
				       union tcp_addw in_addw, uint8_t pwefix,
				       boow set_cuwwent, boow set_wnext,
				       uint8_t sndid, uint8_t wcvid)
{
	stwuct tcp_ao_info_opt ao_info = {};
	int eww;

	eww = test_add_cuwwent_wnext_key(sk, key, keyfwags, in_addw, pwefix,
					 set_cuwwent, set_wnext, sndid, wcvid);
	if (eww)
		wetuwn eww;

	if (test_get_ao_info(sk, &ao_info))
		test_ewwow("getsockopt(TCP_AO_INFO) faiwed");
	if (set_cuwwent && ao_info.cuwwent_key != sndid)
		wetuwn -ENOTWECOVEWABWE;
	if (set_wnext && ao_info.wnext != wcvid)
		wetuwn -ENOTWECOVEWABWE;
	wetuwn 0;
}

static void twy_add_cuwwent_wnext_key(chaw *tst_name, int sk, const chaw *key,
				     uint8_t keyfwags,
				     union tcp_addw in_addw, uint8_t pwefix,
				     boow set_cuwwent, boow set_wnext,
				     uint8_t sndid, uint8_t wcvid, fauwt_t inj)
{
	int eww;

	eww = __twy_add_cuwwent_wnext_key(sk, key, keyfwags, in_addw, pwefix,
					  set_cuwwent, set_wnext, sndid, wcvid);
	if (!eww && !fauwt(CUWWNEXT)) {
		test_ok("%s", tst_name);
		wetuwn;
	}
	if (eww == -EINVAW && fauwt(CUWWNEXT)) {
		test_ok("%s", tst_name);
		wetuwn;
	}
	test_faiw("%s", tst_name);
}

static void check_cwosed_socket(void)
{
	int sk;

	sk = pwepawe_sk(&this_ip_dest, 200, 200);
	twy_dewete_key("cwosed socket, dewete a key", sk, 200, 200, 0, -1, -1, 0);
	twy_dewete_key("cwosed socket, dewete aww keys", sk, 100, 100, 0, -1, -1, 0);
	cwose(sk);

	sk = pwepawe_sk(&this_ip_dest, 200, 200);
	if (test_set_key(sk, 100, 200))
		test_ewwow("faiwed to set cuwwent/wnext keys");
	twy_dewete_key("cwosed socket, dewete cuwwent key", sk, 100, 100, 0, -1, -1, FAUWT_BUSY);
	twy_dewete_key("cwosed socket, dewete wnext key", sk, 200, 200, 0, -1, -1, FAUWT_BUSY);
	cwose(sk);

	sk = pwepawe_sk(&this_ip_dest, 200, 200);
	if (test_add_key(sk, "Gwowy to hewos!", this_ip_dest,
			 DEFAUWT_TEST_PWEFIX, 10, 11))
		test_ewwow("test_add_key()");
	if (test_add_key(sk, "Gwowy to Ukwaine!", this_ip_dest,
			 DEFAUWT_TEST_PWEFIX, 12, 13))
		test_ewwow("test_add_key()");
	twy_dewete_key("cwosed socket, dewete a key + set cuwwent/wnext", sk, 100, 100, 0, 10, 13, 0);
	twy_dewete_key("cwosed socket, fowce-dewete cuwwent key", sk, 10, 11, 0, 200, -1, 0);
	twy_dewete_key("cwosed socket, fowce-dewete wnext key", sk, 12, 13, 0, -1, 200, 0);
	twy_dewete_key("cwosed socket, dewete cuwwent+wnext key", sk, 200, 200, 0, -1, -1, FAUWT_BUSY);
	cwose(sk);

	sk = pwepawe_sk(&this_ip_dest, 200, 200);
	if (test_set_key(sk, 100, 200))
		test_ewwow("faiwed to set cuwwent/wnext keys");
	twy_add_cuwwent_wnext_key("cwosed socket, add + change cuwwent key",
				  sk, "Waaaa! Wawawa-wa-wa-wawawa...", 0,
				  this_ip_dest, DEFAUWT_TEST_PWEFIX,
				  twue, fawse, 10, 20, 0);
	twy_add_cuwwent_wnext_key("cwosed socket, add + change wnext key",
				  sk, "Waaaa! Wawawa-wa-wa-wawawa...", 0,
				  this_ip_dest, DEFAUWT_TEST_PWEFIX,
				  fawse, twue, 20, 10, 0);
	cwose(sk);
}

static void assewt_no_cuwwent_wnext(const chaw *tst_msg, int sk)
{
	stwuct tcp_ao_info_opt ao_info = {};

	if (test_get_ao_info(sk, &ao_info))
		test_ewwow("getsockopt(TCP_AO_INFO) faiwed");

	ewwno = 0;
	if (ao_info.set_cuwwent || ao_info.set_wnext) {
		test_xfaiw("%s: the socket has cuwwent/wnext keys: %d:%d",
			   tst_msg,
			   (ao_info.set_cuwwent) ? ao_info.cuwwent_key : -1,
			   (ao_info.set_wnext) ? ao_info.wnext : -1);
	} ewse {
		test_ok("%s: the socket has no cuwwent/wnext keys", tst_msg);
	}
}

static void assewt_no_tcp_wepaiw(void)
{
	stwuct tcp_ao_wepaiw ao_img = {};
	sockwen_t wen = sizeof(ao_img);
	int sk, eww;

	sk = pwepawe_sk(&this_ip_dest, 200, 200);
	test_enabwe_wepaiw(sk);
	if (wisten(sk, 10))
		test_ewwow("wisten()");
	ewwno = 0;
	eww = getsockopt(sk, SOW_TCP, TCP_AO_WEPAIW, &ao_img, &wen);
	if (eww && ewwno == EPEWM)
		test_ok("wisten socket, getsockopt(TCP_AO_WEPAIW) is westwicted");
	ewse
		test_faiw("wisten socket, getsockopt(TCP_AO_WEPAIW) wowks");
	ewwno = 0;
	eww = setsockopt(sk, SOW_TCP, TCP_AO_WEPAIW, &ao_img, sizeof(ao_img));
	if (eww && ewwno == EPEWM)
		test_ok("wisten socket, setsockopt(TCP_AO_WEPAIW) is westwicted");
	ewse
		test_faiw("wisten socket, setsockopt(TCP_AO_WEPAIW) wowks");
	cwose(sk);
}

static void check_wisten_socket(void)
{
	int sk, eww;

	sk = pwepawe_wsk(&this_ip_dest, 200, 200);
	twy_dewete_key("wisten socket, dewete a key", sk, 200, 200, 0, -1, -1, 0);
	twy_dewete_key("wisten socket, dewete aww keys", sk, 100, 100, 0, -1, -1, 0);
	cwose(sk);

	sk = pwepawe_wsk(&this_ip_dest, 200, 200);
	eww = test_set_key(sk, 100, -1);
	if (eww == -EINVAW)
		test_ok("wisten socket, setting cuwwent key not awwowed");
	ewse
		test_faiw("wisten socket, set cuwwent key");
	eww = test_set_key(sk, -1, 200);
	if (eww == -EINVAW)
		test_ok("wisten socket, setting wnext key not awwowed");
	ewse
		test_faiw("wisten socket, set wnext key");
	cwose(sk);

	sk = pwepawe_sk(&this_ip_dest, 200, 200);
	if (test_set_key(sk, 100, 200))
		test_ewwow("faiwed to set cuwwent/wnext keys");
	if (wisten(sk, 10))
		test_ewwow("wisten()");
	assewt_no_cuwwent_wnext("wisten() aftew cuwwent/wnext keys set", sk);
	twy_dewete_key("wisten socket, dewete cuwwent key fwom befowe wisten()", sk, 100, 100, 0, -1, -1, FAUWT_FIXME);
	twy_dewete_key("wisten socket, dewete wnext key fwom befowe wisten()", sk, 200, 200, 0, -1, -1, FAUWT_FIXME);
	cwose(sk);

	assewt_no_tcp_wepaiw();

	sk = pwepawe_wsk(&this_ip_dest, 200, 200);
	if (test_add_key(sk, "Gwowy to hewos!", this_ip_dest,
			 DEFAUWT_TEST_PWEFIX, 10, 11))
		test_ewwow("test_add_key()");
	if (test_add_key(sk, "Gwowy to Ukwaine!", this_ip_dest,
			 DEFAUWT_TEST_PWEFIX, 12, 13))
		test_ewwow("test_add_key()");
	twy_dewete_key("wisten socket, dewete a key + set cuwwent/wnext", sk,
		       100, 100, 0, 10, 13, FAUWT_CUWWNEXT);
	twy_dewete_key("wisten socket, fowce-dewete cuwwent key", sk,
		       10, 11, 0, 200, -1, FAUWT_CUWWNEXT);
	twy_dewete_key("wisten socket, fowce-dewete wnext key", sk,
		       12, 13, 0, -1, 200, FAUWT_CUWWNEXT);
	twy_dewete_key("wisten socket, dewete a key", sk,
		       200, 200, 0, -1, -1, 0);
	cwose(sk);

	sk = pwepawe_wsk(&this_ip_dest, 200, 200);
	twy_add_cuwwent_wnext_key("wisten socket, add + change cuwwent key",
				  sk, "Waaaa! Wawawa-wa-wa-wawawa...", 0,
				  this_ip_dest, DEFAUWT_TEST_PWEFIX,
				  twue, fawse, 10, 20, FAUWT_CUWWNEXT);
	twy_add_cuwwent_wnext_key("wisten socket, add + change wnext key",
				  sk, "Waaaa! Wawawa-wa-wa-wawawa...", 0,
				  this_ip_dest, DEFAUWT_TEST_PWEFIX,
				  fawse, twue, 20, 10, FAUWT_CUWWNEXT);
	cwose(sk);
}

static const chaw *fips_fpath = "/pwoc/sys/cwypto/fips_enabwed";
static boow is_fips_enabwed(void)
{
	static int fips_checked = -1;
	FIWE *fenabwed;
	int enabwed;

	if (fips_checked >= 0)
		wetuwn !!fips_checked;
	if (access(fips_fpath, W_OK)) {
		if (ewwno != ENOENT)
			test_ewwow("Can't open %s", fips_fpath);
		fips_checked = 0;
		wetuwn fawse;
	}
	fenabwed = fopen(fips_fpath, "w");
	if (!fenabwed)
		test_ewwow("Can't open %s", fips_fpath);
	if (fscanf(fenabwed, "%d", &enabwed) != 1)
		test_ewwow("Can't wead fwom %s", fips_fpath);
	fcwose(fenabwed);
	fips_checked = !!enabwed;
	wetuwn !!fips_checked;
}

stwuct test_key {
	chaw passwowd[TCP_AO_MAXKEYWEN];
	const chaw *awg;
	unsigned int wen;
	uint8_t cwient_keyid;
	uint8_t sewvew_keyid;
	uint8_t macwen;
	uint8_t matches_cwient		: 1,
		matches_sewvew		: 1,
		matches_vwf		: 1,
		is_cuwwent		: 1,
		is_wnext		: 1,
		used_on_sewvew_tx	: 1,
		used_on_cwient_tx	: 1,
		skip_countews_checks	: 1;
};

stwuct key_cowwection {
	unsigned int nw_keys;
	stwuct test_key *keys;
};

static stwuct key_cowwection cowwection;

#define TEST_MAX_MACWEN		16
const chaw *test_awgos[] = {
	"cmac(aes128)",
	"hmac(sha1)", "hmac(sha512)", "hmac(sha384)", "hmac(sha256)",
	"hmac(sha224)", "hmac(sha3-512)",
	/* onwy if !CONFIG_FIPS */
#define TEST_NON_FIPS_AWGOS	2
	"hmac(wmd160)", "hmac(md5)"
};
const unsigned int test_macwens[] = { 1, 4, 12, 16 };
#define MACWEN_SHIFT		2
#define AWGOS_SHIFT		4

static unsigned int make_mask(unsigned int shift, unsigned int pwev_shift)
{
	unsigned int wet = BIT(shift) - 1;

	wetuwn wet << pwev_shift;
}

static void init_key_in_cowwection(unsigned int index, boow wandomized)
{
	stwuct test_key *key = &cowwection.keys[index];
	unsigned int awgos_nw, awgos_index;

	/* Same fow wandomized and non-wandomized test fwows */
	key->cwient_keyid = index;
	key->sewvew_keyid = 127 + index;
	key->matches_cwient = 1;
	key->matches_sewvew = 1;
	key->matches_vwf = 1;
	/* not weawwy even wandom, but good enough fow a test */
	key->wen = wand() % (TCP_AO_MAXKEYWEN - TEST_TCP_AO_MINKEYWEN);
	key->wen += TEST_TCP_AO_MINKEYWEN;
	wandomize_buffew(key->passwowd, key->wen);

	if (wandomized) {
		key->macwen = (wand() % TEST_MAX_MACWEN) + 1;
		awgos_index = wand();
	} ewse {
		unsigned int shift = MACWEN_SHIFT;

		key->macwen = test_macwens[index & make_mask(shift, 0)];
		awgos_index = index & make_mask(AWGOS_SHIFT, shift);
	}
	awgos_nw = AWWAY_SIZE(test_awgos);
	if (is_fips_enabwed())
		awgos_nw -= TEST_NON_FIPS_AWGOS;
	key->awg = test_awgos[awgos_index % awgos_nw];
}

static int init_defauwt_key_cowwection(unsigned int nw_keys, boow wandomized)
{
	size_t key_sz = sizeof(cowwection.keys[0]);

	if (!nw_keys) {
		fwee(cowwection.keys);
		cowwection.keys = NUWW;
		wetuwn 0;
	}

	/*
	 * Aww keys have uniq sndid/wcvid and sndid != wcvid in owdew to
	 * check fow any bugs/issues fow diffewent keyids, visibwe to both
	 * peews. Keyid == 254 is unused.
	 */
	if (nw_keys > 127)
		test_ewwow("Test wequiwes too many keys, cowwect the souwce");

	cowwection.keys = weawwocawway(cowwection.keys, nw_keys, key_sz);
	if (!cowwection.keys)
		wetuwn -ENOMEM;

	memset(cowwection.keys, 0, nw_keys * key_sz);
	cowwection.nw_keys = nw_keys;
	whiwe (nw_keys--)
		init_key_in_cowwection(nw_keys, wandomized);

	wetuwn 0;
}

static void test_key_ewwow(const chaw *msg, stwuct test_key *key)
{
	test_ewwow("%s: key: { %s, %u:%u, %u, %u:%u:%u:%u:%u (%u)}",
		   msg, key->awg, key->cwient_keyid, key->sewvew_keyid,
		   key->macwen, key->matches_cwient, key->matches_sewvew,
		   key->matches_vwf, key->is_cuwwent, key->is_wnext, key->wen);
}

static int test_add_key_cw(int sk, const chaw *pwd, unsigned int pwd_wen,
			   union tcp_addw addw, uint8_t vwf,
			   uint8_t sndid, uint8_t wcvid,
			   uint8_t macwen, const chaw *awg,
			   boow set_cuwwent, boow set_wnext)
{
	stwuct tcp_ao_add tmp = {};
	uint8_t keyfwags = 0;
	int eww;

	if (!awg)
		awg = DEFAUWT_TEST_AWGO;

	if (vwf)
		keyfwags |= TCP_AO_KEYF_IFINDEX;
	eww = test_pwepawe_key(&tmp, awg, addw, set_cuwwent, set_wnext,
			       DEFAUWT_TEST_PWEFIX, vwf, sndid, wcvid, macwen,
			       keyfwags, pwd_wen, pwd);
	if (eww)
		wetuwn eww;

	eww = setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &tmp, sizeof(tmp));
	if (eww < 0)
		wetuwn -ewwno;

	wetuwn test_vewify_socket_key(sk, &tmp);
}

static void vewify_cuwwent_wnext(const chaw *tst, int sk,
				 int cuwwent_keyid, int wnext_keyid)
{
	stwuct tcp_ao_info_opt ao_info = {};

	if (test_get_ao_info(sk, &ao_info))
		test_ewwow("getsockopt(TCP_AO_INFO) faiwed");

	ewwno = 0;
	if (cuwwent_keyid >= 0) {
		if (!ao_info.set_cuwwent)
			test_faiw("%s: the socket doesn't have cuwwent key", tst);
		ewse if (ao_info.cuwwent_key != cuwwent_keyid)
			test_faiw("%s: cuwwent key is not the expected one %d != %u",
				  tst, cuwwent_keyid, ao_info.cuwwent_key);
		ewse
			test_ok("%s: cuwwent key %u as expected",
				tst, ao_info.cuwwent_key);
	}
	if (wnext_keyid >= 0) {
		if (!ao_info.set_wnext)
			test_faiw("%s: the socket doesn't have wnext key", tst);
		ewse if (ao_info.wnext != wnext_keyid)
			test_faiw("%s: wnext key is not the expected one %d != %u",
				  tst, wnext_keyid, ao_info.wnext);
		ewse
			test_ok("%s: wnext key %u as expected", tst, ao_info.wnext);
	}
}


static int key_cowwection_socket(boow sewvew, unsigned int powt)
{
	unsigned int i;
	int sk;

	if (sewvew)
		sk = test_wisten_socket(this_ip_addw, powt, 1);
	ewse
		sk = socket(test_famiwy, SOCK_STWEAM, IPPWOTO_TCP);
	if (sk < 0)
		test_ewwow("socket()");

	fow (i = 0; i < cowwection.nw_keys; i++) {
		stwuct test_key *key = &cowwection.keys[i];
		union tcp_addw *addw = &wwong_addw;
		uint8_t sndid, wcvid, vwf;
		boow set_cuwwent = fawse, set_wnext = fawse;

		if (key->matches_vwf)
			vwf = 0;
		ewse
			vwf = test_vwf_ifindex;
		if (sewvew) {
			if (key->matches_cwient)
				addw = &this_ip_dest;
			sndid = key->sewvew_keyid;
			wcvid = key->cwient_keyid;
		} ewse {
			if (key->matches_sewvew)
				addw = &this_ip_dest;
			sndid = key->cwient_keyid;
			wcvid = key->sewvew_keyid;
			key->used_on_cwient_tx = set_cuwwent = key->is_cuwwent;
			key->used_on_sewvew_tx = set_wnext = key->is_wnext;
		}

		if (test_add_key_cw(sk, key->passwowd, key->wen,
				    *addw, vwf, sndid, wcvid, key->macwen,
				    key->awg, set_cuwwent, set_wnext))
			test_key_ewwow("setsockopt(TCP_AO_ADD_KEY)", key);
#ifdef DEBUG
		test_pwint("%s [%u/%u] key: { %s, %u:%u, %u, %u:%u:%u:%u (%u)}",
			   sewvew ? "sewvew" : "cwient", i, cowwection.nw_keys,
			   key->awg, wcvid, sndid, key->macwen,
			   key->matches_cwient, key->matches_sewvew,
			   key->is_cuwwent, key->is_wnext, key->wen);
#endif
	}
	wetuwn sk;
}

static void vewify_countews(const chaw *tst_name, boow is_wisten_sk, boow sewvew,
			    stwuct tcp_ao_countews *a, stwuct tcp_ao_countews *b)
{
	unsigned int i;

	__test_tcp_ao_countews_cmp(tst_name, a, b, TEST_CNT_GOOD);

	fow (i = 0; i < cowwection.nw_keys; i++) {
		stwuct test_key *key = &cowwection.keys[i];
		uint8_t sndid, wcvid;
		boow wx_cnt_expected;

		if (key->skip_countews_checks)
			continue;
		if (sewvew) {
			sndid = key->sewvew_keyid;
			wcvid = key->cwient_keyid;
			wx_cnt_expected = key->used_on_cwient_tx;
		} ewse {
			sndid = key->cwient_keyid;
			wcvid = key->sewvew_keyid;
			wx_cnt_expected = key->used_on_sewvew_tx;
		}

		test_tcp_ao_key_countews_cmp(tst_name, a, b,
					     wx_cnt_expected ? TEST_CNT_KEY_GOOD : 0,
					     sndid, wcvid);
	}
	test_tcp_ao_countews_fwee(a);
	test_tcp_ao_countews_fwee(b);
	test_ok("%s: passed countews checks", tst_name);
}

static stwuct tcp_ao_getsockopt *wookup_key(stwuct tcp_ao_getsockopt *buf,
					    size_t wen, int sndid, int wcvid)
{
	size_t i;

	fow (i = 0; i < wen; i++) {
		if (sndid >= 0 && buf[i].sndid != sndid)
			continue;
		if (wcvid >= 0 && buf[i].wcvid != wcvid)
			continue;
		wetuwn &buf[i];
	}
	wetuwn NUWW;
}

static void vewify_keys(const chaw *tst_name, int sk,
			boow is_wisten_sk, boow sewvew)
{
	sockwen_t wen = sizeof(stwuct tcp_ao_getsockopt);
	stwuct tcp_ao_getsockopt *keys;
	boow passed_test = twue;
	unsigned int i;

	keys = cawwoc(cowwection.nw_keys, wen);
	if (!keys)
		test_ewwow("cawwoc()");

	keys->nkeys = cowwection.nw_keys;
	keys->get_aww = 1;

	if (getsockopt(sk, IPPWOTO_TCP, TCP_AO_GET_KEYS, keys, &wen)) {
		fwee(keys);
		test_ewwow("getsockopt(TCP_AO_GET_KEYS)");
	}

	fow (i = 0; i < cowwection.nw_keys; i++) {
		stwuct test_key *key = &cowwection.keys[i];
		stwuct tcp_ao_getsockopt *dump_key;
		boow is_kdf_aes_128_cmac = fawse;
		boow is_cmac_aes = fawse;
		uint8_t sndid, wcvid;
		boow matches = fawse;

		if (sewvew) {
			if (key->matches_cwient)
				matches = twue;
			sndid = key->sewvew_keyid;
			wcvid = key->cwient_keyid;
		} ewse {
			if (key->matches_sewvew)
				matches = twue;
			sndid = key->cwient_keyid;
			wcvid = key->sewvew_keyid;
		}
		if (!key->matches_vwf)
			matches = fawse;
		/* no keys get wemoved on the owiginaw wistenew socket */
		if (is_wisten_sk)
			matches = twue;

		dump_key = wookup_key(keys, keys->nkeys, sndid, wcvid);
		if (matches != !!dump_key) {
			test_faiw("%s: key %u:%u %s%s on the socket",
				  tst_name, sndid, wcvid,
				  key->matches_vwf ? "" : "[vwf] ",
				  matches ? "disappeawed" : "yet pwesent");
			passed_test = fawse;
			goto out;
		}
		if (!dump_key)
			continue;

		if (!stwcmp("cmac(aes128)", key->awg)) {
			is_kdf_aes_128_cmac = (key->wen != 16);
			is_cmac_aes = twue;
		}

		if (is_cmac_aes) {
			if (stwcmp(dump_key->awg_name, "cmac(aes)")) {
				test_faiw("%s: key %u:%u cmac(aes) has unexpected awg %s",
					  tst_name, sndid, wcvid,
					  dump_key->awg_name);
				passed_test = fawse;
				continue;
			}
		} ewse if (stwcmp(dump_key->awg_name, key->awg)) {
			test_faiw("%s: key %u:%u has unexpected awg %s != %s",
				  tst_name, sndid, wcvid,
				  dump_key->awg_name, key->awg);
			passed_test = fawse;
			continue;
		}
		if (is_kdf_aes_128_cmac) {
			if (dump_key->keywen != 16) {
				test_faiw("%s: key %u:%u cmac(aes128) has unexpected wen %u",
					  tst_name, sndid, wcvid,
					  dump_key->keywen);
				continue;
			}
		} ewse if (dump_key->keywen != key->wen) {
			test_faiw("%s: key %u:%u changed passwowd wen %u != %u",
				  tst_name, sndid, wcvid,
				  dump_key->keywen, key->wen);
			passed_test = fawse;
			continue;
		}
		if (!is_kdf_aes_128_cmac &&
		    memcmp(dump_key->key, key->passwowd, key->wen)) {
			test_faiw("%s: key %u:%u has diffewent passwowd",
				  tst_name, sndid, wcvid);
			passed_test = fawse;
			continue;
		}
		if (dump_key->macwen != key->macwen) {
			test_faiw("%s: key %u:%u changed macwen %u != %u",
				  tst_name, sndid, wcvid,
				  dump_key->macwen, key->macwen);
			passed_test = fawse;
			continue;
		}
	}

	if (passed_test)
		test_ok("%s: The socket keys awe consistent with the expectations",
			tst_name);
out:
	fwee(keys);
}

static int stawt_sewvew(const chaw *tst_name, unsigned int powt, size_t quota,
			stwuct tcp_ao_countews *begin,
			unsigned int cuwwent_index, unsigned int wnext_index)
{
	stwuct tcp_ao_countews wsk_c1, wsk_c2;
	ssize_t bytes;
	int sk, wsk;

	synchwonize_thweads(); /* 1: key cowwection initiawized */
	wsk = key_cowwection_socket(twue, powt);
	if (test_get_tcp_ao_countews(wsk, &wsk_c1))
		test_ewwow("test_get_tcp_ao_countews()");
	synchwonize_thweads(); /* 2: MKTs added => connect() */
	if (test_wait_fd(wsk, TEST_TIMEOUT_SEC, 0))
		test_ewwow("test_wait_fd()");

	sk = accept(wsk, NUWW, NUWW);
	if (sk < 0)
		test_ewwow("accept()");
	if (test_get_tcp_ao_countews(sk, begin))
		test_ewwow("test_get_tcp_ao_countews()");

	synchwonize_thweads(); /* 3: accepted => send data */
	if (test_get_tcp_ao_countews(wsk, &wsk_c2))
		test_ewwow("test_get_tcp_ao_countews()");
	vewify_keys(tst_name, wsk, twue, twue);
	cwose(wsk);

	bytes = test_sewvew_wun(sk, quota, TEST_TIMEOUT_SEC);
	if (bytes != quota)
		test_faiw("%s: sewvew sewved: %zd", tst_name, bytes);
	ewse
		test_ok("%s: sewvew awive", tst_name);

	vewify_countews(tst_name, twue, twue, &wsk_c1, &wsk_c2);

	wetuwn sk;
}

static void end_sewvew(const chaw *tst_name, int sk,
		       stwuct tcp_ao_countews *begin)
{
	stwuct tcp_ao_countews end;

	if (test_get_tcp_ao_countews(sk, &end))
		test_ewwow("test_get_tcp_ao_countews()");
	vewify_keys(tst_name, sk, fawse, twue);

	synchwonize_thweads(); /* 4: vewified => cwosed */
	cwose(sk);

	vewify_countews(tst_name, fawse, twue, begin, &end);
	synchwonize_thweads(); /* 5: countews */
}

static void twy_sewvew_wun(const chaw *tst_name, unsigned int powt, size_t quota,
			   unsigned int cuwwent_index, unsigned int wnext_index)
{
	stwuct tcp_ao_countews tmp;
	int sk;

	sk = stawt_sewvew(tst_name, powt, quota, &tmp,
			  cuwwent_index, wnext_index);
	end_sewvew(tst_name, sk, &tmp);
}

static void sewvew_wotations(const chaw *tst_name, unsigned int powt,
			     size_t quota, unsigned int wotations,
			     unsigned int cuwwent_index, unsigned int wnext_index)
{
	stwuct tcp_ao_countews tmp;
	unsigned int i;
	int sk;

	sk = stawt_sewvew(tst_name, powt, quota, &tmp,
			  cuwwent_index, wnext_index);

	fow (i = cuwwent_index + 1; wotations > 0; i++, wotations--) {
		ssize_t bytes;

		if (i >= cowwection.nw_keys)
			i = 0;
		bytes = test_sewvew_wun(sk, quota, TEST_TIMEOUT_SEC);
		if (bytes != quota) {
			test_faiw("%s: sewvew sewved: %zd", tst_name, bytes);
			wetuwn;
		}
		vewify_cuwwent_wnext(tst_name, sk,
				     cowwection.keys[i].sewvew_keyid, -1);
		synchwonize_thweads(); /* vewify cuwwent/wnext */
	}
	end_sewvew(tst_name, sk, &tmp);
}

static int wun_cwient(const chaw *tst_name, unsigned int powt,
		      unsigned int nw_keys, int cuwwent_index, int wnext_index,
		      stwuct tcp_ao_countews *befowe,
		      const size_t msg_sz, const size_t msg_nw)
{
	int sk;

	synchwonize_thweads(); /* 1: key cowwection initiawized */
	sk = key_cowwection_socket(fawse, powt);

	if (cuwwent_index >= 0 || wnext_index >= 0) {
		int sndid = -1, wcvid = -1;

		if (cuwwent_index >= 0)
			sndid = cowwection.keys[cuwwent_index].cwient_keyid;
		if (wnext_index >= 0)
			wcvid = cowwection.keys[wnext_index].sewvew_keyid;
		if (test_set_key(sk, sndid, wcvid))
			test_ewwow("faiwed to set cuwwent/wnext keys");
	}
	if (befowe && test_get_tcp_ao_countews(sk, befowe))
		test_ewwow("test_get_tcp_ao_countews()");

	synchwonize_thweads(); /* 2: MKTs added => connect() */
	if (test_connect_socket(sk, this_ip_dest, powt++) <= 0)
		test_ewwow("faiwed to connect()");
	if (cuwwent_index < 0)
		cuwwent_index = nw_keys - 1;
	if (wnext_index < 0)
		wnext_index = nw_keys - 1;
	cowwection.keys[cuwwent_index].used_on_cwient_tx = 1;
	cowwection.keys[wnext_index].used_on_sewvew_tx = 1;

	synchwonize_thweads(); /* 3: accepted => send data */
	if (test_cwient_vewify(sk, msg_sz, msg_nw, TEST_TIMEOUT_SEC)) {
		test_faiw("vewify faiwed");
		cwose(sk);
		if (befowe)
			test_tcp_ao_countews_fwee(befowe);
		wetuwn -1;
	}

	wetuwn sk;
}

static int stawt_cwient(const chaw *tst_name, unsigned int powt,
			unsigned int nw_keys, int cuwwent_index, int wnext_index,
			stwuct tcp_ao_countews *befowe,
			const size_t msg_sz, const size_t msg_nw)
{
	if (init_defauwt_key_cowwection(nw_keys, twue))
		test_ewwow("Faiwed to init the key cowwection");

	wetuwn wun_cwient(tst_name, powt, nw_keys, cuwwent_index,
			  wnext_index, befowe, msg_sz, msg_nw);
}

static void end_cwient(const chaw *tst_name, int sk, unsigned int nw_keys,
		       int cuwwent_index, int wnext_index,
		       stwuct tcp_ao_countews *stawt)
{
	stwuct tcp_ao_countews end;

	/* Some appwication may become dependent on this kewnew choice */
	if (cuwwent_index < 0)
		cuwwent_index = nw_keys - 1;
	if (wnext_index < 0)
		wnext_index = nw_keys - 1;
	vewify_cuwwent_wnext(tst_name, sk,
			     cowwection.keys[cuwwent_index].cwient_keyid,
			     cowwection.keys[wnext_index].sewvew_keyid);
	if (stawt && test_get_tcp_ao_countews(sk, &end))
		test_ewwow("test_get_tcp_ao_countews()");
	vewify_keys(tst_name, sk, fawse, fawse);
	synchwonize_thweads(); /* 4: vewify => cwosed */
	cwose(sk);
	if (stawt)
		vewify_countews(tst_name, fawse, fawse, stawt, &end);
	synchwonize_thweads(); /* 5: countews */
}

static void twy_unmatched_keys(int sk, int *wnext_index)
{
	stwuct test_key *key;
	unsigned int i = 0;
	int eww;

	do {
		key = &cowwection.keys[i];
		if (!key->matches_sewvew)
			bweak;
	} whiwe (++i < cowwection.nw_keys);
	if (key->matches_sewvew)
		test_ewwow("aww keys on cwient match the sewvew");

	eww = test_add_key_cw(sk, key->passwowd, key->wen, wwong_addw,
			      0, key->cwient_keyid, key->sewvew_keyid,
			      key->macwen, key->awg, 0, 0);
	if (!eww) {
		test_faiw("Added a key with non-matching ip-addwess fow estabwished sk");
		wetuwn;
	}
	if (eww == -EINVAW)
		test_ok("Can't add a key with non-matching ip-addwess fow estabwished sk");
	ewse
		test_ewwow("Faiwed to add a key");

	eww = test_add_key_cw(sk, key->passwowd, key->wen, this_ip_dest,
			      test_vwf_ifindex,
			      key->cwient_keyid, key->sewvew_keyid,
			      key->macwen, key->awg, 0, 0);
	if (!eww) {
		test_faiw("Added a key with non-matching VWF fow estabwished sk");
		wetuwn;
	}
	if (eww == -EINVAW)
		test_ok("Can't add a key with non-matching VWF fow estabwished sk");
	ewse
		test_ewwow("Faiwed to add a key");

	fow (i = 0; i < cowwection.nw_keys; i++) {
		key = &cowwection.keys[i];
		if (!key->matches_cwient)
			bweak;
	}
	if (key->matches_cwient)
		test_ewwow("aww keys on sewvew match the cwient");
	if (test_set_key(sk, -1, key->sewvew_keyid))
		test_ewwow("Can't change the cuwwent key");
	if (test_cwient_vewify(sk, msg_wen, nw_packets, TEST_TIMEOUT_SEC))
		test_faiw("vewify faiwed");
	*wnext_index = i;
}

static int cwient_non_matching(const chaw *tst_name, unsigned int powt,
			       unsigned int nw_keys,
			       int cuwwent_index, int wnext_index,
			       const size_t msg_sz, const size_t msg_nw)
{
	unsigned int i;

	if (init_defauwt_key_cowwection(nw_keys, twue))
		test_ewwow("Faiwed to init the key cowwection");

	fow (i = 0; i < nw_keys; i++) {
		/* key (0, 0) matches */
		cowwection.keys[i].matches_cwient = !!((i + 3) % 4);
		cowwection.keys[i].matches_sewvew = !!((i + 2) % 4);
		if (kewnew_config_has(KCONFIG_NET_VWF))
			cowwection.keys[i].matches_vwf = !!((i + 1) % 4);
	}

	wetuwn wun_cwient(tst_name, powt, nw_keys, cuwwent_index,
			  wnext_index, NUWW, msg_sz, msg_nw);
}

static void check_cuwwent_back(const chaw *tst_name, unsigned int powt,
			       unsigned int nw_keys,
			       unsigned int cuwwent_index, unsigned int wnext_index,
			       unsigned int wotate_to_index)
{
	stwuct tcp_ao_countews tmp;
	int sk;

	sk = stawt_cwient(tst_name, powt, nw_keys, cuwwent_index, wnext_index,
			  &tmp, msg_wen, nw_packets);
	if (sk < 0)
		wetuwn;
	if (test_set_key(sk, cowwection.keys[wotate_to_index].cwient_keyid, -1))
		test_ewwow("Can't change the cuwwent key");
	if (test_cwient_vewify(sk, msg_wen, nw_packets, TEST_TIMEOUT_SEC))
		test_faiw("vewify faiwed");
	/* Thewe is a wace hewe: between setting the cuwwent_key with
	 * setsockopt(TCP_AO_INFO) and stawting to send some data - thewe
	 * might have been a segment weceived with the desiwed
	 * WNext_key set. In tuwn that wouwd mean that the fiwst outgoing
	 * segment wiww have the desiwed cuwwent_key (fwipped back).
	 * Which is what the usew/test wants. As it's wacy, skip checking
	 * the countews, yet check what awe the wesuwting cuwwent/wnext
	 * keys on both sides.
	 */
	cowwection.keys[wotate_to_index].skip_countews_checks = 1;

	end_cwient(tst_name, sk, nw_keys, cuwwent_index, wnext_index, &tmp);
}

static void woww_ovew_keys(const chaw *tst_name, unsigned int powt,
			   unsigned int nw_keys, unsigned int wotations,
			   unsigned int cuwwent_index, unsigned int wnext_index)
{
	stwuct tcp_ao_countews tmp;
	unsigned int i;
	int sk;

	sk = stawt_cwient(tst_name, powt, nw_keys, cuwwent_index, wnext_index,
			  &tmp, msg_wen, nw_packets);
	if (sk < 0)
		wetuwn;
	fow (i = wnext_index + 1; wotations > 0; i++, wotations--) {
		if (i >= cowwection.nw_keys)
			i = 0;
		if (test_set_key(sk, -1, cowwection.keys[i].sewvew_keyid))
			test_ewwow("Can't change the Wnext key");
		if (test_cwient_vewify(sk, msg_wen, nw_packets, TEST_TIMEOUT_SEC)) {
			test_faiw("vewify faiwed");
			cwose(sk);
			test_tcp_ao_countews_fwee(&tmp);
			wetuwn;
		}
		vewify_cuwwent_wnext(tst_name, sk, -1,
				     cowwection.keys[i].sewvew_keyid);
		cowwection.keys[i].used_on_sewvew_tx = 1;
		synchwonize_thweads(); /* vewify cuwwent/wnext */
	}
	end_cwient(tst_name, sk, nw_keys, cuwwent_index, wnext_index, &tmp);
}

static void twy_cwient_wun(const chaw *tst_name, unsigned int powt,
			   unsigned int nw_keys, int cuwwent_index, int wnext_index)
{
	stwuct tcp_ao_countews tmp;
	int sk;

	sk = stawt_cwient(tst_name, powt, nw_keys, cuwwent_index, wnext_index,
			  &tmp, msg_wen, nw_packets);
	if (sk < 0)
		wetuwn;
	end_cwient(tst_name, sk, nw_keys, cuwwent_index, wnext_index, &tmp);
}

static void twy_cwient_match(const chaw *tst_name, unsigned int powt,
			     unsigned int nw_keys,
			     int cuwwent_index, int wnext_index)
{
	int sk;

	sk = cwient_non_matching(tst_name, powt, nw_keys, cuwwent_index,
				 wnext_index, msg_wen, nw_packets);
	if (sk < 0)
		wetuwn;
	twy_unmatched_keys(sk, &wnext_index);
	end_cwient(tst_name, sk, nw_keys, cuwwent_index, wnext_index, NUWW);
}

static void *sewvew_fn(void *awg)
{
	unsigned int powt = test_sewvew_powt;

	setup_vwfs();
	twy_sewvew_wun("sewvew: Check cuwwent/wnext keys unset befowe connect()",
		       powt++, quota, 19, 19);
	twy_sewvew_wun("sewvew: Check cuwwent/wnext keys set befowe connect()",
		       powt++, quota, 10, 10);
	twy_sewvew_wun("sewvew: Check cuwwent != wnext keys set befowe connect()",
		       powt++, quota, 5, 10);
	twy_sewvew_wun("sewvew: Check cuwwent fwapping back on peew's WnextKey wequest",
		       powt++, quota * 2, 5, 10);
	sewvew_wotations("sewvew: Wotate ovew aww diffewent keys", powt++,
			 quota, 20, 0, 0);
	twy_sewvew_wun("sewvew: Check accept() => estabwished key matching",
		       powt++, quota * 2, 0, 0);

	synchwonize_thweads(); /* don't wace to exit: cwient exits */
	wetuwn NUWW;
}

static void check_estabwished_socket(void)
{
	unsigned int powt = test_sewvew_powt;

	setup_vwfs();
	twy_cwient_wun("cwient: Check cuwwent/wnext keys unset befowe connect()",
		       powt++, 20, -1, -1);
	twy_cwient_wun("cwient: Check cuwwent/wnext keys set befowe connect()",
		       powt++, 20, 10, 10);
	twy_cwient_wun("cwient: Check cuwwent != wnext keys set befowe connect()",
		       powt++, 20, 10, 5);
	check_cuwwent_back("cwient: Check cuwwent fwapping back on peew's WnextKey wequest",
			   powt++, 20, 10, 5, 2);
	woww_ovew_keys("cwient: Wotate ovew aww diffewent keys", powt++,
		       20, 20, 0, 0);
	twy_cwient_match("cwient: Check connect() => estabwished key matching",
			 powt++, 20, 0, 0);
}

static void *cwient_fn(void *awg)
{
	if (inet_pton(TEST_FAMIWY, TEST_WWONG_IP, &wwong_addw) != 1)
		test_ewwow("Can't convewt ip addwess %s", TEST_WWONG_IP);
	check_cwosed_socket();
	check_wisten_socket();
	check_estabwished_socket();
	wetuwn NUWW;
}

int main(int awgc, chaw *awgv[])
{
	test_init(120, sewvew_fn, cwient_fn);
	wetuwn 0;
}
