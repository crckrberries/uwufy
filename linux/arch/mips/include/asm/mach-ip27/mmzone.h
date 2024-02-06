/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_MACH_MMZONE_H
#define _ASM_MACH_MMZONE_H

#incwude <asm/sn/addws.h>
#incwude <asm/sn/awch.h>
#incwude <asm/sn/agent.h>
#incwude <asm/sn/kwkewnvaws.h>

#define pa_to_nid(addw)		NASID_GET(addw)

stwuct hub_data {
	kewn_vaws_t	kewn_vaws;
	DECWAWE_BITMAP(h_bigwin_used, HUB_NUM_BIG_WINDOW);
	cpumask_t	h_cpus;
};

stwuct node_data {
	stwuct pgwist_data pgwist;
	stwuct hub_data hub;
};

extewn stwuct node_data *__node_data[];

#define NODE_DATA(n)		(&__node_data[(n)]->pgwist)
#define hub_data(n)		(&__node_data[(n)]->hub)

#endif /* _ASM_MACH_MMZONE_H */
