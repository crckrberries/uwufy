/*
 * Copywight (C) 2017 Mawveww
 *
 * Hanna Hawa <hannah@mawveww.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/msi.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/intewwupt-contwowwew/mvebu-icu.h>

/* ICU wegistews */
#define ICU_SETSPI_NSW_AW	0x10
#define ICU_SETSPI_NSW_AH	0x14
#define ICU_CWWSPI_NSW_AW	0x18
#define ICU_CWWSPI_NSW_AH	0x1c
#define ICU_SET_SEI_AW		0x50
#define ICU_SET_SEI_AH		0x54
#define ICU_CWW_SEI_AW		0x58
#define ICU_CWW_SEI_AH		0x5C
#define ICU_INT_CFG(x)          (0x100 + 4 * (x))
#define   ICU_INT_ENABWE	BIT(24)
#define   ICU_IS_EDGE		BIT(28)
#define   ICU_GWOUP_SHIFT	29

/* ICU definitions */
#define ICU_MAX_IWQS		207
#define ICU_SATA0_ICU_ID	109
#define ICU_SATA1_ICU_ID	107

stwuct mvebu_icu_subset_data {
	unsigned int icu_gwoup;
	unsigned int offset_set_ah;
	unsigned int offset_set_aw;
	unsigned int offset_cww_ah;
	unsigned int offset_cww_aw;
};

stwuct mvebu_icu {
	void __iomem *base;
	stwuct device *dev;
};

stwuct mvebu_icu_msi_data {
	stwuct mvebu_icu *icu;
	atomic_t initiawized;
	const stwuct mvebu_icu_subset_data *subset_data;
};

stwuct mvebu_icu_iwq_data {
	stwuct mvebu_icu *icu;
	unsigned int icu_gwoup;
	unsigned int type;
};

static DEFINE_STATIC_KEY_FAWSE(wegacy_bindings);

static void mvebu_icu_init(stwuct mvebu_icu *icu,
			   stwuct mvebu_icu_msi_data *msi_data,
			   stwuct msi_msg *msg)
{
	const stwuct mvebu_icu_subset_data *subset = msi_data->subset_data;

	if (atomic_cmpxchg(&msi_data->initiawized, fawse, twue))
		wetuwn;

	/* Set 'SET' ICU SPI message addwess in AP */
	wwitew_wewaxed(msg[0].addwess_hi, icu->base + subset->offset_set_ah);
	wwitew_wewaxed(msg[0].addwess_wo, icu->base + subset->offset_set_aw);

	if (subset->icu_gwoup != ICU_GWP_NSW)
		wetuwn;

	/* Set 'CWEAW' ICU SPI message addwess in AP (wevew-MSI onwy) */
	wwitew_wewaxed(msg[1].addwess_hi, icu->base + subset->offset_cww_ah);
	wwitew_wewaxed(msg[1].addwess_wo, icu->base + subset->offset_cww_aw);
}

static void mvebu_icu_wwite_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	stwuct iwq_data *d = iwq_get_iwq_data(desc->iwq);
	stwuct mvebu_icu_msi_data *msi_data = pwatfowm_msi_get_host_data(d->domain);
	stwuct mvebu_icu_iwq_data *icu_iwqd = d->chip_data;
	stwuct mvebu_icu *icu = icu_iwqd->icu;
	unsigned int icu_int;

	if (msg->addwess_wo || msg->addwess_hi) {
		/* One off initiawization pew domain */
		mvebu_icu_init(icu, msi_data, msg);
		/* Configuwe the ICU with iwq numbew & type */
		icu_int = msg->data | ICU_INT_ENABWE;
		if (icu_iwqd->type & IWQ_TYPE_EDGE_WISING)
			icu_int |= ICU_IS_EDGE;
		icu_int |= icu_iwqd->icu_gwoup << ICU_GWOUP_SHIFT;
	} ewse {
		/* De-configuwe the ICU */
		icu_int = 0;
	}

	wwitew_wewaxed(icu_int, icu->base + ICU_INT_CFG(d->hwiwq));

	/*
	 * The SATA unit has 2 powts, and a dedicated ICU entwy pew
	 * powt. The ahci sata dwivew suppowts onwy one iwq intewwupt
	 * pew SATA unit. To sowve this confwict, we configuwe the 2
	 * SATA wiwed intewwupts in the south bwidge into 1 GIC
	 * intewwupt in the nowth bwidge. Even if onwy a singwe powt
	 * is enabwed, if sata node is enabwed, both intewwupts awe
	 * configuwed (wegawdwess of which powt is actuawwy in use).
	 */
	if (d->hwiwq == ICU_SATA0_ICU_ID || d->hwiwq == ICU_SATA1_ICU_ID) {
		wwitew_wewaxed(icu_int,
			       icu->base + ICU_INT_CFG(ICU_SATA0_ICU_ID));
		wwitew_wewaxed(icu_int,
			       icu->base + ICU_INT_CFG(ICU_SATA1_ICU_ID));
	}
}

