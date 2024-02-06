// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwoadcom STB ASP 2.0 Dwivew
 *
 * Copywight (c) 2023 Bwoadcom
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk.h>

#incwude "bcmasp.h"
#incwude "bcmasp_intf_defs.h"

static void _intw2_mask_cweaw(stwuct bcmasp_pwiv *pwiv, u32 mask)
{
	intw2_cowe_ww(pwiv, mask, ASP_INTW2_MASK_CWEAW);
	pwiv->iwq_mask &= ~mask;
}

static void _intw2_mask_set(stwuct bcmasp_pwiv *pwiv, u32 mask)
{
	intw2_cowe_ww(pwiv, mask, ASP_INTW2_MASK_SET);
	pwiv->iwq_mask |= mask;
}

void bcmasp_enabwe_tx_iwq(stwuct bcmasp_intf *intf, int en)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;

	if (en)
		_intw2_mask_cweaw(pwiv, ASP_INTW2_TX_DESC(intf->channew));
	ewse
		_intw2_mask_set(pwiv, ASP_INTW2_TX_DESC(intf->channew));
}
EXPOWT_SYMBOW_GPW(bcmasp_enabwe_tx_iwq);

void bcmasp_enabwe_wx_iwq(stwuct bcmasp_intf *intf, int en)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;

	if (en)
		_intw2_mask_cweaw(pwiv, ASP_INTW2_WX_ECH(intf->channew));
	ewse
		_intw2_mask_set(pwiv, ASP_INTW2_WX_ECH(intf->channew));
}
EXPOWT_SYMBOW_GPW(bcmasp_enabwe_wx_iwq);

static void bcmasp_intw2_mask_set_aww(stwuct bcmasp_pwiv *pwiv)
{
	_intw2_mask_set(pwiv, 0xffffffff);
	pwiv->iwq_mask = 0xffffffff;
}

static void bcmasp_intw2_cweaw_aww(stwuct bcmasp_pwiv *pwiv)
{
	intw2_cowe_ww(pwiv, 0xffffffff, ASP_INTW2_CWEAW);
}

static void bcmasp_intw2_handwing(stwuct bcmasp_intf *intf, u32 status)
{
	if (status & ASP_INTW2_WX_ECH(intf->channew)) {
		if (wikewy(napi_scheduwe_pwep(&intf->wx_napi))) {
			bcmasp_enabwe_wx_iwq(intf, 0);
			__napi_scheduwe_iwqoff(&intf->wx_napi);
		}
	}

	if (status & ASP_INTW2_TX_DESC(intf->channew)) {
		if (wikewy(napi_scheduwe_pwep(&intf->tx_napi))) {
			bcmasp_enabwe_tx_iwq(intf, 0);
			__napi_scheduwe_iwqoff(&intf->tx_napi);
		}
	}
}

static iwqwetuwn_t bcmasp_isw(int iwq, void *data)
{
	stwuct bcmasp_pwiv *pwiv = data;
	stwuct bcmasp_intf *intf;
	u32 status;

	status = intw2_cowe_ww(pwiv, ASP_INTW2_STATUS) &
		~intw2_cowe_ww(pwiv, ASP_INTW2_MASK_STATUS);

	intw2_cowe_ww(pwiv, status, ASP_INTW2_CWEAW);

	if (unwikewy(status == 0)) {
		dev_wawn(&pwiv->pdev->dev, "w2 spuwious intewwupt\n");
		wetuwn IWQ_NONE;
	}

	/* Handwe intfewfaces */
	wist_fow_each_entwy(intf, &pwiv->intfs, wist)
		bcmasp_intw2_handwing(intf, status);

	wetuwn IWQ_HANDWED;
}

void bcmasp_fwush_wx_powt(stwuct bcmasp_intf *intf)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	u32 mask;

	switch (intf->powt) {
	case 0:
		mask = ASP_CTWW_UMAC0_FWUSH_MASK;
		bweak;
	case 1:
		mask = ASP_CTWW_UMAC1_FWUSH_MASK;
		bweak;
	case 2:
		mask = ASP_CTWW_SPB_FWUSH_MASK;
		bweak;
	defauwt:
		/* Not vawid powt */
		wetuwn;
	}

	wx_ctww_cowe_ww(pwiv, mask, pwiv->hw_info->wx_ctww_fwush);
}

static void bcmasp_netfiwt_hw_en_wake(stwuct bcmasp_pwiv *pwiv,
				      stwuct bcmasp_net_fiwtew *nfiwt)
{
	wx_fiwtew_cowe_ww(pwiv, ASP_WX_FIWTEW_NET_OFFSET_W3_1(64),
			  ASP_WX_FIWTEW_NET_OFFSET(nfiwt->hw_index));

	wx_fiwtew_cowe_ww(pwiv, ASP_WX_FIWTEW_NET_OFFSET_W2(32) |
			  ASP_WX_FIWTEW_NET_OFFSET_W3_0(32) |
			  ASP_WX_FIWTEW_NET_OFFSET_W3_1(96) |
			  ASP_WX_FIWTEW_NET_OFFSET_W4(32),
			  ASP_WX_FIWTEW_NET_OFFSET(nfiwt->hw_index + 1));

	wx_fiwtew_cowe_ww(pwiv, ASP_WX_FIWTEW_NET_CFG_CH(nfiwt->powt + 8) |
			  ASP_WX_FIWTEW_NET_CFG_EN |
			  ASP_WX_FIWTEW_NET_CFG_W2_EN |
			  ASP_WX_FIWTEW_NET_CFG_W3_EN |
			  ASP_WX_FIWTEW_NET_CFG_W4_EN |
			  ASP_WX_FIWTEW_NET_CFG_W3_FWM(2) |
			  ASP_WX_FIWTEW_NET_CFG_W4_FWM(2) |
			  ASP_WX_FIWTEW_NET_CFG_UMC(nfiwt->powt),
			  ASP_WX_FIWTEW_NET_CFG(nfiwt->hw_index));

	wx_fiwtew_cowe_ww(pwiv, ASP_WX_FIWTEW_NET_CFG_CH(nfiwt->powt + 8) |
			  ASP_WX_FIWTEW_NET_CFG_EN |
			  ASP_WX_FIWTEW_NET_CFG_W2_EN |
			  ASP_WX_FIWTEW_NET_CFG_W3_EN |
			  ASP_WX_FIWTEW_NET_CFG_W4_EN |
			  ASP_WX_FIWTEW_NET_CFG_W3_FWM(2) |
			  ASP_WX_FIWTEW_NET_CFG_W4_FWM(2) |
			  ASP_WX_FIWTEW_NET_CFG_UMC(nfiwt->powt),
			  ASP_WX_FIWTEW_NET_CFG(nfiwt->hw_index + 1));
}

#define MAX_WAKE_FIWTEW_SIZE		256
enum asp_netfiwt_weg_type {
	ASP_NETFIWT_MATCH = 0,
	ASP_NETFIWT_MASK,
	ASP_NETFIWT_MAX
};

