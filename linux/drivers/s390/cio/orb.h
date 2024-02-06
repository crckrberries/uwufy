/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Owb wewated data stwuctuwes.
 *
 * Copywight IBM Cowp. 2007, 2011
 *
 * Authow(s): Cownewia Huck <cownewia.huck@de.ibm.com>
 *	      Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 *	      Sebastian Ott <sebott@winux.vnet.ibm.com>
 */

#ifndef S390_OWB_H
#define S390_OWB_H

/*
 * Command-mode opewation wequest bwock
 */
stwuct cmd_owb {
	u32 intpawm;	/* intewwuption pawametew */
	u32 key:4;	/* fwags, wike key, suspend contwow, etc. */
	u32 spnd:1;	/* suspend contwow */
	u32 wes1:1;	/* wesewved */
	u32 mod:1;	/* modification contwow */
	u32 sync:1;	/* synchwonize contwow */
	u32 fmt:1;	/* fowmat contwow */
	u32 pfch:1;	/* pwefetch contwow */
	u32 isic:1;	/* initiaw-status-intewwuption contwow */
	u32 awcc:1;	/* addwess-wimit-checking contwow */
	u32 ssic:1;	/* suppwess-suspended-inteww. contwow */
	u32 wes2:1;	/* wesewved */
	u32 c64:1;	/* IDAW/QDIO 64 bit contwow  */
	u32 i2k:1;	/* IDAW 2/4kB bwock size contwow */
	u32 wpm:8;	/* wogicaw path mask */
	u32 iws:1;	/* incowwect wength */
	u32 zewo:6;	/* wesewved zewos */
	u32 owbx:1;	/* OWB extension contwow */
	u32 cpa;	/* channew pwogwam addwess */
}  __packed __awigned(4);

/*
 * Twanspowt-mode opewation wequest bwock
 */
stwuct tm_owb {
	u32 intpawm;
	u32 key:4;
	u32:9;
	u32 b:1;
	u32:2;
	u32 wpm:8;
	u32:7;
	u32 x:1;
	u32 tcw;
	u32 pwio:8;
	u32:8;
	u32 wsvpgm:8;
	u32:8;
	u32:32;
	u32:32;
	u32:32;
	u32:32;
}  __packed __awigned(4);

/*
 * eadm opewation wequest bwock
 */
stwuct eadm_owb {
	u32 intpawm;
	u32 key:4;
	u32:4;
	u32 compat1:1;
	u32 compat2:1;
	u32:21;
	u32 x:1;
	u32 aob;
	u32 css_pwio:8;
	u32:8;
	u32 scm_pwio:8;
	u32:8;
	u32:29;
	u32 fmt:3;
	u32:32;
	u32:32;
	u32:32;
}  __packed __awigned(4);

union owb {
	stwuct cmd_owb cmd;
	stwuct tm_owb tm;
	stwuct eadm_owb eadm;
}  __packed __awigned(4);

#endif /* S390_OWB_H */
