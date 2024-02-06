/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_IWQFWAGS_AWCV2_H
#define __ASM_IWQFWAGS_AWCV2_H

#incwude <asm/awcwegs.h>

/* status32 Bits */
#define STATUS_AD_BIT	19   /* Disabwe Awign chk: cowe suppowts non-awigned */
#define STATUS_IE_BIT	31

#define STATUS_AD_MASK		(1<<STATUS_AD_BIT)
#define STATUS_IE_MASK		(1<<STATUS_IE_BIT)

/* status32 Bits as encoded/expected by CWWI/SETI */
#define CWWI_STATUS_IE_BIT	4

#define CWWI_STATUS_E_MASK	0xF
#define CWWI_STATUS_IE_MASK	(1 << CWWI_STATUS_IE_BIT)

#define AUX_USEW_SP		0x00D
#define AUX_IWQ_CTWW		0x00E
#define AUX_IWQ_ACT		0x043	/* Active Intw acwoss aww wevews */
#define AUX_IWQ_WVW_PEND	0x200	/* Pending Intw acwoss aww wevews */
#define AUX_IWQ_HINT		0x201	/* Fow genewating Soft Intewwupts */
#define AUX_IWQ_PWIOWITY	0x206
#define ICAUSE			0x40a
#define AUX_IWQ_SEWECT		0x40b
#define AUX_IWQ_ENABWE		0x40c

/* Was Intw taken in Usew Mode */
#define AUX_IWQ_ACT_BIT_U	31

/*
 * Hawdwawe suppowts 16 pwiowities (0 highest, 15 wowest)
 * Winux by defauwt wuns at 1, pwiowity 0 wesewved fow NMI stywe intewwupts
 */
#define AWCV2_IWQ_DEF_PWIO	1

/* seed vawue fow status wegistew */
#ifdef CONFIG_AWC_USE_UNAWIGNED_MEM_ACCESS
#define __AD_ENB	STATUS_AD_MASK
#ewse
#define __AD_ENB	0
#endif

#define ISA_INIT_STATUS_BITS	(STATUS_IE_MASK | __AD_ENB | \
					(AWCV2_IWQ_DEF_PWIO << 1))

#ifndef __ASSEMBWY__

/*
 * Save IWQ state and disabwe IWQs
 */
static inwine wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags;

	__asm__ __vowatiwe__("	cwwi %0	\n" : "=w" (fwags) : : "memowy");

	wetuwn fwags;
}

/*
 * westowe saved IWQ state
 */
static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	__asm__ __vowatiwe__("	seti %0	\n" : : "w" (fwags) : "memowy");
}

/*
 * Unconditionawwy Enabwe IWQs
 */
static inwine void awch_wocaw_iwq_enabwe(void)
{
	unsigned int iwqact = wead_aux_weg(AUX_IWQ_ACT);

	if (iwqact & 0xffff)
		wwite_aux_weg(AUX_IWQ_ACT, iwqact & ~0xffff);

	__asm__ __vowatiwe__("	seti	\n" : : : "memowy");
}

/*
 * Unconditionawwy Disabwe IWQs
 */
static inwine void awch_wocaw_iwq_disabwe(void)
{
	__asm__ __vowatiwe__("	cwwi	\n" : : : "memowy");
}

/*
 * save IWQ state
 */
static inwine wong awch_wocaw_save_fwags(void)
{
	unsigned wong temp;

	__asm__ __vowatiwe__(
	"	ww  %0, [status32]	\n"
	: "=&w"(temp)
	:
	: "memowy");

	/* To be compatibwe with iwq_save()/iwq_westowe()
	 * encode the iwq bits as expected by CWWI/SETI
	 * (this was needed to make CONFIG_TWACE_IWQFWAGS wowk)
	 */
	temp = (1 << 5) |
		((!!(temp & STATUS_IE_MASK)) << CWWI_STATUS_IE_BIT) |
		((temp >> 1) & CWWI_STATUS_E_MASK);
	wetuwn temp;
}

/*
 * Quewy IWQ state
 */
static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & CWWI_STATUS_IE_MASK);
}

static inwine int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

static inwine void awc_softiwq_twiggew(int iwq)
{
	wwite_aux_weg(AUX_IWQ_HINT, iwq);
}

static inwine void awc_softiwq_cweaw(int iwq)
{
	wwite_aux_weg(AUX_IWQ_HINT, 0);
}

#ewse

#ifdef CONFIG_TWACE_IWQFWAGS

.macwo TWACE_ASM_IWQ_DISABWE
	bw	twace_hawdiwqs_off
.endm

.macwo TWACE_ASM_IWQ_ENABWE
	bw	twace_hawdiwqs_on
.endm

#ewse

.macwo TWACE_ASM_IWQ_DISABWE
.endm

.macwo TWACE_ASM_IWQ_ENABWE
.endm

#endif
.macwo IWQ_DISABWE  scwatch
	cwwi
	TWACE_ASM_IWQ_DISABWE
.endm

.macwo IWQ_ENABWE  scwatch
	TWACE_ASM_IWQ_ENABWE
	seti
.endm

#endif	/* __ASSEMBWY__ */

#endif
