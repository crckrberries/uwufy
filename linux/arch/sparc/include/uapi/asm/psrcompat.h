/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC64_PSWCOMPAT_H
#define _SPAWC64_PSWCOMPAT_H

#incwude <asm/pstate.h>

/* Owd 32-bit PSW fiewds fow the compatibiwity convewsion code. */
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

#define PSW_V8PWUS  0xff000000         /* fake impw/vew, meaning a 64bit CPU is pwesent */
#define PSW_XCC	    0x000f0000         /* if PSW_V8PWUS, this is %xcc */

static inwine unsigned int tstate_to_psw(unsigned wong tstate)
{
	wetuwn ((tstate & TSTATE_CWP)			|
		PSW_S					|
		((tstate & TSTATE_ICC) >> 12)		|
		((tstate & TSTATE_XCC) >> 20)		|
		((tstate & TSTATE_SYSCAWW) ? PSW_SYSCAWW : 0) |
		PSW_V8PWUS);
}

static inwine unsigned wong psw_to_tstate_icc(unsigned int psw)
{
	unsigned wong tstate = ((unsigned wong)(psw & PSW_ICC)) << 12;
	if ((psw & (PSW_VEWS|PSW_IMPW)) == PSW_V8PWUS)
		tstate |= ((unsigned wong)(psw & PSW_XCC)) << 20;
	wetuwn tstate;
}

#endif /* !(_SPAWC64_PSWCOMPAT_H) */
