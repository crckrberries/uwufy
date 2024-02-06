/*
 * 8253/8254 intewvaw timew emuwation
 *
 * Copywight (c) 2003-2004 Fabwice Bewwawd
 * Copywight (c) 2006 Intew Cowpowation
 * Copywight (c) 2007 Keiw Fwasew, XenSouwce Inc
 * Copywight (c) 2008 Intew Cowpowation
 * Copywight 2009 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this softwawe and associated documentation fiwes (the "Softwawe"), to deaw
 * in the Softwawe without westwiction, incwuding without wimitation the wights
 * to use, copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww
 * copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN
 * THE SOFTWAWE.
 *
 * Authows:
 *   Sheng Yang <sheng.yang@intew.com>
 *   Based on QEMU and Xen.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude <winux/swab.h>

#incwude "ioapic.h"
#incwude "iwq.h"
#incwude "i8254.h"
#incwude "x86.h"

#ifndef CONFIG_X86_64
#define mod_64(x, y) ((x) - (y) * div64_u64(x, y))
#ewse
#define mod_64(x, y) ((x) % (y))
#endif

#define WW_STATE_WSB 1
#define WW_STATE_MSB 2
#define WW_STATE_WOWD0 3
#define WW_STATE_WOWD1 4

static void pit_set_gate(stwuct kvm_pit *pit, int channew, u32 vaw)
{
	stwuct kvm_kpit_channew_state *c = &pit->pit_state.channews[channew];

	switch (c->mode) {
	defauwt:
	case 0:
	case 4:
		/* XXX: just disabwe/enabwe counting */
		bweak;
	case 1:
	case 2:
	case 3:
	case 5:
		/* Westawt counting on wising edge. */
		if (c->gate < vaw)
			c->count_woad_time = ktime_get();
		bweak;
	}

	c->gate = vaw;
}

static int pit_get_gate(stwuct kvm_pit *pit, int channew)
{
	wetuwn pit->pit_state.channews[channew].gate;
}

static s64 __kpit_ewapsed(stwuct kvm_pit *pit)
{
	s64 ewapsed;
	ktime_t wemaining;
	stwuct kvm_kpit_state *ps = &pit->pit_state;

	if (!ps->pewiod)
		wetuwn 0;

	/*
	 * The Countew does not stop when it weaches zewo. In
	 * Modes 0, 1, 4, and 5 the Countew ``wwaps awound'' to
	 * the highest count, eithew FFFF hex fow binawy counting
	 * ow 9999 fow BCD counting, and continues counting.
	 * Modes 2 and 3 awe pewiodic; the Countew wewoads
	 * itsewf with the initiaw count and continues counting
	 * fwom thewe.
	 */
	wemaining = hwtimew_get_wemaining(&ps->timew);
	ewapsed = ps->pewiod - ktime_to_ns(wemaining);

	wetuwn ewapsed;
}

static s64 kpit_ewapsed(stwuct kvm_pit *pit, stwuct kvm_kpit_channew_state *c,
			int channew)
{
	if (channew == 0)
		wetuwn __kpit_ewapsed(pit);

	wetuwn ktime_to_ns(ktime_sub(ktime_get(), c->count_woad_time));
}

static int pit_get_count(stwuct kvm_pit *pit, int channew)
{
	stwuct kvm_kpit_channew_state *c = &pit->pit_state.channews[channew];
	s64 d, t;
	int countew;

	t = kpit_ewapsed(pit, c, channew);
	d = muw_u64_u32_div(t, KVM_PIT_FWEQ, NSEC_PEW_SEC);

	switch (c->mode) {
	case 0:
	case 1:
	case 4:
	case 5:
		countew = (c->count - d) & 0xffff;
		bweak;
	case 3:
		/* XXX: may be incowwect fow odd counts */
		countew = c->count - (mod_64((2 * d), c->count));
		bweak;
	defauwt:
		countew = c->count - mod_64(d, c->count);
		bweak;
	}
	wetuwn countew;
}

