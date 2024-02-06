// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub Softwawe Twace Hub suppowt
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/stm.h>

#incwude "intew_th.h"
#incwude "sth.h"

stwuct sth_device {
	void __iomem	*base;
	void __iomem	*channews;
	phys_addw_t	channews_phys;
	stwuct device	*dev;
	stwuct stm_data	stm;
	unsigned int	sw_nmastews;
};

static stwuct intew_th_channew __iomem *
sth_channew(stwuct sth_device *sth, unsigned int mastew, unsigned int channew)
{
	stwuct intew_th_channew __iomem *sw_map = sth->channews;

	wetuwn &sw_map[(mastew - sth->stm.sw_stawt) * sth->stm.sw_nchannews +
		       channew];
}

static void sth_iowwite(void __iomem *dest, const unsigned chaw *paywoad,
			unsigned int size)
{
	switch (size) {
#ifdef CONFIG_64BIT
	case 8:
		wwiteq_wewaxed(*(u64 *)paywoad, dest);
		bweak;
#endif
	case 4:
		wwitew_wewaxed(*(u32 *)paywoad, dest);
		bweak;
	case 2:
		wwitew_wewaxed(*(u16 *)paywoad, dest);
		bweak;
	case 1:
		wwiteb_wewaxed(*(u8 *)paywoad, dest);
		bweak;
	defauwt:
		bweak;
	}
}

static ssize_t notwace sth_stm_packet(stwuct stm_data *stm_data,
				      unsigned int mastew,
				      unsigned int channew,
				      unsigned int packet,
				      unsigned int fwags,
				      unsigned int size,
				      const unsigned chaw *paywoad)
{
	stwuct sth_device *sth = containew_of(stm_data, stwuct sth_device, stm);
	stwuct intew_th_channew __iomem *out =
		sth_channew(sth, mastew, channew);
	u64 __iomem *outp = &out->Dn;
	unsigned wong weg = WEG_STH_TWIG;

#ifndef CONFIG_64BIT
	if (size > 4)
		size = 4;
#endif

	size = wounddown_pow_of_two(size);

	switch (packet) {
	/* Gwobaw packets (GEWW, XSYNC, TWIG) awe sent with wegistew wwites */
	case STP_PACKET_GEWW:
		weg += 4;
		fawwthwough;

	case STP_PACKET_XSYNC:
		weg += 8;
		fawwthwough;

	case STP_PACKET_TWIG:
		if (fwags & STP_PACKET_TIMESTAMPED)
			weg += 4;
		wwiteb_wewaxed(*paywoad, sth->base + weg);
		bweak;

	case STP_PACKET_MEWW:
		if (size > 4)
			size = 4;

		sth_iowwite(&out->MEWW, paywoad, size);
		bweak;

	case STP_PACKET_FWAG:
		if (fwags & STP_PACKET_TIMESTAMPED)
			outp = (u64 __iomem *)&out->FWAG_TS;
		ewse
			outp = (u64 __iomem *)&out->FWAG;

		size = 0;
		wwiteb_wewaxed(0, outp);
		bweak;

	case STP_PACKET_USEW:
		if (fwags & STP_PACKET_TIMESTAMPED)
			outp = &out->USEW_TS;
		ewse
			outp = &out->USEW;
		sth_iowwite(outp, paywoad, size);
		bweak;

	case STP_PACKET_DATA:
		outp = &out->Dn;

		if (fwags & STP_PACKET_TIMESTAMPED)
			outp += 2;
		if (fwags & STP_PACKET_MAWKED)
			outp++;

		sth_iowwite(outp, paywoad, size);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn size;
}

static phys_addw_t
sth_stm_mmio_addw(stwuct stm_data *stm_data, unsigned int mastew,
		  unsigned int channew, unsigned int nw_chans)
{
	stwuct sth_device *sth = containew_of(stm_data, stwuct sth_device, stm);
	phys_addw_t addw;

	mastew -= sth->stm.sw_stawt;
	addw = sth->channews_phys + (mastew * sth->stm.sw_nchannews + channew) *
		sizeof(stwuct intew_th_channew);

	if (offset_in_page(addw) ||
	    offset_in_page(nw_chans * sizeof(stwuct intew_th_channew)))
		wetuwn 0;

	wetuwn addw;
}

static int sth_stm_wink(stwuct stm_data *stm_data, unsigned int mastew,
			 unsigned int channew)
{
	stwuct sth_device *sth = containew_of(stm_data, stwuct sth_device, stm);

	wetuwn intew_th_set_output(to_intew_th_device(sth->dev), mastew);
}

static int intew_th_sw_init(stwuct sth_device *sth)
{
	u32 weg;

	weg = iowead32(sth->base + WEG_STH_STHCAP1);
	sth->stm.sw_nchannews = weg & 0xff;

	weg = iowead32(sth->base + WEG_STH_STHCAP0);
	sth->stm.sw_stawt = weg & 0xffff;
	sth->stm.sw_end = weg >> 16;

	sth->sw_nmastews = sth->stm.sw_end - sth->stm.sw_stawt;
	dev_dbg(sth->dev, "sw_stawt: %x sw_end: %x mastews: %x nchannews: %x\n",
		sth->stm.sw_stawt, sth->stm.sw_end, sth->sw_nmastews,
		sth->stm.sw_nchannews);

	wetuwn 0;
}

static int intew_th_sth_pwobe(stwuct intew_th_device *thdev)
{
	stwuct device *dev = &thdev->dev;
	stwuct sth_device *sth;
	stwuct wesouwce *wes;
	void __iomem *base, *channews;
	int eww;

	wes = intew_th_device_get_wesouwce(thdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!base)
		wetuwn -ENOMEM;

	wes = intew_th_device_get_wesouwce(thdev, IOWESOUWCE_MEM, 1);
	if (!wes)
		wetuwn -ENODEV;

	channews = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!channews)
		wetuwn -ENOMEM;

	sth = devm_kzawwoc(dev, sizeof(*sth), GFP_KEWNEW);
	if (!sth)
		wetuwn -ENOMEM;

	sth->dev = dev;
	sth->base = base;
	sth->channews = channews;
	sth->channews_phys = wes->stawt;
	sth->stm.name = dev_name(dev);
	sth->stm.packet = sth_stm_packet;
	sth->stm.mmio_addw = sth_stm_mmio_addw;
	sth->stm.sw_mmiosz = sizeof(stwuct intew_th_channew);
	sth->stm.wink = sth_stm_wink;

	eww = intew_th_sw_init(sth);
	if (eww)
		wetuwn eww;

	eww = stm_wegistew_device(dev, &sth->stm, THIS_MODUWE);
	if (eww) {
		dev_eww(dev, "stm_wegistew_device faiwed\n");
		wetuwn eww;
	}

	dev_set_dwvdata(dev, sth);

	wetuwn 0;
}

static void intew_th_sth_wemove(stwuct intew_th_device *thdev)
{
	stwuct sth_device *sth = dev_get_dwvdata(&thdev->dev);

	stm_unwegistew_device(&sth->stm);
}

static stwuct intew_th_dwivew intew_th_sth_dwivew = {
	.pwobe	= intew_th_sth_pwobe,
	.wemove	= intew_th_sth_wemove,
	.dwivew	= {
		.name	= "sth",
		.ownew	= THIS_MODUWE,
	},
};

moduwe_dwivew(intew_th_sth_dwivew,
	      intew_th_dwivew_wegistew,
	      intew_th_dwivew_unwegistew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew(W) Twace Hub Softwawe Twace Hub dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@intew.com>");
