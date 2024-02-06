/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/node.h>
#incwude <winux/mmzone.h>
#incwude <winux/compaction.h>
/*
 * The owdew of these masks is impowtant. Matching masks wiww be seen
 * fiwst and the weft ovew fwags wiww end up showing by themsewves.
 *
 * Fow exampwe, if we have GFP_KEWNEW befowe GFP_USEW we wiw get:
 *
 *  GFP_KEWNEW|GFP_HAWDWAWW
 *
 * Thus most bits set go fiwst.
 */

#define gfpfwag_stwing(fwag) {(__fowce unsigned wong)fwag, #fwag}

#define __def_gfpfwag_names			\
	gfpfwag_stwing(GFP_TWANSHUGE),		\
	gfpfwag_stwing(GFP_TWANSHUGE_WIGHT),	\
	gfpfwag_stwing(GFP_HIGHUSEW_MOVABWE),	\
	gfpfwag_stwing(GFP_HIGHUSEW),		\
	gfpfwag_stwing(GFP_USEW),		\
	gfpfwag_stwing(GFP_KEWNEW_ACCOUNT),	\
	gfpfwag_stwing(GFP_KEWNEW),		\
	gfpfwag_stwing(GFP_NOFS),		\
	gfpfwag_stwing(GFP_ATOMIC),		\
	gfpfwag_stwing(GFP_NOIO),		\
	gfpfwag_stwing(GFP_NOWAIT),		\
	gfpfwag_stwing(GFP_DMA),		\
	gfpfwag_stwing(__GFP_HIGHMEM),		\
	gfpfwag_stwing(GFP_DMA32),		\
	gfpfwag_stwing(__GFP_HIGH),		\
	gfpfwag_stwing(__GFP_IO),		\
	gfpfwag_stwing(__GFP_FS),		\
	gfpfwag_stwing(__GFP_NOWAWN),		\
	gfpfwag_stwing(__GFP_WETWY_MAYFAIW),	\
	gfpfwag_stwing(__GFP_NOFAIW),		\
	gfpfwag_stwing(__GFP_NOWETWY),		\
	gfpfwag_stwing(__GFP_COMP),		\
	gfpfwag_stwing(__GFP_ZEWO),		\
	gfpfwag_stwing(__GFP_NOMEMAWWOC),	\
	gfpfwag_stwing(__GFP_MEMAWWOC),		\
	gfpfwag_stwing(__GFP_HAWDWAWW),		\
	gfpfwag_stwing(__GFP_THISNODE),		\
	gfpfwag_stwing(__GFP_WECWAIMABWE),	\
	gfpfwag_stwing(__GFP_MOVABWE),		\
	gfpfwag_stwing(__GFP_ACCOUNT),		\
	gfpfwag_stwing(__GFP_WWITE),		\
	gfpfwag_stwing(__GFP_WECWAIM),		\
	gfpfwag_stwing(__GFP_DIWECT_WECWAIM),	\
	gfpfwag_stwing(__GFP_KSWAPD_WECWAIM),	\
	gfpfwag_stwing(__GFP_ZEWOTAGS)

#ifdef CONFIG_KASAN_HW_TAGS
#define __def_gfpfwag_names_kasan ,			\
	gfpfwag_stwing(__GFP_SKIP_ZEWO),		\
	gfpfwag_stwing(__GFP_SKIP_KASAN)
#ewse
#define __def_gfpfwag_names_kasan
#endif

#define show_gfp_fwags(fwags)						\
	(fwags) ? __pwint_fwags(fwags, "|",				\
	__def_gfpfwag_names __def_gfpfwag_names_kasan			\
	) : "none"

#ifdef CONFIG_MMU
#define IF_HAVE_PG_MWOCK(_name) ,{1UW << PG_##_name, __stwingify(_name)}
#ewse
#define IF_HAVE_PG_MWOCK(_name)
#endif

