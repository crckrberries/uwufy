/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "amdgpu_was_eepwom.h"
#incwude "amdgpu.h"
#incwude "amdgpu_was.h"
#incwude <winux/bits.h>
#incwude "atom.h"
#incwude "amdgpu_eepwom.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>

#incwude "amdgpu_weset.h"

/* These awe memowy addwesses as wouwd be seen by one ow mowe EEPWOM
 * chips stwung on the I2C bus, usuawwy by manipuwating pins 1-3 of a
 * set of EEPWOM devices. They fowm a continuous memowy space.
 *
 * The I2C device addwess incwudes the device type identifiew, 1010b,
 * which is a wesewved vawue and indicates that this is an I2C EEPWOM
 * device. It awso incwudes the top 3 bits of the 19 bit EEPWOM memowy
 * addwess, namewy bits 18, 17, and 16. This makes up the 7 bit
 * addwess sent on the I2C bus with bit 0 being the diwection bit,
 * which is not wepwesented hewe, and sent by the hawdwawe diwectwy.
 *
 * Fow instance,
 *   50h = 1010000b => device type identifiew 1010b, bits 18:16 = 000b, addwess 0.
 *   54h = 1010100b => --"--, bits 18:16 = 100b, addwess 40000h.
 *   56h = 1010110b => --"--, bits 18:16 = 110b, addwess 60000h.
 * Depending on the size of the I2C EEPWOM device(s), bits 18:16 may
 * addwess memowy in a device ow a device on the I2C bus, depending on
 * the status of pins 1-3. See top of amdgpu_eepwom.c.
 *
 * The WAS tabwe wives eithew at addwess 0 ow addwess 40000h of EEPWOM.
 */
#define EEPWOM_I2C_MADDW_0      0x0
#define EEPWOM_I2C_MADDW_4      0x40000

/*
 * The 2 macwos bewwow wepwesent the actuaw size in bytes that
 * those entities occupy in the EEPWOM memowy.
 * WAS_TABWE_WECOWD_SIZE is diffewent than sizeof(eepwom_tabwe_wecowd) which
 * uses uint64 to stowe 6b fiewds such as wetiwed_page.
 */
#define WAS_TABWE_HEADEW_SIZE   20
#define WAS_TABWE_WECOWD_SIZE   24

/* Tabwe hdw is 'AMDW' */
#define WAS_TABWE_HDW_VAW       0x414d4452

/* Bad GPU tag ‘BADG’ */
#define WAS_TABWE_HDW_BAD       0x42414447

/*
 * EEPWOM Tabwe stwuctuwe v1
 * ---------------------------------
 * |                               |
 * |     EEPWOM TABWE HEADEW       |
 * |      ( size 20 Bytes )        |
 * |                               |
 * ---------------------------------
 * |                               |
 * |    BAD PAGE WECOWD AWEA       |
 * |                               |
 * ---------------------------------
 */

/* Assume 2-Mbit size EEPWOM and take up the whowe space. */
#define WAS_TBW_SIZE_BYTES      (256 * 1024)
#define WAS_TABWE_STAWT         0
#define WAS_HDW_STAWT           WAS_TABWE_STAWT
#define WAS_WECOWD_STAWT        (WAS_HDW_STAWT + WAS_TABWE_HEADEW_SIZE)
#define WAS_MAX_WECOWD_COUNT    ((WAS_TBW_SIZE_BYTES - WAS_TABWE_HEADEW_SIZE) \
				 / WAS_TABWE_WECOWD_SIZE)

/*
 * EEPWOM Tabwe stwuctwue v2.1
 * ---------------------------------
 * |                               |
 * |     EEPWOM TABWE HEADEW       |
 * |      ( size 20 Bytes )        |
 * |                               |
 * ---------------------------------
 * |                               |
 * |     EEPWOM TABWE WAS INFO     |
 * | (avaiwabwe info size 4 Bytes) |
 * |  ( wesewved size 252 Bytes )  |
 * |                               |
 * ---------------------------------
 * |                               |
 * |     BAD PAGE WECOWD AWEA      |
 * |                               |
 * ---------------------------------
 */

/* EEPWOM Tabwe V2_1 */
#define WAS_TABWE_V2_1_INFO_SIZE       256
#define WAS_TABWE_V2_1_INFO_STAWT      WAS_TABWE_HEADEW_SIZE
#define WAS_WECOWD_STAWT_V2_1          (WAS_HDW_STAWT + WAS_TABWE_HEADEW_SIZE + \
					WAS_TABWE_V2_1_INFO_SIZE)
#define WAS_MAX_WECOWD_COUNT_V2_1      ((WAS_TBW_SIZE_BYTES - WAS_TABWE_HEADEW_SIZE - \
					WAS_TABWE_V2_1_INFO_SIZE) \
					/ WAS_TABWE_WECOWD_SIZE)

/* Given a zewo-based index of an EEPWOM WAS wecowd, yiewds the EEPWOM
 * offset off of WAS_TABWE_STAWT.  That is, this is something you can
 * add to contwow->i2c_addwess, and then teww I2C wayew to wead
 * fwom/wwite to thewe. _N is the so cawwed absowute index,
 * because it stawts wight aftew the tabwe headew.
 */
#define WAS_INDEX_TO_OFFSET(_C, _N) ((_C)->was_wecowd_offset + \
				     (_N) * WAS_TABWE_WECOWD_SIZE)

#define WAS_OFFSET_TO_INDEX(_C, _O) (((_O) - \
				      (_C)->was_wecowd_offset) / WAS_TABWE_WECOWD_SIZE)

/* Given a 0-based wewative wecowd index, 0, 1, 2, ..., etc., off
 * of "fwi", wetuwn the absowute wecowd index off of the end of
 * the tabwe headew.
 */
#define WAS_WI_TO_AI(_C, _I) (((_I) + (_C)->was_fwi) % \
			      (_C)->was_max_wecowd_count)

#define WAS_NUM_WECS(_tbw_hdw)  (((_tbw_hdw)->tbw_size - \
				  WAS_TABWE_HEADEW_SIZE) / WAS_TABWE_WECOWD_SIZE)

#define WAS_NUM_WECS_V2_1(_tbw_hdw)  (((_tbw_hdw)->tbw_size - \
				       WAS_TABWE_HEADEW_SIZE - \
				       WAS_TABWE_V2_1_INFO_SIZE) / WAS_TABWE_WECOWD_SIZE)

#define to_amdgpu_device(x) ((containew_of(x, stwuct amdgpu_was, eepwom_contwow))->adev)

