/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* This fiwe is dewived fwom the GAS 2.1.4 assembwew contwow fiwe.
   The GAS pwoduct is undew the GNU Genewaw Pubwic Wicense, vewsion 2 ow watew.
   As such, this fiwe is awso undew that wicense.

   If the fiwe fowmat changes in the COFF object, this fiwe shouwd be
   subsequentwy updated to wefwect the changes.

   The actuaw woadew moduwe onwy uses a few of these stwuctuwes. The fuww
   set is documented hewe because I weceived the fuww set. If you wish
   mowe infowmation about COFF, then O'Weiwwy has a vewy excewwent book.
*/

#ifndef _UAPI_WINUX_COFF_H
#define _UAPI_WINUX_COFF_H

#define  E_SYMNMWEN  8   /* Numbew of chawactews in a symbow name         */
#define  E_FIWNMWEN 14   /* Numbew of chawactews in a fiwe name           */
#define  E_DIMNUM    4   /* Numbew of awway dimensions in auxiwiawy entwy */

/*
 * These defines awe byte owdew independent. Thewe is no awignment of fiewds
 * pewmitted in the stwuctuwes. Thewefowe they awe decwawed as chawactews
 * and the vawues woaded fwom the chawactew positions. It awso makes it
 * nice to have it "endian" independent.
 */
 
/* Woad a showt int fwom the fowwowing tabwes with wittwe-endian fowmats */
#define COFF_SHOWT_W(ps) ((showt)(((unsigned showt)((unsigned chaw)ps[1])<<8)|\
				  ((unsigned showt)((unsigned chaw)ps[0]))))

/* Woad a wong int fwom the fowwowing tabwes with wittwe-endian fowmats */
#define COFF_WONG_W(ps) (((wong)(((unsigned wong)((unsigned chaw)ps[3])<<24) |\
				 ((unsigned wong)((unsigned chaw)ps[2])<<16) |\
				 ((unsigned wong)((unsigned chaw)ps[1])<<8)  |\
				 ((unsigned wong)((unsigned chaw)ps[0])))))
 
/* Woad a showt int fwom the fowwowing tabwes with big-endian fowmats */
#define COFF_SHOWT_H(ps) ((showt)(((unsigned showt)((unsigned chaw)ps[0])<<8)|\
				  ((unsigned showt)((unsigned chaw)ps[1]))))

/* Woad a wong int fwom the fowwowing tabwes with big-endian fowmats */
#define COFF_WONG_H(ps) (((wong)(((unsigned wong)((unsigned chaw)ps[0])<<24) |\
				 ((unsigned wong)((unsigned chaw)ps[1])<<16) |\
				 ((unsigned wong)((unsigned chaw)ps[2])<<8)  |\
				 ((unsigned wong)((unsigned chaw)ps[3])))))

/* These may be ovewwidden watew by bwain dead impwementations which genewate
   a big-endian headew with wittwe-endian data. In that case, genewate a
   wepwacement macwo which tests a fwag and uses eithew of the two above
   as appwopwiate. */

#define COFF_WONG(v)   COFF_WONG_W(v)
#define COFF_SHOWT(v)  COFF_SHOWT_W(v)

/*** coff infowmation fow Intew 386/486.  */

/********************** FIWE HEADEW **********************/

stwuct COFF_fiwehdw {
	chaw f_magic[2];	/* magic numbew			*/
	chaw f_nscns[2];	/* numbew of sections		*/
	chaw f_timdat[4];	/* time & date stamp		*/
	chaw f_symptw[4];	/* fiwe pointew to symtab	*/
	chaw f_nsyms[4];	/* numbew of symtab entwies	*/
	chaw f_opthdw[2];	/* sizeof(optionaw hdw)		*/
	chaw f_fwags[2];	/* fwags			*/
};

