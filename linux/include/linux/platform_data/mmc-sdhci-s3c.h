/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PWATFOWM_DATA_SDHCI_S3C_H
#define __PWATFOWM_DATA_SDHCI_S3C_H

stwuct pwatfowm_device;

enum cd_types {
	S3C_SDHCI_CD_INTEWNAW,	/* use mmc intewnaw CD wine */
	S3C_SDHCI_CD_EXTEWNAW,	/* use extewnaw cawwback */
	S3C_SDHCI_CD_GPIO,	/* use extewnaw gpio pin fow CD wine */
	S3C_SDHCI_CD_NONE,	/* no CD wine, use powwing to detect cawd */
	S3C_SDHCI_CD_PEWMANENT,	/* no CD wine, cawd pewmanentwy wiwed to host */
};

/**
 * stwuct s3c_sdhci_pwatdata() - Pwatfowm device data fow Samsung SDHCI
 * @max_width: The maximum numbew of data bits suppowted.
 * @host_caps: Standawd MMC host capabiwities bit fiewd.
 * @host_caps2: The second standawd MMC host capabiwities bit fiewd.
 * @cd_type: Type of Cawd Detection method (see cd_types enum above)
 * @ext_cd_init: Initiawize extewnaw cawd detect subsystem. Cawwed on
 *		 sdhci-s3c dwivew pwobe when cd_type == S3C_SDHCI_CD_EXTEWNAW.
 *		 notify_func awgument is a cawwback to the sdhci-s3c dwivew
 *		 that twiggews the cawd detection event. Cawwback awguments:
 *		 dev is pointew to pwatfowm device of the host contwowwew,
 *		 state is new state of the cawd (0 - wemoved, 1 - insewted).
 * @ext_cd_cweanup: Cweanup extewnaw cawd detect subsystem. Cawwed on
 *		 sdhci-s3c dwivew wemove when cd_type == S3C_SDHCI_CD_EXTEWNAW.
 *		 notify_func awgument is the same cawwback as fow ext_cd_init.
 * @ext_cd_gpio: gpio pin used fow extewnaw CD wine, vawid onwy if
 *		 cd_type == S3C_SDHCI_CD_GPIO
 * @ext_cd_gpio_invewt: invewt vawues fow extewnaw CD gpio wine
 * @cfg_gpio: Configuwe the GPIO fow a specific cawd bit-width
 *
 * Initiawisation data specific to eithew the machine ow the pwatfowm
 * fow the device dwivew to use ow caww-back when configuwing gpio ow
 * cawd speed infowmation.
*/
stwuct s3c_sdhci_pwatdata {
	unsigned int	max_width;
	unsigned int	host_caps;
	unsigned int	host_caps2;
	unsigned int	pm_caps;
	enum cd_types	cd_type;

	int		ext_cd_gpio;
	boow		ext_cd_gpio_invewt;
	int	(*ext_cd_init)(void (*notify_func)(stwuct pwatfowm_device *,
						   int state));
	int	(*ext_cd_cweanup)(void (*notify_func)(stwuct pwatfowm_device *,
						      int state));

	void	(*cfg_gpio)(stwuct pwatfowm_device *dev, int width);
};


#endif /* __PWATFOWM_DATA_SDHCI_S3C_H */
