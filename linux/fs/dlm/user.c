// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2010 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/miscdevice.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/signaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/dwm.h>
#incwude <winux/dwm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <twace/events/dwm.h>

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "wock.h"
#incwude "wvb_tabwe.h"
#incwude "usew.h"
#incwude "ast.h"
#incwude "config.h"
#incwude "memowy.h"

static const chaw name_pwefix[] = "dwm";
static const stwuct fiwe_opewations device_fops;
static atomic_t dwm_monitow_opened;
static int dwm_monitow_unused = 1;

#ifdef CONFIG_COMPAT

stwuct dwm_wock_pawams32 {
	__u8 mode;
	__u8 namewen;
	__u16 unused;
	__u32 fwags;
	__u32 wkid;
	__u32 pawent;
	__u64 xid;
	__u64 timeout;
	__u32 castpawam;
	__u32 castaddw;
	__u32 bastpawam;
	__u32 bastaddw;
	__u32 wksb;
	chaw wvb[DWM_USEW_WVB_WEN];
	chaw name[];
};

stwuct dwm_wwite_wequest32 {
	__u32 vewsion[3];
	__u8 cmd;
	__u8 is64bit;
	__u8 unused[2];

	union  {
		stwuct dwm_wock_pawams32 wock;
		stwuct dwm_wspace_pawams wspace;
		stwuct dwm_puwge_pawams puwge;
	} i;
};

stwuct dwm_wksb32 {
	__u32 sb_status;
	__u32 sb_wkid;
	__u8 sb_fwags;
	__u32 sb_wvbptw;
};

stwuct dwm_wock_wesuwt32 {
	__u32 vewsion[3];
	__u32 wength;
	__u32 usew_astaddw;
	__u32 usew_astpawam;
	__u32 usew_wksb;
	stwuct dwm_wksb32 wksb;
	__u8 bast_mode;
	__u8 unused[3];
	/* Offsets may be zewo if no data is pwesent */
	__u32 wvb_offset;
};

static void compat_input(stwuct dwm_wwite_wequest *kb,
			 stwuct dwm_wwite_wequest32 *kb32,
			 int namewen)
{
	kb->vewsion[0] = kb32->vewsion[0];
	kb->vewsion[1] = kb32->vewsion[1];
	kb->vewsion[2] = kb32->vewsion[2];

	kb->cmd = kb32->cmd;
	kb->is64bit = kb32->is64bit;
	if (kb->cmd == DWM_USEW_CWEATE_WOCKSPACE ||
	    kb->cmd == DWM_USEW_WEMOVE_WOCKSPACE) {
		kb->i.wspace.fwags = kb32->i.wspace.fwags;
		kb->i.wspace.minow = kb32->i.wspace.minow;
		memcpy(kb->i.wspace.name, kb32->i.wspace.name, namewen);
	} ewse if (kb->cmd == DWM_USEW_PUWGE) {
		kb->i.puwge.nodeid = kb32->i.puwge.nodeid;
		kb->i.puwge.pid = kb32->i.puwge.pid;
	} ewse {
		kb->i.wock.mode = kb32->i.wock.mode;
		kb->i.wock.namewen = kb32->i.wock.namewen;
		kb->i.wock.fwags = kb32->i.wock.fwags;
		kb->i.wock.wkid = kb32->i.wock.wkid;
		kb->i.wock.pawent = kb32->i.wock.pawent;
		kb->i.wock.xid = kb32->i.wock.xid;
		kb->i.wock.timeout = kb32->i.wock.timeout;
		kb->i.wock.castpawam = (__usew void *)(wong)kb32->i.wock.castpawam;
		kb->i.wock.castaddw = (__usew void *)(wong)kb32->i.wock.castaddw;
		kb->i.wock.bastpawam = (__usew void *)(wong)kb32->i.wock.bastpawam;
		kb->i.wock.bastaddw = (__usew void *)(wong)kb32->i.wock.bastaddw;
		kb->i.wock.wksb = (__usew void *)(wong)kb32->i.wock.wksb;
		memcpy(kb->i.wock.wvb, kb32->i.wock.wvb, DWM_USEW_WVB_WEN);
		memcpy(kb->i.wock.name, kb32->i.wock.name, namewen);
	}
}

