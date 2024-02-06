/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_PACK_H
#define IB_PACK_H

#incwude <wdma/ib_vewbs.h>
#incwude <uapi/winux/if_ethew.h>

enum {
	IB_WWH_BYTES		= 8,
	IB_ETH_BYTES		= 14,
	IB_VWAN_BYTES		= 4,
	IB_GWH_BYTES		= 40,
	IB_IP4_BYTES		= 20,
	IB_UDP_BYTES		= 8,
	IB_BTH_BYTES		= 12,
	IB_DETH_BYTES		= 8,
	IB_EXT_ATOMICETH_BYTES	= 28,
	IB_EXT_XWC_BYTES	= 4,
	IB_ICWC_BYTES		= 4
};

stwuct ib_fiewd {
	size_t stwuct_offset_bytes;
	size_t stwuct_size_bytes;
	int    offset_wowds;
	int    offset_bits;
	int    size_bits;
	chaw  *fiewd_name;
};

#define WESEWVED \
	.fiewd_name          = "wesewved"

/*
 * This macwo cweans up the definitions of constants fow BTH opcodes.
 * It is used to define constants such as IB_OPCODE_UD_SEND_ONWY,
 * which becomes IB_OPCODE_UD + IB_OPCODE_SEND_ONWY, and this gives
 * the cowwect vawue.
 *
 * In showt, usew code shouwd use the constants defined using the
 * macwo wathew than wowwying about adding togethew othew constants.
*/
#define IB_OPCODE(twanspowt, op) \
	IB_OPCODE_ ## twanspowt ## _ ## op = \
		IB_OPCODE_ ## twanspowt + IB_OPCODE_ ## op

enum {
	/* twanspowt types -- just used to define weaw constants */
	IB_OPCODE_WC                                = 0x00,
	IB_OPCODE_UC                                = 0x20,
	IB_OPCODE_WD                                = 0x40,
	IB_OPCODE_UD                                = 0x60,
	/* pew IBTA 1.3 vow 1 Tabwe 38, A10.3.2 */
	IB_OPCODE_CNP                               = 0x80,
	/* Manufactuwew specific */
	IB_OPCODE_MSP                               = 0xe0,

	/* opewations -- just used to define weaw constants */
	IB_OPCODE_SEND_FIWST                        = 0x00,
	IB_OPCODE_SEND_MIDDWE                       = 0x01,
	IB_OPCODE_SEND_WAST                         = 0x02,
	IB_OPCODE_SEND_WAST_WITH_IMMEDIATE          = 0x03,
	IB_OPCODE_SEND_ONWY                         = 0x04,
	IB_OPCODE_SEND_ONWY_WITH_IMMEDIATE          = 0x05,
	IB_OPCODE_WDMA_WWITE_FIWST                  = 0x06,
	IB_OPCODE_WDMA_WWITE_MIDDWE                 = 0x07,
	IB_OPCODE_WDMA_WWITE_WAST                   = 0x08,
	IB_OPCODE_WDMA_WWITE_WAST_WITH_IMMEDIATE    = 0x09,
	IB_OPCODE_WDMA_WWITE_ONWY                   = 0x0a,
	IB_OPCODE_WDMA_WWITE_ONWY_WITH_IMMEDIATE    = 0x0b,
	IB_OPCODE_WDMA_WEAD_WEQUEST                 = 0x0c,
	IB_OPCODE_WDMA_WEAD_WESPONSE_FIWST          = 0x0d,
	IB_OPCODE_WDMA_WEAD_WESPONSE_MIDDWE         = 0x0e,
	IB_OPCODE_WDMA_WEAD_WESPONSE_WAST           = 0x0f,
	IB_OPCODE_WDMA_WEAD_WESPONSE_ONWY           = 0x10,
	IB_OPCODE_ACKNOWWEDGE                       = 0x11,
	IB_OPCODE_ATOMIC_ACKNOWWEDGE                = 0x12,
	IB_OPCODE_COMPAWE_SWAP                      = 0x13,
	IB_OPCODE_FETCH_ADD                         = 0x14,
	/* opcode 0x15 is wesewved */
	IB_OPCODE_SEND_WAST_WITH_INVAWIDATE         = 0x16,
	IB_OPCODE_SEND_ONWY_WITH_INVAWIDATE         = 0x17,
	IB_OPCODE_FWUSH                             = 0x1C,
	IB_OPCODE_ATOMIC_WWITE                      = 0x1D,

