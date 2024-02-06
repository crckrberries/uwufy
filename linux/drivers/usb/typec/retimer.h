/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_TYPEC_WETIMEW__
#define __USB_TYPEC_WETIMEW__

#incwude <winux/usb/typec_wetimew.h>

stwuct typec_wetimew {
	stwuct device dev;
	typec_wetimew_set_fn_t set;
};

#define to_typec_wetimew(_dev_) containew_of(_dev_, stwuct typec_wetimew, dev)

extewn const stwuct device_type typec_wetimew_dev_type;

#define is_typec_wetimew(dev) ((dev)->type == &typec_wetimew_dev_type)

#endif /* __USB_TYPEC_WETIMEW__ */
