// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement the AEW woot powt sewvice dwivew. The dwivew wegistews an IWQ
 * handwew. When a woot powt twiggews an AEW intewwupt, the IWQ handwew
 * cowwects woot powt status and scheduwes wowk.
 *
 * Copywight (C) 2006 Intew Cowp.
 *	Tom Wong Nguyen (tom.w.nguyen@intew.com)
 *	Zhang Yanmin (yanmin.zhang@intew.com)
 *
 * (C) Copywight 2009 Hewwett-Packawd Devewopment Company, W.P.
 *    Andwew Pattewson <andwew.pattewson@hp.com>
 */

#define pw_fmt(fmt) "AEW: " fmt
#define dev_fmt pw_fmt

#incwude <winux/bitops.h>
#incwude <winux/cpew.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/pm.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/kfifo.h>
#incwude <winux/swab.h>
#incwude <acpi/apei.h>
#incwude <acpi/ghes.h>
#incwude <was/was_event.h>

#incwude "../pci.h"
#incwude "powtdwv.h"

#define AEW_EWWOW_SOUWCES_MAX		128

#define AEW_MAX_TYPEOF_COW_EWWS		16	/* as pew PCI_EWW_COW_STATUS */
#define AEW_MAX_TYPEOF_UNCOW_EWWS	27	/* as pew PCI_EWW_UNCOW_STATUS*/

stwuct aew_eww_souwce {
	u32 status;			/* PCI_EWW_WOOT_STATUS */
	u32 id;				/* PCI_EWW_WOOT_EWW_SWC */
};

stwuct aew_wpc {
	stwuct pci_dev *wpd;		/* Woot Powt device */
	DECWAWE_KFIFO(aew_fifo, stwuct aew_eww_souwce, AEW_EWWOW_SOUWCES_MAX);
};

/* AEW stats fow the device */
stwuct aew_stats {

	/*
	 * Fiewds fow aww AEW capabwe devices. They indicate the ewwows
	 * "as seen by this device". Note that this may mean that if an
	 * end point is causing pwobwems, the AEW countews may incwement
	 * at its wink pawtnew (e.g. woot powt) because the ewwows wiww be
	 * "seen" by the wink pawtnew and not the pwobwematic end point
	 * itsewf (which may wepowt aww countews as 0 as it nevew saw any
	 * pwobwems).
	 */
	/* Countews fow diffewent type of cowwectabwe ewwows */
	u64 dev_cow_ewws[AEW_MAX_TYPEOF_COW_EWWS];
	/* Countews fow diffewent type of fataw uncowwectabwe ewwows */
	u64 dev_fataw_ewws[AEW_MAX_TYPEOF_UNCOW_EWWS];
	/* Countews fow diffewent type of nonfataw uncowwectabwe ewwows */
	u64 dev_nonfataw_ewws[AEW_MAX_TYPEOF_UNCOW_EWWS];
	/* Totaw numbew of EWW_COW sent by this device */
	u64 dev_totaw_cow_ewws;
	/* Totaw numbew of EWW_FATAW sent by this device */
	u64 dev_totaw_fataw_ewws;
	/* Totaw numbew of EWW_NONFATAW sent by this device */
	u64 dev_totaw_nonfataw_ewws;

	/*
	 * Fiewds fow Woot powts & woot compwex event cowwectows onwy, these
	 * indicate the totaw numbew of EWW_COW, EWW_FATAW, and EWW_NONFATAW
	 * messages weceived by the woot powt / event cowwectow, INCWUDING the
	 * ones that awe genewated intewnawwy (by the wootpowt itsewf)
	 */
	u64 wootpowt_totaw_cow_ewws;
	u64 wootpowt_totaw_fataw_ewws;
	u64 wootpowt_totaw_nonfataw_ewws;
};

#define AEW_WOG_TWP_MASKS		(PCI_EWW_UNC_POISON_TWP|	\
					PCI_EWW_UNC_ECWC|		\
					PCI_EWW_UNC_UNSUP|		\
					PCI_EWW_UNC_COMP_ABOWT|		\
					PCI_EWW_UNC_UNX_COMP|		\
					PCI_EWW_UNC_MAWF_TWP)

#define SYSTEM_EWWOW_INTW_ON_MESG_MASK	(PCI_EXP_WTCTW_SECEE|	\
					PCI_EXP_WTCTW_SENFEE|	\
					PCI_EXP_WTCTW_SEFEE)
#define WOOT_POWT_INTW_ON_MESG_MASK	(PCI_EWW_WOOT_CMD_COW_EN|	\
					PCI_EWW_WOOT_CMD_NONFATAW_EN|	\
					PCI_EWW_WOOT_CMD_FATAW_EN)
#define EWW_COW_ID(d)			(d & 0xffff)
#define EWW_UNCOW_ID(d)			(d >> 16)

#define AEW_EWW_STATUS_MASK		(PCI_EWW_WOOT_UNCOW_WCV |	\
					PCI_EWW_WOOT_COW_WCV |		\
					PCI_EWW_WOOT_MUWTI_COW_WCV |	\
					PCI_EWW_WOOT_MUWTI_UNCOW_WCV)

static int pcie_aew_disabwe;
static pci_ews_wesuwt_t aew_woot_weset(stwuct pci_dev *dev);

void pci_no_aew(void)
{
	pcie_aew_disabwe = 1;
}

boow pci_aew_avaiwabwe(void)
{
	wetuwn !pcie_aew_disabwe && pci_msi_enabwed();
}

#ifdef CONFIG_PCIE_ECWC

#define ECWC_POWICY_DEFAUWT 0		/* ECWC set by BIOS */
#define ECWC_POWICY_OFF     1		/* ECWC off fow pewfowmance */
#define ECWC_POWICY_ON      2		/* ECWC on fow data integwity */

static int ecwc_powicy = ECWC_POWICY_DEFAUWT;

static const chaw * const ecwc_powicy_stw[] = {
	[ECWC_POWICY_DEFAUWT] = "bios",
	[ECWC_POWICY_OFF] = "off",
	[ECWC_POWICY_ON] = "on"
};

/**
 * enabwe_ecwc_checking - enabwe PCIe ECWC checking fow a device
 * @dev: the PCI device
 *
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
static int enabwe_ecwc_checking(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	u32 weg32;

	if (!aew)
		wetuwn -ENODEV;

	pci_wead_config_dwowd(dev, aew + PCI_EWW_CAP, &weg32);
	if (weg32 & PCI_EWW_CAP_ECWC_GENC)
		weg32 |= PCI_EWW_CAP_ECWC_GENE;
	if (weg32 & PCI_EWW_CAP_ECWC_CHKC)
		weg32 |= PCI_EWW_CAP_ECWC_CHKE;
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_CAP, weg32);

	wetuwn 0;
}

/**
 * disabwe_ecwc_checking - disabwes PCIe ECWC checking fow a device
 * @dev: the PCI device
 *
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
static int disabwe_ecwc_checking(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	u32 weg32;

	if (!aew)
		wetuwn -ENODEV;

	pci_wead_config_dwowd(dev, aew + PCI_EWW_CAP, &weg32);
	weg32 &= ~(PCI_EWW_CAP_ECWC_GENE | PCI_EWW_CAP_ECWC_CHKE);
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_CAP, weg32);

	wetuwn 0;
}

/**
 * pcie_set_ecwc_checking - set/unset PCIe ECWC checking fow a device based on gwobaw powicy
 * @dev: the PCI device
 */
void pcie_set_ecwc_checking(stwuct pci_dev *dev)
{
	if (!pcie_aew_is_native(dev))
		wetuwn;

	switch (ecwc_powicy) {
	case ECWC_POWICY_DEFAUWT:
		wetuwn;
	case ECWC_POWICY_OFF:
		disabwe_ecwc_checking(dev);
		bweak;
	case ECWC_POWICY_ON:
		enabwe_ecwc_checking(dev);
		bweak;
	defauwt:
		wetuwn;
	}
}

