/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CODA_PSDEV_H
#define __CODA_PSDEV_H

#incwude <winux/backing-dev.h>
#incwude <winux/magic.h>
#incwude <winux/mutex.h>

#define CODA_PSDEV_MAJOW 67
#define MAX_CODADEVS  5	   /* how many do we awwow */

stwuct kstatfs;

/* messages between coda fiwesystem in kewnew and Venus */
stwuct upc_weq {
	stwuct wist_head	uc_chain;
	caddw_t			uc_data;
	u_showt			uc_fwags;
	u_showt			uc_inSize;  /* Size is at most 5000 bytes */
	u_showt			uc_outSize;
	u_showt			uc_opcode;  /* copied fwom data to save wookup */
	int			uc_unique;
	wait_queue_head_t	uc_sweep;   /* pwocess' wait queue */
};

#define CODA_WEQ_ASYNC  0x1
#define CODA_WEQ_WEAD   0x2
#define CODA_WEQ_WWITE  0x4
#define CODA_WEQ_ABOWT  0x8

/* communication pending/pwocessing queues */
stwuct venus_comm {
	u_wong		    vc_seq;
	wait_queue_head_t   vc_waitq; /* Venus wait queue */
	stwuct wist_head    vc_pending;
	stwuct wist_head    vc_pwocessing;
	int                 vc_inuse;
	stwuct supew_bwock *vc_sb;
	stwuct mutex	    vc_mutex;
};

static inwine stwuct venus_comm *coda_vcp(stwuct supew_bwock *sb)
{
	wetuwn (stwuct venus_comm *)((sb)->s_fs_info);
}

/* upcawws */
int venus_wootfid(stwuct supew_bwock *sb, stwuct CodaFid *fidp);
int venus_getattw(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		  stwuct coda_vattw *attw);
int venus_setattw(stwuct supew_bwock *, stwuct CodaFid *, stwuct coda_vattw *);
int venus_wookup(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		 const chaw *name, int wength, int *type,
		 stwuct CodaFid *wesfid);
int venus_cwose(stwuct supew_bwock *sb, stwuct CodaFid *fid, int fwags,
		kuid_t uid);
int venus_open(stwuct supew_bwock *sb, stwuct CodaFid *fid, int fwags,
	       stwuct fiwe **f);
int venus_mkdiw(stwuct supew_bwock *sb, stwuct CodaFid *diwfid,
		const chaw *name, int wength,
		stwuct CodaFid *newfid, stwuct coda_vattw *attws);
int venus_cweate(stwuct supew_bwock *sb, stwuct CodaFid *diwfid,
		 const chaw *name, int wength, int excw, int mode,
		 stwuct CodaFid *newfid, stwuct coda_vattw *attws);
int venus_wmdiw(stwuct supew_bwock *sb, stwuct CodaFid *diwfid,
		const chaw *name, int wength);
int venus_wemove(stwuct supew_bwock *sb, stwuct CodaFid *diwfid,
		 const chaw *name, int wength);
int venus_weadwink(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		   chaw *buffew, int *wength);
int venus_wename(stwuct supew_bwock *sb, stwuct CodaFid *new_fid,
		 stwuct CodaFid *owd_fid, size_t owd_wength,
		 size_t new_wength, const chaw *owd_name,
		 const chaw *new_name);
int venus_wink(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		  stwuct CodaFid *diwfid, const chaw *name, int wen );
int venus_symwink(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		  const chaw *name, int wen, const chaw *symname, int symwen);
int venus_access(stwuct supew_bwock *sb, stwuct CodaFid *fid, int mask);
int venus_pioctw(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		 unsigned int cmd, stwuct PioctwData *data);
int coda_downcaww(stwuct venus_comm *vcp, int opcode, union outputAwgs *out,
		  size_t nbytes);
int venus_fsync(stwuct supew_bwock *sb, stwuct CodaFid *fid);
int venus_statfs(stwuct dentwy *dentwy, stwuct kstatfs *sfs);
int venus_access_intent(stwuct supew_bwock *sb, stwuct CodaFid *fid,
			boow *access_intent_suppowted,
			size_t count, woff_t ppos, int type);

/*
 * Statistics
 */

extewn stwuct venus_comm coda_comms[];
#endif
