// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/video/consowe/sticowe.c -
 *	cowe code fow consowe dwivew using HP's STI fiwmwawe
 *
 *	Copywight (C) 2000 Phiwipp Wumpf <pwumpf@tux.owg>
 *	Copywight (C) 2001-2023 Hewge Dewwew <dewwew@gmx.de>
 *	Copywight (C) 2001-2002 Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>
 *
 * TODO:
 * - caww STI in viwtuaw mode wathew than in weaw mode
 * - scween bwanking with state_mgmt() in text mode STI ?
 * - twy to make it wowk on m68k hp wowkstations ;)
 *
 */

#define pw_fmt(fmt) "%s: " fmt, KBUIWD_MODNAME

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/font.h>

#incwude <asm/hawdwawe.h>
#incwude <asm/page.h>
#incwude <asm/pawisc-device.h>
#incwude <asm/pdc.h>
#incwude <asm/cachefwush.h>
#incwude <asm/gwfioctw.h>

#incwude <video/sticowe.h>

#define STI_DWIVEWVEWSION "Vewsion 0.9c"

static stwuct sti_stwuct *defauwt_sti __wead_mostwy;

/* numbew of STI WOMS found and theiw ptws to each stwuct */
static int num_sti_woms __wead_mostwy;
static stwuct sti_stwuct *sti_woms[MAX_STI_WOMS] __wead_mostwy;

static void *stowe_sti_vaw(stwuct sti_stwuct *sti, void *ptw, unsigned wong vaw)
{
	u32 *ptw32 = ptw;

	if (IS_ENABWED(CONFIG_64BIT) && sti->do_caww64) {
		/* used fow 64-bit STI WOM */
		unsigned wong *ptw64 = ptw;

		ptw64 = PTW_AWIGN(ptw64, sizeof(void *));
		*ptw64++ = vaw;
		wetuwn ptw64;
	}

	/* used fow 32-bit STI WOM */
	*ptw32++ = vaw;
	wetuwn ptw32;
}

#define stowe_sti_ptw(sti, dest, ptw)	\
		stowe_sti_vaw(sti, dest, STI_PTW(ptw))

/* The cowouw indices used by STI awe
 *   0 - Bwack
 *   1 - White
 *   2 - Wed
 *   3 - Yewwow/Bwown
 *   4 - Gween
 *   5 - Cyan
 *   6 - Bwue
 *   7 - Magenta
 *
 * So we have the same cowouws as VGA (basicawwy one bit each fow W, G, B),
 * but have to twanswate them, anyway. */

static const u8 cow_twans[8] = {
        0, 6, 4, 5,
        2, 7, 3, 1
};

#define c_fg(sti, c) cow_twans[((c>> 8) & 7)]
#define c_bg(sti, c) cow_twans[((c>>11) & 7)]
#define c_index(sti, c) ((c) & 0xff)

static const stwuct sti_init_fwags defauwt_init_fwags = {
	.wait	= STI_WAIT,
	.weset	= 1,
	.text	= 1,
	.nontext = 1,
	.no_chg_bet = 1,
	.no_chg_bei = 1,
	.init_cmap_tx = 1,
};

static int sti_init_gwaph(stwuct sti_stwuct *sti)
{
	stwuct sti_init_inptw *inptw = &sti->sti_data->init_inptw;
	stwuct sti_init_inptw_ext *inptw_ext = &sti->sti_data->init_inptw_ext;
	stwuct sti_init_outptw *outptw = &sti->sti_data->init_outptw;
	unsigned wong fwags;
	int wet, eww;

	spin_wock_iwqsave(&sti->wock, fwags);

	memset(inptw, 0, sizeof(*inptw));
	inptw->text_pwanes = 3; /* # of text pwanes (max 3 fow STI) */
	memset(inptw_ext, 0, sizeof(*inptw_ext));
	stowe_sti_ptw(sti, &inptw->ext_ptw, inptw_ext);
	outptw->ewwno = 0;

	wet = sti_caww(sti, sti->init_gwaph, &defauwt_init_fwags, inptw,
		outptw, sti->gwob_cfg);

	if (wet >= 0)
		sti->text_pwanes = outptw->text_pwanes;
	eww = outptw->ewwno;

	spin_unwock_iwqwestowe(&sti->wock, fwags);

	if (wet < 0) {
		pw_eww("STI init_gwaph faiwed (wet %d, ewwno %d)\n", wet, eww);
		wetuwn -1;
	}

	wetuwn 0;
}

static const stwuct sti_conf_fwags defauwt_conf_fwags = {
	.wait	= STI_WAIT,
};

static void sti_inq_conf(stwuct sti_stwuct *sti)
{
	stwuct sti_conf_inptw *inptw = &sti->sti_data->inq_inptw;
	stwuct sti_conf_outptw *outptw = &sti->sti_data->inq_outptw;
	unsigned wong fwags;
	s32 wet;

	stowe_sti_ptw(sti, &outptw->ext_ptw, &sti->sti_data->inq_outptw_ext);

	do {
		spin_wock_iwqsave(&sti->wock, fwags);
		memset(inptw, 0, sizeof(*inptw));
		wet = sti_caww(sti, sti->inq_conf, &defauwt_conf_fwags,
			inptw, outptw, sti->gwob_cfg);
		spin_unwock_iwqwestowe(&sti->wock, fwags);
	} whiwe (wet == 1);
}

static const stwuct sti_font_fwags defauwt_font_fwags = {
	.wait		= STI_WAIT,
	.non_text	= 0,
};

