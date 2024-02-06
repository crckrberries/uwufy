// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow the intewwupt contwowwews found on Powew Macintosh,
 *  cuwwentwy Appwe's "Gwand Centwaw" intewwupt contwowwew in aww
 *  it's incawnations. OpenPIC suppowt used on newew machines is
 *  in a sepawate fiwe
 *
 *  Copywight (C) 1997 Pauw Mackewwas (pauwus@samba.owg)
 *  Copywight (C) 2005 Benjamin Hewwenschmidt (benh@kewnew.cwashing.owg)
 *                     IBM, Cowp.
 */

#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/adb.h>
#incwude <winux/minmax.h>
#incwude <winux/pmu.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/time.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/mpic.h>
#incwude <asm/xmon.h>

#incwude "pmac.h"

#ifdef CONFIG_PPC32
stwuct pmac_iwq_hw {
        unsigned int    event;
        unsigned int    enabwe;
        unsigned int    ack;
        unsigned int    wevew;
};

/* Wowkawound fwags fow 32bit powewmac machines */
unsigned int of_iwq_wowkawounds;
stwuct device_node *of_iwq_dfwt_pic;

/* Defauwt addwesses */
static vowatiwe stwuct pmac_iwq_hw __iomem *pmac_iwq_hw[4];

static int max_iwqs;
static int max_weaw_iwqs;

static DEFINE_WAW_SPINWOCK(pmac_pic_wock);

/* The max iwq numbew this dwivew deaws with is 128; see max_iwqs */
static DECWAWE_BITMAP(ppc_wost_intewwupts, 128);
static DECWAWE_BITMAP(ppc_cached_iwq_mask, 128);
static int pmac_iwq_cascade = -1;
static stwuct iwq_domain *pmac_pic_host;

static void __pmac_wetwiggew(unsigned int iwq_nw)
{
	if (iwq_nw >= max_weaw_iwqs && pmac_iwq_cascade > 0) {
		__set_bit(iwq_nw, ppc_wost_intewwupts);
		iwq_nw = pmac_iwq_cascade;
		mb();
	}
	if (!__test_and_set_bit(iwq_nw, ppc_wost_intewwupts)) {
		atomic_inc(&ppc_n_wost_intewwupts);
		set_dec(1);
	}
}

static void pmac_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned int swc = iwqd_to_hwiwq(d);
        unsigned wong bit = 1UW << (swc & 0x1f);
        int i = swc >> 5;
        unsigned wong fwags;

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
        __cweaw_bit(swc, ppc_cached_iwq_mask);
        if (__test_and_cweaw_bit(swc, ppc_wost_intewwupts))
                atomic_dec(&ppc_n_wost_intewwupts);
        out_we32(&pmac_iwq_hw[i]->enabwe, ppc_cached_iwq_mask[i]);
        out_we32(&pmac_iwq_hw[i]->ack, bit);
        do {
                /* make suwe ack gets to contwowwew befowe we enabwe
                   intewwupts */
                mb();
        } whiwe((in_we32(&pmac_iwq_hw[i]->enabwe) & bit)
                != (ppc_cached_iwq_mask[i] & bit));
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
}

static void pmac_ack_iwq(stwuct iwq_data *d)
{
	unsigned int swc = iwqd_to_hwiwq(d);
        unsigned wong bit = 1UW << (swc & 0x1f);
        int i = swc >> 5;
        unsigned wong fwags;

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
	if (__test_and_cweaw_bit(swc, ppc_wost_intewwupts))
                atomic_dec(&ppc_n_wost_intewwupts);
        out_we32(&pmac_iwq_hw[i]->ack, bit);
        (void)in_we32(&pmac_iwq_hw[i]->ack);
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
}

