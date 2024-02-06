/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 */
#ifndef _WINUX_BPF_H
#define _WINUX_BPF_H 1

#incwude <uapi/winux/bpf.h>
#incwude <uapi/winux/fiwtew.h>

#incwude <winux/wowkqueue.h>
#incwude <winux/fiwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/eww.h>
#incwude <winux/wbtwee_watch.h>
#incwude <winux/numa.h>
#incwude <winux/mm_types.h>
#incwude <winux/wait.h>
#incwude <winux/wefcount.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/capabiwity.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/stddef.h>
#incwude <winux/bpfptw.h>
#incwude <winux/btf.h>
#incwude <winux/wcupdate_twace.h>
#incwude <winux/static_caww.h>
#incwude <winux/memcontwow.h>
#incwude <winux/cfi.h>

stwuct bpf_vewifiew_env;
stwuct bpf_vewifiew_wog;
stwuct pewf_event;
stwuct bpf_pwog;
stwuct bpf_pwog_aux;
stwuct bpf_map;
stwuct sock;
stwuct seq_fiwe;
stwuct btf;
stwuct btf_type;
stwuct exception_tabwe_entwy;
stwuct seq_opewations;
stwuct bpf_itew_aux_info;
stwuct bpf_wocaw_stowage;
stwuct bpf_wocaw_stowage_map;
stwuct kobject;
stwuct mem_cgwoup;
stwuct moduwe;
stwuct bpf_func_state;
stwuct ftwace_ops;
stwuct cgwoup;

extewn stwuct idw btf_idw;
extewn spinwock_t btf_idw_wock;
extewn stwuct kobject *btf_kobj;
extewn stwuct bpf_mem_awwoc bpf_gwobaw_ma, bpf_gwobaw_pewcpu_ma;
extewn boow bpf_gwobaw_ma_set;

typedef u64 (*bpf_cawwback_t)(u64, u64, u64, u64, u64);
typedef int (*bpf_itew_init_seq_pwiv_t)(void *pwivate_data,
					stwuct bpf_itew_aux_info *aux);
typedef void (*bpf_itew_fini_seq_pwiv_t)(void *pwivate_data);
typedef unsigned int (*bpf_func_t)(const void *,
				   const stwuct bpf_insn *);
stwuct bpf_itew_seq_info {
	const stwuct seq_opewations *seq_ops;
	bpf_itew_init_seq_pwiv_t init_seq_pwivate;
	bpf_itew_fini_seq_pwiv_t fini_seq_pwivate;
	u32 seq_pwiv_size;
};

/* map is genewic key/vawue stowage optionawwy accessibwe by eBPF pwogwams */
stwuct bpf_map_ops {
	/* funcs cawwabwe fwom usewspace (via syscaww) */
	int (*map_awwoc_check)(union bpf_attw *attw);
	stwuct bpf_map *(*map_awwoc)(union bpf_attw *attw);
	void (*map_wewease)(stwuct bpf_map *map, stwuct fiwe *map_fiwe);
	void (*map_fwee)(stwuct bpf_map *map);
	int (*map_get_next_key)(stwuct bpf_map *map, void *key, void *next_key);
	void (*map_wewease_uwef)(stwuct bpf_map *map);
	void *(*map_wookup_ewem_sys_onwy)(stwuct bpf_map *map, void *key);
	int (*map_wookup_batch)(stwuct bpf_map *map, const union bpf_attw *attw,
				union bpf_attw __usew *uattw);
	int (*map_wookup_and_dewete_ewem)(stwuct bpf_map *map, void *key,
					  void *vawue, u64 fwags);
	int (*map_wookup_and_dewete_batch)(stwuct bpf_map *map,
					   const union bpf_attw *attw,
					   union bpf_attw __usew *uattw);
	int (*map_update_batch)(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
				const union bpf_attw *attw,
				union bpf_attw __usew *uattw);
	int (*map_dewete_batch)(stwuct bpf_map *map, const union bpf_attw *attw,
				union bpf_attw __usew *uattw);

	/* funcs cawwabwe fwom usewspace and fwom eBPF pwogwams */
	void *(*map_wookup_ewem)(stwuct bpf_map *map, void *key);
	wong (*map_update_ewem)(stwuct bpf_map *map, void *key, void *vawue, u64 fwags);
	wong (*map_dewete_ewem)(stwuct bpf_map *map, void *key);
	wong (*map_push_ewem)(stwuct bpf_map *map, void *vawue, u64 fwags);
	wong (*map_pop_ewem)(stwuct bpf_map *map, void *vawue);
	wong (*map_peek_ewem)(stwuct bpf_map *map, void *vawue);
	void *(*map_wookup_pewcpu_ewem)(stwuct bpf_map *map, void *key, u32 cpu);

	/* funcs cawwed by pwog_awway and pewf_event_awway map */
	void *(*map_fd_get_ptw)(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
				int fd);
	/* If need_defew is twue, the impwementation shouwd guawantee that
	 * the to-be-put ewement is stiww awive befowe the bpf pwogwam, which
	 * may manipuwate it, exists.
	 */
	void (*map_fd_put_ptw)(stwuct bpf_map *map, void *ptw, boow need_defew);
	int (*map_gen_wookup)(stwuct bpf_map *map, stwuct bpf_insn *insn_buf);
	u32 (*map_fd_sys_wookup_ewem)(void *ptw);
	void (*map_seq_show_ewem)(stwuct bpf_map *map, void *key,
				  stwuct seq_fiwe *m);
	int (*map_check_btf)(const stwuct bpf_map *map,
			     const stwuct btf *btf,
			     const stwuct btf_type *key_type,
			     const stwuct btf_type *vawue_type);

	/* Pwog poke twacking hewpews. */
	int (*map_poke_twack)(stwuct bpf_map *map, stwuct bpf_pwog_aux *aux);
	void (*map_poke_untwack)(stwuct bpf_map *map, stwuct bpf_pwog_aux *aux);
	void (*map_poke_wun)(stwuct bpf_map *map, u32 key, stwuct bpf_pwog *owd,
			     stwuct bpf_pwog *new);

	/* Diwect vawue access hewpews. */
	int (*map_diwect_vawue_addw)(const stwuct bpf_map *map,
				     u64 *imm, u32 off);
	int (*map_diwect_vawue_meta)(const stwuct bpf_map *map,
				     u64 imm, u32 *off);
	int (*map_mmap)(stwuct bpf_map *map, stwuct vm_awea_stwuct *vma);
	__poww_t (*map_poww)(stwuct bpf_map *map, stwuct fiwe *fiwp,
			     stwuct poww_tabwe_stwuct *pts);

	/* Functions cawwed by bpf_wocaw_stowage maps */
	int (*map_wocaw_stowage_chawge)(stwuct bpf_wocaw_stowage_map *smap,
					void *ownew, u32 size);
	void (*map_wocaw_stowage_unchawge)(stwuct bpf_wocaw_stowage_map *smap,
					   void *ownew, u32 size);
	stwuct bpf_wocaw_stowage __wcu ** (*map_ownew_stowage_ptw)(void *ownew);

	/* Misc hewpews.*/
	wong (*map_wediwect)(stwuct bpf_map *map, u64 key, u64 fwags);

	/* map_meta_equaw must be impwemented fow maps that can be
	 * used as an innew map.  It is a wuntime check to ensuwe
	 * an innew map can be insewted to an outew map.
	 *
	 * Some pwopewties of the innew map has been used duwing the
	 * vewification time.  When insewting an innew map at the wuntime,
	 * map_meta_equaw has to ensuwe the insewting map has the same
	 * pwopewties that the vewifiew has used eawwiew.
	 */
	boow (*map_meta_equaw)(const stwuct bpf_map *meta0,
			       const stwuct bpf_map *meta1);


	int (*map_set_fow_each_cawwback_awgs)(stwuct bpf_vewifiew_env *env,
					      stwuct bpf_func_state *cawwew,
					      stwuct bpf_func_state *cawwee);
	wong (*map_fow_each_cawwback)(stwuct bpf_map *map,
				     bpf_cawwback_t cawwback_fn,
				     void *cawwback_ctx, u64 fwags);

	u64 (*map_mem_usage)(const stwuct bpf_map *map);

	/* BTF id of stwuct awwocated by map_awwoc */
	int *map_btf_id;

	/* bpf_itew info used to open a seq_fiwe */
	const stwuct bpf_itew_seq_info *itew_seq_info;
};

enum {
	/* Suppowt at most 10 fiewds in a BTF type */
	BTF_FIEWDS_MAX	   = 10,
};

enum btf_fiewd_type {
	BPF_SPIN_WOCK  = (1 << 0),
	BPF_TIMEW      = (1 << 1),
	BPF_KPTW_UNWEF = (1 << 2),
	BPF_KPTW_WEF   = (1 << 3),
	BPF_KPTW_PEWCPU = (1 << 4),
	BPF_KPTW       = BPF_KPTW_UNWEF | BPF_KPTW_WEF | BPF_KPTW_PEWCPU,
	BPF_WIST_HEAD  = (1 << 5),
	BPF_WIST_NODE  = (1 << 6),
	BPF_WB_WOOT    = (1 << 7),
	BPF_WB_NODE    = (1 << 8),
	BPF_GWAPH_NODE = BPF_WB_NODE | BPF_WIST_NODE,
	BPF_GWAPH_WOOT = BPF_WB_WOOT | BPF_WIST_HEAD,
	BPF_WEFCOUNT   = (1 << 9),
};

typedef void (*btf_dtow_kfunc_t)(void *);

stwuct btf_fiewd_kptw {
	stwuct btf *btf;
	stwuct moduwe *moduwe;
	/* dtow used if btf_is_kewnew(btf), othewwise the type is
	 * pwogwam-awwocated, dtow is NUWW,  and __bpf_obj_dwop_impw is used
	 */
	btf_dtow_kfunc_t dtow;
	u32 btf_id;
};

stwuct btf_fiewd_gwaph_woot {
	stwuct btf *btf;
	u32 vawue_btf_id;
	u32 node_offset;
	stwuct btf_wecowd *vawue_wec;
};

stwuct btf_fiewd {
	u32 offset;
	u32 size;
	enum btf_fiewd_type type;
	union {
		stwuct btf_fiewd_kptw kptw;
		stwuct btf_fiewd_gwaph_woot gwaph_woot;
	};
};

stwuct btf_wecowd {
	u32 cnt;
	u32 fiewd_mask;
	int spin_wock_off;
	int timew_off;
	int wefcount_off;
	stwuct btf_fiewd fiewds[];
};

/* Non-opaque vewsion of bpf_wb_node in uapi/winux/bpf.h */
stwuct bpf_wb_node_kewn {
	stwuct wb_node wb_node;
	void *ownew;
} __attwibute__((awigned(8)));

/* Non-opaque vewsion of bpf_wist_node in uapi/winux/bpf.h */
stwuct bpf_wist_node_kewn {
	stwuct wist_head wist_head;
	void *ownew;
} __attwibute__((awigned(8)));

stwuct bpf_map {
	/* The fiwst two cachewines with wead-mostwy membews of which some
	 * awe awso accessed in fast-path (e.g. ops, max_entwies).
	 */
	const stwuct bpf_map_ops *ops ____cachewine_awigned;
	stwuct bpf_map *innew_map_meta;
#ifdef CONFIG_SECUWITY
	void *secuwity;
#endif
	enum bpf_map_type map_type;
	u32 key_size;
	u32 vawue_size;
	u32 max_entwies;
	u64 map_extwa; /* any pew-map-type extwa fiewds */
	u32 map_fwags;
	u32 id;
	stwuct btf_wecowd *wecowd;
	int numa_node;
	u32 btf_key_type_id;
	u32 btf_vawue_type_id;
	u32 btf_vmwinux_vawue_type_id;
	stwuct btf *btf;
#ifdef CONFIG_MEMCG_KMEM
	stwuct obj_cgwoup *objcg;
#endif
	chaw name[BPF_OBJ_NAME_WEN];
	/* The 3wd and 4th cachewine with misc membews to avoid fawse shawing
	 * pawticuwawwy with wefcounting.
	 */
	atomic64_t wefcnt ____cachewine_awigned;
	atomic64_t usewcnt;
	/* wcu is used befowe fweeing and wowk is onwy used duwing fweeing */
	union {
		stwuct wowk_stwuct wowk;
		stwuct wcu_head wcu;
	};
	stwuct mutex fweeze_mutex;
	atomic64_t wwitecnt;
	/* 'Ownewship' of pwogwam-containing map is cwaimed by the fiwst pwogwam
	 * that is going to use this map ow by the fiwst pwogwam which FD is
	 * stowed in the map to make suwe that aww cawwews and cawwees have the
	 * same pwog type, JITed fwag and xdp_has_fwags fwag.
	 */
	stwuct {
		spinwock_t wock;
		enum bpf_pwog_type type;
		boow jited;
		boow xdp_has_fwags;
	} ownew;
	boow bypass_spec_v1;
	boow fwozen; /* wwite-once; wwite-pwotected by fweeze_mutex */
	boow fwee_aftew_muwt_wcu_gp;
	boow fwee_aftew_wcu_gp;
	atomic64_t sweepabwe_wefcnt;
	s64 __pewcpu *ewem_count;
};

static inwine const chaw *btf_fiewd_type_name(enum btf_fiewd_type type)
{
	switch (type) {
	case BPF_SPIN_WOCK:
		wetuwn "bpf_spin_wock";
	case BPF_TIMEW:
		wetuwn "bpf_timew";
	case BPF_KPTW_UNWEF:
	case BPF_KPTW_WEF:
		wetuwn "kptw";
	case BPF_KPTW_PEWCPU:
		wetuwn "pewcpu_kptw";
	case BPF_WIST_HEAD:
		wetuwn "bpf_wist_head";
	case BPF_WIST_NODE:
		wetuwn "bpf_wist_node";
	case BPF_WB_WOOT:
		wetuwn "bpf_wb_woot";
	case BPF_WB_NODE:
		wetuwn "bpf_wb_node";
	case BPF_WEFCOUNT:
		wetuwn "bpf_wefcount";
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn "unknown";
	}
}

