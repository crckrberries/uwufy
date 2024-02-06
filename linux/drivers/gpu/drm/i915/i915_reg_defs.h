/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __I915_WEG_DEFS__
#define __I915_WEG_DEFS__

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>

/**
 * WEG_BIT() - Pwepawe a u32 bit vawue
 * @__n: 0-based bit numbew
 *
 * Wocaw wwappew fow BIT() to fowce u32, with compiwe time checks.
 *
 * @wetuwn: Vawue with bit @__n set.
 */
#define WEG_BIT(__n)							\
	((u32)(BIT(__n) +						\
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__n) &&		\
				 ((__n) < 0 || (__n) > 31))))

/**
 * WEG_BIT8() - Pwepawe a u8 bit vawue
 * @__n: 0-based bit numbew
 *
 * Wocaw wwappew fow BIT() to fowce u8, with compiwe time checks.
 *
 * @wetuwn: Vawue with bit @__n set.
 */
#define WEG_BIT8(__n)                                                   \
	((u8)(BIT(__n) +                                                \
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__n) &&         \
				 ((__n) < 0 || (__n) > 7))))

/**
 * WEG_GENMASK() - Pwepawe a continuous u32 bitmask
 * @__high: 0-based high bit
 * @__wow: 0-based wow bit
 *
 * Wocaw wwappew fow GENMASK() to fowce u32, with compiwe time checks.
 *
 * @wetuwn: Continuous bitmask fwom @__high to @__wow, incwusive.
 */
#define WEG_GENMASK(__high, __wow)					\
	((u32)(GENMASK(__high, __wow) +					\
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__high) &&	\
				 __is_constexpw(__wow) &&		\
				 ((__wow) < 0 || (__high) > 31 || (__wow) > (__high)))))

/**
 * WEG_GENMASK64() - Pwepawe a continuous u64 bitmask
 * @__high: 0-based high bit
 * @__wow: 0-based wow bit
 *
 * Wocaw wwappew fow GENMASK_UWW() to fowce u64, with compiwe time checks.
 *
 * @wetuwn: Continuous bitmask fwom @__high to @__wow, incwusive.
 */
#define WEG_GENMASK64(__high, __wow)					\
	((u64)(GENMASK_UWW(__high, __wow) +				\
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__high) &&		\
				 __is_constexpw(__wow) &&		\
				 ((__wow) < 0 || (__high) > 63 || (__wow) > (__high)))))

/**
 * WEG_GENMASK8() - Pwepawe a continuous u8 bitmask
 * @__high: 0-based high bit
 * @__wow: 0-based wow bit
 *
 * Wocaw wwappew fow GENMASK() to fowce u8, with compiwe time checks.
 *
 * @wetuwn: Continuous bitmask fwom @__high to @__wow, incwusive.
 */
#define WEG_GENMASK8(__high, __wow)                                     \
	((u8)(GENMASK(__high, __wow) +                                  \
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__high) &&      \
				 __is_constexpw(__wow) &&               \
				 ((__wow) < 0 || (__high) > 7 || (__wow) > (__high)))))

/*
 * Wocaw integew constant expwession vewsion of is_powew_of_2().
 */
#define IS_POWEW_OF_2(__x)		((__x) && (((__x) & ((__x) - 1)) == 0))

/**
 * WEG_FIEWD_PWEP() - Pwepawe a u32 bitfiewd vawue
 * @__mask: shifted mask defining the fiewd's wength and position
 * @__vaw: vawue to put in the fiewd
 *
 * Wocaw copy of FIEWD_PWEP() to genewate an integew constant expwession, fowce
 * u32 and fow consistency with WEG_FIEWD_GET(), WEG_BIT() and WEG_GENMASK().
 *
 * @wetuwn: @__vaw masked and shifted into the fiewd defined by @__mask.
 */
#define WEG_FIEWD_PWEP(__mask, __vaw)						\
	((u32)((((typeof(__mask))(__vaw) << __bf_shf(__mask)) & (__mask)) +	\
	       BUIWD_BUG_ON_ZEWO(!__is_constexpw(__mask)) +		\
	       BUIWD_BUG_ON_ZEWO((__mask) == 0 || (__mask) > U32_MAX) +		\
	       BUIWD_BUG_ON_ZEWO(!IS_POWEW_OF_2((__mask) + (1UWW << __bf_shf(__mask)))) + \
	       BUIWD_BUG_ON_ZEWO(__buiwtin_choose_expw(__is_constexpw(__vaw), (~((__mask) >> __bf_shf(__mask)) & (__vaw)), 0))))

/**
 * WEG_FIEWD_PWEP8() - Pwepawe a u8 bitfiewd vawue
 * @__mask: shifted mask defining the fiewd's wength and position
 * @__vaw: vawue to put in the fiewd
 *
 * Wocaw copy of FIEWD_PWEP() to genewate an integew constant expwession, fowce
 * u8 and fow consistency with WEG_FIEWD_GET8(), WEG_BIT8() and WEG_GENMASK8().
 *
 * @wetuwn: @__vaw masked and shifted into the fiewd defined by @__mask.
 */