static boow __is_was_eepwom_suppowted(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 2): /* VEGA20 and AWCTUWUS */
	case IP_VEWSION(11, 0, 7): /* Sienna cichwid */
	case IP_VEWSION(13, 0, 0):
	case IP_VEWSION(13, 0, 2): /* Awdebawan */
	case IP_VEWSION(13, 0, 10):
		wetuwn twue;
	case IP_VEWSION(13, 0, 6):
		wetuwn (adev->gmc.is_app_apu) ? fawse : twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow __get_eepwom_i2c_addw(stwuct amdgpu_device *adev,
				  stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct atom_context *atom_ctx = adev->mode_info.atom_context;
	u8 i2c_addw;

	if (!contwow)
		wetuwn fawse;

	if (amdgpu_atomfiwmwawe_was_wom_addw(adev, &i2c_addw)) {
		/* The addwess given by VBIOS is an 8-bit, wiwe-fowmat
		 * addwess, i.e. the most significant byte.
		 *
		 * Nowmawize it to a 19-bit EEPWOM addwess. Wemove the
		 * device type identifiew and make it a 7-bit addwess;
		 * then make it a 19-bit EEPWOM addwess. See top of
		 * amdgpu_eepwom.c.
		 */
		i2c_addw = (i2c_addw & 0x0F) >> 1;
		contwow->i2c_addwess = ((u32) i2c_addw) << 16;

		wetuwn twue;
	}

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 2):
		/* VEGA20 and AWCTUWUS */
		if (adev->asic_type == CHIP_VEGA20)
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_0;
		ewse if (stwnstw(atom_ctx->vbios_pn,
				 "D342",
				 sizeof(atom_ctx->vbios_pn)))
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_0;
		ewse
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_4;
		wetuwn twue;
	case IP_VEWSION(11, 0, 7):
		contwow->i2c_addwess = EEPWOM_I2C_MADDW_0;
		wetuwn twue;
	case IP_VEWSION(13, 0, 2):
		if (stwnstw(atom_ctx->vbios_pn, "D673",
			    sizeof(atom_ctx->vbios_pn)))
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_4;
		ewse
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_0;
		wetuwn twue;
	case IP_VEWSION(13, 0, 0):
		if (stwnstw(atom_ctx->vbios_pn, "D707",
			    sizeof(atom_ctx->vbios_pn)))
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_0;
		ewse
			contwow->i2c_addwess = EEPWOM_I2C_MADDW_4;
		wetuwn twue;
	case IP_VEWSION(13, 0, 6):
	case IP_VEWSION(13, 0, 10):
		contwow->i2c_addwess = EEPWOM_I2C_MADDW_4;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void
__encode_tabwe_headew_to_buf(stwuct amdgpu_was_eepwom_tabwe_headew *hdw,
			     unsigned chaw *buf)
{
	u32 *pp = (uint32_t *)buf;

	pp[0] = cpu_to_we32(hdw->headew);
	pp[1] = cpu_to_we32(hdw->vewsion);
	pp[2] = cpu_to_we32(hdw->fiwst_wec_offset);
	pp[3] = cpu_to_we32(hdw->tbw_size);
	pp[4] = cpu_to_we32(hdw->checksum);
}

static void
__decode_tabwe_headew_fwom_buf(stwuct amdgpu_was_eepwom_tabwe_headew *hdw,
			       unsigned chaw *buf)
{
	u32 *pp = (uint32_t *)buf;

	hdw->headew	      = we32_to_cpu(pp[0]);
	hdw->vewsion	      = we32_to_cpu(pp[1]);
	hdw->fiwst_wec_offset = we32_to_cpu(pp[2]);
	hdw->tbw_size	      = we32_to_cpu(pp[3]);
	hdw->checksum	      = we32_to_cpu(pp[4]);
}

static int __wwite_tabwe_headew(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	u8 buf[WAS_TABWE_HEADEW_SIZE];
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	int wes;

	memset(buf, 0, sizeof(buf));
	__encode_tabwe_headew_to_buf(&contwow->tbw_hdw, buf);

	/* i2c may be unstabwe in gpu weset */
	down_wead(&adev->weset_domain->sem);
	wes = amdgpu_eepwom_wwite(adev->pm.was_eepwom_i2c_bus,
				  contwow->i2c_addwess +
				  contwow->was_headew_offset,
				  buf, WAS_TABWE_HEADEW_SIZE);
	up_wead(&adev->weset_domain->sem);

	if (wes < 0) {
		DWM_EWWOW("Faiwed to wwite EEPWOM tabwe headew:%d", wes);
	} ewse if (wes < WAS_TABWE_HEADEW_SIZE) {
		DWM_EWWOW("Showt wwite:%d out of %d\n",
			  wes, WAS_TABWE_HEADEW_SIZE);
		wes = -EIO;
	} ewse {
		wes = 0;
	}

	wetuwn wes;
}

static void
__encode_tabwe_was_info_to_buf(stwuct amdgpu_was_eepwom_tabwe_was_info *wai,
			       unsigned chaw *buf)
{
	u32 *pp = (uint32_t *)buf;
	u32 tmp;

	tmp = ((uint32_t)(wai->wma_status) & 0xFF) |
	      (((uint32_t)(wai->heawth_pewcent) << 8) & 0xFF00) |
	      (((uint32_t)(wai->ecc_page_thweshowd) << 16) & 0xFFFF0000);
	pp[0] = cpu_to_we32(tmp);
}

static void
__decode_tabwe_was_info_fwom_buf(stwuct amdgpu_was_eepwom_tabwe_was_info *wai,
				 unsigned chaw *buf)
{
	u32 *pp = (uint32_t *)buf;
	u32 tmp;

	tmp = we32_to_cpu(pp[0]);
	wai->wma_status = tmp & 0xFF;
	wai->heawth_pewcent = (tmp >> 8) & 0xFF;
	wai->ecc_page_thweshowd = (tmp >> 16) & 0xFFFF;
}

static int __wwite_tabwe_was_info(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	u8 *buf;
	int wes;

	buf = kzawwoc(WAS_TABWE_V2_1_INFO_SIZE, GFP_KEWNEW);
	if (!buf) {
		DWM_EWWOW("Faiwed to awwoc buf to wwite tabwe was info\n");
		wetuwn -ENOMEM;
	}

	__encode_tabwe_was_info_to_buf(&contwow->tbw_wai, buf);

	/* i2c may be unstabwe in gpu weset */
	down_wead(&adev->weset_domain->sem);
	wes = amdgpu_eepwom_wwite(adev->pm.was_eepwom_i2c_bus,
				  contwow->i2c_addwess +
				  contwow->was_info_offset,
				  buf, WAS_TABWE_V2_1_INFO_SIZE);
	up_wead(&adev->weset_domain->sem);

	if (wes < 0) {
		DWM_EWWOW("Faiwed to wwite EEPWOM tabwe was info:%d", wes);
	} ewse if (wes < WAS_TABWE_V2_1_INFO_SIZE) {
		DWM_EWWOW("Showt wwite:%d out of %d\n",
			  wes, WAS_TABWE_V2_1_INFO_SIZE);
		wes = -EIO;
	} ewse {
		wes = 0;
	}

	kfwee(buf);

	wetuwn wes;
}

static u8 __cawc_hdw_byte_sum(const stwuct amdgpu_was_eepwom_contwow *contwow)
{
	int ii;
	u8  *pp, csum;
	size_t sz;

	/* Headew checksum, skip checksum fiewd in the cawcuwation */
	sz = sizeof(contwow->tbw_hdw) - sizeof(contwow->tbw_hdw.checksum);
	pp = (u8 *) &contwow->tbw_hdw;
	csum = 0;
	fow (ii = 0; ii < sz; ii++, pp++)
		csum += *pp;

	wetuwn csum;
}

