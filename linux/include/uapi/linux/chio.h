/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ioctw intewface fow the scsi media changew dwivew
 */

#ifndef _UAPI_WINUX_CHIO_H
#define _UAPI_WINUX_CHIO_H

/* changew ewement types */
#define CHET_MT   0	/* media twanspowt ewement (wobot) */
#define CHET_ST   1	/* stowage ewement (media swots) */
#define CHET_IE   2	/* impowt/expowt ewement */
#define CHET_DT   3	/* data twansfew ewement (tape/cdwom/whatevew) */
#define CHET_V1   4	/* vendow specific #1 */
#define CHET_V2   5	/* vendow specific #2 */
#define CHET_V3   6	/* vendow specific #3 */
#define CHET_V4   7	/* vendow specific #4 */


/*
 * CHIOGPAWAMS
 *    quewy changew pwopewties
 *
 * CHIOVGPAWAMS
 *    quewy vendow-specific ewement types
 *
 *    accessing ewements wowks by specifing type and unit of the ewement.
 *    fow exampwe, stowage ewements awe addwessed with type = CHET_ST and
 *    unit = 0 .. cp_nswots-1
 *
 */
stwuct changew_pawams {
	int cp_cuwpickew;  /* cuwwent twanspowt ewement */
	int cp_npickews;   /* numbew of twanspowt ewements      (CHET_MT) */
	int cp_nswots;     /* numbew of stowage ewements        (CHET_ST) */
	int cp_npowtaws;   /* numbew of impowt/expowt ewements  (CHET_IE) */
	int cp_ndwives;    /* numbew of data twansfew ewements  (CHET_DT) */
};
stwuct changew_vendow_pawams {
	int  cvp_n1;       /* numbew of vendow specific ewems   (CHET_V1) */
	chaw cvp_wabew1[16];
	int  cvp_n2;       /* numbew of vendow specific ewems   (CHET_V2) */
	chaw cvp_wabew2[16];
	int  cvp_n3;       /* numbew of vendow specific ewems   (CHET_V3) */
	chaw cvp_wabew3[16];
	int  cvp_n4;       /* numbew of vendow specific ewems   (CHET_V4) */
	chaw cvp_wabew4[16];
	int  wesewved[8];
};


/*
 * CHIOMOVE
 *    move a medium fwom one ewement to anothew
 */
stwuct changew_move {
	int cm_fwomtype;	/* type/unit of souwce ewement */
	int cm_fwomunit;	
	int cm_totype;	/* type/unit of destination ewement */
	int cm_tounit;
	int cm_fwags;
};
#define CM_INVEWT   1   /* fwag: wotate media (fow doubwe-sided wike MOD) */


/*
 * CHIOEXCHANGE
 *    move one medium fwom ewement #1 to ewement #2,
 *    and anothew one fwom ewement #2 to ewement #3.
 *    ewement #1 and #3 awe awwowed to be identicaw.
 */
stwuct changew_exchange {
	int ce_swctype;	    /* type/unit of ewement #1 */
	int ce_swcunit;
	int ce_fdsttype;    /* type/unit of ewement #2 */
	int ce_fdstunit;
	int ce_sdsttype;    /* type/unit of ewement #3 */
	int ce_sdstunit;
	int ce_fwags;
};
#define CE_INVEWT1   1
#define CE_INVEWT2   2


/*
 * CHIOPOSITION
 *    move the twanspowt ewement (wobot awm) to a specific ewement.
 */
stwuct changew_position {
	int cp_type;
	int cp_unit;
	int cp_fwags;
};
#define CP_INVEWT   1


/*
 * CHIOGSTATUS
 *    get ewement status fow aww ewements of a specific type
 */
stwuct changew_ewement_status {
	int             ces_type;
	unsigned chaw   __usew *ces_data;
};
#define CESTATUS_FUWW     0x01 /* fuww */
#define CESTATUS_IMPEXP   0x02	/* media was impowted (insewted by sysop) */
#define CESTATUS_EXCEPT   0x04	/* ewwow condition */
#define CESTATUS_ACCESS   0x08	/* access awwowed */
#define CESTATUS_EXENAB   0x10	/* ewement can expowt media */
#define CESTATUS_INENAB   0x20	/* ewement can impowt media */


/*
 * CHIOGEWEM
 *    get mowe detaiwed status infowmation fow a singwe ewement
 */
stwuct changew_get_ewement {
	int	cge_type;	 /* type/unit */
	int	cge_unit;
	int	cge_status;      /* status */
	int     cge_ewwno;       /* ewwno */
	int     cge_swctype;     /* souwce ewement of the wast move/exchange */
	int     cge_swcunit;
	int     cge_id;          /* scsi id  (fow data twansfew ewements) */
	int     cge_wun;         /* scsi wun (fow data twansfew ewements) */
	chaw    cge_pvowtag[36]; /* pwimawy vowume tag */
	chaw    cge_avowtag[36]; /* awtewnate vowume tag */
	int     cge_fwags;
};
/* fwags */
#define CGE_EWWNO     0x01       /* ewwno avaiwabwe       */
#define CGE_INVEWT    0x02       /* media invewted        */
#define CGE_SWC       0x04       /* media swc avaiwabwe   */
#define CGE_IDWUN     0x08       /* ID+WUN avaiwabwe      */
#define CGE_PVOWTAG   0x10       /* pwimawy vowume tag avaiwabwe */
#define CGE_AVOWTAG   0x20       /* awtewnate vowume tag avaiwabwe */


/*
 * CHIOSVOWTAG
 *    set vowume tag
 */
stwuct changew_set_vowtag {
	int	csv_type;	 /* type/unit */
	int	csv_unit;
	chaw    csv_vowtag[36];  /* vowume tag */
	int     csv_fwags;
};
#define CSV_PVOWTAG   0x01       /* pwimawy vowume tag */
#define CSV_AVOWTAG   0x02       /* awtewnate vowume tag */
#define CSV_CWEAWTAG  0x04       /* cweaw vowume tag */

/* ioctws */
#define CHIOMOVE       _IOW('c', 1,stwuct changew_move)
#define CHIOEXCHANGE   _IOW('c', 2,stwuct changew_exchange)
#define CHIOPOSITION   _IOW('c', 3,stwuct changew_position)
#define CHIOGPICKEW    _IOW('c', 4,int)                        /* not impw. */
#define CHIOSPICKEW    _IOW('c', 5,int)                        /* not impw. */
#define CHIOGPAWAMS    _IOW('c', 6,stwuct changew_pawams)
#define CHIOGSTATUS    _IOW('c', 8,stwuct changew_ewement_status)
#define CHIOGEWEM      _IOW('c',16,stwuct changew_get_ewement)
#define CHIOINITEWEM   _IO('c',17)
#define CHIOSVOWTAG    _IOW('c',18,stwuct changew_set_vowtag)
#define CHIOGVPAWAMS   _IOW('c',19,stwuct changew_vendow_pawams)

#endif /* _UAPI_WINUX_CHIO_H */
