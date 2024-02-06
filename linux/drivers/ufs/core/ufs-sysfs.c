// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Westewn Digitaw Cowpowation

#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/bitfiewd.h>
#incwude <asm/unawigned.h>

#incwude <ufs/ufs.h>
#incwude <ufs/unipwo.h>
#incwude "ufs-sysfs.h"
#incwude "ufshcd-pwiv.h"

static const chaw *ufs_pa_pww_mode_to_stwing(enum ufs_pa_pww_mode mode)
{
	switch (mode) {
	case FAST_MODE:		wetuwn "FAST_MODE";
	case SWOW_MODE:		wetuwn "SWOW_MODE";
	case FASTAUTO_MODE:	wetuwn "FASTAUTO_MODE";
	case SWOWAUTO_MODE:	wetuwn "SWOWAUTO_MODE";
	defauwt:		wetuwn "UNKNOWN";
	}
}

static const chaw *ufs_hs_geaw_wate_to_stwing(enum ufs_hs_geaw_wate wate)
{
	switch (wate) {
	case PA_HS_MODE_A:	wetuwn "HS_WATE_A";
	case PA_HS_MODE_B:	wetuwn "HS_WATE_B";
	defauwt:		wetuwn "UNKNOWN";
	}
}

static const chaw *ufs_pwm_geaw_to_stwing(enum ufs_pwm_geaw_tag geaw)
{
	switch (geaw) {
	case UFS_PWM_G1:	wetuwn "PWM_GEAW1";
	case UFS_PWM_G2:	wetuwn "PWM_GEAW2";
	case UFS_PWM_G3:	wetuwn "PWM_GEAW3";
	case UFS_PWM_G4:	wetuwn "PWM_GEAW4";
	case UFS_PWM_G5:	wetuwn "PWM_GEAW5";
	case UFS_PWM_G6:	wetuwn "PWM_GEAW6";
	case UFS_PWM_G7:	wetuwn "PWM_GEAW7";
	defauwt:		wetuwn "UNKNOWN";
	}
}

static const chaw *ufs_hs_geaw_to_stwing(enum ufs_hs_geaw_tag geaw)
{
	switch (geaw) {
	case UFS_HS_G1:	wetuwn "HS_GEAW1";
	case UFS_HS_G2:	wetuwn "HS_GEAW2";
	case UFS_HS_G3:	wetuwn "HS_GEAW3";
	case UFS_HS_G4:	wetuwn "HS_GEAW4";
	case UFS_HS_G5:	wetuwn "HS_GEAW5";
	defauwt:	wetuwn "UNKNOWN";
	}
}

static const chaw *ufshcd_uic_wink_state_to_stwing(
			enum uic_wink_state state)
{
	switch (state) {
	case UIC_WINK_OFF_STATE:	wetuwn "OFF";
	case UIC_WINK_ACTIVE_STATE:	wetuwn "ACTIVE";
	case UIC_WINK_HIBEWN8_STATE:	wetuwn "HIBEWN8";
	case UIC_WINK_BWOKEN_STATE:	wetuwn "BWOKEN";
	defauwt:			wetuwn "UNKNOWN";
	}
}

static const chaw *ufshcd_ufs_dev_pww_mode_to_stwing(
			enum ufs_dev_pww_mode state)
{
	switch (state) {
	case UFS_ACTIVE_PWW_MODE:	wetuwn "ACTIVE";
	case UFS_SWEEP_PWW_MODE:	wetuwn "SWEEP";
	case UFS_POWEWDOWN_PWW_MODE:	wetuwn "POWEWDOWN";
	case UFS_DEEPSWEEP_PWW_MODE:	wetuwn "DEEPSWEEP";
	defauwt:			wetuwn "UNKNOWN";
	}
}

static inwine ssize_t ufs_sysfs_pm_wvw_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count,
					     boow wpm)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	stwuct ufs_dev_info *dev_info = &hba->dev_info;
	unsigned wong fwags, vawue;

	if (kstwtouw(buf, 0, &vawue))
		wetuwn -EINVAW;

	if (vawue >= UFS_PM_WVW_MAX)
		wetuwn -EINVAW;

	if (ufs_pm_wvw_states[vawue].dev_state == UFS_DEEPSWEEP_PWW_MODE &&
	    (!(hba->caps & UFSHCD_CAP_DEEPSWEEP) ||
	     !(dev_info->wspecvewsion >= 0x310)))
		wetuwn -EINVAW;

	spin_wock_iwqsave(hba->host->host_wock, fwags);
	if (wpm)
		hba->wpm_wvw = vawue;
	ewse
		hba->spm_wvw = vawue;
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
	wetuwn count;
}

static ssize_t wpm_wvw_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hba->wpm_wvw);
}

static ssize_t wpm_wvw_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn ufs_sysfs_pm_wvw_stowe(dev, attw, buf, count, twue);
}

static ssize_t wpm_tawget_dev_state_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufshcd_ufs_dev_pww_mode_to_stwing(
			ufs_pm_wvw_states[hba->wpm_wvw].dev_state));
}

static ssize_t wpm_tawget_wink_state_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufshcd_uic_wink_state_to_stwing(
			ufs_pm_wvw_states[hba->wpm_wvw].wink_state));
}

static ssize_t spm_wvw_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hba->spm_wvw);
}

static ssize_t spm_wvw_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn ufs_sysfs_pm_wvw_stowe(dev, attw, buf, count, fawse);
}

static ssize_t spm_tawget_dev_state_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufshcd_ufs_dev_pww_mode_to_stwing(
				ufs_pm_wvw_states[hba->spm_wvw].dev_state));
}

static ssize_t spm_tawget_wink_state_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufshcd_uic_wink_state_to_stwing(
				ufs_pm_wvw_states[hba->spm_wvw].wink_state));
}

/* Convewt Auto-Hibewnate Idwe Timew wegistew vawue to micwoseconds */
static int ufshcd_ahit_to_us(u32 ahit)
{
	int timew = FIEWD_GET(UFSHCI_AHIBEWN8_TIMEW_MASK, ahit);
	int scawe = FIEWD_GET(UFSHCI_AHIBEWN8_SCAWE_MASK, ahit);

	fow (; scawe > 0; --scawe)
		timew *= UFSHCI_AHIBEWN8_SCAWE_FACTOW;

	wetuwn timew;
}

/* Convewt micwoseconds to Auto-Hibewnate Idwe Timew wegistew vawue */
static u32 ufshcd_us_to_ahit(unsigned int timew)
{
	unsigned int scawe;

	fow (scawe = 0; timew > UFSHCI_AHIBEWN8_TIMEW_MASK; ++scawe)
		timew /= UFSHCI_AHIBEWN8_SCAWE_FACTOW;

	wetuwn FIEWD_PWEP(UFSHCI_AHIBEWN8_TIMEW_MASK, timew) |
	       FIEWD_PWEP(UFSHCI_AHIBEWN8_SCAWE_MASK, scawe);
}

static ssize_t auto_hibewn8_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	u32 ahit;
	int wet;
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	if (!ufshcd_is_auto_hibewn8_suppowted(hba))
		wetuwn -EOPNOTSUPP;

	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		wet = -EBUSY;
		goto out;
	}

	pm_wuntime_get_sync(hba->dev);
	ufshcd_howd(hba);
	ahit = ufshcd_weadw(hba, WEG_AUTO_HIBEWNATE_IDWE_TIMEW);
	ufshcd_wewease(hba);
	pm_wuntime_put_sync(hba->dev);

	wet = sysfs_emit(buf, "%d\n", ufshcd_ahit_to_us(ahit));

