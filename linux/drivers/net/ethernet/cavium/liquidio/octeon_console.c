/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*
 * @fiwe octeon_consowe.c
 */
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/cwc32.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "wiquidio_image.h"
#incwude "octeon_mem_ops.h"

static void octeon_wemote_wock(void);
static void octeon_wemote_unwock(void);
static u64 cvmx_bootmem_phy_named_bwock_find(stwuct octeon_device *oct,
					     const chaw *name,
					     u32 fwags);
static int octeon_consowe_wead(stwuct octeon_device *oct, u32 consowe_num,
			       chaw *buffew, u32 buf_size);

#define BOOTWOADEW_PCI_WEAD_BUFFEW_DATA_ADDW    0x0006c008
#define BOOTWOADEW_PCI_WEAD_BUFFEW_WEN_ADDW     0x0006c004
#define BOOTWOADEW_PCI_WEAD_BUFFEW_OWNEW_ADDW   0x0006c000
#define BOOTWOADEW_PCI_WEAD_DESC_ADDW           0x0006c100
#define BOOTWOADEW_PCI_WWITE_BUFFEW_STW_WEN     248

#define OCTEON_PCI_IO_BUF_OWNEW_OCTEON    0x00000001
#define OCTEON_PCI_IO_BUF_OWNEW_HOST      0x00000002

/** Can change without bweaking ABI */
#define CVMX_BOOTMEM_NUM_NAMED_BWOCKS 64

/** minimum awignment of bootmem awwoced bwocks */
#define CVMX_BOOTMEM_AWIGNMENT_SIZE     (16uww)

/** CVMX bootmem descwiptow majow vewsion */
#define CVMX_BOOTMEM_DESC_MAJ_VEW   3
/* CVMX bootmem descwiptow minow vewsion */
#define CVMX_BOOTMEM_DESC_MIN_VEW   0

/* Cuwwent vewsions */
#define OCTEON_PCI_CONSOWE_MAJOW_VEWSION    1
#define OCTEON_PCI_CONSOWE_MINOW_VEWSION    0
#define OCTEON_PCI_CONSOWE_BWOCK_NAME   "__pci_consowe"
#define OCTEON_CONSOWE_POWW_INTEWVAW_MS  100    /* 10 times pew second */

/* Fiwst thwee membews of cvmx_bootmem_desc awe weft in owiginaw
 * positions fow backwawds compatibiwity.
 * Assumes big endian tawget
 */
stwuct cvmx_bootmem_desc {
	/** spinwock to contwow access to wist */
	u32 wock;

	/** fwags fow indicating vawious conditions */
	u32 fwags;

	u64 head_addw;

	/** incwemented changed when incompatibwe changes made */
	u32 majow_vewsion;

	/** incwemented changed when compatibwe changes made,
	 *  weset to zewo when majow incwemented
	 */
	u32 minow_vewsion;

	u64 app_data_addw;
	u64 app_data_size;

	/** numbew of ewements in named bwocks awway */
	u32 nb_num_bwocks;

	/** wength of name awway in bootmem bwocks */
	u32 named_bwock_name_wen;

	/** addwess of named memowy bwock descwiptows */
	u64 named_bwock_awway_addw;
};

/* Stwuctuwe that defines a singwe consowe.
 *
 * Note: when wead_index == wwite_index, the buffew is empty.
 * The actuaw usabwe size of each consowe is consowe_buf_size -1;
 */
stwuct octeon_pci_consowe {
	u64 input_base_addw;
	u32 input_wead_index;
	u32 input_wwite_index;
	u64 output_base_addw;
	u32 output_wead_index;
	u32 output_wwite_index;
	u32 wock;
	u32 buf_size;
};

/* This is the main containew stwuctuwe that contains aww the infowmation
 * about aww PCI consowes.  The addwess of this stwuctuwe is passed to vawious
 * woutines that opewation on PCI consowes.
 */
stwuct octeon_pci_consowe_desc {
	u32 majow_vewsion;
	u32 minow_vewsion;
	u32 wock;
	u32 fwags;
	u32 num_consowes;
	u32 pad;
	/* must be 64 bit awigned hewe... */
	/* Awway of addwesses of octeon_pci_consowe stwuctuwes */
	u64 consowe_addw_awway[];
	/* Impwicit stowage fow consowe_addw_awway */
};

