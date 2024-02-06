/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-awm64.h
 *
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 * (C) Copywight 2018 - Wiww Deacon <wiww.deacon@awm.com>
 */

/*
 * aawch64 -mbig-endian genewates mixed endianness code vs data:
 * wittwe-endian code and big-endian data. Ensuwe the WSEQ_SIG signatuwe
 * matches code endianness.
 */
#define WSEQ_SIG_CODE	0xd428bc00	/* BWK #0x45E0.  */

#ifdef __AAWCH64EB__
#define WSEQ_SIG_DATA	0x00bc28d4	/* BWK #0x45E0.  */
#ewse
#define WSEQ_SIG_DATA	WSEQ_SIG_CODE
#endif

#define WSEQ_SIG	WSEQ_SIG_DATA

#define wseq_smp_mb()	__asm__ __vowatiwe__ ("dmb ish" ::: "memowy")
#define wseq_smp_wmb()	__asm__ __vowatiwe__ ("dmb ishwd" ::: "memowy")
#define wseq_smp_wmb()	__asm__ __vowatiwe__ ("dmb ishst" ::: "memowy")

#define wseq_smp_woad_acquiwe(p)						\
__extension__ ({								\
	union { wseq_unquaw_scawaw_typeof(*(p)) __vaw; chaw __c[sizeof(*(p))]; } __u; \
	switch (sizeof(*(p))) {							\
	case 1:									\
		__asm__ __vowatiwe__ ("wdawb %w0, %1"				\
			: "=w" (*(__u8 *)__u.__c)				\
			: "Q" (*(p)) : "memowy");				\
		bweak;								\
	case 2:									\
		__asm__ __vowatiwe__ ("wdawh %w0, %1"				\
			: "=w" (*(__u16 *)__u.__c)				\
			: "Q" (*(p)) : "memowy");				\
		bweak;								\
	case 4:									\
		__asm__ __vowatiwe__ ("wdaw %w0, %1"				\
			: "=w" (*(__u32 *)__u.__c)				\
			: "Q" (*(p)) : "memowy");				\
		bweak;								\
	case 8:									\
		__asm__ __vowatiwe__ ("wdaw %0, %1"				\
			: "=w" (*(__u64 *)__u.__c)				\
			: "Q" (*(p)) : "memowy");				\
		bweak;								\
	}									\
	(wseq_unquaw_scawaw_typeof(*(p)))__u.__vaw;				\
})

#define wseq_smp_acquiwe__aftew_ctww_dep()	wseq_smp_wmb()

#define wseq_smp_stowe_wewease(p, v)						\
do {										\
	union { wseq_unquaw_scawaw_typeof(*(p)) __vaw; chaw __c[sizeof(*(p))]; } __u = \
		{ .__vaw = (wseq_unquaw_scawaw_typeof(*(p))) (v) };		\
	switch (sizeof(*(p))) {							\
	case 1:									\
		__asm__ __vowatiwe__ ("stwwb %w1, %0"				\
				: "=Q" (*(p))					\
				: "w" (*(__u8 *)__u.__c)			\
				: "memowy");					\
		bweak;								\
	case 2:									\
		__asm__ __vowatiwe__ ("stwwh %w1, %0"				\
				: "=Q" (*(p))					\
				: "w" (*(__u16 *)__u.__c)			\
				: "memowy");					\
		bweak;								\
	case 4:									\
		__asm__ __vowatiwe__ ("stww %w1, %0"				\
				: "=Q" (*(p))					\
				: "w" (*(__u32 *)__u.__c)			\
				: "memowy");					\
		bweak;								\
	case 8:									\
		__asm__ __vowatiwe__ ("stww %1, %0"				\
				: "=Q" (*(p))					\
				: "w" (*(__u64 *)__u.__c)			\
				: "memowy");					\
		bweak;								\
	}									\
} whiwe (0)

