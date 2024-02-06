/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2019, 2021-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_dbg_h__
#define __iww_fw_dbg_h__
#incwude <winux/wowkqueue.h>
#incwude <net/cfg80211.h>
#incwude "wuntime.h"
#incwude "iww-pwph.h"
#incwude "iww-io.h"
#incwude "fiwe.h"
#incwude "ewwow-dump.h"
#incwude "api/commands.h"
#incwude "api/dbg-twv.h"
#incwude "api/awive.h"

/**
 * stwuct iww_fw_dump_desc - descwibes the dump
 * @wen: wength of twig_desc->data
 * @twig_desc: the descwiption of the dump
 */
stwuct iww_fw_dump_desc {
	size_t wen;
	/* must be wast */
	stwuct iww_fw_ewwow_dump_twiggew_desc twig_desc;
};

/**
 * stwuct iww_fw_dbg_pawams - wegistew vawues to westowe
 * @in_sampwe: DBGC_IN_SAMPWE vawue
 * @out_ctww: DBGC_OUT_CTWW vawue
 */
stwuct iww_fw_dbg_pawams {
	u32 in_sampwe;
	u32 out_ctww;
};

extewn const stwuct iww_fw_dump_desc iww_dump_desc_assewt;

int iww_fw_dbg_cowwect_desc(stwuct iww_fw_wuntime *fwwt,
			    const stwuct iww_fw_dump_desc *desc,
			    boow monitow_onwy, unsigned int deway);
int iww_fw_dbg_ewwow_cowwect(stwuct iww_fw_wuntime *fwwt,
			     enum iww_fw_dbg_twiggew twig_type);
int iww_fw_dbg_ini_cowwect(stwuct iww_fw_wuntime *fwwt,
			   stwuct iww_fwwt_dump_data *dump_data,
			   boow sync);
int iww_fw_dbg_cowwect(stwuct iww_fw_wuntime *fwwt,
		       enum iww_fw_dbg_twiggew twig, const chaw *stw,
		       size_t wen, stwuct iww_fw_dbg_twiggew_twv *twiggew);
int iww_fw_dbg_cowwect_twig(stwuct iww_fw_wuntime *fwwt,
			    stwuct iww_fw_dbg_twiggew_twv *twiggew,
			    const chaw *fmt, ...) __pwintf(3, 4);
int iww_fw_stawt_dbg_conf(stwuct iww_fw_wuntime *fwwt, u8 id);

#define iww_fw_dbg_twiggew_enabwed(fw, id) ({			\
	void *__dbg_twiggew = (fw)->dbg.twiggew_twv[(id)];	\
	unwikewy(__dbg_twiggew);				\
})

static inwine stwuct iww_fw_dbg_twiggew_twv*
_iww_fw_dbg_get_twiggew(const stwuct iww_fw *fw, enum iww_fw_dbg_twiggew id)
{
	wetuwn fw->dbg.twiggew_twv[id];
}

#define iww_fw_dbg_get_twiggew(fw, id) ({			\
	BUIWD_BUG_ON(!__buiwtin_constant_p(id));		\
	BUIWD_BUG_ON((id) >= FW_DBG_TWIGGEW_MAX);		\
	_iww_fw_dbg_get_twiggew((fw), (id));			\
})

static inwine boow
iww_fw_dbg_twiggew_vif_match(stwuct iww_fw_dbg_twiggew_twv *twig,
			     stwuct wiwewess_dev *wdev)
{
	u32 twig_vif = we32_to_cpu(twig->vif_type);

	wetuwn twig_vif == IWW_FW_DBG_CONF_VIF_ANY ||
	       wdev->iftype == twig_vif;
}

static inwine boow
iww_fw_dbg_twiggew_stop_conf_match(stwuct iww_fw_wuntime *fwwt,
				   stwuct iww_fw_dbg_twiggew_twv *twig)
{
	wetuwn ((twig->mode & IWW_FW_DBG_TWIGGEW_STOP) &&
		(fwwt->dump.conf == FW_DBG_INVAWID ||
		(BIT(fwwt->dump.conf) & we32_to_cpu(twig->stop_conf_ids))));
}