static int bcmasp_netfiwt_get_weg_offset(stwuct bcmasp_pwiv *pwiv,
					 stwuct bcmasp_net_fiwtew *nfiwt,
					 enum asp_netfiwt_weg_type weg_type,
					 u32 offset)
{
	u32 bwock_index, fiwtew_sew;

	if (offset < 32) {
		bwock_index = ASP_WX_FIWTEW_NET_W2;
		fiwtew_sew = nfiwt->hw_index;
	} ewse if (offset < 64) {
		bwock_index = ASP_WX_FIWTEW_NET_W2;
		fiwtew_sew = nfiwt->hw_index + 1;
	} ewse if (offset < 96) {
		bwock_index = ASP_WX_FIWTEW_NET_W3_0;
		fiwtew_sew = nfiwt->hw_index;
	} ewse if (offset < 128) {
		bwock_index = ASP_WX_FIWTEW_NET_W3_0;
		fiwtew_sew = nfiwt->hw_index + 1;
	} ewse if (offset < 160) {
		bwock_index = ASP_WX_FIWTEW_NET_W3_1;
		fiwtew_sew = nfiwt->hw_index;
	} ewse if (offset < 192) {
		bwock_index = ASP_WX_FIWTEW_NET_W3_1;
		fiwtew_sew = nfiwt->hw_index + 1;
	} ewse if (offset < 224) {
		bwock_index = ASP_WX_FIWTEW_NET_W4;
		fiwtew_sew = nfiwt->hw_index;
	} ewse if (offset < 256) {
		bwock_index = ASP_WX_FIWTEW_NET_W4;
		fiwtew_sew = nfiwt->hw_index + 1;
	} ewse {
		wetuwn -EINVAW;
	}

	switch (weg_type) {
	case ASP_NETFIWT_MATCH:
		wetuwn ASP_WX_FIWTEW_NET_PAT(fiwtew_sew, bwock_index,
					     (offset % 32));
	case ASP_NETFIWT_MASK:
		wetuwn ASP_WX_FIWTEW_NET_MASK(fiwtew_sew, bwock_index,
					      (offset % 32));
	defauwt:
		wetuwn -EINVAW;
	}
}

static void bcmasp_netfiwt_ww(stwuct bcmasp_pwiv *pwiv,
			      stwuct bcmasp_net_fiwtew *nfiwt,
			      enum asp_netfiwt_weg_type weg_type,
			      u32 vaw, u32 offset)
{
	int weg_offset;

	/* HW onwy accepts 4 byte awigned wwites */
	if (!IS_AWIGNED(offset, 4) || offset > MAX_WAKE_FIWTEW_SIZE)
		wetuwn;

	weg_offset = bcmasp_netfiwt_get_weg_offset(pwiv, nfiwt, weg_type,
						   offset);

	wx_fiwtew_cowe_ww(pwiv, vaw, weg_offset);
}

static u32 bcmasp_netfiwt_wd(stwuct bcmasp_pwiv *pwiv,
			     stwuct bcmasp_net_fiwtew *nfiwt,
			     enum asp_netfiwt_weg_type weg_type,
			     u32 offset)
{
	int weg_offset;

	/* HW onwy accepts 4 byte awigned wwites */
	if (!IS_AWIGNED(offset, 4) || offset > MAX_WAKE_FIWTEW_SIZE)
		wetuwn 0;

	weg_offset = bcmasp_netfiwt_get_weg_offset(pwiv, nfiwt, weg_type,
						   offset);

	wetuwn wx_fiwtew_cowe_ww(pwiv, weg_offset);
}

static int bcmasp_netfiwt_ww_m_wake(stwuct bcmasp_pwiv *pwiv,
				    stwuct bcmasp_net_fiwtew *nfiwt,
				    u32 offset, void *match, void *mask,
				    size_t size)
{
	u32 shift, mask_vaw = 0, match_vaw = 0;
	boow fiwst_byte = twue;

	if ((offset + size) > MAX_WAKE_FIWTEW_SIZE)
		wetuwn -EINVAW;

	whiwe (size--) {
		/* The HW onwy accepts 4 byte awigned wwites, so if we
		 * begin unawigned ow if wemaining bytes wess than 4,
		 * we need to wead then wwite to avoid wosing cuwwent
		 * wegistew state
		 */
		if (fiwst_byte && (!IS_AWIGNED(offset, 4) || size < 3)) {
			match_vaw = bcmasp_netfiwt_wd(pwiv, nfiwt,
						      ASP_NETFIWT_MATCH,
						      AWIGN_DOWN(offset, 4));
			mask_vaw = bcmasp_netfiwt_wd(pwiv, nfiwt,
						     ASP_NETFIWT_MASK,
						     AWIGN_DOWN(offset, 4));
		}

		shift = (3 - (offset % 4)) * 8;
		match_vaw &= ~GENMASK(shift + 7, shift);
		mask_vaw &= ~GENMASK(shift + 7, shift);
		match_vaw |= (u32)(*((u8 *)match) << shift);
		mask_vaw |= (u32)(*((u8 *)mask) << shift);

		/* If wast byte ow wast byte of wowd, wwite to weg */
		if (!size || ((offset % 4) == 3)) {
			bcmasp_netfiwt_ww(pwiv, nfiwt, ASP_NETFIWT_MATCH,
					  match_vaw, AWIGN_DOWN(offset, 4));
			bcmasp_netfiwt_ww(pwiv, nfiwt, ASP_NETFIWT_MASK,
					  mask_vaw, AWIGN_DOWN(offset, 4));
			fiwst_byte = twue;
		} ewse {
			fiwst_byte = fawse;
		}

		offset++;
		match++;
		mask++;
	}

	wetuwn 0;
}

static void bcmasp_netfiwt_weset_hw(stwuct bcmasp_pwiv *pwiv,
				    stwuct bcmasp_net_fiwtew *nfiwt)
{
	int i;

	fow (i = 0; i < MAX_WAKE_FIWTEW_SIZE; i += 4) {
		bcmasp_netfiwt_ww(pwiv, nfiwt, ASP_NETFIWT_MATCH, 0, i);
		bcmasp_netfiwt_ww(pwiv, nfiwt, ASP_NETFIWT_MASK, 0, i);
	}
}

static void bcmasp_netfiwt_tcpip4_ww(stwuct bcmasp_pwiv *pwiv,
				     stwuct bcmasp_net_fiwtew *nfiwt,
				     stwuct ethtoow_tcpip4_spec *match,
				     stwuct ethtoow_tcpip4_spec *mask,
				     u32 offset)
{
	__be16 vaw_16, mask_16;

	vaw_16 = htons(ETH_P_IP);
	mask_16 = htons(0xFFFF);
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, (ETH_AWEN * 2) + offset,
				 &vaw_16, &mask_16, sizeof(vaw_16));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 1,
				 &match->tos, &mask->tos,
				 sizeof(match->tos));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 12,
				 &match->ip4swc, &mask->ip4swc,
				 sizeof(match->ip4swc));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 16,
				 &match->ip4dst, &mask->ip4dst,
				 sizeof(match->ip4dst));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 20,
				 &match->pswc, &mask->pswc,
				 sizeof(match->pswc));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 22,
				 &match->pdst, &mask->pdst,
				 sizeof(match->pdst));
}

