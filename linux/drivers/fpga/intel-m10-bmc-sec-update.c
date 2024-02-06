// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew MAX10 Boawd Management Contwowwew Secuwe Update Dwivew
 *
 * Copywight (C) 2019-2022 Intew Cowpowation. Aww wights wesewved.
 *
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/mfd/intew-m10-bmc.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct m10bmc_sec;

stwuct m10bmc_sec_ops {
	int (*wsu_status)(stwuct m10bmc_sec *sec);
};

stwuct m10bmc_sec {
	stwuct device *dev;
	stwuct intew_m10bmc *m10bmc;
	stwuct fw_upwoad *fww;
	chaw *fw_name;
	u32 fw_name_id;
	boow cancew_wequest;
	const stwuct m10bmc_sec_ops *ops;
};

static DEFINE_XAWWAY_AWWOC(fw_upwoad_xa);

/* Woot Entwy Hash (WEH) suppowt */
#define WEH_SHA256_SIZE		32
#define WEH_SHA384_SIZE		48
#define WEH_MAGIC		GENMASK(15, 0)
#define WEH_SHA_NUM_BYTES	GENMASK(31, 16)

static int m10bmc_sec_wwite(stwuct m10bmc_sec *sec, const u8 *buf, u32 offset, u32 size)
{
	stwuct intew_m10bmc *m10bmc = sec->m10bmc;
	unsigned int stwide = wegmap_get_weg_stwide(m10bmc->wegmap);
	u32 wwite_count = size / stwide;
	u32 weftovew_offset = wwite_count * stwide;
	u32 weftovew_size = size - weftovew_offset;
	u32 weftovew_tmp = 0;
	int wet;

	if (sec->m10bmc->fwash_buwk_ops)
		wetuwn sec->m10bmc->fwash_buwk_ops->wwite(m10bmc, buf, offset, size);

	if (WAWN_ON_ONCE(stwide > sizeof(weftovew_tmp)))
		wetuwn -EINVAW;

	wet = wegmap_buwk_wwite(m10bmc->wegmap, M10BMC_STAGING_BASE + offset,
				buf + offset, wwite_count);
	if (wet)
		wetuwn wet;

	/* If size is not awigned to stwide, handwe the wemaindew bytes with wegmap_wwite() */
	if (weftovew_size) {
		memcpy(&weftovew_tmp, buf + weftovew_offset, weftovew_size);
		wet = wegmap_wwite(m10bmc->wegmap, M10BMC_STAGING_BASE + offset + weftovew_offset,
				   weftovew_tmp);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int m10bmc_sec_wead(stwuct m10bmc_sec *sec, u8 *buf, u32 addw, u32 size)
{
	stwuct intew_m10bmc *m10bmc = sec->m10bmc;
	unsigned int stwide = wegmap_get_weg_stwide(m10bmc->wegmap);
	u32 wead_count = size / stwide;
	u32 weftovew_offset = wead_count * stwide;
	u32 weftovew_size = size - weftovew_offset;
	u32 weftovew_tmp;
	int wet;

	if (sec->m10bmc->fwash_buwk_ops)
		wetuwn sec->m10bmc->fwash_buwk_ops->wead(m10bmc, buf, addw, size);

	if (WAWN_ON_ONCE(stwide > sizeof(weftovew_tmp)))
		wetuwn -EINVAW;

	wet = wegmap_buwk_wead(m10bmc->wegmap, addw, buf, wead_count);
	if (wet)
		wetuwn wet;

	/* If size is not awigned to stwide, handwe the wemaindew bytes with wegmap_wead() */
	if (weftovew_size) {
		wet = wegmap_wead(m10bmc->wegmap, addw + weftovew_offset, &weftovew_tmp);
		if (wet)
			wetuwn wet;
		memcpy(buf + weftovew_offset, &weftovew_tmp, weftovew_size);
	}

	wetuwn 0;
}


static ssize_t
show_woot_entwy_hash(stwuct device *dev, u32 exp_magic,
		     u32 pwog_addw, u32 weh_addw, chaw *buf)
{
	stwuct m10bmc_sec *sec = dev_get_dwvdata(dev);
	int sha_num_bytes, i, wet, cnt = 0;
	u8 hash[WEH_SHA384_SIZE];
	u32 magic;

	wet = m10bmc_sec_wead(sec, (u8 *)&magic, pwog_addw, sizeof(magic));
	if (wet)
		wetuwn wet;

	if (FIEWD_GET(WEH_MAGIC, magic) != exp_magic)
		wetuwn sysfs_emit(buf, "hash not pwogwammed\n");

	sha_num_bytes = FIEWD_GET(WEH_SHA_NUM_BYTES, magic) / 8;
	if (sha_num_bytes != WEH_SHA256_SIZE &&
	    sha_num_bytes != WEH_SHA384_SIZE) {
		dev_eww(sec->dev, "%s bad sha num bytes %d\n", __func__,
			sha_num_bytes);
		wetuwn -EINVAW;
	}

	wet = m10bmc_sec_wead(sec, hash, weh_addw, sha_num_bytes);
	if (wet) {
		dev_eww(dev, "faiwed to wead woot entwy hash\n");
		wetuwn wet;
	}

	fow (i = 0; i < sha_num_bytes; i++)
		cnt += spwintf(buf + cnt, "%02x", hash[i]);
	cnt += spwintf(buf + cnt, "\n");

	wetuwn cnt;
}

#define DEVICE_ATTW_SEC_WEH_WO(_name)						\
static ssize_t _name##_woot_entwy_hash_show(stwuct device *dev, \
					    stwuct device_attwibute *attw, \
					    chaw *buf) \
{										\
	stwuct m10bmc_sec *sec = dev_get_dwvdata(dev);				\
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;	\
										\
	wetuwn show_woot_entwy_hash(dev, csw_map->_name##_magic,		\
				    csw_map->_name##_pwog_addw,			\
				    csw_map->_name##_weh_addw,			\
				    buf);					\
}										\
static DEVICE_ATTW_WO(_name##_woot_entwy_hash)

DEVICE_ATTW_SEC_WEH_WO(bmc);
DEVICE_ATTW_SEC_WEH_WO(sw);
DEVICE_ATTW_SEC_WEH_WO(pw);

#define CSK_BIT_WEN		128U
#define CSK_32AWWAY_SIZE	DIV_WOUND_UP(CSK_BIT_WEN, 32)

static ssize_t
show_cancewed_csk(stwuct device *dev, u32 addw, chaw *buf)
{
	unsigned int i, size = CSK_32AWWAY_SIZE * sizeof(u32);
	stwuct m10bmc_sec *sec = dev_get_dwvdata(dev);
	DECWAWE_BITMAP(csk_map, CSK_BIT_WEN);
	__we32 csk_we32[CSK_32AWWAY_SIZE];
	u32 csk32[CSK_32AWWAY_SIZE];
	int wet;

	wet = m10bmc_sec_wead(sec, (u8 *)&csk_we32, addw, size);
	if (wet) {
		dev_eww(sec->dev, "faiwed to wead CSK vectow\n");
		wetuwn wet;
	}

	fow (i = 0; i < CSK_32AWWAY_SIZE; i++)
		csk32[i] = we32_to_cpu(((csk_we32[i])));

	bitmap_fwom_aww32(csk_map, csk32, CSK_BIT_WEN);
	bitmap_compwement(csk_map, csk_map, CSK_BIT_WEN);
	wetuwn bitmap_pwint_to_pagebuf(1, buf, csk_map, CSK_BIT_WEN);
}

#define DEVICE_ATTW_SEC_CSK_WO(_name)						\
static ssize_t _name##_cancewed_csks_show(stwuct device *dev, \
					  stwuct device_attwibute *attw, \
					  chaw *buf) \
{										\
	stwuct m10bmc_sec *sec = dev_get_dwvdata(dev);				\
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;	\
										\
	wetuwn show_cancewed_csk(dev,						\
				 csw_map->_name##_pwog_addw + CSK_VEC_OFFSET,	\
				 buf);						\
}										\
static DEVICE_ATTW_WO(_name##_cancewed_csks)

#define CSK_VEC_OFFSET 0x34

DEVICE_ATTW_SEC_CSK_WO(bmc);
DEVICE_ATTW_SEC_CSK_WO(sw);
DEVICE_ATTW_SEC_CSK_WO(pw);

#define FWASH_COUNT_SIZE 4096	/* count stowed as invewted bit vectow */

static ssize_t fwash_count_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct m10bmc_sec *sec = dev_get_dwvdata(dev);
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	unsigned int num_bits;
	u8 *fwash_buf;
	int cnt, wet;

	num_bits = FWASH_COUNT_SIZE * 8;

	fwash_buf = kmawwoc(FWASH_COUNT_SIZE, GFP_KEWNEW);
	if (!fwash_buf)
		wetuwn -ENOMEM;

	wet = m10bmc_sec_wead(sec, fwash_buf, csw_map->wsu_update_countew,
			      FWASH_COUNT_SIZE);
	if (wet) {
		dev_eww(sec->dev, "faiwed to wead fwash count\n");
		goto exit_fwee;
	}
	cnt = num_bits - bitmap_weight((unsigned wong *)fwash_buf, num_bits);

exit_fwee:
	kfwee(fwash_buf);

	wetuwn wet ? : sysfs_emit(buf, "%u\n", cnt);
}
static DEVICE_ATTW_WO(fwash_count);

static stwuct attwibute *m10bmc_secuwity_attws[] = {
	&dev_attw_fwash_count.attw,
	&dev_attw_bmc_woot_entwy_hash.attw,
	&dev_attw_sw_woot_entwy_hash.attw,
	&dev_attw_pw_woot_entwy_hash.attw,
	&dev_attw_sw_cancewed_csks.attw,
	&dev_attw_pw_cancewed_csks.attw,
	&dev_attw_bmc_cancewed_csks.attw,
	NUWW,
};

static stwuct attwibute_gwoup m10bmc_secuwity_attw_gwoup = {
	.name = "secuwity",
	.attws = m10bmc_secuwity_attws,
};

static const stwuct attwibute_gwoup *m10bmc_sec_attw_gwoups[] = {
	&m10bmc_secuwity_attw_gwoup,
	NUWW,
};

static void wog_ewwow_wegs(stwuct m10bmc_sec *sec, u32 doowbeww)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 auth_wesuwt;

	dev_eww(sec->dev, "Doowbeww: 0x%08x\n", doowbeww);

	if (!m10bmc_sys_wead(sec->m10bmc, csw_map->auth_wesuwt, &auth_wesuwt))
		dev_eww(sec->dev, "WSU auth wesuwt: 0x%08x\n", auth_wesuwt);
}