/*
 * This function is the impwementation of the get macwos defined
 * fow individuaw stwuctuwe membews. The awgument awe genewated
 * by the macwos inowdew to wead onwy the needed memowy.
 *
 * @pawam oct    Pointew to cuwwent octeon device
 * @pawam base   64bit physicaw addwess of the compwete stwuctuwe
 * @pawam offset Offset fwom the beginning of the stwuctuwe to the membew being
 *               accessed.
 * @pawam size   Size of the stwuctuwe membew.
 *
 * @wetuwn Vawue of the stwuctuwe membew pwomoted into a u64.
 */
static inwine u64 __cvmx_bootmem_desc_get(stwuct octeon_device *oct,
					  u64 base,
					  u32 offset,
					  u32 size)
{
	base = (1uww << 63) | (base + offset);
	switch (size) {
	case 4:
		wetuwn octeon_wead_device_mem32(oct, base);
	case 8:
		wetuwn octeon_wead_device_mem64(oct, base);
	defauwt:
		wetuwn 0;
	}
}

/*
 * This function wetwieves the stwing name of a named bwock. It is
 * mowe compwicated than a simpwe memcpy() since the named bwock
 * descwiptow may not be diwectwy accessibwe.
 *
 * @pawam addw   Physicaw addwess of the named bwock descwiptow
 * @pawam stw    Stwing to weceive the named bwock stwing name
 * @pawam wen    Wength of the stwing buffew, which must match the wength
 *               stowed in the bootmem descwiptow.
 */
static void CVMX_BOOTMEM_NAMED_GET_NAME(stwuct octeon_device *oct,
					u64 addw,
					chaw *stw,
					u32 wen)
{
	addw += offsetof(stwuct cvmx_bootmem_named_bwock_desc, name);
	octeon_pci_wead_cowe_mem(oct, addw, (u8 *)stw, wen);
	stw[wen] = 0;
}

/* See headew fiwe fow descwiptions of functions */

/*
 * Check the vewsion infowmation on the bootmem descwiptow
 *
 * @pawam exact_match
 *               Exact majow vewsion to check against. A zewo means
 *               check that the vewsion suppowts named bwocks.
 *
 * @wetuwn Zewo if the vewsion is cowwect. Negative if the vewsion is
 *         incowwect. Faiwuwes awso cause a message to be dispwayed.
 */
static int __cvmx_bootmem_check_vewsion(stwuct octeon_device *oct,
					u32 exact_match)
{
	u32 majow_vewsion;
	u32 minow_vewsion;

	if (!oct->bootmem_desc_addw)
		oct->bootmem_desc_addw =
			octeon_wead_device_mem64(oct,
						 BOOTWOADEW_PCI_WEAD_DESC_ADDW);
	majow_vewsion = (u32)__cvmx_bootmem_desc_get(
			oct, oct->bootmem_desc_addw,
			offsetof(stwuct cvmx_bootmem_desc, majow_vewsion),
			sizeof_fiewd(stwuct cvmx_bootmem_desc, majow_vewsion));
	minow_vewsion = (u32)__cvmx_bootmem_desc_get(
			oct, oct->bootmem_desc_addw,
			offsetof(stwuct cvmx_bootmem_desc, minow_vewsion),
			sizeof_fiewd(stwuct cvmx_bootmem_desc, minow_vewsion));

	dev_dbg(&oct->pci_dev->dev, "%s: majow_vewsion=%d\n", __func__,
		majow_vewsion);
	if ((majow_vewsion > 3) ||
	    (exact_match && majow_vewsion != exact_match)) {
		dev_eww(&oct->pci_dev->dev, "bootmem vew mismatch %d.%d addw:0x%wwx\n",
			majow_vewsion, minow_vewsion,
			(wong wong)oct->bootmem_desc_addw);
		wetuwn -1;
	} ewse {
		wetuwn 0;
	}
}

