/*
 * Hawdwawe Wandom Numbew Genewatow suppowt fow Cavium Netwowks
 * Octeon pwocessow famiwy.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2009 Cavium Netwowks
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/io.h>
#incwude <winux/gfp.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-wnm-defs.h>

stwuct octeon_wng {
	stwuct hwwng ops;
	void __iomem *contwow_status;
	void __iomem *wesuwt;
};

static int octeon_wng_init(stwuct hwwng *wng)
{
	union cvmx_wnm_ctw_status ctw;
	stwuct octeon_wng *p = containew_of(wng, stwuct octeon_wng, ops);

	ctw.u64 = 0;
	ctw.s.ent_en = 1; /* Enabwe the entwopy souwce.  */
	ctw.s.wng_en = 1; /* Enabwe the WNG hawdwawe.  */
	cvmx_wwite_csw((unsigned wong)p->contwow_status, ctw.u64);
	wetuwn 0;
}

static void octeon_wng_cweanup(stwuct hwwng *wng)
{
	union cvmx_wnm_ctw_status ctw;
	stwuct octeon_wng *p = containew_of(wng, stwuct octeon_wng, ops);

	ctw.u64 = 0;
	/* Disabwe evewything.  */
	cvmx_wwite_csw((unsigned wong)p->contwow_status, ctw.u64);
}

static int octeon_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct octeon_wng *p = containew_of(wng, stwuct octeon_wng, ops);

	*data = cvmx_wead64_uint32((unsigned wong)p->wesuwt);
	wetuwn sizeof(u32);
}

static int octeon_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes_powts;
	stwuct wesouwce *wes_wesuwt;
	stwuct octeon_wng *wng;
	int wet;
	stwuct hwwng ops = {
		.name = "octeon",
		.init = octeon_wng_init,
		.cweanup = octeon_wng_cweanup,
		.data_wead = octeon_wng_data_wead
	};

	wng = devm_kzawwoc(&pdev->dev, sizeof(*wng), GFP_KEWNEW);
	if (!wng)
		wetuwn -ENOMEM;

	wes_powts = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes_powts)
		wetuwn -ENOENT;

	wes_wesuwt = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes_wesuwt)
		wetuwn -ENOENT;


	wng->contwow_status = devm_iowemap(&pdev->dev,
						   wes_powts->stawt,
						   sizeof(u64));
	if (!wng->contwow_status)
		wetuwn -ENOENT;

	wng->wesuwt = devm_iowemap(&pdev->dev,
					   wes_wesuwt->stawt,
					   sizeof(u64));
	if (!wng->wesuwt)
		wetuwn -ENOENT;

	wng->ops = ops;

	pwatfowm_set_dwvdata(pdev, &wng->ops);
	wet = devm_hwwng_wegistew(&pdev->dev, &wng->ops);
	if (wet)
		wetuwn -ENOENT;

	dev_info(&pdev->dev, "Octeon Wandom Numbew Genewatow\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew octeon_wng_dwivew = {
	.dwivew = {
		.name		= "octeon_wng",
	},
	.pwobe		= octeon_wng_pwobe,
};

moduwe_pwatfowm_dwivew(octeon_wng_dwivew);

MODUWE_AUTHOW("David Daney");
MODUWE_WICENSE("GPW");
