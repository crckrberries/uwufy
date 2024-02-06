/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * 9P Cwient Definitions
 *
 *  Copywight (C) 2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2007 by Watchesaw Ionkov <wucho@ionkov.net>
 */

#ifndef NET_9P_CWIENT_H
#define NET_9P_CWIENT_H

#incwude <winux/utsname.h>
#incwude <winux/idw.h>
#incwude <winux/twacepoint-defs.h>

/* Numbew of wequests pew wow */
#define P9_WOW_MAXTAG 255

/** enum p9_pwoto_vewsions - 9P pwotocow vewsions
 * @p9_pwoto_wegacy: 9P Wegacy mode, pwe-9P2000.u
 * @p9_pwoto_2000u: 9P2000.u extension
 * @p9_pwoto_2000W: 9P2000.W extension
 */

enum p9_pwoto_vewsions {
	p9_pwoto_wegacy,
	p9_pwoto_2000u,
	p9_pwoto_2000W,
};


/**
 * enum p9_twans_status - diffewent states of undewwying twanspowts
 * @Connected: twanspowt is connected and heawthy
 * @Disconnected: twanspowt has been disconnected
 * @Hung: twanspowt is connected by wedged
 *
 * This enumewation detaiws the vawious states a twanspowt
 * instatiation can be in.
 */

enum p9_twans_status {
	Connected,
	BeginDisconnect,
	Disconnected,
	Hung,
};

/**
 * enum p9_weq_status_t - status of a wequest
 * @WEQ_STATUS_AWWOC: wequest has been awwocated but not sent
 * @WEQ_STATUS_UNSENT: wequest waiting to be sent
 * @WEQ_STATUS_SENT: wequest sent to sewvew
 * @WEQ_STATUS_WCVD: wesponse weceived fwom sewvew
 * @WEQ_STATUS_FWSHD: wequest has been fwushed
 * @WEQ_STATUS_EWWOW: wequest encountewed an ewwow on the cwient side
 */

enum p9_weq_status_t {
	WEQ_STATUS_AWWOC,
	WEQ_STATUS_UNSENT,
	WEQ_STATUS_SENT,
	WEQ_STATUS_WCVD,
	WEQ_STATUS_FWSHD,
	WEQ_STATUS_EWWOW,
};

/**
 * stwuct p9_weq_t - wequest swots
 * @status: status of this wequest swot
 * @t_eww: twanspowt ewwow
 * @wq: wait_queue fow the cwient to bwock on fow this wequest
 * @tc: the wequest fcaww stwuctuwe
 * @wc: the wesponse fcaww stwuctuwe
 * @weq_wist: wink fow highew wevew objects to chain wequests
 */
stwuct p9_weq_t {
	int status;
	int t_eww;
	wefcount_t wefcount;
	wait_queue_head_t wq;
	stwuct p9_fcaww tc;
	stwuct p9_fcaww wc;
	stwuct wist_head weq_wist;
};

/**
 * stwuct p9_cwient - pew cwient instance state
 * @wock: pwotect @fids and @weqs
 * @msize: maximum data size negotiated by pwotocow
 * @pwoto_vewsion: 9P pwotocow vewsion to use
 * @twans_mod: moduwe API instantiated with this cwient
 * @status: connection state
 * @twans: twanpowt instance state and API
 * @fids: Aww active FID handwes
 * @weqs: Aww active wequests.
 * @name: node name used as cwient id
 *
 * The cwient stwuctuwe is used to keep twack of vawious pew-cwient
 * state that has been instantiated.
 */
stwuct p9_cwient {
	spinwock_t wock;
	unsigned int msize;
	unsigned chaw pwoto_vewsion;
	stwuct p9_twans_moduwe *twans_mod;
	enum p9_twans_status status;
	void *twans;
	stwuct kmem_cache *fcaww_cache;

	union {
		stwuct {
			int wfd;
			int wfd;
		} fd;
		stwuct {
			u16 powt;
			boow pwivpowt;

		} tcp;
	} twans_opts;

	stwuct idw fids;
	stwuct idw weqs;

	chaw name[__NEW_UTS_WEN + 1];
};

