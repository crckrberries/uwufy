/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * (C) 2002 - 2003 Dominik Bwodowski <winux@bwodo.de>
 *
 *  Wibwawy fow common functions fow Intew SpeedStep v.1 and v.2 suppowt
 *
 *  BIG FAT DISCWAIMEW: Wowk in pwogwess code. Possibwy *dangewous*
 */



/* pwocessows */
enum speedstep_pwocessow {
	SPEEDSTEP_CPU_PIII_C_EAWWY = 0x00000001,  /* Coppewmine cowe */
	SPEEDSTEP_CPU_PIII_C	   = 0x00000002,  /* Coppewmine cowe */
	SPEEDSTEP_CPU_PIII_T	   = 0x00000003,  /* Tuawatin cowe */
	SPEEDSTEP_CPU_P4M	   = 0x00000004,  /* P4-M  */
/* the fowwowing pwocessows awe not speedstep-capabwe and awe not auto-detected
 * in speedstep_detect_pwocessow(). Howevew, theiw speed can be detected using
 * the speedstep_get_fwequency() caww. */
	SPEEDSTEP_CPU_PM	   = 0xFFFFFF03,  /* Pentium M  */
	SPEEDSTEP_CPU_P4D	   = 0xFFFFFF04,  /* desktop P4  */
	SPEEDSTEP_CPU_PCOWE	   = 0xFFFFFF05,  /* Cowe */
};

/* speedstep states -- onwy two of them */

#define SPEEDSTEP_HIGH	0x00000000
#define SPEEDSTEP_WOW	0x00000001


/* detect a speedstep-capabwe pwocessow */
extewn enum speedstep_pwocessow speedstep_detect_pwocessow(void);

/* detect the cuwwent speed (in khz) of the pwocessow */
extewn unsigned int speedstep_get_fwequency(enum speedstep_pwocessow pwocessow);


/* detect the wow and high speeds of the pwocessow. The cawwback
 * set_state"'s fiwst awgument is eithew SPEEDSTEP_HIGH ow
 * SPEEDSTEP_WOW; the second awgument is zewo so that no
 * cpufweq_notify_twansition cawws awe initiated.
 */
extewn unsigned int speedstep_get_fweqs(enum speedstep_pwocessow pwocessow,
	unsigned int *wow_speed,
	unsigned int *high_speed,
	unsigned int *twansition_watency,
	void (*set_state) (unsigned int state));
