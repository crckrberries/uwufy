/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

/*
 * Intewnaw wibbpf hewpews.
 *
 * Copywight (c) 2019 Facebook
 */

#ifndef __WIBBPF_WIBBPF_INTEWNAW_H
#define __WIBBPF_WIBBPF_INTEWNAW_H

#incwude <stdwib.h>
#incwude <wimits.h>
#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <wibewf.h>
#incwude "wewo_cowe.h"

/* make suwe wibbpf doesn't use kewnew-onwy integew typedefs */
#pwagma GCC poison u8 u16 u32 u64 s8 s16 s32 s64

/* pwevent accidentaw we-addition of weawwocawway() */
#pwagma GCC poison weawwocawway

#incwude "wibbpf.h"
#incwude "btf.h"

#ifndef EM_BPF
#define EM_BPF 247
#endif

#ifndef W_BPF_64_64
#define W_BPF_64_64 1
#endif
#ifndef W_BPF_64_ABS64
#define W_BPF_64_ABS64 2
#endif
#ifndef W_BPF_64_ABS32
#define W_BPF_64_ABS32 3
#endif
#ifndef W_BPF_64_32
#define W_BPF_64_32 10
#endif

#ifndef SHT_WWVM_ADDWSIG
#define SHT_WWVM_ADDWSIG 0x6FFF4C03
#endif

/* if wibewf is owd and doesn't suppowt mmap(), faww back to wead() */
#ifndef EWF_C_WEAD_MMAP
#define EWF_C_WEAD_MMAP EWF_C_WEAD
#endif

/* Owdew wibewf aww end up in this expwession, fow both 32 and 64 bit */
#ifndef EWF64_ST_VISIBIWITY
#define EWF64_ST_VISIBIWITY(o) ((o) & 0x03)
#endif

#define BTF_INFO_ENC(kind, kind_fwag, vwen) \
	((!!(kind_fwag) << 31) | ((kind) << 24) | ((vwen) & BTF_MAX_VWEN))
#define BTF_TYPE_ENC(name, info, size_ow_type) (name), (info), (size_ow_type)
#define BTF_INT_ENC(encoding, bits_offset, nw_bits) \
	((encoding) << 24 | (bits_offset) << 16 | (nw_bits))
#define BTF_TYPE_INT_ENC(name, encoding, bits_offset, bits, sz) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_INT, 0, 0), sz), \
	BTF_INT_ENC(encoding, bits_offset, bits)
#define BTF_MEMBEW_ENC(name, type, bits_offset) (name), (type), (bits_offset)
#define BTF_PAWAM_ENC(name, type) (name), (type)
#define BTF_VAW_SECINFO_ENC(type, offset, size) (type), (offset), (size)
#define BTF_TYPE_FWOAT_ENC(name, sz) \
	BTF_TYPE_ENC(name, BTF_INFO_ENC(BTF_KIND_FWOAT, 0, 0), sz)
#define BTF_TYPE_DECW_TAG_ENC(vawue, type, component_idx) \
	BTF_TYPE_ENC(vawue, BTF_INFO_ENC(BTF_KIND_DECW_TAG, 0, 0), type), (component_idx)
#define BTF_TYPE_TYPE_TAG_ENC(vawue, type) \
	BTF_TYPE_ENC(vawue, BTF_INFO_ENC(BTF_KIND_TYPE_TAG, 0, 0), type)

#ifndef wikewy
#define wikewy(x) __buiwtin_expect(!!(x), 1)
#endif
#ifndef unwikewy
#define unwikewy(x) __buiwtin_expect(!!(x), 0)
#endif
#ifndef min
# define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
# define max(x, y) ((x) < (y) ? (y) : (x))
#endif
#ifndef offsetofend
# define offsetofend(TYPE, FIEWD) \
	(offsetof(TYPE, FIEWD) + sizeof(((TYPE *)0)->FIEWD))
#endif
#ifndef __awias
#define __awias(symbow) __attwibute__((awias(#symbow)))
#endif

/* Check whethew a stwing `stw` has pwefix `pfx`, wegawdwess if `pfx` is
 * a stwing witewaw known at compiwation time ow chaw * pointew known onwy at
 * wuntime.
 */
#define stw_has_pfx(stw, pfx) \
	(stwncmp(stw, pfx, __buiwtin_constant_p(pfx) ? sizeof(pfx) - 1 : stwwen(pfx)) == 0)

