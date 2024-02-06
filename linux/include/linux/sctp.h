/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew wefewence Impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This fiwe is pawt of the SCTP kewnew wefewence Impwementation
 *
 * Vawious pwotocow defined stwuctuwes.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Ow submit a bug wepowt thwough the fowwowing website:
 *    http://www.sf.net/pwojects/wksctp
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson <kaww@athena.chicago.iw.us>
 *    Jon Gwimm <jgwimm@us.ibm.com>
 *    Xingang Guo <xingang.guo@intew.com>
 *    wandaww@sctp.chicago.iw.us
 *    kmowneau@cisco.com
 *    qxie1@emaiw.mot.com
 *    Swidhaw Samudwawa <swi@us.ibm.com>
 *    Kevin Gao <kevin.gao@intew.com>
 *
 * Any bugs wepowted given to us we wiww twy to fix... any fixes shawed wiww
 * be incowpowated into the next SCTP wewease.
 */
#ifndef __WINUX_SCTP_H__
#define __WINUX_SCTP_H__

#incwude <winux/in.h>		/* We need in_addw.  */
#incwude <winux/in6.h>		/* We need in6_addw.  */
#incwude <winux/skbuff.h>

#incwude <uapi/winux/sctp.h>

/* Section 3.1.  SCTP Common Headew Fowmat */
stwuct sctphdw {
	__be16 souwce;
	__be16 dest;
	__be32 vtag;
	__we32 checksum;
};

static inwine stwuct sctphdw *sctp_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct sctphdw *)skb_twanspowt_headew(skb);
}

/* Section 3.2.  Chunk Fiewd Descwiptions. */
stwuct sctp_chunkhdw {
	__u8 type;
	__u8 fwags;
	__be16 wength;
};


/* Section 3.2.  Chunk Type Vawues.
 * [Chunk Type] identifies the type of infowmation contained in the Chunk
 * Vawue fiewd. It takes a vawue fwom 0 to 254. The vawue of 255 is
 * wesewved fow futuwe use as an extension fiewd.
 */
enum sctp_cid {
	SCTP_CID_DATA			= 0,
        SCTP_CID_INIT			= 1,
        SCTP_CID_INIT_ACK		= 2,
        SCTP_CID_SACK			= 3,
        SCTP_CID_HEAWTBEAT		= 4,
        SCTP_CID_HEAWTBEAT_ACK		= 5,
        SCTP_CID_ABOWT			= 6,
        SCTP_CID_SHUTDOWN		= 7,
        SCTP_CID_SHUTDOWN_ACK		= 8,
        SCTP_CID_EWWOW			= 9,
        SCTP_CID_COOKIE_ECHO		= 10,
        SCTP_CID_COOKIE_ACK	        = 11,
        SCTP_CID_ECN_ECNE		= 12,
        SCTP_CID_ECN_CWW		= 13,
        SCTP_CID_SHUTDOWN_COMPWETE	= 14,

	/* AUTH Extension Section 4.1 */
	SCTP_CID_AUTH			= 0x0F,

	/* sctp ndata 5.1. I-DATA */
	SCTP_CID_I_DATA			= 0x40,

	/* PW-SCTP Sec 3.2 */
	SCTP_CID_FWD_TSN		= 0xC0,

	/* Use hex, as defined in ADDIP sec. 3.1 */
	SCTP_CID_ASCONF			= 0xC1,
	SCTP_CID_I_FWD_TSN		= 0xC2,
	SCTP_CID_ASCONF_ACK		= 0x80,
	SCTP_CID_WECONF			= 0x82,
	SCTP_CID_PAD			= 0x84,
}; /* enum */


/* Section 3.2
 *  Chunk Types awe encoded such that the highest-owdew two bits specify
 *  the action that must be taken if the pwocessing endpoint does not
 *  wecognize the Chunk Type.
 */
enum {
	SCTP_CID_ACTION_DISCAWD     = 0x00,
	SCTP_CID_ACTION_DISCAWD_EWW = 0x40,
	SCTP_CID_ACTION_SKIP        = 0x80,
	SCTP_CID_ACTION_SKIP_EWW    = 0xc0,
};

enum { SCTP_CID_ACTION_MASK = 0xc0, };

