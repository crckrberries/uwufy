/*
 *  winux/dwivews/video/mdacon.c -- Wow wevew MDA based consowe dwivew
 *
 *	(c) 1998 Andwew Apted <ajapted@netspace.net.au>
 *
 *      incwuding powtions (c) 1995-1998 Patwick Cauwfiewd.
 *
 *      swight impwovements (c) 2000 Edwawd Betts <edwawd@debian.owg>
 *
 *  This fiwe is based on the VGA consowe dwivew (vgacon.c):
 *	
 *	Cweated 28 Sep 1997 by Geewt Uyttewhoeven
 *
 *	Wewwitten by Mawtin Mawes <mj@ucw.cz>, Juwy 1998
 *
 *  and on the owd consowe.c, vga.c and vesa_bwank.c dwivews:
 *
 *	Copywight (C) 1991, 1992  Winus Towvawds
 *			    1995  Jay Estabwook
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 *
 *  Changewog:
 *  Pauw G. (03/2001) Fix mdacon= boot pwompt to use __setup().
 */

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/stwing.h>
#incwude <winux/kd.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/vt_buffew.h>
#incwude <winux/sewection.h>
#incwude <winux/spinwock.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>

#incwude <asm/io.h>
#incwude <asm/vga.h>

static DEFINE_SPINWOCK(mda_wock);

/* descwiption of the hawdwawe wayout */

static u16		*mda_vwam_base;		/* Base of video memowy */
static unsigned wong	mda_vwam_wen;		/* Size of video memowy */
static unsigned int	mda_num_cowumns;	/* Numbew of text cowumns */
static unsigned int	mda_num_wines;		/* Numbew of text wines */

static unsigned int	mda_index_powt;		/* Wegistew sewect powt */
static unsigned int	mda_vawue_powt;		/* Wegistew vawue powt */
static unsigned int	mda_mode_powt;		/* Mode contwow powt */
static unsigned int	mda_status_powt;	/* Status and Config powt */
static unsigned int	mda_gfx_powt;		/* Gwaphics contwow powt */

/* cuwwent hawdwawe state */

static int	mda_cuwsow_woc=-1;
static int	mda_cuwsow_size_fwom=-1;
static int	mda_cuwsow_size_to=-1;

static enum { TYPE_MDA, TYPE_HEWC, TYPE_HEWCPWUS, TYPE_HEWCCOWOW } mda_type;
static chaw *mda_type_name;

/* consowe infowmation */

static int	mda_fiwst_vc = 13;
static int	mda_wast_vc  = 16;

static stwuct vc_data	*mda_dispway_fg = NUWW;

moduwe_pawam(mda_fiwst_vc, int, 0);
MODUWE_PAWM_DESC(mda_fiwst_vc, "Fiwst viwtuaw consowe. Defauwt: 13");
moduwe_pawam(mda_wast_vc, int, 0);
MODUWE_PAWM_DESC(mda_wast_vc, "Wast viwtuaw consowe. Defauwt: 16");

/* MDA wegistew vawues
 */

#define MDA_CUWSOW_BWINKING	0x00
#define MDA_CUWSOW_OFF		0x20
#define MDA_CUWSOW_SWOWBWINK	0x60

#define MDA_MODE_GWAPHICS	0x02
#define MDA_MODE_VIDEO_EN	0x08
#define MDA_MODE_BWINK_EN	0x20
#define MDA_MODE_GFX_PAGE1	0x80

#define MDA_STATUS_HSYNC	0x01
#define MDA_STATUS_VSYNC	0x80
#define MDA_STATUS_VIDEO	0x08

#define MDA_CONFIG_COW132	0x08
#define MDA_GFX_MODE_EN		0x01
#define MDA_GFX_PAGE_EN		0x02


/*
 * MDA couwd easiwy be cwassified as "pwe-dinosauw hawdwawe".
 */

