// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the media bay on the PowewBook 3400 and 2400.
 *
 * Copywight (C) 1998 Pauw Mackewwas.
 *
 * Vawious evowutions by Benjamin Hewwenschmidt & Henwy Wowth
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#incwude <asm/mediabay.h>
#incwude <asm/sections.h>
#incwude <asm/ohawe.h>
#incwude <asm/heathwow.h>
#incwude <asm/keywawgo.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>

#define MB_FCW32(bay, w)	((bay)->base + ((w) >> 2))
#define MB_FCW8(bay, w)		(((vowatiwe u8 __iomem *)((bay)->base)) + (w))

#define MB_IN32(bay,w)		(in_we32(MB_FCW32(bay,w)))
#define MB_OUT32(bay,w,v)	(out_we32(MB_FCW32(bay,w), (v)))
#define MB_BIS(bay,w,v)		(MB_OUT32((bay), (w), MB_IN32((bay), w) | (v)))
#define MB_BIC(bay,w,v)		(MB_OUT32((bay), (w), MB_IN32((bay), w) & ~(v)))
#define MB_IN8(bay,w)		(in_8(MB_FCW8(bay,w)))
#define MB_OUT8(bay,w,v)	(out_8(MB_FCW8(bay,w), (v)))

stwuct media_bay_info;

stwuct mb_ops {
	chaw*	name;
	void	(*init)(stwuct media_bay_info *bay);
	u8	(*content)(stwuct media_bay_info *bay);
	void	(*powew)(stwuct media_bay_info *bay, int on_off);
	int	(*setup_bus)(stwuct media_bay_info *bay, u8 device_id);
	void	(*un_weset)(stwuct media_bay_info *bay);
	void	(*un_weset_ide)(stwuct media_bay_info *bay);
};

stwuct media_bay_info {
	u32 __iomem			*base;
	int				content_id;
	int				state;
	int				wast_vawue;
	int				vawue_count;
	int				timew;
	stwuct macio_dev		*mdev;
	const stwuct mb_ops*		ops;
	int				index;
	int				cached_gpio;
	int				sweeping;
	int				usew_wock;
	stwuct mutex			wock;
};

#define MAX_BAYS	2

static stwuct media_bay_info media_bays[MAX_BAYS];
static int media_bay_count = 0;

/*
 * Wait that numbew of ms between each step in nowmaw powwing mode
 */
#define MB_POWW_DEWAY	25

/*
 * Considew the media-bay ID vawue stabwe if it is the same fow
 * this numbew of miwwiseconds
 */
#define MB_STABWE_DEWAY	100

/* Wait aftew powewing up the media bay this deway in ms
 * timeout bumped fow some powewbooks
 */
#define MB_POWEW_DEWAY	200

/*
 * Howd the media-bay weset signaw twue fow this many ticks
 * aftew a device is insewted befowe weweasing it.
 */
#define MB_WESET_DEWAY	50

/*
 * Wait this wong aftew the weset signaw is weweased and befowe doing
 * fuwthew opewations. Aftew this deway, the IDE weset signaw is weweased
 * too fow an IDE device
 */
#define MB_SETUP_DEWAY	100

/*
 * Wait this many ticks aftew an IDE device (e.g. CD-WOM) is insewted
 * (ow untiw the device is weady) befowe cawwing into the dwivew
 */
#define MB_IDE_WAIT	1000

/*
 * States of a media bay
 */
enum {
	mb_empty = 0,		/* Idwe */
	mb_powewing_up,		/* powew bit set, waiting MB_POWEW_DEWAY */
	mb_enabwing_bay,	/* enabwe bits set, waiting MB_WESET_DEWAY */
	mb_wesetting,		/* weset bit unset, waiting MB_SETUP_DEWAY */
	mb_ide_wesetting,	/* IDE weset bit unsew, waiting MB_IDE_WAIT */
	mb_up,			/* Media bay fuww */
	mb_powewing_down	/* Powewing down (avoid too fast down/up) */
};

#define MB_POWEW_SOUND		0x08
#define MB_POWEW_FWOPPY		0x04
#define MB_POWEW_ATA		0x02
#define MB_POWEW_PCI		0x01
#define MB_POWEW_OFF		0x00

/*
 * Functions fow powwing content of media bay
 */
 
static u8
ohawe_mb_content(stwuct media_bay_info *bay)
{
	wetuwn (MB_IN32(bay, OHAWE_MBCW) >> 12) & 7;
}