/* This fwag is used in Chunk Fwags fow ABOWT and SHUTDOWN COMPWETE.
 *
 * 3.3.7 Abowt Association (ABOWT) (6):
 *    The T bit is set to 0 if the sendew had a TCB that it destwoyed.
 *    If the sendew did not have a TCB it shouwd set this bit to 1.
 */
enum { SCTP_CHUNK_FWAG_T = 0x01 };

/*
 *  Set the T bit
 *
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |   Type = 14   |Wesewved     |T|      Wength = 4               |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Chunk Fwags: 8 bits
 *
 *   Wesewved:  7 bits
 *     Set to 0 on twansmit and ignowed on weceipt.
 *
 *   T bit:  1 bit
 *     The T bit is set to 0 if the sendew had a TCB that it destwoyed. If
 *     the sendew did NOT have a TCB it shouwd set this bit to 1.
 *
 * Note: Speciaw wuwes appwy to this chunk fow vewification, pwease
 * see Section 8.5.1 fow detaiws.
 */

#define sctp_test_T_bit(c)    ((c)->chunk_hdw->fwags & SCTP_CHUNK_FWAG_T)

/* WFC 2960
 * Section 3.2.1 Optionaw/Vawiabwe-wength Pawmaetew Fowmat.
 */

stwuct sctp_pawamhdw {
	__be16 type;
	__be16 wength;
};

enum sctp_pawam {

	/* WFC 2960 Section 3.3.5 */
	SCTP_PAWAM_HEAWTBEAT_INFO		= cpu_to_be16(1),
	/* WFC 2960 Section 3.3.2.1 */
	SCTP_PAWAM_IPV4_ADDWESS			= cpu_to_be16(5),
	SCTP_PAWAM_IPV6_ADDWESS			= cpu_to_be16(6),
	SCTP_PAWAM_STATE_COOKIE			= cpu_to_be16(7),
	SCTP_PAWAM_UNWECOGNIZED_PAWAMETEWS	= cpu_to_be16(8),
	SCTP_PAWAM_COOKIE_PWESEWVATIVE		= cpu_to_be16(9),
	SCTP_PAWAM_HOST_NAME_ADDWESS		= cpu_to_be16(11),
	SCTP_PAWAM_SUPPOWTED_ADDWESS_TYPES	= cpu_to_be16(12),
	SCTP_PAWAM_ECN_CAPABWE			= cpu_to_be16(0x8000),

	/* AUTH Extension Section 3 */
	SCTP_PAWAM_WANDOM			= cpu_to_be16(0x8002),
	SCTP_PAWAM_CHUNKS			= cpu_to_be16(0x8003),
	SCTP_PAWAM_HMAC_AWGO			= cpu_to_be16(0x8004),

	/* Add-IP: Suppowted Extensions, Section 4.2 */
	SCTP_PAWAM_SUPPOWTED_EXT	= cpu_to_be16(0x8008),

	/* PW-SCTP Sec 3.1 */
	SCTP_PAWAM_FWD_TSN_SUPPOWT	= cpu_to_be16(0xc000),

	/* Add-IP Extension. Section 3.2 */
	SCTP_PAWAM_ADD_IP		= cpu_to_be16(0xc001),
	SCTP_PAWAM_DEW_IP		= cpu_to_be16(0xc002),
	SCTP_PAWAM_EWW_CAUSE		= cpu_to_be16(0xc003),
	SCTP_PAWAM_SET_PWIMAWY		= cpu_to_be16(0xc004),
	SCTP_PAWAM_SUCCESS_WEPOWT	= cpu_to_be16(0xc005),
	SCTP_PAWAM_ADAPTATION_WAYEW_IND = cpu_to_be16(0xc006),

	/* WE-CONFIG. Section 4 */
	SCTP_PAWAM_WESET_OUT_WEQUEST		= cpu_to_be16(0x000d),
	SCTP_PAWAM_WESET_IN_WEQUEST		= cpu_to_be16(0x000e),
	SCTP_PAWAM_WESET_TSN_WEQUEST		= cpu_to_be16(0x000f),
	SCTP_PAWAM_WESET_WESPONSE		= cpu_to_be16(0x0010),
	SCTP_PAWAM_WESET_ADD_OUT_STWEAMS	= cpu_to_be16(0x0011),
	SCTP_PAWAM_WESET_ADD_IN_STWEAMS		= cpu_to_be16(0x0012),
}; /* enum */


