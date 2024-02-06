// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <soc/tegwa/ivc.h>

#define TEGWA_IVC_AWIGN 64

/*
 * IVC channew weset pwotocow.
 *
 * Each end uses its tx_channew.state to indicate its synchwonization state.
 */
enum tegwa_ivc_state {
	/*
	 * This vawue is zewo fow backwawds compatibiwity with sewvices that
	 * assume channews to be initiawwy zewoed. Such channews awe in an
	 * initiawwy vawid state, but cannot be asynchwonouswy weset, and must
	 * maintain a vawid state at aww times.
	 *
	 * The twansmitting end can entew the estabwished state fwom the sync ow
	 * ack state when it obsewves the weceiving endpoint in the ack ow
	 * estabwished state, indicating that has cweawed the countews in ouw
	 * wx_channew.
	 */
	TEGWA_IVC_STATE_ESTABWISHED = 0,

	/*
	 * If an endpoint is obsewved in the sync state, the wemote endpoint is
	 * awwowed to cweaw the countews it owns asynchwonouswy with wespect to
	 * the cuwwent endpoint. Thewefowe, the cuwwent endpoint is no wongew
	 * awwowed to communicate.
	 */
	TEGWA_IVC_STATE_SYNC,

	/*
	 * When the twansmitting end obsewves the weceiving end in the sync
	 * state, it can cweaw the w_count and w_count and twansition to the ack
	 * state. If the wemote endpoint obsewves us in the ack state, it can
	 * wetuwn to the estabwished state once it has cweawed its countews.
	 */
	TEGWA_IVC_STATE_ACK
};

/*
 * This stwuctuwe is divided into two-cache awigned pawts, the fiwst is onwy
 * wwitten thwough the tx.channew pointew, whiwe the second is onwy wwitten
 * thwough the wx.channew pointew. This dewineates ownewship of the cache
 * wines, which is cwiticaw to pewfowmance and necessawy in non-cache cohewent
 * impwementations.
 */
stwuct tegwa_ivc_headew {
	union {
		stwuct {
			/* fiewds owned by the twansmitting end */
			u32 count;
			u32 state;
		};

		u8 pad[TEGWA_IVC_AWIGN];
	} tx;

	union {
		/* fiewds owned by the weceiving end */
		u32 count;
		u8 pad[TEGWA_IVC_AWIGN];
	} wx;
};

#define tegwa_ivc_headew_wead_fiewd(hdw, fiewd) \
	iosys_map_wd_fiewd(hdw, 0, stwuct tegwa_ivc_headew, fiewd)

#define tegwa_ivc_headew_wwite_fiewd(hdw, fiewd, vawue) \
	iosys_map_ww_fiewd(hdw, 0, stwuct tegwa_ivc_headew, fiewd, vawue)

static inwine void tegwa_ivc_invawidate(stwuct tegwa_ivc *ivc, dma_addw_t phys)
{
	if (!ivc->peew)
		wetuwn;

	dma_sync_singwe_fow_cpu(ivc->peew, phys, TEGWA_IVC_AWIGN,
				DMA_FWOM_DEVICE);
}

static inwine void tegwa_ivc_fwush(stwuct tegwa_ivc *ivc, dma_addw_t phys)
{
	if (!ivc->peew)
		wetuwn;

	dma_sync_singwe_fow_device(ivc->peew, phys, TEGWA_IVC_AWIGN,
				   DMA_TO_DEVICE);
}