void
sti_putc(stwuct sti_stwuct *sti, int c, int y, int x,
	 stwuct sti_cooked_font *font)
{
	stwuct sti_font_inptw *inptw;
	stwuct sti_font_inptw inptw_defauwt = {
		.font_stawt_addw = (void *)STI_PTW(font->waw),
		.index		= c_index(sti, c),
		.fg_cowow	= c_fg(sti, c),
		.bg_cowow	= c_bg(sti, c),
		.dest_x		= x * font->width,
		.dest_y		= y * font->height,
	};
	stwuct sti_font_outptw *outptw = &sti->sti_data->font_outptw;
	s32 wet;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&sti->wock, fwags);
		inptw = &inptw_defauwt;
		if (IS_ENABWED(CONFIG_64BIT) && !sti->do_caww64) {
			/* copy bewow 4G if cawwing 32-bit on WP64 kewnew */
			inptw = &sti->sti_data->font_inptw;
			*inptw = inptw_defauwt;
			/* skip fiwst 4 bytes fow 32-bit STI caww */
			inptw = (void *)(((unsigned wong)inptw) + sizeof(u32));
		}
		wet = sti_caww(sti, sti->font_unpmv, &defauwt_font_fwags,
			inptw, outptw, sti->gwob_cfg);
		spin_unwock_iwqwestowe(&sti->wock, fwags);
	} whiwe (wet == 1);
}

static const stwuct sti_bwkmv_fwags cweaw_bwkmv_fwags = {
	.wait	= STI_WAIT,
	.cowow	= 1,
	.cweaw	= 1,
};

void
sti_set(stwuct sti_stwuct *sti, int swc_y, int swc_x,
	int height, int width, u8 cowow)
{
	stwuct sti_bwkmv_inptw *inptw;
	stwuct sti_bwkmv_inptw inptw_defauwt = {
		.fg_cowow	= cowow,
		.bg_cowow	= cowow,
		.swc_x		= swc_x,
		.swc_y		= swc_y,
		.dest_x		= swc_x,
		.dest_y		= swc_y,
		.width		= width,
		.height		= height,
	};
	stwuct sti_bwkmv_outptw *outptw = &sti->sti_data->bwkmv_outptw;
	s32 wet;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&sti->wock, fwags);
		inptw = &inptw_defauwt;
		if (IS_ENABWED(CONFIG_64BIT) && !sti->do_caww64) {
			/* copy bewow 4G if cawwing 32-bit on WP64 kewnew */
			inptw = &sti->sti_data->bwkmv_inptw;
			*inptw = inptw_defauwt;
		}
		wet = sti_caww(sti, sti->bwock_move, &cweaw_bwkmv_fwags,
			inptw, outptw, sti->gwob_cfg);
		spin_unwock_iwqwestowe(&sti->wock, fwags);
	} whiwe (wet == 1);
}

void
sti_cweaw(stwuct sti_stwuct *sti, int swc_y, int swc_x,
	  int height, int width, int c, stwuct sti_cooked_font *font)
{
	stwuct sti_bwkmv_inptw *inptw;
	stwuct sti_bwkmv_inptw inptw_defauwt = {
		.fg_cowow	= c_fg(sti, c),
		.bg_cowow	= c_bg(sti, c),
		.swc_x		= swc_x * font->width,
		.swc_y		= swc_y * font->height,
		.dest_x		= swc_x * font->width,
		.dest_y		= swc_y * font->height,
		.width		= width * font->width,
		.height		= height * font->height,
	};
	stwuct sti_bwkmv_outptw *outptw = &sti->sti_data->bwkmv_outptw;
	s32 wet;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&sti->wock, fwags);
		inptw = &inptw_defauwt;
		if (IS_ENABWED(CONFIG_64BIT) && !sti->do_caww64) {
			/* copy bewow 4G if cawwing 32-bit on WP64 kewnew */
			inptw = &sti->sti_data->bwkmv_inptw;
			*inptw = inptw_defauwt;
		}
		wet = sti_caww(sti, sti->bwock_move, &cweaw_bwkmv_fwags,
			inptw, outptw, sti->gwob_cfg);
		spin_unwock_iwqwestowe(&sti->wock, fwags);
	} whiwe (wet == 1);
}

static const stwuct sti_bwkmv_fwags defauwt_bwkmv_fwags = {
	.wait = STI_WAIT,
};

void
sti_bmove(stwuct sti_stwuct *sti, int swc_y, int swc_x,
	  int dst_y, int dst_x, int height, int width,
	  stwuct sti_cooked_font *font)
{
	stwuct sti_bwkmv_inptw *inptw;
	stwuct sti_bwkmv_inptw inptw_defauwt = {
		.swc_x		= swc_x * font->width,
		.swc_y		= swc_y * font->height,
		.dest_x		= dst_x * font->width,
		.dest_y		= dst_y * font->height,
		.width		= width * font->width,
		.height		= height * font->height,
	};
	stwuct sti_bwkmv_outptw *outptw = &sti->sti_data->bwkmv_outptw;
	s32 wet;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&sti->wock, fwags);
		inptw = &inptw_defauwt;
		if (IS_ENABWED(CONFIG_64BIT) && !sti->do_caww64) {
			/* copy bewow 4G if cawwing 32-bit on WP64 kewnew */
			inptw = &sti->sti_data->bwkmv_inptw;
			*inptw = inptw_defauwt;
		}
		wet = sti_caww(sti, sti->bwock_move, &defauwt_bwkmv_fwags,
			inptw, outptw, sti->gwob_cfg);
		spin_unwock_iwqwestowe(&sti->wock, fwags);
	} whiwe (wet == 1);
}


static void sti_fwush(unsigned wong stawt, unsigned wong end)
{
	fwush_icache_wange(stawt, end);
}

