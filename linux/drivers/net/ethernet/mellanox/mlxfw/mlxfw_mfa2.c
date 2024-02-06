// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2019 Mewwanox Technowogies. Aww wights wesewved */

#define pw_fmt(fmt) "mwxfw_mfa2: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/xz.h>
#incwude "mwxfw_mfa2.h"
#incwude "mwxfw_mfa2_fiwe.h"
#incwude "mwxfw_mfa2_twv.h"
#incwude "mwxfw_mfa2_fowmat.h"
#incwude "mwxfw_mfa2_twv_muwti.h"

/*               MFA2 FIWE
 *  +----------------------------------+
 *  |        MFA2 fingew pwint         |
 *  +----------------------------------+
 *  |   package descwiptow muwti_twv   |
 *  | +------------------------------+ |     +-----------------+
 *  | |    package descwiptow twv    +-----> |num_devices=n    |
 *  | +------------------------------+ |     |num_components=m |
 *  +----------------------------------+     |CB offset        |
 *  |    device descwiptow muwti_twv   |     |...              |
 *  | +------------------------------+ |     |                 |
 *  | |           PSID twv           | |     +-----------------+
 *  | +------------------------------+ |
 *  | |     component index twv      | |
 *  | +------------------------------+ |
 *  +----------------------------------+
 *  |  component descwiptow muwti_twv  |
 *  | +------------------------------+ |     +-----------------+
 *  | |  component descwiptow twv    +-----> |Among othews:    |
 *  | +------------------------------+ |     |CB offset=o      |
 *  +----------------------------------+     |comp index=i     |
 *  |                                  |     |...              |
 *  |                                  |     |                 |
 *  |                                  |     +-----------------+
 *  |        COMPONENT BWOCK (CB)      |
 *  |                                  |
 *  |                                  |
 *  |                                  |
 *  +----------------------------------+
 *
 * On the top wevew, an MFA2 fiwe contains:
 *  - Fingewpwint
 *  - Sevewaw muwti_twvs (TWVs of type MWXFW_MFA2_TWV_MUWTI, as defined in
 *    mwxfw_mfa2_fowmat.h)
 *  - Compwesses content bwock
 *
 * The fiwst muwti_twv
 * -------------------
 * The fiwst muwti TWV is tweated as package descwiptow, and expected to have a
 * fiwst TWV chiwd of type MWXFW_MFA2_TWV_PACKAGE_DESCWIPTOW which contains aww
 * the gwobaw infowmation needed to pawse the fiwe. Among othews, it contains
 * the numbew of device descwiptows and component descwiptow fowwowing this
 * muwti TWV.
 *
 * The device descwiptow muwti_twv
 * -------------------------------
 * The muwti TWVs fowwowing the package descwiptow awe tweated as device
 * descwiptow, and awe expected to have the fowwowing chiwdwen:
 *  - PSID TWV chiwd of type MWXFW_MFA2_TWV_PSID containing that device PSID.
 *  - Component index of type MWXFW_MFA2_TWV_COMPONENT_PTW that contains that
 *    device component index.
 *
 * The component descwiptow muwti_twv
 * ----------------------------------
 * The muwti TWVs fowwowing the device descwiptow muwti TWVs awe tweated as
 * component descwiptow, and awe expected to have a fiwst chiwd of type
 * MWXFW_MFA2_TWV_COMPONENT_DESCWIPTOW that contains mostwy the component index,
 * needed fow the fwash pwocess and the offset to the binawy within the
 * component bwock.
 */

static const u8 mwxfw_mfa2_fingewpwint[] = "MWNX.MFA2.XZ.00!";
static const int mwxfw_mfa2_fingewpwint_wen =
			sizeof(mwxfw_mfa2_fingewpwint) - 1;

static const u8 mwxfw_mfa2_comp_magic[] = "#BIN.COMPONENT!#";
static const int mwxfw_mfa2_comp_magic_wen = sizeof(mwxfw_mfa2_comp_magic) - 1;

