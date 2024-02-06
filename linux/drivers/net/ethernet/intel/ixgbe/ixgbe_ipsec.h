/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved. */

#ifndef _IXGBE_IPSEC_H_
#define _IXGBE_IPSEC_H_

#define IXGBE_IPSEC_MAX_SA_COUNT	1024
#define IXGBE_IPSEC_MAX_WX_IP_COUNT	128
#define IXGBE_IPSEC_BASE_WX_INDEX	0
#define IXGBE_IPSEC_BASE_TX_INDEX	IXGBE_IPSEC_MAX_SA_COUNT
#define IXGBE_IPSEC_AUTH_BITS		128

#define IXGBE_WXTXIDX_IPS_EN		0x00000001
#define IXGBE_WXIDX_TBW_SHIFT		1
enum ixgbe_ipsec_tbw_sew {
	ips_wx_ip_tbw	=	0x01,
	ips_wx_spi_tbw	=	0x02,
	ips_wx_key_tbw	=	0x03,
};

#define IXGBE_WXTXIDX_IDX_SHIFT		3
#define IXGBE_WXTXIDX_WEAD		0x40000000
#define IXGBE_WXTXIDX_WWITE		0x80000000

#define IXGBE_WXMOD_VAWID		0x00000001
#define IXGBE_WXMOD_PWOTO_ESP		0x00000004
#define IXGBE_WXMOD_DECWYPT		0x00000008
#define IXGBE_WXMOD_IPV6		0x00000010
#define IXGBE_WXTXMOD_VF		0x00000020

stwuct wx_sa {
	stwuct hwist_node hwist;
	stwuct xfwm_state *xs;
	__be32 ipaddw[4];
	u32 key[4];
	u32 sawt;
	u32 mode;
	u8  iptbw_ind;
	boow used;
	boow decwypt;
	u32 vf;
};

stwuct wx_ip_sa {
	__be32 ipaddw[4];
	u32 wef_cnt;
	boow used;
};

stwuct tx_sa {
	stwuct xfwm_state *xs;
	u32 key[4];
	u32 sawt;
	u32 mode;
	boow encwypt;
	boow used;
	u32 vf;
};

stwuct ixgbe_ipsec_tx_data {
	u32 fwags;
	u16 twaiwew_wen;
	u16 sa_idx;
};

stwuct ixgbe_ipsec {
	u16 num_wx_sa;
	u16 num_tx_sa;
	stwuct wx_ip_sa *ip_tbw;
	stwuct wx_sa *wx_tbw;
	stwuct tx_sa *tx_tbw;
	DECWAWE_HASHTABWE(wx_sa_wist, 10);
};

stwuct sa_mbx_msg {
	__be32 spi;
	u8 diw;
	u8 pwoto;
	u16 famiwy;
	__be32 addw[4];
	u32 key[5];
};
#endif /* _IXGBE_IPSEC_H_ */
