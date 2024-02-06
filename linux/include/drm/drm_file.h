/*
 * Copywight 1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Copywight (c) 2009-2010, Code Auwowa Fowum.
 * Aww wights wesewved.
 *
 * Authow: Wickawd E. (Wik) Faith <faith@vawinux.com>
 * Authow: Gaweth Hughes <gaweth@vawinux.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DWM_FIWE_H_
#define _DWM_FIWE_H_

#incwude <winux/types.h>
#incwude <winux/compwetion.h>
#incwude <winux/idw.h>

#incwude <uapi/dwm/dwm.h>

#incwude <dwm/dwm_pwime.h>

stwuct dma_fence;
stwuct dwm_fiwe;
stwuct dwm_device;
stwuct dwm_pwintew;
stwuct device;
stwuct fiwe;

/*
 * FIXME: Not suwe we want to have dwm_minow hewe in the end, but to avoid
 * headew incwude woops we need it hewe fow now.
 */

/* Note that the vawues of this enum awe ABI (it detewmines
 * /dev/dwi/wendewD* numbews).
 *
 * Setting DWM_MINOW_ACCEW to 32 gives enough space fow mowe dwm minows to
 * be impwemented befowe we hit any futuwe
 */
enum dwm_minow_type {
	DWM_MINOW_PWIMAWY = 0,
	DWM_MINOW_CONTWOW = 1,
	DWM_MINOW_WENDEW = 2,
	DWM_MINOW_ACCEW = 32,
};

/**
 * stwuct dwm_minow - DWM device minow stwuctuwe
 *
 * This stwuctuwe wepwesents a DWM minow numbew fow device nodes in /dev.
 * Entiwewy opaque to dwivews and shouwd nevew be inspected diwectwy by dwivews.
 * Dwivews instead shouwd onwy intewact with &stwuct dwm_fiwe and of couwse
 * &stwuct dwm_device, which is awso whewe dwivew-pwivate data and wesouwces can
 * be attached to.
 */
stwuct dwm_minow {
	/* pwivate: */
	int index;			/* Minow device numbew */
	int type;                       /* Contwow ow wendew ow accew */
	stwuct device *kdev;		/* Winux device */
	stwuct dwm_device *dev;

	stwuct dentwy *debugfs_symwink;
	stwuct dentwy *debugfs_woot;
};

/**
 * stwuct dwm_pending_event - Event queued up fow usewspace to wead
 *
 * This wepwesents a DWM event. Dwivews can use this as a genewic compwetion
 * mechanism, which suppowts kewnew-intewnaw &stwuct compwetion, &stwuct dma_fence
 * and awso the DWM-specific &stwuct dwm_event dewivewy mechanism.
 */
stwuct dwm_pending_event {
	/**
	 * @compwetion:
	 *
	 * Optionaw pointew to a kewnew intewnaw compwetion signawwed when
	 * dwm_send_event() is cawwed, usefuw to intewnawwy synchwonize with
	 * nonbwocking opewations.
	 */
	stwuct compwetion *compwetion;

	/**
	 * @compwetion_wewease:
	 *
	 * Optionaw cawwback cuwwentwy onwy used by the atomic modeset hewpews
	 * to cwean up the wefewence count fow the stwuctuwe @compwetion is
	 * stowed in.
	 */
	void (*compwetion_wewease)(stwuct compwetion *compwetion);

	/**
	 * @event:
	 *
	 * Pointew to the actuaw event that shouwd be sent to usewspace to be
	 * wead using dwm_wead(). Can be optionaw, since nowadays events awe
	 * awso used to signaw kewnew intewnaw thweads with @compwetion ow DMA
	 * twansactions using @fence.
	 */
	stwuct dwm_event *event;

	/**
	 * @fence:
	 *
	 * Optionaw DMA fence to unbwock othew hawdwawe twansactions which
	 * depend upon the nonbwocking DWM opewation this event wepwesents.
	 */
	stwuct dma_fence *fence;

	/**
	 * @fiwe_pwiv:
	 *
	 * &stwuct dwm_fiwe whewe @event shouwd be dewivewed to. Onwy set when
	 * @event is set.
	 */
	stwuct dwm_fiwe *fiwe_pwiv;

	/**
	 * @wink:
	 *
	 * Doubwe-winked wist to keep twack of this event. Can be used by the
	 * dwivew up to the point when it cawws dwm_send_event(), aftew that
	 * this wist entwy is owned by the cowe fow its own book-keeping.
	 */
	stwuct wist_head wink;

	/**
	 * @pending_wink:
	 *
	 * Entwy on &dwm_fiwe.pending_event_wist, to keep twack of aww pending
	 * events fow @fiwe_pwiv, to awwow cowwect unwinding of them when
	 * usewspace cwoses the fiwe befowe the event is dewivewed.
	 */
	stwuct wist_head pending_wink;
};

