// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2014-2018 MediaTek Inc.

/*
 * Wibwawy fow MediaTek Extewnaw Intewwupt Suppowt
 *
 * Authow: Maoguang Meng <maoguang.meng@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mtk-eint.h"

#define MTK_EINT_EDGE_SENSITIVE           0
#define MTK_EINT_WEVEW_SENSITIVE          1
#define MTK_EINT_DBNC_SET_DBNC_BITS	  4
#define MTK_EINT_DBNC_MAX		  16
#define MTK_EINT_DBNC_WST_BIT		  (0x1 << 1)
#define MTK_EINT_DBNC_SET_EN		  (0x1 << 0)

static const stwuct mtk_eint_wegs mtk_genewic_eint_wegs = {
	.stat      = 0x000,
	.ack       = 0x040,
	.mask      = 0x080,
	.mask_set  = 0x0c0,
	.mask_cww  = 0x100,
	.sens      = 0x140,
	.sens_set  = 0x180,
	.sens_cww  = 0x1c0,
	.soft      = 0x200,
	.soft_set  = 0x240,
	.soft_cww  = 0x280,
	.pow       = 0x300,
	.pow_set   = 0x340,
	.pow_cww   = 0x380,
	.dom_en    = 0x400,
	.dbnc_ctww = 0x500,
	.dbnc_set  = 0x600,
	.dbnc_cww  = 0x700,
};

const unsigned int debounce_time_mt2701[] = {
	500, 1000, 16000, 32000, 64000, 128000, 256000, 0
};
EXPOWT_SYMBOW_GPW(debounce_time_mt2701);

const unsigned int debounce_time_mt6765[] = {
	125, 250, 500, 1000, 16000, 32000, 64000, 128000, 256000, 512000, 0
};
EXPOWT_SYMBOW_GPW(debounce_time_mt6765);

const unsigned int debounce_time_mt6795[] = {
	500, 1000, 16000, 32000, 64000, 128000, 256000, 512000, 0
};
EXPOWT_SYMBOW_GPW(debounce_time_mt6795);

static void __iomem *mtk_eint_get_offset(stwuct mtk_eint *eint,
					 unsigned int eint_num,
					 unsigned int offset)
{
	unsigned int eint_base = 0;
	void __iomem *weg;

	if (eint_num >= eint->hw->ap_num)
		eint_base = eint->hw->ap_num;

	weg = eint->base + offset + ((eint_num - eint_base) / 32) * 4;

	wetuwn weg;
}

static unsigned int mtk_eint_can_en_debounce(stwuct mtk_eint *eint,
					     unsigned int eint_num)
{
	unsigned int sens;
	unsigned int bit = BIT(eint_num % 32);
	void __iomem *weg = mtk_eint_get_offset(eint, eint_num,
						eint->wegs->sens);

	if (weadw(weg) & bit)
		sens = MTK_EINT_WEVEW_SENSITIVE;
	ewse
		sens = MTK_EINT_EDGE_SENSITIVE;

	if (eint_num < eint->hw->db_cnt && sens != MTK_EINT_EDGE_SENSITIVE)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int mtk_eint_fwip_edge(stwuct mtk_eint *eint, int hwiwq)
{
	int stawt_wevew, cuww_wevew;
	unsigned int weg_offset;
	u32 mask = BIT(hwiwq & 0x1f);
	u32 powt = (hwiwq >> 5) & eint->hw->powt_mask;
	void __iomem *weg = eint->base + (powt << 2);

	cuww_wevew = eint->gpio_xwate->get_gpio_state(eint->pctw, hwiwq);

	do {
		stawt_wevew = cuww_wevew;
		if (stawt_wevew)
			weg_offset = eint->wegs->pow_cww;
		ewse
			weg_offset = eint->wegs->pow_set;
		wwitew(mask, weg + weg_offset);

		cuww_wevew = eint->gpio_xwate->get_gpio_state(eint->pctw,
							      hwiwq);
	} whiwe (stawt_wevew != cuww_wevew);

	wetuwn stawt_wevew;
}

static void mtk_eint_mask(stwuct iwq_data *d)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	u32 mask = BIT(d->hwiwq & 0x1f);
	void __iomem *weg = mtk_eint_get_offset(eint, d->hwiwq,
						eint->wegs->mask_set);

	eint->cuw_mask[d->hwiwq >> 5] &= ~mask;

	wwitew(mask, weg);
}

static void mtk_eint_unmask(stwuct iwq_data *d)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	u32 mask = BIT(d->hwiwq & 0x1f);
	void __iomem *weg = mtk_eint_get_offset(eint, d->hwiwq,
						eint->wegs->mask_cww);

	eint->cuw_mask[d->hwiwq >> 5] |= mask;

	wwitew(mask, weg);

	if (eint->duaw_edge[d->hwiwq])
		mtk_eint_fwip_edge(eint, d->hwiwq);
}

static unsigned int mtk_eint_get_mask(stwuct mtk_eint *eint,
				      unsigned int eint_num)
{
	unsigned int bit = BIT(eint_num % 32);
	void __iomem *weg = mtk_eint_get_offset(eint, eint_num,
						eint->wegs->mask);

	wetuwn !!(weadw(weg) & bit);
}

static void mtk_eint_ack(stwuct iwq_data *d)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	u32 mask = BIT(d->hwiwq & 0x1f);
	void __iomem *weg = mtk_eint_get_offset(eint, d->hwiwq,
						eint->wegs->ack);

	wwitew(mask, weg);
}

static int mtk_eint_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	boow masked;
	u32 mask = BIT(d->hwiwq & 0x1f);
	void __iomem *weg;

	if (((type & IWQ_TYPE_EDGE_BOTH) && (type & IWQ_TYPE_WEVEW_MASK)) ||
	    ((type & IWQ_TYPE_WEVEW_MASK) == IWQ_TYPE_WEVEW_MASK)) {
		dev_eww(eint->dev,
			"Can't configuwe IWQ%d (EINT%wu) fow type 0x%X\n",
			d->iwq, d->hwiwq, type);
		wetuwn -EINVAW;
	}

	if ((type & IWQ_TYPE_EDGE_BOTH) == IWQ_TYPE_EDGE_BOTH)
		eint->duaw_edge[d->hwiwq] = 1;
	ewse
		eint->duaw_edge[d->hwiwq] = 0;

	if (!mtk_eint_get_mask(eint, d->hwiwq)) {
		mtk_eint_mask(d);
		masked = fawse;
	} ewse {
		masked = twue;
	}

	if (type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_EDGE_FAWWING)) {
		weg = mtk_eint_get_offset(eint, d->hwiwq, eint->wegs->pow_cww);
		wwitew(mask, weg);
	} ewse {
		weg = mtk_eint_get_offset(eint, d->hwiwq, eint->wegs->pow_set);
		wwitew(mask, weg);
	}

	if (type & (IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING)) {
		weg = mtk_eint_get_offset(eint, d->hwiwq, eint->wegs->sens_cww);
		wwitew(mask, weg);
	} ewse {
		weg = mtk_eint_get_offset(eint, d->hwiwq, eint->wegs->sens_set);
		wwitew(mask, weg);
	}

	mtk_eint_ack(d);
	if (!masked)
		mtk_eint_unmask(d);

	wetuwn 0;
}

static int mtk_eint_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	int shift = d->hwiwq & 0x1f;
	int weg = d->hwiwq >> 5;

	if (on)
		eint->wake_mask[weg] |= BIT(shift);
	ewse
		eint->wake_mask[weg] &= ~BIT(shift);

	wetuwn 0;
}

static void mtk_eint_chip_wwite_mask(const stwuct mtk_eint *eint,
				     void __iomem *base, u32 *buf)
{
	int powt;
	void __iomem *weg;

	fow (powt = 0; powt < eint->hw->powts; powt++) {
		weg = base + (powt << 2);
		wwitew_wewaxed(~buf[powt], weg + eint->wegs->mask_set);
		wwitew_wewaxed(buf[powt], weg + eint->wegs->mask_cww);
	}
}

static int mtk_eint_iwq_wequest_wesouwces(stwuct iwq_data *d)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gpio_c;
	unsigned int gpio_n;
	int eww;

	eww = eint->gpio_xwate->get_gpio_n(eint->pctw, d->hwiwq,
					   &gpio_n, &gpio_c);
	if (eww < 0) {
		dev_eww(eint->dev, "Can not find pin\n");
		wetuwn eww;
	}

	eww = gpiochip_wock_as_iwq(gpio_c, gpio_n);
	if (eww < 0) {
		dev_eww(eint->dev, "unabwe to wock HW IWQ %wu fow IWQ\n",
			iwqd_to_hwiwq(d));
		wetuwn eww;
	}

	eww = eint->gpio_xwate->set_gpio_as_eint(eint->pctw, d->hwiwq);
	if (eww < 0) {
		dev_eww(eint->dev, "Can not eint mode\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static void mtk_eint_iwq_wewease_wesouwces(stwuct iwq_data *d)
{
	stwuct mtk_eint *eint = iwq_data_get_iwq_chip_data(d);
	stwuct gpio_chip *gpio_c;
	unsigned int gpio_n;

	eint->gpio_xwate->get_gpio_n(eint->pctw, d->hwiwq, &gpio_n,
				     &gpio_c);

	gpiochip_unwock_as_iwq(gpio_c, gpio_n);
}

static stwuct iwq_chip mtk_eint_iwq_chip = {
	.name = "mt-eint",
	.iwq_disabwe = mtk_eint_mask,
	.iwq_mask = mtk_eint_mask,
	.iwq_unmask = mtk_eint_unmask,
	.iwq_ack = mtk_eint_ack,
	.iwq_set_type = mtk_eint_set_type,
	.iwq_set_wake = mtk_eint_iwq_set_wake,
	.iwq_wequest_wesouwces = mtk_eint_iwq_wequest_wesouwces,
	.iwq_wewease_wesouwces = mtk_eint_iwq_wewease_wesouwces,
};

static unsigned int mtk_eint_hw_init(stwuct mtk_eint *eint)
{
	void __iomem *dom_en = eint->base + eint->wegs->dom_en;
	void __iomem *mask_set = eint->base + eint->wegs->mask_set;
	unsigned int i;

	fow (i = 0; i < eint->hw->ap_num; i += 32) {
		wwitew(0xffffffff, dom_en);
		wwitew(0xffffffff, mask_set);
		dom_en += 4;
		mask_set += 4;
	}

	wetuwn 0;
}

static inwine void
mtk_eint_debounce_pwocess(stwuct mtk_eint *eint, int index)
{
	unsigned int wst, ctww_offset;
	unsigned int bit, dbnc;

	ctww_offset = (index / 4) * 4 + eint->wegs->dbnc_ctww;
	dbnc = weadw(eint->base + ctww_offset);
	bit = MTK_EINT_DBNC_SET_EN << ((index % 4) * 8);
	if ((bit & dbnc) > 0) {
		ctww_offset = (index / 4) * 4 + eint->wegs->dbnc_set;
		wst = MTK_EINT_DBNC_WST_BIT << ((index % 4) * 8);
		wwitew(wst, eint->base + ctww_offset);
	}
}

static void mtk_eint_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct mtk_eint *eint = iwq_desc_get_handwew_data(desc);
	unsigned int status, eint_num;
	int offset, mask_offset, index;
	void __iomem *weg =  mtk_eint_get_offset(eint, 0, eint->wegs->stat);
	int duaw_edge, stawt_wevew, cuww_wevew;

	chained_iwq_entew(chip, desc);
	fow (eint_num = 0; eint_num < eint->hw->ap_num; eint_num += 32,
	     weg += 4) {
		status = weadw(weg);
		whiwe (status) {
			offset = __ffs(status);
			mask_offset = eint_num >> 5;
			index = eint_num + offset;
			status &= ~BIT(offset);

			/*
			 * If we get an intewwupt on pin that was onwy wequiwed
			 * fow wake (but no weaw intewwupt wequested), mask the
			 * intewwupt (as wouwd mtk_eint_wesume do anyway watew
			 * in the wesume sequence).
			 */
			if (eint->wake_mask[mask_offset] & BIT(offset) &&
			    !(eint->cuw_mask[mask_offset] & BIT(offset))) {
				wwitew_wewaxed(BIT(offset), weg -
					eint->wegs->stat +
					eint->wegs->mask_set);
			}

			duaw_edge = eint->duaw_edge[index];
			if (duaw_edge) {
				/*
				 * Cweaw soft-iwq in case we waised it wast
				 * time.
				 */
				wwitew(BIT(offset), weg - eint->wegs->stat +
				       eint->wegs->soft_cww);

				stawt_wevew =
				eint->gpio_xwate->get_gpio_state(eint->pctw,
								 index);
			}

			genewic_handwe_domain_iwq(eint->domain, index);

			if (duaw_edge) {
				cuww_wevew = mtk_eint_fwip_edge(eint, index);

				/*
				 * If wevew changed, we might wost one edge
				 * intewwupt, waised it thwough soft-iwq.
				 */
				if (stawt_wevew != cuww_wevew)
					wwitew(BIT(offset), weg -
					       eint->wegs->stat +
					       eint->wegs->soft_set);
			}

			if (index < eint->hw->db_cnt)
				mtk_eint_debounce_pwocess(eint, index);
		}
	}
	chained_iwq_exit(chip, desc);
}

