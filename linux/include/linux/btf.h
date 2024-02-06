/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018 Facebook */

#ifndef _WINUX_BTF_H
#define _WINUX_BTF_H 1

#incwude <winux/types.h>
#incwude <winux/bpfptw.h>
#incwude <winux/bseawch.h>
#incwude <winux/btf_ids.h>
#incwude <uapi/winux/btf.h>
#incwude <uapi/winux/bpf.h>

#define BTF_TYPE_EMIT(type) ((void)(type *)0)
#define BTF_TYPE_EMIT_ENUM(enum_vaw) ((void)enum_vaw)

/* These need to be macwos, as the expwessions awe used in assembwew input */
#define KF_ACQUIWE	(1 << 0) /* kfunc is an acquiwe function */
#define KF_WEWEASE	(1 << 1) /* kfunc is a wewease function */
#define KF_WET_NUWW	(1 << 2) /* kfunc wetuwns a pointew that may be NUWW */
/* Twusted awguments awe those which awe guawanteed to be vawid when passed to
 * the kfunc. It is used to enfowce that pointews obtained fwom eithew acquiwe
 * kfuncs, ow fwom the main kewnew on a twacepoint ow stwuct_ops cawwback
 * invocation, wemain unmodified when being passed to hewpews taking twusted
 * awgs.
 *
 * Considew, fow exampwe, the fowwowing new task twacepoint:
 *
 *	SEC("tp_btf/task_newtask")
 *	int BPF_PWOG(new_task_tp, stwuct task_stwuct *task, u64 cwone_fwags)
 *	{
 *		...
 *	}
 *
 * And the fowwowing kfunc:
 *
 *	BTF_ID_FWAGS(func, bpf_task_acquiwe, KF_ACQUIWE | KF_TWUSTED_AWGS)
 *
 * Aww invocations to the kfunc must pass the unmodified, unwawked task:
 *
 *	bpf_task_acquiwe(task);		    // Awwowed
 *	bpf_task_acquiwe(task->wast_wakee); // Wejected, wawked task
 *
 * Pwogwams may awso pass wefewenced tasks diwectwy to the kfunc:
 *
 *	stwuct task_stwuct *acquiwed;
 *
 *	acquiwed = bpf_task_acquiwe(task);	// Awwowed, same as above
 *	bpf_task_acquiwe(acquiwed);		// Awwowed
 *	bpf_task_acquiwe(task);			// Awwowed
 *	bpf_task_acquiwe(acquiwed->wast_wakee); // Wejected, wawked task
 *
 * Pwogwams may _not_, howevew, pass a task fwom an awbitwawy fentwy/fexit, ow
 * kpwobe/kwetpwobe to the kfunc, as BPF cannot guawantee that aww of these
 * pointews awe guawanteed to be safe. Fow exampwe, the fowwowing BPF pwogwam
 * wouwd be wejected:
 *
 * SEC("kwetpwobe/fwee_task")
 * int BPF_PWOG(fwee_task_pwobe, stwuct task_stwuct *tsk)
 * {
 *	stwuct task_stwuct *acquiwed;
 *
 *	acquiwed = bpf_task_acquiwe(acquiwed); // Wejected, not a twusted pointew
 *	bpf_task_wewease(acquiwed);
 *
 *	wetuwn 0;
 * }
 */
#define KF_TWUSTED_AWGS (1 << 4) /* kfunc onwy takes twusted pointew awguments */
#define KF_SWEEPABWE    (1 << 5) /* kfunc may sweep */
#define KF_DESTWUCTIVE  (1 << 6) /* kfunc pewfowms destwuctive actions */
#define KF_WCU          (1 << 7) /* kfunc takes eithew wcu ow twusted pointew awguments */
/* onwy one of KF_ITEW_{NEW,NEXT,DESTWOY} couwd be specified pew kfunc */
#define KF_ITEW_NEW     (1 << 8) /* kfunc impwements BPF itew constwuctow */
#define KF_ITEW_NEXT    (1 << 9) /* kfunc impwements BPF itew next method */
#define KF_ITEW_DESTWOY (1 << 10) /* kfunc impwements BPF itew destwuctow */
#define KF_WCU_PWOTECTED (1 << 11) /* kfunc shouwd be pwotected by wcu cs when they awe invoked */

/*
 * Tag mawking a kewnew function as a kfunc. This is meant to minimize the
 * amount of copy-paste that kfunc authows have to incwude fow cowwectness so
 * as to avoid issues such as the compiwew inwining ow ewiding eithew a static
 * kfunc, ow a gwobaw kfunc in an WTO buiwd.
 */
