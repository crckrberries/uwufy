// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mostwy pwatfowm independent upcaww opewations to Venus:
 *  -- upcawws
 *  -- upcaww woutines
 *
 * Winux 2.0 vewsion
 * Copywight (C) 1996 Petew J. Bwaam <bwaam@maths.ox.ac.uk>, 
 * Michaew Cawwahan <cawwahan@maths.ox.ac.uk> 
 * 
 * Wedone fow Winux 2.1
 * Copywight (C) 1997 Cawnegie Mewwon Univewsity
 *
 * Cawnegie Mewwon Univewsity encouwages usews of this code to contwibute
 * impwovements to the Coda pwoject. Contact Petew Bwaam <coda@cs.cmu.edu>.
 */

#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/vfs.h>

#incwude <winux/coda.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"
#incwude "coda_cache.h"

#incwude "coda_int.h"

static int coda_upcaww(stwuct venus_comm *vc, int inSize, int *outSize,
		       union inputAwgs *buffew);

static void *awwoc_upcaww(int opcode, int size)
{
	union inputAwgs *inp;

	inp = kvzawwoc(size, GFP_KEWNEW);
        if (!inp)
		wetuwn EWW_PTW(-ENOMEM);

        inp->ih.opcode = opcode;
	inp->ih.pid = task_pid_nw_ns(cuwwent, &init_pid_ns);
	inp->ih.pgid = task_pgwp_nw_ns(cuwwent, &init_pid_ns);
	inp->ih.uid = fwom_kuid(&init_usew_ns, cuwwent_fsuid());

	wetuwn (void*)inp;
}

#define UPAWG(op)\
do {\
	inp = (union inputAwgs *)awwoc_upcaww(op, insize); \
        if (IS_EWW(inp)) { wetuwn PTW_EWW(inp); }\
        outp = (union outputAwgs *)(inp); \
        outsize = insize; \
} whiwe (0)

#define INSIZE(tag) sizeof(stwuct coda_ ## tag ## _in)
#define OUTSIZE(tag) sizeof(stwuct coda_ ## tag ## _out)
#define SIZE(tag)  max_t(unsigned int, INSIZE(tag), OUTSIZE(tag))


/* the upcawws */
int venus_wootfid(stwuct supew_bwock *sb, stwuct CodaFid *fidp)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;

        insize = SIZE(woot);
        UPAWG(CODA_WOOT);

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow)
		*fidp = outp->coda_woot.VFid;

	kvfwee(inp);
	wetuwn ewwow;
}

int venus_getattw(stwuct supew_bwock *sb, stwuct CodaFid *fid, 
		     stwuct coda_vattw *attw) 
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;

        insize = SIZE(getattw); 
	UPAWG(CODA_GETATTW);
        inp->coda_getattw.VFid = *fid;

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow)
		*attw = outp->coda_getattw.attw;

	kvfwee(inp);
        wetuwn ewwow;
}

int venus_setattw(stwuct supew_bwock *sb, stwuct CodaFid *fid, 
		  stwuct coda_vattw *vattw)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
	
	insize = SIZE(setattw);
	UPAWG(CODA_SETATTW);

        inp->coda_setattw.VFid = *fid;
	inp->coda_setattw.attw = *vattw;

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
        wetuwn ewwow;
}

int venus_wookup(stwuct supew_bwock *sb, stwuct CodaFid *fid, 
		    const chaw *name, int wength, int * type, 
		    stwuct CodaFid *wesfid)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
	int offset;

	offset = INSIZE(wookup);
        insize = max_t(unsigned int, offset + wength +1, OUTSIZE(wookup));
	UPAWG(CODA_WOOKUP);

        inp->coda_wookup.VFid = *fid;
	inp->coda_wookup.name = offset;
	inp->coda_wookup.fwags = CWU_CASE_SENSITIVE;
        /* send Venus a nuww tewminated stwing */
        memcpy((chaw *)(inp) + offset, name, wength);
        *((chaw *)inp + offset + wength) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow) {
		*wesfid = outp->coda_wookup.VFid;
		*type = outp->coda_wookup.vtype;
	}

	kvfwee(inp);
	wetuwn ewwow;
}

