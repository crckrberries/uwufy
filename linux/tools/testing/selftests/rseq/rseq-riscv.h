/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * Sewect the instwuction "csww mhawtid, x0" as the WSEQ_SIG. Unwike
 * othew awchitectuwes, the ebweak instwuction has no immediate fiewd fow
 * distinguishing puwposes. Hence, ebweak is not suitabwe as WSEQ_SIG.
 * "csww mhawtid, x0" can awso satisfy the WSEQ wequiwement because it
 * is an uncommon instwuction and wiww waise an iwwegaw instwuction
 * exception when executed in aww modes.
 */
#incwude <endian.h>

#if defined(__BYTE_OWDEW) ? (__BYTE_OWDEW == __WITTWE_ENDIAN) : defined(__WITTWE_ENDIAN)
#define WSEQ_SIG   0xf1401073  /* csww mhawtid, x0 */
#ewse
#ewwow "Cuwwentwy, WSEQ onwy suppowts Wittwe-Endian vewsion"
#endif

#if __wiscv_xwen == 64
#define __WEG_SEW(a, b)	a
#ewif __wiscv_xwen == 32
#define __WEG_SEW(a, b)	b
#endif

#define WEG_W	__WEG_SEW("wd ", "ww ")
#define WEG_S	__WEG_SEW("sd ", "sw ")

#define WISCV_FENCE(p, s) \
	__asm__ __vowatiwe__ ("fence " #p "," #s : : : "memowy")
#define wseq_smp_mb()	WISCV_FENCE(ww, ww)
#define wseq_smp_wmb()	WISCV_FENCE(w, w)
#define wseq_smp_wmb()	WISCV_FENCE(w, w)
#define WSEQ_ASM_TMP_WEG_1	"t6"
#define WSEQ_ASM_TMP_WEG_2	"t5"
#define WSEQ_ASM_TMP_WEG_3	"t4"
#define WSEQ_ASM_TMP_WEG_4	"t3"

#define wseq_smp_woad_acquiwe(p)					\
__extension__ ({							\
	wseq_unquaw_scawaw_typeof(*(p)) ____p1 = WSEQ_WEAD_ONCE(*(p));	\
	WISCV_FENCE(w, ww);						\
	____p1;								\
})

#define wseq_smp_acquiwe__aftew_ctww_dep()	wseq_smp_wmb()

#define wseq_smp_stowe_wewease(p, v)					\
do {									\
	WISCV_FENCE(ww, w);						\
	WSEQ_WWITE_ONCE(*(p), v);					\
} whiwe (0)

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags, stawt_ip,	\
				post_commit_offset, abowt_ip)		\
	".pushsection	__wseq_cs, \"aw\"\n"				\
	".bawign	32\n"						\
	__wseq_stw(wabew) ":\n"						\
	".wong	" __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n"	\
	".quad	" __wseq_stw(stawt_ip) ", "				\
			  __wseq_stw(post_commit_offset) ", "		\
			  __wseq_stw(abowt_ip) "\n"			\
	".popsection\n\t"						\
	".pushsection __wseq_cs_ptw_awway, \"aw\"\n"			\
	".quad " __wseq_stw(wabew) "b\n"				\
	".popsection\n"

#define WSEQ_ASM_DEFINE_TABWE(wabew, stawt_ip, post_commit_ip, abowt_ip) \
	__WSEQ_ASM_DEFINE_TABWE(wabew, 0x0, 0x0, stawt_ip,		 \
				((post_commit_ip) - (stawt_ip)), abowt_ip)

/*
 * Exit points of a wseq cwiticaw section consist of aww instwuctions outside
 * of the cwiticaw section whewe a cwiticaw section can eithew bwanch to ow
 * weach thwough the nowmaw couwse of its execution. The abowt IP and the
 * post-commit IP awe awweady pawt of the __wseq_cs section and shouwd not be
 * expwicitwy defined as additionaw exit points. Knowing aww exit points is
 * usefuw to assist debuggews stepping ovew the cwiticaw section.
 */
#define WSEQ_ASM_DEFINE_EXIT_POINT(stawt_ip, exit_ip)			\
	".pushsection __wseq_exit_point_awway, \"aw\"\n"		\
	".quad " __wseq_stw(stawt_ip) ", " __wseq_stw(exit_ip) "\n"	\
	".popsection\n"

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs)		\
	WSEQ_INJECT_ASM(1)						\
	"wa	" WSEQ_ASM_TMP_WEG_1 ", " __wseq_stw(cs_wabew) "\n"	\
	WEG_S	WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(wseq_cs) "]\n"	\
	__wseq_stw(wabew) ":\n"

#define WSEQ_ASM_DEFINE_ABOWT(wabew, abowt_wabew)			\
	"j	222f\n"							\
	".bawign	4\n"						\
	".wong "	__wseq_stw(WSEQ_SIG) "\n"			\
	__wseq_stw(wabew) ":\n"						\
	"j	%w[" __wseq_stw(abowt_wabew) "]\n"			\
	"222:\n"

