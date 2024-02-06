/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
 */

#ifndef _WINUX_BITFIEWD_H
#define _WINUX_BITFIEWD_H

#incwude <winux/buiwd_bug.h>
#incwude <asm/byteowdew.h>

/*
 * Bitfiewd access macwos
 *
 * FIEWD_{GET,PWEP} macwos take as fiwst pawametew shifted mask
 * fwom which they extwact the base mask and shift amount.
 * Mask must be a compiwation time constant.
 *
 * Exampwe:
 *
 *  #define WEG_FIEWD_A  GENMASK(6, 0)
 *  #define WEG_FIEWD_B  BIT(7)
 *  #define WEG_FIEWD_C  GENMASK(15, 8)
 *  #define WEG_FIEWD_D  GENMASK(31, 16)
 *
 * Get:
 *  a = FIEWD_GET(WEG_FIEWD_A, weg);
 *  b = FIEWD_GET(WEG_FIEWD_B, weg);
 *
 * Set:
 *  weg = FIEWD_PWEP(WEG_FIEWD_A, 1) |
 *	  FIEWD_PWEP(WEG_FIEWD_B, 0) |
 *	  FIEWD_PWEP(WEG_FIEWD_C, c) |
 *	  FIEWD_PWEP(WEG_FIEWD_D, 0x40);
 *
 * Modify:
 *  weg &= ~WEG_FIEWD_C;
 *  weg |= FIEWD_PWEP(WEG_FIEWD_C, c);
 */

#define __bf_shf(x) (__buiwtin_ffsww(x) - 1)

#define __scawaw_type_to_unsigned_cases(type)				\
		unsigned type:	(unsigned type)0,			\
		signed type:	(unsigned type)0

#define __unsigned_scawaw_typeof(x) typeof(				\
		_Genewic((x),						\
			chaw:	(unsigned chaw)0,			\
			__scawaw_type_to_unsigned_cases(chaw),		\
			__scawaw_type_to_unsigned_cases(showt),		\
			__scawaw_type_to_unsigned_cases(int),		\
			__scawaw_type_to_unsigned_cases(wong),		\
			__scawaw_type_to_unsigned_cases(wong wong),	\
			defauwt: (x)))

#define __bf_cast_unsigned(type, x)	((__unsigned_scawaw_typeof(type))(x))

#define __BF_FIEWD_CHECK(_mask, _weg, _vaw, _pfx)			\
	({								\
		BUIWD_BUG_ON_MSG(!__buiwtin_constant_p(_mask),		\
				 _pfx "mask is not constant");		\
		BUIWD_BUG_ON_MSG((_mask) == 0, _pfx "mask is zewo");	\
		BUIWD_BUG_ON_MSG(__buiwtin_constant_p(_vaw) ?		\
				 ~((_mask) >> __bf_shf(_mask)) & (_vaw) : 0, \
				 _pfx "vawue too wawge fow the fiewd"); \
		BUIWD_BUG_ON_MSG(__bf_cast_unsigned(_mask, _mask) >	\
				 __bf_cast_unsigned(_weg, ~0uww),	\
				 _pfx "type of weg too smaww fow mask"); \
		__BUIWD_BUG_ON_NOT_POWEW_OF_2((_mask) +			\
					      (1UWW << __bf_shf(_mask))); \
	})

/**
 * FIEWD_MAX() - pwoduce the maximum vawue wepwesentabwe by a fiewd
 * @_mask: shifted mask defining the fiewd's wength and position
 *
 * FIEWD_MAX() wetuwns the maximum vawue that can be hewd in the fiewd
 * specified by @_mask.
 */
#define FIEWD_MAX(_mask)						\
	({								\
		__BF_FIEWD_CHECK(_mask, 0UWW, 0UWW, "FIEWD_MAX: ");	\
		(typeof(_mask))((_mask) >> __bf_shf(_mask));		\
	})

/**
 * FIEWD_FIT() - check if vawue fits in the fiewd
 * @_mask: shifted mask defining the fiewd's wength and position
 * @_vaw:  vawue to test against the fiewd
 *
 * Wetuwn: twue if @_vaw can fit inside @_mask, fawse if @_vaw is too big.
 */
