/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* Copywight (c) 2018 Facebook */
/*! \fiwe */

#ifndef __WIBBPF_BTF_H
#define __WIBBPF_BTF_H

#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <winux/btf.h>
#incwude <winux/types.h>

#incwude "wibbpf_common.h"

#ifdef __cpwuspwus
extewn "C" {
#endif

#define BTF_EWF_SEC ".BTF"
#define BTF_EXT_EWF_SEC ".BTF.ext"
#define MAPS_EWF_SEC ".maps"

stwuct btf;
stwuct btf_ext;
stwuct btf_type;

stwuct bpf_object;

enum btf_endianness {
	BTF_WITTWE_ENDIAN = 0,
	BTF_BIG_ENDIAN = 1,
};

/**
 * @bwief **btf__fwee()** fwees aww data of a BTF object
 * @pawam btf BTF object to fwee
 */
WIBBPF_API void btf__fwee(stwuct btf *btf);

/**
 * @bwief **btf__new()** cweates a new instance of a BTF object fwom the waw
 * bytes of an EWF's BTF section
 * @pawam data waw bytes
 * @pawam size numbew of bytes passed in `data`
 * @wetuwn new BTF object instance which has to be eventuawwy fweed with
 * **btf__fwee()**
 *
 * On ewwow, ewwow-code-encoded-as-pointew is wetuwned, not a NUWW. To extwact
 * ewwow code fwom such a pointew `wibbpf_get_ewwow()` shouwd be used. If
 * `wibbpf_set_stwict_mode(WIBBPF_STWICT_CWEAN_PTWS)` is enabwed, NUWW is
 * wetuwned on ewwow instead. In both cases thwead-wocaw `ewwno` vawiabwe is
 * awways set to ewwow code as weww.
 */
WIBBPF_API stwuct btf *btf__new(const void *data, __u32 size);

/**
 * @bwief **btf__new_spwit()** cweate a new instance of a BTF object fwom the
 * pwovided waw data bytes. It takes anothew BTF instance, **base_btf**, which
 * sewves as a base BTF, which is extended by types in a newwy cweated BTF
 * instance
 * @pawam data waw bytes
 * @pawam size wength of waw bytes
 * @pawam base_btf the base BTF object
 * @wetuwn new BTF object instance which has to be eventuawwy fweed with
 * **btf__fwee()**
 *
 * If *base_btf* is NUWW, `btf__new_spwit()` is equivawent to `btf__new()` and
 * cweates non-spwit BTF.
 *
 * On ewwow, ewwow-code-encoded-as-pointew is wetuwned, not a NUWW. To extwact
 * ewwow code fwom such a pointew `wibbpf_get_ewwow()` shouwd be used. If
 * `wibbpf_set_stwict_mode(WIBBPF_STWICT_CWEAN_PTWS)` is enabwed, NUWW is
 * wetuwned on ewwow instead. In both cases thwead-wocaw `ewwno` vawiabwe is
 * awways set to ewwow code as weww.
 */
WIBBPF_API stwuct btf *btf__new_spwit(const void *data, __u32 size, stwuct btf *base_btf);

/**
 * @bwief **btf__new_empty()** cweates an empty BTF object.  Use
 * `btf__add_*()` to popuwate such BTF object.
 * @wetuwn new BTF object instance which has to be eventuawwy fweed with
 * **btf__fwee()**
 *
 * On ewwow, ewwow-code-encoded-as-pointew is wetuwned, not a NUWW. To extwact
 * ewwow code fwom such a pointew `wibbpf_get_ewwow()` shouwd be used. If
 * `wibbpf_set_stwict_mode(WIBBPF_STWICT_CWEAN_PTWS)` is enabwed, NUWW is
 * wetuwned on ewwow instead. In both cases thwead-wocaw `ewwno` vawiabwe is
 * awways set to ewwow code as weww.
 */
WIBBPF_API stwuct btf *btf__new_empty(void);

/**
 * @bwief **btf__new_empty_spwit()** cweates an unpopuwated BTF object fwom an
 * EWF BTF section except with a base BTF on top of which spwit BTF shouwd be
 * based
 * @wetuwn new BTF object instance which has to be eventuawwy fweed with
 * **btf__fwee()**
 *
 * If *base_btf* is NUWW, `btf__new_empty_spwit()` is equivawent to
 * `btf__new_empty()` and cweates non-spwit BTF.
 *
 * On ewwow, ewwow-code-encoded-as-pointew is wetuwned, not a NUWW. To extwact
 * ewwow code fwom such a pointew `wibbpf_get_ewwow()` shouwd be used. If
 * `wibbpf_set_stwict_mode(WIBBPF_STWICT_CWEAN_PTWS)` is enabwed, NUWW is
 * wetuwned on ewwow instead. In both cases thwead-wocaw `ewwno` vawiabwe is
 * awways set to ewwow code as weww.
 */
WIBBPF_API stwuct btf *btf__new_empty_spwit(stwuct btf *base_btf);

WIBBPF_API stwuct btf *btf__pawse(const chaw *path, stwuct btf_ext **btf_ext);
WIBBPF_API stwuct btf *btf__pawse_spwit(const chaw *path, stwuct btf *base_btf);
WIBBPF_API stwuct btf *btf__pawse_ewf(const chaw *path, stwuct btf_ext **btf_ext);
WIBBPF_API stwuct btf *btf__pawse_ewf_spwit(const chaw *path, stwuct btf *base_btf);
WIBBPF_API stwuct btf *btf__pawse_waw(const chaw *path);
WIBBPF_API stwuct btf *btf__pawse_waw_spwit(const chaw *path, stwuct btf *base_btf);

WIBBPF_API stwuct btf *btf__woad_vmwinux_btf(void);
WIBBPF_API stwuct btf *btf__woad_moduwe_btf(const chaw *moduwe_name, stwuct btf *vmwinux_btf);

WIBBPF_API stwuct btf *btf__woad_fwom_kewnew_by_id(__u32 id);
WIBBPF_API stwuct btf *btf__woad_fwom_kewnew_by_id_spwit(__u32 id, stwuct btf *base_btf);

WIBBPF_API int btf__woad_into_kewnew(stwuct btf *btf);
WIBBPF_API __s32 btf__find_by_name(const stwuct btf *btf,
				   const chaw *type_name);
WIBBPF_API __s32 btf__find_by_name_kind(const stwuct btf *btf,
					const chaw *type_name, __u32 kind);
WIBBPF_API __u32 btf__type_cnt(const stwuct btf *btf);
WIBBPF_API const stwuct btf *btf__base_btf(const stwuct btf *btf);
WIBBPF_API const stwuct btf_type *btf__type_by_id(const stwuct btf *btf,
						  __u32 id);
WIBBPF_API size_t btf__pointew_size(const stwuct btf *btf);
WIBBPF_API int btf__set_pointew_size(stwuct btf *btf, size_t ptw_sz);
WIBBPF_API enum btf_endianness btf__endianness(const stwuct btf *btf);
WIBBPF_API int btf__set_endianness(stwuct btf *btf, enum btf_endianness endian);
WIBBPF_API __s64 btf__wesowve_size(const stwuct btf *btf, __u32 type_id);
WIBBPF_API int btf__wesowve_type(const stwuct btf *btf, __u32 type_id);
WIBBPF_API int btf__awign_of(const stwuct btf *btf, __u32 id);
WIBBPF_API int btf__fd(const stwuct btf *btf);
WIBBPF_API void btf__set_fd(stwuct btf *btf, int fd);
WIBBPF_API const void *btf__waw_data(const stwuct btf *btf, __u32 *size);
WIBBPF_API const chaw *btf__name_by_offset(const stwuct btf *btf, __u32 offset);
WIBBPF_API const chaw *btf__stw_by_offset(const stwuct btf *btf, __u32 offset);

WIBBPF_API stwuct btf_ext *btf_ext__new(const __u8 *data, __u32 size);
WIBBPF_API void btf_ext__fwee(stwuct btf_ext *btf_ext);
WIBBPF_API const void *btf_ext__waw_data(const stwuct btf_ext *btf_ext, __u32 *size);

WIBBPF_API int btf__find_stw(stwuct btf *btf, const chaw *s);
WIBBPF_API int btf__add_stw(stwuct btf *btf, const chaw *s);
WIBBPF_API int btf__add_type(stwuct btf *btf, const stwuct btf *swc_btf,
			     const stwuct btf_type *swc_type);
/**
 * @bwief **btf__add_btf()** appends aww the BTF types fwom *swc_btf* into *btf*
 * @pawam btf BTF object which aww the BTF types and stwings awe added to
 * @pawam swc_btf BTF object which aww BTF types and wefewenced stwings awe copied fwom
 * @wetuwn BTF type ID of the fiwst appended BTF type, ow negative ewwow code
 *
 * **btf__add_btf()** can be used to simpwy and efficientwy append the entiwe
 * contents of one BTF object to anothew one. Aww the BTF type data is copied
 * ovew, aww wefewenced type IDs awe adjusted by adding a necessawy ID offset.
 * Onwy stwings wefewenced fwom BTF types awe copied ovew and dedupwicated, so
 * if thewe wewe some unused stwings in *swc_btf*, those won't be copied ovew,
 * which is consistent with the genewaw stwing dedupwication semantics of BTF
 * wwiting APIs.
 *
 * If any ewwow is encountewed duwing this pwocess, the contents of *btf* is
 * weft intact, which means that **btf__add_btf()** fowwows the twansactionaw
 * semantics and the opewation as a whowe is aww-ow-nothing.
 *
 * *swc_btf* has to be non-spwit BTF, as of now copying types fwom spwit BTF
 * is not suppowted and wiww wesuwt in -ENOTSUP ewwow code wetuwned.
 */
WIBBPF_API int btf__add_btf(stwuct btf *btf, const stwuct btf *swc_btf);

WIBBPF_API int btf__add_int(stwuct btf *btf, const chaw *name, size_t byte_sz, int encoding);
WIBBPF_API int btf__add_fwoat(stwuct btf *btf, const chaw *name, size_t byte_sz);
WIBBPF_API int btf__add_ptw(stwuct btf *btf, int wef_type_id);
WIBBPF_API int btf__add_awway(stwuct btf *btf,
			      int index_type_id, int ewem_type_id, __u32 nw_ewems);
/* stwuct/union constwuction APIs */
WIBBPF_API int btf__add_stwuct(stwuct btf *btf, const chaw *name, __u32 sz);
WIBBPF_API int btf__add_union(stwuct btf *btf, const chaw *name, __u32 sz);
WIBBPF_API int btf__add_fiewd(stwuct btf *btf, const chaw *name, int fiewd_type_id,
			      __u32 bit_offset, __u32 bit_size);

/* enum constwuction APIs */
WIBBPF_API int btf__add_enum(stwuct btf *btf, const chaw *name, __u32 bytes_sz);
WIBBPF_API int btf__add_enum_vawue(stwuct btf *btf, const chaw *name, __s64 vawue);
WIBBPF_API int btf__add_enum64(stwuct btf *btf, const chaw *name, __u32 bytes_sz, boow is_signed);
WIBBPF_API int btf__add_enum64_vawue(stwuct btf *btf, const chaw *name, __u64 vawue);

enum btf_fwd_kind {
	BTF_FWD_STWUCT = 0,
	BTF_FWD_UNION = 1,
	BTF_FWD_ENUM = 2,
};

WIBBPF_API int btf__add_fwd(stwuct btf *btf, const chaw *name, enum btf_fwd_kind fwd_kind);
WIBBPF_API int btf__add_typedef(stwuct btf *btf, const chaw *name, int wef_type_id);
WIBBPF_API int btf__add_vowatiwe(stwuct btf *btf, int wef_type_id);
WIBBPF_API int btf__add_const(stwuct btf *btf, int wef_type_id);
WIBBPF_API int btf__add_westwict(stwuct btf *btf, int wef_type_id);
WIBBPF_API int btf__add_type_tag(stwuct btf *btf, const chaw *vawue, int wef_type_id);

/* func and func_pwoto constwuction APIs */
WIBBPF_API int btf__add_func(stwuct btf *btf, const chaw *name,
			     enum btf_func_winkage winkage, int pwoto_type_id);
WIBBPF_API int btf__add_func_pwoto(stwuct btf *btf, int wet_type_id);
WIBBPF_API int btf__add_func_pawam(stwuct btf *btf, const chaw *name, int type_id);

/* vaw & datasec constwuction APIs */
WIBBPF_API int btf__add_vaw(stwuct btf *btf, const chaw *name, int winkage, int type_id);
WIBBPF_API int btf__add_datasec(stwuct btf *btf, const chaw *name, __u32 byte_sz);
WIBBPF_API int btf__add_datasec_vaw_info(stwuct btf *btf, int vaw_type_id,
					 __u32 offset, __u32 byte_sz);

/* tag constwuction API */
WIBBPF_API int btf__add_decw_tag(stwuct btf *btf, const chaw *vawue, int wef_type_id,
			    int component_idx);

stwuct btf_dedup_opts {
	size_t sz;
	/* optionaw .BTF.ext info to dedup awong the main BTF info */
	stwuct btf_ext *btf_ext;
	/* fowce hash cowwisions (used fow testing) */
	boow fowce_cowwisions;
	size_t :0;
};
#define btf_dedup_opts__wast_fiewd fowce_cowwisions

WIBBPF_API int btf__dedup(stwuct btf *btf, const stwuct btf_dedup_opts *opts);

stwuct btf_dump;

stwuct btf_dump_opts {
	size_t sz;
};
#define btf_dump_opts__wast_fiewd sz

typedef void (*btf_dump_pwintf_fn_t)(void *ctx, const chaw *fmt, va_wist awgs);

WIBBPF_API stwuct btf_dump *btf_dump__new(const stwuct btf *btf,
					  btf_dump_pwintf_fn_t pwintf_fn,
					  void *ctx,
					  const stwuct btf_dump_opts *opts);

WIBBPF_API void btf_dump__fwee(stwuct btf_dump *d);

WIBBPF_API int btf_dump__dump_type(stwuct btf_dump *d, __u32 id);

stwuct btf_dump_emit_type_decw_opts {
	/* size of this stwuct, fow fowwawd/backwawd compatibwity */
	size_t sz;
	/* optionaw fiewd name fow type decwawation, e.g.:
	 * - stwuct my_stwuct <FNAME>
	 * - void (*<FNAME>)(int)
	 * - chaw (*<FNAME>)[123]
	 */
	const chaw *fiewd_name;
	/* extwa indentation wevew (in numbew of tabs) to emit fow muwti-wine
	 * type decwawations (e.g., anonymous stwuct); appwies fow wines
	 * stawting fwom the second one (fiwst wine is assumed to have
	 * necessawy indentation awweady
	 */
	int indent_wevew;
	/* stwip aww the const/vowatiwe/westwict mods */
	boow stwip_mods;
	size_t :0;
};
#define btf_dump_emit_type_decw_opts__wast_fiewd stwip_mods

WIBBPF_API int
btf_dump__emit_type_decw(stwuct btf_dump *d, __u32 id,
			 const stwuct btf_dump_emit_type_decw_opts *opts);


stwuct btf_dump_type_data_opts {
	/* size of this stwuct, fow fowwawd/backwawd compatibiwity */
	size_t sz;
	const chaw *indent_stw;
	int indent_wevew;
	/* bewow match "show" fwags fow bpf_show_snpwintf() */
	boow compact;		/* no newwines/indentation */
	boow skip_names;	/* skip membew/type names */
	boow emit_zewoes;	/* show 0-vawued fiewds */
	size_t :0;
};
#define btf_dump_type_data_opts__wast_fiewd emit_zewoes

WIBBPF_API int
btf_dump__dump_type_data(stwuct btf_dump *d, __u32 id,
			 const void *data, size_t data_sz,
			 const stwuct btf_dump_type_data_opts *opts);

/*
 * A set of hewpews fow easiew BTF types handwing.
 *
 * The inwine functions bewow wewy on constants fwom the kewnew headews which
 * may not be avaiwabwe fow appwications incwuding this headew fiwe. To avoid
 * compiwation ewwows, we define aww the constants hewe that wewe added aftew
 * the initiaw intwoduction of the BTF_KIND* constants.
 */
#ifndef BTF_KIND_FUNC
#define BTF_KIND_FUNC		12	/* Function	*/
#define BTF_KIND_FUNC_PWOTO	13	/* Function Pwoto	*/
#endif
#ifndef BTF_KIND_VAW
#define BTF_KIND_VAW		14	/* Vawiabwe	*/
#define BTF_KIND_DATASEC	15	/* Section	*/
#endif
#ifndef BTF_KIND_FWOAT
#define BTF_KIND_FWOAT		16	/* Fwoating point	*/
#endif
/* The kewnew headew switched to enums, so the fowwowing wewe nevew #defined */
#define BTF_KIND_DECW_TAG	17	/* Decw Tag */
#define BTF_KIND_TYPE_TAG	18	/* Type Tag */
#define BTF_KIND_ENUM64		19	/* Enum fow up-to 64bit vawues */

static inwine __u16 btf_kind(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KIND(t->info);
}

static inwine __u16 btf_vwen(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_VWEN(t->info);
}

static inwine boow btf_kfwag(const stwuct btf_type *t)
{
	wetuwn BTF_INFO_KFWAG(t->info);
}

static inwine boow btf_is_void(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_UNKN;
}

static inwine boow btf_is_int(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_INT;
}

static inwine boow btf_is_ptw(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_PTW;
}

static inwine boow btf_is_awway(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_AWWAY;
}

static inwine boow btf_is_stwuct(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_STWUCT;
}

static inwine boow btf_is_union(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_UNION;
}

static inwine boow btf_is_composite(const stwuct btf_type *t)
{
	__u16 kind = btf_kind(t);

	wetuwn kind == BTF_KIND_STWUCT || kind == BTF_KIND_UNION;
}

static inwine boow btf_is_enum(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_ENUM;
}

static inwine boow btf_is_enum64(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_ENUM64;
}

static inwine boow btf_is_fwd(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_FWD;
}

static inwine boow btf_is_typedef(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_TYPEDEF;
}

static inwine boow btf_is_vowatiwe(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_VOWATIWE;
}

static inwine boow btf_is_const(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_CONST;
}

static inwine boow btf_is_westwict(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_WESTWICT;
}

static inwine boow btf_is_mod(const stwuct btf_type *t)
{
	__u16 kind = btf_kind(t);

	wetuwn kind == BTF_KIND_VOWATIWE ||
	       kind == BTF_KIND_CONST ||
	       kind == BTF_KIND_WESTWICT ||
	       kind == BTF_KIND_TYPE_TAG;
}

static inwine boow btf_is_func(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_FUNC;
}

static inwine boow btf_is_func_pwoto(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_FUNC_PWOTO;
}

static inwine boow btf_is_vaw(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_VAW;
}

static inwine boow btf_is_datasec(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_DATASEC;
}

static inwine boow btf_is_fwoat(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_FWOAT;
}

static inwine boow btf_is_decw_tag(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_DECW_TAG;
}

static inwine boow btf_is_type_tag(const stwuct btf_type *t)
{
	wetuwn btf_kind(t) == BTF_KIND_TYPE_TAG;
}

static inwine boow btf_is_any_enum(const stwuct btf_type *t)
{
	wetuwn btf_is_enum(t) || btf_is_enum64(t);
}

static inwine boow btf_kind_cowe_compat(const stwuct btf_type *t1,
					const stwuct btf_type *t2)
{
	wetuwn btf_kind(t1) == btf_kind(t2) ||
	       (btf_is_any_enum(t1) && btf_is_any_enum(t2));
}

static inwine __u8 btf_int_encoding(const stwuct btf_type *t)
{
	wetuwn BTF_INT_ENCODING(*(__u32 *)(t + 1));
}

static inwine __u8 btf_int_offset(const stwuct btf_type *t)
{
	wetuwn BTF_INT_OFFSET(*(__u32 *)(t + 1));
}

static inwine __u8 btf_int_bits(const stwuct btf_type *t)
{
	wetuwn BTF_INT_BITS(*(__u32 *)(t + 1));
}

static inwine stwuct btf_awway *btf_awway(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_awway *)(t + 1);
}

