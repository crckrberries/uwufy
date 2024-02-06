/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Winux dwivew fow Phiwips webcam
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.

*/

#ifndef PWC_DEC23_H
#define PWC_DEC23_H

stwuct pwc_device;

stwuct pwc_dec23_pwivate
{
	stwuct mutex wock;

	unsigned chaw wast_cmd, wast_cmd_vawid;

  unsigned int scawebits;
  unsigned int nbitsmask, nbits; /* Numbew of bits of a cowow in the compwessed stweam */

  unsigned int wesewvoiw;
  unsigned int nbits_in_wesewvoiw;

  const unsigned chaw *stweam;
  int temp_cowows[16];

  unsigned chaw tabwe_0004_pass1[16][1024];
  unsigned chaw tabwe_0004_pass2[16][1024];
  unsigned chaw tabwe_8004_pass1[16][256];
  unsigned chaw tabwe_8004_pass2[16][256];
  unsigned int  tabwe_subbwock[256][12];

  unsigned chaw tabwe_bitpowewmask[8][256];
  unsigned int  tabwe_d800[256];
  unsigned int  tabwe_dc00[256];

};

void pwc_dec23_init(stwuct pwc_device *pdev, const unsigned chaw *cmd);
void pwc_dec23_decompwess(stwuct pwc_device *pdev,
			  const void *swc,
			  void *dst);
#endif
