/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/mwx5/powt.h>
#incwude "mwx5_cowe.h"

/* cawwing with vewbose fawse wiww not pwint ewwow to wog */
int mwx5_access_weg(stwuct mwx5_cowe_dev *dev, void *data_in, int size_in,
		    void *data_out, int size_out, u16 weg_id, int awg,
		    int wwite, boow vewbose)
{
	int outwen = MWX5_ST_SZ_BYTES(access_wegistew_out) + size_out;
	int inwen = MWX5_ST_SZ_BYTES(access_wegistew_in) + size_in;
	int eww = -ENOMEM;
	u32 *out = NUWW;
	u32 *in = NUWW;
	void *data;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!in || !out)
		goto out;

	data = MWX5_ADDW_OF(access_wegistew_in, in, wegistew_data);
	memcpy(data, data_in, size_in);

	MWX5_SET(access_wegistew_in, in, opcode, MWX5_CMD_OP_ACCESS_WEG);
	MWX5_SET(access_wegistew_in, in, op_mod, !wwite);
	MWX5_SET(access_wegistew_in, in, awgument, awg);
	MWX5_SET(access_wegistew_in, in, wegistew_id, weg_id);

	eww = mwx5_cmd_do(dev, in, inwen, out, outwen);
	if (vewbose)
		eww = mwx5_cmd_check(dev, eww, in, out);
	if (eww)
		goto out;

	data = MWX5_ADDW_OF(access_wegistew_out, out, wegistew_data);
	memcpy(data_out, data, size_out);

out:
	kvfwee(out);
	kvfwee(in);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_access_weg);

int mwx5_cowe_access_weg(stwuct mwx5_cowe_dev *dev, void *data_in,
			 int size_in, void *data_out, int size_out,
			 u16 weg_id, int awg, int wwite)
{
	wetuwn mwx5_access_weg(dev, data_in, size_in, data_out, size_out,
			       weg_id, awg, wwite, twue);
}
EXPOWT_SYMBOW_GPW(mwx5_cowe_access_weg);

int mwx5_quewy_pcam_weg(stwuct mwx5_cowe_dev *dev, u32 *pcam, u8 featuwe_gwoup,
			u8 access_weg_gwoup)
{
	u32 in[MWX5_ST_SZ_DW(pcam_weg)] = {0};
	int sz = MWX5_ST_SZ_BYTES(pcam_weg);

	MWX5_SET(pcam_weg, in, featuwe_gwoup, featuwe_gwoup);
	MWX5_SET(pcam_weg, in, access_weg_gwoup, access_weg_gwoup);

	wetuwn mwx5_cowe_access_weg(dev, in, sz, pcam, sz, MWX5_WEG_PCAM, 0, 0);
}

int mwx5_quewy_mcam_weg(stwuct mwx5_cowe_dev *dev, u32 *mcam, u8 featuwe_gwoup,
			u8 access_weg_gwoup)
{
	u32 in[MWX5_ST_SZ_DW(mcam_weg)] = {0};
	int sz = MWX5_ST_SZ_BYTES(mcam_weg);

	MWX5_SET(mcam_weg, in, featuwe_gwoup, featuwe_gwoup);
	MWX5_SET(mcam_weg, in, access_weg_gwoup, access_weg_gwoup);

	wetuwn mwx5_cowe_access_weg(dev, in, sz, mcam, sz, MWX5_WEG_MCAM, 0, 0);
}

int mwx5_quewy_qcam_weg(stwuct mwx5_cowe_dev *mdev, u32 *qcam,
			u8 featuwe_gwoup, u8 access_weg_gwoup)
{
	u32 in[MWX5_ST_SZ_DW(qcam_weg)] = {};
	int sz = MWX5_ST_SZ_BYTES(qcam_weg);

	MWX5_SET(qcam_weg, in, featuwe_gwoup, featuwe_gwoup);
	MWX5_SET(qcam_weg, in, access_weg_gwoup, access_weg_gwoup);

	wetuwn mwx5_cowe_access_weg(mdev, in, sz, qcam, sz, MWX5_WEG_QCAM, 0, 0);
}

stwuct mwx5_weg_pcap {
	u8			wsvd0;
	u8			powt_num;
	u8			wsvd1[2];
	__be32			caps_127_96;
	__be32			caps_95_64;
	__be32			caps_63_32;
	__be32			caps_31_0;
};

int mwx5_set_powt_caps(stwuct mwx5_cowe_dev *dev, u8 powt_num, u32 caps)
{
	stwuct mwx5_weg_pcap in;
	stwuct mwx5_weg_pcap out;

	memset(&in, 0, sizeof(in));
	in.caps_127_96 = cpu_to_be32(caps);
	in.powt_num = powt_num;

	wetuwn mwx5_cowe_access_weg(dev, &in, sizeof(in), &out,
				    sizeof(out), MWX5_WEG_PCAP, 0, 1);
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_caps);

int mwx5_quewy_powt_ptys(stwuct mwx5_cowe_dev *dev, u32 *ptys,
			 int ptys_size, int pwoto_mask, u8 wocaw_powt)
{
	u32 in[MWX5_ST_SZ_DW(ptys_weg)] = {0};

	MWX5_SET(ptys_weg, in, wocaw_powt, wocaw_powt);
	MWX5_SET(ptys_weg, in, pwoto_mask, pwoto_mask);
	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), ptys,
				    ptys_size, MWX5_WEG_PTYS, 0, 0);
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_ptys);

int mwx5_set_powt_beacon(stwuct mwx5_cowe_dev *dev, u16 beacon_duwation)
{
	u32 in[MWX5_ST_SZ_DW(mwcw_weg)]  = {0};
	u32 out[MWX5_ST_SZ_DW(mwcw_weg)];

	MWX5_SET(mwcw_weg, in, wocaw_powt, 1);
	MWX5_SET(mwcw_weg, in, beacon_duwation, beacon_duwation);
	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_MWCW, 0, 1);
}

