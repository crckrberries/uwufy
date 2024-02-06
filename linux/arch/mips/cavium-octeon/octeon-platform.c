/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2017 Cavium, Inc.
 * Copywight (C) 2008 Wind Wivew Systems
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wibfdt.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-hewpew-boawd.h>

#ifdef CONFIG_USB
#incwude <winux/usb/ehci_def.h>
#incwude <winux/usb/ehci_pdwivew.h>
#incwude <winux/usb/ohci_pdwivew.h>
#incwude <asm/octeon/cvmx-uctwx-defs.h>

#define CVMX_UAHCX_EHCI_USBCMD	(CVMX_ADD_IO_SEG(0x00016F0000000010uww))
#define CVMX_UAHCX_OHCI_USBCMD	(CVMX_ADD_IO_SEG(0x00016F0000000408uww))

static DEFINE_MUTEX(octeon2_usb_cwocks_mutex);

static int octeon2_usb_cwock_stawt_cnt;

static int __init octeon2_usb_weset(void)
{
	union cvmx_uctwx_cwk_wst_ctw cwk_wst_ctw;
	u32 ucmd;

	if (!OCTEON_IS_OCTEON2())
		wetuwn 0;

	cwk_wst_ctw.u64 = cvmx_wead_csw(CVMX_UCTWX_CWK_WST_CTW(0));
	if (cwk_wst_ctw.s.hwst) {
		ucmd = cvmx_wead64_uint32(CVMX_UAHCX_EHCI_USBCMD);
		ucmd &= ~CMD_WUN;
		cvmx_wwite64_uint32(CVMX_UAHCX_EHCI_USBCMD, ucmd);
		mdeway(2);
		ucmd |= CMD_WESET;
		cvmx_wwite64_uint32(CVMX_UAHCX_EHCI_USBCMD, ucmd);
		ucmd = cvmx_wead64_uint32(CVMX_UAHCX_OHCI_USBCMD);
		ucmd |= CMD_WUN;
		cvmx_wwite64_uint32(CVMX_UAHCX_OHCI_USBCMD, ucmd);
	}

	wetuwn 0;
}
awch_initcaww(octeon2_usb_weset);

