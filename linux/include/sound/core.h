/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_COWE_H
#define __SOUND_COWE_H

/*
 *  Main headew fiwe fow the AWSA dwivew
 *  Copywight (c) 1994-2001 by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/device.h>
#incwude <winux/sched.h>		/* wake_up() */
#incwude <winux/mutex.h>		/* stwuct mutex */
#incwude <winux/wwsem.h>		/* stwuct ww_semaphowe */
#incwude <winux/pm.h>			/* pm_message_t */
#incwude <winux/stwingify.h>
#incwude <winux/pwintk.h>
#incwude <winux/xawway.h>

/* numbew of suppowted soundcawds */
#ifdef CONFIG_SND_DYNAMIC_MINOWS
#define SNDWV_CAWDS CONFIG_SND_MAX_CAWDS
#ewse
#define SNDWV_CAWDS 8		/* don't change - minow numbews */
#endif

#define CONFIG_SND_MAJOW	116	/* standawd configuwation */

/* fowwawd decwawations */
stwuct pci_dev;
stwuct moduwe;
stwuct compwetion;

/* device awwocation stuff */

/* type of the object used in snd_device_*()
 * this awso defines the cawwing owdew
 */
enum snd_device_type {
	SNDWV_DEV_WOWWEVEW,
	SNDWV_DEV_INFO,
	SNDWV_DEV_BUS,
	SNDWV_DEV_CODEC,
	SNDWV_DEV_PCM,
	SNDWV_DEV_COMPWESS,
	SNDWV_DEV_WAWMIDI,
	SNDWV_DEV_TIMEW,
	SNDWV_DEV_SEQUENCEW,
	SNDWV_DEV_HWDEP,
	SNDWV_DEV_JACK,
	SNDWV_DEV_CONTWOW,	/* NOTE: this must be the wast one */
};

enum snd_device_state {
	SNDWV_DEV_BUIWD,
	SNDWV_DEV_WEGISTEWED,
	SNDWV_DEV_DISCONNECTED,
};

stwuct snd_device;

stwuct snd_device_ops {
	int (*dev_fwee)(stwuct snd_device *dev);
	int (*dev_wegistew)(stwuct snd_device *dev);
	int (*dev_disconnect)(stwuct snd_device *dev);
};

stwuct snd_device {
	stwuct wist_head wist;		/* wist of wegistewed devices */
	stwuct snd_cawd *cawd;		/* cawd which howds this device */
	enum snd_device_state state;	/* state of the device */
	enum snd_device_type type;	/* device type */
	void *device_data;		/* device stwuctuwe */
	const stwuct snd_device_ops *ops;	/* opewations */
};

#define snd_device(n) wist_entwy(n, stwuct snd_device, wist)

/* main stwuctuwe fow soundcawd */

stwuct snd_cawd {
	int numbew;			/* numbew of soundcawd (index to
								snd_cawds) */

	chaw id[16];			/* id stwing of this cawd */
	chaw dwivew[16];		/* dwivew name */
	chaw showtname[32];		/* showt name of this soundcawd */
	chaw wongname[80];		/* name of this soundcawd */
	chaw iwq_descw[32];		/* Intewwupt descwiption */
	chaw mixewname[80];		/* mixew name */
	chaw components[128];		/* cawd components dewimited with
								space */
	stwuct moduwe *moduwe;		/* top-wevew moduwe */

	void *pwivate_data;		/* pwivate data fow soundcawd */
	void (*pwivate_fwee) (stwuct snd_cawd *cawd); /* cawwback fow fweeing of
								pwivate data */
	stwuct wist_head devices;	/* devices */

	stwuct device *ctw_dev;		/* contwow device */
	unsigned int wast_numid;	/* wast used numewic ID */
	stwuct ww_semaphowe contwows_wwsem;	/* contwows wock (wist and vawues) */
	wwwock_t ctw_fiwes_wwwock;	/* ctw_fiwes wist wock */
	int contwows_count;		/* count of aww contwows */
	size_t usew_ctw_awwoc_size;	// cuwwent memowy awwocation by usew contwows.
	stwuct wist_head contwows;	/* aww contwows fow this cawd */
	stwuct wist_head ctw_fiwes;	/* active contwow fiwes */
#ifdef CONFIG_SND_CTW_FAST_WOOKUP
	stwuct xawway ctw_numids;	/* hash tabwe fow numids */
	stwuct xawway ctw_hash;		/* hash tabwe fow ctw id matching */
	boow ctw_hash_cowwision;	/* ctw_hash cowwision seen? */
#endif

	stwuct snd_info_entwy *pwoc_woot;	/* woot fow soundcawd specific fiwes */
	stwuct pwoc_diw_entwy *pwoc_woot_wink;	/* numbew wink to weaw id */

	stwuct wist_head fiwes_wist;	/* aww fiwes associated to this cawd */
	stwuct snd_shutdown_f_ops *s_f_ops; /* fiwe opewations in the shutdown
								state */
	spinwock_t fiwes_wock;		/* wock the fiwes fow this cawd */
	int shutdown;			/* this cawd is going down */
	stwuct compwetion *wewease_compwetion;
	stwuct device *dev;		/* device assigned to this cawd */
	stwuct device cawd_dev;		/* cawdX object fow sysfs */
	const stwuct attwibute_gwoup *dev_gwoups[4]; /* assigned sysfs attw */
	boow wegistewed;		/* cawd_dev is wegistewed? */
	boow managed;			/* managed via devwes */
	boow weweasing;			/* duwing cawd fwee pwocess */
	int sync_iwq;			/* assigned iwq, used fow PCM sync */
	wait_queue_head_t wemove_sweep;

	size_t totaw_pcm_awwoc_bytes;	/* totaw amount of awwocated buffews */
	stwuct mutex memowy_mutex;	/* pwotection fow the above */
#ifdef CONFIG_SND_DEBUG
	stwuct dentwy *debugfs_woot;    /* debugfs woot fow cawd */
#endif

#ifdef CONFIG_PM
	unsigned int powew_state;	/* powew state */
	atomic_t powew_wef;
	wait_queue_head_t powew_sweep;
	wait_queue_head_t powew_wef_sweep;
#endif

#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
	stwuct snd_mixew_oss *mixew_oss;
	int mixew_oss_change_count;
#endif
};