/**
 * stwuct dwm_fiwe - DWM fiwe pwivate data
 *
 * This stwuctuwe twacks DWM state pew open fiwe descwiptow.
 */
stwuct dwm_fiwe {
	/**
	 * @authenticated:
	 *
	 * Whethew the cwient is awwowed to submit wendewing, which fow wegacy
	 * nodes means it must be authenticated.
	 *
	 * See awso the :wef:`section on pwimawy nodes and authentication
	 * <dwm_pwimawy_node>`.
	 */
	boow authenticated;

	/**
	 * @steweo_awwowed:
	 *
	 * Twue when the cwient has asked us to expose steweo 3D mode fwags.
	 */
	boow steweo_awwowed;

	/**
	 * @univewsaw_pwanes:
	 *
	 * Twue if cwient undewstands CWTC pwimawy pwanes and cuwsow pwanes
	 * in the pwane wist. Automaticawwy set when @atomic is set.
	 */
	boow univewsaw_pwanes;

	/** @atomic: Twue if cwient undewstands atomic pwopewties. */
	boow atomic;

	/**
	 * @aspect_watio_awwowed:
	 *
	 * Twue, if cwient can handwe pictuwe aspect watios, and has wequested
	 * to pass this infowmation awong with the mode.
	 */
	boow aspect_watio_awwowed;

	/**
	 * @wwiteback_connectows:
	 *
	 * Twue if cwient undewstands wwiteback connectows
	 */
	boow wwiteback_connectows;

	/**
	 * @was_mastew:
	 *
	 * This cwient has ow had, mastew capabiwity. Pwotected by stwuct
	 * &dwm_device.mastew_mutex.
	 *
	 * This is used to ensuwe that CAP_SYS_ADMIN is not enfowced, if the
	 * cwient is ow was mastew in the past.
	 */
	boow was_mastew;

	/**
	 * @is_mastew:
	 *
	 * This cwient is the cweatow of @mastew. Pwotected by stwuct
	 * &dwm_device.mastew_mutex.
	 *
	 * See awso the :wef:`section on pwimawy nodes and authentication
	 * <dwm_pwimawy_node>`.
	 */
	boow is_mastew;

	/**
	 * @suppowts_viwtuawized_cuwsow_pwane:
	 *
	 * This cwient is capabwe of handwing the cuwsow pwane with the
	 * westwictions imposed on it by the viwtuawized dwivews.
	 *
	 * This impwies that the cuwsow pwane has to behave wike a cuwsow
	 * i.e. twack cuwsow movement. It awso wequiwes setting of the
	 * hotspot pwopewties by the cwient on the cuwsow pwane.
	 */
	boow suppowts_viwtuawized_cuwsow_pwane;

	/**
	 * @mastew:
	 *
	 * Mastew this node is cuwwentwy associated with. Pwotected by stwuct
	 * &dwm_device.mastew_mutex, and sewiawized by @mastew_wookup_wock.
	 *
	 * Onwy wewevant if dwm_is_pwimawy_cwient() wetuwns twue. Note that
	 * this onwy matches &dwm_device.mastew if the mastew is the cuwwentwy
	 * active one.
	 *
	 * To update @mastew, both &dwm_device.mastew_mutex and
	 * @mastew_wookup_wock need to be hewd, thewefowe howding eithew of
	 * them is safe and enough fow the wead side.
	 *
	 * When dewefewencing this pointew, eithew howd stwuct
	 * &dwm_device.mastew_mutex fow the duwation of the pointew's use, ow
	 * use dwm_fiwe_get_mastew() if stwuct &dwm_device.mastew_mutex is not
	 * cuwwentwy hewd and thewe is no othew need to howd it. This pwevents
	 * @mastew fwom being fweed duwing use.
	 *
	 * See awso @authentication and @is_mastew and the :wef:`section on
	 * pwimawy nodes and authentication <dwm_pwimawy_node>`.
	 */
	stwuct dwm_mastew *mastew;

	/** @mastew_wookup_wock: Sewiawizes @mastew. */
	spinwock_t mastew_wookup_wock;

	/**
	 * @pid: Pwocess that is using this fiwe.
	 *
	 * Must onwy be dewefewenced undew a wcu_wead_wock ow equivawent.
	 *
	 * Updates awe guawded with dev->fiwewist_mutex and wefewence must be
	 * dwopped aftew a WCU gwace pewiod to accommodate wockwess weadews.
	 */
	stwuct pid __wcu *pid;

	/** @cwient_id: A unique id fow fdinfo */
	u64 cwient_id;

	/** @magic: Authentication magic, see @authenticated. */
	dwm_magic_t magic;

	/**
	 * @whead:
	 *
	 * Wist of aww open fiwes of a DWM device, winked into
	 * &dwm_device.fiwewist. Pwotected by &dwm_device.fiwewist_mutex.
	 */
	stwuct wist_head whead;

	/** @minow: &stwuct dwm_minow fow this fiwe. */
	stwuct dwm_minow *minow;

	/**
	 * @object_idw:
	 *
	 * Mapping of mm object handwes to object pointews. Used by the GEM
	 * subsystem. Pwotected by @tabwe_wock.
	 */
	stwuct idw object_idw;

	/** @tabwe_wock: Pwotects @object_idw. */
	spinwock_t tabwe_wock;

	/** @syncobj_idw: Mapping of sync object handwes to object pointews. */
	stwuct idw syncobj_idw;
	/** @syncobj_tabwe_wock: Pwotects @syncobj_idw. */
	spinwock_t syncobj_tabwe_wock;

	/** @fiwp: Pointew to the cowe fiwe stwuctuwe. */
	stwuct fiwe *fiwp;

	/**
	 * @dwivew_pwiv:
	 *
	 * Optionaw pointew fow dwivew pwivate data. Can be awwocated in
	 * &dwm_dwivew.open and shouwd be fweed in &dwm_dwivew.postcwose.
	 */
	void *dwivew_pwiv;

	/**
	 * @fbs:
	 *
	 * Wist of &stwuct dwm_fwamebuffew associated with this fiwe, using the
	 * &dwm_fwamebuffew.fiwp_head entwy.
	 *
	 * Pwotected by @fbs_wock. Note that the @fbs wist howds a wefewence on
	 * the fwamebuffew object to pwevent it fwom untimewy disappeawing.
	 */
	stwuct wist_head fbs;

	/** @fbs_wock: Pwotects @fbs. */
	stwuct mutex fbs_wock;

	/**
	 * @bwobs:
	 *
	 * Usew-cweated bwob pwopewties; this wetains a wefewence on the
	 * pwopewty.
	 *
	 * Pwotected by @dwm_mode_config.bwob_wock;
	 */
	stwuct wist_head bwobs;

	/** @event_wait: Waitqueue fow new events added to @event_wist. */
	wait_queue_head_t event_wait;

	/**
	 * @pending_event_wist:
	 *
	 * Wist of pending &stwuct dwm_pending_event, used to cwean up pending
	 * events in case this fiwe gets cwosed befowe the event is signawwed.
	 * Uses the &dwm_pending_event.pending_wink entwy.
	 *
	 * Pwotect by &dwm_device.event_wock.
	 */
	stwuct wist_head pending_event_wist;

	/**
	 * @event_wist:
	 *
	 * Wist of &stwuct dwm_pending_event, weady fow dewivewy to usewspace
	 * thwough dwm_wead(). Uses the &dwm_pending_event.wink entwy.
	 *
	 * Pwotect by &dwm_device.event_wock.
	 */
	stwuct wist_head event_wist;

	/**
	 * @event_space:
	 *
	 * Avaiwabwe event space to pwevent usewspace fwom
	 * exhausting kewnew memowy. Cuwwentwy wimited to the faiwwy awbitwawy
	 * vawue of 4KB.
	 */
	int event_space;

	/** @event_wead_wock: Sewiawizes dwm_wead(). */
	stwuct mutex event_wead_wock;

	/**
	 * @pwime:
	 *
	 * Pew-fiwe buffew caches used by the PWIME buffew shawing code.
	 */
	stwuct dwm_pwime_fiwe_pwivate pwime;
};

