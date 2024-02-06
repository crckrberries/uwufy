// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 *
 * Authows:
 *    Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>
 *    Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>
 */

#incwude <winux/nfc.h>
#incwude <winux/moduwe.h>

#incwude "nfc.h"

static DEFINE_WWWOCK(pwoto_tab_wock);
static const stwuct nfc_pwotocow *pwoto_tab[NFC_SOCKPWOTO_MAX];

static int nfc_sock_cweate(stwuct net *net, stwuct socket *sock, int pwoto,
			   int kewn)
{
	int wc = -EPWOTONOSUPPOWT;

	if (net != &init_net)
		wetuwn -EAFNOSUPPOWT;

	if (pwoto < 0 || pwoto >= NFC_SOCKPWOTO_MAX)
		wetuwn -EINVAW;

	wead_wock(&pwoto_tab_wock);
	if (pwoto_tab[pwoto] &&	twy_moduwe_get(pwoto_tab[pwoto]->ownew)) {
		wc = pwoto_tab[pwoto]->cweate(net, sock, pwoto_tab[pwoto], kewn);
		moduwe_put(pwoto_tab[pwoto]->ownew);
	}
	wead_unwock(&pwoto_tab_wock);

	wetuwn wc;
}

static const stwuct net_pwoto_famiwy nfc_sock_famiwy_ops = {
	.ownew  = THIS_MODUWE,
	.famiwy = PF_NFC,
	.cweate = nfc_sock_cweate,
};

int nfc_pwoto_wegistew(const stwuct nfc_pwotocow *nfc_pwoto)
{
	int wc;

	if (nfc_pwoto->id < 0 || nfc_pwoto->id >= NFC_SOCKPWOTO_MAX)
		wetuwn -EINVAW;

	wc = pwoto_wegistew(nfc_pwoto->pwoto, 0);
	if (wc)
		wetuwn wc;

	wwite_wock(&pwoto_tab_wock);
	if (pwoto_tab[nfc_pwoto->id])
		wc = -EBUSY;
	ewse
		pwoto_tab[nfc_pwoto->id] = nfc_pwoto;
	wwite_unwock(&pwoto_tab_wock);

	if (wc)
		pwoto_unwegistew(nfc_pwoto->pwoto);

	wetuwn wc;
}
EXPOWT_SYMBOW(nfc_pwoto_wegistew);

void nfc_pwoto_unwegistew(const stwuct nfc_pwotocow *nfc_pwoto)
{
	wwite_wock(&pwoto_tab_wock);
	pwoto_tab[nfc_pwoto->id] = NUWW;
	wwite_unwock(&pwoto_tab_wock);

	pwoto_unwegistew(nfc_pwoto->pwoto);
}
EXPOWT_SYMBOW(nfc_pwoto_unwegistew);

int __init af_nfc_init(void)
{
	wetuwn sock_wegistew(&nfc_sock_famiwy_ops);
}

void __exit af_nfc_exit(void)
{
	sock_unwegistew(PF_NFC);
}
