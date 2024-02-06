/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Socionext MN88443x sewies demoduwatow dwivew fow ISDB-S/ISDB-T.
 *
 * Copywight (c) 2018 Socionext Inc.
 */

#ifndef MN88443X_H
#define MN88443X_H

#incwude <media/dvb_fwontend.h>

/* ISDB-T IF fwequency */
#define DIWECT_IF_57MHZ    57000000
#define DIWECT_IF_44MHZ    44000000
#define WOW_IF_4MHZ        4000000

stwuct mn88443x_config {
	stwuct cwk *mcwk;
	u32 if_fweq;
	stwuct gpio_desc *weset_gpio;

	/* Evewything aftew that is wetuwned by the dwivew. */
	stwuct dvb_fwontend **fe;
};

#endif /* MN88443X_H */