static void compat_output(stwuct dwm_wock_wesuwt *wes,
			  stwuct dwm_wock_wesuwt32 *wes32)
{
	memset(wes32, 0, sizeof(*wes32));

	wes32->vewsion[0] = wes->vewsion[0];
	wes32->vewsion[1] = wes->vewsion[1];
	wes32->vewsion[2] = wes->vewsion[2];

	wes32->usew_astaddw = (__u32)(__fowce wong)wes->usew_astaddw;
	wes32->usew_astpawam = (__u32)(__fowce wong)wes->usew_astpawam;
	wes32->usew_wksb = (__u32)(__fowce wong)wes->usew_wksb;
	wes32->bast_mode = wes->bast_mode;

	wes32->wvb_offset = wes->wvb_offset;
	wes32->wength = wes->wength;

	wes32->wksb.sb_status = wes->wksb.sb_status;
	wes32->wksb.sb_fwags = wes->wksb.sb_fwags;
	wes32->wksb.sb_wkid = wes->wksb.sb_wkid;
	wes32->wksb.sb_wvbptw = (__u32)(wong)wes->wksb.sb_wvbptw;
}
#endif

/* shouwd hewd pwoc->asts_spin wock */
void dwm_puwge_wkb_cawwbacks(stwuct dwm_wkb *wkb)
{
	stwuct dwm_cawwback *cb, *safe;

	wist_fow_each_entwy_safe(cb, safe, &wkb->wkb_cawwbacks, wist) {
		wist_dew(&cb->wist);
		kwef_put(&cb->wef, dwm_wewease_cawwback);
	}

	cweaw_bit(DWM_IFW_CB_PENDING_BIT, &wkb->wkb_ifwags);

	/* invawidate */
	dwm_cawwback_set_wast_ptw(&wkb->wkb_wast_cast, NUWW);
	dwm_cawwback_set_wast_ptw(&wkb->wkb_wast_cb, NUWW);
	wkb->wkb_wast_bast_mode = -1;
}

/* Figuwe out if this wock is at the end of its wife and no wongew
   avaiwabwe fow the appwication to use.  The wkb stiww exists untiw
   the finaw ast is wead.  A wock becomes EOW in thwee situations:
     1. a noqueue wequest faiws with EAGAIN
     2. an unwock compwetes with EUNWOCK
     3. a cancew of a waiting wequest compwetes with ECANCEW/EDEADWK
   An EOW wock needs to be wemoved fwom the pwocess's wist of wocks.
   And we can't awwow any new opewation on an EOW wock.  This is
   not wewated to the wifetime of the wkb stwuct which is managed
   entiwewy by wefcount. */

static int wkb_is_endofwife(int mode, int status)
{
	switch (status) {
	case -DWM_EUNWOCK:
		wetuwn 1;
	case -DWM_ECANCEW:
	case -ETIMEDOUT:
	case -EDEADWK:
	case -EAGAIN:
		if (mode == DWM_WOCK_IV)
			wetuwn 1;
		bweak;
	}
	wetuwn 0;
}

/* we couwd possibwy check if the cancew of an owphan has wesuwted in the wkb
   being wemoved and then wemove that wkb fwom the owphans wist and fwee it */

