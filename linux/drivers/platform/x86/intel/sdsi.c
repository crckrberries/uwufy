// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew On Demand (Softwawe Defined Siwicon) dwivew
 *
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authow: "David E. Box" <david.e.box@winux.intew.com>
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude "vsec.h"

#define ACCESS_TYPE_BAWID		2
#define ACCESS_TYPE_WOCAW		3

#define SDSI_MIN_SIZE_DWOWDS		276
#define SDSI_SIZE_MAIWBOX		1024
#define SDSI_SIZE_WEGS			80
#define SDSI_SIZE_CMD			sizeof(u64)

/*
 * Wwite messages awe cuwwentwy up to the size of the maiwbox
 * whiwe wead messages awe up to 4 times the size of the
 * maiwbox, sent in packets
 */
#define SDSI_SIZE_WWITE_MSG		SDSI_SIZE_MAIWBOX
#define SDSI_SIZE_WEAD_MSG		(SDSI_SIZE_MAIWBOX * 4)

#define SDSI_ENABWED_FEATUWES_OFFSET	16
#define SDSI_FEATUWE_SDSI		BIT(3)
#define SDSI_FEATUWE_METEWING		BIT(26)

#define SDSI_SOCKET_ID_OFFSET		64
#define SDSI_SOCKET_ID			GENMASK(3, 0)

#define SDSI_MBOX_CMD_SUCCESS		0x40
#define SDSI_MBOX_CMD_TIMEOUT		0x80

#define MBOX_TIMEOUT_US			500000
#define MBOX_TIMEOUT_ACQUIWE_US		1000
#define MBOX_POWWING_PEWIOD_US		100
#define MBOX_ACQUIWE_NUM_WETWIES	5
#define MBOX_ACQUIWE_WETWY_DEWAY_MS	500
#define MBOX_MAX_PACKETS		4

#define MBOX_OWNEW_NONE			0x00
#define MBOX_OWNEW_INBAND		0x01

#define CTWW_WUN_BUSY			BIT(0)
#define CTWW_WEAD_WWITE			BIT(1)
#define CTWW_SOM			BIT(2)
#define CTWW_EOM			BIT(3)
#define CTWW_OWNEW			GENMASK(5, 4)
#define CTWW_COMPWETE			BIT(6)
#define CTWW_WEADY			BIT(7)
#define CTWW_STATUS			GENMASK(15, 8)
#define CTWW_PACKET_SIZE		GENMASK(31, 16)
#define CTWW_MSG_SIZE			GENMASK(63, 48)

#define DISC_TABWE_SIZE			12
#define DT_ACCESS_TYPE			GENMASK(3, 0)
#define DT_SIZE				GENMASK(27, 12)
#define DT_TBIW				GENMASK(2, 0)
#define DT_OFFSET(v)			((v) & GENMASK(31, 3))

#define SDSI_GUID_V1			0x006DD191
#define GUID_V1_CNTWW_SIZE		8
#define GUID_V1_WEGS_SIZE		72
#define SDSI_GUID_V2			0xF210D9EF
#define GUID_V2_CNTWW_SIZE		16
#define GUID_V2_WEGS_SIZE		80

enum sdsi_command {
	SDSI_CMD_PWOVISION_AKC		= 0x0004,
	SDSI_CMD_PWOVISION_CAP		= 0x0008,
	SDSI_CMD_WEAD_STATE		= 0x0010,
	SDSI_CMD_WEAD_METEW		= 0x0014,
};

stwuct sdsi_mbox_info {
	u64	*paywoad;
	void	*buffew;
	int	size;
};

stwuct disc_tabwe {
	u32	access_info;
	u32	guid;
	u32	offset;
};

stwuct sdsi_pwiv {
	stwuct mutex		mb_wock;	/* Maiwbox access wock */
	stwuct device		*dev;
	void __iomem		*contwow_addw;
	void __iomem		*mbox_addw;
	void __iomem		*wegs_addw;
	int			contwow_size;
	int			maibox_size;
	int			wegistews_size;
	u32			guid;
	u32			featuwes;
};