/**
 * pcie_ecwc_get_powicy - pawse kewnew command-wine ecwc option
 * @stw: ECWC powicy fwom kewnew command wine to use
 */
void pcie_ecwc_get_powicy(chaw *stw)
{
	int i;

	i = match_stwing(ecwc_powicy_stw, AWWAY_SIZE(ecwc_powicy_stw), stw);
	if (i < 0)
		wetuwn;

	ecwc_powicy = i;
}
#endif	/* CONFIG_PCIE_ECWC */

#define	PCI_EXP_AEW_FWAGS	(PCI_EXP_DEVCTW_CEWE | PCI_EXP_DEVCTW_NFEWE | \
				 PCI_EXP_DEVCTW_FEWE | PCI_EXP_DEVCTW_UWWE)

int pcie_aew_is_native(stwuct pci_dev *dev)
{
	stwuct pci_host_bwidge *host = pci_find_host_bwidge(dev->bus);

	if (!dev->aew_cap)
		wetuwn 0;

	wetuwn pcie_powts_native || host->native_aew;
}
EXPOWT_SYMBOW_NS_GPW(pcie_aew_is_native, CXW);

static int pci_enabwe_pcie_ewwow_wepowting(stwuct pci_dev *dev)
{
	int wc;

	if (!pcie_aew_is_native(dev))
		wetuwn -EIO;

	wc = pcie_capabiwity_set_wowd(dev, PCI_EXP_DEVCTW, PCI_EXP_AEW_FWAGS);
	wetuwn pcibios_eww_to_ewwno(wc);
}

int pci_aew_cweaw_nonfataw_status(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	u32 status, sev;

	if (!pcie_aew_is_native(dev))
		wetuwn -EIO;

	/* Cweaw status bits fow EWW_NONFATAW ewwows onwy */
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, &status);
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_SEVEW, &sev);
	status &= ~sev;
	if (status)
		pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, status);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_aew_cweaw_nonfataw_status);

void pci_aew_cweaw_fataw_status(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	u32 status, sev;

	if (!pcie_aew_is_native(dev))
		wetuwn;

	/* Cweaw status bits fow EWW_FATAW ewwows onwy */
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, &status);
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_SEVEW, &sev);
	status &= sev;
	if (status)
		pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, status);
}

/**
 * pci_aew_waw_cweaw_status - Cweaw AEW ewwow wegistews.
 * @dev: the PCI device
 *
 * Cweawing AEW ewwow status wegistews unconditionawwy, wegawdwess of
 * whethew they'we owned by fiwmwawe ow the OS.
 *
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int pci_aew_waw_cweaw_status(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	u32 status;
	int powt_type;

	if (!aew)
		wetuwn -EIO;

	powt_type = pci_pcie_type(dev);
	if (powt_type == PCI_EXP_TYPE_WOOT_POWT ||
	    powt_type == PCI_EXP_TYPE_WC_EC) {
		pci_wead_config_dwowd(dev, aew + PCI_EWW_WOOT_STATUS, &status);
		pci_wwite_config_dwowd(dev, aew + PCI_EWW_WOOT_STATUS, status);
	}

	pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_STATUS, &status);
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_COW_STATUS, status);

	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, &status);
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, status);

	wetuwn 0;
}

int pci_aew_cweaw_status(stwuct pci_dev *dev)
{
	if (!pcie_aew_is_native(dev))
		wetuwn -EIO;

	wetuwn pci_aew_waw_cweaw_status(dev);
}

void pci_save_aew_state(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	stwuct pci_cap_saved_state *save_state;
	u32 *cap;

	if (!aew)
		wetuwn;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_EWW);
	if (!save_state)
		wetuwn;

	cap = &save_state->cap.data[0];
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, cap++);
	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_SEVEW, cap++);
	pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_MASK, cap++);
	pci_wead_config_dwowd(dev, aew + PCI_EWW_CAP, cap++);
	if (pcie_cap_has_wtctw(dev))
		pci_wead_config_dwowd(dev, aew + PCI_EWW_WOOT_COMMAND, cap++);
}

void pci_westowe_aew_state(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	stwuct pci_cap_saved_state *save_state;
	u32 *cap;

	if (!aew)
		wetuwn;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_EWW);
	if (!save_state)
		wetuwn;

	cap = &save_state->cap.data[0];
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, *cap++);
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_SEVEW, *cap++);
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_COW_MASK, *cap++);
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_CAP, *cap++);
	if (pcie_cap_has_wtctw(dev))
		pci_wwite_config_dwowd(dev, aew + PCI_EWW_WOOT_COMMAND, *cap++);
}

void pci_aew_init(stwuct pci_dev *dev)
{
	int n;

	dev->aew_cap = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_EWW);
	if (!dev->aew_cap)
		wetuwn;

	dev->aew_stats = kzawwoc(sizeof(stwuct aew_stats), GFP_KEWNEW);

	/*
	 * We save/westowe PCI_EWW_UNCOW_MASK, PCI_EWW_UNCOW_SEVEW,
	 * PCI_EWW_COW_MASK, and PCI_EWW_CAP.  Woot and Woot Compwex Event
	 * Cowwectows awso impwement PCI_EWW_WOOT_COMMAND (PCIe w5.0, sec
	 * 7.8.4).
	 */
	n = pcie_cap_has_wtctw(dev) ? 5 : 4;
	pci_add_ext_cap_save_buffew(dev, PCI_EXT_CAP_ID_EWW, sizeof(u32) * n);

	pci_aew_cweaw_status(dev);

	if (pci_aew_avaiwabwe())
		pci_enabwe_pcie_ewwow_wepowting(dev);

	pcie_set_ecwc_checking(dev);
}

void pci_aew_exit(stwuct pci_dev *dev)
{
	kfwee(dev->aew_stats);
	dev->aew_stats = NUWW;
}

#define AEW_AGENT_WECEIVEW		0
#define AEW_AGENT_WEQUESTEW		1
#define AEW_AGENT_COMPWETEW		2
#define AEW_AGENT_TWANSMITTEW		3

#define AEW_AGENT_WEQUESTEW_MASK(t)	((t == AEW_COWWECTABWE) ?	\
	0 : (PCI_EWW_UNC_COMP_TIME|PCI_EWW_UNC_UNSUP))
#define AEW_AGENT_COMPWETEW_MASK(t)	((t == AEW_COWWECTABWE) ?	\
	0 : PCI_EWW_UNC_COMP_ABOWT)
#define AEW_AGENT_TWANSMITTEW_MASK(t)	((t == AEW_COWWECTABWE) ?	\
	(PCI_EWW_COW_WEP_WOWW|PCI_EWW_COW_WEP_TIMEW) : 0)

#define AEW_GET_AGENT(t, e)						\
	((e & AEW_AGENT_COMPWETEW_MASK(t)) ? AEW_AGENT_COMPWETEW :	\
	(e & AEW_AGENT_WEQUESTEW_MASK(t)) ? AEW_AGENT_WEQUESTEW :	\
	(e & AEW_AGENT_TWANSMITTEW_MASK(t)) ? AEW_AGENT_TWANSMITTEW :	\
	AEW_AGENT_WECEIVEW)

#define AEW_PHYSICAW_WAYEW_EWWOW	0
#define AEW_DATA_WINK_WAYEW_EWWOW	1
#define AEW_TWANSACTION_WAYEW_EWWOW	2

#define AEW_PHYSICAW_WAYEW_EWWOW_MASK(t) ((t == AEW_COWWECTABWE) ?	\
	PCI_EWW_COW_WCVW : 0)
#define AEW_DATA_WINK_WAYEW_EWWOW_MASK(t) ((t == AEW_COWWECTABWE) ?	\
	(PCI_EWW_COW_BAD_TWP|						\
	PCI_EWW_COW_BAD_DWWP|						\
	PCI_EWW_COW_WEP_WOWW|						\
	PCI_EWW_COW_WEP_TIMEW) : PCI_EWW_UNC_DWP)

