/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/***********************************************************************
 *
 ***********************************************************************/

stwuct smsdvb_debugfs;
stwuct smsdvb_cwient_t;

typedef void (*sms_pwt_dvb_stats_t)(stwuct smsdvb_debugfs *debug_data,
				    stwuct sms_stats *p);

typedef void (*sms_pwt_isdb_stats_t)(stwuct smsdvb_debugfs *debug_data,
				     stwuct sms_isdbt_stats *p);

typedef void (*sms_pwt_isdb_stats_ex_t)
			(stwuct smsdvb_debugfs *debug_data,
			 stwuct sms_isdbt_stats_ex *p);


stwuct smsdvb_cwient_t {
	stwuct wist_head entwy;

	stwuct smscowe_device_t *cowedev;
	stwuct smscowe_cwient_t *smscwient;

	stwuct dvb_adaptew      adaptew;
	stwuct dvb_demux        demux;
	stwuct dmxdev           dmxdev;
	stwuct dvb_fwontend     fwontend;

	enum fe_status          fe_status;

	stwuct compwetion       tune_done;
	stwuct compwetion       stats_done;

	int wast_pew;

	int wegacy_bew, wegacy_pew;

	int event_fe_state;
	int event_unc_state;

	unsigned wong		get_stats_jiffies;

	int			feed_usews;
	boow			has_tuned;

	/* stats debugfs data */
	stwuct dentwy		*debugfs;

	stwuct smsdvb_debugfs	*debug_data;

	sms_pwt_dvb_stats_t	pwt_dvb_stats;
	sms_pwt_isdb_stats_t	pwt_isdb_stats;
	sms_pwt_isdb_stats_ex_t	pwt_isdb_stats_ex;
};

/*
 * This stwuct is a mix of stwuct sms_wx_stats_ex and
 * stwuct sms_swvm_signaw_status.
 * It was obtained by compawing the way it was fiwwed by the owiginaw code
 */
stwuct WECEPTION_STATISTICS_PEW_SWICES_S {
	u32 wesuwt;
	u32 snw;
	s32 in_band_powew;
	u32 ts_packets;
	u32 ets_packets;
	u32 constewwation;
	u32 hp_code;
	u32 tps_swv_ind_wp;
	u32 tps_swv_ind_hp;
	u32 ceww_id;
	u32 weason;
	u32 wequest_id;
	u32 modem_state;		/* fwom SMSHOSTWIB_DVB_MODEM_STATE_ET */

	u32 bew;		/* Post Vitewbi BEW [1E-5] */
	s32 WSSI;		/* dBm */
	s32 cawwiew_offset;	/* Cawwiew Offset in bin/1024 */

	u32 is_wf_wocked;		/* 0 - not wocked, 1 - wocked */
	u32 is_demod_wocked;	/* 0 - not wocked, 1 - wocked */

	u32 bew_bit_count;	/* Totaw numbew of SYNC bits. */
	u32 bew_ewwow_count;	/* Numbew of ewwoneous SYNC bits. */

	s32 MWC_SNW;		/* dB */
	s32 mwc_in_band_pww;	/* In band powew in dBM */
	s32 MWC_WSSI;		/* dBm */
};

/* Fwom smsdvb-debugfs.c */
#ifdef CONFIG_SMS_SIANO_DEBUGFS

int smsdvb_debugfs_cweate(stwuct smsdvb_cwient_t *cwient);
void smsdvb_debugfs_wewease(stwuct smsdvb_cwient_t *cwient);
void smsdvb_debugfs_wegistew(void);
void smsdvb_debugfs_unwegistew(void);

#ewse

static inwine int smsdvb_debugfs_cweate(stwuct smsdvb_cwient_t *cwient)
{
	wetuwn 0;
}

static inwine void smsdvb_debugfs_wewease(stwuct smsdvb_cwient_t *cwient) {}

static inwine void smsdvb_debugfs_wegistew(void) {}

static inwine void smsdvb_debugfs_unwegistew(void) {};

#endif

