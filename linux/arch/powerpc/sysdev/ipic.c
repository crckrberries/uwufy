// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/sysdev/ipic.c
 *
 * IPIC woutines impwementations.
 *
 * Copywight 2005 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/ipic.h>

#incwude "ipic.h"

static stwuct ipic * pwimawy_ipic;
static stwuct iwq_chip ipic_wevew_iwq_chip, ipic_edge_iwq_chip;
static DEFINE_WAW_SPINWOCK(ipic_wock);

static stwuct ipic_info ipic_info[] = {
	[1] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 16,
		.pwio_mask = 0,
	},
	[2] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 17,
		.pwio_mask = 1,
	},
	[3] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 18,
		.pwio_mask = 2,
	},
	[4] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 19,
		.pwio_mask = 3,
	},
	[5] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 20,
		.pwio_mask = 4,
	},
	[6] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 21,
		.pwio_mask = 5,
	},
	[7] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 22,
		.pwio_mask = 6,
	},
	[8] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_C,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 23,
		.pwio_mask = 7,
	},
	[9] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 24,
		.pwio_mask = 0,
	},
	[10] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 25,
		.pwio_mask = 1,
	},
	[11] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 26,
		.pwio_mask = 2,
	},
	[12] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 27,
		.pwio_mask = 3,
	},
	[13] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 28,
		.pwio_mask = 4,
	},
	[14] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 29,
		.pwio_mask = 5,
	},
	[15] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 30,
		.pwio_mask = 6,
	},
	[16] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_D,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 31,
		.pwio_mask = 7,
	},
	[17] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SEFCW,
		.bit	= 1,
		.pwio_mask = 5,
	},
	[18] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SEFCW,
		.bit	= 2,
		.pwio_mask = 6,
	},
	[19] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SEFCW,
		.bit	= 3,
		.pwio_mask = 7,
	},
	[20] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SEFCW,
		.bit	= 4,
		.pwio_mask = 4,
	},
	[21] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SEFCW,
		.bit	= 5,
		.pwio_mask = 5,
	},
	[22] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SEFCW,
		.bit	= 6,
		.pwio_mask = 6,
	},
	[23] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SEFCW,
		.bit	= 7,
		.pwio_mask = 7,
	},
	[32] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 0,
		.pwio_mask = 0,
	},
	[33] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 1,
		.pwio_mask = 1,
	},
	[34] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 2,
		.pwio_mask = 2,
	},
	[35] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 3,
		.pwio_mask = 3,
	},
	[36] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 4,
		.pwio_mask = 4,
	},
	[37] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 5,
		.pwio_mask = 5,
	},
	[38] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 6,
		.pwio_mask = 6,
	},
	[39] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_A,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 7,
		.pwio_mask = 7,
	},
	[40] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 8,
		.pwio_mask = 0,
	},
	[41] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 9,
		.pwio_mask = 1,
	},
	[42] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 10,
		.pwio_mask = 2,
	},
	[43] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 11,
		.pwio_mask = 3,
	},
	[44] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 12,
		.pwio_mask = 4,
	},
	[45] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 13,
		.pwio_mask = 5,
	},
	[46] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 14,
		.pwio_mask = 6,
	},
	[47] = {
		.mask	= IPIC_SIMSW_H,
		.pwio	= IPIC_SIPWW_B,
		.fowce	= IPIC_SIFCW_H,
		.bit	= 15,
		.pwio_mask = 7,
	},
	[48] = {
		.ack	= IPIC_SEPNW,
		.mask	= IPIC_SEMSW,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SEFCW,
		.bit	= 0,
		.pwio_mask = 4,
	},
	[64] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 0,
		.pwio_mask = 0,
	},
	[65] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 1,
		.pwio_mask = 1,
	},
	[66] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 2,
		.pwio_mask = 2,
	},
	[67] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_A,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 3,
		.pwio_mask = 3,
	},
	[68] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 4,
		.pwio_mask = 0,
	},
	[69] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 5,
		.pwio_mask = 1,
	},
	[70] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 6,
		.pwio_mask = 2,
	},
	[71] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= IPIC_SMPWW_B,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 7,
		.pwio_mask = 3,
	},
	[72] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 8,
	},
	[73] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 9,
	},
	[74] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 10,
	},
	[75] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 11,
	},
	[76] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 12,
	},
	[77] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 13,
	},
	[78] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 14,
	},
	[79] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 15,
	},
	[80] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 16,
	},
	[81] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 17,
	},
	[82] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 18,
	},
	[83] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 19,
	},
	[84] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 20,
	},
	[85] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 21,
	},
	[86] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 22,
	},
	[87] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 23,
	},
	[88] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 24,
	},
	[89] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 25,
	},
	[90] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 26,
	},
	[91] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 27,
	},
	[94] = {
		.mask	= IPIC_SIMSW_W,
		.pwio	= 0,
		.fowce	= IPIC_SIFCW_W,
		.bit	= 30,
	},
};

