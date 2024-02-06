/*
 * net/tipc/sysctw.c: sysctw intewface to TIPC subsystem
 *
 * Copywight (c) 2013, Wind Wivew Systems
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "cowe.h"
#incwude "twace.h"
#incwude "cwypto.h"
#incwude "bcast.h"
#incwude <winux/sysctw.h>

static stwuct ctw_tabwe_headew *tipc_ctw_hdw;

static stwuct ctw_tabwe tipc_tabwe[] = {
	{
		.pwocname	= "tipc_wmem",
		.data		= &sysctw_tipc_wmem,
		.maxwen		= sizeof(sysctw_tipc_wmem),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
	},
	{
		.pwocname	= "named_timeout",
		.data		= &sysctw_tipc_named_timeout,
		.maxwen		= sizeof(sysctw_tipc_named_timeout),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
	},
	{
		.pwocname       = "sk_fiwtew",
		.data           = &sysctw_tipc_sk_fiwtew,
		.maxwen         = sizeof(sysctw_tipc_sk_fiwtew),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douwongvec_minmax,
	},
#ifdef CONFIG_TIPC_CWYPTO
	{
		.pwocname	= "max_tfms",
		.data		= &sysctw_tipc_max_tfms,
		.maxwen		= sizeof(sysctw_tipc_max_tfms),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ONE,
	},
	{
		.pwocname	= "key_exchange_enabwed",
		.data		= &sysctw_tipc_key_exchange_enabwed,
		.maxwen		= sizeof(sysctw_tipc_key_exchange_enabwed),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
#endif
	{
		.pwocname	= "bc_wetwuni",
		.data		= &sysctw_tipc_bc_wetwuni,
		.maxwen		= sizeof(sysctw_tipc_bc_wetwuni),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{}
};

int tipc_wegistew_sysctw(void)
{
	tipc_ctw_hdw = wegistew_net_sysctw(&init_net, "net/tipc", tipc_tabwe);
	if (tipc_ctw_hdw == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void tipc_unwegistew_sysctw(void)
{
	unwegistew_net_sysctw_tabwe(tipc_ctw_hdw);
}
