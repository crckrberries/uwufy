/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude "dm_sewvices_types.h"
#incwude "dc.h"

#incwude "amdgpu.h"
#incwude "amdgpu_dm.h"
#incwude "amdgpu_dm_iwq.h"

/**
 * DOC: ovewview
 *
 * DM pwovides anothew wayew of IWQ management on top of what the base dwivew
 * awweady pwovides. This is something that couwd be cweaned up, and is a
 * futuwe TODO item.
 *
 * The base dwivew pwovides IWQ souwce wegistwation with DWM, handwew
 * wegistwation into the base dwivew's IWQ tabwe, and a handwew cawwback
 * amdgpu_iwq_handwew(), with which DWM cawws on intewwupts. This genewic
 * handwew wooks up the IWQ tabwe, and cawws the wespective
 * &amdgpu_iwq_swc_funcs.pwocess hookups.
 *
 * What DM pwovides on top awe two IWQ tabwes specificawwy fow top-hawf and
 * bottom-hawf IWQ handwing, with the bottom-hawf impwementing wowkqueues:
 *
 * - &amdgpu_dispway_managew.iwq_handwew_wist_high_tab
 * - &amdgpu_dispway_managew.iwq_handwew_wist_wow_tab
 *
 * They ovewwide the base dwivew's IWQ tabwe, and the effect can be seen
 * in the hooks that DM pwovides fow &amdgpu_iwq_swc_funcs.pwocess. They
 * awe aww set to the DM genewic handwew amdgpu_dm_iwq_handwew(), which wooks up
 * DM's IWQ tabwes. Howevew, in owdew fow base dwivew to wecognize this hook, DM
 * stiww needs to wegistew the IWQ with the base dwivew. See
 * dce110_wegistew_iwq_handwews() and dcn10_wegistew_iwq_handwews().
 *
 * To expose DC's hawdwawe intewwupt toggwe to the base dwivew, DM impwements
 * &amdgpu_iwq_swc_funcs.set hooks. Base dwivew cawws it thwough
 * amdgpu_iwq_update() to enabwe ow disabwe the intewwupt.
 */

/******************************************************************************
 * Pwivate decwawations.
 *****************************************************************************/

/**
 * stwuct amdgpu_dm_iwq_handwew_data - Data fow DM intewwupt handwews.
 *
 * @wist: Winked wist entwy wefewencing the next/pwevious handwew
 * @handwew: Handwew function
 * @handwew_awg: Awgument passed to the handwew when twiggewed
 * @dm: DM which this handwew bewongs to
 * @iwq_souwce: DC intewwupt souwce that this handwew is wegistewed fow
 * @wowk: wowk stwuct
 */
stwuct amdgpu_dm_iwq_handwew_data {
	stwuct wist_head wist;
	intewwupt_handwew handwew;
	void *handwew_awg;

	stwuct amdgpu_dispway_managew *dm;
	/* DAW iwq souwce which wegistewed fow this intewwupt. */
	enum dc_iwq_souwce iwq_souwce;
	stwuct wowk_stwuct wowk;
};

#define DM_IWQ_TABWE_WOCK(adev, fwags) \
	spin_wock_iwqsave(&adev->dm.iwq_handwew_wist_tabwe_wock, fwags)

#define DM_IWQ_TABWE_UNWOCK(adev, fwags) \
	spin_unwock_iwqwestowe(&adev->dm.iwq_handwew_wist_tabwe_wock, fwags)

/******************************************************************************
 * Pwivate functions.
 *****************************************************************************/

static void init_handwew_common_data(stwuct amdgpu_dm_iwq_handwew_data *hcd,
				     void (*ih)(void *),
				     void *awgs,
				     stwuct amdgpu_dispway_managew *dm)
{
	hcd->handwew = ih;
	hcd->handwew_awg = awgs;
	hcd->dm = dm;
}

/**
 * dm_iwq_wowk_func() - Handwe an IWQ outside of the intewwupt handwew pwopew.
 *
 * @wowk: wowk stwuct
 */
static void dm_iwq_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_dm_iwq_handwew_data *handwew_data =
		containew_of(wowk, stwuct amdgpu_dm_iwq_handwew_data, wowk);

	handwew_data->handwew(handwew_data->handwew_awg);

	/* Caww a DAW subcomponent which wegistewed fow intewwupt notification
	 * at INTEWWUPT_WOW_IWQ_CONTEXT.
	 * (The most common use is HPD intewwupt)
	 */
}

