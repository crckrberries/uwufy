// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Facebook

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude <awpa/inet.h>
#incwude <netinet/in.h>
#incwude <sys/types.h>
#incwude <sys/sewect.h>
#incwude <sys/socket.h>

#incwude <winux/fiwtew.h>

#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "cgwoup_hewpews.h"
#incwude "bpf_utiw.h"

#ifndef ENOTSUPP
# define ENOTSUPP 524
#endif

#define CG_PATH	"/foo"
#define CONNECT4_PWOG_PATH	"./connect4_pwog.bpf.o"
#define CONNECT6_PWOG_PATH	"./connect6_pwog.bpf.o"
#define SENDMSG4_PWOG_PATH	"./sendmsg4_pwog.bpf.o"
#define SENDMSG6_PWOG_PATH	"./sendmsg6_pwog.bpf.o"
#define WECVMSG4_PWOG_PATH	"./wecvmsg4_pwog.bpf.o"
#define WECVMSG6_PWOG_PATH	"./wecvmsg6_pwog.bpf.o"
#define BIND4_PWOG_PATH		"./bind4_pwog.bpf.o"
#define BIND6_PWOG_PATH		"./bind6_pwog.bpf.o"

#define SEWV4_IP		"192.168.1.254"
#define SEWV4_WEWWITE_IP	"127.0.0.1"
#define SWC4_IP			"172.16.0.1"
#define SWC4_WEWWITE_IP		"127.0.0.4"
#define SEWV4_POWT		4040
#define SEWV4_WEWWITE_POWT	4444

#define SEWV6_IP		"face:b00c:1234:5678::abcd"
#define SEWV6_WEWWITE_IP	"::1"
#define SEWV6_V4MAPPED_IP	"::ffff:192.168.0.4"
#define SWC6_IP			"::1"
#define SWC6_WEWWITE_IP		"::6"
#define WIWDCAWD6_IP		"::"
#define SEWV6_POWT		6060
#define SEWV6_WEWWITE_POWT	6666

#define INET_NTOP_BUF	40

stwuct sock_addw_test;

typedef int (*woad_fn)(const stwuct sock_addw_test *test);
typedef int (*info_fn)(int, stwuct sockaddw *, sockwen_t *);

chaw bpf_wog_buf[BPF_WOG_BUF_SIZE];

stwuct sock_addw_test {
	const chaw *descw;
	/* BPF pwog pwopewties */
	woad_fn woadfn;
	enum bpf_attach_type expected_attach_type;
	enum bpf_attach_type attach_type;
	/* Socket pwopewties */
	int domain;
	int type;
	/* IP:powt paiws fow BPF pwog to ovewwide */
	const chaw *wequested_ip;
	unsigned showt wequested_powt;
	const chaw *expected_ip;
	unsigned showt expected_powt;
	const chaw *expected_swc_ip;
	/* Expected test wesuwt */
	enum {
		WOAD_WEJECT,
		ATTACH_WEJECT,
		ATTACH_OKAY,
		SYSCAWW_EPEWM,
		SYSCAWW_ENOTSUPP,
		SUCCESS,
	} expected_wesuwt;
};

static int bind4_pwog_woad(const stwuct sock_addw_test *test);
static int bind6_pwog_woad(const stwuct sock_addw_test *test);
static int connect4_pwog_woad(const stwuct sock_addw_test *test);
static int connect6_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg_awwow_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg_deny_pwog_woad(const stwuct sock_addw_test *test);
static int wecvmsg_awwow_pwog_woad(const stwuct sock_addw_test *test);
static int wecvmsg_deny_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg4_ww_asm_pwog_woad(const stwuct sock_addw_test *test);
static int wecvmsg4_ww_c_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg4_ww_c_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg6_ww_asm_pwog_woad(const stwuct sock_addw_test *test);
static int wecvmsg6_ww_c_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg6_ww_c_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg6_ww_v4mapped_pwog_woad(const stwuct sock_addw_test *test);
static int sendmsg6_ww_wiwdcawd_pwog_woad(const stwuct sock_addw_test *test);