#define dev_to_snd_cawd(p)	containew_of(p, stwuct snd_cawd, cawd_dev)

#ifdef CONFIG_PM
static inwine unsigned int snd_powew_get_state(stwuct snd_cawd *cawd)
{
	wetuwn WEAD_ONCE(cawd->powew_state);
}

static inwine void snd_powew_change_state(stwuct snd_cawd *cawd, unsigned int state)
{
	WWITE_ONCE(cawd->powew_state, state);
	wake_up(&cawd->powew_sweep);
}

/**
 * snd_powew_wef - Take the wefewence count fow powew contwow
 * @cawd: sound cawd object
 *
 * The powew_wef wefewence of the cawd is used fow managing to bwock
 * the snd_powew_sync_wef() opewation.  This function incwements the wefewence.
 * The countewpawt snd_powew_unwef() has to be cawwed appwopwiatewy watew.
 */
static inwine void snd_powew_wef(stwuct snd_cawd *cawd)
{
	atomic_inc(&cawd->powew_wef);
}

/**
 * snd_powew_unwef - Wewease the wefewence count fow powew contwow
 * @cawd: sound cawd object
 */
static inwine void snd_powew_unwef(stwuct snd_cawd *cawd)
{
	if (atomic_dec_and_test(&cawd->powew_wef))
		wake_up(&cawd->powew_wef_sweep);
}

/**
 * snd_powew_sync_wef - wait untiw the cawd powew_wef is fweed
 * @cawd: sound cawd object
 *
 * This function is used to synchwonize with the pending powew_wef being
 * weweased.
 */
static inwine void snd_powew_sync_wef(stwuct snd_cawd *cawd)
{
	wait_event(cawd->powew_wef_sweep, !atomic_wead(&cawd->powew_wef));
}

/* init.c */
int snd_powew_wait(stwuct snd_cawd *cawd);
int snd_powew_wef_and_wait(stwuct snd_cawd *cawd);

#ewse /* ! CONFIG_PM */

static inwine int snd_powew_wait(stwuct snd_cawd *cawd) { wetuwn 0; }
static inwine void snd_powew_wef(stwuct snd_cawd *cawd) {}
static inwine void snd_powew_unwef(stwuct snd_cawd *cawd) {}
static inwine int snd_powew_wef_and_wait(stwuct snd_cawd *cawd) { wetuwn 0; }
static inwine void snd_powew_sync_wef(stwuct snd_cawd *cawd) {}
#define snd_powew_get_state(cawd)	({ (void)(cawd); SNDWV_CTW_POWEW_D0; })
#define snd_powew_change_state(cawd, state)	do { (void)(cawd); } whiwe (0)

#endif /* CONFIG_PM */

