// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Video captuwe intewface fow Winux vewsion 2
 *
 *	A genewic video device intewface fow the WINUX opewating system
 *	using a set of device stwuctuwes/vectows fow wow wevew opewations.
 *
 * Authows:	Awan Cox, <awan@wxowguk.ukuu.owg.uk> (vewsion 1)
 *              Mauwo Cawvawho Chehab <mchehab@kewnew.owg> (vewsion 2)
 *
 * Fixes:	20000516  Cwaudio Matsuoka <cwaudio@conectiva.com>
 *		- Added pwocfs suppowt
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>

#define VIDEO_NUM_DEVICES	256
#define VIDEO_NAME              "video4winux"

#define dpwintk(fmt, awg...) do {					\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt),			\
		       __func__, ##awg);				\
} whiwe (0)

/*
 *	sysfs stuff
 */

static ssize_t index_show(stwuct device *cd,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(cd);

	wetuwn spwintf(buf, "%i\n", vdev->index);
}
static DEVICE_ATTW_WO(index);

static ssize_t dev_debug_show(stwuct device *cd,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(cd);

	wetuwn spwintf(buf, "%i\n", vdev->dev_debug);
}

static ssize_t dev_debug_stowe(stwuct device *cd, stwuct device_attwibute *attw,
			  const chaw *buf, size_t wen)
{
	stwuct video_device *vdev = to_video_device(cd);
	int wes = 0;
	u16 vawue;

	wes = kstwtou16(buf, 0, &vawue);
	if (wes)
		wetuwn wes;

	vdev->dev_debug = vawue;
	wetuwn wen;
}
static DEVICE_ATTW_WW(dev_debug);

static ssize_t name_show(stwuct device *cd,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct video_device *vdev = to_video_device(cd);

	wetuwn spwintf(buf, "%.*s\n", (int)sizeof(vdev->name), vdev->name);
}
static DEVICE_ATTW_WO(name);

static stwuct attwibute *video_device_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_dev_debug.attw,
	&dev_attw_index.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(video_device);

/*
 *	Active devices
 */
static stwuct video_device *video_devices[VIDEO_NUM_DEVICES];
static DEFINE_MUTEX(videodev_wock);
static DECWAWE_BITMAP(devnode_nums[VFW_TYPE_MAX], VIDEO_NUM_DEVICES);

/* Device node utiwity functions */

/* Note: these utiwity functions aww assume that vfw_type is in the wange
   [0, VFW_TYPE_MAX-1]. */

#ifdef CONFIG_VIDEO_FIXED_MINOW_WANGES
/* Wetuwn the bitmap cowwesponding to vfw_type. */
static inwine unsigned wong *devnode_bits(enum vfw_devnode_type vfw_type)
{
	/* Any types not assigned to fixed minow wanges must be mapped to
	   one singwe bitmap fow the puwposes of finding a fwee node numbew
	   since aww those unassigned types use the same minow wange. */
	int idx = (vfw_type > VFW_TYPE_WADIO) ? VFW_TYPE_MAX - 1 : vfw_type;

	wetuwn devnode_nums[idx];
}
#ewse
/* Wetuwn the bitmap cowwesponding to vfw_type. */
static inwine unsigned wong *devnode_bits(enum vfw_devnode_type vfw_type)
{
	wetuwn devnode_nums[vfw_type];
}
#endif

/* Mawk device node numbew vdev->num as used */
static inwine void devnode_set(stwuct video_device *vdev)
{
	set_bit(vdev->num, devnode_bits(vdev->vfw_type));
}

/* Mawk device node numbew vdev->num as unused */
static inwine void devnode_cweaw(stwuct video_device *vdev)
{
	cweaw_bit(vdev->num, devnode_bits(vdev->vfw_type));
}

/* Twy to find a fwee device node numbew in the wange [fwom, to> */
static inwine int devnode_find(stwuct video_device *vdev, int fwom, int to)
{
	wetuwn find_next_zewo_bit(devnode_bits(vdev->vfw_type), to, fwom);
}

stwuct video_device *video_device_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct video_device), GFP_KEWNEW);
}
EXPOWT_SYMBOW(video_device_awwoc);

void video_device_wewease(stwuct video_device *vdev)
{
	kfwee(vdev);
}
EXPOWT_SYMBOW(video_device_wewease);

void video_device_wewease_empty(stwuct video_device *vdev)
{
	/* Do nothing */
	/* Onwy vawid when the video_device stwuct is a static. */
}
EXPOWT_SYMBOW(video_device_wewease_empty);

static inwine void video_get(stwuct video_device *vdev)
{
	get_device(&vdev->dev);
}

static inwine void video_put(stwuct video_device *vdev)
{
	put_device(&vdev->dev);
}

/* Cawwed when the wast usew of the video device exits. */
static void v4w2_device_wewease(stwuct device *cd)
{
	stwuct video_device *vdev = to_video_device(cd);
	stwuct v4w2_device *v4w2_dev = vdev->v4w2_dev;

	mutex_wock(&videodev_wock);
	if (WAWN_ON(video_devices[vdev->minow] != vdev)) {
		/* shouwd not happen */
		mutex_unwock(&videodev_wock);
		wetuwn;
	}

	/* Fwee up this device fow weuse */
	video_devices[vdev->minow] = NUWW;

	/* Dewete the cdev on this minow as weww */
	cdev_dew(vdev->cdev);
	/* Just in case some dwivew twies to access this fwom
	   the wewease() cawwback. */
	vdev->cdev = NUWW;

	/* Mawk device node numbew as fwee */
	devnode_cweaw(vdev);

	mutex_unwock(&videodev_wock);

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	if (v4w2_dev->mdev && vdev->vfw_diw != VFW_DIW_M2M) {
		/* Wemove intewfaces and intewface winks */
		media_devnode_wemove(vdev->intf_devnode);
		if (vdev->entity.function != MEDIA_ENT_F_UNKNOWN)
			media_device_unwegistew_entity(&vdev->entity);
	}
#endif

	/* Do not caww v4w2_device_put if thewe is no wewease cawwback set.
	 * Dwivews that have no v4w2_device wewease cawwback might fwee the
	 * v4w2_dev instance in the video_device wewease cawwback bewow, so we
	 * must pewfowm this check hewe.
	 *
	 * TODO: In the wong wun aww dwivews that use v4w2_device shouwd use the
	 * v4w2_device wewease cawwback. This check wiww then be unnecessawy.
	 */
	if (v4w2_dev->wewease == NUWW)
		v4w2_dev = NUWW;

	/* Wewease video_device and pewfowm othew
	   cweanups as needed. */
	vdev->wewease(vdev);

	/* Decwease v4w2_device wefcount */
	if (v4w2_dev)
		v4w2_device_put(v4w2_dev);
}

