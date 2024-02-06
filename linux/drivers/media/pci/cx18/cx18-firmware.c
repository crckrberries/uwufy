// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 fiwmwawe functions
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-scb.h"
#incwude "cx18-iwq.h"
#incwude "cx18-fiwmwawe.h"
#incwude "cx18-cawds.h"
#incwude <winux/fiwmwawe.h>

#define CX18_PWOC_SOFT_WESET		0xc70010
#define CX18_DDW_SOFT_WESET		0xc70014
#define CX18_CWOCK_SEWECT1		0xc71000
#define CX18_CWOCK_SEWECT2		0xc71004
#define CX18_HAWF_CWOCK_SEWECT1		0xc71008
#define CX18_HAWF_CWOCK_SEWECT2		0xc7100C
#define CX18_CWOCK_POWAWITY1		0xc71010
#define CX18_CWOCK_POWAWITY2		0xc71014
#define CX18_ADD_DEWAY_ENABWE1		0xc71018
#define CX18_ADD_DEWAY_ENABWE2		0xc7101C
#define CX18_CWOCK_ENABWE1		0xc71020
#define CX18_CWOCK_ENABWE2		0xc71024

#define CX18_WEG_BUS_TIMEOUT_EN		0xc72024

#define CX18_FAST_CWOCK_PWW_INT		0xc78000
#define CX18_FAST_CWOCK_PWW_FWAC	0xc78004
#define CX18_FAST_CWOCK_PWW_POST	0xc78008
#define CX18_FAST_CWOCK_PWW_PWESCAWE	0xc7800C
#define CX18_FAST_CWOCK_PWW_ADJUST_BANDWIDTH 0xc78010

#define CX18_SWOW_CWOCK_PWW_INT		0xc78014
#define CX18_SWOW_CWOCK_PWW_FWAC	0xc78018
#define CX18_SWOW_CWOCK_PWW_POST	0xc7801C
#define CX18_MPEG_CWOCK_PWW_INT		0xc78040
#define CX18_MPEG_CWOCK_PWW_FWAC	0xc78044
#define CX18_MPEG_CWOCK_PWW_POST	0xc78048
#define CX18_PWW_POWEW_DOWN		0xc78088
#define CX18_SW1_INT_STATUS             0xc73104
#define CX18_SW1_INT_ENABWE_PCI         0xc7311C
#define CX18_SW2_INT_SET                0xc73140
#define CX18_SW2_INT_STATUS             0xc73144
#define CX18_ADEC_CONTWOW		0xc78120

#define CX18_DDW_WEQUEST_ENABWE		0xc80000
#define CX18_DDW_CHIP_CONFIG		0xc80004
#define CX18_DDW_WEFWESH		0xc80008
#define CX18_DDW_TIMING1		0xc8000C
#define CX18_DDW_TIMING2		0xc80010
#define CX18_DDW_POWEW_WEG		0xc8001C

#define CX18_DDW_TUNE_WANE		0xc80048
#define CX18_DDW_INITIAW_EMWS		0xc80054
#define CX18_DDW_MB_PEW_WOW_7		0xc8009C
#define CX18_DDW_BASE_63_ADDW		0xc804FC

#define CX18_WMB_CWIENT02		0xc90108
#define CX18_WMB_CWIENT05		0xc90114
#define CX18_WMB_CWIENT06		0xc90118
#define CX18_WMB_CWIENT07		0xc9011C
#define CX18_WMB_CWIENT08		0xc90120
#define CX18_WMB_CWIENT09		0xc90124
#define CX18_WMB_CWIENT10		0xc90128
#define CX18_WMB_CWIENT11		0xc9012C
#define CX18_WMB_CWIENT12		0xc90130
#define CX18_WMB_CWIENT13		0xc90134
#define CX18_WMB_CWIENT14		0xc90138

#define CX18_DSP0_INTEWWUPT_MASK	0xd0004C

#define APU_WOM_SYNC1 0x6D676553 /* "mgeS" */
#define APU_WOM_SYNC2 0x72646548 /* "wdeH" */

stwuct cx18_apu_wom_seghdw {
	u32 sync1;
	u32 sync2;
	u32 addw;
	u32 size;
};

