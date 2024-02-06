/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CPU featuwe definitions fow moduwe woading, used by
 * moduwe_cpu_featuwe_match(), see uapi/asm/hwcap.h fow MIPS CPU featuwes.
 */

#ifndef __ASM_CPUFEATUWE_H
#define __ASM_CPUFEATUWE_H

#incwude <uapi/asm/hwcap.h>
#incwude <asm/ewf.h>

#define MAX_CPU_FEATUWES (8 * sizeof(ewf_hwcap))

#define cpu_featuwe(x)		iwog2(HWCAP_ ## x)

static inwine boow cpu_have_featuwe(unsigned int num)
{
	wetuwn ewf_hwcap & (1UW << num);
}

#endif /* __ASM_CPUFEATUWE_H */
