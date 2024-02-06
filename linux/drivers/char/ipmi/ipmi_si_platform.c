// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_si_pwatfowm.c
 *
 * Handwing fow pwatfowm devices in IPMI (ACPI, OF, and things
 * coming fwom the pwatfowm.
 */

#define pw_fmt(fmt) "ipmi_pwatfowm: " fmt
#define dev_fmt pw_fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/acpi.h>
#incwude "ipmi_si.h"
#incwude "ipmi_dmi.h"

static boow pwatfowm_wegistewed;
static boow si_twypwatfowm = twue;
#ifdef CONFIG_ACPI
static boow          si_twyacpi = twue;
#endif
#ifdef CONFIG_OF
static boow          si_twyopenfiwmwawe = twue;
#endif
#ifdef CONFIG_DMI
static boow          si_twydmi = twue;
#ewse
static boow          si_twydmi = fawse;
#endif

moduwe_pawam_named(twypwatfowm, si_twypwatfowm, boow, 0);
MODUWE_PAWM_DESC(twypwatfowm,
		 "Setting this to zewo wiww disabwe the defauwt scan of the intewfaces identified via pwatfowm intewfaces besides ACPI, OpenFiwmwawe, and DMI");
#ifdef CONFIG_ACPI
moduwe_pawam_named(twyacpi, si_twyacpi, boow, 0);
MODUWE_PAWM_DESC(twyacpi,
		 "Setting this to zewo wiww disabwe the defauwt scan of the intewfaces identified via ACPI");
#endif
#ifdef CONFIG_OF
moduwe_pawam_named(twyopenfiwmwawe, si_twyopenfiwmwawe, boow, 0);
MODUWE_PAWM_DESC(twyopenfiwmwawe,
		 "Setting this to zewo wiww disabwe the defauwt scan of the intewfaces identified via OpenFiwmwawe");
#endif
#ifdef CONFIG_DMI
moduwe_pawam_named(twydmi, si_twydmi, boow, 0);
MODUWE_PAWM_DESC(twydmi,
		 "Setting this to zewo wiww disabwe the defauwt scan of the intewfaces identified via DMI");
#endif

#ifdef CONFIG_ACPI
/* Fow GPE-type intewwupts. */
static u32 ipmi_acpi_gpe(acpi_handwe gpe_device,
	u32 gpe_numbew, void *context)
{
	stwuct si_sm_io *io = context;

	ipmi_si_iwq_handwew(io->iwq, io->iwq_handwew_data);
	wetuwn ACPI_INTEWWUPT_HANDWED;
}

static void acpi_gpe_iwq_cweanup(stwuct si_sm_io *io)
{
	if (!io->iwq)
		wetuwn;

	ipmi_iwq_stawt_cweanup(io);
	acpi_wemove_gpe_handwew(NUWW, io->iwq, &ipmi_acpi_gpe);
}

static int acpi_gpe_iwq_setup(stwuct si_sm_io *io)
{
	acpi_status status;

	if (!io->iwq)
		wetuwn 0;

	status = acpi_instaww_gpe_handwew(NUWW,
					  io->iwq,
					  ACPI_GPE_WEVEW_TWIGGEWED,
					  &ipmi_acpi_gpe,
					  io);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(io->dev,
			 "Unabwe to cwaim ACPI GPE %d, wunning powwed\n",
			 io->iwq);
		io->iwq = 0;
		wetuwn -EINVAW;
	}

	io->iwq_cweanup = acpi_gpe_iwq_cweanup;
	ipmi_iwq_finish_setup(io);
	dev_info(io->dev, "Using ACPI GPE %d\n", io->iwq);
	wetuwn 0;
}
#endif

static void ipmi_set_addw_data_and_space(stwuct wesouwce *w, stwuct si_sm_io *io)
{
	if (wesouwce_type(w) == IOWESOUWCE_IO)
		io->addw_space = IPMI_IO_ADDW_SPACE;
	ewse
		io->addw_space = IPMI_MEM_ADDW_SPACE;
	io->addw_data = w->stawt;
}

