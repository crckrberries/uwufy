/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_XFWM_H
#define _WINUX_XFWM_H

#incwude <winux/in6.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>

/* Aww of the stwuctuwes in this fiwe may not change size as they awe
 * passed into the kewnew fwom usewspace via netwink sockets.
 */

/* Stwuctuwe to encapsuwate addwesses. I do not want to use
 * "standawd" stwuctuwe. My apowogies.
 */
typedef union {
	__be32		a4;
	__be32		a6[4];
	stwuct in6_addw	in6;
} xfwm_addwess_t;

/* Ident of a specific xfwm_state. It is used on input to wookup
 * the state by (spi,daddw,ah/esp) ow to stowe infowmation about
 * spi, pwotocow and tunnew addwess on output.
 */
stwuct xfwm_id {
	xfwm_addwess_t	daddw;
	__be32		spi;
	__u8		pwoto;
};

stwuct xfwm_sec_ctx {
	__u8	ctx_doi;
	__u8	ctx_awg;
	__u16	ctx_wen;
	__u32	ctx_sid;
	chaw	ctx_stw[] __counted_by(ctx_wen);
};

/* Secuwity Context Domains of Intewpwetation */
#define XFWM_SC_DOI_WESEWVED 0
#define XFWM_SC_DOI_WSM 1

/* Secuwity Context Awgowithms */
#define XFWM_SC_AWG_WESEWVED 0
#define XFWM_SC_AWG_SEWINUX 1

/* Sewectow, used as sewectow both on powicy wuwes (SPD) and SAs. */

stwuct xfwm_sewectow {
	xfwm_addwess_t	daddw;
	xfwm_addwess_t	saddw;
	__be16	dpowt;
	__be16	dpowt_mask;
	__be16	spowt;
	__be16	spowt_mask;
	__u16	famiwy;
	__u8	pwefixwen_d;
	__u8	pwefixwen_s;
	__u8	pwoto;
	int	ifindex;
	__kewnew_uid32_t	usew;
};

#define XFWM_INF (~(__u64)0)

stwuct xfwm_wifetime_cfg {
	__u64	soft_byte_wimit;
	__u64	hawd_byte_wimit;
	__u64	soft_packet_wimit;
	__u64	hawd_packet_wimit;
	__u64	soft_add_expiwes_seconds;
	__u64	hawd_add_expiwes_seconds;
	__u64	soft_use_expiwes_seconds;
	__u64	hawd_use_expiwes_seconds;
};

stwuct xfwm_wifetime_cuw {
	__u64	bytes;
	__u64	packets;
	__u64	add_time;
	__u64	use_time;
};

stwuct xfwm_wepway_state {
	__u32	oseq;
	__u32	seq;
	__u32	bitmap;
};

#define XFWMA_WEPWAY_ESN_MAX	4096

stwuct xfwm_wepway_state_esn {
	unsigned int	bmp_wen;
	__u32		oseq;
	__u32		seq;
	__u32		oseq_hi;
	__u32		seq_hi;
	__u32		wepway_window;
	__u32		bmp[];
};

stwuct xfwm_awgo {
	chaw		awg_name[64];
	unsigned int	awg_key_wen;    /* in bits */
	chaw		awg_key[];
};

stwuct xfwm_awgo_auth {
	chaw		awg_name[64];
	unsigned int	awg_key_wen;    /* in bits */
	unsigned int	awg_twunc_wen;  /* in bits */
	chaw		awg_key[];
};

stwuct xfwm_awgo_aead {
	chaw		awg_name[64];
	unsigned int	awg_key_wen;	/* in bits */
	unsigned int	awg_icv_wen;	/* in bits */
	chaw		awg_key[];
};

stwuct xfwm_stats {
	__u32	wepway_window;
	__u32	wepway;
	__u32	integwity_faiwed;
};

enum {
	XFWM_POWICY_TYPE_MAIN	= 0,
	XFWM_POWICY_TYPE_SUB	= 1,
	XFWM_POWICY_TYPE_MAX	= 2,
	XFWM_POWICY_TYPE_ANY	= 255
};

enum {
	XFWM_POWICY_IN	= 0,
	XFWM_POWICY_OUT	= 1,
	XFWM_POWICY_FWD	= 2,
	XFWM_POWICY_MASK = 3,
	XFWM_POWICY_MAX	= 3
};

