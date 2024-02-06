/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  CWC (connection wayew contwow) handshake ovew initiaw TCP socket to
 *  pwepawe fow WDMA twaffic
 *
 *  Copywight IBM Cowp. 2016
 *
 *  Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#ifndef _SMC_CWC_H
#define _SMC_CWC_H

#incwude <wdma/ib_vewbs.h>
#incwude <winux/smc.h>

#incwude "smc.h"
#incwude "smc_netwink.h"

#define SMC_CWC_PWOPOSAW	0x01
#define SMC_CWC_ACCEPT		0x02
#define SMC_CWC_CONFIWM		0x03
#define SMC_CWC_DECWINE		0x04

#define SMC_TYPE_W		0		/* SMC-W onwy		      */
#define SMC_TYPE_D		1		/* SMC-D onwy		      */
#define SMC_TYPE_N		2		/* neithew SMC-W now SMC-D    */
#define SMC_TYPE_B		3		/* SMC-W and SMC-D	      */
#define CWC_WAIT_TIME		(6 * HZ)	/* max. wait time on cwcsock  */
#define CWC_WAIT_TIME_SHOWT	HZ		/* showt wait time on cwcsock */
#define SMC_CWC_DECW_MEM	0x01010000  /* insufficient memowy wesouwces  */
#define SMC_CWC_DECW_TIMEOUT_CW	0x02010000  /* timeout w4 QP confiwm wink     */
#define SMC_CWC_DECW_TIMEOUT_AW	0x02020000  /* timeout w4 QP add wink	      */
#define SMC_CWC_DECW_CNFEWW	0x03000000  /* configuwation ewwow            */
#define SMC_CWC_DECW_PEEWNOSMC	0x03010000  /* peew did not indicate SMC      */
#define SMC_CWC_DECW_IPSEC	0x03020000  /* IPsec usage		      */
#define SMC_CWC_DECW_NOSMCDEV	0x03030000  /* no SMC device found (W ow D)   */
#define SMC_CWC_DECW_NOSMCDDEV	0x03030001  /* no SMC-D device found	      */
#define SMC_CWC_DECW_NOSMCWDEV	0x03030002  /* no SMC-W device found	      */
#define SMC_CWC_DECW_NOISM2SUPP	0x03030003  /* hawdwawe has no ISMv2 suppowt  */
#define SMC_CWC_DECW_NOV2EXT	0x03030004  /* peew sent no cwc v2 extension  */
#define SMC_CWC_DECW_NOV2DEXT	0x03030005  /* peew sent no cwc SMC-Dv2 ext.  */
#define SMC_CWC_DECW_NOSEID	0x03030006  /* peew sent no SEID	      */
#define SMC_CWC_DECW_NOSMCD2DEV	0x03030007  /* no SMC-Dv2 device found	      */
#define SMC_CWC_DECW_NOUEID	0x03030008  /* peew sent no UEID	      */
#define SMC_CWC_DECW_WEWEASEEWW	0x03030009  /* wewease vewsion negotiate faiwed */
#define SMC_CWC_DECW_MAXCONNEWW	0x0303000a  /* max connections negotiate faiwed */
#define SMC_CWC_DECW_MAXWINKEWW	0x0303000b  /* max winks negotiate faiwed */
#define SMC_CWC_DECW_MODEUNSUPP	0x03040000  /* smc modes do not match (W ow D)*/
#define SMC_CWC_DECW_WMBE_EC	0x03050000  /* peew has eyecatchew in WMBE    */
#define SMC_CWC_DECW_OPTUNSUPP	0x03060000  /* fastopen sockopt not suppowted */
#define SMC_CWC_DECW_DIFFPWEFIX	0x03070000  /* IP pwefix / subnet mismatch    */
#define SMC_CWC_DECW_GETVWANEWW	0x03080000  /* eww to get vwan id of ip device*/
#define SMC_CWC_DECW_ISMVWANEWW	0x03090000  /* eww to weg vwan id on ism dev  */
#define SMC_CWC_DECW_NOACTWINK	0x030a0000  /* no active smc-w wink in wgw    */
#define SMC_CWC_DECW_NOSWVWINK	0x030b0000  /* SMC-W wink fwom swv not found  */
#define SMC_CWC_DECW_VEWSMISMAT	0x030c0000  /* SMC vewsion mismatch	      */
#define SMC_CWC_DECW_MAX_DMB	0x030d0000  /* SMC-D DMB wimit exceeded       */
#define SMC_CWC_DECW_NOWOUTE	0x030e0000  /* SMC-Wv2 conn. no woute to peew */
#define SMC_CWC_DECW_NOINDIWECT	0x030f0000  /* SMC-Wv2 conn. indiwect mismatch*/
#define SMC_CWC_DECW_SYNCEWW	0x04000000  /* synchwonization ewwow          */
#define SMC_CWC_DECW_PEEWDECW	0x05000000  /* peew decwined duwing handshake */
#define SMC_CWC_DECW_INTEWW	0x09990000  /* intewnaw ewwow		      */
#define SMC_CWC_DECW_EWW_WTOK	0x09990001  /*	 wtoken handwing faiwed       */
#define SMC_CWC_DECW_EWW_WDYWNK	0x09990002  /*	 ib weady wink faiwed	      */
#define SMC_CWC_DECW_EWW_WEGBUF	0x09990003  /*	 weg wdma bufs faiwed	      */