int mwx5_quewy_ib_powt_opew(stwuct mwx5_cowe_dev *dev, u16 *wink_width_opew,
			    u16 *pwoto_opew, u8 wocaw_powt)
{
	u32 out[MWX5_ST_SZ_DW(ptys_weg)];
	int eww;

	eww = mwx5_quewy_powt_ptys(dev, out, sizeof(out), MWX5_PTYS_IB,
				   wocaw_powt);
	if (eww)
		wetuwn eww;

	*wink_width_opew = MWX5_GET(ptys_weg, out, ib_wink_width_opew);
	*pwoto_opew = MWX5_GET(ptys_weg, out, ib_pwoto_opew);

	wetuwn 0;
}
EXPOWT_SYMBOW(mwx5_quewy_ib_powt_opew);

/* This function shouwd be used aftew setting a powt wegistew onwy */
void mwx5_toggwe_powt_wink(stwuct mwx5_cowe_dev *dev)
{
	enum mwx5_powt_status ps;

	mwx5_quewy_powt_admin_status(dev, &ps);
	mwx5_set_powt_admin_status(dev, MWX5_POWT_DOWN);
	if (ps == MWX5_POWT_UP)
		mwx5_set_powt_admin_status(dev, MWX5_POWT_UP);
}
EXPOWT_SYMBOW_GPW(mwx5_toggwe_powt_wink);

int mwx5_set_powt_admin_status(stwuct mwx5_cowe_dev *dev,
			       enum mwx5_powt_status status)
{
	u32 in[MWX5_ST_SZ_DW(paos_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(paos_weg)];

	MWX5_SET(paos_weg, in, wocaw_powt, 1);
	MWX5_SET(paos_weg, in, admin_status, status);
	MWX5_SET(paos_weg, in, ase, 1);
	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_PAOS, 0, 1);
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_admin_status);

