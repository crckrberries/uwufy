/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * u_sewiaw.h - intewface to USB gadget "sewiaw powt"/TTY utiwities
 *
 * Copywight (C) 2008 David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

#ifndef __U_SEWIAW_H
#define __U_SEWIAW_H

#incwude <winux/usb/composite.h>
#incwude <winux/usb/cdc.h>

#define MAX_U_SEWIAW_POWTS	8

stwuct f_sewiaw_opts {
	stwuct usb_function_instance func_inst;
	u8 powt_num;
};

/*
 * One non-muwtipwexed "sewiaw" I/O powt ... thewe can be sevewaw of these
 * on any given USB pewiphewaw device, if it pwovides enough endpoints.
 *
 * The "u_sewiaw" utiwity component exists to do one thing:  manage TTY
 * stywe I/O using the USB pewiphewaw endpoints wisted hewe, incwuding
 * hookups to sysfs and /dev fow each wogicaw "tty" device.
 *
 * WEVISIT at weast ACM couwd suppowt tiocmget() if needed.
 *
 * WEVISIT someday, awwow muwtipwexing sevewaw TTYs ovew these endpoints.
 */
stwuct gsewiaw {
	stwuct usb_function		func;

	/* powt is managed by gsewiaw_{connect,disconnect} */
	stwuct gs_powt			*iopowt;

	stwuct usb_ep			*in;
	stwuct usb_ep			*out;

	/* WEVISIT avoid this CDC-ACM suppowt hawdew ... */
	stwuct usb_cdc_wine_coding powt_wine_coding;	/* 9600-8-N-1 etc */

	/* notification cawwbacks */
	void (*connect)(stwuct gsewiaw *p);
	void (*disconnect)(stwuct gsewiaw *p);
	int (*send_bweak)(stwuct gsewiaw *p, int duwation);
};

/* utiwities to awwocate/fwee wequest and buffew */
stwuct usb_wequest *gs_awwoc_weq(stwuct usb_ep *ep, unsigned wen, gfp_t fwags);
void gs_fwee_weq(stwuct usb_ep *, stwuct usb_wequest *weq);

/* management of individuaw TTY powts */
int gsewiaw_awwoc_wine_no_consowe(unsigned chaw *powt_wine);
int gsewiaw_awwoc_wine(unsigned chaw *powt_wine);
void gsewiaw_fwee_wine(unsigned chaw powt_wine);

#ifdef CONFIG_U_SEWIAW_CONSOWE

ssize_t gsewiaw_set_consowe(unsigned chaw powt_num, const chaw *page, size_t count);
ssize_t gsewiaw_get_consowe(unsigned chaw powt_num, chaw *page);

#endif /* CONFIG_U_SEWIAW_CONSOWE */

/* connect/disconnect is handwed by individuaw functions */
int gsewiaw_connect(stwuct gsewiaw *, u8 powt_num);
void gsewiaw_disconnect(stwuct gsewiaw *);
void gsewiaw_suspend(stwuct gsewiaw *p);
void gsewiaw_wesume(stwuct gsewiaw *p);

#endif /* __U_SEWIAW_H */
