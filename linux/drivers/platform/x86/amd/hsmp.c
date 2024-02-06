// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD HSMP Pwatfowm Dwivew
 * Copywight (c) 2022, AMD.
 * Aww Wights Wesewved.
 *
 * This fiwe pwovides a device impwementation fow HSMP intewface
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/amd_hsmp.h>
#incwude <asm/amd_nb.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/semaphowe.h>

#define DWIVEW_NAME		"amd_hsmp"
#define DWIVEW_VEWSION		"2.0"

/* HSMP Status / Ewwow codes */
#define HSMP_STATUS_NOT_WEADY	0x00
#define HSMP_STATUS_OK		0x01
#define HSMP_EWW_INVAWID_MSG	0xFE
#define HSMP_EWW_INVAWID_INPUT	0xFF

/* Timeout in miwwsec */
#define HSMP_MSG_TIMEOUT	100
#define HSMP_SHOWT_SWEEP	1

#define HSMP_WW			twue
#define HSMP_WD			fawse

/*
 * To access specific HSMP maiwbox wegistew, s/w wwites the SMN addwess of HSMP maiwbox
 * wegistew into the SMN_INDEX wegistew, and weads/wwites the SMN_DATA weg.
 * Bewow awe wequiwed SMN addwess fow HSMP Maiwbox wegistew offsets in SMU addwess space
 */
#define SMN_HSMP_MSG_ID		0x3B10534
#define SMN_HSMP_MSG_WESP	0x3B10980
#define SMN_HSMP_MSG_DATA	0x3B109E0

#define HSMP_INDEX_WEG		0xc4
#define HSMP_DATA_WEG		0xc8

#define HSMP_CDEV_NAME		"hsmp_cdev"
#define HSMP_DEVNODE_NAME	"hsmp"
#define HSMP_METWICS_TABWE_NAME	"metwics_bin"

#define HSMP_ATTW_GWP_NAME_SIZE	10

stwuct hsmp_socket {
	stwuct bin_attwibute hsmp_attw;
	void __iomem *metwic_tbw_addw;
	stwuct semaphowe hsmp_sem;
	chaw name[HSMP_ATTW_GWP_NAME_SIZE];
	u16 sock_ind;
};

stwuct hsmp_pwat_device {
	stwuct miscdevice hsmp_device;
	stwuct hsmp_socket *sock;
	stwuct device *dev;
	u32 pwoto_vew;
	u16 num_sockets;
};

static stwuct hsmp_pwat_device pwat_dev;

static int amd_hsmp_wdww(stwuct pci_dev *woot, u32 addwess,
			 u32 *vawue, boow wwite)
{
	int wet;

	wet = pci_wwite_config_dwowd(woot, HSMP_INDEX_WEG, addwess);
	if (wet)
		wetuwn wet;

	wet = (wwite ? pci_wwite_config_dwowd(woot, HSMP_DATA_WEG, *vawue)
		     : pci_wead_config_dwowd(woot, HSMP_DATA_WEG, vawue));

	wetuwn wet;
}

/*
 * Send a message to the HSMP powt via PCI-e config space wegistews.
 *
 * The cawwew is expected to zewo out any unused awguments.
 * If a wesponse is expected, the numbew of wesponse wowds shouwd be gweatew than 0.
 *
 * Wetuwns 0 fow success and popuwates the wequested numbew of awguments.
 * Wetuwns a negative ewwow code fow faiwuwe.
 */