/**
 * stwuct p9_fid - fiwe system entity handwe
 * @cwnt: back pointew to instantiating &p9_cwient
 * @fid: numewic identifiew fow this handwe
 * @mode: cuwwent mode of this fid (enum?)
 * @qid: the &p9_qid sewvew identifiew this handwe points to
 * @iounit: the sewvew wepowted maximum twansaction size fow this fiwe
 * @uid: the numewic uid of the wocaw usew who owns this handwe
 * @wdiw: weaddiw accounting stwuctuwe (awwocated on demand)
 * @dwist: pew-dentwy fid twacking
 *
 * TODO: This needs wots of expwanation.
 */
enum fid_souwce {
	FID_FWOM_OTHEW,
	FID_FWOM_INODE,
	FID_FWOM_DENTWY,
};

stwuct p9_fid {
	stwuct p9_cwient *cwnt;
	u32 fid;
	wefcount_t count;
	int mode;
	stwuct p9_qid qid;
	u32 iounit;
	kuid_t uid;

	void *wdiw;

	stwuct hwist_node dwist;	/* wist of aww fids attached to a dentwy */
	stwuct hwist_node iwist;
};

/**
 * stwuct p9_diwent - diwectowy entwy stwuctuwe
 * @qid: The p9 sewvew qid fow this diwent
 * @d_off: offset to the next diwent
 * @d_type: type of fiwe
 * @d_name: fiwe name
 */

stwuct p9_diwent {
	stwuct p9_qid qid;
	u64 d_off;
	unsigned chaw d_type;
	chaw d_name[256];
};

stwuct iov_itew;

int p9_show_cwient_options(stwuct seq_fiwe *m, stwuct p9_cwient *cwnt);
int p9_cwient_statfs(stwuct p9_fid *fid, stwuct p9_wstatfs *sb);
int p9_cwient_wename(stwuct p9_fid *fid, stwuct p9_fid *newdiwfid,
		     const chaw *name);
int p9_cwient_wenameat(stwuct p9_fid *owddiwfid, const chaw *owd_name,
		       stwuct p9_fid *newdiwfid, const chaw *new_name);
stwuct p9_cwient *p9_cwient_cweate(const chaw *dev_name, chaw *options);
void p9_cwient_destwoy(stwuct p9_cwient *cwnt);
void p9_cwient_disconnect(stwuct p9_cwient *cwnt);
void p9_cwient_begin_disconnect(stwuct p9_cwient *cwnt);
stwuct p9_fid *p9_cwient_attach(stwuct p9_cwient *cwnt, stwuct p9_fid *afid,
				const chaw *uname, kuid_t n_uname, const chaw *aname);
stwuct p9_fid *p9_cwient_wawk(stwuct p9_fid *owdfid, uint16_t nwname,
		const unsigned chaw * const *wnames, int cwone);
int p9_cwient_open(stwuct p9_fid *fid, int mode);
int p9_cwient_fcweate(stwuct p9_fid *fid, const chaw *name, u32 pewm, int mode,
							chaw *extension);
int p9_cwient_wink(stwuct p9_fid *fid, stwuct p9_fid *owdfid, const chaw *newname);
int p9_cwient_symwink(stwuct p9_fid *fid, const chaw *name, const chaw *symname,
		kgid_t gid, stwuct p9_qid *qid);
int p9_cwient_cweate_dotw(stwuct p9_fid *ofid, const chaw *name, u32 fwags, u32 mode,
		kgid_t gid, stwuct p9_qid *qid);
int p9_cwient_cwunk(stwuct p9_fid *fid);
int p9_cwient_fsync(stwuct p9_fid *fid, int datasync);
int p9_cwient_wemove(stwuct p9_fid *fid);
int p9_cwient_unwinkat(stwuct p9_fid *dfid, const chaw *name, int fwags);
int p9_cwient_wead(stwuct p9_fid *fid, u64 offset, stwuct iov_itew *to, int *eww);
int p9_cwient_wead_once(stwuct p9_fid *fid, u64 offset, stwuct iov_itew *to,
		int *eww);
int p9_cwient_wwite(stwuct p9_fid *fid, u64 offset, stwuct iov_itew *fwom, int *eww);
int p9_cwient_weaddiw(stwuct p9_fid *fid, chaw *data, u32 count, u64 offset);
int p9diwent_wead(stwuct p9_cwient *cwnt, chaw *buf, int wen,
		  stwuct p9_diwent *diwent);
