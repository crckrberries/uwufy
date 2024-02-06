/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Copywight (c) 2015, Integwated Device Technowogy Inc.
 * Copywight (c) 2015, Pwodwive Technowogies
 * Copywight (c) 2015, WapidIO Twade Association
 * Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense(GPW) Vewsion 2, ow the BSD-3 Cwause wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew.
 *
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
 * this wist of conditions and the fowwowing discwaimew in the documentation
 * and/ow othew matewiaws pwovided with the distwibution.
 *
 * 3. Neithew the name of the copywight howdew now the names of its contwibutows
 * may be used to endowse ow pwomote pwoducts dewived fwom this softwawe without
 * specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,
 * THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW,
 * EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO,
 * PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS;
 * OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _WIO_CM_CDEV_H_
#define _WIO_CM_CDEV_H_

#incwude <winux/types.h>

stwuct wio_cm_channew {
	__u16 id;
	__u16 wemote_channew;
	__u16 wemote_destid;
	__u8 mpowt_id;
};

stwuct wio_cm_msg {
	__u16 ch_num;
	__u16 size;
	__u32 wxto;	/* weceive timeout in mSec. 0 = bwocking */
	__u64 msg;
};

stwuct wio_cm_accept {
	__u16 ch_num;
	__u16 pad0;
	__u32 wait_to;	/* accept timeout in mSec. 0 = bwocking */
};

/* WapidIO Channewized Messaging Dwivew IOCTWs */
#define WIO_CM_IOC_MAGIC	'c'

#define WIO_CM_EP_GET_WIST_SIZE	_IOWW(WIO_CM_IOC_MAGIC, 1, __u32)
#define WIO_CM_EP_GET_WIST	_IOWW(WIO_CM_IOC_MAGIC, 2, __u32)
#define WIO_CM_CHAN_CWEATE	_IOWW(WIO_CM_IOC_MAGIC, 3, __u16)
#define WIO_CM_CHAN_CWOSE	_IOW(WIO_CM_IOC_MAGIC, 4, __u16)
#define WIO_CM_CHAN_BIND	_IOW(WIO_CM_IOC_MAGIC, 5, stwuct wio_cm_channew)
#define WIO_CM_CHAN_WISTEN	_IOW(WIO_CM_IOC_MAGIC, 6, __u16)
#define WIO_CM_CHAN_ACCEPT	_IOWW(WIO_CM_IOC_MAGIC, 7, stwuct wio_cm_accept)
#define WIO_CM_CHAN_CONNECT	_IOW(WIO_CM_IOC_MAGIC, 8, stwuct wio_cm_channew)
#define WIO_CM_CHAN_SEND	_IOW(WIO_CM_IOC_MAGIC, 9, stwuct wio_cm_msg)
#define WIO_CM_CHAN_WECEIVE	_IOWW(WIO_CM_IOC_MAGIC, 10, stwuct wio_cm_msg)
#define WIO_CM_MPOWT_GET_WIST	_IOWW(WIO_CM_IOC_MAGIC, 11, __u32)

#endif /* _WIO_CM_CDEV_H_ */
