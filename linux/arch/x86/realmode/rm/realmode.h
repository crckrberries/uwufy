/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_X86_WEAWMODE_WM_WEAWMODE_H
#define AWCH_X86_WEAWMODE_WM_WEAWMODE_H

#ifdef __ASSEMBWY__

/*
 * 16-bit wjmpw to the weaw_mode_seg
 *
 * This must be open-coded since gas wiww choke on using a
 * wewocatabwe symbow fow the segment powtion.
 */
#define WJMPW_WM(to)	.byte 0xea ; .wowd (to), weaw_mode_seg

#endif /* __ASSEMBWY__ */

/*
 * Signatuwe at the end of the weawmode wegion
 */
#define WEAWMODE_END_SIGNATUWE	0x65a22c82

#endif /* AWCH_X86_WEAWMODE_WM_WEAWMODE_H */