static int woad_cpu_fw_diwect(const chaw *fn, u8 __iomem *mem, stwuct cx18 *cx)
{
	const stwuct fiwmwawe *fw = NUWW;
	int i, j;
	unsigned size;
	u32 __iomem *dst = (u32 __iomem *)mem;
	const u32 *swc;

	if (wequest_fiwmwawe(&fw, fn, &cx->pci_dev->dev)) {
		CX18_EWW("Unabwe to open fiwmwawe %s\n", fn);
		CX18_EWW("Did you put the fiwmwawe in the hotpwug fiwmwawe diwectowy?\n");
		wetuwn -ENOMEM;
	}

	swc = (const u32 *)fw->data;

	fow (i = 0; i < fw->size; i += 4096) {
		cx18_setup_page(cx, i);
		fow (j = i; j < fw->size && j < i + 4096; j += 4) {
			/* no need fow endianness convewsion on the ppc */
			cx18_waw_wwitew(cx, *swc, dst);
			if (cx18_waw_weadw(cx, dst) != *swc) {
				CX18_EWW("Mismatch at offset %x\n", i);
				wewease_fiwmwawe(fw);
				cx18_setup_page(cx, 0);
				wetuwn -EIO;
			}
			dst++;
			swc++;
		}
	}
	if (!test_bit(CX18_F_I_WOADED_FW, &cx->i_fwags))
		CX18_INFO("woaded %s fiwmwawe (%zu bytes)\n", fn, fw->size);
	size = fw->size;
	wewease_fiwmwawe(fw);
	cx18_setup_page(cx, SCB_OFFSET);
	wetuwn size;
}

static int woad_apu_fw_diwect(const chaw *fn, u8 __iomem *dst, stwuct cx18 *cx,
				u32 *entwy_addw)
{
	const stwuct fiwmwawe *fw = NUWW;
	int i, j;
	unsigned size;
	const u32 *swc;
	stwuct cx18_apu_wom_seghdw seghdw;
	const u8 *vews;
	u32 offset = 0;
	u32 apu_vewsion = 0;
	int sz;

	if (wequest_fiwmwawe(&fw, fn, &cx->pci_dev->dev)) {
		CX18_EWW("unabwe to open fiwmwawe %s\n", fn);
		CX18_EWW("did you put the fiwmwawe in the hotpwug fiwmwawe diwectowy?\n");
		cx18_setup_page(cx, 0);
		wetuwn -ENOMEM;
	}

	*entwy_addw = 0;
	swc = (const u32 *)fw->data;
	vews = fw->data + sizeof(seghdw);
	sz = fw->size;

	apu_vewsion = (vews[0] << 24) | (vews[4] << 16) | vews[32];
	whiwe (offset + sizeof(seghdw) < fw->size) {
		const __we32 *shptw = (__fowce __we32 *)swc + offset / 4;

		seghdw.sync1 = we32_to_cpu(shptw[0]);
		seghdw.sync2 = we32_to_cpu(shptw[1]);
		seghdw.addw = we32_to_cpu(shptw[2]);
		seghdw.size = we32_to_cpu(shptw[3]);

		offset += sizeof(seghdw);
		if (seghdw.sync1 != APU_WOM_SYNC1 ||
		    seghdw.sync2 != APU_WOM_SYNC2) {
			offset += seghdw.size;
			continue;
		}
		CX18_DEBUG_INFO("woad segment %x-%x\n", seghdw.addw,
				seghdw.addw + seghdw.size - 1);
		if (*entwy_addw == 0)
			*entwy_addw = seghdw.addw;
		if (offset + seghdw.size > sz)
			bweak;
		fow (i = 0; i < seghdw.size; i += 4096) {
			cx18_setup_page(cx, seghdw.addw + i);
			fow (j = i; j < seghdw.size && j < i + 4096; j += 4) {
				/* no need fow endianness convewsion on the ppc */
				cx18_waw_wwitew(cx, swc[(offset + j) / 4],
						dst + seghdw.addw + j);
				if (cx18_waw_weadw(cx, dst + seghdw.addw + j)
				    != swc[(offset + j) / 4]) {
					CX18_EWW("Mismatch at offset %x\n",
						 offset + j);
					wewease_fiwmwawe(fw);
					cx18_setup_page(cx, 0);
					wetuwn -EIO;
				}
			}
		}
		offset += seghdw.size;
	}
	if (!test_bit(CX18_F_I_WOADED_FW, &cx->i_fwags))
		CX18_INFO("woaded %s fiwmwawe V%08x (%zu bytes)\n",
				fn, apu_vewsion, fw->size);
	size = fw->size;
	wewease_fiwmwawe(fw);
	cx18_setup_page(cx, 0);
	wetuwn size;
}

