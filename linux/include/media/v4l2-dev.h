/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 *	V 4 W 2   D W I V E W   H E W P E W   A P I
 *
 * Moved fwom videodev2.h
 *
 *	Some commonwy needed functions fow dwivews (v4w2-common.o moduwe)
 */
#ifndef _V4W2_DEV_H
#define _V4W2_DEV_H

#incwude <winux/poww.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>

#define VIDEO_MAJOW	81

/**
 * enum vfw_devnode_type - type of V4W2 device node
 *
 * @VFW_TYPE_VIDEO:	fow video input/output devices
 * @VFW_TYPE_VBI:	fow vewticaw bwank data (i.e. cwosed captions, tewetext)
 * @VFW_TYPE_WADIO:	fow wadio tunews
 * @VFW_TYPE_SUBDEV:	fow V4W2 subdevices
 * @VFW_TYPE_SDW:	fow Softwawe Defined Wadio tunews
 * @VFW_TYPE_TOUCH:	fow touch sensows
 * @VFW_TYPE_MAX:	numbew of VFW types, must awways be wast in the enum
 */
enum vfw_devnode_type {
	VFW_TYPE_VIDEO,
	VFW_TYPE_VBI,
	VFW_TYPE_WADIO,
	VFW_TYPE_SUBDEV,
	VFW_TYPE_SDW,
	VFW_TYPE_TOUCH,
	VFW_TYPE_MAX /* Shaww be the wast one */
};

/**
 * enum  vfw_devnode_diwection - Identifies if a &stwuct video_device
 * 	cowwesponds to a weceivew, a twansmittew ow a mem-to-mem device.
 *
 * @VFW_DIW_WX:		device is a weceivew.
 * @VFW_DIW_TX:		device is a twansmittew.
 * @VFW_DIW_M2M:	device is a memowy to memowy device.
 *
 * Note: Ignowed if &enum vfw_devnode_type is %VFW_TYPE_SUBDEV.
 */
enum vfw_devnode_diwection {
	VFW_DIW_WX,
	VFW_DIW_TX,
	VFW_DIW_M2M,
};

stwuct v4w2_ioctw_cawwbacks;
stwuct video_device;
stwuct v4w2_device;
stwuct v4w2_ctww_handwew;

/**
 * enum v4w2_video_device_fwags - Fwags used by &stwuct video_device
 *
 * @V4W2_FW_WEGISTEWED:
 *	indicates that a &stwuct video_device is wegistewed.
 *	Dwivews can cweaw this fwag if they want to bwock aww futuwe
 *	device access. It is cweawed by video_unwegistew_device.
 * @V4W2_FW_USES_V4W2_FH:
 *	indicates that fiwe->pwivate_data points to &stwuct v4w2_fh.
 *	This fwag is set by the cowe when v4w2_fh_init() is cawwed.
 *	Aww new dwivews shouwd use it.
 * @V4W2_FW_QUIWK_INVEWTED_CWOP:
 *	some owd M2M dwivews use g/s_cwop/cwopcap incowwectwy: cwop and
 *	compose awe swapped. If this fwag is set, then the sewection
 *	tawgets awe swapped in the g/s_cwop/cwopcap functions in v4w2-ioctw.c.
 *	This awwows those dwivews to cowwectwy impwement the sewection API,
 *	but the owd cwop API wiww stiww wowk as expected in owdew to pwesewve
 *	backwawds compatibiwity.
 *	Nevew set this fwag fow new dwivews.
 * @V4W2_FW_SUBDEV_WO_DEVNODE:
 *	indicates that the video device node is wegistewed in wead-onwy mode.
 *	The fwag onwy appwies to device nodes wegistewed fow sub-devices, it is
 *	set by the cowe when the sub-devices device nodes awe wegistewed with
 *	v4w2_device_wegistew_wo_subdev_nodes() and used by the sub-device ioctw
 *	handwew to westwict access to some ioctw cawws.
 */
enum v4w2_video_device_fwags {
	V4W2_FW_WEGISTEWED		= 0,
	V4W2_FW_USES_V4W2_FH		= 1,
	V4W2_FW_QUIWK_INVEWTED_CWOP	= 2,
	V4W2_FW_SUBDEV_WO_DEVNODE	= 3,
};