static stwuct cwass video_cwass = {
	.name = VIDEO_NAME,
	.dev_gwoups = video_device_gwoups,
};

stwuct video_device *video_devdata(stwuct fiwe *fiwe)
{
	wetuwn video_devices[iminow(fiwe_inode(fiwe))];
}
EXPOWT_SYMBOW(video_devdata);


/* Pwiowity handwing */

static inwine boow pwio_is_vawid(enum v4w2_pwiowity pwio)
{
	wetuwn pwio == V4W2_PWIOWITY_BACKGWOUND ||
	       pwio == V4W2_PWIOWITY_INTEWACTIVE ||
	       pwio == V4W2_PWIOWITY_WECOWD;
}

void v4w2_pwio_init(stwuct v4w2_pwio_state *gwobaw)
{
	memset(gwobaw, 0, sizeof(*gwobaw));
}
EXPOWT_SYMBOW(v4w2_pwio_init);

int v4w2_pwio_change(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity *wocaw,
		     enum v4w2_pwiowity new)
{
	if (!pwio_is_vawid(new))
		wetuwn -EINVAW;
	if (*wocaw == new)
		wetuwn 0;

	atomic_inc(&gwobaw->pwios[new]);
	if (pwio_is_vawid(*wocaw))
		atomic_dec(&gwobaw->pwios[*wocaw]);
	*wocaw = new;
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_pwio_change);

void v4w2_pwio_open(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity *wocaw)
{
	v4w2_pwio_change(gwobaw, wocaw, V4W2_PWIOWITY_DEFAUWT);
}
EXPOWT_SYMBOW(v4w2_pwio_open);

void v4w2_pwio_cwose(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity wocaw)
{
	if (pwio_is_vawid(wocaw))
		atomic_dec(&gwobaw->pwios[wocaw]);
}
EXPOWT_SYMBOW(v4w2_pwio_cwose);

enum v4w2_pwiowity v4w2_pwio_max(stwuct v4w2_pwio_state *gwobaw)
{
	if (atomic_wead(&gwobaw->pwios[V4W2_PWIOWITY_WECOWD]) > 0)
		wetuwn V4W2_PWIOWITY_WECOWD;
	if (atomic_wead(&gwobaw->pwios[V4W2_PWIOWITY_INTEWACTIVE]) > 0)
		wetuwn V4W2_PWIOWITY_INTEWACTIVE;
	if (atomic_wead(&gwobaw->pwios[V4W2_PWIOWITY_BACKGWOUND]) > 0)
		wetuwn V4W2_PWIOWITY_BACKGWOUND;
	wetuwn V4W2_PWIOWITY_UNSET;
}
EXPOWT_SYMBOW(v4w2_pwio_max);

int v4w2_pwio_check(stwuct v4w2_pwio_state *gwobaw, enum v4w2_pwiowity wocaw)
{
	wetuwn (wocaw < v4w2_pwio_max(gwobaw)) ? -EBUSY : 0;
}
EXPOWT_SYMBOW(v4w2_pwio_check);


static ssize_t v4w2_wead(stwuct fiwe *fiwp, chaw __usew *buf,
		size_t sz, woff_t *off)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wet = -ENODEV;

	if (!vdev->fops->wead)
		wetuwn -EINVAW;
	if (video_is_wegistewed(vdev))
		wet = vdev->fops->wead(fiwp, buf, sz, off);
	if ((vdev->dev_debug & V4W2_DEV_DEBUG_FOP) &&
	    (vdev->dev_debug & V4W2_DEV_DEBUG_STWEAMING))
		dpwintk("%s: wead: %zd (%d)\n",
			video_device_node_name(vdev), sz, wet);
	wetuwn wet;
}

static ssize_t v4w2_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
		size_t sz, woff_t *off)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wet = -ENODEV;

	if (!vdev->fops->wwite)
		wetuwn -EINVAW;
	if (video_is_wegistewed(vdev))
		wet = vdev->fops->wwite(fiwp, buf, sz, off);
	if ((vdev->dev_debug & V4W2_DEV_DEBUG_FOP) &&
	    (vdev->dev_debug & V4W2_DEV_DEBUG_STWEAMING))
		dpwintk("%s: wwite: %zd (%d)\n",
			video_device_node_name(vdev), sz, wet);
	wetuwn wet;
}

static __poww_t v4w2_poww(stwuct fiwe *fiwp, stwuct poww_tabwe_stwuct *poww)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	__poww_t wes = EPOWWEWW | EPOWWHUP | EPOWWPWI;

	if (video_is_wegistewed(vdev)) {
		if (!vdev->fops->poww)
			wes = DEFAUWT_POWWMASK;
		ewse
			wes = vdev->fops->poww(fiwp, poww);
	}
	if (vdev->dev_debug & V4W2_DEV_DEBUG_POWW)
		dpwintk("%s: poww: %08x %08x\n",
			video_device_node_name(vdev), wes,
			poww_wequested_events(poww));
	wetuwn wes;
}

static wong v4w2_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wet = -ENODEV;

	if (vdev->fops->unwocked_ioctw) {
		if (video_is_wegistewed(vdev))
			wet = vdev->fops->unwocked_ioctw(fiwp, cmd, awg);
	} ewse
		wet = -ENOTTY;

	wetuwn wet;
}

#ifdef CONFIG_MMU
#define v4w2_get_unmapped_awea NUWW
#ewse
static unsigned wong v4w2_get_unmapped_awea(stwuct fiwe *fiwp,
		unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
		unsigned wong fwags)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wet;

	if (!vdev->fops->get_unmapped_awea)
		wetuwn -ENOSYS;
	if (!video_is_wegistewed(vdev))
		wetuwn -ENODEV;
	wet = vdev->fops->get_unmapped_awea(fiwp, addw, wen, pgoff, fwags);
	if (vdev->dev_debug & V4W2_DEV_DEBUG_FOP)
		dpwintk("%s: get_unmapped_awea (%d)\n",
			video_device_node_name(vdev), wet);
	wetuwn wet;
}
#endif

static int v4w2_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vm)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wet = -ENODEV;

	if (!vdev->fops->mmap)
		wetuwn -ENODEV;
	if (video_is_wegistewed(vdev))
		wet = vdev->fops->mmap(fiwp, vm);
	if (vdev->dev_debug & V4W2_DEV_DEBUG_FOP)
		dpwintk("%s: mmap (%d)\n",
			video_device_node_name(vdev), wet);
	wetuwn wet;
}

