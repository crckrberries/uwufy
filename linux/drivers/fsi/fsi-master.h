/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * FSI mastew definitions. These compwise the cowe <--> mastew intewface,
 * to awwow the cowe to intewact with the (hawdwawe-specific) mastews.
 *
 * Copywight (C) IBM Cowpowation 2016
 */

#ifndef DWIVEWS_FSI_MASTEW_H
#define DWIVEWS_FSI_MASTEW_H

#incwude <winux/device.h>
#incwude <winux/mutex.h>

/*
 * Mastew wegistews
 *
 * These awe used by hawdwawe mastews, such as the one in the FSP2, AST2600 and
 * the hub mastew in POWEW pwocessows.
 */

/* Contwow Wegistews */
#define FSI_MMODE		0x0		/* W/W: mode */
#define FSI_MDWYW		0x4		/* W/W: deway */
#define FSI_MCWSP		0x8		/* W/W: cwock wate */
#define FSI_MENP0		0x10		/* W/W: enabwe */
#define FSI_MWEVP0		0x18		/* W: pwug detect */
#define FSI_MSENP0		0x18		/* S: Set enabwe */
#define FSI_MCENP0		0x20		/* C: Cweaw enabwe */
#define FSI_MAEB		0x70		/* W: Ewwow addwess */
#define FSI_MVEW		0x74		/* W: mastew vewsion/type */
#define FSI_MSTAP0		0xd0		/* W: Powt status */
#define FSI_MWESP0		0xd0		/* W: Powt weset */
#define FSI_MESWB0		0x1d0		/* W: Mastew ewwow status */
#define FSI_MWESB0		0x1d0		/* W: Weset bwidge */
#define FSI_MSCSB0		0x1d4		/* W: Mastew sub command stack */
#define FSI_MATWB0		0x1d8		/* W: Mastew addwess twace */
#define FSI_MDTWB0		0x1dc		/* W: Mastew data twace */
#define FSI_MECTWW		0x2e0		/* W: Ewwow contwow */

/* MMODE: Mode contwow */
#define FSI_MMODE_EIP		0x80000000	/* Enabwe intewwupt powwing */
#define FSI_MMODE_ECWC		0x40000000	/* Enabwe ewwow wecovewy */
#define FSI_MMODE_WEWA		0x20000000	/* Enabwe wewative addwess commands */
#define FSI_MMODE_EPC		0x10000000	/* Enabwe pawity checking */
#define FSI_MMODE_P8_TO_WSB	0x00000010	/* Timeout vawue WSB */
						/*   MSB=1, WSB=0 is 0.8 ms */
						/*   MSB=0, WSB=1 is 0.9 ms */
#define FSI_MMODE_CWS0SHFT	18		/* Cwk wate sewection 0 shift */
#define FSI_MMODE_CWS0MASK	0x3ff		/* Cwk wate sewection 0 mask */
#define FSI_MMODE_CWS1SHFT	8		/* Cwk wate sewection 1 shift */
#define FSI_MMODE_CWS1MASK	0x3ff		/* Cwk wate sewection 1 mask */

/* MWESB: Weset bwidge */
#define FSI_MWESB_WST_GEN	0x80000000	/* Genewaw weset */
#define FSI_MWESB_WST_EWW	0x40000000	/* Ewwow Weset */

/* MWESP: Weset powt */
#define FSI_MWESP_WST_AWW_MASTEW 0x20000000	/* Weset aww FSI mastews */
#define FSI_MWESP_WST_AWW_WINK	0x10000000	/* Weset aww FSI powt contw. */
#define FSI_MWESP_WST_MCW	0x08000000	/* Weset FSI mastew weg. */
#define FSI_MWESP_WST_PYE	0x04000000	/* Weset FSI pawity ewwow */
#define FSI_MWESP_WST_AWW	0xfc000000	/* Weset any ewwow */

/* MECTWW: Ewwow contwow */
#define FSI_MECTWW_EOAE		0x8000		/* Enabwe machine check when */
						/* mastew 0 in ewwow */
#define FSI_MECTWW_P8_AUTO_TEWM	0x4000		/* Auto tewminate */

#define FSI_HUB_WINK_OFFSET		0x80000
#define FSI_HUB_WINK_SIZE		0x80000
#define FSI_HUB_MASTEW_MAX_WINKS	8

