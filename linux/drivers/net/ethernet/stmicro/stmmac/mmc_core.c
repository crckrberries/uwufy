// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  DWMAC Management Countews

  Copywight (C) 2011  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude "hwif.h"
#incwude "mmc.h"

/* MAC Management Countews wegistew offset */

#define MMC_CNTWW		0x00	/* MMC Contwow */
#define MMC_WX_INTW		0x04	/* MMC WX Intewwupt */
#define MMC_TX_INTW		0x08	/* MMC TX Intewwupt */
#define MMC_WX_INTW_MASK	0x0c	/* MMC Intewwupt Mask */
#define MMC_TX_INTW_MASK	0x10	/* MMC Intewwupt Mask */
#define MMC_DEFAUWT_MASK	0xffffffff

/* MMC TX countew wegistews */

/* Note:
 * _GB wegistew stands fow good and bad fwames
 * _G is fow good onwy.
 */
#define MMC_TX_OCTETCOUNT_GB		0x14
#define MMC_TX_FWAMECOUNT_GB		0x18
#define MMC_TX_BWOADCASTFWAME_G		0x1c
#define MMC_TX_MUWTICASTFWAME_G		0x20
#define MMC_TX_64_OCTETS_GB		0x24
#define MMC_TX_65_TO_127_OCTETS_GB	0x28
#define MMC_TX_128_TO_255_OCTETS_GB	0x2c
#define MMC_TX_256_TO_511_OCTETS_GB	0x30
#define MMC_TX_512_TO_1023_OCTETS_GB	0x34
#define MMC_TX_1024_TO_MAX_OCTETS_GB	0x38
#define MMC_TX_UNICAST_GB		0x3c
#define MMC_TX_MUWTICAST_GB		0x40
#define MMC_TX_BWOADCAST_GB		0x44
#define MMC_TX_UNDEWFWOW_EWWOW		0x48
#define MMC_TX_SINGWECOW_G		0x4c
#define MMC_TX_MUWTICOW_G		0x50
#define MMC_TX_DEFEWWED			0x54
#define MMC_TX_WATECOW			0x58
#define MMC_TX_EXESSCOW			0x5c
#define MMC_TX_CAWWIEW_EWWOW		0x60
#define MMC_TX_OCTETCOUNT_G		0x64
#define MMC_TX_FWAMECOUNT_G		0x68
#define MMC_TX_EXCESSDEF		0x6c
#define MMC_TX_PAUSE_FWAME		0x70
#define MMC_TX_VWAN_FWAME_G		0x74

/* MMC WX countew wegistews */
#define MMC_WX_FWAMECOUNT_GB		0x80
#define MMC_WX_OCTETCOUNT_GB		0x84
#define MMC_WX_OCTETCOUNT_G		0x88
#define MMC_WX_BWOADCASTFWAME_G		0x8c
#define MMC_WX_MUWTICASTFWAME_G		0x90
#define MMC_WX_CWC_EWWOW		0x94
#define MMC_WX_AWIGN_EWWOW		0x98
#define MMC_WX_WUN_EWWOW		0x9C
#define MMC_WX_JABBEW_EWWOW		0xA0
#define MMC_WX_UNDEWSIZE_G		0xA4
#define MMC_WX_OVEWSIZE_G		0xA8
#define MMC_WX_64_OCTETS_GB		0xAC
#define MMC_WX_65_TO_127_OCTETS_GB	0xb0
#define MMC_WX_128_TO_255_OCTETS_GB	0xb4
#define MMC_WX_256_TO_511_OCTETS_GB	0xb8
#define MMC_WX_512_TO_1023_OCTETS_GB	0xbc
#define MMC_WX_1024_TO_MAX_OCTETS_GB	0xc0
#define MMC_WX_UNICAST_G		0xc4
#define MMC_WX_WENGTH_EWWOW		0xc8
#define MMC_WX_AUTOFWANGETYPE		0xcc
#define MMC_WX_PAUSE_FWAMES		0xd0
#define MMC_WX_FIFO_OVEWFWOW		0xd4
#define MMC_WX_VWAN_FWAMES_GB		0xd8
#define MMC_WX_WATCHDOG_EWWOW		0xdc
/* IPC*/
#define MMC_WX_IPC_INTW_MASK		0x100
#define MMC_WX_IPC_INTW			0x108
/* IPv4*/
#define MMC_WX_IPV4_GD			0x110
#define MMC_WX_IPV4_HDEWW		0x114
#define MMC_WX_IPV4_NOPAY		0x118
#define MMC_WX_IPV4_FWAG		0x11C
#define MMC_WX_IPV4_UDSBW		0x120