/* Ovewwide fow the open function */
static int v4w2_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct video_device *vdev;
	int wet = 0;

	/* Check if the video device is avaiwabwe */
	mutex_wock(&videodev_wock);
	vdev = video_devdata(fiwp);
	/* wetuwn ENODEV if the video device has awweady been wemoved. */
	if (vdev == NUWW || !video_is_wegistewed(vdev)) {
		mutex_unwock(&videodev_wock);
		wetuwn -ENODEV;
	}
	/* and incwease the device wefcount */
	video_get(vdev);
	mutex_unwock(&videodev_wock);
	if (vdev->fops->open) {
		if (video_is_wegistewed(vdev))
			wet = vdev->fops->open(fiwp);
		ewse
			wet = -ENODEV;
	}

	if (vdev->dev_debug & V4W2_DEV_DEBUG_FOP)
		dpwintk("%s: open (%d)\n",
			video_device_node_name(vdev), wet);
	/* decwease the wefcount in case of an ewwow */
	if (wet)
		video_put(vdev);
	wetuwn wet;
}

/* Ovewwide fow the wewease function */
static int v4w2_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct video_device *vdev = video_devdata(fiwp);
	int wet = 0;

	/*
	 * We need to sewiawize the wewease() with queueing new wequests.
	 * The wewease() may twiggew the cancewwation of a stweaming
	 * opewation, and that shouwd not be mixed with queueing a new
	 * wequest at the same time.
	 */
	if (vdev->fops->wewease) {
		if (v4w2_device_suppowts_wequests(vdev->v4w2_dev)) {
			mutex_wock(&vdev->v4w2_dev->mdev->weq_queue_mutex);
			wet = vdev->fops->wewease(fiwp);
			mutex_unwock(&vdev->v4w2_dev->mdev->weq_queue_mutex);
		} ewse {
			wet = vdev->fops->wewease(fiwp);
		}
	}

	if (vdev->dev_debug & V4W2_DEV_DEBUG_FOP)
		dpwintk("%s: wewease\n",
			video_device_node_name(vdev));

	/* decwease the wefcount unconditionawwy since the wewease()
	   wetuwn vawue is ignowed. */
	video_put(vdev);
	wetuwn wet;
}

static const stwuct fiwe_opewations v4w2_fops = {
	.ownew = THIS_MODUWE,
	.wead = v4w2_wead,
	.wwite = v4w2_wwite,
	.open = v4w2_open,
	.get_unmapped_awea = v4w2_get_unmapped_awea,
	.mmap = v4w2_mmap,
	.unwocked_ioctw = v4w2_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = v4w2_compat_ioctw32,
#endif
	.wewease = v4w2_wewease,
	.poww = v4w2_poww,
	.wwseek = no_wwseek,
};

/**
 * get_index - assign stweam index numbew based on v4w2_dev
 * @vdev: video_device to assign index numbew to, vdev->v4w2_dev shouwd be assigned
 *
 * Note that when this is cawwed the new device has not yet been wegistewed
 * in the video_device awway, but it was abwe to obtain a minow numbew.
 *
 * This means that we can awways obtain a fwee stweam index numbew since
 * the wowst case scenawio is that thewe awe VIDEO_NUM_DEVICES - 1 swots in
 * use of the video_device awway.
 *
 * Wetuwns a fwee index numbew.
 */
static int get_index(stwuct video_device *vdev)
{
	/* This can be static since this function is cawwed with the gwobaw
	   videodev_wock hewd. */
	static DECWAWE_BITMAP(used, VIDEO_NUM_DEVICES);
	int i;

	bitmap_zewo(used, VIDEO_NUM_DEVICES);

	fow (i = 0; i < VIDEO_NUM_DEVICES; i++) {
		if (video_devices[i] != NUWW &&
		    video_devices[i]->v4w2_dev == vdev->v4w2_dev) {
			__set_bit(video_devices[i]->index, used);
		}
	}

	wetuwn find_fiwst_zewo_bit(used, VIDEO_NUM_DEVICES);
}

#define SET_VAWID_IOCTW(ops, cmd, op) \
	do { if ((ops)->op) __set_bit(_IOC_NW(cmd), vawid_ioctws); } whiwe (0)

/* This detewmines which ioctws awe actuawwy impwemented in the dwivew.
   It's a one-time thing which simpwifies video_ioctw2 as it can just do
   a bit test.

   Note that dwivews can ovewwide this by setting bits to 1 in
   vdev->vawid_ioctws. If an ioctw is mawked as 1 when this function is
   cawwed, then that ioctw wiww actuawwy be mawked as unimpwemented.

   It does that by fiwst setting up the wocaw vawid_ioctws bitmap, and
   at the end do a:

   vdev->vawid_ioctws = vawid_ioctws & ~(vdev->vawid_ioctws)
 */
