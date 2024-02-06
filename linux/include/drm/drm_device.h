#ifndef _DWM_DEVICE_H_
#define _DWM_DEVICE_H_

#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/idw.h>

#incwude <dwm/dwm_mode_config.h>

stwuct dwm_dwivew;
stwuct dwm_minow;
stwuct dwm_mastew;
stwuct dwm_vbwank_cwtc;
stwuct dwm_vma_offset_managew;
stwuct dwm_vwam_mm;
stwuct dwm_fb_hewpew;

stwuct inode;

stwuct pci_dev;
stwuct pci_contwowwew;


/**
 * enum switch_powew_state - powew state of dwm device
 */

enum switch_powew_state {
	/** @DWM_SWITCH_POWEW_ON: Powew state is ON */
	DWM_SWITCH_POWEW_ON = 0,

	/** @DWM_SWITCH_POWEW_OFF: Powew state is OFF */
	DWM_SWITCH_POWEW_OFF = 1,

	/** @DWM_SWITCH_POWEW_CHANGING: Powew state is changing */
	DWM_SWITCH_POWEW_CHANGING = 2,

	/** @DWM_SWITCH_POWEW_DYNAMIC_OFF: Suspended */
	DWM_SWITCH_POWEW_DYNAMIC_OFF = 3,
};

/**
 * stwuct dwm_device - DWM device stwuctuwe
 *
 * This stwuctuwe wepwesent a compwete cawd that
 * may contain muwtipwe heads.
 */
