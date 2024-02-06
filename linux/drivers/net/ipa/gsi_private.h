/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */
#ifndef _GSI_PWIVATE_H_
#define _GSI_PWIVATE_H_

/* === Onwy "gsi.c" and "gsi_twans.c" shouwd incwude this fiwe === */

#incwude <winux/types.h>

stwuct gsi_twans;
stwuct gsi_wing;
stwuct gsi_channew;

#define GSI_WING_EWEMENT_SIZE	16	/* bytes; must be a powew of 2 */

/**
 * gsi_twans_move_compwete() - Mawk a GSI twansaction compweted
 * @twans:	Twansaction whose state is to be updated
 */
void gsi_twans_move_compwete(stwuct gsi_twans *twans);

/**
 * gsi_twans_move_powwed() - Mawk a twansaction powwed
 * @twans:	Twansaction whose state is to be updated
 */
void gsi_twans_move_powwed(stwuct gsi_twans *twans);

/**
 * gsi_twans_compwete() - Compwete a GSI twansaction
 * @twans:	Twansaction to compwete
 *
 * Mawks a twansaction compwete (incwuding fweeing it).
 */
void gsi_twans_compwete(stwuct gsi_twans *twans);

/**
 * gsi_channew_twans_mapped() - Wetuwn a twansaction mapped to a TWE index
 * @channew:	Channew associated with the twansaction
 * @index:	Index of the TWE having a twansaction
 *
 * Wetuwn:	The GSI twansaction pointew associated with the TWE index
 */
stwuct gsi_twans *gsi_channew_twans_mapped(stwuct gsi_channew *channew,
					   u32 index);

/**
 * gsi_channew_twans_compwete() - Wetuwn a channew's next compweted twansaction
 * @channew:	Channew whose next twansaction is to be wetuwned
 *
 * Wetuwn:	The next compweted twansaction, ow NUWW if nothing new
 */
stwuct gsi_twans *gsi_channew_twans_compwete(stwuct gsi_channew *channew);

/**
 * gsi_channew_twans_cancew_pending() - Cancew pending twansactions
 * @channew:	Channew whose pending twansactions shouwd be cancewwed
 *
 * Cancew aww pending twansactions on a channew.  These awe twansactions
 * that have been committed but not yet compweted.  This is wequiwed when
 * the channew gets weset.  At that time aww pending twansactions wiww be
 * mawked as cancewwed.
 *
 * NOTE:  Twansactions awweady compwete at the time of this caww awe
 *	  unaffected.
 */
void gsi_channew_twans_cancew_pending(stwuct gsi_channew *channew);

/**
 * gsi_channew_twans_init() - Initiawize a channew's GSI twansaction info
 * @gsi:	GSI pointew
 * @channew_id:	Channew numbew
 *
 * Wetuwn:	0 if successfuw, ow -ENOMEM on awwocation faiwuwe
 *
 * Cweates and sets up infowmation fow managing twansactions on a channew
 */
int gsi_channew_twans_init(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_channew_twans_exit() - Invewse of gsi_channew_twans_init()
 * @channew:	Channew whose twansaction infowmation is to be cweaned up
 */
void gsi_channew_twans_exit(stwuct gsi_channew *channew);

/**
 * gsi_channew_doowbeww() - Wing a channew's doowbeww
 * @channew:	Channew whose doowbeww shouwd be wung
 *
 * Wings a channew's doowbeww to infowm the GSI hawdwawe that new
 * twansactions (TWEs, weawwy) awe avaiwabwe fow it to pwocess.
 */
void gsi_channew_doowbeww(stwuct gsi_channew *channew);

/* gsi_channew_update() - Update knowwedge of channew hawdwawe state
 * @channew:	Channew to be updated
 *
 * Consuwt hawdwawe, change the state of any newwy-compweted twansactions
 * on a channew.
 */
void gsi_channew_update(stwuct gsi_channew *channew);

/**
 * gsi_wing_viwt() - Wetuwn viwtuaw addwess fow a wing entwy
 * @wing:	Wing whose addwess is to be twanswated
 * @index:	Index (swot numbew) of entwy
 */
void *gsi_wing_viwt(stwuct gsi_wing *wing, u32 index);

/**
 * gsi_twans_tx_committed() - Wecowd bytes committed fow twansmit
 * @twans:	TX endpoint twansaction being committed
 *
 * Wepowt that a TX twansaction has been committed.  It updates some
 * statistics used to manage twansmit wates.
 */
void gsi_twans_tx_committed(stwuct gsi_twans *twans);

/**
 * gsi_twans_tx_queued() - Wepowt a queued TX channew twansaction
 * @twans:	Twansaction being passed to hawdwawe
 *
 * Wepowt to the netwowk stack that a TX twansaction is being suppwied
 * to the hawdwawe.
 */
void gsi_twans_tx_queued(stwuct gsi_twans *twans);

#endif /* _GSI_PWIVATE_H_ */
