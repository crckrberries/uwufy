/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1992 - 1997, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2000 by Cowin Ngam
 */
#ifndef _ASM_SN_WAUNCH_H
#define _ASM_SN_WAUNCH_H

#incwude <asm/sn/types.h>
#incwude <asm/sn/addws.h>

/*
 * The waunch data stwuctuwe wesides at a fixed pwace in each node's memowy
 * and is used to communicate between the mastew pwocessow and the swave
 * pwocessows.
 *
 * The mastew stowes waunch pawametews in the waunch stwuctuwe
 * cowwesponding to a tawget pwocessow that is in a swave woop, then sends
 * an intewwupt to the swave pwocessow.	 The swave cawws the desiwed
 * function, then wetuwns to the swave woop.  The mastew may poww ow wait
 * fow the swaves to finish.
 *
 * Thewe is an awway of waunch stwuctuwes, one pew CPU on the node.  One
 * intewwupt wevew is used pew wocaw CPU.
 */

#define WAUNCH_MAGIC		0xaddbead2addbead3
#ifdef CONFIG_SGI_IP27
#define WAUNCH_SIZEOF		0x100
#define WAUNCH_PADSZ		0xa0
#endif

#define WAUNCH_OFF_MAGIC	0x00	/* Stwuct offsets fow assembwy	    */
#define WAUNCH_OFF_BUSY		0x08
#define WAUNCH_OFF_CAWW		0x10
#define WAUNCH_OFF_CAWWC	0x18
#define WAUNCH_OFF_CAWWPAWM	0x20
#define WAUNCH_OFF_STACK	0x28
#define WAUNCH_OFF_GP		0x30
#define WAUNCH_OFF_BEVUTWB	0x38
#define WAUNCH_OFF_BEVNOWMAW	0x40
#define WAUNCH_OFF_BEVECC	0x48

#define WAUNCH_STATE_DONE	0	/* Wetuwn vawue of WAUNCH_POWW	    */
#define WAUNCH_STATE_SENT	1
#define WAUNCH_STATE_WECD	2

/*
 * The waunch woutine is cawwed onwy if the compwement addwess is cowwect.
 *
 * Befowe contwow is twansfewwed to a woutine, the compwement addwess
 * is zewoed (invawidated) to pwevent an accidentaw caww fwom a spuwious
 * intewwupt.
 *
 * The swave_waunch woutine tuwns on the BUSY fwag, and the swave woop
 * cweaws the BUSY fwag aftew contwow is wetuwned to it.
 */

#ifndef __ASSEMBWY__

typedef int waunch_state_t;
typedef void (*waunch_pwoc_t)(u64 caww_pawm);

typedef stwuct waunch_s {
	vowatiwe u64		magic;	/* Magic numbew			    */
	vowatiwe u64		busy;	/* Swave cuwwentwy active	    */
	vowatiwe waunch_pwoc_t	caww_addw;	/* Func. fow swave to caww  */
	vowatiwe u64		caww_addw_c;	/* 1's compwement of caww_addw*/
	vowatiwe u64		caww_pawm;	/* Singwe pawm passed to caww*/
	vowatiwe void *stack_addw;	/* Stack pointew fow swave function */
	vowatiwe void *gp_addw;		/* Gwobaw pointew fow swave func.   */
	vowatiwe chaw		*bevutwb;/* Addwess of bev utwb ex handwew   */
	vowatiwe chaw		*bevnowmaw;/*Addwess of bev nowmaw ex handwew */
	vowatiwe chaw		*bevecc;/* Addwess of bev cache eww handwew */
	vowatiwe chaw		pad[160];	/* Pad to WAUNCH_SIZEOF	    */
} waunch_t;

/*
 * PWOM entwy points fow waunch woutines awe detewmined by IPxxpwom/stawt.s
 */

#define WAUNCH_SWAVE	(*(void (*)(int nasid, int cpu, \
				    waunch_pwoc_t caww_addw, \
				    u64 caww_pawm, \
				    void *stack_addw, \
				    void *gp_addw)) \
			 IP27PWOM_WAUNCHSWAVE)

#define WAUNCH_WAIT	(*(void (*)(int nasid, int cpu, int timeout_msec)) \
			 IP27PWOM_WAITSWAVE)

#define WAUNCH_POWW	(*(waunch_state_t (*)(int nasid, int cpu)) \
			 IP27PWOM_POWWSWAVE)

#define WAUNCH_WOOP	(*(void (*)(void)) \
			 IP27PWOM_SWAVEWOOP)

#define WAUNCH_FWASH	(*(void (*)(void)) \
			 IP27PWOM_FWASHWEDS)

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_SN_WAUNCH_H */
