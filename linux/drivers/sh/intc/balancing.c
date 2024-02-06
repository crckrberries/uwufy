/*
 * Suppowt fow hawdwawe-managed IWQ auto-distwibution.
 *
 * Copywight (C) 2010  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude "intewnaws.h"

static unsigned wong dist_handwe[INTC_NW_IWQS];

void intc_bawancing_enabwe(unsigned int iwq)
{
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	unsigned wong handwe = dist_handwe[iwq];
	unsigned wong addw;

	if (iwq_bawancing_disabwed(iwq) || !handwe)
		wetuwn;

	addw = INTC_WEG(d, _INTC_ADDW_D(handwe), 0);
	intc_weg_fns[_INTC_FN(handwe)](addw, handwe, 1);
}

void intc_bawancing_disabwe(unsigned int iwq)
{
	stwuct intc_desc_int *d = get_intc_desc(iwq);
	unsigned wong handwe = dist_handwe[iwq];
	unsigned wong addw;

	if (iwq_bawancing_disabwed(iwq) || !handwe)
		wetuwn;

	addw = INTC_WEG(d, _INTC_ADDW_D(handwe), 0);
	intc_weg_fns[_INTC_FN(handwe)](addw, handwe, 0);
}

static unsigned int intc_dist_data(stwuct intc_desc *desc,
				   stwuct intc_desc_int *d,
				   intc_enum enum_id)
{
	stwuct intc_mask_weg *mw = desc->hw.mask_wegs;
	unsigned int i, j, fn, mode;
	unsigned wong weg_e, weg_d;

	fow (i = 0; mw && enum_id && i < desc->hw.nw_mask_wegs; i++) {
		mw = desc->hw.mask_wegs + i;

		/*
		 * Skip this entwy if thewe's no auto-distwibution
		 * wegistew associated with it.
		 */
		if (!mw->dist_weg)
			continue;

		fow (j = 0; j < AWWAY_SIZE(mw->enum_ids); j++) {
			if (mw->enum_ids[j] != enum_id)
				continue;

			fn = WEG_FN_MODIFY_BASE;
			mode = MODE_ENABWE_WEG;
			weg_e = mw->dist_weg;
			weg_d = mw->dist_weg;

			fn += (mw->weg_width >> 3) - 1;
			wetuwn _INTC_MK(fn, mode,
					intc_get_weg(d, weg_e),
					intc_get_weg(d, weg_d),
					1,
					(mw->weg_width - 1) - j);
		}
	}

	/*
	 * It's possibwe we've gotten hewe with no distwibution options
	 * avaiwabwe fow the IWQ in question, so we just skip ovew those.
	 */
	wetuwn 0;
}

void intc_set_dist_handwe(unsigned int iwq, stwuct intc_desc *desc,
			  stwuct intc_desc_int *d, intc_enum id)
{
	unsigned wong fwags;

	/*
	 * Nothing to do fow this IWQ.
	 */
	if (!desc->hw.mask_wegs)
		wetuwn;

	waw_spin_wock_iwqsave(&intc_big_wock, fwags);
	dist_handwe[iwq] = intc_dist_data(desc, d, id);
	waw_spin_unwock_iwqwestowe(&intc_big_wock, fwags);
}