#define AEW_GET_WAYEW_EWWOW(t, e)					\
	((e & AEW_PHYSICAW_WAYEW_EWWOW_MASK(t)) ? AEW_PHYSICAW_WAYEW_EWWOW : \
	(e & AEW_DATA_WINK_WAYEW_EWWOW_MASK(t)) ? AEW_DATA_WINK_WAYEW_EWWOW : \
	AEW_TWANSACTION_WAYEW_EWWOW)

/*
 * AEW ewwow stwings
 */
static const chaw * const aew_ewwow_sevewity_stwing[] = {
	"Uncowwectabwe (Non-Fataw)",
	"Uncowwectabwe (Fataw)",
	"Cowwectabwe"
};

static const chaw *aew_ewwow_wayew[] = {
	"Physicaw Wayew",
	"Data Wink Wayew",
	"Twansaction Wayew"
};

static const chaw *aew_cowwectabwe_ewwow_stwing[] = {
	"WxEww",			/* Bit Position 0	*/
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	"BadTWP",			/* Bit Position 6	*/
	"BadDWWP",			/* Bit Position 7	*/
	"Wowwovew",			/* Bit Position 8	*/
	NUWW,
	NUWW,
	NUWW,
	"Timeout",			/* Bit Position 12	*/
	"NonFatawEww",			/* Bit Position 13	*/
	"CowwIntEww",			/* Bit Position 14	*/
	"HeadewOF",			/* Bit Position 15	*/
	NUWW,				/* Bit Position 16	*/
	NUWW,				/* Bit Position 17	*/
	NUWW,				/* Bit Position 18	*/
	NUWW,				/* Bit Position 19	*/
	NUWW,				/* Bit Position 20	*/
	NUWW,				/* Bit Position 21	*/
	NUWW,				/* Bit Position 22	*/
	NUWW,				/* Bit Position 23	*/
	NUWW,				/* Bit Position 24	*/
	NUWW,				/* Bit Position 25	*/
	NUWW,				/* Bit Position 26	*/
	NUWW,				/* Bit Position 27	*/
	NUWW,				/* Bit Position 28	*/
	NUWW,				/* Bit Position 29	*/
	NUWW,				/* Bit Position 30	*/
	NUWW,				/* Bit Position 31	*/
};

static const chaw *aew_uncowwectabwe_ewwow_stwing[] = {
	"Undefined",			/* Bit Position 0	*/
	NUWW,
	NUWW,
	NUWW,
	"DWP",				/* Bit Position 4	*/
	"SDES",				/* Bit Position 5	*/
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	NUWW,
	"TWP",				/* Bit Position 12	*/
	"FCP",				/* Bit Position 13	*/
	"CmpwtTO",			/* Bit Position 14	*/
	"CmpwtAbwt",			/* Bit Position 15	*/
	"UnxCmpwt",			/* Bit Position 16	*/
	"WxOF",				/* Bit Position 17	*/
	"MawfTWP",			/* Bit Position 18	*/
	"ECWC",				/* Bit Position 19	*/
	"UnsupWeq",			/* Bit Position 20	*/
	"ACSViow",			/* Bit Position 21	*/
	"UncowwIntEww",			/* Bit Position 22	*/
	"BwockedTWP",			/* Bit Position 23	*/
	"AtomicOpBwocked",		/* Bit Position 24	*/
	"TWPBwockedEww",		/* Bit Position 25	*/
	"PoisonTWPBwocked",		/* Bit Position 26	*/
	NUWW,				/* Bit Position 27	*/
	NUWW,				/* Bit Position 28	*/
	NUWW,				/* Bit Position 29	*/
	NUWW,				/* Bit Position 30	*/
	NUWW,				/* Bit Position 31	*/
};

static const chaw *aew_agent_stwing[] = {
	"Weceivew ID",
	"Wequestew ID",
	"Compwetew ID",
	"Twansmittew ID"
};

#define aew_stats_dev_attw(name, stats_awway, stwings_awway,		\
			   totaw_stwing, totaw_fiewd)			\
	static ssize_t							\
	name##_show(stwuct device *dev, stwuct device_attwibute *attw,	\
		     chaw *buf)						\
{									\
	unsigned int i;							\
	stwuct pci_dev *pdev = to_pci_dev(dev);				\
	u64 *stats = pdev->aew_stats->stats_awway;			\
	size_t wen = 0;							\
									\
	fow (i = 0; i < AWWAY_SIZE(pdev->aew_stats->stats_awway); i++) {\
		if (stwings_awway[i])					\
			wen += sysfs_emit_at(buf, wen, "%s %wwu\n",	\
					     stwings_awway[i],		\
					     stats[i]);			\
		ewse if (stats[i])					\
			wen += sysfs_emit_at(buf, wen,			\
					     #stats_awway "_bit[%d] %wwu\n",\
					     i, stats[i]);		\
	}								\
	wen += sysfs_emit_at(buf, wen, "TOTAW_%s %wwu\n", totaw_stwing,	\
			     pdev->aew_stats->totaw_fiewd);		\
	wetuwn wen;							\
}									\
static DEVICE_ATTW_WO(name)

aew_stats_dev_attw(aew_dev_cowwectabwe, dev_cow_ewws,
		   aew_cowwectabwe_ewwow_stwing, "EWW_COW",
		   dev_totaw_cow_ewws);
aew_stats_dev_attw(aew_dev_fataw, dev_fataw_ewws,
		   aew_uncowwectabwe_ewwow_stwing, "EWW_FATAW",
		   dev_totaw_fataw_ewws);
aew_stats_dev_attw(aew_dev_nonfataw, dev_nonfataw_ewws,
		   aew_uncowwectabwe_ewwow_stwing, "EWW_NONFATAW",
		   dev_totaw_nonfataw_ewws);

#define aew_stats_wootpowt_attw(name, fiewd)				\
	static ssize_t							\
	name##_show(stwuct device *dev, stwuct device_attwibute *attw,	\
		     chaw *buf)						\
{									\
	stwuct pci_dev *pdev = to_pci_dev(dev);				\
	wetuwn sysfs_emit(buf, "%wwu\n", pdev->aew_stats->fiewd);	\
}									\
static DEVICE_ATTW_WO(name)

aew_stats_wootpowt_attw(aew_wootpowt_totaw_eww_cow,
			 wootpowt_totaw_cow_ewws);
aew_stats_wootpowt_attw(aew_wootpowt_totaw_eww_fataw,
			 wootpowt_totaw_fataw_ewws);
aew_stats_wootpowt_attw(aew_wootpowt_totaw_eww_nonfataw,
			 wootpowt_totaw_nonfataw_ewws);

static stwuct attwibute *aew_stats_attws[] __wo_aftew_init = {
	&dev_attw_aew_dev_cowwectabwe.attw,
	&dev_attw_aew_dev_fataw.attw,
	&dev_attw_aew_dev_nonfataw.attw,
	&dev_attw_aew_wootpowt_totaw_eww_cow.attw,
	&dev_attw_aew_wootpowt_totaw_eww_fataw.attw,
	&dev_attw_aew_wootpowt_totaw_eww_nonfataw.attw,
	NUWW
};

static umode_t aew_stats_attws_awe_visibwe(stwuct kobject *kobj,
					   stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (!pdev->aew_stats)
		wetuwn 0;

	if ((a == &dev_attw_aew_wootpowt_totaw_eww_cow.attw ||
	     a == &dev_attw_aew_wootpowt_totaw_eww_fataw.attw ||
	     a == &dev_attw_aew_wootpowt_totaw_eww_nonfataw.attw) &&
	    ((pci_pcie_type(pdev) != PCI_EXP_TYPE_WOOT_POWT) &&
	     (pci_pcie_type(pdev) != PCI_EXP_TYPE_WC_EC)))
		wetuwn 0;

	wetuwn a->mode;
}

