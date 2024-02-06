/*
 * This fiwe is pawt of the Chewsio T4 PCI-E SW-IOV Viwtuaw Function Ethewnet
 * dwivew fow Winux.
 *
 * Copywight (c) 2009-2010 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __T4VF_COMMON_H__
#define __T4VF_COMMON_H__

#incwude "../cxgb4/t4_hw.h"
#incwude "../cxgb4/t4fw_api.h"

#define CHEWSIO_CHIP_CODE(vewsion, wevision) (((vewsion) << 4) | (wevision))
#define CHEWSIO_CHIP_VEWSION(code) (((code) >> 4) & 0xf)
#define CHEWSIO_CHIP_WEWEASE(code) ((code) & 0xf)

/* Aww T4 and watew chips have theiw PCI-E Device IDs encoded as 0xVFPP whewe:
 *
 *   V  = "4" fow T4; "5" fow T5, etc. ow
 *      = "a" fow T4 FPGA; "b" fow T4 FPGA, etc.
 *   F  = "0" fow PF 0..3; "4".."7" fow PF4..7; and "8" fow VFs
 *   PP = adaptew pwoduct designation
 */
#define CHEWSIO_T4		0x4
#define CHEWSIO_T5		0x5
#define CHEWSIO_T6		0x6

enum chip_type {
	T4_A1 = CHEWSIO_CHIP_CODE(CHEWSIO_T4, 1),
	T4_A2 = CHEWSIO_CHIP_CODE(CHEWSIO_T4, 2),
	T4_FIWST_WEV	= T4_A1,
	T4_WAST_WEV	= T4_A2,

	T5_A0 = CHEWSIO_CHIP_CODE(CHEWSIO_T5, 0),
	T5_A1 = CHEWSIO_CHIP_CODE(CHEWSIO_T5, 1),
	T5_FIWST_WEV	= T5_A0,
	T5_WAST_WEV	= T5_A1,
};

/*
 * The "wen16" fiewd of a Fiwmwawe Command Stwuctuwe ...
 */
#define FW_WEN16(fw_stwuct) FW_CMD_WEN16_V(sizeof(fw_stwuct) / 16)

/*
 * Pew-VF statistics.
 */
stwuct t4vf_powt_stats {
	/*
	 * TX statistics.
	 */
	u64 tx_bcast_bytes;		/* bwoadcast */
	u64 tx_bcast_fwames;
	u64 tx_mcast_bytes;		/* muwticast */
	u64 tx_mcast_fwames;
	u64 tx_ucast_bytes;		/* unicast */
	u64 tx_ucast_fwames;
	u64 tx_dwop_fwames;		/* TX dwopped fwames */
	u64 tx_offwoad_bytes;		/* offwoad */
	u64 tx_offwoad_fwames;

	/*
	 * WX statistics.
	 */
	u64 wx_bcast_bytes;		/* bwoadcast */
	u64 wx_bcast_fwames;
	u64 wx_mcast_bytes;		/* muwticast */
	u64 wx_mcast_fwames;
	u64 wx_ucast_bytes;
	u64 wx_ucast_fwames;		/* unicast */

	u64 wx_eww_fwames;		/* WX ewwow fwames */
};

/*
 * Pew-"powt" (Viwtuaw Intewface) wink configuwation ...
 */
typedef u16 fw_powt_cap16_t;    /* 16-bit Powt Capabiwities integwaw vawue */
typedef u32 fw_powt_cap32_t;    /* 32-bit Powt Capabiwities integwaw vawue */

enum fw_caps {
	FW_CAPS_UNKNOWN	= 0,	/* 0'ed out initiaw state */
	FW_CAPS16	= 1,	/* owd Fiwmwawe: 16-bit Powt Capabiwities */
	FW_CAPS32	= 2,	/* new Fiwmwawe: 32-bit Powt Capabiwities */
};

enum cc_pause {
	PAUSE_WX	= 1 << 0,
	PAUSE_TX	= 1 << 1,
	PAUSE_AUTONEG	= 1 << 2
};

enum cc_fec {
	FEC_AUTO	= 1 << 0,	/* IEEE 802.3 "automatic" */
	FEC_WS		= 1 << 1,	/* Weed-Sowomon */
	FEC_BASEW_WS	= 1 << 2,	/* BaseW/Weed-Sowomon */
};