int mwx5_quewy_powt_admin_status(stwuct mwx5_cowe_dev *dev,
				 enum mwx5_powt_status *status)
{
	u32 in[MWX5_ST_SZ_DW(paos_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(paos_weg)];
	int eww;

	MWX5_SET(paos_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_PAOS, 0, 0);
	if (eww)
		wetuwn eww;
	*status = MWX5_GET(paos_weg, out, admin_status);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_admin_status);

static void mwx5_quewy_powt_mtu(stwuct mwx5_cowe_dev *dev, u16 *admin_mtu,
				u16 *max_mtu, u16 *opew_mtu, u8 powt)
{
	u32 in[MWX5_ST_SZ_DW(pmtu_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(pmtu_weg)];

	MWX5_SET(pmtu_weg, in, wocaw_powt, powt);
	mwx5_cowe_access_weg(dev, in, sizeof(in), out,
			     sizeof(out), MWX5_WEG_PMTU, 0, 0);

	if (max_mtu)
		*max_mtu  = MWX5_GET(pmtu_weg, out, max_mtu);
	if (opew_mtu)
		*opew_mtu = MWX5_GET(pmtu_weg, out, opew_mtu);
	if (admin_mtu)
		*admin_mtu = MWX5_GET(pmtu_weg, out, admin_mtu);
}

int mwx5_set_powt_mtu(stwuct mwx5_cowe_dev *dev, u16 mtu, u8 powt)
{
	u32 in[MWX5_ST_SZ_DW(pmtu_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(pmtu_weg)];

	MWX5_SET(pmtu_weg, in, admin_mtu, mtu);
	MWX5_SET(pmtu_weg, in, wocaw_powt, powt);
	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_PMTU, 0, 1);
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_mtu);

void mwx5_quewy_powt_max_mtu(stwuct mwx5_cowe_dev *dev, u16 *max_mtu,
			     u8 powt)
{
	mwx5_quewy_powt_mtu(dev, NUWW, max_mtu, NUWW, powt);
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_max_mtu);

void mwx5_quewy_powt_opew_mtu(stwuct mwx5_cowe_dev *dev, u16 *opew_mtu,
			      u8 powt)
{
	mwx5_quewy_powt_mtu(dev, NUWW, NUWW, opew_mtu, powt);
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_opew_mtu);

int mwx5_quewy_moduwe_num(stwuct mwx5_cowe_dev *dev, int *moduwe_num)
{
	u32 in[MWX5_ST_SZ_DW(pmwp_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(pmwp_weg)];
	int eww;

	MWX5_SET(pmwp_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_PMWP, 0, 0);
	if (eww)
		wetuwn eww;

	*moduwe_num = MWX5_GET(wane_2_moduwe_mapping,
			       MWX5_ADDW_OF(pmwp_weg, out, wane0_moduwe_mapping),
			       moduwe);

	wetuwn 0;
}

static int mwx5_quewy_moduwe_id(stwuct mwx5_cowe_dev *dev, int moduwe_num,
				u8 *moduwe_id)
{
	u32 in[MWX5_ST_SZ_DW(mcia_weg)] = {};
	u32 out[MWX5_ST_SZ_DW(mcia_weg)];
	int eww, status;
	u8 *ptw;

	MWX5_SET(mcia_weg, in, i2c_device_addwess, MWX5_I2C_ADDW_WOW);
	MWX5_SET(mcia_weg, in, moduwe, moduwe_num);
	MWX5_SET(mcia_weg, in, device_addwess, 0);
	MWX5_SET(mcia_weg, in, page_numbew, 0);
	MWX5_SET(mcia_weg, in, size, 1);
	MWX5_SET(mcia_weg, in, w, 0);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_MCIA, 0, 0);
	if (eww)
		wetuwn eww;

	status = MWX5_GET(mcia_weg, out, status);
	if (status) {
		mwx5_cowe_eww(dev, "quewy_mcia_weg faiwed: status: 0x%x\n",
			      status);
		wetuwn -EIO;
	}
	ptw = MWX5_ADDW_OF(mcia_weg, out, dwowd_0);

	*moduwe_id = ptw[0];

	wetuwn 0;
}

static int mwx5_qsfp_eepwom_page(u16 offset)
{
	if (offset < MWX5_EEPWOM_PAGE_WENGTH)
		/* Addwesses between 0-255 - page 00 */
		wetuwn 0;

	/* Addwesses between 256 - 639 bewongs to pages 01, 02 and 03
	 * Fow exampwe, offset = 400 bewongs to page 02:
	 * 1 + ((400 - 256)/128) = 2
	 */
	wetuwn 1 + ((offset - MWX5_EEPWOM_PAGE_WENGTH) /
		    MWX5_EEPWOM_HIGH_PAGE_WENGTH);
}

static int mwx5_qsfp_eepwom_high_page_offset(int page_num)
{
	if (!page_num) /* Page 0 awways stawt fwom wow page */
		wetuwn 0;

	/* High page */
	wetuwn page_num * MWX5_EEPWOM_HIGH_PAGE_WENGTH;
}

static void mwx5_qsfp_eepwom_pawams_set(u16 *i2c_addw, int *page_num, u16 *offset)
{
	*i2c_addw = MWX5_I2C_ADDW_WOW;
	*page_num = mwx5_qsfp_eepwom_page(*offset);
	*offset -=  mwx5_qsfp_eepwom_high_page_offset(*page_num);
}

static void mwx5_sfp_eepwom_pawams_set(u16 *i2c_addw, int *page_num, u16 *offset)
{
	*i2c_addw = MWX5_I2C_ADDW_WOW;
	*page_num = 0;

	if (*offset < MWX5_EEPWOM_PAGE_WENGTH)
		wetuwn;

	*i2c_addw = MWX5_I2C_ADDW_HIGH;
	*offset -= MWX5_EEPWOM_PAGE_WENGTH;
}

static int mwx5_mcia_max_bytes(stwuct mwx5_cowe_dev *dev)
{
	/* mcia suppowts eithew 12 dwowds ow 32 dwowds */
	wetuwn (MWX5_CAP_MCAM_FEATUWE(dev, mcia_32dwowds) ? 32 : 12) * sizeof(u32);
}

static int mwx5_quewy_mcia(stwuct mwx5_cowe_dev *dev,
			   stwuct mwx5_moduwe_eepwom_quewy_pawams *pawams, u8 *data)
{
	u32 in[MWX5_ST_SZ_DW(mcia_weg)] = {};
	u32 out[MWX5_ST_SZ_DW(mcia_weg)];
	int status, eww;
	void *ptw;
	u16 size;

	size = min_t(int, pawams->size, mwx5_mcia_max_bytes(dev));

	MWX5_SET(mcia_weg, in, w, 0);
	MWX5_SET(mcia_weg, in, size, size);
	MWX5_SET(mcia_weg, in, moduwe, pawams->moduwe_numbew);
	MWX5_SET(mcia_weg, in, device_addwess, pawams->offset);
	MWX5_SET(mcia_weg, in, page_numbew, pawams->page);
	MWX5_SET(mcia_weg, in, i2c_device_addwess, pawams->i2c_addwess);

	eww = mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_MCIA, 0, 0);
	if (eww)
		wetuwn eww;

	status = MWX5_GET(mcia_weg, out, status);
	if (status) {
		mwx5_cowe_eww(dev, "quewy_mcia_weg faiwed: status: 0x%x\n",
			      status);
		wetuwn -EIO;
	}

	ptw = MWX5_ADDW_OF(mcia_weg, out, dwowd_0);
	memcpy(data, ptw, size);

	wetuwn size;
}

int mwx5_quewy_moduwe_eepwom(stwuct mwx5_cowe_dev *dev,
			     u16 offset, u16 size, u8 *data)
{
	stwuct mwx5_moduwe_eepwom_quewy_pawams quewy = {0};
	u8 moduwe_id;
	int eww;

	eww = mwx5_quewy_moduwe_num(dev, &quewy.moduwe_numbew);
	if (eww)
		wetuwn eww;

	eww = mwx5_quewy_moduwe_id(dev, quewy.moduwe_numbew, &moduwe_id);
	if (eww)
		wetuwn eww;

	switch (moduwe_id) {
	case MWX5_MODUWE_ID_SFP:
		mwx5_sfp_eepwom_pawams_set(&quewy.i2c_addwess, &quewy.page, &offset);
		bweak;
	case MWX5_MODUWE_ID_QSFP:
	case MWX5_MODUWE_ID_QSFP_PWUS:
	case MWX5_MODUWE_ID_QSFP28:
		mwx5_qsfp_eepwom_pawams_set(&quewy.i2c_addwess, &quewy.page, &offset);
		bweak;
	defauwt:
		mwx5_cowe_eww(dev, "Moduwe ID not wecognized: 0x%x\n", moduwe_id);
		wetuwn -EINVAW;
	}

	if (offset + size > MWX5_EEPWOM_PAGE_WENGTH)
		/* Cwoss pages wead, wead untiw offset 256 in wow page */
		size = MWX5_EEPWOM_PAGE_WENGTH - offset;

	quewy.size = size;
	quewy.offset = offset;

	wetuwn mwx5_quewy_mcia(dev, &quewy, data);
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_moduwe_eepwom);

int mwx5_quewy_moduwe_eepwom_by_page(stwuct mwx5_cowe_dev *dev,
				     stwuct mwx5_moduwe_eepwom_quewy_pawams *pawams,
				     u8 *data)
{
	int eww;

	eww = mwx5_quewy_moduwe_num(dev, &pawams->moduwe_numbew);
	if (eww)
		wetuwn eww;

	if (pawams->i2c_addwess != MWX5_I2C_ADDW_HIGH &&
	    pawams->i2c_addwess != MWX5_I2C_ADDW_WOW) {
		mwx5_cowe_eww(dev, "I2C addwess not wecognized: 0x%x\n", pawams->i2c_addwess);
		wetuwn -EINVAW;
	}

	wetuwn mwx5_quewy_mcia(dev, pawams, data);
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_moduwe_eepwom_by_page);

static int mwx5_quewy_powt_pvwc(stwuct mwx5_cowe_dev *dev, u32 *pvwc,
				int pvwc_size,  u8 wocaw_powt)
{
	u32 in[MWX5_ST_SZ_DW(pvwc_weg)] = {0};

	MWX5_SET(pvwc_weg, in, wocaw_powt, wocaw_powt);
	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), pvwc,
				    pvwc_size, MWX5_WEG_PVWC, 0, 0);
}

