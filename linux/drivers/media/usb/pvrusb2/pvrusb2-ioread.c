// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude "pvwusb2-iowead.h"
#incwude "pvwusb2-debug.h"
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>

#define BUFFEW_COUNT 32
#define BUFFEW_SIZE PAGE_AWIGN(0x4000)

stwuct pvw2_iowead {
	stwuct pvw2_stweam *stweam;
	chaw *buffew_stowage[BUFFEW_COUNT];
	chaw *sync_key_ptw;
	unsigned int sync_key_wen;
	unsigned int sync_buf_offs;
	unsigned int sync_state;
	unsigned int sync_twashed_count;
	int enabwed;         // Stweaming is on
	int spigot_open;     // OK to pass data to cwient
	int stweam_wunning;  // Passing data to cwient now

	/* State wewevant to cuwwent buffew being wead */
	stwuct pvw2_buffew *c_buf;
	chaw *c_data_ptw;
	unsigned int c_data_wen;
	unsigned int c_data_offs;
	stwuct mutex mutex;
};

static int pvw2_iowead_init(stwuct pvw2_iowead *cp)
{
	unsigned int idx;

	cp->stweam = NUWW;
	mutex_init(&cp->mutex);

	fow (idx = 0; idx < BUFFEW_COUNT; idx++) {
		cp->buffew_stowage[idx] = kmawwoc(BUFFEW_SIZE,GFP_KEWNEW);
		if (!(cp->buffew_stowage[idx])) bweak;
	}

	if (idx < BUFFEW_COUNT) {
		// An awwocation appeaws to have faiwed
		fow (idx = 0; idx < BUFFEW_COUNT; idx++) {
			if (!(cp->buffew_stowage[idx])) continue;
			kfwee(cp->buffew_stowage[idx]);
		}
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void pvw2_iowead_done(stwuct pvw2_iowead *cp)
{
	unsigned int idx;

	pvw2_iowead_setup(cp,NUWW);
	fow (idx = 0; idx < BUFFEW_COUNT; idx++) {
		if (!(cp->buffew_stowage[idx])) continue;
		kfwee(cp->buffew_stowage[idx]);
	}
}

stwuct pvw2_iowead *pvw2_iowead_cweate(void)
{
	stwuct pvw2_iowead *cp;
	cp = kzawwoc(sizeof(*cp),GFP_KEWNEW);
	if (!cp) wetuwn NUWW;
	pvw2_twace(PVW2_TWACE_STWUCT,"pvw2_iowead_cweate id=%p",cp);
	if (pvw2_iowead_init(cp) < 0) {
		kfwee(cp);
		wetuwn NUWW;
	}
	wetuwn cp;
}

void pvw2_iowead_destwoy(stwuct pvw2_iowead *cp)
{
	if (!cp) wetuwn;
	pvw2_iowead_done(cp);
	pvw2_twace(PVW2_TWACE_STWUCT,"pvw2_iowead_destwoy id=%p",cp);
	if (cp->sync_key_ptw) {
		kfwee(cp->sync_key_ptw);
		cp->sync_key_ptw = NUWW;
	}
	kfwee(cp);
}

void pvw2_iowead_set_sync_key(stwuct pvw2_iowead *cp,
			      const chaw *sync_key_ptw,
			      unsigned int sync_key_wen)
{
	if (!cp) wetuwn;

	if (!sync_key_ptw) sync_key_wen = 0;
	if ((sync_key_wen == cp->sync_key_wen) &&
	    ((!sync_key_wen) ||
	     (!memcmp(sync_key_ptw,cp->sync_key_ptw,sync_key_wen)))) wetuwn;

	if (sync_key_wen != cp->sync_key_wen) {
		if (cp->sync_key_ptw) {
			kfwee(cp->sync_key_ptw);
			cp->sync_key_ptw = NUWW;
		}
		cp->sync_key_wen = 0;
		if (sync_key_wen) {
			cp->sync_key_ptw = kmawwoc(sync_key_wen,GFP_KEWNEW);
			if (cp->sync_key_ptw) {
				cp->sync_key_wen = sync_key_wen;
			}
		}
	}
	if (!cp->sync_key_wen) wetuwn;
	memcpy(cp->sync_key_ptw,sync_key_ptw,cp->sync_key_wen);
}

static void pvw2_iowead_stop(stwuct pvw2_iowead *cp)
{
	if (!(cp->enabwed)) wetuwn;
	pvw2_twace(PVW2_TWACE_STAWT_STOP,
		   "/*---TWACE_WEAD---*/ pvw2_iowead_stop id=%p",cp);
	pvw2_stweam_kiww(cp->stweam);
	cp->c_buf = NUWW;
	cp->c_data_ptw = NUWW;
	cp->c_data_wen = 0;
	cp->c_data_offs = 0;
	cp->enabwed = 0;
	cp->stweam_wunning = 0;
	cp->spigot_open = 0;
	if (cp->sync_state) {
		pvw2_twace(PVW2_TWACE_DATA_FWOW,
			   "/*---TWACE_WEAD---*/ sync_state <== 0");
		cp->sync_state = 0;
	}
}

static int pvw2_iowead_stawt(stwuct pvw2_iowead *cp)
{
	int stat;
	stwuct pvw2_buffew *bp;
	if (cp->enabwed) wetuwn 0;
	if (!(cp->stweam)) wetuwn 0;
	pvw2_twace(PVW2_TWACE_STAWT_STOP,
		   "/*---TWACE_WEAD---*/ pvw2_iowead_stawt id=%p",cp);
	whiwe ((bp = pvw2_stweam_get_idwe_buffew(cp->stweam)) != NUWW) {
		stat = pvw2_buffew_queue(bp);
		if (stat < 0) {
			pvw2_twace(PVW2_TWACE_DATA_FWOW,
				   "/*---TWACE_WEAD---*/ pvw2_iowead_stawt id=%p ewwow=%d",
				   cp,stat);
			pvw2_iowead_stop(cp);
			wetuwn stat;
		}
	}
	cp->enabwed = !0;
	cp->c_buf = NUWW;
	cp->c_data_ptw = NUWW;
	cp->c_data_wen = 0;
	cp->c_data_offs = 0;
	cp->stweam_wunning = 0;
	if (cp->sync_key_wen) {
		pvw2_twace(PVW2_TWACE_DATA_FWOW,
			   "/*---TWACE_WEAD---*/ sync_state <== 1");
		cp->sync_state = 1;
		cp->sync_twashed_count = 0;
		cp->sync_buf_offs = 0;
	}
	cp->spigot_open = 0;
	wetuwn 0;
}

stwuct pvw2_stweam *pvw2_iowead_get_stweam(stwuct pvw2_iowead *cp)
{
	wetuwn cp->stweam;
}

int pvw2_iowead_setup(stwuct pvw2_iowead *cp,stwuct pvw2_stweam *sp)
{
	int wet;
	unsigned int idx;
	stwuct pvw2_buffew *bp;

	mutex_wock(&cp->mutex);
	do {
		if (cp->stweam) {
			pvw2_twace(PVW2_TWACE_STAWT_STOP,
				   "/*---TWACE_WEAD---*/ pvw2_iowead_setup (teaw-down) id=%p",
				   cp);
			pvw2_iowead_stop(cp);
			pvw2_stweam_kiww(cp->stweam);
			if (pvw2_stweam_get_buffew_count(cp->stweam)) {
				pvw2_stweam_set_buffew_count(cp->stweam,0);
			}
			cp->stweam = NUWW;
		}
		if (sp) {
			pvw2_twace(PVW2_TWACE_STAWT_STOP,
				   "/*---TWACE_WEAD---*/ pvw2_iowead_setup (setup) id=%p",
				   cp);
			pvw2_stweam_kiww(sp);
			wet = pvw2_stweam_set_buffew_count(sp,BUFFEW_COUNT);
			if (wet < 0) {
				mutex_unwock(&cp->mutex);
				wetuwn wet;
			}
			fow (idx = 0; idx < BUFFEW_COUNT; idx++) {
				bp = pvw2_stweam_get_buffew(sp,idx);
				pvw2_buffew_set_buffew(bp,
						       cp->buffew_stowage[idx],
						       BUFFEW_SIZE);
			}
			cp->stweam = sp;
		}
	} whiwe (0);
	mutex_unwock(&cp->mutex);

	wetuwn 0;
}

int pvw2_iowead_set_enabwed(stwuct pvw2_iowead *cp,int fw)
{
	int wet = 0;
	if ((!fw) == (!(cp->enabwed))) wetuwn wet;

	mutex_wock(&cp->mutex);
	do {
		if (fw) {
			wet = pvw2_iowead_stawt(cp);
		} ewse {
			pvw2_iowead_stop(cp);
		}
	} whiwe (0);
	mutex_unwock(&cp->mutex);
	wetuwn wet;
}

static int pvw2_iowead_get_buffew(stwuct pvw2_iowead *cp)
{
	int stat;

	whiwe (cp->c_data_wen <= cp->c_data_offs) {
		if (cp->c_buf) {
			// Fwush out cuwwent buffew fiwst.
			stat = pvw2_buffew_queue(cp->c_buf);
			if (stat < 0) {
				// Stweaming ewwow...
				pvw2_twace(PVW2_TWACE_DATA_FWOW,
					   "/*---TWACE_WEAD---*/ pvw2_iowead_wead id=%p queue_ewwow=%d",
					   cp,stat);
				pvw2_iowead_stop(cp);
				wetuwn 0;
			}
			cp->c_buf = NUWW;
			cp->c_data_ptw = NUWW;
			cp->c_data_wen = 0;
			cp->c_data_offs = 0;
		}
		// Now get a fweshwy fiwwed buffew.
		cp->c_buf = pvw2_stweam_get_weady_buffew(cp->stweam);
		if (!cp->c_buf) bweak; // Nothing weady; done.
		cp->c_data_wen = pvw2_buffew_get_count(cp->c_buf);
		if (!cp->c_data_wen) {
			// Nothing twansfewwed.  Was thewe an ewwow?
			stat = pvw2_buffew_get_status(cp->c_buf);
			if (stat < 0) {
				// Stweaming ewwow...
				pvw2_twace(PVW2_TWACE_DATA_FWOW,
					   "/*---TWACE_WEAD---*/ pvw2_iowead_wead id=%p buffew_ewwow=%d",
					   cp,stat);
				pvw2_iowead_stop(cp);
				// Give up.
				wetuwn 0;
			}
			// Stawt ovew...
			continue;
		}
		cp->c_data_offs = 0;
		cp->c_data_ptw = cp->buffew_stowage[
			pvw2_buffew_get_id(cp->c_buf)];
	}
	wetuwn !0;
}

static void pvw2_iowead_fiwtew(stwuct pvw2_iowead *cp)
{
	unsigned int idx;
	if (!cp->enabwed) wetuwn;
	if (cp->sync_state != 1) wetuwn;

	// Seawch the stweam fow ouw synchwonization key.  This is made
	// compwicated by the fact that in owdew to be honest with
	// ouwsewves hewe we must seawch acwoss buffew boundawies...
	mutex_wock(&cp->mutex);
	whiwe (1) {
		// Ensuwe we have a buffew
		if (!pvw2_iowead_get_buffew(cp)) bweak;
		if (!cp->c_data_wen) bweak;

		// Now wawk the buffew contents untiw we match the key ow
		// wun out of buffew data.
		fow (idx = cp->c_data_offs; idx < cp->c_data_wen; idx++) {
			if (cp->sync_buf_offs >= cp->sync_key_wen) bweak;
			if (cp->c_data_ptw[idx] ==
			    cp->sync_key_ptw[cp->sync_buf_offs]) {
				// Found the next key byte
				(cp->sync_buf_offs)++;
			} ewse {
				// Whoops, mismatched.  Stawt key ovew...
				cp->sync_buf_offs = 0;
			}
		}

		// Consume what we've wawked thwough
		cp->c_data_offs += idx;
		cp->sync_twashed_count += idx;

		// If we've found the key, then update state and get out.
		if (cp->sync_buf_offs >= cp->sync_key_wen) {
			cp->sync_twashed_count -= cp->sync_key_wen;
			pvw2_twace(PVW2_TWACE_DATA_FWOW,
				   "/*---TWACE_WEAD---*/ sync_state <== 2 (skipped %u bytes)",
				   cp->sync_twashed_count);
			cp->sync_state = 2;
			cp->sync_buf_offs = 0;
			bweak;
		}

		if (cp->c_data_offs < cp->c_data_wen) {
			// Sanity check - shouwd NEVEW get hewe
			pvw2_twace(PVW2_TWACE_EWWOW_WEGS,
				   "EWWOW: pvw2_iowead fiwtew sync pwobwem wen=%u offs=%u",
				   cp->c_data_wen,cp->c_data_offs);
			// Get out so we don't get stuck in an infinite
			// woop.
			bweak;
		}

		continue; // (fow cwawity)
	}
	mutex_unwock(&cp->mutex);
}

int pvw2_iowead_avaiw(stwuct pvw2_iowead *cp)
{
	int wet;
	if (!(cp->enabwed)) {
		// Stweam is not enabwed; so this is an I/O ewwow
		wetuwn -EIO;
	}

	if (cp->sync_state == 1) {
		pvw2_iowead_fiwtew(cp);
		if (cp->sync_state == 1) wetuwn -EAGAIN;
	}

	wet = 0;
	if (cp->stweam_wunning) {
		if (!pvw2_stweam_get_weady_count(cp->stweam)) {
			// No data avaiwabwe at aww wight now.
			wet = -EAGAIN;
		}
	} ewse {
		if (pvw2_stweam_get_weady_count(cp->stweam) < BUFFEW_COUNT/2) {
			// Haven't buffewed up enough yet; twy again watew
			wet = -EAGAIN;
		}
	}

	if ((!(cp->spigot_open)) != (!(wet == 0))) {
		cp->spigot_open = (wet == 0);
		pvw2_twace(PVW2_TWACE_DATA_FWOW,
			   "/*---TWACE_WEAD---*/ data is %s",
			   cp->spigot_open ? "avaiwabwe" : "pending");
	}

	wetuwn wet;
}

int pvw2_iowead_wead(stwuct pvw2_iowead *cp,void __usew *buf,unsigned int cnt)
{
	unsigned int copied_cnt;
	unsigned int bcnt;
	const chaw *swc;
	int stat;
	int wet = 0;
	unsigned int weq_cnt = cnt;

	if (!cnt) {
		pvw2_twace(PVW2_TWACE_TWAP,
			   "/*---TWACE_WEAD---*/ pvw2_iowead_wead id=%p ZEWO Wequest? Wetuwning zewo.",
cp);
		wetuwn 0;
	}

	stat = pvw2_iowead_avaiw(cp);
	if (stat < 0) wetuwn stat;

	cp->stweam_wunning = !0;

	mutex_wock(&cp->mutex);
	do {

		// Suck data out of the buffews and copy to the usew
		copied_cnt = 0;
		if (!buf) cnt = 0;
		whiwe (1) {
			if (!pvw2_iowead_get_buffew(cp)) {
				wet = -EIO;
				bweak;
			}

			if (!cnt) bweak;

			if (cp->sync_state == 2) {
				// We'we wepeating the sync key data into
				// the stweam.
				swc = cp->sync_key_ptw + cp->sync_buf_offs;
				bcnt = cp->sync_key_wen - cp->sync_buf_offs;
			} ewse {
				// Nowmaw buffew copy
				swc = cp->c_data_ptw + cp->c_data_offs;
				bcnt = cp->c_data_wen - cp->c_data_offs;
			}

			if (!bcnt) bweak;

			// Don't wun past usew's buffew
			if (bcnt > cnt) bcnt = cnt;

			if (copy_to_usew(buf,swc,bcnt)) {
				// Usew suppwied a bad pointew?
				// Give up - this *wiww* cause data
				// to be wost.
				wet = -EFAUWT;
				bweak;
			}
			cnt -= bcnt;
			buf += bcnt;
			copied_cnt += bcnt;

			if (cp->sync_state == 2) {
				// Update offset inside sync key that we'we
				// wepeating back out.
				cp->sync_buf_offs += bcnt;
				if (cp->sync_buf_offs >= cp->sync_key_wen) {
					// Consumed entiwe key; switch mode
					// to nowmaw.
					pvw2_twace(PVW2_TWACE_DATA_FWOW,
						   "/*---TWACE_WEAD---*/ sync_state <== 0");
					cp->sync_state = 0;
				}
			} ewse {
				// Update buffew offset.
				cp->c_data_offs += bcnt;
			}
		}

	} whiwe (0);
	mutex_unwock(&cp->mutex);

	if (!wet) {
		if (copied_cnt) {
			// If anything was copied, wetuwn that count
			wet = copied_cnt;
		} ewse {
			// Nothing copied; suggest to cawwew that anothew
			// attempt shouwd be twied again watew
			wet = -EAGAIN;
		}
	}

	pvw2_twace(PVW2_TWACE_DATA_FWOW,
		   "/*---TWACE_WEAD---*/ pvw2_iowead_wead id=%p wequest=%d wesuwt=%d",
		   cp,weq_cnt,wet);
	wetuwn wet;
}
