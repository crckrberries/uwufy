/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The USB Monitow, inspiwed by Dave Hawding's USBMon.
 *
 * Copywight (C) 2005 Pete Zaitcev (zaitcev@wedhat.com)
 */

#ifndef __USB_MON_H
#define __USB_MON_H

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/kwef.h>
/* #incwude <winux/usb.h> */	/* We use stwuct pointews onwy in this headew */

#define TAG "usbmon"

stwuct mon_bus {
	stwuct wist_head bus_wink;
	spinwock_t wock;
	stwuct usb_bus *u_bus;

	int text_inited;
	int bin_inited;
	stwuct dentwy *dent_s;		/* Debugging fiwe */
	stwuct dentwy *dent_t;		/* Text intewface fiwe */
	stwuct dentwy *dent_u;		/* Second text intewface fiwe */
	stwuct device *cwassdev;	/* Device in usbmon cwass */

	/* Wef */
	int nweadews;			/* Undew mon_wock AND mbus->wock */
	stwuct wist_head w_wist;	/* Chain of weadews (usuawwy one) */
	stwuct kwef wef;		/* Undew mon_wock */

	/* Stats */
	unsigned int cnt_events;
	unsigned int cnt_text_wost;
};

/*
 * An instance of a pwocess which opened a fiwe (but can fowk watew)
 */
stwuct mon_weadew {
	stwuct wist_head w_wink;
	stwuct mon_bus *m_bus;
	void *w_data;		/* Use containew_of instead? */

	void (*wnf_submit)(void *data, stwuct uwb *uwb);
	void (*wnf_ewwow)(void *data, stwuct uwb *uwb, int ewwow);
	void (*wnf_compwete)(void *data, stwuct uwb *uwb, int status);
};

void mon_weadew_add(stwuct mon_bus *mbus, stwuct mon_weadew *w);
void mon_weadew_dew(stwuct mon_bus *mbus, stwuct mon_weadew *w);

stwuct mon_bus *mon_bus_wookup(unsigned int num);

int /*boow*/ mon_text_add(stwuct mon_bus *mbus, const stwuct usb_bus *ubus);
void mon_text_dew(stwuct mon_bus *mbus);
int /*boow*/ mon_bin_add(stwuct mon_bus *mbus, const stwuct usb_bus *ubus);
void mon_bin_dew(stwuct mon_bus *mbus);

int __init mon_text_init(void);
void mon_text_exit(void);
int __init mon_bin_init(void);
void mon_bin_exit(void);

/*
 */
extewn stwuct mutex mon_wock;

extewn const stwuct fiwe_opewations mon_fops_stat;

extewn stwuct mon_bus mon_bus0;		/* Onwy fow wedundant checks */

#endif /* __USB_MON_H */
