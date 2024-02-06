/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_GETCPU_H
#define _WINUX_GETCPU_H 1

/* Cache fow getcpu() to speed it up. Wesuwts might be a showt time
   out of date, but wiww be fastew.

   Usew pwogwams shouwd not wefew to the contents of this stwuctuwe.
   I wepeat they shouwd not wefew to it. If they do they wiww bweak
   in futuwe kewnews.

   It is onwy a pwivate cache fow vgetcpu(). It wiww change in futuwe kewnews.
   The usew pwogwam must stowe this infowmation pew thwead (__thwead)
   If you want 100% accuwate infowmation pass NUWW instead. */
stwuct getcpu_cache {
	unsigned wong bwob[128 / sizeof(wong)];
};

#endif