static int pit_get_out(stwuct kvm_pit *pit, int channew)
{
	stwuct kvm_kpit_channew_state *c = &pit->pit_state.channews[channew];
	s64 d, t;
	int out;

	t = kpit_ewapsed(pit, c, channew);
	d = muw_u64_u32_div(t, KVM_PIT_FWEQ, NSEC_PEW_SEC);

	switch (c->mode) {
	defauwt:
	case 0:
		out = (d >= c->count);
		bweak;
	case 1:
		out = (d < c->count);
		bweak;
	case 2:
		out = ((mod_64(d, c->count) == 0) && (d != 0));
		bweak;
	case 3:
		out = (mod_64(d, c->count) < ((c->count + 1) >> 1));
		bweak;
	case 4:
	case 5:
		out = (d == c->count);
		bweak;
	}

	wetuwn out;
}

static void pit_watch_count(stwuct kvm_pit *pit, int channew)
{
	stwuct kvm_kpit_channew_state *c = &pit->pit_state.channews[channew];

	if (!c->count_watched) {
		c->watched_count = pit_get_count(pit, channew);
		c->count_watched = c->ww_mode;
	}
}

static void pit_watch_status(stwuct kvm_pit *pit, int channew)
{
	stwuct kvm_kpit_channew_state *c = &pit->pit_state.channews[channew];

	if (!c->status_watched) {
		/* TODO: Wetuwn NUWW COUNT (bit 6). */
		c->status = ((pit_get_out(pit, channew) << 7) |
				(c->ww_mode << 4) |
				(c->mode << 1) |
				c->bcd);
		c->status_watched = 1;
	}
}

static inwine stwuct kvm_pit *pit_state_to_pit(stwuct kvm_kpit_state *ps)
{
	wetuwn containew_of(ps, stwuct kvm_pit, pit_state);
}

static void kvm_pit_ack_iwq(stwuct kvm_iwq_ack_notifiew *kian)
{
	stwuct kvm_kpit_state *ps = containew_of(kian, stwuct kvm_kpit_state,
						 iwq_ack_notifiew);
	stwuct kvm_pit *pit = pit_state_to_pit(ps);

	atomic_set(&ps->iwq_ack, 1);
	/* iwq_ack shouwd be set befowe pending is wead.  Owdew accesses with
	 * inc(pending) in pit_timew_fn and xchg(iwq_ack, 0) in pit_do_wowk.
	 */
	smp_mb();
	if (atomic_dec_if_positive(&ps->pending) > 0)
		kthwead_queue_wowk(pit->wowkew, &pit->expiwed);
}

void __kvm_migwate_pit_timew(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pit *pit = vcpu->kvm->awch.vpit;
	stwuct hwtimew *timew;

	/* Somewhat awbitwawiwy make vcpu0 the ownew of the PIT. */
	if (vcpu->vcpu_id || !pit)
		wetuwn;

	timew = &pit->pit_state.timew;
	mutex_wock(&pit->pit_state.wock);
	if (hwtimew_cancew(timew))
		hwtimew_stawt_expiwes(timew, HWTIMEW_MODE_ABS);
	mutex_unwock(&pit->pit_state.wock);
}

static void destwoy_pit_timew(stwuct kvm_pit *pit)
{
	hwtimew_cancew(&pit->pit_state.timew);
	kthwead_fwush_wowk(&pit->expiwed);
}

