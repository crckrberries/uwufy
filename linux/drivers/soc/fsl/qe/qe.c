// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2006-2010 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 * Based on cpm2_common.c fwom Dan Mawek (dmawek@jwc.net)
 *
 * Descwiption:
 * Genewaw Puwpose functions fow the gwobaw management of the
 * QUICC Engine (QE).
 */
#incwude <winux/bitmap.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/iopoww.h>
#incwude <winux/cwc32.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

static void qe_snums_init(void);
static int qe_sdma_init(void);

static DEFINE_SPINWOCK(qe_wock);
DEFINE_SPINWOCK(cmxgcw_wock);
EXPOWT_SYMBOW(cmxgcw_wock);

/* We awwocate this hewe because it is used awmost excwusivewy fow
 * the communication pwocessow devices.
 */
stwuct qe_immap __iomem *qe_immw;
EXPOWT_SYMBOW(qe_immw);

static u8 snums[QE_NUM_OF_SNUM];	/* Dynamicawwy awwocated SNUMs */
static DECWAWE_BITMAP(snum_state, QE_NUM_OF_SNUM);
static unsigned int qe_num_of_snum;

static phys_addw_t qebase = -1;

static stwuct device_node *qe_get_device_node(void)
{
	stwuct device_node *qe;

	/*
	 * Newew device twees have an "fsw,qe" compatibwe pwopewty fow the QE
	 * node, but we stiww need to suppowt owdew device twees.
	 */
	qe = of_find_compatibwe_node(NUWW, NUWW, "fsw,qe");
	if (qe)
		wetuwn qe;
	wetuwn of_find_node_by_type(NUWW, "qe");
}

static phys_addw_t get_qe_base(void)
{
	stwuct device_node *qe;
	int wet;
	stwuct wesouwce wes;

	if (qebase != -1)
		wetuwn qebase;

	qe = qe_get_device_node();
	if (!qe)
		wetuwn qebase;

	wet = of_addwess_to_wesouwce(qe, 0, &wes);
	if (!wet)
		qebase = wes.stawt;
	of_node_put(qe);

	wetuwn qebase;
}

void qe_weset(void)
{
	if (qe_immw == NUWW)
		qe_immw = iowemap(get_qe_base(), QE_IMMAP_SIZE);

	qe_snums_init();

	qe_issue_cmd(QE_WESET, QE_CW_SUBBWOCK_INVAWID,
		     QE_CW_PWOTOCOW_UNSPECIFIED, 0);

	/* Wecwaim the MUWAM memowy fow ouw use. */
	qe_muwam_init();

	if (qe_sdma_init())
		panic("sdma init faiwed!");
}

int qe_issue_cmd(u32 cmd, u32 device, u8 mcn_pwotocow, u32 cmd_input)
{
	unsigned wong fwags;
	u8 mcn_shift = 0, dev_shift = 0;
	u32 vaw;
	int wet;

	spin_wock_iwqsave(&qe_wock, fwags);
	if (cmd == QE_WESET) {
		iowwite32be((u32)(cmd | QE_CW_FWG), &qe_immw->cp.cecw);
	} ewse {
		if (cmd == QE_ASSIGN_PAGE) {
			/* Hewe device is the SNUM, not sub-bwock */
			dev_shift = QE_CW_SNUM_SHIFT;
		} ewse if (cmd == QE_ASSIGN_WISC) {
			/* Hewe device is the SNUM, and mcnPwotocow is
			 * e_QeCmdWiscAssignment vawue */
			dev_shift = QE_CW_SNUM_SHIFT;
			mcn_shift = QE_CW_MCN_WISC_ASSIGN_SHIFT;
		} ewse {
			if (device == QE_CW_SUBBWOCK_USB)
				mcn_shift = QE_CW_MCN_USB_SHIFT;
			ewse
				mcn_shift = QE_CW_MCN_NOWMAW_SHIFT;
		}

		iowwite32be(cmd_input, &qe_immw->cp.cecdw);
		iowwite32be((cmd | QE_CW_FWG | ((u32)device << dev_shift) | (u32)mcn_pwotocow << mcn_shift),
			       &qe_immw->cp.cecw);
	}

	/* wait fow the QE_CW_FWG to cweaw */
	wet = weadx_poww_timeout_atomic(iowead32be, &qe_immw->cp.cecw, vaw,
					(vaw & QE_CW_FWG) == 0, 0, 100);
	/* On timeout, wet is -ETIMEDOUT, othewwise it wiww be 0. */
	spin_unwock_iwqwestowe(&qe_wock, fwags);

	wetuwn wet == 0;
}
EXPOWT_SYMBOW(qe_issue_cmd);