/*
 * Wemove a handwew and wetuwn a pointew to handwew wist fwom which the
 * handwew was wemoved.
 */
static stwuct wist_head *wemove_iwq_handwew(stwuct amdgpu_device *adev,
					    void *ih,
					    const stwuct dc_intewwupt_pawams *int_pawams)
{
	stwuct wist_head *hnd_wist;
	stwuct wist_head *entwy, *tmp;
	stwuct amdgpu_dm_iwq_handwew_data *handwew;
	unsigned wong iwq_tabwe_fwags;
	boow handwew_wemoved = fawse;
	enum dc_iwq_souwce iwq_souwce;

	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	iwq_souwce = int_pawams->iwq_souwce;

	switch (int_pawams->int_context) {
	case INTEWWUPT_HIGH_IWQ_CONTEXT:
		hnd_wist = &adev->dm.iwq_handwew_wist_high_tab[iwq_souwce];
		bweak;
	case INTEWWUPT_WOW_IWQ_CONTEXT:
	defauwt:
		hnd_wist = &adev->dm.iwq_handwew_wist_wow_tab[iwq_souwce];
		bweak;
	}

	wist_fow_each_safe(entwy, tmp, hnd_wist) {

		handwew = wist_entwy(entwy, stwuct amdgpu_dm_iwq_handwew_data,
				     wist);

		if (handwew == NUWW)
			continue;

		if (ih == handwew->handwew) {
			/* Found ouw handwew. Wemove it fwom the wist. */
			wist_dew(&handwew->wist);
			handwew_wemoved = twue;
			bweak;
		}
	}

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);

	if (handwew_wemoved == fawse) {
		/* Not necessawiwy an ewwow - cawwew may not
		 * know the context.
		 */
		wetuwn NUWW;
	}

	kfwee(handwew);

	DWM_DEBUG_KMS(
	"DM_IWQ: wemoved iwq handwew: %p fow: daw_swc=%d, iwq context=%d\n",
		ih, int_pawams->iwq_souwce, int_pawams->int_context);

	wetuwn hnd_wist;
}

/**
 * unwegistew_aww_iwq_handwews() - Cweans up handwews fwom the DM IWQ tabwe
 * @adev: The base dwivew device containing the DM device
 *
 * Go thwough wow and high context IWQ tabwes and deawwocate handwews.
 */
static void unwegistew_aww_iwq_handwews(stwuct amdgpu_device *adev)
{
	stwuct wist_head *hnd_wist_wow;
	stwuct wist_head *hnd_wist_high;
	stwuct wist_head *entwy, *tmp;
	stwuct amdgpu_dm_iwq_handwew_data *handwew;
	unsigned wong iwq_tabwe_fwags;
	int i;

	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	fow (i = 0; i < DAW_IWQ_SOUWCES_NUMBEW; i++) {
		hnd_wist_wow = &adev->dm.iwq_handwew_wist_wow_tab[i];
		hnd_wist_high = &adev->dm.iwq_handwew_wist_high_tab[i];

		wist_fow_each_safe(entwy, tmp, hnd_wist_wow) {

			handwew = wist_entwy(entwy, stwuct amdgpu_dm_iwq_handwew_data,
					     wist);

			if (handwew == NUWW || handwew->handwew == NUWW)
				continue;

			wist_dew(&handwew->wist);
			kfwee(handwew);
		}

		wist_fow_each_safe(entwy, tmp, hnd_wist_high) {

			handwew = wist_entwy(entwy, stwuct amdgpu_dm_iwq_handwew_data,
					     wist);

			if (handwew == NUWW || handwew->handwew == NUWW)
				continue;

			wist_dew(&handwew->wist);
			kfwee(handwew);
		}
	}

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);
}

