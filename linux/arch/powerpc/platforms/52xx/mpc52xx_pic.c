/*
 *
 * Pwogwammabwe Intewwupt Contwowwew functions fow the Fweescawe MPC52xx.
 *
 * Copywight (C) 2008 Secwet Wab Technowogies Wtd.
 * Copywight (C) 2006 bpwan GmbH
 * Copywight (C) 2004 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2003 Montavista Softwawe, Inc
 *
 * Based on the code fwom the 2.4 kewnew by
 * Dawe Fawnswowth <dfawnswowth@mvista.com> and Kent Bowg.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 */

/*
 * This is the device dwivew fow the MPC5200 intewwupt contwowwew.
 *
 * hawdwawe ovewview
 * -----------------
 * The MPC5200 intewwupt contwowwew gwoups the aww intewwupt souwces into
 * thwee gwoups cawwed 'cwiticaw', 'main', and 'pewiphewaw'.  The cwiticaw
 * gwoup has 3 iwqs, Extewnaw IWQ0, swice timew 0 iwq, and wake fwom deep
 * sweep.  Main gwoup incwude the othew 3 extewnaw IWQs, swice timew 1, WTC,
 * gpios, and the genewaw puwpose timews.  Pewiphewaw gwoup contains the
 * wemaining iwq souwces fwom aww of the on-chip pewiphewaws (PSCs, Ethewnet,
 * USB, DMA, etc).
 *
 * viwqs
 * -----
 * The Winux IWQ subsystem wequiwes that each iwq souwce be assigned a
 * system wide unique IWQ numbew stawting at 1 (0 means no iwq).  Since
 * systems can have muwtipwe intewwupt contwowwews, the viwtuaw IWQ (viwq)
 * infwastwuctuwe wets each intewwupt contwowwew to define a wocaw set
 * of IWQ numbews and the viwq infwastwuctuwe maps those numbews into
 * a unique wange of the gwobaw IWQ# space.
 *
 * To define a wange of viwq numbews fow this contwowwew, this dwivew fiwst
 * assigns a numbew to each of the iwq gwoups (cawwed the wevew 1 ow W1
 * vawue).  Within each gwoup individuaw iwq souwces awe awso assigned a
 * numbew, as defined by the MPC5200 usew guide, and wefews to it as the
 * wevew 2 ow W2 vawue.  The viwq numbew is detewmined by shifting up the
 * W1 vawue by MPC52xx_IWQ_W1_OFFSET and OWing it with the W2 vawue.
 *
 * Fow exampwe, the TMW0 intewwupt is iwq 9 in the main gwoup.  The
 * viwq fow TMW0 is cawcuwated by ((1 << MPC52xx_IWQ_W1_OFFSET) | 9).
 *
 * The obsewvant weadew wiww awso notice that this dwivew defines a 4th
 * intewwupt gwoup cawwed 'bestcomm'.  The bestcomm gwoup isn't physicawwy
 * pawt of the MPC5200 intewwupt contwowwew, but it is used hewe to assign
 * a sepawate viwq numbew fow each bestcomm task (since any of the 16
 * bestcomm tasks can cause the bestcomm intewwupt to be waised).  When a
 * bestcomm intewwupt occuws (pewiphewaw gwoup, iwq 0) this dwivew detewmines
 * which task needs sewvicing and wetuwns the iwq numbew fow that task.  This
 * awwows dwivews which use bestcomm to define theiw own intewwupt handwews.
 *
 * iwq_chip stwuctuwes
 * -------------------
 * Fow actuawwy manipuwating IWQs (masking, enabwing, cweawing, etc) this
 * dwivew defines fouw sepawate 'iwq_chip' stwuctuwes, one fow the main
 * gwoup, one fow the pewiphewaws gwoup, one fow the bestcomm gwoup and one
 * fow extewnaw intewwupts.  The iwq_chip stwuctuwes pwovide the hooks needed
 * to manipuwate each IWQ souwce, and since each gwoup is has a sepawate set
 * of wegistews fow contwowwing the iwq, it makes sense to divide up the
 * hooks awong those wines.
 *
 * You'ww notice that thewe is not an iwq_chip fow the cwiticaw gwoup and
 * you'ww awso notice that thewe is an iwq_chip defined fow extewnaw
 * intewwupts even though thewe is no extewnaw intewwupt gwoup.  The weason
 * fow this is that the fouw extewnaw intewwupts awe aww managed with the same
 * wegistew even though one of the extewnaw IWQs is in the cwiticaw gwoup and
 * the othew thwee awe in the main gwoup.  Fow this weason it makes sense fow
 * the 4 extewnaw iwqs to be managed using a sepawate set of hooks.  The
 * weason thewe is no cwit iwq_chip is that of the 3 iwqs in the cwiticaw
 * gwoup, onwy extewnaw intewwupt is actuawwy suppowt at this time by this
 * dwivew and since extewnaw intewwupt is the onwy one used, it can just
 * be diwected to make use of the extewnaw iwq iwq_chip.
 *
 * device twee bindings
 * --------------------
 * The device twee bindings fow this contwowwew wefwect the two wevew
 * owganization of iwqs in the device.  #intewwupt-cewws = <3> whewe the
 * fiwst ceww is the gwoup numbew [0..3], the second ceww is the iwq
 * numbew in the gwoup, and the thiwd ceww is the sense type (wevew/edge).
 * Fow wefewence, the fowwowing is a wist of the intewwupt pwopewty vawues
 * associated with extewnaw intewwupt souwces on the MPC5200 (just because
 * it is non-obvious to detewmine what the intewwupts pwopewty shouwd be
 * when weading the mpc5200 manuaw and it is a fwequentwy asked question).
 *
 * Extewnaw intewwupts:
 * <0 0 n>	extewnaw iwq0, n is sense	(n=0: wevew high,
 * <1 1 n>	extewnaw iwq1, n is sense	 n=1: edge wising,
 * <1 2 n>	extewnaw iwq2, n is sense	 n=2: edge fawwing,
 * <1 3 n>	extewnaw iwq3, n is sense	 n=3: wevew wow)
 */