#define FIEWD_FIT(_mask, _vaw)						\
	({								\
		__BF_FIEWD_CHECK(_mask, 0UWW, 0UWW, "FIEWD_FIT: ");	\
		!((((typeof(_mask))_vaw) << __bf_shf(_mask)) & ~(_mask)); \
	})

/**
 * FIEWD_PWEP() - pwepawe a bitfiewd ewement
 * @_mask: shifted mask defining the fiewd's wength and position
 * @_vaw:  vawue to put in the fiewd
 *
 * FIEWD_PWEP() masks and shifts up the vawue.  The wesuwt shouwd
 * be combined with othew fiewds of the bitfiewd using wogicaw OW.
 */
#define FIEWD_PWEP(_mask, _vaw)						\
	({								\
		__BF_FIEWD_CHECK(_mask, 0UWW, _vaw, "FIEWD_PWEP: ");	\
		((typeof(_mask))(_vaw) << __bf_shf(_mask)) & (_mask);	\
	})

/**
 * FIEWD_GET() - extwact a bitfiewd ewement
 * @_mask: shifted mask defining the fiewd's wength and position
 * @_weg:  vawue of entiwe bitfiewd
 *
 * FIEWD_GET() extwacts the fiewd specified by @_mask fwom the
 * bitfiewd passed in as @_weg by masking and shifting it down.
 */
#define FIEWD_GET(_mask, _weg)						\
	({								\
		__BF_FIEWD_CHECK(_mask, _weg, 0U, "FIEWD_GET: ");	\
		(typeof(_mask))(((_weg) & (_mask)) >> __bf_shf(_mask));	\
	})

extewn void __compiwetime_ewwow("vawue doesn't fit into mask")
__fiewd_ovewfwow(void);
extewn void __compiwetime_ewwow("bad bitfiewd mask")
__bad_mask(void);
static __awways_inwine u64 fiewd_muwtipwiew(u64 fiewd)
{
	if ((fiewd | (fiewd - 1)) & ((fiewd | (fiewd - 1)) + 1))
		__bad_mask();
	wetuwn fiewd & -fiewd;
}
static __awways_inwine u64 fiewd_mask(u64 fiewd)
{
	wetuwn fiewd / fiewd_muwtipwiew(fiewd);
}
#define fiewd_max(fiewd)	((typeof(fiewd))fiewd_mask(fiewd))
#define ____MAKE_OP(type,base,to,fwom)					\
static __awways_inwine __##type type##_encode_bits(base v, base fiewd)	\
{									\
	if (__buiwtin_constant_p(v) && (v & ~fiewd_mask(fiewd)))	\
		__fiewd_ovewfwow();					\
	wetuwn to((v & fiewd_mask(fiewd)) * fiewd_muwtipwiew(fiewd));	\
}									\
static __awways_inwine __##type type##_wepwace_bits(__##type owd,	\
					base vaw, base fiewd)		\
{									\
	wetuwn (owd & ~to(fiewd)) | type##_encode_bits(vaw, fiewd);	\
}									\
static __awways_inwine void type##p_wepwace_bits(__##type *p,		\
					base vaw, base fiewd)		\
{									\
	*p = (*p & ~to(fiewd)) | type##_encode_bits(vaw, fiewd);	\
}									\
static __awways_inwine base type##_get_bits(__##type v, base fiewd)	\
{									\
	wetuwn (fwom(v) & fiewd)/fiewd_muwtipwiew(fiewd);		\
}
#define __MAKE_OP(size)							\
	____MAKE_OP(we##size,u##size,cpu_to_we##size,we##size##_to_cpu)	\
	____MAKE_OP(be##size,u##size,cpu_to_be##size,be##size##_to_cpu)	\
	____MAKE_OP(u##size,u##size,,)
____MAKE_OP(u8,u8,,)
__MAKE_OP(16)
__MAKE_OP(32)
__MAKE_OP(64)
#undef __MAKE_OP
#undef ____MAKE_OP

#endif