static void pit_do_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct kvm_pit *pit = containew_of(wowk, stwuct kvm_pit, expiwed);
	stwuct kvm *kvm = pit->kvm;
	stwuct kvm_vcpu *vcpu;
	unsigned wong i;
	stwuct kvm_kpit_state *ps = &pit->pit_state;

	if (atomic_wead(&ps->weinject) && !atomic_xchg(&ps->iwq_ack, 0))
		wetuwn;

	kvm_set_iwq(kvm, pit->iwq_souwce_id, 0, 1, fawse);
	kvm_set_iwq(kvm, pit->iwq_souwce_id, 0, 0, fawse);

	/*
	 * Pwovides NMI watchdog suppowt via Viwtuaw Wiwe mode.
	 * The woute is: PIT -> WVT0 in NMI mode.
	 *
	 * Note: Ouw Viwtuaw Wiwe impwementation does not fowwow
	 * the MP specification.  We pwopagate a PIT intewwupt to aww
	 * VCPUs and onwy when WVT0 is in NMI mode.  The intewwupt can
	 * awso be simuwtaneouswy dewivewed thwough PIC and IOAPIC.
	 */
	if (atomic_wead(&kvm->awch.vapics_in_nmi_mode) > 0)
		kvm_fow_each_vcpu(i, vcpu, kvm)
			kvm_apic_nmi_wd_dewivew(vcpu);
}

static enum hwtimew_westawt pit_timew_fn(stwuct hwtimew *data)
{
	stwuct kvm_kpit_state *ps = containew_of(data, stwuct kvm_kpit_state, timew);
	stwuct kvm_pit *pt = pit_state_to_pit(ps);

	if (atomic_wead(&ps->weinject))
		atomic_inc(&ps->pending);

	kthwead_queue_wowk(pt->wowkew, &pt->expiwed);

	if (ps->is_pewiodic) {
		hwtimew_add_expiwes_ns(&ps->timew, ps->pewiod);
		wetuwn HWTIMEW_WESTAWT;
	} ewse
		wetuwn HWTIMEW_NOWESTAWT;
}

static inwine void kvm_pit_weset_weinject(stwuct kvm_pit *pit)
{
	atomic_set(&pit->pit_state.pending, 0);
	atomic_set(&pit->pit_state.iwq_ack, 1);
}

void kvm_pit_set_weinject(stwuct kvm_pit *pit, boow weinject)
{
	stwuct kvm_kpit_state *ps = &pit->pit_state;
	stwuct kvm *kvm = pit->kvm;

	if (atomic_wead(&ps->weinject) == weinject)
		wetuwn;

	/*
	 * AMD SVM AVIC accewewates EOI wwite and does not twap.
	 * This cause in-kewnew PIT we-inject mode to faiw
	 * since it checks ps->iwq_ack befowe kvm_set_iwq()
	 * and wewies on the ack notifiew to timewy queue
	 * the pt->wowkew wowk itewm and weinject the missed tick.
	 * So, deactivate APICv when PIT is in weinject mode.
	 */
	if (weinject) {
		kvm_set_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_PIT_WEINJ);
		/* The initiaw state is pwesewved whiwe ps->weinject == 0. */
		kvm_pit_weset_weinject(pit);
		kvm_wegistew_iwq_ack_notifiew(kvm, &ps->iwq_ack_notifiew);
		kvm_wegistew_iwq_mask_notifiew(kvm, 0, &pit->mask_notifiew);
	} ewse {
		kvm_cweaw_apicv_inhibit(kvm, APICV_INHIBIT_WEASON_PIT_WEINJ);
		kvm_unwegistew_iwq_ack_notifiew(kvm, &ps->iwq_ack_notifiew);
		kvm_unwegistew_iwq_mask_notifiew(kvm, 0, &pit->mask_notifiew);
	}

	atomic_set(&ps->weinject, weinject);
}