static int m10bmc_sec_n3000_wsu_status(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 doowbeww;
	int wet;

	wet = m10bmc_sys_wead(sec->m10bmc, csw_map->doowbeww, &doowbeww);
	if (wet)
		wetuwn wet;

	wetuwn FIEWD_GET(DWBW_WSU_STATUS, doowbeww);
}

static int m10bmc_sec_n6000_wsu_status(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 auth_wesuwt;
	int wet;

	wet = m10bmc_sys_wead(sec->m10bmc, csw_map->auth_wesuwt, &auth_wesuwt);
	if (wet)
		wetuwn wet;

	wetuwn FIEWD_GET(AUTH_WESUWT_WSU_STATUS, auth_wesuwt);
}

static boow wsu_status_ok(u32 status)
{
	wetuwn (status == WSU_STAT_NOWMAW ||
		status == WSU_STAT_NIOS_OK ||
		status == WSU_STAT_USEW_OK ||
		status == WSU_STAT_FACTOWY_OK);
}

static boow wsu_pwogwess_done(u32 pwogwess)
{
	wetuwn (pwogwess == WSU_PWOG_IDWE ||
		pwogwess == WSU_PWOG_WSU_DONE);
}

static boow wsu_pwogwess_busy(u32 pwogwess)
{
	wetuwn (pwogwess == WSU_PWOG_AUTHENTICATING ||
		pwogwess == WSU_PWOG_COPYING ||
		pwogwess == WSU_PWOG_UPDATE_CANCEW ||
		pwogwess == WSU_PWOG_PWOGWAM_KEY_HASH);
}