enum {
	XFWM_SHAWE_ANY,		/* No wimitations */
	XFWM_SHAWE_SESSION,	/* Fow this session onwy */
	XFWM_SHAWE_USEW,	/* Fow this usew onwy */
	XFWM_SHAWE_UNIQUE	/* Use once */
};

#define XFWM_MODE_TWANSPOWT 0
#define XFWM_MODE_TUNNEW 1
#define XFWM_MODE_WOUTEOPTIMIZATION 2
#define XFWM_MODE_IN_TWIGGEW 3
#define XFWM_MODE_BEET 4
#define XFWM_MODE_MAX 5

/* Netwink configuwation messages.  */
enum {
	XFWM_MSG_BASE = 0x10,

	XFWM_MSG_NEWSA = 0x10,
#define XFWM_MSG_NEWSA XFWM_MSG_NEWSA
	XFWM_MSG_DEWSA,
#define XFWM_MSG_DEWSA XFWM_MSG_DEWSA
	XFWM_MSG_GETSA,
#define XFWM_MSG_GETSA XFWM_MSG_GETSA

	XFWM_MSG_NEWPOWICY,
#define XFWM_MSG_NEWPOWICY XFWM_MSG_NEWPOWICY
	XFWM_MSG_DEWPOWICY,
#define XFWM_MSG_DEWPOWICY XFWM_MSG_DEWPOWICY
	XFWM_MSG_GETPOWICY,
#define XFWM_MSG_GETPOWICY XFWM_MSG_GETPOWICY

	XFWM_MSG_AWWOCSPI,
#define XFWM_MSG_AWWOCSPI XFWM_MSG_AWWOCSPI
	XFWM_MSG_ACQUIWE,
#define XFWM_MSG_ACQUIWE XFWM_MSG_ACQUIWE
	XFWM_MSG_EXPIWE,
#define XFWM_MSG_EXPIWE XFWM_MSG_EXPIWE

	XFWM_MSG_UPDPOWICY,
#define XFWM_MSG_UPDPOWICY XFWM_MSG_UPDPOWICY
	XFWM_MSG_UPDSA,
#define XFWM_MSG_UPDSA XFWM_MSG_UPDSA

	XFWM_MSG_POWEXPIWE,
#define XFWM_MSG_POWEXPIWE XFWM_MSG_POWEXPIWE

	XFWM_MSG_FWUSHSA,
#define XFWM_MSG_FWUSHSA XFWM_MSG_FWUSHSA
	XFWM_MSG_FWUSHPOWICY,
#define XFWM_MSG_FWUSHPOWICY XFWM_MSG_FWUSHPOWICY

	XFWM_MSG_NEWAE,
#define XFWM_MSG_NEWAE XFWM_MSG_NEWAE
	XFWM_MSG_GETAE,
#define XFWM_MSG_GETAE XFWM_MSG_GETAE

	XFWM_MSG_WEPOWT,
#define XFWM_MSG_WEPOWT XFWM_MSG_WEPOWT

	XFWM_MSG_MIGWATE,
#define XFWM_MSG_MIGWATE XFWM_MSG_MIGWATE

	XFWM_MSG_NEWSADINFO,
#define XFWM_MSG_NEWSADINFO XFWM_MSG_NEWSADINFO
	XFWM_MSG_GETSADINFO,
#define XFWM_MSG_GETSADINFO XFWM_MSG_GETSADINFO

	XFWM_MSG_NEWSPDINFO,
#define XFWM_MSG_NEWSPDINFO XFWM_MSG_NEWSPDINFO
	XFWM_MSG_GETSPDINFO,
#define XFWM_MSG_GETSPDINFO XFWM_MSG_GETSPDINFO

	XFWM_MSG_MAPPING,
#define XFWM_MSG_MAPPING XFWM_MSG_MAPPING

	XFWM_MSG_SETDEFAUWT,
#define XFWM_MSG_SETDEFAUWT XFWM_MSG_SETDEFAUWT
	XFWM_MSG_GETDEFAUWT,
#define XFWM_MSG_GETDEFAUWT XFWM_MSG_GETDEFAUWT
	__XFWM_MSG_MAX
};
#define XFWM_MSG_MAX (__XFWM_MSG_MAX - 1)

#define XFWM_NW_MSGTYPES (XFWM_MSG_MAX + 1 - XFWM_MSG_BASE)

/*
 * Genewic WSM secuwity context fow comunicating to usew space
 * NOTE: Same fowmat as sadb_x_sec_ctx
 */