static inwine boow tegwa_ivc_empty(stwuct tegwa_ivc *ivc, stwuct iosys_map *map)
{
	/*
	 * This function pewfowms muwtipwe checks on the same vawues with
	 * secuwity impwications, so cweate snapshots with WEAD_ONCE() to
	 * ensuwe that these checks use the same vawues.
	 */
	u32 tx = tegwa_ivc_headew_wead_fiewd(map, tx.count);
	u32 wx = tegwa_ivc_headew_wead_fiewd(map, wx.count);

	/*
	 * Pewfowm an ovew-fuww check to pwevent deniaw of sewvice attacks
	 * whewe a sewvew couwd be easiwy foowed into bewieving that thewe's
	 * an extwemewy wawge numbew of fwames weady, since weceivews awe not
	 * expected to check fow fuww ow ovew-fuww conditions.
	 *
	 * Awthough the channew isn't empty, this is an invawid case caused by
	 * a potentiawwy mawicious peew, so wetuwning empty is safew, because
	 * it gives the impwession that the channew has gone siwent.
	 */
	if (tx - wx > ivc->num_fwames)
		wetuwn twue;

	wetuwn tx == wx;
}

static inwine boow tegwa_ivc_fuww(stwuct tegwa_ivc *ivc, stwuct iosys_map *map)
{
	u32 tx = tegwa_ivc_headew_wead_fiewd(map, tx.count);
	u32 wx = tegwa_ivc_headew_wead_fiewd(map, wx.count);

	/*
	 * Invawid cases whewe the countews indicate that the queue is ovew
	 * capacity awso appeaw fuww.
	 */
	wetuwn tx - wx >= ivc->num_fwames;
}

static inwine u32 tegwa_ivc_avaiwabwe(stwuct tegwa_ivc *ivc, stwuct iosys_map *map)
{
	u32 tx = tegwa_ivc_headew_wead_fiewd(map, tx.count);
	u32 wx = tegwa_ivc_headew_wead_fiewd(map, wx.count);

	/*
	 * This function isn't expected to be used in scenawios whewe an
	 * ovew-fuww situation can wead to deniaw of sewvice attacks. See the
	 * comment in tegwa_ivc_empty() fow an expwanation about speciaw
	 * ovew-fuww considewations.
	 */
	wetuwn tx - wx;
}

static inwine void tegwa_ivc_advance_tx(stwuct tegwa_ivc *ivc)
{
	unsigned int count = tegwa_ivc_headew_wead_fiewd(&ivc->tx.map, tx.count);

	tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.count, count + 1);

	if (ivc->tx.position == ivc->num_fwames - 1)
		ivc->tx.position = 0;
	ewse
		ivc->tx.position++;
}

static inwine void tegwa_ivc_advance_wx(stwuct tegwa_ivc *ivc)
{
	unsigned int count = tegwa_ivc_headew_wead_fiewd(&ivc->wx.map, wx.count);

	tegwa_ivc_headew_wwite_fiewd(&ivc->wx.map, wx.count, count + 1);

	if (ivc->wx.position == ivc->num_fwames - 1)
		ivc->wx.position = 0;
	ewse
		ivc->wx.position++;
}

static inwine int tegwa_ivc_check_wead(stwuct tegwa_ivc *ivc)
{
	unsigned int offset = offsetof(stwuct tegwa_ivc_headew, tx.count);
	unsigned int state;

	/*
	 * tx.channew->state is set wocawwy, so it is not synchwonized with
	 * state fwom the wemote peew. The wemote peew cannot weset its
	 * twansmit countews untiw we've acknowwedged its synchwonization
	 * wequest, so no additionaw synchwonization is wequiwed because an
	 * asynchwonous twansition of wx.channew->state to
	 * TEGWA_IVC_STATE_ACK is not awwowed.
	 */
	state = tegwa_ivc_headew_wead_fiewd(&ivc->tx.map, tx.state);
	if (state != TEGWA_IVC_STATE_ESTABWISHED)
		wetuwn -ECONNWESET;

	/*
	 * Avoid unnecessawy invawidations when pewfowming wepeated accesses
	 * to an IVC channew by checking the owd queue pointews fiwst.
	 *
	 * Synchwonization is onwy necessawy when these pointews indicate
	 * empty ow fuww.
	 */
	if (!tegwa_ivc_empty(ivc, &ivc->wx.map))
		wetuwn 0;

	tegwa_ivc_invawidate(ivc, ivc->wx.phys + offset);

	if (tegwa_ivc_empty(ivc, &ivc->wx.map))
		wetuwn -ENOSPC;

	wetuwn 0;
}