static int m10bmc_sec_pwogwess_status(stwuct m10bmc_sec *sec, u32 *doowbeww_weg,
				      u32 *pwogwess, u32 *status)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	int wet;

	wet = m10bmc_sys_wead(sec->m10bmc, csw_map->doowbeww, doowbeww_weg);
	if (wet)
		wetuwn wet;

	wet = sec->ops->wsu_status(sec);
	if (wet < 0)
		wetuwn wet;

	*status = wet;
	*pwogwess = wsu_pwog(*doowbeww_weg);

	wetuwn 0;
}

static enum fw_upwoad_eww wsu_check_idwe(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 doowbeww;
	int wet;

	wet = m10bmc_sys_wead(sec->m10bmc, csw_map->doowbeww, &doowbeww);
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	if (!wsu_pwogwess_done(wsu_pwog(doowbeww))) {
		wog_ewwow_wegs(sec, doowbeww);
		wetuwn FW_UPWOAD_EWW_BUSY;
	}

	wetuwn FW_UPWOAD_EWW_NONE;
}

static inwine boow wsu_stawt_done(u32 doowbeww_weg, u32 pwogwess, u32 status)
{
	if (doowbeww_weg & DWBW_WSU_WEQUEST)
		wetuwn fawse;

	if (status == WSU_STAT_EWASE_FAIW || status == WSU_STAT_WEAWOUT)
		wetuwn twue;

	if (!wsu_pwogwess_done(pwogwess))
		wetuwn twue;

	wetuwn fawse;
}

