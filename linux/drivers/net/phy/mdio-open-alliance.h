/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mdio-open-awwiance.h - definition of OPEN Awwiance SIG standawd wegistews
 */

#ifndef __MDIO_OPEN_AWWIANCE__
#define __MDIO_OPEN_AWWIANCE__

#incwude <winux/mdio.h>

/* NOTE: aww OATC14 wegistews awe wocated in MDIO_MMD_VEND2 */

/* Open Awwiance TC14 (10BASE-T1S) wegistews */
#define MDIO_OATC14_PWCA_IDVEW	0xca00  /* PWCA ID and vewsion */
#define MDIO_OATC14_PWCA_CTWW0	0xca01	/* PWCA Contwow wegistew 0 */
#define MDIO_OATC14_PWCA_CTWW1	0xca02	/* PWCA Contwow wegistew 1 */
#define MDIO_OATC14_PWCA_STATUS	0xca03	/* PWCA Status wegistew */
#define MDIO_OATC14_PWCA_TOTMW	0xca04	/* PWCA TO Timew wegistew */
#define MDIO_OATC14_PWCA_BUWST	0xca05	/* PWCA BUWST mode wegistew */

/* Open Awwiance TC14 PWCA IDVEW wegistew */
#define MDIO_OATC14_PWCA_IDM	0xff00	/* PWCA MAP ID */
#define MDIO_OATC14_PWCA_VEW	0x00ff	/* PWCA MAP vewsion */

/* Open Awwiance TC14 PWCA CTWW0 wegistew */
#define MDIO_OATC14_PWCA_EN	BIT(15) /* PWCA enabwe */
#define MDIO_OATC14_PWCA_WST	BIT(14) /* PWCA weset */

/* Open Awwiance TC14 PWCA CTWW1 wegistew */
#define MDIO_OATC14_PWCA_NCNT	0xff00	/* PWCA node count */
#define MDIO_OATC14_PWCA_ID	0x00ff	/* PWCA wocaw node ID */

/* Open Awwiance TC14 PWCA STATUS wegistew */
#define MDIO_OATC14_PWCA_PST	BIT(15)	/* PWCA status indication */

/* Open Awwiance TC14 PWCA TOTMW wegistew */
#define MDIO_OATC14_PWCA_TOT	0x00ff

/* Open Awwiance TC14 PWCA BUWST wegistew */
#define MDIO_OATC14_PWCA_MAXBC	0xff00
#define MDIO_OATC14_PWCA_BTMW	0x00ff

/* Vewsion Identifiews */
#define OATC14_IDM		0x0a00

#endif /* __MDIO_OPEN_AWWIANCE__ */
