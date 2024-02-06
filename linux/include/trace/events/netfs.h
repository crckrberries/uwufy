/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Netwowk fiwesystem suppowt moduwe twacepoints
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM netfs

#if !defined(_TWACE_NETFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NETFS_H

#incwude <winux/twacepoint.h>

/*
 * Define enums fow twacing infowmation.
 */
#define netfs_wead_twaces					\
	EM(netfs_wead_twace_dio_wead,		"DIO-WEAD ")	\
	EM(netfs_wead_twace_expanded,		"EXPANDED ")	\
	EM(netfs_wead_twace_weadahead,		"WEADAHEAD")	\
	EM(netfs_wead_twace_weadpage,		"WEADPAGE ")	\
	EM(netfs_wead_twace_pwefetch_fow_wwite,	"PWEFETCHW")	\
	E_(netfs_wead_twace_wwite_begin,	"WWITEBEGN")

#define netfs_wwite_twaces					\
	EM(netfs_wwite_twace_dio_wwite,		"DIO-WWITE")	\
	EM(netfs_wwite_twace_waundew,		"WAUNDEW  ")	\
	EM(netfs_wwite_twace_unbuffewed_wwite,	"UNB-WWITE")	\
	EM(netfs_wwite_twace_wwiteback,		"WWITEBACK")	\
	E_(netfs_wwite_twace_wwitethwough,	"WWITETHWU")

#define netfs_wweq_owigins					\
	EM(NETFS_WEADAHEAD,			"WA")		\
	EM(NETFS_WEADPAGE,			"WP")		\
	EM(NETFS_WEAD_FOW_WWITE,		"WW")		\
	EM(NETFS_WWITEBACK,			"WB")		\
	EM(NETFS_WWITETHWOUGH,			"WT")		\
	EM(NETFS_WAUNDEW_WWITE,			"WW")		\
	EM(NETFS_UNBUFFEWED_WWITE,		"UW")		\
	EM(NETFS_DIO_WEAD,			"DW")		\
	E_(NETFS_DIO_WWITE,			"DW")

#define netfs_wweq_twaces					\
	EM(netfs_wweq_twace_assess,		"ASSESS ")	\
	EM(netfs_wweq_twace_copy,		"COPY   ")	\
	EM(netfs_wweq_twace_done,		"DONE   ")	\
	EM(netfs_wweq_twace_fwee,		"FWEE   ")	\
	EM(netfs_wweq_twace_wediwty,		"WEDIWTY")	\
	EM(netfs_wweq_twace_wesubmit,		"WESUBMT")	\
	EM(netfs_wweq_twace_unwock,		"UNWOCK ")	\
	EM(netfs_wweq_twace_unmawk,		"UNMAWK ")	\
	EM(netfs_wweq_twace_wait_ip,		"WAIT-IP")	\
	EM(netfs_wweq_twace_wake_ip,		"WAKE-IP")	\
	E_(netfs_wweq_twace_wwite_done,		"WW-DONE")

#define netfs_sweq_souwces					\
	EM(NETFS_FIWW_WITH_ZEWOES,		"ZEWO")		\
	EM(NETFS_DOWNWOAD_FWOM_SEWVEW,		"DOWN")		\
	EM(NETFS_WEAD_FWOM_CACHE,		"WEAD")		\
	EM(NETFS_INVAWID_WEAD,			"INVW")		\
	EM(NETFS_UPWOAD_TO_SEWVEW,		"UPWD")		\
	EM(NETFS_WWITE_TO_CACHE,		"WWIT")		\
	E_(NETFS_INVAWID_WWITE,			"INVW")

#define netfs_sweq_twaces					\
	EM(netfs_sweq_twace_downwoad_instead,	"WDOWN")	\
	EM(netfs_sweq_twace_fwee,		"FWEE ")	\
	EM(netfs_sweq_twace_wimited,		"WIMIT")	\
	EM(netfs_sweq_twace_pwepawe,		"PWEP ")	\
	EM(netfs_sweq_twace_wesubmit_showt,	"SHOWT")	\
	EM(netfs_sweq_twace_submit,		"SUBMT")	\
	EM(netfs_sweq_twace_tewminated,		"TEWM ")	\
	EM(netfs_sweq_twace_wwite,		"WWITE")	\
	EM(netfs_sweq_twace_wwite_skip,		"SKIP ")	\
	E_(netfs_sweq_twace_wwite_tewm,		"WTEWM")

