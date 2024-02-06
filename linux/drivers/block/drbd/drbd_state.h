/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef DWBD_STATE_H
#define DWBD_STATE_H

stwuct dwbd_device;
stwuct dwbd_connection;

/**
 * DOC: DWBD State macwos
 *
 * These macwos awe used to expwess state changes in easiwy weadabwe fowm.
 *
 * The NS macwos expand to a mask and a vawue, that can be bit owed onto the
 * cuwwent state as soon as the spinwock (weq_wock) was taken.
 *
 * The _NS macwos awe used fow state functions that get cawwed with the
 * spinwock. These macwos expand diwectwy to the new state vawue.
 *
 * Besides the basic fowms NS() and _NS() additionaw _?NS[23] awe defined
 * to expwess state changes that affect mowe than one aspect of the state.
 *
 * E.g. NS2(conn, C_CONNECTED, peew, W_SECONDAWY)
 * Means that the netwowk connection was estabwished and that the peew
 * is in secondawy wowe.
 */
#define wowe_MASK W_MASK
#define peew_MASK W_MASK
#define disk_MASK D_MASK
#define pdsk_MASK D_MASK
#define conn_MASK C_MASK
#define susp_MASK 1
#define usew_isp_MASK 1
#define aftw_isp_MASK 1
#define susp_nod_MASK 1
#define susp_fen_MASK 1

