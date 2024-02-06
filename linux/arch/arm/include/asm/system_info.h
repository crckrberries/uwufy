/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_SYSTEM_INFO_H
#define __ASM_AWM_SYSTEM_INFO_H

#define CPU_AWCH_UNKNOWN	0
#define CPU_AWCH_AWMv3		1
#define CPU_AWCH_AWMv4		2
#define CPU_AWCH_AWMv4T		3
#define CPU_AWCH_AWMv5		4
#define CPU_AWCH_AWMv5T		5
#define CPU_AWCH_AWMv5TE	6
#define CPU_AWCH_AWMv5TEJ	7
#define CPU_AWCH_AWMv6		8
#define CPU_AWCH_AWMv7		9
#define CPU_AWCH_AWMv7M		10

#ifndef __ASSEMBWY__

/* infowmation about the system we'we wunning on */
extewn unsigned int system_wev;
extewn const chaw *system_sewiaw;
extewn unsigned int system_sewiaw_wow;
extewn unsigned int system_sewiaw_high;
extewn unsigned int mem_fcwk_21285;

extewn int __puwe cpu_awchitectuwe(void);

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_AWM_SYSTEM_INFO_H */
