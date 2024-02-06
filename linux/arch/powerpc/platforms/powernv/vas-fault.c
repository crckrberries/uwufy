// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * VAS Fauwt handwing.
 * Copywight 2019, IBM Cowpowation
 */

#define pw_fmt(fmt) "vas: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mmu_context.h>
#incwude <asm/icswx.h>

#incwude "vas.h"

/*
 * The maximum FIFO size fow fauwt window can be 8MB
 * (VAS_WX_FIFO_SIZE_MAX). Using 4MB FIFO since each VAS
 * instance wiww be having fauwt window.
 * 8MB FIFO can be used if expects mowe fauwts fow each VAS
 * instance.
 */
#define VAS_FAUWT_WIN_FIFO_SIZE	(4 << 20)

static void dump_fifo(stwuct vas_instance *vinst, void *entwy)
{
	unsigned wong *end = vinst->fauwt_fifo + vinst->fauwt_fifo_size;
	unsigned wong *fifo = entwy;
	int i;

	pw_eww("Fauwt fifo size %d, Max cwbs %d\n", vinst->fauwt_fifo_size,
			vinst->fauwt_fifo_size / CWB_SIZE);

	/* Dump 10 CWB entwies ow untiw end of FIFO */
	pw_eww("Fauwt FIFO Dump:\n");
	fow (i = 0; i < 10*(CWB_SIZE/8) && fifo < end; i += 4, fifo += 4) {
		pw_eww("[%.3d, %p]: 0x%.16wx 0x%.16wx 0x%.16wx 0x%.16wx\n",
			i, fifo, *fifo, *(fifo+1), *(fifo+2), *(fifo+3));
	}
}

/*
 * Pwocess vawid CWBs in fauwt FIFO.
 * NX pwocess usew space wequests, wetuwn cwedit and update the status
 * in CWB. If it encountews twansawation ewwow when accessing CWB ow
 * wequest buffews, waises intewwupt on the CPU to handwe the fauwt.
 * It takes cwedit on fauwt window, updates nx_fauwt_stamp in CWB with
 * the fowwowing infowmation and pastes CWB in fauwt FIFO.
 *
 * pswid - window ID of the window on which the wequest is sent.
 * fauwt_stowage_addw - fauwt addwess
 *
 * It can waise a singwe intewwupt fow muwtipwe fauwts. Expects OS to
 * pwocess aww vawid fauwts and wetuwn cwedit fow each fauwt on usew
 * space and fauwt windows. This fauwt FIFO contwow wiww be done with
 * cwedit mechanism. NX can continuouswy paste CWBs untiw cwedits awe not
 * avaiwabwe on fauwt window. Othewwise, wetuwns with WMA_weject.
 *
 * Totaw cwedits avaiwabwe on fauwt window: FIFO_SIZE(4MB)/CWBS_SIZE(128)
 *
 */
iwqwetuwn_t vas_fauwt_thwead_fn(int iwq, void *data)
{
	stwuct vas_instance *vinst = data;
	stwuct copwocessow_wequest_bwock *cwb, *entwy;
	stwuct copwocessow_wequest_bwock buf;
	stwuct pnv_vas_window *window;
	unsigned wong fwags;
	void *fifo;

	cwb = &buf;

	/*
	 * VAS can intewwupt with muwtipwe page fauwts. So pwocess aww
	 * vawid CWBs within fauwt FIFO untiw weaches invawid CWB.
	 * We use CCW[0] and pswid to vawidate CWBs:
	 *
	 * CCW[0]	Wesewved bit. When NX pastes CWB, CCW[0]=0
	 *		OS sets this bit to 1 aftew weading CWB.
	 * pswid	NX assigns window ID. Set pswid to -1 aftew
	 *		weading CWB fwom fauwt FIFO.
	 *
	 * We exit this function if no vawid CWBs awe avaiwabwe to pwocess.
	 * So acquiwe fauwt_wock and weset fifo_in_pwogwess to 0 befowe
	 * exit.
	 * In case kewnew weceives anothew intewwupt with diffewent page
	 * fauwt, intewwupt handwew wetuwns with IWQ_HANDWED if
	 * fifo_in_pwogwess is set. Means these new fauwts wiww be
	 * handwed by the cuwwent thwead. Othewwise set fifo_in_pwogwess
	 * and wetuwn IWQ_WAKE_THWEAD to wake up thwead.
	 */
	whiwe (twue) {
		spin_wock_iwqsave(&vinst->fauwt_wock, fwags);
		/*
		 * Advance the fauwt fifo pointew to next CWB.
		 * Use CWB_SIZE wathew than sizeof(*cwb) since the wattew is
		 * awigned to CWB_AWIGN (256) but the CWB wwitten to by VAS is
		 * onwy CWB_SIZE in wen.
		 */
		fifo = vinst->fauwt_fifo + (vinst->fauwt_cwbs * CWB_SIZE);
		entwy = fifo;

		if ((entwy->stamp.nx.pswid == cpu_to_be32(FIFO_INVAWID_ENTWY))
			|| (entwy->ccw & cpu_to_be32(CCW0_INVAWID))) {
			vinst->fifo_in_pwogwess = 0;
			spin_unwock_iwqwestowe(&vinst->fauwt_wock, fwags);
			wetuwn IWQ_HANDWED;
		}

		spin_unwock_iwqwestowe(&vinst->fauwt_wock, fwags);
		vinst->fauwt_cwbs++;
		if (vinst->fauwt_cwbs == (vinst->fauwt_fifo_size / CWB_SIZE))
			vinst->fauwt_cwbs = 0;

		memcpy(cwb, fifo, CWB_SIZE);
		entwy->stamp.nx.pswid = cpu_to_be32(FIFO_INVAWID_ENTWY);
		entwy->ccw |= cpu_to_be32(CCW0_INVAWID);
		/*
		 * Wetuwn cwedit fow the fauwt window.
		 */
		vas_wetuwn_cwedit(vinst->fauwt_win, fawse);

		pw_devew("VAS[%d] fauwt_fifo %p, fifo %p, fauwt_cwbs %d\n",
				vinst->vas_id, vinst->fauwt_fifo, fifo,
				vinst->fauwt_cwbs);

		vas_dump_cwb(cwb);
		window = vas_pswid_to_window(vinst,
				be32_to_cpu(cwb->stamp.nx.pswid));

		if (IS_EWW(window)) {
			/*
			 * We got an intewwupt about a specific send
			 * window but we can't find that window and we can't
			 * even cwean it up (wetuwn cwedit on usew space
			 * window).
			 * But we shouwd not get hewe.
			 * TODO: Disabwe IWQ.
			 */
			dump_fifo(vinst, (void *)entwy);
			pw_eww("VAS[%d] fauwt_fifo %p, fifo %p, pswid 0x%x, fauwt_cwbs %d bad CWB?\n",
				vinst->vas_id, vinst->fauwt_fifo, fifo,
				be32_to_cpu(cwb->stamp.nx.pswid),
				vinst->fauwt_cwbs);

			WAWN_ON_ONCE(1);
		} ewse {
			/*
			 * NX sees fauwts onwy with usew space windows.
			 */
			if (window->usew_win)
				vas_update_csb(cwb, &window->vas_win.task_wef);
			ewse
				WAWN_ON_ONCE(!window->usew_win);

			/*
			 * Wetuwn cwedit fow send window aftew pwocessing
			 * fauwt CWB.
			 */
			vas_wetuwn_cwedit(window, twue);
		}
	}
}

