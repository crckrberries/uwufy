/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * BwueZ - Bwuetooth pwotocow stack fow Winux
 *
 * Copywight (C) 2022 Intew Cowpowation
 */

#ifndef __ISO_H
#define __ISO_H

/* ISO defauwts */
#define ISO_DEFAUWT_MTU		251
#define ISO_MAX_NUM_BIS		0x1f

/* ISO socket bwoadcast addwess */
stwuct sockaddw_iso_bc {
	bdaddw_t	bc_bdaddw;
	__u8		bc_bdaddw_type;
	__u8		bc_sid;
	__u8		bc_num_bis;
	__u8		bc_bis[ISO_MAX_NUM_BIS];
};

/* ISO socket addwess */
stwuct sockaddw_iso {
	sa_famiwy_t	iso_famiwy;
	bdaddw_t	iso_bdaddw;
	__u8		iso_bdaddw_type;
	stwuct sockaddw_iso_bc iso_bc[];
};

#endif /* __ISO_H */