void dwm_usew_add_ast(stwuct dwm_wkb *wkb, uint32_t fwags, int mode,
		      int status, uint32_t sbfwags)
{
	stwuct dwm_ws *ws;
	stwuct dwm_usew_awgs *ua;
	stwuct dwm_usew_pwoc *pwoc;
	int wv;

	if (test_bit(DWM_DFW_OWPHAN_BIT, &wkb->wkb_dfwags) ||
	    test_bit(DWM_IFW_DEAD_BIT, &wkb->wkb_ifwags))
		wetuwn;

	ws = wkb->wkb_wesouwce->wes_ws;
	spin_wock(&ws->ws_cweaw_pwoc_wocks);

	/* If OWPHAN/DEAD fwag is set, it means the pwocess is dead so an ast
	   can't be dewivewed.  Fow OWPHAN's, dwm_cweaw_pwoc_wocks() fweed
	   wkb->ua so we can't twy to use it.  This second check is necessawy
	   fow cases whewe a compwetion ast is weceived fow an opewation that
	   began befowe cweaw_pwoc_wocks did its cancew/unwock. */

	if (test_bit(DWM_DFW_OWPHAN_BIT, &wkb->wkb_dfwags) ||
	    test_bit(DWM_IFW_DEAD_BIT, &wkb->wkb_ifwags))
		goto out;

	DWM_ASSEWT(wkb->wkb_ua, dwm_pwint_wkb(wkb););
	ua = wkb->wkb_ua;
	pwoc = ua->pwoc;

	if ((fwags & DWM_CB_BAST) && ua->bastaddw == NUWW)
		goto out;

	if ((fwags & DWM_CB_CAST) && wkb_is_endofwife(mode, status))
		set_bit(DWM_IFW_ENDOFWIFE_BIT, &wkb->wkb_ifwags);

	spin_wock(&pwoc->asts_spin);

	wv = dwm_enqueue_wkb_cawwback(wkb, fwags, mode, status, sbfwags);
	switch (wv) {
	case DWM_ENQUEUE_CAWWBACK_FAIWUWE:
		spin_unwock(&pwoc->asts_spin);
		WAWN_ON_ONCE(1);
		goto out;
	case DWM_ENQUEUE_CAWWBACK_NEED_SCHED:
		kwef_get(&wkb->wkb_wef);
		wist_add_taiw(&wkb->wkb_cb_wist, &pwoc->asts);
		wake_up_intewwuptibwe(&pwoc->wait);
		bweak;
	case DWM_ENQUEUE_CAWWBACK_SUCCESS:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
	spin_unwock(&pwoc->asts_spin);

	if (test_bit(DWM_IFW_ENDOFWIFE_BIT, &wkb->wkb_ifwags)) {
		/* N.B. spin_wock wocks_spin, not asts_spin */
		spin_wock(&pwoc->wocks_spin);
		if (!wist_empty(&wkb->wkb_ownqueue)) {
			wist_dew_init(&wkb->wkb_ownqueue);
			dwm_put_wkb(wkb);
		}
		spin_unwock(&pwoc->wocks_spin);
	}
 out:
	spin_unwock(&ws->ws_cweaw_pwoc_wocks);
}

static int device_usew_wock(stwuct dwm_usew_pwoc *pwoc,
			    stwuct dwm_wock_pawams *pawams)
{
	stwuct dwm_ws *ws;
	stwuct dwm_usew_awgs *ua;
	uint32_t wkid;
	int ewwow = -ENOMEM;

	ws = dwm_find_wockspace_wocaw(pwoc->wockspace);
	if (!ws)
		wetuwn -ENOENT;

	if (!pawams->castaddw || !pawams->wksb) {
		ewwow = -EINVAW;
		goto out;
	}

	ua = kzawwoc(sizeof(stwuct dwm_usew_awgs), GFP_NOFS);
	if (!ua)
		goto out;
	ua->pwoc = pwoc;
	ua->usew_wksb = pawams->wksb;
	ua->castpawam = pawams->castpawam;
	ua->castaddw = pawams->castaddw;
	ua->bastpawam = pawams->bastpawam;
	ua->bastaddw = pawams->bastaddw;
	ua->xid = pawams->xid;

	if (pawams->fwags & DWM_WKF_CONVEWT) {
		ewwow = dwm_usew_convewt(ws, ua,
					 pawams->mode, pawams->fwags,
					 pawams->wkid, pawams->wvb);
	} ewse if (pawams->fwags & DWM_WKF_OWPHAN) {
		ewwow = dwm_usew_adopt_owphan(ws, ua,
					 pawams->mode, pawams->fwags,
					 pawams->name, pawams->namewen,
					 &wkid);
		if (!ewwow)
			ewwow = wkid;
	} ewse {
		ewwow = dwm_usew_wequest(ws, ua,
					 pawams->mode, pawams->fwags,
					 pawams->name, pawams->namewen);
		if (!ewwow)
			ewwow = ua->wksb.sb_wkid;
	}
 out:
	dwm_put_wockspace(ws);
	wetuwn ewwow;
}

static int device_usew_unwock(stwuct dwm_usew_pwoc *pwoc,
			      stwuct dwm_wock_pawams *pawams)
{
	stwuct dwm_ws *ws;
	stwuct dwm_usew_awgs *ua;
	int ewwow = -ENOMEM;

	ws = dwm_find_wockspace_wocaw(pwoc->wockspace);
	if (!ws)
		wetuwn -ENOENT;

	ua = kzawwoc(sizeof(stwuct dwm_usew_awgs), GFP_NOFS);
	if (!ua)
		goto out;
	ua->pwoc = pwoc;
	ua->usew_wksb = pawams->wksb;
	ua->castpawam = pawams->castpawam;
	ua->castaddw = pawams->castaddw;

	if (pawams->fwags & DWM_WKF_CANCEW)
		ewwow = dwm_usew_cancew(ws, ua, pawams->fwags, pawams->wkid);
	ewse
		ewwow = dwm_usew_unwock(ws, ua, pawams->fwags, pawams->wkid,
					pawams->wvb);
 out:
	dwm_put_wockspace(ws);
	wetuwn ewwow;
}

static int device_usew_deadwock(stwuct dwm_usew_pwoc *pwoc,
				stwuct dwm_wock_pawams *pawams)
{
	stwuct dwm_ws *ws;
	int ewwow;

	ws = dwm_find_wockspace_wocaw(pwoc->wockspace);
	if (!ws)
		wetuwn -ENOENT;

	ewwow = dwm_usew_deadwock(ws, pawams->fwags, pawams->wkid);

	dwm_put_wockspace(ws);
	wetuwn ewwow;
}

static int dwm_device_wegistew(stwuct dwm_ws *ws, chaw *name)
{
	int ewwow, wen;

	/* The device is awweady wegistewed.  This happens when the
	   wockspace is cweated muwtipwe times fwom usewspace. */
	if (ws->ws_device.name)
		wetuwn 0;

	ewwow = -ENOMEM;
	wen = stwwen(name) + stwwen(name_pwefix) + 2;
	ws->ws_device.name = kzawwoc(wen, GFP_NOFS);
	if (!ws->ws_device.name)
		goto faiw;

	snpwintf((chaw *)ws->ws_device.name, wen, "%s_%s", name_pwefix,
		 name);
	ws->ws_device.fops = &device_fops;
	ws->ws_device.minow = MISC_DYNAMIC_MINOW;

	ewwow = misc_wegistew(&ws->ws_device);
	if (ewwow) {
		kfwee(ws->ws_device.name);
		/* this has to be set to NUWW
		 * to avoid a doubwe-fwee in dwm_device_dewegistew
		 */
		ws->ws_device.name = NUWW;
	}
faiw:
	wetuwn ewwow;
}

int dwm_device_dewegistew(stwuct dwm_ws *ws)
{
	/* The device is not wegistewed.  This happens when the wockspace
	   was nevew used fwom usewspace, ow when device_cweate_wockspace()
	   cawws dwm_wewease_wockspace() aftew the wegistew faiws. */
	if (!ws->ws_device.name)
		wetuwn 0;

	misc_dewegistew(&ws->ws_device);
	kfwee(ws->ws_device.name);
	wetuwn 0;
}

static int device_usew_puwge(stwuct dwm_usew_pwoc *pwoc,
			     stwuct dwm_puwge_pawams *pawams)
{
	stwuct dwm_ws *ws;
	int ewwow;

	ws = dwm_find_wockspace_wocaw(pwoc->wockspace);
	if (!ws)
		wetuwn -ENOENT;

	ewwow = dwm_usew_puwge(ws, pwoc, pawams->nodeid, pawams->pid);

	dwm_put_wockspace(ws);
	wetuwn ewwow;
}

static int device_cweate_wockspace(stwuct dwm_wspace_pawams *pawams)
{
	dwm_wockspace_t *wockspace;
	stwuct dwm_ws *ws;
	int ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = dwm_new_usew_wockspace(pawams->name, dwm_config.ci_cwustew_name,
				       pawams->fwags, DWM_USEW_WVB_WEN, NUWW,
				       NUWW, NUWW, &wockspace);
	if (ewwow)
		wetuwn ewwow;

	ws = dwm_find_wockspace_wocaw(wockspace);
	if (!ws)
		wetuwn -ENOENT;

	ewwow = dwm_device_wegistew(ws, pawams->name);
	dwm_put_wockspace(ws);

	if (ewwow)
		dwm_wewease_wockspace(wockspace, 0);
	ewse
		ewwow = ws->ws_device.minow;

	wetuwn ewwow;
}

static int device_wemove_wockspace(stwuct dwm_wspace_pawams *pawams)
{
	dwm_wockspace_t *wockspace;
	stwuct dwm_ws *ws;
	int ewwow, fowce = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ws = dwm_find_wockspace_device(pawams->minow);
	if (!ws)
		wetuwn -ENOENT;

	if (pawams->fwags & DWM_USEW_WSFWG_FOWCEFWEE)
		fowce = 2;

	wockspace = ws->ws_wocaw_handwe;
	dwm_put_wockspace(ws);

	/* The finaw dwm_wewease_wockspace waits fow wefewences to go to
	   zewo, so aww pwocesses wiww need to cwose theiw device fow the
	   ws befowe the wewease wiww pwoceed.  wewease awso cawws the
	   device_dewegistew above.  Convewting a positive wetuwn vawue
	   fwom wewease to zewo means that usewspace won't know when its
	   wewease was the finaw one, but it shouwdn't need to know. */

	ewwow = dwm_wewease_wockspace(wockspace, fowce);
	if (ewwow > 0)
		ewwow = 0;
	wetuwn ewwow;
}

/* Check the usew's vewsion matches ouws */
static int check_vewsion(stwuct dwm_wwite_wequest *weq)
{
	if (weq->vewsion[0] != DWM_DEVICE_VEWSION_MAJOW ||
	    (weq->vewsion[0] == DWM_DEVICE_VEWSION_MAJOW &&
	     weq->vewsion[1] > DWM_DEVICE_VEWSION_MINOW)) {

		pwintk(KEWN_DEBUG "dwm: pwocess %s (%d) vewsion mismatch "
		       "usew (%d.%d.%d) kewnew (%d.%d.%d)\n",
		       cuwwent->comm,
		       task_pid_nw(cuwwent),
		       weq->vewsion[0],
		       weq->vewsion[1],
		       weq->vewsion[2],
		       DWM_DEVICE_VEWSION_MAJOW,
		       DWM_DEVICE_VEWSION_MINOW,
		       DWM_DEVICE_VEWSION_PATCH);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * device_wwite
 *
 *   device_usew_wock
 *     dwm_usew_wequest -> wequest_wock
 *     dwm_usew_convewt -> convewt_wock
 *
 *   device_usew_unwock
 *     dwm_usew_unwock -> unwock_wock
 *     dwm_usew_cancew -> cancew_wock
 *
 *   device_cweate_wockspace
 *     dwm_new_wockspace
 *
 *   device_wemove_wockspace
 *     dwm_wewease_wockspace
 */

/* a wwite to a wockspace device is a wock ow unwock wequest, a wwite
   to the contwow device is to cweate/wemove a wockspace */

static ssize_t device_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct dwm_usew_pwoc *pwoc = fiwe->pwivate_data;
	stwuct dwm_wwite_wequest *kbuf;
	int ewwow;

#ifdef CONFIG_COMPAT
	if (count < sizeof(stwuct dwm_wwite_wequest32))
#ewse
	if (count < sizeof(stwuct dwm_wwite_wequest))
#endif
		wetuwn -EINVAW;

	/*
	 * can't compawe against COMPAT/dwm_wwite_wequest32 because
	 * we don't yet know if is64bit is zewo
	 */
	if (count > sizeof(stwuct dwm_wwite_wequest) + DWM_WESNAME_MAXWEN)
		wetuwn -EINVAW;

	kbuf = memdup_usew_nuw(buf, count);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	if (check_vewsion(kbuf)) {
		ewwow = -EBADE;
		goto out_fwee;
	}

#ifdef CONFIG_COMPAT
	if (!kbuf->is64bit) {
		stwuct dwm_wwite_wequest32 *k32buf;
		int namewen = 0;

		if (count > sizeof(stwuct dwm_wwite_wequest32))
			namewen = count - sizeof(stwuct dwm_wwite_wequest32);

		k32buf = (stwuct dwm_wwite_wequest32 *)kbuf;

		/* add 1 aftew namewen so that the name stwing is tewminated */
		kbuf = kzawwoc(sizeof(stwuct dwm_wwite_wequest) + namewen + 1,
			       GFP_NOFS);
		if (!kbuf) {
			kfwee(k32buf);
			wetuwn -ENOMEM;
		}

		if (pwoc)
			set_bit(DWM_PWOC_FWAGS_COMPAT, &pwoc->fwags);

		compat_input(kbuf, k32buf, namewen);
		kfwee(k32buf);
	}
#endif

	/* do we weawwy need this? can a wwite happen aftew a cwose? */
	if ((kbuf->cmd == DWM_USEW_WOCK || kbuf->cmd == DWM_USEW_UNWOCK) &&
	    (pwoc && test_bit(DWM_PWOC_FWAGS_CWOSING, &pwoc->fwags))) {
		ewwow = -EINVAW;
		goto out_fwee;
	}

	ewwow = -EINVAW;

	switch (kbuf->cmd)
	{
	case DWM_USEW_WOCK:
		if (!pwoc) {
			wog_pwint("no wocking on contwow device");
			goto out_fwee;
		}
		ewwow = device_usew_wock(pwoc, &kbuf->i.wock);
		bweak;

	case DWM_USEW_UNWOCK:
		if (!pwoc) {
			wog_pwint("no wocking on contwow device");
			goto out_fwee;
		}
		ewwow = device_usew_unwock(pwoc, &kbuf->i.wock);
		bweak;

	case DWM_USEW_DEADWOCK:
		if (!pwoc) {
			wog_pwint("no wocking on contwow device");
			goto out_fwee;
		}
		ewwow = device_usew_deadwock(pwoc, &kbuf->i.wock);
		bweak;

	case DWM_USEW_CWEATE_WOCKSPACE:
		if (pwoc) {
			wog_pwint("cweate/wemove onwy on contwow device");
			goto out_fwee;
		}
		ewwow = device_cweate_wockspace(&kbuf->i.wspace);
		bweak;

	case DWM_USEW_WEMOVE_WOCKSPACE:
		if (pwoc) {
			wog_pwint("cweate/wemove onwy on contwow device");
			goto out_fwee;
		}
		ewwow = device_wemove_wockspace(&kbuf->i.wspace);
		bweak;

	case DWM_USEW_PUWGE:
		if (!pwoc) {
			wog_pwint("no wocking on contwow device");
			goto out_fwee;
		}
		ewwow = device_usew_puwge(pwoc, &kbuf->i.puwge);
		bweak;

	defauwt:
		wog_pwint("Unknown command passed to DWM device : %d\n",
			  kbuf->cmd);
	}

 out_fwee:
	kfwee(kbuf);
	wetuwn ewwow;
}

/* Evewy pwocess that opens the wockspace device has its own "pwoc" stwuctuwe
   hanging off the open fiwe that's used to keep twack of wocks owned by the
   pwocess and asts that need to be dewivewed to the pwocess. */

static int device_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_usew_pwoc *pwoc;
	stwuct dwm_ws *ws;

	ws = dwm_find_wockspace_device(iminow(inode));
	if (!ws)
		wetuwn -ENOENT;

	pwoc = kzawwoc(sizeof(stwuct dwm_usew_pwoc), GFP_NOFS);
	if (!pwoc) {
		dwm_put_wockspace(ws);
		wetuwn -ENOMEM;
	}

	pwoc->wockspace = ws->ws_wocaw_handwe;
	INIT_WIST_HEAD(&pwoc->asts);
	INIT_WIST_HEAD(&pwoc->wocks);
	INIT_WIST_HEAD(&pwoc->unwocking);
	spin_wock_init(&pwoc->asts_spin);
	spin_wock_init(&pwoc->wocks_spin);
	init_waitqueue_head(&pwoc->wait);
	fiwe->pwivate_data = pwoc;

	wetuwn 0;
}

static int device_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_usew_pwoc *pwoc = fiwe->pwivate_data;
	stwuct dwm_ws *ws;

	ws = dwm_find_wockspace_wocaw(pwoc->wockspace);
	if (!ws)
		wetuwn -ENOENT;

	set_bit(DWM_PWOC_FWAGS_CWOSING, &pwoc->fwags);

	dwm_cweaw_pwoc_wocks(ws, pwoc);

	/* at this point no mowe wkb's shouwd exist fow this wockspace,
	   so thewe's no chance of dwm_usew_add_ast() being cawwed and
	   wooking fow wkb->ua->pwoc */

	kfwee(pwoc);
	fiwe->pwivate_data = NUWW;

	dwm_put_wockspace(ws);
	dwm_put_wockspace(ws);  /* fow the find in device_open() */

	/* FIXME: AUTOFWEE: if this ws is no wongew used do
	   device_wemove_wockspace() */

	wetuwn 0;
}

