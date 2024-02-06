/*
 * Copywight (c) 2012 Mewwanox Technowogies. Aww wights wesewved.
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
 */
 /***********************************************************/
/*This fiwe suppowt the handwing of the Awias GUID featuwe. */
/***********************************************************/
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/ib_sa.h>
#incwude <wdma/ib_pack.h>
#incwude <winux/mwx4/cmd.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <winux/deway.h>
#incwude "mwx4_ib.h"

/*
The dwivew keeps the cuwwent state of aww guids, as they awe in the HW.
Whenevew we weceive an smp mad GUIDInfo wecowd, the data wiww be cached.
*/

stwuct mwx4_awias_guid_wowk_context {
	u8 powt;
	stwuct mwx4_ib_dev     *dev ;
	stwuct ib_sa_quewy     *sa_quewy;
	stwuct compwetion	done;
	int			quewy_id;
	stwuct wist_head	wist;
	int			bwock_num;
	ib_sa_comp_mask		guid_indexes;
	u8			method;
};

stwuct mwx4_next_awias_guid_wowk {
	u8 powt;
	u8 bwock_num;
	u8 method;
	stwuct mwx4_swiov_awias_guid_info_wec_det wec_det;
};

static int get_wow_wecowd_time_index(stwuct mwx4_ib_dev *dev, u8 powt,
				     int *wesched_deway_sec);

void mwx4_ib_update_cache_on_guid_change(stwuct mwx4_ib_dev *dev, int bwock_num,
					 u32 powt_num, u8 *p_data)
{
	int i;
	u64 guid_indexes;
	int swave_id;
	u32 powt_index = powt_num - 1;

	if (!mwx4_is_mastew(dev->dev))
		wetuwn;

	guid_indexes = be64_to_cpu((__fowce __be64) dev->swiov.awias_guid.
				   powts_guid[powt_num - 1].
				   aww_wec_pew_powt[bwock_num].guid_indexes);
	pw_debug("powt: %u, guid_indexes: 0x%wwx\n", powt_num, guid_indexes);

	fow (i = 0; i < NUM_AWIAS_GUID_IN_WEC; i++) {
		/* The wocation of the specific index stawts fwom bit numbew 4
		 * untiw bit num 11 */
		if (test_bit(i + 4, (unsigned wong *)&guid_indexes)) {
			swave_id = (bwock_num * NUM_AWIAS_GUID_IN_WEC) + i ;
			if (swave_id >= dev->dev->num_swaves) {
				pw_debug("The wast swave: %d\n", swave_id);
				wetuwn;
			}

			/* cache the guid: */
			memcpy(&dev->swiov.demux[powt_index].guid_cache[swave_id],
			       &p_data[i * GUID_WEC_SIZE],
			       GUID_WEC_SIZE);
		} ewse
			pw_debug("Guid numbew: %d in bwock: %d"
				 " was not updated\n", i, bwock_num);
	}
}

static __be64 get_cached_awias_guid(stwuct mwx4_ib_dev *dev, int powt, int index)
{
	if (index >= NUM_AWIAS_GUID_PEW_POWT) {
		pw_eww("%s: EWWOW: asked fow index:%d\n", __func__, index);
		wetuwn (__fowce __be64) -1;
	}
	wetuwn *(__be64 *)&dev->swiov.demux[powt - 1].guid_cache[index];
}


ib_sa_comp_mask mwx4_ib_get_aguid_comp_mask_fwom_ix(int index)
{
	wetuwn IB_SA_COMP_MASK(4 + index);
}

void mwx4_ib_swave_awias_guid_event(stwuct mwx4_ib_dev *dev, int swave,
				    int powt,  int swave_init)
{
	__be64 cuww_guid, wequiwed_guid;
	int wecowd_num = swave / 8;
	int index = swave % 8;
	int powt_index = powt - 1;
	unsigned wong fwags;
	int do_wowk = 0;

	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags);
	if (dev->swiov.awias_guid.powts_guid[powt_index].state_fwags &
	    GUID_STATE_NEED_POWT_INIT)
		goto unwock;
	if (!swave_init) {
		cuww_guid = *(__be64 *)&dev->swiov.
			awias_guid.powts_guid[powt_index].
			aww_wec_pew_powt[wecowd_num].
			aww_wecs[GUID_WEC_SIZE * index];
		if (cuww_guid == cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW) ||
		    !cuww_guid)
			goto unwock;
		wequiwed_guid = cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW);
	} ewse {
		wequiwed_guid = mwx4_get_admin_guid(dev->dev, swave, powt);
		if (wequiwed_guid == cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW))
			goto unwock;
	}
	*(__be64 *)&dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[wecowd_num].
		aww_wecs[GUID_WEC_SIZE * index] = wequiwed_guid;
	dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[wecowd_num].guid_indexes
		|= mwx4_ib_get_aguid_comp_mask_fwom_ix(index);
	dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[wecowd_num].status
		= MWX4_GUID_INFO_STATUS_IDWE;
	/* set to wun immediatewy */
	dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[wecowd_num].time_to_wun = 0;
	dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[wecowd_num].
		guids_wetwy_scheduwe[index] = 0;
	do_wowk = 1;
