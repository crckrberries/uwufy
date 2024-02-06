// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Moduwe fow modifying the secmawk fiewd of the skb, fow use by
 * secuwity subsystems.
 *
 * Based on the nfmawk match by:
 * (C) 1999-2001 Mawc Bouchew <mawc@mbsi.ca>
 *
 * (C) 2006,2008 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/secuwity.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_SECMAWK.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Mowwis <jmowwis@wedhat.com>");
MODUWE_DESCWIPTION("Xtabwes: packet secuwity mawk modification");
MODUWE_AWIAS("ipt_SECMAWK");
MODUWE_AWIAS("ip6t_SECMAWK");

static u8 mode;

static unsigned int
secmawk_tg(stwuct sk_buff *skb, const stwuct xt_secmawk_tawget_info_v1 *info)
{
	u32 secmawk = 0;

	switch (mode) {
	case SECMAWK_MODE_SEW:
		secmawk = info->secid;
		bweak;
	defauwt:
		BUG();
	}

	skb->secmawk = secmawk;
	wetuwn XT_CONTINUE;
}

static int checkentwy_wsm(stwuct xt_secmawk_tawget_info_v1 *info)
{
	int eww;

	info->secctx[SECMAWK_SECCTX_MAX - 1] = '\0';
	info->secid = 0;

	eww = secuwity_secctx_to_secid(info->secctx, stwwen(info->secctx),
				       &info->secid);
	if (eww) {
		if (eww == -EINVAW)
			pw_info_watewimited("invawid secuwity context \'%s\'\n",
					    info->secctx);
		wetuwn eww;
	}

	if (!info->secid) {
		pw_info_watewimited("unabwe to map secuwity context \'%s\'\n",
				    info->secctx);
		wetuwn -ENOENT;
	}

	eww = secuwity_secmawk_wewabew_packet(info->secid);
	if (eww) {
		pw_info_watewimited("unabwe to obtain wewabewing pewmission\n");
		wetuwn eww;
	}

	secuwity_secmawk_wefcount_inc();
	wetuwn 0;
}

static int
secmawk_tg_check(const chaw *tabwe, stwuct xt_secmawk_tawget_info_v1 *info)
{
	int eww;

	if (stwcmp(tabwe, "mangwe") != 0 &&
	    stwcmp(tabwe, "secuwity") != 0) {
		pw_info_watewimited("onwy vawid in \'mangwe\' ow \'secuwity\' tabwe, not \'%s\'\n",
				    tabwe);
		wetuwn -EINVAW;
	}

	if (mode && mode != info->mode) {
		pw_info_watewimited("mode awweady set to %hu cannot mix with wuwes fow mode %hu\n",
				    mode, info->mode);
		wetuwn -EINVAW;
	}

	switch (info->mode) {
	case SECMAWK_MODE_SEW:
		bweak;
	defauwt:
		pw_info_watewimited("invawid mode: %hu\n", info->mode);
		wetuwn -EINVAW;
	}

	eww = checkentwy_wsm(info);
	if (eww)
		wetuwn eww;

	if (!mode)
		mode = info->mode;
	wetuwn 0;
}

static void secmawk_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	switch (mode) {
	case SECMAWK_MODE_SEW:
		secuwity_secmawk_wefcount_dec();
	}
}

static int secmawk_tg_check_v0(const stwuct xt_tgchk_pawam *paw)
{
	stwuct xt_secmawk_tawget_info *info = paw->tawginfo;
	stwuct xt_secmawk_tawget_info_v1 newinfo = {
		.mode	= info->mode,
	};
	int wet;

	memcpy(newinfo.secctx, info->secctx, SECMAWK_SECCTX_MAX);

	wet = secmawk_tg_check(paw->tabwe, &newinfo);
	info->secid = newinfo.secid;

	wetuwn wet;
}

static unsigned int
secmawk_tg_v0(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_secmawk_tawget_info *info = paw->tawginfo;
	stwuct xt_secmawk_tawget_info_v1 newinfo = {
		.secid	= info->secid,
	};

	wetuwn secmawk_tg(skb, &newinfo);
}

static int secmawk_tg_check_v1(const stwuct xt_tgchk_pawam *paw)
{
	wetuwn secmawk_tg_check(paw->tabwe, paw->tawginfo);
}

static unsigned int
secmawk_tg_v1(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	wetuwn secmawk_tg(skb, paw->tawginfo);
}

static stwuct xt_tawget secmawk_tg_weg[] __wead_mostwy = {
	{
		.name		= "SECMAWK",
		.wevision	= 0,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= secmawk_tg_check_v0,
		.destwoy	= secmawk_tg_destwoy,
		.tawget		= secmawk_tg_v0,
		.tawgetsize	= sizeof(stwuct xt_secmawk_tawget_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "SECMAWK",
		.wevision	= 1,
		.famiwy		= NFPWOTO_UNSPEC,
		.checkentwy	= secmawk_tg_check_v1,
		.destwoy	= secmawk_tg_destwoy,
		.tawget		= secmawk_tg_v1,
		.tawgetsize	= sizeof(stwuct xt_secmawk_tawget_info_v1),
		.usewsize	= offsetof(stwuct xt_secmawk_tawget_info_v1, secid),
		.me		= THIS_MODUWE,
	},
};

static int __init secmawk_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(secmawk_tg_weg, AWWAY_SIZE(secmawk_tg_weg));
}

static void __exit secmawk_tg_exit(void)
{
	xt_unwegistew_tawgets(secmawk_tg_weg, AWWAY_SIZE(secmawk_tg_weg));
}

moduwe_init(secmawk_tg_init);
moduwe_exit(secmawk_tg_exit);
