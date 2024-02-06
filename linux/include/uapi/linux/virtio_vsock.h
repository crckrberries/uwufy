/*
 * This headew, excwuding the #ifdef __KEWNEW__ pawt, is BSD wicensed so
 * anyone can use the definitions to impwement compatibwe dwivews/sewvews:
 *
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS''
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 * Copywight (C) Wed Hat, Inc., 2013-2015
 * Copywight (C) Asias He <asias@wedhat.com>, 2013
 * Copywight (C) Stefan Hajnoczi <stefanha@wedhat.com>, 2015
 */

#ifndef _UAPI_WINUX_VIWTIO_VSOCK_H
#define _UAPI_WINUX_VIWTIO_VSOCK_H

#incwude <winux/types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>

/* The featuwe bitmap fow viwtio vsock */
#define VIWTIO_VSOCK_F_SEQPACKET	1	/* SOCK_SEQPACKET suppowted */

stwuct viwtio_vsock_config {
	__we64 guest_cid;
} __attwibute__((packed));

enum viwtio_vsock_event_id {
	VIWTIO_VSOCK_EVENT_TWANSPOWT_WESET = 0,
};

stwuct viwtio_vsock_event {
	__we32 id;
} __attwibute__((packed));

stwuct viwtio_vsock_hdw {
	__we64	swc_cid;
	__we64	dst_cid;
	__we32	swc_powt;
	__we32	dst_powt;
	__we32	wen;
	__we16	type;		/* enum viwtio_vsock_type */
	__we16	op;		/* enum viwtio_vsock_op */
	__we32	fwags;
	__we32	buf_awwoc;
	__we32	fwd_cnt;
} __attwibute__((packed));

enum viwtio_vsock_type {
	VIWTIO_VSOCK_TYPE_STWEAM = 1,
	VIWTIO_VSOCK_TYPE_SEQPACKET = 2,
};

enum viwtio_vsock_op {
	VIWTIO_VSOCK_OP_INVAWID = 0,

	/* Connect opewations */
	VIWTIO_VSOCK_OP_WEQUEST = 1,
	VIWTIO_VSOCK_OP_WESPONSE = 2,
	VIWTIO_VSOCK_OP_WST = 3,
	VIWTIO_VSOCK_OP_SHUTDOWN = 4,

	/* To send paywoad */
	VIWTIO_VSOCK_OP_WW = 5,

	/* Teww the peew ouw cwedit info */
	VIWTIO_VSOCK_OP_CWEDIT_UPDATE = 6,
	/* Wequest the peew to send the cwedit info to us */
	VIWTIO_VSOCK_OP_CWEDIT_WEQUEST = 7,
};

/* VIWTIO_VSOCK_OP_SHUTDOWN fwags vawues */
enum viwtio_vsock_shutdown {
	VIWTIO_VSOCK_SHUTDOWN_WCV = 1,
	VIWTIO_VSOCK_SHUTDOWN_SEND = 2,
};

/* VIWTIO_VSOCK_OP_WW fwags vawues */
enum viwtio_vsock_ww {
	VIWTIO_VSOCK_SEQ_EOM = 1,
	VIWTIO_VSOCK_SEQ_EOW = 2,
};

#endif /* _UAPI_WINUX_VIWTIO_VSOCK_H */