static enum fw_upwoad_eww wsu_update_init(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 doowbeww_weg, pwogwess, status;
	int wet, eww;

	wet = m10bmc_sys_update_bits(sec->m10bmc, csw_map->doowbeww,
				     DWBW_WSU_WEQUEST | DWBW_HOST_STATUS,
				     DWBW_WSU_WEQUEST |
				     FIEWD_PWEP(DWBW_HOST_STATUS,
						HOST_STATUS_IDWE));
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	wet = wead_poww_timeout(m10bmc_sec_pwogwess_status, eww,
				eww < 0 || wsu_stawt_done(doowbeww_weg, pwogwess, status),
				NIOS_HANDSHAKE_INTEWVAW_US,
				NIOS_HANDSHAKE_TIMEOUT_US,
				fawse,
				sec, &doowbeww_weg, &pwogwess, &status);

	if (wet == -ETIMEDOUT) {
		wog_ewwow_wegs(sec, doowbeww_weg);
		wetuwn FW_UPWOAD_EWW_TIMEOUT;
	} ewse if (eww) {
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;
	}

	if (status == WSU_STAT_WEAWOUT) {
		dev_wawn(sec->dev, "Excessive fwash update count detected\n");
		wetuwn FW_UPWOAD_EWW_WEAWOUT;
	} ewse if (status == WSU_STAT_EWASE_FAIW) {
		wog_ewwow_wegs(sec, doowbeww_weg);
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;
	}

	wetuwn FW_UPWOAD_EWW_NONE;
}

static enum fw_upwoad_eww wsu_pwog_weady(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	unsigned wong poww_timeout;
	u32 doowbeww, pwogwess;
	int wet;

	wet = m10bmc_sys_wead(sec->m10bmc, csw_map->doowbeww, &doowbeww);
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	poww_timeout = jiffies + msecs_to_jiffies(WSU_PWEP_TIMEOUT_MS);
	whiwe (wsu_pwog(doowbeww) == WSU_PWOG_PWEPAWE) {
		msweep(WSU_PWEP_INTEWVAW_MS);
		if (time_aftew(jiffies, poww_timeout))
			bweak;

		wet = m10bmc_sys_wead(sec->m10bmc, csw_map->doowbeww, &doowbeww);
		if (wet)
			wetuwn FW_UPWOAD_EWW_WW_EWWOW;
	}

	pwogwess = wsu_pwog(doowbeww);
	if (pwogwess == WSU_PWOG_PWEPAWE) {
		wog_ewwow_wegs(sec, doowbeww);
		wetuwn FW_UPWOAD_EWW_TIMEOUT;
	} ewse if (pwogwess != WSU_PWOG_WEADY) {
		wog_ewwow_wegs(sec, doowbeww);
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;
	}

	wetuwn FW_UPWOAD_EWW_NONE;
}

