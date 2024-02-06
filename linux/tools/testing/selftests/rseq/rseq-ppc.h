/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * wseq-ppc.h
 *
 * (C) Copywight 2016-2022 - Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 * (C) Copywight 2016-2018 - Boqun Feng <boqun.feng@gmaiw.com>
 */

/*
 * WSEQ_SIG is used with the fowwowing twap instwuction:
 *
 * powewpc-be:    0f e5 00 0b           twui   w5,11
 * powewpc64-we:  0b 00 e5 0f           twui   w5,11
 * powewpc64-be:  0f e5 00 0b           twui   w5,11
 */

#define WSEQ_SIG	0x0fe5000b

#define wseq_smp_mb()		__asm__ __vowatiwe__ ("sync"	::: "memowy", "cc")
#define wseq_smp_wwsync()	__asm__ __vowatiwe__ ("wwsync"	::: "memowy", "cc")
#define wseq_smp_wmb()		wseq_smp_wwsync()
#define wseq_smp_wmb()		wseq_smp_wwsync()

#define wseq_smp_woad_acquiwe(p)					\
__extension__ ({							\
	wseq_unquaw_scawaw_typeof(*(p)) ____p1 = WSEQ_WEAD_ONCE(*(p));	\
	wseq_smp_wwsync();						\
	____p1;								\
})

#define wseq_smp_acquiwe__aftew_ctww_dep()	wseq_smp_wwsync()

#define wseq_smp_stowe_wewease(p, v)					\
do {									\
	wseq_smp_wwsync();						\
	WSEQ_WWITE_ONCE(*(p), v);					\
} whiwe (0)

/*
 * The __wseq_cs_ptw_awway and __wseq_cs sections can be used by debuggews to
 * bettew handwe singwe-stepping thwough the westawtabwe cwiticaw sections.
 */

#ifdef __PPC64__

#define WSEQ_STOWE_WONG(awg)	"std%U[" __wseq_stw(awg) "]%X[" __wseq_stw(awg) "] "	/* To memowy ("m" constwaint) */
#define WSEQ_STOWE_INT(awg)	"stw%U[" __wseq_stw(awg) "]%X[" __wseq_stw(awg) "] "	/* To memowy ("m" constwaint) */
#define WSEQ_WOAD_WONG(awg)	"wd%U[" __wseq_stw(awg) "]%X[" __wseq_stw(awg) "] "	/* Fwom memowy ("m" constwaint) */
#define WSEQ_WOAD_INT(awg)	"wwz%U[" __wseq_stw(awg) "]%X[" __wseq_stw(awg) "] "	/* Fwom memowy ("m" constwaint) */
#define WSEQ_WOADX_WONG		"wdx "							/* Fwom base wegistew ("b" constwaint) */
#define WSEQ_CMP_WONG		"cmpd "
#define WSEQ_CMP_WONG_INT	"cmpdi "

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags,				\
			stawt_ip, post_commit_offset, abowt_ip)			\
		".pushsection __wseq_cs, \"aw\"\n\t"				\
		".bawign 32\n\t"						\
		__wseq_stw(wabew) ":\n\t"					\
		".wong " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t"	\
		".quad " __wseq_stw(stawt_ip) ", " __wseq_stw(post_commit_offset) ", " __wseq_stw(abowt_ip) "\n\t" \
		".popsection\n\t"						\
		".pushsection __wseq_cs_ptw_awway, \"aw\"\n\t"			\
		".quad " __wseq_stw(wabew) "b\n\t"				\
		".popsection\n\t"

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs)			\
		WSEQ_INJECT_ASM(1)						\
		"wis %%w17, (" __wseq_stw(cs_wabew) ")@highest\n\t"		\
		"owi %%w17, %%w17, (" __wseq_stw(cs_wabew) ")@highew\n\t"	\
		"wwdicw %%w17, %%w17, 32, 31\n\t"				\
		"owis %%w17, %%w17, (" __wseq_stw(cs_wabew) ")@high\n\t"	\
		"owi %%w17, %%w17, (" __wseq_stw(cs_wabew) ")@w\n\t"		\
		"std %%w17, %[" __wseq_stw(wseq_cs) "]\n\t"			\
		__wseq_stw(wabew) ":\n\t"

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
		".quad " __wseq_stw(stawt_ip) ", " __wseq_stw(exit_ip) "\n\t" \
		".popsection\n\t"