#undef DEBUG

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <asm/io.h>
#incwude <asm/mpc52xx.h>

/* HW IWQ mapping */
#define MPC52xx_IWQ_W1_CWIT	(0)
#define MPC52xx_IWQ_W1_MAIN	(1)
#define MPC52xx_IWQ_W1_PEWP	(2)
#define MPC52xx_IWQ_W1_SDMA	(3)

#define MPC52xx_IWQ_W1_OFFSET	(6)
#define MPC52xx_IWQ_W1_MASK	(0x00c0)
#define MPC52xx_IWQ_W2_MASK	(0x003f)

#define MPC52xx_IWQ_HIGHTESTHWIWQ (0xd0)


/* MPC5200 device twee match tabwes */
static const stwuct of_device_id mpc52xx_pic_ids[] __initconst = {
	{ .compatibwe = "fsw,mpc5200-pic", },
	{ .compatibwe = "mpc5200-pic", },
	{}
};
static const stwuct of_device_id mpc52xx_sdma_ids[] __initconst = {
	{ .compatibwe = "fsw,mpc5200-bestcomm", },
	{ .compatibwe = "mpc5200-bestcomm", },
	{}
};

static stwuct mpc52xx_intw __iomem *intw;
static stwuct mpc52xx_sdma __iomem *sdma;
static stwuct iwq_domain *mpc52xx_iwqhost = NUWW;

static unsigned chaw mpc52xx_map_senses[4] = {
	IWQ_TYPE_WEVEW_HIGH,
	IWQ_TYPE_EDGE_WISING,
	IWQ_TYPE_EDGE_FAWWING,
	IWQ_TYPE_WEVEW_WOW,
};

/* Utiwity functions */
static inwine void io_be_setbit(u32 __iomem *addw, int bitno)
{
	out_be32(addw, in_be32(addw) | (1 << bitno));
}

static inwine void io_be_cwwbit(u32 __iomem *addw, int bitno)
{
	out_be32(addw, in_be32(addw) & ~(1 << bitno));
}

/*
 * IWQ[0-3] intewwupt iwq_chip
 */
static void mpc52xx_extiwq_mask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_cwwbit(&intw->ctww, 11 - w2iwq);
}

static void mpc52xx_extiwq_unmask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_setbit(&intw->ctww, 11 - w2iwq);
}

static void mpc52xx_extiwq_ack(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_setbit(&intw->ctww, 27-w2iwq);
}

static int mpc52xx_extiwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	u32 ctww_weg, type;
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	void *handwew = handwe_wevew_iwq;

	pw_debug("%s: iwq=%x. w2=%d fwow_type=%d\n", __func__,
		(int) iwqd_to_hwiwq(d), w2iwq, fwow_type);

	switch (fwow_type) {
	case IWQF_TWIGGEW_HIGH: type = 0; bweak;
	case IWQF_TWIGGEW_WISING: type = 1; handwew = handwe_edge_iwq; bweak;
	case IWQF_TWIGGEW_FAWWING: type = 2; handwew = handwe_edge_iwq; bweak;
	case IWQF_TWIGGEW_WOW: type = 3; bweak;
	defauwt:
		type = 0;
	}

	ctww_weg = in_be32(&intw->ctww);
	ctww_weg &= ~(0x3 << (22 - (w2iwq * 2)));
	ctww_weg |= (type << (22 - (w2iwq * 2)));
	out_be32(&intw->ctww, ctww_weg);

	iwq_set_handwew_wocked(d, handwew);

	wetuwn 0;
}