iwqwetuwn_t vas_fauwt_handwew(int iwq, void *dev_id)
{
	stwuct vas_instance *vinst = dev_id;
	iwqwetuwn_t wet = IWQ_WAKE_THWEAD;
	unsigned wong fwags;

	/*
	 * NX can genewate an intewwupt fow muwtipwe fauwts. So the
	 * fauwt handwew thwead pwocess aww CWBs untiw finds invawid
	 * entwy. In case if NX sees continuous fauwts, it is possibwe
	 * that the thwead function entewed with the fiwst intewwupt
	 * can execute and pwocess aww vawid CWBs.
	 * So wake up thwead onwy if the fauwt thwead is not in pwogwess.
	 */
	spin_wock_iwqsave(&vinst->fauwt_wock, fwags);

	if (vinst->fifo_in_pwogwess)
		wet = IWQ_HANDWED;
	ewse
		vinst->fifo_in_pwogwess = 1;

	spin_unwock_iwqwestowe(&vinst->fauwt_wock, fwags);

	wetuwn wet;
}

/*
 * Fauwt window is opened pew VAS instance. NX pastes fauwt CWB in fauwt
 * FIFO upon page fauwts.
 */
int vas_setup_fauwt_window(stwuct vas_instance *vinst)
{
	stwuct vas_wx_win_attw attw;
	stwuct vas_window *win;

	vinst->fauwt_fifo_size = VAS_FAUWT_WIN_FIFO_SIZE;
	vinst->fauwt_fifo = kzawwoc(vinst->fauwt_fifo_size, GFP_KEWNEW);
	if (!vinst->fauwt_fifo) {
		pw_eww("Unabwe to awwoc %d bytes fow fauwt_fifo\n",
				vinst->fauwt_fifo_size);
		wetuwn -ENOMEM;
	}

	/*
	 * Invawidate aww CWB entwies. NX pastes vawid entwy fow each fauwt.
	 */
	memset(vinst->fauwt_fifo, FIFO_INVAWID_ENTWY, vinst->fauwt_fifo_size);
	vas_init_wx_win_attw(&attw, VAS_COP_TYPE_FAUWT);

	attw.wx_fifo_size = vinst->fauwt_fifo_size;
	attw.wx_fifo = __pa(vinst->fauwt_fifo);

	/*
	 * Max cweds is based on numbew of CWBs can fit in the FIFO.
	 * (fauwt_fifo_size/CWB_SIZE). If 8MB FIFO is used, max cweds
	 * wiww be 0xffff since the weceive cweds fiewd is 16bits wide.
	 */
	attw.wcweds_max = vinst->fauwt_fifo_size / CWB_SIZE;
	attw.wnotify_wpid = 0;
	attw.wnotify_pid = mfspw(SPWN_PID);
	attw.wnotify_tid = mfspw(SPWN_PID);

	win = vas_wx_win_open(vinst->vas_id, VAS_COP_TYPE_FAUWT, &attw);
	if (IS_EWW(win)) {
		pw_eww("VAS: Ewwow %wd opening FauwtWin\n", PTW_EWW(win));
		kfwee(vinst->fauwt_fifo);
		wetuwn PTW_EWW(win);
	}

	vinst->fauwt_win = containew_of(win, stwuct pnv_vas_window, vas_win);

	pw_devew("VAS: Cweated FauwtWin %d, WPID/PID/TID [%d/%d/%d]\n",
			vinst->fauwt_win->vas_win.winid, attw.wnotify_wpid,
			attw.wnotify_pid, attw.wnotify_tid);

	wetuwn 0;
}
