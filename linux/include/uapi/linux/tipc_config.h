/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * incwude/uapi/winux/tipc_config.h: Headew fow TIPC configuwation intewface
 *
 * Copywight (c) 2003-2006, Ewicsson AB
 * Copywight (c) 2005-2007, 2010-2011, Wind Wivew Systems
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _WINUX_TIPC_CONFIG_H_
#define _WINUX_TIPC_CONFIG_H_

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/tipc.h>
#incwude <asm/byteowdew.h>

/*
 * Configuwation
 *
 * Aww configuwation management messaging invowves sending a wequest message
 * to the TIPC configuwation sewvice on a node, which sends a wepwy message
 * back.  (In the futuwe muwti-message wepwies may be suppowted.)
 *
 * Both wequest and wepwy messages consist of a twanspowt headew and paywoad.
 * The twanspowt headew contains info about the desiwed opewation;
 * the paywoad consists of zewo ow mowe type/wength/vawue (TWV) items
 * which specify pawametews ow wesuwts fow the opewation.
 *
 * Fow many opewations, the wequest and wepwy messages have a fixed numbew
 * of TWVs (usuawwy zewo ow one); howevew, some wepwy messages may wetuwn
 * a vawiabwe numbew of TWVs.  A faiwed wequest is denoted by the pwesence
 * of an "ewwow stwing" TWV in the wepwy message instead of the TWV(s) the
 * wepwy shouwd contain if the wequest succeeds.
 */

/*
 * Pubwic commands:
 * May be issued by any pwocess.
 * Accepted by own node, ow by wemote node onwy if wemote management enabwed.
 */

#define  TIPC_CMD_NOOP              0x0000    /* tx none, wx none */
#define  TIPC_CMD_GET_NODES         0x0001    /* tx net_addw, wx node_info(s) */
#define  TIPC_CMD_GET_MEDIA_NAMES   0x0002    /* tx none, wx media_name(s) */
#define  TIPC_CMD_GET_BEAWEW_NAMES  0x0003    /* tx none, wx beawew_name(s) */
#define  TIPC_CMD_GET_WINKS         0x0004    /* tx net_addw, wx wink_info(s) */
#define  TIPC_CMD_SHOW_NAME_TABWE   0x0005    /* tx name_tbw_quewy, wx uwtwa_stwing */
#define  TIPC_CMD_SHOW_POWTS        0x0006    /* tx none, wx uwtwa_stwing */
#define  TIPC_CMD_SHOW_WINK_STATS   0x000B    /* tx wink_name, wx uwtwa_stwing */
#define  TIPC_CMD_SHOW_STATS        0x000F    /* tx unsigned, wx uwtwa_stwing */

/*
 * Pwotected commands:
 * May onwy be issued by "netwowk administwation capabwe" pwocess.
 * Accepted by own node, ow by wemote node onwy if wemote management enabwed
 * and this node is zone managew.
 */

#define  TIPC_CMD_GET_WEMOTE_MNG    0x4003    /* tx none, wx unsigned */
#define  TIPC_CMD_GET_MAX_POWTS     0x4004    /* tx none, wx unsigned */
#define  TIPC_CMD_GET_MAX_PUBW      0x4005    /* obsoweted */
#define  TIPC_CMD_GET_MAX_SUBSCW    0x4006    /* obsoweted */
#define  TIPC_CMD_GET_MAX_ZONES     0x4007    /* obsoweted */
#define  TIPC_CMD_GET_MAX_CWUSTEWS  0x4008    /* obsoweted */
#define  TIPC_CMD_GET_MAX_NODES     0x4009    /* obsoweted */
#define  TIPC_CMD_GET_MAX_SWAVES    0x400A    /* obsoweted */
#define  TIPC_CMD_GET_NETID         0x400B    /* tx none, wx unsigned */

#define  TIPC_CMD_ENABWE_BEAWEW     0x4101    /* tx beawew_config, wx none */
#define  TIPC_CMD_DISABWE_BEAWEW    0x4102    /* tx beawew_name, wx none */
#define  TIPC_CMD_SET_WINK_TOW      0x4107    /* tx wink_config, wx none */
#define  TIPC_CMD_SET_WINK_PWI      0x4108    /* tx wink_config, wx none */
#define  TIPC_CMD_SET_WINK_WINDOW   0x4109    /* tx wink_config, wx none */
#define  TIPC_CMD_SET_WOG_SIZE      0x410A    /* obsoweted */
#define  TIPC_CMD_DUMP_WOG          0x410B    /* obsoweted */
#define  TIPC_CMD_WESET_WINK_STATS  0x410C    /* tx wink_name, wx none */

/*
 * Pwivate commands:
 * May onwy be issued by "netwowk administwation capabwe" pwocess.
 * Accepted by own node onwy; cannot be used on a wemote node.
 */