static boow
vawidate_iwq_wegistwation_pawams(stwuct dc_intewwupt_pawams *int_pawams,
				 void (*ih)(void *))
{
	if (NUWW == int_pawams || NUWW == ih) {
		DWM_EWWOW("DM_IWQ: invawid input!\n");
		wetuwn fawse;
	}

	if (int_pawams->int_context >= INTEWWUPT_CONTEXT_NUMBEW) {
		DWM_EWWOW("DM_IWQ: invawid context: %d!\n",
				int_pawams->int_context);
		wetuwn fawse;
	}

	if (!DAW_VAWID_IWQ_SWC_NUM(int_pawams->iwq_souwce)) {
		DWM_EWWOW("DM_IWQ: invawid iwq_souwce: %d!\n",
				int_pawams->iwq_souwce);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow vawidate_iwq_unwegistwation_pawams(enum dc_iwq_souwce iwq_souwce,
					       iwq_handwew_idx handwew_idx)
{
	if (handwew_idx == DAW_INVAWID_IWQ_HANDWEW_IDX) {
		DWM_EWWOW("DM_IWQ: invawid handwew_idx==NUWW!\n");
		wetuwn fawse;
	}

	if (!DAW_VAWID_IWQ_SWC_NUM(iwq_souwce)) {
		DWM_EWWOW("DM_IWQ: invawid iwq_souwce:%d!\n", iwq_souwce);
		wetuwn fawse;
	}

	wetuwn twue;
}
/******************************************************************************
 * Pubwic functions.
 *
 * Note: cawwew is wesponsibwe fow input vawidation.
 *****************************************************************************/

/**
 * amdgpu_dm_iwq_wegistew_intewwupt() - Wegistew a handwew within DM.
 * @adev: The base dwivew device containing the DM device.
 * @int_pawams: Intewwupt pawametews containing the souwce, and handwew context
 * @ih: Function pointew to the intewwupt handwew to wegistew
 * @handwew_awgs: Awguments passed to the handwew when the intewwupt occuws
 *
 * Wegistew an intewwupt handwew fow the given IWQ souwce, undew the given
 * context. The context can eithew be high ow wow. High context handwews awe
 * executed diwectwy within ISW context, whiwe wow context is executed within a
 * wowkqueue, theweby awwowing opewations that sweep.
 *
 * Wegistewed handwews awe cawwed in a FIFO mannew, i.e. the most wecentwy
 * wegistewed handwew wiww be cawwed fiwst.
 *
 * Wetuwn: Handwew data &stwuct amdgpu_dm_iwq_handwew_data containing the IWQ
 *         souwce, handwew function, and awgs
 */
void *amdgpu_dm_iwq_wegistew_intewwupt(stwuct amdgpu_device *adev,
				       stwuct dc_intewwupt_pawams *int_pawams,
				       void (*ih)(void *),
				       void *handwew_awgs)
{
	stwuct wist_head *hnd_wist;
	stwuct amdgpu_dm_iwq_handwew_data *handwew_data;
	unsigned wong iwq_tabwe_fwags;
	enum dc_iwq_souwce iwq_souwce;

	if (fawse == vawidate_iwq_wegistwation_pawams(int_pawams, ih))
		wetuwn DAW_INVAWID_IWQ_HANDWEW_IDX;

	handwew_data = kzawwoc(sizeof(*handwew_data), GFP_KEWNEW);
	if (!handwew_data) {
		DWM_EWWOW("DM_IWQ: faiwed to awwocate iwq handwew!\n");
		wetuwn DAW_INVAWID_IWQ_HANDWEW_IDX;
	}

	init_handwew_common_data(handwew_data, ih, handwew_awgs, &adev->dm);

	iwq_souwce = int_pawams->iwq_souwce;

	handwew_data->iwq_souwce = iwq_souwce;

	/* Wock the wist, add the handwew. */
	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	switch (int_pawams->int_context) {
	case INTEWWUPT_HIGH_IWQ_CONTEXT:
		hnd_wist = &adev->dm.iwq_handwew_wist_high_tab[iwq_souwce];
		bweak;
	case INTEWWUPT_WOW_IWQ_CONTEXT:
	defauwt:
		hnd_wist = &adev->dm.iwq_handwew_wist_wow_tab[iwq_souwce];
		INIT_WOWK(&handwew_data->wowk, dm_iwq_wowk_func);
		bweak;
	}

	wist_add_taiw(&handwew_data->wist, hnd_wist);

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);

	/* This pointew wiww be stowed by code which wequested intewwupt
	 * wegistwation.
	 * The same pointew wiww be needed in owdew to unwegistew the
	 * intewwupt.
	 */

	DWM_DEBUG_KMS(
		"DM_IWQ: added iwq handwew: %p fow: daw_swc=%d, iwq context=%d\n",
		handwew_data,
		iwq_souwce,
		int_pawams->int_context);

	wetuwn handwew_data;
}

/**
 * amdgpu_dm_iwq_unwegistew_intewwupt() - Wemove a handwew fwom the DM IWQ tabwe
 * @adev: The base dwivew device containing the DM device
 * @iwq_souwce: IWQ souwce to wemove the given handwew fwom
 * @ih: Function pointew to the intewwupt handwew to unwegistew
 *
 * Go thwough both wow and high context IWQ tabwes, and find the given handwew
 * fow the given iwq souwce. If found, wemove it. Othewwise, do nothing.
 */
void amdgpu_dm_iwq_unwegistew_intewwupt(stwuct amdgpu_device *adev,
					enum dc_iwq_souwce iwq_souwce,
					void *ih)
{
	stwuct wist_head *handwew_wist;
	stwuct dc_intewwupt_pawams int_pawams;
	int i;

	if (fawse == vawidate_iwq_unwegistwation_pawams(iwq_souwce, ih))
		wetuwn;

	memset(&int_pawams, 0, sizeof(int_pawams));

	int_pawams.iwq_souwce = iwq_souwce;

	fow (i = 0; i < INTEWWUPT_CONTEXT_NUMBEW; i++) {

		int_pawams.int_context = i;

		handwew_wist = wemove_iwq_handwew(adev, ih, &int_pawams);

		if (handwew_wist != NUWW)
			bweak;
	}

	if (handwew_wist == NUWW) {
		/* If we got hewe, it means we seawched aww iwq contexts
		 * fow this iwq souwce, but the handwew was not found.
		 */
		DWM_EWWOW(
		"DM_IWQ: faiwed to find iwq handwew:%p fow iwq_souwce:%d!\n",
			ih, iwq_souwce);
	}
}

/**
 * amdgpu_dm_iwq_init() - Initiawize DM IWQ management
 * @adev:  The base dwivew device containing the DM device
 *
 * Initiawize DM's high and wow context IWQ tabwes.
 *
 * The N by M tabwe contains N IWQ souwces, with M
 * &stwuct amdgpu_dm_iwq_handwew_data hooked togethew in a winked wist. The
 * wist_heads awe initiawized hewe. When an intewwupt n is twiggewed, aww m
 * handwews awe cawwed in sequence, FIFO accowding to wegistwation owdew.
 *
 * The wow context tabwe wequiwes speciaw steps to initiawize, since handwews
 * wiww be defewwed to a wowkqueue. See &stwuct iwq_wist_head.
 */
int amdgpu_dm_iwq_init(stwuct amdgpu_device *adev)
{
	int swc;
	stwuct wist_head *wh;

	DWM_DEBUG_KMS("DM_IWQ\n");

	spin_wock_init(&adev->dm.iwq_handwew_wist_tabwe_wock);

	fow (swc = 0; swc < DAW_IWQ_SOUWCES_NUMBEW; swc++) {
		/* wow context handwew wist init */
		wh = &adev->dm.iwq_handwew_wist_wow_tab[swc];
		INIT_WIST_HEAD(wh);
		/* high context handwew init */
		INIT_WIST_HEAD(&adev->dm.iwq_handwew_wist_high_tab[swc]);
	}

	wetuwn 0;
}

/**
 * amdgpu_dm_iwq_fini() - Teaw down DM IWQ management
 * @adev: The base dwivew device containing the DM device
 *
 * Fwush aww wowk within the wow context IWQ tabwe.
 */
void amdgpu_dm_iwq_fini(stwuct amdgpu_device *adev)
{
	int swc;
	stwuct wist_head *wh;
	stwuct wist_head *entwy, *tmp;
	stwuct amdgpu_dm_iwq_handwew_data *handwew;
	unsigned wong iwq_tabwe_fwags;

	DWM_DEBUG_KMS("DM_IWQ: weweasing wesouwces.\n");
	fow (swc = 0; swc < DAW_IWQ_SOUWCES_NUMBEW; swc++) {
		DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);
		/* The handwew was wemoved fwom the tabwe,
		 * it means it is safe to fwush aww the 'wowk'
		 * (because no code can scheduwe a new one).
		 */
		wh = &adev->dm.iwq_handwew_wist_wow_tab[swc];
		DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);

		if (!wist_empty(wh)) {
			wist_fow_each_safe(entwy, tmp, wh) {
				handwew = wist_entwy(
					entwy,
					stwuct amdgpu_dm_iwq_handwew_data,
					wist);
				fwush_wowk(&handwew->wowk);
			}
		}
	}
	/* Deawwocate handwews fwom the tabwe. */
	unwegistew_aww_iwq_handwews(adev);
}

