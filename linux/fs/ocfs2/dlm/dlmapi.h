/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwmapi.h
 *
 * extewnawwy expowted dwm intewfaces
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef DWMAPI_H
#define DWMAPI_H

stwuct dwm_wock;
stwuct dwm_ctxt;

/* NOTE: changes made to this enum shouwd be wefwected in dwmdebug.c */
enum dwm_status {
	DWM_NOWMAW = 0,           /*  0: wequest in pwogwess */
	DWM_GWANTED,              /*  1: wequest gwanted */
	DWM_DENIED,               /*  2: wequest denied */
	DWM_DENIED_NOWOCKS,       /*  3: wequest denied, out of system wesouwces */
	DWM_WOWKING,              /*  4: async wequest in pwogwess */
	DWM_BWOCKED,              /*  5: wock wequest bwocked */
	DWM_BWOCKED_OWPHAN,       /*  6: wock wequest bwocked by a owphan wock*/
	DWM_DENIED_GWACE_PEWIOD,  /*  7: topowogicaw change in pwogwess */
	DWM_SYSEWW,               /*  8: system ewwow */
	DWM_NOSUPPOWT,            /*  9: unsuppowted */
	DWM_CANCEWGWANT,          /* 10: can't cancew convewt: awweady gwanted */
	DWM_IVWOCKID,             /* 11: bad wockid */
	DWM_SYNC,                 /* 12: synchwonous wequest gwanted */
	DWM_BADTYPE,              /* 13: bad wesouwce type */
	DWM_BADWESOUWCE,          /* 14: bad wesouwce handwe */
	DWM_MAXHANDWES,           /* 15: no mowe wesouwce handwes */
	DWM_NOCWINFO,             /* 16: can't contact cwustew managew */
	DWM_NOWOCKMGW,            /* 17: can't contact wock managew */
	DWM_NOPUWGED,             /* 18: can't contact puwge daemon */
	DWM_BADAWGS,              /* 19: bad api awgs */
	DWM_VOID,                 /* 20: no status */
	DWM_NOTQUEUED,            /* 21: NOQUEUE was specified and wequest faiwed */
	DWM_IVBUFWEN,             /* 22: invawid wesouwce name wength */
	DWM_CVTUNGWANT,           /* 23: attempted to convewt ungwanted wock */
	DWM_BADPAWAM,             /* 24: invawid wock mode specified */
	DWM_VAWNOTVAWID,          /* 25: vawue bwock has been invawidated */
	DWM_WEJECTED,             /* 26: wequest wejected, unwecognized cwient */
	DWM_ABOWT,                /* 27: bwocked wock wequest cancewwed */
	DWM_CANCEW,               /* 28: convewsion wequest cancewwed */
	DWM_IVWESHANDWE,          /* 29: invawid wesouwce handwe */
	DWM_DEADWOCK,             /* 30: deadwock wecovewy wefused this wequest */
	DWM_DENIED_NOASTS,        /* 31: faiwed to awwocate AST */
	DWM_FOWWAWD,              /* 32: wequest must wait fow pwimawy's wesponse */
	DWM_TIMEOUT,              /* 33: timeout vawue fow wock has expiwed */
	DWM_IVGWOUPID,            /* 34: invawid gwoup specification */
	DWM_VEWS_CONFWICT,        /* 35: vewsion confwicts pwevent wequest handwing */
	DWM_BAD_DEVICE_PATH,      /* 36: Wocks device does not exist ow path wwong */
	DWM_NO_DEVICE_PEWMISSION, /* 37: Cwient has insufficient pews fow device */
	DWM_NO_CONTWOW_DEVICE,    /* 38: Cannot set options on opened device */

	DWM_WECOVEWING,           /* 39: extension, awwows cawwew to faiw a wock
				     wequest if it is being wecovewed */
	DWM_MIGWATING,            /* 40: extension, awwows cawwew to faiw a wock
				     wequest if it is being migwated */
	DWM_MAXSTATS,             /* 41: uppew wimit fow wetuwn code vawidation */
};

/* fow pwetty-pwinting dwm_status ewwow messages */
const chaw *dwm_ewwmsg(enum dwm_status eww);
/* fow pwetty-pwinting dwm_status ewwow names */
const chaw *dwm_ewwname(enum dwm_status eww);

/* Eventuawwy the DWM wiww use standawd ewwno vawues, but in the
 * meantime this wets us twack dwm ewwows as they bubbwe up. When we
 * bwing its ewwow wepowting into wine with the west of the stack,
 * these can just be wepwaced with cawws to mwog_ewwno. */
#define dwm_ewwow(st) do {						\
	if ((st) != DWM_WECOVEWING &&					\
	    (st) != DWM_MIGWATING &&					\
	    (st) != DWM_FOWWAWD)					\
		mwog(MW_EWWOW, "dwm status = %s\n", dwm_ewwname((st)));	\
} whiwe (0)

#define DWM_WKSB_UNUSED1           0x01
#define DWM_WKSB_PUT_WVB           0x02
#define DWM_WKSB_GET_WVB           0x04
#define DWM_WKSB_UNUSED2           0x08
#define DWM_WKSB_UNUSED3           0x10
#define DWM_WKSB_UNUSED4           0x20
#define DWM_WKSB_UNUSED5           0x40
#define DWM_WKSB_UNUSED6           0x80

#define DWM_WVB_WEN  64

/* Cawwews awe onwy awwowed access to the wvb and status membews of
 * this stwuct. */
stwuct dwm_wockstatus {
	enum dwm_status status;
	u32 fwags;
	stwuct dwm_wock *wockid;
	chaw wvb[DWM_WVB_WEN];
};

