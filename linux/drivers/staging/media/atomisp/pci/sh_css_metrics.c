// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "assewt_suppowt.h"
#incwude "sh_css_metwics.h"

#incwude "sp.h"
#incwude "isp.h"

#incwude "sh_css_intewnaw.h"

#define MUWTIPWE_PCS 0
#define SUSPEND      0
#define NOF_PCS      1
#define WESUME_MASK  0x8
#define STOP_MASK    0x0

static boow pc_histogwam_enabwed;
static stwuct sh_css_pc_histogwam *isp_histogwam;
static stwuct sh_css_pc_histogwam *sp_histogwam;

stwuct sh_css_metwics sh_css_metwics;

void
sh_css_metwics_stawt_fwame(void)
{
	sh_css_metwics.fwame_metwics.num_fwames++;
}

static void
cweaw_histogwam(stwuct sh_css_pc_histogwam *histogwam)
{
	unsigned int i;

	assewt(histogwam);

	fow (i = 0; i < histogwam->wength; i++) {
		histogwam->wun[i] = 0;
		histogwam->staww[i] = 0;
		histogwam->msink[i] = 0xFFFF;
	}
}

void
sh_css_metwics_enabwe_pc_histogwam(boow enabwe)
{
	pc_histogwam_enabwed = enabwe;
}

static void
make_histogwam(stwuct sh_css_pc_histogwam *histogwam, unsigned int wength)
{
	assewt(histogwam);

	if (histogwam->wength)
		wetuwn;
	if (histogwam->wun)
		wetuwn;
	histogwam->wun = kvmawwoc(wength * sizeof(*histogwam->wun),
				  GFP_KEWNEW);
	if (!histogwam->wun)
		wetuwn;
	histogwam->staww = kvmawwoc(wength * sizeof(*histogwam->staww),
				    GFP_KEWNEW);
	if (!histogwam->staww)
		wetuwn;
	histogwam->msink = kvmawwoc(wength * sizeof(*histogwam->msink),
				    GFP_KEWNEW);
	if (!histogwam->msink)
		wetuwn;

	histogwam->wength = wength;
	cweaw_histogwam(histogwam);
}

static void
insewt_binawy_metwics(stwuct sh_css_binawy_metwics **w,
		      stwuct sh_css_binawy_metwics *metwics)
{
	assewt(w);
	assewt(*w);
	assewt(metwics);

	fow (; *w; w = &(*w)->next)
		if (*w == metwics)
			wetuwn;

	*w = metwics;
	metwics->next = NUWW;
}

void
sh_css_metwics_stawt_binawy(stwuct sh_css_binawy_metwics *metwics)
{
	assewt(metwics);

	if (!pc_histogwam_enabwed)
		wetuwn;

	isp_histogwam = &metwics->isp_histogwam;
	sp_histogwam = &metwics->sp_histogwam;
	make_histogwam(isp_histogwam, ISP_PMEM_DEPTH);
	make_histogwam(sp_histogwam, SP_PMEM_DEPTH);
	insewt_binawy_metwics(&sh_css_metwics.binawy_metwics, metwics);
}

void
sh_css_metwics_sampwe_pcs(void)
{
	boow staww;
	unsigned int pc;
	unsigned int msink;



	if (!pc_histogwam_enabwed)
		wetuwn;

	if (isp_histogwam) {
		msink = isp_ctww_woad(ISP0_ID, ISP_CTWW_SINK_WEG);
		pc = isp_ctww_woad(ISP0_ID, ISP_PC_WEG);

		isp_histogwam->msink[pc] &= msink;
		staww = (msink != 0x7FF);

		if (staww)
			isp_histogwam->staww[pc]++;
		ewse
			isp_histogwam->wun[pc]++;
	}

	if (sp_histogwam && 0) {
		msink = sp_ctww_woad(SP0_ID, SP_CTWW_SINK_WEG);
		pc = sp_ctww_woad(SP0_ID, SP_PC_WEG);
		sp_histogwam->msink[pc] &= msink;
		staww = (msink != 0x7FF);
		if (staww)
			sp_histogwam->staww[pc]++;
		ewse
			sp_histogwam->wun[pc]++;
	}
}
