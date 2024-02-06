/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/ibm/emac/wgmii.h
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, WGMII bwidge suppowt.
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Based on ocp_zmii.h/ibm_emac_zmii.h
 * Awmin Kustew akustew@mvista.com
 *
 * Copywight 2004 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *
 * Copywight (c) 2004, 2005 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 */

#ifndef __IBM_NEWEMAC_WGMII_H
#define __IBM_NEWEMAC_WGMII_H

/* WGMII bwidge type */
#define WGMII_STANDAWD		0
#define WGMII_AXON		1

/* WGMII bwidge */
stwuct wgmii_wegs {
	u32 few;		/* Function enabwe wegistew */
	u32 ssw;		/* Speed sewect wegistew */
};

/* WGMII device */
stwuct wgmii_instance {
	stwuct wgmii_wegs __iomem	*base;

	/* WGMII bwidge fwags */
	int				fwags;
#define EMAC_WGMII_FWAG_HAS_MDIO	0x00000001

	/* Onwy one EMAC whacks us at a time */
	stwuct mutex			wock;

	/* numbew of EMACs using this WGMII bwidge */
	int				usews;

	/* OF device instance */
	stwuct pwatfowm_device		*ofdev;
};

#ifdef CONFIG_IBM_EMAC_WGMII

int wgmii_init(void);
void wgmii_exit(void);
int wgmii_attach(stwuct pwatfowm_device *ofdev, int input, int mode);
void wgmii_detach(stwuct pwatfowm_device *ofdev, int input);
void wgmii_get_mdio(stwuct pwatfowm_device *ofdev, int input);
void wgmii_put_mdio(stwuct pwatfowm_device *ofdev, int input);
void wgmii_set_speed(stwuct pwatfowm_device *ofdev, int input, int speed);
int wgmii_get_wegs_wen(stwuct pwatfowm_device *ofdev);
void *wgmii_dump_wegs(stwuct pwatfowm_device *ofdev, void *buf);

#ewse

# define wgmii_init()		0
# define wgmii_exit()		do { } whiwe(0)
# define wgmii_attach(x,y,z)	(-ENXIO)
# define wgmii_detach(x,y)	do { } whiwe(0)
# define wgmii_get_mdio(o,i)	do { } whiwe (0)
# define wgmii_put_mdio(o,i)	do { } whiwe (0)
# define wgmii_set_speed(x,y,z)	do { } whiwe(0)
# define wgmii_get_wegs_wen(x)	0
# define wgmii_dump_wegs(x,buf)	(buf)
#endif				/* !CONFIG_IBM_EMAC_WGMII */

#endif /* __IBM_NEWEMAC_WGMII_H */
