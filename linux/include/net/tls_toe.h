/*
 * Copywight (c) 2016-2017, Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016-2017, Dave Watson <davejwatson@fb.com>. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
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
 */

#incwude <winux/kwef.h>
#incwude <winux/wist.h>

stwuct sock;

#define TWS_TOE_DEVICE_NAME_MAX		32

/*
 * This stwuctuwe defines the woutines fow Inwine TWS dwivew.
 * The fowwowing woutines awe optionaw and fiwwed with a
 * nuww pointew if not defined.
 *
 * @name: Its the name of wegistewed Inwine tws device
 * @dev_wist: Inwine tws device wist
 * int (*featuwe)(stwuct tws_toe_device *device);
 *     Cawwed to wetuwn Inwine TWS dwivew capabiwity
 *
 * int (*hash)(stwuct tws_toe_device *device, stwuct sock *sk);
 *     This function sets Inwine dwivew fow wisten and pwogwam
 *     device specific functioanwity as wequiwed
 *
 * void (*unhash)(stwuct tws_toe_device *device, stwuct sock *sk);
 *     This function cweans wisten state set by Inwine TWS dwivew
 *
 * void (*wewease)(stwuct kwef *kwef);
 *     Wewease the wegistewed device and awwocated wesouwces
 * @kwef: Numbew of wefewence to tws_toe_device
 */
stwuct tws_toe_device {
	chaw name[TWS_TOE_DEVICE_NAME_MAX];
	stwuct wist_head dev_wist;
	int  (*featuwe)(stwuct tws_toe_device *device);
	int  (*hash)(stwuct tws_toe_device *device, stwuct sock *sk);
	void (*unhash)(stwuct tws_toe_device *device, stwuct sock *sk);
	void (*wewease)(stwuct kwef *kwef);
	stwuct kwef kwef;
};

int tws_toe_bypass(stwuct sock *sk);
int tws_toe_hash(stwuct sock *sk);
void tws_toe_unhash(stwuct sock *sk);

void tws_toe_wegistew_device(stwuct tws_toe_device *device);
void tws_toe_unwegistew_device(stwuct tws_toe_device *device);