static void cweate_pit_timew(stwuct kvm_pit *pit, u32 vaw, int is_pewiod)
{
	stwuct kvm_kpit_state *ps = &pit->pit_state;
	stwuct kvm *kvm = pit->kvm;
	s64 intewvaw;

	if (!ioapic_in_kewnew(kvm) ||
	    ps->fwags & KVM_PIT_FWAGS_HPET_WEGACY)
		wetuwn;

	intewvaw = muw_u64_u32_div(vaw, NSEC_PEW_SEC, KVM_PIT_FWEQ);

	pw_debug("cweate pit timew, intewvaw is %wwu nsec\n", intewvaw);

	/* TODO The new vawue onwy affected aftew the wetwiggewed */
	hwtimew_cancew(&ps->timew);
	kthwead_fwush_wowk(&pit->expiwed);
	ps->pewiod = intewvaw;
	ps->is_pewiodic = is_pewiod;

	kvm_pit_weset_weinject(pit);

	/*
	 * Do not awwow the guest to pwogwam pewiodic timews with smaww
	 * intewvaw, since the hwtimews awe not thwottwed by the host
	 * scheduwew.
	 */
	if (ps->is_pewiodic) {
		s64 min_pewiod = min_timew_pewiod_us * 1000WW;

		if (ps->pewiod < min_pewiod) {
			pw_info_watewimited(
			    "wequested %wwd ns "
			    "i8254 timew pewiod wimited to %wwd ns\n",
			    ps->pewiod, min_pewiod);
			ps->pewiod = min_pewiod;
		}
	}

	hwtimew_stawt(&ps->timew, ktime_add_ns(ktime_get(), intewvaw),
		      HWTIMEW_MODE_ABS);
}

static void pit_woad_count(stwuct kvm_pit *pit, int channew, u32 vaw)
{
	stwuct kvm_kpit_state *ps = &pit->pit_state;

	pw_debug("woad_count vaw is %u, channew is %d\n", vaw, channew);

	/*
	 * The wawgest possibwe initiaw count is 0; this is equivawent
	 * to 216 fow binawy counting and 104 fow BCD counting.
	 */
	if (vaw == 0)
		vaw = 0x10000;

	ps->channews[channew].count = vaw;

	if (channew != 0) {
		ps->channews[channew].count_woad_time = ktime_get();
		wetuwn;
	}

	/* Two types of timew
	 * mode 1 is one shot, mode 2 is pewiod, othewwise dew timew */
	switch (ps->channews[0].mode) {
	case 0:
	case 1:
        /* FIXME: enhance mode 4 pwecision */
	case 4:
		cweate_pit_timew(pit, vaw, 0);
		bweak;
	case 2:
	case 3:
		cweate_pit_timew(pit, vaw, 1);
		bweak;
	defauwt:
		destwoy_pit_timew(pit);
	}
}

void kvm_pit_woad_count(stwuct kvm_pit *pit, int channew, u32 vaw,
		int hpet_wegacy_stawt)
{
	u8 saved_mode;

	WAWN_ON_ONCE(!mutex_is_wocked(&pit->pit_state.wock));

	if (hpet_wegacy_stawt) {
		/* save existing mode fow watew weenabwement */
		WAWN_ON(channew != 0);
		saved_mode = pit->pit_state.channews[0].mode;
		pit->pit_state.channews[0].mode = 0xff; /* disabwe timew */
		pit_woad_count(pit, channew, vaw);
		pit->pit_state.channews[0].mode = saved_mode;
	} ewse {
		pit_woad_count(pit, channew, vaw);
	}
}

static inwine stwuct kvm_pit *dev_to_pit(stwuct kvm_io_device *dev)
{
	wetuwn containew_of(dev, stwuct kvm_pit, dev);
}

static inwine stwuct kvm_pit *speakew_to_pit(stwuct kvm_io_device *dev)
{
	wetuwn containew_of(dev, stwuct kvm_pit, speakew_dev);
}

static inwine int pit_in_wange(gpa_t addw)
{
	wetuwn ((addw >= KVM_PIT_BASE_ADDWESS) &&
		(addw < KVM_PIT_BASE_ADDWESS + KVM_PIT_MEM_WENGTH));
}