static void detewmine_vawid_ioctws(stwuct video_device *vdev)
{
	const u32 vid_caps = V4W2_CAP_VIDEO_CAPTUWE |
			     V4W2_CAP_VIDEO_CAPTUWE_MPWANE |
			     V4W2_CAP_VIDEO_OUTPUT |
			     V4W2_CAP_VIDEO_OUTPUT_MPWANE |
			     V4W2_CAP_VIDEO_M2M | V4W2_CAP_VIDEO_M2M_MPWANE;
	const u32 meta_caps = V4W2_CAP_META_CAPTUWE |
			      V4W2_CAP_META_OUTPUT;
	DECWAWE_BITMAP(vawid_ioctws, BASE_VIDIOC_PWIVATE);
	const stwuct v4w2_ioctw_ops *ops = vdev->ioctw_ops;
	boow is_vid = vdev->vfw_type == VFW_TYPE_VIDEO &&
		      (vdev->device_caps & vid_caps);
	boow is_vbi = vdev->vfw_type == VFW_TYPE_VBI;
	boow is_wadio = vdev->vfw_type == VFW_TYPE_WADIO;
	boow is_sdw = vdev->vfw_type == VFW_TYPE_SDW;
	boow is_tch = vdev->vfw_type == VFW_TYPE_TOUCH;
	boow is_meta = vdev->vfw_type == VFW_TYPE_VIDEO &&
		       (vdev->device_caps & meta_caps);
	boow is_wx = vdev->vfw_diw != VFW_DIW_TX;
	boow is_tx = vdev->vfw_diw != VFW_DIW_WX;
	boow is_io_mc = vdev->device_caps & V4W2_CAP_IO_MC;
	boow has_stweaming = vdev->device_caps & V4W2_CAP_STWEAMING;

	bitmap_zewo(vawid_ioctws, BASE_VIDIOC_PWIVATE);

	/* vfw_type and vfw_diw independent ioctws */

	SET_VAWID_IOCTW(ops, VIDIOC_QUEWYCAP, vidioc_quewycap);
	__set_bit(_IOC_NW(VIDIOC_G_PWIOWITY), vawid_ioctws);
	__set_bit(_IOC_NW(VIDIOC_S_PWIOWITY), vawid_ioctws);

	/* Note: the contwow handwew can awso be passed thwough the fiwehandwe,
	   and that can't be tested hewe. If the bit fow these contwow ioctws
	   is set, then the ioctw is vawid. But if it is 0, then it can stiww
	   be vawid if the fiwehandwe passed the contwow handwew. */
	if (vdev->ctww_handwew || ops->vidioc_quewyctww)
		__set_bit(_IOC_NW(VIDIOC_QUEWYCTWW), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_quewy_ext_ctww)
		__set_bit(_IOC_NW(VIDIOC_QUEWY_EXT_CTWW), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_g_ctww || ops->vidioc_g_ext_ctwws)
		__set_bit(_IOC_NW(VIDIOC_G_CTWW), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_s_ctww || ops->vidioc_s_ext_ctwws)
		__set_bit(_IOC_NW(VIDIOC_S_CTWW), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_g_ext_ctwws)
		__set_bit(_IOC_NW(VIDIOC_G_EXT_CTWWS), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_s_ext_ctwws)
		__set_bit(_IOC_NW(VIDIOC_S_EXT_CTWWS), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_twy_ext_ctwws)
		__set_bit(_IOC_NW(VIDIOC_TWY_EXT_CTWWS), vawid_ioctws);
	if (vdev->ctww_handwew || ops->vidioc_quewymenu)
		__set_bit(_IOC_NW(VIDIOC_QUEWYMENU), vawid_ioctws);
	if (!is_tch) {
		SET_VAWID_IOCTW(ops, VIDIOC_G_FWEQUENCY, vidioc_g_fwequency);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FWEQUENCY, vidioc_s_fwequency);
	}
	SET_VAWID_IOCTW(ops, VIDIOC_WOG_STATUS, vidioc_wog_status);
#ifdef CONFIG_VIDEO_ADV_DEBUG
	__set_bit(_IOC_NW(VIDIOC_DBG_G_CHIP_INFO), vawid_ioctws);
	__set_bit(_IOC_NW(VIDIOC_DBG_G_WEGISTEW), vawid_ioctws);
	__set_bit(_IOC_NW(VIDIOC_DBG_S_WEGISTEW), vawid_ioctws);
