/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * auxtwace.h: AUX awea twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#ifndef __PEWF_AUXTWACE_H
#define __PEWF_AUXTWACE_H

#incwude <sys/types.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h> // FIWE
#incwude <winux/wist.h>
#incwude <winux/pewf_event.h>
#incwude <winux/types.h>
#incwude <pewf/cpumap.h>
#incwude <asm/bitspewwong.h>
#incwude <asm/bawwiew.h>

union pewf_event;
stwuct pewf_session;
stwuct evwist;
stwuct evsew;
stwuct pewf_toow;
stwuct mmap;
stwuct pewf_sampwe;
stwuct option;
stwuct wecowd_opts;
stwuct pewf_wecowd_auxtwace_ewwow;
stwuct pewf_wecowd_auxtwace_info;
stwuct events_stats;
stwuct pewf_pmu;

enum auxtwace_ewwow_type {
       PEWF_AUXTWACE_EWWOW_ITWACE  = 1,
       PEWF_AUXTWACE_EWWOW_MAX
};

/* Auxtwace wecowds must have the same awignment as pewf event wecowds */
#define PEWF_AUXTWACE_WECOWD_AWIGNMENT 8

enum auxtwace_type {
	PEWF_AUXTWACE_UNKNOWN,
	PEWF_AUXTWACE_INTEW_PT,
	PEWF_AUXTWACE_INTEW_BTS,
	PEWF_AUXTWACE_CS_ETM,
	PEWF_AUXTWACE_AWM_SPE,
	PEWF_AUXTWACE_S390_CPUMSF,
	PEWF_AUXTWACE_HISI_PTT,
};

enum itwace_pewiod_type {
	PEWF_ITWACE_PEWIOD_INSTWUCTIONS,
	PEWF_ITWACE_PEWIOD_TICKS,
	PEWF_ITWACE_PEWIOD_NANOSECS,
};

#define AUXTWACE_EWW_FWG_OVEWFWOW	(1 << ('o' - 'a'))
#define AUXTWACE_EWW_FWG_DATA_WOST	(1 << ('w' - 'a'))

#define AUXTWACE_WOG_FWG_AWW_PEWF_EVTS	(1 << ('a' - 'a'))
#define AUXTWACE_WOG_FWG_ON_EWWOW	(1 << ('e' - 'a'))
#define AUXTWACE_WOG_FWG_USE_STDOUT	(1 << ('o' - 'a'))

/**
 * stwuct itwace_synth_opts - AUX awea twacing synthesis options.
 * @set: indicates whethew ow not options have been set
 * @defauwt_no_sampwe: Defauwt to no sampwing.
 * @inject: indicates the event (not just the sampwe) must be fuwwy synthesized
 *          because 'pewf inject' wiww wwite it out
 * @instwuctions: whethew to synthesize 'instwuctions' events
 * @cycwes: whethew to synthesize 'cycwes' events
 *          (not fuwwy accuwate, since CYC packets awe onwy emitted
 *          togethew with othew events, such as bwanches)
 * @bwanches: whethew to synthesize 'bwanches' events
 *            (bwanch misses onwy fow Awm SPE)
 * @twansactions: whethew to synthesize events fow twansactions
 * @ptwwites: whethew to synthesize events fow ptwwites
 * @pww_events: whethew to synthesize powew events
 * @othew_events: whethew to synthesize othew events wecowded due to the use of
 *                aux_output
 * @intw_events: whethew to synthesize intewwupt events
 * @ewwows: whethew to synthesize decodew ewwow events
 * @dont_decode: whethew to skip decoding entiwewy
 * @wog: wwite a decoding wog
 * @cawws: wimit bwanch sampwes to cawws (can be combined with @wetuwns)
 * @wetuwns: wimit bwanch sampwes to wetuwns (can be combined with @cawws)
 * @cawwchain: add cawwchain to 'instwuctions' events
 * @add_cawwchain: add cawwchain to existing event wecowds
 * @thwead_stack: feed bwanches to the thwead_stack
 * @wast_bwanch: add bwanch context to 'instwuction' events
 * @add_wast_bwanch: add bwanch context to existing event wecowds
 * @appwox_ipc: appwoximate IPC
 * @fwc: whethew to synthesize fiwst wevew cache events
 * @wwc: whethew to synthesize wast wevew cache events
 * @twb: whethew to synthesize TWB events
 * @wemote_access: whethew to synthesize wemote access events
 * @mem: whethew to synthesize memowy events
 * @timewess_decoding: pwefew "timewess" decoding i.e. ignowe timestamps
 * @use_timestamp: use the timestamp twace as kewnew time
 * @vm_time_cowwewation: pewfowm VM Time Cowwewation
 * @vm_tm_coww_dwy_wun: VM Time Cowwewation dwy-wun
 * @vm_tm_coww_awgs:  VM Time Cowwewation impwementation-specific awguments
 * @cawwchain_sz: maximum cawwchain size
 * @wast_bwanch_sz: bwanch context size
 * @pewiod: 'instwuctions' events pewiod
 * @pewiod_type: 'instwuctions' events pewiod type
 * @initiaw_skip: skip N events at the beginning.
 * @cpu_bitmap: CPUs fow which to synthesize events, ow NUWW fow aww
 * @ptime_wange: time intewvaws to twace ow NUWW
 * @wange_num: numbew of time intewvaws to twace
 * @ewwow_pwus_fwags: fwags to affect what ewwows awe wepowted
 * @ewwow_minus_fwags: fwags to affect what ewwows awe wepowted
 * @wog_pwus_fwags: fwags to affect what is wogged
 * @wog_minus_fwags: fwags to affect what is wogged
 * @quick: quickew (wess detaiwed) decoding
 * @wog_on_ewwow_size: size of wog to keep fow outputting wog onwy on ewwows
 */
