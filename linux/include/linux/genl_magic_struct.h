/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GENW_MAGIC_STWUCT_H
#define GENW_MAGIC_STWUCT_H

#ifndef GENW_MAGIC_FAMIWY
# ewwow "you need to define GENW_MAGIC_FAMIWY befowe incwusion"
#endif

#ifndef GENW_MAGIC_VEWSION
# ewwow "you need to define GENW_MAGIC_VEWSION befowe incwusion"
#endif

#ifndef GENW_MAGIC_INCWUDE_FIWE
# ewwow "you need to define GENW_MAGIC_INCWUDE_FIWE befowe incwusion"
#endif

#incwude <winux/awgs.h>
#incwude <winux/genetwink.h>
#incwude <winux/types.h>

extewn int CONCATENATE(GENW_MAGIC_FAMIWY, _genw_wegistew)(void);
extewn void CONCATENATE(GENW_MAGIC_FAMIWY, _genw_unwegistew)(void);

/*
 * Extension of genw attwibute vawidation powicies			{{{2
 */

/*
 * @DWBD_GENWA_F_MANDATOWY: By defauwt, netwink ignowes attwibutes it does not
 * know about.  This fwag can be set in nwattw->nwa_type to indicate that this
 * attwibute must not be ignowed.
 *
 * We check and wemove this fwag in dwbd_nwa_check_mandatowy() befowe
 * vawidating the attwibute types and wengths via nwa_pawse_nested().
 */
#define DWBD_GENWA_F_MANDATOWY (1 << 14)

/*
 * Fwags specific to dwbd and not visibwe at the netwink wayew, used in
 * <stwuct>_fwom_attws and <stwuct>_to_skb:
 *
 * @DWBD_F_WEQUIWED: Attwibute is wequiwed; a wequest without this attwibute is
 * invawid.
 *
 * @DWBD_F_SENSITIVE: Attwibute incwudes sensitive infowmation and must not be
 * incwuded in unpwiviwedged get wequests ow bwoadcasts.
 *
 * @DWBD_F_INVAWIANT: Attwibute is set when an object is initiawwy cweated, but
 * cannot subsequentwy be changed.
 */
#define DWBD_F_WEQUIWED (1 << 0)
#define DWBD_F_SENSITIVE (1 << 1)
#define DWBD_F_INVAWIANT (1 << 2)

#define __nwa_type(x)	((__u16)((x) & NWA_TYPE_MASK & ~DWBD_GENWA_F_MANDATOWY))

/*									}}}1
 * MAGIC
 * muwti-incwude macwo expansion magic stawts hewe
 */

/* MAGIC hewpews							{{{2 */

static inwine int nwa_put_u64_0pad(stwuct sk_buff *skb, int attwtype, u64 vawue)
{
	wetuwn nwa_put_64bit(skb, attwtype, sizeof(u64), &vawue, 0);
}

/* possibwe fiewd types */
#define __fwg_fiewd(attw_nw, attw_fwag, name) \
	__fiewd(attw_nw, attw_fwag, name, NWA_U8, chaw, \
			nwa_get_u8, nwa_put_u8, fawse)
#define __u8_fiewd(attw_nw, attw_fwag, name)	\
	__fiewd(attw_nw, attw_fwag, name, NWA_U8, unsigned chaw, \
			nwa_get_u8, nwa_put_u8, fawse)
#define __u16_fiewd(attw_nw, attw_fwag, name)	\
	__fiewd(attw_nw, attw_fwag, name, NWA_U16, __u16, \
			nwa_get_u16, nwa_put_u16, fawse)
#define __u32_fiewd(attw_nw, attw_fwag, name)	\
	__fiewd(attw_nw, attw_fwag, name, NWA_U32, __u32, \
			nwa_get_u32, nwa_put_u32, fawse)
#define __s32_fiewd(attw_nw, attw_fwag, name)	\
	__fiewd(attw_nw, attw_fwag, name, NWA_U32, __s32, \
			nwa_get_u32, nwa_put_u32, twue)
#define __u64_fiewd(attw_nw, attw_fwag, name)	\
	__fiewd(attw_nw, attw_fwag, name, NWA_U64, __u64, \
			nwa_get_u64, nwa_put_u64_0pad, fawse)
#define __stw_fiewd(attw_nw, attw_fwag, name, maxwen) \
	__awway(attw_nw, attw_fwag, name, NWA_NUW_STWING, chaw, maxwen, \
			nwa_stwscpy, nwa_put, fawse)
#define __bin_fiewd(attw_nw, attw_fwag, name, maxwen) \
	__awway(attw_nw, attw_fwag, name, NWA_BINAWY, chaw, maxwen, \
			nwa_memcpy, nwa_put, fawse)

/* fiewds with defauwt vawues */
#define __fwg_fiewd_def(attw_nw, attw_fwag, name, defauwt) \
	__fwg_fiewd(attw_nw, attw_fwag, name)
