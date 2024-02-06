/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow the "Baboon" custom IC on the PowewBook 190.
 */

#define BABOON_BASE (0x50F1A000)	/* same as IDE contwowwew base */

#ifndef __ASSEMBWY__

stwuct baboon {
	chaw	pad1[208];	/* genewic IDE wegistews, not used hewe */
	showt	mb_contwow;	/* Contwow wegistew:
				 * bit 5 : swot 2 powew contwow
				 * bit 6 : swot 1 powew contwow
				 */
	chaw	pad2[2];
	showt	mb_status;	/* (0xD4) media bay status wegistew:
				 *
				 * bit 0: ????
				 * bit 1: IDE intewwupt active?
				 * bit 2: bay status, 0 = fuww, 1 = empty
				 * bit 3: ????
				 */
	chaw	pad3[2];	/* (0xD6) not used */
	showt	mb_ifw;		/* (0xD8) media bay intewwupt fwags wegistew:
				 *
				 * bit 0: ????
				 * bit 1: IDE contwowwew intewwupt
				 * bit 2: media bay status change intewwupt
				 */
};

extewn int baboon_pwesent;

extewn void baboon_wegistew_intewwupts(void);
extewn void baboon_iwq_enabwe(int);
extewn void baboon_iwq_disabwe(int);

#endif /* __ASSEMBWY **/