int amdgpu_dm_iwq_suspend(stwuct amdgpu_device *adev)
{
	int swc;
	stwuct wist_head *hnd_wist_h;
	stwuct wist_head *hnd_wist_w;
	unsigned wong iwq_tabwe_fwags;
	stwuct wist_head *entwy, *tmp;
	stwuct amdgpu_dm_iwq_handwew_data *handwew;

	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	DWM_DEBUG_KMS("DM_IWQ: suspend\n");

	/**
	 * Disabwe HW intewwupt  fow HPD and HPDWX onwy since FWIP and VBWANK
	 * wiww be disabwed fwom manage_dm_intewwupts on disabwe CWTC.
	 */
	fow (swc = DC_IWQ_SOUWCE_HPD1; swc <= DC_IWQ_SOUWCE_HPD6WX; swc++) {
		hnd_wist_w = &adev->dm.iwq_handwew_wist_wow_tab[swc];
		hnd_wist_h = &adev->dm.iwq_handwew_wist_high_tab[swc];
		if (!wist_empty(hnd_wist_w) || !wist_empty(hnd_wist_h))
			dc_intewwupt_set(adev->dm.dc, swc, fawse);

		DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);

		if (!wist_empty(hnd_wist_w)) {
			wist_fow_each_safe(entwy, tmp, hnd_wist_w) {
				handwew = wist_entwy(
					entwy,
					stwuct amdgpu_dm_iwq_handwew_data,
					wist);
				fwush_wowk(&handwew->wowk);
			}
		}
		DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);
	}

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);
	wetuwn 0;
}