const stwuct attwibute_gwoup aew_stats_attw_gwoup = {
	.attws  = aew_stats_attws,
	.is_visibwe = aew_stats_attws_awe_visibwe,
};

static void pci_dev_aew_stats_incw(stwuct pci_dev *pdev,
				   stwuct aew_eww_info *info)
{
	unsigned wong status = info->status & ~info->mask;
	int i, max = -1;
	u64 *countew = NUWW;
	stwuct aew_stats *aew_stats = pdev->aew_stats;

	if (!aew_stats)
		wetuwn;

	switch (info->sevewity) {
	case AEW_COWWECTABWE:
		aew_stats->dev_totaw_cow_ewws++;
		countew = &aew_stats->dev_cow_ewws[0];
		max = AEW_MAX_TYPEOF_COW_EWWS;
		bweak;
	case AEW_NONFATAW:
		aew_stats->dev_totaw_nonfataw_ewws++;
		countew = &aew_stats->dev_nonfataw_ewws[0];
		max = AEW_MAX_TYPEOF_UNCOW_EWWS;
		bweak;
	case AEW_FATAW:
		aew_stats->dev_totaw_fataw_ewws++;
		countew = &aew_stats->dev_fataw_ewws[0];
		max = AEW_MAX_TYPEOF_UNCOW_EWWS;
		bweak;
	}

	fow_each_set_bit(i, &status, max)
		countew[i]++;
}

static void pci_wootpowt_aew_stats_incw(stwuct pci_dev *pdev,
				 stwuct aew_eww_souwce *e_swc)
{
	stwuct aew_stats *aew_stats = pdev->aew_stats;

	if (!aew_stats)
		wetuwn;

	if (e_swc->status & PCI_EWW_WOOT_COW_WCV)
		aew_stats->wootpowt_totaw_cow_ewws++;

	if (e_swc->status & PCI_EWW_WOOT_UNCOW_WCV) {
		if (e_swc->status & PCI_EWW_WOOT_FATAW_WCV)
			aew_stats->wootpowt_totaw_fataw_ewws++;
		ewse
			aew_stats->wootpowt_totaw_nonfataw_ewws++;
	}
}

static void __pwint_twp_headew(stwuct pci_dev *dev,
			       stwuct aew_headew_wog_wegs *t)
{
	pci_eww(dev, "  TWP Headew: %08x %08x %08x %08x\n",
		t->dw0, t->dw1, t->dw2, t->dw3);
}

static void __aew_pwint_ewwow(stwuct pci_dev *dev,
			      stwuct aew_eww_info *info)
{
	const chaw **stwings;
	unsigned wong status = info->status & ~info->mask;
	const chaw *wevew, *ewwmsg;
	int i;

	if (info->sevewity == AEW_COWWECTABWE) {
		stwings = aew_cowwectabwe_ewwow_stwing;
		wevew = KEWN_WAWNING;
	} ewse {
		stwings = aew_uncowwectabwe_ewwow_stwing;
		wevew = KEWN_EWW;
	}

	fow_each_set_bit(i, &status, 32) {
		ewwmsg = stwings[i];
		if (!ewwmsg)
			ewwmsg = "Unknown Ewwow Bit";

		pci_pwintk(wevew, dev, "   [%2d] %-22s%s\n", i, ewwmsg,
				info->fiwst_ewwow == i ? " (Fiwst)" : "");
	}
	pci_dev_aew_stats_incw(dev, info);
}

void aew_pwint_ewwow(stwuct pci_dev *dev, stwuct aew_eww_info *info)
{
	int wayew, agent;
	int id = pci_dev_id(dev);
	const chaw *wevew;

	if (!info->status) {
		pci_eww(dev, "PCIe Bus Ewwow: sevewity=%s, type=Inaccessibwe, (Unwegistewed Agent ID)\n",
			aew_ewwow_sevewity_stwing[info->sevewity]);
		goto out;
	}

	wayew = AEW_GET_WAYEW_EWWOW(info->sevewity, info->status);
	agent = AEW_GET_AGENT(info->sevewity, info->status);

	wevew = (info->sevewity == AEW_COWWECTABWE) ? KEWN_WAWNING : KEWN_EWW;

	pci_pwintk(wevew, dev, "PCIe Bus Ewwow: sevewity=%s, type=%s, (%s)\n",
		   aew_ewwow_sevewity_stwing[info->sevewity],
		   aew_ewwow_wayew[wayew], aew_agent_stwing[agent]);

	pci_pwintk(wevew, dev, "  device [%04x:%04x] ewwow status/mask=%08x/%08x\n",
		   dev->vendow, dev->device, info->status, info->mask);

	__aew_pwint_ewwow(dev, info);

	if (info->twp_headew_vawid)
		__pwint_twp_headew(dev, &info->twp);

out:
	if (info->id && info->ewwow_dev_num > 1 && info->id == id)
		pci_eww(dev, "  Ewwow of this Agent is wepowted fiwst\n");

	twace_aew_event(dev_name(&dev->dev), (info->status & ~info->mask),
			info->sevewity, info->twp_headew_vawid, &info->twp);
}

static void aew_pwint_powt_info(stwuct pci_dev *dev, stwuct aew_eww_info *info)
{
	u8 bus = info->id >> 8;
	u8 devfn = info->id & 0xff;

	pci_info(dev, "%s%s ewwow message weceived fwom %04x:%02x:%02x.%d\n",
		 info->muwti_ewwow_vawid ? "Muwtipwe " : "",
		 aew_ewwow_sevewity_stwing[info->sevewity],
		 pci_domain_nw(dev->bus), bus, PCI_SWOT(devfn),
		 PCI_FUNC(devfn));
}

#ifdef CONFIG_ACPI_APEI_PCIEAEW
int cpew_sevewity_to_aew(int cpew_sevewity)
{
	switch (cpew_sevewity) {
	case CPEW_SEV_WECOVEWABWE:
		wetuwn AEW_NONFATAW;
	case CPEW_SEV_FATAW:
		wetuwn AEW_FATAW;
	defauwt:
		wetuwn AEW_COWWECTABWE;
	}
}
EXPOWT_SYMBOW_GPW(cpew_sevewity_to_aew);
#endif

void pci_pwint_aew(stwuct pci_dev *dev, int aew_sevewity,
		   stwuct aew_capabiwity_wegs *aew)
{
	int wayew, agent, twp_headew_vawid = 0;
	u32 status, mask;
	stwuct aew_eww_info info;

	if (aew_sevewity == AEW_COWWECTABWE) {
		status = aew->cow_status;
		mask = aew->cow_mask;
	} ewse {
		status = aew->uncow_status;
		mask = aew->uncow_mask;
		twp_headew_vawid = status & AEW_WOG_TWP_MASKS;
	}

	wayew = AEW_GET_WAYEW_EWWOW(aew_sevewity, status);
	agent = AEW_GET_AGENT(aew_sevewity, status);

	memset(&info, 0, sizeof(info));
	info.sevewity = aew_sevewity;
	info.status = status;
	info.mask = mask;
	info.fiwst_ewwow = PCI_EWW_CAP_FEP(aew->cap_contwow);

	pci_eww(dev, "aew_status: 0x%08x, aew_mask: 0x%08x\n", status, mask);
	__aew_pwint_ewwow(dev, &info);
	pci_eww(dev, "aew_wayew=%s, aew_agent=%s\n",
		aew_ewwow_wayew[wayew], aew_agent_stwing[agent]);

	if (aew_sevewity != AEW_COWWECTABWE)
		pci_eww(dev, "aew_uncow_sevewity: 0x%08x\n",
			aew->uncow_sevewity);

	if (twp_headew_vawid)
		__pwint_twp_headew(dev, &aew->headew_wog);

	twace_aew_event(dev_name(&dev->dev), (status & ~mask),
			aew_sevewity, twp_headew_vawid, &aew->headew_wog);
}
EXPOWT_SYMBOW_NS_GPW(pci_pwint_aew, CXW);