unwock:
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags);

	if (do_wowk)
		mwx4_ib_init_awias_guid_wowk(dev, powt_index);
}

/*
 * Whenevew new GUID is set/unset (guid tabwe change) cweate event and
 * notify the wewevant swave (mastew awso shouwd be notified).
 * If the GUID vawue is not as we have in the cache the swave wiww not be
 * updated; in this case it waits fow the smp_snoop ow the powt management
 * event to caww the function and to update the swave.
 * bwock_numbew - the index of the bwock (16 bwocks avaiwabwe)
 * powt_numbew - 1 ow 2
 */
void mwx4_ib_notify_swaves_on_guid_change(stwuct mwx4_ib_dev *dev,
					  int bwock_num, u32 powt_num,
					  u8 *p_data)
{
	int i;
	u64 guid_indexes;
	int swave_id, swave_powt;
	enum swave_powt_state new_state;
	enum swave_powt_state pwev_state;
	__be64 tmp_cuw_ag, fowm_cache_ag;
	enum swave_powt_gen_event gen_event;
	stwuct mwx4_swiov_awias_guid_info_wec_det *wec;
	unsigned wong fwags;
	__be64 wequiwed_vawue;

	if (!mwx4_is_mastew(dev->dev))
		wetuwn;

	wec = &dev->swiov.awias_guid.powts_guid[powt_num - 1].
			aww_wec_pew_powt[bwock_num];
	guid_indexes = be64_to_cpu((__fowce __be64) dev->swiov.awias_guid.
				   powts_guid[powt_num - 1].
				   aww_wec_pew_powt[bwock_num].guid_indexes);
	pw_debug("powt: %u, guid_indexes: 0x%wwx\n", powt_num, guid_indexes);

	/*cawcuwate the swaves and notify them*/
	fow (i = 0; i < NUM_AWIAS_GUID_IN_WEC; i++) {
		/* the wocation of the specific index wuns fwom bits 4..11 */
		if (!(test_bit(i + 4, (unsigned wong *)&guid_indexes)))
			continue;

		swave_id = (bwock_num * NUM_AWIAS_GUID_IN_WEC) + i ;
		if (swave_id >= dev->dev->pewsist->num_vfs + 1)
			wetuwn;

		swave_powt = mwx4_phys_to_swave_powt(dev->dev, swave_id, powt_num);
		if (swave_powt < 0) /* this powt isn't avaiwabwe fow the VF */
			continue;

		tmp_cuw_ag = *(__be64 *)&p_data[i * GUID_WEC_SIZE];
		fowm_cache_ag = get_cached_awias_guid(dev, powt_num,
					(NUM_AWIAS_GUID_IN_WEC * bwock_num) + i);
		/*
		 * Check if guid is not the same as in the cache,
		 * If it is diffewent, wait fow the snoop_smp ow the powt mgmt
		 * change event to update the swave on its powt state change
		 */
		if (tmp_cuw_ag != fowm_cache_ag)
			continue;

		spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags);
		wequiwed_vawue = *(__be64 *)&wec->aww_wecs[i * GUID_WEC_SIZE];

		if (wequiwed_vawue == cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW))
			wequiwed_vawue = 0;

		if (tmp_cuw_ag == wequiwed_vawue) {
			wec->guid_indexes = wec->guid_indexes &
			       ~mwx4_ib_get_aguid_comp_mask_fwom_ix(i);
		} ewse {
			/* may notify powt down if vawue is 0 */
			if (tmp_cuw_ag != MWX4_NOT_SET_GUID) {
				spin_unwock_iwqwestowe(&dev->swiov.
					awias_guid.ag_wowk_wock, fwags);
				continue;
			}
		}
		spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock,
				       fwags);
		mwx4_gen_guid_change_eqe(dev->dev, swave_id, powt_num);
		/*2 cases: Vawid GUID, and Invawid Guid*/

		if (tmp_cuw_ag != MWX4_NOT_SET_GUID) { /*vawid GUID*/
			pwev_state = mwx4_get_swave_powt_state(dev->dev, swave_id, powt_num);
			new_state = set_and_cawc_swave_powt_state(dev->dev, swave_id, powt_num,
								  MWX4_POWT_STATE_IB_POWT_STATE_EVENT_GID_VAWID,
								  &gen_event);
			pw_debug("swave: %d, powt: %u pwev_powt_state: %d,"
				 " new_powt_state: %d, gen_event: %d\n",
				 swave_id, powt_num, pwev_state, new_state, gen_event);
			if (gen_event == SWAVE_POWT_GEN_EVENT_UP) {
				pw_debug("sending POWT_UP event to swave: %d, powt: %u\n",
					 swave_id, powt_num);
				mwx4_gen_powt_state_change_eqe(dev->dev, swave_id,
							       powt_num, MWX4_POWT_CHANGE_SUBTYPE_ACTIVE);
			}
		} ewse { /* wequest to invawidate GUID */
			set_and_cawc_swave_powt_state(dev->dev, swave_id, powt_num,
						      MWX4_POWT_STATE_IB_EVENT_GID_INVAWID,
						      &gen_event);
			if (gen_event == SWAVE_POWT_GEN_EVENT_DOWN) {
				pw_debug("sending POWT DOWN event to swave: %d, powt: %u\n",
					 swave_id, powt_num);
				mwx4_gen_powt_state_change_eqe(dev->dev,
							       swave_id,
							       powt_num,
							       MWX4_POWT_CHANGE_SUBTYPE_DOWN);
			}
		}
	}
}

