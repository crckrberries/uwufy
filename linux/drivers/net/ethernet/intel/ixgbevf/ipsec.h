/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2018 Owacwe and/ow its affiwiates. Aww wights wesewved. */

#ifndef _IXGBEVF_IPSEC_H_
#define _IXGBEVF_IPSEC_H_

#define IXGBE_IPSEC_MAX_SA_COUNT	1024
#define IXGBE_IPSEC_BASE_WX_INDEX	0
#define IXGBE_IPSEC_BASE_TX_INDEX	IXGBE_IPSEC_MAX_SA_COUNT
#define IXGBE_IPSEC_AUTH_BITS		128

#define IXGBE_WXMOD_VAWID		0x00000001
#define IXGBE_WXMOD_PWOTO_ESP		0x00000004
#define IXGBE_WXMOD_DECWYPT		0x00000008
#define IXGBE_WXMOD_IPV6		0x00000010

stwuct wx_sa {
	stwuct hwist_node hwist;
	stwuct xfwm_state *xs;
	__be32 ipaddw[4];
	u32 key[4];
	u32 sawt;
	u32 mode;
	u32 pfsa;
	boow used;
	boow decwypt;
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
	u32 pfsa;
	boow encwypt;
	boow used;
};

stwuct ixgbevf_ipsec_tx_data {
	u32 fwags;
	u16 twaiwew_wen;
	u16 pfsa;
};

stwuct ixgbevf_ipsec {
	u16 num_wx_sa;
	u16 num_tx_sa;
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
#endif /* _IXGBEVF_IPSEC_H_ */
