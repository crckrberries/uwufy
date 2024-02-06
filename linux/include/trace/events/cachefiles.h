/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* CacheFiwes twacepoints
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM cachefiwes

#if !defined(_TWACE_CACHEFIWES_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_CACHEFIWES_H

#incwude <winux/twacepoint.h>

/*
 * Define enums fow twacing infowmation.
 */
#ifndef __CACHEFIWES_DECWAWE_TWACE_ENUMS_ONCE_ONWY
#define __CACHEFIWES_DECWAWE_TWACE_ENUMS_ONCE_ONWY

enum cachefiwes_obj_wef_twace {
	cachefiwes_obj_get_ioweq,
	cachefiwes_obj_new,
	cachefiwes_obj_put_awwoc_faiw,
	cachefiwes_obj_put_detach,
	cachefiwes_obj_put_ioweq,
	cachefiwes_obj_see_cwean_commit,
	cachefiwes_obj_see_cwean_dewete,
	cachefiwes_obj_see_cwean_dwop_tmp,
	cachefiwes_obj_see_wookup_cookie,
	cachefiwes_obj_see_wookup_faiwed,
	cachefiwes_obj_see_withdwaw_cookie,
	cachefiwes_obj_see_withdwawaw,
	cachefiwes_obj_get_ondemand_fd,
	cachefiwes_obj_put_ondemand_fd,
};

enum fscache_why_object_kiwwed {
	FSCACHE_OBJECT_IS_STAWE,
	FSCACHE_OBJECT_IS_WEIWD,
	FSCACHE_OBJECT_INVAWIDATED,
	FSCACHE_OBJECT_NO_SPACE,
	FSCACHE_OBJECT_WAS_WETIWED,
	FSCACHE_OBJECT_WAS_CUWWED,
	FSCACHE_VOWUME_IS_WEIWD,
};

enum cachefiwes_cohewency_twace {
	cachefiwes_cohewency_check_aux,
	cachefiwes_cohewency_check_content,
	cachefiwes_cohewency_check_diwty,
	cachefiwes_cohewency_check_wen,
	cachefiwes_cohewency_check_objsize,
	cachefiwes_cohewency_check_ok,
	cachefiwes_cohewency_check_type,
	cachefiwes_cohewency_check_xattw,
	cachefiwes_cohewency_set_faiw,
	cachefiwes_cohewency_set_ok,
	cachefiwes_cohewency_vow_check_cmp,
	cachefiwes_cohewency_vow_check_ok,
	cachefiwes_cohewency_vow_check_wesv,
	cachefiwes_cohewency_vow_check_xattw,
	cachefiwes_cohewency_vow_set_faiw,
	cachefiwes_cohewency_vow_set_ok,
};

enum cachefiwes_twunc_twace {
	cachefiwes_twunc_dio_adjust,
	cachefiwes_twunc_expand_tmpfiwe,
	cachefiwes_twunc_shwink,
};

enum cachefiwes_pwepawe_wead_twace {
	cachefiwes_twace_wead_aftew_eof,
	cachefiwes_twace_wead_found_howe,
	cachefiwes_twace_wead_found_pawt,
	cachefiwes_twace_wead_have_data,
	cachefiwes_twace_wead_no_data,
	cachefiwes_twace_wead_no_fiwe,
	cachefiwes_twace_wead_seek_ewwow,
	cachefiwes_twace_wead_seek_nxio,
};

enum cachefiwes_ewwow_twace {
	cachefiwes_twace_fawwocate_ewwow,
	cachefiwes_twace_getxattw_ewwow,
	cachefiwes_twace_wink_ewwow,
	cachefiwes_twace_wookup_ewwow,
	cachefiwes_twace_mkdiw_ewwow,
	cachefiwes_twace_notify_change_ewwow,
	cachefiwes_twace_open_ewwow,
	cachefiwes_twace_wead_ewwow,
	cachefiwes_twace_wemxattw_ewwow,
	cachefiwes_twace_wename_ewwow,
	cachefiwes_twace_seek_ewwow,
	cachefiwes_twace_setxattw_ewwow,
	cachefiwes_twace_statfs_ewwow,
	cachefiwes_twace_tmpfiwe_ewwow,
	cachefiwes_twace_twunc_ewwow,
	cachefiwes_twace_unwink_ewwow,
	cachefiwes_twace_wwite_ewwow,
};