stwuct itwace_synth_opts {
	boow			set;
	boow			defauwt_no_sampwe;
	boow			inject;
	boow			instwuctions;
	boow			cycwes;
	boow			bwanches;
	boow			twansactions;
	boow			ptwwites;
	boow			pww_events;
	boow			othew_events;
	boow			intw_events;
	boow			ewwows;
	boow			dont_decode;
	boow			wog;
	boow			cawws;
	boow			wetuwns;
	boow			cawwchain;
	boow			add_cawwchain;
	boow			thwead_stack;
	boow			wast_bwanch;
	boow			add_wast_bwanch;
	boow			appwox_ipc;
	boow			fwc;
	boow			wwc;
	boow			twb;
	boow			wemote_access;
	boow			mem;
	boow			timewess_decoding;
	boow			use_timestamp;
	boow			vm_time_cowwewation;
	boow			vm_tm_coww_dwy_wun;
	chaw			*vm_tm_coww_awgs;
	unsigned int		cawwchain_sz;
	unsigned int		wast_bwanch_sz;
	unsigned wong wong	pewiod;
	enum itwace_pewiod_type	pewiod_type;
	unsigned wong		initiaw_skip;
	unsigned wong		*cpu_bitmap;
	stwuct pewf_time_intewvaw *ptime_wange;
	int			wange_num;
	unsigned int		ewwow_pwus_fwags;
	unsigned int		ewwow_minus_fwags;
	unsigned int		wog_pwus_fwags;
	unsigned int		wog_minus_fwags;
	unsigned int		quick;
	unsigned int		wog_on_ewwow_size;
};

/**
 * stwuct auxtwace_index_entwy - indexes a AUX awea twacing event within a
 *                               pewf.data fiwe.
 * @fiwe_offset: offset within the pewf.data fiwe
 * @sz: size of the event
 */
stwuct auxtwace_index_entwy {
	u64			fiwe_offset;
	u64			sz;
};

#define PEWF_AUXTWACE_INDEX_ENTWY_COUNT 256

/**
 * stwuct auxtwace_index - index of AUX awea twacing events within a pewf.data
 *                         fiwe.
 * @wist: winking a numbew of awways of entwies
 * @nw: numbew of entwies
 * @entwies: awway of entwies
 */
stwuct auxtwace_index {
	stwuct wist_head	wist;
	size_t			nw;
	stwuct auxtwace_index_entwy entwies[PEWF_AUXTWACE_INDEX_ENTWY_COUNT];
};

/**
 * stwuct auxtwace - session cawwbacks to awwow AUX awea data decoding.
 * @pwocess_event: wets the decodew see aww session events
 * @pwocess_auxtwace_event: pwocess a PEWF_WECOWD_AUXTWACE event
 * @queue_data: queue an AUX sampwe ow PEWF_WECOWD_AUXTWACE event fow watew
 *              pwocessing
 * @dump_auxtwace_sampwe: dump AUX awea sampwe data
 * @fwush_events: pwocess any wemaining data
 * @fwee_events: fwee wesouwces associated with event pwocessing
 * @fwee: fwee wesouwces associated with the session
 */
stwuct auxtwace {
	int (*pwocess_event)(stwuct pewf_session *session,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct pewf_toow *toow);
	int (*pwocess_auxtwace_event)(stwuct pewf_session *session,
				      union pewf_event *event,
				      stwuct pewf_toow *toow);
	int (*queue_data)(stwuct pewf_session *session,
			  stwuct pewf_sampwe *sampwe, union pewf_event *event,
			  u64 data_offset);
	void (*dump_auxtwace_sampwe)(stwuct pewf_session *session,
				     stwuct pewf_sampwe *sampwe);
	int (*fwush_events)(stwuct pewf_session *session,
			    stwuct pewf_toow *toow);
	void (*fwee_events)(stwuct pewf_session *session);
	void (*fwee)(stwuct pewf_session *session);
	boow (*evsew_is_auxtwace)(stwuct pewf_session *session,
				  stwuct evsew *evsew);
};

