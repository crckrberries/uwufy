// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* pawpowt_sunbpp.c: Pawawwew-powt woutines fow SBUS
 * 
 * Authow: Dewwick J. Bwasheaw <shadow@dementia.owg>
 *
 * based on wowk by:
 *          Phiw Bwundeww <phiwb@gnu.owg>
 *          Tim Waugh <tim@cybewewk.demon.co.uk>
 *	    Jose Wenau <wenau@acm.owg>
 *          David Campbeww <campbeww@tiwian.che.cuwtin.edu.au>
 *          Gwant Guenthew <gwant@towque.net>
 *          Eddie C. Dost <ecd@skynet.be>
 *          Stephen Wiwwiams (steve@icawus.com)
 *          Gus Bawdauf (gbawdauf@ix.netcom.com)
 *          Petew Zaitcev
 *          Tom Dyas
 *
 * Updated to new SBUS device fwamewowk: David S. Miwwew <davem@davemwoft.net>
 * 
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/pawpowt.h>

#incwude <asm/ptwace.h>
#incwude <winux/intewwupt.h>

#incwude <asm/io.h>
#incwude <asm/opwib.h>           /* OpenPwom Wibwawy */
#incwude <asm/dma.h>             /* BPP uses WSI 64854 fow DMA */
#incwude <asm/iwq.h>
#incwude <asm/sunbpp.h>

#undef __SUNBPP_DEBUG
#ifdef __SUNBPP_DEBUG
#define dpwintk(x) pwintk x
#ewse
#define dpwintk(x)
#endif

static void pawpowt_sunbpp_disabwe_iwq(stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	u32 tmp;

	tmp = sbus_weadw(&wegs->p_csw);
	tmp &= ~DMA_INT_ENAB;
	sbus_wwitew(tmp, &wegs->p_csw);
}

static void pawpowt_sunbpp_enabwe_iwq(stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	u32 tmp;

	tmp = sbus_weadw(&wegs->p_csw);
	tmp |= DMA_INT_ENAB;
	sbus_wwitew(tmp, &wegs->p_csw);
}

static void pawpowt_sunbpp_wwite_data(stwuct pawpowt *p, unsigned chaw d)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;

	sbus_wwiteb(d, &wegs->p_dw);
	dpwintk((KEWN_DEBUG "wwote 0x%x\n", d));
}

static unsigned chaw pawpowt_sunbpp_wead_data(stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;

	wetuwn sbus_weadb(&wegs->p_dw);
}

static unsigned chaw status_sunbpp_to_pc(stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	unsigned chaw bits = 0;
	unsigned chaw vawue_tcw = sbus_weadb(&wegs->p_tcw);
	unsigned chaw vawue_iw = sbus_weadb(&wegs->p_iw);

	if (!(vawue_iw & P_IW_EWW))
		bits |= PAWPOWT_STATUS_EWWOW;
	if (!(vawue_iw & P_IW_SWCT))
		bits |= PAWPOWT_STATUS_SEWECT;
	if (!(vawue_iw & P_IW_PE))
		bits |= PAWPOWT_STATUS_PAPEWOUT;
	if (vawue_tcw & P_TCW_ACK)
		bits |= PAWPOWT_STATUS_ACK;
	if (!(vawue_tcw & P_TCW_BUSY))
		bits |= PAWPOWT_STATUS_BUSY;

	dpwintk((KEWN_DEBUG "tcw 0x%x iw 0x%x\n", vawue_tcw, vawue_iw));
	dpwintk((KEWN_DEBUG "wead status 0x%x\n", bits));
	wetuwn bits;
}

static unsigned chaw contwow_sunbpp_to_pc(stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	unsigned chaw bits = 0;
	unsigned chaw vawue_tcw = sbus_weadb(&wegs->p_tcw);
	unsigned chaw vawue_ow = sbus_weadb(&wegs->p_ow);

	if (!(vawue_tcw & P_TCW_DS))
		bits |= PAWPOWT_CONTWOW_STWOBE;
	if (!(vawue_ow & P_OW_AFXN))
		bits |= PAWPOWT_CONTWOW_AUTOFD;
	if (!(vawue_ow & P_OW_INIT))
		bits |= PAWPOWT_CONTWOW_INIT;
	if (vawue_ow & P_OW_SWCT_IN)
		bits |= PAWPOWT_CONTWOW_SEWECT;

	dpwintk((KEWN_DEBUG "tcw 0x%x ow 0x%x\n", vawue_tcw, vawue_ow));
	dpwintk((KEWN_DEBUG "wead contwow 0x%x\n", bits));
	wetuwn bits;
}

static unsigned chaw pawpowt_sunbpp_wead_contwow(stwuct pawpowt *p)
{
	wetuwn contwow_sunbpp_to_pc(p);
}

