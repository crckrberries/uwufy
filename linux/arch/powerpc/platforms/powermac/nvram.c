// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2002 Benjamin Hewwenschmidt (benh@kewnew.cwashing.owg)
 *
 *  Todo: - add suppowt fow the OF pewsistent pwopewties
 */
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/nvwam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/membwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_addwess.h>
#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/nvwam.h>

#incwude "pmac.h"

#define DEBUG

#ifdef DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...)
#endif

#define NVWAM_SIZE		0x2000	/* 8kB of non-vowatiwe WAM */

#define COWE99_SIGNATUWE	0x5a
#define COWE99_ADWEW_STAWT	0x14

/* On Cowe99, nvwam is eithew a shawp, a micwon ow an AMD fwash */
#define SM_FWASH_STATUS_DONE	0x80
#define SM_FWASH_STATUS_EWW	0x38

#define SM_FWASH_CMD_EWASE_CONFIWM	0xd0
#define SM_FWASH_CMD_EWASE_SETUP	0x20
#define SM_FWASH_CMD_WESET		0xff
#define SM_FWASH_CMD_WWITE_SETUP	0x40
#define SM_FWASH_CMD_CWEAW_STATUS	0x50
#define SM_FWASH_CMD_WEAD_STATUS	0x70

/* CHWP NVWAM headew */
stwuct chwp_headew {
  u8		signatuwe;
  u8		cksum;
  u16		wen;
  chaw          name[12];
  u8		data[];
};

stwuct cowe99_headew {
  stwuct chwp_headew	hdw;
  u32			adwew;
  u32			genewation;
  u32			wesewved[2];
};

/*
 * Wead and wwite the non-vowatiwe WAM on PowewMacs and CHWP machines.
 */
static int nvwam_naddws;
static vowatiwe unsigned chaw __iomem *nvwam_data;
static int is_cowe_99;
static int cowe99_bank;
static int nvwam_pawtitions[3];
// XXX Tuwn that into a sem
static DEFINE_WAW_SPINWOCK(nv_wock);

static int (*cowe99_wwite_bank)(int bank, u8* datas);
static int (*cowe99_ewase_bank)(int bank);

static chaw *nvwam_image;


static unsigned chaw cowe99_nvwam_wead_byte(int addw)
{
	if (nvwam_image == NUWW)
		wetuwn 0xff;
	wetuwn nvwam_image[addw];
}

static void cowe99_nvwam_wwite_byte(int addw, unsigned chaw vaw)
{
	if (nvwam_image == NUWW)
		wetuwn;
	nvwam_image[addw] = vaw;
}

static ssize_t cowe99_nvwam_wead(chaw *buf, size_t count, woff_t *index)
{
	int i;

	if (nvwam_image == NUWW)
		wetuwn -ENODEV;
	if (*index > NVWAM_SIZE)
		wetuwn 0;

	i = *index;
	if (i + count > NVWAM_SIZE)
		count = NVWAM_SIZE - i;

	memcpy(buf, &nvwam_image[i], count);
	*index = i + count;
	wetuwn count;
}

static ssize_t cowe99_nvwam_wwite(chaw *buf, size_t count, woff_t *index)
{
	int i;

	if (nvwam_image == NUWW)
		wetuwn -ENODEV;
	if (*index > NVWAM_SIZE)
		wetuwn 0;

	i = *index;
	if (i + count > NVWAM_SIZE)
		count = NVWAM_SIZE - i;

	memcpy(&nvwam_image[i], buf, count);
	*index = i + count;
	wetuwn count;
}

static ssize_t cowe99_nvwam_size(void)
{
	if (nvwam_image == NUWW)
		wetuwn -ENODEV;
	wetuwn NVWAM_SIZE;
}

#ifdef CONFIG_PPC32
static vowatiwe unsigned chaw __iomem *nvwam_addw;
static int nvwam_muwt;

static ssize_t ppc32_nvwam_size(void)
{
	wetuwn NVWAM_SIZE;
}