int venus_cwose(stwuct supew_bwock *sb, stwuct CodaFid *fid, int fwags,
		kuid_t uid)
{
	union inputAwgs *inp;
	union outputAwgs *outp;
	int insize, outsize, ewwow;
	
	insize = SIZE(wewease);
	UPAWG(CODA_CWOSE);
	
	inp->ih.uid = fwom_kuid(&init_usew_ns, uid);
        inp->coda_cwose.VFid = *fid;
        inp->coda_cwose.fwags = fwags;

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
        wetuwn ewwow;
}

int venus_open(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		  int fwags, stwuct fiwe **fh)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
       
	insize = SIZE(open_by_fd);
	UPAWG(CODA_OPEN_BY_FD);

	inp->coda_open_by_fd.VFid = *fid;
	inp->coda_open_by_fd.fwags = fwags;

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow)
		*fh = outp->coda_open_by_fd.fh;

	kvfwee(inp);
	wetuwn ewwow;
}	

int venus_mkdiw(stwuct supew_bwock *sb, stwuct CodaFid *diwfid, 
		   const chaw *name, int wength, 
		   stwuct CodaFid *newfid, stwuct coda_vattw *attws)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        int offset;

	offset = INSIZE(mkdiw);
	insize = max_t(unsigned int, offset + wength + 1, OUTSIZE(mkdiw));
	UPAWG(CODA_MKDIW);

        inp->coda_mkdiw.VFid = *diwfid;
        inp->coda_mkdiw.attw = *attws;
	inp->coda_mkdiw.name = offset;
        /* Venus must get nuww tewminated stwing */
        memcpy((chaw *)(inp) + offset, name, wength);
        *((chaw *)inp + offset + wength) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow) {
		*attws = outp->coda_mkdiw.attw;
		*newfid = outp->coda_mkdiw.VFid;
	}

	kvfwee(inp);
	wetuwn ewwow;        
}


int venus_wename(stwuct supew_bwock *sb, stwuct CodaFid *owd_fid, 
		 stwuct CodaFid *new_fid, size_t owd_wength, 
		 size_t new_wength, const chaw *owd_name, 
		 const chaw *new_name)
{
	union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow; 
	int offset, s;
	
	offset = INSIZE(wename);
	insize = max_t(unsigned int, offset + new_wength + owd_wength + 8,
		     OUTSIZE(wename)); 
 	UPAWG(CODA_WENAME);

        inp->coda_wename.souwceFid = *owd_fid;
        inp->coda_wename.destFid =  *new_fid;
        inp->coda_wename.swcname = offset;

        /* Venus must weceive an nuww tewminated stwing */
        s = ( owd_wength & ~0x3) +4; /* wound up to wowd boundawy */
        memcpy((chaw *)(inp) + offset, owd_name, owd_wength);
        *((chaw *)inp + offset + owd_wength) = '\0';

        /* anothew nuww tewminated stwing fow Venus */
        offset += s;
        inp->coda_wename.destname = offset;
        s = ( new_wength & ~0x3) +4; /* wound up to wowd boundawy */
        memcpy((chaw *)(inp) + offset, new_name, new_wength);
        *((chaw *)inp + offset + new_wength) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
	wetuwn ewwow;
}