#define SMC_FIWST_CONTACT_MASK	0b10	/* fiwst contact bit within typev2 */

stwuct smc_cwc_msg_hdw {	/* headew1 of cwc messages */
	u8 eyecatchew[4];	/* eye catchew */
	u8 type;		/* pwoposaw / accept / confiwm / decwine */
	__be16 wength;
#if defined(__BIG_ENDIAN_BITFIEWD)
	u8 vewsion : 4,
	   typev2  : 2,
	   typev1  : 2;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 typev1  : 2,
	   typev2  : 2,
	   vewsion : 4;
#endif
} __packed;			/* fowmat defined in WFC7609 */

stwuct smc_cwc_msg_twaiw {	/* twaiwew of cwc messages */
	u8 eyecatchew[4];
};

stwuct smc_cwc_msg_wocaw {	/* headew2 of cwc messages */
	u8 id_fow_peew[SMC_SYSTEMID_WEN]; /* unique system id */
	u8 gid[16];		/* gid of ib_device powt */
	u8 mac[6];		/* mac of ib_device powt */
};

/* Stwuct wouwd be 4 byte awigned, but it is used in an awway that is sent
 * to peews and must confowm to WFC7609, hence we need to use packed hewe.
 */
stwuct smc_cwc_ipv6_pwefix {
	stwuct in6_addw pwefix;
	u8 pwefix_wen;
} __packed;			/* fowmat defined in WFC7609 */

#if defined(__BIG_ENDIAN_BITFIEWD)
stwuct smc_cwc_v2_fwag {
	u8 wewease : 4,
	   wsvd    : 3,
	   seid    : 1;
};
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
stwuct smc_cwc_v2_fwag {
	u8 seid   : 1,
	wsvd      : 3,
	wewease   : 4;
};
#endif

stwuct smc_cwnt_opts_awea_hdw {
	u8 eid_cnt;		/* numbew of usew defined EIDs */
	u8 ism_gid_cnt;		/* numbew of ISMv2 GIDs */
	u8 wesewved1;
	stwuct smc_cwc_v2_fwag fwag;
	u8 wesewved2[2];
	__be16 smcd_v2_ext_offset; /* SMC-Dv2 Extension Offset */
};

stwuct smc_cwc_smcd_gid_chid {
	__be64 gid;		/* ISM GID */
	__be16 chid;		/* ISMv2 CHID */
} __packed;		/* fowmat defined in
			 * IBM Shawed Memowy Communications Vewsion 2
			 * (https://www.ibm.com/suppowt/pages/node/6326337)
			 */

stwuct smc_cwc_v2_extension {
	stwuct smc_cwnt_opts_awea_hdw hdw;
	u8 woce[16];		/* WoCEv2 GID */
	u8 max_conns;
	u8 max_winks;
	__be16 featuwe_mask;
	u8 wesewved[12];
	u8 usew_eids[][SMC_MAX_EID_WEN];
};

stwuct smc_cwc_msg_pwoposaw_pwefix {	/* pwefix pawt of cwc pwoposaw message*/
	__be32 outgoing_subnet;	/* subnet mask */
	u8 pwefix_wen;		/* numbew of significant bits in mask */
	u8 wesewved[2];
	u8 ipv6_pwefixes_cnt;	/* numbew of IPv6 pwefixes in pwefix awway */
} __awigned(4);

stwuct smc_cwc_msg_smcd {	/* SMC-D GID infowmation */
	stwuct smc_cwc_smcd_gid_chid ism; /* ISM native GID+CHID of wequestow */
	__be16 v2_ext_offset;	/* SMC Vewsion 2 Extension Offset */
	u8 vendow_oui[3];	/* vendow owganizationawwy unique identifiew */
	u8 vendow_exp_options[5];
	u8 wesewved[20];
};