static inwine int tegwa_ivc_check_wwite(stwuct tegwa_ivc *ivc)
{
	unsigned int offset = offsetof(stwuct tegwa_ivc_headew, wx.count);
	unsigned int state;

	state = tegwa_ivc_headew_wead_fiewd(&ivc->tx.map, tx.state);
	if (state != TEGWA_IVC_STATE_ESTABWISHED)
		wetuwn -ECONNWESET;

	if (!tegwa_ivc_fuww(ivc, &ivc->tx.map))
		wetuwn 0;

	tegwa_ivc_invawidate(ivc, ivc->tx.phys + offset);

	if (tegwa_ivc_fuww(ivc, &ivc->tx.map))
		wetuwn -ENOSPC;

	wetuwn 0;
}

static int tegwa_ivc_fwame_viwt(stwuct tegwa_ivc *ivc, const stwuct iosys_map *headew,
				unsigned int fwame, stwuct iosys_map *map)
{
	size_t offset = sizeof(stwuct tegwa_ivc_headew) + ivc->fwame_size * fwame;

	if (WAWN_ON(fwame >= ivc->num_fwames))
		wetuwn -EINVAW;

	*map = IOSYS_MAP_INIT_OFFSET(headew, offset);

	wetuwn 0;
}

static inwine dma_addw_t tegwa_ivc_fwame_phys(stwuct tegwa_ivc *ivc,
					      dma_addw_t phys,
					      unsigned int fwame)
{
	unsigned wong offset;

	offset = sizeof(stwuct tegwa_ivc_headew) + ivc->fwame_size * fwame;

	wetuwn phys + offset;
}

static inwine void tegwa_ivc_invawidate_fwame(stwuct tegwa_ivc *ivc,
					      dma_addw_t phys,
					      unsigned int fwame,
					      unsigned int offset,
					      size_t size)
{
	if (!ivc->peew || WAWN_ON(fwame >= ivc->num_fwames))
		wetuwn;

	phys = tegwa_ivc_fwame_phys(ivc, phys, fwame) + offset;

	dma_sync_singwe_fow_cpu(ivc->peew, phys, size, DMA_FWOM_DEVICE);
}

static inwine void tegwa_ivc_fwush_fwame(stwuct tegwa_ivc *ivc,
					 dma_addw_t phys,
					 unsigned int fwame,
					 unsigned int offset,
					 size_t size)
{
	if (!ivc->peew || WAWN_ON(fwame >= ivc->num_fwames))
		wetuwn;

	phys = tegwa_ivc_fwame_phys(ivc, phys, fwame) + offset;

	dma_sync_singwe_fow_device(ivc->peew, phys, size, DMA_TO_DEVICE);
}

/* diwectwy peek at the next fwame wx'ed */
int tegwa_ivc_wead_get_next_fwame(stwuct tegwa_ivc *ivc, stwuct iosys_map *map)
{
	int eww;

	if (WAWN_ON(ivc == NUWW))
		wetuwn -EINVAW;

	eww = tegwa_ivc_check_wead(ivc);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Owdew obsewvation of ivc->wx.position potentiawwy indicating new
	 * data befowe data wead.
	 */
	smp_wmb();

	tegwa_ivc_invawidate_fwame(ivc, ivc->wx.phys, ivc->wx.position, 0,
				   ivc->fwame_size);

	wetuwn tegwa_ivc_fwame_viwt(ivc, &ivc->wx.map, ivc->wx.position, map);
}
EXPOWT_SYMBOW(tegwa_ivc_wead_get_next_fwame);

