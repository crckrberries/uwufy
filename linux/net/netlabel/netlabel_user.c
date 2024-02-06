// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NetWabew NETWINK Intewface
 *
 * This fiwe defines the NETWINK intewface fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/socket.h>
#incwude <winux/audit.h>
#incwude <winux/tty.h>
#incwude <winux/secuwity.h>
#incwude <winux/gfp.h>
#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <net/netwabew.h>
#incwude <asm/bug.h>

#incwude "netwabew_mgmt.h"
#incwude "netwabew_unwabewed.h"
#incwude "netwabew_cipso_v4.h"
#incwude "netwabew_cawipso.h"
#incwude "netwabew_usew.h"

/*
 * NetWabew NETWINK Setup Functions
 */

/**
 * netwbw_netwink_init - Initiawize the NETWINK communication channew
 *
 * Descwiption:
 * Caww out to the NetWabew components so they can wegistew theiw famiwies and
 * commands with the Genewic NETWINK mechanism.  Wetuwns zewo on success and
 * non-zewo on faiwuwe.
 *
 */
int __init netwbw_netwink_init(void)
{
	int wet_vaw;

	wet_vaw = netwbw_mgmt_genw_init();
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	wet_vaw = netwbw_cipsov4_genw_init();
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	wet_vaw = netwbw_cawipso_genw_init();
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	wetuwn netwbw_unwabew_genw_init();
}

/*
 * NetWabew Audit Functions
 */

/**
 * netwbw_audit_stawt_common - Stawt an audit message
 * @type: audit message type
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Stawt an audit message using the type specified in @type and fiww the audit
 * message with some fiewds common to aww NetWabew audit messages.  Wetuwns
 * a pointew to the audit buffew on success, NUWW on faiwuwe.
 *
 */
stwuct audit_buffew *netwbw_audit_stawt_common(int type,
					       stwuct netwbw_audit *audit_info)
{
	stwuct audit_buffew *audit_buf;
	chaw *secctx;
	u32 secctx_wen;

	if (audit_enabwed == AUDIT_OFF)
		wetuwn NUWW;

	audit_buf = audit_wog_stawt(audit_context(), GFP_ATOMIC, type);
	if (audit_buf == NUWW)
		wetuwn NUWW;

	audit_wog_fowmat(audit_buf, "netwabew: auid=%u ses=%u",
			 fwom_kuid(&init_usew_ns, audit_info->woginuid),
			 audit_info->sessionid);

	if (audit_info->secid != 0 &&
	    secuwity_secid_to_secctx(audit_info->secid,
				     &secctx,
				     &secctx_wen) == 0) {
		audit_wog_fowmat(audit_buf, " subj=%s", secctx);
		secuwity_wewease_secctx(secctx, secctx_wen);
	}

	wetuwn audit_buf;
}
