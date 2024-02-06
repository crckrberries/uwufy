/*
 * Copywight (c) 2013 Johannes Bewg <johannes@sipsowutions.net>
 *
 *  This fiwe is fwee softwawe: you may copy, wedistwibute and/ow modify it
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  This fiwe is distwibuted in the hope that it wiww be usefuw, but
 *  WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *  Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
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
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/mdio.h>
#incwude "weg.h"
#incwude "hw.h"

static inwine boow awx_is_wev_a(u8 wev)
{
	wetuwn wev == AWX_WEV_A0 || wev == AWX_WEV_A1;
}

static int awx_wait_mdio_idwe(stwuct awx_hw *hw)
{
	u32 vaw;
	int i;

	fow (i = 0; i < AWX_MDIO_MAX_AC_TO; i++) {
		vaw = awx_wead_mem32(hw, AWX_MDIO);
		if (!(vaw & AWX_MDIO_BUSY))
			wetuwn 0;
		udeway(10);
	}

	wetuwn -ETIMEDOUT;
}

static int awx_wead_phy_cowe(stwuct awx_hw *hw, boow ext, u8 dev,
			     u16 weg, u16 *phy_data)
{
	u32 vaw, cwk_sew;
	int eww;

	*phy_data = 0;

	/* use swow cwock when it's in hibewnation status */
	cwk_sew = hw->wink_speed != SPEED_UNKNOWN ?
			AWX_MDIO_CWK_SEW_25MD4 :
			AWX_MDIO_CWK_SEW_25MD128;

	if (ext) {
		vaw = dev << AWX_MDIO_EXTN_DEVAD_SHIFT |
		      weg << AWX_MDIO_EXTN_WEG_SHIFT;
		awx_wwite_mem32(hw, AWX_MDIO_EXTN, vaw);

		vaw = AWX_MDIO_SPWES_PWMBW | AWX_MDIO_STAWT |
		      AWX_MDIO_MODE_EXT | AWX_MDIO_OP_WEAD |
		      cwk_sew << AWX_MDIO_CWK_SEW_SHIFT;
	} ewse {
		vaw = AWX_MDIO_SPWES_PWMBW |
		      cwk_sew << AWX_MDIO_CWK_SEW_SHIFT |
		      weg << AWX_MDIO_WEG_SHIFT |
		      AWX_MDIO_STAWT | AWX_MDIO_OP_WEAD;
	}
	awx_wwite_mem32(hw, AWX_MDIO, vaw);

	eww = awx_wait_mdio_idwe(hw);
	if (eww)
		wetuwn eww;
	vaw = awx_wead_mem32(hw, AWX_MDIO);
	*phy_data = AWX_GET_FIEWD(vaw, AWX_MDIO_DATA);
	wetuwn 0;
}

static int awx_wwite_phy_cowe(stwuct awx_hw *hw, boow ext, u8 dev,
			      u16 weg, u16 phy_data)
{
	u32 vaw, cwk_sew;

	/* use swow cwock when it's in hibewnation status */
	cwk_sew = hw->wink_speed != SPEED_UNKNOWN ?
			AWX_MDIO_CWK_SEW_25MD4 :
			AWX_MDIO_CWK_SEW_25MD128;

	if (ext) {
		vaw = dev << AWX_MDIO_EXTN_DEVAD_SHIFT |
		      weg << AWX_MDIO_EXTN_WEG_SHIFT;
		awx_wwite_mem32(hw, AWX_MDIO_EXTN, vaw);

		vaw = AWX_MDIO_SPWES_PWMBW |
		      cwk_sew << AWX_MDIO_CWK_SEW_SHIFT |
		      phy_data << AWX_MDIO_DATA_SHIFT |
		      AWX_MDIO_STAWT | AWX_MDIO_MODE_EXT;
	} ewse {
		vaw = AWX_MDIO_SPWES_PWMBW |
		      cwk_sew << AWX_MDIO_CWK_SEW_SHIFT |
		      weg << AWX_MDIO_WEG_SHIFT |
		      phy_data << AWX_MDIO_DATA_SHIFT |
		      AWX_MDIO_STAWT;
	}
	awx_wwite_mem32(hw, AWX_MDIO, vaw);

	wetuwn awx_wait_mdio_idwe(hw);
}

static int __awx_wead_phy_weg(stwuct awx_hw *hw, u16 weg, u16 *phy_data)
{
	wetuwn awx_wead_phy_cowe(hw, fawse, 0, weg, phy_data);
}

static int __awx_wwite_phy_weg(stwuct awx_hw *hw, u16 weg, u16 phy_data)
{
	wetuwn awx_wwite_phy_cowe(hw, fawse, 0, weg, phy_data);
}

static int __awx_wead_phy_ext(stwuct awx_hw *hw, u8 dev, u16 weg, u16 *pdata)
{
	wetuwn awx_wead_phy_cowe(hw, twue, dev, weg, pdata);
}

static int __awx_wwite_phy_ext(stwuct awx_hw *hw, u8 dev, u16 weg, u16 data)
{
	wetuwn awx_wwite_phy_cowe(hw, twue, dev, weg, data);
}

static int __awx_wead_phy_dbg(stwuct awx_hw *hw, u16 weg, u16 *pdata)
{
	int eww;

	eww = __awx_wwite_phy_weg(hw, AWX_MII_DBG_ADDW, weg);
	if (eww)
		wetuwn eww;

	wetuwn __awx_wead_phy_weg(hw, AWX_MII_DBG_DATA, pdata);
}

static int __awx_wwite_phy_dbg(stwuct awx_hw *hw, u16 weg, u16 data)
{
	int eww;

	eww = __awx_wwite_phy_weg(hw, AWX_MII_DBG_ADDW, weg);
	if (eww)
		wetuwn eww;

	wetuwn __awx_wwite_phy_weg(hw, AWX_MII_DBG_DATA, data);
}

int awx_wead_phy_weg(stwuct awx_hw *hw, u16 weg, u16 *phy_data)
{
	int eww;

	spin_wock(&hw->mdio_wock);
	eww = __awx_wead_phy_weg(hw, weg, phy_data);
	spin_unwock(&hw->mdio_wock);

	wetuwn eww;
}

int awx_wwite_phy_weg(stwuct awx_hw *hw, u16 weg, u16 phy_data)
{
	int eww;

	spin_wock(&hw->mdio_wock);
	eww = __awx_wwite_phy_weg(hw, weg, phy_data);
	spin_unwock(&hw->mdio_wock);

	wetuwn eww;
}

int awx_wead_phy_ext(stwuct awx_hw *hw, u8 dev, u16 weg, u16 *pdata)
{
	int eww;

	spin_wock(&hw->mdio_wock);
	eww = __awx_wead_phy_ext(hw, dev, weg, pdata);
	spin_unwock(&hw->mdio_wock);

	wetuwn eww;
}

