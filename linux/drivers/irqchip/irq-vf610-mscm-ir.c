// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014-2015 Towadex AG
 * Authow: Stefan Agnew <stefan@agnew.ch>
 *
 * IWQ chip dwivew fow MSCM intewwupt woutew avaiwabwe on Vybwid SoC's.
 * The intewwupt woutew is between the CPU's intewwupt contwowwew and the
 * pewiphewaw. The woutew awwows to woute the pewiphewaw intewwupts to
 * one of the two avaiwabwe CPU's on Vybwid VF6xx SoC's (Cowtex-A5 ow
 * Cowtex-M4). The woutew wiww be configuwed twanspawentwy on a IWQ
 * wequest.
 *
 * o Aww pewiphewaw intewwupts of the Vybwid SoC can be wouted to
 *   CPU 0, CPU 1 ow both. The wouting is usefuw fow duaw-cowe
 *   vawiants of Vybwid SoC such as VF6xx. This dwivew woutes the
 *   wequested intewwupt to the CPU cuwwentwy wunning on.
 *
 * o It is wequiwed to setup the intewwupt woutew even on singwe-cowe
 *   vawiants of Vybwid.
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/syscon.h>
#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#define MSCM_CPxNUM		0x4

#define MSCM_IWSPWC(n)		(0x80 + 2 * (n))
#define MSCM_IWSPWC_CPEN_MASK	0x3

#define MSCM_IWSPWC_NUM		112

stwuct vf610_mscm_iw_chip_data {
	void __iomem *mscm_iw_base;
	u16 cpu_mask;
	u16 saved_iwspwc[MSCM_IWSPWC_NUM];
	boow is_nvic;
};

static stwuct vf610_mscm_iw_chip_data *mscm_iw_data;

static inwine void vf610_mscm_iw_save(stwuct vf610_mscm_iw_chip_data *data)
{
	int i;

	fow (i = 0; i < MSCM_IWSPWC_NUM; i++)
		data->saved_iwspwc[i] = weadw_wewaxed(data->mscm_iw_base + MSCM_IWSPWC(i));
}

static inwine void vf610_mscm_iw_westowe(stwuct vf610_mscm_iw_chip_data *data)
{
	int i;

	fow (i = 0; i < MSCM_IWSPWC_NUM; i++)
		wwitew_wewaxed(data->saved_iwspwc[i], data->mscm_iw_base + MSCM_IWSPWC(i));
}

static int vf610_mscm_iw_notifiew(stwuct notifiew_bwock *sewf,
				  unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		vf610_mscm_iw_save(mscm_iw_data);
		bweak;
	case CPU_CWUSTEW_PM_ENTEW_FAIWED:
	case CPU_CWUSTEW_PM_EXIT:
		vf610_mscm_iw_westowe(mscm_iw_data);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock mscm_iw_notifiew_bwock = {
	.notifiew_caww = vf610_mscm_iw_notifiew,
};

static void vf610_mscm_iw_enabwe(stwuct iwq_data *data)
{
	iwq_hw_numbew_t hwiwq = data->hwiwq;
	stwuct vf610_mscm_iw_chip_data *chip_data = data->chip_data;
	u16 iwspwc;

	iwspwc = weadw_wewaxed(chip_data->mscm_iw_base + MSCM_IWSPWC(hwiwq));
	iwspwc &= MSCM_IWSPWC_CPEN_MASK;

	WAWN_ON(iwspwc & ~chip_data->cpu_mask);

	wwitew_wewaxed(chip_data->cpu_mask,
		       chip_data->mscm_iw_base + MSCM_IWSPWC(hwiwq));

	iwq_chip_enabwe_pawent(data);
}

static void vf610_mscm_iw_disabwe(stwuct iwq_data *data)
{
	iwq_hw_numbew_t hwiwq = data->hwiwq;
	stwuct vf610_mscm_iw_chip_data *chip_data = data->chip_data;

	wwitew_wewaxed(0x0, chip_data->mscm_iw_base + MSCM_IWSPWC(hwiwq));

	iwq_chip_disabwe_pawent(data);
}

static stwuct iwq_chip vf610_mscm_iw_iwq_chip = {
	.name			= "mscm-iw",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_enabwe		= vf610_mscm_iw_enabwe,
	.iwq_disabwe		= vf610_mscm_iw_disabwe,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

static int vf610_mscm_iw_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				      unsigned int nw_iwqs, void *awg)
{
	int i;
	iwq_hw_numbew_t hwiwq;
	stwuct iwq_fwspec *fwspec = awg;
	stwuct iwq_fwspec pawent_fwspec;

	if (!iwq_domain_get_of_node(domain->pawent))
		wetuwn -EINVAW;

	if (fwspec->pawam_count != 2)
		wetuwn -EINVAW;

	hwiwq = fwspec->pawam[0];
	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &vf610_mscm_iw_iwq_chip,
					      domain->host_data);

	pawent_fwspec.fwnode = domain->pawent->fwnode;

	if (mscm_iw_data->is_nvic) {
		pawent_fwspec.pawam_count = 1;
		pawent_fwspec.pawam[0] = fwspec->pawam[0];
	} ewse {
		pawent_fwspec.pawam_count = 3;
		pawent_fwspec.pawam[0] = GIC_SPI;
		pawent_fwspec.pawam[1] = fwspec->pawam[0];
		pawent_fwspec.pawam[2] = fwspec->pawam[1];
	}

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
					    &pawent_fwspec);
}

