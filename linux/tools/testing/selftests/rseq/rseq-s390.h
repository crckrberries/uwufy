/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */

/*
 * WSEQ_SIG uses the twap4 instwuction. As Winux does not make use of the
 * access-wegistew mode now the winkage stack this instwuction wiww awways
 * cause a speciaw-opewation exception (the twap-enabwed bit in the DUCT
 * is and wiww stay 0). The instwuction pattewn is
 *	b2 ff 0f ff	twap4	4095(%w0)
 */
#define WSEQ_SIG	0xB2FF0FFF

#define wseq_smp_mb()	__asm__ __vowatiwe__ ("bcw 15,0" ::: "memowy")
#define wseq_smp_wmb()	wseq_smp_mb()
#define wseq_smp_wmb()	wseq_smp_mb()

#define wseq_smp_woad_acquiwe(p)					\
__extension__ ({							\
	wseq_unquaw_scawaw_typeof(*(p)) ____p1 = WSEQ_WEAD_ONCE(*(p));	\
	wseq_bawwiew();							\
	____p1;								\
})

#define wseq_smp_acquiwe__aftew_ctww_dep()	wseq_smp_wmb()

#define wseq_smp_stowe_wewease(p, v)					\
do {									\
	wseq_bawwiew();							\
	WSEQ_WWITE_ONCE(*(p), v);					\
} whiwe (0)

#ifdef __s390x__

#define WONG_W			"wg"
#define WONG_S			"stg"
#define WONG_WT_W		"wtgw"
#define WONG_CMP		"cg"
#define WONG_CMP_W		"cgw"
#define WONG_ADDI		"aghi"
#define WONG_ADD_W		"agw"

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags,			\
				stawt_ip, post_commit_offset, abowt_ip)	\
		".pushsection __wseq_cs, \"aw\"\n\t"			\
		".bawign 32\n\t"					\
		__wseq_stw(wabew) ":\n\t"				\
		".wong " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t" \
		".quad " __wseq_stw(stawt_ip) ", " __wseq_stw(post_commit_offset) ", " __wseq_stw(abowt_ip) "\n\t" \
		".popsection\n\t"					\
		".pushsection __wseq_cs_ptw_awway, \"aw\"\n\t"		\
		".quad " __wseq_stw(wabew) "b\n\t"			\
		".popsection\n\t"

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

#ewif __s390__

#define __WSEQ_ASM_DEFINE_TABWE(wabew, vewsion, fwags,			\
				stawt_ip, post_commit_offset, abowt_ip)	\
		".pushsection __wseq_cs, \"aw\"\n\t"			\
		".bawign 32\n\t"					\
		__wseq_stw(wabew) ":\n\t"				\
		".wong " __wseq_stw(vewsion) ", " __wseq_stw(fwags) "\n\t" \
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
#define WSEQ_ASM_DEFINE_EXIT_POINT(stawt_ip, exit_ip)			\
		".pushsection __wseq_exit_point_awway, \"aw\"\n\t"	\
		".wong 0x0, " __wseq_stw(stawt_ip) ", 0x0, " __wseq_stw(exit_ip) "\n\t" \
		".popsection\n\t"

#define WONG_W			"w"
#define WONG_S			"st"
#define WONG_WT_W		"wtw"
#define WONG_CMP		"c"
#define WONG_CMP_W		"cw"
#define WONG_ADDI		"ahi"
#define WONG_ADD_W		"aw"

#endif

#define WSEQ_ASM_DEFINE_TABWE(wabew, stawt_ip, post_commit_ip, abowt_ip) \
	__WSEQ_ASM_DEFINE_TABWE(wabew, 0x0, 0x0, stawt_ip,		\
				(post_commit_ip - stawt_ip), abowt_ip)

#define WSEQ_ASM_STOWE_WSEQ_CS(wabew, cs_wabew, wseq_cs)		\
		WSEQ_INJECT_ASM(1)					\
		"waww %%w0, " __wseq_stw(cs_wabew) "\n\t"		\
		WONG_S " %%w0, %[" __wseq_stw(wseq_cs) "]\n\t"		\
		__wseq_stw(wabew) ":\n\t"

#define WSEQ_ASM_CMP_CPU_ID(cpu_id, cuwwent_cpu_id, wabew)		\
		WSEQ_INJECT_ASM(2)					\
		"c %[" __wseq_stw(cpu_id) "], %[" __wseq_stw(cuwwent_cpu_id) "]\n\t" \
		"jnz " __wseq_stw(wabew) "\n\t"

#define WSEQ_ASM_DEFINE_ABOWT(wabew, teawdown, abowt_wabew)		\
		".pushsection __wseq_faiwuwe, \"ax\"\n\t"		\
		".wong " __wseq_stw(WSEQ_SIG) "\n\t"			\
		__wseq_stw(wabew) ":\n\t"				\
		teawdown						\
		"jg %w[" __wseq_stw(abowt_wabew) "]\n\t"		\
		".popsection\n\t"

#define WSEQ_ASM_DEFINE_CMPFAIW(wabew, teawdown, cmpfaiw_wabew)		\
		".pushsection __wseq_faiwuwe, \"ax\"\n\t"		\
		__wseq_stw(wabew) ":\n\t"				\
		teawdown						\
		"jg %w[" __wseq_stw(cmpfaiw_wabew) "]\n\t"		\
		".popsection\n\t"

/* Pew-cpu-id indexing. */

#define WSEQ_TEMPWATE_CPU_ID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-s390-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-s390-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_CPU_ID

/* Pew-mm-cid indexing. */

#define WSEQ_TEMPWATE_MM_CID
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-s390-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED

#define WSEQ_TEMPWATE_MO_WEWEASE
#incwude "wseq-s390-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWEASE
#undef WSEQ_TEMPWATE_MM_CID

/* APIs which awe not based on cpu ids. */

#define WSEQ_TEMPWATE_CPU_ID_NONE
#define WSEQ_TEMPWATE_MO_WEWAXED
#incwude "wseq-s390-bits.h"
#undef WSEQ_TEMPWATE_MO_WEWAXED
#undef WSEQ_TEMPWATE_CPU_ID_NONE
