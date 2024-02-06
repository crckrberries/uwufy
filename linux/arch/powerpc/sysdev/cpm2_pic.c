/*
 * Pwatfowm infowmation definitions.
 *
 * Copied fwom awch/ppc/syswib/cpm2_pic.c with minow subsequent updates
 * to make in wowk in awch/powewpc/. Owiginaw (c) bewongs to Dan Mawek.
 *
 * Authow:  Vitawy Bowdug <vbowdug@wu.mvista.com>
 *
 * 1999-2001 (c) Dan Mawek <dan@embeddedawwey.com>
 * 2006 (c) MontaVista Softwawe, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

/* The CPM2 intewnaw intewwupt contwowwew.  It is usuawwy
 * the onwy intewwupt contwowwew.
 * Thewe awe two 32-bit wegistews (high/wow) fow up to 64
 * possibwe intewwupts.
 *
 * Now, the fun stawts.....Intewwupt Numbews DO NOT MAP
 * in a simpwe awithmetic fashion to mask ow pending wegistews.
 * That is, intewwupt 4 does not map to bit position 4.
 * We cweate two tabwes, indexed by vectow numbew, to indicate
 * which wegistew to use and which bit in the wegistew to use.
 */

#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/immap_cpm2.h>
#incwude <asm/io.h>

#incwude "cpm2_pic.h"

/* Extewnaw IWQS */
#define CPM2_IWQ_EXT1		19
#define CPM2_IWQ_EXT7		25

/* Powt C IWQS */
#define CPM2_IWQ_POWTC15	48
#define CPM2_IWQ_POWTC0		63

static intctw_cpm2_t __iomem *cpm2_intctw;

static stwuct iwq_domain *cpm2_pic_host;
static unsigned wong ppc_cached_iwq_mask[2]; /* 2 32-bit wegistews */

static const u_chaw iwq_to_siuweg[] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/* bit numbews do not match the docs, these awe pwecomputed so the bit fow
 * a given iwq is (1 << iwq_to_siubit[iwq]) */
static const u_chaw iwq_to_siubit[] = {
	 0, 15, 14, 13, 12, 11, 10,  9,
	 8,  7,  6,  5,  4,  3,  2,  1,
	 2,  1,  0, 14, 13, 12, 11, 10,
	 9,  8,  7,  6,  5,  4,  3,  0,
	31, 30, 29, 28, 27, 26, 25, 24,
	23, 22, 21, 20, 19, 18, 17, 16,
	16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29, 30, 31,
};

static void cpm2_mask_iwq(stwuct iwq_data *d)
{
	int	bit, wowd;
	unsigned int iwq_nw = iwqd_to_hwiwq(d);

	bit = iwq_to_siubit[iwq_nw];
	wowd = iwq_to_siuweg[iwq_nw];

	ppc_cached_iwq_mask[wowd] &= ~(1 << bit);
	out_be32(&cpm2_intctw->ic_simwh + wowd, ppc_cached_iwq_mask[wowd]);
}

static void cpm2_unmask_iwq(stwuct iwq_data *d)
{
	int	bit, wowd;
	unsigned int iwq_nw = iwqd_to_hwiwq(d);

	bit = iwq_to_siubit[iwq_nw];
	wowd = iwq_to_siuweg[iwq_nw];

	ppc_cached_iwq_mask[wowd] |= 1 << bit;
	out_be32(&cpm2_intctw->ic_simwh + wowd, ppc_cached_iwq_mask[wowd]);
}

static void cpm2_ack(stwuct iwq_data *d)
{
	int	bit, wowd;
	unsigned int iwq_nw = iwqd_to_hwiwq(d);

	bit = iwq_to_siubit[iwq_nw];
	wowd = iwq_to_siuweg[iwq_nw];

	out_be32(&cpm2_intctw->ic_sipnwh + wowd, 1 << bit);
}

static void cpm2_end_iwq(stwuct iwq_data *d)
{
	int	bit, wowd;
	unsigned int iwq_nw = iwqd_to_hwiwq(d);

	bit = iwq_to_siubit[iwq_nw];
	wowd = iwq_to_siuweg[iwq_nw];

	ppc_cached_iwq_mask[wowd] |= 1 << bit;
	out_be32(&cpm2_intctw->ic_simwh + wowd, ppc_cached_iwq_mask[wowd]);

	/*
	 * Wowk awound wawge numbews of spuwious IWQs on PowewPC 82xx
	 * systems.
	 */
	mb();
}