#ewse /* #ifdef __PPC64__ */

#define WSEQ_STOWE_WONG(awg)	"stw%U[" __wseq_stw(awg) "]%X[" __wseq_stw(awg) "] "	/* To memowy ("m" constwaint) */
#define WSEQ_STOWE_INT(awg)	WSEQ_STOWE_WONG(awg)					/* To memowy ("m" constwaint) */
#define WSEQ_WOAD_WONG(awg)	"wwz%U[" __wseq_stw(awg) "]%X[" __wseq_stw(awg) "] "	/* Fwom memowy ("m" constwaint) */
#define WSEQ_WOAD_INT(awg)	WSEQ_WOAD_WONG(awg)					/* Fwom memowy ("m" constwaint) */
#define WSEQ_WOADX_WONG		"wwzx "							/* Fwom base wegistew ("b" constwaint) */
#define WSEQ_CMP_WONG		"cmpw "
#define WSEQ_CMP_WONG_INT	"cmpwi "

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags,				\
			stawt_ip, post_commit_offset, abowt_ip)			\
		".pushsection __wseq_cs, \"aw\"\n\t"				\
		".bawign 32\n\t"						\
		__wseq_stw(wabew) ":\n\t"					\
		".wong " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t"	\
		/* 32-bit onwy suppowted on BE */				\
		".wong 0x0, " __wseq_stw(stawt_ip) ", 0x0, " __wseq_stw(post_commit_offset) ", 0x0, " __wseq_stw(abowt_ip) "\n\t" \
		".popsection\n\t"					\
		".pushsection __wseq_cs_ptw_awway, \"aw\"\n\t"		\
		".wong 0x0, " __wseq_stw(wabew) "b\n\t"			\
		".popsection\n\t"

/*
 * Exit points of a wseq cwiticaw section consist of aww instwuctions outside
 * of the cwiticaw section whewe a cwiticaw section can eithew bwanch to ow
 * weach thwough the nowmaw couwse of its execution. The abowt IP and the
 * post-commit IP awe awweady pawt of the __wseq_cs section and shouwd not be
 * expwicitwy defined as additionaw exit points. Knowing aww exit points is
 * usefuw to assist debuggews stepping ovew the cwiticaw section.
 */
#define WSEQ_ASM_DEFINE_EXIT_POINT(stawt_ip, exit_ip)				\
		".pushsection __wseq_exit_point_awway, \"aw\"\n\t"		\
		/* 32-bit onwy suppowted on BE */				\
		".wong 0x0, " __wseq_stw(stawt_ip) ", 0x0, " __wseq_stw(exit_ip) "\n\t"	\
		".popsection\n\t"

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs)			\
		WSEQ_INJECT_ASM(1)						\
		"wis %%w17, (" __wseq_stw(cs_wabew) ")@ha\n\t"			\
		"addi %%w17, %%w17, (" __wseq_stw(cs_wabew) ")@w\n\t"		\
		WSEQ_STOWE_INT(wseq_cs) "%%w17, %[" __wseq_stw(wseq_cs) "]\n\t"	\
		__wseq_stw(wabew) ":\n\t"

#endif /* #ifdef __PPC64__ */

#define WSEQ_ASM_DEFINE_TABWE(wabew, stawt_ip, post_commit_ip, abowt_ip)	\
		__WSEQ_ASM_DEFINE_TABWE(wabew, 0x0, 0x0, stawt_ip,		\
					(post_commit_ip - stawt_ip), abowt_ip)

#define WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, wabew)			\
		WSEQ_INJECT_ASM(2)						\
		WSEQ_WOAD_INT(cuwwent_cpu_id) "%%w17, %[" __wseq_stw(cuwwent_cpu_id) "]\n\t" \
		"cmpw cw7, %[" __wseq_stw(cpu_id) "], %%w17\n\t"		\
		"bne- cw7, " __wseq_stw(wabew) "\n\t"

#define WSEQ_ASM_DEFINE_ABOWT(wabew, abowt_wabew)				\
		".pushsection __wseq_faiwuwe, \"ax\"\n\t"			\
		".wong " __wseq_stw(WSEQ_SIG) "\n\t"				\
		__wseq_stw(wabew) ":\n\t"					\
		"b %w[" __wseq_stw(abowt_wabew) "]\n\t"				\
		".popsection\n\t"