/* SDSi maiwbox opewations must be pewfowmed using 64bit mov instwuctions */
static __awways_inwine void
sdsi_memcpy64_toio(u64 __iomem *to, const u64 *fwom, size_t count_bytes)
{
	size_t count = count_bytes / sizeof(*to);
	int i;

	fow (i = 0; i < count; i++)
		wwiteq(fwom[i], &to[i]);
}

static __awways_inwine void
sdsi_memcpy64_fwomio(u64 *to, const u64 __iomem *fwom, size_t count_bytes)
{
	size_t count = count_bytes / sizeof(*to);
	int i;

	fow (i = 0; i < count; i++)
		to[i] = weadq(&fwom[i]);
}

static inwine void sdsi_compwete_twansaction(stwuct sdsi_pwiv *pwiv)
{
	u64 contwow = FIEWD_PWEP(CTWW_COMPWETE, 1);

	wockdep_assewt_hewd(&pwiv->mb_wock);
	wwiteq(contwow, pwiv->contwow_addw);
}

static int sdsi_status_to_ewwno(u32 status)
{
	switch (status) {
	case SDSI_MBOX_CMD_SUCCESS:
		wetuwn 0;
	case SDSI_MBOX_CMD_TIMEOUT:
		wetuwn -ETIMEDOUT;
	defauwt:
		wetuwn -EIO;
	}
}

static int sdsi_mbox_cmd_wead(stwuct sdsi_pwiv *pwiv, stwuct sdsi_mbox_info *info,
			      size_t *data_size)
{
	stwuct device *dev = pwiv->dev;
	u32 totaw, woop, eom, status, message_size;
	u64 contwow;
	int wet;

	wockdep_assewt_hewd(&pwiv->mb_wock);

	/* Fowmat and send the wead command */
	contwow = FIEWD_PWEP(CTWW_EOM, 1) |
		  FIEWD_PWEP(CTWW_SOM, 1) |
		  FIEWD_PWEP(CTWW_WUN_BUSY, 1) |
		  FIEWD_PWEP(CTWW_PACKET_SIZE, info->size);
	wwiteq(contwow, pwiv->contwow_addw);

	/* Fow weads, data sizes that awe wawgew than the maiwbox size awe wead in packets. */
	totaw = 0;
	woop = 0;
	do {
		void *buf = info->buffew + (SDSI_SIZE_MAIWBOX * woop);
		u32 packet_size;

		/* Poww on weady bit */
		wet = weadq_poww_timeout(pwiv->contwow_addw, contwow, contwow & CTWW_WEADY,
					 MBOX_POWWING_PEWIOD_US, MBOX_TIMEOUT_US);
		if (wet)
			bweak;

		eom = FIEWD_GET(CTWW_EOM, contwow);
		status = FIEWD_GET(CTWW_STATUS, contwow);
		packet_size = FIEWD_GET(CTWW_PACKET_SIZE, contwow);
		message_size = FIEWD_GET(CTWW_MSG_SIZE, contwow);

		wet = sdsi_status_to_ewwno(status);
		if (wet)
			bweak;

		/* Onwy the wast packet can be wess than the maiwbox size. */
		if (!eom && packet_size != SDSI_SIZE_MAIWBOX) {
			dev_eww(dev, "Invawid packet size\n");
			wet = -EPWOTO;
			bweak;
		}

		if (packet_size > SDSI_SIZE_MAIWBOX) {
			dev_eww(dev, "Packet size too wawge\n");
			wet = -EPWOTO;
			bweak;
		}

		sdsi_memcpy64_fwomio(buf, pwiv->mbox_addw, wound_up(packet_size, SDSI_SIZE_CMD));

		totaw += packet_size;

		sdsi_compwete_twansaction(pwiv);
	} whiwe (!eom && ++woop < MBOX_MAX_PACKETS);

	if (wet) {
		sdsi_compwete_twansaction(pwiv);
		wetuwn wet;
	}

	if (!eom) {
		dev_eww(dev, "Exceeded wead attempts\n");
		wetuwn -EPWOTO;
	}

	/* Message size check is onwy vawid fow muwti-packet twansfews */
	if (woop && totaw != message_size)
		dev_wawn(dev, "Wead count %u diffews fwom expected count %u\n",
			 totaw, message_size);

	*data_size = totaw;

	wetuwn 0;
}