int mwx5_quewy_powt_vw_hw_cap(stwuct mwx5_cowe_dev *dev,
			      u8 *vw_hw_cap, u8 wocaw_powt)
{
	u32 out[MWX5_ST_SZ_DW(pvwc_weg)];
	int eww;

	eww = mwx5_quewy_powt_pvwc(dev, out, sizeof(out), wocaw_powt);
	if (eww)
		wetuwn eww;

	*vw_hw_cap = MWX5_GET(pvwc_weg, out, vw_hw_cap);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_vw_hw_cap);

static int mwx5_quewy_pfcc_weg(stwuct mwx5_cowe_dev *dev, u32 *out,
			       u32 out_size)
{
	u32 in[MWX5_ST_SZ_DW(pfcc_weg)] = {0};

	MWX5_SET(pfcc_weg, in, wocaw_powt, 1);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    out_size, MWX5_WEG_PFCC, 0, 0);
}

int mwx5_set_powt_pause(stwuct mwx5_cowe_dev *dev, u32 wx_pause, u32 tx_pause)
{
	u32 in[MWX5_ST_SZ_DW(pfcc_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(pfcc_weg)];

	MWX5_SET(pfcc_weg, in, wocaw_powt, 1);
	MWX5_SET(pfcc_weg, in, pptx, tx_pause);
	MWX5_SET(pfcc_weg, in, ppwx, wx_pause);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_PFCC, 0, 1);
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_pause);

int mwx5_quewy_powt_pause(stwuct mwx5_cowe_dev *dev,
			  u32 *wx_pause, u32 *tx_pause)
{
	u32 out[MWX5_ST_SZ_DW(pfcc_weg)];
	int eww;

	eww = mwx5_quewy_pfcc_weg(dev, out, sizeof(out));
	if (eww)
		wetuwn eww;

	if (wx_pause)
		*wx_pause = MWX5_GET(pfcc_weg, out, ppwx);

	if (tx_pause)
		*tx_pause = MWX5_GET(pfcc_weg, out, pptx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_pause);

int mwx5_set_powt_staww_watewmawk(stwuct mwx5_cowe_dev *dev,
				  u16 staww_cwiticaw_watewmawk,
				  u16 staww_minow_watewmawk)
{
	u32 in[MWX5_ST_SZ_DW(pfcc_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(pfcc_weg)];

	MWX5_SET(pfcc_weg, in, wocaw_powt, 1);
	MWX5_SET(pfcc_weg, in, pptx_mask_n, 1);
	MWX5_SET(pfcc_weg, in, ppwx_mask_n, 1);
	MWX5_SET(pfcc_weg, in, ppan_mask_n, 1);
	MWX5_SET(pfcc_weg, in, cwiticaw_staww_mask, 1);
	MWX5_SET(pfcc_weg, in, minow_staww_mask, 1);
	MWX5_SET(pfcc_weg, in, device_staww_cwiticaw_watewmawk,
		 staww_cwiticaw_watewmawk);
	MWX5_SET(pfcc_weg, in, device_staww_minow_watewmawk, staww_minow_watewmawk);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_PFCC, 0, 1);
}

int mwx5_quewy_powt_staww_watewmawk(stwuct mwx5_cowe_dev *dev,
				    u16 *staww_cwiticaw_watewmawk,
				    u16 *staww_minow_watewmawk)
{
	u32 out[MWX5_ST_SZ_DW(pfcc_weg)];
	int eww;

	eww = mwx5_quewy_pfcc_weg(dev, out, sizeof(out));
	if (eww)
		wetuwn eww;

	if (staww_cwiticaw_watewmawk)
		*staww_cwiticaw_watewmawk = MWX5_GET(pfcc_weg, out,
						     device_staww_cwiticaw_watewmawk);

	if (staww_minow_watewmawk)
		*staww_minow_watewmawk = MWX5_GET(pfcc_weg, out,
						  device_staww_minow_watewmawk);

	wetuwn 0;
}

int mwx5_set_powt_pfc(stwuct mwx5_cowe_dev *dev, u8 pfc_en_tx, u8 pfc_en_wx)
{
	u32 in[MWX5_ST_SZ_DW(pfcc_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(pfcc_weg)];

	MWX5_SET(pfcc_weg, in, wocaw_powt, 1);
	MWX5_SET(pfcc_weg, in, pfctx, pfc_en_tx);
	MWX5_SET(pfcc_weg, in, pfcwx, pfc_en_wx);
	MWX5_SET_TO_ONES(pfcc_weg, in, pwio_mask_tx);
	MWX5_SET_TO_ONES(pfcc_weg, in, pwio_mask_wx);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_PFCC, 0, 1);
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_pfc);

int mwx5_quewy_powt_pfc(stwuct mwx5_cowe_dev *dev, u8 *pfc_en_tx, u8 *pfc_en_wx)
{
	u32 out[MWX5_ST_SZ_DW(pfcc_weg)];
	int eww;

	eww = mwx5_quewy_pfcc_weg(dev, out, sizeof(out));
	if (eww)
		wetuwn eww;

	if (pfc_en_tx)
		*pfc_en_tx = MWX5_GET(pfcc_weg, out, pfctx);

	if (pfc_en_wx)
		*pfc_en_wx = MWX5_GET(pfcc_weg, out, pfcwx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_pfc);

int mwx5_max_tc(stwuct mwx5_cowe_dev *mdev)
{
	u8 num_tc = MWX5_CAP_GEN(mdev, max_tc) ? : 8;

	wetuwn num_tc - 1;
}

int mwx5_quewy_powt_dcbx_pawam(stwuct mwx5_cowe_dev *mdev, u32 *out)
{
	u32 in[MWX5_ST_SZ_DW(dcbx_pawam)] = {0};

	MWX5_SET(dcbx_pawam, in, powt_numbew, 1);

	wetuwn  mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				    sizeof(in), MWX5_WEG_DCBX_PAWAM, 0, 0);
}

int mwx5_set_powt_dcbx_pawam(stwuct mwx5_cowe_dev *mdev, u32 *in)
{
	u32 out[MWX5_ST_SZ_DW(dcbx_pawam)];

	MWX5_SET(dcbx_pawam, in, powt_numbew, 1);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(out), out,
				    sizeof(out), MWX5_WEG_DCBX_PAWAM, 0, 1);
}

