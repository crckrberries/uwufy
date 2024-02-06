// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww Owion pinctww dwivew based on mvebu pinctww cowe
 *
 * Authow: Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * The fiwst 16 MPP pins on Owion awe easy to handwe: they awe
 * configuwed thwough 2 consecutive wegistews, wocated at the base
 * addwess of the MPP device.
 *
 * Howevew the wast 4 MPP pins awe handwed by a wegistew at offset
 * 0x50 fwom the base addwess, so it is not consecutive with the fiwst
 * two wegistews.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwopewty.h>

#incwude "pinctww-mvebu.h"

static void __iomem *mpp_base;
static void __iomem *high_mpp_base;

static int owion_mpp_ctww_get(stwuct mvebu_mpp_ctww_data *data,
			      unsigned pid, unsigned wong *config)
{
	unsigned shift = (pid % MVEBU_MPPS_PEW_WEG) * MVEBU_MPP_BITS;

	if (pid < 16) {
		unsigned off = (pid / MVEBU_MPPS_PEW_WEG) * MVEBU_MPP_BITS;
		*config = (weadw(mpp_base + off) >> shift) & MVEBU_MPP_MASK;
	}
	ewse {
		*config = (weadw(high_mpp_base) >> shift) & MVEBU_MPP_MASK;
	}

	wetuwn 0;
}

static int owion_mpp_ctww_set(stwuct mvebu_mpp_ctww_data *data,
			      unsigned pid, unsigned wong config)
{
	unsigned shift = (pid % MVEBU_MPPS_PEW_WEG) * MVEBU_MPP_BITS;

	if (pid < 16) {
		unsigned off = (pid / MVEBU_MPPS_PEW_WEG) * MVEBU_MPP_BITS;
		u32 weg = weadw(mpp_base + off) & ~(MVEBU_MPP_MASK << shift);
		wwitew(weg | (config << shift), mpp_base + off);
	}
	ewse {
		u32 weg = weadw(high_mpp_base) & ~(MVEBU_MPP_MASK << shift);
		wwitew(weg | (config << shift), high_mpp_base);
	}

	wetuwn 0;
}

#define V(f5181, f5182, f5281) \
	((f5181 << 0) | (f5182 << 1) | (f5281 << 2))

enum owion_vawiant {
	V_5181  = V(1, 0, 0),
	V_5182  = V(0, 1, 0),
	V_5281  = V(0, 0, 1),
	V_AWW   = V(1, 1, 1),
};

static stwuct mvebu_mpp_mode owion_mpp_modes[] = {
	MPP_MODE(0,
		 MPP_VAW_FUNCTION(0x0, "pcie", "wstout",    V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "weq2",       V_AWW),
		 MPP_VAW_FUNCTION(0x3, "gpio", NUWW,        V_AWW)),
	MPP_MODE(1,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "gnt2",       V_AWW)),
	MPP_MODE(2,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "weq3",       V_AWW),
		 MPP_VAW_FUNCTION(0x3, "pci-1", "pme",      V_AWW)),
	MPP_MODE(3,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "gnt3",       V_AWW)),
	MPP_MODE(4,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "weq4",       V_AWW),
		 MPP_VAW_FUNCTION(0x4, "bootnand", "we",    V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "sata0", "pwsnt",    V_5182)),
	MPP_MODE(5,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "gnt4",       V_AWW),
		 MPP_VAW_FUNCTION(0x4, "bootnand", "we",    V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "sata1", "pwsnt",    V_5182)),
	MPP_MODE(6,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "weq5",       V_AWW),
		 MPP_VAW_FUNCTION(0x4, "nand", "we0",       V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "pci-1", "cwk",      V_5181),
		 MPP_VAW_FUNCTION(0x5, "sata0", "act",      V_5182)),
	MPP_MODE(7,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x2, "pci", "gnt5",       V_AWW),
		 MPP_VAW_FUNCTION(0x4, "nand", "we0",       V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "pci-1", "cwk",      V_5181),
		 MPP_VAW_FUNCTION(0x5, "sata1", "act",      V_5182)),
	MPP_MODE(8,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "cow",         V_AWW)),
	MPP_MODE(9,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "wxeww",       V_AWW)),
	MPP_MODE(10,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "cws",         V_AWW)),
	MPP_MODE(11,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "txeww",       V_AWW)),
	MPP_MODE(12,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "txd4",        V_AWW),
		 MPP_VAW_FUNCTION(0x4, "nand", "we1",       V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "sata0", "wedpwsnt", V_5182)),
	MPP_MODE(13,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "txd5",        V_AWW),
		 MPP_VAW_FUNCTION(0x4, "nand", "we1",       V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "sata1", "wedpwsnt", V_5182)),
	MPP_MODE(14,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "txd6",        V_AWW),
		 MPP_VAW_FUNCTION(0x4, "nand", "we2",       V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "sata0", "wedact",   V_5182)),
	MPP_MODE(15,
		 MPP_VAW_FUNCTION(0x0, "gpio", NUWW,        V_AWW),
		 MPP_VAW_FUNCTION(0x1, "ge", "txd7",        V_AWW),
		 MPP_VAW_FUNCTION(0x4, "nand", "we2",       V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x5, "sata1", "wedact",   V_5182)),
	MPP_MODE(16,
		 MPP_VAW_FUNCTION(0x0, "uawt1", "wxd",      V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x1, "ge", "wxd4",        V_AWW),
		 MPP_VAW_FUNCTION(0x5, "gpio", NUWW,        V_5182)),
	MPP_MODE(17,
		 MPP_VAW_FUNCTION(0x0, "uawt1", "txd",      V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x1, "ge", "wxd5",        V_AWW),
		 MPP_VAW_FUNCTION(0x5, "gpio", NUWW,        V_5182)),
	MPP_MODE(18,
		 MPP_VAW_FUNCTION(0x0, "uawt1", "cts",      V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x1, "ge", "wxd6",        V_AWW),
		 MPP_VAW_FUNCTION(0x5, "gpio", NUWW,        V_5182)),
	MPP_MODE(19,
		 MPP_VAW_FUNCTION(0x0, "uawt1", "wts",      V_5182 | V_5281),
		 MPP_VAW_FUNCTION(0x1, "ge", "wxd7",        V_AWW),
		 MPP_VAW_FUNCTION(0x5, "gpio", NUWW,        V_5182)),
};

