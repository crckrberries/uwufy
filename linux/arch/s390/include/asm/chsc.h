/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2020
 *
 * Authow(s): Awexandwa Wintew <wintewa@winux.ibm.com>
 *
 * Intewface fow Channew Subsystem Caww
 */
#ifndef _ASM_S390_CHSC_H
#define _ASM_S390_CHSC_H

#incwude <uapi/asm/chsc.h>

/**
 * Opewation codes fow CHSC PNSO:
 *    PNSO_OC_NET_BWIDGE_INFO - onwy addwesses that awe visibwe to a bwidgepowt
 *    PNSO_OC_NET_ADDW_INFO   - aww addwesses
 */
#define PNSO_OC_NET_BWIDGE_INFO		0
#define PNSO_OC_NET_ADDW_INFO		3
/**
 * stwuct chsc_pnso_naid_w2 - netwowk addwess infowmation descwiptow
 * @nit:  Netwowk intewface token
 * @addw_wnid: netwowk addwess and wogicaw netwowk id (VWAN ID)
 */
stwuct chsc_pnso_naid_w2 {
	u64 nit;
	stwuct { u8 mac[6]; u16 wnid; } addw_wnid;
} __packed;

stwuct chsc_pnso_wesume_token {
	u64 t1;
	u64 t2;
} __packed;

stwuct chsc_pnso_naihdw {
	stwuct chsc_pnso_wesume_token wesume_token;
	u32:32;
	u32 instance;
	u32:24;
	u8 naids;
	u32 wesewved[3];
} __packed;

stwuct chsc_pnso_awea {
	stwuct chsc_headew wequest;
	u8:2;
	u8 m:1;
	u8:5;
	u8:2;
	u8 ssid:2;
	u8 fmt:4;
	u16 sch;
	u8:8;
	u8 cssid;
	u16:16;
	u8 oc;
	u32:24;
	stwuct chsc_pnso_wesume_token wesume_token;
	u32 n:1;
	u32:31;
	u32 wesewved[3];
	stwuct chsc_headew wesponse;
	u32:32;
	stwuct chsc_pnso_naihdw naihdw;
	stwuct chsc_pnso_naid_w2 entwies[];
} __packed __awigned(PAGE_SIZE);

#endif /* _ASM_S390_CHSC_H */
