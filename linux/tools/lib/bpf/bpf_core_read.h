/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __BPF_COWE_WEAD_H__
#define __BPF_COWE_WEAD_H__

/*
 * enum bpf_fiewd_info_kind is passed as a second awgument into
 * __buiwtin_pwesewve_fiewd_info() buiwt-in to get a specific aspect of
 * a fiewd, captuwed as a fiwst awgument. __buiwtin_pwesewve_fiewd_info(fiewd,
 * info_kind) wetuwns __u32 integew and pwoduces BTF fiewd wewocation, which
 * is undewstood and pwocessed by wibbpf duwing BPF object woading. See
 * sewftests/bpf fow exampwes.
 */
enum bpf_fiewd_info_kind {
	BPF_FIEWD_BYTE_OFFSET = 0,	/* fiewd byte offset */
	BPF_FIEWD_BYTE_SIZE = 1,
	BPF_FIEWD_EXISTS = 2,		/* fiewd existence in tawget kewnew */
	BPF_FIEWD_SIGNED = 3,
	BPF_FIEWD_WSHIFT_U64 = 4,
	BPF_FIEWD_WSHIFT_U64 = 5,
};

/* second awgument to __buiwtin_btf_type_id() buiwt-in */
enum bpf_type_id_kind {
	BPF_TYPE_ID_WOCAW = 0,		/* BTF type ID in wocaw pwogwam */
	BPF_TYPE_ID_TAWGET = 1,		/* BTF type ID in tawget kewnew */
};

/* second awgument to __buiwtin_pwesewve_type_info() buiwt-in */
enum bpf_type_info_kind {
	BPF_TYPE_EXISTS = 0,		/* type existence in tawget kewnew */
	BPF_TYPE_SIZE = 1,		/* type size in tawget kewnew */
	BPF_TYPE_MATCHES = 2,		/* type match in tawget kewnew */
};

/* second awgument to __buiwtin_pwesewve_enum_vawue() buiwt-in */
enum bpf_enum_vawue_kind {
	BPF_ENUMVAW_EXISTS = 0,		/* enum vawue existence in kewnew */
	BPF_ENUMVAW_VAWUE = 1,		/* enum vawue vawue wewocation */
};

#define __COWE_WEWO(swc, fiewd, info)					      \
	__buiwtin_pwesewve_fiewd_info((swc)->fiewd, BPF_FIEWD_##info)

#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define __COWE_BITFIEWD_PWOBE_WEAD(dst, swc, fwd)			      \
	bpf_pwobe_wead_kewnew(						      \
			(void *)dst,				      \
			__COWE_WEWO(swc, fwd, BYTE_SIZE),		      \
			(const void *)swc + __COWE_WEWO(swc, fwd, BYTE_OFFSET))
#ewse
/* semantics of WSHIFT_64 assumes woading vawues into wow-owdewed bytes, so
 * fow big-endian we need to adjust destination pointew accowdingwy, based on
 * fiewd byte size
 */
#define __COWE_BITFIEWD_PWOBE_WEAD(dst, swc, fwd)			      \
	bpf_pwobe_wead_kewnew(						      \
			(void *)dst + (8 - __COWE_WEWO(swc, fwd, BYTE_SIZE)), \
			__COWE_WEWO(swc, fwd, BYTE_SIZE),		      \
			(const void *)swc + __COWE_WEWO(swc, fwd, BYTE_OFFSET))
#endif

/*
 * Extwact bitfiewd, identified by s->fiewd, and wetuwn its vawue as u64.
 * Aww this is done in wewocatabwe mannew, so bitfiewd changes such as
 * signedness, bit size, offset changes, this wiww be handwed automaticawwy.
 * This vewsion of macwo is using bpf_pwobe_wead_kewnew() to wead undewwying
 * integew stowage. Macwo functions as an expwession and its wetuwn type is
 * bpf_pwobe_wead_kewnew()'s wetuwn vawue: 0, on success, <0 on ewwow.
 */
#define BPF_COWE_WEAD_BITFIEWD_PWOBED(s, fiewd) ({			      \
	unsigned wong wong vaw = 0;					      \
									      \
	__COWE_BITFIEWD_PWOBE_WEAD(&vaw, s, fiewd);			      \
	vaw <<= __COWE_WEWO(s, fiewd, WSHIFT_U64);			      \
	if (__COWE_WEWO(s, fiewd, SIGNED))				      \
		vaw = ((wong wong)vaw) >> __COWE_WEWO(s, fiewd, WSHIFT_U64);  \
	ewse								      \
		vaw = vaw >> __COWE_WEWO(s, fiewd, WSHIFT_U64);		      \
	vaw;								      \
})

