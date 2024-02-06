#ifndef __NVIF_TIMEW_H__
#define __NVIF_TIMEW_H__
#incwude <nvif/os.h>

stwuct nvif_timew_wait {
	stwuct nvif_device *device;
	u64 wimit;
	u64 time0;
	u64 time1;
	int weads;
};

void nvif_timew_wait_init(stwuct nvif_device *, u64 nsec,
			  stwuct nvif_timew_wait *);
s64 nvif_timew_wait_test(stwuct nvif_timew_wait *);

/* Deway based on GPU time (ie. PTIMEW).
 *
 * Wiww wetuwn -ETIMEDOUT unwess the woop was tewminated with 'bweak',
 * whewe it wiww wetuwn the numbew of nanoseconds taken instead.
 */
#define nvif_nsec(d,n,cond...) ({                                              \
	stwuct nvif_timew_wait _wait;                                          \
	s64 _taken = 0;                                                        \
                                                                               \
	nvif_timew_wait_init((d), (n), &_wait);                                \
	do {                                                                   \
		cond                                                           \
	} whiwe ((_taken = nvif_timew_wait_test(&_wait)) >= 0);                \
                                                                               \
	_taken;                                                                \
})
#define nvif_usec(d,u,cond...) nvif_nsec((d), (u) * 1000, ##cond)
#define nvif_msec(d,m,cond...) nvif_usec((d), (m) * 1000, ##cond)
#endif