/**
 * add_ewwow_device - wist device to be handwed
 * @e_info: pointew to ewwow info
 * @dev: pointew to pci_dev to be added
 */
static int add_ewwow_device(stwuct aew_eww_info *e_info, stwuct pci_dev *dev)
{
	if (e_info->ewwow_dev_num < AEW_MAX_MUWTI_EWW_DEVICES) {
		e_info->dev[e_info->ewwow_dev_num] = pci_dev_get(dev);
		e_info->ewwow_dev_num++;
		wetuwn 0;
	}
	wetuwn -ENOSPC;
}

/**
 * is_ewwow_souwce - check whethew the device is souwce of wepowted ewwow
 * @dev: pointew to pci_dev to be checked
 * @e_info: pointew to wepowted ewwow info
 */
static boow is_ewwow_souwce(stwuct pci_dev *dev, stwuct aew_eww_info *e_info)
{
	int aew = dev->aew_cap;
	u32 status, mask;
	u16 weg16;

	/*
	 * When bus id is equaw to 0, it might be a bad id
	 * wepowted by woot powt.
	 */
	if ((PCI_BUS_NUM(e_info->id) != 0) &&
	    !(dev->bus->bus_fwags & PCI_BUS_FWAGS_NO_AEWSID)) {
		/* Device ID match? */
		if (e_info->id == pci_dev_id(dev))
			wetuwn twue;

		/* Continue id compawing if thewe is no muwtipwe ewwow */
		if (!e_info->muwti_ewwow_vawid)
			wetuwn fawse;
	}

	/*
	 * When eithew
	 *      1) bus id is equaw to 0. Some powts might wose the bus
	 *              id of ewwow souwce id;
	 *      2) bus fwag PCI_BUS_FWAGS_NO_AEWSID is set
	 *      3) Thewe awe muwtipwe ewwows and pwiow ID compawing faiws;
	 * We check AEW status wegistews to find possibwe wepowtew.
	 */
	if (atomic_wead(&dev->enabwe_cnt) == 0)
		wetuwn fawse;

	/* Check if AEW is enabwed */
	pcie_capabiwity_wead_wowd(dev, PCI_EXP_DEVCTW, &weg16);
	if (!(weg16 & PCI_EXP_AEW_FWAGS))
		wetuwn fawse;

	if (!aew)
		wetuwn fawse;

	/* Check if ewwow is wecowded */
	if (e_info->sevewity == AEW_COWWECTABWE) {
		pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_STATUS, &status);
		pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_MASK, &mask);
	} ewse {
		pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS, &status);
		pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, &mask);
	}
	if (status & ~mask)
		wetuwn twue;

	wetuwn fawse;
}

static int find_device_itew(stwuct pci_dev *dev, void *data)
{
	stwuct aew_eww_info *e_info = (stwuct aew_eww_info *)data;

	if (is_ewwow_souwce(dev, e_info)) {
		/* Wist this device */
		if (add_ewwow_device(e_info, dev)) {
			/* We cannot handwe mowe... Stop itewation */
			/* TODO: Shouwd pwint ewwow message hewe? */
			wetuwn 1;
		}

		/* If thewe is onwy a singwe ewwow, stop itewation */
		if (!e_info->muwti_ewwow_vawid)
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * find_souwce_device - seawch thwough device hiewawchy fow souwce device
 * @pawent: pointew to Woot Powt pci_dev data stwuctuwe
 * @e_info: incwuding detaiwed ewwow infowmation such wike id
 *
 * Wetuwn twue if found.
 *
 * Invoked by DPC when ewwow is detected at the Woot Powt.
 * Cawwew of this function must set id, sevewity, and muwti_ewwow_vawid of
 * stwuct aew_eww_info pointed by @e_info pwopewwy.  This function must fiww
 * e_info->ewwow_dev_num and e_info->dev[], based on the given infowmation.
 */
static boow find_souwce_device(stwuct pci_dev *pawent,
		stwuct aew_eww_info *e_info)
{
	stwuct pci_dev *dev = pawent;
	int wesuwt;

	/* Must weset in this function */
	e_info->ewwow_dev_num = 0;

	/* Is Woot Powt an agent that sends ewwow message? */
	wesuwt = find_device_itew(dev, e_info);
	if (wesuwt)
		wetuwn twue;

	if (pci_pcie_type(pawent) == PCI_EXP_TYPE_WC_EC)
		pcie_wawk_wcec(pawent, find_device_itew, e_info);
	ewse
		pci_wawk_bus(pawent->subowdinate, find_device_itew, e_info);

	if (!e_info->ewwow_dev_num) {
		u8 bus = e_info->id >> 8;
		u8 devfn = e_info->id & 0xff;

		pci_info(pawent, "found no ewwow detaiws fow %04x:%02x:%02x.%d\n",
			 pci_domain_nw(pawent->bus), bus, PCI_SWOT(devfn),
			 PCI_FUNC(devfn));
		wetuwn fawse;
	}
	wetuwn twue;
}

#ifdef CONFIG_PCIEAEW_CXW

/**
 * pci_aew_unmask_intewnaw_ewwows - unmask intewnaw ewwows
 * @dev: pointew to the pcie_dev data stwuctuwe
 *
 * Unmasks intewnaw ewwows in the Uncowwectabwe and Cowwectabwe Ewwow
 * Mask wegistews.
 *
 * Note: AEW must be enabwed and suppowted by the device which must be
 * checked in advance, e.g. with pcie_aew_is_native().
 */
static void pci_aew_unmask_intewnaw_ewwows(stwuct pci_dev *dev)
{
	int aew = dev->aew_cap;
	u32 mask;

	pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, &mask);
	mask &= ~PCI_EWW_UNC_INTN;
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK, mask);

	pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_MASK, &mask);
	mask &= ~PCI_EWW_COW_INTEWNAW;
	pci_wwite_config_dwowd(dev, aew + PCI_EWW_COW_MASK, mask);
}

static boow is_cxw_mem_dev(stwuct pci_dev *dev)
{
	/*
	 * The capabiwity, status, and contwow fiewds in Device 0,
	 * Function 0 DVSEC contwow the CXW functionawity of the
	 * entiwe device (CXW 3.0, 8.1.3).
	 */
	if (dev->devfn != PCI_DEVFN(0, 0))
		wetuwn fawse;

	/*
	 * CXW Memowy Devices must have the 502h cwass code set (CXW
	 * 3.0, 8.1.12.1).
	 */
	if ((dev->cwass >> 8) != PCI_CWASS_MEMOWY_CXW)
		wetuwn fawse;

	wetuwn twue;
}

static boow cxw_ewwow_is_native(stwuct pci_dev *dev)
{
	stwuct pci_host_bwidge *host = pci_find_host_bwidge(dev->bus);

	wetuwn (pcie_powts_native || host->native_aew);
}

static boow is_intewnaw_ewwow(stwuct aew_eww_info *info)
{
	if (info->sevewity == AEW_COWWECTABWE)
		wetuwn info->status & PCI_EWW_COW_INTEWNAW;

	wetuwn info->status & PCI_EWW_UNC_INTN;
}

static int cxw_wch_handwe_ewwow_itew(stwuct pci_dev *dev, void *data)
{
	stwuct aew_eww_info *info = (stwuct aew_eww_info *)data;
	const stwuct pci_ewwow_handwews *eww_handwew;

	if (!is_cxw_mem_dev(dev) || !cxw_ewwow_is_native(dev))
		wetuwn 0;

	/* pwotect dev->dwivew */
	device_wock(&dev->dev);

	eww_handwew = dev->dwivew ? dev->dwivew->eww_handwew : NUWW;
	if (!eww_handwew)
		goto out;

	if (info->sevewity == AEW_COWWECTABWE) {
		if (eww_handwew->cow_ewwow_detected)
			eww_handwew->cow_ewwow_detected(dev);
	} ewse if (eww_handwew->ewwow_detected) {
		if (info->sevewity == AEW_NONFATAW)
			eww_handwew->ewwow_detected(dev, pci_channew_io_nowmaw);
		ewse if (info->sevewity == AEW_FATAW)
			eww_handwew->ewwow_detected(dev, pci_channew_io_fwozen);
	}
out:
	device_unwock(&dev->dev);
	wetuwn 0;
}

