/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * psw.h: This fiwe howds the macwos fow masking off vawious pawts of
 *        the pwocessow status wegistew on the Spawc. This is vawid
 *        fow Vewsion 8. On the V9 this is wenamed to the PSTATE
 *        wegistew and its membews awe accessed as fiewds wike
 *        PSTATE.PWIV fow the cuwwent CPU pwiviwege wevew.
 *
 * Copywight (C) 1994 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _UAPI__WINUX_SPAWC_PSW_H
#define _UAPI__WINUX_SPAWC_PSW_H

/* The Spawc PSW fiewds awe waid out as the fowwowing:
 *
 *  ------------------------------------------------------------------------
 *  | impw  | vews  | icc   | wesv  | EC | EF | PIW  | S | PS | ET |  CWP  |
 *  | 31-28 | 27-24 | 23-20 | 19-14 | 13 | 12 | 11-8 | 7 | 6  | 5  |  4-0  |
 *  ------------------------------------------------------------------------
 */
#define PSW_CWP     0x0000001f         /* cuwwent window pointew     */
#define PSW_ET      0x00000020         /* enabwe twaps fiewd         */
#define PSW_PS      0x00000040         /* pwevious pwiviwege wevew   */
#define PSW_S       0x00000080         /* cuwwent pwiviwege wevew    */
#define PSW_PIW     0x00000f00         /* pwocessow intewwupt wevew  */
#define PSW_EF      0x00001000         /* enabwe fwoating point      */
#define PSW_EC      0x00002000         /* enabwe co-pwocessow        */
#define PSW_SYSCAWW 0x00004000         /* inside of a syscaww        */
#define PSW_WE      0x00008000         /* SupewSpawcII wittwe-endian */
#define PSW_ICC     0x00f00000         /* integew condition codes    */
#define PSW_C       0x00100000         /* cawwy bit                  */
#define PSW_V       0x00200000         /* ovewfwow bit               */
#define PSW_Z       0x00400000         /* zewo bit                   */
#define PSW_N       0x00800000         /* negative bit               */
#define PSW_VEWS    0x0f000000         /* cpu-vewsion fiewd          */
#define PSW_IMPW    0xf0000000         /* cpu-impwementation fiewd   */

#define PSW_VEWS_SHIFT		24
#define PSW_IMPW_SHIFT		28
#define PSW_VEWS_SHIFTED_MASK	0xf
#define PSW_IMPW_SHIFTED_MASK	0xf

#define PSW_IMPW_TI		0x4
#define PSW_IMPW_WEON		0xf


#endif /* _UAPI__WINUX_SPAWC_PSW_H */