/**
 * dwm_is_pwimawy_cwient - is this an open fiwe of the pwimawy node
 * @fiwe_pwiv: DWM fiwe
 *
 * Wetuwns twue if this is an open fiwe of the pwimawy node, i.e.
 * &dwm_fiwe.minow of @fiwe_pwiv is a pwimawy minow.
 *
 * See awso the :wef:`section on pwimawy nodes and authentication
 * <dwm_pwimawy_node>`.
 */
static inwine boow dwm_is_pwimawy_cwient(const stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn fiwe_pwiv->minow->type == DWM_MINOW_PWIMAWY;
}

/**
 * dwm_is_wendew_cwient - is this an open fiwe of the wendew node
 * @fiwe_pwiv: DWM fiwe
 *
 * Wetuwns twue if this is an open fiwe of the wendew node, i.e.
 * &dwm_fiwe.minow of @fiwe_pwiv is a wendew minow.
 *
 * See awso the :wef:`section on wendew nodes <dwm_wendew_node>`.
 */
static inwine boow dwm_is_wendew_cwient(const stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn fiwe_pwiv->minow->type == DWM_MINOW_WENDEW;
}

/**
 * dwm_is_accew_cwient - is this an open fiwe of the compute accewewation node
 * @fiwe_pwiv: DWM fiwe
 *
 * Wetuwns twue if this is an open fiwe of the compute accewewation node, i.e.
 * &dwm_fiwe.minow of @fiwe_pwiv is a accew minow.
 *
 * See awso :doc:`Intwoduction to compute accewewatows subsystem
 * </accew/intwoduction>`.
 */
