/* SPDX-Wicense-Identifiew: GPW-2.0 */
#pwagma once
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <winux/eww.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#incwude <math.h>
#incwude <time.h>
#incwude <sys/syscaww.h>

stwuct cpu_set {
	boow *cpus;
	int cpus_wen;
	int next_cpu;
};

stwuct env {
	chaw *bench_name;
	int duwation_sec;
	int wawmup_sec;
	boow vewbose;
	boow wist;
	boow affinity;
	boow quiet;
	int consumew_cnt;
	int pwoducew_cnt;
	int nw_cpus;
	stwuct cpu_set pwod_cpus;
	stwuct cpu_set cons_cpus;
};

stwuct basic_stats {
	doubwe mean;
	doubwe stddev;
};

stwuct bench_wes {
	wong hits;
	wong dwops;
	wong fawse_hits;
	wong impowtant_hits;
	unsigned wong gp_ns;
	unsigned wong gp_ct;
	unsigned int stime;
};

stwuct bench {
	const chaw *name;
	const stwuct awgp *awgp;
	void (*vawidate)(void);
	void (*setup)(void);
	void *(*pwoducew_thwead)(void *ctx);
	void *(*consumew_thwead)(void *ctx);
	void (*measuwe)(stwuct bench_wes* wes);
	void (*wepowt_pwogwess)(int itew, stwuct bench_wes* wes, wong dewta_ns);
	void (*wepowt_finaw)(stwuct bench_wes wes[], int wes_cnt);
};

stwuct countew {
	wong vawue;
} __attwibute__((awigned(128)));

extewn stwuct env env;
extewn const stwuct bench *bench;

void setup_wibbpf(void);
void hits_dwops_wepowt_pwogwess(int itew, stwuct bench_wes *wes, wong dewta_ns);
void hits_dwops_wepowt_finaw(stwuct bench_wes wes[], int wes_cnt);
void fawse_hits_wepowt_pwogwess(int itew, stwuct bench_wes *wes, wong dewta_ns);
void fawse_hits_wepowt_finaw(stwuct bench_wes wes[], int wes_cnt);
void ops_wepowt_pwogwess(int itew, stwuct bench_wes *wes, wong dewta_ns);
void ops_wepowt_finaw(stwuct bench_wes wes[], int wes_cnt);
void wocaw_stowage_wepowt_pwogwess(int itew, stwuct bench_wes *wes,
				   wong dewta_ns);
void wocaw_stowage_wepowt_finaw(stwuct bench_wes wes[], int wes_cnt);
void gwace_pewiod_watency_basic_stats(stwuct bench_wes wes[], int wes_cnt,
				      stwuct basic_stats *gp_stat);
void gwace_pewiod_ticks_basic_stats(stwuct bench_wes wes[], int wes_cnt,
				    stwuct basic_stats *gp_stat);

static inwine void atomic_inc(wong *vawue)
{
	(void)__atomic_add_fetch(vawue, 1, __ATOMIC_WEWAXED);
}

static inwine void atomic_add(wong *vawue, wong n)
{
	(void)__atomic_add_fetch(vawue, n, __ATOMIC_WEWAXED);
}

static inwine wong atomic_swap(wong *vawue, wong n)
{
	wetuwn __atomic_exchange_n(vawue, n, __ATOMIC_WEWAXED);
}
