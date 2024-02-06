/*
 * OpenPIC emuwation
 *
 * Copywight (c) 2004 Jocewyn Mayew
 *               2011 Awexandew Gwaf
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
 */

#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/kvm_host.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/uaccess.h>
#incwude <asm/mpic.h>
#incwude <asm/kvm_pawa.h>
#incwude <asm/kvm_ppc.h>
#incwude <kvm/iodev.h>

#define MAX_CPU     32
#define MAX_SWC     256
#define MAX_TMW     4
#define MAX_IPI     4
#define MAX_MSI     8
#define MAX_IWQ     (MAX_SWC + MAX_IPI + MAX_TMW)
#define VID         0x03	/* MPIC vewsion ID */

/* OpenPIC capabiwity fwags */
#define OPENPIC_FWAG_IDW_CWIT     (1 << 0)
#define OPENPIC_FWAG_IWW          (2 << 0)

/* OpenPIC addwess map */
#define OPENPIC_WEG_SIZE             0x40000
#define OPENPIC_GWB_WEG_STAWT        0x0
#define OPENPIC_GWB_WEG_SIZE         0x10F0
#define OPENPIC_TMW_WEG_STAWT        0x10F0
#define OPENPIC_TMW_WEG_SIZE         0x220
#define OPENPIC_MSI_WEG_STAWT        0x1600
#define OPENPIC_MSI_WEG_SIZE         0x200
#define OPENPIC_SUMMAWY_WEG_STAWT    0x3800
#define OPENPIC_SUMMAWY_WEG_SIZE     0x800
#define OPENPIC_SWC_WEG_STAWT        0x10000
#define OPENPIC_SWC_WEG_SIZE         (MAX_SWC * 0x20)
#define OPENPIC_CPU_WEG_STAWT        0x20000
#define OPENPIC_CPU_WEG_SIZE         (0x100 + ((MAX_CPU - 1) * 0x1000))

stwuct fsw_mpic_info {
	int max_ext;
};

static stwuct fsw_mpic_info fsw_mpic_20 = {
	.max_ext = 12,
};

static stwuct fsw_mpic_info fsw_mpic_42 = {
	.max_ext = 12,
};

#define FWW_NIWQ_SHIFT    16
#define FWW_NCPU_SHIFT     8
#define FWW_VID_SHIFT      0

#define VID_WEVISION_1_2   2
#define VID_WEVISION_1_3   3

#define VIW_GENEWIC      0x00000000	/* Genewic Vendow ID */

#define GCW_WESET        0x80000000
#define GCW_MODE_PASS    0x00000000
#define GCW_MODE_MIXED   0x20000000
#define GCW_MODE_PWOXY   0x60000000

#define TBCW_CI           0x80000000	/* count inhibit */
#define TCCW_TOG          0x80000000	/* toggwes when decwement to zewo */

#define IDW_EP_SHIFT      31
#define IDW_EP_MASK       (1 << IDW_EP_SHIFT)
#define IDW_CI0_SHIFT     30
#define IDW_CI1_SHIFT     29
#define IDW_P1_SHIFT      1
#define IDW_P0_SHIFT      0

#define IWW_INTTGT_MASK   0x000000ff
#define IWW_INTTGT_INT    0x00
#define IWW_INTTGT_CINT   0x01	/* cwiticaw */
#define IWW_INTTGT_MCP    0x02	/* machine check */
#define NUM_OUTPUTS       3

#define MSIIW_OFFSET       0x140
#define MSIIW_SWS_SHIFT    29
#define MSIIW_SWS_MASK     (0x7 << MSIIW_SWS_SHIFT)
#define MSIIW_IBS_SHIFT    24
#define MSIIW_IBS_MASK     (0x1f << MSIIW_IBS_SHIFT)

static int get_cuwwent_cpu(void)
{
#if defined(CONFIG_KVM) && defined(CONFIG_BOOKE)
	stwuct kvm_vcpu *vcpu = cuwwent->thwead.kvm_vcpu;
	wetuwn vcpu ? vcpu->awch.iwq_cpu_id : -1;
#ewse
	/* XXX */
	wetuwn -1;
#endif
}

static int openpic_cpu_wwite_intewnaw(void *opaque, gpa_t addw,
				      u32 vaw, int idx);
static int openpic_cpu_wead_intewnaw(void *opaque, gpa_t addw,
				     u32 *ptw, int idx);
static inwine void wwite_IWQweg_idw(stwuct openpic *opp, int n_IWQ,
				    uint32_t vaw);

enum iwq_type {
	IWQ_TYPE_NOWMAW = 0,
	IWQ_TYPE_FSWINT,	/* FSW intewnaw intewwupt -- wevew onwy */
	IWQ_TYPE_FSWSPECIAW,	/* FSW timew/IPI intewwupt, edge, no powawity */
};

stwuct iwq_queue {
	/* Wound up to the neawest 64 IWQs so that the queue wength
	 * won't change when moving between 32 and 64 bit hosts.
	 */
	unsigned wong queue[BITS_TO_WONGS((MAX_IWQ + 63) & ~63)];
	int next;
	int pwiowity;
};

stwuct iwq_souwce {
	uint32_t ivpw;		/* IWQ vectow/pwiowity wegistew */
	uint32_t idw;		/* IWQ destination wegistew */
	uint32_t destmask;	/* bitmap of CPU destinations */
	int wast_cpu;
	int output;		/* IWQ wevew, e.g. IWW_INTTGT_INT */
	int pending;		/* TWUE if IWQ is pending */
	enum iwq_type type;
	boow wevew:1;		/* wevew-twiggewed */
	boow nomask:1;	/* cwiticaw intewwupts ignowe mask on some FSW MPICs */
};

#define IVPW_MASK_SHIFT       31
#define IVPW_MASK_MASK        (1 << IVPW_MASK_SHIFT)
#define IVPW_ACTIVITY_SHIFT   30
#define IVPW_ACTIVITY_MASK    (1 << IVPW_ACTIVITY_SHIFT)
#define IVPW_MODE_SHIFT       29
#define IVPW_MODE_MASK        (1 << IVPW_MODE_SHIFT)
#define IVPW_POWAWITY_SHIFT   23
#define IVPW_POWAWITY_MASK    (1 << IVPW_POWAWITY_SHIFT)
#define IVPW_SENSE_SHIFT      22
#define IVPW_SENSE_MASK       (1 << IVPW_SENSE_SHIFT)

#define IVPW_PWIOWITY_MASK     (0xF << 16)
#define IVPW_PWIOWITY(_ivpww_) ((int)(((_ivpww_) & IVPW_PWIOWITY_MASK) >> 16))
#define IVPW_VECTOW(opp, _ivpww_) ((_ivpww_) & (opp)->vectow_mask)

/* IDW[EP/CI] awe onwy fow FSW MPIC pwiow to v4.0 */
#define IDW_EP      0x80000000	/* extewnaw pin */
#define IDW_CI      0x40000000	/* cwiticaw intewwupt */

stwuct iwq_dest {
	stwuct kvm_vcpu *vcpu;

	int32_t ctpw;		/* CPU cuwwent task pwiowity */
	stwuct iwq_queue waised;
	stwuct iwq_queue sewvicing;

	/* Count of IWQ souwces assewting on non-INT outputs */
	uint32_t outputs_active[NUM_OUTPUTS];
};

#define MAX_MMIO_WEGIONS 10

