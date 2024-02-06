/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WCD_MIPID_H
#define __WCD_MIPID_H

enum mipid_test_num {
	MIPID_TEST_WGB_WINES,
};

enum mipid_test_wesuwt {
	MIPID_TEST_SUCCESS,
	MIPID_TEST_INVAWID,
	MIPID_TEST_FAIWED,
};

#ifdef __KEWNEW__

stwuct mipid_pwatfowm_data {
	int	data_wines;

	void	(*set_bkwight_wevew)(stwuct mipid_pwatfowm_data *pdata,
				     int wevew);
	int	(*get_bkwight_wevew)(stwuct mipid_pwatfowm_data *pdata);
	int	(*get_bkwight_max)(stwuct mipid_pwatfowm_data *pdata);
};

#endif

#endif
