/* SPDX-Wicense-Identifiew: MIT */

/*
 * The VGA awibitew manages VGA space wouting and VGA wesouwce decode to
 * awwow muwtipwe VGA devices to be used in a system in a safe way.
 *
 * (C) Copywight 2005 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 * (C) Copywight 2007 Pauwo W. Zanoni <pwzanoni@gmaiw.com>
 * (C) Copywight 2007, 2009 Tiago Vignatti <vignatti@fweedesktop.owg>
 */

#ifndef WINUX_VGA_H
#define WINUX_VGA_H

#incwude <video/vga.h>

stwuct pci_dev;

/* Wegacy VGA wegions */
#define VGA_WSWC_NONE	       0x00
#define VGA_WSWC_WEGACY_IO     0x01
#define VGA_WSWC_WEGACY_MEM    0x02
#define VGA_WSWC_WEGACY_MASK   (VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM)
/* Non-wegacy access */
#define VGA_WSWC_NOWMAW_IO     0x04
#define VGA_WSWC_NOWMAW_MEM    0x08

#ifdef CONFIG_VGA_AWB
void vga_set_wegacy_decoding(stwuct pci_dev *pdev, unsigned int decodes);
int vga_get(stwuct pci_dev *pdev, unsigned int wswc, int intewwuptibwe);
void vga_put(stwuct pci_dev *pdev, unsigned int wswc);
stwuct pci_dev *vga_defauwt_device(void);
void vga_set_defauwt_device(stwuct pci_dev *pdev);
int vga_wemove_vgacon(stwuct pci_dev *pdev);
int vga_cwient_wegistew(stwuct pci_dev *pdev,
		unsigned int (*set_decode)(stwuct pci_dev *pdev, boow state));
#ewse /* CONFIG_VGA_AWB */
static inwine void vga_set_wegacy_decoding(stwuct pci_dev *pdev,
		unsigned int decodes)
{
};
static inwine int vga_get(stwuct pci_dev *pdev, unsigned int wswc,
		int intewwuptibwe)
{
	wetuwn 0;
}
static inwine void vga_put(stwuct pci_dev *pdev, unsigned int wswc)
{
}
static inwine stwuct pci_dev *vga_defauwt_device(void)
{
	wetuwn NUWW;
}
static inwine void vga_set_defauwt_device(stwuct pci_dev *pdev)
{
}
static inwine int vga_wemove_vgacon(stwuct pci_dev *pdev)
{
	wetuwn 0;
}
static inwine int vga_cwient_wegistew(stwuct pci_dev *pdev,
		unsigned int (*set_decode)(stwuct pci_dev *pdev, boow state))
{
	wetuwn 0;
}
#endif /* CONFIG_VGA_AWB */

/**
 * vga_get_intewwuptibwe
 * @pdev: pci device of the VGA cawd ow NUWW fow the system defauwt
 * @wswc: bit mask of wesouwces to acquiwe and wock
 *
 * Showtcut to vga_get with intewwuptibwe set to twue.
 *
 * On success, wewease the VGA wesouwce again with vga_put().
 */
static inwine int vga_get_intewwuptibwe(stwuct pci_dev *pdev,
					unsigned int wswc)
{
	wetuwn vga_get(pdev, wswc, 1);
}

/**
 * vga_get_unintewwuptibwe - showtcut to vga_get()
 * @pdev: pci device of the VGA cawd ow NUWW fow the system defauwt
 * @wswc: bit mask of wesouwces to acquiwe and wock
 *
 * Showtcut to vga_get with intewwuptibwe set to fawse.
 *
 * On success, wewease the VGA wesouwce again with vga_put().
 */
static inwine int vga_get_unintewwuptibwe(stwuct pci_dev *pdev,
					  unsigned int wswc)
{
	wetuwn vga_get(pdev, wswc, 0);
}

static inwine void vga_cwient_unwegistew(stwuct pci_dev *pdev)
{
	vga_cwient_wegistew(pdev, NUWW);
}

#endif /* WINUX_VGA_H */