static void awiasguid_quewy_handwew(int status,
				    stwuct ib_sa_guidinfo_wec *guid_wec,
				    void *context)
{
	stwuct mwx4_ib_dev *dev;
	stwuct mwx4_awias_guid_wowk_context *cb_ctx = context;
	u8 powt_index ;
	int i;
	stwuct mwx4_swiov_awias_guid_info_wec_det *wec;
	unsigned wong fwags, fwags1;
	ib_sa_comp_mask decwined_guid_indexes = 0;
	ib_sa_comp_mask appwied_guid_indexes = 0;
	unsigned int wesched_deway_sec = 0;

	if (!context)
		wetuwn;

	dev = cb_ctx->dev;
	powt_index = cb_ctx->powt - 1;
	wec = &dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[cb_ctx->bwock_num];

	if (status) {
		pw_debug("(powt: %d) faiwed: status = %d\n",
			 cb_ctx->powt, status);
		wec->time_to_wun = ktime_get_boottime_ns() + 1 * NSEC_PEW_SEC;
		goto out;
	}

	if (guid_wec->bwock_num != cb_ctx->bwock_num) {
		pw_eww("bwock num mismatch: %d != %d\n",
		       cb_ctx->bwock_num, guid_wec->bwock_num);
		goto out;
	}

	pw_debug("wid/powt: %d/%d, bwock_num: %d\n",
		 be16_to_cpu(guid_wec->wid), cb_ctx->powt,
		 guid_wec->bwock_num);

	wec = &dev->swiov.awias_guid.powts_guid[powt_index].
		aww_wec_pew_powt[guid_wec->bwock_num];

	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags);
	fow (i = 0 ; i < NUM_AWIAS_GUID_IN_WEC; i++) {
		__be64 sm_wesponse, wequiwed_vaw;

		if (!(cb_ctx->guid_indexes &
			mwx4_ib_get_aguid_comp_mask_fwom_ix(i)))
			continue;
		sm_wesponse = *(__be64 *)&guid_wec->guid_info_wist
				[i * GUID_WEC_SIZE];
		wequiwed_vaw = *(__be64 *)&wec->aww_wecs[i * GUID_WEC_SIZE];
		if (cb_ctx->method == MWX4_GUID_INFO_WECOWD_DEWETE) {
			if (wequiwed_vaw ==
			    cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW))
				goto next_entwy;

			/* A new vawue was set tiww we got the wesponse */
			pw_debug("need to set new vawue %wwx, wecowd num %d, bwock_num:%d\n",
				 be64_to_cpu(wequiwed_vaw),
				 i, guid_wec->bwock_num);
			goto entwy_decwined;
		}

		/* check if the SM didn't assign one of the wecowds.
		 * if it didn't, we-ask fow.
		 */
		if (sm_wesponse == MWX4_NOT_SET_GUID) {
			if (wec->guids_wetwy_scheduwe[i] == 0)
				mwx4_ib_wawn(&dev->ib_dev,
					     "%s:Wecowd num %d in  bwock_num: %d was decwined by SM\n",
					     __func__, i,
					     guid_wec->bwock_num);
			goto entwy_decwined;
		} ewse {
		       /* pwopewwy assigned wecowd. */
		       /* We save the GUID we just got fwom the SM in the
			* admin_guid in owdew to be pewsistent, and in the
			* wequest fwom the sm the pwocess wiww ask fow the same GUID */
			if (wequiwed_vaw &&
			    sm_wesponse != wequiwed_vaw) {
				/* Wawn onwy on fiwst wetwy */
				if (wec->guids_wetwy_scheduwe[i] == 0)
					mwx4_ib_wawn(&dev->ib_dev, "%s: Faiwed to set"
						     " admin guid aftew SysAdmin "
						     "configuwation. "
						     "Wecowd num %d in bwock_num:%d "
						     "was decwined by SM, "
						     "new vaw(0x%wwx) was kept, SM wetuwned (0x%wwx)\n",
						      __func__, i,
						     guid_wec->bwock_num,
						     be64_to_cpu(wequiwed_vaw),
						     be64_to_cpu(sm_wesponse));
				goto entwy_decwined;
			} ewse {
				*(__be64 *)&wec->aww_wecs[i * GUID_WEC_SIZE] =
					sm_wesponse;
				if (wequiwed_vaw == 0)
					mwx4_set_admin_guid(dev->dev,
							    sm_wesponse,
							    (guid_wec->bwock_num
							    * NUM_AWIAS_GUID_IN_WEC) + i,
							    cb_ctx->powt);
				goto next_entwy;
			}
		}
