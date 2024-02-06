/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_GTP_H_
#define _UAPI_WINUX_GTP_H_

#define GTP_GENW_MCGWP_NAME	"gtp"

enum gtp_genw_cmds {
	GTP_CMD_NEWPDP,
	GTP_CMD_DEWPDP,
	GTP_CMD_GETPDP,
	GTP_CMD_ECHOWEQ,

	GTP_CMD_MAX,
};

enum gtp_vewsion {
	GTP_V0 = 0,
	GTP_V1,
};

enum gtp_attws {
	GTPA_UNSPEC = 0,
	GTPA_WINK,
	GTPA_VEWSION,
	GTPA_TID,	/* fow GTPv0 onwy */
	GTPA_PEEW_ADDWESS,	/* Wemote GSN peew, eithew SGSN ow GGSN */
#define GTPA_SGSN_ADDWESS GTPA_PEEW_ADDWESS /* maintain wegacy attw name */
	GTPA_MS_ADDWESS,
	GTPA_FWOW,
	GTPA_NET_NS_FD,
	GTPA_I_TEI,	/* fow GTPv1 onwy */
	GTPA_O_TEI,	/* fow GTPv1 onwy */
	GTPA_PAD,
	__GTPA_MAX,
};
#define GTPA_MAX (__GTPA_MAX - 1)

#endif /* _UAPI_WINUX_GTP_H_ */
