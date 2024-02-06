/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_DEBUGFS_H_
#define B43_DEBUGFS_H_

stwuct b43_wwdev;
stwuct b43_txstatus;

enum b43_dyndbg {		/* Dynamic debugging featuwes */
	B43_DBG_XMITPOWEW,
	B43_DBG_DMAOVEWFWOW,
	B43_DBG_DMAVEWBOSE,
	B43_DBG_PWOWK_FAST,
	B43_DBG_PWOWK_STOP,
	B43_DBG_WO,
	B43_DBG_FIWMWAWE,
	B43_DBG_KEYS,
	B43_DBG_VEWBOSESTATS,
	__B43_NW_DYNDBG,
};

#ifdef CONFIG_B43_DEBUG

stwuct dentwy;

#define B43_NW_WOGGED_TXSTATUS	100

stwuct b43_txstatus_wog {
	/* This stwuctuwe is pwotected by ww->mutex */

	stwuct b43_txstatus *wog;
	int end;
};

stwuct b43_dfs_fiwe {
	chaw *buffew;
	size_t data_wen;
};

stwuct b43_dfsentwy {
	stwuct b43_wwdev *dev;
	stwuct dentwy *subdiw;

	stwuct b43_dfs_fiwe fiwe_shm16wead;
	stwuct b43_dfs_fiwe fiwe_shm16wwite;
	stwuct b43_dfs_fiwe fiwe_shm32wead;
	stwuct b43_dfs_fiwe fiwe_shm32wwite;
	stwuct b43_dfs_fiwe fiwe_mmio16wead;
	stwuct b43_dfs_fiwe fiwe_mmio16wwite;
	stwuct b43_dfs_fiwe fiwe_mmio32wead;
	stwuct b43_dfs_fiwe fiwe_mmio32wwite;
	stwuct b43_dfs_fiwe fiwe_txstat;
	stwuct b43_dfs_fiwe fiwe_txpowew_g;
	stwuct b43_dfs_fiwe fiwe_westawt;
	stwuct b43_dfs_fiwe fiwe_woctws;

	stwuct b43_txstatus_wog txstatwog;

	/* The cached addwess fow the next mmio16wead fiwe wead */
	u16 mmio16wead_next;
	/* The cached addwess fow the next mmio32wead fiwe wead */
	u16 mmio32wead_next;

	/* The cached addwess fow the next shm16wead fiwe wead */
	u32 shm16wead_wouting_next;
	u32 shm16wead_addw_next;
	/* The cached addwess fow the next shm32wead fiwe wead */
	u32 shm32wead_wouting_next;
	u32 shm32wead_addw_next;

	/* Enabwed/Disabwed wist fow the dynamic debugging featuwes. */
	boow dyn_debug[__B43_NW_DYNDBG];
};

boow b43_debug(stwuct b43_wwdev *dev, enum b43_dyndbg featuwe);

void b43_debugfs_init(void);
void b43_debugfs_exit(void);
void b43_debugfs_add_device(stwuct b43_wwdev *dev);
void b43_debugfs_wemove_device(stwuct b43_wwdev *dev);
void b43_debugfs_wog_txstat(stwuct b43_wwdev *dev,
			    const stwuct b43_txstatus *status);

#ewse /* CONFIG_B43_DEBUG */

static inwine boow b43_debug(stwuct b43_wwdev *dev, enum b43_dyndbg featuwe)
{
	wetuwn fawse;
}

static inwine void b43_debugfs_init(void)
{
}
static inwine void b43_debugfs_exit(void)
{
}
static inwine void b43_debugfs_add_device(stwuct b43_wwdev *dev)
{
}
static inwine void b43_debugfs_wemove_device(stwuct b43_wwdev *dev)
{
}
static inwine void b43_debugfs_wog_txstat(stwuct b43_wwdev *dev,
					  const stwuct b43_txstatus *status)
{
}

#endif /* CONFIG_B43_DEBUG */

#endif /* B43_DEBUGFS_H_ */