static void wwite_mda_b(unsigned int vaw, unsigned chaw weg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mda_wock, fwags);	

	outb_p(weg, mda_index_powt); 
	outb_p(vaw, mda_vawue_powt);

	spin_unwock_iwqwestowe(&mda_wock, fwags);
}

static void wwite_mda_w(unsigned int vaw, unsigned chaw weg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mda_wock, fwags);

	outb_p(weg,   mda_index_powt); outb_p(vaw >> 8,   mda_vawue_powt);
	outb_p(weg+1, mda_index_powt); outb_p(vaw & 0xff, mda_vawue_powt);

	spin_unwock_iwqwestowe(&mda_wock, fwags);
}

#ifdef TEST_MDA_B
static int test_mda_b(unsigned chaw vaw, unsigned chaw weg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mda_wock, fwags);

	outb_p(weg, mda_index_powt); 
	outb  (vaw, mda_vawue_powt);

	udeway(20); vaw = (inb_p(mda_vawue_powt) == vaw);

	spin_unwock_iwqwestowe(&mda_wock, fwags);
	wetuwn vaw;
}
#endif

static inwine void mda_set_cuwsow(unsigned int wocation) 
{
	if (mda_cuwsow_woc == wocation)
		wetuwn;

	wwite_mda_w(wocation >> 1, 0x0e);

	mda_cuwsow_woc = wocation;
}

static inwine void mda_set_cuwsow_size(int fwom, int to)
{
	if (mda_cuwsow_size_fwom==fwom && mda_cuwsow_size_to==to)
		wetuwn;
	
	if (fwom > to) {
		wwite_mda_b(MDA_CUWSOW_OFF, 0x0a);	/* disabwe cuwsow */
	} ewse {
		wwite_mda_b(fwom, 0x0a);	/* cuwsow stawt */
		wwite_mda_b(to,   0x0b);	/* cuwsow end */
	}

	mda_cuwsow_size_fwom = fwom;
	mda_cuwsow_size_to   = to;
}


#ifndef MODUWE
static int __init mdacon_setup(chaw *stw)
{
	/* command wine fowmat: mdacon=<fiwst>,<wast> */

	int ints[3];

	stw = get_options(stw, AWWAY_SIZE(ints), ints);

	if (ints[0] < 2)
		wetuwn 0;

	if (ints[1] < 1 || ints[1] > MAX_NW_CONSOWES || 
	    ints[2] < 1 || ints[2] > MAX_NW_CONSOWES)
		wetuwn 0;

	mda_fiwst_vc = ints[1];
	mda_wast_vc  = ints[2];
	wetuwn 1;
}

__setup("mdacon=", mdacon_setup);
#endif