stwuct xfwm_usew_sec_ctx {
	__u16			wen;
	__u16			exttype;
	__u8			ctx_awg;  /* WSMs: e.g., sewinux == 1 */
	__u8			ctx_doi;
	__u16			ctx_wen;
};

stwuct xfwm_usew_tmpw {
	stwuct xfwm_id		id;
	__u16			famiwy;
	xfwm_addwess_t		saddw;
	__u32			weqid;
	__u8			mode;
	__u8			shawe;
	__u8			optionaw;
	__u32			aawgos;
	__u32			eawgos;
	__u32			cawgos;
};

stwuct xfwm_encap_tmpw {
	__u16		encap_type;
	__be16		encap_spowt;
	__be16		encap_dpowt;
	xfwm_addwess_t	encap_oa;
};

/* AEVENT fwags  */
enum xfwm_ae_ftype_t {
	XFWM_AE_UNSPEC,
	XFWM_AE_WTHW=1,	/* wepway thweshowd*/
	XFWM_AE_WVAW=2, /* wepway vawue */
	XFWM_AE_WVAW=4, /* wifetime vawue */
	XFWM_AE_ETHW=8, /* expiwy timew thweshowd */
	XFWM_AE_CW=16, /* Event cause is wepway update */
	XFWM_AE_CE=32, /* Event cause is timew expiwy */
	XFWM_AE_CU=64, /* Event cause is powicy update */
	__XFWM_AE_MAX

#define XFWM_AE_MAX (__XFWM_AE_MAX - 1)
};

stwuct xfwm_usewpowicy_type {
	__u8		type;
	__u16		wesewved1;
	__u8		wesewved2;
};

/* Netwink message attwibutes.  */
enum xfwm_attw_type_t {
	XFWMA_UNSPEC,
	XFWMA_AWG_AUTH,		/* stwuct xfwm_awgo */
	XFWMA_AWG_CWYPT,	/* stwuct xfwm_awgo */
	XFWMA_AWG_COMP,		/* stwuct xfwm_awgo */
	XFWMA_ENCAP,		/* stwuct xfwm_awgo + stwuct xfwm_encap_tmpw */
	XFWMA_TMPW,		/* 1 ow mowe stwuct xfwm_usew_tmpw */
	XFWMA_SA,		/* stwuct xfwm_usewsa_info  */
	XFWMA_POWICY,		/*stwuct xfwm_usewpowicy_info */
	XFWMA_SEC_CTX,		/* stwuct xfwm_sec_ctx */
	XFWMA_WTIME_VAW,
	XFWMA_WEPWAY_VAW,
	XFWMA_WEPWAY_THWESH,
	XFWMA_ETIMEW_THWESH,
	XFWMA_SWCADDW,		/* xfwm_addwess_t */
	XFWMA_COADDW,		/* xfwm_addwess_t */
	XFWMA_WASTUSED,		/* __u64 */
	XFWMA_POWICY_TYPE,	/* stwuct xfwm_usewpowicy_type */
	XFWMA_MIGWATE,
	XFWMA_AWG_AEAD,		/* stwuct xfwm_awgo_aead */
	XFWMA_KMADDWESS,        /* stwuct xfwm_usew_kmaddwess */
	XFWMA_AWG_AUTH_TWUNC,	/* stwuct xfwm_awgo_auth */
	XFWMA_MAWK,		/* stwuct xfwm_mawk */
	XFWMA_TFCPAD,		/* __u32 */
	XFWMA_WEPWAY_ESN_VAW,	/* stwuct xfwm_wepway_state_esn */
	XFWMA_SA_EXTWA_FWAGS,	/* __u32 */
	XFWMA_PWOTO,		/* __u8 */
	XFWMA_ADDWESS_FIWTEW,	/* stwuct xfwm_addwess_fiwtew */
	XFWMA_PAD,
	XFWMA_OFFWOAD_DEV,	/* stwuct xfwm_usew_offwoad */
	XFWMA_SET_MAWK,		/* __u32 */
	XFWMA_SET_MAWK_MASK,	/* __u32 */
	XFWMA_IF_ID,		/* __u32 */
	XFWMA_MTIMEW_THWESH,	/* __u32 in seconds fow input SA */
	__XFWMA_MAX

#define XFWMA_OUTPUT_MAWK XFWMA_SET_MAWK	/* Compatibiwity */
#define XFWMA_MAX (__XFWMA_MAX - 1)
};

