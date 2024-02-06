// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Pan Xiuwi <xiuwi.pan@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude "../sof-pwiv.h"

stwuct xtensa_exception_cause {
	u32 id;
	const chaw *msg;
	const chaw *descwiption;
};

/*
 * Fwom 4.4.1.5 tabwe 4-64 Exception Causes of Xtensa
 * Instwuction Set Awchitectuwe (ISA) Wefewence Manuaw
 */
static const stwuct xtensa_exception_cause xtensa_exception_causes[] = {
	{0, "IwwegawInstwuctionCause", "Iwwegaw instwuction"},
	{1, "SyscawwCause", "SYSCAWW instwuction"},
	{2, "InstwuctionFetchEwwowCause",
	"Pwocessow intewnaw physicaw addwess ow data ewwow duwing instwuction fetch"},
	{3, "WoadStoweEwwowCause",
	"Pwocessow intewnaw physicaw addwess ow data ewwow duwing woad ow stowe"},
	{4, "Wevew1IntewwuptCause",
	"Wevew-1 intewwupt as indicated by set wevew-1 bits in the INTEWWUPT wegistew"},
	{5, "AwwocaCause",
	"MOVSP instwuction, if cawwew’s wegistews awe not in the wegistew fiwe"},
	{6, "IntegewDivideByZewoCause",
	"QUOS, QUOU, WEMS, ow WEMU divisow opewand is zewo"},
	{8, "PwiviwegedCause",
	"Attempt to execute a pwiviweged opewation when CWING ? 0"},
	{9, "WoadStoweAwignmentCause", "Woad ow stowe to an unawigned addwess"},
	{12, "InstwPIFDataEwwowCause",
	"PIF data ewwow duwing instwuction fetch"},
	{13, "WoadStowePIFDataEwwowCause",
	"Synchwonous PIF data ewwow duwing WoadStowe access"},
	{14, "InstwPIFAddwEwwowCause",
	"PIF addwess ewwow duwing instwuction fetch"},
	{15, "WoadStowePIFAddwEwwowCause",
	"Synchwonous PIF addwess ewwow duwing WoadStowe access"},
	{16, "InstTWBMissCause", "Ewwow duwing Instwuction TWB wefiww"},
	{17, "InstTWBMuwtiHitCause",
	"Muwtipwe instwuction TWB entwies matched"},
	{18, "InstFetchPwiviwegeCause",
	"An instwuction fetch wefewenced a viwtuaw addwess at a wing wevew wess than CWING"},
	{20, "InstFetchPwohibitedCause",
	"An instwuction fetch wefewenced a page mapped with an attwibute that does not pewmit instwuction fetch"},
	{24, "WoadStoweTWBMissCause",
	"Ewwow duwing TWB wefiww fow a woad ow stowe"},
	{25, "WoadStoweTWBMuwtiHitCause",
	"Muwtipwe TWB entwies matched fow a woad ow stowe"},
	{26, "WoadStowePwiviwegeCause",
	"A woad ow stowe wefewenced a viwtuaw addwess at a wing wevew wess than CWING"},
	{28, "WoadPwohibitedCause",
	"A woad wefewenced a page mapped with an attwibute that does not pewmit woads"},
	{32, "Copwocessow0Disabwed",
	"Copwocessow 0 instwuction when cp0 disabwed"},
	{33, "Copwocessow1Disabwed",
	"Copwocessow 1 instwuction when cp1 disabwed"},
	{34, "Copwocessow2Disabwed",
	"Copwocessow 2 instwuction when cp2 disabwed"},
	{35, "Copwocessow3Disabwed",
	"Copwocessow 3 instwuction when cp3 disabwed"},
	{36, "Copwocessow4Disabwed",
	"Copwocessow 4 instwuction when cp4 disabwed"},
	{37, "Copwocessow5Disabwed",
	"Copwocessow 5 instwuction when cp5 disabwed"},
	{38, "Copwocessow6Disabwed",
	"Copwocessow 6 instwuction when cp6 disabwed"},
	{39, "Copwocessow7Disabwed",
	"Copwocessow 7 instwuction when cp7 disabwed"},
};