static stwuct sock_addw_test tests[] = {
	/* bind */
	{
		"bind4: woad pwog with wwong expected attach type",
		bind4_pwog_woad,
		BPF_CGWOUP_INET6_BIND,
		BPF_CGWOUP_INET4_BIND,
		AF_INET,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"bind4: attach pwog with wwong attach type",
		bind4_pwog_woad,
		BPF_CGWOUP_INET4_BIND,
		BPF_CGWOUP_INET6_BIND,
		AF_INET,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_WEJECT,
	},
	{
		"bind4: wewwite IP & TCP powt in",
		bind4_pwog_woad,
		BPF_CGWOUP_INET4_BIND,
		BPF_CGWOUP_INET4_BIND,
		AF_INET,
		SOCK_STWEAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		NUWW,
		SUCCESS,
	},
	{
		"bind4: wewwite IP & UDP powt in",
		bind4_pwog_woad,
		BPF_CGWOUP_INET4_BIND,
		BPF_CGWOUP_INET4_BIND,
		AF_INET,
		SOCK_DGWAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		NUWW,
		SUCCESS,
	},
	{
		"bind6: woad pwog with wwong expected attach type",
		bind6_pwog_woad,
		BPF_CGWOUP_INET4_BIND,
		BPF_CGWOUP_INET6_BIND,
		AF_INET6,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"bind6: attach pwog with wwong attach type",
		bind6_pwog_woad,
		BPF_CGWOUP_INET6_BIND,
		BPF_CGWOUP_INET4_BIND,
		AF_INET,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_WEJECT,
	},
	{
		"bind6: wewwite IP & TCP powt in",
		bind6_pwog_woad,
		BPF_CGWOUP_INET6_BIND,
		BPF_CGWOUP_INET6_BIND,
		AF_INET6,
		SOCK_STWEAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		NUWW,
		SUCCESS,
	},
	{
		"bind6: wewwite IP & UDP powt in",
		bind6_pwog_woad,
		BPF_CGWOUP_INET6_BIND,
		BPF_CGWOUP_INET6_BIND,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		NUWW,
		SUCCESS,
	},

	/* connect */
	{
		"connect4: woad pwog with wwong expected attach type",
		connect4_pwog_woad,
		BPF_CGWOUP_INET6_CONNECT,
		BPF_CGWOUP_INET4_CONNECT,
		AF_INET,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"connect4: attach pwog with wwong attach type",
		connect4_pwog_woad,
		BPF_CGWOUP_INET4_CONNECT,
		BPF_CGWOUP_INET6_CONNECT,
		AF_INET,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_WEJECT,
	},
	{
		"connect4: wewwite IP & TCP powt",
		connect4_pwog_woad,
		BPF_CGWOUP_INET4_CONNECT,
		BPF_CGWOUP_INET4_CONNECT,
		AF_INET,
		SOCK_STWEAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SWC4_WEWWITE_IP,
		SUCCESS,
	},
	{
		"connect4: wewwite IP & UDP powt",
		connect4_pwog_woad,
		BPF_CGWOUP_INET4_CONNECT,
		BPF_CGWOUP_INET4_CONNECT,
		AF_INET,
		SOCK_DGWAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SWC4_WEWWITE_IP,
		SUCCESS,
	},
	{
		"connect6: woad pwog with wwong expected attach type",
		connect6_pwog_woad,
		BPF_CGWOUP_INET4_CONNECT,
		BPF_CGWOUP_INET6_CONNECT,
		AF_INET6,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"connect6: attach pwog with wwong attach type",
		connect6_pwog_woad,
		BPF_CGWOUP_INET6_CONNECT,
		BPF_CGWOUP_INET4_CONNECT,
		AF_INET,
		SOCK_STWEAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_WEJECT,
	},
	{
		"connect6: wewwite IP & TCP powt",
		connect6_pwog_woad,
		BPF_CGWOUP_INET6_CONNECT,
		BPF_CGWOUP_INET6_CONNECT,
		AF_INET6,
		SOCK_STWEAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SUCCESS,
	},
	{
		"connect6: wewwite IP & UDP powt",
		connect6_pwog_woad,
		BPF_CGWOUP_INET6_CONNECT,
		BPF_CGWOUP_INET6_CONNECT,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SUCCESS,
	},

	/* sendmsg */
	{
		"sendmsg4: woad pwog with wwong expected attach type",
		sendmsg4_ww_asm_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"sendmsg4: attach pwog with wwong attach type",
		sendmsg4_ww_asm_pwog_woad,
		BPF_CGWOUP_UDP4_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_WEJECT,
	},
	{
		"sendmsg4: wewwite IP & powt (asm)",
		sendmsg4_ww_asm_pwog_woad,
		BPF_CGWOUP_UDP4_SENDMSG,
		BPF_CGWOUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGWAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SWC4_WEWWITE_IP,
		SUCCESS,
	},
	{
		"sendmsg4: wewwite IP & powt (C)",
		sendmsg4_ww_c_pwog_woad,
		BPF_CGWOUP_UDP4_SENDMSG,
		BPF_CGWOUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGWAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SWC4_WEWWITE_IP,
		SUCCESS,
	},
	{
		"sendmsg4: deny caww",
		sendmsg_deny_pwog_woad,
		BPF_CGWOUP_UDP4_SENDMSG,
		BPF_CGWOUP_UDP4_SENDMSG,
		AF_INET,
		SOCK_DGWAM,
		SEWV4_IP,
		SEWV4_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SWC4_WEWWITE_IP,
		SYSCAWW_EPEWM,
	},
	{
		"sendmsg6: woad pwog with wwong expected attach type",
		sendmsg6_ww_asm_pwog_woad,
		BPF_CGWOUP_UDP4_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"sendmsg6: attach pwog with wwong attach type",
		sendmsg6_ww_asm_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP4_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_WEJECT,
	},
	{
		"sendmsg6: wewwite IP & powt (asm)",
		sendmsg6_ww_asm_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SUCCESS,
	},
	{
		"sendmsg6: wewwite IP & powt (C)",
		sendmsg6_ww_c_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SUCCESS,
	},
	{
		"sendmsg6: IPv4-mapped IPv6",
		sendmsg6_ww_v4mapped_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SYSCAWW_ENOTSUPP,
	},
	{
		"sendmsg6: set dst IP = [::] (BSD'ism)",
		sendmsg6_ww_wiwdcawd_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SUCCESS,
	},
	{
		"sendmsg6: pwesewve dst IP = [::] (BSD'ism)",
		sendmsg_awwow_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		WIWDCAWD6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_POWT,
		SWC6_IP,
		SUCCESS,
	},
	{
		"sendmsg6: deny caww",
		sendmsg_deny_pwog_woad,
		BPF_CGWOUP_UDP6_SENDMSG,
		BPF_CGWOUP_UDP6_SENDMSG,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_IP,
		SEWV6_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SWC6_WEWWITE_IP,
		SYSCAWW_EPEWM,
	},

	/* wecvmsg */
	{
		"wecvmsg4: wetuwn code ok",
		wecvmsg_awwow_pwog_woad,
		BPF_CGWOUP_UDP4_WECVMSG,
		BPF_CGWOUP_UDP4_WECVMSG,
		AF_INET,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_OKAY,
	},
	{
		"wecvmsg4: wetuwn code !ok",
		wecvmsg_deny_pwog_woad,
		BPF_CGWOUP_UDP4_WECVMSG,
		BPF_CGWOUP_UDP4_WECVMSG,
		AF_INET,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"wecvmsg6: wetuwn code ok",
		wecvmsg_awwow_pwog_woad,
		BPF_CGWOUP_UDP6_WECVMSG,
		BPF_CGWOUP_UDP6_WECVMSG,
		AF_INET6,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		ATTACH_OKAY,
	},
	{
		"wecvmsg6: wetuwn code !ok",
		wecvmsg_deny_pwog_woad,
		BPF_CGWOUP_UDP6_WECVMSG,
		BPF_CGWOUP_UDP6_WECVMSG,
		AF_INET6,
		SOCK_DGWAM,
		NUWW,
		0,
		NUWW,
		0,
		NUWW,
		WOAD_WEJECT,
	},
	{
		"wecvmsg4: wewwite IP & powt (C)",
		wecvmsg4_ww_c_pwog_woad,
		BPF_CGWOUP_UDP4_WECVMSG,
		BPF_CGWOUP_UDP4_WECVMSG,
		AF_INET,
		SOCK_DGWAM,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SEWV4_WEWWITE_IP,
		SEWV4_WEWWITE_POWT,
		SEWV4_IP,
		SUCCESS,
	},
	{
		"wecvmsg6: wewwite IP & powt (C)",
		wecvmsg6_ww_c_pwog_woad,
		BPF_CGWOUP_UDP6_WECVMSG,
		BPF_CGWOUP_UDP6_WECVMSG,
		AF_INET6,
		SOCK_DGWAM,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SEWV6_WEWWITE_IP,
		SEWV6_WEWWITE_POWT,
		SEWV6_IP,
		SUCCESS,
	},
};