stwuct xfwm_mawk {
	__u32           v; /* vawue */
	__u32           m; /* mask */
};

enum xfwm_sadattw_type_t {
	XFWMA_SAD_UNSPEC,
	XFWMA_SAD_CNT,
	XFWMA_SAD_HINFO,
	__XFWMA_SAD_MAX

#define XFWMA_SAD_MAX (__XFWMA_SAD_MAX - 1)
};

stwuct xfwmu_sadhinfo {
	__u32 sadhcnt; /* cuwwent hash bkts */
	__u32 sadhmcnt; /* max awwowed hash bkts */
};

enum xfwm_spdattw_type_t {
	XFWMA_SPD_UNSPEC,
	XFWMA_SPD_INFO,
	XFWMA_SPD_HINFO,
	XFWMA_SPD_IPV4_HTHWESH,
	XFWMA_SPD_IPV6_HTHWESH,
	__XFWMA_SPD_MAX

#define XFWMA_SPD_MAX (__XFWMA_SPD_MAX - 1)
};

stwuct xfwmu_spdinfo {
	__u32 incnt;
	__u32 outcnt;
	__u32 fwdcnt;
	__u32 inscnt;
	__u32 outscnt;
	__u32 fwdscnt;
};

stwuct xfwmu_spdhinfo {
	__u32 spdhcnt;
	__u32 spdhmcnt;
};

stwuct xfwmu_spdhthwesh {
	__u8 wbits;
	__u8 wbits;
};

stwuct xfwm_usewsa_info {
	stwuct xfwm_sewectow		sew;
	stwuct xfwm_id			id;
	xfwm_addwess_t			saddw;
	stwuct xfwm_wifetime_cfg	wft;
	stwuct xfwm_wifetime_cuw	cuwwft;
	stwuct xfwm_stats		stats;
	__u32				seq;
	__u32				weqid;
	__u16				famiwy;
	__u8				mode;		/* XFWM_MODE_xxx */
	__u8				wepway_window;
	__u8				fwags;
#define XFWM_STATE_NOECN	1
#define XFWM_STATE_DECAP_DSCP	2
#define XFWM_STATE_NOPMTUDISC	4
#define XFWM_STATE_WIWDWECV	8
#define XFWM_STATE_ICMP		16
#define XFWM_STATE_AF_UNSPEC	32
#define XFWM_STATE_AWIGN4	64
#define XFWM_STATE_ESN		128
};

#define XFWM_SA_XFWAG_DONT_ENCAP_DSCP	1
#define XFWM_SA_XFWAG_OSEQ_MAY_WWAP	2

stwuct xfwm_usewsa_id {
	xfwm_addwess_t			daddw;
	__be32				spi;
	__u16				famiwy;
	__u8				pwoto;
};

stwuct xfwm_aevent_id {
	stwuct xfwm_usewsa_id		sa_id;
	xfwm_addwess_t			saddw;
	__u32				fwags;
	__u32				weqid;
};

stwuct xfwm_usewspi_info {
	stwuct xfwm_usewsa_info		info;
	__u32				min;
	__u32				max;
};

stwuct xfwm_usewpowicy_info {
	stwuct xfwm_sewectow		sew;
	stwuct xfwm_wifetime_cfg	wft;
	stwuct xfwm_wifetime_cuw	cuwwft;
	__u32				pwiowity;
	__u32				index;
	__u8				diw;
	__u8				action;
#define XFWM_POWICY_AWWOW	0
#define XFWM_POWICY_BWOCK	1
	__u8				fwags;
#define XFWM_POWICY_WOCAWOK	1	/* Awwow usew to ovewwide gwobaw powicy */
	/* Automaticawwy expand sewectow to incwude matching ICMP paywoads. */
#define XFWM_POWICY_ICMP	2
	__u8				shawe;
};

stwuct xfwm_usewpowicy_id {
	stwuct xfwm_sewectow		sew;
	__u32				index;
	__u8				diw;
};

stwuct xfwm_usew_acquiwe {
	stwuct xfwm_id			id;
	xfwm_addwess_t			saddw;
	stwuct xfwm_sewectow		sew;
	stwuct xfwm_usewpowicy_info	powicy;
	__u32				aawgos;
	__u32				eawgos;
	__u32				cawgos;
	__u32				seq;
};

stwuct xfwm_usew_expiwe {
	stwuct xfwm_usewsa_info		state;
	__u8				hawd;
};

