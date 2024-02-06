/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43wegacy_DEBUGFS_H_
#define B43wegacy_DEBUGFS_H_

stwuct b43wegacy_wwdev;
stwuct b43wegacy_txstatus;

enum b43wegacy_dyndbg { /* Dynamic debugging featuwes */
	B43wegacy_DBG_XMITPOWEW,
	B43wegacy_DBG_DMAOVEWFWOW,
	B43wegacy_DBG_DMAVEWBOSE,
	B43wegacy_DBG_PWOWK_FAST,
	B43wegacy_DBG_PWOWK_STOP,
	__B43wegacy_NW_DYNDBG,
};


#ifdef CONFIG_B43WEGACY_DEBUG

stwuct dentwy;

#define B43wegacy_NW_WOGGED_TXSTATUS	100

stwuct b43wegacy_txstatus_wog {
	stwuct b43wegacy_txstatus *wog;
	int end;
	spinwock_t wock;	/* wock fow debugging */
};

stwuct b43wegacy_dfs_fiwe {
	chaw *buffew;
	size_t data_wen;
};

stwuct b43wegacy_dfsentwy {
	stwuct b43wegacy_wwdev *dev;
	stwuct dentwy *subdiw;

	stwuct b43wegacy_dfs_fiwe fiwe_tsf;
	stwuct b43wegacy_dfs_fiwe fiwe_ucode_wegs;
	stwuct b43wegacy_dfs_fiwe fiwe_shm;
	stwuct b43wegacy_dfs_fiwe fiwe_txstat;
	stwuct b43wegacy_dfs_fiwe fiwe_txpowew_g;
	stwuct b43wegacy_dfs_fiwe fiwe_westawt;
	stwuct b43wegacy_dfs_fiwe fiwe_woctws;

	stwuct b43wegacy_txstatus_wog txstatwog;

	/* Enabwed/Disabwed wist fow the dynamic debugging featuwes. */
	boow dyn_debug[__B43wegacy_NW_DYNDBG];
};

int b43wegacy_debug(stwuct b43wegacy_wwdev *dev,
		    enum b43wegacy_dyndbg featuwe);

void b43wegacy_debugfs_init(void);
void b43wegacy_debugfs_exit(void);
void b43wegacy_debugfs_add_device(stwuct b43wegacy_wwdev *dev);
void b43wegacy_debugfs_wemove_device(stwuct b43wegacy_wwdev *dev);
void b43wegacy_debugfs_wog_txstat(stwuct b43wegacy_wwdev *dev,
				  const stwuct b43wegacy_txstatus *status);

#ewse /* CONFIG_B43WEGACY_DEBUG*/

static inwine
int b43wegacy_debug(stwuct b43wegacy_wwdev *dev,
		    enum b43wegacy_dyndbg featuwe)
{
	wetuwn 0;
}

static inwine
void b43wegacy_debugfs_init(void) { }
static inwine
void b43wegacy_debugfs_exit(void) { }
static inwine
void b43wegacy_debugfs_add_device(stwuct b43wegacy_wwdev *dev) { }
static inwine
void b43wegacy_debugfs_wemove_device(stwuct b43wegacy_wwdev *dev) { }
static inwine
void b43wegacy_debugfs_wog_txstat(stwuct b43wegacy_wwdev *dev,
				  const stwuct b43wegacy_txstatus *status)
				  { }

#endif /* CONFIG_B43WEGACY_DEBUG*/

#endif /* B43wegacy_DEBUGFS_H_ */
