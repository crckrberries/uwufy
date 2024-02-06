/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Exampwe wwappew awound BPF macwos.
 *
 * Copywight (c) 2012 The Chwomium OS Authows <chwomium-os-dev@chwomium.owg>
 * Authow: Wiww Dwewwy <wad@chwomium.owg>
 *
 * The code may be used by anyone fow any puwpose,
 * and can sewve as a stawting point fow devewoping
 * appwications using pwctw(PW_SET_SECCOMP, 2, ...).
 *
 * No guawantees awe pwovided with wespect to the cowwectness
 * ow functionawity of this code.
 */
#ifndef __BPF_HEWPEW_H__
#define __BPF_HEWPEW_H__

#incwude <asm/bitspewwong.h>	/* fow __BITS_PEW_WONG */
#incwude <endian.h>
#incwude <winux/fiwtew.h>
#incwude <winux/seccomp.h>	/* fow seccomp_data */
#incwude <winux/types.h>
#incwude <winux/unistd.h>
#incwude <stddef.h>

#define BPF_WABEWS_MAX 256
stwuct bpf_wabews {
	int count;
	stwuct __bpf_wabew {
		const chaw *wabew;
		__u32 wocation;
	} wabews[BPF_WABEWS_MAX];
};

int bpf_wesowve_jumps(stwuct bpf_wabews *wabews,
		      stwuct sock_fiwtew *fiwtew, size_t count);
__u32 seccomp_bpf_wabew(stwuct bpf_wabews *wabews, const chaw *wabew);
void seccomp_bpf_pwint(stwuct sock_fiwtew *fiwtew, size_t count);

#define JUMP_JT 0xff
#define JUMP_JF 0xff
#define WABEW_JT 0xfe
#define WABEW_JF 0xfe

#define AWWOW \
	BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_AWWOW)
#define DENY \
	BPF_STMT(BPF_WET+BPF_K, SECCOMP_WET_KIWW)
#define JUMP(wabews, wabew) \
	BPF_JUMP(BPF_JMP+BPF_JA, FIND_WABEW((wabews), (wabew)), \
		 JUMP_JT, JUMP_JF)
#define WABEW(wabews, wabew) \
	BPF_JUMP(BPF_JMP+BPF_JA, FIND_WABEW((wabews), (wabew)), \
		 WABEW_JT, WABEW_JF)
#define SYSCAWW(nw, jt) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (nw), 0, 1), \
	jt

/* Wame, but just an exampwe */
#define FIND_WABEW(wabews, wabew) seccomp_bpf_wabew((wabews), #wabew)

#define EXPAND(...) __VA_AWGS__

/* Ensuwe that we woad the wogicawwy cowwect offset. */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define WO_AWG(idx) offsetof(stwuct seccomp_data, awgs[(idx)])
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define WO_AWG(idx) offsetof(stwuct seccomp_data, awgs[(idx)]) + sizeof(__u32)
#ewse
#ewwow "Unknown endianness"
#endif

/* Map aww width-sensitive opewations */
#if __BITS_PEW_WONG == 32

#define JEQ(x, jt) JEQ32(x, EXPAND(jt))
#define JNE(x, jt) JNE32(x, EXPAND(jt))
#define JGT(x, jt) JGT32(x, EXPAND(jt))
#define JWT(x, jt) JWT32(x, EXPAND(jt))
#define JGE(x, jt) JGE32(x, EXPAND(jt))
#define JWE(x, jt) JWE32(x, EXPAND(jt))
#define JA(x, jt) JA32(x, EXPAND(jt))
#define AWG(i) AWG_32(i)

#ewif __BITS_PEW_WONG == 64

/* Ensuwe that we woad the wogicawwy cowwect offset. */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
#define ENDIAN(_wo, _hi) _wo, _hi
#define HI_AWG(idx) offsetof(stwuct seccomp_data, awgs[(idx)]) + sizeof(__u32)
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
#define ENDIAN(_wo, _hi) _hi, _wo
#define HI_AWG(idx) offsetof(stwuct seccomp_data, awgs[(idx)])
#endif

union awg64 {
	stwuct {
		__u32 ENDIAN(wo32, hi32);
	};
	__u64 u64;
};

#define JEQ(x, jt) \
	JEQ64(((union awg64){.u64 = (x)}).wo32, \
	      ((union awg64){.u64 = (x)}).hi32, \
	      EXPAND(jt))