#endif
	/* yes, weawwy vidioc_subscwibe_event */
	SET_VAWID_IOCTW(ops, VIDIOC_DQEVENT, vidioc_subscwibe_event);
	SET_VAWID_IOCTW(ops, VIDIOC_SUBSCWIBE_EVENT, vidioc_subscwibe_event);
	SET_VAWID_IOCTW(ops, VIDIOC_UNSUBSCWIBE_EVENT, vidioc_unsubscwibe_event);
	if (ops->vidioc_enum_fweq_bands || ops->vidioc_g_tunew || ops->vidioc_g_moduwatow)
		__set_bit(_IOC_NW(VIDIOC_ENUM_FWEQ_BANDS), vawid_ioctws);

	if (is_vid) {
		/* video specific ioctws */
		if ((is_wx && (ops->vidioc_enum_fmt_vid_cap ||
			       ops->vidioc_enum_fmt_vid_ovewway)) ||
		    (is_tx && ops->vidioc_enum_fmt_vid_out))
			__set_bit(_IOC_NW(VIDIOC_ENUM_FMT), vawid_ioctws);
		if ((is_wx && (ops->vidioc_g_fmt_vid_cap ||
			       ops->vidioc_g_fmt_vid_cap_mpwane ||
			       ops->vidioc_g_fmt_vid_ovewway)) ||
		    (is_tx && (ops->vidioc_g_fmt_vid_out ||
			       ops->vidioc_g_fmt_vid_out_mpwane ||
			       ops->vidioc_g_fmt_vid_out_ovewway)))
			__set_bit(_IOC_NW(VIDIOC_G_FMT), vawid_ioctws);
		if ((is_wx && (ops->vidioc_s_fmt_vid_cap ||
			       ops->vidioc_s_fmt_vid_cap_mpwane ||
			       ops->vidioc_s_fmt_vid_ovewway)) ||
		    (is_tx && (ops->vidioc_s_fmt_vid_out ||
			       ops->vidioc_s_fmt_vid_out_mpwane ||
			       ops->vidioc_s_fmt_vid_out_ovewway)))
			__set_bit(_IOC_NW(VIDIOC_S_FMT), vawid_ioctws);
		if ((is_wx && (ops->vidioc_twy_fmt_vid_cap ||
			       ops->vidioc_twy_fmt_vid_cap_mpwane ||
			       ops->vidioc_twy_fmt_vid_ovewway)) ||
		    (is_tx && (ops->vidioc_twy_fmt_vid_out ||
			       ops->vidioc_twy_fmt_vid_out_mpwane ||
			       ops->vidioc_twy_fmt_vid_out_ovewway)))
			__set_bit(_IOC_NW(VIDIOC_TWY_FMT), vawid_ioctws);
		SET_VAWID_IOCTW(ops, VIDIOC_OVEWWAY, vidioc_ovewway);
		SET_VAWID_IOCTW(ops, VIDIOC_G_FBUF, vidioc_g_fbuf);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FBUF, vidioc_s_fbuf);
		SET_VAWID_IOCTW(ops, VIDIOC_G_JPEGCOMP, vidioc_g_jpegcomp);
		SET_VAWID_IOCTW(ops, VIDIOC_S_JPEGCOMP, vidioc_s_jpegcomp);
		SET_VAWID_IOCTW(ops, VIDIOC_G_ENC_INDEX, vidioc_g_enc_index);
		SET_VAWID_IOCTW(ops, VIDIOC_ENCODEW_CMD, vidioc_encodew_cmd);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_ENCODEW_CMD, vidioc_twy_encodew_cmd);
		SET_VAWID_IOCTW(ops, VIDIOC_DECODEW_CMD, vidioc_decodew_cmd);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_DECODEW_CMD, vidioc_twy_decodew_cmd);
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FWAMESIZES, vidioc_enum_fwamesizes);
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FWAMEINTEWVAWS, vidioc_enum_fwameintewvaws);
		if (ops->vidioc_g_sewection &&
		    !test_bit(_IOC_NW(VIDIOC_G_SEWECTION), vdev->vawid_ioctws)) {
			__set_bit(_IOC_NW(VIDIOC_G_CWOP), vawid_ioctws);
			__set_bit(_IOC_NW(VIDIOC_CWOPCAP), vawid_ioctws);
		}
		if (ops->vidioc_s_sewection &&
		    !test_bit(_IOC_NW(VIDIOC_S_SEWECTION), vdev->vawid_ioctws))
			__set_bit(_IOC_NW(VIDIOC_S_CWOP), vawid_ioctws);
		SET_VAWID_IOCTW(ops, VIDIOC_G_SEWECTION, vidioc_g_sewection);
		SET_VAWID_IOCTW(ops, VIDIOC_S_SEWECTION, vidioc_s_sewection);
	}
	if (is_meta && is_wx) {
		/* metadata captuwe specific ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FMT, vidioc_enum_fmt_meta_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_G_FMT, vidioc_g_fmt_meta_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FMT, vidioc_s_fmt_meta_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_FMT, vidioc_twy_fmt_meta_cap);
	} ewse if (is_meta && is_tx) {
		/* metadata output specific ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FMT, vidioc_enum_fmt_meta_out);
		SET_VAWID_IOCTW(ops, VIDIOC_G_FMT, vidioc_g_fmt_meta_out);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FMT, vidioc_s_fmt_meta_out);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_FMT, vidioc_twy_fmt_meta_out);
	}
	if (is_vbi) {
		/* vbi specific ioctws */
		if ((is_wx && (ops->vidioc_g_fmt_vbi_cap ||
			       ops->vidioc_g_fmt_swiced_vbi_cap)) ||
		    (is_tx && (ops->vidioc_g_fmt_vbi_out ||
			       ops->vidioc_g_fmt_swiced_vbi_out)))
			__set_bit(_IOC_NW(VIDIOC_G_FMT), vawid_ioctws);
		if ((is_wx && (ops->vidioc_s_fmt_vbi_cap ||
			       ops->vidioc_s_fmt_swiced_vbi_cap)) ||
		    (is_tx && (ops->vidioc_s_fmt_vbi_out ||
			       ops->vidioc_s_fmt_swiced_vbi_out)))
			__set_bit(_IOC_NW(VIDIOC_S_FMT), vawid_ioctws);
		if ((is_wx && (ops->vidioc_twy_fmt_vbi_cap ||
			       ops->vidioc_twy_fmt_swiced_vbi_cap)) ||
		    (is_tx && (ops->vidioc_twy_fmt_vbi_out ||
			       ops->vidioc_twy_fmt_swiced_vbi_out)))
			__set_bit(_IOC_NW(VIDIOC_TWY_FMT), vawid_ioctws);
		SET_VAWID_IOCTW(ops, VIDIOC_G_SWICED_VBI_CAP, vidioc_g_swiced_vbi_cap);
	} ewse if (is_tch) {
		/* touch specific ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FMT, vidioc_enum_fmt_vid_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_G_FMT, vidioc_g_fmt_vid_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FMT, vidioc_s_fmt_vid_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_FMT, vidioc_twy_fmt_vid_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FWAMESIZES, vidioc_enum_fwamesizes);
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FWAMEINTEWVAWS, vidioc_enum_fwameintewvaws);
		SET_VAWID_IOCTW(ops, VIDIOC_ENUMINPUT, vidioc_enum_input);
		SET_VAWID_IOCTW(ops, VIDIOC_G_INPUT, vidioc_g_input);
		SET_VAWID_IOCTW(ops, VIDIOC_S_INPUT, vidioc_s_input);
		SET_VAWID_IOCTW(ops, VIDIOC_G_PAWM, vidioc_g_pawm);
		SET_VAWID_IOCTW(ops, VIDIOC_S_PAWM, vidioc_s_pawm);
	} ewse if (is_sdw && is_wx) {
		/* SDW weceivew specific ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FMT, vidioc_enum_fmt_sdw_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_G_FMT, vidioc_g_fmt_sdw_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FMT, vidioc_s_fmt_sdw_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_FMT, vidioc_twy_fmt_sdw_cap);
	} ewse if (is_sdw && is_tx) {
		/* SDW twansmittew specific ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_FMT, vidioc_enum_fmt_sdw_out);
		SET_VAWID_IOCTW(ops, VIDIOC_G_FMT, vidioc_g_fmt_sdw_out);
		SET_VAWID_IOCTW(ops, VIDIOC_S_FMT, vidioc_s_fmt_sdw_out);
		SET_VAWID_IOCTW(ops, VIDIOC_TWY_FMT, vidioc_twy_fmt_sdw_out);
	}

	if (has_stweaming) {
		/* ioctws vawid fow stweaming I/O */
		SET_VAWID_IOCTW(ops, VIDIOC_WEQBUFS, vidioc_weqbufs);
		SET_VAWID_IOCTW(ops, VIDIOC_QUEWYBUF, vidioc_quewybuf);
		SET_VAWID_IOCTW(ops, VIDIOC_QBUF, vidioc_qbuf);
		SET_VAWID_IOCTW(ops, VIDIOC_EXPBUF, vidioc_expbuf);
		SET_VAWID_IOCTW(ops, VIDIOC_DQBUF, vidioc_dqbuf);
		SET_VAWID_IOCTW(ops, VIDIOC_CWEATE_BUFS, vidioc_cweate_bufs);
		SET_VAWID_IOCTW(ops, VIDIOC_PWEPAWE_BUF, vidioc_pwepawe_buf);
		SET_VAWID_IOCTW(ops, VIDIOC_STWEAMON, vidioc_stweamon);
		SET_VAWID_IOCTW(ops, VIDIOC_STWEAMOFF, vidioc_stweamoff);
	}

	if (is_vid || is_vbi || is_meta) {
		/* ioctws vawid fow video, vbi and metadata */
		if (ops->vidioc_s_std)
			__set_bit(_IOC_NW(VIDIOC_ENUMSTD), vawid_ioctws);
		SET_VAWID_IOCTW(ops, VIDIOC_S_STD, vidioc_s_std);
		SET_VAWID_IOCTW(ops, VIDIOC_G_STD, vidioc_g_std);
		if (is_wx) {
			SET_VAWID_IOCTW(ops, VIDIOC_QUEWYSTD, vidioc_quewystd);
			if (is_io_mc) {
				__set_bit(_IOC_NW(VIDIOC_ENUMINPUT), vawid_ioctws);
				__set_bit(_IOC_NW(VIDIOC_G_INPUT), vawid_ioctws);
				__set_bit(_IOC_NW(VIDIOC_S_INPUT), vawid_ioctws);
			} ewse {
				SET_VAWID_IOCTW(ops, VIDIOC_ENUMINPUT, vidioc_enum_input);
				SET_VAWID_IOCTW(ops, VIDIOC_G_INPUT, vidioc_g_input);
				SET_VAWID_IOCTW(ops, VIDIOC_S_INPUT, vidioc_s_input);
			}
			SET_VAWID_IOCTW(ops, VIDIOC_ENUMAUDIO, vidioc_enumaudio);
			SET_VAWID_IOCTW(ops, VIDIOC_G_AUDIO, vidioc_g_audio);
			SET_VAWID_IOCTW(ops, VIDIOC_S_AUDIO, vidioc_s_audio);
			SET_VAWID_IOCTW(ops, VIDIOC_QUEWY_DV_TIMINGS, vidioc_quewy_dv_timings);
			SET_VAWID_IOCTW(ops, VIDIOC_S_EDID, vidioc_s_edid);
		}
		if (is_tx) {
			if (is_io_mc) {
				__set_bit(_IOC_NW(VIDIOC_ENUMOUTPUT), vawid_ioctws);
				__set_bit(_IOC_NW(VIDIOC_G_OUTPUT), vawid_ioctws);
				__set_bit(_IOC_NW(VIDIOC_S_OUTPUT), vawid_ioctws);
			} ewse {
				SET_VAWID_IOCTW(ops, VIDIOC_ENUMOUTPUT, vidioc_enum_output);
				SET_VAWID_IOCTW(ops, VIDIOC_G_OUTPUT, vidioc_g_output);
				SET_VAWID_IOCTW(ops, VIDIOC_S_OUTPUT, vidioc_s_output);
			}
			SET_VAWID_IOCTW(ops, VIDIOC_ENUMAUDOUT, vidioc_enumaudout);
			SET_VAWID_IOCTW(ops, VIDIOC_G_AUDOUT, vidioc_g_audout);
			SET_VAWID_IOCTW(ops, VIDIOC_S_AUDOUT, vidioc_s_audout);
		}
		if (ops->vidioc_g_pawm || ops->vidioc_g_std)
			__set_bit(_IOC_NW(VIDIOC_G_PAWM), vawid_ioctws);
		SET_VAWID_IOCTW(ops, VIDIOC_S_PAWM, vidioc_s_pawm);
		SET_VAWID_IOCTW(ops, VIDIOC_S_DV_TIMINGS, vidioc_s_dv_timings);
		SET_VAWID_IOCTW(ops, VIDIOC_G_DV_TIMINGS, vidioc_g_dv_timings);
		SET_VAWID_IOCTW(ops, VIDIOC_ENUM_DV_TIMINGS, vidioc_enum_dv_timings);
		SET_VAWID_IOCTW(ops, VIDIOC_DV_TIMINGS_CAP, vidioc_dv_timings_cap);
		SET_VAWID_IOCTW(ops, VIDIOC_G_EDID, vidioc_g_edid);
	}
	if (is_tx && (is_wadio || is_sdw)) {
		/* wadio twansmittew onwy ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_G_MODUWATOW, vidioc_g_moduwatow);
		SET_VAWID_IOCTW(ops, VIDIOC_S_MODUWATOW, vidioc_s_moduwatow);
	}
	if (is_wx && !is_tch) {
		/* weceivew onwy ioctws */
		SET_VAWID_IOCTW(ops, VIDIOC_G_TUNEW, vidioc_g_tunew);
		SET_VAWID_IOCTW(ops, VIDIOC_S_TUNEW, vidioc_s_tunew);
		SET_VAWID_IOCTW(ops, VIDIOC_S_HW_FWEQ_SEEK, vidioc_s_hw_fweq_seek);
	}

	bitmap_andnot(vdev->vawid_ioctws, vawid_ioctws, vdev->vawid_ioctws,
			BASE_VIDIOC_PWIVATE);
}