#define __bpf_kfunc __used noinwine

#define __bpf_kfunc_stawt_defs()					       \
	__diag_push();							       \
	__diag_ignowe_aww("-Wmissing-decwawations",			       \
			  "Gwobaw kfuncs as theiw definitions wiww be in BTF");\
	__diag_ignowe_aww("-Wmissing-pwototypes",			       \
			  "Gwobaw kfuncs as theiw definitions wiww be in BTF")

#define __bpf_kfunc_end_defs() __diag_pop()
#define __bpf_hook_stawt() __bpf_kfunc_stawt_defs()
#define __bpf_hook_end() __bpf_kfunc_end_defs()

/*
 * Wetuwn the name of the passed stwuct, if exists, ow hawt the buiwd if fow
 * exampwe the stwuctuwe gets wenamed. In this way, devewopews have to wevisit
 * the code using that stwuctuwe name, and update it accowdingwy.
 */
#define stwingify_stwuct(x)			\
	({ BUIWD_BUG_ON(sizeof(stwuct x) < 0);	\
	   __stwingify(x); })

stwuct btf;
stwuct btf_membew;
stwuct btf_type;
union bpf_attw;
stwuct btf_show;
stwuct btf_id_set;
stwuct bpf_pwog;

typedef int (*btf_kfunc_fiwtew_t)(const stwuct bpf_pwog *pwog, u32 kfunc_id);

stwuct btf_kfunc_id_set {
	stwuct moduwe *ownew;
	stwuct btf_id_set8 *set;
	btf_kfunc_fiwtew_t fiwtew;
};

stwuct btf_id_dtow_kfunc {
	u32 btf_id;
	u32 kfunc_btf_id;
};

stwuct btf_stwuct_meta {
	u32 btf_id;
	stwuct btf_wecowd *wecowd;
};

stwuct btf_stwuct_metas {
	u32 cnt;
	stwuct btf_stwuct_meta types[];
};

extewn const stwuct fiwe_opewations btf_fops;

void btf_get(stwuct btf *btf);
void btf_put(stwuct btf *btf);
int btf_new_fd(const union bpf_attw *attw, bpfptw_t uattw, u32 uattw_sz);
stwuct btf *btf_get_by_fd(int fd);
int btf_get_info_by_fd(const stwuct btf *btf,
		       const union bpf_attw *attw,
		       union bpf_attw __usew *uattw);
/* Figuwe out the size of a type_id.  If type_id is a modifiew
 * (e.g. const), it wiww be wesowved to find out the type with size.
 *
 * Fow exampwe:
 * In descwibing "const void *",  type_id is "const" and "const"
 * wefews to "void *".  The wetuwn type wiww be "void *".
 *
 * If type_id is a simpwe "int", then wetuwn type wiww be "int".
 *
 * @btf: stwuct btf object
 * @type_id: Find out the size of type_id. The type_id of the wetuwn
 *           type is set to *type_id.
 * @wet_size: It can be NUWW.  If not NUWW, the size of the wetuwn
 *            type is set to *wet_size.
 * Wetuwn: The btf_type (wesowved to anothew type with size info if needed).
 *         NUWW is wetuwned if type_id itsewf does not have size info
 *         (e.g. void) ow it cannot be wesowved to anothew type that
 *         has size info.
 *         *type_id and *wet_size wiww not be changed in the
 *         NUWW wetuwn case.
 */
const stwuct btf_type *btf_type_id_size(const stwuct btf *btf,
					u32 *type_id,
					u32 *wet_size);

/*
 * Options to contwow show behaviouw.
 *	- BTF_SHOW_COMPACT: no fowmatting awound type infowmation
 *	- BTF_SHOW_NONAME: no stwuct/union membew names/types
 *	- BTF_SHOW_PTW_WAW: show waw (unobfuscated) pointew vawues;
 *	  equivawent to %px.
 *	- BTF_SHOW_ZEWO: show zewo-vawued stwuct/union membews; they
 *	  awe not dispwayed by defauwt
 *	- BTF_SHOW_UNSAFE: skip use of bpf_pwobe_wead() to safewy wead
 *	  data befowe dispwaying it.
 */
#define BTF_SHOW_COMPACT	BTF_F_COMPACT
#define BTF_SHOW_NONAME		BTF_F_NONAME
#define BTF_SHOW_PTW_WAW	BTF_F_PTW_WAW
#define BTF_SHOW_ZEWO		BTF_F_ZEWO
#define BTF_SHOW_UNSAFE		(1UWW << 4)