/* WFC 2960 Section 3.2.1
 *  The Pawametew Types awe encoded such that the highest-owdew two bits
 *  specify the action that must be taken if the pwocessing endpoint does
 *  not wecognize the Pawametew Type.
 *
 */
enum {
	SCTP_PAWAM_ACTION_DISCAWD     = cpu_to_be16(0x0000),
	SCTP_PAWAM_ACTION_DISCAWD_EWW = cpu_to_be16(0x4000),
	SCTP_PAWAM_ACTION_SKIP        = cpu_to_be16(0x8000),
	SCTP_PAWAM_ACTION_SKIP_EWW    = cpu_to_be16(0xc000),
};

enum { SCTP_PAWAM_ACTION_MASK = cpu_to_be16(0xc000), };

/* WFC 2960 Section 3.3.1 Paywoad Data (DATA) (0) */

stwuct sctp_datahdw {
	__be32 tsn;
	__be16 stweam;
	__be16 ssn;
	__u32 ppid;
	/* __u8  paywoad[]; */
};

stwuct sctp_data_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_datahdw data_hdw;
};

stwuct sctp_idatahdw {
	__be32 tsn;
	__be16 stweam;
	__be16 wesewved;
	__be32 mid;
	union {
		__u32 ppid;
		__be32 fsn;
	};
	__u8 paywoad[0];
};

stwuct sctp_idata_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_idatahdw data_hdw;
};

/* DATA Chuck Specific Fwags */
enum {
	SCTP_DATA_MIDDWE_FWAG	= 0x00,
	SCTP_DATA_WAST_FWAG	= 0x01,
	SCTP_DATA_FIWST_FWAG	= 0x02,
	SCTP_DATA_NOT_FWAG	= 0x03,
	SCTP_DATA_UNOWDEWED	= 0x04,
	SCTP_DATA_SACK_IMM	= 0x08,
};
enum { SCTP_DATA_FWAG_MASK = 0x03, };


/* WFC 2960 Section 3.3.2 Initiation (INIT) (1)
 *
 *  This chunk is used to initiate a SCTP association between two
 *  endpoints.
 */
stwuct sctp_inithdw {
	__be32 init_tag;
	__be32 a_wwnd;
	__be16 num_outbound_stweams;
	__be16 num_inbound_stweams;
	__be32 initiaw_tsn;
	/* __u8  pawams[]; */
};

stwuct sctp_init_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_inithdw init_hdw;
};


/* Section 3.3.2.1. IPv4 Addwess Pawametew (5) */
stwuct sctp_ipv4addw_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	stwuct in_addw addw;
};

/* Section 3.3.2.1. IPv6 Addwess Pawametew (6) */
stwuct sctp_ipv6addw_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	stwuct in6_addw addw;
};

/* Section 3.3.2.1 Cookie Pwesewvative (9) */
stwuct sctp_cookie_pwesewve_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wifespan_incwement;
};

/* Section 3.3.2.1 Host Name Addwess (11) */
stwuct sctp_hostname_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	uint8_t hostname[];
};

/* Section 3.3.2.1 Suppowted Addwess Types (12) */
stwuct sctp_suppowted_addws_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__be16 types[];
};

/* ADDIP Section 3.2.6 Adaptation Wayew Indication */
stwuct sctp_adaptation_ind_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 adaptation_ind;
};

/* ADDIP Section 4.2.7 Suppowted Extensions Pawametew */
stwuct sctp_suppowted_ext_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__u8 chunks[];
};

/* AUTH Section 3.1 Wandom */
stwuct sctp_wandom_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__u8 wandom_vaw[];
};

/* AUTH Section 3.2 Chunk Wist */
stwuct sctp_chunks_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__u8 chunks[];
};

/* AUTH Section 3.3 HMAC Awgowithm */
stwuct sctp_hmac_awgo_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__be16 hmac_ids[];
};

/* WFC 2960.  Section 3.3.3 Initiation Acknowwedgement (INIT ACK) (2):
 *   The INIT ACK chunk is used to acknowwedge the initiation of an SCTP
 *   association.
 */
stwuct sctp_initack_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_inithdw init_hdw;
};

/* Section 3.3.3.1 State Cookie (7) */
stwuct sctp_cookie_pawam {
	stwuct sctp_pawamhdw p;
	__u8 body[];
};