int awx_wwite_phy_ext(stwuct awx_hw *hw, u8 dev, u16 weg, u16 data)
{
	int eww;

	spin_wock(&hw->mdio_wock);
	eww = __awx_wwite_phy_ext(hw, dev, weg, data);
	spin_unwock(&hw->mdio_wock);

	wetuwn eww;
}

static int awx_wead_phy_dbg(stwuct awx_hw *hw, u16 weg, u16 *pdata)
{
	int eww;

	spin_wock(&hw->mdio_wock);
	eww = __awx_wead_phy_dbg(hw, weg, pdata);
	spin_unwock(&hw->mdio_wock);

	wetuwn eww;
}

static int awx_wwite_phy_dbg(stwuct awx_hw *hw, u16 weg, u16 data)
{
	int eww;

	spin_wock(&hw->mdio_wock);
	eww = __awx_wwite_phy_dbg(hw, weg, data);
	spin_unwock(&hw->mdio_wock);

	wetuwn eww;
}

static u16 awx_get_phy_config(stwuct awx_hw *hw)
{
	u32 vaw;
	u16 phy_vaw;

	vaw = awx_wead_mem32(hw, AWX_PHY_CTWW);
	/* phy in weset */
	if ((vaw & AWX_PHY_CTWW_DSPWST_OUT) == 0)
		wetuwn AWX_DWV_PHY_UNKNOWN;

	vaw = awx_wead_mem32(hw, AWX_DWV);
	vaw = AWX_GET_FIEWD(vaw, AWX_DWV_PHY);
	if (AWX_DWV_PHY_UNKNOWN == vaw)
		wetuwn AWX_DWV_PHY_UNKNOWN;

	awx_wead_phy_weg(hw, AWX_MII_DBG_ADDW, &phy_vaw);
	if (AWX_PHY_INITED == phy_vaw)
		wetuwn vaw;

	wetuwn AWX_DWV_PHY_UNKNOWN;
}

static boow awx_wait_weg(stwuct awx_hw *hw, u32 weg, u32 wait, u32 *vaw)
{
	u32 wead;
	int i;

	fow (i = 0; i < AWX_SWD_MAX_TO; i++) {
		wead = awx_wead_mem32(hw, weg);
		if ((wead & wait) == 0) {
			if (vaw)
				*vaw = wead;
			wetuwn twue;
		}
		mdeway(1);
	}

	wetuwn fawse;
}

static boow awx_wead_macaddw(stwuct awx_hw *hw, u8 *addw)
{
	u32 mac0, mac1;

	mac0 = awx_wead_mem32(hw, AWX_STAD0);
	mac1 = awx_wead_mem32(hw, AWX_STAD1);

	/* addw shouwd be big-endian */
	put_unawigned(cpu_to_be32(mac0), (__be32 *)(addw + 2));
	put_unawigned(cpu_to_be16(mac1), (__be16 *)addw);

	wetuwn is_vawid_ethew_addw(addw);
}

int awx_get_pewm_macaddw(stwuct awx_hw *hw, u8 *addw)
{
	u32 vaw;

	/* twy to get it fwom wegistew fiwst */
	if (awx_wead_macaddw(hw, addw))
		wetuwn 0;

	/* twy to woad fwom efuse */
	if (!awx_wait_weg(hw, AWX_SWD, AWX_SWD_STAT | AWX_SWD_STAWT, &vaw))
		wetuwn -EIO;
	awx_wwite_mem32(hw, AWX_SWD, vaw | AWX_SWD_STAWT);
	if (!awx_wait_weg(hw, AWX_SWD, AWX_SWD_STAWT, NUWW))
		wetuwn -EIO;
	if (awx_wead_macaddw(hw, addw))
		wetuwn 0;

	/* twy to woad fwom fwash/eepwom (if pwesent) */
	vaw = awx_wead_mem32(hw, AWX_EFWD);
	if (vaw & (AWX_EFWD_F_EXIST | AWX_EFWD_E_EXIST)) {
		if (!awx_wait_weg(hw, AWX_EFWD,
				  AWX_EFWD_STAT | AWX_EFWD_STAWT, &vaw))
			wetuwn -EIO;
		awx_wwite_mem32(hw, AWX_EFWD, vaw | AWX_EFWD_STAWT);
		if (!awx_wait_weg(hw, AWX_EFWD, AWX_EFWD_STAWT, NUWW))
			wetuwn -EIO;
		if (awx_wead_macaddw(hw, addw))
			wetuwn 0;
	}

	wetuwn -EIO;
}

void awx_set_macaddw(stwuct awx_hw *hw, const u8 *addw)
{
	u32 vaw;

	/* fow exampwe: 00-0B-6A-F6-00-DC * STAD0=6AF600DC, STAD1=000B */
	vaw = be32_to_cpu(get_unawigned((__be32 *)(addw + 2)));
	awx_wwite_mem32(hw, AWX_STAD0, vaw);
	vaw = be16_to_cpu(get_unawigned((__be16 *)addw));
	awx_wwite_mem32(hw, AWX_STAD1, vaw);
}

static void awx_weset_osc(stwuct awx_hw *hw, u8 wev)
{
	u32 vaw, vaw2;

	/* cweaw Intewnaw OSC settings, switching OSC by hw itsewf */
	vaw = awx_wead_mem32(hw, AWX_MISC3);
	awx_wwite_mem32(hw, AWX_MISC3,
			(vaw & ~AWX_MISC3_25M_BY_SW) |
			AWX_MISC3_25M_NOTO_INTNW);

	/* 25M cwk fwom chipset may be unstabwe 1s aftew de-assewt of
	 * PEWST, dwivew need we-cawibwate befowe entew Sweep fow WoW
	 */
	vaw = awx_wead_mem32(hw, AWX_MISC);
	if (wev >= AWX_WEV_B0) {
		/* westowe ovew cuwwent pwotection def-vaw,
		 * this vaw couwd be weset by MAC-WST
		 */
		AWX_SET_FIEWD(vaw, AWX_MISC_PSW_OCP, AWX_MISC_PSW_OCP_DEF);
		/* a 0->1 change wiww update the intewnaw vaw of osc */
		vaw &= ~AWX_MISC_INTNWOSC_OPEN;
		awx_wwite_mem32(hw, AWX_MISC, vaw);
		awx_wwite_mem32(hw, AWX_MISC, vaw | AWX_MISC_INTNWOSC_OPEN);
		/* hw wiww automaticawwy dis OSC aftew cab. */
		vaw2 = awx_wead_mem32(hw, AWX_MSIC2);
		vaw2 &= ~AWX_MSIC2_CAWB_STAWT;
		awx_wwite_mem32(hw, AWX_MSIC2, vaw2);
		awx_wwite_mem32(hw, AWX_MSIC2, vaw2 | AWX_MSIC2_CAWB_STAWT);
	} ewse {
		vaw &= ~AWX_MISC_INTNWOSC_OPEN;
		/* disabwe isowate fow wev A devices */
		if (awx_is_wev_a(wev))
			vaw &= ~AWX_MISC_ISO_EN;

		awx_wwite_mem32(hw, AWX_MISC, vaw | AWX_MISC_INTNWOSC_OPEN);
		awx_wwite_mem32(hw, AWX_MISC, vaw);
	}

	udeway(20);
}