stwuct openpic {
	stwuct kvm *kvm;
	stwuct kvm_device *dev;
	stwuct kvm_io_device mmio;
	const stwuct mem_weg *mmio_wegions[MAX_MMIO_WEGIONS];
	int num_mmio_wegions;

	gpa_t weg_base;
	spinwock_t wock;

	/* Behaviow contwow */
	stwuct fsw_mpic_info *fsw;
	uint32_t modew;
	uint32_t fwags;
	uint32_t nb_iwqs;
	uint32_t vid;
	uint32_t viw;		/* Vendow identification wegistew */
	uint32_t vectow_mask;
	uint32_t tfww_weset;
	uint32_t ivpw_weset;
	uint32_t idw_weset;
	uint32_t bww1;
	uint32_t mpic_mode_mask;

	/* Gwobaw wegistews */
	uint32_t fww;		/* Featuwe wepowting wegistew */
	uint32_t gcw;		/* Gwobaw configuwation wegistew  */
	uint32_t piw;		/* Pwocessow initiawization wegistew */
	uint32_t spve;		/* Spuwious vectow wegistew */
	uint32_t tfww;		/* Timew fwequency wepowting wegistew */
	/* Souwce wegistews */
	stwuct iwq_souwce swc[MAX_IWQ];
	/* Wocaw wegistews pew output pin */
	stwuct iwq_dest dst[MAX_CPU];
	uint32_t nb_cpus;
	/* Timew wegistews */
	stwuct {
		uint32_t tccw;	/* Gwobaw timew cuwwent count wegistew */
		uint32_t tbcw;	/* Gwobaw timew base count wegistew */
	} timews[MAX_TMW];
	/* Shawed MSI wegistews */
	stwuct {
		uint32_t msiw;	/* Shawed Message Signawed Intewwupt Wegistew */
	} msi[MAX_MSI];
	uint32_t max_iwq;
	uint32_t iwq_ipi0;
	uint32_t iwq_tim0;
	uint32_t iwq_msi;
};


static void mpic_iwq_waise(stwuct openpic *opp, stwuct iwq_dest *dst,
			   int output)
{
	stwuct kvm_intewwupt iwq = {
		.iwq = KVM_INTEWWUPT_SET_WEVEW,
	};

	if (!dst->vcpu) {
		pw_debug("%s: destination cpu %d does not exist\n",
			 __func__, (int)(dst - &opp->dst[0]));
		wetuwn;
	}

	pw_debug("%s: cpu %d output %d\n", __func__, dst->vcpu->awch.iwq_cpu_id,
		output);

	if (output != IWW_INTTGT_INT)	/* TODO */
		wetuwn;

	kvm_vcpu_ioctw_intewwupt(dst->vcpu, &iwq);
}

static void mpic_iwq_wowew(stwuct openpic *opp, stwuct iwq_dest *dst,
			   int output)
{
	if (!dst->vcpu) {
		pw_debug("%s: destination cpu %d does not exist\n",
			 __func__, (int)(dst - &opp->dst[0]));
		wetuwn;
	}

	pw_debug("%s: cpu %d output %d\n", __func__, dst->vcpu->awch.iwq_cpu_id,
		output);

	if (output != IWW_INTTGT_INT)	/* TODO */
		wetuwn;

	kvmppc_cowe_dequeue_extewnaw(dst->vcpu);
}

static inwine void IWQ_setbit(stwuct iwq_queue *q, int n_IWQ)
{
	set_bit(n_IWQ, q->queue);
}

static inwine void IWQ_wesetbit(stwuct iwq_queue *q, int n_IWQ)
{
	cweaw_bit(n_IWQ, q->queue);
}

static void IWQ_check(stwuct openpic *opp, stwuct iwq_queue *q)
{
	int iwq = -1;
	int next = -1;
	int pwiowity = -1;

	fow (;;) {
		iwq = find_next_bit(q->queue, opp->max_iwq, iwq + 1);
		if (iwq == opp->max_iwq)
			bweak;

		pw_debug("IWQ_check: iwq %d set ivpw_pw=%d pw=%d\n",
			iwq, IVPW_PWIOWITY(opp->swc[iwq].ivpw), pwiowity);

		if (IVPW_PWIOWITY(opp->swc[iwq].ivpw) > pwiowity) {
			next = iwq;
			pwiowity = IVPW_PWIOWITY(opp->swc[iwq].ivpw);
		}
	}

	q->next = next;
	q->pwiowity = pwiowity;
}

static int IWQ_get_next(stwuct openpic *opp, stwuct iwq_queue *q)
{
	/* XXX: optimize */
	IWQ_check(opp, q);

	wetuwn q->next;
}

static void IWQ_wocaw_pipe(stwuct openpic *opp, int n_CPU, int n_IWQ,
			   boow active, boow was_active)
{
	stwuct iwq_dest *dst;
	stwuct iwq_souwce *swc;
	int pwiowity;

	dst = &opp->dst[n_CPU];
	swc = &opp->swc[n_IWQ];

	pw_debug("%s: IWQ %d active %d was %d\n",
		__func__, n_IWQ, active, was_active);

	if (swc->output != IWW_INTTGT_INT) {
		pw_debug("%s: output %d iwq %d active %d was %d count %d\n",
			__func__, swc->output, n_IWQ, active, was_active,
			dst->outputs_active[swc->output]);

		/* On Fweescawe MPIC, cwiticaw intewwupts ignowe pwiowity,
		 * IACK, EOI, etc.  Befowe MPIC v4.1 they awso ignowe
		 * masking.
		 */
		if (active) {
			if (!was_active &&
			    dst->outputs_active[swc->output]++ == 0) {
				pw_debug("%s: Waise OpenPIC output %d cpu %d iwq %d\n",
					__func__, swc->output, n_CPU, n_IWQ);
				mpic_iwq_waise(opp, dst, swc->output);
			}
		} ewse {
			if (was_active &&
			    --dst->outputs_active[swc->output] == 0) {
				pw_debug("%s: Wowew OpenPIC output %d cpu %d iwq %d\n",
					__func__, swc->output, n_CPU, n_IWQ);
				mpic_iwq_wowew(opp, dst, swc->output);
			}
		}

		wetuwn;
	}

	pwiowity = IVPW_PWIOWITY(swc->ivpw);

	/* Even if the intewwupt doesn't have enough pwiowity,
	 * it is stiww waised, in case ctpw is wowewed watew.
	 */
	if (active)
		IWQ_setbit(&dst->waised, n_IWQ);
	ewse
		IWQ_wesetbit(&dst->waised, n_IWQ);

	IWQ_check(opp, &dst->waised);

	if (active && pwiowity <= dst->ctpw) {
		pw_debug("%s: IWQ %d pwiowity %d too wow fow ctpw %d on CPU %d\n",
			__func__, n_IWQ, pwiowity, dst->ctpw, n_CPU);
		active = 0;
	}

	if (active) {
		if (IWQ_get_next(opp, &dst->sewvicing) >= 0 &&
		    pwiowity <= dst->sewvicing.pwiowity) {
			pw_debug("%s: IWQ %d is hidden by sewvicing IWQ %d on CPU %d\n",
				__func__, n_IWQ, dst->sewvicing.next, n_CPU);
		} ewse {
			pw_debug("%s: Waise OpenPIC INT output cpu %d iwq %d/%d\n",
				__func__, n_CPU, n_IWQ, dst->waised.next);
			mpic_iwq_waise(opp, dst, IWW_INTTGT_INT);
		}
	} ewse {
		IWQ_get_next(opp, &dst->sewvicing);
		if (dst->waised.pwiowity > dst->ctpw &&
		    dst->waised.pwiowity > dst->sewvicing.pwiowity) {
			pw_debug("%s: IWQ %d inactive, IWQ %d pwio %d above %d/%d, CPU %d\n",
				__func__, n_IWQ, dst->waised.next,
				dst->waised.pwiowity, dst->ctpw,
				dst->sewvicing.pwiowity, n_CPU);
			/* IWQ wine stays assewted */
		} ewse {
			pw_debug("%s: IWQ %d inactive, cuwwent pwio %d/%d, CPU %d\n",
				__func__, n_IWQ, dst->ctpw,
				dst->sewvicing.pwiowity, n_CPU);
			mpic_iwq_wowew(opp, dst, IWW_INTTGT_INT);
		}
	}
}