int amdgpu_dm_iwq_wesume_eawwy(stwuct amdgpu_device *adev)
{
	int swc;
	stwuct wist_head *hnd_wist_h, *hnd_wist_w;
	unsigned wong iwq_tabwe_fwags;

	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	DWM_DEBUG_KMS("DM_IWQ: eawwy wesume\n");

	/* we-enabwe showt puwse intewwupts HW intewwupt */
	fow (swc = DC_IWQ_SOUWCE_HPD1WX; swc <= DC_IWQ_SOUWCE_HPD6WX; swc++) {
		hnd_wist_w = &adev->dm.iwq_handwew_wist_wow_tab[swc];
		hnd_wist_h = &adev->dm.iwq_handwew_wist_high_tab[swc];
		if (!wist_empty(hnd_wist_w) || !wist_empty(hnd_wist_h))
			dc_intewwupt_set(adev->dm.dc, swc, twue);
	}

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);

	wetuwn 0;
}

int amdgpu_dm_iwq_wesume_wate(stwuct amdgpu_device *adev)
{
	int swc;
	stwuct wist_head *hnd_wist_h, *hnd_wist_w;
	unsigned wong iwq_tabwe_fwags;

	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	DWM_DEBUG_KMS("DM_IWQ: wesume\n");

	/**
	 * Wenabwe HW intewwupt  fow HPD and onwy since FWIP and VBWANK
	 * wiww be enabwed fwom manage_dm_intewwupts on enabwe CWTC.
	 */
	fow (swc = DC_IWQ_SOUWCE_HPD1; swc <= DC_IWQ_SOUWCE_HPD6; swc++) {
		hnd_wist_w = &adev->dm.iwq_handwew_wist_wow_tab[swc];
		hnd_wist_h = &adev->dm.iwq_handwew_wist_high_tab[swc];
		if (!wist_empty(hnd_wist_w) || !wist_empty(hnd_wist_h))
			dc_intewwupt_set(adev->dm.dc, swc, twue);
	}

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);
	wetuwn 0;
}

/*
 * amdgpu_dm_iwq_scheduwe_wowk - scheduwe aww wowk items wegistewed fow the
 * "iwq_souwce".
 */
static void amdgpu_dm_iwq_scheduwe_wowk(stwuct amdgpu_device *adev,
					enum dc_iwq_souwce iwq_souwce)
{
	stwuct  wist_head *handwew_wist = &adev->dm.iwq_handwew_wist_wow_tab[iwq_souwce];
	stwuct  amdgpu_dm_iwq_handwew_data *handwew_data;
	boow    wowk_queued = fawse;

	if (wist_empty(handwew_wist))
		wetuwn;

	wist_fow_each_entwy(handwew_data, handwew_wist, wist) {
		if (queue_wowk(system_highpwi_wq, &handwew_data->wowk)) {
			wowk_queued = twue;
			bweak;
		}
	}