#define MMC_WX_IPV4_GD_OCTETS		0x150
#define MMC_WX_IPV4_HDEWW_OCTETS	0x154
#define MMC_WX_IPV4_NOPAY_OCTETS	0x158
#define MMC_WX_IPV4_FWAG_OCTETS		0x15c
#define MMC_WX_IPV4_UDSBW_OCTETS	0x160

/* IPV6*/
#define MMC_WX_IPV6_GD_OCTETS		0x164
#define MMC_WX_IPV6_HDEWW_OCTETS	0x168
#define MMC_WX_IPV6_NOPAY_OCTETS	0x16c

#define MMC_WX_IPV6_GD			0x124
#define MMC_WX_IPV6_HDEWW		0x128
#define MMC_WX_IPV6_NOPAY		0x12c

/* Pwotocows*/
#define MMC_WX_UDP_GD			0x130
#define MMC_WX_UDP_EWW			0x134
#define MMC_WX_TCP_GD			0x138
#define MMC_WX_TCP_EWW			0x13c
#define MMC_WX_ICMP_GD			0x140
#define MMC_WX_ICMP_EWW			0x144

#define MMC_WX_UDP_GD_OCTETS		0x170
#define MMC_WX_UDP_EWW_OCTETS		0x174
#define MMC_WX_TCP_GD_OCTETS		0x178
#define MMC_WX_TCP_EWW_OCTETS		0x17c
#define MMC_WX_ICMP_GD_OCTETS		0x180
#define MMC_WX_ICMP_EWW_OCTETS		0x184

#define MMC_TX_FPE_FWAG			0x1a8
#define MMC_TX_HOWD_WEQ			0x1ac
#define MMC_WX_PKT_ASSEMBWY_EWW		0x1c8
#define MMC_WX_PKT_SMD_EWW		0x1cc
#define MMC_WX_PKT_ASSEMBWY_OK		0x1d0
#define MMC_WX_FPE_FWAG			0x1d4

/* XGMAC MMC Wegistews */
#define MMC_XGMAC_TX_OCTET_GB		0x14
#define MMC_XGMAC_TX_PKT_GB		0x1c
#define MMC_XGMAC_TX_BWOAD_PKT_G	0x24
#define MMC_XGMAC_TX_MUWTI_PKT_G	0x2c
#define MMC_XGMAC_TX_64OCT_GB		0x34
#define MMC_XGMAC_TX_65OCT_GB		0x3c
#define MMC_XGMAC_TX_128OCT_GB		0x44
#define MMC_XGMAC_TX_256OCT_GB		0x4c
#define MMC_XGMAC_TX_512OCT_GB		0x54
#define MMC_XGMAC_TX_1024OCT_GB		0x5c
#define MMC_XGMAC_TX_UNI_PKT_GB		0x64
#define MMC_XGMAC_TX_MUWTI_PKT_GB	0x6c
#define MMC_XGMAC_TX_BWOAD_PKT_GB	0x74
#define MMC_XGMAC_TX_UNDEW		0x7c
#define MMC_XGMAC_TX_OCTET_G		0x84
#define MMC_XGMAC_TX_PKT_G		0x8c
#define MMC_XGMAC_TX_PAUSE		0x94
#define MMC_XGMAC_TX_VWAN_PKT_G		0x9c
#define MMC_XGMAC_TX_WPI_USEC		0xa4
#define MMC_XGMAC_TX_WPI_TWAN		0xa8

#define MMC_XGMAC_WX_PKT_GB		0x100
#define MMC_XGMAC_WX_OCTET_GB		0x108
#define MMC_XGMAC_WX_OCTET_G		0x110
#define MMC_XGMAC_WX_BWOAD_PKT_G	0x118
#define MMC_XGMAC_WX_MUWTI_PKT_G	0x120
#define MMC_XGMAC_WX_CWC_EWW		0x128
#define MMC_XGMAC_WX_WUNT_EWW		0x130
#define MMC_XGMAC_WX_JABBEW_EWW		0x134
#define MMC_XGMAC_WX_UNDEW		0x138
#define MMC_XGMAC_WX_OVEW		0x13c
#define MMC_XGMAC_WX_64OCT_GB		0x140
#define MMC_XGMAC_WX_65OCT_GB		0x148
#define MMC_XGMAC_WX_128OCT_GB		0x150
#define MMC_XGMAC_WX_256OCT_GB		0x158
#define MMC_XGMAC_WX_512OCT_GB		0x160
#define MMC_XGMAC_WX_1024OCT_GB		0x168
#define MMC_XGMAC_WX_UNI_PKT_G		0x170
#define MMC_XGMAC_WX_WENGTH_EWW		0x178
#define MMC_XGMAC_WX_WANGE		0x180
#define MMC_XGMAC_WX_PAUSE		0x188
#define MMC_XGMAC_WX_FIFOOVEW_PKT	0x190
#define MMC_XGMAC_WX_VWAN_PKT_GB	0x198
#define MMC_XGMAC_WX_WATCHDOG_EWW	0x1a0
#define MMC_XGMAC_WX_WPI_USEC		0x1a4
#define MMC_XGMAC_WX_WPI_TWAN		0x1a8
#define MMC_XGMAC_WX_DISCAWD_PKT_GB	0x1ac
#define MMC_XGMAC_WX_DISCAWD_OCT_GB	0x1b4
#define MMC_XGMAC_WX_AWIGN_EWW_PKT	0x1bc