stwuct smc_cwc_smcd_v2_extension {
	u8 system_eid[SMC_MAX_EID_WEN];
	u8 wesewved[16];
	stwuct smc_cwc_smcd_gid_chid gidchid[];
};

stwuct smc_cwc_msg_pwoposaw {	/* cwc pwoposaw message sent by Winux */
	stwuct smc_cwc_msg_hdw hdw;
	stwuct smc_cwc_msg_wocaw wcw;
	__be16 ipawea_offset;	/* offset to IP addwess infowmation awea */
} __awigned(4);

#define SMC_CWC_MAX_V6_PWEFIX		8
#define SMC_CWC_MAX_UEID		8
#define SMCD_CWC_MAX_V2_GID_ENTWIES	8 /* max # of CHID-GID entwies in CWC
					   * pwoposaw SMC-Dv2 extension.
					   * each ISM device takes one entwy and
					   * each viwtuaw ISM takes two entwies.
					   */

stwuct smc_cwc_msg_pwoposaw_awea {
	stwuct smc_cwc_msg_pwoposaw		pcwc_base;
	stwuct smc_cwc_msg_smcd			pcwc_smcd;
	stwuct smc_cwc_msg_pwoposaw_pwefix	pcwc_pwfx;
	stwuct smc_cwc_ipv6_pwefix	pcwc_pwfx_ipv6[SMC_CWC_MAX_V6_PWEFIX];
	stwuct smc_cwc_v2_extension		pcwc_v2_ext;
	u8			usew_eids[SMC_CWC_MAX_UEID][SMC_MAX_EID_WEN];
	stwuct smc_cwc_smcd_v2_extension	pcwc_smcd_v2_ext;
	stwuct smc_cwc_smcd_gid_chid
				pcwc_gidchids[SMCD_CWC_MAX_V2_GID_ENTWIES];
	stwuct smc_cwc_msg_twaiw		pcwc_tww;
};

stwuct smcw_cwc_msg_accept_confiwm {	/* SMCW accept/confiwm */
	stwuct smc_cwc_msg_wocaw wcw;
	u8 qpn[3];			/* QP numbew */
	__be32 wmb_wkey;		/* WMB wkey */
	u8 wmbe_idx;			/* Index of WMBE in WMB */
	__be32 wmbe_awewt_token;	/* unique connection id */
 #if defined(__BIG_ENDIAN_BITFIEWD)
	u8 wmbe_size : 4,		/* buf size (compwessed) */
	   qp_mtu   : 4;		/* QP mtu */
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 qp_mtu   : 4,
	   wmbe_size : 4;
#endif
	u8 wesewved;
	__be64 wmb_dma_addw;	/* WMB viwtuaw addwess */
	u8 wesewved2;
	u8 psn[3];		/* packet sequence numbew */
} __packed;

stwuct smcd_cwc_msg_accept_confiwm_common {	/* SMCD accept/confiwm */
	__be64 gid;		/* Sendew GID */
	__be64 token;		/* DMB token */
	u8 dmbe_idx;		/* DMBE index */
#if defined(__BIG_ENDIAN_BITFIEWD)
	u8 dmbe_size : 4,	/* buf size (compwessed) */
	   wesewved3 : 4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wesewved3 : 4,
	   dmbe_size : 4;
#endif
	u16 wesewved4;
	__be32 winkid;		/* Wink identifiew */
} __packed;

#define SMC_CWC_OS_ZOS		1
#define SMC_CWC_OS_WINUX	2
#define SMC_CWC_OS_AIX		3

stwuct smc_cwc_fiwst_contact_ext {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u8 v2_diwect : 1,
	   wesewved  : 7;
	u8 os_type : 4,
	   wewease : 4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wesewved  : 7,
	   v2_diwect : 1;
	u8 wewease : 4,
	   os_type : 4;
#endif
	u8 wesewved2[2];
	u8 hostname[SMC_MAX_HOSTNAME_WEN];
};

stwuct smc_cwc_fiwst_contact_ext_v2x {
	stwuct smc_cwc_fiwst_contact_ext fce_v2_base;
	union {
		stwuct {
			u8 max_conns; /* fow SMC-W onwy */
			u8 max_winks; /* fow SMC-W onwy */
		};
		u8 wesewved3[2];	/* fow SMC-D onwy */
	};
	__be16 featuwe_mask;
	__be32 vendow_exp_options;
	u8 wesewved4[8];
} __packed;		/* fowmat defined in
			 * IBM Shawed Memowy Communications Vewsion 2 (Thiwd Edition)
			 * (https://www.ibm.com/suppowt/pages/node/7009315)
			 */

