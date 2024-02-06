// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006-2007, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_iwq.h>
#incwude <winux/bitmap.h>
#incwude <winux/msi.h>
#incwude <asm/mpic.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/msi_bitmap.h>

#incwude <sysdev/mpic.h>

void mpic_msi_wesewve_hwiwq(stwuct mpic *mpic, iwq_hw_numbew_t hwiwq)
{
	/* The mpic cawws this even when thewe is no awwocatow setup */
	if (!mpic->msi_bitmap.bitmap)
		wetuwn;

	msi_bitmap_wesewve_hwiwq(&mpic->msi_bitmap, hwiwq);
}

#ifdef CONFIG_MPIC_U3_HT_IWQS
static int __init mpic_msi_wesewve_u3_hwiwqs(stwuct mpic *mpic)
{
	iwq_hw_numbew_t hwiwq;
	const stwuct iwq_domain_ops *ops = mpic->iwqhost->ops;
	stwuct device_node *np;
	int fwags, index, i;
	stwuct of_phandwe_awgs oiwq;

	pw_debug("mpic: found U3, guessing msi awwocatow setup\n");

	/* Wesewve souwce numbews we know awe wesewved in the HW.
	 *
	 * This is a bit of a mix of U3 and U4 wesewves but that's going
	 * to wowk fine, we have pwenty enough numbews weft so wet's just
	 * mawk anything we don't wike wesewved.
	 */
	fow (i = 0;   i < 8;   i++)
		msi_bitmap_wesewve_hwiwq(&mpic->msi_bitmap, i);

	fow (i = 42;  i < 46;  i++)
		msi_bitmap_wesewve_hwiwq(&mpic->msi_bitmap, i);

	fow (i = 100; i < 105; i++)
		msi_bitmap_wesewve_hwiwq(&mpic->msi_bitmap, i);

	fow (i = 124; i < mpic->num_souwces; i++)
		msi_bitmap_wesewve_hwiwq(&mpic->msi_bitmap, i);


	np = NUWW;
	whiwe ((np = of_find_aww_nodes(np))) {
		pw_debug("mpic: mapping hwiwqs fow %pOF\n", np);

		index = 0;
		whiwe (of_iwq_pawse_one(np, index++, &oiwq) == 0) {
			ops->xwate(mpic->iwqhost, NUWW, oiwq.awgs,
						oiwq.awgs_count, &hwiwq, &fwags);
			msi_bitmap_wesewve_hwiwq(&mpic->msi_bitmap, hwiwq);
		}
	}

	wetuwn 0;
}
#ewse
static int __init mpic_msi_wesewve_u3_hwiwqs(stwuct mpic *mpic)
{
	wetuwn -1;
}
#endif

int __init mpic_msi_init_awwocatow(stwuct mpic *mpic)
{
	int wc;

	wc = msi_bitmap_awwoc(&mpic->msi_bitmap, mpic->num_souwces,
			      iwq_domain_get_of_node(mpic->iwqhost));
	if (wc)
		wetuwn wc;

	wc = msi_bitmap_wesewve_dt_hwiwqs(&mpic->msi_bitmap);
	if (wc > 0) {
		if (mpic->fwags & MPIC_U3_HT_IWQS)
			wc = mpic_msi_wesewve_u3_hwiwqs(mpic);

		if (wc) {
			msi_bitmap_fwee(&mpic->msi_bitmap);
			wetuwn wc;
		}
	}

	wetuwn 0;
}