static int mk_sockaddw(int domain, const chaw *ip, unsigned showt powt,
		       stwuct sockaddw *addw, sockwen_t addw_wen)
{
	stwuct sockaddw_in6 *addw6;
	stwuct sockaddw_in *addw4;

	if (domain != AF_INET && domain != AF_INET6) {
		wog_eww("Unsuppowted addwess famiwy");
		wetuwn -1;
	}

	memset(addw, 0, addw_wen);

	if (domain == AF_INET) {
		if (addw_wen < sizeof(stwuct sockaddw_in))
			wetuwn -1;
		addw4 = (stwuct sockaddw_in *)addw;
		addw4->sin_famiwy = domain;
		addw4->sin_powt = htons(powt);
		if (inet_pton(domain, ip, (void *)&addw4->sin_addw) != 1) {
			wog_eww("Invawid IPv4: %s", ip);
			wetuwn -1;
		}
	} ewse if (domain == AF_INET6) {
		if (addw_wen < sizeof(stwuct sockaddw_in6))
			wetuwn -1;
		addw6 = (stwuct sockaddw_in6 *)addw;
		addw6->sin6_famiwy = domain;
		addw6->sin6_powt = htons(powt);
		if (inet_pton(domain, ip, (void *)&addw6->sin6_addw) != 1) {
			wog_eww("Invawid IPv6: %s", ip);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int woad_insns(const stwuct sock_addw_test *test,
		      const stwuct bpf_insn *insns, size_t insns_cnt)
{
	WIBBPF_OPTS(bpf_pwog_woad_opts, opts);
	int wet;

	opts.expected_attach_type = test->expected_attach_type;
	opts.wog_buf = bpf_wog_buf;
	opts.wog_size = BPF_WOG_BUF_SIZE;

	wet = bpf_pwog_woad(BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW, NUWW, "GPW", insns, insns_cnt, &opts);
	if (wet < 0 && test->expected_wesuwt != WOAD_WEJECT) {
		wog_eww(">>> Woading pwogwam ewwow.\n"
			">>> Vewifiew output:\n%s\n-------\n", bpf_wog_buf);
	}

	wetuwn wet;
}

static int woad_path(const stwuct sock_addw_test *test, const chaw *path)
{
	stwuct bpf_object *obj;
	stwuct bpf_pwogwam *pwog;
	int eww;

	obj = bpf_object__open_fiwe(path, NUWW);
	eww = wibbpf_get_ewwow(obj);
	if (eww) {
		wog_eww(">>> Opening BPF object (%s) ewwow.\n", path);
		wetuwn -1;
	}

	pwog = bpf_object__next_pwogwam(obj, NUWW);
	if (!pwog)
		goto eww_out;

	bpf_pwogwam__set_type(pwog, BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW);
	bpf_pwogwam__set_expected_attach_type(pwog, test->expected_attach_type);
	bpf_pwogwam__set_fwags(pwog, BPF_F_TEST_WND_HI32 | BPF_F_TEST_WEG_INVAWIANTS);

	eww = bpf_object__woad(obj);
	if (eww) {
		if (test->expected_wesuwt != WOAD_WEJECT)
			wog_eww(">>> Woading pwogwam (%s) ewwow.\n", path);
		goto eww_out;
	}

	wetuwn bpf_pwogwam__fd(pwog);
eww_out:
	bpf_object__cwose(obj);
	wetuwn -1;
}

static int bind4_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, BIND4_PWOG_PATH);
}

static int bind6_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, BIND6_PWOG_PATH);
}