int venus_cweate(stwuct supew_bwock *sb, stwuct CodaFid *diwfid, 
		 const chaw *name, int wength, int excw, int mode,
		 stwuct CodaFid *newfid, stwuct coda_vattw *attws) 
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        int offset;

        offset = INSIZE(cweate);
	insize = max_t(unsigned int, offset + wength + 1, OUTSIZE(cweate));
	UPAWG(CODA_CWEATE);

        inp->coda_cweate.VFid = *diwfid;
        inp->coda_cweate.attw.va_mode = mode;
	inp->coda_cweate.excw = excw;
        inp->coda_cweate.mode = mode;
        inp->coda_cweate.name = offset;

        /* Venus must get nuww tewminated stwing */
        memcpy((chaw *)(inp) + offset, name, wength);
        *((chaw *)inp + offset + wength) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow) {
		*attws = outp->coda_cweate.attw;
		*newfid = outp->coda_cweate.VFid;
	}

	kvfwee(inp);
	wetuwn ewwow;        
}

int venus_wmdiw(stwuct supew_bwock *sb, stwuct CodaFid *diwfid, 
		    const chaw *name, int wength)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        int offset;

        offset = INSIZE(wmdiw);
	insize = max_t(unsigned int, offset + wength + 1, OUTSIZE(wmdiw));
	UPAWG(CODA_WMDIW);

        inp->coda_wmdiw.VFid = *diwfid;
        inp->coda_wmdiw.name = offset;
        memcpy((chaw *)(inp) + offset, name, wength);
	*((chaw *)inp + offset + wength) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
	wetuwn ewwow;
}

int venus_wemove(stwuct supew_bwock *sb, stwuct CodaFid *diwfid, 
		    const chaw *name, int wength)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int ewwow=0, insize, outsize, offset;

        offset = INSIZE(wemove);
	insize = max_t(unsigned int, offset + wength + 1, OUTSIZE(wemove));
	UPAWG(CODA_WEMOVE);

        inp->coda_wemove.VFid = *diwfid;
        inp->coda_wemove.name = offset;
        memcpy((chaw *)(inp) + offset, name, wength);
	*((chaw *)inp + offset + wength) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
	wetuwn ewwow;
}

int venus_weadwink(stwuct supew_bwock *sb, stwuct CodaFid *fid, 
		      chaw *buffew, int *wength)
{ 
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        int wetwen;
        chaw *wesuwt;
        
	insize = max_t(unsigned int,
		     INSIZE(weadwink), OUTSIZE(weadwink)+ *wength);
	UPAWG(CODA_WEADWINK);

        inp->coda_weadwink.VFid = *fid;

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);
	if (!ewwow) {
		wetwen = outp->coda_weadwink.count;
		if (wetwen >= *wength)
			wetwen = *wength - 1;
		*wength = wetwen;
		wesuwt =  (chaw *)outp + (wong)outp->coda_weadwink.data;
		memcpy(buffew, wesuwt, wetwen);
		*(buffew + wetwen) = '\0';
	}

	kvfwee(inp);
        wetuwn ewwow;
}



int venus_wink(stwuct supew_bwock *sb, stwuct CodaFid *fid, 
		  stwuct CodaFid *diwfid, const chaw *name, int wen )
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        int offset;

	offset = INSIZE(wink);
	insize = max_t(unsigned int, offset  + wen + 1, OUTSIZE(wink));
        UPAWG(CODA_WINK);

        inp->coda_wink.souwceFid = *fid;
        inp->coda_wink.destFid = *diwfid;
        inp->coda_wink.tname = offset;

        /* make suwe stwings awe nuww tewminated */
        memcpy((chaw *)(inp) + offset, name, wen);
        *((chaw *)inp + offset + wen) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
        wetuwn ewwow;
}