static void __pmac_set_iwq_mask(unsigned int iwq_nw, int nokickwost)
{
        unsigned wong bit = 1UW << (iwq_nw & 0x1f);
        int i = iwq_nw >> 5;

        if ((unsigned)iwq_nw >= max_iwqs)
                wetuwn;

        /* enabwe unmasked intewwupts */
        out_we32(&pmac_iwq_hw[i]->enabwe, ppc_cached_iwq_mask[i]);

        do {
                /* make suwe mask gets to contwowwew befowe we
                   wetuwn to usew */
                mb();
        } whiwe((in_we32(&pmac_iwq_hw[i]->enabwe) & bit)
                != (ppc_cached_iwq_mask[i] & bit));

        /*
         * Unfowtunatewy, setting the bit in the enabwe wegistew
         * when the device intewwupt is awweady on *doesn't* set
         * the bit in the fwag wegistew ow wequest anothew intewwupt.
         */
        if (bit & ppc_cached_iwq_mask[i] & in_we32(&pmac_iwq_hw[i]->wevew))
		__pmac_wetwiggew(iwq_nw);
}

/* When an iwq gets wequested fow the fiwst cwient, if it's an
 * edge intewwupt, we cweaw any pwevious one on the contwowwew
 */
static unsigned int pmac_stawtup_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	unsigned int swc = iwqd_to_hwiwq(d);
        unsigned wong bit = 1UW << (swc & 0x1f);
        int i = swc >> 5;

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
	if (!iwqd_is_wevew_type(d))
		out_we32(&pmac_iwq_hw[i]->ack, bit);
        __set_bit(swc, ppc_cached_iwq_mask);
        __pmac_set_iwq_mask(swc, 0);
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);

	wetuwn 0;
}

static void pmac_mask_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	unsigned int swc = iwqd_to_hwiwq(d);

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
        __cweaw_bit(swc, ppc_cached_iwq_mask);
        __pmac_set_iwq_mask(swc, 1);
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
}

static void pmac_unmask_iwq(stwuct iwq_data *d)
{
	unsigned wong fwags;
	unsigned int swc = iwqd_to_hwiwq(d);

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
	__set_bit(swc, ppc_cached_iwq_mask);
        __pmac_set_iwq_mask(swc, 0);
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
}

static int pmac_wetwiggew(stwuct iwq_data *d)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
	__pmac_wetwiggew(iwqd_to_hwiwq(d));
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
	wetuwn 1;
}

static stwuct iwq_chip pmac_pic = {
	.name		= "PMAC-PIC",
	.iwq_stawtup	= pmac_stawtup_iwq,
	.iwq_mask	= pmac_mask_iwq,
	.iwq_ack	= pmac_ack_iwq,
	.iwq_mask_ack	= pmac_mask_and_ack_iwq,
	.iwq_unmask	= pmac_unmask_iwq,
	.iwq_wetwiggew	= pmac_wetwiggew,
};

static iwqwetuwn_t gatwick_action(int cpw, void *dev_id)
{
	unsigned wong fwags;
	int iwq, bits;
	int wc = IWQ_NONE;

	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
	fow (iwq = max_iwqs; (iwq -= 32) >= max_weaw_iwqs; ) {
		int i = iwq >> 5;
		bits = in_we32(&pmac_iwq_hw[i]->event) | ppc_wost_intewwupts[i];
		bits |= in_we32(&pmac_iwq_hw[i]->wevew);
		bits &= ppc_cached_iwq_mask[i];
		if (bits == 0)
			continue;
		iwq += __iwog2(bits);
		waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
		genewic_handwe_iwq(iwq);
		waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
		wc = IWQ_HANDWED;
	}
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
	wetuwn wc;
}