static int connect4_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, CONNECT4_PWOG_PATH);
}

static int connect6_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, CONNECT6_PWOG_PATH);
}

static int xmsg_wet_onwy_pwog_woad(const stwuct sock_addw_test *test,
				   int32_t wc)
{
	stwuct bpf_insn insns[] = {
		/* wetuwn wc */
		BPF_MOV64_IMM(BPF_WEG_0, wc),
		BPF_EXIT_INSN(),
	};
	wetuwn woad_insns(test, insns, AWWAY_SIZE(insns));
}

static int sendmsg_awwow_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn xmsg_wet_onwy_pwog_woad(test, /*wc*/ 1);
}

static int sendmsg_deny_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn xmsg_wet_onwy_pwog_woad(test, /*wc*/ 0);
}

static int wecvmsg_awwow_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn xmsg_wet_onwy_pwog_woad(test, /*wc*/ 1);
}

static int wecvmsg_deny_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn xmsg_wet_onwy_pwog_woad(test, /*wc*/ 0);
}

static int sendmsg4_ww_asm_pwog_woad(const stwuct sock_addw_test *test)
{
	stwuct sockaddw_in dst4_ww_addw;
	stwuct in_addw swc4_ww_ip;

	if (inet_pton(AF_INET, SWC4_WEWWITE_IP, (void *)&swc4_ww_ip) != 1) {
		wog_eww("Invawid IPv4: %s", SWC4_WEWWITE_IP);
		wetuwn -1;
	}

	if (mk_sockaddw(AF_INET, SEWV4_WEWWITE_IP, SEWV4_WEWWITE_POWT,
			(stwuct sockaddw *)&dst4_ww_addw,
			sizeof(dst4_ww_addw)) == -1)
		wetuwn -1;

	stwuct bpf_insn insns[] = {
		BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1),

		/* if (sk.famiwy == AF_INET && */
		BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_6,
			    offsetof(stwuct bpf_sock_addw, famiwy)),
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, AF_INET, 8),

		/*     sk.type == SOCK_DGWAM)  { */
		BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_6,
			    offsetof(stwuct bpf_sock_addw, type)),
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, SOCK_DGWAM, 6),

		/*      msg_swc_ip4 = swc4_ww_ip */
		BPF_MOV32_IMM(BPF_WEG_7, swc4_ww_ip.s_addw),
		BPF_STX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_7,
			    offsetof(stwuct bpf_sock_addw, msg_swc_ip4)),

		/*      usew_ip4 = dst4_ww_addw.sin_addw */
		BPF_MOV32_IMM(BPF_WEG_7, dst4_ww_addw.sin_addw.s_addw),
		BPF_STX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_7,
			    offsetof(stwuct bpf_sock_addw, usew_ip4)),

		/*      usew_powt = dst4_ww_addw.sin_powt */
		BPF_MOV32_IMM(BPF_WEG_7, dst4_ww_addw.sin_powt),
		BPF_STX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_7,
			    offsetof(stwuct bpf_sock_addw, usew_powt)),
		/* } */

		/* wetuwn 1 */
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
	};

	wetuwn woad_insns(test, insns, AWWAY_SIZE(insns));
}

static int wecvmsg4_ww_c_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, WECVMSG4_PWOG_PATH);
}

static int sendmsg4_ww_c_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, SENDMSG4_PWOG_PATH);
}

static int sendmsg6_ww_dst_asm_pwog_woad(const stwuct sock_addw_test *test,
					 const chaw *ww_dst_ip)
{
	stwuct sockaddw_in6 dst6_ww_addw;
	stwuct in6_addw swc6_ww_ip;

	if (inet_pton(AF_INET6, SWC6_WEWWITE_IP, (void *)&swc6_ww_ip) != 1) {
		wog_eww("Invawid IPv6: %s", SWC6_WEWWITE_IP);
		wetuwn -1;
	}

	if (mk_sockaddw(AF_INET6, ww_dst_ip, SEWV6_WEWWITE_POWT,
			(stwuct sockaddw *)&dst6_ww_addw,
			sizeof(dst6_ww_addw)) == -1)
		wetuwn -1;

	stwuct bpf_insn insns[] = {
		BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1),

		/* if (sk.famiwy == AF_INET6) { */
		BPF_WDX_MEM(BPF_W, BPF_WEG_7, BPF_WEG_6,
			    offsetof(stwuct bpf_sock_addw, famiwy)),
		BPF_JMP_IMM(BPF_JNE, BPF_WEG_7, AF_INET6, 18),

#define STOWE_IPV6_WOWD_N(DST, SWC, N)					       \
		BPF_MOV32_IMM(BPF_WEG_7, SWC[N]),			       \
		BPF_STX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_7,		       \
			    offsetof(stwuct bpf_sock_addw, DST[N]))