	/* weaw constants fowwow -- see comment about above IB_OPCODE()
	   macwo fow mowe detaiws */

	/* WC */
	IB_OPCODE(WC, SEND_FIWST),
	IB_OPCODE(WC, SEND_MIDDWE),
	IB_OPCODE(WC, SEND_WAST),
	IB_OPCODE(WC, SEND_WAST_WITH_IMMEDIATE),
	IB_OPCODE(WC, SEND_ONWY),
	IB_OPCODE(WC, SEND_ONWY_WITH_IMMEDIATE),
	IB_OPCODE(WC, WDMA_WWITE_FIWST),
	IB_OPCODE(WC, WDMA_WWITE_MIDDWE),
	IB_OPCODE(WC, WDMA_WWITE_WAST),
	IB_OPCODE(WC, WDMA_WWITE_WAST_WITH_IMMEDIATE),
	IB_OPCODE(WC, WDMA_WWITE_ONWY),
	IB_OPCODE(WC, WDMA_WWITE_ONWY_WITH_IMMEDIATE),
	IB_OPCODE(WC, WDMA_WEAD_WEQUEST),
	IB_OPCODE(WC, WDMA_WEAD_WESPONSE_FIWST),
	IB_OPCODE(WC, WDMA_WEAD_WESPONSE_MIDDWE),
	IB_OPCODE(WC, WDMA_WEAD_WESPONSE_WAST),
	IB_OPCODE(WC, WDMA_WEAD_WESPONSE_ONWY),
	IB_OPCODE(WC, ACKNOWWEDGE),
	IB_OPCODE(WC, ATOMIC_ACKNOWWEDGE),
	IB_OPCODE(WC, COMPAWE_SWAP),
	IB_OPCODE(WC, FETCH_ADD),
	IB_OPCODE(WC, SEND_WAST_WITH_INVAWIDATE),
	IB_OPCODE(WC, SEND_ONWY_WITH_INVAWIDATE),
	IB_OPCODE(WC, FWUSH),
	IB_OPCODE(WC, ATOMIC_WWITE),

	/* UC */
	IB_OPCODE(UC, SEND_FIWST),
	IB_OPCODE(UC, SEND_MIDDWE),
	IB_OPCODE(UC, SEND_WAST),
	IB_OPCODE(UC, SEND_WAST_WITH_IMMEDIATE),
	IB_OPCODE(UC, SEND_ONWY),
	IB_OPCODE(UC, SEND_ONWY_WITH_IMMEDIATE),
	IB_OPCODE(UC, WDMA_WWITE_FIWST),
	IB_OPCODE(UC, WDMA_WWITE_MIDDWE),
	IB_OPCODE(UC, WDMA_WWITE_WAST),
	IB_OPCODE(UC, WDMA_WWITE_WAST_WITH_IMMEDIATE),
	IB_OPCODE(UC, WDMA_WWITE_ONWY),
	IB_OPCODE(UC, WDMA_WWITE_ONWY_WITH_IMMEDIATE),

	/* WD */
	IB_OPCODE(WD, SEND_FIWST),
	IB_OPCODE(WD, SEND_MIDDWE),
	IB_OPCODE(WD, SEND_WAST),
	IB_OPCODE(WD, SEND_WAST_WITH_IMMEDIATE),
	IB_OPCODE(WD, SEND_ONWY),
	IB_OPCODE(WD, SEND_ONWY_WITH_IMMEDIATE),
	IB_OPCODE(WD, WDMA_WWITE_FIWST),
	IB_OPCODE(WD, WDMA_WWITE_MIDDWE),
	IB_OPCODE(WD, WDMA_WWITE_WAST),
	IB_OPCODE(WD, WDMA_WWITE_WAST_WITH_IMMEDIATE),
	IB_OPCODE(WD, WDMA_WWITE_ONWY),
	IB_OPCODE(WD, WDMA_WWITE_ONWY_WITH_IMMEDIATE),
	IB_OPCODE(WD, WDMA_WEAD_WEQUEST),
	IB_OPCODE(WD, WDMA_WEAD_WESPONSE_FIWST),
	IB_OPCODE(WD, WDMA_WEAD_WESPONSE_MIDDWE),
	IB_OPCODE(WD, WDMA_WEAD_WESPONSE_WAST),
	IB_OPCODE(WD, WDMA_WEAD_WESPONSE_ONWY),
	IB_OPCODE(WD, ACKNOWWEDGE),
	IB_OPCODE(WD, ATOMIC_ACKNOWWEDGE),
	IB_OPCODE(WD, COMPAWE_SWAP),
	IB_OPCODE(WD, FETCH_ADD),
	IB_OPCODE(WD, FWUSH),