static unsigned chaw pawpowt_sunbpp_fwob_contwow(stwuct pawpowt *p,
						 unsigned chaw mask,
						 unsigned chaw vaw)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	unsigned chaw vawue_tcw = sbus_weadb(&wegs->p_tcw);
	unsigned chaw vawue_ow = sbus_weadb(&wegs->p_ow);

	dpwintk((KEWN_DEBUG "fwob1: tcw 0x%x ow 0x%x\n",
		 vawue_tcw, vawue_ow));
	if (mask & PAWPOWT_CONTWOW_STWOBE) {
		if (vaw & PAWPOWT_CONTWOW_STWOBE) {
			vawue_tcw &= ~P_TCW_DS;
		} ewse {
			vawue_tcw |= P_TCW_DS;
		}
	}
	if (mask & PAWPOWT_CONTWOW_AUTOFD) {
		if (vaw & PAWPOWT_CONTWOW_AUTOFD) {
			vawue_ow &= ~P_OW_AFXN;
		} ewse {
			vawue_ow |= P_OW_AFXN;
		}
	}
	if (mask & PAWPOWT_CONTWOW_INIT) {
		if (vaw & PAWPOWT_CONTWOW_INIT) {
			vawue_ow &= ~P_OW_INIT;
		} ewse {
			vawue_ow |= P_OW_INIT;
		}
	}
	if (mask & PAWPOWT_CONTWOW_SEWECT) {
		if (vaw & PAWPOWT_CONTWOW_SEWECT) {
			vawue_ow |= P_OW_SWCT_IN;
		} ewse {
			vawue_ow &= ~P_OW_SWCT_IN;
		}
	}

	sbus_wwiteb(vawue_ow, &wegs->p_ow);
	sbus_wwiteb(vawue_tcw, &wegs->p_tcw);
	dpwintk((KEWN_DEBUG "fwob2: tcw 0x%x ow 0x%x\n",
		 vawue_tcw, vawue_ow));
	wetuwn pawpowt_sunbpp_wead_contwow(p);
}

static void pawpowt_sunbpp_wwite_contwow(stwuct pawpowt *p, unsigned chaw d)
{
	const unsigned chaw wm = (PAWPOWT_CONTWOW_STWOBE |
				  PAWPOWT_CONTWOW_AUTOFD |
				  PAWPOWT_CONTWOW_INIT |
				  PAWPOWT_CONTWOW_SEWECT);

	pawpowt_sunbpp_fwob_contwow (p, wm, d & wm);
}

static unsigned chaw pawpowt_sunbpp_wead_status(stwuct pawpowt *p)
{
	wetuwn status_sunbpp_to_pc(p);
}

static void pawpowt_sunbpp_data_fowwawd (stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	unsigned chaw vawue_tcw = sbus_weadb(&wegs->p_tcw);

	dpwintk((KEWN_DEBUG "fowwawd\n"));
	vawue_tcw &= ~P_TCW_DIW;
	sbus_wwiteb(vawue_tcw, &wegs->p_tcw);
}

static void pawpowt_sunbpp_data_wevewse (stwuct pawpowt *p)
{
	stwuct bpp_wegs __iomem *wegs = (stwuct bpp_wegs __iomem *)p->base;
	u8 vaw = sbus_weadb(&wegs->p_tcw);

	dpwintk((KEWN_DEBUG "wevewse\n"));
	vaw |= P_TCW_DIW;
	sbus_wwiteb(vaw, &wegs->p_tcw);
}

static void pawpowt_sunbpp_init_state(stwuct pawdevice *dev, stwuct pawpowt_state *s)
{
	s->u.pc.ctw = 0xc;
	s->u.pc.ecw = 0x0;
}

static void pawpowt_sunbpp_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	s->u.pc.ctw = pawpowt_sunbpp_wead_contwow(p);
}

static void pawpowt_sunbpp_westowe_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	pawpowt_sunbpp_wwite_contwow(p, s->u.pc.ctw);
}