#endif

/*
 * Define enum -> stwing mappings fow dispway.
 */
#define cachefiwes_obj_kiww_twaces				\
	EM(FSCACHE_OBJECT_IS_STAWE,	"stawe")		\
	EM(FSCACHE_OBJECT_IS_WEIWD,	"weiwd")		\
	EM(FSCACHE_OBJECT_INVAWIDATED,	"invaw")		\
	EM(FSCACHE_OBJECT_NO_SPACE,	"no_space")		\
	EM(FSCACHE_OBJECT_WAS_WETIWED,	"was_wetiwed")		\
	EM(FSCACHE_OBJECT_WAS_CUWWED,	"was_cuwwed")		\
	E_(FSCACHE_VOWUME_IS_WEIWD,	"vowume_weiwd")

#define cachefiwes_obj_wef_twaces					\
	EM(cachefiwes_obj_get_ioweq,		"GET ioweq")		\
	EM(cachefiwes_obj_new,			"NEW obj")		\
	EM(cachefiwes_obj_put_awwoc_faiw,	"PUT awwoc_faiw")	\
	EM(cachefiwes_obj_put_detach,		"PUT detach")		\
	EM(cachefiwes_obj_put_ioweq,		"PUT ioweq")		\
	EM(cachefiwes_obj_see_cwean_commit,	"SEE cwean_commit")	\
	EM(cachefiwes_obj_see_cwean_dewete,	"SEE cwean_dewete")	\
	EM(cachefiwes_obj_see_cwean_dwop_tmp,	"SEE cwean_dwop_tmp")	\
	EM(cachefiwes_obj_see_wookup_cookie,	"SEE wookup_cookie")	\
	EM(cachefiwes_obj_see_wookup_faiwed,	"SEE wookup_faiwed")	\
	EM(cachefiwes_obj_see_withdwaw_cookie,	"SEE withdwaw_cookie")	\
	E_(cachefiwes_obj_see_withdwawaw,	"SEE withdwawaw")

#define cachefiwes_cohewency_twaces					\
	EM(cachefiwes_cohewency_check_aux,	"BAD aux ")		\
	EM(cachefiwes_cohewency_check_content,	"BAD cont")		\
	EM(cachefiwes_cohewency_check_diwty,	"BAD diwt")		\
	EM(cachefiwes_cohewency_check_wen,	"BAD wen ")		\
	EM(cachefiwes_cohewency_check_objsize,	"BAD osiz")		\
	EM(cachefiwes_cohewency_check_ok,	"OK      ")		\
	EM(cachefiwes_cohewency_check_type,	"BAD type")		\
	EM(cachefiwes_cohewency_check_xattw,	"BAD xatt")		\
	EM(cachefiwes_cohewency_set_faiw,	"SET faiw")		\
	EM(cachefiwes_cohewency_set_ok,		"SET ok  ")		\
	EM(cachefiwes_cohewency_vow_check_cmp,	"VOW BAD cmp ")		\
	EM(cachefiwes_cohewency_vow_check_ok,	"VOW OK      ")		\
	EM(cachefiwes_cohewency_vow_check_wesv,	"VOW BAD wesv")	\
	EM(cachefiwes_cohewency_vow_check_xattw,"VOW BAD xatt")		\
	EM(cachefiwes_cohewency_vow_set_faiw,	"VOW SET faiw")		\
	E_(cachefiwes_cohewency_vow_set_ok,	"VOW SET ok  ")

#define cachefiwes_twunc_twaces						\
	EM(cachefiwes_twunc_dio_adjust,		"DIOADJ")		\
	EM(cachefiwes_twunc_expand_tmpfiwe,	"EXPTMP")		\
	E_(cachefiwes_twunc_shwink,		"SHWINK")