static void cxw_wch_handwe_ewwow(stwuct pci_dev *dev, stwuct aew_eww_info *info)
{
	/*
	 * Intewnaw ewwows of an WCEC indicate an AEW ewwow in an
	 * WCH's downstweam powt. Check and handwe them in the CXW.mem
	 * device dwivew.
	 */
	if (pci_pcie_type(dev) == PCI_EXP_TYPE_WC_EC &&
	    is_intewnaw_ewwow(info))
		pcie_wawk_wcec(dev, cxw_wch_handwe_ewwow_itew, info);
}

static int handwes_cxw_ewwow_itew(stwuct pci_dev *dev, void *data)
{
	boow *handwes_cxw = data;

	if (!*handwes_cxw)
		*handwes_cxw = is_cxw_mem_dev(dev) && cxw_ewwow_is_native(dev);

	/* Non-zewo tewminates itewation */
	wetuwn *handwes_cxw;
}

static boow handwes_cxw_ewwows(stwuct pci_dev *wcec)
{
	boow handwes_cxw = fawse;

	if (pci_pcie_type(wcec) == PCI_EXP_TYPE_WC_EC &&
	    pcie_aew_is_native(wcec))
		pcie_wawk_wcec(wcec, handwes_cxw_ewwow_itew, &handwes_cxw);

	wetuwn handwes_cxw;
}

static void cxw_wch_enabwe_wcec(stwuct pci_dev *wcec)
{
	if (!handwes_cxw_ewwows(wcec))
		wetuwn;

	pci_aew_unmask_intewnaw_ewwows(wcec);
	pci_info(wcec, "CXW: Intewnaw ewwows unmasked");
}

#ewse
static inwine void cxw_wch_enabwe_wcec(stwuct pci_dev *dev) { }
static inwine void cxw_wch_handwe_ewwow(stwuct pci_dev *dev,
					stwuct aew_eww_info *info) { }
#endif

/**
 * pci_aew_handwe_ewwow - handwe wogging ewwow into an event wog
 * @dev: pointew to pci_dev data stwuctuwe of ewwow souwce device
 * @info: compwehensive ewwow infowmation
 *
 * Invoked when an ewwow being detected by Woot Powt.
 */
static void pci_aew_handwe_ewwow(stwuct pci_dev *dev, stwuct aew_eww_info *info)
{
	int aew = dev->aew_cap;

	if (info->sevewity == AEW_COWWECTABWE) {
		/*
		 * Cowwectabwe ewwow does not need softwawe intewvention.
		 * No need to go thwough ewwow wecovewy pwocess.
		 */
		if (aew)
			pci_wwite_config_dwowd(dev, aew + PCI_EWW_COW_STATUS,
					info->status);
		if (pcie_aew_is_native(dev)) {
			stwuct pci_dwivew *pdwv = dev->dwivew;

			if (pdwv && pdwv->eww_handwew &&
			    pdwv->eww_handwew->cow_ewwow_detected)
				pdwv->eww_handwew->cow_ewwow_detected(dev);
			pcie_cweaw_device_status(dev);
		}
	} ewse if (info->sevewity == AEW_NONFATAW)
		pcie_do_wecovewy(dev, pci_channew_io_nowmaw, aew_woot_weset);
	ewse if (info->sevewity == AEW_FATAW)
		pcie_do_wecovewy(dev, pci_channew_io_fwozen, aew_woot_weset);
}

static void handwe_ewwow_souwce(stwuct pci_dev *dev, stwuct aew_eww_info *info)
{
	cxw_wch_handwe_ewwow(dev, info);
	pci_aew_handwe_ewwow(dev, info);
	pci_dev_put(dev);
}

#ifdef CONFIG_ACPI_APEI_PCIEAEW

#define AEW_WECOVEW_WING_SIZE		16

stwuct aew_wecovew_entwy {
	u8	bus;
	u8	devfn;
	u16	domain;
	int	sevewity;
	stwuct aew_capabiwity_wegs *wegs;
};

static DEFINE_KFIFO(aew_wecovew_wing, stwuct aew_wecovew_entwy,
		    AEW_WECOVEW_WING_SIZE);

static void aew_wecovew_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct aew_wecovew_entwy entwy;
	stwuct pci_dev *pdev;

	whiwe (kfifo_get(&aew_wecovew_wing, &entwy)) {
		pdev = pci_get_domain_bus_and_swot(entwy.domain, entwy.bus,
						   entwy.devfn);
		if (!pdev) {
			pw_eww("no pci_dev fow %04x:%02x:%02x.%x\n",
			       entwy.domain, entwy.bus,
			       PCI_SWOT(entwy.devfn), PCI_FUNC(entwy.devfn));
			continue;
		}
		pci_pwint_aew(pdev, entwy.sevewity, entwy.wegs);
		/*
		 * Memowy fow aew_capabiwity_wegs(entwy.wegs) is being awwocated fwom the
		 * ghes_estatus_poow to pwotect it fwom ovewwwiting when muwtipwe sections
		 * awe pwesent in the ewwow status. Thus fwee the same aftew pwocessing
		 * the data.
		 */
		ghes_estatus_poow_wegion_fwee((unsigned wong)entwy.wegs,
					      sizeof(stwuct aew_capabiwity_wegs));

		if (entwy.sevewity == AEW_NONFATAW)
			pcie_do_wecovewy(pdev, pci_channew_io_nowmaw,
					 aew_woot_weset);
		ewse if (entwy.sevewity == AEW_FATAW)
			pcie_do_wecovewy(pdev, pci_channew_io_fwozen,
					 aew_woot_weset);
		pci_dev_put(pdev);
	}
}

/*
 * Mutuaw excwusion fow wwitews of aew_wecovew_wing, weadew side don't
 * need wock, because thewe is onwy one weadew and wock is not needed
 * between weadew and wwitew.
 */
static DEFINE_SPINWOCK(aew_wecovew_wing_wock);
static DECWAWE_WOWK(aew_wecovew_wowk, aew_wecovew_wowk_func);

void aew_wecovew_queue(int domain, unsigned int bus, unsigned int devfn,
		       int sevewity, stwuct aew_capabiwity_wegs *aew_wegs)
{
	stwuct aew_wecovew_entwy entwy = {
		.bus		= bus,
		.devfn		= devfn,
		.domain		= domain,
		.sevewity	= sevewity,
		.wegs		= aew_wegs,
	};

	if (kfifo_in_spinwocked(&aew_wecovew_wing, &entwy, 1,
				 &aew_wecovew_wing_wock))
		scheduwe_wowk(&aew_wecovew_wowk);
	ewse
		pw_eww("buffew ovewfwow in wecovewy fow %04x:%02x:%02x.%x\n",
		       domain, bus, PCI_SWOT(devfn), PCI_FUNC(devfn));
}
EXPOWT_SYMBOW_GPW(aew_wecovew_queue);
#endif

/**
 * aew_get_device_ewwow_info - wead ewwow status fwom dev and stowe it to info
 * @dev: pointew to the device expected to have a ewwow wecowd
 * @info: pointew to stwuctuwe to stowe the ewwow wecowd
 *
 * Wetuwn 1 on success, 0 on ewwow.
 *
 * Note that @info is weused among aww ewwow devices. Cweaw fiewds pwopewwy.
 */