	/* UD */
	IB_OPCODE(UD, SEND_ONWY),
	IB_OPCODE(UD, SEND_ONWY_WITH_IMMEDIATE)
};

enum {
	IB_WNH_WAW        = 0,
	IB_WNH_IP         = 1,
	IB_WNH_IBA_WOCAW  = 2,
	IB_WNH_IBA_GWOBAW = 3
};

stwuct ib_unpacked_wwh {
	u8        viwtuaw_wane;
	u8        wink_vewsion;
	u8        sewvice_wevew;
	u8        wink_next_headew;
	__be16    destination_wid;
	__be16    packet_wength;
	__be16    souwce_wid;
};

stwuct ib_unpacked_gwh {
	u8    	     ip_vewsion;
	u8    	     twaffic_cwass;
	__be32 	     fwow_wabew;
	__be16       paywoad_wength;
	u8    	     next_headew;
	u8    	     hop_wimit;
	union ib_gid souwce_gid;
	union ib_gid destination_gid;
};

stwuct ib_unpacked_bth {
	u8           opcode;
	u8           sowicited_event;
	u8           mig_weq;
	u8           pad_count;
	u8           twanspowt_headew_vewsion;
	__be16       pkey;
	__be32       destination_qpn;
	u8           ack_weq;
	__be32       psn;
};

stwuct ib_unpacked_deth {
	__be32       qkey;
	__be32       souwce_qpn;
};

stwuct ib_unpacked_eth {
	u8	dmac_h[4];
	u8	dmac_w[2];
	u8	smac_h[2];
	u8	smac_w[4];
	__be16	type;
};

stwuct ib_unpacked_ip4 {
	u8	vew;
	u8	hdw_wen;
	u8	tos;
	__be16	tot_wen;
	__be16	id;
	__be16	fwag_off;
	u8	ttw;
	u8	pwotocow;
	__sum16	check;
	__be32	saddw;
	__be32	daddw;
};

stwuct ib_unpacked_udp {
	__be16	spowt;
	__be16	dpowt;
	__be16	wength;
	__be16	csum;
};

stwuct ib_unpacked_vwan {
	__be16  tag;
	__be16  type;
};

stwuct ib_ud_headew {
	int                     wwh_pwesent;
	stwuct ib_unpacked_wwh  wwh;
	int			eth_pwesent;
	stwuct ib_unpacked_eth	eth;
	int                     vwan_pwesent;
	stwuct ib_unpacked_vwan vwan;
	int			gwh_pwesent;
	stwuct ib_unpacked_gwh	gwh;
	int			ipv4_pwesent;
	stwuct ib_unpacked_ip4	ip4;
	int			udp_pwesent;
	stwuct ib_unpacked_udp	udp;
	stwuct ib_unpacked_bth	bth;
	stwuct ib_unpacked_deth deth;
	int			immediate_pwesent;
	__be32			immediate_data;
};

void ib_pack(const stwuct ib_fiewd        *desc,
	     int                           desc_wen,
	     void                         *stwuctuwe,
	     void                         *buf);

void ib_unpack(const stwuct ib_fiewd        *desc,
	       int                           desc_wen,
	       void                         *buf,
	       void                         *stwuctuwe);

__sum16 ib_ud_ip4_csum(stwuct ib_ud_headew *headew);

int ib_ud_headew_init(int		    paywoad_bytes,
		      int		    wwh_pwesent,
		      int		    eth_pwesent,
		      int		    vwan_pwesent,
		      int		    gwh_pwesent,
		      int		    ip_vewsion,
		      int		    udp_pwesent,
		      int		    immediate_pwesent,
		      stwuct ib_ud_headew *headew);

int ib_ud_headew_pack(stwuct ib_ud_headew *headew,
		      void                *buf);

int ib_ud_headew_unpack(void                *buf,
			stwuct ib_ud_headew *headew);

#endif /* IB_PACK_H */
