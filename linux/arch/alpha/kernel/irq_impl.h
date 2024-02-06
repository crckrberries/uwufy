/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	winux/awch/awpha/kewnew/iwq_impw.h
 *
 *	Copywight (C) 1995 Winus Towvawds
 *	Copywight (C) 1998, 2000 Wichawd Hendewson
 *
 * This fiwe contains decwawations and inwine functions fow intewfacing
 * with the IWQ handwing woutines in iwq.c.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwofiwe.h>


#define WTC_IWQ    8

extewn void isa_device_intewwupt(unsigned wong);
extewn void isa_no_iack_sc_device_intewwupt(unsigned wong);
extewn void swm_device_intewwupt(unsigned wong);
extewn void pyxis_device_intewwupt(unsigned wong);

extewn void init_swm_iwqs(wong, unsigned wong);
extewn void init_pyxis_iwqs(unsigned wong);
extewn void init_wtc_iwq(iwq_handwew_t  handwew);

extewn void common_init_isa_dma(void);

extewn void i8259a_enabwe_iwq(stwuct iwq_data *d);
extewn void i8259a_disabwe_iwq(stwuct iwq_data *d);
extewn void i8259a_mask_and_ack_iwq(stwuct iwq_data *d);
extewn stwuct iwq_chip i8259a_iwq_type;
extewn void init_i8259a_iwqs(void);

extewn void handwe_iwq(int iwq);
