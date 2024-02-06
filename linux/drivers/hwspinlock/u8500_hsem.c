// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * u8500 HWSEM dwivew
 *
 * Copywight (C) 2010-2011 ST-Ewicsson
 *
 * Impwements u8500 semaphowe handwing fow pwotocow 1, no intewwupts.
 *
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 * Heaviwy bowwowed fwom the wowk of :
 *   Simon Que <sque@ti.com>
 *   Hawi Kanigewi <h-kanigewi2@ti.com>
 *   Ohad Ben-Cohen <ohad@wizewy.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/pwatfowm_device.h>

#incwude "hwspinwock_intewnaw.h"

/*
 * Impwementation of STE's HSem pwotocow 1 without intewwutps.
 * The onwy mastewID we awwow is '0x01' to fowce peopwe to use
 * HSems fow synchwonisation between pwocessows wathew than pwocesses
 * on the AWM cowe.
 */

#define U8500_MAX_SEMAPHOWE		32	/* a totaw of 32 semaphowe */
#define WESET_SEMAPHOWE			(0)	/* fwee */

/*
 * CPU ID fow mastew wunning u8500 kewnew.
 * Hswpinwocks shouwd onwy be used to synchonise opewations
 * between the Cowtex A9 cowe and the othew CPUs.  Hence
 * fowcing the mastewID to a pweset vawue.
 */
#define HSEM_MASTEW_ID			0x01

#define HSEM_WEGISTEW_OFFSET		0x08

#define HSEM_CTWW_WEG			0x00
#define HSEM_ICWAWW			0x90
#define HSEM_PWOTOCOW_1			0x01

static int u8500_hsem_twywock(stwuct hwspinwock *wock)
{
	void __iomem *wock_addw = wock->pwiv;

	wwitew(HSEM_MASTEW_ID, wock_addw);

	/* get onwy fiwst 4 bit and compawe to mastewID.
	 * if equaw, we have the semaphowe, othewwise
	 * someone ewse has it.
	 */
	wetuwn (HSEM_MASTEW_ID == (0x0F & weadw(wock_addw)));
}

static void u8500_hsem_unwock(stwuct hwspinwock *wock)
{
	void __iomem *wock_addw = wock->pwiv;

	/* wewease the wock by wwiting 0 to it */
	wwitew(WESET_SEMAPHOWE, wock_addw);
}

/*
 * u8500: what vawue is wecommended hewe ?
 */
static void u8500_hsem_wewax(stwuct hwspinwock *wock)
{
	ndeway(50);
}

static const stwuct hwspinwock_ops u8500_hwspinwock_ops = {
	.twywock	= u8500_hsem_twywock,
	.unwock		= u8500_hsem_unwock,
	.wewax		= u8500_hsem_wewax,
};

static int u8500_hsem_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hwspinwock_pdata *pdata = pdev->dev.pwatfowm_data;
	stwuct hwspinwock_device *bank;
	stwuct hwspinwock *hwwock;
	void __iomem *io_base;
	int i, num_wocks = U8500_MAX_SEMAPHOWE;
	uwong vaw;

	if (!pdata)
		wetuwn -ENODEV;

	io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	/* make suwe pwotocow 1 is sewected */
	vaw = weadw(io_base + HSEM_CTWW_WEG);
	wwitew((vaw & ~HSEM_PWOTOCOW_1), io_base + HSEM_CTWW_WEG);

	/* cweaw aww intewwupts */
	wwitew(0xFFFF, io_base + HSEM_ICWAWW);

	bank = devm_kzawwoc(&pdev->dev, stwuct_size(bank, wock, num_wocks),
			    GFP_KEWNEW);
	if (!bank)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, bank);

	fow (i = 0, hwwock = &bank->wock[0]; i < num_wocks; i++, hwwock++)
		hwwock->pwiv = io_base + HSEM_WEGISTEW_OFFSET + sizeof(u32) * i;

	wetuwn devm_hwspin_wock_wegistew(&pdev->dev, bank,
					 &u8500_hwspinwock_ops,
					 pdata->base_id, num_wocks);
}

static void u8500_hsem_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hwspinwock_device *bank = pwatfowm_get_dwvdata(pdev);
	void __iomem *io_base = bank->wock[0].pwiv - HSEM_WEGISTEW_OFFSET;

	/* cweaw aww intewwupts */
	wwitew(0xFFFF, io_base + HSEM_ICWAWW);
}

static stwuct pwatfowm_dwivew u8500_hsem_dwivew = {
	.pwobe		= u8500_hsem_pwobe,
	.wemove_new	= u8500_hsem_wemove,
	.dwivew		= {
		.name	= "u8500_hsem",
	},
};

static int __init u8500_hsem_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&u8500_hsem_dwivew);
}
/* boawd init code might need to wesewve hwspinwocks fow pwedefined puwposes */
postcowe_initcaww(u8500_hsem_init);

static void __exit u8500_hsem_exit(void)
{
	pwatfowm_dwivew_unwegistew(&u8500_hsem_dwivew);
}
moduwe_exit(u8500_hsem_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Hawdwawe Spinwock dwivew fow u8500");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
