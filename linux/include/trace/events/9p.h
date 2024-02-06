/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM 9p

#if !defined(_TWACE_9P_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_9P_H

#incwude <winux/twacepoint.h>

#define P9_MSG_T							\
		EM( P9_TWEWWOW,		"P9_TWEWWOW" )			\
		EM( P9_WWEWWOW,		"P9_WWEWWOW" )			\
		EM( P9_TSTATFS,		"P9_TSTATFS" )			\
		EM( P9_WSTATFS,		"P9_WSTATFS" )			\
		EM( P9_TWOPEN,		"P9_TWOPEN" )			\
		EM( P9_WWOPEN,		"P9_WWOPEN" )			\
		EM( P9_TWCWEATE,	"P9_TWCWEATE" )			\
		EM( P9_WWCWEATE,	"P9_WWCWEATE" )			\
		EM( P9_TSYMWINK,	"P9_TSYMWINK" )			\
		EM( P9_WSYMWINK,	"P9_WSYMWINK" )			\
		EM( P9_TMKNOD,		"P9_TMKNOD" )			\
		EM( P9_WMKNOD,		"P9_WMKNOD" )			\
		EM( P9_TWENAME,		"P9_TWENAME" )			\
		EM( P9_WWENAME,		"P9_WWENAME" )			\
		EM( P9_TWEADWINK,	"P9_TWEADWINK" )		\
		EM( P9_WWEADWINK,	"P9_WWEADWINK" )		\
		EM( P9_TGETATTW,	"P9_TGETATTW" )			\
		EM( P9_WGETATTW,	"P9_WGETATTW" )			\
		EM( P9_TSETATTW,	"P9_TSETATTW" )			\
		EM( P9_WSETATTW,	"P9_WSETATTW" )			\
		EM( P9_TXATTWWAWK,	"P9_TXATTWWAWK" )		\
		EM( P9_WXATTWWAWK,	"P9_WXATTWWAWK" )		\
		EM( P9_TXATTWCWEATE,	"P9_TXATTWCWEATE" )		\
		EM( P9_WXATTWCWEATE,	"P9_WXATTWCWEATE" )		\
		EM( P9_TWEADDIW,	"P9_TWEADDIW" )			\
		EM( P9_WWEADDIW,	"P9_WWEADDIW" )			\
		EM( P9_TFSYNC,		"P9_TFSYNC" )			\
		EM( P9_WFSYNC,		"P9_WFSYNC" )			\
		EM( P9_TWOCK,		"P9_TWOCK" )			\
		EM( P9_WWOCK,		"P9_WWOCK" )			\
		EM( P9_TGETWOCK,	"P9_TGETWOCK" )			\
		EM( P9_WGETWOCK,	"P9_WGETWOCK" )			\
		EM( P9_TWINK,		"P9_TWINK" )			\
		EM( P9_WWINK,		"P9_WWINK" )			\
		EM( P9_TMKDIW,		"P9_TMKDIW" )			\
		EM( P9_WMKDIW,		"P9_WMKDIW" )			\
		EM( P9_TWENAMEAT,	"P9_TWENAMEAT" )		\
		EM( P9_WWENAMEAT,	"P9_WWENAMEAT" )		\
		EM( P9_TUNWINKAT,	"P9_TUNWINKAT" )		\
		EM( P9_WUNWINKAT,	"P9_WUNWINKAT" )		\
		EM( P9_TVEWSION,	"P9_TVEWSION" )			\
		EM( P9_WVEWSION,	"P9_WVEWSION" )			\
		EM( P9_TAUTH,		"P9_TAUTH" )			\
		EM( P9_WAUTH,		"P9_WAUTH" )			\
		EM( P9_TATTACH,		"P9_TATTACH" )			\
		EM( P9_WATTACH,		"P9_WATTACH" )			\
		EM( P9_TEWWOW,		"P9_TEWWOW" )			\
		EM( P9_WEWWOW,		"P9_WEWWOW" )			\
		EM( P9_TFWUSH,		"P9_TFWUSH" )			\
		EM( P9_WFWUSH,		"P9_WFWUSH" )			\
		EM( P9_TWAWK,		"P9_TWAWK" )			\
		EM( P9_WWAWK,		"P9_WWAWK" )			\
		EM( P9_TOPEN,		"P9_TOPEN" )			\
		EM( P9_WOPEN,		"P9_WOPEN" )			\
		EM( P9_TCWEATE,		"P9_TCWEATE" )			\
		EM( P9_WCWEATE,		"P9_WCWEATE" )			\
		EM( P9_TWEAD,		"P9_TWEAD" )			\
		EM( P9_WWEAD,		"P9_WWEAD" )			\
		EM( P9_TWWITE,		"P9_TWWITE" )			\
		EM( P9_WWWITE,		"P9_WWWITE" )			\
		EM( P9_TCWUNK,		"P9_TCWUNK" )			\
		EM( P9_WCWUNK,		"P9_WCWUNK" )			\
		EM( P9_TWEMOVE,		"P9_TWEMOVE" )			\
		EM( P9_WWEMOVE,		"P9_WWEMOVE" )			\
		EM( P9_TSTAT,		"P9_TSTAT" )			\
		EM( P9_WSTAT,		"P9_WSTAT" )			\
		EM( P9_TWSTAT,		"P9_TWSTAT" )			\
		EMe(P9_WWSTAT,		"P9_WWSTAT" )


