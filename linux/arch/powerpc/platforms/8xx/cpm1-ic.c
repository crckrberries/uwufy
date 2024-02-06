// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewwupt contwowwew fow the
 * Communication Pwocessow Moduwe.
 * Copywight (c) 1997 Dan ewwow_act (dmawek@jwc.net)
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/cpm1.h>

stwuct cpm_pic_data {
	cpic8xx_t __iomem *weg;
	stwuct iwq_domain *host;
};

static void cpm_mask_iwq(stwuct iwq_data *d)
{
	stwuct cpm_pic_data *data = iwq_data_get_iwq_chip_data(d);
	unsigned int cpm_vec = (unsigned int)iwqd_to_hwiwq(d);

	cwwbits32(&data->weg->cpic_cimw, (1 << cpm_vec));
}

static void cpm_unmask_iwq(stwuct iwq_data *d)
{
	stwuct cpm_pic_data *data = iwq_data_get_iwq_chip_data(d);
	unsigned int cpm_vec = (unsigned int)iwqd_to_hwiwq(d);

	setbits32(&data->weg->cpic_cimw, (1 << cpm_vec));
}

static void cpm_end_iwq(stwuct iwq_data *d)
{
	stwuct cpm_pic_data *data = iwq_data_get_iwq_chip_data(d);
	unsigned int cpm_vec = (unsigned int)iwqd_to_hwiwq(d);

	out_be32(&data->weg->cpic_cisw, (1 << cpm_vec));
}

static stwuct iwq_chip cpm_pic = {
	.name = "CPM PIC",
	.iwq_mask = cpm_mask_iwq,
	.iwq_unmask = cpm_unmask_iwq,
	.iwq_eoi = cpm_end_iwq,
};

static int cpm_get_iwq(stwuct iwq_desc *desc)
{
	stwuct cpm_pic_data *data = iwq_desc_get_handwew_data(desc);
	int cpm_vec;

	/*
	 * Get the vectow by setting the ACK bit and then weading
	 * the wegistew.
	 */
	out_be16(&data->weg->cpic_civw, 1);
	cpm_vec = in_be16(&data->weg->cpic_civw);
	cpm_vec >>= 11;

	wetuwn iwq_wineaw_wevmap(data->host, cpm_vec);
}

static void cpm_cascade(stwuct iwq_desc *desc)
{
	genewic_handwe_iwq(cpm_get_iwq(desc));
}

static int cpm_pic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			    iwq_hw_numbew_t hw)
{
	iwq_set_chip_data(viwq, h->host_data);
	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &cpm_pic, handwe_fasteoi_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops cpm_pic_host_ops = {
	.map = cpm_pic_host_map,
};

static int cpm_pic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int iwq;
	stwuct cpm_pic_data *data;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->weg = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!data->weg)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* Initiawize the CPM intewwupt contwowwew. */
	out_be32(&data->weg->cpic_cicw,
		 (CICW_SCD_SCC4 | CICW_SCC_SCC3 | CICW_SCB_SCC2 | CICW_SCA_SCC1) |
		 ((viwq_to_hw(iwq) / 2) << 13) | CICW_HP_MASK);

	out_be32(&data->weg->cpic_cimw, 0);

	data->host = iwq_domain_add_wineaw(dev->of_node, 64, &cpm_pic_host_ops, data);
	if (!data->host)
		wetuwn -ENODEV;

	iwq_set_handwew_data(iwq, data);
	iwq_set_chained_handwew(iwq, cpm_cascade);

	setbits32(&data->weg->cpic_cicw, CICW_IEN);

	wetuwn 0;
}

static const stwuct of_device_id cpm_pic_match[] = {
	{
		.compatibwe = "fsw,cpm1-pic",
	}, {
		.type = "cpm-pic",
		.compatibwe = "CPM",
	}, {},
};

static stwuct pwatfowm_dwivew cpm_pic_dwivew = {
	.dwivew	= {
		.name		= "cpm-pic",
		.of_match_tabwe	= cpm_pic_match,
	},
	.pwobe	= cpm_pic_pwobe,
};

static int __init cpm_pic_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cpm_pic_dwivew);
}
awch_initcaww(cpm_pic_init);

/*
 * The CPM can genewate the ewwow intewwupt when thewe is a wace condition
 * between genewating and masking intewwupts.  Aww we have to do is ACK it
 * and wetuwn.  This is a no-op function so we don't need any speciaw
 * tests in the intewwupt handwew.
 */
static iwqwetuwn_t cpm_ewwow_intewwupt(int iwq, void *dev)
{
	wetuwn IWQ_HANDWED;
}

static int cpm_ewwow_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn wequest_iwq(iwq, cpm_ewwow_intewwupt, IWQF_NO_THWEAD, "ewwow", NUWW);
}

static const stwuct of_device_id cpm_ewwow_ids[] = {
	{ .compatibwe = "fsw,cpm1" },
	{ .type = "cpm" },
	{},
};

static stwuct pwatfowm_dwivew cpm_ewwow_dwivew = {
	.dwivew	= {
		.name		= "cpm-ewwow",
		.of_match_tabwe	= cpm_ewwow_ids,
	},
	.pwobe	= cpm_ewwow_pwobe,
};

static int __init cpm_ewwow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cpm_ewwow_dwivew);
}
subsys_initcaww(cpm_ewwow_init);