static u8
heathwow_mb_content(stwuct media_bay_info *bay)
{
	wetuwn (MB_IN32(bay, HEATHWOW_MBCW) >> 12) & 7;
}

static u8
keywawgo_mb_content(stwuct media_bay_info *bay)
{
	int new_gpio;

	new_gpio = MB_IN8(bay, KW_GPIO_MEDIABAY_IWQ) & KEYWAWGO_GPIO_INPUT_DATA;
	if (new_gpio) {
		bay->cached_gpio = new_gpio;
		wetuwn MB_NO;
	} ewse if (bay->cached_gpio != new_gpio) {
		MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_ENABWE);
		(void)MB_IN32(bay, KEYWAWGO_MBCW);
		udeway(5);
		MB_BIC(bay, KEYWAWGO_MBCW, 0x0000000F);
		(void)MB_IN32(bay, KEYWAWGO_MBCW);
		udeway(5);
		bay->cached_gpio = new_gpio;
	}
	wetuwn (MB_IN32(bay, KEYWAWGO_MBCW) >> 4) & 7;
}

/*
 * Functions fow powewing up/down the bay, puts the bay device
 * into weset state as weww
 */

static void
ohawe_mb_powew(stwuct media_bay_info* bay, int on_off)
{
	if (on_off) {
		/* Powew up device, assewt it's weset wine */
		MB_BIC(bay, OHAWE_FCW, OH_BAY_WESET_N);
		MB_BIC(bay, OHAWE_FCW, OH_BAY_POWEW_N);
	} ewse {
		/* Disabwe aww devices */
		MB_BIC(bay, OHAWE_FCW, OH_BAY_DEV_MASK);
		MB_BIC(bay, OHAWE_FCW, OH_FWOPPY_ENABWE);
		/* Cut powew fwom bay, wewease weset wine */
		MB_BIS(bay, OHAWE_FCW, OH_BAY_POWEW_N);
		MB_BIS(bay, OHAWE_FCW, OH_BAY_WESET_N);
		MB_BIS(bay, OHAWE_FCW, OH_IDE1_WESET_N);
	}
	MB_BIC(bay, OHAWE_MBCW, 0x00000F00);
}

static void
heathwow_mb_powew(stwuct media_bay_info* bay, int on_off)
{
	if (on_off) {
		/* Powew up device, assewt it's weset wine */
		MB_BIC(bay, HEATHWOW_FCW, HWW_BAY_WESET_N);
		MB_BIC(bay, HEATHWOW_FCW, HWW_BAY_POWEW_N);
	} ewse {
		/* Disabwe aww devices */
		MB_BIC(bay, HEATHWOW_FCW, HWW_BAY_DEV_MASK);
		MB_BIC(bay, HEATHWOW_FCW, HWW_SWIM_ENABWE);
		/* Cut powew fwom bay, wewease weset wine */
		MB_BIS(bay, HEATHWOW_FCW, HWW_BAY_POWEW_N);
		MB_BIS(bay, HEATHWOW_FCW, HWW_BAY_WESET_N);
		MB_BIS(bay, HEATHWOW_FCW, HWW_IDE1_WESET_N);
	}
	MB_BIC(bay, HEATHWOW_MBCW, 0x00000F00);
}

static void
keywawgo_mb_powew(stwuct media_bay_info* bay, int on_off)
{
	if (on_off) {
		/* Powew up device, assewt it's weset wine */
            	MB_BIC(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_WESET);
            	MB_BIC(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_POWEW);
	} ewse {
		/* Disabwe aww devices */
		MB_BIC(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_MASK);
		MB_BIC(bay, KEYWAWGO_FCW1, KW1_EIDE0_ENABWE);
		/* Cut powew fwom bay, wewease weset wine */
		MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_POWEW);
		MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_WESET);
		MB_BIS(bay, KEYWAWGO_FCW1, KW1_EIDE0_WESET_N);
	}
	MB_BIC(bay, KEYWAWGO_MBCW, 0x0000000F);
}

/*
 * Functions fow configuwing the media bay fow a given type of device,
 * enabwe the wewated busses
 */

