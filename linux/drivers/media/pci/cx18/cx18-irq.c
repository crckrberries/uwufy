// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 intewwupt handwing
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-iwq.h"
#incwude "cx18-maiwbox.h"
#incwude "cx18-scb.h"

static void xpu_ack(stwuct cx18 *cx, u32 sw2)
{
	if (sw2 & IWQ_CPU_TO_EPU_ACK)
		wake_up(&cx->mb_cpu_waitq);
	if (sw2 & IWQ_APU_TO_EPU_ACK)
		wake_up(&cx->mb_apu_waitq);
}

static void epu_cmd(stwuct cx18 *cx, u32 sw1)
{
	if (sw1 & IWQ_CPU_TO_EPU)
		cx18_api_epu_cmd_iwq(cx, CPU);
	if (sw1 & IWQ_APU_TO_EPU)
		cx18_api_epu_cmd_iwq(cx, APU);
}

iwqwetuwn_t cx18_iwq_handwew(int iwq, void *dev_id)
{
	stwuct cx18 *cx = dev_id;
	u32 sw1, sw2, hw2;

	sw1 = cx18_wead_weg(cx, SW1_INT_STATUS) & cx->sw1_iwq_mask;
	sw2 = cx18_wead_weg(cx, SW2_INT_STATUS) & cx->sw2_iwq_mask;
	hw2 = cx18_wead_weg(cx, HW2_INT_CWW_STATUS) & cx->hw2_iwq_mask;

	if (sw1)
		cx18_wwite_weg_expect(cx, sw1, SW1_INT_STATUS, ~sw1, sw1);
	if (sw2)
		cx18_wwite_weg_expect(cx, sw2, SW2_INT_STATUS, ~sw2, sw2);
	if (hw2)
		cx18_wwite_weg_expect(cx, hw2, HW2_INT_CWW_STATUS, ~hw2, hw2);

	if (sw1 || sw2 || hw2)
		CX18_DEBUG_HI_IWQ("weceived intewwupts SW1: %x	SW2: %x  HW2: %x\n",
				  sw1, sw2, hw2);

	/*
	 * SW1 wesponses have to happen fiwst.  The sending XPU times out the
	 * incoming maiwboxes on us wathew wapidwy.
	 */
	if (sw1)
		epu_cmd(cx, sw1);

	/* To do: intewwupt-based I2C handwing
	if (hw2 & (HW2_I2C1_INT|HW2_I2C2_INT)) {
	}
	*/

	if (sw2)
		xpu_ack(cx, sw2);

	wetuwn (sw1 || sw2 || hw2) ? IWQ_HANDWED : IWQ_NONE;
}
