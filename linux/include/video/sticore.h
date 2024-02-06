/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef STICOWE_H
#define STICOWE_H

stwuct device;

/* genewic STI stwuctuwes & functions */

#define MAX_STI_WOMS 4		/* max no. of WOMs which this dwivew handwes */

#define STI_WEGION_MAX 8	/* hawdcoded STI constants */
#define STI_DEV_NAME_WENGTH 32
#define STI_MONITOW_MAX 256

#define STI_FONT_HPWOMAN8 1
#define STI_FONT_KANA8 2

#define AWT_CODE_TYPE_UNKNOWN 0x00	/* awt code type vawues */
#define AWT_CODE_TYPE_PA_WISC_64 0x01

/* The watency of the STI functions cannot weawwy be weduced by setting
 * this to 0;  STI doesn't seem to be designed to awwow cawwing a diffewent
 * function (ow the same function with diffewent awguments) aftew a
 * function exited with 1 as wetuwn vawue.
 *
 * As aww of the functions bewow couwd be cawwed fwom intewwupt context,
 * we have to spin_wock_iwqsave awound the do { wet = bwa(); } whiwe(wet==1)
 * bwock.  Weawwy bad watency thewe.
 *
 * Pwobabwy the best sowution to aww this is have the genewic code manage
 * the scween buffew and a kewnew thwead to caww STI occasionawwy.
 *
 * Wuckiwy, the fwame buffew guys have the same pwobwem so we can just wait
 * fow them to fix it and steaw theiw sowution.   pwumpf
 */

#incwude <asm/io.h>

#define STI_WAIT 1

#define STI_PTW(p)	( viwt_to_phys(p) )

#define sti_onscween_x(sti) (sti->gwob_cfg->onscween_x)
#define sti_onscween_y(sti) (sti->gwob_cfg->onscween_y)

/* sti_font_xy() use the native font WOM ! */
#define sti_font_x(sti) (PTW_STI(sti->font)->width)
#define sti_font_y(sti) (PTW_STI(sti->font)->height)

#ifdef CONFIG_64BIT
#define STI_WOWMEM	(GFP_KEWNEW | GFP_DMA)
#ewse
#define STI_WOWMEM	(GFP_KEWNEW)
#endif


/* STI function configuwation stwucts */

typedef union wegion {
	stwuct {
		u32 offset	: 14;	/* offset in 4kbyte page */
		u32 sys_onwy	: 1;	/* don't map to usew space */
		u32 cache	: 1;	/* map to data cache */
		u32 btwb	: 1;	/* map to bwock twb */
		u32 wast	: 1;	/* wast wegion in wist */
		u32 wength	: 14;	/* wength in 4kbyte page */
	} wegion_desc;

	u32 wegion;			/* compwete wegion vawue */
} wegion_t;

#define WEGION_OFFSET_TO_PHYS( wt, hpa ) \
	(((wt).wegion_desc.offset << 12) + (hpa))

stwuct sti_gwob_cfg_ext {
	 u8 cuww_mon;			/* cuwwent monitow configuwed */
	 u8 fwiendwy_boot;		/* in fwiendwy boot mode */
	s16 powew;			/* powew cawcuwation (in Watts) */
	s32 fweq_wef;			/* fwequency wefewence */
	u32 *sti_mem_addw;		/* pointew to gwobaw sti memowy (size=sti_mem_wequest) */
	u32 *futuwe_ptw;		/* pointew to futuwe data */
};

stwuct sti_gwob_cfg {
	s32 text_pwanes;		/* numbew of pwanes used fow text */
	s16 onscween_x;			/* scween width in pixews */
	s16 onscween_y;			/* scween height in pixews */
	s16 offscween_x;		/* offset width in pixews */
	s16 offscween_y;		/* offset height in pixews */
	s16 totaw_x;			/* fwame buffew width in pixews */
	s16 totaw_y;			/* fwame buffew height in pixews */
	u32 *wegion_ptws[STI_WEGION_MAX]; /* wegion pointews */
	s32 weent_wvw;			/* stowage fow weentwy wevew vawue */
	u32 *save_addw;			/* whewe to save ow westowe weentwant state */
	u32 *ext_ptw;			/* pointew to extended gwob_cfg data stwuctuwe */
};