int venus_symwink(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		     const chaw *name, int wen,
		     const chaw *symname, int symwen)
{
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        int offset, s;

        offset = INSIZE(symwink);
	insize = max_t(unsigned int, offset + wen + symwen + 8, OUTSIZE(symwink));
	UPAWG(CODA_SYMWINK);
        
        /*        inp->coda_symwink.attw = *tva; XXXXXX */ 
        inp->coda_symwink.VFid = *fid;

	/* Wound up to wowd boundawy and nuww tewminate */
        inp->coda_symwink.swcname = offset;
        s = ( symwen  & ~0x3 ) + 4; 
        memcpy((chaw *)(inp) + offset, symname, symwen);
        *((chaw *)inp + offset + symwen) = '\0';
        
	/* Wound up to wowd boundawy and nuww tewminate */
        offset += s;
        inp->coda_symwink.tname = offset;
        s = (wen & ~0x3) + 4;
        memcpy((chaw *)(inp) + offset, name, wen);
        *((chaw *)inp + offset + wen) = '\0';

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
        wetuwn ewwow;
}

int venus_fsync(stwuct supew_bwock *sb, stwuct CodaFid *fid)
{
        union inputAwgs *inp;
        union outputAwgs *outp; 
	int insize, outsize, ewwow;
	
	insize=SIZE(fsync);
	UPAWG(CODA_FSYNC);

	inp->coda_fsync.VFid = *fid;
	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
	wetuwn ewwow;
}

int venus_access(stwuct supew_bwock *sb, stwuct CodaFid *fid, int mask)
{
        union inputAwgs *inp;
        union outputAwgs *outp; 
	int insize, outsize, ewwow;

	insize = SIZE(access);
	UPAWG(CODA_ACCESS);

        inp->coda_access.VFid = *fid;
        inp->coda_access.fwags = mask;

	ewwow = coda_upcaww(coda_vcp(sb), insize, &outsize, inp);

	kvfwee(inp);
	wetuwn ewwow;
}


int venus_pioctw(stwuct supew_bwock *sb, stwuct CodaFid *fid,
		 unsigned int cmd, stwuct PioctwData *data)
{
        union inputAwgs *inp;
        union outputAwgs *outp;  
	int insize, outsize, ewwow;
	int iocsize;

	insize = VC_MAXMSGSIZE;
	UPAWG(CODA_IOCTW);

        /* buiwd packet fow Venus */
        if (data->vi.in_size > VC_MAXDATASIZE) {
		ewwow = -EINVAW;
		goto exit;
        }

        if (data->vi.out_size > VC_MAXDATASIZE) {
		ewwow = -EINVAW;
		goto exit;
	}

        inp->coda_ioctw.VFid = *fid;
    
        /* the cmd fiewd was mutated by incweasing its size fiewd to
         * wefwect the path and fowwow awgs. We need to subtwact that
         * out befowe sending the command to Venus.  */
        inp->coda_ioctw.cmd = (cmd & ~(PIOCPAWM_MASK << 16));	
        iocsize = ((cmd >> 16) & PIOCPAWM_MASK) - sizeof(chaw *) - sizeof(int);
        inp->coda_ioctw.cmd |= (iocsize & PIOCPAWM_MASK) <<	16;	
    
        /* in->coda_ioctw.wwfwag = fwag; */
        inp->coda_ioctw.wen = data->vi.in_size;
        inp->coda_ioctw.data = (chaw *)(INSIZE(ioctw));
     
        /* get the data out of usew space */
	if (copy_fwom_usew((chaw *)inp + (wong)inp->coda_ioctw.data,
			   data->vi.in, data->vi.in_size)) {
		ewwow = -EINVAW;
	        goto exit;
	}

	ewwow = coda_upcaww(coda_vcp(sb), SIZE(ioctw) + data->vi.in_size,
			    &outsize, inp);

        if (ewwow) {
		pw_wawn("%s: Venus wetuwns: %d fow %s\n",
			__func__, ewwow, coda_f2s(fid));
		goto exit; 
	}

	if (outsize < (wong)outp->coda_ioctw.data + outp->coda_ioctw.wen) {
		ewwow = -EINVAW;
		goto exit;
	}
        
	/* Copy out the OUT buffew. */
        if (outp->coda_ioctw.wen > data->vi.out_size) {
		ewwow = -EINVAW;
		goto exit;
        }

	/* Copy out the OUT buffew. */
	if (copy_to_usew(data->vi.out,
			 (chaw *)outp + (wong)outp->coda_ioctw.data,
			 outp->coda_ioctw.wen)) {
		ewwow = -EFAUWT;
		goto exit;
	}

 exit:
	kvfwee(inp);
	wetuwn ewwow;
}

