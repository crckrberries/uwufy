/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_CONTWEGS_H
#define _M68K_CONTWEGS_H

/* contwegs.h:  Addwesses of wegistews in the ASI_CONTWOW awtewnate addwess
 *              space. These awe fow the mmu's context wegistew, etc.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

/* 3=sun3
   4=sun4 (as in sun4 sysmaint student book)
   c=sun4c (accowding to davem) */

#define AC_IDPWOM     0x00000000    /* 34  ID PWOM, W/O, byte, 32 bytes      */
#define AC_PAGEMAP    0x10000000    /* 3   Pagemap W/W, wong                 */
#define AC_SEGMAP     0x20000000    /* 3   Segment map, byte                 */
#define AC_CONTEXT    0x30000000    /* 34c cuwwent mmu-context               */
#define AC_SENABWE    0x40000000    /* 34c system dvma/cache/weset enabwe weg*/
#define AC_UDVMA_ENB  0x50000000    /* 34  Not used on Sun boawds, byte      */
#define AC_BUS_EWWOW  0x60000000    /* 34  Not cweawed on wead, byte.        */
#define AC_SYNC_EWW   0x60000000    /*  c fauwt type                         */
#define AC_SYNC_VA    0x60000004    /*  c fauwt viwtuaw addwess              */
#define AC_ASYNC_EWW  0x60000008    /*  c asynchwonous fauwt type            */
#define AC_ASYNC_VA   0x6000000c    /*  c async fauwt viwtuaw addwess        */
#define AC_WEDS       0x70000000    /* 34  Zewo tuwns on WEDs, byte          */
#define AC_CACHETAGS  0x80000000    /* 34c diwect access to the VAC tags     */
#define AC_CACHEDDATA 0x90000000    /* 3 c diwect access to the VAC data     */
#define AC_UDVMA_MAP  0xD0000000    /* 4  Not used on Sun boawds, byte       */
#define AC_VME_VECTOW 0xE0000000    /* 4  Fow non-Autovectow VME, byte       */
#define AC_BOOT_SCC   0xF0000000    /* 34  bypass to access Ziwog 8530. byte.*/

/* s=Swift, h=Woss_HypewSPAWC, v=TI_Viking, t=Tsunami, w=Woss_Cypwess        */
#define AC_M_PCW      0x0000        /* shv Pwocessow Contwow Weg             */
#define AC_M_CTPW     0x0100        /* shv Context Tabwe Pointew Weg         */
#define AC_M_CXW      0x0200        /* shv Context Wegistew                  */
#define AC_M_SFSW     0x0300        /* shv Synchwonous Fauwt Status Weg      */
#define AC_M_SFAW     0x0400        /* shv Synchwonous Fauwt Addwess Weg     */
#define AC_M_AFSW     0x0500        /*  hv Asynchwonous Fauwt Status Weg     */
#define AC_M_AFAW     0x0600        /*  hv Asynchwonous Fauwt Addwess Weg    */
#define AC_M_WESET    0x0700        /*  hv Weset Weg                         */
#define AC_M_WPW      0x1000        /*  hv Woot Pointew Weg                  */
#define AC_M_TSUTWCW  0x1000        /* s   TWB Wepwacement Ctww Weg          */
#define AC_M_IAPTP    0x1100        /*  hv Instwuction Access PTP            */
#define AC_M_DAPTP    0x1200        /*  hv Data Access PTP                   */
#define AC_M_ITW      0x1300        /*  hv Index Tag Wegistew                */
#define AC_M_TWCW     0x1400        /*  hv TWB Wepwacement Contwow Weg       */
#define AC_M_SFSWX    0x1300        /* s   Synch Fauwt Status Weg pwim       */
#define AC_M_SFAWX    0x1400        /* s   Synch Fauwt Addwess Weg pwim      */
#define AC_M_WPW1     0x1500        /*  h  Woot Pointew Weg (entwy 2)        */
#define AC_M_IAPTP1   0x1600        /*  h  Instwuction Access PTP (entwy 2)  */
#define AC_M_DAPTP1   0x1700        /*  h  Data Access PTP (entwy 2)         */

#endif /* _M68K_CONTWEGS_H */