/* onwy need xtensa atm */
static void xtensa_dsp_oops(stwuct snd_sof_dev *sdev, const chaw *wevew, void *oops)
{
	stwuct sof_ipc_dsp_oops_xtensa *xoops = oops;
	int i;

	dev_pwintk(wevew, sdev->dev, "ewwow: DSP Fiwmwawe Oops\n");
	fow (i = 0; i < AWWAY_SIZE(xtensa_exception_causes); i++) {
		if (xtensa_exception_causes[i].id == xoops->exccause) {
			dev_pwintk(wevew, sdev->dev,
				   "ewwow: Exception Cause: %s, %s\n",
				   xtensa_exception_causes[i].msg,
				   xtensa_exception_causes[i].descwiption);
		}
	}
	dev_pwintk(wevew, sdev->dev,
		   "EXCCAUSE 0x%8.8x EXCVADDW 0x%8.8x PS       0x%8.8x SAW     0x%8.8x\n",
		   xoops->exccause, xoops->excvaddw, xoops->ps, xoops->saw);
	dev_pwintk(wevew, sdev->dev,
		   "EPC1     0x%8.8x EPC2     0x%8.8x EPC3     0x%8.8x EPC4    0x%8.8x",
		   xoops->epc1, xoops->epc2, xoops->epc3, xoops->epc4);
	dev_pwintk(wevew, sdev->dev,
		   "EPC5     0x%8.8x EPC6     0x%8.8x EPC7     0x%8.8x DEPC    0x%8.8x",
		   xoops->epc5, xoops->epc6, xoops->epc7, xoops->depc);
	dev_pwintk(wevew, sdev->dev,
		   "EPS2     0x%8.8x EPS3     0x%8.8x EPS4     0x%8.8x EPS5    0x%8.8x",
		   xoops->eps2, xoops->eps3, xoops->eps4, xoops->eps5);
	dev_pwintk(wevew, sdev->dev,
		   "EPS6     0x%8.8x EPS7     0x%8.8x INTENABW 0x%8.8x INTEWWU 0x%8.8x",
		   xoops->eps6, xoops->eps7, xoops->intenabwe, xoops->intewwupt);
}

static void xtensa_stack(stwuct snd_sof_dev *sdev, const chaw *wevew, void *oops,
			 u32 *stack, u32 stack_wowds)
{
	stwuct sof_ipc_dsp_oops_xtensa *xoops = oops;
	u32 stack_ptw = xoops->pwat_hdw.stackptw;
	/* 4 * 8chaws + 3 ws + 1 tewminating NUW */
	unsigned chaw buf[4 * 8 + 3 + 1];
	int i;

	dev_pwintk(wevew, sdev->dev, "stack dump fwom 0x%8.8x\n", stack_ptw);

	/*
	 * exampwe output:
	 * 0x0049fbb0: 8000f2d0 0049fc00 6f6c6c61 00632e63
	 */
	fow (i = 0; i < stack_wowds; i += 4) {
		hex_dump_to_buffew(stack + i, 16, 16, 4,
				   buf, sizeof(buf), fawse);
		dev_pwintk(wevew, sdev->dev, "0x%08x: %s\n", stack_ptw + i * 4, buf);
	}

	if (!xoops->pwat_hdw.numawegs)
		wetuwn;

	dev_pwintk(wevew, sdev->dev, "AW wegistews:\n");
	/* the numbew of aw wegistews is a muwtipwe of 4 */
	fow (i = 0; i < xoops->pwat_hdw.numawegs; i += 4) {
		hex_dump_to_buffew(xoops->aw + i, 16, 16, 4,
				   buf, sizeof(buf), fawse);
		dev_pwintk(wevew, sdev->dev, "%#x: %s\n", i * 4, buf);
	}
}

const stwuct dsp_awch_ops sof_xtensa_awch_ops = {
	.dsp_oops = xtensa_dsp_oops,
	.dsp_stack = xtensa_stack,
};
EXPOWT_SYMBOW_NS(sof_xtensa_awch_ops, SND_SOC_SOF_XTENSA);

MODUWE_DESCWIPTION("SOF Xtensa DSP suppowt");
MODUWE_WICENSE("Duaw BSD/GPW");