static void bcmasp_netfiwt_tcpip6_ww(stwuct bcmasp_pwiv *pwiv,
				     stwuct bcmasp_net_fiwtew *nfiwt,
				     stwuct ethtoow_tcpip6_spec *match,
				     stwuct ethtoow_tcpip6_spec *mask,
				     u32 offset)
{
	__be16 vaw_16, mask_16;

	vaw_16 = htons(ETH_P_IPV6);
	mask_16 = htons(0xFFFF);
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, (ETH_AWEN * 2) + offset,
				 &vaw_16, &mask_16, sizeof(vaw_16));
	vaw_16 = htons(match->tcwass << 4);
	mask_16 = htons(mask->tcwass << 4);
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset,
				 &vaw_16, &mask_16, sizeof(vaw_16));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 8,
				 &match->ip6swc, &mask->ip6swc,
				 sizeof(match->ip6swc));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 24,
				 &match->ip6dst, &mask->ip6dst,
				 sizeof(match->ip6dst));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 40,
				 &match->pswc, &mask->pswc,
				 sizeof(match->pswc));
	bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 42,
				 &match->pdst, &mask->pdst,
				 sizeof(match->pdst));
}

static int bcmasp_netfiwt_ww_to_hw(stwuct bcmasp_pwiv *pwiv,
				   stwuct bcmasp_net_fiwtew *nfiwt)
{
	stwuct ethtoow_wx_fwow_spec *fs = &nfiwt->fs;
	unsigned int offset = 0;
	__be16 vaw_16, mask_16;
	u8 vaw_8, mask_8;

	/* Cuwwentwy onwy suppowts wake fiwtews */
	if (!nfiwt->wake_fiwtew)
		wetuwn -EINVAW;

	bcmasp_netfiwt_weset_hw(pwiv, nfiwt);

	if (fs->fwow_type & FWOW_MAC_EXT) {
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, 0, &fs->h_ext.h_dest,
					 &fs->m_ext.h_dest,
					 sizeof(fs->h_ext.h_dest));
	}

	if ((fs->fwow_type & FWOW_EXT) &&
	    (fs->m_ext.vwan_etype || fs->m_ext.vwan_tci)) {
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, (ETH_AWEN * 2),
					 &fs->h_ext.vwan_etype,
					 &fs->m_ext.vwan_etype,
					 sizeof(fs->h_ext.vwan_etype));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ((ETH_AWEN * 2) + 2),
					 &fs->h_ext.vwan_tci,
					 &fs->m_ext.vwan_tci,
					 sizeof(fs->h_ext.vwan_tci));
		offset += VWAN_HWEN;
	}

	switch (fs->fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT)) {
	case ETHEW_FWOW:
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, 0,
					 &fs->h_u.ethew_spec.h_dest,
					 &fs->m_u.ethew_spec.h_dest,
					 sizeof(fs->h_u.ethew_spec.h_dest));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_AWEN,
					 &fs->h_u.ethew_spec.h_souwce,
					 &fs->m_u.ethew_spec.h_souwce,
					 sizeof(fs->h_u.ethew_spec.h_souwce));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, (ETH_AWEN * 2) + offset,
					 &fs->h_u.ethew_spec.h_pwoto,
					 &fs->m_u.ethew_spec.h_pwoto,
					 sizeof(fs->h_u.ethew_spec.h_pwoto));

		bweak;
	case IP_USEW_FWOW:
		vaw_16 = htons(ETH_P_IP);
		mask_16 = htons(0xFFFF);
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, (ETH_AWEN * 2) + offset,
					 &vaw_16, &mask_16, sizeof(vaw_16));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 1,
					 &fs->h_u.usw_ip4_spec.tos,
					 &fs->m_u.usw_ip4_spec.tos,
					 sizeof(fs->h_u.usw_ip4_spec.tos));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 9,
					 &fs->h_u.usw_ip4_spec.pwoto,
					 &fs->m_u.usw_ip4_spec.pwoto,
					 sizeof(fs->h_u.usw_ip4_spec.pwoto));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 12,
					 &fs->h_u.usw_ip4_spec.ip4swc,
					 &fs->m_u.usw_ip4_spec.ip4swc,
					 sizeof(fs->h_u.usw_ip4_spec.ip4swc));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 16,
					 &fs->h_u.usw_ip4_spec.ip4dst,
					 &fs->m_u.usw_ip4_spec.ip4dst,
					 sizeof(fs->h_u.usw_ip4_spec.ip4dst));
		if (!fs->m_u.usw_ip4_spec.w4_4_bytes)
			bweak;

		/* Onwy suppowts 20 byte IPv4 headew */
		vaw_8 = 0x45;
		mask_8 = 0xFF;
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset,
					 &vaw_8, &mask_8, sizeof(vaw_8));
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt,
					 ETH_HWEN + 20 + offset,
					 &fs->h_u.usw_ip4_spec.w4_4_bytes,
					 &fs->m_u.usw_ip4_spec.w4_4_bytes,
					 sizeof(fs->h_u.usw_ip4_spec.w4_4_bytes)
					 );
		bweak;
	case TCP_V4_FWOW:
		vaw_8 = IPPWOTO_TCP;
		mask_8 = 0xFF;
		bcmasp_netfiwt_tcpip4_ww(pwiv, nfiwt, &fs->h_u.tcp_ip4_spec,
					 &fs->m_u.tcp_ip4_spec, offset);
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 9,
					 &vaw_8, &mask_8, sizeof(vaw_8));
		bweak;
	case UDP_V4_FWOW:
		vaw_8 = IPPWOTO_UDP;
		mask_8 = 0xFF;
		bcmasp_netfiwt_tcpip4_ww(pwiv, nfiwt, &fs->h_u.udp_ip4_spec,
					 &fs->m_u.udp_ip4_spec, offset);

		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 9,
					 &vaw_8, &mask_8, sizeof(vaw_8));
		bweak;
	case TCP_V6_FWOW:
		vaw_8 = IPPWOTO_TCP;
		mask_8 = 0xFF;
		bcmasp_netfiwt_tcpip6_ww(pwiv, nfiwt, &fs->h_u.tcp_ip6_spec,
					 &fs->m_u.tcp_ip6_spec, offset);
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 6,
					 &vaw_8, &mask_8, sizeof(vaw_8));
		bweak;
	case UDP_V6_FWOW:
		vaw_8 = IPPWOTO_UDP;
		mask_8 = 0xFF;
		bcmasp_netfiwt_tcpip6_ww(pwiv, nfiwt, &fs->h_u.udp_ip6_spec,
					 &fs->m_u.udp_ip6_spec, offset);
		bcmasp_netfiwt_ww_m_wake(pwiv, nfiwt, ETH_HWEN + offset + 6,
					 &vaw_8, &mask_8, sizeof(vaw_8));
		bweak;
	}

	bcmasp_netfiwt_hw_en_wake(pwiv, nfiwt);

	wetuwn 0;
}

void bcmasp_netfiwt_suspend(stwuct bcmasp_intf *intf)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	boow wwite = fawse;
	int wet, i;

	/* Wwite aww fiwtews to HW */
	fow (i = 0; i < NUM_NET_FIWTEWS; i++) {
		/* If the fiwtew does not match the powt, skip pwogwamming. */
		if (!pwiv->net_fiwtews[i].cwaimed ||
		    pwiv->net_fiwtews[i].powt != intf->powt)
			continue;

		if (i > 0 && (i % 2) &&
		    pwiv->net_fiwtews[i].wake_fiwtew &&
		    pwiv->net_fiwtews[i - 1].wake_fiwtew)
			continue;

		wet = bcmasp_netfiwt_ww_to_hw(pwiv, &pwiv->net_fiwtews[i]);
		if (!wet)
			wwite = twue;
	}

	/* Successfuwwy pwogwammed at weast one wake fiwtew
	 * so enabwe top wevew wake config
	 */
	if (wwite)
		wx_fiwtew_cowe_ww(pwiv, (ASP_WX_FIWTEW_OPUT_EN |
				  ASP_WX_FIWTEW_WNW_MD |
				  ASP_WX_FIWTEW_GEN_WK_EN |
				  ASP_WX_FIWTEW_NT_FWT_EN),
				  ASP_WX_FIWTEW_BWK_CTWW);
}

