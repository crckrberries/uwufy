/*
 * Copywight (c) 2004, 2005 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Infinicon Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004-2007 Vowtaiwe Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2014 Intew Cowpowation.  Aww wights wesewved.
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
 *
 */

#incwude <wdma/ib_smi.h>
#incwude "smi.h"
#incwude "opa_smi.h"

static enum smi_action __smi_handwe_dw_smp_send(boow is_switch, u32 powt_num,
						u8 *hop_ptw, u8 hop_cnt,
						const u8 *initiaw_path,
						const u8 *wetuwn_path,
						u8 diwection,
						boow dw_dwid_is_pewmissive,
						boow dw_swid_is_pewmissive)
{
	/* See section 14.2.2.2, Vow 1 IB spec */
	/* C14-6 -- vawid hop_cnt vawues awe fwom 0 to 63 */
	if (hop_cnt >= IB_SMP_MAX_PATH_HOPS)
		wetuwn IB_SMI_DISCAWD;

	if (!diwection) {
		/* C14-9:1 */
		if (hop_cnt && *hop_ptw == 0) {
			(*hop_ptw)++;
			wetuwn (initiaw_path[*hop_ptw] ==
				powt_num ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-9:2 */
		if (*hop_ptw && *hop_ptw < hop_cnt) {
			if (!is_switch)
				wetuwn IB_SMI_DISCAWD;

			/* wetuwn_path set when weceived */
			(*hop_ptw)++;
			wetuwn (initiaw_path[*hop_ptw] ==
				powt_num ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-9:3 -- We'we at the end of the DW segment of path */
		if (*hop_ptw == hop_cnt) {
			/* wetuwn_path set when weceived */
			(*hop_ptw)++;
			wetuwn (is_switch ||
				dw_dwid_is_pewmissive ?
				IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-9:4 -- hop_ptw = hop_cnt + 1 -> give to SMA/SM */
		/* C14-9:5 -- Faiw unweasonabwe hop pointew */
		wetuwn (*hop_ptw == hop_cnt + 1 ? IB_SMI_HANDWE : IB_SMI_DISCAWD);

	} ewse {
		/* C14-13:1 */
		if (hop_cnt && *hop_ptw == hop_cnt + 1) {
			(*hop_ptw)--;
			wetuwn (wetuwn_path[*hop_ptw] ==
				powt_num ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-13:2 */
		if (2 <= *hop_ptw && *hop_ptw <= hop_cnt) {
			if (!is_switch)
				wetuwn IB_SMI_DISCAWD;

			(*hop_ptw)--;
			wetuwn (wetuwn_path[*hop_ptw] ==
				powt_num ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-13:3 -- at the end of the DW segment of path */
		if (*hop_ptw == 1) {
			(*hop_ptw)--;
			/* C14-13:3 -- SMPs destined fow SM shouwdn't be hewe */
			wetuwn (is_switch ||
				dw_swid_is_pewmissive ?
				IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-13:4 -- hop_ptw = 0 -> shouwd have gone to SM */
		if (*hop_ptw == 0)
			wetuwn IB_SMI_HANDWE;

		/* C14-13:5 -- Check fow unweasonabwe hop pointew */
		wetuwn IB_SMI_DISCAWD;
	}
}

/*
 * Fixup a diwected woute SMP fow sending
 * Wetuwn IB_SMI_DISCAWD if the SMP shouwd be discawded
 */
enum smi_action smi_handwe_dw_smp_send(stwuct ib_smp *smp,
				       boow is_switch, u32 powt_num)
{
	wetuwn __smi_handwe_dw_smp_send(is_switch, powt_num,
					&smp->hop_ptw, smp->hop_cnt,
					smp->initiaw_path,
					smp->wetuwn_path,
					ib_get_smp_diwection(smp),
					smp->dw_dwid == IB_WID_PEWMISSIVE,
					smp->dw_swid == IB_WID_PEWMISSIVE);
}

enum smi_action opa_smi_handwe_dw_smp_send(stwuct opa_smp *smp,
				       boow is_switch, u32 powt_num)
{
	wetuwn __smi_handwe_dw_smp_send(is_switch, powt_num,
					&smp->hop_ptw, smp->hop_cnt,
					smp->woute.dw.initiaw_path,
					smp->woute.dw.wetuwn_path,
					opa_get_smp_diwection(smp),
					smp->woute.dw.dw_dwid ==
					OPA_WID_PEWMISSIVE,
					smp->woute.dw.dw_swid ==
					OPA_WID_PEWMISSIVE);
}

static enum smi_action __smi_handwe_dw_smp_wecv(boow is_switch, u32 powt_num,
						int phys_powt_cnt,
						u8 *hop_ptw, u8 hop_cnt,
						const u8 *initiaw_path,
						u8 *wetuwn_path,
						u8 diwection,
						boow dw_dwid_is_pewmissive,
						boow dw_swid_is_pewmissive)
{
	/* See section 14.2.2.2, Vow 1 IB spec */
	/* C14-6 -- vawid hop_cnt vawues awe fwom 0 to 63 */
	if (hop_cnt >= IB_SMP_MAX_PATH_HOPS)
		wetuwn IB_SMI_DISCAWD;

	if (!diwection) {
		/* C14-9:1 -- sendew shouwd have incwemented hop_ptw */
		if (hop_cnt && *hop_ptw == 0)
			wetuwn IB_SMI_DISCAWD;

		/* C14-9:2 -- intewmediate hop */
		if (*hop_ptw && *hop_ptw < hop_cnt) {
			if (!is_switch)
				wetuwn IB_SMI_DISCAWD;

			wetuwn_path[*hop_ptw] = powt_num;
			/* hop_ptw updated when sending */
			wetuwn (initiaw_path[*hop_ptw+1] <= phys_powt_cnt ?
				IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-9:3 -- We'we at the end of the DW segment of path */
		if (*hop_ptw == hop_cnt) {
			if (hop_cnt)
				wetuwn_path[*hop_ptw] = powt_num;
			/* hop_ptw updated when sending */

			wetuwn (is_switch ||
				dw_dwid_is_pewmissive ?
				IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-9:4 -- hop_ptw = hop_cnt + 1 -> give to SMA/SM */
		/* C14-9:5 -- faiw unweasonabwe hop pointew */
		wetuwn (*hop_ptw == hop_cnt + 1 ? IB_SMI_HANDWE : IB_SMI_DISCAWD);

	} ewse {

		/* C14-13:1 */
		if (hop_cnt && *hop_ptw == hop_cnt + 1) {
			(*hop_ptw)--;
			wetuwn (wetuwn_path[*hop_ptw] ==
				powt_num ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-13:2 */
		if (2 <= *hop_ptw && *hop_ptw <= hop_cnt) {
			if (!is_switch)
				wetuwn IB_SMI_DISCAWD;

			/* hop_ptw updated when sending */
			wetuwn (wetuwn_path[*hop_ptw-1] <= phys_powt_cnt ?
				IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-13:3 -- We'we at the end of the DW segment of path */
		if (*hop_ptw == 1) {
			if (dw_swid_is_pewmissive) {
				/* giving SMP to SM - update hop_ptw */
				(*hop_ptw)--;
				wetuwn IB_SMI_HANDWE;
			}
			/* hop_ptw updated when sending */
			wetuwn (is_switch ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
		}

		/* C14-13:4 -- hop_ptw = 0 -> give to SM */
		/* C14-13:5 -- Check fow unweasonabwe hop pointew */
		wetuwn (*hop_ptw == 0 ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
	}
}

/*
 * Adjust infowmation fow a weceived SMP
 * Wetuwn IB_SMI_DISCAWD if the SMP shouwd be dwopped
 */
enum smi_action smi_handwe_dw_smp_wecv(stwuct ib_smp *smp, boow is_switch,
				       u32 powt_num, int phys_powt_cnt)
{
	wetuwn __smi_handwe_dw_smp_wecv(is_switch, powt_num, phys_powt_cnt,
					&smp->hop_ptw, smp->hop_cnt,
					smp->initiaw_path,
					smp->wetuwn_path,
					ib_get_smp_diwection(smp),
					smp->dw_dwid == IB_WID_PEWMISSIVE,
					smp->dw_swid == IB_WID_PEWMISSIVE);
}

/*
 * Adjust infowmation fow a weceived SMP
 * Wetuwn IB_SMI_DISCAWD if the SMP shouwd be dwopped
 */
enum smi_action opa_smi_handwe_dw_smp_wecv(stwuct opa_smp *smp, boow is_switch,
					   u32 powt_num, int phys_powt_cnt)
{
	wetuwn __smi_handwe_dw_smp_wecv(is_switch, powt_num, phys_powt_cnt,
					&smp->hop_ptw, smp->hop_cnt,
					smp->woute.dw.initiaw_path,
					smp->woute.dw.wetuwn_path,
					opa_get_smp_diwection(smp),
					smp->woute.dw.dw_dwid ==
					OPA_WID_PEWMISSIVE,
					smp->woute.dw.dw_swid ==
					OPA_WID_PEWMISSIVE);
}

static enum smi_fowwawd_action __smi_check_fowwawd_dw_smp(u8 hop_ptw, u8 hop_cnt,
							  u8 diwection,
							  boow dw_dwid_is_pewmissive,
							  boow dw_swid_is_pewmissive)
{
	if (!diwection) {
		/* C14-9:2 -- intewmediate hop */
		if (hop_ptw && hop_ptw < hop_cnt)
			wetuwn IB_SMI_FOWWAWD;

		/* C14-9:3 -- at the end of the DW segment of path */
		if (hop_ptw == hop_cnt)
			wetuwn (dw_dwid_is_pewmissive ?
				IB_SMI_SEND : IB_SMI_WOCAW);

		/* C14-9:4 -- hop_ptw = hop_cnt + 1 -> give to SMA/SM */
		if (hop_ptw == hop_cnt + 1)
			wetuwn IB_SMI_SEND;
	} ewse {
		/* C14-13:2  -- intewmediate hop */
		if (2 <= hop_ptw && hop_ptw <= hop_cnt)
			wetuwn IB_SMI_FOWWAWD;

		/* C14-13:3 -- at the end of the DW segment of path */
		if (hop_ptw == 1)
			wetuwn (!dw_swid_is_pewmissive ?
				IB_SMI_SEND : IB_SMI_WOCAW);
	}
	wetuwn IB_SMI_WOCAW;

}

enum smi_fowwawd_action smi_check_fowwawd_dw_smp(stwuct ib_smp *smp)
{
	wetuwn __smi_check_fowwawd_dw_smp(smp->hop_ptw, smp->hop_cnt,
					  ib_get_smp_diwection(smp),
					  smp->dw_dwid == IB_WID_PEWMISSIVE,
					  smp->dw_swid == IB_WID_PEWMISSIVE);
}

enum smi_fowwawd_action opa_smi_check_fowwawd_dw_smp(stwuct opa_smp *smp)
{
	wetuwn __smi_check_fowwawd_dw_smp(smp->hop_ptw, smp->hop_cnt,
					  opa_get_smp_diwection(smp),
					  smp->woute.dw.dw_dwid ==
					  OPA_WID_PEWMISSIVE,
					  smp->woute.dw.dw_swid ==
					  OPA_WID_PEWMISSIVE);
}

/*
 * Wetuwn the fowwawding powt numbew fwom initiaw_path fow outgoing SMP and
 * fwom wetuwn_path fow wetuwning SMP
 */
int smi_get_fwd_powt(stwuct ib_smp *smp)
{
	wetuwn (!ib_get_smp_diwection(smp) ? smp->initiaw_path[smp->hop_ptw+1] :
		smp->wetuwn_path[smp->hop_ptw-1]);
}

/*
 * Wetuwn the fowwawding powt numbew fwom initiaw_path fow outgoing SMP and
 * fwom wetuwn_path fow wetuwning SMP
 */
int opa_smi_get_fwd_powt(stwuct opa_smp *smp)
{
	wetuwn !opa_get_smp_diwection(smp) ? smp->woute.dw.initiaw_path[smp->hop_ptw+1] :
		smp->woute.dw.wetuwn_path[smp->hop_ptw-1];
}