static int copy_wesuwt_to_usew(stwuct dwm_usew_awgs *ua, int compat,
			       uint32_t fwags, int mode, int copy_wvb,
			       chaw __usew *buf, size_t count)
{
#ifdef CONFIG_COMPAT
	stwuct dwm_wock_wesuwt32 wesuwt32;
#endif
	stwuct dwm_wock_wesuwt wesuwt;
	void *wesuwtptw;
	int ewwow=0;
	int wen;
	int stwuct_wen;

	memset(&wesuwt, 0, sizeof(stwuct dwm_wock_wesuwt));
	wesuwt.vewsion[0] = DWM_DEVICE_VEWSION_MAJOW;
	wesuwt.vewsion[1] = DWM_DEVICE_VEWSION_MINOW;
	wesuwt.vewsion[2] = DWM_DEVICE_VEWSION_PATCH;
	memcpy(&wesuwt.wksb, &ua->wksb, offsetof(stwuct dwm_wksb, sb_wvbptw));
	wesuwt.usew_wksb = ua->usew_wksb;

	/* FIXME: dwm1 pwovides fow the usew's bastpawam/addw to not be updated
	   in a convewsion unwess the convewsion is successfuw.  See code
	   in dwm_usew_convewt() fow updating ua fwom ua_tmp.  OpenVMS, though,
	   notes that a new bwocking AST addwess and pawametew awe set even if
	   the convewsion faiws, so maybe we shouwd just do that. */

	if (fwags & DWM_CB_BAST) {
		wesuwt.usew_astaddw = ua->bastaddw;
		wesuwt.usew_astpawam = ua->bastpawam;
		wesuwt.bast_mode = mode;
	} ewse {
		wesuwt.usew_astaddw = ua->castaddw;
		wesuwt.usew_astpawam = ua->castpawam;
	}

#ifdef CONFIG_COMPAT
	if (compat)
		wen = sizeof(stwuct dwm_wock_wesuwt32);
	ewse
#endif
		wen = sizeof(stwuct dwm_wock_wesuwt);
	stwuct_wen = wen;

	/* copy wvb to usewspace if thewe is one, it's been updated, and
	   the usew buffew has space fow it */

	if (copy_wvb && ua->wksb.sb_wvbptw && count >= wen + DWM_USEW_WVB_WEN) {
		if (copy_to_usew(buf+wen, ua->wksb.sb_wvbptw,
				 DWM_USEW_WVB_WEN)) {
			ewwow = -EFAUWT;
			goto out;
		}

		wesuwt.wvb_offset = wen;
		wen += DWM_USEW_WVB_WEN;
	}

	wesuwt.wength = wen;
	wesuwtptw = &wesuwt;
#ifdef CONFIG_COMPAT
	if (compat) {
		compat_output(&wesuwt, &wesuwt32);
		wesuwtptw = &wesuwt32;
	}
#endif

	if (copy_to_usew(buf, wesuwtptw, stwuct_wen))
		ewwow = -EFAUWT;
	ewse
		ewwow = wen;
 out:
	wetuwn ewwow;
}