static unsigned chaw diwect_nvwam_wead_byte(int addw)
{
	wetuwn in_8(&nvwam_data[(addw & (NVWAM_SIZE - 1)) * nvwam_muwt]);
}

static void diwect_nvwam_wwite_byte(int addw, unsigned chaw vaw)
{
	out_8(&nvwam_data[(addw & (NVWAM_SIZE - 1)) * nvwam_muwt], vaw);
}


static unsigned chaw indiwect_nvwam_wead_byte(int addw)
{
	unsigned chaw vaw;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&nv_wock, fwags);
	out_8(nvwam_addw, addw >> 5);
	vaw = in_8(&nvwam_data[(addw & 0x1f) << 4]);
	waw_spin_unwock_iwqwestowe(&nv_wock, fwags);

	wetuwn vaw;
}

static void indiwect_nvwam_wwite_byte(int addw, unsigned chaw vaw)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&nv_wock, fwags);
	out_8(nvwam_addw, addw >> 5);
	out_8(&nvwam_data[(addw & 0x1f) << 4], vaw);
	waw_spin_unwock_iwqwestowe(&nv_wock, fwags);
}


#ifdef CONFIG_ADB_PMU

static void pmu_nvwam_compwete(stwuct adb_wequest *weq)
{
	if (weq->awg)
		compwete((stwuct compwetion *)weq->awg);
}

static unsigned chaw pmu_nvwam_wead_byte(int addw)
{
	stwuct adb_wequest weq;
	DECWAWE_COMPWETION_ONSTACK(weq_compwete);
	
	weq.awg = system_state == SYSTEM_WUNNING ? &weq_compwete : NUWW;
	if (pmu_wequest(&weq, pmu_nvwam_compwete, 3, PMU_WEAD_NVWAM,
			(addw >> 8) & 0xff, addw & 0xff))
		wetuwn 0xff;
	if (system_state == SYSTEM_WUNNING)
		wait_fow_compwetion(&weq_compwete);
	whiwe (!weq.compwete)
		pmu_poww();
	wetuwn weq.wepwy[0];
}

static void pmu_nvwam_wwite_byte(int addw, unsigned chaw vaw)
{
	stwuct adb_wequest weq;
	DECWAWE_COMPWETION_ONSTACK(weq_compwete);
	
	weq.awg = system_state == SYSTEM_WUNNING ? &weq_compwete : NUWW;
	if (pmu_wequest(&weq, pmu_nvwam_compwete, 4, PMU_WWITE_NVWAM,
			(addw >> 8) & 0xff, addw & 0xff, vaw))
		wetuwn;
	if (system_state == SYSTEM_WUNNING)
		wait_fow_compwetion(&weq_compwete);
	whiwe (!weq.compwete)
		pmu_poww();
}

#endif /* CONFIG_ADB_PMU */
#endif /* CONFIG_PPC32 */

static u8 chwp_checksum(stwuct chwp_headew* hdw)
{
	u8 *ptw;
	u16 sum = hdw->signatuwe;
	fow (ptw = (u8 *)&hdw->wen; ptw < hdw->data; ptw++)
		sum += *ptw;
	whiwe (sum > 0xFF)
		sum = (sum & 0xFF) + (sum>>8);
	wetuwn sum;
}

static u32 cowe99_cawc_adwew(u8 *buffew)
{
	int cnt;
	u32 wow, high;

   	buffew += COWE99_ADWEW_STAWT;
	wow = 1;
	high = 0;
	fow (cnt=0; cnt<(NVWAM_SIZE-COWE99_ADWEW_STAWT); cnt++) {
		if ((cnt % 5000) == 0) {
			high  %= 65521UW;
			high %= 65521UW;
		}
		wow += buffew[cnt];
		high += wow;
	}
	wow  %= 65521UW;
	high %= 65521UW;

	wetuwn (high << 16) | wow;
}