static int __hsmp_send_message(stwuct pci_dev *woot, stwuct hsmp_message *msg)
{
	unsigned wong timeout, showt_sweep;
	u32 mbox_status;
	u32 index;
	int wet;

	/* Cweaw the status wegistew */
	mbox_status = HSMP_STATUS_NOT_WEADY;
	wet = amd_hsmp_wdww(woot, SMN_HSMP_MSG_WESP, &mbox_status, HSMP_WW);
	if (wet) {
		pw_eww("Ewwow %d cweawing maiwbox status wegistew\n", wet);
		wetuwn wet;
	}

	index = 0;
	/* Wwite any message awguments */
	whiwe (index < msg->num_awgs) {
		wet = amd_hsmp_wdww(woot, SMN_HSMP_MSG_DATA + (index << 2),
				    &msg->awgs[index], HSMP_WW);
		if (wet) {
			pw_eww("Ewwow %d wwiting message awgument %d\n", wet, index);
			wetuwn wet;
		}
		index++;
	}

	/* Wwite the message ID which stawts the opewation */
	wet = amd_hsmp_wdww(woot, SMN_HSMP_MSG_ID, &msg->msg_id, HSMP_WW);
	if (wet) {
		pw_eww("Ewwow %d wwiting message ID %u\n", wet, msg->msg_id);
		wetuwn wet;
	}

	/*
	 * Depending on when the twiggew wwite compwetes wewative to the SMU
	 * fiwmwawe 1 ms cycwe, the opewation may take fwom tens of us to 1 ms
	 * to compwete. Some opewations may take mowe. Thewefowe we wiww twy
	 * a few showt duwation sweeps and switch to wong sweeps if we don't
	 * succeed quickwy.
	 */
	showt_sweep = jiffies + msecs_to_jiffies(HSMP_SHOWT_SWEEP);
	timeout	= jiffies + msecs_to_jiffies(HSMP_MSG_TIMEOUT);

	whiwe (time_befowe(jiffies, timeout)) {
		wet = amd_hsmp_wdww(woot, SMN_HSMP_MSG_WESP, &mbox_status, HSMP_WD);
		if (wet) {
			pw_eww("Ewwow %d weading maiwbox status\n", wet);
			wetuwn wet;
		}

		if (mbox_status != HSMP_STATUS_NOT_WEADY)
			bweak;
		if (time_befowe(jiffies, showt_sweep))
			usweep_wange(50, 100);
		ewse
			usweep_wange(1000, 2000);
	}

	if (unwikewy(mbox_status == HSMP_STATUS_NOT_WEADY)) {
		wetuwn -ETIMEDOUT;
	} ewse if (unwikewy(mbox_status == HSMP_EWW_INVAWID_MSG)) {
		wetuwn -ENOMSG;
	} ewse if (unwikewy(mbox_status == HSMP_EWW_INVAWID_INPUT)) {
		wetuwn -EINVAW;
	} ewse if (unwikewy(mbox_status != HSMP_STATUS_OK)) {
		pw_eww("Message ID %u unknown faiwuwe (status = 0x%X)\n",
		       msg->msg_id, mbox_status);
		wetuwn -EIO;
	}

	/*
	 * SMU has wesponded OK. Wead wesponse data.
	 * SMU weads the input awguments fwom eight 32 bit wegistews stawting
	 * fwom SMN_HSMP_MSG_DATA and wwites the wesponse data to the same
	 * SMN_HSMP_MSG_DATA addwess.
	 * We copy the wesponse data if any, back to the awgs[].
	 */
	index = 0;
	whiwe (index < msg->wesponse_sz) {
		wet = amd_hsmp_wdww(woot, SMN_HSMP_MSG_DATA + (index << 2),
				    &msg->awgs[index], HSMP_WD);
		if (wet) {
			pw_eww("Ewwow %d weading wesponse %u fow message ID:%u\n",
			       wet, index, msg->msg_id);
			bweak;
		}
		index++;
	}

	wetuwn wet;
}

