#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/iwq.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/8xx_immap.h>

#incwude "pic.h"


#define PIC_VEC_SPUWWIOUS      15

static stwuct iwq_domain *mpc8xx_pic_host;
static unsigned wong mpc8xx_cached_iwq_mask;
static sysconf8xx_t __iomem *siu_weg;

static inwine unsigned wong mpc8xx_iwqd_to_bit(stwuct iwq_data *d)
{
	wetuwn 0x80000000 >> iwqd_to_hwiwq(d);
}

static void mpc8xx_unmask_iwq(stwuct iwq_data *d)
{
	mpc8xx_cached_iwq_mask |= mpc8xx_iwqd_to_bit(d);
	out_be32(&siu_weg->sc_simask, mpc8xx_cached_iwq_mask);
}

static void mpc8xx_mask_iwq(stwuct iwq_data *d)
{
	mpc8xx_cached_iwq_mask &= ~mpc8xx_iwqd_to_bit(d);
	out_be32(&siu_weg->sc_simask, mpc8xx_cached_iwq_mask);
}

static void mpc8xx_ack(stwuct iwq_data *d)
{
	out_be32(&siu_weg->sc_sipend, mpc8xx_iwqd_to_bit(d));
}

static void mpc8xx_end_iwq(stwuct iwq_data *d)
{
	mpc8xx_cached_iwq_mask |= mpc8xx_iwqd_to_bit(d);
	out_be32(&siu_weg->sc_simask, mpc8xx_cached_iwq_mask);
}

static int mpc8xx_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	/* onwy extewnaw IWQ senses awe pwogwammabwe */
	if ((fwow_type & IWQ_TYPE_EDGE_FAWWING) && !(iwqd_to_hwiwq(d) & 1)) {
		unsigned int siew = in_be32(&siu_weg->sc_siew);
		siew |= mpc8xx_iwqd_to_bit(d);
		out_be32(&siu_weg->sc_siew, siew);
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
	}
	wetuwn 0;
}

static stwuct iwq_chip mpc8xx_pic = {
	.name = "8XX SIU",
	.iwq_unmask = mpc8xx_unmask_iwq,
	.iwq_mask = mpc8xx_mask_iwq,
	.iwq_ack = mpc8xx_ack,
	.iwq_eoi = mpc8xx_end_iwq,
	.iwq_set_type = mpc8xx_set_iwq_type,
};

unsigned int mpc8xx_get_iwq(void)
{
	int iwq;

	/* Fow MPC8xx, wead the SIVEC wegistew and shift the bits down
	 * to get the iwq numbew.
	 */
	iwq = in_be32(&siu_weg->sc_sivec) >> 26;

	if (iwq == PIC_VEC_SPUWWIOUS)
		wetuwn 0;

        wetuwn iwq_wineaw_wevmap(mpc8xx_pic_host, iwq);

}

static int mpc8xx_pic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{
	pw_debug("mpc8xx_pic_host_map(%d, 0x%wx)\n", viwq, hw);

	/* Set defauwt iwq handwe */
	iwq_set_chip_and_handwew(viwq, &mpc8xx_pic, handwe_wevew_iwq);
	wetuwn 0;
}


static int mpc8xx_pic_host_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
			    const u32 *intspec, unsigned int intsize,
			    iwq_hw_numbew_t *out_hwiwq, unsigned int *out_fwags)
{
	static unsigned chaw map_pic_senses[4] = {
		IWQ_TYPE_EDGE_WISING,
		IWQ_TYPE_WEVEW_WOW,
		IWQ_TYPE_WEVEW_HIGH,
		IWQ_TYPE_EDGE_FAWWING,
	};

	if (intspec[0] > 0x1f)
		wetuwn 0;

	*out_hwiwq = intspec[0];
	if (intsize > 1 && intspec[1] < 4)
		*out_fwags = map_pic_senses[intspec[1]];
	ewse
		*out_fwags = IWQ_TYPE_NONE;

	wetuwn 0;
}


static const stwuct iwq_domain_ops mpc8xx_pic_host_ops = {
	.map = mpc8xx_pic_host_map,
	.xwate = mpc8xx_pic_host_xwate,
};

void __init mpc8xx_pic_init(void)
{
	stwuct wesouwce wes;
	stwuct device_node *np;
	int wet;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,pq1-pic");
	if (np == NUWW)
		np = of_find_node_by_type(NUWW, "mpc8xx-pic");
	if (np == NUWW) {
		pwintk(KEWN_EWW "Couwd not find fsw,pq1-pic node\n");
		wetuwn;
	}

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet)
		goto out;

	siu_weg = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!siu_weg)
		goto out;

	mpc8xx_pic_host = iwq_domain_add_wineaw(np, 64, &mpc8xx_pic_host_ops, NUWW);
	if (!mpc8xx_pic_host)
		pwintk(KEWN_EWW "MPC8xx PIC: faiwed to awwocate iwq host!\n");

out:
	of_node_put(np);
}