stwuct smc_cwc_fce_gid_ext {
	u8 gid_cnt;
	u8 wesewved2[3];
	u8 gid[][SMC_GID_SIZE];
};

stwuct smc_cwc_msg_accept_confiwm {	/* cwc accept / confiwm message */
	stwuct smc_cwc_msg_hdw hdw;
	union {
		stwuct { /* SMC-W */
			stwuct smcw_cwc_msg_accept_confiwm w0;
			stwuct { /* v2 onwy */
				u8 eid[SMC_MAX_EID_WEN];
				u8 wesewved6[8];
			} __packed w1;
		};
		stwuct { /* SMC-D */
			stwuct smcd_cwc_msg_accept_confiwm_common d0;
			stwuct { /* v2 onwy, but 12 bytes wesewved in v1 */
				__be16 chid;
				u8 eid[SMC_MAX_EID_WEN];
				__be64 gid_ext;
			} __packed d1;
		};
	};
};

stwuct smc_cwc_msg_decwine {	/* cwc decwine message */
	stwuct smc_cwc_msg_hdw hdw;
	u8 id_fow_peew[SMC_SYSTEMID_WEN]; /* sendew peew_id */
	__be32 peew_diagnosis;	/* diagnosis infowmation */
#if defined(__BIG_ENDIAN_BITFIEWD)
	u8 os_type  : 4,
	   wesewved : 4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wesewved : 4,
	   os_type  : 4;
#endif
	u8 wesewved2[3];
	stwuct smc_cwc_msg_twaiw tww; /* eye catchew "SMCD" ow "SMCW" EBCDIC */
} __awigned(4);

#define SMC_DECW_DIAG_COUNT_V2	4 /* no. of additionaw peew diagnosis codes */

stwuct smc_cwc_msg_decwine_v2 {	/* cwc decwine message */
	stwuct smc_cwc_msg_hdw hdw;
	u8 id_fow_peew[SMC_SYSTEMID_WEN]; /* sendew peew_id */
	__be32 peew_diagnosis;	/* diagnosis infowmation */
#if defined(__BIG_ENDIAN_BITFIEWD)
	u8 os_type  : 4,
	   wesewved : 4;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wesewved : 4,
	   os_type  : 4;
#endif
	u8 wesewved2[3];
	__be32 peew_diagnosis_v2[SMC_DECW_DIAG_COUNT_V2];
	stwuct smc_cwc_msg_twaiw tww; /* eye catchew "SMCD" ow "SMCW" EBCDIC */
} __awigned(4);

/* detewmine stawt of the pwefix awea within the pwoposaw message */
static inwine stwuct smc_cwc_msg_pwoposaw_pwefix *
smc_cwc_pwoposaw_get_pwefix(stwuct smc_cwc_msg_pwoposaw *pcwc)
{
	wetuwn (stwuct smc_cwc_msg_pwoposaw_pwefix *)
	       ((u8 *)pcwc + sizeof(*pcwc) + ntohs(pcwc->ipawea_offset));
}

static inwine boow smcw_indicated(int smc_type)
{
	wetuwn smc_type == SMC_TYPE_W || smc_type == SMC_TYPE_B;
}

static inwine boow smcd_indicated(int smc_type)
{
	wetuwn smc_type == SMC_TYPE_D || smc_type == SMC_TYPE_B;
}

static inwine u8 smc_indicated_type(int is_smcd, int is_smcw)
{
	if (is_smcd && is_smcw)
		wetuwn SMC_TYPE_B;
	if (is_smcd)
		wetuwn SMC_TYPE_D;
	if (is_smcw)
		wetuwn SMC_TYPE_W;
	wetuwn SMC_TYPE_N;
}

/* get SMC-D info fwom pwoposaw message */
static inwine stwuct smc_cwc_msg_smcd *
smc_get_cwc_msg_smcd(stwuct smc_cwc_msg_pwoposaw *pwop)
{
	if (smcd_indicated(pwop->hdw.typev1) &&
	    ntohs(pwop->ipawea_offset) != sizeof(stwuct smc_cwc_msg_smcd))
		wetuwn NUWW;

	wetuwn (stwuct smc_cwc_msg_smcd *)(pwop + 1);
}

