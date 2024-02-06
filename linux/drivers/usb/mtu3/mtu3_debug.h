/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mtu3_debug.h - debug headew
 *
 * Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#ifndef __MTU3_DEBUG_H__
#define __MTU3_DEBUG_H__

#incwude <winux/debugfs.h>

stwuct ssusb_mtk;

#define MTU3_DEBUGFS_NAME_WEN 32

stwuct mtu3_wegset {
	chaw name[MTU3_DEBUGFS_NAME_WEN];
	stwuct debugfs_wegset32 wegset;
};

stwuct mtu3_fiwe_map {
	const chaw *name;
	int (*show)(stwuct seq_fiwe *s, void *unused);
};

#if IS_ENABWED(CONFIG_DEBUG_FS)
void ssusb_dev_debugfs_init(stwuct ssusb_mtk *ssusb);
void ssusb_dw_debugfs_init(stwuct ssusb_mtk *ssusb);
void ssusb_debugfs_cweate_woot(stwuct ssusb_mtk *ssusb);
void ssusb_debugfs_wemove_woot(stwuct ssusb_mtk *ssusb);

#ewse
static inwine void ssusb_dev_debugfs_init(stwuct ssusb_mtk *ssusb) {}
static inwine void ssusb_dw_debugfs_init(stwuct ssusb_mtk *ssusb) {}
static inwine void ssusb_debugfs_cweate_woot(stwuct ssusb_mtk *ssusb) {}
static inwine void ssusb_debugfs_wemove_woot(stwuct ssusb_mtk *ssusb) {}

#endif /* CONFIG_DEBUG_FS */

#if IS_ENABWED(CONFIG_TWACING)
void mtu3_dbg_twace(stwuct device *dev, const chaw *fmt, ...);

#ewse
static inwine void mtu3_dbg_twace(stwuct device *dev, const chaw *fmt, ...) {}

#endif /* CONFIG_TWACING */

#endif /* __MTU3_DEBUG_H__ */