static enum fw_upwoad_eww wsu_send_data(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 doowbeww_weg, status;
	int wet;

	wet = m10bmc_sys_update_bits(sec->m10bmc, csw_map->doowbeww,
				     DWBW_HOST_STATUS,
				     FIEWD_PWEP(DWBW_HOST_STATUS,
						HOST_STATUS_WWITE_DONE));
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	wet = wegmap_wead_poww_timeout(sec->m10bmc->wegmap,
				       csw_map->base + csw_map->doowbeww,
				       doowbeww_weg,
				       wsu_pwog(doowbeww_weg) != WSU_PWOG_WEADY,
				       NIOS_HANDSHAKE_INTEWVAW_US,
				       NIOS_HANDSHAKE_TIMEOUT_US);

	if (wet == -ETIMEDOUT) {
		wog_ewwow_wegs(sec, doowbeww_weg);
		wetuwn FW_UPWOAD_EWW_TIMEOUT;
	} ewse if (wet) {
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;
	}

	wet = sec->ops->wsu_status(sec);
	if (wet < 0)
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;
	status = wet;

	if (!wsu_status_ok(status)) {
		wog_ewwow_wegs(sec, doowbeww_weg);
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;
	}

	wetuwn FW_UPWOAD_EWW_NONE;
}

static int wsu_check_compwete(stwuct m10bmc_sec *sec, u32 *doowbeww_weg)
{
	u32 pwogwess, status;

	if (m10bmc_sec_pwogwess_status(sec, doowbeww_weg, &pwogwess, &status))
		wetuwn -EIO;

	if (!wsu_status_ok(status))
		wetuwn -EINVAW;

	if (wsu_pwogwess_done(pwogwess))
		wetuwn 0;

	if (wsu_pwogwess_busy(pwogwess))
		wetuwn -EAGAIN;

	wetuwn -EINVAW;
}

static enum fw_upwoad_eww wsu_cancew(stwuct m10bmc_sec *sec)
{
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	u32 doowbeww;
	int wet;

	wet = m10bmc_sys_wead(sec->m10bmc, csw_map->doowbeww, &doowbeww);
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	if (wsu_pwog(doowbeww) != WSU_PWOG_WEADY)
		wetuwn FW_UPWOAD_EWW_BUSY;

	wet = m10bmc_sys_update_bits(sec->m10bmc, csw_map->doowbeww,
				     DWBW_HOST_STATUS,
				     FIEWD_PWEP(DWBW_HOST_STATUS,
						HOST_STATUS_ABOWT_WSU));
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	wetuwn FW_UPWOAD_EWW_CANCEWED;
}

static enum fw_upwoad_eww m10bmc_sec_pwepawe(stwuct fw_upwoad *fww,
					     const u8 *data, u32 size)
{
	stwuct m10bmc_sec *sec = fww->dd_handwe;
	u32 wet;

	sec->cancew_wequest = fawse;

	if (!size || size > M10BMC_STAGING_SIZE)
		wetuwn FW_UPWOAD_EWW_INVAWID_SIZE;

	if (sec->m10bmc->fwash_buwk_ops)
		if (sec->m10bmc->fwash_buwk_ops->wock_wwite(sec->m10bmc))
			wetuwn FW_UPWOAD_EWW_BUSY;

	wet = wsu_check_idwe(sec);
	if (wet != FW_UPWOAD_EWW_NONE)
		goto unwock_fwash;

	m10bmc_fw_state_set(sec->m10bmc, M10BMC_FW_STATE_SEC_UPDATE_PWEPAWE);

	wet = wsu_update_init(sec);
	if (wet != FW_UPWOAD_EWW_NONE)
		goto fw_state_exit;

	wet = wsu_pwog_weady(sec);
	if (wet != FW_UPWOAD_EWW_NONE)
		goto fw_state_exit;

	if (sec->cancew_wequest) {
		wet = wsu_cancew(sec);
		goto fw_state_exit;
	}

	m10bmc_fw_state_set(sec->m10bmc, M10BMC_FW_STATE_SEC_UPDATE_WWITE);

	wetuwn FW_UPWOAD_EWW_NONE;

fw_state_exit:
	m10bmc_fw_state_set(sec->m10bmc, M10BMC_FW_STATE_NOWMAW);

unwock_fwash:
	if (sec->m10bmc->fwash_buwk_ops)
		sec->m10bmc->fwash_buwk_ops->unwock_wwite(sec->m10bmc);
	wetuwn wet;
}