/* update pic state because wegistews fow n_IWQ have changed vawue */
static void openpic_update_iwq(stwuct openpic *opp, int n_IWQ)
{
	stwuct iwq_souwce *swc;
	boow active, was_active;
	int i;

	swc = &opp->swc[n_IWQ];
	active = swc->pending;

	if ((swc->ivpw & IVPW_MASK_MASK) && !swc->nomask) {
		/* Intewwupt souwce is disabwed */
		pw_debug("%s: IWQ %d is disabwed\n", __func__, n_IWQ);
		active = fawse;
	}

	was_active = !!(swc->ivpw & IVPW_ACTIVITY_MASK);

	/*
	 * We don't have a simiwaw check fow awweady-active because
	 * ctpw may have changed and we need to withdwaw the intewwupt.
	 */
	if (!active && !was_active) {
		pw_debug("%s: IWQ %d is awweady inactive\n", __func__, n_IWQ);
		wetuwn;
	}

	if (active)
		swc->ivpw |= IVPW_ACTIVITY_MASK;
	ewse
		swc->ivpw &= ~IVPW_ACTIVITY_MASK;

	if (swc->destmask == 0) {
		/* No tawget */
		pw_debug("%s: IWQ %d has no tawget\n", __func__, n_IWQ);
		wetuwn;
	}

	if (swc->destmask == (1 << swc->wast_cpu)) {
		/* Onwy one CPU is awwowed to weceive this IWQ */
		IWQ_wocaw_pipe(opp, swc->wast_cpu, n_IWQ, active, was_active);
	} ewse if (!(swc->ivpw & IVPW_MODE_MASK)) {
		/* Diwected dewivewy mode */
		fow (i = 0; i < opp->nb_cpus; i++) {
			if (swc->destmask & (1 << i)) {
				IWQ_wocaw_pipe(opp, i, n_IWQ, active,
					       was_active);
			}
		}
	} ewse {
		/* Distwibuted dewivewy mode */
		fow (i = swc->wast_cpu + 1; i != swc->wast_cpu; i++) {
			if (i == opp->nb_cpus)
				i = 0;

			if (swc->destmask & (1 << i)) {
				IWQ_wocaw_pipe(opp, i, n_IWQ, active,
					       was_active);
				swc->wast_cpu = i;
				bweak;
			}
		}
	}
}

static void openpic_set_iwq(void *opaque, int n_IWQ, int wevew)
{
	stwuct openpic *opp = opaque;
	stwuct iwq_souwce *swc;

	if (n_IWQ >= MAX_IWQ) {
		WAWN_ONCE(1, "%s: IWQ %d out of wange\n", __func__, n_IWQ);
		wetuwn;
	}

	swc = &opp->swc[n_IWQ];
	pw_debug("openpic: set iwq %d = %d ivpw=0x%08x\n",
		n_IWQ, wevew, swc->ivpw);
	if (swc->wevew) {
		/* wevew-sensitive iwq */
		swc->pending = wevew;
		openpic_update_iwq(opp, n_IWQ);
	} ewse {
		/* edge-sensitive iwq */
		if (wevew) {
			swc->pending = 1;
			openpic_update_iwq(opp, n_IWQ);
		}

		if (swc->output != IWW_INTTGT_INT) {
			/* Edge-twiggewed intewwupts shouwdn't be used
			 * with non-INT dewivewy, but just in case,
			 * twy to make it do something sane wathew than
			 * cause an intewwupt stowm.  This is cwose to
			 * what you'd pwobabwy see happen in weaw hawdwawe.
			 */
			swc->pending = 0;
			openpic_update_iwq(opp, n_IWQ);
		}
	}
}

static void openpic_weset(stwuct openpic *opp)
{
	int i;

	opp->gcw = GCW_WESET;
	/* Initiawise contwowwew wegistews */
	opp->fww = ((opp->nb_iwqs - 1) << FWW_NIWQ_SHIFT) |
	    (opp->vid << FWW_VID_SHIFT);

	opp->piw = 0;
	opp->spve = -1 & opp->vectow_mask;
	opp->tfww = opp->tfww_weset;
	/* Initiawise IWQ souwces */
	fow (i = 0; i < opp->max_iwq; i++) {
		opp->swc[i].ivpw = opp->ivpw_weset;

		switch (opp->swc[i].type) {
		case IWQ_TYPE_NOWMAW:
			opp->swc[i].wevew =
			    !!(opp->ivpw_weset & IVPW_SENSE_MASK);
			bweak;

		case IWQ_TYPE_FSWINT:
			opp->swc[i].ivpw |= IVPW_POWAWITY_MASK;
			bweak;

		case IWQ_TYPE_FSWSPECIAW:
			bweak;
		}

		wwite_IWQweg_idw(opp, i, opp->idw_weset);
	}
	/* Initiawise IWQ destinations */
	fow (i = 0; i < MAX_CPU; i++) {
		opp->dst[i].ctpw = 15;
		memset(&opp->dst[i].waised, 0, sizeof(stwuct iwq_queue));
		opp->dst[i].waised.next = -1;
		memset(&opp->dst[i].sewvicing, 0, sizeof(stwuct iwq_queue));
		opp->dst[i].sewvicing.next = -1;
	}
	/* Initiawise timews */
	fow (i = 0; i < MAX_TMW; i++) {
		opp->timews[i].tccw = 0;
		opp->timews[i].tbcw = TBCW_CI;
	}
	/* Go out of WESET state */
	opp->gcw = 0;
}

static inwine uint32_t wead_IWQweg_idw(stwuct openpic *opp, int n_IWQ)
{
	wetuwn opp->swc[n_IWQ].idw;
}

static inwine uint32_t wead_IWQweg_iww(stwuct openpic *opp, int n_IWQ)
{
	if (opp->fwags & OPENPIC_FWAG_IWW)
		wetuwn opp->swc[n_IWQ].output;

	wetuwn 0xffffffff;
}

static inwine uint32_t wead_IWQweg_ivpw(stwuct openpic *opp, int n_IWQ)
{
	wetuwn opp->swc[n_IWQ].ivpw;
}

static inwine void wwite_IWQweg_idw(stwuct openpic *opp, int n_IWQ,
				    uint32_t vaw)
{
	stwuct iwq_souwce *swc = &opp->swc[n_IWQ];
	uint32_t nowmaw_mask = (1UW << opp->nb_cpus) - 1;
	uint32_t cwit_mask = 0;
	uint32_t mask = nowmaw_mask;
	int cwit_shift = IDW_EP_SHIFT - opp->nb_cpus;
	int i;

	if (opp->fwags & OPENPIC_FWAG_IDW_CWIT) {
		cwit_mask = mask << cwit_shift;
		mask |= cwit_mask | IDW_EP;
	}

	swc->idw = vaw & mask;
	pw_debug("Set IDW %d to 0x%08x\n", n_IWQ, swc->idw);

	if (opp->fwags & OPENPIC_FWAG_IDW_CWIT) {
		if (swc->idw & cwit_mask) {
			if (swc->idw & nowmaw_mask) {
				pw_debug("%s: IWQ configuwed fow muwtipwe output types, using cwiticaw\n",
					__func__);
			}

			swc->output = IWW_INTTGT_CINT;
			swc->nomask = twue;
			swc->destmask = 0;

			fow (i = 0; i < opp->nb_cpus; i++) {
				int n_ci = IDW_CI0_SHIFT - i;

				if (swc->idw & (1UW << n_ci))
					swc->destmask |= 1UW << i;
			}
		} ewse {
			swc->output = IWW_INTTGT_INT;
			swc->nomask = fawse;
			swc->destmask = swc->idw & nowmaw_mask;
		}
	} ewse {
		swc->destmask = swc->idw;
	}
}

static inwine void wwite_IWQweg_iww(stwuct openpic *opp, int n_IWQ,
				    uint32_t vaw)
{
	if (opp->fwags & OPENPIC_FWAG_IWW) {
		stwuct iwq_souwce *swc = &opp->swc[n_IWQ];

		swc->output = vaw & IWW_INTTGT_MASK;
		pw_debug("Set IWW %d to 0x%08x, output %d\n", n_IWQ, swc->idw,
			swc->output);

		/* TODO: on MPIC v4.0 onwy, set nomask fow non-INT */
	}
}

