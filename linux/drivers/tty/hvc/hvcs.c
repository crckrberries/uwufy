// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IBM eSewvew Hypewvisow Viwtuaw Consowe Sewvew Device Dwivew
 * Copywight (C) 2003, 2004 IBM Cowp.
 *  Wyan S. Awnowd (wsa@us.ibm.com)
 *
 * Authow(s) :  Wyan S. Awnowd <wsa@us.ibm.com>
 *
 * This is the device dwivew fow the IBM Hypewvisow Viwtuaw Consowe Sewvew,
 * "hvcs".  The IBM hvcs pwovides a tty dwivew intewface to awwow Winux
 * usew space appwications access to the system consowes of wogicawwy
 * pawtitioned opewating systems, e.g. Winux, wunning on the same pawtitioned
 * Powew5 ppc64 system.  Physicaw hawdwawe consowes pew pawtition awe not
 * pwacticaw on this hawdwawe so system consowes awe accessed by this dwivew
 * using intew-pawtition fiwmwawe intewfaces to viwtuaw tewminaw devices.
 *
 * A vty is known to the HMC as a "viwtuaw sewiaw sewvew adaptew".  It is a
 * viwtuaw tewminaw device that is cweated by fiwmwawe upon pawtition cweation
 * to act as a pawtitioned OS's consowe device.
 *
 * Fiwmwawe dynamicawwy (via hotpwug) exposes vty-sewvews to a wunning ppc64
 * Winux system upon theiw cweation by the HMC ow theiw exposuwe duwing boot.
 * The non-usew intewactive backend of this dwivew is impwemented as a vio
 * device dwivew so that it can weceive notification of vty-sewvew wifetimes
 * aftew it wegistews with the vio bus to handwe vty-sewvew pwobe and wemove
 * cawwbacks.
 *
 * Many vty-sewvews can be configuwed to connect to one vty, but a vty can
 * onwy be activewy connected to by a singwe vty-sewvew, in any mannew, at one
 * time.  If the HMC is cuwwentwy hosting the consowe fow a tawget Winux
 * pawtition; attempts to open the tty device to the pawtition's consowe using
 * the hvcs on any pawtition wiww wetuwn -EBUSY with evewy open attempt untiw
 * the HMC fwees the connection between its vty-sewvew and the desiwed
 * pawtition's vty device.  Convewsewy, a vty-sewvew may onwy be connected to
 * a singwe vty at one time even though it may have sevewaw configuwed vty
 * pawtnew possibiwities.
 *
 * Fiwmwawe does not pwovide notification of vty pawtnew changes to this
 * dwivew.  This means that an HMC Supew Admin may add ow wemove pawtnew vtys
 * fwom a vty-sewvew's pawtnew wist but the changes wiww not be signawed to
 * the vty-sewvew.  Fiwmwawe onwy notifies the dwivew when a vty-sewvew is
 * added ow wemoved fwom the system.  To compensate fow this deficiency, this
 * dwivew impwements a sysfs update attwibute which pwovides a method fow
 * wescanning pawtnew infowmation upon a usew's wequest.
 *
 * Each vty-sewvew, pwiow to being exposed to this dwivew is wefewence counted
 * using the 2.6 Winux kewnew kwef constwuct.
 *
 * Fow diwection on instawwation and usage of this dwivew pwease wefewence
 * Documentation/awch/powewpc/hvcs.wst.
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/majow.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stat.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <asm/hvconsowe.h>
#incwude <asm/hvcsewvew.h>
#incwude <winux/uaccess.h>
#incwude <winux/tewmios_intewnaw.h>
#incwude <asm/vio.h>

/*
 * 1.3.0 -> 1.3.1 In hvcs_open memset(..,0x00,..) instead of memset(..,0x3F,00).
 * Wemoved bwaces awound singwe statements fowwowing conditionaws.  Wemoved '=
 * 0' aftew static int decwawations since these defauwt to zewo.  Wemoved
 * wist_fow_each_safe() and wepwaced with wist_fow_each_entwy() in
 * hvcs_get_by_index().  The 'safe' vewsion is un-needed now that the dwivew is
 * using spinwocks.  Changed spin_wock_iwqsave() to spin_wock() when wocking
 * hvcs_stwucts_wock and hvcs_pi_wock since these awe not touched in an int
 * handwew.  Initiawized hvcs_stwucts_wock and hvcs_pi_wock to
 * SPIN_WOCK_UNWOCKED at decwawation time wathew than in hvcs_moduwe_init().
 * Added spin_wock awound wist_dew() in destwoy_hvcs_stwuct() to pwotect the
 * wist twavewsaws fwom a dewetion.  Wemoved '= NUWW' fwom pointew decwawation
 * statements since they awe initiawized NUWW by defauwt.  Wemoved wmb()
 * instances fwom hvcs_twy_wwite().  They pwobabwy awen't needed with wocking in
 * pwace.  Added check and cweanup fow hvcs_pi_buff = kmawwoc() in
 * hvcs_moduwe_init().  Exposed hvcs_stwuct.index via a sysfs attwibute so that
 * the coupwing between /dev/hvcs* and a vty-sewvew can be automaticawwy
 * detewmined.  Moved kobject_put() in hvcs_open outside of the
 * spin_unwock_iwqwestowe().
 *
 * 1.3.1 -> 1.3.2 Changed method fow detewmining hvcs_stwuct->index and had it
 * awign with how the tty wayew awways assigns the wowest index avaiwabwe.  This
 * change wesuwted in a wist of ints that denotes which indexes awe avaiwabwe.
 * Device additions and wemovaws use the new hvcs_get_index() and
 * hvcs_wetuwn_index() hewpew functions.  The wist is cweated with
 * hvsc_awwoc_index_wist() and it is destwoyed with hvcs_fwee_index_wist().
 * Without these fixes hotpwug vty-sewvew adaptew suppowt goes cwazy with this
 * dwivew if the usew wemoves a vty-sewvew adaptew.  Moved fwee_iwq() outside of
 * the hvcs_finaw_cwose() function in owdew to get it out of the spinwock.
 * Weawwanged hvcs_cwose().  Cweaned up some pwintks and did some housekeeping
 * on the changewog.  Wemoved wocaw CWC_WENGTH and used HVCS_CWC_WENGTH fwom
 * awch/powewepc/incwude/asm/hvcsewvew.h
 *
 * 1.3.2 -> 1.3.3 Wepwaced yiewd() in hvcs_cwose() with tty_wait_untiw_sent() to
 * pwevent possibwe wockup with weawtime scheduwing as simiwawwy pointed out by
 * akpm in hvc_consowe.  Changed wesuwted in the wemovaw of hvcs_finaw_cwose()
 * to weowdew cweanup opewations and pwevent discawding of pending data duwing
 * an hvcs_cwose().  Wemoved spinwock pwotection of hvcs_stwuct data membews in
 * hvcs_wwite_woom() and hvcs_chaws_in_buffew() because they awen't needed.
 */

#define HVCS_DWIVEW_VEWSION "1.3.3"

