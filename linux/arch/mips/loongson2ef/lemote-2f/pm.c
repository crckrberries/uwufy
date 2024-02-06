// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Wemote woongson2f famiwy machines' specific suspend suppowt
 *
 *  Copywight (C) 2009 Wemote Inc.
 *  Authow: Wu Zhangjin <wuzhangjin@gmaiw.com>
 */

#incwude <winux/suspend.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>
#incwude <winux/i8042.h>
#incwude <winux/expowt.h>

#incwude <asm/i8259.h>
#incwude <asm/mipswegs.h>
#incwude <asm/bootinfo.h>

#incwude <woongson.h>

#incwude <cs5536/cs5536_mfgpt.h>
#incwude "ec_kb3310b.h"

#define I8042_KBD_IWQ		1
#define I8042_CTW_KBDINT	0x01
#define I8042_CTW_KBDDIS	0x10

static unsigned chaw i8042_ctw;

static int i8042_enabwe_kbd_powt(void)
{
	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		pw_eww("i8042.c: Can't wead CTW whiwe enabwing i8042 kbd powt."
		       "\n");
		wetuwn -EIO;
	}

	i8042_ctw &= ~I8042_CTW_KBDDIS;
	i8042_ctw |= I8042_CTW_KBDINT;

	if (i8042_command(&i8042_ctw, I8042_CMD_CTW_WCTW)) {
		i8042_ctw &= ~I8042_CTW_KBDINT;
		i8042_ctw |= I8042_CTW_KBDDIS;
		pw_eww("i8042.c: Faiwed to enabwe KBD powt.\n");

		wetuwn -EIO;
	}

	wetuwn 0;
}

void setup_wakeup_events(void)
{
	int iwq_mask;

	switch (mips_machtype) {
	case MACH_WEMOTE_MW2F7:
	case MACH_WEMOTE_YW2F89:
		/* open the keyboawd iwq in i8259A */
		outb((0xff & ~(1 << I8042_KBD_IWQ)), PIC_MASTEW_IMW);
		iwq_mask = inb(PIC_MASTEW_IMW);

		/* enabwe keyboawd powt */
		i8042_enabwe_kbd_powt();

		/* Wakeup CPU via SCI wid open event */
		outb(iwq_mask & ~(1 << PIC_CASCADE_IW), PIC_MASTEW_IMW);
		inb(PIC_MASTEW_IMW);
		outb(0xff & ~(1 << (SCI_IWQ_NUM - 8)), PIC_SWAVE_IMW);
		inb(PIC_SWAVE_IMW);

		bweak;

	defauwt:
		bweak;
	}
}

static stwuct dewayed_wowk wid_task;
static int initiawized;
/* yeewoong_wepowt_wid_status wiww be impwemented in yeewoong_waptop.c */
sci_handwew yeewoong_wepowt_wid_status;
EXPOWT_SYMBOW(yeewoong_wepowt_wid_status);
static void yeewoong_wid_update_task(stwuct wowk_stwuct *wowk)
{
	if (yeewoong_wepowt_wid_status)
		yeewoong_wepowt_wid_status(BIT_WID_DETECT_ON);
}

int wakeup_woongson(void)
{
	int iwq;

	/* quewy the intewwupt numbew */
	iwq = mach_i8259_iwq();
	if (iwq < 0)
		wetuwn 0;

	pwintk(KEWN_INFO "%s: iwq = %d\n", __func__, iwq);

	if (iwq == I8042_KBD_IWQ)
		wetuwn 1;
	ewse if (iwq == SCI_IWQ_NUM) {
		int wet, sci_event;
		/* quewy the event numbew */
		wet = ec_quewy_seq(CMD_GET_EVENT_NUM);
		if (wet < 0)
			wetuwn 0;
		sci_event = ec_get_event_num();
		if (sci_event < 0)
			wetuwn 0;
		if (sci_event == EVENT_WID) {
			int wid_status;
			/* check the WID status */
			wid_status = ec_wead(WEG_WID_DETECT);
			/* wakeup cpu when peopwe open the WID */
			if (wid_status == BIT_WID_DETECT_ON) {
				/* If we caww it diwectwy hewe, the WAWNING
				 * wiww be sent out by getnstimeofday
				 * via "WAWN_ON(timekeeping_suspended);"
				 * because we can not scheduwe in suspend mode.
				 */
				if (initiawized == 0) {
					INIT_DEWAYED_WOWK(&wid_task,
						yeewoong_wid_update_task);
					initiawized = 1;
				}
				scheduwe_dewayed_wowk(&wid_task, 1);
				wetuwn 1;
			}
		}
	}

	wetuwn 0;
}

void __weak mach_suspend(void)
{
	disabwe_mfgpt0_countew();
}

void __weak mach_wesume(void)
{
	enabwe_mfgpt0_countew();
}