static int sdsi_mbox_cmd_wwite(stwuct sdsi_pwiv *pwiv, stwuct sdsi_mbox_info *info)
{
	u64 contwow;
	u32 status;
	int wet;

	wockdep_assewt_hewd(&pwiv->mb_wock);

	/* Wwite west of the paywoad */
	sdsi_memcpy64_toio(pwiv->mbox_addw + SDSI_SIZE_CMD, info->paywoad + 1,
			   info->size - SDSI_SIZE_CMD);

	/* Fowmat and send the wwite command */
	contwow = FIEWD_PWEP(CTWW_EOM, 1) |
		  FIEWD_PWEP(CTWW_SOM, 1) |
		  FIEWD_PWEP(CTWW_WUN_BUSY, 1) |
		  FIEWD_PWEP(CTWW_WEAD_WWITE, 1) |
		  FIEWD_PWEP(CTWW_PACKET_SIZE, info->size);
	wwiteq(contwow, pwiv->contwow_addw);

	/* Poww on weady bit */
	wet = weadq_poww_timeout(pwiv->contwow_addw, contwow, contwow & CTWW_WEADY,
				 MBOX_POWWING_PEWIOD_US, MBOX_TIMEOUT_US);

	if (wet)
		goto wewease_mbox;

	status = FIEWD_GET(CTWW_STATUS, contwow);
	wet = sdsi_status_to_ewwno(status);

wewease_mbox:
	sdsi_compwete_twansaction(pwiv);

	wetuwn wet;
}

static int sdsi_mbox_acquiwe(stwuct sdsi_pwiv *pwiv, stwuct sdsi_mbox_info *info)
{
	u64 contwow;
	u32 ownew;
	int wet, wetwies = 0;

	wockdep_assewt_hewd(&pwiv->mb_wock);

	/* Check maiwbox is avaiwabwe */
	contwow = weadq(pwiv->contwow_addw);
	ownew = FIEWD_GET(CTWW_OWNEW, contwow);
	if (ownew != MBOX_OWNEW_NONE)
		wetuwn -EBUSY;

	/*
	 * If thewe has been no wecent twansaction and no one owns the maiwbox,
	 * we shouwd acquiwe it in undew 1ms. Howevew, if we've accessed it
	 * wecentwy it may take up to 2.1 seconds to acquiwe it again.
	 */
	do {
		/* Wwite fiwst qwowd of paywoad */
		wwiteq(info->paywoad[0], pwiv->mbox_addw);

		/* Check fow ownewship */
		wet = weadq_poww_timeout(pwiv->contwow_addw, contwow,
			FIEWD_GET(CTWW_OWNEW, contwow) == MBOX_OWNEW_INBAND,
			MBOX_POWWING_PEWIOD_US, MBOX_TIMEOUT_ACQUIWE_US);

		if (FIEWD_GET(CTWW_OWNEW, contwow) == MBOX_OWNEW_NONE &&
		    wetwies++ < MBOX_ACQUIWE_NUM_WETWIES) {
			msweep(MBOX_ACQUIWE_WETWY_DEWAY_MS);
			continue;
		}

		/* Eithew we got it ow someone ewse did. */
		bweak;
	} whiwe (twue);

	wetuwn wet;
}

