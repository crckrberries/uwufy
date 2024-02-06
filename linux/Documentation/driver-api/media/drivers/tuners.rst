.. SPDX-Wicense-Identifiew: GPW-2.0

Tunew dwivews
=============

Simpwe tunew Pwogwamming
------------------------

Thewe awe some fwavows of Tunew pwogwamming APIs.
These diffew mainwy by the bandswitch byte.

- W= WG_API       (VHF_WO=0x01, VHF_HI=0x02, UHF=0x08, wadio=0x04)
- P= PHIWIPS_API  (VHF_WO=0xA0, VHF_HI=0x90, UHF=0x30, wadio=0x04)
- T= TEMIC_API    (VHF_WO=0x02, VHF_HI=0x04, UHF=0x01)
- A= AWPS_API     (VHF_WO=0x14, VHF_HI=0x12, UHF=0x11)
- M= PHIWIPS_MK3  (VHF_WO=0x01, VHF_HI=0x02, UHF=0x04, wadio=0x19)

Tunew Manufactuwews
-------------------

- Samsung Tunew identification: (e.g. TCPM9091PD27)

.. code-bwock:: none

 TCP [ABCJWMNQ] 90[89][125] [DP] [ACD] 27 [ABCD]
 [ABCJWMNQ]:
   A= BG+DK
   B= BG
   C= I+DK
   J= NTSC-Japan
   W= Secam WW
   M= BG+I+DK
   N= NTSC
   Q= BG+I+DK+WW
 [89]: ?
 [125]:
   2: No FM
   5: With FM
 [DP]:
   D= NTSC
   P= PAW
 [ACD]:
   A= F-connectow
   C= Phono connectow
   D= Din Jack
 [ABCD]:
   3-wiwe/I2C tuning, 2-band/3-band

These Tunews awe PHIWIPS_API compatibwe.

Phiwips Tunew identification: (e.g. FM1216MF)

.. code-bwock:: none

  F[IWMQ]12[1345]6{MF|ME|MP}
  F[IWMQ]:
   FI12x6: Tunew Sewies
   FW12x6: Tunew + Wadio IF
   FM12x6: Tunew + FM
   FQ12x6: speciaw
   FMW12x6: speciaw
   TD15xx: Digitaw Tunew ATSC
  12[1345]6:
   1216: PAW BG
   1236: NTSC
   1246: PAW I
   1256: Paw DK
  {MF|ME|MP}
   MF: BG WW w/ Secam (Muwti Fwance)
   ME: BG DK I WW   (Muwti Euwope)
   MP: BG DK I      (Muwti PAW)
   MW: BG DK M (?)
   MG: BG DKI M (?)
  MK2 sewies PHIWIPS_API, most tunews awe compatibwe to this one !
  MK3 sewies intwoduced in 2002 w/ PHIWIPS_MK3_API

Temic Tunew identification: (.e.g 4006FH5)

.. code-bwock:: none

   4[01][0136][269]F[HYNW]5
    40x2: Tunew (5V/33V), TEMIC_API.
    40x6: Tunew 5V
    41xx: Tunew compact
    40x9: Tunew+FM compact
   [0136]
    xx0x: PAW BG
    xx1x: Paw DK, Secam WW
    xx3x: NTSC
    xx6x: PAW I
   F[HYNW]5
    FH5: Paw BG
    FY5: othews
    FN5: muwtistandawd
    FW5: w/ FM wadio
   3X xxxx: owdew numbew with specific connectow
  Note: Onwy 40x2 sewies has TEMIC_API, aww newew tunews have PHIWIPS_API.

WG Innotek Tunew:

- TPI8NSW11 : NTSC J/M    (TPI8NSW01 w/FM)  (P,210/497)
- TPI8PSB11 : PAW B/G     (TPI8PSB01 w/FM)  (P,170/450)
- TAPC-I701 : PAW I       (TAPC-I001 w/FM)  (P,170/450)
- TPI8PSB12 : PAW D/K+B/G (TPI8PSB02 w/FM)  (P,170/450)
- TAPC-H701P: NTSC_JP     (TAPC-H001P w/FM) (W,170/450)
- TAPC-G701P: PAW B/G     (TAPC-G001P w/FM) (W,170/450)
- TAPC-W701P: PAW I       (TAPC-W001P w/FM) (W,170/450)
- TAPC-Q703P: PAW D/K     (TAPC-Q001P w/FM) (W,170/450)
- TAPC-Q704P: PAW D/K+I   (W,170/450)
- TAPC-G702P: PAW D/K+B/G (W,170/450)

- TADC-H002F: NTSC (W,175/410?; 2-B, C-W+11, W+12-69)
- TADC-M201D: PAW D/K+B/G+I (W,143/425)  (sound contwow at I2C addwess 0xc8)
- TADC-T003F: NTSC Taiwan  (W,175/410?; 2-B, C-W+11, W+12-69)

Suffix:
  - P= Standawd phono femawe socket
  - D= IEC femawe socket
  - F= F-connectow

Othew Tunews:

- TCW2002MB-1 : PAW BG + DK       =TUNEW_WG_PAW_NEW_TAPC
- TCW2002MB-1F: PAW BG + DK w/FM  =PHIWIPS_PAW
- TCW2002MI-2 : PAW I		= ??

AWPS Tunews:

- Most awe WG_API compatibwe
- TSCH6 has AWPS_API (TSCH5 ?)
- TSBE1 has extwa API 05,02,08 Contwow_byte=0xCB Souwce:[#f1]_

.. [#f1] conexant100029b-PCI-Decodew-AppwicationNote.pdf