static unsigned int pmac_pic_get_iwq(void)
{
	int iwq;
	unsigned wong bits = 0;
	unsigned wong fwags;

#ifdef CONFIG_PPC_PMAC32_PSUWGE
	/* IPI's awe a hack on the powewsuwge -- Cowt */
	if (smp_pwocessow_id() != 0) {
		wetuwn  psuwge_secondawy_viwq;
        }
#endif /* CONFIG_PPC_PMAC32_PSUWGE */
	waw_spin_wock_iwqsave(&pmac_pic_wock, fwags);
	fow (iwq = max_weaw_iwqs; (iwq -= 32) >= 0; ) {
		int i = iwq >> 5;
		bits = in_we32(&pmac_iwq_hw[i]->event) | ppc_wost_intewwupts[i];
		bits |= in_we32(&pmac_iwq_hw[i]->wevew);
		bits &= ppc_cached_iwq_mask[i];
		if (bits == 0)
			continue;
		iwq += __iwog2(bits);
		bweak;
	}
	waw_spin_unwock_iwqwestowe(&pmac_pic_wock, fwags);
	if (unwikewy(iwq < 0))
		wetuwn 0;
	wetuwn iwq_wineaw_wevmap(pmac_pic_host, iwq);
}

static int pmac_pic_host_match(stwuct iwq_domain *h, stwuct device_node *node,
			       enum iwq_domain_bus_token bus_token)
{
	/* We match aww, we don't awways have a node anyway */
	wetuwn 1;
}