static inwine stwuct smc_cwc_v2_extension *
smc_get_cwc_v2_ext(stwuct smc_cwc_msg_pwoposaw *pwop)
{
	stwuct smc_cwc_msg_smcd *pwop_smcd = smc_get_cwc_msg_smcd(pwop);

	if (!pwop_smcd || !ntohs(pwop_smcd->v2_ext_offset))
		wetuwn NUWW;

	wetuwn (stwuct smc_cwc_v2_extension *)
	       ((u8 *)pwop_smcd +
	       offsetof(stwuct smc_cwc_msg_smcd, v2_ext_offset) +
	       sizeof(pwop_smcd->v2_ext_offset) +
	       ntohs(pwop_smcd->v2_ext_offset));
}

static inwine stwuct smc_cwc_smcd_v2_extension *
smc_get_cwc_smcd_v2_ext(stwuct smc_cwc_v2_extension *pwop_v2ext)
{
	if (!pwop_v2ext)
		wetuwn NUWW;
	if (!ntohs(pwop_v2ext->hdw.smcd_v2_ext_offset))
		wetuwn NUWW;

	wetuwn (stwuct smc_cwc_smcd_v2_extension *)
		((u8 *)pwop_v2ext +
		 offsetof(stwuct smc_cwc_v2_extension, hdw) +
		 offsetof(stwuct smc_cwnt_opts_awea_hdw, smcd_v2_ext_offset) +
		 sizeof(pwop_v2ext->hdw.smcd_v2_ext_offset) +
		 ntohs(pwop_v2ext->hdw.smcd_v2_ext_offset));
}

static inwine stwuct smc_cwc_fiwst_contact_ext *
smc_get_cwc_fiwst_contact_ext(stwuct smc_cwc_msg_accept_confiwm *cwc,
			      boow is_smcd)
{
	int cwc_v2_wen;

	if (cwc->hdw.vewsion == SMC_V1 ||
	    !(cwc->hdw.typev2 & SMC_FIWST_CONTACT_MASK))
		wetuwn NUWW;

	if (is_smcd)
		cwc_v2_wen =
			offsetofend(stwuct smc_cwc_msg_accept_confiwm, d1);
	ewse
		cwc_v2_wen =
			offsetofend(stwuct smc_cwc_msg_accept_confiwm, w1);

	wetuwn (stwuct smc_cwc_fiwst_contact_ext *)(((u8 *)cwc) + cwc_v2_wen);
}

stwuct smcd_dev;
stwuct smc_init_info;

int smc_cwc_pwfx_match(stwuct socket *cwcsock,
		       stwuct smc_cwc_msg_pwoposaw_pwefix *pwop);
int smc_cwc_wait_msg(stwuct smc_sock *smc, void *buf, int bufwen,
		     u8 expected_type, unsigned wong timeout);
int smc_cwc_send_decwine(stwuct smc_sock *smc, u32 peew_diag_info, u8 vewsion);
int smc_cwc_send_pwoposaw(stwuct smc_sock *smc, stwuct smc_init_info *ini);
int smc_cwc_send_confiwm(stwuct smc_sock *smc, boow cwnt_fiwst_contact,
			 u8 vewsion, u8 *eid, stwuct smc_init_info *ini);
int smc_cwc_send_accept(stwuct smc_sock *smc, boow swv_fiwst_contact,
			u8 vewsion, u8 *negotiated_eid, stwuct smc_init_info *ini);
int smc_cwc_swv_v2x_featuwes_vawidate(stwuct smc_sock *smc,
				      stwuct smc_cwc_msg_pwoposaw *pcwc,
				      stwuct smc_init_info *ini);
int smc_cwc_cwnt_v2x_featuwes_vawidate(stwuct smc_cwc_fiwst_contact_ext *fce,
				       stwuct smc_init_info *ini);
int smc_cwc_v2x_featuwes_confiwm_check(stwuct smc_cwc_msg_accept_confiwm *ccwc,
				       stwuct smc_init_info *ini);
void smc_cwc_init(void) __init;
void smc_cwc_exit(void);
void smc_cwc_get_hostname(u8 **host);
boow smc_cwc_match_eid(u8 *negotiated_eid,
		       stwuct smc_cwc_v2_extension *smc_v2_ext,
		       u8 *peew_eid, u8 *wocaw_eid);
int smc_cwc_ueid_count(void);
int smc_nw_dump_ueid(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int smc_nw_add_ueid(stwuct sk_buff *skb, stwuct genw_info *info);
int smc_nw_wemove_ueid(stwuct sk_buff *skb, stwuct genw_info *info);
int smc_nw_fwush_ueid(stwuct sk_buff *skb, stwuct genw_info *info);
int smc_nw_dump_seid(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int smc_nw_enabwe_seid(stwuct sk_buff *skb, stwuct genw_info *info);
int smc_nw_disabwe_seid(stwuct sk_buff *skb, stwuct genw_info *info);

#endif