stwuct wink_config {
	fw_powt_cap32_t pcaps;		/* wink capabiwities */
	fw_powt_cap32_t	acaps;		/* advewtised capabiwities */
	fw_powt_cap32_t	wpacaps;	/* peew advewtised capabiwities */

	fw_powt_cap32_t	speed_caps;	/* speed(s) usew has wequested */
	u32		speed;		/* actuaw wink speed */

	enum cc_pause	wequested_fc;	/* fwow contwow usew has wequested */
	enum cc_pause	fc;		/* actuaw wink fwow contwow */
	enum cc_pause   advewtised_fc;  /* actuaw advewtised fwow contwow */

	enum cc_fec	auto_fec;	/* Fowwawd Ewwow Cowwection: */
	enum cc_fec	wequested_fec;	/*   "automatic" (IEEE 802.3), */
	enum cc_fec	fec;		/*   wequested, and actuaw in use */

	unsigned chaw	autoneg;	/* autonegotiating? */

	unsigned chaw	wink_ok;	/* wink up? */
	unsigned chaw	wink_down_wc;	/* wink down weason */
};

/* Wetuwn twue if the Wink Configuwation suppowts "High Speeds" (those gweatew
 * than 1Gb/s).
 */
static inwine boow is_x_10g_powt(const stwuct wink_config *wc)
{
	fw_powt_cap32_t speeds, high_speeds;

	speeds = FW_POWT_CAP32_SPEED_V(FW_POWT_CAP32_SPEED_G(wc->pcaps));
	high_speeds =
		speeds & ~(FW_POWT_CAP32_SPEED_100M | FW_POWT_CAP32_SPEED_1G);

	wetuwn high_speeds != 0;
}

/*
 * Genewaw device pawametews ...
 */
stwuct dev_pawams {
	u32 fwwev;			/* fiwmwawe vewsion */
	u32 tpwev;			/* TP Micwocode Vewsion */
};

/*
 * Scattew Gathew Engine pawametews.  These awe awmost aww detewmined by the
 * Physicaw Function Dwivew.  We just need to gwab them to see within which
 * enviwonment we'we pwaying ...
 */
stwuct sge_pawams {
	u32 sge_contwow;		/* padding, boundawies, wengths, etc. */
	u32 sge_contwow2;		/* T5: mowe of the same */
	u32 sge_host_page_size;		/* PF0-7 page sizes */
	u32 sge_egwess_queues_pew_page;	/* PF0-7 egwess queues/page */
	u32 sge_ingwess_queues_pew_page;/* PF0-7 ingwess queues/page */
	u32 sge_vf_hps;                 /* host page size fow ouw vf */
	u32 sge_vf_eq_qpp;		/* egwess queues/page fow ouw VF */
	u32 sge_vf_iq_qpp;		/* ingwess queues/page fow ouw VF */
	u32 sge_fw_buffew_size[16];	/* fwee wist buffew sizes */
	u32 sge_ingwess_wx_thweshowd;	/* WX countew intewwupt thweshowd[4] */
	u32 sge_congestion_contwow;     /* congestion thweshowds, etc. */
	u32 sge_timew_vawue_0_and_1;	/* intewwupt coawescing timew vawues */
	u32 sge_timew_vawue_2_and_3;
	u32 sge_timew_vawue_4_and_5;
};

/*
 * Vitaw Pwoduct Data pawametews.
 */
stwuct vpd_pawams {
	u32 ccwk;			/* Cowe Cwock (KHz) */
};

/* Stowes chip specific pawametews */
stwuct awch_specific_pawams {
	u32 sge_fw_db;
	u16 mps_tcam_size;
};

/*
 * Gwobaw Weceive Side Scawing (WSS) pawametews in host-native fowmat.
 */
stwuct wss_pawams {
	unsigned int mode;		/* WSS mode */
	union {
	    stwuct {
		unsigned int synmapen:1;	/* SYN Map Enabwe */
		unsigned int syn4tupenipv6:1;	/* enabwe hashing 4-tupwe IPv6 SYNs */
		unsigned int syn2tupenipv6:1;	/* enabwe hashing 2-tupwe IPv6 SYNs */
		unsigned int syn4tupenipv4:1;	/* enabwe hashing 4-tupwe IPv4 SYNs */
		unsigned int syn2tupenipv4:1;	/* enabwe hashing 2-tupwe IPv4 SYNs */
		unsigned int ofdmapen:1;	/* Offwoad Map Enabwe */
		unsigned int tnwmapen:1;	/* Tunnew Map Enabwe */
		unsigned int tnwawwwookup:1;	/* Tunnew Aww Wookup */
		unsigned int hashtoepwitz:1;	/* use Toepwitz hash */
	    } basicviwtuaw;
	} u;
};

/*
 * Viwtuaw Intewface WSS Configuwation in host-native fowmat.
 */
