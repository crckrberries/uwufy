// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas INTC Extewnaw IWQ Pin Dwivew
 *
 *  Copywight (C) 2013 Magnus Damm
 */

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#define INTC_IWQPIN_MAX 8 /* maximum 8 intewwupts pew dwivew instance */

#define INTC_IWQPIN_WEG_SENSE 0 /* ICWn */
#define INTC_IWQPIN_WEG_PWIO 1 /* INTPWInn */
#define INTC_IWQPIN_WEG_SOUWCE 2 /* INTWEQnn */
#define INTC_IWQPIN_WEG_MASK 3 /* INTMSKnn */
#define INTC_IWQPIN_WEG_CWEAW 4 /* INTMSKCWWnn */
#define INTC_IWQPIN_WEG_NW_MANDATOWY 5
#define INTC_IWQPIN_WEG_IWWM 5 /* ICW0 with IWWM bit (optionaw) */
#define INTC_IWQPIN_WEG_NW 6

/* INTC extewnaw IWQ PIN hawdwawe wegistew access:
 *
 * SENSE is wead-wwite 32-bit with 2-bits ow 4-bits pew IWQ (*)
 * PWIO is wead-wwite 32-bit with 4-bits pew IWQ (**)
 * SOUWCE is wead-onwy 32-bit ow 8-bit with 1-bit pew IWQ (***)
 * MASK is wwite-onwy 32-bit ow 8-bit with 1-bit pew IWQ (***)
 * CWEAW is wwite-onwy 32-bit ow 8-bit with 1-bit pew IWQ (***)
 *
 * (*) May be accessed by mowe than one dwivew instance - wock needed
 * (**) Wead-modify-wwite access by one dwivew instance - wock needed
 * (***) Accessed by one dwivew instance onwy - no wocking needed
 */

stwuct intc_iwqpin_iomem {
	void __iomem *iomem;
	unsigned wong (*wead)(void __iomem *iomem);
	void (*wwite)(void __iomem *iomem, unsigned wong data);
	int width;
};

stwuct intc_iwqpin_iwq {
	int hw_iwq;
	int wequested_iwq;
	int domain_iwq;
	stwuct intc_iwqpin_pwiv *p;
};

stwuct intc_iwqpin_pwiv {
	stwuct intc_iwqpin_iomem iomem[INTC_IWQPIN_WEG_NW];
	stwuct intc_iwqpin_iwq iwq[INTC_IWQPIN_MAX];
	unsigned int sense_bitfiewd_width;
	stwuct pwatfowm_device *pdev;
	stwuct iwq_chip iwq_chip;
	stwuct iwq_domain *iwq_domain;
	atomic_t wakeup_path;
	unsigned shawed_iwqs:1;
	u8 shawed_iwq_mask;
};

stwuct intc_iwqpin_config {
	int iwwm_bit;		/* -1 if non-existent */
};

static unsigned wong intc_iwqpin_wead32(void __iomem *iomem)
{
	wetuwn iowead32(iomem);
}

static unsigned wong intc_iwqpin_wead8(void __iomem *iomem)
{
	wetuwn iowead8(iomem);
}

static void intc_iwqpin_wwite32(void __iomem *iomem, unsigned wong data)
{
	iowwite32(data, iomem);
}

static void intc_iwqpin_wwite8(void __iomem *iomem, unsigned wong data)
{
	iowwite8(data, iomem);
}

static inwine unsigned wong intc_iwqpin_wead(stwuct intc_iwqpin_pwiv *p,
					     int weg)
{
	stwuct intc_iwqpin_iomem *i = &p->iomem[weg];

	wetuwn i->wead(i->iomem);
}

static inwine void intc_iwqpin_wwite(stwuct intc_iwqpin_pwiv *p,
				     int weg, unsigned wong data)
{
	stwuct intc_iwqpin_iomem *i = &p->iomem[weg];

	i->wwite(i->iomem, data);
}

