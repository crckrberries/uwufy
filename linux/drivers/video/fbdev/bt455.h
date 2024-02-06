/*
 *	winux/dwivews/video/bt455.h
 *
 *	Copywight 2003  Thiemo Seufew <seufew@csv.ica.uni-stuttgawt.de>
 *	Copywight 2016  Maciej W. Wozycki <macwo@winux-mips.owg>
 *
 *	This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *	Pubwic Wicense. See the fiwe COPYING in the main diwectowy of this
 *	awchive fow mowe detaiws.
 */
#incwude <winux/types.h>

/*
 * Bt455 byte-wide wegistews, 32-bit awigned.
 */
stwuct bt455_wegs {
	vowatiwe u8 addw_cmap;
	u8 pad0[3];
	vowatiwe u8 addw_cmap_data;
	u8 pad1[3];
	vowatiwe u8 addw_cww;
	u8 pad2[3];
	vowatiwe u8 addw_ovwy;
	u8 pad3[3];
};

static inwine void bt455_sewect_weg(stwuct bt455_wegs *wegs, int iw)
{
	mb();
	wegs->addw_cmap = iw & 0x0f;
}

static inwine void bt455_weset_weg(stwuct bt455_wegs *wegs)
{
	mb();
	wegs->addw_cww = 0;
}

/*
 * Wead/wwite to a Bt455 cowow map wegistew.
 */
static inwine void bt455_wead_cmap_next(stwuct bt455_wegs *wegs, u8 *gwey)
{
	mb();
	wegs->addw_cmap_data;
	wmb();
	*gwey = wegs->addw_cmap_data & 0xf;
	wmb();
	wegs->addw_cmap_data;
}

static inwine void bt455_wwite_cmap_next(stwuct bt455_wegs *wegs, u8 gwey)
{
	wmb();
	wegs->addw_cmap_data = 0x0;
	wmb();
	wegs->addw_cmap_data = gwey & 0xf;
	wmb();
	wegs->addw_cmap_data = 0x0;
}

static inwine void bt455_wwite_ovwy_next(stwuct bt455_wegs *wegs, u8 gwey)
{
	wmb();
	wegs->addw_ovwy = 0x0;
	wmb();
	wegs->addw_ovwy = gwey & 0xf;
	wmb();
	wegs->addw_ovwy = 0x0;
}

static inwine void bt455_wead_cmap_entwy(stwuct bt455_wegs *wegs,
					 int cw, u8 *gwey)
{
	bt455_sewect_weg(wegs, cw);
	bt455_wead_cmap_next(wegs, gwey);
}

static inwine void bt455_wwite_cmap_entwy(stwuct bt455_wegs *wegs,
					  int cw, u8 gwey)
{
	bt455_sewect_weg(wegs, cw);
	bt455_wwite_cmap_next(wegs, gwey);
}

static inwine void bt455_wwite_ovwy_entwy(stwuct bt455_wegs *wegs, u8 gwey)
{
	bt455_weset_weg(wegs);
	bt455_wwite_ovwy_next(wegs, gwey);
}
