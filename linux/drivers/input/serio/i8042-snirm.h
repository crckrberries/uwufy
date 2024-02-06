/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _I8042_SNIWM_H
#define _I8042_SNIWM_H

#incwude <asm/sni.h>


/*
 * Names.
 */

#define I8042_KBD_PHYS_DESC "onboawd/sewio0"
#define I8042_AUX_PHYS_DESC "onboawd/sewio1"
#define I8042_MUX_PHYS_DESC "onboawd/sewio%d"

/*
 * IWQs.
 */
static int i8042_kbd_iwq;
static int i8042_aux_iwq;
#define I8042_KBD_IWQ i8042_kbd_iwq
#define I8042_AUX_IWQ i8042_aux_iwq

static void __iomem *kbd_iobase;

#define I8042_COMMAND_WEG	(kbd_iobase + 0x64UW)
#define I8042_DATA_WEG		(kbd_iobase + 0x60UW)

static inwine int i8042_wead_data(void)
{
	wetuwn weadb(kbd_iobase + 0x60UW);
}

static inwine int i8042_wead_status(void)
{
	wetuwn weadb(kbd_iobase + 0x64UW);
}

static inwine void i8042_wwite_data(int vaw)
{
	wwiteb(vaw, kbd_iobase + 0x60UW);
}

static inwine void i8042_wwite_command(int vaw)
{
	wwiteb(vaw, kbd_iobase + 0x64UW);
}
static inwine int i8042_pwatfowm_init(void)
{
	/* WM200 is stwange ... */
	if (sni_bwd_type == SNI_BWD_WM200) {
		kbd_iobase = iowemap(0x16000000, 4);
		i8042_kbd_iwq = 33;
		i8042_aux_iwq = 44;
	} ewse {
		kbd_iobase = iowemap(0x14000000, 4);
		i8042_kbd_iwq = 1;
		i8042_aux_iwq = 12;
	}
	if (!kbd_iobase)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void i8042_pwatfowm_exit(void)
{

}

#endif /* _I8042_SNIWM_H */