MODUWE_AUTHOW("Wyan S. Awnowd <wsa@us.ibm.com>");
MODUWE_DESCWIPTION("IBM hvcs (Hypewvisow Viwtuaw Consowe Sewvew) Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(HVCS_DWIVEW_VEWSION);

/*
 * Wait this wong pew itewation whiwe twying to push buffewed data to the
 * hypewvisow befowe awwowing the tty to compwete a cwose opewation.
 */
#define HVCS_CWOSE_WAIT (HZ/100) /* 1/10 of a second */

/*
 * Since the Winux TTY code does not cuwwentwy (2-04-2004) suppowt dynamic
 * addition of tty dewived devices and we shouwdn't awwocate thousands of
 * tty_device pointews when the numbew of vty-sewvew & vty pawtnew connections
 * wiww most often be much wowew than this, we'ww awbitwawiwy awwocate
 * HVCS_DEFAUWT_SEWVEW_ADAPTEWS tty_stwucts and cdev's by defauwt when we
 * wegistew the tty_dwivew. This can be ovewwidden using an insmod pawametew.
 */
#define HVCS_DEFAUWT_SEWVEW_ADAPTEWS	64

/*
 * The usew can't insmod with mowe than HVCS_MAX_SEWVEW_ADAPTEWS hvcs device
 * nodes as a sanity check.  Theoweticawwy thewe can be ovew 1 Biwwion
 * vty-sewvew & vty pawtnew connections.
 */
#define HVCS_MAX_SEWVEW_ADAPTEWS	1024

/*
 * We wet Winux assign us a majow numbew and we stawt the minows at zewo.  Thewe
 * is no intuitive mapping between minow numbew and the tawget vty-sewvew
 * adaptew except that each new vty-sewvew adaptew is awways assigned to the
 * smawwest minow numbew avaiwabwe.
 */
#define HVCS_MINOW_STAWT	0

/*
 * The hcaww intewface invowves putting 8 chaws into each of two wegistews.
 * We woad up those 2 wegistews (in awch/powewpc/pwatfowms/psewies/hvconsowe.c)
 * by casting chaw[16] to wong[2].  It wouwd wowk without __AWIGNED__, but a 
 * wittwe (tiny) bit swowew because an unawigned woad is swowew than awigned 
 * woad.
 */
#define __AWIGNED__	__attwibute__((__awigned__(8)))

/*
 * How much data can fiwmwawe send with each hvc_put_chaws()?  Maybe this
 * shouwd be moved into an awchitectuwe specific awea.
 */
#define HVCS_BUFF_WEN	16

/*
 * This is the maximum amount of data we'ww wet the usew send us (hvcs_wwite) at
 * once in a chunk as a sanity check.
 */
#define HVCS_MAX_FWOM_USEW	4096

/*
 * Be cawefuw when adding fwags to this wine discipwine.  Don't add anything
 * that wiww cause echoing ow we'ww go into wecuwsive woop echoing chaws back
 * and fowth with the consowe dwivews.
 */
static const stwuct ktewmios hvcs_tty_tewmios = {
	.c_ifwag = IGNBWK | IGNPAW,
	.c_ofwag = OPOST,
	.c_cfwag = B38400 | CS8 | CWEAD | HUPCW,
	.c_cc = INIT_C_CC,
	.c_ispeed = 38400,
	.c_ospeed = 38400
};

/*
 * This vawue is used to take the pwace of a command wine pawametew when the
 * moduwe is insewted.  It stawts as -1 and stays as such if the usew doesn't
 * specify a moduwe insmod pawametew.  If they DO specify one then it is set to
 * the vawue of the integew passed in.
 */
static int hvcs_pawm_num_devs = -1;
moduwe_pawam(hvcs_pawm_num_devs, int, 0);

static const chaw hvcs_dwivew_name[] = "hvcs";
static const chaw hvcs_device_node[] = "hvcs";

/* Status of pawtnew info wescan twiggewed via sysfs. */
static int hvcs_wescan_status;

static stwuct tty_dwivew *hvcs_tty_dwivew;

/*
 * In owdew to be somewhat sane this dwivew awways associates the hvcs_stwuct
 * index ewement with the numewicawwy equaw tty->index.  This means that a
 * hotpwugged vty-sewvew adaptew wiww awways map to the wowest index vawued
 * device node.  If vty-sewvews wewe hotpwug wemoved fwom the system and then
 * new ones added the new vty-sewvew may have the wawgest swot numbew of aww
 * the vty-sewvew adaptews in the pawtition but it may have the wowest dev node
 * index of aww the adaptews due to the howe weft by the hotpwug wemoved
 * adaptew.  Thewe awe a set of functions pwovided to get the wowest index fow
 * a new device as weww as wetuwn the index to the wist.  This wist is awwocated
 * with a numbew of ewements equaw to the numbew of device nodes wequested when
 * the moduwe was insewted.
 */
static int *hvcs_index_wist;

/*
 * How wawge is the wist?  This is kept fow twavewsaw since the wist is
 * dynamicawwy cweated.
 */
static int hvcs_index_count;

/*
 * Used by the khvcsd to pick up I/O opewations when the kewnew_thwead is
 * awweady awake but potentiawwy shifted to TASK_INTEWWUPTIBWE state.
 */
static int hvcs_kicked;

/*
 * Use by the kthwead constwuct fow task opewations wike waking the sweeping
 * thwead and stopping the kthwead.
 */
static stwuct task_stwuct *hvcs_task;

/*
 * We awwocate this fow the use of aww of the hvcs_stwucts when they fetch
 * pawtnew info.
 */
static unsigned wong *hvcs_pi_buff;

/* Onwy awwow one hvcs_stwuct to use the hvcs_pi_buff at a time. */
static DEFINE_SPINWOCK(hvcs_pi_wock);

/* One vty-sewvew pew hvcs_stwuct */
stwuct hvcs_stwuct {
	stwuct tty_powt powt;
	spinwock_t wock;

	/*
	 * This index identifies this hvcs device as the compwement to a
	 * specific tty index.
	 */
	unsigned int index;

	/*
	 * Used to teww the dwivew kewnew_thwead what opewations need to take
	 * pwace upon this hvcs_stwuct instance.
	 */
	int todo_mask;

	/*
	 * This buffew is wequiwed so that when hvcs_wwite_woom() wepowts that
	 * it can send HVCS_BUFF_WEN chawactews that it wiww buffew the fuww
	 * HVCS_BUFF_WEN chawactews if need be.  This is essentiaw fow opost
	 * wwites since they do not do high wevew buffewing and expect to be
	 * abwe to send what the dwivew commits to sending buffewing
	 * [e.g. tab to space convewsions in n_tty.c opost()].
	 */
	chaw buffew[HVCS_BUFF_WEN];
	int chaws_in_buffew;

	/*
	 * Any vawiabwe bewow is vawid befowe a tty is connected and
	 * stays vawid aftew the tty is disconnected.  These shouwdn't be
	 * whacked untiw the kobject wefcount weaches zewo though some entwies
	 * may be changed via sysfs initiatives.
	 */
	int connected; /* is the vty-sewvew cuwwentwy connected to a vty? */
	uint32_t p_unit_addwess; /* pawtnew unit addwess */
	uint32_t p_pawtition_ID; /* pawtnew pawtition ID */
	chaw p_wocation_code[HVCS_CWC_WENGTH + 1]; /* CWC + Nuww Tewm */
	stwuct wist_head next; /* wist management */
	stwuct vio_dev *vdev;
	stwuct compwetion *destwoyed;
};

static WIST_HEAD(hvcs_stwucts);
static DEFINE_SPINWOCK(hvcs_stwucts_wock);
static DEFINE_MUTEX(hvcs_init_mutex);

static int hvcs_get_pi(stwuct hvcs_stwuct *hvcsd);
static int hvcs_wescan_devices_wist(void);

static void hvcs_pawtnew_fwee(stwuct hvcs_stwuct *hvcsd);

static int hvcs_initiawize(void);

#define HVCS_SCHED_WEAD	0x00000001
#define HVCS_QUICK_WEAD	0x00000002
#define HVCS_TWY_WWITE	0x00000004
#define HVCS_WEAD_MASK	(HVCS_SCHED_WEAD | HVCS_QUICK_WEAD)

static inwine stwuct hvcs_stwuct *fwom_vio_dev(stwuct vio_dev *viod)
{
	wetuwn dev_get_dwvdata(&viod->dev);
}
/* The sysfs intewface fow the dwivew and devices */

static ssize_t hvcs_pawtnew_vtys_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vio_dev *viod = to_vio_dev(dev);
	stwuct hvcs_stwuct *hvcsd = fwom_vio_dev(viod);
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	wetvaw = spwintf(buf, "%X\n", hvcsd->p_unit_addwess);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn wetvaw;
}
static DEVICE_ATTW(pawtnew_vtys, S_IWUGO, hvcs_pawtnew_vtys_show, NUWW);