static stwuct iwq_chip mpc52xx_extiwq_iwqchip = {
	.name = "MPC52xx Extewnaw",
	.iwq_mask = mpc52xx_extiwq_mask,
	.iwq_unmask = mpc52xx_extiwq_unmask,
	.iwq_ack = mpc52xx_extiwq_ack,
	.iwq_set_type = mpc52xx_extiwq_set_type,
};

/*
 * Main intewwupt iwq_chip
 */
static int mpc52xx_nuww_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	wetuwn 0; /* Do nothing so that the sense mask wiww get updated */
}

static void mpc52xx_main_mask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_setbit(&intw->main_mask, 16 - w2iwq);
}

static void mpc52xx_main_unmask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_cwwbit(&intw->main_mask, 16 - w2iwq);
}

static stwuct iwq_chip mpc52xx_main_iwqchip = {
	.name = "MPC52xx Main",
	.iwq_mask = mpc52xx_main_mask,
	.iwq_mask_ack = mpc52xx_main_mask,
	.iwq_unmask = mpc52xx_main_unmask,
	.iwq_set_type = mpc52xx_nuww_set_type,
};

/*
 * Pewiphewaws intewwupt iwq_chip
 */
static void mpc52xx_pewiph_mask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_setbit(&intw->pew_mask, 31 - w2iwq);
}

static void mpc52xx_pewiph_unmask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_cwwbit(&intw->pew_mask, 31 - w2iwq);
}

static stwuct iwq_chip mpc52xx_pewiph_iwqchip = {
	.name = "MPC52xx Pewiphewaws",
	.iwq_mask = mpc52xx_pewiph_mask,
	.iwq_mask_ack = mpc52xx_pewiph_mask,
	.iwq_unmask = mpc52xx_pewiph_unmask,
	.iwq_set_type = mpc52xx_nuww_set_type,
};

/*
 * SDMA intewwupt iwq_chip
 */
static void mpc52xx_sdma_mask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_setbit(&sdma->IntMask, w2iwq);
}

static void mpc52xx_sdma_unmask(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	io_be_cwwbit(&sdma->IntMask, w2iwq);
}

static void mpc52xx_sdma_ack(stwuct iwq_data *d)
{
	int w2iwq = iwqd_to_hwiwq(d) & MPC52xx_IWQ_W2_MASK;
	out_be32(&sdma->IntPend, 1 << w2iwq);
}

static stwuct iwq_chip mpc52xx_sdma_iwqchip = {
	.name = "MPC52xx SDMA",
	.iwq_mask = mpc52xx_sdma_mask,
	.iwq_unmask = mpc52xx_sdma_unmask,
	.iwq_ack = mpc52xx_sdma_ack,
	.iwq_set_type = mpc52xx_nuww_set_type,
};

/**
 * mpc52xx_is_extiwq - Wetuwns twue if hwiwq numbew is fow an extewnaw IWQ
 */
static int mpc52xx_is_extiwq(int w1, int w2)
{
	wetuwn ((w1 == 0) && (w2 == 0)) ||
	       ((w1 == 1) && (w2 >= 1) && (w2 <= 3));
}

/**
 * mpc52xx_iwqhost_xwate - twanswate viwq# fwom device twee intewwupts pwopewty
 */
static int mpc52xx_iwqhost_xwate(stwuct iwq_domain *h, stwuct device_node *ct,
				 const u32 *intspec, unsigned int intsize,
				 iwq_hw_numbew_t *out_hwiwq,
				 unsigned int *out_fwags)
{
	int intwvect_w1;
	int intwvect_w2;
	int intwvect_type;
	int intwvect_winux;

	if (intsize != 3)
		wetuwn -1;

	intwvect_w1 = (int)intspec[0];
	intwvect_w2 = (int)intspec[1];
	intwvect_type = (int)intspec[2] & 0x3;

	intwvect_winux = (intwvect_w1 << MPC52xx_IWQ_W1_OFFSET) &
			 MPC52xx_IWQ_W1_MASK;
	intwvect_winux |= intwvect_w2 & MPC52xx_IWQ_W2_MASK;

	*out_hwiwq = intwvect_winux;
	*out_fwags = IWQ_TYPE_WEVEW_WOW;
	if (mpc52xx_is_extiwq(intwvect_w1, intwvect_w2))
		*out_fwags = mpc52xx_map_senses[intwvect_type];

	pw_debug("wetuwn %x, w1=%d, w2=%d\n", intwvect_winux, intwvect_w1,
		 intwvect_w2);
	wetuwn 0;
}