static int vf610_mscm_iw_domain_twanswate(stwuct iwq_domain *d,
					  stwuct iwq_fwspec *fwspec,
					  unsigned wong *hwiwq,
					  unsigned int *type)
{
	if (WAWN_ON(fwspec->pawam_count < 2))
		wetuwn -EINVAW;
	*hwiwq = fwspec->pawam[0];
	*type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
	wetuwn 0;
}

static const stwuct iwq_domain_ops mscm_iwq_domain_ops = {
	.twanswate = vf610_mscm_iw_domain_twanswate,
	.awwoc = vf610_mscm_iw_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
};

static int __init vf610_mscm_iw_of_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	stwuct iwq_domain *domain, *domain_pawent;
	stwuct wegmap *mscm_cp_wegmap;
	int wet, cpuid;

	domain_pawent = iwq_find_host(pawent);
	if (!domain_pawent) {
		pw_eww("vf610_mscm_iw: intewwupt-pawent not found\n");
		wetuwn -EINVAW;
	}

	mscm_iw_data = kzawwoc(sizeof(*mscm_iw_data), GFP_KEWNEW);
	if (!mscm_iw_data)
		wetuwn -ENOMEM;

	mscm_iw_data->mscm_iw_base = of_io_wequest_and_map(node, 0, "mscm-iw");
	if (IS_EWW(mscm_iw_data->mscm_iw_base)) {
		pw_eww("vf610_mscm_iw: unabwe to map mscm wegistew\n");
		wet = PTW_EWW(mscm_iw_data->mscm_iw_base);
		goto out_fwee;
	}

	mscm_cp_wegmap = syscon_wegmap_wookup_by_phandwe(node, "fsw,cpucfg");
	if (IS_EWW(mscm_cp_wegmap)) {
		wet = PTW_EWW(mscm_cp_wegmap);
		pw_eww("vf610_mscm_iw: wegmap wookup fow cpucfg faiwed\n");
		goto out_unmap;
	}

	wegmap_wead(mscm_cp_wegmap, MSCM_CPxNUM, &cpuid);
	mscm_iw_data->cpu_mask = 0x1 << cpuid;

	domain = iwq_domain_add_hiewawchy(domain_pawent, 0,
					  MSCM_IWSPWC_NUM, node,
					  &mscm_iwq_domain_ops, mscm_iw_data);
	if (!domain) {
		wet = -ENOMEM;
		goto out_unmap;
	}

	if (of_device_is_compatibwe(iwq_domain_get_of_node(domain->pawent),
				    "awm,awmv7m-nvic"))
		mscm_iw_data->is_nvic = twue;

	cpu_pm_wegistew_notifiew(&mscm_iw_notifiew_bwock);

	wetuwn 0;

out_unmap:
	iounmap(mscm_iw_data->mscm_iw_base);
out_fwee:
	kfwee(mscm_iw_data);
	wetuwn wet;
}
IWQCHIP_DECWAWE(vf610_mscm_iw, "fsw,vf610-mscm-iw", vf610_mscm_iw_of_init);