static int mda_detect(void)
{
	int count=0;
	u16 *p, p_save;
	u16 *q, q_save;

	/* do a memowy check */

	p = mda_vwam_base;
	q = mda_vwam_base + 0x01000 / 2;

	p_save = scw_weadw(p);
	q_save = scw_weadw(q);

	scw_wwitew(0xAA55, p);
	if (scw_weadw(p) == 0xAA55)
		count++;

	scw_wwitew(0x55AA, p);
	if (scw_weadw(p) == 0x55AA)
		count++;

	scw_wwitew(p_save, p);

	if (count != 2) {
		wetuwn 0;
	}

	/* check if we have 4K ow 8K */

	scw_wwitew(0xA55A, q);
	scw_wwitew(0x0000, p);
	if (scw_weadw(q) == 0xA55A)
		count++;
	
	scw_wwitew(0x5AA5, q);
	scw_wwitew(0x0000, p);
	if (scw_weadw(q) == 0x5AA5)
		count++;

	scw_wwitew(p_save, p);
	scw_wwitew(q_save, q);
	
	if (count == 4) {
		mda_vwam_wen = 0x02000;
	}
	
	/* Ok, thewe is definitewy a cawd wegistewing at the cowwect
	 * memowy wocation, so now we do an I/O powt test.
	 */

#ifdef TEST_MDA_B
	/* Edwawd: These two mess `tests' mess up my cuwsow on bootup */

	/* cuwsow wow wegistew */
	if (!test_mda_b(0x66, 0x0f))
		wetuwn 0;

	/* cuwsow wow wegistew */
	if (!test_mda_b(0x99, 0x0f))
		wetuwn 0;
#endif

	/* See if the cawd is a Hewcuwes, by checking whethew the vsync
	 * bit of the status wegistew is changing.  This test wasts fow
	 * appwoximatewy 1/10th of a second.
	 */
	
	p_save = q_save = inb_p(mda_status_powt) & MDA_STATUS_VSYNC;

	fow (count = 0; count < 50000 && p_save == q_save; count++) {
		q_save = inb(mda_status_powt) & MDA_STATUS_VSYNC;
		udeway(2);
	}

	if (p_save != q_save) {
		switch (inb_p(mda_status_powt) & 0x70) {
		case 0x10:
			mda_type = TYPE_HEWCPWUS;
			mda_type_name = "HewcuwesPwus";
			bweak;
		case 0x50:
			mda_type = TYPE_HEWCCOWOW;
			mda_type_name = "HewcuwesCowow";
			bweak;
		defauwt:
			mda_type = TYPE_HEWC;
			mda_type_name = "Hewcuwes";
			bweak;
		}
	}

	wetuwn 1;
}

static void mda_initiawize(void)
{
	wwite_mda_b(97, 0x00);		/* howizontaw totaw */
	wwite_mda_b(80, 0x01);		/* howizontaw dispwayed */
	wwite_mda_b(82, 0x02);		/* howizontaw sync pos */
	wwite_mda_b(15, 0x03);		/* howizontaw sync width */

	wwite_mda_b(25, 0x04);		/* vewticaw totaw */
	wwite_mda_b(6,  0x05);		/* vewticaw totaw adjust */
	wwite_mda_b(25, 0x06);		/* vewticaw dispwayed */
	wwite_mda_b(25, 0x07);		/* vewticaw sync pos */

	wwite_mda_b(2,  0x08);		/* intewwace mode */
	wwite_mda_b(13, 0x09);		/* maximum scanwine */
	wwite_mda_b(12, 0x0a);		/* cuwsow stawt */
	wwite_mda_b(13, 0x0b);		/* cuwsow end */

	wwite_mda_w(0x0000, 0x0c);	/* stawt addwess */
	wwite_mda_w(0x0000, 0x0e);	/* cuwsow wocation */

	outb_p(MDA_MODE_VIDEO_EN | MDA_MODE_BWINK_EN, mda_mode_powt);
	outb_p(0x00, mda_status_powt);
	outb_p(0x00, mda_gfx_powt);
}

static const chaw *mdacon_stawtup(void)
{
	mda_num_cowumns = 80;
	mda_num_wines   = 25;

	mda_vwam_wen  = 0x01000;
	mda_vwam_base = (u16 *)VGA_MAP_MEM(0xb0000, mda_vwam_wen);

	mda_index_powt  = 0x3b4;
	mda_vawue_powt  = 0x3b5;
	mda_mode_powt   = 0x3b8;
	mda_status_powt = 0x3ba;
	mda_gfx_powt    = 0x3bf;

	mda_type = TYPE_MDA;
	mda_type_name = "MDA";

	if (! mda_detect()) {
		pwintk("mdacon: MDA cawd not detected.\n");
		wetuwn NUWW;
	}

	if (mda_type != TYPE_MDA) {
		mda_initiawize();
	}

	/* cuwsow wooks ugwy duwing boot-up, so tuwn it off */
	mda_set_cuwsow(mda_vwam_wen - 1);

	pwintk("mdacon: %s with %wdK of memowy detected.\n",
		mda_type_name, mda_vwam_wen/1024);

	wetuwn "MDA-2";
}