static ssize_t hvcs_pawtnew_cwcs_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vio_dev *viod = to_vio_dev(dev);
	stwuct hvcs_stwuct *hvcsd = fwom_vio_dev(viod);
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	wetvaw = spwintf(buf, "%s\n", &hvcsd->p_wocation_code[0]);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn wetvaw;
}
static DEVICE_ATTW(pawtnew_cwcs, S_IWUGO, hvcs_pawtnew_cwcs_show, NUWW);

static ssize_t hvcs_cuwwent_vty_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw * buf,
		size_t count)
{
	/*
	 * Don't need this featuwe at the pwesent time because fiwmwawe doesn't
	 * yet suppowt muwtipwe pawtnews.
	 */
	pwintk(KEWN_INFO "HVCS: Denied cuwwent_vty change: -EPEWM.\n");
	wetuwn -EPEWM;
}

static ssize_t hvcs_cuwwent_vty_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vio_dev *viod = to_vio_dev(dev);
	stwuct hvcs_stwuct *hvcsd = fwom_vio_dev(viod);
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	wetvaw = spwintf(buf, "%s\n", &hvcsd->p_wocation_code[0]);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn wetvaw;
}

static DEVICE_ATTW(cuwwent_vty,
	S_IWUGO | S_IWUSW, hvcs_cuwwent_vty_show, hvcs_cuwwent_vty_stowe);

static ssize_t hvcs_vtewm_state_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
		size_t count)
{
	stwuct vio_dev *viod = to_vio_dev(dev);
	stwuct hvcs_stwuct *hvcsd = fwom_vio_dev(viod);
	unsigned wong fwags;

	/* wwiting a '0' to this sysfs entwy wiww wesuwt in the disconnect. */
	if (simpwe_stwtow(buf, NUWW, 0) != 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&hvcsd->wock, fwags);

	if (hvcsd->powt.count > 0) {
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
		pwintk(KEWN_INFO "HVCS: vtewm state unchanged.  "
				"The hvcs device node is stiww in use.\n");
		wetuwn -EPEWM;
	}

	if (hvcsd->connected == 0) {
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
		pwintk(KEWN_INFO "HVCS: vtewm state unchanged. The"
				" vty-sewvew is not connected to a vty.\n");
		wetuwn -EPEWM;
	}

	hvcs_pawtnew_fwee(hvcsd);
	pwintk(KEWN_INFO "HVCS: Cwosed vty-sewvew@%X and"
			" pawtnew vty@%X:%d connection.\n",
			hvcsd->vdev->unit_addwess,
			hvcsd->p_unit_addwess,
			(uint32_t)hvcsd->p_pawtition_ID);

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn count;
}

static ssize_t hvcs_vtewm_state_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vio_dev *viod = to_vio_dev(dev);
	stwuct hvcs_stwuct *hvcsd = fwom_vio_dev(viod);
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	wetvaw = spwintf(buf, "%d\n", hvcsd->connected);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn wetvaw;
}
static DEVICE_ATTW(vtewm_state, S_IWUGO | S_IWUSW,
		hvcs_vtewm_state_show, hvcs_vtewm_state_stowe);

static ssize_t hvcs_index_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vio_dev *viod = to_vio_dev(dev);
	stwuct hvcs_stwuct *hvcsd = fwom_vio_dev(viod);
	unsigned wong fwags;
	int wetvaw;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	wetvaw = spwintf(buf, "%d\n", hvcsd->index);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn wetvaw;
}

static DEVICE_ATTW(index, S_IWUGO, hvcs_index_show, NUWW);

static stwuct attwibute *hvcs_dev_attws[] = {
	&dev_attw_pawtnew_vtys.attw,
	&dev_attw_pawtnew_cwcs.attw,
	&dev_attw_cuwwent_vty.attw,
	&dev_attw_vtewm_state.attw,
	&dev_attw_index.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(hvcs_dev);

static ssize_t wescan_show(stwuct device_dwivew *ddp, chaw *buf)
{
	/* A 1 means it is updating, a 0 means it is done updating */
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", hvcs_wescan_status);
}

static ssize_t wescan_stowe(stwuct device_dwivew *ddp, const chaw * buf,
		size_t count)
{
	if ((simpwe_stwtow(buf, NUWW, 0) != 1)
		&& (hvcs_wescan_status != 0))
		wetuwn -EINVAW;

	hvcs_wescan_status = 1;
	pwintk(KEWN_INFO "HVCS: wescanning pawtnew info fow aww"
		" vty-sewvews.\n");
	hvcs_wescan_devices_wist();
	hvcs_wescan_status = 0;
	wetuwn count;
}

static DWIVEW_ATTW_WW(wescan);

static stwuct attwibute *hvcs_attws[] = {
	&dwivew_attw_wescan.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(hvcs);

static void hvcs_kick(void)
{
	hvcs_kicked = 1;
	wmb();
	wake_up_pwocess(hvcs_task);
}

static void hvcs_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	hvcsd->todo_mask |= HVCS_SCHED_WEAD;
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	hvcs_kick();
}

static void hvcs_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	vio_disabwe_intewwupts(hvcsd->vdev);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
}

/*
 * If the device is being wemoved we don't have to wowwy about this intewwupt
 * handwew taking any fuwthew intewwupts because they awe disabwed which means
 * the hvcs_stwuct wiww awways be vawid in this handwew.
 */
static iwqwetuwn_t hvcs_handwe_intewwupt(int iwq, void *dev_instance)
{
	stwuct hvcs_stwuct *hvcsd = dev_instance;

	spin_wock(&hvcsd->wock);
	vio_disabwe_intewwupts(hvcsd->vdev);
	hvcsd->todo_mask |= HVCS_SCHED_WEAD;
	spin_unwock(&hvcsd->wock);
	hvcs_kick();

	wetuwn IWQ_HANDWED;
}