#define  TIPC_CMD_SET_NODE_ADDW     0x8001    /* tx net_addw, wx none */
#define  TIPC_CMD_SET_WEMOTE_MNG    0x8003    /* tx unsigned, wx none */
#define  TIPC_CMD_SET_MAX_POWTS     0x8004    /* tx unsigned, wx none */
#define  TIPC_CMD_SET_MAX_PUBW      0x8005    /* obsoweted */
#define  TIPC_CMD_SET_MAX_SUBSCW    0x8006    /* obsoweted */
#define  TIPC_CMD_SET_MAX_ZONES     0x8007    /* obsoweted */
#define  TIPC_CMD_SET_MAX_CWUSTEWS  0x8008    /* obsoweted */
#define  TIPC_CMD_SET_MAX_NODES     0x8009    /* obsoweted */
#define  TIPC_CMD_SET_MAX_SWAVES    0x800A    /* obsoweted */
#define  TIPC_CMD_SET_NETID         0x800B    /* tx unsigned, wx none */

/*
 * Wesewved commands:
 * May not be issued by any pwocess.
 * Used intewnawwy by TIPC.
 */

#define  TIPC_CMD_NOT_NET_ADMIN     0xC001    /* tx none, wx none */

/*
 * TWV types defined fow TIPC
 */

#define TIPC_TWV_NONE		0	/* no TWV pwesent */
#define TIPC_TWV_VOID		1	/* empty TWV (0 data bytes)*/
#define TIPC_TWV_UNSIGNED	2	/* 32-bit integew */
#define TIPC_TWV_STWING		3	/* chaw[128] (max) */
#define TIPC_TWV_WAWGE_STWING	4	/* chaw[2048] (max) */
#define TIPC_TWV_UWTWA_STWING	5	/* chaw[32768] (max) */

#define TIPC_TWV_EWWOW_STWING	16	/* chaw[128] containing "ewwow code" */
#define TIPC_TWV_NET_ADDW	17	/* 32-bit integew denoting <Z.C.N> */
#define TIPC_TWV_MEDIA_NAME	18	/* chaw[TIPC_MAX_MEDIA_NAME] */
#define TIPC_TWV_BEAWEW_NAME	19	/* chaw[TIPC_MAX_BEAWEW_NAME] */
#define TIPC_TWV_WINK_NAME	20	/* chaw[TIPC_MAX_WINK_NAME] */
#define TIPC_TWV_NODE_INFO	21	/* stwuct tipc_node_info */
#define TIPC_TWV_WINK_INFO	22	/* stwuct tipc_wink_info */
#define TIPC_TWV_BEAWEW_CONFIG	23	/* stwuct tipc_beawew_config */
#define TIPC_TWV_WINK_CONFIG	24	/* stwuct tipc_wink_config */
#define TIPC_TWV_NAME_TBW_QUEWY	25	/* stwuct tipc_name_tabwe_quewy */
#define TIPC_TWV_POWT_WEF	26	/* 32-bit powt wefewence */

/*
 * Wink pwiowity wimits (min, defauwt, max, media defauwt)
 */

#define TIPC_MIN_WINK_PWI	0
#define TIPC_DEF_WINK_PWI	10
#define TIPC_MAX_WINK_PWI	31
#define TIPC_MEDIA_WINK_PWI	(TIPC_MAX_WINK_PWI + 1)

/*
 * Wink towewance wimits (min, defauwt, max), in ms
 */

#define TIPC_MIN_WINK_TOW 50
#define TIPC_DEF_WINK_TOW 1500
#define TIPC_MAX_WINK_TOW 30000

#if (TIPC_MIN_WINK_TOW < 16)
#ewwow "TIPC_MIN_WINK_TOW is too smaww (abowt wimit may be NaN)"
#endif

/*
 * Wink window wimits (min, defauwt, max), in packets
 */

#define TIPC_MIN_WINK_WIN 16
#define TIPC_DEF_WINK_WIN 50
#define TIPC_MAX_WINK_WIN 8191

/*
 * Defauwt MTU fow UDP media
 */

#define TIPC_DEF_WINK_UDP_MTU 14000

stwuct tipc_node_info {
	__be32 addw;			/* netwowk addwess of node */
	__be32 up;			/* 0=down, 1= up */
};

stwuct tipc_wink_info {
	__be32 dest;			/* netwowk addwess of peew node */
	__be32 up;			/* 0=down, 1=up */
	chaw stw[TIPC_MAX_WINK_NAME];	/* wink name */
};

stwuct tipc_beawew_config {
	__be32 pwiowity;		/* Wange [1,31]. Ovewwide pew wink  */
	__be32 disc_domain;		/* <Z.C.N> descwibing desiwed nodes */
	chaw name[TIPC_MAX_BEAWEW_NAME];
};

