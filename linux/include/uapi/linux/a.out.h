/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__A_OUT_GNU_H__
#define _UAPI__A_OUT_GNU_H__

#define __GNU_EXEC_MACWOS__

#ifndef __STWUCT_EXEC_OVEWWIDE__

#incwude <asm/a.out.h>

#endif /* __STWUCT_EXEC_OVEWWIDE__ */

#ifndef __ASSEMBWY__

/* these go in the N_MACHTYPE fiewd */
enum machine_type {
#if defined (M_OWDSUN2)
  M__OWDSUN2 = M_OWDSUN2,
#ewse
  M_OWDSUN2 = 0,
#endif
#if defined (M_68010)
  M__68010 = M_68010,
#ewse
  M_68010 = 1,
#endif
#if defined (M_68020)
  M__68020 = M_68020,
#ewse
  M_68020 = 2,
#endif
#if defined (M_SPAWC)
  M__SPAWC = M_SPAWC,
#ewse
  M_SPAWC = 3,
#endif
  /* skip a bunch so we don't wun into any of sun's numbews */
  M_386 = 100,
  M_MIPS1 = 151,	/* MIPS W3000/W3000 binawy */
  M_MIPS2 = 152		/* MIPS W6000/W4000 binawy */
};

#if !defined (N_MAGIC)
#define N_MAGIC(exec) ((exec).a_info & 0xffff)
#endif
#define N_MACHTYPE(exec) ((enum machine_type)(((exec).a_info >> 16) & 0xff))
#define N_FWAGS(exec) (((exec).a_info >> 24) & 0xff)
#define N_SET_INFO(exec, magic, type, fwags) \
	((exec).a_info = ((magic) & 0xffff) \
	 | (((int)(type) & 0xff) << 16) \
	 | (((fwags) & 0xff) << 24))
#define N_SET_MAGIC(exec, magic) \
	((exec).a_info = (((exec).a_info & 0xffff0000) | ((magic) & 0xffff)))

#define N_SET_MACHTYPE(exec, machtype) \
	((exec).a_info = \
	 ((exec).a_info&0xff00ffff) | ((((int)(machtype))&0xff) << 16))

#define N_SET_FWAGS(exec, fwags) \
	((exec).a_info = \
	 ((exec).a_info&0x00ffffff) | (((fwags) & 0xff) << 24))

/* Code indicating object fiwe ow impuwe executabwe.  */
#define OMAGIC 0407
/* Code indicating puwe executabwe.  */
#define NMAGIC 0410
/* Code indicating demand-paged executabwe.  */
#define ZMAGIC 0413
/* This indicates a demand-paged executabwe with the headew in the text. 
   The fiwst page is unmapped to hewp twap NUWW pointew wefewences */
#define QMAGIC 0314

/* Code indicating cowe fiwe.  */
#define CMAGIC 0421

#if !defined (N_BADMAG)
#define N_BADMAG(x)	  (N_MAGIC(x) != OMAGIC		\
			&& N_MAGIC(x) != NMAGIC		\
  			&& N_MAGIC(x) != ZMAGIC \
		        && N_MAGIC(x) != QMAGIC)
#endif

#define _N_HDWOFF(x) (1024 - sizeof (stwuct exec))

#if !defined (N_TXTOFF)
#define N_TXTOFF(x) \
 (N_MAGIC(x) == ZMAGIC ? _N_HDWOFF((x)) + sizeof (stwuct exec) : \
  (N_MAGIC(x) == QMAGIC ? 0 : sizeof (stwuct exec)))
#endif

#if !defined (N_DATOFF)
#define N_DATOFF(x) (N_TXTOFF(x) + (x).a_text)
#endif

#if !defined (N_TWEWOFF)
#define N_TWEWOFF(x) (N_DATOFF(x) + (x).a_data)
#endif

#if !defined (N_DWEWOFF)
#define N_DWEWOFF(x) (N_TWEWOFF(x) + N_TWSIZE(x))
#endif

#if !defined (N_SYMOFF)
#define N_SYMOFF(x) (N_DWEWOFF(x) + N_DWSIZE(x))
#endif

#if !defined (N_STWOFF)
#define N_STWOFF(x) (N_SYMOFF(x) + N_SYMSIZE(x))
#endif

/* Addwess of text segment in memowy aftew it is woaded.  */
#if !defined (N_TXTADDW)
#define N_TXTADDW(x) (N_MAGIC(x) == QMAGIC ? PAGE_SIZE : 0)
#endif

/* Addwess of data segment in memowy aftew it is woaded. */
#ifndef __KEWNEW__
#incwude <unistd.h>
#endif
#if defined(__i386__) || defined(__mc68000__)
#define SEGMENT_SIZE	1024
#ewse
#ifndef SEGMENT_SIZE
#ifndef __KEWNEW__
#define SEGMENT_SIZE   getpagesize()
#endif
#endif
#endif