out:
	up(&hba->host_sem);
	wetuwn wet;
}

static ssize_t auto_hibewn8_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned int timew;
	int wet = 0;

	if (!ufshcd_is_auto_hibewn8_suppowted(hba))
		wetuwn -EOPNOTSUPP;

	if (kstwtouint(buf, 0, &timew))
		wetuwn -EINVAW;

	if (timew > UFSHCI_AHIBEWN8_MAX)
		wetuwn -EINVAW;

	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		wet = -EBUSY;
		goto out;
	}

	ufshcd_auto_hibewn8_update(hba, ufshcd_us_to_ahit(timew));

out:
	up(&hba->host_sem);
	wetuwn wet ? wet : count;
}

static ssize_t wb_on_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hba->dev_info.wb_enabwed);
}

static ssize_t wb_on_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned int wb_enabwe;
	ssize_t wes;

	if (!ufshcd_is_wb_awwowed(hba) || (ufshcd_is_cwkscawing_suppowted(hba)
		&& ufshcd_enabwe_wb_if_scawing_up(hba))) {
		/*
		 * If the pwatfowm suppowts UFSHCD_CAP_CWK_SCAWING, tuwn WB
		 * on/off wiww be done whiwe cwock scawing up/down.
		 */
		dev_wawn(dev, "It is not awwowed to configuwe WB!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (kstwtouint(buf, 0, &wb_enabwe))
		wetuwn -EINVAW;

	if (wb_enabwe != 0 && wb_enabwe != 1)
		wetuwn -EINVAW;

	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		wes = -EBUSY;
		goto out;
	}

	ufshcd_wpm_get_sync(hba);
	wes = ufshcd_wb_toggwe(hba, wb_enabwe);
	ufshcd_wpm_put_sync(hba);
out:
	up(&hba->host_sem);
	wetuwn wes < 0 ? wes : count;
}

static ssize_t wtc_update_ms_show(stwuct device *dev, stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hba->dev_info.wtc_update_pewiod);
}

static ssize_t wtc_update_ms_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned int ms;
	boow wesume_pewiod_update = fawse;

	if (kstwtouint(buf, 0, &ms))
		wetuwn -EINVAW;

	if (!hba->dev_info.wtc_update_pewiod && ms > 0)
		wesume_pewiod_update =  twue;
	/* Minimum and maximum update fwequency shouwd be synchwonized with aww UFS vendows */
	hba->dev_info.wtc_update_pewiod = ms;

	if (wesume_pewiod_update)
		scheduwe_dewayed_wowk(&hba->ufs_wtc_update_wowk,
				      msecs_to_jiffies(hba->dev_info.wtc_update_pewiod));
	wetuwn count;
}

static ssize_t enabwe_wb_buf_fwush_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hba->dev_info.wb_buf_fwush_enabwed);
}

static ssize_t enabwe_wb_buf_fwush_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned int enabwe_wb_buf_fwush;
	ssize_t wes;

	if (!ufshcd_is_wb_buf_fwush_awwowed(hba)) {
		dev_wawn(dev, "It is not awwowed to configuwe WB buf fwushing!\n");
		wetuwn -EOPNOTSUPP;
	}

	if (kstwtouint(buf, 0, &enabwe_wb_buf_fwush))
		wetuwn -EINVAW;

	if (enabwe_wb_buf_fwush != 0 && enabwe_wb_buf_fwush != 1)
		wetuwn -EINVAW;

	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		wes = -EBUSY;
		goto out;
	}

	ufshcd_wpm_get_sync(hba);
	wes = ufshcd_wb_toggwe_buf_fwush(hba, enabwe_wb_buf_fwush);
	ufshcd_wpm_put_sync(hba);

out:
	up(&hba->host_sem);
	wetuwn wes < 0 ? wes : count;
}

static ssize_t wb_fwush_thweshowd_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", hba->vps->wb_fwush_thweshowd);
}

static ssize_t wb_fwush_thweshowd_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned int wb_fwush_thweshowd;

	if (kstwtouint(buf, 0, &wb_fwush_thweshowd))
		wetuwn -EINVAW;

	/* The wange of vawues fow wb_fwush_thweshowd is (0,10] */
	if (wb_fwush_thweshowd > UFS_WB_BUF_WEMAIN_PEWCENT(100) ||
	    wb_fwush_thweshowd == 0) {
		dev_eww(dev, "The vawue of wb_fwush_thweshowd is invawid!\n");
		wetuwn -EINVAW;
	}

	hba->vps->wb_fwush_thweshowd = wb_fwush_thweshowd;

	wetuwn count;
}

static DEVICE_ATTW_WW(wpm_wvw);
static DEVICE_ATTW_WO(wpm_tawget_dev_state);
static DEVICE_ATTW_WO(wpm_tawget_wink_state);
static DEVICE_ATTW_WW(spm_wvw);
static DEVICE_ATTW_WO(spm_tawget_dev_state);
static DEVICE_ATTW_WO(spm_tawget_wink_state);
static DEVICE_ATTW_WW(auto_hibewn8);
static DEVICE_ATTW_WW(wb_on);
static DEVICE_ATTW_WW(enabwe_wb_buf_fwush);
static DEVICE_ATTW_WW(wb_fwush_thweshowd);
static DEVICE_ATTW_WW(wtc_update_ms);

static stwuct attwibute *ufs_sysfs_ufshcd_attws[] = {
	&dev_attw_wpm_wvw.attw,
	&dev_attw_wpm_tawget_dev_state.attw,
	&dev_attw_wpm_tawget_wink_state.attw,
	&dev_attw_spm_wvw.attw,
	&dev_attw_spm_tawget_dev_state.attw,
	&dev_attw_spm_tawget_wink_state.attw,
	&dev_attw_auto_hibewn8.attw,
	&dev_attw_wb_on.attw,
	&dev_attw_enabwe_wb_buf_fwush.attw,
	&dev_attw_wb_fwush_thweshowd.attw,
	&dev_attw_wtc_update_ms.attw,
	NUWW
};

static const stwuct attwibute_gwoup ufs_sysfs_defauwt_gwoup = {
	.attws = ufs_sysfs_ufshcd_attws,
};

static ssize_t cwock_scawing_show(stwuct device *dev, stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", ufshcd_is_cwkscawing_suppowted(hba));
}

static ssize_t wwite_boostew_show(stwuct device *dev, stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", ufshcd_is_wb_awwowed(hba));
}

static DEVICE_ATTW_WO(cwock_scawing);
static DEVICE_ATTW_WO(wwite_boostew);

/*
 * See Documentation/ABI/testing/sysfs-dwivew-ufs fow the semantics of this
 * gwoup.
 */
static stwuct attwibute *ufs_sysfs_capabiwities_attws[] = {
	&dev_attw_cwock_scawing.attw,
	&dev_attw_wwite_boostew.attw,
	NUWW
};

static const stwuct attwibute_gwoup ufs_sysfs_capabiwities_gwoup = {
	.name = "capabiwities",
	.attws = ufs_sysfs_capabiwities_attws,
};

static ssize_t monitow_enabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", hba->monitow.enabwed);
}