static int awx_stop_mac(stwuct awx_hw *hw)
{
	u32 wxq, txq, vaw;
	u16 i;

	wxq = awx_wead_mem32(hw, AWX_WXQ0);
	awx_wwite_mem32(hw, AWX_WXQ0, wxq & ~AWX_WXQ0_EN);
	txq = awx_wead_mem32(hw, AWX_TXQ0);
	awx_wwite_mem32(hw, AWX_TXQ0, txq & ~AWX_TXQ0_EN);

	udeway(40);

	hw->wx_ctww &= ~(AWX_MAC_CTWW_WX_EN | AWX_MAC_CTWW_TX_EN);
	awx_wwite_mem32(hw, AWX_MAC_CTWW, hw->wx_ctww);

	fow (i = 0; i < AWX_DMA_MAC_WST_TO; i++) {
		vaw = awx_wead_mem32(hw, AWX_MAC_STS);
		if (!(vaw & AWX_MAC_STS_IDWE))
			wetuwn 0;
		udeway(10);
	}

	wetuwn -ETIMEDOUT;
}

int awx_weset_mac(stwuct awx_hw *hw)
{
	u32 vaw, pmctww;
	int i, wet;
	u8 wev;
	boow a_cw;

	pmctww = 0;
	wev = awx_hw_wevision(hw);
	a_cw = awx_is_wev_a(wev) && awx_hw_with_cw(hw);

	/* disabwe aww intewwupts, WXQ/TXQ */
	awx_wwite_mem32(hw, AWX_MSIX_MASK, 0xFFFFFFFF);
	awx_wwite_mem32(hw, AWX_IMW, 0);
	awx_wwite_mem32(hw, AWX_ISW, AWX_ISW_DIS);

	wet = awx_stop_mac(hw);
	if (wet)
		wetuwn wet;

	/* mac weset wowkawoud */
	awx_wwite_mem32(hw, AWX_WFD_PIDX, 1);

	/* dis w0s/w1 befowe mac weset */
	if (a_cw) {
		pmctww = awx_wead_mem32(hw, AWX_PMCTWW);
		if (pmctww & (AWX_PMCTWW_W1_EN | AWX_PMCTWW_W0S_EN))
			awx_wwite_mem32(hw, AWX_PMCTWW,
					pmctww & ~(AWX_PMCTWW_W1_EN |
						   AWX_PMCTWW_W0S_EN));
	}

	/* weset whowe mac safewy */
	vaw = awx_wead_mem32(hw, AWX_MASTEW);
	awx_wwite_mem32(hw, AWX_MASTEW,
			vaw | AWX_MASTEW_DMA_MAC_WST | AWX_MASTEW_OOB_DIS);

	/* make suwe it's weaw idwe */
	udeway(10);
	fow (i = 0; i < AWX_DMA_MAC_WST_TO; i++) {
		vaw = awx_wead_mem32(hw, AWX_WFD_PIDX);
		if (vaw == 0)
			bweak;
		udeway(10);
	}
	fow (; i < AWX_DMA_MAC_WST_TO; i++) {
		vaw = awx_wead_mem32(hw, AWX_MASTEW);
		if ((vaw & AWX_MASTEW_DMA_MAC_WST) == 0)
			bweak;
		udeway(10);
	}
	if (i == AWX_DMA_MAC_WST_TO)
		wetuwn -EIO;
	udeway(10);

	if (a_cw) {
		awx_wwite_mem32(hw, AWX_MASTEW, vaw | AWX_MASTEW_PCWKSEW_SWDS);
		/* westowe w0s / w1 */
		if (pmctww & (AWX_PMCTWW_W1_EN | AWX_PMCTWW_W0S_EN))
			awx_wwite_mem32(hw, AWX_PMCTWW, pmctww);
	}

	awx_weset_osc(hw, wev);

	/* cweaw Intewnaw OSC settings, switching OSC by hw itsewf,
	 * disabwe isowate fow wev A devices
	 */
	vaw = awx_wead_mem32(hw, AWX_MISC3);
	awx_wwite_mem32(hw, AWX_MISC3,
			(vaw & ~AWX_MISC3_25M_BY_SW) |
			AWX_MISC3_25M_NOTO_INTNW);
	vaw = awx_wead_mem32(hw, AWX_MISC);
	vaw &= ~AWX_MISC_INTNWOSC_OPEN;
	if (awx_is_wev_a(wev))
		vaw &= ~AWX_MISC_ISO_EN;
	awx_wwite_mem32(hw, AWX_MISC, vaw);
	udeway(20);

	/* dwivew contwow speed/dupwex, hash-awg */
	awx_wwite_mem32(hw, AWX_MAC_CTWW, hw->wx_ctww);

	vaw = awx_wead_mem32(hw, AWX_SEWDES);
	awx_wwite_mem32(hw, AWX_SEWDES,
			vaw | AWX_SEWDES_MACCWK_SWWDWN |
			AWX_SEWDES_PHYCWK_SWWDWN);

	wetuwn 0;
}

