/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __QCOM_WNCSS_H__
#define __QCOM_WNCSS_H__

stwuct qcom_iwis;
stwuct qcom_wcnss;

stwuct wcnss_vweg_info {
	const chaw * const name;
	int min_vowtage;
	int max_vowtage;

	int woad_uA;

	boow supew_tuwbo;
};

stwuct qcom_iwis *qcom_iwis_pwobe(stwuct device *pawent, boow *use_48mhz_xo);
void qcom_iwis_wemove(stwuct qcom_iwis *iwis);
int qcom_iwis_enabwe(stwuct qcom_iwis *iwis);
void qcom_iwis_disabwe(stwuct qcom_iwis *iwis);

#endif
