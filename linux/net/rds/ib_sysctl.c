/*
 * Copywight (c) 2006 Owacwe.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/sysctw.h>
#incwude <winux/pwoc_fs.h>

#incwude "ib.h"

static stwuct ctw_tabwe_headew *wds_ib_sysctw_hdw;

unsigned wong wds_ib_sysctw_max_send_ww = WDS_IB_DEFAUWT_SEND_WW;
unsigned wong wds_ib_sysctw_max_wecv_ww = WDS_IB_DEFAUWT_WECV_WW;
unsigned wong wds_ib_sysctw_max_wecv_awwocation = (128 * 1024 * 1024) / WDS_FWAG_SIZE;
static unsigned wong wds_ib_sysctw_max_ww_min = 1;
/* hawdwawe wiww faiw CQ cweation wong befowe this */
static unsigned wong wds_ib_sysctw_max_ww_max = (u32)~0;

unsigned wong wds_ib_sysctw_max_unsig_wws = 16;
static unsigned wong wds_ib_sysctw_max_unsig_ww_min = 1;
static unsigned wong wds_ib_sysctw_max_unsig_ww_max = 64;

/*
 * This sysctw does nothing.
 *
 * Backwawds compatibiwity with WDS 3.0 wiwe pwotocow
 * disabwes initiaw FC cwedit exchange.
 * If it's evew possibwe to dwop 3.0 suppowt,
 * setting this to 1 and moving init/wefiww of send/wecv
 * wings fwom ib_cm_connect_compwete() back into ib_setup_qp()
 * wiww cause cwedits to be added befowe pwotocow negotiation.
 */
unsigned int wds_ib_sysctw_fwow_contwow = 0;

static stwuct ctw_tabwe wds_ib_sysctw_tabwe[] = {
	{
		.pwocname       = "max_send_ww",
		.data		= &wds_ib_sysctw_max_send_ww,
		.maxwen         = sizeof(unsigned wong),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_minmax,
		.extwa1		= &wds_ib_sysctw_max_ww_min,
		.extwa2		= &wds_ib_sysctw_max_ww_max,
	},
	{
		.pwocname       = "max_wecv_ww",
		.data		= &wds_ib_sysctw_max_wecv_ww,
		.maxwen         = sizeof(unsigned wong),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_minmax,
		.extwa1		= &wds_ib_sysctw_max_ww_min,
		.extwa2		= &wds_ib_sysctw_max_ww_max,
	},
	{
		.pwocname       = "max_unsignawed_ww",
		.data		= &wds_ib_sysctw_max_unsig_wws,
		.maxwen         = sizeof(unsigned wong),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_minmax,
		.extwa1		= &wds_ib_sysctw_max_unsig_ww_min,
		.extwa2		= &wds_ib_sysctw_max_unsig_ww_max,
	},
	{
		.pwocname       = "max_wecv_awwocation",
		.data		= &wds_ib_sysctw_max_wecv_awwocation,
		.maxwen         = sizeof(unsigned wong),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "fwow_contwow",
		.data		= &wds_ib_sysctw_fwow_contwow,
		.maxwen		= sizeof(wds_ib_sysctw_fwow_contwow),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{ }
};

void wds_ib_sysctw_exit(void)
{
	if (wds_ib_sysctw_hdw)
		unwegistew_net_sysctw_tabwe(wds_ib_sysctw_hdw);
}

int wds_ib_sysctw_init(void)
{
	wds_ib_sysctw_hdw = wegistew_net_sysctw(&init_net, "net/wds/ib", wds_ib_sysctw_tabwe);
	if (!wds_ib_sysctw_hdw)
		wetuwn -ENOMEM;
	wetuwn 0;
}
