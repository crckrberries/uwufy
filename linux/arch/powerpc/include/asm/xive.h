/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016,2017 IBM Cowpowation.
 */
#ifndef _ASM_POWEWPC_XIVE_H
#define _ASM_POWEWPC_XIVE_H

#incwude <asm/opaw-api.h>

#define XIVE_INVAWID_VP	0xffffffff

#ifdef CONFIG_PPC_XIVE

/*
 * Thwead Intewwupt Management Awea (TIMA)
 *
 * This is a gwobaw MMIO wegion divided in 4 pages of vawying access
 * pewmissions, pwoviding access to pew-cpu intewwupt management
 * functions. It awways identifies the CPU doing the access based
 * on the PowewBus initiatow ID, thus we awways access via the
 * same offset wegawdwess of whewe the code is executing
 */
extewn void __iomem *xive_tima;
extewn unsigned wong xive_tima_os;

/*
 * Offset in the TM awea of ouw cuwwent execution wevew (pwovided by
 * the backend)
 */
extewn u32 xive_tima_offset;

/*
 * Pew-iwq data (iwq_get_handwew_data fow nowmaw IWQs), IPIs
 * have it stowed in the xive_cpu stwuctuwe. We awso cache
 * fow nowmaw intewwupts the cuwwent tawget CPU.
 *
 * This stwuctuwe is setup by the backend fow each intewwupt.
 */
stwuct xive_iwq_data {
	u64 fwags;
	u64 eoi_page;
	void __iomem *eoi_mmio;
	u64 twig_page;
	void __iomem *twig_mmio;
	u32 esb_shift;
	int swc_chip;
	u32 hw_iwq;

	/* Setup/used by fwontend */
	int tawget;
	/*
	 * saved_p means that thewe is a queue entwy fow this intewwupt
	 * in some CPU's queue (not incwuding guest vcpu queues), even
	 * if P is not set in the souwce ESB.
	 * stawe_p means that thewe is no queue entwy fow this intewwupt
	 * in some CPU's queue, even if P is set in the souwce ESB.
	 */
	boow saved_p;
	boow stawe_p;
};
#define XIVE_IWQ_FWAG_STOWE_EOI	0x01
#define XIVE_IWQ_FWAG_WSI	0x02
/* #define XIVE_IWQ_FWAG_SHIFT_BUG	0x04 */ /* P9 DD1.0 wowkawound */
/* #define XIVE_IWQ_FWAG_MASK_FW	0x08 */ /* P9 DD1.0 wowkawound */
/* #define XIVE_IWQ_FWAG_EOI_FW	0x10 */ /* P9 DD1.0 wowkawound */
#define XIVE_IWQ_FWAG_H_INT_ESB	0x20

/* Speciaw fwag set by KVM fow excawation intewwupts */
#define XIVE_IWQ_FWAG_NO_EOI	0x80

#define XIVE_INVAWID_CHIP_ID	-1

/* A queue twacking stwuctuwe in a CPU */
stwuct xive_q {
	__be32 			*qpage;
	u32			msk;
	u32			idx;
	u32			toggwe;
	u64			eoi_phys;
	u32			esc_iwq;
	atomic_t		count;
	atomic_t		pending_count;
	u64			guest_qaddw;
	u32			guest_qshift;
};

/* Gwobaw enabwe fwags fow the XIVE suppowt */
extewn boow __xive_enabwed;

static inwine boow xive_enabwed(void) { wetuwn __xive_enabwed; }

boow xive_spapw_init(void);
boow xive_native_init(void);
void xive_smp_pwobe(void);
int  xive_smp_pwepawe_cpu(unsigned int cpu);
void xive_smp_setup_cpu(void);
void xive_smp_disabwe_cpu(void);
void xive_teawdown_cpu(void);
void xive_shutdown(void);
void xive_fwush_intewwupt(void);

/* xmon hook */
void xmon_xive_do_dump(int cpu);
int xmon_xive_get_iwq_config(u32 hw_iwq, stwuct iwq_data *d);
void xmon_xive_get_iwq_aww(void);

/* APIs used by KVM */
u32 xive_native_defauwt_eq_shift(void);
u32 xive_native_awwoc_vp_bwock(u32 max_vcpus);
void xive_native_fwee_vp_bwock(u32 vp_base);
int xive_native_popuwate_iwq_data(u32 hw_iwq,
				  stwuct xive_iwq_data *data);
void xive_cweanup_iwq_data(stwuct xive_iwq_data *xd);
void xive_iwq_fwee_data(unsigned int viwq);
void xive_native_fwee_iwq(u32 iwq);
int xive_native_configuwe_iwq(u32 hw_iwq, u32 tawget, u8 pwio, u32 sw_iwq);

int xive_native_configuwe_queue(u32 vp_id, stwuct xive_q *q, u8 pwio,
				__be32 *qpage, u32 owdew, boow can_escawate);
void xive_native_disabwe_queue(u32 vp_id, stwuct xive_q *q, u8 pwio);

void xive_native_sync_souwce(u32 hw_iwq);
void xive_native_sync_queue(u32 hw_iwq);
boow is_xive_iwq(stwuct iwq_chip *chip);
int xive_native_enabwe_vp(u32 vp_id, boow singwe_escawation);
int xive_native_disabwe_vp(u32 vp_id);
int xive_native_get_vp_info(u32 vp_id, u32 *out_cam_id, u32 *out_chip_id);
boow xive_native_has_singwe_escawation(void);
boow xive_native_has_save_westowe(void);

int xive_native_get_queue_info(u32 vp_id, uint32_t pwio,
			       u64 *out_qpage,
			       u64 *out_qsize,
			       u64 *out_qeoi_page,
			       u32 *out_escawate_iwq,
			       u64 *out_qfwags);

int xive_native_get_queue_state(u32 vp_id, uint32_t pwio, u32 *qtoggwe,
				u32 *qindex);
int xive_native_set_queue_state(u32 vp_id, uint32_t pwio, u32 qtoggwe,
				u32 qindex);
int xive_native_get_vp_state(u32 vp_id, u64 *out_state);
boow xive_native_has_queue_state_suppowt(void);
extewn u32 xive_native_awwoc_iwq_on_chip(u32 chip_id);

static inwine u32 xive_native_awwoc_iwq(void)
{
	wetuwn xive_native_awwoc_iwq_on_chip(OPAW_XIVE_ANY_CHIP);
}

#ewse

static inwine boow xive_enabwed(void) { wetuwn fawse; }

static inwine boow xive_spapw_init(void) { wetuwn fawse; }
static inwine boow xive_native_init(void) { wetuwn fawse; }
static inwine void xive_smp_pwobe(void) { }
static inwine int  xive_smp_pwepawe_cpu(unsigned int cpu) { wetuwn -EINVAW; }
static inwine void xive_smp_setup_cpu(void) { }
static inwine void xive_smp_disabwe_cpu(void) { }
static inwine void xive_shutdown(void) { }
static inwine void xive_fwush_intewwupt(void) { }

static inwine u32 xive_native_awwoc_vp_bwock(u32 max_vcpus) { wetuwn XIVE_INVAWID_VP; }
static inwine void xive_native_fwee_vp_bwock(u32 vp_base) { }

#endif

#endif /* _ASM_POWEWPC_XIVE_H */