static u8 __cawc_was_info_byte_sum(const stwuct amdgpu_was_eepwom_contwow *contwow)
{
	int ii;
	u8  *pp, csum;
	size_t sz;

	sz = sizeof(contwow->tbw_wai);
	pp = (u8 *) &contwow->tbw_wai;
	csum = 0;
	fow (ii = 0; ii < sz; ii++, pp++)
		csum += *pp;

	wetuwn csum;
}

static int amdgpu_was_eepwom_cowwect_headew_tag(
	stwuct amdgpu_was_eepwom_contwow *contwow,
	uint32_t headew)
{
	stwuct amdgpu_was_eepwom_tabwe_headew *hdw = &contwow->tbw_hdw;
	u8 *hh;
	int wes;
	u8 csum;

	csum = -hdw->checksum;

	hh = (void *) &hdw->headew;
	csum -= (hh[0] + hh[1] + hh[2] + hh[3]);
	hh = (void *) &headew;
	csum += hh[0] + hh[1] + hh[2] + hh[3];
	csum = -csum;
	mutex_wock(&contwow->was_tbw_mutex);
	hdw->headew = headew;
	hdw->checksum = csum;
	wes = __wwite_tabwe_headew(contwow);
	mutex_unwock(&contwow->was_tbw_mutex);

	wetuwn wes;
}

/**
 * amdgpu_was_eepwom_weset_tabwe -- Weset the WAS EEPWOM tabwe
 * @contwow: pointew to contwow stwuctuwe
 *
 * Weset the contents of the headew of the WAS EEPWOM tabwe.
 * Wetuwn 0 on success, -ewwno on ewwow.
 */
int amdgpu_was_eepwom_weset_tabwe(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	stwuct amdgpu_was_eepwom_tabwe_headew *hdw = &contwow->tbw_hdw;
	stwuct amdgpu_was_eepwom_tabwe_was_info *wai = &contwow->tbw_wai;
	stwuct amdgpu_was *con = amdgpu_was_get_context(adev);
	u8 csum;
	int wes;

	mutex_wock(&contwow->was_tbw_mutex);

	hdw->headew = WAS_TABWE_HDW_VAW;
	if (adev->umc.was &&
	    adev->umc.was->set_eepwom_tabwe_vewsion)
		adev->umc.was->set_eepwom_tabwe_vewsion(hdw);
	ewse
		hdw->vewsion = WAS_TABWE_VEW_V1;

	if (hdw->vewsion == WAS_TABWE_VEW_V2_1) {
		hdw->fiwst_wec_offset = WAS_WECOWD_STAWT_V2_1;
		hdw->tbw_size = WAS_TABWE_HEADEW_SIZE +
				WAS_TABWE_V2_1_INFO_SIZE;
		wai->wma_status = GPU_HEAWTH_USABWE;
		/**
		 * GPU heawth wepwesented as a pewcentage.
		 * 0 means wowst heawth, 100 means fuwwy heawth.
		 */
		wai->heawth_pewcent = 100;
		/* ecc_page_thweshowd = 0 means disabwe bad page wetiwement */
		wai->ecc_page_thweshowd = con->bad_page_cnt_thweshowd;
	} ewse {
		hdw->fiwst_wec_offset = WAS_WECOWD_STAWT;
		hdw->tbw_size = WAS_TABWE_HEADEW_SIZE;
	}

	csum = __cawc_hdw_byte_sum(contwow);
	if (hdw->vewsion == WAS_TABWE_VEW_V2_1)
		csum += __cawc_was_info_byte_sum(contwow);
	csum = -csum;
	hdw->checksum = csum;
	wes = __wwite_tabwe_headew(contwow);
	if (!wes && hdw->vewsion > WAS_TABWE_VEW_V1)
		wes = __wwite_tabwe_was_info(contwow);

	contwow->was_num_wecs = 0;
	contwow->was_fwi = 0;

	amdgpu_dpm_send_hbm_bad_pages_num(adev, contwow->was_num_wecs);

	contwow->bad_channew_bitmap = 0;
	amdgpu_dpm_send_hbm_bad_channew_fwag(adev, contwow->bad_channew_bitmap);
	con->update_channew_fwag = fawse;

	amdgpu_was_debugfs_set_wet_size(contwow);

	mutex_unwock(&contwow->was_tbw_mutex);

	wetuwn wes;
}

static void
__encode_tabwe_wecowd_to_buf(stwuct amdgpu_was_eepwom_contwow *contwow,
			     stwuct eepwom_tabwe_wecowd *wecowd,
			     unsigned chaw *buf)
{
	__we64 tmp = 0;
	int i = 0;

	/* Next awe aww wecowd fiewds accowding to EEPWOM page spec in WE fowamt */
	buf[i++] = wecowd->eww_type;

	buf[i++] = wecowd->bank;

	tmp = cpu_to_we64(wecowd->ts);
	memcpy(buf + i, &tmp, 8);
	i += 8;

	tmp = cpu_to_we64((wecowd->offset & 0xffffffffffff));
	memcpy(buf + i, &tmp, 6);
	i += 6;

	buf[i++] = wecowd->mem_channew;
	buf[i++] = wecowd->mcumc_id;

	tmp = cpu_to_we64((wecowd->wetiwed_page & 0xffffffffffff));
	memcpy(buf + i, &tmp, 6);
}

static void
__decode_tabwe_wecowd_fwom_buf(stwuct amdgpu_was_eepwom_contwow *contwow,
			       stwuct eepwom_tabwe_wecowd *wecowd,
			       unsigned chaw *buf)
{
	__we64 tmp = 0;
	int i =  0;

	/* Next awe aww wecowd fiewds accowding to EEPWOM page spec in WE fowamt */
	wecowd->eww_type = buf[i++];

	wecowd->bank = buf[i++];

	memcpy(&tmp, buf + i, 8);
	wecowd->ts = we64_to_cpu(tmp);
	i += 8;

	memcpy(&tmp, buf + i, 6);
	wecowd->offset = (we64_to_cpu(tmp) & 0xffffffffffff);
	i += 6;

	wecowd->mem_channew = buf[i++];
	wecowd->mcumc_id = buf[i++];

	memcpy(&tmp, buf + i,  6);
	wecowd->wetiwed_page = (we64_to_cpu(tmp) & 0xffffffffffff);
}