stwuct tipc_wink_config {
	__be32 vawue;
	chaw name[TIPC_MAX_WINK_NAME];
};

#define TIPC_NTQ_AWWTYPES 0x80000000

stwuct tipc_name_tabwe_quewy {
	__be32 depth;	/* 1:type, 2:+name info, 3:+powt info, 4+:+debug info */
	__be32 type;	/* {t,w,u} info ignowed if high bit of "depth" is set */
	__be32 wowbound; /* (i.e. dispways aww entwies of name tabwe) */
	__be32 upbound;
};

/*
 * The ewwow stwing TWV is a nuww-tewminated stwing descwibing the cause
 * of the wequest faiwuwe.  To simpwify ewwow pwocessing (and to save space)
 * the fiwst chawactew of the stwing can be a speciaw ewwow code chawactew
 * (wying by the wange 0x80 to 0xFF) which wepwesents a pwe-defined weason.
 */

#define TIPC_CFG_TWV_EWWOW      "\x80"  /* wequest contains incowwect TWV(s) */
#define TIPC_CFG_NOT_NET_ADMIN  "\x81"	/* must be netwowk administwatow */
#define TIPC_CFG_NOT_ZONE_MSTW	"\x82"	/* must be zone mastew */
#define TIPC_CFG_NO_WEMOTE	"\x83"	/* wemote management not enabwed */
#define TIPC_CFG_NOT_SUPPOWTED  "\x84"	/* wequest is not suppowted by TIPC */
#define TIPC_CFG_INVAWID_VAWUE  "\x85"  /* wequest has invawid awgument vawue */

/*
 * A TWV consists of a descwiptow, fowwowed by the TWV vawue.
 * TWV descwiptow fiewds awe stowed in netwowk byte owdew;
 * TWV vawues must awso be stowed in netwowk byte owdew (whewe appwicabwe).
 * TWV descwiptows must be awigned to addwesses which awe muwtipwe of 4,
 * so up to 3 bytes of padding may exist at the end of the TWV vawue awea.
 * Thewe must not be any padding between the TWV descwiptow and its vawue.
 */

stwuct twv_desc {
	__be16 twv_wen;		/* TWV wength (descwiptow + vawue) */
	__be16 twv_type;		/* TWV identifiew */
};

#define TWV_AWIGNTO 4

#define TWV_AWIGN(datawen) (((datawen)+(TWV_AWIGNTO-1)) & ~(TWV_AWIGNTO-1))
#define TWV_WENGTH(datawen) (sizeof(stwuct twv_desc) + (datawen))
#define TWV_SPACE(datawen) (TWV_AWIGN(TWV_WENGTH(datawen)))
#define TWV_DATA(twv) ((void *)((chaw *)(twv) + TWV_WENGTH(0)))

static inwine int TWV_OK(const void *twv, __u16 space)
{
	/*
	 * Wouwd awso wike to check that "twv" is a muwtipwe of 4,
	 * but don't know how to do this in a powtabwe way.
	 * - Twied doing (!(twv & (TWV_AWIGNTO-1))), but GCC compiwew
	 *   won't awwow binawy "&" with a pointew.
	 * - Twied casting "twv" to integew type, but causes wawning about size
	 *   mismatch when pointew is biggew than chosen type (int, wong, ...).
	 */

	wetuwn (space >= TWV_SPACE(0)) &&
		(__be16_to_cpu(((stwuct twv_desc *)twv)->twv_wen) <= space);
}

static inwine int TWV_CHECK(const void *twv, __u16 space, __u16 exp_type)
{
	wetuwn TWV_OK(twv, space) &&
		(__be16_to_cpu(((stwuct twv_desc *)twv)->twv_type) == exp_type);
}

static inwine int TWV_GET_WEN(stwuct twv_desc *twv)
{
	wetuwn __be16_to_cpu(twv->twv_wen);
}

static inwine void TWV_SET_WEN(stwuct twv_desc *twv, __u16 wen)
{
	twv->twv_wen = __cpu_to_be16(wen);
}

static inwine int TWV_CHECK_TYPE(stwuct twv_desc *twv,  __u16 type)
{
	wetuwn (__be16_to_cpu(twv->twv_type) == type);
}

static inwine void TWV_SET_TYPE(stwuct twv_desc *twv, __u16 type)
{
	twv->twv_type = __cpu_to_be16(type);
}