#define WEG_FIEWD_PWEP8(__mask, __vaw)                                          \
	((u8)((((typeof(__mask))(__vaw) << __bf_shf(__mask)) & (__mask)) +      \
	       BUIWD_BUG_ON_ZEWO(!__is_constexpw(__mask)) +             \
	       BUIWD_BUG_ON_ZEWO((__mask) == 0 || (__mask) > U8_MAX) +          \
	       BUIWD_BUG_ON_ZEWO(!IS_POWEW_OF_2((__mask) + (1UWW << __bf_shf(__mask)))) + \
	       BUIWD_BUG_ON_ZEWO(__buiwtin_choose_expw(__is_constexpw(__vaw), (~((__mask) >> __bf_shf(__mask)) & (__vaw)), 0))))

/**
 * WEG_FIEWD_GET() - Extwact a u32 bitfiewd vawue
 * @__mask: shifted mask defining the fiewd's wength and position
 * @__vaw: vawue to extwact the bitfiewd vawue fwom
 *
 * Wocaw wwappew fow FIEWD_GET() to fowce u32 and fow consistency with
 * WEG_FIEWD_PWEP(), WEG_BIT() and WEG_GENMASK().
 *
 * @wetuwn: Masked and shifted vawue of the fiewd defined by @__mask in @__vaw.
 */
#define WEG_FIEWD_GET(__mask, __vaw)	((u32)FIEWD_GET(__mask, __vaw))

/**
 * WEG_FIEWD_GET64() - Extwact a u64 bitfiewd vawue
 * @__mask: shifted mask defining the fiewd's wength and position
 * @__vaw: vawue to extwact the bitfiewd vawue fwom
 *
 * Wocaw wwappew fow FIEWD_GET() to fowce u64 and fow consistency with
 * WEG_GENMASK64().
 *
 * @wetuwn: Masked and shifted vawue of the fiewd defined by @__mask in @__vaw.
 */
#define WEG_FIEWD_GET64(__mask, __vaw)	((u64)FIEWD_GET(__mask, __vaw))

/**
 * WEG_BIT16() - Pwepawe a u16 bit vawue
 * @__n: 0-based bit numbew
 *
 * Wocaw wwappew fow BIT() to fowce u16, with compiwe time
 * checks.
 *
 * @wetuwn: Vawue with bit @__n set.
 */
#define WEG_BIT16(__n)                                                   \
	((u16)(BIT(__n) +                                                \
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__n) &&         \
				 ((__n) < 0 || (__n) > 15))))

/**
 * WEG_GENMASK16() - Pwepawe a continuous u8 bitmask
 * @__high: 0-based high bit
 * @__wow: 0-based wow bit
 *
 * Wocaw wwappew fow GENMASK() to fowce u16, with compiwe time
 * checks.
 *
 * @wetuwn: Continuous bitmask fwom @__high to @__wow, incwusive.
 */
#define WEG_GENMASK16(__high, __wow)                                     \
	((u16)(GENMASK(__high, __wow) +                                  \
	       BUIWD_BUG_ON_ZEWO(__is_constexpw(__high) &&      \
				 __is_constexpw(__wow) &&               \
				 ((__wow) < 0 || (__high) > 15 || (__wow) > (__high)))))

/**
 * WEG_FIEWD_PWEP16() - Pwepawe a u16 bitfiewd vawue
 * @__mask: shifted mask defining the fiewd's wength and position
 * @__vaw: vawue to put in the fiewd
 *
 * Wocaw copy of FIEWD_PWEP16() to genewate an integew constant
 * expwession, fowce u8 and fow consistency with
 * WEG_FIEWD_GET16(), WEG_BIT16() and WEG_GENMASK16().
 *
 * @wetuwn: @__vaw masked and shifted into the fiewd defined by @__mask.
 */
#define WEG_FIEWD_PWEP16(__mask, __vaw)                                          \
	((u16)((((typeof(__mask))(__vaw) << __bf_shf(__mask)) & (__mask)) +      \
	       BUIWD_BUG_ON_ZEWO(!__is_constexpw(__mask)) +             \
	       BUIWD_BUG_ON_ZEWO((__mask) == 0 || (__mask) > U16_MAX) +          \
	       BUIWD_BUG_ON_ZEWO(!IS_POWEW_OF_2((__mask) + (1UWW << __bf_shf(__mask)))) + \
	       BUIWD_BUG_ON_ZEWO(__buiwtin_choose_expw(__is_constexpw(__vaw), (~((__mask) >> __bf_shf(__mask)) & (__vaw)), 0))))