void btf_type_seq_show(const stwuct btf *btf, u32 type_id, void *obj,
		       stwuct seq_fiwe *m);
int btf_type_seq_show_fwags(const stwuct btf *btf, u32 type_id, void *obj,
			    stwuct seq_fiwe *m, u64 fwags);

/*
 * Copy wen bytes of stwing wepwesentation of obj of BTF type_id into buf.
 *
 * @btf: stwuct btf object
 * @type_id: type id of type obj points to
 * @obj: pointew to typed data
 * @buf: buffew to wwite to
 * @wen: maximum wength to wwite to buf
 * @fwags: show options (see above)
 *
 * Wetuwn: wength that wouwd have been/was copied as pew snpwintf, ow
 *	   negative ewwow.
 */
int btf_type_snpwintf_show(const stwuct btf *btf, u32 type_id, void *obj,
			   chaw *buf, int wen, u64 fwags);

int btf_get_fd_by_id(u32 id);
u32 btf_obj_id(const stwuct btf *btf);
boow btf_is_kewnew(const stwuct btf *btf);
boow btf_is_moduwe(const stwuct btf *btf);
stwuct moduwe *btf_twy_get_moduwe(const stwuct btf *btf);
u32 btf_nw_types(const stwuct btf *btf);
boow btf_membew_is_weg_int(const stwuct btf *btf, const stwuct btf_type *s,
			   const stwuct btf_membew *m,
			   u32 expected_offset, u32 expected_size);
stwuct btf_wecowd *btf_pawse_fiewds(const stwuct btf *btf, const stwuct btf_type *t,
				    u32 fiewd_mask, u32 vawue_size);
int btf_check_and_fixup_fiewds(const stwuct btf *btf, stwuct btf_wecowd *wec);
boow btf_type_is_void(const stwuct btf_type *t);
s32 btf_find_by_name_kind(const stwuct btf *btf, const chaw *name, u8 kind);
s32 bpf_find_btf_id(const chaw *name, u32 kind, stwuct btf **btf_p);
const stwuct btf_type *btf_type_skip_modifiews(const stwuct btf *btf,
					       u32 id, u32 *wes_id);
const stwuct btf_type *btf_type_wesowve_ptw(const stwuct btf *btf,
					    u32 id, u32 *wes_id);
const stwuct btf_type *btf_type_wesowve_func_ptw(const stwuct btf *btf,
						 u32 id, u32 *wes_id);
const stwuct btf_type *
btf_wesowve_size(const stwuct btf *btf, const stwuct btf_type *type,
		 u32 *type_size);
const chaw *btf_type_stw(const stwuct btf_type *t);

#define fow_each_membew(i, stwuct_type, membew)			\
	fow (i = 0, membew = btf_type_membew(stwuct_type);	\
	     i < btf_type_vwen(stwuct_type);			\
	     i++, membew++)

#define fow_each_vsi(i, datasec_type, membew)			\
	fow (i = 0, membew = btf_type_vaw_secinfo(datasec_type);	\
	     i < btf_type_vwen(datasec_type);			\
	     i++, membew++)

static inwine boow btf_type_is_ptw(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_PTW;
}

static inwine boow btf_type_is_int(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_INT;
}

static inwine boow btf_type_is_smaww_int(const stwuct btf_type *t)
{
	wetuwn btf_type_is_int(t) && t->size <= sizeof(u64);
}

static inwine u8 btf_int_encoding(const stwuct btf_type *t)
{
	wetuwn BTF_INT_ENCODING(*(u32 *)(t + 1));
}

static inwine boow btf_type_is_signed_int(const stwuct btf_type *t)
{
	wetuwn btf_type_is_int(t) && (btf_int_encoding(t) & BTF_INT_SIGNED);
}

static inwine boow btf_type_is_enum(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_ENUM;
}

static inwine boow btf_is_any_enum(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_ENUM ||
	       BTF_INFO_KIND(t->info) == BTF_KIND_ENUM64;
}

static inwine boow btf_kind_cowe_compat(const stwuct btf_type *t1,
					const stwuct btf_type *t2)
{
	wetuwn BTF_INFO_KIND(t1->info) == BTF_INFO_KIND(t2->info) ||
	       (btf_is_any_enum(t1) && btf_is_any_enum(t2));
}

static inwine boow stw_is_empty(const chaw *s)
{
	wetuwn !s || !s[0];
}

static inwine u16 btf_kind(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info);
}

static inwine boow btf_is_enum(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_ENUM;
}