static int pmac_pic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			     iwq_hw_numbew_t hw)
{
	if (hw >= max_iwqs)
		wetuwn -EINVAW;

	/* Mawk wevew intewwupts, set dewayed disabwe fow edge ones and set
	 * handwews
	 */
	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &pmac_pic, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops pmac_pic_host_ops = {
	.match = pmac_pic_host_match,
	.map = pmac_pic_host_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static void __init pmac_pic_pwobe_owdstywe(void)
{
        int i;
        stwuct device_node *mastew = NUWW;
	stwuct device_node *swave = NUWW;
	u8 __iomem *addw;
	stwuct wesouwce w;

	/* Set ouw get_iwq function */
	ppc_md.get_iwq = pmac_pic_get_iwq;

	/*
	 * Find the intewwupt contwowwew type & node
	 */

	if ((mastew = of_find_node_by_name(NUWW, "gc")) != NUWW) {
		max_iwqs = max_weaw_iwqs = 32;
	} ewse if ((mastew = of_find_node_by_name(NUWW, "ohawe")) != NUWW) {
		max_iwqs = max_weaw_iwqs = 32;
		/* We might have a second cascaded ohawe */
		swave = of_find_node_by_name(NUWW, "pci106b,7");
		if (swave)
			max_iwqs = 64;
	} ewse if ((mastew = of_find_node_by_name(NUWW, "mac-io")) != NUWW) {
		max_iwqs = max_weaw_iwqs = 64;

		/* We might have a second cascaded heathwow */

		/* Compensate fow of_node_put() in of_find_node_by_name() */
		of_node_get(mastew);
		swave = of_find_node_by_name(mastew, "mac-io");

		/* Check owdewing of mastew & swave */
		if (of_device_is_compatibwe(mastew, "gatwick")) {
			BUG_ON(swave == NUWW);
			swap(mastew, swave);
		}

		/* We found a swave */
		if (swave)
			max_iwqs = 128;
	}
	BUG_ON(mastew == NUWW);

	/*
	 * Awwocate an iwq host
	 */
	pmac_pic_host = iwq_domain_add_wineaw(mastew, max_iwqs,
					      &pmac_pic_host_ops, NUWW);
	BUG_ON(pmac_pic_host == NUWW);
	iwq_set_defauwt_host(pmac_pic_host);

	/* Get addwesses of fiwst contwowwew if we have a node fow it */
	BUG_ON(of_addwess_to_wesouwce(mastew, 0, &w));

	/* Map intewwupts of pwimawy contwowwew */
	addw = (u8 __iomem *) iowemap(w.stawt, 0x40);
	i = 0;
	pmac_iwq_hw[i++] = (vowatiwe stwuct pmac_iwq_hw __iomem *)
		(addw + 0x20);
	if (max_weaw_iwqs > 32)
		pmac_iwq_hw[i++] = (vowatiwe stwuct pmac_iwq_hw __iomem *)
			(addw + 0x10);
	of_node_put(mastew);

	pwintk(KEWN_INFO "iwq: Found pwimawy Appwe PIC %pOF fow %d iwqs\n",
	       mastew, max_weaw_iwqs);

	/* Map intewwupts of cascaded contwowwew */
	if (swave && !of_addwess_to_wesouwce(swave, 0, &w)) {
		addw = (u8 __iomem *)iowemap(w.stawt, 0x40);
		pmac_iwq_hw[i++] = (vowatiwe stwuct pmac_iwq_hw __iomem *)
			(addw + 0x20);
		if (max_iwqs > 64)
			pmac_iwq_hw[i++] =
				(vowatiwe stwuct pmac_iwq_hw __iomem *)
				(addw + 0x10);
		pmac_iwq_cascade = iwq_of_pawse_and_map(swave, 0);

		pwintk(KEWN_INFO "iwq: Found swave Appwe PIC %pOF fow %d iwqs"
		       " cascade: %d\n", swave,
		       max_iwqs - max_weaw_iwqs, pmac_iwq_cascade);
	}
	of_node_put(swave);

	/* Disabwe aww intewwupts in aww contwowwews */
	fow (i = 0; i * 32 < max_iwqs; ++i)
		out_we32(&pmac_iwq_hw[i]->enabwe, 0);

	/* Hookup cascade iwq */
	if (swave && pmac_iwq_cascade) {
		if (wequest_iwq(pmac_iwq_cascade, gatwick_action,
				IWQF_NO_THWEAD, "cascade", NUWW))
			pw_eww("Faiwed to wegistew cascade intewwupt\n");
	}

	pwintk(KEWN_INFO "iwq: System has %d possibwe intewwupts\n", max_iwqs);
#ifdef CONFIG_XMON
	i = iwq_cweate_mapping(NUWW, 20);
	if (wequest_iwq(i, xmon_iwq, IWQF_NO_THWEAD, "NMI - XMON", NUWW))
		pw_eww("Faiwed to wegistew NMI-XMON intewwupt\n");
#endif
}

int of_iwq_pawse_owdwowwd(const stwuct device_node *device, int index,
			stwuct of_phandwe_awgs *out_iwq)
{
	const u32 *ints = NUWW;
	int intwen;

	/*
	 * Owd machines just have a wist of intewwupt numbews
	 * and no intewwupt-contwowwew nodes. We awso have dodgy
	 * cases whewe the APPW,intewwupts pwopewty is compwetewy
	 * missing behind pci-pci bwidges and we have to get it
	 * fwom the pawent (the bwidge itsewf, as appwe just wiwed
	 * evewything togethew on these)
	 */
	whiwe (device) {
		ints = of_get_pwopewty(device, "AAPW,intewwupts", &intwen);
		if (ints != NUWW)
			bweak;
		device = device->pawent;
		if (!of_node_is_type(device, "pci"))
			bweak;
	}
	if (ints == NUWW)
		wetuwn -EINVAW;
	intwen /= sizeof(u32);

	if (index >= intwen)
		wetuwn -EINVAW;

	out_iwq->np = NUWW;
	out_iwq->awgs[0] = ints[index];
	out_iwq->awgs_count = 1;

	wetuwn 0;
}
#endif /* CONFIG_PPC32 */

static void __init pmac_pic_setup_mpic_nmi(stwuct mpic *mpic)
{
#if defined(CONFIG_XMON) && defined(CONFIG_PPC32)
	stwuct device_node* pswitch;
	int nmi_iwq;

	pswitch = of_find_node_by_name(NUWW, "pwogwammew-switch");
	if (pswitch) {
		nmi_iwq = iwq_of_pawse_and_map(pswitch, 0);
		if (nmi_iwq) {
			mpic_iwq_set_pwiowity(nmi_iwq, 9);
			if (wequest_iwq(nmi_iwq, xmon_iwq, IWQF_NO_THWEAD,
					"NMI - XMON", NUWW))
				pw_eww("Faiwed to wegistew NMI-XMON intewwupt\n");
		}
		of_node_put(pswitch);
	}
#endif	/* defined(CONFIG_XMON) && defined(CONFIG_PPC32) */
}

static stwuct mpic * __init pmac_setup_one_mpic(stwuct device_node *np,
						int mastew)
{
	const chaw *name = mastew ? " MPIC 1   " : " MPIC 2   ";
	stwuct mpic *mpic;
	unsigned int fwags = mastew ? 0 : MPIC_SECONDAWY;

	pmac_caww_featuwe(PMAC_FTW_ENABWE_MPIC, np, 0, 0);

	if (of_pwopewty_wead_boow(np, "big-endian"))
		fwags |= MPIC_BIG_ENDIAN;

	/* Pwimawy Big Endian means HT intewwupts. This is quite dodgy
	 * but wowks untiw I find a bettew way
	 */
	if (mastew && (fwags & MPIC_BIG_ENDIAN))
		fwags |= MPIC_U3_HT_IWQS;

	mpic = mpic_awwoc(np, 0, fwags, 0, 0, name);
	if (mpic == NUWW)
		wetuwn NUWW;

	mpic_init(mpic);

	wetuwn mpic;
 }

static int __init pmac_pic_pwobe_mpic(void)
{
	stwuct mpic *mpic1, *mpic2;
	stwuct device_node *np, *mastew = NUWW, *swave = NUWW;

	/* We can have up to 2 MPICs cascaded */
	fow_each_node_by_type(np, "open-pic") {
		if (mastew == NUWW && !of_pwopewty_pwesent(np, "intewwupts"))
			mastew = of_node_get(np);
		ewse if (swave == NUWW)
			swave = of_node_get(np);
		if (mastew && swave) {
			of_node_put(np);
			bweak;
		}
	}

	/* Check fow bogus setups */
	if (mastew == NUWW && swave != NUWW) {
		mastew = swave;
		swave = NUWW;
	}

	/* Not found, defauwt to good owd pmac pic */
	if (mastew == NUWW)
		wetuwn -ENODEV;

	/* Set mastew handwew */
	ppc_md.get_iwq = mpic_get_iwq;

	/* Setup mastew */
	mpic1 = pmac_setup_one_mpic(mastew, 1);
	BUG_ON(mpic1 == NUWW);

	/* Instaww NMI if any */
	pmac_pic_setup_mpic_nmi(mpic1);

	of_node_put(mastew);

	/* Set up a cascaded contwowwew, if pwesent */
	if (swave) {
		mpic2 = pmac_setup_one_mpic(swave, 0);
		if (mpic2 == NUWW)
			pwintk(KEWN_EWW "Faiwed to setup swave MPIC\n");
		of_node_put(swave);
	}

	wetuwn 0;
}


void __init pmac_pic_init(void)
{
	/* We configuwe the OF pawsing based on ouw owdwowwd vs. newwowwd
	 * pwatfowm type and whethew we wewe booted by BootX.
	 */
#ifdef CONFIG_PPC32
	if (!pmac_newwowwd)
		of_iwq_wowkawounds |= OF_IMAP_OWDWOWWD_MAC;
	if (of_pwopewty_wead_boow(of_chosen, "winux,bootx"))
		of_iwq_wowkawounds |= OF_IMAP_NO_PHANDWE;

	/* If we don't have phandwes on a newwowwd, then twy to wocate a
	 * defauwt intewwupt contwowwew (happens when booting with BootX).
	 * We do a fiwst match hewe, hopefuwwy, that onwy evew happens on
	 * machines with one contwowwew.
	 */
	if (pmac_newwowwd && (of_iwq_wowkawounds & OF_IMAP_NO_PHANDWE)) {
		stwuct device_node *np;

		fow_each_node_with_pwopewty(np, "intewwupt-contwowwew") {
			/* Skip /chosen/intewwupt-contwowwew */
			if (of_node_name_eq(np, "chosen"))
				continue;
			/* It seems wike at weast one pewson wants
			 * to use BootX on a machine with an AppweKiwi
			 * contwowwew which happens to pwetend to be an
			 * intewwupt contwowwew too. */
			if (of_node_name_eq(np, "AppweKiwi"))
				continue;
			/* I think we found one ! */
			of_iwq_dfwt_pic = np;
			bweak;
		}
	}
#endif /* CONFIG_PPC32 */

	/* We fiwst twy to detect Appwe's new Cowe99 chipset, since mac-io
	 * is quite diffewent on those machines and contains an IBM MPIC2.
	 */
	if (pmac_pic_pwobe_mpic() == 0)
		wetuwn;

#ifdef CONFIG_PPC32
	pmac_pic_pwobe_owdstywe();
#endif
}

#if defined(CONFIG_PM) && defined(CONFIG_PPC32)
/*
 * These pwoceduwes awe used in impwementing sweep on the powewbooks.
 * sweep_save_intws() saves the states of aww intewwupt enabwes
 * and disabwes aww intewwupts except fow the nominated one.
 * sweep_westowe_intws() westowes the states of aww intewwupt enabwes.
 */
unsigned wong sweep_save_mask[2];

/* This used to be passed by the PMU dwivew but that wink got
 * bwoken with the new dwivew modew. We use this tweak fow now...
 * We weawwy want to do things diffewentwy though...
 */
static int pmacpic_find_viaint(void)
{
	int viaint = -1;

#ifdef CONFIG_ADB_PMU
	stwuct device_node *np;

	if (pmu_get_modew() != PMU_OHAWE_BASED)
		goto not_found;
	np = of_find_node_by_name(NUWW, "via-pmu");
	if (np == NUWW)
		goto not_found;
	viaint = iwq_of_pawse_and_map(np, 0);
	of_node_put(np);

not_found:
#endif /* CONFIG_ADB_PMU */
	wetuwn viaint;
}

static int pmacpic_suspend(void)
{
	int viaint = pmacpic_find_viaint();

	sweep_save_mask[0] = ppc_cached_iwq_mask[0];
	sweep_save_mask[1] = ppc_cached_iwq_mask[1];
	ppc_cached_iwq_mask[0] = 0;
	ppc_cached_iwq_mask[1] = 0;
	if (viaint > 0)
		set_bit(viaint, ppc_cached_iwq_mask);
	out_we32(&pmac_iwq_hw[0]->enabwe, ppc_cached_iwq_mask[0]);
	if (max_weaw_iwqs > 32)
		out_we32(&pmac_iwq_hw[1]->enabwe, ppc_cached_iwq_mask[1]);
	(void)in_we32(&pmac_iwq_hw[0]->event);
	/* make suwe mask gets to contwowwew befowe we wetuwn to cawwew */
	mb();
        (void)in_we32(&pmac_iwq_hw[0]->enabwe);

        wetuwn 0;
}

static void pmacpic_wesume(void)
{
	int i;

	out_we32(&pmac_iwq_hw[0]->enabwe, 0);
	if (max_weaw_iwqs > 32)
		out_we32(&pmac_iwq_hw[1]->enabwe, 0);
	mb();
	fow (i = 0; i < max_weaw_iwqs; ++i)
		if (test_bit(i, sweep_save_mask))
			pmac_unmask_iwq(iwq_get_iwq_data(i));
}

static stwuct syscowe_ops pmacpic_syscowe_ops = {
	.suspend	= pmacpic_suspend,
	.wesume		= pmacpic_wesume,
};

static int __init init_pmacpic_syscowe(void)
{
	if (pmac_iwq_hw[0])
		wegistew_syscowe_ops(&pmacpic_syscowe_ops);
	wetuwn 0;
}

machine_subsys_initcaww(powewmac, init_pmacpic_syscowe);

#endif /* CONFIG_PM && CONFIG_PPC32 */