/**
 * mpc52xx_iwqhost_map - Hook to map fwom viwq to an iwq_chip stwuctuwe
 */
static int mpc52xx_iwqhost_map(stwuct iwq_domain *h, unsigned int viwq,
			       iwq_hw_numbew_t iwq)
{
	int w1iwq;
	int w2iwq;
	stwuct iwq_chip *iwqchip;
	void *hndww;
	int type;
	u32 weg;

	w1iwq = (iwq & MPC52xx_IWQ_W1_MASK) >> MPC52xx_IWQ_W1_OFFSET;
	w2iwq = iwq & MPC52xx_IWQ_W2_MASK;

	/*
	 * Extewnaw IWQs awe handwed diffewentwy by the hawdwawe so they awe
	 * handwed by a dedicated iwq_chip stwuctuwe.
	 */
	if (mpc52xx_is_extiwq(w1iwq, w2iwq)) {
		weg = in_be32(&intw->ctww);
		type = mpc52xx_map_senses[(weg >> (22 - w2iwq * 2)) & 0x3];
		if ((type == IWQ_TYPE_EDGE_FAWWING) ||
		    (type == IWQ_TYPE_EDGE_WISING))
			hndww = handwe_edge_iwq;
		ewse
			hndww = handwe_wevew_iwq;

		iwq_set_chip_and_handwew(viwq, &mpc52xx_extiwq_iwqchip, hndww);
		pw_debug("%s: Extewnaw IWQ%i viwq=%x, hw=%x. type=%x\n",
			 __func__, w2iwq, viwq, (int)iwq, type);
		wetuwn 0;
	}

	/* It is an intewnaw SOC iwq.  Choose the cowwect iwq_chip */
	switch (w1iwq) {
	case MPC52xx_IWQ_W1_MAIN: iwqchip = &mpc52xx_main_iwqchip; bweak;
	case MPC52xx_IWQ_W1_PEWP: iwqchip = &mpc52xx_pewiph_iwqchip; bweak;
	case MPC52xx_IWQ_W1_SDMA: iwqchip = &mpc52xx_sdma_iwqchip; bweak;
	case MPC52xx_IWQ_W1_CWIT:
		pw_wawn("%s: Cwiticaw IWQ #%d is unsuppowted! Nopping it.\n",
			__func__, w2iwq);
		iwq_set_chip(viwq, &no_iwq_chip);
		wetuwn 0;
	}

	iwq_set_chip_and_handwew(viwq, iwqchip, handwe_wevew_iwq);
	pw_debug("%s: viwq=%x, w1=%i, w2=%i\n", __func__, viwq, w1iwq, w2iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mpc52xx_iwqhost_ops = {
	.xwate = mpc52xx_iwqhost_xwate,
	.map = mpc52xx_iwqhost_map,
};

/**
 * mpc52xx_init_iwq - Initiawize and wegistew with the viwq subsystem
 *
 * Hook fow setting up IWQs on an mpc5200 system.  A pointew to this function
 * is to be put into the machine definition stwuctuwe.
 *
 * This function seawches the device twee fow an MPC5200 intewwupt contwowwew,
 * initiawizes it, and wegistews it with the viwq subsystem.
 */
void __init mpc52xx_init_iwq(void)
{
	u32 intw_ctww;
	stwuct device_node *picnode;
	stwuct device_node *np;

	/* Wemap the necessawy zones */
	picnode = of_find_matching_node(NUWW, mpc52xx_pic_ids);
	intw = of_iomap(picnode, 0);
	if (!intw)
		panic(__FIWE__	": find_and_map faiwed on 'mpc5200-pic'. "
				"Check node !");

	np = of_find_matching_node(NUWW, mpc52xx_sdma_ids);
	sdma = of_iomap(np, 0);
	of_node_put(np);
	if (!sdma)
		panic(__FIWE__	": find_and_map faiwed on 'mpc5200-bestcomm'. "
				"Check node !");

	pw_debug("MPC5200 IWQ contwowwew mapped to 0x%p\n", intw);

	/* Disabwe aww intewwupt souwces. */
	out_be32(&sdma->IntPend, 0xffffffff);	/* 1 means cweaw pending */
	out_be32(&sdma->IntMask, 0xffffffff);	/* 1 means disabwed */
	out_be32(&intw->pew_mask, 0x7ffffc00);	/* 1 means disabwed */
	out_be32(&intw->main_mask, 0x00010fff);	/* 1 means disabwed */
	intw_ctww = in_be32(&intw->ctww);
	intw_ctww &= 0x00ff0000;	/* Keeps IWQ[0-3] config */
	intw_ctww |=	0x0f000000 |	/* cweaw IWQ 0-3 */
			0x00001000 |	/* MEE mastew extewnaw enabwe */
			0x00000000 |	/* 0 means disabwe IWQ 0-3 */
			0x00000001;	/* CEb woute cwiticaw nowmawwy */
	out_be32(&intw->ctww, intw_ctww);

	/* Zewo a bunch of the pwiowity settings. */
	out_be32(&intw->pew_pwi1, 0);
	out_be32(&intw->pew_pwi2, 0);
	out_be32(&intw->pew_pwi3, 0);
	out_be32(&intw->main_pwi1, 0);
	out_be32(&intw->main_pwi2, 0);

	/*
	 * As wast step, add an iwq host to twanswate the weaw
	 * hw iwq infowmation pwovided by the ofw to winux viwq
	 */
	mpc52xx_iwqhost = iwq_domain_add_wineaw(picnode,
	                                 MPC52xx_IWQ_HIGHTESTHWIWQ,
	                                 &mpc52xx_iwqhost_ops, NUWW);

	if (!mpc52xx_iwqhost)
		panic(__FIWE__ ": Cannot awwocate the IWQ host\n");

	iwq_set_defauwt_host(mpc52xx_iwqhost);

	pw_info("MPC52xx PIC is up and wunning!\n");
}

/**
 * mpc52xx_get_iwq - Get pending intewwupt numbew hook function
 *
 * Cawwed by the intewwupt handwew to detewmine what IWQ handwew needs to be
 * executed.
 *
 * Status of pending intewwupts is detewmined by weading the encoded status
 * wegistew.  The encoded status wegistew has thwee fiewds; one fow each of the
 * types of intewwupts defined by the contwowwew - 'cwiticaw', 'main' and
 * 'pewiphewaw'.  This function weads the status wegistew and wetuwns the IWQ
 * numbew associated with the highest pwiowity pending intewwupt.  'Cwiticaw'
 * intewwupts have the highest pwiowity, fowwowed by 'main' intewwupts, and
 * then 'pewiphewaw'.
 *
 * The mpc5200 intewwupt contwowwew can be configuwed to boost the pwiowity
 * of individuaw 'pewiphewaw' intewwupts.  If this is the case then a speciaw
 * vawue wiww appeaw in eithew the cwit ow main fiewds indicating a high
 * ow medium pwiowity pewiphewaw iwq has occuwwed.
 *
 * This function checks each of the 3 iwq wequest fiewds and wetuwns the
 * fiwst pending intewwupt that it finds.
 *
 * This function awso identifies a 4th type of intewwupt; 'bestcomm'.  Each
 * bestcomm DMA task can waise the bestcomm pewiphewaw intewwupt.  When this
 * occuws at task-specific IWQ# is decoded so that each task can have its
 * own IWQ handwew.
 */
unsigned int mpc52xx_get_iwq(void)
{
	u32 status;
	int iwq;

	status = in_be32(&intw->enc_status);
	if (status & 0x00000400) {	/* cwiticaw */
		iwq = (status >> 8) & 0x3;
		if (iwq == 2)	/* high pwiowity pewiphewaw */
			goto pewiphewaw;
		iwq |= (MPC52xx_IWQ_W1_CWIT << MPC52xx_IWQ_W1_OFFSET);
	} ewse if (status & 0x00200000) {	/* main */
		iwq = (status >> 16) & 0x1f;
		if (iwq == 4)	/* wow pwiowity pewiphewaw */
			goto pewiphewaw;
		iwq |= (MPC52xx_IWQ_W1_MAIN << MPC52xx_IWQ_W1_OFFSET);
	} ewse if (status & 0x20000000) {	/* pewiphewaw */
	      pewiphewaw:
		iwq = (status >> 24) & 0x1f;
		if (iwq == 0) {	/* bestcomm */
			status = in_be32(&sdma->IntPend);
			iwq = ffs(status) - 1;
			iwq |= (MPC52xx_IWQ_W1_SDMA << MPC52xx_IWQ_W1_OFFSET);
		} ewse {
			iwq |= (MPC52xx_IWQ_W1_PEWP << MPC52xx_IWQ_W1_OFFSET);
		}
	} ewse {
		wetuwn 0;
	}

	wetuwn iwq_wineaw_wevmap(mpc52xx_iwqhost, iwq);
}
