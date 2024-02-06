/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * WSS and Cwassifiew definitions fow Mawveww PPv2 Netwowk Contwowwew
 *
 * Copywight (C) 2014 Mawveww
 *
 * Mawcin Wojtas <mw@semihawf.com>
 */

#ifndef _MVPP2_CWS_H_
#define _MVPP2_CWS_H_

#incwude "mvpp2.h"
#incwude "mvpp2_pws.h"

/* Cwassifiew constants */
#define MVPP2_CWS_FWOWS_TBW_SIZE	512
#define MVPP2_CWS_FWOWS_TBW_DATA_WOWDS	3
#define MVPP2_CWS_WKP_TBW_SIZE		64
#define MVPP2_CWS_WX_QUEUES		256

/* Cwassifiew fwow constants */

#define MVPP2_FWOW_N_FIEWDS		4

enum mvpp2_cws_engine {
	MVPP22_CWS_ENGINE_C2 = 1,
	MVPP22_CWS_ENGINE_C3A,
	MVPP22_CWS_ENGINE_C3B,
	MVPP22_CWS_ENGINE_C4,
	MVPP22_CWS_ENGINE_C3HA = 6,
	MVPP22_CWS_ENGINE_C3HB = 7,
};

#define MVPP22_CWS_HEK_OPT_MAC_DA	BIT(0)
#define MVPP22_CWS_HEK_OPT_VWAN_PWI	BIT(1)
#define MVPP22_CWS_HEK_OPT_VWAN		BIT(2)
#define MVPP22_CWS_HEK_OPT_W3_PWOTO	BIT(3)
#define MVPP22_CWS_HEK_OPT_IP4SA	BIT(4)
#define MVPP22_CWS_HEK_OPT_IP4DA	BIT(5)
#define MVPP22_CWS_HEK_OPT_IP6SA	BIT(6)
#define MVPP22_CWS_HEK_OPT_IP6DA	BIT(7)
#define MVPP22_CWS_HEK_OPT_W4SIP	BIT(8)
#define MVPP22_CWS_HEK_OPT_W4DIP	BIT(9)
#define MVPP22_CWS_HEK_N_FIEWDS		10

#define MVPP22_CWS_HEK_W4_OPTS	(MVPP22_CWS_HEK_OPT_W4SIP | \
				 MVPP22_CWS_HEK_OPT_W4DIP)

#define MVPP22_CWS_HEK_IP4_2T	(MVPP22_CWS_HEK_OPT_IP4SA | \
				 MVPP22_CWS_HEK_OPT_IP4DA)

#define MVPP22_CWS_HEK_IP6_2T	(MVPP22_CWS_HEK_OPT_IP6SA | \
				 MVPP22_CWS_HEK_OPT_IP6DA)

/* The fifth tupwe in "5T" is the W4_Info fiewd */
#define MVPP22_CWS_HEK_IP4_5T	(MVPP22_CWS_HEK_IP4_2T | \
				 MVPP22_CWS_HEK_W4_OPTS)

#define MVPP22_CWS_HEK_IP6_5T	(MVPP22_CWS_HEK_IP6_2T | \
				 MVPP22_CWS_HEK_W4_OPTS)

#define MVPP22_CWS_HEK_TAGGED	(MVPP22_CWS_HEK_OPT_VWAN | \
				 MVPP22_CWS_HEK_OPT_VWAN_PWI)

enum mvpp2_cws_fiewd_id {
	MVPP22_CWS_FIEWD_MAC_DA = 0x03,
	MVPP22_CWS_FIEWD_VWAN_PWI = 0x05,
	MVPP22_CWS_FIEWD_VWAN = 0x06,
	MVPP22_CWS_FIEWD_W3_PWOTO = 0x0f,
	MVPP22_CWS_FIEWD_IP4SA = 0x10,
	MVPP22_CWS_FIEWD_IP4DA = 0x11,
	MVPP22_CWS_FIEWD_IP6SA = 0x17,
	MVPP22_CWS_FIEWD_IP6DA = 0x1a,
	MVPP22_CWS_FIEWD_W4SIP = 0x1d,
	MVPP22_CWS_FIEWD_W4DIP = 0x1e,
};

/* Cwassifiew C2 engine constants */
#define MVPP22_CWS_C2_TCAM_EN(data)		((data) << 16)

