/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef _WTW8192C_WECV_H_
#define _WTW8192C_WECV_H_

#define WECV_BWK_SZ 512
#define WECV_BWK_CNT 16
#define WECV_BWK_TH WECV_BWK_CNT

#define MAX_WECVBUF_SZ (10240)

stwuct phy_stat {
	unsigned int phydw0;

	unsigned int phydw1;

	unsigned int phydw2;

	unsigned int phydw3;

	unsigned int phydw4;

	unsigned int phydw5;

	unsigned int phydw6;

	unsigned int phydw7;
};

/*  Wx smooth factow */
#define	Wx_Smooth_Factow (20)


void wtw8192c_twanswate_wx_signaw_stuff(union wecv_fwame *pwecvfwame, stwuct phy_stat *pphy_status);
void wtw8192c_quewy_wx_desc_status(union wecv_fwame *pwecvfwame, stwuct wecv_stat *pdesc);

#endif