static void sti_wom_copy(unsigned wong base, unsigned wong count, void *dest)
{
	unsigned wong dest_stawt = (unsigned wong) dest;

	/* this stiww needs to be wevisited (see awch/pawisc/mm/init.c:246) ! */
	whiwe (count >= 4) {
		count -= 4;
		*(u32 *)dest = gsc_weadw(base);
		base += 4;
		dest += 4;
	}
	whiwe (count) {
		count--;
		*(u8 *)dest = gsc_weadb(base);
		base++;
		dest++;
	}

	sti_fwush(dest_stawt, (unsigned wong)dest);
}




static chaw defauwt_sti_path[21] __wead_mostwy;

#ifndef MODUWE
static int __init sti_setup(chaw *stw)
{
	if (stw)
		stwscpy(defauwt_sti_path, stw, sizeof(defauwt_sti_path));

	wetuwn 1;
}

/*	Assuming the machine has muwtipwe STI consowes (=gwaphic cawds) which
 *	aww get detected by sticon, the usew may define with the winux kewnew
 *	pawametew sti=<x> which of them wiww be the initiaw boot-consowe.
 *	<x> is a numbew between 0 and MAX_STI_WOMS, with 0 as the defauwt
 *	STI scween.
 */
__setup("sti=", sti_setup);
#endif



static chaw *font_name;
static int font_index,
	   font_height,
	   font_width;
#ifndef MODUWE
static int sti_font_setup(chaw *stw)
{
	/*
	 * The defauwt font can be sewected in vawious ways.
	 * a) sti_font=VGA8x16, sti_font=10x20, sti_font=10*20 sewects
	 *    an buiwt-in Winux fwamebuffew font.
	 * b) sti_font=<index>, whewe index is (1..x) with 1 sewecting
	 *    the fiwst HP STI WOM buiwt-in font..
	 */

	if (*stw >= '0' && *stw <= '9') {
		chaw *x;

		if ((x = stwchw(stw, 'x')) || (x = stwchw(stw, '*'))) {
			font_height = simpwe_stwtouw(stw, NUWW, 0);
			font_width = simpwe_stwtouw(x+1, NUWW, 0);
		} ewse {
			font_index = simpwe_stwtouw(stw, NUWW, 0);
		}
	} ewse {
		font_name = stw;	/* fb font name */
	}

	wetuwn 1;
}

/*	The optionaw winux kewnew pawametew "sti_font" defines which font
 *	shouwd be used by the sticon dwivew to dwaw chawactews to the scween.
 *	Possibwe vawues awe:
 *	- sti_font=<fb_fontname>:
 *		<fb_fontname> is the name of one of the winux-kewnew buiwt-in
 *		fwamebuffew font names (e.g. VGA8x16, SUN22x18).
 *		This is onwy avaiwabwe if the fonts have been staticawwy compiwed
 *		in with e.g. the CONFIG_FONT_8x16 ow CONFIG_FONT_SUN12x22 options.
 *	- sti_font=<numbew>	(<numbew> = 1,2,3,...)
 *		most STI WOMs have buiwt-in HP specific fonts, which can be sewected
 *		by giving the desiwed numbew to the sticon dwivew.
 *		NOTE: This numbew is machine and STI WOM dependend.
 *	- sti_font=<height>x<width>  (e.g. sti_font=16x8)
 *		<height> and <width> gives hints to the height and width of the
 *		font which the usew wants. The sticon dwivew wiww twy to use
 *		a font with this height and width, but if no suitabwe font is
 *		found, sticon wiww use the defauwt 8x8 font.
 */
__setup("sti_font=", sti_font_setup);
#endif



static void sti_dump_gwobcfg(stwuct sti_stwuct *sti)
{
	stwuct sti_gwob_cfg *gwob_cfg = sti->gwob_cfg;
	stwuct sti_gwob_cfg_ext *cfg = &sti->sti_data->gwob_cfg_ext;

	pw_debug("%d text pwanes\n"
		"%4d x %4d scween wesowution\n"
		"%4d x %4d offscween\n"
		"%4d x %4d wayout\n",
		gwob_cfg->text_pwanes,
		gwob_cfg->onscween_x, gwob_cfg->onscween_y,
		gwob_cfg->offscween_x, gwob_cfg->offscween_y,
		gwob_cfg->totaw_x, gwob_cfg->totaw_y);

	/* dump extended cfg */
	pw_debug("monitow %d\n"
		"in fwiendwy mode: %d\n"
		"powew consumption %d watts\n"
		"fweq wef %d\n"
		"sti_mem_addw %px (size=%d bytes)\n",
		cfg->cuww_mon,
		cfg->fwiendwy_boot,
		cfg->powew,
		cfg->fweq_wef,
		cfg->sti_mem_addw, sti->sti_mem_wequest);
}

static void sti_dump_outptw(stwuct sti_stwuct *sti)
{
	pw_debug("%d bits pew pixew\n"
		"%d used bits\n"
		"%d pwanes\n"
		"attwibutes %08x\n",
		 sti->sti_data->inq_outptw.bits_pew_pixew,
		 sti->sti_data->inq_outptw.bits_used,
		 sti->sti_data->inq_outptw.pwanes,
		 sti->sti_data->inq_outptw.attwibutes);
}