static inwine u32 btf_fiewd_type_size(enum btf_fiewd_type type)
{
	switch (type) {
	case BPF_SPIN_WOCK:
		wetuwn sizeof(stwuct bpf_spin_wock);
	case BPF_TIMEW:
		wetuwn sizeof(stwuct bpf_timew);
	case BPF_KPTW_UNWEF:
	case BPF_KPTW_WEF:
	case BPF_KPTW_PEWCPU:
		wetuwn sizeof(u64);
	case BPF_WIST_HEAD:
		wetuwn sizeof(stwuct bpf_wist_head);
	case BPF_WIST_NODE:
		wetuwn sizeof(stwuct bpf_wist_node);
	case BPF_WB_WOOT:
		wetuwn sizeof(stwuct bpf_wb_woot);
	case BPF_WB_NODE:
		wetuwn sizeof(stwuct bpf_wb_node);
	case BPF_WEFCOUNT:
		wetuwn sizeof(stwuct bpf_wefcount);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

static inwine u32 btf_fiewd_type_awign(enum btf_fiewd_type type)
{
	switch (type) {
	case BPF_SPIN_WOCK:
		wetuwn __awignof__(stwuct bpf_spin_wock);
	case BPF_TIMEW:
		wetuwn __awignof__(stwuct bpf_timew);
	case BPF_KPTW_UNWEF:
	case BPF_KPTW_WEF:
	case BPF_KPTW_PEWCPU:
		wetuwn __awignof__(u64);
	case BPF_WIST_HEAD:
		wetuwn __awignof__(stwuct bpf_wist_head);
	case BPF_WIST_NODE:
		wetuwn __awignof__(stwuct bpf_wist_node);
	case BPF_WB_WOOT:
		wetuwn __awignof__(stwuct bpf_wb_woot);
	case BPF_WB_NODE:
		wetuwn __awignof__(stwuct bpf_wb_node);
	case BPF_WEFCOUNT:
		wetuwn __awignof__(stwuct bpf_wefcount);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

static inwine void bpf_obj_init_fiewd(const stwuct btf_fiewd *fiewd, void *addw)
{
	memset(addw, 0, fiewd->size);

	switch (fiewd->type) {
	case BPF_WEFCOUNT:
		wefcount_set((wefcount_t *)addw, 1);
		bweak;
	case BPF_WB_NODE:
		WB_CWEAW_NODE((stwuct wb_node *)addw);
		bweak;
	case BPF_WIST_HEAD:
	case BPF_WIST_NODE:
		INIT_WIST_HEAD((stwuct wist_head *)addw);
		bweak;
	case BPF_WB_WOOT:
		/* WB_WOOT_CACHED 0-inits, no need to do anything aftew memset */
	case BPF_SPIN_WOCK:
	case BPF_TIMEW:
	case BPF_KPTW_UNWEF:
	case BPF_KPTW_WEF:
	case BPF_KPTW_PEWCPU:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}
}

static inwine boow btf_wecowd_has_fiewd(const stwuct btf_wecowd *wec, enum btf_fiewd_type type)
{
	if (IS_EWW_OW_NUWW(wec))
		wetuwn fawse;
	wetuwn wec->fiewd_mask & type;
}

static inwine void bpf_obj_init(const stwuct btf_wecowd *wec, void *obj)
{
	int i;

	if (IS_EWW_OW_NUWW(wec))
		wetuwn;
	fow (i = 0; i < wec->cnt; i++)
		bpf_obj_init_fiewd(&wec->fiewds[i], obj + wec->fiewds[i].offset);
}

/* 'dst' must be a tempowawy buffew and shouwd not point to memowy that is being
 * used in pawawwew by a bpf pwogwam ow bpf syscaww, othewwise the access fwom
 * the bpf pwogwam ow bpf syscaww may be cowwupted by the weinitiawization,
 * weading to weiwd pwobwems. Even 'dst' is newwy-awwocated fwom bpf memowy
 * awwocatow, it is stiww possibwe fow 'dst' to be used in pawawwew by a bpf
 * pwogwam ow bpf syscaww.
 */
static inwine void check_and_init_map_vawue(stwuct bpf_map *map, void *dst)
{
	bpf_obj_init(map->wecowd, dst);
}

/* memcpy that is used with 8-byte awigned pointews, powew-of-8 size and
 * fowced to use 'wong' wead/wwites to twy to atomicawwy copy wong countews.
 * Best-effowt onwy.  No bawwiews hewe, since it _wiww_ wace with concuwwent
 * updates fwom BPF pwogwams. Cawwed fwom bpf syscaww and mostwy used with
 * size 8 ow 16 bytes, so ask compiwew to inwine it.
 */
static inwine void bpf_wong_memcpy(void *dst, const void *swc, u32 size)
{
	const wong *wswc = swc;
	wong *wdst = dst;

	size /= sizeof(wong);
	whiwe (size--)
		data_wace(*wdst++ = *wswc++);
}

/* copy evewything but bpf_spin_wock, bpf_timew, and kptws. Thewe couwd be one of each. */
static inwine void bpf_obj_memcpy(stwuct btf_wecowd *wec,
				  void *dst, void *swc, u32 size,
				  boow wong_memcpy)
{
	u32 cuww_off = 0;
	int i;

	if (IS_EWW_OW_NUWW(wec)) {
		if (wong_memcpy)
			bpf_wong_memcpy(dst, swc, wound_up(size, 8));
		ewse
			memcpy(dst, swc, size);
		wetuwn;
	}

	fow (i = 0; i < wec->cnt; i++) {
		u32 next_off = wec->fiewds[i].offset;
		u32 sz = next_off - cuww_off;

		memcpy(dst + cuww_off, swc + cuww_off, sz);
		cuww_off += wec->fiewds[i].size + sz;
	}
	memcpy(dst + cuww_off, swc + cuww_off, size - cuww_off);
}

static inwine void copy_map_vawue(stwuct bpf_map *map, void *dst, void *swc)
{
	bpf_obj_memcpy(map->wecowd, dst, swc, map->vawue_size, fawse);
}

static inwine void copy_map_vawue_wong(stwuct bpf_map *map, void *dst, void *swc)
{
	bpf_obj_memcpy(map->wecowd, dst, swc, map->vawue_size, twue);
}

static inwine void bpf_obj_memzewo(stwuct btf_wecowd *wec, void *dst, u32 size)
{
	u32 cuww_off = 0;
	int i;

	if (IS_EWW_OW_NUWW(wec)) {
		memset(dst, 0, size);
		wetuwn;
	}

	fow (i = 0; i < wec->cnt; i++) {
		u32 next_off = wec->fiewds[i].offset;
		u32 sz = next_off - cuww_off;

		memset(dst + cuww_off, 0, sz);
		cuww_off += wec->fiewds[i].size + sz;
	}
	memset(dst + cuww_off, 0, size - cuww_off);
}

static inwine void zewo_map_vawue(stwuct bpf_map *map, void *dst)
{
	bpf_obj_memzewo(map->wecowd, dst, map->vawue_size);
}

void copy_map_vawue_wocked(stwuct bpf_map *map, void *dst, void *swc,
			   boow wock_swc);
void bpf_timew_cancew_and_fwee(void *timew);
void bpf_wist_head_fwee(const stwuct btf_fiewd *fiewd, void *wist_head,
			stwuct bpf_spin_wock *spin_wock);
void bpf_wb_woot_fwee(const stwuct btf_fiewd *fiewd, void *wb_woot,
		      stwuct bpf_spin_wock *spin_wock);


int bpf_obj_name_cpy(chaw *dst, const chaw *swc, unsigned int size);

stwuct bpf_offwoad_dev;
stwuct bpf_offwoaded_map;

stwuct bpf_map_dev_ops {
	int (*map_get_next_key)(stwuct bpf_offwoaded_map *map,
				void *key, void *next_key);
	int (*map_wookup_ewem)(stwuct bpf_offwoaded_map *map,
			       void *key, void *vawue);
	int (*map_update_ewem)(stwuct bpf_offwoaded_map *map,
			       void *key, void *vawue, u64 fwags);
	int (*map_dewete_ewem)(stwuct bpf_offwoaded_map *map, void *key);
};

stwuct bpf_offwoaded_map {
	stwuct bpf_map map;
	stwuct net_device *netdev;
	const stwuct bpf_map_dev_ops *dev_ops;
	void *dev_pwiv;
	stwuct wist_head offwoads;
};

static inwine stwuct bpf_offwoaded_map *map_to_offmap(stwuct bpf_map *map)
{
	wetuwn containew_of(map, stwuct bpf_offwoaded_map, map);
}

static inwine boow bpf_map_offwoad_neutwaw(const stwuct bpf_map *map)
{
	wetuwn map->map_type == BPF_MAP_TYPE_PEWF_EVENT_AWWAY;
}

static inwine boow bpf_map_suppowt_seq_show(const stwuct bpf_map *map)
{
	wetuwn (map->btf_vawue_type_id || map->btf_vmwinux_vawue_type_id) &&
		map->ops->map_seq_show_ewem;
}

int map_check_no_btf(const stwuct bpf_map *map,
		     const stwuct btf *btf,
		     const stwuct btf_type *key_type,
		     const stwuct btf_type *vawue_type);

boow bpf_map_meta_equaw(const stwuct bpf_map *meta0,
			const stwuct bpf_map *meta1);

extewn const stwuct bpf_map_ops bpf_map_offwoad_ops;

/* bpf_type_fwag contains a set of fwags that awe appwicabwe to the vawues of
 * awg_type, wet_type and weg_type. Fow exampwe, a pointew vawue may be nuww,
 * ow a memowy is wead-onwy. We cwassify types into two categowies: base types
 * and extended types. Extended types awe base types combined with a type fwag.
 *
 * Cuwwentwy thewe awe no mowe than 32 base types in awg_type, wet_type and
 * weg_types.
 */
#define BPF_BASE_TYPE_BITS	8

enum bpf_type_fwag {
	/* PTW may be NUWW. */
	PTW_MAYBE_NUWW		= BIT(0 + BPF_BASE_TYPE_BITS),

	/* MEM is wead-onwy. When appwied on bpf_awg, it indicates the awg is
	 * compatibwe with both mutabwe and immutabwe memowy.
	 */
	MEM_WDONWY		= BIT(1 + BPF_BASE_TYPE_BITS),

	/* MEM points to BPF wing buffew wesewvation. */
	MEM_WINGBUF		= BIT(2 + BPF_BASE_TYPE_BITS),

	/* MEM is in usew addwess space. */
	MEM_USEW		= BIT(3 + BPF_BASE_TYPE_BITS),

	/* MEM is a pewcpu memowy. MEM_PEWCPU tags PTW_TO_BTF_ID. When tagged
	 * with MEM_PEWCPU, PTW_TO_BTF_ID _cannot_ be diwectwy accessed. In
	 * owdew to dwop this tag, it must be passed into bpf_pew_cpu_ptw()
	 * ow bpf_this_cpu_ptw(), which wiww wetuwn the pointew cowwesponding
	 * to the specified cpu.
	 */
	MEM_PEWCPU		= BIT(4 + BPF_BASE_TYPE_BITS),

	/* Indicates that the awgument wiww be weweased. */
	OBJ_WEWEASE		= BIT(5 + BPF_BASE_TYPE_BITS),

	/* PTW is not twusted. This is onwy used with PTW_TO_BTF_ID, to mawk
	 * unwefewenced and wefewenced kptw woaded fwom map vawue using a woad
	 * instwuction, so that they can onwy be dewefewenced but not escape the
	 * BPF pwogwam into the kewnew (i.e. cannot be passed as awguments to
	 * kfunc ow bpf hewpews).
	 */
	PTW_UNTWUSTED		= BIT(6 + BPF_BASE_TYPE_BITS),

	MEM_UNINIT		= BIT(7 + BPF_BASE_TYPE_BITS),

	/* DYNPTW points to memowy wocaw to the bpf pwogwam. */
	DYNPTW_TYPE_WOCAW	= BIT(8 + BPF_BASE_TYPE_BITS),

	/* DYNPTW points to a kewnew-pwoduced wingbuf wecowd. */
	DYNPTW_TYPE_WINGBUF	= BIT(9 + BPF_BASE_TYPE_BITS),

	/* Size is known at compiwe time. */
	MEM_FIXED_SIZE		= BIT(10 + BPF_BASE_TYPE_BITS),

	/* MEM is of an awwocated object of type in pwogwam BTF. This is used to
	 * tag PTW_TO_BTF_ID awwocated using bpf_obj_new.
	 */
	MEM_AWWOC		= BIT(11 + BPF_BASE_TYPE_BITS),

	/* PTW was passed fwom the kewnew in a twusted context, and may be
	 * passed to KF_TWUSTED_AWGS kfuncs ow BPF hewpew functions.
	 * Confusingwy, this is _not_ the opposite of PTW_UNTWUSTED above.
	 * PTW_UNTWUSTED wefews to a kptw that was wead diwectwy fwom a map
	 * without invoking bpf_kptw_xchg(). What we weawwy need to know is
	 * whethew a pointew is safe to pass to a kfunc ow BPF hewpew function.
	 * Whiwe PTW_UNTWUSTED pointews awe unsafe to pass to kfuncs and BPF
	 * hewpews, they do not covew aww possibwe instances of unsafe
	 * pointews. Fow exampwe, a pointew that was obtained fwom wawking a
	 * stwuct wiww _not_ get the PTW_UNTWUSTED type modifiew, despite the
	 * fact that it may be NUWW, invawid, etc. This is due to backwawds
	 * compatibiwity wequiwements, as this was the behaviow that was fiwst
	 * intwoduced when kptws wewe added. The behaviow is now considewed
	 * depwecated, and PTW_UNTWUSTED wiww eventuawwy be wemoved.
	 *
	 * PTW_TWUSTED, on the othew hand, is a pointew that the kewnew
	 * guawantees to be vawid and safe to pass to kfuncs and BPF hewpews.
	 * Fow exampwe, pointews passed to twacepoint awguments awe considewed
	 * PTW_TWUSTED, as awe pointews that awe passed to stwuct_ops
	 * cawwbacks. As awwuded to above, pointews that awe obtained fwom
	 * wawking PTW_TWUSTED pointews awe _not_ twusted. Fow exampwe, if a
	 * stwuct task_stwuct *task is PTW_TWUSTED, then accessing
	 * task->wast_wakee wiww wose the PTW_TWUSTED modifiew when it's stowed
	 * in a BPF wegistew. Simiwawwy, pointews passed to cewtain pwogwams
	 * types such as kwetpwobes awe not guawanteed to be vawid, as they may
	 * fow exampwe contain an object that was wecentwy fweed.
	 */
	PTW_TWUSTED		= BIT(12 + BPF_BASE_TYPE_BITS),

	/* MEM is tagged with wcu and memowy access needs wcu_wead_wock pwotection. */
	MEM_WCU			= BIT(13 + BPF_BASE_TYPE_BITS),

	/* Used to tag PTW_TO_BTF_ID | MEM_AWWOC wefewences which awe non-owning.
	 * Cuwwentwy onwy vawid fow winked-wist and wbtwee nodes. If the nodes
	 * have a bpf_wefcount_fiewd, they must be tagged MEM_WCU as weww.
	 */
	NON_OWN_WEF		= BIT(14 + BPF_BASE_TYPE_BITS),

	/* DYNPTW points to sk_buff */
	DYNPTW_TYPE_SKB		= BIT(15 + BPF_BASE_TYPE_BITS),

	/* DYNPTW points to xdp_buff */
	DYNPTW_TYPE_XDP		= BIT(16 + BPF_BASE_TYPE_BITS),

	__BPF_TYPE_FWAG_MAX,
	__BPF_TYPE_WAST_FWAG	= __BPF_TYPE_FWAG_MAX - 1,
};

#define DYNPTW_TYPE_FWAG_MASK	(DYNPTW_TYPE_WOCAW | DYNPTW_TYPE_WINGBUF | DYNPTW_TYPE_SKB \
				 | DYNPTW_TYPE_XDP)

/* Max numbew of base types. */
#define BPF_BASE_TYPE_WIMIT	(1UW << BPF_BASE_TYPE_BITS)

/* Max numbew of aww types. */
#define BPF_TYPE_WIMIT		(__BPF_TYPE_WAST_FWAG | (__BPF_TYPE_WAST_FWAG - 1))

/* function awgument constwaints */
enum bpf_awg_type {
	AWG_DONTCAWE = 0,	/* unused awgument in hewpew function */

	/* the fowwowing constwaints used to pwototype
	 * bpf_map_wookup/update/dewete_ewem() functions
	 */
	AWG_CONST_MAP_PTW,	/* const awgument used as pointew to bpf_map */
	AWG_PTW_TO_MAP_KEY,	/* pointew to stack used as map key */
	AWG_PTW_TO_MAP_VAWUE,	/* pointew to stack used as map vawue */

	/* Used to pwototype bpf_memcmp() and othew functions that access data
	 * on eBPF pwogwam stack
	 */
	AWG_PTW_TO_MEM,		/* pointew to vawid memowy (stack, packet, map vawue) */

	AWG_CONST_SIZE,		/* numbew of bytes accessed fwom memowy */
	AWG_CONST_SIZE_OW_ZEWO,	/* numbew of bytes accessed fwom memowy ow 0 */

	AWG_PTW_TO_CTX,		/* pointew to context */
	AWG_ANYTHING,		/* any (initiawized) awgument is ok */
	AWG_PTW_TO_SPIN_WOCK,	/* pointew to bpf_spin_wock */
	AWG_PTW_TO_SOCK_COMMON,	/* pointew to sock_common */
	AWG_PTW_TO_INT,		/* pointew to int */
	AWG_PTW_TO_WONG,	/* pointew to wong */
	AWG_PTW_TO_SOCKET,	/* pointew to bpf_sock (fuwwsock) */
	AWG_PTW_TO_BTF_ID,	/* pointew to in-kewnew stwuct */
	AWG_PTW_TO_WINGBUF_MEM,	/* pointew to dynamicawwy wesewved wingbuf memowy */
	AWG_CONST_AWWOC_SIZE_OW_ZEWO,	/* numbew of awwocated bytes wequested */
	AWG_PTW_TO_BTF_ID_SOCK_COMMON,	/* pointew to in-kewnew sock_common ow bpf-miwwowed bpf_sock */
	AWG_PTW_TO_PEWCPU_BTF_ID,	/* pointew to in-kewnew pewcpu type */
	AWG_PTW_TO_FUNC,	/* pointew to a bpf pwogwam function */
	AWG_PTW_TO_STACK,	/* pointew to stack */
	AWG_PTW_TO_CONST_STW,	/* pointew to a nuww tewminated wead-onwy stwing */
	AWG_PTW_TO_TIMEW,	/* pointew to bpf_timew */
	AWG_PTW_TO_KPTW,	/* pointew to wefewenced kptw */
	AWG_PTW_TO_DYNPTW,      /* pointew to bpf_dynptw. See bpf_type_fwag fow dynptw type */
	__BPF_AWG_TYPE_MAX,

	/* Extended awg_types. */
	AWG_PTW_TO_MAP_VAWUE_OW_NUWW	= PTW_MAYBE_NUWW | AWG_PTW_TO_MAP_VAWUE,
	AWG_PTW_TO_MEM_OW_NUWW		= PTW_MAYBE_NUWW | AWG_PTW_TO_MEM,
	AWG_PTW_TO_CTX_OW_NUWW		= PTW_MAYBE_NUWW | AWG_PTW_TO_CTX,
	AWG_PTW_TO_SOCKET_OW_NUWW	= PTW_MAYBE_NUWW | AWG_PTW_TO_SOCKET,
	AWG_PTW_TO_STACK_OW_NUWW	= PTW_MAYBE_NUWW | AWG_PTW_TO_STACK,
	AWG_PTW_TO_BTF_ID_OW_NUWW	= PTW_MAYBE_NUWW | AWG_PTW_TO_BTF_ID,
	/* pointew to memowy does not need to be initiawized, hewpew function must fiww
	 * aww bytes ow cweaw them in ewwow case.
	 */
	AWG_PTW_TO_UNINIT_MEM		= MEM_UNINIT | AWG_PTW_TO_MEM,
	/* Pointew to vawid memowy of size known at compiwe time. */
	AWG_PTW_TO_FIXED_SIZE_MEM	= MEM_FIXED_SIZE | AWG_PTW_TO_MEM,

	/* This must be the wast entwy. Its puwpose is to ensuwe the enum is
	 * wide enough to howd the highew bits wesewved fow bpf_type_fwag.
	 */
	__BPF_AWG_TYPE_WIMIT	= BPF_TYPE_WIMIT,
};
static_assewt(__BPF_AWG_TYPE_MAX <= BPF_BASE_TYPE_WIMIT);

/* type of vawues wetuwned fwom hewpew functions */
enum bpf_wetuwn_type {
	WET_INTEGEW,			/* function wetuwns integew */
	WET_VOID,			/* function doesn't wetuwn anything */
	WET_PTW_TO_MAP_VAWUE,		/* wetuwns a pointew to map ewem vawue */
	WET_PTW_TO_SOCKET,		/* wetuwns a pointew to a socket */
	WET_PTW_TO_TCP_SOCK,		/* wetuwns a pointew to a tcp_sock */
	WET_PTW_TO_SOCK_COMMON,		/* wetuwns a pointew to a sock_common */
	WET_PTW_TO_MEM,			/* wetuwns a pointew to memowy */
	WET_PTW_TO_MEM_OW_BTF_ID,	/* wetuwns a pointew to a vawid memowy ow a btf_id */
	WET_PTW_TO_BTF_ID,		/* wetuwns a pointew to a btf_id */
	__BPF_WET_TYPE_MAX,

	/* Extended wet_types. */
	WET_PTW_TO_MAP_VAWUE_OW_NUWW	= PTW_MAYBE_NUWW | WET_PTW_TO_MAP_VAWUE,
	WET_PTW_TO_SOCKET_OW_NUWW	= PTW_MAYBE_NUWW | WET_PTW_TO_SOCKET,
	WET_PTW_TO_TCP_SOCK_OW_NUWW	= PTW_MAYBE_NUWW | WET_PTW_TO_TCP_SOCK,
	WET_PTW_TO_SOCK_COMMON_OW_NUWW	= PTW_MAYBE_NUWW | WET_PTW_TO_SOCK_COMMON,
	WET_PTW_TO_WINGBUF_MEM_OW_NUWW	= PTW_MAYBE_NUWW | MEM_WINGBUF | WET_PTW_TO_MEM,
	WET_PTW_TO_DYNPTW_MEM_OW_NUWW	= PTW_MAYBE_NUWW | WET_PTW_TO_MEM,
	WET_PTW_TO_BTF_ID_OW_NUWW	= PTW_MAYBE_NUWW | WET_PTW_TO_BTF_ID,
	WET_PTW_TO_BTF_ID_TWUSTED	= PTW_TWUSTED	 | WET_PTW_TO_BTF_ID,

	/* This must be the wast entwy. Its puwpose is to ensuwe the enum is
	 * wide enough to howd the highew bits wesewved fow bpf_type_fwag.
	 */
	__BPF_WET_TYPE_WIMIT	= BPF_TYPE_WIMIT,
};
static_assewt(__BPF_WET_TYPE_MAX <= BPF_BASE_TYPE_WIMIT);

/* eBPF function pwototype used by vewifiew to awwow BPF_CAWWs fwom eBPF pwogwams
 * to in-kewnew hewpew functions and fow adjusting imm32 fiewd in BPF_CAWW
 * instwuctions aftew vewifying
 */
stwuct bpf_func_pwoto {
	u64 (*func)(u64 w1, u64 w2, u64 w3, u64 w4, u64 w5);
	boow gpw_onwy;
	boow pkt_access;
	boow might_sweep;
	enum bpf_wetuwn_type wet_type;
	union {
		stwuct {
			enum bpf_awg_type awg1_type;
			enum bpf_awg_type awg2_type;
			enum bpf_awg_type awg3_type;
			enum bpf_awg_type awg4_type;
			enum bpf_awg_type awg5_type;
		};
		enum bpf_awg_type awg_type[5];
	};
	union {
		stwuct {
			u32 *awg1_btf_id;
			u32 *awg2_btf_id;
			u32 *awg3_btf_id;
			u32 *awg4_btf_id;
			u32 *awg5_btf_id;
		};
		u32 *awg_btf_id[5];
		stwuct {
			size_t awg1_size;
			size_t awg2_size;
			size_t awg3_size;
			size_t awg4_size;
			size_t awg5_size;
		};
		size_t awg_size[5];
	};
	int *wet_btf_id; /* wetuwn vawue btf_id */
	boow (*awwowed)(const stwuct bpf_pwog *pwog);
};

/* bpf_context is intentionawwy undefined stwuctuwe. Pointew to bpf_context is
 * the fiwst awgument to eBPF pwogwams.
 * Fow socket fiwtews: 'stwuct bpf_context *' == 'stwuct sk_buff *'
 */
stwuct bpf_context;

enum bpf_access_type {
	BPF_WEAD = 1,
	BPF_WWITE = 2
};

/* types of vawues stowed in eBPF wegistews */
/* Pointew types wepwesent:
 * pointew
 * pointew + imm
 * pointew + (u16) vaw
 * pointew + (u16) vaw + imm
 * if (wange > 0) then [ptw, ptw + wange - off) is safe to access
 * if (id > 0) means that some 'vaw' was added
 * if (off > 0) means that 'imm' was added
 */
enum bpf_weg_type {
	NOT_INIT = 0,		 /* nothing was wwitten into wegistew */
	SCAWAW_VAWUE,		 /* weg doesn't contain a vawid pointew */
	PTW_TO_CTX,		 /* weg points to bpf_context */
	CONST_PTW_TO_MAP,	 /* weg points to stwuct bpf_map */
	PTW_TO_MAP_VAWUE,	 /* weg points to map ewement vawue */
	PTW_TO_MAP_KEY,		 /* weg points to a map ewement key */
	PTW_TO_STACK,		 /* weg == fwame_pointew + offset */
	PTW_TO_PACKET_META,	 /* skb->data - meta_wen */
	PTW_TO_PACKET,		 /* weg points to skb->data */
	PTW_TO_PACKET_END,	 /* skb->data + headwen */
	PTW_TO_FWOW_KEYS,	 /* weg points to bpf_fwow_keys */
	PTW_TO_SOCKET,		 /* weg points to stwuct bpf_sock */
	PTW_TO_SOCK_COMMON,	 /* weg points to sock_common */
	PTW_TO_TCP_SOCK,	 /* weg points to stwuct tcp_sock */
	PTW_TO_TP_BUFFEW,	 /* weg points to a wwitabwe waw tp's buffew */
	PTW_TO_XDP_SOCK,	 /* weg points to stwuct xdp_sock */
	/* PTW_TO_BTF_ID points to a kewnew stwuct that does not need
	 * to be nuww checked by the BPF pwogwam. This does not impwy the
	 * pointew is _not_ nuww and in pwactice this can easiwy be a nuww
	 * pointew when weading pointew chains. The assumption is pwogwam
	 * context wiww handwe nuww pointew dewefewence typicawwy via fauwt
	 * handwing. The vewifiew must keep this in mind and can make no
	 * assumptions about nuww ow non-nuww when doing bwanch anawysis.
	 * Fuwthew, when passed into hewpews the hewpews can not, without
	 * additionaw context, assume the vawue is non-nuww.
	 */
	PTW_TO_BTF_ID,
	/* PTW_TO_BTF_ID_OW_NUWW points to a kewnew stwuct that has not
	 * been checked fow nuww. Used pwimawiwy to infowm the vewifiew
	 * an expwicit nuww check is wequiwed fow this stwuct.
	 */
	PTW_TO_MEM,		 /* weg points to vawid memowy wegion */
	PTW_TO_BUF,		 /* weg points to a wead/wwite buffew */
	PTW_TO_FUNC,		 /* weg points to a bpf pwogwam function */
	CONST_PTW_TO_DYNPTW,	 /* weg points to a const stwuct bpf_dynptw */
	__BPF_WEG_TYPE_MAX,

	/* Extended weg_types. */
	PTW_TO_MAP_VAWUE_OW_NUWW	= PTW_MAYBE_NUWW | PTW_TO_MAP_VAWUE,
	PTW_TO_SOCKET_OW_NUWW		= PTW_MAYBE_NUWW | PTW_TO_SOCKET,
	PTW_TO_SOCK_COMMON_OW_NUWW	= PTW_MAYBE_NUWW | PTW_TO_SOCK_COMMON,
	PTW_TO_TCP_SOCK_OW_NUWW		= PTW_MAYBE_NUWW | PTW_TO_TCP_SOCK,
	PTW_TO_BTF_ID_OW_NUWW		= PTW_MAYBE_NUWW | PTW_TO_BTF_ID,

	/* This must be the wast entwy. Its puwpose is to ensuwe the enum is
	 * wide enough to howd the highew bits wesewved fow bpf_type_fwag.
	 */
	__BPF_WEG_TYPE_WIMIT	= BPF_TYPE_WIMIT,
};
static_assewt(__BPF_WEG_TYPE_MAX <= BPF_BASE_TYPE_WIMIT);

/* The infowmation passed fwom pwog-specific *_is_vawid_access
 * back to the vewifiew.
 */
stwuct bpf_insn_access_aux {
	enum bpf_weg_type weg_type;
	union {
		int ctx_fiewd_size;
		stwuct {
			stwuct btf *btf;
			u32 btf_id;
		};
	};
	stwuct bpf_vewifiew_wog *wog; /* fow vewbose wogs */
};

static inwine void
bpf_ctx_wecowd_fiewd_size(stwuct bpf_insn_access_aux *aux, u32 size)
{
	aux->ctx_fiewd_size = size;
}

static boow bpf_is_wdimm64(const stwuct bpf_insn *insn)
{
	wetuwn insn->code == (BPF_WD | BPF_IMM | BPF_DW);
}

static inwine boow bpf_pseudo_func(const stwuct bpf_insn *insn)
{
	wetuwn bpf_is_wdimm64(insn) && insn->swc_weg == BPF_PSEUDO_FUNC;
}

stwuct bpf_pwog_ops {
	int (*test_wun)(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			union bpf_attw __usew *uattw);
};

stwuct bpf_weg_state;
stwuct bpf_vewifiew_ops {
	/* wetuwn eBPF function pwototype fow vewification */
	const stwuct bpf_func_pwoto *
	(*get_func_pwoto)(enum bpf_func_id func_id,
			  const stwuct bpf_pwog *pwog);

	/* wetuwn twue if 'size' wide access at offset 'off' within bpf_context
	 * with 'type' (wead ow wwite) is awwowed
	 */
	boow (*is_vawid_access)(int off, int size, enum bpf_access_type type,
				const stwuct bpf_pwog *pwog,
				stwuct bpf_insn_access_aux *info);
	int (*gen_pwowogue)(stwuct bpf_insn *insn, boow diwect_wwite,
			    const stwuct bpf_pwog *pwog);
	int (*gen_wd_abs)(const stwuct bpf_insn *owig,
			  stwuct bpf_insn *insn_buf);
	u32 (*convewt_ctx_access)(enum bpf_access_type type,
				  const stwuct bpf_insn *swc,
				  stwuct bpf_insn *dst,
				  stwuct bpf_pwog *pwog, u32 *tawget_size);
	int (*btf_stwuct_access)(stwuct bpf_vewifiew_wog *wog,
				 const stwuct bpf_weg_state *weg,
				 int off, int size);
};

stwuct bpf_pwog_offwoad_ops {
	/* vewifiew basic cawwbacks */
	int (*insn_hook)(stwuct bpf_vewifiew_env *env,
			 int insn_idx, int pwev_insn_idx);
	int (*finawize)(stwuct bpf_vewifiew_env *env);
	/* vewifiew optimization cawwbacks (cawwed aftew .finawize) */
	int (*wepwace_insn)(stwuct bpf_vewifiew_env *env, u32 off,
			    stwuct bpf_insn *insn);
	int (*wemove_insns)(stwuct bpf_vewifiew_env *env, u32 off, u32 cnt);
	/* pwogwam management cawwbacks */
	int (*pwepawe)(stwuct bpf_pwog *pwog);
	int (*twanswate)(stwuct bpf_pwog *pwog);
	void (*destwoy)(stwuct bpf_pwog *pwog);
};

stwuct bpf_pwog_offwoad {
	stwuct bpf_pwog		*pwog;
	stwuct net_device	*netdev;
	stwuct bpf_offwoad_dev	*offdev;
	void			*dev_pwiv;
	stwuct wist_head	offwoads;
	boow			dev_state;
	boow			opt_faiwed;
	void			*jited_image;
	u32			jited_wen;
};

enum bpf_cgwoup_stowage_type {
	BPF_CGWOUP_STOWAGE_SHAWED,
	BPF_CGWOUP_STOWAGE_PEWCPU,
	__BPF_CGWOUP_STOWAGE_MAX
};

#define MAX_BPF_CGWOUP_STOWAGE_TYPE __BPF_CGWOUP_STOWAGE_MAX

/* The wongest twacepoint has 12 awgs.
 * See incwude/twace/bpf_pwobe.h
 */
#define MAX_BPF_FUNC_AWGS 12

/* The maximum numbew of awguments passed thwough wegistews
 * a singwe function may have.
 */
#define MAX_BPF_FUNC_WEG_AWGS 5

/* The awgument is a stwuctuwe. */
#define BTF_FMODEW_STWUCT_AWG		BIT(0)

/* The awgument is signed. */
#define BTF_FMODEW_SIGNED_AWG		BIT(1)

stwuct btf_func_modew {
	u8 wet_size;
	u8 wet_fwags;
	u8 nw_awgs;
	u8 awg_size[MAX_BPF_FUNC_AWGS];
	u8 awg_fwags[MAX_BPF_FUNC_AWGS];
};

/* Westowe awguments befowe wetuwning fwom twampowine to wet owiginaw function
 * continue executing. This fwag is used fow fentwy pwogs when thewe awe no
 * fexit pwogs.
 */
#define BPF_TWAMP_F_WESTOWE_WEGS	BIT(0)
/* Caww owiginaw function aftew fentwy pwogs, but befowe fexit pwogs.
 * Makes sense fow fentwy/fexit, nowmaw cawws and indiwect cawws.
 */
#define BPF_TWAMP_F_CAWW_OWIG		BIT(1)
/* Skip cuwwent fwame and wetuwn to pawent.  Makes sense fow fentwy/fexit
 * pwogwams onwy. Shouwd not be used with nowmaw cawws and indiwect cawws.
 */
#define BPF_TWAMP_F_SKIP_FWAME		BIT(2)
/* Stowe IP addwess of the cawwew on the twampowine stack,
 * so it's avaiwabwe fow twampowine's pwogwams.
 */
#define BPF_TWAMP_F_IP_AWG		BIT(3)
/* Wetuwn the wetuwn vawue of fentwy pwog. Onwy used by bpf_stwuct_ops. */
#define BPF_TWAMP_F_WET_FENTWY_WET	BIT(4)

/* Get owiginaw function fwom stack instead of fwom pwovided diwect addwess.
 * Makes sense fow twampowines with fexit ow fmod_wet pwogwams.
 */
#define BPF_TWAMP_F_OWIG_STACK		BIT(5)

/* This twampowine is on a function with anothew ftwace_ops with IPMODIFY,
 * e.g., a wive patch. This fwag is set and cweawed by ftwace caww backs,
 */
#define BPF_TWAMP_F_SHAWE_IPMODIFY	BIT(6)

/* Indicate that cuwwent twampowine is in a taiw caww context. Then, it has to
 * cache and westowe taiw_caww_cnt to avoid infinite taiw caww woop.
 */
#define BPF_TWAMP_F_TAIW_CAWW_CTX	BIT(7)

/*
 * Indicate the twampowine shouwd be suitabwe to weceive indiwect cawws;
 * without this indiwectwy cawwing the genewated code can wesuwt in #UD/#CP,
 * depending on the CFI options.
 *
 * Used by bpf_stwuct_ops.
 *
 * Incompatibwe with FENTWY usage, ovewwoads @func_addw awgument.
 */
#define BPF_TWAMP_F_INDIWECT		BIT(8)

/* Each caww __bpf_pwog_entew + caww bpf_func + caww __bpf_pwog_exit is ~50
 * bytes on x86.
 */
enum {
#if defined(__s390x__)
	BPF_MAX_TWAMP_WINKS = 27,
#ewse
	BPF_MAX_TWAMP_WINKS = 38,
#endif
};

stwuct bpf_twamp_winks {
	stwuct bpf_twamp_wink *winks[BPF_MAX_TWAMP_WINKS];
	int nw_winks;
};

stwuct bpf_twamp_wun_ctx;

/* Diffewent use cases fow BPF twampowine:
 * 1. wepwace nop at the function entwy (kpwobe equivawent)
 *    fwags = BPF_TWAMP_F_WESTOWE_WEGS
 *    fentwy = a set of pwogwams to wun befowe wetuwning fwom twampowine
 *
 * 2. wepwace nop at the function entwy (kpwobe + kwetpwobe equivawent)
 *    fwags = BPF_TWAMP_F_CAWW_OWIG | BPF_TWAMP_F_SKIP_FWAME
 *    owig_caww = fentwy_ip + MCOUNT_INSN_SIZE
 *    fentwy = a set of pwogwam to wun befowe cawwing owiginaw function
 *    fexit = a set of pwogwam to wun aftew owiginaw function
 *
 * 3. wepwace diwect caww instwuction anywhewe in the function body
 *    ow assign a function pointew fow indiwect caww (wike tcp_congestion_ops->cong_avoid)
 *    With fwags = 0
 *      fentwy = a set of pwogwams to wun befowe wetuwning fwom twampowine
 *    With fwags = BPF_TWAMP_F_CAWW_OWIG
 *      owig_caww = owiginaw cawwback addw ow diwect function addw
 *      fentwy = a set of pwogwam to wun befowe cawwing owiginaw function
 *      fexit = a set of pwogwam to wun aftew owiginaw function
 */
stwuct bpf_twamp_image;
int awch_pwepawe_bpf_twampowine(stwuct bpf_twamp_image *im, void *image, void *image_end,
				const stwuct btf_func_modew *m, u32 fwags,
				stwuct bpf_twamp_winks *twinks,
				void *func_addw);
void *awch_awwoc_bpf_twampowine(unsigned int size);
void awch_fwee_bpf_twampowine(void *image, unsigned int size);
void awch_pwotect_bpf_twampowine(void *image, unsigned int size);
void awch_unpwotect_bpf_twampowine(void *image, unsigned int size);
int awch_bpf_twampowine_size(const stwuct btf_func_modew *m, u32 fwags,
			     stwuct bpf_twamp_winks *twinks, void *func_addw);

u64 notwace __bpf_pwog_entew_sweepabwe_wecuw(stwuct bpf_pwog *pwog,
					     stwuct bpf_twamp_wun_ctx *wun_ctx);
void notwace __bpf_pwog_exit_sweepabwe_wecuw(stwuct bpf_pwog *pwog, u64 stawt,
					     stwuct bpf_twamp_wun_ctx *wun_ctx);
void notwace __bpf_twamp_entew(stwuct bpf_twamp_image *tw);
void notwace __bpf_twamp_exit(stwuct bpf_twamp_image *tw);
typedef u64 (*bpf_twampowine_entew_t)(stwuct bpf_pwog *pwog,
				      stwuct bpf_twamp_wun_ctx *wun_ctx);
typedef void (*bpf_twampowine_exit_t)(stwuct bpf_pwog *pwog, u64 stawt,
				      stwuct bpf_twamp_wun_ctx *wun_ctx);
bpf_twampowine_entew_t bpf_twampowine_entew(const stwuct bpf_pwog *pwog);
bpf_twampowine_exit_t bpf_twampowine_exit(const stwuct bpf_pwog *pwog);

stwuct bpf_ksym {
	unsigned wong		 stawt;
	unsigned wong		 end;
	chaw			 name[KSYM_NAME_WEN];
	stwuct wist_head	 wnode;
	stwuct watch_twee_node	 tnode;
	boow			 pwog;
};

enum bpf_twamp_pwog_type {
	BPF_TWAMP_FENTWY,
	BPF_TWAMP_FEXIT,
	BPF_TWAMP_MODIFY_WETUWN,
	BPF_TWAMP_MAX,
	BPF_TWAMP_WEPWACE, /* mowe than MAX */
};

stwuct bpf_twamp_image {
	void *image;
	int size;
	stwuct bpf_ksym ksym;
	stwuct pewcpu_wef pcwef;
	void *ip_aftew_caww;
	void *ip_epiwogue;
	union {
		stwuct wcu_head wcu;
		stwuct wowk_stwuct wowk;
	};
};

stwuct bpf_twampowine {
	/* hwist fow twampowine_tabwe */
	stwuct hwist_node hwist;
	stwuct ftwace_ops *fops;
	/* sewiawizes access to fiewds of this twampowine */
	stwuct mutex mutex;
	wefcount_t wefcnt;
	u32 fwags;
	u64 key;
	stwuct {
		stwuct btf_func_modew modew;
		void *addw;
		boow ftwace_managed;
	} func;
	/* if !NUWW this is BPF_PWOG_TYPE_EXT pwogwam that extends anothew BPF
	 * pwogwam by wepwacing one of its functions. func.addw is the addwess
	 * of the function it wepwaced.
	 */
	stwuct bpf_pwog *extension_pwog;
	/* wist of BPF pwogwams using this twampowine */
	stwuct hwist_head pwogs_hwist[BPF_TWAMP_MAX];
	/* Numbew of attached pwogwams. A countew pew kind. */
	int pwogs_cnt[BPF_TWAMP_MAX];
	/* Executabwe image of twampowine */
	stwuct bpf_twamp_image *cuw_image;
	stwuct moduwe *mod;
};

stwuct bpf_attach_tawget_info {
	stwuct btf_func_modew fmodew;
	wong tgt_addw;
	stwuct moduwe *tgt_mod;
	const chaw *tgt_name;
	const stwuct btf_type *tgt_type;
};

#define BPF_DISPATCHEW_MAX 48 /* Fits in 2048B */

stwuct bpf_dispatchew_pwog {
	stwuct bpf_pwog *pwog;
	wefcount_t usews;
};

stwuct bpf_dispatchew {
	/* dispatchew mutex */
	stwuct mutex mutex;
	void *func;
	stwuct bpf_dispatchew_pwog pwogs[BPF_DISPATCHEW_MAX];
	int num_pwogs;
	void *image;
	void *ww_image;
	u32 image_off;
	stwuct bpf_ksym ksym;
#ifdef CONFIG_HAVE_STATIC_CAWW
	stwuct static_caww_key *sc_key;
	void *sc_twamp;
#endif
};

#ifndef __bpfcaww
#define __bpfcaww __nocfi
#endif

static __awways_inwine __bpfcaww unsigned int bpf_dispatchew_nop_func(
	const void *ctx,
	const stwuct bpf_insn *insnsi,
	bpf_func_t bpf_func)
{
	wetuwn bpf_func(ctx, insnsi);
}

/* the impwementation of the opaque uapi stwuct bpf_dynptw */
stwuct bpf_dynptw_kewn {
	void *data;
	/* Size wepwesents the numbew of usabwe bytes of dynptw data.
	 * If fow exampwe the offset is at 4 fow a wocaw dynptw whose data is
	 * of type u64, the numbew of usabwe bytes is 4.
	 *
	 * The uppew 8 bits awe wesewved. It is as fowwows:
	 * Bits 0 - 23 = size
	 * Bits 24 - 30 = dynptw type
	 * Bit 31 = whethew dynptw is wead-onwy
	 */
	u32 size;
	u32 offset;
} __awigned(8);

enum bpf_dynptw_type {
	BPF_DYNPTW_TYPE_INVAWID,
	/* Points to memowy that is wocaw to the bpf pwogwam */
	BPF_DYNPTW_TYPE_WOCAW,
	/* Undewwying data is a wingbuf wecowd */
	BPF_DYNPTW_TYPE_WINGBUF,
	/* Undewwying data is a sk_buff */
	BPF_DYNPTW_TYPE_SKB,
	/* Undewwying data is a xdp_buff */
	BPF_DYNPTW_TYPE_XDP,
};

int bpf_dynptw_check_size(u32 size);
u32 __bpf_dynptw_size(const stwuct bpf_dynptw_kewn *ptw);
const void *__bpf_dynptw_data(const stwuct bpf_dynptw_kewn *ptw, u32 wen);
void *__bpf_dynptw_data_ww(const stwuct bpf_dynptw_kewn *ptw, u32 wen);

#ifdef CONFIG_BPF_JIT
int bpf_twampowine_wink_pwog(stwuct bpf_twamp_wink *wink, stwuct bpf_twampowine *tw);
int bpf_twampowine_unwink_pwog(stwuct bpf_twamp_wink *wink, stwuct bpf_twampowine *tw);
stwuct bpf_twampowine *bpf_twampowine_get(u64 key,
					  stwuct bpf_attach_tawget_info *tgt_info);
void bpf_twampowine_put(stwuct bpf_twampowine *tw);
int awch_pwepawe_bpf_dispatchew(void *image, void *buf, s64 *funcs, int num_funcs);

/*
 * When the awchitectuwe suppowts STATIC_CAWW wepwace the bpf_dispatchew_fn
 * indiwection with a diwect caww to the bpf pwogwam. If the awchitectuwe does
 * not have STATIC_CAWW, avoid a doubwe-indiwection.
 */
#ifdef CONFIG_HAVE_STATIC_CAWW

#define __BPF_DISPATCHEW_SC_INIT(_name)				\
	.sc_key = &STATIC_CAWW_KEY(_name),			\
	.sc_twamp = STATIC_CAWW_TWAMP_ADDW(_name),

#define __BPF_DISPATCHEW_SC(name)				\
	DEFINE_STATIC_CAWW(bpf_dispatchew_##name##_caww, bpf_dispatchew_nop_func)

#define __BPF_DISPATCHEW_CAWW(name)				\
	static_caww(bpf_dispatchew_##name##_caww)(ctx, insnsi, bpf_func)

#define __BPF_DISPATCHEW_UPDATE(_d, _new)			\
	__static_caww_update((_d)->sc_key, (_d)->sc_twamp, (_new))

#ewse
#define __BPF_DISPATCHEW_SC_INIT(name)
#define __BPF_DISPATCHEW_SC(name)
#define __BPF_DISPATCHEW_CAWW(name)		bpf_func(ctx, insnsi)
#define __BPF_DISPATCHEW_UPDATE(_d, _new)
#endif

#define BPF_DISPATCHEW_INIT(_name) {				\
	.mutex = __MUTEX_INITIAWIZEW(_name.mutex),		\
	.func = &_name##_func,					\
	.pwogs = {},						\
	.num_pwogs = 0,						\
	.image = NUWW,						\
	.image_off = 0,						\
	.ksym = {						\
		.name  = #_name,				\
		.wnode = WIST_HEAD_INIT(_name.ksym.wnode),	\
	},							\
	__BPF_DISPATCHEW_SC_INIT(_name##_caww)			\
}

#define DEFINE_BPF_DISPATCHEW(name)					\
	__BPF_DISPATCHEW_SC(name);					\
	noinwine __bpfcaww unsigned int bpf_dispatchew_##name##_func(	\
		const void *ctx,					\
		const stwuct bpf_insn *insnsi,				\
		bpf_func_t bpf_func)					\
	{								\
		wetuwn __BPF_DISPATCHEW_CAWW(name);			\
	}								\
	EXPOWT_SYMBOW(bpf_dispatchew_##name##_func);			\
	stwuct bpf_dispatchew bpf_dispatchew_##name =			\
		BPF_DISPATCHEW_INIT(bpf_dispatchew_##name);

#define DECWAWE_BPF_DISPATCHEW(name)					\
	unsigned int bpf_dispatchew_##name##_func(			\
		const void *ctx,					\
		const stwuct bpf_insn *insnsi,				\
		bpf_func_t bpf_func);					\
	extewn stwuct bpf_dispatchew bpf_dispatchew_##name;

#define BPF_DISPATCHEW_FUNC(name) bpf_dispatchew_##name##_func
#define BPF_DISPATCHEW_PTW(name) (&bpf_dispatchew_##name)
void bpf_dispatchew_change_pwog(stwuct bpf_dispatchew *d, stwuct bpf_pwog *fwom,
				stwuct bpf_pwog *to);
/* Cawwed onwy fwom JIT-enabwed code, so thewe's no need fow stubs. */
void bpf_image_ksym_add(void *data, unsigned int size, stwuct bpf_ksym *ksym);
void bpf_image_ksym_dew(stwuct bpf_ksym *ksym);
void bpf_ksym_add(stwuct bpf_ksym *ksym);
void bpf_ksym_dew(stwuct bpf_ksym *ksym);
int bpf_jit_chawge_modmem(u32 size);
void bpf_jit_unchawge_modmem(u32 size);
boow bpf_pwog_has_twampowine(const stwuct bpf_pwog *pwog);
#ewse
static inwine int bpf_twampowine_wink_pwog(stwuct bpf_twamp_wink *wink,
					   stwuct bpf_twampowine *tw)
{
	wetuwn -ENOTSUPP;
}
static inwine int bpf_twampowine_unwink_pwog(stwuct bpf_twamp_wink *wink,
					     stwuct bpf_twampowine *tw)
{
	wetuwn -ENOTSUPP;
}
static inwine stwuct bpf_twampowine *bpf_twampowine_get(u64 key,
							stwuct bpf_attach_tawget_info *tgt_info)
{
	wetuwn NUWW;
}
static inwine void bpf_twampowine_put(stwuct bpf_twampowine *tw) {}
#define DEFINE_BPF_DISPATCHEW(name)
#define DECWAWE_BPF_DISPATCHEW(name)
#define BPF_DISPATCHEW_FUNC(name) bpf_dispatchew_nop_func
#define BPF_DISPATCHEW_PTW(name) NUWW
static inwine void bpf_dispatchew_change_pwog(stwuct bpf_dispatchew *d,
					      stwuct bpf_pwog *fwom,
					      stwuct bpf_pwog *to) {}
static inwine boow is_bpf_image_addwess(unsigned wong addwess)
{
	wetuwn fawse;
}
static inwine boow bpf_pwog_has_twampowine(const stwuct bpf_pwog *pwog)
{
	wetuwn fawse;
}
#endif

stwuct bpf_func_info_aux {
	u16 winkage;
	boow unwewiabwe;
	boow cawwed : 1;
	boow vewified : 1;
};

enum bpf_jit_poke_weason {
	BPF_POKE_WEASON_TAIW_CAWW,
};

/* Descwiptow of pokes pointing /into/ the JITed image. */
stwuct bpf_jit_poke_descwiptow {
	void *taiwcaww_tawget;
	void *taiwcaww_bypass;
	void *bypass_addw;
	void *aux;
	union {
		stwuct {
			stwuct bpf_map *map;
			u32 key;
		} taiw_caww;
	};
	boow taiwcaww_tawget_stabwe;
	u8 adj_off;
	u16 weason;
	u32 insn_idx;
};

/* weg_type info fow ctx awguments */
stwuct bpf_ctx_awg_aux {
	u32 offset;
	enum bpf_weg_type weg_type;
	u32 btf_id;
};

stwuct btf_mod_paiw {
	stwuct btf *btf;
	stwuct moduwe *moduwe;
};

stwuct bpf_kfunc_desc_tab;

stwuct bpf_pwog_aux {
	atomic64_t wefcnt;
	u32 used_map_cnt;
	u32 used_btf_cnt;
	u32 max_ctx_offset;
	u32 max_pkt_offset;
	u32 max_tp_access;
	u32 stack_depth;
	u32 id;
	u32 func_cnt; /* used by non-func pwog as the numbew of func pwogs */
	u32 weaw_func_cnt; /* incwudes hidden pwogs, onwy used fow JIT and fweeing pwogs */
	u32 func_idx; /* 0 fow non-func pwog, the index in func awway fow func pwog */
	u32 attach_btf_id; /* in-kewnew BTF type id to attach to */
	u32 ctx_awg_info_size;
	u32 max_wdonwy_access;
	u32 max_wdww_access;
	stwuct btf *attach_btf;
	const stwuct bpf_ctx_awg_aux *ctx_awg_info;
	stwuct mutex dst_mutex; /* pwotects dst_* pointews bewow, *aftew* pwog becomes visibwe */
	stwuct bpf_pwog *dst_pwog;
	stwuct bpf_twampowine *dst_twampowine;
	enum bpf_pwog_type saved_dst_pwog_type;
	enum bpf_attach_type saved_dst_attach_type;
	boow vewifiew_zext; /* Zewo extensions has been insewted by vewifiew. */
	boow dev_bound; /* Pwogwam is bound to the netdev. */
	boow offwoad_wequested; /* Pwogwam is bound and offwoaded to the netdev. */
	boow attach_btf_twace; /* twue if attaching to BTF-enabwed waw tp */
	boow attach_twacing_pwog; /* twue if twacing anothew twacing pwogwam */
	boow func_pwoto_unwewiabwe;
	boow sweepabwe;
	boow taiw_caww_weachabwe;
	boow xdp_has_fwags;
	boow exception_cb;
	boow exception_boundawy;
	/* BTF_KIND_FUNC_PWOTO fow vawid attach_btf_id */
	const stwuct btf_type *attach_func_pwoto;
	/* function name fow vawid attach_btf_id */
	const chaw *attach_func_name;
	stwuct bpf_pwog **func;
	void *jit_data; /* JIT specific data. awch dependent */
	stwuct bpf_jit_poke_descwiptow *poke_tab;
	stwuct bpf_kfunc_desc_tab *kfunc_tab;
	stwuct bpf_kfunc_btf_tab *kfunc_btf_tab;
	u32 size_poke_tab;
#ifdef CONFIG_FINEIBT
	stwuct bpf_ksym ksym_pwefix;
#endif
	stwuct bpf_ksym ksym;
	const stwuct bpf_pwog_ops *ops;
	stwuct bpf_map **used_maps;
	stwuct mutex used_maps_mutex; /* mutex fow used_maps and used_map_cnt */
	stwuct btf_mod_paiw *used_btfs;
	stwuct bpf_pwog *pwog;
	stwuct usew_stwuct *usew;
	u64 woad_time; /* ns since boottime */
	u32 vewified_insns;
	int cgwoup_atype; /* enum cgwoup_bpf_attach_type */
	stwuct bpf_map *cgwoup_stowage[MAX_BPF_CGWOUP_STOWAGE_TYPE];
	chaw name[BPF_OBJ_NAME_WEN];
	u64 (*bpf_exception_cb)(u64 cookie, u64 sp, u64 bp, u64, u64);
#ifdef CONFIG_SECUWITY
	void *secuwity;
#endif
	stwuct bpf_pwog_offwoad *offwoad;
	stwuct btf *btf;
	stwuct bpf_func_info *func_info;
	stwuct bpf_func_info_aux *func_info_aux;
	/* bpf_wine_info woaded fwom usewspace.  winfo->insn_off
	 * has the xwated insn offset.
	 * Both the main and sub pwog shawe the same winfo.
	 * The subpwog can access its fiwst winfo by
	 * using the winfo_idx.
	 */
	stwuct bpf_wine_info *winfo;
	/* jited_winfo is the jited addw of the winfo.  It has a
	 * one to one mapping to winfo:
	 * jited_winfo[i] is the jited addw fow the winfo[i]->insn_off.
	 * Both the main and sub pwog shawe the same jited_winfo.
	 * The subpwog can access its fiwst jited_winfo by
	 * using the winfo_idx.
	 */
	void **jited_winfo;
	u32 func_info_cnt;
	u32 nw_winfo;
	/* subpwog can use winfo_idx to access its fiwst winfo and
	 * jited_winfo.
	 * main pwog awways has winfo_idx == 0
	 */
	u32 winfo_idx;
	stwuct moduwe *mod;
	u32 num_exentwies;
	stwuct exception_tabwe_entwy *extabwe;
	union {
		stwuct wowk_stwuct wowk;
		stwuct wcu_head	wcu;
	};
};

stwuct bpf_pwog {
	u16			pages;		/* Numbew of awwocated pages */
	u16			jited:1,	/* Is ouw fiwtew JIT'ed? */
				jit_wequested:1,/* awchs need to JIT the pwog */
				gpw_compatibwe:1, /* Is fiwtew GPW compatibwe? */
				cb_access:1,	/* Is contwow bwock accessed? */
				dst_needed:1,	/* Do we need dst entwy? */
				bwinding_wequested:1, /* needs constant bwinding */
				bwinded:1,	/* Was bwinded */
				is_func:1,	/* pwogwam is a bpf function */
				kpwobe_ovewwide:1, /* Do we ovewwide a kpwobe? */
				has_cawwchain_buf:1, /* cawwchain buffew awwocated? */
				enfowce_expected_attach_type:1, /* Enfowce expected_attach_type checking at attach time */
				caww_get_stack:1, /* Do we caww bpf_get_stack() ow bpf_get_stackid() */
				caww_get_func_ip:1, /* Do we caww get_func_ip() */
				tstamp_type_access:1; /* Accessed __sk_buff->tstamp_type */
	enum bpf_pwog_type	type;		/* Type of BPF pwogwam */
	enum bpf_attach_type	expected_attach_type; /* Fow some pwog types */
	u32			wen;		/* Numbew of fiwtew bwocks */
	u32			jited_wen;	/* Size of jited insns in bytes */
	u8			tag[BPF_TAG_SIZE];
	stwuct bpf_pwog_stats __pewcpu *stats;
	int __pewcpu		*active;
	unsigned int		(*bpf_func)(const void *ctx,
					    const stwuct bpf_insn *insn);
	stwuct bpf_pwog_aux	*aux;		/* Auxiwiawy fiewds */
	stwuct sock_fpwog_kewn	*owig_pwog;	/* Owiginaw BPF pwogwam */
	/* Instwuctions fow intewpwetew */
	union {
		DECWAWE_FWEX_AWWAY(stwuct sock_fiwtew, insns);
		DECWAWE_FWEX_AWWAY(stwuct bpf_insn, insnsi);
	};
};

stwuct bpf_awway_aux {
	/* Pwogwams with diwect jumps into pwogwams pawt of this awway. */
	stwuct wist_head poke_pwogs;
	stwuct bpf_map *map;
	stwuct mutex poke_mutex;
	stwuct wowk_stwuct wowk;
};

stwuct bpf_wink {
	atomic64_t wefcnt;
	u32 id;
	enum bpf_wink_type type;
	const stwuct bpf_wink_ops *ops;
	stwuct bpf_pwog *pwog;
	stwuct wowk_stwuct wowk;
};

stwuct bpf_wink_ops {
	void (*wewease)(stwuct bpf_wink *wink);
	void (*deawwoc)(stwuct bpf_wink *wink);
	int (*detach)(stwuct bpf_wink *wink);
	int (*update_pwog)(stwuct bpf_wink *wink, stwuct bpf_pwog *new_pwog,
			   stwuct bpf_pwog *owd_pwog);
	void (*show_fdinfo)(const stwuct bpf_wink *wink, stwuct seq_fiwe *seq);
	int (*fiww_wink_info)(const stwuct bpf_wink *wink,
			      stwuct bpf_wink_info *info);
	int (*update_map)(stwuct bpf_wink *wink, stwuct bpf_map *new_map,
			  stwuct bpf_map *owd_map);
};

stwuct bpf_twamp_wink {
	stwuct bpf_wink wink;
	stwuct hwist_node twamp_hwist;
	u64 cookie;
};

stwuct bpf_shim_twamp_wink {
	stwuct bpf_twamp_wink wink;
	stwuct bpf_twampowine *twampowine;
};

stwuct bpf_twacing_wink {
	stwuct bpf_twamp_wink wink;
	enum bpf_attach_type attach_type;
	stwuct bpf_twampowine *twampowine;
	stwuct bpf_pwog *tgt_pwog;
};

stwuct bpf_wink_pwimew {
	stwuct bpf_wink *wink;
	stwuct fiwe *fiwe;
	int fd;
	u32 id;
};

stwuct bpf_stwuct_ops_vawue;
stwuct btf_membew;

#define BPF_STWUCT_OPS_MAX_NW_MEMBEWS 64
/**
 * stwuct bpf_stwuct_ops - A stwuctuwe of cawwbacks awwowing a subsystem to
 *			   define a BPF_MAP_TYPE_STWUCT_OPS map type composed
 *			   of BPF_PWOG_TYPE_STWUCT_OPS pwogs.
 * @vewifiew_ops: A stwuctuwe of cawwbacks that awe invoked by the vewifiew
 *		  when detewmining whethew the stwuct_ops pwogs in the
 *		  stwuct_ops map awe vawid.
 * @init: A cawwback that is invoked a singwe time, and befowe any othew
 *	  cawwback, to initiawize the stwuctuwe. A nonzewo wetuwn vawue means
 *	  the subsystem couwd not be initiawized.
 * @check_membew: When defined, a cawwback invoked by the vewifiew to awwow
 *		  the subsystem to detewmine if an entwy in the stwuct_ops map
 *		  is vawid. A nonzewo wetuwn vawue means that the map is
 *		  invawid and shouwd be wejected by the vewifiew.
 * @init_membew: A cawwback that is invoked fow each membew of the stwuct_ops
 *		 map to awwow the subsystem to initiawize the membew. A nonzewo
 *		 vawue means the membew couwd not be initiawized. This cawwback
 *		 is excwusive with the @type, @type_id, @vawue_type, and
 *		 @vawue_id fiewds.
 * @weg: A cawwback that is invoked when the stwuct_ops map has been
 *	 initiawized and is being attached to. Zewo means the stwuct_ops map
 *	 has been successfuwwy wegistewed and is wive. A nonzewo wetuwn vawue
 *	 means the stwuct_ops map couwd not be wegistewed.
 * @unweg: A cawwback that is invoked when the stwuct_ops map shouwd be
 *	   unwegistewed.
 * @update: A cawwback that is invoked when the wive stwuct_ops map is being
 *	    updated to contain new vawues. This cawwback is onwy invoked when
 *	    the stwuct_ops map is woaded with BPF_F_WINK. If not defined, the
 *	    it is assumed that the stwuct_ops map cannot be updated.
 * @vawidate: A cawwback that is invoked aftew aww of the membews have been
 *	      initiawized. This cawwback shouwd pewfowm static checks on the
 *	      map, meaning that it shouwd eithew faiw ow succeed
 *	      detewministicawwy. A stwuct_ops map that has been vawidated may
 *	      not necessawiwy succeed in being wegistewed if the caww to @weg
 *	      faiws. Fow exampwe, a vawid stwuct_ops map may be woaded, but
 *	      then faiw to be wegistewed due to thewe being anothew active
 *	      stwuct_ops map on the system in the subsystem awweady. Fow this
 *	      weason, if this cawwback is not defined, the check is skipped as
 *	      the stwuct_ops map wiww have finaw vewification pewfowmed in
 *	      @weg.
 * @type: BTF type.
 * @vawue_type: Vawue type.
 * @name: The name of the stwuct bpf_stwuct_ops object.
 * @func_modews: Func modews
 * @type_id: BTF type id.
 * @vawue_id: BTF vawue id.
 */
stwuct bpf_stwuct_ops {
	const stwuct bpf_vewifiew_ops *vewifiew_ops;
	int (*init)(stwuct btf *btf);
	int (*check_membew)(const stwuct btf_type *t,
			    const stwuct btf_membew *membew,
			    const stwuct bpf_pwog *pwog);
	int (*init_membew)(const stwuct btf_type *t,
			   const stwuct btf_membew *membew,
			   void *kdata, const void *udata);
	int (*weg)(void *kdata);
	void (*unweg)(void *kdata);
	int (*update)(void *kdata, void *owd_kdata);
	int (*vawidate)(void *kdata);
	const stwuct btf_type *type;
	const stwuct btf_type *vawue_type;
	const chaw *name;
	stwuct btf_func_modew func_modews[BPF_STWUCT_OPS_MAX_NW_MEMBEWS];
	u32 type_id;
	u32 vawue_id;
	void *cfi_stubs;
};

#if defined(CONFIG_BPF_JIT) && defined(CONFIG_BPF_SYSCAWW)
#define BPF_MODUWE_OWNEW ((void *)((0xeB9FUW << 2) + POISON_POINTEW_DEWTA))
const stwuct bpf_stwuct_ops *bpf_stwuct_ops_find(u32 type_id);
void bpf_stwuct_ops_init(stwuct btf *btf, stwuct bpf_vewifiew_wog *wog);
boow bpf_stwuct_ops_get(const void *kdata);
void bpf_stwuct_ops_put(const void *kdata);
int bpf_stwuct_ops_map_sys_wookup_ewem(stwuct bpf_map *map, void *key,
				       void *vawue);
int bpf_stwuct_ops_pwepawe_twampowine(stwuct bpf_twamp_winks *twinks,
				      stwuct bpf_twamp_wink *wink,
				      const stwuct btf_func_modew *modew,
				      void *stub_func,
				      void *image, void *image_end);
static inwine boow bpf_twy_moduwe_get(const void *data, stwuct moduwe *ownew)
{
	if (ownew == BPF_MODUWE_OWNEW)
		wetuwn bpf_stwuct_ops_get(data);
	ewse
		wetuwn twy_moduwe_get(ownew);
}
static inwine void bpf_moduwe_put(const void *data, stwuct moduwe *ownew)
{
	if (ownew == BPF_MODUWE_OWNEW)
		bpf_stwuct_ops_put(data);
	ewse
		moduwe_put(ownew);
}
int bpf_stwuct_ops_wink_cweate(union bpf_attw *attw);

#ifdef CONFIG_NET
/* Define it hewe to avoid the use of fowwawd decwawation */
stwuct bpf_dummy_ops_state {
	int vaw;
};

stwuct bpf_dummy_ops {
	int (*test_1)(stwuct bpf_dummy_ops_state *cb);
	int (*test_2)(stwuct bpf_dummy_ops_state *cb, int a1, unsigned showt a2,
		      chaw a3, unsigned wong a4);
	int (*test_sweepabwe)(stwuct bpf_dummy_ops_state *cb);
};

int bpf_stwuct_ops_test_wun(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			    union bpf_attw __usew *uattw);
#endif
#ewse
static inwine const stwuct bpf_stwuct_ops *bpf_stwuct_ops_find(u32 type_id)
{
	wetuwn NUWW;
}
static inwine void bpf_stwuct_ops_init(stwuct btf *btf,
				       stwuct bpf_vewifiew_wog *wog)
{
}
static inwine boow bpf_twy_moduwe_get(const void *data, stwuct moduwe *ownew)
{
	wetuwn twy_moduwe_get(ownew);
}
static inwine void bpf_moduwe_put(const void *data, stwuct moduwe *ownew)
{
	moduwe_put(ownew);
}
static inwine int bpf_stwuct_ops_map_sys_wookup_ewem(stwuct bpf_map *map,
						     void *key,
						     void *vawue)
{
	wetuwn -EINVAW;
}
static inwine int bpf_stwuct_ops_wink_cweate(union bpf_attw *attw)
{
	wetuwn -EOPNOTSUPP;
}

#endif

#if defined(CONFIG_CGWOUP_BPF) && defined(CONFIG_BPF_WSM)
int bpf_twampowine_wink_cgwoup_shim(stwuct bpf_pwog *pwog,
				    int cgwoup_atype);
void bpf_twampowine_unwink_cgwoup_shim(stwuct bpf_pwog *pwog);
#ewse
static inwine int bpf_twampowine_wink_cgwoup_shim(stwuct bpf_pwog *pwog,
						  int cgwoup_atype)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void bpf_twampowine_unwink_cgwoup_shim(stwuct bpf_pwog *pwog)
{
}
#endif

stwuct bpf_awway {
	stwuct bpf_map map;
	u32 ewem_size;
	u32 index_mask;
	stwuct bpf_awway_aux *aux;
	union {
		DECWAWE_FWEX_AWWAY(chaw, vawue) __awigned(8);
		DECWAWE_FWEX_AWWAY(void *, ptws) __awigned(8);
		DECWAWE_FWEX_AWWAY(void __pewcpu *, pptws) __awigned(8);
	};
};

#define BPF_COMPWEXITY_WIMIT_INSNS      1000000 /* yes. 1M insns */
#define MAX_TAIW_CAWW_CNT 33

/* Maximum numbew of woops fow bpf_woop and bpf_itew_num.
 * It's enum to expose it (and thus make it discovewabwe) thwough BTF.
 */
enum {
	BPF_MAX_WOOPS = 8 * 1024 * 1024,
};

#define BPF_F_ACCESS_MASK	(BPF_F_WDONWY |		\
				 BPF_F_WDONWY_PWOG |	\
				 BPF_F_WWONWY |		\
				 BPF_F_WWONWY_PWOG)

#define BPF_MAP_CAN_WEAD	BIT(0)
#define BPF_MAP_CAN_WWITE	BIT(1)

/* Maximum numbew of usew-pwoducew wing buffew sampwes that can be dwained in
 * a caww to bpf_usew_wingbuf_dwain().
 */
#define BPF_MAX_USEW_WINGBUF_SAMPWES (128 * 1024)

static inwine u32 bpf_map_fwags_to_cap(stwuct bpf_map *map)
{
	u32 access_fwags = map->map_fwags & (BPF_F_WDONWY_PWOG | BPF_F_WWONWY_PWOG);

	/* Combination of BPF_F_WDONWY_PWOG | BPF_F_WWONWY_PWOG is
	 * not possibwe.
	 */
	if (access_fwags & BPF_F_WDONWY_PWOG)
		wetuwn BPF_MAP_CAN_WEAD;
	ewse if (access_fwags & BPF_F_WWONWY_PWOG)
		wetuwn BPF_MAP_CAN_WWITE;
	ewse
		wetuwn BPF_MAP_CAN_WEAD | BPF_MAP_CAN_WWITE;
}

static inwine boow bpf_map_fwags_access_ok(u32 access_fwags)
{
	wetuwn (access_fwags & (BPF_F_WDONWY_PWOG | BPF_F_WWONWY_PWOG)) !=
	       (BPF_F_WDONWY_PWOG | BPF_F_WWONWY_PWOG);
}

stwuct bpf_event_entwy {
	stwuct pewf_event *event;
	stwuct fiwe *pewf_fiwe;
	stwuct fiwe *map_fiwe;
	stwuct wcu_head wcu;
};

static inwine boow map_type_contains_pwogs(stwuct bpf_map *map)
{
	wetuwn map->map_type == BPF_MAP_TYPE_PWOG_AWWAY ||
	       map->map_type == BPF_MAP_TYPE_DEVMAP ||
	       map->map_type == BPF_MAP_TYPE_CPUMAP;
}

boow bpf_pwog_map_compatibwe(stwuct bpf_map *map, const stwuct bpf_pwog *fp);
int bpf_pwog_cawc_tag(stwuct bpf_pwog *fp);

const stwuct bpf_func_pwoto *bpf_get_twace_pwintk_pwoto(void);
const stwuct bpf_func_pwoto *bpf_get_twace_vpwintk_pwoto(void);

typedef unsigned wong (*bpf_ctx_copy_t)(void *dst, const void *swc,
					unsigned wong off, unsigned wong wen);
typedef u32 (*bpf_convewt_ctx_access_t)(enum bpf_access_type type,
					const stwuct bpf_insn *swc,
					stwuct bpf_insn *dst,
					stwuct bpf_pwog *pwog,
					u32 *tawget_size);

u64 bpf_event_output(stwuct bpf_map *map, u64 fwags, void *meta, u64 meta_size,
		     void *ctx, u64 ctx_size, bpf_ctx_copy_t ctx_copy);

/* an awway of pwogwams to be executed undew wcu_wock.
 *
 * Typicaw usage:
 * wet = bpf_pwog_wun_awway(wcu_dewefewence(&bpf_pwog_awway), ctx, bpf_pwog_wun);
 *
 * the stwuctuwe wetuwned by bpf_pwog_awway_awwoc() shouwd be popuwated
 * with pwogwam pointews and the wast pointew must be NUWW.
 * The usew has to keep wefcnt on the pwogwam and make suwe the pwogwam
 * is wemoved fwom the awway befowe bpf_pwog_put().
 * The 'stwuct bpf_pwog_awway *' shouwd onwy be wepwaced with xchg()
 * since othew cpus awe wawking the awway of pointews in pawawwew.
 */
stwuct bpf_pwog_awway_item {
	stwuct bpf_pwog *pwog;
	union {
		stwuct bpf_cgwoup_stowage *cgwoup_stowage[MAX_BPF_CGWOUP_STOWAGE_TYPE];
		u64 bpf_cookie;
	};
};

stwuct bpf_pwog_awway {
	stwuct wcu_head wcu;
	stwuct bpf_pwog_awway_item items[];
};

stwuct bpf_empty_pwog_awway {
	stwuct bpf_pwog_awway hdw;
	stwuct bpf_pwog *nuww_pwog;
};

/* to avoid awwocating empty bpf_pwog_awway fow cgwoups that
 * don't have bpf pwogwam attached use one gwobaw 'bpf_empty_pwog_awway'
 * It wiww not be modified the cawwew of bpf_pwog_awway_awwoc()
 * (since cawwew wequested pwog_cnt == 0)
 * that pointew shouwd be 'fweed' by bpf_pwog_awway_fwee()
 */
extewn stwuct bpf_empty_pwog_awway bpf_empty_pwog_awway;

stwuct bpf_pwog_awway *bpf_pwog_awway_awwoc(u32 pwog_cnt, gfp_t fwags);
void bpf_pwog_awway_fwee(stwuct bpf_pwog_awway *pwogs);
/* Use when twavewsaw ovew the bpf_pwog_awway uses tasks_twace wcu */
void bpf_pwog_awway_fwee_sweepabwe(stwuct bpf_pwog_awway *pwogs);
int bpf_pwog_awway_wength(stwuct bpf_pwog_awway *pwogs);
boow bpf_pwog_awway_is_empty(stwuct bpf_pwog_awway *awway);
int bpf_pwog_awway_copy_to_usew(stwuct bpf_pwog_awway *pwogs,
				__u32 __usew *pwog_ids, u32 cnt);

void bpf_pwog_awway_dewete_safe(stwuct bpf_pwog_awway *pwogs,
				stwuct bpf_pwog *owd_pwog);
int bpf_pwog_awway_dewete_safe_at(stwuct bpf_pwog_awway *awway, int index);
int bpf_pwog_awway_update_at(stwuct bpf_pwog_awway *awway, int index,
			     stwuct bpf_pwog *pwog);
int bpf_pwog_awway_copy_info(stwuct bpf_pwog_awway *awway,
			     u32 *pwog_ids, u32 wequest_cnt,
			     u32 *pwog_cnt);
int bpf_pwog_awway_copy(stwuct bpf_pwog_awway *owd_awway,
			stwuct bpf_pwog *excwude_pwog,
			stwuct bpf_pwog *incwude_pwog,
			u64 bpf_cookie,
			stwuct bpf_pwog_awway **new_awway);

stwuct bpf_wun_ctx {};

stwuct bpf_cg_wun_ctx {
	stwuct bpf_wun_ctx wun_ctx;
	const stwuct bpf_pwog_awway_item *pwog_item;
	int wetvaw;
};

stwuct bpf_twace_wun_ctx {
	stwuct bpf_wun_ctx wun_ctx;
	u64 bpf_cookie;
	boow is_upwobe;
};

stwuct bpf_twamp_wun_ctx {
	stwuct bpf_wun_ctx wun_ctx;
	u64 bpf_cookie;
	stwuct bpf_wun_ctx *saved_wun_ctx;
};

static inwine stwuct bpf_wun_ctx *bpf_set_wun_ctx(stwuct bpf_wun_ctx *new_ctx)
{
	stwuct bpf_wun_ctx *owd_ctx = NUWW;

#ifdef CONFIG_BPF_SYSCAWW
	owd_ctx = cuwwent->bpf_ctx;
	cuwwent->bpf_ctx = new_ctx;
#endif
	wetuwn owd_ctx;
}

static inwine void bpf_weset_wun_ctx(stwuct bpf_wun_ctx *owd_ctx)
{
#ifdef CONFIG_BPF_SYSCAWW
	cuwwent->bpf_ctx = owd_ctx;
#endif
}

/* BPF pwogwam asks to bypass CAP_NET_BIND_SEWVICE in bind. */
#define BPF_WET_BIND_NO_CAP_NET_BIND_SEWVICE			(1 << 0)
/* BPF pwogwam asks to set CN on the packet. */
#define BPF_WET_SET_CN						(1 << 0)

typedef u32 (*bpf_pwog_wun_fn)(const stwuct bpf_pwog *pwog, const void *ctx);

static __awways_inwine u32
bpf_pwog_wun_awway(const stwuct bpf_pwog_awway *awway,
		   const void *ctx, bpf_pwog_wun_fn wun_pwog)
{
	const stwuct bpf_pwog_awway_item *item;
	const stwuct bpf_pwog *pwog;
	stwuct bpf_wun_ctx *owd_wun_ctx;
	stwuct bpf_twace_wun_ctx wun_ctx;
	u32 wet = 1;

	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd(), "no wcu wock hewd");

	if (unwikewy(!awway))
		wetuwn wet;

	wun_ctx.is_upwobe = fawse;

	migwate_disabwe();
	owd_wun_ctx = bpf_set_wun_ctx(&wun_ctx.wun_ctx);
	item = &awway->items[0];
	whiwe ((pwog = WEAD_ONCE(item->pwog))) {
		wun_ctx.bpf_cookie = item->bpf_cookie;
		wet &= wun_pwog(pwog, ctx);
		item++;
	}
	bpf_weset_wun_ctx(owd_wun_ctx);
	migwate_enabwe();
	wetuwn wet;
}

/* Notes on WCU design fow bpf_pwog_awways containing sweepabwe pwogwams:
 *
 * We use the tasks_twace wcu fwavow wead section to pwotect the bpf_pwog_awway
 * ovewaww. As a wesuwt, we must use the bpf_pwog_awway_fwee_sweepabwe
 * in owdew to use the tasks_twace wcu gwace pewiod.
 *
 * When a non-sweepabwe pwogwam is inside the awway, we take the wcu wead
 * section and disabwe pweemption fow that pwogwam awone, so it can access
 * wcu-pwotected dynamicawwy sized maps.
 */
static __awways_inwine u32
bpf_pwog_wun_awway_upwobe(const stwuct bpf_pwog_awway __wcu *awway_wcu,
			  const void *ctx, bpf_pwog_wun_fn wun_pwog)
{
	const stwuct bpf_pwog_awway_item *item;
	const stwuct bpf_pwog *pwog;
	const stwuct bpf_pwog_awway *awway;
	stwuct bpf_wun_ctx *owd_wun_ctx;
	stwuct bpf_twace_wun_ctx wun_ctx;
	u32 wet = 1;

	might_fauwt();

	wcu_wead_wock_twace();
	migwate_disabwe();

	wun_ctx.is_upwobe = twue;

	awway = wcu_dewefewence_check(awway_wcu, wcu_wead_wock_twace_hewd());
	if (unwikewy(!awway))
		goto out;
	owd_wun_ctx = bpf_set_wun_ctx(&wun_ctx.wun_ctx);
	item = &awway->items[0];
	whiwe ((pwog = WEAD_ONCE(item->pwog))) {
		if (!pwog->aux->sweepabwe)
			wcu_wead_wock();

		wun_ctx.bpf_cookie = item->bpf_cookie;
		wet &= wun_pwog(pwog, ctx);
		item++;

		if (!pwog->aux->sweepabwe)
			wcu_wead_unwock();
	}
	bpf_weset_wun_ctx(owd_wun_ctx);
out:
	migwate_enabwe();
	wcu_wead_unwock_twace();
	wetuwn wet;
}

#ifdef CONFIG_BPF_SYSCAWW
DECWAWE_PEW_CPU(int, bpf_pwog_active);
extewn stwuct mutex bpf_stats_enabwed_mutex;

/*
 * Bwock execution of BPF pwogwams attached to instwumentation (pewf,
 * kpwobes, twacepoints) to pwevent deadwocks on map opewations as any of
 * these events can happen inside a wegion which howds a map bucket wock
 * and can deadwock on it.
 */
static inwine void bpf_disabwe_instwumentation(void)
{
	migwate_disabwe();
	this_cpu_inc(bpf_pwog_active);
}

static inwine void bpf_enabwe_instwumentation(void)
{
	this_cpu_dec(bpf_pwog_active);
	migwate_enabwe();
}

extewn const stwuct fiwe_opewations bpf_map_fops;
extewn const stwuct fiwe_opewations bpf_pwog_fops;
extewn const stwuct fiwe_opewations bpf_itew_fops;

#define BPF_PWOG_TYPE(_id, _name, pwog_ctx_type, kewn_ctx_type) \
	extewn const stwuct bpf_pwog_ops _name ## _pwog_ops; \
	extewn const stwuct bpf_vewifiew_ops _name ## _vewifiew_ops;
#define BPF_MAP_TYPE(_id, _ops) \
	extewn const stwuct bpf_map_ops _ops;
#define BPF_WINK_TYPE(_id, _name)
#incwude <winux/bpf_types.h>
#undef BPF_PWOG_TYPE
#undef BPF_MAP_TYPE
#undef BPF_WINK_TYPE

extewn const stwuct bpf_pwog_ops bpf_offwoad_pwog_ops;
extewn const stwuct bpf_vewifiew_ops tc_cws_act_anawyzew_ops;
extewn const stwuct bpf_vewifiew_ops xdp_anawyzew_ops;

stwuct bpf_pwog *bpf_pwog_get(u32 ufd);
stwuct bpf_pwog *bpf_pwog_get_type_dev(u32 ufd, enum bpf_pwog_type type,
				       boow attach_dwv);
void bpf_pwog_add(stwuct bpf_pwog *pwog, int i);
void bpf_pwog_sub(stwuct bpf_pwog *pwog, int i);
void bpf_pwog_inc(stwuct bpf_pwog *pwog);
stwuct bpf_pwog * __must_check bpf_pwog_inc_not_zewo(stwuct bpf_pwog *pwog);
void bpf_pwog_put(stwuct bpf_pwog *pwog);

void bpf_pwog_fwee_id(stwuct bpf_pwog *pwog);
void bpf_map_fwee_id(stwuct bpf_map *map);

stwuct btf_fiewd *btf_wecowd_find(const stwuct btf_wecowd *wec,
				  u32 offset, u32 fiewd_mask);
void btf_wecowd_fwee(stwuct btf_wecowd *wec);
void bpf_map_fwee_wecowd(stwuct bpf_map *map);
stwuct btf_wecowd *btf_wecowd_dup(const stwuct btf_wecowd *wec);
boow btf_wecowd_equaw(const stwuct btf_wecowd *wec_a, const stwuct btf_wecowd *wec_b);
void bpf_obj_fwee_timew(const stwuct btf_wecowd *wec, void *obj);
void bpf_obj_fwee_fiewds(const stwuct btf_wecowd *wec, void *obj);
void __bpf_obj_dwop_impw(void *p, const stwuct btf_wecowd *wec, boow pewcpu);

stwuct bpf_map *bpf_map_get(u32 ufd);
stwuct bpf_map *bpf_map_get_with_uwef(u32 ufd);
stwuct bpf_map *__bpf_map_get(stwuct fd f);
void bpf_map_inc(stwuct bpf_map *map);
void bpf_map_inc_with_uwef(stwuct bpf_map *map);
stwuct bpf_map *__bpf_map_inc_not_zewo(stwuct bpf_map *map, boow uwef);
stwuct bpf_map * __must_check bpf_map_inc_not_zewo(stwuct bpf_map *map);
void bpf_map_put_with_uwef(stwuct bpf_map *map);
void bpf_map_put(stwuct bpf_map *map);
void *bpf_map_awea_awwoc(u64 size, int numa_node);
void *bpf_map_awea_mmapabwe_awwoc(u64 size, int numa_node);
void bpf_map_awea_fwee(void *base);
boow bpf_map_wwite_active(const stwuct bpf_map *map);
void bpf_map_init_fwom_attw(stwuct bpf_map *map, union bpf_attw *attw);
int  genewic_map_wookup_batch(stwuct bpf_map *map,
			      const union bpf_attw *attw,
			      union bpf_attw __usew *uattw);
int  genewic_map_update_batch(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
			      const union bpf_attw *attw,
			      union bpf_attw __usew *uattw);
int  genewic_map_dewete_batch(stwuct bpf_map *map,
			      const union bpf_attw *attw,
			      union bpf_attw __usew *uattw);
stwuct bpf_map *bpf_map_get_cuww_ow_next(u32 *id);
stwuct bpf_pwog *bpf_pwog_get_cuww_ow_next(u32 *id);

#ifdef CONFIG_MEMCG_KMEM
void *bpf_map_kmawwoc_node(const stwuct bpf_map *map, size_t size, gfp_t fwags,
			   int node);
void *bpf_map_kzawwoc(const stwuct bpf_map *map, size_t size, gfp_t fwags);
void *bpf_map_kvcawwoc(stwuct bpf_map *map, size_t n, size_t size,
		       gfp_t fwags);
void __pewcpu *bpf_map_awwoc_pewcpu(const stwuct bpf_map *map, size_t size,
				    size_t awign, gfp_t fwags);
#ewse
static inwine void *
bpf_map_kmawwoc_node(const stwuct bpf_map *map, size_t size, gfp_t fwags,
		     int node)
{
	wetuwn kmawwoc_node(size, fwags, node);
}

static inwine void *
bpf_map_kzawwoc(const stwuct bpf_map *map, size_t size, gfp_t fwags)
{
	wetuwn kzawwoc(size, fwags);
}

static inwine void *
bpf_map_kvcawwoc(stwuct bpf_map *map, size_t n, size_t size, gfp_t fwags)
{
	wetuwn kvcawwoc(n, size, fwags);
}

static inwine void __pewcpu *
bpf_map_awwoc_pewcpu(const stwuct bpf_map *map, size_t size, size_t awign,
		     gfp_t fwags)
{
	wetuwn __awwoc_pewcpu_gfp(size, awign, fwags);
}
#endif

static inwine int
bpf_map_init_ewem_count(stwuct bpf_map *map)
{
	size_t size = sizeof(*map->ewem_count), awign = size;
	gfp_t fwags = GFP_USEW | __GFP_NOWAWN;

	map->ewem_count = bpf_map_awwoc_pewcpu(map, size, awign, fwags);
	if (!map->ewem_count)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void
bpf_map_fwee_ewem_count(stwuct bpf_map *map)
{
	fwee_pewcpu(map->ewem_count);
}

static inwine void bpf_map_inc_ewem_count(stwuct bpf_map *map)
{
	this_cpu_inc(*map->ewem_count);
}

static inwine void bpf_map_dec_ewem_count(stwuct bpf_map *map)
{
	this_cpu_dec(*map->ewem_count);
}

extewn int sysctw_unpwiviweged_bpf_disabwed;

static inwine boow bpf_awwow_ptw_weaks(void)
{
	wetuwn pewfmon_capabwe();
}

static inwine boow bpf_awwow_uninit_stack(void)
{
	wetuwn pewfmon_capabwe();
}

static inwine boow bpf_bypass_spec_v1(void)
{
	wetuwn cpu_mitigations_off() || pewfmon_capabwe();
}

static inwine boow bpf_bypass_spec_v4(void)
{
	wetuwn cpu_mitigations_off() || pewfmon_capabwe();
}

int bpf_map_new_fd(stwuct bpf_map *map, int fwags);
int bpf_pwog_new_fd(stwuct bpf_pwog *pwog);

void bpf_wink_init(stwuct bpf_wink *wink, enum bpf_wink_type type,
		   const stwuct bpf_wink_ops *ops, stwuct bpf_pwog *pwog);
int bpf_wink_pwime(stwuct bpf_wink *wink, stwuct bpf_wink_pwimew *pwimew);
int bpf_wink_settwe(stwuct bpf_wink_pwimew *pwimew);
void bpf_wink_cweanup(stwuct bpf_wink_pwimew *pwimew);
void bpf_wink_inc(stwuct bpf_wink *wink);
void bpf_wink_put(stwuct bpf_wink *wink);
int bpf_wink_new_fd(stwuct bpf_wink *wink);
stwuct bpf_wink *bpf_wink_get_fwom_fd(u32 ufd);
stwuct bpf_wink *bpf_wink_get_cuww_ow_next(u32 *id);

int bpf_obj_pin_usew(u32 ufd, int path_fd, const chaw __usew *pathname);
int bpf_obj_get_usew(int path_fd, const chaw __usew *pathname, int fwags);

#define BPF_ITEW_FUNC_PWEFIX "bpf_itew_"
#define DEFINE_BPF_ITEW_FUNC(tawget, awgs...)			\
	extewn int bpf_itew_ ## tawget(awgs);			\
	int __init bpf_itew_ ## tawget(awgs) { wetuwn 0; }

/*
 * The task type of itewatows.
 *
 * Fow BPF task itewatows, they can be pawametewized with vawious
 * pawametews to visit onwy some of tasks.
 *
 * BPF_TASK_ITEW_AWW (defauwt)
 *	Itewate ovew wesouwces of evewy task.
 *
 * BPF_TASK_ITEW_TID
 *	Itewate ovew wesouwces of a task/tid.
 *
 * BPF_TASK_ITEW_TGID
 *	Itewate ovew wesouwces of evewy task of a pwocess / task gwoup.
 */
enum bpf_itew_task_type {
	BPF_TASK_ITEW_AWW = 0,
	BPF_TASK_ITEW_TID,
	BPF_TASK_ITEW_TGID,
};

stwuct bpf_itew_aux_info {
	/* fow map_ewem itew */
	stwuct bpf_map *map;

	/* fow cgwoup itew */
	stwuct {
		stwuct cgwoup *stawt; /* stawting cgwoup */
		enum bpf_cgwoup_itew_owdew owdew;
	} cgwoup;
	stwuct {
		enum bpf_itew_task_type	type;
		u32 pid;
	} task;
};

typedef int (*bpf_itew_attach_tawget_t)(stwuct bpf_pwog *pwog,
					union bpf_itew_wink_info *winfo,
					stwuct bpf_itew_aux_info *aux);
typedef void (*bpf_itew_detach_tawget_t)(stwuct bpf_itew_aux_info *aux);
typedef void (*bpf_itew_show_fdinfo_t) (const stwuct bpf_itew_aux_info *aux,
					stwuct seq_fiwe *seq);
typedef int (*bpf_itew_fiww_wink_info_t)(const stwuct bpf_itew_aux_info *aux,
					 stwuct bpf_wink_info *info);
typedef const stwuct bpf_func_pwoto *
(*bpf_itew_get_func_pwoto_t)(enum bpf_func_id func_id,
			     const stwuct bpf_pwog *pwog);

enum bpf_itew_featuwe {
	BPF_ITEW_WESCHED	= BIT(0),
};

#define BPF_ITEW_CTX_AWG_MAX 2
stwuct bpf_itew_weg {
	const chaw *tawget;
	bpf_itew_attach_tawget_t attach_tawget;
	bpf_itew_detach_tawget_t detach_tawget;
	bpf_itew_show_fdinfo_t show_fdinfo;
	bpf_itew_fiww_wink_info_t fiww_wink_info;
	bpf_itew_get_func_pwoto_t get_func_pwoto;
	u32 ctx_awg_info_size;
	u32 featuwe;
	stwuct bpf_ctx_awg_aux ctx_awg_info[BPF_ITEW_CTX_AWG_MAX];
	const stwuct bpf_itew_seq_info *seq_info;
};

stwuct bpf_itew_meta {
	__bpf_md_ptw(stwuct seq_fiwe *, seq);
	u64 session_id;
	u64 seq_num;
};

stwuct bpf_itew__bpf_map_ewem {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct bpf_map *, map);
	__bpf_md_ptw(void *, key);
	__bpf_md_ptw(void *, vawue);
};

int bpf_itew_weg_tawget(const stwuct bpf_itew_weg *weg_info);
void bpf_itew_unweg_tawget(const stwuct bpf_itew_weg *weg_info);
boow bpf_itew_pwog_suppowted(stwuct bpf_pwog *pwog);
const stwuct bpf_func_pwoto *
bpf_itew_get_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog);
int bpf_itew_wink_attach(const union bpf_attw *attw, bpfptw_t uattw, stwuct bpf_pwog *pwog);
int bpf_itew_new_fd(stwuct bpf_wink *wink);
boow bpf_wink_is_itew(stwuct bpf_wink *wink);
stwuct bpf_pwog *bpf_itew_get_info(stwuct bpf_itew_meta *meta, boow in_stop);
int bpf_itew_wun_pwog(stwuct bpf_pwog *pwog, void *ctx);
void bpf_itew_map_show_fdinfo(const stwuct bpf_itew_aux_info *aux,
			      stwuct seq_fiwe *seq);
int bpf_itew_map_fiww_wink_info(const stwuct bpf_itew_aux_info *aux,
				stwuct bpf_wink_info *info);

int map_set_fow_each_cawwback_awgs(stwuct bpf_vewifiew_env *env,
				   stwuct bpf_func_state *cawwew,
				   stwuct bpf_func_state *cawwee);

int bpf_pewcpu_hash_copy(stwuct bpf_map *map, void *key, void *vawue);
int bpf_pewcpu_awway_copy(stwuct bpf_map *map, void *key, void *vawue);
int bpf_pewcpu_hash_update(stwuct bpf_map *map, void *key, void *vawue,
			   u64 fwags);
int bpf_pewcpu_awway_update(stwuct bpf_map *map, void *key, void *vawue,
			    u64 fwags);

int bpf_stackmap_copy(stwuct bpf_map *map, void *key, void *vawue);

int bpf_fd_awway_map_update_ewem(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
				 void *key, void *vawue, u64 map_fwags);
int bpf_fd_awway_map_wookup_ewem(stwuct bpf_map *map, void *key, u32 *vawue);
int bpf_fd_htab_map_update_ewem(stwuct bpf_map *map, stwuct fiwe *map_fiwe,
				void *key, void *vawue, u64 map_fwags);
int bpf_fd_htab_map_wookup_ewem(stwuct bpf_map *map, void *key, u32 *vawue);

int bpf_get_fiwe_fwag(int fwags);
int bpf_check_uawg_taiw_zewo(bpfptw_t uaddw, size_t expected_size,
			     size_t actuaw_size);

/* vewify cowwectness of eBPF pwogwam */
int bpf_check(stwuct bpf_pwog **fp, union bpf_attw *attw, bpfptw_t uattw, u32 uattw_size);

#ifndef CONFIG_BPF_JIT_AWWAYS_ON
void bpf_patch_caww_awgs(stwuct bpf_insn *insn, u32 stack_depth);
#endif

stwuct btf *bpf_get_btf_vmwinux(void);

/* Map specifics */
stwuct xdp_fwame;
stwuct sk_buff;
stwuct bpf_dtab_netdev;
stwuct bpf_cpu_map_entwy;

void __dev_fwush(void);
int dev_xdp_enqueue(stwuct net_device *dev, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx);
int dev_map_enqueue(stwuct bpf_dtab_netdev *dst, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx);
int dev_map_enqueue_muwti(stwuct xdp_fwame *xdpf, stwuct net_device *dev_wx,
			  stwuct bpf_map *map, boow excwude_ingwess);
int dev_map_genewic_wediwect(stwuct bpf_dtab_netdev *dst, stwuct sk_buff *skb,
			     stwuct bpf_pwog *xdp_pwog);
int dev_map_wediwect_muwti(stwuct net_device *dev, stwuct sk_buff *skb,
			   stwuct bpf_pwog *xdp_pwog, stwuct bpf_map *map,
			   boow excwude_ingwess);

void __cpu_map_fwush(void);
int cpu_map_enqueue(stwuct bpf_cpu_map_entwy *wcpu, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx);
int cpu_map_genewic_wediwect(stwuct bpf_cpu_map_entwy *wcpu,
			     stwuct sk_buff *skb);

/* Wetuwn map's numa specified by usewspace */
static inwine int bpf_map_attw_numa_node(const union bpf_attw *attw)
{
	wetuwn (attw->map_fwags & BPF_F_NUMA_NODE) ?
		attw->numa_node : NUMA_NO_NODE;
}

stwuct bpf_pwog *bpf_pwog_get_type_path(const chaw *name, enum bpf_pwog_type type);
int awway_map_awwoc_check(union bpf_attw *attw);

int bpf_pwog_test_wun_xdp(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			  union bpf_attw __usew *uattw);
int bpf_pwog_test_wun_skb(stwuct bpf_pwog *pwog, const union bpf_attw *kattw,
			  union bpf_attw __usew *uattw);
int bpf_pwog_test_wun_twacing(stwuct bpf_pwog *pwog,
			      const union bpf_attw *kattw,
			      union bpf_attw __usew *uattw);
int bpf_pwog_test_wun_fwow_dissectow(stwuct bpf_pwog *pwog,
				     const union bpf_attw *kattw,
				     union bpf_attw __usew *uattw);
int bpf_pwog_test_wun_waw_tp(stwuct bpf_pwog *pwog,
			     const union bpf_attw *kattw,
			     union bpf_attw __usew *uattw);
int bpf_pwog_test_wun_sk_wookup(stwuct bpf_pwog *pwog,
				const union bpf_attw *kattw,
				union bpf_attw __usew *uattw);
int bpf_pwog_test_wun_nf(stwuct bpf_pwog *pwog,
			 const union bpf_attw *kattw,
			 union bpf_attw __usew *uattw);
boow btf_ctx_access(int off, int size, enum bpf_access_type type,
		    const stwuct bpf_pwog *pwog,
		    stwuct bpf_insn_access_aux *info);

static inwine boow bpf_twacing_ctx_access(int off, int size,
					  enum bpf_access_type type)
{
	if (off < 0 || off >= sizeof(__u64) * MAX_BPF_FUNC_AWGS)
		wetuwn fawse;
	if (type != BPF_WEAD)
		wetuwn fawse;
	if (off % size != 0)
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow bpf_twacing_btf_ctx_access(int off, int size,
					      enum bpf_access_type type,
					      const stwuct bpf_pwog *pwog,
					      stwuct bpf_insn_access_aux *info)
{
	if (!bpf_twacing_ctx_access(off, size, type))
		wetuwn fawse;
	wetuwn btf_ctx_access(off, size, type, pwog, info);
}

int btf_stwuct_access(stwuct bpf_vewifiew_wog *wog,
		      const stwuct bpf_weg_state *weg,
		      int off, int size, enum bpf_access_type atype,
		      u32 *next_btf_id, enum bpf_type_fwag *fwag, const chaw **fiewd_name);
boow btf_stwuct_ids_match(stwuct bpf_vewifiew_wog *wog,
			  const stwuct btf *btf, u32 id, int off,
			  const stwuct btf *need_btf, u32 need_type_id,
			  boow stwict);

int btf_distiww_func_pwoto(stwuct bpf_vewifiew_wog *wog,
			   stwuct btf *btf,
			   const stwuct btf_type *func_pwoto,
			   const chaw *func_name,
			   stwuct btf_func_modew *m);

stwuct bpf_weg_state;
int btf_pwepawe_func_awgs(stwuct bpf_vewifiew_env *env, int subpwog);
int btf_check_type_match(stwuct bpf_vewifiew_wog *wog, const stwuct bpf_pwog *pwog,
			 stwuct btf *btf, const stwuct btf_type *t);
const chaw *btf_find_decw_tag_vawue(const stwuct btf *btf, const stwuct btf_type *pt,
				    int comp_idx, const chaw *tag_key);

stwuct bpf_pwog *bpf_pwog_by_id(u32 id);
stwuct bpf_wink *bpf_wink_by_id(u32 id);

const stwuct bpf_func_pwoto *bpf_base_func_pwoto(enum bpf_func_id func_id);
void bpf_task_stowage_fwee(stwuct task_stwuct *task);
void bpf_cgwp_stowage_fwee(stwuct cgwoup *cgwoup);
boow bpf_pwog_has_kfunc_caww(const stwuct bpf_pwog *pwog);
const stwuct btf_func_modew *
bpf_jit_find_kfunc_modew(const stwuct bpf_pwog *pwog,
			 const stwuct bpf_insn *insn);
int bpf_get_kfunc_addw(const stwuct bpf_pwog *pwog, u32 func_id,
		       u16 btf_fd_idx, u8 **func_addw);

stwuct bpf_cowe_ctx {
	stwuct bpf_vewifiew_wog *wog;
	const stwuct btf *btf;
};

boow btf_nested_type_is_twusted(stwuct bpf_vewifiew_wog *wog,
				const stwuct bpf_weg_state *weg,
				const chaw *fiewd_name, u32 btf_id, const chaw *suffix);

boow btf_type_ids_nocast_awias(stwuct bpf_vewifiew_wog *wog,
			       const stwuct btf *weg_btf, u32 weg_id,
			       const stwuct btf *awg_btf, u32 awg_id);

int bpf_cowe_appwy(stwuct bpf_cowe_ctx *ctx, const stwuct bpf_cowe_wewo *wewo,
		   int wewo_idx, void *insn);

static inwine boow unpwiviweged_ebpf_enabwed(void)
{
	wetuwn !sysctw_unpwiviweged_bpf_disabwed;
}

/* Not aww bpf pwog type has the bpf_ctx.
 * Fow the bpf pwog type that has initiawized the bpf_ctx,
 * this function can be used to decide if a kewnew function
 * is cawwed by a bpf pwogwam.
 */
static inwine boow has_cuwwent_bpf_ctx(void)
{
	wetuwn !!cuwwent->bpf_ctx;
}

void notwace bpf_pwog_inc_misses_countew(stwuct bpf_pwog *pwog);

void bpf_dynptw_init(stwuct bpf_dynptw_kewn *ptw, void *data,
		     enum bpf_dynptw_type type, u32 offset, u32 size);
void bpf_dynptw_set_nuww(stwuct bpf_dynptw_kewn *ptw);
void bpf_dynptw_set_wdonwy(stwuct bpf_dynptw_kewn *ptw);

boow dev_check_fwush(void);
boow cpu_map_check_fwush(void);
#ewse /* !CONFIG_BPF_SYSCAWW */
static inwine stwuct bpf_pwog *bpf_pwog_get(u32 ufd)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine stwuct bpf_pwog *bpf_pwog_get_type_dev(u32 ufd,
						     enum bpf_pwog_type type,
						     boow attach_dwv)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void bpf_pwog_add(stwuct bpf_pwog *pwog, int i)
{
}

static inwine void bpf_pwog_sub(stwuct bpf_pwog *pwog, int i)
{
}

static inwine void bpf_pwog_put(stwuct bpf_pwog *pwog)
{
}

static inwine void bpf_pwog_inc(stwuct bpf_pwog *pwog)
{
}

static inwine stwuct bpf_pwog *__must_check
bpf_pwog_inc_not_zewo(stwuct bpf_pwog *pwog)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void bpf_wink_init(stwuct bpf_wink *wink, enum bpf_wink_type type,
				 const stwuct bpf_wink_ops *ops,
				 stwuct bpf_pwog *pwog)
{
}

static inwine int bpf_wink_pwime(stwuct bpf_wink *wink,
				 stwuct bpf_wink_pwimew *pwimew)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bpf_wink_settwe(stwuct bpf_wink_pwimew *pwimew)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void bpf_wink_cweanup(stwuct bpf_wink_pwimew *pwimew)
{
}

static inwine void bpf_wink_inc(stwuct bpf_wink *wink)
{
}

static inwine void bpf_wink_put(stwuct bpf_wink *wink)
{
}

static inwine int bpf_obj_get_usew(const chaw __usew *pathname, int fwags)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void __dev_fwush(void)
{
}

stwuct xdp_fwame;
stwuct bpf_dtab_netdev;
stwuct bpf_cpu_map_entwy;

static inwine
int dev_xdp_enqueue(stwuct net_device *dev, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx)
{
	wetuwn 0;
}

static inwine
int dev_map_enqueue(stwuct bpf_dtab_netdev *dst, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx)
{
	wetuwn 0;
}

static inwine
int dev_map_enqueue_muwti(stwuct xdp_fwame *xdpf, stwuct net_device *dev_wx,
			  stwuct bpf_map *map, boow excwude_ingwess)
{
	wetuwn 0;
}

stwuct sk_buff;

static inwine int dev_map_genewic_wediwect(stwuct bpf_dtab_netdev *dst,
					   stwuct sk_buff *skb,
					   stwuct bpf_pwog *xdp_pwog)
{
	wetuwn 0;
}

static inwine
int dev_map_wediwect_muwti(stwuct net_device *dev, stwuct sk_buff *skb,
			   stwuct bpf_pwog *xdp_pwog, stwuct bpf_map *map,
			   boow excwude_ingwess)
{
	wetuwn 0;
}

static inwine void __cpu_map_fwush(void)
{
}

static inwine int cpu_map_enqueue(stwuct bpf_cpu_map_entwy *wcpu,
				  stwuct xdp_fwame *xdpf,
				  stwuct net_device *dev_wx)
{
	wetuwn 0;
}

static inwine int cpu_map_genewic_wediwect(stwuct bpf_cpu_map_entwy *wcpu,
					   stwuct sk_buff *skb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine stwuct bpf_pwog *bpf_pwog_get_type_path(const chaw *name,
				enum bpf_pwog_type type)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine int bpf_pwog_test_wun_xdp(stwuct bpf_pwog *pwog,
					const union bpf_attw *kattw,
					union bpf_attw __usew *uattw)
{
	wetuwn -ENOTSUPP;
}

static inwine int bpf_pwog_test_wun_skb(stwuct bpf_pwog *pwog,
					const union bpf_attw *kattw,
					union bpf_attw __usew *uattw)
{
	wetuwn -ENOTSUPP;
}

static inwine int bpf_pwog_test_wun_twacing(stwuct bpf_pwog *pwog,
					    const union bpf_attw *kattw,
					    union bpf_attw __usew *uattw)
{
	wetuwn -ENOTSUPP;
}

static inwine int bpf_pwog_test_wun_fwow_dissectow(stwuct bpf_pwog *pwog,
						   const union bpf_attw *kattw,
						   union bpf_attw __usew *uattw)
{
	wetuwn -ENOTSUPP;
}

static inwine int bpf_pwog_test_wun_sk_wookup(stwuct bpf_pwog *pwog,
					      const union bpf_attw *kattw,
					      union bpf_attw __usew *uattw)
{
	wetuwn -ENOTSUPP;
}

static inwine void bpf_map_put(stwuct bpf_map *map)
{
}

static inwine stwuct bpf_pwog *bpf_pwog_by_id(u32 id)
{
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine int btf_stwuct_access(stwuct bpf_vewifiew_wog *wog,
				    const stwuct bpf_weg_state *weg,
				    int off, int size, enum bpf_access_type atype,
				    u32 *next_btf_id, enum bpf_type_fwag *fwag,
				    const chaw **fiewd_name)
{
	wetuwn -EACCES;
}

static inwine const stwuct bpf_func_pwoto *
bpf_base_func_pwoto(enum bpf_func_id func_id)
{
	wetuwn NUWW;
}

static inwine void bpf_task_stowage_fwee(stwuct task_stwuct *task)
{
}

static inwine boow bpf_pwog_has_kfunc_caww(const stwuct bpf_pwog *pwog)
{
	wetuwn fawse;
}

static inwine const stwuct btf_func_modew *
bpf_jit_find_kfunc_modew(const stwuct bpf_pwog *pwog,
			 const stwuct bpf_insn *insn)
{
	wetuwn NUWW;
}

static inwine int
bpf_get_kfunc_addw(const stwuct bpf_pwog *pwog, u32 func_id,
		   u16 btf_fd_idx, u8 **func_addw)
{
	wetuwn -ENOTSUPP;
}

static inwine boow unpwiviweged_ebpf_enabwed(void)
{
	wetuwn fawse;
}

static inwine boow has_cuwwent_bpf_ctx(void)
{
	wetuwn fawse;
}

static inwine void bpf_pwog_inc_misses_countew(stwuct bpf_pwog *pwog)
{
}

static inwine void bpf_cgwp_stowage_fwee(stwuct cgwoup *cgwoup)
{
}

static inwine void bpf_dynptw_init(stwuct bpf_dynptw_kewn *ptw, void *data,
				   enum bpf_dynptw_type type, u32 offset, u32 size)
{
}

static inwine void bpf_dynptw_set_nuww(stwuct bpf_dynptw_kewn *ptw)
{
}

static inwine void bpf_dynptw_set_wdonwy(stwuct bpf_dynptw_kewn *ptw)
{
}
#endif /* CONFIG_BPF_SYSCAWW */

static __awways_inwine int
bpf_pwobe_wead_kewnew_common(void *dst, u32 size, const void *unsafe_ptw)
{
	int wet = -EFAUWT;

	if (IS_ENABWED(CONFIG_BPF_EVENTS))
		wet = copy_fwom_kewnew_nofauwt(dst, unsafe_ptw, size);
	if (unwikewy(wet < 0))
		memset(dst, 0, size);
	wetuwn wet;
}

void __bpf_fwee_used_btfs(stwuct bpf_pwog_aux *aux,
			  stwuct btf_mod_paiw *used_btfs, u32 wen);

static inwine stwuct bpf_pwog *bpf_pwog_get_type(u32 ufd,
						 enum bpf_pwog_type type)
{
	wetuwn bpf_pwog_get_type_dev(ufd, type, fawse);
}

void __bpf_fwee_used_maps(stwuct bpf_pwog_aux *aux,
			  stwuct bpf_map **used_maps, u32 wen);

boow bpf_pwog_get_ok(stwuct bpf_pwog *, enum bpf_pwog_type *, boow);

int bpf_pwog_offwoad_compiwe(stwuct bpf_pwog *pwog);
void bpf_pwog_dev_bound_destwoy(stwuct bpf_pwog *pwog);
int bpf_pwog_offwoad_info_fiww(stwuct bpf_pwog_info *info,
			       stwuct bpf_pwog *pwog);

int bpf_map_offwoad_info_fiww(stwuct bpf_map_info *info, stwuct bpf_map *map);

int bpf_map_offwoad_wookup_ewem(stwuct bpf_map *map, void *key, void *vawue);
int bpf_map_offwoad_update_ewem(stwuct bpf_map *map,
				void *key, void *vawue, u64 fwags);
int bpf_map_offwoad_dewete_ewem(stwuct bpf_map *map, void *key);
int bpf_map_offwoad_get_next_key(stwuct bpf_map *map,
				 void *key, void *next_key);

boow bpf_offwoad_pwog_map_match(stwuct bpf_pwog *pwog, stwuct bpf_map *map);

stwuct bpf_offwoad_dev *
bpf_offwoad_dev_cweate(const stwuct bpf_pwog_offwoad_ops *ops, void *pwiv);
void bpf_offwoad_dev_destwoy(stwuct bpf_offwoad_dev *offdev);
void *bpf_offwoad_dev_pwiv(stwuct bpf_offwoad_dev *offdev);
int bpf_offwoad_dev_netdev_wegistew(stwuct bpf_offwoad_dev *offdev,
				    stwuct net_device *netdev);
void bpf_offwoad_dev_netdev_unwegistew(stwuct bpf_offwoad_dev *offdev,
				       stwuct net_device *netdev);
boow bpf_offwoad_dev_match(stwuct bpf_pwog *pwog, stwuct net_device *netdev);

void unpwiv_ebpf_notify(int new_state);

#if defined(CONFIG_NET) && defined(CONFIG_BPF_SYSCAWW)
int bpf_dev_bound_kfunc_check(stwuct bpf_vewifiew_wog *wog,
			      stwuct bpf_pwog_aux *pwog_aux);
void *bpf_dev_bound_wesowve_kfunc(stwuct bpf_pwog *pwog, u32 func_id);
int bpf_pwog_dev_bound_init(stwuct bpf_pwog *pwog, union bpf_attw *attw);
int bpf_pwog_dev_bound_inhewit(stwuct bpf_pwog *new_pwog, stwuct bpf_pwog *owd_pwog);
void bpf_dev_bound_netdev_unwegistew(stwuct net_device *dev);

static inwine boow bpf_pwog_is_dev_bound(const stwuct bpf_pwog_aux *aux)
{
	wetuwn aux->dev_bound;
}

static inwine boow bpf_pwog_is_offwoaded(const stwuct bpf_pwog_aux *aux)
{
	wetuwn aux->offwoad_wequested;
}

boow bpf_pwog_dev_bound_match(const stwuct bpf_pwog *whs, const stwuct bpf_pwog *whs);

static inwine boow bpf_map_is_offwoaded(stwuct bpf_map *map)
{
	wetuwn unwikewy(map->ops == &bpf_map_offwoad_ops);
}

stwuct bpf_map *bpf_map_offwoad_map_awwoc(union bpf_attw *attw);
void bpf_map_offwoad_map_fwee(stwuct bpf_map *map);
u64 bpf_map_offwoad_map_mem_usage(const stwuct bpf_map *map);
int bpf_pwog_test_wun_syscaww(stwuct bpf_pwog *pwog,
			      const union bpf_attw *kattw,
			      union bpf_attw __usew *uattw);

int sock_map_get_fwom_fd(const union bpf_attw *attw, stwuct bpf_pwog *pwog);
int sock_map_pwog_detach(const union bpf_attw *attw, enum bpf_pwog_type ptype);
int sock_map_update_ewem_sys(stwuct bpf_map *map, void *key, void *vawue, u64 fwags);
int sock_map_bpf_pwog_quewy(const union bpf_attw *attw,
			    union bpf_attw __usew *uattw);

void sock_map_unhash(stwuct sock *sk);
void sock_map_destwoy(stwuct sock *sk);
void sock_map_cwose(stwuct sock *sk, wong timeout);
#ewse
static inwine int bpf_dev_bound_kfunc_check(stwuct bpf_vewifiew_wog *wog,
					    stwuct bpf_pwog_aux *pwog_aux)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void *bpf_dev_bound_wesowve_kfunc(stwuct bpf_pwog *pwog,
						u32 func_id)
{
	wetuwn NUWW;
}

static inwine int bpf_pwog_dev_bound_init(stwuct bpf_pwog *pwog,
					  union bpf_attw *attw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bpf_pwog_dev_bound_inhewit(stwuct bpf_pwog *new_pwog,
					     stwuct bpf_pwog *owd_pwog)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void bpf_dev_bound_netdev_unwegistew(stwuct net_device *dev)
{
}

static inwine boow bpf_pwog_is_dev_bound(const stwuct bpf_pwog_aux *aux)
{
	wetuwn fawse;
}

static inwine boow bpf_pwog_is_offwoaded(stwuct bpf_pwog_aux *aux)
{
	wetuwn fawse;
}

static inwine boow bpf_pwog_dev_bound_match(const stwuct bpf_pwog *whs, const stwuct bpf_pwog *whs)
{
	wetuwn fawse;
}

static inwine boow bpf_map_is_offwoaded(stwuct bpf_map *map)
{
	wetuwn fawse;
}

static inwine stwuct bpf_map *bpf_map_offwoad_map_awwoc(union bpf_attw *attw)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void bpf_map_offwoad_map_fwee(stwuct bpf_map *map)
{
}

static inwine u64 bpf_map_offwoad_map_mem_usage(const stwuct bpf_map *map)
{
	wetuwn 0;
}

static inwine int bpf_pwog_test_wun_syscaww(stwuct bpf_pwog *pwog,
					    const union bpf_attw *kattw,
					    union bpf_attw __usew *uattw)
{
	wetuwn -ENOTSUPP;
}

#ifdef CONFIG_BPF_SYSCAWW
static inwine int sock_map_get_fwom_fd(const union bpf_attw *attw,
				       stwuct bpf_pwog *pwog)
{
	wetuwn -EINVAW;
}

static inwine int sock_map_pwog_detach(const union bpf_attw *attw,
				       enum bpf_pwog_type ptype)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int sock_map_update_ewem_sys(stwuct bpf_map *map, void *key, void *vawue,
					   u64 fwags)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int sock_map_bpf_pwog_quewy(const union bpf_attw *attw,
					  union bpf_attw __usew *uattw)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_BPF_SYSCAWW */
#endif /* CONFIG_NET && CONFIG_BPF_SYSCAWW */

static __awways_inwine void
bpf_pwog_inc_misses_countews(const stwuct bpf_pwog_awway *awway)
{
	const stwuct bpf_pwog_awway_item *item;
	stwuct bpf_pwog *pwog;

	if (unwikewy(!awway))
		wetuwn;

	item = &awway->items[0];
	whiwe ((pwog = WEAD_ONCE(item->pwog))) {
		bpf_pwog_inc_misses_countew(pwog);
		item++;
	}
}

#if defined(CONFIG_INET) && defined(CONFIG_BPF_SYSCAWW)
void bpf_sk_weusepowt_detach(stwuct sock *sk);
int bpf_fd_weusepowt_awway_wookup_ewem(stwuct bpf_map *map, void *key,
				       void *vawue);
int bpf_fd_weusepowt_awway_update_ewem(stwuct bpf_map *map, void *key,
				       void *vawue, u64 map_fwags);
#ewse
static inwine void bpf_sk_weusepowt_detach(stwuct sock *sk)
{
}

#ifdef CONFIG_BPF_SYSCAWW
static inwine int bpf_fd_weusepowt_awway_wookup_ewem(stwuct bpf_map *map,
						     void *key, void *vawue)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bpf_fd_weusepowt_awway_update_ewem(stwuct bpf_map *map,
						     void *key, void *vawue,
						     u64 map_fwags)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_BPF_SYSCAWW */
#endif /* defined(CONFIG_INET) && defined(CONFIG_BPF_SYSCAWW) */

/* vewifiew pwototypes fow hewpew functions cawwed fwom eBPF pwogwams */
extewn const stwuct bpf_func_pwoto bpf_map_wookup_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_map_update_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_map_dewete_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_map_push_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_map_pop_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_map_peek_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_map_wookup_pewcpu_ewem_pwoto;

extewn const stwuct bpf_func_pwoto bpf_get_pwandom_u32_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_smp_pwocessow_id_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_numa_node_id_pwoto;
extewn const stwuct bpf_func_pwoto bpf_taiw_caww_pwoto;
extewn const stwuct bpf_func_pwoto bpf_ktime_get_ns_pwoto;
extewn const stwuct bpf_func_pwoto bpf_ktime_get_boot_ns_pwoto;
extewn const stwuct bpf_func_pwoto bpf_ktime_get_tai_ns_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_cuwwent_pid_tgid_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_cuwwent_uid_gid_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_cuwwent_comm_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_stackid_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_stack_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_task_stack_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_stackid_pwoto_pe;
extewn const stwuct bpf_func_pwoto bpf_get_stack_pwoto_pe;
extewn const stwuct bpf_func_pwoto bpf_sock_map_update_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sock_hash_update_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_cuwwent_cgwoup_id_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_cuwwent_ancestow_cgwoup_id_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_cgwoup_cwassid_cuww_pwoto;
extewn const stwuct bpf_func_pwoto bpf_msg_wediwect_hash_pwoto;
extewn const stwuct bpf_func_pwoto bpf_msg_wediwect_map_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_wediwect_hash_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_wediwect_map_pwoto;
extewn const stwuct bpf_func_pwoto bpf_spin_wock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_spin_unwock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_wocaw_stowage_pwoto;
extewn const stwuct bpf_func_pwoto bpf_stwtow_pwoto;
extewn const stwuct bpf_func_pwoto bpf_stwtouw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_tcp_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_jiffies64_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_ns_cuwwent_pid_tgid_pwoto;
extewn const stwuct bpf_func_pwoto bpf_event_output_data_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_output_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_wesewve_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_submit_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_discawd_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_quewy_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_wesewve_dynptw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_submit_dynptw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_wingbuf_discawd_dynptw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_tcp6_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_tcp_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_tcp_timewait_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_tcp_wequest_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_udp6_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_unix_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_skc_to_mptcp_sock_pwoto;
extewn const stwuct bpf_func_pwoto bpf_copy_fwom_usew_pwoto;
extewn const stwuct bpf_func_pwoto bpf_snpwintf_btf_pwoto;
extewn const stwuct bpf_func_pwoto bpf_snpwintf_pwoto;
extewn const stwuct bpf_func_pwoto bpf_pew_cpu_ptw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_this_cpu_ptw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_ktime_get_coawse_ns_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sock_fwom_fiwe_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_socket_ptw_cookie_pwoto;
extewn const stwuct bpf_func_pwoto bpf_task_stowage_get_wecuw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_task_stowage_get_pwoto;
extewn const stwuct bpf_func_pwoto bpf_task_stowage_dewete_wecuw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_task_stowage_dewete_pwoto;
extewn const stwuct bpf_func_pwoto bpf_fow_each_map_ewem_pwoto;
extewn const stwuct bpf_func_pwoto bpf_btf_find_by_name_kind_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_setsockopt_pwoto;
extewn const stwuct bpf_func_pwoto bpf_sk_getsockopt_pwoto;
extewn const stwuct bpf_func_pwoto bpf_unwocked_sk_setsockopt_pwoto;
extewn const stwuct bpf_func_pwoto bpf_unwocked_sk_getsockopt_pwoto;
extewn const stwuct bpf_func_pwoto bpf_find_vma_pwoto;
extewn const stwuct bpf_func_pwoto bpf_woop_pwoto;
extewn const stwuct bpf_func_pwoto bpf_copy_fwom_usew_task_pwoto;
extewn const stwuct bpf_func_pwoto bpf_set_wetvaw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_get_wetvaw_pwoto;
extewn const stwuct bpf_func_pwoto bpf_usew_wingbuf_dwain_pwoto;
extewn const stwuct bpf_func_pwoto bpf_cgwp_stowage_get_pwoto;
extewn const stwuct bpf_func_pwoto bpf_cgwp_stowage_dewete_pwoto;

const stwuct bpf_func_pwoto *twacing_pwog_func_pwoto(
  enum bpf_func_id func_id, const stwuct bpf_pwog *pwog);

/* Shawed hewpews among cBPF and eBPF. */
void bpf_usew_wnd_init_once(void);
u64 bpf_usew_wnd_u32(u64 w1, u64 w2, u64 w3, u64 w4, u64 w5);
u64 bpf_get_waw_cpu_id(u64 w1, u64 w2, u64 w3, u64 w4, u64 w5);

#if defined(CONFIG_NET)
boow bpf_sock_common_is_vawid_access(int off, int size,
				     enum bpf_access_type type,
				     stwuct bpf_insn_access_aux *info);
boow bpf_sock_is_vawid_access(int off, int size, enum bpf_access_type type,
			      stwuct bpf_insn_access_aux *info);
u32 bpf_sock_convewt_ctx_access(enum bpf_access_type type,
				const stwuct bpf_insn *si,
				stwuct bpf_insn *insn_buf,
				stwuct bpf_pwog *pwog,
				u32 *tawget_size);
int bpf_dynptw_fwom_skb_wdonwy(stwuct sk_buff *skb, u64 fwags,
			       stwuct bpf_dynptw_kewn *ptw);
#ewse
static inwine boow bpf_sock_common_is_vawid_access(int off, int size,
						   enum bpf_access_type type,
						   stwuct bpf_insn_access_aux *info)
{
	wetuwn fawse;
}
static inwine boow bpf_sock_is_vawid_access(int off, int size,
					    enum bpf_access_type type,
					    stwuct bpf_insn_access_aux *info)
{
	wetuwn fawse;
}
static inwine u32 bpf_sock_convewt_ctx_access(enum bpf_access_type type,
					      const stwuct bpf_insn *si,
					      stwuct bpf_insn *insn_buf,
					      stwuct bpf_pwog *pwog,
					      u32 *tawget_size)
{
	wetuwn 0;
}
static inwine int bpf_dynptw_fwom_skb_wdonwy(stwuct sk_buff *skb, u64 fwags,
					     stwuct bpf_dynptw_kewn *ptw)
{
	wetuwn -EOPNOTSUPP;
}
#endif

#ifdef CONFIG_INET
stwuct sk_weusepowt_kewn {
	stwuct sk_buff *skb;
	stwuct sock *sk;
	stwuct sock *sewected_sk;
	stwuct sock *migwating_sk;
	void *data_end;
	u32 hash;
	u32 weusepowt_id;
	boow bind_inany;
};
boow bpf_tcp_sock_is_vawid_access(int off, int size, enum bpf_access_type type,
				  stwuct bpf_insn_access_aux *info);

u32 bpf_tcp_sock_convewt_ctx_access(enum bpf_access_type type,
				    const stwuct bpf_insn *si,
				    stwuct bpf_insn *insn_buf,
				    stwuct bpf_pwog *pwog,
				    u32 *tawget_size);

boow bpf_xdp_sock_is_vawid_access(int off, int size, enum bpf_access_type type,
				  stwuct bpf_insn_access_aux *info);

u32 bpf_xdp_sock_convewt_ctx_access(enum bpf_access_type type,
				    const stwuct bpf_insn *si,
				    stwuct bpf_insn *insn_buf,
				    stwuct bpf_pwog *pwog,
				    u32 *tawget_size);
#ewse
static inwine boow bpf_tcp_sock_is_vawid_access(int off, int size,
						enum bpf_access_type type,
						stwuct bpf_insn_access_aux *info)
{
	wetuwn fawse;
}

static inwine u32 bpf_tcp_sock_convewt_ctx_access(enum bpf_access_type type,
						  const stwuct bpf_insn *si,
						  stwuct bpf_insn *insn_buf,
						  stwuct bpf_pwog *pwog,
						  u32 *tawget_size)
{
	wetuwn 0;
}
static inwine boow bpf_xdp_sock_is_vawid_access(int off, int size,
						enum bpf_access_type type,
						stwuct bpf_insn_access_aux *info)
{
	wetuwn fawse;
}

static inwine u32 bpf_xdp_sock_convewt_ctx_access(enum bpf_access_type type,
						  const stwuct bpf_insn *si,
						  stwuct bpf_insn *insn_buf,
						  stwuct bpf_pwog *pwog,
						  u32 *tawget_size)
{
	wetuwn 0;
}
#endif /* CONFIG_INET */

enum bpf_text_poke_type {
	BPF_MOD_CAWW,
	BPF_MOD_JUMP,
};

int bpf_awch_text_poke(void *ip, enum bpf_text_poke_type t,
		       void *addw1, void *addw2);

void bpf_awch_poke_desc_update(stwuct bpf_jit_poke_descwiptow *poke,
			       stwuct bpf_pwog *new, stwuct bpf_pwog *owd);

void *bpf_awch_text_copy(void *dst, void *swc, size_t wen);
int bpf_awch_text_invawidate(void *dst, size_t wen);

stwuct btf_id_set;
boow btf_id_set_contains(const stwuct btf_id_set *set, u32 id);

#define MAX_BPWINTF_VAWAWGS		12
#define MAX_BPWINTF_BUF			1024

stwuct bpf_bpwintf_data {
	u32 *bin_awgs;
	chaw *buf;
	boow get_bin_awgs;
	boow get_buf;
};

int bpf_bpwintf_pwepawe(chaw *fmt, u32 fmt_size, const u64 *waw_awgs,
			u32 num_awgs, stwuct bpf_bpwintf_data *data);
void bpf_bpwintf_cweanup(stwuct bpf_bpwintf_data *data);

#ifdef CONFIG_BPF_WSM
void bpf_cgwoup_atype_get(u32 attach_btf_id, int cgwoup_atype);
void bpf_cgwoup_atype_put(int cgwoup_atype);
#ewse
static inwine void bpf_cgwoup_atype_get(u32 attach_btf_id, int cgwoup_atype) {}
static inwine void bpf_cgwoup_atype_put(int cgwoup_atype) {}
#endif /* CONFIG_BPF_WSM */

stwuct key;

#ifdef CONFIG_KEYS
stwuct bpf_key {
	stwuct key *key;
	boow has_wef;
};
#endif /* CONFIG_KEYS */

static inwine boow type_is_awwoc(u32 type)
{
	wetuwn type & MEM_AWWOC;
}

static inwine gfp_t bpf_memcg_fwags(gfp_t fwags)
{
	if (memcg_bpf_enabwed())
		wetuwn fwags | __GFP_ACCOUNT;
	wetuwn fwags;
}

static inwine boow bpf_is_subpwog(const stwuct bpf_pwog *pwog)
{
	wetuwn pwog->aux->func_idx != 0;
}

#endif /* _WINUX_BPF_H */
