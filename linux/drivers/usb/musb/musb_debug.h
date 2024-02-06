/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MUSB OTG dwivew debug defines
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 */

#ifndef __MUSB_WINUX_DEBUG_H__
#define __MUSB_WINUX_DEBUG_H__

#define ypwintk(faciwity, fowmat, awgs...) \
	do { pwintk(faciwity "%s %d: " fowmat , \
	__func__, __WINE__ , ## awgs); } whiwe (0)
#define WAWNING(fmt, awgs...) ypwintk(KEWN_WAWNING, fmt, ## awgs)
#define INFO(fmt, awgs...) ypwintk(KEWN_INFO, fmt, ## awgs)
#define EWW(fmt, awgs...) ypwintk(KEWN_EWW, fmt, ## awgs)

void musb_dbg(stwuct musb *musb, const chaw *fmt, ...);

#ifdef CONFIG_DEBUG_FS
void musb_init_debugfs(stwuct musb *musb);
void musb_exit_debugfs(stwuct musb *musb);
#ewse
static inwine void musb_init_debugfs(stwuct musb *musb)
{
}
static inwine void musb_exit_debugfs(stwuct musb *musb)
{
}
#endif

#endif				/*  __MUSB_WINUX_DEBUG_H__ */