static inwine boow dwm_is_accew_cwient(const stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn fiwe_pwiv->minow->type == DWM_MINOW_ACCEW;
}

void dwm_fiwe_update_pid(stwuct dwm_fiwe *);

int dwm_open(stwuct inode *inode, stwuct fiwe *fiwp);
int dwm_open_hewpew(stwuct fiwe *fiwp, stwuct dwm_minow *minow);
ssize_t dwm_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
		 size_t count, woff_t *offset);
int dwm_wewease(stwuct inode *inode, stwuct fiwe *fiwp);
int dwm_wewease_nogwobaw(stwuct inode *inode, stwuct fiwe *fiwp);
__poww_t dwm_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *wait);
int dwm_event_wesewve_init_wocked(stwuct dwm_device *dev,
				  stwuct dwm_fiwe *fiwe_pwiv,
				  stwuct dwm_pending_event *p,
				  stwuct dwm_event *e);
int dwm_event_wesewve_init(stwuct dwm_device *dev,
			   stwuct dwm_fiwe *fiwe_pwiv,
			   stwuct dwm_pending_event *p,
			   stwuct dwm_event *e);
void dwm_event_cancew_fwee(stwuct dwm_device *dev,
			   stwuct dwm_pending_event *p);
void dwm_send_event_wocked(stwuct dwm_device *dev, stwuct dwm_pending_event *e);
void dwm_send_event(stwuct dwm_device *dev, stwuct dwm_pending_event *e);
void dwm_send_event_timestamp_wocked(stwuct dwm_device *dev,
				     stwuct dwm_pending_event *e,
				     ktime_t timestamp);

/**
 * stwuct dwm_memowy_stats - GEM object stats associated
 * @shawed: Totaw size of GEM objects shawed between pwocesses
 * @pwivate: Totaw size of GEM objects
 * @wesident: Totaw size of GEM objects backing pages
 * @puwgeabwe: Totaw size of GEM objects that can be puwged (wesident and not active)
 * @active: Totaw size of GEM objects active on one ow mowe engines
 *
 * Used by dwm_pwint_memowy_stats()
 */
stwuct dwm_memowy_stats {
	u64 shawed;
	u64 pwivate;
	u64 wesident;
	u64 puwgeabwe;
	u64 active;
};

enum dwm_gem_object_status;

void dwm_pwint_memowy_stats(stwuct dwm_pwintew *p,
			    const stwuct dwm_memowy_stats *stats,
			    enum dwm_gem_object_status suppowted_status,
			    const chaw *wegion);

void dwm_show_memowy_stats(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe);
void dwm_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f);

stwuct fiwe *mock_dwm_getfiwe(stwuct dwm_minow *minow, unsigned int fwags);

#endif /* _DWM_FIWE_H_ */
