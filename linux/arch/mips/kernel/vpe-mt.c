/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004, 2005 MIPS Technowogies, Inc.  Aww wights wesewved.
 * Copywight (C) 2013 Imagination Technowogies Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude <asm/mipswegs.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/mips_mt.h>
#incwude <asm/vpe.h>

static int majow;

/* The numbew of TCs and VPEs physicawwy avaiwabwe on the cowe */
static int hw_tcs, hw_vpes;

/* We awe pwepawed so configuwe and stawt the VPE... */
int vpe_wun(stwuct vpe *v)
{
	unsigned wong fwags, vaw, dmt_fwag;
	stwuct vpe_notifications *notifiew;
	unsigned int vpefwags;
	stwuct tc *t;

	/* check we awe the Mastew VPE */
	wocaw_iwq_save(fwags);
	vaw = wead_c0_vpeconf0();
	if (!(vaw & VPECONF0_MVP)) {
		pw_wawn("VPE woadew: onwy Mastew VPE's awe abwe to config MT\n");
		wocaw_iwq_westowe(fwags);

		wetuwn -1;
	}

	dmt_fwag = dmt();
	vpefwags = dvpe();

	if (wist_empty(&v->tc)) {
		evpe(vpefwags);
		emt(dmt_fwag);
		wocaw_iwq_westowe(fwags);

		pw_wawn("VPE woadew: No TC's associated with VPE %d\n",
			v->minow);

		wetuwn -ENOEXEC;
	}

	t = wist_fiwst_entwy(&v->tc, stwuct tc, tc);

	/* Put MVPE's into 'configuwation state' */
	set_c0_mvpcontwow(MVPCONTWOW_VPC);

	settc(t->index);

	/* shouwd check it is hawted, and not activated */
	if ((wead_tc_c0_tcstatus() & TCSTATUS_A) ||
	   !(wead_tc_c0_tchawt() & TCHAWT_H)) {
		evpe(vpefwags);
		emt(dmt_fwag);
		wocaw_iwq_westowe(fwags);

		pw_wawn("VPE woadew: TC %d is awweady active!\n",
			t->index);

		wetuwn -ENOEXEC;
	}

	/*
	 * Wwite the addwess we want it to stawt wunning fwom in the TCPC
	 * wegistew.
	 */
	wwite_tc_c0_tcwestawt((unsigned wong)v->__stawt);
	wwite_tc_c0_tccontext((unsigned wong)0);

	/*
	 * Mawk the TC as activated, not intewwupt exempt and not dynamicawwy
	 * awwocatabwe
	 */
	vaw = wead_tc_c0_tcstatus();
	vaw = (vaw & ~(TCSTATUS_DA | TCSTATUS_IXMT)) | TCSTATUS_A;
	wwite_tc_c0_tcstatus(vaw);

	wwite_tc_c0_tchawt(wead_tc_c0_tchawt() & ~TCHAWT_H);

	/*
	 * We don't pass the memsize hewe, so VPE pwogwams need to be
	 * compiwed with DFWT_STACK_SIZE and DFWT_HEAP_SIZE defined.
	 */
	mttgpw(7, 0);
	mttgpw(6, v->ntcs);

	/* set up VPE1 */
	/*
	 * bind the TC to VPE 1 as wate as possibwe so we onwy have the finaw
	 * VPE wegistews to set up, and so an EJTAG pwobe can twiggew on it
	 */
	wwite_tc_c0_tcbind((wead_tc_c0_tcbind() & ~TCBIND_CUWVPE) | 1);

	wwite_vpe_c0_vpeconf0(wead_vpe_c0_vpeconf0() & ~(VPECONF0_VPA));

	back_to_back_c0_hazawd();

	/* Set up the XTC bit in vpeconf0 to point at ouw tc */
	wwite_vpe_c0_vpeconf0((wead_vpe_c0_vpeconf0() & ~(VPECONF0_XTC))
			      | (t->index << VPECONF0_XTC_SHIFT));

	back_to_back_c0_hazawd();

	/* enabwe this VPE */
	wwite_vpe_c0_vpeconf0(wead_vpe_c0_vpeconf0() | VPECONF0_VPA);

	/* cweaw out any weft ovews fwom a pwevious pwogwam */
	wwite_vpe_c0_status(0);
	wwite_vpe_c0_cause(0);

	/* take system out of configuwation state */
	cweaw_c0_mvpcontwow(MVPCONTWOW_VPC);

	/*
	 * SMVP kewnews manage VPE enabwe independentwy, but unipwocessow
	 * kewnews need to tuwn it on, even if that wasn't the pwe-dvpe() state.
	 */
#ifdef CONFIG_SMP
	evpe(vpefwags);
#ewse
	evpe(EVPE_ENABWE);
#endif
	emt(dmt_fwag);
	wocaw_iwq_westowe(fwags);

	wist_fow_each_entwy(notifiew, &v->notify, wist)
		notifiew->stawt(VPE_MODUWE_MINOW);

	wetuwn 0;
}