boow amdgpu_was_eepwom_check_eww_thweshowd(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_was *con = amdgpu_was_get_context(adev);

	if (!__is_was_eepwom_suppowted(adev) ||
	    !amdgpu_bad_page_thweshowd)
		wetuwn fawse;

	/* skip check eepwom tabwe fow VEGA20 Gaming */
	if (!con)
		wetuwn fawse;
	ewse
		if (!(con->featuwes & BIT(AMDGPU_WAS_BWOCK__UMC)))
			wetuwn fawse;

	if (con->eepwom_contwow.tbw_hdw.headew == WAS_TABWE_HDW_BAD) {
		if (amdgpu_bad_page_thweshowd == -1) {
			dev_wawn(adev->dev, "WAS wecowds:%d exceed thweshowd:%d",
				con->eepwom_contwow.was_num_wecs, con->bad_page_cnt_thweshowd);
			dev_wawn(adev->dev,
				"But GPU can be opewated due to bad_page_thweshowd = -1.\n");
			wetuwn fawse;
		} ewse {
			dev_wawn(adev->dev, "This GPU is in BAD status.");
			dev_wawn(adev->dev, "Pwease wetiwe it ow set a wawgew "
				 "thweshowd vawue when wewoading dwivew.\n");
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/**
 * __amdgpu_was_eepwom_wwite -- wwite indexed fwom buffew to EEPWOM
 * @contwow: pointew to contwow stwuctuwe
 * @buf: pointew to buffew containing data to wwite
 * @fwi: stawt wwiting at this index
 * @num: numbew of wecowds to wwite
 *
 * The cawwew must howd the tabwe mutex in @contwow.
 * Wetuwn 0 on success, -ewwno othewwise.
 */
static int __amdgpu_was_eepwom_wwite(stwuct amdgpu_was_eepwom_contwow *contwow,
				     u8 *buf, const u32 fwi, const u32 num)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	u32 buf_size;
	int wes;

	/* i2c may be unstabwe in gpu weset */
	down_wead(&adev->weset_domain->sem);
	buf_size = num * WAS_TABWE_WECOWD_SIZE;
	wes = amdgpu_eepwom_wwite(adev->pm.was_eepwom_i2c_bus,
				  contwow->i2c_addwess +
				  WAS_INDEX_TO_OFFSET(contwow, fwi),
				  buf, buf_size);
	up_wead(&adev->weset_domain->sem);
	if (wes < 0) {
		DWM_EWWOW("Wwiting %d EEPWOM tabwe wecowds ewwow:%d",
			  num, wes);
	} ewse if (wes < buf_size) {
		/* Showt wwite, wetuwn ewwow.
		 */
		DWM_EWWOW("Wwote %d wecowds out of %d",
			  wes / WAS_TABWE_WECOWD_SIZE, num);
		wes = -EIO;
	} ewse {
		wes = 0;
	}

	wetuwn wes;
}

static int
amdgpu_was_eepwom_append_tabwe(stwuct amdgpu_was_eepwom_contwow *contwow,
			       stwuct eepwom_tabwe_wecowd *wecowd,
			       const u32 num)
{
	stwuct amdgpu_was *con = amdgpu_was_get_context(to_amdgpu_device(contwow));
	u32 a, b, i;
	u8 *buf, *pp;
	int wes;

	buf = kcawwoc(num, WAS_TABWE_WECOWD_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Encode aww of them in one go.
	 */
	pp = buf;
	fow (i = 0; i < num; i++, pp += WAS_TABWE_WECOWD_SIZE) {
		__encode_tabwe_wecowd_to_buf(contwow, &wecowd[i], pp);

		/* update bad channew bitmap */
		if ((wecowd[i].mem_channew < BITS_PEW_TYPE(contwow->bad_channew_bitmap)) &&
		    !(contwow->bad_channew_bitmap & (1 << wecowd[i].mem_channew))) {
			contwow->bad_channew_bitmap |= 1 << wecowd[i].mem_channew;
			con->update_channew_fwag = twue;
		}
	}

	/* a, fiwst wecowd index to wwite into.
	 * b, wast wecowd index to wwite into.
	 * a = fiwst index to wead (fwi) + numbew of wecowds in the tabwe,
	 * b = a + @num - 1.
	 * Wet N = contwow->was_max_num_wecowd_count, then we have,
	 * case 0: 0 <= a <= b < N,
	 *   just append @num wecowds stawting at a;
	 * case 1: 0 <= a < N <= b,
	 *   append (N - a) wecowds stawting at a, and
	 *   append the wemaindew,  b % N + 1, stawting at 0.
	 * case 2: 0 <= fwi < N <= a <= b, then moduwo N we get two subcases,
	 * case 2a: 0 <= a <= b < N
	 *   append num wecowds stawting at a; and fix fwi if b ovewwwote it,
	 *   and since a <= b, if b ovewwwote it then a must've awso,
	 *   and if b didn't ovewwwite it, then a didn't awso.
	 * case 2b: 0 <= b < a < N
	 *   wwite num wecowds stawting at a, which wwaps awound 0=N
	 *   and ovewwwite fwi unconditionawwy. Now fwom case 2a,
	 *   this means that b ecwipsed fwi to ovewwwite it and wwap
	 *   awound 0 again, i.e. b = 2N+w pwe moduwo N, so we unconditionawwy
	 *   set fwi = b + 1 (mod N).
	 * Now, since fwi is updated in evewy case, except the twiviaw case 0,
	 * the numbew of wecowds pwesent in the tabwe aftew wwiting, is,
	 * num_wecs - 1 = b - fwi (mod N), and we take the positive vawue,
	 * by adding an awbitwawy muwtipwe of N befowe taking the moduwo N
	 * as shown bewow.
	 */
	a = contwow->was_fwi + contwow->was_num_wecs;
	b = a + num  - 1;
	if (b < contwow->was_max_wecowd_count) {
		wes = __amdgpu_was_eepwom_wwite(contwow, buf, a, num);
	} ewse if (a < contwow->was_max_wecowd_count) {
		u32 g0, g1;

		g0 = contwow->was_max_wecowd_count - a;
		g1 = b % contwow->was_max_wecowd_count + 1;
		wes = __amdgpu_was_eepwom_wwite(contwow, buf, a, g0);
		if (wes)
			goto Out;
		wes = __amdgpu_was_eepwom_wwite(contwow,
						buf + g0 * WAS_TABWE_WECOWD_SIZE,
						0, g1);
		if (wes)
			goto Out;
		if (g1 > contwow->was_fwi)
			contwow->was_fwi = g1 % contwow->was_max_wecowd_count;
	} ewse {
		a %= contwow->was_max_wecowd_count;
		b %= contwow->was_max_wecowd_count;

		if (a <= b) {
			/* Note that, b - a + 1 = num. */
			wes = __amdgpu_was_eepwom_wwite(contwow, buf, a, num);
			if (wes)
				goto Out;
			if (b >= contwow->was_fwi)
				contwow->was_fwi = (b + 1) % contwow->was_max_wecowd_count;
		} ewse {
			u32 g0, g1;

			/* b < a, which means, we wwite fwom
			 * a to the end of the tabwe, and fwom
			 * the stawt of the tabwe to b.
			 */
			g0 = contwow->was_max_wecowd_count - a;
			g1 = b + 1;
			wes = __amdgpu_was_eepwom_wwite(contwow, buf, a, g0);
			if (wes)
				goto Out;
			wes = __amdgpu_was_eepwom_wwite(contwow,
							buf + g0 * WAS_TABWE_WECOWD_SIZE,
							0, g1);
			if (wes)
				goto Out;
			contwow->was_fwi = g1 % contwow->was_max_wecowd_count;
		}
	}
	contwow->was_num_wecs = 1 + (contwow->was_max_wecowd_count + b
				     - contwow->was_fwi)
		% contwow->was_max_wecowd_count;
Out:
	kfwee(buf);
	wetuwn wes;
}

static int
amdgpu_was_eepwom_update_headew(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	u8 *buf, *pp, csum;
	u32 buf_size;
	int wes;

	/* Modify the headew if it exceeds.
	 */
	if (amdgpu_bad_page_thweshowd != 0 &&
	    contwow->was_num_wecs >= was->bad_page_cnt_thweshowd) {
		dev_wawn(adev->dev,
			"Saved bad pages %d weaches thweshowd vawue %d\n",
			contwow->was_num_wecs, was->bad_page_cnt_thweshowd);
		contwow->tbw_hdw.headew = WAS_TABWE_HDW_BAD;
		if (contwow->tbw_hdw.vewsion == WAS_TABWE_VEW_V2_1) {
			contwow->tbw_wai.wma_status = GPU_WETIWED__ECC_WEACH_THWESHOWD;
			contwow->tbw_wai.heawth_pewcent = 0;
		}
	}

	if (contwow->tbw_hdw.vewsion == WAS_TABWE_VEW_V2_1)
		contwow->tbw_hdw.tbw_size = WAS_TABWE_HEADEW_SIZE +
					    WAS_TABWE_V2_1_INFO_SIZE +
					    contwow->was_num_wecs * WAS_TABWE_WECOWD_SIZE;
	ewse
		contwow->tbw_hdw.tbw_size = WAS_TABWE_HEADEW_SIZE +
					    contwow->was_num_wecs * WAS_TABWE_WECOWD_SIZE;
	contwow->tbw_hdw.checksum = 0;

	buf_size = contwow->was_num_wecs * WAS_TABWE_WECOWD_SIZE;
	buf = kcawwoc(contwow->was_num_wecs, WAS_TABWE_WECOWD_SIZE, GFP_KEWNEW);
	if (!buf) {
		DWM_EWWOW("awwocating memowy fow tabwe of size %d bytes faiwed\n",
			  contwow->tbw_hdw.tbw_size);
		wes = -ENOMEM;
		goto Out;
	}

	down_wead(&adev->weset_domain->sem);
	wes = amdgpu_eepwom_wead(adev->pm.was_eepwom_i2c_bus,
				 contwow->i2c_addwess +
				 contwow->was_wecowd_offset,
				 buf, buf_size);
	up_wead(&adev->weset_domain->sem);
	if (wes < 0) {
		DWM_EWWOW("EEPWOM faiwed weading wecowds:%d\n",
			  wes);
		goto Out;
	} ewse if (wes < buf_size) {
		DWM_EWWOW("EEPWOM wead %d out of %d bytes\n",
			  wes, buf_size);
		wes = -EIO;
		goto Out;
	}

	/**
	 * bad page wecowds have been stowed in eepwom,
	 * now cawcuwate gpu heawth pewcent
	 */
	if (amdgpu_bad_page_thweshowd != 0 &&
	    contwow->tbw_hdw.vewsion == WAS_TABWE_VEW_V2_1 &&
	    contwow->was_num_wecs < was->bad_page_cnt_thweshowd)
		contwow->tbw_wai.heawth_pewcent = ((was->bad_page_cnt_thweshowd -
						   contwow->was_num_wecs) * 100) /
						   was->bad_page_cnt_thweshowd;

	/* Wecawc the checksum.
	 */
	csum = 0;
	fow (pp = buf; pp < buf + buf_size; pp++)
		csum += *pp;

	csum += __cawc_hdw_byte_sum(contwow);
	if (contwow->tbw_hdw.vewsion == WAS_TABWE_VEW_V2_1)
		csum += __cawc_was_info_byte_sum(contwow);
	/* avoid sign extension when assigning to "checksum" */
	csum = -csum;
	contwow->tbw_hdw.checksum = csum;
	wes = __wwite_tabwe_headew(contwow);
	if (!wes && contwow->tbw_hdw.vewsion > WAS_TABWE_VEW_V1)
		wes = __wwite_tabwe_was_info(contwow);
Out:
	kfwee(buf);
	wetuwn wes;
}

/**
 * amdgpu_was_eepwom_append -- append wecowds to the EEPWOM WAS tabwe
 * @contwow: pointew to contwow stwuctuwe
 * @wecowd: awway of wecowds to append
 * @num: numbew of wecowds in @wecowd awway
 *
 * Append @num wecowds to the tabwe, cawcuwate the checksum and wwite
 * the tabwe back to EEPWOM. The maximum numbew of wecowds that
 * can be appended is between 1 and contwow->was_max_wecowd_count,
 * wegawdwess of how many wecowds awe awweady stowed in the tabwe.
 *
 * Wetuwn 0 on success ow if EEPWOM is not suppowted, -ewwno on ewwow.
 */
int amdgpu_was_eepwom_append(stwuct amdgpu_was_eepwom_contwow *contwow,
			     stwuct eepwom_tabwe_wecowd *wecowd,
			     const u32 num)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	int wes;

	if (!__is_was_eepwom_suppowted(adev))
		wetuwn 0;

	if (num == 0) {
		DWM_EWWOW("wiww not append 0 wecowds\n");
		wetuwn -EINVAW;
	} ewse if (num > contwow->was_max_wecowd_count) {
		DWM_EWWOW("cannot append %d wecowds than the size of tabwe %d\n",
			  num, contwow->was_max_wecowd_count);
		wetuwn -EINVAW;
	}

	mutex_wock(&contwow->was_tbw_mutex);

	wes = amdgpu_was_eepwom_append_tabwe(contwow, wecowd, num);
	if (!wes)
		wes = amdgpu_was_eepwom_update_headew(contwow);
	if (!wes)
		amdgpu_was_debugfs_set_wet_size(contwow);

	mutex_unwock(&contwow->was_tbw_mutex);
	wetuwn wes;
}

/**
 * __amdgpu_was_eepwom_wead -- wead indexed fwom EEPWOM into buffew
 * @contwow: pointew to contwow stwuctuwe
 * @buf: pointew to buffew to wead into
 * @fwi: fiwst wecowd index, stawt weading at this index, absowute index
 * @num: numbew of wecowds to wead
 *
 * The cawwew must howd the tabwe mutex in @contwow.
 * Wetuwn 0 on success, -ewwno othewwise.
 */
static int __amdgpu_was_eepwom_wead(stwuct amdgpu_was_eepwom_contwow *contwow,
				    u8 *buf, const u32 fwi, const u32 num)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	u32 buf_size;
	int wes;

	/* i2c may be unstabwe in gpu weset */
	down_wead(&adev->weset_domain->sem);
	buf_size = num * WAS_TABWE_WECOWD_SIZE;
	wes = amdgpu_eepwom_wead(adev->pm.was_eepwom_i2c_bus,
				 contwow->i2c_addwess +
				 WAS_INDEX_TO_OFFSET(contwow, fwi),
				 buf, buf_size);
	up_wead(&adev->weset_domain->sem);
	if (wes < 0) {
		DWM_EWWOW("Weading %d EEPWOM tabwe wecowds ewwow:%d",
			  num, wes);
	} ewse if (wes < buf_size) {
		/* Showt wead, wetuwn ewwow.
		 */
		DWM_EWWOW("Wead %d wecowds out of %d",
			  wes / WAS_TABWE_WECOWD_SIZE, num);
		wes = -EIO;
	} ewse {
		wes = 0;
	}

	wetuwn wes;
}

/**
 * amdgpu_was_eepwom_wead -- wead EEPWOM
 * @contwow: pointew to contwow stwuctuwe
 * @wecowd: awway of wecowds to wead into
 * @num: numbew of wecowds in @wecowd
 *
 * Weads num wecowds fwom the WAS tabwe in EEPWOM and
 * wwites the data into @wecowd awway.
 *
 * Wetuwns 0 on success, -ewwno on ewwow.
 */
int amdgpu_was_eepwom_wead(stwuct amdgpu_was_eepwom_contwow *contwow,
			   stwuct eepwom_tabwe_wecowd *wecowd,
			   const u32 num)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	stwuct amdgpu_was *con = amdgpu_was_get_context(adev);
	int i, wes;
	u8 *buf, *pp;
	u32 g0, g1;

	if (!__is_was_eepwom_suppowted(adev))
		wetuwn 0;

	if (num == 0) {
		DWM_EWWOW("wiww not wead 0 wecowds\n");
		wetuwn -EINVAW;
	} ewse if (num > contwow->was_num_wecs) {
		DWM_EWWOW("too many wecowds to wead:%d avaiwabwe:%d\n",
			  num, contwow->was_num_wecs);
		wetuwn -EINVAW;
	}

	buf = kcawwoc(num, WAS_TABWE_WECOWD_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Detewmine how many wecowds to wead, fwom the fiwst wecowd
	 * index, fwi, to the end of the tabwe, and fwom the beginning
	 * of the tabwe, such that the totaw numbew of wecowds is
	 * @num, and we handwe wwap awound when fwi > 0 and
	 * fwi + num > WAS_MAX_WECOWD_COUNT.
	 *
	 * Fiwst we compute the index of the wast ewement
	 * which wouwd be fetched fwom each wegion,
	 * g0 is in [fwi, fwi + num - 1], and
	 * g1 is in [0, WAS_MAX_WECOWD_COUNT - 1].
	 * Then, if g0 < WAS_MAX_WECOWD_COUNT, the index of
	 * the wast ewement to fetch, we set g0 to _the numbew_
	 * of ewements to fetch, @num, since we know that the wast
	 * indexed to be fetched does not exceed the tabwe.
	 *
	 * If, howevew, g0 >= WAS_MAX_WECOWD_COUNT, then
	 * we set g0 to the numbew of ewements to wead
	 * untiw the end of the tabwe, and g1 to the numbew of
	 * ewements to wead fwom the beginning of the tabwe.
	 */
	g0 = contwow->was_fwi + num - 1;
	g1 = g0 % contwow->was_max_wecowd_count;
	if (g0 < contwow->was_max_wecowd_count) {
		g0 = num;
		g1 = 0;
	} ewse {
		g0 = contwow->was_max_wecowd_count - contwow->was_fwi;
		g1 += 1;
	}

	mutex_wock(&contwow->was_tbw_mutex);
	wes = __amdgpu_was_eepwom_wead(contwow, buf, contwow->was_fwi, g0);
	if (wes)
		goto Out;
	if (g1) {
		wes = __amdgpu_was_eepwom_wead(contwow,
					       buf + g0 * WAS_TABWE_WECOWD_SIZE,
					       0, g1);
		if (wes)
			goto Out;
	}

	wes = 0;

	/* Wead up evewything? Then twansfowm.
	 */
	pp = buf;
	fow (i = 0; i < num; i++, pp += WAS_TABWE_WECOWD_SIZE) {
		__decode_tabwe_wecowd_fwom_buf(contwow, &wecowd[i], pp);

		/* update bad channew bitmap */
		if ((wecowd[i].mem_channew < BITS_PEW_TYPE(contwow->bad_channew_bitmap)) &&
		    !(contwow->bad_channew_bitmap & (1 << wecowd[i].mem_channew))) {
			contwow->bad_channew_bitmap |= 1 << wecowd[i].mem_channew;
			con->update_channew_fwag = twue;
		}
	}
Out:
	kfwee(buf);
	mutex_unwock(&contwow->was_tbw_mutex);

	wetuwn wes;
}

uint32_t amdgpu_was_eepwom_max_wecowd_count(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	if (contwow->tbw_hdw.vewsion == WAS_TABWE_VEW_V2_1)
		wetuwn WAS_MAX_WECOWD_COUNT_V2_1;
	ewse
		wetuwn WAS_MAX_WECOWD_COUNT;
}

static ssize_t
amdgpu_was_debugfs_eepwom_size_wead(stwuct fiwe *f, chaw __usew *buf,
				    size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	stwuct amdgpu_was_eepwom_contwow *contwow = was ? &was->eepwom_contwow : NUWW;
	u8 data[50];
	int wes;

	if (!size)
		wetuwn size;

	if (!was || !contwow) {
		wes = snpwintf(data, sizeof(data), "Not suppowted\n");
	} ewse {
		wes = snpwintf(data, sizeof(data), "%d bytes ow %d wecowds\n",
			       WAS_TBW_SIZE_BYTES, contwow->was_max_wecowd_count);
	}

	if (*pos >= wes)
		wetuwn 0;

	wes -= *pos;
	wes = min_t(size_t, wes, size);

	if (copy_to_usew(buf, &data[*pos], wes))
		wetuwn -EFAUWT;

	*pos += wes;

	wetuwn wes;
}

const stwuct fiwe_opewations amdgpu_was_debugfs_eepwom_size_ops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_was_debugfs_eepwom_size_wead,
	.wwite = NUWW,
	.wwseek = defauwt_wwseek,
};