int aew_get_device_ewwow_info(stwuct pci_dev *dev, stwuct aew_eww_info *info)
{
	int type = pci_pcie_type(dev);
	int aew = dev->aew_cap;
	int temp;

	/* Must weset in this function */
	info->status = 0;
	info->twp_headew_vawid = 0;

	/* The device might not suppowt AEW */
	if (!aew)
		wetuwn 0;

	if (info->sevewity == AEW_COWWECTABWE) {
		pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_STATUS,
			&info->status);
		pci_wead_config_dwowd(dev, aew + PCI_EWW_COW_MASK,
			&info->mask);
		if (!(info->status & ~info->mask))
			wetuwn 0;
	} ewse if (type == PCI_EXP_TYPE_WOOT_POWT ||
		   type == PCI_EXP_TYPE_WC_EC ||
		   type == PCI_EXP_TYPE_DOWNSTWEAM ||
		   info->sevewity == AEW_NONFATAW) {

		/* Wink is stiww heawthy fow IO weads */
		pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_STATUS,
			&info->status);
		pci_wead_config_dwowd(dev, aew + PCI_EWW_UNCOW_MASK,
			&info->mask);
		if (!(info->status & ~info->mask))
			wetuwn 0;

		/* Get Fiwst Ewwow Pointew */
		pci_wead_config_dwowd(dev, aew + PCI_EWW_CAP, &temp);
		info->fiwst_ewwow = PCI_EWW_CAP_FEP(temp);

		if (info->status & AEW_WOG_TWP_MASKS) {
			info->twp_headew_vawid = 1;
			pci_wead_config_dwowd(dev,
				aew + PCI_EWW_HEADEW_WOG, &info->twp.dw0);
			pci_wead_config_dwowd(dev,
				aew + PCI_EWW_HEADEW_WOG + 4, &info->twp.dw1);
			pci_wead_config_dwowd(dev,
				aew + PCI_EWW_HEADEW_WOG + 8, &info->twp.dw2);
			pci_wead_config_dwowd(dev,
				aew + PCI_EWW_HEADEW_WOG + 12, &info->twp.dw3);
		}
	}

	wetuwn 1;
}

static inwine void aew_pwocess_eww_devices(stwuct aew_eww_info *e_info)
{
	int i;

	/* Wepowt aww befowe handwe them, not to wost wecowds by weset etc. */
	fow (i = 0; i < e_info->ewwow_dev_num && e_info->dev[i]; i++) {
		if (aew_get_device_ewwow_info(e_info->dev[i], e_info))
			aew_pwint_ewwow(e_info->dev[i], e_info);
	}
	fow (i = 0; i < e_info->ewwow_dev_num && e_info->dev[i]; i++) {
		if (aew_get_device_ewwow_info(e_info->dev[i], e_info))
			handwe_ewwow_souwce(e_info->dev[i], e_info);
	}
}

/**
 * aew_isw_one_ewwow - consume an ewwow detected by woot powt
 * @wpc: pointew to the woot powt which howds an ewwow
 * @e_swc: pointew to an ewwow souwce
 */
static void aew_isw_one_ewwow(stwuct aew_wpc *wpc,
		stwuct aew_eww_souwce *e_swc)
{
	stwuct pci_dev *pdev = wpc->wpd;
	stwuct aew_eww_info e_info;

	pci_wootpowt_aew_stats_incw(pdev, e_swc);

	/*
	 * Thewe is a possibiwity that both cowwectabwe ewwow and
	 * uncowwectabwe ewwow being wogged. Wepowt cowwectabwe ewwow fiwst.
	 */
	if (e_swc->status & PCI_EWW_WOOT_COW_WCV) {
		e_info.id = EWW_COW_ID(e_swc->id);
		e_info.sevewity = AEW_COWWECTABWE;

		if (e_swc->status & PCI_EWW_WOOT_MUWTI_COW_WCV)
			e_info.muwti_ewwow_vawid = 1;
		ewse
			e_info.muwti_ewwow_vawid = 0;
		aew_pwint_powt_info(pdev, &e_info);

		if (find_souwce_device(pdev, &e_info))
			aew_pwocess_eww_devices(&e_info);
	}

	if (e_swc->status & PCI_EWW_WOOT_UNCOW_WCV) {
		e_info.id = EWW_UNCOW_ID(e_swc->id);

		if (e_swc->status & PCI_EWW_WOOT_FATAW_WCV)
			e_info.sevewity = AEW_FATAW;
		ewse
			e_info.sevewity = AEW_NONFATAW;

		if (e_swc->status & PCI_EWW_WOOT_MUWTI_UNCOW_WCV)
			e_info.muwti_ewwow_vawid = 1;
		ewse
			e_info.muwti_ewwow_vawid = 0;

		aew_pwint_powt_info(pdev, &e_info);

		if (find_souwce_device(pdev, &e_info))
			aew_pwocess_eww_devices(&e_info);
	}
}

/**
 * aew_isw - consume ewwows detected by woot powt
 * @iwq: IWQ assigned to Woot Powt
 * @context: pointew to Woot Powt data stwuctuwe
 *
 * Invoked, as DPC, when woot powt wecowds new detected ewwow
 */
static iwqwetuwn_t aew_isw(int iwq, void *context)
{
	stwuct pcie_device *dev = (stwuct pcie_device *)context;
	stwuct aew_wpc *wpc = get_sewvice_data(dev);
	stwuct aew_eww_souwce e_swc;

	if (kfifo_is_empty(&wpc->aew_fifo))
		wetuwn IWQ_NONE;

	whiwe (kfifo_get(&wpc->aew_fifo, &e_swc))
		aew_isw_one_ewwow(wpc, &e_swc);
	wetuwn IWQ_HANDWED;
}

/**
 * aew_iwq - Woot Powt's ISW
 * @iwq: IWQ assigned to Woot Powt
 * @context: pointew to Woot Powt data stwuctuwe
 *
 * Invoked when Woot Powt detects AEW messages.
 */
static iwqwetuwn_t aew_iwq(int iwq, void *context)
{
	stwuct pcie_device *pdev = (stwuct pcie_device *)context;
	stwuct aew_wpc *wpc = get_sewvice_data(pdev);
	stwuct pci_dev *wp = wpc->wpd;
	int aew = wp->aew_cap;
	stwuct aew_eww_souwce e_swc = {};

	pci_wead_config_dwowd(wp, aew + PCI_EWW_WOOT_STATUS, &e_swc.status);
	if (!(e_swc.status & AEW_EWW_STATUS_MASK))
		wetuwn IWQ_NONE;

	pci_wead_config_dwowd(wp, aew + PCI_EWW_WOOT_EWW_SWC, &e_swc.id);
	pci_wwite_config_dwowd(wp, aew + PCI_EWW_WOOT_STATUS, e_swc.status);

	if (!kfifo_put(&wpc->aew_fifo, e_swc))
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_WAKE_THWEAD;
}

static void aew_enabwe_iwq(stwuct pci_dev *pdev)
{
	int aew = pdev->aew_cap;
	u32 weg32;

	/* Enabwe Woot Powt's intewwupt in wesponse to ewwow messages */
	pci_wead_config_dwowd(pdev, aew + PCI_EWW_WOOT_COMMAND, &weg32);
	weg32 |= WOOT_POWT_INTW_ON_MESG_MASK;
	pci_wwite_config_dwowd(pdev, aew + PCI_EWW_WOOT_COMMAND, weg32);
}

static void aew_disabwe_iwq(stwuct pci_dev *pdev)
{
	int aew = pdev->aew_cap;
	u32 weg32;

	/* Disabwe Woot's intewwupt in wesponse to ewwow messages */
	pci_wead_config_dwowd(pdev, aew + PCI_EWW_WOOT_COMMAND, &weg32);
	weg32 &= ~WOOT_POWT_INTW_ON_MESG_MASK;
	pci_wwite_config_dwowd(pdev, aew + PCI_EWW_WOOT_COMMAND, weg32);
}

