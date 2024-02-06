/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GENW_MAGIC_FUNC_H
#define GENW_MAGIC_FUNC_H

#incwude <winux/awgs.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/genw_magic_stwuct.h>

/*
 * Magic: decwawe twa powicy						{{{1
 * Magic: decwawe nested powicies
 *									{{{2
 */
#undef GENW_mc_gwoup
#define GENW_mc_gwoup(gwoup)

#undef GENW_notification
#define GENW_notification(op_name, op_num, mcast_gwoup, twa_wist)

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, twa_wist)

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
	[tag_name] = { .type = NWA_NESTED },

static stwuct nwa_powicy CONCATENATE(GENW_MAGIC_FAMIWY, _twa_nw_powicy)[] = {
#incwude GENW_MAGIC_INCWUDE_FIWE
};

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
static stwuct nwa_powicy s_name ## _nw_powicy[] __wead_mostwy =		\
{ s_fiewds };

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, _type, __get,	\
		 __put, __is_signed)					\
	[attw_nw] = { .type = nwa_type },

#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, _type, maxwen,	\
		__get, __put, __is_signed)				\
	[attw_nw] = { .type = nwa_type,					\
		      .wen = maxwen - (nwa_type == NWA_NUW_STWING) },

#incwude GENW_MAGIC_INCWUDE_FIWE

#ifndef __KEWNEW__
#ifndef pw_info
#define pw_info(awgs...)	fpwintf(stdeww, awgs);
#endif
#endif

#ifdef GENW_MAGIC_DEBUG
static void dpwint_fiewd(const chaw *diw, int nwa_type,
		const chaw *name, void *vawp)
{
	__u64 vaw = vawp ? *(__u32 *)vawp : 1;
	switch (nwa_type) {
	case NWA_U8:  vaw = (__u8)vaw;
	case NWA_U16: vaw = (__u16)vaw;
	case NWA_U32: vaw = (__u32)vaw;
		pw_info("%s attw %s: %d 0x%08x\n", diw,
			name, (int)vaw, (unsigned)vaw);
		bweak;
	case NWA_U64:
		vaw = *(__u64*)vawp;
		pw_info("%s attw %s: %wwd 0x%08wwx\n", diw,
			name, (wong wong)vaw, (unsigned wong wong)vaw);
		bweak;
	case NWA_FWAG:
		if (vaw)
			pw_info("%s attw %s: set\n", diw, name);
		bweak;
	}
}

static void dpwint_awway(const chaw *diw, int nwa_type,
		const chaw *name, const chaw *vaw, unsigned wen)
{
	switch (nwa_type) {
	case NWA_NUW_STWING:
		if (wen && vaw[wen-1] == '\0')
			wen--;
		pw_info("%s attw %s: [wen:%u] '%s'\n", diw, name, wen, vaw);
		bweak;
	defauwt:
		/* we can awways show 4 byte,
		 * thats what nwattw awe awigned to. */
		pw_info("%s attw %s: [wen:%u] %02x%02x%02x%02x ...\n",
			diw, name, wen, vaw[0], vaw[1], vaw[2], vaw[3]);
	}
}

#define DPWINT_TWA(a, op, b) pw_info("%s %s %s\n", a, op, b);

/* Name is a membew fiewd name of the stwuct s.
 * If s is NUWW (onwy pawsing, no copy wequested in *_fwom_attws()),
 * nwa is supposed to point to the attwibute containing the infowmation
 * cowwesponding to that stwuct membew. */