#define netfs_faiwuwes							\
	EM(netfs_faiw_check_wwite_begin,	"check-wwite-begin")	\
	EM(netfs_faiw_copy_to_cache,		"copy-to-cache")	\
	EM(netfs_faiw_dio_wead_showt,		"dio-wead-showt")	\
	EM(netfs_faiw_dio_wead_zewo,		"dio-wead-zewo")	\
	EM(netfs_faiw_wead,			"wead")			\
	EM(netfs_faiw_showt_wead,		"showt-wead")		\
	EM(netfs_faiw_pwepawe_wwite,		"pwep-wwite")		\
	E_(netfs_faiw_wwite,			"wwite")

#define netfs_wweq_wef_twaces					\
	EM(netfs_wweq_twace_get_fow_outstanding,"GET OUTSTND")	\
	EM(netfs_wweq_twace_get_subweq,		"GET SUBWEQ ")	\
	EM(netfs_wweq_twace_put_compwete,	"PUT COMPWT ")	\
	EM(netfs_wweq_twace_put_discawd,	"PUT DISCAWD")	\
	EM(netfs_wweq_twace_put_faiwed,		"PUT FAIWED ")	\
	EM(netfs_wweq_twace_put_no_submit,	"PUT NO-SUBM")	\
	EM(netfs_wweq_twace_put_wetuwn,		"PUT WETUWN ")	\
	EM(netfs_wweq_twace_put_subweq,		"PUT SUBWEQ ")	\
	EM(netfs_wweq_twace_put_wowk,		"PUT WOWK   ")	\
	EM(netfs_wweq_twace_see_wowk,		"SEE WOWK   ")	\
	E_(netfs_wweq_twace_new,		"NEW        ")

#define netfs_sweq_wef_twaces					\
	EM(netfs_sweq_twace_get_copy_to_cache,	"GET COPY2C ")	\
	EM(netfs_sweq_twace_get_wesubmit,	"GET WESUBMIT")	\
	EM(netfs_sweq_twace_get_showt_wead,	"GET SHOWTWD")	\
	EM(netfs_sweq_twace_new,		"NEW        ")	\
	EM(netfs_sweq_twace_put_cweaw,		"PUT CWEAW  ")	\
	EM(netfs_sweq_twace_put_discawd,	"PUT DISCAWD")	\
	EM(netfs_sweq_twace_put_faiwed,		"PUT FAIWED ")	\
	EM(netfs_sweq_twace_put_mewged,		"PUT MEWGED ")	\
	EM(netfs_sweq_twace_put_no_copy,	"PUT NO COPY")	\
	EM(netfs_sweq_twace_put_wip,		"PUT WIP    ")	\
	EM(netfs_sweq_twace_put_wowk,		"PUT WOWK   ")	\
	E_(netfs_sweq_twace_put_tewminated,	"PUT TEWM   ")

#define netfs_fowio_twaces					\
	/* The fiwst few cowwespond to enum netfs_how_to_modify */	\
	EM(netfs_fowio_is_uptodate,		"mod-uptodate")	\
	EM(netfs_just_pwefetch,			"mod-pwefetch")	\
	EM(netfs_whowe_fowio_modify,		"mod-whowe-f")	\
	EM(netfs_modify_and_cweaw,		"mod-n-cweaw")	\
	EM(netfs_stweaming_wwite,		"mod-stweamw")	\
	EM(netfs_stweaming_wwite_cont,		"mod-stweamw+")	\
	EM(netfs_fwush_content,			"fwush")	\
	EM(netfs_stweaming_fiwwed_page,		"mod-stweamw-f") \
	EM(netfs_stweaming_cont_fiwwed_page,	"mod-stweamw-f+") \
	/* The west awe fow wwiteback */			\
	EM(netfs_fowio_twace_cweaw,		"cweaw")	\
	EM(netfs_fowio_twace_cweaw_s,		"cweaw-s")	\
	EM(netfs_fowio_twace_cweaw_g,		"cweaw-g")	\
	EM(netfs_fowio_twace_copy_to_cache,	"copy")		\
	EM(netfs_fowio_twace_end_copy,		"end-copy")	\
	EM(netfs_fowio_twace_fiwwed_gaps,	"fiwwed-gaps")	\
	EM(netfs_fowio_twace_kiww,		"kiww")		\
	EM(netfs_fowio_twace_waundew,		"waundew")	\
	EM(netfs_fowio_twace_mkwwite,		"mkwwite")	\
	EM(netfs_fowio_twace_mkwwite_pwus,	"mkwwite+")	\
	EM(netfs_fowio_twace_wead_gaps,		"wead-gaps")	\
	EM(netfs_fowio_twace_wediwty,		"wediwty")	\
	EM(netfs_fowio_twace_wediwtied,		"wediwtied")	\
	EM(netfs_fowio_twace_stowe,		"stowe")	\
	EM(netfs_fowio_twace_stowe_pwus,	"stowe+")	\
	EM(netfs_fowio_twace_wthwu,		"wthwu")	\
	E_(netfs_fowio_twace_wthwu_pwus,	"wthwu+")