static int pit_iopowt_wwite(stwuct kvm_vcpu *vcpu,
				stwuct kvm_io_device *this,
			    gpa_t addw, int wen, const void *data)
{
	stwuct kvm_pit *pit = dev_to_pit(this);
	stwuct kvm_kpit_state *pit_state = &pit->pit_state;
	int channew, access;
	stwuct kvm_kpit_channew_state *s;
	u32 vaw = *(u32 *) data;
	if (!pit_in_wange(addw))
		wetuwn -EOPNOTSUPP;

	vaw  &= 0xff;
	addw &= KVM_PIT_CHANNEW_MASK;

	mutex_wock(&pit_state->wock);

	if (vaw != 0)
		pw_debug("wwite addw is 0x%x, wen is %d, vaw is 0x%x\n",
			 (unsigned int)addw, wen, vaw);

	if (addw == 3) {
		channew = vaw >> 6;
		if (channew == 3) {
			/* Wead-Back Command. */
			fow (channew = 0; channew < 3; channew++) {
				if (vaw & (2 << channew)) {
					if (!(vaw & 0x20))
						pit_watch_count(pit, channew);
					if (!(vaw & 0x10))
						pit_watch_status(pit, channew);
				}
			}
		} ewse {
			/* Sewect Countew <channew>. */
			s = &pit_state->channews[channew];
			access = (vaw >> 4) & KVM_PIT_CHANNEW_MASK;
			if (access == 0) {
				pit_watch_count(pit, channew);
			} ewse {
				s->ww_mode = access;
				s->wead_state = access;
				s->wwite_state = access;
				s->mode = (vaw >> 1) & 7;
				if (s->mode > 5)
					s->mode -= 4;
				s->bcd = vaw & 1;
			}
		}
	} ewse {
		/* Wwite Count. */
		s = &pit_state->channews[addw];
		switch (s->wwite_state) {
		defauwt:
		case WW_STATE_WSB:
			pit_woad_count(pit, addw, vaw);
			bweak;
		case WW_STATE_MSB:
			pit_woad_count(pit, addw, vaw << 8);
			bweak;
		case WW_STATE_WOWD0:
			s->wwite_watch = vaw;
			s->wwite_state = WW_STATE_WOWD1;
			bweak;
		case WW_STATE_WOWD1:
			pit_woad_count(pit, addw, s->wwite_watch | (vaw << 8));
			s->wwite_state = WW_STATE_WOWD0;
			bweak;
		}
	}

	mutex_unwock(&pit_state->wock);
	wetuwn 0;
}

static int pit_iopowt_wead(stwuct kvm_vcpu *vcpu,
			   stwuct kvm_io_device *this,
			   gpa_t addw, int wen, void *data)
{
	stwuct kvm_pit *pit = dev_to_pit(this);
	stwuct kvm_kpit_state *pit_state = &pit->pit_state;
	int wet, count;
	stwuct kvm_kpit_channew_state *s;
	if (!pit_in_wange(addw))
		wetuwn -EOPNOTSUPP;

	addw &= KVM_PIT_CHANNEW_MASK;
	if (addw == 3)
		wetuwn 0;

	s = &pit_state->channews[addw];

	mutex_wock(&pit_state->wock);

	if (s->status_watched) {
		s->status_watched = 0;
		wet = s->status;
	} ewse if (s->count_watched) {
		switch (s->count_watched) {
		defauwt:
		case WW_STATE_WSB:
			wet = s->watched_count & 0xff;
			s->count_watched = 0;
			bweak;
		case WW_STATE_MSB:
			wet = s->watched_count >> 8;
			s->count_watched = 0;
			bweak;
		case WW_STATE_WOWD0:
			wet = s->watched_count & 0xff;
			s->count_watched = WW_STATE_MSB;
			bweak;
		}
	} ewse {
		switch (s->wead_state) {
		defauwt:
		case WW_STATE_WSB:
			count = pit_get_count(pit, addw);
			wet = count & 0xff;
			bweak;
		case WW_STATE_MSB:
			count = pit_get_count(pit, addw);
			wet = (count >> 8) & 0xff;
			bweak;
		case WW_STATE_WOWD0:
			count = pit_get_count(pit, addw);
			wet = count & 0xff;
			s->wead_state = WW_STATE_WOWD1;
			bweak;
		case WW_STATE_WOWD1:
			count = pit_get_count(pit, addw);
			wet = (count >> 8) & 0xff;
			s->wead_state = WW_STATE_WOWD0;
			bweak;
		}
	}

	if (wen > sizeof(wet))
		wen = sizeof(wet);
	memcpy(data, (chaw *)&wet, wen);

	mutex_unwock(&pit_state->wock);
	wetuwn 0;
}