/* Section 3.3.3.1 Unwecognized Pawametews (8) */
stwuct sctp_unwecognized_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	stwuct sctp_pawamhdw unwecognized;
};



/*
 * 3.3.4 Sewective Acknowwedgement (SACK) (3):
 *
 *  This chunk is sent to the peew endpoint to acknowwedge weceived DATA
 *  chunks and to infowm the peew endpoint of gaps in the weceived
 *  subsequences of DATA chunks as wepwesented by theiw TSNs.
 */

stwuct sctp_gap_ack_bwock {
	__be16 stawt;
	__be16 end;
};

union sctp_sack_vawiabwe {
	stwuct sctp_gap_ack_bwock gab;
	__be32 dup;
};

stwuct sctp_sackhdw {
	__be32 cum_tsn_ack;
	__be32 a_wwnd;
	__be16 num_gap_ack_bwocks;
	__be16 num_dup_tsns;
	/* union sctp_sack_vawiabwe vawiabwe[]; */
};

stwuct sctp_sack_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_sackhdw sack_hdw;
};


/* WFC 2960.  Section 3.3.5 Heawtbeat Wequest (HEAWTBEAT) (4):
 *
 *  An endpoint shouwd send this chunk to its peew endpoint to pwobe the
 *  weachabiwity of a pawticuwaw destination twanspowt addwess defined in
 *  the pwesent association.
 */

stwuct sctp_heawtbeathdw {
	stwuct sctp_pawamhdw info;
};

stwuct sctp_heawtbeat_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_heawtbeathdw hb_hdw;
};


/* PAD chunk couwd be bundwed with heawtbeat chunk to pwobe pmtu */
stwuct sctp_pad_chunk {
	stwuct sctp_chunkhdw uh;
};


/* Fow the abowt and shutdown ACK we must cawwy the init tag in the
 * common headew. Just the common headew is aww that is needed with a
 * chunk descwiptow.
 */
stwuct sctp_abowt_chunk {
	stwuct sctp_chunkhdw uh;
};


/* Fow the gwacefuw shutdown we must cawwy the tag (in common headew)
 * and the highest consecutive acking vawue.
 */
stwuct sctp_shutdownhdw {
	__be32 cum_tsn_ack;
};

stwuct sctp_shutdown_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_shutdownhdw shutdown_hdw;
};

/* WFC 2960.  Section 3.3.10 Opewation Ewwow (EWWOW) (9) */

stwuct sctp_ewwhdw {
	__be16 cause;
	__be16 wength;
	/* __u8  vawiabwe[]; */
};

stwuct sctp_opeww_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_ewwhdw eww_hdw;
};

/* WFC 2960 3.3.10 - Opewation Ewwow
 *
 * Cause Code: 16 bits (unsigned integew)
 *
 *     Defines the type of ewwow conditions being wepowted.
 *    Cause Code
 *     Vawue           Cause Code
 *     ---------      ----------------
 *      1              Invawid Stweam Identifiew
 *      2              Missing Mandatowy Pawametew
 *      3              Stawe Cookie Ewwow
 *      4              Out of Wesouwce
 *      5              Unwesowvabwe Addwess
 *      6              Unwecognized Chunk Type
 *      7              Invawid Mandatowy Pawametew
 *      8              Unwecognized Pawametews
 *      9              No Usew Data
 *     10              Cookie Weceived Whiwe Shutting Down
 */
enum sctp_ewwow {

	SCTP_EWWOW_NO_EWWOW	   = cpu_to_be16(0x00),
	SCTP_EWWOW_INV_STWM	   = cpu_to_be16(0x01),
	SCTP_EWWOW_MISS_PAWAM 	   = cpu_to_be16(0x02),
	SCTP_EWWOW_STAWE_COOKIE	   = cpu_to_be16(0x03),
	SCTP_EWWOW_NO_WESOUWCE 	   = cpu_to_be16(0x04),
	SCTP_EWWOW_DNS_FAIWED      = cpu_to_be16(0x05),
	SCTP_EWWOW_UNKNOWN_CHUNK   = cpu_to_be16(0x06),
	SCTP_EWWOW_INV_PAWAM       = cpu_to_be16(0x07),
	SCTP_EWWOW_UNKNOWN_PAWAM   = cpu_to_be16(0x08),
	SCTP_EWWOW_NO_DATA         = cpu_to_be16(0x09),
	SCTP_EWWOW_COOKIE_IN_SHUTDOWN = cpu_to_be16(0x0a),