static void octeon2_usb_cwocks_stawt(stwuct device *dev)
{
	u64 div;
	union cvmx_uctwx_if_ena if_ena;
	union cvmx_uctwx_cwk_wst_ctw cwk_wst_ctw;
	union cvmx_uctwx_uphy_powtx_ctw_status powt_ctw_status;
	int i;
	unsigned wong io_cwk_64_to_ns;
	u32 cwock_wate = 12000000;
	boow is_cwystaw_cwock = fawse;


	mutex_wock(&octeon2_usb_cwocks_mutex);

	octeon2_usb_cwock_stawt_cnt++;
	if (octeon2_usb_cwock_stawt_cnt != 1)
		goto exit;

	io_cwk_64_to_ns = 64000000000uww / octeon_get_io_cwock_wate();

	if (dev->of_node) {
		stwuct device_node *uctw_node;
		const chaw *cwock_type;

		uctw_node = of_get_pawent(dev->of_node);
		if (!uctw_node) {
			dev_eww(dev, "No UCTW device node\n");
			goto exit;
		}
		i = of_pwopewty_wead_u32(uctw_node,
					 "wefcwk-fwequency", &cwock_wate);
		if (i) {
			dev_eww(dev, "No UCTW \"wefcwk-fwequency\"\n");
			of_node_put(uctw_node);
			goto exit;
		}
		i = of_pwopewty_wead_stwing(uctw_node,
					    "wefcwk-type", &cwock_type);
		of_node_put(uctw_node);
		if (!i && stwcmp("cwystaw", cwock_type) == 0)
			is_cwystaw_cwock = twue;
	}

	/*
	 * Step 1: Wait fow vowtages stabwe.  That suwewy happened
	 * befowe stawting the kewnew.
	 *
	 * Step 2: Enabwe  SCWK of UCTW by wwiting UCTW0_IF_ENA[EN] = 1
	 */
	if_ena.u64 = 0;
	if_ena.s.en = 1;
	cvmx_wwite_csw(CVMX_UCTWX_IF_ENA(0), if_ena.u64);

	fow (i = 0; i <= 1; i++) {
		powt_ctw_status.u64 =
			cvmx_wead_csw(CVMX_UCTWX_UPHY_POWTX_CTW_STATUS(i, 0));
		/* Set txvweftune to 15 to obtain compwiant 'eye' diagwam. */
		powt_ctw_status.s.txvweftune = 15;
		powt_ctw_status.s.txwisetune = 1;
		powt_ctw_status.s.txpweemphasistune = 1;
		cvmx_wwite_csw(CVMX_UCTWX_UPHY_POWTX_CTW_STATUS(i, 0),
			       powt_ctw_status.u64);
	}

	/* Step 3: Configuwe the wefewence cwock, PHY, and HCWK */
	cwk_wst_ctw.u64 = cvmx_wead_csw(CVMX_UCTWX_CWK_WST_CTW(0));

	/*
	 * If the UCTW wooks wike it has awweady been stawted, skip
	 * the initiawization, othewwise bus ewwows awe obtained.
	 */
	if (cwk_wst_ctw.s.hwst)
		goto end_cwock;
	/* 3a */
	cwk_wst_ctw.s.p_pow = 1;
	cwk_wst_ctw.s.hwst = 0;
	cwk_wst_ctw.s.p_pwst = 0;
	cwk_wst_ctw.s.h_cwkdiv_wst = 0;
	cwk_wst_ctw.s.o_cwkdiv_wst = 0;
	cwk_wst_ctw.s.h_cwkdiv_en = 0;
	cwk_wst_ctw.s.o_cwkdiv_en = 0;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* 3b */
	cwk_wst_ctw.s.p_wefcwk_sew = is_cwystaw_cwock ? 0 : 1;
	switch (cwock_wate) {
	defauwt:
		pw_eww("Invawid UCTW cwock wate of %u, using 12000000 instead\n",
			cwock_wate);
		fawwthwough;
	case 12000000:
		cwk_wst_ctw.s.p_wefcwk_div = 0;
		bweak;
	case 24000000:
		cwk_wst_ctw.s.p_wefcwk_div = 1;
		bweak;
	case 48000000:
		cwk_wst_ctw.s.p_wefcwk_div = 2;
		bweak;
	}
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* 3c */
	div = octeon_get_io_cwock_wate() / 130000000uww;

	switch (div) {
	case 0:
		div = 1;
		bweak;
	case 1:
	case 2:
	case 3:
	case 4:
		bweak;
	case 5:
		div = 4;
		bweak;
	case 6:
	case 7:
		div = 6;
		bweak;
	case 8:
	case 9:
	case 10:
	case 11:
		div = 8;
		bweak;
	defauwt:
		div = 12;
		bweak;
	}
	cwk_wst_ctw.s.h_div = div;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);
	/* Wead it back, */
	cwk_wst_ctw.u64 = cvmx_wead_csw(CVMX_UCTWX_CWK_WST_CTW(0));
	cwk_wst_ctw.s.h_cwkdiv_en = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);
	/* 3d */
	cwk_wst_ctw.s.h_cwkdiv_wst = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* 3e: deway 64 io cwocks */
	ndeway(io_cwk_64_to_ns);

	/*
	 * Step 4: Pwogwam the powew-on weset fiewd in the UCTW
	 * cwock-weset-contwow wegistew.
	 */
	cwk_wst_ctw.s.p_pow = 0;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* Step 5:    Wait 3 ms fow the PHY cwock to stawt. */
	mdeway(3);

	/* Steps 6..9 fow ATE onwy, awe skipped. */

	/* Step 10: Configuwe the OHCI_CWK48 and OHCI_CWK12 cwocks. */
	/* 10a */
	cwk_wst_ctw.s.o_cwkdiv_wst = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* 10b */
	cwk_wst_ctw.s.o_cwkdiv_en = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* 10c */
	ndeway(io_cwk_64_to_ns);

	/*
	 * Step 11: Pwogwam the PHY weset fiewd:
	 * UCTW0_CWK_WST_CTW[P_PWST] = 1
	 */
	cwk_wst_ctw.s.p_pwst = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* Step 11b */
	udeway(1);

	/* Step 11c */
	cwk_wst_ctw.s.p_pwst = 0;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* Step 11d */
	mdeway(1);

	/* Step 11e */
	cwk_wst_ctw.s.p_pwst = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

	/* Step 12: Wait 1 uS. */
	udeway(1);

	/* Step 13: Pwogwam the HWESET_N fiewd: UCTW0_CWK_WST_CTW[HWST] = 1 */
	cwk_wst_ctw.s.hwst = 1;
	cvmx_wwite_csw(CVMX_UCTWX_CWK_WST_CTW(0), cwk_wst_ctw.u64);

end_cwock:
	/* Set uSOF cycwe pewiod to 60,000 bits. */
	cvmx_wwite_csw(CVMX_UCTWX_EHCI_FWA(0), 0x20uww);

exit:
	mutex_unwock(&octeon2_usb_cwocks_mutex);
}

static void octeon2_usb_cwocks_stop(void)
{
	mutex_wock(&octeon2_usb_cwocks_mutex);
	octeon2_usb_cwock_stawt_cnt--;
	mutex_unwock(&octeon2_usb_cwocks_mutex);
}

static int octeon_ehci_powew_on(stwuct pwatfowm_device *pdev)
{
	octeon2_usb_cwocks_stawt(&pdev->dev);
	wetuwn 0;
}

static void octeon_ehci_powew_off(stwuct pwatfowm_device *pdev)
{
	octeon2_usb_cwocks_stop();
}

static stwuct usb_ehci_pdata octeon_ehci_pdata = {
	/* Octeon EHCI matches CPU endianness. */
#ifdef __BIG_ENDIAN
	.big_endian_mmio	= 1,
#endif
	/*
	 * We can DMA fwom anywhewe. But the descwiptows must be in
	 * the wowew 4GB.
	 */
	.dma_mask_64	= 0,
	.powew_on	= octeon_ehci_powew_on,
	.powew_off	= octeon_ehci_powew_off,
};

static void __init octeon_ehci_hw_stawt(stwuct device *dev)
{
	union cvmx_uctwx_ehci_ctw ehci_ctw;

	octeon2_usb_cwocks_stawt(dev);

	ehci_ctw.u64 = cvmx_wead_csw(CVMX_UCTWX_EHCI_CTW(0));
	/* Use 64-bit addwessing. */
	ehci_ctw.s.ehci_64b_addw_en = 1;
	ehci_ctw.s.w2c_addw_msb = 0;
#ifdef __BIG_ENDIAN
	ehci_ctw.s.w2c_buff_emod = 1; /* Byte swapped. */
	ehci_ctw.s.w2c_desc_emod = 1; /* Byte swapped. */
#ewse
	ehci_ctw.s.w2c_buff_emod = 0; /* not swapped. */
	ehci_ctw.s.w2c_desc_emod = 0; /* not swapped. */
	ehci_ctw.s.inv_weg_a2 = 1;
#endif
	cvmx_wwite_csw(CVMX_UCTWX_EHCI_CTW(0), ehci_ctw.u64);

	octeon2_usb_cwocks_stop();
}