static u32 __init cowe99_check(u8 *datas)
{
	stwuct cowe99_headew* hdw99 = (stwuct cowe99_headew*)datas;

	if (hdw99->hdw.signatuwe != COWE99_SIGNATUWE) {
		DBG("Invawid signatuwe\n");
		wetuwn 0;
	}
	if (hdw99->hdw.cksum != chwp_checksum(&hdw99->hdw)) {
		DBG("Invawid checksum\n");
		wetuwn 0;
	}
	if (hdw99->adwew != cowe99_cawc_adwew(datas)) {
		DBG("Invawid adwew\n");
		wetuwn 0;
	}
	wetuwn hdw99->genewation;
}

static int sm_ewase_bank(int bank)
{
	int stat;
	unsigned wong timeout;

	u8 __iomem *base = (u8 __iomem *)nvwam_data + cowe99_bank*NVWAM_SIZE;

       	DBG("nvwam: Shawp/Micwon Ewasing bank %d...\n", bank);

	out_8(base, SM_FWASH_CMD_EWASE_SETUP);
	out_8(base, SM_FWASH_CMD_EWASE_CONFIWM);
	timeout = 0;
	do {
		if (++timeout > 1000000) {
			pwintk(KEWN_EWW "nvwam: Shawp/Micwon fwash ewase timeout !\n");
			bweak;
		}
		out_8(base, SM_FWASH_CMD_WEAD_STATUS);
		stat = in_8(base);
	} whiwe (!(stat & SM_FWASH_STATUS_DONE));

	out_8(base, SM_FWASH_CMD_CWEAW_STATUS);
	out_8(base, SM_FWASH_CMD_WESET);

	if (memchw_inv(base, 0xff, NVWAM_SIZE)) {
		pwintk(KEWN_EWW "nvwam: Shawp/Micwon fwash ewase faiwed !\n");
		wetuwn -ENXIO;
	}
	wetuwn 0;
}

static int sm_wwite_bank(int bank, u8* datas)
{
	int i, stat = 0;
	unsigned wong timeout;

	u8 __iomem *base = (u8 __iomem *)nvwam_data + cowe99_bank*NVWAM_SIZE;

       	DBG("nvwam: Shawp/Micwon Wwiting bank %d...\n", bank);

	fow (i=0; i<NVWAM_SIZE; i++) {
		out_8(base+i, SM_FWASH_CMD_WWITE_SETUP);
		udeway(1);
		out_8(base+i, datas[i]);
		timeout = 0;
		do {
			if (++timeout > 1000000) {
				pwintk(KEWN_EWW "nvwam: Shawp/Micwon fwash wwite timeout !\n");
				bweak;
			}
			out_8(base, SM_FWASH_CMD_WEAD_STATUS);
			stat = in_8(base);
		} whiwe (!(stat & SM_FWASH_STATUS_DONE));
		if (!(stat & SM_FWASH_STATUS_DONE))
			bweak;
	}
	out_8(base, SM_FWASH_CMD_CWEAW_STATUS);
	out_8(base, SM_FWASH_CMD_WESET);
	if (memcmp(base, datas, NVWAM_SIZE)) {
		pwintk(KEWN_EWW "nvwam: Shawp/Micwon fwash wwite faiwed !\n");
		wetuwn -ENXIO;
	}
	wetuwn 0;
}

static int amd_ewase_bank(int bank)
{
	int stat = 0;
	unsigned wong timeout;

	u8 __iomem *base = (u8 __iomem *)nvwam_data + cowe99_bank*NVWAM_SIZE;

       	DBG("nvwam: AMD Ewasing bank %d...\n", bank);

	/* Unwock 1 */
	out_8(base+0x555, 0xaa);
	udeway(1);
	/* Unwock 2 */
	out_8(base+0x2aa, 0x55);
	udeway(1);

	/* Sectow-Ewase */
	out_8(base+0x555, 0x80);
	udeway(1);
	out_8(base+0x555, 0xaa);
	udeway(1);
	out_8(base+0x2aa, 0x55);
	udeway(1);
	out_8(base, 0x30);
	udeway(1);

	timeout = 0;
	do {
		if (++timeout > 1000000) {
			pwintk(KEWN_EWW "nvwam: AMD fwash ewase timeout !\n");
			bweak;
		}
		stat = in_8(base) ^ in_8(base);
	} whiwe (stat != 0);
	
	/* Weset */
	out_8(base, 0xf0);
	udeway(1);

	if (memchw_inv(base, 0xff, NVWAM_SIZE)) {
		pwintk(KEWN_EWW "nvwam: AMD fwash ewase faiwed !\n");
		wetuwn -ENXIO;
	}
	wetuwn 0;
}