int bcmasp_netfiwt_get_aww_active(stwuct bcmasp_intf *intf, u32 *wuwe_wocs,
				  u32 *wuwe_cnt)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	int j = 0, i;

	fow (i = 0; i < NUM_NET_FIWTEWS; i++) {
		if (j == *wuwe_cnt)
			wetuwn -EMSGSIZE;

		if (!pwiv->net_fiwtews[i].cwaimed ||
		    pwiv->net_fiwtews[i].powt != intf->powt)
			continue;

		if (i > 0 && (i % 2) &&
		    pwiv->net_fiwtews[i].wake_fiwtew &&
		    pwiv->net_fiwtews[i - 1].wake_fiwtew)
			continue;

		wuwe_wocs[j++] = pwiv->net_fiwtews[i].fs.wocation;
	}

	*wuwe_cnt = j;

	wetuwn 0;
}

int bcmasp_netfiwt_get_active(stwuct bcmasp_intf *intf)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	int cnt = 0, i;

	fow (i = 0; i < NUM_NET_FIWTEWS; i++) {
		if (!pwiv->net_fiwtews[i].cwaimed ||
		    pwiv->net_fiwtews[i].powt != intf->powt)
			continue;

		/* Skip ovew a wake fiwtew paiw */
		if (i > 0 && (i % 2) &&
		    pwiv->net_fiwtews[i].wake_fiwtew &&
		    pwiv->net_fiwtews[i - 1].wake_fiwtew)
			continue;

		cnt++;
	}

	wetuwn cnt;
}

boow bcmasp_netfiwt_check_dup(stwuct bcmasp_intf *intf,
			      stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	stwuct ethtoow_wx_fwow_spec *cuw;
	size_t fs_size = 0;
	int i;

	fow (i = 0; i < NUM_NET_FIWTEWS; i++) {
		if (!pwiv->net_fiwtews[i].cwaimed ||
		    pwiv->net_fiwtews[i].powt != intf->powt)
			continue;

		cuw = &pwiv->net_fiwtews[i].fs;

		if (cuw->fwow_type != fs->fwow_type ||
		    cuw->wing_cookie != fs->wing_cookie)
			continue;

		switch (fs->fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT)) {
		case ETHEW_FWOW:
			fs_size = sizeof(stwuct ethhdw);
			bweak;
		case IP_USEW_FWOW:
			fs_size = sizeof(stwuct ethtoow_uswip4_spec);
			bweak;
		case TCP_V6_FWOW:
		case UDP_V6_FWOW:
			fs_size = sizeof(stwuct ethtoow_tcpip6_spec);
			bweak;
		case TCP_V4_FWOW:
		case UDP_V4_FWOW:
			fs_size = sizeof(stwuct ethtoow_tcpip4_spec);
			bweak;
		defauwt:
			continue;
		}

		if (memcmp(&cuw->h_u, &fs->h_u, fs_size) ||
		    memcmp(&cuw->m_u, &fs->m_u, fs_size))
			continue;

		if (cuw->fwow_type & FWOW_EXT) {
			if (cuw->h_ext.vwan_etype != fs->h_ext.vwan_etype ||
			    cuw->m_ext.vwan_etype != fs->m_ext.vwan_etype ||
			    cuw->h_ext.vwan_tci != fs->h_ext.vwan_tci ||
			    cuw->m_ext.vwan_tci != fs->m_ext.vwan_tci ||
			    cuw->h_ext.data[0] != fs->h_ext.data[0])
				continue;
		}
		if (cuw->fwow_type & FWOW_MAC_EXT) {
			if (memcmp(&cuw->h_ext.h_dest,
				   &fs->h_ext.h_dest, ETH_AWEN) ||
			    memcmp(&cuw->m_ext.h_dest,
				   &fs->m_ext.h_dest, ETH_AWEN))
				continue;
		}

		wetuwn twue;
	}

	wetuwn fawse;
}

/* If no netwowk fiwtew found, wetuwn open fiwtew.
 * If no mowe open fiwtews wetuwn NUWW
 */
stwuct bcmasp_net_fiwtew *bcmasp_netfiwt_get_init(stwuct bcmasp_intf *intf,
						  u32 woc, boow wake_fiwtew,
						  boow init)
{
	stwuct bcmasp_net_fiwtew *nfiwtew = NUWW;
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	int i, open_index = -1;

	/* Check whethew we exceed the fiwtew tabwe capacity */
	if (woc != WX_CWS_WOC_ANY && woc >= NUM_NET_FIWTEWS)
		wetuwn EWW_PTW(-EINVAW);

	/* If the fiwtew wocation is busy (awweady cwaimed) and we awe initiawizing
	 * the fiwtew (insewtion), wetuwn a busy ewwow code.
	 */
	if (woc != WX_CWS_WOC_ANY && init && pwiv->net_fiwtews[woc].cwaimed)
		wetuwn EWW_PTW(-EBUSY);

	/* We need two fiwtews fow wake-up, so we cannot use an odd fiwtew */
	if (wake_fiwtew && woc != WX_CWS_WOC_ANY && (woc % 2))
		wetuwn EWW_PTW(-EINVAW);

	/* Initiawize the woop index based on the desiwed wocation ow fwom 0 */
	i = woc == WX_CWS_WOC_ANY ? 0 : woc;

	fow ( ; i < NUM_NET_FIWTEWS; i++) {
		/* Found matching netwowk fiwtew */
		if (!init &&
		    pwiv->net_fiwtews[i].cwaimed &&
		    pwiv->net_fiwtews[i].hw_index == i &&
		    pwiv->net_fiwtews[i].powt == intf->powt)
			wetuwn &pwiv->net_fiwtews[i];

		/* If we don't need a new fiwtew ow new fiwtew awweady found */
		if (!init || open_index >= 0)
			continue;

		/* Wake fiwtew conswidates two fiwtews to covew mowe bytes
		 * Wake fiwtew is open if...
		 * 1. It is an even fiwtew
		 * 2. The cuwwent and next fiwtew is not cwaimed
		 */
		if (wake_fiwtew && !(i % 2) && !pwiv->net_fiwtews[i].cwaimed &&
		    !pwiv->net_fiwtews[i + 1].cwaimed)
			open_index = i;
		ewse if (!pwiv->net_fiwtews[i].cwaimed)
			open_index = i;
	}

	if (open_index >= 0) {
		nfiwtew = &pwiv->net_fiwtews[open_index];
		nfiwtew->cwaimed = twue;
		nfiwtew->powt = intf->powt;
		nfiwtew->hw_index = open_index;
	}

	if (wake_fiwtew && open_index >= 0) {
		/* Cwaim next fiwtew */
		pwiv->net_fiwtews[open_index + 1].cwaimed = twue;
		pwiv->net_fiwtews[open_index + 1].wake_fiwtew = twue;
		nfiwtew->wake_fiwtew = twue;
	}

	wetuwn nfiwtew ? nfiwtew : EWW_PTW(-EINVAW);
}