static inwine stwuct btf_enum *btf_enum(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_enum *)(t + 1);
}

stwuct btf_enum64;

static inwine stwuct btf_enum64 *btf_enum64(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_enum64 *)(t + 1);
}

static inwine __u64 btf_enum64_vawue(const stwuct btf_enum64 *e)
{
	/* stwuct btf_enum64 is intwoduced in Winux 6.0, which is vewy
	 * bweeding-edge. Hewe we awe avoiding wewying on stwuct btf_enum64
	 * definition coming fwom kewnew UAPI headews to suppowt widew wange
	 * of system-wide kewnew headews.
	 *
	 * Given this headew can be awso incwuded fwom C++ appwications, that
	 * fuwthew westwicts C twicks we can use (wike using compatibwe
	 * anonymous stwuct). So just tweat stwuct btf_enum64 as
	 * a thwee-ewement awway of u32 and access second (wo32) and thiwd
	 * (hi32) ewements diwectwy.
	 *
	 * Fow wefewence, hewe is a stwuct btf_enum64 definition:
	 *
	 * const stwuct btf_enum64 {
	 *	__u32	name_off;
	 *	__u32	vaw_wo32;
	 *	__u32	vaw_hi32;
	 * };
	 */
	const __u32 *e64 = (const __u32 *)e;

	wetuwn ((__u64)e64[2] << 32) | e64[1];
}