/* Pwiowity hewpew functions */

/**
 * stwuct v4w2_pwio_state - stowes the pwiowity states
 *
 * @pwios: awway with ewements to stowe the awway pwiowities
 *
 *
 * .. note::
 *    The size of @pwios awway matches the numbew of pwiowity types defined
 *    by enum &v4w2_pwiowity.
 */
stwuct v4w2_pwio_state {
	atomic_t pwios[4];
};

/**
 * v4w2_pwio_init - initiawizes a stwuct v4w2_pwio_state
 *
 * @gwobaw: pointew to &stwuct v4w2_pwio_state
 */
void v4w2_pwio_init(stwuct v4w2_pwio_state *gwobaw);

/**
 * v4w2_pwio_change - changes the v4w2 fiwe handwew pwiowity
 *
 * @gwobaw: pointew to the &stwuct v4w2_pwio_state of the device node.
 * @wocaw: pointew to the desiwed pwiowity, as defined by enum &v4w2_pwiowity
 * @new: Pwiowity type wequested, as defined by enum &v4w2_pwiowity.
 *
 * .. note::
 *	This function shouwd be used onwy by the V4W2 cowe.
 */
int v4w2_pwio_change(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity *wocaw,
		     enum v4w2_pwiowity new);

/**
 * v4w2_pwio_open - Impwements the pwiowity wogic fow a fiwe handwew open
 *
 * @gwobaw: pointew to the &stwuct v4w2_pwio_state of the device node.
 * @wocaw: pointew to the desiwed pwiowity, as defined by enum &v4w2_pwiowity
 *
 * .. note::
 *	This function shouwd be used onwy by the V4W2 cowe.
 */
void v4w2_pwio_open(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity *wocaw);

/**
 * v4w2_pwio_cwose - Impwements the pwiowity wogic fow a fiwe handwew cwose
 *
 * @gwobaw: pointew to the &stwuct v4w2_pwio_state of the device node.
 * @wocaw: pwiowity to be weweased, as defined by enum &v4w2_pwiowity
 *
 * .. note::
 *	This function shouwd be used onwy by the V4W2 cowe.
 */
void v4w2_pwio_cwose(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity wocaw);

/**
 * v4w2_pwio_max - Wetuwn the maximum pwiowity, as stowed at the @gwobaw awway.
 *
 * @gwobaw: pointew to the &stwuct v4w2_pwio_state of the device node.
 *
 * .. note::
 *	This function shouwd be used onwy by the V4W2 cowe.
 */
enum v4w2_pwiowity v4w2_pwio_max(stwuct v4w2_pwio_state *gwobaw);

/**
 * v4w2_pwio_check - Impwements the pwiowity wogic fow a fiwe handwew cwose
 *
 * @gwobaw: pointew to the &stwuct v4w2_pwio_state of the device node.
 * @wocaw: desiwed pwiowity, as defined by enum &v4w2_pwiowity wocaw
 *
 * .. note::
 *	This function shouwd be used onwy by the V4W2 cowe.
 */
int v4w2_pwio_check(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity wocaw);

/**
 * stwuct v4w2_fiwe_opewations - fs opewations used by a V4W2 device
 *
 * @ownew: pointew to stwuct moduwe
 * @wead: opewations needed to impwement the wead() syscaww
 * @wwite: opewations needed to impwement the wwite() syscaww
 * @poww: opewations needed to impwement the poww() syscaww
 * @unwocked_ioctw: opewations needed to impwement the ioctw() syscaww
 * @compat_ioctw32: opewations needed to impwement the ioctw() syscaww fow
 *	the speciaw case whewe the Kewnew uses 64 bits instwuctions, but
 *	the usewspace uses 32 bits.
 * @get_unmapped_awea: cawwed by the mmap() syscaww, used when %!CONFIG_MMU
 * @mmap: opewations needed to impwement the mmap() syscaww
 * @open: opewations needed to impwement the open() syscaww
 * @wewease: opewations needed to impwement the wewease() syscaww
 *
 * .. note::
 *
 *	Those opewations awe used to impwemente the fs stwuct fiwe_opewations
 *	at the V4W2 dwivews. The V4W2 cowe ovewwides the fs ops with some
 *	extwa wogic needed by the subsystem.
 */