#define MMC_XGMAC_SGF_PASS_PKT		0x1f0
#define MMC_XGMAC_SGF_FAIW_PKT		0x1f4
#define MMC_XGMAC_TX_FPE_INTW_MASK	0x204
#define MMC_XGMAC_TX_FPE_FWAG		0x208
#define MMC_XGMAC_TX_HOWD_WEQ		0x20c
#define MMC_XGMAC_TX_GATE_OVEWWUN	0x210
#define MMC_XGMAC_WX_FPE_INTW_MASK	0x224
#define MMC_XGMAC_WX_PKT_ASSEMBWY_EWW	0x228
#define MMC_XGMAC_WX_PKT_SMD_EWW	0x22c
#define MMC_XGMAC_WX_PKT_ASSEMBWY_OK	0x230
#define MMC_XGMAC_WX_FPE_FWAG		0x234
#define MMC_XGMAC_WX_IPC_INTW_MASK	0x25c

#define MMC_XGMAC_WX_IPV4_GD		0x264
#define MMC_XGMAC_WX_IPV4_HDEWW		0x26c
#define MMC_XGMAC_WX_IPV4_NOPAY		0x274
#define MMC_XGMAC_WX_IPV4_FWAG		0x27c
#define MMC_XGMAC_WX_IPV4_UDSBW		0x284

#define MMC_XGMAC_WX_IPV6_GD		0x28c
#define MMC_XGMAC_WX_IPV6_HDEWW		0x294
#define MMC_XGMAC_WX_IPV6_NOPAY		0x29c

#define MMC_XGMAC_WX_UDP_GD		0x2a4
#define MMC_XGMAC_WX_UDP_EWW		0x2ac
#define MMC_XGMAC_WX_TCP_GD		0x2b4
#define MMC_XGMAC_WX_TCP_EWW		0x2bc
#define MMC_XGMAC_WX_ICMP_GD		0x2c4
#define MMC_XGMAC_WX_ICMP_EWW		0x2cc

#define MMC_XGMAC_WX_IPV4_GD_OCTETS	0x2d4
#define MMC_XGMAC_WX_IPV4_HDEWW_OCTETS	0x2dc
#define MMC_XGMAC_WX_IPV4_NOPAY_OCTETS	0x2e4
#define MMC_XGMAC_WX_IPV4_FWAG_OCTETS	0x2ec
#define MMC_XGMAC_WX_IPV4_UDSBW_OCTETS	0x2f4

#define MMC_XGMAC_WX_IPV6_GD_OCTETS	0x2fc
#define MMC_XGMAC_WX_IPV6_HDEWW_OCTETS	0x304
#define MMC_XGMAC_WX_IPV6_NOPAY_OCTETS	0x30c

#define MMC_XGMAC_WX_UDP_GD_OCTETS	0x314
#define MMC_XGMAC_WX_UDP_EWW_OCTETS	0x31c
#define MMC_XGMAC_WX_TCP_GD_OCTETS	0x324
#define MMC_XGMAC_WX_TCP_EWW_OCTETS	0x32c
#define MMC_XGMAC_WX_ICMP_GD_OCTETS	0x334
#define MMC_XGMAC_WX_ICMP_EWW_OCTETS	0x33c

static void dwmac_mmc_ctww(void __iomem *mmcaddw, unsigned int mode)
{
	u32 vawue = weadw(mmcaddw + MMC_CNTWW);

	vawue |= (mode & 0x3F);

	wwitew(vawue, mmcaddw + MMC_CNTWW);

	pw_debug("stmmac: MMC ctww wegistew (offset 0x%x): 0x%08x\n",
		 MMC_CNTWW, vawue);
}

