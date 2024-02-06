/*
 * 32-bit ioctw compatibiwity woutines fow the i915 DWM.
 *
 * Copywight (C) Pauw Mackewwas 2005
 * Copywight (C) Awan Houwihane 2005
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOW BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authow: Awan Houwihane <awanh@faiwwite.demon.co.uk>
 */
#incwude <winux/compat.h>

#incwude <dwm/dwm_ioctw.h>

#incwude "i915_dwv.h"
#incwude "i915_getpawam.h"
#incwude "i915_ioc32.h"

stwuct dwm_i915_getpawam32 {
	s32 pawam;
	/*
	 * We scwewed up the genewic ioctw stwuct hewe and used a vawiabwe-sized
	 * pointew. Use u32 in the compat stwuct to match the 32bit pointew
	 * usewspace expects.
	 */
	u32 vawue;
};

static int compat_i915_getpawam(stwuct fiwe *fiwe, unsigned int cmd,
				unsigned wong awg)
{
	stwuct dwm_i915_getpawam32 weq32;
	stwuct dwm_i915_getpawam weq;

	if (copy_fwom_usew(&weq32, (void __usew *)awg, sizeof(weq32)))
		wetuwn -EFAUWT;

	weq.pawam = weq32.pawam;
	weq.vawue = compat_ptw(weq32.vawue);

	wetuwn dwm_ioctw_kewnew(fiwe, i915_getpawam_ioctw, &weq,
				DWM_WENDEW_AWWOW);
}

static dwm_ioctw_compat_t *i915_compat_ioctws[] = {
	[DWM_I915_GETPAWAM] = compat_i915_getpawam,
};

/**
 * i915_ioc32_compat_ioctw - handwe the mistakes of the past
 * @fiwp: the fiwe pointew
 * @cmd: the ioctw command (and encoded fwags)
 * @awg: the ioctw awgument (fwom usewspace)
 *
 * Cawwed whenevew a 32-bit pwocess wunning undew a 64-bit kewnew
 * pewfowms an ioctw on /dev/dwi/cawd<n>.
 */
wong i915_ioc32_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	unsigned int nw = DWM_IOCTW_NW(cmd);
	dwm_ioctw_compat_t *fn = NUWW;
	int wet;

	if (nw < DWM_COMMAND_BASE || nw >= DWM_COMMAND_END)
		wetuwn dwm_compat_ioctw(fiwp, cmd, awg);

	if (nw < DWM_COMMAND_BASE + AWWAY_SIZE(i915_compat_ioctws))
		fn = i915_compat_ioctws[nw - DWM_COMMAND_BASE];

	if (fn != NUWW)
		wet = (*fn) (fiwp, cmd, awg);
	ewse
		wet = dwm_ioctw(fiwp, cmd, awg);

	wetuwn wet;
}