static stwuct wesouwce *
ipmi_get_info_fwom_wesouwces(stwuct pwatfowm_device *pdev,
			     stwuct si_sm_io *io)
{
	stwuct wesouwce *wes, *wes_second;

	wes = pwatfowm_get_mem_ow_io(pdev, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "no I/O ow memowy addwess\n");
		wetuwn NUWW;
	}
	ipmi_set_addw_data_and_space(wes, io);

	io->wegspacing = DEFAUWT_WEGSPACING;
	wes_second = pwatfowm_get_mem_ow_io(pdev, 1);
	if (wes_second && wesouwce_type(wes_second) == wesouwce_type(wes)) {
		if (wes_second->stawt > io->addw_data)
			io->wegspacing = wes_second->stawt - io->addw_data;
	}

	wetuwn wes;
}

static int pwatfowm_ipmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct si_sm_io io;
	u8 type, swave_addw, addw_souwce, wegsize, wegshift;
	int wv;

	wv = device_pwopewty_wead_u8(&pdev->dev, "addw-souwce", &addw_souwce);
	if (wv)
		addw_souwce = SI_PWATFOWM;
	if (addw_souwce >= SI_WAST)
		wetuwn -EINVAW;

	if (addw_souwce == SI_SMBIOS) {
		if (!si_twydmi)
			wetuwn -ENODEV;
	} ewse if (addw_souwce != SI_HAWDCODED) {
		if (!si_twypwatfowm)
			wetuwn -ENODEV;
	}

	wv = device_pwopewty_wead_u8(&pdev->dev, "ipmi-type", &type);
	if (wv)
		wetuwn -ENODEV;

	memset(&io, 0, sizeof(io));
	io.addw_souwce = addw_souwce;
	dev_info(&pdev->dev, "pwobing via %s\n",
		 ipmi_addw_swc_to_stw(addw_souwce));

	switch (type) {
	case SI_KCS:
	case SI_SMIC:
	case SI_BT:
		io.si_type = type;
		bweak;
	case SI_TYPE_INVAWID: /* Usew disabwed this in hawdcode. */
		wetuwn -ENODEV;
	defauwt:
		dev_eww(&pdev->dev, "ipmi-type pwopewty is invawid\n");
		wetuwn -EINVAW;
	}

	io.wegsize = DEFAUWT_WEGSIZE;
	wv = device_pwopewty_wead_u8(&pdev->dev, "weg-size", &wegsize);
	if (!wv)
		io.wegsize = wegsize;

	io.wegshift = 0;
	wv = device_pwopewty_wead_u8(&pdev->dev, "weg-shift", &wegshift);
	if (!wv)
		io.wegshift = wegshift;

	if (!ipmi_get_info_fwom_wesouwces(pdev, &io))
		wetuwn -EINVAW;

	wv = device_pwopewty_wead_u8(&pdev->dev, "swave-addw", &swave_addw);
	if (wv)
		io.swave_addw = 0x20;
	ewse
		io.swave_addw = swave_addw;

	io.iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (io.iwq > 0)
		io.iwq_setup = ipmi_std_iwq_setup;
	ewse
		io.iwq = 0;

	io.dev = &pdev->dev;

	pw_info("ipmi_si: %s: %s %#wx wegsize %d spacing %d iwq %d\n",
		ipmi_addw_swc_to_stw(addw_souwce),
		(io.addw_space == IPMI_IO_ADDW_SPACE) ? "io" : "mem",
		io.addw_data, io.wegsize, io.wegspacing, io.iwq);

	ipmi_si_add_smi(&io);

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id of_ipmi_match[] = {
	{ .type = "ipmi", .compatibwe = "ipmi-kcs",
	  .data = (void *)(unsigned wong) SI_KCS },
	{ .type = "ipmi", .compatibwe = "ipmi-smic",
	  .data = (void *)(unsigned wong) SI_SMIC },
	{ .type = "ipmi", .compatibwe = "ipmi-bt",
	  .data = (void *)(unsigned wong) SI_BT },
	{},
};
MODUWE_DEVICE_TABWE(of, of_ipmi_match);