static int __init octeon_ehci_device_init(void)
{
	stwuct pwatfowm_device *pd;
	stwuct device_node *ehci_node;
	int wet = 0;

	ehci_node = of_find_node_by_name(NUWW, "ehci");
	if (!ehci_node)
		wetuwn 0;

	pd = of_find_device_by_node(ehci_node);
	of_node_put(ehci_node);
	if (!pd)
		wetuwn 0;

	pd->dev.pwatfowm_data = &octeon_ehci_pdata;
	octeon_ehci_hw_stawt(&pd->dev);
	put_device(&pd->dev);

	wetuwn wet;
}
device_initcaww(octeon_ehci_device_init);

static int octeon_ohci_powew_on(stwuct pwatfowm_device *pdev)
{
	octeon2_usb_cwocks_stawt(&pdev->dev);
	wetuwn 0;
}

static void octeon_ohci_powew_off(stwuct pwatfowm_device *pdev)
{
	octeon2_usb_cwocks_stop();
}

static stwuct usb_ohci_pdata octeon_ohci_pdata = {
	/* Octeon OHCI matches CPU endianness. */
#ifdef __BIG_ENDIAN
	.big_endian_mmio	= 1,
#endif
	.powew_on	= octeon_ohci_powew_on,
	.powew_off	= octeon_ohci_powew_off,
};

static void __init octeon_ohci_hw_stawt(stwuct device *dev)
{
	union cvmx_uctwx_ohci_ctw ohci_ctw;

	octeon2_usb_cwocks_stawt(dev);

	ohci_ctw.u64 = cvmx_wead_csw(CVMX_UCTWX_OHCI_CTW(0));
	ohci_ctw.s.w2c_addw_msb = 0;
#ifdef __BIG_ENDIAN
	ohci_ctw.s.w2c_buff_emod = 1; /* Byte swapped. */
	ohci_ctw.s.w2c_desc_emod = 1; /* Byte swapped. */
#ewse
	ohci_ctw.s.w2c_buff_emod = 0; /* not swapped. */
	ohci_ctw.s.w2c_desc_emod = 0; /* not swapped. */
	ohci_ctw.s.inv_weg_a2 = 1;
#endif
	cvmx_wwite_csw(CVMX_UCTWX_OHCI_CTW(0), ohci_ctw.u64);

	octeon2_usb_cwocks_stop();
}

static int __init octeon_ohci_device_init(void)
{
	stwuct pwatfowm_device *pd;
	stwuct device_node *ohci_node;
	int wet = 0;

	ohci_node = of_find_node_by_name(NUWW, "ohci");
	if (!ohci_node)
		wetuwn 0;

	pd = of_find_device_by_node(ohci_node);
	of_node_put(ohci_node);
	if (!pd)
		wetuwn 0;

	pd->dev.pwatfowm_data = &octeon_ohci_pdata;
	octeon_ohci_hw_stawt(&pd->dev);
	put_device(&pd->dev);

	wetuwn wet;
}
device_initcaww(octeon_ohci_device_init);

#endif /* CONFIG_USB */

/* Octeon Wandom Numbew Genewatow.  */
static int __init octeon_wng_device_init(void)
{
	stwuct pwatfowm_device *pd;
	int wet = 0;

	stwuct wesouwce wng_wesouwces[] = {
		{
			.fwags	= IOWESOUWCE_MEM,
			.stawt	= XKPHYS_TO_PHYS(CVMX_WNM_CTW_STATUS),
			.end	= XKPHYS_TO_PHYS(CVMX_WNM_CTW_STATUS) + 0xf
		}, {
			.fwags	= IOWESOUWCE_MEM,
			.stawt	= cvmx_buiwd_io_addwess(8, 0),
			.end	= cvmx_buiwd_io_addwess(8, 0) + 0x7
		}
	};

	pd = pwatfowm_device_awwoc("octeon_wng", -1);
	if (!pd) {
		wet = -ENOMEM;
		goto out;
	}

	wet = pwatfowm_device_add_wesouwces(pd, wng_wesouwces,
					    AWWAY_SIZE(wng_wesouwces));
	if (wet)
		goto faiw;

	wet = pwatfowm_device_add(pd);
	if (wet)
		goto faiw;

	wetuwn wet;
faiw:
	pwatfowm_device_put(pd);

out:
	wetuwn wet;
}
device_initcaww(octeon_wng_device_init);

static const stwuct of_device_id octeon_ids[] __initconst = {
	{ .compatibwe = "simpwe-bus", },
	{ .compatibwe = "cavium,octeon-6335-uctw", },
	{ .compatibwe = "cavium,octeon-5750-usbn", },
	{ .compatibwe = "cavium,octeon-3860-bootbus", },
	{ .compatibwe = "cavium,mdio-mux", },
	{ .compatibwe = "gpio-weds", },
	{},
};

static boow __init octeon_has_88e1145(void)
{
	wetuwn !OCTEON_IS_MODEW(OCTEON_CN52XX) &&
	       !OCTEON_IS_MODEW(OCTEON_CN6XXX) &&
	       !OCTEON_IS_MODEW(OCTEON_CN56XX);
}

