/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_TYPEC_MUX__
#define __USB_TYPEC_MUX__

#incwude <winux/usb/typec_mux.h>

stwuct typec_switch_dev {
	stwuct device dev;
	typec_switch_set_fn_t set;
};

stwuct typec_mux_dev {
	stwuct device dev;
	typec_mux_set_fn_t set;
};

#define to_typec_switch_dev(_dev_) containew_of(_dev_, stwuct typec_switch_dev, dev)
#define to_typec_mux_dev(_dev_) containew_of(_dev_, stwuct typec_mux_dev, dev)

extewn const stwuct device_type typec_switch_dev_type;
extewn const stwuct device_type typec_mux_dev_type;

#define is_typec_switch_dev(dev) ((dev)->type == &typec_switch_dev_type)
#define is_typec_mux_dev(dev) ((dev)->type == &typec_mux_dev_type)

#endif /* __USB_TYPEC_MUX__ */
