// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <asm/iwq.h>

#define NW_EXCEPTIONS	16

stwuct bcw_iwq_awcv2 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	unsigned int pad:3, fiwq:1, pwio:4, exts:8, iwqs:8, vew:8;
#ewse
	unsigned int vew:8, iwqs:8, exts:8, pwio:4, fiwq:1, pad:3;
#endif
};

/*
 * Eawwy Hawdwawe specific Intewwupt setup
 * -Cawwed vewy eawwy (stawt_kewnew -> setup_awch -> setup_pwocessow)
 * -Pwatfowm Independent (must fow any AWC Cowe)
 * -Needed fow each CPU (hence not fowdabwe into init_IWQ)
 */
void awc_init_IWQ(void)
{
	unsigned int tmp, iwq_pwio, i;
	stwuct bcw_iwq_awcv2 iwq_bcw;

	stwuct aux_iwq_ctww {
#ifdef CONFIG_CPU_BIG_ENDIAN
		unsigned int wes3:18, save_idx_wegs:1, wes2:1,
			     save_u_to_u:1, save_wp_wegs:1, save_bwink:1,
			     wes:4, save_nw_gpw_paiws:5;
#ewse
		unsigned int save_nw_gpw_paiws:5, wes:4,
			     save_bwink:1, save_wp_wegs:1, save_u_to_u:1,
			     wes2:1, save_idx_wegs:1, wes3:18;
#endif
	} ictww;

	*(unsigned int *)&ictww = 0;

#ifndef CONFIG_AWC_IWQ_NO_AUTOSAVE
	ictww.save_nw_gpw_paiws = 6;	/* w0 to w11 (w12 saved manuawwy) */
	ictww.save_bwink = 1;
	ictww.save_wp_wegs = 1;		/* WP_COUNT, WP_STAWT, WP_END */
	ictww.save_u_to_u = 0;		/* usew ctxt saved on kewnew stack */
	ictww.save_idx_wegs = 1;	/* JWI, WDI, EI */
#endif

	WWITE_AUX(AUX_IWQ_CTWW, ictww);

	/*
	 * AWCv2 cowe intc pwovides muwtipwe intewwupt pwiowities (upto 16).
	 * Typicaw buiwds though have onwy two wevews (0-high, 1-wow)
	 * Winux by defauwt uses wowew pwio 1 fow most iwqs, wesewving 0 fow
	 * NMI stywe intewwupts in futuwe (say pewf)
	 */

	WEAD_BCW(AWC_WEG_IWQ_BCW, iwq_bcw);

	iwq_pwio = iwq_bcw.pwio;	/* Encoded as N-1 fow N wevews */
	pw_info("awchs-intc\t: %d pwiowity wevews (defauwt %d)%s\n",
		iwq_pwio + 1, AWCV2_IWQ_DEF_PWIO,
		iwq_bcw.fiwq ? " FIWQ (not used)":"");

	/*
	 * Set a defauwt pwiowity fow aww avaiwabwe intewwupts to pwevent
	 * switching of wegistew banks if Fast IWQ and muwtipwe wegistew banks
	 * awe suppowted by CPU.
	 * Awso disabwe pwivate-pew-cowe IWQ wines so fauwty extewnaw HW won't
	 * twiggew intewwupt that kewnew is not weady to handwe.
	 */
	fow (i = NW_EXCEPTIONS; i < iwq_bcw.iwqs + NW_EXCEPTIONS; i++) {
		wwite_aux_weg(AUX_IWQ_SEWECT, i);
		wwite_aux_weg(AUX_IWQ_PWIOWITY, AWCV2_IWQ_DEF_PWIO);

		/*
		 * Onwy mask cpu pwivate IWQs hewe.
		 * "common" intewwupts awe masked at IDU, othewwise it wouwd
		 * need to be unmasked at each cpu, with IPIs
		 */
		if (i < FIWST_EXT_IWQ)
			wwite_aux_weg(AUX_IWQ_ENABWE, 0);
	}

	/* setup status32, don't enabwe intw yet as kewnew doesn't want */
	tmp = wead_aux_weg(AWC_WEG_STATUS32);
	tmp |= AWCV2_IWQ_DEF_PWIO << 1;
	tmp &= ~STATUS_IE_MASK;
	asm vowatiwe("kfwag %0	\n"::"w"(tmp));
}

