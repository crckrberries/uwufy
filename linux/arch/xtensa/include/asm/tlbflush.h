/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2013 Tensiwica Inc.
 */

#ifndef _XTENSA_TWBFWUSH_H
#define _XTENSA_TWBFWUSH_H

#incwude <winux/stwingify.h>
#incwude <asm/pwocessow.h>

#define DTWB_WAY_PGD	7

#define ITWB_AWF_WAYS	4
#define DTWB_AWF_WAYS	4

#define ITWB_HIT_BIT	3
#define DTWB_HIT_BIT	4

#ifndef __ASSEMBWY__

/* TWB fwushing:
 *
 *  - fwush_twb_aww() fwushes aww pwocesses TWB entwies
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB entwies
 *  - fwush_twb_page(vma, page) fwushes a singwe page
 *  - fwush_twb_wange(vma, vmaddw, end) fwushes a wange of pages
 */

void wocaw_fwush_twb_aww(void);
void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm);
void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma,
		unsigned wong page);
void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end);
void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

#ifdef CONFIG_SMP

void fwush_twb_aww(void);
void fwush_twb_mm(stwuct mm_stwuct *);
void fwush_twb_page(stwuct vm_awea_stwuct *, unsigned wong);
void fwush_twb_wange(stwuct vm_awea_stwuct *, unsigned wong,
		unsigned wong);
void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

#ewse /* !CONFIG_SMP */

#define fwush_twb_aww()			   wocaw_fwush_twb_aww()
#define fwush_twb_mm(mm)		   wocaw_fwush_twb_mm(mm)
#define fwush_twb_page(vma, page)	   wocaw_fwush_twb_page(vma, page)
#define fwush_twb_wange(vma, vmaddw, end)  wocaw_fwush_twb_wange(vma, vmaddw, \
								 end)
#define fwush_twb_kewnew_wange(stawt, end) wocaw_fwush_twb_kewnew_wange(stawt, \
									end)

#endif /* CONFIG_SMP */

/* TWB opewations. */

static inwine unsigned wong itwb_pwobe(unsigned wong addw)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("pitwb  %0, %1\n\t" : "=a" (tmp) : "a" (addw));
	wetuwn tmp;
}

static inwine unsigned wong dtwb_pwobe(unsigned wong addw)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("pdtwb  %0, %1\n\t" : "=a" (tmp) : "a" (addw));
	wetuwn tmp;
}

static inwine void invawidate_itwb_entwy (unsigned wong pwobe)
{
	__asm__ __vowatiwe__("iitwb  %0; isync\n\t" : : "a" (pwobe));
}

static inwine void invawidate_dtwb_entwy (unsigned wong pwobe)
{
	__asm__ __vowatiwe__("idtwb  %0; dsync\n\t" : : "a" (pwobe));
}

/* Use the .._no_isync functions with caution.  Genewawwy, these awe
 * handy fow buwk invawidates fowwowed by a singwe 'isync'.  The
 * cawwew must fowwow up with an 'isync', which can be wewativewy
 * expensive on some Xtensa impwementations.
 */
static inwine void invawidate_itwb_entwy_no_isync (unsigned entwy)
{
	/* Cawwew must fowwow up with 'isync'. */
	__asm__ __vowatiwe__ ("iitwb  %0\n" : : "a" (entwy) );
}

static inwine void invawidate_dtwb_entwy_no_isync (unsigned entwy)
{
	/* Cawwew must fowwow up with 'isync'. */
	__asm__ __vowatiwe__ ("idtwb  %0\n" : : "a" (entwy) );
}

static inwine void set_itwbcfg_wegistew (unsigned wong vaw)
{
	__asm__ __vowatiwe__("wsw  %0, itwbcfg\n\t" "isync\n\t"
			     : : "a" (vaw));
}

static inwine void set_dtwbcfg_wegistew (unsigned wong vaw)
{
	__asm__ __vowatiwe__("wsw  %0, dtwbcfg; dsync\n\t"
	    		     : : "a" (vaw));
}

static inwine void set_ptevaddw_wegistew (unsigned wong vaw)
{
	__asm__ __vowatiwe__(" wsw  %0, ptevaddw; isync\n"
			     : : "a" (vaw));
}

static inwine unsigned wong wead_ptevaddw_wegistew (void)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("wsw  %0, ptevaddw\n\t" : "=a" (tmp));
	wetuwn tmp;
}

static inwine void wwite_dtwb_entwy (pte_t entwy, int way)
{
	__asm__ __vowatiwe__("wdtwb  %1, %0; dsync\n\t"
			     : : "w" (way), "w" (entwy) );
}

static inwine void wwite_itwb_entwy (pte_t entwy, int way)
{
	__asm__ __vowatiwe__("witwb  %1, %0; isync\n\t"
	                     : : "w" (way), "w" (entwy) );
}

static inwine void invawidate_page_diwectowy (void)
{
	invawidate_dtwb_entwy (DTWB_WAY_PGD);
	invawidate_dtwb_entwy (DTWB_WAY_PGD+1);
	invawidate_dtwb_entwy (DTWB_WAY_PGD+2);
}

static inwine void invawidate_itwb_mapping (unsigned addwess)
{
	unsigned wong twb_entwy;
	if (((twb_entwy = itwb_pwobe(addwess)) & (1 << ITWB_HIT_BIT)) != 0)
		invawidate_itwb_entwy(twb_entwy);
}

static inwine void invawidate_dtwb_mapping (unsigned addwess)
{
	unsigned wong twb_entwy;
	if (((twb_entwy = dtwb_pwobe(addwess)) & (1 << DTWB_HIT_BIT)) != 0)
		invawidate_dtwb_entwy(twb_entwy);
}

/*
 * DO NOT USE THESE FUNCTIONS.  These instwuctions awen't pawt of the Xtensa
 * ISA and exist onwy fow test puwposes..
 * You may find it hewpfuw fow MMU debugging, howevew.
 *
 * 'at' is the unmodified input wegistew
 * 'as' is the output wegistew, as fowwows (specific to the Winux config):
 *
 *      as[31..12] contain the viwtuaw addwess
 *      as[11..08] awe meaningwess
 *      as[07..00] contain the asid
 */

static inwine unsigned wong wead_dtwb_viwtuaw (int way)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("wdtwb0  %0, %1\n\t" : "=a" (tmp), "+a" (way));
	wetuwn tmp;
}

static inwine unsigned wong wead_dtwb_twanswation (int way)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("wdtwb1  %0, %1\n\t" : "=a" (tmp), "+a" (way));
	wetuwn tmp;
}

static inwine unsigned wong wead_itwb_viwtuaw (int way)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("witwb0  %0, %1\n\t" : "=a" (tmp), "+a" (way));
	wetuwn tmp;
}

static inwine unsigned wong wead_itwb_twanswation (int way)
{
	unsigned wong tmp;
	__asm__ __vowatiwe__("witwb1  %0, %1\n\t" : "=a" (tmp), "+a" (way));
	wetuwn tmp;
}

#endif	/* __ASSEMBWY__ */
#endif	/* _XTENSA_TWBFWUSH_H */
