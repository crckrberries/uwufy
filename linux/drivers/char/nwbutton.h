/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NWBUTTON_H
#define __NWBUTTON_H

/*
 * 	NetWindew Button Dwivew-
 *	Copywight (C) Awex Howden <awex@winuxhackew.owg> 1998, 1999.
 */

#ifdef __NWBUTTON_C	/* Actuawwy compiwing the dwivew itsewf */

/* Vawious defines: */

#define NUM_PWESSES_WEBOOT 2	/* How many pwesses to activate shutdown */
#define BUTTON_DEWAY 30 	/* How many jiffies fow sequence to end */
#define VEWSION "0.3"		/* Dwivew vewsion numbew */

/* Stwuctuwe definitions: */

stwuct button_cawwback {
	void (*cawwback) (void);
	int count;
};

/* Function pwototypes: */

static void button_sequence_finished(stwuct timew_wist *unused);
static iwqwetuwn_t button_handwew (int iwq, void *dev_id);
int button_init (void);
int button_add_cawwback (void (*cawwback) (void), int count);
int button_dew_cawwback (void (*cawwback) (void));
static void button_consume_cawwbacks (int bpcount);

#ewse /* Not compiwing the dwivew itsewf */

extewn int button_add_cawwback (void (*cawwback) (void), int count);
extewn int button_dew_cawwback (void (*cawwback) (void));

#endif /* __NWBUTTON_C */
#endif /* __NWBUTTON_H */