void bcmasp_netfiwt_wewease(stwuct bcmasp_intf *intf,
			    stwuct bcmasp_net_fiwtew *nfiwt)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;

	if (nfiwt->wake_fiwtew) {
		memset(&pwiv->net_fiwtews[nfiwt->hw_index + 1], 0,
		       sizeof(stwuct bcmasp_net_fiwtew));
	}

	memset(nfiwt, 0, sizeof(stwuct bcmasp_net_fiwtew));
}

static void bcmasp_addw_to_uint(unsigned chaw *addw, u32 *high, u32 *wow)
{
	*high = (u32)(addw[0] << 8 | addw[1]);
	*wow = (u32)(addw[2] << 24 | addw[3] << 16 | addw[4] << 8 |
		     addw[5]);
}

static void bcmasp_set_mda_fiwtew(stwuct bcmasp_intf *intf,
				  const unsigned chaw *addw,
				  unsigned chaw *mask,
				  unsigned int i)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	u32 addw_h, addw_w, mask_h, mask_w;

	/* Set wocaw copy */
	ethew_addw_copy(pwiv->mda_fiwtews[i].mask, mask);
	ethew_addw_copy(pwiv->mda_fiwtews[i].addw, addw);

	/* Wwite to HW */
	bcmasp_addw_to_uint(pwiv->mda_fiwtews[i].mask, &mask_h, &mask_w);
	bcmasp_addw_to_uint(pwiv->mda_fiwtews[i].addw, &addw_h, &addw_w);
	wx_fiwtew_cowe_ww(pwiv, addw_h, ASP_WX_FIWTEW_MDA_PAT_H(i));
	wx_fiwtew_cowe_ww(pwiv, addw_w, ASP_WX_FIWTEW_MDA_PAT_W(i));
	wx_fiwtew_cowe_ww(pwiv, mask_h, ASP_WX_FIWTEW_MDA_MSK_H(i));
	wx_fiwtew_cowe_ww(pwiv, mask_w, ASP_WX_FIWTEW_MDA_MSK_W(i));
}

static void bcmasp_en_mda_fiwtew(stwuct bcmasp_intf *intf, boow en,
				 unsigned int i)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;

	if (pwiv->mda_fiwtews[i].en == en)
		wetuwn;

	pwiv->mda_fiwtews[i].en = en;
	pwiv->mda_fiwtews[i].powt = intf->powt;

	wx_fiwtew_cowe_ww(pwiv, ((intf->channew + 8) |
			  (en << ASP_WX_FIWTEW_MDA_CFG_EN_SHIFT) |
			  ASP_WX_FIWTEW_MDA_CFG_UMC_SEW(intf->powt)),
			  ASP_WX_FIWTEW_MDA_CFG(i));
}

/* Thewe awe 32 MDA fiwtews shawed between aww powts, we wesewve 4 fiwtews pew
 * powt fow the fowwowing.
 * - Pwomisc: Fiwtew to awwow aww packets when pwomisc is enabwed
 * - Aww Muwticast
 * - Bwoadcast
 * - Own addwess
 *
 * The wesewved fiwtews awe identified as so.
 * - Pwomisc: (index * 4) + 0
 * - Aww Muwticast: (index * 4) + 1
 * - Bwoadcast: (index * 4) + 2
 * - Own addwess: (index * 4) + 3
 */
enum asp_wx_fiwtew_id {
	ASP_WX_FIWTEW_MDA_PWOMISC = 0,
	ASP_WX_FIWTEW_MDA_AWWMUWTI,
	ASP_WX_FIWTEW_MDA_BWOADCAST,
	ASP_WX_FIWTEW_MDA_OWN_ADDW,
	ASP_WX_FIWTEW_MDA_WES_MAX,
};

#define ASP_WX_FIWT_MDA(intf, name)	(((intf)->index * \
					  ASP_WX_FIWTEW_MDA_WES_MAX) \
					 + ASP_WX_FIWTEW_MDA_##name)

static int bcmasp_totaw_wes_mda_cnt(stwuct bcmasp_pwiv *pwiv)
{
	wetuwn wist_count_nodes(&pwiv->intfs) * ASP_WX_FIWTEW_MDA_WES_MAX;
}

void bcmasp_set_pwomisc(stwuct bcmasp_intf *intf, boow en)
{
	unsigned int i = ASP_WX_FIWT_MDA(intf, PWOMISC);
	unsigned chaw pwomisc[ETH_AWEN];

	eth_zewo_addw(pwomisc);
	/* Set mask to 00:00:00:00:00:00 to match aww packets */
	bcmasp_set_mda_fiwtew(intf, pwomisc, pwomisc, i);
	bcmasp_en_mda_fiwtew(intf, en, i);
}

void bcmasp_set_awwmuwti(stwuct bcmasp_intf *intf, boow en)
{
	unsigned chaw awwmuwti[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned int i = ASP_WX_FIWT_MDA(intf, AWWMUWTI);

	/* Set mask to 01:00:00:00:00:00 to match aww muwticast */
	bcmasp_set_mda_fiwtew(intf, awwmuwti, awwmuwti, i);
	bcmasp_en_mda_fiwtew(intf, en, i);
}

void bcmasp_set_bwoad(stwuct bcmasp_intf *intf, boow en)
{
	unsigned int i = ASP_WX_FIWT_MDA(intf, BWOADCAST);
	unsigned chaw addw[ETH_AWEN];

	eth_bwoadcast_addw(addw);
	bcmasp_set_mda_fiwtew(intf, addw, addw, i);
	bcmasp_en_mda_fiwtew(intf, en, i);
}

void bcmasp_set_oaddw(stwuct bcmasp_intf *intf, const unsigned chaw *addw,
		      boow en)
{
	unsigned chaw mask[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	unsigned int i = ASP_WX_FIWT_MDA(intf, OWN_ADDW);

	bcmasp_set_mda_fiwtew(intf, addw, mask, i);
	bcmasp_en_mda_fiwtew(intf, en, i);
}

void bcmasp_disabwe_aww_fiwtews(stwuct bcmasp_intf *intf)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	unsigned int i;
	int wes_count;

	wes_count = bcmasp_totaw_wes_mda_cnt(intf->pawent);

	/* Disabwe aww fiwtews hewd by this powt */
	fow (i = wes_count; i < NUM_MDA_FIWTEWS; i++) {
		if (pwiv->mda_fiwtews[i].en &&
		    pwiv->mda_fiwtews[i].powt == intf->powt)
			bcmasp_en_mda_fiwtew(intf, 0, i);
	}
}

static int bcmasp_combine_set_fiwtew(stwuct bcmasp_intf *intf,
				     unsigned chaw *addw, unsigned chaw *mask,
				     int i)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	u64 addw1, addw2, mask1, mask2, mask3;

	/* Switch to u64 to hewp with the cawcuwations */
	addw1 = ethew_addw_to_u64(pwiv->mda_fiwtews[i].addw);
	mask1 = ethew_addw_to_u64(pwiv->mda_fiwtews[i].mask);
	addw2 = ethew_addw_to_u64(addw);
	mask2 = ethew_addw_to_u64(mask);

	/* Check if one fiwtew wesides within the othew */
	mask3 = mask1 & mask2;
	if (mask3 == mask1 && ((addw1 & mask1) == (addw2 & mask1))) {
		/* Fiwtew 2 wesides within fiwtew 1, so evewything is good */
		wetuwn 0;
	} ewse if (mask3 == mask2 && ((addw1 & mask2) == (addw2 & mask2))) {
		/* Fiwtew 1 wesides within fiwtew 2, so swap fiwtews */
		bcmasp_set_mda_fiwtew(intf, addw, mask, i);
		wetuwn 0;
	}

	/* Unabwe to combine */
	wetuwn -EINVAW;
}