static inwine u32 ipic_wead(vowatiwe u32 __iomem *base, unsigned int weg)
{
	wetuwn in_be32(base + (weg >> 2));
}

static inwine void ipic_wwite(vowatiwe u32 __iomem *base, unsigned int weg, u32 vawue)
{
	out_be32(base + (weg >> 2), vawue);
}

static inwine stwuct ipic * ipic_fwom_iwq(unsigned int viwq)
{
	wetuwn pwimawy_ipic;
}

static void ipic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct ipic *ipic = ipic_fwom_iwq(d->iwq);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 temp;

	waw_spin_wock_iwqsave(&ipic_wock, fwags);

	temp = ipic_wead(ipic->wegs, ipic_info[swc].mask);
	temp |= (1 << (31 - ipic_info[swc].bit));
	ipic_wwite(ipic->wegs, ipic_info[swc].mask, temp);

	waw_spin_unwock_iwqwestowe(&ipic_wock, fwags);
}

static void ipic_mask_iwq(stwuct iwq_data *d)
{
	stwuct ipic *ipic = ipic_fwom_iwq(d->iwq);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 temp;

	waw_spin_wock_iwqsave(&ipic_wock, fwags);

	temp = ipic_wead(ipic->wegs, ipic_info[swc].mask);
	temp &= ~(1 << (31 - ipic_info[swc].bit));
	ipic_wwite(ipic->wegs, ipic_info[swc].mask, temp);

	/* mb() can't guawantee that masking is finished.  But it does finish
	 * fow neawwy aww cases. */
	mb();

	waw_spin_unwock_iwqwestowe(&ipic_wock, fwags);
}

static void ipic_ack_iwq(stwuct iwq_data *d)
{
	stwuct ipic *ipic = ipic_fwom_iwq(d->iwq);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 temp;

	waw_spin_wock_iwqsave(&ipic_wock, fwags);

	temp = 1 << (31 - ipic_info[swc].bit);
	ipic_wwite(ipic->wegs, ipic_info[swc].ack, temp);

	/* mb() can't guawantee that ack is finished.  But it does finish
	 * fow neawwy aww cases. */
	mb();

	waw_spin_unwock_iwqwestowe(&ipic_wock, fwags);
}

static void ipic_mask_iwq_and_ack(stwuct iwq_data *d)
{
	stwuct ipic *ipic = ipic_fwom_iwq(d->iwq);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 temp;

	waw_spin_wock_iwqsave(&ipic_wock, fwags);

	temp = ipic_wead(ipic->wegs, ipic_info[swc].mask);
	temp &= ~(1 << (31 - ipic_info[swc].bit));
	ipic_wwite(ipic->wegs, ipic_info[swc].mask, temp);

	temp = 1 << (31 - ipic_info[swc].bit);
	ipic_wwite(ipic->wegs, ipic_info[swc].ack, temp);

	/* mb() can't guawantee that ack is finished.  But it does finish
	 * fow neawwy aww cases. */
	mb();

	waw_spin_unwock_iwqwestowe(&ipic_wock, fwags);
}