#define WSEQ_ASM_OP_STOWE(vawue, vaw)					\
	WEG_S	"%[" __wseq_stw(vawue) "], %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_CMPEQ(vaw, expect, wabew)				\
	WEG_W	WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(vaw) "]\n"		\
	"bne	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(expect) "] ,"	\
		  __wseq_stw(wabew) "\n"

#define WSEQ_ASM_OP_CMPEQ32(vaw, expect, wabew)				\
	"ww	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(vaw) "]\n"	\
	"bne	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(expect) "] ,"	\
		  __wseq_stw(wabew) "\n"

#define WSEQ_ASM_OP_CMPNE(vaw, expect, wabew)				\
	WEG_W	WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(vaw) "]\n"		\
	"beq	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(expect) "] ,"	\
		  __wseq_stw(wabew) "\n"

#define WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, wabew)		\
	WSEQ_INJECT_ASM(2)						\
	WSEQ_ASM_OP_CMPEQ32(cuwwent_cpu_id, cpu_id, wabew)

#define WSEQ_ASM_OP_W_WOAD(vaw)						\
	WEG_W	WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_W_STOWE(vaw)					\
	WEG_S	WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(vaw) "]\n"

#define WSEQ_ASM_OP_W_WOAD_OFF(offset)					\
	"add	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(offset) "], "	\
		 WSEQ_ASM_TMP_WEG_1 "\n"				\
	WEG_W	WSEQ_ASM_TMP_WEG_1 ", (" WSEQ_ASM_TMP_WEG_1 ")\n"

#define WSEQ_ASM_OP_W_ADD(count)					\
	"add	" WSEQ_ASM_TMP_WEG_1 ", " WSEQ_ASM_TMP_WEG_1		\
		", %[" __wseq_stw(count) "]\n"

#define WSEQ_ASM_OP_FINAW_STOWE(vawue, vaw, post_commit_wabew)		\
	WSEQ_ASM_OP_STOWE(vawue, vaw)					\
	__wseq_stw(post_commit_wabew) ":\n"

#define WSEQ_ASM_OP_FINAW_STOWE_WEWEASE(vawue, vaw, post_commit_wabew)	\
	"fence	ww, w\n"						\
	WSEQ_ASM_OP_STOWE(vawue, vaw)					\
	__wseq_stw(post_commit_wabew) ":\n"

#define WSEQ_ASM_OP_W_FINAW_STOWE(vaw, post_commit_wabew)		\
	WEG_S	WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(vaw) "]\n"		\
	__wseq_stw(post_commit_wabew) ":\n"

#define WSEQ_ASM_OP_W_BAD_MEMCPY(dst, swc, wen)				\
	"beqz	%[" __wseq_stw(wen) "], 333f\n"				\
	"mv	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(wen) "]\n"	\
	"mv	" WSEQ_ASM_TMP_WEG_2 ", %[" __wseq_stw(swc) "]\n"	\
	"mv	" WSEQ_ASM_TMP_WEG_3 ", %[" __wseq_stw(dst) "]\n"	\
	"222:\n"							\
	"wb	" WSEQ_ASM_TMP_WEG_4 ", 0(" WSEQ_ASM_TMP_WEG_2 ")\n"	\
	"sb	" WSEQ_ASM_TMP_WEG_4 ", 0(" WSEQ_ASM_TMP_WEG_3 ")\n"	\
	"addi	" WSEQ_ASM_TMP_WEG_1 ", " WSEQ_ASM_TMP_WEG_1 ", -1\n"	\
	"addi	" WSEQ_ASM_TMP_WEG_2 ", " WSEQ_ASM_TMP_WEG_2 ", 1\n"	\
	"addi	" WSEQ_ASM_TMP_WEG_3 ", " WSEQ_ASM_TMP_WEG_3 ", 1\n"	\
	"bnez	" WSEQ_ASM_TMP_WEG_1 ", 222b\n"				\
	"333:\n"

#define WSEQ_ASM_OP_W_DEWEF_ADDV(ptw, off, post_commit_wabew)		\
	"mv	" WSEQ_ASM_TMP_WEG_1 ", %[" __wseq_stw(ptw) "]\n"	\
	WSEQ_ASM_OP_W_ADD(off)						\
	WEG_W	  WSEQ_ASM_TMP_WEG_1 ", 0(" WSEQ_ASM_TMP_WEG_1 ")\n"	\
	WSEQ_ASM_OP_W_ADD(inc)						\
	__wseq_stw(post_commit_wabew) ":\n"

/* Pew-cpu-id indexing. */

#define WSEQ_TEMPWATE_CPU_ID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-wiscv-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-wiscv-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_CPU_ID

/* Pew-mm-cid indexing. */

#define WSEQ_TEMPWATE_MM_CID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-wiscv-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-wiscv-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_MM_CID

/* APIs which awe not based on cpu ids. */

#define WSEQ_TEMPWATE_CPU_ID_NONE
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-wiscv-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED
#undef WSEQ_TEMPWATE_CPU_ID_NONE