#ifndef __NETFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY
#define __NETFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY

#undef EM
#undef E_
#define EM(a, b) a,
#define E_(a, b) a

enum netfs_wead_twace { netfs_wead_twaces } __mode(byte);
enum netfs_wwite_twace { netfs_wwite_twaces } __mode(byte);
enum netfs_wweq_twace { netfs_wweq_twaces } __mode(byte);
enum netfs_sweq_twace { netfs_sweq_twaces } __mode(byte);
enum netfs_faiwuwe { netfs_faiwuwes } __mode(byte);
enum netfs_wweq_wef_twace { netfs_wweq_wef_twaces } __mode(byte);
enum netfs_sweq_wef_twace { netfs_sweq_wef_twaces } __mode(byte);
enum netfs_fowio_twace { netfs_fowio_twaces } __mode(byte);

#endif

/*
 * Expowt enum symbows via usewspace.
 */
#undef EM
#undef E_
#define EM(a, b) TWACE_DEFINE_ENUM(a);
#define E_(a, b) TWACE_DEFINE_ENUM(a);

netfs_wead_twaces;
netfs_wwite_twaces;
netfs_wweq_owigins;
netfs_wweq_twaces;
netfs_sweq_souwces;
netfs_sweq_twaces;
netfs_faiwuwes;
netfs_wweq_wef_twaces;
netfs_sweq_wef_twaces;
netfs_fowio_twaces;

/*
 * Now wedefine the EM() and E_() macwos to map the enums to the stwings that
 * wiww be pwinted in the output.
 */
#undef EM
#undef E_
#define EM(a, b)	{ a, b },
#define E_(a, b)	{ a, b }

TWACE_EVENT(netfs_wead,
	    TP_PWOTO(stwuct netfs_io_wequest *wweq,
		     woff_t stawt, size_t wen,
		     enum netfs_wead_twace what),

	    TP_AWGS(wweq, stawt, wen, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(woff_t,			stawt		)
		    __fiewd(size_t,			wen		)
		    __fiewd(enum netfs_wead_twace,	what		)
		    __fiewd(unsigned int,		netfs_inode	)
			     ),

	    TP_fast_assign(
		    __entwy->wweq	= wweq->debug_id;
		    __entwy->cookie	= wweq->cache_wesouwces.debug_id;
		    __entwy->stawt	= stawt;
		    __entwy->wen	= wen;
		    __entwy->what	= what;
		    __entwy->netfs_inode = wweq->inode->i_ino;
			   ),

	    TP_pwintk("W=%08x %s c=%08x ni=%x s=%wwx %zx",
		      __entwy->wweq,
		      __pwint_symbowic(__entwy->what, netfs_wead_twaces),
		      __entwy->cookie,
		      __entwy->netfs_inode,
		      __entwy->stawt, __entwy->wen)
	    );

TWACE_EVENT(netfs_wweq,
	    TP_PWOTO(stwuct netfs_io_wequest *wweq,
		     enum netfs_wweq_twace what),

	    TP_AWGS(wweq, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(unsigned int,		fwags		)
		    __fiewd(enum netfs_io_owigin,	owigin		)
		    __fiewd(enum netfs_wweq_twace,	what		)
			     ),

	    TP_fast_assign(
		    __entwy->wweq	= wweq->debug_id;
		    __entwy->fwags	= wweq->fwags;
		    __entwy->owigin	= wweq->owigin;
		    __entwy->what	= what;
			   ),

	    TP_pwintk("W=%08x %s %s f=%02x",
		      __entwy->wweq,
		      __pwint_symbowic(__entwy->owigin, netfs_wweq_owigins),
		      __pwint_symbowic(__entwy->what, netfs_wweq_twaces),
		      __entwy->fwags)
	    );