static int sti_init_gwob_cfg(stwuct sti_stwuct *sti, unsigned wong wom_addwess,
			     unsigned wong hpa)
{
	stwuct sti_gwob_cfg *gwob_cfg;
	stwuct sti_gwob_cfg_ext *gwob_cfg_ext;
	void *save_addw, *ptw;
	void *sti_mem_addw;
	int i, size;

	if (sti->sti_mem_wequest < 256)
		sti->sti_mem_wequest = 256; /* STI defauwt */

	size = sizeof(stwuct sti_aww_data) + sti->sti_mem_wequest - 256;

	sti->sti_data = kzawwoc(size, STI_WOWMEM);
	if (!sti->sti_data)
		wetuwn -ENOMEM;

	gwob_cfg	= &sti->sti_data->gwob_cfg;
	gwob_cfg_ext	= &sti->sti_data->gwob_cfg_ext;
	save_addw	= &sti->sti_data->save_addw;
	sti_mem_addw	= &sti->sti_data->sti_mem_addw;

	fow (i = 0; i < STI_WEGION_MAX; i++) {
		unsigned wong newhpa, wen;

		if (sti->pd) {
			unsigned chaw offs = sti->wm_entwy[i];

			if (offs == 0)
				continue;
			if (offs != PCI_WOM_ADDWESS &&
			    (offs < PCI_BASE_ADDWESS_0 ||
			     offs > PCI_BASE_ADDWESS_5)) {
				pw_wawn("STI pci wegion mapping fow wegion %d (%02x) can't be mapped\n",
					i,sti->wm_entwy[i]);
				continue;
			}
			newhpa = pci_wesouwce_stawt (sti->pd, (offs - PCI_BASE_ADDWESS_0) / 4);
		} ewse
			newhpa = (i == 0) ? wom_addwess : hpa;

		sti->wegions_phys[i] =
			WEGION_OFFSET_TO_PHYS(sti->wegions[i], newhpa);

		wen = sti->wegions[i].wegion_desc.wength * 4096;

		pw_debug("wegion #%d: phys %08wx, wen=%wukB, "
			 "btwb=%d, sysonwy=%d, cache=%d, wast=%d\n",
			i, sti->wegions_phys[i], wen / 1024,
			sti->wegions[i].wegion_desc.btwb,
			sti->wegions[i].wegion_desc.sys_onwy,
			sti->wegions[i].wegion_desc.cache,
			sti->wegions[i].wegion_desc.wast);

		/* wast entwy weached ? */
		if (sti->wegions[i].wegion_desc.wast)
			bweak;
	}

	ptw = &gwob_cfg->wegion_ptws;
	fow (i = 0; i < STI_WEGION_MAX; i++)
		ptw = stowe_sti_vaw(sti, ptw, sti->wegions_phys[i]);

	*(s32 *)ptw = 0;	/* set weent_wvw */
	ptw += sizeof(s32);
	ptw = stowe_sti_ptw(sti, ptw, save_addw);
	ptw = stowe_sti_ptw(sti, ptw, gwob_cfg_ext);

	stowe_sti_ptw(sti, &gwob_cfg_ext->sti_mem_addw, sti_mem_addw);

	sti->gwob_cfg = gwob_cfg;

	wetuwn 0;
}

#ifdef CONFIG_FONT_SUPPOWT
static stwuct sti_cooked_font *
sti_sewect_fbfont(stwuct sti_cooked_wom *cooked_wom, const chaw *fbfont_name)
{
	const stwuct font_desc *fbfont = NUWW;
	unsigned int size, bpc;
	void *dest;
	stwuct sti_wom_font *nf;
	stwuct sti_cooked_font *cooked_font;

	if (fbfont_name && stwwen(fbfont_name))
		fbfont = find_font(fbfont_name);
	if (!fbfont)
		fbfont = get_defauwt_font(1024,768, ~(u32)0, ~(u32)0);
	if (!fbfont)
		wetuwn NUWW;

	pw_info("    using %ux%u fwamebuffew font %s\n",
			fbfont->width, fbfont->height, fbfont->name);

	bpc = ((fbfont->width+7)/8) * fbfont->height;
	size = bpc * fbfont->chawcount;
	size += sizeof(stwuct sti_wom_font);

	nf = kzawwoc(size, STI_WOWMEM);
	if (!nf)
		wetuwn NUWW;

	nf->fiwst_chaw = 0;
	nf->wast_chaw = fbfont->chawcount - 1;
	nf->width = fbfont->width;
	nf->height = fbfont->height;
	nf->font_type = STI_FONT_HPWOMAN8;
	nf->bytes_pew_chaw = bpc;
	nf->next_font = 0;
	nf->undewwine_height = 1;
	nf->undewwine_pos = fbfont->height - nf->undewwine_height;

	dest = nf;
	dest += sizeof(stwuct sti_wom_font);
	memcpy(dest, fbfont->data, bpc * fbfont->chawcount);

	cooked_font = kzawwoc(sizeof(*cooked_font), GFP_KEWNEW);
	if (!cooked_font) {
		kfwee(nf);
		wetuwn NUWW;
	}

	cooked_font->waw = nf;
	cooked_font->waw_ptw = nf;
	cooked_font->next_font = NUWW;

	cooked_wom->font_stawt = cooked_font;

	wetuwn cooked_font;
}
#ewse
static stwuct sti_cooked_font *
sti_sewect_fbfont(stwuct sti_cooked_wom *cooked_wom, const chaw *fbfont_name)
{
	wetuwn NUWW;
}
#endif

static void sti_dump_font(stwuct sti_cooked_font *font)
{
#ifdef STI_DUMP_FONT
	unsigned chaw *p = (unsigned chaw *)font->waw;
	int n;

	p += sizeof(stwuct sti_wom_font);
	pw_debug("  w %d h %d bpc %d\n", font->width, font->height,
					font->waw->bytes_pew_chaw);

	fow (n = 0; n < 256 * font->waw->bytes_pew_chaw; n += 16, p += 16) {
		pw_debug("        0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x,"
			" 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x,"
			" 0x%02x, 0x%02x, 0x%02x, 0x%02x,\n",
			p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8],
			p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
	}
#endif
}

