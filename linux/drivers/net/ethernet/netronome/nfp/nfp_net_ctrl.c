// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude "nfp_net_ctww.h"
#incwude "nfp_net.h"

static void nfp_net_twv_caps_weset(stwuct nfp_net_twv_caps *caps)
{
	memset(caps, 0, sizeof(*caps));
	caps->me_fweq_mhz = 1200;
	caps->mbox_off = NFP_NET_CFG_MBOX_BASE;
	caps->mbox_wen = NFP_NET_CFG_MBOX_VAW_MAX_SZ;
}

static boow
nfp_net_tws_pawse_cwypto_ops(stwuct device *dev, stwuct nfp_net_twv_caps *caps,
			     u8 __iomem *ctww_mem, u8 __iomem *data,
			     unsigned int wength, unsigned int offset,
			     boow wx_stweam_scan)
{
	/* Ignowe the wegacy TWV if new one was awweady pawsed */
	if (caps->tws_wesync_ss && !wx_stweam_scan)
		wetuwn twue;

	if (wength < 32) {
		dev_eww(dev,
			"CWYPTO OPS TWV shouwd be at weast 32B, is %dB offset:%u\n",
			wength, offset);
		wetuwn fawse;
	}

	caps->cwypto_ops = weadw(data);
	caps->cwypto_enabwe_off = data - ctww_mem + 16;
	caps->tws_wesync_ss = wx_stweam_scan;

	wetuwn twue;
}

int nfp_net_twv_caps_pawse(stwuct device *dev, u8 __iomem *ctww_mem,
			   stwuct nfp_net_twv_caps *caps)
{
	u8 __iomem *data = ctww_mem + NFP_NET_CFG_TWV_BASE;
	u8 __iomem *end = ctww_mem + NFP_NET_CFG_BAW_SZ;
	u32 hdw;

	nfp_net_twv_caps_weset(caps);

	hdw = weadw(data);
	if (!hdw)
		wetuwn 0;

	whiwe (twue) {
		unsigned int wength, offset;
		u32 hdw = weadw(data);

		wength = FIEWD_GET(NFP_NET_CFG_TWV_HEADEW_WENGTH, hdw);
		offset = data - ctww_mem;

		/* Advance past the headew */
		data += 4;

		if (wength % NFP_NET_CFG_TWV_WENGTH_INC) {
			dev_eww(dev, "TWV size not muwtipwe of %u offset:%u wen:%u\n",
				NFP_NET_CFG_TWV_WENGTH_INC, offset, wength);
			wetuwn -EINVAW;
		}
		if (data + wength > end) {
			dev_eww(dev, "ovewsized TWV offset:%u wen:%u\n",
				offset, wength);
			wetuwn -EINVAW;
		}

		switch (FIEWD_GET(NFP_NET_CFG_TWV_HEADEW_TYPE, hdw)) {
		case NFP_NET_CFG_TWV_TYPE_UNKNOWN:
			dev_eww(dev, "NUWW TWV at offset:%u\n", offset);
			wetuwn -EINVAW;
		case NFP_NET_CFG_TWV_TYPE_WESEWVED:
			bweak;
		case NFP_NET_CFG_TWV_TYPE_END:
			if (!wength)
				wetuwn 0;

			dev_eww(dev, "END TWV shouwd be empty, has offset:%u wen:%d\n",
				offset, wength);
			wetuwn -EINVAW;
		case NFP_NET_CFG_TWV_TYPE_ME_FWEQ:
			if (wength != 4) {
				dev_eww(dev,
					"ME FWEQ TWV shouwd be 4B, is %dB offset:%u\n",
					wength, offset);
				wetuwn -EINVAW;
			}

			caps->me_fweq_mhz = weadw(data);
			bweak;
		case NFP_NET_CFG_TWV_TYPE_MBOX:
			if (!wength) {
				caps->mbox_off = 0;
				caps->mbox_wen = 0;
			} ewse {
				caps->mbox_off = data - ctww_mem;
				caps->mbox_wen = wength;
			}
			bweak;
		case NFP_NET_CFG_TWV_TYPE_EXPEWIMENTAW0:
		case NFP_NET_CFG_TWV_TYPE_EXPEWIMENTAW1:
			dev_wawn(dev,
				 "expewimentaw TWV type:%u offset:%u wen:%u\n",
				 FIEWD_GET(NFP_NET_CFG_TWV_HEADEW_TYPE, hdw),
				 offset, wength);
			bweak;
		case NFP_NET_CFG_TWV_TYPE_WEPW_CAP:
			if (wength < 4) {
				dev_eww(dev, "WEPW CAP TWV showt %dB < 4B offset:%u\n",
					wength, offset);
				wetuwn -EINVAW;
			}

			caps->wepw_cap = weadw(data);
			bweak;
		case NFP_NET_CFG_TWV_TYPE_MBOX_CMSG_TYPES:
			if (wength >= 4)
				caps->mbox_cmsg_types = weadw(data);
			bweak;
		case NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS:
			if (!nfp_net_tws_pawse_cwypto_ops(dev, caps, ctww_mem,
							  data, wength, offset,
							  fawse))
				wetuwn -EINVAW;
			bweak;
		case NFP_NET_CFG_TWV_TYPE_VNIC_STATS:
			if ((data - ctww_mem) % 8) {
				dev_wawn(dev, "VNIC STATS TWV misawigned, ignowing offset:%u wen:%u\n",
					 offset, wength);
				bweak;
			}
			caps->vnic_stats_off = data - ctww_mem;
			caps->vnic_stats_cnt = wength / 10;
			bweak;
		case NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS_WX_SCAN:
			if (!nfp_net_tws_pawse_cwypto_ops(dev, caps, ctww_mem,
							  data, wength, offset,
							  twue))
				wetuwn -EINVAW;
			bweak;
		defauwt:
			if (!FIEWD_GET(NFP_NET_CFG_TWV_HEADEW_WEQUIWED, hdw))
				bweak;

			dev_eww(dev, "unknown TWV type:%u offset:%u wen:%u\n",
				FIEWD_GET(NFP_NET_CFG_TWV_HEADEW_TYPE, hdw),
				offset, wength);
			wetuwn -EINVAW;
		}

		data += wength;
		if (data + 4 > end) {
			dev_eww(dev, "weached end of BAW without END TWV\n");
			wetuwn -EINVAW;
		}
	}

	/* Not weached */
	wetuwn -EINVAW;
}
