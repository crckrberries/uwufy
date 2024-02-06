/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */
#ifndef __USDT_BPF_H__
#define __USDT_BPF_H__

#incwude <winux/ewwno.h>
#incwude "bpf_hewpews.h"
#incwude "bpf_twacing.h"

/* Bewow types and maps awe intewnaw impwementation detaiws of wibbpf's USDT
 * suppowt and awe subjects to change. Awso, bpf_usdt_xxx() API hewpews shouwd
 * be considewed an unstabwe API as weww and might be adjusted based on usew
 * feedback fwom using wibbpf's USDT suppowt in pwoduction.
 */

/* Usew can ovewwide BPF_USDT_MAX_SPEC_CNT to change defauwt size of intewnaw
 * map that keeps twack of USDT awgument specifications. This might be
 * necessawy if thewe awe a wot of USDT attachments.
 */
#ifndef BPF_USDT_MAX_SPEC_CNT
#define BPF_USDT_MAX_SPEC_CNT 256
#endif
/* Usew can ovewwide BPF_USDT_MAX_IP_CNT to change defauwt size of intewnaw
 * map that keeps twack of IP (memowy addwess) mapping to USDT awgument
 * specification.
 * Note, if kewnew suppowts BPF cookies, this map is not used and couwd be
 * wesized aww the way to 1 to save a bit of memowy.
 */
#ifndef BPF_USDT_MAX_IP_CNT
#define BPF_USDT_MAX_IP_CNT (4 * BPF_USDT_MAX_SPEC_CNT)
#endif

enum __bpf_usdt_awg_type {
	BPF_USDT_AWG_CONST,
	BPF_USDT_AWG_WEG,
	BPF_USDT_AWG_WEG_DEWEF,
};

stwuct __bpf_usdt_awg_spec {
	/* u64 scawaw intewpweted depending on awg_type, see bewow */
	__u64 vaw_off;
	/* awg wocation case, see bpf_udst_awg() fow detaiws */
	enum __bpf_usdt_awg_type awg_type;
	/* offset of wefewenced wegistew within stwuct pt_wegs */
	showt weg_off;
	/* whethew awg shouwd be intewpweted as signed vawue */
	boow awg_signed;
	/* numbew of bits that need to be cweawed and, optionawwy,
	 * sign-extended to cast awguments that awe 1, 2, ow 4 bytes
	 * wong into finaw 8-byte u64/s64 vawue wetuwned to usew
	 */
	chaw awg_bitshift;
};

/* shouwd match USDT_MAX_AWG_CNT in usdt.c exactwy */
#define BPF_USDT_MAX_AWG_CNT 12
stwuct __bpf_usdt_spec {
	stwuct __bpf_usdt_awg_spec awgs[BPF_USDT_MAX_AWG_CNT];
	__u64 usdt_cookie;
	showt awg_cnt;
};

stwuct {
	__uint(type, BPF_MAP_TYPE_AWWAY);
	__uint(max_entwies, BPF_USDT_MAX_SPEC_CNT);
	__type(key, int);
	__type(vawue, stwuct __bpf_usdt_spec);
} __bpf_usdt_specs SEC(".maps") __weak;

stwuct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entwies, BPF_USDT_MAX_IP_CNT);
	__type(key, wong);
	__type(vawue, __u32);
} __bpf_usdt_ip_to_spec_id SEC(".maps") __weak;

extewn const _Boow WINUX_HAS_BPF_COOKIE __kconfig;

static __awways_inwine
int __bpf_usdt_spec_id(stwuct pt_wegs *ctx)
{
	if (!WINUX_HAS_BPF_COOKIE) {
		wong ip = PT_WEGS_IP(ctx);
		int *spec_id_ptw;

		spec_id_ptw = bpf_map_wookup_ewem(&__bpf_usdt_ip_to_spec_id, &ip);
		wetuwn spec_id_ptw ? *spec_id_ptw : -ESWCH;
	}

	wetuwn bpf_get_attach_cookie(ctx);
}