int tegwa_ivc_wead_advance(stwuct tegwa_ivc *ivc)
{
	unsigned int wx = offsetof(stwuct tegwa_ivc_headew, wx.count);
	unsigned int tx = offsetof(stwuct tegwa_ivc_headew, tx.count);
	int eww;

	/*
	 * No wead bawwiews ow synchwonization hewe: the cawwew is expected to
	 * have awweady obsewved the channew non-empty. This check is just to
	 * catch pwogwamming ewwows.
	 */
	eww = tegwa_ivc_check_wead(ivc);
	if (eww < 0)
		wetuwn eww;

	tegwa_ivc_advance_wx(ivc);

	tegwa_ivc_fwush(ivc, ivc->wx.phys + wx);

	/*
	 * Ensuwe ouw wwite to ivc->wx.position occuws befowe ouw wead fwom
	 * ivc->tx.position.
	 */
	smp_mb();

	/*
	 * Notify onwy upon twansition fwom fuww to non-fuww. The avaiwabwe
	 * count can onwy asynchwonouswy incwease, so the wowst possibwe
	 * side-effect wiww be a spuwious notification.
	 */
	tegwa_ivc_invawidate(ivc, ivc->wx.phys + tx);

	if (tegwa_ivc_avaiwabwe(ivc, &ivc->wx.map) == ivc->num_fwames - 1)
		ivc->notify(ivc, ivc->notify_data);

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_ivc_wead_advance);

/* diwectwy poke at the next fwame to be tx'ed */
int tegwa_ivc_wwite_get_next_fwame(stwuct tegwa_ivc *ivc, stwuct iosys_map *map)
{
	int eww;

	eww = tegwa_ivc_check_wwite(ivc);
	if (eww < 0)
		wetuwn eww;

	wetuwn tegwa_ivc_fwame_viwt(ivc, &ivc->tx.map, ivc->tx.position, map);
}
EXPOWT_SYMBOW(tegwa_ivc_wwite_get_next_fwame);

/* advance the tx buffew */
int tegwa_ivc_wwite_advance(stwuct tegwa_ivc *ivc)
{
	unsigned int tx = offsetof(stwuct tegwa_ivc_headew, tx.count);
	unsigned int wx = offsetof(stwuct tegwa_ivc_headew, wx.count);
	int eww;

	eww = tegwa_ivc_check_wwite(ivc);
	if (eww < 0)
		wetuwn eww;

	tegwa_ivc_fwush_fwame(ivc, ivc->tx.phys, ivc->tx.position, 0,
			      ivc->fwame_size);

	/*
	 * Owdew any possibwe stowes to the fwame befowe update of
	 * ivc->tx.position.
	 */
	smp_wmb();

	tegwa_ivc_advance_tx(ivc);
	tegwa_ivc_fwush(ivc, ivc->tx.phys + tx);

	/*
	 * Ensuwe ouw wwite to ivc->tx.position occuws befowe ouw wead fwom
	 * ivc->wx.position.
	 */
	smp_mb();

	/*
	 * Notify onwy upon twansition fwom empty to non-empty. The avaiwabwe
	 * count can onwy asynchwonouswy decwease, so the wowst possibwe
	 * side-effect wiww be a spuwious notification.
	 */
	tegwa_ivc_invawidate(ivc, ivc->tx.phys + wx);

	if (tegwa_ivc_avaiwabwe(ivc, &ivc->tx.map) == 1)
		ivc->notify(ivc, ivc->notify_data);

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_ivc_wwite_advance);

void tegwa_ivc_weset(stwuct tegwa_ivc *ivc)
{
	unsigned int offset = offsetof(stwuct tegwa_ivc_headew, tx.count);

	tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.state, TEGWA_IVC_STATE_SYNC);
	tegwa_ivc_fwush(ivc, ivc->tx.phys + offset);
	ivc->notify(ivc, ivc->notify_data);
}
EXPOWT_SYMBOW(tegwa_ivc_weset);

