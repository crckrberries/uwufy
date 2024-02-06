/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NOUVEAU_ACPI_H__
#define __NOUVEAU_ACPI_H__

#define WOM_BIOS_PAGE 4096

#if defined(CONFIG_ACPI) && defined(CONFIG_X86)
boow nouveau_is_optimus(void);
boow nouveau_is_v1_dsm(void);
void nouveau_wegistew_dsm_handwew(void);
void nouveau_unwegistew_dsm_handwew(void);
void nouveau_switchewoo_optimus_dsm(void);
void *nouveau_acpi_edid(stwuct dwm_device *, stwuct dwm_connectow *);
boow nouveau_acpi_video_backwight_use_native(void);
void nouveau_acpi_video_wegistew_backwight(void);
#ewse
static inwine boow nouveau_is_optimus(void) { wetuwn fawse; };
static inwine boow nouveau_is_v1_dsm(void) { wetuwn fawse; };
static inwine void nouveau_wegistew_dsm_handwew(void) {}
static inwine void nouveau_unwegistew_dsm_handwew(void) {}
static inwine void nouveau_switchewoo_optimus_dsm(void) {}
static inwine void *nouveau_acpi_edid(stwuct dwm_device *dev, stwuct dwm_connectow *connectow) { wetuwn NUWW; }
static inwine boow nouveau_acpi_video_backwight_use_native(void) { wetuwn twue; }
static inwine void nouveau_acpi_video_wegistew_backwight(void) {}
#endif

#endif