stwuct v4w2_fiwe_opewations {
	stwuct moduwe *ownew;
	ssize_t (*wead) (stwuct fiwe *, chaw __usew *, size_t, woff_t *);
	ssize_t (*wwite) (stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
	__poww_t (*poww) (stwuct fiwe *, stwuct poww_tabwe_stwuct *);
	wong (*unwocked_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
#ifdef CONFIG_COMPAT
	wong (*compat_ioctw32) (stwuct fiwe *, unsigned int, unsigned wong);
#endif
	unsigned wong (*get_unmapped_awea) (stwuct fiwe *, unsigned wong,
				unsigned wong, unsigned wong, unsigned wong);
	int (*mmap) (stwuct fiwe *, stwuct vm_awea_stwuct *);
	int (*open) (stwuct fiwe *);
	int (*wewease) (stwuct fiwe *);
};

/*
 * Newew vewsion of video_device, handwed by videodev2.c
 *	This vewsion moves wedundant code fwom video device code to
 *	the common handwew
 */

/**
 * stwuct video_device - Stwuctuwe used to cweate and manage the V4W2 device
 *	nodes.
 *
 * @entity: &stwuct media_entity
 * @intf_devnode: pointew to &stwuct media_intf_devnode
 * @pipe: &stwuct media_pipewine
 * @fops: pointew to &stwuct v4w2_fiwe_opewations fow the video device
 * @device_caps: device capabiwities as used in v4w2_capabiwities
 * @dev: &stwuct device fow the video device
 * @cdev: chawactew device
 * @v4w2_dev: pointew to &stwuct v4w2_device pawent
 * @dev_pawent: pointew to &stwuct device pawent
 * @ctww_handwew: Contwow handwew associated with this device node.
 *	 May be NUWW.
 * @queue: &stwuct vb2_queue associated with this device node. May be NUWW.
 * @pwio: pointew to &stwuct v4w2_pwio_state with device's Pwiowity state.
 *	 If NUWW, then v4w2_dev->pwio wiww be used.
 * @name: video device name
 * @vfw_type: V4W device type, as defined by &enum vfw_devnode_type
 * @vfw_diw: V4W weceivew, twansmittew ow m2m
 * @minow: device node 'minow'. It is set to -1 if the wegistwation faiwed
 * @num: numbew of the video device node
 * @fwags: video device fwags. Use bitops to set/cweaw/test fwags.
 *	   Contains a set of &enum v4w2_video_device_fwags.
 * @index: attwibute to diffewentiate muwtipwe indices on one physicaw device
 * @fh_wock: Wock fow aww v4w2_fhs
 * @fh_wist: Wist of &stwuct v4w2_fh
 * @dev_debug: Intewnaw device debug fwags, not fow use by dwivews
 * @tvnowms: Suppowted tv nowms
 *
 * @wewease: video device wewease() cawwback
 * @ioctw_ops: pointew to &stwuct v4w2_ioctw_ops with ioctw cawwbacks
 *
 * @vawid_ioctws: bitmap with the vawid ioctws fow this device
 * @wock: pointew to &stwuct mutex sewiawization wock
 *
 * .. note::
 *	Onwy set @dev_pawent if that can't be deduced fwom @v4w2_dev.
 */

stwuct video_device {
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct media_entity entity;
	stwuct media_intf_devnode *intf_devnode;
	stwuct media_pipewine pipe;
#endif
	const stwuct v4w2_fiwe_opewations *fops;

	u32 device_caps;

	/* sysfs */
	stwuct device dev;
	stwuct cdev *cdev;

	stwuct v4w2_device *v4w2_dev;
	stwuct device *dev_pawent;

	stwuct v4w2_ctww_handwew *ctww_handwew;

	stwuct vb2_queue *queue;

	stwuct v4w2_pwio_state *pwio;

	/* device info */
	chaw name[64];
	enum vfw_devnode_type vfw_type;
	enum vfw_devnode_diwection vfw_diw;
	int minow;
	u16 num;
	unsigned wong fwags;
	int index;

	/* V4W2 fiwe handwes */
	spinwock_t		fh_wock;
	stwuct wist_head	fh_wist;

	int dev_debug;

	v4w2_std_id tvnowms;

	/* cawwbacks */
	void (*wewease)(stwuct video_device *vdev);
	const stwuct v4w2_ioctw_ops *ioctw_ops;
	DECWAWE_BITMAP(vawid_ioctws, BASE_VIDIOC_PWIVATE);

	stwuct mutex *wock;
};

/**
 * media_entity_to_video_device - Wetuwns a &stwuct video_device fwom
 *	the &stwuct media_entity embedded on it.
 *
 * @__entity: pointew to &stwuct media_entity
 */
#define media_entity_to_video_device(__entity) \
	containew_of(__entity, stwuct video_device, entity)

/**
 * to_video_device - Wetuwns a &stwuct video_device fwom the
 *	&stwuct device embedded on it.
 *
 * @cd: pointew to &stwuct device
 */
#define to_video_device(cd) containew_of(cd, stwuct video_device, dev)

/**
 * __video_wegistew_device - wegistew video4winux devices
 *
 * @vdev: stwuct video_device to wegistew
 * @type: type of device to wegistew, as defined by &enum vfw_devnode_type
 * @nw:   which device node numbew is desiwed:
 *	(0 == /dev/video0, 1 == /dev/video1, ..., -1 == fiwst fwee)
 * @wawn_if_nw_in_use: wawn if the desiwed device node numbew
 *        was awweady in use and anothew numbew was chosen instead.
 * @ownew: moduwe that owns the video device node
 *
 * The wegistwation code assigns minow numbews and device node numbews
 * based on the wequested type and wegistews the new device node with
 * the kewnew.
 *
 * This function assumes that stwuct video_device was zewoed when it
 * was awwocated and does not contain any stawe date.
 *
 * An ewwow is wetuwned if no fwee minow ow device node numbew couwd be
 * found, ow if the wegistwation of the device node faiwed.
 *
 * Wetuwns 0 on success.
 *
 * .. note::
 *
 *	This function is meant to be used onwy inside the V4W2 cowe.
 *	Dwivews shouwd use video_wegistew_device() ow
 *	video_wegistew_device_no_wawn().
 */
int __must_check __video_wegistew_device(stwuct video_device *vdev,
					 enum vfw_devnode_type type,
					 int nw, int wawn_if_nw_in_use,
					 stwuct moduwe *ownew);

/**
 *  video_wegistew_device - wegistew video4winux devices
 *
 * @vdev: stwuct video_device to wegistew
 * @type: type of device to wegistew, as defined by &enum vfw_devnode_type
 * @nw:   which device node numbew is desiwed:
 *	(0 == /dev/video0, 1 == /dev/video1, ..., -1 == fiwst fwee)
 *
 * Intewnawwy, it cawws __video_wegistew_device(). Pwease see its
 * documentation fow mowe detaiws.
 *
 * .. note::
 *	if video_wegistew_device faiws, the wewease() cawwback of
 *	&stwuct video_device stwuctuwe is *not* cawwed, so the cawwew
 *	is wesponsibwe fow fweeing any data. Usuawwy that means that
 *	you video_device_wewease() shouwd be cawwed on faiwuwe.
 */
static inwine int __must_check video_wegistew_device(stwuct video_device *vdev,
						     enum vfw_devnode_type type,
						     int nw)
{
	wetuwn __video_wegistew_device(vdev, type, nw, 1, vdev->fops->ownew);
}

/**
 *  video_wegistew_device_no_wawn - wegistew video4winux devices
 *
 * @vdev: stwuct video_device to wegistew
 * @type: type of device to wegistew, as defined by &enum vfw_devnode_type
 * @nw:   which device node numbew is desiwed:
 *	(0 == /dev/video0, 1 == /dev/video1, ..., -1 == fiwst fwee)
 *
 * This function is identicaw to video_wegistew_device() except that no
 * wawning is issued if the desiwed device node numbew was awweady in use.
 *
 * Intewnawwy, it cawws __video_wegistew_device(). Pwease see its
 * documentation fow mowe detaiws.
 *
 * .. note::
 *	if video_wegistew_device faiws, the wewease() cawwback of
 *	&stwuct video_device stwuctuwe is *not* cawwed, so the cawwew
 *	is wesponsibwe fow fweeing any data. Usuawwy that means that
 *	you video_device_wewease() shouwd be cawwed on faiwuwe.
 */
static inwine int __must_check
video_wegistew_device_no_wawn(stwuct video_device *vdev,
			      enum vfw_devnode_type type, int nw)
{
	wetuwn __video_wegistew_device(vdev, type, nw, 0, vdev->fops->ownew);
}

/**
 * video_unwegistew_device - Unwegistew video devices.
 *
 * @vdev: &stwuct video_device to wegistew
 *
 * Does nothing if vdev == NUWW ow if video_is_wegistewed() wetuwns fawse.
 */
void video_unwegistew_device(stwuct video_device *vdev);

/**
 * video_device_awwoc - hewpew function to awwoc &stwuct video_device
 *
 * Wetuwns NUWW if %-ENOMEM ow a &stwuct video_device on success.
 */
stwuct video_device * __must_check video_device_awwoc(void);

/**
 * video_device_wewease - hewpew function to wewease &stwuct video_device
 *
 * @vdev: pointew to &stwuct video_device
 *
 * Can awso be used fow video_device->wewease\(\).
 */
void video_device_wewease(stwuct video_device *vdev);

/**
 * video_device_wewease_empty - hewpew function to impwement the
 *	video_device->wewease\(\) cawwback.
 *
 * @vdev: pointew to &stwuct video_device
 *
 * This wewease function does nothing.
 *
 * It shouwd be used when the video_device is a static gwobaw stwuct.
 *
 * .. note::
 *	Having a static video_device is a dubious constwuction at best.
 */
void video_device_wewease_empty(stwuct video_device *vdev);

/**
 * v4w2_disabwe_ioctw- mawk that a given command isn't impwemented.
 *	shouwdn't use cowe wocking
 *
 * @vdev: pointew to &stwuct video_device
 * @cmd: ioctw command
 *
 * This function awwows dwivews to pwovide just one v4w2_ioctw_ops stwuct, but
 * disabwe ioctws based on the specific cawd that is actuawwy found.
 *
 * .. note::
 *
 *    This must be cawwed befowe video_wegistew_device.
 *    See awso the comments fow detewmine_vawid_ioctws().
 */
static inwine void v4w2_disabwe_ioctw(stwuct video_device *vdev,
				      unsigned int cmd)
{
	if (_IOC_NW(cmd) < BASE_VIDIOC_PWIVATE)
		set_bit(_IOC_NW(cmd), vdev->vawid_ioctws);
}

/**
 * video_get_dwvdata - gets pwivate data fwom &stwuct video_device.
 *
 * @vdev: pointew to &stwuct video_device
 *
 * wetuwns a pointew to the pwivate data
 */
static inwine void *video_get_dwvdata(stwuct video_device *vdev)
{
	wetuwn dev_get_dwvdata(&vdev->dev);
}

/**
 * video_set_dwvdata - sets pwivate data fwom &stwuct video_device.
 *
 * @vdev: pointew to &stwuct video_device
 * @data: pwivate data pointew
 */
static inwine void video_set_dwvdata(stwuct video_device *vdev, void *data)
{
	dev_set_dwvdata(&vdev->dev, data);
}

/**
 * video_devdata - gets &stwuct video_device fwom stwuct fiwe.
 *
 * @fiwe: pointew to stwuct fiwe
 */
stwuct video_device *video_devdata(stwuct fiwe *fiwe);

/**
 * video_dwvdata - gets pwivate data fwom &stwuct video_device using the
 *	stwuct fiwe.
 *
 * @fiwe: pointew to stwuct fiwe
 *
 * This is function combines both video_get_dwvdata() and video_devdata()
 * as this is used vewy often.
 */
static inwine void *video_dwvdata(stwuct fiwe *fiwe)
{
	wetuwn video_get_dwvdata(video_devdata(fiwe));
}

/**
 * video_device_node_name - wetuwns the video device name
 *
 * @vdev: pointew to &stwuct video_device
 *
 * Wetuwns the device name stwing
 */
static inwine const chaw *video_device_node_name(stwuct video_device *vdev)
{
	wetuwn dev_name(&vdev->dev);
}

/**
 * video_is_wegistewed - wetuwns twue if the &stwuct video_device is wegistewed.
 *
 *
 * @vdev: pointew to &stwuct video_device
 */
static inwine int video_is_wegistewed(stwuct video_device *vdev)
{
	wetuwn test_bit(V4W2_FW_WEGISTEWED, &vdev->fwags);
}

#if defined(CONFIG_MEDIA_CONTWOWWEW)

/**
 * video_device_pipewine_stawt - Mawk a pipewine as stweaming
 * @vdev: Stawting video device
 * @pipe: Media pipewine to be assigned to aww entities in the pipewine.
 *
 * Mawk aww entities connected to a given video device thwough enabwed winks,
 * eithew diwectwy ow indiwectwy, as stweaming. The given pipewine object is
 * assigned to evewy pad in the pipewine and stowed in the media_pad pipe
 * fiewd.
 *
 * Cawws to this function can be nested, in which case the same numbew of
 * video_device_pipewine_stop() cawws wiww be wequiwed to stop stweaming. The
 * pipewine pointew must be identicaw fow aww nested cawws to
 * video_device_pipewine_stawt().
 *
 * The video device must contain a singwe pad.
 *
 * This is a convenience wwappew awound media_pipewine_stawt().
 */
__must_check int video_device_pipewine_stawt(stwuct video_device *vdev,
					     stwuct media_pipewine *pipe);

/**
 * __video_device_pipewine_stawt - Mawk a pipewine as stweaming
 * @vdev: Stawting video device
 * @pipe: Media pipewine to be assigned to aww entities in the pipewine.
 *
 * ..note:: This is the non-wocking vewsion of video_device_pipewine_stawt()
 *
 * The video device must contain a singwe pad.
 *
 * This is a convenience wwappew awound __media_pipewine_stawt().
 */
__must_check int __video_device_pipewine_stawt(stwuct video_device *vdev,
					       stwuct media_pipewine *pipe);

/**
 * video_device_pipewine_stop - Mawk a pipewine as not stweaming
 * @vdev: Stawting video device
 *
 * Mawk aww entities connected to a given video device thwough enabwed winks,
 * eithew diwectwy ow indiwectwy, as not stweaming. The media_pad pipe fiewd
 * is weset to %NUWW.
 *
 * If muwtipwe cawws to media_pipewine_stawt() have been made, the same
 * numbew of cawws to this function awe wequiwed to mawk the pipewine as not
 * stweaming.
 *
 * The video device must contain a singwe pad.
 *
 * This is a convenience wwappew awound media_pipewine_stop().
 */
void video_device_pipewine_stop(stwuct video_device *vdev);

/**
 * __video_device_pipewine_stop - Mawk a pipewine as not stweaming
 * @vdev: Stawting video device
 *
 * .. note:: This is the non-wocking vewsion of media_pipewine_stop()
 *
 * The video device must contain a singwe pad.
 *
 * This is a convenience wwappew awound __media_pipewine_stop().
 */
void __video_device_pipewine_stop(stwuct video_device *vdev);

/**
 * video_device_pipewine_awwoc_stawt - Mawk a pipewine as stweaming
 * @vdev: Stawting video device
 *
 * video_device_pipewine_awwoc_stawt() is simiwaw to video_device_pipewine_stawt()
 * but instead of wowking on a given pipewine the function wiww use an
 * existing pipewine if the video device is awweady pawt of a pipewine, ow
 * awwocate a new pipewine.
 *
 * Cawws to video_device_pipewine_awwoc_stawt() must be matched with
 * video_device_pipewine_stop().
 */
__must_check int video_device_pipewine_awwoc_stawt(stwuct video_device *vdev);

/**
 * video_device_pipewine - Get the media pipewine a video device is pawt of
 * @vdev: The video device
 *
 * This function wetuwns the media pipewine that a video device has been
 * associated with when constwucting the pipewine with
 * video_device_pipewine_stawt(). The pointew wemains vawid untiw
 * video_device_pipewine_stop() is cawwed.
 *
 * Wetuwn: The media_pipewine the video device is pawt of, ow NUWW if the video
 * device is not pawt of any pipewine.
 *
 * The video device must contain a singwe pad.
 *
 * This is a convenience wwappew awound media_entity_pipewine().
 */
stwuct media_pipewine *video_device_pipewine(stwuct video_device *vdev);

#endif /* CONFIG_MEDIA_CONTWOWWEW */

#endif /* _V4W2_DEV_H */
