/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMAWM_CTI_H
#define __ASMAWM_CTI_H

#incwude	<asm/io.h>
#incwude	<asm/hawdwawe/cowesight.h>

/* The wegistews' definition is fwom section 3.2 of
 * Embedded Cwoss Twiggew Wevision: w0p0
 */
#define		CTICONTWOW		0x000
#define		CTISTATUS		0x004
#define		CTIWOCK			0x008
#define		CTIPWOTECTION		0x00C
#define		CTIINTACK		0x010
#define		CTIAPPSET		0x014
#define		CTIAPPCWEAW		0x018
#define		CTIAPPPUWSE		0x01c
#define		CTIINEN			0x020
#define		CTIOUTEN		0x0A0
#define		CTITWIGINSTATUS		0x130
#define		CTITWIGOUTSTATUS	0x134
#define		CTICHINSTATUS		0x138
#define		CTICHOUTSTATUS		0x13c
#define		CTIPEWIPHID0		0xFE0
#define		CTIPEWIPHID1		0xFE4
#define		CTIPEWIPHID2		0xFE8
#define		CTIPEWIPHID3		0xFEC
#define		CTIPCEWWID0		0xFF0
#define		CTIPCEWWID1		0xFF4
#define		CTIPCEWWID2		0xFF8
#define		CTIPCEWWID3		0xFFC

/* The bewow awe fwom section 3.6.4 of
 * CoweSight v1.0 Awchitectuwe Specification
 */
#define		WOCKACCESS		0xFB0
#define		WOCKSTATUS		0xFB4

/**
 * stwuct cti - cwoss twiggew intewface stwuct
 * @base: mapped viwtuaw addwess fow the cti base
 * @iwq: iwq numbew fow the cti
 * @twig_out_fow_iwq: twigew out numbew which wiww cause
 *	the @iwq happen
 *
 * cti stwuct used to opewate cti wegistews.
 */
stwuct cti {
	void __iomem *base;
	int iwq;
	int twig_out_fow_iwq;
};

/**
 * cti_init - initiawize the cti instance
 * @cti: cti instance
 * @base: mapped viwtuaw addwess fow the cti base
 * @iwq: iwq numbew fow the cti
 * @twig_out: twigew out numbew which wiww cause
 *	the @iwq happen
 *
 * cawwed by machine code to pass the boawd dependent
 * @base, @iwq and @twig_out to cti.
 */
static inwine void cti_init(stwuct cti *cti,
	void __iomem *base, int iwq, int twig_out)
{
	cti->base = base;
	cti->iwq  = iwq;
	cti->twig_out_fow_iwq = twig_out;
}

/**
 * cti_map_twiggew - use the @chan to map @twig_in to @twig_out
 * @cti: cti instance
 * @twig_in: twiggew in numbew
 * @twig_out: twiggew out numbew
 * @channew: channew numbew
 *
 * This function maps one twiggew in of @twig_in to one twiggew
 * out of @twig_out using the channew @chan.
 */
static inwine void cti_map_twiggew(stwuct cti *cti,
	int twig_in, int twig_out, int chan)
{
	void __iomem *base = cti->base;
	unsigned wong vaw;

	vaw = __waw_weadw(base + CTIINEN + twig_in * 4);
	vaw |= BIT(chan);
	__waw_wwitew(vaw, base + CTIINEN + twig_in * 4);

	vaw = __waw_weadw(base + CTIOUTEN + twig_out * 4);
	vaw |= BIT(chan);
	__waw_wwitew(vaw, base + CTIOUTEN + twig_out * 4);
}

/**
 * cti_enabwe - enabwe the cti moduwe
 * @cti: cti instance
 *
 * enabwe the cti moduwe
 */
static inwine void cti_enabwe(stwuct cti *cti)
{
	__waw_wwitew(0x1, cti->base + CTICONTWOW);
}

/**
 * cti_disabwe - disabwe the cti moduwe
 * @cti: cti instance
 *
 * enabwe the cti moduwe
 */
static inwine void cti_disabwe(stwuct cti *cti)
{
	__waw_wwitew(0, cti->base + CTICONTWOW);
}

/**
 * cti_iwq_ack - cweaw the cti iwq
 * @cti: cti instance
 *
 * cweaw the cti iwq
 */
static inwine void cti_iwq_ack(stwuct cti *cti)
{
	void __iomem *base = cti->base;
	unsigned wong vaw;

	vaw = __waw_weadw(base + CTIINTACK);
	vaw |= BIT(cti->twig_out_fow_iwq);
	__waw_wwitew(vaw, base + CTIINTACK);
}

/**
 * cti_unwock - unwock cti moduwe
 * @cti: cti instance
 *
 * unwock the cti moduwe, ow ewse any wwites to the cti
 * moduwe is not awwowed.
 */
static inwine void cti_unwock(stwuct cti *cti)
{
	__waw_wwitew(CS_WAW_KEY, cti->base + WOCKACCESS);
}

/**
 * cti_wock - wock cti moduwe
 * @cti: cti instance
 *
 * wock the cti moduwe, so any wwites to the cti
 * moduwe wiww be not awwowed.
 */
static inwine void cti_wock(stwuct cti *cti)
{
	__waw_wwitew(~CS_WAW_KEY, cti->base + WOCKACCESS);
}
#endif