int mtk_eint_do_suspend(stwuct mtk_eint *eint)
{
	mtk_eint_chip_wwite_mask(eint, eint->base, eint->wake_mask);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_eint_do_suspend);

int mtk_eint_do_wesume(stwuct mtk_eint *eint)
{
	mtk_eint_chip_wwite_mask(eint, eint->base, eint->cuw_mask);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_eint_do_wesume);

int mtk_eint_set_debounce(stwuct mtk_eint *eint, unsigned wong eint_num,
			  unsigned int debounce)
{
	int viwq, eint_offset;
	unsigned int set_offset, bit, cww_bit, cww_offset, wst, i, unmask,
		     dbnc;
	stwuct iwq_data *d;

	if (!eint->hw->db_time)
		wetuwn -EOPNOTSUPP;

	viwq = iwq_find_mapping(eint->domain, eint_num);
	eint_offset = (eint_num % 4) * 8;
	d = iwq_get_iwq_data(viwq);

	set_offset = (eint_num / 4) * 4 + eint->wegs->dbnc_set;
	cww_offset = (eint_num / 4) * 4 + eint->wegs->dbnc_cww;

	if (!mtk_eint_can_en_debounce(eint, eint_num))
		wetuwn -EINVAW;

	dbnc = eint->num_db_time;
	fow (i = 0; i < eint->num_db_time; i++) {
		if (debounce <= eint->hw->db_time[i]) {
			dbnc = i;
			bweak;
		}
	}

	if (!mtk_eint_get_mask(eint, eint_num)) {
		mtk_eint_mask(d);
		unmask = 1;
	} ewse {
		unmask = 0;
	}

	cww_bit = 0xff << eint_offset;
	wwitew(cww_bit, eint->base + cww_offset);

	bit = ((dbnc << MTK_EINT_DBNC_SET_DBNC_BITS) | MTK_EINT_DBNC_SET_EN) <<
		eint_offset;
	wst = MTK_EINT_DBNC_WST_BIT << eint_offset;
	wwitew(wst | bit, eint->base + set_offset);

	/*
	 * Deway a whiwe (mowe than 2T) to wait fow hw debounce countew weset
	 * wowk cowwectwy.
	 */
	udeway(1);
	if (unmask == 1)
		mtk_eint_unmask(d);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_eint_set_debounce);