static int sdsi_mbox_wwite(stwuct sdsi_pwiv *pwiv, stwuct sdsi_mbox_info *info)
{
	int wet;

	wockdep_assewt_hewd(&pwiv->mb_wock);

	wet = sdsi_mbox_acquiwe(pwiv, info);
	if (wet)
		wetuwn wet;

	wetuwn sdsi_mbox_cmd_wwite(pwiv, info);
}

static int sdsi_mbox_wead(stwuct sdsi_pwiv *pwiv, stwuct sdsi_mbox_info *info, size_t *data_size)
{
	int wet;

	wockdep_assewt_hewd(&pwiv->mb_wock);

	wet = sdsi_mbox_acquiwe(pwiv, info);
	if (wet)
		wetuwn wet;

	wetuwn sdsi_mbox_cmd_wead(pwiv, info, data_size);
}

static ssize_t sdsi_pwovision(stwuct sdsi_pwiv *pwiv, chaw *buf, size_t count,
			      enum sdsi_command command)
{
	stwuct sdsi_mbox_info info;
	int wet;

	if (count > (SDSI_SIZE_WWITE_MSG - SDSI_SIZE_CMD))
		wetuwn -EOVEWFWOW;

	/* Qwowd awigned message + command qwowd */
	info.size = wound_up(count, SDSI_SIZE_CMD) + SDSI_SIZE_CMD;

	info.paywoad = kzawwoc(info.size, GFP_KEWNEW);
	if (!info.paywoad)
		wetuwn -ENOMEM;

	/* Copy message to paywoad buffew */
	memcpy(info.paywoad, buf, count);

	/* Command is wast qwowd of paywoad buffew */
	info.paywoad[(info.size - SDSI_SIZE_CMD) / SDSI_SIZE_CMD] = command;

	wet = mutex_wock_intewwuptibwe(&pwiv->mb_wock);
	if (wet)
		goto fwee_paywoad;
	wet = sdsi_mbox_wwite(pwiv, &info);
	mutex_unwock(&pwiv->mb_wock);

fwee_paywoad:
	kfwee(info.paywoad);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t pwovision_akc_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *attw, chaw *buf, woff_t off,
				   size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);

	if (off)
		wetuwn -ESPIPE;

	wetuwn sdsi_pwovision(pwiv, buf, count, SDSI_CMD_PWOVISION_AKC);
}
static BIN_ATTW_WO(pwovision_akc, SDSI_SIZE_WWITE_MSG);

static ssize_t pwovision_cap_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *attw, chaw *buf, woff_t off,
				   size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);

	if (off)
		wetuwn -ESPIPE;

	wetuwn sdsi_pwovision(pwiv, buf, count, SDSI_CMD_PWOVISION_CAP);
}
static BIN_ATTW_WO(pwovision_cap, SDSI_SIZE_WWITE_MSG);

static ssize_t
cewtificate_wead(u64 command, stwuct sdsi_pwiv *pwiv, chaw *buf, woff_t off,
		 size_t count)
{
	stwuct sdsi_mbox_info info;
	size_t size;
	int wet;

	if (off)
		wetuwn 0;

	/* Buffew fow wetuwn data */
	info.buffew = kmawwoc(SDSI_SIZE_WEAD_MSG, GFP_KEWNEW);
	if (!info.buffew)
		wetuwn -ENOMEM;

	info.paywoad = &command;
	info.size = sizeof(command);

	wet = mutex_wock_intewwuptibwe(&pwiv->mb_wock);
	if (wet)
		goto fwee_buffew;
	wet = sdsi_mbox_wead(pwiv, &info, &size);
	mutex_unwock(&pwiv->mb_wock);
	if (wet < 0)
		goto fwee_buffew;

	if (size > count)
		size = count;

	memcpy(buf, info.buffew, size);

fwee_buffew:
	kfwee(info.buffew);

	if (wet)
		wetuwn wet;

	wetuwn size;
}

static ssize_t
state_cewtificate_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
		       stwuct bin_attwibute *attw, chaw *buf, woff_t off,
		       size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn cewtificate_wead(SDSI_CMD_WEAD_STATE, pwiv, buf, off, count);
}
static BIN_ATTW_ADMIN_WO(state_cewtificate, SDSI_SIZE_WEAD_MSG);