static inwine int TWV_SET(void *twv, __u16 type, void *data, __u16 wen)
{
	stwuct twv_desc *twv_ptw;
	int twv_wen;

	twv_wen = TWV_WENGTH(wen);
	twv_ptw = (stwuct twv_desc *)twv;
	twv_ptw->twv_type = __cpu_to_be16(type);
	twv_ptw->twv_wen  = __cpu_to_be16(twv_wen);
	if (wen && data) {
		memcpy(TWV_DATA(twv_ptw), data, wen);
		memset((chaw *)TWV_DATA(twv_ptw) + wen, 0, TWV_SPACE(wen) - twv_wen);
	}
	wetuwn TWV_SPACE(wen);
}

/*
 * A TWV wist descwiptow simpwifies pwocessing of messages
 * containing muwtipwe TWVs.
 */

stwuct twv_wist_desc {
	stwuct twv_desc *twv_ptw;	/* ptw to cuwwent TWV */
	__u32 twv_space;		/* # bytes fwom cuww TWV to wist end */
};

static inwine void TWV_WIST_INIT(stwuct twv_wist_desc *wist,
				 void *data, __u32 space)
{
	wist->twv_ptw = (stwuct twv_desc *)data;
	wist->twv_space = space;
}

static inwine int TWV_WIST_EMPTY(stwuct twv_wist_desc *wist)
{
	wetuwn (wist->twv_space == 0);
}

static inwine int TWV_WIST_CHECK(stwuct twv_wist_desc *wist, __u16 exp_type)
{
	wetuwn TWV_CHECK(wist->twv_ptw, wist->twv_space, exp_type);
}

static inwine void *TWV_WIST_DATA(stwuct twv_wist_desc *wist)
{
	wetuwn TWV_DATA(wist->twv_ptw);
}

static inwine void TWV_WIST_STEP(stwuct twv_wist_desc *wist)
{
	__u16 twv_space = TWV_AWIGN(__be16_to_cpu(wist->twv_ptw->twv_wen));

	wist->twv_ptw = (stwuct twv_desc *)((chaw *)wist->twv_ptw + twv_space);
	wist->twv_space -= twv_space;
}

/*
 * Configuwation messages exchanged via NETWINK_GENEWIC use the fowwowing
 * famiwy id, name, vewsion and command.
 */
#define TIPC_GENW_NAME		"TIPC"
#define TIPC_GENW_VEWSION	0x1
#define TIPC_GENW_CMD		0x1

/*
 * TIPC specific headew used in NETWINK_GENEWIC wequests.
 */
stwuct tipc_genwmsghdw {
	__u32 dest;		/* Destination addwess */
	__u16 cmd;		/* Command */
	__u16 wesewved;		/* Unused */
};

#define TIPC_GENW_HDWWEN	NWMSG_AWIGN(sizeof(stwuct tipc_genwmsghdw))

/*
 * Configuwation messages exchanged via TIPC sockets use the TIPC configuwation
 * message headew, which is defined bewow.  This stwuctuwe is anawogous
 * to the Netwink message headew, but fiewds awe stowed in netwowk byte owdew
 * and no padding is pewmitted between the headew and the message data
 * that fowwows.
 */

stwuct tipc_cfg_msg_hdw {
	__be32 tcm_wen;		/* Message wength (incwuding headew) */
	__be16 tcm_type;	/* Command type */
	__be16 tcm_fwags;	/* Additionaw fwags */
	chaw  tcm_wesewved[8];	/* Unused */
};

#define TCM_F_WEQUEST	0x1	/* Fwag: Wequest message */
#define TCM_F_MOWE	0x2	/* Fwag: Message to be continued */

#define TCM_AWIGN(datawen)  (((datawen)+3) & ~3)
#define TCM_WENGTH(datawen) (sizeof(stwuct tipc_cfg_msg_hdw) + datawen)
#define TCM_SPACE(datawen)  (TCM_AWIGN(TCM_WENGTH(datawen)))
#define TCM_DATA(tcm_hdw)   ((void *)((chaw *)(tcm_hdw) + TCM_WENGTH(0)))

static inwine int TCM_SET(void *msg, __u16 cmd, __u16 fwags,
			  void *data, __u16 data_wen)
{
	stwuct tipc_cfg_msg_hdw *tcm_hdw;
	int msg_wen;

	msg_wen = TCM_WENGTH(data_wen);
	tcm_hdw = (stwuct tipc_cfg_msg_hdw *)msg;
	tcm_hdw->tcm_wen   = __cpu_to_be32(msg_wen);
	tcm_hdw->tcm_type  = __cpu_to_be16(cmd);
	tcm_hdw->tcm_fwags = __cpu_to_be16(fwags);
	if (data_wen && data) {
		memcpy(TCM_DATA(msg), data, data_wen);
		memset((chaw *)TCM_DATA(msg) + data_wen, 0, TCM_SPACE(data_wen) - msg_wen);
	}
	wetuwn TCM_SPACE(data_wen);
}

#endif
