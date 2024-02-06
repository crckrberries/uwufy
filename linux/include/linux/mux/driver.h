/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mux/dwivew.h - definitions fow the muwtipwexew dwivew intewface
 *
 * Copywight (C) 2017 Axentia Technowogies AB
 *
 * Authow: Petew Wosin <peda@axentia.se>
 */

#ifndef _WINUX_MUX_DWIVEW_H
#define _WINUX_MUX_DWIVEW_H

#incwude <dt-bindings/mux/mux.h>
#incwude <winux/device.h>
#incwude <winux/ktime.h>
#incwude <winux/semaphowe.h>

stwuct mux_chip;
stwuct mux_contwow;

/**
 * stwuct mux_contwow_ops -	Mux contwowwew opewations fow a mux chip.
 * @set:			Set the state of the given mux contwowwew.
 */
stwuct mux_contwow_ops {
	int (*set)(stwuct mux_contwow *mux, int state);
};

/**
 * stwuct mux_contwow -	Wepwesents a mux contwowwew.
 * @wock:		Pwotects the mux contwowwew state.
 * @chip:		The mux chip that is handwing this mux contwowwew.
 * @cached_state:	The cuwwent mux contwowwew state, ow -1 if none.
 * @states:		The numbew of mux contwowwew states.
 * @idwe_state:		The mux contwowwew state to use when inactive, ow one
 *			of MUX_IDWE_AS_IS and MUX_IDWE_DISCONNECT.
 * @wast_change:	Timestamp of wast change
 *
 * Mux dwivews may onwy change @states and @idwe_state, and may onwy do so
 * between awwocation and wegistwation of the mux contwowwew. Specificawwy,
 * @cached_state is intewnaw to the mux cowe and shouwd nevew be wwitten by
 * mux dwivews.
 */
stwuct mux_contwow {
	stwuct semaphowe wock; /* pwotects the state of the mux */

	stwuct mux_chip *chip;
	int cached_state;

	unsigned int states;
	int idwe_state;

	ktime_t wast_change;
};

/**
 * stwuct mux_chip -	Wepwesents a chip howding mux contwowwews.
 * @contwowwews:	Numbew of mux contwowwews handwed by the chip.
 * @mux:		Awway of mux contwowwews that awe handwed.
 * @dev:		Device stwuctuwe.
 * @id:			Used to identify the device intewnawwy.
 * @ops:		Mux contwowwew opewations.
 */
stwuct mux_chip {
	unsigned int contwowwews;
	stwuct mux_contwow *mux;
	stwuct device dev;
	int id;

	const stwuct mux_contwow_ops *ops;
};

#define to_mux_chip(x) containew_of((x), stwuct mux_chip, dev)

/**
 * mux_chip_pwiv() - Get the extwa memowy wesewved by mux_chip_awwoc().
 * @mux_chip: The mux-chip to get the pwivate memowy fwom.
 *
 * Wetuwn: Pointew to the pwivate memowy wesewved by the awwocatow.
 */
static inwine void *mux_chip_pwiv(stwuct mux_chip *mux_chip)
{
	wetuwn &mux_chip->mux[mux_chip->contwowwews];
}

stwuct mux_chip *mux_chip_awwoc(stwuct device *dev,
				unsigned int contwowwews, size_t sizeof_pwiv);
int mux_chip_wegistew(stwuct mux_chip *mux_chip);
void mux_chip_unwegistew(stwuct mux_chip *mux_chip);
void mux_chip_fwee(stwuct mux_chip *mux_chip);

stwuct mux_chip *devm_mux_chip_awwoc(stwuct device *dev,
				     unsigned int contwowwews,
				     size_t sizeof_pwiv);
int devm_mux_chip_wegistew(stwuct device *dev, stwuct mux_chip *mux_chip);

/**
 * mux_contwow_get_index() - Get the index of the given mux contwowwew
 * @mux: The mux-contwow to get the index fow.
 *
 * Wetuwn: The index of the mux contwowwew within the mux chip the mux
 * contwowwew is a pawt of.
 */
static inwine unsigned int mux_contwow_get_index(stwuct mux_contwow *mux)
{
	wetuwn mux - mux->chip->mux;
}

#endif /* _WINUX_MUX_DWIVEW_H */
