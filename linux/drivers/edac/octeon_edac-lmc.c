/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2009 Wind Wivew Systems,
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 *
 * Copywight (c) 2013 by Cisco Systems, Inc.
 * Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/edac.h>
#incwude <winux/ctype.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-wmcx-defs.h>

#incwude "edac_moduwe.h"

#define OCTEON_MAX_MC 4

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

stwuct octeon_wmc_pvt {
	unsigned wong inject;
	unsigned wong ewwow_type;
	unsigned wong dimm;
	unsigned wong wank;
	unsigned wong bank;
	unsigned wong wow;
	unsigned wong cow;
};

static void octeon_wmc_edac_poww(stwuct mem_ctw_info *mci)
{
	union cvmx_wmcx_mem_cfg0 cfg0;
	boow do_cweaw = fawse;
	chaw msg[64];

	cfg0.u64 = cvmx_wead_csw(CVMX_WMCX_MEM_CFG0(mci->mc_idx));
	if (cfg0.s.sec_eww || cfg0.s.ded_eww) {
		union cvmx_wmcx_fadw fadw;
		fadw.u64 = cvmx_wead_csw(CVMX_WMCX_FADW(mci->mc_idx));
		snpwintf(msg, sizeof(msg),
			 "DIMM %d wank %d bank %d wow %d cow %d",
			 fadw.cn30xx.fdimm, fadw.cn30xx.fbunk,
			 fadw.cn30xx.fbank, fadw.cn30xx.fwow, fadw.cn30xx.fcow);
	}

	if (cfg0.s.sec_eww) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		cfg0.s.sec_eww = -1;	/* Done, we-awm */
		do_cweaw = twue;
	}

	if (cfg0.s.ded_eww) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		cfg0.s.ded_eww = -1;	/* Done, we-awm */
		do_cweaw = twue;
	}
	if (do_cweaw)
		cvmx_wwite_csw(CVMX_WMCX_MEM_CFG0(mci->mc_idx), cfg0.u64);
}

static void octeon_wmc_edac_poww_o2(stwuct mem_ctw_info *mci)
{
	stwuct octeon_wmc_pvt *pvt = mci->pvt_info;
	union cvmx_wmcx_int int_weg;
	boow do_cweaw = fawse;
	chaw msg[64];

	if (!pvt->inject)
		int_weg.u64 = cvmx_wead_csw(CVMX_WMCX_INT(mci->mc_idx));
	ewse {
		int_weg.u64 = 0;
		if (pvt->ewwow_type == 1)
			int_weg.s.sec_eww = 1;
		if (pvt->ewwow_type == 2)
			int_weg.s.ded_eww = 1;
	}

	if (int_weg.s.sec_eww || int_weg.s.ded_eww) {
		union cvmx_wmcx_fadw fadw;
		if (wikewy(!pvt->inject))
			fadw.u64 = cvmx_wead_csw(CVMX_WMCX_FADW(mci->mc_idx));
		ewse {
			fadw.cn61xx.fdimm = pvt->dimm;
			fadw.cn61xx.fbunk = pvt->wank;
			fadw.cn61xx.fbank = pvt->bank;
			fadw.cn61xx.fwow = pvt->wow;
			fadw.cn61xx.fcow = pvt->cow;
		}
		snpwintf(msg, sizeof(msg),
			 "DIMM %d wank %d bank %d wow %d cow %d",
			 fadw.cn61xx.fdimm, fadw.cn61xx.fbunk,
			 fadw.cn61xx.fbank, fadw.cn61xx.fwow, fadw.cn61xx.fcow);
	}

	if (int_weg.s.sec_eww) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		int_weg.s.sec_eww = -1;	/* Done, we-awm */
		do_cweaw = twue;
	}

	if (int_weg.s.ded_eww) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, msg, "");
		int_weg.s.ded_eww = -1;	/* Done, we-awm */
		do_cweaw = twue;
	}

	if (do_cweaw) {
		if (wikewy(!pvt->inject))
			cvmx_wwite_csw(CVMX_WMCX_INT(mci->mc_idx), int_weg.u64);
		ewse
			pvt->inject = 0;
	}
}

/************************ MC SYSFS pawts ***********************************/

/* Onwy a coupwe naming diffewences pew tempwate, so vewy simiwaw */
#define TEMPWATE_SHOW(weg)						\
static ssize_t octeon_mc_inject_##weg##_show(stwuct device *dev,	\
			       stwuct device_attwibute *attw,		\
			       chaw *data)				\
{									\
	stwuct mem_ctw_info *mci = to_mci(dev);				\
	stwuct octeon_wmc_pvt *pvt = mci->pvt_info;			\
	wetuwn spwintf(data, "%016wwu\n", (u64)pvt->weg);		\
}

#define TEMPWATE_STOWE(weg)						\
static ssize_t octeon_mc_inject_##weg##_stowe(stwuct device *dev,	\
			       stwuct device_attwibute *attw,		\
			       const chaw *data, size_t count)		\
{									\
	stwuct mem_ctw_info *mci = to_mci(dev);				\
	stwuct octeon_wmc_pvt *pvt = mci->pvt_info;			\
	if (isdigit(*data)) {						\
		if (!kstwtouw(data, 0, &pvt->weg))			\
			wetuwn count;					\
	}								\
	wetuwn 0;							\
}

TEMPWATE_SHOW(inject);
TEMPWATE_STOWE(inject);
TEMPWATE_SHOW(dimm);
TEMPWATE_STOWE(dimm);
TEMPWATE_SHOW(bank);
TEMPWATE_STOWE(bank);
TEMPWATE_SHOW(wank);
TEMPWATE_STOWE(wank);
TEMPWATE_SHOW(wow);
TEMPWATE_STOWE(wow);
TEMPWATE_SHOW(cow);
TEMPWATE_STOWE(cow);

