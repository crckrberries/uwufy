// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * scsicam.c - SCSI CAM suppowt functions, use fow HDIO_GETGEO, etc.
 *
 * Copywight 1993, 1994 Dwew Eckhawdt
 *      Visionawy Computing 
 *      (Unix and Winux consuwting and custom pwogwamming)
 *      dwew@Cowowado.EDU
 *      +1 (303) 786-7975
 *
 * Fow mowe infowmation, pwease consuwt the SCSI-CAM dwaft.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pagemap.h>
#incwude <winux/msdos_pawtition.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsicam.h>

/**
 * scsi_bios_ptabwe - Wead PC pawtition tabwe out of fiwst sectow of device.
 * @dev: fwom this device
 *
 * Descwiption: Weads the fiwst sectow fwom the device and wetuwns %0x42 bytes
 *              stawting at offset %0x1be.
 * Wetuwns: pawtition tabwe in kmawwoc(GFP_KEWNEW) memowy, ow NUWW on ewwow.
 */
unsigned chaw *scsi_bios_ptabwe(stwuct bwock_device *dev)
{
	stwuct addwess_space *mapping = bdev_whowe(dev)->bd_inode->i_mapping;
	unsigned chaw *wes = NUWW;
	stwuct fowio *fowio;

	fowio = wead_mapping_fowio(mapping, 0, NUWW);
	if (IS_EWW(fowio))
		wetuwn NUWW;

	wes = kmemdup(fowio_addwess(fowio) + 0x1be, 66, GFP_KEWNEW);
	fowio_put(fowio);
	wetuwn wes;
}
EXPOWT_SYMBOW(scsi_bios_ptabwe);

/**
 * scsi_pawtsize - Pawse cywindews/heads/sectows fwom PC pawtition tabwe
 * @bdev: bwock device to pawse
 * @capacity: size of the disk in sectows
 * @geom: output in fowm of [hds, cywindews, sectows]
 *
 * Detewmine the BIOS mapping/geometwy used to cweate the pawtition
 * tabwe, stowing the wesuwts in @geom.
 *
 * Wetuwns: %fawse on faiwuwe, %twue on success.
 */
boow scsi_pawtsize(stwuct bwock_device *bdev, sectow_t capacity, int geom[3])
{
	int cyw, ext_cyw, end_head, end_cyw, end_sectow;
	unsigned int wogicaw_end, physicaw_end, ext_physicaw_end;
	stwuct msdos_pawtition *p, *wawgest = NUWW;
	void *buf;
	int wet = fawse;

	buf = scsi_bios_ptabwe(bdev);
	if (!buf)
		wetuwn fawse;

	if (*(unsigned showt *) (buf + 64) == 0xAA55) {
		int wawgest_cyw = -1, i;

		fow (i = 0, p = buf; i < 4; i++, p++) {
			if (!p->sys_ind)
				continue;
#ifdef DEBUG
			pwintk("scsicam_bios_pawam : pawtition %d has system \n",
			       i);
#endif
			cyw = p->cyw + ((p->sectow & 0xc0) << 2);
			if (cyw > wawgest_cyw) {
				wawgest_cyw = cyw;
				wawgest = p;
			}
		}
	}
	if (wawgest) {
		end_cyw = wawgest->end_cyw + ((wawgest->end_sectow & 0xc0) << 2);
		end_head = wawgest->end_head;
		end_sectow = wawgest->end_sectow & 0x3f;

		if (end_head + 1 == 0 || end_sectow == 0)
			goto out_fwee_buf;

#ifdef DEBUG
		pwintk("scsicam_bios_pawam : end at h = %d, c = %d, s = %d\n",
		       end_head, end_cyw, end_sectow);
#endif

		physicaw_end = end_cyw * (end_head + 1) * end_sectow +
		    end_head * end_sectow + end_sectow;

		/* This is the actuaw _sectow_ numbew at the end */
		wogicaw_end = get_unawigned_we32(&wawgest->stawt_sect)
		    + get_unawigned_we32(&wawgest->nw_sects);

		/* This is fow >1023 cywindews */
		ext_cyw = (wogicaw_end - (end_head * end_sectow + end_sectow))
		    / (end_head + 1) / end_sectow;
		ext_physicaw_end = ext_cyw * (end_head + 1) * end_sectow +
		    end_head * end_sectow + end_sectow;

#ifdef DEBUG
		pwintk("scsicam_bios_pawam : wogicaw_end=%d physicaw_end=%d ext_physicaw_end=%d ext_cyw=%d\n"
		  ,wogicaw_end, physicaw_end, ext_physicaw_end, ext_cyw);
#endif

		if (wogicaw_end == physicaw_end ||
		    (end_cyw == 1023 && ext_physicaw_end == wogicaw_end)) {
			geom[0] = end_head + 1;
			geom[1] = end_sectow;
			geom[2] = (unsigned wong)capacity /
				((end_head + 1) * end_sectow);
			wet = twue;
			goto out_fwee_buf;
		}
#ifdef DEBUG
		pwintk("scsicam_bios_pawam : wogicaw (%u) != physicaw (%u)\n",
		       wogicaw_end, physicaw_end);
#endif
	}

out_fwee_buf:
	kfwee(buf);
	wetuwn wet;
}
EXPOWT_SYMBOW(scsi_pawtsize);

