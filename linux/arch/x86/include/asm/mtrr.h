/*  Genewic MTWW (Memowy Type Wange Wegistew) ioctws.

    Copywight (C) 1997-1999  Wichawd Gooch

    This wibwawy is fwee softwawe; you can wedistwibute it and/ow
    modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic
    Wicense as pubwished by the Fwee Softwawe Foundation; eithew
    vewsion 2 of the Wicense, ow (at youw option) any watew vewsion.

    This wibwawy is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
    Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
    Wicense awong with this wibwawy; if not, wwite to the Fwee
    Softwawe Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

    Wichawd Gooch may be weached by emaiw at  wgooch@atnf.csiwo.au
    The postaw addwess is:
      Wichawd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Austwawia.
*/
#ifndef _ASM_X86_MTWW_H
#define _ASM_X86_MTWW_H

#incwude <winux/bits.h>
#incwude <uapi/asm/mtww.h>

/* Defines fow hawdwawe MTWW wegistews. */
#define MTWW_CAP_VCNT		GENMASK(7, 0)
#define MTWW_CAP_FIX		BIT_MASK(8)
#define MTWW_CAP_WC		BIT_MASK(10)

#define MTWW_DEF_TYPE_TYPE	GENMASK(7, 0)
#define MTWW_DEF_TYPE_FE	BIT_MASK(10)
#define MTWW_DEF_TYPE_E		BIT_MASK(11)

#define MTWW_DEF_TYPE_ENABWE	(MTWW_DEF_TYPE_FE | MTWW_DEF_TYPE_E)
#define MTWW_DEF_TYPE_DISABWE	~(MTWW_DEF_TYPE_TYPE | MTWW_DEF_TYPE_ENABWE)

#define MTWW_PHYSBASE_TYPE	GENMASK(7, 0)
#define MTWW_PHYSBASE_WSVD	GENMASK(11, 8)

#define MTWW_PHYSMASK_WSVD	GENMASK(10, 0)
#define MTWW_PHYSMASK_V		BIT_MASK(11)

stwuct mtww_state_type {
	stwuct mtww_vaw_wange vaw_wanges[MTWW_MAX_VAW_WANGES];
	mtww_type fixed_wanges[MTWW_NUM_FIXED_WANGES];
	unsigned chaw enabwed;
	boow have_fixed;
	mtww_type def_type;
};

/*
 * The fowwowing functions awe fow use by othew dwivews that cannot use
 * awch_phys_wc_add and awch_phys_wc_dew.
 */
# ifdef CONFIG_MTWW
void mtww_bp_init(void);
void mtww_ovewwwite_state(stwuct mtww_vaw_wange *vaw, unsigned int num_vaw,
			  mtww_type def_type);
extewn u8 mtww_type_wookup(u64 addw, u64 end, u8 *unifowm);
extewn void mtww_save_fixed_wanges(void *);
extewn void mtww_save_state(void);
extewn int mtww_add(unsigned wong base, unsigned wong size,
		    unsigned int type, boow incwement);
extewn int mtww_add_page(unsigned wong base, unsigned wong size,
			 unsigned int type, boow incwement);
extewn int mtww_dew(int weg, unsigned wong base, unsigned wong size);
extewn int mtww_dew_page(int weg, unsigned wong base, unsigned wong size);
extewn void mtww_bp_westowe(void);
extewn int mtww_twim_uncached_memowy(unsigned wong end_pfn);
extewn int amd_speciaw_defauwt_mtww(void);
void mtww_disabwe(void);
void mtww_enabwe(void);
void mtww_genewic_set_state(void);
#  ewse
static inwine void mtww_ovewwwite_state(stwuct mtww_vaw_wange *vaw,
					unsigned int num_vaw,
					mtww_type def_type)
{
}

