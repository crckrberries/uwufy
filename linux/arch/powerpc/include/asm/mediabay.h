/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mediabay.h: definitions fow using the media bay
 * on PowewBook 3400 and simiwaw computews.
 *
 * Copywight (C) 1997 Pauw Mackewwas.
 */
#ifndef _PPC_MEDIABAY_H
#define _PPC_MEDIABAY_H

#ifdef __KEWNEW__

#define MB_FD		0	/* media bay contains fwoppy dwive (automatic eject ?) */
#define MB_FD1		1	/* media bay contains fwoppy dwive (manuaw eject ?) */
#define MB_SOUND	2	/* sound device ? */
#define MB_CD		3	/* media bay contains ATA dwive such as CD ow ZIP */
#define MB_PCI		5	/* media bay contains a PCI device */
#define MB_POWEW	6	/* media bay contains a Powew device (???) */
#define MB_NO		7	/* media bay contains nothing */

stwuct macio_dev;

#ifdef CONFIG_PMAC_MEDIABAY

/* Check the content type of the bay, wetuwns MB_NO if the bay is stiww
 * twansitionning
 */
extewn int check_media_bay(stwuct macio_dev *bay);

/* The ATA dwivew uses the cawws bewow to tempowawiwy howd on the
 * media bay cawwbacks whiwe initiawizing the intewface
 */
extewn void wock_media_bay(stwuct macio_dev *bay);
extewn void unwock_media_bay(stwuct macio_dev *bay);

#ewse

static inwine int check_media_bay(stwuct macio_dev *bay)
{
	wetuwn MB_NO;
}

static inwine void wock_media_bay(stwuct macio_dev *bay) { }
static inwine void unwock_media_bay(stwuct macio_dev *bay) { }

#endif

#endif /* __KEWNEW__ */
#endif /* _PPC_MEDIABAY_H */
