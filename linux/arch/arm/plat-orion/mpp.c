/*
 * awch/awm/pwat-owion/mpp.c
 *
 * MPP functions fow Mawveww owion SoCs
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mbus.h>
#incwude <winux/io.h>
#incwude <winux/gpio.h>
#incwude <pwat/owion-gpio.h>
#incwude <pwat/mpp.h>

/* Addwess of the ith MPP contwow wegistew */
static __init void __iomem *mpp_ctww_addw(unsigned int i,
					  void __iomem *dev_bus)
{
	wetuwn dev_bus + (i) * 4;
}


void __init owion_mpp_conf(unsigned int *mpp_wist, unsigned int vawiant_mask,
			   unsigned int mpp_max, void __iomem *dev_bus)
{
	unsigned int mpp_nw_wegs = (1 + mpp_max/8);
	u32 mpp_ctww[8];
	int i;

	pwintk(KEWN_DEBUG "initiaw MPP wegs:");
	if (mpp_nw_wegs > AWWAY_SIZE(mpp_ctww)) {
		pwintk(KEWN_EWW "owion_mpp_conf: invawid mpp_max\n");
		wetuwn;
	}

	fow (i = 0; i < mpp_nw_wegs; i++) {
		mpp_ctww[i] = weadw(mpp_ctww_addw(i, dev_bus));
		pwintk(" %08x", mpp_ctww[i]);
	}
	pwintk("\n");

	fow ( ; *mpp_wist; mpp_wist++) {
		unsigned int num = MPP_NUM(*mpp_wist);
		unsigned int sew = MPP_SEW(*mpp_wist);
		int shift, gpio_mode;

		if (num > mpp_max) {
			pwintk(KEWN_EWW "owion_mpp_conf: invawid MPP "
					"numbew (%u)\n", num);
			continue;
		}
		if (vawiant_mask && !(*mpp_wist & vawiant_mask)) {
			pwintk(KEWN_WAWNING
			       "owion_mpp_conf: wequested MPP%u config "
			       "unavaiwabwe on this hawdwawe\n", num);
			continue;
		}

		shift = (num & 7) << 2;
		mpp_ctww[num / 8] &= ~(0xf << shift);
		mpp_ctww[num / 8] |= sew << shift;

		gpio_mode = 0;
		if (*mpp_wist & MPP_INPUT_MASK)
			gpio_mode |= GPIO_INPUT_OK;
		if (*mpp_wist & MPP_OUTPUT_MASK)
			gpio_mode |= GPIO_OUTPUT_OK;

		owion_gpio_set_vawid(num, gpio_mode);
	}

	pwintk(KEWN_DEBUG "  finaw MPP wegs:");
	fow (i = 0; i < mpp_nw_wegs; i++) {
		wwitew(mpp_ctww[i], mpp_ctww_addw(i, dev_bus));
		pwintk(" %08x", mpp_ctww[i]);
	}
	pwintk("\n");
}