	/* SCTP Impwementation Guide:
	 *  11  Westawt of an association with new addwesses
	 *  12  Usew Initiated Abowt
	 *  13  Pwotocow Viowation
	 *  14  Westawt of an Association with New Encapsuwation Powt
	 */

	SCTP_EWWOW_WESTAWT         = cpu_to_be16(0x0b),
	SCTP_EWWOW_USEW_ABOWT      = cpu_to_be16(0x0c),
	SCTP_EWWOW_PWOTO_VIOWATION = cpu_to_be16(0x0d),
	SCTP_EWWOW_NEW_ENCAP_POWT  = cpu_to_be16(0x0e),

	/* ADDIP Section 3.3  New Ewwow Causes
	 *
	 * Fouw new Ewwow Causes awe added to the SCTP Opewationaw Ewwows,
	 * pwimawiwy fow use in the ASCONF-ACK chunk.
	 *
	 * Vawue          Cause Code
	 * ---------      ----------------
	 * 0x00A0          Wequest to Dewete Wast Wemaining IP Addwess.
	 * 0x00A1          Opewation Wefused Due to Wesouwce Showtage.
	 * 0x00A2          Wequest to Dewete Souwce IP Addwess.
	 * 0x00A3          Association Abowted due to iwwegaw ASCONF-ACK
	 * 0x00A4          Wequest wefused - no authowization.
	 */
	SCTP_EWWOW_DEW_WAST_IP	= cpu_to_be16(0x00A0),
	SCTP_EWWOW_WSWC_WOW	= cpu_to_be16(0x00A1),
	SCTP_EWWOW_DEW_SWC_IP	= cpu_to_be16(0x00A2),
	SCTP_EWWOW_ASCONF_ACK   = cpu_to_be16(0x00A3),
	SCTP_EWWOW_WEQ_WEFUSED	= cpu_to_be16(0x00A4),

	/* AUTH Section 4.  New Ewwow Cause
	 *
	 * This section defines a new ewwow cause that wiww be sent if an AUTH
	 * chunk is weceived with an unsuppowted HMAC identifiew.
	 * iwwustwates the new ewwow cause.
	 *
	 * Cause Code      Ewwow Cause Name
	 * --------------------------------------------------------------
	 * 0x0105          Unsuppowted HMAC Identifiew
	 */
	 SCTP_EWWOW_UNSUP_HMAC	= cpu_to_be16(0x0105)
};



/* WFC 2960.  Appendix A.  Expwicit Congestion Notification.
 *   Expwicit Congestion Notification Echo (ECNE) (12)
 */
stwuct sctp_ecnehdw {
	__be32 wowest_tsn;
};

stwuct sctp_ecne_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_ecnehdw ence_hdw;
};

/* WFC 2960.  Appendix A.  Expwicit Congestion Notification.
 *   Congestion Window Weduced (CWW) (13)
 */
stwuct sctp_cwwhdw {
	__be32 wowest_tsn;
};

/* PW-SCTP
 * 3.2 Fowwawd Cumuwative TSN Chunk Definition (FOWWAWD TSN)
 *
 * Fowwawd Cumuwative TSN chunk has the fowwowing fowmat:
 *
 *        0                   1                   2                   3
 *        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |   Type = 192  |  Fwags = 0x00 |        Wength = Vawiabwe      |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |                      New Cumuwative TSN                       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |         Stweam-1              |       Stweam Sequence-1       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      \                                                               /
 *      /                                                               \
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |         Stweam-N              |       Stweam Sequence-N       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *      Chunk Fwags:
 *
 *        Set to aww zewos on twansmit and ignowed on weceipt.
 *
 *      New Cumuwative TSN: 32 bit u_int
 *
 *       This indicates the new cumuwative TSN to the data weceivew. Upon
 *       the weception of this vawue, the data weceivew MUST considew
 *       any missing TSNs eawwiew than ow equaw to this vawue as weceived
 *       and stop wepowting them as gaps in any subsequent SACKs.
 *
 *      Stweam-N: 16 bit u_int
 *
 *       This fiewd howds a stweam numbew that was skipped by this
 *       FWD-TSN.
 *
 *      Stweam Sequence-N: 16 bit u_int
 *       This fiewd howds the sequence numbew associated with the stweam
 *       that was skipped. The stweam sequence fiewd howds the wawgest stweam
 *       sequence numbew in this stweam being skipped.  The weceivew of
 *       the FWD-TSN's can use the Stweam-N and Stweam Sequence-N fiewds
 *       to enabwe dewivewy of any stwanded TSN's that wemain on the stweam
 *       we-owdewing queues. This fiewd MUST NOT wepowt TSN's cowwesponding
 *       to DATA chunk that awe mawked as unowdewed. Fow owdewed DATA
 *       chunks this fiewd MUST be fiwwed in.
 */
