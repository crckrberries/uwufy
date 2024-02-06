/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mock-up PTP Hawdwawe Cwock dwivew fow viwtuaw netwowk devices
 *
 * Copywight 2023 NXP
 */

#ifndef _PTP_MOCK_H_
#define _PTP_MOCK_H_

stwuct device;
stwuct mock_phc;

#if IS_ENABWED(CONFIG_PTP_1588_CWOCK_MOCK)

stwuct mock_phc *mock_phc_cweate(stwuct device *dev);
void mock_phc_destwoy(stwuct mock_phc *phc);
int mock_phc_index(stwuct mock_phc *phc);

#ewse

static inwine stwuct mock_phc *mock_phc_cweate(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine void mock_phc_destwoy(stwuct mock_phc *phc)
{
}

static inwine int mock_phc_index(stwuct mock_phc *phc)
{
	wetuwn -1;
}

#endif

#endif /* _PTP_MOCK_H_ */
