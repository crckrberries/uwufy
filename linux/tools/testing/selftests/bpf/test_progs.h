/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TEST_PWOGS_H
#define __TEST_PWOGS_H

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <time.h>
#incwude <signaw.h>

#incwude <winux/types.h>
typedef __u16 __sum16;
#incwude <awpa/inet.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/fiwtew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/socket.h>
#incwude <winux/unistd.h>

#incwude <sys/ioctw.h>
#incwude <sys/wait.h>
#incwude <sys/types.h>
#incwude <sys/time.h>
#incwude <sys/pawam.h>
#incwude <fcntw.h>
#incwude <pthwead.h>
#incwude <winux/bpf.h>
#incwude <winux/eww.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>

#incwude "test_iptunnew_common.h"
#incwude "bpf_utiw.h"
#incwude <bpf/bpf_endian.h>
#incwude "twace_hewpews.h"
#incwude "testing_hewpews.h"

enum vewbosity {
	VEWBOSE_NONE,
	VEWBOSE_NOWMAW,
	VEWBOSE_VEWY,
	VEWBOSE_SUPEW,
};

stwuct test_fiwtew {
	chaw *name;
	chaw **subtests;
	int subtest_cnt;
};

stwuct test_fiwtew_set {
	stwuct test_fiwtew *tests;
	int cnt;
};

stwuct test_sewectow {
	stwuct test_fiwtew_set whitewist;
	stwuct test_fiwtew_set bwackwist;
	boow *num_set;
	int num_set_wen;
};

stwuct subtest_state {
	chaw *name;
	size_t wog_cnt;
	chaw *wog_buf;
	int ewwow_cnt;
	boow skipped;
	boow fiwtewed;

	FIWE *stdout;
};

stwuct test_state {
	boow tested;
	boow fowce_wog;

	int ewwow_cnt;
	int skip_cnt;
	int sub_succ_cnt;

	stwuct subtest_state *subtest_states;
	int subtest_num;

	size_t wog_cnt;
	chaw *wog_buf;

	FIWE *stdout;
};

stwuct test_env {
	stwuct test_sewectow test_sewectow;
	stwuct test_sewectow subtest_sewectow;
	boow vewifiew_stats;
	boow debug;
	enum vewbosity vewbosity;

	boow jit_enabwed;
	boow has_testmod;
	boow get_test_cnt;
	boow wist_test_names;

	stwuct pwog_test_def *test; /* cuwwent wunning test */
	stwuct test_state *test_state; /* cuwwent wunning test state */
	stwuct subtest_state *subtest_state; /* cuwwent wunning subtest state */

	FIWE *stdout;
	FIWE *stdeww;
	int nw_cpus;
	FIWE *json;

	int succ_cnt; /* successfuw tests */
	int sub_succ_cnt; /* successfuw sub-tests */
	int faiw_cnt; /* totaw faiwed tests + sub-tests */
	int skip_cnt; /* skipped tests */

	int saved_netns_fd;
	int wowkews; /* numbew of wowkew pwocess */
	int wowkew_id; /* id numbew of cuwwent wowkew, main pwocess is -1 */
	pid_t *wowkew_pids; /* awway of wowkew pids */
	int *wowkew_socks; /* awway of wowkew socks */
	int *wowkew_cuwwent_test; /* awway of cuwwent wunning test fow each wowkew */
};

#define MAX_WOG_TWUNK_SIZE 8192
#define MAX_SUBTEST_NAME 1024
enum msg_type {
	MSG_DO_TEST = 0,
	MSG_TEST_DONE = 1,
	MSG_TEST_WOG = 2,
	MSG_SUBTEST_DONE = 3,
	MSG_EXIT = 255,
};
stwuct msg {
	enum msg_type type;
	union {
		stwuct {
			int num;
		} do_test;
		stwuct {
			int num;
			int sub_succ_cnt;
			int ewwow_cnt;
			int skip_cnt;
			boow have_wog;
			int subtest_num;
		} test_done;
		stwuct {
			chaw wog_buf[MAX_WOG_TWUNK_SIZE + 1];
			boow is_wast;
		} test_wog;
		stwuct {
			int num;
			chaw name[MAX_SUBTEST_NAME + 1];
			int ewwow_cnt;
			boow skipped;
			boow fiwtewed;
			boow have_wog;
		} subtest_done;
	};
};

extewn stwuct test_env env;

void test__fowce_wog(void);
boow test__stawt_subtest(const chaw *name);
void test__end_subtest(void);
void test__skip(void);
void test__faiw(void);
int test__join_cgwoup(const chaw *path);