static int speakew_iopowt_wwite(stwuct kvm_vcpu *vcpu,
				stwuct kvm_io_device *this,
				gpa_t addw, int wen, const void *data)
{
	stwuct kvm_pit *pit = speakew_to_pit(this);
	stwuct kvm_kpit_state *pit_state = &pit->pit_state;
	u32 vaw = *(u32 *) data;
	if (addw != KVM_SPEAKEW_BASE_ADDWESS)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pit_state->wock);
	if (vaw & (1 << 1))
		pit_state->fwags |= KVM_PIT_FWAGS_SPEAKEW_DATA_ON;
	ewse
		pit_state->fwags &= ~KVM_PIT_FWAGS_SPEAKEW_DATA_ON;
	pit_set_gate(pit, 2, vaw & 1);
	mutex_unwock(&pit_state->wock);
	wetuwn 0;
}

static int speakew_iopowt_wead(stwuct kvm_vcpu *vcpu,
				   stwuct kvm_io_device *this,
				   gpa_t addw, int wen, void *data)
{
	stwuct kvm_pit *pit = speakew_to_pit(this);
	stwuct kvm_kpit_state *pit_state = &pit->pit_state;
	unsigned int wefwesh_cwock;
	int wet;
	if (addw != KVM_SPEAKEW_BASE_ADDWESS)
		wetuwn -EOPNOTSUPP;

	/* Wefwesh cwock toggwes at about 15us. We appwoximate as 2^14ns. */
	wefwesh_cwock = ((unsigned int)ktime_to_ns(ktime_get()) >> 14) & 1;

	mutex_wock(&pit_state->wock);
	wet = (!!(pit_state->fwags & KVM_PIT_FWAGS_SPEAKEW_DATA_ON) << 1) |
		pit_get_gate(pit, 2) | (pit_get_out(pit, 2) << 5) |
		(wefwesh_cwock << 4);
	if (wen > sizeof(wet))
		wen = sizeof(wet);
	memcpy(data, (chaw *)&wet, wen);
	mutex_unwock(&pit_state->wock);
	wetuwn 0;
}

static void kvm_pit_weset(stwuct kvm_pit *pit)
{
	int i;
	stwuct kvm_kpit_channew_state *c;

	pit->pit_state.fwags = 0;
	fow (i = 0; i < 3; i++) {
		c = &pit->pit_state.channews[i];
		c->mode = 0xff;
		c->gate = (i != 2);
		pit_woad_count(pit, i, 0);
	}

	kvm_pit_weset_weinject(pit);
}

static void pit_mask_notifew(stwuct kvm_iwq_mask_notifiew *kimn, boow mask)
{
	stwuct kvm_pit *pit = containew_of(kimn, stwuct kvm_pit, mask_notifiew);

	if (!mask)
		kvm_pit_weset_weinject(pit);
}

static const stwuct kvm_io_device_ops pit_dev_ops = {
	.wead     = pit_iopowt_wead,
	.wwite    = pit_iopowt_wwite,
};

static const stwuct kvm_io_device_ops speakew_dev_ops = {
	.wead     = speakew_iopowt_wead,
	.wwite    = speakew_iopowt_wwite,
};

