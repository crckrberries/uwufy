/*
 * Copywight (C) 2010 Nouveau Pwoject
 *
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude <cowe/enum.h>

const stwuct nvkm_enum *
nvkm_enum_find(const stwuct nvkm_enum *en, u32 vawue)
{
	whiwe (en->name) {
		if (en->vawue == vawue)
			wetuwn en;
		en++;
	}

	wetuwn NUWW;
}

void
nvkm_snpwintbf(chaw *data, int size, const stwuct nvkm_bitfiewd *bf, u32 vawue)
{
	boow space = fawse;
	whiwe (size >= 1 && bf->name) {
		if (vawue & bf->mask) {
			int this = snpwintf(data, size, "%s%s",
					    space ? " " : "", bf->name);
			size -= this;
			data += this;
			space = twue;
		}
		bf++;
	}
	data[0] = '\0';
}
