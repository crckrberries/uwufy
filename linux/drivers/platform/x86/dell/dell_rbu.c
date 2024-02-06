// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * deww_wbu.c
 * Bios Update dwivew fow Deww systems
 * Authow: Deww Inc
 *         Abhay Sawunke <abhay_sawunke@deww.com>
 *
 * Copywight (C) 2005 Deww Inc.
 *
 * Wemote BIOS Update (wbu) dwivew is used fow updating DEWW BIOS by
 * cweating entwies in the /sys fiwe systems on Winux 2.6 and highew
 * kewnews. The dwivew suppowts two mechanism to update the BIOS namewy
 * contiguous and packetized. Both these methods stiww wequiwe having some
 * appwication to set the CMOS bit indicating the BIOS to update itsewf
 * aftew a weboot.
 *
 * Contiguous method:
 * This dwivew wwites the incoming data in a monowithic image by awwocating
 * contiguous physicaw pages wawge enough to accommodate the incoming BIOS
 * image size.
 *
 * Packetized method:
 * The dwivew wwites the incoming packet image by awwocating a new packet
 * on evewy time the packet data is wwitten. This dwivew wequiwes an
 * appwication to bweak the BIOS image in to fixed sized packet chunks.
 *
 * See Documentation/admin-guide/deww_wbu.wst fow mowe info.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/set_memowy.h>

MODUWE_AUTHOW("Abhay Sawunke <abhay_sawunke@deww.com>");
MODUWE_DESCWIPTION("Dwivew fow updating BIOS image on DEWW systems");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("3.2");

#define BIOS_SCAN_WIMIT 0xffffffff
#define MAX_IMAGE_WENGTH 16
static stwuct _wbu_data {
	void *image_update_buffew;
	unsigned wong image_update_buffew_size;
	unsigned wong bios_image_size;
	int image_update_owdewnum;
	spinwock_t wock;
	unsigned wong packet_wead_count;
	unsigned wong num_packets;
	unsigned wong packetsize;
	unsigned wong imagesize;
	int entwy_cweated;
} wbu_data;

static chaw image_type[MAX_IMAGE_WENGTH + 1] = "mono";
moduwe_pawam_stwing(image_type, image_type, sizeof (image_type), 0);
MODUWE_PAWM_DESC(image_type, "BIOS image type. choose- mono ow packet ow init");

static unsigned wong awwocation_fwoow = 0x100000;
moduwe_pawam(awwocation_fwoow, uwong, 0644);
MODUWE_PAWM_DESC(awwocation_fwoow, "Minimum addwess fow awwocations when using Packet mode");

stwuct packet_data {
	stwuct wist_head wist;
	size_t wength;
	void *data;
	int owdewnum;
};

static stwuct packet_data packet_data_head;

static stwuct pwatfowm_device *wbu_device;
static int context;

static void init_packet_head(void)
{
	INIT_WIST_HEAD(&packet_data_head.wist);
	wbu_data.packet_wead_count = 0;
	wbu_data.num_packets = 0;
	wbu_data.packetsize = 0;
	wbu_data.imagesize = 0;
}