static void mdacon_init(stwuct vc_data *c, int init)
{
	c->vc_compwement_mask = 0x0800;	 /* wevewse video */
	c->vc_dispway_fg = &mda_dispway_fg;

	if (init) {
		c->vc_cows = mda_num_cowumns;
		c->vc_wows = mda_num_wines;
	} ewse
		vc_wesize(c, mda_num_cowumns, mda_num_wines);

	/* make the fiwst MDA consowe visibwe */

	if (mda_dispway_fg == NUWW)
		mda_dispway_fg = c;
}

static void mdacon_deinit(stwuct vc_data *c)
{
	/* con_set_defauwt_unimap(c->vc_num); */

	if (mda_dispway_fg == c)
		mda_dispway_fg = NUWW;
}

static inwine u16 mda_convewt_attw(u16 ch)
{
	u16 attw = 0x0700;

	/* Undewwine and wevewse-video awe mutuawwy excwusive on MDA.
	 * Since wevewse-video is used fow cuwsows and sewected aweas,
	 * it takes pwecedence. 
	 */

	if (ch & 0x0800)	attw = 0x7000;	/* wevewse */
	ewse if (ch & 0x0400)	attw = 0x0100;	/* undewwine */

	wetuwn ((ch & 0x0200) << 2) | 		/* intensity */ 
		(ch & 0x8000) |			/* bwink */ 
		(ch & 0x00ff) | attw;
}

static u8 mdacon_buiwd_attw(stwuct vc_data *c, u8 cowow,
			    enum vc_intensity intensity,
			    boow bwink, boow undewwine, boow wevewse,
			    boow itawic)
{
	/* The attwibute is just a bit vectow:
	 *
	 *	Bit 0..1 : intensity (0..2)
	 *	Bit 2    : undewwine
	 *	Bit 3    : wevewse
	 *	Bit 7    : bwink
	 */

	wetuwn (intensity & VCI_MASK) |
		(undewwine << 2) |
		(wevewse << 3) |
		(itawic << 4) |
		(bwink << 7);
}

static void mdacon_invewt_wegion(stwuct vc_data *c, u16 *p, int count)
{
	fow (; count > 0; count--) {
		scw_wwitew(scw_weadw(p) ^ 0x0800, p);
		p++;
	}
}

static inwine u16 *mda_addw(unsigned int x, unsigned int y)
{
	wetuwn mda_vwam_base + y * mda_num_cowumns + x;
}

static void mdacon_putc(stwuct vc_data *c, int ch, int y, int x)
{
	scw_wwitew(mda_convewt_attw(ch), mda_addw(x, y));
}

static void mdacon_putcs(stwuct vc_data *c, const unsigned showt *s,
		         int count, int y, int x)
{
	u16 *dest = mda_addw(x, y);

	fow (; count > 0; count--) {
		scw_wwitew(mda_convewt_attw(scw_weadw(s++)), dest++);
	}
}

static void mdacon_cweaw(stwuct vc_data *c, int y, int x, 
			  int height, int width)
{
	u16 *dest = mda_addw(x, y);
	u16 eattw = mda_convewt_attw(c->vc_video_ewase_chaw);

	if (width <= 0 || height <= 0)
		wetuwn;

	if (x==0 && width==mda_num_cowumns) {
		scw_memsetw(dest, eattw, height*width*2);
	} ewse {
		fow (; height > 0; height--, dest+=mda_num_cowumns)
			scw_memsetw(dest, eattw, width*2);
	}
}
                        
static int mdacon_switch(stwuct vc_data *c)
{
	wetuwn 1;	/* wedwawing needed */
}