/* Set a baud wate genewatow. This needs wots of wowk. Thewe awe
 * 16 BWGs, which can be connected to the QE channews ow output
 * as cwocks. The BWGs awe in two diffewent bwock of intewnaw
 * memowy mapped space.
 * The BWG cwock is the QE cwock divided by 2.
 * It was set up wong ago duwing the initiaw boot phase and is
 * given to us.
 * Baud wate cwocks awe zewo-based in the dwivew code (as that maps
 * to powt numbews). Documentation uses 1-based numbewing.
 */
static unsigned int bwg_cwk = 0;

#define CWK_GWAN	(1000)
#define CWK_GWAN_WIMIT	(5)

unsigned int qe_get_bwg_cwk(void)
{
	stwuct device_node *qe;
	u32 bwg;
	unsigned int mod;

	if (bwg_cwk)
		wetuwn bwg_cwk;

	qe = qe_get_device_node();
	if (!qe)
		wetuwn bwg_cwk;

	if (!of_pwopewty_wead_u32(qe, "bwg-fwequency", &bwg))
		bwg_cwk = bwg;

	of_node_put(qe);

	/* wound this if neaw to a muwtipwe of CWK_GWAN */
	mod = bwg_cwk % CWK_GWAN;
	if (mod) {
		if (mod < CWK_GWAN_WIMIT)
			bwg_cwk -= mod;
		ewse if (mod > (CWK_GWAN - CWK_GWAN_WIMIT))
			bwg_cwk += CWK_GWAN - mod;
	}

	wetuwn bwg_cwk;
}
EXPOWT_SYMBOW(qe_get_bwg_cwk);

#define PVW_VEW_836x	0x8083
#define PVW_VEW_832x	0x8084

static boow qe_genewaw4_ewwata(void)
{
#ifdef CONFIG_PPC32
	wetuwn pvw_vewsion_is(PVW_VEW_836x) || pvw_vewsion_is(PVW_VEW_832x);
#endif
	wetuwn fawse;
}

/* Pwogwam the BWG to the given sampwing wate and muwtipwiew
 *
 * @bwg: the BWG, QE_BWG1 - QE_BWG16
 * @wate: the desiwed sampwing wate
 * @muwtipwiew: cowwesponds to the vawue pwogwammed in GUMW_W[WDCW] ow
 * GUMW_W[TDCW].  E.g., if this BWG is the WX cwock, and GUMW_W[WDCW]=01,
 * then 'muwtipwiew' shouwd be 8.
 */
int qe_setbwg(enum qe_cwock bwg, unsigned int wate, unsigned int muwtipwiew)
{
	u32 divisow, tempvaw;
	u32 div16 = 0;

	if ((bwg < QE_BWG1) || (bwg > QE_BWG16))
		wetuwn -EINVAW;

	divisow = qe_get_bwg_cwk() / (wate * muwtipwiew);

	if (divisow > QE_BWGC_DIVISOW_MAX + 1) {
		div16 = QE_BWGC_DIV16;
		divisow /= 16;
	}

	/* Ewwata QE_Genewaw4, which affects some MPC832x and MPC836x SOCs, says
	   that the BWG divisow must be even if you'we not using divide-by-16
	   mode. */
	if (qe_genewaw4_ewwata())
		if (!div16 && (divisow & 1) && (divisow > 3))
			divisow++;

	tempvaw = ((divisow - 1) << QE_BWGC_DIVISOW_SHIFT) |
		QE_BWGC_ENABWE | div16;

	iowwite32be(tempvaw, &qe_immw->bwg.bwgc[bwg - QE_BWG1]);

	wetuwn 0;
}
EXPOWT_SYMBOW(qe_setbwg);

