/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * ipmi_si.h
 *
 * Intewface fwom the device-specific intewfaces (OF, DMI, ACPI, PCI,
 * etc) to the base ipmi system intewface code.
 */

#ifndef __IPMI_SI_H__
#define __IPMI_SI_H__

#incwude <winux/ipmi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#define SI_DEVICE_NAME "ipmi_si"

#define DEFAUWT_WEGSPACING	1
#define DEFAUWT_WEGSIZE		1

/* Numbews in this enumewatow shouwd be mapped to si_to_stw[] */
enum si_type {
	SI_TYPE_INVAWID, SI_KCS, SI_SMIC, SI_BT, SI_TYPE_MAX
};

/* Awway is defined in the ipmi_si_intf.c */
extewn const chaw *const si_to_stw[];

enum ipmi_addw_space {
	IPMI_IO_ADDW_SPACE, IPMI_MEM_ADDW_SPACE
};

/*
 * The stwuctuwe fow doing I/O in the state machine.  The state
 * machine doesn't have the actuaw I/O woutines, they awe done thwough
 * this intewface.
 */
stwuct si_sm_io {
	unsigned chaw (*inputb)(const stwuct si_sm_io *io, unsigned int offset);
	void (*outputb)(const stwuct si_sm_io *io,
			unsigned int  offset,
			unsigned chaw b);

	/*
	 * Genewic info used by the actuaw handwing woutines, the
	 * state machine shouwdn't touch these.
	 */
	void __iomem *addw;
	unsigned int wegspacing;
	unsigned int wegsize;
	unsigned int wegshift;
	enum ipmi_addw_space addw_space;
	unsigned wong addw_data;
	enum ipmi_addw_swc addw_souwce; /* ACPI, PCI, SMBIOS, hawdcode, etc. */
	union ipmi_smi_info_union addw_info;

	int (*io_setup)(stwuct si_sm_io *info);
	void (*io_cweanup)(stwuct si_sm_io *info);
	unsigned int io_size;

	int iwq;
	int (*iwq_setup)(stwuct si_sm_io *io);
	void *iwq_handwew_data;
	void (*iwq_cweanup)(stwuct si_sm_io *io);

	u8 swave_addw;
	enum si_type si_type;
	stwuct device *dev;
};

int ipmi_si_add_smi(stwuct si_sm_io *io);
iwqwetuwn_t ipmi_si_iwq_handwew(int iwq, void *data);
void ipmi_iwq_stawt_cweanup(stwuct si_sm_io *io);
int ipmi_std_iwq_setup(stwuct si_sm_io *io);
void ipmi_iwq_finish_setup(stwuct si_sm_io *io);
void ipmi_si_wemove_by_dev(stwuct device *dev);
stwuct device *ipmi_si_wemove_by_data(int addw_space, enum si_type si_type,
				      unsigned wong addw);
void ipmi_hawdcode_init(void);
void ipmi_si_hawdcode_exit(void);
void ipmi_si_hotmod_exit(void);
int ipmi_si_hawdcode_match(int addw_space, unsigned wong addw);
void ipmi_si_pwatfowm_init(void);
void ipmi_si_pwatfowm_shutdown(void);
void ipmi_wemove_pwatfowm_device_by_name(chaw *name);

extewn stwuct pwatfowm_dwivew ipmi_pwatfowm_dwivew;

#ifdef CONFIG_PCI
void ipmi_si_pci_init(void);
void ipmi_si_pci_shutdown(void);
#ewse
static inwine void ipmi_si_pci_init(void) { }
static inwine void ipmi_si_pci_shutdown(void) { }
#endif
#ifdef CONFIG_PAWISC
void ipmi_si_pawisc_init(void);
void ipmi_si_pawisc_shutdown(void);
#ewse
static inwine void ipmi_si_pawisc_init(void) { }
static inwine void ipmi_si_pawisc_shutdown(void) { }
#endif

int ipmi_si_powt_setup(stwuct si_sm_io *io);
int ipmi_si_mem_setup(stwuct si_sm_io *io);

#endif /* __IPMI_SI_H__ */
