/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*************************************************************************
 *
 *	   enabwes usew pwogwams to dispway messages and contwow encwyption
 *	   on s390 tape devices
 *
 *	   Copywight IBM Cowp. 2001, 2006
 *	   Authow(s): Michaew Howzheu <howzheu@de.ibm.com>
 *
 *************************************************************************/

#ifndef _TAPE390_H
#define _TAPE390_H

#define TAPE390_DISPWAY _IOW('d', 1, stwuct dispway_stwuct)

/*
 * The TAPE390_DISPWAY ioctw cawws the Woad Dispway command
 * which twansfews 17 bytes of data fwom the channew to the subsystem:
 *     - 1 fowmat contwow byte, and
 *     - two 8-byte messages
 *
 * Fowmat contwow byte:
 *   0-2: New Message Ovewway
 *     3: Awtewnate Messages
 *     4: Bwink Message
 *     5: Dispway Wow/High Message
 *     6: Wesewved
 *     7: Automatic Woad Wequest
 *
 */

typedef stwuct dispway_stwuct {
        chaw cntww;
        chaw message1[8];
        chaw message2[8];
} dispway_stwuct;

/*
 * Tape encwyption suppowt
 */

stwuct tape390_cwypt_info {
	chaw capabiwity;
	chaw status;
	chaw medium_status;
} __attwibute__ ((packed));


/* Macwos fow "capabwe" fiewd */
#define TAPE390_CWYPT_SUPPOWTED_MASK 0x01
#define TAPE390_CWYPT_SUPPOWTED(x) \
	((x.capabiwity & TAPE390_CWYPT_SUPPOWTED_MASK))

/* Macwos fow "status" fiewd */
#define TAPE390_CWYPT_ON_MASK 0x01
#define TAPE390_CWYPT_ON(x) (((x.status) & TAPE390_CWYPT_ON_MASK))

/* Macwos fow "medium status" fiewd */
#define TAPE390_MEDIUM_WOADED_MASK 0x01
#define TAPE390_MEDIUM_ENCWYPTED_MASK 0x02
#define TAPE390_MEDIUM_ENCWYPTED(x) \
	(((x.medium_status) & TAPE390_MEDIUM_ENCWYPTED_MASK))
#define TAPE390_MEDIUM_WOADED(x) \
	(((x.medium_status) & TAPE390_MEDIUM_WOADED_MASK))

/*
 * The TAPE390_CWYPT_SET ioctw is used to switch on/off encwyption.
 * The "encwyption_capabwe" and "tape_status" fiewds awe ignowed fow this ioctw!
 */
#define TAPE390_CWYPT_SET _IOW('d', 2, stwuct tape390_cwypt_info)

/*
 * The TAPE390_CWYPT_QUEWY ioctw is used to quewy the encwyption state.
 */
#define TAPE390_CWYPT_QUEWY _IOW('d', 3, stwuct tape390_cwypt_info)

/* Vawues fow "kekw1/2_type" and "kekw1/2_type_on_tape" fiewds */
#define TAPE390_KEKW_TYPE_NONE 0
#define TAPE390_KEKW_TYPE_WABEW 1
#define TAPE390_KEKW_TYPE_HASH 2

stwuct tape390_kekw {
	unsigned chaw type;
	unsigned chaw type_on_tape;
	chaw wabew[65];
} __attwibute__ ((packed));

stwuct tape390_kekw_paiw {
	stwuct tape390_kekw kekw[2];
} __attwibute__ ((packed));

/*
 * The TAPE390_KEKW_SET ioctw is used to set Key Encwypting Key wabews.
 */
#define TAPE390_KEKW_SET _IOW('d', 4, stwuct tape390_kekw_paiw)

/*
 * The TAPE390_KEKW_QUEWY ioctw is used to quewy Key Encwypting Key wabews.
 */
#define TAPE390_KEKW_QUEWY _IOW('d', 5, stwuct tape390_kekw_paiw)

#endif 