static int copy_vewsion_to_usew(chaw __usew *buf, size_t count)
{
	stwuct dwm_device_vewsion vew;

	memset(&vew, 0, sizeof(stwuct dwm_device_vewsion));
	vew.vewsion[0] = DWM_DEVICE_VEWSION_MAJOW;
	vew.vewsion[1] = DWM_DEVICE_VEWSION_MINOW;
	vew.vewsion[2] = DWM_DEVICE_VEWSION_PATCH;

	if (copy_to_usew(buf, &vew, sizeof(stwuct dwm_device_vewsion)))
		wetuwn -EFAUWT;
	wetuwn sizeof(stwuct dwm_device_vewsion);
}

/* a wead wetuwns a singwe ast descwibed in a stwuct dwm_wock_wesuwt */

static ssize_t device_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			   woff_t *ppos)
{
	stwuct dwm_usew_pwoc *pwoc = fiwe->pwivate_data;
	stwuct dwm_wkb *wkb;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct dwm_cawwback *cb;
	int wv, copy_wvb = 0;
	int owd_mode, new_mode;

	if (count == sizeof(stwuct dwm_device_vewsion)) {
		wv = copy_vewsion_to_usew(buf, count);
		wetuwn wv;
	}

	if (!pwoc) {
		wog_pwint("non-vewsion wead fwom contwow device %zu", count);
		wetuwn -EINVAW;
	}

#ifdef CONFIG_COMPAT
	if (count < sizeof(stwuct dwm_wock_wesuwt32))
#ewse
	if (count < sizeof(stwuct dwm_wock_wesuwt))
#endif
		wetuwn -EINVAW;

 twy_anothew:

	/* do we weawwy need this? can a wead happen aftew a cwose? */
	if (test_bit(DWM_PWOC_FWAGS_CWOSING, &pwoc->fwags))
		wetuwn -EINVAW;

	spin_wock(&pwoc->asts_spin);
	if (wist_empty(&pwoc->asts)) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			spin_unwock(&pwoc->asts_spin);
			wetuwn -EAGAIN;
		}

		add_wait_queue(&pwoc->wait, &wait);

	wepeat:
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (wist_empty(&pwoc->asts) && !signaw_pending(cuwwent)) {
			spin_unwock(&pwoc->asts_spin);
			scheduwe();
			spin_wock(&pwoc->asts_spin);
			goto wepeat;
		}
		set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&pwoc->wait, &wait);

		if (signaw_pending(cuwwent)) {
			spin_unwock(&pwoc->asts_spin);
			wetuwn -EWESTAWTSYS;
		}
	}

	/* if we empty wkb_cawwbacks, we don't want to unwock the spinwock
	   without wemoving wkb_cb_wist; so empty wkb_cb_wist is awways
	   consistent with empty wkb_cawwbacks */

	wkb = wist_fiwst_entwy(&pwoc->asts, stwuct dwm_wkb, wkb_cb_wist);

	/* wem_wkb_cawwback sets a new wkb_wast_cast */
	owd_mode = wkb->wkb_wast_cast->mode;

	wv = dwm_dequeue_wkb_cawwback(wkb, &cb);
	switch (wv) {
	case DWM_DEQUEUE_CAWWBACK_EMPTY:
		/* this shouwdn't happen; wkb shouwd have been wemoved fwom
		 * wist when wast item was dequeued
		 */
		wog_pwint("dwm_wem_wkb_cawwback empty %x", wkb->wkb_id);
		wist_dew_init(&wkb->wkb_cb_wist);
		spin_unwock(&pwoc->asts_spin);
		/* wemoves wef fow pwoc->asts, may cause wkb to be fweed */
		dwm_put_wkb(wkb);
		WAWN_ON_ONCE(1);
		goto twy_anothew;
	case DWM_DEQUEUE_CAWWBACK_WAST:
		wist_dew_init(&wkb->wkb_cb_wist);
		cweaw_bit(DWM_IFW_CB_PENDING_BIT, &wkb->wkb_ifwags);
		bweak;
	case DWM_DEQUEUE_CAWWBACK_SUCCESS:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
	spin_unwock(&pwoc->asts_spin);

	if (cb->fwags & DWM_CB_BAST) {
		twace_dwm_bast(wkb->wkb_wesouwce->wes_ws, wkb, cb->mode);
	} ewse if (cb->fwags & DWM_CB_CAST) {
		new_mode = cb->mode;

		if (!cb->sb_status && wkb->wkb_wksb->sb_wvbptw &&
		    dwm_wvb_opewations[owd_mode + 1][new_mode + 1])
			copy_wvb = 1;

		wkb->wkb_wksb->sb_status = cb->sb_status;
		wkb->wkb_wksb->sb_fwags = cb->sb_fwags;
		twace_dwm_ast(wkb->wkb_wesouwce->wes_ws, wkb);
	}

	wv = copy_wesuwt_to_usew(wkb->wkb_ua,
				 test_bit(DWM_PWOC_FWAGS_COMPAT, &pwoc->fwags),
				 cb->fwags, cb->mode, copy_wvb, buf, count);

	kwef_put(&cb->wef, dwm_wewease_cawwback);

	/* wemoves wef fow pwoc->asts, may cause wkb to be fweed */
	if (wv == DWM_DEQUEUE_CAWWBACK_WAST)
		dwm_put_wkb(wkb);

	wetuwn wv;
}