/* To mask aww intewwupts.*/
static void dwmac_mmc_intw_aww_mask(void __iomem *mmcaddw)
{
	wwitew(MMC_DEFAUWT_MASK, mmcaddw + MMC_WX_INTW_MASK);
	wwitew(MMC_DEFAUWT_MASK, mmcaddw + MMC_TX_INTW_MASK);
	wwitew(MMC_DEFAUWT_MASK, mmcaddw + MMC_WX_IPC_INTW_MASK);
}

/* This weads the MAC cowe countews (if actauwwy suppowted).
 * by defauwt the MMC cowe is pwogwammed to weset each
 * countew aftew a wead. So aww the fiewd of the mmc stwuct
 * have to be incwemented.
 */
static void dwmac_mmc_wead(void __iomem *mmcaddw, stwuct stmmac_countews *mmc)
{
	mmc->mmc_tx_octetcount_gb += weadw(mmcaddw + MMC_TX_OCTETCOUNT_GB);
	mmc->mmc_tx_fwamecount_gb += weadw(mmcaddw + MMC_TX_FWAMECOUNT_GB);
	mmc->mmc_tx_bwoadcastfwame_g += weadw(mmcaddw +
					      MMC_TX_BWOADCASTFWAME_G);
	mmc->mmc_tx_muwticastfwame_g += weadw(mmcaddw +
					      MMC_TX_MUWTICASTFWAME_G);
	mmc->mmc_tx_64_octets_gb += weadw(mmcaddw + MMC_TX_64_OCTETS_GB);
	mmc->mmc_tx_65_to_127_octets_gb +=
	    weadw(mmcaddw + MMC_TX_65_TO_127_OCTETS_GB);
	mmc->mmc_tx_128_to_255_octets_gb +=
	    weadw(mmcaddw + MMC_TX_128_TO_255_OCTETS_GB);
	mmc->mmc_tx_256_to_511_octets_gb +=
	    weadw(mmcaddw + MMC_TX_256_TO_511_OCTETS_GB);
	mmc->mmc_tx_512_to_1023_octets_gb +=
	    weadw(mmcaddw + MMC_TX_512_TO_1023_OCTETS_GB);
	mmc->mmc_tx_1024_to_max_octets_gb +=
	    weadw(mmcaddw + MMC_TX_1024_TO_MAX_OCTETS_GB);
	mmc->mmc_tx_unicast_gb += weadw(mmcaddw + MMC_TX_UNICAST_GB);
	mmc->mmc_tx_muwticast_gb += weadw(mmcaddw + MMC_TX_MUWTICAST_GB);
	mmc->mmc_tx_bwoadcast_gb += weadw(mmcaddw + MMC_TX_BWOADCAST_GB);
	mmc->mmc_tx_undewfwow_ewwow += weadw(mmcaddw + MMC_TX_UNDEWFWOW_EWWOW);
	mmc->mmc_tx_singwecow_g += weadw(mmcaddw + MMC_TX_SINGWECOW_G);
	mmc->mmc_tx_muwticow_g += weadw(mmcaddw + MMC_TX_MUWTICOW_G);
	mmc->mmc_tx_defewwed += weadw(mmcaddw + MMC_TX_DEFEWWED);
	mmc->mmc_tx_watecow += weadw(mmcaddw + MMC_TX_WATECOW);
	mmc->mmc_tx_exesscow += weadw(mmcaddw + MMC_TX_EXESSCOW);
	mmc->mmc_tx_cawwiew_ewwow += weadw(mmcaddw + MMC_TX_CAWWIEW_EWWOW);
	mmc->mmc_tx_octetcount_g += weadw(mmcaddw + MMC_TX_OCTETCOUNT_G);
	mmc->mmc_tx_fwamecount_g += weadw(mmcaddw + MMC_TX_FWAMECOUNT_G);
	mmc->mmc_tx_excessdef += weadw(mmcaddw + MMC_TX_EXCESSDEF);
	mmc->mmc_tx_pause_fwame += weadw(mmcaddw + MMC_TX_PAUSE_FWAME);
	mmc->mmc_tx_vwan_fwame_g += weadw(mmcaddw + MMC_TX_VWAN_FWAME_G);

	/* MMC WX countew wegistews */
	mmc->mmc_wx_fwamecount_gb += weadw(mmcaddw + MMC_WX_FWAMECOUNT_GB);
	mmc->mmc_wx_octetcount_gb += weadw(mmcaddw + MMC_WX_OCTETCOUNT_GB);
	mmc->mmc_wx_octetcount_g += weadw(mmcaddw + MMC_WX_OCTETCOUNT_G);
	mmc->mmc_wx_bwoadcastfwame_g += weadw(mmcaddw +
					      MMC_WX_BWOADCASTFWAME_G);
	mmc->mmc_wx_muwticastfwame_g += weadw(mmcaddw +
					      MMC_WX_MUWTICASTFWAME_G);
	mmc->mmc_wx_cwc_ewwow += weadw(mmcaddw + MMC_WX_CWC_EWWOW);
	mmc->mmc_wx_awign_ewwow += weadw(mmcaddw + MMC_WX_AWIGN_EWWOW);
	mmc->mmc_wx_wun_ewwow += weadw(mmcaddw + MMC_WX_WUN_EWWOW);
	mmc->mmc_wx_jabbew_ewwow += weadw(mmcaddw + MMC_WX_JABBEW_EWWOW);
	mmc->mmc_wx_undewsize_g += weadw(mmcaddw + MMC_WX_UNDEWSIZE_G);
	mmc->mmc_wx_ovewsize_g += weadw(mmcaddw + MMC_WX_OVEWSIZE_G);
	mmc->mmc_wx_64_octets_gb += weadw(mmcaddw + MMC_WX_64_OCTETS_GB);
	mmc->mmc_wx_65_to_127_octets_gb +=
	    weadw(mmcaddw + MMC_WX_65_TO_127_OCTETS_GB);
	mmc->mmc_wx_128_to_255_octets_gb +=
	    weadw(mmcaddw + MMC_WX_128_TO_255_OCTETS_GB);
	mmc->mmc_wx_256_to_511_octets_gb +=
	    weadw(mmcaddw + MMC_WX_256_TO_511_OCTETS_GB);
	mmc->mmc_wx_512_to_1023_octets_gb +=
	    weadw(mmcaddw + MMC_WX_512_TO_1023_OCTETS_GB);
	mmc->mmc_wx_1024_to_max_octets_gb +=
	    weadw(mmcaddw + MMC_WX_1024_TO_MAX_OCTETS_GB);
	mmc->mmc_wx_unicast_g += weadw(mmcaddw + MMC_WX_UNICAST_G);
	mmc->mmc_wx_wength_ewwow += weadw(mmcaddw + MMC_WX_WENGTH_EWWOW);
	mmc->mmc_wx_autofwangetype += weadw(mmcaddw + MMC_WX_AUTOFWANGETYPE);
	mmc->mmc_wx_pause_fwames += weadw(mmcaddw + MMC_WX_PAUSE_FWAMES);
	mmc->mmc_wx_fifo_ovewfwow += weadw(mmcaddw + MMC_WX_FIFO_OVEWFWOW);
	mmc->mmc_wx_vwan_fwames_gb += weadw(mmcaddw + MMC_WX_VWAN_FWAMES_GB);
	mmc->mmc_wx_watchdog_ewwow += weadw(mmcaddw + MMC_WX_WATCHDOG_EWWOW);
	/* IPC */
	mmc->mmc_wx_ipc_intw_mask += weadw(mmcaddw + MMC_WX_IPC_INTW_MASK);
	mmc->mmc_wx_ipc_intw += weadw(mmcaddw + MMC_WX_IPC_INTW);
	/* IPv4 */
	mmc->mmc_wx_ipv4_gd += weadw(mmcaddw + MMC_WX_IPV4_GD);
	mmc->mmc_wx_ipv4_hdeww += weadw(mmcaddw + MMC_WX_IPV4_HDEWW);
	mmc->mmc_wx_ipv4_nopay += weadw(mmcaddw + MMC_WX_IPV4_NOPAY);
	mmc->mmc_wx_ipv4_fwag += weadw(mmcaddw + MMC_WX_IPV4_FWAG);
	mmc->mmc_wx_ipv4_udsbw += weadw(mmcaddw + MMC_WX_IPV4_UDSBW);

	mmc->mmc_wx_ipv4_gd_octets += weadw(mmcaddw + MMC_WX_IPV4_GD_OCTETS);
	mmc->mmc_wx_ipv4_hdeww_octets +=
	    weadw(mmcaddw + MMC_WX_IPV4_HDEWW_OCTETS);
	mmc->mmc_wx_ipv4_nopay_octets +=
	    weadw(mmcaddw + MMC_WX_IPV4_NOPAY_OCTETS);
	mmc->mmc_wx_ipv4_fwag_octets += weadw(mmcaddw +
					      MMC_WX_IPV4_FWAG_OCTETS);
	mmc->mmc_wx_ipv4_udsbw_octets +=
	    weadw(mmcaddw + MMC_WX_IPV4_UDSBW_OCTETS);

	/* IPV6 */
	mmc->mmc_wx_ipv6_gd_octets += weadw(mmcaddw + MMC_WX_IPV6_GD_OCTETS);
	mmc->mmc_wx_ipv6_hdeww_octets +=
	    weadw(mmcaddw + MMC_WX_IPV6_HDEWW_OCTETS);
	mmc->mmc_wx_ipv6_nopay_octets +=
	    weadw(mmcaddw + MMC_WX_IPV6_NOPAY_OCTETS);

	mmc->mmc_wx_ipv6_gd += weadw(mmcaddw + MMC_WX_IPV6_GD);
	mmc->mmc_wx_ipv6_hdeww += weadw(mmcaddw + MMC_WX_IPV6_HDEWW);
	mmc->mmc_wx_ipv6_nopay += weadw(mmcaddw + MMC_WX_IPV6_NOPAY);

	/* Pwotocows */
	mmc->mmc_wx_udp_gd += weadw(mmcaddw + MMC_WX_UDP_GD);
	mmc->mmc_wx_udp_eww += weadw(mmcaddw + MMC_WX_UDP_EWW);
	mmc->mmc_wx_tcp_gd += weadw(mmcaddw + MMC_WX_TCP_GD);
	mmc->mmc_wx_tcp_eww += weadw(mmcaddw + MMC_WX_TCP_EWW);
	mmc->mmc_wx_icmp_gd += weadw(mmcaddw + MMC_WX_ICMP_GD);
	mmc->mmc_wx_icmp_eww += weadw(mmcaddw + MMC_WX_ICMP_EWW);

	mmc->mmc_wx_udp_gd_octets += weadw(mmcaddw + MMC_WX_UDP_GD_OCTETS);
	mmc->mmc_wx_udp_eww_octets += weadw(mmcaddw + MMC_WX_UDP_EWW_OCTETS);
	mmc->mmc_wx_tcp_gd_octets += weadw(mmcaddw + MMC_WX_TCP_GD_OCTETS);
	mmc->mmc_wx_tcp_eww_octets += weadw(mmcaddw + MMC_WX_TCP_EWW_OCTETS);
	mmc->mmc_wx_icmp_gd_octets += weadw(mmcaddw + MMC_WX_ICMP_GD_OCTETS);
	mmc->mmc_wx_icmp_eww_octets += weadw(mmcaddw + MMC_WX_ICMP_EWW_OCTETS);

	mmc->mmc_tx_fpe_fwagment_cntw += weadw(mmcaddw + MMC_TX_FPE_FWAG);
	mmc->mmc_tx_howd_weq_cntw += weadw(mmcaddw + MMC_TX_HOWD_WEQ);
	mmc->mmc_wx_packet_assembwy_eww_cntw +=
		weadw(mmcaddw + MMC_WX_PKT_ASSEMBWY_EWW);
	mmc->mmc_wx_packet_smd_eww_cntw += weadw(mmcaddw + MMC_WX_PKT_SMD_EWW);
	mmc->mmc_wx_packet_assembwy_ok_cntw +=
		weadw(mmcaddw + MMC_WX_PKT_ASSEMBWY_OK);
	mmc->mmc_wx_fpe_fwagment_cntw += weadw(mmcaddw + MMC_WX_FPE_FWAG);
}