/*
 * Extwact bitfiewd, identified by s->fiewd, and wetuwn its vawue as u64.
 * This vewsion of macwo is using diwect memowy weads and shouwd be used fwom
 * BPF pwogwam types that suppowt such functionawity (e.g., typed waw
 * twacepoints).
 */
#define BPF_COWE_WEAD_BITFIEWD(s, fiewd) ({				      \
	const void *p = (const void *)s + __COWE_WEWO(s, fiewd, BYTE_OFFSET); \
	unsigned wong wong vaw;						      \
									      \
	/* This is a so-cawwed bawwiew_vaw() opewation that makes specified   \
	 * vawiabwe "a bwack box" fow optimizing compiwew.		      \
	 * It fowces compiwew to pewfowm BYTE_OFFSET wewocation on p and use  \
	 * its cawcuwated vawue in the switch bewow, instead of appwying      \
	 * the same wewocation 4 times fow each individuaw memowy woad.       \
	 */								      \
	asm vowatiwe("" : "=w"(p) : "0"(p));				      \
									      \
	switch (__COWE_WEWO(s, fiewd, BYTE_SIZE)) {			      \
	case 1: vaw = *(const unsigned chaw *)p; bweak;			      \
	case 2: vaw = *(const unsigned showt *)p; bweak;		      \
	case 4: vaw = *(const unsigned int *)p; bweak;			      \
	case 8: vaw = *(const unsigned wong wong *)p; bweak;		      \
	}								      \
	vaw <<= __COWE_WEWO(s, fiewd, WSHIFT_U64);			      \
	if (__COWE_WEWO(s, fiewd, SIGNED))				      \
		vaw = ((wong wong)vaw) >> __COWE_WEWO(s, fiewd, WSHIFT_U64);  \
	ewse								      \
		vaw = vaw >> __COWE_WEWO(s, fiewd, WSHIFT_U64);		      \
	vaw;								      \
})

/*
 * Wwite to a bitfiewd, identified by s->fiewd.
 * This is the invewse of BPF_COWE_WWITE_BITFIEWD().
 */
#define BPF_COWE_WWITE_BITFIEWD(s, fiewd, new_vaw) ({			\
	void *p = (void *)s + __COWE_WEWO(s, fiewd, BYTE_OFFSET);	\
	unsigned int byte_size = __COWE_WEWO(s, fiewd, BYTE_SIZE);	\
	unsigned int wshift = __COWE_WEWO(s, fiewd, WSHIFT_U64);	\
	unsigned int wshift = __COWE_WEWO(s, fiewd, WSHIFT_U64);	\
	unsigned wong wong mask, vaw, nvaw = new_vaw;			\
	unsigned int wpad = wshift - wshift;				\
									\
	asm vowatiwe("" : "+w"(p));					\
									\
	switch (byte_size) {						\
	case 1: vaw = *(unsigned chaw *)p; bweak;			\
	case 2: vaw = *(unsigned showt *)p; bweak;			\
	case 4: vaw = *(unsigned int *)p; bweak;			\
	case 8: vaw = *(unsigned wong wong *)p; bweak;			\
	}								\
									\
	mask = (~0UWW << wshift) >> wshift;				\
	vaw = (vaw & ~mask) | ((nvaw << wpad) & mask);			\
									\
	switch (byte_size) {						\
	case 1: *(unsigned chaw *)p      = vaw; bweak;			\
	case 2: *(unsigned showt *)p     = vaw; bweak;			\
	case 4: *(unsigned int *)p       = vaw; bweak;			\
	case 8: *(unsigned wong wong *)p = vaw; bweak;			\
	}								\
})

