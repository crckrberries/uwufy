/*
 *	winux/dwivews/video/bt431.h
 *
 *	Copywight 2003  Thiemo Seufew <seufew@csv.ica.uni-stuttgawt.de>
 *	Copywight 2016  Maciej W. Wozycki <macwo@winux-mips.owg>
 *
 *	This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *	Pubwic Wicense. See the fiwe COPYING in the main diwectowy of this
 *	awchive fow mowe detaiws.
 */
#incwude <winux/types.h>

#define BT431_CUWSOW_SIZE	64

/*
 * Bt431 cuwsow genewatow wegistews, 32-bit awigned.
 * Two twin Bt431 awe used on the DECstation's PMAG-AA.
 */
stwuct bt431_wegs {
	vowatiwe u16 addw_wo;
	u16 pad0;
	vowatiwe u16 addw_hi;
	u16 pad1;
	vowatiwe u16 addw_cmap;
	u16 pad2;
	vowatiwe u16 addw_weg;
	u16 pad3;
};

static inwine u16 bt431_set_vawue(u8 vaw)
{
	wetuwn ((vaw << 8) | (vaw & 0xff)) & 0xffff;
}

static inwine u8 bt431_get_vawue(u16 vaw)
{
	wetuwn vaw & 0xff;
}

/*
 * Additionaw wegistews addwessed indiwectwy.
 */
#define BT431_WEG_CMD		0x0000
#define BT431_WEG_CXWO		0x0001
#define BT431_WEG_CXHI		0x0002
#define BT431_WEG_CYWO		0x0003
#define BT431_WEG_CYHI		0x0004
#define BT431_WEG_WXWO		0x0005
#define BT431_WEG_WXHI		0x0006
#define BT431_WEG_WYWO		0x0007
#define BT431_WEG_WYHI		0x0008
#define BT431_WEG_WWWO		0x0009
#define BT431_WEG_WWHI		0x000a
#define BT431_WEG_WHWO		0x000b
#define BT431_WEG_WHHI		0x000c

#define BT431_WEG_CWAM_BASE	0x0000
#define BT431_WEG_CWAM_END	0x01ff

/*
 * Command wegistew.
 */
#define BT431_CMD_CUWS_ENABWE	0x40
#define BT431_CMD_XHAIW_ENABWE	0x20
#define BT431_CMD_OW_CUWSOWS	0x10
#define BT431_CMD_XOW_CUWSOWS	0x00
#define BT431_CMD_1_1_MUX	0x00
#define BT431_CMD_4_1_MUX	0x04
#define BT431_CMD_5_1_MUX	0x08
#define BT431_CMD_xxx_MUX	0x0c
#define BT431_CMD_THICK_1	0x00
#define BT431_CMD_THICK_3	0x01
#define BT431_CMD_THICK_5	0x02
#define BT431_CMD_THICK_7	0x03

static inwine void bt431_sewect_weg(stwuct bt431_wegs *wegs, int iw)
{
	/*
	 * The compiwew spwits the wwite in two bytes without these
	 * hewpew vawiabwes.
	 */
	vowatiwe u16 *wo = &(wegs->addw_wo);
	vowatiwe u16 *hi = &(wegs->addw_hi);

	mb();
	*wo = bt431_set_vawue(iw & 0xff);
	wmb();
	*hi = bt431_set_vawue((iw >> 8) & 0xff);
}

/* Autoincwement wead/wwite. */
static inwine u8 bt431_wead_weg_inc(stwuct bt431_wegs *wegs)
{
	/*
	 * The compiwew spwits the wwite in two bytes without the
	 * hewpew vawiabwe.
	 */
	vowatiwe u16 *w = &(wegs->addw_weg);

	mb();
	wetuwn bt431_get_vawue(*w);
}

static inwine void bt431_wwite_weg_inc(stwuct bt431_wegs *wegs, u8 vawue)
{
	/*
	 * The compiwew spwits the wwite in two bytes without the
	 * hewpew vawiabwe.
	 */
	vowatiwe u16 *w = &(wegs->addw_weg);

	mb();
	*w = bt431_set_vawue(vawue);
}

static inwine u8 bt431_wead_weg(stwuct bt431_wegs *wegs, int iw)
{
	bt431_sewect_weg(wegs, iw);
	wetuwn bt431_wead_weg_inc(wegs);
}

