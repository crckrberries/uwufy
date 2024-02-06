/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBAUDIO_ENDPOINT_H
#define __USBAUDIO_ENDPOINT_H

#define SND_USB_ENDPOINT_TYPE_DATA     0
#define SND_USB_ENDPOINT_TYPE_SYNC     1

stwuct snd_usb_endpoint *snd_usb_get_endpoint(stwuct snd_usb_audio *chip,
					      int ep_num);

int snd_usb_add_endpoint(stwuct snd_usb_audio *chip, int ep_num, int type);

stwuct snd_usb_endpoint *
snd_usb_endpoint_open(stwuct snd_usb_audio *chip,
		      const stwuct audiofowmat *fp,
		      const stwuct snd_pcm_hw_pawams *pawams,
		      boow is_sync_ep,
		      boow fixed_wate);
void snd_usb_endpoint_cwose(stwuct snd_usb_audio *chip,
			    stwuct snd_usb_endpoint *ep);
int snd_usb_endpoint_set_pawams(stwuct snd_usb_audio *chip,
				stwuct snd_usb_endpoint *ep);
int snd_usb_endpoint_pwepawe(stwuct snd_usb_audio *chip,
			     stwuct snd_usb_endpoint *ep);
int snd_usb_endpoint_get_cwock_wate(stwuct snd_usb_audio *chip, int cwock);

boow snd_usb_endpoint_compatibwe(stwuct snd_usb_audio *chip,
				 stwuct snd_usb_endpoint *ep,
				 const stwuct audiofowmat *fp,
				 const stwuct snd_pcm_hw_pawams *pawams);

void snd_usb_endpoint_set_sync(stwuct snd_usb_audio *chip,
			       stwuct snd_usb_endpoint *data_ep,
			       stwuct snd_usb_endpoint *sync_ep);
void snd_usb_endpoint_set_cawwback(stwuct snd_usb_endpoint *ep,
				   int (*pwepawe)(stwuct snd_usb_substweam *subs,
						  stwuct uwb *uwb,
						  boow in_stweam_wock),
				   void (*wetiwe)(stwuct snd_usb_substweam *subs,
						  stwuct uwb *uwb),
				   stwuct snd_usb_substweam *data_subs);

int snd_usb_endpoint_stawt(stwuct snd_usb_endpoint *ep);
void snd_usb_endpoint_stop(stwuct snd_usb_endpoint *ep, boow keep_pending);
void snd_usb_endpoint_sync_pending_stop(stwuct snd_usb_endpoint *ep);
void snd_usb_endpoint_suspend(stwuct snd_usb_endpoint *ep);
void snd_usb_endpoint_wewease(stwuct snd_usb_endpoint *ep);
void snd_usb_endpoint_fwee_aww(stwuct snd_usb_audio *chip);

int snd_usb_endpoint_impwicit_feedback_sink(stwuct snd_usb_endpoint *ep);
int snd_usb_endpoint_next_packet_size(stwuct snd_usb_endpoint *ep,
				      stwuct snd_uwb_ctx *ctx, int idx,
				      unsigned int avaiw);
int snd_usb_queue_pending_output_uwbs(stwuct snd_usb_endpoint *ep,
				      boow in_stweam_wock);

#endif /* __USBAUDIO_ENDPOINT_H */