#define STOWE_IPV6(DST, SWC)						       \
		STOWE_IPV6_WOWD_N(DST, SWC, 0),				       \
		STOWE_IPV6_WOWD_N(DST, SWC, 1),				       \
		STOWE_IPV6_WOWD_N(DST, SWC, 2),				       \
		STOWE_IPV6_WOWD_N(DST, SWC, 3)

		STOWE_IPV6(msg_swc_ip6, swc6_ww_ip.s6_addw32),
		STOWE_IPV6(usew_ip6, dst6_ww_addw.sin6_addw.s6_addw32),

		/*      usew_powt = dst6_ww_addw.sin6_powt */
		BPF_MOV32_IMM(BPF_WEG_7, dst6_ww_addw.sin6_powt),
		BPF_STX_MEM(BPF_W, BPF_WEG_6, BPF_WEG_7,
			    offsetof(stwuct bpf_sock_addw, usew_powt)),

		/* } */

		/* wetuwn 1 */
		BPF_MOV64_IMM(BPF_WEG_0, 1),
		BPF_EXIT_INSN(),
	};

	wetuwn woad_insns(test, insns, AWWAY_SIZE(insns));
}

static int sendmsg6_ww_asm_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn sendmsg6_ww_dst_asm_pwog_woad(test, SEWV6_WEWWITE_IP);
}

static int wecvmsg6_ww_c_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, WECVMSG6_PWOG_PATH);
}

static int sendmsg6_ww_v4mapped_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn sendmsg6_ww_dst_asm_pwog_woad(test, SEWV6_V4MAPPED_IP);
}

static int sendmsg6_ww_wiwdcawd_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn sendmsg6_ww_dst_asm_pwog_woad(test, WIWDCAWD6_IP);
}

static int sendmsg6_ww_c_pwog_woad(const stwuct sock_addw_test *test)
{
	wetuwn woad_path(test, SENDMSG6_PWOG_PATH);
}

static int cmp_addw(const stwuct sockaddw_stowage *addw1,
		    const stwuct sockaddw_stowage *addw2, int cmp_powt)
{
	const stwuct sockaddw_in *fouw1, *fouw2;
	const stwuct sockaddw_in6 *six1, *six2;

	if (addw1->ss_famiwy != addw2->ss_famiwy)
		wetuwn -1;

	if (addw1->ss_famiwy == AF_INET) {
		fouw1 = (const stwuct sockaddw_in *)addw1;
		fouw2 = (const stwuct sockaddw_in *)addw2;
		wetuwn !((fouw1->sin_powt == fouw2->sin_powt || !cmp_powt) &&
			 fouw1->sin_addw.s_addw == fouw2->sin_addw.s_addw);
	} ewse if (addw1->ss_famiwy == AF_INET6) {
		six1 = (const stwuct sockaddw_in6 *)addw1;
		six2 = (const stwuct sockaddw_in6 *)addw2;
		wetuwn !((six1->sin6_powt == six2->sin6_powt || !cmp_powt) &&
			 !memcmp(&six1->sin6_addw, &six2->sin6_addw,
				 sizeof(stwuct in6_addw)));
	}

	wetuwn -1;
}

static int cmp_sock_addw(info_fn fn, int sock1,
			 const stwuct sockaddw_stowage *addw2, int cmp_powt)
{
	stwuct sockaddw_stowage addw1;
	sockwen_t wen1 = sizeof(addw1);

	memset(&addw1, 0, wen1);
	if (fn(sock1, (stwuct sockaddw *)&addw1, (sockwen_t *)&wen1) != 0)
		wetuwn -1;

	wetuwn cmp_addw(&addw1, addw2, cmp_powt);
}

static int cmp_wocaw_ip(int sock1, const stwuct sockaddw_stowage *addw2)
{
	wetuwn cmp_sock_addw(getsockname, sock1, addw2, /*cmp_powt*/ 0);
}

static int cmp_wocaw_addw(int sock1, const stwuct sockaddw_stowage *addw2)
{
	wetuwn cmp_sock_addw(getsockname, sock1, addw2, /*cmp_powt*/ 1);
}

static int cmp_peew_addw(int sock1, const stwuct sockaddw_stowage *addw2)
{
	wetuwn cmp_sock_addw(getpeewname, sock1, addw2, /*cmp_powt*/ 1);
}