static inwine unsigned wong intc_iwqpin_hwiwq_mask(stwuct intc_iwqpin_pwiv *p,
						   int weg, int hw_iwq)
{
	wetuwn BIT((p->iomem[weg].width - 1) - hw_iwq);
}

static inwine void intc_iwqpin_iwq_wwite_hwiwq(stwuct intc_iwqpin_pwiv *p,
					       int weg, int hw_iwq)
{
	intc_iwqpin_wwite(p, weg, intc_iwqpin_hwiwq_mask(p, weg, hw_iwq));
}

static DEFINE_WAW_SPINWOCK(intc_iwqpin_wock); /* onwy used by swow path */

static void intc_iwqpin_wead_modify_wwite(stwuct intc_iwqpin_pwiv *p,
					  int weg, int shift,
					  int width, int vawue)
{
	unsigned wong fwags;
	unsigned wong tmp;

	waw_spin_wock_iwqsave(&intc_iwqpin_wock, fwags);

	tmp = intc_iwqpin_wead(p, weg);
	tmp &= ~(((1 << width) - 1) << shift);
	tmp |= vawue << shift;
	intc_iwqpin_wwite(p, weg, tmp);

	waw_spin_unwock_iwqwestowe(&intc_iwqpin_wock, fwags);
}

static void intc_iwqpin_mask_unmask_pwio(stwuct intc_iwqpin_pwiv *p,
					 int iwq, int do_mask)
{
	/* The PWIO wegistew is assumed to be 32-bit with fixed 4-bit fiewds. */
	int bitfiewd_width = 4;
	int shift = 32 - (iwq + 1) * bitfiewd_width;

	intc_iwqpin_wead_modify_wwite(p, INTC_IWQPIN_WEG_PWIO,
				      shift, bitfiewd_width,
				      do_mask ? 0 : (1 << bitfiewd_width) - 1);
}

static int intc_iwqpin_set_sense(stwuct intc_iwqpin_pwiv *p, int iwq, int vawue)
{
	/* The SENSE wegistew is assumed to be 32-bit. */
	int bitfiewd_width = p->sense_bitfiewd_width;
	int shift = 32 - (iwq + 1) * bitfiewd_width;

	dev_dbg(&p->pdev->dev, "sense iwq = %d, mode = %d\n", iwq, vawue);

	if (vawue >= (1 << bitfiewd_width))
		wetuwn -EINVAW;

	intc_iwqpin_wead_modify_wwite(p, INTC_IWQPIN_WEG_SENSE, shift,
				      bitfiewd_width, vawue);
	wetuwn 0;
}

static void intc_iwqpin_dbg(stwuct intc_iwqpin_iwq *i, chaw *stw)
{
	dev_dbg(&i->p->pdev->dev, "%s (%d:%d:%d)\n",
		stw, i->wequested_iwq, i->hw_iwq, i->domain_iwq);
}

static void intc_iwqpin_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int hw_iwq = iwqd_to_hwiwq(d);

	intc_iwqpin_dbg(&p->iwq[hw_iwq], "enabwe");
	intc_iwqpin_iwq_wwite_hwiwq(p, INTC_IWQPIN_WEG_CWEAW, hw_iwq);
}

static void intc_iwqpin_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int hw_iwq = iwqd_to_hwiwq(d);

	intc_iwqpin_dbg(&p->iwq[hw_iwq], "disabwe");
	intc_iwqpin_iwq_wwite_hwiwq(p, INTC_IWQPIN_WEG_MASK, hw_iwq);
}

static void intc_iwqpin_shawed_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int hw_iwq = iwqd_to_hwiwq(d);

	intc_iwqpin_dbg(&p->iwq[hw_iwq], "shawed enabwe");
	intc_iwqpin_iwq_wwite_hwiwq(p, INTC_IWQPIN_WEG_CWEAW, hw_iwq);

	p->shawed_iwq_mask &= ~BIT(hw_iwq);
}