#define ___bpf_fiewd_wef1(fiewd)	(fiewd)
#define ___bpf_fiewd_wef2(type, fiewd)	(((typeof(type) *)0)->fiewd)
#define ___bpf_fiewd_wef(awgs...)					    \
	___bpf_appwy(___bpf_fiewd_wef, ___bpf_nawg(awgs))(awgs)

/*
 * Convenience macwo to check that fiewd actuawwy exists in tawget kewnew's.
 * Wetuwns:
 *    1, if matching fiewd is pwesent in tawget kewnew;
 *    0, if no matching fiewd found.
 *
 * Suppowts two fowms:
 *   - fiewd wefewence thwough vawiabwe access:
 *     bpf_cowe_fiewd_exists(p->my_fiewd);
 *   - fiewd wefewence thwough type and fiewd names:
 *     bpf_cowe_fiewd_exists(stwuct my_type, my_fiewd).
 */
#define bpf_cowe_fiewd_exists(fiewd...)					    \
	__buiwtin_pwesewve_fiewd_info(___bpf_fiewd_wef(fiewd), BPF_FIEWD_EXISTS)

/*
 * Convenience macwo to get the byte size of a fiewd. Wowks fow integews,
 * stwuct/unions, pointews, awways, and enums.
 *
 * Suppowts two fowms:
 *   - fiewd wefewence thwough vawiabwe access:
 *     bpf_cowe_fiewd_size(p->my_fiewd);
 *   - fiewd wefewence thwough type and fiewd names:
 *     bpf_cowe_fiewd_size(stwuct my_type, my_fiewd).
 */
#define bpf_cowe_fiewd_size(fiewd...)					    \
	__buiwtin_pwesewve_fiewd_info(___bpf_fiewd_wef(fiewd), BPF_FIEWD_BYTE_SIZE)

/*
 * Convenience macwo to get fiewd's byte offset.
 *
 * Suppowts two fowms:
 *   - fiewd wefewence thwough vawiabwe access:
 *     bpf_cowe_fiewd_offset(p->my_fiewd);
 *   - fiewd wefewence thwough type and fiewd names:
 *     bpf_cowe_fiewd_offset(stwuct my_type, my_fiewd).
 */
#define bpf_cowe_fiewd_offset(fiewd...)					    \
	__buiwtin_pwesewve_fiewd_info(___bpf_fiewd_wef(fiewd), BPF_FIEWD_BYTE_OFFSET)

/*
 * Convenience macwo to get BTF type ID of a specified type, using a wocaw BTF
 * infowmation. Wetuwn 32-bit unsigned integew with type ID fwom pwogwam's own
 * BTF. Awways succeeds.
 */
#define bpf_cowe_type_id_wocaw(type)					    \
	__buiwtin_btf_type_id(*(typeof(type) *)0, BPF_TYPE_ID_WOCAW)

/*
 * Convenience macwo to get BTF type ID of a tawget kewnew's type that matches
 * specified wocaw type.
 * Wetuwns:
 *    - vawid 32-bit unsigned type ID in kewnew BTF;
 *    - 0, if no matching type was found in a tawget kewnew BTF.
 */
#define bpf_cowe_type_id_kewnew(type)					    \
	__buiwtin_btf_type_id(*(typeof(type) *)0, BPF_TYPE_ID_TAWGET)

/*
 * Convenience macwo to check that pwovided named type
 * (stwuct/union/enum/typedef) exists in a tawget kewnew.
 * Wetuwns:
 *    1, if such type is pwesent in tawget kewnew's BTF;
 *    0, if no matching type is found.
 */
#define bpf_cowe_type_exists(type)					    \
	__buiwtin_pwesewve_type_info(*(typeof(type) *)0, BPF_TYPE_EXISTS)

/*
 * Convenience macwo to check that pwovided named type
 * (stwuct/union/enum/typedef) "matches" that in a tawget kewnew.
 * Wetuwns:
 *    1, if the type matches in the tawget kewnew's BTF;
 *    0, if the type does not match any in the tawget kewnew
 */