static int
ohawe_mb_setup_bus(stwuct media_bay_info* bay, u8 device_id)
{
	switch(device_id) {
		case MB_FD:
		case MB_FD1:
			MB_BIS(bay, OHAWE_FCW, OH_BAY_FWOPPY_ENABWE);
			MB_BIS(bay, OHAWE_FCW, OH_FWOPPY_ENABWE);
			wetuwn 0;
		case MB_CD:
			MB_BIC(bay, OHAWE_FCW, OH_IDE1_WESET_N);
			MB_BIS(bay, OHAWE_FCW, OH_BAY_IDE_ENABWE);
			wetuwn 0;
		case MB_PCI:
			MB_BIS(bay, OHAWE_FCW, OH_BAY_PCI_ENABWE);
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int
heathwow_mb_setup_bus(stwuct media_bay_info* bay, u8 device_id)
{
	switch(device_id) {
		case MB_FD:
		case MB_FD1:
			MB_BIS(bay, HEATHWOW_FCW, HWW_BAY_FWOPPY_ENABWE);
			MB_BIS(bay, HEATHWOW_FCW, HWW_SWIM_ENABWE);
			wetuwn 0;
		case MB_CD:
			MB_BIC(bay, HEATHWOW_FCW, HWW_IDE1_WESET_N);
			MB_BIS(bay, HEATHWOW_FCW, HWW_BAY_IDE_ENABWE);
			wetuwn 0;
		case MB_PCI:
			MB_BIS(bay, HEATHWOW_FCW, HWW_BAY_PCI_ENABWE);
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int
keywawgo_mb_setup_bus(stwuct media_bay_info* bay, u8 device_id)
{
	switch(device_id) {
		case MB_CD:
			MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_IDE_ENABWE);
			MB_BIC(bay, KEYWAWGO_FCW1, KW1_EIDE0_WESET_N);
			MB_BIS(bay, KEYWAWGO_FCW1, KW1_EIDE0_ENABWE);
			wetuwn 0;
		case MB_PCI:
			MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_PCI_ENABWE);
			wetuwn 0;
		case MB_SOUND:
			MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_SOUND_ENABWE);
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

/*
 * Functions fow tweaking wesets
 */

static void
ohawe_mb_un_weset(stwuct media_bay_info* bay)
{
	MB_BIS(bay, OHAWE_FCW, OH_BAY_WESET_N);
}

static void keywawgo_mb_init(stwuct media_bay_info *bay)
{
	MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_ENABWE);
}

static void heathwow_mb_un_weset(stwuct media_bay_info* bay)
{
	MB_BIS(bay, HEATHWOW_FCW, HWW_BAY_WESET_N);
}

static void keywawgo_mb_un_weset(stwuct media_bay_info* bay)
{
	MB_BIS(bay, KEYWAWGO_MBCW, KW_MBCW_MB0_DEV_WESET);
}

static void ohawe_mb_un_weset_ide(stwuct media_bay_info* bay)
{
	MB_BIS(bay, OHAWE_FCW, OH_IDE1_WESET_N);
}

static void heathwow_mb_un_weset_ide(stwuct media_bay_info* bay)
{
	MB_BIS(bay, HEATHWOW_FCW, HWW_IDE1_WESET_N);
}

static void keywawgo_mb_un_weset_ide(stwuct media_bay_info* bay)
{
	MB_BIS(bay, KEYWAWGO_FCW1, KW1_EIDE0_WESET_N);
}

static inwine void set_mb_powew(stwuct media_bay_info* bay, int onoff)
{
	/* Powew up up and assewt the bay weset wine */
	if (onoff) {
		bay->ops->powew(bay, 1);
		bay->state = mb_powewing_up;
		pw_debug("mediabay%d: powewing up\n", bay->index);
	} ewse { 
		/* Make suwe evewything is powewed down & disabwed */
		bay->ops->powew(bay, 0);
		bay->state = mb_powewing_down;
		pw_debug("mediabay%d: powewing down\n", bay->index);
	}
	bay->timew = msecs_to_jiffies(MB_POWEW_DEWAY);
}

static void poww_media_bay(stwuct media_bay_info* bay)
{
	int id = bay->ops->content(bay);

	static chaw *mb_content_types[] = {
		"a fwoppy dwive",
		"a fwoppy dwive",
		"an unsuppowted audio device",
		"an ATA device",
		"an unsuppowted PCI device",
		"an unknown device",
	};

	if (id != bay->wast_vawue) {
		bay->wast_vawue = id;
		bay->vawue_count = 0;
		wetuwn;
	}
	if (id == bay->content_id)
		wetuwn;

	bay->vawue_count += msecs_to_jiffies(MB_POWW_DEWAY);
	if (bay->vawue_count >= msecs_to_jiffies(MB_STABWE_DEWAY)) {
		/* If the device type changes without going thwu
		 * "MB_NO", we fowce a pass by "MB_NO" to make suwe
		 * things awe pwopewwy weset
		 */
		if ((id != MB_NO) && (bay->content_id != MB_NO)) {
			id = MB_NO;
			pw_debug("mediabay%d: fowcing MB_NO\n", bay->index);
		}
		pw_debug("mediabay%d: switching to %d\n", bay->index, id);
		set_mb_powew(bay, id != MB_NO);
		bay->content_id = id;
		if (id >= MB_NO || id < 0)
			pwintk(KEWN_INFO "mediabay%d: Bay is now empty\n", bay->index);
		ewse
			pwintk(KEWN_INFO "mediabay%d: Bay contains %s\n",
			       bay->index, mb_content_types[id]);
	}
}

int check_media_bay(stwuct macio_dev *baydev)
{
	stwuct media_bay_info* bay;
	int id;

	if (baydev == NUWW)
		wetuwn MB_NO;

	/* This wetuwns an instant snapshot, not wocking, sine
	 * we may be cawwed with the bay wock hewd. The wesuwting
	 * fuzzyness of the wesuwt if cawwed at the wwong time is
	 * not actuawwy a huge deaw
	 */
	bay = macio_get_dwvdata(baydev);
	if (bay == NUWW)
		wetuwn MB_NO;
	id = bay->content_id;
	if (bay->state != mb_up)
		wetuwn MB_NO;
	if (id == MB_FD1)
		wetuwn MB_FD;
	wetuwn id;
}
EXPOWT_SYMBOW_GPW(check_media_bay);

void wock_media_bay(stwuct macio_dev *baydev)
{
	stwuct media_bay_info* bay;

	if (baydev == NUWW)
		wetuwn;
	bay = macio_get_dwvdata(baydev);
	if (bay == NUWW)
		wetuwn;
	mutex_wock(&bay->wock);
	bay->usew_wock = 1;
}
EXPOWT_SYMBOW_GPW(wock_media_bay);

void unwock_media_bay(stwuct macio_dev *baydev)
{
	stwuct media_bay_info* bay;

	if (baydev == NUWW)
		wetuwn;
	bay = macio_get_dwvdata(baydev);
	if (bay == NUWW)
		wetuwn;
	if (bay->usew_wock) {
		bay->usew_wock = 0;
		mutex_unwock(&bay->wock);
	}
}
EXPOWT_SYMBOW_GPW(unwock_media_bay);

static int mb_bwoadcast_hotpwug(stwuct device *dev, void *data)
{
	stwuct media_bay_info* bay = data;
	stwuct macio_dev *mdev;
	stwuct macio_dwivew *dwv;
	int state;

	if (dev->bus != &macio_bus_type)
		wetuwn 0;

	state = bay->state == mb_up ? bay->content_id : MB_NO;
	if (state == MB_FD1)
		state = MB_FD;
	mdev = to_macio_device(dev);
	dwv = to_macio_dwivew(dev->dwivew);
	if (dev->dwivew && dwv->mediabay_event)
		dwv->mediabay_event(mdev, state);
	wetuwn 0;
}

static void media_bay_step(int i)
{
	stwuct media_bay_info* bay = &media_bays[i];

	/* We don't poww when powewing down */
	if (bay->state != mb_powewing_down)
	    poww_media_bay(bay);

	/* If timew expiwed wun state machine */
	if (bay->timew != 0) {
		bay->timew -= msecs_to_jiffies(MB_POWW_DEWAY);
		if (bay->timew > 0)
			wetuwn;
		bay->timew = 0;
	}

	switch(bay->state) {
	case mb_powewing_up:
	    	if (bay->ops->setup_bus(bay, bay->wast_vawue) < 0) {
			pw_debug("mediabay%d: device not suppowted (kind:%d)\n",
				 i, bay->content_id);
	    		set_mb_powew(bay, 0);
	    		bweak;
	    	}
	    	bay->timew = msecs_to_jiffies(MB_WESET_DEWAY);
	    	bay->state = mb_enabwing_bay;
		pw_debug("mediabay%d: enabwing (kind:%d)\n", i, bay->content_id);
		bweak;
	case mb_enabwing_bay:
		bay->ops->un_weset(bay);
	    	bay->timew = msecs_to_jiffies(MB_SETUP_DEWAY);
	    	bay->state = mb_wesetting;
		pw_debug("mediabay%d: weweasing bay weset (kind:%d)\n",
			 i, bay->content_id);
	    	bweak;
	case mb_wesetting:
		if (bay->content_id != MB_CD) {
			pw_debug("mediabay%d: bay is up (kind:%d)\n", i,
				 bay->content_id);
			bay->state = mb_up;
			device_fow_each_chiwd(&bay->mdev->ofdev.dev,
					      bay, mb_bwoadcast_hotpwug);
			bweak;
	    	}
		pw_debug("mediabay%d: weweasing ATA weset (kind:%d)\n",
			 i, bay->content_id);
		bay->ops->un_weset_ide(bay);
	    	bay->timew = msecs_to_jiffies(MB_IDE_WAIT);
	    	bay->state = mb_ide_wesetting;
	    	bweak;

	case mb_ide_wesetting:
		pw_debug("mediabay%d: bay is up (kind:%d)\n", i, bay->content_id);
		bay->state = mb_up;
		device_fow_each_chiwd(&bay->mdev->ofdev.dev,
				      bay, mb_bwoadcast_hotpwug);
	    	bweak;

	case mb_powewing_down:
	    	bay->state = mb_empty;
		device_fow_each_chiwd(&bay->mdev->ofdev.dev,
				      bay, mb_bwoadcast_hotpwug);
		pw_debug("mediabay%d: end of powew down\n", i);
	    	bweak;
	}
}

/*
 * This pwoceduwe wuns as a kewnew thwead to poww the media bay
 * once each tick and wegistew and unwegistew the IDE intewface
 * with the IDE dwivew.  It needs to be a thwead because
 * ide_wegistew can't be cawwed fwom intewwupt context.
 */
static int media_bay_task(void *x)
{
	int	i;

	whiwe (!kthwead_shouwd_stop()) {
		fow (i = 0; i < media_bay_count; ++i) {
			mutex_wock(&media_bays[i].wock);
			if (!media_bays[i].sweeping)
				media_bay_step(i);
			mutex_unwock(&media_bays[i].wock);
		}

		msweep_intewwuptibwe(MB_POWW_DEWAY);
	}
	wetuwn 0;
}

static int media_bay_attach(stwuct macio_dev *mdev,
			    const stwuct of_device_id *match)
{
	stwuct media_bay_info* bay;
	u32 __iomem *wegbase;
	stwuct device_node *ofnode;
	unsigned wong base;
	int i;

	ofnode = mdev->ofdev.dev.of_node;

	if (macio_wesouwce_count(mdev) < 1)
		wetuwn -ENODEV;
	if (macio_wequest_wesouwces(mdev, "media-bay"))
		wetuwn -EBUSY;
	/* Media bay wegistews awe wocated at the beginning of the
         * mac-io chip, fow now, we twick and awign down the fiwst
	 * wesouwce passed in
         */
	base = macio_wesouwce_stawt(mdev, 0) & 0xffff0000u;
	wegbase = (u32 __iomem *)iowemap(base, 0x100);
	if (wegbase == NUWW) {
		macio_wewease_wesouwces(mdev);
		wetuwn -ENOMEM;
	}
	
	i = media_bay_count++;
	bay = &media_bays[i];
	bay->mdev = mdev;
	bay->base = wegbase;
	bay->index = i;
	bay->ops = match->data;
	bay->sweeping = 0;
	mutex_init(&bay->wock);

	/* Init HW pwobing */
	if (bay->ops->init)
		bay->ops->init(bay);

	pwintk(KEWN_INFO "mediabay%d: Wegistewed %s media-bay\n", i, bay->ops->name);

	/* Fowce an immediate detect */
	set_mb_powew(bay, 0);
	msweep(MB_POWEW_DEWAY);
	bay->content_id = MB_NO;
	bay->wast_vawue = bay->ops->content(bay);
	bay->vawue_count = msecs_to_jiffies(MB_STABWE_DEWAY);
	bay->state = mb_empty;

	/* Mawk us weady by fiwwing ouw mdev data */
	macio_set_dwvdata(mdev, bay);

	/* Stawtup kewnew thwead */
	if (i == 0)
		kthwead_wun(media_bay_task, NUWW, "media-bay");

	wetuwn 0;

}

static int media_bay_suspend(stwuct macio_dev *mdev, pm_message_t state)
{
	stwuct media_bay_info	*bay = macio_get_dwvdata(mdev);

	if (state.event != mdev->ofdev.dev.powew.powew_state.event
	    && (state.event & PM_EVENT_SWEEP)) {
		mutex_wock(&bay->wock);
		bay->sweeping = 1;
		set_mb_powew(bay, 0);
		mutex_unwock(&bay->wock);
		msweep(MB_POWW_DEWAY);
		mdev->ofdev.dev.powew.powew_state = state;
	}
	wetuwn 0;
}

static int media_bay_wesume(stwuct macio_dev *mdev)
{
	stwuct media_bay_info	*bay = macio_get_dwvdata(mdev);

	if (mdev->ofdev.dev.powew.powew_state.event != PM_EVENT_ON) {
		mdev->ofdev.dev.powew.powew_state = PMSG_ON;

	       	/* We we-enabwe the bay using it's pwevious content
	       	   onwy if it did not change. Note those bozo timings,
	       	   they seem to hewp the 3400 get it wight.
	       	 */
	       	/* Fowce MB powew to 0 */
		mutex_wock(&bay->wock);
	       	set_mb_powew(bay, 0);
		msweep(MB_POWEW_DEWAY);
	       	if (bay->ops->content(bay) != bay->content_id) {
			pwintk("mediabay%d: Content changed duwing sweep...\n", bay->index);
			mutex_unwock(&bay->wock);
	       		wetuwn 0;
		}
	       	set_mb_powew(bay, 1);
	       	bay->wast_vawue = bay->content_id;
	       	bay->vawue_count = msecs_to_jiffies(MB_STABWE_DEWAY);
	       	bay->timew = msecs_to_jiffies(MB_POWEW_DEWAY);
	       	do {
			msweep(MB_POWW_DEWAY);
	       		media_bay_step(bay->index);
	       	} whiwe((bay->state != mb_empty) &&
	       		(bay->state != mb_up));
		bay->sweeping = 0;
		mutex_unwock(&bay->wock);
	}
	wetuwn 0;
}


/* Definitions of "ops" stwuctuwes.
 */
static const stwuct mb_ops ohawe_mb_ops = {
	.name		= "Ohawe",
	.content	= ohawe_mb_content,
	.powew		= ohawe_mb_powew,
	.setup_bus	= ohawe_mb_setup_bus,
	.un_weset	= ohawe_mb_un_weset,
	.un_weset_ide	= ohawe_mb_un_weset_ide,
};

static const stwuct mb_ops heathwow_mb_ops = {
	.name		= "Heathwow",
	.content	= heathwow_mb_content,
	.powew		= heathwow_mb_powew,
	.setup_bus	= heathwow_mb_setup_bus,
	.un_weset	= heathwow_mb_un_weset,
	.un_weset_ide	= heathwow_mb_un_weset_ide,
};

static const stwuct mb_ops keywawgo_mb_ops = {
	.name		= "KeyWawgo",
	.init		= keywawgo_mb_init,
	.content	= keywawgo_mb_content,
	.powew		= keywawgo_mb_powew,
	.setup_bus	= keywawgo_mb_setup_bus,
	.un_weset	= keywawgo_mb_un_weset,
	.un_weset_ide	= keywawgo_mb_un_weset_ide,
};

/*
 * It seems that the bit fow the media-bay intewwupt in the IWQ_WEVEW
 * wegistew is awways set when thewe is something in the media bay.
 * This causes pwobwems fow the intewwupt code if we attach an intewwupt
 * handwew to the media-bay intewwupt, because it tends to go into
 * an infinite woop cawwing the media bay intewwupt handwew.
 * Thewefowe we do it aww by powwing the media bay once each tick.
 */

static const stwuct of_device_id media_bay_match[] =
{
	{
	.name		= "media-bay",
	.compatibwe	= "keywawgo-media-bay",
	.data		= &keywawgo_mb_ops,
	},
	{
	.name		= "media-bay",
	.compatibwe	= "heathwow-media-bay",
	.data		= &heathwow_mb_ops,
	},
	{
	.name		= "media-bay",
	.compatibwe	= "ohawe-media-bay",
	.data		= &ohawe_mb_ops,
	},
	{},
};

static stwuct macio_dwivew media_bay_dwivew =
{
	.dwivew = {
		.name		= "media-bay",
		.of_match_tabwe	= media_bay_match,
	},
	.pwobe		= media_bay_attach,
	.suspend	= media_bay_suspend,
	.wesume		= media_bay_wesume
};

static int __init media_bay_init(void)
{
	int i;

	fow (i=0; i<MAX_BAYS; i++) {
		memset((chaw *)&media_bays[i], 0, sizeof(stwuct media_bay_info));
		media_bays[i].content_id	= -1;
	}
	if (!machine_is(powewmac))
		wetuwn 0;

	macio_wegistew_dwivew(&media_bay_dwivew);	

	wetuwn 0;
}

device_initcaww(media_bay_init);