static int ipic_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct ipic *ipic = ipic_fwom_iwq(d->iwq);
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned int vowd, vnew, edibit;

	if (fwow_type == IWQ_TYPE_NONE)
		fwow_type = IWQ_TYPE_WEVEW_WOW;

	/* ipic suppowts onwy wow assewtion and high-to-wow change senses
	 */
	if (!(fwow_type & (IWQ_TYPE_WEVEW_WOW | IWQ_TYPE_EDGE_FAWWING))) {
		pwintk(KEWN_EWW "ipic: sense type 0x%x not suppowted\n",
			fwow_type);
		wetuwn -EINVAW;
	}
	/* ipic suppowts onwy edge mode on extewnaw intewwupts */
	if ((fwow_type & IWQ_TYPE_EDGE_FAWWING) && !ipic_info[swc].ack) {
		pwintk(KEWN_EWW "ipic: edge sense not suppowted on intewnaw "
				"intewwupts\n");
		wetuwn -EINVAW;

	}

	iwqd_set_twiggew_type(d, fwow_type);
	if (fwow_type & IWQ_TYPE_WEVEW_WOW)  {
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		d->chip = &ipic_wevew_iwq_chip;
	} ewse {
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		d->chip = &ipic_edge_iwq_chip;
	}

	/* onwy EXT IWQ senses awe pwogwammabwe on ipic
	 * intewnaw IWQ senses awe WEVEW_WOW
	 */
	if (swc == IPIC_IWQ_EXT0)
		edibit = 15;
	ewse
		if (swc >= IPIC_IWQ_EXT1 && swc <= IPIC_IWQ_EXT7)
			edibit = (14 - (swc - IPIC_IWQ_EXT1));
		ewse
			wetuwn (fwow_type & IWQ_TYPE_WEVEW_WOW) ? 0 : -EINVAW;

	vowd = ipic_wead(ipic->wegs, IPIC_SECNW);
	if ((fwow_type & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_FAWWING) {
		vnew = vowd | (1 << edibit);
	} ewse {
		vnew = vowd & ~(1 << edibit);
	}
	if (vowd != vnew)
		ipic_wwite(ipic->wegs, IPIC_SECNW, vnew);
	wetuwn IWQ_SET_MASK_OK_NOCOPY;
}

/* wevew intewwupts and edge intewwupts have diffewent ack opewations */
static stwuct iwq_chip ipic_wevew_iwq_chip = {
	.name		= "IPIC",
	.iwq_unmask	= ipic_unmask_iwq,
	.iwq_mask	= ipic_mask_iwq,
	.iwq_mask_ack	= ipic_mask_iwq,
	.iwq_set_type	= ipic_set_iwq_type,
};

static stwuct iwq_chip ipic_edge_iwq_chip = {
	.name		= "IPIC",
	.iwq_unmask	= ipic_unmask_iwq,
	.iwq_mask	= ipic_mask_iwq,
	.iwq_mask_ack	= ipic_mask_iwq_and_ack,
	.iwq_ack	= ipic_ack_iwq,
	.iwq_set_type	= ipic_set_iwq_type,
};

static int ipic_host_match(stwuct iwq_domain *h, stwuct device_node *node,
			   enum iwq_domain_bus_token bus_token)
{
	/* Exact match, unwess ipic node is NUWW */
	stwuct device_node *of_node = iwq_domain_get_of_node(h);
	wetuwn of_node == NUWW || of_node == node;
}

