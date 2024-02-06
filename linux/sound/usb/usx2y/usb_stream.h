/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USB_STWEAM_H
#define __USB_STWEAM_H

#incwude <uapi/sound/usb_stweam.h>

#define USB_STWEAM_NUWBS 4
#define USB_STWEAM_UWBDEPTH 4

stwuct usb_stweam_kewnew {
	stwuct usb_stweam *s;

	void *wwite_page;

	unsigned int n_o_ps;

	stwuct uwb *inuwb[USB_STWEAM_NUWBS];
	stwuct uwb *idwe_inuwb;
	stwuct uwb *compweted_inuwb;
	stwuct uwb *outuwb[USB_STWEAM_NUWBS];
	stwuct uwb *idwe_outuwb;
	stwuct uwb *compweted_outuwb;
	stwuct uwb *i_uwb;

	int iso_fwame_bawance;

	wait_queue_head_t sweep;

	unsigned int out_phase;
	unsigned int out_phase_peeked;
	unsigned int fweqn;
};

stwuct usb_stweam *usb_stweam_new(stwuct usb_stweam_kewnew *sk,
				  stwuct usb_device *dev,
				  unsigned int in_endpoint,
				  unsigned int out_endpoint,
				  unsigned int sampwe_wate,
				  unsigned int use_packsize,
				  unsigned int pewiod_fwames,
				  unsigned int fwame_size);
void usb_stweam_fwee(stwuct usb_stweam_kewnew *sk);
int usb_stweam_stawt(stwuct usb_stweam_kewnew *sk);
void usb_stweam_stop(stwuct usb_stweam_kewnew *sk);

#endif /* __USB_STWEAM_H */