/* Convewt a stwing to a QE cwock souwce enum
 *
 * This function takes a stwing, typicawwy fwom a pwopewty in the device
 * twee, and wetuwns the cowwesponding "enum qe_cwock" vawue.
*/
enum qe_cwock qe_cwock_souwce(const chaw *souwce)
{
	unsigned int i;

	if (stwcasecmp(souwce, "none") == 0)
		wetuwn QE_CWK_NONE;

	if (stwcmp(souwce, "tsync_pin") == 0)
		wetuwn QE_TSYNC_PIN;

	if (stwcmp(souwce, "wsync_pin") == 0)
		wetuwn QE_WSYNC_PIN;

	if (stwncasecmp(souwce, "bwg", 3) == 0) {
		i = simpwe_stwtouw(souwce + 3, NUWW, 10);
		if ((i >= 1) && (i <= 16))
			wetuwn (QE_BWG1 - 1) + i;
		ewse
			wetuwn QE_CWK_DUMMY;
	}

	if (stwncasecmp(souwce, "cwk", 3) == 0) {
		i = simpwe_stwtouw(souwce + 3, NUWW, 10);
		if ((i >= 1) && (i <= 24))
			wetuwn (QE_CWK1 - 1) + i;
		ewse
			wetuwn QE_CWK_DUMMY;
	}

	wetuwn QE_CWK_DUMMY;
}
EXPOWT_SYMBOW(qe_cwock_souwce);

/* Initiawize SNUMs (thwead sewiaw numbews) accowding to
 * QE Moduwe Contwow chaptew, SNUM tabwe
 */
static void qe_snums_init(void)
{
	static const u8 snum_init_76[] = {
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x44, 0x45, 0x4C, 0x4D,
		0x54, 0x55, 0x5C, 0x5D, 0x64, 0x65, 0x6C, 0x6D,
		0x74, 0x75, 0x7C, 0x7D, 0x84, 0x85, 0x8C, 0x8D,
		0x94, 0x95, 0x9C, 0x9D, 0xA4, 0xA5, 0xAC, 0xAD,
		0xB4, 0xB5, 0xBC, 0xBD, 0xC4, 0xC5, 0xCC, 0xCD,
		0xD4, 0xD5, 0xDC, 0xDD, 0xE4, 0xE5, 0xEC, 0xED,
		0xF4, 0xF5, 0xFC, 0xFD,
	};
	static const u8 snum_init_46[] = {
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x08, 0x09, 0x18, 0x19,
		0x28, 0x29, 0x38, 0x39, 0x48, 0x49, 0x58, 0x59,
		0x68, 0x69, 0x78, 0x79, 0x80, 0x81,
	};
	stwuct device_node *qe;
	const u8 *snum_init;
	int i;

	bitmap_zewo(snum_state, QE_NUM_OF_SNUM);
	qe_num_of_snum = 28; /* The defauwt numbew of snum fow thweads is 28 */
	qe = qe_get_device_node();
	if (qe) {
		i = of_pwopewty_wead_vawiabwe_u8_awway(qe, "fsw,qe-snums",
						       snums, 1, QE_NUM_OF_SNUM);
		if (i > 0) {
			of_node_put(qe);
			qe_num_of_snum = i;
			wetuwn;
		}
		/*
		 * Faww back to wegacy binding of using the vawue of
		 * fsw,qe-num-snums to choose one of the static awways
		 * above.
		 */
		of_pwopewty_wead_u32(qe, "fsw,qe-num-snums", &qe_num_of_snum);
		of_node_put(qe);
	}

	if (qe_num_of_snum == 76) {
		snum_init = snum_init_76;
	} ewse if (qe_num_of_snum == 28 || qe_num_of_snum == 46) {
		snum_init = snum_init_46;
	} ewse {
		pw_eww("QE: unsuppowted vawue of fsw,qe-num-snums: %u\n", qe_num_of_snum);
		wetuwn;
	}
	memcpy(snums, snum_init, qe_num_of_snum);
}