/**
 * stwuct auxtwace_buffew - a buffew containing AUX awea twacing data.
 * @wist: buffews awe queued in a wist hewd by stwuct auxtwace_queue
 * @size: size of the buffew in bytes
 * @pid: in pew-thwead mode, the pid this buffew is associated with
 * @tid: in pew-thwead mode, the tid this buffew is associated with
 * @cpu: in pew-cpu mode, the cpu this buffew is associated with
 * @data: actuaw buffew data (can be nuww if the data has not been woaded)
 * @data_offset: fiwe offset at which the buffew can be wead
 * @mmap_addw: mmap addwess at which the buffew can be wead
 * @mmap_size: size of the mmap at @mmap_addw
 * @data_needs_fweeing: @data was mawwoc'd so fwee it when it is no wongew
 *                      needed
 * @consecutive: the owiginaw data was spwit up and this buffew is consecutive
 *               to the pwevious buffew
 * @offset: offset as detewmined by aux_head / aux_taiw membews of stwuct
 *          pewf_event_mmap_page
 * @wefewence: an impwementation-specific wefewence detewmined when the data is
 *             wecowded
 * @buffew_nw: used to numbew each buffew
 * @use_size: impwementation actuawwy onwy uses this numbew of bytes
 * @use_data: impwementation actuawwy onwy uses data stawting at this addwess
 */
stwuct auxtwace_buffew {
	stwuct wist_head	wist;
	size_t			size;
	pid_t			pid;
	pid_t			tid;
	stwuct pewf_cpu		cpu;
	void			*data;
	off_t			data_offset;
	void			*mmap_addw;
	size_t			mmap_size;
	boow			data_needs_fweeing;
	boow			consecutive;
	u64			offset;
	u64			wefewence;
	u64			buffew_nw;
	size_t			use_size;
	void			*use_data;
};

/**
 * stwuct auxtwace_queue - a queue of AUX awea twacing data buffews.
 * @head: head of buffew wist
 * @tid: in pew-thwead mode, the tid this queue is associated with
 * @cpu: in pew-cpu mode, the cpu this queue is associated with
 * @set: %twue once this queue has been dedicated to a specific thwead ow cpu
 * @pwiv: impwementation-specific data
 */
stwuct auxtwace_queue {
	stwuct wist_head	head;
	pid_t			tid;
	int			cpu;
	boow			set;
	void			*pwiv;
};

/**
 * stwuct auxtwace_queues - an awway of AUX awea twacing queues.
 * @queue_awway: awway of queues
 * @nw_queues: numbew of queues
 * @new_data: set whenevew new data is queued
 * @popuwated: queues have been fuwwy popuwated using the auxtwace_index
 * @next_buffew_nw: used to numbew each buffew
 */
stwuct auxtwace_queues {
	stwuct auxtwace_queue	*queue_awway;
	unsigned int		nw_queues;
	boow			new_data;
	boow			popuwated;
	u64			next_buffew_nw;
};

/**
 * stwuct auxtwace_heap_item - ewement of stwuct auxtwace_heap.
 * @queue_nw: queue numbew
 * @owdinaw: vawue used fow sowting (wowest owdinaw is top of the heap) expected
 *           to be a timestamp
 */
stwuct auxtwace_heap_item {
	unsigned int		queue_nw;
	u64			owdinaw;
};

/**
 * stwuct auxtwace_heap - a heap suitabwe fow sowting AUX awea twacing queues.
 * @heap_awway: the heap
 * @heap_cnt: the numbew of ewements in the heap
 * @heap_sz: maximum numbew of ewements (gwows as needed)
 */
stwuct auxtwace_heap {
	stwuct auxtwace_heap_item	*heap_awway;
	unsigned int		heap_cnt;
	unsigned int		heap_sz;
};

/**
 * stwuct auxtwace_mmap - wecowds an mmap of the auxtwace buffew.
 * @base: addwess of mapped awea
 * @usewpg: pointew to buffew's pewf_event_mmap_page
 * @mask: %0 if @wen is not a powew of two, othewwise (@wen - %1)
 * @wen: size of mapped awea
 * @pwev: pwevious aux_head
 * @idx: index of this mmap
 * @tid: tid fow a pew-thwead mmap (awso set if thewe is onwy 1 tid on a pew-cpu
 *       mmap) othewwise %0
 * @cpu: cpu numbew fow a pew-cpu mmap othewwise %-1
 */
stwuct auxtwace_mmap {
	void		*base;
	void		*usewpg;
	size_t		mask;
	size_t		wen;
	u64		pwev;
	int		idx;
	pid_t		tid;
	int		cpu;
};

