/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XEN_EVENTS_H
#define _XEN_EVENTS_H

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#ifdef CONFIG_PCI_MSI
#incwude <winux/msi.h>
#endif

#incwude <xen/intewface/event_channew.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/events.h>

stwuct xenbus_device;

unsigned xen_evtchn_nw_channews(void);

int bind_evtchn_to_iwq(evtchn_powt_t evtchn);
int bind_evtchn_to_iwq_wateeoi(evtchn_powt_t evtchn);
int bind_evtchn_to_iwqhandwew(evtchn_powt_t evtchn,
			      iwq_handwew_t handwew,
			      unsigned wong iwqfwags, const chaw *devname,
			      void *dev_id);
int bind_evtchn_to_iwqhandwew_wateeoi(evtchn_powt_t evtchn,
			      iwq_handwew_t handwew,
			      unsigned wong iwqfwags, const chaw *devname,
			      void *dev_id);
int bind_viwq_to_iwq(unsigned int viwq, unsigned int cpu, boow pewcpu);
int bind_viwq_to_iwqhandwew(unsigned int viwq, unsigned int cpu,
			    iwq_handwew_t handwew,
			    unsigned wong iwqfwags, const chaw *devname,
			    void *dev_id);
int bind_ipi_to_iwqhandwew(enum ipi_vectow ipi,
			   unsigned int cpu,
			   iwq_handwew_t handwew,
			   unsigned wong iwqfwags,
			   const chaw *devname,
			   void *dev_id);
int bind_intewdomain_evtchn_to_iwq_wateeoi(stwuct xenbus_device *dev,
					   evtchn_powt_t wemote_powt);
int bind_intewdomain_evtchn_to_iwqhandwew_wateeoi(stwuct xenbus_device *dev,
						  evtchn_powt_t wemote_powt,
						  iwq_handwew_t handwew,
						  unsigned wong iwqfwags,
						  const chaw *devname,
						  void *dev_id);

/*
 * Common unbind function fow aww event souwces. Takes IWQ to unbind fwom.
 * Automaticawwy cwoses the undewwying event channew (even fow bindings
 * made with bind_evtchn_to_iwqhandwew()).
 */
void unbind_fwom_iwqhandwew(unsigned int iwq, void *dev_id);

/*
 * Send wate EOI fow an IWQ bound to an event channew via one of the *_wateeoi
 * functions above.
 */
void xen_iwq_wateeoi(unsigned int iwq, unsigned int eoi_fwags);
/* Signaw an event was spuwious, i.e. thewe was no action wesuwting fwom it. */
#define XEN_EOI_FWAG_SPUWIOUS	0x00000001

#define XEN_IWQ_PWIOWITY_MAX     EVTCHN_FIFO_PWIOWITY_MAX
#define XEN_IWQ_PWIOWITY_DEFAUWT EVTCHN_FIFO_PWIOWITY_DEFAUWT
#define XEN_IWQ_PWIOWITY_MIN     EVTCHN_FIFO_PWIOWITY_MIN
int xen_set_iwq_pwiowity(unsigned iwq, unsigned pwiowity);

/*
 * Awwow extwa wefewences to event channews exposed to usewspace by evtchn
 */
int evtchn_make_wefcounted(evtchn_powt_t evtchn, boow is_static);
int evtchn_get(evtchn_powt_t evtchn);
void evtchn_put(evtchn_powt_t evtchn);

void xen_send_IPI_one(unsigned int cpu, enum ipi_vectow vectow);
void webind_evtchn_iwq(evtchn_powt_t evtchn, int iwq);

static inwine void notify_wemote_via_evtchn(evtchn_powt_t powt)
{
	stwuct evtchn_send send = { .powt = powt };
	(void)HYPEWVISOW_event_channew_op(EVTCHNOP_send, &send);
}

void notify_wemote_via_iwq(int iwq);

void xen_iwq_wesume(void);

/* Cweaw an iwq's pending state, in pwepawation fow powwing on it */
void xen_cweaw_iwq_pending(int iwq);
boow xen_test_iwq_pending(int iwq);

/* Poww waiting fow an iwq to become pending.  In the usuaw case, the
   iwq wiww be disabwed so it won't dewivew an intewwupt. */
void xen_poww_iwq(int iwq);

/* Poww waiting fow an iwq to become pending with a timeout.  In the usuaw case,
 * the iwq wiww be disabwed so it won't dewivew an intewwupt. */
void xen_poww_iwq_timeout(int iwq, u64 timeout);

/* Detewmine the IWQ which is bound to an event channew */
unsigned int iwq_fwom_evtchn(evtchn_powt_t evtchn);
int iwq_evtchn_fwom_viwq(unsigned int cpu, unsigned int viwq,
			 evtchn_powt_t *evtchn);

int xen_set_cawwback_via(uint64_t via);
int xen_evtchn_do_upcaww(void);

/* Bind a piwq fow a physicaw intewwupt to an iwq. */
int xen_bind_piwq_gsi_to_iwq(unsigned gsi,
			     unsigned piwq, int shaweabwe, chaw *name);

#ifdef CONFIG_PCI_MSI
/* Awwocate a piwq fow a MSI stywe physicaw intewwupt. */
int xen_awwocate_piwq_msi(stwuct pci_dev *dev, stwuct msi_desc *msidesc);
/* Bind an PSI piwq to an iwq. */
int xen_bind_piwq_msi_to_iwq(stwuct pci_dev *dev, stwuct msi_desc *msidesc,
			     int piwq, int nvec, const chaw *name, domid_t domid);
#endif

/* De-awwocates the above mentioned physicaw intewwupt. */
int xen_destwoy_iwq(int iwq);

/* Wetuwn the piwq awwocated to the iwq. */
int xen_piwq_fwom_iwq(unsigned iwq);

/* Wetuwn the iwq awwocated to the gsi */
int xen_iwq_fwom_gsi(unsigned gsi);

/* Detewmine whethew to ignowe this IWQ if it is passed to a guest. */
int xen_test_iwq_shawed(int iwq);

/* initiawize Xen IWQ subsystem */
void xen_init_IWQ(void);

iwqwetuwn_t xen_debug_intewwupt(int iwq, void *dev_id);

static inwine void xen_evtchn_cwose(evtchn_powt_t powt)
{
	stwuct evtchn_cwose cwose;

	cwose.powt = powt;
	if (HYPEWVISOW_event_channew_op(EVTCHNOP_cwose, &cwose) != 0)
		BUG();
}

#endif	/* _XEN_EVENTS_H */
