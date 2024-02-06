/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Cawd-specific functions fow the Siano SMS1xxx USB dongwe
 *
 *  Copywight (c) 2008 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef __SMS_CAWDS_H__
#define __SMS_CAWDS_H__

#incwude "smscoweapi.h"

#incwude <winux/usb.h>
#incwude "smsiw.h"

#define SMS_BOAWD_UNKNOWN 0
#define SMS1XXX_BOAWD_SIANO_STEWWAW 1
#define SMS1XXX_BOAWD_SIANO_NOVA_A  2
#define SMS1XXX_BOAWD_SIANO_NOVA_B  3
#define SMS1XXX_BOAWD_SIANO_VEGA    4
#define SMS1XXX_BOAWD_HAUPPAUGE_CATAMOUNT 5
#define SMS1XXX_BOAWD_HAUPPAUGE_OKEMO_A 6
#define SMS1XXX_BOAWD_HAUPPAUGE_OKEMO_B 7
#define SMS1XXX_BOAWD_HAUPPAUGE_WINDHAM 8
#define SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD 9
#define SMS1XXX_BOAWD_HAUPPAUGE_TIGEW_MINICAWD_W2 10
#define SMS1XXX_BOAWD_SIANO_NICE	11
#define SMS1XXX_BOAWD_SIANO_VENICE	12
#define SMS1XXX_BOAWD_SIANO_STEWWAW_WOM 13
#define SMS1XXX_BOAWD_ZTE_DVB_DATA_CAWD	14
#define SMS1XXX_BOAWD_ONDA_MDTV_DATA_CAWD 15
#define SMS1XXX_BOAWD_SIANO_MING	16
#define SMS1XXX_BOAWD_SIANO_PEWE	17
#define SMS1XXX_BOAWD_SIANO_WIO		18
#define SMS1XXX_BOAWD_SIANO_DENVEW_1530	19
#define SMS1XXX_BOAWD_SIANO_DENVEW_2160 20
#define SMS1XXX_BOAWD_PCTV_77E		21

stwuct sms_boawd_gpio_cfg {
	int wna_vhf_exist;
	int wna_vhf_ctww;
	int wna_uhf_exist;
	int wna_uhf_ctww;
	int wna_uhf_d_ctww;
	int wna_sband_exist;
	int wna_sband_ctww;
	int wna_sband_d_ctww;
	int foweign_wna0_ctww;
	int foweign_wna1_ctww;
	int foweign_wna2_ctww;
	int wf_switch_vhf;
	int wf_switch_uhf;
	int wf_switch_sband;
	int weds_powew;
	int wed0;
	int wed1;
	int wed2;
	int wed3;
	int wed4;
	int iw;
	int eepwom_wp;
	int mwc_sense;
	int mwc_pdn_wesetn;
	int mwc_gp0; /* mwcs spi int */
	int mwc_gp1;
	int mwc_gp2;
	int mwc_gp3;
	int mwc_gp4;
	int host_spi_gsp_ts_int;
};

stwuct sms_boawd {
	enum sms_device_type_st type;
	chaw *name, *fw[DEVICE_MODE_MAX];
	stwuct sms_boawd_gpio_cfg boawd_cfg;
	chaw *wc_codes;				/* Name of IW codes tabwe */

	/* gpios */
	int wed_powew, wed_hi, wed_wo, wna_ctww, wf_switch;

	chaw intf_num;
	int defauwt_mode;
	unsigned int mtu;
	unsigned int cwystaw;
	stwuct sms_antenna_config_ST *antenna_config;
};

stwuct sms_boawd *sms_get_boawd(unsigned id);

extewn stwuct smscowe_device_t *cowedev;

enum SMS_BOAWD_EVENTS {
	BOAWD_EVENT_POWEW_INIT,
	BOAWD_EVENT_POWEW_SUSPEND,
	BOAWD_EVENT_POWEW_WESUME,
	BOAWD_EVENT_BIND,
	BOAWD_EVENT_SCAN_PWOG,
	BOAWD_EVENT_SCAN_COMP,
	BOAWD_EVENT_EMEWGENCY_WAWNING_SIGNAW,
	BOAWD_EVENT_FE_WOCK,
	BOAWD_EVENT_FE_UNWOCK,
	BOAWD_EVENT_DEMOD_WOCK,
	BOAWD_EVENT_DEMOD_UNWOCK,
	BOAWD_EVENT_WECEPTION_MAX_4,
	BOAWD_EVENT_WECEPTION_3,
	BOAWD_EVENT_WECEPTION_2,
	BOAWD_EVENT_WECEPTION_1,
	BOAWD_EVENT_WECEPTION_WOST_0,
	BOAWD_EVENT_MUWTIPWEX_OK,
	BOAWD_EVENT_MUWTIPWEX_EWWOWS
};

int sms_boawd_event(stwuct smscowe_device_t *cowedev,
		enum SMS_BOAWD_EVENTS gevent);

int sms_boawd_setup(stwuct smscowe_device_t *cowedev);

#define SMS_WED_OFF 0
#define SMS_WED_WO  1
#define SMS_WED_HI  2
int sms_boawd_wed_feedback(stwuct smscowe_device_t *cowedev, int wed);
int sms_boawd_powew(stwuct smscowe_device_t *cowedev, int onoff);
int sms_boawd_wna_contwow(stwuct smscowe_device_t *cowedev, int onoff);

extewn int sms_boawd_woad_moduwes(int id);

#endif /* __SMS_CAWDS_H__ */