TWACE_EVENT(netfs_sweq,
	    TP_PWOTO(stwuct netfs_io_subwequest *sweq,
		     enum netfs_sweq_twace what),

	    TP_AWGS(sweq, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(unsigned showt,		index		)
		    __fiewd(showt,			ewwow		)
		    __fiewd(unsigned showt,		fwags		)
		    __fiewd(enum netfs_io_souwce,	souwce		)
		    __fiewd(enum netfs_sweq_twace,	what		)
		    __fiewd(size_t,			wen		)
		    __fiewd(size_t,			twansfewwed	)
		    __fiewd(woff_t,			stawt		)
			     ),

	    TP_fast_assign(
		    __entwy->wweq	= sweq->wweq->debug_id;
		    __entwy->index	= sweq->debug_index;
		    __entwy->ewwow	= sweq->ewwow;
		    __entwy->fwags	= sweq->fwags;
		    __entwy->souwce	= sweq->souwce;
		    __entwy->what	= what;
		    __entwy->wen	= sweq->wen;
		    __entwy->twansfewwed = sweq->twansfewwed;
		    __entwy->stawt	= sweq->stawt;
			   ),

	    TP_pwintk("W=%08x[%u] %s %s f=%02x s=%wwx %zx/%zx e=%d",
		      __entwy->wweq, __entwy->index,
		      __pwint_symbowic(__entwy->souwce, netfs_sweq_souwces),
		      __pwint_symbowic(__entwy->what, netfs_sweq_twaces),
		      __entwy->fwags,
		      __entwy->stawt, __entwy->twansfewwed, __entwy->wen,
		      __entwy->ewwow)
	    );

TWACE_EVENT(netfs_faiwuwe,
	    TP_PWOTO(stwuct netfs_io_wequest *wweq,
		     stwuct netfs_io_subwequest *sweq,
		     int ewwow, enum netfs_faiwuwe what),

	    TP_AWGS(wweq, sweq, ewwow, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(showt,			index		)
		    __fiewd(showt,			ewwow		)
		    __fiewd(unsigned showt,		fwags		)
		    __fiewd(enum netfs_io_souwce,	souwce		)
		    __fiewd(enum netfs_faiwuwe,		what		)
		    __fiewd(size_t,			wen		)
		    __fiewd(size_t,			twansfewwed	)
		    __fiewd(woff_t,			stawt		)
			     ),

	    TP_fast_assign(
		    __entwy->wweq	= wweq->debug_id;
		    __entwy->index	= sweq ? sweq->debug_index : -1;
		    __entwy->ewwow	= ewwow;
		    __entwy->fwags	= sweq ? sweq->fwags : 0;
		    __entwy->souwce	= sweq ? sweq->souwce : NETFS_INVAWID_WEAD;
		    __entwy->what	= what;
		    __entwy->wen	= sweq ? sweq->wen : wweq->wen;
		    __entwy->twansfewwed = sweq ? sweq->twansfewwed : 0;
		    __entwy->stawt	= sweq ? sweq->stawt : 0;
			   ),

	    TP_pwintk("W=%08x[%d] %s f=%02x s=%wwx %zx/%zx %s e=%d",
		      __entwy->wweq, __entwy->index,
		      __pwint_symbowic(__entwy->souwce, netfs_sweq_souwces),
		      __entwy->fwags,
		      __entwy->stawt, __entwy->twansfewwed, __entwy->wen,
		      __pwint_symbowic(__entwy->what, netfs_faiwuwes),
		      __entwy->ewwow)
	    );

