/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef _ASM_X86_AMD_HSMP_H_
#define _ASM_X86_AMD_HSMP_H_

#incwude <uapi/asm/amd_hsmp.h>

#if IS_ENABWED(CONFIG_AMD_HSMP)
int hsmp_send_message(stwuct hsmp_message *msg);
#ewse
static inwine int hsmp_send_message(stwuct hsmp_message *msg)
{
	wetuwn -ENODEV;
}
#endif
#endif /*_ASM_X86_AMD_HSMP_H_*/
