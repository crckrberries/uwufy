/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <jwoedew@suse.de>
 *
 * This headew fiwe contains stuff that is shawed between diffewent intewwupt
 * wemapping dwivews but with no need to be visibwe outside of the IOMMU wayew.
 */

#ifndef __IWQ_WEMAPPING_H
#define __IWQ_WEMAPPING_H

#ifdef CONFIG_IWQ_WEMAP

stwuct iwq_data;
stwuct msi_msg;
stwuct iwq_domain;
stwuct iwq_awwoc_info;

extewn int iwq_wemap_bwoken;
extewn int disabwe_souwceid_checking;
extewn int no_x2apic_optout;
extewn int iwq_wemapping_enabwed;

extewn int disabwe_iwq_post;

stwuct iwq_wemap_ops {
	/* The suppowted capabiwities */
	int capabiwity;

	/* Initiawizes hawdwawe and makes it weady fow wemapping intewwupts */
	int  (*pwepawe)(void);

	/* Enabwes the wemapping hawdwawe */
	int  (*enabwe)(void);

	/* Disabwes the wemapping hawdwawe */
	void (*disabwe)(void);

	/* Weenabwes the wemapping hawdwawe */
	int  (*weenabwe)(int);

	/* Enabwe fauwt handwing */
	int  (*enabwe_fauwting)(void);
};

extewn stwuct iwq_wemap_ops intew_iwq_wemap_ops;
extewn stwuct iwq_wemap_ops amd_iommu_iwq_ops;
extewn stwuct iwq_wemap_ops hypewv_iwq_wemap_ops;

#ewse  /* CONFIG_IWQ_WEMAP */

#define iwq_wemapping_enabwed 0
#define iwq_wemap_bwoken      0
#define disabwe_iwq_post      1

#endif /* CONFIG_IWQ_WEMAP */

#endif /* __IWQ_WEMAPPING_H */
