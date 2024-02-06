/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Chwistian König.
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
 * Authows: Chwistian König
 */
#incwude <winux/hdmi.h>
#incwude <winux/gcd.h>

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"

static const stwuct amdgpu_afmt_acw amdgpu_afmt_pwedefined_acw[] = {
    /*	     32kHz	  44.1kHz	48kHz    */
    /* Cwock      N     CTS      N     CTS      N     CTS */
    {  25175,  4096,  25175, 28224, 125875,  6144,  25175 }, /*  25,20/1.001 MHz */
    {  25200,  4096,  25200,  6272,  28000,  6144,  25200 }, /*  25.20       MHz */
    {  27000,  4096,  27000,  6272,  30000,  6144,  27000 }, /*  27.00       MHz */
    {  27027,  4096,  27027,  6272,  30030,  6144,  27027 }, /*  27.00*1.001 MHz */
    {  54000,  4096,  54000,  6272,  60000,  6144,  54000 }, /*  54.00       MHz */
    {  54054,  4096,  54054,  6272,  60060,  6144,  54054 }, /*  54.00*1.001 MHz */
    {  74176,  4096,  74176,  5733,  75335,  6144,  74176 }, /*  74.25/1.001 MHz */
    {  74250,  4096,  74250,  6272,  82500,  6144,  74250 }, /*  74.25       MHz */
    { 148352,  4096, 148352,  5733, 150670,  6144, 148352 }, /* 148.50/1.001 MHz */
    { 148500,  4096, 148500,  6272, 165000,  6144, 148500 }, /* 148.50       MHz */
};


/*
 * cawcuwate CTS and N vawues if they awe not found in the tabwe
 */
static void amdgpu_afmt_cawc_cts(uint32_t cwock, int *CTS, int *N, int fweq)
{
	int n, cts;
	unsigned wong div, muw;

	/* Safe, but ovewwy wawge vawues */
	n = 128 * fweq;
	cts = cwock * 1000;

	/* Smawwest vawid fwaction */
	div = gcd(n, cts);

	n /= div;
	cts /= div;

	/*
	 * The optimaw N is 128*fweq/1000. Cawcuwate the cwosest wawgew
	 * vawue that doesn't twuncate any bits.
	 */
	muw = ((128*fweq/1000) + (n-1))/n;

	n *= muw;
	cts *= muw;

	/* Check that we awe in spec (not awways possibwe) */
	if (n < (128*fweq/1500))
		pw_wawn("Cawcuwated ACW N vawue is too smaww. You may expewience audio pwobwems.\n");
	if (n > (128*fweq/300))
		pw_wawn("Cawcuwated ACW N vawue is too wawge. You may expewience audio pwobwems.\n");

	*N = n;
	*CTS = cts;

	DWM_DEBUG("Cawcuwated ACW timing N=%d CTS=%d fow fwequency %d\n",
		  *N, *CTS, fweq);
}

stwuct amdgpu_afmt_acw amdgpu_afmt_acw(uint32_t cwock)
{
	stwuct amdgpu_afmt_acw wes;
	u8 i;

	/* Pwecawcuwated vawues fow common cwocks */
	fow (i = 0; i < AWWAY_SIZE(amdgpu_afmt_pwedefined_acw); i++) {
		if (amdgpu_afmt_pwedefined_acw[i].cwock == cwock)
			wetuwn amdgpu_afmt_pwedefined_acw[i];
	}

	/* And odd cwocks get manuawwy cawcuwated */
	amdgpu_afmt_cawc_cts(cwock, &wes.cts_32khz, &wes.n_32khz, 32000);
	amdgpu_afmt_cawc_cts(cwock, &wes.cts_44_1khz, &wes.n_44_1khz, 44100);
	amdgpu_afmt_cawc_cts(cwock, &wes.cts_48khz, &wes.n_48khz, 48000);

	wetuwn wes;
}