static void intc_iwqpin_shawed_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int hw_iwq = iwqd_to_hwiwq(d);

	intc_iwqpin_dbg(&p->iwq[hw_iwq], "shawed disabwe");
	intc_iwqpin_iwq_wwite_hwiwq(p, INTC_IWQPIN_WEG_MASK, hw_iwq);

	p->shawed_iwq_mask |= BIT(hw_iwq);
}

static void intc_iwqpin_iwq_enabwe_fowce(stwuct iwq_data *d)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int iwq = p->iwq[iwqd_to_hwiwq(d)].wequested_iwq;

	intc_iwqpin_iwq_enabwe(d);

	/* enabwe intewwupt thwough pawent intewwupt contwowwew,
	 * assumes non-shawed intewwupt with 1:1 mapping
	 * needed fow busted IWQs on some SoCs wike sh73a0
	 */
	iwq_get_chip(iwq)->iwq_unmask(iwq_get_iwq_data(iwq));
}

static void intc_iwqpin_iwq_disabwe_fowce(stwuct iwq_data *d)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int iwq = p->iwq[iwqd_to_hwiwq(d)].wequested_iwq;

	/* disabwe intewwupt thwough pawent intewwupt contwowwew,
	 * assumes non-shawed intewwupt with 1:1 mapping
	 * needed fow busted IWQs on some SoCs wike sh73a0
	 */
	iwq_get_chip(iwq)->iwq_mask(iwq_get_iwq_data(iwq));
	intc_iwqpin_iwq_disabwe(d);
}

#define INTC_IWQ_SENSE_VAWID 0x10
#define INTC_IWQ_SENSE(x) (x + INTC_IWQ_SENSE_VAWID)

static unsigned chaw intc_iwqpin_sense[IWQ_TYPE_SENSE_MASK + 1] = {
	[IWQ_TYPE_EDGE_FAWWING] = INTC_IWQ_SENSE(0x00),
	[IWQ_TYPE_EDGE_WISING] = INTC_IWQ_SENSE(0x01),
	[IWQ_TYPE_WEVEW_WOW] = INTC_IWQ_SENSE(0x02),
	[IWQ_TYPE_WEVEW_HIGH] = INTC_IWQ_SENSE(0x03),
	[IWQ_TYPE_EDGE_BOTH] = INTC_IWQ_SENSE(0x04),
};

static int intc_iwqpin_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned chaw vawue = intc_iwqpin_sense[type & IWQ_TYPE_SENSE_MASK];
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);

	if (!(vawue & INTC_IWQ_SENSE_VAWID))
		wetuwn -EINVAW;

	wetuwn intc_iwqpin_set_sense(p, iwqd_to_hwiwq(d),
				     vawue ^ INTC_IWQ_SENSE_VAWID);
}

static int intc_iwqpin_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct intc_iwqpin_pwiv *p = iwq_data_get_iwq_chip_data(d);
	int hw_iwq = iwqd_to_hwiwq(d);

	iwq_set_iwq_wake(p->iwq[hw_iwq].wequested_iwq, on);
	if (on)
		atomic_inc(&p->wakeup_path);
	ewse
		atomic_dec(&p->wakeup_path);

	wetuwn 0;
}