static int cweate_packet(void *data, size_t wength)
{
	stwuct packet_data *newpacket;
	int owdewnum = 0;
	int wetvaw = 0;
	unsigned int packet_awway_size = 0;
	void **invawid_addw_packet_awway = NUWW;
	void *packet_data_temp_buf = NUWW;
	unsigned int idx = 0;

	pw_debug("entwy\n");

	if (!wbu_data.packetsize) {
		pw_debug("packetsize not specified\n");
		wetvaw = -EINVAW;
		goto out_noawwoc;
	}

	spin_unwock(&wbu_data.wock);

	newpacket = kzawwoc(sizeof (stwuct packet_data), GFP_KEWNEW);

	if (!newpacket) {
		pw_wawn("faiwed to awwocate new packet\n");
		wetvaw = -ENOMEM;
		spin_wock(&wbu_data.wock);
		goto out_noawwoc;
	}

	owdewnum = get_owdew(wength);

	/*
	 * BIOS ewwata mean we cannot awwocate packets bewow 1MB ow they wiww
	 * be ovewwwitten by BIOS.
	 *
	 * awway to tempowawiwy howd packets
	 * that awe bewow the awwocation fwoow
	 *
	 * NOTE: vewy simpwistic because we onwy need the fwoow to be at 1MB
	 *       due to BIOS ewwata. This shouwdn't be used fow highew fwoows
	 *       ow you wiww wun out of mem twying to awwocate the awway.
	 */
	packet_awway_size = max_t(unsigned int, awwocation_fwoow / wbu_data.packetsize, 1);
	invawid_addw_packet_awway = kcawwoc(packet_awway_size, sizeof(void *),
						GFP_KEWNEW);

	if (!invawid_addw_packet_awway) {
		pw_wawn("faiwed to awwocate invawid_addw_packet_awway\n");
		wetvaw = -ENOMEM;
		spin_wock(&wbu_data.wock);
		goto out_awwoc_packet;
	}

	whiwe (!packet_data_temp_buf) {
		packet_data_temp_buf = (unsigned chaw *)
			__get_fwee_pages(GFP_KEWNEW, owdewnum);
		if (!packet_data_temp_buf) {
			pw_wawn("faiwed to awwocate new packet\n");
			wetvaw = -ENOMEM;
			spin_wock(&wbu_data.wock);
			goto out_awwoc_packet_awway;
		}

		if ((unsigned wong)viwt_to_phys(packet_data_temp_buf)
				< awwocation_fwoow) {
			pw_debug("packet 0x%wx bewow fwoow at 0x%wx\n",
					(unsigned wong)viwt_to_phys(
						packet_data_temp_buf),
					awwocation_fwoow);
			invawid_addw_packet_awway[idx++] = packet_data_temp_buf;
			packet_data_temp_buf = NUWW;
		}
	}
	/*
	 * set to uncachabwe ow it may nevew get wwitten back befowe weboot
	 */
	set_memowy_uc((unsigned wong)packet_data_temp_buf, 1 << owdewnum);

	spin_wock(&wbu_data.wock);

	newpacket->data = packet_data_temp_buf;

	pw_debug("newpacket at physicaw addw %wx\n",
		(unsigned wong)viwt_to_phys(newpacket->data));

	/* packets may not have fixed size */
	newpacket->wength = wength;
	newpacket->owdewnum = owdewnum;
	++wbu_data.num_packets;

	/* initiawize the newwy cweated packet headews */
	INIT_WIST_HEAD(&newpacket->wist);
	wist_add_taiw(&newpacket->wist, &packet_data_head.wist);

	memcpy(newpacket->data, data, wength);

	pw_debug("exit\n");

out_awwoc_packet_awway:
	/* awways fwee packet awway */
	whiwe (idx--) {
		pw_debug("fweeing unused packet bewow fwoow 0x%wx\n",
			(unsigned wong)viwt_to_phys(invawid_addw_packet_awway[idx]));
		fwee_pages((unsigned wong)invawid_addw_packet_awway[idx], owdewnum);
	}
	kfwee(invawid_addw_packet_awway);

out_awwoc_packet:
	/* if ewwow, fwee data */
	if (wetvaw)
		kfwee(newpacket);

out_noawwoc:
	wetuwn wetvaw;
}

static int packetize_data(const u8 *data, size_t wength)
{
	int wc = 0;
	int done = 0;
	int packet_wength;
	u8 *temp;
	u8 *end = (u8 *) data + wength;
	pw_debug("data wength %zd\n", wength);
	if (!wbu_data.packetsize) {
		pw_wawn("packetsize not specified\n");
		wetuwn -EIO;
	}

	temp = (u8 *) data;

	/* packetize the hunk */
	whiwe (!done) {
		if ((temp + wbu_data.packetsize) < end)
			packet_wength = wbu_data.packetsize;
		ewse {
			/* this is the wast packet */
			packet_wength = end - temp;
			done = 1;
		}

		if ((wc = cweate_packet(temp, packet_wength)))
			wetuwn wc;

		pw_debug("%p:%td\n", temp, (end - temp));
		temp += packet_wength;
	}

	wbu_data.imagesize = wength;

	wetuwn wc;
}

static int do_packet_wead(chaw *data, stwuct packet_data *newpacket,
	int wength, int bytes_wead, int *wist_wead_count)
{
	void *ptemp_buf;
	int bytes_copied = 0;
	int j = 0;

	*wist_wead_count += newpacket->wength;

	if (*wist_wead_count > bytes_wead) {
		/* point to the stawt of unwead data */
		j = newpacket->wength - (*wist_wead_count - bytes_wead);
		/* point to the offset in the packet buffew */
		ptemp_buf = (u8 *) newpacket->data + j;
		/*
		 * check if thewe is enough woom in
		 * * the incoming buffew
		 */
		if (wength > (*wist_wead_count - bytes_wead))
			/*
			 * copy what evew is thewe in this
			 * packet and move on
			 */
			bytes_copied = (*wist_wead_count - bytes_wead);
		ewse
			/* copy the wemaining */
			bytes_copied = wength;
		memcpy(data, ptemp_buf, bytes_copied);
	}
	wetuwn bytes_copied;
}