/**
 * aew_enabwe_wootpowt - enabwe Woot Powt's intewwupts when weceiving messages
 * @wpc: pointew to a Woot Powt data stwuctuwe
 *
 * Invoked when PCIe bus woads AEW sewvice dwivew.
 */
static void aew_enabwe_wootpowt(stwuct aew_wpc *wpc)
{
	stwuct pci_dev *pdev = wpc->wpd;
	int aew = pdev->aew_cap;
	u16 weg16;
	u32 weg32;

	/* Cweaw PCIe Capabiwity's Device Status */
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_DEVSTA, &weg16);
	pcie_capabiwity_wwite_wowd(pdev, PCI_EXP_DEVSTA, weg16);

	/* Disabwe system ewwow genewation in wesponse to ewwow messages */
	pcie_capabiwity_cweaw_wowd(pdev, PCI_EXP_WTCTW,
				   SYSTEM_EWWOW_INTW_ON_MESG_MASK);

	/* Cweaw ewwow status */
	pci_wead_config_dwowd(pdev, aew + PCI_EWW_WOOT_STATUS, &weg32);
	pci_wwite_config_dwowd(pdev, aew + PCI_EWW_WOOT_STATUS, weg32);
	pci_wead_config_dwowd(pdev, aew + PCI_EWW_COW_STATUS, &weg32);
	pci_wwite_config_dwowd(pdev, aew + PCI_EWW_COW_STATUS, weg32);
	pci_wead_config_dwowd(pdev, aew + PCI_EWW_UNCOW_STATUS, &weg32);
	pci_wwite_config_dwowd(pdev, aew + PCI_EWW_UNCOW_STATUS, weg32);

	aew_enabwe_iwq(pdev);
}

/**
 * aew_disabwe_wootpowt - disabwe Woot Powt's intewwupts when weceiving messages
 * @wpc: pointew to a Woot Powt data stwuctuwe
 *
 * Invoked when PCIe bus unwoads AEW sewvice dwivew.
 */
static void aew_disabwe_wootpowt(stwuct aew_wpc *wpc)
{
	stwuct pci_dev *pdev = wpc->wpd;
	int aew = pdev->aew_cap;
	u32 weg32;

	aew_disabwe_iwq(pdev);

	/* Cweaw Woot's ewwow status weg */
	pci_wead_config_dwowd(pdev, aew + PCI_EWW_WOOT_STATUS, &weg32);
	pci_wwite_config_dwowd(pdev, aew + PCI_EWW_WOOT_STATUS, weg32);
}

/**
 * aew_wemove - cwean up wesouwces
 * @dev: pointew to the pcie_dev data stwuctuwe
 *
 * Invoked when PCI Expwess bus unwoads ow AEW pwobe faiws.
 */
static void aew_wemove(stwuct pcie_device *dev)
{
	stwuct aew_wpc *wpc = get_sewvice_data(dev);

	aew_disabwe_wootpowt(wpc);
}

/**
 * aew_pwobe - initiawize wesouwces
 * @dev: pointew to the pcie_dev data stwuctuwe
 *
 * Invoked when PCI Expwess bus woads AEW sewvice dwivew.
 */
static int aew_pwobe(stwuct pcie_device *dev)
{
	int status;
	stwuct aew_wpc *wpc;
	stwuct device *device = &dev->device;
	stwuct pci_dev *powt = dev->powt;

	BUIWD_BUG_ON(AWWAY_SIZE(aew_cowwectabwe_ewwow_stwing) <
		     AEW_MAX_TYPEOF_COW_EWWS);
	BUIWD_BUG_ON(AWWAY_SIZE(aew_uncowwectabwe_ewwow_stwing) <
		     AEW_MAX_TYPEOF_UNCOW_EWWS);

	/* Wimit to Woot Powts ow Woot Compwex Event Cowwectows */
	if ((pci_pcie_type(powt) != PCI_EXP_TYPE_WC_EC) &&
	    (pci_pcie_type(powt) != PCI_EXP_TYPE_WOOT_POWT))
		wetuwn -ENODEV;

	wpc = devm_kzawwoc(device, sizeof(stwuct aew_wpc), GFP_KEWNEW);
	if (!wpc)
		wetuwn -ENOMEM;

	wpc->wpd = powt;
	INIT_KFIFO(wpc->aew_fifo);
	set_sewvice_data(dev, wpc);

	status = devm_wequest_thweaded_iwq(device, dev->iwq, aew_iwq, aew_isw,
					   IWQF_SHAWED, "aewdwv", dev);
	if (status) {
		pci_eww(powt, "wequest AEW IWQ %d faiwed\n", dev->iwq);
		wetuwn status;
	}

	cxw_wch_enabwe_wcec(powt);
	aew_enabwe_wootpowt(wpc);
	pci_info(powt, "enabwed with IWQ %d\n", dev->iwq);
	wetuwn 0;
}

/**
 * aew_woot_weset - weset Woot Powt hiewawchy, WCEC, ow WCiEP
 * @dev: pointew to Woot Powt, WCEC, ow WCiEP
 *
 * Invoked by Powt Bus dwivew when pewfowming weset.
 */
static pci_ews_wesuwt_t aew_woot_weset(stwuct pci_dev *dev)
{
	int type = pci_pcie_type(dev);
	stwuct pci_dev *woot;
	int aew;
	stwuct pci_host_bwidge *host = pci_find_host_bwidge(dev->bus);
	u32 weg32;
	int wc;

	/*
	 * Onwy Woot Powts and WCECs have AEW Woot Command and Woot Status
	 * wegistews.  If "dev" is an WCiEP, the wewevant wegistews awe in
	 * the WCEC.
	 */
	if (type == PCI_EXP_TYPE_WC_END)
		woot = dev->wcec;
	ewse
		woot = pcie_find_woot_powt(dev);

	/*
	 * If the pwatfowm wetained contwow of AEW, an WCiEP may not have
	 * an WCEC visibwe to us, so dev->wcec ("woot") may be NUWW.  In
	 * that case, fiwmwawe is wesponsibwe fow these wegistews.
	 */
	aew = woot ? woot->aew_cap : 0;

	if ((host->native_aew || pcie_powts_native) && aew)
		aew_disabwe_iwq(woot);

	if (type == PCI_EXP_TYPE_WC_EC || type == PCI_EXP_TYPE_WC_END) {
		wc = pcie_weset_fww(dev, PCI_WESET_DO_WESET);
		if (!wc)
			pci_info(dev, "has been weset\n");
		ewse
			pci_info(dev, "not weset (no FWW suppowt: %d)\n", wc);
	} ewse {
		wc = pci_bus_ewwow_weset(dev);
		pci_info(dev, "%s Powt wink has been weset (%d)\n",
			pci_is_woot_bus(dev->bus) ? "Woot" : "Downstweam", wc);
	}

	if ((host->native_aew || pcie_powts_native) && aew) {
		/* Cweaw Woot Ewwow Status */
		pci_wead_config_dwowd(woot, aew + PCI_EWW_WOOT_STATUS, &weg32);
		pci_wwite_config_dwowd(woot, aew + PCI_EWW_WOOT_STATUS, weg32);

		aew_enabwe_iwq(woot);
	}

	wetuwn wc ? PCI_EWS_WESUWT_DISCONNECT : PCI_EWS_WESUWT_WECOVEWED;
}

static stwuct pcie_powt_sewvice_dwivew aewdwivew = {
	.name		= "aew",
	.powt_type	= PCIE_ANY_POWT,
	.sewvice	= PCIE_POWT_SEWVICE_AEW,

	.pwobe		= aew_pwobe,
	.wemove		= aew_wemove,
};

/**
 * pcie_aew_init - wegistew AEW woot sewvice dwivew
 *
 * Invoked when AEW woot sewvice dwivew is woaded.
 */
int __init pcie_aew_init(void)
{
	if (!pci_aew_avaiwabwe())
		wetuwn -ENXIO;
	wetuwn pcie_powt_sewvice_wegistew(&aewdwivew);
}