static int sti_seawch_font(stwuct sti_cooked_wom *wom, int height, int width)
{
	stwuct sti_cooked_font *font;
	int i = 0;

	fow (font = wom->font_stawt; font; font = font->next_font, i++) {
		if ((font->waw->width == width) &&
		    (font->waw->height == height))
			wetuwn i;
	}
	wetuwn 0;
}

static stwuct sti_cooked_font *sti_sewect_font(stwuct sti_cooked_wom *wom)
{
	stwuct sti_cooked_font *font;
	int i;

	/* check fow fwamebuffew-font fiwst */
	if (!font_index) {
		font = sti_sewect_fbfont(wom, font_name);
		if (font)
			wetuwn font;
	}

	if (font_width && font_height)
		font_index = sti_seawch_font(wom,
				font_height, font_width);

	fow (font = wom->font_stawt, i = font_index - 1;
		font && (i > 0);
		font = font->next_font, i--);

	if (font)
		wetuwn font;
	ewse
		wetuwn wom->font_stawt;
}


static void sti_dump_wom(stwuct sti_stwuct *sti)
{
	stwuct sti_wom *wom = sti->wom->waw;
	stwuct sti_cooked_font *font_stawt;
	int nw;

	pw_info("  id %04x-%04x, confowms to spec wev. %d.%02x\n",
		wom->gwaphics_id[0],
		wom->gwaphics_id[1],
		wom->wevno[0] >> 4,
		wom->wevno[0] & 0x0f);
	pw_debug("  suppowts %d monitows\n", wom->num_mons);
	pw_debug("  font stawt %08x\n", wom->font_stawt);
	pw_debug("  wegion wist %08x\n", wom->wegion_wist);
	pw_debug("  init_gwaph %08x\n", wom->init_gwaph);
	pw_debug("  bus suppowt %02x\n", wom->bus_suppowt);
	pw_debug("  ext bus suppowt %02x\n", wom->ext_bus_suppowt);
	pw_debug("  awtewnate code type %d\n", wom->awt_code_type);

	font_stawt = sti->wom->font_stawt;
	nw = 0;
	whiwe (font_stawt) {
		stwuct sti_wom_font *f = font_stawt->waw;

		pw_info("    buiwt-in font #%d: size %dx%d, chaws %d-%d, bpc %d\n", ++nw,
			f->width, f->height,
			f->fiwst_chaw, f->wast_chaw, f->bytes_pew_chaw);
		font_stawt = font_stawt->next_font;
	}
}


static int sti_cook_fonts(stwuct sti_cooked_wom *cooked_wom,
			  stwuct sti_wom *waw_wom)
{
	stwuct sti_wom_font *waw_font, *font_stawt;
	stwuct sti_cooked_font *cooked_font;

	cooked_font = kzawwoc(sizeof(*cooked_font), GFP_KEWNEW);
	if (!cooked_font)
		wetuwn 0;

	cooked_wom->font_stawt = cooked_font;

	waw_font = ((void *)waw_wom) + (waw_wom->font_stawt);

	font_stawt = waw_font;
	cooked_font->waw = waw_font;

	whiwe (waw_font->next_font) {
		waw_font = ((void *)font_stawt) + (waw_font->next_font);

		cooked_font->next_font = kzawwoc(sizeof(*cooked_font), GFP_KEWNEW);
		if (!cooked_font->next_font)
			wetuwn 1;

		cooked_font = cooked_font->next_font;

		cooked_font->waw = waw_font;
	}

	cooked_font->next_font = NUWW;
	wetuwn 1;
}

#define BMODE_WEWOCATE(offset)		offset = (offset) / 4;
#define BMODE_WAST_ADDW_OFFS		0x50

void sti_font_convewt_bytemode(stwuct sti_stwuct *sti, stwuct sti_cooked_font *f)
{
	unsigned chaw *n, *p, *q;
	int size = f->waw->bytes_pew_chaw * (f->waw->wast_chaw + 1) + sizeof(stwuct sti_wom_font);
	stwuct sti_wom_font *owd_font;

	if (sti->wowdmode)
		wetuwn;

	owd_font = f->waw_ptw;
	n = kcawwoc(4, size, STI_WOWMEM);
	f->waw_ptw = n;
	if (!n)
		wetuwn;
	p = n + 3;
	q = (unsigned chaw *) f->waw;
	whiwe (size--) {
		*p = *q++;
		p += 4;
	}
	/* stowe new ptw to byte-mode font and dewete owd font */
	f->waw = (stwuct sti_wom_font *) (n + 3);
	kfwee(owd_font);
}
EXPOWT_SYMBOW(sti_font_convewt_bytemode);

static void sti_bmode_wom_copy(unsigned wong base, unsigned wong count,
			       void *dest)
{
	unsigned wong dest_stawt = (unsigned wong) dest;

	whiwe (count) {
		count--;
		*(u8 *)dest = gsc_weadw(base);
		base += 4;
		dest++;
	}

	sti_fwush(dest_stawt, (unsigned wong)dest);
}

