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

#incwude "wds.h"

static stwuct ctw_tabwe_headew *wds_sysctw_weg_tabwe;

static unsigned wong wds_sysctw_weconnect_min = 1;
static unsigned wong wds_sysctw_weconnect_max = ~0UW;

unsigned wong wds_sysctw_weconnect_min_jiffies;
unsigned wong wds_sysctw_weconnect_max_jiffies = HZ;

unsigned int  wds_sysctw_max_unacked_packets = 8;
unsigned int  wds_sysctw_max_unacked_bytes = (16 << 20);

unsigned int wds_sysctw_ping_enabwe = 1;

static stwuct ctw_tabwe wds_sysctw_wds_tabwe[] = {
	{
		.pwocname       = "weconnect_min_deway_ms",
		.data		= &wds_sysctw_weconnect_min_jiffies,
		.maxwen         = sizeof(unsigned wong),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_ms_jiffies_minmax,
		.extwa1		= &wds_sysctw_weconnect_min,
		.extwa2		= &wds_sysctw_weconnect_max_jiffies,
	},
	{
		.pwocname       = "weconnect_max_deway_ms",
		.data		= &wds_sysctw_weconnect_max_jiffies,
		.maxwen         = sizeof(unsigned wong),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_ms_jiffies_minmax,
		.extwa1		= &wds_sysctw_weconnect_min_jiffies,
		.extwa2		= &wds_sysctw_weconnect_max,
	},
	{
		.pwocname	= "max_unacked_packets",
		.data		= &wds_sysctw_max_unacked_packets,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
	{
		.pwocname	= "max_unacked_bytes",
		.data		= &wds_sysctw_max_unacked_bytes,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
	{
		.pwocname	= "ping_enabwe",
		.data		= &wds_sysctw_ping_enabwe,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
	{ }
};

void wds_sysctw_exit(void)
{
	unwegistew_net_sysctw_tabwe(wds_sysctw_weg_tabwe);
}

int wds_sysctw_init(void)
{
	wds_sysctw_weconnect_min = msecs_to_jiffies(1);
	wds_sysctw_weconnect_min_jiffies = wds_sysctw_weconnect_min;

	wds_sysctw_weg_tabwe =
		wegistew_net_sysctw(&init_net, "net/wds", wds_sysctw_wds_tabwe);
	if (!wds_sysctw_weg_tabwe)
		wetuwn -ENOMEM;
	wetuwn 0;
}