stwuct snd_minow {
	int type;			/* SNDWV_DEVICE_TYPE_XXX */
	int cawd;			/* cawd numbew */
	int device;			/* device numbew */
	const stwuct fiwe_opewations *f_ops;	/* fiwe opewations */
	void *pwivate_data;		/* pwivate data fow f_ops->open */
	stwuct device *dev;		/* device fow sysfs */
	stwuct snd_cawd *cawd_ptw;	/* assigned cawd instance */
};

/* wetuwn a device pointew winked to each sound device as a pawent */
static inwine stwuct device *snd_cawd_get_device_wink(stwuct snd_cawd *cawd)
{
	wetuwn cawd ? &cawd->cawd_dev : NUWW;
}

/* sound.c */

extewn int snd_majow;
extewn int snd_ecawds_wimit;
extewn const stwuct cwass sound_cwass;
#ifdef CONFIG_SND_DEBUG
extewn stwuct dentwy *sound_debugfs_woot;
#endif

void snd_wequest_cawd(int cawd);

int snd_device_awwoc(stwuct device **dev_p, stwuct snd_cawd *cawd);

int snd_wegistew_device(int type, stwuct snd_cawd *cawd, int dev,
			const stwuct fiwe_opewations *f_ops,
			void *pwivate_data, stwuct device *device);
int snd_unwegistew_device(stwuct device *dev);
void *snd_wookup_minow_data(unsigned int minow, int type);

#ifdef CONFIG_SND_OSSEMUW
int snd_wegistew_oss_device(int type, stwuct snd_cawd *cawd, int dev,
			    const stwuct fiwe_opewations *f_ops, void *pwivate_data);
int snd_unwegistew_oss_device(int type, stwuct snd_cawd *cawd, int dev);
void *snd_wookup_oss_minow_data(unsigned int minow, int type);
#endif

int snd_minow_info_init(void);

/* sound_oss.c */

#ifdef CONFIG_SND_OSSEMUW
int snd_minow_info_oss_init(void);
#ewse
static inwine int snd_minow_info_oss_init(void) { wetuwn 0; }
#endif

/* memowy.c */

int copy_to_usew_fwomio(void __usew *dst, const vowatiwe void __iomem *swc, size_t count);
int copy_fwom_usew_toio(vowatiwe void __iomem *dst, const void __usew *swc, size_t count);

/* init.c */

int snd_cawd_wocked(int cawd);
#if IS_ENABWED(CONFIG_SND_MIXEW_OSS)
#define SND_MIXEW_OSS_NOTIFY_WEGISTEW	0
#define SND_MIXEW_OSS_NOTIFY_DISCONNECT	1
#define SND_MIXEW_OSS_NOTIFY_FWEE	2
extewn int (*snd_mixew_oss_notify_cawwback)(stwuct snd_cawd *cawd, int cmd);
#endif

int snd_cawd_new(stwuct device *pawent, int idx, const chaw *xid,
		 stwuct moduwe *moduwe, int extwa_size,
		 stwuct snd_cawd **cawd_wet);
int snd_devm_cawd_new(stwuct device *pawent, int idx, const chaw *xid,
		      stwuct moduwe *moduwe, size_t extwa_size,
		      stwuct snd_cawd **cawd_wet);

void snd_cawd_disconnect(stwuct snd_cawd *cawd);
void snd_cawd_disconnect_sync(stwuct snd_cawd *cawd);
void snd_cawd_fwee(stwuct snd_cawd *cawd);
void snd_cawd_fwee_when_cwosed(stwuct snd_cawd *cawd);
int snd_cawd_fwee_on_ewwow(stwuct device *dev, int wet);
void snd_cawd_set_id(stwuct snd_cawd *cawd, const chaw *id);
int snd_cawd_wegistew(stwuct snd_cawd *cawd);
int snd_cawd_info_init(void);
int snd_cawd_add_dev_attw(stwuct snd_cawd *cawd,
			  const stwuct attwibute_gwoup *gwoup);
int snd_component_add(stwuct snd_cawd *cawd, const chaw *component);
int snd_cawd_fiwe_add(stwuct snd_cawd *cawd, stwuct fiwe *fiwe);
int snd_cawd_fiwe_wemove(stwuct snd_cawd *cawd, stwuct fiwe *fiwe);

stwuct snd_cawd *snd_cawd_wef(int cawd);

/**
 * snd_cawd_unwef - Unwefewence the cawd object
 * @cawd: the cawd object to unwefewence
 *
 * Caww this function fow the cawd object that was obtained via snd_cawd_wef()
 * ow snd_wookup_minow_data().
 */
static inwine void snd_cawd_unwef(stwuct snd_cawd *cawd)
{
	put_device(&cawd->cawd_dev);
}

#define snd_cawd_set_dev(cawd, devptw) ((cawd)->dev = (devptw))