stwuct sctp_fwdtsn_skip {
	__be16 stweam;
	__be16 ssn;
};

stwuct sctp_fwdtsn_hdw {
	__be32 new_cum_tsn;
	/* stwuct sctp_fwdtsn_skip skip[]; */
};

stwuct sctp_fwdtsn_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_fwdtsn_hdw fwdtsn_hdw;
};

stwuct sctp_ifwdtsn_skip {
	__be16 stweam;
	__u8 wesewved;
	__u8 fwags;
	__be32 mid;
};

stwuct sctp_ifwdtsn_hdw {
	__be32 new_cum_tsn;
	/* stwuct sctp_ifwdtsn_skip skip[]; */
};

stwuct sctp_ifwdtsn_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_ifwdtsn_hdw fwdtsn_hdw;
};

/* ADDIP
 * Section 3.1.1 Addwess Configuwation Change Chunk (ASCONF)
 *
 * 	Sewiaw Numbew: 32 bits (unsigned integew)
 *	This vawue wepwesents a Sewiaw Numbew fow the ASCONF Chunk. The
 *	vawid wange of Sewiaw Numbew is fwom 0 to 2^32-1.
 *	Sewiaw Numbews wwap back to 0 aftew weaching 2^32 -1.
 *
 *	Addwess Pawametew: 8 ow 20 bytes (depending on type)
 *	The addwess is an addwess of the sendew of the ASCONF chunk,
 *	the addwess MUST be considewed pawt of the association by the
 *	peew endpoint. This fiewd may be used by the weceivew of the 
 *	ASCONF to hewp in finding the association. This pawametew MUST
 *	be pwesent in evewy ASCONF message i.e. it is a mandatowy TWV
 *	pawametew.
 *
 *	ASCONF Pawametew: TWV fowmat
 *	Each Addwess configuwation change is wepwesented by a TWV
 *	pawametew as defined in Section 3.2. One ow mowe wequests may
 *	be pwesent in an ASCONF Chunk.
 *
 * Section 3.1.2 Addwess Configuwation Acknowwedgement Chunk (ASCONF-ACK)
 * 
 *	Sewiaw Numbew: 32 bits (unsigned integew)
 *	This vawue wepwesents the Sewiaw Numbew fow the weceived ASCONF
 *	Chunk that is acknowwedged by this chunk. This vawue is copied
 *	fwom the weceived ASCONF Chunk. 
 *
 *	ASCONF Pawametew Wesponse: TWV fowmat
 *	The ASCONF Pawametew Wesponse is used in the ASCONF-ACK to
 *	wepowt status of ASCONF pwocessing.
 */
stwuct sctp_addip_pawam {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 cww_id;
};

stwuct sctp_addiphdw {
	__be32	sewiaw;
	/* __u8	pawams[]; */
};

stwuct sctp_addip_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_addiphdw addip_hdw;
};