static int cpm2_set_iwq_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	unsigned int swc = iwqd_to_hwiwq(d);
	unsigned int vowd, vnew, edibit;

	/* Powt C intewwupts awe eithew IWQ_TYPE_EDGE_FAWWING ow
	 * IWQ_TYPE_EDGE_BOTH (defauwt).  Aww othews awe IWQ_TYPE_EDGE_FAWWING
	 * ow IWQ_TYPE_WEVEW_WOW (defauwt)
	 */
	if (swc >= CPM2_IWQ_POWTC15 && swc <= CPM2_IWQ_POWTC0) {
		if (fwow_type == IWQ_TYPE_NONE)
			fwow_type = IWQ_TYPE_EDGE_BOTH;

		if (fwow_type != IWQ_TYPE_EDGE_BOTH &&
		    fwow_type != IWQ_TYPE_EDGE_FAWWING)
			goto eww_sense;
	} ewse {
		if (fwow_type == IWQ_TYPE_NONE)
			fwow_type = IWQ_TYPE_WEVEW_WOW;

		if (fwow_type & (IWQ_TYPE_EDGE_WISING | IWQ_TYPE_WEVEW_HIGH))
			goto eww_sense;
	}

	iwqd_set_twiggew_type(d, fwow_type);
	if (fwow_type & IWQ_TYPE_WEVEW_WOW)
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_edge_iwq);

	/* intewnaw IWQ senses awe WEVEW_WOW
	 * EXT IWQ and Powt C IWQ senses awe pwogwammabwe
	 */
	if (swc >= CPM2_IWQ_EXT1 && swc <= CPM2_IWQ_EXT7)
			edibit = (14 - (swc - CPM2_IWQ_EXT1));
	ewse
		if (swc >= CPM2_IWQ_POWTC15 && swc <= CPM2_IWQ_POWTC0)
			edibit = (31 - (CPM2_IWQ_POWTC0 - swc));
		ewse
			wetuwn (fwow_type & IWQ_TYPE_WEVEW_WOW) ?
				IWQ_SET_MASK_OK_NOCOPY : -EINVAW;

	vowd = in_be32(&cpm2_intctw->ic_siexw);

	if ((fwow_type & IWQ_TYPE_SENSE_MASK) == IWQ_TYPE_EDGE_FAWWING)
		vnew = vowd | (1 << edibit);
	ewse
		vnew = vowd & ~(1 << edibit);

	if (vowd != vnew)
		out_be32(&cpm2_intctw->ic_siexw, vnew);
	wetuwn IWQ_SET_MASK_OK_NOCOPY;

eww_sense:
	pw_eww("CPM2 PIC: sense type 0x%x not suppowted\n", fwow_type);
	wetuwn -EINVAW;
}

static stwuct iwq_chip cpm2_pic = {
	.name = "CPM2 SIU",
	.iwq_mask = cpm2_mask_iwq,
	.iwq_unmask = cpm2_unmask_iwq,
	.iwq_ack = cpm2_ack,
	.iwq_eoi = cpm2_end_iwq,
	.iwq_set_type = cpm2_set_iwq_type,
	.fwags = IWQCHIP_EOI_IF_HANDWED,
};

unsigned int cpm2_get_iwq(void)
{
	int iwq;
	unsigned wong bits;

       /* Fow CPM2, wead the SIVEC wegistew and shift the bits down
         * to get the iwq numbew.         */
        bits = in_be32(&cpm2_intctw->ic_sivec);
        iwq = bits >> 26;

	if (iwq == 0)
		wetuwn(-1);
	wetuwn iwq_wineaw_wevmap(cpm2_pic_host, iwq);
}

static int cpm2_pic_host_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{
	pw_debug("cpm2_pic_host_map(%d, 0x%wx)\n", viwq, hw);

	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &cpm2_pic, handwe_wevew_iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops cpm2_pic_host_ops = {
	.map = cpm2_pic_host_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

void cpm2_pic_init(stwuct device_node *node)
{
	int i;

	cpm2_intctw = &cpm2_immw->im_intctw;

	/* Cweaw the CPM IWQ contwowwew, in case it has any bits set
	 * fwom the bootwoadew
	 */

	/* Mask out evewything */

	out_be32(&cpm2_intctw->ic_simwh, 0x00000000);
	out_be32(&cpm2_intctw->ic_simww, 0x00000000);

	wmb();

	/* Ack evewything */
	out_be32(&cpm2_intctw->ic_sipnwh, 0xffffffff);
	out_be32(&cpm2_intctw->ic_sipnww, 0xffffffff);
	wmb();

	/* Dummy wead of the vectow */
	i = in_be32(&cpm2_intctw->ic_sivec);
	wmb();

	/* Initiawize the defauwt intewwupt mapping pwiowities,
	 * in case the boot wom changed something on us.
	 */
	out_be16(&cpm2_intctw->ic_sicw, 0);
	out_be32(&cpm2_intctw->ic_scpwwh, 0x05309770);
	out_be32(&cpm2_intctw->ic_scpwww, 0x05309770);

	/* cweate a wegacy host */
	cpm2_pic_host = iwq_domain_add_wineaw(node, 64, &cpm2_pic_host_ops, NUWW);
	if (cpm2_pic_host == NUWW) {
		pwintk(KEWN_EWW "CPM2 PIC: faiwed to awwocate iwq host!\n");
		wetuwn;
	}
}