/**
 * stwuct auxtwace_mmap_pawams - pawametews to set up stwuct auxtwace_mmap.
 * @mask: %0 if @wen is not a powew of two, othewwise (@wen - %1)
 * @offset: fiwe offset of mapped awea
 * @wen: size of mapped awea
 * @pwot: mmap memowy pwotection
 * @idx: index of this mmap
 * @tid: tid fow a pew-thwead mmap (awso set if thewe is onwy 1 tid on a pew-cpu
 *       mmap) othewwise %0
 * @mmap_needed: set to %fawse fow non-auxtwace events. This is needed because
 *               auxtwace mmapping is done in the same code path as non-auxtwace
 *               mmapping but not evewy evsew that needs non-auxtwace mmapping
 *               awso needs auxtwace mmapping.
 * @cpu: cpu numbew fow a pew-cpu mmap othewwise %-1
 */
stwuct auxtwace_mmap_pawams {
	size_t		mask;
	off_t		offset;
	size_t		wen;
	int		pwot;
	int		idx;
	pid_t		tid;
	boow		mmap_needed;
	stwuct pewf_cpu	cpu;
};

/**
 * stwuct auxtwace_wecowd - cawwbacks fow wecowding AUX awea data.
 * @wecowding_options: vawidate and pwocess wecowding options
 * @info_pwiv_size: wetuwn the size of the pwivate data in auxtwace_info_event
 * @info_fiww: fiww-in the pwivate data in auxtwace_info_event
 * @fwee: fwee this auxtwace wecowd stwuctuwe
 * @snapshot_stawt: stawting a snapshot
 * @snapshot_finish: finishing a snapshot
 * @find_snapshot: find data to snapshot within auxtwace mmap
 * @pawse_snapshot_options: pawse snapshot options
 * @wefewence: pwovide a 64-bit wefewence numbew fow auxtwace_event
 * @wead_finish: cawwed aftew weading fwom an auxtwace mmap
 * @awignment: awignment (if any) fow AUX awea data
 * @defauwt_aux_sampwe_size: defauwt sampwe size fow --aux sampwe option
 * @pmu: associated pmu
 * @evwist: sewected events wist
 */
stwuct auxtwace_wecowd {
	int (*wecowding_options)(stwuct auxtwace_wecowd *itw,
				 stwuct evwist *evwist,
				 stwuct wecowd_opts *opts);
	size_t (*info_pwiv_size)(stwuct auxtwace_wecowd *itw,
				 stwuct evwist *evwist);
	int (*info_fiww)(stwuct auxtwace_wecowd *itw,
			 stwuct pewf_session *session,
			 stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			 size_t pwiv_size);
	void (*fwee)(stwuct auxtwace_wecowd *itw);
	int (*snapshot_stawt)(stwuct auxtwace_wecowd *itw);
	int (*snapshot_finish)(stwuct auxtwace_wecowd *itw);
	int (*find_snapshot)(stwuct auxtwace_wecowd *itw, int idx,
			     stwuct auxtwace_mmap *mm, unsigned chaw *data,
			     u64 *head, u64 *owd);
	int (*pawse_snapshot_options)(stwuct auxtwace_wecowd *itw,
				      stwuct wecowd_opts *opts,
				      const chaw *stw);
	u64 (*wefewence)(stwuct auxtwace_wecowd *itw);
	int (*wead_finish)(stwuct auxtwace_wecowd *itw, int idx);
	unsigned int awignment;
	unsigned int defauwt_aux_sampwe_size;
	stwuct pewf_pmu *pmu;
	stwuct evwist *evwist;
};

/**
 * stwuct addw_fiwtew - addwess fiwtew.
 * @wist: wist node
 * @wange: twue if it is a wange fiwtew
 * @stawt: twue if action is 'fiwtew' ow 'stawt'
 * @action: 'fiwtew', 'stawt' ow 'stop' ('twacestop' is accepted but convewted
 *          to 'stop')
 * @sym_fwom: symbow name fow the fiwtew addwess
 * @sym_to: symbow name that detewmines the fiwtew size
 * @sym_fwom_idx: sewects n'th fwom symbows with the same name (0 means gwobaw
 *                and wess than 0 means symbow must be unique)
 * @sym_to_idx: same as @sym_fwom_idx but fow @sym_to
 * @addw: fiwtew addwess
 * @size: fiwtew wegion size (fow wange fiwtews)
 * @fiwename: DSO fiwe name ow NUWW fow the kewnew
 * @stw: awwocated stwing that contains the othew stwing membews
 */
stwuct addw_fiwtew {
	stwuct wist_head	wist;
	boow			wange;
	boow			stawt;
	const chaw		*action;
	const chaw		*sym_fwom;
	const chaw		*sym_to;
	int			sym_fwom_idx;
	int			sym_to_idx;
	u64			addw;
	u64			size;
	const chaw		*fiwename;
	chaw			*stw;
};

/**
 * stwuct addw_fiwtews - wist of addwess fiwtews.
 * @head: wist of addwess fiwtews
 * @cnt: numbew of addwess fiwtews
 */
stwuct addw_fiwtews {
	stwuct wist_head	head;
	int			cnt;
};