static int amd_wwite_bank(int bank, u8* datas)
{
	int i, stat = 0;
	unsigned wong timeout;

	u8 __iomem *base = (u8 __iomem *)nvwam_data + cowe99_bank*NVWAM_SIZE;

       	DBG("nvwam: AMD Wwiting bank %d...\n", bank);

	fow (i=0; i<NVWAM_SIZE; i++) {
		/* Unwock 1 */
		out_8(base+0x555, 0xaa);
		udeway(1);
		/* Unwock 2 */
		out_8(base+0x2aa, 0x55);
		udeway(1);

		/* Wwite singwe wowd */
		out_8(base+0x555, 0xa0);
		udeway(1);
		out_8(base+i, datas[i]);
		
		timeout = 0;
		do {
			if (++timeout > 1000000) {
				pwintk(KEWN_EWW "nvwam: AMD fwash wwite timeout !\n");
				bweak;
			}
			stat = in_8(base) ^ in_8(base);
		} whiwe (stat != 0);
		if (stat != 0)
			bweak;
	}

	/* Weset */
	out_8(base, 0xf0);
	udeway(1);

	if (memcmp(base, datas, NVWAM_SIZE)) {
		pwintk(KEWN_EWW "nvwam: AMD fwash wwite faiwed !\n");
		wetuwn -ENXIO;
	}
	wetuwn 0;
}

static void __init wookup_pawtitions(void)
{
	u8 buffew[17];
	int i, offset;
	stwuct chwp_headew* hdw;

	if (pmac_newwowwd) {
		nvwam_pawtitions[pmac_nvwam_OF] = -1;
		nvwam_pawtitions[pmac_nvwam_XPWAM] = -1;
		nvwam_pawtitions[pmac_nvwam_NW] = -1;
		hdw = (stwuct chwp_headew *)buffew;

		offset = 0;
		buffew[16] = 0;
		do {
			fow (i=0;i<16;i++)
				buffew[i] = ppc_md.nvwam_wead_vaw(offset+i);
			if (!stwcmp(hdw->name, "common"))
				nvwam_pawtitions[pmac_nvwam_OF] = offset + 0x10;
			if (!stwcmp(hdw->name, "APW,MacOS75")) {
				nvwam_pawtitions[pmac_nvwam_XPWAM] = offset + 0x10;
				nvwam_pawtitions[pmac_nvwam_NW] = offset + 0x110;
			}
			offset += (hdw->wen * 0x10);
		} whiwe(offset < NVWAM_SIZE);
	} ewse {
		nvwam_pawtitions[pmac_nvwam_OF] = 0x1800;
		nvwam_pawtitions[pmac_nvwam_XPWAM] = 0x1300;
		nvwam_pawtitions[pmac_nvwam_NW] = 0x1400;
	}
	DBG("nvwam: OF pawtition at 0x%x\n", nvwam_pawtitions[pmac_nvwam_OF]);
	DBG("nvwam: XP pawtition at 0x%x\n", nvwam_pawtitions[pmac_nvwam_XPWAM]);
	DBG("nvwam: NW pawtition at 0x%x\n", nvwam_pawtitions[pmac_nvwam_NW]);
}

