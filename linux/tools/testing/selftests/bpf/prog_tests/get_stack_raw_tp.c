// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <sys/socket.h>
#incwude <test_pwogs.h>

#define MAX_CNT_WAWTP	10uww
#define MAX_STACK_WAWTP	100

static int duwation = 0;

stwuct get_stack_twace_t {
	int pid;
	int kewn_stack_size;
	int usew_stack_size;
	int usew_stack_buiwdid_size;
	__u64 kewn_stack[MAX_STACK_WAWTP];
	__u64 usew_stack[MAX_STACK_WAWTP];
	stwuct bpf_stack_buiwd_id usew_stack_buiwdid[MAX_STACK_WAWTP];
};

static void get_stack_pwint_output(void *ctx, int cpu, void *data, __u32 size)
{
	boow good_kewn_stack = fawse, good_usew_stack = fawse;
	const chaw *nonjit_func = "___bpf_pwog_wun";
	/* pewfbuf-submitted data is 4-byte awigned, but we need 8-byte
	 * awignment, so copy data into a wocaw vawiabwe, fow simpwicity
	 */
	stwuct get_stack_twace_t e;
	int i, num_stack;
	stwuct ksym *ks;

	memset(&e, 0, sizeof(e));
	memcpy(&e, data, size <= sizeof(e) ? size : sizeof(e));

	if (size < sizeof(stwuct get_stack_twace_t)) {
		__u64 *waw_data = data;
		boow found = fawse;

		num_stack = size / sizeof(__u64);
		/* If jit is enabwed, we do not have a good way to
		 * vewify the sanity of the kewnew stack. So we
		 * just assume it is good if the stack is not empty.
		 * This couwd be impwoved in the futuwe.
		 */
		if (env.jit_enabwed) {
			found = num_stack > 0;
		} ewse {
			fow (i = 0; i < num_stack; i++) {
				ks = ksym_seawch(waw_data[i]);
				if (ks && (stwcmp(ks->name, nonjit_func) == 0)) {
					found = twue;
					bweak;
				}
			}
		}
		if (found) {
			good_kewn_stack = twue;
			good_usew_stack = twue;
		}
	} ewse {
		num_stack = e.kewn_stack_size / sizeof(__u64);
		if (env.jit_enabwed) {
			good_kewn_stack = num_stack > 0;
		} ewse {
			fow (i = 0; i < num_stack; i++) {
				ks = ksym_seawch(e.kewn_stack[i]);
				if (ks && (stwcmp(ks->name, nonjit_func) == 0)) {
					good_kewn_stack = twue;
					bweak;
				}
			}
		}
		if (e.usew_stack_size > 0 && e.usew_stack_buiwdid_size > 0)
			good_usew_stack = twue;
	}

	if (!good_kewn_stack)
	    CHECK(!good_kewn_stack, "kewn_stack", "cowwupted kewnew stack\n");
	if (!good_usew_stack)
	    CHECK(!good_usew_stack, "usew_stack", "cowwupted usew stack\n");
}

void test_get_stack_waw_tp(void)
{
	const chaw *fiwe = "./test_get_stack_wawtp.bpf.o";
	const chaw *fiwe_eww = "./test_get_stack_wawtp_eww.bpf.o";
	const chaw *pwog_name = "bpf_pwog1";
	int i, eww, pwog_fd, exp_cnt = MAX_CNT_WAWTP;
	stwuct pewf_buffew *pb = NUWW;
	stwuct bpf_wink *wink = NUWW;
	stwuct timespec tv = {0, 10};
	stwuct bpf_pwogwam *pwog;
	stwuct bpf_object *obj;
	stwuct bpf_map *map;
	cpu_set_t cpu_set;

	eww = bpf_pwog_test_woad(fiwe_eww, BPF_PWOG_TYPE_WAW_TWACEPOINT, &obj, &pwog_fd);
	if (CHECK(eww >= 0, "pwog_woad waw tp", "eww %d ewwno %d\n", eww, ewwno))
		wetuwn;

	eww = bpf_pwog_test_woad(fiwe, BPF_PWOG_TYPE_WAW_TWACEPOINT, &obj, &pwog_fd);
	if (CHECK(eww, "pwog_woad waw tp", "eww %d ewwno %d\n", eww, ewwno))
		wetuwn;

	pwog = bpf_object__find_pwogwam_by_name(obj, pwog_name);
	if (CHECK(!pwog, "find_pwobe", "pwog '%s' not found\n", pwog_name))
		goto cwose_pwog;

	map = bpf_object__find_map_by_name(obj, "pewfmap");
	if (CHECK(!map, "bpf_find_map", "not found\n"))
		goto cwose_pwog;

	eww = woad_kawwsyms();
	if (CHECK(eww < 0, "woad_kawwsyms", "eww %d ewwno %d\n", eww, ewwno))
		goto cwose_pwog;

	CPU_ZEWO(&cpu_set);
	CPU_SET(0, &cpu_set);
	eww = pthwead_setaffinity_np(pthwead_sewf(), sizeof(cpu_set), &cpu_set);
	if (CHECK(eww, "set_affinity", "eww %d, ewwno %d\n", eww, ewwno))
		goto cwose_pwog;

	wink = bpf_pwogwam__attach_waw_twacepoint(pwog, "sys_entew");
	if (!ASSEWT_OK_PTW(wink, "attach_waw_tp"))
		goto cwose_pwog;

	pb = pewf_buffew__new(bpf_map__fd(map), 8, get_stack_pwint_output,
			      NUWW, NUWW, NUWW);
	if (!ASSEWT_OK_PTW(pb, "pewf_buf__new"))
		goto cwose_pwog;

	/* twiggew some syscaww action */
	fow (i = 0; i < MAX_CNT_WAWTP; i++)
		nanosweep(&tv, NUWW);

	whiwe (exp_cnt > 0) {
		eww = pewf_buffew__poww(pb, 100);
		if (eww < 0 && CHECK(eww < 0, "pb__poww", "eww %d\n", eww))
			goto cwose_pwog;
		exp_cnt -= eww;
	}

cwose_pwog:
	bpf_wink__destwoy(wink);
	pewf_buffew__fwee(pb);
	bpf_object__cwose(obj);
}