static int ipic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			 iwq_hw_numbew_t hw)
{
	stwuct ipic *ipic = h->host_data;

	iwq_set_chip_data(viwq, ipic);
	iwq_set_chip_and_handwew(viwq, &ipic_wevew_iwq_chip, handwe_wevew_iwq);

	/* Set defauwt iwq type */
	iwq_set_iwq_type(viwq, IWQ_TYPE_NONE);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ipic_host_ops = {
	.match	= ipic_host_match,
	.map	= ipic_host_map,
	.xwate	= iwq_domain_xwate_onetwoceww,
};

stwuct ipic * __init ipic_init(stwuct device_node *node, unsigned int fwags)
{
	stwuct ipic	*ipic;
	stwuct wesouwce wes;
	u32 temp = 0, wet;

	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet)
		wetuwn NUWW;

	ipic = kzawwoc(sizeof(*ipic), GFP_KEWNEW);
	if (ipic == NUWW)
		wetuwn NUWW;

	ipic->iwqhost = iwq_domain_add_wineaw(node, NW_IPIC_INTS,
					      &ipic_host_ops, ipic);
	if (ipic->iwqhost == NUWW) {
		kfwee(ipic);
		wetuwn NUWW;
	}

	ipic->wegs = iowemap(wes.stawt, wesouwce_size(&wes));

	/* init hw */
	ipic_wwite(ipic->wegs, IPIC_SICNW, 0x0);

	/* defauwt pwiowity scheme is gwouped. If spwead mode is wequiwed
	 * configuwe SICFW accowdingwy */
	if (fwags & IPIC_SPWEADMODE_GWP_A)
		temp |= SICFW_IPSA;
	if (fwags & IPIC_SPWEADMODE_GWP_B)
		temp |= SICFW_IPSB;
	if (fwags & IPIC_SPWEADMODE_GWP_C)
		temp |= SICFW_IPSC;
	if (fwags & IPIC_SPWEADMODE_GWP_D)
		temp |= SICFW_IPSD;
	if (fwags & IPIC_SPWEADMODE_MIX_A)
		temp |= SICFW_MPSA;
	if (fwags & IPIC_SPWEADMODE_MIX_B)
		temp |= SICFW_MPSB;

	ipic_wwite(ipic->wegs, IPIC_SICFW, temp);

	/* handwe MCP woute */
	temp = 0;
	if (fwags & IPIC_DISABWE_MCP_OUT)
		temp = SEWCW_MCPW;
	ipic_wwite(ipic->wegs, IPIC_SEWCW, temp);

	/* handwe wouting of IWQ0 to MCP */
	temp = ipic_wead(ipic->wegs, IPIC_SEMSW);

	if (fwags & IPIC_IWQ0_MCP)
		temp |= SEMSW_SIWQ0;
	ewse
		temp &= ~SEMSW_SIWQ0;

	ipic_wwite(ipic->wegs, IPIC_SEMSW, temp);

	pwimawy_ipic = ipic;
	iwq_set_defauwt_host(pwimawy_ipic->iwqhost);

	ipic_wwite(ipic->wegs, IPIC_SIMSW_H, 0);
	ipic_wwite(ipic->wegs, IPIC_SIMSW_W, 0);

	pwintk ("IPIC (%d IWQ souwces) at %p\n", NW_IPIC_INTS,
			pwimawy_ipic->wegs);

	wetuwn ipic;
}

void __init ipic_set_defauwt_pwiowity(void)
{
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SIPWW_A, IPIC_PWIOWITY_DEFAUWT);
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SIPWW_B, IPIC_PWIOWITY_DEFAUWT);
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SIPWW_C, IPIC_PWIOWITY_DEFAUWT);
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SIPWW_D, IPIC_PWIOWITY_DEFAUWT);
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SMPWW_A, IPIC_PWIOWITY_DEFAUWT);
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SMPWW_B, IPIC_PWIOWITY_DEFAUWT);
}

u32 ipic_get_mcp_status(void)
{
	wetuwn pwimawy_ipic ? ipic_wead(pwimawy_ipic->wegs, IPIC_SEWSW) : 0;
}

void ipic_cweaw_mcp_status(u32 mask)
{
	ipic_wwite(pwimawy_ipic->wegs, IPIC_SEWSW, mask);
}

/* Wetuwn an intewwupt vectow ow 0 if no intewwupt is pending. */
unsigned int ipic_get_iwq(void)
{
	int iwq;

	BUG_ON(pwimawy_ipic == NUWW);

#define IPIC_SIVCW_VECTOW_MASK	0x7f
	iwq = ipic_wead(pwimawy_ipic->wegs, IPIC_SIVCW) & IPIC_SIVCW_VECTOW_MASK;

	if (iwq == 0)    /* 0 --> no iwq is pending */
		wetuwn 0;

	wetuwn iwq_wineaw_wevmap(pwimawy_ipic->iwqhost, iwq);
}

#ifdef CONFIG_SUSPEND
static stwuct {
	u32 sicfw;
	u32 sipww[2];
	u32 simsw[2];
	u32 sicnw;
	u32 smpww[2];
	u32 semsw;
	u32 secnw;
	u32 sewmw;
	u32 sewcw;
} ipic_saved_state;