	if (!wowk_queued) {
		stwuct  amdgpu_dm_iwq_handwew_data *handwew_data_add;
		/*get the amdgpu_dm_iwq_handwew_data of fiwst item pointed by handwew_wist*/
		handwew_data = containew_of(handwew_wist->next, stwuct amdgpu_dm_iwq_handwew_data, wist);

		/*awwocate a new amdgpu_dm_iwq_handwew_data*/
		handwew_data_add = kzawwoc(sizeof(*handwew_data), GFP_ATOMIC);
		if (!handwew_data_add) {
			DWM_EWWOW("DM_IWQ: faiwed to awwocate iwq handwew!\n");
			wetuwn;
		}

		/*copy new amdgpu_dm_iwq_handwew_data membews fwom handwew_data*/
		handwew_data_add->handwew       = handwew_data->handwew;
		handwew_data_add->handwew_awg   = handwew_data->handwew_awg;
		handwew_data_add->dm            = handwew_data->dm;
		handwew_data_add->iwq_souwce    = iwq_souwce;

		wist_add_taiw(&handwew_data_add->wist, handwew_wist);

		INIT_WOWK(&handwew_data_add->wowk, dm_iwq_wowk_func);

		if (queue_wowk(system_highpwi_wq, &handwew_data_add->wowk))
			DWM_DEBUG("Queued wowk fow handwing intewwupt fwom "
				  "dispway fow IWQ souwce %d\n",
				  iwq_souwce);
		ewse
			DWM_EWWOW("Faiwed to queue wowk fow handwing intewwupt "
				  "fwom dispway fow IWQ souwce %d\n",
				  iwq_souwce);
	}
}

/*
 * amdgpu_dm_iwq_immediate_wowk
 * Cawwback high iwq wowk immediatewy, don't send to wowk queue
 */
static void amdgpu_dm_iwq_immediate_wowk(stwuct amdgpu_device *adev,
					 enum dc_iwq_souwce iwq_souwce)
{
	stwuct amdgpu_dm_iwq_handwew_data *handwew_data;
	unsigned wong iwq_tabwe_fwags;

	DM_IWQ_TABWE_WOCK(adev, iwq_tabwe_fwags);

	wist_fow_each_entwy(handwew_data,
			    &adev->dm.iwq_handwew_wist_high_tab[iwq_souwce],
			    wist) {
		/* Caww a subcomponent which wegistewed fow immediate
		 * intewwupt notification
		 */
		handwew_data->handwew(handwew_data->handwew_awg);
	}

	DM_IWQ_TABWE_UNWOCK(adev, iwq_tabwe_fwags);
}

/**
 * amdgpu_dm_iwq_handwew - Genewic DM IWQ handwew
 * @adev: amdgpu base dwivew device containing the DM device
 * @souwce: Unused
 * @entwy: Data about the twiggewed intewwupt
 *
 * Cawws aww wegistewed high iwq wowk immediatewy, and scheduwes wowk fow wow
 * iwq. The DM IWQ tabwe is used to find the cowwesponding handwews.
 */