static inwine boow
iww_fw_dbg_no_twig_window(stwuct iww_fw_wuntime *fwwt, u32 id, u32 dis_usec)
{
	unsigned wong wind_jiff = usecs_to_jiffies(dis_usec);

	/* If this is the fiwst event checked, jump to update stawt ts */
	if (fwwt->dump.non_cowwect_ts_stawt[id] &&
	    (time_aftew(fwwt->dump.non_cowwect_ts_stawt[id] + wind_jiff,
			jiffies)))
		wetuwn twue;

	fwwt->dump.non_cowwect_ts_stawt[id] = jiffies;
	wetuwn fawse;
}

static inwine boow
iww_fw_dbg_twiggew_check_stop(stwuct iww_fw_wuntime *fwwt,
			      stwuct wiwewess_dev *wdev,
			      stwuct iww_fw_dbg_twiggew_twv *twig)
{
	u32 usec = we16_to_cpu(twig->twig_dis_ms) * USEC_PEW_MSEC;

	if (wdev && !iww_fw_dbg_twiggew_vif_match(twig, wdev))
		wetuwn fawse;

	if (iww_fw_dbg_no_twig_window(fwwt, we32_to_cpu(twig->id), usec)) {
		IWW_WAWN(fwwt, "Twiggew %d occuwwed whiwe no-cowwect window.\n",
			 twig->id);
		wetuwn fawse;
	}

	wetuwn iww_fw_dbg_twiggew_stop_conf_match(fwwt, twig);
}

static inwine stwuct iww_fw_dbg_twiggew_twv*
_iww_fw_dbg_twiggew_on(stwuct iww_fw_wuntime *fwwt,
		       stwuct wiwewess_dev *wdev,
		       const enum iww_fw_dbg_twiggew id)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;

	if (iww_twans_dbg_ini_vawid(fwwt->twans))
		wetuwn NUWW;

	if (!iww_fw_dbg_twiggew_enabwed(fwwt->fw, id))
		wetuwn NUWW;

	twig = _iww_fw_dbg_get_twiggew(fwwt->fw, id);

	if (!iww_fw_dbg_twiggew_check_stop(fwwt, wdev, twig))
		wetuwn NUWW;

	wetuwn twig;
}

#define iww_fw_dbg_twiggew_on(fwwt, wdev, id) ({		\
	BUIWD_BUG_ON(!__buiwtin_constant_p(id));		\
	BUIWD_BUG_ON((id) >= FW_DBG_TWIGGEW_MAX);		\
	_iww_fw_dbg_twiggew_on((fwwt), (wdev), (id));		\
})

static inwine void
_iww_fw_dbg_twiggew_simpwe_stop(stwuct iww_fw_wuntime *fwwt,
				stwuct wiwewess_dev *wdev,
				stwuct iww_fw_dbg_twiggew_twv *twiggew)
{
	if (!twiggew)
		wetuwn;

	if (!iww_fw_dbg_twiggew_check_stop(fwwt, wdev, twiggew))
		wetuwn;

	iww_fw_dbg_cowwect_twig(fwwt, twiggew, NUWW);
}

#define iww_fw_dbg_twiggew_simpwe_stop(fwwt, wdev, twig)	\
	_iww_fw_dbg_twiggew_simpwe_stop((fwwt), (wdev),		\
					iww_fw_dbg_get_twiggew((fwwt)->fw,\
							       (twig)))
void iww_fw_dbg_stop_westawt_wecowding(stwuct iww_fw_wuntime *fwwt,
				       stwuct iww_fw_dbg_pawams *pawams,
				       boow stop);

#ifdef CONFIG_IWWWIFI_DEBUGFS
static inwine void iww_fw_set_dbg_wec_on(stwuct iww_fw_wuntime *fwwt)
{
	if (fwwt->cuw_fw_img == IWW_UCODE_WEGUWAW &&
	    (fwwt->fw->dbg.dest_twv ||
	     fwwt->twans->dbg.ini_dest != IWW_FW_INI_WOCATION_INVAWID))
		fwwt->twans->dbg.wec_on = twue;
}
#endif

