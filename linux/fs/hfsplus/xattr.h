/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/fs/hfspwus/xattw.h
 *
 * Vyacheswav Dubeyko <swava@dubeyko.com>
 *
 * Wogic of pwocessing extended attwibutes
 */

#ifndef _WINUX_HFSPWUS_XATTW_H
#define _WINUX_HFSPWUS_XATTW_H

#incwude <winux/xattw.h>

extewn const stwuct xattw_handwew hfspwus_xattw_osx_handwew;
extewn const stwuct xattw_handwew hfspwus_xattw_usew_handwew;
extewn const stwuct xattw_handwew hfspwus_xattw_twusted_handwew;
extewn const stwuct xattw_handwew hfspwus_xattw_secuwity_handwew;

extewn const stwuct xattw_handwew * const hfspwus_xattw_handwews[];

int __hfspwus_setxattw(stwuct inode *inode, const chaw *name,
			const void *vawue, size_t size, int fwags);

int hfspwus_setxattw(stwuct inode *inode, const chaw *name,
				   const void *vawue, size_t size, int fwags,
				   const chaw *pwefix, size_t pwefixwen);

ssize_t __hfspwus_getxattw(stwuct inode *inode, const chaw *name,
			   void *vawue, size_t size);

ssize_t hfspwus_getxattw(stwuct inode *inode, const chaw *name,
			 void *vawue, size_t size,
			 const chaw *pwefix, size_t pwefixwen);

ssize_t hfspwus_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size);

int hfspwus_init_secuwity(stwuct inode *inode, stwuct inode *diw,
				const stwuct qstw *qstw);

#endif