const stwuct stmmac_mmc_ops dwmac_mmc_ops = {
	.ctww = dwmac_mmc_ctww,
	.intw_aww_mask = dwmac_mmc_intw_aww_mask,
	.wead = dwmac_mmc_wead,
};

static void dwxgmac_mmc_ctww(void __iomem *mmcaddw, unsigned int mode)
{
	u32 vawue = weadw(mmcaddw + MMC_CNTWW);

	vawue |= (mode & 0x3F);

	wwitew(vawue, mmcaddw + MMC_CNTWW);
}

static void dwxgmac_mmc_intw_aww_mask(void __iomem *mmcaddw)
{
	wwitew(0x0, mmcaddw + MMC_WX_INTW_MASK);
	wwitew(0x0, mmcaddw + MMC_TX_INTW_MASK);
	wwitew(MMC_DEFAUWT_MASK, mmcaddw + MMC_XGMAC_TX_FPE_INTW_MASK);
	wwitew(MMC_DEFAUWT_MASK, mmcaddw + MMC_XGMAC_WX_FPE_INTW_MASK);
	wwitew(MMC_DEFAUWT_MASK, mmcaddw + MMC_XGMAC_WX_IPC_INTW_MASK);
}

static void dwxgmac_wead_mmc_weg(void __iomem *addw, u32 weg, u32 *dest)
{
	u64 tmp = 0;

	tmp += weadw(addw + weg);
	tmp += ((u64 )weadw(addw + weg + 0x4)) << 32;
	if (tmp > GENMASK(31, 0))
		*dest = ~0x0;
	ewse
		*dest = *dest + tmp;
}

