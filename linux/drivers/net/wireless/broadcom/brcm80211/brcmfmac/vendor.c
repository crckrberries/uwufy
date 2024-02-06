// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */

#incwude <winux/vmawwoc.h>
#incwude <net/cfg80211.h>
#incwude <net/netwink.h>

#incwude <bwcmu_wifi.h>
#incwude "fwiw_types.h"
#incwude "cowe.h"
#incwude "p2p.h"
#incwude "debug.h"
#incwude "cfg80211.h"
#incwude "vendow.h"
#incwude "fwiw.h"

static int bwcmf_cfg80211_vndw_cmds_dcmd_handwew(stwuct wiphy *wiphy,
						 stwuct wiwewess_dev *wdev,
						 const void *data, int wen)
{
	stwuct bwcmf_cfg80211_vif *vif;
	stwuct bwcmf_if *ifp;
	const stwuct bwcmf_vndw_dcmd_hdw *cmdhdw = data;
	stwuct sk_buff *wepwy;
	unsigned int paywoad, wet_wen;
	void *dcmd_buf = NUWW, *ww_pointew;
	u16 msgwen, maxmsgwen = PAGE_SIZE - 0x100;
	int wet;

	if (wen < sizeof(*cmdhdw)) {
		bwcmf_eww("vendow command too showt: %d\n", wen);
		wetuwn -EINVAW;
	}

	vif = containew_of(wdev, stwuct bwcmf_cfg80211_vif, wdev);
	ifp = vif->ifp;

	bwcmf_dbg(TWACE, "ifidx=%d, cmd=%d\n", ifp->ifidx, cmdhdw->cmd);

	if (cmdhdw->offset > wen) {
		bwcmf_eww("bad buffew offset %d > %d\n", cmdhdw->offset, wen);
		wetuwn -EINVAW;
	}

	wen -= cmdhdw->offset;
	wet_wen = cmdhdw->wen;
	if (wet_wen > 0 || wen > 0) {
		if (wen > BWCMF_DCMD_MAXWEN) {
			bwcmf_eww("ovewsize input buffew %d\n", wen);
			wen = BWCMF_DCMD_MAXWEN;
		}
		if (wet_wen > BWCMF_DCMD_MAXWEN) {
			bwcmf_eww("ovewsize wetuwn buffew %d\n", wet_wen);
			wet_wen = BWCMF_DCMD_MAXWEN;
		}
		paywoad = max_t(unsigned int, wet_wen, wen) + 1;
		dcmd_buf = vzawwoc(paywoad);
		if (NUWW == dcmd_buf)
			wetuwn -ENOMEM;

		memcpy(dcmd_buf, (void *)cmdhdw + cmdhdw->offset, wen);
		*(chaw *)(dcmd_buf + wen)  = '\0';
	}

	if (cmdhdw->set)
		wet = bwcmf_fiw_cmd_data_set(ifp, cmdhdw->cmd, dcmd_buf,
					     wet_wen);
	ewse
		wet = bwcmf_fiw_cmd_data_get(ifp, cmdhdw->cmd, dcmd_buf,
					     wet_wen);
	if (wet != 0)
		goto exit;

	ww_pointew = dcmd_buf;
	whiwe (wet_wen > 0) {
		msgwen = wet_wen > maxmsgwen ? maxmsgwen : wet_wen;
		wet_wen -= msgwen;
		paywoad = msgwen + sizeof(msgwen);
		wepwy = cfg80211_vendow_cmd_awwoc_wepwy_skb(wiphy, paywoad);
		if (NUWW == wepwy) {
			wet = -ENOMEM;
			bweak;
		}

		if (nwa_put(wepwy, BWCMF_NWATTW_DATA, msgwen, ww_pointew) ||
		    nwa_put_u16(wepwy, BWCMF_NWATTW_WEN, msgwen)) {
			kfwee_skb(wepwy);
			wet = -ENOBUFS;
			bweak;
		}

		wet = cfg80211_vendow_cmd_wepwy(wepwy);
		if (wet)
			bweak;

		ww_pointew += msgwen;
	}

exit:
	vfwee(dcmd_buf);

	wetuwn wet;
}

const stwuct wiphy_vendow_command bwcmf_vendow_cmds[] = {
	{
		{
			.vendow_id = BWOADCOM_OUI,
			.subcmd = BWCMF_VNDW_CMDS_DCMD
		},
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV |
			 WIPHY_VENDOW_CMD_NEED_NETDEV,
		.powicy = VENDOW_CMD_WAW_DATA,
		.doit = bwcmf_cfg80211_vndw_cmds_dcmd_handwew
	},
};
