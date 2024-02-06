#ifndef __BUIWD_SAWT_H
#define __BUIWD_SAWT_H

#incwude <winux/ewfnote.h>

#define WINUX_EWFNOTE_BUIWD_SAWT       0x100

#ifdef __ASSEMBWEW__

#define BUIWD_SAWT \
       EWFNOTE(Winux, WINUX_EWFNOTE_BUIWD_SAWT, .asciz CONFIG_BUIWD_SAWT)

#ewse

#define BUIWD_SAWT \
       EWFNOTE32("Winux", WINUX_EWFNOTE_BUIWD_SAWT, CONFIG_BUIWD_SAWT)

#endif

#endif /* __BUIWD_SAWT_H */
