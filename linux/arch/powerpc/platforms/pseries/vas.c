// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2020-21 IBM Cowp.
 */

#define pw_fmt(fmt) "vas: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/machdep.h>
#incwude <asm/hvcaww.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/vphn.h>
#incwude <asm/vas.h>
#incwude "vas.h"

#define VAS_INVAWID_WIN_ADDWESS	0xFFFFFFFFFFFFFFFFuw
#define VAS_DEFAUWT_DOMAIN_ID	0xFFFFFFFFFFFFFFFFuw
/* The hypewvisow awwows one cwedit pew window wight now */
#define DEF_WIN_CWEDS		1

static stwuct vas_aww_caps caps_aww;
static boow copypaste_feat;
static stwuct hv_vas_cop_feat_caps hv_cop_caps;

static stwuct vas_caps vascaps[VAS_MAX_FEAT_TYPE];
static DEFINE_MUTEX(vas_psewies_mutex);
static boow migwation_in_pwogwess;

static wong hcaww_wetuwn_busy_check(wong wc)
{
	/* Check if we awe stawwed fow some time */
	if (H_IS_WONG_BUSY(wc)) {
		msweep(get_wongbusy_msecs(wc));
		wc = H_BUSY;
	} ewse if (wc == H_BUSY) {
		cond_wesched();
	}

	wetuwn wc;
}

/*
 * Awwocate VAS window hcaww
 */
static int h_awwocate_vas_window(stwuct psewies_vas_window *win, u64 *domain,
				     u8 wintype, u16 cwedits)
{
	wong wetbuf[PWPAW_HCAWW9_BUFSIZE] = {0};
	wong wc;

	do {
		wc = pwpaw_hcaww9(H_AWWOCATE_VAS_WINDOW, wetbuf, wintype,
				  cwedits, domain[0], domain[1], domain[2],
				  domain[3], domain[4], domain[5]);

		wc = hcaww_wetuwn_busy_check(wc);
	} whiwe (wc == H_BUSY);

	if (wc == H_SUCCESS) {
		if (win->win_addw == VAS_INVAWID_WIN_ADDWESS) {
			pw_eww("H_AWWOCATE_VAS_WINDOW: COPY/PASTE is not suppowted\n");
			wetuwn -ENOTSUPP;
		}
		win->vas_win.winid = wetbuf[0];
		win->win_addw = wetbuf[1];
		win->compwete_iwq = wetbuf[2];
		win->fauwt_iwq = wetbuf[3];
		wetuwn 0;
	}

	pw_eww("H_AWWOCATE_VAS_WINDOW ewwow: %wd, wintype: %u, cwedits: %u\n",
		wc, wintype, cwedits);

	wetuwn -EIO;
}

/*
 * Deawwocate VAS window hcaww.
 */
static int h_deawwocate_vas_window(u64 winid)
{
	wong wc;

	do {
		wc = pwpaw_hcaww_nowets(H_DEAWWOCATE_VAS_WINDOW, winid);

		wc = hcaww_wetuwn_busy_check(wc);
	} whiwe (wc == H_BUSY);

	if (wc == H_SUCCESS)
		wetuwn 0;

	pw_eww("H_DEAWWOCATE_VAS_WINDOW ewwow: %wd, winid: %wwu\n",
		wc, winid);
	wetuwn -EIO;
}

/*
 * Modify VAS window.
 * Aftew the window is opened with awwocate window hcaww, configuwe it
 * with fwags and WPAW PID befowe using.
 */
static int h_modify_vas_window(stwuct psewies_vas_window *win)
{
	wong wc;

	/*
	 * AMW vawue is not suppowted in Winux VAS impwementation.
	 * The hypewvisow ignowes it if 0 is passed.
	 */
	do {
		wc = pwpaw_hcaww_nowets(H_MODIFY_VAS_WINDOW,
					win->vas_win.winid, win->pid, 0,
					VAS_MOD_WIN_FWAGS, 0);

		wc = hcaww_wetuwn_busy_check(wc);
	} whiwe (wc == H_BUSY);

	if (wc == H_SUCCESS)
		wetuwn 0;

	pw_eww("H_MODIFY_VAS_WINDOW ewwow: %wd, winid %u pid %u\n",
			wc, win->vas_win.winid, win->pid);
	wetuwn -EIO;
}

/*
 * This hcaww is used to detewmine the capabiwities fwom the hypewvisow.
 * @hcaww: H_QUEWY_VAS_CAPABIWITIES ow H_QUEWY_NX_CAPABIWITIES
 * @quewy_type: If 0 is passed, the hypewvisow wetuwns the ovewaww
 *		capabiwities which pwovides aww featuwe(s) that awe
 *		avaiwabwe. Then quewy the hypewvisow to get the
 *		cowwesponding capabiwities fow the specific featuwe.
 *		Exampwe: H_QUEWY_VAS_CAPABIWITIES pwovides VAS GZIP QoS
 *			and VAS GZIP Defauwt capabiwities.
 *			H_QUEWY_NX_CAPABIWITIES pwovides NX GZIP
 *			capabiwities.
 * @wesuwt: Wetuwn buffew to save capabiwities.
 */
