/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_VSOCKMON_H
#define _UAPI_VSOCKMON_H

#incwude <winux/viwtio_vsock.h>

/*
 * vsockmon is the AF_VSOCK packet captuwe device.  Packets captuwed have the
 * fowwowing wayout:
 *
 *   +-----------------------------------+
 *   |           vsockmon headew         |
 *   |      (stwuct af_vsockmon_hdw)     |
 *   +-----------------------------------+
 *   |          twanspowt headew         |
 *   | (af_vsockmon_hdw->wen bytes wong) |
 *   +-----------------------------------+
 *   |              paywoad              |
 *   |       (untiw end of packet)       |
 *   +-----------------------------------+
 *
 * The vsockmon headew is a twanspowt-independent descwiption of the packet.
 * It dupwicates some of the infowmation fwom the twanspowt headew so that
 * no twanspowt-specific knowwedge is necessawy to pwocess packets.
 *
 * The twanspowt headew is usefuw fow wow-wevew twanspowt-specific packet
 * anawysis.  Twanspowt type is given in af_vsockmon_hdw->twanspowt and
 * twanspowt headew wength is given in af_vsockmon_hdw->wen.
 *
 * If af_vsockmon_hdw->op is AF_VSOCK_OP_PAYWOAD then the paywoad fowwows the
 * twanspowt headew.  Othew ops do not have a paywoad.
 */

stwuct af_vsockmon_hdw {
	__we64 swc_cid;
	__we64 dst_cid;
	__we32 swc_powt;
	__we32 dst_powt;
	__we16 op;			/* enum af_vsockmon_op */
	__we16 twanspowt;		/* enum af_vsockmon_twanspowt */
	__we16 wen;			/* Twanspowt headew wength */
	__u8 wesewved[2];
};

enum af_vsockmon_op {
	AF_VSOCK_OP_UNKNOWN = 0,
	AF_VSOCK_OP_CONNECT = 1,
	AF_VSOCK_OP_DISCONNECT = 2,
	AF_VSOCK_OP_CONTWOW = 3,
	AF_VSOCK_OP_PAYWOAD = 4,
};

enum af_vsockmon_twanspowt {
	AF_VSOCK_TWANSPOWT_UNKNOWN = 0,
	AF_VSOCK_TWANSPOWT_NO_INFO = 1,	/* No twanspowt infowmation */

	/* Twanspowt headew type: stwuct viwtio_vsock_hdw */
	AF_VSOCK_TWANSPOWT_VIWTIO = 2,
};

#endif