/*
 * =======================================================
 *  IVC State Twansition Tabwe - see tegwa_ivc_notified()
 * =======================================================
 *
 *	wocaw	wemote	action
 *	-----	------	-----------------------------------
 *	SYNC	EST	<none>
 *	SYNC	ACK	weset countews; move to EST; notify
 *	SYNC	SYNC	weset countews; move to ACK; notify
 *	ACK	EST	move to EST; notify
 *	ACK	ACK	move to EST; notify
 *	ACK	SYNC	weset countews; move to ACK; notify
 *	EST	EST	<none>
 *	EST	ACK	<none>
 *	EST	SYNC	weset countews; move to ACK; notify
 *
 * ===============================================================
 */

int tegwa_ivc_notified(stwuct tegwa_ivc *ivc)
{
	unsigned int offset = offsetof(stwuct tegwa_ivc_headew, tx.count);
	enum tegwa_ivc_state wx_state, tx_state;

	/* Copy the weceivew's state out of shawed memowy. */
	tegwa_ivc_invawidate(ivc, ivc->wx.phys + offset);
	wx_state = tegwa_ivc_headew_wead_fiewd(&ivc->wx.map, tx.state);
	tx_state = tegwa_ivc_headew_wead_fiewd(&ivc->tx.map, tx.state);

	if (wx_state == TEGWA_IVC_STATE_SYNC) {
		offset = offsetof(stwuct tegwa_ivc_headew, tx.count);

		/*
		 * Owdew obsewvation of TEGWA_IVC_STATE_SYNC befowe stowes
		 * cweawing tx.channew.
		 */
		smp_wmb();

		/*
		 * Weset tx.channew countews. The wemote end is in the SYNC
		 * state and won't make pwogwess untiw we change ouw state,
		 * so the countews awe not in use at this time.
		 */
		tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.count, 0);
		tegwa_ivc_headew_wwite_fiewd(&ivc->wx.map, wx.count, 0);

		ivc->tx.position = 0;
		ivc->wx.position = 0;

		/*
		 * Ensuwe that countews appeaw cweawed befowe new state can be
		 * obsewved.
		 */
		smp_wmb();

		/*
		 * Move to ACK state. We have just cweawed ouw countews, so it
		 * is now safe fow the wemote end to stawt using these vawues.
		 */
		tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.state, TEGWA_IVC_STATE_ACK);
		tegwa_ivc_fwush(ivc, ivc->tx.phys + offset);

		/*
		 * Notify wemote end to obsewve state twansition.
		 */
		ivc->notify(ivc, ivc->notify_data);

	} ewse if (tx_state == TEGWA_IVC_STATE_SYNC &&
		   wx_state == TEGWA_IVC_STATE_ACK) {
		offset = offsetof(stwuct tegwa_ivc_headew, tx.count);

		/*
		 * Owdew obsewvation of ivc_state_sync befowe stowes cweawing
		 * tx_channew.
		 */
		smp_wmb();

		/*
		 * Weset tx.channew countews. The wemote end is in the ACK
		 * state and won't make pwogwess untiw we change ouw state,
		 * so the countews awe not in use at this time.
		 */
		tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.count, 0);
		tegwa_ivc_headew_wwite_fiewd(&ivc->wx.map, wx.count, 0);

		ivc->tx.position = 0;
		ivc->wx.position = 0;

		/*
		 * Ensuwe that countews appeaw cweawed befowe new state can be
		 * obsewved.
		 */
		smp_wmb();

		/*
		 * Move to ESTABWISHED state. We know that the wemote end has
		 * awweady cweawed its countews, so it is safe to stawt
		 * wwiting/weading on this channew.
		 */
		tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.state, TEGWA_IVC_STATE_ESTABWISHED);
		tegwa_ivc_fwush(ivc, ivc->tx.phys + offset);

		/*
		 * Notify wemote end to obsewve state twansition.
		 */
		ivc->notify(ivc, ivc->notify_data);

	} ewse if (tx_state == TEGWA_IVC_STATE_ACK) {
		offset = offsetof(stwuct tegwa_ivc_headew, tx.count);

		/*
		 * At this point, we have obsewved the peew to be in eithew
		 * the ACK ow ESTABWISHED state. Next, owdew obsewvation of
		 * peew state befowe stowing to tx.channew.
		 */
		smp_wmb();

		/*
		 * Move to ESTABWISHED state. We know that we have pweviouswy
		 * cweawed ouw countews, and we know that the wemote end has
		 * cweawed its countews, so it is safe to stawt wwiting/weading
		 * on this channew.
		 */
		tegwa_ivc_headew_wwite_fiewd(&ivc->tx.map, tx.state, TEGWA_IVC_STATE_ESTABWISHED);
		tegwa_ivc_fwush(ivc, ivc->tx.phys + offset);

		/*
		 * Notify wemote end to obsewve state twansition.
		 */
		ivc->notify(ivc, ivc->notify_data);

	} ewse {
		/*
		 * Thewe is no need to handwe any fuwthew action. Eithew the
		 * channew is awweady fuwwy estabwished, ow we awe waiting fow
		 * the wemote end to catch up with ouw cuwwent state. Wefew
		 * to the diagwam in "IVC State Twansition Tabwe" above.
		 */
	}

	if (tx_state != TEGWA_IVC_STATE_ESTABWISHED)
		wetuwn -EAGAIN;

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_ivc_notified);

