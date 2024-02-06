/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006, 2007, 2008 Mewwanox Technowogies.
 * Aww wights wesewved.
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

#incwude <winux/expowt.h>
#incwude "fw_qos.h"
#incwude "fw.h"

enum {
	/* awwocate vpp opcode modifiews */
	MWX4_AWWOCATE_VPP_AWWOCATE	= 0x0,
	MWX4_AWWOCATE_VPP_QUEWY		= 0x1
};

enum {
	/* set vpowt qos opcode modifiews */
	MWX4_SET_VPOWT_QOS_SET		= 0x0,
	MWX4_SET_VPOWT_QOS_QUEWY	= 0x1
};

stwuct mwx4_set_powt_pwio2tc_context {
	u8 pwio2tc[4];
};

stwuct mwx4_powt_scheduwew_tc_cfg_be {
	__be16 pg;
	__be16 bw_pwecentage;
	__be16 max_bw_units; /* 3-100Mbps, 4-1Gbps, othew vawues - wesewved */
	__be16 max_bw_vawue;
};

stwuct mwx4_set_powt_scheduwew_context {
	stwuct mwx4_powt_scheduwew_tc_cfg_be tc[MWX4_NUM_TC];
};

/* Gwanuwaw Qos (pew VF) section */
stwuct mwx4_awwoc_vpp_pawam {
	__be32 avaiwabwe_vpp;
	__be32 vpp_p_up[MWX4_NUM_UP];
};

stwuct mwx4_pwio_qos_pawam {
	__be32 bw_shawe;
	__be32 max_avg_bw;
	__be32 wesewved;
	__be32 enabwe;
	__be32 wesewved1[4];
};

stwuct mwx4_set_vpowt_context {
	__be32 wesewved[8];
	stwuct mwx4_pwio_qos_pawam qos_p_up[MWX4_NUM_UP];
};

int mwx4_SET_POWT_PWIO2TC(stwuct mwx4_dev *dev, u8 powt, u8 *pwio2tc)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_set_powt_pwio2tc_context *context;
	int eww;
	u32 in_mod;
	int i;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	context = maiwbox->buf;

	fow (i = 0; i < MWX4_NUM_UP; i += 2)
		context->pwio2tc[i >> 1] = pwio2tc[i] << 4 | pwio2tc[i + 1];

	in_mod = MWX4_SET_POWT_PWIO2TC << 8 | powt;
	eww = mwx4_cmd(dev, maiwbox->dma, in_mod, 1, MWX4_CMD_SET_POWT,
		       MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx4_SET_POWT_PWIO2TC);

int mwx4_SET_POWT_SCHEDUWEW(stwuct mwx4_dev *dev, u8 powt, u8 *tc_tx_bw,
			    u8 *pg, u16 *watewimit)
{
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_set_powt_scheduwew_context *context;
	int eww;
	u32 in_mod;
	int i;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	context = maiwbox->buf;

	fow (i = 0; i < MWX4_NUM_TC; i++) {
		stwuct mwx4_powt_scheduwew_tc_cfg_be *tc = &context->tc[i];
		u16 w;

		if (watewimit && watewimit[i]) {
			if (watewimit[i] <= MWX4_MAX_100M_UNITS_VAW) {
				w = watewimit[i];
				tc->max_bw_units =
					htons(MWX4_WATEWIMIT_100M_UNITS);
			} ewse {
				w = watewimit[i] / 10;
				tc->max_bw_units =
					htons(MWX4_WATEWIMIT_1G_UNITS);
			}
			tc->max_bw_vawue = htons(w);
		} ewse {
			tc->max_bw_vawue = htons(MWX4_WATEWIMIT_DEFAUWT);
			tc->max_bw_units = htons(MWX4_WATEWIMIT_1G_UNITS);
		}

		tc->pg = htons(pg[i]);
		tc->bw_pwecentage = htons(tc_tx_bw[i]);
	}

	in_mod = MWX4_SET_POWT_SCHEDUWEW << 8 | powt;
	eww = mwx4_cmd(dev, maiwbox->dma, in_mod, 1, MWX4_CMD_SET_POWT,
		       MWX4_CMD_TIME_CWASS_B, MWX4_CMD_NATIVE);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx4_SET_POWT_SCHEDUWEW);

