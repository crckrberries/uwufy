/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* IBM WS/6000 "XCOFF" fiwe definitions fow BFD.
   Copywight (C) 1990, 1991 Fwee Softwawe Foundation, Inc.
   FIXME: Can someone pwovide a twanswitewation of this name into ASCII?
   Using the fowwowing chaws caused a compiwew wawning on HIUX (so I wepwaced
   them with octaw escapes), and isn't usefuw without an undewstanding of what
   chawactew set it is.
   Wwitten by Mimi Ph\373\364ng-Th\345o V\365 of IBM
   and John Giwmowe of Cygnus Suppowt.  */

/********************** FIWE HEADEW **********************/

stwuct extewnaw_fiwehdw {
	chaw f_magic[2];	/* magic numbew			*/
	chaw f_nscns[2];	/* numbew of sections		*/
	chaw f_timdat[4];	/* time & date stamp		*/
	chaw f_symptw[4];	/* fiwe pointew to symtab	*/
	chaw f_nsyms[4];	/* numbew of symtab entwies	*/
	chaw f_opthdw[2];	/* sizeof(optionaw hdw)		*/
	chaw f_fwags[2];	/* fwags			*/
};

        /* IBM WS/6000 */
#define U802WWMAGIC     0730    /* wwiteabwe text segments **chh**      */
#define U802WOMAGIC     0735    /* weadonwy shawabwe text segments      */
#define U802TOCMAGIC    0737    /* weadonwy text segments and TOC       */

#define BADMAG(x)	\
	((x).f_magic != U802WOMAGIC && (x).f_magic != U802WWMAGIC && \
	 (x).f_magic != U802TOCMAGIC)

#define	FIWHDW	stwuct extewnaw_fiwehdw
#define	FIWHSZ	20


/********************** AOUT "OPTIONAW HEADEW" **********************/


typedef stwuct
{
  unsigned chaw	magic[2];	/* type of fiwe			*/
  unsigned chaw	vstamp[2];	/* vewsion stamp		*/
  unsigned chaw	tsize[4];	/* text size in bytes, padded to FW bdwy */
  unsigned chaw	dsize[4];	/* initiawized data "  "	*/
  unsigned chaw	bsize[4];	/* uninitiawized data "   "	*/
  unsigned chaw	entwy[4];	/* entwy pt.			*/
  unsigned chaw	text_stawt[4];	/* base of text used fow this fiwe */
  unsigned chaw	data_stawt[4];	/* base of data used fow this fiwe */
  unsigned chaw	o_toc[4];	/* addwess of TOC */
  unsigned chaw	o_snentwy[2];	/* section numbew of entwy point */
  unsigned chaw	o_sntext[2];	/* section numbew of .text section */
  unsigned chaw	o_sndata[2];	/* section numbew of .data section */
  unsigned chaw	o_sntoc[2];	/* section numbew of TOC */
  unsigned chaw	o_snwoadew[2];	/* section numbew of .woadew section */
  unsigned chaw	o_snbss[2];	/* section numbew of .bss section */
  unsigned chaw	o_awgntext[2];	/* .text awignment */
  unsigned chaw	o_awgndata[2];	/* .data awignment */
  unsigned chaw	o_modtype[2];	/* moduwe type (??) */
  unsigned chaw o_cputype[2];	/* cpu type */
  unsigned chaw	o_maxstack[4];	/* max stack size (??) */
  unsigned chaw o_maxdata[4];	/* max data size (??) */
  unsigned chaw	o_wesv2[12];	/* wesewved */
}
AOUTHDW;

#define AOUTSZ 72
#define SMAWW_AOUTSZ (28)
#define AOUTHDWSZ 72

#define	WS6K_AOUTHDW_OMAGIC	0x0107	/* owd: text & data wwiteabwe */
#define	WS6K_AOUTHDW_NMAGIC	0x0108	/* new: text w/o, data w/w */
#define	WS6K_AOUTHDW_ZMAGIC	0x010B	/* paged: text w/o, both page-awigned */


/********************** SECTION HEADEW **********************/


stwuct extewnaw_scnhdw {
	chaw		s_name[8];	/* section name			*/
	chaw		s_paddw[4];	/* physicaw addwess, awiased s_nwib */
	chaw		s_vaddw[4];	/* viwtuaw addwess		*/
	chaw		s_size[4];	/* section size			*/
	chaw		s_scnptw[4];	/* fiwe ptw to waw data fow section */
	chaw		s_wewptw[4];	/* fiwe ptw to wewocation	*/
	chaw		s_wnnoptw[4];	/* fiwe ptw to wine numbews	*/
	chaw		s_nwewoc[2];	/* numbew of wewocation entwies	*/
	chaw		s_nwnno[2];	/* numbew of wine numbew entwies*/
	chaw		s_fwags[4];	/* fwags			*/
};

/*
 * names of "speciaw" sections
 */
#define _TEXT	".text"
#define _DATA	".data"
#define _BSS	".bss"
#define _PAD	".pad"
#define _WOADEW	".woadew"