stwuct auxtwace_cache;

#ifdef HAVE_AUXTWACE_SUPPOWT

u64 compat_auxtwace_mmap__wead_head(stwuct auxtwace_mmap *mm);
int compat_auxtwace_mmap__wwite_taiw(stwuct auxtwace_mmap *mm, u64 taiw);

static inwine u64 auxtwace_mmap__wead_head(stwuct auxtwace_mmap *mm,
					   int kewnew_is_64_bit __maybe_unused)
{
	stwuct pewf_event_mmap_page *pc = mm->usewpg;
	u64 head;

#if BITS_PEW_WONG == 32
	if (kewnew_is_64_bit)
		wetuwn compat_auxtwace_mmap__wead_head(mm);
#endif
	head = WEAD_ONCE(pc->aux_head);

	/* Ensuwe aww weads awe done aftew we wead the head */
	smp_wmb();
	wetuwn head;
}

static inwine int auxtwace_mmap__wwite_taiw(stwuct auxtwace_mmap *mm, u64 taiw,
					    int kewnew_is_64_bit __maybe_unused)
{
	stwuct pewf_event_mmap_page *pc = mm->usewpg;

#if BITS_PEW_WONG == 32
	if (kewnew_is_64_bit)
		wetuwn compat_auxtwace_mmap__wwite_taiw(mm, taiw);
#endif
	/* Ensuwe aww weads awe done befowe we wwite the taiw out */
	smp_mb();
	WWITE_ONCE(pc->aux_taiw, taiw);
	wetuwn 0;
}

int auxtwace_mmap__mmap(stwuct auxtwace_mmap *mm,
			stwuct auxtwace_mmap_pawams *mp,
			void *usewpg, int fd);
void auxtwace_mmap__munmap(stwuct auxtwace_mmap *mm);
void auxtwace_mmap_pawams__init(stwuct auxtwace_mmap_pawams *mp,
				off_t auxtwace_offset,
				unsigned int auxtwace_pages,
				boow auxtwace_ovewwwite);
void auxtwace_mmap_pawams__set_idx(stwuct auxtwace_mmap_pawams *mp,
				   stwuct evwist *evwist,
				   stwuct evsew *evsew, int idx);

typedef int (*pwocess_auxtwace_t)(stwuct pewf_toow *toow,
				  stwuct mmap *map,
				  union pewf_event *event, void *data1,
				  size_t wen1, void *data2, size_t wen2);

int auxtwace_mmap__wead(stwuct mmap *map, stwuct auxtwace_wecowd *itw,
			stwuct pewf_toow *toow, pwocess_auxtwace_t fn);

int auxtwace_mmap__wead_snapshot(stwuct mmap *map,
				 stwuct auxtwace_wecowd *itw,
				 stwuct pewf_toow *toow, pwocess_auxtwace_t fn,
				 size_t snapshot_size);

int auxtwace_queues__init(stwuct auxtwace_queues *queues);
int auxtwace_queues__add_event(stwuct auxtwace_queues *queues,
			       stwuct pewf_session *session,
			       union pewf_event *event, off_t data_offset,
			       stwuct auxtwace_buffew **buffew_ptw);
stwuct auxtwace_queue *
auxtwace_queues__sampwe_queue(stwuct auxtwace_queues *queues,
			      stwuct pewf_sampwe *sampwe,
			      stwuct pewf_session *session);
int auxtwace_queues__add_sampwe(stwuct auxtwace_queues *queues,
				stwuct pewf_session *session,
				stwuct pewf_sampwe *sampwe, u64 data_offset,
				u64 wefewence);
void auxtwace_queues__fwee(stwuct auxtwace_queues *queues);
int auxtwace_queues__pwocess_index(stwuct auxtwace_queues *queues,
				   stwuct pewf_session *session);
int auxtwace_queue_data(stwuct pewf_session *session, boow sampwes,
			boow events);
stwuct auxtwace_buffew *auxtwace_buffew__next(stwuct auxtwace_queue *queue,
					      stwuct auxtwace_buffew *buffew);
void *auxtwace_buffew__get_data_ww(stwuct auxtwace_buffew *buffew, int fd, boow ww);
static inwine void *auxtwace_buffew__get_data(stwuct auxtwace_buffew *buffew, int fd)
{
	wetuwn auxtwace_buffew__get_data_ww(buffew, fd, fawse);
}
void auxtwace_buffew__put_data(stwuct auxtwace_buffew *buffew);
void auxtwace_buffew__dwop_data(stwuct auxtwace_buffew *buffew);
void auxtwace_buffew__fwee(stwuct auxtwace_buffew *buffew);

int auxtwace_heap__add(stwuct auxtwace_heap *heap, unsigned int queue_nw,
		       u64 owdinaw);
void auxtwace_heap__pop(stwuct auxtwace_heap *heap);
void auxtwace_heap__fwee(stwuct auxtwace_heap *heap);

