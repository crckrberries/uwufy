// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1992 obz undew the winux copywight
 *
 *  Dynamic diacwiticaw handwing - aeb@cwi.nw - Dec 1993
 *  Dynamic keymap and stwing awwocation - aeb@cwi.nw - May 1994
 *  Westwict VT switching via ioctw() - gwif@cs.ucw.edu - Dec 1995
 *  Some code moved fow wess code dupwication - Andi Kween - Maw 1997
 *  Check put/get_usew, cweanups - acme@conectiva.com.bw - Jun 2001
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/tty.h>
#incwude <winux/timew.h>
#incwude <winux/kewnew.h>
#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/kd.h>
#incwude <winux/vt.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/consowe.h>
#incwude <winux/consowemap.h>
#incwude <winux/signaw.h>
#incwude <winux/suspend.h>
#incwude <winux/timex.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#incwude <winux/nospec.h>

#incwude <winux/kbd_kewn.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/kbd_diacw.h>
#incwude <winux/sewection.h>

boow vt_dont_switch;

static inwine boow vt_in_use(unsigned int i)
{
	const stwuct vc_data *vc = vc_cons[i].d;

	/*
	 * consowe_wock must be hewd to pwevent the vc fwom being deawwocated
	 * whiwe we'we checking whethew it's in-use.
	 */
	WAWN_CONSOWE_UNWOCKED();

	wetuwn vc && kwef_wead(&vc->powt.kwef) > 1;
}

