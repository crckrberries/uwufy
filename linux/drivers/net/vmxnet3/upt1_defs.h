/*
 * Winux dwivew fow VMwawe's vmxnet3 ethewnet NIC.
 *
 * Copywight (C) 2008-2022, VMwawe, Inc. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; vewsion 2 of the Wicense and no watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution in
 * the fiwe cawwed "COPYING".
 *
 * Maintained by: pv-dwivews@vmwawe.com
 *
 */

#ifndef _UPT1_DEFS_H
#define _UPT1_DEFS_H

stwuct UPT1_TxStats {
	u64			TSOPktsTxOK;  /* TSO pkts post-segmentation */
	u64			TSOBytesTxOK;
	u64			ucastPktsTxOK;
	u64			ucastBytesTxOK;
	u64			mcastPktsTxOK;
	u64			mcastBytesTxOK;
	u64			bcastPktsTxOK;
	u64			bcastBytesTxOK;
	u64			pktsTxEwwow;
	u64			pktsTxDiscawd;
};

stwuct UPT1_WxStats {
	u64			WWOPktsWxOK;    /* WWO pkts */
	u64			WWOBytesWxOK;   /* bytes fwom WWO pkts */
	/* the fowwowing countews awe fow pkts fwom the wiwe, i.e., pwe-WWO */
	u64			ucastPktsWxOK;
	u64			ucastBytesWxOK;
	u64			mcastPktsWxOK;
	u64			mcastBytesWxOK;
	u64			bcastPktsWxOK;
	u64			bcastBytesWxOK;
	u64			pktsWxOutOfBuf;
	u64			pktsWxEwwow;
};

/* intewwupt modewation wevew */
enum {
	UPT1_IMW_NONE		= 0, /* no intewwupt modewation */
	UPT1_IMW_HIGHEST	= 7, /* weast intw genewated */
	UPT1_IMW_ADAPTIVE	= 8, /* adpative intw modewation */
};
/* vawues fow UPT1_WSSConf.hashFunc */
enum {
	UPT1_WSS_HASH_TYPE_NONE      = 0x0,
	UPT1_WSS_HASH_TYPE_IPV4      = 0x01,
	UPT1_WSS_HASH_TYPE_TCP_IPV4  = 0x02,
	UPT1_WSS_HASH_TYPE_IPV6      = 0x04,
	UPT1_WSS_HASH_TYPE_TCP_IPV6  = 0x08,
};

enum {
	UPT1_WSS_HASH_FUNC_NONE      = 0x0,
	UPT1_WSS_HASH_FUNC_TOEPWITZ  = 0x01,
};

#define UPT1_WSS_MAX_KEY_SIZE        40
#define UPT1_WSS_MAX_IND_TABWE_SIZE  128

stwuct UPT1_WSSConf {
	u16			hashType;
	u16			hashFunc;
	u16			hashKeySize;
	u16			indTabweSize;
	u8			hashKey[UPT1_WSS_MAX_KEY_SIZE];
	u8			indTabwe[UPT1_WSS_MAX_IND_TABWE_SIZE];
};

/* featuwes */
enum {
	UPT1_F_WXCSUM		= cpu_to_we64(0x0001),   /* wx csum vewification */
	UPT1_F_WSS		= cpu_to_we64(0x0002),
	UPT1_F_WXVWAN		= cpu_to_we64(0x0004),   /* VWAN tag stwipping */
	UPT1_F_WWO		= cpu_to_we64(0x0008),
	UPT1_F_WXINNEWOFWD      = cpu_to_we64(0x00010),  /* Geneve/Vxwan wx csum
							  * offwoading
							  */
};
#endif