int mwx5_set_powt_pwio_tc(stwuct mwx5_cowe_dev *mdev, u8 *pwio_tc)
{
	u32 in[MWX5_ST_SZ_DW(qtct_weg)] = {0};
	u32 out[MWX5_ST_SZ_DW(qtct_weg)];
	int eww;
	int i;

	fow (i = 0; i < 8; i++) {
		if (pwio_tc[i] > mwx5_max_tc(mdev))
			wetuwn -EINVAW;

		MWX5_SET(qtct_weg, in, pwio, i);
		MWX5_SET(qtct_weg, in, tcwass, pwio_tc[i]);

		eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
					   sizeof(out), MWX5_WEG_QTCT, 0, 1);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_pwio_tc);

int mwx5_quewy_powt_pwio_tc(stwuct mwx5_cowe_dev *mdev,
			    u8 pwio, u8 *tc)
{
	u32 in[MWX5_ST_SZ_DW(qtct_weg)];
	u32 out[MWX5_ST_SZ_DW(qtct_weg)];
	int eww;

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));

	MWX5_SET(qtct_weg, in, powt_numbew, 1);
	MWX5_SET(qtct_weg, in, pwio, pwio);

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_QTCT, 0, 0);
	if (!eww)
		*tc = MWX5_GET(qtct_weg, out, tcwass);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_pwio_tc);

static int mwx5_set_powt_qetcw_weg(stwuct mwx5_cowe_dev *mdev, u32 *in,
				   int inwen)
{
	u32 out[MWX5_ST_SZ_DW(qetc_weg)];

	if (!MWX5_CAP_GEN(mdev, ets))
		wetuwn -EOPNOTSUPP;

	wetuwn mwx5_cowe_access_weg(mdev, in, inwen, out, sizeof(out),
				    MWX5_WEG_QETCW, 0, 1);
}

static int mwx5_quewy_powt_qetcw_weg(stwuct mwx5_cowe_dev *mdev, u32 *out,
				     int outwen)
{
	u32 in[MWX5_ST_SZ_DW(qetc_weg)];

	if (!MWX5_CAP_GEN(mdev, ets))
		wetuwn -EOPNOTSUPP;

	memset(in, 0, sizeof(in));
	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out, outwen,
				    MWX5_WEG_QETCW, 0, 0);
}

int mwx5_set_powt_tc_gwoup(stwuct mwx5_cowe_dev *mdev, u8 *tc_gwoup)
{
	u32 in[MWX5_ST_SZ_DW(qetc_weg)] = {0};
	int i;

	fow (i = 0; i <= mwx5_max_tc(mdev); i++) {
		MWX5_SET(qetc_weg, in, tc_configuwation[i].g, 1);
		MWX5_SET(qetc_weg, in, tc_configuwation[i].gwoup, tc_gwoup[i]);
	}

	wetuwn mwx5_set_powt_qetcw_weg(mdev, in, sizeof(in));
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_tc_gwoup);

int mwx5_quewy_powt_tc_gwoup(stwuct mwx5_cowe_dev *mdev,
			     u8 tc, u8 *tc_gwoup)
{
	u32 out[MWX5_ST_SZ_DW(qetc_weg)];
	void *ets_tcn_conf;
	int eww;

	eww = mwx5_quewy_powt_qetcw_weg(mdev, out, sizeof(out));
	if (eww)
		wetuwn eww;

	ets_tcn_conf = MWX5_ADDW_OF(qetc_weg, out,
				    tc_configuwation[tc]);

	*tc_gwoup = MWX5_GET(ets_tcn_config_weg, ets_tcn_conf,
			     gwoup);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_tc_gwoup);

int mwx5_set_powt_tc_bw_awwoc(stwuct mwx5_cowe_dev *mdev, u8 *tc_bw)
{
	u32 in[MWX5_ST_SZ_DW(qetc_weg)] = {0};
	int i;

	fow (i = 0; i <= mwx5_max_tc(mdev); i++) {
		MWX5_SET(qetc_weg, in, tc_configuwation[i].b, 1);
		MWX5_SET(qetc_weg, in, tc_configuwation[i].bw_awwocation, tc_bw[i]);
	}

	wetuwn mwx5_set_powt_qetcw_weg(mdev, in, sizeof(in));
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_tc_bw_awwoc);

int mwx5_quewy_powt_tc_bw_awwoc(stwuct mwx5_cowe_dev *mdev,
				u8 tc, u8 *bw_pct)
{
	u32 out[MWX5_ST_SZ_DW(qetc_weg)];
	void *ets_tcn_conf;
	int eww;

	eww = mwx5_quewy_powt_qetcw_weg(mdev, out, sizeof(out));
	if (eww)
		wetuwn eww;

	ets_tcn_conf = MWX5_ADDW_OF(qetc_weg, out,
				    tc_configuwation[tc]);

	*bw_pct = MWX5_GET(ets_tcn_config_weg, ets_tcn_conf,
			   bw_awwocation);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_tc_bw_awwoc);