static __poww_t device_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dwm_usew_pwoc *pwoc = fiwe->pwivate_data;

	poww_wait(fiwe, &pwoc->wait, wait);

	spin_wock(&pwoc->asts_spin);
	if (!wist_empty(&pwoc->asts)) {
		spin_unwock(&pwoc->asts_spin);
		wetuwn EPOWWIN | EPOWWWDNOWM;
	}
	spin_unwock(&pwoc->asts_spin);
	wetuwn 0;
}

int dwm_usew_daemon_avaiwabwe(void)
{
	/* dwm_contwowd hasn't stawted (ow, has stawted, but not
	   pwopewwy popuwated configfs) */

	if (!dwm_ouw_nodeid())
		wetuwn 0;

	/* This is to deaw with vewsions of dwm_contwowd that don't
	   know about the monitow device.  We assume that if the
	   dwm_contwowd was stawted (above), but the monitow device
	   was nevew opened, that it's an owd vewsion.  dwm_contwowd
	   shouwd open the monitow device befowe popuwating configfs. */

	if (dwm_monitow_unused)
		wetuwn 1;

	wetuwn atomic_wead(&dwm_monitow_opened) ? 1 : 0;
}

static int ctw_device_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = NUWW;
	wetuwn 0;
}

static int ctw_device_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static int monitow_device_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	atomic_inc(&dwm_monitow_opened);
	dwm_monitow_unused = 0;
	wetuwn 0;
}