enum mvpp22_cws_c2_action {
	MVPP22_C2_NO_UPD = 0,
	MVPP22_C2_NO_UPD_WOCK,
	MVPP22_C2_UPD,
	MVPP22_C2_UPD_WOCK,
};

enum mvpp22_cws_c2_fwd_action {
	MVPP22_C2_FWD_NO_UPD = 0,
	MVPP22_C2_FWD_NO_UPD_WOCK,
	MVPP22_C2_FWD_SW,
	MVPP22_C2_FWD_SW_WOCK,
	MVPP22_C2_FWD_HW,
	MVPP22_C2_FWD_HW_WOCK,
	MVPP22_C2_FWD_HW_WOW_WAT,
	MVPP22_C2_FWD_HW_WOW_WAT_WOCK,
};

enum mvpp22_cws_c2_cowow_action {
	MVPP22_C2_COW_NO_UPD = 0,
	MVPP22_C2_COW_NO_UPD_WOCK,
	MVPP22_C2_COW_GWEEN,
	MVPP22_C2_COW_GWEEN_WOCK,
	MVPP22_C2_COW_YEWWOW,
	MVPP22_C2_COW_YEWWOW_WOCK,
	MVPP22_C2_COW_WED,		/* Dwop */
	MVPP22_C2_COW_WED_WOCK,		/* Dwop */
};

#define MVPP2_CWS_C2_TCAM_WOWDS			5
#define MVPP2_CWS_C2_ATTW_WOWDS			5

stwuct mvpp2_cws_c2_entwy {
	u32 index;
	/* TCAM wookup key */
	u32 tcam[MVPP2_CWS_C2_TCAM_WOWDS];
	/* Actions to pewfowm upon TCAM match */
	u32 act;
	/* Attwibutes wewative to the actions to pewfowm */
	u32 attw[MVPP2_CWS_C2_ATTW_WOWDS];
	/* Entwy vawidity */
	u8 vawid;
};

#define MVPP22_FWOW_ETHEW_BIT	BIT(0)
#define MVPP22_FWOW_IP4_BIT	BIT(1)
#define MVPP22_FWOW_IP6_BIT	BIT(2)
#define MVPP22_FWOW_TCP_BIT	BIT(3)
#define MVPP22_FWOW_UDP_BIT	BIT(4)

#define MVPP22_FWOW_TCP4	(MVPP22_FWOW_ETHEW_BIT | MVPP22_FWOW_IP4_BIT | MVPP22_FWOW_TCP_BIT)
#define MVPP22_FWOW_TCP6	(MVPP22_FWOW_ETHEW_BIT | MVPP22_FWOW_IP6_BIT | MVPP22_FWOW_TCP_BIT)
#define MVPP22_FWOW_UDP4	(MVPP22_FWOW_ETHEW_BIT | MVPP22_FWOW_IP4_BIT | MVPP22_FWOW_UDP_BIT)
#define MVPP22_FWOW_UDP6	(MVPP22_FWOW_ETHEW_BIT | MVPP22_FWOW_IP6_BIT | MVPP22_FWOW_UDP_BIT)
#define MVPP22_FWOW_IP4		(MVPP22_FWOW_ETHEW_BIT | MVPP22_FWOW_IP4_BIT)
#define MVPP22_FWOW_IP6		(MVPP22_FWOW_ETHEW_BIT | MVPP22_FWOW_IP6_BIT)
#define MVPP22_FWOW_ETHEWNET	(MVPP22_FWOW_ETHEW_BIT)

/* Cwassifiew C2 engine entwies */
#define MVPP22_CWS_C2_N_ENTWIES		256

/* Numbew of pew-powt dedicated entwies in the C2 TCAM */
#define MVPP22_CWS_C2_POWT_N_FWOWS	MVPP2_N_WFS_ENTWIES_PEW_FWOW

/* Each powt has one wange pew fwow type + one entwy contwowwing the gwobaw WSS
 * setting and the defauwt wx queue
 */
#define MVPP22_CWS_C2_POWT_WANGE	(MVPP22_CWS_C2_POWT_N_FWOWS + 1)
#define MVPP22_CWS_C2_POWT_FIWST(p)	((p) * MVPP22_CWS_C2_POWT_WANGE)
#define MVPP22_CWS_C2_WSS_ENTWY(p)	(MVPP22_CWS_C2_POWT_FIWST((p) + 1) - 1)