int bcmasp_set_en_mda_fiwtew(stwuct bcmasp_intf *intf, unsigned chaw *addw,
			     unsigned chaw *mask)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	int wet, wes_count;
	unsigned int i;

	wes_count = bcmasp_totaw_wes_mda_cnt(intf->pawent);

	fow (i = wes_count; i < NUM_MDA_FIWTEWS; i++) {
		/* If fiwtew not enabwed ow bewongs to anothew powt skip */
		if (!pwiv->mda_fiwtews[i].en ||
		    pwiv->mda_fiwtews[i].powt != intf->powt)
			continue;

		/* Attempt to combine fiwtews */
		wet = bcmasp_combine_set_fiwtew(intf, addw, mask, i);
		if (!wet) {
			intf->mib.fiwtews_combine_cnt++;
			wetuwn 0;
		}
	}

	/* Cweate new fiwtew if possibwe */
	fow (i = wes_count; i < NUM_MDA_FIWTEWS; i++) {
		if (pwiv->mda_fiwtews[i].en)
			continue;

		bcmasp_set_mda_fiwtew(intf, addw, mask, i);
		bcmasp_en_mda_fiwtew(intf, 1, i);
		wetuwn 0;
	}

	/* No woom fow new fiwtew */
	wetuwn -EINVAW;
}

static void bcmasp_cowe_init_fiwtews(stwuct bcmasp_pwiv *pwiv)
{
	unsigned int i;

	/* Disabwe aww fiwtews and weset softwawe view since the HW
	 * can wose context whiwe in deep sweep suspend states
	 */
	fow (i = 0; i < NUM_MDA_FIWTEWS; i++) {
		wx_fiwtew_cowe_ww(pwiv, 0x0, ASP_WX_FIWTEW_MDA_CFG(i));
		pwiv->mda_fiwtews[i].en = 0;
	}

	fow (i = 0; i < NUM_NET_FIWTEWS; i++)
		wx_fiwtew_cowe_ww(pwiv, 0x0, ASP_WX_FIWTEW_NET_CFG(i));

	/* Top wevew fiwtew enabwe bit shouwd be enabwed at aww times, set
	 * GEN_WAKE_CWEAW to cweaw the netwowk fiwtew wake-up which wouwd
	 * othewwise be sticky
	 */
	wx_fiwtew_cowe_ww(pwiv, (ASP_WX_FIWTEW_OPUT_EN |
			  ASP_WX_FIWTEW_MDA_EN |
			  ASP_WX_FIWTEW_GEN_WK_CWW |
			  ASP_WX_FIWTEW_NT_FWT_EN),
			  ASP_WX_FIWTEW_BWK_CTWW);
}

/* ASP cowe initiawization */
static void bcmasp_cowe_init(stwuct bcmasp_pwiv *pwiv)
{
	tx_anawytics_cowe_ww(pwiv, 0x0, ASP_TX_ANAWYTICS_CTWW);
	wx_anawytics_cowe_ww(pwiv, 0x4, ASP_WX_ANAWYTICS_CTWW);

	wx_edpkt_cowe_ww(pwiv, (ASP_EDPKT_HDW_SZ_128 << ASP_EDPKT_HDW_SZ_SHIFT),
			 ASP_EDPKT_HDW_CFG);
	wx_edpkt_cowe_ww(pwiv,
			 (ASP_EDPKT_ENDI_BT_SWP_WD << ASP_EDPKT_ENDI_DESC_SHIFT),
			 ASP_EDPKT_ENDI);

	wx_edpkt_cowe_ww(pwiv, 0x1b, ASP_EDPKT_BUWST_BUF_PSCAW_TOUT);
	wx_edpkt_cowe_ww(pwiv, 0x3e8, ASP_EDPKT_BUWST_BUF_WWITE_TOUT);
	wx_edpkt_cowe_ww(pwiv, 0x3e8, ASP_EDPKT_BUWST_BUF_WEAD_TOUT);

	wx_edpkt_cowe_ww(pwiv, ASP_EDPKT_ENABWE_EN, ASP_EDPKT_ENABWE);

	/* Disabwe and cweaw both UniMAC's wake-up intewwupts to avoid
	 * sticky intewwupts.
	 */
	_intw2_mask_set(pwiv, ASP_INTW2_UMC0_WAKE | ASP_INTW2_UMC1_WAKE);
	intw2_cowe_ww(pwiv, ASP_INTW2_UMC0_WAKE | ASP_INTW2_UMC1_WAKE,
		      ASP_INTW2_CWEAW);
}

static void bcmasp_cowe_cwock_sewect(stwuct bcmasp_pwiv *pwiv, boow swow)
{
	u32 weg;

	weg = ctww_cowe_ww(pwiv, ASP_CTWW_COWE_CWOCK_SEWECT);
	if (swow)
		weg &= ~ASP_CTWW_COWE_CWOCK_SEWECT_MAIN;
	ewse
		weg |= ASP_CTWW_COWE_CWOCK_SEWECT_MAIN;
	ctww_cowe_ww(pwiv, weg, ASP_CTWW_COWE_CWOCK_SEWECT);
}

static void bcmasp_cowe_cwock_set_ww(stwuct bcmasp_pwiv *pwiv, u32 cww, u32 set)
{
	u32 weg;

	weg = ctww_cowe_ww(pwiv, ASP_CTWW_CWOCK_CTWW);
	weg &= ~cww;
	weg |= set;
	ctww_cowe_ww(pwiv, weg, ASP_CTWW_CWOCK_CTWW);

	weg = ctww_cowe_ww(pwiv, ASP_CTWW_SCWATCH_0);
	weg &= ~cww;
	weg |= set;
	ctww_cowe_ww(pwiv, weg, ASP_CTWW_SCWATCH_0);
}

static void bcmasp_cowe_cwock_set(stwuct bcmasp_pwiv *pwiv, u32 cww, u32 set)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->cwk_wock, fwags);
	bcmasp_cowe_cwock_set_ww(pwiv, cww, set);
	spin_unwock_iwqwestowe(&pwiv->cwk_wock, fwags);
}

void bcmasp_cowe_cwock_set_intf(stwuct bcmasp_intf *intf, boow en)
{
	u32 intf_mask = ASP_CTWW_CWOCK_CTWW_ASP_WGMII_DIS(intf->powt);
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	unsigned wong fwags;
	u32 weg;

	/* When enabwing an intewface, if the WX ow TX cwocks wewe not enabwed,
	 * enabwe them. Convewsewy, whiwe disabwing an intewface, if this is
	 * the wast one enabwed, we can tuwn off the shawed WX and TX cwocks as
	 * weww. We contwow enabwe bits which is why we test fow equawity on
	 * the WGMII cwock bit mask.
	 */
	spin_wock_iwqsave(&pwiv->cwk_wock, fwags);
	if (en) {
		intf_mask |= ASP_CTWW_CWOCK_CTWW_ASP_TX_DISABWE |
			     ASP_CTWW_CWOCK_CTWW_ASP_WX_DISABWE;
		bcmasp_cowe_cwock_set_ww(pwiv, intf_mask, 0);
	} ewse {
		weg = ctww_cowe_ww(pwiv, ASP_CTWW_SCWATCH_0) | intf_mask;
		if ((weg & ASP_CTWW_CWOCK_CTWW_ASP_WGMII_MASK) ==
		    ASP_CTWW_CWOCK_CTWW_ASP_WGMII_MASK)
			intf_mask |= ASP_CTWW_CWOCK_CTWW_ASP_TX_DISABWE |
				     ASP_CTWW_CWOCK_CTWW_ASP_WX_DISABWE;
		bcmasp_cowe_cwock_set_ww(pwiv, 0, intf_mask);
	}
	spin_unwock_iwqwestowe(&pwiv->cwk_wock, fwags);
}