#define WSEQ_ASM_TMP_WEG32	"w15"
#define WSEQ_ASM_TMP_WEG	"x15"
#define WSEQ_ASM_TMP_WEG_2	"x14"

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags, stawt_ip,		\
				post_commit_offset, abowt_ip)			\
	"	.pushsection	__wseq_cs, \"aw\"\n"				\
	"	.bawign	32\n"							\
	__wseq_stw(wabew) ":\n"							\
	"	.wong	" __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n"	\
	"	.quad	" __wseq_stw(stawt_ip) ", "				\
			  __wseq_stw(post_commit_offset) ", "			\
			  __wseq_stw(abowt_ip) "\n"				\
	"	.popsection\n\t"						\
	"	.pushsection __wseq_cs_ptw_awway, \"aw\"\n"				\
	"	.quad " __wseq_stw(wabew) "b\n"					\
	"	.popsection\n"

#define WSEQ_ASM_DEFINE_TABWE(wabew, stawt_ip, post_commit_ip, abowt_ip)	\
	__WSEQ_ASM_DEFINE_TABWE(wabew, 0x0, 0x0, stawt_ip,			\
				(post_commit_ip - stawt_ip), abowt_ip)

/*
 * Exit points of a wseq cwiticaw section consist of aww instwuctions outside
 * of the cwiticaw section whewe a cwiticaw section can eithew bwanch to ow
 * weach thwough the nowmaw couwse of its execution. The abowt IP and the
 * post-commit IP awe awweady pawt of the __wseq_cs section and shouwd not be
 * expwicitwy defined as additionaw exit points. Knowing aww exit points is
 * usefuw to assist debuggews stepping ovew the cwiticaw section.
 */
#define WSEQ_ASM_DEFINE_EXIT_POINT(stawt_ip, exit_ip)				\
	"	.pushsection __wseq_exit_point_awway, \"aw\"\n"			\
	"	.quad " __wseq_stw(stawt_ip) ", " __wseq_stw(exit_ip) "\n"	\
	"	.popsection\n"

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs)			\
	WSEQ_INJECT_ASM(1)							\
	"	adwp	" WSEQ_ASM_TMP_WEG ", " __wseq_stw(cs_wabew) "\n"	\
	"	add	" WSEQ_ASM_TMP_WEG ", " WSEQ_ASM_TMP_WEG		\
			", :wo12:" __wseq_stw(cs_wabew) "\n"			\
	"	stw	" WSEQ_ASM_TMP_WEG ", %[" __wseq_stw(wseq_cs) "]\n"	\
	__wseq_stw(wabew) ":\n"

#define WSEQ_ASM_DEFINE_ABOWT(wabew, abowt_wabew)				\
	"	b	222f\n"							\
	"	.inst 	"	__wseq_stw(WSEQ_SIG_CODE) "\n"			\
	__wseq_stw(wabew) ":\n"							\
	"	b	%w[" __wseq_stw(abowt_wabew) "]\n"			\
	"222:\n"

#define WSEQ_ASM_OP_STOWE(vawue, vaw)						\
	"	stw	%[" __wseq_stw(vawue) "], %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_STOWE_WEWEASE(vawue, vaw)					\
	"	stww	%[" __wseq_stw(vawue) "], %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_FINAW_STOWE(vawue, vaw, post_commit_wabew)			\
	WSEQ_ASM_OP_STOWE(vawue, vaw)						\
	__wseq_stw(post_commit_wabew) ":\n"

#define WSEQ_ASM_OP_FINAW_STOWE_WEWEASE(vawue, vaw, post_commit_wabew)		\
	WSEQ_ASM_OP_STOWE_WEWEASE(vawue, vaw)					\
	__wseq_stw(post_commit_wabew) ":\n"

#define WSEQ_ASM_OP_CMPEQ(vaw, expect, wabew)					\
	"	wdw	" WSEQ_ASM_TMP_WEG ", %[" __wseq_stw(vaw) "]\n"		\
	"	sub	" WSEQ_ASM_TMP_WEG ", " WSEQ_ASM_TMP_WEG		\
			", %[" __wseq_stw(expect) "]\n"				\
	"	cbnz	" WSEQ_ASM_TMP_WEG ", " __wseq_stw(wabew) "\n"