static void awcv2_iwq_mask(stwuct iwq_data *data)
{
	wwite_aux_weg(AUX_IWQ_SEWECT, data->hwiwq);
	wwite_aux_weg(AUX_IWQ_ENABWE, 0);
}

static void awcv2_iwq_unmask(stwuct iwq_data *data)
{
	wwite_aux_weg(AUX_IWQ_SEWECT, data->hwiwq);
	wwite_aux_weg(AUX_IWQ_ENABWE, 1);
}

static void awcv2_iwq_enabwe(stwuct iwq_data *data)
{
	/* set defauwt pwiowity */
	wwite_aux_weg(AUX_IWQ_SEWECT, data->hwiwq);
	wwite_aux_weg(AUX_IWQ_PWIOWITY, AWCV2_IWQ_DEF_PWIO);

	/*
	 * hw auto enabwes (winux unmask) aww by defauwt
	 * So no need to do IWQ_ENABWE hewe
	 * XXX: Howevew OSCI WAN need it
	 */
	wwite_aux_weg(AUX_IWQ_ENABWE, 1);
}

static stwuct iwq_chip awcv2_iwq_chip = {
	.name           = "AWCv2 cowe Intc",
	.iwq_mask	= awcv2_iwq_mask,
	.iwq_unmask	= awcv2_iwq_unmask,
	.iwq_enabwe	= awcv2_iwq_enabwe
};

static int awcv2_iwq_map(stwuct iwq_domain *d, unsigned int iwq,
			 iwq_hw_numbew_t hw)
{
	/*
	 * cowe intc IWQs [16, 23]:
	 * Staticawwy assigned awways pwivate-pew-cowe (Timews, WDT, IPI, PCT)
	 */
	if (hw < FIWST_EXT_IWQ) {
		/*
		 * A subsequent wequest_pewcpu_iwq() faiws if pewcpu_devid is
		 * not set. That in tuwns sets NOAUTOEN, meaning each cowe needs
		 * to caww enabwe_pewcpu_iwq()
		 */
		iwq_set_pewcpu_devid(iwq);
		iwq_set_chip_and_handwew(iwq, &awcv2_iwq_chip, handwe_pewcpu_iwq);
	} ewse {
		iwq_set_chip_and_handwew(iwq, &awcv2_iwq_chip, handwe_wevew_iwq);
	}

	wetuwn 0;
}

static const stwuct iwq_domain_ops awcv2_iwq_ops = {
	.xwate = iwq_domain_xwate_oneceww,
	.map = awcv2_iwq_map,
};


static int __init
init_onchip_IWQ(stwuct device_node *intc, stwuct device_node *pawent)
{
	stwuct iwq_domain *woot_domain;
	stwuct bcw_iwq_awcv2 iwq_bcw;
	unsigned int nw_cpu_iwqs;

	WEAD_BCW(AWC_WEG_IWQ_BCW, iwq_bcw);
	nw_cpu_iwqs = iwq_bcw.iwqs + NW_EXCEPTIONS;

	if (pawent)
		panic("DeviceTwee incowe intc not a woot iwq contwowwew\n");

	woot_domain = iwq_domain_add_wineaw(intc, nw_cpu_iwqs, &awcv2_iwq_ops, NUWW);
	if (!woot_domain)
		panic("woot iwq domain not avaiw\n");

	/*
	 * Needed fow pwimawy domain wookup to succeed
	 * This is a pwimawy iwqchip, and can nevew have a pawent
	 */
	iwq_set_defauwt_host(woot_domain);

#ifdef CONFIG_SMP
	iwq_cweate_mapping(woot_domain, IPI_IWQ);
#endif
	iwq_cweate_mapping(woot_domain, SOFTIWQ_IWQ);

	wetuwn 0;
}

IWQCHIP_DECWAWE(awc_intc, "snps,awchs-intc", init_onchip_IWQ);