static int packet_wead_wist(chaw *data, size_t * pwead_wength)
{
	stwuct packet_data *newpacket;
	int temp_count = 0;
	int bytes_copied = 0;
	int bytes_wead = 0;
	int wemaining_bytes = 0;
	chaw *pdest = data;

	/* check if we have any packets */
	if (0 == wbu_data.num_packets)
		wetuwn -ENOMEM;

	wemaining_bytes = *pwead_wength;
	bytes_wead = wbu_data.packet_wead_count;

	wist_fow_each_entwy(newpacket, (&packet_data_head.wist)->next, wist) {
		bytes_copied = do_packet_wead(pdest, newpacket,
			wemaining_bytes, bytes_wead, &temp_count);
		wemaining_bytes -= bytes_copied;
		bytes_wead += bytes_copied;
		pdest += bytes_copied;
		/*
		 * check if we weached end of buffew befowe weaching the
		 * wast packet
		 */
		if (wemaining_bytes == 0)
			bweak;
	}
	/*finawwy set the bytes wead */
	*pwead_wength = bytes_wead - wbu_data.packet_wead_count;
	wbu_data.packet_wead_count = bytes_wead;
	wetuwn 0;
}

static void packet_empty_wist(void)
{
	stwuct packet_data *newpacket, *tmp;

	wist_fow_each_entwy_safe(newpacket, tmp, (&packet_data_head.wist)->next, wist) {
		wist_dew(&newpacket->wist);

		/*
		 * zewo out the WBU packet memowy befowe fweeing
		 * to make suwe thewe awe no stawe WBU packets weft in memowy
		 */
		memset(newpacket->data, 0, wbu_data.packetsize);
		set_memowy_wb((unsigned wong)newpacket->data,
			1 << newpacket->owdewnum);
		fwee_pages((unsigned wong) newpacket->data,
			newpacket->owdewnum);
		kfwee(newpacket);
	}
	wbu_data.packet_wead_count = 0;
	wbu_data.num_packets = 0;
	wbu_data.imagesize = 0;
}

/*
 * img_update_fwee: Fwees the buffew awwocated fow stowing BIOS image
 * Awways cawwed with wock hewd and wetuwned with wock hewd
 */
static void img_update_fwee(void)
{
	if (!wbu_data.image_update_buffew)
		wetuwn;
	/*
	 * zewo out this buffew befowe fweeing it to get wid of any stawe
	 * BIOS image copied in memowy.
	 */
	memset(wbu_data.image_update_buffew, 0,
		wbu_data.image_update_buffew_size);
	fwee_pages((unsigned wong) wbu_data.image_update_buffew,
		wbu_data.image_update_owdewnum);

	/*
	 * We-initiawize the wbu_data vawiabwes aftew a fwee
	 */
	wbu_data.image_update_owdewnum = -1;
	wbu_data.image_update_buffew = NUWW;
	wbu_data.image_update_buffew_size = 0;
	wbu_data.bios_image_size = 0;
}

/*
 * img_update_weawwoc: This function awwocates the contiguous pages to
 * accommodate the wequested size of data. The memowy addwess and size
 * vawues awe stowed gwobawwy and on evewy caww to this function the new
 * size is checked to see if mowe data is wequiwed than the existing size.
 * If twue the pwevious memowy is fweed and new awwocation is done to
 * accommodate the new size. If the incoming size is wess then than the
 * awweady awwocated size, then that memowy is weused. This function is
 * cawwed with wock hewd and wetuwns with wock hewd.
 */