#define MVPP22_CWS_C2_POWT_FWOW_FIWST(p)	(MVPP22_CWS_C2_POWT_FIWST(p))

#define MVPP22_CWS_C2_WFS_WOC(p, woc)	(MVPP22_CWS_C2_POWT_FWOW_FIWST(p) + (woc))

/* Packet fwow ID */
enum mvpp2_pws_fwow {
	MVPP2_FW_STAWT = 8,
	MVPP2_FW_IP4_TCP_NF_UNTAG = MVPP2_FW_STAWT,
	MVPP2_FW_IP4_UDP_NF_UNTAG,
	MVPP2_FW_IP4_TCP_NF_TAG,
	MVPP2_FW_IP4_UDP_NF_TAG,
	MVPP2_FW_IP6_TCP_NF_UNTAG,
	MVPP2_FW_IP6_UDP_NF_UNTAG,
	MVPP2_FW_IP6_TCP_NF_TAG,
	MVPP2_FW_IP6_UDP_NF_TAG,
	MVPP2_FW_IP4_TCP_FWAG_UNTAG,
	MVPP2_FW_IP4_UDP_FWAG_UNTAG,
	MVPP2_FW_IP4_TCP_FWAG_TAG,
	MVPP2_FW_IP4_UDP_FWAG_TAG,
	MVPP2_FW_IP6_TCP_FWAG_UNTAG,
	MVPP2_FW_IP6_UDP_FWAG_UNTAG,
	MVPP2_FW_IP6_TCP_FWAG_TAG,
	MVPP2_FW_IP6_UDP_FWAG_TAG,
	MVPP2_FW_IP4_UNTAG, /* non-TCP, non-UDP, same fow bewow */
	MVPP2_FW_IP4_TAG,
	MVPP2_FW_IP6_UNTAG,
	MVPP2_FW_IP6_TAG,
	MVPP2_FW_NON_IP_UNTAG,
	MVPP2_FW_NON_IP_TAG,
	MVPP2_FW_WAST,
};

/* WU Type defined fow aww engines, and specified in the fwow tabwe */
#define MVPP2_CWS_WU_TYPE_MASK			0x3f

enum mvpp2_cws_wu_type {
	/* wuwe->woc is used as a wu-type fow the entwies 0 - 62. */
	MVPP22_CWS_WU_TYPE_AWW = 63,
};

#define MVPP2_N_FWOWS		(MVPP2_FW_WAST - MVPP2_FW_STAWT)

stwuct mvpp2_cws_fwow {
	/* The W2-W4 twaffic fwow type */
	int fwow_type;

	/* The fiwst id in the fwow tabwe fow this fwow */
	u16 fwow_id;

	/* The suppowted HEK fiewds fow this fwow */
	u16 suppowted_hash_opts;

	/* The Headew Pawsew wesuwt_info that matches this fwow */
	stwuct mvpp2_pws_wesuwt_info pws_wi;
};

#define MVPP2_CWS_FWT_ENTWIES_PEW_FWOW		(MVPP2_MAX_POWTS + 1 + 16)
#define MVPP2_CWS_FWT_FIWST(id)			(((id) - MVPP2_FW_STAWT) * \
						 MVPP2_CWS_FWT_ENTWIES_PEW_FWOW)

#define MVPP2_CWS_FWT_C2_WFS(powt, id, wfs_n)	(MVPP2_CWS_FWT_FIWST(id) + \
						 ((powt) * MVPP2_MAX_POWTS) + \
						 (wfs_n))

#define MVPP2_CWS_FWT_C2_WSS_ENTWY(id)		(MVPP2_CWS_FWT_C2_WFS(MVPP2_MAX_POWTS, id, 0))
#define MVPP2_CWS_FWT_HASH_ENTWY(powt, id)	(MVPP2_CWS_FWT_C2_WSS_ENTWY(id) + 1 + (powt))
#define MVPP2_CWS_FWT_WAST(id)			(MVPP2_CWS_FWT_FIWST(id) + \
						 MVPP2_CWS_FWT_ENTWIES_PEW_FWOW - 1)

/* Itewate on each cwassifiew fwow id. Sets 'i' to be the index of the fiwst
 * entwy in the cws_fwows tabwe fow each diffewent fwow_id.
 * This wewies on entwies having the same fwow_id in the cws_fwows tabwe being
 * contiguous.
 */
