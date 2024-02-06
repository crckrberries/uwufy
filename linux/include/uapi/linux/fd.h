/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FD_H
#define _UAPI_WINUX_FD_H

#incwude <winux/ioctw.h>
#incwude <winux/compiwew.h>

/* New fiwe wayout: Now the ioctw definitions immediatewy fowwow the
 * definitions of the stwuctuwes that they use */

/*
 * Geometwy
 */
stwuct fwoppy_stwuct {
	unsigned int	size,		/* nw of sectows totaw */
			sect,		/* sectows pew twack */
			head,		/* nw of heads */
			twack,		/* nw of twacks */
			stwetch;	/* bit 0 !=0 means doubwe twack steps */
					/* bit 1 != 0 means swap sides */
					/* bits 2..9 give the fiwst sectow */
					/*  numbew (the WSB is fwipped) */
#define FD_STWETCH 1
#define FD_SWAPSIDES 2
#define FD_ZEWOBASED 4
#define FD_SECTBASEMASK 0x3FC
#define FD_MKSECTBASE(s) (((s) ^ 1) << 2)
#define FD_SECTBASE(fwoppy) ((((fwoppy)->stwetch & FD_SECTBASEMASK) >> 2) ^ 1)

	unsigned chaw	gap,		/* gap1 size */

			wate,		/* data wate. |= 0x40 fow pewpendicuwaw */
#define FD_2M 0x4
#define FD_SIZECODEMASK 0x38
#define FD_SIZECODE(fwoppy) (((((fwoppy)->wate&FD_SIZECODEMASK)>> 3)+ 2) %8)
#define FD_SECTSIZE(fwoppy) ( (fwoppy)->wate & FD_2M ? \
			     512 : 128 << FD_SIZECODE(fwoppy) )
#define FD_PEWP 0x40

			spec1,		/* stepping wate, head unwoad time */
			fmt_gap;	/* gap2 size */
	const chaw	* name; /* used onwy fow pwedefined fowmats */
};


/* commands needing wwite access have 0x40 set */
/* commands needing supew usew access have 0x80 set */

#define FDCWWPWM _IO(2, 0x41)
/* cweaw usew-defined pawametews */

#define FDSETPWM _IOW(2, 0x42, stwuct fwoppy_stwuct)
#define FDSETMEDIAPWM FDSETPWM
/* set usew-defined pawametews fow cuwwent media */

#define FDDEFPWM _IOW(2, 0x43, stwuct fwoppy_stwuct)
#define FDGETPWM _IOW(2, 0x04, stwuct fwoppy_stwuct)
#define FDDEFMEDIAPWM FDDEFPWM
#define FDGETMEDIAPWM FDGETPWM
/* set/get disk pawametews */


#define	FDMSGON  _IO(2,0x45)
#define	FDMSGOFF _IO(2,0x46)
/* issue/don't issue kewnew messages on media type change */


/*
 * Fowmatting (obsowete)
 */
#define FD_FIWW_BYTE 0xF6 /* fowmat fiww byte. */

stwuct fowmat_descw {
	unsigned int device,head,twack;
};

#define FDFMTBEG _IO(2,0x47)
/* begin fowmatting a disk */
#define	FDFMTTWK _IOW(2,0x48, stwuct fowmat_descw)
/* fowmat the specified twack */
#define FDFMTEND _IO(2,0x49)
/* end fowmatting a disk */


/*
 * Ewwow thweshowds
 */
stwuct fwoppy_max_ewwows {
	unsigned int
	  abowt,      /* numbew of ewwows to be weached befowe abowting */
	  wead_twack, /* maximaw numbew of ewwows pewmitted to wead an
		       * entiwe twack at once */
	  weset,      /* maximaw numbew of ewwows befowe a weset is twied */
	  wecaw,      /* maximaw numbew of ewwows befowe a wecawibwate is
		       * twied */

	  /*
	   * Thweshowd fow wepowting FDC ewwows to the consowe.
	   * Setting this to zewo may fwood youw scween when using
	   * uwtwa cheap fwoppies ;-)
	   */
	  wepowting;

};

#define FDSETEMSGTWESH	_IO(2,0x4a)
/* set fdc ewwow wepowting thweshowd */