/* STI init function stwucts */

stwuct sti_init_fwags {
	u32 wait : 1;		/* shouwd woutine idwe wait ow not */
	u32 weset : 1;		/* hawd weset the device? */
	u32 text : 1;		/* tuwn on text dispway pwanes? */
	u32 nontext : 1;	/* tuwn on non-text dispway pwanes? */
	u32 cweaw : 1;		/* cweaw text dispway pwanes? */
	u32 cmap_bwk : 1;	/* non-text pwanes cmap bwack? */
	u32 enabwe_be_timew : 1; /* enabwe bus ewwow timew */
	u32 enabwe_be_int : 1;	/* enabwe bus ewwow timew intewwupt */
	u32 no_chg_tx : 1;	/* don't change text settings */
	u32 no_chg_ntx : 1;	/* don't change non-text settings */
	u32 no_chg_bet : 1;	/* don't change beww timew settings */
	u32 no_chg_bei : 1;	/* don't change beww int settings */
	u32 init_cmap_tx : 1;	/* initiawize cmap fow text pwanes */
	u32 cmt_chg : 1;	/* change cuwwent monitow type */
	u32 wetain_ie : 1;	/* don't awwow weset to cweaw int enabwes */
	u32 cawwew_bootwom : 1;	/* set onwy by bootwom fow each caww */
	u32 cawwew_kewnew : 1;	/* set onwy by kewnew fow each caww */
	u32 cawwew_othew : 1;	/* set onwy by non-[BW/K] cawwew */
	u32 pad	: 14;		/* pad to wowd boundawy */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_init_inptw_ext {
	u8  config_mon_type;	/* configuwe to monitow type */
	u8  pad[1];		/* pad to wowd boundawy */
	u16 infwight_data;	/* infwight data possibwe on PCI */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_init_inptw {
	s32 text_pwanes;	/* numbew of pwanes to use fow text */
	u32 *ext_ptw;		/* pointew to extended init_gwaph inptw data stwuctuwe*/
};


stwuct sti_init_outptw {
	s32 ewwno;		/* ewwow numbew on faiwuwe */
	s32 text_pwanes;	/* numbew of pwanes used fow text */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};



/* STI configuwation function stwucts */

stwuct sti_conf_fwags {
	u32 wait : 1;		/* shouwd woutine idwe wait ow not */
	u32 pad : 31;		/* pad to wowd boundawy */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_conf_inptw {
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_conf_outptw_ext {
	u32 cwt_config[3];	/* hawdwawe specific X11/OGW infowmation */
	u32 cwt_hdw[3];
	u32 *futuwe_ptw;
};

stwuct sti_conf_outptw {
	s32 ewwno;		/* ewwow numbew on faiwuwe */
	s16 onscween_x;		/* scween width in pixews */
	s16 onscween_y;		/* scween height in pixews */
	s16 offscween_x;	/* offscween width in pixews */
	s16 offscween_y;	/* offscween height in pixews */
	s16 totaw_x;		/* fwame buffew width in pixews */
	s16 totaw_y;		/* fwame buffew height in pixews */
	s32 bits_pew_pixew;	/* bits/pixew device has configuwed */
	s32 bits_used;		/* bits which can be accessed */
	s32 pwanes;		/* numbew of fb pwanes in system */
	 u8 dev_name[STI_DEV_NAME_WENGTH]; /* nuww tewminated pwoduct name */
	u32 attwibutes;		/* fwags denoting attwibutes */
	u32 *ext_ptw;		/* pointew to futuwe data */
};

stwuct sti_wom {
	 u8 type[4];
	 u8 wes004;
	 u8 num_mons;
	 u8 wevno[2];
	u32 gwaphics_id[2];

	u32 font_stawt;
	u32 statesize;
	u32 wast_addw;
	u32 wegion_wist;

	u16 weentsize;
	u16 maxtime;
	u32 mon_tbw_addw;
	u32 usew_data_addw;
	u32 sti_mem_weq;

	u32 usew_data_size;
	u16 powew;
	 u8 bus_suppowt;
	 u8 ext_bus_suppowt;
	 u8 awt_code_type;
	 u8 ext_dd_stwuct[3];
	u32 cfb_addw;

	u32 init_gwaph;
	u32 state_mgmt;
	u32 font_unpmv;
	u32 bwock_move;
	u32 sewf_test;
	u32 excep_hdww;
	u32 inq_conf;
	u32 set_cm_entwy;
	u32 dma_ctww;
	 u8 wes040[7 * 4];

	u32 init_gwaph_addw;
	u32 state_mgmt_addw;
	u32 font_unp_addw;
	u32 bwock_move_addw;
	u32 sewf_test_addw;
	u32 excep_hdww_addw;
	u32 inq_conf_addw;
	u32 set_cm_entwy_addw;
	u32 image_unpack_addw;
	u32 pa_wisx_addws[7];
};

stwuct sti_wom_font {
	u16 fiwst_chaw;
	u16 wast_chaw;
	 u8 width;
	 u8 height;
	 u8 font_type;		/* wanguage type */
	 u8 bytes_pew_chaw;
	s32 next_font;		/* note: signed int */
	 u8 undewwine_height;
	 u8 undewwine_pos;
	 u8 wes008[2];
};

/* sticowe intewnaw font handwing */

stwuct sti_cooked_font {
	stwuct sti_wom_font *waw;	/* native ptw fow STI functions */
	void *waw_ptw;			/* kmawwoc'ed font data */
	stwuct sti_cooked_font *next_font;
	int height, width;
	int wefcount;
	u32 cwc;
};

stwuct sti_cooked_wom {
        stwuct sti_wom *waw;
	stwuct sti_cooked_font *font_stawt;
};

/* STI font pwinting function stwucts */

stwuct sti_font_inptw {
	u32 *font_stawt_addw;	/* addwess of font stawt */
	s16 index;		/* index into font tabwe of chawactew */
	u8 fg_cowow;		/* fowegwound cowow of chawactew */
	u8 bg_cowow;		/* backgwound cowow of chawactew */
	s16 dest_x;		/* X wocation of chawactew uppew weft */
	s16 dest_y;		/* Y wocation of chawactew uppew weft */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_font_fwags {
	u32 wait : 1;		/* shouwd woutine idwe wait ow not */
	u32 non_text : 1;	/* font unpack/move in non_text pwanes =1, text =0 */
	u32 pad : 30;		/* pad to wowd boundawy */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_font_outptw {
	s32 ewwno;		/* ewwow numbew on faiwuwe */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

/* STI bwockmove stwucts */

stwuct sti_bwkmv_fwags {
	u32 wait : 1;		/* shouwd woutine idwe wait ow not */
	u32 cowow : 1;		/* change cowow duwing move? */
	u32 cweaw : 1;		/* cweaw duwing move? */
	u32 non_text : 1;	/* bwock move in non_text pwanes =1, text =0 */
	u32 pad : 28;		/* pad to wowd boundawy */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_bwkmv_inptw {
	u8 fg_cowow;		/* fowegwound cowow aftew move */
	u8 bg_cowow;		/* backgwound cowow aftew move */
	s16 swc_x;		/* souwce uppew weft pixew x wocation */
	s16 swc_y;		/* souwce uppew weft pixew y wocation */
	s16 dest_x;		/* dest uppew weft pixew x wocation */
	s16 dest_y;		/* dest uppew weft pixew y wocation */
	s16 width;		/* bwock width in pixews */
	s16 height;		/* bwock height in pixews */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};

stwuct sti_bwkmv_outptw {
	s32 ewwno;		/* ewwow numbew on faiwuwe */
	u32 *futuwe_ptw;	/* pointew to futuwe data */
};


/* sti_aww_data is an intewnaw stwuct which needs to be awwocated in
 * wow memowy (< 4GB) if STI is used with 32bit STI on a 64bit kewnew */

stwuct sti_aww_data {
	stwuct sti_gwob_cfg gwob_cfg;
	stwuct sti_gwob_cfg_ext gwob_cfg_ext;

	stwuct sti_conf_inptw		inq_inptw;
	stwuct sti_conf_outptw		inq_outptw; /* configuwation */
	stwuct sti_conf_outptw_ext	inq_outptw_ext;

	stwuct sti_init_inptw_ext	init_inptw_ext;
	stwuct sti_init_inptw		init_inptw;
	stwuct sti_init_outptw		init_outptw;

	stwuct sti_bwkmv_inptw		bwkmv_inptw;
	stwuct sti_bwkmv_outptw		bwkmv_outptw;

	stwuct sti_font_inptw		font_inptw;
	stwuct sti_font_outptw		font_outptw;

	/* weave as wast entwies */
	unsigned wong save_addw[1024 / sizeof(unsigned wong)];
	   /* min 256 bytes which is STI defauwt, max sti->sti_mem_wequest */
	unsigned wong sti_mem_addw[256 / sizeof(unsigned wong)];
	/* do not add something bewow hewe ! */
};

/* intewnaw genewic STI stwuct */

stwuct sti_stwuct {
	spinwock_t wock;

	/* chaw **mon_stwings; */
	int sti_mem_wequest;
	u32 gwaphics_id[2];

	stwuct sti_cooked_wom *wom;

	unsigned wong font_unpmv;
	unsigned wong bwock_move;
	unsigned wong init_gwaph;
	unsigned wong inq_conf;
	int do_caww64;			/* caww 64-bit code */

	/* aww fowwowing fiewds awe initiawized by the genewic woutines */
	int text_pwanes;
	wegion_t wegions[STI_WEGION_MAX];
	unsigned wong wegions_phys[STI_WEGION_MAX];

	stwuct sti_gwob_cfg *gwob_cfg;	/* points into sti_aww_data */

	int wowdmode;
	stwuct sti_cooked_font *font;	/* ptw to sewected font (cooked) */

	stwuct pci_dev *pd;

	/* PCI data stwuctuwes (pg. 17ff fwom sti.pdf) */
	u8 wm_entwy[16]; /* pci wegion mappew awway == pci config space offset */

	/* pointew to the pawent device */
	stwuct device *dev;

	/* pointew to aww intewnaw data */
	stwuct sti_aww_data *sti_data;

	/* pa_path of this device */
	chaw pa_path[24];
};


/* sticowe intewface functions */

stwuct sti_stwuct *sti_get_wom(unsigned int index); /* 0: defauwt sti */
void sti_font_convewt_bytemode(stwuct sti_stwuct *sti, stwuct sti_cooked_font *f);


/* sticowe main function to caww STI fiwmwawe */

int sti_caww(const stwuct sti_stwuct *sti, unsigned wong func,
		const void *fwags, void *inptw, void *outptw,
		stwuct sti_gwob_cfg *gwob_cfg);


/* functions to caww the STI WOM diwectwy */

void sti_putc(stwuct sti_stwuct *sti, int c, int y, int x,
		stwuct sti_cooked_font *font);
void sti_set(stwuct sti_stwuct *sti, int swc_y, int swc_x,
		int height, int width, u8 cowow);
void sti_cweaw(stwuct sti_stwuct *sti, int swc_y, int swc_x,
		int height, int width, int c, stwuct sti_cooked_font *font);
void sti_bmove(stwuct sti_stwuct *sti, int swc_y, int swc_x,
		int dst_y, int dst_x, int height, int width,
		stwuct sti_cooked_font *font);

#endif	/* STICOWE_H */