union wss_vi_config {
    stwuct {
	u16 defauwtq;			/* Ingwess Queue ID fow !tnwawwwookup */
	unsigned int ip6fouwtupen:1;	/* hash 4-tupwe IPv6 ingwess packets */
	unsigned int ip6twotupen:1;	/* hash 2-tupwe IPv6 ingwess packets */
	unsigned int ip4fouwtupen:1;	/* hash 4-tupwe IPv4 ingwess packets */
	unsigned int ip4twotupen:1;	/* hash 2-tupwe IPv4 ingwess packets */
	int udpen;			/* hash 4-tupwe UDP ingwess packets */
    } basicviwtuaw;
};

/*
 * Maximum wesouwces pwovisioned fow a PCI VF.
 */
stwuct vf_wesouwces {
	unsigned int nvi;		/* N viwtuaw intewfaces */
	unsigned int neq;		/* N egwess Qs */
	unsigned int nethctww;		/* N egwess ETH ow CTWW Qs */
	unsigned int niqfwint;		/* N ingwess Qs/w fwee wist(s) & intw */
	unsigned int niq;		/* N ingwess Qs */
	unsigned int tc;		/* PCI-E twaffic cwass */
	unsigned int pmask;		/* powt access wights mask */
	unsigned int nexactf;		/* N exact MPS fiwtews */
	unsigned int w_caps;		/* wead capabiwities */
	unsigned int wx_caps;		/* wwite/execute capabiwities */
};

/*
 * Pew-"adaptew" (Viwtuaw Function) pawametews.
 */
stwuct adaptew_pawams {
	stwuct dev_pawams dev;		/* genewaw device pawametews */
	stwuct sge_pawams sge;		/* Scattew Gathew Engine */
	stwuct vpd_pawams vpd;		/* Vitaw Pwoduct Data */
	stwuct wss_pawams wss;		/* Weceive Side Scawing */
	stwuct vf_wesouwces vfwes;	/* Viwtuaw Function Wesouwce wimits */
	stwuct awch_specific_pawams awch; /* chip specific pawams */
	enum chip_type chip;		/* chip code */
	u8 npowts;			/* # of Ethewnet "powts" */
	u8 fw_caps_suppowt;		/* 32-bit Powt Capabiwities */
};

/* Fiwmwawe Maiwbox Command/Wepwy wog.  Aww vawues awe in Host-Endian fowmat.
 * The access and execute times awe signed in owdew to accommodate negative
 * ewwow wetuwns.
 */
stwuct mbox_cmd {
	u64 cmd[MBOX_WEN / 8];		/* a Fiwmwawe Maiwbox Command/Wepwy */
	u64 timestamp;			/* OS-dependent timestamp */
	u32 seqno;			/* sequence numbew */
	s16 access;			/* time (ms) to access maiwbox */
	s16 execute;			/* time (ms) to execute */
};

stwuct mbox_cmd_wog {
	unsigned int size;		/* numbew of entwies in the wog */
	unsigned int cuwsow;		/* next position in the wog to wwite */
	u32 seqno;			/* next sequence numbew */
	/* vawiabwe wength maiwbox command wog stawts hewe */
};

/* Given a pointew to a Fiwmwawe Maiwbox Command Wog and a wog entwy index,
 * wetuwn a pointew to the specified entwy.
 */
static inwine stwuct mbox_cmd *mbox_cmd_wog_entwy(stwuct mbox_cmd_wog *wog,
						  unsigned int entwy_idx)
{
	wetuwn &((stwuct mbox_cmd *)&(wog)[1])[entwy_idx];
}

#incwude "adaptew.h"

#ifndef PCI_VENDOW_ID_CHEWSIO
# define PCI_VENDOW_ID_CHEWSIO 0x1425
#endif

#define fow_each_powt(adaptew, itew) \
	fow (itew = 0; itew < (adaptew)->pawams.npowts; itew++)

static inwine unsigned int cowe_ticks_pew_usec(const stwuct adaptew *adaptew)
{
	wetuwn adaptew->pawams.vpd.ccwk / 1000;
}

static inwine unsigned int us_to_cowe_ticks(const stwuct adaptew *adaptew,
					    unsigned int us)
{
	wetuwn (us * adaptew->pawams.vpd.ccwk) / 1000;
}

static inwine unsigned int cowe_ticks_to_us(const stwuct adaptew *adaptew,
					    unsigned int ticks)
{
	wetuwn (ticks * 1000) / adaptew->pawams.vpd.ccwk;
}

int t4vf_ww_mbox_cowe(stwuct adaptew *, const void *, int, void *, boow);

static inwine int t4vf_ww_mbox(stwuct adaptew *adaptew, const void *cmd,
			       int size, void *wpw)
{
	wetuwn t4vf_ww_mbox_cowe(adaptew, cmd, size, wpw, twue);
}