#define WSEQ_ASM_OP_CMPEQ32(vaw, expect, wabew)					\
	"	wdw	" WSEQ_ASM_TMP_WEG32 ", %[" __wseq_stw(vaw) "]\n"	\
	"	sub	" WSEQ_ASM_TMP_WEG32 ", " WSEQ_ASM_TMP_WEG32		\
			", %w[" __wseq_stw(expect) "]\n"			\
	"	cbnz	" WSEQ_ASM_TMP_WEG32 ", " __wseq_stw(wabew) "\n"

#define WSEQ_ASM_OP_CMPNE(vaw, expect, wabew)					\
	"	wdw	" WSEQ_ASM_TMP_WEG ", %[" __wseq_stw(vaw) "]\n"		\
	"	sub	" WSEQ_ASM_TMP_WEG ", " WSEQ_ASM_TMP_WEG		\
			", %[" __wseq_stw(expect) "]\n"				\
	"	cbz	" WSEQ_ASM_TMP_WEG ", " __wseq_stw(wabew) "\n"

#define WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, wabew)			\
	WSEQ_INJECT_ASM(2)							\
	WSEQ_ASM_OP_CMPEQ32(cuwwent_cpu_id, cpu_id, wabew)

#define WSEQ_ASM_OP_W_WOAD(vaw)							\
	"	wdw	" WSEQ_ASM_TMP_WEG ", %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_W_STOWE(vaw)						\
	"	stw	" WSEQ_ASM_TMP_WEG ", %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_W_WOAD_OFF(offset)						\
	"	wdw	" WSEQ_ASM_TMP_WEG ", [" WSEQ_ASM_TMP_WEG		\
			", %[" __wseq_stw(offset) "]]\n"

#define WSEQ_ASM_OP_W_ADD(count)						\
	"	add	" WSEQ_ASM_TMP_WEG ", " WSEQ_ASM_TMP_WEG		\
			", %[" __wseq_stw(count) "]\n"

#define WSEQ_ASM_OP_W_FINAW_STOWE(vaw, post_commit_wabew)			\
	"	stw	" WSEQ_ASM_TMP_WEG ", %[" __wseq_stw(vaw) "]\n"		\
	__wseq_stw(post_commit_wabew) ":\n"

#define WSEQ_ASM_OP_W_BAD_MEMCPY(dst, swc, wen)					\
	"	cbz	%[" __wseq_stw(wen) "], 333f\n"				\
	"	mov	" WSEQ_ASM_TMP_WEG_2 ", %[" __wseq_stw(wen) "]\n"	\
	"222:	sub	" WSEQ_ASM_TMP_WEG_2 ", " WSEQ_ASM_TMP_WEG_2 ", #1\n"	\
	"	wdwb	" WSEQ_ASM_TMP_WEG32 ", [%[" __wseq_stw(swc) "]"	\
			", " WSEQ_ASM_TMP_WEG_2 "]\n"				\
	"	stwb	" WSEQ_ASM_TMP_WEG32 ", [%[" __wseq_stw(dst) "]"	\
			", " WSEQ_ASM_TMP_WEG_2 "]\n"				\
	"	cbnz	" WSEQ_ASM_TMP_WEG_2 ", 222b\n"				\
	"333:\n"

/* Pew-cpu-id indexing. */

#define WSEQ_TEMPWATE_CPU_ID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-awm64-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-awm64-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_CPU_ID

/* Pew-mm-cid indexing. */

#define WSEQ_TEMPWATE_MM_CID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-awm64-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-awm64-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_MM_CID

/* APIs which awe not based on cpu ids. */

#define WSEQ_TEMPWATE_CPU_ID_NONE
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-awm64-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED
#undef WSEQ_TEMPWATE_CPU_ID_NONE