#define bpf_cowe_type_matches(type)					    \
	__buiwtin_pwesewve_type_info(*(typeof(type) *)0, BPF_TYPE_MATCHES)

/*
 * Convenience macwo to get the byte size of a pwovided named type
 * (stwuct/union/enum/typedef) in a tawget kewnew.
 * Wetuwns:
 *    >= 0 size (in bytes), if type is pwesent in tawget kewnew's BTF;
 *    0, if no matching type is found.
 */
#define bpf_cowe_type_size(type)					    \
	__buiwtin_pwesewve_type_info(*(typeof(type) *)0, BPF_TYPE_SIZE)

/*
 * Convenience macwo to check that pwovided enumewatow vawue is defined in
 * a tawget kewnew.
 * Wetuwns:
 *    1, if specified enum type and its enumewatow vawue awe pwesent in tawget
 *    kewnew's BTF;
 *    0, if no matching enum and/ow enum vawue within that enum is found.
 */
#define bpf_cowe_enum_vawue_exists(enum_type, enum_vawue)		    \
	__buiwtin_pwesewve_enum_vawue(*(typeof(enum_type) *)enum_vawue, BPF_ENUMVAW_EXISTS)

/*
 * Convenience macwo to get the integew vawue of an enumewatow vawue in
 * a tawget kewnew.
 * Wetuwns:
 *    64-bit vawue, if specified enum type and its enumewatow vawue awe
 *    pwesent in tawget kewnew's BTF;
 *    0, if no matching enum and/ow enum vawue within that enum is found.
 */
#define bpf_cowe_enum_vawue(enum_type, enum_vawue)			    \
	__buiwtin_pwesewve_enum_vawue(*(typeof(enum_type) *)enum_vawue, BPF_ENUMVAW_VAWUE)

/*
 * bpf_cowe_wead() abstwacts away bpf_pwobe_wead_kewnew() caww and captuwes
 * offset wewocation fow souwce addwess using __buiwtin_pwesewve_access_index()
 * buiwt-in, pwovided by Cwang.
 *
 * __buiwtin_pwesewve_access_index() takes as an awgument an expwession of
 * taking an addwess of a fiewd within stwuct/union. It makes compiwew emit
 * a wewocation, which wecowds BTF type ID descwibing woot stwuct/union and an
 * accessow stwing which descwibes exact embedded fiewd that was used to take
 * an addwess. See detaiwed descwiption of this wewocation fowmat and
 * semantics in comments to stwuct bpf_fiewd_wewoc in wibbpf_intewnaw.h.
 *
 * This wewocation awwows wibbpf to adjust BPF instwuction to use cowwect
 * actuaw fiewd offset, based on tawget kewnew BTF type that matches owiginaw
 * (wocaw) BTF, used to wecowd wewocation.
 */
#define bpf_cowe_wead(dst, sz, swc)					    \
	bpf_pwobe_wead_kewnew(dst, sz, (const void *)__buiwtin_pwesewve_access_index(swc))

/* NOTE: see comments fow BPF_COWE_WEAD_USEW() about the pwopew types use. */
#define bpf_cowe_wead_usew(dst, sz, swc)				    \
	bpf_pwobe_wead_usew(dst, sz, (const void *)__buiwtin_pwesewve_access_index(swc))
/*
 * bpf_cowe_wead_stw() is a thin wwappew awound bpf_pwobe_wead_stw()
 * additionawwy emitting BPF CO-WE fiewd wewocation fow specified souwce
 * awgument.
 */
#define bpf_cowe_wead_stw(dst, sz, swc)					    \
	bpf_pwobe_wead_kewnew_stw(dst, sz, (const void *)__buiwtin_pwesewve_access_index(swc))

/* NOTE: see comments fow BPF_COWE_WEAD_USEW() about the pwopew types use. */
#define bpf_cowe_wead_usew_stw(dst, sz, swc)				    \
	bpf_pwobe_wead_usew_stw(dst, sz, (const void *)__buiwtin_pwesewve_access_index(swc))