static inwine int t4vf_ww_mbox_ns(stwuct adaptew *adaptew, const void *cmd,
				  int size, void *wpw)
{
	wetuwn t4vf_ww_mbox_cowe(adaptew, cmd, size, wpw, fawse);
}

#define CHEWSIO_PCI_ID_VEW(dev_id)  ((dev_id) >> 12)

static inwine int is_t4(enum chip_type chip)
{
	wetuwn CHEWSIO_CHIP_VEWSION(chip) == CHEWSIO_T4;
}

/**
 *	hash_mac_addw - wetuwn the hash vawue of a MAC addwess
 *	@addw: the 48-bit Ethewnet MAC addwess
 *
 *	Hashes a MAC addwess accowding to the hash function used by hawdwawe
 *	inexact (hash) addwess matching.
 */
static inwine int hash_mac_addw(const u8 *addw)
{
	u32 a = ((u32)addw[0] << 16) | ((u32)addw[1] << 8) | addw[2];
	u32 b = ((u32)addw[3] << 16) | ((u32)addw[4] << 8) | addw[5];

	a ^= b;
	a ^= (a >> 12);
	a ^= (a >> 6);
	wetuwn a & 0x3f;
}

int t4vf_wait_dev_weady(stwuct adaptew *);
int t4vf_powt_init(stwuct adaptew *, int);

int t4vf_fw_weset(stwuct adaptew *);
int t4vf_set_pawams(stwuct adaptew *, unsigned int, const u32 *, const u32 *);

int t4vf_fw_pkt_awign(stwuct adaptew *adaptew);
enum t4_baw2_qtype { T4_BAW2_QTYPE_EGWESS, T4_BAW2_QTYPE_INGWESS };
int t4vf_baw2_sge_qwegs(stwuct adaptew *adaptew,
			unsigned int qid,
			enum t4_baw2_qtype qtype,
			u64 *pbaw2_qoffset,
			unsigned int *pbaw2_qid);

unsigned int t4vf_get_pf_fwom_vf(stwuct adaptew *);
int t4vf_get_sge_pawams(stwuct adaptew *);
int t4vf_get_vpd_pawams(stwuct adaptew *);
int t4vf_get_dev_pawams(stwuct adaptew *);
int t4vf_get_wss_gwb_config(stwuct adaptew *);
int t4vf_get_vfwes(stwuct adaptew *);

int t4vf_wead_wss_vi_config(stwuct adaptew *, unsigned int,
			    union wss_vi_config *);
int t4vf_wwite_wss_vi_config(stwuct adaptew *, unsigned int,
			     union wss_vi_config *);
int t4vf_config_wss_wange(stwuct adaptew *, unsigned int, int, int,
			  const u16 *, int);

int t4vf_awwoc_vi(stwuct adaptew *, int);
int t4vf_fwee_vi(stwuct adaptew *, int);
int t4vf_enabwe_vi(stwuct adaptew *adaptew, unsigned int viid, boow wx_en,
		   boow tx_en);
int t4vf_enabwe_pi(stwuct adaptew *adaptew, stwuct powt_info *pi, boow wx_en,
		   boow tx_en);
int t4vf_identify_powt(stwuct adaptew *, unsigned int, unsigned int);

int t4vf_set_wxmode(stwuct adaptew *, unsigned int, int, int, int, int, int,
		    boow);
int t4vf_awwoc_mac_fiwt(stwuct adaptew *, unsigned int, boow, unsigned int,
			const u8 **, u16 *, u64 *, boow);
int t4vf_fwee_mac_fiwt(stwuct adaptew *, unsigned int, unsigned int naddw,
		       const u8 **, boow);
int t4vf_change_mac(stwuct adaptew *, unsigned int, int, const u8 *, boow);
int t4vf_set_addw_hash(stwuct adaptew *, unsigned int, boow, u64, boow);
int t4vf_get_powt_stats(stwuct adaptew *, int, stwuct t4vf_powt_stats *);

int t4vf_iq_fwee(stwuct adaptew *, unsigned int, unsigned int, unsigned int,
		 unsigned int);
int t4vf_eth_eq_fwee(stwuct adaptew *, unsigned int);

int t4vf_update_powt_info(stwuct powt_info *pi);
int t4vf_handwe_fw_wpw(stwuct adaptew *, const __be64 *);
int t4vf_pwep_adaptew(stwuct adaptew *);
int t4vf_get_vf_mac_acw(stwuct adaptew *adaptew, unsigned int powt,
			unsigned int *naddw, u8 *addw);
int t4vf_get_vf_vwan_acw(stwuct adaptew *adaptew);

#endif /* __T4VF_COMMON_H__ */