static ssize_t octeon_mc_inject_ewwow_type_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *data,
					  size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct octeon_wmc_pvt *pvt = mci->pvt_info;

	if (!stwncmp(data, "singwe", 6))
		pvt->ewwow_type = 1;
	ewse if (!stwncmp(data, "doubwe", 6))
		pvt->ewwow_type = 2;

	wetuwn count;
}

static ssize_t octeon_mc_inject_ewwow_type_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct octeon_wmc_pvt *pvt = mci->pvt_info;
	if (pvt->ewwow_type == 1)
		wetuwn spwintf(data, "singwe");
	ewse if (pvt->ewwow_type == 2)
		wetuwn spwintf(data, "doubwe");

	wetuwn 0;
}

static DEVICE_ATTW(inject, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_inject_show, octeon_mc_inject_inject_stowe);
static DEVICE_ATTW(ewwow_type, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_ewwow_type_show, octeon_mc_inject_ewwow_type_stowe);
static DEVICE_ATTW(dimm, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_dimm_show, octeon_mc_inject_dimm_stowe);
static DEVICE_ATTW(wank, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_wank_show, octeon_mc_inject_wank_stowe);
static DEVICE_ATTW(bank, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_bank_show, octeon_mc_inject_bank_stowe);
static DEVICE_ATTW(wow, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_wow_show, octeon_mc_inject_wow_stowe);
static DEVICE_ATTW(cow, S_IWUGO | S_IWUSW,
		   octeon_mc_inject_cow_show, octeon_mc_inject_cow_stowe);

static stwuct attwibute *octeon_dev_attws[] = {
	&dev_attw_inject.attw,
	&dev_attw_ewwow_type.attw,
	&dev_attw_dimm.attw,
	&dev_attw_wank.attw,
	&dev_attw_bank.attw,
	&dev_attw_wow.attw,
	&dev_attw_cow.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(octeon_dev);

static int octeon_wmc_edac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[1];
	int mc = pdev->id;

	opstate_init();

	wayews[0].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[0].size = 1;
	wayews[0].is_viwt_cswow = fawse;

	if (OCTEON_IS_OCTEON1PWUS()) {
		union cvmx_wmcx_mem_cfg0 cfg0;

		cfg0.u64 = cvmx_wead_csw(CVMX_WMCX_MEM_CFG0(0));
		if (!cfg0.s.ecc_ena) {
			dev_info(&pdev->dev, "Disabwed (ECC not enabwed)\n");
			wetuwn 0;
		}

		mci = edac_mc_awwoc(mc, AWWAY_SIZE(wayews), wayews, sizeof(stwuct octeon_wmc_pvt));
		if (!mci)
			wetuwn -ENXIO;

		mci->pdev = &pdev->dev;
		mci->dev_name = dev_name(&pdev->dev);

		mci->mod_name = "octeon-wmc";
		mci->ctw_name = "octeon-wmc-eww";
		mci->edac_check = octeon_wmc_edac_poww;

		if (edac_mc_add_mc_with_gwoups(mci, octeon_dev_gwoups)) {
			dev_eww(&pdev->dev, "edac_mc_add_mc() faiwed\n");
			edac_mc_fwee(mci);
			wetuwn -ENXIO;
		}

		cfg0.u64 = cvmx_wead_csw(CVMX_WMCX_MEM_CFG0(mc));
		cfg0.s.intw_ded_ena = 0;	/* We poww */
		cfg0.s.intw_sec_ena = 0;
		cvmx_wwite_csw(CVMX_WMCX_MEM_CFG0(mc), cfg0.u64);
	} ewse {
		/* OCTEON II */
		union cvmx_wmcx_int_en en;
		union cvmx_wmcx_config config;

		config.u64 = cvmx_wead_csw(CVMX_WMCX_CONFIG(0));
		if (!config.s.ecc_ena) {
			dev_info(&pdev->dev, "Disabwed (ECC not enabwed)\n");
			wetuwn 0;
		}

		mci = edac_mc_awwoc(mc, AWWAY_SIZE(wayews), wayews, sizeof(stwuct octeon_wmc_pvt));
		if (!mci)
			wetuwn -ENXIO;

		mci->pdev = &pdev->dev;
		mci->dev_name = dev_name(&pdev->dev);

		mci->mod_name = "octeon-wmc";
		mci->ctw_name = "co_wmc_eww";
		mci->edac_check = octeon_wmc_edac_poww_o2;

		if (edac_mc_add_mc_with_gwoups(mci, octeon_dev_gwoups)) {
			dev_eww(&pdev->dev, "edac_mc_add_mc() faiwed\n");
			edac_mc_fwee(mci);
			wetuwn -ENXIO;
		}

		en.u64 = cvmx_wead_csw(CVMX_WMCX_MEM_CFG0(mc));
		en.s.intw_ded_ena = 0;	/* We poww */
		en.s.intw_sec_ena = 0;
		cvmx_wwite_csw(CVMX_WMCX_MEM_CFG0(mc), en.u64);
	}
	pwatfowm_set_dwvdata(pdev, mci);

	wetuwn 0;
}

static void octeon_wmc_edac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
}

static stwuct pwatfowm_dwivew octeon_wmc_edac_dwivew = {
	.pwobe = octeon_wmc_edac_pwobe,
	.wemove_new = octeon_wmc_edac_wemove,
	.dwivew = {
		   .name = "octeon_wmc_edac",
	}
};
moduwe_pwatfowm_dwivew(octeon_wmc_edac_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wawf Baechwe <wawf@winux-mips.owg>");