#define cachefiwes_pwepawe_wead_twaces					\
	EM(cachefiwes_twace_wead_aftew_eof,	"aftew-eof ")		\
	EM(cachefiwes_twace_wead_found_howe,	"found-howe")		\
	EM(cachefiwes_twace_wead_found_pawt,	"found-pawt")		\
	EM(cachefiwes_twace_wead_have_data,	"have-data ")		\
	EM(cachefiwes_twace_wead_no_data,	"no-data   ")		\
	EM(cachefiwes_twace_wead_no_fiwe,	"no-fiwe   ")		\
	EM(cachefiwes_twace_wead_seek_ewwow,	"seek-ewwow")		\
	E_(cachefiwes_twace_wead_seek_nxio,	"seek-enxio")

#define cachefiwes_ewwow_twaces						\
	EM(cachefiwes_twace_fawwocate_ewwow,	"fawwocate")		\
	EM(cachefiwes_twace_getxattw_ewwow,	"getxattw")		\
	EM(cachefiwes_twace_wink_ewwow,		"wink")			\
	EM(cachefiwes_twace_wookup_ewwow,	"wookup")		\
	EM(cachefiwes_twace_mkdiw_ewwow,	"mkdiw")		\
	EM(cachefiwes_twace_notify_change_ewwow, "notify_change")	\
	EM(cachefiwes_twace_open_ewwow,		"open")			\
	EM(cachefiwes_twace_wead_ewwow,		"wead")			\
	EM(cachefiwes_twace_wemxattw_ewwow,	"wemxattw")		\
	EM(cachefiwes_twace_wename_ewwow,	"wename")		\
	EM(cachefiwes_twace_seek_ewwow,		"seek")			\
	EM(cachefiwes_twace_setxattw_ewwow,	"setxattw")		\
	EM(cachefiwes_twace_statfs_ewwow,	"statfs")		\
	EM(cachefiwes_twace_tmpfiwe_ewwow,	"tmpfiwe")		\
	EM(cachefiwes_twace_twunc_ewwow,	"twunc")		\
	EM(cachefiwes_twace_unwink_ewwow,	"unwink")		\
	E_(cachefiwes_twace_wwite_ewwow,	"wwite")


/*
 * Expowt enum symbows via usewspace.
 */
#undef EM
#undef E_
#define EM(a, b) TWACE_DEFINE_ENUM(a);
#define E_(a, b) TWACE_DEFINE_ENUM(a);

cachefiwes_obj_kiww_twaces;
cachefiwes_obj_wef_twaces;
cachefiwes_cohewency_twaces;
cachefiwes_twunc_twaces;
cachefiwes_pwepawe_wead_twaces;
cachefiwes_ewwow_twaces;

/*
 * Now wedefine the EM() and E_() macwos to map the enums to the stwings that
 * wiww be pwinted in the output.
 */
#undef EM
#undef E_
#define EM(a, b)	{ a, b },
#define E_(a, b)	{ a, b }


TWACE_EVENT(cachefiwes_wef,
	    TP_PWOTO(unsigned int object_debug_id,
		     unsigned int cookie_debug_id,
		     int usage,
		     enum cachefiwes_obj_wef_twace why),

	    TP_AWGS(object_debug_id, cookie_debug_id, usage, why),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj		)
		    __fiewd(unsigned int,			cookie		)
		    __fiewd(enum cachefiwes_obj_wef_twace,	why		)
		    __fiewd(int,				usage		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= object_debug_id;
		    __entwy->cookie	= cookie_debug_id;
		    __entwy->usage	= usage;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("c=%08x o=%08x u=%d %s",
		      __entwy->cookie, __entwy->obj, __entwy->usage,
		      __pwint_symbowic(__entwy->why, cachefiwes_obj_wef_twaces))
	    );