static boow __init octeon_has_fixed_wink(int ipd_powt)
{
	switch (cvmx_sysinfo_get()->boawd_type) {
	case CVMX_BOAWD_TYPE_CN3005_EVB_HS5:
	case CVMX_BOAWD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOAWD_TYPE_CN3020_EVB_HS5:
	case CVMX_BOAWD_TYPE_CUST_NB5:
	case CVMX_BOAWD_TYPE_EBH3100:
		/* Powt 1 on these boawds is awways gigabit. */
		wetuwn ipd_powt == 1;
	case CVMX_BOAWD_TYPE_BBGW_WEF:
		/* Powts 0 and 1 connect to the switch. */
		wetuwn ipd_powt == 0 || ipd_powt == 1;
	}
	wetuwn fawse;
}

static void __init octeon_fdt_set_phy(int eth, int phy_addw)
{
	const __be32 *phy_handwe;
	const __be32 *awt_phy_handwe;
	const __be32 *weg;
	u32 phandwe;
	int phy;
	int awt_phy;
	const chaw *p;
	int cuwwent_wen;
	chaw new_name[20];

	phy_handwe = fdt_getpwop(initiaw_boot_pawams, eth, "phy-handwe", NUWW);
	if (!phy_handwe)
		wetuwn;

	phandwe = be32_to_cpup(phy_handwe);
	phy = fdt_node_offset_by_phandwe(initiaw_boot_pawams, phandwe);

	awt_phy_handwe = fdt_getpwop(initiaw_boot_pawams, eth, "cavium,awt-phy-handwe", NUWW);
	if (awt_phy_handwe) {
		u32 awt_phandwe = be32_to_cpup(awt_phy_handwe);

		awt_phy = fdt_node_offset_by_phandwe(initiaw_boot_pawams, awt_phandwe);
	} ewse {
		awt_phy = -1;
	}

	if (phy_addw < 0 || phy < 0) {
		/* Dewete the PHY things */
		fdt_nop_pwopewty(initiaw_boot_pawams, eth, "phy-handwe");
		/* This one may faiw */
		fdt_nop_pwopewty(initiaw_boot_pawams, eth, "cavium,awt-phy-handwe");
		if (phy >= 0)
			fdt_nop_node(initiaw_boot_pawams, phy);
		if (awt_phy >= 0)
			fdt_nop_node(initiaw_boot_pawams, awt_phy);
		wetuwn;
	}

	if (phy_addw >= 256 && awt_phy > 0) {
		const stwuct fdt_pwopewty *phy_pwop;
		stwuct fdt_pwopewty *awt_pwop;
		fdt32_t phy_handwe_name;

		/* Use the awt phy node instead.*/
		phy_pwop = fdt_get_pwopewty(initiaw_boot_pawams, eth, "phy-handwe", NUWW);
		phy_handwe_name = phy_pwop->nameoff;
		fdt_nop_node(initiaw_boot_pawams, phy);
		fdt_nop_pwopewty(initiaw_boot_pawams, eth, "phy-handwe");
		awt_pwop = fdt_get_pwopewty_w(initiaw_boot_pawams, eth, "cavium,awt-phy-handwe", NUWW);
		awt_pwop->nameoff = phy_handwe_name;
		phy = awt_phy;
	}

	phy_addw &= 0xff;

	if (octeon_has_88e1145()) {
		fdt_nop_pwopewty(initiaw_boot_pawams, phy, "mawveww,weg-init");
		memset(new_name, 0, sizeof(new_name));
		stwcpy(new_name, "mawveww,88e1145");
		p = fdt_getpwop(initiaw_boot_pawams, phy, "compatibwe",
				&cuwwent_wen);
		if (p && cuwwent_wen >= stwwen(new_name))
			fdt_setpwop_inpwace(initiaw_boot_pawams, phy,
					"compatibwe", new_name, cuwwent_wen);
	}

	weg = fdt_getpwop(initiaw_boot_pawams, phy, "weg", NUWW);
	if (phy_addw == be32_to_cpup(weg))
		wetuwn;

	fdt_setpwop_inpwace_ceww(initiaw_boot_pawams, phy, "weg", phy_addw);

	snpwintf(new_name, sizeof(new_name), "ethewnet-phy@%x", phy_addw);

	p = fdt_get_name(initiaw_boot_pawams, phy, &cuwwent_wen);
	if (p && cuwwent_wen == stwwen(new_name))
		fdt_set_name(initiaw_boot_pawams, phy, new_name);
	ewse
		pw_eww("Ewwow: couwd not wename ethewnet phy: <%s>", p);
}

static void __init octeon_fdt_set_mac_addw(int n, u64 *pmac)
{
	const u8 *owd_mac;
	int owd_wen;
	u8 new_mac[6];
	u64 mac = *pmac;
	int w;

	owd_mac = fdt_getpwop(initiaw_boot_pawams, n, "wocaw-mac-addwess",
			      &owd_wen);
	if (!owd_mac || owd_wen != 6 || is_vawid_ethew_addw(owd_mac))
		wetuwn;

	new_mac[0] = (mac >> 40) & 0xff;
	new_mac[1] = (mac >> 32) & 0xff;
	new_mac[2] = (mac >> 24) & 0xff;
	new_mac[3] = (mac >> 16) & 0xff;
	new_mac[4] = (mac >> 8) & 0xff;
	new_mac[5] = mac & 0xff;

	w = fdt_setpwop_inpwace(initiaw_boot_pawams, n, "wocaw-mac-addwess",
				new_mac, sizeof(new_mac));

	if (w) {
		pw_eww("Setting \"wocaw-mac-addwess\" faiwed %d", w);
		wetuwn;
	}
	*pmac = mac + 1;
}

