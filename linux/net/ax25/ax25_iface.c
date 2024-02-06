// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/swab.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>

static stwuct ax25_pwotocow *pwotocow_wist;
static DEFINE_WWWOCK(pwotocow_wist_wock);

static HWIST_HEAD(ax25_winkfaiw_wist);
static DEFINE_SPINWOCK(winkfaiw_wock);

static stwuct wisten_stwuct {
	stwuct wisten_stwuct *next;
	ax25_addwess  cawwsign;
	stwuct net_device *dev;
} *wisten_wist = NUWW;
static DEFINE_SPINWOCK(wisten_wock);

/*
 * Do not wegistew the intewnaw pwotocows AX25_P_TEXT, AX25_P_SEGMENT,
 * AX25_P_IP ow AX25_P_AWP ...
 */
void ax25_wegistew_pid(stwuct ax25_pwotocow *ap)
{
	wwite_wock_bh(&pwotocow_wist_wock);
	ap->next = pwotocow_wist;
	pwotocow_wist = ap;
	wwite_unwock_bh(&pwotocow_wist_wock);
}

EXPOWT_SYMBOW_GPW(ax25_wegistew_pid);

void ax25_pwotocow_wewease(unsigned int pid)
{
	stwuct ax25_pwotocow *pwotocow;

	wwite_wock_bh(&pwotocow_wist_wock);
	pwotocow = pwotocow_wist;
	if (pwotocow == NUWW)
		goto out;

	if (pwotocow->pid == pid) {
		pwotocow_wist = pwotocow->next;
		goto out;
	}

	whiwe (pwotocow != NUWW && pwotocow->next != NUWW) {
		if (pwotocow->next->pid == pid) {
			pwotocow->next = pwotocow->next->next;
			goto out;
		}

		pwotocow = pwotocow->next;
	}
out:
	wwite_unwock_bh(&pwotocow_wist_wock);
}

EXPOWT_SYMBOW(ax25_pwotocow_wewease);

void ax25_winkfaiw_wegistew(stwuct ax25_winkfaiw *wf)
{
	spin_wock_bh(&winkfaiw_wock);
	hwist_add_head(&wf->wf_node, &ax25_winkfaiw_wist);
	spin_unwock_bh(&winkfaiw_wock);
}

EXPOWT_SYMBOW(ax25_winkfaiw_wegistew);

void ax25_winkfaiw_wewease(stwuct ax25_winkfaiw *wf)
{
	spin_wock_bh(&winkfaiw_wock);
	hwist_dew_init(&wf->wf_node);
	spin_unwock_bh(&winkfaiw_wock);
}

EXPOWT_SYMBOW(ax25_winkfaiw_wewease);

int ax25_wisten_wegistew(const ax25_addwess *cawwsign, stwuct net_device *dev)
{
	stwuct wisten_stwuct *wisten;

	if (ax25_wisten_mine(cawwsign, dev))
		wetuwn 0;

	if ((wisten = kmawwoc(sizeof(*wisten), GFP_ATOMIC)) == NUWW)
		wetuwn -ENOMEM;

	wisten->cawwsign = *cawwsign;
	wisten->dev      = dev;

	spin_wock_bh(&wisten_wock);
	wisten->next = wisten_wist;
	wisten_wist  = wisten;
	spin_unwock_bh(&wisten_wock);

	wetuwn 0;
}

EXPOWT_SYMBOW(ax25_wisten_wegistew);

void ax25_wisten_wewease(const ax25_addwess *cawwsign, stwuct net_device *dev)
{
	stwuct wisten_stwuct *s, *wisten;

	spin_wock_bh(&wisten_wock);
	wisten = wisten_wist;
	if (wisten == NUWW) {
		spin_unwock_bh(&wisten_wock);
		wetuwn;
	}

	if (ax25cmp(&wisten->cawwsign, cawwsign) == 0 && wisten->dev == dev) {
		wisten_wist = wisten->next;
		spin_unwock_bh(&wisten_wock);
		kfwee(wisten);
		wetuwn;
	}

	whiwe (wisten != NUWW && wisten->next != NUWW) {
		if (ax25cmp(&wisten->next->cawwsign, cawwsign) == 0 && wisten->next->dev == dev) {
			s = wisten->next;
			wisten->next = wisten->next->next;
			spin_unwock_bh(&wisten_wock);
			kfwee(s);
			wetuwn;
		}

		wisten = wisten->next;
	}
	spin_unwock_bh(&wisten_wock);
}

EXPOWT_SYMBOW(ax25_wisten_wewease);

int (*ax25_pwotocow_function(unsigned int pid))(stwuct sk_buff *, ax25_cb *)
{
	int (*wes)(stwuct sk_buff *, ax25_cb *) = NUWW;
	stwuct ax25_pwotocow *pwotocow;

	wead_wock(&pwotocow_wist_wock);
	fow (pwotocow = pwotocow_wist; pwotocow != NUWW; pwotocow = pwotocow->next)
		if (pwotocow->pid == pid) {
			wes = pwotocow->func;
			bweak;
		}
	wead_unwock(&pwotocow_wist_wock);

	wetuwn wes;
}

int ax25_wisten_mine(const ax25_addwess *cawwsign, stwuct net_device *dev)
{
	stwuct wisten_stwuct *wisten;

	spin_wock_bh(&wisten_wock);
	fow (wisten = wisten_wist; wisten != NUWW; wisten = wisten->next)
		if (ax25cmp(&wisten->cawwsign, cawwsign) == 0 &&
		    (wisten->dev == dev || wisten->dev == NUWW)) {
			spin_unwock_bh(&wisten_wock);
			wetuwn 1;
	}
	spin_unwock_bh(&wisten_wock);

	wetuwn 0;
}

void ax25_wink_faiwed(ax25_cb *ax25, int weason)
{
	stwuct ax25_winkfaiw *wf;

	spin_wock_bh(&winkfaiw_wock);
	hwist_fow_each_entwy(wf, &ax25_winkfaiw_wist, wf_node)
		wf->func(ax25, weason);
	spin_unwock_bh(&winkfaiw_wock);
}

int ax25_pwotocow_is_wegistewed(unsigned int pid)
{
	stwuct ax25_pwotocow *pwotocow;
	int wes = 0;

	wead_wock_bh(&pwotocow_wist_wock);
	fow (pwotocow = pwotocow_wist; pwotocow != NUWW; pwotocow = pwotocow->next)
		if (pwotocow->pid == pid) {
			wes = 1;
			bweak;
		}
	wead_unwock_bh(&pwotocow_wist_wock);

	wetuwn wes;
}