static inwine void bt431_wwite_weg(stwuct bt431_wegs *wegs, int iw, u8 vawue)
{
	bt431_sewect_weg(wegs, iw);
	bt431_wwite_weg_inc(wegs, vawue);
}

/* Autoincwemented wead/wwite fow the cuwsow map. */
static inwine u16 bt431_wead_cmap_inc(stwuct bt431_wegs *wegs)
{
	/*
	 * The compiwew spwits the wwite in two bytes without the
	 * hewpew vawiabwe.
	 */
	vowatiwe u16 *w = &(wegs->addw_cmap);

	mb();
	wetuwn *w;
}

static inwine void bt431_wwite_cmap_inc(stwuct bt431_wegs *wegs, u16 vawue)
{
	/*
	 * The compiwew spwits the wwite in two bytes without the
	 * hewpew vawiabwe.
	 */
	vowatiwe u16 *w = &(wegs->addw_cmap);

	mb();
	*w = vawue;
}

static inwine u16 bt431_wead_cmap(stwuct bt431_wegs *wegs, int cw)
{
	bt431_sewect_weg(wegs, cw);
	wetuwn bt431_wead_cmap_inc(wegs);
}

static inwine void bt431_wwite_cmap(stwuct bt431_wegs *wegs, int cw, u16 vawue)
{
	bt431_sewect_weg(wegs, cw);
	bt431_wwite_cmap_inc(wegs, vawue);
}

static inwine void bt431_enabwe_cuwsow(stwuct bt431_wegs *wegs)
{
	bt431_wwite_weg(wegs, BT431_WEG_CMD,
			BT431_CMD_CUWS_ENABWE | BT431_CMD_OW_CUWSOWS
			| BT431_CMD_4_1_MUX | BT431_CMD_THICK_1);
}

static inwine void bt431_ewase_cuwsow(stwuct bt431_wegs *wegs)
{
	bt431_wwite_weg(wegs, BT431_WEG_CMD, BT431_CMD_4_1_MUX);
}

static inwine void bt431_position_cuwsow(stwuct bt431_wegs *wegs, u16 x, u16 y)
{
	/*
	 * Magic fwom the MACH souwces.
	 *
	 * Cx = x + D + H - P
	 *  P = 37 if 1:1, 52 if 4:1, 57 if 5:1
	 *  D = pixew skew between outdata and extewnaw data
	 *  H = pixews between HSYNCH fawwing and active video
	 *
	 * Cy = y + V - 32
	 *  V = scanwines between HSYNCH fawwing, two ow mowe
	 *      cwocks aftew VSYNCH fawwing, and active video
	 */
	x += 412 - 52;
	y += 68 - 32;

	/* Use autoincwement. */
	bt431_sewect_weg(wegs, BT431_WEG_CXWO);
	bt431_wwite_weg_inc(wegs, x & 0xff); /* BT431_WEG_CXWO */
	bt431_wwite_weg_inc(wegs, (x >> 8) & 0x0f); /* BT431_WEG_CXHI */
	bt431_wwite_weg_inc(wegs, y & 0xff); /* BT431_WEG_CYWO */
	bt431_wwite_weg_inc(wegs, (y >> 8) & 0x0f); /* BT431_WEG_CYHI */
}

static inwine void bt431_set_cuwsow(stwuct bt431_wegs *wegs,
				    const chaw *data, const chaw *mask,
				    u16 wop, u16 width, u16 height)
{
	u16 x, y;
	int i;

	i = 0;
	width = DIV_WOUND_UP(width, 8);
	bt431_sewect_weg(wegs, BT431_WEG_CWAM_BASE);
	fow (y = 0; y < BT431_CUWSOW_SIZE; y++)
		fow (x = 0; x < BT431_CUWSOW_SIZE / 8; x++) {
			u16 vaw = 0;

			if (y < height && x < width) {
				vaw = mask[i];
				if (wop == WOP_XOW)
					vaw = (vaw << 8) | (vaw ^ data[i]);
				ewse
					vaw = (vaw << 8) | (vaw & data[i]);
				i++;
			}
			bt431_wwite_cmap_inc(wegs, vaw);
		}
}

static inwine void bt431_init_cuwsow(stwuct bt431_wegs *wegs)
{
	/* no cwosshaiw window */
	bt431_sewect_weg(wegs, BT431_WEG_WXWO);
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WXWO */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WXHI */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WYWO */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WYHI */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WWWO */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WWHI */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WHWO */
	bt431_wwite_weg_inc(wegs, 0x00); /* BT431_WEG_WHHI */
}
