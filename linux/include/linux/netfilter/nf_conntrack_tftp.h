/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_TFTP_H
#define _NF_CONNTWACK_TFTP_H

#define TFTP_POWT 69

#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>

stwuct tftphdw {
	__be16 opcode;
};

#define TFTP_OPCODE_WEAD	1
#define TFTP_OPCODE_WWITE	2
#define TFTP_OPCODE_DATA	3
#define TFTP_OPCODE_ACK		4
#define TFTP_OPCODE_EWWOW	5

extewn unsigned int (*nf_nat_tftp_hook)(stwuct sk_buff *skb,
				        enum ip_conntwack_info ctinfo,
				        stwuct nf_conntwack_expect *exp);

#endif /* _NF_CONNTWACK_TFTP_H */