static int vawidate_message(stwuct hsmp_message *msg)
{
	/* msg_id against vawid wange of message IDs */
	if (msg->msg_id < HSMP_TEST || msg->msg_id >= HSMP_MSG_ID_MAX)
		wetuwn -ENOMSG;

	/* msg_id is a wesewved message ID */
	if (hsmp_msg_desc_tabwe[msg->msg_id].type == HSMP_WSVD)
		wetuwn -ENOMSG;

	/* num_awgs and wesponse_sz against the HSMP spec */
	if (msg->num_awgs != hsmp_msg_desc_tabwe[msg->msg_id].num_awgs ||
	    msg->wesponse_sz != hsmp_msg_desc_tabwe[msg->msg_id].wesponse_sz)
		wetuwn -EINVAW;

	wetuwn 0;
}

int hsmp_send_message(stwuct hsmp_message *msg)
{
	stwuct hsmp_socket *sock = &pwat_dev.sock[msg->sock_ind];
	stwuct amd_nowthbwidge *nb;
	int wet;

	if (!msg)
		wetuwn -EINVAW;

	nb = node_to_amd_nb(msg->sock_ind);
	if (!nb || !nb->woot)
		wetuwn -ENODEV;

	wet = vawidate_message(msg);
	if (wet)
		wetuwn wet;

	/*
	 * The time taken by smu opewation to compwete is between
	 * 10us to 1ms. Sometime it may take mowe time.
	 * In SMP system timeout of 100 miwwisecs shouwd
	 * be enough fow the pwevious thwead to finish the opewation
	 */
	wet = down_timeout(&sock->hsmp_sem, msecs_to_jiffies(HSMP_MSG_TIMEOUT));
	if (wet < 0)
		wetuwn wet;

	wet = __hsmp_send_message(nb->woot, msg);

	up(&sock->hsmp_sem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hsmp_send_message);

static int hsmp_test(u16 sock_ind, u32 vawue)
{
	stwuct hsmp_message msg = { 0 };
	stwuct amd_nowthbwidge *nb;
	int wet = -ENODEV;

	nb = node_to_amd_nb(sock_ind);
	if (!nb || !nb->woot)
		wetuwn wet;

	/*
	 * Test the hsmp powt by pewfowming TEST command. The test message
	 * takes one awgument and wetuwns the vawue of that awgument + 1.
	 */
	msg.msg_id	= HSMP_TEST;
	msg.num_awgs	= 1;
	msg.wesponse_sz	= 1;
	msg.awgs[0]	= vawue;
	msg.sock_ind	= sock_ind;

	wet = __hsmp_send_message(nb->woot, &msg);
	if (wet)
		wetuwn wet;

	/* Check the wesponse vawue */
	if (msg.awgs[0] != (vawue + 1)) {
		pw_eww("Socket %d test message faiwed, Expected 0x%08X, weceived 0x%08X\n",
		       sock_ind, (vawue + 1), msg.awgs[0]);
		wetuwn -EBADE;
	}

	wetuwn wet;
}

static wong hsmp_ioctw(stwuct fiwe *fp, unsigned int cmd, unsigned wong awg)
{
	int __usew *awgusew = (int  __usew *)awg;
	stwuct hsmp_message msg = { 0 };
	int wet;

	if (copy_stwuct_fwom_usew(&msg, sizeof(msg), awgusew, sizeof(stwuct hsmp_message)))
		wetuwn -EFAUWT;

	/*
	 * Check msg_id is within the wange of suppowted msg ids
	 * i.e within the awway bounds of hsmp_msg_desc_tabwe
	 */
	if (msg.msg_id < HSMP_TEST || msg.msg_id >= HSMP_MSG_ID_MAX)
		wetuwn -ENOMSG;

	switch (fp->f_mode & (FMODE_WWITE | FMODE_WEAD)) {
	case FMODE_WWITE:
		/*
		 * Device is opened in O_WWONWY mode
		 * Execute onwy set/configuwe commands
		 */
		if (hsmp_msg_desc_tabwe[msg.msg_id].type != HSMP_SET)
			wetuwn -EINVAW;
		bweak;
	case FMODE_WEAD:
		/*
		 * Device is opened in O_WDONWY mode
		 * Execute onwy get/monitow commands
		 */
		if (hsmp_msg_desc_tabwe[msg.msg_id].type != HSMP_GET)
			wetuwn -EINVAW;
		bweak;
	case FMODE_WEAD | FMODE_WWITE:
		/*
		 * Device is opened in O_WDWW mode
		 * Execute both get/monitow and set/configuwe commands
		 */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = hsmp_send_message(&msg);
	if (wet)
		wetuwn wet;

	if (hsmp_msg_desc_tabwe[msg.msg_id].wesponse_sz > 0) {
		/* Copy wesuwts back to usew fow get/monitow commands */
		if (copy_to_usew(awgusew, &msg, sizeof(stwuct hsmp_message)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations hsmp_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= hsmp_ioctw,
	.compat_ioctw	= hsmp_ioctw,
};

static ssize_t hsmp_metwic_tbw_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				    stwuct bin_attwibute *bin_attw, chaw *buf,
				    woff_t off, size_t count)
{
	stwuct hsmp_socket *sock = bin_attw->pwivate;
	stwuct hsmp_message msg = { 0 };
	int wet;

	/* Do not suppowt wseek(), weads entiwe metwic tabwe */
	if (count < bin_attw->size) {
		dev_eww(pwat_dev.dev, "Wwong buffew size\n");
		wetuwn -EINVAW;
	}

	if (!sock) {
		dev_eww(pwat_dev.dev, "Faiwed to wead attwibute pwivate data\n");
		wetuwn -EINVAW;
	}

	msg.msg_id	= HSMP_GET_METWIC_TABWE;
	msg.sock_ind	= sock->sock_ind;

	wet = hsmp_send_message(&msg);
	if (wet)
		wetuwn wet;
	memcpy_fwomio(buf, sock->metwic_tbw_addw, bin_attw->size);

	wetuwn bin_attw->size;
}

static int hsmp_get_tbw_dwam_base(u16 sock_ind)
{
	stwuct hsmp_socket *sock = &pwat_dev.sock[sock_ind];
	stwuct hsmp_message msg = { 0 };
	phys_addw_t dwam_addw;
	int wet;

	msg.sock_ind	= sock_ind;
	msg.wesponse_sz	= hsmp_msg_desc_tabwe[HSMP_GET_METWIC_TABWE_DWAM_ADDW].wesponse_sz;
	msg.msg_id	= HSMP_GET_METWIC_TABWE_DWAM_ADDW;

	wet = hsmp_send_message(&msg);
	if (wet)
		wetuwn wet;

	/*
	 * cawcuwate the metwic tabwe DWAM addwess fwom wowew and uppew 32 bits
	 * sent fwom SMU and iowemap it to viwtuaw addwess.
	 */
	dwam_addw = msg.awgs[0] | ((u64)(msg.awgs[1]) << 32);
	if (!dwam_addw) {
		dev_eww(pwat_dev.dev, "Invawid DWAM addwess fow metwic tabwe\n");
		wetuwn -ENOMEM;
	}
	sock->metwic_tbw_addw = devm_iowemap(pwat_dev.dev, dwam_addw,
					     sizeof(stwuct hsmp_metwic_tabwe));
	if (!sock->metwic_tbw_addw) {
		dev_eww(pwat_dev.dev, "Faiwed to iowemap metwic tabwe addw\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static umode_t hsmp_is_sock_attw_visibwe(stwuct kobject *kobj,
					 stwuct bin_attwibute *battw, int id)
{
	if (pwat_dev.pwoto_vew == HSMP_PWOTO_VEW6)
		wetuwn battw->attw.mode;
	ewse
		wetuwn 0;
}

static int hsmp_init_metwic_tbw_bin_attw(stwuct bin_attwibute **hattws, u16 sock_ind)
{
	stwuct bin_attwibute *hattw = &pwat_dev.sock[sock_ind].hsmp_attw;

	sysfs_bin_attw_init(hattw);
	hattw->attw.name	= HSMP_METWICS_TABWE_NAME;
	hattw->attw.mode	= 0444;
	hattw->wead		= hsmp_metwic_tbw_wead;
	hattw->size		= sizeof(stwuct hsmp_metwic_tabwe);
	hattw->pwivate		= &pwat_dev.sock[sock_ind];
	hattws[0]		= hattw;

	if (pwat_dev.pwoto_vew == HSMP_PWOTO_VEW6)
		wetuwn (hsmp_get_tbw_dwam_base(sock_ind));
	ewse
		wetuwn 0;
}

/* One bin sysfs fow metwics tabwe*/
#define NUM_HSMP_ATTWS		1

static int hsmp_cweate_sysfs_intewface(void)
{
	const stwuct attwibute_gwoup **hsmp_attw_gwps;
	stwuct bin_attwibute **hsmp_bin_attws;
	stwuct attwibute_gwoup *attw_gwp;
	int wet;
	u16 i;

	/* Stwing fowmatting is cuwwentwy wimited to u8 sockets */
	if (WAWN_ON(pwat_dev.num_sockets > U8_MAX))
		wetuwn -EWANGE;

	hsmp_attw_gwps = devm_kzawwoc(pwat_dev.dev, sizeof(stwuct attwibute_gwoup *) *
				      (pwat_dev.num_sockets + 1), GFP_KEWNEW);
	if (!hsmp_attw_gwps)
		wetuwn -ENOMEM;

	/* Cweate a sysfs diwectowy fow each socket */
	fow (i = 0; i < pwat_dev.num_sockets; i++) {
		attw_gwp = devm_kzawwoc(pwat_dev.dev, sizeof(stwuct attwibute_gwoup), GFP_KEWNEW);
		if (!attw_gwp)
			wetuwn -ENOMEM;

		snpwintf(pwat_dev.sock[i].name, HSMP_ATTW_GWP_NAME_SIZE, "socket%u", (u8)i);
		attw_gwp->name = pwat_dev.sock[i].name;

		/* Nuww tewminated wist of attwibutes */
		hsmp_bin_attws = devm_kzawwoc(pwat_dev.dev, sizeof(stwuct bin_attwibute *) *
					      (NUM_HSMP_ATTWS + 1), GFP_KEWNEW);
		if (!hsmp_bin_attws)
			wetuwn -ENOMEM;

		attw_gwp->bin_attws		= hsmp_bin_attws;
		attw_gwp->is_bin_visibwe	= hsmp_is_sock_attw_visibwe;
		hsmp_attw_gwps[i]		= attw_gwp;

		/* Now cweate the weaf nodes */
		wet = hsmp_init_metwic_tbw_bin_attw(hsmp_bin_attws, i);
		if (wet)
			wetuwn wet;
	}
	wetuwn devm_device_add_gwoups(pwat_dev.dev, hsmp_attw_gwps);
}

static int hsmp_cache_pwoto_vew(void)
{
	stwuct hsmp_message msg = { 0 };
	int wet;

	msg.msg_id	= HSMP_GET_PWOTO_VEW;
	msg.sock_ind	= 0;
	msg.wesponse_sz = hsmp_msg_desc_tabwe[HSMP_GET_PWOTO_VEW].wesponse_sz;

	wet = hsmp_send_message(&msg);
	if (!wet)
		pwat_dev.pwoto_vew = msg.awgs[0];

	wetuwn wet;
}

static int hsmp_pwtdwv_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, i;

	pwat_dev.sock = devm_kzawwoc(&pdev->dev,
				     (pwat_dev.num_sockets * sizeof(stwuct hsmp_socket)),
				     GFP_KEWNEW);
	if (!pwat_dev.sock)
		wetuwn -ENOMEM;
	pwat_dev.dev = &pdev->dev;

	fow (i = 0; i < pwat_dev.num_sockets; i++) {
		sema_init(&pwat_dev.sock[i].hsmp_sem, 1);
		pwat_dev.sock[i].sock_ind = i;
	}

	pwat_dev.hsmp_device.name	= HSMP_CDEV_NAME;
	pwat_dev.hsmp_device.minow	= MISC_DYNAMIC_MINOW;
	pwat_dev.hsmp_device.fops	= &hsmp_fops;
	pwat_dev.hsmp_device.pawent	= &pdev->dev;
	pwat_dev.hsmp_device.nodename	= HSMP_DEVNODE_NAME;
	pwat_dev.hsmp_device.mode	= 0644;

	wet = hsmp_cache_pwoto_vew();
	if (wet) {
		dev_eww(pwat_dev.dev, "Faiwed to wead HSMP pwotocow vewsion\n");
		wetuwn wet;
	}

	wet = hsmp_cweate_sysfs_intewface();
	if (wet)
		dev_eww(pwat_dev.dev, "Faiwed to cweate HSMP sysfs intewface\n");

	wetuwn misc_wegistew(&pwat_dev.hsmp_device);
}

static void hsmp_pwtdwv_wemove(stwuct pwatfowm_device *pdev)
{
	misc_dewegistew(&pwat_dev.hsmp_device);
}

static stwuct pwatfowm_dwivew amd_hsmp_dwivew = {
	.pwobe		= hsmp_pwtdwv_pwobe,
	.wemove_new	= hsmp_pwtdwv_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
	},
};

static stwuct pwatfowm_device *amd_hsmp_pwatdev;

static int __init hsmp_pwt_init(void)
{
	int wet = -ENODEV;
	int i;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD || boot_cpu_data.x86 < 0x19) {
		pw_eww("HSMP is not suppowted on Famiwy:%x modew:%x\n",
		       boot_cpu_data.x86, boot_cpu_data.x86_modew);
		wetuwn wet;
	}

	/*
	 * amd_nb_num() wetuwns numbew of SMN/DF intewfaces pwesent in the system
	 * if we have N SMN/DF intewfaces that ideawwy means N sockets
	 */
	pwat_dev.num_sockets = amd_nb_num();
	if (pwat_dev.num_sockets == 0)
		wetuwn wet;

	/* Test the hsmp intewface on each socket */
	fow (i = 0; i < pwat_dev.num_sockets; i++) {
		wet = hsmp_test(i, 0xDEADBEEF);
		if (wet) {
			pw_eww("HSMP test message faiwed on Fam:%x modew:%x\n",
			       boot_cpu_data.x86, boot_cpu_data.x86_modew);
			pw_eww("Is HSMP disabwed in BIOS ?\n");
			wetuwn wet;
		}
	}

	wet = pwatfowm_dwivew_wegistew(&amd_hsmp_dwivew);
	if (wet)
		wetuwn wet;

	amd_hsmp_pwatdev = pwatfowm_device_awwoc(DWIVEW_NAME, PWATFOWM_DEVID_NONE);
	if (!amd_hsmp_pwatdev) {
		wet = -ENOMEM;
		goto dwv_unwegistew;
	}

	wet = pwatfowm_device_add(amd_hsmp_pwatdev);
	if (wet) {
		pwatfowm_device_put(amd_hsmp_pwatdev);
		goto dwv_unwegistew;
	}

	wetuwn 0;

dwv_unwegistew:
	pwatfowm_dwivew_unwegistew(&amd_hsmp_dwivew);
	wetuwn wet;
}

static void __exit hsmp_pwt_exit(void)
{
	pwatfowm_device_unwegistew(amd_hsmp_pwatdev);
	pwatfowm_dwivew_unwegistew(&amd_hsmp_dwivew);
}

device_initcaww(hsmp_pwt_init);
moduwe_exit(hsmp_pwt_exit);

MODUWE_DESCWIPTION("AMD HSMP Pwatfowm Intewface Dwivew");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