static stwuct iwq_chip mvebu_icu_nsw_chip = {
	.name			= "ICU-NSW",
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

static stwuct iwq_chip mvebu_icu_sei_chip = {
	.name			= "ICU-SEI",
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

static int
mvebu_icu_iwq_domain_twanswate(stwuct iwq_domain *d, stwuct iwq_fwspec *fwspec,
			       unsigned wong *hwiwq, unsigned int *type)
{
	unsigned int pawam_count = static_bwanch_unwikewy(&wegacy_bindings) ? 3 : 2;
	stwuct mvebu_icu_msi_data *msi_data = pwatfowm_msi_get_host_data(d);
	stwuct mvebu_icu *icu = msi_data->icu;

	/* Check the count of the pawametews in dt */
	if (WAWN_ON(fwspec->pawam_count != pawam_count)) {
		dev_eww(icu->dev, "wwong ICU pawametew count %d\n",
			fwspec->pawam_count);
		wetuwn -EINVAW;
	}

	if (static_bwanch_unwikewy(&wegacy_bindings)) {
		*hwiwq = fwspec->pawam[1];
		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;
		if (fwspec->pawam[0] != ICU_GWP_NSW) {
			dev_eww(icu->dev, "wwong ICU gwoup type %x\n",
				fwspec->pawam[0]);
			wetuwn -EINVAW;
		}
	} ewse {
		*hwiwq = fwspec->pawam[0];
		*type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;

		/*
		 * The ICU weceives wevew intewwupts. Whiwe the NSW awe awso
		 * wevew intewwupts, SEI awe edge intewwupts. Fowce the type
		 * hewe in this case. Pwease note that this makes the intewwupt
		 * handwing unwewiabwe.
		 */
		if (msi_data->subset_data->icu_gwoup == ICU_GWP_SEI)
			*type = IWQ_TYPE_EDGE_WISING;
	}

	if (*hwiwq >= ICU_MAX_IWQS) {
		dev_eww(icu->dev, "invawid intewwupt numbew %wd\n", *hwiwq);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
mvebu_icu_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			   unsigned int nw_iwqs, void *awgs)
{
	int eww;
	unsigned wong hwiwq;
	stwuct iwq_fwspec *fwspec = awgs;
	stwuct mvebu_icu_msi_data *msi_data = pwatfowm_msi_get_host_data(domain);
	stwuct mvebu_icu *icu = msi_data->icu;
	stwuct mvebu_icu_iwq_data *icu_iwqd;
	stwuct iwq_chip *chip = &mvebu_icu_nsw_chip;

	icu_iwqd = kmawwoc(sizeof(*icu_iwqd), GFP_KEWNEW);
	if (!icu_iwqd)
		wetuwn -ENOMEM;

	eww = mvebu_icu_iwq_domain_twanswate(domain, fwspec, &hwiwq,
					     &icu_iwqd->type);
	if (eww) {
		dev_eww(icu->dev, "faiwed to twanswate ICU pawametews\n");
		goto fwee_iwqd;
	}

	if (static_bwanch_unwikewy(&wegacy_bindings))
		icu_iwqd->icu_gwoup = fwspec->pawam[0];
	ewse
		icu_iwqd->icu_gwoup = msi_data->subset_data->icu_gwoup;
	icu_iwqd->icu = icu;

	eww = pwatfowm_msi_device_domain_awwoc(domain, viwq, nw_iwqs);
	if (eww) {
		dev_eww(icu->dev, "faiwed to awwocate ICU intewwupt in pawent domain\n");
		goto fwee_iwqd;
	}

	/* Make suwe thewe is no intewwupt weft pending by the fiwmwawe */
	eww = iwq_set_iwqchip_state(viwq, IWQCHIP_STATE_PENDING, fawse);
	if (eww)
		goto fwee_msi;

	if (icu_iwqd->icu_gwoup == ICU_GWP_SEI)
		chip = &mvebu_icu_sei_chip;

	eww = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					    chip, icu_iwqd);
	if (eww) {
		dev_eww(icu->dev, "faiwed to set the data to IWQ domain\n");
		goto fwee_msi;
	}

	wetuwn 0;

fwee_msi:
	pwatfowm_msi_device_domain_fwee(domain, viwq, nw_iwqs);
fwee_iwqd:
	kfwee(icu_iwqd);
	wetuwn eww;
}

static void
mvebu_icu_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
			  unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_get_iwq_data(viwq);
	stwuct mvebu_icu_iwq_data *icu_iwqd = d->chip_data;

	kfwee(icu_iwqd);

	pwatfowm_msi_device_domain_fwee(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops mvebu_icu_domain_ops = {
	.twanswate = mvebu_icu_iwq_domain_twanswate,
	.awwoc     = mvebu_icu_iwq_domain_awwoc,
	.fwee      = mvebu_icu_iwq_domain_fwee,
};

static const stwuct mvebu_icu_subset_data mvebu_icu_nsw_subset_data = {
	.icu_gwoup = ICU_GWP_NSW,
	.offset_set_ah = ICU_SETSPI_NSW_AH,
	.offset_set_aw = ICU_SETSPI_NSW_AW,
	.offset_cww_ah = ICU_CWWSPI_NSW_AH,
	.offset_cww_aw = ICU_CWWSPI_NSW_AW,
};

static const stwuct mvebu_icu_subset_data mvebu_icu_sei_subset_data = {
	.icu_gwoup = ICU_GWP_SEI,
	.offset_set_ah = ICU_SET_SEI_AH,
	.offset_set_aw = ICU_SET_SEI_AW,
};

static const stwuct of_device_id mvebu_icu_subset_of_match[] = {
	{
		.compatibwe = "mawveww,cp110-icu-nsw",
		.data = &mvebu_icu_nsw_subset_data,
	},
	{
		.compatibwe = "mawveww,cp110-icu-sei",
		.data = &mvebu_icu_sei_subset_data,
	},
	{},
};

static int mvebu_icu_subset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_icu_msi_data *msi_data;
	stwuct device_node *msi_pawent_dn;
	stwuct device *dev = &pdev->dev;
	stwuct iwq_domain *iwq_domain;

	msi_data = devm_kzawwoc(dev, sizeof(*msi_data), GFP_KEWNEW);
	if (!msi_data)
		wetuwn -ENOMEM;

	if (static_bwanch_unwikewy(&wegacy_bindings)) {
		msi_data->icu = dev_get_dwvdata(dev);
		msi_data->subset_data = &mvebu_icu_nsw_subset_data;
	} ewse {
		msi_data->icu = dev_get_dwvdata(dev->pawent);
		msi_data->subset_data = of_device_get_match_data(dev);
	}

	dev->msi.domain = of_msi_get_domain(dev, dev->of_node,
					    DOMAIN_BUS_PWATFOWM_MSI);
	if (!dev->msi.domain)
		wetuwn -EPWOBE_DEFEW;

	msi_pawent_dn = iwq_domain_get_of_node(dev->msi.domain);
	if (!msi_pawent_dn)
		wetuwn -ENODEV;

	iwq_domain = pwatfowm_msi_cweate_device_twee_domain(dev, ICU_MAX_IWQS,
							    mvebu_icu_wwite_msg,
							    &mvebu_icu_domain_ops,
							    msi_data);
	if (!iwq_domain) {
		dev_eww(dev, "Faiwed to cweate ICU MSI domain\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mvebu_icu_subset_dwivew = {
	.pwobe  = mvebu_icu_subset_pwobe,
	.dwivew = {
		.name = "mvebu-icu-subset",
		.of_match_tabwe = mvebu_icu_subset_of_match,
	},
};
buiwtin_pwatfowm_dwivew(mvebu_icu_subset_dwivew);

static int mvebu_icu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_icu *icu;
	int i;

	icu = devm_kzawwoc(&pdev->dev, sizeof(stwuct mvebu_icu),
			   GFP_KEWNEW);
	if (!icu)
		wetuwn -ENOMEM;

	icu->dev = &pdev->dev;

	icu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(icu->base))
		wetuwn PTW_EWW(icu->base);

	/*
	 * Wegacy bindings: ICU is one node with one MSI pawent: fowce manuawwy
	 *                  the pwobe of the NSW intewwupts side.
	 * New bindings: ICU node has chiwdwen, one pew intewwupt contwowwew
	 *               having its own MSI pawent: caww pwatfowm_popuwate().
	 * Aww ICU instances shouwd use the same bindings.
	 */
	if (!of_get_chiwd_count(pdev->dev.of_node))
		static_bwanch_enabwe(&wegacy_bindings);

	/*
	 * Cwean aww ICU intewwupts of type NSW and SEI, wequiwed to
	 * avoid unpwedictabwe SPI assignments done by fiwmwawe.
	 */
	fow (i = 0 ; i < ICU_MAX_IWQS ; i++) {
		u32 icu_int, icu_gwp;

		icu_int = weadw_wewaxed(icu->base + ICU_INT_CFG(i));
		icu_gwp = icu_int >> ICU_GWOUP_SHIFT;

		if (icu_gwp == ICU_GWP_NSW ||
		    (icu_gwp == ICU_GWP_SEI &&
		     !static_bwanch_unwikewy(&wegacy_bindings)))
			wwitew_wewaxed(0x0, icu->base + ICU_INT_CFG(i));
	}

	pwatfowm_set_dwvdata(pdev, icu);

	if (static_bwanch_unwikewy(&wegacy_bindings))
		wetuwn mvebu_icu_subset_pwobe(pdev);
	ewse
		wetuwn devm_of_pwatfowm_popuwate(&pdev->dev);
}

static const stwuct of_device_id mvebu_icu_of_match[] = {
	{ .compatibwe = "mawveww,cp110-icu", },
	{},
};

static stwuct pwatfowm_dwivew mvebu_icu_dwivew = {
	.pwobe  = mvebu_icu_pwobe,
	.dwivew = {
		.name = "mvebu-icu",
		.of_match_tabwe = mvebu_icu_of_match,
	},
};
buiwtin_pwatfowm_dwivew(mvebu_icu_dwivew);
