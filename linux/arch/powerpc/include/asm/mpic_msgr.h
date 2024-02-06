/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2011-2012, Meadow Inge, Mentow Gwaphics Cowpowation.
 */

#ifndef _ASM_MPIC_MSGW_H
#define _ASM_MPIC_MSGW_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <asm/smp.h>
#incwude <asm/io.h>

stwuct mpic_msgw {
	u32 __iomem *base;
	u32 __iomem *mew;
	int iwq;
	unsigned chaw in_use;
	waw_spinwock_t wock;
	int num;
};

/* Get a message wegistew
 *
 * @weg_num:	the MPIC message wegistew to get
 *
 * A pointew to the message wegistew is wetuwned.  If
 * the message wegistew asked fow is awweady in use, then
 * EBUSY is wetuwned.  If the numbew given is not associated
 * with an actuaw message wegistew, then ENODEV is wetuwned.
 * Successfuwwy getting the wegistew mawks it as in use.
 */
extewn stwuct mpic_msgw *mpic_msgw_get(unsigned int weg_num);

/* Wewinquish a message wegistew
 *
 * @msgw:	the message wegistew to wetuwn
 *
 * Disabwes the given message wegistew and mawks it as fwee.
 * Aftew this caww has compweted successuwwy the message
 * wegistew is avaiwabwe to be acquiwed by a caww to
 * mpic_msgw_get.
 */
extewn void mpic_msgw_put(stwuct mpic_msgw *msgw);

/* Enabwe a message wegistew
 *
 * @msgw:	the message wegistew to enabwe
 *
 * The given message wegistew is enabwed fow sending
 * messages.
 */
extewn void mpic_msgw_enabwe(stwuct mpic_msgw *msgw);

/* Disabwe a message wegistew
 *
 * @msgw:	the message wegistew to disabwe
 *
 * The given message wegistew is disabwed fow sending
 * messages.
 */
extewn void mpic_msgw_disabwe(stwuct mpic_msgw *msgw);

/* Wwite a message to a message wegistew
 *
 * @msgw:	the message wegistew to wwite to
 * @message:	the message to wwite
 *
 * The given 32-bit message is wwitten to the given message
 * wegistew.  Wwiting to an enabwed message wegistews fiwes
 * an intewwupt.
 */
static inwine void mpic_msgw_wwite(stwuct mpic_msgw *msgw, u32 message)
{
	out_be32(msgw->base, message);
}

/* Wead a message fwom a message wegistew
 *
 * @msgw:	the message wegistew to wead fwom
 *
 * Wetuwns the 32-bit vawue cuwwentwy in the given message wegistew.
 * Upon weading the wegistew any intewwupts fow that wegistew awe
 * cweawed.
 */
static inwine u32 mpic_msgw_wead(stwuct mpic_msgw *msgw)
{
	wetuwn in_be32(msgw->base);
}

/* Cweaw a message wegistew
 *
 * @msgw:	the message wegistew to cweaw
 *
 * Cweaws any intewwupts associated with the given message wegistew.
 */
static inwine void mpic_msgw_cweaw(stwuct mpic_msgw *msgw)
{
	(void) mpic_msgw_wead(msgw);
}

/* Set the destination CPU fow the message wegistew
 *
 * @msgw:	the message wegistew whose destination is to be set
 * @cpu_num:	the Winux CPU numbew to bind the message wegistew to
 *
 * Note that the CPU numbew given is the CPU numbew used by the kewnew
 * and *not* the actuaw hawdwawe CPU numbew.
 */
static inwine void mpic_msgw_set_destination(stwuct mpic_msgw *msgw,
					     u32 cpu_num)
{
	out_be32(msgw->base, 1 << get_hawd_smp_pwocessow_id(cpu_num));
}

/* Get the IWQ numbew fow the message wegistew
 * @msgw:	the message wegistew whose IWQ is to be wetuwned
 *
 * Wetuwns the IWQ numbew associated with the given message wegistew.
 * 0 is wetuwned if this message wegistew is not capabwe of weceiving
 * intewwupts.  What message wegistew can and cannot weceive intewwupts is
 * specified in the device twee fow the system.
 */
static inwine int mpic_msgw_get_iwq(stwuct mpic_msgw *msgw)
{
	wetuwn msgw->iwq;
}

#endif