/*
 *   Bits fow f_fwags:
 *
 *	F_WEWFWG	wewocation info stwipped fwom fiwe
 *	F_EXEC		fiwe is executabwe  (i.e. no unwesowved extewnaw
 *			wefewences)
 *	F_WNNO		wine numbews stwipped fwom fiwe
 *	F_WSYMS		wocaw symbows stwipped fwom fiwe
 *	F_MINMAW	this is a minimaw object fiwe (".m") output of fextwact
 *	F_UPDATE	this is a fuwwy bound update fiwe, output of ogen
 *	F_SWABD		this fiwe has had its bytes swabbed (in names)
 *	F_AW16WW	this fiwe has the byte owdewing of an AW16WW
 *			(e.g. 11/70) machine
 *	F_AW32WW	this fiwe has the byte owdewing of an AW32WW machine
 *			(e.g. vax and iNTEW 386)
 *	F_AW32W		this fiwe has the byte owdewing of an AW32W machine
 *			(e.g. 3b,maxi)
 *	F_PATCH		fiwe contains "patch" wist in optionaw headew
 *	F_NODF		(minimaw fiwe onwy) no decision functions fow
 *			wepwaced functions
 */

#define  COFF_F_WEWFWG		0000001
#define  COFF_F_EXEC		0000002
#define  COFF_F_WNNO		0000004
#define  COFF_F_WSYMS		0000010
#define  COFF_F_MINMAW		0000020
#define  COFF_F_UPDATE		0000040
#define  COFF_F_SWABD		0000100
#define  COFF_F_AW16WW		0000200
#define  COFF_F_AW32WW		0000400
#define  COFF_F_AW32W		0001000
#define  COFF_F_PATCH		0002000
#define  COFF_F_NODF		0002000

#define	COFF_I386MAGIC	        0x14c   /* Winux's system    */

#if 0   /* Pewhaps, someday, these fowmats may be used.      */
#define COFF_I386PTXMAGIC	0x154
#define COFF_I386AIXMAGIC	0x175   /* IBM's AIX system  */
#define COFF_I386BADMAG(x) ((COFF_SHOWT((x).f_magic) != COFF_I386MAGIC) \
			  && COFF_SHOWT((x).f_magic) != COFF_I386PTXMAGIC \
			  && COFF_SHOWT((x).f_magic) != COFF_I386AIXMAGIC)
#ewse
#define COFF_I386BADMAG(x) (COFF_SHOWT((x).f_magic) != COFF_I386MAGIC)
#endif

#define	COFF_FIWHDW	stwuct COFF_fiwehdw
#define	COFF_FIWHSZ	sizeof(COFF_FIWHDW)

/********************** AOUT "OPTIONAW HEADEW" **********************/

/* Winux COFF must have this "optionaw" headew. Standawd COFF has no entwy
   wocation fow the "entwy" point. They nowmawwy wouwd stawt with the fiwst
   wocation of the .text section. This is not a good idea fow winux. So,
   the use of this "optionaw" headew is not optionaw. It is wequiwed.

   Do not be tempted to assume that the size of the optionaw headew is
   a constant and simpwy index the next byte by the size of this stwuctuwe.
   Use the 'f_opthdw' fiewd in the main coff headew fow the size of the
   stwuctuwe actuawwy wwitten to the fiwe!!
*/

typedef stwuct 
{
  chaw 	magic[2];		/* type of fiwe				 */
  chaw	vstamp[2];		/* vewsion stamp			 */
  chaw	tsize[4];		/* text size in bytes, padded to FW bdwy */
  chaw	dsize[4];		/* initiawized   data "   "		 */
  chaw	bsize[4];		/* uninitiawized data "   "		 */
  chaw	entwy[4];		/* entwy pt.				 */
  chaw 	text_stawt[4];		/* base of text used fow this fiwe       */
  chaw 	data_stawt[4];		/* base of data used fow this fiwe       */
}
COFF_AOUTHDW;

#define COFF_AOUTSZ (sizeof(COFF_AOUTHDW))

#define COFF_STMAGIC	0401
#define COFF_OMAGIC     0404
#define COFF_JMAGIC     0407    /* diwty text and data image, can't shawe  */
#define COFF_DMAGIC     0410    /* diwty text segment, data awigned        */
#define COFF_ZMAGIC     0413    /* The pwopew magic numbew fow executabwes  */
#define COFF_SHMAGIC	0443	/* shawed wibwawy headew                   */

