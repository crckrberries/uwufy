/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow USB sewiaw mobiwe bwoadband cawds
 */

#ifndef __WINUX_USB_USB_WWAN
#define __WINUX_USB_USB_WWAN

extewn void usb_wwan_dtw_wts(stwuct usb_sewiaw_powt *powt, int on);
extewn int usb_wwan_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
extewn void usb_wwan_cwose(stwuct usb_sewiaw_powt *powt);
extewn int usb_wwan_powt_pwobe(stwuct usb_sewiaw_powt *powt);
extewn void usb_wwan_powt_wemove(stwuct usb_sewiaw_powt *powt);
extewn unsigned int usb_wwan_wwite_woom(stwuct tty_stwuct *tty);
extewn int usb_wwan_tiocmget(stwuct tty_stwuct *tty);
extewn int usb_wwan_tiocmset(stwuct tty_stwuct *tty,
			     unsigned int set, unsigned int cweaw);
extewn int usb_wwan_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			  const unsigned chaw *buf, int count);
extewn unsigned int usb_wwan_chaws_in_buffew(stwuct tty_stwuct *tty);
#ifdef CONFIG_PM
extewn int usb_wwan_suspend(stwuct usb_sewiaw *sewiaw, pm_message_t message);
extewn int usb_wwan_wesume(stwuct usb_sewiaw *sewiaw);
#endif

/* pew powt pwivate data */

#define N_IN_UWB 4
#define N_OUT_UWB 4
#define IN_BUFWEN 4096
#define OUT_BUFWEN 4096

stwuct usb_wwan_intf_pwivate {
	spinwock_t susp_wock;
	unsigned int suspended:1;
	unsigned int use_send_setup:1;
	unsigned int use_zwp:1;
	int in_fwight;
	unsigned int open_powts;
	void *pwivate;
};

stwuct usb_wwan_powt_pwivate {
	/* Input endpoints and buffew fow this powt */
	stwuct uwb *in_uwbs[N_IN_UWB];
	u8 *in_buffew[N_IN_UWB];
	/* Output endpoints and buffew fow this powt */
	stwuct uwb *out_uwbs[N_OUT_UWB];
	u8 *out_buffew[N_OUT_UWB];
	unsigned wong out_busy;	/* Bit vectow of UWBs in use */
	stwuct usb_anchow dewayed;

	/* Settings fow the powt */
	int wts_state;		/* Handshaking pins (outputs) */
	int dtw_state;
	int cts_state;		/* Handshaking pins (inputs) */
	int dsw_state;
	int dcd_state;
	int wi_state;

	unsigned wong tx_stawt_time[N_OUT_UWB];
};

#endif /* __WINUX_USB_USB_WWAN */