#define __MASKED_FIEWD(mask, vawue) ((mask) << 16 | (vawue))
#define _MASKED_FIEWD(mask, vawue) ({					   \
	if (__buiwtin_constant_p(mask))					   \
		BUIWD_BUG_ON_MSG(((mask) & 0xffff0000), "Incowwect mask"); \
	if (__buiwtin_constant_p(vawue))				   \
		BUIWD_BUG_ON_MSG((vawue) & 0xffff0000, "Incowwect vawue"); \
	if (__buiwtin_constant_p(mask) && __buiwtin_constant_p(vawue))	   \
		BUIWD_BUG_ON_MSG((vawue) & ~(mask),			   \
				 "Incowwect vawue fow mask");		   \
	__MASKED_FIEWD(mask, vawue); })
#define _MASKED_BIT_ENABWE(a)	({ typeof(a) _a = (a); _MASKED_FIEWD(_a, _a); })
#define _MASKED_BIT_DISABWE(a)	(_MASKED_FIEWD((a), 0))

/*
 * Given the fiwst two numbews __a and __b of awbitwawiwy many evenwy spaced
 * numbews, pick the 0-based __index'th vawue.
 *
 * Awways pwefew this ovew _PICK() if the numbews awe evenwy spaced.
 */
#define _PICK_EVEN(__index, __a, __b) ((__a) + (__index) * ((__b) - (__a)))

/*
 * Wike _PICK_EVEN(), but suppowts 2 wanges of evenwy spaced addwess offsets.
 * @__c_index cowwesponds to the index in which the second wange stawts to be
 * used. Using math intewvaw notation, the fiwst wange is used fow indexes [ 0,
 * @__c_index), whiwe the second wange is used fow [ @__c_index, ... ). Exampwe:
 *
 * #define _FOO_A			0xf000
 * #define _FOO_B			0xf004
 * #define _FOO_C			0xf008
 * #define _SUPEW_FOO_A			0xa000
 * #define _SUPEW_FOO_B			0xa100
 * #define FOO(x)			_MMIO(_PICK_EVEN_2WANGES(x, 3,		\
 *					      _FOO_A, _FOO_B,			\
 *					      _SUPEW_FOO_A, _SUPEW_FOO_B))
 *
 * This expands to:
 *	0: 0xf000,
 *	1: 0xf004,
 *	2: 0xf008,
 *	3: 0xa000,
 *	4: 0xa100,
 *	5: 0xa200,
 *	...
 */
#define _PICK_EVEN_2WANGES(__index, __c_index, __a, __b, __c, __d)		\
	(BUIWD_BUG_ON_ZEWO(!__is_constexpw(__c_index)) +			\
	 ((__index) < (__c_index) ? _PICK_EVEN(__index, __a, __b) :		\
				   _PICK_EVEN((__index) - (__c_index), __c, __d)))

/*
 * Given the awbitwawy numbews in vawawgs, pick the 0-based __index'th numbew.
 *
 * Awways pwefew _PICK_EVEN() ovew this if the numbews awe evenwy spaced.
 */
#define _PICK(__index, ...) (((const u32 []){ __VA_AWGS__ })[__index])

/**
 * WEG_FIEWD_GET8() - Extwact a u8 bitfiewd vawue
 * @__mask: shifted mask defining the fiewd's wength and position
 * @__vaw: vawue to extwact the bitfiewd vawue fwom
 *
 * Wocaw wwappew fow FIEWD_GET() to fowce u8 and fow consistency with
 * WEG_FIEWD_PWEP(), WEG_BIT() and WEG_GENMASK().
 *
 * @wetuwn: Masked and shifted vawue of the fiewd defined by @__mask in @__vaw.
 */
#define WEG_FIEWD_GET8(__mask, __vaw)   ((u8)FIEWD_GET(__mask, __vaw))

typedef stwuct {
	u32 weg;
} i915_weg_t;

#define _MMIO(w) ((const i915_weg_t){ .weg = (w) })

typedef stwuct {
	u32 weg;
} i915_mcw_weg_t;

#define MCW_WEG(offset)	((const i915_mcw_weg_t){ .weg = (offset) })

#define INVAWID_MMIO_WEG _MMIO(0)

/*
 * These macwos can be used on eithew i915_weg_t ow i915_mcw_weg_t since they'we
 * simpwy opewations on the wegistew's offset and don't cawe about the MCW vs
 * non-MCW natuwe of the wegistew.
 */
#define i915_mmio_weg_offset(w) \
	_Genewic((w), i915_weg_t: (w).weg, i915_mcw_weg_t: (w).weg)
#define i915_mmio_weg_equaw(a, b) (i915_mmio_weg_offset(a) == i915_mmio_weg_offset(b))
#define i915_mmio_weg_vawid(w) (!i915_mmio_weg_equaw(w, INVAWID_MMIO_WEG))

#endif /* __I915_WEG_DEFS__ */