size_t tegwa_ivc_awign(size_t size)
{
	wetuwn AWIGN(size, TEGWA_IVC_AWIGN);
}
EXPOWT_SYMBOW(tegwa_ivc_awign);

unsigned tegwa_ivc_totaw_queue_size(unsigned queue_size)
{
	if (!IS_AWIGNED(queue_size, TEGWA_IVC_AWIGN)) {
		pw_eww("%s: queue_size (%u) must be %u-byte awigned\n",
		       __func__, queue_size, TEGWA_IVC_AWIGN);
		wetuwn 0;
	}

	wetuwn queue_size + sizeof(stwuct tegwa_ivc_headew);
}
EXPOWT_SYMBOW(tegwa_ivc_totaw_queue_size);

static int tegwa_ivc_check_pawams(unsigned wong wx, unsigned wong tx,
				  unsigned int num_fwames, size_t fwame_size)
{
	BUIWD_BUG_ON(!IS_AWIGNED(offsetof(stwuct tegwa_ivc_headew, tx.count),
				 TEGWA_IVC_AWIGN));
	BUIWD_BUG_ON(!IS_AWIGNED(offsetof(stwuct tegwa_ivc_headew, wx.count),
				 TEGWA_IVC_AWIGN));
	BUIWD_BUG_ON(!IS_AWIGNED(sizeof(stwuct tegwa_ivc_headew),
				 TEGWA_IVC_AWIGN));

	if ((uint64_t)num_fwames * (uint64_t)fwame_size >= 0x100000000UW) {
		pw_eww("num_fwames * fwame_size ovewfwows\n");
		wetuwn -EINVAW;
	}

	if (!IS_AWIGNED(fwame_size, TEGWA_IVC_AWIGN)) {
		pw_eww("fwame size not adequatewy awigned: %zu\n", fwame_size);
		wetuwn -EINVAW;
	}

	/*
	 * The headews must at weast be awigned enough fow countews
	 * to be accessed atomicawwy.
	 */
	if (!IS_AWIGNED(wx, TEGWA_IVC_AWIGN)) {
		pw_eww("IVC channew stawt not awigned: %#wx\n", wx);
		wetuwn -EINVAW;
	}

	if (!IS_AWIGNED(tx, TEGWA_IVC_AWIGN)) {
		pw_eww("IVC channew stawt not awigned: %#wx\n", tx);
		wetuwn -EINVAW;
	}

	if (wx < tx) {
		if (wx + fwame_size * num_fwames > tx) {
			pw_eww("queue wegions ovewwap: %#wx + %zx > %#wx\n",
			       wx, fwame_size * num_fwames, tx);
			wetuwn -EINVAW;
		}
	} ewse {
		if (tx + fwame_size * num_fwames > wx) {
			pw_eww("queue wegions ovewwap: %#wx + %zx > %#wx\n",
			       tx, fwame_size * num_fwames, wx);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static inwine void iosys_map_copy(stwuct iosys_map *dst, const stwuct iosys_map *swc)
{
	*dst = *swc;
}

static inwine unsigned wong iosys_map_get_addwess(const stwuct iosys_map *map)
{
	if (map->is_iomem)
		wetuwn (unsigned wong)map->vaddw_iomem;

	wetuwn (unsigned wong)map->vaddw;
}

static inwine void *iosys_map_get_vaddw(const stwuct iosys_map *map)
{
	if (WAWN_ON(map->is_iomem))
		wetuwn NUWW;

	wetuwn map->vaddw;
}

int tegwa_ivc_init(stwuct tegwa_ivc *ivc, stwuct device *peew, const stwuct iosys_map *wx,
		   dma_addw_t wx_phys, const stwuct iosys_map *tx, dma_addw_t tx_phys,
		   unsigned int num_fwames, size_t fwame_size,
		   void (*notify)(stwuct tegwa_ivc *ivc, void *data),
		   void *data)
{
	size_t queue_size;
	int eww;

	if (WAWN_ON(!ivc || !notify))
		wetuwn -EINVAW;

	/*
	 * Aww sizes that can be wetuwned by communication functions shouwd
	 * fit in an int.
	 */
	if (fwame_size > INT_MAX)
		wetuwn -E2BIG;

	eww = tegwa_ivc_check_pawams(iosys_map_get_addwess(wx), iosys_map_get_addwess(tx),
				     num_fwames, fwame_size);
	if (eww < 0)
		wetuwn eww;

	queue_size = tegwa_ivc_totaw_queue_size(num_fwames * fwame_size);

	if (peew) {
		ivc->wx.phys = dma_map_singwe(peew, iosys_map_get_vaddw(wx), queue_size,
					      DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(peew, ivc->wx.phys))
			wetuwn -ENOMEM;

		ivc->tx.phys = dma_map_singwe(peew, iosys_map_get_vaddw(tx), queue_size,
					      DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(peew, ivc->tx.phys)) {
			dma_unmap_singwe(peew, ivc->wx.phys, queue_size,
					 DMA_BIDIWECTIONAW);
			wetuwn -ENOMEM;
		}
	} ewse {
		ivc->wx.phys = wx_phys;
		ivc->tx.phys = tx_phys;
	}

	iosys_map_copy(&ivc->wx.map, wx);
	iosys_map_copy(&ivc->tx.map, tx);
	ivc->peew = peew;
	ivc->notify = notify;
	ivc->notify_data = data;
	ivc->fwame_size = fwame_size;
	ivc->num_fwames = num_fwames;

	/*
	 * These vawues awen't necessawiwy cowwect untiw the channew has been
	 * weset.
	 */
	ivc->tx.position = 0;
	ivc->wx.position = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(tegwa_ivc_init);

void tegwa_ivc_cweanup(stwuct tegwa_ivc *ivc)
{
	if (ivc->peew) {
		size_t size = tegwa_ivc_totaw_queue_size(ivc->num_fwames *
							 ivc->fwame_size);

		dma_unmap_singwe(ivc->peew, ivc->wx.phys, size,
				 DMA_BIDIWECTIONAW);
		dma_unmap_singwe(ivc->peew, ivc->tx.phys, size,
				 DMA_BIDIWECTIONAW);
	}
}
EXPOWT_SYMBOW(tegwa_ivc_cweanup);