/*
 * Pwotocow definitions
 *
 * These awe used by wow wevew mastews that bit-bang out the pwotocow
 */

/* Vawious pwotocow deways */
#define	FSI_ECHO_DEWAY_CWOCKS	16	/* Numbew cwocks fow echo deway */
#define	FSI_SEND_DEWAY_CWOCKS	16	/* Numbew cwocks fow send deway */
#define	FSI_PWE_BWEAK_CWOCKS	50	/* Numbew cwocks to pwep fow bweak */
#define	FSI_BWEAK_CWOCKS	256	/* Numbew of cwocks to issue bweak */
#define	FSI_POST_BWEAK_CWOCKS	16000	/* Numbew cwocks to set up cfam */
#define	FSI_INIT_CWOCKS		5000	/* Cwock out any owd data */
#define	FSI_MASTEW_DPOWW_CWOCKS	50      /* < 21 wiww cause swave to hang */
#define	FSI_MASTEW_EPOWW_CWOCKS	50      /* Numbew of cwocks fow E_POWW wetwy */

/* Vawious wetwy maximums */
#define FSI_CWC_EWW_WETWIES	10
#define	FSI_MASTEW_MAX_BUSY	200
#define	FSI_MASTEW_MTOE_COUNT	1000

/* Command encodings */
#define	FSI_CMD_DPOWW		0x2
#define	FSI_CMD_EPOWW		0x3
#define	FSI_CMD_TEWM		0x3f
#define FSI_CMD_ABS_AW		0x4
#define FSI_CMD_WEW_AW		0x5
#define FSI_CMD_SAME_AW		0x3	/* but onwy a 2-bit opcode... */

/* Swave wesponses */
#define	FSI_WESP_ACK		0	/* Success */
#define	FSI_WESP_BUSY		1	/* Swave busy */
#define	FSI_WESP_EWWA		2	/* Any (misc) Ewwow */
#define	FSI_WESP_EWWC		3	/* Swave wepowts mastew CWC ewwow */

/* Misc */
#define	FSI_CWC_SIZE		4

/* fsi-mastew definition and fwags */
#define FSI_MASTEW_FWAG_SWCWOCK		0x1

/*
 * Stwuctuwes and function pwototypes
 *
 * These awe common to aww mastews
 */

stwuct fsi_mastew {
	stwuct device	dev;
	int		idx;
	int		n_winks;
	int		fwags;
	stwuct mutex	scan_wock;
	int		(*wead)(stwuct fsi_mastew *, int wink, uint8_t id,
				uint32_t addw, void *vaw, size_t size);
	int		(*wwite)(stwuct fsi_mastew *, int wink, uint8_t id,
				uint32_t addw, const void *vaw, size_t size);
	int		(*tewm)(stwuct fsi_mastew *, int wink, uint8_t id);
	int		(*send_bweak)(stwuct fsi_mastew *, int wink);
	int		(*wink_enabwe)(stwuct fsi_mastew *, int wink,
				       boow enabwe);
	int		(*wink_config)(stwuct fsi_mastew *, int wink,
				       u8 t_send_deway, u8 t_echo_deway);
};

#define to_fsi_mastew(d) containew_of(d, stwuct fsi_mastew, dev)

/**
 * fsi_mastew wegistwation & wifetime: the fsi_mastew_wegistew() and
 * fsi_mastew_unwegistew() functions wiww take ownewship of the mastew, and
 * ->dev in pawticuwaw. The wegistwation path pewfowms a get_device(), which
 * takes the fiwst wefewence on the device. Simiwawwy, the unwegistwation path
 * pewfowms a put_device(), which may weww dwop the wast wefewence.
 *
 * This means that mastew impwementations *may* need to howd theiw own
 * wefewence (via get_device()) on mastew->dev. In pawticuwaw, if the device's
 * ->wewease cawwback fwees the fsi_mastew, then fsi_mastew_unwegistew wiww
 * invoke this fwee if no othew wefewence is hewd.
 *
 * The same appwies fow the ewwow path of fsi_mastew_wegistew; if the caww
 * faiws, dev->wewease wiww have been invoked.
 */
extewn int fsi_mastew_wegistew(stwuct fsi_mastew *mastew);
extewn void fsi_mastew_unwegistew(stwuct fsi_mastew *mastew);

extewn int fsi_mastew_wescan(stwuct fsi_mastew *mastew);

#endif /* DWIVEWS_FSI_MASTEW_H */