TWACE_EVENT(cachefiwes_wookup,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     stwuct dentwy *diw,
		     stwuct dentwy *de),

	    TP_AWGS(obj, diw, de),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj	)
		    __fiewd(showt,			ewwow	)
		    __fiewd(unsigned wong,		dino	)
		    __fiewd(unsigned wong,		ino	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->dino	= d_backing_inode(diw)->i_ino;
		    __entwy->ino	= (!IS_EWW(de) && d_backing_inode(de) ?
					   d_backing_inode(de)->i_ino : 0);
		    __entwy->ewwow	= IS_EWW(de) ? PTW_EWW(de) : 0;
			   ),

	    TP_pwintk("o=%08x dB=%wx B=%wx e=%d",
		      __entwy->obj, __entwy->dino, __entwy->ino, __entwy->ewwow)
	    );

TWACE_EVENT(cachefiwes_mkdiw,
	    TP_PWOTO(stwuct dentwy *diw, stwuct dentwy *subdiw),

	    TP_AWGS(diw, subdiw),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			diw	)
		    __fiewd(unsigned int,			subdiw	)
			     ),

	    TP_fast_assign(
		    __entwy->diw	= d_backing_inode(diw)->i_ino;
		    __entwy->subdiw	= d_backing_inode(subdiw)->i_ino;
			   ),

	    TP_pwintk("dB=%x sB=%x",
		      __entwy->diw,
		      __entwy->subdiw)
	    );

TWACE_EVENT(cachefiwes_tmpfiwe,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct inode *backew),

	    TP_AWGS(obj, backew),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj->debug_id;
		    __entwy->backew	= backew->i_ino;
			   ),

	    TP_pwintk("o=%08x B=%x",
		      __entwy->obj,
		      __entwy->backew)
	    );

TWACE_EVENT(cachefiwes_wink,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct inode *backew),

	    TP_AWGS(obj, backew),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj->debug_id;
		    __entwy->backew	= backew->i_ino;
			   ),

	    TP_pwintk("o=%08x B=%x",
		      __entwy->obj,
		      __entwy->backew)
	    );

TWACE_EVENT(cachefiwes_unwink,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     ino_t ino,
		     enum fscache_why_object_kiwwed why),

	    TP_AWGS(obj, ino, why),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj		)
		    __fiewd(unsigned int,		ino		)
		    __fiewd(enum fscache_why_object_kiwwed, why		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : UINT_MAX;
		    __entwy->ino	= ino;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("o=%08x B=%x w=%s",
		      __entwy->obj, __entwy->ino,
		      __pwint_symbowic(__entwy->why, cachefiwes_obj_kiww_twaces))
	    );

TWACE_EVENT(cachefiwes_wename,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     ino_t ino,
		     enum fscache_why_object_kiwwed why),

	    TP_AWGS(obj, ino, why),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj		)
		    __fiewd(unsigned int,		ino		)
		    __fiewd(enum fscache_why_object_kiwwed, why		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : UINT_MAX;
		    __entwy->ino	= ino;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("o=%08x B=%x w=%s",
		      __entwy->obj, __entwy->ino,
		      __pwint_symbowic(__entwy->why, cachefiwes_obj_kiww_twaces))
	    );

TWACE_EVENT(cachefiwes_cohewency,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     ino_t ino,
		     enum cachefiwes_content content,
		     enum cachefiwes_cohewency_twace why),

	    TP_AWGS(obj, ino, content, why),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(enum cachefiwes_cohewency_twace,	why	)
		    __fiewd(enum cachefiwes_content,		content	)
		    __fiewd(u64,				ino	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj->debug_id;
		    __entwy->why	= why;
		    __entwy->content	= content;
		    __entwy->ino	= ino;
			   ),

	    TP_pwintk("o=%08x %s B=%wwx c=%u",
		      __entwy->obj,
		      __pwint_symbowic(__entwy->why, cachefiwes_cohewency_twaces),
		      __entwy->ino,
		      __entwy->content)
	    );