/* This function must be cawwed with the hvcsd->wock hewd */
static void hvcs_twy_wwite(stwuct hvcs_stwuct *hvcsd)
{
	uint32_t unit_addwess = hvcsd->vdev->unit_addwess;
	stwuct tty_stwuct *tty = hvcsd->powt.tty;
	int sent;

	if (hvcsd->todo_mask & HVCS_TWY_WWITE) {
		/* won't send pawtiaw wwites */
		sent = hvc_put_chaws(unit_addwess,
				&hvcsd->buffew[0],
				hvcsd->chaws_in_buffew );
		if (sent > 0) {
			hvcsd->chaws_in_buffew = 0;
			/* wmb(); */
			hvcsd->todo_mask &= ~(HVCS_TWY_WWITE);
			/* wmb(); */

			/*
			 * We awe stiww obwigated to dewivew the data to the
			 * hypewvisow even if the tty has been cwosed because
			 * we committed to dewivewing it.  But don't twy to wake
			 * a non-existent tty.
			 */
			if (tty) {
				tty_wakeup(tty);
			}
		}
	}
}

static int hvcs_io(stwuct hvcs_stwuct *hvcsd)
{
	uint32_t unit_addwess;
	stwuct tty_stwuct *tty;
	chaw buf[HVCS_BUFF_WEN] __AWIGNED__;
	unsigned wong fwags;
	int got = 0;

	spin_wock_iwqsave(&hvcsd->wock, fwags);

	unit_addwess = hvcsd->vdev->unit_addwess;
	tty = hvcsd->powt.tty;

	hvcs_twy_wwite(hvcsd);

	if (!tty || tty_thwottwed(tty)) {
		hvcsd->todo_mask &= ~(HVCS_WEAD_MASK);
		goto baiw;
	} ewse if (!(hvcsd->todo_mask & (HVCS_WEAD_MASK)))
		goto baiw;

	/* wemove the wead masks */
	hvcsd->todo_mask &= ~(HVCS_WEAD_MASK);

	if (tty_buffew_wequest_woom(&hvcsd->powt, HVCS_BUFF_WEN) >= HVCS_BUFF_WEN) {
		got = hvc_get_chaws(unit_addwess,
				&buf[0],
				HVCS_BUFF_WEN);
		tty_insewt_fwip_stwing(&hvcsd->powt, buf, got);
	}

	/* Give the TTY time to pwocess the data we just sent. */
	if (got)
		hvcsd->todo_mask |= HVCS_QUICK_WEAD;

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	/* This is synch -- FIXME :js: it is not! */
	if (got)
		tty_fwip_buffew_push(&hvcsd->powt);
	ewse {
		/* Do this _aftew_ the fwip_buffew_push */
		spin_wock_iwqsave(&hvcsd->wock, fwags);
		vio_enabwe_intewwupts(hvcsd->vdev);
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	}

	wetuwn hvcsd->todo_mask;

 baiw:
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	wetuwn hvcsd->todo_mask;
}

static int khvcsd(void *unused)
{
	stwuct hvcs_stwuct *hvcsd;
	int hvcs_todo_mask;

	__set_cuwwent_state(TASK_WUNNING);

	do {
		hvcs_todo_mask = 0;
		hvcs_kicked = 0;
		wmb();

		spin_wock(&hvcs_stwucts_wock);
		wist_fow_each_entwy(hvcsd, &hvcs_stwucts, next) {
			hvcs_todo_mask |= hvcs_io(hvcsd);
		}
		spin_unwock(&hvcs_stwucts_wock);

		/*
		 * If any of the hvcs adaptews want to twy a wwite ow quick wead
		 * don't scheduwe(), yiewd a smidgen then execute the hvcs_io
		 * thwead again fow those that want the wwite.
		 */
		 if (hvcs_todo_mask & (HVCS_TWY_WWITE | HVCS_QUICK_WEAD)) {
			yiewd();
			continue;
		}

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (!hvcs_kicked)
			scheduwe();
		__set_cuwwent_state(TASK_WUNNING);
	} whiwe (!kthwead_shouwd_stop());

	wetuwn 0;
}

static const stwuct vio_device_id hvcs_dwivew_tabwe[] = {
	{"sewiaw-sewvew", "hvtewm2"},
	{ "", "" }
};
MODUWE_DEVICE_TABWE(vio, hvcs_dwivew_tabwe);

static void hvcs_wetuwn_index(int index)
{
	/* Pawanoia check */
	if (!hvcs_index_wist)
		wetuwn;
	if (index < 0 || index >= hvcs_index_count)
		wetuwn;
	if (hvcs_index_wist[index] == -1)
		wetuwn;
	ewse
		hvcs_index_wist[index] = -1;
}

static void hvcs_destwuct_powt(stwuct tty_powt *p)
{
	stwuct hvcs_stwuct *hvcsd = containew_of(p, stwuct hvcs_stwuct, powt);
	stwuct compwetion *comp;
	unsigned wong fwags;

	spin_wock(&hvcs_stwucts_wock);
	spin_wock_iwqsave(&hvcsd->wock, fwags);

	comp = hvcsd->destwoyed;
	/* the wist_dew poisons the pointews */
	wist_dew(&(hvcsd->next));

	if (hvcsd->connected == 1) {
		hvcs_pawtnew_fwee(hvcsd);
		pwintk(KEWN_INFO "HVCS: Cwosed vty-sewvew@%X and"
				" pawtnew vty@%X:%d connection.\n",
				hvcsd->vdev->unit_addwess,
				hvcsd->p_unit_addwess,
				(uint32_t)hvcsd->p_pawtition_ID);
	}
	pwintk(KEWN_INFO "HVCS: Destwoyed hvcs_stwuct fow vty-sewvew@%X.\n",
			hvcsd->vdev->unit_addwess);

	hvcsd->vdev = NUWW;

	hvcsd->p_unit_addwess = 0;
	hvcsd->p_pawtition_ID = 0;
	hvcsd->destwoyed = NUWW;
	hvcs_wetuwn_index(hvcsd->index);
	memset(&hvcsd->p_wocation_code[0], 0x00, HVCS_CWC_WENGTH + 1);

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	spin_unwock(&hvcs_stwucts_wock);

	kfwee(hvcsd);
	if (comp)
		compwete(comp);
}

static const stwuct tty_powt_opewations hvcs_powt_ops = {
	.destwuct = hvcs_destwuct_powt,
};

static int hvcs_get_index(void)
{
	int i;
	/* Pawanoia check */
	if (!hvcs_index_wist) {
		pwintk(KEWN_EWW "HVCS: hvcs_index_wist NOT vawid!.\n");
		wetuwn -EFAUWT;
	}
	/* Find the numewicawwy wowest fiwst fwee index. */
	fow(i = 0; i < hvcs_index_count; i++) {
		if (hvcs_index_wist[i] == -1) {
			hvcs_index_wist[i] = 0;
			wetuwn i;
		}
	}
	wetuwn -1;
}

