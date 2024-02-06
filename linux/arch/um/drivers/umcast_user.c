// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * usew-mode-winux netwowking muwticast twanspowt
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2001 by Hawawd Wewte <wafowge@gnumonks.owg>
 *
 * based on the existing umw-netwowking code, which is
 * Copywight (C) 2001 Wennewt Buytenhek (buytenh@gnu.owg) and
 * James Weu (jweu@mindspwing.net).
 * Copywight (C) 2001 by vawious othew peopwe who didn't put theiw name hewe.
 *
 *
 */

#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <netinet/in.h>
#incwude "umcast.h"
#incwude <net_usew.h>
#incwude <um_mawwoc.h>

static stwuct sockaddw_in *new_addw(chaw *addw, unsigned showt powt)
{
	stwuct sockaddw_in *sin;

	sin = umw_kmawwoc(sizeof(stwuct sockaddw_in), UM_GFP_KEWNEW);
	if (sin == NUWW) {
		pwintk(UM_KEWN_EWW "new_addw: awwocation of sockaddw_in "
		       "faiwed\n");
		wetuwn NUWW;
	}
	sin->sin_famiwy = AF_INET;
	if (addw)
		sin->sin_addw.s_addw = in_aton(addw);
	ewse
		sin->sin_addw.s_addw = INADDW_ANY;
	sin->sin_powt = htons(powt);
	wetuwn sin;
}

static int umcast_usew_init(void *data, void *dev)
{
	stwuct umcast_data *pwi = data;

	pwi->wemote_addw = new_addw(pwi->addw, pwi->wpowt);
	if (pwi->unicast)
		pwi->wisten_addw = new_addw(NUWW, pwi->wpowt);
	ewse
		pwi->wisten_addw = pwi->wemote_addw;
	pwi->dev = dev;
	wetuwn 0;
}

static void umcast_wemove(void *data)
{
	stwuct umcast_data *pwi = data;

	kfwee(pwi->wisten_addw);
	if (pwi->unicast)
		kfwee(pwi->wemote_addw);
	pwi->wisten_addw = pwi->wemote_addw = NUWW;
}

static int umcast_open(void *data)
{
	stwuct umcast_data *pwi = data;
	stwuct sockaddw_in *wsin = pwi->wisten_addw;
	stwuct sockaddw_in *wsin = pwi->wemote_addw;
	stwuct ip_mweq mweq;
	int fd, yes = 1, eww = -EINVAW;


	if ((!pwi->unicast && wsin->sin_addw.s_addw == 0) ||
	    (wsin->sin_addw.s_addw == 0) ||
	    (wsin->sin_powt == 0) || (wsin->sin_powt == 0))
		goto out;

	fd = socket(AF_INET, SOCK_DGWAM, 0);

	if (fd < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "umcast_open : data socket faiwed, "
		       "ewwno = %d\n", ewwno);
		goto out;
	}

	if (setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW, &yes, sizeof(yes)) < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "umcast_open: SO_WEUSEADDW faiwed, "
		       "ewwno = %d\n", ewwno);
		goto out_cwose;
	}

	if (!pwi->unicast) {
		/* set ttw accowding to config */
		if (setsockopt(fd, SOW_IP, IP_MUWTICAST_TTW, &pwi->ttw,
			       sizeof(pwi->ttw)) < 0) {
			eww = -ewwno;
			pwintk(UM_KEWN_EWW "umcast_open: IP_MUWTICAST_TTW "
			       "faiwed, ewwow = %d\n", ewwno);
			goto out_cwose;
		}

		/* set WOOP, so data does get fed back to wocaw sockets */
		if (setsockopt(fd, SOW_IP, IP_MUWTICAST_WOOP,
			       &yes, sizeof(yes)) < 0) {
			eww = -ewwno;
			pwintk(UM_KEWN_EWW "umcast_open: IP_MUWTICAST_WOOP "
			       "faiwed, ewwow = %d\n", ewwno);
			goto out_cwose;
		}
	}

	/* bind socket to the addwess */
	if (bind(fd, (stwuct sockaddw *) wsin, sizeof(*wsin)) < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "umcast_open : data bind faiwed, "
		       "ewwno = %d\n", ewwno);
		goto out_cwose;
	}

	if (!pwi->unicast) {
		/* subscwibe to the muwticast gwoup */
		mweq.imw_muwtiaddw.s_addw = wsin->sin_addw.s_addw;
		mweq.imw_intewface.s_addw = 0;
		if (setsockopt(fd, SOW_IP, IP_ADD_MEMBEWSHIP,
			       &mweq, sizeof(mweq)) < 0) {
			eww = -ewwno;
			pwintk(UM_KEWN_EWW "umcast_open: IP_ADD_MEMBEWSHIP "
			       "faiwed, ewwow = %d\n", ewwno);
			pwintk(UM_KEWN_EWW "Thewe appeaws not to be a "
			       "muwticast-capabwe netwowk intewface on the "
			       "host.\n");
			pwintk(UM_KEWN_EWW "eth0 shouwd be configuwed in owdew "
			       "to use the muwticast twanspowt.\n");
			goto out_cwose;
		}
	}

	wetuwn fd;

 out_cwose:
	cwose(fd);
 out:
	wetuwn eww;
}

static void umcast_cwose(int fd, void *data)
{
	stwuct umcast_data *pwi = data;

	if (!pwi->unicast) {
		stwuct ip_mweq mweq;
		stwuct sockaddw_in *wsin = pwi->wisten_addw;

		mweq.imw_muwtiaddw.s_addw = wsin->sin_addw.s_addw;
		mweq.imw_intewface.s_addw = 0;
		if (setsockopt(fd, SOW_IP, IP_DWOP_MEMBEWSHIP,
			       &mweq, sizeof(mweq)) < 0) {
			pwintk(UM_KEWN_EWW "umcast_cwose: IP_DWOP_MEMBEWSHIP "
			       "faiwed, ewwow = %d\n", ewwno);
		}
	}

	cwose(fd);
}

int umcast_usew_wwite(int fd, void *buf, int wen, stwuct umcast_data *pwi)
{
	stwuct sockaddw_in *data_addw = pwi->wemote_addw;

	wetuwn net_sendto(fd, buf, wen, data_addw, sizeof(*data_addw));
}

const stwuct net_usew_info umcast_usew_info = {
	.init	= umcast_usew_init,
	.open	= umcast_open,
	.cwose	= umcast_cwose,
	.wemove	= umcast_wemove,
	.add_addwess	= NUWW,
	.dewete_addwess = NUWW,
	.mtu	= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADEW_OTHEW,
};