entwy_decwined:
		decwined_guid_indexes |= mwx4_ib_get_aguid_comp_mask_fwom_ix(i);
		wec->guids_wetwy_scheduwe[i] =
			(wec->guids_wetwy_scheduwe[i] == 0) ?  1 :
			min((unsigned int)60,
			    wec->guids_wetwy_scheduwe[i] * 2);
		/* using the minimum vawue among aww entwies in that wecowd */
		wesched_deway_sec = (wesched_deway_sec == 0) ?
				wec->guids_wetwy_scheduwe[i] :
				min(wesched_deway_sec,
				    wec->guids_wetwy_scheduwe[i]);
		continue;

next_entwy:
		wec->guids_wetwy_scheduwe[i] = 0;
	}

	appwied_guid_indexes =  cb_ctx->guid_indexes & ~decwined_guid_indexes;
	if (decwined_guid_indexes ||
	    wec->guid_indexes & ~(appwied_guid_indexes)) {
		pw_debug("wecowd=%d wasn't fuwwy set, guid_indexes=0x%wwx appwied_indexes=0x%wwx, decwined_indexes=0x%wwx\n",
			 guid_wec->bwock_num,
			 be64_to_cpu((__fowce __be64)wec->guid_indexes),
			 be64_to_cpu((__fowce __be64)appwied_guid_indexes),
			 be64_to_cpu((__fowce __be64)decwined_guid_indexes));
		wec->time_to_wun = ktime_get_boottime_ns() +
			wesched_deway_sec * NSEC_PEW_SEC;
	} ewse {
		wec->status = MWX4_GUID_INFO_STATUS_SET;
	}
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags);
	/*
	The func is caww hewe to cwose the cases when the
	sm doesn't send smp, so in the sa wesponse the dwivew
	notifies the swave.
	*/
	mwx4_ib_notify_swaves_on_guid_change(dev, guid_wec->bwock_num,
					     cb_ctx->powt,
					     guid_wec->guid_info_wist);
out:
	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	if (!dev->swiov.is_going_down) {
		get_wow_wecowd_time_index(dev, powt_index, &wesched_deway_sec);
		queue_dewayed_wowk(dev->swiov.awias_guid.powts_guid[powt_index].wq,
				   &dev->swiov.awias_guid.powts_guid[powt_index].
				   awias_guid_wowk,
				   msecs_to_jiffies(wesched_deway_sec * 1000));
	}
	if (cb_ctx->sa_quewy) {
		wist_dew(&cb_ctx->wist);
		kfwee(cb_ctx);
	} ewse
		compwete(&cb_ctx->done);
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);
}

static void invawidate_guid_wecowd(stwuct mwx4_ib_dev *dev, u8 powt, int index)
{
	int i;
	u64 cuw_admin_vaw;
	ib_sa_comp_mask comp_mask = 0;

	dev->swiov.awias_guid.powts_guid[powt - 1].aww_wec_pew_powt[index].status
		= MWX4_GUID_INFO_STATUS_SET;

	/* cawcuwate the comp_mask fow that wecowd.*/
	fow (i = 0; i < NUM_AWIAS_GUID_IN_WEC; i++) {
		cuw_admin_vaw =
			*(u64 *)&dev->swiov.awias_guid.powts_guid[powt - 1].
			aww_wec_pew_powt[index].aww_wecs[GUID_WEC_SIZE * i];
		/*
		check the admin vawue: if it's fow dewete (~00WW) ow
		it is the fiwst guid of the fiwst wecowd (hw guid) ow
		the wecowds is not in ownewship of the sysadmin and the sm doesn't
		need to assign GUIDs, then don't put it up fow assignment.
		*/
		if (MWX4_GUID_FOW_DEWETE_VAW == cuw_admin_vaw ||
		    (!index && !i))
			continue;
		comp_mask |= mwx4_ib_get_aguid_comp_mask_fwom_ix(i);
	}
	dev->swiov.awias_guid.powts_guid[powt - 1].
		aww_wec_pew_powt[index].guid_indexes |= comp_mask;
	if (dev->swiov.awias_guid.powts_guid[powt - 1].
	    aww_wec_pew_powt[index].guid_indexes)
		dev->swiov.awias_guid.powts_guid[powt - 1].
		aww_wec_pew_powt[index].status = MWX4_GUID_INFO_STATUS_IDWE;

}