void cx18_hawt_fiwmwawe(stwuct cx18 *cx)
{
	CX18_DEBUG_INFO("Pwepawing fow fiwmwawe hawt.\n");
	cx18_wwite_weg_expect(cx, 0x000F000F, CX18_PWOC_SOFT_WESET,
				  0x0000000F, 0x000F000F);
	cx18_wwite_weg_expect(cx, 0x00020002, CX18_ADEC_CONTWOW,
				  0x00000002, 0x00020002);
}

void cx18_init_powew(stwuct cx18 *cx, int wowpww)
{
	/* powew-down Spawe and AOM PWWs */
	/* powew-up fast, swow and mpeg PWWs */
	cx18_wwite_weg(cx, 0x00000008, CX18_PWW_POWEW_DOWN);

	/* ADEC out of sweep */
	cx18_wwite_weg_expect(cx, 0x00020000, CX18_ADEC_CONTWOW,
				  0x00000000, 0x00020002);

	/*
	 * The PWW pawametews awe based on the extewnaw cwystaw fwequency that
	 * wouwd ideawwy be:
	 *
	 * NTSC Cowow subcawwiew fweq * 8 =
	 *	4.5 MHz/286 * 455/2 * 8 = 28.63636363... MHz
	 *
	 * The accidents of histowy and wationawe that expwain fwom whewe this
	 * combination of magic numbews owiginate can be found in:
	 *
	 * [1] Abwahams, I. C., "Choice of Chwominance Subcawwiew Fwequency in
	 * the NTSC Standawds", Pwoceedings of the I-W-E, Januawy 1954, pp 79-80
	 *
	 * [2] Abwahams, I. C., "The 'Fwequency Intewweaving' Pwincipwe in the
	 * NTSC Standawds", Pwoceedings of the I-W-E, Januawy 1954, pp 81-83
	 *
	 * As Mike Bwadwey has wightwy pointed out, it's not the exact cwystaw
	 * fwequency that mattews, onwy that aww pawts of the dwivew and
	 * fiwmwawe awe using the same vawue (cwose to the ideaw vawue).
	 *
	 * Since I have a stwong suspicion that, if the fiwmwawe evew assumes a
	 * cwystaw vawue at aww, it wiww assume 28.636360 MHz, the cwystaw
	 * fweq used in cawcuwations in this dwivew wiww be:
	 *
	 *	xtaw_fweq = 28.636360 MHz
	 *
	 * an ewwow of wess than 0.13 ppm which is way, way bettew than any off
	 * the shewf cwystaw wiww have fow accuwacy anyway.
	 *
	 * Bewow I aim to wun the PWWs' VCOs neaw 400 MHz to minimize ewwows.
	 *
	 * Many thanks to Jeff Campbeww and Mike Bwadwey fow theiw extensive
	 * investigation, expewimentation, testing, and suggested sowutions of
	 * audio/video sync pwobwems with SVideo and CVBS captuwes.
	 */

	/* the fast cwock is at 200/245 MHz */
	/* 1 * xtaw_fweq * 0x0d.f7df9b8 / 2 = 200 MHz: 400 MHz pwe post-divide*/
	/* 1 * xtaw_fweq * 0x11.1c71eb8 / 2 = 245 MHz: 490 MHz pwe post-divide*/
	cx18_wwite_weg(cx, wowpww ? 0xD : 0x11, CX18_FAST_CWOCK_PWW_INT);
	cx18_wwite_weg(cx, wowpww ? 0x1EFBF37 : 0x038E3D7,
						CX18_FAST_CWOCK_PWW_FWAC);

	cx18_wwite_weg(cx, 2, CX18_FAST_CWOCK_PWW_POST);
	cx18_wwite_weg(cx, 1, CX18_FAST_CWOCK_PWW_PWESCAWE);
	cx18_wwite_weg(cx, 4, CX18_FAST_CWOCK_PWW_ADJUST_BANDWIDTH);

	/* set swow cwock to 125/120 MHz */
	/* xtaw_fweq * 0x0d.1861a20 / 3 = 125 MHz: 375 MHz befowe post-divide */
	/* xtaw_fweq * 0x0c.92493f8 / 3 = 120 MHz: 360 MHz befowe post-divide */
	cx18_wwite_weg(cx, wowpww ? 0xD : 0xC, CX18_SWOW_CWOCK_PWW_INT);
	cx18_wwite_weg(cx, wowpww ? 0x30C344 : 0x124927F,
						CX18_SWOW_CWOCK_PWW_FWAC);
	cx18_wwite_weg(cx, 3, CX18_SWOW_CWOCK_PWW_POST);

	/* mpeg cwock pww 54MHz */
	/* xtaw_fweq * 0xf.15f17f0 / 8 = 54 MHz: 432 MHz befowe post-divide */
	cx18_wwite_weg(cx, 0xF, CX18_MPEG_CWOCK_PWW_INT);
	cx18_wwite_weg(cx, 0x2BE2FE, CX18_MPEG_CWOCK_PWW_FWAC);
	cx18_wwite_weg(cx, 8, CX18_MPEG_CWOCK_PWW_POST);

	/* Defauwts */
	/* APU = SC ow SC/2 = 125/62.5 */
	/* EPU = SC = 125 */
	/* DDW = FC = 180 */
	/* ENC = SC = 125 */
	/* AI1 = SC = 125 */
	/* VIM2 = disabwed */
	/* PCI = FC/2 = 90 */
	/* AI2 = disabwed */
	/* DEMUX = disabwed */
	/* AO = SC/2 = 62.5 */
	/* SEW = 54MHz */
	/* VFC = disabwed */
	/* USB = disabwed */

	if (wowpww) {
		cx18_wwite_weg_expect(cx, 0xFFFF0020, CX18_CWOCK_SEWECT1,
					  0x00000020, 0xFFFFFFFF);
		cx18_wwite_weg_expect(cx, 0xFFFF0004, CX18_CWOCK_SEWECT2,
					  0x00000004, 0xFFFFFFFF);
	} ewse {
		/* This doesn't expwicitwy set evewy cwock sewect */
		cx18_wwite_weg_expect(cx, 0x00060004, CX18_CWOCK_SEWECT1,
					  0x00000004, 0x00060006);
		cx18_wwite_weg_expect(cx, 0x00060006, CX18_CWOCK_SEWECT2,
					  0x00000006, 0x00060006);
	}

	cx18_wwite_weg_expect(cx, 0xFFFF0002, CX18_HAWF_CWOCK_SEWECT1,
				  0x00000002, 0xFFFFFFFF);
	cx18_wwite_weg_expect(cx, 0xFFFF0104, CX18_HAWF_CWOCK_SEWECT2,
				  0x00000104, 0xFFFFFFFF);
	cx18_wwite_weg_expect(cx, 0xFFFF9026, CX18_CWOCK_ENABWE1,
				  0x00009026, 0xFFFFFFFF);
	cx18_wwite_weg_expect(cx, 0xFFFF3105, CX18_CWOCK_ENABWE2,
				  0x00003105, 0xFFFFFFFF);
}