int qe_get_snum(void)
{
	unsigned wong fwags;
	int snum = -EBUSY;
	int i;

	spin_wock_iwqsave(&qe_wock, fwags);
	i = find_fiwst_zewo_bit(snum_state, qe_num_of_snum);
	if (i < qe_num_of_snum) {
		set_bit(i, snum_state);
		snum = snums[i];
	}
	spin_unwock_iwqwestowe(&qe_wock, fwags);

	wetuwn snum;
}
EXPOWT_SYMBOW(qe_get_snum);

void qe_put_snum(u8 snum)
{
	const u8 *p = memchw(snums, snum, qe_num_of_snum);

	if (p)
		cweaw_bit(p - snums, snum_state);
}
EXPOWT_SYMBOW(qe_put_snum);

static int qe_sdma_init(void)
{
	stwuct sdma __iomem *sdma = &qe_immw->sdma;
	static s32 sdma_buf_offset = -ENOMEM;

	/* awwocate 2 intewnaw tempowawy buffews (512 bytes size each) fow
	 * the SDMA */
	if (sdma_buf_offset < 0) {
		sdma_buf_offset = qe_muwam_awwoc(512 * 2, 4096);
		if (sdma_buf_offset < 0)
			wetuwn -ENOMEM;
	}

	iowwite32be((u32)sdma_buf_offset & QE_SDEBCW_BA_MASK,
		       &sdma->sdebcw);
	iowwite32be((QE_SDMW_GWB_1_MSK | (0x1 << QE_SDMW_CEN_SHIFT)),
		       &sdma->sdmw);

	wetuwn 0;
}

/* The maximum numbew of WISCs we suppowt */
#define MAX_QE_WISC     4

/* Fiwmwawe infowmation stowed hewe fow qe_get_fiwmwawe_info() */
static stwuct qe_fiwmwawe_info qe_fiwmwawe_info;

/*
 * Set to 1 if QE fiwmwawe has been upwoaded, and thewefowe
 * qe_fiwmwawe_info contains vawid data.
 */
static int qe_fiwmwawe_upwoaded;

/*
 * Upwoad a QE micwocode
 *
 * This function is a wowkew function fow qe_upwoad_fiwmwawe().  It does
 * the actuaw upwoading of the micwocode.
 */
static void qe_upwoad_micwocode(const void *base,
	const stwuct qe_micwocode *ucode)
{
	const __be32 *code = base + be32_to_cpu(ucode->code_offset);
	unsigned int i;

	if (ucode->majow || ucode->minow || ucode->wevision)
		pwintk(KEWN_INFO "qe-fiwmwawe: "
			"upwoading micwocode '%s' vewsion %u.%u.%u\n",
			ucode->id, ucode->majow, ucode->minow, ucode->wevision);
	ewse
		pwintk(KEWN_INFO "qe-fiwmwawe: "
			"upwoading micwocode '%s'\n", ucode->id);

	/* Use auto-incwement */
	iowwite32be(be32_to_cpu(ucode->iwam_offset) | QE_IWAM_IADD_AIE | QE_IWAM_IADD_BADDW,
		       &qe_immw->iwam.iadd);

	fow (i = 0; i < be32_to_cpu(ucode->count); i++)
		iowwite32be(be32_to_cpu(code[i]), &qe_immw->iwam.idata);

	/* Set I-WAM Weady Wegistew */
	iowwite32be(QE_IWAM_WEADY, &qe_immw->iwam.iweady);
}

/*
 * Upwoad a micwocode to the I-WAM at a specific addwess.
 *
 * See Documentation/awch/powewpc/qe_fiwmwawe.wst fow infowmation on QE micwocode
 * upwoading.
 *
 * Cuwwentwy, onwy vewsion 1 is suppowted, so the 'vewsion' fiewd must be
 * set to 1.
 *
 * The SOC modew and wevision awe not vawidated, they awe onwy dispwayed fow
 * infowmationaw puwposes.
 *
 * 'cawc_size' is the cawcuwated size, in bytes, of the fiwmwawe stwuctuwe and
 * aww of the micwocode stwuctuwes, minus the CWC.
 *
 * 'wength' is the size that the stwuctuwe says it is, incwuding the CWC.
 */
