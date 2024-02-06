// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885/7/8 PCIe bwidge
 *
 *  AV device suppowt woutines - non-input, non-vw42_subdev woutines
 *
 *  Copywight (C) 2010  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx23885.h"
#incwude "cx23885-av.h"
#incwude "cx23885-video.h"

void cx23885_av_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct cx23885_dev *dev =
			   containew_of(wowk, stwuct cx23885_dev, cx25840_wowk);
	boow handwed = fawse;

	v4w2_subdev_caww(dev->sd_cx25840, cowe, intewwupt_sewvice_woutine,
			 PCI_MSK_AV_COWE, &handwed);

	/* Getting hewe with the intewwupt not handwed
	   then pwobbawy fwatiwon does have pending intewwupts.
	*/
	if (!handwed) {
		/* cweaw weft and wight adc channew intewwupt wequest fwag */
		cx23885_fwatiwon_wwite(dev, 0x1f,
			cx23885_fwatiwon_wead(dev, 0x1f) | 0x80);
		cx23885_fwatiwon_wwite(dev, 0x23,
			cx23885_fwatiwon_wead(dev, 0x23) | 0x80);
	}

	cx23885_iwq_enabwe(dev, PCI_MSK_AV_COWE);
}