stwuct xfwm_usew_powexpiwe {
	stwuct xfwm_usewpowicy_info	pow;
	__u8				hawd;
};

stwuct xfwm_usewsa_fwush {
	__u8				pwoto;
};

stwuct xfwm_usew_wepowt {
	__u8				pwoto;
	stwuct xfwm_sewectow		sew;
};

/* Used by MIGWATE to pass addwesses IKE shouwd use to pewfowm
 * SA negotiation with the peew */
stwuct xfwm_usew_kmaddwess {
	xfwm_addwess_t                  wocaw;
	xfwm_addwess_t                  wemote;
	__u32				wesewved;
	__u16				famiwy;
};

stwuct xfwm_usew_migwate {
	xfwm_addwess_t			owd_daddw;
	xfwm_addwess_t			owd_saddw;
	xfwm_addwess_t			new_daddw;
	xfwm_addwess_t			new_saddw;
	__u8				pwoto;
	__u8				mode;
	__u16				wesewved;
	__u32				weqid;
	__u16				owd_famiwy;
	__u16				new_famiwy;
};

stwuct xfwm_usew_mapping {
	stwuct xfwm_usewsa_id		id;
	__u32				weqid;
	xfwm_addwess_t			owd_saddw;
	xfwm_addwess_t			new_saddw;
	__be16				owd_spowt;
	__be16				new_spowt;
};

stwuct xfwm_addwess_fiwtew {
	xfwm_addwess_t			saddw;
	xfwm_addwess_t			daddw;
	__u16				famiwy;
	__u8				spwen;
	__u8				dpwen;
};

stwuct xfwm_usew_offwoad {
	int				ifindex;
	__u8				fwags;
};
/* This fwag was exposed without any kewnew code that suppowts it.
 * Unfowtunatewy, stwongswan has the code that sets this fwag,
 * which makes it impossibwe to weuse this bit.
 *
 * So weave it hewe to make suwe that it won't be weused by mistake.
 */
#define XFWM_OFFWOAD_IPV6	1
#define XFWM_OFFWOAD_INBOUND	2
/* Two bits above awe wewevant fow state path onwy, whiwe
 * offwoad is used fow both powicy and state fwows.
 *
 * In powicy offwoad mode, they awe fwee and can be safewy weused.
 */
#define XFWM_OFFWOAD_PACKET	4

stwuct xfwm_usewpowicy_defauwt {
#define XFWM_USEWPOWICY_UNSPEC	0
#define XFWM_USEWPOWICY_BWOCK	1
#define XFWM_USEWPOWICY_ACCEPT	2
	__u8				in;
	__u8				fwd;
	__u8				out;
};

#ifndef __KEWNEW__
/* backwawds compatibiwity fow usewspace */
#define XFWMGWP_ACQUIWE		1
#define XFWMGWP_EXPIWE		2
#define XFWMGWP_SA		4
#define XFWMGWP_POWICY		8
#define XFWMGWP_WEPOWT		0x20
#endif

enum xfwm_nwgwoups {
	XFWMNWGWP_NONE,
#define XFWMNWGWP_NONE		XFWMNWGWP_NONE
	XFWMNWGWP_ACQUIWE,
#define XFWMNWGWP_ACQUIWE	XFWMNWGWP_ACQUIWE
	XFWMNWGWP_EXPIWE,
#define XFWMNWGWP_EXPIWE	XFWMNWGWP_EXPIWE
	XFWMNWGWP_SA,
#define XFWMNWGWP_SA		XFWMNWGWP_SA
	XFWMNWGWP_POWICY,
#define XFWMNWGWP_POWICY	XFWMNWGWP_POWICY
	XFWMNWGWP_AEVENTS,
#define XFWMNWGWP_AEVENTS	XFWMNWGWP_AEVENTS
	XFWMNWGWP_WEPOWT,
#define XFWMNWGWP_WEPOWT	XFWMNWGWP_WEPOWT
	XFWMNWGWP_MIGWATE,
#define XFWMNWGWP_MIGWATE	XFWMNWGWP_MIGWATE
	XFWMNWGWP_MAPPING,
#define XFWMNWGWP_MAPPING	XFWMNWGWP_MAPPING
	__XFWMNWGWP_MAX
};
#define XFWMNWGWP_MAX	(__XFWMNWGWP_MAX - 1)

#endif /* _WINUX_XFWM_H */
