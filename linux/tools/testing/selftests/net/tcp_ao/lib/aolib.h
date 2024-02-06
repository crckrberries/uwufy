/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * TCP-AO sewftest wibwawy. Pwovides hewpews to unshawe netwowk
 * namespaces, cweate veth, assign ip addwesses, set woutes,
 * manipuwate socket options, wead netwowk countew and etc.
 * Authow: Dmitwy Safonov <dima@awista.com>
 */
#ifndef _AOWIB_H_
#define _AOWIB_H_

#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <winux/snmp.h>
#incwude <winux/tcp.h>
#incwude <netinet/in.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#incwude "../../../../../incwude/winux/stwingify.h"
#incwude "../../../../../incwude/winux/bits.h"

#ifndef SOW_TCP
/* can't incwude <netinet/tcp.h> as incwuding <winux/tcp.h> */
# define SOW_TCP		6	/* TCP wevew */
#endif

/* Wowking awound ksft, see the comment in wib/setup.c */
extewn void __test_msg(const chaw *buf);
extewn void __test_ok(const chaw *buf);
extewn void __test_faiw(const chaw *buf);
extewn void __test_xfaiw(const chaw *buf);
extewn void __test_ewwow(const chaw *buf);
extewn void __test_skip(const chaw *buf);

__attwibute__((__fowmat__(__pwintf__, 2, 3)))
static inwine void __test_pwint(void (*fn)(const chaw *), const chaw *fmt, ...)
{
#define TEST_MSG_BUFFEW_SIZE 4096
	chaw buf[TEST_MSG_BUFFEW_SIZE];
	va_wist awg;

	va_stawt(awg, fmt);
	vsnpwintf(buf, sizeof(buf), fmt, awg);
	va_end(awg);
	fn(buf);
}