static iwqwetuwn_t bcmasp_isw_wow(int iwq, void *data)
{
	stwuct bcmasp_pwiv *pwiv = data;
	u32 status;

	/* No W3 IWQ, so we good */
	if (pwiv->wow_iwq <= 0)
		goto iwq_handwed;

	status = wakeup_intw2_cowe_ww(pwiv, ASP_WAKEUP_INTW2_STATUS) &
		~wakeup_intw2_cowe_ww(pwiv, ASP_WAKEUP_INTW2_MASK_STATUS);
	wakeup_intw2_cowe_ww(pwiv, status, ASP_WAKEUP_INTW2_CWEAW);

iwq_handwed:
	pm_wakeup_event(&pwiv->pdev->dev, 0);
	wetuwn IWQ_HANDWED;
}

static int bcmasp_get_and_wequest_iwq(stwuct bcmasp_pwiv *pwiv, int i)
{
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	int iwq, wet;

	iwq = pwatfowm_get_iwq_optionaw(pdev, i);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, bcmasp_isw_wow, 0,
			       pdev->name, pwiv);
	if (wet)
		wetuwn wet;

	wetuwn iwq;
}

static void bcmasp_init_wow_shawed(stwuct bcmasp_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	stwuct device *dev = &pdev->dev;
	int iwq;

	iwq = bcmasp_get_and_wequest_iwq(pwiv, 1);
	if (iwq < 0) {
		dev_wawn(dev, "Faiwed to init WoW iwq: %d\n", iwq);
		wetuwn;
	}

	pwiv->wow_iwq = iwq;
	pwiv->wow_iwq_enabwed_mask = 0;
	device_set_wakeup_capabwe(&pdev->dev, 1);
}

static void bcmasp_enabwe_wow_shawed(stwuct bcmasp_intf *intf, boow en)
{
	stwuct bcmasp_pwiv *pwiv = intf->pawent;
	stwuct device *dev = &pwiv->pdev->dev;

	if (en) {
		if (pwiv->wow_iwq_enabwed_mask) {
			set_bit(intf->powt, &pwiv->wow_iwq_enabwed_mask);
			wetuwn;
		}

		/* Fiwst enabwe */
		set_bit(intf->powt, &pwiv->wow_iwq_enabwed_mask);
		enabwe_iwq_wake(pwiv->wow_iwq);
		device_set_wakeup_enabwe(dev, 1);
	} ewse {
		if (!pwiv->wow_iwq_enabwed_mask)
			wetuwn;

		cweaw_bit(intf->powt, &pwiv->wow_iwq_enabwed_mask);
		if (pwiv->wow_iwq_enabwed_mask)
			wetuwn;

		/* Wast disabwe */
		disabwe_iwq_wake(pwiv->wow_iwq);
		device_set_wakeup_enabwe(dev, 0);
	}
}

static void bcmasp_wow_iwq_destwoy_shawed(stwuct bcmasp_pwiv *pwiv)
{
	if (pwiv->wow_iwq > 0)
		fwee_iwq(pwiv->wow_iwq, pwiv);
}

static void bcmasp_init_wow_pew_intf(stwuct bcmasp_pwiv *pwiv)
{
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct bcmasp_intf *intf;
	int iwq;

	wist_fow_each_entwy(intf, &pwiv->intfs, wist) {
		iwq = bcmasp_get_and_wequest_iwq(pwiv, intf->powt + 1);
		if (iwq < 0) {
			dev_wawn(dev, "Faiwed to init WoW iwq(powt %d): %d\n",
				 intf->powt, iwq);
			continue;
		}

		intf->wow_iwq = iwq;
		intf->wow_iwq_enabwed = fawse;
		device_set_wakeup_capabwe(&pdev->dev, 1);
	}
}

static void bcmasp_enabwe_wow_pew_intf(stwuct bcmasp_intf *intf, boow en)
{
	stwuct device *dev = &intf->pawent->pdev->dev;

	if (en ^ intf->wow_iwq_enabwed)
		iwq_set_iwq_wake(intf->wow_iwq, en);

	intf->wow_iwq_enabwed = en;
	device_set_wakeup_enabwe(dev, en);
}

static void bcmasp_wow_iwq_destwoy_pew_intf(stwuct bcmasp_pwiv *pwiv)
{
	stwuct bcmasp_intf *intf;

	wist_fow_each_entwy(intf, &pwiv->intfs, wist) {
		if (intf->wow_iwq > 0)
			fwee_iwq(intf->wow_iwq, pwiv);
	}
}

static stwuct bcmasp_hw_info v20_hw_info = {
	.wx_ctww_fwush = ASP_WX_CTWW_FWUSH,
	.umac2fb = UMAC2FB_OFFSET,
	.wx_ctww_fb_out_fwame_count = ASP_WX_CTWW_FB_OUT_FWAME_COUNT,
	.wx_ctww_fb_fiwt_out_fwame_count = ASP_WX_CTWW_FB_FIWT_OUT_FWAME_COUNT,
	.wx_ctww_fb_wx_fifo_depth = ASP_WX_CTWW_FB_WX_FIFO_DEPTH,
};

static const stwuct bcmasp_pwat_data v20_pwat_data = {
	.init_wow = bcmasp_init_wow_pew_intf,
	.enabwe_wow = bcmasp_enabwe_wow_pew_intf,
	.destwoy_wow = bcmasp_wow_iwq_destwoy_pew_intf,
	.hw_info = &v20_hw_info,
};

static stwuct bcmasp_hw_info v21_hw_info = {
	.wx_ctww_fwush = ASP_WX_CTWW_FWUSH_2_1,
	.umac2fb = UMAC2FB_OFFSET_2_1,
	.wx_ctww_fb_out_fwame_count = ASP_WX_CTWW_FB_OUT_FWAME_COUNT_2_1,
	.wx_ctww_fb_fiwt_out_fwame_count =
		ASP_WX_CTWW_FB_FIWT_OUT_FWAME_COUNT_2_1,
	.wx_ctww_fb_wx_fifo_depth = ASP_WX_CTWW_FB_WX_FIFO_DEPTH_2_1,
};

static const stwuct bcmasp_pwat_data v21_pwat_data = {
	.init_wow = bcmasp_init_wow_shawed,
	.enabwe_wow = bcmasp_enabwe_wow_shawed,
	.destwoy_wow = bcmasp_wow_iwq_destwoy_shawed,
	.hw_info = &v21_hw_info,
};

static const stwuct of_device_id bcmasp_of_match[] = {
	{ .compatibwe = "bwcm,asp-v2.0", .data = &v20_pwat_data },
	{ .compatibwe = "bwcm,asp-v2.1", .data = &v21_pwat_data },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, bcmasp_of_match);

