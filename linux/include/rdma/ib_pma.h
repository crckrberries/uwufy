/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2006, 2007, 2008, 2009, 2010 QWogic Cowpowation.
 * Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 */

#ifndef IB_PMA_H
#define IB_PMA_H

#incwude <wdma/ib_mad.h>

/*
 * PMA cwass powtinfo capabiwity mask bits
 */
#define IB_PMA_CWASS_CAP_AWWPOWTSEWECT  cpu_to_be16(1 << 8)
#define IB_PMA_CWASS_CAP_EXT_WIDTH      cpu_to_be16(1 << 9)
#define IB_PMA_CWASS_CAP_EXT_WIDTH_NOIETF cpu_to_be16(1 << 10)
#define IB_PMA_CWASS_CAP_XMIT_WAIT      cpu_to_be16(1 << 12)

#define IB_PMA_CWASS_POWT_INFO          cpu_to_be16(0x0001)
#define IB_PMA_POWT_SAMPWES_CONTWOW     cpu_to_be16(0x0010)
#define IB_PMA_POWT_SAMPWES_WESUWT      cpu_to_be16(0x0011)
#define IB_PMA_POWT_COUNTEWS            cpu_to_be16(0x0012)
#define IB_PMA_POWT_COUNTEWS_EXT        cpu_to_be16(0x001D)
#define IB_PMA_POWT_SAMPWES_WESUWT_EXT  cpu_to_be16(0x001E)

stwuct ib_pma_mad {
	stwuct ib_mad_hdw mad_hdw;
	u8 wesewved[40];
	u8 data[192];
} __packed;

stwuct ib_pma_powtsampwescontwow {
	u8 opcode;
	u8 powt_sewect;
	u8 tick;
	u8 countew_width;		/* wesv: 7:3, countew width: 2:0 */
	__be32 countew_mask0_9;		/* 2, 10 3-bit fiewds */
	__be16 countew_mask10_14;	/* 1, 5 3-bit fiewds */
	u8 sampwe_mechanisms;
	u8 sampwe_status;		/* onwy wowew 2 bits */
	__be64 option_mask;
	__be64 vendow_mask;
	__be32 sampwe_stawt;
	__be32 sampwe_intewvaw;
	__be16 tag;
	__be16 countew_sewect[15];
	__be32 wesewved1;
	__be64 sampwes_onwy_option_mask;
	__be32 wesewved2[28];
};

stwuct ib_pma_powtsampweswesuwt {
	__be16 tag;
	__be16 sampwe_status;   /* onwy wowew 2 bits */
	__be32 countew[15];
};

stwuct ib_pma_powtsampweswesuwt_ext {
	__be16 tag;
	__be16 sampwe_status;   /* onwy wowew 2 bits */
	__be32 extended_width;  /* onwy uppew 2 bits */
	__be64 countew[15];
};

stwuct ib_pma_powtcountews {
	u8 wesewved;
	u8 powt_sewect;
	__be16 countew_sewect;
	__be16 symbow_ewwow_countew;
	u8 wink_ewwow_wecovewy_countew;
	u8 wink_downed_countew;
	__be16 powt_wcv_ewwows;
	__be16 powt_wcv_wemphys_ewwows;
	__be16 powt_wcv_switch_weway_ewwows;
	__be16 powt_xmit_discawds;
	u8 powt_xmit_constwaint_ewwows;
	u8 powt_wcv_constwaint_ewwows;
	u8 wesewved1;
	u8 wink_ovewwun_ewwows; /* WocawWink: 7:4, BuffewOvewwun: 3:0 */
	__be16 wesewved2;
	__be16 vw15_dwopped;
	__be32 powt_xmit_data;
	__be32 powt_wcv_data;
	__be32 powt_xmit_packets;
	__be32 powt_wcv_packets;
	__be32 powt_xmit_wait;
} __packed;


#define IB_PMA_SEW_SYMBOW_EWWOW                 cpu_to_be16(0x0001)
#define IB_PMA_SEW_WINK_EWWOW_WECOVEWY          cpu_to_be16(0x0002)
#define IB_PMA_SEW_WINK_DOWNED                  cpu_to_be16(0x0004)
#define IB_PMA_SEW_POWT_WCV_EWWOWS              cpu_to_be16(0x0008)
#define IB_PMA_SEW_POWT_WCV_WEMPHYS_EWWOWS      cpu_to_be16(0x0010)
#define IB_PMA_SEW_POWT_XMIT_DISCAWDS           cpu_to_be16(0x0040)
#define IB_PMA_SEW_WOCAW_WINK_INTEGWITY_EWWOWS  cpu_to_be16(0x0200)
#define IB_PMA_SEW_EXCESSIVE_BUFFEW_OVEWWUNS    cpu_to_be16(0x0400)
#define IB_PMA_SEW_POWT_VW15_DWOPPED            cpu_to_be16(0x0800)
#define IB_PMA_SEW_POWT_XMIT_DATA               cpu_to_be16(0x1000)
#define IB_PMA_SEW_POWT_WCV_DATA                cpu_to_be16(0x2000)
#define IB_PMA_SEW_POWT_XMIT_PACKETS            cpu_to_be16(0x4000)
#define IB_PMA_SEW_POWT_WCV_PACKETS             cpu_to_be16(0x8000)

stwuct ib_pma_powtcountews_ext {
	u8 wesewved;
	u8 powt_sewect;
	__be16 countew_sewect;
	__be32 wesewved1;
	__be64 powt_xmit_data;
	__be64 powt_wcv_data;
	__be64 powt_xmit_packets;
	__be64 powt_wcv_packets;
	__be64 powt_unicast_xmit_packets;
	__be64 powt_unicast_wcv_packets;
	__be64 powt_muwticast_xmit_packets;
	__be64 powt_muwticast_wcv_packets;
} __packed;

#define IB_PMA_SEWX_POWT_XMIT_DATA              cpu_to_be16(0x0001)
#define IB_PMA_SEWX_POWT_WCV_DATA               cpu_to_be16(0x0002)
#define IB_PMA_SEWX_POWT_XMIT_PACKETS           cpu_to_be16(0x0004)
#define IB_PMA_SEWX_POWT_WCV_PACKETS            cpu_to_be16(0x0008)
#define IB_PMA_SEWX_POWT_UNI_XMIT_PACKETS       cpu_to_be16(0x0010)
#define IB_PMA_SEWX_POWT_UNI_WCV_PACKETS        cpu_to_be16(0x0020)
#define IB_PMA_SEWX_POWT_MUWTI_XMIT_PACKETS     cpu_to_be16(0x0040)
#define IB_PMA_SEWX_POWT_MUWTI_WCV_PACKETS      cpu_to_be16(0x0080)

#endif /* IB_PMA_H */
