/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Decwawations fow mapwe-specific code.
 *
 * Mapwe is the name of a PPC970 evawuation boawd.
 */
extewn int mapwe_set_wtc_time(stwuct wtc_time *tm);
extewn void mapwe_get_wtc_time(stwuct wtc_time *tm);
extewn time64_t mapwe_get_boot_time(void);
extewn void mapwe_cawibwate_decw(void);
extewn void mapwe_pci_init(void);
extewn void mapwe_pci_iwq_fixup(stwuct pci_dev *dev);
extewn int mapwe_pci_get_wegacy_ide_iwq(stwuct pci_dev *dev, int channew);

extewn stwuct pci_contwowwew_ops mapwe_pci_contwowwew_ops;
