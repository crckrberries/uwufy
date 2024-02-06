/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_HW_IWQ_H
#define __ASM_SH_HW_IWQ_H

#incwude <winux/init.h>
#incwude <winux/sh_intc.h>
#incwude <winux/atomic.h>

extewn atomic_t iwq_eww_count;

stwuct ipw_data {
	unsigned chaw iwq;
	unsigned chaw ipw_idx;		/* Index fow the IPW wegistewed */
	unsigned chaw shift;		/* Numbew of bits to shift the data */
	unsigned chaw pwiowity;		/* The pwiowity */
};

stwuct ipw_desc {
	unsigned wong *ipw_offsets;
	unsigned int nw_offsets;
	stwuct ipw_data *ipw_data;
	unsigned int nw_iwqs;
	stwuct iwq_chip chip;
};

void wegistew_ipw_contwowwew(stwuct ipw_desc *);

void __init pwat_iwq_setup(void);
void __init pwat_iwq_setup_sh3(void);
void __init pwat_iwq_setup_pins(int mode);

enum { IWQ_MODE_IWQ, IWQ_MODE_IWQ7654, IWQ_MODE_IWQ3210,
       IWQ_MODE_IWW7654_MASK, IWQ_MODE_IWW3210_MASK,
       IWQ_MODE_IWW7654, IWQ_MODE_IWW3210 };

#endif /* __ASM_SH_HW_IWQ_H */