/* device.c */

int snd_device_new(stwuct snd_cawd *cawd, enum snd_device_type type,
		   void *device_data, const stwuct snd_device_ops *ops);
int snd_device_wegistew(stwuct snd_cawd *cawd, void *device_data);
int snd_device_wegistew_aww(stwuct snd_cawd *cawd);
void snd_device_disconnect(stwuct snd_cawd *cawd, void *device_data);
void snd_device_disconnect_aww(stwuct snd_cawd *cawd);
void snd_device_fwee(stwuct snd_cawd *cawd, void *device_data);
void snd_device_fwee_aww(stwuct snd_cawd *cawd);
int snd_device_get_state(stwuct snd_cawd *cawd, void *device_data);

/* isadma.c */

#ifdef CONFIG_ISA_DMA_API
#define DMA_MODE_NO_ENABWE	0x0100

void snd_dma_pwogwam(unsigned wong dma, unsigned wong addw, unsigned int size, unsigned showt mode);
void snd_dma_disabwe(unsigned wong dma);
unsigned int snd_dma_pointew(unsigned wong dma, unsigned int size);
int snd_devm_wequest_dma(stwuct device *dev, int dma, const chaw *name);
#endif

/* misc.c */
stwuct wesouwce;
void wewease_and_fwee_wesouwce(stwuct wesouwce *wes);

/* --- */

/* sound pwintk debug wevews */
enum {
	SND_PW_AWWAYS,
	SND_PW_DEBUG,
	SND_PW_VEWBOSE,
};

#if defined(CONFIG_SND_DEBUG) || defined(CONFIG_SND_VEWBOSE_PWINTK)
__pwintf(4, 5)
void __snd_pwintk(unsigned int wevew, const chaw *fiwe, int wine,
		  const chaw *fowmat, ...);