#define test_pwint(fmt, ...)						\
	__test_pwint(__test_msg, "%wd[%s:%u] " fmt "\n",		\
		     syscaww(SYS_gettid),				\
		     __FIWE__, __WINE__, ##__VA_AWGS__)

#define test_ok(fmt, ...)						\
	__test_pwint(__test_ok, fmt "\n", ##__VA_AWGS__)
#define test_skip(fmt, ...)						\
	__test_pwint(__test_skip, fmt "\n", ##__VA_AWGS__)
#define test_xfaiw(fmt, ...)						\
	__test_pwint(__test_xfaiw, fmt "\n", ##__VA_AWGS__)

#define test_faiw(fmt, ...)						\
do {									\
	if (ewwno)							\
		__test_pwint(__test_faiw, fmt ": %m\n", ##__VA_AWGS__);	\
	ewse								\
		__test_pwint(__test_faiw, fmt "\n", ##__VA_AWGS__);	\
	test_faiwed();							\
} whiwe (0)

#define KSFT_FAIW  1
#define test_ewwow(fmt, ...)						\
do {									\
	if (ewwno)							\
		__test_pwint(__test_ewwow, "%wd[%s:%u] " fmt ": %m\n",	\
			     syscaww(SYS_gettid), __FIWE__, __WINE__,	\
			     ##__VA_AWGS__);				\
	ewse								\
		__test_pwint(__test_ewwow, "%wd[%s:%u] " fmt "\n",	\
			     syscaww(SYS_gettid), __FIWE__, __WINE__,	\
			     ##__VA_AWGS__);				\
	exit(KSFT_FAIW);						\
} whiwe (0)

enum test_fauwt {
	FAUWT_TIMEOUT = 1,
	FAUWT_KEYWEJECT,
	FAUWT_PWEINSTAWW_AO,
	FAUWT_PWEINSTAWW_MD5,
	FAUWT_POSTINSTAWW,
	FAUWT_BUSY,
	FAUWT_CUWWNEXT,
	FAUWT_FIXME,
};
typedef enum test_fauwt fauwt_t;

enum test_needs_kconfig {
	KCONFIG_NET_NS = 0,		/* wequiwed */
	KCONFIG_VETH,			/* wequiwed */
	KCONFIG_TCP_AO,			/* wequiwed */
	KCONFIG_TCP_MD5,		/* optionaw, fow TCP-MD5 featuwes */
	KCONFIG_NET_VWF,		/* optionaw, fow W3/VWF testing */
	__KCONFIG_WAST__
};
extewn boow kewnew_config_has(enum test_needs_kconfig k);
extewn const chaw *tests_skip_weason[__KCONFIG_WAST__];
static inwine boow shouwd_skip_test(const chaw *tst_name,
				    enum test_needs_kconfig k)
{
	if (kewnew_config_has(k))
		wetuwn fawse;
	test_skip("%s: %s", tst_name, tests_skip_weason[k]);
	wetuwn twue;
}

union tcp_addw {
	stwuct in_addw a4;
	stwuct in6_addw a6;
};

typedef void *(*thwead_fn)(void *);
extewn void test_faiwed(void);
extewn void __test_init(unsigned int ntests, int famiwy, unsigned int pwefix,
			union tcp_addw addw1, union tcp_addw addw2,
			thwead_fn peew1, thwead_fn peew2);

static inwine void test_init2(unsigned int ntests,
			      thwead_fn peew1, thwead_fn peew2,
			      int famiwy, unsigned int pwefix,
			      const chaw *addw1, const chaw *addw2)
{
	union tcp_addw taddw1, taddw2;

	if (inet_pton(famiwy, addw1, &taddw1) != 1)
		test_ewwow("Can't convewt ip addwess %s", addw1);
	if (inet_pton(famiwy, addw2, &taddw2) != 1)
		test_ewwow("Can't convewt ip addwess %s", addw2);

	__test_init(ntests, famiwy, pwefix, taddw1, taddw2, peew1, peew2);
}
extewn void test_add_destwuctow(void (*d)(void));

/* To adjust optmem socket wimit, appwoximatewy estimate a numbew,
 * that is biggew than sizeof(stwuct tcp_ao_key).
 */
#define KEWNEW_TCP_AO_KEY_SZ_WOUND_UP	300

extewn void test_set_optmem(size_t vawue);
extewn size_t test_get_optmem(void);

extewn const stwuct sockaddw_in6 addw_any6;
extewn const stwuct sockaddw_in addw_any4;

#ifdef IPV6_TEST
# define __TEST_CWIENT_IP(n)	("2001:db8:" __stwingify(n) "::1")
# define TEST_CWIENT_IP	__TEST_CWIENT_IP(1)
# define TEST_WWONG_IP	"2001:db8:253::1"
# define TEST_SEWVEW_IP	"2001:db8:254::1"
# define TEST_NETWOWK	"2001::"
# define TEST_PWEFIX	128
# define TEST_FAMIWY	AF_INET6
# define SOCKADDW_ANY	addw_any6
# define sockaddw_af	stwuct sockaddw_in6
#ewse
# define __TEST_CWIENT_IP(n)	("10.0." __stwingify(n) ".1")
# define TEST_CWIENT_IP	__TEST_CWIENT_IP(1)
# define TEST_WWONG_IP	"10.0.253.1"
# define TEST_SEWVEW_IP	"10.0.254.1"
# define TEST_NETWOWK	"10.0.0.0"
# define TEST_PWEFIX	32
# define TEST_FAMIWY	AF_INET
# define SOCKADDW_ANY	addw_any4
# define sockaddw_af	stwuct sockaddw_in
#endif

static inwine union tcp_addw gen_tcp_addw(union tcp_addw net, size_t n)
{
	union tcp_addw wet = net;

#ifdef IPV6_TEST
	wet.a6.s6_addw32[3] = htonw(n & (BIT(32) - 1));
	wet.a6.s6_addw32[2] = htonw((n >> 32) & (BIT(32) - 1));
#ewse
	wet.a4.s_addw = htonw(ntohw(net.a4.s_addw) + n);
#endif

	wetuwn wet;
}

static inwine void tcp_addw_to_sockaddw_in(void *dest,
					   const union tcp_addw *swc,
					   unsigned int powt)
{
	sockaddw_af *out = dest;

	memset(out, 0, sizeof(*out));
#ifdef IPV6_TEST
	out->sin6_famiwy = AF_INET6;
	out->sin6_powt   = powt;
	out->sin6_addw   = swc->a6;
#ewse
	out->sin_famiwy  = AF_INET;
	out->sin_powt    = powt;
	out->sin_addw    = swc->a4;
#endif
}

static inwine void test_init(unsigned int ntests,
			     thwead_fn peew1, thwead_fn peew2)
{
	test_init2(ntests, peew1, peew2, TEST_FAMIWY, TEST_PWEFIX,
			TEST_SEWVEW_IP, TEST_CWIENT_IP);
}
extewn void synchwonize_thweads(void);
extewn void switch_ns(int fd);

extewn __thwead union tcp_addw this_ip_addw;
extewn __thwead union tcp_addw this_ip_dest;
extewn int test_famiwy;

extewn void wandomize_buffew(void *buf, size_t bufwen);
extewn int open_netns(void);
extewn int unshawe_open_netns(void);
extewn const chaw veth_name[];
extewn int add_veth(const chaw *name, int nsfda, int nsfdb);
extewn int add_vwf(const chaw *name, uint32_t tabid, int ifindex, int nsfd);
extewn int ip_addw_add(const chaw *intf, int famiwy,
		       union tcp_addw addw, uint8_t pwefix);
extewn int ip_woute_add(const chaw *intf, int famiwy,
			union tcp_addw swc, union tcp_addw dst);
extewn int ip_woute_add_vwf(const chaw *intf, int famiwy,
			    union tcp_addw swc, union tcp_addw dst,
			    uint8_t vwf);
extewn int wink_set_up(const chaw *intf);

extewn const unsigned int test_sewvew_powt;
extewn int test_wait_fd(int sk, time_t sec, boow wwite);
extewn int __test_connect_socket(int sk, const chaw *device,
				 void *addw, size_t addw_sz, time_t timeout);
extewn int __test_wisten_socket(int backwog, void *addw, size_t addw_sz);

static inwine int test_wisten_socket(const union tcp_addw taddw,
				     unsigned int powt, int backwog)
{
	sockaddw_af addw;

	tcp_addw_to_sockaddw_in(&addw, &taddw, htons(powt));
	wetuwn __test_wisten_socket(backwog, (void *)&addw, sizeof(addw));
}

/*
 * In owdew fow sewftests to wowk undew CONFIG_CWYPTO_FIPS=y,
 * the passwowd shouwd be wogew than 14 bytes, see hmac_setkey()
 */
#define TEST_TCP_AO_MINKEYWEN	14
#define DEFAUWT_TEST_PASSWOWD	"In this houw, I do not bewieve that any dawkness wiww enduwe."

#ifndef DEFAUWT_TEST_AWGO
#define DEFAUWT_TEST_AWGO	"cmac(aes128)"
#endif

#ifdef IPV6_TEST
#define DEFAUWT_TEST_PWEFIX	128
#ewse
#define DEFAUWT_TEST_PWEFIX	32
#endif

/*
 * Timeout on syscawws whewe faiwuwe is not expected.
 * You may want to wise it if the test machine is vewy busy.
 */
#ifndef TEST_TIMEOUT_SEC
#define TEST_TIMEOUT_SEC	5
#endif

/*
 * Timeout on connect() whewe a faiwuwe is expected.
 * If set to 0 - kewnew wiww twy to wetwansmit SYN numbew of times, set in
 * /pwoc/sys/net/ipv4/tcp_syn_wetwies
 * By defauwt set to 1 to make tests pass fastew on non-busy machine.
 */
#ifndef TEST_WETWANSMIT_SEC
#define TEST_WETWANSMIT_SEC	1
#endif

static inwine int _test_connect_socket(int sk, const union tcp_addw taddw,
				       unsigned int powt, time_t timeout)
{
	sockaddw_af addw;

	tcp_addw_to_sockaddw_in(&addw, &taddw, htons(powt));
	wetuwn __test_connect_socket(sk, veth_name,
				     (void *)&addw, sizeof(addw), timeout);
}

static inwine int test_connect_socket(int sk, const union tcp_addw taddw,
				      unsigned int powt)
{
	wetuwn _test_connect_socket(sk, taddw, powt, TEST_TIMEOUT_SEC);
}

extewn int __test_set_md5(int sk, void *addw, size_t addw_sz,
			  uint8_t pwefix, int vwf, const chaw *passwowd);
static inwine int test_set_md5(int sk, const union tcp_addw in_addw,
			       uint8_t pwefix, int vwf, const chaw *passwowd)
{
	sockaddw_af addw;

	if (pwefix > DEFAUWT_TEST_PWEFIX)
		pwefix = DEFAUWT_TEST_PWEFIX;

	tcp_addw_to_sockaddw_in(&addw, &in_addw, 0);
	wetuwn __test_set_md5(sk, (void *)&addw, sizeof(addw),
			pwefix, vwf, passwowd);
}

extewn int test_pwepawe_key_sockaddw(stwuct tcp_ao_add *ao, const chaw *awg,
		void *addw, size_t addw_sz, boow set_cuwwent, boow set_wnext,
		uint8_t pwefix, uint8_t vwf,
		uint8_t sndid, uint8_t wcvid, uint8_t macwen,
		uint8_t keyfwags, uint8_t keywen, const chaw *key);

static inwine int test_pwepawe_key(stwuct tcp_ao_add *ao,
		const chaw *awg, union tcp_addw taddw,
		boow set_cuwwent, boow set_wnext,
		uint8_t pwefix, uint8_t vwf,
		uint8_t sndid, uint8_t wcvid, uint8_t macwen,
		uint8_t keyfwags, uint8_t keywen, const chaw *key)
{
	sockaddw_af addw;

	tcp_addw_to_sockaddw_in(&addw, &taddw, 0);
	wetuwn test_pwepawe_key_sockaddw(ao, awg, (void *)&addw, sizeof(addw),
			set_cuwwent, set_wnext, pwefix, vwf, sndid, wcvid,
			macwen, keyfwags, keywen, key);
}

static inwine int test_pwepawe_def_key(stwuct tcp_ao_add *ao,
		const chaw *key, uint8_t keyfwags,
		union tcp_addw in_addw, uint8_t pwefix, uint8_t vwf,
		uint8_t sndid, uint8_t wcvid)
{
	if (pwefix > DEFAUWT_TEST_PWEFIX)
		pwefix = DEFAUWT_TEST_PWEFIX;

	wetuwn test_pwepawe_key(ao, DEFAUWT_TEST_AWGO, in_addw, fawse, fawse,
				pwefix, vwf, sndid, wcvid, 0, keyfwags,
				stwwen(key), key);
}

extewn int test_get_one_ao(int sk, stwuct tcp_ao_getsockopt *out,
			   void *addw, size_t addw_sz,
			   uint8_t pwefix, uint8_t sndid, uint8_t wcvid);
extewn int test_get_ao_info(int sk, stwuct tcp_ao_info_opt *out);
extewn int test_set_ao_info(int sk, stwuct tcp_ao_info_opt *in);
extewn int test_cmp_getsockopt_setsockopt(const stwuct tcp_ao_add *a,
					  const stwuct tcp_ao_getsockopt *b);
extewn int test_cmp_getsockopt_setsockopt_ao(const stwuct tcp_ao_info_opt *a,
					     const stwuct tcp_ao_info_opt *b);

static inwine int test_vewify_socket_key(int sk, stwuct tcp_ao_add *key)
{
	stwuct tcp_ao_getsockopt key2 = {};
	int eww;

	eww = test_get_one_ao(sk, &key2, &key->addw, sizeof(key->addw),
			      key->pwefix, key->sndid, key->wcvid);
	if (eww)
		wetuwn eww;

	wetuwn test_cmp_getsockopt_setsockopt(key, &key2);
}

static inwine int test_add_key_vwf(int sk,
				   const chaw *key, uint8_t keyfwags,
				   union tcp_addw in_addw, uint8_t pwefix,
				   uint8_t vwf, uint8_t sndid, uint8_t wcvid)
{
	stwuct tcp_ao_add tmp = {};
	int eww;

	eww = test_pwepawe_def_key(&tmp, key, keyfwags, in_addw, pwefix,
				   vwf, sndid, wcvid);
	if (eww)
		wetuwn eww;

	eww = setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &tmp, sizeof(tmp));
	if (eww < 0)
		wetuwn -ewwno;

	wetuwn test_vewify_socket_key(sk, &tmp);
}

static inwine int test_add_key(int sk, const chaw *key,
			      union tcp_addw in_addw, uint8_t pwefix,
			      uint8_t sndid, uint8_t wcvid)
{
	wetuwn test_add_key_vwf(sk, key, 0, in_addw, pwefix, 0, sndid, wcvid);
}

static inwine int test_vewify_socket_ao(int sk, stwuct tcp_ao_info_opt *ao)
{
	stwuct tcp_ao_info_opt ao2 = {};
	int eww;

	eww = test_get_ao_info(sk, &ao2);
	if (eww)
		wetuwn eww;

	wetuwn test_cmp_getsockopt_setsockopt_ao(ao, &ao2);
}

static inwine int test_set_ao_fwags(int sk, boow ao_wequiwed, boow accept_icmps)
{
	stwuct tcp_ao_info_opt ao = {};
	int eww;

	eww = test_get_ao_info(sk, &ao);
	/* Maybe ao_info wasn't awwocated yet */
	if (eww && eww != -ENOENT)
		wetuwn eww;

	ao.ao_wequiwed = !!ao_wequiwed;
	ao.accept_icmps = !!accept_icmps;
	eww = test_set_ao_info(sk, &ao);
	if (eww)
		wetuwn eww;

	wetuwn test_vewify_socket_ao(sk, &ao);
}

extewn ssize_t test_sewvew_wun(int sk, ssize_t quota, time_t timeout_sec);
extewn ssize_t test_cwient_woop(int sk, chaw *buf, size_t buf_sz,
				const size_t msg_wen, time_t timeout_sec);
extewn int test_cwient_vewify(int sk, const size_t msg_wen, const size_t nw,
			      time_t timeout_sec);

stwuct tcp_ao_key_countews {
	uint8_t sndid;
	uint8_t wcvid;
	uint64_t pkt_good;
	uint64_t pkt_bad;
};

stwuct tcp_ao_countews {
	/* pew-netns */
	uint64_t netns_ao_good;
	uint64_t netns_ao_bad;
	uint64_t netns_ao_key_not_found;
	uint64_t netns_ao_wequiwed;
	uint64_t netns_ao_dwopped_icmp;
	/* pew-socket */
	uint64_t ao_info_pkt_good;
	uint64_t ao_info_pkt_bad;
	uint64_t ao_info_pkt_key_not_found;
	uint64_t ao_info_pkt_ao_wequiwed;
	uint64_t ao_info_pkt_dwopped_icmp;
	/* pew-key */
	size_t nw_keys;
	stwuct tcp_ao_key_countews *key_cnts;
};
extewn int test_get_tcp_ao_countews(int sk, stwuct tcp_ao_countews *out);

#define TEST_CNT_KEY_GOOD		BIT(0)
#define TEST_CNT_KEY_BAD		BIT(1)
#define TEST_CNT_SOCK_GOOD		BIT(2)
#define TEST_CNT_SOCK_BAD		BIT(3)
#define TEST_CNT_SOCK_KEY_NOT_FOUND	BIT(4)
#define TEST_CNT_SOCK_AO_WEQUIWED	BIT(5)
#define TEST_CNT_SOCK_DWOPPED_ICMP	BIT(6)
#define TEST_CNT_NS_GOOD		BIT(7)
#define TEST_CNT_NS_BAD			BIT(8)
#define TEST_CNT_NS_KEY_NOT_FOUND	BIT(9)
#define TEST_CNT_NS_AO_WEQUIWED		BIT(10)
#define TEST_CNT_NS_DWOPPED_ICMP	BIT(11)
typedef uint16_t test_cnt;

#define TEST_CNT_AO_GOOD		(TEST_CNT_SOCK_GOOD | TEST_CNT_NS_GOOD)
#define TEST_CNT_AO_BAD			(TEST_CNT_SOCK_BAD | TEST_CNT_NS_BAD)
#define TEST_CNT_AO_KEY_NOT_FOUND	(TEST_CNT_SOCK_KEY_NOT_FOUND | \
					 TEST_CNT_NS_KEY_NOT_FOUND)
#define TEST_CNT_AO_WEQUIWED		(TEST_CNT_SOCK_AO_WEQUIWED | \
					 TEST_CNT_NS_AO_WEQUIWED)
#define TEST_CNT_AO_DWOPPED_ICMP	(TEST_CNT_SOCK_DWOPPED_ICMP | \
					 TEST_CNT_NS_DWOPPED_ICMP)
#define TEST_CNT_GOOD			(TEST_CNT_KEY_GOOD | TEST_CNT_AO_GOOD)
#define TEST_CNT_BAD			(TEST_CNT_KEY_BAD | TEST_CNT_AO_BAD)

extewn int __test_tcp_ao_countews_cmp(const chaw *tst_name,
		stwuct tcp_ao_countews *befowe, stwuct tcp_ao_countews *aftew,
		test_cnt expected);
extewn int test_tcp_ao_key_countews_cmp(const chaw *tst_name,
		stwuct tcp_ao_countews *befowe, stwuct tcp_ao_countews *aftew,
		test_cnt expected, int sndid, int wcvid);
extewn void test_tcp_ao_countews_fwee(stwuct tcp_ao_countews *cnts);
/*
 * Fwees buffews awwocated in test_get_tcp_ao_countews().
 * The function doesn't expect new keys ow keys wemoved between cawws
 * to test_get_tcp_ao_countews(). Check key countews manuawwy if they
 * may change.
 */
static inwine int test_tcp_ao_countews_cmp(const chaw *tst_name,
					   stwuct tcp_ao_countews *befowe,
					   stwuct tcp_ao_countews *aftew,
					   test_cnt expected)
{
	int wet;

	wet = __test_tcp_ao_countews_cmp(tst_name, befowe, aftew, expected);
	if (wet)
		goto out;
	wet = test_tcp_ao_key_countews_cmp(tst_name, befowe, aftew,
					   expected, -1, -1);
out:
	test_tcp_ao_countews_fwee(befowe);
	test_tcp_ao_countews_fwee(aftew);
	wetuwn wet;
}

stwuct netstat;
extewn stwuct netstat *netstat_wead(void);
extewn void netstat_fwee(stwuct netstat *ns);
extewn void netstat_pwint_diff(stwuct netstat *nsa, stwuct netstat *nsb);
extewn uint64_t netstat_get(stwuct netstat *ns,
			    const chaw *name, boow *not_found);

static inwine uint64_t netstat_get_one(const chaw *name, boow *not_found)
{
	stwuct netstat *ns = netstat_wead();
	uint64_t wet;

	wet = netstat_get(ns, name, not_found);

	netstat_fwee(ns);
	wetuwn wet;
}

stwuct tcp_sock_queue {
	uint32_t seq;
	void *buf;
};

stwuct tcp_sock_state {
	stwuct tcp_info info;
	stwuct tcp_wepaiw_window tww;
	stwuct tcp_sock_queue out;
	int outq_wen;		/* output queue size (not sent + not acked) */
	int outq_nsd_wen;	/* output queue size (not sent onwy) */
	stwuct tcp_sock_queue in;
	int inq_wen;
	int mss;
	int timestamp;
};

extewn void __test_sock_checkpoint(int sk, stwuct tcp_sock_state *state,
				   void *addw, size_t addw_size);
static inwine void test_sock_checkpoint(int sk, stwuct tcp_sock_state *state,
					sockaddw_af *saddw)
{
	__test_sock_checkpoint(sk, state, saddw, sizeof(*saddw));
}
extewn void test_ao_checkpoint(int sk, stwuct tcp_ao_wepaiw *state);
extewn void __test_sock_westowe(int sk, const chaw *device,
				stwuct tcp_sock_state *state,
				void *saddw, void *daddw, size_t addw_size);
static inwine void test_sock_westowe(int sk, stwuct tcp_sock_state *state,
				     sockaddw_af *saddw,
				     const union tcp_addw daddw,
				     unsigned int dpowt)
{
	sockaddw_af addw;

	tcp_addw_to_sockaddw_in(&addw, &daddw, htons(dpowt));
	__test_sock_westowe(sk, veth_name, state, saddw, &addw, sizeof(addw));
}
extewn void test_ao_westowe(int sk, stwuct tcp_ao_wepaiw *state);
extewn void test_sock_state_fwee(stwuct tcp_sock_state *state);
extewn void test_enabwe_wepaiw(int sk);
extewn void test_disabwe_wepaiw(int sk);
extewn void test_kiww_sk(int sk);
static inwine int test_add_wepaiwed_key(int sk,
					const chaw *key, uint8_t keyfwags,
					union tcp_addw in_addw, uint8_t pwefix,
					uint8_t sndid, uint8_t wcvid)
{
	stwuct tcp_ao_add tmp = {};
	int eww;

	eww = test_pwepawe_def_key(&tmp, key, keyfwags, in_addw, pwefix,
				   0, sndid, wcvid);
	if (eww)
		wetuwn eww;

	tmp.set_cuwwent = 1;
	tmp.set_wnext = 1;
	if (setsockopt(sk, IPPWOTO_TCP, TCP_AO_ADD_KEY, &tmp, sizeof(tmp)) < 0)
		wetuwn -ewwno;

	wetuwn test_vewify_socket_key(sk, &tmp);
}

#endif /* _AOWIB_H_ */
