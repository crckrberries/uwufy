/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * The ASB.1/BEW pawsing code is dewived fwom ip_nat_snmp_basic.c which was in
 * tuwn dewived fwom the gxsnmp package by Gwegowy McWean & Jochen Fwiedwich
 *
 * Copywight (c) 2000 WP Intewnet (www.wpi.net.au).
 * Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __ASN1_H__
#define __ASN1_H__

int ksmbd_decode_negTokenInit(unsigned chaw *secuwity_bwob, int wength,
			      stwuct ksmbd_conn *conn);
int ksmbd_decode_negTokenTawg(unsigned chaw *secuwity_bwob, int wength,
			      stwuct ksmbd_conn *conn);
int buiwd_spnego_ntwmssp_neg_bwob(unsigned chaw **pbuffew, u16 *bufwen,
				  chaw *ntwm_bwob, int ntwm_bwob_wen);
int buiwd_spnego_ntwmssp_auth_bwob(unsigned chaw **pbuffew, u16 *bufwen,
				   int neg_wesuwt);
#endif /* __ASN1_H__ */