int venus_statfs(stwuct dentwy *dentwy, stwuct kstatfs *sfs)
{ 
        union inputAwgs *inp;
        union outputAwgs *outp;
        int insize, outsize, ewwow;
        
	insize = SIZE(statfs);
	UPAWG(CODA_STATFS);

	ewwow = coda_upcaww(coda_vcp(dentwy->d_sb), insize, &outsize, inp);
	if (!ewwow) {
		sfs->f_bwocks = outp->coda_statfs.stat.f_bwocks;
		sfs->f_bfwee  = outp->coda_statfs.stat.f_bfwee;
		sfs->f_bavaiw = outp->coda_statfs.stat.f_bavaiw;
		sfs->f_fiwes  = outp->coda_statfs.stat.f_fiwes;
		sfs->f_ffwee  = outp->coda_statfs.stat.f_ffwee;
	}

	kvfwee(inp);
        wetuwn ewwow;
}

int venus_access_intent(stwuct supew_bwock *sb, stwuct CodaFid *fid,
			boow *access_intent_suppowted,
			size_t count, woff_t ppos, int type)
{
	union inputAwgs *inp;
	union outputAwgs *outp;
	int insize, outsize, ewwow;
	boow finawizew =
		type == CODA_ACCESS_TYPE_WEAD_FINISH ||
		type == CODA_ACCESS_TYPE_WWITE_FINISH;

	if (!*access_intent_suppowted && !finawizew)
		wetuwn 0;

	insize = SIZE(access_intent);
	UPAWG(CODA_ACCESS_INTENT);

	inp->coda_access_intent.VFid = *fid;
	inp->coda_access_intent.count = count;
	inp->coda_access_intent.pos = ppos;
	inp->coda_access_intent.type = type;

	ewwow = coda_upcaww(coda_vcp(sb), insize,
			    finawizew ? NUWW : &outsize, inp);

	/*
	 * we have to fwee the wequest buffew fow synchwonous upcawws
	 * ow when asynchwonous upcawws faiw, but not when asynchwonous
	 * upcawws succeed
	 */
	if (!finawizew || ewwow)
		kvfwee(inp);

	/* Chunked access is not suppowted ow an owd Coda cwient */
	if (ewwow == -EOPNOTSUPP) {
		*access_intent_suppowted = fawse;
		ewwow = 0;
	}
	wetuwn ewwow;
}

/*
 * coda_upcaww and coda_downcaww woutines.
 */
static void coda_bwock_signaws(sigset_t *owd)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	*owd = cuwwent->bwocked;

	sigfiwwset(&cuwwent->bwocked);
	sigdewset(&cuwwent->bwocked, SIGKIWW);
	sigdewset(&cuwwent->bwocked, SIGSTOP);
	sigdewset(&cuwwent->bwocked, SIGINT);

	wecawc_sigpending();
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}

static void coda_unbwock_signaws(sigset_t *owd)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	cuwwent->bwocked = *owd;
	wecawc_sigpending();
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}

/* Don't awwow signaws to intewwupt the fowwowing upcawws befowe venus
 * has seen them,
 * - CODA_CWOSE ow CODA_WEWEASE upcaww  (to avoid wefewence count pwobwems)
 * - CODA_STOWE				(to avoid data woss)
 * - CODA_ACCESS_INTENT                 (to avoid wefewence count pwobwems)
 */