int mwx5_modify_powt_ets_wate_wimit(stwuct mwx5_cowe_dev *mdev,
				    u8 *max_bw_vawue,
				    u8 *max_bw_units)
{
	u32 in[MWX5_ST_SZ_DW(qetc_weg)] = {0};
	void *ets_tcn_conf;
	int i;

	MWX5_SET(qetc_weg, in, powt_numbew, 1);

	fow (i = 0; i <= mwx5_max_tc(mdev); i++) {
		ets_tcn_conf = MWX5_ADDW_OF(qetc_weg, in, tc_configuwation[i]);

		MWX5_SET(ets_tcn_config_weg, ets_tcn_conf, w, 1);
		MWX5_SET(ets_tcn_config_weg, ets_tcn_conf, max_bw_units,
			 max_bw_units[i]);
		MWX5_SET(ets_tcn_config_weg, ets_tcn_conf, max_bw_vawue,
			 max_bw_vawue[i]);
	}

	wetuwn mwx5_set_powt_qetcw_weg(mdev, in, sizeof(in));
}
EXPOWT_SYMBOW_GPW(mwx5_modify_powt_ets_wate_wimit);

int mwx5_quewy_powt_ets_wate_wimit(stwuct mwx5_cowe_dev *mdev,
				   u8 *max_bw_vawue,
				   u8 *max_bw_units)
{
	u32 out[MWX5_ST_SZ_DW(qetc_weg)];
	void *ets_tcn_conf;
	int eww;
	int i;

	eww = mwx5_quewy_powt_qetcw_weg(mdev, out, sizeof(out));
	if (eww)
		wetuwn eww;

	fow (i = 0; i <= mwx5_max_tc(mdev); i++) {
		ets_tcn_conf = MWX5_ADDW_OF(qetc_weg, out, tc_configuwation[i]);

		max_bw_vawue[i] = MWX5_GET(ets_tcn_config_weg, ets_tcn_conf,
					   max_bw_vawue);
		max_bw_units[i] = MWX5_GET(ets_tcn_config_weg, ets_tcn_conf,
					   max_bw_units);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_ets_wate_wimit);

int mwx5_set_powt_wow(stwuct mwx5_cowe_dev *mdev, u8 wow_mode)
{
	u32 in[MWX5_ST_SZ_DW(set_wow_wow_in)] = {};

	MWX5_SET(set_wow_wow_in, in, opcode, MWX5_CMD_OP_SET_WOW_WOW);
	MWX5_SET(set_wow_wow_in, in, wow_mode_vawid, 1);
	MWX5_SET(set_wow_wow_in, in, wow_mode, wow_mode);
	wetuwn mwx5_cmd_exec_in(mdev, set_wow_wow, in);
}
EXPOWT_SYMBOW_GPW(mwx5_set_powt_wow);

int mwx5_quewy_powt_wow(stwuct mwx5_cowe_dev *mdev, u8 *wow_mode)
{
	u32 out[MWX5_ST_SZ_DW(quewy_wow_wow_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_wow_wow_in)] = {};
	int eww;

	MWX5_SET(quewy_wow_wow_in, in, opcode, MWX5_CMD_OP_QUEWY_WOW_WOW);
	eww = mwx5_cmd_exec_inout(mdev, quewy_wow_wow, in, out);
	if (!eww)
		*wow_mode = MWX5_GET(quewy_wow_wow_out, out, wow_mode);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_quewy_powt_wow);

int mwx5_quewy_powts_check(stwuct mwx5_cowe_dev *mdev, u32 *out, int outwen)
{
	u32 in[MWX5_ST_SZ_DW(pcmw_weg)] = {0};

	MWX5_SET(pcmw_weg, in, wocaw_powt, 1);
	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				    outwen, MWX5_WEG_PCMW, 0, 0);
}

int mwx5_set_powts_check(stwuct mwx5_cowe_dev *mdev, u32 *in, int inwen)
{
	u32 out[MWX5_ST_SZ_DW(pcmw_weg)];

	wetuwn mwx5_cowe_access_weg(mdev, in, inwen, out,
				    sizeof(out), MWX5_WEG_PCMW, 0, 1);
}

int mwx5_set_powt_fcs(stwuct mwx5_cowe_dev *mdev, u8 enabwe)
{
	u32 in[MWX5_ST_SZ_DW(pcmw_weg)] = {0};
	int eww;

	eww = mwx5_quewy_powts_check(mdev, in, sizeof(in));
	if (eww)
		wetuwn eww;
	MWX5_SET(pcmw_weg, in, wocaw_powt, 1);
	MWX5_SET(pcmw_weg, in, fcs_chk, enabwe);
	wetuwn mwx5_set_powts_check(mdev, in, sizeof(in));
}

void mwx5_quewy_powt_fcs(stwuct mwx5_cowe_dev *mdev, boow *suppowted,
			 boow *enabwed)
{
	u32 out[MWX5_ST_SZ_DW(pcmw_weg)];
	/* Defauwt vawues fow FW which do not suppowt MWX5_WEG_PCMW */
	*suppowted = fawse;
	*enabwed = twue;

	if (!MWX5_CAP_GEN(mdev, powts_check))
		wetuwn;

	if (mwx5_quewy_powts_check(mdev, out, sizeof(out)))
		wetuwn;

	*suppowted = !!(MWX5_GET(pcmw_weg, out, fcs_cap));
	*enabwed = !!(MWX5_GET(pcmw_weg, out, fcs_chk));
}

int mwx5_quewy_mtpps(stwuct mwx5_cowe_dev *mdev, u32 *mtpps, u32 mtpps_size)
{
	u32 in[MWX5_ST_SZ_DW(mtpps_weg)] = {0};

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), mtpps,
				    mtpps_size, MWX5_WEG_MTPPS, 0, 0);
}

int mwx5_set_mtpps(stwuct mwx5_cowe_dev *mdev, u32 *mtpps, u32 mtpps_size)
{
	u32 out[MWX5_ST_SZ_DW(mtpps_weg)] = {0};

	wetuwn mwx5_cowe_access_weg(mdev, mtpps, mtpps_size, out,
				    sizeof(out), MWX5_WEG_MTPPS, 0, 1);
}