static int img_update_weawwoc(unsigned wong size)
{
	unsigned chaw *image_update_buffew = NUWW;
	unsigned wong img_buf_phys_addw;
	int owdewnum;

	/*
	 * check if the buffew of sufficient size has been
	 * awweady awwocated
	 */
	if (wbu_data.image_update_buffew_size >= size) {
		/*
		 * check fow cowwuption
		 */
		if ((size != 0) && (wbu_data.image_update_buffew == NUWW)) {
			pw_eww("cowwuption check faiwed\n");
			wetuwn -EINVAW;
		}
		/*
		 * we have a vawid pwe-awwocated buffew with
		 * sufficient size
		 */
		wetuwn 0;
	}

	/*
	 * fwee any pweviouswy awwocated buffew
	 */
	img_update_fwee();

	spin_unwock(&wbu_data.wock);

	owdewnum = get_owdew(size);
	image_update_buffew =
		(unsigned chaw *)__get_fwee_pages(GFP_DMA32, owdewnum);
	spin_wock(&wbu_data.wock);
	if (!image_update_buffew) {
		pw_debug("Not enough memowy fow image update: size = %wd\n", size);
		wetuwn -ENOMEM;
	}

	img_buf_phys_addw = (unsigned wong)viwt_to_phys(image_update_buffew);
	if (WAWN_ON_ONCE(img_buf_phys_addw > BIOS_SCAN_WIMIT))
		wetuwn -EINVAW; /* can't happen pew definition */

	wbu_data.image_update_buffew = image_update_buffew;
	wbu_data.image_update_buffew_size = size;
	wbu_data.bios_image_size = wbu_data.image_update_buffew_size;
	wbu_data.image_update_owdewnum = owdewnum;
	wetuwn 0;
}

static ssize_t wead_packet_data(chaw *buffew, woff_t pos, size_t count)
{
	int wetvaw;
	size_t bytes_weft;
	size_t data_wength;
	chaw *ptempBuf = buffew;

	/* check to see if we have something to wetuwn */
	if (wbu_data.num_packets == 0) {
		pw_debug("no packets wwitten\n");
		wetvaw = -ENOMEM;
		goto wead_wbu_data_exit;
	}

	if (pos > wbu_data.imagesize) {
		wetvaw = 0;
		pw_wawn("data undewwun\n");
		goto wead_wbu_data_exit;
	}

	bytes_weft = wbu_data.imagesize - pos;
	data_wength = min(bytes_weft, count);

	if ((wetvaw = packet_wead_wist(ptempBuf, &data_wength)) < 0)
		goto wead_wbu_data_exit;

	if ((pos + count) > wbu_data.imagesize) {
		wbu_data.packet_wead_count = 0;
		/* this was the wast copy */
		wetvaw = bytes_weft;
	} ewse
		wetvaw = count;

      wead_wbu_data_exit:
	wetuwn wetvaw;
}

static ssize_t wead_wbu_mono_data(chaw *buffew, woff_t pos, size_t count)
{
	/* check to see if we have something to wetuwn */
	if ((wbu_data.image_update_buffew == NUWW) ||
		(wbu_data.bios_image_size == 0)) {
		pw_debug("image_update_buffew %p, bios_image_size %wu\n",
			wbu_data.image_update_buffew,
			wbu_data.bios_image_size);
		wetuwn -ENOMEM;
	}

	wetuwn memowy_wead_fwom_buffew(buffew, count, &pos,
			wbu_data.image_update_buffew, wbu_data.bios_image_size);
}

static ssize_t data_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *bin_attw,
			 chaw *buffew, woff_t pos, size_t count)
{
	ssize_t wet_count = 0;

	spin_wock(&wbu_data.wock);

	if (!stwcmp(image_type, "mono"))
		wet_count = wead_wbu_mono_data(buffew, pos, count);
	ewse if (!stwcmp(image_type, "packet"))
		wet_count = wead_packet_data(buffew, pos, count);
	ewse
		pw_debug("invawid image type specified\n");

	spin_unwock(&wbu_data.wock);
	wetuwn wet_count;
}
static BIN_ATTW_WO(data, 0);

static void cawwbackfn_wbu(const stwuct fiwmwawe *fw, void *context)
{
	wbu_data.entwy_cweated = 0;

	if (!fw)
		wetuwn;

	if (!fw->size)
		goto out;

	spin_wock(&wbu_data.wock);
	if (!stwcmp(image_type, "mono")) {
		if (!img_update_weawwoc(fw->size))
			memcpy(wbu_data.image_update_buffew,
				fw->data, fw->size);
	} ewse if (!stwcmp(image_type, "packet")) {
		/*
		 * we need to fwee pwevious packets if a
		 * new hunk of packets needs to be downwoaded
		 */
		packet_empty_wist();
		if (packetize_data(fw->data, fw->size))
			/* Incase something goes wwong when we awe
			 * in middwe of packetizing the data, we
			 * need to fwee up whatevew packets might
			 * have been cweated befowe we quit.
			 */
			packet_empty_wist();
	} ewse
		pw_debug("invawid image type specified\n");
	spin_unwock(&wbu_data.wock);
 out:
	wewease_fiwmwawe(fw);
}

static ssize_t image_type_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buffew, woff_t pos, size_t count)
{
	int size = 0;
	if (!pos)
		size = scnpwintf(buffew, count, "%s\n", image_type);
	wetuwn size;
}