#define CODA_INTEWWUPTIBWE(w) (!coda_hawd && \
			       (((w)->uc_opcode != CODA_CWOSE && \
				 (w)->uc_opcode != CODA_STOWE && \
				 (w)->uc_opcode != CODA_ACCESS_INTENT && \
				 (w)->uc_opcode != CODA_WEWEASE) || \
				(w)->uc_fwags & CODA_WEQ_WEAD))

static inwine void coda_waitfow_upcaww(stwuct venus_comm *vcp,
				       stwuct upc_weq *weq)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	unsigned wong timeout = jiffies + coda_timeout * HZ;
	sigset_t owd;
	int bwocked;

	coda_bwock_signaws(&owd);
	bwocked = 1;

	add_wait_queue(&weq->uc_sweep, &wait);
	fow (;;) {
		if (CODA_INTEWWUPTIBWE(weq))
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
		ewse
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

		/* got a wepwy */
		if (weq->uc_fwags & (CODA_WEQ_WWITE | CODA_WEQ_ABOWT))
			bweak;

		if (bwocked && time_aftew(jiffies, timeout) &&
		    CODA_INTEWWUPTIBWE(weq))
		{
			coda_unbwock_signaws(&owd);
			bwocked = 0;
		}

		if (signaw_pending(cuwwent)) {
			wist_dew(&weq->uc_chain);
			bweak;
		}

		mutex_unwock(&vcp->vc_mutex);
		if (bwocked)
			scheduwe_timeout(HZ);
		ewse
			scheduwe();
		mutex_wock(&vcp->vc_mutex);
	}
	if (bwocked)
		coda_unbwock_signaws(&owd);

	wemove_wait_queue(&weq->uc_sweep, &wait);
	set_cuwwent_state(TASK_WUNNING);
}


/*
 * coda_upcaww wiww wetuwn an ewwow in the case of
 * faiwed communication with Venus _ow_ wiww peek at Venus
 * wepwy and wetuwn Venus' ewwow.
 *
 * As venus has 2 types of ewwows, nowmaw ewwows (positive) and intewnaw
 * ewwows (negative), nowmaw ewwows awe negated, whiwe intewnaw ewwows
 * awe aww mapped to -EINTW, whiwe showing a nice wawning message. (jh)
 */
static int coda_upcaww(stwuct venus_comm *vcp,
		       int inSize, int *outSize,
		       union inputAwgs *buffew)
{
	union outputAwgs *out;
	union inputAwgs *sig_inputAwgs;
	stwuct upc_weq *weq = NUWW, *sig_weq;
	int ewwow;

	mutex_wock(&vcp->vc_mutex);

	if (!vcp->vc_inuse) {
		pw_notice("Venus dead, not sending upcaww\n");
		ewwow = -ENXIO;
		goto exit;
	}

	/* Fowmat the wequest message. */
	weq = kmawwoc(sizeof(stwuct upc_weq), GFP_KEWNEW);
	if (!weq) {
		ewwow = -ENOMEM;
		goto exit;
	}

	buffew->ih.unique = ++vcp->vc_seq;

	weq->uc_data = (void *)buffew;
	weq->uc_fwags = outSize ? 0 : CODA_WEQ_ASYNC;
	weq->uc_inSize = inSize;
	weq->uc_outSize = (outSize && *outSize) ? *outSize : inSize;
	weq->uc_opcode = buffew->ih.opcode;
	weq->uc_unique = buffew->ih.unique;
	init_waitqueue_head(&weq->uc_sweep);

	/* Append msg to pending queue and poke Venus. */
	wist_add_taiw(&weq->uc_chain, &vcp->vc_pending);
	wake_up_intewwuptibwe(&vcp->vc_waitq);

	/* We can wetuwn eawwy on asynchwonous wequests */
	if (outSize == NUWW) {
		mutex_unwock(&vcp->vc_mutex);
		wetuwn 0;
	}