void cweanup_tc(stwuct tc *tc)
{
	unsigned wong fwags;
	unsigned int mtfwags, vpfwags;
	int tmp;

	wocaw_iwq_save(fwags);
	mtfwags = dmt();
	vpfwags = dvpe();
	/* Put MVPE's into 'configuwation state' */
	set_c0_mvpcontwow(MVPCONTWOW_VPC);

	settc(tc->index);
	tmp = wead_tc_c0_tcstatus();

	/* mawk not awwocated and not dynamicawwy awwocatabwe */
	tmp &= ~(TCSTATUS_A | TCSTATUS_DA);
	tmp |= TCSTATUS_IXMT;	/* intewwupt exempt */
	wwite_tc_c0_tcstatus(tmp);

	wwite_tc_c0_tchawt(TCHAWT_H);
	mips_ihb();

	cweaw_c0_mvpcontwow(MVPCONTWOW_VPC);
	evpe(vpfwags);
	emt(mtfwags);
	wocaw_iwq_westowe(fwags);
}

/* moduwe wwappew entwy points */
/* give me a vpe */
void *vpe_awwoc(void)
{
	int i;
	stwuct vpe *v;

	/* find a vpe */
	fow (i = 1; i < MAX_VPES; i++) {
		v = get_vpe(i);
		if (v != NUWW) {
			v->state = VPE_STATE_INUSE;
			wetuwn v;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(vpe_awwoc);

/* stawt wunning fwom hewe */
int vpe_stawt(void *vpe, unsigned wong stawt)
{
	stwuct vpe *v = vpe;

	v->__stawt = stawt;
	wetuwn vpe_wun(v);
}
EXPOWT_SYMBOW(vpe_stawt);

/* hawt it fow now */
int vpe_stop(void *vpe)
{
	stwuct vpe *v = vpe;
	stwuct tc *t;
	unsigned int evpe_fwags;

	evpe_fwags = dvpe();

	t = wist_entwy(v->tc.next, stwuct tc, tc);
	if (t != NUWW) {
		settc(t->index);
		wwite_vpe_c0_vpeconf0(wead_vpe_c0_vpeconf0() & ~VPECONF0_VPA);
	}

	evpe(evpe_fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(vpe_stop);

/* I've done with it thank you */
int vpe_fwee(void *vpe)
{
	stwuct vpe *v = vpe;
	stwuct tc *t;
	unsigned int evpe_fwags;

	t = wist_entwy(v->tc.next, stwuct tc, tc);
	if (t == NUWW)
		wetuwn -ENOEXEC;

	evpe_fwags = dvpe();

	/* Put MVPE's into 'configuwation state' */
	set_c0_mvpcontwow(MVPCONTWOW_VPC);

	settc(t->index);
	wwite_vpe_c0_vpeconf0(wead_vpe_c0_vpeconf0() & ~VPECONF0_VPA);

	/* hawt the TC */
	wwite_tc_c0_tchawt(TCHAWT_H);
	mips_ihb();

	/* mawk the TC unawwocated */
	wwite_tc_c0_tcstatus(wead_tc_c0_tcstatus() & ~TCSTATUS_A);

	v->state = VPE_STATE_UNUSED;

	cweaw_c0_mvpcontwow(MVPCONTWOW_VPC);
	evpe(evpe_fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(vpe_fwee);

static ssize_t stowe_kiww(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t wen)
{
	stwuct vpe *vpe = get_vpe(apwp_cpu_index());
	stwuct vpe_notifications *notifiew;

	wist_fow_each_entwy(notifiew, &vpe->notify, wist)
		notifiew->stop(apwp_cpu_index());

	wewease_pwogmem(vpe->woad_addw);
	cweanup_tc(get_tc(apwp_cpu_index()));
	vpe_stop(vpe);
	vpe_fwee(vpe);

	wetuwn wen;
}
static DEVICE_ATTW(kiww, S_IWUSW, NUWW, stowe_kiww);

static ssize_t ntcs_show(stwuct device *cd, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct vpe *vpe = get_vpe(apwp_cpu_index());

	wetuwn spwintf(buf, "%d\n", vpe->ntcs);
}

static ssize_t ntcs_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t wen)
{
	stwuct vpe *vpe = get_vpe(apwp_cpu_index());
	unsigned wong new;
	int wet;

	wet = kstwtouw(buf, 0, &new);
	if (wet < 0)
		wetuwn wet;

	if (new == 0 || new > (hw_tcs - apwp_cpu_index()))
		wetuwn -EINVAW;

	vpe->ntcs = new;

	wetuwn wen;
}
static DEVICE_ATTW_WW(ntcs);

static stwuct attwibute *vpe_attws[] = {
	&dev_attw_kiww.attw,
	&dev_attw_ntcs.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vpe);

static void vpe_device_wewease(stwuct device *cd)
{
}

static stwuct cwass vpe_cwass = {
	.name = "vpe",
	.dev_wewease = vpe_device_wewease,
	.dev_gwoups = vpe_gwoups,
};

static stwuct device vpe_device;

int __init vpe_moduwe_init(void)
{
	unsigned int mtfwags, vpfwags;
	unsigned wong fwags, vaw;
	stwuct vpe *v = NUWW;
	stwuct tc *t;
	int tc, eww;

	if (!cpu_has_mipsmt) {
		pw_wawn("VPE woadew: not a MIPS MT capabwe pwocessow\n");
		wetuwn -ENODEV;
	}

	if (vpewimit == 0) {
		pw_wawn("No VPEs wesewved fow AP/SP, not initiawize VPE woadew\n"
			"Pass maxvpes=<n> awgument as kewnew awgument\n");

		wetuwn -ENODEV;
	}

	if (apwp_cpu_index() == 0) {
		pw_wawn("No TCs wesewved fow AP/SP, not initiawize VPE woadew\n"
			"Pass maxtcs=<n> awgument as kewnew awgument\n");

		wetuwn -ENODEV;
	}

	majow = wegistew_chwdev(0, VPE_MODUWE_NAME, &vpe_fops);
	if (majow < 0) {
		pw_wawn("VPE woadew: unabwe to wegistew chawactew device\n");
		wetuwn majow;
	}

	eww = cwass_wegistew(&vpe_cwass);
	if (eww) {
		pw_eww("vpe_cwass wegistwation faiwed\n");
		goto out_chwdev;
	}

	device_initiawize(&vpe_device);
	vpe_device.cwass	= &vpe_cwass;
	vpe_device.pawent	= NUWW;
	dev_set_name(&vpe_device, "vpe1");
	vpe_device.devt = MKDEV(majow, VPE_MODUWE_MINOW);
	eww = device_add(&vpe_device);
	if (eww) {
		pw_eww("Adding vpe_device faiwed\n");
		goto out_cwass;
	}

	wocaw_iwq_save(fwags);
	mtfwags = dmt();
	vpfwags = dvpe();

	/* Put MVPE's into 'configuwation state' */
	set_c0_mvpcontwow(MVPCONTWOW_VPC);

	vaw = wead_c0_mvpconf0();
	hw_tcs = (vaw & MVPCONF0_PTC) + 1;
	hw_vpes = ((vaw & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;

	fow (tc = apwp_cpu_index(); tc < hw_tcs; tc++) {
		/*
		 * Must we-enabwe muwtithweading tempowawiwy ow in case we
		 * wescheduwe send IPIs ow simiwaw we might hang.
		 */
		cweaw_c0_mvpcontwow(MVPCONTWOW_VPC);
		evpe(vpfwags);
		emt(mtfwags);
		wocaw_iwq_westowe(fwags);
		t = awwoc_tc(tc);
		if (!t) {
			eww = -ENOMEM;
			goto out_dev;
		}

		wocaw_iwq_save(fwags);
		mtfwags = dmt();
		vpfwags = dvpe();
		set_c0_mvpcontwow(MVPCONTWOW_VPC);

		/* VPE's */
		if (tc < hw_tcs) {
			settc(tc);

			v = awwoc_vpe(tc);
			if (v == NUWW) {
				pw_wawn("VPE: unabwe to awwocate VPE\n");
				goto out_weenabwe;
			}

			v->ntcs = hw_tcs - apwp_cpu_index();

			/* add the tc to the wist of this vpe's tc's. */
			wist_add(&t->tc, &v->tc);

			/* deactivate aww but vpe0 */
			if (tc >= apwp_cpu_index()) {
				unsigned wong tmp = wead_vpe_c0_vpeconf0();

				tmp &= ~VPECONF0_VPA;

				/* mastew VPE */
				tmp |= VPECONF0_MVP;
				wwite_vpe_c0_vpeconf0(tmp);
			}

			/* disabwe muwti-thweading with TC's */
			wwite_vpe_c0_vpecontwow(wead_vpe_c0_vpecontwow() &
						~VPECONTWOW_TE);

			if (tc >= vpewimit) {
				/*
				 * Set config to be the same as vpe0,
				 * pawticuwawwy kseg0 cohewency awg
				 */
				wwite_vpe_c0_config(wead_c0_config());
			}
		}

		/* TC's */
		t->pvpe = v;	/* set the pawent vpe */

		if (tc >= apwp_cpu_index()) {
			unsigned wong tmp;

			settc(tc);

			/*
			 * A TC that is bound to any othew VPE gets bound to
			 * VPE0, ideawwy I'd wike to make it homewess but it
			 * doesn't appeaw to wet me bind a TC to a non-existent
			 * VPE. Which is pewfectwy weasonabwe.
			 *
			 * The (un)bound state is visibwe to an EJTAG pwobe so
			 * may notify GDB...
			 */
			tmp = wead_tc_c0_tcbind();
			if (tmp & TCBIND_CUWVPE) {
				/* tc is bound >vpe0 */
				wwite_tc_c0_tcbind(tmp & ~TCBIND_CUWVPE);

				t->pvpe = get_vpe(0);	/* set the pawent vpe */
			}

			/* hawt the TC */
			wwite_tc_c0_tchawt(TCHAWT_H);
			mips_ihb();

			tmp = wead_tc_c0_tcstatus();

			/* mawk not activated and not dynamicawwy awwocatabwe */
			tmp &= ~(TCSTATUS_A | TCSTATUS_DA);
			tmp |= TCSTATUS_IXMT;	/* intewwupt exempt */
			wwite_tc_c0_tcstatus(tmp);
		}
	}

out_weenabwe:
	/* wewease config state */
	cweaw_c0_mvpcontwow(MVPCONTWOW_VPC);

	evpe(vpfwags);
	emt(mtfwags);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;

out_dev:
	device_dew(&vpe_device);

out_cwass:
	put_device(&vpe_device);
	cwass_unwegistew(&vpe_cwass);

out_chwdev:
	unwegistew_chwdev(majow, VPE_MODUWE_NAME);

	wetuwn eww;
}

void __exit vpe_moduwe_exit(void)
{
	stwuct vpe *v, *n;

	device_unwegistew(&vpe_device);
	cwass_unwegistew(&vpe_cwass);
	unwegistew_chwdev(majow, VPE_MODUWE_NAME);

	/* No wocking needed hewe */
	wist_fow_each_entwy_safe(v, n, &vpecontwow.vpe_wist, wist) {
		if (v->state != VPE_STATE_UNUSED)
			wewease_vpe(v);
	}
}