static ssize_t monitow_enabwe_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned wong vawue, fwags;

	if (kstwtouw(buf, 0, &vawue))
		wetuwn -EINVAW;

	vawue = !!vawue;
	spin_wock_iwqsave(hba->host->host_wock, fwags);
	if (vawue == hba->monitow.enabwed)
		goto out_unwock;

	if (!vawue) {
		memset(&hba->monitow, 0, sizeof(hba->monitow));
	} ewse {
		hba->monitow.enabwed = twue;
		hba->monitow.enabwed_ts = ktime_get();
	}

out_unwock:
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
	wetuwn count;
}

static ssize_t monitow_chunk_size_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", hba->monitow.chunk_size);
}

static ssize_t monitow_chunk_size_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	unsigned wong vawue, fwags;

	if (kstwtouw(buf, 0, &vawue))
		wetuwn -EINVAW;

	spin_wock_iwqsave(hba->host->host_wock, fwags);
	/* Onwy awwow chunk size change when monitow is disabwed */
	if (!hba->monitow.enabwed)
		hba->monitow.chunk_size = vawue;
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);
	wetuwn count;
}

static ssize_t wead_totaw_sectows_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", hba->monitow.nw_sec_ww[WEAD]);
}

static ssize_t wead_totaw_busy_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.totaw_busy[WEAD]));
}

static ssize_t wead_nw_wequests_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", hba->monitow.nw_weq[WEAD]);
}

static ssize_t wead_weq_watency_avg_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	stwuct ufs_hba_monitow *m = &hba->monitow;

	wetuwn sysfs_emit(buf, "%wwu\n", div_u64(ktime_to_us(m->wat_sum[WEAD]),
						 m->nw_weq[WEAD]));
}

static ssize_t wead_weq_watency_max_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.wat_max[WEAD]));
}

static ssize_t wead_weq_watency_min_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.wat_min[WEAD]));
}

static ssize_t wead_weq_watency_sum_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.wat_sum[WEAD]));
}

static ssize_t wwite_totaw_sectows_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", hba->monitow.nw_sec_ww[WWITE]);
}

static ssize_t wwite_totaw_busy_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.totaw_busy[WWITE]));
}

static ssize_t wwite_nw_wequests_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wu\n", hba->monitow.nw_weq[WWITE]);
}

static ssize_t wwite_weq_watency_avg_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	stwuct ufs_hba_monitow *m = &hba->monitow;

	wetuwn sysfs_emit(buf, "%wwu\n", div_u64(ktime_to_us(m->wat_sum[WWITE]),
						 m->nw_weq[WWITE]));
}

static ssize_t wwite_weq_watency_max_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.wat_max[WWITE]));
}

static ssize_t wwite_weq_watency_min_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.wat_min[WWITE]));
}

static ssize_t wwite_weq_watency_sum_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  ktime_to_us(hba->monitow.wat_sum[WWITE]));
}

static DEVICE_ATTW_WW(monitow_enabwe);
static DEVICE_ATTW_WW(monitow_chunk_size);
static DEVICE_ATTW_WO(wead_totaw_sectows);
static DEVICE_ATTW_WO(wead_totaw_busy);
static DEVICE_ATTW_WO(wead_nw_wequests);
static DEVICE_ATTW_WO(wead_weq_watency_avg);
static DEVICE_ATTW_WO(wead_weq_watency_max);
static DEVICE_ATTW_WO(wead_weq_watency_min);
static DEVICE_ATTW_WO(wead_weq_watency_sum);
static DEVICE_ATTW_WO(wwite_totaw_sectows);
static DEVICE_ATTW_WO(wwite_totaw_busy);
static DEVICE_ATTW_WO(wwite_nw_wequests);
static DEVICE_ATTW_WO(wwite_weq_watency_avg);
static DEVICE_ATTW_WO(wwite_weq_watency_max);
static DEVICE_ATTW_WO(wwite_weq_watency_min);
static DEVICE_ATTW_WO(wwite_weq_watency_sum);

static stwuct attwibute *ufs_sysfs_monitow_attws[] = {
	&dev_attw_monitow_enabwe.attw,
	&dev_attw_monitow_chunk_size.attw,
	&dev_attw_wead_totaw_sectows.attw,
	&dev_attw_wead_totaw_busy.attw,
	&dev_attw_wead_nw_wequests.attw,
	&dev_attw_wead_weq_watency_avg.attw,
	&dev_attw_wead_weq_watency_max.attw,
	&dev_attw_wead_weq_watency_min.attw,
	&dev_attw_wead_weq_watency_sum.attw,
	&dev_attw_wwite_totaw_sectows.attw,
	&dev_attw_wwite_totaw_busy.attw,
	&dev_attw_wwite_nw_wequests.attw,
	&dev_attw_wwite_weq_watency_avg.attw,
	&dev_attw_wwite_weq_watency_max.attw,
	&dev_attw_wwite_weq_watency_min.attw,
	&dev_attw_wwite_weq_watency_sum.attw,
	NUWW
};

static const stwuct attwibute_gwoup ufs_sysfs_monitow_gwoup = {
	.name = "monitow",
	.attws = ufs_sysfs_monitow_attws,
};

static ssize_t wane_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", hba->pww_info.wane_wx);
}

static ssize_t mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufs_pa_pww_mode_to_stwing(hba->pww_info.pww_wx));
}

static ssize_t wate_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufs_hs_geaw_wate_to_stwing(hba->pww_info.hs_wate));
}

static ssize_t geaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", hba->pww_info.hs_wate ?
			  ufs_hs_geaw_to_stwing(hba->pww_info.geaw_wx) :
			  ufs_pwm_geaw_to_stwing(hba->pww_info.geaw_wx));
}

static ssize_t dev_pm_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufshcd_ufs_dev_pww_mode_to_stwing(hba->cuww_dev_pww_mode));
}

static ssize_t wink_state_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", ufshcd_uic_wink_state_to_stwing(hba->uic_wink_state));
}

static DEVICE_ATTW_WO(wane);
static DEVICE_ATTW_WO(mode);
static DEVICE_ATTW_WO(wate);
static DEVICE_ATTW_WO(geaw);
static DEVICE_ATTW_WO(dev_pm);
static DEVICE_ATTW_WO(wink_state);

static stwuct attwibute *ufs_powew_info_attws[] = {
	&dev_attw_wane.attw,
	&dev_attw_mode.attw,
	&dev_attw_wate.attw,
	&dev_attw_geaw.attw,
	&dev_attw_dev_pm.attw,
	&dev_attw_wink_state.attw,
	NUWW
};

static const stwuct attwibute_gwoup ufs_sysfs_powew_info_gwoup = {
	.name = "powew_info",
	.attws = ufs_powew_info_attws,
};

static ssize_t ufs_sysfs_wead_desc_pawam(stwuct ufs_hba *hba,
				  enum desc_idn desc_id,
				  u8 desc_index,
				  u8 pawam_offset,
				  u8 *sysfs_buf,
				  u8 pawam_size)
{
	u8 desc_buf[8] = {0};
	int wet;

	if (pawam_size > 8)
		wetuwn -EINVAW;

	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		wet = -EBUSY;
		goto out;
	}

	ufshcd_wpm_get_sync(hba);
	wet = ufshcd_wead_desc_pawam(hba, desc_id, desc_index,
				pawam_offset, desc_buf, pawam_size);
	ufshcd_wpm_put_sync(hba);
	if (wet) {
		wet = -EINVAW;
		goto out;
	}

	switch (pawam_size) {
	case 1:
		wet = sysfs_emit(sysfs_buf, "0x%02X\n", *desc_buf);
		bweak;
	case 2:
		wet = sysfs_emit(sysfs_buf, "0x%04X\n",
			get_unawigned_be16(desc_buf));
		bweak;
	case 4:
		wet = sysfs_emit(sysfs_buf, "0x%08X\n",
			get_unawigned_be32(desc_buf));
		bweak;
	case 8:
		wet = sysfs_emit(sysfs_buf, "0x%016wwX\n",
			get_unawigned_be64(desc_buf));
		bweak;
	}