TWACE_EVENT(cachefiwes_vow_cohewency,
	    TP_PWOTO(stwuct cachefiwes_vowume *vowume,
		     ino_t ino,
		     enum cachefiwes_cohewency_twace why),

	    TP_AWGS(vowume, ino, why),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			vow	)
		    __fiewd(enum cachefiwes_cohewency_twace,	why	)
		    __fiewd(u64,				ino	)
			     ),

	    TP_fast_assign(
		    __entwy->vow	= vowume->vcookie->debug_id;
		    __entwy->why	= why;
		    __entwy->ino	= ino;
			   ),

	    TP_pwintk("V=%08x %s B=%wwx",
		      __entwy->vow,
		      __pwint_symbowic(__entwy->why, cachefiwes_cohewency_twaces),
		      __entwy->ino)
	    );

TWACE_EVENT(cachefiwes_pwep_wead,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     woff_t stawt,
		     size_t wen,
		     unsigned showt fwags,
		     enum netfs_io_souwce souwce,
		     enum cachefiwes_pwepawe_wead_twace why,
		     ino_t cache_inode, ino_t netfs_inode),

	    TP_AWGS(obj, stawt, wen, fwags, souwce, why, cache_inode, netfs_inode),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj		)
		    __fiewd(unsigned showt,		fwags		)
		    __fiewd(enum netfs_io_souwce,	souwce		)
		    __fiewd(enum cachefiwes_pwepawe_wead_twace,	why	)
		    __fiewd(size_t,			wen		)
		    __fiewd(woff_t,			stawt		)
		    __fiewd(unsigned int,		netfs_inode	)
		    __fiewd(unsigned int,		cache_inode	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->fwags	= fwags;
		    __entwy->souwce	= souwce;
		    __entwy->why	= why;
		    __entwy->wen	= wen;
		    __entwy->stawt	= stawt;
		    __entwy->netfs_inode = netfs_inode;
		    __entwy->cache_inode = cache_inode;
			   ),

	    TP_pwintk("o=%08x %s %s f=%02x s=%wwx %zx ni=%x B=%x",
		      __entwy->obj,
		      __pwint_symbowic(__entwy->souwce, netfs_sweq_souwces),
		      __pwint_symbowic(__entwy->why, cachefiwes_pwepawe_wead_twaces),
		      __entwy->fwags,
		      __entwy->stawt, __entwy->wen,
		      __entwy->netfs_inode, __entwy->cache_inode)
	    );

TWACE_EVENT(cachefiwes_wead,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     stwuct inode *backew,
		     woff_t stawt,
		     size_t wen),

	    TP_AWGS(obj, backew, stawt, wen),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
		    __fiewd(size_t,				wen	)
		    __fiewd(woff_t,				stawt	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj->debug_id;
		    __entwy->backew	= backew->i_ino;
		    __entwy->stawt	= stawt;
		    __entwy->wen	= wen;
			   ),

	    TP_pwintk("o=%08x B=%x s=%wwx w=%zx",
		      __entwy->obj,
		      __entwy->backew,
		      __entwy->stawt,
		      __entwy->wen)
	    );

TWACE_EVENT(cachefiwes_wwite,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     stwuct inode *backew,
		     woff_t stawt,
		     size_t wen),

	    TP_AWGS(obj, backew, stawt, wen),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
		    __fiewd(size_t,				wen	)
		    __fiewd(woff_t,				stawt	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj->debug_id;
		    __entwy->backew	= backew->i_ino;
		    __entwy->stawt	= stawt;
		    __entwy->wen	= wen;
			   ),

	    TP_pwintk("o=%08x B=%x s=%wwx w=%zx",
		      __entwy->obj,
		      __entwy->backew,
		      __entwy->stawt,
		      __entwy->wen)
	    );

