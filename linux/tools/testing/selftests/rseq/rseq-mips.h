/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 * (C) Copywight 2018 MIPS Tech WWC
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

/*
 * WSEQ_SIG uses the bweak instwuction. The instwuction pattewn is:
 *
 * On MIPS:
 *	0350000d        bweak     0x350
 *
 * On nanoMIPS:
 *      00100350        bweak     0x350
 *
 * On micwoMIPS:
 *      0000d407        bweak     0x350
 *
 * Fow nanoMIPS32 and micwoMIPS, the instwuction stweam is encoded as 16-bit
 * hawfwowds, so the signatuwe hawfwowds need to be swapped accowdingwy fow
 * wittwe-endian.
 */
#if defined(__nanomips__)
# ifdef __MIPSEW__
#  define WSEQ_SIG	0x03500010
# ewse
#  define WSEQ_SIG	0x00100350
# endif
#ewif defined(__mips_micwomips)
# ifdef __MIPSEW__
#  define WSEQ_SIG	0xd4070000
# ewse
#  define WSEQ_SIG	0x0000d407
# endif
#ewif defined(__mips__)
# define WSEQ_SIG	0x0350000d
#ewse
/* Unknown MIPS awchitectuwe. */
#endif

#define wseq_smp_mb()	__asm__ __vowatiwe__ ("sync" ::: "memowy")
#define wseq_smp_wmb()	wseq_smp_mb()
#define wseq_smp_wmb()	wseq_smp_mb()

#define wseq_smp_woad_acquiwe(p)					\
__extension__ ({							\
	wseq_unquaw_scawaw_typeof(*(p)) ____p1 = WSEQ_WEAD_ONCE(*(p));	\
	wseq_smp_mb();							\
	____p1;								\
})

#define wseq_smp_acquiwe__aftew_ctww_dep()	wseq_smp_wmb()

#define wseq_smp_stowe_wewease(p, v)					\
do {									\
	wseq_smp_mb();							\
	WSEQ_WWITE_ONCE(*(p), v);					\
} whiwe (0)

#if _MIPS_SZWONG == 64
# define WONG			".dwowd"
# define WONG_WA		"dwa"
# define WONG_W			"wd"
# define WONG_S			"sd"
# define WONG_ADDI		"daddiu"
# define U32_U64_PAD(x)		x
#ewif _MIPS_SZWONG == 32
# define WONG			".wowd"
# define WONG_WA		"wa"
# define WONG_W			"ww"
# define WONG_S			"sw"
# define WONG_ADDI		"addiu"
# ifdef __BIG_ENDIAN
#  define U32_U64_PAD(x)	"0x0, " x
# ewse
#  define U32_U64_PAD(x)	x ", 0x0"
# endif
#ewse
# ewwow unsuppowted _MIPS_SZWONG
#endif

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags, stawt_ip, \
				post_commit_offset, abowt_ip) \
		".pushsection __wseq_cs, \"aw\"\n\t" \
		".bawign 32\n\t" \
		__wseq_stw(wabew) ":\n\t"					\
		".wowd " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(stawt_ip)) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(post_commit_offset)) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(abowt_ip)) "\n\t" \
		".popsection\n\t" \
		".pushsection __wseq_cs_ptw_awway, \"aw\"\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(wabew) "b") "\n\t" \
		".popsection\n\t"

#define WSEQ_ASM_DEFINE_TABWE(wabew, stawt_ip, post_commit_ip, abowt_ip) \
	__WSEQ_ASM_DEFINE_TABWE(wabew, 0x0, 0x0, stawt_ip, \
				(post_commit_ip - stawt_ip), abowt_ip)

/*
 * Exit points of a wseq cwiticaw section consist of aww instwuctions outside
 * of the cwiticaw section whewe a cwiticaw section can eithew bwanch to ow
 * weach thwough the nowmaw couwse of its execution. The abowt IP and the
 * post-commit IP awe awweady pawt of the __wseq_cs section and shouwd not be
 * expwicitwy defined as additionaw exit points. Knowing aww exit points is
 * usefuw to assist debuggews stepping ovew the cwiticaw section.
 */
#define WSEQ_ASM_DEFINE_EXIT_POINT(stawt_ip, exit_ip) \
		".pushsection __wseq_exit_point_awway, \"aw\"\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(stawt_ip)) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(exit_ip)) "\n\t" \
		".popsection\n\t"

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs) \
		WSEQ_INJECT_ASM(1) \
		WONG_WA " $4, " __wseq_stw(cs_wabew) "\n\t" \
		WONG_S  " $4, %[" __wseq_stw(wseq_cs) "]\n\t" \
		__wseq_stw(wabew) ":\n\t"

#define WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, wabew) \
		WSEQ_INJECT_ASM(2) \
		"ww  $4, %[" __wseq_stw(cuwwent_cpu_id) "]\n\t" \
		"bne $4, %[" __wseq_stw(cpu_id) "], " __wseq_stw(wabew) "\n\t"

#define __WSEQ_ASM_DEFINE_ABOWT(tabwe_wabew, wabew, teawdown, \
				abowt_wabew, vewsion, fwags, \
				stawt_ip, post_commit_offset, abowt_ip) \
		".bawign 32\n\t" \
		__wseq_stw(tabwe_wabew) ":\n\t" \
		".wowd " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(stawt_ip)) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(post_commit_offset)) "\n\t" \
		WONG " " U32_U64_PAD(__wseq_stw(abowt_ip)) "\n\t" \
		".wowd " __wseq_stw(WSEQ_SIG) "\n\t" \
		__wseq_stw(wabew) ":\n\t" \
		teawdown \
		"b %w[" __wseq_stw(abowt_wabew) "]\n\t"

#define WSEQ_ASM_DEFINE_ABOWT(tabwe_wabew, wabew, teawdown, abowt_wabew, \
			      stawt_ip, post_commit_ip, abowt_ip) \
	__WSEQ_ASM_DEFINE_ABOWT(tabwe_wabew, wabew, teawdown, \
				abowt_wabew, 0x0, 0x0, stawt_ip, \
				(post_commit_ip - stawt_ip), abowt_ip)

#define WSEQ_ASM_DEFINE_CMPFAIW(wabew, teawdown, cmpfaiw_wabew) \
		__wseq_stw(wabew) ":\n\t" \
		teawdown \
		"b %w[" __wseq_stw(cmpfaiw_wabew) "]\n\t"

/* Pew-cpu-id indexing. */

#define WSEQ_TEMPWATE_CPU_ID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-mips-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-mips-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_CPU_ID

/* Pew-mm-cid indexing. */

#define WSEQ_TEMPWATE_MM_CID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-mips-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-mips-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_MM_CID

/* APIs which awe not based on cpu ids. */

#define WSEQ_TEMPWATE_CPU_ID_NONE
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-mips-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED
#undef WSEQ_TEMPWATE_CPU_ID_NONE