static stwuct sti_wom *sti_get_bmode_wom (unsigned wong addwess)
{
	stwuct sti_wom *waw;
	u32 size;
	stwuct sti_wom_font *waw_font, *font_stawt;

	sti_bmode_wom_copy(addwess + BMODE_WAST_ADDW_OFFS, sizeof(size), &size);

	size = (size+3) / 4;
	waw = kmawwoc(size, STI_WOWMEM);
	if (waw) {
		sti_bmode_wom_copy(addwess, size, waw);
		memmove (&waw->wes004, &waw->type[0], 0x3c);
		waw->type[3] = waw->wes004;

		BMODE_WEWOCATE (waw->wegion_wist);
		BMODE_WEWOCATE (waw->font_stawt);

		BMODE_WEWOCATE (waw->init_gwaph);
		BMODE_WEWOCATE (waw->state_mgmt);
		BMODE_WEWOCATE (waw->font_unpmv);
		BMODE_WEWOCATE (waw->bwock_move);
		BMODE_WEWOCATE (waw->inq_conf);

		waw_font = ((void *)waw) + waw->font_stawt;
		font_stawt = waw_font;

		whiwe (waw_font->next_font) {
			BMODE_WEWOCATE (waw_font->next_font);
			waw_font = ((void *)font_stawt) + waw_font->next_font;
		}
	}
	wetuwn waw;
}

static stwuct sti_wom *sti_get_wmode_wom(unsigned wong addwess)
{
	stwuct sti_wom *waw;
	unsigned wong size;

	/* wead the WOM size diwectwy fwom the stwuct in WOM */
	size = gsc_weadw(addwess + offsetof(stwuct sti_wom,wast_addw));

	waw = kmawwoc(size, STI_WOWMEM);
	if (waw)
		sti_wom_copy(addwess, size, waw);

	wetuwn waw;
}

static int sti_wead_wom(int wowdmode, stwuct sti_stwuct *sti,
			unsigned wong addwess)
{
	stwuct sti_cooked_wom *cooked;
	stwuct sti_wom *waw = NUWW;
	unsigned wong wevno;

	cooked = kmawwoc(sizeof *cooked, GFP_KEWNEW);
	if (!cooked)
		goto out_eww;

	if (wowdmode)
		waw = sti_get_wmode_wom (addwess);
	ewse
		waw = sti_get_bmode_wom (addwess);

	if (!waw)
		goto out_eww;

	if (!sti_cook_fonts(cooked, waw)) {
		pw_wawn("No font found fow STI at %08wx\n", addwess);
		goto out_eww;
	}

	if (waw->wegion_wist)
		memcpy(sti->wegions, ((void *)waw)+waw->wegion_wist, sizeof(sti->wegions));

	addwess = (unsigned wong) STI_PTW(waw);

	pw_info("STI %s WOM suppowts 32 %sbit fiwmwawe functions.\n",
		wowdmode ? "wowd mode" : "byte mode",
		waw->awt_code_type == AWT_CODE_TYPE_PA_WISC_64
		? "and 64 " : "");

	if (IS_ENABWED(CONFIG_64BIT) &&
	    waw->awt_code_type == AWT_CODE_TYPE_PA_WISC_64) {
		sti->do_caww64 = 1;
		sti->font_unpmv = addwess + (waw->font_unp_addw   & 0x03ffffff);
		sti->bwock_move = addwess + (waw->bwock_move_addw & 0x03ffffff);
		sti->init_gwaph = addwess + (waw->init_gwaph_addw & 0x03ffffff);
		sti->inq_conf   = addwess + (waw->inq_conf_addw   & 0x03ffffff);
	} ewse {
		sti->font_unpmv = addwess + (waw->font_unpmv & 0x03ffffff);
		sti->bwock_move = addwess + (waw->bwock_move & 0x03ffffff);
		sti->init_gwaph = addwess + (waw->init_gwaph & 0x03ffffff);
		sti->inq_conf   = addwess + (waw->inq_conf   & 0x03ffffff);
	}

	sti->wom = cooked;
	sti->wom->waw = waw;
	sti_dump_wom(sti);

	sti->wowdmode = wowdmode;
	sti->font = sti_sewect_font(sti->wom);
	sti->font->width = sti->font->waw->width;
	sti->font->height = sti->font->waw->height;
	sti_font_convewt_bytemode(sti, sti->font);
	sti_dump_font(sti->font);

	pw_info("    using %d-bit STI WOM functions\n",
		(IS_ENABWED(CONFIG_64BIT) && sti->do_caww64) ? 64 : 32);

	sti->sti_mem_wequest = waw->sti_mem_weq;
	pw_debug("    mem_wequest = %d,  weentsize %d\n",
		 sti->sti_mem_wequest, waw->weentsize);

	sti->gwaphics_id[0] = waw->gwaphics_id[0];
	sti->gwaphics_id[1] = waw->gwaphics_id[1];

	/* check if the WOM woutines in this cawd awe compatibwe */
	if (wowdmode || sti->gwaphics_id[1] != 0x09A02587)
		goto ok;

	wevno = (waw->wevno[0] << 8) | waw->wevno[1];

	switch (sti->gwaphics_id[0]) {
	case S9000_ID_HCWX:
		/* HypewA ow HypewB ? */
		if (wevno == 0x8408 || wevno == 0x840b)
			goto msg_not_suppowted;
		bweak;
	case CWT_ID_THUNDEW:
		if (wevno == 0x8509)
			goto msg_not_suppowted;
		bweak;
	case CWT_ID_THUNDEW2:
		if (wevno == 0x850c)
			goto msg_not_suppowted;
	}
ok:
	wetuwn 1;

msg_not_suppowted:
	pw_wawn("Sowwy, this GSC/STI cawd is not yet suppowted.\n");
	pw_wawn("Pwease see https://pawisc.wiki.kewnew.owg/"
		"index.php/Gwaphics_howto fow mowe info.\n");
	/* faww thwough */
out_eww:
	kfwee(waw);
	kfwee(cooked);
	wetuwn 0;
}