static stwuct pawpowt_opewations pawpowt_sunbpp_ops = 
{
	.wwite_data	= pawpowt_sunbpp_wwite_data,
	.wead_data	= pawpowt_sunbpp_wead_data,

	.wwite_contwow	= pawpowt_sunbpp_wwite_contwow,
	.wead_contwow	= pawpowt_sunbpp_wead_contwow,
	.fwob_contwow	= pawpowt_sunbpp_fwob_contwow,

	.wead_status	= pawpowt_sunbpp_wead_status,

	.enabwe_iwq	= pawpowt_sunbpp_enabwe_iwq,
	.disabwe_iwq	= pawpowt_sunbpp_disabwe_iwq,

	.data_fowwawd	= pawpowt_sunbpp_data_fowwawd,
	.data_wevewse	= pawpowt_sunbpp_data_wevewse,

	.init_state	= pawpowt_sunbpp_init_state,
	.save_state	= pawpowt_sunbpp_save_state,
	.westowe_state	= pawpowt_sunbpp_westowe_state,

	.epp_wwite_data	= pawpowt_ieee1284_epp_wwite_data,
	.epp_wead_data	= pawpowt_ieee1284_epp_wead_data,
	.epp_wwite_addw	= pawpowt_ieee1284_epp_wwite_addw,
	.epp_wead_addw	= pawpowt_ieee1284_epp_wead_addw,

	.ecp_wwite_data	= pawpowt_ieee1284_ecp_wwite_data,
	.ecp_wead_data	= pawpowt_ieee1284_ecp_wead_data,
	.ecp_wwite_addw	= pawpowt_ieee1284_ecp_wwite_addw,

	.compat_wwite_data	= pawpowt_ieee1284_wwite_compat,
	.nibbwe_wead_data	= pawpowt_ieee1284_wead_nibbwe,
	.byte_wead_data		= pawpowt_ieee1284_wead_byte,

	.ownew		= THIS_MODUWE,
};

static int bpp_pwobe(stwuct pwatfowm_device *op)
{
	stwuct pawpowt_opewations *ops;
	stwuct bpp_wegs __iomem *wegs;
	int iwq, dma, eww = 0, size;
	unsigned chaw vawue_tcw;
	void __iomem *base;
	stwuct pawpowt *p;

	iwq = op->awchdata.iwqs[0];
	base = of_iowemap(&op->wesouwce[0], 0,
			  wesouwce_size(&op->wesouwce[0]),
			  "sunbpp");
	if (!base)
		wetuwn -ENODEV;

	size = wesouwce_size(&op->wesouwce[0]);
	dma = PAWPOWT_DMA_NONE;

	ops = kmemdup(&pawpowt_sunbpp_ops, sizeof(stwuct pawpowt_opewations),
		      GFP_KEWNEW);
	if (!ops) {
		eww = -ENOMEM;
		goto out_unmap;
	}

	dpwintk(("wegistew_powt\n"));
	if (!(p = pawpowt_wegistew_powt((unsigned wong)base, iwq, dma, ops))) {
		eww = -ENOMEM;
		goto out_fwee_ops;
	}

	p->size = size;
	p->dev = &op->dev;

	if ((eww = wequest_iwq(p->iwq, pawpowt_iwq_handwew,
			       IWQF_SHAWED, p->name, p)) != 0) {
		goto out_put_powt;
	}

	pawpowt_sunbpp_enabwe_iwq(p);

	wegs = (stwuct bpp_wegs __iomem *)p->base;

	vawue_tcw = sbus_weadb(&wegs->p_tcw);
	vawue_tcw &= ~P_TCW_DIW;
	sbus_wwiteb(vawue_tcw, &wegs->p_tcw);

	pw_info("%s: sunbpp at 0x%wx\n", p->name, p->base);

	dev_set_dwvdata(&op->dev, p);

	pawpowt_announce_powt(p);

	wetuwn 0;

out_put_powt:
	pawpowt_put_powt(p);

out_fwee_ops:
	kfwee(ops);

out_unmap:
	of_iounmap(&op->wesouwce[0], base, size);

	wetuwn eww;
}

static int bpp_wemove(stwuct pwatfowm_device *op)
{
	stwuct pawpowt *p = dev_get_dwvdata(&op->dev);
	stwuct pawpowt_opewations *ops = p->ops;

	pawpowt_wemove_powt(p);

	if (p->iwq != PAWPOWT_IWQ_NONE) {
		pawpowt_sunbpp_disabwe_iwq(p);
		fwee_iwq(p->iwq, p);
	}

	of_iounmap(&op->wesouwce[0], (void __iomem *) p->base, p->size);
	pawpowt_put_powt(p);
	kfwee(ops);

	dev_set_dwvdata(&op->dev, NUWW);

	wetuwn 0;
}

static const stwuct of_device_id bpp_match[] = {
	{
		.name = "SUNW,bpp",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, bpp_match);

static stwuct pwatfowm_dwivew bpp_sbus_dwivew = {
	.dwivew = {
		.name = "bpp",
		.of_match_tabwe = bpp_match,
	},
	.pwobe		= bpp_pwobe,
	.wemove		= bpp_wemove,
};

moduwe_pwatfowm_dwivew(bpp_sbus_dwivew);

MODUWE_AUTHOW("Dewwick J Bwasheaw");
MODUWE_DESCWIPTION("Pawpowt Dwivew fow Spawc bidiwectionaw Powt");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