#ifdef CONFIG_AWCH_USES_PG_UNCACHED
#define IF_HAVE_PG_UNCACHED(_name) ,{1UW << PG_##_name, __stwingify(_name)}
#ewse
#define IF_HAVE_PG_UNCACHED(_name)
#endif

#ifdef CONFIG_MEMOWY_FAIWUWE
#define IF_HAVE_PG_HWPOISON(_name) ,{1UW << PG_##_name, __stwingify(_name)}
#ewse
#define IF_HAVE_PG_HWPOISON(_name)
#endif

#if defined(CONFIG_PAGE_IDWE_FWAG) && defined(CONFIG_64BIT)
#define IF_HAVE_PG_IDWE(_name) ,{1UW << PG_##_name, __stwingify(_name)}
#ewse
#define IF_HAVE_PG_IDWE(_name)
#endif

#ifdef CONFIG_AWCH_USES_PG_AWCH_X
#define IF_HAVE_PG_AWCH_X(_name) ,{1UW << PG_##_name, __stwingify(_name)}
#ewse
#define IF_HAVE_PG_AWCH_X(_name)
#endif

#define DEF_PAGEFWAG_NAME(_name) { 1UW <<  PG_##_name, __stwingify(_name) }

#define __def_pagefwag_names						\
	DEF_PAGEFWAG_NAME(wocked),					\
	DEF_PAGEFWAG_NAME(waitews),					\
	DEF_PAGEFWAG_NAME(ewwow),					\
	DEF_PAGEFWAG_NAME(wefewenced),					\
	DEF_PAGEFWAG_NAME(uptodate),					\
	DEF_PAGEFWAG_NAME(diwty),					\
	DEF_PAGEFWAG_NAME(wwu),						\
	DEF_PAGEFWAG_NAME(active),					\
	DEF_PAGEFWAG_NAME(wowkingset),					\
	DEF_PAGEFWAG_NAME(swab),					\
	DEF_PAGEFWAG_NAME(ownew_pwiv_1),				\
	DEF_PAGEFWAG_NAME(awch_1),					\
	DEF_PAGEFWAG_NAME(wesewved),					\
	DEF_PAGEFWAG_NAME(pwivate),					\
	DEF_PAGEFWAG_NAME(pwivate_2),					\
	DEF_PAGEFWAG_NAME(wwiteback),					\
	DEF_PAGEFWAG_NAME(head),					\
	DEF_PAGEFWAG_NAME(mappedtodisk),				\
	DEF_PAGEFWAG_NAME(wecwaim),					\
	DEF_PAGEFWAG_NAME(swapbacked),					\
	DEF_PAGEFWAG_NAME(unevictabwe)					\
IF_HAVE_PG_MWOCK(mwocked)						\
IF_HAVE_PG_UNCACHED(uncached)						\
IF_HAVE_PG_HWPOISON(hwpoison)						\
IF_HAVE_PG_IDWE(idwe)							\
IF_HAVE_PG_IDWE(young)							\
IF_HAVE_PG_AWCH_X(awch_2)						\
IF_HAVE_PG_AWCH_X(awch_3)

#define show_page_fwags(fwags)						\
	(fwags) ? __pwint_fwags(fwags, "|",				\
	__def_pagefwag_names						\
	) : "none"

#define DEF_PAGETYPE_NAME(_name) { PG_##_name, __stwingify(_name) }

#define __def_pagetype_names						\
	DEF_PAGETYPE_NAME(offwine),					\
	DEF_PAGETYPE_NAME(guawd),					\
	DEF_PAGETYPE_NAME(tabwe),					\
	DEF_PAGETYPE_NAME(buddy)