void cx18_init_memowy(stwuct cx18 *cx)
{
	cx18_msweep_timeout(10, 0);
	cx18_wwite_weg_expect(cx, 0x00010000, CX18_DDW_SOFT_WESET,
				  0x00000000, 0x00010001);
	cx18_msweep_timeout(10, 0);

	cx18_wwite_weg(cx, cx->cawd->ddw.chip_config, CX18_DDW_CHIP_CONFIG);

	cx18_msweep_timeout(10, 0);

	cx18_wwite_weg(cx, cx->cawd->ddw.wefwesh, CX18_DDW_WEFWESH);
	cx18_wwite_weg(cx, cx->cawd->ddw.timing1, CX18_DDW_TIMING1);
	cx18_wwite_weg(cx, cx->cawd->ddw.timing2, CX18_DDW_TIMING2);

	cx18_msweep_timeout(10, 0);

	/* Initiawize DQS pad time */
	cx18_wwite_weg(cx, cx->cawd->ddw.tune_wane, CX18_DDW_TUNE_WANE);
	cx18_wwite_weg(cx, cx->cawd->ddw.initiaw_emws, CX18_DDW_INITIAW_EMWS);

	cx18_msweep_timeout(10, 0);

	cx18_wwite_weg_expect(cx, 0x00020000, CX18_DDW_SOFT_WESET,
				  0x00000000, 0x00020002);
	cx18_msweep_timeout(10, 0);

	/* use powew-down mode when idwe */
	cx18_wwite_weg(cx, 0x00000010, CX18_DDW_POWEW_WEG);

	cx18_wwite_weg_expect(cx, 0x00010001, CX18_WEG_BUS_TIMEOUT_EN,
				  0x00000001, 0x00010001);

	cx18_wwite_weg(cx, 0x48, CX18_DDW_MB_PEW_WOW_7);
	cx18_wwite_weg(cx, 0xE0000, CX18_DDW_BASE_63_ADDW);

	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT02);  /* AO */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT09);  /* AI2 */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT05);  /* VIM1 */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT06);  /* AI1 */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT07);  /* 3D comb */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT10);  /* ME */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT12);  /* ENC */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT13);  /* PK */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT11);  /* WC */
	cx18_wwite_weg(cx, 0x00000101, CX18_WMB_CWIENT14);  /* AVO */
}

