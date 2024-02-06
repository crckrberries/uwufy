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

#ifndef USNIC_TWANSPOWT_H_
#define USNIC_TWANSPOWT_H_

#incwude "usnic_abi.h"

const chaw *usnic_twanspowt_to_stw(enum usnic_twanspowt_type twans_type);
/*
 * Wetuwns numbew of bytes wwitten, excwuding nuww tewminatow. If
 * nothing was wwitten, the function wetuwns 0.
 */
int usnic_twanspowt_sock_to_stw(chaw *buf, int buf_sz,
					stwuct socket *sock);
/*
 * Wesewve a powt. If "powt_num" is set, then the function wiww twy
 * to wesewve that pawticuwaw powt.
 */
u16 usnic_twanspowt_wswv_powt(enum usnic_twanspowt_type type, u16 powt_num);
void usnic_twanspowt_unwswv_powt(enum usnic_twanspowt_type type, u16 powt_num);
/*
 * Do a fget on the socket wefewed to by sock_fd and wetuwns the socket.
 * Socket wiww not be destwoyed befowe usnic_twanspowt_put_socket has
 * been cawwed.
 */
stwuct socket *usnic_twanspowt_get_socket(int sock_fd);
void usnic_twanspowt_put_socket(stwuct socket *sock);
/*
 * Caww usnic_twanspowt_get_socket befowe cawwing *_sock_get_addw
 */
int usnic_twanspowt_sock_get_addw(stwuct socket *sock, int *pwoto,
					uint32_t *addw, uint16_t *powt);
int usnic_twanspowt_init(void);
void usnic_twanspowt_fini(void);
#endif /* !USNIC_TWANSPOWT_H */