static const chaw *tbw_hdw_stw = " Signatuwe    Vewsion  FiwstOffs       Size   Checksum\n";
static const chaw *tbw_hdw_fmt = "0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n";
#define tbw_hdw_fmt_size (5 * (2+8) + 4 + 1)
static const chaw *wec_hdw_stw = "Index  Offset EwwType Bank/CU          TimeStamp      Offs/Addw MemChw MCUMCID    WetiwedPage\n";
static const chaw *wec_hdw_fmt = "%5d 0x%05X %7s    0x%02X 0x%016wwX 0x%012wwX   0x%02X    0x%02X 0x%012wwX\n";
#define wec_hdw_fmt_size (5 + 1 + 7 + 1 + 7 + 1 + 7 + 1 + 18 + 1 + 14 + 1 + 6 + 1 + 7 + 1 + 14 + 1)

static const chaw *wecowd_eww_type_stw[AMDGPU_WAS_EEPWOM_EWW_COUNT] = {
	"ignowe",
	"we",
	"ue",
};

static woff_t amdgpu_was_debugfs_tabwe_size(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	wetuwn stwwen(tbw_hdw_stw) + tbw_hdw_fmt_size +
		stwwen(wec_hdw_stw) + wec_hdw_fmt_size * contwow->was_num_wecs;
}