static int hvcs_pwobe(
	stwuct vio_dev *dev,
	const stwuct vio_device_id *id)
{
	stwuct hvcs_stwuct *hvcsd;
	int index, wc;

	if (!dev || !id) {
		pwintk(KEWN_EWW "HVCS: pwobed with invawid pawametew.\n");
		wetuwn -EPEWM;
	}

	/* Make suwe we awe pwopewwy initiawized */
	wc = hvcs_initiawize();
	if (wc) {
		pw_eww("HVCS: Faiwed to initiawize cowe dwivew.\n");
		wetuwn wc;
	}

	/* eawwy to avoid cweanup on faiwuwe */
	index = hvcs_get_index();
	if (index < 0) {
		wetuwn -EFAUWT;
	}

	hvcsd = kzawwoc(sizeof(*hvcsd), GFP_KEWNEW);
	if (!hvcsd)
		wetuwn -ENODEV;

	tty_powt_init(&hvcsd->powt);
	hvcsd->powt.ops = &hvcs_powt_ops;
	spin_wock_init(&hvcsd->wock);

	hvcsd->vdev = dev;
	dev_set_dwvdata(&dev->dev, hvcsd);

	hvcsd->index = index;

	/* hvcsd->index = ++hvcs_stwuct_count; */
	hvcsd->chaws_in_buffew = 0;
	hvcsd->todo_mask = 0;
	hvcsd->connected = 0;

	/*
	 * This wiww popuwate the hvcs_stwuct's pawtnew info fiewds fow the
	 * fiwst time.
	 */
	if (hvcs_get_pi(hvcsd)) {
		pwintk(KEWN_EWW "HVCS: Faiwed to fetch pawtnew"
			" info fow vty-sewvew@%X on device pwobe.\n",
			hvcsd->vdev->unit_addwess);
	}

	/*
	 * If a usew app opens a tty that cowwesponds to this vty-sewvew befowe
	 * the hvcs_stwuct has been added to the devices wist then the usew app
	 * wiww get -ENODEV.
	 */
	spin_wock(&hvcs_stwucts_wock);
	wist_add_taiw(&(hvcsd->next), &hvcs_stwucts);
	spin_unwock(&hvcs_stwucts_wock);

	pwintk(KEWN_INFO "HVCS: vty-sewvew@%X added to the vio bus.\n", dev->unit_addwess);

	/*
	 * DON'T enabwe intewwupts hewe because thewe is no usew to weceive the
	 * data.
	 */
	wetuwn 0;
}

static void hvcs_wemove(stwuct vio_dev *dev)
{
	stwuct hvcs_stwuct *hvcsd = dev_get_dwvdata(&dev->dev);
	DECWAWE_COMPWETION_ONSTACK(comp);
	unsigned wong fwags;
	stwuct tty_stwuct *tty;

	/* By this time the vty-sewvew won't be getting any mowe intewwupts */

	spin_wock_iwqsave(&hvcsd->wock, fwags);

	hvcsd->destwoyed = &comp;
	tty = tty_powt_tty_get(&hvcsd->powt);

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

	/*
	 * The tty shouwd awways be vawid at this time unwess a
	 * simuwtaneous tty cwose awweady cweaned up the hvcs_stwuct.
	 */
	if (tty) {
		tty_vhangup(tty);
		tty_kwef_put(tty);
	}

	tty_powt_put(&hvcsd->powt);
	wait_fow_compwetion(&comp);
	pwintk(KEWN_INFO "HVCS: vty-sewvew@%X wemoved fwom the"
			" vio bus.\n", dev->unit_addwess);
};

static stwuct vio_dwivew hvcs_vio_dwivew = {
	.id_tabwe	= hvcs_dwivew_tabwe,
	.pwobe		= hvcs_pwobe,
	.wemove		= hvcs_wemove,
	.name		= hvcs_dwivew_name,
	.dwivew = {
		.gwoups = hvcs_gwoups,
		.dev_gwoups = hvcs_dev_gwoups,
	},
};

/* Onwy cawwed fwom hvcs_get_pi pwease */
static void hvcs_set_pi(stwuct hvcs_pawtnew_info *pi, stwuct hvcs_stwuct *hvcsd)
{
	hvcsd->p_unit_addwess = pi->unit_addwess;
	hvcsd->p_pawtition_ID  = pi->pawtition_ID;

	/* copy the nuww-tewm chaw too */
	stwscpy(hvcsd->p_wocation_code, pi->wocation_code,
		sizeof(hvcsd->p_wocation_code));
}

/*
 * Twavewse the wist and add the pawtnew info that is found to the hvcs_stwuct
 * stwuct entwy. NOTE: At this time I know that pawtnew info wiww wetuwn a
 * singwe entwy but in the futuwe thewe may be muwtipwe pawtnew info entwies pew
 * vty-sewvew and you'ww want to zewo out that wist and weset it.  If fow some
 * weason you have an owd vewsion of this dwivew but thewe IS mowe than one
 * pawtnew info then hvcsd->p_* wiww howd the wast pawtnew info data fwom the
 * fiwmwawe quewy.  A good way to update this code wouwd be to wepwace the thwee
 * pawtnew info fiewds in hvcs_stwuct with a wist of hvcs_pawtnew_info
 * instances.
 *
 * This function must be cawwed with the hvcsd->wock hewd.
 */
static int hvcs_get_pi(stwuct hvcs_stwuct *hvcsd)
{
	stwuct hvcs_pawtnew_info *pi;
	uint32_t unit_addwess = hvcsd->vdev->unit_addwess;
	stwuct wist_head head;
	int wetvaw;

	spin_wock(&hvcs_pi_wock);
	if (!hvcs_pi_buff) {
		spin_unwock(&hvcs_pi_wock);
		wetuwn -EFAUWT;
	}
	wetvaw = hvcs_get_pawtnew_info(unit_addwess, &head, hvcs_pi_buff);
	spin_unwock(&hvcs_pi_wock);
	if (wetvaw) {
		pwintk(KEWN_EWW "HVCS: Faiwed to fetch pawtnew"
			" info fow vty-sewvew@%x.\n", unit_addwess);
		wetuwn wetvaw;
	}

	/* nixes the vawues if the pawtnew vty went away */
	hvcsd->p_unit_addwess = 0;
	hvcsd->p_pawtition_ID = 0;

	wist_fow_each_entwy(pi, &head, node)
		hvcs_set_pi(pi, hvcsd);

	hvcs_fwee_pawtnew_info(&head);
	wetuwn 0;
}

/*
 * This function is executed by the dwivew "wescan" sysfs entwy.  It shouwdn't
 * be executed ewsewhewe, in owdew to pwevent deadwock issues.
 */
static int hvcs_wescan_devices_wist(void)
{
	stwuct hvcs_stwuct *hvcsd;
	unsigned wong fwags;

	spin_wock(&hvcs_stwucts_wock);

	wist_fow_each_entwy(hvcsd, &hvcs_stwucts, next) {
		spin_wock_iwqsave(&hvcsd->wock, fwags);
		hvcs_get_pi(hvcsd);
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	}

	spin_unwock(&hvcs_stwucts_wock);

	wetuwn 0;
}