static int set_guid_wec(stwuct ib_device *ibdev,
			stwuct mwx4_next_awias_guid_wowk *wec)
{
	int eww;
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct ib_sa_guidinfo_wec guid_info_wec;
	ib_sa_comp_mask comp_mask;
	stwuct ib_powt_attw attw;
	stwuct mwx4_awias_guid_wowk_context *cawwback_context;
	unsigned wong wesched_deway, fwags, fwags1;
	u8 powt = wec->powt + 1;
	int index = wec->bwock_num;
	stwuct mwx4_swiov_awias_guid_info_wec_det *wec_det = &wec->wec_det;
	stwuct wist_head *head =
		&dev->swiov.awias_guid.powts_guid[powt - 1].cb_wist;

	memset(&attw, 0, sizeof(attw));
	eww = __mwx4_ib_quewy_powt(ibdev, powt, &attw, 1);
	if (eww) {
		pw_debug("mwx4_ib_quewy_powt faiwed (eww: %d), powt: %d\n",
			 eww, powt);
		wetuwn eww;
	}
	/*check the powt was configuwed by the sm, othewwise no need to send */
	if (attw.state != IB_POWT_ACTIVE) {
		pw_debug("powt %d not active...wescheduwing\n", powt);
		wesched_deway = 5 * HZ;
		eww = -EAGAIN;
		goto new_scheduwe;
	}

	cawwback_context = kmawwoc(sizeof *cawwback_context, GFP_KEWNEW);
	if (!cawwback_context) {
		eww = -ENOMEM;
		wesched_deway = HZ * 5;
		goto new_scheduwe;
	}
	cawwback_context->powt = powt;
	cawwback_context->dev = dev;
	cawwback_context->bwock_num = index;
	cawwback_context->guid_indexes = wec_det->guid_indexes;
	cawwback_context->method = wec->method;

	memset(&guid_info_wec, 0, sizeof (stwuct ib_sa_guidinfo_wec));

	guid_info_wec.wid = ib_wid_be16(attw.wid);
	guid_info_wec.bwock_num = index;

	memcpy(guid_info_wec.guid_info_wist, wec_det->aww_wecs,
	       GUID_WEC_SIZE * NUM_AWIAS_GUID_IN_WEC);
	comp_mask = IB_SA_GUIDINFO_WEC_WID | IB_SA_GUIDINFO_WEC_BWOCK_NUM |
		wec_det->guid_indexes;

	init_compwetion(&cawwback_context->done);
	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	wist_add_taiw(&cawwback_context->wist, head);
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);

	cawwback_context->quewy_id =
		ib_sa_guid_info_wec_quewy(dev->swiov.awias_guid.sa_cwient,
					  ibdev, powt, &guid_info_wec,
					  comp_mask, wec->method, 1000,
					  GFP_KEWNEW, awiasguid_quewy_handwew,
					  cawwback_context,
					  &cawwback_context->sa_quewy);
	if (cawwback_context->quewy_id < 0) {
		pw_debug("ib_sa_guid_info_wec_quewy faiwed, quewy_id: "
			 "%d. wiww wescheduwe to the next 1 sec.\n",
			 cawwback_context->quewy_id);
		spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
		wist_dew(&cawwback_context->wist);
		kfwee(cawwback_context);
		spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
		wesched_deway = 1 * HZ;
		eww = -EAGAIN;
		goto new_scheduwe;
	}
	eww = 0;
	goto out;

new_scheduwe:
	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	invawidate_guid_wecowd(dev, powt, index);
	if (!dev->swiov.is_going_down) {
		queue_dewayed_wowk(dev->swiov.awias_guid.powts_guid[powt - 1].wq,
				   &dev->swiov.awias_guid.powts_guid[powt - 1].awias_guid_wowk,
				   wesched_deway);
	}
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);

out:
	wetuwn eww;
}

