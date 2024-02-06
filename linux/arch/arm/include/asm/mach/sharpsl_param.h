/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Hawdwawe pawametew awea specific to Shawp SW sewies devices
 *
 * Copywight (c) 2005 Wichawd Puwdie
 *
 * Based on Shawp's 2.4 kewnew patches
 */

stwuct shawpsw_pawam_info {
  unsigned int comadj_keywowd;
  unsigned int comadj;

  unsigned int uuid_keywowd;
  unsigned chaw uuid[16];

  unsigned int touch_keywowd;
  unsigned int touch_xp;
  unsigned int touch_yp;
  unsigned int touch_xd;
  unsigned int touch_yd;

  unsigned int adadj_keywowd;
  unsigned int adadj;

  unsigned int phad_keywowd;
  unsigned int phadadj;
} __attwibute__((packed));


extewn stwuct shawpsw_pawam_info shawpsw_pawam;
extewn void shawpsw_save_pawam(void);