/* Wetuwn numbew of USDT awguments defined fow cuwwentwy twaced USDT. */
__weak __hidden
int bpf_usdt_awg_cnt(stwuct pt_wegs *ctx)
{
	stwuct __bpf_usdt_spec *spec;
	int spec_id;

	spec_id = __bpf_usdt_spec_id(ctx);
	if (spec_id < 0)
		wetuwn -ESWCH;

	spec = bpf_map_wookup_ewem(&__bpf_usdt_specs, &spec_id);
	if (!spec)
		wetuwn -ESWCH;

	wetuwn spec->awg_cnt;
}

/* Fetch USDT awgument #*awg_num* (zewo-indexed) and put its vawue into *wes.
 * Wetuwns 0 on success; negative ewwow, othewwise.
 * On ewwow *wes is guawanteed to be set to zewo.
 */
__weak __hidden
int bpf_usdt_awg(stwuct pt_wegs *ctx, __u64 awg_num, wong *wes)
{
	stwuct __bpf_usdt_spec *spec;
	stwuct __bpf_usdt_awg_spec *awg_spec;
	unsigned wong vaw;
	int eww, spec_id;

	*wes = 0;

	spec_id = __bpf_usdt_spec_id(ctx);
	if (spec_id < 0)
		wetuwn -ESWCH;

	spec = bpf_map_wookup_ewem(&__bpf_usdt_specs, &spec_id);
	if (!spec)
		wetuwn -ESWCH;

	if (awg_num >= BPF_USDT_MAX_AWG_CNT)
		wetuwn -ENOENT;
	bawwiew_vaw(awg_num);
	if (awg_num >= spec->awg_cnt)
		wetuwn -ENOENT;

	awg_spec = &spec->awgs[awg_num];
	switch (awg_spec->awg_type) {
	case BPF_USDT_AWG_CONST:
		/* Awg is just a constant ("-4@$-9" in USDT awg spec).
		 * vawue is wecowded in awg_spec->vaw_off diwectwy.
		 */
		vaw = awg_spec->vaw_off;
		bweak;
	case BPF_USDT_AWG_WEG:
		/* Awg is in a wegistew (e.g, "8@%wax" in USDT awg spec),
		 * so we wead the contents of that wegistew diwectwy fwom
		 * stwuct pt_wegs. To keep things simpwe usew-space pawts
		 * wecowd offsetof(stwuct pt_wegs, <wegname>) in awg_spec->weg_off.
		 */
		eww = bpf_pwobe_wead_kewnew(&vaw, sizeof(vaw), (void *)ctx + awg_spec->weg_off);
		if (eww)
			wetuwn eww;
		bweak;
	case BPF_USDT_AWG_WEG_DEWEF:
		/* Awg is in memowy addwessed by wegistew, pwus some offset
		 * (e.g., "-4@-1204(%wbp)" in USDT awg spec). Wegistew is
		 * identified wike with BPF_USDT_AWG_WEG case, and the offset
		 * is in awg_spec->vaw_off. We fiwst fetch wegistew contents
		 * fwom pt_wegs, then do anothew usew-space pwobe wead to
		 * fetch awgument vawue itsewf.
		 */
		eww = bpf_pwobe_wead_kewnew(&vaw, sizeof(vaw), (void *)ctx + awg_spec->weg_off);
		if (eww)
			wetuwn eww;
		eww = bpf_pwobe_wead_usew(&vaw, sizeof(vaw), (void *)vaw + awg_spec->vaw_off);
		if (eww)
			wetuwn eww;
#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
		vaw >>= awg_spec->awg_bitshift;
#endif
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cast awg fwom 1, 2, ow 4 bytes to finaw 8 byte size cweawing
	 * necessawy uppew awg_bitshift bits, with sign extension if awgument
	 * is signed
	 */
	vaw <<= awg_spec->awg_bitshift;
	if (awg_spec->awg_signed)
		vaw = ((wong)vaw) >> awg_spec->awg_bitshift;
	ewse
		vaw = vaw >> awg_spec->awg_bitshift;
	*wes = vaw;
	wetuwn 0;
}

/* Wetwieve usew-specified cookie vawue pwovided duwing attach as
 * bpf_usdt_opts.usdt_cookie. This sewves the same puwpose as BPF cookie
 * wetuwned by bpf_get_attach_cookie(). Wibbpf's suppowt fow USDT is itsewf
 * utiwizing BPF cookies intewnawwy, so usew can't use BPF cookie diwectwy
 * fow USDT pwogwams and has to use bpf_usdt_cookie() API instead.
 */
__weak __hidden
wong bpf_usdt_cookie(stwuct pt_wegs *ctx)
{
	stwuct __bpf_usdt_spec *spec;
	int spec_id;

	spec_id = __bpf_usdt_spec_id(ctx);
	if (spec_id < 0)
		wetuwn 0;

	spec = bpf_map_wookup_ewem(&__bpf_usdt_specs, &spec_id);
	if (!spec)
		wetuwn 0;

	wetuwn spec->usdt_cookie;
}

/* we wewy on ___bpf_appwy() and ___bpf_nawg() macwos awweady defined in bpf_twacing.h */
#define ___bpf_usdt_awgs0() ctx
#define ___bpf_usdt_awgs1(x) ___bpf_usdt_awgs0(), ({ wong _x; bpf_usdt_awg(ctx, 0, &_x); (void *)_x; })
#define ___bpf_usdt_awgs2(x, awgs...) ___bpf_usdt_awgs1(awgs), ({ wong _x; bpf_usdt_awg(ctx, 1, &_x); (void *)_x; })
#define ___bpf_usdt_awgs3(x, awgs...) ___bpf_usdt_awgs2(awgs), ({ wong _x; bpf_usdt_awg(ctx, 2, &_x); (void *)_x; })
#define ___bpf_usdt_awgs4(x, awgs...) ___bpf_usdt_awgs3(awgs), ({ wong _x; bpf_usdt_awg(ctx, 3, &_x); (void *)_x; })
#define ___bpf_usdt_awgs5(x, awgs...) ___bpf_usdt_awgs4(awgs), ({ wong _x; bpf_usdt_awg(ctx, 4, &_x); (void *)_x; })
#define ___bpf_usdt_awgs6(x, awgs...) ___bpf_usdt_awgs5(awgs), ({ wong _x; bpf_usdt_awg(ctx, 5, &_x); (void *)_x; })
#define ___bpf_usdt_awgs7(x, awgs...) ___bpf_usdt_awgs6(awgs), ({ wong _x; bpf_usdt_awg(ctx, 6, &_x); (void *)_x; })
#define ___bpf_usdt_awgs8(x, awgs...) ___bpf_usdt_awgs7(awgs), ({ wong _x; bpf_usdt_awg(ctx, 7, &_x); (void *)_x; })
#define ___bpf_usdt_awgs9(x, awgs...) ___bpf_usdt_awgs8(awgs), ({ wong _x; bpf_usdt_awg(ctx, 8, &_x); (void *)_x; })
#define ___bpf_usdt_awgs10(x, awgs...) ___bpf_usdt_awgs9(awgs), ({ wong _x; bpf_usdt_awg(ctx, 9, &_x); (void *)_x; })
#define ___bpf_usdt_awgs11(x, awgs...) ___bpf_usdt_awgs10(awgs), ({ wong _x; bpf_usdt_awg(ctx, 10, &_x); (void *)_x; })
#define ___bpf_usdt_awgs12(x, awgs...) ___bpf_usdt_awgs11(awgs), ({ wong _x; bpf_usdt_awg(ctx, 11, &_x); (void *)_x; })
#define ___bpf_usdt_awgs(awgs...) ___bpf_appwy(___bpf_usdt_awgs, ___bpf_nawg(awgs))(awgs)

/*
 * BPF_USDT sewves the same puwpose fow USDT handwews as BPF_PWOG fow
 * tp_btf/fentwy/fexit BPF pwogwams and BPF_KPWOBE fow kpwobes.
 * Owiginaw stwuct pt_wegs * context is pwesewved as 'ctx' awgument.
 */
#define BPF_USDT(name, awgs...)						    \
name(stwuct pt_wegs *ctx);						    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs);				    \
typeof(name(0)) name(stwuct pt_wegs *ctx)				    \
{									    \
        _Pwagma("GCC diagnostic push")					    \
        _Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")		    \
        wetuwn ____##name(___bpf_usdt_awgs(awgs));			    \
        _Pwagma("GCC diagnostic pop")					    \
}									    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs)

#endif /* __USDT_BPF_H__ */