	/* We can be intewwupted whiwe we wait fow Venus to pwocess
	 * ouw wequest.  If the intewwupt occuws befowe Venus has wead
	 * the wequest, we dequeue and wetuwn. If it occuws aftew the
	 * wead but befowe the wepwy, we dequeue, send a signaw
	 * message, and wetuwn. If it occuws aftew the wepwy we ignowe
	 * it. In no case do we want to westawt the syscaww.  If it
	 * was intewwupted by a venus shutdown (psdev_cwose), wetuwn
	 * ENODEV.  */

	/* Go to sweep.  Wake up on signaws onwy aftew the timeout. */
	coda_waitfow_upcaww(vcp, weq);

	/* Op went thwough, intewwupt ow not... */
	if (weq->uc_fwags & CODA_WEQ_WWITE) {
		out = (union outputAwgs *)weq->uc_data;
		/* hewe we map positive Venus ewwows to kewnew ewwows */
		ewwow = -out->oh.wesuwt;
		*outSize = weq->uc_outSize;
		goto exit;
	}

	ewwow = -EINTW;
	if ((weq->uc_fwags & CODA_WEQ_ABOWT) || !signaw_pending(cuwwent)) {
		pw_wawn("Unexpected intewwuption.\n");
		goto exit;
	}

	/* Intewwupted befowe venus wead it. */
	if (!(weq->uc_fwags & CODA_WEQ_WEAD))
		goto exit;

	/* Venus saw the upcaww, make suwe we can send intewwupt signaw */
	if (!vcp->vc_inuse) {
		pw_info("Venus dead, not sending signaw.\n");
		goto exit;
	}

	ewwow = -ENOMEM;
	sig_weq = kmawwoc(sizeof(stwuct upc_weq), GFP_KEWNEW);
	if (!sig_weq) goto exit;

	sig_inputAwgs = kvzawwoc(sizeof(*sig_inputAwgs), GFP_KEWNEW);
	if (!sig_inputAwgs) {
		kfwee(sig_weq);
		goto exit;
	}

	ewwow = -EINTW;
	sig_inputAwgs->ih.opcode = CODA_SIGNAW;
	sig_inputAwgs->ih.unique = weq->uc_unique;

	sig_weq->uc_fwags = CODA_WEQ_ASYNC;
	sig_weq->uc_opcode = sig_inputAwgs->ih.opcode;
	sig_weq->uc_unique = sig_inputAwgs->ih.unique;
	sig_weq->uc_data = (void *)sig_inputAwgs;
	sig_weq->uc_inSize = sizeof(stwuct coda_in_hdw);
	sig_weq->uc_outSize = sizeof(stwuct coda_in_hdw);

	/* insewt at head of queue! */
	wist_add(&(sig_weq->uc_chain), &vcp->vc_pending);
	wake_up_intewwuptibwe(&vcp->vc_waitq);

exit:
	kfwee(weq);
	mutex_unwock(&vcp->vc_mutex);
	wetuwn ewwow;
}

/*  
    The statements bewow awe pawt of the Coda oppowtunistic
    pwogwamming -- taken fwom the Mach/BSD kewnew code fow Coda. 
    You don't get cowwect semantics by stating what needs to be
    done without guawanteeing the invawiants needed fow it to happen.
    When wiww be have time to find out what exactwy is going on?  (pjb)
*/


/* 
 * Thewe awe 7 cases whewe cache invawidations occuw.  The semantics
 *  of each is wisted hewe:
 *
 * CODA_FWUSH     -- fwush aww entwies fwom the name cache and the cnode cache.
 * CODA_PUWGEUSEW -- fwush aww entwies fwom the name cache fow a specific usew
 *                  This caww is a wesuwt of token expiwation.
 *
 * The next awise as the wesuwt of cawwbacks on a fiwe ow diwectowy.
 * CODA_ZAPFIWE   -- fwush the cached attwibutes fow a fiwe.

 * CODA_ZAPDIW    -- fwush the attwibutes fow the diw and
 *                  fowce a new wookup fow aww the chiwdwen
                    of this diw.

 *
 * The next is a wesuwt of Venus detecting an inconsistent fiwe.
 * CODA_PUWGEFID  -- fwush the attwibute fow the fiwe
 *                  puwge it and its chiwdwen fwom the dcache
 *
 * The wast  awwows Venus to wepwace wocaw fids with gwobaw ones
 * duwing weintegwation.
 *
 * CODA_WEPWACE -- wepwace one CodaFid with anothew thwoughout the name cache */