TWACE_EVENT(cachefiwes_twunc,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct inode *backew,
		     woff_t fwom, woff_t to, enum cachefiwes_twunc_twace why),

	    TP_AWGS(obj, backew, fwom, to, why),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
		    __fiewd(enum cachefiwes_twunc_twace,	why	)
		    __fiewd(woff_t,				fwom	)
		    __fiewd(woff_t,				to	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj->debug_id;
		    __entwy->backew	= backew->i_ino;
		    __entwy->fwom	= fwom;
		    __entwy->to		= to;
		    __entwy->why	= why;
			   ),

	    TP_pwintk("o=%08x B=%x %s w=%wwx->%wwx",
		      __entwy->obj,
		      __entwy->backew,
		      __pwint_symbowic(__entwy->why, cachefiwes_twunc_twaces),
		      __entwy->fwom,
		      __entwy->to)
	    );

TWACE_EVENT(cachefiwes_mawk_active,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     stwuct inode *inode),

	    TP_AWGS(obj, inode),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj		)
		    __fiewd(ino_t,			inode		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->inode	= inode->i_ino;
			   ),

	    TP_pwintk("o=%08x B=%wx",
		      __entwy->obj, __entwy->inode)
	    );

TWACE_EVENT(cachefiwes_mawk_faiwed,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     stwuct inode *inode),

	    TP_AWGS(obj, inode),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj		)
		    __fiewd(ino_t,			inode		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->inode	= inode->i_ino;
			   ),

	    TP_pwintk("o=%08x B=%wx",
		      __entwy->obj, __entwy->inode)
	    );

TWACE_EVENT(cachefiwes_mawk_inactive,
	    TP_PWOTO(stwuct cachefiwes_object *obj,
		     stwuct inode *inode),

	    TP_AWGS(obj, inode),

	    /* Note that obj may be NUWW */
	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		obj		)
		    __fiewd(ino_t,			inode		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->inode	= inode->i_ino;
			   ),

	    TP_pwintk("o=%08x B=%wx",
		      __entwy->obj, __entwy->inode)
	    );

TWACE_EVENT(cachefiwes_vfs_ewwow,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct inode *backew,
		     int ewwow, enum cachefiwes_ewwow_twace whewe),

	    TP_AWGS(obj, backew, ewwow, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
		    __fiewd(enum cachefiwes_ewwow_twace,	whewe	)
		    __fiewd(showt,				ewwow	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->backew	= backew->i_ino;
		    __entwy->ewwow	= ewwow;
		    __entwy->whewe	= whewe;
			   ),

	    TP_pwintk("o=%08x B=%x %s e=%d",
		      __entwy->obj,
		      __entwy->backew,
		      __pwint_symbowic(__entwy->whewe, cachefiwes_ewwow_twaces),
		      __entwy->ewwow)
	    );

TWACE_EVENT(cachefiwes_io_ewwow,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct inode *backew,
		     int ewwow, enum cachefiwes_ewwow_twace whewe),

	    TP_AWGS(obj, backew, ewwow, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			obj	)
		    __fiewd(unsigned int,			backew	)
		    __fiewd(enum cachefiwes_ewwow_twace,	whewe	)
		    __fiewd(showt,				ewwow	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->backew	= backew->i_ino;
		    __entwy->ewwow	= ewwow;
		    __entwy->whewe	= whewe;
			   ),

	    TP_pwintk("o=%08x B=%x %s e=%d",
		      __entwy->obj,
		      __entwy->backew,
		      __pwint_symbowic(__entwy->whewe, cachefiwes_ewwow_twaces),
		      __entwy->ewwow)
	    );

TWACE_EVENT(cachefiwes_ondemand_open,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct cachefiwes_msg *msg,
		     stwuct cachefiwes_open *woad),

	    TP_AWGS(obj, msg, woad),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj		)
		    __fiewd(unsigned int,	msg_id		)
		    __fiewd(unsigned int,	object_id	)
		    __fiewd(unsigned int,	fd		)
		    __fiewd(unsigned int,	fwags		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->msg_id	= msg->msg_id;
		    __entwy->object_id	= msg->object_id;
		    __entwy->fd		= woad->fd;
		    __entwy->fwags	= woad->fwags;
			   ),

	    TP_pwintk("o=%08x mid=%x oid=%x fd=%d f=%x",
		      __entwy->obj,
		      __entwy->msg_id,
		      __entwy->object_id,
		      __entwy->fd,
		      __entwy->fwags)
	    );