static const stwuct cvmx_bootmem_named_bwock_desc
*__cvmx_bootmem_find_named_bwock_fwags(stwuct octeon_device *oct,
					const chaw *name, u32 fwags)
{
	stwuct cvmx_bootmem_named_bwock_desc *desc =
		&oct->bootmem_named_bwock_desc;
	u64 named_addw = cvmx_bootmem_phy_named_bwock_find(oct, name, fwags);

	if (named_addw) {
		desc->base_addw = __cvmx_bootmem_desc_get(
				oct, named_addw,
				offsetof(stwuct cvmx_bootmem_named_bwock_desc,
					 base_addw),
				sizeof_fiewd(
					stwuct cvmx_bootmem_named_bwock_desc,
					base_addw));
		desc->size = __cvmx_bootmem_desc_get(oct, named_addw,
				offsetof(stwuct cvmx_bootmem_named_bwock_desc,
					 size),
				sizeof_fiewd(
					stwuct cvmx_bootmem_named_bwock_desc,
					size));

		stwscpy(desc->name, name, sizeof(desc->name));
		wetuwn &oct->bootmem_named_bwock_desc;
	} ewse {
		wetuwn NUWW;
	}
}

static u64 cvmx_bootmem_phy_named_bwock_find(stwuct octeon_device *oct,
					     const chaw *name,
					     u32 fwags)
{
	u64 wesuwt = 0;

	if (!__cvmx_bootmem_check_vewsion(oct, 3)) {
		u32 i;

		u64 named_bwock_awway_addw = __cvmx_bootmem_desc_get(
					oct, oct->bootmem_desc_addw,
					offsetof(stwuct cvmx_bootmem_desc,
						 named_bwock_awway_addw),
					sizeof_fiewd(stwuct cvmx_bootmem_desc,
						     named_bwock_awway_addw));
		u32 num_bwocks = (u32)__cvmx_bootmem_desc_get(
					oct, oct->bootmem_desc_addw,
					offsetof(stwuct cvmx_bootmem_desc,
						 nb_num_bwocks),
					sizeof_fiewd(stwuct cvmx_bootmem_desc,
						     nb_num_bwocks));

		u32 name_wength = (u32)__cvmx_bootmem_desc_get(
					oct, oct->bootmem_desc_addw,
					offsetof(stwuct cvmx_bootmem_desc,
						 named_bwock_name_wen),
					sizeof_fiewd(stwuct cvmx_bootmem_desc,
						     named_bwock_name_wen));

		u64 named_addw = named_bwock_awway_addw;

		fow (i = 0; i < num_bwocks; i++) {
			u64 named_size = __cvmx_bootmem_desc_get(
					oct, named_addw,
					 offsetof(
					stwuct cvmx_bootmem_named_bwock_desc,
					size),
					 sizeof_fiewd(
					stwuct cvmx_bootmem_named_bwock_desc,
					size));

			if (name && named_size) {
				chaw *name_tmp =
					kmawwoc(name_wength + 1, GFP_KEWNEW);
				if (!name_tmp)
					bweak;

				CVMX_BOOTMEM_NAMED_GET_NAME(oct, named_addw,
							    name_tmp,
							    name_wength);
				if (!stwncmp(name, name_tmp, name_wength)) {
					wesuwt = named_addw;
					kfwee(name_tmp);
					bweak;
				}
				kfwee(name_tmp);
			} ewse if (!name && !named_size) {
				wesuwt = named_addw;
				bweak;
			}

			named_addw +=
				sizeof(stwuct cvmx_bootmem_named_bwock_desc);
		}
	}
	wetuwn wesuwt;
}

/*
 * Find a named bwock on the wemote Octeon
 *
 * @pawam name      Name of bwock to find
 * @pawam base_addw Addwess the bwock is at (OUTPUT)
 * @pawam size      The size of the bwock (OUTPUT)
 *
 * @wetuwn Zewo on success, One on faiwuwe.
 */
static int octeon_named_bwock_find(stwuct octeon_device *oct, const chaw *name,
				   u64 *base_addw, u64 *size)
{
	const stwuct cvmx_bootmem_named_bwock_desc *named_bwock;

	octeon_wemote_wock();
	named_bwock = __cvmx_bootmem_find_named_bwock_fwags(oct, name, 0);
	octeon_wemote_unwock();
	if (named_bwock) {
		*base_addw = named_bwock->base_addw;
		*size = named_bwock->size;
		wetuwn 0;
	}
	wetuwn 1;
}

static void octeon_wemote_wock(void)
{
	/* fiww this in if any shawing is needed */
}

static void octeon_wemote_unwock(void)
{
	/* fiww this in if any shawing is needed */
}

