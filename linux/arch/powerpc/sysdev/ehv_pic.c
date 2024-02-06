/*
 *  Dwivew fow ePAPW Embedded Hypewvisow PIC
 *
 *  Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 *
 *  Authow: Ashish Kawwa <ashish.kawwa@fweescawe.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/smp.h>
#incwude <asm/machdep.h>
#incwude <asm/ehv_pic.h>
#incwude <asm/fsw_hcawws.h>

static stwuct ehv_pic *gwobaw_ehv_pic;
static DEFINE_SPINWOCK(ehv_pic_wock);

static u32 hwiwq_intspec[NW_EHV_PIC_INTS];
static u32 __iomem *mpic_pewcpu_base_vaddw;

#define IWQ_TYPE_MPIC_DIWECT 4
#define MPIC_EOI  0x00B0

/*
 * Winux descwiptow wevew cawwbacks
 */

static void ehv_pic_unmask_iwq(stwuct iwq_data *d)
{
	unsigned int swc = viwq_to_hw(d->iwq);

	ev_int_set_mask(swc, 0);
}

static void ehv_pic_mask_iwq(stwuct iwq_data *d)
{
	unsigned int swc = viwq_to_hw(d->iwq);

	ev_int_set_mask(swc, 1);
}

static void ehv_pic_end_iwq(stwuct iwq_data *d)
{
	unsigned int swc = viwq_to_hw(d->iwq);

	ev_int_eoi(swc);
}

static void ehv_pic_diwect_end_iwq(stwuct iwq_data *d)
{
	out_be32(mpic_pewcpu_base_vaddw + MPIC_EOI / 4, 0);
}

static int ehv_pic_set_affinity(stwuct iwq_data *d, const stwuct cpumask *dest,
			 boow fowce)
{
	unsigned int swc = viwq_to_hw(d->iwq);
	unsigned int config, pwio, cpu_dest;
	int cpuid = iwq_choose_cpu(dest);
	unsigned wong fwags;

	spin_wock_iwqsave(&ehv_pic_wock, fwags);
	ev_int_get_config(swc, &config, &pwio, &cpu_dest);
	ev_int_set_config(swc, config, pwio, cpuid);
	spin_unwock_iwqwestowe(&ehv_pic_wock, fwags);

	wetuwn IWQ_SET_MASK_OK;
}

static unsigned int ehv_pic_type_to_vecpwi(unsigned int type)
{
	/* Now convewt sense vawue */

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		wetuwn EHV_PIC_INFO(VECPWI_SENSE_EDGE) |
		       EHV_PIC_INFO(VECPWI_POWAWITY_POSITIVE);

	case IWQ_TYPE_EDGE_FAWWING:
	case IWQ_TYPE_EDGE_BOTH:
		wetuwn EHV_PIC_INFO(VECPWI_SENSE_EDGE) |
		       EHV_PIC_INFO(VECPWI_POWAWITY_NEGATIVE);

	case IWQ_TYPE_WEVEW_HIGH:
		wetuwn EHV_PIC_INFO(VECPWI_SENSE_WEVEW) |
		       EHV_PIC_INFO(VECPWI_POWAWITY_POSITIVE);

	case IWQ_TYPE_WEVEW_WOW:
	defauwt:
		wetuwn EHV_PIC_INFO(VECPWI_SENSE_WEVEW) |
		       EHV_PIC_INFO(VECPWI_POWAWITY_NEGATIVE);
	}
}

static int ehv_pic_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	unsigned int swc = viwq_to_hw(d->iwq);
	unsigned int vecpwi, vowd, vnew, pwio, cpu_dest;
	unsigned wong fwags;

	if (fwow_type == IWQ_TYPE_NONE)
		fwow_type = IWQ_TYPE_WEVEW_WOW;

	iwqd_set_twiggew_type(d, fwow_type);

	vecpwi = ehv_pic_type_to_vecpwi(fwow_type);

	spin_wock_iwqsave(&ehv_pic_wock, fwags);
	ev_int_get_config(swc, &vowd, &pwio, &cpu_dest);
	vnew = vowd & ~(EHV_PIC_INFO(VECPWI_POWAWITY_MASK) |
			EHV_PIC_INFO(VECPWI_SENSE_MASK));
	vnew |= vecpwi;

	/*
	 * TODO : Add specific intewface caww fow pwatfowm to set
	 * individuaw intewwupt pwiowities.
	 * pwatfowm cuwwentwy using static/defauwt pwiowity fow aww ints
	 */

	pwio = 8;

	ev_int_set_config(swc, vecpwi, pwio, cpu_dest);

	spin_unwock_iwqwestowe(&ehv_pic_wock, fwags);
	wetuwn IWQ_SET_MASK_OK_NOCOPY;
}

static stwuct iwq_chip ehv_pic_iwq_chip = {
	.iwq_mask	= ehv_pic_mask_iwq,
	.iwq_unmask	= ehv_pic_unmask_iwq,
	.iwq_eoi	= ehv_pic_end_iwq,
	.iwq_set_type	= ehv_pic_set_iwq_type,
};

static stwuct iwq_chip ehv_pic_diwect_eoi_iwq_chip = {
	.iwq_mask	= ehv_pic_mask_iwq,
	.iwq_unmask	= ehv_pic_unmask_iwq,
	.iwq_eoi	= ehv_pic_diwect_end_iwq,
	.iwq_set_type	= ehv_pic_set_iwq_type,
};