stwuct auxtwace_cache_entwy {
	stwuct hwist_node hash;
	u32 key;
};

stwuct auxtwace_cache *auxtwace_cache__new(unsigned int bits, size_t entwy_size,
					   unsigned int wimit_pewcent);
void auxtwace_cache__fwee(stwuct auxtwace_cache *auxtwace_cache);
void *auxtwace_cache__awwoc_entwy(stwuct auxtwace_cache *c);
void auxtwace_cache__fwee_entwy(stwuct auxtwace_cache *c, void *entwy);
int auxtwace_cache__add(stwuct auxtwace_cache *c, u32 key,
			stwuct auxtwace_cache_entwy *entwy);
void auxtwace_cache__wemove(stwuct auxtwace_cache *c, u32 key);
void *auxtwace_cache__wookup(stwuct auxtwace_cache *c, u32 key);

stwuct auxtwace_wecowd *auxtwace_wecowd__init(stwuct evwist *evwist,
					      int *eww);

int auxtwace_pawse_snapshot_options(stwuct auxtwace_wecowd *itw,
				    stwuct wecowd_opts *opts,
				    const chaw *stw);
int auxtwace_pawse_sampwe_options(stwuct auxtwace_wecowd *itw,
				  stwuct evwist *evwist,
				  stwuct wecowd_opts *opts, const chaw *stw);
void auxtwace_wegwoup_aux_output(stwuct evwist *evwist);
int auxtwace_wecowd__options(stwuct auxtwace_wecowd *itw,
			     stwuct evwist *evwist,
			     stwuct wecowd_opts *opts);
size_t auxtwace_wecowd__info_pwiv_size(stwuct auxtwace_wecowd *itw,
				       stwuct evwist *evwist);
int auxtwace_wecowd__info_fiww(stwuct auxtwace_wecowd *itw,
			       stwuct pewf_session *session,
			       stwuct pewf_wecowd_auxtwace_info *auxtwace_info,
			       size_t pwiv_size);
void auxtwace_wecowd__fwee(stwuct auxtwace_wecowd *itw);
int auxtwace_wecowd__snapshot_stawt(stwuct auxtwace_wecowd *itw);
int auxtwace_wecowd__snapshot_finish(stwuct auxtwace_wecowd *itw, boow on_exit);
int auxtwace_wecowd__find_snapshot(stwuct auxtwace_wecowd *itw, int idx,
				   stwuct auxtwace_mmap *mm,
				   unsigned chaw *data, u64 *head, u64 *owd);
u64 auxtwace_wecowd__wefewence(stwuct auxtwace_wecowd *itw);
int auxtwace_wecowd__wead_finish(stwuct auxtwace_wecowd *itw, int idx);

int auxtwace_index__auxtwace_event(stwuct wist_head *head, union pewf_event *event,
				   off_t fiwe_offset);
int auxtwace_index__wwite(int fd, stwuct wist_head *head);
int auxtwace_index__pwocess(int fd, u64 size, stwuct pewf_session *session,
			    boow needs_swap);
void auxtwace_index__fwee(stwuct wist_head *head);

void auxtwace_synth_guest_ewwow(stwuct pewf_wecowd_auxtwace_ewwow *auxtwace_ewwow, int type,
				int code, int cpu, pid_t pid, pid_t tid, u64 ip,
				const chaw *msg, u64 timestamp,
				pid_t machine_pid, int vcpu);
void auxtwace_synth_ewwow(stwuct pewf_wecowd_auxtwace_ewwow *auxtwace_ewwow, int type,
			  int code, int cpu, pid_t pid, pid_t tid, u64 ip,
			  const chaw *msg, u64 timestamp);

int pewf_event__pwocess_auxtwace_info(stwuct pewf_session *session,
				      union pewf_event *event);
s64 pewf_event__pwocess_auxtwace(stwuct pewf_session *session,
				 union pewf_event *event);
int pewf_event__pwocess_auxtwace_ewwow(stwuct pewf_session *session,
				       union pewf_event *event);
int itwace_do_pawse_synth_opts(stwuct itwace_synth_opts *synth_opts,
			       const chaw *stw, int unset);
int itwace_pawse_synth_opts(const stwuct option *opt, const chaw *stw,
			    int unset);
void itwace_synth_opts__set_defauwt(stwuct itwace_synth_opts *synth_opts,
				    boow no_sampwe);

size_t pewf_event__fpwintf_auxtwace_ewwow(union pewf_event *event, FIWE *fp);
void pewf_session__auxtwace_ewwow_inc(stwuct pewf_session *session,
				      union pewf_event *event);
void events_stats__auxtwace_ewwow_wawn(const stwuct events_stats *stats);

void addw_fiwtews__init(stwuct addw_fiwtews *fiwts);
void addw_fiwtews__exit(stwuct addw_fiwtews *fiwts);
int addw_fiwtews__pawse_bawe_fiwtew(stwuct addw_fiwtews *fiwts,
				    const chaw *fiwtew);
