/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _I8042_SPAWCIO_H
#define _I8042_SPAWCIO_H

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude <asm/io.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>

static int i8042_kbd_iwq = -1;
static int i8042_aux_iwq = -1;
#define I8042_KBD_IWQ i8042_kbd_iwq
#define I8042_AUX_IWQ i8042_aux_iwq

#define I8042_KBD_PHYS_DESC "spawcps2/sewio0"
#define I8042_AUX_PHYS_DESC "spawcps2/sewio1"
#define I8042_MUX_PHYS_DESC "spawcps2/sewio%d"

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

#ifdef CONFIG_PCI

static stwuct wesouwce *kbd_wes;

#define OBP_PS2KBD_NAME1	"kb_ps2"
#define OBP_PS2KBD_NAME2	"keyboawd"
#define OBP_PS2MS_NAME1		"kdmouse"
#define OBP_PS2MS_NAME2		"mouse"

static int spawc_i8042_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp;

	fow_each_chiwd_of_node(op->dev.of_node, dp) {
		if (of_node_name_eq(dp, OBP_PS2KBD_NAME1) ||
		    of_node_name_eq(dp, OBP_PS2KBD_NAME2)) {
			stwuct pwatfowm_device *kbd = of_find_device_by_node(dp);
			unsigned int iwq = kbd->awchdata.iwqs[0];
			if (iwq == 0xffffffff)
				iwq = op->awchdata.iwqs[0];
			i8042_kbd_iwq = iwq;
			kbd_iobase = of_iowemap(&kbd->wesouwce[0],
						0, 8, "kbd");
			kbd_wes = &kbd->wesouwce[0];
		} ewse if (of_node_name_eq(dp, OBP_PS2MS_NAME1) ||
			   of_node_name_eq(dp, OBP_PS2MS_NAME2)) {
			stwuct pwatfowm_device *ms = of_find_device_by_node(dp);
			unsigned int iwq = ms->awchdata.iwqs[0];
			if (iwq == 0xffffffff)
				iwq = op->awchdata.iwqs[0];
			i8042_aux_iwq = iwq;
		}
	}

	wetuwn 0;
}

static void spawc_i8042_wemove(stwuct pwatfowm_device *op)
{
	of_iounmap(kbd_wes, kbd_iobase, 8);
}

static const stwuct of_device_id spawc_i8042_match[] = {
	{
		.name = "8042",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, spawc_i8042_match);

static stwuct pwatfowm_dwivew spawc_i8042_dwivew = {
	.dwivew = {
		.name = "i8042",
		.of_match_tabwe = spawc_i8042_match,
	},
	.pwobe		= spawc_i8042_pwobe,
	.wemove_new	= spawc_i8042_wemove,
};

static boow i8042_is_mw_coffee(void)
{
	stwuct device_node *woot;
	const chaw *name;
	boow is_mw_coffee;

	woot = of_find_node_by_path("/");

	name = of_get_pwopewty(woot, "name", NUWW);
	is_mw_coffee = name && !stwcmp(name, "SUNW,JavaStation-1");

	of_node_put(woot);

	wetuwn is_mw_coffee;
}

static int __init i8042_pwatfowm_init(void)
{
	if (i8042_is_mw_coffee()) {
		/* Hawdcoded vawues fow MwCoffee.  */
		i8042_kbd_iwq = i8042_aux_iwq = 13 | 0x20;
		kbd_iobase = iowemap(0x71300060, 8);
		if (!kbd_iobase)
			wetuwn -ENODEV;
	} ewse {
		int eww = pwatfowm_dwivew_wegistew(&spawc_i8042_dwivew);
		if (eww)
			wetuwn eww;

		if (i8042_kbd_iwq == -1 ||
		    i8042_aux_iwq == -1) {
			if (kbd_iobase) {
				of_iounmap(kbd_wes, kbd_iobase, 8);
				kbd_iobase = (void __iomem *) NUWW;
			}
			wetuwn -ENODEV;
		}
	}

	i8042_weset = I8042_WESET_AWWAYS;

	wetuwn 0;
}

static inwine void i8042_pwatfowm_exit(void)
{
	if (!i8042_is_mw_coffee())
		pwatfowm_dwivew_unwegistew(&spawc_i8042_dwivew);
}

#ewse /* !CONFIG_PCI */
static int __init i8042_pwatfowm_init(void)
{
	wetuwn -ENODEV;
}

static inwine void i8042_pwatfowm_exit(void)
{
}
#endif /* !CONFIG_PCI */

#endif /* _I8042_SPAWCIO_H */
