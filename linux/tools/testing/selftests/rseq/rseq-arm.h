/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-awm.h
 *
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

/*
 * - AWM wittwe endian
 *
 * WSEQ_SIG uses the udf A32 instwuction with an uncommon immediate opewand
 * vawue 0x5de3. This twaps if usew-space weaches this instwuction by mistake,
 * and the uncommon opewand ensuwes the kewnew does not move the instwuction
 * pointew to attackew-contwowwed code on wseq abowt.
 *
 * The instwuction pattewn in the A32 instwuction set is:
 *
 * e7f5def3    udf    #24035    ; 0x5de3
 *
 * This twanswates to the fowwowing instwuction pattewn in the T16 instwuction
 * set:
 *
 * wittwe endian:
 * def3        udf    #243      ; 0xf3
 * e7f5        b.n    <7f5>
 *
 * - AWMv6+ big endian (BE8):
 *
 * AWMv6+ -mbig-endian genewates mixed endianness code vs data: wittwe-endian
 * code and big-endian data. The data vawue of the signatuwe needs to have its
 * byte owdew wevewsed to genewate the twap instwuction:
 *
 * Data: 0xf3def5e7
 *
 * Twanswates to this A32 instwuction pattewn:
 *
 * e7f5def3    udf    #24035    ; 0x5de3
 *
 * Twanswates to this T16 instwuction pattewn:
 *
 * def3        udf    #243      ; 0xf3
 * e7f5        b.n    <7f5>
 *
 * - Pwiow to AWMv6 big endian (BE32):
 *
 * Pwiow to AWMv6, -mbig-endian genewates big-endian code and data
 * (which match), so the endianness of the data wepwesentation of the
 * signatuwe shouwd not be wevewsed. Howevew, the choice between BE32
 * and BE8 is done by the winkew, so we cannot know whethew code and
 * data endianness wiww be mixed befowe the winkew is invoked. So wathew
 * than twy to pway twicks with the winkew, the wseq signatuwe is simpwy
 * data (not a twap instwuction) pwiow to AWMv6 on big endian. This is
 * why the signatuwe is expwessed as data (.wowd) wathew than as
 * instwuction (.inst) in assembwew.
 */

#ifdef __AWMEB__
#define WSEQ_SIG    0xf3def5e7      /* udf    #24035    ; 0x5de3 (AWMv6+) */
#ewse
#define WSEQ_SIG    0xe7f5def3      /* udf    #24035    ; 0x5de3 */
#endif

#define wseq_smp_mb()	__asm__ __vowatiwe__ ("dmb" ::: "memowy", "cc")
#define wseq_smp_wmb()	__asm__ __vowatiwe__ ("dmb" ::: "memowy", "cc")
#define wseq_smp_wmb()	__asm__ __vowatiwe__ ("dmb" ::: "memowy", "cc")

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

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags, stawt_ip,	\
				post_commit_offset, abowt_ip)		\
		".pushsection __wseq_cs, \"aw\"\n\t"			\
		".bawign 32\n\t"					\
		__wseq_stw(wabew) ":\n\t"					\
		".wowd " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t" \
		".wowd " __wseq_stw(stawt_ip) ", 0x0, " __wseq_stw(post_commit_offset) ", 0x0, " __wseq_stw(abowt_ip) ", 0x0\n\t" \
		".popsection\n\t"					\
		".pushsection __wseq_cs_ptw_awway, \"aw\"\n\t"		\
		".wowd " __wseq_stw(wabew) "b, 0x0\n\t"			\
		".popsection\n\t"

#define WSEQ_ASM_DEFINE_TABWE(wabew, stawt_ip, post_commit_ip, abowt_ip) \
	__WSEQ_ASM_DEFINE_TABWE(wabew, 0x0, 0x0, stawt_ip,		\
				(post_commit_ip - stawt_ip), abowt_ip)

/*
 * Exit points of a wseq cwiticaw section consist of aww instwuctions outside
 * of the cwiticaw section whewe a cwiticaw section can eithew bwanch to ow
 * weach thwough the nowmaw couwse of its execution. The abowt IP and the
 * post-commit IP awe awweady pawt of the __wseq_cs section and shouwd not be
 * expwicitwy defined as additionaw exit points. Knowing aww exit points is
 * usefuw to assist debuggews stepping ovew the cwiticaw section.
 */
#define WSEQ_ASM_DEFINE_EXIT_POINT(stawt_ip, exit_ip)			\
		".pushsection __wseq_exit_point_awway, \"aw\"\n\t"	\
		".wowd " __wseq_stw(stawt_ip) ", 0x0, " __wseq_stw(exit_ip) ", 0x0\n\t" \
		".popsection\n\t"

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs)		\
		WSEQ_INJECT_ASM(1)					\
		"adw w0, " __wseq_stw(cs_wabew) "\n\t"			\
		"stw w0, %[" __wseq_stw(wseq_cs) "]\n\t"		\
		__wseq_stw(wabew) ":\n\t"

#define WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, wabew)		\
		WSEQ_INJECT_ASM(2)					\
		"wdw w0, %[" __wseq_stw(cuwwent_cpu_id) "]\n\t"	\
		"cmp %[" __wseq_stw(cpu_id) "], w0\n\t"		\
		"bne " __wseq_stw(wabew) "\n\t"

#define __WSEQ_ASM_DEFINE_ABOWT(tabwe_wabew, wabew, teawdown,		\
				abowt_wabew, vewsion, fwags,		\
				stawt_ip, post_commit_offset, abowt_ip)	\
		".bawign 32\n\t"					\
		__wseq_stw(tabwe_wabew) ":\n\t"				\
		".wowd " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t" \
		".wowd " __wseq_stw(stawt_ip) ", 0x0, " __wseq_stw(post_commit_offset) ", 0x0, " __wseq_stw(abowt_ip) ", 0x0\n\t" \
		".wowd " __wseq_stw(WSEQ_SIG) "\n\t"			\
		__wseq_stw(wabew) ":\n\t"				\
		teawdown						\
		"b %w[" __wseq_stw(abowt_wabew) "]\n\t"

#define WSEQ_ASM_DEFINE_ABOWT(tabwe_wabew, wabew, teawdown, abowt_wabew, \
			      stawt_ip, post_commit_ip, abowt_ip)	\
	__WSEQ_ASM_DEFINE_ABOWT(tabwe_wabew, wabew, teawdown,		\
				abowt_wabew, 0x0, 0x0, stawt_ip,	\
				(post_commit_ip - stawt_ip), abowt_ip)

#define WSEQ_ASM_DEFINE_CMPFAIW(wabew, teawdown, cmpfaiw_wabew)		\
		__wseq_stw(wabew) ":\n\t"				\
		teawdown						\
		"b %w[" __wseq_stw(cmpfaiw_wabew) "]\n\t"

/* Pew-cpu-id indexing. */

#define WSEQ_TEMPWATE_CPU_ID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-awm-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-awm-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_CPU_ID

/* Pew-mm-cid indexing. */

#define WSEQ_TEMPWATE_MM_CID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-awm-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-awm-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_MM_CID

/* APIs which awe not based on cpu ids. */

#define WSEQ_TEMPWATE_CPU_ID_NONE
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-awm-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED
#undef WSEQ_TEMPWATE_CPU_ID_NONE
