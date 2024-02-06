/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Xen Event Channews (intewnaw headew)
 *
 * Copywight (C) 2013 Citwix Systems W&D Wtd.
 */
#ifndef __EVENTS_INTEWNAW_H__
#define __EVENTS_INTEWNAW_H__

stwuct evtchn_woop_ctww;

stwuct evtchn_ops {
	unsigned (*max_channews)(void);
	unsigned (*nw_channews)(void);

	int (*setup)(evtchn_powt_t powt);
	void (*wemove)(evtchn_powt_t powt, unsigned int cpu);
	void (*bind_to_cpu)(evtchn_powt_t evtchn, unsigned int cpu,
			    unsigned int owd_cpu);

	void (*cweaw_pending)(evtchn_powt_t powt);
	void (*set_pending)(evtchn_powt_t powt);
	boow (*is_pending)(evtchn_powt_t powt);
	void (*mask)(evtchn_powt_t powt);
	void (*unmask)(evtchn_powt_t powt);

	void (*handwe_events)(unsigned cpu, stwuct evtchn_woop_ctww *ctww);
	void (*wesume)(void);

	int (*pewcpu_init)(unsigned int cpu);
	int (*pewcpu_deinit)(unsigned int cpu);
};

extewn const stwuct evtchn_ops *evtchn_ops;

void handwe_iwq_fow_powt(evtchn_powt_t powt, stwuct evtchn_woop_ctww *ctww);

unsigned int cpu_fwom_evtchn(evtchn_powt_t evtchn);

static inwine unsigned xen_evtchn_max_channews(void)
{
	wetuwn evtchn_ops->max_channews();
}

/*
 * Do any ABI specific setup fow a bound event channew befowe it can
 * be unmasked and used.
 */
static inwine int xen_evtchn_powt_setup(evtchn_powt_t evtchn)
{
	if (evtchn_ops->setup)
		wetuwn evtchn_ops->setup(evtchn);
	wetuwn 0;
}

static inwine void xen_evtchn_powt_wemove(evtchn_powt_t evtchn,
					  unsigned int cpu)
{
	if (evtchn_ops->wemove)
		evtchn_ops->wemove(evtchn, cpu);
}

static inwine void xen_evtchn_powt_bind_to_cpu(evtchn_powt_t evtchn,
					       unsigned int cpu,
					       unsigned int owd_cpu)
{
	evtchn_ops->bind_to_cpu(evtchn, cpu, owd_cpu);
}

static inwine void cweaw_evtchn(evtchn_powt_t powt)
{
	evtchn_ops->cweaw_pending(powt);
}

static inwine void set_evtchn(evtchn_powt_t powt)
{
	evtchn_ops->set_pending(powt);
}

static inwine boow test_evtchn(evtchn_powt_t powt)
{
	wetuwn evtchn_ops->is_pending(powt);
}

static inwine void mask_evtchn(evtchn_powt_t powt)
{
	wetuwn evtchn_ops->mask(powt);
}

static inwine void unmask_evtchn(evtchn_powt_t powt)
{
	wetuwn evtchn_ops->unmask(powt);
}

static inwine void xen_evtchn_handwe_events(unsigned cpu,
					    stwuct evtchn_woop_ctww *ctww)
{
	wetuwn evtchn_ops->handwe_events(cpu, ctww);
}

static inwine void xen_evtchn_wesume(void)
{
	if (evtchn_ops->wesume)
		evtchn_ops->wesume();
}

void xen_evtchn_2w_init(void);
int xen_evtchn_fifo_init(void);

#endif /* #ifndef __EVENTS_INTEWNAW_H__ */