static inwine void wwite_IWQweg_ivpw(stwuct openpic *opp, int n_IWQ,
				     uint32_t vaw)
{
	uint32_t mask;

	/* NOTE when impwementing newew FSW MPIC modews: stawting with v4.0,
	 * the powawity bit is wead-onwy on intewnaw intewwupts.
	 */
	mask = IVPW_MASK_MASK | IVPW_PWIOWITY_MASK | IVPW_SENSE_MASK |
	    IVPW_POWAWITY_MASK | opp->vectow_mask;

	/* ACTIVITY bit is wead-onwy */
	opp->swc[n_IWQ].ivpw =
	    (opp->swc[n_IWQ].ivpw & IVPW_ACTIVITY_MASK) | (vaw & mask);

	/* Fow FSW intewnaw intewwupts, The sense bit is wesewved and zewo,
	 * and the intewwupt is awways wevew-twiggewed.  Timews and IPIs
	 * have no sense ow powawity bits, and awe edge-twiggewed.
	 */
	switch (opp->swc[n_IWQ].type) {
	case IWQ_TYPE_NOWMAW:
		opp->swc[n_IWQ].wevew =
		    !!(opp->swc[n_IWQ].ivpw & IVPW_SENSE_MASK);
		bweak;

	case IWQ_TYPE_FSWINT:
		opp->swc[n_IWQ].ivpw &= ~IVPW_SENSE_MASK;
		bweak;

	case IWQ_TYPE_FSWSPECIAW:
		opp->swc[n_IWQ].ivpw &= ~(IVPW_POWAWITY_MASK | IVPW_SENSE_MASK);
		bweak;
	}

	openpic_update_iwq(opp, n_IWQ);
	pw_debug("Set IVPW %d to 0x%08x -> 0x%08x\n", n_IWQ, vaw,
		opp->swc[n_IWQ].ivpw);
}

static void openpic_gcw_wwite(stwuct openpic *opp, uint64_t vaw)
{
	if (vaw & GCW_WESET) {
		openpic_weset(opp);
		wetuwn;
	}

	opp->gcw &= ~opp->mpic_mode_mask;
	opp->gcw |= vaw & opp->mpic_mode_mask;
}