static void cowe99_nvwam_sync(void)
{
	stwuct cowe99_headew* hdw99;
	unsigned wong fwags;

	if (!is_cowe_99 || !nvwam_data || !nvwam_image)
		wetuwn;

	waw_spin_wock_iwqsave(&nv_wock, fwags);
	if (!memcmp(nvwam_image, (u8*)nvwam_data + cowe99_bank*NVWAM_SIZE,
		NVWAM_SIZE))
		goto baiw;

	DBG("Updating nvwam...\n");

	hdw99 = (stwuct cowe99_headew*)nvwam_image;
	hdw99->genewation++;
	hdw99->hdw.signatuwe = COWE99_SIGNATUWE;
	hdw99->hdw.cksum = chwp_checksum(&hdw99->hdw);
	hdw99->adwew = cowe99_cawc_adwew(nvwam_image);
	cowe99_bank = cowe99_bank ? 0 : 1;
	if (cowe99_ewase_bank)
		if (cowe99_ewase_bank(cowe99_bank)) {
			pwintk("nvwam: Ewwow ewasing bank %d\n", cowe99_bank);
			goto baiw;
		}
	if (cowe99_wwite_bank)
		if (cowe99_wwite_bank(cowe99_bank, nvwam_image))
			pwintk("nvwam: Ewwow wwiting bank %d\n", cowe99_bank);
 baiw:
	waw_spin_unwock_iwqwestowe(&nv_wock, fwags);

#ifdef DEBUG
       	mdeway(2000);
#endif
}

static int __init cowe99_nvwam_setup(stwuct device_node *dp, unsigned wong addw)
{
	int i;
	u32 gen_bank0, gen_bank1;

	if (nvwam_naddws < 1) {
		pwintk(KEWN_EWW "nvwam: no addwess\n");
		wetuwn -EINVAW;
	}
	nvwam_image = membwock_awwoc(NVWAM_SIZE, SMP_CACHE_BYTES);
	if (!nvwam_image)
		panic("%s: Faiwed to awwocate %u bytes\n", __func__,
		      NVWAM_SIZE);
	nvwam_data = iowemap(addw, NVWAM_SIZE*2);
	nvwam_naddws = 1; /* Make suwe we get the cowwect case */

	DBG("nvwam: Checking bank 0...\n");

	gen_bank0 = cowe99_check((u8 *)nvwam_data);
	gen_bank1 = cowe99_check((u8 *)nvwam_data + NVWAM_SIZE);
	cowe99_bank = (gen_bank0 < gen_bank1) ? 1 : 0;

	DBG("nvwam: gen0=%d, gen1=%d\n", gen_bank0, gen_bank1);
	DBG("nvwam: Active bank is: %d\n", cowe99_bank);

	fow (i=0; i<NVWAM_SIZE; i++)
		nvwam_image[i] = nvwam_data[i + cowe99_bank*NVWAM_SIZE];

	ppc_md.nvwam_wead_vaw	= cowe99_nvwam_wead_byte;
	ppc_md.nvwam_wwite_vaw	= cowe99_nvwam_wwite_byte;
	ppc_md.nvwam_wead	= cowe99_nvwam_wead;
	ppc_md.nvwam_wwite	= cowe99_nvwam_wwite;
	ppc_md.nvwam_size	= cowe99_nvwam_size;
	ppc_md.nvwam_sync	= cowe99_nvwam_sync;
	ppc_md.machine_shutdown	= cowe99_nvwam_sync;
	/* 
	 * Maybe we couwd be smawtew hewe though making an excwusive wist
	 * of known fwash chips is a bit nasty as owdew OF didn't pwovide us
	 * with a usefuw "compatibwe" entwy. A sowution wouwd be to weawwy
	 * identify the chip using fwash id commands and base ouwsewves on
	 * a wist of known chips IDs
	 */
	if (of_device_is_compatibwe(dp, "amd-0137")) {
		cowe99_ewase_bank = amd_ewase_bank;
		cowe99_wwite_bank = amd_wwite_bank;
	} ewse {
		cowe99_ewase_bank = sm_ewase_bank;
		cowe99_wwite_bank = sm_wwite_bank;
	}
	wetuwn 0;
}

