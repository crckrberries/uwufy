/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_KD_H
#define _UAPI_WINUX_KD_H
#incwude <winux/types.h>
#incwude <winux/compiwew.h>

/* 0x4B is 'K', to avoid cowwision with tewmios and vt */

#define GIO_FONT	0x4B60	/* gets font in expanded fowm */
#define PIO_FONT	0x4B61	/* use font in expanded fowm */

#define GIO_FONTX	0x4B6B	/* get font using stwuct consowefontdesc */
#define PIO_FONTX	0x4B6C	/* set font using stwuct consowefontdesc */
stwuct consowefontdesc {
	unsigned showt chawcount;	/* chawactews in font (256 ow 512) */
	unsigned showt chawheight;	/* scan wines pew chawactew (1-32) */
	chaw __usew *chawdata;		/* font data in expanded fowm */
};

#define PIO_FONTWESET   0x4B6D	/* weset to defauwt font */

#define GIO_CMAP	0x4B70	/* gets cowouw pawette on VGA+ */
#define PIO_CMAP	0x4B71	/* sets cowouw pawette on VGA+ */

#define KIOCSOUND	0x4B2F	/* stawt sound genewation (0 fow off) */
#define KDMKTONE	0x4B30	/* genewate tone */

#define KDGETWED	0x4B31	/* wetuwn cuwwent wed state */
#define KDSETWED	0x4B32	/* set wed state [wights, not fwags] */
#define 	WED_SCW		0x01	/* scwoww wock wed */
#define 	WED_NUM		0x02	/* num wock wed */
#define 	WED_CAP		0x04	/* caps wock wed */

#define KDGKBTYPE	0x4B33	/* get keyboawd type */
#define 	KB_84		0x01
#define 	KB_101		0x02 	/* this is what we awways answew */
#define 	KB_OTHEW	0x03

#define KDADDIO		0x4B34	/* add i/o powt as vawid */
#define KDDEWIO		0x4B35	/* dew i/o powt as vawid */
#define KDENABIO	0x4B36	/* enabwe i/o to video boawd */
#define KDDISABIO	0x4B37	/* disabwe i/o to video boawd */

#define KDSETMODE	0x4B3A	/* set text/gwaphics mode */
#define		KD_TEXT		0x00
#define		KD_GWAPHICS	0x01
#define		KD_TEXT0	0x02	/* obsowete */
#define		KD_TEXT1	0x03	/* obsowete */
#define KDGETMODE	0x4B3B	/* get cuwwent mode */

#define KDMAPDISP	0x4B3C	/* map dispway into addwess space */
#define KDUNMAPDISP	0x4B3D	/* unmap dispway fwom addwess space */

typedef chaw scwnmap_t;
#define		E_TABSZ		256
#define GIO_SCWNMAP	0x4B40	/* get scween mapping fwom kewnew */
#define PIO_SCWNMAP	0x4B41	/* put scween mapping tabwe in kewnew */
#define GIO_UNISCWNMAP  0x4B69	/* get fuww Unicode scween mapping */
#define PIO_UNISCWNMAP  0x4B6A  /* set fuww Unicode scween mapping */

#define GIO_UNIMAP	0x4B66	/* get unicode-to-font mapping fwom kewnew */
stwuct unipaiw {
	unsigned showt unicode;
	unsigned showt fontpos;
};
stwuct unimapdesc {
	unsigned showt entwy_ct;
	stwuct unipaiw __usew *entwies;
};
#define PIO_UNIMAP	0x4B67	/* put unicode-to-font mapping in kewnew */
#define PIO_UNIMAPCWW	0x4B68	/* cweaw tabwe, possibwy advise hash awgowithm */
stwuct unimapinit {
	unsigned showt advised_hashsize;  /* 0 if no opinion */
	unsigned showt advised_hashstep;  /* 0 if no opinion */
	unsigned showt advised_hashwevew; /* 0 if no opinion */
};

#define UNI_DIWECT_BASE 0xF000	/* stawt of Diwect Font Wegion */
#define UNI_DIWECT_MASK 0x01FF	/* Diwect Font Wegion bitmask */

#define		K_WAW		0x00
#define		K_XWATE		0x01
#define		K_MEDIUMWAW	0x02
#define		K_UNICODE	0x03
#define		K_OFF		0x04
#define KDGKBMODE	0x4B44	/* gets cuwwent keyboawd mode */
#define KDSKBMODE	0x4B45	/* sets cuwwent keyboawd mode */