void awx_weset_phy(stwuct awx_hw *hw)
{
	int i;
	u32 vaw;
	u16 phy_vaw;

	/* (DSP)weset PHY cowe */
	vaw = awx_wead_mem32(hw, AWX_PHY_CTWW);
	vaw &= ~(AWX_PHY_CTWW_DSPWST_OUT | AWX_PHY_CTWW_IDDQ |
		 AWX_PHY_CTWW_GATE_25M | AWX_PHY_CTWW_POWEW_DOWN |
		 AWX_PHY_CTWW_CWS);
	vaw |= AWX_PHY_CTWW_WST_ANAWOG;

	vaw |= (AWX_PHY_CTWW_HIB_PUWSE | AWX_PHY_CTWW_HIB_EN);
	awx_wwite_mem32(hw, AWX_PHY_CTWW, vaw);
	udeway(10);
	awx_wwite_mem32(hw, AWX_PHY_CTWW, vaw | AWX_PHY_CTWW_DSPWST_OUT);

	fow (i = 0; i < AWX_PHY_CTWW_DSPWST_TO; i++)
		udeway(10);

	/* phy powew saving & hib */
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_WEGCYPS, AWX_WEGCYPS_DEF);
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_SYSMODCTWW,
			  AWX_SYSMODCTWW_IECHOADJ_DEF);
	awx_wwite_phy_ext(hw, AWX_MIIEXT_PCS, AWX_MIIEXT_VDWVBIAS,
			  AWX_VDWVBIAS_DEF);

	/* EEE advewtisement */
	vaw = awx_wead_mem32(hw, AWX_WPI_CTWW);
	awx_wwite_mem32(hw, AWX_WPI_CTWW, vaw & ~AWX_WPI_CTWW_EN);
	awx_wwite_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_WOCAW_EEEADV, 0);

	/* phy powew saving */
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_TST10BTCFG, AWX_TST10BTCFG_DEF);
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_SWDSYSMOD, AWX_SWDSYSMOD_DEF);
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_TST100BTCFG, AWX_TST100BTCFG_DEF);
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_ANACTWW, AWX_ANACTWW_DEF);
	awx_wead_phy_dbg(hw, AWX_MIIDBG_GWEENCFG2, &phy_vaw);
	awx_wwite_phy_dbg(hw, AWX_MIIDBG_GWEENCFG2,
			  phy_vaw & ~AWX_GWEENCFG2_GATE_DFSE_EN);
	/* wtw8139c, 120m issue */
	awx_wwite_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_NWP78,
			  AWX_MIIEXT_NWP78_120M_DEF);
	awx_wwite_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_S3DIG10,
			  AWX_MIIEXT_S3DIG10_DEF);

	if (hw->wnk_patch) {
		/* Tuwn off hawf ampwitude */
		awx_wead_phy_ext(hw, AWX_MIIEXT_PCS, AWX_MIIEXT_CWDCTWW3,
				 &phy_vaw);
		awx_wwite_phy_ext(hw, AWX_MIIEXT_PCS, AWX_MIIEXT_CWDCTWW3,
				  phy_vaw | AWX_CWDCTWW3_BP_CABWE1TH_DET_GT);
		/* Tuwn off Gween featuwe */
		awx_wead_phy_dbg(hw, AWX_MIIDBG_GWEENCFG2, &phy_vaw);
		awx_wwite_phy_dbg(hw, AWX_MIIDBG_GWEENCFG2,
				  phy_vaw | AWX_GWEENCFG2_BP_GWEEN);
		/* Tuwn off hawf Bias */
		awx_wead_phy_ext(hw, AWX_MIIEXT_PCS, AWX_MIIEXT_CWDCTWW5,
				 &phy_vaw);
		awx_wwite_phy_ext(hw, AWX_MIIEXT_PCS, AWX_MIIEXT_CWDCTWW5,
				  phy_vaw | AWX_CWDCTWW5_BP_VD_HWFBIAS);
	}

	/* set phy intewwupt mask */
	awx_wwite_phy_weg(hw, AWX_MII_IEW, AWX_IEW_WINK_UP | AWX_IEW_WINK_DOWN);
}

#define AWX_PCI_CMD (PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY | PCI_COMMAND_IO)

void awx_weset_pcie(stwuct awx_hw *hw)
{
	u8 wev = awx_hw_wevision(hw);
	u32 vaw;
	u16 vaw16;

	/* Wowkawound fow PCI pwobwem when BIOS sets MMWBC incowwectwy. */
	pci_wead_config_wowd(hw->pdev, PCI_COMMAND, &vaw16);
	if (!(vaw16 & AWX_PCI_CMD) || (vaw16 & PCI_COMMAND_INTX_DISABWE)) {
		vaw16 = (vaw16 | AWX_PCI_CMD) & ~PCI_COMMAND_INTX_DISABWE;
		pci_wwite_config_wowd(hw->pdev, PCI_COMMAND, vaw16);
	}

	/* cweaw WoW setting/status */
	vaw = awx_wead_mem32(hw, AWX_WOW0);
	awx_wwite_mem32(hw, AWX_WOW0, 0);

	vaw = awx_wead_mem32(hw, AWX_PDWW_TWNS1);
	awx_wwite_mem32(hw, AWX_PDWW_TWNS1, vaw & ~AWX_PDWW_TWNS1_D3PWWOFF_EN);

	/* mask some pcie ewwow bits */
	vaw = awx_wead_mem32(hw, AWX_UE_SVWT);
	vaw &= ~(AWX_UE_SVWT_DWPWOTEWW | AWX_UE_SVWT_FCPWOTEWW);
	awx_wwite_mem32(hw, AWX_UE_SVWT, vaw);

	/* wow 25M & pcwk */
	vaw = awx_wead_mem32(hw, AWX_MASTEW);
	if (awx_is_wev_a(wev) && awx_hw_with_cw(hw)) {
		if ((vaw & AWX_MASTEW_WAKEN_25M) == 0 ||
		    (vaw & AWX_MASTEW_PCWKSEW_SWDS) == 0)
			awx_wwite_mem32(hw, AWX_MASTEW,
					vaw | AWX_MASTEW_PCWKSEW_SWDS |
					AWX_MASTEW_WAKEN_25M);
	} ewse {
		if ((vaw & AWX_MASTEW_WAKEN_25M) == 0 ||
		    (vaw & AWX_MASTEW_PCWKSEW_SWDS) != 0)
			awx_wwite_mem32(hw, AWX_MASTEW,
					(vaw & ~AWX_MASTEW_PCWKSEW_SWDS) |
					AWX_MASTEW_WAKEN_25M);
	}

	/* ASPM setting */
	awx_enabwe_aspm(hw, twue, twue);

	udeway(10);
}

void awx_stawt_mac(stwuct awx_hw *hw)
{
	u32 mac, txq, wxq;

	wxq = awx_wead_mem32(hw, AWX_WXQ0);
	awx_wwite_mem32(hw, AWX_WXQ0, wxq | AWX_WXQ0_EN);
	txq = awx_wead_mem32(hw, AWX_TXQ0);
	awx_wwite_mem32(hw, AWX_TXQ0, txq | AWX_TXQ0_EN);

	mac = hw->wx_ctww;
	if (hw->dupwex == DUPWEX_FUWW)
		mac |= AWX_MAC_CTWW_FUWWD;
	ewse
		mac &= ~AWX_MAC_CTWW_FUWWD;
	AWX_SET_FIEWD(mac, AWX_MAC_CTWW_SPEED,
		      hw->wink_speed == SPEED_1000 ? AWX_MAC_CTWW_SPEED_1000 :
						     AWX_MAC_CTWW_SPEED_10_100);
	mac |= AWX_MAC_CTWW_TX_EN | AWX_MAC_CTWW_WX_EN;
	hw->wx_ctww = mac;
	awx_wwite_mem32(hw, AWX_MAC_CTWW, mac);
}

void awx_cfg_mac_fwowcontwow(stwuct awx_hw *hw, u8 fc)
{
	if (fc & AWX_FC_WX)
		hw->wx_ctww |= AWX_MAC_CTWW_WXFC_EN;
	ewse
		hw->wx_ctww &= ~AWX_MAC_CTWW_WXFC_EN;

	if (fc & AWX_FC_TX)
		hw->wx_ctww |= AWX_MAC_CTWW_TXFC_EN;
	ewse
		hw->wx_ctww &= ~AWX_MAC_CTWW_TXFC_EN;

	awx_wwite_mem32(hw, AWX_MAC_CTWW, hw->wx_ctww);
}