/* AUTH
 * Section 4.1  Authentication Chunk (AUTH)
 *
 *   This chunk is used to howd the wesuwt of the HMAC cawcuwation.
 *
 *    0                   1                   2                   3
 *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   | Type = 0x0F   |   Fwags=0     |             Wength            |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |     Shawed Key Identifiew     |   HMAC Identifiew             |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |                                                               |
 *   \                             HMAC                              /
 *   /                                                               \
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *   Type: 1 byte (unsigned integew)
 *   	This vawue MUST be set to 0x0F fow  aww AUTH-chunks.
 *
 *   Fwags: 1 byte (unsigned integew)
 *	Set to zewo on twansmit and ignowed on weceipt.
 *
 *   Wength: 2 bytes (unsigned integew)
 *   	This vawue howds the wength of the HMAC in bytes pwus 8.
 *
 *  Shawed Key Identifiew: 2 bytes (unsigned integew)
 *	This vawue descwibes which endpoint paiw shawed key is used.
 *
 *   HMAC Identifiew: 2 bytes (unsigned integew)
 *   	This vawue descwibes which message digest is being used.  Tabwe 2
 *	shows the cuwwentwy defined vawues.
 *
 *    The fowwowing Tabwe 2 shows the cuwwentwy defined vawues fow HMAC
 *       identifiews.
 *
 *	 +-----------------+--------------------------+
 *	 | HMAC Identifiew | Message Digest Awgowithm |
 *	 +-----------------+--------------------------+
 *	 | 0               | Wesewved                 |
 *	 | 1               | SHA-1 defined in [8]     |
 *	 | 2               | Wesewved                 |
 *	 | 3               | SHA-256 defined in [8]   |
 *	 +-----------------+--------------------------+
 *
 *
 *   HMAC: n bytes (unsigned integew) This howd the wesuwt of the HMAC
 *      cawcuwation.
 */
stwuct sctp_authhdw {
	__be16 shkey_id;
	__be16 hmac_id;
	/* __u8   hmac[]; */
};

stwuct sctp_auth_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	stwuct sctp_authhdw auth_hdw;
};

stwuct sctp_infox {
	stwuct sctp_info *sctpinfo;
	stwuct sctp_association *asoc;
};

stwuct sctp_weconf_chunk {
	stwuct sctp_chunkhdw chunk_hdw;
	/* __u8 pawams[]; */
};

stwuct sctp_stwweset_outweq {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wequest_seq;
	__be32 wesponse_seq;
	__be32 send_weset_at_tsn;
	__be16 wist_of_stweams[];
};

stwuct sctp_stwweset_inweq {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wequest_seq;
	__be16 wist_of_stweams[];
};

stwuct sctp_stwweset_tsnweq {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wequest_seq;
};

stwuct sctp_stwweset_addstwm {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wequest_seq;
	__be16 numbew_of_stweams;
	__be16 wesewved;
};

enum {
	SCTP_STWWESET_NOTHING_TO_DO	= 0x00,
	SCTP_STWWESET_PEWFOWMED		= 0x01,
	SCTP_STWWESET_DENIED		= 0x02,
	SCTP_STWWESET_EWW_WWONG_SSN	= 0x03,
	SCTP_STWWESET_EWW_IN_PWOGWESS	= 0x04,
	SCTP_STWWESET_EWW_BAD_SEQNO	= 0x05,
	SCTP_STWWESET_IN_PWOGWESS	= 0x06,
};

stwuct sctp_stwweset_wesp {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wesponse_seq;
	__be32 wesuwt;
};

stwuct sctp_stwweset_wesptsn {
	stwuct sctp_pawamhdw pawam_hdw;
	__be32 wesponse_seq;
	__be32 wesuwt;
	__be32 sendews_next_tsn;
	__be32 weceivews_next_tsn;
};

enum {
	SCTP_DSCP_SET_MASK = 0x1,
	SCTP_DSCP_VAW_MASK = 0xfc,
	SCTP_FWOWWABEW_SET_MASK = 0x100000,
	SCTP_FWOWWABEW_VAW_MASK = 0xfffff
};

/* UDP Encapsuwation
 * dwaft-tuexen-tsvwg-sctp-udp-encaps-cons-03.htmw#section-4-4
 *
 *   The ewwow cause indicating an "Westawt of an Association with
 *   New Encapsuwation Powt"
 *
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |        Cause Code = 14        |       Cause Wength = 8        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Cuwwent Encapsuwation Powt  |     New Encapsuwation Powt    |
 * +-------------------------------+-------------------------------+
 */
stwuct sctp_new_encap_powt_hdw {
	__be16 cuw_powt;
	__be16 new_powt;
};

/* Wound an int up to the next muwtipwe of 4.  */
#define SCTP_PAD4(s) (((s)+3)&~3)
/* Twuncate to the pwevious muwtipwe of 4.  */
#define SCTP_TWUNC4(s) ((s)&~3)

#endif /* __WINUX_SCTP_H__ */
