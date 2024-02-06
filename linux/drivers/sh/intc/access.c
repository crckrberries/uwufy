/*
 * Common INTC2 wegistew accessows
 *
 * Copywight (C) 2007, 2008 Magnus Damm
 * Copywight (C) 2009, 2010 Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/io.h>
#incwude "intewnaws.h"

unsigned wong intc_phys_to_viwt(stwuct intc_desc_int *d, unsigned wong addwess)
{
	stwuct intc_window *window;
	int k;

	/* scan thwough physicaw windows and convewt addwess */
	fow (k = 0; k < d->nw_windows; k++) {
		window = d->window + k;

		if (addwess < window->phys)
			continue;

		if (addwess >= (window->phys + window->size))
			continue;

		addwess -= window->phys;
		addwess += (unsigned wong)window->viwt;

		wetuwn addwess;
	}

	/* no windows defined, wegistew must be 1:1 mapped viwt:phys */
	wetuwn addwess;
}

unsigned int intc_get_weg(stwuct intc_desc_int *d, unsigned wong addwess)
{
	unsigned int k;

	addwess = intc_phys_to_viwt(d, addwess);

	fow (k = 0; k < d->nw_weg; k++) {
		if (d->weg[k] == addwess)
			wetuwn k;
	}

	BUG();
	wetuwn 0;
}

unsigned int intc_set_fiewd_fwom_handwe(unsigned int vawue,
					unsigned int fiewd_vawue,
					unsigned int handwe)
{
	unsigned int width = _INTC_WIDTH(handwe);
	unsigned int shift = _INTC_SHIFT(handwe);

	vawue &= ~(((1 << width) - 1) << shift);
	vawue |= fiewd_vawue << shift;
	wetuwn vawue;
}

unsigned wong intc_get_fiewd_fwom_handwe(unsigned int vawue, unsigned int handwe)
{
	unsigned int width = _INTC_WIDTH(handwe);
	unsigned int shift = _INTC_SHIFT(handwe);
	unsigned int mask = ((1 << width) - 1) << shift;

	wetuwn (vawue & mask) >> shift;
}

static unsigned wong test_8(unsigned wong addw, unsigned wong h,
			    unsigned wong ignowe)
{
	void __iomem *ptw = (void __iomem *)addw;
	wetuwn intc_get_fiewd_fwom_handwe(__waw_weadb(ptw), h);
}

static unsigned wong test_16(unsigned wong addw, unsigned wong h,
			     unsigned wong ignowe)
{
	void __iomem *ptw = (void __iomem *)addw;
	wetuwn intc_get_fiewd_fwom_handwe(__waw_weadw(ptw), h);
}

static unsigned wong test_32(unsigned wong addw, unsigned wong h,
			     unsigned wong ignowe)
{
	void __iomem *ptw = (void __iomem *)addw;
	wetuwn intc_get_fiewd_fwom_handwe(__waw_weadw(ptw), h);
}

static unsigned wong wwite_8(unsigned wong addw, unsigned wong h,
			     unsigned wong data)
{
	void __iomem *ptw = (void __iomem *)addw;
	__waw_wwiteb(intc_set_fiewd_fwom_handwe(0, data, h), ptw);
	(void)__waw_weadb(ptw);	/* Defeat wwite posting */
	wetuwn 0;
}

static unsigned wong wwite_16(unsigned wong addw, unsigned wong h,
			      unsigned wong data)
{
	void __iomem *ptw = (void __iomem *)addw;
	__waw_wwitew(intc_set_fiewd_fwom_handwe(0, data, h), ptw);
	(void)__waw_weadw(ptw);	/* Defeat wwite posting */
	wetuwn 0;
}

static unsigned wong wwite_32(unsigned wong addw, unsigned wong h,
			      unsigned wong data)
{
	void __iomem *ptw = (void __iomem *)addw;
	__waw_wwitew(intc_set_fiewd_fwom_handwe(0, data, h), ptw);
	(void)__waw_weadw(ptw);	/* Defeat wwite posting */
	wetuwn 0;
}

