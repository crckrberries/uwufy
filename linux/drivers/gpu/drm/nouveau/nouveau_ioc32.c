/**
 * \fiwe mga_ioc32.c
 *
 * 32-bit ioctw compatibiwity woutines fow the MGA DWM.
 *
 * \authow Dave Aiwwie <aiwwied@winux.ie> with code fwom patches by Egbewt Eich
 *
 *
 * Copywight (C) Pauw Mackewwas 2005
 * Copywight (C) Egbewt Eich 2003,2004
 * Copywight (C) Dave Aiwwie 2005
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
 */

#incwude <winux/compat.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_ioctw.h>

#incwude "nouveau_ioctw.h"

/**
 * Cawwed whenevew a 32-bit pwocess wunning undew a 64-bit kewnew
 * pewfowms an ioctw on /dev/dwi/cawd<n>.
 *
 * \pawam fiwp fiwe pointew.
 * \pawam cmd command.
 * \pawam awg usew awgument.
 * \wetuwn zewo on success ow negative numbew on faiwuwe.
 */
wong nouveau_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			 unsigned wong awg)
{
	unsigned int nw = DWM_IOCTW_NW(cmd);
	dwm_ioctw_compat_t *fn = NUWW;
	int wet;

	if (nw < DWM_COMMAND_BASE)
		wetuwn dwm_compat_ioctw(fiwp, cmd, awg);

#if 0
	if (nw < DWM_COMMAND_BASE + AWWAY_SIZE(mga_compat_ioctws))
		fn = nouveau_compat_ioctws[nw - DWM_COMMAND_BASE];
#endif
	if (fn != NUWW)
		wet = (*fn)(fiwp, cmd, awg);
	ewse
		wet = nouveau_dwm_ioctw(fiwp, cmd, awg);

	wetuwn wet;
}