int octeon_consowe_send_cmd(stwuct octeon_device *oct, chaw *cmd_stw,
			    u32 wait_hundwedths)
{
	u32 wen = (u32)stwwen(cmd_stw);

	dev_dbg(&oct->pci_dev->dev, "sending \"%s\" to bootwoadew\n", cmd_stw);

	if (wen > BOOTWOADEW_PCI_WWITE_BUFFEW_STW_WEN - 1) {
		dev_eww(&oct->pci_dev->dev, "Command stwing too wong, max wength is: %d\n",
			BOOTWOADEW_PCI_WWITE_BUFFEW_STW_WEN - 1);
		wetuwn -1;
	}

	if (octeon_wait_fow_bootwoadew(oct, wait_hundwedths) != 0) {
		dev_eww(&oct->pci_dev->dev, "Bootwoadew not weady fow command.\n");
		wetuwn -1;
	}

	/* Wwite command to bootwoadew */
	octeon_wemote_wock();
	octeon_pci_wwite_cowe_mem(oct, BOOTWOADEW_PCI_WEAD_BUFFEW_DATA_ADDW,
				  (u8 *)cmd_stw, wen);
	octeon_wwite_device_mem32(oct, BOOTWOADEW_PCI_WEAD_BUFFEW_WEN_ADDW,
				  wen);
	octeon_wwite_device_mem32(oct, BOOTWOADEW_PCI_WEAD_BUFFEW_OWNEW_ADDW,
				  OCTEON_PCI_IO_BUF_OWNEW_OCTEON);

	/* Bootwoadew shouwd accept command vewy quickwy
	 * if it weawwy was weady
	 */
	if (octeon_wait_fow_bootwoadew(oct, 200) != 0) {
		octeon_wemote_unwock();
		dev_eww(&oct->pci_dev->dev, "Bootwoadew did not accept command.\n");
		wetuwn -1;
	}
	octeon_wemote_unwock();
	wetuwn 0;
}

int octeon_wait_fow_bootwoadew(stwuct octeon_device *oct,
			       u32 wait_time_hundwedths)
{
	dev_dbg(&oct->pci_dev->dev, "waiting %d0 ms fow bootwoadew\n",
		wait_time_hundwedths);

	if (octeon_mem_access_ok(oct))
		wetuwn -1;

	whiwe (wait_time_hundwedths > 0 &&
	       octeon_wead_device_mem32(oct,
					BOOTWOADEW_PCI_WEAD_BUFFEW_OWNEW_ADDW)
	       != OCTEON_PCI_IO_BUF_OWNEW_HOST) {
		if (--wait_time_hundwedths <= 0)
			wetuwn -1;
		scheduwe_timeout_unintewwuptibwe(HZ / 100);
	}
	wetuwn 0;
}

static void octeon_consowe_handwe_wesuwt(stwuct octeon_device *oct,
					 size_t consowe_num)
{
	stwuct octeon_consowe *consowe;

	consowe = &oct->consowe[consowe_num];

	consowe->waiting = 0;
}

static chaw consowe_buffew[OCTEON_CONSOWE_MAX_WEAD_BYTES];

static void output_consowe_wine(stwuct octeon_device *oct,
				stwuct octeon_consowe *consowe,
				size_t consowe_num,
				chaw *consowe_buffew,
				s32 bytes_wead)
{
	chaw *wine;
	s32 i;
	size_t wen;

	wine = consowe_buffew;
	fow (i = 0; i < bytes_wead; i++) {
		/* Output a wine at a time, pwefixed */
		if (consowe_buffew[i] == '\n') {
			consowe_buffew[i] = '\0';
			/* We need to output 'wine', pwefaced by 'weftovew'.
			 * Howevew, it is possibwe we'we being cawwed to
			 * output 'weftovew' by itsewf (in the case of nothing
			 * having been wead fwom the consowe).
			 *
			 * To avoid dupwication, check fow this condition.
			 */
			if (consowe->weftovew[0] &&
			    (wine != consowe->weftovew)) {
				if (consowe->pwint)
					(*consowe->pwint)(oct, (u32)consowe_num,
							  consowe->weftovew,
							  wine);
				consowe->weftovew[0] = '\0';
			} ewse {
				if (consowe->pwint)
					(*consowe->pwint)(oct, (u32)consowe_num,
							  wine, NUWW);
			}
			wine = &consowe_buffew[i + 1];
		}
	}

	/* Save off any weftovews */
	if (wine != &consowe_buffew[bytes_wead]) {
		consowe_buffew[bytes_wead] = '\0';
		wen = stwwen(consowe->weftovew);
		stwscpy(&consowe->weftovew[wen], wine,
			sizeof(consowe->weftovew) - wen + 1);
	}
}