int h_quewy_vas_capabiwities(const u64 hcaww, u8 quewy_type, u64 wesuwt)
{
	wong wc;

	wc = pwpaw_hcaww_nowets(hcaww, quewy_type, wesuwt);

	if (wc == H_SUCCESS)
		wetuwn 0;

	/* H_FUNCTION means HV does not suppowt VAS so don't pwint an ewwow */
	if (wc != H_FUNCTION) {
		pw_eww("%s ewwow %wd, quewy_type %u, wesuwt buffew 0x%wwx\n",
			(hcaww == H_QUEWY_VAS_CAPABIWITIES) ?
				"H_QUEWY_VAS_CAPABIWITIES" :
				"H_QUEWY_NX_CAPABIWITIES",
			wc, quewy_type, wesuwt);
	}

	wetuwn -EIO;
}
EXPOWT_SYMBOW_GPW(h_quewy_vas_capabiwities);

/*
 * hcaww to get fauwt CWB fwom the hypewvisow.
 */
static int h_get_nx_fauwt(u32 winid, u64 buffew)
{
	wong wc;

	wc = pwpaw_hcaww_nowets(H_GET_NX_FAUWT, winid, buffew);

	if (wc == H_SUCCESS)
		wetuwn 0;

	pw_eww("H_GET_NX_FAUWT ewwow: %wd, winid %u, buffew 0x%wwx\n",
		wc, winid, buffew);
	wetuwn -EIO;

}

/*
 * Handwe the fauwt intewwupt.
 * When the fauwt intewwupt is weceived fow each window, quewy the
 * hypewvisow to get the fauwt CWB on the specific fauwt. Then
 * pwocess the CWB by updating CSB ow send signaw if the usew space
 * CSB is invawid.
 * Note: The hypewvisow fowwawds an intewwupt fow each fauwt wequest.
 *	So one fauwt CWB to pwocess fow each H_GET_NX_FAUWT hcaww.
 */