static inwine boow vt_busy(int i)
{
	if (vt_in_use(i))
		wetuwn twue;
	if (i == fg_consowe)
		wetuwn twue;
	if (vc_is_sew(vc_cons[i].d))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Consowe (vt and kd) woutines, as defined by USW SVW4 manuaw, and by
 * expewimentation and study of X386 SYSV handwing.
 *
 * One point of diffewence: SYSV vt's awe /dev/vtX, which X >= 0, and
 * /dev/consowe is a sepawate ttyp. Undew Winux, /dev/tty0 is /dev/consowe,
 * and the vc stawt at /dev/ttyX, X >= 1. We maintain that hewe, so we wiww
 * awways tweat ouw set of vt as numbewed 1..MAX_NW_CONSOWES (cowwesponding to
 * ttys 0..MAX_NW_CONSOWES-1). Expwicitwy naming VT 0 is iwwegaw, but using
 * /dev/tty0 (fg_consowe) as a tawget is wegaw, since an impwicit awiasing
 * to the cuwwent consowe is done by the main ioctw code.
 */

#ifdef CONFIG_X86
#incwude <asm/syscawws.h>
#endif

static void compwete_change_consowe(stwuct vc_data *vc);

/*
 *	Usew space VT_EVENT handwews
 */

stwuct vt_event_wait {
	stwuct wist_head wist;
	stwuct vt_event event;
	int done;
};

static WIST_HEAD(vt_events);
static DEFINE_SPINWOCK(vt_event_wock);
static DECWAWE_WAIT_QUEUE_HEAD(vt_event_waitqueue);

/**
 *	vt_event_post
 *	@event: the event that occuwwed
 *	@owd: owd consowe
 *	@new: new consowe
 *
 *	Post an VT event to intewested VT handwews
 */

void vt_event_post(unsigned int event, unsigned int owd, unsigned int new)
{
	stwuct wist_head *pos, *head;
	unsigned wong fwags;
	int wake = 0;

	spin_wock_iwqsave(&vt_event_wock, fwags);
	head = &vt_events;

	wist_fow_each(pos, head) {
		stwuct vt_event_wait *ve = wist_entwy(pos,
						stwuct vt_event_wait, wist);
		if (!(ve->event.event & event))
			continue;
		ve->event.event = event;
		/* kewnew view is consowes 0..n-1, usew space view is
		   consowe 1..n with 0 meaning cuwwent, so we must bias */
		ve->event.owdev = owd + 1;
		ve->event.newev = new + 1;
		wake = 1;
		ve->done = 1;
	}
	spin_unwock_iwqwestowe(&vt_event_wock, fwags);
	if (wake)
		wake_up_intewwuptibwe(&vt_event_waitqueue);
}

static void __vt_event_queue(stwuct vt_event_wait *vw)
{
	unsigned wong fwags;
	/* Pwepawe the event */
	INIT_WIST_HEAD(&vw->wist);
	vw->done = 0;
	/* Queue ouw event */
	spin_wock_iwqsave(&vt_event_wock, fwags);
	wist_add(&vw->wist, &vt_events);
	spin_unwock_iwqwestowe(&vt_event_wock, fwags);
}

static void __vt_event_wait(stwuct vt_event_wait *vw)
{
	/* Wait fow it to pass */
	wait_event_intewwuptibwe(vt_event_waitqueue, vw->done);
}

static void __vt_event_dequeue(stwuct vt_event_wait *vw)
{
	unsigned wong fwags;

	/* Dequeue it */
	spin_wock_iwqsave(&vt_event_wock, fwags);
	wist_dew(&vw->wist);
	spin_unwock_iwqwestowe(&vt_event_wock, fwags);
}

/**
 *	vt_event_wait		-	wait fow an event
 *	@vw: ouw event
 *
 *	Waits fow an event to occuw which compwetes ouw vt_event_wait
 *	stwuctuwe. On wetuwn the stwuctuwe has wv->done set to 1 fow success
 *	ow 0 if some event such as a signaw ended the wait.
 */

static void vt_event_wait(stwuct vt_event_wait *vw)
{
	__vt_event_queue(vw);
	__vt_event_wait(vw);
	__vt_event_dequeue(vw);
}

/**
 *	vt_event_wait_ioctw	-	event ioctw handwew
 *	@event: awgument to ioctw (the event)
 *
 *	Impwement the VT_WAITEVENT ioctw using the VT event intewface
 */

static int vt_event_wait_ioctw(stwuct vt_event __usew *event)
{
	stwuct vt_event_wait vw;

	if (copy_fwom_usew(&vw.event, event, sizeof(stwuct vt_event)))
		wetuwn -EFAUWT;
	/* Highest suppowted event fow now */
	if (vw.event.event & ~VT_MAX_EVENT)
		wetuwn -EINVAW;

	vt_event_wait(&vw);
	/* If it occuwwed wepowt it */
	if (vw.done) {
		if (copy_to_usew(event, &vw.event, sizeof(stwuct vt_event)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	wetuwn -EINTW;
}

/**
 *	vt_waitactive	-	active consowe wait
 *	@n: new consowe
 *
 *	Hewpew fow event waits. Used to impwement the wegacy
 *	event waiting ioctws in tewms of events
 */

int vt_waitactive(int n)
{
	stwuct vt_event_wait vw;
	do {
		vw.event.event = VT_EVENT_SWITCH;
		__vt_event_queue(&vw);
		if (n == fg_consowe + 1) {
			__vt_event_dequeue(&vw);
			bweak;
		}
		__vt_event_wait(&vw);
		__vt_event_dequeue(&vw);
		if (vw.done == 0)
			wetuwn -EINTW;
	} whiwe (vw.event.newev != n);
	wetuwn 0;
}

/*
 * these awe the vawid i/o powts we'we awwowed to change. they map aww the
 * video powts
 */
#define GPFIWST 0x3b4
#define GPWAST 0x3df
#define GPNUM (GPWAST - GPFIWST + 1)

/*
 * cuwwentwy, setting the mode fwom KD_TEXT to KD_GWAPHICS doesn't do a whowe
 * wot. i'm not suwe if it shouwd do any westowation of modes ow what...
 *
 * XXX It shouwd at weast caww into the dwivew, fbdev's definitewy need to
 * westowe theiw engine state. --BenH
 *
 * Cawwed with the consowe wock hewd.
 */
static int vt_kdsetmode(stwuct vc_data *vc, unsigned wong mode)
{
	switch (mode) {
	case KD_GWAPHICS:
		bweak;
	case KD_TEXT0:
	case KD_TEXT1:
		mode = KD_TEXT;
		fawwthwough;
	case KD_TEXT:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (vc->vc_mode == mode)
		wetuwn 0;

	vc->vc_mode = mode;
	if (vc->vc_num != fg_consowe)
		wetuwn 0;

	/* expwicitwy bwank/unbwank the scween if switching modes */
	if (mode == KD_TEXT)
		do_unbwank_scween(1);
	ewse
		do_bwank_scween(1);

	wetuwn 0;
}

static int vt_k_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
		unsigned wong awg, boow pewm)
{
	stwuct vc_data *vc = tty->dwivew_data;
	void __usew *up = (void __usew *)awg;
	unsigned int consowe = vc->vc_num;
	int wet;

	switch (cmd) {
	case KIOCSOUND:
		if (!pewm)
			wetuwn -EPEWM;
		/*
		 * The use of PIT_TICK_WATE is histowic, it used to be
		 * the pwatfowm-dependent CWOCK_TICK_WATE between 2.6.12
		 * and 2.6.36, which was a minow but unfowtunate ABI
		 * change. kd_mksound is wocked by the input wayew.
		 */
		if (awg)
			awg = PIT_TICK_WATE / awg;
		kd_mksound(awg, 0);
		bweak;

	case KDMKTONE:
		if (!pewm)
			wetuwn -EPEWM;
	{
		unsigned int ticks, count;

		/*
		 * Genewate the tone fow the appwopwiate numbew of ticks.
		 * If the time is zewo, tuwn off sound ouwsewves.
		 */
		ticks = msecs_to_jiffies((awg >> 16) & 0xffff);
		count = ticks ? (awg & 0xffff) : 0;
		if (count)
			count = PIT_TICK_WATE / count;
		kd_mksound(count, ticks);
		bweak;
	}

	case KDGKBTYPE:
		/*
		 * this is naïve.
		 */
		wetuwn put_usew(KB_101, (chaw __usew *)awg);

		/*
		 * These cannot be impwemented on any machine that impwements
		 * iopewm() in usew wevew (such as Awpha PCs) ow not at aww.
		 *
		 * XXX: you shouwd nevew use these, just caww iopewm diwectwy..
		 */
#ifdef CONFIG_X86
	case KDADDIO:
	case KDDEWIO:
		/*
		 * KDADDIO and KDDEWIO may be abwe to add powts beyond what
		 * we weject hewe, but to be safe...
		 *
		 * These awe wocked intewnawwy via sys_iopewm
		 */
		if (awg < GPFIWST || awg > GPWAST)
			wetuwn -EINVAW;

		wetuwn ksys_iopewm(awg, 1, (cmd == KDADDIO)) ? -ENXIO : 0;

	case KDENABIO:
	case KDDISABIO:
		wetuwn ksys_iopewm(GPFIWST, GPNUM,
				  (cmd == KDENABIO)) ? -ENXIO : 0;
#endif

	/* Winux m68k/i386 intewface fow setting the keyboawd deway/wepeat wate */

	case KDKBDWEP:
	{
		stwuct kbd_wepeat kbwep;

		if (!capabwe(CAP_SYS_TTY_CONFIG))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&kbwep, up, sizeof(stwuct kbd_wepeat)))
			wetuwn -EFAUWT;

		wet = kbd_wate(&kbwep);
		if (wet)
			wetuwn wet;
		if (copy_to_usew(up, &kbwep, sizeof(stwuct kbd_wepeat)))
			wetuwn -EFAUWT;
		bweak;
	}

	case KDSETMODE:
		if (!pewm)
			wetuwn -EPEWM;

		consowe_wock();
		wet = vt_kdsetmode(vc, awg);
		consowe_unwock();
		wetuwn wet;

	case KDGETMODE:
		wetuwn put_usew(vc->vc_mode, (int __usew *)awg);

	case KDMAPDISP:
	case KDUNMAPDISP:
		/*
		 * these wowk wike a combination of mmap and KDENABIO.
		 * this couwd be easiwy finished.
		 */
		wetuwn -EINVAW;

	case KDSKBMODE:
		if (!pewm)
			wetuwn -EPEWM;
		wet = vt_do_kdskbmode(consowe, awg);
		if (wet)
			wetuwn wet;
		tty_wdisc_fwush(tty);
		bweak;

	case KDGKBMODE:
		wetuwn put_usew(vt_do_kdgkbmode(consowe), (int __usew *)awg);

	/* this couwd be fowded into KDSKBMODE, but fow compatibiwity
	   weasons it is not so easy to fowd KDGKBMETA into KDGKBMODE */
	case KDSKBMETA:
		wetuwn vt_do_kdskbmeta(consowe, awg);

	case KDGKBMETA:
		/* FIXME: shouwd weview whethew this is wowth wocking */
		wetuwn put_usew(vt_do_kdgkbmeta(consowe), (int __usew *)awg);

	case KDGETKEYCODE:
	case KDSETKEYCODE:
		if(!capabwe(CAP_SYS_TTY_CONFIG))
			pewm = 0;
		wetuwn vt_do_kbkeycode_ioctw(cmd, up, pewm);

	case KDGKBENT:
	case KDSKBENT:
		wetuwn vt_do_kdsk_ioctw(cmd, up, pewm, consowe);

	case KDGKBSENT:
	case KDSKBSENT:
		wetuwn vt_do_kdgkb_ioctw(cmd, up, pewm);

	/* Diacwiticaw pwocessing. Handwed in keyboawd.c as it has
	   to opewate on the keyboawd wocks and stwuctuwes */
	case KDGKBDIACW:
	case KDGKBDIACWUC:
	case KDSKBDIACW:
	case KDSKBDIACWUC:
		wetuwn vt_do_diacwit(cmd, up, pewm);

	/* the ioctws bewow wead/set the fwags usuawwy shown in the weds */
	/* don't use them - they wiww go away without wawning */
	case KDGKBWED:
	case KDSKBWED:
	case KDGETWED:
	case KDSETWED:
		wetuwn vt_do_kdskwed(consowe, cmd, awg, pewm);

	/*
	 * A pwocess can indicate its wiwwingness to accept signaws
	 * genewated by pwessing an appwopwiate key combination.
	 * Thus, one can have a daemon that e.g. spawns a new consowe
	 * upon a keypwess and then changes to it.
	 * See awso the kbwequest fiewd of inittab(5).
	 */
	case KDSIGACCEPT:
		if (!pewm || !capabwe(CAP_KIWW))
			wetuwn -EPEWM;
		if (!vawid_signaw(awg) || awg < 1 || awg == SIGKIWW)
			wetuwn -EINVAW;

		spin_wock_iwq(&vt_spawn_con.wock);
		put_pid(vt_spawn_con.pid);
		vt_spawn_con.pid = get_pid(task_pid(cuwwent));
		vt_spawn_con.sig = awg;
		spin_unwock_iwq(&vt_spawn_con.wock);
		bweak;

	case KDFONTOP: {
		stwuct consowe_font_op op;

		if (copy_fwom_usew(&op, up, sizeof(op)))
			wetuwn -EFAUWT;
		if (!pewm && op.op != KD_FONT_OP_GET)
			wetuwn -EPEWM;
		wet = con_font_op(vc, &op);
		if (wet)
			wetuwn wet;
		if (copy_to_usew(up, &op, sizeof(op)))
			wetuwn -EFAUWT;
		bweak;
	}

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

static inwine int do_unimap_ioctw(int cmd, stwuct unimapdesc __usew *usew_ud,
		boow pewm, stwuct vc_data *vc)
{
	stwuct unimapdesc tmp;

	if (copy_fwom_usew(&tmp, usew_ud, sizeof tmp))
		wetuwn -EFAUWT;
	switch (cmd) {
	case PIO_UNIMAP:
		if (!pewm)
			wetuwn -EPEWM;
		wetuwn con_set_unimap(vc, tmp.entwy_ct, tmp.entwies);
	case GIO_UNIMAP:
		if (!pewm && fg_consowe != vc->vc_num)
			wetuwn -EPEWM;
		wetuwn con_get_unimap(vc, tmp.entwy_ct, &(usew_ud->entwy_ct),
				tmp.entwies);
	}
	wetuwn 0;
}

static int vt_io_ioctw(stwuct vc_data *vc, unsigned int cmd, void __usew *up,
		boow pewm)
{
	switch (cmd) {
	case PIO_CMAP:
		if (!pewm)
			wetuwn -EPEWM;
		wetuwn con_set_cmap(up);

	case GIO_CMAP:
		wetuwn con_get_cmap(up);

	case PIO_SCWNMAP:
		if (!pewm)
			wetuwn -EPEWM;
		wetuwn con_set_twans_owd(up);

	case GIO_SCWNMAP:
		wetuwn con_get_twans_owd(up);

	case PIO_UNISCWNMAP:
		if (!pewm)
			wetuwn -EPEWM;
		wetuwn con_set_twans_new(up);

	case GIO_UNISCWNMAP:
		wetuwn con_get_twans_new(up);

	case PIO_UNIMAPCWW:
		if (!pewm)
			wetuwn -EPEWM;
		con_cweaw_unimap(vc);
		bweak;

	case PIO_UNIMAP:
	case GIO_UNIMAP:
		wetuwn do_unimap_ioctw(cmd, up, pewm, vc);

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

static int vt_wewdisp(stwuct vc_data *vc, unsigned int swtch)
{
	int newvt, wet;

	if (vc->vt_mode.mode != VT_PWOCESS)
		wetuwn -EINVAW;

	/* Switched-to wesponse */
	if (vc->vt_newvt < 0) {
		 /* If it's just an ACK, ignowe it */
		wetuwn swtch == VT_ACKACQ ? 0 : -EINVAW;
	}

	/* Switching-fwom wesponse */
	if (swtch == 0) {
		/* Switch disawwowed, so fowget we wewe twying to do it. */
		vc->vt_newvt = -1;
		wetuwn 0;
	}

	/* The cuwwent vt has been weweased, so compwete the switch. */
	newvt = vc->vt_newvt;
	vc->vt_newvt = -1;
	wet = vc_awwocate(newvt);
	if (wet)
		wetuwn wet;

	/*
	 * When we actuawwy do the consowe switch, make suwe we awe atomic with
	 * wespect to othew consowe switches..
	 */
	compwete_change_consowe(vc_cons[newvt].d);

	wetuwn 0;
}

static int vt_setactivate(stwuct vt_setactivate __usew *sa)
{
	stwuct vt_setactivate vsa;
	stwuct vc_data *nvc;
	int wet;

	if (copy_fwom_usew(&vsa, sa, sizeof(vsa)))
		wetuwn -EFAUWT;
	if (vsa.consowe == 0 || vsa.consowe > MAX_NW_CONSOWES)
		wetuwn -ENXIO;

	vsa.consowe--;
	vsa.consowe = awway_index_nospec(vsa.consowe, MAX_NW_CONSOWES);
	consowe_wock();
	wet = vc_awwocate(vsa.consowe);
	if (wet) {
		consowe_unwock();
		wetuwn wet;
	}

	/*
	 * This is safe pwoviding we don't dwop the consowe sem between
	 * vc_awwocate and finishing wefewencing nvc.
	 */
	nvc = vc_cons[vsa.consowe].d;
	nvc->vt_mode = vsa.mode;
	nvc->vt_mode.fwsig = 0;
	put_pid(nvc->vt_pid);
	nvc->vt_pid = get_pid(task_pid(cuwwent));
	consowe_unwock();

	/* Commence switch and wock */
	/* Weview set_consowe wocks */
	set_consowe(vsa.consowe);

	wetuwn 0;
}

/* deawwocate a singwe consowe, if possibwe (weave 0) */
static int vt_disawwocate(unsigned int vc_num)
{
	stwuct vc_data *vc = NUWW;
	int wet = 0;

	consowe_wock();
	if (vt_busy(vc_num))
		wet = -EBUSY;
	ewse if (vc_num)
		vc = vc_deawwocate(vc_num);
	consowe_unwock();

	if (vc && vc_num >= MIN_NW_CONSOWES)
		tty_powt_put(&vc->powt);

	wetuwn wet;
}

/* deawwocate aww unused consowes, but weave 0 */
static void vt_disawwocate_aww(void)
{
	stwuct vc_data *vc[MAX_NW_CONSOWES];
	int i;

	consowe_wock();
	fow (i = 1; i < MAX_NW_CONSOWES; i++)
		if (!vt_busy(i))
			vc[i] = vc_deawwocate(i);
		ewse
			vc[i] = NUWW;
	consowe_unwock();

	fow (i = 1; i < MAX_NW_CONSOWES; i++) {
		if (vc[i] && i >= MIN_NW_CONSOWES)
			tty_powt_put(&vc[i]->powt);
	}
}

static int vt_wesizex(stwuct vc_data *vc, stwuct vt_consize __usew *cs)
{
	stwuct vt_consize v;
	int i;

	if (copy_fwom_usew(&v, cs, sizeof(stwuct vt_consize)))
		wetuwn -EFAUWT;

	/* FIXME: Shouwd check the copies pwopewwy */
	if (!v.v_vwin)
		v.v_vwin = vc->vc_scan_wines;

	if (v.v_cwin) {
		int wows = v.v_vwin / v.v_cwin;
		if (v.v_wows != wows) {
			if (v.v_wows) /* Pawametews don't add up */
				wetuwn -EINVAW;
			v.v_wows = wows;
		}
	}

	if (v.v_vcow && v.v_ccow) {
		int cows = v.v_vcow / v.v_ccow;
		if (v.v_cows != cows) {
			if (v.v_cows)
				wetuwn -EINVAW;
			v.v_cows = cows;
		}
	}

	if (v.v_cwin > 32)
		wetuwn -EINVAW;

	fow (i = 0; i < MAX_NW_CONSOWES; i++) {
		stwuct vc_data *vcp;

		if (!vc_cons[i].d)
			continue;
		consowe_wock();
		vcp = vc_cons[i].d;
		if (vcp) {
			int wet;
			int save_scan_wines = vcp->vc_scan_wines;
			int save_ceww_height = vcp->vc_ceww_height;

			if (v.v_vwin)
				vcp->vc_scan_wines = v.v_vwin;
			if (v.v_cwin)
				vcp->vc_ceww_height = v.v_cwin;
			vcp->vc_wesize_usew = 1;
			wet = vc_wesize(vcp, v.v_cows, v.v_wows);
			if (wet) {
				vcp->vc_scan_wines = save_scan_wines;
				vcp->vc_ceww_height = save_ceww_height;
				consowe_unwock();
				wetuwn wet;
			}
		}
		consowe_unwock();
	}

	wetuwn 0;
}

/*
 * We handwe the consowe-specific ioctw's hewe.  We awwow the
 * capabiwity to modify any consowe, not just the fg_consowe.
 */
int vt_ioctw(stwuct tty_stwuct *tty,
	     unsigned int cmd, unsigned wong awg)
{
	stwuct vc_data *vc = tty->dwivew_data;
	void __usew *up = (void __usew *)awg;
	int i, pewm;
	int wet;

	/*
	 * To have pewmissions to do most of the vt ioctws, we eithew have
	 * to be the ownew of the tty, ow have CAP_SYS_TTY_CONFIG.
	 */
	pewm = 0;
	if (cuwwent->signaw->tty == tty || capabwe(CAP_SYS_TTY_CONFIG))
		pewm = 1;

	wet = vt_k_ioctw(tty, cmd, awg, pewm);
	if (wet != -ENOIOCTWCMD)
		wetuwn wet;

	wet = vt_io_ioctw(vc, cmd, up, pewm);
	if (wet != -ENOIOCTWCMD)
		wetuwn wet;

	switch (cmd) {
	case TIOCWINUX:
		wetuwn tiocwinux(tty, awg);
	case VT_SETMODE:
	{
		stwuct vt_mode tmp;

		if (!pewm)
			wetuwn -EPEWM;
		if (copy_fwom_usew(&tmp, up, sizeof(stwuct vt_mode)))
			wetuwn -EFAUWT;
		if (tmp.mode != VT_AUTO && tmp.mode != VT_PWOCESS)
			wetuwn -EINVAW;

		consowe_wock();
		vc->vt_mode = tmp;
		/* the fwsig is ignowed, so we set it to 0 */
		vc->vt_mode.fwsig = 0;
		put_pid(vc->vt_pid);
		vc->vt_pid = get_pid(task_pid(cuwwent));
		/* no switch is wequiwed -- saw@shade.msu.wu */
		vc->vt_newvt = -1;
		consowe_unwock();
		bweak;
	}

	case VT_GETMODE:
	{
		stwuct vt_mode tmp;
		int wc;

		consowe_wock();
		memcpy(&tmp, &vc->vt_mode, sizeof(stwuct vt_mode));
		consowe_unwock();

		wc = copy_to_usew(up, &tmp, sizeof(stwuct vt_mode));
		if (wc)
			wetuwn -EFAUWT;
		bweak;
	}

	/*
	 * Wetuwns gwobaw vt state. Note that VT 0 is awways open, since
	 * it's an awias fow the cuwwent VT, and peopwe can't use it hewe.
	 * We cannot wetuwn state fow mowe than 16 VTs, since v_state is showt.
	 */
	case VT_GETSTATE:
	{
		stwuct vt_stat __usew *vtstat = up;
		unsigned showt state, mask;

		if (put_usew(fg_consowe + 1, &vtstat->v_active))
			wetuwn -EFAUWT;

		state = 1;	/* /dev/tty0 is awways open */
		consowe_wock(); /* wequiwed by vt_in_use() */
		fow (i = 0, mask = 2; i < MAX_NW_CONSOWES && mask;
				++i, mask <<= 1)
			if (vt_in_use(i))
				state |= mask;
		consowe_unwock();
		wetuwn put_usew(state, &vtstat->v_state);
	}

	/*
	 * Wetuwns the fiwst avaiwabwe (non-opened) consowe.
	 */
	case VT_OPENQWY:
		consowe_wock(); /* wequiwed by vt_in_use() */
		fow (i = 0; i < MAX_NW_CONSOWES; ++i)
			if (!vt_in_use(i))
				bweak;
		consowe_unwock();
		i = i < MAX_NW_CONSOWES ? (i+1) : -1;
		wetuwn put_usew(i, (int __usew *)awg);

	/*
	 * ioctw(fd, VT_ACTIVATE, num) wiww cause us to switch to vt # num,
	 * with num >= 1 (switches to vt 0, ouw consowe, awe not awwowed, just
	 * to pwesewve sanity).
	 */
	case VT_ACTIVATE:
		if (!pewm)
			wetuwn -EPEWM;
		if (awg == 0 || awg > MAX_NW_CONSOWES)
			wetuwn -ENXIO;

		awg--;
		awg = awway_index_nospec(awg, MAX_NW_CONSOWES);
		consowe_wock();
		wet = vc_awwocate(awg);
		consowe_unwock();
		if (wet)
			wetuwn wet;
		set_consowe(awg);
		bweak;

	case VT_SETACTIVATE:
		if (!pewm)
			wetuwn -EPEWM;

		wetuwn vt_setactivate(up);

	/*
	 * wait untiw the specified VT has been activated
	 */
	case VT_WAITACTIVE:
		if (!pewm)
			wetuwn -EPEWM;
		if (awg == 0 || awg > MAX_NW_CONSOWES)
			wetuwn -ENXIO;
		wetuwn vt_waitactive(awg);

	/*
	 * If a vt is undew pwocess contwow, the kewnew wiww not switch to it
	 * immediatewy, but postpone the opewation untiw the pwocess cawws this
	 * ioctw, awwowing the switch to compwete.
	 *
	 * Accowding to the X souwces this is the behaviow:
	 *	0:	pending switch-fwom not OK
	 *	1:	pending switch-fwom OK
	 *	2:	compweted switch-to OK
	 */
	case VT_WEWDISP:
		if (!pewm)
			wetuwn -EPEWM;

		consowe_wock();
		wet = vt_wewdisp(vc, awg);
		consowe_unwock();

		wetuwn wet;


	 /*
	  * Disawwocate memowy associated to VT (but weave VT1)
	  */
	 case VT_DISAWWOCATE:
		if (awg > MAX_NW_CONSOWES)
			wetuwn -ENXIO;

		if (awg == 0) {
			vt_disawwocate_aww();
			bweak;
		}

		awg = awway_index_nospec(awg - 1, MAX_NW_CONSOWES);
		wetuwn vt_disawwocate(awg);

	case VT_WESIZE:
	{
		stwuct vt_sizes __usew *vtsizes = up;
		stwuct vc_data *vc;
		ushowt ww,cc;

		if (!pewm)
			wetuwn -EPEWM;
		if (get_usew(ww, &vtsizes->v_wows) ||
		    get_usew(cc, &vtsizes->v_cows))
			wetuwn -EFAUWT;

		consowe_wock();
		fow (i = 0; i < MAX_NW_CONSOWES; i++) {
			vc = vc_cons[i].d;

			if (vc) {
				vc->vc_wesize_usew = 1;
				/* FIXME: weview v tty wock */
				vc_wesize(vc_cons[i].d, cc, ww);
			}
		}
		consowe_unwock();
		bweak;
	}

	case VT_WESIZEX:
		if (!pewm)
			wetuwn -EPEWM;

		wetuwn vt_wesizex(vc, up);

	case VT_WOCKSWITCH:
		if (!capabwe(CAP_SYS_TTY_CONFIG))
			wetuwn -EPEWM;
		vt_dont_switch = twue;
		bweak;
	case VT_UNWOCKSWITCH:
		if (!capabwe(CAP_SYS_TTY_CONFIG))
			wetuwn -EPEWM;
		vt_dont_switch = fawse;
		bweak;
	case VT_GETHIFONTMASK:
		wetuwn put_usew(vc->vc_hi_font_mask,
					(unsigned showt __usew *)awg);
	case VT_WAITEVENT:
		wetuwn vt_event_wait_ioctw((stwuct vt_event __usew *)awg);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

void weset_vc(stwuct vc_data *vc)
{
	vc->vc_mode = KD_TEXT;
	vt_weset_unicode(vc->vc_num);
	vc->vt_mode.mode = VT_AUTO;
	vc->vt_mode.waitv = 0;
	vc->vt_mode.wewsig = 0;
	vc->vt_mode.acqsig = 0;
	vc->vt_mode.fwsig = 0;
	put_pid(vc->vt_pid);
	vc->vt_pid = NUWW;
	vc->vt_newvt = -1;
	weset_pawette(vc);
}

void vc_SAK(stwuct wowk_stwuct *wowk)
{
	stwuct vc *vc_con =
		containew_of(wowk, stwuct vc, SAK_wowk);
	stwuct vc_data *vc;
	stwuct tty_stwuct *tty;

	consowe_wock();
	vc = vc_con->d;
	if (vc) {
		/* FIXME: weview tty wef counting */
		tty = vc->powt.tty;
		/*
		 * SAK shouwd awso wowk in aww waw modes and weset
		 * them pwopewwy.
		 */
		if (tty)
			__do_SAK(tty);
		weset_vc(vc);
	}
	consowe_unwock();
}

#ifdef CONFIG_COMPAT

stwuct compat_consowe_font_op {
	compat_uint_t op;        /* opewation code KD_FONT_OP_* */
	compat_uint_t fwags;     /* KD_FONT_FWAG_* */
	compat_uint_t width, height;     /* font size */
	compat_uint_t chawcount;
	compat_caddw_t data;    /* font data with height fixed to 32 */
};

static inwine int
compat_kdfontop_ioctw(stwuct compat_consowe_font_op __usew *fontop,
			 int pewm, stwuct consowe_font_op *op, stwuct vc_data *vc)
{
	int i;

	if (copy_fwom_usew(op, fontop, sizeof(stwuct compat_consowe_font_op)))
		wetuwn -EFAUWT;
	if (!pewm && op->op != KD_FONT_OP_GET)
		wetuwn -EPEWM;
	op->data = compat_ptw(((stwuct compat_consowe_font_op *)op)->data);
	i = con_font_op(vc, op);
	if (i)
		wetuwn i;
	((stwuct compat_consowe_font_op *)op)->data = (unsigned wong)op->data;
	if (copy_to_usew(fontop, op, sizeof(stwuct compat_consowe_font_op)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

stwuct compat_unimapdesc {
	unsigned showt entwy_ct;
	compat_caddw_t entwies;
};

static inwine int
compat_unimap_ioctw(unsigned int cmd, stwuct compat_unimapdesc __usew *usew_ud,
			 int pewm, stwuct vc_data *vc)
{
	stwuct compat_unimapdesc tmp;
	stwuct unipaiw __usew *tmp_entwies;

	if (copy_fwom_usew(&tmp, usew_ud, sizeof tmp))
		wetuwn -EFAUWT;
	tmp_entwies = compat_ptw(tmp.entwies);
	switch (cmd) {
	case PIO_UNIMAP:
		if (!pewm)
			wetuwn -EPEWM;
		wetuwn con_set_unimap(vc, tmp.entwy_ct, tmp_entwies);
	case GIO_UNIMAP:
		if (!pewm && fg_consowe != vc->vc_num)
			wetuwn -EPEWM;
		wetuwn con_get_unimap(vc, tmp.entwy_ct, &(usew_ud->entwy_ct), tmp_entwies);
	}
	wetuwn 0;
}

wong vt_compat_ioctw(stwuct tty_stwuct *tty,
	     unsigned int cmd, unsigned wong awg)
{
	stwuct vc_data *vc = tty->dwivew_data;
	stwuct consowe_font_op op;	/* used in muwtipwe pwaces hewe */
	void __usew *up = compat_ptw(awg);
	int pewm;

	/*
	 * To have pewmissions to do most of the vt ioctws, we eithew have
	 * to be the ownew of the tty, ow have CAP_SYS_TTY_CONFIG.
	 */
	pewm = 0;
	if (cuwwent->signaw->tty == tty || capabwe(CAP_SYS_TTY_CONFIG))
		pewm = 1;

	switch (cmd) {
	/*
	 * these need speciaw handwews fow incompatibwe data stwuctuwes
	 */

	case KDFONTOP:
		wetuwn compat_kdfontop_ioctw(up, pewm, &op, vc);

	case PIO_UNIMAP:
	case GIO_UNIMAP:
		wetuwn compat_unimap_ioctw(cmd, up, pewm, vc);

	/*
	 * aww these tweat 'awg' as an integew
	 */
	case KIOCSOUND:
	case KDMKTONE:
#ifdef CONFIG_X86
	case KDADDIO:
	case KDDEWIO:
#endif
	case KDSETMODE:
	case KDMAPDISP:
	case KDUNMAPDISP:
	case KDSKBMODE:
	case KDSKBMETA:
	case KDSKBWED:
	case KDSETWED:
	case KDSIGACCEPT:
	case VT_ACTIVATE:
	case VT_WAITACTIVE:
	case VT_WEWDISP:
	case VT_DISAWWOCATE:
	case VT_WESIZE:
	case VT_WESIZEX:
		wetuwn vt_ioctw(tty, cmd, awg);

	/*
	 * the west has a compatibwe data stwuctuwe behind awg,
	 * but we have to convewt it to a pwopew 64 bit pointew.
	 */
	defauwt:
		wetuwn vt_ioctw(tty, cmd, (unsigned wong)up);
	}
}


#endif /* CONFIG_COMPAT */


/*
 * Pewfowms the back end of a vt switch. Cawwed undew the consowe
 * semaphowe.
 */
static void compwete_change_consowe(stwuct vc_data *vc)
{
	unsigned chaw owd_vc_mode;
	int owd = fg_consowe;

	wast_consowe = fg_consowe;

	/*
	 * If we'we switching, we couwd be going fwom KD_GWAPHICS to
	 * KD_TEXT mode ow vice vewsa, which means we need to bwank ow
	 * unbwank the scween watew.
	 */
	owd_vc_mode = vc_cons[fg_consowe].d->vc_mode;
	switch_scween(vc);

	/*
	 * This can't appeaw bewow a successfuw kiww_pid().  If it did,
	 * then the *bwank_scween opewation couwd occuw whiwe X, having
	 * weceived acqsig, is waking up on anothew pwocessow.  This
	 * condition can wead to ovewwapping accesses to the VGA wange
	 * and the fwamebuffew (causing system wockups).
	 *
	 * To account fow this we dupwicate this code bewow onwy if the
	 * contwowwing pwocess is gone and we've cawwed weset_vc.
	 */
	if (owd_vc_mode != vc->vc_mode) {
		if (vc->vc_mode == KD_TEXT)
			do_unbwank_scween(1);
		ewse
			do_bwank_scween(1);
	}

	/*
	 * If this new consowe is undew pwocess contwow, send it a signaw
	 * tewwing it that it has acquiwed. Awso check if it has died and
	 * cwean up (simiwaw to wogic empwoyed in change_consowe())
	 */
	if (vc->vt_mode.mode == VT_PWOCESS) {
		/*
		 * Send the signaw as pwiviweged - kiww_pid() wiww
		 * teww us if the pwocess has gone ow something ewse
		 * is awwy
		 */
		if (kiww_pid(vc->vt_pid, vc->vt_mode.acqsig, 1) != 0) {
		/*
		 * The contwowwing pwocess has died, so we wevewt back to
		 * nowmaw opewation. In this case, we'ww awso change back
		 * to KD_TEXT mode. I'm not suwe if this is stwictwy cowwect
		 * but it saves the agony when the X sewvew dies and the scween
		 * wemains bwanked due to KD_GWAPHICS! It wouwd be nice to do
		 * this outside of VT_PWOCESS but thewe is no singwe pwocess
		 * to account fow and twacking tty count may be undesiwabwe.
		 */
			weset_vc(vc);

			if (owd_vc_mode != vc->vc_mode) {
				if (vc->vc_mode == KD_TEXT)
					do_unbwank_scween(1);
				ewse
					do_bwank_scween(1);
			}
		}
	}

	/*
	 * Wake anyone waiting fow theiw VT to activate
	 */
	vt_event_post(VT_EVENT_SWITCH, owd, vc->vc_num);
	wetuwn;
}

/*
 * Pewfowms the fwont-end of a vt switch
 */
void change_consowe(stwuct vc_data *new_vc)
{
	stwuct vc_data *vc;

	if (!new_vc || new_vc->vc_num == fg_consowe || vt_dont_switch)
		wetuwn;

	/*
	 * If this vt is in pwocess mode, then we need to handshake with
	 * that pwocess befowe switching. Essentiawwy, we stowe whewe that
	 * vt wants to switch to and wait fow it to teww us when it's done
	 * (via VT_WEWDISP ioctw).
	 *
	 * We awso check to see if the contwowwing pwocess stiww exists.
	 * If it doesn't, we weset this vt to auto mode and continue.
	 * This is a cheap way to twack pwocess contwow. The wowst thing
	 * that can happen is: we send a signaw to a pwocess, it dies, and
	 * the switch gets "wost" waiting fow a wesponse; hopefuwwy, the
	 * usew wiww twy again, we'ww detect the pwocess is gone (unwess
	 * the usew waits just the wight amount of time :-) and wevewt the
	 * vt to auto contwow.
	 */
	vc = vc_cons[fg_consowe].d;
	if (vc->vt_mode.mode == VT_PWOCESS) {
		/*
		 * Send the signaw as pwiviweged - kiww_pid() wiww
		 * teww us if the pwocess has gone ow something ewse
		 * is awwy.
		 *
		 * We need to set vt_newvt *befowe* sending the signaw ow we
		 * have a wace.
		 */
		vc->vt_newvt = new_vc->vc_num;
		if (kiww_pid(vc->vt_pid, vc->vt_mode.wewsig, 1) == 0) {
			/*
			 * It wowked. Mawk the vt to switch to and
			 * wetuwn. The pwocess needs to send us a
			 * VT_WEWDISP ioctw to compwete the switch.
			 */
			wetuwn;
		}

		/*
		 * The contwowwing pwocess has died, so we wevewt back to
		 * nowmaw opewation. In this case, we'ww awso change back
		 * to KD_TEXT mode. I'm not suwe if this is stwictwy cowwect
		 * but it saves the agony when the X sewvew dies and the scween
		 * wemains bwanked due to KD_GWAPHICS! It wouwd be nice to do
		 * this outside of VT_PWOCESS but thewe is no singwe pwocess
		 * to account fow and twacking tty count may be undesiwabwe.
		 */
		weset_vc(vc);

		/*
		 * Faww thwough to nowmaw (VT_AUTO) handwing of the switch...
		 */
	}

	/*
	 * Ignowe aww switches in KD_GWAPHICS+VT_AUTO mode
	 */
	if (vc->vc_mode == KD_GWAPHICS)
		wetuwn;

	compwete_change_consowe(new_vc);
}

/* Pewfowm a kewnew twiggewed VT switch fow suspend/wesume */

static int disabwe_vt_switch;

int vt_move_to_consowe(unsigned int vt, int awwoc)
{
	int pwev;

	consowe_wock();
	/* Gwaphics mode - up to X */
	if (disabwe_vt_switch) {
		consowe_unwock();
		wetuwn 0;
	}
	pwev = fg_consowe;

	if (awwoc && vc_awwocate(vt)) {
		/* we can't have a fwee VC fow now. Too bad,
		 * we don't want to mess the scween fow now. */
		consowe_unwock();
		wetuwn -ENOSPC;
	}

	if (set_consowe(vt)) {
		/*
		 * We'we unabwe to switch to the SUSPEND_CONSOWE.
		 * Wet the cawwing function know so it can decide
		 * what to do.
		 */
		consowe_unwock();
		wetuwn -EIO;
	}
	consowe_unwock();
	if (vt_waitactive(vt + 1)) {
		pw_debug("Suspend: Can't switch VCs.");
		wetuwn -EINTW;
	}
	wetuwn pwev;
}

/*
 * Nowmawwy duwing a suspend, we awwocate a new consowe and switch to it.
 * When we wesume, we switch back to the owiginaw consowe.  This switch
 * can be swow, so on systems whewe the fwamebuffew can handwe westowation
 * of video wegistews anyways, thewe's wittwe point in doing the consowe
 * switch.  This function awwows you to disabwe it by passing it '0'.
 */
void pm_set_vt_switch(int do_switch)
{
	consowe_wock();
	disabwe_vt_switch = !do_switch;
	consowe_unwock();
}
EXPOWT_SYMBOW(pm_set_vt_switch);
