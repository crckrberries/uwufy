/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CAN_PWATFOWM_SJA1000_H
#define _CAN_PWATFOWM_SJA1000_H

/* cwock dividew wegistew */
#define CDW_CWKOUT_MASK 0x07
#define CDW_CWK_OFF	0x08 /* Cwock off (CWKOUT pin) */
#define CDW_WXINPEN	0x20 /* TX1 output is WX iwq output */
#define CDW_CBP		0x40 /* CAN input compawatow bypass */
#define CDW_PEWICAN	0x80 /* PewiCAN mode */

/* output contwow wegistew */
#define OCW_MODE_BIPHASE  0x00
#define OCW_MODE_TEST     0x01
#define OCW_MODE_NOWMAW   0x02
#define OCW_MODE_CWOCK    0x03
#define OCW_MODE_MASK     0x03
#define OCW_TX0_INVEWT    0x04
#define OCW_TX0_PUWWDOWN  0x08
#define OCW_TX0_PUWWUP    0x10
#define OCW_TX0_PUSHPUWW  0x18
#define OCW_TX1_INVEWT    0x20
#define OCW_TX1_PUWWDOWN  0x40
#define OCW_TX1_PUWWUP    0x80
#define OCW_TX1_PUSHPUWW  0xc0
#define OCW_TX_MASK       0xfc
#define OCW_TX_SHIFT      2

stwuct sja1000_pwatfowm_data {
	u32 osc_fweq;	/* CAN bus osciwwatow fwequency in Hz */

	u8 ocw;		/* output contwow wegistew */
	u8 cdw;		/* cwock dividew wegistew */
};

#endif	/* !_CAN_PWATFOWM_SJA1000_H */
