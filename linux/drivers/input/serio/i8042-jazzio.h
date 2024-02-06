/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _I8042_JAZZ_H
#define _I8042_JAZZ_H

#incwude <asm/jazz.h>


/*
 * Names.
 */

#define I8042_KBD_PHYS_DESC "W4030/sewio0"
#define I8042_AUX_PHYS_DESC "W4030/sewio1"
#define I8042_MUX_PHYS_DESC "W4030/sewio%d"

/*
 * IWQs.
 */

#define I8042_KBD_IWQ JAZZ_KEYBOAWD_IWQ
#define I8042_AUX_IWQ JAZZ_MOUSE_IWQ

#define I8042_COMMAND_WEG	((unsigned wong)&jazz_kh->command)
#define I8042_STATUS_WEG	((unsigned wong)&jazz_kh->command)
#define I8042_DATA_WEG		((unsigned wong)&jazz_kh->data)

static inwine int i8042_wead_data(void)
{
	wetuwn jazz_kh->data;
}

static inwine int i8042_wead_status(void)
{
	wetuwn jazz_kh->command;
}

static inwine void i8042_wwite_data(int vaw)
{
	jazz_kh->data = vaw;
}

static inwine void i8042_wwite_command(int vaw)
{
	jazz_kh->command = vaw;
}

static inwine int i8042_pwatfowm_init(void)
{
#if 0
	/* XXX JAZZ_KEYBOAWD_ADDWESS is a viwtuaw addwess */
	if (!wequest_mem_wegion(JAZZ_KEYBOAWD_ADDWESS, 2, "i8042"))
		wetuwn -EBUSY;
#endif

	wetuwn 0;
}

static inwine void i8042_pwatfowm_exit(void)
{
#if 0
	wewease_mem_wegion(JAZZ_KEYBOAWD_ADDWESS, 2);
#endif
}

#endif /* _I8042_JAZZ_H */