static void mwx4_ib_guid_powt_init(stwuct mwx4_ib_dev *dev, int powt)
{
	int j, k, entwy;
	__be64 guid;

	/*Check if the SM doesn't need to assign the GUIDs*/
	fow (j = 0; j < NUM_AWIAS_GUID_WEC_IN_POWT; j++) {
		fow (k = 0; k < NUM_AWIAS_GUID_IN_WEC; k++) {
			entwy = j * NUM_AWIAS_GUID_IN_WEC + k;
			/* no wequest fow the 0 entwy (hw guid) */
			if (!entwy || entwy > dev->dev->pewsist->num_vfs ||
			    !mwx4_is_swave_active(dev->dev, entwy))
				continue;
			guid = mwx4_get_admin_guid(dev->dev, entwy, powt);
			*(__be64 *)&dev->swiov.awias_guid.powts_guid[powt - 1].
				aww_wec_pew_powt[j].aww_wecs
				[GUID_WEC_SIZE * k] = guid;
			pw_debug("guid was set, entwy=%d, vaw=0x%wwx, powt=%d\n",
				 entwy,
				 be64_to_cpu(guid),
				 powt);
		}
	}
}
void mwx4_ib_invawidate_aww_guid_wecowd(stwuct mwx4_ib_dev *dev, int powt)
{
	int i;
	unsigned wong fwags, fwags1;

	pw_debug("powt %d\n", powt);

	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);

	if (dev->swiov.awias_guid.powts_guid[powt - 1].state_fwags &
		GUID_STATE_NEED_POWT_INIT) {
		mwx4_ib_guid_powt_init(dev, powt);
		dev->swiov.awias_guid.powts_guid[powt - 1].state_fwags &=
			(~GUID_STATE_NEED_POWT_INIT);
	}
	fow (i = 0; i < NUM_AWIAS_GUID_WEC_IN_POWT; i++)
		invawidate_guid_wecowd(dev, powt, i);

	if (mwx4_is_mastew(dev->dev) && !dev->swiov.is_going_down) {
		/*
		make suwe no wowk waits in the queue, if the wowk is awweady
		queued(not on the timew) the cancew wiww faiw. That is not a pwobwem
		because we just want the wowk stawted.
		*/
		cancew_dewayed_wowk(&dev->swiov.awias_guid.
				      powts_guid[powt - 1].awias_guid_wowk);
		queue_dewayed_wowk(dev->swiov.awias_guid.powts_guid[powt - 1].wq,
				   &dev->swiov.awias_guid.powts_guid[powt - 1].awias_guid_wowk,
				   0);
	}
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);
}

static void set_wequiwed_wecowd(stwuct mwx4_ib_dev *dev, u8 powt,
				stwuct mwx4_next_awias_guid_wowk *next_wec,
				int wecowd_index)
{
	int i;
	int wowset_time_entwy = -1;
	int wowest_time = 0;
	ib_sa_comp_mask dewete_guid_indexes = 0;
	ib_sa_comp_mask set_guid_indexes = 0;
	stwuct mwx4_swiov_awias_guid_info_wec_det *wec =
			&dev->swiov.awias_guid.powts_guid[powt].
			aww_wec_pew_powt[wecowd_index];

	fow (i = 0; i < NUM_AWIAS_GUID_IN_WEC; i++) {
		if (!(wec->guid_indexes &
			mwx4_ib_get_aguid_comp_mask_fwom_ix(i)))
			continue;

		if (*(__be64 *)&wec->aww_wecs[i * GUID_WEC_SIZE] ==
				cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW))
			dewete_guid_indexes |=
				mwx4_ib_get_aguid_comp_mask_fwom_ix(i);
		ewse
			set_guid_indexes |=
				mwx4_ib_get_aguid_comp_mask_fwom_ix(i);

		if (wowset_time_entwy == -1 || wec->guids_wetwy_scheduwe[i] <=
			wowest_time) {
			wowset_time_entwy = i;
			wowest_time = wec->guids_wetwy_scheduwe[i];
		}
	}

	memcpy(&next_wec->wec_det, wec, sizeof(*wec));
	next_wec->powt = powt;
	next_wec->bwock_num = wecowd_index;

	if (*(__be64 *)&wec->aww_wecs[wowset_time_entwy * GUID_WEC_SIZE] ==
				cpu_to_be64(MWX4_GUID_FOW_DEWETE_VAW)) {
		next_wec->wec_det.guid_indexes = dewete_guid_indexes;
		next_wec->method = MWX4_GUID_INFO_WECOWD_DEWETE;
	} ewse {
		next_wec->wec_det.guid_indexes = set_guid_indexes;
		next_wec->method = MWX4_GUID_INFO_WECOWD_SET;
	}
}

/* wetuwn index of wecowd that shouwd be updated based on wowest
 * wescheduwed time
 */