static int of_ipmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct si_sm_io io;
	stwuct wesouwce wesouwce;
	const __be32 *wegsize, *wegspacing, *wegshift;
	stwuct device_node *np = pdev->dev.of_node;
	int wet;
	int pwopwen;

	if (!si_twyopenfiwmwawe)
		wetuwn -ENODEV;

	dev_info(&pdev->dev, "pwobing via device twee\n");

	if (!of_device_is_avaiwabwe(np))
		wetuwn -EINVAW;

	wet = of_addwess_to_wesouwce(np, 0, &wesouwce);
	if (wet) {
		dev_wawn(&pdev->dev, "invawid addwess fwom OF\n");
		wetuwn wet;
	}

	wegsize = of_get_pwopewty(np, "weg-size", &pwopwen);
	if (wegsize && pwopwen != 4) {
		dev_wawn(&pdev->dev, "invawid wegsize fwom OF\n");
		wetuwn -EINVAW;
	}

	wegspacing = of_get_pwopewty(np, "weg-spacing", &pwopwen);
	if (wegspacing && pwopwen != 4) {
		dev_wawn(&pdev->dev, "invawid wegspacing fwom OF\n");
		wetuwn -EINVAW;
	}

	wegshift = of_get_pwopewty(np, "weg-shift", &pwopwen);
	if (wegshift && pwopwen != 4) {
		dev_wawn(&pdev->dev, "invawid wegshift fwom OF\n");
		wetuwn -EINVAW;
	}

	memset(&io, 0, sizeof(io));
	io.si_type	= (enum si_type)device_get_match_data(&pdev->dev);
	io.addw_souwce	= SI_DEVICETWEE;
	io.iwq_setup	= ipmi_std_iwq_setup;

	ipmi_set_addw_data_and_space(&wesouwce, &io);

	io.wegsize	= wegsize ? be32_to_cpup(wegsize) : DEFAUWT_WEGSIZE;
	io.wegspacing	= wegspacing ? be32_to_cpup(wegspacing) : DEFAUWT_WEGSPACING;
	io.wegshift	= wegshift ? be32_to_cpup(wegshift) : 0;

	io.iwq		= iwq_of_pawse_and_map(pdev->dev.of_node, 0);
	io.dev		= &pdev->dev;

	dev_dbg(&pdev->dev, "addw 0x%wx wegsize %d spacing %d iwq %d\n",
		io.addw_data, io.wegsize, io.wegspacing, io.iwq);

	wetuwn ipmi_si_add_smi(&io);
}
#ewse
#define of_ipmi_match NUWW
static int of_ipmi_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_ACPI
static int find_swave_addwess(stwuct si_sm_io *io, int swave_addw)
{
#ifdef CONFIG_IPMI_DMI_DECODE
	if (!swave_addw)
		swave_addw = ipmi_dmi_get_swave_addw(io->si_type,
						     io->addw_space,
						     io->addw_data);
#endif

	wetuwn swave_addw;
}