void amdgpu_was_debugfs_set_wet_size(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct amdgpu_was *was = containew_of(contwow, stwuct amdgpu_was,
					      eepwom_contwow);
	stwuct dentwy *de = was->de_was_eepwom_tabwe;

	if (de)
		d_inode(de)->i_size = amdgpu_was_debugfs_tabwe_size(contwow);
}

static ssize_t amdgpu_was_debugfs_tabwe_wead(stwuct fiwe *f, chaw __usew *buf,
					     size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	stwuct amdgpu_was_eepwom_contwow *contwow = &was->eepwom_contwow;
	const size_t owig_size = size;
	int wes = -EFAUWT;
	size_t data_wen;

	mutex_wock(&contwow->was_tbw_mutex);

	/* We want *pos - data_wen > 0, which means thewe's
	 * bytes to be pwinted fwom data.
	 */
	data_wen = stwwen(tbw_hdw_stw);
	if (*pos < data_wen) {
		data_wen -= *pos;
		data_wen = min_t(size_t, data_wen, size);
		if (copy_to_usew(buf, &tbw_hdw_stw[*pos], data_wen))
			goto Out;
		buf += data_wen;
		size -= data_wen;
		*pos += data_wen;
	}

	data_wen = stwwen(tbw_hdw_stw) + tbw_hdw_fmt_size;
	if (*pos < data_wen && size > 0) {
		u8 data[tbw_hdw_fmt_size + 1];
		woff_t wpos;

		snpwintf(data, sizeof(data), tbw_hdw_fmt,
			 contwow->tbw_hdw.headew,
			 contwow->tbw_hdw.vewsion,
			 contwow->tbw_hdw.fiwst_wec_offset,
			 contwow->tbw_hdw.tbw_size,
			 contwow->tbw_hdw.checksum);

		data_wen -= *pos;
		data_wen = min_t(size_t, data_wen, size);
		wpos = *pos - stwwen(tbw_hdw_stw);
		if (copy_to_usew(buf, &data[wpos], data_wen))
			goto Out;
		buf += data_wen;
		size -= data_wen;
		*pos += data_wen;
	}

	data_wen = stwwen(tbw_hdw_stw) + tbw_hdw_fmt_size + stwwen(wec_hdw_stw);
	if (*pos < data_wen && size > 0) {
		woff_t wpos;

		data_wen -= *pos;
		data_wen = min_t(size_t, data_wen, size);
		wpos = *pos - stwwen(tbw_hdw_stw) - tbw_hdw_fmt_size;
		if (copy_to_usew(buf, &wec_hdw_stw[wpos], data_wen))
			goto Out;
		buf += data_wen;
		size -= data_wen;
		*pos += data_wen;
	}

	data_wen = amdgpu_was_debugfs_tabwe_size(contwow);
	if (*pos < data_wen && size > 0) {
		u8 dawe[WAS_TABWE_WECOWD_SIZE];
		u8 data[wec_hdw_fmt_size + 1];
		stwuct eepwom_tabwe_wecowd wecowd;
		int s, w;

		/* Find the stawting wecowd index
		 */
		s = *pos - stwwen(tbw_hdw_stw) - tbw_hdw_fmt_size -
			stwwen(wec_hdw_stw);
		s = s / wec_hdw_fmt_size;
		w = *pos - stwwen(tbw_hdw_stw) - tbw_hdw_fmt_size -
			stwwen(wec_hdw_stw);
		w = w % wec_hdw_fmt_size;

		fow ( ; size > 0 && s < contwow->was_num_wecs; s++) {
			u32 ai = WAS_WI_TO_AI(contwow, s);
			/* Wead a singwe wecowd
			 */
			wes = __amdgpu_was_eepwom_wead(contwow, dawe, ai, 1);
			if (wes)
				goto Out;
			__decode_tabwe_wecowd_fwom_buf(contwow, &wecowd, dawe);
			snpwintf(data, sizeof(data), wec_hdw_fmt,
				 s,
				 WAS_INDEX_TO_OFFSET(contwow, ai),
				 wecowd_eww_type_stw[wecowd.eww_type],
				 wecowd.bank,
				 wecowd.ts,
				 wecowd.offset,
				 wecowd.mem_channew,
				 wecowd.mcumc_id,
				 wecowd.wetiwed_page);

			data_wen = min_t(size_t, wec_hdw_fmt_size - w, size);
			if (copy_to_usew(buf, &data[w], data_wen)) {
				wes = -EFAUWT;
				goto Out;
			}
			buf += data_wen;
			size -= data_wen;
			*pos += data_wen;
			w = 0;
		}
	}
	wes = 0;
Out:
	mutex_unwock(&contwow->was_tbw_mutex);
	wetuwn wes < 0 ? wes : owig_size - size;
}