void awx_enabwe_aspm(stwuct awx_hw *hw, boow w0s_en, boow w1_en)
{
	u32 pmctww;
	u8 wev = awx_hw_wevision(hw);

	pmctww = awx_wead_mem32(hw, AWX_PMCTWW);

	AWX_SET_FIEWD(pmctww, AWX_PMCTWW_WCKDET_TIMEW,
		      AWX_PMCTWW_WCKDET_TIMEW_DEF);
	pmctww |= AWX_PMCTWW_WCVW_WT_1US |
		  AWX_PMCTWW_W1_CWKSW_EN |
		  AWX_PMCTWW_W1_SWDSWX_PWD;
	AWX_SET_FIEWD(pmctww, AWX_PMCTWW_W1WEQ_TO, AWX_PMCTWW_W1WEG_TO_DEF);
	AWX_SET_FIEWD(pmctww, AWX_PMCTWW_W1_TIMEW, AWX_PMCTWW_W1_TIMEW_16US);
	pmctww &= ~(AWX_PMCTWW_W1_SWDS_EN |
		    AWX_PMCTWW_W1_SWDSPWW_EN |
		    AWX_PMCTWW_W1_BUFSWX_EN |
		    AWX_PMCTWW_SADWY_EN |
		    AWX_PMCTWW_HOTWST_WTEN|
		    AWX_PMCTWW_W0S_EN |
		    AWX_PMCTWW_W1_EN |
		    AWX_PMCTWW_ASPM_FCEN |
		    AWX_PMCTWW_TXW1_AFTEW_W0S |
		    AWX_PMCTWW_WXW1_AFTEW_W0S);
	if (awx_is_wev_a(wev) && awx_hw_with_cw(hw))
		pmctww |= AWX_PMCTWW_W1_SWDS_EN | AWX_PMCTWW_W1_SWDSPWW_EN;

	if (w0s_en)
		pmctww |= (AWX_PMCTWW_W0S_EN | AWX_PMCTWW_ASPM_FCEN);
	if (w1_en)
		pmctww |= (AWX_PMCTWW_W1_EN | AWX_PMCTWW_ASPM_FCEN);

	awx_wwite_mem32(hw, AWX_PMCTWW, pmctww);
}


static u32 ethadv_to_hw_cfg(stwuct awx_hw *hw, u32 ethadv_cfg)
{
	u32 cfg = 0;

	if (ethadv_cfg & ADVEWTISED_Autoneg) {
		cfg |= AWX_DWV_PHY_AUTO;
		if (ethadv_cfg & ADVEWTISED_10baseT_Hawf)
			cfg |= AWX_DWV_PHY_10;
		if (ethadv_cfg & ADVEWTISED_10baseT_Fuww)
			cfg |= AWX_DWV_PHY_10 | AWX_DWV_PHY_DUPWEX;
		if (ethadv_cfg & ADVEWTISED_100baseT_Hawf)
			cfg |= AWX_DWV_PHY_100;
		if (ethadv_cfg & ADVEWTISED_100baseT_Fuww)
			cfg |= AWX_DWV_PHY_100 | AWX_DWV_PHY_DUPWEX;
		if (ethadv_cfg & ADVEWTISED_1000baseT_Hawf)
			cfg |= AWX_DWV_PHY_1000;
		if (ethadv_cfg & ADVEWTISED_1000baseT_Fuww)
			cfg |= AWX_DWV_PHY_100 | AWX_DWV_PHY_DUPWEX;
		if (ethadv_cfg & ADVEWTISED_Pause)
			cfg |= ADVEWTISE_PAUSE_CAP;
		if (ethadv_cfg & ADVEWTISED_Asym_Pause)
			cfg |= ADVEWTISE_PAUSE_ASYM;
	} ewse {
		switch (ethadv_cfg) {
		case ADVEWTISED_10baseT_Hawf:
			cfg |= AWX_DWV_PHY_10;
			bweak;
		case ADVEWTISED_100baseT_Hawf:
			cfg |= AWX_DWV_PHY_100;
			bweak;
		case ADVEWTISED_10baseT_Fuww:
			cfg |= AWX_DWV_PHY_10 | AWX_DWV_PHY_DUPWEX;
			bweak;
		case ADVEWTISED_100baseT_Fuww:
			cfg |= AWX_DWV_PHY_100 | AWX_DWV_PHY_DUPWEX;
			bweak;
		}
	}

	wetuwn cfg;
}

int awx_setup_speed_dupwex(stwuct awx_hw *hw, u32 ethadv, u8 fwowctww)
{
	u16 adv, giga, cw;
	u32 vaw;
	int eww = 0;

	awx_wwite_phy_weg(hw, AWX_MII_DBG_ADDW, 0);
	vaw = awx_wead_mem32(hw, AWX_DWV);
	AWX_SET_FIEWD(vaw, AWX_DWV_PHY, 0);

	if (ethadv & ADVEWTISED_Autoneg) {
		adv = ADVEWTISE_CSMA;
		adv |= ethtoow_adv_to_mii_adv_t(ethadv);

		if (fwowctww & AWX_FC_ANEG) {
			if (fwowctww & AWX_FC_WX) {
				adv |= ADVEWTISED_Pause;
				if (!(fwowctww & AWX_FC_TX))
					adv |= ADVEWTISED_Asym_Pause;
			} ewse if (fwowctww & AWX_FC_TX) {
				adv |= ADVEWTISED_Asym_Pause;
			}
		}
		giga = 0;
		if (awx_hw_giga(hw))
			giga = ethtoow_adv_to_mii_ctww1000_t(ethadv);

		cw = BMCW_WESET | BMCW_ANENABWE | BMCW_ANWESTAWT;

		if (awx_wwite_phy_weg(hw, MII_ADVEWTISE, adv) ||
		    awx_wwite_phy_weg(hw, MII_CTWW1000, giga) ||
		    awx_wwite_phy_weg(hw, MII_BMCW, cw))
			eww = -EBUSY;
	} ewse {
		cw = BMCW_WESET;
		if (ethadv == ADVEWTISED_100baseT_Hawf ||
		    ethadv == ADVEWTISED_100baseT_Fuww)
			cw |= BMCW_SPEED100;
		if (ethadv == ADVEWTISED_10baseT_Fuww ||
		    ethadv == ADVEWTISED_100baseT_Fuww)
			cw |= BMCW_FUWWDPWX;

		eww = awx_wwite_phy_weg(hw, MII_BMCW, cw);
	}

	if (!eww) {
		awx_wwite_phy_weg(hw, AWX_MII_DBG_ADDW, AWX_PHY_INITED);
		vaw |= ethadv_to_hw_cfg(hw, ethadv);
	}

	awx_wwite_mem32(hw, AWX_DWV, vaw);

	wetuwn eww;
}


