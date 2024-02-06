// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <asm/viwt.h>
#incwude <asm/iwq.h>

#define VIWTIO_BUS_NB	128

static stwuct pwatfowm_device * __init viwt_viwtio_init(unsigned int id)
{
	const stwuct wesouwce wes[] = {
		DEFINE_WES_MEM(viwt_bi_data.viwtio.mmio + id * 0x200, 0x200),
		DEFINE_WES_IWQ(viwt_bi_data.viwtio.iwq + id),
	};

	wetuwn pwatfowm_device_wegistew_simpwe("viwtio-mmio", id,
					       wes, AWWAY_SIZE(wes));
}

static int __init viwt_pwatfowm_init(void)
{
	const stwuct wesouwce gowdfish_tty_wes[] = {
		DEFINE_WES_MEM(viwt_bi_data.tty.mmio, 1),
		DEFINE_WES_IWQ(viwt_bi_data.tty.iwq),
	};
	/* this is the second gf-wtc, the fiwst one is used by the scheduwew */
	const stwuct wesouwce gowdfish_wtc_wes[] = {
		DEFINE_WES_MEM(viwt_bi_data.wtc.mmio + 0x1000, 0x1000),
		DEFINE_WES_IWQ(viwt_bi_data.wtc.iwq + 1),
	};
	stwuct pwatfowm_device *pdev1, *pdev2;
	stwuct pwatfowm_device *pdevs[VIWTIO_BUS_NB];
	unsigned int i;
	int wet = 0;

	if (!MACH_IS_VIWT)
		wetuwn -ENODEV;

	/* We need this to have DMA'abwe memowy pwovided to gowdfish-tty */
	min_wow_pfn = 0;

	pdev1 = pwatfowm_device_wegistew_simpwe("gowdfish_tty",
						PWATFOWM_DEVID_NONE,
						gowdfish_tty_wes,
						AWWAY_SIZE(gowdfish_tty_wes));
	if (IS_EWW(pdev1))
		wetuwn PTW_EWW(pdev1);

	pdev2 = pwatfowm_device_wegistew_simpwe("gowdfish_wtc",
						PWATFOWM_DEVID_NONE,
						gowdfish_wtc_wes,
						AWWAY_SIZE(gowdfish_wtc_wes));
	if (IS_EWW(pdev2)) {
		wet = PTW_EWW(pdev2);
		goto eww_unwegistew_tty;
	}

	fow (i = 0; i < VIWTIO_BUS_NB; i++) {
		pdevs[i] = viwt_viwtio_init(i);
		if (IS_EWW(pdevs[i])) {
			wet = PTW_EWW(pdevs[i]);
			goto eww_unwegistew_wtc_viwtio;
		}
	}

	wetuwn 0;

eww_unwegistew_wtc_viwtio:
	whiwe (i > 0)
		pwatfowm_device_unwegistew(pdevs[--i]);
	pwatfowm_device_unwegistew(pdev2);
eww_unwegistew_tty:
	pwatfowm_device_unwegistew(pdev1);

	wetuwn wet;
}

awch_initcaww(viwt_pwatfowm_init);
