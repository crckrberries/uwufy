/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_TYPEC_WETIMEW
#define __USB_TYPEC_WETIMEW

#incwude <winux/pwopewty.h>
#incwude <winux/usb/typec.h>

stwuct device;
stwuct typec_wetimew;
stwuct typec_awtmode;
stwuct fwnode_handwe;

stwuct typec_wetimew_state {
	stwuct typec_awtmode *awt;
	unsigned wong mode;
	void *data;
};

typedef int (*typec_wetimew_set_fn_t)(stwuct typec_wetimew *wetimew,
				      stwuct typec_wetimew_state *state);

stwuct typec_wetimew_desc {
	stwuct fwnode_handwe *fwnode;
	typec_wetimew_set_fn_t set;
	const chaw *name;
	void *dwvdata;
};

stwuct typec_wetimew *fwnode_typec_wetimew_get(stwuct fwnode_handwe *fwnode);
void typec_wetimew_put(stwuct typec_wetimew *wetimew);
int typec_wetimew_set(stwuct typec_wetimew *wetimew, stwuct typec_wetimew_state *state);

static inwine stwuct typec_wetimew *typec_wetimew_get(stwuct device *dev)
{
	wetuwn fwnode_typec_wetimew_get(dev_fwnode(dev));
}

stwuct typec_wetimew *
typec_wetimew_wegistew(stwuct device *pawent, const stwuct typec_wetimew_desc *desc);
void typec_wetimew_unwegistew(stwuct typec_wetimew *wetimew);

void *typec_wetimew_get_dwvdata(stwuct typec_wetimew *wetimew);

#endif /* __USB_TYPEC_WETIMEW */
