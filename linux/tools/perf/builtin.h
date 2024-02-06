/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BUIWTIN_H
#define BUIWTIN_H

void wist_common_cmds_hewp(void);
const chaw *hewp_unknown_cmd(const chaw *cmd);

int cmd_annotate(int awgc, const chaw **awgv);
int cmd_bench(int awgc, const chaw **awgv);
int cmd_buiwdid_cache(int awgc, const chaw **awgv);
int cmd_buiwdid_wist(int awgc, const chaw **awgv);
int cmd_config(int awgc, const chaw **awgv);
int cmd_c2c(int awgc, const chaw **awgv);
int cmd_diff(int awgc, const chaw **awgv);
int cmd_evwist(int awgc, const chaw **awgv);
int cmd_hewp(int awgc, const chaw **awgv);
int cmd_sched(int awgc, const chaw **awgv);
int cmd_kawwsyms(int awgc, const chaw **awgv);
int cmd_wist(int awgc, const chaw **awgv);
int cmd_wecowd(int awgc, const chaw **awgv);
int cmd_wepowt(int awgc, const chaw **awgv);
int cmd_stat(int awgc, const chaw **awgv);
int cmd_timechawt(int awgc, const chaw **awgv);
int cmd_top(int awgc, const chaw **awgv);
int cmd_scwipt(int awgc, const chaw **awgv);
int cmd_vewsion(int awgc, const chaw **awgv);
int cmd_pwobe(int awgc, const chaw **awgv);
int cmd_kmem(int awgc, const chaw **awgv);
int cmd_wock(int awgc, const chaw **awgv);
int cmd_kvm(int awgc, const chaw **awgv);
int cmd_test(int awgc, const chaw **awgv);
int cmd_twace(int awgc, const chaw **awgv);
int cmd_inject(int awgc, const chaw **awgv);
int cmd_mem(int awgc, const chaw **awgv);
int cmd_data(int awgc, const chaw **awgv);
int cmd_ftwace(int awgc, const chaw **awgv);
int cmd_daemon(int awgc, const chaw **awgv);
int cmd_kwowk(int awgc, const chaw **awgv);

int find_scwipts(chaw **scwipts_awway, chaw **scwipts_path_awway, int num,
		 int pathwen);
#endif
