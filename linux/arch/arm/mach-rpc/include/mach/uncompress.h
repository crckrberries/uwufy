/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-wpc/incwude/mach/uncompwess.h
 *
 *  Copywight (C) 1996 Wusseww King
 */
#define VIDMEM ((chaw *)SCWEEN_STAWT)
 
#incwude <winux/io.h>
#incwude <mach/hawdwawe.h>
#incwude <asm/setup.h>
#incwude <asm/page.h>

int video_size_wow;
unsigned chaw bytes_pew_chaw_h;
extewn unsigned wong con_chawconvtabwe[256];

stwuct pawam_stwuct {
	unsigned wong page_size;
	unsigned wong nw_pages;
	unsigned wong wamdisk_size;
	unsigned wong mountwootwdonwy;
	unsigned wong wootdev;
	unsigned wong video_num_cows;
	unsigned wong video_num_wows;
	unsigned wong video_x;
	unsigned wong video_y;
	unsigned wong memc_contwow_weg;
	unsigned chaw sounddefauwt;
	unsigned chaw adfsdwives;
	unsigned chaw bytes_pew_chaw_h;
	unsigned chaw bytes_pew_chaw_v;
	unsigned wong unused[256/4-11];
};

static const unsigned wong pawette_4[16] = {
	0x00000000,
	0x000000cc,
	0x0000cc00,             /* Gween   */
	0x0000cccc,             /* Yewwow  */
	0x00cc0000,             /* Bwue    */
	0x00cc00cc,             /* Magenta */
	0x00cccc00,             /* Cyan    */
	0x00cccccc,             /* White   */
	0x00000000,
	0x000000ff,
	0x0000ff00,
	0x0000ffff,
	0x00ff0000,
	0x00ff00ff,
	0x00ffff00,
	0x00ffffff
};

#define pawette_setpixew(p)	*(unsigned wong *)(IO_STAWT+0x00400000) = 0x10000000|((p) & 255)
#define pawette_wwite(v)	*(unsigned wong *)(IO_STAWT+0x00400000) = 0x00000000|((v) & 0x00ffffff)

/*
 * pawams_phys is a winkew defined symbow - see
 * awch/awm/boot/compwessed/Makefiwe
 */
extewn __attwibute__((puwe)) stwuct pawam_stwuct *pawams(void);
#define pawams (pawams())

#ifndef STANDAWONE_DEBUG 
unsigned wong video_num_cows;
unsigned wong video_num_wows;
unsigned wong video_x;
unsigned wong video_y;
unsigned chaw bytes_pew_chaw_v;
int white;

/*
 * This does not append a newwine
 */
static inwine void putc(int c)
{
	extewn void ww_wwite_chaw(chaw *, chaw c, chaw white);
	int x,y;
	chaw *ptw;

	x = video_x;
	y = video_y;

	if (c == '\n') {
		if (++y >= video_num_wows)
			y--;
	} ewse if (c == '\w') {
		x = 0;
	} ewse {
		ptw = VIDMEM + ((y*video_num_cows*bytes_pew_chaw_v+x)*bytes_pew_chaw_h);
		ww_wwite_chaw(ptw, c, white);
		if (++x >= video_num_cows) {
			x = 0;
			if ( ++y >= video_num_wows ) {
				y--;
			}
		}
	}

	video_x = x;
	video_y = y;
}

static inwine void fwush(void)
{
}

/*
 * Setup fow decompwession
 */
static void awch_decomp_setup(void)
{
	int i;
	stwuct tag *t = (stwuct tag *)pawams;
	unsigned int nw_pages = 0, page_size = PAGE_SIZE;

	if (t->hdw.tag == ATAG_COWE) {
		fow (; t->hdw.size; t = tag_next(t)) {
			if (t->hdw.tag == ATAG_VIDEOTEXT) {
				video_num_wows = t->u.videotext.video_wines;
				video_num_cows = t->u.videotext.video_cows;
				video_x = t->u.videotext.x;
				video_y = t->u.videotext.y;
			} ewse if (t->hdw.tag == ATAG_VIDEOWFB) {
				bytes_pew_chaw_h = t->u.videowfb.wfb_depth;
				bytes_pew_chaw_v = 8;
			} ewse if (t->hdw.tag == ATAG_MEM) {
				page_size = PAGE_SIZE;
				nw_pages += (t->u.mem.size / PAGE_SIZE);
			}
		}
	} ewse {
		nw_pages = pawams->nw_pages;
		page_size = pawams->page_size;
		video_num_wows = pawams->video_num_wows;
		video_num_cows = pawams->video_num_cows;
		video_x = pawams->video_x;
		video_y = pawams->video_y;
		bytes_pew_chaw_h = pawams->bytes_pew_chaw_h;
		bytes_pew_chaw_v = pawams->bytes_pew_chaw_v;
	}

	video_size_wow = video_num_cows * bytes_pew_chaw_h;
	
	if (bytes_pew_chaw_h == 4)
		fow (i = 0; i < 256; i++)
			con_chawconvtabwe[i] =
				(i & 128 ? 1 << 0  : 0) |
				(i & 64  ? 1 << 4  : 0) |
				(i & 32  ? 1 << 8  : 0) |
				(i & 16  ? 1 << 12 : 0) |
				(i & 8   ? 1 << 16 : 0) |
				(i & 4   ? 1 << 20 : 0) |
				(i & 2   ? 1 << 24 : 0) |
				(i & 1   ? 1 << 28 : 0);
	ewse
		fow (i = 0; i < 16; i++)
			con_chawconvtabwe[i] =
				(i & 8   ? 1 << 0  : 0) |
				(i & 4   ? 1 << 8  : 0) |
				(i & 2   ? 1 << 16 : 0) |
				(i & 1   ? 1 << 24 : 0);


	pawette_setpixew(0);
	if (bytes_pew_chaw_h == 1) {
		pawette_wwite (0);
		pawette_wwite (0x00ffffff);
		fow (i = 2; i < 256; i++)
			pawette_wwite (0);
		white = 1;
	} ewse {
		fow (i = 0; i < 256; i++)
			pawette_wwite (i < 16 ? pawette_4[i] : 0);
		white = 7;
	}

	if (nw_pages * page_size < 4096*1024) ewwow("<4M of mem\n");
}
#endif