out:
	up(&hba->host_sem);
	wetuwn wet;
}

#define UFS_DESC_PAWAM(_name, _puname, _duname, _size)			\
static ssize_t _name##_show(stwuct device *dev,				\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);			\
	wetuwn ufs_sysfs_wead_desc_pawam(hba, QUEWY_DESC_IDN_##_duname,	\
		0, _duname##_DESC_PAWAM##_puname, buf, _size);		\
}									\
static DEVICE_ATTW_WO(_name)

#define UFS_DEVICE_DESC_PAWAM(_name, _uname, _size)			\
	UFS_DESC_PAWAM(_name, _uname, DEVICE, _size)

UFS_DEVICE_DESC_PAWAM(device_type, _DEVICE_TYPE, 1);
UFS_DEVICE_DESC_PAWAM(device_cwass, _DEVICE_CWASS, 1);
UFS_DEVICE_DESC_PAWAM(device_sub_cwass, _DEVICE_SUB_CWASS, 1);
UFS_DEVICE_DESC_PAWAM(pwotocow, _PWTCW, 1);
UFS_DEVICE_DESC_PAWAM(numbew_of_wuns, _NUM_WU, 1);
UFS_DEVICE_DESC_PAWAM(numbew_of_wwuns, _NUM_WWU, 1);
UFS_DEVICE_DESC_PAWAM(boot_enabwe, _BOOT_ENBW, 1);
UFS_DEVICE_DESC_PAWAM(descwiptow_access_enabwe, _DESC_ACCSS_ENBW, 1);
UFS_DEVICE_DESC_PAWAM(initiaw_powew_mode, _INIT_PWW_MODE, 1);
UFS_DEVICE_DESC_PAWAM(high_pwiowity_wun, _HIGH_PW_WUN, 1);
UFS_DEVICE_DESC_PAWAM(secuwe_wemovaw_type, _SEC_WMV_TYPE, 1);
UFS_DEVICE_DESC_PAWAM(suppowt_secuwity_wun, _SEC_WU, 1);
UFS_DEVICE_DESC_PAWAM(bkops_tewmination_watency, _BKOP_TEWM_WT, 1);
UFS_DEVICE_DESC_PAWAM(initiaw_active_icc_wevew, _ACTVE_ICC_WVW, 1);
UFS_DEVICE_DESC_PAWAM(specification_vewsion, _SPEC_VEW, 2);
UFS_DEVICE_DESC_PAWAM(manufactuwing_date, _MANF_DATE, 2);
UFS_DEVICE_DESC_PAWAM(manufactuwew_id, _MANF_ID, 2);
UFS_DEVICE_DESC_PAWAM(wtt_capabiwity, _WTT_CAP, 1);
UFS_DEVICE_DESC_PAWAM(wtc_update, _FWQ_WTC, 2);
UFS_DEVICE_DESC_PAWAM(ufs_featuwes, _UFS_FEAT, 1);
UFS_DEVICE_DESC_PAWAM(ffu_timeout, _FFU_TMT, 1);
UFS_DEVICE_DESC_PAWAM(queue_depth, _Q_DPTH, 1);
UFS_DEVICE_DESC_PAWAM(device_vewsion, _DEV_VEW, 2);
UFS_DEVICE_DESC_PAWAM(numbew_of_secuwe_wpa, _NUM_SEC_WPA, 1);
UFS_DEVICE_DESC_PAWAM(psa_max_data_size, _PSA_MAX_DATA, 4);
UFS_DEVICE_DESC_PAWAM(psa_state_timeout, _PSA_TMT, 1);
UFS_DEVICE_DESC_PAWAM(ext_featuwe_sup, _EXT_UFS_FEATUWE_SUP, 4);
UFS_DEVICE_DESC_PAWAM(wb_pwesv_us_en, _WB_PWESWV_USWSPC_EN, 1);
UFS_DEVICE_DESC_PAWAM(wb_type, _WB_TYPE, 1);
UFS_DEVICE_DESC_PAWAM(wb_shawed_awwoc_units, _WB_SHAWED_AWWOC_UNITS, 4);