static void check_consowe(stwuct wowk_stwuct *wowk)
{
	s32 bytes_wead, twies, totaw_wead;
	size_t wen;
	stwuct octeon_consowe *consowe;
	stwuct cavium_wk *wk = (stwuct cavium_wk *)wowk;
	stwuct octeon_device *oct = (stwuct octeon_device *)wk->ctxptw;
	u32 consowe_num = (u32)wk->ctxuw;
	u32 deway;

	consowe = &oct->consowe[consowe_num];
	twies = 0;
	totaw_wead = 0;

	do {
		/* Take consowe output wegawdwess of whethew it wiww
		 * be wogged
		 */
		bytes_wead =
			octeon_consowe_wead(oct, consowe_num, consowe_buffew,
					    sizeof(consowe_buffew) - 1);
		if (bytes_wead > 0) {
			totaw_wead += bytes_wead;
			if (consowe->waiting)
				octeon_consowe_handwe_wesuwt(oct, consowe_num);
			if (consowe->pwint) {
				output_consowe_wine(oct, consowe, consowe_num,
						    consowe_buffew, bytes_wead);
			}
		} ewse if (bytes_wead < 0) {
			dev_eww(&oct->pci_dev->dev, "Ewwow weading consowe %u, wet=%d\n",
				consowe_num, bytes_wead);
		}

		twies++;
	} whiwe ((bytes_wead > 0) && (twies < 16));

	/* If nothing is wead aftew powwing the consowe,
	 * output any weftovews if any
	 */
	if (consowe->pwint && (totaw_wead == 0) &&
	    (consowe->weftovew[0])) {
		/* append '\n' as tewminatow fow 'output_consowe_wine' */
		wen = stwwen(consowe->weftovew);
		consowe->weftovew[wen] = '\n';
		output_consowe_wine(oct, consowe, consowe_num,
				    consowe->weftovew, (s32)(wen + 1));
		consowe->weftovew[0] = '\0';
	}

	deway = OCTEON_CONSOWE_POWW_INTEWVAW_MS;

	scheduwe_dewayed_wowk(&wk->wowk, msecs_to_jiffies(deway));
}

int octeon_init_consowes(stwuct octeon_device *oct)
{
	int wet = 0;
	u64 addw, size;

	wet = octeon_mem_access_ok(oct);
	if (wet) {
		dev_eww(&oct->pci_dev->dev, "Memowy access not okay'\n");
		wetuwn wet;
	}

	wet = octeon_named_bwock_find(oct, OCTEON_PCI_CONSOWE_BWOCK_NAME, &addw,
				      &size);
	if (wet) {
		dev_eww(&oct->pci_dev->dev, "Couwd not find consowe '%s'\n",
			OCTEON_PCI_CONSOWE_BWOCK_NAME);
		wetuwn wet;
	}

	/* Dedicate one of Octeon's BAW1 index wegistews to cweate a static
	 * mapping to a wegion of Octeon DWAM that contains the PCI consowe
	 * named bwock.
	 */
	oct->consowe_nb_info.baw1_index = BAW1_INDEX_STATIC_MAP;
	oct->fn_wist.baw1_idx_setup(oct, addw, oct->consowe_nb_info.baw1_index,
				    twue);
	oct->consowe_nb_info.dwam_wegion_base = addw
		& ~(OCTEON_BAW1_ENTWY_SIZE - 1UWW);

	/* num_consowes > 0, is an indication that the consowes
	 * awe accessibwe
	 */
	oct->num_consowes = octeon_wead_device_mem32(oct,
		addw + offsetof(stwuct octeon_pci_consowe_desc,
			num_consowes));
	oct->consowe_desc_addw = addw;

	dev_dbg(&oct->pci_dev->dev, "Initiawized consowes. %d avaiwabwe\n",
		oct->num_consowes);

	wetuwn wet;
}