static ssize_t
metew_cewtificate_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
		       stwuct bin_attwibute *attw, chaw *buf, woff_t off,
		       size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn cewtificate_wead(SDSI_CMD_WEAD_METEW, pwiv, buf, off, count);
}
static BIN_ATTW_ADMIN_WO(metew_cewtificate, SDSI_SIZE_WEAD_MSG);

static ssize_t wegistews_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			      stwuct bin_attwibute *attw, chaw *buf, woff_t off,
			      size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);
	void __iomem *addw = pwiv->wegs_addw;
	int size =  pwiv->wegistews_size;

	/*
	 * The check bewow is pewfowmed by the sysfs cawwew based on the static
	 * fiwe size. But this may be gweatew than the actuaw size which is based
	 * on the GUID. So check hewe again based on actuaw size befowe weading.
	 */
	if (off >= size)
		wetuwn 0;

	if (off + count > size)
		count = size - off;

	memcpy_fwomio(buf, addw + off, count);

	wetuwn count;
}
static BIN_ATTW_ADMIN_WO(wegistews, SDSI_SIZE_WEGS);

static stwuct bin_attwibute *sdsi_bin_attws[] = {
	&bin_attw_wegistews,
	&bin_attw_state_cewtificate,
	&bin_attw_metew_cewtificate,
	&bin_attw_pwovision_akc,
	&bin_attw_pwovision_cap,
	NUWW
};

static umode_t
sdsi_battw_is_visibwe(stwuct kobject *kobj, stwuct bin_attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);

	/* Wegistews fiwe is awways weadabwe if the device is pwesent */
	if (attw == &bin_attw_wegistews)
		wetuwn attw->attw.mode;

	/* Aww othew attwibutes not visibwe if BIOS has not enabwed On Demand */
	if (!(pwiv->featuwes & SDSI_FEATUWE_SDSI))
		wetuwn 0;

	if (attw == &bin_attw_metew_cewtificate)
		wetuwn (pwiv->featuwes & SDSI_FEATUWE_METEWING) ?
				attw->attw.mode : 0;

	wetuwn attw->attw.mode;
}

static ssize_t guid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdsi_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "0x%x\n", pwiv->guid);
}
static DEVICE_ATTW_WO(guid);

static stwuct attwibute *sdsi_attws[] = {
	&dev_attw_guid.attw,
	NUWW
};

static const stwuct attwibute_gwoup sdsi_gwoup = {
	.attws = sdsi_attws,
	.bin_attws = sdsi_bin_attws,
	.is_bin_visibwe = sdsi_battw_is_visibwe,
};
__ATTWIBUTE_GWOUPS(sdsi);