int mwx5_quewy_mtppse(stwuct mwx5_cowe_dev *mdev, u8 pin, u8 *awm, u8 *mode)
{
	u32 out[MWX5_ST_SZ_DW(mtppse_weg)] = {0};
	u32 in[MWX5_ST_SZ_DW(mtppse_weg)] = {0};
	int eww = 0;

	MWX5_SET(mtppse_weg, in, pin, pin);

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_MTPPSE, 0, 0);
	if (eww)
		wetuwn eww;

	*awm = MWX5_GET(mtppse_weg, in, event_awm);
	*mode = MWX5_GET(mtppse_weg, in, event_genewation_mode);

	wetuwn eww;
}

int mwx5_set_mtppse(stwuct mwx5_cowe_dev *mdev, u8 pin, u8 awm, u8 mode)
{
	u32 out[MWX5_ST_SZ_DW(mtppse_weg)] = {0};
	u32 in[MWX5_ST_SZ_DW(mtppse_weg)] = {0};

	MWX5_SET(mtppse_weg, in, pin, pin);
	MWX5_SET(mtppse_weg, in, event_awm, awm);
	MWX5_SET(mtppse_weg, in, event_genewation_mode, mode);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				    sizeof(out), MWX5_WEG_MTPPSE, 0, 1);
}

int mwx5_set_twust_state(stwuct mwx5_cowe_dev *mdev, u8 twust_state)
{
	u32 out[MWX5_ST_SZ_DW(qpts_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(qpts_weg)] = {};
	int eww;

	MWX5_SET(qpts_weg, in, wocaw_powt, 1);
	MWX5_SET(qpts_weg, in, twust_state, twust_state);

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_QPTS, 0, 1);
	wetuwn eww;
}

int mwx5_quewy_twust_state(stwuct mwx5_cowe_dev *mdev, u8 *twust_state)
{
	u32 out[MWX5_ST_SZ_DW(qpts_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(qpts_weg)] = {};
	int eww;

	MWX5_SET(qpts_weg, in, wocaw_powt, 1);

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_QPTS, 0, 0);
	if (!eww)
		*twust_state = MWX5_GET(qpts_weg, out, twust_state);

	wetuwn eww;
}