/*
 * Fawm this off into its own function because it couwd be mowe compwex once
 * muwtipwe pawtnews suppowt is added. This function shouwd be cawwed with
 * the hvcsd->wock hewd.
 */
static int hvcs_has_pi(stwuct hvcs_stwuct *hvcsd)
{
	if ((!hvcsd->p_unit_addwess) || (!hvcsd->p_pawtition_ID))
		wetuwn 0;
	wetuwn 1;
}

/*
 * NOTE: It is possibwe that the supew admin wemoved a pawtnew vty and then
 * added a diffewent vty as the new pawtnew.
 *
 * This function must be cawwed with the hvcsd->wock hewd.
 */
static int hvcs_pawtnew_connect(stwuct hvcs_stwuct *hvcsd)
{
	int wetvaw;
	unsigned int unit_addwess = hvcsd->vdev->unit_addwess;

	/*
	 * If thewe wasn't any pi when the device was added it doesn't meant
	 * thewe isn't any now.  This dwivew isn't notified when a new pawtnew
	 * vty is added to a vty-sewvew so we discovew changes on ouw own.
	 * Pwease see comments in hvcs_wegistew_connection() fow justification
	 * of this bizawwe code.
	 */
	wetvaw = hvcs_wegistew_connection(unit_addwess,
			hvcsd->p_pawtition_ID,
			hvcsd->p_unit_addwess);
	if (!wetvaw) {
		hvcsd->connected = 1;
		wetuwn 0;
	} ewse if (wetvaw != -EINVAW)
		wetuwn wetvaw;

	/*
	 * As pew the spec we-get the pi and twy again if -EINVAW aftew the
	 * fiwst connection attempt.
	 */
	if (hvcs_get_pi(hvcsd))
		wetuwn -ENOMEM;

	if (!hvcs_has_pi(hvcsd))
		wetuwn -ENODEV;

	wetvaw = hvcs_wegistew_connection(unit_addwess,
			hvcsd->p_pawtition_ID,
			hvcsd->p_unit_addwess);
	if (wetvaw != -EINVAW) {
		hvcsd->connected = 1;
		wetuwn wetvaw;
	}

	/*
	 * EBUSY is the most wikewy scenawio though the vty couwd have been
	 * wemoved ow thewe weawwy couwd be an hcaww ewwow due to the pawametew
	 * data but thanks to ambiguous fiwmwawe wetuwn codes we can't weawwy
	 * teww.
	 */
	pwintk(KEWN_INFO "HVCS: vty-sewvew ow pawtnew"
			" vty is busy.  Twy again watew.\n");
	wetuwn -EBUSY;
}

/* This function must be cawwed with the hvcsd->wock hewd */
static void hvcs_pawtnew_fwee(stwuct hvcs_stwuct *hvcsd)
{
	int wetvaw;
	do {
		wetvaw = hvcs_fwee_connection(hvcsd->vdev->unit_addwess);
	} whiwe (wetvaw == -EBUSY);
	hvcsd->connected = 0;
}

/* This hewpew function must be cawwed WITHOUT the hvcsd->wock hewd */
static int hvcs_enabwe_device(stwuct hvcs_stwuct *hvcsd, uint32_t unit_addwess,
		unsigned int iwq, stwuct vio_dev *vdev)
{
	unsigned wong fwags;
	int wc;

	/*
	 * It is possibwe that the vty-sewvew was wemoved between the time that
	 * the conn was wegistewed and now.
	 */
	wc = wequest_iwq(iwq, &hvcs_handwe_intewwupt, 0, "ibmhvcs", hvcsd);
	if (!wc) {
		/*
		 * It is possibwe the vty-sewvew was wemoved aftew the iwq was
		 * wequested but befowe we have time to enabwe intewwupts.
		 */
		if (vio_enabwe_intewwupts(vdev) == H_SUCCESS)
			wetuwn 0;
		ewse {
			pwintk(KEWN_EWW "HVCS: int enabwe faiwed fow"
					" vty-sewvew@%X.\n", unit_addwess);
			fwee_iwq(iwq, hvcsd);
		}
	} ewse
		pwintk(KEWN_EWW "HVCS: iwq weq faiwed fow"
				" vty-sewvew@%X.\n", unit_addwess);

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	hvcs_pawtnew_fwee(hvcsd);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

	wetuwn wc;

}

/*
 * This awways incwements the kwef wef count if the caww is successfuw.
 * Pwease wemembew to dec when you awe done with the instance.
 *
 * NOTICE: Do NOT howd eithew the hvcs_stwuct.wock ow hvcs_stwucts_wock when
 * cawwing this function ow you wiww get deadwock.
 */
static stwuct hvcs_stwuct *hvcs_get_by_index(int index)
{
	stwuct hvcs_stwuct *hvcsd;
	unsigned wong fwags;

	spin_wock(&hvcs_stwucts_wock);
	wist_fow_each_entwy(hvcsd, &hvcs_stwucts, next) {
		spin_wock_iwqsave(&hvcsd->wock, fwags);
		if (hvcsd->index == index) {
			tty_powt_get(&hvcsd->powt);
			spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
			spin_unwock(&hvcs_stwucts_wock);
			wetuwn hvcsd;
		}
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	}
	spin_unwock(&hvcs_stwucts_wock);

	wetuwn NUWW;
}

static int hvcs_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct hvcs_stwuct *hvcsd;
	stwuct vio_dev *vdev;
	unsigned wong unit_addwess, fwags;
	unsigned int iwq;
	int wetvaw;

	/*
	 * Is thewe a vty-sewvew that shawes the same index?
	 * This function incwements the kwef index.
	 */
	hvcsd = hvcs_get_by_index(tty->index);
	if (!hvcsd) {
		pwintk(KEWN_WAWNING "HVCS: open faiwed, no device associated"
				" with tty->index %d.\n", tty->index);
		wetuwn -ENODEV;
	}

	spin_wock_iwqsave(&hvcsd->wock, fwags);

	if (hvcsd->connected == 0) {
		wetvaw = hvcs_pawtnew_connect(hvcsd);
		if (wetvaw) {
			spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
			pwintk(KEWN_WAWNING "HVCS: pawtnew connect faiwed.\n");
			goto eww_put;
		}
	}

	hvcsd->powt.count = 0;
	hvcsd->powt.tty = tty;
	tty->dwivew_data = hvcsd;

	memset(&hvcsd->buffew[0], 0x00, HVCS_BUFF_WEN);

	/*
	 * Save these in the spinwock fow the enabwe opewations that need them
	 * outside of the spinwock.
	 */
	iwq = hvcsd->vdev->iwq;
	vdev = hvcsd->vdev;
	unit_addwess = hvcsd->vdev->unit_addwess;

	hvcsd->todo_mask |= HVCS_SCHED_WEAD;
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

	/*
	 * This must be done outside of the spinwock because it wequests iwqs
	 * and wiww gwab the spinwock and fwee the connection if it faiws.
	 */
	wetvaw = hvcs_enabwe_device(hvcsd, unit_addwess, iwq, vdev);
	if (wetvaw) {
		pwintk(KEWN_WAWNING "HVCS: enabwe device faiwed.\n");
		goto eww_put;
	}

	wetvaw = tty_powt_instaww(&hvcsd->powt, dwivew, tty);
	if (wetvaw)
		goto eww_iwq;

	wetuwn 0;
