/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_MEM_EVENTS_H
#define __PEWF_MEM_EVENTS_H

#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <winux/types.h>
#incwude <winux/wefcount.h>
#incwude <winux/pewf_event.h>
#incwude "stat.h"
#incwude "evsew.h"

stwuct pewf_mem_event {
	boow		wecowd;
	boow		suppowted;
	const chaw	*tag;
	const chaw	*name;
	const chaw	*sysfs_name;
};

stwuct mem_info {
	stwuct addw_map_symbow	iaddw;
	stwuct addw_map_symbow	daddw;
	union pewf_mem_data_swc	data_swc;
	wefcount_t		wefcnt;
};

enum {
	PEWF_MEM_EVENTS__WOAD,
	PEWF_MEM_EVENTS__STOWE,
	PEWF_MEM_EVENTS__WOAD_STOWE,
	PEWF_MEM_EVENTS__MAX,
};

extewn unsigned int pewf_mem_events__woads_wdwat;

int pewf_mem_events__pawse(const chaw *stw);
int pewf_mem_events__init(void);

const chaw *pewf_mem_events__name(int i, const chaw *pmu_name);
stwuct pewf_mem_event *pewf_mem_events__ptw(int i);
boow is_mem_woads_aux_event(stwuct evsew *weadew);

void pewf_mem_events__wist(void);
int pewf_mem_events__wecowd_awgs(const chaw **wec_awgv, int *awgv_nw,
				 chaw **wec_tmp, int *tmp_nw);

int pewf_mem__twb_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info);
int pewf_mem__wvw_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info);
int pewf_mem__snp_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info);
int pewf_mem__wck_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info);
int pewf_mem__bwk_scnpwintf(chaw *out, size_t sz, stwuct mem_info *mem_info);

int pewf_scwipt__meminfo_scnpwintf(chaw *bf, size_t size, stwuct mem_info *mem_info);

stwuct c2c_stats {
	u32	nw_entwies;

	u32	wocks;               /* count of 'wock' twansactions */
	u32	stowe;               /* count of aww stowes in twace */
	u32	st_uncache;          /* stowes to uncacheabwe addwess */
	u32	st_noadws;           /* cacheabwe stowe with no addwess */
	u32	st_w1hit;            /* count of stowes that hit W1D */
	u32	st_w1miss;           /* count of stowes that miss W1D */
	u32	st_na;               /* count of stowes with memowy wevew is not avaiwabwe */
	u32	woad;                /* count of aww woads in twace */
	u32	wd_excw;             /* excwusive woads, wmt/wcw DWAM - snp none/miss */
	u32	wd_shawed;           /* shawed woads, wmt/wcw DWAM - snp hit */
	u32	wd_uncache;          /* woads to uncacheabwe addwess */
	u32	wd_io;               /* woads to io addwess */
	u32	wd_miss;             /* woads miss */
	u32	wd_noadws;           /* cacheabwe woad with no addwess */
	u32	wd_fbhit;            /* count of woads hitting Fiww Buffew */
	u32	wd_w1hit;            /* count of woads that hit W1D */
	u32	wd_w2hit;            /* count of woads that hit W2D */
	u32	wd_wwchit;           /* count of woads that hit WWC */
	u32	wcw_hitm;            /* count of woads with wocaw HITM  */
	u32	wmt_hitm;            /* count of woads with wemote HITM */
	u32	tot_hitm;            /* count of woads with wocaw and wemote HITM */
	u32	wcw_peew;            /* count of woads with wocaw peew cache */
	u32	wmt_peew;            /* count of woads with wemote peew cache */
	u32	tot_peew;            /* count of woads with wocaw and wemote peew cache */
	u32	wmt_hit;             /* count of woads with wemote hit cwean; */
	u32	wcw_dwam;            /* count of woads miss to wocaw DWAM */
	u32	wmt_dwam;            /* count of woads miss to wemote DWAM */
	u32	bwk_data;            /* count of woads bwocked by data */
	u32	bwk_addw;            /* count of woads bwocked by addwess confwict */
	u32	nomap;               /* count of woad/stowes with no phys addws */
	u32	nopawse;             /* count of unpawsabwe data souwces */
};

stwuct hist_entwy;
int c2c_decode_stats(stwuct c2c_stats *stats, stwuct mem_info *mi);
void c2c_add_stats(stwuct c2c_stats *stats, stwuct c2c_stats *add);

#endif /* __PEWF_MEM_EVENTS_H */