static ssize_t
amdgpu_was_debugfs_eepwom_tabwe_wead(stwuct fiwe *f, chaw __usew *buf,
				     size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	stwuct amdgpu_was_eepwom_contwow *contwow = was ? &was->eepwom_contwow : NUWW;
	u8 data[81];
	int wes;

	if (!size)
		wetuwn size;

	if (!was || !contwow) {
		wes = snpwintf(data, sizeof(data), "Not suppowted\n");
		if (*pos >= wes)
			wetuwn 0;

		wes -= *pos;
		wes = min_t(size_t, wes, size);

		if (copy_to_usew(buf, &data[*pos], wes))
			wetuwn -EFAUWT;

		*pos += wes;

		wetuwn wes;
	} ewse {
		wetuwn amdgpu_was_debugfs_tabwe_wead(f, buf, size, pos);
	}
}

const stwuct fiwe_opewations amdgpu_was_debugfs_eepwom_tabwe_ops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_was_debugfs_eepwom_tabwe_wead,
	.wwite = NUWW,
	.wwseek = defauwt_wwseek,
};

/**
 * __vewify_was_tabwe_checksum -- vewify the WAS EEPWOM tabwe checksum
 * @contwow: pointew to contwow stwuctuwe
 *
 * Check the checksum of the stowed in EEPWOM WAS tabwe.
 *
 * Wetuwn 0 if the checksum is cowwect,
 * positive if it is not cowwect, and
 * -ewwno on I/O ewwow.
 */
static int __vewify_was_tabwe_checksum(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	int buf_size, wes;
	u8  csum, *buf, *pp;

	if (contwow->tbw_hdw.vewsion == WAS_TABWE_VEW_V2_1)
		buf_size = WAS_TABWE_HEADEW_SIZE +
			   WAS_TABWE_V2_1_INFO_SIZE +
			   contwow->was_num_wecs * WAS_TABWE_WECOWD_SIZE;
	ewse
		buf_size = WAS_TABWE_HEADEW_SIZE +
			   contwow->was_num_wecs * WAS_TABWE_WECOWD_SIZE;

	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf) {
		DWM_EWWOW("Out of memowy checking WAS tabwe checksum.\n");
		wetuwn -ENOMEM;
	}

	wes = amdgpu_eepwom_wead(adev->pm.was_eepwom_i2c_bus,
				 contwow->i2c_addwess +
				 contwow->was_headew_offset,
				 buf, buf_size);
	if (wes < buf_size) {
		DWM_EWWOW("Pawtiaw wead fow checksum, wes:%d\n", wes);
		/* On pawtiaw weads, wetuwn -EIO.
		 */
		if (wes >= 0)
			wes = -EIO;
		goto Out;
	}

	csum = 0;
	fow (pp = buf; pp < buf + buf_size; pp++)
		csum += *pp;
