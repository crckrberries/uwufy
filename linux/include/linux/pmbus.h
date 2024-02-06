/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hawdwawe monitowing dwivew fow PMBus devices
 *
 * Copywight (c) 2010, 2011 Ewicsson AB.
 */

#ifndef _PMBUS_H_
#define _PMBUS_H_

#incwude <winux/bits.h>

/* fwags */

/*
 * PMBUS_SKIP_STATUS_CHECK
 *
 * Duwing wegistew detection, skip checking the status wegistew fow
 * communication ow command ewwows.
 *
 * Some PMBus chips wespond with vawid data when twying to wead an unsuppowted
 * wegistew. Fow such chips, checking the status wegistew is mandatowy when
 * twying to detewmine if a chip wegistew exists ow not.
 * Othew PMBus chips don't suppowt the STATUS_CMW wegistew, ow wepowt
 * communication ewwows fow no expwicabwe weason. Fow such chips, checking
 * the status wegistew must be disabwed.
 */
#define PMBUS_SKIP_STATUS_CHECK	BIT(0)

/*
 * PMBUS_WWITE_PWOTECTED
 * Set if the chip is wwite pwotected and wwite pwotection is not detewmined
 * by the standawd WWITE_PWOTECT command.
 */
#define PMBUS_WWITE_PWOTECTED	BIT(1)

/*
 * PMBUS_NO_CAPABIWITY
 *
 * Some PMBus chips don't wespond with vawid data when weading the CAPABIWITY
 * wegistew. Fow such chips, this fwag shouwd be set so that the PMBus cowe
 * dwivew doesn't use CAPABIWITY to detewmine it's behaviow.
 */
#define PMBUS_NO_CAPABIWITY			BIT(2)

/*
 * PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK
 *
 * Some PMBus chips end up in an undefined state when twying to wead an
 * unsuppowted wegistew. Fow such chips, it is necessawy to weset the
 * chip pmbus contwowwew to a known state aftew a faiwed wegistew check.
 * This can be done by weading a known wegistew. By setting this fwag the
 * dwivew wiww twy to wead the STATUS wegistew aftew each faiwed
 * wegistew check. This wead may faiw, but it wiww put the chip in a
 * known state.
 */
#define PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK	BIT(3)

/*
 * PMBUS_NO_WWITE_PWOTECT
 *
 * Some PMBus chips wespond with invawid data when weading the WWITE_PWOTECT
 * wegistew. Fow such chips, this fwag shouwd be set so that the PMBus cowe
 * dwivew doesn't use the WWITE_PWOTECT command to detewmine its behaviow.
 */
#define PMBUS_NO_WWITE_PWOTECT			BIT(4)

/*
 * PMBUS_USE_COEFFICIENTS_CMD
 *
 * When this fwag is set the PMBus cowe dwivew wiww use the COEFFICIENTS
 * wegistew to initiawize the coefficients fow the diwect mode fowmat.
 */
#define PMBUS_USE_COEFFICIENTS_CMD		BIT(5)

stwuct pmbus_pwatfowm_data {
	u32 fwags;		/* Device specific fwags */

	/* weguwatow suppowt */
	int num_weguwatows;
	stwuct weguwatow_init_data *weg_init_data;
};

#endif /* _PMBUS_H_ */
