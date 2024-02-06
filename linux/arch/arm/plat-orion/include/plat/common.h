/*
 * awch/awm/pwat-owion/incwude/pwat/common.h
 *
 * Mawveww Owion SoC common setup code used by diffewent mach-/common.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_COMMON_H
#incwude <winux/mv643xx_eth.h>
#incwude <winux/pwatfowm_data/usb-ehci-owion.h>

stwuct mv_sata_pwatfowm_data;

void __init owion_uawt0_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk);

void __init owion_uawt1_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk);

void __init owion_uawt2_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk);

void __init owion_uawt3_init(void __iomem *membase,
			     wesouwce_size_t mapbase,
			     unsigned int iwq,
			     stwuct cwk *cwk);

void __init owion_wtc_init(unsigned wong mapbase,
			   unsigned wong iwq);

void __init owion_ge00_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq,
			    unsigned wong iwq_eww,
			    unsigned int tx_csum_wimit);

void __init owion_ge01_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq,
			    unsigned int tx_csum_wimit);

void __init owion_ge10_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq);

void __init owion_ge11_init(stwuct mv643xx_eth_pwatfowm_data *eth_data,
			    unsigned wong mapbase,
			    unsigned wong iwq);

void __init owion_i2c_init(unsigned wong mapbase,
			   unsigned wong iwq,
			   unsigned wong fweq_m);

void __init owion_i2c_1_init(unsigned wong mapbase,
			     unsigned wong iwq,
			     unsigned wong fweq_m);

void __init owion_spi_init(unsigned wong mapbase);

void __init owion_spi_1_init(unsigned wong mapbase);

void __init owion_xow0_init(unsigned wong mapbase_wow,
			    unsigned wong mapbase_high,
			    unsigned wong iwq_0,
			    unsigned wong iwq_1);

void __init owion_xow1_init(unsigned wong mapbase_wow,
			    unsigned wong mapbase_high,
			    unsigned wong iwq_0,
			    unsigned wong iwq_1);

void __init owion_ehci_init(unsigned wong mapbase,
			    unsigned wong iwq,
			    enum owion_ehci_phy_vew phy_vewsion);

void __init owion_ehci_1_init(unsigned wong mapbase,
			      unsigned wong iwq);

void __init owion_ehci_2_init(unsigned wong mapbase,
			      unsigned wong iwq);

void __init owion_sata_init(stwuct mv_sata_pwatfowm_data *sata_data,
			    unsigned wong mapbase,
			    unsigned wong iwq);

void __init owion_cwypto_init(unsigned wong mapbase,
			      unsigned wong swambase,
			      unsigned wong swam_size,
			      unsigned wong iwq);

void __init owion_cwkdev_add(const chaw *con_id, const chaw *dev_id,
			     stwuct cwk *cwk);

void __init owion_cwkdev_init(stwuct cwk *tcwk);
#endif