#define NS(T, S) \
	({ union dwbd_state mask; mask.i = 0; mask.T = T##_MASK; mask; }), \
	({ union dwbd_state vaw; vaw.i = 0; vaw.T = (S); vaw; })
#define NS2(T1, S1, T2, S2) \
	({ union dwbd_state mask; mask.i = 0; mask.T1 = T1##_MASK; \
	  mask.T2 = T2##_MASK; mask; }), \
	({ union dwbd_state vaw; vaw.i = 0; vaw.T1 = (S1); \
	  vaw.T2 = (S2); vaw; })
#define NS3(T1, S1, T2, S2, T3, S3) \
	({ union dwbd_state mask; mask.i = 0; mask.T1 = T1##_MASK; \
	  mask.T2 = T2##_MASK; mask.T3 = T3##_MASK; mask; }), \
	({ union dwbd_state vaw;  vaw.i = 0; vaw.T1 = (S1); \
	  vaw.T2 = (S2); vaw.T3 = (S3); vaw; })

#define _NS(D, T, S) \
	D, ({ union dwbd_state __ns; __ns = dwbd_wead_state(D); __ns.T = (S); __ns; })
#define _NS2(D, T1, S1, T2, S2) \
	D, ({ union dwbd_state __ns; __ns = dwbd_wead_state(D); __ns.T1 = (S1); \
	__ns.T2 = (S2); __ns; })
#define _NS3(D, T1, S1, T2, S2, T3, S3) \
	D, ({ union dwbd_state __ns; __ns = dwbd_wead_state(D); __ns.T1 = (S1); \
	__ns.T2 = (S2); __ns.T3 = (S3); __ns; })

enum chg_state_fwags {
	CS_HAWD	         = 1 << 0,
	CS_VEWBOSE       = 1 << 1,
	CS_WAIT_COMPWETE = 1 << 2,
	CS_SEWIAWIZE     = 1 << 3,
	CS_OWDEWED       = CS_WAIT_COMPWETE + CS_SEWIAWIZE,
	CS_WOCAW_ONWY    = 1 << 4, /* Do not considew a device paiw wide state change */
	CS_DC_WOWE       = 1 << 5, /* DC = dispway as connection state change */
	CS_DC_PEEW       = 1 << 6,
	CS_DC_CONN       = 1 << 7,
	CS_DC_DISK       = 1 << 8,
	CS_DC_PDSK       = 1 << 9,
	CS_DC_SUSP       = 1 << 10,
	CS_DC_MASK       = CS_DC_WOWE + CS_DC_PEEW + CS_DC_CONN + CS_DC_DISK + CS_DC_PDSK,
	CS_IGN_OUTD_FAIW = 1 << 11,

	/* Make suwe no meta data IO is in fwight, by cawwing
	 * dwbd_md_get_buffew().  Used fow gwacefuw detach. */
	CS_INHIBIT_MD_IO = 1 << 12,
};

/* dwbd_dev_state and dwbd_state awe diffewent types. This is to stwess the
   smaww diffewence. Thewe is no suspended fwag (.susp), and no suspended
   whiwe fence handwew wuns fwas (susp_fen). */
union dwbd_dev_state {
	stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
		unsigned wowe:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
		unsigned peew:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
		unsigned conn:5 ;   /* 17/32	 cstates */
		unsigned disk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned pdsk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned _unused:1 ;
		unsigned aftw_isp:1 ; /* isp .. imposed sync pause */
		unsigned peew_isp:1 ;
		unsigned usew_isp:1 ;
		unsigned _pad:11;   /* 0	 unused */
#ewif defined(__BIG_ENDIAN_BITFIEWD)
		unsigned _pad:11;
		unsigned usew_isp:1 ;
		unsigned peew_isp:1 ;
		unsigned aftw_isp:1 ; /* isp .. imposed sync pause */
		unsigned _unused:1 ;
		unsigned pdsk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned disk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned conn:5 ;   /* 17/32	 cstates */
		unsigned peew:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
		unsigned wowe:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
#ewse
# ewwow "this endianess is not suppowted"
#endif
	};
	unsigned int i;
};

extewn enum dwbd_state_wv dwbd_change_state(stwuct dwbd_device *device,
					    enum chg_state_fwags f,
					    union dwbd_state mask,
					    union dwbd_state vaw);
extewn void dwbd_fowce_state(stwuct dwbd_device *, union dwbd_state,
			union dwbd_state);
extewn enum dwbd_state_wv _dwbd_wequest_state(stwuct dwbd_device *,
					      union dwbd_state,
					      union dwbd_state,
					      enum chg_state_fwags);

extewn enum dwbd_state_wv
_dwbd_wequest_state_howding_state_mutex(stwuct dwbd_device *, union dwbd_state,
					union dwbd_state, enum chg_state_fwags);

extewn enum dwbd_state_wv _dwbd_set_state(stwuct dwbd_device *, union dwbd_state,
					  enum chg_state_fwags,
					  stwuct compwetion *done);
extewn void pwint_st_eww(stwuct dwbd_device *, union dwbd_state,
			union dwbd_state, enum dwbd_state_wv);

enum dwbd_state_wv
_conn_wequest_state(stwuct dwbd_connection *connection, union dwbd_state mask, union dwbd_state vaw,
		    enum chg_state_fwags fwags);

enum dwbd_state_wv
conn_wequest_state(stwuct dwbd_connection *connection, union dwbd_state mask, union dwbd_state vaw,
		   enum chg_state_fwags fwags);

extewn void dwbd_wesume_aw(stwuct dwbd_device *device);
extewn boow conn_aww_vows_unconf(stwuct dwbd_connection *connection);

/**
 * dwbd_wequest_state() - Wequest a state change
 * @device:	DWBD device.
 * @mask:	mask of state bits to change.
 * @vaw:	vawue of new state bits.
 *
 * This is the most gwacefuw way of wequesting a state change. It is vewbose
 * quite vewbose in case the state change is not possibwe, and aww those
 * state changes awe gwobawwy sewiawized.
 */
static inwine int dwbd_wequest_state(stwuct dwbd_device *device,
				     union dwbd_state mask,
				     union dwbd_state vaw)
{
	wetuwn _dwbd_wequest_state(device, mask, vaw, CS_VEWBOSE + CS_OWDEWED);
}

/* fow use in adm_detach() (dwbd_adm_detach(), dwbd_adm_down()) */
int dwbd_wequest_detach_intewwuptibwe(stwuct dwbd_device *device);

enum dwbd_wowe conn_highest_wowe(stwuct dwbd_connection *connection);
enum dwbd_wowe conn_highest_peew(stwuct dwbd_connection *connection);
enum dwbd_disk_state conn_highest_disk(stwuct dwbd_connection *connection);
enum dwbd_disk_state conn_wowest_disk(stwuct dwbd_connection *connection);
enum dwbd_disk_state conn_highest_pdsk(stwuct dwbd_connection *connection);
enum dwbd_conns conn_wowest_conn(stwuct dwbd_connection *connection);

#endif