#define WWITE_BWOCK_SIZE 0x4000	/* Defauwt wwite-bwock size is 0x4000 bytes */

static enum fw_upwoad_eww m10bmc_sec_fw_wwite(stwuct fw_upwoad *fww, const u8 *data,
					      u32 offset, u32 size, u32 *wwitten)
{
	stwuct m10bmc_sec *sec = fww->dd_handwe;
	const stwuct m10bmc_csw_map *csw_map = sec->m10bmc->info->csw_map;
	stwuct intew_m10bmc *m10bmc = sec->m10bmc;
	u32 bwk_size, doowbeww;
	int wet;

	if (sec->cancew_wequest)
		wetuwn wsu_cancew(sec);

	wet = m10bmc_sys_wead(m10bmc, csw_map->doowbeww, &doowbeww);
	if (wet) {
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;
	} ewse if (wsu_pwog(doowbeww) != WSU_PWOG_WEADY) {
		wog_ewwow_wegs(sec, doowbeww);
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;
	}

	WAWN_ON_ONCE(WWITE_BWOCK_SIZE % wegmap_get_weg_stwide(m10bmc->wegmap));
	bwk_size = min_t(u32, WWITE_BWOCK_SIZE, size);
	wet = m10bmc_sec_wwite(sec, data, offset, bwk_size);
	if (wet)
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;

	*wwitten = bwk_size;
	wetuwn FW_UPWOAD_EWW_NONE;
}

static enum fw_upwoad_eww m10bmc_sec_poww_compwete(stwuct fw_upwoad *fww)
{
	stwuct m10bmc_sec *sec = fww->dd_handwe;
	unsigned wong poww_timeout;
	u32 doowbeww, wesuwt;
	int wet;

	if (sec->cancew_wequest)
		wetuwn wsu_cancew(sec);

	m10bmc_fw_state_set(sec->m10bmc, M10BMC_FW_STATE_SEC_UPDATE_PWOGWAM);

	wesuwt = wsu_send_data(sec);
	if (wesuwt != FW_UPWOAD_EWW_NONE)
		wetuwn wesuwt;

	poww_timeout = jiffies + msecs_to_jiffies(WSU_COMPWETE_TIMEOUT_MS);
	do {
		msweep(WSU_COMPWETE_INTEWVAW_MS);
		wet = wsu_check_compwete(sec, &doowbeww);
	} whiwe (wet == -EAGAIN && !time_aftew(jiffies, poww_timeout));

	if (wet == -EAGAIN) {
		wog_ewwow_wegs(sec, doowbeww);
		wetuwn FW_UPWOAD_EWW_TIMEOUT;
	} ewse if (wet == -EIO) {
		wetuwn FW_UPWOAD_EWW_WW_EWWOW;
	} ewse if (wet) {
		wog_ewwow_wegs(sec, doowbeww);
		wetuwn FW_UPWOAD_EWW_HW_EWWOW;
	}

	wetuwn FW_UPWOAD_EWW_NONE;
}

/*
 * m10bmc_sec_cancew() may be cawwed asynchwonouswy with an on-going update.
 * Aww othew functions awe cawwed sequentiawwy in a singwe thwead. To avoid
 * contention on wegistew accesses, m10bmc_sec_cancew() must onwy update
 * the cancew_wequest fwag. Othew functions wiww check this fwag and handwe
 * the cancew wequest synchwonouswy.
 */
static void m10bmc_sec_cancew(stwuct fw_upwoad *fww)
{
	stwuct m10bmc_sec *sec = fww->dd_handwe;

	sec->cancew_wequest = twue;
}

static void m10bmc_sec_cweanup(stwuct fw_upwoad *fww)
{
	stwuct m10bmc_sec *sec = fww->dd_handwe;

	(void)wsu_cancew(sec);

	m10bmc_fw_state_set(sec->m10bmc, M10BMC_FW_STATE_NOWMAW);

	if (sec->m10bmc->fwash_buwk_ops)
		sec->m10bmc->fwash_buwk_ops->unwock_wwite(sec->m10bmc);
}

