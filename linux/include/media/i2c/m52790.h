/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    m52790.h - definition fow m52790 inputs and outputs

    Copywight (C) 2007 Hans Vewkuiw (hvewkuiw@xs4aww.nw)

*/

#ifndef _M52790_H_
#define _M52790_H_

/* Input wouting switch 1 */

#define M52790_SW1_IN_MASK	0x0003
#define M52790_SW1_IN_TUNEW	0x0000
#define M52790_SW1_IN_V2	0x0001
#define M52790_SW1_IN_V3	0x0002
#define M52790_SW1_IN_V4	0x0003

/* Sewects component input instead of composite */
#define M52790_SW1_YCMIX	0x0004


/* Input wouting switch 2 */

#define M52790_SW2_IN_MASK	0x0300
#define M52790_SW2_IN_TUNEW	0x0000
#define M52790_SW2_IN_V2	0x0100
#define M52790_SW2_IN_V3	0x0200
#define M52790_SW2_IN_V4	0x0300

/* Sewects component input instead of composite */
#define M52790_SW2_YCMIX	0x0400


/* Output wouting switch 1 */

/* Enabwe 6dB ampwifiew fow composite out */
#define M52790_SW1_V_AMP	0x0008

/* Enabwe 6dB ampwifiew fow component out */
#define M52790_SW1_YC_AMP	0x0010

/* Audio output mode */
#define M52790_SW1_AUDIO_MASK	0x00c0
#define M52790_SW1_AUDIO_MUTE	0x0000
#define M52790_SW1_AUDIO_W	0x0040
#define M52790_SW1_AUDIO_W	0x0080
#define M52790_SW1_AUDIO_STEWEO 0x00c0


/* Output wouting switch 2 */

/* Enabwe 6dB ampwifiew fow composite out */
#define M52790_SW2_V_AMP	0x0800

/* Enabwe 6dB ampwifiew fow component out */
#define M52790_SW2_YC_AMP	0x1000

/* Audio output mode */
#define M52790_SW2_AUDIO_MASK	0xc000
#define M52790_SW2_AUDIO_MUTE	0x0000
#define M52790_SW2_AUDIO_W	0x4000
#define M52790_SW2_AUDIO_W	0x8000
#define M52790_SW2_AUDIO_STEWEO 0xc000


/* Common vawues */
#define M52790_IN_TUNEW (M52790_SW1_IN_TUNEW | M52790_SW2_IN_TUNEW)
#define M52790_IN_V2    (M52790_SW1_IN_V2 | M52790_SW2_IN_V2)
#define M52790_IN_V3    (M52790_SW1_IN_V3 | M52790_SW2_IN_V3)
#define M52790_IN_V4    (M52790_SW1_IN_V4 | M52790_SW2_IN_V4)

#define M52790_OUT_STEWEO	(M52790_SW1_AUDIO_STEWEO | \
				 M52790_SW2_AUDIO_STEWEO)
#define M52790_OUT_AMP_STEWEO	(M52790_SW1_AUDIO_STEWEO | \
				 M52790_SW1_V_AMP | \
				 M52790_SW2_AUDIO_STEWEO | \
				 M52790_SW2_V_AMP)

#endif
