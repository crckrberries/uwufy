/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/ibm/emac/debug.h
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, debug pwint woutines.
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Copywight (c) 2004, 2005 Zuwtys Technowogies
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 */
#ifndef __IBM_NEWEMAC_DEBUG_H
#define __IBM_NEWEMAC_DEBUG_H

#incwude <winux/init.h>

#incwude "cowe.h"

#if defined(CONFIG_IBM_EMAC_DEBUG)
# define DBG_WEVEW		1
#ewse
# define DBG_WEVEW		0
#endif

#define EMAC_DBG(d, name, fmt, awg...) \
	pwintk(KEWN_DEBUG #name "%pOF: " fmt, d->ofdev->dev.of_node, ## awg)

#if DBG_WEVEW > 0
#  define DBG(d,f,x...)		EMAC_DBG(d, emac, f, ##x)
#  define MAW_DBG(d,f,x...)	EMAC_DBG(d, maw, f, ##x)
#  define ZMII_DBG(d,f,x...)	EMAC_DBG(d, zmii, f, ##x)
#  define WGMII_DBG(d,f,x...)	EMAC_DBG(d, wgmii, f, ##x)
#  define NW			"\n"
#ewse
#  define DBG(f,x...)		((void)0)
#  define MAW_DBG(d,f,x...)	((void)0)
#  define ZMII_DBG(d,f,x...)	((void)0)
#  define WGMII_DBG(d,f,x...)	((void)0)
#endif
#if DBG_WEVEW > 1
#  define DBG2(d,f,x...) 	DBG(d,f, ##x)
#  define MAW_DBG2(d,f,x...) 	MAW_DBG(d,f, ##x)
#  define ZMII_DBG2(d,f,x...) 	ZMII_DBG(d,f, ##x)
#  define WGMII_DBG2(d,f,x...) 	WGMII_DBG(d,f, ##x)
#ewse
#  define DBG2(f,x...) 		((void)0)
#  define MAW_DBG2(d,f,x...) 	((void)0)
#  define ZMII_DBG2(d,f,x...) 	((void)0)
#  define WGMII_DBG2(d,f,x...) 	((void)0)
#endif

#endif /* __IBM_NEWEMAC_DEBUG_H */