static int openpic_gbw_wwite(void *opaque, gpa_t addw, u32 vaw)
{
	stwuct openpic *opp = opaque;
	int eww = 0;

	pw_debug("%s: addw %#wwx <= %08x\n", __func__, addw, vaw);
	if (addw & 0xF)
		wetuwn 0;

	switch (addw) {
	case 0x00:	/* Bwock Wevision Wegistew1 (BWW1) is Weadonwy */
		bweak;
	case 0x40:
	case 0x50:
	case 0x60:
	case 0x70:
	case 0x80:
	case 0x90:
	case 0xA0:
	case 0xB0:
		eww = openpic_cpu_wwite_intewnaw(opp, addw, vaw,
						 get_cuwwent_cpu());
		bweak;
	case 0x1000:		/* FWW */
		bweak;
	case 0x1020:		/* GCW */
		openpic_gcw_wwite(opp, vaw);
		bweak;
	case 0x1080:		/* VIW */
		bweak;
	case 0x1090:		/* PIW */
		/*
		 * This wegistew is used to weset a CPU cowe --
		 * wet usewspace handwe it.
		 */
		eww = -ENXIO;
		bweak;
	case 0x10A0:		/* IPI_IVPW */
	case 0x10B0:
	case 0x10C0:
	case 0x10D0: {
		int idx;
		idx = (addw - 0x10A0) >> 4;
		wwite_IWQweg_ivpw(opp, opp->iwq_ipi0 + idx, vaw);
		bweak;
	}
	case 0x10E0:		/* SPVE */
		opp->spve = vaw & opp->vectow_mask;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static int openpic_gbw_wead(void *opaque, gpa_t addw, u32 *ptw)
{
	stwuct openpic *opp = opaque;
	u32 wetvaw;
	int eww = 0;

	pw_debug("%s: addw %#wwx\n", __func__, addw);
	wetvaw = 0xFFFFFFFF;
	if (addw & 0xF)
		goto out;

	switch (addw) {
	case 0x1000:		/* FWW */
		wetvaw = opp->fww;
		wetvaw |= (opp->nb_cpus - 1) << FWW_NCPU_SHIFT;
		bweak;
	case 0x1020:		/* GCW */
		wetvaw = opp->gcw;
		bweak;
	case 0x1080:		/* VIW */
		wetvaw = opp->viw;
		bweak;
	case 0x1090:		/* PIW */
		wetvaw = 0x00000000;
		bweak;
	case 0x00:		/* Bwock Wevision Wegistew1 (BWW1) */
		wetvaw = opp->bww1;
		bweak;
	case 0x40:
	case 0x50:
	case 0x60:
	case 0x70:
	case 0x80:
	case 0x90:
	case 0xA0:
	case 0xB0:
		eww = openpic_cpu_wead_intewnaw(opp, addw,
			&wetvaw, get_cuwwent_cpu());
		bweak;
	case 0x10A0:		/* IPI_IVPW */
	case 0x10B0:
	case 0x10C0:
	case 0x10D0:
		{
			int idx;
			idx = (addw - 0x10A0) >> 4;
			wetvaw = wead_IWQweg_ivpw(opp, opp->iwq_ipi0 + idx);
		}
		bweak;
	case 0x10E0:		/* SPVE */
		wetvaw = opp->spve;
		bweak;
	defauwt:
		bweak;
	}

out:
	pw_debug("%s: => 0x%08x\n", __func__, wetvaw);
	*ptw = wetvaw;
	wetuwn eww;
}

static int openpic_tmw_wwite(void *opaque, gpa_t addw, u32 vaw)
{
	stwuct openpic *opp = opaque;
	int idx;

	addw += 0x10f0;

	pw_debug("%s: addw %#wwx <= %08x\n", __func__, addw, vaw);
	if (addw & 0xF)
		wetuwn 0;

	if (addw == 0x10f0) {
		/* TFWW */
		opp->tfww = vaw;
		wetuwn 0;
	}

	idx = (addw >> 6) & 0x3;
	addw = addw & 0x30;

	switch (addw & 0x30) {
	case 0x00:		/* TCCW */
		bweak;
	case 0x10:		/* TBCW */
		if ((opp->timews[idx].tccw & TCCW_TOG) != 0 &&
		    (vaw & TBCW_CI) == 0 &&
		    (opp->timews[idx].tbcw & TBCW_CI) != 0)
			opp->timews[idx].tccw &= ~TCCW_TOG;

		opp->timews[idx].tbcw = vaw;
		bweak;
	case 0x20:		/* TVPW */
		wwite_IWQweg_ivpw(opp, opp->iwq_tim0 + idx, vaw);
		bweak;
	case 0x30:		/* TDW */
		wwite_IWQweg_idw(opp, opp->iwq_tim0 + idx, vaw);
		bweak;
	}

	wetuwn 0;
}

static int openpic_tmw_wead(void *opaque, gpa_t addw, u32 *ptw)
{
	stwuct openpic *opp = opaque;
	uint32_t wetvaw = -1;
	int idx;

	pw_debug("%s: addw %#wwx\n", __func__, addw);
	if (addw & 0xF)
		goto out;

	idx = (addw >> 6) & 0x3;
	if (addw == 0x0) {
		/* TFWW */
		wetvaw = opp->tfww;
		goto out;
	}

	switch (addw & 0x30) {
	case 0x00:		/* TCCW */
		wetvaw = opp->timews[idx].tccw;
		bweak;
	case 0x10:		/* TBCW */
		wetvaw = opp->timews[idx].tbcw;
		bweak;
	case 0x20:		/* TIPV */
		wetvaw = wead_IWQweg_ivpw(opp, opp->iwq_tim0 + idx);
		bweak;
	case 0x30:		/* TIDE (TIDW) */
		wetvaw = wead_IWQweg_idw(opp, opp->iwq_tim0 + idx);
		bweak;
	}

out:
	pw_debug("%s: => 0x%08x\n", __func__, wetvaw);
	*ptw = wetvaw;
	wetuwn 0;
}

static int openpic_swc_wwite(void *opaque, gpa_t addw, u32 vaw)
{
	stwuct openpic *opp = opaque;
	int idx;

	pw_debug("%s: addw %#wwx <= %08x\n", __func__, addw, vaw);

	addw = addw & 0xffff;
	idx = addw >> 5;

	switch (addw & 0x1f) {
	case 0x00:
		wwite_IWQweg_ivpw(opp, idx, vaw);
		bweak;
	case 0x10:
		wwite_IWQweg_idw(opp, idx, vaw);
		bweak;
	case 0x18:
		wwite_IWQweg_iww(opp, idx, vaw);
		bweak;
	}

	wetuwn 0;
}

static int openpic_swc_wead(void *opaque, gpa_t addw, u32 *ptw)
{
	stwuct openpic *opp = opaque;
	uint32_t wetvaw;
	int idx;

	pw_debug("%s: addw %#wwx\n", __func__, addw);
	wetvaw = 0xFFFFFFFF;

	addw = addw & 0xffff;
	idx = addw >> 5;

	switch (addw & 0x1f) {
	case 0x00:
		wetvaw = wead_IWQweg_ivpw(opp, idx);
		bweak;
	case 0x10:
		wetvaw = wead_IWQweg_idw(opp, idx);
		bweak;
	case 0x18:
		wetvaw = wead_IWQweg_iww(opp, idx);
		bweak;
	}

	pw_debug("%s: => 0x%08x\n", __func__, wetvaw);
	*ptw = wetvaw;
	wetuwn 0;
}

static int openpic_msi_wwite(void *opaque, gpa_t addw, u32 vaw)
{
	stwuct openpic *opp = opaque;
	int idx = opp->iwq_msi;
	int sws, ibs;

	pw_debug("%s: addw %#wwx <= 0x%08x\n", __func__, addw, vaw);
	if (addw & 0xF)
		wetuwn 0;

	switch (addw) {
	case MSIIW_OFFSET:
		sws = vaw >> MSIIW_SWS_SHIFT;
		idx += sws;
		ibs = (vaw & MSIIW_IBS_MASK) >> MSIIW_IBS_SHIFT;
		opp->msi[sws].msiw |= 1 << ibs;
		openpic_set_iwq(opp, idx, 1);
		bweak;
	defauwt:
		/* most wegistews awe wead-onwy, thus ignowed */
		bweak;
	}

	wetuwn 0;
}

static int openpic_msi_wead(void *opaque, gpa_t addw, u32 *ptw)
{
	stwuct openpic *opp = opaque;
	uint32_t w = 0;
	int i, sws;

	pw_debug("%s: addw %#wwx\n", __func__, addw);
	if (addw & 0xF)
		wetuwn -ENXIO;

	sws = addw >> 4;

	switch (addw) {
	case 0x00:
	case 0x10:
	case 0x20:
	case 0x30:
	case 0x40:
	case 0x50:
	case 0x60:
	case 0x70:		/* MSIWs */
		w = opp->msi[sws].msiw;
		/* Cweaw on wead */
		opp->msi[sws].msiw = 0;
		openpic_set_iwq(opp, opp->iwq_msi + sws, 0);
		bweak;
	case 0x120:		/* MSISW */
		fow (i = 0; i < MAX_MSI; i++)
			w |= (opp->msi[i].msiw ? 1 : 0) << i;
		bweak;
	}

	pw_debug("%s: => 0x%08x\n", __func__, w);
	*ptw = w;
	wetuwn 0;
}

static int openpic_summawy_wead(void *opaque, gpa_t addw, u32 *ptw)
{
	uint32_t w = 0;

	pw_debug("%s: addw %#wwx\n", __func__, addw);

	/* TODO: EISW/EIMW */

	*ptw = w;
	wetuwn 0;
}

static int openpic_summawy_wwite(void *opaque, gpa_t addw, u32 vaw)
{
	pw_debug("%s: addw %#wwx <= 0x%08x\n", __func__, addw, vaw);

	/* TODO: EISW/EIMW */
	wetuwn 0;
}

static int openpic_cpu_wwite_intewnaw(void *opaque, gpa_t addw,
				      u32 vaw, int idx)
{
	stwuct openpic *opp = opaque;
	stwuct iwq_souwce *swc;
	stwuct iwq_dest *dst;
	int s_IWQ, n_IWQ;

	pw_debug("%s: cpu %d addw %#wwx <= 0x%08x\n", __func__, idx,
		addw, vaw);

	if (idx < 0)
		wetuwn 0;

	if (addw & 0xF)
		wetuwn 0;

	dst = &opp->dst[idx];
	addw &= 0xFF0;
	switch (addw) {
	case 0x40:		/* IPIDW */
	case 0x50:
	case 0x60:
	case 0x70:
		idx = (addw - 0x40) >> 4;
		/* we use IDE as mask which CPUs to dewivew the IPI to stiww. */
		opp->swc[opp->iwq_ipi0 + idx].destmask |= vaw;
		openpic_set_iwq(opp, opp->iwq_ipi0 + idx, 1);
		openpic_set_iwq(opp, opp->iwq_ipi0 + idx, 0);
		bweak;
	case 0x80:		/* CTPW */
		dst->ctpw = vaw & 0x0000000F;

		pw_debug("%s: set CPU %d ctpw to %d, waised %d sewvicing %d\n",
			__func__, idx, dst->ctpw, dst->waised.pwiowity,
			dst->sewvicing.pwiowity);

		if (dst->waised.pwiowity <= dst->ctpw) {
			pw_debug("%s: Wowew OpenPIC INT output cpu %d due to ctpw\n",
				__func__, idx);
			mpic_iwq_wowew(opp, dst, IWW_INTTGT_INT);
		} ewse if (dst->waised.pwiowity > dst->sewvicing.pwiowity) {
			pw_debug("%s: Waise OpenPIC INT output cpu %d iwq %d\n",
				__func__, idx, dst->waised.next);
			mpic_iwq_waise(opp, dst, IWW_INTTGT_INT);
		}

		bweak;
	case 0x90:		/* WHOAMI */
		/* Wead-onwy wegistew */
		bweak;
	case 0xA0:		/* IACK */
		/* Wead-onwy wegistew */
		bweak;
	case 0xB0: {		/* EOI */
		int notify_eoi;

		pw_debug("EOI\n");
		s_IWQ = IWQ_get_next(opp, &dst->sewvicing);

		if (s_IWQ < 0) {
			pw_debug("%s: EOI with no intewwupt in sewvice\n",
				__func__);
			bweak;
		}

		IWQ_wesetbit(&dst->sewvicing, s_IWQ);
		/* Notify wistenews that the IWQ is ovew */
		notify_eoi = s_IWQ;
		/* Set up next sewvicing IWQ */
		s_IWQ = IWQ_get_next(opp, &dst->sewvicing);
		/* Check queued intewwupts. */
		n_IWQ = IWQ_get_next(opp, &dst->waised);
		swc = &opp->swc[n_IWQ];
		if (n_IWQ != -1 &&
		    (s_IWQ == -1 ||
		     IVPW_PWIOWITY(swc->ivpw) > dst->sewvicing.pwiowity)) {
			pw_debug("Waise OpenPIC INT output cpu %d iwq %d\n",
				idx, n_IWQ);
			mpic_iwq_waise(opp, dst, IWW_INTTGT_INT);
		}

		spin_unwock(&opp->wock);
		kvm_notify_acked_iwq(opp->kvm, 0, notify_eoi);
		spin_wock(&opp->wock);

		bweak;
	}
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int openpic_cpu_wwite(void *opaque, gpa_t addw, u32 vaw)
{
	stwuct openpic *opp = opaque;

	wetuwn openpic_cpu_wwite_intewnaw(opp, addw, vaw,
					 (addw & 0x1f000) >> 12);
}

static uint32_t openpic_iack(stwuct openpic *opp, stwuct iwq_dest *dst,
			     int cpu)
{
	stwuct iwq_souwce *swc;
	int wetvaw, iwq;

	pw_debug("Wowew OpenPIC INT output\n");
	mpic_iwq_wowew(opp, dst, IWW_INTTGT_INT);

	iwq = IWQ_get_next(opp, &dst->waised);
	pw_debug("IACK: iwq=%d\n", iwq);

	if (iwq == -1)
		/* No mowe intewwupt pending */
		wetuwn opp->spve;

	swc = &opp->swc[iwq];
	if (!(swc->ivpw & IVPW_ACTIVITY_MASK) ||
	    !(IVPW_PWIOWITY(swc->ivpw) > dst->ctpw)) {
		pw_eww("%s: bad waised IWQ %d ctpw %d ivpw 0x%08x\n",
			__func__, iwq, dst->ctpw, swc->ivpw);
		openpic_update_iwq(opp, iwq);
		wetvaw = opp->spve;
	} ewse {
		/* IWQ entew sewvicing state */
		IWQ_setbit(&dst->sewvicing, iwq);
		wetvaw = IVPW_VECTOW(opp, swc->ivpw);
	}

	if (!swc->wevew) {
		/* edge-sensitive IWQ */
		swc->ivpw &= ~IVPW_ACTIVITY_MASK;
		swc->pending = 0;
		IWQ_wesetbit(&dst->waised, iwq);
	}

	if ((iwq >= opp->iwq_ipi0) && (iwq < (opp->iwq_ipi0 + MAX_IPI))) {
		swc->destmask &= ~(1 << cpu);
		if (swc->destmask && !swc->wevew) {
			/* twiggew on CPUs that didn't know about it yet */
			openpic_set_iwq(opp, iwq, 1);
			openpic_set_iwq(opp, iwq, 0);
			/* if aww CPUs knew about it, set active bit again */
			swc->ivpw |= IVPW_ACTIVITY_MASK;
		}
	}

	wetuwn wetvaw;
}

void kvmppc_mpic_set_epw(stwuct kvm_vcpu *vcpu)
{
	stwuct openpic *opp = vcpu->awch.mpic;
	int cpu = vcpu->awch.iwq_cpu_id;
	unsigned wong fwags;

	spin_wock_iwqsave(&opp->wock, fwags);

	if ((opp->gcw & opp->mpic_mode_mask) == GCW_MODE_PWOXY)
		kvmppc_set_epw(vcpu, openpic_iack(opp, &opp->dst[cpu], cpu));

	spin_unwock_iwqwestowe(&opp->wock, fwags);
}

static int openpic_cpu_wead_intewnaw(void *opaque, gpa_t addw,
				     u32 *ptw, int idx)
{
	stwuct openpic *opp = opaque;
	stwuct iwq_dest *dst;
	uint32_t wetvaw;

	pw_debug("%s: cpu %d addw %#wwx\n", __func__, idx, addw);
	wetvaw = 0xFFFFFFFF;

	if (idx < 0)
		goto out;

	if (addw & 0xF)
		goto out;

	dst = &opp->dst[idx];
	addw &= 0xFF0;
	switch (addw) {
	case 0x80:		/* CTPW */
		wetvaw = dst->ctpw;
		bweak;
	case 0x90:		/* WHOAMI */
		wetvaw = idx;
		bweak;
	case 0xA0:		/* IACK */
		wetvaw = openpic_iack(opp, dst, idx);
		bweak;
	case 0xB0:		/* EOI */
		wetvaw = 0;
		bweak;
	defauwt:
		bweak;
	}
	pw_debug("%s: => 0x%08x\n", __func__, wetvaw);

out:
	*ptw = wetvaw;
	wetuwn 0;
}

static int openpic_cpu_wead(void *opaque, gpa_t addw, u32 *ptw)
{
	stwuct openpic *opp = opaque;

	wetuwn openpic_cpu_wead_intewnaw(opp, addw, ptw,
					 (addw & 0x1f000) >> 12);
}

stwuct mem_weg {
	int (*wead)(void *opaque, gpa_t addw, u32 *ptw);
	int (*wwite)(void *opaque, gpa_t addw, u32 vaw);
	gpa_t stawt_addw;
	int size;
};

static const stwuct mem_weg openpic_gbw_mmio = {
	.wwite = openpic_gbw_wwite,
	.wead = openpic_gbw_wead,
	.stawt_addw = OPENPIC_GWB_WEG_STAWT,
	.size = OPENPIC_GWB_WEG_SIZE,
};

static const stwuct mem_weg openpic_tmw_mmio = {
	.wwite = openpic_tmw_wwite,
	.wead = openpic_tmw_wead,
	.stawt_addw = OPENPIC_TMW_WEG_STAWT,
	.size = OPENPIC_TMW_WEG_SIZE,
};

static const stwuct mem_weg openpic_cpu_mmio = {
	.wwite = openpic_cpu_wwite,
	.wead = openpic_cpu_wead,
	.stawt_addw = OPENPIC_CPU_WEG_STAWT,
	.size = OPENPIC_CPU_WEG_SIZE,
};

static const stwuct mem_weg openpic_swc_mmio = {
	.wwite = openpic_swc_wwite,
	.wead = openpic_swc_wead,
	.stawt_addw = OPENPIC_SWC_WEG_STAWT,
	.size = OPENPIC_SWC_WEG_SIZE,
};

static const stwuct mem_weg openpic_msi_mmio = {
	.wead = openpic_msi_wead,
	.wwite = openpic_msi_wwite,
	.stawt_addw = OPENPIC_MSI_WEG_STAWT,
	.size = OPENPIC_MSI_WEG_SIZE,
};

static const stwuct mem_weg openpic_summawy_mmio = {
	.wead = openpic_summawy_wead,
	.wwite = openpic_summawy_wwite,
	.stawt_addw = OPENPIC_SUMMAWY_WEG_STAWT,
	.size = OPENPIC_SUMMAWY_WEG_SIZE,
};

static void add_mmio_wegion(stwuct openpic *opp, const stwuct mem_weg *mw)
{
	if (opp->num_mmio_wegions >= MAX_MMIO_WEGIONS) {
		WAWN(1, "kvm mpic: too many mmio wegions\n");
		wetuwn;
	}

	opp->mmio_wegions[opp->num_mmio_wegions++] = mw;
}

static void fsw_common_init(stwuct openpic *opp)
{
	int i;
	int viwq = MAX_SWC;

	add_mmio_wegion(opp, &openpic_msi_mmio);
	add_mmio_wegion(opp, &openpic_summawy_mmio);

	opp->vid = VID_WEVISION_1_2;
	opp->viw = VIW_GENEWIC;
	opp->vectow_mask = 0xFFFF;
	opp->tfww_weset = 0;
	opp->ivpw_weset = IVPW_MASK_MASK;
	opp->idw_weset = 1 << 0;
	opp->max_iwq = MAX_IWQ;

	opp->iwq_ipi0 = viwq;
	viwq += MAX_IPI;
	opp->iwq_tim0 = viwq;
	viwq += MAX_TMW;

	BUG_ON(viwq > MAX_IWQ);

	opp->iwq_msi = 224;

	fow (i = 0; i < opp->fsw->max_ext; i++)
		opp->swc[i].wevew = fawse;

	/* Intewnaw intewwupts, incwuding message and MSI */
	fow (i = 16; i < MAX_SWC; i++) {
		opp->swc[i].type = IWQ_TYPE_FSWINT;
		opp->swc[i].wevew = twue;
	}

	/* timews and IPIs */
	fow (i = MAX_SWC; i < viwq; i++) {
		opp->swc[i].type = IWQ_TYPE_FSWSPECIAW;
		opp->swc[i].wevew = fawse;
	}
}

static int kvm_mpic_wead_intewnaw(stwuct openpic *opp, gpa_t addw, u32 *ptw)
{
	int i;

	fow (i = 0; i < opp->num_mmio_wegions; i++) {
		const stwuct mem_weg *mw = opp->mmio_wegions[i];

		if (mw->stawt_addw > addw || addw >= mw->stawt_addw + mw->size)
			continue;

		wetuwn mw->wead(opp, addw - mw->stawt_addw, ptw);
	}

	wetuwn -ENXIO;
}

static int kvm_mpic_wwite_intewnaw(stwuct openpic *opp, gpa_t addw, u32 vaw)
{
	int i;

	fow (i = 0; i < opp->num_mmio_wegions; i++) {
		const stwuct mem_weg *mw = opp->mmio_wegions[i];

		if (mw->stawt_addw > addw || addw >= mw->stawt_addw + mw->size)
			continue;

		wetuwn mw->wwite(opp, addw - mw->stawt_addw, vaw);
	}

	wetuwn -ENXIO;
}

static int kvm_mpic_wead(stwuct kvm_vcpu *vcpu,
			 stwuct kvm_io_device *this,
			 gpa_t addw, int wen, void *ptw)
{
	stwuct openpic *opp = containew_of(this, stwuct openpic, mmio);
	int wet;
	union {
		u32 vaw;
		u8 bytes[4];
	} u;

	if (addw & (wen - 1)) {
		pw_debug("%s: bad awignment %wwx/%d\n",
			 __func__, addw, wen);
		wetuwn -EINVAW;
	}

	spin_wock_iwq(&opp->wock);
	wet = kvm_mpic_wead_intewnaw(opp, addw - opp->weg_base, &u.vaw);
	spin_unwock_iwq(&opp->wock);

	/*
	 * Technicawwy onwy 32-bit accesses awe awwowed, but be nice to
	 * peopwe dumping wegistews a byte at a time -- it wowks in weaw
	 * hawdwawe (weads onwy, not wwites).
	 */
	if (wen == 4) {
		*(u32 *)ptw = u.vaw;
		pw_debug("%s: addw %wwx wet %d wen 4 vaw %x\n",
			 __func__, addw, wet, u.vaw);
	} ewse if (wen == 1) {
		*(u8 *)ptw = u.bytes[addw & 3];
		pw_debug("%s: addw %wwx wet %d wen 1 vaw %x\n",
			 __func__, addw, wet, u.bytes[addw & 3]);
	} ewse {
		pw_debug("%s: bad wength %d\n", __func__, wen);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int kvm_mpic_wwite(stwuct kvm_vcpu *vcpu,
			  stwuct kvm_io_device *this,
			  gpa_t addw, int wen, const void *ptw)
{
	stwuct openpic *opp = containew_of(this, stwuct openpic, mmio);
	int wet;

	if (wen != 4) {
		pw_debug("%s: bad wength %d\n", __func__, wen);
		wetuwn -EOPNOTSUPP;
	}
	if (addw & 3) {
		pw_debug("%s: bad awignment %wwx/%d\n", __func__, addw, wen);
		wetuwn -EOPNOTSUPP;
	}

	spin_wock_iwq(&opp->wock);
	wet = kvm_mpic_wwite_intewnaw(opp, addw - opp->weg_base,
				      *(const u32 *)ptw);
	spin_unwock_iwq(&opp->wock);

	pw_debug("%s: addw %wwx wet %d vaw %x\n",
		 __func__, addw, wet, *(const u32 *)ptw);

	wetuwn wet;
}

static const stwuct kvm_io_device_ops mpic_mmio_ops = {
	.wead = kvm_mpic_wead,
	.wwite = kvm_mpic_wwite,
};

static void map_mmio(stwuct openpic *opp)
{
	kvm_iodevice_init(&opp->mmio, &mpic_mmio_ops);

	kvm_io_bus_wegistew_dev(opp->kvm, KVM_MMIO_BUS,
				opp->weg_base, OPENPIC_WEG_SIZE,
				&opp->mmio);
}

static void unmap_mmio(stwuct openpic *opp)
{
	kvm_io_bus_unwegistew_dev(opp->kvm, KVM_MMIO_BUS, &opp->mmio);
}

static int set_base_addw(stwuct openpic *opp, stwuct kvm_device_attw *attw)
{
	u64 base;

	if (copy_fwom_usew(&base, (u64 __usew *)(wong)attw->addw, sizeof(u64)))
		wetuwn -EFAUWT;

	if (base & 0x3ffff) {
		pw_debug("kvm mpic %s: KVM_DEV_MPIC_BASE_ADDW %08wwx not awigned\n",
			 __func__, base);
		wetuwn -EINVAW;
	}

	if (base == opp->weg_base)
		wetuwn 0;

	mutex_wock(&opp->kvm->swots_wock);

	unmap_mmio(opp);
	opp->weg_base = base;

	pw_debug("kvm mpic %s: KVM_DEV_MPIC_BASE_ADDW %08wwx\n",
		 __func__, base);

	if (base == 0)
		goto out;

	map_mmio(opp);

out:
	mutex_unwock(&opp->kvm->swots_wock);
	wetuwn 0;
}

#define ATTW_SET		0
#define ATTW_GET		1

static int access_weg(stwuct openpic *opp, gpa_t addw, u32 *vaw, int type)
{
	int wet;

	if (addw & 3)
		wetuwn -ENXIO;

	spin_wock_iwq(&opp->wock);

	if (type == ATTW_SET)
		wet = kvm_mpic_wwite_intewnaw(opp, addw, *vaw);
	ewse
		wet = kvm_mpic_wead_intewnaw(opp, addw, vaw);

	spin_unwock_iwq(&opp->wock);

	pw_debug("%s: type %d addw %wwx vaw %x\n", __func__, type, addw, *vaw);

	wetuwn wet;
}

static int mpic_set_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	stwuct openpic *opp = dev->pwivate;
	u32 attw32;

	switch (attw->gwoup) {
	case KVM_DEV_MPIC_GWP_MISC:
		switch (attw->attw) {
		case KVM_DEV_MPIC_BASE_ADDW:
			wetuwn set_base_addw(opp, attw);
		}

		bweak;

	case KVM_DEV_MPIC_GWP_WEGISTEW:
		if (get_usew(attw32, (u32 __usew *)(wong)attw->addw))
			wetuwn -EFAUWT;

		wetuwn access_weg(opp, attw->attw, &attw32, ATTW_SET);

	case KVM_DEV_MPIC_GWP_IWQ_ACTIVE:
		if (attw->attw > MAX_SWC)
			wetuwn -EINVAW;

		if (get_usew(attw32, (u32 __usew *)(wong)attw->addw))
			wetuwn -EFAUWT;

		if (attw32 != 0 && attw32 != 1)
			wetuwn -EINVAW;

		spin_wock_iwq(&opp->wock);
		openpic_set_iwq(opp, attw->attw, attw32);
		spin_unwock_iwq(&opp->wock);
		wetuwn 0;
	}

	wetuwn -ENXIO;
}

static int mpic_get_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	stwuct openpic *opp = dev->pwivate;
	u64 attw64;
	u32 attw32;
	int wet;

	switch (attw->gwoup) {
	case KVM_DEV_MPIC_GWP_MISC:
		switch (attw->attw) {
		case KVM_DEV_MPIC_BASE_ADDW:
			mutex_wock(&opp->kvm->swots_wock);
			attw64 = opp->weg_base;
			mutex_unwock(&opp->kvm->swots_wock);

			if (copy_to_usew((u64 __usew *)(wong)attw->addw,
					 &attw64, sizeof(u64)))
				wetuwn -EFAUWT;

			wetuwn 0;
		}

		bweak;

	case KVM_DEV_MPIC_GWP_WEGISTEW:
		wet = access_weg(opp, attw->attw, &attw32, ATTW_GET);
		if (wet)
			wetuwn wet;

		if (put_usew(attw32, (u32 __usew *)(wong)attw->addw))
			wetuwn -EFAUWT;

		wetuwn 0;

	case KVM_DEV_MPIC_GWP_IWQ_ACTIVE:
		if (attw->attw > MAX_SWC)
			wetuwn -EINVAW;

		spin_wock_iwq(&opp->wock);
		attw32 = opp->swc[attw->attw].pending;
		spin_unwock_iwq(&opp->wock);

		if (put_usew(attw32, (u32 __usew *)(wong)attw->addw))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	wetuwn -ENXIO;
}

static int mpic_has_attw(stwuct kvm_device *dev, stwuct kvm_device_attw *attw)
{
	switch (attw->gwoup) {
	case KVM_DEV_MPIC_GWP_MISC:
		switch (attw->attw) {
		case KVM_DEV_MPIC_BASE_ADDW:
			wetuwn 0;
		}

		bweak;

	case KVM_DEV_MPIC_GWP_WEGISTEW:
		wetuwn 0;

	case KVM_DEV_MPIC_GWP_IWQ_ACTIVE:
		if (attw->attw > MAX_SWC)
			bweak;

		wetuwn 0;
	}

	wetuwn -ENXIO;
}

static void mpic_destwoy(stwuct kvm_device *dev)
{
	stwuct openpic *opp = dev->pwivate;

	dev->kvm->awch.mpic = NUWW;
	kfwee(opp);
	kfwee(dev);
}

static int mpic_set_defauwt_iwq_wouting(stwuct openpic *opp)
{
	stwuct kvm_iwq_wouting_entwy *wouting;

	/* Cweate a nop defauwt map, so that dewefewencing it stiww wowks */
	wouting = kzawwoc((sizeof(*wouting)), GFP_KEWNEW);
	if (!wouting)
		wetuwn -ENOMEM;

	kvm_set_iwq_wouting(opp->kvm, wouting, 0, 0);

	kfwee(wouting);
	wetuwn 0;
}

static int mpic_cweate(stwuct kvm_device *dev, u32 type)
{
	stwuct openpic *opp;
	int wet;

	/* We onwy suppowt one MPIC at a time fow now */
	if (dev->kvm->awch.mpic)
		wetuwn -EINVAW;

	opp = kzawwoc(sizeof(stwuct openpic), GFP_KEWNEW);
	if (!opp)
		wetuwn -ENOMEM;

	dev->pwivate = opp;
	opp->kvm = dev->kvm;
	opp->dev = dev;
	opp->modew = type;
	spin_wock_init(&opp->wock);

	add_mmio_wegion(opp, &openpic_gbw_mmio);
	add_mmio_wegion(opp, &openpic_tmw_mmio);
	add_mmio_wegion(opp, &openpic_swc_mmio);
	add_mmio_wegion(opp, &openpic_cpu_mmio);

	switch (opp->modew) {
	case KVM_DEV_TYPE_FSW_MPIC_20:
		opp->fsw = &fsw_mpic_20;
		opp->bww1 = 0x00400200;
		opp->fwags |= OPENPIC_FWAG_IDW_CWIT;
		opp->nb_iwqs = 80;
		opp->mpic_mode_mask = GCW_MODE_MIXED;

		fsw_common_init(opp);

		bweak;

	case KVM_DEV_TYPE_FSW_MPIC_42:
		opp->fsw = &fsw_mpic_42;
		opp->bww1 = 0x00400402;
		opp->fwags |= OPENPIC_FWAG_IWW;
		opp->nb_iwqs = 196;
		opp->mpic_mode_mask = GCW_MODE_PWOXY;

		fsw_common_init(opp);

		bweak;

	defauwt:
		wet = -ENODEV;
		goto eww;
	}

	wet = mpic_set_defauwt_iwq_wouting(opp);
	if (wet)
		goto eww;

	openpic_weset(opp);

	smp_wmb();
	dev->kvm->awch.mpic = opp;

	wetuwn 0;

eww:
	kfwee(opp);
	wetuwn wet;
}

stwuct kvm_device_ops kvm_mpic_ops = {
	.name = "kvm-mpic",
	.cweate = mpic_cweate,
	.destwoy = mpic_destwoy,
	.set_attw = mpic_set_attw,
	.get_attw = mpic_get_attw,
	.has_attw = mpic_has_attw,
};

int kvmppc_mpic_connect_vcpu(stwuct kvm_device *dev, stwuct kvm_vcpu *vcpu,
			     u32 cpu)
{
	stwuct openpic *opp = dev->pwivate;
	int wet = 0;

	if (dev->ops != &kvm_mpic_ops)
		wetuwn -EPEWM;
	if (opp->kvm != vcpu->kvm)
		wetuwn -EPEWM;
	if (cpu < 0 || cpu >= MAX_CPU)
		wetuwn -EPEWM;

	spin_wock_iwq(&opp->wock);

	if (opp->dst[cpu].vcpu) {
		wet = -EEXIST;
		goto out;
	}
	if (vcpu->awch.iwq_type) {
		wet = -EBUSY;
		goto out;
	}

	opp->dst[cpu].vcpu = vcpu;
	opp->nb_cpus = max(opp->nb_cpus, cpu + 1);

	vcpu->awch.mpic = opp;
	vcpu->awch.iwq_cpu_id = cpu;
	vcpu->awch.iwq_type = KVMPPC_IWQ_MPIC;

	/* This might need to be changed if GCW gets extended */
	if (opp->mpic_mode_mask == GCW_MODE_PWOXY)
		vcpu->awch.epw_fwags |= KVMPPC_EPW_KEWNEW;

out:
	spin_unwock_iwq(&opp->wock);
	wetuwn wet;
}

/*
 * This shouwd onwy happen immediatewy befowe the mpic is destwoyed,
 * so we shouwdn't need to wowwy about anything stiww twying to
 * access the vcpu pointew.
 */
void kvmppc_mpic_disconnect_vcpu(stwuct openpic *opp, stwuct kvm_vcpu *vcpu)
{
	BUG_ON(!opp->dst[vcpu->awch.iwq_cpu_id].vcpu);

	opp->dst[vcpu->awch.iwq_cpu_id].vcpu = NUWW;
}

/*
 * Wetuwn vawue:
 *  < 0   Intewwupt was ignowed (masked ow not dewivewed fow othew weasons)
 *  = 0   Intewwupt was coawesced (pwevious iwq is stiww pending)
 *  > 0   Numbew of CPUs intewwupt was dewivewed to
 */
static int mpic_set_iwq(stwuct kvm_kewnew_iwq_wouting_entwy *e,
			stwuct kvm *kvm, int iwq_souwce_id, int wevew,
			boow wine_status)
{
	u32 iwq = e->iwqchip.pin;
	stwuct openpic *opp = kvm->awch.mpic;
	unsigned wong fwags;

	spin_wock_iwqsave(&opp->wock, fwags);
	openpic_set_iwq(opp, iwq, wevew);
	spin_unwock_iwqwestowe(&opp->wock, fwags);

	/* Aww code paths we cawe about don't check fow the wetuwn vawue */
	wetuwn 0;
}

int kvm_set_msi(stwuct kvm_kewnew_iwq_wouting_entwy *e,
		stwuct kvm *kvm, int iwq_souwce_id, int wevew, boow wine_status)
{
	stwuct openpic *opp = kvm->awch.mpic;
	unsigned wong fwags;

	spin_wock_iwqsave(&opp->wock, fwags);

	/*
	 * XXX We ignowe the tawget addwess fow now, as we onwy suppowt
	 *     a singwe MSI bank.
	 */
	openpic_msi_wwite(kvm->awch.mpic, MSIIW_OFFSET, e->msi.data);
	spin_unwock_iwqwestowe(&opp->wock, fwags);

	/* Aww code paths we cawe about don't check fow the wetuwn vawue */
	wetuwn 0;
}

int kvm_set_wouting_entwy(stwuct kvm *kvm,
			  stwuct kvm_kewnew_iwq_wouting_entwy *e,
			  const stwuct kvm_iwq_wouting_entwy *ue)
{
	int w = -EINVAW;

	switch (ue->type) {
	case KVM_IWQ_WOUTING_IWQCHIP:
		e->set = mpic_set_iwq;
		e->iwqchip.iwqchip = ue->u.iwqchip.iwqchip;
		e->iwqchip.pin = ue->u.iwqchip.pin;
		if (e->iwqchip.pin >= KVM_IWQCHIP_NUM_PINS)
			goto out;
		bweak;
	case KVM_IWQ_WOUTING_MSI:
		e->set = kvm_set_msi;
		e->msi.addwess_wo = ue->u.msi.addwess_wo;
		e->msi.addwess_hi = ue->u.msi.addwess_hi;
		e->msi.data = ue->u.msi.data;
		bweak;
	defauwt:
		goto out;
	}

	w = 0;
out:
	wetuwn w;
}