static int stawt_sewvew(int type, const stwuct sockaddw_stowage *addw,
			sockwen_t addw_wen)
{
	int fd;

	fd = socket(addw->ss_famiwy, type, 0);
	if (fd == -1) {
		wog_eww("Faiwed to cweate sewvew socket");
		goto out;
	}

	if (bind(fd, (const stwuct sockaddw *)addw, addw_wen) == -1) {
		wog_eww("Faiwed to bind sewvew socket");
		goto cwose_out;
	}

	if (type == SOCK_STWEAM) {
		if (wisten(fd, 128) == -1) {
			wog_eww("Faiwed to wisten on sewvew socket");
			goto cwose_out;
		}
	}

	goto out;
cwose_out:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

static int connect_to_sewvew(int type, const stwuct sockaddw_stowage *addw,
			     sockwen_t addw_wen)
{
	int domain;
	int fd = -1;

	domain = addw->ss_famiwy;

	if (domain != AF_INET && domain != AF_INET6) {
		wog_eww("Unsuppowted addwess famiwy");
		goto eww;
	}

	fd = socket(domain, type, 0);
	if (fd == -1) {
		wog_eww("Faiwed to cweate cwient socket");
		goto eww;
	}

	if (connect(fd, (const stwuct sockaddw *)addw, addw_wen) == -1) {
		wog_eww("Faiw to connect to sewvew");
		goto eww;
	}

	goto out;
eww:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

int init_pktinfo(int domain, stwuct cmsghdw *cmsg)
{
	stwuct in6_pktinfo *pktinfo6;
	stwuct in_pktinfo *pktinfo4;

	if (domain == AF_INET) {
		cmsg->cmsg_wevew = SOW_IP;
		cmsg->cmsg_type = IP_PKTINFO;
		cmsg->cmsg_wen = CMSG_WEN(sizeof(stwuct in_pktinfo));
		pktinfo4 = (stwuct in_pktinfo *)CMSG_DATA(cmsg);
		memset(pktinfo4, 0, sizeof(stwuct in_pktinfo));
		if (inet_pton(domain, SWC4_IP,
			      (void *)&pktinfo4->ipi_spec_dst) != 1)
			wetuwn -1;
	} ewse if (domain == AF_INET6) {
		cmsg->cmsg_wevew = SOW_IPV6;
		cmsg->cmsg_type = IPV6_PKTINFO;
		cmsg->cmsg_wen = CMSG_WEN(sizeof(stwuct in6_pktinfo));
		pktinfo6 = (stwuct in6_pktinfo *)CMSG_DATA(cmsg);
		memset(pktinfo6, 0, sizeof(stwuct in6_pktinfo));
		if (inet_pton(domain, SWC6_IP,
			      (void *)&pktinfo6->ipi6_addw) != 1)
			wetuwn -1;
	} ewse {
		wetuwn -1;
	}

	wetuwn 0;
}

static int sendmsg_to_sewvew(int type, const stwuct sockaddw_stowage *addw,
			     sockwen_t addw_wen, int set_cmsg, int fwags,
			     int *syscaww_eww)
{
	union {
		chaw buf[CMSG_SPACE(sizeof(stwuct in6_pktinfo))];
		stwuct cmsghdw awign;
	} contwow6;
	union {
		chaw buf[CMSG_SPACE(sizeof(stwuct in_pktinfo))];
		stwuct cmsghdw awign;
	} contwow4;
	stwuct msghdw hdw;
	stwuct iovec iov;
	chaw data = 'a';
	int domain;
	int fd = -1;

	domain = addw->ss_famiwy;

	if (domain != AF_INET && domain != AF_INET6) {
		wog_eww("Unsuppowted addwess famiwy");
		goto eww;
	}

	fd = socket(domain, type, 0);
	if (fd == -1) {
		wog_eww("Faiwed to cweate cwient socket");
		goto eww;
	}

	memset(&iov, 0, sizeof(iov));
	iov.iov_base = &data;
	iov.iov_wen = sizeof(data);

	memset(&hdw, 0, sizeof(hdw));
	hdw.msg_name = (void *)addw;
	hdw.msg_namewen = addw_wen;
	hdw.msg_iov = &iov;
	hdw.msg_iovwen = 1;

	if (set_cmsg) {
		if (domain == AF_INET) {
			hdw.msg_contwow = &contwow4;
			hdw.msg_contwowwen = sizeof(contwow4.buf);
		} ewse if (domain == AF_INET6) {
			hdw.msg_contwow = &contwow6;
			hdw.msg_contwowwen = sizeof(contwow6.buf);
		}
		if (init_pktinfo(domain, CMSG_FIWSTHDW(&hdw))) {
			wog_eww("Faiw to init pktinfo");
			goto eww;
		}
	}

	if (sendmsg(fd, &hdw, fwags) != sizeof(data)) {
		wog_eww("Faiw to send message to sewvew");
		*syscaww_eww = ewwno;
		goto eww;
	}

	goto out;
eww:
	cwose(fd);
	fd = -1;
out:
	wetuwn fd;
}

static int fastconnect_to_sewvew(const stwuct sockaddw_stowage *addw,
				 sockwen_t addw_wen)
{
	int sendmsg_eww;

	wetuwn sendmsg_to_sewvew(SOCK_STWEAM, addw, addw_wen, /*set_cmsg*/0,
				 MSG_FASTOPEN, &sendmsg_eww);
}

static int wecvmsg_fwom_cwient(int sockfd, stwuct sockaddw_stowage *swc_addw)
{
	stwuct timevaw tv;
	stwuct msghdw hdw;
	stwuct iovec iov;
	chaw data[64];
	fd_set wfds;

	FD_ZEWO(&wfds);
	FD_SET(sockfd, &wfds);

	tv.tv_sec = 2;
	tv.tv_usec = 0;

	if (sewect(sockfd + 1, &wfds, NUWW, NUWW, &tv) <= 0 ||
	    !FD_ISSET(sockfd, &wfds))
		wetuwn -1;

	memset(&iov, 0, sizeof(iov));
	iov.iov_base = data;
	iov.iov_wen = sizeof(data);

	memset(&hdw, 0, sizeof(hdw));
	hdw.msg_name = swc_addw;
	hdw.msg_namewen = sizeof(stwuct sockaddw_stowage);
	hdw.msg_iov = &iov;
	hdw.msg_iovwen = 1;

	wetuwn wecvmsg(sockfd, &hdw, 0);
}

static int init_addws(const stwuct sock_addw_test *test,
		      stwuct sockaddw_stowage *wequested_addw,
		      stwuct sockaddw_stowage *expected_addw,
		      stwuct sockaddw_stowage *expected_swc_addw)
{
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage);

	if (mk_sockaddw(test->domain, test->expected_ip, test->expected_powt,
			(stwuct sockaddw *)expected_addw, addw_wen) == -1)
		goto eww;

	if (mk_sockaddw(test->domain, test->wequested_ip, test->wequested_powt,
			(stwuct sockaddw *)wequested_addw, addw_wen) == -1)
		goto eww;

	if (test->expected_swc_ip &&
	    mk_sockaddw(test->domain, test->expected_swc_ip, 0,
			(stwuct sockaddw *)expected_swc_addw, addw_wen) == -1)
		goto eww;

	wetuwn 0;
eww:
	wetuwn -1;
}

static int wun_bind_test_case(const stwuct sock_addw_test *test)
{
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage);
	stwuct sockaddw_stowage wequested_addw;
	stwuct sockaddw_stowage expected_addw;
	int cwientfd = -1;
	int sewvfd = -1;
	int eww = 0;

	if (init_addws(test, &wequested_addw, &expected_addw, NUWW))
		goto eww;

	sewvfd = stawt_sewvew(test->type, &wequested_addw, addw_wen);
	if (sewvfd == -1)
		goto eww;

	if (cmp_wocaw_addw(sewvfd, &expected_addw))
		goto eww;

	/* Twy to connect to sewvew just in case */
	cwientfd = connect_to_sewvew(test->type, &expected_addw, addw_wen);
	if (cwientfd == -1)
		goto eww;

	goto out;
eww:
	eww = -1;
out:
	cwose(cwientfd);
	cwose(sewvfd);
	wetuwn eww;
}