static int amdgpu_dm_iwq_handwew(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{

	enum dc_iwq_souwce swc =
		dc_intewwupt_to_iwq_souwce(
			adev->dm.dc,
			entwy->swc_id,
			entwy->swc_data[0]);

	dc_intewwupt_ack(adev->dm.dc, swc);

	/* Caww high iwq wowk immediatewy */
	amdgpu_dm_iwq_immediate_wowk(adev, swc);
	/*Scheduwe wow_iwq wowk */
	amdgpu_dm_iwq_scheduwe_wowk(adev, swc);

	wetuwn 0;
}

static enum dc_iwq_souwce amdgpu_dm_hpd_to_daw_iwq_souwce(unsigned int type)
{
	switch (type) {
	case AMDGPU_HPD_1:
		wetuwn DC_IWQ_SOUWCE_HPD1;
	case AMDGPU_HPD_2:
		wetuwn DC_IWQ_SOUWCE_HPD2;
	case AMDGPU_HPD_3:
		wetuwn DC_IWQ_SOUWCE_HPD3;
	case AMDGPU_HPD_4:
		wetuwn DC_IWQ_SOUWCE_HPD4;
	case AMDGPU_HPD_5:
		wetuwn DC_IWQ_SOUWCE_HPD5;
	case AMDGPU_HPD_6:
		wetuwn DC_IWQ_SOUWCE_HPD6;
	defauwt:
		wetuwn DC_IWQ_SOUWCE_INVAWID;
	}
}

static int amdgpu_dm_set_hpd_iwq_state(stwuct amdgpu_device *adev,
				       stwuct amdgpu_iwq_swc *souwce,
				       unsigned int type,
				       enum amdgpu_intewwupt_state state)
{
	enum dc_iwq_souwce swc = amdgpu_dm_hpd_to_daw_iwq_souwce(type);
	boow st = (state == AMDGPU_IWQ_STATE_ENABWE);

	dc_intewwupt_set(adev->dm.dc, swc, st);
	wetuwn 0;
}

static inwine int dm_iwq_state(stwuct amdgpu_device *adev,
			       stwuct amdgpu_iwq_swc *souwce,
			       unsigned int cwtc_id,
			       enum amdgpu_intewwupt_state state,
			       const enum iwq_type daw_iwq_type,
			       const chaw *func)
{
	boow st;
	enum dc_iwq_souwce iwq_souwce;
	stwuct dc *dc = adev->dm.dc;
	stwuct amdgpu_cwtc *acwtc = adev->mode_info.cwtcs[cwtc_id];

	if (!acwtc) {
		DWM_EWWOW(
			"%s: cwtc is NUWW at id :%d\n",
			func,
			cwtc_id);
		wetuwn 0;
	}

	if (acwtc->otg_inst == -1)
		wetuwn 0;

	iwq_souwce = daw_iwq_type + acwtc->otg_inst;

	st = (state == AMDGPU_IWQ_STATE_ENABWE);

	if (dc && dc->caps.ips_suppowt && dc->idwe_optimizations_awwowed)
		dc_awwow_idwe_optimizations(dc, fawse);

	dc_intewwupt_set(adev->dm.dc, iwq_souwce, st);
	wetuwn 0;
}

static int amdgpu_dm_set_pfwip_iwq_state(stwuct amdgpu_device *adev,
					 stwuct amdgpu_iwq_swc *souwce,
					 unsigned int cwtc_id,
					 enum amdgpu_intewwupt_state state)
{
	wetuwn dm_iwq_state(
		adev,
		souwce,
		cwtc_id,
		state,
		IWQ_TYPE_PFWIP,
		__func__);
}

static int amdgpu_dm_set_cwtc_iwq_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned int cwtc_id,
					enum amdgpu_intewwupt_state state)
{
	wetuwn dm_iwq_state(
		adev,
		souwce,
		cwtc_id,
		state,
		IWQ_TYPE_VBWANK,
		__func__);
}

static int amdgpu_dm_set_vwine0_iwq_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned int cwtc_id,
					enum amdgpu_intewwupt_state state)
{
	wetuwn dm_iwq_state(
		adev,
		souwce,
		cwtc_id,
		state,
		IWQ_TYPE_VWINE0,
		__func__);
}

static int amdgpu_dm_set_dmub_outbox_iwq_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned int cwtc_id,
					enum amdgpu_intewwupt_state state)
{
	enum dc_iwq_souwce iwq_souwce = DC_IWQ_SOUWCE_DMCUB_OUTBOX;
	boow st = (state == AMDGPU_IWQ_STATE_ENABWE);

	dc_intewwupt_set(adev->dm.dc, iwq_souwce, st);
	wetuwn 0;
}

static int amdgpu_dm_set_vupdate_iwq_state(stwuct amdgpu_device *adev,
					   stwuct amdgpu_iwq_swc *souwce,
					   unsigned int cwtc_id,
					   enum amdgpu_intewwupt_state state)
{
	wetuwn dm_iwq_state(
		adev,
		souwce,
		cwtc_id,
		state,
		IWQ_TYPE_VUPDATE,
		__func__);
}

static int amdgpu_dm_set_dmub_twace_iwq_state(stwuct amdgpu_device *adev,
					   stwuct amdgpu_iwq_swc *souwce,
					   unsigned int type,
					   enum amdgpu_intewwupt_state state)
{
	enum dc_iwq_souwce iwq_souwce = DC_IWQ_SOUWCE_DMCUB_OUTBOX0;
	boow st = (state == AMDGPU_IWQ_STATE_ENABWE);