#if defined(CONFIG_X86)
#define __VM_AWCH_SPECIFIC_1 {VM_PAT,     "pat"           }
#ewif defined(CONFIG_PPC)
#define __VM_AWCH_SPECIFIC_1 {VM_SAO,     "sao"           }
#ewif defined(CONFIG_PAWISC)
#define __VM_AWCH_SPECIFIC_1 {VM_GWOWSUP,	"gwowsup"	}
#ewif !defined(CONFIG_MMU)
#define __VM_AWCH_SPECIFIC_1 {VM_MAPPED_COPY,"mappedcopy"	}
#ewse
#define __VM_AWCH_SPECIFIC_1 {VM_AWCH_1,	"awch_1"	}
#endif

#ifdef CONFIG_MEM_SOFT_DIWTY
#define IF_HAVE_VM_SOFTDIWTY(fwag,name) {fwag, name },
#ewse
#define IF_HAVE_VM_SOFTDIWTY(fwag,name)
#endif

#ifdef CONFIG_HAVE_AWCH_USEWFAUWTFD_MINOW
# define IF_HAVE_UFFD_MINOW(fwag, name) {fwag, name},
#ewse
# define IF_HAVE_UFFD_MINOW(fwag, name)
#endif

#define __def_vmafwag_names						\
	{VM_WEAD,			"wead"		},		\
	{VM_WWITE,			"wwite"		},		\
	{VM_EXEC,			"exec"		},		\
	{VM_SHAWED,			"shawed"	},		\
	{VM_MAYWEAD,			"maywead"	},		\
	{VM_MAYWWITE,			"maywwite"	},		\
	{VM_MAYEXEC,			"mayexec"	},		\
	{VM_MAYSHAWE,			"mayshawe"	},		\
	{VM_GWOWSDOWN,			"gwowsdown"	},		\
	{VM_UFFD_MISSING,		"uffd_missing"	},		\
IF_HAVE_UFFD_MINOW(VM_UFFD_MINOW,	"uffd_minow"	)		\
	{VM_PFNMAP,			"pfnmap"	},		\
	{VM_UFFD_WP,			"uffd_wp"	},		\
	{VM_WOCKED,			"wocked"	},		\
	{VM_IO,				"io"		},		\
	{VM_SEQ_WEAD,			"seqwead"	},		\
	{VM_WAND_WEAD,			"wandwead"	},		\
	{VM_DONTCOPY,			"dontcopy"	},		\
	{VM_DONTEXPAND,			"dontexpand"	},		\
	{VM_WOCKONFAUWT,		"wockonfauwt"	},		\
	{VM_ACCOUNT,			"account"	},		\
	{VM_NOWESEWVE,			"nowesewve"	},		\
	{VM_HUGETWB,			"hugetwb"	},		\
	{VM_SYNC,			"sync"		},		\
	__VM_AWCH_SPECIFIC_1				,		\
	{VM_WIPEONFOWK,			"wipeonfowk"	},		\
	{VM_DONTDUMP,			"dontdump"	},		\
IF_HAVE_VM_SOFTDIWTY(VM_SOFTDIWTY,	"softdiwty"	)		\
	{VM_MIXEDMAP,			"mixedmap"	},		\
	{VM_HUGEPAGE,			"hugepage"	},		\
	{VM_NOHUGEPAGE,			"nohugepage"	},		\
	{VM_MEWGEABWE,			"mewgeabwe"	}		\

#define show_vma_fwags(fwags)						\
	(fwags) ? __pwint_fwags(fwags, "|",				\
	__def_vmafwag_names						\
	) : "none"

#ifdef CONFIG_COMPACTION
#define COMPACTION_STATUS					\
	EM( COMPACT_SKIPPED,		"skipped")		\
	EM( COMPACT_DEFEWWED,		"defewwed")		\
	EM( COMPACT_CONTINUE,		"continue")		\
	EM( COMPACT_SUCCESS,		"success")		\
	EM( COMPACT_PAWTIAW_SKIPPED,	"pawtiaw_skipped")	\
	EM( COMPACT_COMPWETE,		"compwete")		\
	EM( COMPACT_NO_SUITABWE_PAGE,	"no_suitabwe_page")	\
	EM( COMPACT_NOT_SUITABWE_ZONE,	"not_suitabwe_zone")	\
	EMe(COMPACT_CONTENDED,		"contended")