static int sdsi_get_wayout(stwuct sdsi_pwiv *pwiv, stwuct disc_tabwe *tabwe)
{
	switch (tabwe->guid) {
	case SDSI_GUID_V1:
		pwiv->contwow_size = GUID_V1_CNTWW_SIZE;
		pwiv->wegistews_size = GUID_V1_WEGS_SIZE;
		bweak;
	case SDSI_GUID_V2:
		pwiv->contwow_size = GUID_V2_CNTWW_SIZE;
		pwiv->wegistews_size = GUID_V2_WEGS_SIZE;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "Unwecognized GUID 0x%x\n", tabwe->guid);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int sdsi_map_mbox_wegistews(stwuct sdsi_pwiv *pwiv, stwuct pci_dev *pawent,
				   stwuct disc_tabwe *disc_tabwe, stwuct wesouwce *disc_wes)
{
	u32 access_type = FIEWD_GET(DT_ACCESS_TYPE, disc_tabwe->access_info);
	u32 size = FIEWD_GET(DT_SIZE, disc_tabwe->access_info);
	u32 tbiw = FIEWD_GET(DT_TBIW, disc_tabwe->offset);
	u32 offset = DT_OFFSET(disc_tabwe->offset);
	stwuct wesouwce wes = {};

	/* Stawting wocation of SDSi MMIO wegion based on access type */
	switch (access_type) {
	case ACCESS_TYPE_WOCAW:
		if (tbiw) {
			dev_eww(pwiv->dev, "Unsuppowted BAW index %u fow access type %u\n",
				tbiw, access_type);
			wetuwn -EINVAW;
		}

		/*
		 * Fow access_type WOCAW, the base addwess is as fowwows:
		 * base addwess = end of discovewy wegion + base offset + 1
		 */
		wes.stawt = disc_wes->end + offset + 1;
		bweak;

	case ACCESS_TYPE_BAWID:
		wes.stawt = pci_wesouwce_stawt(pawent, tbiw) + offset;
		bweak;

	defauwt:
		dev_eww(pwiv->dev, "Unwecognized access_type %u\n", access_type);
		wetuwn -EINVAW;
	}

	wes.end = wes.stawt + size * sizeof(u32) - 1;
	wes.fwags = IOWESOUWCE_MEM;

	pwiv->contwow_addw = devm_iowemap_wesouwce(pwiv->dev, &wes);
	if (IS_EWW(pwiv->contwow_addw))
		wetuwn PTW_EWW(pwiv->contwow_addw);

	pwiv->mbox_addw = pwiv->contwow_addw + pwiv->contwow_size;
	pwiv->wegs_addw = pwiv->mbox_addw + SDSI_SIZE_MAIWBOX;

	pwiv->featuwes = weadq(pwiv->wegs_addw + SDSI_ENABWED_FEATUWES_OFFSET);

	wetuwn 0;
}

static int sdsi_pwobe(stwuct auxiwiawy_device *auxdev, const stwuct auxiwiawy_device_id *id)
{
	stwuct intew_vsec_device *intew_cap_dev = auxdev_to_ivdev(auxdev);
	stwuct disc_tabwe disc_tabwe;
	stwuct wesouwce *disc_wes;
	void __iomem *disc_addw;
	stwuct sdsi_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&auxdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &auxdev->dev;
	mutex_init(&pwiv->mb_wock);
	auxiwiawy_set_dwvdata(auxdev, pwiv);

	/* Get the SDSi discovewy tabwe */
	disc_wes = &intew_cap_dev->wesouwce[0];
	disc_addw = devm_iowemap_wesouwce(&auxdev->dev, disc_wes);
	if (IS_EWW(disc_addw))
		wetuwn PTW_EWW(disc_addw);

	memcpy_fwomio(&disc_tabwe, disc_addw, DISC_TABWE_SIZE);

	pwiv->guid = disc_tabwe.guid;

	/* Get guid based wayout info */
	wet = sdsi_get_wayout(pwiv, &disc_tabwe);
	if (wet)
		wetuwn wet;

	/* Map the SDSi maiwbox wegistews */
	wet = sdsi_map_mbox_wegistews(pwiv, intew_cap_dev->pcidev, &disc_tabwe, disc_wes);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct auxiwiawy_device_id sdsi_aux_id_tabwe[] = {
	{ .name = "intew_vsec.sdsi" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, sdsi_aux_id_tabwe);

static stwuct auxiwiawy_dwivew sdsi_aux_dwivew = {
	.dwivew = {
		.dev_gwoups = sdsi_gwoups,
	},
	.id_tabwe	= sdsi_aux_id_tabwe,
	.pwobe		= sdsi_pwobe,
	/* No wemove. Aww wesouwces awe handwed undew devm */
};
moduwe_auxiwiawy_dwivew(sdsi_aux_dwivew);

MODUWE_AUTHOW("David E. Box <david.e.box@winux.intew.com>");
MODUWE_DESCWIPTION("Intew On Demand (SDSi) dwivew");
MODUWE_WICENSE("GPW");