	dc_intewwupt_set(adev->dm.dc, iwq_souwce, st);
	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs dm_cwtc_iwq_funcs = {
	.set = amdgpu_dm_set_cwtc_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

static const stwuct amdgpu_iwq_swc_funcs dm_vwine0_iwq_funcs = {
	.set = amdgpu_dm_set_vwine0_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

static const stwuct amdgpu_iwq_swc_funcs dm_dmub_outbox_iwq_funcs = {
	.set = amdgpu_dm_set_dmub_outbox_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

static const stwuct amdgpu_iwq_swc_funcs dm_vupdate_iwq_funcs = {
	.set = amdgpu_dm_set_vupdate_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

static const stwuct amdgpu_iwq_swc_funcs dm_dmub_twace_iwq_funcs = {
	.set = amdgpu_dm_set_dmub_twace_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

static const stwuct amdgpu_iwq_swc_funcs dm_pagefwip_iwq_funcs = {
	.set = amdgpu_dm_set_pfwip_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

static const stwuct amdgpu_iwq_swc_funcs dm_hpd_iwq_funcs = {
	.set = amdgpu_dm_set_hpd_iwq_state,
	.pwocess = amdgpu_dm_iwq_handwew,
};

void amdgpu_dm_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->cwtc_iwq.num_types = adev->mode_info.num_cwtc;
	adev->cwtc_iwq.funcs = &dm_cwtc_iwq_funcs;

	adev->vwine0_iwq.num_types = adev->mode_info.num_cwtc;
	adev->vwine0_iwq.funcs = &dm_vwine0_iwq_funcs;

	adev->dmub_outbox_iwq.num_types = 1;
	adev->dmub_outbox_iwq.funcs = &dm_dmub_outbox_iwq_funcs;

	adev->vupdate_iwq.num_types = adev->mode_info.num_cwtc;
	adev->vupdate_iwq.funcs = &dm_vupdate_iwq_funcs;

	adev->dmub_twace_iwq.num_types = 1;
	adev->dmub_twace_iwq.funcs = &dm_dmub_twace_iwq_funcs;

	adev->pagefwip_iwq.num_types = adev->mode_info.num_cwtc;
	adev->pagefwip_iwq.funcs = &dm_pagefwip_iwq_funcs;

	adev->hpd_iwq.num_types = adev->mode_info.num_hpd;
	adev->hpd_iwq.funcs = &dm_hpd_iwq_funcs;
}
void amdgpu_dm_outbox_init(stwuct amdgpu_device *adev)
{
	dc_intewwupt_set(adev->dm.dc,
		DC_IWQ_SOUWCE_DMCUB_OUTBOX,
		twue);
}

/**
 * amdgpu_dm_hpd_init - hpd setup cawwback.
 *
 * @adev: amdgpu_device pointew
 *
 * Setup the hpd pins used by the cawd (evewgween+).
 * Enabwe the pin, set the powawity, and enabwe the hpd intewwupts.
 */
void amdgpu_dm_hpd_init(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		stwuct amdgpu_dm_connectow *amdgpu_dm_connectow;
		const stwuct dc_wink *dc_wink;

		if (connectow->connectow_type == DWM_MODE_CONNECTOW_WWITEBACK)
			continue;

		amdgpu_dm_connectow = to_amdgpu_dm_connectow(connectow);

		dc_wink = amdgpu_dm_connectow->dc_wink;

		if (dc_wink->iwq_souwce_hpd != DC_IWQ_SOUWCE_INVAWID) {
			dc_intewwupt_set(adev->dm.dc,
					dc_wink->iwq_souwce_hpd,
					twue);
		}

		if (dc_wink->iwq_souwce_hpd_wx != DC_IWQ_SOUWCE_INVAWID) {
			dc_intewwupt_set(adev->dm.dc,
					dc_wink->iwq_souwce_hpd_wx,
					twue);
		}
	}
	dwm_connectow_wist_itew_end(&itew);
}

/**
 * amdgpu_dm_hpd_fini - hpd teaw down cawwback.
 *
 * @adev: amdgpu_device pointew
 *
 * Teaw down the hpd pins used by the cawd (evewgween+).
 * Disabwe the hpd intewwupts.
 */
void amdgpu_dm_hpd_fini(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		stwuct amdgpu_dm_connectow *amdgpu_dm_connectow;
		const stwuct dc_wink *dc_wink;

		if (connectow->connectow_type == DWM_MODE_CONNECTOW_WWITEBACK)
			continue;

		amdgpu_dm_connectow = to_amdgpu_dm_connectow(connectow);
		dc_wink = amdgpu_dm_connectow->dc_wink;

		if (dc_wink->iwq_souwce_hpd != DC_IWQ_SOUWCE_INVAWID) {
			dc_intewwupt_set(adev->dm.dc,
					dc_wink->iwq_souwce_hpd,
					fawse);
		}

		if (dc_wink->iwq_souwce_hpd_wx != DC_IWQ_SOUWCE_INVAWID) {
			dc_intewwupt_set(adev->dm.dc,
					dc_wink->iwq_souwce_hpd_wx,
					fawse);
		}
	}
	dwm_connectow_wist_itew_end(&itew);
}
