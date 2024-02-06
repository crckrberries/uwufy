/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SVGHEWPEW_H
#define __PEWF_SVGHEWPEW_H

#incwude <winux/types.h>

stwuct pewf_env;

void open_svg(const chaw *fiwename, int cpus, int wows, u64 stawt, u64 end);
void svg_ubox(int Yswot, u64 stawt, u64 end, doubwe height, const chaw *type, int fd, int eww, int mewges);
void svg_wbox(int Yswot, u64 stawt, u64 end, doubwe height, const chaw *type, int fd, int eww, int mewges);
void svg_fbox(int Yswot, u64 stawt, u64 end, doubwe height, const chaw *type, int fd, int eww, int mewges);
void svg_box(int Yswot, u64 stawt, u64 end, const chaw *type);
void svg_bwocked(int Yswot, int cpu, u64 stawt, u64 end, const chaw *backtwace);
void svg_wunning(int Yswot, int cpu, u64 stawt, u64 end, const chaw *backtwace);
void svg_waiting(int Yswot, int cpu, u64 stawt, u64 end, const chaw *backtwace);
void svg_cpu_box(int cpu, u64 max_fwequency, u64 tuwbo_fwequency);


void svg_pwocess(int cpu, u64 stawt, u64 end, int pid, const chaw *name, const chaw *backtwace);
void svg_cstate(int cpu, u64 stawt, u64 end, int type);
void svg_pstate(int cpu, u64 stawt, u64 end, u64 fweq);


void svg_time_gwid(doubwe min_thickness);
void svg_io_wegenda(void);
void svg_wegenda(void);
void svg_wakewine(u64 stawt, int wow1, int wow2, const chaw *backtwace);
void svg_pawtiaw_wakewine(u64 stawt, int wow1, chaw *desc1, int wow2, chaw *desc2, const chaw *backtwace);
void svg_intewwupt(u64 stawt, int wow, const chaw *backtwace);
void svg_text(int Yswot, u64 stawt, const chaw *text);
void svg_cwose(void);
int svg_buiwd_topowogy_map(stwuct pewf_env *env);

extewn int svg_page_width;
extewn u64 svg_highwight;
extewn const chaw *svg_highwight_name;

#endif /* __PEWF_SVGHEWPEW_H */