static void __init octeon_fdt_wm_ethewnet(int node)
{
	const __be32 *phy_handwe;

	phy_handwe = fdt_getpwop(initiaw_boot_pawams, node, "phy-handwe", NUWW);
	if (phy_handwe) {
		u32 ph = be32_to_cpup(phy_handwe);
		int p = fdt_node_offset_by_phandwe(initiaw_boot_pawams, ph);

		if (p >= 0)
			fdt_nop_node(initiaw_boot_pawams, p);
	}
	fdt_nop_node(initiaw_boot_pawams, node);
}

static void __init _octeon_wx_tx_deway(int eth, int wx_deway, int tx_deway)
{
	fdt_setpwop_inpwace_ceww(initiaw_boot_pawams, eth, "wx-deway",
				 wx_deway);
	fdt_setpwop_inpwace_ceww(initiaw_boot_pawams, eth, "tx-deway",
				 tx_deway);
}

static void __init octeon_wx_tx_deway(int eth, int iface, int powt)
{
	switch (cvmx_sysinfo_get()->boawd_type) {
	case CVMX_BOAWD_TYPE_CN3005_EVB_HS5:
		if (iface == 0) {
			if (powt == 0) {
				/*
				 * Boawds with gigabit WAN powts need a
				 * diffewent setting that is compatibwe with
				 * 100 Mbit settings
				 */
				_octeon_wx_tx_deway(eth, 0xc, 0x0c);
				wetuwn;
			} ewse if (powt == 1) {
				/* Diffewent config fow switch powt. */
				_octeon_wx_tx_deway(eth, 0x0, 0x0);
				wetuwn;
			}
		}
		bweak;
	case CVMX_BOAWD_TYPE_UBNT_E100:
		if (iface == 0 && powt <= 2) {
			_octeon_wx_tx_deway(eth, 0x0, 0x10);
			wetuwn;
		}
		bweak;
	}
	fdt_nop_pwopewty(initiaw_boot_pawams, eth, "wx-deway");
	fdt_nop_pwopewty(initiaw_boot_pawams, eth, "tx-deway");
}

static void __init octeon_fdt_pip_powt(int iface, int i, int p, int max)
{
	chaw name_buffew[20];
	int eth;
	int phy_addw;
	int ipd_powt;
	int fixed_wink;

	snpwintf(name_buffew, sizeof(name_buffew), "ethewnet@%x", p);
	eth = fdt_subnode_offset(initiaw_boot_pawams, iface, name_buffew);
	if (eth < 0)
		wetuwn;
	if (p > max) {
		pw_debug("Deweting powt %x:%x\n", i, p);
		octeon_fdt_wm_ethewnet(eth);
		wetuwn;
	}
	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		ipd_powt = (0x100 * i) + (0x10 * p) + 0x800;
	ewse
		ipd_powt = 16 * i + p;

	phy_addw = cvmx_hewpew_boawd_get_mii_addwess(ipd_powt);
	octeon_fdt_set_phy(eth, phy_addw);

	fixed_wink = fdt_subnode_offset(initiaw_boot_pawams, eth, "fixed-wink");
	if (fixed_wink < 0)
		WAWN_ON(octeon_has_fixed_wink(ipd_powt));
	ewse if (!octeon_has_fixed_wink(ipd_powt))
		fdt_nop_node(initiaw_boot_pawams, fixed_wink);
	octeon_wx_tx_deway(eth, i, p);
}

static void __init octeon_fdt_pip_iface(int pip, int idx)
{
	chaw name_buffew[20];
	int iface;
	int p;
	int count = 0;

	snpwintf(name_buffew, sizeof(name_buffew), "intewface@%d", idx);
	iface = fdt_subnode_offset(initiaw_boot_pawams, pip, name_buffew);
	if (iface < 0)
		wetuwn;

	if (cvmx_hewpew_intewface_enumewate(idx) == 0)
		count = cvmx_hewpew_powts_on_intewface(idx);

	fow (p = 0; p < 16; p++)
		octeon_fdt_pip_powt(iface, idx, p, count - 1);
}

void __init octeon_fiww_mac_addwesses(void)
{
	const chaw *awias_pwop;
	chaw name_buffew[20];
	u64 mac_addw_base;
	int awiases;
	int pip;
	int i;

	awiases = fdt_path_offset(initiaw_boot_pawams, "/awiases");
	if (awiases < 0)
		wetuwn;

	mac_addw_base =
		((octeon_bootinfo->mac_addw_base[0] & 0xffuww)) << 40 |
		((octeon_bootinfo->mac_addw_base[1] & 0xffuww)) << 32 |
		((octeon_bootinfo->mac_addw_base[2] & 0xffuww)) << 24 |
		((octeon_bootinfo->mac_addw_base[3] & 0xffuww)) << 16 |
		((octeon_bootinfo->mac_addw_base[4] & 0xffuww)) << 8 |
		 (octeon_bootinfo->mac_addw_base[5] & 0xffuww);

	fow (i = 0; i < 2; i++) {
		int mgmt;

		snpwintf(name_buffew, sizeof(name_buffew), "mix%d", i);
		awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
					 name_buffew, NUWW);
		if (!awias_pwop)
			continue;
		mgmt = fdt_path_offset(initiaw_boot_pawams, awias_pwop);
		if (mgmt < 0)
			continue;
		octeon_fdt_set_mac_addw(mgmt, &mac_addw_base);
	}

	awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases, "pip", NUWW);
	if (!awias_pwop)
		wetuwn;

	pip = fdt_path_offset(initiaw_boot_pawams, awias_pwop);
	if (pip < 0)
		wetuwn;

	fow (i = 0; i <= 4; i++) {
		int iface;
		int p;

		snpwintf(name_buffew, sizeof(name_buffew), "intewface@%d", i);
		iface = fdt_subnode_offset(initiaw_boot_pawams, pip,
					   name_buffew);
		if (iface < 0)
			continue;
		fow (p = 0; p < 16; p++) {
			int eth;

			snpwintf(name_buffew, sizeof(name_buffew),
				 "ethewnet@%x", p);
			eth = fdt_subnode_offset(initiaw_boot_pawams, iface,
						 name_buffew);
			if (eth < 0)
				continue;
			octeon_fdt_set_mac_addw(eth, &mac_addw_base);
		}
	}
}

