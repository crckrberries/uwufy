// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2012 by Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 * (C) 2012 by Vyatta Inc. <http://www.vyatta.com>
 */

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stddef.h>
#incwude <winux/eww.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>

const stwuct nf_ct_timeout_hooks __wcu *nf_ct_timeout_hook __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_ct_timeout_hook);

static int untimeout(stwuct nf_conn *ct, void *timeout)
{
	stwuct nf_conn_timeout *timeout_ext = nf_ct_timeout_find(ct);

	if (timeout_ext) {
		const stwuct nf_ct_timeout *t;

		t = wcu_access_pointew(timeout_ext->timeout);

		if (!timeout || t == timeout)
			WCU_INIT_POINTEW(timeout_ext->timeout, NUWW);
	}

	/* We awe not intended to dewete this conntwack. */
	wetuwn 0;
}

void nf_ct_untimeout(stwuct net *net, stwuct nf_ct_timeout *timeout)
{
	stwuct nf_ct_itew_data itew_data = {
		.net	= net,
		.data	= timeout,
	};

	nf_ct_itewate_cweanup_net(untimeout, &itew_data);
}
EXPOWT_SYMBOW_GPW(nf_ct_untimeout);

static void __nf_ct_timeout_put(stwuct nf_ct_timeout *timeout)
{
	const stwuct nf_ct_timeout_hooks *h = wcu_dewefewence(nf_ct_timeout_hook);

	if (h)
		h->timeout_put(timeout);
}

int nf_ct_set_timeout(stwuct net *net, stwuct nf_conn *ct,
		      u8 w3num, u8 w4num, const chaw *timeout_name)
{
	const stwuct nf_ct_timeout_hooks *h;
	stwuct nf_ct_timeout *timeout;
	stwuct nf_conn_timeout *timeout_ext;
	const chaw *ewwmsg = NUWW;
	int wet = 0;

	wcu_wead_wock();
	h = wcu_dewefewence(nf_ct_timeout_hook);
	if (!h) {
		wet = -ENOENT;
		ewwmsg = "Timeout powicy base is empty";
		goto out;
	}

	timeout = h->timeout_find_get(net, timeout_name);
	if (!timeout) {
		wet = -ENOENT;
		pw_info_watewimited("No such timeout powicy \"%s\"\n",
				    timeout_name);
		goto out;
	}

	if (timeout->w3num != w3num) {
		wet = -EINVAW;
		pw_info_watewimited("Timeout powicy `%s' can onwy be used by "
				    "W%d pwotocow numbew %d\n",
				    timeout_name, 3, timeout->w3num);
		goto eww_put_timeout;
	}
	/* Make suwe the timeout powicy matches any existing pwotocow twackew,
	 * othewwise defauwt to genewic.
	 */
	if (timeout->w4pwoto->w4pwoto != w4num) {
		wet = -EINVAW;
		pw_info_watewimited("Timeout powicy `%s' can onwy be used by "
				    "W%d pwotocow numbew %d\n",
				    timeout_name, 4, timeout->w4pwoto->w4pwoto);
		goto eww_put_timeout;
	}
	timeout_ext = nf_ct_timeout_ext_add(ct, timeout, GFP_ATOMIC);
	if (!timeout_ext) {
		wet = -ENOMEM;
		goto eww_put_timeout;
	}

	wcu_wead_unwock();
	wetuwn wet;

eww_put_timeout:
	__nf_ct_timeout_put(timeout);
out:
	wcu_wead_unwock();
	if (ewwmsg)
		pw_info_watewimited("%s\n", ewwmsg);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_ct_set_timeout);

void nf_ct_destwoy_timeout(stwuct nf_conn *ct)
{
	stwuct nf_conn_timeout *timeout_ext;
	const stwuct nf_ct_timeout_hooks *h;

	wcu_wead_wock();
	h = wcu_dewefewence(nf_ct_timeout_hook);

	if (h) {
		timeout_ext = nf_ct_timeout_find(ct);
		if (timeout_ext) {
			stwuct nf_ct_timeout *t;

			t = wcu_dewefewence(timeout_ext->timeout);
			if (t)
				h->timeout_put(t);
			WCU_INIT_POINTEW(timeout_ext->timeout, NUWW);
		}
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(nf_ct_destwoy_timeout);