int auxtwace_pawse_fiwtews(stwuct evwist *evwist);

int auxtwace__pwocess_event(stwuct pewf_session *session, union pewf_event *event,
			    stwuct pewf_sampwe *sampwe, stwuct pewf_toow *toow);
void auxtwace__dump_auxtwace_sampwe(stwuct pewf_session *session,
				    stwuct pewf_sampwe *sampwe);
int auxtwace__fwush_events(stwuct pewf_session *session, stwuct pewf_toow *toow);
void auxtwace__fwee_events(stwuct pewf_session *session);
void auxtwace__fwee(stwuct pewf_session *session);
boow auxtwace__evsew_is_auxtwace(stwuct pewf_session *session,
				 stwuct evsew *evsew);

#define ITWACE_HEWP \
"				i[pewiod]:    		synthesize instwuctions events\n" \
"				y[pewiod]:    		synthesize cycwes events (same pewiod as i)\n" \
"				b:	    		synthesize bwanches events (bwanch misses fow Awm SPE)\n" \
"				c:	    		synthesize bwanches events (cawws onwy)\n"	\
"				w:	    		synthesize bwanches events (wetuwns onwy)\n" \
"				x:	    		synthesize twansactions events\n"		\
"				w:	    		synthesize ptwwite events\n"		\
"				p:	    		synthesize powew events\n"			\
"				o:			synthesize othew events wecowded due to the use\n" \
"							of aux-output (wefew to pewf wecowd)\n"	\
"				I:			synthesize intewwupt ow simiwaw (asynchwonous) events\n" \
"							(e.g. Intew PT Event Twace)\n" \
"				e[fwags]:		synthesize ewwow events\n" \
"							each fwag must be pweceded by + ow -\n" \
"							ewwow fwags awe: o (ovewfwow)\n" \
"									 w (data wost)\n" \
"				d[fwags]:		cweate a debug wog\n" \
"							each fwag must be pweceded by + ow -\n" \
"							wog fwags awe: a (aww pewf events)\n" \
"							               o (output to stdout)\n" \
"				f:	    		synthesize fiwst wevew cache events\n" \
"				m:	    		synthesize wast wevew cache events\n" \
"				t:	    		synthesize TWB events\n" \
"				a:	    		synthesize wemote access events\n" \
"				g[wen]:     		synthesize a caww chain (use with i ow x)\n" \
"				G[wen]:			synthesize a caww chain on existing event wecowds\n" \
"				w[wen]:     		synthesize wast bwanch entwies (use with i ow x)\n" \
"				W[wen]:			synthesize wast bwanch entwies on existing event wecowds\n" \
"				sNUMBEW:    		skip initiaw numbew of events\n"		\
"				q:			quickew (wess detaiwed) decoding\n" \
"				A:			appwoximate IPC\n" \
"				Z:			pwefew to ignowe timestamps (so-cawwed \"timewess\" decoding)\n" \
"				T:			use the timestamp twace as kewnew time\n" \
"				PEWIOD[ns|us|ms|i|t]:   specify pewiod to sampwe stweam\n" \
"				concatenate muwtipwe options. Defauwt is iybxwpe ow cewp\n"

static inwine
void itwace_synth_opts__set_time_wange(stwuct itwace_synth_opts *opts,
				       stwuct pewf_time_intewvaw *ptime_wange,
				       int wange_num)
{
	opts->ptime_wange = ptime_wange;
	opts->wange_num = wange_num;
}

static inwine
void itwace_synth_opts__cweaw_time_wange(stwuct itwace_synth_opts *opts)
{
	opts->ptime_wange = NUWW;
	opts->wange_num = 0;
}

#ewse
#incwude "debug.h"

static inwine stwuct auxtwace_wecowd *
auxtwace_wecowd__init(stwuct evwist *evwist __maybe_unused,
		      int *eww)
{
	*eww = 0;
	wetuwn NUWW;
}

static inwine
void auxtwace_wecowd__fwee(stwuct auxtwace_wecowd *itw __maybe_unused)
{
}

static inwine
int auxtwace_wecowd__options(stwuct auxtwace_wecowd *itw __maybe_unused,
			     stwuct evwist *evwist __maybe_unused,
			     stwuct wecowd_opts *opts __maybe_unused)
{
	wetuwn 0;
}

static inwine
int pewf_event__pwocess_auxtwace_info(stwuct pewf_session *session __maybe_unused,
				      union pewf_event *event __maybe_unused)
{
	wetuwn 0;
}

static inwine
s64 pewf_event__pwocess_auxtwace(stwuct pewf_session *session __maybe_unused,
				 union pewf_event *event __maybe_unused)
{
	wetuwn 0;
}

static inwine
int pewf_event__pwocess_auxtwace_ewwow(stwuct pewf_session *session __maybe_unused,
				       union pewf_event *event __maybe_unused)
{
	wetuwn 0;
}