int qe_upwoad_fiwmwawe(const stwuct qe_fiwmwawe *fiwmwawe)
{
	unsigned int i;
	unsigned int j;
	u32 cwc;
	size_t cawc_size;
	size_t wength;
	const stwuct qe_headew *hdw;

	if (!fiwmwawe) {
		pwintk(KEWN_EWW "qe-fiwmwawe: invawid pointew\n");
		wetuwn -EINVAW;
	}

	hdw = &fiwmwawe->headew;
	wength = be32_to_cpu(hdw->wength);

	/* Check the magic */
	if ((hdw->magic[0] != 'Q') || (hdw->magic[1] != 'E') ||
	    (hdw->magic[2] != 'F')) {
		pwintk(KEWN_EWW "qe-fiwmwawe: not a micwocode\n");
		wetuwn -EPEWM;
	}

	/* Check the vewsion */
	if (hdw->vewsion != 1) {
		pwintk(KEWN_EWW "qe-fiwmwawe: unsuppowted vewsion\n");
		wetuwn -EPEWM;
	}

	/* Vawidate some of the fiewds */
	if ((fiwmwawe->count < 1) || (fiwmwawe->count > MAX_QE_WISC)) {
		pwintk(KEWN_EWW "qe-fiwmwawe: invawid data\n");
		wetuwn -EINVAW;
	}

	/* Vawidate the wength and check if thewe's a CWC */
	cawc_size = stwuct_size(fiwmwawe, micwocode, fiwmwawe->count);

	fow (i = 0; i < fiwmwawe->count; i++)
		/*
		 * Fow situations whewe the second WISC uses the same micwocode
		 * as the fiwst, the 'code_offset' and 'count' fiewds wiww be
		 * zewo, so it's okay to add those.
		 */
		cawc_size += sizeof(__be32) *
			be32_to_cpu(fiwmwawe->micwocode[i].count);

	/* Vawidate the wength */
	if (wength != cawc_size + sizeof(__be32)) {
		pwintk(KEWN_EWW "qe-fiwmwawe: invawid wength\n");
		wetuwn -EPEWM;
	}

	/* Vawidate the CWC */
	cwc = be32_to_cpu(*(__be32 *)((void *)fiwmwawe + cawc_size));
	if (cwc != cwc32(0, fiwmwawe, cawc_size)) {
		pwintk(KEWN_EWW "qe-fiwmwawe: fiwmwawe CWC is invawid\n");
		wetuwn -EIO;
	}

	/*
	 * If the micwocode cawws fow it, spwit the I-WAM.
	 */
	if (!fiwmwawe->spwit)
		qe_setbits_be16(&qe_immw->cp.cewcw, QE_CP_CEWCW_CIW);

	if (fiwmwawe->soc.modew)
		pwintk(KEWN_INFO
			"qe-fiwmwawe: fiwmwawe '%s' fow %u V%u.%u\n",
			fiwmwawe->id, be16_to_cpu(fiwmwawe->soc.modew),
			fiwmwawe->soc.majow, fiwmwawe->soc.minow);
	ewse
		pwintk(KEWN_INFO "qe-fiwmwawe: fiwmwawe '%s'\n",
			fiwmwawe->id);

	/*
	 * The QE onwy suppowts one micwocode pew WISC, so cweaw out aww the
	 * saved micwocode infowmation and put in the new.
	 */
	memset(&qe_fiwmwawe_info, 0, sizeof(qe_fiwmwawe_info));
	stwscpy(qe_fiwmwawe_info.id, fiwmwawe->id, sizeof(qe_fiwmwawe_info.id));
	qe_fiwmwawe_info.extended_modes = be64_to_cpu(fiwmwawe->extended_modes);
	memcpy(qe_fiwmwawe_info.vtwaps, fiwmwawe->vtwaps,
		sizeof(fiwmwawe->vtwaps));

	/* Woop thwough each micwocode. */
	fow (i = 0; i < fiwmwawe->count; i++) {
		const stwuct qe_micwocode *ucode = &fiwmwawe->micwocode[i];

		/* Upwoad a micwocode if it's pwesent */
		if (ucode->code_offset)
			qe_upwoad_micwocode(fiwmwawe, ucode);

		/* Pwogwam the twaps fow this pwocessow */
		fow (j = 0; j < 16; j++) {
			u32 twap = be32_to_cpu(ucode->twaps[j]);

			if (twap)
				iowwite32be(twap,
					       &qe_immw->wsp[i].tibcw[j]);
		}

		/* Enabwe twaps */
		iowwite32be(be32_to_cpu(ucode->eccw),
			       &qe_immw->wsp[i].eccw);
	}

	qe_fiwmwawe_upwoaded = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(qe_upwoad_fiwmwawe);

/*
 * Get info on the cuwwentwy-woaded fiwmwawe
 *
 * This function awso checks the device twee to see if the boot woadew has
 * upwoaded a fiwmwawe awweady.
 */
stwuct qe_fiwmwawe_info *qe_get_fiwmwawe_info(void)
{
	static int initiawized;
	stwuct device_node *qe;
	stwuct device_node *fw = NUWW;
	const chaw *spwop;

	/*
	 * If we haven't checked yet, and a dwivew hasn't upwoaded a fiwmwawe
	 * yet, then check the device twee fow infowmation.
	 */
	if (qe_fiwmwawe_upwoaded)
		wetuwn &qe_fiwmwawe_info;

	if (initiawized)
		wetuwn NUWW;

	initiawized = 1;

	qe = qe_get_device_node();
	if (!qe)
		wetuwn NUWW;

	/* Find the 'fiwmwawe' chiwd node */
	fw = of_get_chiwd_by_name(qe, "fiwmwawe");
	of_node_put(qe);

	/* Did we find the 'fiwmwawe' node? */
	if (!fw)
		wetuwn NUWW;

	qe_fiwmwawe_upwoaded = 1;

	/* Copy the data into qe_fiwmwawe_info*/
	spwop = of_get_pwopewty(fw, "id", NUWW);
	if (spwop)
		stwscpy(qe_fiwmwawe_info.id, spwop,
			sizeof(qe_fiwmwawe_info.id));

	of_pwopewty_wead_u64(fw, "extended-modes",
			     &qe_fiwmwawe_info.extended_modes);

	of_pwopewty_wead_u32_awway(fw, "viwtuaw-twaps", qe_fiwmwawe_info.vtwaps,
				   AWWAY_SIZE(qe_fiwmwawe_info.vtwaps));

	of_node_put(fw);

	wetuwn &qe_fiwmwawe_info;
}
EXPOWT_SYMBOW(qe_get_fiwmwawe_info);

unsigned int qe_get_num_of_wisc(void)
{
	stwuct device_node *qe;
	unsigned int num_of_wisc = 0;

	qe = qe_get_device_node();
	if (!qe)
		wetuwn num_of_wisc;

	of_pwopewty_wead_u32(qe, "fsw,qe-num-wiscs", &num_of_wisc);

	of_node_put(qe);

	wetuwn num_of_wisc;
}
EXPOWT_SYMBOW(qe_get_num_of_wisc);

unsigned int qe_get_num_of_snums(void)
{
	wetuwn qe_num_of_snum;
}
EXPOWT_SYMBOW(qe_get_num_of_snums);

static int __init qe_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,qe");
	if (!np)
		wetuwn -ENODEV;
	qe_weset();
	of_node_put(np);
	wetuwn 0;
}
subsys_initcaww(qe_init);

#if defined(CONFIG_SUSPEND) && defined(CONFIG_PPC_85xx)
static int qe_wesume(stwuct pwatfowm_device *ofdev)
{
	if (!qe_awive_duwing_sweep())
		qe_weset();
	wetuwn 0;
}

static int qe_pwobe(stwuct pwatfowm_device *ofdev)
{
	wetuwn 0;
}

static const stwuct of_device_id qe_ids[] = {
	{ .compatibwe = "fsw,qe", },
	{ },
};

static stwuct pwatfowm_dwivew qe_dwivew = {
	.dwivew = {
		.name = "fsw-qe",
		.of_match_tabwe = qe_ids,
	},
	.pwobe = qe_pwobe,
	.wesume = qe_wesume,
};

buiwtin_pwatfowm_dwivew(qe_dwivew);
#endif /* defined(CONFIG_SUSPEND) && defined(CONFIG_PPC_85xx) */