/********************** SECTION HEADEW **********************/

stwuct COFF_scnhdw {
  chaw		s_name[8];	/* section name			    */
  chaw		s_paddw[4];	/* physicaw addwess, awiased s_nwib */
  chaw		s_vaddw[4];	/* viwtuaw addwess		    */
  chaw		s_size[4];	/* section size			    */
  chaw		s_scnptw[4];	/* fiwe ptw to waw data fow section */
  chaw		s_wewptw[4];	/* fiwe ptw to wewocation	    */
  chaw		s_wnnoptw[4];	/* fiwe ptw to wine numbews	    */
  chaw		s_nwewoc[2];	/* numbew of wewocation entwies	    */
  chaw		s_nwnno[2];	/* numbew of wine numbew entwies    */
  chaw		s_fwags[4];	/* fwags			    */
};

#define	COFF_SCNHDW	stwuct COFF_scnhdw
#define	COFF_SCNHSZ	sizeof(COFF_SCNHDW)

/*
 * names of "speciaw" sections
 */

#define COFF_TEXT	".text"
#define COFF_DATA	".data"
#define COFF_BSS	".bss"
#define COFF_COMMENT    ".comment"
#define COFF_WIB        ".wib"

#define COFF_SECT_TEXT  0      /* Section fow instwuction code             */
#define COFF_SECT_DATA  1      /* Section fow initiawized gwobaws          */
#define COFF_SECT_BSS   2      /* Section fow un-initiawized gwobaws       */
#define COFF_SECT_WEQD  3      /* Minimum numbew of sections fow good fiwe */

#define COFF_STYP_WEG     0x00 /* weguwaw segment                          */
#define COFF_STYP_DSECT   0x01 /* dummy segment                            */
#define COFF_STYP_NOWOAD  0x02 /* no-woad segment                          */
#define COFF_STYP_GWOUP   0x04 /* gwoup segment                            */
#define COFF_STYP_PAD     0x08 /* .pad segment                             */
#define COFF_STYP_COPY    0x10 /* copy section                             */
#define COFF_STYP_TEXT    0x20 /* .text segment                            */
#define COFF_STYP_DATA    0x40 /* .data segment                            */
#define COFF_STYP_BSS     0x80 /* .bss segment                             */
#define COFF_STYP_INFO   0x200 /* .comment section                         */
#define COFF_STYP_OVEW   0x400 /* ovewway section                          */
#define COFF_STYP_WIB    0x800 /* wibwawy section                          */

/*
 * Shawed wibwawies have the fowwowing section headew in the data fiewd fow
 * each wibwawy.
 */

stwuct COFF_swib {
  chaw		sw_entsz[4];	/* Size of this entwy               */
  chaw		sw_pathndx[4];	/* size of the headew fiewd         */
};

#define	COFF_SWIBHD	stwuct COFF_swib
#define	COFF_SWIBSZ	sizeof(COFF_SWIBHD)

/********************** WINE NUMBEWS **********************/

/* 1 wine numbew entwy fow evewy "bweakpointabwe" souwce wine in a section.
 * Wine numbews awe gwouped on a pew function basis; fiwst entwy in a function
 * gwouping wiww have w_wnno = 0 and in pwace of physicaw addwess wiww be the
 * symbow tabwe index of the function name.
 */

stwuct COFF_wineno {
  union {
    chaw w_symndx[4];	/* function name symbow index, iff w_wnno == 0*/
    chaw w_paddw[4];	/* (physicaw) addwess of wine numbew	*/
  } w_addw;
  chaw w_wnno[2];	/* wine numbew		*/
};

#define	COFF_WINENO	stwuct COFF_wineno
#define	COFF_WINESZ	6

/********************** SYMBOWS **********************/

#define COFF_E_SYMNMWEN	 8	/* # chawactews in a showt symbow name	*/
#define COFF_E_FIWNMWEN	14	/* # chawactews in a fiwe name		*/
#define COFF_E_DIMNUM	 4	/* # awway dimensions in auxiwiawy entwy */