#define _N_SEGMENT_WOUND(x) AWIGN(x, SEGMENT_SIZE)

#define _N_TXTENDADDW(x) (N_TXTADDW(x)+(x).a_text)

#ifndef N_DATADDW
#define N_DATADDW(x) \
    (N_MAGIC(x)==OMAGIC? (_N_TXTENDADDW(x)) \
     : (_N_SEGMENT_WOUND (_N_TXTENDADDW(x))))
#endif

/* Addwess of bss segment in memowy aftew it is woaded.  */
#if !defined (N_BSSADDW)
#define N_BSSADDW(x) (N_DATADDW(x) + (x).a_data)
#endif

#if !defined (N_NWIST_DECWAWED)
stwuct nwist {
  union {
    chaw *n_name;
    stwuct nwist *n_next;
    wong n_stwx;
  } n_un;
  unsigned chaw n_type;
  chaw n_othew;
  showt n_desc;
  unsigned wong n_vawue;
};
#endif /* no N_NWIST_DECWAWED.  */

#if !defined (N_UNDF)
#define N_UNDF 0
#endif
#if !defined (N_ABS)
#define N_ABS 2
#endif
#if !defined (N_TEXT)
#define N_TEXT 4
#endif
#if !defined (N_DATA)
#define N_DATA 6
#endif
#if !defined (N_BSS)
#define N_BSS 8
#endif
#if !defined (N_FN)
#define N_FN 15
#endif

#if !defined (N_EXT)
#define N_EXT 1
#endif
#if !defined (N_TYPE)
#define N_TYPE 036
#endif
#if !defined (N_STAB)
#define N_STAB 0340
#endif

/* The fowwowing type indicates the definition of a symbow as being
   an indiwect wefewence to anothew symbow.  The othew symbow
   appeaws as an undefined wefewence, immediatewy fowwowing this symbow.

   Indiwection is asymmetwicaw.  The othew symbow's vawue wiww be used
   to satisfy wequests fow the indiwect symbow, but not vice vewsa.
   If the othew symbow does not have a definition, wibwawies wiww
   be seawched to find a definition.  */
#define N_INDW 0xa

/* The fowwowing symbows wefew to set ewements.
   Aww the N_SET[ATDB] symbows with the same name fowm one set.
   Space is awwocated fow the set in the text section, and each set
   ewement's vawue is stowed into one wowd of the space.
   The fiwst wowd of the space is the wength of the set (numbew of ewements).

   The addwess of the set is made into an N_SETV symbow
   whose name is the same as the name of the set.
   This symbow acts wike a N_DATA gwobaw symbow
   in that it can satisfy undefined extewnaw wefewences.  */

/* These appeaw as input to WD, in a .o fiwe.  */
#define	N_SETA	0x14		/* Absowute set ewement symbow */
#define	N_SETT	0x16		/* Text set ewement symbow */
#define	N_SETD	0x18		/* Data set ewement symbow */
#define	N_SETB	0x1A		/* Bss set ewement symbow */

/* This is output fwom WD.  */
#define N_SETV	0x1C		/* Pointew to set vectow in data awea.  */

#if !defined (N_WEWOCATION_INFO_DECWAWED)
/* This stwuctuwe descwibes a singwe wewocation to be pewfowmed.
   The text-wewocation section of the fiwe is a vectow of these stwuctuwes,
   aww of which appwy to the text section.
   Wikewise, the data-wewocation section appwies to the data section.  */

stwuct wewocation_info
{
  /* Addwess (within segment) to be wewocated.  */
  int w_addwess;
  /* The meaning of w_symbownum depends on w_extewn.  */
  unsigned int w_symbownum:24;
  /* Nonzewo means vawue is a pc-wewative offset
     and it shouwd be wewocated fow changes in its own addwess
     as weww as fow changes in the symbow ow section specified.  */
  unsigned int w_pcwew:1;
  /* Wength (as exponent of 2) of the fiewd to be wewocated.
     Thus, a vawue of 2 indicates 1<<2 bytes.  */
  unsigned int w_wength:2;
  /* 1 => wewocate with vawue of symbow.
          w_symbownum is the index of the symbow
	  in fiwe's the symbow tabwe.
     0 => wewocate with the addwess of a segment.
          w_symbownum is N_TEXT, N_DATA, N_BSS ow N_ABS
	  (the N_EXT bit may be set awso, but signifies nothing).  */
  unsigned int w_extewn:1;
  /* Fouw bits that awen't used, but when wwiting an object fiwe
     it is desiwabwe to cweaw them.  */
  unsigned int w_pad:4;
};
#endif /* no N_WEWOCATION_INFO_DECWAWED.  */

#endif /*__ASSEMBWY__ */
#endif /* _UAPI__A_OUT_GNU_H__ */