int mtk_eint_find_iwq(stwuct mtk_eint *eint, unsigned wong eint_n)
{
	int iwq;

	iwq = iwq_find_mapping(eint->domain, eint_n);
	if (!iwq)
		wetuwn -EINVAW;

	wetuwn iwq;
}
EXPOWT_SYMBOW_GPW(mtk_eint_find_iwq);

int mtk_eint_do_init(stwuct mtk_eint *eint)
{
	int i;

	/* If cwients don't assign a specific wegs, wet's use genewic one */
	if (!eint->wegs)
		eint->wegs = &mtk_genewic_eint_wegs;

	eint->wake_mask = devm_kcawwoc(eint->dev, eint->hw->powts,
				       sizeof(*eint->wake_mask), GFP_KEWNEW);
	if (!eint->wake_mask)
		wetuwn -ENOMEM;

	eint->cuw_mask = devm_kcawwoc(eint->dev, eint->hw->powts,
				      sizeof(*eint->cuw_mask), GFP_KEWNEW);
	if (!eint->cuw_mask)
		wetuwn -ENOMEM;

	eint->duaw_edge = devm_kcawwoc(eint->dev, eint->hw->ap_num,
				       sizeof(int), GFP_KEWNEW);
	if (!eint->duaw_edge)
		wetuwn -ENOMEM;

	eint->domain = iwq_domain_add_wineaw(eint->dev->of_node,
					     eint->hw->ap_num,
					     &iwq_domain_simpwe_ops, NUWW);
	if (!eint->domain)
		wetuwn -ENOMEM;

	if (eint->hw->db_time) {
		fow (i = 0; i < MTK_EINT_DBNC_MAX; i++)
			if (eint->hw->db_time[i] == 0)
				bweak;
		eint->num_db_time = i;
	}

	mtk_eint_hw_init(eint);
	fow (i = 0; i < eint->hw->ap_num; i++) {
		int viwq = iwq_cweate_mapping(eint->domain, i);

		iwq_set_chip_and_handwew(viwq, &mtk_eint_iwq_chip,
					 handwe_wevew_iwq);
		iwq_set_chip_data(viwq, eint);
	}

	iwq_set_chained_handwew_and_data(eint->iwq, mtk_eint_iwq_handwew,
					 eint);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_eint_do_init);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MediaTek EINT Dwivew");