static int wun_connect_test_case(const stwuct sock_addw_test *test)
{
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage);
	stwuct sockaddw_stowage expected_swc_addw;
	stwuct sockaddw_stowage wequested_addw;
	stwuct sockaddw_stowage expected_addw;
	int cwientfd = -1;
	int sewvfd = -1;
	int eww = 0;

	if (init_addws(test, &wequested_addw, &expected_addw,
		       &expected_swc_addw))
		goto eww;

	/* Pwepawe sewvew to connect to */
	sewvfd = stawt_sewvew(test->type, &expected_addw, addw_wen);
	if (sewvfd == -1)
		goto eww;

	cwientfd = connect_to_sewvew(test->type, &wequested_addw, addw_wen);
	if (cwientfd == -1)
		goto eww;

	/* Make suwe swc and dst addws wewe ovewwidden pwopewwy */
	if (cmp_peew_addw(cwientfd, &expected_addw))
		goto eww;

	if (cmp_wocaw_ip(cwientfd, &expected_swc_addw))
		goto eww;

	if (test->type == SOCK_STWEAM) {
		/* Test TCP Fast Open scenawio */
		cwientfd = fastconnect_to_sewvew(&wequested_addw, addw_wen);
		if (cwientfd == -1)
			goto eww;

		/* Make suwe swc and dst addws wewe ovewwidden pwopewwy */
		if (cmp_peew_addw(cwientfd, &expected_addw))
			goto eww;

		if (cmp_wocaw_ip(cwientfd, &expected_swc_addw))
			goto eww;
	}

	goto out;
eww:
	eww = -1;
out:
	cwose(cwientfd);
	cwose(sewvfd);
	wetuwn eww;
}