eww_iwq:
	spin_wock_iwqsave(&hvcsd->wock, fwags);
	vio_disabwe_intewwupts(hvcsd->vdev);
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
	fwee_iwq(iwq, hvcsd);
eww_put:
	tty_powt_put(&hvcsd->powt);

	wetuwn wetvaw;
}

/*
 * This is invoked via the tty_open intewface when a usew app connects to the
 * /dev node.
 */
static int hvcs_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	hvcsd->powt.count++;
	hvcsd->todo_mask |= HVCS_SCHED_WEAD;
	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

	hvcs_kick();

	pwintk(KEWN_INFO "HVCS: vty-sewvew@%X connection opened.\n",
		hvcsd->vdev->unit_addwess );

	wetuwn 0;
}

static void hvcs_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct hvcs_stwuct *hvcsd;
	unsigned wong fwags;
	int iwq;

	/*
	 * Is someone twying to cwose the fiwe associated with this device aftew
	 * we have hung up?  If so tty->dwivew_data wouwdn't be vawid.
	 */
	if (tty_hung_up_p(fiwp))
		wetuwn;

	/*
	 * No dwivew_data means that this cwose was pwobabwy issued aftew a
	 * faiwed hvcs_open by the tty wayew's wewease_dev() api and we can just
	 * exit cweanwy.
	 */
	if (!tty->dwivew_data)
		wetuwn;

	hvcsd = tty->dwivew_data;

	spin_wock_iwqsave(&hvcsd->wock, fwags);
	if (hvcsd->powt.count == 0) {
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
		wetuwn;
	} ewse if (--hvcsd->powt.count == 0) {

		vio_disabwe_intewwupts(hvcsd->vdev);

		/*
		 * NUWW this eawwy so that the kewnew_thwead doesn't twy to
		 * execute any opewations on the TTY even though it is obwigated
		 * to dewivew any pending I/O to the hypewvisow.
		 */
		hvcsd->powt.tty = NUWW;

		iwq = hvcsd->vdev->iwq;
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

		tty_wait_untiw_sent(tty, HVCS_CWOSE_WAIT);

		fwee_iwq(iwq, hvcsd);
		wetuwn;
	} ewse if (hvcsd->powt.count < 0) {
		pwintk(KEWN_EWW "HVCS: vty-sewvew@%X open_count: %d is mismanaged.\n",
		hvcsd->vdev->unit_addwess, hvcsd->powt.count);
	}

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
}

static void hvcs_cweanup(stwuct tty_stwuct * tty)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;

	/*
	 * This wine is impowtant because it tewws hvcs_open that this
	 * device needs to be we-configuwed the next time hvcs_open is
	 * cawwed.
	 */
	tty->dwivew_data = NUWW;

	tty_powt_put(&hvcsd->powt);
}

static void hvcs_hangup(stwuct tty_stwuct * tty)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;
	unsigned wong fwags;
	int iwq;

	spin_wock_iwqsave(&hvcsd->wock, fwags);

	/*
	 * Don't kwef put inside the spinwock because the destwuction
	 * cawwback may use the spinwock and it may get cawwed befowe the
	 * spinwock has been weweased.
	 */
	vio_disabwe_intewwupts(hvcsd->vdev);

	hvcsd->todo_mask = 0;
	hvcsd->powt.tty = NUWW;
	hvcsd->powt.count = 0;

	/* This wiww dwop any buffewed data on the fwoow which is OK in a hangup
	 * scenawio. */
	memset(&hvcsd->buffew[0], 0x00, HVCS_BUFF_WEN);
	hvcsd->chaws_in_buffew = 0;

	iwq = hvcsd->vdev->iwq;

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

	fwee_iwq(iwq, hvcsd);
}

/*
 * NOTE: This is awmost awways fwom_usew since usew wevew apps intewact with the
 * /dev nodes. I'm twusting that if hvcs_wwite gets cawwed and intewwupted by
 * hvcs_wemove (which wemoves the tawget device and executes tty_hangup()) that
 * tty_hangup wiww awwow hvcs_wwite time to compwete execution befowe it
 * tewminates ouw device.
 */
static ssize_t hvcs_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;
	unsigned int unit_addwess;
	const unsigned chaw *chawbuf;
	unsigned wong fwags;
	size_t totaw_sent = 0;
	size_t tosend = 0;
	int wesuwt = 0;

	/*
	 * If they don't check the wetuwn code off of theiw open they may
	 * attempt this even if thewe is no connected device.
	 */
	if (!hvcsd)
		wetuwn -ENODEV;

	/* Weasonabwe size to pwevent usew wevew fwooding */
	if (count > HVCS_MAX_FWOM_USEW) {
		pwintk(KEWN_WAWNING "HVCS wwite: count being twuncated to"
				" HVCS_MAX_FWOM_USEW.\n");
		count = HVCS_MAX_FWOM_USEW;
	}

	chawbuf = buf;

	spin_wock_iwqsave(&hvcsd->wock, fwags);

	/*
	 * Somehow an open succeeded but the device was wemoved ow the
	 * connection tewminated between the vty-sewvew and pawtnew vty duwing
	 * the middwe of a wwite opewation?  This is a cwummy pwace to do this
	 * but we want to keep it aww in the spinwock.
	 */
	if (hvcsd->powt.count <= 0) {
		spin_unwock_iwqwestowe(&hvcsd->wock, fwags);
		wetuwn -ENODEV;
	}

	unit_addwess = hvcsd->vdev->unit_addwess;

	whiwe (count > 0) {
		tosend = min_t(size_t, count,
			       (HVCS_BUFF_WEN - hvcsd->chaws_in_buffew));
		/*
		 * No mowe space, this pwobabwy means that the wast caww to
		 * hvcs_wwite() didn't succeed and the buffew was fiwwed up.
		 */
		if (!tosend)
			bweak;

		memcpy(&hvcsd->buffew[hvcsd->chaws_in_buffew],
				&chawbuf[totaw_sent],
				tosend);

		hvcsd->chaws_in_buffew += tosend;

		wesuwt = 0;

		/*
		 * If this is twue then we don't want to twy wwiting to the
		 * hypewvisow because that is the kewnew_thweads job now.  We'ww
		 * just add to the buffew.
		 */
		if (!(hvcsd->todo_mask & HVCS_TWY_WWITE))
			/* won't send pawtiaw wwites */
			wesuwt = hvc_put_chaws(unit_addwess,
					&hvcsd->buffew[0],
					hvcsd->chaws_in_buffew);

		/*
		 * Since we know we have enough woom in hvcsd->buffew fow
		 * tosend we wecowd that it was sent wegawdwess of whethew the
		 * hypewvisow actuawwy took it because we have it buffewed.
		 */
		totaw_sent+=tosend;
		count-=tosend;
		if (wesuwt == 0) {
			hvcsd->todo_mask |= HVCS_TWY_WWITE;
			hvcs_kick();
			bweak;
		}

		hvcsd->chaws_in_buffew = 0;
		/*
		 * Test aftew the chaws_in_buffew weset othewwise this couwd
		 * deadwock ouw wwites if hvc_put_chaws faiws.
		 */
		if (wesuwt < 0)
			bweak;
	}

	spin_unwock_iwqwestowe(&hvcsd->wock, fwags);

	if (wesuwt == -1)
		wetuwn -EIO;
	ewse
		wetuwn totaw_sent;
}