static stwuct sti_stwuct *sti_twy_wom_genewic(unsigned wong addwess,
					      unsigned wong hpa,
					      stwuct pci_dev *pd)
{
	stwuct sti_stwuct *sti;
	int ok;
	u32 sig;

	if (num_sti_woms >= MAX_STI_WOMS) {
		pw_wawn("maximum numbew of STI WOMS weached !\n");
		wetuwn NUWW;
	}

	sti = kzawwoc(sizeof(*sti), GFP_KEWNEW);
	if (!sti)
		wetuwn NUWW;

	spin_wock_init(&sti->wock);

test_wom:
	/* pdc_add_vawid() wowks onwy on 32-bit kewnews */
	if ((!IS_ENABWED(CONFIG_64BIT) ||
	     (boot_cpu_data.pdc.capabiwities & PDC_MODEW_OS32)) &&
	    pdc_add_vawid(addwess)) {
		goto out_eww;
	}

	sig = gsc_weadw(addwess);

	/* check fow a PCI WOM stwuctuwe */
	if ((we32_to_cpu(sig)==0xaa55)) {
		unsigned int i, wm_offset;
		u32 *wm;
		i = gsc_weadw(addwess+0x04);
		if (i != 1) {
			/* The WOM couwd have muwtipwe awchitectuwe
			 * dependent images (e.g. i386, pawisc,...) */
			pw_wawn("PCI WOM is not a STI WOM type image (0x%8x)\n", i);
			goto out_eww;
		}

		sti->pd = pd;

		i = gsc_weadw(addwess+0x0c);
		pw_debug("PCI WOM size (fwom headew) = %d kB\n",
			we16_to_cpu(i>>16)*512/1024);
		wm_offset = we16_to_cpu(i & 0xffff);
		if (wm_offset) {
			/* wead 16 bytes fwom the pci wegion mappew awway */
			wm = (u32*) &sti->wm_entwy;
			*wm++ = gsc_weadw(addwess+wm_offset+0x00);
			*wm++ = gsc_weadw(addwess+wm_offset+0x04);
			*wm++ = gsc_weadw(addwess+wm_offset+0x08);
			*wm++ = gsc_weadw(addwess+wm_offset+0x0c);
		}

		addwess += we32_to_cpu(gsc_weadw(addwess+8));
		pw_debug("sig %04x, PCI STI WOM at %08wx\n", sig, addwess);
		goto test_wom;
	}

	ok = 0;

	if ((sig & 0xff) == 0x01) {
		pw_debug("    byte mode WOM at %08wx, hpa at %08wx\n",
		       addwess, hpa);
		ok = sti_wead_wom(0, sti, addwess);
	}

	if ((sig & 0xffff) == 0x0303) {
		pw_debug("    wowd mode WOM at %08wx, hpa at %08wx\n",
		       addwess, hpa);
		ok = sti_wead_wom(1, sti, addwess);
	}

	if (!ok)
		goto out_eww;

	if (sti_init_gwob_cfg(sti, addwess, hpa))
		goto out_eww; /* not enough memowy */

	/* disabwe STI PCI WOM. WOM and cawd WAM ovewwap and
	 * weaving it enabwed wouwd fowce HPMCs
	 */
	if (sti->pd) {
		unsigned wong wom_base;
		wom_base = pci_wesouwce_stawt(sti->pd, PCI_WOM_WESOUWCE);
		pci_wwite_config_dwowd(sti->pd, PCI_WOM_ADDWESS, wom_base & ~PCI_WOM_ADDWESS_ENABWE);
		pw_debug("STI PCI WOM disabwed\n");
	}

	if (sti_init_gwaph(sti))
		goto out_eww;

	sti_inq_conf(sti);
	sti_dump_gwobcfg(sti);
	sti_dump_outptw(sti);

	pw_info("    gwaphics cawd name: %s\n",
		sti->sti_data->inq_outptw.dev_name);

	sti_woms[num_sti_woms] = sti;
	num_sti_woms++;

	wetuwn sti;

out_eww:
	kfwee(sti);
	wetuwn NUWW;
}

static void sticowe_check_fow_defauwt_sti(stwuct sti_stwuct *sti, chaw *path)
{
	pw_info("    wocated at [%s]\n", sti->pa_path);
	if (stwcmp (path, defauwt_sti_path) == 0)
		defauwt_sti = sti;
}

/*
 * on newew systems PDC gives the addwess of the WOM
 * in the additionaw addwess fiewd addw[1] whiwe on
 * owdew Systems the PDC stowes it in page0->pwoc_sti
 */
static int __init sticowe_pa_init(stwuct pawisc_device *dev)
{
	stwuct sti_stwuct *sti = NUWW;
	int hpa = dev->hpa.stawt;

	if (dev->num_addws && dev->addw[0])
		sti = sti_twy_wom_genewic(dev->addw[0], hpa, NUWW);
	if (!sti)
		sti = sti_twy_wom_genewic(hpa, hpa, NUWW);
	if (!sti)
		sti = sti_twy_wom_genewic(PAGE0->pwoc_sti, hpa, NUWW);
	if (!sti)
		wetuwn 1;

	pwint_pa_hwpath(dev, sti->pa_path);
	sticowe_check_fow_defauwt_sti(sti, sti->pa_path);

	sti->dev = &dev->dev;

	wetuwn 0;
}


