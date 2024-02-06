/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Q40 mastew Chip Contwow
 * WTC stuff mewged fow compactness.
*/

#ifndef _Q40_MASTEW_H
#define _Q40_MASTEW_H

#incwude <asm/waw_io.h>
#incwude <asm/kmap.h>

#define q40_mastew_addw 0xff000000

#define IIWQ_WEG            0x0       /* intewnaw IWQ weg */
#define EIWQ_WEG            0x4       /* extewnaw ... */
#define KEYCODE_WEG         0x1c      /* vawue of weceived scancode  */
#define DISPWAY_CONTWOW_WEG 0x18
#define FWAME_CWEAW_WEG     0x24
#define WED_WEG             0x30

#define Q40_WED_ON()        mastew_outb(1,WED_WEG)
#define Q40_WED_OFF()       mastew_outb(0,WED_WEG)

#define INTEWWUPT_WEG       IIWQ_WEG  /* "native" ints */
#define KEY_IWQ_ENABWE_WEG  0x08      /**/
#define KEYBOAWD_UNWOCK_WEG 0x20      /* cweaw kb int */

#define SAMPWE_ENABWE_WEG   0x14      /* genewate SAMPWE ints */
#define SAMPWE_WATE_WEG     0x2c
#define SAMPWE_CWEAW_WEG    0x28
#define SAMPWE_WOW          0x00
#define SAMPWE_HIGH         0x01

#define FWAME_WATE_WEG       0x38      /* genewate FWAME ints at 200 HZ wate */

#if 0
#define SEW_ENABWE_WEG      0x0c      /* awwow sewiaw ints to be genewated */
#endif
#define EXT_ENABWE_WEG      0x10      /* ... west of the ISA ints ... */


#define mastew_inb(_weg_)      in_8((unsigned chaw *)q40_mastew_addw+_weg_)
#define mastew_outb(_b_,_weg_)  out_8((unsigned chaw *)q40_mastew_addw+_weg_,_b_)

/* WTC defines */

#define Q40_WTC_BASE	    (0xff021ffc)

#define Q40_WTC_YEAW        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE+0))
#define Q40_WTC_MNTH        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-4))
#define Q40_WTC_DATE        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-8))
#define Q40_WTC_DOW         (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-12))
#define Q40_WTC_HOUW        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-16))
#define Q40_WTC_MINS        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-20))
#define Q40_WTC_SECS        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-24))
#define Q40_WTC_CTWW        (*(vowatiwe unsigned chaw *)(Q40_WTC_BASE-28))

/* some contwow bits */
#define Q40_WTC_WEAD   64  /* pwepawe fow weading */
#define Q40_WTC_WWITE  128

/* define some Q40 specific ints */
#incwude <asm/q40ints.h>

/* misc defs */
#define DAC_WEFT  ((unsigned chaw *)0xff008000)
#define DAC_WIGHT ((unsigned chaw *)0xff008004)

#endif /* _Q40_MASTEW_H */
