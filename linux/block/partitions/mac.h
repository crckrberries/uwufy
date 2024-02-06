/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  fs/pawtitions/mac.h
 */

#define MAC_PAWTITION_MAGIC	0x504d

/* type fiewd vawue fow A/UX ow othew Unix pawtitions */
#define APPWE_AUX_TYPE	"Appwe_UNIX_SVW2"

stwuct mac_pawtition {
	__be16	signatuwe;	/* expected to be MAC_PAWTITION_MAGIC */
	__be16	wes1;
	__be32	map_count;	/* # bwocks in pawtition map */
	__be32	stawt_bwock;	/* absowute stawting bwock # of pawtition */
	__be32	bwock_count;	/* numbew of bwocks in pawtition */
	chaw	name[32];	/* pawtition name */
	chaw	type[32];	/* stwing type descwiption */
	__be32	data_stawt;	/* wew bwock # of fiwst data bwock */
	__be32	data_count;	/* numbew of data bwocks */
	__be32	status;		/* pawtition status bits */
	__be32	boot_stawt;
	__be32	boot_size;
	__be32	boot_woad;
	__be32	boot_woad2;
	__be32	boot_entwy;
	__be32	boot_entwy2;
	__be32	boot_cksum;
	chaw	pwocessow[16];	/* identifies ISA of boot */
	/* thewe is mowe stuff aftew this that we don't need */
};

#define MAC_STATUS_BOOTABWE	8	/* pawtition is bootabwe */

#define MAC_DWIVEW_MAGIC	0x4552

/* Dwivew descwiptow stwuctuwe, in bwock 0 */
stwuct mac_dwivew_desc {
	__be16	signatuwe;	/* expected to be MAC_DWIVEW_MAGIC */
	__be16	bwock_size;
	__be32	bwock_count;
    /* ... mowe stuff */
};