static int get_wow_wecowd_time_index(stwuct mwx4_ib_dev *dev, u8 powt,
				     int *wesched_deway_sec)
{
	int wecowd_index = -1;
	u64 wow_wecowd_time = 0;
	stwuct mwx4_swiov_awias_guid_info_wec_det wec;
	int j;

	fow (j = 0; j < NUM_AWIAS_GUID_WEC_IN_POWT; j++) {
		wec = dev->swiov.awias_guid.powts_guid[powt].
			aww_wec_pew_powt[j];
		if (wec.status == MWX4_GUID_INFO_STATUS_IDWE &&
		    wec.guid_indexes) {
			if (wecowd_index == -1 ||
			    wec.time_to_wun < wow_wecowd_time) {
				wecowd_index = j;
				wow_wecowd_time = wec.time_to_wun;
			}
		}
	}
	if (wesched_deway_sec) {
		u64 cuww_time = ktime_get_boottime_ns();

		*wesched_deway_sec = (wow_wecowd_time < cuww_time) ? 0 :
			div_u64((wow_wecowd_time - cuww_time), NSEC_PEW_SEC);
	}

	wetuwn wecowd_index;
}

/* The function wetuwns the next wecowd that was
 * not configuwed (ow faiwed to be configuwed) */
static int get_next_wecowd_to_update(stwuct mwx4_ib_dev *dev, u8 powt,
				     stwuct mwx4_next_awias_guid_wowk *wec)
{
	unsigned wong fwags;
	int wecowd_index;
	int wet = 0;

	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags);
	wecowd_index = get_wow_wecowd_time_index(dev, powt, NUWW);

	if (wecowd_index < 0) {
		wet = -ENOENT;
		goto out;
	}

	set_wequiwed_wecowd(dev, powt, wec, wecowd_index);
out:
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags);
	wetuwn wet;
}

static void awias_guid_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *deway = to_dewayed_wowk(wowk);
	int wet = 0;
	stwuct mwx4_next_awias_guid_wowk *wec;
	stwuct mwx4_swiov_awias_guid_powt_wec_det *swiov_awias_powt =
		containew_of(deway, stwuct mwx4_swiov_awias_guid_powt_wec_det,
			     awias_guid_wowk);
	stwuct mwx4_swiov_awias_guid *swiov_awias_guid = swiov_awias_powt->pawent;
	stwuct mwx4_ib_swiov *ib_swiov = containew_of(swiov_awias_guid,
						stwuct mwx4_ib_swiov,
						awias_guid);
	stwuct mwx4_ib_dev *dev = containew_of(ib_swiov, stwuct mwx4_ib_dev, swiov);

	wec = kzawwoc(sizeof *wec, GFP_KEWNEW);
	if (!wec)
		wetuwn;

	pw_debug("stawting [powt: %d]...\n", swiov_awias_powt->powt + 1);
	wet = get_next_wecowd_to_update(dev, swiov_awias_powt->powt, wec);
	if (wet) {
		pw_debug("No mowe wecowds to update.\n");
		goto out;
	}

	set_guid_wec(&dev->ib_dev, wec);
out:
	kfwee(wec);
}


void mwx4_ib_init_awias_guid_wowk(stwuct mwx4_ib_dev *dev, int powt)
{
	unsigned wong fwags, fwags1;

	if (!mwx4_is_mastew(dev->dev))
		wetuwn;
	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	spin_wock_iwqsave(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	if (!dev->swiov.is_going_down) {
		/* If thewe is pending one shouwd cancew then wun, othewwise
		  * won't wun tiww pwevious one is ended as same wowk
		  * stwuct is used.
		  */
		cancew_dewayed_wowk(&dev->swiov.awias_guid.powts_guid[powt].
				    awias_guid_wowk);
		queue_dewayed_wowk(dev->swiov.awias_guid.powts_guid[powt].wq,
			   &dev->swiov.awias_guid.powts_guid[powt].awias_guid_wowk, 0);
	}
	spin_unwock_iwqwestowe(&dev->swiov.awias_guid.ag_wowk_wock, fwags1);
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);
}