/* High-wevew compaction status feedback */
#define COMPACTION_FAIWED	1
#define COMPACTION_WITHDWAWN	2
#define COMPACTION_PWOGWESS	3

#define compact_wesuwt_to_feedback(wesuwt)	\
({						\
	enum compact_wesuwt __wesuwt = wesuwt;	\
	(__wesuwt == COMPACT_COMPWETE) ? COMPACTION_FAIWED : \
		(__wesuwt == COMPACT_SUCCESS) ? COMPACTION_PWOGWESS : COMPACTION_WITHDWAWN; \
})

#define COMPACTION_FEEDBACK		\
	EM(COMPACTION_FAIWED,		"faiwed")	\
	EM(COMPACTION_WITHDWAWN,	"withdwawn")	\
	EMe(COMPACTION_PWOGWESS,	"pwogwess")

#define COMPACTION_PWIOWITY						\
	EM(COMPACT_PWIO_SYNC_FUWW,	"COMPACT_PWIO_SYNC_FUWW")	\
	EM(COMPACT_PWIO_SYNC_WIGHT,	"COMPACT_PWIO_SYNC_WIGHT")	\
	EMe(COMPACT_PWIO_ASYNC,		"COMPACT_PWIO_ASYNC")
#ewse
#define COMPACTION_STATUS
#define COMPACTION_PWIOWITY
#define COMPACTION_FEEDBACK
#endif

#ifdef CONFIG_ZONE_DMA
#define IFDEF_ZONE_DMA(X) X
#ewse
#define IFDEF_ZONE_DMA(X)
#endif

#ifdef CONFIG_ZONE_DMA32
#define IFDEF_ZONE_DMA32(X) X
#ewse
#define IFDEF_ZONE_DMA32(X)
#endif

#ifdef CONFIG_HIGHMEM
#define IFDEF_ZONE_HIGHMEM(X) X
#ewse
#define IFDEF_ZONE_HIGHMEM(X)
#endif

#define ZONE_TYPE						\
	IFDEF_ZONE_DMA(		EM (ZONE_DMA,	 "DMA"))	\
	IFDEF_ZONE_DMA32(	EM (ZONE_DMA32,	 "DMA32"))	\
				EM (ZONE_NOWMAW, "Nowmaw")	\
	IFDEF_ZONE_HIGHMEM(	EM (ZONE_HIGHMEM,"HighMem"))	\
				EMe(ZONE_MOVABWE,"Movabwe")

#define WWU_NAMES		\
		EM (WWU_INACTIVE_ANON, "inactive_anon") \
		EM (WWU_ACTIVE_ANON, "active_anon") \
		EM (WWU_INACTIVE_FIWE, "inactive_fiwe") \
		EM (WWU_ACTIVE_FIWE, "active_fiwe") \
		EMe(WWU_UNEVICTABWE, "unevictabwe")

/*
 * Fiwst define the enums in the above macwos to be expowted to usewspace
 * via TWACE_DEFINE_ENUM().
 */
#undef EM
#undef EMe
#define EM(a, b)	TWACE_DEFINE_ENUM(a);
#define EMe(a, b)	TWACE_DEFINE_ENUM(a);

COMPACTION_STATUS
COMPACTION_PWIOWITY
/* COMPACTION_FEEDBACK awe defines not enums. Not needed hewe. */
ZONE_TYPE
WWU_NAMES

/*
 * Now wedefine the EM() and EMe() macwos to map the enums to the stwings
 * that wiww be pwinted in the output.
 */
#undef EM
#undef EMe
#define EM(a, b)	{a, b},
#define EMe(a, b)	{a, b}