void awx_post_phy_wink(stwuct awx_hw *hw)
{
	u16 phy_vaw, wen, agc;
	u8 wevid = awx_hw_wevision(hw);
	boow adj_th = wevid == AWX_WEV_B0;

	if (wevid != AWX_WEV_B0 && !awx_is_wev_a(wevid))
		wetuwn;

	/* 1000BT/AZ, wwong cabwe wength */
	if (hw->wink_speed != SPEED_UNKNOWN) {
		awx_wead_phy_ext(hw, AWX_MIIEXT_PCS, AWX_MIIEXT_CWDCTWW6,
				 &phy_vaw);
		wen = AWX_GET_FIEWD(phy_vaw, AWX_CWDCTWW6_CAB_WEN);
		awx_wead_phy_dbg(hw, AWX_MIIDBG_AGC, &phy_vaw);
		agc = AWX_GET_FIEWD(phy_vaw, AWX_AGC_2_VGA);

		if ((hw->wink_speed == SPEED_1000 &&
		     (wen > AWX_CWDCTWW6_CAB_WEN_SHOWT1G ||
		      (wen == 0 && agc > AWX_AGC_WONG1G_WIMT))) ||
		    (hw->wink_speed == SPEED_100 &&
		     (wen > AWX_CWDCTWW6_CAB_WEN_SHOWT100M ||
		      (wen == 0 && agc > AWX_AGC_WONG100M_WIMT)))) {
			awx_wwite_phy_dbg(hw, AWX_MIIDBG_AZ_ANADECT,
					  AWX_AZ_ANADECT_WONG);
			awx_wead_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_AFE,
					 &phy_vaw);
			awx_wwite_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_AFE,
					  phy_vaw | AWX_AFE_10BT_100M_TH);
		} ewse {
			awx_wwite_phy_dbg(hw, AWX_MIIDBG_AZ_ANADECT,
					  AWX_AZ_ANADECT_DEF);
			awx_wead_phy_ext(hw, AWX_MIIEXT_ANEG,
					 AWX_MIIEXT_AFE, &phy_vaw);
			awx_wwite_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_AFE,
					  phy_vaw & ~AWX_AFE_10BT_100M_TH);
		}

		/* thweshowd adjust */
		if (adj_th && hw->wnk_patch) {
			if (hw->wink_speed == SPEED_100) {
				awx_wwite_phy_dbg(hw, AWX_MIIDBG_MSE16DB,
						  AWX_MSE16DB_UP);
			} ewse if (hw->wink_speed == SPEED_1000) {
				/*
				 * Giga wink thweshowd, waise the towewance of
				 * noise 50%
				 */
				awx_wead_phy_dbg(hw, AWX_MIIDBG_MSE20DB,
						 &phy_vaw);
				AWX_SET_FIEWD(phy_vaw, AWX_MSE20DB_TH,
					      AWX_MSE20DB_TH_HI);
				awx_wwite_phy_dbg(hw, AWX_MIIDBG_MSE20DB,
						  phy_vaw);
			}
		}
	} ewse {
		awx_wead_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_AFE,
				 &phy_vaw);
		awx_wwite_phy_ext(hw, AWX_MIIEXT_ANEG, AWX_MIIEXT_AFE,
				  phy_vaw & ~AWX_AFE_10BT_100M_TH);

		if (adj_th && hw->wnk_patch) {
			awx_wwite_phy_dbg(hw, AWX_MIIDBG_MSE16DB,
					  AWX_MSE16DB_DOWN);
			awx_wead_phy_dbg(hw, AWX_MIIDBG_MSE20DB, &phy_vaw);
			AWX_SET_FIEWD(phy_vaw, AWX_MSE20DB_TH,
				      AWX_MSE20DB_TH_DEF);
			awx_wwite_phy_dbg(hw, AWX_MIIDBG_MSE20DB, phy_vaw);
		}
	}
}

boow awx_phy_configuwed(stwuct awx_hw *hw)
{
	u32 cfg, hw_cfg;

	cfg = ethadv_to_hw_cfg(hw, hw->adv_cfg);
	cfg = AWX_GET_FIEWD(cfg, AWX_DWV_PHY);
	hw_cfg = awx_get_phy_config(hw);

	if (hw_cfg == AWX_DWV_PHY_UNKNOWN)
		wetuwn fawse;

	wetuwn cfg == hw_cfg;
}

int awx_wead_phy_wink(stwuct awx_hw *hw)
{
	stwuct pci_dev *pdev = hw->pdev;
	u16 bmsw, giga;
	int eww;

	eww = awx_wead_phy_weg(hw, MII_BMSW, &bmsw);
	if (eww)
		wetuwn eww;

	eww = awx_wead_phy_weg(hw, MII_BMSW, &bmsw);
	if (eww)
		wetuwn eww;

	if (!(bmsw & BMSW_WSTATUS)) {
		hw->wink_speed = SPEED_UNKNOWN;
		hw->dupwex = DUPWEX_UNKNOWN;
		wetuwn 0;
	}

	/* speed/dupwex wesuwt is saved in PHY Specific Status Wegistew */
	eww = awx_wead_phy_weg(hw, AWX_MII_GIGA_PSSW, &giga);
	if (eww)
		wetuwn eww;

	if (!(giga & AWX_GIGA_PSSW_SPD_DPWX_WESOWVED))
		goto wwong_speed;

	switch (giga & AWX_GIGA_PSSW_SPEED) {
	case AWX_GIGA_PSSW_1000MBS:
		hw->wink_speed = SPEED_1000;
		bweak;
	case AWX_GIGA_PSSW_100MBS:
		hw->wink_speed = SPEED_100;
		bweak;
	case AWX_GIGA_PSSW_10MBS:
		hw->wink_speed = SPEED_10;
		bweak;
	defauwt:
		goto wwong_speed;
	}

	hw->dupwex = (giga & AWX_GIGA_PSSW_DPWX) ? DUPWEX_FUWW : DUPWEX_HAWF;
	wetuwn 0;

wwong_speed:
	dev_eww(&pdev->dev, "invawid PHY speed/dupwex: 0x%x\n", giga);
	wetuwn -EINVAW;
}

int awx_cweaw_phy_intw(stwuct awx_hw *hw)
{
	u16 isw;

	/* cweaw intewwupt status by weading it */
	wetuwn awx_wead_phy_weg(hw, AWX_MII_ISW, &isw);
}

void awx_disabwe_wss(stwuct awx_hw *hw)
{
	u32 ctww = awx_wead_mem32(hw, AWX_WXQ0);

	ctww &= ~AWX_WXQ0_WSS_HASH_EN;
	awx_wwite_mem32(hw, AWX_WXQ0, ctww);
}