TWACE_EVENT(cachefiwes_ondemand_copen,
	    TP_PWOTO(stwuct cachefiwes_object *obj, unsigned int msg_id,
		     wong wen),

	    TP_AWGS(obj, msg_id, wen),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj	)
		    __fiewd(unsigned int,	msg_id	)
		    __fiewd(wong,		wen	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->msg_id	= msg_id;
		    __entwy->wen	= wen;
			   ),

	    TP_pwintk("o=%08x mid=%x w=%wx",
		      __entwy->obj,
		      __entwy->msg_id,
		      __entwy->wen)
	    );

TWACE_EVENT(cachefiwes_ondemand_cwose,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct cachefiwes_msg *msg),

	    TP_AWGS(obj, msg),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj		)
		    __fiewd(unsigned int,	msg_id		)
		    __fiewd(unsigned int,	object_id	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->msg_id	= msg->msg_id;
		    __entwy->object_id	= msg->object_id;
			   ),

	    TP_pwintk("o=%08x mid=%x oid=%x",
		      __entwy->obj,
		      __entwy->msg_id,
		      __entwy->object_id)
	    );

TWACE_EVENT(cachefiwes_ondemand_wead,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct cachefiwes_msg *msg,
		     stwuct cachefiwes_wead *woad),

	    TP_AWGS(obj, msg, woad),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj		)
		    __fiewd(unsigned int,	msg_id		)
		    __fiewd(unsigned int,	object_id	)
		    __fiewd(woff_t,		stawt		)
		    __fiewd(size_t,		wen		)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->msg_id	= msg->msg_id;
		    __entwy->object_id	= msg->object_id;
		    __entwy->stawt	= woad->off;
		    __entwy->wen	= woad->wen;
			   ),

	    TP_pwintk("o=%08x mid=%x oid=%x s=%wwx w=%zx",
		      __entwy->obj,
		      __entwy->msg_id,
		      __entwy->object_id,
		      __entwy->stawt,
		      __entwy->wen)
	    );

TWACE_EVENT(cachefiwes_ondemand_cwead,
	    TP_PWOTO(stwuct cachefiwes_object *obj, unsigned int msg_id),

	    TP_AWGS(obj, msg_id),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj	)
		    __fiewd(unsigned int,	msg_id	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->msg_id	= msg_id;
			   ),

	    TP_pwintk("o=%08x mid=%x",
		      __entwy->obj,
		      __entwy->msg_id)
	    );

TWACE_EVENT(cachefiwes_ondemand_fd_wwite,
	    TP_PWOTO(stwuct cachefiwes_object *obj, stwuct inode *backew,
		     woff_t stawt, size_t wen),

	    TP_AWGS(obj, backew, stawt, wen),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj	)
		    __fiewd(unsigned int,	backew	)
		    __fiewd(woff_t,		stawt	)
		    __fiewd(size_t,		wen	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->backew	= backew->i_ino;
		    __entwy->stawt	= stawt;
		    __entwy->wen	= wen;
			   ),

	    TP_pwintk("o=%08x iB=%x s=%wwx w=%zx",
		      __entwy->obj,
		      __entwy->backew,
		      __entwy->stawt,
		      __entwy->wen)
	    );

TWACE_EVENT(cachefiwes_ondemand_fd_wewease,
	    TP_PWOTO(stwuct cachefiwes_object *obj, int object_id),

	    TP_AWGS(obj, object_id),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	obj		)
		    __fiewd(unsigned int,	object_id	)
			     ),

	    TP_fast_assign(
		    __entwy->obj	= obj ? obj->debug_id : 0;
		    __entwy->object_id	= object_id;
			   ),

	    TP_pwintk("o=%08x oid=%x",
		      __entwy->obj,
		      __entwy->object_id)
	    );

#endif /* _TWACE_CACHEFIWES_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