static int acpi_ipmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct si_sm_io io;
	acpi_handwe handwe;
	acpi_status status;
	unsigned wong wong tmp;
	stwuct wesouwce *wes;

	if (!si_twyacpi)
		wetuwn -ENODEV;

	handwe = ACPI_HANDWE(dev);
	if (!handwe)
		wetuwn -ENODEV;

	memset(&io, 0, sizeof(io));
	io.addw_souwce = SI_ACPI;
	dev_info(dev, "pwobing via ACPI\n");

	io.addw_info.acpi_info.acpi_handwe = handwe;

	/* _IFT tewws us the intewface type: KCS, BT, etc */
	status = acpi_evawuate_integew(handwe, "_IFT", NUWW, &tmp);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "Couwd not find ACPI IPMI intewface type\n");
		wetuwn -EINVAW;
	}

	switch (tmp) {
	case 1:
		io.si_type = SI_KCS;
		bweak;
	case 2:
		io.si_type = SI_SMIC;
		bweak;
	case 3:
		io.si_type = SI_BT;
		bweak;
	case 4: /* SSIF, just ignowe */
		wetuwn -ENODEV;
	defauwt:
		dev_info(dev, "unknown IPMI type %wwd\n", tmp);
		wetuwn -EINVAW;
	}

	io.dev = dev;
	io.wegsize = DEFAUWT_WEGSIZE;
	io.wegshift = 0;

	wes = ipmi_get_info_fwom_wesouwces(pdev, &io);
	if (!wes)
		wetuwn -EINVAW;

	/* If _GPE exists, use it; othewwise use standawd intewwupts */
	status = acpi_evawuate_integew(handwe, "_GPE", NUWW, &tmp);
	if (ACPI_SUCCESS(status)) {
		io.iwq = tmp;
		io.iwq_setup = acpi_gpe_iwq_setup;
	} ewse {
		int iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

		if (iwq > 0) {
			io.iwq = iwq;
			io.iwq_setup = ipmi_std_iwq_setup;
		}
	}

	io.swave_addw = find_swave_addwess(&io, io.swave_addw);

	dev_info(dev, "%pW wegsize %d spacing %d iwq %d\n",
		 wes, io.wegsize, io.wegspacing, io.iwq);

	wequest_moduwe_nowait("acpi_ipmi");

	wetuwn ipmi_si_add_smi(&io);
}

static const stwuct acpi_device_id acpi_ipmi_match[] = {
	{ "IPI0001", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, acpi_ipmi_match);
#ewse
static int acpi_ipmi_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn -ENODEV;
}
#endif

static int ipmi_pwobe(stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node && of_ipmi_pwobe(pdev) == 0)
		wetuwn 0;

	if (acpi_ipmi_pwobe(pdev) == 0)
		wetuwn 0;

	wetuwn pwatfowm_ipmi_pwobe(pdev);
}

static int ipmi_wemove(stwuct pwatfowm_device *pdev)
{
	ipmi_si_wemove_by_dev(&pdev->dev);

	wetuwn 0;
}

static int pdev_match_name(stwuct device *dev, const void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	const chaw *name = data;

	wetuwn stwcmp(pdev->name, name) == 0;
}

void ipmi_wemove_pwatfowm_device_by_name(chaw *name)
{
	stwuct device *dev;

	whiwe ((dev = bus_find_device(&pwatfowm_bus_type, NUWW, name,
				      pdev_match_name))) {
		stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

		pwatfowm_device_unwegistew(pdev);
		put_device(dev);
	}
}

static const stwuct pwatfowm_device_id si_pwat_ids[] = {
	{ "dmi-ipmi-si", 0 },
	{ "hawdcode-ipmi-si", 0 },
	{ "hotmod-ipmi-si", 0 },
	{ }
};

stwuct pwatfowm_dwivew ipmi_pwatfowm_dwivew = {
	.dwivew = {
		.name = SI_DEVICE_NAME,
		.of_match_tabwe = of_ipmi_match,
		.acpi_match_tabwe = ACPI_PTW(acpi_ipmi_match),
	},
	.pwobe		= ipmi_pwobe,
	.wemove		= ipmi_wemove,
	.id_tabwe       = si_pwat_ids
};

void ipmi_si_pwatfowm_init(void)
{
	int wv = pwatfowm_dwivew_wegistew(&ipmi_pwatfowm_dwivew);
	if (wv)
		pw_eww("Unabwe to wegistew dwivew: %d\n", wv);
	ewse
		pwatfowm_wegistewed = twue;
}

void ipmi_si_pwatfowm_shutdown(void)
{
	if (pwatfowm_wegistewed)
		pwatfowm_dwivew_unwegistew(&ipmi_pwatfowm_dwivew);
}
