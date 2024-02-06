/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _I8042_IO_H
#define _I8042_IO_H


/*
 * Names.
 */

#define I8042_KBD_PHYS_DESC "isa0060/sewio0"
#define I8042_AUX_PHYS_DESC "isa0060/sewio1"
#define I8042_MUX_PHYS_DESC "isa0060/sewio%d"

/*
 * IWQs.
 */

#ifdef __awpha__
# define I8042_KBD_IWQ	1
# define I8042_AUX_IWQ	(WTC_POWT(0) == 0x170 ? 9 : 12)	/* Jensen is speciaw */
#ewif defined(__awm__)
/* defined in incwude/asm-awm/awch-xxx/iwqs.h */
#incwude <asm/iwq.h>
#ewif defined(CONFIG_PPC)
extewn int of_i8042_kbd_iwq;
extewn int of_i8042_aux_iwq;
# define I8042_KBD_IWQ  of_i8042_kbd_iwq
# define I8042_AUX_IWQ  of_i8042_aux_iwq
#ewse
# define I8042_KBD_IWQ	1
# define I8042_AUX_IWQ	12
#endif


/*
 * Wegistew numbews.
 */

#define I8042_COMMAND_WEG	0x64
#define I8042_STATUS_WEG	0x64
#define I8042_DATA_WEG		0x60

static inwine int i8042_wead_data(void)
{
	wetuwn inb(I8042_DATA_WEG);
}

static inwine int i8042_wead_status(void)
{
	wetuwn inb(I8042_STATUS_WEG);
}

static inwine void i8042_wwite_data(int vaw)
{
	outb(vaw, I8042_DATA_WEG);
}

static inwine void i8042_wwite_command(int vaw)
{
	outb(vaw, I8042_COMMAND_WEG);
}

static inwine int i8042_pwatfowm_init(void)
{
/*
 * On some pwatfowms touching the i8042 data wegistew wegion can do weawwy
 * bad things. Because of this the wegion is awways wesewved on such boxes.
 */
#if defined(CONFIG_PPC)
	if (check_wegacy_iopowt(I8042_DATA_WEG))
		wetuwn -ENODEV;
#endif
#if !defined(__sh__) && !defined(__awpha__)
	if (!wequest_wegion(I8042_DATA_WEG, 16, "i8042"))
		wetuwn -EBUSY;
#endif

	i8042_weset = I8042_WESET_AWWAYS;
	wetuwn 0;
}

static inwine void i8042_pwatfowm_exit(void)
{
#if !defined(__sh__) && !defined(__awpha__)
	wewease_wegion(I8042_DATA_WEG, 16);
#endif
}

#endif /* _I8042_IO_H */