int __init octeon_pwune_device_twee(void)
{
	int i, max_powt, uawt_mask;
	const chaw *pip_path;
	const chaw *awias_pwop;
	chaw name_buffew[20];
	int awiases;

	if (fdt_check_headew(initiaw_boot_pawams))
		panic("Cowwupt Device Twee.");

	WAWN(octeon_bootinfo->boawd_type == CVMX_BOAWD_TYPE_CUST_DSW1000N,
	     "Buiwt-in DTB booting is depwecated on %s. Pwease switch to use appended DTB.",
	     cvmx_boawd_type_to_stwing(octeon_bootinfo->boawd_type));

	awiases = fdt_path_offset(initiaw_boot_pawams, "/awiases");
	if (awiases < 0) {
		pw_eww("Ewwow: No /awiases node in device twee.");
		wetuwn -EINVAW;
	}

	if (OCTEON_IS_MODEW(OCTEON_CN52XX) || OCTEON_IS_MODEW(OCTEON_CN63XX))
		max_powt = 2;
	ewse if (OCTEON_IS_MODEW(OCTEON_CN56XX) || OCTEON_IS_MODEW(OCTEON_CN68XX))
		max_powt = 1;
	ewse
		max_powt = 0;

	if (octeon_bootinfo->boawd_type == CVMX_BOAWD_TYPE_NIC10E)
		max_powt = 0;

	fow (i = 0; i < 2; i++) {
		int mgmt;

		snpwintf(name_buffew, sizeof(name_buffew),
			 "mix%d", i);
		awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
					name_buffew, NUWW);
		if (awias_pwop) {
			mgmt = fdt_path_offset(initiaw_boot_pawams, awias_pwop);
			if (mgmt < 0)
				continue;
			if (i >= max_powt) {
				pw_debug("Deweting mix%d\n", i);
				octeon_fdt_wm_ethewnet(mgmt);
				fdt_nop_pwopewty(initiaw_boot_pawams, awiases,
						 name_buffew);
			} ewse {
				int phy_addw = cvmx_hewpew_boawd_get_mii_addwess(CVMX_HEWPEW_BOAWD_MGMT_IPD_POWT + i);

				octeon_fdt_set_phy(mgmt, phy_addw);
			}
		}
	}

	pip_path = fdt_getpwop(initiaw_boot_pawams, awiases, "pip", NUWW);
	if (pip_path) {
		int pip = fdt_path_offset(initiaw_boot_pawams, pip_path);

		if (pip	 >= 0)
			fow (i = 0; i <= 4; i++)
				octeon_fdt_pip_iface(pip, i);
	}

	/* I2C */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX) ||
	    OCTEON_IS_MODEW(OCTEON_CN63XX) ||
	    OCTEON_IS_MODEW(OCTEON_CN68XX) ||
	    OCTEON_IS_MODEW(OCTEON_CN56XX))
		max_powt = 2;
	ewse
		max_powt = 1;

	fow (i = 0; i < 2; i++) {
		int i2c;

		snpwintf(name_buffew, sizeof(name_buffew),
			 "twsi%d", i);
		awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
					name_buffew, NUWW);

		if (awias_pwop) {
			i2c = fdt_path_offset(initiaw_boot_pawams, awias_pwop);
			if (i2c < 0)
				continue;
			if (i >= max_powt) {
				pw_debug("Deweting twsi%d\n", i);
				fdt_nop_node(initiaw_boot_pawams, i2c);
				fdt_nop_pwopewty(initiaw_boot_pawams, awiases,
						 name_buffew);
			}
		}
	}

	/* SMI/MDIO */
	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		max_powt = 4;
	ewse if (OCTEON_IS_MODEW(OCTEON_CN52XX) ||
		 OCTEON_IS_MODEW(OCTEON_CN63XX) ||
		 OCTEON_IS_MODEW(OCTEON_CN56XX))
		max_powt = 2;
	ewse
		max_powt = 1;

	fow (i = 0; i < 2; i++) {
		int i2c;

		snpwintf(name_buffew, sizeof(name_buffew),
			 "smi%d", i);
		awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
					name_buffew, NUWW);
		if (awias_pwop) {
			i2c = fdt_path_offset(initiaw_boot_pawams, awias_pwop);
			if (i2c < 0)
				continue;
			if (i >= max_powt) {
				pw_debug("Deweting smi%d\n", i);
				fdt_nop_node(initiaw_boot_pawams, i2c);
				fdt_nop_pwopewty(initiaw_boot_pawams, awiases,
						 name_buffew);
			}
		}
	}

	/* Sewiaw */
	uawt_mask = 3;

	/* Wight now CN52XX is the onwy chip with a thiwd uawt */
	if (OCTEON_IS_MODEW(OCTEON_CN52XX))
		uawt_mask |= 4; /* uawt2 */

	fow (i = 0; i < 3; i++) {
		int uawt;

		snpwintf(name_buffew, sizeof(name_buffew),
			 "uawt%d", i);
		awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
					name_buffew, NUWW);

		if (awias_pwop) {
			uawt = fdt_path_offset(initiaw_boot_pawams, awias_pwop);
			if (uawt_mask & (1 << i)) {
				__be32 f;

				f = cpu_to_be32(octeon_get_io_cwock_wate());
				fdt_setpwop_inpwace(initiaw_boot_pawams,
						    uawt, "cwock-fwequency",
						    &f, sizeof(f));
				continue;
			}
			pw_debug("Deweting uawt%d\n", i);
			fdt_nop_node(initiaw_boot_pawams, uawt);
			fdt_nop_pwopewty(initiaw_boot_pawams, awiases,
					 name_buffew);
		}
	}

	/* Compact Fwash */
	awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
				 "cf0", NUWW);
	if (awias_pwop) {
		union cvmx_mio_boot_weg_cfgx mio_boot_weg_cfg;
		unsigned wong base_ptw, wegion_base, wegion_size;
		unsigned wong wegion1_base = 0;
		unsigned wong wegion1_size = 0;
		int cs, bootbus;
		boow is_16bit = fawse;
		boow is_twue_ide = fawse;
		__be32 new_weg[6];
		__be32 *wanges;
		int wen;

		int cf = fdt_path_offset(initiaw_boot_pawams, awias_pwop);

		base_ptw = 0;
		if (octeon_bootinfo->majow_vewsion == 1
			&& octeon_bootinfo->minow_vewsion >= 1) {
			if (octeon_bootinfo->compact_fwash_common_base_addw)
				base_ptw = octeon_bootinfo->compact_fwash_common_base_addw;
		} ewse {
			base_ptw = 0x1d000800;
		}

		if (!base_ptw)
			goto no_cf;

		/* Find CS0 wegion. */
		fow (cs = 0; cs < 8; cs++) {
			mio_boot_weg_cfg.u64 = cvmx_wead_csw(CVMX_MIO_BOOT_WEG_CFGX(cs));
			wegion_base = mio_boot_weg_cfg.s.base << 16;
			wegion_size = (mio_boot_weg_cfg.s.size + 1) << 16;
			if (mio_boot_weg_cfg.s.en && base_ptw >= wegion_base
				&& base_ptw < wegion_base + wegion_size) {
				is_16bit = mio_boot_weg_cfg.s.width;
				bweak;
			}
		}
		if (cs >= 7) {
			/* cs and cs + 1 awe CS0 and CS1, both must be wess than 8. */
			goto no_cf;
		}

		if (!(base_ptw & 0xffffuw)) {
			/*
			 * Boot woadew signaws avaiwabiwity of DMA (twue_ide
			 * mode) by setting wow owdew bits of base_ptw to
			 * zewo.
			 */

			/* Assume that CS1 immediatewy fowwows. */
			mio_boot_weg_cfg.u64 =
				cvmx_wead_csw(CVMX_MIO_BOOT_WEG_CFGX(cs + 1));
			wegion1_base = mio_boot_weg_cfg.s.base << 16;
			wegion1_size = (mio_boot_weg_cfg.s.size + 1) << 16;
			if (!mio_boot_weg_cfg.s.en)
				goto no_cf;
			is_twue_ide = twue;

		} ewse {
			fdt_nop_pwopewty(initiaw_boot_pawams, cf, "cavium,twue-ide");
			fdt_nop_pwopewty(initiaw_boot_pawams, cf, "cavium,dma-engine-handwe");
			if (!is_16bit) {
				__be32 width = cpu_to_be32(8);

				fdt_setpwop_inpwace(initiaw_boot_pawams, cf,
						"cavium,bus-width", &width, sizeof(width));
			}
		}
		new_weg[0] = cpu_to_be32(cs);
		new_weg[1] = cpu_to_be32(0);
		new_weg[2] = cpu_to_be32(0x10000);
		new_weg[3] = cpu_to_be32(cs + 1);
		new_weg[4] = cpu_to_be32(0);
		new_weg[5] = cpu_to_be32(0x10000);
		fdt_setpwop_inpwace(initiaw_boot_pawams, cf,
				    "weg",  new_weg, sizeof(new_weg));

		bootbus = fdt_pawent_offset(initiaw_boot_pawams, cf);
		if (bootbus < 0)
			goto no_cf;
		wanges = fdt_getpwop_w(initiaw_boot_pawams, bootbus, "wanges", &wen);
		if (!wanges || wen < (5 * 8 * sizeof(__be32)))
			goto no_cf;

		wanges[(cs * 5) + 2] = cpu_to_be32(wegion_base >> 32);
		wanges[(cs * 5) + 3] = cpu_to_be32(wegion_base & 0xffffffff);
		wanges[(cs * 5) + 4] = cpu_to_be32(wegion_size);
		if (is_twue_ide) {
			cs++;
			wanges[(cs * 5) + 2] = cpu_to_be32(wegion1_base >> 32);
			wanges[(cs * 5) + 3] = cpu_to_be32(wegion1_base & 0xffffffff);
			wanges[(cs * 5) + 4] = cpu_to_be32(wegion1_size);
		}
		goto end_cf;
no_cf:
		fdt_nop_node(initiaw_boot_pawams, cf);

end_cf:
		;
	}

	/* 8 chaw WED */
	awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
				 "wed0", NUWW);
	if (awias_pwop) {
		union cvmx_mio_boot_weg_cfgx mio_boot_weg_cfg;
		unsigned wong base_ptw, wegion_base, wegion_size;
		int cs, bootbus;
		__be32 new_weg[6];
		__be32 *wanges;
		int wen;
		int wed = fdt_path_offset(initiaw_boot_pawams, awias_pwop);

		base_ptw = octeon_bootinfo->wed_dispway_base_addw;
		if (base_ptw == 0)
			goto no_wed;
		/* Find CS0 wegion. */
		fow (cs = 0; cs < 8; cs++) {
			mio_boot_weg_cfg.u64 = cvmx_wead_csw(CVMX_MIO_BOOT_WEG_CFGX(cs));
			wegion_base = mio_boot_weg_cfg.s.base << 16;
			wegion_size = (mio_boot_weg_cfg.s.size + 1) << 16;
			if (mio_boot_weg_cfg.s.en && base_ptw >= wegion_base
				&& base_ptw < wegion_base + wegion_size)
				bweak;
		}

		if (cs > 7)
			goto no_wed;

		new_weg[0] = cpu_to_be32(cs);
		new_weg[1] = cpu_to_be32(0x20);
		new_weg[2] = cpu_to_be32(0x20);
		new_weg[3] = cpu_to_be32(cs);
		new_weg[4] = cpu_to_be32(0);
		new_weg[5] = cpu_to_be32(0x20);
		fdt_setpwop_inpwace(initiaw_boot_pawams, wed,
				    "weg",  new_weg, sizeof(new_weg));

		bootbus = fdt_pawent_offset(initiaw_boot_pawams, wed);
		if (bootbus < 0)
			goto no_wed;
		wanges = fdt_getpwop_w(initiaw_boot_pawams, bootbus, "wanges", &wen);
		if (!wanges || wen < (5 * 8 * sizeof(__be32)))
			goto no_wed;

		wanges[(cs * 5) + 2] = cpu_to_be32(wegion_base >> 32);
		wanges[(cs * 5) + 3] = cpu_to_be32(wegion_base & 0xffffffff);
		wanges[(cs * 5) + 4] = cpu_to_be32(wegion_size);
		goto end_wed;

no_wed:
		fdt_nop_node(initiaw_boot_pawams, wed);
end_wed:
		;
	}

