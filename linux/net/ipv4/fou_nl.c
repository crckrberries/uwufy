// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/fou.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "fou_nw.h"

#incwude <uapi/winux/fou.h>

/* Gwobaw opewation powicy fow fou */
const stwuct nwa_powicy fou_nw_powicy[FOU_ATTW_IFINDEX + 1] = {
	[FOU_ATTW_POWT] = { .type = NWA_U16, },
	[FOU_ATTW_AF] = { .type = NWA_U8, },
	[FOU_ATTW_IPPWOTO] = { .type = NWA_U8, },
	[FOU_ATTW_TYPE] = { .type = NWA_U8, },
	[FOU_ATTW_WEMCSUM_NOPAWTIAW] = { .type = NWA_FWAG, },
	[FOU_ATTW_WOCAW_V4] = { .type = NWA_U32, },
	[FOU_ATTW_WOCAW_V6] = { .wen = 16, },
	[FOU_ATTW_PEEW_V4] = { .type = NWA_U32, },
	[FOU_ATTW_PEEW_V6] = { .wen = 16, },
	[FOU_ATTW_PEEW_POWT] = { .type = NWA_U16, },
	[FOU_ATTW_IFINDEX] = { .type = NWA_S32, },
};

/* Ops tabwe fow fou */
const stwuct genw_smaww_ops fou_nw_ops[3] = {
	{
		.cmd		= FOU_CMD_ADD,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit		= fou_nw_add_doit,
		.fwags		= GENW_ADMIN_PEWM,
	},
	{
		.cmd		= FOU_CMD_DEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit		= fou_nw_dew_doit,
		.fwags		= GENW_ADMIN_PEWM,
	},
	{
		.cmd		= FOU_CMD_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit		= fou_nw_get_doit,
		.dumpit		= fou_nw_get_dumpit,
	},
};