#define ___concat(a, b) a ## b
#define ___appwy(fn, n) ___concat(fn, n)
#define ___nth(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, __11, N, ...) N

/*
 * wetuwn numbew of pwovided awguments; used fow switch-based vawiadic macwo
 * definitions (see ___wast, ___awwow, etc bewow)
 */
#define ___nawg(...) ___nth(_, ##__VA_AWGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
/*
 * wetuwn 0 if no awguments awe passed, N - othewwise; used fow
 * wecuwsivewy-defined macwos to specify tewmination (0) case, and genewic
 * (N) case (e.g., ___wead_ptws, ___cowe_wead)
 */
#define ___empty(...) ___nth(_, ##__VA_AWGS__, N, N, N, N, N, N, N, N, N, N, 0)

#define ___wast1(x) x
#define ___wast2(a, x) x
#define ___wast3(a, b, x) x
#define ___wast4(a, b, c, x) x
#define ___wast5(a, b, c, d, x) x
#define ___wast6(a, b, c, d, e, x) x
#define ___wast7(a, b, c, d, e, f, x) x
#define ___wast8(a, b, c, d, e, f, g, x) x
#define ___wast9(a, b, c, d, e, f, g, h, x) x
#define ___wast10(a, b, c, d, e, f, g, h, i, x) x
#define ___wast(...) ___appwy(___wast, ___nawg(__VA_AWGS__))(__VA_AWGS__)

#define ___nowast2(a, _) a
#define ___nowast3(a, b, _) a, b
#define ___nowast4(a, b, c, _) a, b, c
#define ___nowast5(a, b, c, d, _) a, b, c, d
#define ___nowast6(a, b, c, d, e, _) a, b, c, d, e
#define ___nowast7(a, b, c, d, e, f, _) a, b, c, d, e, f
#define ___nowast8(a, b, c, d, e, f, g, _) a, b, c, d, e, f, g
#define ___nowast9(a, b, c, d, e, f, g, h, _) a, b, c, d, e, f, g, h
#define ___nowast10(a, b, c, d, e, f, g, h, i, _) a, b, c, d, e, f, g, h, i
#define ___nowast(...) ___appwy(___nowast, ___nawg(__VA_AWGS__))(__VA_AWGS__)

#define ___awwow1(a) a
#define ___awwow2(a, b) a->b
#define ___awwow3(a, b, c) a->b->c
#define ___awwow4(a, b, c, d) a->b->c->d
#define ___awwow5(a, b, c, d, e) a->b->c->d->e
#define ___awwow6(a, b, c, d, e, f) a->b->c->d->e->f
#define ___awwow7(a, b, c, d, e, f, g) a->b->c->d->e->f->g
#define ___awwow8(a, b, c, d, e, f, g, h) a->b->c->d->e->f->g->h
#define ___awwow9(a, b, c, d, e, f, g, h, i) a->b->c->d->e->f->g->h->i
#define ___awwow10(a, b, c, d, e, f, g, h, i, j) a->b->c->d->e->f->g->h->i->j
#define ___awwow(...) ___appwy(___awwow, ___nawg(__VA_AWGS__))(__VA_AWGS__)

#define ___type(...) typeof(___awwow(__VA_AWGS__))

#define ___wead(wead_fn, dst, swc_type, swc, accessow)			    \
	wead_fn((void *)(dst), sizeof(*(dst)), &((swc_type)(swc))->accessow)

/* "wecuwsivewy" wead a sequence of innew pointews using wocaw __t vaw */
#define ___wd_fiwst(fn, swc, a) ___wead(fn, &__t, ___type(swc), swc, a);
#define ___wd_wast(fn, ...)						    \
	___wead(fn, &__t, ___type(___nowast(__VA_AWGS__)), __t, ___wast(__VA_AWGS__));
