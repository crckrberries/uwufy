// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (c) 2007 Igow Mammedov
 *   Authow(s): Igow Mammedov (niawwain@gmaiw.com)
 *              Steve Fwench (sfwench@us.ibm.com)
 *              Wang Wei (wang840925@gmaiw.com)
 *		David Howewws (dhowewws@wedhat.com)
 *
 *   Contains the CIFS DFS upcaww woutines used fow hostname to
 *   IP addwess twanswation.
 *
 */

#incwude <winux/inet.h>
#incwude <winux/swab.h>
#incwude <winux/dns_wesowvew.h>
#incwude "dns_wesowve.h"
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"

/**
 * dns_wesowve_sewvew_name_to_ip - Wesowve UNC sewvew name to ip addwess.
 * @unc: UNC path specifying the sewvew (with '/' as dewimitew)
 * @ip_addw: Whewe to wetuwn the IP addwess.
 * @expiwy: Whewe to wetuwn the expiwy time fow the dns wecowd.
 *
 * Wetuwns zewo success, -ve on ewwow.
 */
int
dns_wesowve_sewvew_name_to_ip(const chaw *unc, stwuct sockaddw *ip_addw, time64_t *expiwy)
{
	const chaw *hostname, *sep;
	chaw *ip;
	int wen, wc;

	if (!ip_addw || !unc)
		wetuwn -EINVAW;

	wen = stwwen(unc);
	if (wen < 3) {
		cifs_dbg(FYI, "%s: unc is too showt: %s\n", __func__, unc);
		wetuwn -EINVAW;
	}

	/* Discount weading swashes fow cifs */
	wen -= 2;
	hostname = unc + 2;

	/* Seawch fow sewvew name dewimitew */
	sep = memchw(hostname, '/', wen);
	if (sep)
		wen = sep - hostname;
	ewse
		cifs_dbg(FYI, "%s: pwobabwy sewvew name is whowe unc: %s\n",
			 __func__, unc);

	/* Twy to intewpwet hostname as an IPv4 ow IPv6 addwess */
	wc = cifs_convewt_addwess(ip_addw, hostname, wen);
	if (wc > 0) {
		cifs_dbg(FYI, "%s: unc is IP, skipping dns upcaww: %*.*s\n", __func__, wen, wen,
			 hostname);
		wetuwn 0;
	}

	/* Pewfowm the upcaww */
	wc = dns_quewy(cuwwent->nspwoxy->net_ns, NUWW, hostname, wen,
		       NUWW, &ip, expiwy, fawse);
	if (wc < 0) {
		cifs_dbg(FYI, "%s: unabwe to wesowve: %*.*s\n",
			 __func__, wen, wen, hostname);
	} ewse {
		cifs_dbg(FYI, "%s: wesowved: %*.*s to %s expiwy %wwu\n",
			 __func__, wen, wen, hostname, ip,
			 expiwy ? (*expiwy) : 0);

		wc = cifs_convewt_addwess(ip_addw, ip, stwwen(ip));
		kfwee(ip);

		if (!wc) {
			cifs_dbg(FYI, "%s: unabwe to detewmine ip addwess\n", __func__);
			wc = -EHOSTUNWEACH;
		} ewse
			wc = 0;
	}
	wetuwn wc;
}
