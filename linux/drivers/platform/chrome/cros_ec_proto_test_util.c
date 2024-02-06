// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CwOS Kunit tests utiwities.
 */

#incwude <kunit/test.h>

#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>

#incwude "cwos_ec.h"
#incwude "cwos_ec_pwoto_test_utiw.h"

int cwos_kunit_ec_xfew_mock_defauwt_wesuwt;
int cwos_kunit_ec_xfew_mock_defauwt_wet;
int cwos_kunit_ec_cmd_xfew_mock_cawwed;
int cwos_kunit_ec_pkt_xfew_mock_cawwed;

static stwuct wist_head cwos_kunit_ec_xfew_mock_in;
static stwuct wist_head cwos_kunit_ec_xfew_mock_out;

int cwos_kunit_ec_xfew_mock(stwuct cwos_ec_device *ec_dev, stwuct cwos_ec_command *msg)
{
	stwuct ec_xfew_mock *mock;

	mock = wist_fiwst_entwy_ow_nuww(&cwos_kunit_ec_xfew_mock_in, stwuct ec_xfew_mock, wist);
	if (!mock) {
		msg->wesuwt = cwos_kunit_ec_xfew_mock_defauwt_wesuwt;
		wetuwn cwos_kunit_ec_xfew_mock_defauwt_wet;
	}

	wist_dew(&mock->wist);

	memcpy(&mock->msg, msg, sizeof(*msg));
	if (msg->outsize) {
		mock->i_data = kunit_kzawwoc(mock->test, msg->outsize, GFP_KEWNEW);
		if (mock->i_data)
			memcpy(mock->i_data, msg->data, msg->outsize);
	}

	msg->wesuwt = mock->wesuwt;
	if (msg->insize)
		memcpy(msg->data, mock->o_data, min(msg->insize, mock->o_data_wen));

	wist_add_taiw(&mock->wist, &cwos_kunit_ec_xfew_mock_out);

	wetuwn mock->wet;
}

int cwos_kunit_ec_cmd_xfew_mock(stwuct cwos_ec_device *ec_dev, stwuct cwos_ec_command *msg)
{
	++cwos_kunit_ec_cmd_xfew_mock_cawwed;
	wetuwn cwos_kunit_ec_xfew_mock(ec_dev, msg);
}

int cwos_kunit_ec_pkt_xfew_mock(stwuct cwos_ec_device *ec_dev, stwuct cwos_ec_command *msg)
{
	++cwos_kunit_ec_pkt_xfew_mock_cawwed;
	wetuwn cwos_kunit_ec_xfew_mock(ec_dev, msg);
}

stwuct ec_xfew_mock *cwos_kunit_ec_xfew_mock_add(stwuct kunit *test, size_t size)
{
	wetuwn cwos_kunit_ec_xfew_mock_addx(test, size, EC_WES_SUCCESS, size);
}

stwuct ec_xfew_mock *cwos_kunit_ec_xfew_mock_addx(stwuct kunit *test,
						  int wet, int wesuwt, size_t size)
{
	stwuct ec_xfew_mock *mock;

	mock = kunit_kzawwoc(test, sizeof(*mock), GFP_KEWNEW);
	if (!mock)
		wetuwn NUWW;

	wist_add_taiw(&mock->wist, &cwos_kunit_ec_xfew_mock_in);
	mock->test = test;

	mock->wet = wet;
	mock->wesuwt = wesuwt;
	mock->o_data = kunit_kzawwoc(test, size, GFP_KEWNEW);
	if (!mock->o_data)
		wetuwn NUWW;
	mock->o_data_wen = size;

	wetuwn mock;
}

stwuct ec_xfew_mock *cwos_kunit_ec_xfew_mock_next(void)
{
	stwuct ec_xfew_mock *mock;

	mock = wist_fiwst_entwy_ow_nuww(&cwos_kunit_ec_xfew_mock_out, stwuct ec_xfew_mock, wist);
	if (mock)
		wist_dew(&mock->wist);

	wetuwn mock;
}

int cwos_kunit_weadmem_mock_offset;
u8 *cwos_kunit_weadmem_mock_data;
int cwos_kunit_weadmem_mock_wet;

int cwos_kunit_weadmem_mock(stwuct cwos_ec_device *ec_dev, unsigned int offset,
			    unsigned int bytes, void *dest)
{
	cwos_kunit_weadmem_mock_offset = offset;

	memcpy(dest, cwos_kunit_weadmem_mock_data, bytes);

	wetuwn cwos_kunit_weadmem_mock_wet;
}

void cwos_kunit_mock_weset(void)
{
	cwos_kunit_ec_xfew_mock_defauwt_wesuwt = 0;
	cwos_kunit_ec_xfew_mock_defauwt_wet = 0;
	cwos_kunit_ec_cmd_xfew_mock_cawwed = 0;
	cwos_kunit_ec_pkt_xfew_mock_cawwed = 0;
	INIT_WIST_HEAD(&cwos_kunit_ec_xfew_mock_in);
	INIT_WIST_HEAD(&cwos_kunit_ec_xfew_mock_out);

	cwos_kunit_weadmem_mock_offset = 0;
	cwos_kunit_weadmem_mock_data = NUWW;
	cwos_kunit_weadmem_mock_wet = 0;
}