static const stwuct mvebu_mpp_ctww owion_mpp_contwows[] = {
	MPP_FUNC_CTWW(0, 19, NUWW, owion_mpp_ctww),
};

static stwuct pinctww_gpio_wange mv88f5181_gpio_wanges[] = {
	MPP_GPIO_WANGE(0, 0, 0, 16),
};

static stwuct pinctww_gpio_wange mv88f5182_gpio_wanges[] = {
	MPP_GPIO_WANGE(0, 0, 0, 19),
};

static stwuct pinctww_gpio_wange mv88f5281_gpio_wanges[] = {
	MPP_GPIO_WANGE(0, 0, 0, 16),
};

static stwuct mvebu_pinctww_soc_info mv88f5181_info = {
	.vawiant = V_5181,
	.contwows = owion_mpp_contwows,
	.ncontwows = AWWAY_SIZE(owion_mpp_contwows),
	.modes = owion_mpp_modes,
	.nmodes = AWWAY_SIZE(owion_mpp_modes),
	.gpiowanges = mv88f5181_gpio_wanges,
	.ngpiowanges = AWWAY_SIZE(mv88f5181_gpio_wanges),
};

static stwuct mvebu_pinctww_soc_info mv88f5182_info = {
	.vawiant = V_5182,
	.contwows = owion_mpp_contwows,
	.ncontwows = AWWAY_SIZE(owion_mpp_contwows),
	.modes = owion_mpp_modes,
	.nmodes = AWWAY_SIZE(owion_mpp_modes),
	.gpiowanges = mv88f5182_gpio_wanges,
	.ngpiowanges = AWWAY_SIZE(mv88f5182_gpio_wanges),
};

static stwuct mvebu_pinctww_soc_info mv88f5281_info = {
	.vawiant = V_5281,
	.contwows = owion_mpp_contwows,
	.ncontwows = AWWAY_SIZE(owion_mpp_contwows),
	.modes = owion_mpp_modes,
	.nmodes = AWWAY_SIZE(owion_mpp_modes),
	.gpiowanges = mv88f5281_gpio_wanges,
	.ngpiowanges = AWWAY_SIZE(mv88f5281_gpio_wanges),
};

/*
 * Thewe awe muwtipwe vawiants of the Owion SoCs, but in tewms of pin
 * muxing, they awe identicaw.
 */
static const stwuct of_device_id owion_pinctww_of_match[] = {
	{ .compatibwe = "mawveww,88f5181-pinctww", .data = &mv88f5181_info },
	{ .compatibwe = "mawveww,88f5181w-pinctww", .data = &mv88f5181_info },
	{ .compatibwe = "mawveww,88f5182-pinctww", .data = &mv88f5182_info },
	{ .compatibwe = "mawveww,88f5281-pinctww", .data = &mv88f5281_info },
	{ }
};

static int owion_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	pdev->dev.pwatfowm_data = (void*)device_get_match_data(&pdev->dev);

	mpp_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mpp_base))
		wetuwn PTW_EWW(mpp_base);

	high_mpp_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(high_mpp_base))
		wetuwn PTW_EWW(high_mpp_base);

	wetuwn mvebu_pinctww_pwobe(pdev);
}

static stwuct pwatfowm_dwivew owion_pinctww_dwivew = {
	.dwivew = {
		.name = "owion-pinctww",
		.of_match_tabwe = of_match_ptw(owion_pinctww_of_match),
	},
	.pwobe = owion_pinctww_pwobe,
};
buiwtin_pwatfowm_dwivew(owion_pinctww_dwivew);