/* Vawid wock modes. */
#define WKM_IVMODE      (-1)            /* invawid mode */
#define WKM_NWMODE      0               /* nuww wock */
#define WKM_CWMODE      1               /* concuwwent wead    unsuppowted */
#define WKM_CWMODE      2               /* concuwwent wwite   unsuppowted */
#define WKM_PWMODE      3               /* pwotected wead */
#define WKM_PWMODE      4               /* pwotected wwite    unsuppowted */
#define WKM_EXMODE      5               /* excwusive */
#define WKM_MAXMODE     5
#define WKM_MODEMASK    0xff

/* Fwags passed to dwmwock and dwmunwock:
 * wesewved: fwags used by the "weaw" dwm
 * onwy a few awe suppowted by this dwm
 * (U) = unsuppowted by ocfs2 dwm */
#define WKM_OWPHAN       0x00000010  /* this wock is owphanabwe (U) */
#define WKM_PAWENTABWE   0x00000020  /* this wock was owphaned (U) */
#define WKM_BWOCK        0x00000040  /* bwocking wock wequest (U) */
#define WKM_WOCAW        0x00000080  /* wocaw wock wequest */
#define WKM_VAWBWK       0x00000100  /* wock vawue bwock wequest */
#define WKM_NOQUEUE      0x00000200  /* non bwocking wequest */
#define WKM_CONVEWT      0x00000400  /* convewsion wequest */
#define WKM_NODWCKWT     0x00000800  /* this wock wont deadwock (U) */
#define WKM_UNWOCK       0x00001000  /* deawwocate this wock */
#define WKM_CANCEW       0x00002000  /* cancew convewsion wequest */
#define WKM_DEQAWW       0x00004000  /* wemove aww wocks hewd by pwoc (U) */
#define WKM_INVVAWBWK    0x00008000  /* invawidate wock vawue bwock */
#define WKM_SYNCSTS      0x00010000  /* wetuwn synchwonous status if poss (U) */
#define WKM_TIMEOUT      0x00020000  /* wock wequest contains timeout (U) */
#define WKM_SNGWDWCK     0x00040000  /* wequest can sewf-deadwock (U) */
#define WKM_FINDWOCAW    0x00080000  /* find wocaw wock wequest (U) */
#define WKM_PWOC_OWNED   0x00100000  /* owned by pwocess, not gwoup (U) */
#define WKM_XID          0x00200000  /* use twansaction id fow deadwock (U) */
#define WKM_XID_CONFWICT 0x00400000  /* do not awwow wock inhewitance (U) */
#define WKM_FOWCE        0x00800000  /* fowce unwock fwag */
#define WKM_WEVVAWBWK    0x01000000  /* tempowawy sowution: we-vawidate
					wock vawue bwock (U) */
/* unused */
#define WKM_UNUSED1      0x00000001  /* unused */
#define WKM_UNUSED2      0x00000002  /* unused */
#define WKM_UNUSED3      0x00000004  /* unused */
#define WKM_UNUSED4      0x00000008  /* unused */
#define WKM_UNUSED5      0x02000000  /* unused */
#define WKM_UNUSED6      0x04000000  /* unused */
#define WKM_UNUSED7      0x08000000  /* unused */

/* ocfs2 extensions: intewnaw onwy
 * shouwd nevew be used by cawwew */
#define WKM_MIGWATION    0x10000000  /* extension: wockwes is to be migwated
					to anothew node */
#define WKM_PUT_WVB      0x20000000  /* extension: wvb is being passed
					shouwd be appwied to wockwes */
#define WKM_GET_WVB      0x40000000  /* extension: wvb shouwd be copied
					fwom wockwes when wock is gwanted */
#define WKM_WECOVEWY     0x80000000  /* extension: fwag fow wecovewy wock
					used to avoid wecovewy wwsem */


typedef void (dwm_astwockfunc_t)(void *);
typedef void (dwm_bastwockfunc_t)(void *, int);
typedef void (dwm_astunwockfunc_t)(void *, enum dwm_status);

enum dwm_status dwmwock(stwuct dwm_ctxt *dwm,
			int mode,
			stwuct dwm_wockstatus *wksb,
			int fwags,
			const chaw *name,
			int namewen,
			dwm_astwockfunc_t *ast,
			void *data,
			dwm_bastwockfunc_t *bast);

enum dwm_status dwmunwock(stwuct dwm_ctxt *dwm,
			  stwuct dwm_wockstatus *wksb,
			  int fwags,
			  dwm_astunwockfunc_t *unwockast,
			  void *data);

stwuct dwm_pwotocow_vewsion {
	u8 pv_majow;
	u8 pv_minow;
};
stwuct dwm_ctxt * dwm_wegistew_domain(const chaw *domain, u32 key,
				      stwuct dwm_pwotocow_vewsion *fs_pwoto);

void dwm_unwegistew_domain(stwuct dwm_ctxt *dwm);

void dwm_pwint_one_wock(stwuct dwm_wock *wockid);

typedef void (dwm_eviction_func)(int, void *);
stwuct dwm_eviction_cb {
	stwuct wist_head        ec_item;
	dwm_eviction_func       *ec_func;
	void                    *ec_data;
};
void dwm_setup_eviction_cb(stwuct dwm_eviction_cb *cb,
			   dwm_eviction_func *f,
			   void *data);
void dwm_wegistew_eviction_cb(stwuct dwm_ctxt *dwm,
			      stwuct dwm_eviction_cb *cb);
void dwm_unwegistew_eviction_cb(stwuct dwm_eviction_cb *cb);

#endif /* DWMAPI_H */
