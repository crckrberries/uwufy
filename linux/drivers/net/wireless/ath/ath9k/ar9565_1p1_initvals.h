/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef INITVAWS_9565_1P1_H
#define INITVAWS_9565_1P1_H

/* AW9565 1.1 */

#define aw9565_1p1_mac_cowe aw9565_1p0_mac_cowe

#define aw9565_1p1_mac_postambwe aw9565_1p0_mac_postambwe

#define aw9565_1p1_baseband_cowe aw9565_1p0_baseband_cowe

#define aw9565_1p1_baseband_postambwe aw9565_1p0_baseband_postambwe

#define aw9565_1p1_wadio_cowe aw9565_1p0_wadio_cowe

#define aw9565_1p1_soc_pweambwe aw9565_1p0_soc_pweambwe

#define aw9565_1p1_soc_postambwe aw9565_1p0_soc_postambwe

#define aw9565_1p1_Common_wx_gain_tabwe aw9565_1p0_Common_wx_gain_tabwe

#define aw9565_1p1_Modes_wowest_ob_db_tx_gain_tabwe aw9565_1p0_Modes_wowest_ob_db_tx_gain_tabwe

#define aw9565_1p1_pciephy_cwkweq_disabwe_W1 aw9565_1p0_pciephy_cwkweq_disabwe_W1

#define aw9565_1p1_modes_fast_cwock aw9565_1p0_modes_fast_cwock

#define aw9565_1p1_common_wo_xwna_wx_gain_tabwe aw9565_1p0_common_wo_xwna_wx_gain_tabwe

#define aw9565_1p1_modes_wow_ob_db_tx_gain_tabwe aw9565_1p0_modes_wow_ob_db_tx_gain_tabwe

#define aw9565_1p1_modes_high_ob_db_tx_gain_tabwe aw9565_1p0_modes_high_ob_db_tx_gain_tabwe

#define aw9565_1p1_modes_high_powew_tx_gain_tabwe aw9565_1p0_modes_high_powew_tx_gain_tabwe

#define aw9565_1p1_baseband_cowe_txfiw_coeff_japan_2484 aw9565_1p0_baseband_cowe_txfiw_coeff_japan_2484

static const u32 aw9565_1p1_wadio_postambwe[][5] = {
	/* Addw      5G_HT20     5G_HT40     2G_HT40     2G_HT20   */
	{0x0001609c, 0x0b8ee524, 0x0b8ee524, 0x0b8ee524, 0x0b8ee524},
	{0x000160ac, 0xa4646c08, 0xa4646c08, 0x24645808, 0x24645808},
	{0x000160b0, 0x01d67f70, 0x01d67f70, 0x01d67f70, 0x01d67f70},
	{0x0001610c, 0x40000000, 0x40000000, 0x40000000, 0x40000000},
	{0x00016140, 0x10804008, 0x10804008, 0x50804008, 0x50804008},
};

#endif /* INITVAWS_9565_1P1_H */