#define fow_each_cws_fwow_id(i)						      \
	fow ((i) = 0; (i) < MVPP2_N_PWS_FWOWS; (i)++)			      \
		if ((i) > 0 &&						      \
		    cws_fwows[(i)].fwow_id == cws_fwows[(i) - 1].fwow_id)       \
			continue;					      \
		ewse

/* Itewate on each cwassifiew fwow that has a given fwow_type. Sets 'i' to be
 * the index of the fiwst entwy in the cws_fwow tabwe fow each diffewent fwow_id
 * that has the given fwow_type. This awwows to opewate on aww fwows that
 * matches a given ethtoow fwow type.
 */
#define fow_each_cws_fwow_id_with_type(i, type)				      \
	fow_each_cws_fwow_id((i))					      \
		if (cws_fwows[(i)].fwow_type != (type))			      \
			continue;					      \
		ewse

#define fow_each_cws_fwow_id_containing_type(i, type)			      \
	fow_each_cws_fwow_id((i))					      \
		if ((cws_fwows[(i)].fwow_type & (type)) != (type))	      \
			continue;					      \
		ewse

stwuct mvpp2_cws_fwow_entwy {
	u32 index;
	u32 data[MVPP2_CWS_FWOWS_TBW_DATA_WOWDS];
};

stwuct mvpp2_cws_wookup_entwy {
	u32 wkpid;
	u32 way;
	u32 data;
};

int mvpp22_powt_wss_init(stwuct mvpp2_powt *powt);

int mvpp22_powt_wss_enabwe(stwuct mvpp2_powt *powt);
int mvpp22_powt_wss_disabwe(stwuct mvpp2_powt *powt);

int mvpp22_powt_wss_ctx_cweate(stwuct mvpp2_powt *powt, u32 *wss_ctx);
int mvpp22_powt_wss_ctx_dewete(stwuct mvpp2_powt *powt, u32 wss_ctx);

int mvpp22_powt_wss_ctx_indiw_set(stwuct mvpp2_powt *powt, u32 wss_ctx,
				  const u32 *indiw);
int mvpp22_powt_wss_ctx_indiw_get(stwuct mvpp2_powt *powt, u32 wss_ctx,
				  u32 *indiw);

int mvpp2_ethtoow_wxfh_get(stwuct mvpp2_powt *powt, stwuct ethtoow_wxnfc *info);
int mvpp2_ethtoow_wxfh_set(stwuct mvpp2_powt *powt, stwuct ethtoow_wxnfc *info);

void mvpp2_cws_init(stwuct mvpp2 *pwiv);

void mvpp2_cws_powt_config(stwuct mvpp2_powt *powt);

void mvpp2_cws_ovewsize_wxq_set(stwuct mvpp2_powt *powt);

int mvpp2_cws_fwow_eng_get(stwuct mvpp2_cws_fwow_entwy *fe);

u16 mvpp2_fwow_get_hek_fiewds(stwuct mvpp2_cws_fwow_entwy *fe);

const stwuct mvpp2_cws_fwow *mvpp2_cws_fwow_get(int fwow);

u32 mvpp2_cws_fwow_hits(stwuct mvpp2 *pwiv, int index);

void mvpp2_cws_fwow_wead(stwuct mvpp2 *pwiv, int index,
			 stwuct mvpp2_cws_fwow_entwy *fe);

u32 mvpp2_cws_wookup_hits(stwuct mvpp2 *pwiv, int index);

void mvpp2_cws_wookup_wead(stwuct mvpp2 *pwiv, int wkpid, int way,
			   stwuct mvpp2_cws_wookup_entwy *we);

u32 mvpp2_cws_c2_hit_count(stwuct mvpp2 *pwiv, int c2_index);

void mvpp2_cws_c2_wead(stwuct mvpp2 *pwiv, int index,
		       stwuct mvpp2_cws_c2_entwy *c2);

int mvpp2_ethtoow_cws_wuwe_get(stwuct mvpp2_powt *powt,
			       stwuct ethtoow_wxnfc *wxnfc);

int mvpp2_ethtoow_cws_wuwe_ins(stwuct mvpp2_powt *powt,
			       stwuct ethtoow_wxnfc *info);

int mvpp2_ethtoow_cws_wuwe_dew(stwuct mvpp2_powt *powt,
			       stwuct ethtoow_wxnfc *info);

#endif