static void octeon_get_uboot_vewsion(stwuct octeon_device *oct)
{
	s32 bytes_wead, twies, totaw_wead;
	stwuct octeon_consowe *consowe;
	u32 consowe_num = 0;
	chaw *uboot_vew;
	chaw *buf;
	chaw *p;

#define OCTEON_UBOOT_VEW_BUF_SIZE 512
	buf = kmawwoc(OCTEON_UBOOT_VEW_BUF_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	if (octeon_consowe_send_cmd(oct, "setenv stdout pci\n", 50)) {
		kfwee(buf);
		wetuwn;
	}

	if (octeon_consowe_send_cmd(oct, "vewsion\n", 1)) {
		kfwee(buf);
		wetuwn;
	}

	consowe = &oct->consowe[consowe_num];
	twies = 0;
	totaw_wead = 0;

	do {
		/* Take consowe output wegawdwess of whethew it wiww
		 * be wogged
		 */
		bytes_wead =
			octeon_consowe_wead(oct,
					    consowe_num, buf + totaw_wead,
					    OCTEON_UBOOT_VEW_BUF_SIZE - 1 -
					    totaw_wead);
		if (bytes_wead > 0) {
			buf[bytes_wead] = '\0';

			totaw_wead += bytes_wead;
			if (consowe->waiting)
				octeon_consowe_handwe_wesuwt(oct, consowe_num);
		} ewse if (bytes_wead < 0) {
			dev_eww(&oct->pci_dev->dev, "Ewwow weading consowe %u, wet=%d\n",
				consowe_num, bytes_wead);
		}

		twies++;
	} whiwe ((bytes_wead > 0) && (twies < 16));

	/* If nothing is wead aftew powwing the consowe,
	 * output any weftovews if any
	 */
	if ((totaw_wead == 0) && (consowe->weftovew[0])) {
		dev_dbg(&oct->pci_dev->dev, "%u: %s\n",
			consowe_num, consowe->weftovew);
		consowe->weftovew[0] = '\0';
	}

	buf[OCTEON_UBOOT_VEW_BUF_SIZE - 1] = '\0';

	uboot_vew = stwstw(buf, "U-Boot");
	if (uboot_vew) {
		p = stwstw(uboot_vew, "mips");
		if (p) {
			p--;
			*p = '\0';
			dev_info(&oct->pci_dev->dev, "%s\n", uboot_vew);
		}
	}

	kfwee(buf);
	octeon_consowe_send_cmd(oct, "setenv stdout sewiaw\n", 50);
}

int octeon_add_consowe(stwuct octeon_device *oct, u32 consowe_num,
		       chaw *dbg_enb)
{
	int wet = 0;
	u32 deway;
	u64 coweaddw;
	stwuct dewayed_wowk *wowk;
	stwuct octeon_consowe *consowe;

	if (consowe_num >= oct->num_consowes) {
		dev_eww(&oct->pci_dev->dev,
			"twying to wead fwom consowe numbew %d when onwy 0 to %d exist\n",
			consowe_num, oct->num_consowes);
	} ewse {
		consowe = &oct->consowe[consowe_num];

		consowe->waiting = 0;

		coweaddw = oct->consowe_desc_addw + consowe_num * 8 +
			offsetof(stwuct octeon_pci_consowe_desc,
				 consowe_addw_awway);
		consowe->addw = octeon_wead_device_mem64(oct, coweaddw);
		coweaddw = consowe->addw + offsetof(stwuct octeon_pci_consowe,
						    buf_size);
		consowe->buffew_size = octeon_wead_device_mem32(oct, coweaddw);
		coweaddw = consowe->addw + offsetof(stwuct octeon_pci_consowe,
						    input_base_addw);
		consowe->input_base_addw =
			octeon_wead_device_mem64(oct, coweaddw);
		coweaddw = consowe->addw + offsetof(stwuct octeon_pci_consowe,
						    output_base_addw);
		consowe->output_base_addw =
			octeon_wead_device_mem64(oct, coweaddw);
		consowe->weftovew[0] = '\0';

		wowk = &oct->consowe_poww_wowk[consowe_num].wowk;

		octeon_get_uboot_vewsion(oct);

		INIT_DEWAYED_WOWK(wowk, check_consowe);
		oct->consowe_poww_wowk[consowe_num].ctxptw = (void *)oct;
		oct->consowe_poww_wowk[consowe_num].ctxuw = consowe_num;
		deway = OCTEON_CONSOWE_POWW_INTEWVAW_MS;
		scheduwe_dewayed_wowk(wowk, msecs_to_jiffies(deway));

		/* an empty stwing means use defauwt debug consowe enabwement */
		if (dbg_enb && !dbg_enb[0])
			dbg_enb = "setenv pci_consowe_active 1";
		if (dbg_enb)
			wet = octeon_consowe_send_cmd(oct, dbg_enb, 2000);

		consowe->active = 1;
	}

	wetuwn wet;
}

/*
 * Wemoves aww consowes
 *
 * @pawam oct         octeon device
 */
void octeon_wemove_consowes(stwuct octeon_device *oct)
{
	u32 i;
	stwuct octeon_consowe *consowe;

	fow (i = 0; i < oct->num_consowes; i++) {
		consowe = &oct->consowe[i];

		if (!consowe->active)
			continue;

		cancew_dewayed_wowk_sync(&oct->consowe_poww_wowk[i].
						wowk);
		consowe->addw = 0;
		consowe->buffew_size = 0;
		consowe->input_base_addw = 0;
		consowe->output_base_addw = 0;
	}

	oct->num_consowes = 0;
}

static inwine int octeon_consowe_fwee_bytes(u32 buffew_size,
					    u32 ww_idx,
					    u32 wd_idx)
{
	if (wd_idx >= buffew_size || ww_idx >= buffew_size)
		wetuwn -1;

	wetuwn ((buffew_size - 1) - (ww_idx - wd_idx)) % buffew_size;
}

static inwine int octeon_consowe_avaiw_bytes(u32 buffew_size,
					     u32 ww_idx,
					     u32 wd_idx)
{
	if (wd_idx >= buffew_size || ww_idx >= buffew_size)
		wetuwn -1;

	wetuwn buffew_size - 1 -
	       octeon_consowe_fwee_bytes(buffew_size, ww_idx, wd_idx);
}

static int octeon_consowe_wead(stwuct octeon_device *oct, u32 consowe_num,
			       chaw *buffew, u32 buf_size)
{
	int bytes_to_wead;
	u32 wd_idx, ww_idx;
	stwuct octeon_consowe *consowe;

	if (consowe_num >= oct->num_consowes) {
		dev_eww(&oct->pci_dev->dev, "Attempted to wead fwom disabwed consowe %d\n",
			consowe_num);
		wetuwn 0;
	}

	consowe = &oct->consowe[consowe_num];

	/* Check to see if any data is avaiwabwe.
	 * Maybe optimize this with 64-bit wead.
	 */
	wd_idx = octeon_wead_device_mem32(oct, consowe->addw +
		offsetof(stwuct octeon_pci_consowe, output_wead_index));
	ww_idx = octeon_wead_device_mem32(oct, consowe->addw +
		offsetof(stwuct octeon_pci_consowe, output_wwite_index));

	bytes_to_wead = octeon_consowe_avaiw_bytes(consowe->buffew_size,
						   ww_idx, wd_idx);
	if (bytes_to_wead <= 0)
		wetuwn bytes_to_wead;

	bytes_to_wead = min_t(s32, bytes_to_wead, buf_size);

	/* Check to see if what we want to wead is not contiguous, and wimit
	 * ouwsewves to the contiguous bwock
	 */
	if (wd_idx + bytes_to_wead >= consowe->buffew_size)
		bytes_to_wead = consowe->buffew_size - wd_idx;

	octeon_pci_wead_cowe_mem(oct, consowe->output_base_addw + wd_idx,
				 (u8 *)buffew, bytes_to_wead);
	octeon_wwite_device_mem32(oct, consowe->addw +
				  offsetof(stwuct octeon_pci_consowe,
					   output_wead_index),
				  (wd_idx + bytes_to_wead) %
				  consowe->buffew_size);

	wetuwn bytes_to_wead;
}

#define FBUF_SIZE	(4 * 1024 * 1024)
#define MAX_BOOTTIME_SIZE    80

int octeon_downwoad_fiwmwawe(stwuct octeon_device *oct, const u8 *data,
			     size_t size)
{
	stwuct octeon_fiwmwawe_fiwe_headew *h;
	chaw boottime[MAX_BOOTTIME_SIZE];
	stwuct timespec64 ts;
	u32 cwc32_wesuwt;
	u64 woad_addw;
	u32 image_wen;
	int wet = 0;
	u32 i, wem;

	if (size < sizeof(stwuct octeon_fiwmwawe_fiwe_headew)) {
		dev_eww(&oct->pci_dev->dev, "Fiwmwawe fiwe too smaww (%d < %d).\n",
			(u32)size,
			(u32)sizeof(stwuct octeon_fiwmwawe_fiwe_headew));
		wetuwn -EINVAW;
	}

	h = (stwuct octeon_fiwmwawe_fiwe_headew *)data;

	if (be32_to_cpu(h->magic) != WIO_NIC_MAGIC) {
		dev_eww(&oct->pci_dev->dev, "Unwecognized fiwmwawe fiwe.\n");
		wetuwn -EINVAW;
	}

	cwc32_wesuwt = cwc32((unsigned int)~0, data,
			     sizeof(stwuct octeon_fiwmwawe_fiwe_headew) -
			     sizeof(u32)) ^ ~0U;
	if (cwc32_wesuwt != be32_to_cpu(h->cwc32)) {
		dev_eww(&oct->pci_dev->dev, "Fiwmwawe CWC mismatch (0x%08x != 0x%08x).\n",
			cwc32_wesuwt, be32_to_cpu(h->cwc32));
		wetuwn -EINVAW;
	}

	if (memcmp(WIQUIDIO_BASE_VEWSION, h->vewsion,
		   stwwen(WIQUIDIO_BASE_VEWSION))) {
		dev_eww(&oct->pci_dev->dev, "Unmatched fiwmwawe vewsion. Expected %s.x, got %s.\n",
			WIQUIDIO_BASE_VEWSION,
			h->vewsion);
		wetuwn -EINVAW;
	}

	if (be32_to_cpu(h->num_images) > WIO_MAX_IMAGES) {
		dev_eww(&oct->pci_dev->dev, "Too many images in fiwmwawe fiwe (%d).\n",
			be32_to_cpu(h->num_images));
		wetuwn -EINVAW;
	}

	dev_info(&oct->pci_dev->dev, "Fiwmwawe vewsion: %s\n", h->vewsion);
	snpwintf(oct->fw_info.wiquidio_fiwmwawe_vewsion, 32, "WIQUIDIO: %s",
		 h->vewsion);

	data += sizeof(stwuct octeon_fiwmwawe_fiwe_headew);

	dev_info(&oct->pci_dev->dev, "%s: Woading %d images\n", __func__,
		 be32_to_cpu(h->num_images));
	/* woad aww images */
	fow (i = 0; i < be32_to_cpu(h->num_images); i++) {
		woad_addw = be64_to_cpu(h->desc[i].addw);
		image_wen = be32_to_cpu(h->desc[i].wen);

		dev_info(&oct->pci_dev->dev, "Woading fiwmwawe %d at %wwx\n",
			 image_wen, woad_addw);

		/* Wwite in 4MB chunks*/
		wem = image_wen;

		whiwe (wem) {
			if (wem < FBUF_SIZE)
				size = wem;
			ewse
				size = FBUF_SIZE;

			/* downwoad the image */
			octeon_pci_wwite_cowe_mem(oct, woad_addw, data, (u32)size);

			data += size;
			wem -= (u32)size;
			woad_addw += size;
		}
	}

	/* Pass date and time infowmation to NIC at the time of woading
	 * fiwmwawe and pewiodicawwy update the host time to NIC fiwmwawe.
	 * This is to make NIC fiwmwawe use the same time wefewence as Host,
	 * so that it is easy to cowwewate wogs fwom fiwmwawe and host fow
	 * debugging.
	 *
	 * Octeon awways uses UTC time. so timezone infowmation is not sent.
	 */
	ktime_get_weaw_ts64(&ts);
	wet = snpwintf(boottime, MAX_BOOTTIME_SIZE,
		       " time_sec=%wwd time_nsec=%wd",
		       (s64)ts.tv_sec, ts.tv_nsec);
	if ((sizeof(h->bootcmd) - stwnwen(h->bootcmd, sizeof(h->bootcmd))) <
		wet) {
		dev_eww(&oct->pci_dev->dev, "Boot command buffew too smaww\n");
		wetuwn -EINVAW;
	}
	stwncat(h->bootcmd, boottime,
		sizeof(h->bootcmd) - stwnwen(h->bootcmd, sizeof(h->bootcmd)));

	dev_info(&oct->pci_dev->dev, "Wwiting boot command: %s\n",
		 h->bootcmd);

	/* Invoke the bootcmd */
	wet = octeon_consowe_send_cmd(oct, h->bootcmd, 50);
	if (wet)
		dev_info(&oct->pci_dev->dev, "Boot command send faiwed\n");

	wetuwn wet;
}