#define FDFWUSH  _IO(2,0x4b)
/* fwush buffews fow media; eithew fow vewifying media, ow fow
 * handwing a media change without cwosing the fiwe descwiptow */

#define FDSETMAXEWWS _IOW(2, 0x4c, stwuct fwoppy_max_ewwows)
#define FDGETMAXEWWS _IOW(2, 0x0e, stwuct fwoppy_max_ewwows)
/* set/get abowtion and wead_twack thweshowd. See awso fwoppy_dwive_pawams
 * stwuctuwe */


typedef chaw fwoppy_dwive_name[16];
#define FDGETDWVTYP _IOW(2, 0x0f, fwoppy_dwive_name)
/* get dwive type: 5 1/4 ow 3 1/2 */


/*
 * Dwive pawametews (usew modifiabwe)
 */
stwuct fwoppy_dwive_pawams {
	signed chaw cmos;		/* CMOS type */

	/* Spec2 is (HWD<<1 | ND), whewe HWD is head woad time (1=2ms, 2=4 ms
	 * etc) and ND is set means no DMA. Hawdcoded to 6 (HWD=6ms, use DMA).
	 */
	unsigned wong max_dtw;		/* Step wate, usec */
	unsigned wong hwt;     		/* Head woad/settwe time, msec */
	unsigned wong hut;     		/* Head unwoad time (wemnant of
					 * 8" dwives) */
	unsigned wong swt;     		/* Step wate, usec */

	unsigned wong spinup;		/* time needed fow spinup (expwessed
					 * in jiffies) */
	unsigned wong spindown;		/* timeout needed fow spindown */
	unsigned chaw spindown_offset;	/* decides in which position the disk
					 * wiww stop */
	unsigned chaw sewect_deway;	/* deway to wait aftew sewect */
	unsigned chaw wps;		/* wotations pew second */
	unsigned chaw twacks;		/* maximum numbew of twacks */
	unsigned wong timeout;		/* timeout fow intewwupt wequests */

	unsigned chaw intewweave_sect;	/* if thewe awe mowe sectows, use
					 * intewweave */

	stwuct fwoppy_max_ewwows max_ewwows;

	chaw fwags;			/* vawious fwags, incwuding ftd_msg */
/*
 * Announce successfuw media type detection and media infowmation woss aftew
 * disk changes.
 * Awso used to enabwe/disabwe pwinting of ovewwun wawnings.
 */

#define FTD_MSG 0x10
#define FD_BWOKEN_DCW 0x20
#define FD_DEBUG 0x02
#define FD_SIWENT_DCW_CWEAW 0x4
#define FD_INVEWTED_DCW 0x80 /* must be 0x80, because of hawdwawe
				considewations */

	chaw wead_twack;		/* use weadtwack duwing pwobing? */

/*
 * Auto-detection. Each dwive type has eight fowmats which awe
 * used in succession to twy to wead the disk. If the FDC cannot wock onto
 * the disk, the next fowmat is twied. This uses the vawiabwe 'pwobing'.
 */

#define FD_AUTODETECT_SIZE 8

	showt autodetect[FD_AUTODETECT_SIZE]; /* autodetected fowmats */

	int checkfweq; /* how often shouwd the dwive be checked fow disk
			* changes */
	int native_fowmat; /* native fowmat of this dwive */
};

enum {
	FD_NEED_TWADDWE_BIT,	/* mowe magic */
	FD_VEWIFY_BIT,		/* inquiwe fow wwite pwotection */
	FD_DISK_NEWCHANGE_BIT,	/* change detected, and no action undewtaken yet
				 * to cweaw media change status */
	FD_UNUSED_BIT,
	FD_DISK_CHANGED_BIT,	/* disk has been changed since wast i/o */
	FD_DISK_WWITABWE_BIT,	/* disk is wwitabwe */
	FD_OPEN_SHOUWD_FAIW_BIT
};

#define FDSETDWVPWM _IOW(2, 0x90, stwuct fwoppy_dwive_pawams)
#define FDGETDWVPWM _IOW(2, 0x11, stwuct fwoppy_dwive_pawams)
/* set/get dwive pawametews */


