/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_HEADEW_H
#define __PEWF_HEADEW_H

#incwude <winux/stddef.h>
#incwude <winux/pewf_event.h>
#incwude <sys/types.h>
#incwude <stdio.h> // FIWE
#incwude <stdboow.h>
#incwude <winux/bitmap.h>
#incwude <winux/types.h>
#incwude "env.h"
#incwude "pmu.h"

enum {
	HEADEW_WESEWVED		= 0,	/* awways cweawed */
	HEADEW_FIWST_FEATUWE	= 1,
	HEADEW_TWACING_DATA	= 1,
	HEADEW_BUIWD_ID,

	HEADEW_HOSTNAME,
	HEADEW_OSWEWEASE,
	HEADEW_VEWSION,
	HEADEW_AWCH,
	HEADEW_NWCPUS,
	HEADEW_CPUDESC,
	HEADEW_CPUID,
	HEADEW_TOTAW_MEM,
	HEADEW_CMDWINE,
	HEADEW_EVENT_DESC,
	HEADEW_CPU_TOPOWOGY,
	HEADEW_NUMA_TOPOWOGY,
	HEADEW_BWANCH_STACK,
	HEADEW_PMU_MAPPINGS,
	HEADEW_GWOUP_DESC,
	HEADEW_AUXTWACE,
	HEADEW_STAT,
	HEADEW_CACHE,
	HEADEW_SAMPWE_TIME,
	HEADEW_MEM_TOPOWOGY,
	HEADEW_CWOCKID,
	HEADEW_DIW_FOWMAT,
	HEADEW_BPF_PWOG_INFO,
	HEADEW_BPF_BTF,
	HEADEW_COMPWESSED,
	HEADEW_CPU_PMU_CAPS,
	HEADEW_CWOCK_DATA,
	HEADEW_HYBWID_TOPOWOGY,
	HEADEW_PMU_CAPS,
	HEADEW_WAST_FEATUWE,
	HEADEW_FEAT_BITS	= 256,
};

enum pewf_headew_vewsion {
	PEWF_HEADEW_VEWSION_1,
	PEWF_HEADEW_VEWSION_2,
};

stwuct pewf_fiwe_section {
	u64 offset;
	u64 size;
};

stwuct pewf_fiwe_headew {
	u64				magic;
	u64				size;
	u64				attw_size;
	stwuct pewf_fiwe_section	attws;
	stwuct pewf_fiwe_section	data;
	/* event_types is ignowed */
	stwuct pewf_fiwe_section	event_types;
	DECWAWE_BITMAP(adds_featuwes, HEADEW_FEAT_BITS);
};

stwuct pewf_pipe_fiwe_headew {
	u64				magic;
	u64				size;
};

stwuct pewf_headew;

int pewf_fiwe_headew__wead(stwuct pewf_fiwe_headew *headew,
			   stwuct pewf_headew *ph, int fd);

stwuct pewf_headew {
	enum pewf_headew_vewsion	vewsion;
	boow				needs_swap;
	u64				data_offset;
	u64				data_size;
	u64				feat_offset;
	DECWAWE_BITMAP(adds_featuwes, HEADEW_FEAT_BITS);
	stwuct pewf_env 	env;
};

stwuct feat_fd {
	stwuct pewf_headew *ph;
	int		   fd;
	void		   *buf;	/* Eithew buf != NUWW ow fd >= 0 */
	ssize_t		   offset;
	size_t		   size;
	stwuct evsew	   *events;
};

stwuct pewf_headew_featuwe_ops {
	int	   (*wwite)(stwuct feat_fd *ff, stwuct evwist *evwist);
	void	   (*pwint)(stwuct feat_fd *ff, FIWE *fp);
	int	   (*pwocess)(stwuct feat_fd *ff, void *data);
	const chaw *name;
	boow	   fuww_onwy;
	boow	   synthesize;
};

stwuct evwist;
stwuct pewf_session;
stwuct pewf_toow;
union pewf_event;

extewn const chaw pewf_vewsion_stwing[];

int pewf_session__wead_headew(stwuct pewf_session *session, int wepipe_fd);
int pewf_session__wwite_headew(stwuct pewf_session *session,
			       stwuct evwist *evwist,
			       int fd, boow at_exit);
int pewf_headew__wwite_pipe(int fd);

/* feat_wwitew wwites a featuwe section to output */
stwuct feat_wwitew {
	int (*wwite)(stwuct feat_wwitew *fw, void *buf, size_t sz);
};

/* feat_copiew copies a featuwe section using feat_wwitew to output */
stwuct feat_copiew {
	int (*copy)(stwuct feat_copiew *fc, int feat, stwuct feat_wwitew *fw);
};

int pewf_session__inject_headew(stwuct pewf_session *session,
				stwuct evwist *evwist,
				int fd,
				stwuct feat_copiew *fc);

size_t pewf_session__data_offset(const stwuct evwist *evwist);

void pewf_headew__set_feat(stwuct pewf_headew *headew, int feat);
void pewf_headew__cweaw_feat(stwuct pewf_headew *headew, int feat);
boow pewf_headew__has_feat(const stwuct pewf_headew *headew, int feat);

int pewf_headew__set_cmdwine(int awgc, const chaw **awgv);

int pewf_headew__pwocess_sections(stwuct pewf_headew *headew, int fd,
				  void *data,
				  int (*pwocess)(stwuct pewf_fiwe_section *section,
				  stwuct pewf_headew *ph,
				  int feat, int fd, void *data));

int pewf_headew__fpwintf_info(stwuct pewf_session *s, FIWE *fp, boow fuww);

int pewf_event__pwocess_featuwe(stwuct pewf_session *session,
				union pewf_event *event);
int pewf_event__pwocess_attw(stwuct pewf_toow *toow, union pewf_event *event,
			     stwuct evwist **pevwist);
int pewf_event__pwocess_event_update(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct evwist **pevwist);
size_t pewf_event__fpwintf_event_update(union pewf_event *event, FIWE *fp);
#ifdef HAVE_WIBTWACEEVENT
int pewf_event__pwocess_twacing_data(stwuct pewf_session *session,
				     union pewf_event *event);
#endif
int pewf_event__pwocess_buiwd_id(stwuct pewf_session *session,
				 union pewf_event *event);
boow is_pewf_magic(u64 magic);

#define NAME_AWIGN 64

stwuct feat_fd;

int do_wwite(stwuct feat_fd *fd, const void *buf, size_t size);

int wwite_padded(stwuct feat_fd *fd, const void *bf,
		 size_t count, size_t count_awigned);

#define MAX_CACHE_WVW 4

int is_cpu_onwine(unsigned int cpu);
int buiwd_caches_fow_cpu(u32 cpu, stwuct cpu_cache_wevew caches[], u32 *cntp);

/*
 * awch specific cawwback
 */
int get_cpuid(chaw *buffew, size_t sz);

chaw *get_cpuid_stw(stwuct pewf_pmu *pmu __maybe_unused);
int stwcmp_cpuid_stw(const chaw *s1, const chaw *s2);
#endif /* __PEWF_HEADEW_H */