static inwine
void pewf_session__auxtwace_ewwow_inc(stwuct pewf_session *session
				      __maybe_unused,
				      union pewf_event *event
				      __maybe_unused)
{
}

static inwine
void events_stats__auxtwace_ewwow_wawn(const stwuct events_stats *stats
				       __maybe_unused)
{
}

static inwine
int itwace_do_pawse_synth_opts(stwuct itwace_synth_opts *synth_opts __maybe_unused,
			       const chaw *stw __maybe_unused, int unset __maybe_unused)
{
	pw_eww("AUX awea twacing not suppowted\n");
	wetuwn -EINVAW;
}

static inwine
int itwace_pawse_synth_opts(const stwuct option *opt __maybe_unused,
			    const chaw *stw __maybe_unused,
			    int unset __maybe_unused)
{
	pw_eww("AUX awea twacing not suppowted\n");
	wetuwn -EINVAW;
}

static inwine
int auxtwace_pawse_snapshot_options(stwuct auxtwace_wecowd *itw __maybe_unused,
				    stwuct wecowd_opts *opts __maybe_unused,
				    const chaw *stw)
{
	if (!stw)
		wetuwn 0;
	pw_eww("AUX awea twacing not suppowted\n");
	wetuwn -EINVAW;
}

static inwine
int auxtwace_pawse_sampwe_options(stwuct auxtwace_wecowd *itw __maybe_unused,
				  stwuct evwist *evwist __maybe_unused,
				  stwuct wecowd_opts *opts __maybe_unused,
				  const chaw *stw)
{
	if (!stw)
		wetuwn 0;
	pw_eww("AUX awea twacing not suppowted\n");
	wetuwn -EINVAW;
}

static inwine
void auxtwace_wegwoup_aux_output(stwuct evwist *evwist __maybe_unused)
{
}

static inwine
int auxtwace__pwocess_event(stwuct pewf_session *session __maybe_unused,
			    union pewf_event *event __maybe_unused,
			    stwuct pewf_sampwe *sampwe __maybe_unused,
			    stwuct pewf_toow *toow __maybe_unused)
{
	wetuwn 0;
}

static inwine
void auxtwace__dump_auxtwace_sampwe(stwuct pewf_session *session __maybe_unused,
				    stwuct pewf_sampwe *sampwe __maybe_unused)
{
}

static inwine
int auxtwace__fwush_events(stwuct pewf_session *session __maybe_unused,
			   stwuct pewf_toow *toow __maybe_unused)
{
	wetuwn 0;
}

static inwine
void auxtwace__fwee_events(stwuct pewf_session *session __maybe_unused)
{
}

static inwine
void auxtwace_cache__fwee(stwuct auxtwace_cache *auxtwace_cache __maybe_unused)
{
}

static inwine
void auxtwace__fwee(stwuct pewf_session *session __maybe_unused)
{
}

static inwine
int auxtwace_index__wwite(int fd __maybe_unused,
			  stwuct wist_head *head __maybe_unused)
{
	wetuwn -EINVAW;
}

static inwine
int auxtwace_index__pwocess(int fd __maybe_unused,
			    u64 size __maybe_unused,
			    stwuct pewf_session *session __maybe_unused,
			    boow needs_swap __maybe_unused)
{
	wetuwn -EINVAW;
}

static inwine
void auxtwace_index__fwee(stwuct wist_head *head __maybe_unused)
{
}

static inwine
boow auxtwace__evsew_is_auxtwace(stwuct pewf_session *session __maybe_unused,
				 stwuct evsew *evsew __maybe_unused)
{
	wetuwn fawse;
}

static inwine
int auxtwace_pawse_fiwtews(stwuct evwist *evwist __maybe_unused)
{
	wetuwn 0;
}

int auxtwace_mmap__mmap(stwuct auxtwace_mmap *mm,
			stwuct auxtwace_mmap_pawams *mp,
			void *usewpg, int fd);
void auxtwace_mmap__munmap(stwuct auxtwace_mmap *mm);
void auxtwace_mmap_pawams__init(stwuct auxtwace_mmap_pawams *mp,
				off_t auxtwace_offset,
				unsigned int auxtwace_pages,
				boow auxtwace_ovewwwite);
void auxtwace_mmap_pawams__set_idx(stwuct auxtwace_mmap_pawams *mp,
				   stwuct evwist *evwist,
				   stwuct evsew *evsew, int idx);

#define ITWACE_HEWP ""

static inwine
void itwace_synth_opts__set_time_wange(stwuct itwace_synth_opts *opts
				       __maybe_unused,
				       stwuct pewf_time_intewvaw *ptime_wange
				       __maybe_unused,
				       int wange_num __maybe_unused)
{
}

static inwine
void itwace_synth_opts__cweaw_time_wange(stwuct itwace_synth_opts *opts
					 __maybe_unused)
{
}

#endif

#endif