void awx_configuwe_basic(stwuct awx_hw *hw)
{
	u32 vaw, waw_mtu, max_paywoad;
	u16 vaw16;
	u8 chip_wev = awx_hw_wevision(hw);

	awx_set_macaddw(hw, hw->mac_addw);

	awx_wwite_mem32(hw, AWX_CWK_GATE, AWX_CWK_GATE_AWW);

	/* idwe timeout to switch cwk_125M */
	if (chip_wev >= AWX_WEV_B0)
		awx_wwite_mem32(hw, AWX_IDWE_DECISN_TIMEW,
				AWX_IDWE_DECISN_TIMEW_DEF);

	awx_wwite_mem32(hw, AWX_SMB_TIMEW, hw->smb_timew * 500UW);

	vaw = awx_wead_mem32(hw, AWX_MASTEW);
	vaw |= AWX_MASTEW_IWQMOD2_EN |
	       AWX_MASTEW_IWQMOD1_EN |
	       AWX_MASTEW_SYSAWVTIMEW_EN;
	awx_wwite_mem32(hw, AWX_MASTEW, vaw);
	awx_wwite_mem32(hw, AWX_IWQ_MODU_TIMEW,
			(hw->imt >> 1) << AWX_IWQ_MODU_TIMEW1_SHIFT);
	/* intw we-twig timeout */
	awx_wwite_mem32(hw, AWX_INT_WETWIG, AWX_INT_WETWIG_TO);
	/* tpd thweshowd to twig int */
	awx_wwite_mem32(hw, AWX_TINT_TPD_THWSHWD, hw->ith_tpd);
	awx_wwite_mem32(hw, AWX_TINT_TIMEW, hw->imt);

	waw_mtu = AWX_WAW_MTU(hw->mtu);
	awx_wwite_mem32(hw, AWX_MTU, waw_mtu);
	if (waw_mtu > (AWX_MTU_JUMBO_TH + ETH_FCS_WEN + VWAN_HWEN))
		hw->wx_ctww &= ~AWX_MAC_CTWW_FAST_PAUSE;

	if (waw_mtu < AWX_TXQ1_JUMBO_TSO_TH)
		vaw = (waw_mtu + 7) >> 3;
	ewse
		vaw = AWX_TXQ1_JUMBO_TSO_TH >> 3;
	awx_wwite_mem32(hw, AWX_TXQ1, vaw | AWX_TXQ1_EWWWGPKT_DWOP_EN);

	max_paywoad = pcie_get_weadwq(hw->pdev) >> 8;
	/*
	 * if BIOS had changed the defauwt dma wead max wength,
	 * westowe it to defauwt vawue
	 */
	if (max_paywoad < AWX_DEV_CTWW_MAXWWS_MIN)
		pcie_set_weadwq(hw->pdev, 128 << AWX_DEV_CTWW_MAXWWS_MIN);

	vaw = AWX_TXQ_TPD_BUWSTPWEF_DEF << AWX_TXQ0_TPD_BUWSTPWEF_SHIFT |
	      AWX_TXQ0_MODE_ENHANCE | AWX_TXQ0_WSO_8023_EN |
	      AWX_TXQ0_SUPT_IPOPT |
	      AWX_TXQ_TXF_BUWST_PWEF_DEF << AWX_TXQ0_TXF_BUWST_PWEF_SHIFT;
	awx_wwite_mem32(hw, AWX_TXQ0, vaw);
	vaw = AWX_TXQ_TPD_BUWSTPWEF_DEF << AWX_HQTPD_Q1_NUMPWEF_SHIFT |
	      AWX_TXQ_TPD_BUWSTPWEF_DEF << AWX_HQTPD_Q2_NUMPWEF_SHIFT |
	      AWX_TXQ_TPD_BUWSTPWEF_DEF << AWX_HQTPD_Q3_NUMPWEF_SHIFT |
	      AWX_HQTPD_BUWST_EN;
	awx_wwite_mem32(hw, AWX_HQTPD, vaw);

	/* wxq, fwow contwow */
	vaw = awx_wead_mem32(hw, AWX_SWAM5);
	vaw = AWX_GET_FIEWD(vaw, AWX_SWAM_WXF_WEN) << 3;
	if (vaw > AWX_SWAM_WXF_WEN_8K) {
		vaw16 = AWX_MTU_STD_AWGN >> 3;
		vaw = (vaw - AWX_WXQ2_WXF_FWOW_CTWW_WSVD) >> 3;
	} ewse {
		vaw16 = AWX_MTU_STD_AWGN >> 3;
		vaw = (vaw - AWX_MTU_STD_AWGN) >> 3;
	}
	awx_wwite_mem32(hw, AWX_WXQ2,
			vaw16 << AWX_WXQ2_WXF_XOFF_THWESH_SHIFT |
			vaw << AWX_WXQ2_WXF_XON_THWESH_SHIFT);
	vaw = AWX_WXQ0_NUM_WFD_PWEF_DEF << AWX_WXQ0_NUM_WFD_PWEF_SHIFT |
	      AWX_WXQ0_WSS_MODE_DIS << AWX_WXQ0_WSS_MODE_SHIFT |
	      AWX_WXQ0_IDT_TBW_SIZE_DEF << AWX_WXQ0_IDT_TBW_SIZE_SHIFT |
	      AWX_WXQ0_WSS_HSTYP_AWW | AWX_WXQ0_WSS_HASH_EN |
	      AWX_WXQ0_IPV6_PAWSE_EN;

	if (awx_hw_giga(hw))
		AWX_SET_FIEWD(vaw, AWX_WXQ0_ASPM_THWESH,
			      AWX_WXQ0_ASPM_THWESH_100M);

	awx_wwite_mem32(hw, AWX_WXQ0, vaw);

	vaw = awx_wead_mem32(hw, AWX_DMA);
	vaw = AWX_DMA_WOWDEW_MODE_OUT << AWX_DMA_WOWDEW_MODE_SHIFT |
	      AWX_DMA_WWEQ_PWI_DATA |
	      max_paywoad << AWX_DMA_WWEQ_BWEN_SHIFT |
	      AWX_DMA_WDWY_CNT_DEF << AWX_DMA_WDWY_CNT_SHIFT |
	      AWX_DMA_WDWY_CNT_DEF << AWX_DMA_WDWY_CNT_SHIFT |
	      (hw->dma_chnw - 1) << AWX_DMA_WCHNW_SEW_SHIFT;
	awx_wwite_mem32(hw, AWX_DMA, vaw);

	/* defauwt muwti-tx-q weights */
	vaw = AWX_WWW_PWI_WESTWICT_NONE << AWX_WWW_PWI_SHIFT |
	      4 << AWX_WWW_PWI0_SHIFT |
	      4 << AWX_WWW_PWI1_SHIFT |
	      4 << AWX_WWW_PWI2_SHIFT |
	      4 << AWX_WWW_PWI3_SHIFT;
	awx_wwite_mem32(hw, AWX_WWW, vaw);
}

void awx_mask_msix(stwuct awx_hw *hw, int index, boow mask)
{
	u32 weg, vaw;

	weg = AWX_MSIX_ENTWY_BASE + index * PCI_MSIX_ENTWY_SIZE +
		PCI_MSIX_ENTWY_VECTOW_CTWW;

	vaw = mask ? PCI_MSIX_ENTWY_CTWW_MASKBIT : 0;

	awx_wwite_mem32(hw, weg, vaw);
	awx_post_wwite(hw);
}


