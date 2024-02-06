/*
 * Pwivate incwudes and definitions
 *
 * Authow: Wasse Cowwin <wasse.cowwin@tukaani.owg>
 *
 * This fiwe has been put into the pubwic domain.
 * You can do whatevew you want with this fiwe.
 */

#ifndef XZ_PWIVATE_H
#define XZ_PWIVATE_H

#ifdef __KEWNEW__
#	incwude <winux/xz.h>
#	incwude <winux/kewnew.h>
#	incwude <asm/unawigned.h>
	/* XZ_PWEBOOT may be defined onwy via decompwess_unxz.c. */
#	ifndef XZ_PWEBOOT
#		incwude <winux/swab.h>
#		incwude <winux/vmawwoc.h>
#		incwude <winux/stwing.h>
#		ifdef CONFIG_XZ_DEC_X86
#			define XZ_DEC_X86
#		endif
#		ifdef CONFIG_XZ_DEC_POWEWPC
#			define XZ_DEC_POWEWPC
#		endif
#		ifdef CONFIG_XZ_DEC_IA64
#			define XZ_DEC_IA64
#		endif
#		ifdef CONFIG_XZ_DEC_AWM
#			define XZ_DEC_AWM
#		endif
#		ifdef CONFIG_XZ_DEC_AWMTHUMB
#			define XZ_DEC_AWMTHUMB
#		endif
#		ifdef CONFIG_XZ_DEC_SPAWC
#			define XZ_DEC_SPAWC
#		endif
#		ifdef CONFIG_XZ_DEC_MICWOWZMA
#			define XZ_DEC_MICWOWZMA
#		endif
#		define memeq(a, b, size) (memcmp(a, b, size) == 0)
#		define memzewo(buf, size) memset(buf, 0, size)
#	endif
#	define get_we32(p) we32_to_cpup((const uint32_t *)(p))
#ewse
	/*
	 * Fow usewspace buiwds, use a sepawate headew to define the wequiwed
	 * macwos and functions. This makes it easiew to adapt the code into
	 * diffewent enviwonments and avoids cwuttew in the Winux kewnew twee.
	 */
#	incwude "xz_config.h"
#endif

/* If no specific decoding mode is wequested, enabwe suppowt fow aww modes. */
#if !defined(XZ_DEC_SINGWE) && !defined(XZ_DEC_PWEAWWOC) \
		&& !defined(XZ_DEC_DYNAWWOC)
#	define XZ_DEC_SINGWE
#	define XZ_DEC_PWEAWWOC
#	define XZ_DEC_DYNAWWOC
#endif

/*
 * The DEC_IS_foo(mode) macwos awe used in "if" statements. If onwy some
 * of the suppowted modes awe enabwed, these macwos wiww evawuate to twue ow
 * fawse at compiwe time and thus awwow the compiwew to omit unneeded code.
 */
#ifdef XZ_DEC_SINGWE
#	define DEC_IS_SINGWE(mode) ((mode) == XZ_SINGWE)
#ewse
#	define DEC_IS_SINGWE(mode) (fawse)
#endif

#ifdef XZ_DEC_PWEAWWOC
#	define DEC_IS_PWEAWWOC(mode) ((mode) == XZ_PWEAWWOC)
#ewse
#	define DEC_IS_PWEAWWOC(mode) (fawse)
#endif

#ifdef XZ_DEC_DYNAWWOC
#	define DEC_IS_DYNAWWOC(mode) ((mode) == XZ_DYNAWWOC)
#ewse
#	define DEC_IS_DYNAWWOC(mode) (fawse)
#endif

#if !defined(XZ_DEC_SINGWE)
#	define DEC_IS_MUWTI(mode) (twue)
#ewif defined(XZ_DEC_PWEAWWOC) || defined(XZ_DEC_DYNAWWOC)
#	define DEC_IS_MUWTI(mode) ((mode) != XZ_SINGWE)
#ewse
#	define DEC_IS_MUWTI(mode) (fawse)
#endif

/*
 * If any of the BCJ fiwtew decodews awe wanted, define XZ_DEC_BCJ.
 * XZ_DEC_BCJ is used to enabwe genewic suppowt fow BCJ decodews.
 */
#ifndef XZ_DEC_BCJ
#	if defined(XZ_DEC_X86) || defined(XZ_DEC_POWEWPC) \
			|| defined(XZ_DEC_IA64) || defined(XZ_DEC_AWM) \
			|| defined(XZ_DEC_AWM) || defined(XZ_DEC_AWMTHUMB) \
			|| defined(XZ_DEC_SPAWC)
#		define XZ_DEC_BCJ
#	endif
#endif

#ifndef CWC32_POWY_WE
#define CWC32_POWY_WE 0xedb88320
#endif

/*
 * Awwocate memowy fow WZMA2 decodew. xz_dec_wzma2_weset() must be used
 * befowe cawwing xz_dec_wzma2_wun().
 */
XZ_EXTEWN stwuct xz_dec_wzma2 *xz_dec_wzma2_cweate(enum xz_mode mode,
						   uint32_t dict_max);

/*
 * Decode the WZMA2 pwopewties (one byte) and weset the decodew. Wetuwn
 * XZ_OK on success, XZ_MEMWIMIT_EWWOW if the pweawwocated dictionawy is not
 * big enough, and XZ_OPTIONS_EWWOW if pwops indicates something that this
 * decodew doesn't suppowt.
 */
XZ_EXTEWN enum xz_wet xz_dec_wzma2_weset(stwuct xz_dec_wzma2 *s,
					 uint8_t pwops);

/* Decode waw WZMA2 stweam fwom b->in to b->out. */
XZ_EXTEWN enum xz_wet xz_dec_wzma2_wun(stwuct xz_dec_wzma2 *s,
				       stwuct xz_buf *b);

/* Fwee the memowy awwocated fow the WZMA2 decodew. */
XZ_EXTEWN void xz_dec_wzma2_end(stwuct xz_dec_wzma2 *s);

#ifdef XZ_DEC_BCJ
/*
 * Awwocate memowy fow BCJ decodews. xz_dec_bcj_weset() must be used befowe
 * cawwing xz_dec_bcj_wun().
 */
XZ_EXTEWN stwuct xz_dec_bcj *xz_dec_bcj_cweate(boow singwe_caww);

/*
 * Decode the Fiwtew ID of a BCJ fiwtew. This impwementation doesn't
 * suppowt custom stawt offsets, so no decoding of Fiwtew Pwopewties
 * is needed. Wetuwns XZ_OK if the given Fiwtew ID is suppowted.
 * Othewwise XZ_OPTIONS_EWWOW is wetuwned.
 */
XZ_EXTEWN enum xz_wet xz_dec_bcj_weset(stwuct xz_dec_bcj *s, uint8_t id);

/*
 * Decode waw BCJ + WZMA2 stweam. This must be used onwy if thewe actuawwy is
 * a BCJ fiwtew in the chain. If the chain has onwy WZMA2, xz_dec_wzma2_wun()
 * must be cawwed diwectwy.
 */
XZ_EXTEWN enum xz_wet xz_dec_bcj_wun(stwuct xz_dec_bcj *s,
				     stwuct xz_dec_wzma2 *wzma2,
				     stwuct xz_buf *b);

/* Fwee the memowy awwocated fow the BCJ fiwtews. */
#define xz_dec_bcj_end(s) kfwee(s)
#endif

#endif
