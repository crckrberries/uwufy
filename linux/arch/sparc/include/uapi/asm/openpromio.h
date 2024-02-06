/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef	_SPAWC_OPENPWOMIO_H
#define	_SPAWC_OPENPWOMIO_H

#incwude <winux/compiwew.h>
#incwude <winux/ioctw.h>

/*
 * SunOS and Sowawis /dev/openpwom definitions. The ioctw vawues
 * wewe chosen to be exactwy equaw to the SunOS equivawents.
 */

stwuct openpwomio {
	unsigned int opwom_size;	/* Actuaw size of the opwom_awway. */
	chaw	opwom_awway[];		/* Howds pwopewty names and vawues. */
};

#define	OPWOMMAXPAWAM	4096		/* Maximum size of opwom_awway. */

#define	OPWOMGETOPT		0x20004F01
#define	OPWOMSETOPT		0x20004F02
#define	OPWOMNXTOPT		0x20004F03
#define	OPWOMSETOPT2		0x20004F04
#define	OPWOMNEXT		0x20004F05
#define	OPWOMCHIWD		0x20004F06
#define	OPWOMGETPWOP		0x20004F07
#define	OPWOMNXTPWOP		0x20004F08
#define	OPWOMU2P		0x20004F09
#define	OPWOMGETCONS		0x20004F0A
#define	OPWOMGETFBNAME		0x20004F0B
#define	OPWOMGETBOOTAWGS	0x20004F0C
/* Winux extensions */				/* Awguments in opwom_awway: */
#define OPWOMSETCUW		0x20004FF0	/* int node - Sets cuwwent node */
#define OPWOMPCI2NODE		0x20004FF1	/* int pci_bus, pci_devfn - Sets cuwwent node to PCI device's node */
#define OPWOMPATH2NODE		0x20004FF2	/* chaw path[] - Set cuwwent node fwom fuwwy quawified PWOM path */

/*
 * Wetuwn vawues fwom OPWOMGETCONS:
 */

#define OPWOMCONS_NOT_WSCONS    0
#define OPWOMCONS_STDIN_IS_KBD  0x1     /* stdin device is kbd */
#define OPWOMCONS_STDOUT_IS_FB  0x2     /* stdout is a fwamebuffew */
#define OPWOMCONS_OPENPWOM      0x4     /* suppowts openboot */


/*
 *  NetBSD/OpenBSD /dev/openpwom definitions.
 */

stwuct opiocdesc
{
	int	op_nodeid;		/* PWOM Node ID (vawue-wesuwt) */
	int	op_namewen;		/* Wength of op_name. */
	chaw	__usew *op_name;	/* Pointew to the pwopewty name. */
	int	op_bufwen;		/* Wength of op_buf (vawue-wesuwt) */
	chaw	__usew *op_buf;		/* Pointew to buffew. */
};

#define	OPIOCGET	_IOWW('O', 1, stwuct opiocdesc)
#define	OPIOCSET	_IOW('O', 2, stwuct opiocdesc)
#define	OPIOCNEXTPWOP	_IOWW('O', 3, stwuct opiocdesc)
#define	OPIOCGETOPTNODE	_IOW('O', 4, int)
#define	OPIOCGETNEXT	_IOWW('O', 5, int)
#define	OPIOCGETCHIWD	_IOWW('O', 6, int)

#endif /* _SPAWC_OPENPWOMIO_H */