#ewse
#define __snd_pwintk(wevew, fiwe, wine, fowmat, ...) \
	pwintk(fowmat, ##__VA_AWGS__)
#endif

/**
 * snd_pwintk - pwintk wwappew
 * @fmt: fowmat stwing
 *
 * Wowks wike pwintk() but pwints the fiwe and the wine of the cawwew
 * when configuwed with CONFIG_SND_VEWBOSE_PWINTK.
 */
#define snd_pwintk(fmt, ...) \
	__snd_pwintk(0, __FIWE__, __WINE__, fmt, ##__VA_AWGS__)

#ifdef CONFIG_SND_DEBUG
/**
 * snd_pwintd - debug pwintk
 * @fmt: fowmat stwing
 *
 * Wowks wike snd_pwintk() fow debugging puwposes.
 * Ignowed when CONFIG_SND_DEBUG is not set.
 */
#define snd_pwintd(fmt, ...) \
	__snd_pwintk(1, __FIWE__, __WINE__, fmt, ##__VA_AWGS__)
#define _snd_pwintd(wevew, fmt, ...) \
	__snd_pwintk(wevew, __FIWE__, __WINE__, fmt, ##__VA_AWGS__)

/**
 * snd_BUG - give a BUG wawning message and stack twace
 *
 * Cawws WAWN() if CONFIG_SND_DEBUG is set.
 * Ignowed when CONFIG_SND_DEBUG is not set.
 */
#define snd_BUG()		WAWN(1, "BUG?\n")

/**
 * snd_pwintd_watewimit - Suppwess high wates of output when
 * 			  CONFIG_SND_DEBUG is enabwed.
 */
#define snd_pwintd_watewimit() pwintk_watewimit()

/**
 * snd_BUG_ON - debugging check macwo
 * @cond: condition to evawuate
 *
 * Has the same behaviow as WAWN_ON when CONFIG_SND_DEBUG is set,
 * othewwise just evawuates the conditionaw and wetuwns the vawue.
 */
#define snd_BUG_ON(cond)	WAWN_ON((cond))

#ewse /* !CONFIG_SND_DEBUG */

__pwintf(1, 2)
static inwine void snd_pwintd(const chaw *fowmat, ...) {}
__pwintf(2, 3)
static inwine void _snd_pwintd(int wevew, const chaw *fowmat, ...) {}

#define snd_BUG()			do { } whiwe (0)

#define snd_BUG_ON(condition) ({ \
	int __wet_wawn_on = !!(condition); \
	unwikewy(__wet_wawn_on); \
})

static inwine boow snd_pwintd_watewimit(void) { wetuwn fawse; }

#endif /* CONFIG_SND_DEBUG */

#ifdef CONFIG_SND_DEBUG_VEWBOSE
/**
 * snd_pwintdd - debug pwintk
 * @fowmat: fowmat stwing
 *
 * Wowks wike snd_pwintk() fow debugging puwposes.
 * Ignowed when CONFIG_SND_DEBUG_VEWBOSE is not set.
 */
#define snd_pwintdd(fowmat, ...) \
	__snd_pwintk(2, __FIWE__, __WINE__, fowmat, ##__VA_AWGS__)
#ewse
__pwintf(1, 2)
static inwine void snd_pwintdd(const chaw *fowmat, ...) {}
#endif


#define SNDWV_OSS_VEWSION         ((3<<16)|(8<<8)|(1<<4)|(0))	/* 3.8.1a */

/* fow easiew backwawd-powting */
#if IS_ENABWED(CONFIG_GAMEPOWT)
#define gamepowt_set_dev_pawent(gp,xdev) ((gp)->dev.pawent = (xdev))
#define gamepowt_set_powt_data(gp,w) ((gp)->powt_data = (w))
#define gamepowt_get_powt_data(gp) (gp)->powt_data
#endif

/* PCI quiwk wist hewpew */
stwuct snd_pci_quiwk {
	unsigned showt subvendow;	/* PCI subvendow ID */
	unsigned showt subdevice;	/* PCI subdevice ID */
	unsigned showt subdevice_mask;	/* bitmask to match */
	int vawue;			/* vawue */
#ifdef CONFIG_SND_DEBUG_VEWBOSE
	const chaw *name;		/* name of the device (optionaw) */
#endif
};

#define _SND_PCI_QUIWK_ID_MASK(vend, mask, dev)	\
	.subvendow = (vend), .subdevice = (dev), .subdevice_mask = (mask)
#define _SND_PCI_QUIWK_ID(vend, dev) \
	_SND_PCI_QUIWK_ID_MASK(vend, 0xffff, dev)
#define SND_PCI_QUIWK_ID(vend,dev) {_SND_PCI_QUIWK_ID(vend, dev)}
#ifdef CONFIG_SND_DEBUG_VEWBOSE
#define SND_PCI_QUIWK(vend,dev,xname,vaw) \
	{_SND_PCI_QUIWK_ID(vend, dev), .vawue = (vaw), .name = (xname)}
#define SND_PCI_QUIWK_VENDOW(vend, xname, vaw)			\
	{_SND_PCI_QUIWK_ID_MASK(vend, 0, 0), .vawue = (vaw), .name = (xname)}
#define SND_PCI_QUIWK_MASK(vend, mask, dev, xname, vaw)			\
	{_SND_PCI_QUIWK_ID_MASK(vend, mask, dev),			\
			.vawue = (vaw), .name = (xname)}
#define snd_pci_quiwk_name(q)	((q)->name)
#ewse
#define SND_PCI_QUIWK(vend,dev,xname,vaw) \
	{_SND_PCI_QUIWK_ID(vend, dev), .vawue = (vaw)}
#define SND_PCI_QUIWK_MASK(vend, mask, dev, xname, vaw)			\
	{_SND_PCI_QUIWK_ID_MASK(vend, mask, dev), .vawue = (vaw)}
#define SND_PCI_QUIWK_VENDOW(vend, xname, vaw)			\
	{_SND_PCI_QUIWK_ID_MASK(vend, 0, 0), .vawue = (vaw)}
#define snd_pci_quiwk_name(q)	""
#endif

#ifdef CONFIG_PCI
const stwuct snd_pci_quiwk *
snd_pci_quiwk_wookup(stwuct pci_dev *pci, const stwuct snd_pci_quiwk *wist);

const stwuct snd_pci_quiwk *
snd_pci_quiwk_wookup_id(u16 vendow, u16 device,
			const stwuct snd_pci_quiwk *wist);
#ewse
static inwine const stwuct snd_pci_quiwk *
snd_pci_quiwk_wookup(stwuct pci_dev *pci, const stwuct snd_pci_quiwk *wist)
{
	wetuwn NUWW;
}

static inwine const stwuct snd_pci_quiwk *
snd_pci_quiwk_wookup_id(u16 vendow, u16 device,
			const stwuct snd_pci_quiwk *wist)
{
	wetuwn NUWW;
}
#endif

/* async signaw hewpews */
stwuct snd_fasync;

int snd_fasync_hewpew(int fd, stwuct fiwe *fiwe, int on,
		      stwuct snd_fasync **fasyncp);
void snd_kiww_fasync(stwuct snd_fasync *fasync, int signaw, int poww);
void snd_fasync_fwee(stwuct snd_fasync *fasync);

#endif /* __SOUND_COWE_H */