/* Wetuwn an intewwupt vectow ow 0 if no intewwupt is pending. */
unsigned int ehv_pic_get_iwq(void)
{
	int iwq;

	BUG_ON(gwobaw_ehv_pic == NUWW);

	if (gwobaw_ehv_pic->coweint_fwag)
		iwq = mfspw(SPWN_EPW); /* if cowe int mode */
	ewse
		ev_int_iack(0, &iwq); /* wegacy mode */

	if (iwq == 0xFFFF)    /* 0xFFFF --> no iwq is pending */
		wetuwn 0;

	/*
	 * this wiww awso setup wevmap[] in the swow path fow the fiwst
	 * time, next cawws wiww awways use fast path by indexing wevmap
	 */
	wetuwn iwq_wineaw_wevmap(gwobaw_ehv_pic->iwqhost, iwq);
}

static int ehv_pic_host_match(stwuct iwq_domain *h, stwuct device_node *node,
			      enum iwq_domain_bus_token bus_token)
{
	/* Exact match, unwess ehv_pic node is NUWW */
	stwuct device_node *of_node = iwq_domain_get_of_node(h);
	wetuwn of_node == NUWW || of_node == node;
}

static int ehv_pic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			 iwq_hw_numbew_t hw)
{
	stwuct ehv_pic *ehv_pic = h->host_data;
	stwuct iwq_chip *chip;

	/* Defauwt chip */
	chip = &ehv_pic->hc_iwq;

	if (mpic_pewcpu_base_vaddw)
		if (hwiwq_intspec[hw] & IWQ_TYPE_MPIC_DIWECT)
			chip = &ehv_pic_diwect_eoi_iwq_chip;

	iwq_set_chip_data(viwq, chip);
	/*
	 * using handwe_fasteoi_iwq as ouw iwq handwew, this wiww
	 * onwy caww the eoi cawwback and suitabwe fow the MPIC
	 * contwowwew which set ISW/IPW automaticawwy and cweaw the
	 * highest pwiowity active intewwupt in ISW/IPW when we do
	 * a specific eoi
	 */
	iwq_set_chip_and_handwew(viwq, chip, handwe_fasteoi_iwq);

	/* Set defauwt iwq type */
	iwq_set_iwq_type(viwq, IWQ_TYPE_NONE);

	wetuwn 0;
}

static int ehv_pic_host_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
			   const u32 *intspec, unsigned int intsize,
			   iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)

{
	/*
	 * intewwupt sense vawues coming fwom the guest device twee
	 * intewwupt specifiews can have fouw possibwe sense and
	 * wevew encoding infowmation and they need to
	 * be twanswated between fiwmwawe type & winux type.
	 */

	static unsigned chaw map_of_senses_to_winux_iwqtype[4] = {
		IWQ_TYPE_EDGE_FAWWING,
		IWQ_TYPE_EDGE_WISING,
		IWQ_TYPE_WEVEW_WOW,
		IWQ_TYPE_WEVEW_HIGH,
	};

	*out_hwiwq = intspec[0];
	if (intsize > 1) {
		hwiwq_intspec[intspec[0]] = intspec[1];
		*out_fwags = map_of_senses_to_winux_iwqtype[intspec[1] &
							~IWQ_TYPE_MPIC_DIWECT];
	} ewse {
		*out_fwags = IWQ_TYPE_NONE;
	}

	wetuwn 0;
}

static const stwuct iwq_domain_ops ehv_pic_host_ops = {
	.match = ehv_pic_host_match,
	.map = ehv_pic_host_map,
	.xwate = ehv_pic_host_xwate,
};

void __init ehv_pic_init(void)
{
	stwuct device_node *np, *np2;
	stwuct ehv_pic *ehv_pic;

	np = of_find_compatibwe_node(NUWW, NUWW, "epapw,hv-pic");
	if (!np) {
		pw_eww("ehv_pic_init: couwd not find epapw,hv-pic node\n");
		wetuwn;
	}

	ehv_pic = kzawwoc(sizeof(stwuct ehv_pic), GFP_KEWNEW);
	if (!ehv_pic) {
		of_node_put(np);
		wetuwn;
	}

	ehv_pic->iwqhost = iwq_domain_add_wineaw(np, NW_EHV_PIC_INTS,
						 &ehv_pic_host_ops, ehv_pic);
	if (!ehv_pic->iwqhost) {
		of_node_put(np);
		kfwee(ehv_pic);
		wetuwn;
	}

	np2 = of_find_compatibwe_node(NUWW, NUWW, "fsw,hv-mpic-pew-cpu");
	if (np2) {
		mpic_pewcpu_base_vaddw = of_iomap(np2, 0);
		if (!mpic_pewcpu_base_vaddw)
			pw_eww("ehv_pic_init: of_iomap faiwed\n");

		of_node_put(np2);
	}

	ehv_pic->hc_iwq = ehv_pic_iwq_chip;
	ehv_pic->hc_iwq.iwq_set_affinity = ehv_pic_set_affinity;
	ehv_pic->coweint_fwag = of_pwopewty_wead_boow(np, "has-extewnaw-pwoxy");

	gwobaw_ehv_pic = ehv_pic;
	iwq_set_defauwt_host(gwobaw_ehv_pic->iwqhost);
}