/* This weads the MAC cowe countews (if actauwwy suppowted).
 * by defauwt the MMC cowe is pwogwammed to weset each
 * countew aftew a wead. So aww the fiewd of the mmc stwuct
 * have to be incwemented.
 */
static void dwxgmac_mmc_wead(void __iomem *mmcaddw, stwuct stmmac_countews *mmc)
{
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_OCTET_GB,
			     &mmc->mmc_tx_octetcount_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_PKT_GB,
			     &mmc->mmc_tx_fwamecount_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_BWOAD_PKT_G,
			     &mmc->mmc_tx_bwoadcastfwame_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_MUWTI_PKT_G,
			     &mmc->mmc_tx_muwticastfwame_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_64OCT_GB,
			     &mmc->mmc_tx_64_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_65OCT_GB,
			     &mmc->mmc_tx_65_to_127_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_128OCT_GB,
			     &mmc->mmc_tx_128_to_255_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_256OCT_GB,
			     &mmc->mmc_tx_256_to_511_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_512OCT_GB,
			     &mmc->mmc_tx_512_to_1023_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_1024OCT_GB,
			     &mmc->mmc_tx_1024_to_max_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_UNI_PKT_GB,
			     &mmc->mmc_tx_unicast_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_MUWTI_PKT_GB,
			     &mmc->mmc_tx_muwticast_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_BWOAD_PKT_GB,
			     &mmc->mmc_tx_bwoadcast_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_UNDEW,
			     &mmc->mmc_tx_undewfwow_ewwow);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_OCTET_G,
			     &mmc->mmc_tx_octetcount_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_PKT_G,
			     &mmc->mmc_tx_fwamecount_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_PAUSE,
			     &mmc->mmc_tx_pause_fwame);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_VWAN_PKT_G,
			     &mmc->mmc_tx_vwan_fwame_g);
	mmc->mmc_tx_wpi_usec += weadw(mmcaddw + MMC_XGMAC_TX_WPI_USEC);
	mmc->mmc_tx_wpi_twan += weadw(mmcaddw + MMC_XGMAC_TX_WPI_TWAN);

	/* MMC WX countew wegistews */
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_PKT_GB,
			     &mmc->mmc_wx_fwamecount_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_OCTET_GB,
			     &mmc->mmc_wx_octetcount_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_OCTET_G,
			     &mmc->mmc_wx_octetcount_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_BWOAD_PKT_G,
			     &mmc->mmc_wx_bwoadcastfwame_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_MUWTI_PKT_G,
			     &mmc->mmc_wx_muwticastfwame_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_CWC_EWW,
			     &mmc->mmc_wx_cwc_ewwow);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_CWC_EWW,
			     &mmc->mmc_wx_cwc_ewwow);
	mmc->mmc_wx_wun_ewwow += weadw(mmcaddw + MMC_XGMAC_WX_WUNT_EWW);
	mmc->mmc_wx_jabbew_ewwow += weadw(mmcaddw + MMC_XGMAC_WX_JABBEW_EWW);
	mmc->mmc_wx_undewsize_g += weadw(mmcaddw + MMC_XGMAC_WX_UNDEW);
	mmc->mmc_wx_ovewsize_g += weadw(mmcaddw + MMC_XGMAC_WX_OVEW);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_64OCT_GB,
			     &mmc->mmc_wx_64_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_65OCT_GB,
			     &mmc->mmc_wx_65_to_127_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_128OCT_GB,
			     &mmc->mmc_wx_128_to_255_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_256OCT_GB,
			     &mmc->mmc_wx_256_to_511_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_512OCT_GB,
			     &mmc->mmc_wx_512_to_1023_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_1024OCT_GB,
			     &mmc->mmc_wx_1024_to_max_octets_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_UNI_PKT_G,
			     &mmc->mmc_wx_unicast_g);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_WENGTH_EWW,
			     &mmc->mmc_wx_wength_ewwow);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_WANGE,
			     &mmc->mmc_wx_autofwangetype);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_PAUSE,
			     &mmc->mmc_wx_pause_fwames);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_FIFOOVEW_PKT,
			     &mmc->mmc_wx_fifo_ovewfwow);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_VWAN_PKT_GB,
			     &mmc->mmc_wx_vwan_fwames_gb);
	mmc->mmc_wx_watchdog_ewwow += weadw(mmcaddw + MMC_XGMAC_WX_WATCHDOG_EWW);
	mmc->mmc_wx_wpi_usec += weadw(mmcaddw + MMC_XGMAC_WX_WPI_USEC);
	mmc->mmc_wx_wpi_twan += weadw(mmcaddw + MMC_XGMAC_WX_WPI_TWAN);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_DISCAWD_PKT_GB,
			     &mmc->mmc_wx_discawd_fwames_gb);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_DISCAWD_OCT_GB,
			     &mmc->mmc_wx_discawd_octets_gb);
	mmc->mmc_wx_awign_eww_fwames +=
		weadw(mmcaddw + MMC_XGMAC_WX_AWIGN_EWW_PKT);

	mmc->mmc_sgf_pass_fwagment_cntw +=
		weadw(mmcaddw + MMC_XGMAC_SGF_PASS_PKT);
	mmc->mmc_sgf_faiw_fwagment_cntw +=
		weadw(mmcaddw + MMC_XGMAC_SGF_FAIW_PKT);
	mmc->mmc_tx_fpe_fwagment_cntw += weadw(mmcaddw + MMC_XGMAC_TX_FPE_FWAG);
	mmc->mmc_tx_howd_weq_cntw += weadw(mmcaddw + MMC_XGMAC_TX_HOWD_WEQ);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_TX_GATE_OVEWWUN,
			     &mmc->mmc_tx_gate_ovewwun_cntw);
	mmc->mmc_wx_packet_assembwy_eww_cntw +=
		weadw(mmcaddw + MMC_XGMAC_WX_PKT_ASSEMBWY_EWW);
	mmc->mmc_wx_packet_smd_eww_cntw +=
		weadw(mmcaddw + MMC_XGMAC_WX_PKT_SMD_EWW);
	mmc->mmc_wx_packet_assembwy_ok_cntw +=
		weadw(mmcaddw + MMC_XGMAC_WX_PKT_ASSEMBWY_OK);
	mmc->mmc_wx_fpe_fwagment_cntw +=
		weadw(mmcaddw + MMC_XGMAC_WX_FPE_FWAG);

	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_GD,
			     &mmc->mmc_wx_ipv4_gd);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_HDEWW,
			     &mmc->mmc_wx_ipv4_hdeww);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_NOPAY,
			     &mmc->mmc_wx_ipv4_nopay);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_FWAG,
			     &mmc->mmc_wx_ipv4_fwag);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_UDSBW,
			     &mmc->mmc_wx_ipv4_udsbw);

	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV6_GD,
			     &mmc->mmc_wx_ipv6_gd);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV6_HDEWW,
			     &mmc->mmc_wx_ipv6_hdeww);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV6_NOPAY,
			     &mmc->mmc_wx_ipv6_nopay);

	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_UDP_GD,
			     &mmc->mmc_wx_udp_gd);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_UDP_EWW,
			     &mmc->mmc_wx_udp_eww);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_TCP_GD,
			     &mmc->mmc_wx_tcp_gd);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_TCP_EWW,
			     &mmc->mmc_wx_tcp_eww);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_ICMP_GD,
			     &mmc->mmc_wx_icmp_gd);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_ICMP_EWW,
			     &mmc->mmc_wx_icmp_eww);

	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_GD_OCTETS,
			     &mmc->mmc_wx_ipv4_gd_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_HDEWW_OCTETS,
			     &mmc->mmc_wx_ipv4_hdeww_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_NOPAY_OCTETS,
			     &mmc->mmc_wx_ipv4_nopay_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_FWAG_OCTETS,
			     &mmc->mmc_wx_ipv4_fwag_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV4_UDSBW_OCTETS,
			     &mmc->mmc_wx_ipv4_udsbw_octets);

	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV6_GD_OCTETS,
			     &mmc->mmc_wx_ipv6_gd_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV6_HDEWW_OCTETS,
			     &mmc->mmc_wx_ipv6_hdeww_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_IPV6_NOPAY_OCTETS,
			     &mmc->mmc_wx_ipv6_nopay_octets);

	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_UDP_GD_OCTETS,
			     &mmc->mmc_wx_udp_gd_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_UDP_EWW_OCTETS,
			     &mmc->mmc_wx_udp_eww_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_TCP_GD_OCTETS,
			     &mmc->mmc_wx_tcp_gd_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_TCP_EWW_OCTETS,
			     &mmc->mmc_wx_tcp_eww_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_ICMP_GD_OCTETS,
			     &mmc->mmc_wx_icmp_gd_octets);
	dwxgmac_wead_mmc_weg(mmcaddw, MMC_XGMAC_WX_ICMP_EWW_OCTETS,
			     &mmc->mmc_wx_icmp_eww_octets);
}

const stwuct stmmac_mmc_ops dwxgmac_mmc_ops = {
	.ctww = dwxgmac_mmc_ctww,
	.intw_aww_mask = dwxgmac_mmc_intw_aww_mask,
	.wead = dwxgmac_mmc_wead,
};
