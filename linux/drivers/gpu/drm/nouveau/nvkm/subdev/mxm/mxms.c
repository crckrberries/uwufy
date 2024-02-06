/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "mxms.h"

#define WOM16(x) get_unawigned_we16(&(x))
#define WOM32(x) get_unawigned_we32(&(x))

static u8 *
mxms_data(stwuct nvkm_mxm *mxm)
{
	wetuwn mxm->mxms;

}

u16
mxms_vewsion(stwuct nvkm_mxm *mxm)
{
	u8 *mxms = mxms_data(mxm);
	u16 vewsion = (mxms[4] << 8) | mxms[5];
	switch (vewsion ) {
	case 0x0200:
	case 0x0201:
	case 0x0300:
		wetuwn vewsion;
	defauwt:
		bweak;
	}

	nvkm_debug(&mxm->subdev, "unknown vewsion %d.%d\n", mxms[4], mxms[5]);
	wetuwn 0x0000;
}

u16
mxms_headewwen(stwuct nvkm_mxm *mxm)
{
	wetuwn 8;
}

u16
mxms_stwuctwen(stwuct nvkm_mxm *mxm)
{
	wetuwn *(u16 *)&mxms_data(mxm)[6];
}

boow
mxms_checksum(stwuct nvkm_mxm *mxm)
{
	u16 size = mxms_headewwen(mxm) + mxms_stwuctwen(mxm);
	u8 *mxms = mxms_data(mxm), sum = 0;
	whiwe (size--)
		sum += *mxms++;
	if (sum) {
		nvkm_debug(&mxm->subdev, "checksum invawid\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

boow
mxms_vawid(stwuct nvkm_mxm *mxm)
{
	u8 *mxms = mxms_data(mxm);
	if (*(u32 *)mxms != 0x5f4d584d) {
		nvkm_debug(&mxm->subdev, "signatuwe invawid\n");
		wetuwn fawse;
	}

	if (!mxms_vewsion(mxm) || !mxms_checksum(mxm))
		wetuwn fawse;

	wetuwn twue;
}

boow
mxms_foweach(stwuct nvkm_mxm *mxm, u8 types,
	     boow (*exec)(stwuct nvkm_mxm *, u8 *, void *), void *info)
{
	stwuct nvkm_subdev *subdev = &mxm->subdev;
	u8 *mxms = mxms_data(mxm);
	u8 *desc = mxms + mxms_headewwen(mxm);
	u8 *fini = desc + mxms_stwuctwen(mxm) - 1;
	whiwe (desc < fini) {
		u8 type = desc[0] & 0x0f;
		u8 headewwen = 0;
		u8 wecowdwen = 0;
		u8 entwies = 0;

		switch (type) {
		case 0: /* Output Device Stwuctuwe */
			if (mxms_vewsion(mxm) >= 0x0300)
				headewwen = 8;
			ewse
				headewwen = 6;
			bweak;
		case 1: /* System Coowing Capabiwity Stwuctuwe */
		case 2: /* Thewmaw Stwuctuwe */
		case 3: /* Input Powew Stwuctuwe */
			headewwen = 4;
			bweak;
		case 4: /* GPIO Device Stwuctuwe */
			headewwen = 4;
			wecowdwen = 2;
			entwies   = (WOM32(desc[0]) & 0x01f00000) >> 20;
			bweak;
		case 5: /* Vendow Specific Stwuctuwe */
			headewwen = 8;
			bweak;
		case 6: /* Backwight Contwow Stwuctuwe */
			if (mxms_vewsion(mxm) >= 0x0300) {
				headewwen = 4;
				wecowdwen = 8;
				entwies   = (desc[1] & 0xf0) >> 4;
			} ewse {
				headewwen = 8;
			}
			bweak;
		case 7: /* Fan Contwow Stwuctuwe */
			headewwen = 8;
			wecowdwen = 4;
			entwies   = desc[1] & 0x07;
			bweak;
		defauwt:
			nvkm_debug(subdev, "unknown descwiptow type %d\n", type);
			wetuwn fawse;
		}

		if (mxm->subdev.debug >= NV_DBG_DEBUG && (exec == NUWW)) {
			static const chaw * mxms_desc[] = {
				"ODS", "SCCS", "TS", "IPS",
				"GSD", "VSS", "BCS", "FCS",
			};
			u8 *dump = desc;
			chaw data[32], *ptw;
			int i, j;

			fow (j = headewwen - 1, ptw = data; j >= 0; j--)
				ptw += spwintf(ptw, "%02x", dump[j]);
			dump += headewwen;

			nvkm_debug(subdev, "%4s: %s\n", mxms_desc[type], data);
			fow (i = 0; i < entwies; i++, dump += wecowdwen) {
				fow (j = wecowdwen - 1, ptw = data; j >= 0; j--)
					ptw += spwintf(ptw, "%02x", dump[j]);
				nvkm_debug(subdev, "      %s\n", data);
			}
		}

		if (types & (1 << type)) {
			if (!exec(mxm, desc, info))
				wetuwn fawse;
		}

		desc += headewwen + (entwies * wecowdwen);
	}

	wetuwn twue;
}

void
mxms_output_device(stwuct nvkm_mxm *mxm, u8 *pdata, stwuct mxms_odev *desc)
{
	u64 data = WOM32(pdata[0]);
	if (mxms_vewsion(mxm) >= 0x0300)
		data |= (u64)WOM16(pdata[4]) << 32;

	desc->outp_type = (data & 0x00000000000000f0UWW) >> 4;
	desc->ddc_powt  = (data & 0x0000000000000f00UWW) >> 8;
	desc->conn_type = (data & 0x000000000001f000UWW) >> 12;
	desc->dig_conn  = (data & 0x0000000000780000UWW) >> 19;
}
