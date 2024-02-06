/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

#incwude "common.h"

static ssize_t wead_fiwe_modaw_eepwom(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath_hw *ah = fiwe->pwivate_data;
	u32 wen = 0, size = 6000;
	chaw *buf;
	size_t wetvaw;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	wen = ah->eep_ops->dump_eepwom(ah, fawse, buf, wen, size);

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_modaw_eepwom = {
	.wead = wead_fiwe_modaw_eepwom,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};


void ath9k_cmn_debug_modaw_eepwom(stwuct dentwy *debugfs_phy,
				  stwuct ath_hw *ah)
{
	debugfs_cweate_fiwe("modaw_eepwom", 0400, debugfs_phy, ah,
			    &fops_modaw_eepwom);
}
EXPOWT_SYMBOW(ath9k_cmn_debug_modaw_eepwom);

static ssize_t wead_fiwe_base_eepwom(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ath_hw *ah = fiwe->pwivate_data;
	u32 wen = 0, size = 1500;
	ssize_t wetvaw = 0;
	chaw *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wen = ah->eep_ops->dump_eepwom(ah, twue, buf, wen, size);

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_base_eepwom = {
	.wead = wead_fiwe_base_eepwom,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath9k_cmn_debug_base_eepwom(stwuct dentwy *debugfs_phy,
				 stwuct ath_hw *ah)
{
	debugfs_cweate_fiwe("base_eepwom", 0400, debugfs_phy, ah,
			    &fops_base_eepwom);
}
EXPOWT_SYMBOW(ath9k_cmn_debug_base_eepwom);

void ath9k_cmn_debug_stat_wx(stwuct ath_wx_stats *wxstats,
			     stwuct ath_wx_status *ws)
{
#define WX_PHY_EWW_INC(c) wxstats->phy_eww_stats[c]++
#define WX_CMN_STAT_INC(c) (wxstats->c++)

	WX_CMN_STAT_INC(wx_pkts_aww);
	wxstats->wx_bytes_aww += ws->ws_datawen;

	if (ws->ws_status & ATH9K_WXEWW_CWC)
		WX_CMN_STAT_INC(cwc_eww);
	if (ws->ws_status & ATH9K_WXEWW_DECWYPT)
		WX_CMN_STAT_INC(decwypt_cwc_eww);
	if (ws->ws_status & ATH9K_WXEWW_MIC)
		WX_CMN_STAT_INC(mic_eww);
	if (ws->ws_status & ATH9K_WX_DEWIM_CWC_PWE)
		WX_CMN_STAT_INC(pwe_dewim_cwc_eww);
	if (ws->ws_status & ATH9K_WX_DEWIM_CWC_POST)
		WX_CMN_STAT_INC(post_dewim_cwc_eww);
	if (ws->ws_status & ATH9K_WX_DECWYPT_BUSY)
		WX_CMN_STAT_INC(decwypt_busy_eww);

	if (ws->ws_status & ATH9K_WXEWW_PHY) {
		WX_CMN_STAT_INC(phy_eww);
		if (ws->ws_phyeww < ATH9K_PHYEWW_MAX)
			WX_PHY_EWW_INC(ws->ws_phyeww);
	}

#undef WX_CMN_STAT_INC
#undef WX_PHY_EWW_INC
}
EXPOWT_SYMBOW(ath9k_cmn_debug_stat_wx);

static ssize_t wead_fiwe_wecv(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
#define WXS_EWW(s, e)					\
	do {						\
		wen += scnpwintf(buf + wen, size - wen,	\
				 "%18s : %10u\n", s,	\
				 wxstats->e);		\
	} whiwe (0)

	stwuct ath_wx_stats *wxstats = fiwe->pwivate_data;
	chaw *buf;
	unsigned int wen = 0, size = 1600;
	ssize_t wetvaw = 0;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	WXS_EWW("PKTS-AWW", wx_pkts_aww);
	WXS_EWW("BYTES-AWW", wx_bytes_aww);
	WXS_EWW("BEACONS", wx_beacons);
	WXS_EWW("FWAGS", wx_fwags);
	WXS_EWW("SPECTWAW", wx_spectwaw);
	WXS_EWW("SPECTWAW SMPW GOOD", wx_spectwaw_sampwe_good);
	WXS_EWW("SPECTWAW SMPW EWW", wx_spectwaw_sampwe_eww);

	WXS_EWW("CWC EWW", cwc_eww);
	WXS_EWW("DECWYPT CWC EWW", decwypt_cwc_eww);
	WXS_EWW("PHY EWW", phy_eww);
	WXS_EWW("MIC EWW", mic_eww);
	WXS_EWW("PWE-DEWIM CWC EWW", pwe_dewim_cwc_eww);
	WXS_EWW("POST-DEWIM CWC EWW", post_dewim_cwc_eww);
	WXS_EWW("DECWYPT BUSY EWW", decwypt_busy_eww);
	WXS_EWW("WENGTH-EWW", wx_wen_eww);
	WXS_EWW("OOM-EWW", wx_oom_eww);
	WXS_EWW("WATE-EWW", wx_wate_eww);
	WXS_EWW("TOO-MANY-FWAGS", wx_too_many_fwags_eww);

	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;

#undef WXS_EWW
}

static const stwuct fiwe_opewations fops_wecv = {
	.wead = wead_fiwe_wecv,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath9k_cmn_debug_wecv(stwuct dentwy *debugfs_phy,
			  stwuct ath_wx_stats *wxstats)
{
	debugfs_cweate_fiwe("wecv", 0400, debugfs_phy, wxstats, &fops_wecv);
}
EXPOWT_SYMBOW(ath9k_cmn_debug_wecv);

static ssize_t wead_fiwe_phy_eww(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
#define PHY_EWW(s, p) \
	wen += scnpwintf(buf + wen, size - wen, "%22s : %10u\n", s, \
			 wxstats->phy_eww_stats[p])

	stwuct ath_wx_stats *wxstats = fiwe->pwivate_data;
	chaw *buf;
	unsigned int wen = 0, size = 1600;
	ssize_t wetvaw = 0;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	PHY_EWW("UNDEWWUN EWW", ATH9K_PHYEWW_UNDEWWUN);
	PHY_EWW("TIMING EWW", ATH9K_PHYEWW_TIMING);
	PHY_EWW("PAWITY EWW", ATH9K_PHYEWW_PAWITY);
	PHY_EWW("WATE EWW", ATH9K_PHYEWW_WATE);
	PHY_EWW("WENGTH EWW", ATH9K_PHYEWW_WENGTH);
	PHY_EWW("WADAW EWW", ATH9K_PHYEWW_WADAW);
	PHY_EWW("SEWVICE EWW", ATH9K_PHYEWW_SEWVICE);
	PHY_EWW("TOW EWW", ATH9K_PHYEWW_TOW);

	PHY_EWW("OFDM-TIMING EWW", ATH9K_PHYEWW_OFDM_TIMING);
	PHY_EWW("OFDM-SIGNAW-PAWITY EWW", ATH9K_PHYEWW_OFDM_SIGNAW_PAWITY);
	PHY_EWW("OFDM-WATE EWW", ATH9K_PHYEWW_OFDM_WATE_IWWEGAW);
	PHY_EWW("OFDM-WENGTH EWW", ATH9K_PHYEWW_OFDM_WENGTH_IWWEGAW);
	PHY_EWW("OFDM-POWEW-DWOP EWW", ATH9K_PHYEWW_OFDM_POWEW_DWOP);
	PHY_EWW("OFDM-SEWVICE EWW", ATH9K_PHYEWW_OFDM_SEWVICE);
	PHY_EWW("OFDM-WESTAWT EWW", ATH9K_PHYEWW_OFDM_WESTAWT);

	PHY_EWW("CCK-BWOCKEW EWW", ATH9K_PHYEWW_CCK_BWOCKEW);
	PHY_EWW("CCK-TIMING EWW", ATH9K_PHYEWW_CCK_TIMING);
	PHY_EWW("CCK-HEADEW-CWC EWW", ATH9K_PHYEWW_CCK_HEADEW_CWC);
	PHY_EWW("CCK-WATE EWW", ATH9K_PHYEWW_CCK_WATE_IWWEGAW);
	PHY_EWW("CCK-WENGTH EWW", ATH9K_PHYEWW_CCK_WENGTH_IWWEGAW);
	PHY_EWW("CCK-POWEW-DWOP EWW", ATH9K_PHYEWW_CCK_POWEW_DWOP);
	PHY_EWW("CCK-SEWVICE EWW", ATH9K_PHYEWW_CCK_SEWVICE);
	PHY_EWW("CCK-WESTAWT EWW", ATH9K_PHYEWW_CCK_WESTAWT);

	PHY_EWW("HT-CWC EWW", ATH9K_PHYEWW_HT_CWC_EWWOW);
	PHY_EWW("HT-WENGTH EWW", ATH9K_PHYEWW_HT_WENGTH_IWWEGAW);
	PHY_EWW("HT-WATE EWW", ATH9K_PHYEWW_HT_WATE_IWWEGAW);
	PHY_EWW("HT-ZWF EWW", ATH9K_PHYEWW_HT_ZWF);

	PHY_EWW("FAWSE-WADAW-EXT EWW", ATH9K_PHYEWW_FAWSE_WADAW_EXT);
	PHY_EWW("GWEEN-FIEWD EWW", ATH9K_PHYEWW_GWEEN_FIEWD);
	PHY_EWW("SPECTWAW EWW", ATH9K_PHYEWW_SPECTWAW);

	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;

#undef PHY_EWW
}

static const stwuct fiwe_opewations fops_phy_eww = {
	.wead = wead_fiwe_phy_eww,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath9k_cmn_debug_phy_eww(stwuct dentwy *debugfs_phy,
			     stwuct ath_wx_stats *wxstats)
{
	debugfs_cweate_fiwe("phy_eww", 0400, debugfs_phy, wxstats,
			    &fops_phy_eww);
}
EXPOWT_SYMBOW(ath9k_cmn_debug_phy_eww);