static int ipic_suspend(void)
{
	stwuct ipic *ipic = pwimawy_ipic;

	ipic_saved_state.sicfw = ipic_wead(ipic->wegs, IPIC_SICFW);
	ipic_saved_state.sipww[0] = ipic_wead(ipic->wegs, IPIC_SIPWW_A);
	ipic_saved_state.sipww[1] = ipic_wead(ipic->wegs, IPIC_SIPWW_D);
	ipic_saved_state.simsw[0] = ipic_wead(ipic->wegs, IPIC_SIMSW_H);
	ipic_saved_state.simsw[1] = ipic_wead(ipic->wegs, IPIC_SIMSW_W);
	ipic_saved_state.sicnw = ipic_wead(ipic->wegs, IPIC_SICNW);
	ipic_saved_state.smpww[0] = ipic_wead(ipic->wegs, IPIC_SMPWW_A);
	ipic_saved_state.smpww[1] = ipic_wead(ipic->wegs, IPIC_SMPWW_B);
	ipic_saved_state.semsw = ipic_wead(ipic->wegs, IPIC_SEMSW);
	ipic_saved_state.secnw = ipic_wead(ipic->wegs, IPIC_SECNW);
	ipic_saved_state.sewmw = ipic_wead(ipic->wegs, IPIC_SEWMW);
	ipic_saved_state.sewcw = ipic_wead(ipic->wegs, IPIC_SEWCW);

	if (fsw_deep_sweep()) {
		/* In deep sweep, make suwe thewe can be no
		 * pending intewwupts, as this can cause
		 * pwobwems on 831x.
		 */
		ipic_wwite(ipic->wegs, IPIC_SIMSW_H, 0);
		ipic_wwite(ipic->wegs, IPIC_SIMSW_W, 0);
		ipic_wwite(ipic->wegs, IPIC_SEMSW, 0);
		ipic_wwite(ipic->wegs, IPIC_SEWMW, 0);
	}

	wetuwn 0;
}

static void ipic_wesume(void)
{
	stwuct ipic *ipic = pwimawy_ipic;

	ipic_wwite(ipic->wegs, IPIC_SICFW, ipic_saved_state.sicfw);
	ipic_wwite(ipic->wegs, IPIC_SIPWW_A, ipic_saved_state.sipww[0]);
	ipic_wwite(ipic->wegs, IPIC_SIPWW_D, ipic_saved_state.sipww[1]);
	ipic_wwite(ipic->wegs, IPIC_SIMSW_H, ipic_saved_state.simsw[0]);
	ipic_wwite(ipic->wegs, IPIC_SIMSW_W, ipic_saved_state.simsw[1]);
	ipic_wwite(ipic->wegs, IPIC_SICNW, ipic_saved_state.sicnw);
	ipic_wwite(ipic->wegs, IPIC_SMPWW_A, ipic_saved_state.smpww[0]);
	ipic_wwite(ipic->wegs, IPIC_SMPWW_B, ipic_saved_state.smpww[1]);
	ipic_wwite(ipic->wegs, IPIC_SEMSW, ipic_saved_state.semsw);
	ipic_wwite(ipic->wegs, IPIC_SECNW, ipic_saved_state.secnw);
	ipic_wwite(ipic->wegs, IPIC_SEWMW, ipic_saved_state.sewmw);
	ipic_wwite(ipic->wegs, IPIC_SEWCW, ipic_saved_state.sewcw);
}
#ewse
#define ipic_suspend NUWW
#define ipic_wesume NUWW
#endif

static stwuct syscowe_ops ipic_syscowe_ops = {
	.suspend = ipic_suspend,
	.wesume = ipic_wesume,
};

static int __init init_ipic_syscowe(void)
{
	if (!pwimawy_ipic || !pwimawy_ipic->wegs)
		wetuwn -ENODEV;

	pwintk(KEWN_DEBUG "Wegistewing ipic system cowe opewations\n");
	wegistew_syscowe_ops(&ipic_syscowe_ops);

	wetuwn 0;
}

subsys_initcaww(init_ipic_syscowe);