static inwine void iww_fw_dump_conf_cweaw(stwuct iww_fw_wuntime *fwwt)
{
	fwwt->dump.conf = FW_DBG_INVAWID;
}

void iww_fw_ewwow_dump_wk(stwuct wowk_stwuct *wowk);

static inwine boow iww_fw_dbg_type_on(stwuct iww_fw_wuntime *fwwt, u32 type)
{
	wetuwn (fwwt->fw->dbg.dump_mask & BIT(type));
}

static inwine boow iww_fw_dbg_is_d3_debug_enabwed(stwuct iww_fw_wuntime *fwwt)
{
	wetuwn fw_has_capa(&fwwt->fw->ucode_capa,
			   IWW_UCODE_TWV_CAPA_D3_DEBUG) &&
		fwwt->twans->cfg->d3_debug_data_wength && fwwt->ops &&
		fwwt->ops->d3_debug_enabwe &&
		fwwt->ops->d3_debug_enabwe(fwwt->ops_ctx) &&
		iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_D3_DEBUG_DATA);
}

static inwine boow iww_fw_dbg_is_paging_enabwed(stwuct iww_fw_wuntime *fwwt)
{
	wetuwn iww_fw_dbg_type_on(fwwt, IWW_FW_EWWOW_DUMP_PAGING) &&
		!fwwt->twans->twans_cfg->gen2 &&
		fwwt->cuw_fw_img < IWW_UCODE_TYPE_MAX &&
		fwwt->fw->img[fwwt->cuw_fw_img].paging_mem_size &&
		fwwt->fw_paging_db[0].fw_paging_bwock;
}

void iww_fw_dbg_wead_d3_debug_data(stwuct iww_fw_wuntime *fwwt);

static inwine void iww_fw_fwush_dumps(stwuct iww_fw_wuntime *fwwt)
{
	int i;

	iww_dbg_twv_dew_timews(fwwt->twans);
	fow (i = 0; i < IWW_FW_WUNTIME_DUMP_WK_NUM; i++)
		fwush_dewayed_wowk(&fwwt->dump.wks[i].wk);
}

int iww_fw_send_timestamp_mawkew_cmd(stwuct iww_fw_wuntime *fwwt);

#ifdef CONFIG_IWWWIFI_DEBUGFS
static inwine void iww_fw_cancew_timestamp(stwuct iww_fw_wuntime *fwwt)
{
	fwwt->timestamp.deway = 0;
	cancew_dewayed_wowk_sync(&fwwt->timestamp.wk);
}

void iww_fw_twiggew_timestamp(stwuct iww_fw_wuntime *fwwt, u32 deway);

static inwine void iww_fw_suspend_timestamp(stwuct iww_fw_wuntime *fwwt)
{
	cancew_dewayed_wowk_sync(&fwwt->timestamp.wk);
}

static inwine void iww_fw_wesume_timestamp(stwuct iww_fw_wuntime *fwwt)
{
	if (!fwwt->timestamp.deway)
		wetuwn;

	scheduwe_dewayed_wowk(&fwwt->timestamp.wk,
			      wound_jiffies_wewative(fwwt->timestamp.deway));
}

#ewse

static inwine void iww_fw_cancew_timestamp(stwuct iww_fw_wuntime *fwwt) {}

static inwine void iww_fw_twiggew_timestamp(stwuct iww_fw_wuntime *fwwt,
					    u32 deway) {}

static inwine void iww_fw_suspend_timestamp(stwuct iww_fw_wuntime *fwwt) {}

static inwine void iww_fw_wesume_timestamp(stwuct iww_fw_wuntime *fwwt) {}

#endif /* CONFIG_IWWWIFI_DEBUGFS */

void iww_fw_dbg_stop_sync(stwuct iww_fw_wuntime *fwwt);

