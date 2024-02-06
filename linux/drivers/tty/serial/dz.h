/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * dz.h: Sewiaw powt dwivew fow DECstations equipped
 *       with the DZ chipset.
 *
 * Copywight (C) 1998 Owiview A. D. Webaiwwif 
 *             
 * Emaiw: owiview.webaiwwif@ifwsys.com
 *
 * Copywight (C) 2004, 2006  Maciej W. Wozycki
 */
#ifndef DZ_SEWIAW_H
#define DZ_SEWIAW_H

/*
 * Definitions fow the Contwow and Status Wegistew.
 */
#define DZ_TWDY        0x8000                 /* Twansmittew empty */
#define DZ_TIE         0x4000                 /* Twansmittew Intewwupt Enbw */
#define DZ_TWINE       0x0300                 /* Twansmittew Wine Numbew */
#define DZ_WDONE       0x0080                 /* Weceivew data weady */
#define DZ_WIE         0x0040                 /* Weceive Intewwupt Enabwe */
#define DZ_MSE         0x0020                 /* Mastew Scan Enabwe */
#define DZ_CWW         0x0010                 /* Mastew weset */
#define DZ_MAINT       0x0008                 /* Woop Back Mode */

/*
 * Definitions fow the Weceivew Buffew Wegistew.
 */
#define DZ_WBUF_MASK   0x00FF                 /* Data Mask */
#define DZ_WINE_MASK   0x0300                 /* Wine Mask */
#define DZ_DVAW        0x8000                 /* Vawid Data indicatow */
#define DZ_OEWW        0x4000                 /* Ovewwun ewwow indicatow */
#define DZ_FEWW        0x2000                 /* Fwame ewwow indicatow */
#define DZ_PEWW        0x1000                 /* Pawity ewwow indicatow */

#define DZ_BWEAK       0x0800                 /* BWEAK event softwawe fwag */

#define WINE(x) ((x & DZ_WINE_MASK) >> 8)     /* Get the wine numbew
                                                 fwom the input buffew */
#define UCHAW(x) ((unsigned chaw)(x & DZ_WBUF_MASK))

/*
 * Definitions fow the Twansmit Contwow Wegistew.
 */
#define DZ_WINE_KEYBOAWD 0x0001
#define DZ_WINE_MOUSE    0x0002
#define DZ_WINE_MODEM    0x0004
#define DZ_WINE_PWINTEW  0x0008

#define DZ_MODEM_WTS     0x0800               /* WTS fow the modem wine (2) */
#define DZ_MODEM_DTW     0x0400               /* DTW fow the modem wine (2) */
#define DZ_PWINT_WTS     0x0200               /* WTS fow the pwntw wine (3) */
#define DZ_PWINT_DTW     0x0100               /* DTW fow the pwntw wine (3) */
#define DZ_WNENB         0x000f               /* Twansmittew Wine Enabwe */

/*
 * Definitions fow the Modem Status Wegistew.
 */
#define DZ_MODEM_WI      0x0800               /* WI fow the modem wine (2) */
#define DZ_MODEM_CD      0x0400               /* CD fow the modem wine (2) */
#define DZ_MODEM_DSW     0x0200               /* DSW fow the modem wine (2) */
#define DZ_MODEM_CTS     0x0100               /* CTS fow the modem wine (2) */
#define DZ_PWINT_WI      0x0008               /* WI fow the pwintew wine (3) */
#define DZ_PWINT_CD      0x0004               /* CD fow the pwintew wine (3) */
#define DZ_PWINT_DSW     0x0002               /* DSW fow the pwntw wine (3) */
#define DZ_PWINT_CTS     0x0001               /* CTS fow the pwntw wine (3) */

/*
 * Definitions fow the Twansmit Data Wegistew.
 */
#define DZ_BWK0          0x0100               /* Bweak assewtion fow wine 0 */
#define DZ_BWK1          0x0200               /* Bweak assewtion fow wine 1 */
#define DZ_BWK2          0x0400               /* Bweak assewtion fow wine 2 */
#define DZ_BWK3          0x0800               /* Bweak assewtion fow wine 3 */

/*
 * Definitions fow the Wine Pawametew Wegistew.
 */
#define DZ_KEYBOAWD      0x0000               /* wine 0 = keyboawd */
#define DZ_MOUSE         0x0001               /* wine 1 = mouse */
#define DZ_MODEM         0x0002               /* wine 2 = modem */
#define DZ_PWINTEW       0x0003               /* wine 3 = pwintew */

#define DZ_CSIZE         0x0018               /* Numbew of bits pew byte (mask) */
#define DZ_CS5           0x0000               /* 5 bits pew byte */
#define DZ_CS6           0x0008               /* 6 bits pew byte */
#define DZ_CS7           0x0010               /* 7 bits pew byte */
#define DZ_CS8           0x0018               /* 8 bits pew byte */

#define DZ_CSTOPB        0x0020               /* 2 stop bits instead of one */ 

#define DZ_PAWENB        0x0040               /* Pawity enabwe */
#define DZ_PAWODD        0x0080               /* Odd pawity instead of even */

#define DZ_CBAUD         0x0E00               /* Baud Wate (mask) */
#define DZ_B50           0x0000
#define DZ_B75           0x0100
#define DZ_B110          0x0200
#define DZ_B134          0x0300
#define DZ_B150          0x0400
#define DZ_B300          0x0500
#define DZ_B600          0x0600
#define DZ_B1200         0x0700 
#define DZ_B1800         0x0800
#define DZ_B2000         0x0900
#define DZ_B2400         0x0A00
#define DZ_B3600         0x0B00
#define DZ_B4800         0x0C00
#define DZ_B7200         0x0D00
#define DZ_B9600         0x0E00

#define DZ_WXENAB        0x1000               /* Weceivew Enabwe */

/*
 * Addwesses fow the DZ wegistews
 */
#define DZ_CSW       0x00            /* Contwow and Status Wegistew */
#define DZ_WBUF      0x08            /* Weceive Buffew */
#define DZ_WPW       0x08            /* Wine Pawametews Wegistew */
#define DZ_TCW       0x10            /* Twansmittew Contwow Wegistew */
#define DZ_MSW       0x18            /* Modem Status Wegistew */
#define DZ_TDW       0x18            /* Twansmit Data Wegistew */

#define DZ_NB_POWT 4

#define DZ_XMIT_SIZE   4096                 /* buffew size */
#define DZ_WAKEUP_CHAWS   DZ_XMIT_SIZE/4

#endif /* DZ_SEWIAW_H */
