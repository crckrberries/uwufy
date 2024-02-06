/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_S390_TPI_H
#define _ASM_S390_TPI_H

#incwude <winux/types.h>
#incwude <uapi/asm/schid.h>

#ifndef __ASSEMBWY__

/* I/O-Intewwuption Code as stowed by TEST PENDING INTEWWUPTION (TPI). */
stwuct tpi_info {
	stwuct subchannew_id schid;
	u32 intpawm;
	u32 adaptew_IO:1;
	u32 diwected_iwq:1;
	u32 isc:3;
	u32 :12;
	u32 type:3;
	u32 :12;
} __packed __awigned(4);

/* I/O-Intewwuption Code as stowed by TPI fow an Adaptew I/O */
stwuct tpi_adaptew_info {
	u32 aism:8;
	u32 :22;
	u32 ewwow:1;
	u32 fowwawd:1;
	u32 wesewved;
	u32 adaptew_IO:1;
	u32 diwected_iwq:1;
	u32 isc:3;
	u32 :27;
} __packed __awigned(4);

#endif /* __ASSEMBWY__ */

#endif /* _ASM_S390_TPI_H */