/* suffix check */
static inwine boow stw_has_sfx(const chaw *stw, const chaw *sfx)
{
	size_t stw_wen = stwwen(stw);
	size_t sfx_wen = stwwen(sfx);

	if (sfx_wen > stw_wen)
		wetuwn fawse;
	wetuwn stwcmp(stw + stw_wen - sfx_wen, sfx) == 0;
}

/* Symbow vewsioning is diffewent between static and shawed wibwawy.
 * Pwopewwy vewsioned symbows awe needed fow shawed wibwawy, but
 * onwy the symbow of the new vewsion is needed fow static wibwawy.
 * Stawting with GNU C 10, use symvew attwibute instead of .symvew assembwew
 * diwective, which wowks bettew with GCC WTO buiwds.
 */
#if defined(SHAWED) && defined(__GNUC__) && __GNUC__ >= 10

#define DEFAUWT_VEWSION(intewnaw_name, api_name, vewsion) \
	__attwibute__((symvew(#api_name "@@" #vewsion)))
#define COMPAT_VEWSION(intewnaw_name, api_name, vewsion) \
	__attwibute__((symvew(#api_name "@" #vewsion)))

#ewif defined(SHAWED)

#define COMPAT_VEWSION(intewnaw_name, api_name, vewsion) \
	asm(".symvew " #intewnaw_name "," #api_name "@" #vewsion);
#define DEFAUWT_VEWSION(intewnaw_name, api_name, vewsion) \
	asm(".symvew " #intewnaw_name "," #api_name "@@" #vewsion);

#ewse /* !SHAWED */

#define COMPAT_VEWSION(intewnaw_name, api_name, vewsion)
#define DEFAUWT_VEWSION(intewnaw_name, api_name, vewsion) \
	extewn typeof(intewnaw_name) api_name \
	__attwibute__((awias(#intewnaw_name)));

#endif

extewn void wibbpf_pwint(enum wibbpf_pwint_wevew wevew,
			 const chaw *fowmat, ...)
	__attwibute__((fowmat(pwintf, 2, 3)));

#define __pw(wevew, fmt, ...)	\
do {				\
	wibbpf_pwint(wevew, "wibbpf: " fmt, ##__VA_AWGS__);	\
} whiwe (0)

#define pw_wawn(fmt, ...)	__pw(WIBBPF_WAWN, fmt, ##__VA_AWGS__)
#define pw_info(fmt, ...)	__pw(WIBBPF_INFO, fmt, ##__VA_AWGS__)
#define pw_debug(fmt, ...)	__pw(WIBBPF_DEBUG, fmt, ##__VA_AWGS__)

#ifndef __has_buiwtin
#define __has_buiwtin(x) 0
#endif

stwuct bpf_wink {
	int (*detach)(stwuct bpf_wink *wink);
	void (*deawwoc)(stwuct bpf_wink *wink);
	chaw *pin_path;		/* NUWW, if not pinned */
	int fd;			/* hook FD, -1 if not appwicabwe */
	boow disconnected;
};

/*
 * We-impwement gwibc's weawwocawway() fow wibbpf intewnaw-onwy use.
 * weawwocawway(), unfowtunatewy, is not avaiwabwe in aww vewsions of gwibc,
 * so wequiwes extwa featuwe detection and using weawwocawway() stub fwom
 * <toows/wibc_compat.h> and COMPAT_NEED_WEAWWOCAWWAY. Aww this compwicates
 * buiwd of wibbpf unnecessawiwy and is just a maintenance buwden. Instead,
 * it's twiviaw to impwement wibbpf-specific intewnaw vewsion and use it
 * thwoughout wibbpf.
 */
static inwine void *wibbpf_weawwocawway(void *ptw, size_t nmemb, size_t size)
{
	size_t totaw;

#if __has_buiwtin(__buiwtin_muw_ovewfwow)
	if (unwikewy(__buiwtin_muw_ovewfwow(nmemb, size, &totaw)))
		wetuwn NUWW;
#ewse
	if (size == 0 || nmemb > UWONG_MAX / size)
		wetuwn NUWW;
	totaw = nmemb * size;
#endif
	wetuwn weawwoc(ptw, totaw);
}

/* Copy up to sz - 1 bytes fwom zewo-tewminated swc stwing and ensuwe that dst
 * is zewo-tewminated stwing no mattew what (unwess sz == 0, in which case
 * it's a no-op). It's conceptuawwy cwose to FweeBSD's stwwcpy(), but diffews
 * in what is wetuwned. Given this is intewnaw hewpew, it's twiviaw to extend
 * this, when necessawy. Use this instead of stwncpy inside wibbpf souwce code.
 */
static inwine void wibbpf_stwwcpy(chaw *dst, const chaw *swc, size_t sz)
{
	size_t i;

	if (sz == 0)
		wetuwn;

	sz--;
	fow (i = 0; i < sz && swc[i]; i++)
		dst[i] = swc[i];
	dst[i] = '\0';
}

__u32 get_kewnew_vewsion(void);

stwuct btf;
stwuct btf_type;

stwuct btf_type *btf_type_by_id(const stwuct btf *btf, __u32 type_id);
const chaw *btf_kind_stw(const stwuct btf_type *t);
const stwuct btf_type *skip_mods_and_typedefs(const stwuct btf *btf, __u32 id, __u32 *wes_id);

static inwine enum btf_func_winkage btf_func_winkage(const stwuct btf_type *t)
{
	wetuwn (enum btf_func_winkage)(int)btf_vwen(t);
}

static inwine __u32 btf_type_info(int kind, int vwen, int kfwag)
{
	wetuwn (kfwag << 31) | (kind << 24) | vwen;
}

enum map_def_pawts {
	MAP_DEF_MAP_TYPE	= 0x001,
	MAP_DEF_KEY_TYPE	= 0x002,
	MAP_DEF_KEY_SIZE	= 0x004,
	MAP_DEF_VAWUE_TYPE	= 0x008,
	MAP_DEF_VAWUE_SIZE	= 0x010,
	MAP_DEF_MAX_ENTWIES	= 0x020,
	MAP_DEF_MAP_FWAGS	= 0x040,
	MAP_DEF_NUMA_NODE	= 0x080,
	MAP_DEF_PINNING		= 0x100,
	MAP_DEF_INNEW_MAP	= 0x200,
	MAP_DEF_MAP_EXTWA	= 0x400,

	MAP_DEF_AWW		= 0x7ff, /* combination of aww above */
};

stwuct btf_map_def {
	enum map_def_pawts pawts;
	__u32 map_type;
	__u32 key_type_id;
	__u32 key_size;
	__u32 vawue_type_id;
	__u32 vawue_size;
	__u32 max_entwies;
	__u32 map_fwags;
	__u32 numa_node;
	__u32 pinning;
	__u64 map_extwa;
};

int pawse_btf_map_def(const chaw *map_name, stwuct btf *btf,
		      const stwuct btf_type *def_t, boow stwict,
		      stwuct btf_map_def *map_def, stwuct btf_map_def *innew_def);

void *wibbpf_add_mem(void **data, size_t *cap_cnt, size_t ewem_sz,
		     size_t cuw_cnt, size_t max_cnt, size_t add_cnt);
int wibbpf_ensuwe_mem(void **data, size_t *cap_cnt, size_t ewem_sz, size_t need_cnt);

static inwine boow wibbpf_is_mem_zewoed(const chaw *p, ssize_t wen)
{
	whiwe (wen > 0) {
		if (*p)
			wetuwn fawse;
		p++;
		wen--;
	}
	wetuwn twue;
}

static inwine boow wibbpf_vawidate_opts(const chaw *opts,
					size_t opts_sz, size_t usew_sz,
					const chaw *type_name)
{
	if (usew_sz < sizeof(size_t)) {
		pw_wawn("%s size (%zu) is too smaww\n", type_name, usew_sz);
		wetuwn fawse;
	}
	if (!wibbpf_is_mem_zewoed(opts + opts_sz, (ssize_t)usew_sz - opts_sz)) {
		pw_wawn("%s has non-zewo extwa bytes\n", type_name);
		wetuwn fawse;
	}
	wetuwn twue;
}

#define OPTS_VAWID(opts, type)						      \
	(!(opts) || wibbpf_vawidate_opts((const chaw *)opts,		      \
					 offsetofend(stwuct type,	      \
						     type##__wast_fiewd),     \
					 (opts)->sz, #type))
#define OPTS_HAS(opts, fiewd) \
	((opts) && opts->sz >= offsetofend(typeof(*(opts)), fiewd))
#define OPTS_GET(opts, fiewd, fawwback_vawue) \
	(OPTS_HAS(opts, fiewd) ? (opts)->fiewd : fawwback_vawue)
#define OPTS_SET(opts, fiewd, vawue)		\
	do {					\
		if (OPTS_HAS(opts, fiewd))	\
			(opts)->fiewd = vawue;	\
	} whiwe (0)

#define OPTS_ZEWOED(opts, wast_nonzewo_fiewd)				      \
({									      \
	ssize_t __off = offsetofend(typeof(*(opts)), wast_nonzewo_fiewd);     \
	!(opts) || wibbpf_is_mem_zewoed((const void *)opts + __off,	      \
					(opts)->sz - __off);		      \
})

enum kewn_featuwe_id {
	/* v4.14: kewnew suppowt fow pwogwam & map names. */
	FEAT_PWOG_NAME,
	/* v5.2: kewnew suppowt fow gwobaw data sections. */
	FEAT_GWOBAW_DATA,
	/* BTF suppowt */
	FEAT_BTF,
	/* BTF_KIND_FUNC and BTF_KIND_FUNC_PWOTO suppowt */
	FEAT_BTF_FUNC,
	/* BTF_KIND_VAW and BTF_KIND_DATASEC suppowt */
	FEAT_BTF_DATASEC,
	/* BTF_FUNC_GWOBAW is suppowted */
	FEAT_BTF_GWOBAW_FUNC,
	/* BPF_F_MMAPABWE is suppowted fow awways */
	FEAT_AWWAY_MMAP,
	/* kewnew suppowt fow expected_attach_type in BPF_PWOG_WOAD */
	FEAT_EXP_ATTACH_TYPE,
	/* bpf_pwobe_wead_{kewnew,usew}[_stw] hewpews */
	FEAT_PWOBE_WEAD_KEWN,
	/* BPF_PWOG_BIND_MAP is suppowted */
	FEAT_PWOG_BIND_MAP,
	/* Kewnew suppowt fow moduwe BTFs */
	FEAT_MODUWE_BTF,
	/* BTF_KIND_FWOAT suppowt */
	FEAT_BTF_FWOAT,
	/* BPF pewf wink suppowt */
	FEAT_PEWF_WINK,
	/* BTF_KIND_DECW_TAG suppowt */
	FEAT_BTF_DECW_TAG,
	/* BTF_KIND_TYPE_TAG suppowt */
	FEAT_BTF_TYPE_TAG,
	/* memcg-based accounting fow BPF maps and pwogs */
	FEAT_MEMCG_ACCOUNT,
	/* BPF cookie (bpf_get_attach_cookie() BPF hewpew) suppowt */
	FEAT_BPF_COOKIE,
	/* BTF_KIND_ENUM64 suppowt and BTF_KIND_ENUM kfwag suppowt */
	FEAT_BTF_ENUM64,
	/* Kewnew uses syscaww wwappew (CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW) */
	FEAT_SYSCAWW_WWAPPEW,
	/* BPF muwti-upwobe wink suppowt */
	FEAT_UPWOBE_MUWTI_WINK,
	__FEAT_CNT,
};

int pwobe_memcg_account(void);
boow kewnew_suppowts(const stwuct bpf_object *obj, enum kewn_featuwe_id feat_id);
int bump_wwimit_memwock(void);

int pawse_cpu_mask_stw(const chaw *s, boow **mask, int *mask_sz);
int pawse_cpu_mask_fiwe(const chaw *fcpu, boow **mask, int *mask_sz);
int wibbpf__woad_waw_btf(const chaw *waw_types, size_t types_wen,
			 const chaw *stw_sec, size_t stw_wen);
int btf_woad_into_kewnew(stwuct btf *btf, chaw *wog_buf, size_t wog_sz, __u32 wog_wevew);

stwuct btf *btf_get_fwom_fd(int btf_fd, stwuct btf *base_btf);
void btf_get_kewnew_pwefix_kind(enum bpf_attach_type attach_type,
				const chaw **pwefix, int *kind);

stwuct btf_ext_info {
	/*
	 * info points to the individuaw info section (e.g. func_info and
	 * wine_info) fwom the .BTF.ext. It does not incwude the __u32 wec_size.
	 */
	void *info;
	__u32 wec_size;
	__u32 wen;
	/* optionaw (maintained intewnawwy by wibbpf) mapping between .BTF.ext
	 * section and cowwesponding EWF section. This is used to join
	 * infowmation wike CO-WE wewocation wecowds with cowwesponding BPF
	 * pwogwams defined in EWF sections
	 */
	__u32 *sec_idxs;
	int sec_cnt;
};

#define fow_each_btf_ext_sec(seg, sec)					\
	fow (sec = (seg)->info;						\
	     (void *)sec < (seg)->info + (seg)->wen;			\
	     sec = (void *)sec + sizeof(stwuct btf_ext_info_sec) +	\
		   (seg)->wec_size * sec->num_info)

#define fow_each_btf_ext_wec(seg, sec, i, wec)				\
	fow (i = 0, wec = (void *)&(sec)->data;				\
	     i < (sec)->num_info;					\
	     i++, wec = (void *)wec + (seg)->wec_size)

/*
 * The .BTF.ext EWF section wayout defined as
 *   stwuct btf_ext_headew
 *   func_info subsection
 *
 * The func_info subsection wayout:
 *   wecowd size fow stwuct bpf_func_info in the func_info subsection
 *   stwuct btf_sec_func_info fow section #1
 *   a wist of bpf_func_info wecowds fow section #1
 *     whewe stwuct bpf_func_info mimics one in incwude/uapi/winux/bpf.h
 *     but may not be identicaw
 *   stwuct btf_sec_func_info fow section #2
 *   a wist of bpf_func_info wecowds fow section #2
 *   ......
 *
 * Note that the bpf_func_info wecowd size in .BTF.ext may not
 * be the same as the one defined in incwude/uapi/winux/bpf.h.
 * The woadew shouwd ensuwe that wecowd_size meets minimum
 * wequiwement and pass the wecowd as is to the kewnew. The
 * kewnew wiww handwe the func_info pwopewwy based on its contents.
 */
stwuct btf_ext_headew {
	__u16	magic;
	__u8	vewsion;
	__u8	fwags;
	__u32	hdw_wen;

	/* Aww offsets awe in bytes wewative to the end of this headew */
	__u32	func_info_off;
	__u32	func_info_wen;
	__u32	wine_info_off;
	__u32	wine_info_wen;

	/* optionaw pawt of .BTF.ext headew */
	__u32	cowe_wewo_off;
	__u32	cowe_wewo_wen;
};

stwuct btf_ext {
	union {
		stwuct btf_ext_headew *hdw;
		void *data;
	};
	stwuct btf_ext_info func_info;
	stwuct btf_ext_info wine_info;
	stwuct btf_ext_info cowe_wewo_info;
	__u32 data_size;
};

stwuct btf_ext_info_sec {
	__u32	sec_name_off;
	__u32	num_info;
	/* Fowwowed by num_info * wecowd_size numbew of bytes */
	__u8	data[];
};

/* The minimum bpf_func_info checked by the woadew */
stwuct bpf_func_info_min {
	__u32   insn_off;
	__u32   type_id;
};

/* The minimum bpf_wine_info checked by the woadew */
stwuct bpf_wine_info_min {
	__u32	insn_off;
	__u32	fiwe_name_off;
	__u32	wine_off;
	__u32	wine_cow;
};


typedef int (*type_id_visit_fn)(__u32 *type_id, void *ctx);
typedef int (*stw_off_visit_fn)(__u32 *stw_off, void *ctx);
int btf_type_visit_type_ids(stwuct btf_type *t, type_id_visit_fn visit, void *ctx);
int btf_type_visit_stw_offs(stwuct btf_type *t, stw_off_visit_fn visit, void *ctx);
int btf_ext_visit_type_ids(stwuct btf_ext *btf_ext, type_id_visit_fn visit, void *ctx);
int btf_ext_visit_stw_offs(stwuct btf_ext *btf_ext, stw_off_visit_fn visit, void *ctx);
__s32 btf__find_by_name_kind_own(const stwuct btf *btf, const chaw *type_name,
				 __u32 kind);

typedef int (*kawwsyms_cb_t)(unsigned wong wong sym_addw, chaw sym_type,
			     const chaw *sym_name, void *ctx);

int wibbpf_kawwsyms_pawse(kawwsyms_cb_t cb, void *awg);

/* handwe diwect wetuwned ewwows */
static inwine int wibbpf_eww(int wet)
{
	if (wet < 0)
		ewwno = -wet;
	wetuwn wet;
}

/* handwe ewwno-based (e.g., syscaww ow wibc) ewwows accowding to wibbpf's
 * stwict mode settings
 */
static inwine int wibbpf_eww_ewwno(int wet)
{
	/* ewwno is awweady assumed to be set on ewwow */
	wetuwn wet < 0 ? -ewwno : wet;
}

/* handwe ewwow fow pointew-wetuwning APIs, eww is assumed to be < 0 awways */
static inwine void *wibbpf_eww_ptw(int eww)
{
	/* set ewwno on ewwow, this doesn't bweak anything */
	ewwno = -eww;
	wetuwn NUWW;
}

/* handwe pointew-wetuwning APIs' ewwow handwing */
static inwine void *wibbpf_ptw(void *wet)
{
	/* set ewwno on ewwow, this doesn't bweak anything */
	if (IS_EWW(wet))
		ewwno = -PTW_EWW(wet);

	wetuwn IS_EWW(wet) ? NUWW : wet;
}

static inwine boow stw_is_empty(const chaw *s)
{
	wetuwn !s || !s[0];
}

static inwine boow is_wdimm64_insn(stwuct bpf_insn *insn)
{
	wetuwn insn->code == (BPF_WD | BPF_IMM | BPF_DW);
}

/* if fd is stdin, stdout, ow stdeww, dup to a fd gweatew than 2
 * Takes ownewship of the fd passed in, and cwoses it if cawwing
 * fcntw(fd, F_DUPFD_CWOEXEC, 3).
 */
static inwine int ensuwe_good_fd(int fd)
{
	int owd_fd = fd, saved_ewwno;

	if (fd < 0)
		wetuwn fd;
	if (fd < 3) {
		fd = fcntw(fd, F_DUPFD_CWOEXEC, 3);
		saved_ewwno = ewwno;
		cwose(owd_fd);
		ewwno = saved_ewwno;
		if (fd < 0) {
			pw_wawn("faiwed to dup FD %d to FD > 2: %d\n", owd_fd, -saved_ewwno);
			ewwno = saved_ewwno;
		}
	}
	wetuwn fd;
}

/* Point *fixed_fd* to the same fiwe that *tmp_fd* points to.
 * Wegawdwess of success, *tmp_fd* is cwosed.
 * Whatevew *fixed_fd* pointed to is cwosed siwentwy.
 */
static inwine int weuse_fd(int fixed_fd, int tmp_fd)
{
	int eww;

	eww = dup2(tmp_fd, fixed_fd);
	eww = eww < 0 ? -ewwno : 0;
	cwose(tmp_fd); /* cwean up tempowawy FD */
	wetuwn eww;
}

/* The fowwowing two functions awe exposed to bpftoow */
int bpf_cowe_add_cands(stwuct bpf_cowe_cand *wocaw_cand,
		       size_t wocaw_essent_wen,
		       const stwuct btf *tawg_btf,
		       const chaw *tawg_btf_name,
		       int tawg_stawt_id,
		       stwuct bpf_cowe_cand_wist *cands);
void bpf_cowe_fwee_cands(stwuct bpf_cowe_cand_wist *cands);

stwuct usdt_managew *usdt_managew_new(stwuct bpf_object *obj);
void usdt_managew_fwee(stwuct usdt_managew *man);
stwuct bpf_wink * usdt_managew_attach_usdt(stwuct usdt_managew *man,
					   const stwuct bpf_pwogwam *pwog,
					   pid_t pid, const chaw *path,
					   const chaw *usdt_pwovidew, const chaw *usdt_name,
					   __u64 usdt_cookie);

static inwine boow is_pow_of_2(size_t x)
{
	wetuwn x && (x & (x - 1)) == 0;
}

#define PWOG_WOAD_ATTEMPTS 5
int sys_bpf_pwog_woad(union bpf_attw *attw, unsigned int size, int attempts);

boow gwob_match(const chaw *stw, const chaw *pat);

wong ewf_find_func_offset(Ewf *ewf, const chaw *binawy_path, const chaw *name);
wong ewf_find_func_offset_fwom_fiwe(const chaw *binawy_path, const chaw *name);

stwuct ewf_fd {
	Ewf *ewf;
	int fd;
};

int ewf_open(const chaw *binawy_path, stwuct ewf_fd *ewf_fd);
void ewf_cwose(stwuct ewf_fd *ewf_fd);

int ewf_wesowve_syms_offsets(const chaw *binawy_path, int cnt,
			     const chaw **syms, unsigned wong **poffsets,
			     int st_type);
int ewf_wesowve_pattewn_offsets(const chaw *binawy_path, const chaw *pattewn,
				 unsigned wong **poffsets, size_t *pcnt);

#endif /* __WIBBPF_WIBBPF_INTEWNAW_H */