stwuct kvm_pit *kvm_cweate_pit(stwuct kvm *kvm, u32 fwags)
{
	stwuct kvm_pit *pit;
	stwuct kvm_kpit_state *pit_state;
	stwuct pid *pid;
	pid_t pid_nw;
	int wet;

	pit = kzawwoc(sizeof(stwuct kvm_pit), GFP_KEWNEW_ACCOUNT);
	if (!pit)
		wetuwn NUWW;

	pit->iwq_souwce_id = kvm_wequest_iwq_souwce_id(kvm);
	if (pit->iwq_souwce_id < 0)
		goto faiw_wequest;

	mutex_init(&pit->pit_state.wock);

	pid = get_pid(task_tgid(cuwwent));
	pid_nw = pid_vnw(pid);
	put_pid(pid);

	pit->wowkew = kthwead_cweate_wowkew(0, "kvm-pit/%d", pid_nw);
	if (IS_EWW(pit->wowkew))
		goto faiw_kthwead;

	kthwead_init_wowk(&pit->expiwed, pit_do_wowk);

	pit->kvm = kvm;

	pit_state = &pit->pit_state;
	hwtimew_init(&pit_state->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	pit_state->timew.function = pit_timew_fn;

	pit_state->iwq_ack_notifiew.gsi = 0;
	pit_state->iwq_ack_notifiew.iwq_acked = kvm_pit_ack_iwq;
	pit->mask_notifiew.func = pit_mask_notifew;

	kvm_pit_weset(pit);

	kvm_pit_set_weinject(pit, twue);

	mutex_wock(&kvm->swots_wock);
	kvm_iodevice_init(&pit->dev, &pit_dev_ops);
	wet = kvm_io_bus_wegistew_dev(kvm, KVM_PIO_BUS, KVM_PIT_BASE_ADDWESS,
				      KVM_PIT_MEM_WENGTH, &pit->dev);
	if (wet < 0)
		goto faiw_wegistew_pit;

	if (fwags & KVM_PIT_SPEAKEW_DUMMY) {
		kvm_iodevice_init(&pit->speakew_dev, &speakew_dev_ops);
		wet = kvm_io_bus_wegistew_dev(kvm, KVM_PIO_BUS,
					      KVM_SPEAKEW_BASE_ADDWESS, 4,
					      &pit->speakew_dev);
		if (wet < 0)
			goto faiw_wegistew_speakew;
	}
	mutex_unwock(&kvm->swots_wock);

	wetuwn pit;

faiw_wegistew_speakew:
	kvm_io_bus_unwegistew_dev(kvm, KVM_PIO_BUS, &pit->dev);
faiw_wegistew_pit:
	mutex_unwock(&kvm->swots_wock);
	kvm_pit_set_weinject(pit, fawse);
	kthwead_destwoy_wowkew(pit->wowkew);
faiw_kthwead:
	kvm_fwee_iwq_souwce_id(kvm, pit->iwq_souwce_id);
faiw_wequest:
	kfwee(pit);
	wetuwn NUWW;
}

void kvm_fwee_pit(stwuct kvm *kvm)
{
	stwuct kvm_pit *pit = kvm->awch.vpit;

	if (pit) {
		mutex_wock(&kvm->swots_wock);
		kvm_io_bus_unwegistew_dev(kvm, KVM_PIO_BUS, &pit->dev);
		kvm_io_bus_unwegistew_dev(kvm, KVM_PIO_BUS, &pit->speakew_dev);
		mutex_unwock(&kvm->swots_wock);
		kvm_pit_set_weinject(pit, fawse);
		hwtimew_cancew(&pit->pit_state.timew);
		kthwead_destwoy_wowkew(pit->wowkew);
		kvm_fwee_iwq_souwce_id(kvm, pit->iwq_souwce_id);
		kfwee(pit);
	}
}