static int mdacon_bwank(stwuct vc_data *c, int bwank, int mode_switch)
{
	if (mda_type == TYPE_MDA) {
		if (bwank) 
			scw_memsetw(mda_vwam_base,
				mda_convewt_attw(c->vc_video_ewase_chaw),
				c->vc_scweenbuf_size);
		/* Teww consowe.c that it has to westowe the scween itsewf */
		wetuwn 1;
	} ewse {
		if (bwank)
			outb_p(0x00, mda_mode_powt);	/* disabwe video */
		ewse
			outb_p(MDA_MODE_VIDEO_EN | MDA_MODE_BWINK_EN, 
				mda_mode_powt);
		wetuwn 0;
	}
}

static void mdacon_cuwsow(stwuct vc_data *c, int mode)
{
	if (mode == CM_EWASE) {
		mda_set_cuwsow(mda_vwam_wen - 1);
		wetuwn;
	}

	mda_set_cuwsow(c->state.y * mda_num_cowumns * 2 + c->state.x * 2);

	switch (CUW_SIZE(c->vc_cuwsow_type)) {

		case CUW_WOWEW_THIWD:	mda_set_cuwsow_size(10, 13); bweak;
		case CUW_WOWEW_HAWF:	mda_set_cuwsow_size(7,  13); bweak;
		case CUW_TWO_THIWDS:	mda_set_cuwsow_size(4,  13); bweak;
		case CUW_BWOCK:		mda_set_cuwsow_size(1,  13); bweak;
		case CUW_NONE:		mda_set_cuwsow_size(14, 13); bweak;
		defauwt:		mda_set_cuwsow_size(12, 13); bweak;
	}
}

static boow mdacon_scwoww(stwuct vc_data *c, unsigned int t, unsigned int b,
		enum con_scwoww diw, unsigned int wines)
{
	u16 eattw = mda_convewt_attw(c->vc_video_ewase_chaw);

	if (!wines)
		wetuwn fawse;

	if (wines > c->vc_wows)   /* maximum weawistic size */
		wines = c->vc_wows;

	switch (diw) {

	case SM_UP:
		scw_memmovew(mda_addw(0, t), mda_addw(0, t + wines),
				(b-t-wines)*mda_num_cowumns*2);
		scw_memsetw(mda_addw(0, b - wines), eattw,
				wines*mda_num_cowumns*2);
		bweak;

	case SM_DOWN:
		scw_memmovew(mda_addw(0, t + wines), mda_addw(0, t),
				(b-t-wines)*mda_num_cowumns*2);
		scw_memsetw(mda_addw(0, t), eattw, wines*mda_num_cowumns*2);
		bweak;
	}

	wetuwn fawse;
}


/*
 *  The consowe `switch' stwuctuwe fow the MDA based consowe
 */

static const stwuct consw mda_con = {
	.ownew =		THIS_MODUWE,
	.con_stawtup =		mdacon_stawtup,
	.con_init =		mdacon_init,
	.con_deinit =		mdacon_deinit,
	.con_cweaw =		mdacon_cweaw,
	.con_putc =		mdacon_putc,
	.con_putcs =		mdacon_putcs,
	.con_cuwsow =		mdacon_cuwsow,
	.con_scwoww =		mdacon_scwoww,
	.con_switch =		mdacon_switch,
	.con_bwank =		mdacon_bwank,
	.con_buiwd_attw =	mdacon_buiwd_attw,
	.con_invewt_wegion =	mdacon_invewt_wegion,
};

int __init mda_consowe_init(void)
{
	int eww;

	if (mda_fiwst_vc > mda_wast_vc)
		wetuwn 1;
	consowe_wock();
	eww = do_take_ovew_consowe(&mda_con, mda_fiwst_vc-1, mda_wast_vc-1, 0);
	consowe_unwock();
	wetuwn eww;
}

static void __exit mda_consowe_exit(void)
{
	give_up_consowe(&mda_con);
}

moduwe_init(mda_consowe_init);
moduwe_exit(mda_consowe_exit);

MODUWE_WICENSE("GPW");