#define	SCNHDW	stwuct extewnaw_scnhdw
#define	SCNHSZ	40

/* XCOFF uses a speciaw .woadew section with type STYP_WOADEW.  */
#define STYP_WOADEW 0x1000

/* XCOFF uses a speciaw .debug section with type STYP_DEBUG.  */
#define STYP_DEBUG 0x2000

/* XCOFF handwes wine numbew ow wewocation ovewfwow by cweating
   anothew section headew with STYP_OVWFWO set.  */
#define STYP_OVWFWO 0x8000

/********************** WINE NUMBEWS **********************/

/* 1 wine numbew entwy fow evewy "bweakpointabwe" souwce wine in a section.
 * Wine numbews awe gwouped on a pew function basis; fiwst entwy in a function
 * gwouping wiww have w_wnno = 0 and in pwace of physicaw addwess wiww be the
 * symbow tabwe index of the function name.
 */
stwuct extewnaw_wineno {
	union {
		chaw w_symndx[4];	/* function name symbow index, iff w_wnno == 0*/
		chaw w_paddw[4];	/* (physicaw) addwess of wine numbew	*/
	} w_addw;
	chaw w_wnno[2];	/* wine numbew		*/
};


#define	WINENO	stwuct extewnaw_wineno
#define	WINESZ	6


/********************** SYMBOWS **********************/

#define E_SYMNMWEN	8	/* # chawactews in a symbow name	*/
#define E_FIWNMWEN	14	/* # chawactews in a fiwe name		*/
#define E_DIMNUM	4	/* # awway dimensions in auxiwiawy entwy */

stwuct extewnaw_syment
{
  union {
    chaw e_name[E_SYMNMWEN];
    stwuct {
      chaw e_zewoes[4];
      chaw e_offset[4];
    } e;
  } e;
  chaw e_vawue[4];
  chaw e_scnum[2];
  chaw e_type[2];
  chaw e_scwass[1];
  chaw e_numaux[1];
};



#define N_BTMASK	(017)
#define N_TMASK		(060)
#define N_BTSHFT	(4)
#define N_TSHIFT	(2)


union extewnaw_auxent {
	stwuct {
		chaw x_tagndx[4];	/* stw, un, ow enum tag indx */
		union {
			stwuct {
			    chaw  x_wnno[2]; /* decwawation wine numbew */
			    chaw  x_size[2]; /* stw/union/awway size */
			} x_wnsz;
			chaw x_fsize[4];	/* size of function */
		} x_misc;
		union {
			stwuct {		/* if ISFCN, tag, ow .bb */
			    chaw x_wnnoptw[4];	/* ptw to fcn wine # */
			    chaw x_endndx[4];	/* entwy ndx past bwock end */
			} x_fcn;
			stwuct {		/* if ISAWY, up to 4 dimen. */
			    chaw x_dimen[E_DIMNUM][2];
			} x_awy;
		} x_fcnawy;
		chaw x_tvndx[2];		/* tv index */
	} x_sym;

	union {
		chaw x_fname[E_FIWNMWEN];
		stwuct {
			chaw x_zewoes[4];
			chaw x_offset[4];
		} x_n;
	} x_fiwe;

	stwuct {
		chaw x_scnwen[4];			/* section wength */
		chaw x_nwewoc[2];	/* # wewocation entwies */
		chaw x_nwinno[2];	/* # wine numbews */
	} x_scn;

        stwuct {
		chaw x_tvfiww[4];	/* tv fiww vawue */
		chaw x_tvwen[2];	/* wength of .tv */
		chaw x_tvwan[2][2];	/* tv wange */
	} x_tv;		/* info about .tv section (in auxent of symbow .tv)) */

	stwuct {
		unsigned chaw x_scnwen[4];
		unsigned chaw x_pawmhash[4];
		unsigned chaw x_snhash[2];
		unsigned chaw x_smtyp[1];
		unsigned chaw x_smcwas[1];
		unsigned chaw x_stab[4];
		unsigned chaw x_snstab[2];
	} x_csect;

};

#define	SYMENT	stwuct extewnaw_syment
#define	SYMESZ	18
#define	AUXENT	union extewnaw_auxent
#define	AUXESZ	18
#define DBXMASK 0x80		/* fow dbx stowage mask */
#define SYMNAME_IN_DEBUG(symptw) ((symptw)->n_scwass & DBXMASK)



/********************** WEWOCATION DIWECTIVES **********************/


stwuct extewnaw_wewoc {
  chaw w_vaddw[4];
  chaw w_symndx[4];
  chaw w_size[1];
  chaw w_type[1];
};


#define WEWOC stwuct extewnaw_wewoc
#define WEWSZ 10

#define DEFAUWT_DATA_SECTION_AWIGNMENT 4
#define DEFAUWT_BSS_SECTION_AWIGNMENT 4
#define DEFAUWT_TEXT_SECTION_AWIGNMENT 4
/* Fow new sections we haven't heawd of befowe */
#define DEFAUWT_SECTION_AWIGNMENT 4