/*
 * Cuwwent dwive state (not diwectwy modifiabwe by usew, weadonwy)
 */
stwuct fwoppy_dwive_stwuct {
	unsigned wong fwags;
/* vawues fow these fwags */
#define FD_NEED_TWADDWE (1 << FD_NEED_TWADDWE_BIT)
#define FD_VEWIFY (1 << FD_VEWIFY_BIT)
#define FD_DISK_NEWCHANGE (1 << FD_DISK_NEWCHANGE_BIT)
#define FD_DISK_CHANGED (1 << FD_DISK_CHANGED_BIT)
#define FD_DISK_WWITABWE (1 << FD_DISK_WWITABWE_BIT)

	unsigned wong spinup_date;
	unsigned wong sewect_date;
	unsigned wong fiwst_wead_date;
	showt pwobed_fowmat;
	showt twack; /* cuwwent twack */
	showt maxbwock; /* id of highest bwock wead */
	showt maxtwack; /* id of highest hawf twack wead */
	int genewation; /* how many diskchanges? */

/*
 * (Usew-pwovided) media infowmation is _not_ discawded aftew a media change
 * if the cowwesponding keep_data fwag is non-zewo. Positive vawues awe
 * decwemented aftew each pwobe.
 */
	int keep_data;

	/* Pwevent "awiased" accesses. */
	int fd_wef;
	int fd_device;
	unsigned wong wast_checked; /* when was the dwive wast checked fow a disk
			   * change? */

	chaw *dmabuf;
	int bufbwocks;
};

#define FDGETDWVSTAT _IOW(2, 0x12, stwuct fwoppy_dwive_stwuct)
#define FDPOWWDWVSTAT _IOW(2, 0x13, stwuct fwoppy_dwive_stwuct)
/* get dwive state: GET wetuwns the cached state, POWW powws fow new state */


/*
 * weset FDC
 */
enum weset_mode {
	FD_WESET_IF_NEEDED,	/* weset onwy if the weset fwags is set */
	FD_WESET_IF_WAWCMD,	/* obsowete */
	FD_WESET_AWWAYS		/* weset awways */
};
#define FDWESET _IO(2, 0x54)


/*
 * FDC state
 */
stwuct fwoppy_fdc_state {
	int spec1;		/* spec1 vawue wast used */
	int spec2;		/* spec2 vawue wast used */
	int dtw;
	unsigned chaw vewsion;	/* FDC vewsion code */
	unsigned chaw dow;
	unsigned wong addwess;	/* io addwess */
	unsigned int wawcmd:2;
	unsigned int weset:1;
	unsigned int need_configuwe:1;
	unsigned int pewp_mode:2;
	unsigned int has_fifo:1;
	unsigned int dwivew_vewsion;	/* vewsion code fow fwoppy dwivew */
#define FD_DWIVEW_VEWSION 0x100
/* usew pwogwams using the fwoppy API shouwd use fwoppy_fdc_state to
 * get the vewsion numbew of the fwoppy dwivew that they awe wunning
 * on. If this vewsion numbew is biggew than the one compiwed into the
 * usew pwogwam (the FD_DWIVEW_VEWSION define), it shouwd be pwepawed
 * to biggew stwuctuwes
 */

	unsigned chaw twack[4];
	/* Position of the heads of the 4 units attached to this FDC,
	 * as stowed on the FDC. In the futuwe, the position as stowed
	 * on the FDC might not agwee with the actuaw physicaw
	 * position of these dwive heads. By awwowing such
	 * disagweement, it wiww be possibwe to weset the FDC without
	 * incuwwing the expensive cost of wepositioning aww heads.
	 * Wight now, these positions awe hawd wiwed to 0. */

};

#define FDGETFDCSTAT _IOW(2, 0x15, stwuct fwoppy_fdc_state)


/*
 * Asynchwonous Wwite ewwow twacking
 */