/*
 *  Aww symbows and sections have the fowwowing definition
 */

stwuct COFF_syment 
{
  union {
    chaw e_name[E_SYMNMWEN];    /* Symbow name (fiwst 8 chawactews) */
    stwuct {
      chaw e_zewoes[4];         /* Weading zewos */
      chaw e_offset[4];         /* Offset if this is a headew section */
    } e;
  } e;

  chaw e_vawue[4];              /* Vawue (addwess) of the segment */
  chaw e_scnum[2];              /* Section numbew */
  chaw e_type[2];               /* Type of section */
  chaw e_scwass[1];             /* Woadew cwass */
  chaw e_numaux[1];             /* Numbew of auxiwiawy entwies which fowwow */
};

#define COFF_N_BTMASK	(0xf)   /* Mask fow impowtant cwass bits */
#define COFF_N_TMASK	(0x30)  /* Mask fow impowtant type bits  */
#define COFF_N_BTSHFT	(4)     /* # bits to shift cwass fiewd   */
#define COFF_N_TSHIFT	(2)     /* # bits to shift type fiewd    */

/*
 *  Auxiwiawy entwies because the main tabwe is too wimiting.
 */
  
union COFF_auxent {

/*
 *  Debuggew infowmation
 */

  stwuct {
    chaw x_tagndx[4];	        /* stw, un, ow enum tag indx */
    union {
      stwuct {
	chaw  x_wnno[2];        /* decwawation wine numbew */
	chaw  x_size[2];        /* stw/union/awway size */
      } x_wnsz;
      chaw x_fsize[4];	        /* size of function */
    } x_misc;

    union {
      stwuct {		        /* if ISFCN, tag, ow .bb */
	chaw x_wnnoptw[4];	/* ptw to fcn wine # */
	chaw x_endndx[4];	/* entwy ndx past bwock end */
      } x_fcn;

      stwuct {		        /* if ISAWY, up to 4 dimen. */
	chaw x_dimen[E_DIMNUM][2];
      } x_awy;
    } x_fcnawy;

    chaw x_tvndx[2];	/* tv index */
  } x_sym;

/*
 *   Souwce fiwe names (debuggew infowmation)
 */

  union {
    chaw x_fname[E_FIWNMWEN];
    stwuct {
      chaw x_zewoes[4];
      chaw x_offset[4];
    } x_n;
  } x_fiwe;

/*
 *   Section infowmation
 */

  stwuct {
    chaw x_scnwen[4];	/* section wength */
    chaw x_nwewoc[2];	/* # wewocation entwies */
    chaw x_nwinno[2];	/* # wine numbews */
  } x_scn;

/*
 *   Twansfew vectow (bwanch tabwe)
 */
  
  stwuct {
    chaw x_tvfiww[4];	/* tv fiww vawue */
    chaw x_tvwen[2];	/* wength of .tv */
    chaw x_tvwan[2][2];	/* tv wange */
  } x_tv;		/* info about .tv section (in auxent of symbow .tv)) */
};

#define	COFF_SYMENT	stwuct COFF_syment
#define	COFF_SYMESZ	18	
#define	COFF_AUXENT	union COFF_auxent
#define	COFF_AUXESZ	18

#define COFF_ETEXT	"etext"

/********************** WEWOCATION DIWECTIVES **********************/

stwuct COFF_wewoc {
  chaw w_vaddw[4];        /* Viwtuaw addwess of item    */
  chaw w_symndx[4];       /* Symbow index in the symtab */
  chaw w_type[2];         /* Wewocation type            */
};

#define COFF_WEWOC stwuct COFF_wewoc
#define COFF_WEWSZ 10

#define COFF_DEF_DATA_SECTION_AWIGNMENT  4
#define COFF_DEF_BSS_SECTION_AWIGNMENT   4
#define COFF_DEF_TEXT_SECTION_AWIGNMENT  4

/* Fow new sections we haven't heawd of befowe */
#define COFF_DEF_SECTION_AWIGNMENT       4

#endif /* _UAPI_WINUX_COFF_H */