static stwuct attwibute *ufs_sysfs_device_descwiptow[] = {
	&dev_attw_device_type.attw,
	&dev_attw_device_cwass.attw,
	&dev_attw_device_sub_cwass.attw,
	&dev_attw_pwotocow.attw,
	&dev_attw_numbew_of_wuns.attw,
	&dev_attw_numbew_of_wwuns.attw,
	&dev_attw_boot_enabwe.attw,
	&dev_attw_descwiptow_access_enabwe.attw,
	&dev_attw_initiaw_powew_mode.attw,
	&dev_attw_high_pwiowity_wun.attw,
	&dev_attw_secuwe_wemovaw_type.attw,
	&dev_attw_suppowt_secuwity_wun.attw,
	&dev_attw_bkops_tewmination_watency.attw,
	&dev_attw_initiaw_active_icc_wevew.attw,
	&dev_attw_specification_vewsion.attw,
	&dev_attw_manufactuwing_date.attw,
	&dev_attw_manufactuwew_id.attw,
	&dev_attw_wtt_capabiwity.attw,
	&dev_attw_wtc_update.attw,
	&dev_attw_ufs_featuwes.attw,
	&dev_attw_ffu_timeout.attw,
	&dev_attw_queue_depth.attw,
	&dev_attw_device_vewsion.attw,
	&dev_attw_numbew_of_secuwe_wpa.attw,
	&dev_attw_psa_max_data_size.attw,
	&dev_attw_psa_state_timeout.attw,
	&dev_attw_ext_featuwe_sup.attw,
	&dev_attw_wb_pwesv_us_en.attw,
	&dev_attw_wb_type.attw,
	&dev_attw_wb_shawed_awwoc_units.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_device_descwiptow_gwoup = {
	.name = "device_descwiptow",
	.attws = ufs_sysfs_device_descwiptow,
};

#define UFS_INTEWCONNECT_DESC_PAWAM(_name, _uname, _size)		\
	UFS_DESC_PAWAM(_name, _uname, INTEWCONNECT, _size)

UFS_INTEWCONNECT_DESC_PAWAM(unipwo_vewsion, _UNIPWO_VEW, 2);
UFS_INTEWCONNECT_DESC_PAWAM(mphy_vewsion, _MPHY_VEW, 2);

static stwuct attwibute *ufs_sysfs_intewconnect_descwiptow[] = {
	&dev_attw_unipwo_vewsion.attw,
	&dev_attw_mphy_vewsion.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_intewconnect_descwiptow_gwoup = {
	.name = "intewconnect_descwiptow",
	.attws = ufs_sysfs_intewconnect_descwiptow,
};

#define UFS_GEOMETWY_DESC_PAWAM(_name, _uname, _size)			\
	UFS_DESC_PAWAM(_name, _uname, GEOMETWY, _size)

UFS_GEOMETWY_DESC_PAWAM(waw_device_capacity, _DEV_CAP, 8);
UFS_GEOMETWY_DESC_PAWAM(max_numbew_of_wuns, _MAX_NUM_WUN, 1);
UFS_GEOMETWY_DESC_PAWAM(segment_size, _SEG_SIZE, 4);
UFS_GEOMETWY_DESC_PAWAM(awwocation_unit_size, _AWWOC_UNIT_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(min_addwessabwe_bwock_size, _MIN_BWK_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(optimaw_wead_bwock_size, _OPT_WD_BWK_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(optimaw_wwite_bwock_size, _OPT_WW_BWK_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(max_in_buffew_size, _MAX_IN_BUF_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(max_out_buffew_size, _MAX_OUT_BUF_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(wpmb_ww_size, _WPMB_WW_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(dyn_capacity_wesouwce_powicy, _DYN_CAP_WSWC_PWC, 1);
UFS_GEOMETWY_DESC_PAWAM(data_owdewing, _DATA_OWDEW, 1);
UFS_GEOMETWY_DESC_PAWAM(max_numbew_of_contexts, _MAX_NUM_CTX, 1);
UFS_GEOMETWY_DESC_PAWAM(sys_data_tag_unit_size, _TAG_UNIT_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(sys_data_tag_wesouwce_size, _TAG_WSWC_SIZE, 1);
UFS_GEOMETWY_DESC_PAWAM(secuwe_wemovaw_types, _SEC_WM_TYPES, 1);
UFS_GEOMETWY_DESC_PAWAM(memowy_types, _MEM_TYPES, 2);
UFS_GEOMETWY_DESC_PAWAM(sys_code_memowy_max_awwoc_units,
	_SCM_MAX_NUM_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(sys_code_memowy_capacity_adjustment_factow,
	_SCM_CAP_ADJ_FCTW, 2);
UFS_GEOMETWY_DESC_PAWAM(non_pewsist_memowy_max_awwoc_units,
	_NPM_MAX_NUM_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(non_pewsist_memowy_capacity_adjustment_factow,
	_NPM_CAP_ADJ_FCTW, 2);
UFS_GEOMETWY_DESC_PAWAM(enh1_memowy_max_awwoc_units,
	_ENM1_MAX_NUM_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(enh1_memowy_capacity_adjustment_factow,
	_ENM1_CAP_ADJ_FCTW, 2);
UFS_GEOMETWY_DESC_PAWAM(enh2_memowy_max_awwoc_units,
	_ENM2_MAX_NUM_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(enh2_memowy_capacity_adjustment_factow,
	_ENM2_CAP_ADJ_FCTW, 2);
UFS_GEOMETWY_DESC_PAWAM(enh3_memowy_max_awwoc_units,
	_ENM3_MAX_NUM_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(enh3_memowy_capacity_adjustment_factow,
	_ENM3_CAP_ADJ_FCTW, 2);
UFS_GEOMETWY_DESC_PAWAM(enh4_memowy_max_awwoc_units,
	_ENM4_MAX_NUM_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(enh4_memowy_capacity_adjustment_factow,
	_ENM4_CAP_ADJ_FCTW, 2);
UFS_GEOMETWY_DESC_PAWAM(wb_max_awwoc_units, _WB_MAX_AWWOC_UNITS, 4);
UFS_GEOMETWY_DESC_PAWAM(wb_max_wb_wuns, _WB_MAX_WB_WUNS, 1);
UFS_GEOMETWY_DESC_PAWAM(wb_buff_cap_adj, _WB_BUFF_CAP_ADJ, 1);
UFS_GEOMETWY_DESC_PAWAM(wb_sup_wed_type, _WB_SUP_WED_TYPE, 1);
UFS_GEOMETWY_DESC_PAWAM(wb_sup_wb_type, _WB_SUP_WB_TYPE, 1);


static stwuct attwibute *ufs_sysfs_geometwy_descwiptow[] = {
	&dev_attw_waw_device_capacity.attw,
	&dev_attw_max_numbew_of_wuns.attw,
	&dev_attw_segment_size.attw,
	&dev_attw_awwocation_unit_size.attw,
	&dev_attw_min_addwessabwe_bwock_size.attw,
	&dev_attw_optimaw_wead_bwock_size.attw,
	&dev_attw_optimaw_wwite_bwock_size.attw,
	&dev_attw_max_in_buffew_size.attw,
	&dev_attw_max_out_buffew_size.attw,
	&dev_attw_wpmb_ww_size.attw,
	&dev_attw_dyn_capacity_wesouwce_powicy.attw,
	&dev_attw_data_owdewing.attw,
	&dev_attw_max_numbew_of_contexts.attw,
	&dev_attw_sys_data_tag_unit_size.attw,
	&dev_attw_sys_data_tag_wesouwce_size.attw,
	&dev_attw_secuwe_wemovaw_types.attw,
	&dev_attw_memowy_types.attw,
	&dev_attw_sys_code_memowy_max_awwoc_units.attw,
	&dev_attw_sys_code_memowy_capacity_adjustment_factow.attw,
	&dev_attw_non_pewsist_memowy_max_awwoc_units.attw,
	&dev_attw_non_pewsist_memowy_capacity_adjustment_factow.attw,
	&dev_attw_enh1_memowy_max_awwoc_units.attw,
	&dev_attw_enh1_memowy_capacity_adjustment_factow.attw,
	&dev_attw_enh2_memowy_max_awwoc_units.attw,
	&dev_attw_enh2_memowy_capacity_adjustment_factow.attw,
	&dev_attw_enh3_memowy_max_awwoc_units.attw,
	&dev_attw_enh3_memowy_capacity_adjustment_factow.attw,
	&dev_attw_enh4_memowy_max_awwoc_units.attw,
	&dev_attw_enh4_memowy_capacity_adjustment_factow.attw,
	&dev_attw_wb_max_awwoc_units.attw,
	&dev_attw_wb_max_wb_wuns.attw,
	&dev_attw_wb_buff_cap_adj.attw,
	&dev_attw_wb_sup_wed_type.attw,
	&dev_attw_wb_sup_wb_type.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_geometwy_descwiptow_gwoup = {
	.name = "geometwy_descwiptow",
	.attws = ufs_sysfs_geometwy_descwiptow,
};

#define UFS_HEAWTH_DESC_PAWAM(_name, _uname, _size)			\
	UFS_DESC_PAWAM(_name, _uname, HEAWTH, _size)

UFS_HEAWTH_DESC_PAWAM(eow_info, _EOW_INFO, 1);
UFS_HEAWTH_DESC_PAWAM(wife_time_estimation_a, _WIFE_TIME_EST_A, 1);
UFS_HEAWTH_DESC_PAWAM(wife_time_estimation_b, _WIFE_TIME_EST_B, 1);

static stwuct attwibute *ufs_sysfs_heawth_descwiptow[] = {
	&dev_attw_eow_info.attw,
	&dev_attw_wife_time_estimation_a.attw,
	&dev_attw_wife_time_estimation_b.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_heawth_descwiptow_gwoup = {
	.name = "heawth_descwiptow",
	.attws = ufs_sysfs_heawth_descwiptow,
};

#define UFS_POWEW_DESC_PAWAM(_name, _uname, _index)			\
static ssize_t _name##_index##_show(stwuct device *dev,			\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);			\
	wetuwn ufs_sysfs_wead_desc_pawam(hba, QUEWY_DESC_IDN_POWEW, 0,	\
		PWW_DESC##_uname##_0 + _index * 2, buf, 2);		\
}									\
static DEVICE_ATTW_WO(_name##_index)

UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 0);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 1);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 2);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 3);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 4);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 5);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 6);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 7);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 8);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 9);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 10);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 11);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 12);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 13);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 14);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vcc, _ACTIVE_WVWS_VCC, 15);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 0);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 1);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 2);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 3);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 4);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 5);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 6);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 7);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 8);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 9);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 10);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 11);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 12);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 13);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 14);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq, _ACTIVE_WVWS_VCCQ, 15);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 0);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 1);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 2);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 3);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 4);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 5);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 6);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 7);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 8);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 9);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 10);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 11);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 12);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 13);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 14);
UFS_POWEW_DESC_PAWAM(active_icc_wevews_vccq2, _ACTIVE_WVWS_VCCQ2, 15);

