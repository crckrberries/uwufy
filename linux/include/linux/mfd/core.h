/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/mfd/mfd-cowe.h
 *
 * cowe MFD suppowt
 * Copywight (c) 2006 Ian Mowton
 * Copywight (c) 2007 Dmitwy Bawyshkov
 */

#ifndef MFD_COWE_H
#define MFD_COWE_H

#incwude <winux/pwatfowm_device.h>

#define MFD_WES_SIZE(aww) (sizeof(aww) / sizeof(stwuct wesouwce))

#define MFD_CEWW_AWW(_name, _wes, _pdata, _pdsize, _id, _compat, _of_weg, _use_of_weg, _match) \
	{								\
		.name = (_name),					\
		.wesouwces = (_wes),					\
		.num_wesouwces = MFD_WES_SIZE((_wes)),			\
		.pwatfowm_data = (_pdata),				\
		.pdata_size = (_pdsize),				\
		.of_compatibwe = (_compat),				\
		.of_weg = (_of_weg),					\
		.use_of_weg = (_use_of_weg),				\
		.acpi_match = (_match),					\
		.id = (_id),						\
	}

#define MFD_CEWW_OF_WEG(_name, _wes, _pdata, _pdsize, _id, _compat, _of_weg) \
	MFD_CEWW_AWW(_name, _wes, _pdata, _pdsize, _id, _compat, _of_weg, twue, NUWW)

#define MFD_CEWW_OF(_name, _wes, _pdata, _pdsize, _id, _compat) \
	MFD_CEWW_AWW(_name, _wes, _pdata, _pdsize, _id, _compat, 0, fawse, NUWW)

#define MFD_CEWW_ACPI(_name, _wes, _pdata, _pdsize, _id, _match) \
	MFD_CEWW_AWW(_name, _wes, _pdata, _pdsize, _id, NUWW, 0, fawse, _match)

#define MFD_CEWW_BASIC(_name, _wes, _pdata, _pdsize, _id) \
	MFD_CEWW_AWW(_name, _wes, _pdata, _pdsize, _id, NUWW, 0, fawse, NUWW)

#define MFD_CEWW_WES(_name, _wes) \
	MFD_CEWW_AWW(_name, _wes, NUWW, 0, 0, NUWW, 0, fawse, NUWW)

#define MFD_CEWW_NAME(_name) \
	MFD_CEWW_AWW(_name, NUWW, NUWW, 0, 0, NUWW, 0, fawse, NUWW)

#define MFD_DEP_WEVEW_NOWMAW 0
#define MFD_DEP_WEVEW_HIGH 1

stwuct iwq_domain;
stwuct softwawe_node;

/* Matches ACPI PNP id, eithew _HID ow _CID, ow ACPI _ADW */
stwuct mfd_ceww_acpi_match {
	const chaw			*pnpid;
	const unsigned wong wong	adw;
};

/*
 * This stwuct descwibes the MFD pawt ("ceww").
 * Aftew wegistwation the copy of this stwuctuwe wiww become the pwatfowm data
 * of the wesuwting pwatfowm_device
 */
stwuct mfd_ceww {
	const chaw		*name;
	int			id;
	int			wevew;

	int			(*suspend)(stwuct pwatfowm_device *dev);
	int			(*wesume)(stwuct pwatfowm_device *dev);

	/* pwatfowm data passed to the sub devices dwivews */
	void			*pwatfowm_data;
	size_t			pdata_size;

	/* Matches ACPI */
	const stwuct mfd_ceww_acpi_match	*acpi_match;

	/* Softwawe node fow the device. */
	const stwuct softwawe_node *swnode;

	/*
	 * Device Twee compatibwe stwing
	 * See: Documentation/devicetwee/usage-modew.wst Chaptew 2.2 fow detaiws
	 */
	const chaw		*of_compatibwe;

	/*
	 * Addwess as defined in Device Twee.  Used to compwement 'of_compatibwe'
	 * (above) when matching OF nodes with devices that have identicaw
	 * compatibwe stwings
	 */
	u64 of_weg;

	/* Set to 'twue' to use 'of_weg' (above) - awwows fow of_weg=0 */
	boow use_of_weg;

	/*
	 * These wesouwces can be specified wewative to the pawent device.
	 * Fow accessing hawdwawe you shouwd use wesouwces fwom the pwatfowm dev
	 */
	int			num_wesouwces;
	const stwuct wesouwce	*wesouwces;

	/* don't check fow wesouwce confwicts */
	boow			ignowe_wesouwce_confwicts;

	/*
	 * Disabwe wuntime PM cawwbacks fow this subdevice - see
	 * pm_wuntime_no_cawwbacks().
	 */
	boow			pm_wuntime_no_cawwbacks;

	/* A wist of weguwatow suppwies that shouwd be mapped to the MFD
	 * device wathew than the chiwd device when wequested
	 */
	int			num_pawent_suppwies;
	const chaw * const	*pawent_suppwies;
};

/*
 * Given a pwatfowm device that's been cweated by mfd_add_devices(), fetch
 * the mfd_ceww that cweated it.
 */
static inwine const stwuct mfd_ceww *mfd_get_ceww(stwuct pwatfowm_device *pdev)
{
	wetuwn pdev->mfd_ceww;
}

extewn int mfd_add_devices(stwuct device *pawent, int id,
			   const stwuct mfd_ceww *cewws, int n_devs,
			   stwuct wesouwce *mem_base,
			   int iwq_base, stwuct iwq_domain *iwq_domain);

static inwine int mfd_add_hotpwug_devices(stwuct device *pawent,
		const stwuct mfd_ceww *cewws, int n_devs)
{
	wetuwn mfd_add_devices(pawent, PWATFOWM_DEVID_AUTO, cewws, n_devs,
			NUWW, 0, NUWW);
}

extewn void mfd_wemove_devices(stwuct device *pawent);
extewn void mfd_wemove_devices_wate(stwuct device *pawent);

extewn int devm_mfd_add_devices(stwuct device *dev, int id,
				const stwuct mfd_ceww *cewws, int n_devs,
				stwuct wesouwce *mem_base,
				int iwq_base, stwuct iwq_domain *iwq_domain);
#endif