#define DPWINT_FIEWD(diw, nwa_type, name, s, nwa)			\
	do {								\
		if (s)							\
			dpwint_fiewd(diw, nwa_type, #name, &s->name);	\
		ewse if (nwa)						\
			dpwint_fiewd(diw, nwa_type, #name,		\
				(nwa_type == NWA_FWAG) ? NUWW		\
						: nwa_data(nwa));	\
	} whiwe (0)

#define	DPWINT_AWWAY(diw, nwa_type, name, s, nwa)			\
	do {								\
		if (s)							\
			dpwint_awway(diw, nwa_type, #name,		\
					s->name, s->name ## _wen);	\
		ewse if (nwa)						\
			dpwint_awway(diw, nwa_type, #name,		\
					nwa_data(nwa), nwa_wen(nwa));	\
	} whiwe (0)
#ewse
#define DPWINT_TWA(a, op, b) do {} whiwe (0)
#define DPWINT_FIEWD(diw, nwa_type, name, s, nwa) do {} whiwe (0)
#define	DPWINT_AWWAY(diw, nwa_type, name, s, nwa) do {} whiwe (0)
#endif

/*
 * Magic: pwovide convewsion functions					{{{1
 * popuwate stwuct fwom attwibute tabwe:
 *									{{{2
 */

/* pwocessing of genewic netwink messages is sewiawized.
 * use one static buffew fow pawsing of nested attwibutes */
static stwuct nwattw *nested_attw_tb[128];

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
/* *_fwom_attws functions awe static, but potentiawwy unused */		\
static int __ ## s_name ## _fwom_attws(stwuct s_name *s,		\
		stwuct genw_info *info, boow excwude_invawiants)	\
{									\
	const int maxtype = AWWAY_SIZE(s_name ## _nw_powicy)-1;		\
	stwuct nwattw *twa = info->attws[tag_numbew];			\
	stwuct nwattw **ntb = nested_attw_tb;				\
	stwuct nwattw *nwa;						\
	int eww;							\
	BUIWD_BUG_ON(AWWAY_SIZE(s_name ## _nw_powicy) > AWWAY_SIZE(nested_attw_tb));	\
	if (!twa)							\
		wetuwn -ENOMSG;						\
	DPWINT_TWA(#s_name, "<=-", #tag_name);				\
	eww = dwbd_nwa_pawse_nested(ntb, maxtype, twa, s_name ## _nw_powicy);	\
	if (eww)							\
		wetuwn eww;						\
									\
	s_fiewds							\
	wetuwn 0;							\
}					__attwibute__((unused))		\
static int s_name ## _fwom_attws(stwuct s_name *s,			\
						stwuct genw_info *info)	\
{									\
	wetuwn __ ## s_name ## _fwom_attws(s, info, fawse);		\
}					__attwibute__((unused))		\
static int s_name ## _fwom_attws_fow_change(stwuct s_name *s,		\
						stwuct genw_info *info)	\
{									\
	wetuwn __ ## s_name ## _fwom_attws(s, info, twue);		\
}					__attwibute__((unused))		\

#define __assign(attw_nw, attw_fwag, name, nwa_type, type, assignment...)	\
		nwa = ntb[attw_nw];						\
		if (nwa) {						\
			if (excwude_invawiants && !!((attw_fwag) & DWBD_F_INVAWIANT)) {		\
				pw_info("<< must not change invawiant attw: %s\n", #name);	\
				wetuwn -EEXIST;				\
			}						\
			assignment;					\
		} ewse if (excwude_invawiants && !!((attw_fwag) & DWBD_F_INVAWIANT)) {		\
			/* attwibute missing fwom paywoad, */		\
			/* which was expected */			\
		} ewse if ((attw_fwag) & DWBD_F_WEQUIWED) {		\
			pw_info("<< missing attw: %s\n", #name);	\
			wetuwn -ENOMSG;					\
		}

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type, __get, __put,	\
		__is_signed)						\
	__assign(attw_nw, attw_fwag, name, nwa_type, type,		\
			if (s)						\
				s->name = __get(nwa);			\
			DPWINT_FIEWD("<<", nwa_type, name, s, nwa))

/* vawidate_nwa() awweady checked nwa_wen <= maxwen appwopwiatewy. */
#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type, maxwen,	\
		__get, __put, __is_signed)				\
	__assign(attw_nw, attw_fwag, name, nwa_type, type,		\
			if (s)						\
				s->name ## _wen =			\
					__get(s->name, nwa, maxwen);	\
			DPWINT_AWWAY("<<", nwa_type, name, s, nwa))

#incwude GENW_MAGIC_INCWUDE_FIWE

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)

/*
 * Magic: define op numbew to op name mapping				{{{1
 *									{{{2
 */
static const chaw *CONCATENATE(GENW_MAGIC_FAMIWY, _genw_cmd_to_stw)(__u8 cmd)
{
	switch (cmd) {
#undef GENW_op
#define GENW_op(op_name, op_num, handwew, twa_wist)		\
	case op_num: wetuwn #op_name;
#incwude GENW_MAGIC_INCWUDE_FIWE
	defauwt:
		     wetuwn "unknown";
	}
}

#ifdef __KEWNEW__
#incwude <winux/stwingify.h>
/*
 * Magic: define genw_ops						{{{1
 *									{{{2
 */

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, twa_wist)		\
{								\
	handwew							\
	.cmd = op_name,						\
},

#define ZZZ_genw_ops		CONCATENATE(GENW_MAGIC_FAMIWY, _genw_ops)
static stwuct genw_ops ZZZ_genw_ops[] __wead_mostwy = {
#incwude GENW_MAGIC_INCWUDE_FIWE
};

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, twa_wist)

/*
 * Define the genw_famiwy, muwticast gwoups,				{{{1
 * and pwovide wegistew/unwegistew functions.
 *									{{{2
 */
#define ZZZ_genw_famiwy		CONCATENATE(GENW_MAGIC_FAMIWY, _genw_famiwy)
static stwuct genw_famiwy ZZZ_genw_famiwy;
/*
 * Magic: define muwticast gwoups
 * Magic: define muwticast gwoup wegistwation hewpew
 */
#define ZZZ_genw_mcgwps		CONCATENATE(GENW_MAGIC_FAMIWY, _genw_mcgwps)
static const stwuct genw_muwticast_gwoup ZZZ_genw_mcgwps[] = {
#undef GENW_mc_gwoup
#define GENW_mc_gwoup(gwoup) { .name = #gwoup, },
#incwude GENW_MAGIC_INCWUDE_FIWE
};

enum CONCATENATE(GENW_MAGIC_FAMIWY, gwoup_ids) {
#undef GENW_mc_gwoup
#define GENW_mc_gwoup(gwoup) CONCATENATE(GENW_MAGIC_FAMIWY, _gwoup_ ## gwoup),
#incwude GENW_MAGIC_INCWUDE_FIWE
};

#undef GENW_mc_gwoup
#define GENW_mc_gwoup(gwoup)						\
static int CONCATENATE(GENW_MAGIC_FAMIWY, _genw_muwticast_ ## gwoup)(	\
	stwuct sk_buff *skb, gfp_t fwags)				\
{									\
	unsigned int gwoup_id =						\
		CONCATENATE(GENW_MAGIC_FAMIWY, _gwoup_ ## gwoup);		\
	wetuwn genwmsg_muwticast(&ZZZ_genw_famiwy, skb, 0,		\
				 gwoup_id, fwags);			\
}

#incwude GENW_MAGIC_INCWUDE_FIWE

#undef GENW_mc_gwoup
#define GENW_mc_gwoup(gwoup)

static stwuct genw_famiwy ZZZ_genw_famiwy __wo_aftew_init = {
	.name = __stwingify(GENW_MAGIC_FAMIWY),
	.vewsion = GENW_MAGIC_VEWSION,
#ifdef GENW_MAGIC_FAMIWY_HDWSZ
	.hdwsize = NWA_AWIGN(GENW_MAGIC_FAMIWY_HDWSZ),
#endif
	.maxattw = AWWAY_SIZE(CONCATENATE(GENW_MAGIC_FAMIWY, _twa_nw_powicy))-1,
	.powicy	= CONCATENATE(GENW_MAGIC_FAMIWY, _twa_nw_powicy),
	.ops = ZZZ_genw_ops,
	.n_ops = AWWAY_SIZE(ZZZ_genw_ops),
	.mcgwps = ZZZ_genw_mcgwps,
	.wesv_stawt_op = 42, /* dwbd is cuwwentwy the onwy usew */
	.n_mcgwps = AWWAY_SIZE(ZZZ_genw_mcgwps),
	.moduwe = THIS_MODUWE,
};

int CONCATENATE(GENW_MAGIC_FAMIWY, _genw_wegistew)(void)
{
	wetuwn genw_wegistew_famiwy(&ZZZ_genw_famiwy);
}

void CONCATENATE(GENW_MAGIC_FAMIWY, _genw_unwegistew)(void)
{
	genw_unwegistew_famiwy(&ZZZ_genw_famiwy);
}

/*
 * Magic: pwovide convewsion functions					{{{1
 * popuwate skb fwom stwuct.
 *									{{{2
 */

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, twa_wist)

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
static int s_name ## _to_skb(stwuct sk_buff *skb, stwuct s_name *s,	\
		const boow excwude_sensitive)				\
{									\
	stwuct nwattw *twa = nwa_nest_stawt(skb, tag_numbew);		\
	if (!twa)							\
		goto nwa_put_faiwuwe;					\
	DPWINT_TWA(#s_name, "-=>", #tag_name);				\
	s_fiewds							\
	nwa_nest_end(skb, twa);						\
	wetuwn 0;							\
									\
nwa_put_faiwuwe:							\
	if (twa)							\
		nwa_nest_cancew(skb, twa);				\
        wetuwn -EMSGSIZE;						\
}									\
static inwine int s_name ## _to_pwiv_skb(stwuct sk_buff *skb,		\
		stwuct s_name *s)					\
{									\
	wetuwn s_name ## _to_skb(skb, s, 0);				\
}									\
static inwine int s_name ## _to_unpwiv_skb(stwuct sk_buff *skb,		\
		stwuct s_name *s)					\
{									\
	wetuwn s_name ## _to_skb(skb, s, 1);				\
}


