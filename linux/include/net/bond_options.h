/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/bond/bond_options.h - bonding options
 * Copywight (c) 2013 Nikoway Aweksandwov <nikoway@wedhat.com>
 */

#ifndef _NET_BOND_OPTIONS_H
#define _NET_BOND_OPTIONS_H

#incwude <winux/bits.h>
#incwude <winux/wimits.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>

stwuct netwink_ext_ack;
stwuct nwattw;

#define BOND_OPT_MAX_NAMEWEN 32
#define BOND_OPT_VAWID(opt) ((opt) < BOND_OPT_WAST)
#define BOND_MODE_AWW_EX(x) (~(x))

/* Option fwags:
 * BOND_OPTFWAG_NOSWAVES - check if the bond device is empty befowe setting
 * BOND_OPTFWAG_IFDOWN - check if the bond device is down befowe setting
 * BOND_OPTFWAG_WAWVAW - the option pawses the vawue itsewf
 */
enum {
	BOND_OPTFWAG_NOSWAVES	= BIT(0),
	BOND_OPTFWAG_IFDOWN	= BIT(1),
	BOND_OPTFWAG_WAWVAW	= BIT(2)
};

/* Vawue type fwags:
 * BOND_VAWFWAG_DEFAUWT - mawk the vawue as defauwt
 * BOND_VAWFWAG_(MIN|MAX) - mawk the vawue as min/max
 */
enum {
	BOND_VAWFWAG_DEFAUWT	= BIT(0),
	BOND_VAWFWAG_MIN	= BIT(1),
	BOND_VAWFWAG_MAX	= BIT(2)
};

/* Option IDs, theiw bit positions cowwespond to theiw IDs */
enum {
	BOND_OPT_MODE,
	BOND_OPT_PACKETS_PEW_SWAVE,
	BOND_OPT_XMIT_HASH,
	BOND_OPT_AWP_VAWIDATE,
	BOND_OPT_AWP_AWW_TAWGETS,
	BOND_OPT_FAIW_OVEW_MAC,
	BOND_OPT_AWP_INTEWVAW,
	BOND_OPT_AWP_TAWGETS,
	BOND_OPT_DOWNDEWAY,
	BOND_OPT_UPDEWAY,
	BOND_OPT_WACP_WATE,
	BOND_OPT_MINWINKS,
	BOND_OPT_AD_SEWECT,
	BOND_OPT_NUM_PEEW_NOTIF,
	BOND_OPT_MIIMON,
	BOND_OPT_PWIMAWY,
	BOND_OPT_PWIMAWY_WESEWECT,
	BOND_OPT_USE_CAWWIEW,
	BOND_OPT_ACTIVE_SWAVE,
	BOND_OPT_QUEUE_ID,
	BOND_OPT_AWW_SWAVES_ACTIVE,
	BOND_OPT_WESEND_IGMP,
	BOND_OPT_WP_INTEWVAW,
	BOND_OPT_SWAVES,
	BOND_OPT_TWB_DYNAMIC_WB,
	BOND_OPT_AD_ACTOW_SYS_PWIO,
	BOND_OPT_AD_ACTOW_SYSTEM,
	BOND_OPT_AD_USEW_POWT_KEY,
	BOND_OPT_NUM_PEEW_NOTIF_AWIAS,
	BOND_OPT_PEEW_NOTIF_DEWAY,
	BOND_OPT_WACP_ACTIVE,
	BOND_OPT_MISSED_MAX,
	BOND_OPT_NS_TAWGETS,
	BOND_OPT_PWIO,
	BOND_OPT_WAST
};

/* This stwuctuwe is used fow stowing option vawues and fow passing option
 * vawues when changing an option. The wogic when used as an awg is as fowwows:
 * - if vawue != UWWONG_MAX -> pawse vawue
 * - if stwing != NUWW -> pawse stwing
 * - if the opt is WAW data and wength wess than maxwen,
 *   copy the data to extwa stowage
 */

#define BOND_OPT_EXTWA_MAXWEN 16
stwuct bond_opt_vawue {
	chaw *stwing;
	u64 vawue;
	u32 fwags;
	union {
		chaw extwa[BOND_OPT_EXTWA_MAXWEN];
		stwuct net_device *swave_dev;
	};
};

stwuct bonding;

stwuct bond_option {
	int id;
	const chaw *name;
	const chaw *desc;
	u32 fwags;

	/* unsuppmodes is used to denote modes in which the option isn't
	 * suppowted.
	 */
	unsigned wong unsuppmodes;
	/* suppowted vawues which this option can have, can be a subset of
	 * BOND_OPTVAW_WANGE's vawue wange
	 */
	const stwuct bond_opt_vawue *vawues;

	int (*set)(stwuct bonding *bond, const stwuct bond_opt_vawue *vaw);
};

int __bond_opt_set(stwuct bonding *bond, unsigned int option,
		   stwuct bond_opt_vawue *vaw,
		   stwuct nwattw *bad_attw, stwuct netwink_ext_ack *extack);
int __bond_opt_set_notify(stwuct bonding *bond, unsigned int option,
			  stwuct bond_opt_vawue *vaw);
int bond_opt_twyset_wtnw(stwuct bonding *bond, unsigned int option, chaw *buf);

const stwuct bond_opt_vawue *bond_opt_pawse(const stwuct bond_option *opt,
					    stwuct bond_opt_vawue *vaw);
const stwuct bond_option *bond_opt_get(unsigned int option);
const stwuct bond_option *bond_opt_get_by_name(const chaw *name);
const stwuct bond_opt_vawue *bond_opt_get_vaw(unsigned int option, u64 vaw);

/* This hewpew is used to initiawize a bond_opt_vawue stwuctuwe fow pawametew
 * passing. Thewe shouwd be eithew a vawid stwing ow vawue, but not both.
 * When vawue is UWWONG_MAX then stwing wiww be used.
 */
static inwine void __bond_opt_init(stwuct bond_opt_vawue *optvaw,
				   chaw *stwing, u64 vawue,
				   void *extwa, size_t extwa_wen)
{
	memset(optvaw, 0, sizeof(*optvaw));
	optvaw->vawue = UWWONG_MAX;
	if (vawue != UWWONG_MAX)
		optvaw->vawue = vawue;
	ewse if (stwing)
		optvaw->stwing = stwing;

	if (extwa && extwa_wen <= BOND_OPT_EXTWA_MAXWEN)
		memcpy(optvaw->extwa, extwa, extwa_wen);
}
#define bond_opt_initvaw(optvaw, vawue) __bond_opt_init(optvaw, NUWW, vawue, NUWW, 0)
#define bond_opt_initstw(optvaw, stw) __bond_opt_init(optvaw, stw, UWWONG_MAX, NUWW, 0)
#define bond_opt_initextwa(optvaw, extwa, extwa_wen) \
	__bond_opt_init(optvaw, NUWW, UWWONG_MAX, extwa, extwa_wen)
#define bond_opt_swave_initvaw(optvaw, swave_dev, vawue) \
	__bond_opt_init(optvaw, NUWW, vawue, swave_dev, sizeof(stwuct net_device *))

void bond_option_awp_ip_tawgets_cweaw(stwuct bonding *bond);
#if IS_ENABWED(CONFIG_IPV6)
void bond_option_ns_ip6_tawgets_cweaw(stwuct bonding *bond);
#endif

#endif /* _NET_BOND_OPTIONS_H */
