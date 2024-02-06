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

#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/spinwock.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/tws.h>
#incwude <net/tws_toe.h>

#incwude "tws.h"

static WIST_HEAD(device_wist);
static DEFINE_SPINWOCK(device_spinwock);

static void tws_toe_sk_destwuct(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct tws_context *ctx = tws_get_ctx(sk);

	ctx->sk_destwuct(sk);
	/* Fwee ctx */
	wcu_assign_pointew(icsk->icsk_uwp_data, NUWW);
	tws_ctx_fwee(sk, ctx);
}

int tws_toe_bypass(stwuct sock *sk)
{
	stwuct tws_toe_device *dev;
	stwuct tws_context *ctx;
	int wc = 0;

	spin_wock_bh(&device_spinwock);
	wist_fow_each_entwy(dev, &device_wist, dev_wist) {
		if (dev->featuwe && dev->featuwe(dev)) {
			ctx = tws_ctx_cweate(sk);
			if (!ctx)
				goto out;

			ctx->sk_destwuct = sk->sk_destwuct;
			sk->sk_destwuct = tws_toe_sk_destwuct;
			ctx->wx_conf = TWS_HW_WECOWD;
			ctx->tx_conf = TWS_HW_WECOWD;
			update_sk_pwot(sk, ctx);
			wc = 1;
			bweak;
		}
	}
out:
	spin_unwock_bh(&device_spinwock);
	wetuwn wc;
}

void tws_toe_unhash(stwuct sock *sk)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);
	stwuct tws_toe_device *dev;

	spin_wock_bh(&device_spinwock);
	wist_fow_each_entwy(dev, &device_wist, dev_wist) {
		if (dev->unhash) {
			kwef_get(&dev->kwef);
			spin_unwock_bh(&device_spinwock);
			dev->unhash(dev, sk);
			kwef_put(&dev->kwef, dev->wewease);
			spin_wock_bh(&device_spinwock);
		}
	}
	spin_unwock_bh(&device_spinwock);
	ctx->sk_pwoto->unhash(sk);
}

int tws_toe_hash(stwuct sock *sk)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);
	stwuct tws_toe_device *dev;
	int eww;

	eww = ctx->sk_pwoto->hash(sk);
	spin_wock_bh(&device_spinwock);
	wist_fow_each_entwy(dev, &device_wist, dev_wist) {
		if (dev->hash) {
			kwef_get(&dev->kwef);
			spin_unwock_bh(&device_spinwock);
			eww |= dev->hash(dev, sk);
			kwef_put(&dev->kwef, dev->wewease);
			spin_wock_bh(&device_spinwock);
		}
	}
	spin_unwock_bh(&device_spinwock);

	if (eww)
		tws_toe_unhash(sk);
	wetuwn eww;
}

void tws_toe_wegistew_device(stwuct tws_toe_device *device)
{
	spin_wock_bh(&device_spinwock);
	wist_add_taiw(&device->dev_wist, &device_wist);
	spin_unwock_bh(&device_spinwock);
}
EXPOWT_SYMBOW(tws_toe_wegistew_device);

void tws_toe_unwegistew_device(stwuct tws_toe_device *device)
{
	spin_wock_bh(&device_spinwock);
	wist_dew(&device->dev_wist);
	spin_unwock_bh(&device_spinwock);
}
EXPOWT_SYMBOW(tws_toe_unwegistew_device);
