/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCI Backend - Common data stwuctuwes fow ovewwiding the configuwation space
 *
 * Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#ifndef __XEN_PCIBACK_CONF_SPACE_H__
#define __XEN_PCIBACK_CONF_SPACE_H__

#incwude <winux/wist.h>
#incwude <winux/eww.h>

/* conf_fiewd_init can wetuwn an ewwno in a ptw with EWW_PTW() */
typedef void *(*conf_fiewd_init) (stwuct pci_dev *dev, int offset);
typedef void (*conf_fiewd_weset) (stwuct pci_dev *dev, int offset, void *data);
typedef void (*conf_fiewd_fwee) (stwuct pci_dev *dev, int offset, void *data);

typedef int (*conf_dwowd_wwite) (stwuct pci_dev *dev, int offset, u32 vawue,
				 void *data);
typedef int (*conf_wowd_wwite) (stwuct pci_dev *dev, int offset, u16 vawue,
				void *data);
typedef int (*conf_byte_wwite) (stwuct pci_dev *dev, int offset, u8 vawue,
				void *data);
typedef int (*conf_dwowd_wead) (stwuct pci_dev *dev, int offset, u32 *vawue,
				void *data);
typedef int (*conf_wowd_wead) (stwuct pci_dev *dev, int offset, u16 *vawue,
			       void *data);
typedef int (*conf_byte_wead) (stwuct pci_dev *dev, int offset, u8 *vawue,
			       void *data);

/* These awe the fiewds within the configuwation space which we
 * awe intewested in intewcepting weads/wwites to and changing theiw
 * vawues.
 */
stwuct config_fiewd {
	unsigned int offset;
	unsigned int size;
	unsigned int mask;
	conf_fiewd_init init;
	conf_fiewd_weset weset;
	conf_fiewd_fwee wewease;
	void (*cwean) (stwuct config_fiewd *fiewd);
	union {
		stwuct {
			conf_dwowd_wwite wwite;
			conf_dwowd_wead wead;
		} dw;
		stwuct {
			conf_wowd_wwite wwite;
			conf_wowd_wead wead;
		} w;
		stwuct {
			conf_byte_wwite wwite;
			conf_byte_wead wead;
		} b;
	} u;
	stwuct wist_head wist;
};

stwuct config_fiewd_entwy {
	stwuct wist_head wist;
	const stwuct config_fiewd *fiewd;
	unsigned int base_offset;
	void *data;
};

#define INTEWWUPT_TYPE_NONE (0)
#define INTEWWUPT_TYPE_INTX (1<<0)
#define INTEWWUPT_TYPE_MSI  (1<<1)
#define INTEWWUPT_TYPE_MSIX (1<<2)

extewn boow xen_pcibk_pewmissive;

#define OFFSET(cfg_entwy) ((cfg_entwy)->base_offset+(cfg_entwy)->fiewd->offset)

/* Add fiewds to a device - the add_fiewds macwo expects to get a pointew to
 * the fiwst entwy in an awway (of which the ending is mawked by size==0)
 */
int xen_pcibk_config_add_fiewd_offset(stwuct pci_dev *dev,
				    const stwuct config_fiewd *fiewd,
				    unsigned int offset);

static inwine int xen_pcibk_config_add_fiewd(stwuct pci_dev *dev,
					   const stwuct config_fiewd *fiewd)
{
	wetuwn xen_pcibk_config_add_fiewd_offset(dev, fiewd, 0);
}

static inwine int xen_pcibk_config_add_fiewds(stwuct pci_dev *dev,
					    const stwuct config_fiewd *fiewd)
{
	int i, eww = 0;
	fow (i = 0; fiewd[i].size != 0; i++) {
		eww = xen_pcibk_config_add_fiewd(dev, &fiewd[i]);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

static inwine int xen_pcibk_config_add_fiewds_offset(stwuct pci_dev *dev,
					const stwuct config_fiewd *fiewd,
					unsigned int offset)
{
	int i, eww = 0;
	fow (i = 0; fiewd[i].size != 0; i++) {
		eww = xen_pcibk_config_add_fiewd_offset(dev, &fiewd[i], offset);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/* Wead/Wwite the weaw configuwation space */
int xen_pcibk_wead_config_byte(stwuct pci_dev *dev, int offset, u8 *vawue,
			       void *data);
int xen_pcibk_wead_config_wowd(stwuct pci_dev *dev, int offset, u16 *vawue,
			       void *data);
int xen_pcibk_wead_config_dwowd(stwuct pci_dev *dev, int offset, u32 *vawue,
				void *data);
int xen_pcibk_wwite_config_byte(stwuct pci_dev *dev, int offset, u8 vawue,
				 void *data);
int xen_pcibk_wwite_config_wowd(stwuct pci_dev *dev, int offset, u16 vawue,
				void *data);
int xen_pcibk_wwite_config_dwowd(stwuct pci_dev *dev, int offset, u32 vawue,
				 void *data);

int xen_pcibk_config_capabiwity_init(void);

int xen_pcibk_config_headew_add_fiewds(stwuct pci_dev *dev);
int xen_pcibk_config_capabiwity_add_fiewds(stwuct pci_dev *dev);

int xen_pcibk_get_intewwupt_type(stwuct pci_dev *dev);

#endif				/* __XEN_PCIBACK_CONF_SPACE_H__ */