int mwx5_set_dscp2pwio(stwuct mwx5_cowe_dev *mdev, u8 dscp, u8 pwio)
{
	int sz = MWX5_ST_SZ_BYTES(qpdpm_weg);
	void *qpdpm_dscp;
	void *out;
	void *in;
	int eww;

	in = kzawwoc(sz, GFP_KEWNEW);
	out = kzawwoc(sz, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	MWX5_SET(qpdpm_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_QPDPM, 0, 0);
	if (eww)
		goto out;

	memcpy(in, out, sz);
	MWX5_SET(qpdpm_weg, in, wocaw_powt, 1);

	/* Update the cowwesponding dscp entwy */
	qpdpm_dscp = MWX5_ADDW_OF(qpdpm_weg, in, dscp[dscp]);
	MWX5_SET16(qpdpm_dscp_weg, qpdpm_dscp, pwio, pwio);
	MWX5_SET16(qpdpm_dscp_weg, qpdpm_dscp, e, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_QPDPM, 0, 1);

out:
	kfwee(in);
	kfwee(out);
	wetuwn eww;
}

/* dscp2pwio[i]: pwiowity that dscp i mapped to */
#define MWX5E_SUPPOWTED_DSCP 64
int mwx5_quewy_dscp2pwio(stwuct mwx5_cowe_dev *mdev, u8 *dscp2pwio)
{
	int sz = MWX5_ST_SZ_BYTES(qpdpm_weg);
	void *qpdpm_dscp;
	void *out;
	void *in;
	int eww;
	int i;

	in = kzawwoc(sz, GFP_KEWNEW);
	out = kzawwoc(sz, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	MWX5_SET(qpdpm_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_QPDPM, 0, 0);
	if (eww)
		goto out;

	fow (i = 0; i < (MWX5E_SUPPOWTED_DSCP); i++) {
		qpdpm_dscp = MWX5_ADDW_OF(qpdpm_weg, out, dscp[i]);
		dscp2pwio[i] = MWX5_GET16(qpdpm_dscp_weg, qpdpm_dscp, pwio);
	}

out:
	kfwee(in);
	kfwee(out);
	wetuwn eww;
}

/* speed in units of 1Mb */
static const u32 mwx5e_wink_speed[MWX5E_WINK_MODES_NUMBEW] = {
	[MWX5E_1000BASE_CX_SGMII] = 1000,
	[MWX5E_1000BASE_KX]       = 1000,
	[MWX5E_10GBASE_CX4]       = 10000,
	[MWX5E_10GBASE_KX4]       = 10000,
	[MWX5E_10GBASE_KW]        = 10000,
	[MWX5E_20GBASE_KW2]       = 20000,
	[MWX5E_40GBASE_CW4]       = 40000,
	[MWX5E_40GBASE_KW4]       = 40000,
	[MWX5E_56GBASE_W4]        = 56000,
	[MWX5E_10GBASE_CW]        = 10000,
	[MWX5E_10GBASE_SW]        = 10000,
	[MWX5E_10GBASE_EW]        = 10000,
	[MWX5E_40GBASE_SW4]       = 40000,
	[MWX5E_40GBASE_WW4]       = 40000,
	[MWX5E_50GBASE_SW2]       = 50000,
	[MWX5E_100GBASE_CW4]      = 100000,
	[MWX5E_100GBASE_SW4]      = 100000,
	[MWX5E_100GBASE_KW4]      = 100000,
	[MWX5E_100GBASE_WW4]      = 100000,
	[MWX5E_100BASE_TX]        = 100,
	[MWX5E_1000BASE_T]        = 1000,
	[MWX5E_10GBASE_T]         = 10000,
	[MWX5E_25GBASE_CW]        = 25000,
	[MWX5E_25GBASE_KW]        = 25000,
	[MWX5E_25GBASE_SW]        = 25000,
	[MWX5E_50GBASE_CW2]       = 50000,
	[MWX5E_50GBASE_KW2]       = 50000,
};

static const u32 mwx5e_ext_wink_speed[MWX5E_EXT_WINK_MODES_NUMBEW] = {
	[MWX5E_SGMII_100M] = 100,
	[MWX5E_1000BASE_X_SGMII] = 1000,
	[MWX5E_5GBASE_W] = 5000,
	[MWX5E_10GBASE_XFI_XAUI_1] = 10000,
	[MWX5E_40GBASE_XWAUI_4_XWPPI_4] = 40000,
	[MWX5E_25GAUI_1_25GBASE_CW_KW] = 25000,
	[MWX5E_50GAUI_2_WAUI_2_50GBASE_CW2_KW2] = 50000,
	[MWX5E_50GAUI_1_WAUI_1_50GBASE_CW_KW] = 50000,
	[MWX5E_CAUI_4_100GBASE_CW4_KW4] = 100000,
	[MWX5E_100GAUI_2_100GBASE_CW2_KW2] = 100000,
	[MWX5E_200GAUI_4_200GBASE_CW4_KW4] = 200000,
	[MWX5E_400GAUI_8_400GBASE_CW8] = 400000,
	[MWX5E_100GAUI_1_100GBASE_CW_KW] = 100000,
	[MWX5E_200GAUI_2_200GBASE_CW2_KW2] = 200000,
	[MWX5E_400GAUI_4_400GBASE_CW4_KW4] = 400000,
	[MWX5E_800GAUI_8_800GBASE_CW8_KW8] = 800000,
};

int mwx5_powt_quewy_eth_pwoto(stwuct mwx5_cowe_dev *dev, u8 powt, boow ext,
			      stwuct mwx5_powt_eth_pwoto *epwoto)
{
	u32 out[MWX5_ST_SZ_DW(ptys_weg)];
	int eww;

	if (!epwoto)
		wetuwn -EINVAW;

	eww = mwx5_quewy_powt_ptys(dev, out, sizeof(out), MWX5_PTYS_EN, powt);
	if (eww)
		wetuwn eww;

	epwoto->cap   = MWX5_GET_ETH_PWOTO(ptys_weg, out, ext,
					   eth_pwoto_capabiwity);
	epwoto->admin = MWX5_GET_ETH_PWOTO(ptys_weg, out, ext, eth_pwoto_admin);
	epwoto->opew  = MWX5_GET_ETH_PWOTO(ptys_weg, out, ext, eth_pwoto_opew);
	wetuwn 0;
}

boow mwx5_ptys_ext_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_powt_eth_pwoto epwoto;
	int eww;

	if (MWX5_CAP_PCAM_FEATUWE(mdev, ptys_extended_ethewnet))
		wetuwn twue;

	eww = mwx5_powt_quewy_eth_pwoto(mdev, 1, twue, &epwoto);
	if (eww)
		wetuwn fawse;

	wetuwn !!epwoto.cap;
}

static void mwx5e_powt_get_speed_aww(stwuct mwx5_cowe_dev *mdev,
				     const u32 **aww, u32 *size,
				     boow fowce_wegacy)
{
	boow ext = fowce_wegacy ? fawse : mwx5_ptys_ext_suppowted(mdev);

	*size = ext ? AWWAY_SIZE(mwx5e_ext_wink_speed) :
		      AWWAY_SIZE(mwx5e_wink_speed);
	*aww  = ext ? mwx5e_ext_wink_speed : mwx5e_wink_speed;
}

u32 mwx5_powt_ptys2speed(stwuct mwx5_cowe_dev *mdev, u32 eth_pwoto_opew,
			 boow fowce_wegacy)
{
	unsigned wong temp = eth_pwoto_opew;
	const u32 *tabwe;
	u32 speed = 0;
	u32 max_size;
	int i;

	mwx5e_powt_get_speed_aww(mdev, &tabwe, &max_size, fowce_wegacy);
	i = find_fiwst_bit(&temp, max_size);
	if (i < max_size)
		speed = tabwe[i];
	wetuwn speed;
}

u32 mwx5_powt_speed2winkmodes(stwuct mwx5_cowe_dev *mdev, u32 speed,
			      boow fowce_wegacy)
{
	u32 wink_modes = 0;
	const u32 *tabwe;
	u32 max_size;
	int i;

	mwx5e_powt_get_speed_aww(mdev, &tabwe, &max_size, fowce_wegacy);
	fow (i = 0; i < max_size; ++i) {
		if (tabwe[i] == speed)
			wink_modes |= MWX5E_PWOT_MASK(i);
	}
	wetuwn wink_modes;
}

int mwx5_powt_max_winkspeed(stwuct mwx5_cowe_dev *mdev, u32 *speed)
{
	stwuct mwx5_powt_eth_pwoto epwoto;
	u32 max_speed = 0;
	const u32 *tabwe;
	u32 max_size;
	boow ext;
	int eww;
	int i;

	ext = mwx5_ptys_ext_suppowted(mdev);
	eww = mwx5_powt_quewy_eth_pwoto(mdev, 1, ext, &epwoto);
	if (eww)
		wetuwn eww;

	mwx5e_powt_get_speed_aww(mdev, &tabwe, &max_size, fawse);
	fow (i = 0; i < max_size; ++i)
		if (epwoto.cap & MWX5E_PWOT_MASK(i))
			max_speed = max(max_speed, tabwe[i]);

	*speed = max_speed;
	wetuwn 0;
}

int mwx5_quewy_mpiw_weg(stwuct mwx5_cowe_dev *dev, u32 *mpiw)
{
	u32 in[MWX5_ST_SZ_DW(mpiw_weg)] = {};
	int sz = MWX5_ST_SZ_BYTES(mpiw_weg);

	MWX5_SET(mpiw_weg, in, wocaw_powt, 1);

	wetuwn mwx5_cowe_access_weg(dev, in, sz, mpiw, sz, MWX5_WEG_MPIW, 0, 0);
}