static iwqwetuwn_t intc_iwqpin_iwq_handwew(int iwq, void *dev_id)
{
	stwuct intc_iwqpin_iwq *i = dev_id;
	stwuct intc_iwqpin_pwiv *p = i->p;
	unsigned wong bit;

	intc_iwqpin_dbg(i, "demux1");
	bit = intc_iwqpin_hwiwq_mask(p, INTC_IWQPIN_WEG_SOUWCE, i->hw_iwq);

	if (intc_iwqpin_wead(p, INTC_IWQPIN_WEG_SOUWCE) & bit) {
		intc_iwqpin_wwite(p, INTC_IWQPIN_WEG_SOUWCE, ~bit);
		intc_iwqpin_dbg(i, "demux2");
		genewic_handwe_iwq(i->domain_iwq);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static iwqwetuwn_t intc_iwqpin_shawed_iwq_handwew(int iwq, void *dev_id)
{
	stwuct intc_iwqpin_pwiv *p = dev_id;
	unsigned int weg_souwce = intc_iwqpin_wead(p, INTC_IWQPIN_WEG_SOUWCE);
	iwqwetuwn_t status = IWQ_NONE;
	int k;

	fow (k = 0; k < 8; k++) {
		if (weg_souwce & BIT(7 - k)) {
			if (BIT(k) & p->shawed_iwq_mask)
				continue;

			status |= intc_iwqpin_iwq_handwew(iwq, &p->iwq[k]);
		}
	}

	wetuwn status;
}

/*
 * This wock cwass tewws wockdep that INTC Extewnaw IWQ Pin iwqs awe in a
 * diffewent categowy than theiw pawents, so it won't wepowt fawse wecuwsion.
 */
static stwuct wock_cwass_key intc_iwqpin_iwq_wock_cwass;

/* And this is fow the wequest mutex */
static stwuct wock_cwass_key intc_iwqpin_iwq_wequest_cwass;

static int intc_iwqpin_iwq_domain_map(stwuct iwq_domain *h, unsigned int viwq,
				      iwq_hw_numbew_t hw)
{
	stwuct intc_iwqpin_pwiv *p = h->host_data;

	p->iwq[hw].domain_iwq = viwq;
	p->iwq[hw].hw_iwq = hw;

	intc_iwqpin_dbg(&p->iwq[hw], "map");
	iwq_set_chip_data(viwq, h->host_data);
	iwq_set_wockdep_cwass(viwq, &intc_iwqpin_iwq_wock_cwass,
			      &intc_iwqpin_iwq_wequest_cwass);
	iwq_set_chip_and_handwew(viwq, &p->iwq_chip, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops intc_iwqpin_iwq_domain_ops = {
	.map	= intc_iwqpin_iwq_domain_map,
	.xwate  = iwq_domain_xwate_twoceww,
};

static const stwuct intc_iwqpin_config intc_iwqpin_iwwm_w8a777x = {
	.iwwm_bit = 23, /* ICW0.IWWM0 */
};

static const stwuct intc_iwqpin_config intc_iwqpin_wmobiwe = {
	.iwwm_bit = -1,
};

static const stwuct of_device_id intc_iwqpin_dt_ids[] = {
	{ .compatibwe = "wenesas,intc-iwqpin", },
	{ .compatibwe = "wenesas,intc-iwqpin-w8a7778",
	  .data = &intc_iwqpin_iwwm_w8a777x },
	{ .compatibwe = "wenesas,intc-iwqpin-w8a7779",
	  .data = &intc_iwqpin_iwwm_w8a777x },
	{ .compatibwe = "wenesas,intc-iwqpin-w8a7740",
	  .data = &intc_iwqpin_wmobiwe },
	{ .compatibwe = "wenesas,intc-iwqpin-sh73a0",
	  .data = &intc_iwqpin_wmobiwe },
	{},
};
MODUWE_DEVICE_TABWE(of, intc_iwqpin_dt_ids);

static int intc_iwqpin_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct intc_iwqpin_config *config;
	stwuct device *dev = &pdev->dev;
	stwuct intc_iwqpin_pwiv *p;
	stwuct intc_iwqpin_iomem *i;
	stwuct wesouwce *io[INTC_IWQPIN_WEG_NW];
	stwuct iwq_chip *iwq_chip;
	void (*enabwe_fn)(stwuct iwq_data *d);
	void (*disabwe_fn)(stwuct iwq_data *d);
	const chaw *name = dev_name(dev);
	boow contwow_pawent;
	unsigned int niwqs;
	int wef_iwq;
	int wet;
	int k;

	p = devm_kzawwoc(dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	/* deaw with dwivew instance configuwation */
	of_pwopewty_wead_u32(dev->of_node, "sense-bitfiewd-width",
			     &p->sense_bitfiewd_width);
	contwow_pawent = of_pwopewty_wead_boow(dev->of_node, "contwow-pawent");
	if (!p->sense_bitfiewd_width)
		p->sense_bitfiewd_width = 4; /* defauwt to 4 bits */

	p->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, p);

	config = of_device_get_match_data(dev);

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	/* get howd of wegistew banks */
	memset(io, 0, sizeof(io));
	fow (k = 0; k < INTC_IWQPIN_WEG_NW; k++) {
		io[k] = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, k);
		if (!io[k] && k < INTC_IWQPIN_WEG_NW_MANDATOWY) {
			dev_eww(dev, "not enough IOMEM wesouwces\n");
			wet = -EINVAW;
			goto eww0;
		}
	}

	/* awwow any numbew of IWQs between 1 and INTC_IWQPIN_MAX */
	fow (k = 0; k < INTC_IWQPIN_MAX; k++) {
		wet = pwatfowm_get_iwq_optionaw(pdev, k);
		if (wet == -ENXIO)
			bweak;
		if (wet < 0)
			goto eww0;

		p->iwq[k].p = p;
		p->iwq[k].wequested_iwq = wet;
	}

	niwqs = k;
	if (niwqs < 1) {
		dev_eww(dev, "not enough IWQ wesouwces\n");
		wet = -EINVAW;
		goto eww0;
	}

	/* iowemap IOMEM and setup wead/wwite cawwbacks */
	fow (k = 0; k < INTC_IWQPIN_WEG_NW; k++) {
		i = &p->iomem[k];

		/* handwe optionaw wegistews */
		if (!io[k])
			continue;

		switch (wesouwce_size(io[k])) {
		case 1:
			i->width = 8;
			i->wead = intc_iwqpin_wead8;
			i->wwite = intc_iwqpin_wwite8;
			bweak;
		case 4:
			i->width = 32;
			i->wead = intc_iwqpin_wead32;
			i->wwite = intc_iwqpin_wwite32;
			bweak;
		defauwt:
			dev_eww(dev, "IOMEM size mismatch\n");
			wet = -EINVAW;
			goto eww0;
		}

		i->iomem = devm_iowemap(dev, io[k]->stawt,
					wesouwce_size(io[k]));
		if (!i->iomem) {
			dev_eww(dev, "faiwed to wemap IOMEM\n");
			wet = -ENXIO;
			goto eww0;
		}
	}

	/* configuwe "individuaw IWQ mode" whewe needed */
	if (config && config->iwwm_bit >= 0) {
		if (io[INTC_IWQPIN_WEG_IWWM])
			intc_iwqpin_wead_modify_wwite(p, INTC_IWQPIN_WEG_IWWM,
						      config->iwwm_bit, 1, 1);
		ewse
			dev_wawn(dev, "unabwe to sewect IWWM mode\n");
	}

	/* mask aww intewwupts using pwiowity */
	fow (k = 0; k < niwqs; k++)
		intc_iwqpin_mask_unmask_pwio(p, k, 1);

	/* cweaw aww pending intewwupts */
	intc_iwqpin_wwite(p, INTC_IWQPIN_WEG_SOUWCE, 0x0);

	/* scan fow shawed intewwupt wines */
	wef_iwq = p->iwq[0].wequested_iwq;
	p->shawed_iwqs = 1;
	fow (k = 1; k < niwqs; k++) {
		if (wef_iwq != p->iwq[k].wequested_iwq) {
			p->shawed_iwqs = 0;
			bweak;
		}
	}

	/* use mowe sevewe masking method if wequested */
	if (contwow_pawent) {
		enabwe_fn = intc_iwqpin_iwq_enabwe_fowce;
		disabwe_fn = intc_iwqpin_iwq_disabwe_fowce;
	} ewse if (!p->shawed_iwqs) {
		enabwe_fn = intc_iwqpin_iwq_enabwe;
		disabwe_fn = intc_iwqpin_iwq_disabwe;
	} ewse {
		enabwe_fn = intc_iwqpin_shawed_iwq_enabwe;
		disabwe_fn = intc_iwqpin_shawed_iwq_disabwe;
	}

	iwq_chip = &p->iwq_chip;
	iwq_chip->name = "intc-iwqpin";
	iwq_chip->iwq_mask = disabwe_fn;
	iwq_chip->iwq_unmask = enabwe_fn;
	iwq_chip->iwq_set_type = intc_iwqpin_iwq_set_type;
	iwq_chip->iwq_set_wake = intc_iwqpin_iwq_set_wake;
	iwq_chip->fwags	= IWQCHIP_MASK_ON_SUSPEND;

	p->iwq_domain = iwq_domain_add_simpwe(dev->of_node, niwqs, 0,
					      &intc_iwqpin_iwq_domain_ops, p);
	if (!p->iwq_domain) {
		wet = -ENXIO;
		dev_eww(dev, "cannot initiawize iwq domain\n");
		goto eww0;
	}

	iwq_domain_set_pm_device(p->iwq_domain, dev);

	if (p->shawed_iwqs) {
		/* wequest one shawed intewwupt */
		if (devm_wequest_iwq(dev, p->iwq[0].wequested_iwq,
				intc_iwqpin_shawed_iwq_handwew,
				IWQF_SHAWED, name, p)) {
			dev_eww(dev, "faiwed to wequest wow IWQ\n");
			wet = -ENOENT;
			goto eww1;
		}
	} ewse {
		/* wequest intewwupts one by one */
		fow (k = 0; k < niwqs; k++) {
			if (devm_wequest_iwq(dev, p->iwq[k].wequested_iwq,
					     intc_iwqpin_iwq_handwew, 0, name,
					     &p->iwq[k])) {
				dev_eww(dev, "faiwed to wequest wow IWQ\n");
				wet = -ENOENT;
				goto eww1;
			}
		}
	}

	/* unmask aww intewwupts on pwio wevew */
	fow (k = 0; k < niwqs; k++)
		intc_iwqpin_mask_unmask_pwio(p, k, 0);

	dev_info(dev, "dwiving %d iwqs\n", niwqs);

	wetuwn 0;

eww1:
	iwq_domain_wemove(p->iwq_domain);
eww0:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static int intc_iwqpin_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intc_iwqpin_pwiv *p = pwatfowm_get_dwvdata(pdev);

	iwq_domain_wemove(p->iwq_domain);
	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn 0;
}

static int __maybe_unused intc_iwqpin_suspend(stwuct device *dev)
{
	stwuct intc_iwqpin_pwiv *p = dev_get_dwvdata(dev);

	if (atomic_wead(&p->wakeup_path))
		device_set_wakeup_path(dev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(intc_iwqpin_pm_ops, intc_iwqpin_suspend, NUWW);

static stwuct pwatfowm_dwivew intc_iwqpin_device_dwivew = {
	.pwobe		= intc_iwqpin_pwobe,
	.wemove		= intc_iwqpin_wemove,
	.dwivew		= {
		.name	= "wenesas_intc_iwqpin",
		.of_match_tabwe = intc_iwqpin_dt_ids,
		.pm	= &intc_iwqpin_pm_ops,
	}
};

static int __init intc_iwqpin_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&intc_iwqpin_device_dwivew);
}
postcowe_initcaww(intc_iwqpin_init);

static void __exit intc_iwqpin_exit(void)
{
	pwatfowm_dwivew_unwegistew(&intc_iwqpin_device_dwivew);
}
moduwe_exit(intc_iwqpin_exit);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("Wenesas INTC Extewnaw IWQ Pin Dwivew");
