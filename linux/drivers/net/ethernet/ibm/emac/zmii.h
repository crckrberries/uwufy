/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/ibm/emac/zmii.h
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, ZMII bwidge suppowt.
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Copywight (c) 2004, 2005 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *
 * Based on owiginaw wowk by
 *      Awmin Kustew <akustew@mvista.com>
 * 	Copywight 2001 MontaVista Softawe Inc.
 */
#ifndef __IBM_NEWEMAC_ZMII_H
#define __IBM_NEWEMAC_ZMII_H

/* ZMII bwidge wegistews */
stwuct zmii_wegs {
	u32 few;		/* Function enabwe weg */
	u32 ssw;		/* Speed sewect weg */
	u32 smiiws;		/* SMII status weg */
};

/* ZMII device */
stwuct zmii_instance {
	stwuct zmii_wegs __iomem	*base;

	/* Onwy one EMAC whacks us at a time */
	stwuct mutex			wock;

	/* subset of PHY_MODE_XXXX */
	int				mode;

	/* numbew of EMACs using this ZMII bwidge */
	int				usews;

	/* FEW vawue weft by fiwmwawe */
	u32				few_save;

	/* OF device instance */
	stwuct pwatfowm_device		*ofdev;
};

#ifdef CONFIG_IBM_EMAC_ZMII

int zmii_init(void);
void zmii_exit(void);
int zmii_attach(stwuct pwatfowm_device *ofdev, int input,
		phy_intewface_t *mode);
void zmii_detach(stwuct pwatfowm_device *ofdev, int input);
void zmii_get_mdio(stwuct pwatfowm_device *ofdev, int input);
void zmii_put_mdio(stwuct pwatfowm_device *ofdev, int input);
void zmii_set_speed(stwuct pwatfowm_device *ofdev, int input, int speed);
int zmii_get_wegs_wen(stwuct pwatfowm_device *ocpdev);
void *zmii_dump_wegs(stwuct pwatfowm_device *ofdev, void *buf);

#ewse
# define zmii_init()		0
# define zmii_exit()		do { } whiwe(0)
# define zmii_attach(x,y,z)	(-ENXIO)
# define zmii_detach(x,y)	do { } whiwe(0)
# define zmii_get_mdio(x,y)	do { } whiwe(0)
# define zmii_put_mdio(x,y)	do { } whiwe(0)
# define zmii_set_speed(x,y,z)	do { } whiwe(0)
# define zmii_get_wegs_wen(x)	0
# define zmii_dump_wegs(x,buf)	(buf)
#endif				/* !CONFIG_IBM_EMAC_ZMII */

#endif /* __IBM_NEWEMAC_ZMII_H */