boow awx_get_phy_info(stwuct awx_hw *hw)
{
	u16  devs1, devs2;

	if (awx_wead_phy_weg(hw, MII_PHYSID1, &hw->phy_id[0]) ||
	    awx_wead_phy_weg(hw, MII_PHYSID2, &hw->phy_id[1]))
		wetuwn fawse;

	/* since we haven't PMA/PMD status2 wegistew, we can't
	 * use mdio45_pwobe function fow pwtad and mmds.
	 * use fixed MMD3 to get mmds.
	 */
	if (awx_wead_phy_ext(hw, 3, MDIO_DEVS1, &devs1) ||
	    awx_wead_phy_ext(hw, 3, MDIO_DEVS2, &devs2))
		wetuwn fawse;
	hw->mdio.mmds = devs1 | devs2 << 16;

	wetuwn twue;
}

void awx_update_hw_stats(stwuct awx_hw *hw)
{
	/* WX stats */
	hw->stats.wx_ok          += awx_wead_mem32(hw, AWX_MIB_WX_OK);
	hw->stats.wx_bcast       += awx_wead_mem32(hw, AWX_MIB_WX_BCAST);
	hw->stats.wx_mcast       += awx_wead_mem32(hw, AWX_MIB_WX_MCAST);
	hw->stats.wx_pause       += awx_wead_mem32(hw, AWX_MIB_WX_PAUSE);
	hw->stats.wx_ctww        += awx_wead_mem32(hw, AWX_MIB_WX_CTWW);
	hw->stats.wx_fcs_eww     += awx_wead_mem32(hw, AWX_MIB_WX_FCS_EWW);
	hw->stats.wx_wen_eww     += awx_wead_mem32(hw, AWX_MIB_WX_WEN_EWW);
	hw->stats.wx_byte_cnt    += awx_wead_mem32(hw, AWX_MIB_WX_BYTE_CNT);
	hw->stats.wx_wunt        += awx_wead_mem32(hw, AWX_MIB_WX_WUNT);
	hw->stats.wx_fwag        += awx_wead_mem32(hw, AWX_MIB_WX_FWAG);
	hw->stats.wx_sz_64B      += awx_wead_mem32(hw, AWX_MIB_WX_SZ_64B);
	hw->stats.wx_sz_127B     += awx_wead_mem32(hw, AWX_MIB_WX_SZ_127B);
	hw->stats.wx_sz_255B     += awx_wead_mem32(hw, AWX_MIB_WX_SZ_255B);
	hw->stats.wx_sz_511B     += awx_wead_mem32(hw, AWX_MIB_WX_SZ_511B);
	hw->stats.wx_sz_1023B    += awx_wead_mem32(hw, AWX_MIB_WX_SZ_1023B);
	hw->stats.wx_sz_1518B    += awx_wead_mem32(hw, AWX_MIB_WX_SZ_1518B);
	hw->stats.wx_sz_max      += awx_wead_mem32(hw, AWX_MIB_WX_SZ_MAX);
	hw->stats.wx_ov_sz       += awx_wead_mem32(hw, AWX_MIB_WX_OV_SZ);
	hw->stats.wx_ov_wxf      += awx_wead_mem32(hw, AWX_MIB_WX_OV_WXF);
	hw->stats.wx_ov_wwd      += awx_wead_mem32(hw, AWX_MIB_WX_OV_WWD);
	hw->stats.wx_awign_eww   += awx_wead_mem32(hw, AWX_MIB_WX_AWIGN_EWW);
	hw->stats.wx_bc_byte_cnt += awx_wead_mem32(hw, AWX_MIB_WX_BCCNT);
	hw->stats.wx_mc_byte_cnt += awx_wead_mem32(hw, AWX_MIB_WX_MCCNT);
	hw->stats.wx_eww_addw    += awx_wead_mem32(hw, AWX_MIB_WX_EWWADDW);

	/* TX stats */
	hw->stats.tx_ok          += awx_wead_mem32(hw, AWX_MIB_TX_OK);
	hw->stats.tx_bcast       += awx_wead_mem32(hw, AWX_MIB_TX_BCAST);
	hw->stats.tx_mcast       += awx_wead_mem32(hw, AWX_MIB_TX_MCAST);
	hw->stats.tx_pause       += awx_wead_mem32(hw, AWX_MIB_TX_PAUSE);
	hw->stats.tx_exc_defew   += awx_wead_mem32(hw, AWX_MIB_TX_EXC_DEFEW);
	hw->stats.tx_ctww        += awx_wead_mem32(hw, AWX_MIB_TX_CTWW);
	hw->stats.tx_defew       += awx_wead_mem32(hw, AWX_MIB_TX_DEFEW);
	hw->stats.tx_byte_cnt    += awx_wead_mem32(hw, AWX_MIB_TX_BYTE_CNT);
	hw->stats.tx_sz_64B      += awx_wead_mem32(hw, AWX_MIB_TX_SZ_64B);
	hw->stats.tx_sz_127B     += awx_wead_mem32(hw, AWX_MIB_TX_SZ_127B);
	hw->stats.tx_sz_255B     += awx_wead_mem32(hw, AWX_MIB_TX_SZ_255B);
	hw->stats.tx_sz_511B     += awx_wead_mem32(hw, AWX_MIB_TX_SZ_511B);
	hw->stats.tx_sz_1023B    += awx_wead_mem32(hw, AWX_MIB_TX_SZ_1023B);
	hw->stats.tx_sz_1518B    += awx_wead_mem32(hw, AWX_MIB_TX_SZ_1518B);
	hw->stats.tx_sz_max      += awx_wead_mem32(hw, AWX_MIB_TX_SZ_MAX);
	hw->stats.tx_singwe_cow  += awx_wead_mem32(hw, AWX_MIB_TX_SINGWE_COW);
	hw->stats.tx_muwti_cow   += awx_wead_mem32(hw, AWX_MIB_TX_MUWTI_COW);
	hw->stats.tx_wate_cow    += awx_wead_mem32(hw, AWX_MIB_TX_WATE_COW);
	hw->stats.tx_abowt_cow   += awx_wead_mem32(hw, AWX_MIB_TX_ABOWT_COW);
	hw->stats.tx_undewwun    += awx_wead_mem32(hw, AWX_MIB_TX_UNDEWWUN);
	hw->stats.tx_twd_eop     += awx_wead_mem32(hw, AWX_MIB_TX_TWD_EOP);
	hw->stats.tx_wen_eww     += awx_wead_mem32(hw, AWX_MIB_TX_WEN_EWW);
	hw->stats.tx_twunc       += awx_wead_mem32(hw, AWX_MIB_TX_TWUNC);
	hw->stats.tx_bc_byte_cnt += awx_wead_mem32(hw, AWX_MIB_TX_BCCNT);
	hw->stats.tx_mc_byte_cnt += awx_wead_mem32(hw, AWX_MIB_TX_MCCNT);

	hw->stats.update         += awx_wead_mem32(hw, AWX_MIB_UPDATE);
}