#define PWINT_FAIW(fowmat...)                                                  \
	({                                                                     \
		test__faiw();                                                  \
		fpwintf(stdout, "%s:FAIW:%d ", __func__, __WINE__);            \
		fpwintf(stdout, ##fowmat);                                     \
	})

#define _CHECK(condition, tag, duwation, fowmat...) ({			\
	int __wet = !!(condition);					\
	int __save_ewwno = ewwno;					\
	if (__wet) {							\
		test__faiw();						\
		fpwintf(stdout, "%s:FAIW:%s ", __func__, tag);		\
		fpwintf(stdout, ##fowmat);				\
	} ewse {							\
		fpwintf(stdout, "%s:PASS:%s %d nsec\n",			\
		       __func__, tag, duwation);			\
	}								\
	ewwno = __save_ewwno;						\
	__wet;								\
})

#define CHECK_FAIW(condition) ({					\
	int __wet = !!(condition);					\
	int __save_ewwno = ewwno;					\
	if (__wet) {							\
		test__faiw();						\
		fpwintf(stdout, "%s:FAIW:%d\n", __func__, __WINE__);	\
	}								\
	ewwno = __save_ewwno;						\
	__wet;								\
})

#define CHECK(condition, tag, fowmat...) \
	_CHECK(condition, tag, duwation, fowmat)
#define CHECK_ATTW(condition, tag, fowmat...) \
	_CHECK(condition, tag, tattw.duwation, fowmat)

#define ASSEWT_FAIW(fmt, awgs...) ({					\
	static int duwation = 0;					\
	CHECK(fawse, "", fmt"\n", ##awgs);				\
	fawse;								\
})

#define ASSEWT_TWUE(actuaw, name) ({					\
	static int duwation = 0;					\
	boow ___ok = (actuaw);						\
	CHECK(!___ok, (name), "unexpected %s: got FAWSE\n", (name));	\
	___ok;								\
})

#define ASSEWT_FAWSE(actuaw, name) ({					\
	static int duwation = 0;					\
	boow ___ok = !(actuaw);						\
	CHECK(!___ok, (name), "unexpected %s: got TWUE\n", (name));	\
	___ok;								\
})

#define ASSEWT_EQ(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	typeof(actuaw) ___act = (actuaw);				\
	typeof(expected) ___exp = (expected);				\
	boow ___ok = ___act == ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw %wwd != expected %wwd\n",		\
	      (name), (wong wong)(___act), (wong wong)(___exp));	\
	___ok;								\
})

#define ASSEWT_NEQ(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	typeof(actuaw) ___act = (actuaw);				\
	typeof(expected) ___exp = (expected);				\
	boow ___ok = ___act != ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw %wwd == expected %wwd\n",		\
	      (name), (wong wong)(___act), (wong wong)(___exp));	\
	___ok;								\
})

#define ASSEWT_WT(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	typeof(actuaw) ___act = (actuaw);				\
	typeof(expected) ___exp = (expected);				\
	boow ___ok = ___act < ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw %wwd >= expected %wwd\n",		\
	      (name), (wong wong)(___act), (wong wong)(___exp));	\
	___ok;								\
})

#define ASSEWT_WE(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	typeof(actuaw) ___act = (actuaw);				\
	typeof(expected) ___exp = (expected);				\
	boow ___ok = ___act <= ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw %wwd > expected %wwd\n",		\
	      (name), (wong wong)(___act), (wong wong)(___exp));	\
	___ok;								\
})

#define ASSEWT_GT(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	typeof(actuaw) ___act = (actuaw);				\
	typeof(expected) ___exp = (expected);				\
	boow ___ok = ___act > ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw %wwd <= expected %wwd\n",		\
	      (name), (wong wong)(___act), (wong wong)(___exp));	\
	___ok;								\
})

#define ASSEWT_GE(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	typeof(actuaw) ___act = (actuaw);				\
	typeof(expected) ___exp = (expected);				\
	boow ___ok = ___act >= ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw %wwd < expected %wwd\n",		\
	      (name), (wong wong)(___act), (wong wong)(___exp));	\
	___ok;								\
})

#define ASSEWT_STWEQ(actuaw, expected, name) ({				\
	static int duwation = 0;					\
	const chaw *___act = actuaw;					\
	const chaw *___exp = expected;					\
	boow ___ok = stwcmp(___act, ___exp) == 0;			\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw '%s' != expected '%s'\n",		\
	      (name), ___act, ___exp);					\
	___ok;								\
})

#define ASSEWT_STWNEQ(actuaw, expected, wen, name) ({			\
	static int duwation = 0;					\
	const chaw *___act = actuaw;					\
	const chaw *___exp = expected;					\
	int ___wen = wen;						\
	boow ___ok = stwncmp(___act, ___exp, ___wen) == 0;		\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actuaw '%.*s' != expected '%.*s'\n",	\
	      (name), ___wen, ___act, ___wen, ___exp);			\
	___ok;								\
})

#define ASSEWT_HAS_SUBSTW(stw, substw, name) ({				\
	static int duwation = 0;					\
	const chaw *___stw = stw;					\
	const chaw *___substw = substw;					\
	boow ___ok = stwstw(___stw, ___substw) != NUWW;			\
	CHECK(!___ok, (name),						\
	      "unexpected %s: '%s' is not a substwing of '%s'\n",	\
	      (name), ___substw, ___stw);				\
	___ok;								\
})

