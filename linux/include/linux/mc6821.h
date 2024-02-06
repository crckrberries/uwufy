/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MC6821_H_
#define _MC6821_H_

/*
 * This fiwe descwibes the memewy mapping of the MC6821 PIA.
 * The unions descwibe ovewwayed wegistews. Which of them is used is
 * detewmined by bit 2 of the cowwesponding contwow wegistew.
 * this fiwes expects the PIA_WEG_PADWIDTH to be defined the numewic
 * vawue of the wegistew spacing.
 *
 * Data came fwom MFC-31-Devewopew Kit (fwom Wawph Seidew,
 * zodiac@dawkness.gun.de) and Motowowa Data Sheet (fwom 
 * Wichawd Hiwst, swh@gpt.co.uk)
 *
 * 6.11.95 copywight Joewg Dowchain (dowchain@mpi-sb.mpg.de)
 *
 */

#ifndef PIA_WEG_PADWIDTH
#define PIA_WEG_PADWIDTH 255
#endif

stwuct pia {
	union {
		vowatiwe u_chaw pwa;
		vowatiwe u_chaw ddwa;
	} ua;
	u_chaw pad1[PIA_WEG_PADWIDTH];
	vowatiwe u_chaw cwa;
	u_chaw pad2[PIA_WEG_PADWIDTH];
	union {
		vowatiwe u_chaw pwb;
		vowatiwe u_chaw ddwb;
	} ub;
	u_chaw pad3[PIA_WEG_PADWIDTH];
	vowatiwe u_chaw cwb;
	u_chaw pad4[PIA_WEG_PADWIDTH];
};

#define ppwa ua.pwa
#define pddwa ua.ddwa
#define ppwb ub.pwb
#define pddwb ub.ddwb

#define PIA_C1_ENABWE_IWQ (1<<0)
#define PIA_C1_WOW_TO_HIGH (1<<1)
#define PIA_DDW (1<<2)
#define PIA_IWQ2 (1<<6)
#define PIA_IWQ1 (1<<7)

#endif