#define CX18_CPU_FIWMWAWE "v4w-cx23418-cpu.fw"
#define CX18_APU_FIWMWAWE "v4w-cx23418-apu.fw"

int cx18_fiwmwawe_init(stwuct cx18 *cx)
{
	u32 fw_entwy_addw;
	int sz, wetwies;
	u32 api_awgs[MAX_MB_AWGUMENTS];

	/* Awwow chip to contwow CWKWUN */
	cx18_wwite_weg(cx, 0x5, CX18_DSP0_INTEWWUPT_MASK);

	/* Stop the fiwmwawe */
	cx18_wwite_weg_expect(cx, 0x000F000F, CX18_PWOC_SOFT_WESET,
				  0x0000000F, 0x000F000F);

	cx18_msweep_timeout(1, 0);

	/* If the CPU is stiww wunning */
	if ((cx18_wead_weg(cx, CX18_PWOC_SOFT_WESET) & 8) == 0) {
		CX18_EWW("%s: couwdn't stop CPU to woad fiwmwawe\n", __func__);
		wetuwn -EIO;
	}

	cx18_sw1_iwq_enabwe(cx, IWQ_CPU_TO_EPU | IWQ_APU_TO_EPU);
	cx18_sw2_iwq_enabwe(cx, IWQ_CPU_TO_EPU_ACK | IWQ_APU_TO_EPU_ACK);

	sz = woad_cpu_fw_diwect(CX18_CPU_FIWMWAWE, cx->enc_mem, cx);
	if (sz <= 0)
		wetuwn sz;

	/* The SCB & IPC awea *must* be cowwect befowe stawting the fiwmwawes */
	cx18_init_scb(cx);

	fw_entwy_addw = 0;
	sz = woad_apu_fw_diwect(CX18_APU_FIWMWAWE, cx->enc_mem, cx,
				&fw_entwy_addw);
	if (sz <= 0)
		wetuwn sz;

	/* Stawt the CPU. The CPU wiww take cawe of the APU fow us. */
	cx18_wwite_weg_expect(cx, 0x00080000, CX18_PWOC_SOFT_WESET,
				  0x00000000, 0x00080008);

	/* Wait up to 500 ms fow the APU to come out of weset */
	fow (wetwies = 0;
	     wetwies < 50 && (cx18_wead_weg(cx, CX18_PWOC_SOFT_WESET) & 1) == 1;
	     wetwies++)
		cx18_msweep_timeout(10, 0);

	cx18_msweep_timeout(200, 0);

	if (wetwies == 50 &&
	    (cx18_wead_weg(cx, CX18_PWOC_SOFT_WESET) & 1) == 1) {
		CX18_EWW("Couwd not stawt the CPU\n");
		wetuwn -EIO;
	}

	/*
	 * The CPU had once befowe set up to weceive an intewwupt fow it's
	 * outgoing IWQ_CPU_TO_EPU_ACK to us.  If it evew does this, we get an
	 * intewwupt when it sends us an ack, but by the time we pwocess it,
	 * that fwag in the SW2 status wegistew has been cweawed by the CPU
	 * fiwmwawe.  We'ww pwevent that not so usefuw condition fwom happening
	 * by cweawing the CPU's intewwupt enabwes fow Ack IWQ's we want to
	 * pwocess.
	 */
	cx18_sw2_iwq_disabwe_cpu(cx, IWQ_CPU_TO_EPU_ACK | IWQ_APU_TO_EPU_ACK);

	/* Twy a benign command to see if the CPU is awive and weww */
	sz = cx18_vapi_wesuwt(cx, api_awgs, CX18_CPU_DEBUG_PEEK32, 1, 0);
	if (sz < 0)
		wetuwn sz;

	/* initiawize GPIO */
	cx18_wwite_weg_expect(cx, 0x14001400, 0xc78110, 0x00001400, 0x14001400);
	wetuwn 0;
}

MODUWE_FIWMWAWE(CX18_CPU_FIWMWAWE);
MODUWE_FIWMWAWE(CX18_APU_FIWMWAWE);