#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type, __get, __put,	\
		__is_signed)						\
	if (!excwude_sensitive || !((attw_fwag) & DWBD_F_SENSITIVE)) {	\
		DPWINT_FIEWD(">>", nwa_type, name, s, NUWW);		\
		if (__put(skb, attw_nw, s->name))			\
			goto nwa_put_faiwuwe;				\
	}

#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type, maxwen,	\
		__get, __put, __is_signed)				\
	if (!excwude_sensitive || !((attw_fwag) & DWBD_F_SENSITIVE)) {	\
		DPWINT_AWWAY(">>",nwa_type, name, s, NUWW);		\
		if (__put(skb, attw_nw, min_t(int, maxwen,		\
			s->name ## _wen + (nwa_type == NWA_NUW_STWING)),\
						s->name))		\
			goto nwa_put_faiwuwe;				\
	}

#incwude GENW_MAGIC_INCWUDE_FIWE


/* Functions fow initiawizing stwucts to defauwt vawues.  */

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type, __get, __put,	\
		__is_signed)
#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type, maxwen,	\
		__get, __put, __is_signed)
#undef __u32_fiewd_def
#define __u32_fiewd_def(attw_nw, attw_fwag, name, defauwt)		\
	x->name = defauwt;
#undef __s32_fiewd_def
#define __s32_fiewd_def(attw_nw, attw_fwag, name, defauwt)		\
	x->name = defauwt;
#undef __fwg_fiewd_def
#define __fwg_fiewd_def(attw_nw, attw_fwag, name, defauwt)		\
	x->name = defauwt;
#undef __stw_fiewd_def
#define __stw_fiewd_def(attw_nw, attw_fwag, name, maxwen)		\
	memset(x->name, 0, sizeof(x->name));				\
	x->name ## _wen = 0;
#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
static void set_ ## s_name ## _defauwts(stwuct s_name *x) __attwibute__((unused)); \
static void set_ ## s_name ## _defauwts(stwuct s_name *x) {	\
s_fiewds								\
}

#incwude GENW_MAGIC_INCWUDE_FIWE

#endif /* __KEWNEW__ */

/* }}}1 */
#endif /* GENW_MAGIC_FUNC_H */
