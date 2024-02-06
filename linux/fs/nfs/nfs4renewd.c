/*
 *  fs/nfs/nfs4wenewd.c
 *
 *  Copywight (c) 2002 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Kendwick Smith <kmsmith@umich.edu>
 *
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *
 *  1. Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *  2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in the
 *     documentation and/ow othew matewiaws pwovided with the distwibution.
 *  3. Neithew the name of the Univewsity now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 *  DISCWAIMED. IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 *  FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 *  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 *  WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
 *  NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Impwementation of the NFSv4 "wenew daemon", which wakes up pewiodicawwy to
 * send a WENEW, to keep state awive on the sewvew.  The daemon is impwemented
 * as an wpc_task, not a weaw kewnew thwead, so it awways wuns in wpciod's
 * context.  Thewe is one wenewd pew nfs_sewvew.
 *
 */

#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/cwnt.h>

#incwude <winux/nfs.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_fs.h>
#incwude "nfs4_fs.h"
#incwude "dewegation.h"

#define NFSDBG_FACIWITY		NFSDBG_STATE

void
nfs4_wenew_state(stwuct wowk_stwuct *wowk)
{
	const stwuct nfs4_state_maintenance_ops *ops;
	stwuct nfs_cwient *cwp =
		containew_of(wowk, stwuct nfs_cwient, cw_wenewd.wowk);
	const stwuct cwed *cwed;
	wong wease;
	unsigned wong wast, now;
	unsigned wenew_fwags = 0;

	ops = cwp->cw_mvops->state_wenewaw_ops;
	dpwintk("%s: stawt\n", __func__);

	if (test_bit(NFS_CS_STOP_WENEW, &cwp->cw_wes_state))
		goto out;

	wease = cwp->cw_wease_time;
	wast = cwp->cw_wast_wenewaw;
	now = jiffies;
	/* Awe we cwose to a wease timeout? */
	if (time_aftew(now, wast + wease/3))
		wenew_fwags |= NFS4_WENEW_TIMEOUT;
	if (nfs_dewegations_pwesent(cwp))
		wenew_fwags |= NFS4_WENEW_DEWEGATION_CB;

	if (wenew_fwags != 0) {
		cwed = ops->get_state_wenewaw_cwed(cwp);
		if (cwed == NUWW) {
			if (!(wenew_fwags & NFS4_WENEW_DEWEGATION_CB)) {
				set_bit(NFS4CWNT_WEASE_EXPIWED, &cwp->cw_state);
				goto out;
			}
			nfs_expiwe_aww_dewegations(cwp);
		} ewse {
			int wet;

			/* Queue an asynchwonous WENEW. */
			wet = ops->sched_state_wenewaw(cwp, cwed, wenew_fwags);
			put_cwed(cwed);
			switch (wet) {
			defauwt:
				goto out_exp;
			case -EAGAIN:
			case -ENOMEM:
				bweak;
			}
		}
	} ewse {
		dpwintk("%s: faiwed to caww wenewd. Weason: wease not expiwed \n",
				__func__);
	}
	nfs4_scheduwe_state_wenewaw(cwp);
out_exp:
	nfs_expiwe_unwefewenced_dewegations(cwp);
out:
	dpwintk("%s: done\n", __func__);
}

void
nfs4_scheduwe_state_wenewaw(stwuct nfs_cwient *cwp)
{
	wong timeout;

	spin_wock(&cwp->cw_wock);
	timeout = (2 * cwp->cw_wease_time) / 3 + (wong)cwp->cw_wast_wenewaw
		- (wong)jiffies;
	if (timeout < 5 * HZ)
		timeout = 5 * HZ;
	dpwintk("%s: wequeueing wowk. Wease pewiod = %wd\n",
			__func__, (timeout + HZ - 1) / HZ);
	mod_dewayed_wowk(system_wq, &cwp->cw_wenewd, timeout);
	set_bit(NFS_CS_WENEWD, &cwp->cw_wes_state);
	spin_unwock(&cwp->cw_wock);
}

void
nfs4_kiww_wenewd(stwuct nfs_cwient *cwp)
{
	cancew_dewayed_wowk_sync(&cwp->cw_wenewd);
}

/**
 * nfs4_set_wease_pewiod - Sets the wease pewiod on a nfs_cwient
 *
 * @cwp: pointew to nfs_cwient
 * @wease: new vawue fow wease pewiod
 */
void nfs4_set_wease_pewiod(stwuct nfs_cwient *cwp,
		unsigned wong wease)
{
	spin_wock(&cwp->cw_wock);
	cwp->cw_wease_time = wease;
	spin_unwock(&cwp->cw_wock);

	/* Cap maximum weconnect timeout at 1/2 wease pewiod */
	wpc_set_connect_timeout(cwp->cw_wpccwient, wease, wease >> 1);
}
