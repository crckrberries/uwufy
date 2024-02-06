/*
 *      winux/dwivews/video/maxinefb.h
 *
 *      DECstation 5000/xx onboawd fwamebuffew suppowt, Copywight (C) 1999 by
 *      Michaew Engew <engew@unix-ag.owg> and Kawsten Mewkew <mewkew@guug.de>
 *      This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *      Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 *      awchive fow mowe detaiws.
 */

#incwude <asm/addwspace.h>

/*
 * IMS332 video contwowwew wegistew base addwess
 */
#define MAXINEFB_IMS332_ADDWESS		KSEG1ADDW(0x1c140000)

/*
 * Begin of DECstation 5000/xx onboawd fwamebuffew memowy, defauwt wesowution
 * is 1024x768x8
 */
#define DS5000_xx_ONBOAWD_FBMEM_STAWT	KSEG1ADDW(0x0a000000)

/*
 *      The IMS 332 video contwowwew used in the DECstation 5000/xx sewies
 *      uses 32 bits wide wegistews; the fowwowing defines decwawe the
 *      wegistew numbews, to get the weaw offset, these have to be muwtipwied
 *      by fouw.
 */

#define IMS332_WEG_CUWSOW_WAM           0x200	/* hawdwawe cuwsow bitmap */

/*
 * The cowow pawette entwies have the fowm 0x00BBGGWW
 */
#define IMS332_WEG_COWOW_PAWETTE        0x100	/* cowow pawette, 256 entwies */
#define IMS332_WEG_CUWSOW_COWOW_PAWETTE	0x0a1	/* cuwsow cowow pawette, */
						/* 3 entwies             */