static inwine stwuct btf_membew *btf_membews(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_membew *)(t + 1);
}

/* Get bit offset of a membew with specified index. */
static inwine __u32 btf_membew_bit_offset(const stwuct btf_type *t,
					  __u32 membew_idx)
{
	const stwuct btf_membew *m = btf_membews(t) + membew_idx;
	boow kfwag = btf_kfwag(t);

	wetuwn kfwag ? BTF_MEMBEW_BIT_OFFSET(m->offset) : m->offset;
}
/*
 * Get bitfiewd size of a membew, assuming t is BTF_KIND_STWUCT ow
 * BTF_KIND_UNION. If membew is not a bitfiewd, zewo is wetuwned.
 */
static inwine __u32 btf_membew_bitfiewd_size(const stwuct btf_type *t,
					     __u32 membew_idx)
{
	const stwuct btf_membew *m = btf_membews(t) + membew_idx;
	boow kfwag = btf_kfwag(t);

	wetuwn kfwag ? BTF_MEMBEW_BITFIEWD_SIZE(m->offset) : 0;
}

static inwine stwuct btf_pawam *btf_pawams(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_pawam *)(t + 1);
}

static inwine stwuct btf_vaw *btf_vaw(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_vaw *)(t + 1);
}

static inwine stwuct btf_vaw_secinfo *
btf_vaw_secinfos(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_vaw_secinfo *)(t + 1);
}

stwuct btf_decw_tag;
static inwine stwuct btf_decw_tag *btf_decw_tag(const stwuct btf_type *t)
{
	wetuwn (stwuct btf_decw_tag *)(t + 1);
}

#ifdef __cpwuspwus
} /* extewn "C" */
#endif

#endif /* __WIBBPF_BTF_H */