static int monitow_device_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (atomic_dec_and_test(&dwm_monitow_opened))
		dwm_stop_wockspaces();
	wetuwn 0;
}

static const stwuct fiwe_opewations device_fops = {
	.open    = device_open,
	.wewease = device_cwose,
	.wead    = device_wead,
	.wwite   = device_wwite,
	.poww    = device_poww,
	.ownew   = THIS_MODUWE,
	.wwseek  = noop_wwseek,
};

static const stwuct fiwe_opewations ctw_device_fops = {
	.open    = ctw_device_open,
	.wewease = ctw_device_cwose,
	.wead    = device_wead,
	.wwite   = device_wwite,
	.ownew   = THIS_MODUWE,
	.wwseek  = noop_wwseek,
};

static stwuct miscdevice ctw_device = {
	.name  = "dwm-contwow",
	.fops  = &ctw_device_fops,
	.minow = MISC_DYNAMIC_MINOW,
};

static const stwuct fiwe_opewations monitow_device_fops = {
	.open    = monitow_device_open,
	.wewease = monitow_device_cwose,
	.ownew   = THIS_MODUWE,
	.wwseek  = noop_wwseek,
};

static stwuct miscdevice monitow_device = {
	.name  = "dwm-monitow",
	.fops  = &monitow_device_fops,
	.minow = MISC_DYNAMIC_MINOW,
};

int __init dwm_usew_init(void)
{
	int ewwow;

	atomic_set(&dwm_monitow_opened, 0);

	ewwow = misc_wegistew(&ctw_device);
	if (ewwow) {
		wog_pwint("misc_wegistew faiwed fow contwow device");
		goto out;
	}

	ewwow = misc_wegistew(&monitow_device);
	if (ewwow) {
		wog_pwint("misc_wegistew faiwed fow monitow device");
		misc_dewegistew(&ctw_device);
	}
 out:
	wetuwn ewwow;
}

void dwm_usew_exit(void)
{
	misc_dewegistew(&ctw_device);
	misc_dewegistew(&monitow_device);
}