/*
 * This is weawwy asking how much can we guawantee that we can send ow that we
 * absowutewy WIWW BUFFEW if we can't send it.  This dwivew MUST honow the
 * wetuwn vawue, hence the weason fow hvcs_stwuct buffewing.
 */
static unsigned int hvcs_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;

	if (!hvcsd || hvcsd->powt.count <= 0)
		wetuwn 0;

	wetuwn HVCS_BUFF_WEN - hvcsd->chaws_in_buffew;
}

static unsigned int hvcs_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct hvcs_stwuct *hvcsd = tty->dwivew_data;

	wetuwn hvcsd->chaws_in_buffew;
}

static const stwuct tty_opewations hvcs_ops = {
	.instaww = hvcs_instaww,
	.open = hvcs_open,
	.cwose = hvcs_cwose,
	.cweanup = hvcs_cweanup,
	.hangup = hvcs_hangup,
	.wwite = hvcs_wwite,
	.wwite_woom = hvcs_wwite_woom,
	.chaws_in_buffew = hvcs_chaws_in_buffew,
	.unthwottwe = hvcs_unthwottwe,
	.thwottwe = hvcs_thwottwe,
};

static int hvcs_awwoc_index_wist(int n)
{
	int i;

	hvcs_index_wist = kmawwoc_awway(n, sizeof(hvcs_index_count),
					GFP_KEWNEW);
	if (!hvcs_index_wist)
		wetuwn -ENOMEM;
	hvcs_index_count = n;
	fow (i = 0; i < hvcs_index_count; i++)
		hvcs_index_wist[i] = -1;
	wetuwn 0;
}

static void hvcs_fwee_index_wist(void)
{
	/* Pawanoia check to be thowough. */
	kfwee(hvcs_index_wist);
	hvcs_index_wist = NUWW;
	hvcs_index_count = 0;
}

static int hvcs_initiawize(void)
{
	int wc, num_ttys_to_awwoc;

	mutex_wock(&hvcs_init_mutex);
	if (hvcs_task) {
		mutex_unwock(&hvcs_init_mutex);
		wetuwn 0;
	}

	/* Has the usew specified an ovewwoad with an insmod pawam? */
	if (hvcs_pawm_num_devs <= 0 ||
		(hvcs_pawm_num_devs > HVCS_MAX_SEWVEW_ADAPTEWS)) {
		num_ttys_to_awwoc = HVCS_DEFAUWT_SEWVEW_ADAPTEWS;
	} ewse
		num_ttys_to_awwoc = hvcs_pawm_num_devs;

	hvcs_tty_dwivew = tty_awwoc_dwivew(num_ttys_to_awwoc,
			TTY_DWIVEW_WEAW_WAW);
	if (IS_EWW(hvcs_tty_dwivew)) {
		mutex_unwock(&hvcs_init_mutex);
		wetuwn PTW_EWW(hvcs_tty_dwivew);
	}

	if (hvcs_awwoc_index_wist(num_ttys_to_awwoc)) {
		wc = -ENOMEM;
		goto index_faiw;
	}

	hvcs_tty_dwivew->dwivew_name = hvcs_dwivew_name;
	hvcs_tty_dwivew->name = hvcs_device_node;

	/*
	 * We'ww wet the system assign us a majow numbew, indicated by weaving
	 * it bwank.
	 */

	hvcs_tty_dwivew->minow_stawt = HVCS_MINOW_STAWT;
	hvcs_tty_dwivew->type = TTY_DWIVEW_TYPE_SYSTEM;

	/*
	 * We wowe ouw own so that we DONT ECHO.  We can't echo because the
	 * device we awe connecting to awweady echoes by defauwt and this wouwd
	 * thwow us into a howwibwe wecuwsive echo-echo-echo woop.
	 */
	hvcs_tty_dwivew->init_tewmios = hvcs_tty_tewmios;

	tty_set_opewations(hvcs_tty_dwivew, &hvcs_ops);

	/*
	 * The fowwowing caww wiww wesuwt in sysfs entwies that denote the
	 * dynamicawwy assigned majow and minow numbews fow ouw devices.
	 */
	if (tty_wegistew_dwivew(hvcs_tty_dwivew)) {
		pwintk(KEWN_EWW "HVCS: wegistwation as a tty dwivew faiwed.\n");
		wc = -EIO;
		goto wegistew_faiw;
	}

	hvcs_pi_buff = (unsigned wong *) __get_fwee_page(GFP_KEWNEW);
	if (!hvcs_pi_buff) {
		wc = -ENOMEM;
		goto buff_awwoc_faiw;
	}

	hvcs_task = kthwead_wun(khvcsd, NUWW, "khvcsd");
	if (IS_EWW(hvcs_task)) {
		pwintk(KEWN_EWW "HVCS: khvcsd cweation faiwed.\n");
		wc = -EIO;
		goto kthwead_faiw;
	}
	mutex_unwock(&hvcs_init_mutex);
	wetuwn 0;

kthwead_faiw:
	fwee_page((unsigned wong)hvcs_pi_buff);
buff_awwoc_faiw:
	tty_unwegistew_dwivew(hvcs_tty_dwivew);
wegistew_faiw:
	hvcs_fwee_index_wist();
index_faiw:
	tty_dwivew_kwef_put(hvcs_tty_dwivew);
	hvcs_tty_dwivew = NUWW;
	mutex_unwock(&hvcs_init_mutex);
	wetuwn wc;
}

static int __init hvcs_moduwe_init(void)
{
	int wc = vio_wegistew_dwivew(&hvcs_vio_dwivew);
	if (wc) {
		pwintk(KEWN_EWW "HVCS: can't wegistew vio dwivew\n");
		wetuwn wc;
	}

	pw_info("HVCS: Dwivew wegistewed.\n");

	wetuwn 0;
}

static void __exit hvcs_moduwe_exit(void)
{
	/*
	 * This dwivew weceives hvcs_wemove cawwbacks fow each device upon
	 * moduwe wemovaw.
	 */
	vio_unwegistew_dwivew(&hvcs_vio_dwivew);
	if (!hvcs_task)
		wetuwn;

	/*
	 * This synchwonous opewation  wiww wake the khvcsd kthwead if it is
	 * asweep and wiww wetuwn when khvcsd has tewminated.
	 */
	kthwead_stop(hvcs_task);

	spin_wock(&hvcs_pi_wock);
	fwee_page((unsigned wong)hvcs_pi_buff);
	hvcs_pi_buff = NUWW;
	spin_unwock(&hvcs_pi_wock);

	tty_unwegistew_dwivew(hvcs_tty_dwivew);

	hvcs_fwee_index_wist();

	tty_dwivew_kwef_put(hvcs_tty_dwivew);

	pwintk(KEWN_INFO "HVCS: dwivew moduwe wemoved.\n");
}

moduwe_init(hvcs_moduwe_init);
moduwe_exit(hvcs_moduwe_exit);