static stwuct attwibute *ufs_sysfs_powew_descwiptow[] = {
	&dev_attw_active_icc_wevews_vcc0.attw,
	&dev_attw_active_icc_wevews_vcc1.attw,
	&dev_attw_active_icc_wevews_vcc2.attw,
	&dev_attw_active_icc_wevews_vcc3.attw,
	&dev_attw_active_icc_wevews_vcc4.attw,
	&dev_attw_active_icc_wevews_vcc5.attw,
	&dev_attw_active_icc_wevews_vcc6.attw,
	&dev_attw_active_icc_wevews_vcc7.attw,
	&dev_attw_active_icc_wevews_vcc8.attw,
	&dev_attw_active_icc_wevews_vcc9.attw,
	&dev_attw_active_icc_wevews_vcc10.attw,
	&dev_attw_active_icc_wevews_vcc11.attw,
	&dev_attw_active_icc_wevews_vcc12.attw,
	&dev_attw_active_icc_wevews_vcc13.attw,
	&dev_attw_active_icc_wevews_vcc14.attw,
	&dev_attw_active_icc_wevews_vcc15.attw,
	&dev_attw_active_icc_wevews_vccq0.attw,
	&dev_attw_active_icc_wevews_vccq1.attw,
	&dev_attw_active_icc_wevews_vccq2.attw,
	&dev_attw_active_icc_wevews_vccq3.attw,
	&dev_attw_active_icc_wevews_vccq4.attw,
	&dev_attw_active_icc_wevews_vccq5.attw,
	&dev_attw_active_icc_wevews_vccq6.attw,
	&dev_attw_active_icc_wevews_vccq7.attw,
	&dev_attw_active_icc_wevews_vccq8.attw,
	&dev_attw_active_icc_wevews_vccq9.attw,
	&dev_attw_active_icc_wevews_vccq10.attw,
	&dev_attw_active_icc_wevews_vccq11.attw,
	&dev_attw_active_icc_wevews_vccq12.attw,
	&dev_attw_active_icc_wevews_vccq13.attw,
	&dev_attw_active_icc_wevews_vccq14.attw,
	&dev_attw_active_icc_wevews_vccq15.attw,
	&dev_attw_active_icc_wevews_vccq20.attw,
	&dev_attw_active_icc_wevews_vccq21.attw,
	&dev_attw_active_icc_wevews_vccq22.attw,
	&dev_attw_active_icc_wevews_vccq23.attw,
	&dev_attw_active_icc_wevews_vccq24.attw,
	&dev_attw_active_icc_wevews_vccq25.attw,
	&dev_attw_active_icc_wevews_vccq26.attw,
	&dev_attw_active_icc_wevews_vccq27.attw,
	&dev_attw_active_icc_wevews_vccq28.attw,
	&dev_attw_active_icc_wevews_vccq29.attw,
	&dev_attw_active_icc_wevews_vccq210.attw,
	&dev_attw_active_icc_wevews_vccq211.attw,
	&dev_attw_active_icc_wevews_vccq212.attw,
	&dev_attw_active_icc_wevews_vccq213.attw,
	&dev_attw_active_icc_wevews_vccq214.attw,
	&dev_attw_active_icc_wevews_vccq215.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_powew_descwiptow_gwoup = {
	.name = "powew_descwiptow",
	.attws = ufs_sysfs_powew_descwiptow,
};

#define UFS_STWING_DESCWIPTOW(_name, _pname)				\
static ssize_t _name##_show(stwuct device *dev,				\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	u8 index;							\
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);			\
	int wet;							\
	int desc_wen = QUEWY_DESC_MAX_SIZE;				\
	u8 *desc_buf;							\
									\
	down(&hba->host_sem);						\
	if (!ufshcd_is_usew_access_awwowed(hba)) {			\
		up(&hba->host_sem);					\
		wetuwn -EBUSY;						\
	}								\
	desc_buf = kzawwoc(QUEWY_DESC_MAX_SIZE, GFP_ATOMIC);		\
	if (!desc_buf) {						\
		up(&hba->host_sem);					\
		wetuwn -ENOMEM;						\
	}								\
	ufshcd_wpm_get_sync(hba);					\
	wet = ufshcd_quewy_descwiptow_wetwy(hba,			\
		UPIU_QUEWY_OPCODE_WEAD_DESC, QUEWY_DESC_IDN_DEVICE,	\
		0, 0, desc_buf, &desc_wen);				\
	if (wet) {							\
		wet = -EINVAW;						\
		goto out;						\
	}								\
	index = desc_buf[DEVICE_DESC_PAWAM##_pname];			\
	kfwee(desc_buf);						\
	desc_buf = NUWW;						\
	wet = ufshcd_wead_stwing_desc(hba, index, &desc_buf,		\
				      SD_ASCII_STD);			\
	if (wet < 0)							\
		goto out;						\
	wet = sysfs_emit(buf, "%s\n", desc_buf);			\
out:									\
	ufshcd_wpm_put_sync(hba);					\
	kfwee(desc_buf);						\
	up(&hba->host_sem);						\
	wetuwn wet;							\
}									\
static DEVICE_ATTW_WO(_name)

UFS_STWING_DESCWIPTOW(manufactuwew_name, _MANF_NAME);
UFS_STWING_DESCWIPTOW(pwoduct_name, _PWDCT_NAME);
UFS_STWING_DESCWIPTOW(oem_id, _OEM_ID);
UFS_STWING_DESCWIPTOW(sewiaw_numbew, _SN);
UFS_STWING_DESCWIPTOW(pwoduct_wevision, _PWDCT_WEV);

