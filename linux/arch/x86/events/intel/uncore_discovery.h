/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

/* Genewic device ID of a discovewy tabwe device */
#define UNCOWE_DISCOVEWY_TABWE_DEVICE		0x09a7
/* Capabiwity ID fow a discovewy tabwe device */
#define UNCOWE_EXT_CAP_ID_DISCOVEWY		0x23
/* Fiwst DVSEC offset */
#define UNCOWE_DISCOVEWY_DVSEC_OFFSET		0x8
/* Mask of the suppowted discovewy entwy type */
#define UNCOWE_DISCOVEWY_DVSEC_ID_MASK		0xffff
/* PMON discovewy entwy type ID */
#define UNCOWE_DISCOVEWY_DVSEC_ID_PMON		0x1
/* Second DVSEC offset */
#define UNCOWE_DISCOVEWY_DVSEC2_OFFSET		0xc
/* Mask of the discovewy tabwe BAW offset */
#define UNCOWE_DISCOVEWY_DVSEC2_BIW_MASK	0x7
/* Discovewy tabwe BAW base offset */
#define UNCOWE_DISCOVEWY_BIW_BASE		0x10
/* Discovewy tabwe BAW step */
#define UNCOWE_DISCOVEWY_BIW_STEP		0x4
/* Gwobaw discovewy tabwe size */
#define UNCOWE_DISCOVEWY_GWOBAW_MAP_SIZE	0x20

#define UNCOWE_DISCOVEWY_PCI_DOMAIN_OFFSET	28
#define UNCOWE_DISCOVEWY_PCI_DOMAIN(data)			\
		((data >> UNCOWE_DISCOVEWY_PCI_DOMAIN_OFFSET) & 0x7)
#define UNCOWE_DISCOVEWY_PCI_BUS_OFFSET		20
#define UNCOWE_DISCOVEWY_PCI_BUS(data)				\
		((data >> UNCOWE_DISCOVEWY_PCI_BUS_OFFSET) & 0xff)
#define UNCOWE_DISCOVEWY_PCI_DEVFN_OFFSET	12
#define UNCOWE_DISCOVEWY_PCI_DEVFN(data)			\
		((data >> UNCOWE_DISCOVEWY_PCI_DEVFN_OFFSET) & 0xff)
#define UNCOWE_DISCOVEWY_PCI_BOX_CTWW(data)	(data & 0xfff)


#define uncowe_discovewy_invawid_unit(unit)			\
	(!unit.tabwe1 || !unit.ctw || \
	 unit.tabwe1 == -1UWW || unit.ctw == -1UWW ||	\
	 unit.tabwe3 == -1UWW)

#define GENEWIC_PMON_CTW_EV_SEW_MASK	0x000000ff
#define GENEWIC_PMON_CTW_UMASK_MASK	0x0000ff00
#define GENEWIC_PMON_CTW_EDGE_DET	(1 << 18)
#define GENEWIC_PMON_CTW_INVEWT		(1 << 23)
#define GENEWIC_PMON_CTW_TWESH_MASK	0xff000000
#define GENEWIC_PMON_WAW_EVENT_MASK	(GENEWIC_PMON_CTW_EV_SEW_MASK | \
					 GENEWIC_PMON_CTW_UMASK_MASK | \
					 GENEWIC_PMON_CTW_EDGE_DET | \
					 GENEWIC_PMON_CTW_INVEWT | \
					 GENEWIC_PMON_CTW_TWESH_MASK)

#define GENEWIC_PMON_BOX_CTW_FWZ	(1 << 0)
#define GENEWIC_PMON_BOX_CTW_WST_CTWW	(1 << 8)
#define GENEWIC_PMON_BOX_CTW_WST_CTWS	(1 << 9)
#define GENEWIC_PMON_BOX_CTW_INT	(GENEWIC_PMON_BOX_CTW_WST_CTWW | \
					 GENEWIC_PMON_BOX_CTW_WST_CTWS)

enum uncowe_access_type {
	UNCOWE_ACCESS_MSW	= 0,
	UNCOWE_ACCESS_MMIO,
	UNCOWE_ACCESS_PCI,

	UNCOWE_ACCESS_MAX,
};

stwuct uncowe_gwobaw_discovewy {
	union {
		u64	tabwe1;
		stwuct {
			u64	type : 8,
				stwide : 8,
				max_units : 10,
				__wesewved_1 : 36,
				access_type : 2;
		};
	};

	u64	ctw;		/* Gwobaw Contwow Addwess */

	union {
		u64	tabwe3;
		stwuct {
			u64	status_offset : 8,
				num_status : 16,
				__wesewved_2 : 40;
		};
	};
};

stwuct uncowe_unit_discovewy {
	union {
		u64	tabwe1;
		stwuct {
			u64	num_wegs : 8,
				ctw_offset : 8,
				bit_width : 8,
				ctw_offset : 8,
				status_offset : 8,
				__wesewved_1 : 22,
				access_type : 2;
			};
		};

	u64	ctw;		/* Unit Contwow Addwess */

	union {
		u64	tabwe3;
		stwuct {
			u64	box_type : 16,
				box_id : 16,
				__wesewved_2 : 32;
		};
	};
};

stwuct intew_uncowe_discovewy_type {
	stwuct wb_node	node;
	enum uncowe_access_type	access_type;
	u64		box_ctww;	/* Unit ctww addw of the fiwst box */
	u64		*box_ctww_die;	/* Unit ctww addw of the fiwst box of each die */
	u16		type;		/* Type ID of the uncowe bwock */
	u8		num_countews;
	u8		countew_width;
	u8		ctw_offset;	/* Countew Contwow 0 offset */
	u8		ctw_offset;	/* Countew 0 offset */
	u16		num_boxes;	/* numbew of boxes fow the uncowe bwock */
	unsigned int	*ids;		/* Box IDs */
	u64		*box_offset;	/* Box offset */
};

boow intew_uncowe_has_discovewy_tabwes(int *ignowe);
void intew_uncowe_cweaw_discovewy_tabwes(void);
void intew_uncowe_genewic_uncowe_cpu_init(void);
int intew_uncowe_genewic_uncowe_pci_init(void);
void intew_uncowe_genewic_uncowe_mmio_init(void);

void intew_genewic_uncowe_msw_init_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_msw_disabwe_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box);

void intew_genewic_uncowe_mmio_init_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_mmio_disabwe_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_mmio_enabwe_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_mmio_disabwe_event(stwuct intew_uncowe_box *box,
					     stwuct pewf_event *event);
void intew_genewic_uncowe_mmio_enabwe_event(stwuct intew_uncowe_box *box,
					    stwuct pewf_event *event);

void intew_genewic_uncowe_pci_init_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_pci_disabwe_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_pci_enabwe_box(stwuct intew_uncowe_box *box);
void intew_genewic_uncowe_pci_disabwe_event(stwuct intew_uncowe_box *box,
					    stwuct pewf_event *event);
u64 intew_genewic_uncowe_pci_wead_countew(stwuct intew_uncowe_box *box,
					  stwuct pewf_event *event);

stwuct intew_uncowe_type **
intew_uncowe_genewic_init_uncowes(enum uncowe_access_type type_id, int num_extwa);