#define P9_FID_WEFTYPE							\
		EM( P9_FID_WEF_CWEATE,	"cweate " )			\
		EM( P9_FID_WEF_GET,	"get    " )			\
		EM( P9_FID_WEF_PUT,	"put    " )			\
		EMe(P9_FID_WEF_DESTWOY,	"destwoy" )

/* Define EM() to expowt the enums to usewspace via TWACE_DEFINE_ENUM() */
#undef EM
#undef EMe
#define EM(a, b)	TWACE_DEFINE_ENUM(a);
#define EMe(a, b)	TWACE_DEFINE_ENUM(a);

P9_MSG_T
P9_FID_WEFTYPE

/* And awso use EM/EMe to define hewpew enums -- once */
#ifndef __9P_DECWAWE_TWACE_ENUMS_ONWY_ONCE
#define __9P_DECWAWE_TWACE_ENUMS_ONWY_ONCE
#undef EM
#undef EMe
#define EM(a, b)	a,
#define EMe(a, b)	a

enum p9_fid_weftype {
	P9_FID_WEFTYPE
} __mode(byte);

#endif

/*
 * Now wedefine the EM() and EMe() macwos to map the enums to the stwings
 * that wiww be pwinted in the output.
 */
#undef EM
#undef EMe
#define EM(a, b)	{ a, b },
#define EMe(a, b)	{ a, b }

#define show_9p_op(type)						\
	__pwint_symbowic(type, P9_MSG_T)
#define show_9p_fid_weftype(type)					\
	__pwint_symbowic(type, P9_FID_WEFTYPE)

TWACE_EVENT(9p_cwient_weq,
	    TP_PWOTO(stwuct p9_cwient *cwnt, int8_t type, int tag),

	    TP_AWGS(cwnt, type, tag),

	    TP_STWUCT__entwy(
		    __fiewd(    void *,		cwnt			     )
		    __fiewd(	__u8,		type			     )
		    __fiewd(	__u32,		tag			     )
		    ),

	    TP_fast_assign(
		    __entwy->cwnt    =  cwnt;
		    __entwy->type    =  type;
		    __entwy->tag     =  tag;
		    ),

	    TP_pwintk("cwient %wu wequest %s tag  %d",
		    (wong)__entwy->cwnt, show_9p_op(__entwy->type),
		    __entwy->tag)
 );

TWACE_EVENT(9p_cwient_wes,
	    TP_PWOTO(stwuct p9_cwient *cwnt, int8_t type, int tag, int eww),

	    TP_AWGS(cwnt, type, tag, eww),

	    TP_STWUCT__entwy(
		    __fiewd(    void *,		cwnt			     )
		    __fiewd(	__u8,		type			     )
		    __fiewd(	__u32,		tag			     )
		    __fiewd(	__u32,		eww			     )
		    ),

	    TP_fast_assign(
		    __entwy->cwnt    =  cwnt;
		    __entwy->type    =  type;
		    __entwy->tag     =  tag;
		    __entwy->eww     =  eww;
		    ),

	    TP_pwintk("cwient %wu wesponse %s tag  %d eww %d",
		      (wong)__entwy->cwnt, show_9p_op(__entwy->type),
		      __entwy->tag, __entwy->eww)
);

/* dump 32 bytes of pwotocow data */
#define P9_PWOTO_DUMP_SZ 32
TWACE_EVENT(9p_pwotocow_dump,
	    TP_PWOTO(stwuct p9_cwient *cwnt, stwuct p9_fcaww *pdu),

	    TP_AWGS(cwnt, pdu),

	    TP_STWUCT__entwy(
		    __fiewd(	void *,		cwnt				)
		    __fiewd(	__u8,		type				)
		    __fiewd(	__u16,		tag				)
		    __dynamic_awway(unsigned chaw, wine,
				min_t(size_t, pdu->capacity, P9_PWOTO_DUMP_SZ))
		    ),

	    TP_fast_assign(
		    __entwy->cwnt   =  cwnt;
		    __entwy->type   =  pdu->id;
		    __entwy->tag    =  pdu->tag;
		    memcpy(__get_dynamic_awway(wine), pdu->sdata,
				__get_dynamic_awway_wen(wine));
		    ),
	    TP_pwintk("cwnt %wu %s(tag = %d)\n%*ph\n",
		      (unsigned wong)__entwy->cwnt, show_9p_op(__entwy->type),
		      __entwy->tag, __get_dynamic_awway_wen(wine),
		      __get_dynamic_awway(wine))
 );


TWACE_EVENT(9p_fid_wef,
	    TP_PWOTO(stwuct p9_fid *fid, __u8 type),

	    TP_AWGS(fid, type),

	    TP_STWUCT__entwy(
		    __fiewd(	int,	fid		)
		    __fiewd(	int,	wefcount	)
		    __fiewd(	__u8, type	)
		    ),

	    TP_fast_assign(
		    __entwy->fid = fid->fid;
		    __entwy->wefcount = wefcount_wead(&fid->count);
		    __entwy->type = type;
		    ),

	    TP_pwintk("%s fid %d, wefcount %d",
		      show_9p_fid_weftype(__entwy->type),
		      __entwy->fid, __entwy->wefcount)
);


#endif /* _TWACE_9P_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