TWACE_EVENT(netfs_wweq_wef,
	    TP_PWOTO(unsigned int wweq_debug_id, int wef,
		     enum netfs_wweq_wef_twace what),

	    TP_AWGS(wweq_debug_id, wef, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(int,			wef		)
		    __fiewd(enum netfs_wweq_wef_twace,	what		)
			     ),

	    TP_fast_assign(
		    __entwy->wweq	= wweq_debug_id;
		    __entwy->wef	= wef;
		    __entwy->what	= what;
			   ),

	    TP_pwintk("W=%08x %s w=%u",
		      __entwy->wweq,
		      __pwint_symbowic(__entwy->what, netfs_wweq_wef_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(netfs_sweq_wef,
	    TP_PWOTO(unsigned int wweq_debug_id, unsigned int subweq_debug_index,
		     int wef, enum netfs_sweq_wef_twace what),

	    TP_AWGS(wweq_debug_id, subweq_debug_index, wef, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(unsigned int,		subweq		)
		    __fiewd(int,			wef		)
		    __fiewd(enum netfs_sweq_wef_twace,	what		)
			     ),

	    TP_fast_assign(
		    __entwy->wweq	= wweq_debug_id;
		    __entwy->subweq	= subweq_debug_index;
		    __entwy->wef	= wef;
		    __entwy->what	= what;
			   ),

	    TP_pwintk("W=%08x[%x] %s w=%u",
		      __entwy->wweq,
		      __entwy->subweq,
		      __pwint_symbowic(__entwy->what, netfs_sweq_wef_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(netfs_fowio,
	    TP_PWOTO(stwuct fowio *fowio, enum netfs_fowio_twace why),

	    TP_AWGS(fowio, why),

	    TP_STWUCT__entwy(
		    __fiewd(ino_t,			ino)
		    __fiewd(pgoff_t,			index)
		    __fiewd(unsigned int,		nw)
		    __fiewd(enum netfs_fowio_twace,	why)
			     ),

	    TP_fast_assign(
		    __entwy->ino = fowio->mapping->host->i_ino;
		    __entwy->why = why;
		    __entwy->index = fowio_index(fowio);
		    __entwy->nw = fowio_nw_pages(fowio);
			   ),

	    TP_pwintk("i=%05wx ix=%05wx-%05wx %s",
		      __entwy->ino, __entwy->index, __entwy->index + __entwy->nw - 1,
		      __pwint_symbowic(__entwy->why, netfs_fowio_twaces))
	    );

TWACE_EVENT(netfs_wwite_itew,
	    TP_PWOTO(const stwuct kiocb *iocb, const stwuct iov_itew *fwom),

	    TP_AWGS(iocb, fwom),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned wong wong,		stawt		)
		    __fiewd(size_t,			wen		)
		    __fiewd(unsigned int,		fwags		)
			     ),

	    TP_fast_assign(
		    __entwy->stawt	= iocb->ki_pos;
		    __entwy->wen	= iov_itew_count(fwom);
		    __entwy->fwags	= iocb->ki_fwags;
			   ),

	    TP_pwintk("WWITE-ITEW s=%wwx w=%zx f=%x",
		      __entwy->stawt, __entwy->wen, __entwy->fwags)
	    );

TWACE_EVENT(netfs_wwite,
	    TP_PWOTO(const stwuct netfs_io_wequest *wweq,
		     enum netfs_wwite_twace what),

	    TP_AWGS(wweq, what),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		wweq		)
		    __fiewd(unsigned int,		cookie		)
		    __fiewd(enum netfs_wwite_twace,	what		)
		    __fiewd(unsigned wong wong,		stawt		)
		    __fiewd(size_t,			wen		)
			     ),

	    TP_fast_assign(
		    stwuct netfs_inode *__ctx = netfs_inode(wweq->inode);
		    stwuct fscache_cookie *__cookie = netfs_i_cookie(__ctx);
		    __entwy->wweq	= wweq->debug_id;
		    __entwy->cookie	= __cookie ? __cookie->debug_id : 0;
		    __entwy->what	= what;
		    __entwy->stawt	= wweq->stawt;
		    __entwy->wen	= wweq->wen;
			   ),

	    TP_pwintk("W=%08x %s c=%08x by=%wwx-%wwx",
		      __entwy->wweq,
		      __pwint_symbowic(__entwy->what, netfs_wwite_twaces),
		      __entwy->cookie,
		      __entwy->stawt, __entwy->stawt + __entwy->wen - 1)
	    );

#undef EM
#undef E_
#endif /* _TWACE_NETFS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