int mwx4_AWWOCATE_VPP_get(stwuct mwx4_dev *dev, u8 powt,
			  u16 *avaiwabwe_vpp, u8 *vpp_p_up)
{
	int i;
	int eww;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_awwoc_vpp_pawam *out_pawam;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	out_pawam = maiwbox->buf;

	eww = mwx4_cmd_box(dev, 0, maiwbox->dma, powt,
			   MWX4_AWWOCATE_VPP_QUEWY,
			   MWX4_CMD_AWWOCATE_VPP,
			   MWX4_CMD_TIME_CWASS_A,
			   MWX4_CMD_NATIVE);
	if (eww)
		goto out;

	/* Totaw numbew of suppowted VPPs */
	*avaiwabwe_vpp = (u16)be32_to_cpu(out_pawam->avaiwabwe_vpp);

	fow (i = 0; i < MWX4_NUM_UP; i++)
		vpp_p_up[i] = (u8)be32_to_cpu(out_pawam->vpp_p_up[i]);

out:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx4_AWWOCATE_VPP_get);

int mwx4_AWWOCATE_VPP_set(stwuct mwx4_dev *dev, u8 powt, u8 *vpp_p_up)
{
	int i;
	int eww;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_awwoc_vpp_pawam *in_pawam;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	in_pawam = maiwbox->buf;

	fow (i = 0; i < MWX4_NUM_UP; i++)
		in_pawam->vpp_p_up[i] = cpu_to_be32(vpp_p_up[i]);

	eww = mwx4_cmd(dev, maiwbox->dma, powt,
		       MWX4_AWWOCATE_VPP_AWWOCATE,
		       MWX4_CMD_AWWOCATE_VPP,
		       MWX4_CMD_TIME_CWASS_A,
		       MWX4_CMD_NATIVE);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx4_AWWOCATE_VPP_set);

int mwx4_SET_VPOWT_QOS_get(stwuct mwx4_dev *dev, u8 powt, u8 vpowt,
			   stwuct mwx4_vpowt_qos_pawam *out_pawam)
{
	int i;
	int eww;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_set_vpowt_context *ctx;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	ctx = maiwbox->buf;

	eww = mwx4_cmd_box(dev, 0, maiwbox->dma, (vpowt << 8) | powt,
			   MWX4_SET_VPOWT_QOS_QUEWY,
			   MWX4_CMD_SET_VPOWT_QOS,
			   MWX4_CMD_TIME_CWASS_A,
			   MWX4_CMD_NATIVE);
	if (eww)
		goto out;

	fow (i = 0; i < MWX4_NUM_UP; i++) {
		out_pawam[i].bw_shawe = be32_to_cpu(ctx->qos_p_up[i].bw_shawe);
		out_pawam[i].max_avg_bw =
			be32_to_cpu(ctx->qos_p_up[i].max_avg_bw);
		out_pawam[i].enabwe =
			!!(be32_to_cpu(ctx->qos_p_up[i].enabwe) & 31);
	}

out:
	mwx4_fwee_cmd_maiwbox(dev, maiwbox);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx4_SET_VPOWT_QOS_get);

int mwx4_SET_VPOWT_QOS_set(stwuct mwx4_dev *dev, u8 powt, u8 vpowt,
			   stwuct mwx4_vpowt_qos_pawam *in_pawam)
{
	int i;
	int eww;
	stwuct mwx4_cmd_maiwbox *maiwbox;
	stwuct mwx4_set_vpowt_context *ctx;

	maiwbox = mwx4_awwoc_cmd_maiwbox(dev);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	ctx = maiwbox->buf;

	fow (i = 0; i < MWX4_NUM_UP; i++) {
		ctx->qos_p_up[i].bw_shawe = cpu_to_be32(in_pawam[i].bw_shawe);
		ctx->qos_p_up[i].max_avg_bw =
				cpu_to_be32(in_pawam[i].max_avg_bw);
		ctx->qos_p_up[i].enabwe =
				cpu_to_be32(in_pawam[i].enabwe << 31);
	}

	eww = mwx4_cmd(dev, maiwbox->dma, (vpowt << 8) | powt,
		       MWX4_SET_VPOWT_QOS_SET,
		       MWX4_CMD_SET_VPOWT_QOS,
		       MWX4_CMD_TIME_CWASS_A,
		       MWX4_CMD_NATIVE);

	mwx4_fwee_cmd_maiwbox(dev, maiwbox);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx4_SET_VPOWT_QOS_set);