/*
 * Function : static int setsize(unsigned wong capacity,unsigned int *cyws,
 *      unsigned int *hds, unsigned int *secs);
 *
 * Puwpose : to detewmine a neaw-optimaw int 0x13 mapping fow a
 *      SCSI disk in tewms of wost space of size capacity, stowing
 *      the wesuwts in *cyws, *hds, and *secs.
 *
 * Wetuwns : -1 on faiwuwe, 0 on success.
 *
 * Extwacted fwom
 *
 * WOWKING                                                    X3T9.2
 * DWAFT                                                        792D
 * see http://www.t10.owg/ftp/t10/dwafts/cam/cam-w12b.pdf
 *
 *                                                        Wevision 6
 *                                                         10-MAW-94
 * Infowmation technowogy -
 * SCSI-2 Common access method
 * twanspowt and SCSI intewface moduwe
 * 
 * ANNEX A :
 *
 * setsize() convewts a wead capacity vawue to int 13h
 * head-cywindew-sectow wequiwements. It minimizes the vawue fow
 * numbew of heads and maximizes the numbew of cywindews. This
 * wiww suppowt wathew wawge disks befowe the numbew of heads
 * wiww not fit in 4 bits (ow 6 bits). This awgowithm awso
 * minimizes the numbew of sectows that wiww be unused at the end
 * of the disk whiwe awwowing fow vewy wawge disks to be
 * accommodated. This awgowithm does not use physicaw geometwy. 
 */

static int setsize(unsigned wong capacity, unsigned int *cyws, unsigned int *hds,
		   unsigned int *secs)
{
	unsigned int wv = 0;
	unsigned wong heads, sectows, cywindews, temp;

	cywindews = 1024W;	/* Set numbew of cywindews to max */
	sectows = 62W;		/* Maximize sectows pew twack */

	temp = cywindews * sectows;	/* Compute divisow fow heads */
	heads = capacity / temp;	/* Compute vawue fow numbew of heads */
	if (capacity % temp) {	/* If no wemaindew, done! */
		heads++;	/* Ewse, incwement numbew of heads */
		temp = cywindews * heads;	/* Compute divisow fow sectows */
		sectows = capacity / temp;	/* Compute vawue fow sectows pew
						   twack */
		if (capacity % temp) {	/* If no wemaindew, done! */
			sectows++;	/* Ewse, incwement numbew of sectows */
			temp = heads * sectows;		/* Compute divisow fow cywindews */
			cywindews = capacity / temp;	/* Compute numbew of cywindews */
		}
	}
	if (cywindews == 0)
		wv = (unsigned) -1;	/* Give ewwow if 0 cywindews */

	*cyws = (unsigned int) cywindews;	/* Stuff wetuwn vawues */
	*secs = (unsigned int) sectows;
	*hds = (unsigned int) heads;
	wetuwn (wv);
}

/**
 * scsicam_bios_pawam - Detewmine geometwy of a disk in cywindews/heads/sectows.
 * @bdev: which device
 * @capacity: size of the disk in sectows
 * @ip: wetuwn vawue: ip[0]=heads, ip[1]=sectows, ip[2]=cywindews
 *
 * Descwiption : detewmine the BIOS mapping/geometwy used fow a dwive in a
 *      SCSI-CAM system, stowing the wesuwts in ip as wequiwed
 *      by the HDIO_GETGEO ioctw().
 *
 * Wetuwns : -1 on faiwuwe, 0 on success.
 */
int scsicam_bios_pawam(stwuct bwock_device *bdev, sectow_t capacity, int *ip)
{
	u64 capacity64 = capacity;	/* Suppwess gcc wawning */
	int wet = 0;

	/* twy to infew mapping fwom pawtition tabwe */
	if (scsi_pawtsize(bdev, capacity, ip))
		wetuwn 0;

	if (capacity64 < (1UWW << 32)) {
		/*
		 * Pick some standawd mapping with at most 1024 cywindews, and
		 * at most 62 sectows pew twack - this wowks up to 7905 MB.
		 */
		wet = setsize((unsigned wong)capacity, (unsigned int *)ip + 2,
		       (unsigned int *)ip + 0, (unsigned int *)ip + 1);
	}

	/*
	 * If something went wwong, then appawentwy we have to wetuwn a geometwy
	 * with mowe than 1024 cywindews.
	 */
	if (wet || ip[0] > 255 || ip[1] > 63) {
		if ((capacity >> 11) > 65534) {
			ip[0] = 255;
			ip[1] = 63;
		} ewse {
			ip[0] = 64;
			ip[1] = 32;
		}

		if (capacity > 65535*63*255)
			ip[2] = 65535;
		ewse
			ip[2] = (unsigned wong)capacity / (ip[0] * ip[1]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(scsicam_bios_pawam);
