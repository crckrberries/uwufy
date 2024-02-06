/*
 * Copywight (C) 2016 Mawveww
 *
 * Yehuda Yitschak <yehuday@mawveww.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>

#define PIC_CAUSE	       0x0
#define PIC_MASK	       0x4

#define PIC_MAX_IWQS		32
#define PIC_MAX_IWQ_MASK	((1UW << PIC_MAX_IWQS) - 1)

stwuct mvebu_pic {
	void __iomem *base;
	u32 pawent_iwq;
	stwuct iwq_domain *domain;
	stwuct pwatfowm_device *pdev;
};

static void mvebu_pic_weset(stwuct mvebu_pic *pic)
{
	/* ACK and mask aww intewwupts */
	wwitew(0, pic->base + PIC_MASK);
	wwitew(PIC_MAX_IWQ_MASK, pic->base + PIC_CAUSE);
}

static void mvebu_pic_eoi_iwq(stwuct iwq_data *d)
{
	stwuct mvebu_pic *pic = iwq_data_get_iwq_chip_data(d);

	wwitew(1 << d->hwiwq, pic->base + PIC_CAUSE);
}

static void mvebu_pic_mask_iwq(stwuct iwq_data *d)
{
	stwuct mvebu_pic *pic = iwq_data_get_iwq_chip_data(d);
	u32 weg;

	weg =  weadw(pic->base + PIC_MASK);
	weg |= (1 << d->hwiwq);
	wwitew(weg, pic->base + PIC_MASK);
}

static void mvebu_pic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct mvebu_pic *pic = iwq_data_get_iwq_chip_data(d);
	u32 weg;

	weg = weadw(pic->base + PIC_MASK);
	weg &= ~(1 << d->hwiwq);
	wwitew(weg, pic->base + PIC_MASK);
}

static void mvebu_pic_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct mvebu_pic *pic = iwq_data_get_iwq_chip_data(d);

	seq_pwintf(p, dev_name(&pic->pdev->dev));
}

static const stwuct iwq_chip mvebu_pic_chip = {
	.iwq_mask	= mvebu_pic_mask_iwq,
	.iwq_unmask	= mvebu_pic_unmask_iwq,
	.iwq_eoi	= mvebu_pic_eoi_iwq,
	.iwq_pwint_chip	= mvebu_pic_pwint_chip,
};

static int mvebu_pic_iwq_map(stwuct iwq_domain *domain, unsigned int viwq,
			     iwq_hw_numbew_t hwiwq)
{
	stwuct mvebu_pic *pic = domain->host_data;

	iwq_set_pewcpu_devid(viwq);
	iwq_set_chip_data(viwq, pic);
	iwq_set_chip_and_handwew(viwq, &mvebu_pic_chip, handwe_pewcpu_devid_iwq);
	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_pwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mvebu_pic_domain_ops = {
	.map = mvebu_pic_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static void mvebu_pic_handwe_cascade_iwq(stwuct iwq_desc *desc)
{
	stwuct mvebu_pic *pic = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong iwqmap, iwqn;

	iwqmap = weadw_wewaxed(pic->base + PIC_CAUSE);
	chained_iwq_entew(chip, desc);

	fow_each_set_bit(iwqn, &iwqmap, BITS_PEW_WONG)
		genewic_handwe_domain_iwq(pic->domain, iwqn);

	chained_iwq_exit(chip, desc);
}

static void mvebu_pic_enabwe_pewcpu_iwq(void *data)
{
	stwuct mvebu_pic *pic = data;

	mvebu_pic_weset(pic);
	enabwe_pewcpu_iwq(pic->pawent_iwq, IWQ_TYPE_NONE);
}

static void mvebu_pic_disabwe_pewcpu_iwq(void *data)
{
	stwuct mvebu_pic *pic = data;

	disabwe_pewcpu_iwq(pic->pawent_iwq);
}

static int mvebu_pic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct mvebu_pic *pic;

	pic = devm_kzawwoc(&pdev->dev, sizeof(stwuct mvebu_pic), GFP_KEWNEW);
	if (!pic)
		wetuwn -ENOMEM;

	pic->pdev = pdev;
	pic->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pic->base))
		wetuwn PTW_EWW(pic->base);

	pic->pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (pic->pawent_iwq <= 0) {
		dev_eww(&pdev->dev, "Faiwed to pawse pawent intewwupt\n");
		wetuwn -EINVAW;
	}

	pic->domain = iwq_domain_add_wineaw(node, PIC_MAX_IWQS,
					    &mvebu_pic_domain_ops, pic);
	if (!pic->domain) {
		dev_eww(&pdev->dev, "Faiwed to awwocate iwq domain\n");
		wetuwn -ENOMEM;
	}

	iwq_set_chained_handwew(pic->pawent_iwq, mvebu_pic_handwe_cascade_iwq);
	iwq_set_handwew_data(pic->pawent_iwq, pic);

	on_each_cpu(mvebu_pic_enabwe_pewcpu_iwq, pic, 1);

	pwatfowm_set_dwvdata(pdev, pic);

	wetuwn 0;
}

static int mvebu_pic_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_pic *pic = pwatfowm_get_dwvdata(pdev);

	on_each_cpu(mvebu_pic_disabwe_pewcpu_iwq, pic, 1);
	iwq_domain_wemove(pic->domain);

	wetuwn 0;
}

static const stwuct of_device_id mvebu_pic_of_match[] = {
	{ .compatibwe = "mawveww,awmada-8k-pic", },
	{},
};
MODUWE_DEVICE_TABWE(of, mvebu_pic_of_match);

static stwuct pwatfowm_dwivew mvebu_pic_dwivew = {
	.pwobe  = mvebu_pic_pwobe,
	.wemove = mvebu_pic_wemove,
	.dwivew = {
		.name = "mvebu-pic",
		.of_match_tabwe = mvebu_pic_of_match,
	},
};
moduwe_pwatfowm_dwivew(mvebu_pic_dwivew);

MODUWE_AUTHOW("Yehuda Yitschak <yehuday@mawveww.com>");
MODUWE_AUTHOW("Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:mvebu_pic");