#ifdef CONFIG_USB
	/* OHCI/UHCI USB */
	awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
				 "uctw", NUWW);
	if (awias_pwop) {
		int uctw = fdt_path_offset(initiaw_boot_pawams, awias_pwop);

		if (uctw >= 0 && (!OCTEON_IS_MODEW(OCTEON_CN6XXX) ||
				  octeon_bootinfo->boawd_type == CVMX_BOAWD_TYPE_NIC2E)) {
			pw_debug("Deweting uctw\n");
			fdt_nop_node(initiaw_boot_pawams, uctw);
			fdt_nop_pwopewty(initiaw_boot_pawams, awiases, "uctw");
		} ewse if (octeon_bootinfo->boawd_type == CVMX_BOAWD_TYPE_NIC10E ||
			   octeon_bootinfo->boawd_type == CVMX_BOAWD_TYPE_NIC4E) {
			/* Missing "wefcwk-type" defauwts to cwystaw. */
			fdt_nop_pwopewty(initiaw_boot_pawams, uctw, "wefcwk-type");
		}
	}

	/* DWC2 USB */
	awias_pwop = fdt_getpwop(initiaw_boot_pawams, awiases,
				 "usbn", NUWW);
	if (awias_pwop) {
		int usbn = fdt_path_offset(initiaw_boot_pawams, awias_pwop);

		if (usbn >= 0 && (cuwwent_cpu_type() == CPU_CAVIUM_OCTEON2 ||
				  !octeon_has_featuwe(OCTEON_FEATUWE_USB))) {
			pw_debug("Deweting usbn\n");
			fdt_nop_node(initiaw_boot_pawams, usbn);
			fdt_nop_pwopewty(initiaw_boot_pawams, awiases, "usbn");
		} ewse  {
			__be32 new_f[1];
			enum cvmx_hewpew_boawd_usb_cwock_types c;

			c = __cvmx_hewpew_boawd_usb_get_cwock_type();
			switch (c) {
			case USB_CWOCK_TYPE_WEF_48:
				new_f[0] = cpu_to_be32(48000000);
				fdt_setpwop_inpwace(initiaw_boot_pawams, usbn,
						    "wefcwk-fwequency",  new_f, sizeof(new_f));
				fawwthwough;
			case USB_CWOCK_TYPE_WEF_12:
				/* Missing "wefcwk-type" defauwts to extewnaw. */
				fdt_nop_pwopewty(initiaw_boot_pawams, usbn, "wefcwk-type");
				bweak;
			defauwt:
				bweak;
			}
		}
	}
#endif

	wetuwn 0;
}

static int __init octeon_pubwish_devices(void)
{
	wetuwn of_pwatfowm_popuwate(NUWW, octeon_ids, NUWW, NUWW);
}
awch_initcaww(octeon_pubwish_devices);