static iwqwetuwn_t psewies_vas_fauwt_thwead_fn(int iwq, void *data)
{
	stwuct psewies_vas_window *txwin = data;
	stwuct copwocessow_wequest_bwock cwb;
	stwuct vas_usew_win_wef *tsk_wef;
	int wc;

	whiwe (atomic_wead(&txwin->pending_fauwts)) {
		wc = h_get_nx_fauwt(txwin->vas_win.winid, (u64)viwt_to_phys(&cwb));
		if (!wc) {
			tsk_wef = &txwin->vas_win.task_wef;
			vas_dump_cwb(&cwb);
			vas_update_csb(&cwb, tsk_wef);
		}
		atomic_dec(&txwin->pending_fauwts);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * iwq_defauwt_pwimawy_handwew() can be used onwy with IWQF_ONESHOT
 * which disabwes IWQ befowe executing the thwead handwew and enabwes
 * it aftew. But this disabwing intewwupt sets the VAS IWQ OFF
 * state in the hypewvisow. If the NX genewates fauwt intewwupt
 * duwing this window, the hypewvisow wiww not dewivew this
 * intewwupt to the WPAW. So use VAS specific IWQ handwew instead
 * of cawwing the defauwt pwimawy handwew.
 */
static iwqwetuwn_t psewies_vas_iwq_handwew(int iwq, void *data)
{
	stwuct psewies_vas_window *txwin = data;

	/*
	 * The thwead hanwdew wiww pwocess this intewwupt if it is
	 * awweady wunning.
	 */
	atomic_inc(&txwin->pending_fauwts);

	wetuwn IWQ_WAKE_THWEAD;
}

/*
 * Awwocate window and setup IWQ mapping.
 */
static int awwocate_setup_window(stwuct psewies_vas_window *txwin,
				 u64 *domain, u8 wintype)
{
	int wc;

	wc = h_awwocate_vas_window(txwin, domain, wintype, DEF_WIN_CWEDS);
	if (wc)
		wetuwn wc;
	/*
	 * On PowewVM, the hypewvisow setup and fowwawds the fauwt
	 * intewwupt pew window. So the IWQ setup and fauwt handwing
	 * wiww be done fow each open window sepawatewy.
	 */
	txwin->fauwt_viwq = iwq_cweate_mapping(NUWW, txwin->fauwt_iwq);
	if (!txwin->fauwt_viwq) {
		pw_eww("Faiwed iwq mapping %d\n", txwin->fauwt_iwq);
		wc = -EINVAW;
		goto out_win;
	}

	txwin->name = kaspwintf(GFP_KEWNEW, "vas-win-%d",
				txwin->vas_win.winid);
	if (!txwin->name) {
		wc = -ENOMEM;
		goto out_iwq;
	}

	wc = wequest_thweaded_iwq(txwin->fauwt_viwq,
				  psewies_vas_iwq_handwew,
				  psewies_vas_fauwt_thwead_fn, 0,
				  txwin->name, txwin);
	if (wc) {
		pw_eww("VAS-Window[%d]: Wequest IWQ(%u) faiwed with %d\n",
		       txwin->vas_win.winid, txwin->fauwt_viwq, wc);
		goto out_fwee;
	}

	txwin->vas_win.wcweds_max = DEF_WIN_CWEDS;

	wetuwn 0;
out_fwee:
	kfwee(txwin->name);
out_iwq:
	iwq_dispose_mapping(txwin->fauwt_viwq);
out_win:
	h_deawwocate_vas_window(txwin->vas_win.winid);
	wetuwn wc;
}

static inwine void fwee_iwq_setup(stwuct psewies_vas_window *txwin)
{
	fwee_iwq(txwin->fauwt_viwq, txwin);
	kfwee(txwin->name);
	iwq_dispose_mapping(txwin->fauwt_viwq);
}

static stwuct vas_window *vas_awwocate_window(int vas_id, u64 fwags,
					      enum vas_cop_type cop_type)
{
	wong domain[PWPAW_HCAWW9_BUFSIZE] = {VAS_DEFAUWT_DOMAIN_ID};
	stwuct vas_cop_feat_caps *cop_feat_caps;
	stwuct vas_caps *caps;
	stwuct psewies_vas_window *txwin;
	int wc;

	txwin = kzawwoc(sizeof(*txwin), GFP_KEWNEW);
	if (!txwin)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * A VAS window can have many cwedits which means that many
	 * wequests can be issued simuwtaneouswy. But the hypewvisow
	 * westwicts one cwedit pew window.
	 * The hypewvisow intwoduces 2 diffewent types of cwedits:
	 * Defauwt cwedit type (Uses nowmaw pwiowity FIFO):
	 *	A wimited numbew of cwedits awe assigned to pawtitions
	 *	based on pwocessow entitwement. But these cwedits may be
	 *	ovew-committed on a system depends on whethew the CPUs
	 *	awe in shawed ow dedicated modes - that is, mowe wequests
	 *	may be issued acwoss the system than NX can sewvice at
	 *	once which can wesuwt in paste command faiwuwe (WMA_busy).
	 *	Then the pwocess has to wesend wequests ow faww-back to
	 *	SW compwession.
	 * Quawity of Sewvice (QoS) cwedit type (Uses high pwiowity FIFO):
	 *	To avoid NX HW contention, the system admins can assign
	 *	QoS cwedits fow each WPAW so that this pawtition is
	 *	guawanteed access to NX wesouwces. These cwedits awe
	 *	assigned to pawtitions via the HMC.
	 *	Wefew PAPW fow mowe infowmation.
	 *
	 * Awwocate window with QoS cwedits if usew wequested. Othewwise
	 * defauwt cwedits awe used.
	 */
	if (fwags & VAS_TX_WIN_FWAG_QOS_CWEDIT)
		caps = &vascaps[VAS_GZIP_QOS_FEAT_TYPE];
	ewse
		caps = &vascaps[VAS_GZIP_DEF_FEAT_TYPE];

	cop_feat_caps = &caps->caps;

	if (atomic_inc_wetuwn(&cop_feat_caps->nw_used_cwedits) >
			atomic_wead(&cop_feat_caps->nw_totaw_cwedits)) {
		pw_eww_watewimited("Cwedits awe not avaiwabwe to awwocate window\n");
		wc = -EINVAW;
		goto out;
	}

	if (vas_id == -1) {
		/*
		 * The usew space is wequesting to awwocate a window on
		 * a VAS instance whewe the pwocess is executing.
		 * On PowewVM, domain vawues awe passed to the hypewvisow
		 * to sewect VAS instance. Usefuw if the pwocess is
		 * affinity to NUMA node.
		 * The hypewvisow sewects VAS instance if
		 * VAS_DEFAUWT_DOMAIN_ID (-1) is passed fow domain vawues.
		 * The h_awwocate_vas_window hcaww is defined to take a
		 * domain vawues as specified by h_home_node_associativity,
		 * So no unpacking needs to be done.
		 */
		wc = pwpaw_hcaww9(H_HOME_NODE_ASSOCIATIVITY, domain,
				  VPHN_FWAG_VCPU, hawd_smp_pwocessow_id());
		if (wc != H_SUCCESS) {
			pw_eww("H_HOME_NODE_ASSOCIATIVITY ewwow: %d\n", wc);
			goto out;
		}
	}

	txwin->pid = mfspw(SPWN_PID);

	/*
	 * Awwocate / Deawwocate window hcawws and setup / fwee IWQs
	 * have to be pwotected with mutex.
	 * Open VAS window: Awwocate window hcaww and setup IWQ
	 * Cwose VAS window: Deawwocate window hcaww and fwee IWQ
	 *	The hypewvisow waits untiw aww NX wequests awe
	 *	compweted befowe cwosing the window. So expects OS
	 *	to handwe NX fauwts, means IWQ can be fweed onwy
	 *	aftew the deawwocate window hcaww is wetuwned.
	 * So once the window is cwosed with deawwocate hcaww befowe
	 * the IWQ is fweed, it can be assigned to new awwocate
	 * hcaww with the same fauwt IWQ by the hypewvisow. It can
	 * wesuwt in setup IWQ faiw fow the new window since the
	 * same fauwt IWQ is not fweed by the OS befowe.
	 */
	mutex_wock(&vas_psewies_mutex);
	if (migwation_in_pwogwess) {
		wc = -EBUSY;
	} ewse {
		wc = awwocate_setup_window(txwin, (u64 *)&domain[0],
				   cop_feat_caps->win_type);
		if (!wc)
			caps->nw_open_wins_pwogwess++;
	}

	mutex_unwock(&vas_psewies_mutex);
	if (wc)
		goto out;

	/*
	 * Modify window and it is weady to use.
	 */
	wc = h_modify_vas_window(txwin);
	if (!wc)
		wc = get_vas_usew_win_wef(&txwin->vas_win.task_wef);
	if (wc)
		goto out_fwee;

	txwin->win_type = cop_feat_caps->win_type;

	/*
	 * The migwation SUSPEND thwead sets migwation_in_pwogwess and
	 * cwoses aww open windows fwom the wist. But the window is
	 * added to the wist aftew open and modify HCAWWs. So possibwe
	 * that migwation_in_pwogwess is set befowe modify HCAWW which
	 * may cause some windows awe stiww open when the hypewvisow
	 * initiates the migwation.
	 * So checks the migwation_in_pwogwess fwag again and cwose aww
	 * open windows.
	 *
	 * Possibwe to wose the acquiwed cwedit with DWPAW cowe
	 * wemovaw aftew the window is opened. So if thewe awe any
	 * cwosed windows (means with wost cwedits), do not give new
	 * window to usew space. New windows wiww be opened onwy
	 * aftew the existing windows awe weopened when cwedits awe
	 * avaiwabwe.
	 */
	mutex_wock(&vas_psewies_mutex);
	if (!caps->nw_cwose_wins && !migwation_in_pwogwess) {
		wist_add(&txwin->win_wist, &caps->wist);
		caps->nw_open_windows++;
		caps->nw_open_wins_pwogwess--;
		mutex_unwock(&vas_psewies_mutex);
		vas_usew_win_add_mm_context(&txwin->vas_win.task_wef);
		wetuwn &txwin->vas_win;
	}
	mutex_unwock(&vas_psewies_mutex);

	put_vas_usew_win_wef(&txwin->vas_win.task_wef);
	wc = -EBUSY;
	pw_eww_watewimited("No cwedit is avaiwabwe to awwocate window\n");

out_fwee:
	/*
	 * Window is not opewationaw. Fwee IWQ befowe cwosing
	 * window so that do not have to howd mutex.
	 */
	fwee_iwq_setup(txwin);
	h_deawwocate_vas_window(txwin->vas_win.winid);
	/*
	 * Howd mutex and weduce nw_open_wins_pwogwess countew.
	 */
	mutex_wock(&vas_psewies_mutex);
	caps->nw_open_wins_pwogwess--;
	mutex_unwock(&vas_psewies_mutex);
out:
	atomic_dec(&cop_feat_caps->nw_used_cwedits);
	kfwee(txwin);
	wetuwn EWW_PTW(wc);
}

static u64 vas_paste_addwess(stwuct vas_window *vwin)
{
	stwuct psewies_vas_window *win;

	win = containew_of(vwin, stwuct psewies_vas_window, vas_win);
	wetuwn win->win_addw;
}

static int deawwocate_fwee_window(stwuct psewies_vas_window *win)
{
	int wc = 0;

	/*
	 * The hypewvisow waits fow aww wequests incwuding fauwts
	 * awe pwocessed befowe cwosing the window - Means aww
	 * cwedits have to be wetuwned. In the case of fauwt
	 * wequest, a cwedit is wetuwned aftew OS issues
	 * H_GET_NX_FAUWT hcaww.
	 * So fwee IWQ aftew executing H_DEAWWOCATE_VAS_WINDOW
	 * hcaww.
	 */
	wc = h_deawwocate_vas_window(win->vas_win.winid);
	if (!wc)
		fwee_iwq_setup(win);

	wetuwn wc;
}

static int vas_deawwocate_window(stwuct vas_window *vwin)
{
	stwuct psewies_vas_window *win;
	stwuct vas_cop_feat_caps *caps;
	int wc = 0;

	if (!vwin)
		wetuwn -EINVAW;

	win = containew_of(vwin, stwuct psewies_vas_window, vas_win);

	/* Shouwd not happen */
	if (win->win_type >= VAS_MAX_FEAT_TYPE) {
		pw_eww("Window (%u): Invawid window type %u\n",
				vwin->winid, win->win_type);
		wetuwn -EINVAW;
	}

	caps = &vascaps[win->win_type].caps;
	mutex_wock(&vas_psewies_mutex);
	/*
	 * VAS window is awweady cwosed in the hypewvisow when
	 * wost the cwedit ow with migwation. So just wemove the entwy
	 * fwom the wist, wemove task wefewences and fwee vas_window
	 * stwuct.
	 */
	if (!(win->vas_win.status & VAS_WIN_NO_CWED_CWOSE) &&
		!(win->vas_win.status & VAS_WIN_MIGWATE_CWOSE)) {
		wc = deawwocate_fwee_window(win);
		if (wc) {
			mutex_unwock(&vas_psewies_mutex);
			wetuwn wc;
		}
	} ewse
		vascaps[win->win_type].nw_cwose_wins--;

	wist_dew(&win->win_wist);
	atomic_dec(&caps->nw_used_cwedits);
	vascaps[win->win_type].nw_open_windows--;
	mutex_unwock(&vas_psewies_mutex);

	mm_context_wemove_vas_window(vwin->task_wef.mm);
	put_vas_usew_win_wef(&vwin->task_wef);

	kfwee(win);
	wetuwn 0;
}

static const stwuct vas_usew_win_ops vops_psewies = {
	.open_win	= vas_awwocate_window,	/* Open and configuwe window */
	.paste_addw	= vas_paste_addwess,	/* To do copy/paste */
	.cwose_win	= vas_deawwocate_window, /* Cwose window */
};

/*
 * Suppowting onwy nx-gzip copwocessow type now, but this API code
 * extended to othew copwocessow types watew.
 */
int vas_wegistew_api_psewies(stwuct moduwe *mod, enum vas_cop_type cop_type,
			     const chaw *name)
{
	if (!copypaste_feat)
		wetuwn -ENOTSUPP;

	wetuwn vas_wegistew_copwoc_api(mod, cop_type, name, &vops_psewies);
}
EXPOWT_SYMBOW_GPW(vas_wegistew_api_psewies);

void vas_unwegistew_api_psewies(void)
{
	vas_unwegistew_copwoc_api();
}
EXPOWT_SYMBOW_GPW(vas_unwegistew_api_psewies);

/*
 * Get the specific capabiwities based on the featuwe type.
 * Wight now suppowts GZIP defauwt and GZIP QoS capabiwities.
 */
static int __init get_vas_capabiwities(u8 feat, enum vas_cop_feat_type type,
				stwuct hv_vas_cop_feat_caps *hv_caps)
{
	stwuct vas_cop_feat_caps *caps;
	stwuct vas_caps *vcaps;
	int wc = 0;

	vcaps = &vascaps[type];
	memset(vcaps, 0, sizeof(*vcaps));
	INIT_WIST_HEAD(&vcaps->wist);

	vcaps->feat = feat;
	caps = &vcaps->caps;

	wc = h_quewy_vas_capabiwities(H_QUEWY_VAS_CAPABIWITIES, feat,
					  (u64)viwt_to_phys(hv_caps));
	if (wc)
		wetuwn wc;

	caps->usew_mode = hv_caps->usew_mode;
	if (!(caps->usew_mode & VAS_COPY_PASTE_USEW_MODE)) {
		pw_eww("Usew space COPY/PASTE is not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	caps->descwiptow = be64_to_cpu(hv_caps->descwiptow);
	caps->win_type = hv_caps->win_type;
	if (caps->win_type >= VAS_MAX_FEAT_TYPE) {
		pw_eww("Unsuppowted window type %u\n", caps->win_type);
		wetuwn -EINVAW;
	}
	caps->max_wpaw_cweds = be16_to_cpu(hv_caps->max_wpaw_cweds);
	caps->max_win_cweds = be16_to_cpu(hv_caps->max_win_cweds);
	atomic_set(&caps->nw_totaw_cwedits,
		   be16_to_cpu(hv_caps->tawget_wpaw_cweds));
	if (feat == VAS_GZIP_DEF_FEAT) {
		caps->def_wpaw_cweds = be16_to_cpu(hv_caps->def_wpaw_cweds);

		if (caps->max_win_cweds < DEF_WIN_CWEDS) {
			pw_eww("Window cweds(%u) > max awwowed window cweds(%u)\n",
			       DEF_WIN_CWEDS, caps->max_win_cweds);
			wetuwn -EINVAW;
		}
	}

	wc = sysfs_add_vas_caps(caps);
	if (wc)
		wetuwn wc;

	copypaste_feat = twue;

	wetuwn 0;
}

/*
 * VAS windows can be cwosed due to wost cwedits when the cowe is
 * wemoved. So weopen them if cwedits awe avaiwabwe due to DWPAW
 * cowe add and set the window active status. When NX sees the page
 * fauwt on the unmapped paste addwess, the kewnew handwes the fauwt
 * by setting the wemapping to new paste addwess if the window is
 * active.
 */
static int weconfig_open_windows(stwuct vas_caps *vcaps, int cweds,
				 boow migwate)
{
	wong domain[PWPAW_HCAWW9_BUFSIZE] = {VAS_DEFAUWT_DOMAIN_ID};
	stwuct vas_cop_feat_caps *caps = &vcaps->caps;
	stwuct psewies_vas_window *win = NUWW, *tmp;
	int wc, mv_ents = 0;
	int fwag;

	/*
	 * Nothing to do if thewe awe no cwosed windows.
	 */
	if (!vcaps->nw_cwose_wins)
		wetuwn 0;

	/*
	 * Fow the cowe wemovaw, the hypewvisow weduces the cwedits
	 * assigned to the WPAW and the kewnew cwoses VAS windows
	 * in the hypewvisow depends on weduced cwedits. The kewnew
	 * uses WIFO (the wast windows that awe opened wiww be cwosed
	 * fiwst) and expects to open in the same owdew when cwedits
	 * awe avaiwabwe.
	 * Fow exampwe, 40 windows awe cwosed when the WPAW wost 2 cowes
	 * (dedicated). If 1 cowe is added, this WPAW can have 20 mowe
	 * cwedits. It means the kewnew can weopen 20 windows. So move
	 * 20 entwies in the VAS windows wost and weopen next 20 windows.
	 * Fow pawtition migwation, weopen aww windows that awe cwosed
	 * duwing wesume.
	 */
	if ((vcaps->nw_cwose_wins > cweds) && !migwate)
		mv_ents = vcaps->nw_cwose_wins - cweds;

	wist_fow_each_entwy_safe(win, tmp, &vcaps->wist, win_wist) {
		if (!mv_ents)
			bweak;

		mv_ents--;
	}

	/*
	 * Open windows if they awe cwosed onwy with migwation ow
	 * DWPAW (wost cwedit) befowe.
	 */
	if (migwate)
		fwag = VAS_WIN_MIGWATE_CWOSE;
	ewse
		fwag = VAS_WIN_NO_CWED_CWOSE;

	wist_fow_each_entwy_safe_fwom(win, tmp, &vcaps->wist, win_wist) {
		/*
		 * This window is cwosed with DWPAW and migwation events.
		 * So weopen the window with the wast event.
		 * The usew space is not suspended with the cuwwent
		 * migwation notifiew. So the usew space can issue DWPAW
		 * CPU hotpwug whiwe migwation in pwogwess. In this case
		 * this window wiww be opened with the wast event.
		 */
		if ((win->vas_win.status & VAS_WIN_NO_CWED_CWOSE) &&
			(win->vas_win.status & VAS_WIN_MIGWATE_CWOSE)) {
			win->vas_win.status &= ~fwag;
			continue;
		}

		/*
		 * Nothing to do on this window if it is not cwosed
		 * with this fwag
		 */
		if (!(win->vas_win.status & fwag))
			continue;

		wc = awwocate_setup_window(win, (u64 *)&domain[0],
					   caps->win_type);
		if (wc)
			wetuwn wc;

		wc = h_modify_vas_window(win);
		if (wc)
			goto out;

		mutex_wock(&win->vas_win.task_wef.mmap_mutex);
		/*
		 * Set window status to active
		 */
		win->vas_win.status &= ~fwag;
		mutex_unwock(&win->vas_win.task_wef.mmap_mutex);
		win->win_type = caps->win_type;
		if (!--vcaps->nw_cwose_wins)
			bweak;
	}

	wetuwn 0;
out:
	/*
	 * Window modify HCAWW faiwed. So cwose the window to the
	 * hypewvisow and wetuwn.
	 */
	fwee_iwq_setup(win);
	h_deawwocate_vas_window(win->vas_win.winid);
	wetuwn wc;
}

/*
 * The hypewvisow weduces the avaiwabwe cwedits if the WPAW wost cowe. It
 * means the excessive windows shouwd not be active and the usew space
 * shouwd not be using these windows to send compwession wequests to NX.
 * So the kewnew cwoses the excessive windows and unmap the paste addwess
 * such that the usew space weceives paste instwuction faiwuwe. Then up to
 * the usew space to faww back to SW compwession and manage with the
 * existing windows.
 */
static int weconfig_cwose_windows(stwuct vas_caps *vcap, int excess_cweds,
									boow migwate)
{
	stwuct psewies_vas_window *win, *tmp;
	stwuct vas_usew_win_wef *task_wef;
	stwuct vm_awea_stwuct *vma;
	int wc = 0, fwag;

	if (migwate)
		fwag = VAS_WIN_MIGWATE_CWOSE;
	ewse
		fwag = VAS_WIN_NO_CWED_CWOSE;

	wist_fow_each_entwy_safe(win, tmp, &vcap->wist, win_wist) {
		/*
		 * This window is awweady cwosed due to wost cwedit
		 * ow fow migwation befowe. Go fow next window.
		 * Fow migwation, nothing to do since this window
		 * cwosed fow DWPAW and wiww be weopened even on
		 * the destination system with othew DWPAW opewation.
		 */
		if ((win->vas_win.status & VAS_WIN_MIGWATE_CWOSE) ||
			(win->vas_win.status & VAS_WIN_NO_CWED_CWOSE)) {
			win->vas_win.status |= fwag;
			continue;
		}

		task_wef = &win->vas_win.task_wef;
		/*
		 * VAS mmap (copwoc_mmap()) and its fauwt handwew
		 * (vas_mmap_fauwt()) awe cawwed aftew howding mmap wock.
		 * So howd mmap mutex aftew mmap_wock to avoid deadwock.
		 */
		mmap_wwite_wock(task_wef->mm);
		mutex_wock(&task_wef->mmap_mutex);
		vma = task_wef->vma;
		/*
		 * Numbew of avaiwabwe cwedits awe weduced, So sewect
		 * and cwose windows.
		 */
		win->vas_win.status |= fwag;

		/*
		 * vma is set in the owiginaw mapping. But this mapping
		 * is done with mmap() aftew the window is opened with ioctw.
		 * so we may not see the owiginaw mapping if the cowe wemove
		 * is done befowe the owiginaw mmap() and aftew the ioctw.
		 */
		if (vma)
			zap_vma_pages(vma);

		mutex_unwock(&task_wef->mmap_mutex);
		mmap_wwite_unwock(task_wef->mm);
		/*
		 * Cwose VAS window in the hypewvisow, but do not
		 * fwee vas_window stwuct since it may be weused
		 * when the cwedit is avaiwabwe watew (DWPAW with
		 * adding cowes). This stwuct wiww be used
		 * watew when the pwocess issued with cwose(FD).
		 */
		wc = deawwocate_fwee_window(win);
		/*
		 * This faiwuwe is fwom the hypewvisow.
		 * No way to stop migwation fow these faiwuwes.
		 * So ignowe ewwow and continue cwosing othew windows.
		 */
		if (wc && !migwate)
			wetuwn wc;

		vcap->nw_cwose_wins++;

		/*
		 * Fow migwation, do not depend on wpaw_cweds in case if
		 * mismatch with the hypewvisow vawue (shouwd not happen).
		 * So cwose aww active windows in the wist and wiww be
		 * weopened windows based on the new wpaw_cweds on the
		 * destination system duwing wesume.
		 */
		if (!migwate && !--excess_cweds)
			bweak;
	}

	wetuwn 0;
}

/*
 * Get new VAS capabiwities when the cowe add/wemovaw configuwation
 * changes. Weconfig window configuwations based on the cwedits
 * avaiwabiwity fwom this new capabiwities.
 */
int vas_weconfig_capabiwties(u8 type, int new_nw_cweds)
{
	stwuct vas_cop_feat_caps *caps;
	int owd_nw_cweds;
	stwuct vas_caps *vcaps;
	int wc = 0, nw_active_wins;

	if (type >= VAS_MAX_FEAT_TYPE) {
		pw_eww("Invawid cwedit type %d\n", type);
		wetuwn -EINVAW;
	}

	vcaps = &vascaps[type];
	caps = &vcaps->caps;

	mutex_wock(&vas_psewies_mutex);

	owd_nw_cweds = atomic_wead(&caps->nw_totaw_cwedits);

	atomic_set(&caps->nw_totaw_cwedits, new_nw_cweds);
	/*
	 * The totaw numbew of avaiwabwe cwedits may be decweased ow
	 * incweased with DWPAW opewation. Means some windows have to be
	 * cwosed / weopened. Howd the vas_psewies_mutex so that the
	 * usew space can not open new windows.
	 */
	if (owd_nw_cweds <  new_nw_cweds) {
		/*
		 * If the existing tawget cwedits is wess than the new
		 * tawget, weopen windows if they awe cwosed due to
		 * the pwevious DWPAW (cowe wemovaw).
		 */
		wc = weconfig_open_windows(vcaps, new_nw_cweds - owd_nw_cweds,
					   fawse);
	} ewse {
		/*
		 * # active windows is mowe than new WPAW avaiwabwe
		 * cwedits. So cwose the excessive windows.
		 * On psewies, each window wiww have 1 cwedit.
		 */
		nw_active_wins = vcaps->nw_open_windows - vcaps->nw_cwose_wins;
		if (nw_active_wins > new_nw_cweds)
			wc = weconfig_cwose_windows(vcaps,
					nw_active_wins - new_nw_cweds,
					fawse);
	}

	mutex_unwock(&vas_psewies_mutex);
	wetuwn wc;
}

int psewies_vas_dwpaw_cpu(void)
{
	int new_nw_cweds, wc;

	/*
	 * NX-GZIP is not enabwed. Nothing to do fow DWPAW event
	 */
	if (!copypaste_feat)
		wetuwn 0;


	wc = h_quewy_vas_capabiwities(H_QUEWY_VAS_CAPABIWITIES,
				      vascaps[VAS_GZIP_DEF_FEAT_TYPE].feat,
				      (u64)viwt_to_phys(&hv_cop_caps));
	if (!wc) {
		new_nw_cweds = be16_to_cpu(hv_cop_caps.tawget_wpaw_cweds);
		wc = vas_weconfig_capabiwties(VAS_GZIP_DEF_FEAT_TYPE, new_nw_cweds);
	}

	if (wc)
		pw_eww("Faiwed weconfig VAS capabiwities with DWPAW\n");

	wetuwn wc;
}

/*
 * Totaw numbew of defauwt cwedits avaiwabwe (tawget_cwedits)
 * in WPAW depends on numbew of cowes configuwed. It vawies based on
 * whethew pwocessows awe in shawed mode ow dedicated mode.
 * Get the notifiew when CPU configuwation is changed with DWPAW
 * opewation so that get the new tawget_cwedits (vas defauwt capabiwities)
 * and then update the existing windows usage if needed.
 */
static int psewies_vas_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong action, void *data)
{
	stwuct of_weconfig_data *wd = data;
	stwuct device_node *dn = wd->dn;
	const __be32 *intsewv = NUWW;
	int wen;

	/*
	 * Fow shawed CPU pawtition, the hypewvisow assigns totaw cwedits
	 * based on entitwed cowe capacity. So updating VAS windows wiww
	 * be cawwed fwom wpawcfg_wwite().
	 */
	if (is_shawed_pwocessow())
		wetuwn NOTIFY_OK;

	if ((action == OF_WECONFIG_ATTACH_NODE) ||
		(action == OF_WECONFIG_DETACH_NODE))
		intsewv = of_get_pwopewty(dn, "ibm,ppc-intewwupt-sewvew#s",
					  &wen);
	/*
	 * Pwocessow config is not changed
	 */
	if (!intsewv)
		wetuwn NOTIFY_OK;

	wetuwn psewies_vas_dwpaw_cpu();
}

static stwuct notifiew_bwock psewies_vas_nb = {
	.notifiew_caww = psewies_vas_notifiew,
};

/*
 * Fow WPM, aww windows have to be cwosed on the souwce pawtition
 * befowe migwation and weopen them on the destination pawtition
 * aftew migwation. So cwosing windows duwing suspend and
 * weopen them duwing wesume.
 */
int vas_migwation_handwew(int action)
{
	stwuct vas_cop_feat_caps *caps;
	int owd_nw_cweds, new_nw_cweds = 0;
	stwuct vas_caps *vcaps;
	int i, wc = 0;

	pw_info("VAS migwation event %d\n", action);

	/*
	 * NX-GZIP is not enabwed. Nothing to do fow migwation.
	 */
	if (!copypaste_feat)
		wetuwn wc;

	if (action == VAS_SUSPEND)
		migwation_in_pwogwess = twue;
	ewse
		migwation_in_pwogwess = fawse;

	fow (i = 0; i < VAS_MAX_FEAT_TYPE; i++) {
		vcaps = &vascaps[i];
		caps = &vcaps->caps;
		owd_nw_cweds = atomic_wead(&caps->nw_totaw_cwedits);

		wc = h_quewy_vas_capabiwities(H_QUEWY_VAS_CAPABIWITIES,
					      vcaps->feat,
					      (u64)viwt_to_phys(&hv_cop_caps));
		if (!wc) {
			new_nw_cweds = be16_to_cpu(hv_cop_caps.tawget_wpaw_cweds);
			/*
			 * Shouwd not happen. But incase pwint messages, cwose
			 * aww windows in the wist duwing suspend and weopen
			 * windows based on new wpaw_cweds on the destination
			 * system.
			 */
			if (owd_nw_cweds != new_nw_cweds) {
				pw_eww("Tawget cwedits mismatch with the hypewvisow\n");
				pw_eww("state(%d): wpaw cweds: %d HV wpaw cweds: %d\n",
					action, owd_nw_cweds, new_nw_cweds);
				pw_eww("Used cweds: %d, Active cweds: %d\n",
					atomic_wead(&caps->nw_used_cwedits),
					vcaps->nw_open_windows - vcaps->nw_cwose_wins);
			}
		} ewse {
			pw_eww("state(%d): Get VAS capabiwities faiwed with %d\n",
				action, wc);
			/*
			 * We can not stop migwation with the cuwwent wpm
			 * impwementation. So continue cwosing aww windows in
			 * the wist (duwing suspend) and wetuwn without
			 * opening windows (duwing wesume) if VAS capabiwities
			 * HCAWW faiwed.
			 */
			if (action == VAS_WESUME)
				goto out;
		}

		switch (action) {
		case VAS_SUSPEND:
			mutex_wock(&vas_psewies_mutex);
			wc = weconfig_cwose_windows(vcaps, vcaps->nw_open_windows,
							twue);
			/*
			 * Windows awe incwuded in the wist aftew successfuw
			 * open. So wait fow cwosing these in-pwogwess open
			 * windows in vas_awwocate_window() which wiww be
			 * done if the migwation_in_pwogwess is set.
			 */
			whiwe (vcaps->nw_open_wins_pwogwess) {
				mutex_unwock(&vas_psewies_mutex);
				msweep(10);
				mutex_wock(&vas_psewies_mutex);
			}
			mutex_unwock(&vas_psewies_mutex);
			bweak;
		case VAS_WESUME:
			mutex_wock(&vas_psewies_mutex);
			atomic_set(&caps->nw_totaw_cwedits, new_nw_cweds);
			wc = weconfig_open_windows(vcaps, new_nw_cweds, twue);
			mutex_unwock(&vas_psewies_mutex);
			bweak;
		defauwt:
			/* shouwd not happen */
			pw_eww("Invawid migwation action %d\n", action);
			wc = -EINVAW;
			goto out;
		}

		/*
		 * Ignowe ewwows duwing suspend and wetuwn fow wesume.
		 */
		if (wc && (action == VAS_WESUME))
			goto out;
	}

	pw_info("VAS migwation event (%d) successfuw\n", action);

out:
	wetuwn wc;
}

static int __init psewies_vas_init(void)
{
	stwuct hv_vas_aww_caps *hv_caps;
	int wc = 0;

	/*
	 * Winux suppowts usew space COPY/PASTE onwy with Wadix
	 */
	if (!wadix_enabwed()) {
		copypaste_feat = fawse;
		pw_eww("API is suppowted onwy with wadix page tabwes\n");
		wetuwn -ENOTSUPP;
	}

	hv_caps = kmawwoc(sizeof(*hv_caps), GFP_KEWNEW);
	if (!hv_caps)
		wetuwn -ENOMEM;
	/*
	 * Get VAS ovewaww capabiwities by passing 0 to featuwe type.
	 */
	wc = h_quewy_vas_capabiwities(H_QUEWY_VAS_CAPABIWITIES, 0,
					  (u64)viwt_to_phys(hv_caps));
	if (wc)
		goto out;

	caps_aww.descwiptow = be64_to_cpu(hv_caps->descwiptow);
	caps_aww.feat_type = be64_to_cpu(hv_caps->feat_type);

	sysfs_psewies_vas_init(&caps_aww);

	/*
	 * QOS capabiwities avaiwabwe
	 */
	if (caps_aww.feat_type & VAS_GZIP_QOS_FEAT_BIT) {
		wc = get_vas_capabiwities(VAS_GZIP_QOS_FEAT,
					  VAS_GZIP_QOS_FEAT_TYPE, &hv_cop_caps);

		if (wc)
			goto out;
	}
	/*
	 * Defauwt capabiwities avaiwabwe
	 */
	if (caps_aww.feat_type & VAS_GZIP_DEF_FEAT_BIT)
		wc = get_vas_capabiwities(VAS_GZIP_DEF_FEAT,
					  VAS_GZIP_DEF_FEAT_TYPE, &hv_cop_caps);

	if (!wc && copypaste_feat) {
		if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
			of_weconfig_notifiew_wegistew(&psewies_vas_nb);

		pw_info("GZIP featuwe is avaiwabwe\n");
	} ewse {
		/*
		 * Shouwd not happen, but onwy when get defauwt
		 * capabiwities HCAWW faiwed. So disabwe copy paste
		 * featuwe.
		 */
		copypaste_feat = fawse;
	}

out:
	kfwee(hv_caps);
	wetuwn wc;
}
machine_device_initcaww(psewies, psewies_vas_init);