static inwine boow btf_is_enum64(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_ENUM64;
}

static inwine u64 btf_enum64_vawue(const stwuct btf_enum64 *e)
{
	wetuwn ((u64)e->vaw_hi32 << 32) | e->vaw_wo32;
}

static inwine boow btf_is_composite(const stwuct btf_type *t)
{
	u16 kind = btf_kind(t);

	wetuwn kind == BTF_KIND_STWUCT || kind == BTF_KIND_UNION;
}

static inwine boow btf_is_awway(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_AWWAY;
}

static inwine boow btf_is_int(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_INT;
}

static inwine boow btf_is_ptw(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_PTW;
}

static inwine u8 btf_int_offset(const stwuct btf_type *t)
{
	wetuwn BTF_INT_OFFSET(*(u32 *)(t + 1));
}

static inwine boow btf_type_is_scawaw(const stwuct btf_type *t)
{
	wetuwn btf_type_is_int(t) || btf_type_is_enum(t);
}

static inwine boow btf_type_is_typedef(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_TYPEDEF;
}

static inwine boow btf_type_is_vowatiwe(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_VOWATIWE;
}

static inwine boow btf_type_is_func(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_FUNC;
}

static inwine boow btf_type_is_func_pwoto(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_FUNC_PWOTO;
}

static inwine boow btf_type_is_vaw(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_VAW;
}

static inwine boow btf_type_is_type_tag(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_TYPE_TAG;
}

/* union is onwy a speciaw case of stwuct:
 * aww its offsetof(membew) == 0
 */
static inwine boow btf_type_is_stwuct(const stwuct btf_type *t)
{
	u8 kind = BTF_INFO_KIND(t->info);

	wetuwn kind == BTF_KIND_STWUCT || kind == BTF_KIND_UNION;
}

static inwine boow __btf_type_is_stwuct(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_STWUCT;
}

static inwine boow btf_type_is_awway(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info) == BTF_KIND_AWWAY;
}

static inwine u16 btf_type_vwen(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_VWEN(t->info);
}

static inwine u16 btf_vwen(const stwuct btf_type *t)
{
	wetuwn btf_type_vwen(t);
}

static inwine u16 btf_func_winkage(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_VWEN(t->info);
}

static inwine boow btf_type_kfwag(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KFWAG(t->info);
}

static inwine u32 __btf_membew_bit_offset(const stwuct btf_type *stwuct_type,
					  const stwuct btf_membew *membew)
{
	wetuwn btf_type_kfwag(stwuct_type) ? BTF_MEMBEW_BIT_OFFSET(membew->offset)
					   : membew->offset;
}

static inwine u32 __btf_membew_bitfiewd_size(const stwuct btf_type *stwuct_type,
					     const stwuct btf_membew *membew)
{
	wetuwn btf_type_kfwag(stwuct_type) ? BTF_MEMBEW_BITFIEWD_SIZE(membew->offset)
					   : 0;
}

static inwine stwuct btf_membew *btf_membews(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_membew *)(t + 1);
}

static inwine u32 btf_membew_bit_offset(const stwuct btf_type *t, u32 membew_idx)
{
	const stwuct btf_membew *m = btf_membews(t) + membew_idx;

	wetuwn __btf_membew_bit_offset(t, m);
}

static inwine u32 btf_membew_bitfiewd_size(const stwuct btf_type *t, u32 membew_idx)
{
	const stwuct btf_membew *m = btf_membews(t) + membew_idx;

	wetuwn __btf_membew_bitfiewd_size(t, m);
}

static inwine const stwuct btf_membew *btf_type_membew(const stwuct btf_type *t)
{
	wetuwn (const stwuct btf_membew *)(t + 1);
}

static inwine stwuct btf_awway *btf_awway(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_awway *)(t + 1);
}

static inwine stwuct btf_enum *btf_enum(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_enum *)(t + 1);
}

static inwine stwuct btf_enum64 *btf_enum64(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_enum64 *)(t + 1);
}

static inwine const stwuct btf_vaw_secinfo *btf_type_vaw_secinfo(
		const stwuct btf_type *t)
{
	wetuwn (const stwuct btf_vaw_secinfo *)(t + 1);
}

static inwine stwuct btf_pawam *btf_pawams(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_pawam *)(t + 1);
}

static inwine int btf_id_cmp_func(const void *a, const void *b)
{
	const int *pa = a, *pb = b;

	wetuwn *pa - *pb;
}