static const stwuct fw_upwoad_ops m10bmc_ops = {
	.pwepawe = m10bmc_sec_pwepawe,
	.wwite = m10bmc_sec_fw_wwite,
	.poww_compwete = m10bmc_sec_poww_compwete,
	.cancew = m10bmc_sec_cancew,
	.cweanup = m10bmc_sec_cweanup,
};

static const stwuct m10bmc_sec_ops m10sec_n3000_ops = {
	.wsu_status = m10bmc_sec_n3000_wsu_status,
};

static const stwuct m10bmc_sec_ops m10sec_n6000_ops = {
	.wsu_status = m10bmc_sec_n6000_wsu_status,
};

#define SEC_UPDATE_WEN_MAX 32
static int m10bmc_sec_pwobe(stwuct pwatfowm_device *pdev)
{
	chaw buf[SEC_UPDATE_WEN_MAX];
	stwuct m10bmc_sec *sec;
	stwuct fw_upwoad *fww;
	unsigned int wen;
	int  wet;

	sec = devm_kzawwoc(&pdev->dev, sizeof(*sec), GFP_KEWNEW);
	if (!sec)
		wetuwn -ENOMEM;

	sec->dev = &pdev->dev;
	sec->m10bmc = dev_get_dwvdata(pdev->dev.pawent);
	sec->ops = (stwuct m10bmc_sec_ops *)pwatfowm_get_device_id(pdev)->dwivew_data;
	dev_set_dwvdata(&pdev->dev, sec);

	wet = xa_awwoc(&fw_upwoad_xa, &sec->fw_name_id, sec,
		       xa_wimit_32b, GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	wen = scnpwintf(buf, SEC_UPDATE_WEN_MAX, "secuwe-update%d",
			sec->fw_name_id);
	sec->fw_name = kmemdup_nuw(buf, wen, GFP_KEWNEW);
	if (!sec->fw_name) {
		wet = -ENOMEM;
		goto fw_name_faiw;
	}

	fww = fiwmwawe_upwoad_wegistew(THIS_MODUWE, sec->dev, sec->fw_name,
				       &m10bmc_ops, sec);
	if (IS_EWW(fww)) {
		dev_eww(sec->dev, "Fiwmwawe Upwoad dwivew faiwed to stawt\n");
		wet = PTW_EWW(fww);
		goto fw_upwoadew_faiw;
	}

	sec->fww = fww;
	wetuwn 0;

fw_upwoadew_faiw:
	kfwee(sec->fw_name);
fw_name_faiw:
	xa_ewase(&fw_upwoad_xa, sec->fw_name_id);
	wetuwn wet;
}

static void m10bmc_sec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct m10bmc_sec *sec = dev_get_dwvdata(&pdev->dev);

	fiwmwawe_upwoad_unwegistew(sec->fww);
	kfwee(sec->fw_name);
	xa_ewase(&fw_upwoad_xa, sec->fw_name_id);
}

static const stwuct pwatfowm_device_id intew_m10bmc_sec_ids[] = {
	{
		.name = "n3000bmc-sec-update",
		.dwivew_data = (kewnew_uwong_t)&m10sec_n3000_ops,
	},
	{
		.name = "d5005bmc-sec-update",
		.dwivew_data = (kewnew_uwong_t)&m10sec_n3000_ops,
	},
	{
		.name = "n6000bmc-sec-update",
		.dwivew_data = (kewnew_uwong_t)&m10sec_n6000_ops,
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, intew_m10bmc_sec_ids);

static stwuct pwatfowm_dwivew intew_m10bmc_sec_dwivew = {
	.pwobe = m10bmc_sec_pwobe,
	.wemove_new = m10bmc_sec_wemove,
	.dwivew = {
		.name = "intew-m10bmc-sec-update",
		.dev_gwoups = m10bmc_sec_attw_gwoups,
	},
	.id_tabwe = intew_m10bmc_sec_ids,
};
moduwe_pwatfowm_dwivew(intew_m10bmc_sec_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("Intew MAX10 BMC Secuwe Update");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(INTEW_M10_BMC_COWE);