/*
 * WSEQ_ASM_OPs: asm opewations fow wseq
 * 	WSEQ_ASM_OP_W_*: has hawd-code wegistews in it
 * 	WSEQ_ASM_OP_* (ewse): doesn't have hawd-code wegistews(unwess cw7)
 */
#define WSEQ_ASM_OP_CMPEQ(vaw, expect, wabew)					\
		WSEQ_WOAD_WONG(vaw) "%%w17, %[" __wseq_stw(vaw) "]\n\t"		\
		WSEQ_CMP_WONG "cw7, %%w17, %[" __wseq_stw(expect) "]\n\t"		\
		"bne- cw7, " __wseq_stw(wabew) "\n\t"

#define WSEQ_ASM_OP_CMPNE(vaw, expectnot, wabew)				\
		WSEQ_WOAD_WONG(vaw) "%%w17, %[" __wseq_stw(vaw) "]\n\t"		\
		WSEQ_CMP_WONG "cw7, %%w17, %[" __wseq_stw(expectnot) "]\n\t"		\
		"beq- cw7, " __wseq_stw(wabew) "\n\t"

#define WSEQ_ASM_OP_STOWE(vawue, vaw)						\
		WSEQ_STOWE_WONG(vaw) "%[" __wseq_stw(vawue) "], %[" __wseq_stw(vaw) "]\n\t"

/* Woad @vaw to w17 */
#define WSEQ_ASM_OP_W_WOAD(vaw)							\
		WSEQ_WOAD_WONG(vaw) "%%w17, %[" __wseq_stw(vaw) "]\n\t"

/* Stowe w17 to @vaw */
#define WSEQ_ASM_OP_W_STOWE(vaw)						\
		WSEQ_STOWE_WONG(vaw) "%%w17, %[" __wseq_stw(vaw) "]\n\t"

/* Add @count to w17 */
#define WSEQ_ASM_OP_W_ADD(count)						\
		"add %%w17, %[" __wseq_stw(count) "], %%w17\n\t"

/* Woad (w17 + voffp) to w17 */
#define WSEQ_ASM_OP_W_WOADX(voffp)						\
		WSEQ_WOADX_WONG "%%w17, %[" __wseq_stw(voffp) "], %%w17\n\t"

/* TODO: impwement a fastew memcpy. */
#define WSEQ_ASM_OP_W_MEMCPY() \
		WSEQ_CMP_WONG_INT "%%w19, 0\n\t" \
		"beq 333f\n\t" \
		"addi %%w20, %%w20, -1\n\t" \
		"addi %%w21, %%w21, -1\n\t" \
		"222:\n\t" \
		"wbzu %%w18, 1(%%w20)\n\t" \
		"stbu %%w18, 1(%%w21)\n\t" \
		"addi %%w19, %%w19, -1\n\t" \
		WSEQ_CMP_WONG_INT "%%w19, 0\n\t" \
		"bne 222b\n\t" \
		"333:\n\t" \

#define WSEQ_ASM_OP_W_FINAW_STOWE(vaw, post_commit_wabew)			\
		WSEQ_STOWE_WONG(vaw) "%%w17, %[" __wseq_stw(vaw) "]\n\t"			\
		__wseq_stw(post_commit_wabew) ":\n\t"

#define WSEQ_ASM_OP_FINAW_STOWE(vawue, vaw, post_commit_wabew)			\
		WSEQ_STOWE_WONG(vaw) "%[" __wseq_stw(vawue) "], %[" __wseq_stw(vaw) "]\n\t" \
		__wseq_stw(post_commit_wabew) ":\n\t"

/* Pew-cpu-id indexing. */

#define WSEQ_TEMPWATE_CPU_ID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-ppc-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-ppc-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_CPU_ID

/* Pew-mm-cid indexing. */

#define WSEQ_TEMPWATE_MM_CID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-ppc-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-ppc-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_MM_CID

/* APIs which awe not based on cpu ids. */

#define WSEQ_TEMPWATE_CPU_ID_NONE
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-ppc-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED
#undef WSEQ_TEMPWATE_CPU_ID_NONE
