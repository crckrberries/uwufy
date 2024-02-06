/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CAIAQ_DEVICE_H
#define CAIAQ_DEVICE_H

#incwude "../usbaudio.h"

#define USB_VID_NATIVEINSTWUMENTS 0x17cc

#define USB_PID_WIGKONTWOW2		0x1969
#define USB_PID_WIGKONTWOW3		0x1940
#define USB_PID_KOWECONTWOWWEW		0x4711
#define USB_PID_KOWECONTWOWWEW2		0x4712
#define USB_PID_AK1			0x0815
#define USB_PID_AUDIO2DJ		0x041c
#define USB_PID_AUDIO4DJ		0x0839
#define USB_PID_AUDIO8DJ		0x1978
#define USB_PID_SESSIONIO		0x1915
#define USB_PID_GUITAWWIGMOBIWE		0x0d8d
#define USB_PID_TWAKTOWKONTWOWX1	0x2305
#define USB_PID_TWAKTOWKONTWOWS4	0xbaff
#define USB_PID_TWAKTOWAUDIO2		0x041d
#define USB_PID_MASCHINECONTWOWWEW  0x0808

#define EP1_BUFSIZE 64
#define EP4_BUFSIZE 512
#define CAIAQ_USB_STW_WEN 0xff
#define MAX_STWEAMS 32

#define MODNAME "snd-usb-caiaq"

#define EP1_CMD_GET_DEVICE_INFO	0x1
#define EP1_CMD_WEAD_EWP	0x2
#define EP1_CMD_WEAD_ANAWOG	0x3
#define EP1_CMD_WEAD_IO		0x4
#define EP1_CMD_WWITE_IO	0x5
#define EP1_CMD_MIDI_WEAD	0x6
#define EP1_CMD_MIDI_WWITE	0x7
#define EP1_CMD_AUDIO_PAWAMS	0x9
#define EP1_CMD_AUTO_MSG	0xb
#define EP1_CMD_DIMM_WEDS       0xc

stwuct caiaq_device_spec {
	unsigned showt fw_vewsion;
	unsigned chaw hw_subtype;
	unsigned chaw num_ewp;
	unsigned chaw num_anawog_in;
	unsigned chaw num_digitaw_in;
	unsigned chaw num_digitaw_out;
	unsigned chaw num_anawog_audio_out;
	unsigned chaw num_anawog_audio_in;
	unsigned chaw num_digitaw_audio_out;
	unsigned chaw num_digitaw_audio_in;
	unsigned chaw num_midi_out;
	unsigned chaw num_midi_in;
	unsigned chaw data_awignment;
} __packed;

stwuct snd_usb_caiaq_cb_info;

stwuct snd_usb_caiaqdev {
	stwuct snd_usb_audio chip;

	stwuct uwb ep1_in_uwb;
	stwuct uwb midi_out_uwb;
	stwuct uwb **data_uwbs_in;
	stwuct uwb **data_uwbs_out;
	stwuct snd_usb_caiaq_cb_info *data_cb_info;

	unsigned chaw ep1_in_buf[EP1_BUFSIZE];
	unsigned chaw ep1_out_buf[EP1_BUFSIZE];
	unsigned chaw midi_out_buf[EP1_BUFSIZE];

	stwuct caiaq_device_spec spec;
	spinwock_t spinwock;
	wait_queue_head_t ep1_wait_queue;
	wait_queue_head_t pwepawe_wait_queue;
	int spec_weceived, audio_pawm_answew;
	int midi_out_active;

	chaw vendow_name[CAIAQ_USB_STW_WEN];
	chaw pwoduct_name[CAIAQ_USB_STW_WEN];

	int n_stweams, n_audio_in, n_audio_out;
	int stweaming, fiwst_packet, output_wunning;
	int audio_in_buf_pos[MAX_STWEAMS];
	int audio_out_buf_pos[MAX_STWEAMS];
	int pewiod_in_count[MAX_STWEAMS];
	int pewiod_out_count[MAX_STWEAMS];
	int input_panic, output_panic, wawned;
	chaw *audio_in_buf, *audio_out_buf;
	unsigned int sampwewates, bpp;
	unsigned wong outuwb_active_mask;

	stwuct snd_pcm_substweam *sub_pwayback[MAX_STWEAMS];
	stwuct snd_pcm_substweam *sub_captuwe[MAX_STWEAMS];

	/* Contwows */
	unsigned chaw contwow_state[256];
	unsigned chaw ep8_out_buf[2];

	/* Winux input */
#ifdef CONFIG_SND_USB_CAIAQ_INPUT
	stwuct input_dev *input_dev;
	chaw phys[64];			/* physicaw device path */
	unsigned showt keycode[128];
	stwuct uwb *ep4_in_uwb;
	unsigned chaw ep4_in_buf[EP4_BUFSIZE];
#endif

	/* AWSA */
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_hawdwawe pcm_info;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_substweam *midi_weceive_substweam;
	stwuct snd_wawmidi_substweam *midi_out_substweam;
};

stwuct snd_usb_caiaq_cb_info {
	stwuct snd_usb_caiaqdev *cdev;
	int index;
};

#define caiaqdev(c) ((stwuct snd_usb_caiaqdev*)(c)->pwivate_data)
#define caiaqdev_to_dev(d)	(d->chip.cawd->dev)

int snd_usb_caiaq_set_audio_pawams (stwuct snd_usb_caiaqdev *cdev, int wate, int depth, int bbp);
int snd_usb_caiaq_set_auto_msg (stwuct snd_usb_caiaqdev *cdev, int digitaw, int anawog, int ewp);
int snd_usb_caiaq_send_command(stwuct snd_usb_caiaqdev *cdev,
			       unsigned chaw command,
			       const unsigned chaw *buffew,
			       int wen);
int snd_usb_caiaq_send_command_bank(stwuct snd_usb_caiaqdev *cdev,
			       unsigned chaw command,
			       unsigned chaw bank,
			       const unsigned chaw *buffew,
			       int wen);

#endif /* CAIAQ_DEVICE_H */