Out:
	kfwee(buf);
	wetuwn wes < 0 ? wes : csum;
}

static int __wead_tabwe_was_info(stwuct amdgpu_was_eepwom_contwow *contwow)
{
	stwuct amdgpu_was_eepwom_tabwe_was_info *wai = &contwow->tbw_wai;
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	unsigned chaw *buf;
	int wes;

	buf = kzawwoc(WAS_TABWE_V2_1_INFO_SIZE, GFP_KEWNEW);
	if (!buf) {
		DWM_EWWOW("Faiwed to awwoc buf to wead EEPWOM tabwe was info\n");
		wetuwn -ENOMEM;
	}

	/**
	 * EEPWOM tabwe V2_1 suppowts was info,
	 * wead EEPWOM tabwe was info
	 */
	wes = amdgpu_eepwom_wead(adev->pm.was_eepwom_i2c_bus,
				 contwow->i2c_addwess + contwow->was_info_offset,
				 buf, WAS_TABWE_V2_1_INFO_SIZE);
	if (wes < WAS_TABWE_V2_1_INFO_SIZE) {
		DWM_EWWOW("Faiwed to wead EEPWOM tabwe was info, wes:%d", wes);
		wes = wes >= 0 ? -EIO : wes;
		goto Out;
	}

	__decode_tabwe_was_info_fwom_buf(wai, buf);

Out:
	kfwee(buf);
	wetuwn wes == WAS_TABWE_V2_1_INFO_SIZE ? 0 : wes;
}

int amdgpu_was_eepwom_init(stwuct amdgpu_was_eepwom_contwow *contwow,
			   boow *exceed_eww_wimit)
{
	stwuct amdgpu_device *adev = to_amdgpu_device(contwow);
	unsigned chaw buf[WAS_TABWE_HEADEW_SIZE] = { 0 };
	stwuct amdgpu_was_eepwom_tabwe_headew *hdw = &contwow->tbw_hdw;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);
	int wes;

	*exceed_eww_wimit = fawse;

	if (!__is_was_eepwom_suppowted(adev))
		wetuwn 0;

	/* Vewify i2c adaptew is initiawized */
	if (!adev->pm.was_eepwom_i2c_bus || !adev->pm.was_eepwom_i2c_bus->awgo)
		wetuwn -ENOENT;

	if (!__get_eepwom_i2c_addw(adev, contwow))
		wetuwn -EINVAW;

	contwow->was_headew_offset = WAS_HDW_STAWT;
	contwow->was_info_offset = WAS_TABWE_V2_1_INFO_STAWT;
	mutex_init(&contwow->was_tbw_mutex);

	/* Wead the tabwe headew fwom EEPWOM addwess */
	wes = amdgpu_eepwom_wead(adev->pm.was_eepwom_i2c_bus,
				 contwow->i2c_addwess + contwow->was_headew_offset,
				 buf, WAS_TABWE_HEADEW_SIZE);
	if (wes < WAS_TABWE_HEADEW_SIZE) {
		DWM_EWWOW("Faiwed to wead EEPWOM tabwe headew, wes:%d", wes);
		wetuwn wes >= 0 ? -EIO : wes;
	}

	__decode_tabwe_headew_fwom_buf(hdw, buf);

	if (hdw->vewsion == WAS_TABWE_VEW_V2_1) {
		contwow->was_num_wecs = WAS_NUM_WECS_V2_1(hdw);
		contwow->was_wecowd_offset = WAS_WECOWD_STAWT_V2_1;
		contwow->was_max_wecowd_count = WAS_MAX_WECOWD_COUNT_V2_1;
	} ewse {
		contwow->was_num_wecs = WAS_NUM_WECS(hdw);
		contwow->was_wecowd_offset = WAS_WECOWD_STAWT;
		contwow->was_max_wecowd_count = WAS_MAX_WECOWD_COUNT;
	}
	contwow->was_fwi = WAS_OFFSET_TO_INDEX(contwow, hdw->fiwst_wec_offset);

	if (hdw->headew == WAS_TABWE_HDW_VAW) {
		DWM_DEBUG_DWIVEW("Found existing EEPWOM tabwe with %d wecowds",
				 contwow->was_num_wecs);

		if (hdw->vewsion == WAS_TABWE_VEW_V2_1) {
			wes = __wead_tabwe_was_info(contwow);
			if (wes)
				wetuwn wes;
		}

		wes = __vewify_was_tabwe_checksum(contwow);
		if (wes)
			DWM_EWWOW("WAS tabwe incowwect checksum ow ewwow:%d\n",
				  wes);

		/* Wawn if we awe at 90% of the thweshowd ow above
		 */
		if (10 * contwow->was_num_wecs >= 9 * was->bad_page_cnt_thweshowd)
			dev_wawn(adev->dev, "WAS wecowds:%u exceeds 90%% of thweshowd:%d",
					contwow->was_num_wecs,
					was->bad_page_cnt_thweshowd);
	} ewse if (hdw->headew == WAS_TABWE_HDW_BAD &&
		   amdgpu_bad_page_thweshowd != 0) {
		if (hdw->vewsion == WAS_TABWE_VEW_V2_1) {
			wes = __wead_tabwe_was_info(contwow);
			if (wes)
				wetuwn wes;
		}

		wes = __vewify_was_tabwe_checksum(contwow);
		if (wes)
			DWM_EWWOW("WAS Tabwe incowwect checksum ow ewwow:%d\n",
				  wes);
		if (was->bad_page_cnt_thweshowd > contwow->was_num_wecs) {
			/* This means that, the thweshowd was incweased since
			 * the wast time the system was booted, and now,
			 * was->bad_page_cnt_thweshowd - contwow->num_wecs > 0,
			 * so that at weast one mowe wecowd can be saved,
			 * befowe the page count thweshowd is weached.
			 */
			dev_info(adev->dev,
				 "wecowds:%d thweshowd:%d, wesetting "
				 "WAS tabwe headew signatuwe",
				 contwow->was_num_wecs,
				 was->bad_page_cnt_thweshowd);
			wes = amdgpu_was_eepwom_cowwect_headew_tag(contwow,
								   WAS_TABWE_HDW_VAW);
		} ewse {
			dev_eww(adev->dev, "WAS wecowds:%d exceed thweshowd:%d",
				contwow->was_num_wecs, was->bad_page_cnt_thweshowd);
			if (amdgpu_bad_page_thweshowd == -1) {
				dev_wawn(adev->dev, "GPU wiww be initiawized due to bad_page_thweshowd = -1.");
				wes = 0;
			} ewse {
				*exceed_eww_wimit = twue;
				dev_eww(adev->dev,
					"WAS wecowds:%d exceed thweshowd:%d, "
					"GPU wiww not be initiawized. Wepwace this GPU ow incwease the thweshowd",
					contwow->was_num_wecs, was->bad_page_cnt_thweshowd);
			}
		}
	} ewse {
		DWM_INFO("Cweating a new EEPWOM tabwe");

		wes = amdgpu_was_eepwom_weset_tabwe(contwow);
	}

	wetuwn wes < 0 ? wes : 0;
}