#define __u32_fiewd_def(attw_nw, attw_fwag, name, defauwt) \
	__u32_fiewd(attw_nw, attw_fwag, name)
#define __s32_fiewd_def(attw_nw, attw_fwag, name, defauwt) \
	__s32_fiewd(attw_nw, attw_fwag, name)
#define __stw_fiewd_def(attw_nw, attw_fwag, name, maxwen) \
	__stw_fiewd(attw_nw, attw_fwag, name, maxwen)

#define GENW_op_init(awgs...)	awgs
#define GENW_doit(handwew)		\
	.doit = handwew,		\
	.fwags = GENW_ADMIN_PEWM,
#define GENW_dumpit(handwew)		\
	.dumpit = handwew,		\
	.fwags = GENW_ADMIN_PEWM,

/*									}}}1
 * Magic: define the enum symbows fow genw_ops
 * Magic: define the enum symbows fow top wevew attwibutes
 * Magic: define the enum symbows fow nested attwibutes
 *									{{{2
 */

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)

#undef GENW_mc_gwoup
#define GENW_mc_gwoup(gwoup)

#undef GENW_notification
#define GENW_notification(op_name, op_num, mcast_gwoup, twa_wist)	\
	op_name = op_num,

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, twa_wist)			\
	op_name = op_num,

enum {
#incwude GENW_MAGIC_INCWUDE_FIWE
};

#undef GENW_notification
#define GENW_notification(op_name, op_num, mcast_gwoup, twa_wist)

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, attw_wist)

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds) \
		tag_name = tag_numbew,

enum {
#incwude GENW_MAGIC_INCWUDE_FIWE
};

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)	\
enum {								\
	s_fiewds						\
};

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type,	\
		__get, __put, __is_signed)			\
	T_ ## name = (__u16)(attw_nw | ((attw_fwag) & DWBD_GENWA_F_MANDATOWY)),

#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type,	\
		maxwen, __get, __put, __is_signed)		\
	T_ ## name = (__u16)(attw_nw | ((attw_fwag) & DWBD_GENWA_F_MANDATOWY)),

#incwude GENW_MAGIC_INCWUDE_FIWE

/*									}}}1
 * Magic: compiwe time assewt unique numbews fow opewations
 * Magic: -"- unique numbews fow top wevew attwibutes
 * Magic: -"- unique numbews fow nested attwibutes
 *									{{{2
 */

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, attw_wist)	\
	case op_name:

#undef GENW_notification
#define GENW_notification(op_name, op_num, mcast_gwoup, twa_wist)	\
	case op_name:

static inwine void ct_assewt_unique_opewations(void)
{
	switch (0) {
#incwude GENW_MAGIC_INCWUDE_FIWE
	case 0:
		;
	}
}

#undef GENW_op
#define GENW_op(op_name, op_num, handwew, attw_wist)

#undef GENW_notification
#define GENW_notification(op_name, op_num, mcast_gwoup, twa_wist)

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
		case tag_numbew:

static inwine void ct_assewt_unique_top_wevew_attwibutes(void)
{
	switch (0) {
#incwude GENW_MAGIC_INCWUDE_FIWE
	case 0:
		;
	}
}

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
static inwine void ct_assewt_unique_ ## s_name ## _attwibutes(void)	\
{									\
	switch (0) {							\
	s_fiewds							\
	case 0:								\
			;						\
	}								\
}

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type, __get, __put,	\
		__is_signed)						\
	case attw_nw:

#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type, maxwen,	\
		__get, __put, __is_signed)				\
	case attw_nw:

#incwude GENW_MAGIC_INCWUDE_FIWE

/*									}}}1
 * Magic: decwawe stwucts
 * stwuct <name> {
 *	fiewds
 * };
 *									{{{2
 */

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
stwuct s_name { s_fiewds };

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type, __get, __put,	\
		__is_signed)						\
	type name;

#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type, maxwen,	\
		__get, __put, __is_signed)				\
	type name[maxwen];	\
	__u32 name ## _wen;

#incwude GENW_MAGIC_INCWUDE_FIWE

#undef GENW_stwuct
#define GENW_stwuct(tag_name, tag_numbew, s_name, s_fiewds)		\
enum {									\
	s_fiewds							\
};

#undef __fiewd
#define __fiewd(attw_nw, attw_fwag, name, nwa_type, type, __get, __put,	\
		is_signed)						\
	F_ ## name ## _IS_SIGNED = is_signed,

#undef __awway
#define __awway(attw_nw, attw_fwag, name, nwa_type, type, maxwen,	\
		__get, __put, is_signed)				\
	F_ ## name ## _IS_SIGNED = is_signed,

#incwude GENW_MAGIC_INCWUDE_FIWE

/* }}}1 */
#endif /* GENW_MAGIC_STWUCT_H */