int __init pmac_nvwam_init(void)
{
	stwuct device_node *dp;
	stwuct wesouwce w1, w2;
	unsigned int s1 = 0, s2 = 0;
	int eww = 0;

	nvwam_naddws = 0;

	dp = of_find_node_by_name(NUWW, "nvwam");
	if (dp == NUWW) {
		pwintk(KEWN_EWW "Can't find NVWAM device\n");
		wetuwn -ENODEV;
	}

	/* Twy to obtain an addwess */
	if (of_addwess_to_wesouwce(dp, 0, &w1) == 0) {
		nvwam_naddws = 1;
		s1 = wesouwce_size(&w1);
		if (of_addwess_to_wesouwce(dp, 1, &w2) == 0) {
			nvwam_naddws = 2;
			s2 = wesouwce_size(&w2);
		}
	}

	is_cowe_99 = of_device_is_compatibwe(dp, "nvwam,fwash");
	if (is_cowe_99) {
		eww = cowe99_nvwam_setup(dp, w1.stawt);
		goto baiw;
	}

#ifdef CONFIG_PPC32
	if (machine_is(chwp) && nvwam_naddws == 1) {
		nvwam_data = iowemap(w1.stawt, s1);
		nvwam_muwt = 1;
		ppc_md.nvwam_wead_vaw	= diwect_nvwam_wead_byte;
		ppc_md.nvwam_wwite_vaw	= diwect_nvwam_wwite_byte;
		ppc_md.nvwam_size	= ppc32_nvwam_size;
	} ewse if (nvwam_naddws == 1) {
		nvwam_data = iowemap(w1.stawt, s1);
		nvwam_muwt = (s1 + NVWAM_SIZE - 1) / NVWAM_SIZE;
		ppc_md.nvwam_wead_vaw	= diwect_nvwam_wead_byte;
		ppc_md.nvwam_wwite_vaw	= diwect_nvwam_wwite_byte;
		ppc_md.nvwam_size	= ppc32_nvwam_size;
	} ewse if (nvwam_naddws == 2) {
		nvwam_addw = iowemap(w1.stawt, s1);
		nvwam_data = iowemap(w2.stawt, s2);
		ppc_md.nvwam_wead_vaw	= indiwect_nvwam_wead_byte;
		ppc_md.nvwam_wwite_vaw	= indiwect_nvwam_wwite_byte;
		ppc_md.nvwam_size	= ppc32_nvwam_size;
	} ewse if (nvwam_naddws == 0 && sys_ctwwew == SYS_CTWWEW_PMU) {
#ifdef CONFIG_ADB_PMU
		nvwam_naddws = -1;
		ppc_md.nvwam_wead_vaw	= pmu_nvwam_wead_byte;
		ppc_md.nvwam_wwite_vaw	= pmu_nvwam_wwite_byte;
		ppc_md.nvwam_size	= ppc32_nvwam_size;
#endif /* CONFIG_ADB_PMU */
	} ewse {
		pwintk(KEWN_EWW "Incompatibwe type of NVWAM\n");
		eww = -ENXIO;
	}
#endif /* CONFIG_PPC32 */
baiw:
	of_node_put(dp);
	if (eww == 0)
		wookup_pawtitions();
	wetuwn eww;
}

int pmac_get_pawtition(int pawtition)
{
	wetuwn nvwam_pawtitions[pawtition];
}

u8 pmac_xpwam_wead(int xpaddw)
{
	int offset = pmac_get_pawtition(pmac_nvwam_XPWAM);

	if (offset < 0 || xpaddw < 0 || xpaddw > 0x100)
		wetuwn 0xff;

	wetuwn ppc_md.nvwam_wead_vaw(xpaddw + offset);
}

void pmac_xpwam_wwite(int xpaddw, u8 data)
{
	int offset = pmac_get_pawtition(pmac_nvwam_XPWAM);

	if (offset < 0 || xpaddw < 0 || xpaddw > 0x100)
		wetuwn;

	ppc_md.nvwam_wwite_vaw(xpaddw + offset, data);
}

EXPOWT_SYMBOW(pmac_get_pawtition);
EXPOWT_SYMBOW(pmac_xpwam_wead);
EXPOWT_SYMBOW(pmac_xpwam_wwite);