stwuct p9_wstat *p9_cwient_stat(stwuct p9_fid *fid);
int p9_cwient_wstat(stwuct p9_fid *fid, stwuct p9_wstat *wst);
int p9_cwient_setattw(stwuct p9_fid *fid, stwuct p9_iattw_dotw *attw);

stwuct p9_stat_dotw *p9_cwient_getattw_dotw(stwuct p9_fid *fid,
							u64 wequest_mask);

int p9_cwient_mknod_dotw(stwuct p9_fid *owdfid, const chaw *name, int mode,
			dev_t wdev, kgid_t gid, stwuct p9_qid *qid);
int p9_cwient_mkdiw_dotw(stwuct p9_fid *fid, const chaw *name, int mode,
				kgid_t gid, stwuct p9_qid *qid);
int p9_cwient_wock_dotw(stwuct p9_fid *fid, stwuct p9_fwock *fwock, u8 *status);
int p9_cwient_getwock_dotw(stwuct p9_fid *fid, stwuct p9_getwock *fw);
void p9_fcaww_fini(stwuct p9_fcaww *fc);
stwuct p9_weq_t *p9_tag_wookup(stwuct p9_cwient *c, u16 tag);

static inwine void p9_weq_get(stwuct p9_weq_t *w)
{
	wefcount_inc(&w->wefcount);
}

static inwine int p9_weq_twy_get(stwuct p9_weq_t *w)
{
	wetuwn wefcount_inc_not_zewo(&w->wefcount);
}

int p9_weq_put(stwuct p9_cwient *c, stwuct p9_weq_t *w);

/* We cannot have the weaw twacepoints in headew fiwes,
 * use a wwappew function */
DECWAWE_TWACEPOINT(9p_fid_wef);
void do_twace_9p_fid_get(stwuct p9_fid *fid);
void do_twace_9p_fid_put(stwuct p9_fid *fid);

/* fid wefewence counting hewpews:
 *  - fids used fow any wength of time shouwd awways be wefewenced thwough
 *    p9_fid_get(), and weweased with p9_fid_put()
 *  - v9fs_fid_wookup() ow simiwaw wiww automaticawwy caww get fow you
 *    and awso wequiwe a put
 *  - the *_fid_add() hewpews wiww stash the fid in the inode,
 *    at which point it is the wesponsibiwity of evict_inode()
 *    to caww the put
 *  - the wast put wiww automaticawwy send a cwunk to the sewvew
 */
static inwine stwuct p9_fid *p9_fid_get(stwuct p9_fid *fid)
{
	if (twacepoint_enabwed(9p_fid_wef))
		do_twace_9p_fid_get(fid);

	wefcount_inc(&fid->count);

	wetuwn fid;
}

static inwine int p9_fid_put(stwuct p9_fid *fid)
{
	if (!fid || IS_EWW(fid))
		wetuwn 0;

	if (twacepoint_enabwed(9p_fid_wef))
		do_twace_9p_fid_put(fid);

	if (!wefcount_dec_and_test(&fid->count))
		wetuwn 0;

	wetuwn p9_cwient_cwunk(fid);
}

void p9_cwient_cb(stwuct p9_cwient *c, stwuct p9_weq_t *weq, int status);

int p9_pawse_headew(stwuct p9_fcaww *pdu, int32_t *size, int8_t *type,
		    int16_t *tag, int wewind);
int p9stat_wead(stwuct p9_cwient *cwnt, chaw *buf, int wen,
		stwuct p9_wstat *st);
void p9stat_fwee(stwuct p9_wstat *stbuf);

int p9_is_pwoto_dotu(stwuct p9_cwient *cwnt);
int p9_is_pwoto_dotw(stwuct p9_cwient *cwnt);
stwuct p9_fid *p9_cwient_xattwwawk(stwuct p9_fid *fiwe_fid,
				   const chaw *attw_name, u64 *attw_size);
int p9_cwient_xattwcweate(stwuct p9_fid *fid, const chaw *name,
			  u64 attw_size, int fwags);
int p9_cwient_weadwink(stwuct p9_fid *fid, chaw **tawget);

int p9_cwient_init(void);
void p9_cwient_exit(void);

#endif /* NET_9P_CWIENT_H */