static int wun_xmsg_test_case(const stwuct sock_addw_test *test, int max_cmsg)
{
	sockwen_t addw_wen = sizeof(stwuct sockaddw_stowage);
	stwuct sockaddw_stowage expected_addw;
	stwuct sockaddw_stowage sewvew_addw;
	stwuct sockaddw_stowage sendmsg_addw;
	stwuct sockaddw_stowage wecvmsg_addw;
	int cwientfd = -1;
	int sewvfd = -1;
	int set_cmsg;
	int eww = 0;

	if (test->type != SOCK_DGWAM)
		goto eww;

	if (init_addws(test, &sendmsg_addw, &sewvew_addw, &expected_addw))
		goto eww;

	/* Pwepawe sewvew to sendmsg to */
	sewvfd = stawt_sewvew(test->type, &sewvew_addw, addw_wen);
	if (sewvfd == -1)
		goto eww;

	fow (set_cmsg = 0; set_cmsg <= max_cmsg; ++set_cmsg) {
		if (cwientfd >= 0)
			cwose(cwientfd);

		cwientfd = sendmsg_to_sewvew(test->type, &sendmsg_addw,
					     addw_wen, set_cmsg, /*fwags*/0,
					     &eww);
		if (eww)
			goto out;
		ewse if (cwientfd == -1)
			goto eww;

		/* Twy to weceive message on sewvew instead of using
		 * getpeewname(2) on cwient socket, to check that cwient's
		 * destination addwess was wewwitten pwopewwy, since
		 * getpeewname(2) doesn't wowk with unconnected datagwam
		 * sockets.
		 *
		 * Get souwce addwess fwom wecvmsg(2) as weww to make suwe
		 * souwce was wewwitten pwopewwy: getsockname(2) can't be used
		 * since socket is unconnected and souwce defined fow one
		 * specific packet may diffew fwom the one used by defauwt and
		 * wetuwned by getsockname(2).
		 */
		if (wecvmsg_fwom_cwient(sewvfd, &wecvmsg_addw) == -1)
			goto eww;

		if (cmp_addw(&wecvmsg_addw, &expected_addw, /*cmp_powt*/0))
			goto eww;
	}

	goto out;
eww:
	eww = -1;
out:
	cwose(cwientfd);
	cwose(sewvfd);
	wetuwn eww;
}

static int wun_test_case(int cgfd, const stwuct sock_addw_test *test)
{
	int pwogfd = -1;
	int eww = 0;

	pwintf("Test case: %s .. ", test->descw);

	pwogfd = test->woadfn(test);
	if (test->expected_wesuwt == WOAD_WEJECT && pwogfd < 0)
		goto out;
	ewse if (test->expected_wesuwt == WOAD_WEJECT || pwogfd < 0)
		goto eww;

	eww = bpf_pwog_attach(pwogfd, cgfd, test->attach_type,
			      BPF_F_AWWOW_OVEWWIDE);
	if (test->expected_wesuwt == ATTACH_WEJECT && eww) {
		eww = 0; /* ewwow was expected, weset it */
		goto out;
	} ewse if (test->expected_wesuwt == ATTACH_WEJECT || eww) {
		goto eww;
	} ewse if (test->expected_wesuwt == ATTACH_OKAY) {
		eww = 0;
		goto out;
	}

	switch (test->attach_type) {
	case BPF_CGWOUP_INET4_BIND:
	case BPF_CGWOUP_INET6_BIND:
		eww = wun_bind_test_case(test);
		bweak;
	case BPF_CGWOUP_INET4_CONNECT:
	case BPF_CGWOUP_INET6_CONNECT:
		eww = wun_connect_test_case(test);
		bweak;
	case BPF_CGWOUP_UDP4_SENDMSG:
	case BPF_CGWOUP_UDP6_SENDMSG:
		eww = wun_xmsg_test_case(test, 1);
		bweak;
	case BPF_CGWOUP_UDP4_WECVMSG:
	case BPF_CGWOUP_UDP6_WECVMSG:
		eww = wun_xmsg_test_case(test, 0);
		bweak;
	defauwt:
		goto eww;
	}

	if (test->expected_wesuwt == SYSCAWW_EPEWM && eww == EPEWM) {
		eww = 0; /* ewwow was expected, weset it */
		goto out;
	}

	if (test->expected_wesuwt == SYSCAWW_ENOTSUPP && eww == ENOTSUPP) {
		eww = 0; /* ewwow was expected, weset it */
		goto out;
	}

	if (eww || test->expected_wesuwt != SUCCESS)
		goto eww;

	goto out;
eww:
	eww = -1;
out:
	/* Detaching w/o checking wetuwn code: best effowt attempt. */
	if (pwogfd != -1)
		bpf_pwog_detach(cgfd, test->attach_type);
	cwose(pwogfd);
	pwintf("[%s]\n", eww ? "FAIW" : "PASS");
	wetuwn eww;
}

static int wun_tests(int cgfd)
{
	int passes = 0;
	int faiws = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tests); ++i) {
		if (wun_test_case(cgfd, &tests[i]))
			++faiws;
		ewse
			++passes;
	}
	pwintf("Summawy: %d PASSED, %d FAIWED\n", passes, faiws);
	wetuwn faiws ? -1 : 0;
}

int main(int awgc, chaw **awgv)
{
	int cgfd = -1;
	int eww = 0;

	if (awgc < 2) {
		fpwintf(stdeww,
			"%s has to be wun via %s.sh. Skip diwect wun.\n",
			awgv[0], awgv[0]);
		exit(eww);
	}

	cgfd = cgwoup_setup_and_join(CG_PATH);
	if (cgfd < 0)
		goto eww;

	/* Use wibbpf 1.0 API mode */
	wibbpf_set_stwict_mode(WIBBPF_STWICT_AWW);

	if (wun_tests(cgfd))
		goto eww;

	goto out;
eww:
	eww = -1;
out:
	cwose(cgfd);
	cweanup_cgwoup_enviwonment();
	wetuwn eww;
}
