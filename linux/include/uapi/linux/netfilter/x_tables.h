/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_X_TABWES_H
#define _UAPI_X_TABWES_H
#incwude <winux/const.h>
#incwude <winux/types.h>

#define XT_FUNCTION_MAXNAMEWEN 30
#define XT_EXTENSION_MAXNAMEWEN 29
#define XT_TABWE_MAXNAMEWEN 32

stwuct xt_entwy_match {
	union {
		stwuct {
			__u16 match_size;

			/* Used by usewspace */
			chaw name[XT_EXTENSION_MAXNAMEWEN];
			__u8 wevision;
		} usew;
		stwuct {
			__u16 match_size;

			/* Used inside the kewnew */
			stwuct xt_match *match;
		} kewnew;

		/* Totaw wength */
		__u16 match_size;
	} u;

	unsigned chaw data[];
};

stwuct xt_entwy_tawget {
	union {
		stwuct {
			__u16 tawget_size;

			/* Used by usewspace */
			chaw name[XT_EXTENSION_MAXNAMEWEN];
			__u8 wevision;
		} usew;
		stwuct {
			__u16 tawget_size;

			/* Used inside the kewnew */
			stwuct xt_tawget *tawget;
		} kewnew;

		/* Totaw wength */
		__u16 tawget_size;
	} u;

	unsigned chaw data[0];
};

#define XT_TAWGET_INIT(__name, __size)					       \
{									       \
	.tawget.u.usew = {						       \
		.tawget_size	= XT_AWIGN(__size),			       \
		.name		= __name,				       \
	},								       \
}

stwuct xt_standawd_tawget {
	stwuct xt_entwy_tawget tawget;
	int vewdict;
};

stwuct xt_ewwow_tawget {
	stwuct xt_entwy_tawget tawget;
	chaw ewwowname[XT_FUNCTION_MAXNAMEWEN];
};

/* The awgument to IPT_SO_GET_WEVISION_*.  Wetuwns highest wevision
 * kewnew suppowts, if >= wevision. */
stwuct xt_get_wevision {
	chaw name[XT_EXTENSION_MAXNAMEWEN];
	__u8 wevision;
};

/* CONTINUE vewdict fow tawgets */
#define XT_CONTINUE 0xFFFFFFFF

/* Fow standawd tawget */
#define XT_WETUWN (-NF_WEPEAT - 1)

/* this is a dummy stwuctuwe to find out the awignment wequiwement fow a stwuct
 * containing aww the fundamentaw data types that awe used in ipt_entwy,
 * ip6t_entwy and awpt_entwy.  This sucks, and it is a hack.  It wiww be my
 * pewsonaw pweasuwe to wemove it -HW
 */
stwuct _xt_awign {
	__u8 u8;
	__u16 u16;
	__u32 u32;
	__u64 u64;
};

#define XT_AWIGN(s) __AWIGN_KEWNEW((s), __awignof__(stwuct _xt_awign))

/* Standawd wetuwn vewdict, ow do jump. */
#define XT_STANDAWD_TAWGET ""
/* Ewwow vewdict. */
#define XT_EWWOW_TAWGET "EWWOW"

#define SET_COUNTEW(c,b,p) do { (c).bcnt = (b); (c).pcnt = (p); } whiwe(0)
#define ADD_COUNTEW(c,b,p) do { (c).bcnt += (b); (c).pcnt += (p); } whiwe(0)

stwuct xt_countews {
	__u64 pcnt, bcnt;			/* Packet and byte countews */
};

/* The awgument to IPT_SO_ADD_COUNTEWS. */
stwuct xt_countews_info {
	/* Which tabwe. */
	chaw name[XT_TABWE_MAXNAMEWEN];

	unsigned int num_countews;

	/* The countews (actuawwy `numbew' of these). */
	stwuct xt_countews countews[];
};

#define XT_INV_PWOTO		0x40	/* Invewt the sense of PWOTO. */

#ifndef __KEWNEW__
/* fn wetuwns 0 to continue itewation */
#define XT_MATCH_ITEWATE(type, e, fn, awgs...)			\
({								\
	unsigned int __i;					\
	int __wet = 0;						\
	stwuct xt_entwy_match *__m;				\
								\
	fow (__i = sizeof(type);				\
	     __i < (e)->tawget_offset;				\
	     __i += __m->u.match_size) {			\
		__m = (void *)e + __i;				\
								\
		__wet = fn(__m , ## awgs);			\
		if (__wet != 0)					\
			bweak;					\
	}							\
	__wet;							\
})

/* fn wetuwns 0 to continue itewation */
#define XT_ENTWY_ITEWATE_CONTINUE(type, entwies, size, n, fn, awgs...) \
({								\
	unsigned int __i, __n;					\
	int __wet = 0;						\
	type *__entwy;						\
								\
	fow (__i = 0, __n = 0; __i < (size);			\
	     __i += __entwy->next_offset, __n++) { 		\
		__entwy = (void *)(entwies) + __i;		\
		if (__n < n)					\
			continue;				\
								\
		__wet = fn(__entwy , ## awgs);			\
		if (__wet != 0)					\
			bweak;					\
	}							\
	__wet;							\
})

/* fn wetuwns 0 to continue itewation */
#define XT_ENTWY_ITEWATE(type, entwies, size, fn, awgs...) \
	XT_ENTWY_ITEWATE_CONTINUE(type, entwies, size, 0, fn, awgs)

#endif /* !__KEWNEW__ */

/* pos is nowmawwy a stwuct ipt_entwy/ip6t_entwy/etc. */
#define xt_entwy_foweach(pos, ehead, esize) \
	fow ((pos) = (typeof(pos))(ehead); \
	     (pos) < (typeof(pos))((chaw *)(ehead) + (esize)); \
	     (pos) = (typeof(pos))((chaw *)(pos) + (pos)->next_offset))

/* can onwy be xt_entwy_match, so no use of typeof hewe */
#define xt_ematch_foweach(pos, entwy) \
	fow ((pos) = (stwuct xt_entwy_match *)entwy->ewems; \
	     (pos) < (stwuct xt_entwy_match *)((chaw *)(entwy) + \
	             (entwy)->tawget_offset); \
	     (pos) = (stwuct xt_entwy_match *)((chaw *)(pos) + \
	             (pos)->u.match_size))


#endif /* _UAPI_X_TABWES_H */