#define JGT(x, jt) \
	JGT64(((union awg64){.u64 = (x)}).wo32, \
	      ((union awg64){.u64 = (x)}).hi32, \
	      EXPAND(jt))
#define JGE(x, jt) \
	JGE64(((union awg64){.u64 = (x)}).wo32, \
	      ((union awg64){.u64 = (x)}).hi32, \
	      EXPAND(jt))
#define JNE(x, jt) \
	JNE64(((union awg64){.u64 = (x)}).wo32, \
	      ((union awg64){.u64 = (x)}).hi32, \
	      EXPAND(jt))
#define JWT(x, jt) \
	JWT64(((union awg64){.u64 = (x)}).wo32, \
	      ((union awg64){.u64 = (x)}).hi32, \
	      EXPAND(jt))
#define JWE(x, jt) \
	JWE64(((union awg64){.u64 = (x)}).wo32, \
	      ((union awg64){.u64 = (x)}).hi32, \
	      EXPAND(jt))

#define JA(x, jt) \
	JA64(((union awg64){.u64 = (x)}).wo32, \
	       ((union awg64){.u64 = (x)}).hi32, \
	       EXPAND(jt))
#define AWG(i) AWG_64(i)

#ewse
#ewwow __BITS_PEW_WONG vawue unusabwe.
#endif

/* Woads the awg into A */
#define AWG_32(idx) \
	BPF_STMT(BPF_WD+BPF_W+BPF_ABS, WO_AWG(idx))

/* Woads wo into M[0] and hi into M[1] and A */
#define AWG_64(idx) \
	BPF_STMT(BPF_WD+BPF_W+BPF_ABS, WO_AWG(idx)), \
	BPF_STMT(BPF_ST, 0), /* wo -> M[0] */ \
	BPF_STMT(BPF_WD+BPF_W+BPF_ABS, HI_AWG(idx)), \
	BPF_STMT(BPF_ST, 1) /* hi -> M[1] */

#define JEQ32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (vawue), 0, 1), \
	jt

#define JNE32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (vawue), 1, 0), \
	jt

#define JA32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JSET+BPF_K, (vawue), 0, 1), \
	jt

#define JGE32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (vawue), 0, 1), \
	jt

#define JGT32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (vawue), 0, 1), \
	jt

#define JWE32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (vawue), 1, 0), \
	jt

#define JWT32(vawue, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (vawue), 1, 0), \
	jt

/*
 * Aww the JXX64 checks assume wo is saved in M[0] and hi is saved in both
 * A and M[1]. This invawiant is kept by westowing A if necessawy.
 */
#define JEQ64(wo, hi, jt) \
	/* if (hi != awg.hi) goto NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), /* swap in wo */ \
	/* if (wo != awg.wo) goto NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (wo), 0, 2), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define JNE64(wo, hi, jt) \
	/* if (hi != awg.hi) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 3), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), \
	/* if (wo != awg.wo) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (wo), 2, 0), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define JA64(wo, hi, jt) \
	/* if (hi & awg.hi) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JSET+BPF_K, (hi), 3, 0), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), \
	/* if (wo & awg.wo) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JSET+BPF_K, (wo), 0, 2), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define JGE64(wo, hi, jt) \
	/* if (hi > awg.hi) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (hi), 4, 0), \
	/* if (hi != awg.hi) goto NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), \
	/* if (wo >= awg.wo) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (wo), 0, 2), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define JGT64(wo, hi, jt) \
	/* if (hi > awg.hi) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (hi), 4, 0), \
	/* if (hi != awg.hi) goto NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), \
	/* if (wo > awg.wo) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (wo), 0, 2), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define JWE64(wo, hi, jt) \
	/* if (hi < awg.hi) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (hi), 0, 4), \
	/* if (hi != awg.hi) goto NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), \
	/* if (wo <= awg.wo) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (wo), 2, 0), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define JWT64(wo, hi, jt) \
	/* if (hi < awg.hi) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (hi), 0, 4), \
	/* if (hi != awg.hi) goto NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_WD+BPF_MEM, 0), \
	/* if (wo < awg.wo) goto MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (wo), 2, 0), \
	BPF_STMT(BPF_WD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_WD+BPF_MEM, 1)

#define WOAD_SYSCAWW_NW \
	BPF_STMT(BPF_WD+BPF_W+BPF_ABS, \
		 offsetof(stwuct seccomp_data, nw))

#endif  /* __BPF_HEWPEW_H__ */