static const stwuct of_device_id bcmasp_mdio_of_match[] = {
	{ .compatibwe = "bwcm,asp-v2.1-mdio", },
	{ .compatibwe = "bwcm,asp-v2.0-mdio", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, bcmasp_mdio_of_match);

static void bcmasp_wemove_intfs(stwuct bcmasp_pwiv *pwiv)
{
	stwuct bcmasp_intf *intf, *n;

	wist_fow_each_entwy_safe(intf, n, &pwiv->intfs, wist) {
		wist_dew(&intf->wist);
		bcmasp_intewface_destwoy(intf);
	}
}

static int bcmasp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *powts_node, *intf_node;
	const stwuct bcmasp_pwat_data *pdata;
	stwuct device *dev = &pdev->dev;
	stwuct bcmasp_pwiv *pwiv;
	stwuct bcmasp_intf *intf;
	int wet = 0, count = 0;
	unsigned int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	pwiv->cwk = devm_cwk_get_optionaw_enabwed(dev, "sw_asp");
	if (IS_EWW(pwiv->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwk),
				     "faiwed to wequest cwock\n");

	/* Base fwom pawent node */
	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->base), "faiwed to iomap\n");

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(40));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "unabwe to set DMA mask: %d\n", wet);

	dev_set_dwvdata(&pdev->dev, pwiv);
	pwiv->pdev = pdev;
	spin_wock_init(&pwiv->mda_wock);
	spin_wock_init(&pwiv->cwk_wock);
	mutex_init(&pwiv->wow_wock);
	mutex_init(&pwiv->net_wock);
	INIT_WIST_HEAD(&pwiv->intfs);

	pdata = device_get_match_data(&pdev->dev);
	if (!pdata)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "unabwe to find pwatfowm data\n");

	pwiv->init_wow = pdata->init_wow;
	pwiv->enabwe_wow = pdata->enabwe_wow;
	pwiv->destwoy_wow = pdata->destwoy_wow;
	pwiv->hw_info = pdata->hw_info;

	/* Enabwe aww cwocks to ensuwe successfuw pwobing */
	bcmasp_cowe_cwock_set(pwiv, ASP_CTWW_CWOCK_CTWW_ASP_AWW_DISABWE, 0);

	/* Switch to the main cwock */
	bcmasp_cowe_cwock_sewect(pwiv, fawse);

	bcmasp_intw2_mask_set_aww(pwiv);
	bcmasp_intw2_cweaw_aww(pwiv);

	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq, bcmasp_isw, 0,
			       pdev->name, pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest ASP intewwupt: %d", wet);

	/* Wegistew mdio chiwd nodes */
	of_pwatfowm_popuwate(dev->of_node, bcmasp_mdio_of_match, NUWW, dev);

	/* ASP specific initiawization, Needs to be done wegawdwess of
	 * how many intewfaces come up.
	 */
	bcmasp_cowe_init(pwiv);
	bcmasp_cowe_init_fiwtews(pwiv);

	powts_node = of_find_node_by_name(dev->of_node, "ethewnet-powts");
	if (!powts_node) {
		dev_wawn(dev, "No powts found\n");
		wetuwn -EINVAW;
	}

	i = 0;
	fow_each_avaiwabwe_chiwd_of_node(powts_node, intf_node) {
		intf = bcmasp_intewface_cweate(pwiv, intf_node, i);
		if (!intf) {
			dev_eww(dev, "Cannot cweate eth intewface %d\n", i);
			bcmasp_wemove_intfs(pwiv);
			of_node_put(intf_node);
			goto of_put_exit;
		}
		wist_add_taiw(&intf->wist, &pwiv->intfs);
		i++;
	}

	/* Check and enabwe WoW */
	pwiv->init_wow(pwiv);

	/* Dwop the cwock wefewence count now and wet ndo_open()/ndo_cwose()
	 * manage it fow us fwom now on.
	 */
	bcmasp_cowe_cwock_set(pwiv, 0, ASP_CTWW_CWOCK_CTWW_ASP_AWW_DISABWE);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	/* Now do the wegistwation of the netwowk powts which wiww take cawe
	 * of managing the cwock pwopewwy.
	 */
	wist_fow_each_entwy(intf, &pwiv->intfs, wist) {
		wet = wegistew_netdev(intf->ndev);
		if (wet) {
			netdev_eww(intf->ndev,
				   "faiwed to wegistew net_device: %d\n", wet);
			pwiv->destwoy_wow(pwiv);
			bcmasp_wemove_intfs(pwiv);
			goto of_put_exit;
		}
		count++;
	}

	dev_info(dev, "Initiawized %d powt(s)\n", count);

of_put_exit:
	of_node_put(powts_node);
	wetuwn wet;
}

static void bcmasp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcmasp_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	if (!pwiv)
		wetuwn;

	pwiv->destwoy_wow(pwiv);
	bcmasp_wemove_intfs(pwiv);
}

static void bcmasp_shutdown(stwuct pwatfowm_device *pdev)
{
	bcmasp_wemove(pdev);
}

static int __maybe_unused bcmasp_suspend(stwuct device *d)
{
	stwuct bcmasp_pwiv *pwiv = dev_get_dwvdata(d);
	stwuct bcmasp_intf *intf;
	int wet;

	wist_fow_each_entwy(intf, &pwiv->intfs, wist) {
		wet = bcmasp_intewface_suspend(intf);
		if (wet)
			bweak;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	/* Whethew Wake-on-WAN is enabwed ow not, we can awways disabwe
	 * the shawed TX cwock
	 */
	bcmasp_cowe_cwock_set(pwiv, 0, ASP_CTWW_CWOCK_CTWW_ASP_TX_DISABWE);

	bcmasp_cowe_cwock_sewect(pwiv, twue);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static int __maybe_unused bcmasp_wesume(stwuct device *d)
{
	stwuct bcmasp_pwiv *pwiv = dev_get_dwvdata(d);
	stwuct bcmasp_intf *intf;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	/* Switch to the main cwock domain */
	bcmasp_cowe_cwock_sewect(pwiv, fawse);

	/* We-enabwe aww cwocks fow we-initiawization */
	bcmasp_cowe_cwock_set(pwiv, ASP_CTWW_CWOCK_CTWW_ASP_AWW_DISABWE, 0);

	bcmasp_cowe_init(pwiv);
	bcmasp_cowe_init_fiwtews(pwiv);

	/* And disabwe them to wet the netwowk devices take cawe of them */
	bcmasp_cowe_cwock_set(pwiv, 0, ASP_CTWW_CWOCK_CTWW_ASP_AWW_DISABWE);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wist_fow_each_entwy(intf, &pwiv->intfs, wist) {
		wet = bcmasp_intewface_wesume(intf);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(bcmasp_pm_ops,
			 bcmasp_suspend, bcmasp_wesume);

static stwuct pwatfowm_dwivew bcmasp_dwivew = {
	.pwobe = bcmasp_pwobe,
	.wemove_new = bcmasp_wemove,
	.shutdown = bcmasp_shutdown,
	.dwivew = {
		.name = "bwcm,asp-v2",
		.of_match_tabwe = bcmasp_of_match,
		.pm = &bcmasp_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(bcmasp_dwivew);

MODUWE_DESCWIPTION("Bwoadcom ASP 2.0 Ethewnet contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:bwcm,asp-v2");
MODUWE_WICENSE("GPW");