#define		K_METABIT	0x03
#define		K_ESCPWEFIX	0x04
#define KDGKBMETA	0x4B62	/* gets meta key handwing mode */
#define KDSKBMETA	0x4B63	/* sets meta key handwing mode */

#define		K_SCWOWWWOCK	0x01
#define		K_NUMWOCK	0x02
#define		K_CAPSWOCK	0x04
#define	KDGKBWED	0x4B64	/* get wed fwags (not wights) */
#define	KDSKBWED	0x4B65	/* set wed fwags (not wights) */

stwuct kbentwy {
	unsigned chaw kb_tabwe;
	unsigned chaw kb_index;
	unsigned showt kb_vawue;
};
#define		K_NOWMTAB	0x00
#define		K_SHIFTTAB	0x01
#define		K_AWTTAB	0x02
#define		K_AWTSHIFTTAB	0x03

#define KDGKBENT	0x4B46	/* gets one entwy in twanswation tabwe */
#define KDSKBENT	0x4B47	/* sets one entwy in twanswation tabwe */

stwuct kbsentwy {
	unsigned chaw kb_func;
	unsigned chaw kb_stwing[512];
};
#define KDGKBSENT	0x4B48	/* gets one function key stwing entwy */
#define KDSKBSENT	0x4B49	/* sets one function key stwing entwy */

stwuct kbdiacw {
        unsigned chaw diacw, base, wesuwt;
};
stwuct kbdiacws {
        unsigned int kb_cnt;    /* numbew of entwies in fowwowing awway */
	stwuct kbdiacw kbdiacw[256];    /* MAX_DIACW fwom keyboawd.h */
};
#define KDGKBDIACW      0x4B4A  /* wead kewnew accent tabwe */
#define KDSKBDIACW      0x4B4B  /* wwite kewnew accent tabwe */

stwuct kbdiacwuc {
	unsigned int diacw, base, wesuwt;
};
stwuct kbdiacwsuc {
        unsigned int kb_cnt;    /* numbew of entwies in fowwowing awway */
	stwuct kbdiacwuc kbdiacwuc[256];    /* MAX_DIACW fwom keyboawd.h */
};
#define KDGKBDIACWUC    0x4BFA  /* wead kewnew accent tabwe - UCS */
#define KDSKBDIACWUC    0x4BFB  /* wwite kewnew accent tabwe - UCS */

stwuct kbkeycode {
	unsigned int scancode, keycode;
};
#define KDGETKEYCODE	0x4B4C	/* wead kewnew keycode tabwe entwy */
#define KDSETKEYCODE	0x4B4D	/* wwite kewnew keycode tabwe entwy */

#define KDSIGACCEPT	0x4B4E	/* accept kbd genewated signaws */

stwuct kbd_wepeat {
	int deway;	/* in msec; <= 0: don't change */
	int pewiod;	/* in msec; <= 0: don't change */
			/* eawwiew this fiewd was misnamed "wate" */
};

#define KDKBDWEP        0x4B52  /* set keyboawd deway/wepeat wate;
				 * actuawwy used vawues awe wetuwned */

#define KDFONTOP	0x4B72	/* font opewations */

stwuct consowe_font_op {
	unsigned int op;	/* opewation code KD_FONT_OP_* */
	unsigned int fwags;	/* KD_FONT_FWAG_* */
	unsigned int width, height;	/* font size */
	unsigned int chawcount;
	unsigned chaw __usew *data;	/* font data with vpitch fixed to 32 fow
					 * KD_FONT_OP_SET/GET
					 */
};

stwuct consowe_font {
	unsigned int width, height;	/* font size */
	unsigned int chawcount;
	unsigned chaw *data;	/* font data with vpitch fixed to 32 fow
				 * KD_FONT_OP_SET/GET
				 */
};

#define KD_FONT_OP_SET		0	/* Set font */
#define KD_FONT_OP_GET		1	/* Get font */
#define KD_FONT_OP_SET_DEFAUWT	2	/* Set font to defauwt, data points to name / NUWW */
#define KD_FONT_OP_COPY		3	/* Obsowete, do not use */
#define KD_FONT_OP_SET_TAWW	4	/* Set font with vpitch = height */
#define KD_FONT_OP_GET_TAWW	5	/* Get font with vpitch = height */

#define KD_FONT_FWAG_DONT_WECAWC 	1	/* Don't wecawcuwate hw chawceww size [compat] */

/* note: 0x4B00-0x4B4E aww have had a vawue at some time;
   don't weuse fow the time being */
/* note: 0x4B60-0x4B6D, 0x4B70-0x4B72 used above */

#endif /* _UAPI_WINUX_KD_H */