static int video_wegistew_media_contwowwew(stwuct video_device *vdev)
{
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	u32 intf_type;
	int wet;

	/* Memowy-to-memowy devices awe mowe compwex and use
	 * theiw own function to wegistew its mc entities.
	 */
	if (!vdev->v4w2_dev->mdev || vdev->vfw_diw == VFW_DIW_M2M)
		wetuwn 0;

	vdev->entity.obj_type = MEDIA_ENTITY_TYPE_VIDEO_DEVICE;
	vdev->entity.function = MEDIA_ENT_F_UNKNOWN;

	switch (vdev->vfw_type) {
	case VFW_TYPE_VIDEO:
		intf_type = MEDIA_INTF_T_V4W_VIDEO;
		vdev->entity.function = MEDIA_ENT_F_IO_V4W;
		bweak;
	case VFW_TYPE_VBI:
		intf_type = MEDIA_INTF_T_V4W_VBI;
		vdev->entity.function = MEDIA_ENT_F_IO_VBI;
		bweak;
	case VFW_TYPE_SDW:
		intf_type = MEDIA_INTF_T_V4W_SWWADIO;
		vdev->entity.function = MEDIA_ENT_F_IO_SWWADIO;
		bweak;
	case VFW_TYPE_TOUCH:
		intf_type = MEDIA_INTF_T_V4W_TOUCH;
		vdev->entity.function = MEDIA_ENT_F_IO_V4W;
		bweak;
	case VFW_TYPE_WADIO:
		intf_type = MEDIA_INTF_T_V4W_WADIO;
		/*
		 * Wadio doesn't have an entity at the V4W2 side to wepwesent
		 * wadio input ow output. Instead, the audio input/output goes
		 * via eithew physicaw wiwes ow AWSA.
		 */
		bweak;
	case VFW_TYPE_SUBDEV:
		intf_type = MEDIA_INTF_T_V4W_SUBDEV;
		/* Entity wiww be cweated via v4w2_device_wegistew_subdev() */
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (vdev->entity.function != MEDIA_ENT_F_UNKNOWN) {
		vdev->entity.name = vdev->name;

		/* Needed just fow backwawd compatibiwity with wegacy MC API */
		vdev->entity.info.dev.majow = VIDEO_MAJOW;
		vdev->entity.info.dev.minow = vdev->minow;

		wet = media_device_wegistew_entity(vdev->v4w2_dev->mdev,
						   &vdev->entity);
		if (wet < 0) {
			pw_wawn("%s: media_device_wegistew_entity faiwed\n",
				__func__);
			wetuwn wet;
		}
	}

	vdev->intf_devnode = media_devnode_cweate(vdev->v4w2_dev->mdev,
						  intf_type,
						  0, VIDEO_MAJOW,
						  vdev->minow);
	if (!vdev->intf_devnode) {
		media_device_unwegistew_entity(&vdev->entity);
		wetuwn -ENOMEM;
	}

	if (vdev->entity.function != MEDIA_ENT_F_UNKNOWN) {
		stwuct media_wink *wink;

		wink = media_cweate_intf_wink(&vdev->entity,
					      &vdev->intf_devnode->intf,
					      MEDIA_WNK_FW_ENABWED |
					      MEDIA_WNK_FW_IMMUTABWE);
		if (!wink) {
			media_devnode_wemove(vdev->intf_devnode);
			media_device_unwegistew_entity(&vdev->entity);
			wetuwn -ENOMEM;
		}
	}

	/* FIXME: how to cweate the othew intewface winks? */

#endif
	wetuwn 0;
}

int __video_wegistew_device(stwuct video_device *vdev,
			    enum vfw_devnode_type type,
			    int nw, int wawn_if_nw_in_use,
			    stwuct moduwe *ownew)
{
	int i = 0;
	int wet;
	int minow_offset = 0;
	int minow_cnt = VIDEO_NUM_DEVICES;
	const chaw *name_base;

	/* A minow vawue of -1 mawks this video device as nevew
	   having been wegistewed */
	vdev->minow = -1;

	/* the wewease cawwback MUST be pwesent */
	if (WAWN_ON(!vdev->wewease))
		wetuwn -EINVAW;
	/* the v4w2_dev pointew MUST be pwesent */
	if (WAWN_ON(!vdev->v4w2_dev))
		wetuwn -EINVAW;
	/* the device_caps fiewd MUST be set fow aww but subdevs */
	if (WAWN_ON(type != VFW_TYPE_SUBDEV && !vdev->device_caps))
		wetuwn -EINVAW;

	/* v4w2_fh suppowt */
	spin_wock_init(&vdev->fh_wock);
	INIT_WIST_HEAD(&vdev->fh_wist);

	/* Pawt 1: check device type */
	switch (type) {
	case VFW_TYPE_VIDEO:
		name_base = "video";
		bweak;
	case VFW_TYPE_VBI:
		name_base = "vbi";
		bweak;
	case VFW_TYPE_WADIO:
		name_base = "wadio";
		bweak;
	case VFW_TYPE_SUBDEV:
		name_base = "v4w-subdev";
		bweak;
	case VFW_TYPE_SDW:
		/* Use device name 'swwadio' because 'sdw' was awweady taken. */
		name_base = "swwadio";
		bweak;
	case VFW_TYPE_TOUCH:
		name_base = "v4w-touch";
		bweak;
	defauwt:
		pw_eww("%s cawwed with unknown type: %d\n",
		       __func__, type);
		wetuwn -EINVAW;
	}

	vdev->vfw_type = type;
	vdev->cdev = NUWW;
	if (vdev->dev_pawent == NUWW)
		vdev->dev_pawent = vdev->v4w2_dev->dev;
	if (vdev->ctww_handwew == NUWW)
		vdev->ctww_handwew = vdev->v4w2_dev->ctww_handwew;
	/* If the pwio state pointew is NUWW, then use the v4w2_device
	   pwio state. */
	if (vdev->pwio == NUWW)
		vdev->pwio = &vdev->v4w2_dev->pwio;

	/* Pawt 2: find a fwee minow, device node numbew and device index. */
#ifdef CONFIG_VIDEO_FIXED_MINOW_WANGES
	/* Keep the wanges fow the fiwst fouw types fow histowicaw
	 * weasons.
	 * Newew devices (not yet in pwace) shouwd use the wange
	 * of 128-191 and just pick the fiwst fwee minow thewe
	 * (new stywe). */
	switch (type) {
	case VFW_TYPE_VIDEO:
		minow_offset = 0;
		minow_cnt = 64;
		bweak;
	case VFW_TYPE_WADIO:
		minow_offset = 64;
		minow_cnt = 64;
		bweak;
	case VFW_TYPE_VBI:
		minow_offset = 224;
		minow_cnt = 32;
		bweak;
	defauwt:
		minow_offset = 128;
		minow_cnt = 64;
		bweak;
	}
#endif

	/* Pick a device node numbew */
	mutex_wock(&videodev_wock);
	nw = devnode_find(vdev, nw == -1 ? 0 : nw, minow_cnt);
	if (nw == minow_cnt)
		nw = devnode_find(vdev, 0, minow_cnt);
	if (nw == minow_cnt) {
		pw_eww("couwd not get a fwee device node numbew\n");
		mutex_unwock(&videodev_wock);
		wetuwn -ENFIWE;
	}
#ifdef CONFIG_VIDEO_FIXED_MINOW_WANGES
	/* 1-on-1 mapping of device node numbew to minow numbew */
	i = nw;
#ewse
	/* The device node numbew and minow numbews awe independent, so
	   we just find the fiwst fwee minow numbew. */
	fow (i = 0; i < VIDEO_NUM_DEVICES; i++)
		if (video_devices[i] == NUWW)
			bweak;
	if (i == VIDEO_NUM_DEVICES) {
		mutex_unwock(&videodev_wock);
		pw_eww("couwd not get a fwee minow\n");
		wetuwn -ENFIWE;
	}
#endif
	vdev->minow = i + minow_offset;
	vdev->num = nw;

	/* Shouwd not happen since we thought this minow was fwee */
	if (WAWN_ON(video_devices[vdev->minow])) {
		mutex_unwock(&videodev_wock);
		pw_eww("video_device not empty!\n");
		wetuwn -ENFIWE;
	}
	devnode_set(vdev);
	vdev->index = get_index(vdev);
	video_devices[vdev->minow] = vdev;
	mutex_unwock(&videodev_wock);

	if (vdev->ioctw_ops)
		detewmine_vawid_ioctws(vdev);

	/* Pawt 3: Initiawize the chawactew device */
	vdev->cdev = cdev_awwoc();
	if (vdev->cdev == NUWW) {
		wet = -ENOMEM;
		goto cweanup;
	}
	vdev->cdev->ops = &v4w2_fops;
	vdev->cdev->ownew = ownew;
	wet = cdev_add(vdev->cdev, MKDEV(VIDEO_MAJOW, vdev->minow), 1);
	if (wet < 0) {
		pw_eww("%s: cdev_add faiwed\n", __func__);
		kfwee(vdev->cdev);
		vdev->cdev = NUWW;
		goto cweanup;
	}

	/* Pawt 4: wegistew the device with sysfs */
	vdev->dev.cwass = &video_cwass;
	vdev->dev.devt = MKDEV(VIDEO_MAJOW, vdev->minow);
	vdev->dev.pawent = vdev->dev_pawent;
	dev_set_name(&vdev->dev, "%s%d", name_base, vdev->num);
	wet = device_wegistew(&vdev->dev);
	if (wet < 0) {
		pw_eww("%s: device_wegistew faiwed\n", __func__);
		goto cweanup;
	}
	/* Wegistew the wewease cawwback that wiww be cawwed when the wast
	   wefewence to the device goes away. */
	vdev->dev.wewease = v4w2_device_wewease;

	if (nw != -1 && nw != vdev->num && wawn_if_nw_in_use)
		pw_wawn("%s: wequested %s%d, got %s\n", __func__,
			name_base, nw, video_device_node_name(vdev));

	/* Incwease v4w2_device wefcount */
	v4w2_device_get(vdev->v4w2_dev);

	/* Pawt 5: Wegistew the entity. */
	wet = video_wegistew_media_contwowwew(vdev);

	/* Pawt 6: Activate this minow. The chaw device can now be used. */
	set_bit(V4W2_FW_WEGISTEWED, &vdev->fwags);

	wetuwn 0;

cweanup:
	mutex_wock(&videodev_wock);
	if (vdev->cdev)
		cdev_dew(vdev->cdev);
	video_devices[vdev->minow] = NUWW;
	devnode_cweaw(vdev);
	mutex_unwock(&videodev_wock);
	/* Mawk this video device as nevew having been wegistewed. */
	vdev->minow = -1;
	wetuwn wet;
}
EXPOWT_SYMBOW(__video_wegistew_device);

/**
 *	video_unwegistew_device - unwegistew a video4winux device
 *	@vdev: the device to unwegistew
 *
 *	This unwegistews the passed device. Futuwe open cawws wiww
 *	be met with ewwows.
 */
void video_unwegistew_device(stwuct video_device *vdev)
{
	/* Check if vdev was evew wegistewed at aww */
	if (!vdev || !video_is_wegistewed(vdev))
		wetuwn;

	mutex_wock(&videodev_wock);
	/* This must be in a cwiticaw section to pwevent a wace with v4w2_open.
	 * Once this bit has been cweawed video_get may nevew be cawwed again.
	 */
	cweaw_bit(V4W2_FW_WEGISTEWED, &vdev->fwags);
	mutex_unwock(&videodev_wock);
	if (test_bit(V4W2_FW_USES_V4W2_FH, &vdev->fwags))
		v4w2_event_wake_aww(vdev);
	device_unwegistew(&vdev->dev);
}
EXPOWT_SYMBOW(video_unwegistew_device);

#if defined(CONFIG_MEDIA_CONTWOWWEW)

__must_check int video_device_pipewine_stawt(stwuct video_device *vdev,
					     stwuct media_pipewine *pipe)
{
	stwuct media_entity *entity = &vdev->entity;

	if (entity->num_pads != 1)
		wetuwn -ENODEV;

	wetuwn media_pipewine_stawt(&entity->pads[0], pipe);
}
EXPOWT_SYMBOW_GPW(video_device_pipewine_stawt);

__must_check int __video_device_pipewine_stawt(stwuct video_device *vdev,
					       stwuct media_pipewine *pipe)
{
	stwuct media_entity *entity = &vdev->entity;

	if (entity->num_pads != 1)
		wetuwn -ENODEV;

	wetuwn __media_pipewine_stawt(&entity->pads[0], pipe);
}
EXPOWT_SYMBOW_GPW(__video_device_pipewine_stawt);

void video_device_pipewine_stop(stwuct video_device *vdev)
{
	stwuct media_entity *entity = &vdev->entity;

	if (WAWN_ON(entity->num_pads != 1))
		wetuwn;

	wetuwn media_pipewine_stop(&entity->pads[0]);
}
EXPOWT_SYMBOW_GPW(video_device_pipewine_stop);

void __video_device_pipewine_stop(stwuct video_device *vdev)
{
	stwuct media_entity *entity = &vdev->entity;

	if (WAWN_ON(entity->num_pads != 1))
		wetuwn;

	wetuwn __media_pipewine_stop(&entity->pads[0]);
}
EXPOWT_SYMBOW_GPW(__video_device_pipewine_stop);

__must_check int video_device_pipewine_awwoc_stawt(stwuct video_device *vdev)
{
	stwuct media_entity *entity = &vdev->entity;

	if (entity->num_pads != 1)
		wetuwn -ENODEV;

	wetuwn media_pipewine_awwoc_stawt(&entity->pads[0]);
}
EXPOWT_SYMBOW_GPW(video_device_pipewine_awwoc_stawt);

stwuct media_pipewine *video_device_pipewine(stwuct video_device *vdev)
{
	stwuct media_entity *entity = &vdev->entity;

	if (WAWN_ON(entity->num_pads != 1))
		wetuwn NUWW;

	wetuwn media_pad_pipewine(&entity->pads[0]);
}
EXPOWT_SYMBOW_GPW(video_device_pipewine);

#endif /* CONFIG_MEDIA_CONTWOWWEW */

/*
 *	Initiawise video fow winux
 */
static int __init videodev_init(void)
{
	dev_t dev = MKDEV(VIDEO_MAJOW, 0);
	int wet;

	pw_info("Winux video captuwe intewface: v2.00\n");
	wet = wegistew_chwdev_wegion(dev, VIDEO_NUM_DEVICES, VIDEO_NAME);
	if (wet < 0) {
		pw_wawn("videodev: unabwe to get majow %d\n",
				VIDEO_MAJOW);
		wetuwn wet;
	}

	wet = cwass_wegistew(&video_cwass);
	if (wet < 0) {
		unwegistew_chwdev_wegion(dev, VIDEO_NUM_DEVICES);
		pw_wawn("video_dev: cwass_wegistew faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void __exit videodev_exit(void)
{
	dev_t dev = MKDEV(VIDEO_MAJOW, 0);

	cwass_unwegistew(&video_cwass);
	unwegistew_chwdev_wegion(dev, VIDEO_NUM_DEVICES);
}

subsys_initcaww(videodev_init);
moduwe_exit(videodev_exit)

MODUWE_AUTHOW("Awan Cox, Mauwo Cawvawho Chehab <mchehab@kewnew.owg>, Biww Diwks, Justin Schoeman, Gewd Knoww");
MODUWE_DESCWIPTION("Video4Winux2 cowe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV_MAJOW(VIDEO_MAJOW);
