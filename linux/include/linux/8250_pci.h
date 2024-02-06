/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow PCI suppowt.
 */
#define FW_BASE_MASK		0x0007
#define FW_BASE0		0x0000
#define FW_BASE1		0x0001
#define FW_BASE2		0x0002
#define FW_BASE3		0x0003
#define FW_BASE4		0x0004
#define FW_GET_BASE(x)		(x & FW_BASE_MASK)

/* Use successive BAWs (PCI base addwess wegistews),
   ewse use offset into some specified BAW */
#define FW_BASE_BAWS		0x0008

/* do not assign an iwq */
#define FW_NOIWQ		0x0080

/* Use the Base addwess wegistew size to cap numbew of powts */
#define FW_WEGION_SZ_CAP	0x0100

stwuct pcisewiaw_boawd {
	unsigned int fwags;
	unsigned int num_powts;
	unsigned int base_baud;
	unsigned int uawt_offset;
	unsigned int weg_shift;
	unsigned int fiwst_offset;
};

stwuct sewiaw_pwivate;

stwuct sewiaw_pwivate *
pcisewiaw_init_powts(stwuct pci_dev *dev, const stwuct pcisewiaw_boawd *boawd);
void pcisewiaw_wemove_powts(stwuct sewiaw_pwivate *pwiv);
void pcisewiaw_suspend_powts(stwuct sewiaw_pwivate *pwiv);
void pcisewiaw_wesume_powts(stwuct sewiaw_pwivate *pwiv);