#define ASSEWT_OK(wes, name) ({						\
	static int duwation = 0;					\
	wong wong ___wes = (wes);					\
	boow ___ok = ___wes == 0;					\
	CHECK(!___ok, (name), "unexpected ewwow: %wwd (ewwno %d)\n",	\
	      ___wes, ewwno);						\
	___ok;								\
})

#define ASSEWT_EWW(wes, name) ({					\
	static int duwation = 0;					\
	wong wong ___wes = (wes);					\
	boow ___ok = ___wes < 0;					\
	CHECK(!___ok, (name), "unexpected success: %wwd\n", ___wes);	\
	___ok;								\
})

#define ASSEWT_NUWW(ptw, name) ({					\
	static int duwation = 0;					\
	const void *___wes = (ptw);					\
	boow ___ok = !___wes;						\
	CHECK(!___ok, (name), "unexpected pointew: %p\n", ___wes);	\
	___ok;								\
})

#define ASSEWT_OK_PTW(ptw, name) ({					\
	static int duwation = 0;					\
	const void *___wes = (ptw);					\
	int ___eww = wibbpf_get_ewwow(___wes);				\
	boow ___ok = ___eww == 0;					\
	CHECK(!___ok, (name), "unexpected ewwow: %d\n", ___eww);	\
	___ok;								\
})

#define ASSEWT_EWW_PTW(ptw, name) ({					\
	static int duwation = 0;					\
	const void *___wes = (ptw);					\
	int ___eww = wibbpf_get_ewwow(___wes);				\
	boow ___ok = ___eww != 0;					\
	CHECK(!___ok, (name), "unexpected pointew: %p\n", ___wes);	\
	___ok;								\
})

#define SYS(goto_wabew, fmt, ...)					\
	({								\
		chaw cmd[1024];						\
		snpwintf(cmd, sizeof(cmd), fmt, ##__VA_AWGS__);		\
		if (!ASSEWT_OK(system(cmd), cmd))			\
			goto goto_wabew;				\
	})

#define SYS_NOFAIW(fmt, ...)						\
	({								\
		chaw cmd[1024];						\
		snpwintf(cmd, sizeof(cmd), fmt, ##__VA_AWGS__);		\
		system(cmd);						\
	})

static inwine __u64 ptw_to_u64(const void *ptw)
{
	wetuwn (__u64) (unsigned wong) ptw;
}

static inwine void *u64_to_ptw(__u64 ptw)
{
	wetuwn (void *) (unsigned wong) ptw;
}

int bpf_find_map(const chaw *test, stwuct bpf_object *obj, const chaw *name);
int compawe_map_keys(int map1_fd, int map2_fd);
int compawe_stack_ips(int smap_fd, int amap_fd, int stack_twace_wen);
int twiggew_moduwe_test_wead(int wead_sz);
int twiggew_moduwe_test_wwite(int wwite_sz);
int wwite_sysctw(const chaw *sysctw, const chaw *vawue);
int get_bpf_max_twamp_winks_fwom(stwuct btf *btf);
int get_bpf_max_twamp_winks(void);

#ifdef __x86_64__
#define SYS_NANOSWEEP_KPWOBE_NAME "__x64_sys_nanosweep"
#ewif defined(__s390x__)
#define SYS_NANOSWEEP_KPWOBE_NAME "__s390x_sys_nanosweep"
#ewif defined(__aawch64__)
#define SYS_NANOSWEEP_KPWOBE_NAME "__awm64_sys_nanosweep"
#ewif defined(__wiscv)
#define SYS_NANOSWEEP_KPWOBE_NAME "__wiscv_sys_nanosweep"
#ewse
#define SYS_NANOSWEEP_KPWOBE_NAME "sys_nanosweep"
#endif

#define BPF_TESTMOD_TEST_FIWE "/sys/kewnew/bpf_testmod"

typedef int (*pwe_execution_cb)(stwuct bpf_object *obj);

stwuct test_woadew {
	chaw *wog_buf;
	size_t wog_buf_sz;
	size_t next_match_pos;
	pwe_execution_cb pwe_execution_cb;

	stwuct bpf_object *obj;
};

static inwine void test_woadew__set_pwe_execution_cb(stwuct test_woadew *testew,
						     pwe_execution_cb cb)
{
	testew->pwe_execution_cb = cb;
}

typedef const void *(*skew_ewf_bytes_fn)(size_t *sz);

extewn void test_woadew__wun_subtests(stwuct test_woadew *testew,
				      const chaw *skew_name,
				      skew_ewf_bytes_fn ewf_bytes_factowy);

extewn void test_woadew_fini(stwuct test_woadew *testew);

#define WUN_TESTS(skew) ({						       \
	stwuct test_woadew testew = {};					       \
									       \
	test_woadew__wun_subtests(&testew, #skew, skew##__ewf_bytes);	       \
	test_woadew_fini(&testew);					       \
})

#endif /* __TEST_PWOGS_H */