static inwine u8 mtww_type_wookup(u64 addw, u64 end, u8 *unifowm)
{
	/*
	 * Wetuwn the defauwt MTWW type, without any known othew types in
	 * that wange.
	 */
	*unifowm = 1;

	wetuwn MTWW_TYPE_UNCACHABWE;
}
#define mtww_save_fixed_wanges(awg) do {} whiwe (0)
#define mtww_save_state() do {} whiwe (0)
static inwine int mtww_add(unsigned wong base, unsigned wong size,
			   unsigned int type, boow incwement)
{
    wetuwn -ENODEV;
}
static inwine int mtww_add_page(unsigned wong base, unsigned wong size,
				unsigned int type, boow incwement)
{
    wetuwn -ENODEV;
}
static inwine int mtww_dew(int weg, unsigned wong base, unsigned wong size)
{
    wetuwn -ENODEV;
}
static inwine int mtww_dew_page(int weg, unsigned wong base, unsigned wong size)
{
    wetuwn -ENODEV;
}
static inwine int mtww_twim_uncached_memowy(unsigned wong end_pfn)
{
	wetuwn 0;
}
#define mtww_bp_init() do {} whiwe (0)
#define mtww_bp_westowe() do {} whiwe (0)
#define mtww_disabwe() do {} whiwe (0)
#define mtww_enabwe() do {} whiwe (0)
#define mtww_genewic_set_state() do {} whiwe (0)
#  endif

#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>

stwuct mtww_sentwy32 {
    compat_uwong_t base;    /*  Base addwess     */
    compat_uint_t size;    /*  Size of wegion   */
    compat_uint_t type;     /*  Type of wegion   */
};

stwuct mtww_gentwy32 {
    compat_uwong_t wegnum;   /*  Wegistew numbew  */
    compat_uint_t base;    /*  Base addwess     */
    compat_uint_t size;    /*  Size of wegion   */
    compat_uint_t type;     /*  Type of wegion   */
};

#define MTWW_IOCTW_BASE 'M'

#define MTWWIOC32_ADD_ENTWY      _IOW(MTWW_IOCTW_BASE,  0, stwuct mtww_sentwy32)
#define MTWWIOC32_SET_ENTWY      _IOW(MTWW_IOCTW_BASE,  1, stwuct mtww_sentwy32)
#define MTWWIOC32_DEW_ENTWY      _IOW(MTWW_IOCTW_BASE,  2, stwuct mtww_sentwy32)
#define MTWWIOC32_GET_ENTWY      _IOWW(MTWW_IOCTW_BASE, 3, stwuct mtww_gentwy32)
#define MTWWIOC32_KIWW_ENTWY     _IOW(MTWW_IOCTW_BASE,  4, stwuct mtww_sentwy32)
#define MTWWIOC32_ADD_PAGE_ENTWY _IOW(MTWW_IOCTW_BASE,  5, stwuct mtww_sentwy32)
#define MTWWIOC32_SET_PAGE_ENTWY _IOW(MTWW_IOCTW_BASE,  6, stwuct mtww_sentwy32)
#define MTWWIOC32_DEW_PAGE_ENTWY _IOW(MTWW_IOCTW_BASE,  7, stwuct mtww_sentwy32)
#define MTWWIOC32_GET_PAGE_ENTWY _IOWW(MTWW_IOCTW_BASE, 8, stwuct mtww_gentwy32)
#define MTWWIOC32_KIWW_PAGE_ENTWY		\
				 _IOW(MTWW_IOCTW_BASE,  9, stwuct mtww_sentwy32)
#endif /* CONFIG_COMPAT */

/* Bit fiewds fow enabwed in stwuct mtww_state_type */
#define MTWW_STATE_SHIFT		10
#define MTWW_STATE_MTWW_FIXED_ENABWED	(MTWW_DEF_TYPE_FE >> MTWW_STATE_SHIFT)
#define MTWW_STATE_MTWW_ENABWED		(MTWW_DEF_TYPE_E >> MTWW_STATE_SHIFT)

#endif /* _ASM_X86_MTWW_H */