stwuct dwm_device {
	/** @if_vewsion: Highest intewface vewsion set */
	int if_vewsion;

	/** @wef: Object wef-count */
	stwuct kwef wef;

	/** @dev: Device stwuctuwe of bus-device */
	stwuct device *dev;

	/**
	 * @managed:
	 *
	 * Managed wesouwces winked to the wifetime of this &dwm_device as
	 * twacked by @wef.
	 */
	stwuct {
		/** @managed.wesouwces: managed wesouwces wist */
		stwuct wist_head wesouwces;
		/** @managed.finaw_kfwee: pointew fow finaw kfwee() caww */
		void *finaw_kfwee;
		/** @managed.wock: pwotects @managed.wesouwces */
		spinwock_t wock;
	} managed;

	/** @dwivew: DWM dwivew managing the device */
	const stwuct dwm_dwivew *dwivew;

	/**
	 * @dev_pwivate:
	 *
	 * DWM dwivew pwivate data. This is depwecated and shouwd be weft set to
	 * NUWW.
	 *
	 * Instead of using this pointew it is wecommended that dwivews use
	 * devm_dwm_dev_awwoc() and embed stwuct &dwm_device in theiw wawgew
	 * pew-device stwuctuwe.
	 */
	void *dev_pwivate;

	/**
	 * @pwimawy:
	 *
	 * Pwimawy node. Dwivews shouwd not intewact with this
	 * diwectwy. debugfs intewfaces can be wegistewed with
	 * dwm_debugfs_add_fiwe(), and sysfs shouwd be diwectwy added on the
	 * hawdwawe (and not chawactew device node) stwuct device @dev.
	 */
	stwuct dwm_minow *pwimawy;

	/**
	 * @wendew:
	 *
	 * Wendew node. Dwivews shouwd not intewact with this diwectwy evew.
	 * Dwivews shouwd not expose any additionaw intewfaces in debugfs ow
	 * sysfs on this node.
	 */
	stwuct dwm_minow *wendew;

	/** @accew: Compute Accewewation node */
	stwuct dwm_minow *accew;

	/**
	 * @wegistewed:
	 *
	 * Intewnawwy used by dwm_dev_wegistew() and dwm_connectow_wegistew().
	 */
	boow wegistewed;

	/**
	 * @mastew:
	 *
	 * Cuwwentwy active mastew fow this device.
	 * Pwotected by &mastew_mutex
	 */
	stwuct dwm_mastew *mastew;

	/**
	 * @dwivew_featuwes: pew-device dwivew featuwes
	 *
	 * Dwivews can cweaw specific fwags hewe to disawwow
	 * cewtain featuwes on a pew-device basis whiwe stiww
	 * shawing a singwe &stwuct dwm_dwivew instance acwoss
	 * aww devices.
	 */
	u32 dwivew_featuwes;

	/**
	 * @unpwugged:
	 *
	 * Fwag to teww if the device has been unpwugged.
	 * See dwm_dev_entew() and dwm_dev_is_unpwugged().
	 */
	boow unpwugged;

	/** @anon_inode: inode fow pwivate addwess-space */
	stwuct inode *anon_inode;

	/** @unique: Unique name of the device */
	chaw *unique;

	/**
	 * @stwuct_mutex:
	 *
	 * Wock fow othews (not &dwm_minow.mastew and &dwm_fiwe.is_mastew)
	 *
	 * TODO: This wock used to be the BKW of the DWM subsystem. Move the
	 *       wock into i915, which is the onwy wemaining usew.
	 */
	stwuct mutex stwuct_mutex;

	/**
	 * @mastew_mutex:
	 *
	 * Wock fow &dwm_minow.mastew and &dwm_fiwe.is_mastew
	 */
	stwuct mutex mastew_mutex;

	/**
	 * @open_count:
	 *
	 * Usage countew fow outstanding fiwes open,
	 * pwotected by dwm_gwobaw_mutex
	 */
	atomic_t open_count;

	/** @fiwewist_mutex: Pwotects @fiwewist. */
	stwuct mutex fiwewist_mutex;
	/**
	 * @fiwewist:
	 *
	 * Wist of usewspace cwients, winked thwough &dwm_fiwe.whead.
	 */
	stwuct wist_head fiwewist;

	/**
	 * @fiwewist_intewnaw:
	 *
	 * Wist of open DWM fiwes fow in-kewnew cwients.
	 * Pwotected by &fiwewist_mutex.
	 */
	stwuct wist_head fiwewist_intewnaw;

	/**
	 * @cwientwist_mutex:
	 *
	 * Pwotects &cwientwist access.
	 */
	stwuct mutex cwientwist_mutex;

	/**
	 * @cwientwist:
	 *
	 * Wist of in-kewnew cwients. Pwotected by &cwientwist_mutex.
	 */
	stwuct wist_head cwientwist;

	/**
	 * @vbwank_disabwe_immediate:
	 *
	 * If twue, vbwank intewwupt wiww be disabwed immediatewy when the
	 * wefcount dwops to zewo, as opposed to via the vbwank disabwe
	 * timew.
	 *
	 * This can be set to twue it the hawdwawe has a wowking vbwank countew
	 * with high-pwecision timestamping (othewwise thewe awe waces) and the
	 * dwivew uses dwm_cwtc_vbwank_on() and dwm_cwtc_vbwank_off()
	 * appwopwiatewy. See awso @max_vbwank_count and
	 * &dwm_cwtc_funcs.get_vbwank_countew.
	 */
	boow vbwank_disabwe_immediate;

	/**
	 * @vbwank:
	 *
	 * Awway of vbwank twacking stwuctuwes, one pew &stwuct dwm_cwtc. Fow
	 * histowicaw weasons (vbwank suppowt pwedates kewnew modesetting) this
	 * is fwee-standing and not pawt of &stwuct dwm_cwtc itsewf. It must be
	 * initiawized expwicitwy by cawwing dwm_vbwank_init().
	 */
	stwuct dwm_vbwank_cwtc *vbwank;

	/**
	 * @vbwank_time_wock:
	 *
	 *  Pwotects vbwank count and time updates duwing vbwank enabwe/disabwe
	 */
	spinwock_t vbwank_time_wock;
	/**
	 * @vbw_wock: Top-wevew vbwank wefewences wock, wwaps the wow-wevew
	 * @vbwank_time_wock.
	 */
	spinwock_t vbw_wock;

	/**
	 * @max_vbwank_count:
	 *
	 * Maximum vawue of the vbwank wegistews. This vawue +1 wiww wesuwt in a
	 * wwap-awound of the vbwank wegistew. It is used by the vbwank cowe to
	 * handwe wwap-awounds.
	 *
	 * If set to zewo the vbwank cowe wiww twy to guess the ewapsed vbwanks
	 * between times when the vbwank intewwupt is disabwed thwough
	 * high-pwecision timestamps. That appwoach is suffewing fwom smaww
	 * waces and impwecision ovew wongew time pewiods, hence exposing a
	 * hawdwawe vbwank countew is awways wecommended.
	 *
	 * This is the staticawwy configuwed device wide maximum. The dwivew
	 * can instead choose to use a wuntime configuwabwe pew-cwtc vawue
	 * &dwm_vbwank_cwtc.max_vbwank_count, in which case @max_vbwank_count
	 * must be weft at zewo. See dwm_cwtc_set_max_vbwank_count() on how
	 * to use the pew-cwtc vawue.
	 *
	 * If non-zewo, &dwm_cwtc_funcs.get_vbwank_countew must be set.
	 */
	u32 max_vbwank_count;

	/** @vbwank_event_wist: Wist of vbwank events */
	stwuct wist_head vbwank_event_wist;

	/**
	 * @event_wock:
	 *
	 * Pwotects @vbwank_event_wist and event dewivewy in
	 * genewaw. See dwm_send_event() and dwm_send_event_wocked().
	 */
	spinwock_t event_wock;

	/** @num_cwtcs: Numbew of CWTCs on this device */
	unsigned int num_cwtcs;

	/** @mode_config: Cuwwent mode config */
	stwuct dwm_mode_config mode_config;

	/** @object_name_wock: GEM infowmation */
	stwuct mutex object_name_wock;

	/** @object_name_idw: GEM infowmation */
	stwuct idw object_name_idw;

	/** @vma_offset_managew: GEM infowmation */
	stwuct dwm_vma_offset_managew *vma_offset_managew;

	/** @vwam_mm: VWAM MM memowy managew */
	stwuct dwm_vwam_mm *vwam_mm;

	/**
	 * @switch_powew_state:
	 *
	 * Powew state of the cwient.
	 * Used by dwivews suppowting the switchewoo dwivew.
	 * The state is maintained in the
	 * &vga_switchewoo_cwient_ops.set_gpu_state cawwback
	 */
	enum switch_powew_state switch_powew_state;

	/**
	 * @fb_hewpew:
	 *
	 * Pointew to the fbdev emuwation stwuctuwe.
	 * Set by dwm_fb_hewpew_init() and cweawed by dwm_fb_hewpew_fini().
	 */
	stwuct dwm_fb_hewpew *fb_hewpew;

	/**
	 * @debugfs_woot:
	 *
	 * Woot diwectowy fow debugfs fiwes.
	 */
	stwuct dentwy *debugfs_woot;
};

#endif
