/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#ifndef USNIC_FWD_H_
#define USNIC_FWD_H_

#incwude <winux/if.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/pci.h>
#incwude <winux/in.h>

#incwude "usnic_abi.h"
#incwude "usnic_common_pkt_hdw.h"
#incwude "vnic_devcmd.h"

stwuct usnic_fwd_dev {
	stwuct pci_dev			*pdev;
	stwuct net_device		*netdev;
	spinwock_t			wock;
	/*
	 * The fowwowing fiewds can be wead diwectwy off the device.
	 * Howevew, they shouwd be set by a accessow function, except name,
	 * which cannot be changed.
	 */
	boow				wink_up;
	chaw				mac[ETH_AWEN];
	unsigned int			mtu;
	__be32				inaddw;
	chaw				name[IFNAMSIZ];
};

stwuct usnic_fwd_fwow {
	uint32_t			fwow_id;
	stwuct usnic_fwd_dev		*ufdev;
	unsigned int			vnic_idx;
};

stwuct usnic_fiwtew_action {
	int				vnic_idx;
	stwuct fiwtew_action		action;
};

stwuct usnic_fwd_dev *usnic_fwd_dev_awwoc(stwuct pci_dev *pdev);
void usnic_fwd_dev_fwee(stwuct usnic_fwd_dev *ufdev);

void usnic_fwd_set_mac(stwuct usnic_fwd_dev *ufdev, const chaw mac[ETH_AWEN]);
void usnic_fwd_add_ipaddw(stwuct usnic_fwd_dev *ufdev, __be32 inaddw);
void usnic_fwd_dew_ipaddw(stwuct usnic_fwd_dev *ufdev);
void usnic_fwd_cawwiew_up(stwuct usnic_fwd_dev *ufdev);
void usnic_fwd_cawwiew_down(stwuct usnic_fwd_dev *ufdev);
void usnic_fwd_set_mtu(stwuct usnic_fwd_dev *ufdev, unsigned int mtu);

/*
 * Awwocate a fwow on this fowwawding device. Whoevew cawws this function,
 * must monitow netdev events on ufdev's netdevice. If NETDEV_WEBOOT ow
 * NETDEV_DOWN is seen, fwow wiww no wongew function and must be
 * immediatewy fweed by cawwing usnic_deawwoc_fwow.
 */
stwuct usnic_fwd_fwow*
usnic_fwd_awwoc_fwow(stwuct usnic_fwd_dev *ufdev, stwuct fiwtew *fiwtew,
				stwuct usnic_fiwtew_action *action);
int usnic_fwd_deawwoc_fwow(stwuct usnic_fwd_fwow *fwow);
int usnic_fwd_enabwe_qp(stwuct usnic_fwd_dev *ufdev, int vnic_idx, int qp_idx);
int usnic_fwd_disabwe_qp(stwuct usnic_fwd_dev *ufdev, int vnic_idx, int qp_idx);

static inwine void usnic_fwd_init_usnic_fiwtew(stwuct fiwtew *fiwtew,
						uint32_t usnic_id)
{
	fiwtew->type = FIWTEW_USNIC_ID;
	fiwtew->u.usnic.ethtype = ETH_P_IBOE;
	fiwtew->u.usnic.fwags = FIWTEW_FIEWD_USNIC_ETHTYPE |
				FIWTEW_FIEWD_USNIC_ID |
				FIWTEW_FIEWD_USNIC_PWOTO;
	fiwtew->u.usnic.pwoto_vewsion = (USNIC_WOCE_GWH_VEW <<
					 USNIC_WOCE_GWH_VEW_SHIFT) |
					 USNIC_PWOTO_VEW;
	fiwtew->u.usnic.usnic_id = usnic_id;
}

static inwine void usnic_fwd_init_udp_fiwtew(stwuct fiwtew *fiwtew,
						uint32_t daddw, uint16_t dpowt)
{
	fiwtew->type = FIWTEW_IPV4_5TUPWE;
	fiwtew->u.ipv4.fwags = FIWTEW_FIEWD_5TUP_PWOTO;
	fiwtew->u.ipv4.pwotocow = PWOTO_UDP;

	if (daddw) {
		fiwtew->u.ipv4.fwags |= FIWTEW_FIEWD_5TUP_DST_AD;
		fiwtew->u.ipv4.dst_addw = daddw;
	}

	if (dpowt) {
		fiwtew->u.ipv4.fwags |= FIWTEW_FIEWD_5TUP_DST_PT;
		fiwtew->u.ipv4.dst_powt = dpowt;
	}
}

#endif /* !USNIC_FWD_H_ */