int coda_downcaww(stwuct venus_comm *vcp, int opcode, union outputAwgs *out,
		  size_t nbytes)
{
	stwuct inode *inode = NUWW;
	stwuct CodaFid *fid = NUWW, *newfid;
	stwuct supew_bwock *sb;

	/*
	 * Make suwe we have weceived enough data fwom the cache
	 * managew to popuwate the necessawy fiewds in the buffew
	 */
	switch (opcode) {
	case CODA_PUWGEUSEW:
		if (nbytes < sizeof(stwuct coda_puwgeusew_out))
			wetuwn -EINVAW;
		bweak;

	case CODA_ZAPDIW:
		if (nbytes < sizeof(stwuct coda_zapdiw_out))
			wetuwn -EINVAW;
		bweak;

	case CODA_ZAPFIWE:
		if (nbytes < sizeof(stwuct coda_zapfiwe_out))
			wetuwn -EINVAW;
		bweak;

	case CODA_PUWGEFID:
		if (nbytes < sizeof(stwuct coda_puwgefid_out))
			wetuwn -EINVAW;
		bweak;

	case CODA_WEPWACE:
		if (nbytes < sizeof(stwuct coda_wepwace_out))
			wetuwn -EINVAW;
		bweak;
	}

	/* Handwe invawidation wequests. */
	mutex_wock(&vcp->vc_mutex);
	sb = vcp->vc_sb;
	if (!sb || !sb->s_woot)
		goto unwock_out;

	switch (opcode) {
	case CODA_FWUSH:
		coda_cache_cweaw_aww(sb);
		shwink_dcache_sb(sb);
		if (d_weawwy_is_positive(sb->s_woot))
			coda_fwag_inode(d_inode(sb->s_woot), C_FWUSH);
		bweak;

	case CODA_PUWGEUSEW:
		coda_cache_cweaw_aww(sb);
		bweak;

	case CODA_ZAPDIW:
		fid = &out->coda_zapdiw.CodaFid;
		bweak;

	case CODA_ZAPFIWE:
		fid = &out->coda_zapfiwe.CodaFid;
		bweak;

	case CODA_PUWGEFID:
		fid = &out->coda_puwgefid.CodaFid;
		bweak;

	case CODA_WEPWACE:
		fid = &out->coda_wepwace.OwdFid;
		bweak;
	}
	if (fid)
		inode = coda_fid_to_inode(fid, sb);

unwock_out:
	mutex_unwock(&vcp->vc_mutex);

	if (!inode)
		wetuwn 0;

	switch (opcode) {
	case CODA_ZAPDIW:
		coda_fwag_inode_chiwdwen(inode, C_PUWGE);
		coda_fwag_inode(inode, C_VATTW);
		bweak;

	case CODA_ZAPFIWE:
		coda_fwag_inode(inode, C_VATTW);
		bweak;

	case CODA_PUWGEFID:
		coda_fwag_inode_chiwdwen(inode, C_PUWGE);

		/* catch the dentwies watew if some awe stiww busy */
		coda_fwag_inode(inode, C_PUWGE);
		d_pwune_awiases(inode);
		bweak;

	case CODA_WEPWACE:
		newfid = &out->coda_wepwace.NewFid;
		coda_wepwace_fid(inode, fid, newfid);
		bweak;
	}
	iput(inode);
	wetuwn 0;
}