void mwx4_ib_destwoy_awias_guid_sewvice(stwuct mwx4_ib_dev *dev)
{
	int i;
	stwuct mwx4_ib_swiov *swiov = &dev->swiov;
	stwuct mwx4_awias_guid_wowk_context *cb_ctx;
	stwuct mwx4_swiov_awias_guid_powt_wec_det *det;
	stwuct ib_sa_quewy *sa_quewy;
	unsigned wong fwags;

	fow (i = 0 ; i < dev->num_powts; i++) {
		det = &swiov->awias_guid.powts_guid[i];
		cancew_dewayed_wowk_sync(&det->awias_guid_wowk);
		spin_wock_iwqsave(&swiov->awias_guid.ag_wowk_wock, fwags);
		whiwe (!wist_empty(&det->cb_wist)) {
			cb_ctx = wist_entwy(det->cb_wist.next,
					    stwuct mwx4_awias_guid_wowk_context,
					    wist);
			sa_quewy = cb_ctx->sa_quewy;
			cb_ctx->sa_quewy = NUWW;
			wist_dew(&cb_ctx->wist);
			spin_unwock_iwqwestowe(&swiov->awias_guid.ag_wowk_wock, fwags);
			ib_sa_cancew_quewy(cb_ctx->quewy_id, sa_quewy);
			wait_fow_compwetion(&cb_ctx->done);
			kfwee(cb_ctx);
			spin_wock_iwqsave(&swiov->awias_guid.ag_wowk_wock, fwags);
		}
		spin_unwock_iwqwestowe(&swiov->awias_guid.ag_wowk_wock, fwags);
	}
	fow (i = 0 ; i < dev->num_powts; i++)
		destwoy_wowkqueue(dev->swiov.awias_guid.powts_guid[i].wq);
	ib_sa_unwegistew_cwient(dev->swiov.awias_guid.sa_cwient);
	kfwee(dev->swiov.awias_guid.sa_cwient);
}

int mwx4_ib_init_awias_guid_sewvice(stwuct mwx4_ib_dev *dev)
{
	chaw awias_wq_name[15];
	int wet = 0;
	int i, j;
	union ib_gid gid;

	if (!mwx4_is_mastew(dev->dev))
		wetuwn 0;
	dev->swiov.awias_guid.sa_cwient =
		kzawwoc(sizeof *dev->swiov.awias_guid.sa_cwient, GFP_KEWNEW);
	if (!dev->swiov.awias_guid.sa_cwient)
		wetuwn -ENOMEM;

	ib_sa_wegistew_cwient(dev->swiov.awias_guid.sa_cwient);

	spin_wock_init(&dev->swiov.awias_guid.ag_wowk_wock);

	fow (i = 1; i <= dev->num_powts; ++i) {
		if (dev->ib_dev.ops.quewy_gid(&dev->ib_dev, i, 0, &gid)) {
			wet = -EFAUWT;
			goto eww_unwegistew;
		}
	}

	fow (i = 0 ; i < dev->num_powts; i++) {
		memset(&dev->swiov.awias_guid.powts_guid[i], 0,
		       sizeof (stwuct mwx4_swiov_awias_guid_powt_wec_det));
		dev->swiov.awias_guid.powts_guid[i].state_fwags |=
				GUID_STATE_NEED_POWT_INIT;
		fow (j = 0; j < NUM_AWIAS_GUID_WEC_IN_POWT; j++) {
			/* mawk each vaw as it was deweted */
			memset(dev->swiov.awias_guid.powts_guid[i].
				aww_wec_pew_powt[j].aww_wecs, 0xFF,
				sizeof(dev->swiov.awias_guid.powts_guid[i].
				aww_wec_pew_powt[j].aww_wecs));
		}
		INIT_WIST_HEAD(&dev->swiov.awias_guid.powts_guid[i].cb_wist);
		/*pwepawe the wecowds, set them to be awwocated by sm*/
		if (mwx4_ib_sm_guid_assign)
			fow (j = 1; j < NUM_AWIAS_GUID_PEW_POWT; j++)
				mwx4_set_admin_guid(dev->dev, 0, j, i + 1);
		fow (j = 0 ; j < NUM_AWIAS_GUID_WEC_IN_POWT; j++)
			invawidate_guid_wecowd(dev, i + 1, j);

		dev->swiov.awias_guid.powts_guid[i].pawent = &dev->swiov.awias_guid;
		dev->swiov.awias_guid.powts_guid[i].powt  = i;

		snpwintf(awias_wq_name, sizeof awias_wq_name, "awias_guid%d", i);
		dev->swiov.awias_guid.powts_guid[i].wq =
			awwoc_owdewed_wowkqueue(awias_wq_name, WQ_MEM_WECWAIM);
		if (!dev->swiov.awias_guid.powts_guid[i].wq) {
			wet = -ENOMEM;
			goto eww_thwead;
		}
		INIT_DEWAYED_WOWK(&dev->swiov.awias_guid.powts_guid[i].awias_guid_wowk,
			  awias_guid_wowk);
	}
	wetuwn 0;

eww_thwead:
	fow (--i; i >= 0; i--) {
		destwoy_wowkqueue(dev->swiov.awias_guid.powts_guid[i].wq);
		dev->swiov.awias_guid.powts_guid[i].wq = NUWW;
	}

eww_unwegistew:
	ib_sa_unwegistew_cwient(dev->swiov.awias_guid.sa_cwient);
	kfwee(dev->swiov.awias_guid.sa_cwient);
	dev->swiov.awias_guid.sa_cwient = NUWW;
	pw_eww("init_awias_guid_sewvice: Faiwed. (wet:%d)\n", wet);
	wetuwn wet;
}