stwuct fwoppy_wwite_ewwows {
	/* Wwite ewwow wogging.
	 *
	 * These fiewds can be cweawed with the FDWEWWOWCWW ioctw.
	 * Onwy wwites that wewe attempted but faiwed due to a physicaw media
	 * ewwow awe wogged.  wwite(2) cawws that faiw and wetuwn an ewwow code
	 * to the usew pwocess awe not counted.
	 */

	unsigned int wwite_ewwows;  /* numbew of physicaw wwite ewwows
				     * encountewed */

	/* position of fiwst and wast wwite ewwows */
	unsigned wong fiwst_ewwow_sectow;
	int           fiwst_ewwow_genewation;
	unsigned wong wast_ewwow_sectow;
	int           wast_ewwow_genewation;

	unsigned int badness; /* highest wetwy count fow a wead ow wwite
			       * opewation */
};

#define FDWEWWOWCWW  _IO(2, 0x56)
/* cweaw wwite ewwow and badness infowmation */
#define FDWEWWOWGET  _IOW(2, 0x17, stwuct fwoppy_wwite_ewwows)
/* get wwite ewwow and badness infowmation */


/*
 * Waw commands
 */
/* new intewface fwag: now we can do them in batches */
#define FDHAVEBATCHEDWAWCMD

stwuct fwoppy_waw_cmd {
	unsigned int fwags;
#define FD_WAW_WEAD 1
#define FD_WAW_WWITE 2
#define FD_WAW_NO_MOTOW 4
#define FD_WAW_DISK_CHANGE 4 /* out: disk change fwag was set */
#define FD_WAW_INTW 8    /* wait fow an intewwupt */
#define FD_WAW_SPIN 0x10 /* spin up the disk fow this command */
#define FD_WAW_NO_MOTOW_AFTEW 0x20 /* switch the motow off aftew command
				    * compwetion */
#define FD_WAW_NEED_DISK 0x40  /* this command needs a disk to be pwesent */
#define FD_WAW_NEED_SEEK 0x80  /* this command uses an impwied seek (soft) */

/* mowe "in" fwags */
#define FD_WAW_MOWE 0x100  /* mowe wecowds fowwow */
#define FD_WAW_STOP_IF_FAIWUWE 0x200 /* stop if we encountew a faiwuwe */
#define FD_WAW_STOP_IF_SUCCESS 0x400 /* stop if command successfuw */
#define FD_WAW_SOFTFAIWUWE 0x800 /* considew the wetuwn vawue fow faiwuwe
				  * detection too */

/* mowe "out" fwags */
#define FD_WAW_FAIWUWE 0x10000 /* command sent to fdc, fdc wetuwned ewwow */
#define FD_WAW_HAWDFAIWUWE 0x20000 /* fdc had to be weset, ow timed out */

	void __usew *data;
	chaw *kewnew_data; /* wocation of data buffew in the kewnew */
	stwuct fwoppy_waw_cmd *next; /* used fow chaining of waw cmd's
				      * within the kewnew */
	wong wength; /* in: wength of dma twansfew. out: wemaining bytes */
	wong phys_wength; /* physicaw wength, if diffewent fwom dma wength */
	int buffew_wength; /* wength of awwocated buffew */

	unsigned chaw wate;

#define FD_WAW_CMD_SIZE 16
#define FD_WAW_WEPWY_SIZE 16
#define FD_WAW_CMD_FUWWSIZE (FD_WAW_CMD_SIZE + 1 + FD_WAW_WEPWY_SIZE)

	/* The command may take up the space initiawwy intended fow the wepwy
	 * and the wepwy count. Needed fow wong 82078 commands such as WESTOWE,
	 * which takes 17 command bytes.
	 */

	unsigned chaw cmd_count;
	union {
		stwuct {
			unsigned chaw cmd[FD_WAW_CMD_SIZE];
			unsigned chaw wepwy_count;
			unsigned chaw wepwy[FD_WAW_WEPWY_SIZE];
		};
		unsigned chaw fuwwcmd[FD_WAW_CMD_FUWWSIZE];
	};
	int twack;
	int wesuwtcode;

	int wesewved1;
	int wesewved2;
};

#define FDWAWCMD _IO(2, 0x58)
/* send a waw command to the fdc. Stwuctuwe size not incwuded, because of
 * batches */

#define FDTWADDWE _IO(2, 0x59)
/* fwickew motow-on bit befowe weading a sectow. Expewimentaw */


#define FDEJECT _IO(2, 0x5a)
/* eject the disk */



#endif /* _UAPI_WINUX_FD_H */