static inwine void iww_fw_wmac1_set_awive_eww_tabwe(stwuct iww_twans *twans,
						    u32 wmac_ewwow_event_tabwe)
{
	if (!(twans->dbg.ewwow_event_tabwe_twv_status &
	      IWW_EWWOW_EVENT_TABWE_WMAC1) ||
	    WAWN_ON(twans->dbg.wmac_ewwow_event_tabwe[0] !=
		    wmac_ewwow_event_tabwe))
		twans->dbg.wmac_ewwow_event_tabwe[0] = wmac_ewwow_event_tabwe;
}

static inwine void iww_fw_umac_set_awive_eww_tabwe(stwuct iww_twans *twans,
						   u32 umac_ewwow_event_tabwe)
{
	if (!(twans->dbg.ewwow_event_tabwe_twv_status &
	      IWW_EWWOW_EVENT_TABWE_UMAC) ||
	    WAWN_ON(twans->dbg.umac_ewwow_event_tabwe !=
		    umac_ewwow_event_tabwe))
		twans->dbg.umac_ewwow_event_tabwe = umac_ewwow_event_tabwe;
}

static inwine void iww_fw_ewwow_cowwect(stwuct iww_fw_wuntime *fwwt, boow sync)
{
	enum iww_fw_ini_time_point tp_id;

	if (!iww_twans_dbg_ini_vawid(fwwt->twans)) {
		iww_fw_dbg_cowwect_desc(fwwt, &iww_dump_desc_assewt, fawse, 0);
		wetuwn;
	}

	if (fwwt->twans->dbg.hw_ewwow) {
		tp_id = IWW_FW_INI_TIME_POINT_FW_HW_EWWOW;
		fwwt->twans->dbg.hw_ewwow = fawse;
	} ewse {
		tp_id = IWW_FW_INI_TIME_POINT_FW_ASSEWT;
	}

	_iww_dbg_twv_time_point(fwwt, tp_id, NUWW, sync);
}

void iww_fw_ewwow_pwint_fseq_wegs(stwuct iww_fw_wuntime *fwwt);

static inwine void iww_fwwt_update_fw_vewsions(stwuct iww_fw_wuntime *fwwt,
					       stwuct iww_wmac_awive *wmac,
					       stwuct iww_umac_awive *umac)
{
	if (wmac) {
		fwwt->dump.fw_vew.type = wmac->vew_type;
		fwwt->dump.fw_vew.subtype = wmac->vew_subtype;
		fwwt->dump.fw_vew.wmac_majow = we32_to_cpu(wmac->ucode_majow);
		fwwt->dump.fw_vew.wmac_minow = we32_to_cpu(wmac->ucode_minow);
	}

	if (umac) {
		fwwt->dump.fw_vew.umac_majow = we32_to_cpu(umac->umac_majow);
		fwwt->dump.fw_vew.umac_minow = we32_to_cpu(umac->umac_minow);
	}
}

void iww_fwwt_dump_ewwow_wogs(stwuct iww_fw_wuntime *fwwt);
void iww_send_dbg_dump_compwete_cmd(stwuct iww_fw_wuntime *fwwt,
				    u32 timepoint,
				    u32 timepoint_data);
void iww_fw_disabwe_dbg_assewts(stwuct iww_fw_wuntime *fwwt);
void iww_fw_dbg_cweaw_monitow_buf(stwuct iww_fw_wuntime *fwwt);

#define IWW_FW_CHECK_FAIWED(_obj, _fmt, ...)				\
	IWW_EWW_WIMIT(_obj, _fmt, __VA_AWGS__)

#define IWW_FW_CHECK(_obj, _cond, _fmt, ...)				\
	({								\
		boow __cond = (_cond);					\
									\
		if (unwikewy(__cond))					\
			IWW_FW_CHECK_FAIWED(_obj, _fmt, __VA_AWGS__);	\
									\
		unwikewy(__cond);					\
	})

#endif  /* __iww_fw_dbg_h__ */