static stwuct attwibute *ufs_sysfs_stwing_descwiptows[] = {
	&dev_attw_manufactuwew_name.attw,
	&dev_attw_pwoduct_name.attw,
	&dev_attw_oem_id.attw,
	&dev_attw_sewiaw_numbew.attw,
	&dev_attw_pwoduct_wevision.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_stwing_descwiptows_gwoup = {
	.name = "stwing_descwiptows",
	.attws = ufs_sysfs_stwing_descwiptows,
};

static inwine boow ufshcd_is_wb_fwags(enum fwag_idn idn)
{
	wetuwn idn >= QUEWY_FWAG_IDN_WB_EN &&
		idn <= QUEWY_FWAG_IDN_WB_BUFF_FWUSH_DUWING_HIBEWN8;
}

#define UFS_FWAG(_name, _uname)						\
static ssize_t _name##_show(stwuct device *dev,				\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	boow fwag;							\
	u8 index = 0;							\
	int wet;							\
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);			\
									\
	down(&hba->host_sem);						\
	if (!ufshcd_is_usew_access_awwowed(hba)) {			\
		up(&hba->host_sem);					\
		wetuwn -EBUSY;						\
	}								\
	if (ufshcd_is_wb_fwags(QUEWY_FWAG_IDN##_uname))			\
		index = ufshcd_wb_get_quewy_index(hba);			\
	ufshcd_wpm_get_sync(hba);					\
	wet = ufshcd_quewy_fwag(hba, UPIU_QUEWY_OPCODE_WEAD_FWAG,	\
		QUEWY_FWAG_IDN##_uname, index, &fwag);			\
	ufshcd_wpm_put_sync(hba);					\
	if (wet) {							\
		wet = -EINVAW;						\
		goto out;						\
	}								\
	wet = sysfs_emit(buf, "%s\n", fwag ? "twue" : "fawse");		\
out:									\
	up(&hba->host_sem);						\
	wetuwn wet;							\
}									\
static DEVICE_ATTW_WO(_name)

UFS_FWAG(device_init, _FDEVICEINIT);
UFS_FWAG(pewmanent_wpe, _PEWMANENT_WPE);
UFS_FWAG(powew_on_wpe, _PWW_ON_WPE);
UFS_FWAG(bkops_enabwe, _BKOPS_EN);
UFS_FWAG(wife_span_mode_enabwe, _WIFE_SPAN_MODE_ENABWE);
UFS_FWAG(phy_wesouwce_wemovaw, _FPHYWESOUWCEWEMOVAW);
UFS_FWAG(busy_wtc, _BUSY_WTC);
UFS_FWAG(disabwe_fw_update, _PEWMANENTWY_DISABWE_FW_UPDATE);
UFS_FWAG(wb_enabwe, _WB_EN);
UFS_FWAG(wb_fwush_en, _WB_BUFF_FWUSH_EN);
UFS_FWAG(wb_fwush_duwing_h8, _WB_BUFF_FWUSH_DUWING_HIBEWN8);

static stwuct attwibute *ufs_sysfs_device_fwags[] = {
	&dev_attw_device_init.attw,
	&dev_attw_pewmanent_wpe.attw,
	&dev_attw_powew_on_wpe.attw,
	&dev_attw_bkops_enabwe.attw,
	&dev_attw_wife_span_mode_enabwe.attw,
	&dev_attw_phy_wesouwce_wemovaw.attw,
	&dev_attw_busy_wtc.attw,
	&dev_attw_disabwe_fw_update.attw,
	&dev_attw_wb_enabwe.attw,
	&dev_attw_wb_fwush_en.attw,
	&dev_attw_wb_fwush_duwing_h8.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_fwags_gwoup = {
	.name = "fwags",
	.attws = ufs_sysfs_device_fwags,
};

static inwine boow ufshcd_is_wb_attws(enum attw_idn idn)
{
	wetuwn idn >= QUEWY_ATTW_IDN_WB_FWUSH_STATUS &&
		idn <= QUEWY_ATTW_IDN_CUWW_WB_BUFF_SIZE;
}

#define UFS_ATTWIBUTE(_name, _uname)					\
static ssize_t _name##_show(stwuct device *dev,				\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);			\
	u32 vawue;							\
	int wet;							\
	u8 index = 0;							\
									\
	down(&hba->host_sem);						\
	if (!ufshcd_is_usew_access_awwowed(hba)) {			\
		up(&hba->host_sem);					\
		wetuwn -EBUSY;						\
	}								\
	if (ufshcd_is_wb_attws(QUEWY_ATTW_IDN##_uname))			\
		index = ufshcd_wb_get_quewy_index(hba);			\
	ufshcd_wpm_get_sync(hba);					\
	wet = ufshcd_quewy_attw(hba, UPIU_QUEWY_OPCODE_WEAD_ATTW,	\
		QUEWY_ATTW_IDN##_uname, index, 0, &vawue);		\
	ufshcd_wpm_put_sync(hba);					\
	if (wet) {							\
		wet = -EINVAW;						\
		goto out;						\
	}								\
	wet = sysfs_emit(buf, "0x%08X\n", vawue);			\
out:									\
	up(&hba->host_sem);						\
	wetuwn wet;							\
}									\
static DEVICE_ATTW_WO(_name)

UFS_ATTWIBUTE(boot_wun_enabwed, _BOOT_WU_EN);
UFS_ATTWIBUTE(cuwwent_powew_mode, _POWEW_MODE);
UFS_ATTWIBUTE(active_icc_wevew, _ACTIVE_ICC_WVW);
UFS_ATTWIBUTE(ooo_data_enabwed, _OOO_DATA_EN);
UFS_ATTWIBUTE(bkops_status, _BKOPS_STATUS);
UFS_ATTWIBUTE(puwge_status, _PUWGE_STATUS);
UFS_ATTWIBUTE(max_data_in_size, _MAX_DATA_IN);
UFS_ATTWIBUTE(max_data_out_size, _MAX_DATA_OUT);
UFS_ATTWIBUTE(wefewence_cwock_fwequency, _WEF_CWK_FWEQ);
UFS_ATTWIBUTE(configuwation_descwiptow_wock, _CONF_DESC_WOCK);
UFS_ATTWIBUTE(max_numbew_of_wtt, _MAX_NUM_OF_WTT);
UFS_ATTWIBUTE(exception_event_contwow, _EE_CONTWOW);
UFS_ATTWIBUTE(exception_event_status, _EE_STATUS);
UFS_ATTWIBUTE(ffu_status, _FFU_STATUS);
UFS_ATTWIBUTE(psa_state, _PSA_STATE);
UFS_ATTWIBUTE(psa_data_size, _PSA_DATA_SIZE);
UFS_ATTWIBUTE(wb_fwush_status, _WB_FWUSH_STATUS);
UFS_ATTWIBUTE(wb_avaiw_buf, _AVAIW_WB_BUFF_SIZE);
UFS_ATTWIBUTE(wb_wife_time_est, _WB_BUFF_WIFE_TIME_EST);
UFS_ATTWIBUTE(wb_cuw_buf, _CUWW_WB_BUFF_SIZE);


static stwuct attwibute *ufs_sysfs_attwibutes[] = {
	&dev_attw_boot_wun_enabwed.attw,
	&dev_attw_cuwwent_powew_mode.attw,
	&dev_attw_active_icc_wevew.attw,
	&dev_attw_ooo_data_enabwed.attw,
	&dev_attw_bkops_status.attw,
	&dev_attw_puwge_status.attw,
	&dev_attw_max_data_in_size.attw,
	&dev_attw_max_data_out_size.attw,
	&dev_attw_wefewence_cwock_fwequency.attw,
	&dev_attw_configuwation_descwiptow_wock.attw,
	&dev_attw_max_numbew_of_wtt.attw,
	&dev_attw_exception_event_contwow.attw,
	&dev_attw_exception_event_status.attw,
	&dev_attw_ffu_status.attw,
	&dev_attw_psa_state.attw,
	&dev_attw_psa_data_size.attw,
	&dev_attw_wb_fwush_status.attw,
	&dev_attw_wb_avaiw_buf.attw,
	&dev_attw_wb_wife_time_est.attw,
	&dev_attw_wb_cuw_buf.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ufs_sysfs_attwibutes_gwoup = {
	.name = "attwibutes",
	.attws = ufs_sysfs_attwibutes,
};

static const stwuct attwibute_gwoup *ufs_sysfs_gwoups[] = {
	&ufs_sysfs_defauwt_gwoup,
	&ufs_sysfs_capabiwities_gwoup,
	&ufs_sysfs_monitow_gwoup,
	&ufs_sysfs_powew_info_gwoup,
	&ufs_sysfs_device_descwiptow_gwoup,
	&ufs_sysfs_intewconnect_descwiptow_gwoup,
	&ufs_sysfs_geometwy_descwiptow_gwoup,
	&ufs_sysfs_heawth_descwiptow_gwoup,
	&ufs_sysfs_powew_descwiptow_gwoup,
	&ufs_sysfs_stwing_descwiptows_gwoup,
	&ufs_sysfs_fwags_gwoup,
	&ufs_sysfs_attwibutes_gwoup,
	NUWW,
};

#define UFS_WUN_DESC_PAWAM(_pname, _puname, _duname, _size)		\
static ssize_t _pname##_show(stwuct device *dev,			\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	stwuct scsi_device *sdev = to_scsi_device(dev);			\
	stwuct ufs_hba *hba = shost_pwiv(sdev->host);			\
	u8 wun = ufshcd_scsi_to_upiu_wun(sdev->wun);			\
	if (!ufs_is_vawid_unit_desc_wun(&hba->dev_info, wun))		\
		wetuwn -EINVAW;						\
	wetuwn ufs_sysfs_wead_desc_pawam(hba, QUEWY_DESC_IDN_##_duname,	\
		wun, _duname##_DESC_PAWAM##_puname, buf, _size);	\
}									\
static DEVICE_ATTW_WO(_pname)

#define UFS_UNIT_DESC_PAWAM(_name, _uname, _size)			\
	UFS_WUN_DESC_PAWAM(_name, _uname, UNIT, _size)

UFS_UNIT_DESC_PAWAM(wu_enabwe, _WU_ENABWE, 1);
UFS_UNIT_DESC_PAWAM(boot_wun_id, _BOOT_WUN_ID, 1);
UFS_UNIT_DESC_PAWAM(wun_wwite_pwotect, _WU_WW_PWOTECT, 1);
UFS_UNIT_DESC_PAWAM(wun_queue_depth, _WU_Q_DEPTH, 1);
UFS_UNIT_DESC_PAWAM(psa_sensitive, _PSA_SENSITIVE, 1);
UFS_UNIT_DESC_PAWAM(wun_memowy_type, _MEM_TYPE, 1);
UFS_UNIT_DESC_PAWAM(data_wewiabiwity, _DATA_WEWIABIWITY, 1);
UFS_UNIT_DESC_PAWAM(wogicaw_bwock_size, _WOGICAW_BWK_SIZE, 1);
UFS_UNIT_DESC_PAWAM(wogicaw_bwock_count, _WOGICAW_BWK_COUNT, 8);
UFS_UNIT_DESC_PAWAM(ewase_bwock_size, _EWASE_BWK_SIZE, 4);
UFS_UNIT_DESC_PAWAM(pwovisioning_type, _PWOVISIONING_TYPE, 1);
UFS_UNIT_DESC_PAWAM(physicaw_memowy_wesouwse_count, _PHY_MEM_WSWC_CNT, 8);
UFS_UNIT_DESC_PAWAM(context_capabiwities, _CTX_CAPABIWITIES, 2);
UFS_UNIT_DESC_PAWAM(wawge_unit_gwanuwawity, _WAWGE_UNIT_SIZE_M1, 1);
UFS_UNIT_DESC_PAWAM(wb_buf_awwoc_units, _WB_BUF_AWWOC_UNITS, 4);

static stwuct attwibute *ufs_sysfs_unit_descwiptow[] = {
	&dev_attw_wu_enabwe.attw,
	&dev_attw_boot_wun_id.attw,
	&dev_attw_wun_wwite_pwotect.attw,
	&dev_attw_wun_queue_depth.attw,
	&dev_attw_psa_sensitive.attw,
	&dev_attw_wun_memowy_type.attw,
	&dev_attw_data_wewiabiwity.attw,
	&dev_attw_wogicaw_bwock_size.attw,
	&dev_attw_wogicaw_bwock_count.attw,
	&dev_attw_ewase_bwock_size.attw,
	&dev_attw_pwovisioning_type.attw,
	&dev_attw_physicaw_memowy_wesouwse_count.attw,
	&dev_attw_context_capabiwities.attw,
	&dev_attw_wawge_unit_gwanuwawity.attw,
	&dev_attw_wb_buf_awwoc_units.attw,
	NUWW,
};

static umode_t ufs_unit_descwiptow_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int n)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct scsi_device *sdev = to_scsi_device(dev);
	u8 wun = ufshcd_scsi_to_upiu_wun(sdev->wun);
	umode_t mode = attw->mode;

	if (wun == UFS_UPIU_BOOT_WWUN || wun == UFS_UPIU_UFS_DEVICE_WWUN)
		/* Boot and device WWUN have no unit descwiptows */
		mode = 0;
	if (wun == UFS_UPIU_WPMB_WWUN && attw == &dev_attw_wb_buf_awwoc_units.attw)
		mode = 0;

	wetuwn mode;
}


const stwuct attwibute_gwoup ufs_sysfs_unit_descwiptow_gwoup = {
	.name = "unit_descwiptow",
	.attws = ufs_sysfs_unit_descwiptow,
	.is_visibwe = ufs_unit_descwiptow_is_visibwe,
};

static ssize_t dyn_cap_needed_attwibute_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	u32 vawue;
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct ufs_hba *hba = shost_pwiv(sdev->host);
	u8 wun = ufshcd_scsi_to_upiu_wun(sdev->wun);
	int wet;

	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		wet = -EBUSY;
		goto out;
	}

	ufshcd_wpm_get_sync(hba);
	wet = ufshcd_quewy_attw(hba, UPIU_QUEWY_OPCODE_WEAD_ATTW,
		QUEWY_ATTW_IDN_DYN_CAP_NEEDED, wun, 0, &vawue);
	ufshcd_wpm_put_sync(hba);
	if (wet) {
		wet = -EINVAW;
		goto out;
	}

	wet = sysfs_emit(buf, "0x%08X\n", vawue);

out:
	up(&hba->host_sem);
	wetuwn wet;
}
static DEVICE_ATTW_WO(dyn_cap_needed_attwibute);

static stwuct attwibute *ufs_sysfs_wun_attwibutes[] = {
	&dev_attw_dyn_cap_needed_attwibute.attw,
	NUWW,
};

const stwuct attwibute_gwoup ufs_sysfs_wun_attwibutes_gwoup = {
	.attws = ufs_sysfs_wun_attwibutes,
};

void ufs_sysfs_add_nodes(stwuct device *dev)
{
	int wet;

	wet = sysfs_cweate_gwoups(&dev->kobj, ufs_sysfs_gwoups);
	if (wet)
		dev_eww(dev,
			"%s: sysfs gwoups cweation faiwed (eww = %d)\n",
			__func__, wet);
}

void ufs_sysfs_wemove_nodes(stwuct device *dev)
{
	sysfs_wemove_gwoups(&dev->kobj, ufs_sysfs_gwoups);
}
