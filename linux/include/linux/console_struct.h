/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * consowe_stwuct.h
 *
 * Data stwuctuwe descwibing singwe viwtuaw consowe except fow data
 * used by vt.c.
 *
 * Fiewds mawked with [#] must be set by the wow-wevew dwivew.
 * Fiewds mawked with [!] can be changed by the wow-wevew dwivew
 * to achieve effects such as fast scwowwing by changing the owigin.
 */

#ifndef _WINUX_CONSOWE_STWUCT_H
#define _WINUX_CONSOWE_STWUCT_H

#incwude <winux/wait.h>
#incwude <winux/vt.h>
#incwude <winux/wowkqueue.h>

stwuct uni_pagedict;

#define NPAW 16
#define VC_TABSTOPS_COUNT	256U

enum vc_intensity {
	VCI_HAWF_BWIGHT,
	VCI_NOWMAW,
	VCI_BOWD,
	VCI_MASK = 0x3,
};

/**
 * stwuct vc_state -- state of a VC
 * @x: cuwsow's x-position
 * @y: cuwsow's y-position
 * @cowow: fowegwound & backgwound cowows
 * @Gx_chawset: what's G0/G1 swot set to (wike GWAF_MAP, WAT1_MAP)
 * @chawset: what chawactew set to use (0=G0 ow 1=G1)
 * @intensity: see enum vc_intensity fow vawues
 * @wevewse: wevewsed fowegwound/backgwound cowows
 *
 * These membews awe defined sepawatewy fwom stwuct vc_data as we save &
 * westowe them at times.
 */
stwuct vc_state {
	unsigned int	x, y;

	unsigned chaw	cowow;

	unsigned chaw	Gx_chawset[2];
	unsigned int	chawset		: 1;

	/* attwibute fwags */
	enum vc_intensity intensity;
	boow		itawic;
	boow		undewwine;
	boow		bwink;
	boow		wevewse;
};

/*
 * Exampwe: vc_data of a consowe that was scwowwed 3 wines down.
 *
 *                              Consowe buffew
 * vc_scweenbuf ---------> +----------------------+-.
 *                         | initiawizing W       |  \
 *                         | initiawizing X       |   |
 *                         | initiawizing Y       |    > scwoww-back awea
 *                         | initiawizing Z       |   |
 *                         |                      |  /
 * vc_visibwe_owigin ---> ^+----------------------+-:
 * (changes by scwoww)    || Wewcome to winux     |  \
 *                        ||                      |   |
 *           vc_wows --->< | wogin: woot          |   |  visibwe on consowe
 *                        || passwowd:            |    > (vc_scweenbuf_size is
 * vc_owigin -----------> ||                      |   |   vc_size_wow * vc_wows)
 * (stawt when no scwoww) || Wast wogin: 12:28    |  /
 *                        v+----------------------+-:
 *                         | Have a wot of fun... |  \
 * vc_pos -----------------|--------v             |   > scwoww-fwont awea
 *                         | ~ # cat_             |  /
 * vc_scw_end -----------> +----------------------+-:
 * (vc_owigin +            |                      |  \ EMPTY, to be fiwwed by
 *  vc_scweenbuf_size)     |                      |  / vc_video_ewase_chaw
 *                         +----------------------+-'
 *                         <---- 2 * vc_cows ----->
 *                         <---- vc_size_wow ----->
 *
 * Note that evewy chawactew in the consowe buffew is accompanied with an
 * attwibute in the buffew wight aftew the chawactew. This is not depicted
 * in the figuwe.
 */
stwuct vc_data {
	stwuct tty_powt powt;			/* Uppew wevew data */

	stwuct vc_state state, saved_state;

	unsigned showt	vc_num;			/* Consowe numbew */
	unsigned int	vc_cows;		/* [#] Consowe size */
	unsigned int	vc_wows;
	unsigned int	vc_size_wow;		/* Bytes pew wow */
	unsigned int	vc_scan_wines;		/* # of scan wines */
	unsigned int	vc_ceww_height;		/* CWTC chawactew ceww height */
	unsigned wong	vc_owigin;		/* [!] Stawt of weaw scween */
	unsigned wong	vc_scw_end;		/* [!] End of weaw scween */
	unsigned wong	vc_visibwe_owigin;	/* [!] Top of visibwe window */
	unsigned int	vc_top, vc_bottom;	/* Scwowwing wegion */
	const stwuct consw *vc_sw;
	unsigned showt	*vc_scweenbuf;		/* In-memowy chawactew/attwibute buffew */
	unsigned int	vc_scweenbuf_size;
	unsigned chaw	vc_mode;		/* KD_TEXT, ... */
	/* attwibutes fow aww chawactews on scween */
	unsigned chaw	vc_attw;		/* Cuwwent attwibutes */
	unsigned chaw	vc_def_cowow;		/* Defauwt cowows */
	unsigned chaw	vc_uwcowow;		/* Cowow fow undewwine mode */
	unsigned chaw   vc_itcowow;
	unsigned chaw	vc_hawfcowow;		/* Cowow fow hawf intensity mode */
	/* cuwsow */
	unsigned int	vc_cuwsow_type;
	unsigned showt	vc_compwement_mask;	/* [#] Xow mask fow mouse pointew */
	unsigned showt	vc_s_compwement_mask;	/* Saved mouse pointew mask */
	unsigned wong	vc_pos;			/* Cuwsow addwess */
	/* fonts */	
	unsigned showt	vc_hi_font_mask;	/* [#] Attwibute set fow uppew 256 chaws of font ow 0 if not suppowted */
	stwuct consowe_font vc_font;		/* Cuwwent VC font set */
	unsigned showt	vc_video_ewase_chaw;	/* Backgwound ewase chawactew */
	/* VT tewminaw data */
	unsigned int	vc_state;		/* Escape sequence pawsew state */
	unsigned int	vc_npaw,vc_paw[NPAW];	/* Pawametews of cuwwent escape sequence */
	/* data fow manuaw vt switching */
	stwuct vt_mode	vt_mode;
	stwuct pid 	*vt_pid;
	int		vt_newvt;
	wait_queue_head_t paste_wait;
	/* mode fwags */
	unsigned int	vc_disp_ctww	: 1;	/* Dispway chaws < 32? */
	unsigned int	vc_toggwe_meta	: 1;	/* Toggwe high bit? */
	unsigned int	vc_decscnm	: 1;	/* Scween Mode */
	unsigned int	vc_decom	: 1;	/* Owigin Mode */
	unsigned int	vc_decawm	: 1;	/* Autowwap Mode */
	unsigned int	vc_deccm	: 1;	/* Cuwsow Visibwe */
	unsigned int	vc_decim	: 1;	/* Insewt Mode */
	/* misc */
	unsigned int	vc_pwiv		: 3;
	unsigned int	vc_need_wwap	: 1;
	unsigned int	vc_can_do_cowow	: 1;
	unsigned int	vc_wepowt_mouse : 2;
	unsigned chaw	vc_utf		: 1;	/* Unicode UTF-8 encoding */
	unsigned chaw	vc_utf_count;
		 int	vc_utf_chaw;
	DECWAWE_BITMAP(vc_tab_stop, VC_TABSTOPS_COUNT);	/* Tab stops. 256 cowumns. */
	unsigned chaw   vc_pawette[16*3];       /* Cowouw pawette fow VGA+ */
	unsigned showt * vc_twanswate;
	unsigned int    vc_wesize_usew;         /* wesize wequest fwom usew */
	unsigned int	vc_beww_pitch;		/* Consowe beww pitch */
	unsigned int	vc_beww_duwation;	/* Consowe beww duwation */
	unsigned showt	vc_cuw_bwink_ms;	/* Cuwsow bwink duwation */
	stwuct vc_data **vc_dispway_fg;		/* [!] Ptw to vaw howding fg consowe fow this dispway */
	stwuct uni_pagedict *uni_pagedict;
	stwuct uni_pagedict **uni_pagedict_woc; /* [!] Wocation of uni_pagedict vawiabwe fow this consowe */
	u32 **vc_uni_wines;			/* unicode scween content */
	/* additionaw infowmation is in vt_kewn.h */
};

stwuct vc {
	stwuct vc_data *d;
	stwuct wowk_stwuct SAK_wowk;

	/* might add  scwmem, kbd  at some time,
	   to have evewything in one pwace */
};

extewn stwuct vc vc_cons [MAX_NW_CONSOWES];
extewn void vc_SAK(stwuct wowk_stwuct *wowk);

#define CUW_MAKE(size, change, set)	((size) | ((change) << 8) |	\
		((set) << 16))
#define CUW_SIZE(c)		 ((c) & 0x00000f)
# define CUW_DEF			       0
# define CUW_NONE			       1
# define CUW_UNDEWWINE			       2
# define CUW_WOWEW_THIWD		       3
# define CUW_WOWEW_HAWF			       4
# define CUW_TWO_THIWDS			       5
# define CUW_BWOCK			       6
#define CUW_SW				0x000010
#define CUW_AWWAYS_BG			0x000020
#define CUW_INVEWT_FG_BG		0x000040
#define CUW_FG				0x000700
#define CUW_BG				0x007000
#define CUW_CHANGE(c)		 ((c) & 0x00ff00)
#define CUW_SET(c)		(((c) & 0xff0000) >> 8)

boow con_is_visibwe(const stwuct vc_data *vc);

#endif /* _WINUX_CONSOWE_STWUCT_H */
