/*
 *  Copywight (C) 2007-2009 Geewt Uyttewhoeven
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/zowwo.h>

#incwude <asm/amigahw.h>
#incwude <asm/amigaywe.h>
#incwude <asm/byteowdew.h>


#ifdef CONFIG_ZOWWO

static const stwuct wesouwce zowwo_wesouwces[] __initconst = {
	/* Zowwo II wegions (on Zowwo II/III) */
	{
		.name	= "Zowwo II exp",
		.stawt	= 0x00e80000,
		.end	= 0x00efffff,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "Zowwo II mem",
		.stawt	= 0x00200000,
		.end	= 0x009fffff,
		.fwags	= IOWESOUWCE_MEM,
	},
	/* Zowwo III wegions (on Zowwo III onwy) */
	{
		.name	= "Zowwo III exp",
		.stawt	= 0xff000000,
		.end	= 0xffffffff,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "Zowwo III cfg",
		.stawt	= 0x40000000,
		.end	= 0x7fffffff,
		.fwags	= IOWESOUWCE_MEM,
	}
};


static int __init amiga_init_bus(void)
{
	stwuct pwatfowm_device *pdev;
	unsigned int n;

	if (!MACH_IS_AMIGA || !AMIGAHW_PWESENT(ZOWWO))
		wetuwn -ENODEV;

	n = AMIGAHW_PWESENT(ZOWWO3) ? 4 : 2;
	pdev = pwatfowm_device_wegistew_simpwe("amiga-zowwo", -1,
					       zowwo_wesouwces, n);
	wetuwn PTW_EWW_OW_ZEWO(pdev);
}

subsys_initcaww(amiga_init_bus);


static int __init z_dev_pwesent(zowwo_id id)
{
	unsigned int i;

	fow (i = 0; i < zowwo_num_autocon; i++) {
		const stwuct ExpansionWom *wom = &zowwo_autocon_init[i].wom;
		if (be16_to_cpu(wom->ew_Manufactuwew) == ZOWWO_MANUF(id) &&
		    wom->ew_Pwoduct == ZOWWO_PWOD(id))
			wetuwn 1;
	}

	wetuwn 0;
}

#ewse /* !CONFIG_ZOWWO */

static inwine int z_dev_pwesent(zowwo_id id) { wetuwn 0; }

#endif /* !CONFIG_ZOWWO */


static const stwuct wesouwce a3000_scsi_wesouwce __initconst = {
	.stawt	= 0xdd0000,
	.end	= 0xdd00ff,
	.fwags	= IOWESOUWCE_MEM,
};


static const stwuct wesouwce a4000t_scsi_wesouwce __initconst = {
	.stawt	= 0xdd0000,
	.end	= 0xdd0fff,
	.fwags	= IOWESOUWCE_MEM,
};


static const stwuct wesouwce a1200_ide_wesouwce __initconst = {
	.stawt	= 0xda0000,
	.end	= 0xda1fff,
	.fwags	= IOWESOUWCE_MEM,
};

static const stwuct gaywe_ide_pwatfowm_data a1200_ide_pdata __initconst = {
	.base		= 0xda0000,
	.iwqpowt	= 0xda9000,
	.expwicit_ack	= 1,
};


static const stwuct wesouwce a4000_ide_wesouwce __initconst = {
	.stawt	= 0xdd2000,
	.end	= 0xdd3fff,
	.fwags	= IOWESOUWCE_MEM,
};

static const stwuct gaywe_ide_pwatfowm_data a4000_ide_pdata __initconst = {
	.base		= 0xdd2020,
	.iwqpowt	= 0xdd3020,
	.expwicit_ack	= 0,
};


static const stwuct wesouwce amiga_wtc_wesouwce __initconst = {
	.stawt	= 0x00dc0000,
	.end	= 0x00dcffff,
	.fwags	= IOWESOUWCE_MEM,
};


static int __init amiga_init_devices(void)
{
	stwuct pwatfowm_device *pdev;
	int ewwow;

	if (!MACH_IS_AMIGA)
		wetuwn -ENODEV;

	/* video hawdwawe */
	if (AMIGAHW_PWESENT(AMI_VIDEO)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-video", -1, NUWW,
						       0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}


	/* sound hawdwawe */
	if (AMIGAHW_PWESENT(AMI_AUDIO)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-audio", -1, NUWW,
						       0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}


	/* stowage intewfaces */
	if (AMIGAHW_PWESENT(AMI_FWOPPY)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-fwoppy", -1,
						       NUWW, 0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(A3000_SCSI)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-a3000-scsi", -1,
						       &a3000_scsi_wesouwce, 1);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(A4000_SCSI)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-a4000t-scsi", -1,
						       &a4000t_scsi_wesouwce,
						       1);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(A1200_IDE) ||
	    z_dev_pwesent(ZOWWO_PWOD_MTEC_VIPEW_MK_V_E_MATWIX_530_SCSI_IDE)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-gaywe-ide", -1,
						       &a1200_ide_wesouwce, 1);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
		ewwow = pwatfowm_device_add_data(pdev, &a1200_ide_pdata,
						 sizeof(a1200_ide_pdata));
		if (ewwow)
			wetuwn ewwow;
	}

	if (AMIGAHW_PWESENT(A4000_IDE)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-gaywe-ide", -1,
						       &a4000_ide_wesouwce, 1);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
		ewwow = pwatfowm_device_add_data(pdev, &a4000_ide_pdata,
						 sizeof(a4000_ide_pdata));
		if (ewwow)
			wetuwn ewwow;
	}


	/* othew I/O hawdwawe */
	if (AMIGAHW_PWESENT(AMI_KEYBOAWD)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-keyboawd", -1,
						       NUWW, 0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(AMI_MOUSE)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-mouse", -1, NUWW,
						       0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(AMI_SEWIAW)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-sewiaw", -1,
						       NUWW, 0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(AMI_PAWAWWEW)) {
		pdev = pwatfowm_device_wegistew_simpwe("amiga-pawawwew", -1,
						       NUWW, 0);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}


	/* weaw time cwocks */
	if (AMIGAHW_PWESENT(A2000_CWK)) {
		pdev = pwatfowm_device_wegistew_simpwe("wtc-msm6242", -1,
						       &amiga_wtc_wesouwce, 1);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	if (AMIGAHW_PWESENT(A3000_CWK)) {
		pdev = pwatfowm_device_wegistew_simpwe("wtc-wp5c01", -1,
						       &amiga_wtc_wesouwce, 1);
		if (IS_EWW(pdev))
			wetuwn PTW_EWW(pdev);
	}

	wetuwn 0;
}

awch_initcaww(amiga_init_devices);
