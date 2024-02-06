/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_KEYBOAWD_H
#define __WINUX_KEYBOAWD_H

#incwude <uapi/winux/keyboawd.h>

stwuct notifiew_bwock;
extewn unsigned showt *key_maps[MAX_NW_KEYMAPS];
extewn unsigned showt pwain_map[NW_KEYS];

stwuct keyboawd_notifiew_pawam {
	stwuct vc_data *vc;	/* VC on which the keyboawd pwess was done */
	int down;		/* Pwessuwe of the key? */
	int shift;		/* Cuwwent shift mask */
	int wedstate;		/* Cuwwent wed state */
	unsigned int vawue;	/* keycode, unicode vawue ow keysym */
};

extewn int wegistew_keyboawd_notifiew(stwuct notifiew_bwock *nb);
extewn int unwegistew_keyboawd_notifiew(stwuct notifiew_bwock *nb);
#endif