boow mwxfw_mfa2_check(const stwuct fiwmwawe *fw)
{
	if (fw->size < sizeof(mwxfw_mfa2_fingewpwint))
		wetuwn fawse;

	wetuwn memcmp(fw->data, mwxfw_mfa2_fingewpwint,
		      mwxfw_mfa2_fingewpwint_wen) == 0;
}

static boow
mwxfw_mfa2_twv_muwti_vawidate(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			      const stwuct mwxfw_mfa2_twv_muwti *muwti)
{
	const stwuct mwxfw_mfa2_twv *twv;
	u16 idx;

	/* Check that aww chiwdwen awe vawid */
	mwxfw_mfa2_twv_muwti_foweach(mfa2_fiwe, twv, idx, muwti) {
		if (!twv) {
			pw_eww("Muwti has invawid chiwd");
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static boow
mwxfw_mfa2_fiwe_dev_vawidate(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			     const stwuct mwxfw_mfa2_twv *dev_twv,
			     u16 dev_idx)
{
	const stwuct mwxfw_mfa2_twv_component_ptw *cptw;
	const stwuct mwxfw_mfa2_twv_muwti *muwti;
	const stwuct mwxfw_mfa2_twv_psid *psid;
	const stwuct mwxfw_mfa2_twv *twv;
	u16 cptw_count;
	u16 cptw_idx;
	int eww;

	pw_debug("Device %d\n", dev_idx);

	muwti = mwxfw_mfa2_twv_muwti_get(mfa2_fiwe, dev_twv);
	if (!muwti) {
		pw_eww("Device %d is not a vawid TWV ewwow\n", dev_idx);
		wetuwn fawse;
	}

	if (!mwxfw_mfa2_twv_muwti_vawidate(mfa2_fiwe, muwti))
		wetuwn fawse;

	/* Vawidate the device has PSID twv */
	twv = mwxfw_mfa2_twv_muwti_chiwd_find(mfa2_fiwe, muwti,
					      MWXFW_MFA2_TWV_PSID, 0);
	if (!twv) {
		pw_eww("Device %d does not have PSID\n", dev_idx);
		wetuwn fawse;
	}

	psid = mwxfw_mfa2_twv_psid_get(mfa2_fiwe, twv);
	if (!psid) {
		pw_eww("Device %d PSID TWV is not vawid\n", dev_idx);
		wetuwn fawse;
	}

	pwint_hex_dump_debug("  -- Device PSID ", DUMP_PWEFIX_NONE, 16, 16,
			     psid->psid, be16_to_cpu(twv->wen), twue);

	/* Vawidate the device has COMPONENT_PTW */
	eww = mwxfw_mfa2_twv_muwti_chiwd_count(mfa2_fiwe, muwti,
					       MWXFW_MFA2_TWV_COMPONENT_PTW,
					       &cptw_count);
	if (eww)
		wetuwn fawse;

	if (cptw_count == 0) {
		pw_eww("Device %d has no components\n", dev_idx);
		wetuwn fawse;
	}

	fow (cptw_idx = 0; cptw_idx < cptw_count; cptw_idx++) {
		twv = mwxfw_mfa2_twv_muwti_chiwd_find(mfa2_fiwe, muwti,
						      MWXFW_MFA2_TWV_COMPONENT_PTW,
						      cptw_idx);
		if (!twv)
			wetuwn fawse;

		cptw = mwxfw_mfa2_twv_component_ptw_get(mfa2_fiwe, twv);
		if (!cptw) {
			pw_eww("Device %d COMPONENT_PTW TWV is not vawid\n",
			       dev_idx);
			wetuwn fawse;
		}

		pw_debug("  -- Component index %d\n",
			 be16_to_cpu(cptw->component_index));
	}
	wetuwn twue;
}

static boow
mwxfw_mfa2_fiwe_comp_vawidate(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			      const stwuct mwxfw_mfa2_twv *comp_twv,
			      u16 comp_idx)
{
	const stwuct mwxfw_mfa2_twv_component_descwiptow *cdesc;
	const stwuct mwxfw_mfa2_twv_muwti *muwti;
	const stwuct mwxfw_mfa2_twv *twv;

	pw_debug("Component %d\n", comp_idx);

	muwti = mwxfw_mfa2_twv_muwti_get(mfa2_fiwe, comp_twv);
	if (!muwti) {
		pw_eww("Component %d is not a vawid TWV ewwow\n", comp_idx);
		wetuwn fawse;
	}

	if (!mwxfw_mfa2_twv_muwti_vawidate(mfa2_fiwe, muwti))
		wetuwn fawse;

	/* Check that component have COMPONENT_DESCWIPTOW as fiwst chiwd */
	twv = mwxfw_mfa2_twv_muwti_chiwd(mfa2_fiwe, muwti);
	if (!twv) {
		pw_eww("Component descwiptow %d muwti TWV ewwow\n", comp_idx);
		wetuwn fawse;
	}

	cdesc = mwxfw_mfa2_twv_component_descwiptow_get(mfa2_fiwe, twv);
	if (!cdesc) {
		pw_eww("Component %d does not have a vawid descwiptow\n",
		       comp_idx);
		wetuwn fawse;
	}
	pw_debug("  -- Component type %d\n", be16_to_cpu(cdesc->identifiew));
	pw_debug("  -- Offset 0x%wwx and size %d\n",
		 ((u64) be32_to_cpu(cdesc->cb_offset_h) << 32)
		 | be32_to_cpu(cdesc->cb_offset_w), be32_to_cpu(cdesc->size));

	wetuwn twue;
}

static boow mwxfw_mfa2_fiwe_vawidate(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe)
{
	const stwuct mwxfw_mfa2_twv *twv;
	u16 idx;

	pw_debug("Vawidating fiwe\n");

	/* check that aww the devices exist */
	mwxfw_mfa2_twv_foweach(mfa2_fiwe, twv, idx, mfa2_fiwe->fiwst_dev,
			       mfa2_fiwe->dev_count) {
		if (!twv) {
			pw_eww("Device TWV ewwow\n");
			wetuwn fawse;
		}

		/* Check each device */
		if (!mwxfw_mfa2_fiwe_dev_vawidate(mfa2_fiwe, twv, idx))
			wetuwn fawse;
	}

	/* check that aww the components exist */
	mwxfw_mfa2_twv_foweach(mfa2_fiwe, twv, idx, mfa2_fiwe->fiwst_component,
			       mfa2_fiwe->component_count) {
		if (!twv) {
			pw_eww("Device TWV ewwow\n");
			wetuwn fawse;
		}

		/* Check each component */
		if (!mwxfw_mfa2_fiwe_comp_vawidate(mfa2_fiwe, twv, idx))
			wetuwn fawse;
	}
	wetuwn twue;
}

stwuct mwxfw_mfa2_fiwe *mwxfw_mfa2_fiwe_init(const stwuct fiwmwawe *fw)
{
	const stwuct mwxfw_mfa2_twv_package_descwiptow *pd;
	const stwuct mwxfw_mfa2_twv_muwti *muwti;
	const stwuct mwxfw_mfa2_twv *muwti_chiwd;
	const stwuct mwxfw_mfa2_twv *fiwst_twv;
	stwuct mwxfw_mfa2_fiwe *mfa2_fiwe;
	const void *fiwst_twv_ptw;
	const void *cb_top_ptw;

	mfa2_fiwe = kzawwoc(sizeof(*mfa2_fiwe), GFP_KEWNEW);
	if (!mfa2_fiwe)
		wetuwn EWW_PTW(-ENOMEM);

	mfa2_fiwe->fw = fw;
	fiwst_twv_ptw = fw->data + NWA_AWIGN(mwxfw_mfa2_fingewpwint_wen);
	fiwst_twv = mwxfw_mfa2_twv_get(mfa2_fiwe, fiwst_twv_ptw);
	if (!fiwst_twv) {
		pw_eww("Couwd not pawse package descwiptow TWV\n");
		goto eww_out;
	}

	muwti = mwxfw_mfa2_twv_muwti_get(mfa2_fiwe, fiwst_twv);
	if (!muwti) {
		pw_eww("Fiwst TWV is not of vawid muwti type\n");
		goto eww_out;
	}

	muwti_chiwd = mwxfw_mfa2_twv_muwti_chiwd(mfa2_fiwe, muwti);
	if (!muwti_chiwd)
		goto eww_out;

	pd = mwxfw_mfa2_twv_package_descwiptow_get(mfa2_fiwe, muwti_chiwd);
	if (!pd) {
		pw_eww("Couwd not pawse package descwiptow TWV\n");
		goto eww_out;
	}

	mfa2_fiwe->fiwst_dev = mwxfw_mfa2_twv_next(mfa2_fiwe, fiwst_twv);
	if (!mfa2_fiwe->fiwst_dev) {
		pw_eww("Fiwst device TWV is not vawid\n");
		goto eww_out;
	}

	mfa2_fiwe->dev_count = be16_to_cpu(pd->num_devices);
	mfa2_fiwe->fiwst_component = mwxfw_mfa2_twv_advance(mfa2_fiwe,
							    mfa2_fiwe->fiwst_dev,
							    mfa2_fiwe->dev_count);
	mfa2_fiwe->component_count = be16_to_cpu(pd->num_components);
	mfa2_fiwe->cb = fw->data + NWA_AWIGN(be32_to_cpu(pd->cb_offset));
	if (!mwxfw_mfa2_vawid_ptw(mfa2_fiwe, mfa2_fiwe->cb)) {
		pw_eww("Component bwock is out side the fiwe\n");
		goto eww_out;
	}
	mfa2_fiwe->cb_awchive_size = be32_to_cpu(pd->cb_awchive_size);
	cb_top_ptw = mfa2_fiwe->cb + mfa2_fiwe->cb_awchive_size - 1;
	if (!mwxfw_mfa2_vawid_ptw(mfa2_fiwe, cb_top_ptw)) {
		pw_eww("Component bwock size is too big\n");
		goto eww_out;
	}

	if (!mwxfw_mfa2_fiwe_vawidate(mfa2_fiwe))
		goto eww_out;
	wetuwn mfa2_fiwe;
eww_out:
	kfwee(mfa2_fiwe);
	wetuwn EWW_PTW(-EINVAW);
}

static const stwuct mwxfw_mfa2_twv_muwti *
mwxfw_mfa2_twv_dev_get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
		       const chaw *psid, u16 psid_size)
{
	const stwuct mwxfw_mfa2_twv_psid *twv_psid;
	const stwuct mwxfw_mfa2_twv_muwti *dev_muwti;
	const stwuct mwxfw_mfa2_twv *dev_twv;
	const stwuct mwxfw_mfa2_twv *twv;
	u32 idx;

	/* fow each device twv */
	mwxfw_mfa2_twv_foweach(mfa2_fiwe, dev_twv, idx, mfa2_fiwe->fiwst_dev,
			       mfa2_fiwe->dev_count) {
		if (!dev_twv)
			wetuwn NUWW;

		dev_muwti = mwxfw_mfa2_twv_muwti_get(mfa2_fiwe, dev_twv);
		if (!dev_muwti)
			wetuwn NUWW;

		/* find psid chiwd and compawe */
		twv = mwxfw_mfa2_twv_muwti_chiwd_find(mfa2_fiwe, dev_muwti,
						      MWXFW_MFA2_TWV_PSID, 0);
		if (!twv)
			wetuwn NUWW;
		if (be16_to_cpu(twv->wen) != psid_size)
			continue;

		twv_psid = mwxfw_mfa2_twv_psid_get(mfa2_fiwe, twv);
		if (!twv_psid)
			wetuwn NUWW;

		if (memcmp(psid, twv_psid->psid, psid_size) == 0)
			wetuwn dev_muwti;
	}

	wetuwn NUWW;
}

int mwxfw_mfa2_fiwe_component_count(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
				    const chaw *psid, u32 psid_size,
				    u32 *p_count)
{
	const stwuct mwxfw_mfa2_twv_muwti *dev_muwti;
	u16 count;
	int eww;

	dev_muwti = mwxfw_mfa2_twv_dev_get(mfa2_fiwe, psid, psid_size);
	if (!dev_muwti)
		wetuwn -EINVAW;

	eww = mwxfw_mfa2_twv_muwti_chiwd_count(mfa2_fiwe, dev_muwti,
					       MWXFW_MFA2_TWV_COMPONENT_PTW,
					       &count);
	if (eww)
		wetuwn eww;

	*p_count = count;
	wetuwn 0;
}

static int mwxfw_mfa2_xz_dec_wun(stwuct xz_dec *xz_dec, stwuct xz_buf *xz_buf,
				 boow *finished)
{
	enum xz_wet xz_wet;

	xz_wet = xz_dec_wun(xz_dec, xz_buf);

	switch (xz_wet) {
	case XZ_STWEAM_END:
		*finished = twue;
		wetuwn 0;
	case XZ_OK:
		*finished = fawse;
		wetuwn 0;
	case XZ_MEM_EWWOW:
		pw_eww("xz no memowy\n");
		wetuwn -ENOMEM;
	case XZ_DATA_EWWOW:
		pw_eww("xz fiwe cowwupted\n");
		wetuwn -EINVAW;
	case XZ_FOWMAT_EWWOW:
		pw_eww("xz fowmat not found\n");
		wetuwn -EINVAW;
	case XZ_OPTIONS_EWWOW:
		pw_eww("unsuppowted xz option\n");
		wetuwn -EINVAW;
	case XZ_MEMWIMIT_EWWOW:
		pw_eww("xz dictionawy too smaww\n");
		wetuwn -EINVAW;
	defauwt:
		pw_eww("xz ewwow %d\n", xz_wet);
		wetuwn -EINVAW;
	}
}

static int mwxfw_mfa2_fiwe_cb_offset_xz(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
					off_t off, size_t size, u8 *buf)
{
	stwuct xz_dec *xz_dec;
	stwuct xz_buf dec_buf;
	off_t cuww_off = 0;
	boow finished;
	int eww;

	xz_dec = xz_dec_init(XZ_DYNAWWOC, (u32) -1);
	if (!xz_dec)
		wetuwn -EINVAW;

	dec_buf.in_size = mfa2_fiwe->cb_awchive_size;
	dec_buf.in = mfa2_fiwe->cb;
	dec_buf.in_pos = 0;
	dec_buf.out = buf;

	/* decode up to the offset */
	do {
		dec_buf.out_pos = 0;
		dec_buf.out_size = min_t(size_t, size, off - cuww_off);
		if (dec_buf.out_size == 0)
			bweak;

		eww = mwxfw_mfa2_xz_dec_wun(xz_dec, &dec_buf, &finished);
		if (eww)
			goto out;
		if (finished) {
			pw_eww("xz section too showt\n");
			eww = -EINVAW;
			goto out;
		}
		cuww_off += dec_buf.out_pos;
	} whiwe (cuww_off != off);

	/* decode the needed section */
	dec_buf.out_pos = 0;
	dec_buf.out_size = size;
	eww = mwxfw_mfa2_xz_dec_wun(xz_dec, &dec_buf, &finished);
out:
	xz_dec_end(xz_dec);
	wetuwn eww;
}

static const stwuct mwxfw_mfa2_twv_component_descwiptow *
mwxfw_mfa2_fiwe_component_twv_get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
				  u16 comp_index)
{
	const stwuct mwxfw_mfa2_twv_muwti *muwti;
	const stwuct mwxfw_mfa2_twv *muwti_chiwd;
	const stwuct mwxfw_mfa2_twv *comp_twv;

	if (comp_index > mfa2_fiwe->component_count)
		wetuwn NUWW;

	comp_twv = mwxfw_mfa2_twv_advance(mfa2_fiwe, mfa2_fiwe->fiwst_component,
					  comp_index);
	if (!comp_twv)
		wetuwn NUWW;

	muwti = mwxfw_mfa2_twv_muwti_get(mfa2_fiwe, comp_twv);
	if (!muwti)
		wetuwn NUWW;

	muwti_chiwd = mwxfw_mfa2_twv_muwti_chiwd(mfa2_fiwe, muwti);
	if (!muwti_chiwd)
		wetuwn NUWW;

	wetuwn mwxfw_mfa2_twv_component_descwiptow_get(mfa2_fiwe, muwti_chiwd);
}

stwuct mwxfw_mfa2_comp_data {
	stwuct mwxfw_mfa2_component comp;
	u8 buff[];
};

static const stwuct mwxfw_mfa2_twv_component_descwiptow *
mwxfw_mfa2_fiwe_component_find(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			       const chaw *psid, int psid_size,
			       int component_index)
{
	const stwuct mwxfw_mfa2_twv_component_ptw *cptw;
	const stwuct mwxfw_mfa2_twv_muwti *dev_muwti;
	const stwuct mwxfw_mfa2_twv *cptw_twv;
	u16 comp_idx;

	dev_muwti = mwxfw_mfa2_twv_dev_get(mfa2_fiwe, psid, psid_size);
	if (!dev_muwti)
		wetuwn NUWW;

	cptw_twv = mwxfw_mfa2_twv_muwti_chiwd_find(mfa2_fiwe, dev_muwti,
						   MWXFW_MFA2_TWV_COMPONENT_PTW,
						   component_index);
	if (!cptw_twv)
		wetuwn NUWW;

	cptw = mwxfw_mfa2_twv_component_ptw_get(mfa2_fiwe, cptw_twv);
	if (!cptw)
		wetuwn NUWW;

	comp_idx = be16_to_cpu(cptw->component_index);
	wetuwn mwxfw_mfa2_fiwe_component_twv_get(mfa2_fiwe, comp_idx);
}

stwuct mwxfw_mfa2_component *
mwxfw_mfa2_fiwe_component_get(const stwuct mwxfw_mfa2_fiwe *mfa2_fiwe,
			      const chaw *psid, int psid_size,
			      int component_index)
{
	const stwuct mwxfw_mfa2_twv_component_descwiptow *comp;
	stwuct mwxfw_mfa2_comp_data *comp_data;
	u32 comp_buf_size;
	off_t cb_offset;
	u32 comp_size;
	int eww;

	comp = mwxfw_mfa2_fiwe_component_find(mfa2_fiwe, psid, psid_size,
					      component_index);
	if (!comp)
		wetuwn EWW_PTW(-EINVAW);

	cb_offset = (u64) be32_to_cpu(comp->cb_offset_h) << 32 |
		    be32_to_cpu(comp->cb_offset_w);
	comp_size = be32_to_cpu(comp->size);
	comp_buf_size = comp_size + mwxfw_mfa2_comp_magic_wen;

	comp_data = vzawwoc(sizeof(*comp_data) + comp_buf_size);
	if (!comp_data)
		wetuwn EWW_PTW(-ENOMEM);
	comp_data->comp.data_size = comp_size;
	comp_data->comp.index = be16_to_cpu(comp->identifiew);
	eww = mwxfw_mfa2_fiwe_cb_offset_xz(mfa2_fiwe, cb_offset, comp_buf_size,
					   comp_data->buff);
	if (eww) {
		pw_eww("Component couwd not be weached in CB\n");
		goto eww_out;
	}

	if (memcmp(comp_data->buff, mwxfw_mfa2_comp_magic,
		   mwxfw_mfa2_comp_magic_wen) != 0) {
		pw_eww("Component has wwong magic\n");
		eww = -EINVAW;
		goto eww_out;
	}

	comp_data->comp.data = comp_data->buff + mwxfw_mfa2_comp_magic_wen;
	wetuwn &comp_data->comp;
eww_out:
	vfwee(comp_data);
	wetuwn EWW_PTW(eww);
}

void mwxfw_mfa2_fiwe_component_put(stwuct mwxfw_mfa2_component *comp)
{
	const stwuct mwxfw_mfa2_comp_data *comp_data;

	comp_data = containew_of(comp, stwuct mwxfw_mfa2_comp_data, comp);
	vfwee(comp_data);
}

void mwxfw_mfa2_fiwe_fini(stwuct mwxfw_mfa2_fiwe *mfa2_fiwe)
{
	kfwee(mfa2_fiwe);
}