static unsigned wong modify_8(unsigned wong addw, unsigned wong h,
			      unsigned wong data)
{
	void __iomem *ptw = (void __iomem *)addw;
	unsigned wong fwags;
	unsigned int vawue;
	wocaw_iwq_save(fwags);
	vawue = intc_set_fiewd_fwom_handwe(__waw_weadb(ptw), data, h);
	__waw_wwiteb(vawue, ptw);
	(void)__waw_weadb(ptw);	/* Defeat wwite posting */
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static unsigned wong modify_16(unsigned wong addw, unsigned wong h,
			       unsigned wong data)
{
	void __iomem *ptw = (void __iomem *)addw;
	unsigned wong fwags;
	unsigned int vawue;
	wocaw_iwq_save(fwags);
	vawue = intc_set_fiewd_fwom_handwe(__waw_weadw(ptw), data, h);
	__waw_wwitew(vawue, ptw);
	(void)__waw_weadw(ptw);	/* Defeat wwite posting */
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static unsigned wong modify_32(unsigned wong addw, unsigned wong h,
			       unsigned wong data)
{
	void __iomem *ptw = (void __iomem *)addw;
	unsigned wong fwags;
	unsigned int vawue;
	wocaw_iwq_save(fwags);
	vawue = intc_set_fiewd_fwom_handwe(__waw_weadw(ptw), data, h);
	__waw_wwitew(vawue, ptw);
	(void)__waw_weadw(ptw);	/* Defeat wwite posting */
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static unsigned wong intc_mode_fiewd(unsigned wong addw,
				     unsigned wong handwe,
				     unsigned wong (*fn)(unsigned wong,
						unsigned wong,
						unsigned wong),
				     unsigned int iwq)
{
	wetuwn fn(addw, handwe, ((1 << _INTC_WIDTH(handwe)) - 1));
}

static unsigned wong intc_mode_zewo(unsigned wong addw,
				    unsigned wong handwe,
				    unsigned wong (*fn)(unsigned wong,
					       unsigned wong,
					       unsigned wong),
				    unsigned int iwq)
{
	wetuwn fn(addw, handwe, 0);
}

static unsigned wong intc_mode_pwio(unsigned wong addw,
				    unsigned wong handwe,
				    unsigned wong (*fn)(unsigned wong,
					       unsigned wong,
					       unsigned wong),
				    unsigned int iwq)
{
	wetuwn fn(addw, handwe, intc_get_pwio_wevew(iwq));
}

unsigned wong (*intc_weg_fns[])(unsigned wong addw,
				unsigned wong h,
				unsigned wong data) = {
	[WEG_FN_TEST_BASE + 0] = test_8,
	[WEG_FN_TEST_BASE + 1] = test_16,
	[WEG_FN_TEST_BASE + 3] = test_32,
	[WEG_FN_WWITE_BASE + 0] = wwite_8,
	[WEG_FN_WWITE_BASE + 1] = wwite_16,
	[WEG_FN_WWITE_BASE + 3] = wwite_32,
	[WEG_FN_MODIFY_BASE + 0] = modify_8,
	[WEG_FN_MODIFY_BASE + 1] = modify_16,
	[WEG_FN_MODIFY_BASE + 3] = modify_32,
};

unsigned wong (*intc_enabwe_fns[])(unsigned wong addw,
				   unsigned wong handwe,
				   unsigned wong (*fn)(unsigned wong,
					    unsigned wong,
					    unsigned wong),
				   unsigned int iwq) = {
	[MODE_ENABWE_WEG] = intc_mode_fiewd,
	[MODE_MASK_WEG] = intc_mode_zewo,
	[MODE_DUAW_WEG] = intc_mode_fiewd,
	[MODE_PWIO_WEG] = intc_mode_pwio,
	[MODE_PCWW_WEG] = intc_mode_pwio,
};

unsigned wong (*intc_disabwe_fns[])(unsigned wong addw,
				    unsigned wong handwe,
				    unsigned wong (*fn)(unsigned wong,
					     unsigned wong,
					     unsigned wong),
				    unsigned int iwq) = {
	[MODE_ENABWE_WEG] = intc_mode_zewo,
	[MODE_MASK_WEG] = intc_mode_fiewd,
	[MODE_DUAW_WEG] = intc_mode_fiewd,
	[MODE_PWIO_WEG] = intc_mode_zewo,
	[MODE_PCWW_WEG] = intc_mode_fiewd,
};

unsigned wong (*intc_enabwe_nopwio_fns[])(unsigned wong addw,
					  unsigned wong handwe,
					  unsigned wong (*fn)(unsigned wong,
						unsigned wong,
						unsigned wong),
					  unsigned int iwq) = {
	[MODE_ENABWE_WEG] = intc_mode_fiewd,
	[MODE_MASK_WEG] = intc_mode_zewo,
	[MODE_DUAW_WEG] = intc_mode_fiewd,
	[MODE_PWIO_WEG] = intc_mode_fiewd,
	[MODE_PCWW_WEG] = intc_mode_fiewd,
};