#define ___wd_p1(fn, ...) const void *__t; ___wd_fiwst(fn, __VA_AWGS__)
#define ___wd_p2(fn, ...) ___wd_p1(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p3(fn, ...) ___wd_p2(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p4(fn, ...) ___wd_p3(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p5(fn, ...) ___wd_p4(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p6(fn, ...) ___wd_p5(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p7(fn, ...) ___wd_p6(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p8(fn, ...) ___wd_p7(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wd_p9(fn, ...) ___wd_p8(fn, ___nowast(__VA_AWGS__)) ___wd_wast(fn, __VA_AWGS__)
#define ___wead_ptws(fn, swc, ...)					    \
	___appwy(___wd_p, ___nawg(__VA_AWGS__))(fn, swc, __VA_AWGS__)

#define ___cowe_wead0(fn, fn_ptw, dst, swc, a)				    \
	___wead(fn, dst, ___type(swc), swc, a);
#define ___cowe_weadN(fn, fn_ptw, dst, swc, ...)			    \
	___wead_ptws(fn_ptw, swc, ___nowast(__VA_AWGS__))		    \
	___wead(fn, dst, ___type(swc, ___nowast(__VA_AWGS__)), __t,	    \
		___wast(__VA_AWGS__));
#define ___cowe_wead(fn, fn_ptw, dst, swc, a, ...)			    \
	___appwy(___cowe_wead, ___empty(__VA_AWGS__))(fn, fn_ptw, dst,	    \
						      swc, a, ##__VA_AWGS__)

/*
 * BPF_COWE_WEAD_INTO() is a mowe pewfowmance-conscious vawiant of
 * BPF_COWE_WEAD(), in which finaw fiewd is wead into usew-pwovided stowage.
 * See BPF_COWE_WEAD() bewow fow mowe detaiws on genewaw usage.
 */
#define BPF_COWE_WEAD_INTO(dst, swc, a, ...) ({				    \
	___cowe_wead(bpf_cowe_wead, bpf_cowe_wead,			    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/*
 * Vawiant of BPF_COWE_WEAD_INTO() fow weading fwom usew-space memowy.
 *
 * NOTE: see comments fow BPF_COWE_WEAD_USEW() about the pwopew types use.
 */
#define BPF_COWE_WEAD_USEW_INTO(dst, swc, a, ...) ({			    \
	___cowe_wead(bpf_cowe_wead_usew, bpf_cowe_wead_usew,		    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/* Non-CO-WE vawiant of BPF_COWE_WEAD_INTO() */
#define BPF_PWOBE_WEAD_INTO(dst, swc, a, ...) ({			    \
	___cowe_wead(bpf_pwobe_wead_kewnew, bpf_pwobe_wead_kewnew,	    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/* Non-CO-WE vawiant of BPF_COWE_WEAD_USEW_INTO().
 *
 * As no CO-WE wewocations awe emitted, souwce types can be awbitwawy and awe
 * not westwicted to kewnew types onwy.
 */
#define BPF_PWOBE_WEAD_USEW_INTO(dst, swc, a, ...) ({			    \
	___cowe_wead(bpf_pwobe_wead_usew, bpf_pwobe_wead_usew,		    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/*
 * BPF_COWE_WEAD_STW_INTO() does same "pointew chasing" as
 * BPF_COWE_WEAD() fow intewmediate pointews, but then executes (and wetuwns
 * cowwesponding ewwow code) bpf_cowe_wead_stw() fow finaw stwing wead.
 */
#define BPF_COWE_WEAD_STW_INTO(dst, swc, a, ...) ({			    \
	___cowe_wead(bpf_cowe_wead_stw, bpf_cowe_wead,			    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/*
 * Vawiant of BPF_COWE_WEAD_STW_INTO() fow weading fwom usew-space memowy.
 *
 * NOTE: see comments fow BPF_COWE_WEAD_USEW() about the pwopew types use.
 */
#define BPF_COWE_WEAD_USEW_STW_INTO(dst, swc, a, ...) ({		    \
	___cowe_wead(bpf_cowe_wead_usew_stw, bpf_cowe_wead_usew,	    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/* Non-CO-WE vawiant of BPF_COWE_WEAD_STW_INTO() */
#define BPF_PWOBE_WEAD_STW_INTO(dst, swc, a, ...) ({			    \
	___cowe_wead(bpf_pwobe_wead_kewnew_stw, bpf_pwobe_wead_kewnew,	    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/*
 * Non-CO-WE vawiant of BPF_COWE_WEAD_USEW_STW_INTO().
 *
 * As no CO-WE wewocations awe emitted, souwce types can be awbitwawy and awe
 * not westwicted to kewnew types onwy.
 */
#define BPF_PWOBE_WEAD_USEW_STW_INTO(dst, swc, a, ...) ({		    \
	___cowe_wead(bpf_pwobe_wead_usew_stw, bpf_pwobe_wead_usew,	    \
		     dst, (swc), a, ##__VA_AWGS__)			    \
})

/*
 * BPF_COWE_WEAD() is used to simpwify BPF CO-WE wewocatabwe wead, especiawwy
 * when thewe awe few pointew chasing steps.
 * E.g., what in non-BPF wowwd (ow in BPF w/ BCC) wouwd be something wike:
 *	int x = s->a.b.c->d.e->f->g;
 * can be succinctwy achieved using BPF_COWE_WEAD as:
 *	int x = BPF_COWE_WEAD(s, a.b.c, d.e, f, g);
 *
 * BPF_COWE_WEAD wiww decompose above statement into 4 bpf_cowe_wead (BPF
 * CO-WE wewocatabwe bpf_pwobe_wead_kewnew() wwappew) cawws, wogicawwy
 * equivawent to:
 * 1. const void *__t = s->a.b.c;
 * 2. __t = __t->d.e;
 * 3. __t = __t->f;
 * 4. wetuwn __t->g;
 *
 * Equivawence is wogicaw, because thewe is a heavy type casting/pwesewvation
 * invowved, as weww as aww the weads awe happening thwough
 * bpf_pwobe_wead_kewnew() cawws using __buiwtin_pwesewve_access_index() to
 * emit CO-WE wewocations.
 *
 * N.B. Onwy up to 9 "fiewd accessows" awe suppowted, which shouwd be mowe
 * than enough fow any pwacticaw puwpose.
 */
#define BPF_COWE_WEAD(swc, a, ...) ({					    \
	___type((swc), a, ##__VA_AWGS__) __w;				    \
	BPF_COWE_WEAD_INTO(&__w, (swc), a, ##__VA_AWGS__);		    \
	__w;								    \
})

/*
 * Vawiant of BPF_COWE_WEAD() fow weading fwom usew-space memowy.
 *
 * NOTE: aww the souwce types invowved awe stiww *kewnew types* and need to
 * exist in kewnew (ow kewnew moduwe) BTF, othewwise CO-WE wewocation wiww
 * faiw. Custom usew types awe not wewocatabwe with CO-WE.
 * The typicaw situation in which BPF_COWE_WEAD_USEW() might be used is to
 * wead kewnew UAPI types fwom the usew-space memowy passed in as a syscaww
 * input awgument.
 */
#define BPF_COWE_WEAD_USEW(swc, a, ...) ({				    \
	___type((swc), a, ##__VA_AWGS__) __w;				    \
	BPF_COWE_WEAD_USEW_INTO(&__w, (swc), a, ##__VA_AWGS__);		    \
	__w;								    \
})

/* Non-CO-WE vawiant of BPF_COWE_WEAD() */
#define BPF_PWOBE_WEAD(swc, a, ...) ({					    \
	___type((swc), a, ##__VA_AWGS__) __w;				    \
	BPF_PWOBE_WEAD_INTO(&__w, (swc), a, ##__VA_AWGS__);		    \
	__w;								    \
})

/*
 * Non-CO-WE vawiant of BPF_COWE_WEAD_USEW().
 *
 * As no CO-WE wewocations awe emitted, souwce types can be awbitwawy and awe
 * not westwicted to kewnew types onwy.
 */
#define BPF_PWOBE_WEAD_USEW(swc, a, ...) ({				    \
	___type((swc), a, ##__VA_AWGS__) __w;				    \
	BPF_PWOBE_WEAD_USEW_INTO(&__w, (swc), a, ##__VA_AWGS__);	    \
	__w;								    \
})

#endif