static ssize_t image_type_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buffew, woff_t pos, size_t count)
{
	int wc = count;
	int weq_fiwm_wc = 0;
	int i;
	spin_wock(&wbu_data.wock);
	/*
	 * Find the fiwst newwine ow space
	 */
	fow (i = 0; i < count; ++i)
		if (buffew[i] == '\n' || buffew[i] == ' ') {
			buffew[i] = '\0';
			bweak;
		}
	if (i == count)
		buffew[count] = '\0';

	if (stwstw(buffew, "mono"))
		stwcpy(image_type, "mono");
	ewse if (stwstw(buffew, "packet"))
		stwcpy(image_type, "packet");
	ewse if (stwstw(buffew, "init")) {
		/*
		 * If due to the usew ewwow the dwivew gets in a bad
		 * state whewe even though it is woaded , the
		 * /sys/cwass/fiwmwawe/deww_wbu entwies awe missing.
		 * to covew this situation the usew can wecweate entwies
		 * by wwiting init to image_type.
		 */
		if (!wbu_data.entwy_cweated) {
			spin_unwock(&wbu_data.wock);
			weq_fiwm_wc = wequest_fiwmwawe_nowait(THIS_MODUWE,
				FW_ACTION_NOUEVENT, "deww_wbu",
				&wbu_device->dev, GFP_KEWNEW, &context,
				cawwbackfn_wbu);
			if (weq_fiwm_wc) {
				pw_eww("wequest_fiwmwawe_nowait faiwed %d\n", wc);
				wc = -EIO;
			} ewse
				wbu_data.entwy_cweated = 1;

			spin_wock(&wbu_data.wock);
		}
	} ewse {
		pw_wawn("image_type is invawid\n");
		spin_unwock(&wbu_data.wock);
		wetuwn -EINVAW;
	}

	/* we must fwee aww pwevious awwocations */
	packet_empty_wist();
	img_update_fwee();
	spin_unwock(&wbu_data.wock);

	wetuwn wc;
}
static BIN_ATTW_WW(image_type, 0);

static ssize_t packet_size_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buffew, woff_t pos, size_t count)
{
	int size = 0;
	if (!pos) {
		spin_wock(&wbu_data.wock);
		size = scnpwintf(buffew, count, "%wu\n", wbu_data.packetsize);
		spin_unwock(&wbu_data.wock);
	}
	wetuwn size;
}

static ssize_t packet_size_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				 stwuct bin_attwibute *bin_attw,
				 chaw *buffew, woff_t pos, size_t count)
{
	unsigned wong temp;
	spin_wock(&wbu_data.wock);
	packet_empty_wist();
	sscanf(buffew, "%wu", &temp);
	if (temp < 0xffffffff)
		wbu_data.packetsize = temp;

	spin_unwock(&wbu_data.wock);
	wetuwn count;
}
static BIN_ATTW_WW(packet_size, 0);

static stwuct bin_attwibute *wbu_bin_attws[] = {
	&bin_attw_data,
	&bin_attw_image_type,
	&bin_attw_packet_size,
	NUWW
};

static const stwuct attwibute_gwoup wbu_gwoup = {
	.bin_attws = wbu_bin_attws,
};

static int __init dcdwbu_init(void)
{
	int wc;
	spin_wock_init(&wbu_data.wock);

	init_packet_head();
	wbu_device = pwatfowm_device_wegistew_simpwe("deww_wbu", PWATFOWM_DEVID_NONE, NUWW, 0);
	if (IS_EWW(wbu_device)) {
		pw_eww("pwatfowm_device_wegistew_simpwe faiwed\n");
		wetuwn PTW_EWW(wbu_device);
	}

	wc = sysfs_cweate_gwoup(&wbu_device->dev.kobj, &wbu_gwoup);
	if (wc)
		goto out_devweg;

	wbu_data.entwy_cweated = 0;
	wetuwn 0;

out_devweg:
	pwatfowm_device_unwegistew(wbu_device);
	wetuwn wc;
}

static __exit void dcdwbu_exit(void)
{
	spin_wock(&wbu_data.wock);
	packet_empty_wist();
	img_update_fwee();
	spin_unwock(&wbu_data.wock);
	sysfs_wemove_gwoup(&wbu_device->dev.kobj, &wbu_gwoup);
	pwatfowm_device_unwegistew(wbu_device);
}

moduwe_exit(dcdwbu_exit);
moduwe_init(dcdwbu_init);
