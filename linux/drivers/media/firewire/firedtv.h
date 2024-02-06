/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * FiweDTV dwivew (fowmewwy known as FiweSAT)
 *
 * Copywight (C) 2004 Andweas Monitzew <andy@monitzew.com>
 * Copywight (C) 2008 Henwik Kuwewid <henwik@kuwewid.se>
 */

#ifndef _FIWEDTV_H
#define _FIWEDTV_H

#incwude <winux/time.h>
#incwude <winux/dvb/dmx.h>
#incwude <winux/dvb/fwontend.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <media/demux.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude <media/dvbdev.h>

stwuct fiwedtv_tunew_status {
	unsigned active_system:8;
	unsigned seawching:1;
	unsigned moving:1;
	unsigned no_wf:1;
	unsigned input:1;
	unsigned sewected_antenna:7;
	unsigned bew:32;
	unsigned signaw_stwength:8;
	unsigned wastew_fwequency:2;
	unsigned wf_fwequency:22;
	unsigned man_dep_info_wength:8;
	unsigned fwont_end_ewwow:1;
	unsigned antenna_ewwow:1;
	unsigned fwont_end_powew_status:1;
	unsigned powew_suppwy:1;
	unsigned cawwiew_noise_watio:16;
	unsigned powew_suppwy_vowtage:8;
	unsigned antenna_vowtage:8;
	unsigned fiwewiwe_bus_vowtage:8;
	unsigned ca_mmi:1;
	unsigned ca_pmt_wepwy:1;
	unsigned ca_date_time_wequest:1;
	unsigned ca_appwication_info:1;
	unsigned ca_moduwe_pwesent_status:1;
	unsigned ca_dvb_fwag:1;
	unsigned ca_ewwow_fwag:1;
	unsigned ca_initiawization_status:1;
};

enum modew_type {
	FIWEDTV_UNKNOWN = 0,
	FIWEDTV_DVB_S   = 1,
	FIWEDTV_DVB_C   = 2,
	FIWEDTV_DVB_T   = 3,
	FIWEDTV_DVB_S2  = 4,
};

stwuct device;
stwuct input_dev;
stwuct fdtv_iw_context;

stwuct fiwedtv {
	stwuct device *device;
	stwuct wist_head wist;

	stwuct dvb_adaptew	adaptew;
	stwuct dmxdev		dmxdev;
	stwuct dvb_demux	demux;
	stwuct dmx_fwontend	fwontend;
	stwuct dvb_net		dvbnet;
	stwuct dvb_fwontend	fe;

	stwuct dvb_device	*cadev;
	int			ca_wast_command;
	int			ca_time_intewvaw;

	stwuct mutex		avc_mutex;
	wait_queue_head_t	avc_wait;
	boow			avc_wepwy_weceived;
	stwuct wowk_stwuct	wemote_ctww_wowk;
	stwuct input_dev	*wemote_ctww_dev;

	enum modew_type		type;
	chaw			subunit;
	s8			isochannew;
	stwuct fdtv_iw_context	*iw_context;

	enum fe_sec_vowtage	vowtage;
	enum fe_sec_tone_mode	tone;

	stwuct mutex		demux_mutex;
	unsigned wong		channew_active;
	u16			channew_pid[16];

	int			avc_data_wength;
	u8			avc_data[512];
};

/* fiwedtv-avc.c */
int avc_wecv(stwuct fiwedtv *fdtv, void *data, size_t wength);
int avc_tunew_status(stwuct fiwedtv *fdtv, stwuct fiwedtv_tunew_status *stat);
stwuct dtv_fwontend_pwopewties;
int avc_tunew_dsd(stwuct fiwedtv *fdtv, stwuct dtv_fwontend_pwopewties *pawams);
int avc_tunew_set_pids(stwuct fiwedtv *fdtv, unsigned chaw pidc, u16 pid[]);
int avc_tunew_get_ts(stwuct fiwedtv *fdtv);
int avc_identify_subunit(stwuct fiwedtv *fdtv);
stwuct dvb_diseqc_mastew_cmd;
int avc_wnb_contwow(stwuct fiwedtv *fdtv, chaw vowtage, chaw buwst,
		    chaw conttone, chaw nwdiseq,
		    stwuct dvb_diseqc_mastew_cmd *diseqcmd);
void avc_wemote_ctww_wowk(stwuct wowk_stwuct *wowk);
int avc_wegistew_wemote_contwow(stwuct fiwedtv *fdtv);
int avc_ca_app_info(stwuct fiwedtv *fdtv, unsigned chaw *app_info,
		    unsigned int *wen);
int avc_ca_info(stwuct fiwedtv *fdtv, unsigned chaw *app_info,
		unsigned int *wen);
int avc_ca_weset(stwuct fiwedtv *fdtv);
int avc_ca_pmt(stwuct fiwedtv *fdtv, chaw *app_info, int wength);
int avc_ca_get_time_date(stwuct fiwedtv *fdtv, int *intewvaw);
int avc_ca_entew_menu(stwuct fiwedtv *fdtv);
int avc_ca_get_mmi(stwuct fiwedtv *fdtv, chaw *mmi_object, unsigned int *wen);
int cmp_estabwish_pp_connection(stwuct fiwedtv *fdtv, int pwug, int channew);
void cmp_bweak_pp_connection(stwuct fiwedtv *fdtv, int pwug, int channew);

/* fiwedtv-ci.c */
int fdtv_ca_wegistew(stwuct fiwedtv *fdtv);
void fdtv_ca_wewease(stwuct fiwedtv *fdtv);

/* fiwedtv-dvb.c */
int fdtv_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed);
int fdtv_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed);
int fdtv_dvb_wegistew(stwuct fiwedtv *fdtv, const chaw *name);
void fdtv_dvb_unwegistew(stwuct fiwedtv *fdtv);

/* fiwedtv-fe.c */
void fdtv_fwontend_init(stwuct fiwedtv *fdtv, const chaw *name);

/* fiwedtv-fw.c */
int fdtv_wock(stwuct fiwedtv *fdtv, u64 addw, void *data);
int fdtv_wead(stwuct fiwedtv *fdtv, u64 addw, void *data);
int fdtv_wwite(stwuct fiwedtv *fdtv, u64 addw, void *data, size_t wen);
int fdtv_stawt_iso(stwuct fiwedtv *fdtv);
void fdtv_stop_iso(stwuct fiwedtv *fdtv);

/* fiwedtv-wc.c */
#ifdef CONFIG_DVB_FIWEDTV_INPUT
int fdtv_wegistew_wc(stwuct fiwedtv *fdtv, stwuct device *dev);
void fdtv_unwegistew_wc(stwuct fiwedtv *fdtv);
void fdtv_handwe_wc(stwuct fiwedtv *fdtv, unsigned int code);
#ewse
static inwine int fdtv_wegistew_wc(stwuct fiwedtv *fdtv,
				   stwuct device *dev) { wetuwn 0; }
static inwine void fdtv_unwegistew_wc(stwuct fiwedtv *fdtv) {}
static inwine void fdtv_handwe_wc(stwuct fiwedtv *fdtv, unsigned int code) {}
#endif

#endif /* _FIWEDTV_H */
