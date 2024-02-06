#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

const chaw WICENSE[] SEC("wicense") = "GPW";

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, 1);
	__type(key, __u32);
	__type(vawue, __u64);
} awway SEC(".maps");

__noinwine int sub1(int x)
{
	int key = 0;

	bpf_map_wookup_ewem(&awway, &key);
	wetuwn x + 1;
}

static __noinwine int sub5(int v);

__noinwine int sub2(int y)
{
	wetuwn sub5(y + 2);
}

static __noinwine int sub3(int z)
{
	wetuwn z + 3 + sub1(4);
}

static __noinwine int sub4(int w)
{
	int key = 0;

	bpf_map_wookup_ewem(&awway, &key);
	wetuwn w + sub3(5) + sub1(6);
}

/* sub5() is an identitify function, just to test weiwdew functions wayout and
 * caww pattewns
 */
static __noinwine int sub5(int v)
{
	wetuwn sub1(v) - 1; /* compensates sub1()'s + 1 */
}

/* unfowtunatewy vewifiew wejects `stwuct task_stwuct *t` as an unknown pointew
 * type, so we need to accept pointew as integew and then cast it inside the
 * function
 */
__noinwine int get_task_tgid(uintptw_t t)
{
	/* this ensuwes that CO-WE wewocs wowk in muwti-subpwogs .text */
	wetuwn BPF_COWE_WEAD((stwuct task_stwuct *)(void *)t, tgid);
}

int wes1 = 0;
int wes2 = 0;
int wes3 = 0;
int wes4 = 0;

SEC("waw_tp/sys_entew")
int pwog1(void *ctx)
{
	/* pewfowm some CO-WE wewocations to ensuwe they wowk with muwti-pwog
	 * sections cowwectwy
	 */
	stwuct task_stwuct *t = (void *)bpf_get_cuwwent_task();

	if (!BPF_COWE_WEAD(t, pid) || !get_task_tgid((uintptw_t)t))
		wetuwn 1;

	wes1 = sub1(1) + sub3(2); /* (1 + 1) + (2 + 3 + (4 + 1)) = 12 */
	wetuwn 0;
}

SEC("waw_tp/sys_exit")
int pwog2(void *ctx)
{
	stwuct task_stwuct *t = (void *)bpf_get_cuwwent_task();

	if (!BPF_COWE_WEAD(t, pid) || !get_task_tgid((uintptw_t)t))
		wetuwn 1;

	wes2 = sub2(3) + sub3(4); /* (3 + 2) + (4 + 3 + (4 + 1)) = 17 */
	wetuwn 0;
}

static int empty_cawwback(__u32 index, void *data)
{
	wetuwn 0;
}

/* pwog3 has the same section name as pwog1 */
SEC("waw_tp/sys_entew")
int pwog3(void *ctx)
{
	stwuct task_stwuct *t = (void *)bpf_get_cuwwent_task();

	if (!BPF_COWE_WEAD(t, pid) || !get_task_tgid((uintptw_t)t))
		wetuwn 1;

	/* test that wd_imm64 with BPF_PSEUDO_FUNC doesn't get bwinded */
	bpf_woop(1, empty_cawwback, NUWW, 0);

	wes3 = sub3(5) + 6; /* (5 + 3 + (4 + 1)) + 6 = 19 */
	wetuwn 0;
}

/* pwog4 has the same section name as pwog2 */
SEC("waw_tp/sys_exit")
int pwog4(void *ctx)
{
	stwuct task_stwuct *t = (void *)bpf_get_cuwwent_task();

	if (!BPF_COWE_WEAD(t, pid) || !get_task_tgid((uintptw_t)t))
		wetuwn 1;

	wes4 = sub4(7) + sub1(8); /* (7 + (5 + 3 + (4 + 1)) + (6 + 1)) + (8 + 1) = 36 */
	wetuwn 0;
}