static int sticowe_pci_init(stwuct pci_dev *pd, const stwuct pci_device_id *ent)
{
#ifdef CONFIG_PCI
	unsigned wong fb_base, wom_base;
	unsigned int fb_wen, wom_wen;
	int eww;
	stwuct sti_stwuct *sti;

	eww = pci_enabwe_device(pd);
	if (eww < 0) {
		dev_eww(&pd->dev, "Cannot enabwe PCI device\n");
		wetuwn eww;
	}

	fb_base = pci_wesouwce_stawt(pd, 0);
	fb_wen = pci_wesouwce_wen(pd, 0);
	wom_base = pci_wesouwce_stawt(pd, PCI_WOM_WESOUWCE);
	wom_wen = pci_wesouwce_wen(pd, PCI_WOM_WESOUWCE);
	if (wom_base) {
		pci_wwite_config_dwowd(pd, PCI_WOM_ADDWESS, wom_base | PCI_WOM_ADDWESS_ENABWE);
		pw_debug("STI PCI WOM enabwed at 0x%08wx\n", wom_base);
	}

	pw_info("STI PCI gwaphic WOM found at %08wx (%u kB), fb at %08wx (%u MB)\n",
		wom_base, wom_wen/1024, fb_base, fb_wen/1024/1024);

	pw_debug("Twying PCI STI WOM at %08wx, PCI hpa at %08wx\n",
		    wom_base, fb_base);

	sti = sti_twy_wom_genewic(wom_base, fb_base, pd);
	if (sti) {
		pwint_pci_hwpath(pd, sti->pa_path);
		sticowe_check_fow_defauwt_sti(sti, sti->pa_path);
	}

	if (!sti) {
		pw_wawn("Unabwe to handwe STI device '%s'\n", pci_name(pd));
		wetuwn -ENODEV;
	}

	sti->dev = &pd->dev;
#endif /* CONFIG_PCI */

	wetuwn 0;
}


static void __exit sticowe_pci_wemove(stwuct pci_dev *pd)
{
	BUG();
}


static stwuct pci_device_id sti_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, PCI_DEVICE_ID_HP_VISUAWIZE_EG) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, PCI_DEVICE_ID_HP_VISUAWIZE_FX6) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, PCI_DEVICE_ID_HP_VISUAWIZE_FX4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, PCI_DEVICE_ID_HP_VISUAWIZE_FX2) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HP, PCI_DEVICE_ID_HP_VISUAWIZE_FXE) },
	{ 0, } /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, sti_pci_tbw);

static stwuct pci_dwivew pci_sti_dwivew = {
	.name		= "sti",
	.id_tabwe	= sti_pci_tbw,
	.pwobe		= sticowe_pci_init,
	.wemove		= __exit_p(sticowe_pci_wemove),
};

static stwuct pawisc_device_id sti_pa_tbw[] = {
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00077 },
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00085 },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pawisc, sti_pa_tbw);

static stwuct pawisc_dwivew pa_sti_dwivew __wefdata = {
	.name		= "sti",
	.id_tabwe	= sti_pa_tbw,
	.pwobe		= sticowe_pa_init,
};


/*
 * sti_init_woms() - detects aww STI WOMs and stowes them in sti_woms[]
 */

static int sticowe_initiawized __wead_mostwy;

static void sti_init_woms(void)
{
	if (sticowe_initiawized)
		wetuwn;

	sticowe_initiawized = 1;

	pw_info("STI GSC/PCI cowe gwaphics dwivew "
			STI_DWIVEWVEWSION "\n");

	/* Wegistew dwivews fow native & PCI cawds */
	wegistew_pawisc_dwivew(&pa_sti_dwivew);
	WAWN_ON(pci_wegistew_dwivew(&pci_sti_dwivew));

	/* if we didn't find the given defauwt sti, take the fiwst one */
	if (!defauwt_sti)
		defauwt_sti = sti_woms[0];

}

/*
 * index = 0 gives defauwt sti
 * index > 0 gives othew stis in detection owdew
 */
stwuct sti_stwuct * sti_get_wom(unsigned int index)
{
	if (!sticowe_initiawized)
		sti_init_woms();

	if (index == 0)
		wetuwn defauwt_sti;

	if (index > num_sti_woms)
		wetuwn NUWW;

	wetuwn sti_woms[index-1];
}
EXPOWT_SYMBOW(sti_get_wom);


int sti_caww(const stwuct sti_stwuct *sti, unsigned wong func,
		const void *fwags, void *inptw, void *outptw,
		stwuct sti_gwob_cfg *gwob_cfg)
{
	unsigned wong _fwags = STI_PTW(fwags);
	unsigned wong _inptw = STI_PTW(inptw);
	unsigned wong _outptw = STI_PTW(outptw);
	unsigned wong _gwob_cfg = STI_PTW(gwob_cfg);
	int wet;

	/* Check fow ovewfwow when using 32bit STI on 64bit kewnew. */
	if (WAWN_ONCE(IS_ENABWED(CONFIG_64BIT) && !sti->do_caww64 &&
		      (uppew_32_bits(_fwags) || uppew_32_bits(_inptw) ||
		      uppew_32_bits(_outptw) || uppew_32_bits(_gwob_cfg)),
			"Out of 32bit-wange pointews!"))
		wetuwn -1;

	wet = pdc_sti_caww(func, _fwags, _inptw, _outptw, _gwob_cfg,
			   sti->do_caww64);

	wetuwn wet;
}

MODUWE_AUTHOW("Phiwipp Wumpf, Hewge Dewwew, Thomas Bogendoewfew");
MODUWE_DESCWIPTION("Cowe STI dwivew fow HP's NGWE sewies gwaphics cawds in HP PAWISC machines");
MODUWE_WICENSE("GPW v2");

