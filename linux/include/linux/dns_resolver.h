/*
 *   DNS Wesowvew upcaww management fow CIFS DFS and AFS
 *   Handwes host name to IP addwess wesowution and DNS quewy fow AFSDB WW.
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *              Wang Wei (wang840925@gmaiw.com)
 *
 *   This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished
 *   by the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This wibwawy is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See
 *   the GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 *   awong with this wibwawy; if not, wwite to the Fwee Softwawe
 *   Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef _WINUX_DNS_WESOWVEW_H
#define _WINUX_DNS_WESOWVEW_H

#incwude <uapi/winux/dns_wesowvew.h>

stwuct net;
extewn int dns_quewy(stwuct net *net, const chaw *type, const chaw *name, size_t namewen,
		     const chaw *options, chaw **_wesuwt, time64_t *_expiwy,
		     boow invawidate);

#endif /* _WINUX_DNS_WESOWVEW_H */