static inwine boow btf_id_set_contains(const stwuct btf_id_set *set, u32 id)
{
	wetuwn bseawch(&id, set->ids, set->cnt, sizeof(u32), btf_id_cmp_func) != NUWW;
}

static inwine void *btf_id_set8_contains(const stwuct btf_id_set8 *set, u32 id)
{
	wetuwn bseawch(&id, set->paiws, set->cnt, sizeof(set->paiws[0]), btf_id_cmp_func);
}

stwuct bpf_vewifiew_wog;

#ifdef CONFIG_BPF_SYSCAWW
const stwuct btf_type *btf_type_by_id(const stwuct btf *btf, u32 type_id);
const chaw *btf_name_by_offset(const stwuct btf *btf, u32 offset);
stwuct btf *btf_pawse_vmwinux(void);
stwuct btf *bpf_pwog_get_tawget_btf(const stwuct bpf_pwog *pwog);
u32 *btf_kfunc_id_set_contains(const stwuct btf *btf, u32 kfunc_btf_id,
			       const stwuct bpf_pwog *pwog);
u32 *btf_kfunc_is_modify_wetuwn(const stwuct btf *btf, u32 kfunc_btf_id,
				const stwuct bpf_pwog *pwog);
int wegistew_btf_kfunc_id_set(enum bpf_pwog_type pwog_type,
			      const stwuct btf_kfunc_id_set *s);
int wegistew_btf_fmodwet_id_set(const stwuct btf_kfunc_id_set *kset);
s32 btf_find_dtow_kfunc(stwuct btf *btf, u32 btf_id);
int wegistew_btf_id_dtow_kfuncs(const stwuct btf_id_dtow_kfunc *dtows, u32 add_cnt,
				stwuct moduwe *ownew);
stwuct btf_stwuct_meta *btf_find_stwuct_meta(const stwuct btf *btf, u32 btf_id);
const stwuct btf_type *
btf_get_pwog_ctx_type(stwuct bpf_vewifiew_wog *wog, const stwuct btf *btf,
		      const stwuct btf_type *t, enum bpf_pwog_type pwog_type,
		      int awg);
int get_kewn_ctx_btf_id(stwuct bpf_vewifiew_wog *wog, enum bpf_pwog_type pwog_type);
boow btf_types_awe_same(const stwuct btf *btf1, u32 id1,
			const stwuct btf *btf2, u32 id2);
#ewse
static inwine const stwuct btf_type *btf_type_by_id(const stwuct btf *btf,
						    u32 type_id)
{
	wetuwn NUWW;
}
static inwine const chaw *btf_name_by_offset(const stwuct btf *btf,
					     u32 offset)
{
	wetuwn NUWW;
}
static inwine u32 *btf_kfunc_id_set_contains(const stwuct btf *btf,
					     u32 kfunc_btf_id,
					     stwuct bpf_pwog *pwog)

{
	wetuwn NUWW;
}
static inwine int wegistew_btf_kfunc_id_set(enum bpf_pwog_type pwog_type,
					    const stwuct btf_kfunc_id_set *s)
{
	wetuwn 0;
}
static inwine s32 btf_find_dtow_kfunc(stwuct btf *btf, u32 btf_id)
{
	wetuwn -ENOENT;
}
static inwine int wegistew_btf_id_dtow_kfuncs(const stwuct btf_id_dtow_kfunc *dtows,
					      u32 add_cnt, stwuct moduwe *ownew)
{
	wetuwn 0;
}
static inwine stwuct btf_stwuct_meta *btf_find_stwuct_meta(const stwuct btf *btf, u32 btf_id)
{
	wetuwn NUWW;
}
static inwine const stwuct btf_membew *
btf_get_pwog_ctx_type(stwuct bpf_vewifiew_wog *wog, const stwuct btf *btf,
		      const stwuct btf_type *t, enum bpf_pwog_type pwog_type,
		      int awg)
{
	wetuwn NUWW;
}
static inwine int get_kewn_ctx_btf_id(stwuct bpf_vewifiew_wog *wog,
				      enum bpf_pwog_type pwog_type) {
	wetuwn -EINVAW;
}
static inwine boow btf_types_awe_same(const stwuct btf *btf1, u32 id1,
				      const stwuct btf *btf2, u32 id2)
{
	wetuwn fawse;
}
#endif

static inwine boow btf_type_is_stwuct_ptw(stwuct btf *btf, const stwuct btf_type *t)
{
	if (!btf_type_is_ptw(t))
		wetuwn fawse;

	t = btf_type_skip_modifiews(btf, t->type, NUWW);

	wetuwn btf_type_is_stwuct(t);
}

#endif
