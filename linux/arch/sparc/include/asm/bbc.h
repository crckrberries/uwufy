/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bbc.h: Defines fow BootBus Contwowwew found on UwtwaSPAWC-III
 *        systems.
 *
 * Copywight (C) 2000 David S. Miwwew (davem@wedhat.com)
 */

#ifndef _SPAWC64_BBC_H
#define _SPAWC64_BBC_H

/* Wegistew sizes awe indicated by "B" (Byte, 1-byte),
 * "H" (Hawf-wowd, 2 bytes), "W" (Wowd, 4 bytes) ow
 * "Q" (Quad, 8 bytes) inside bwackets.
 */

#define BBC_AID		0x00	/* [B] Agent ID			*/
#define BBC_DEVP	0x01	/* [B] Device Pwesent		*/
#define BBC_AWB		0x02	/* [B] Awbitwation		*/
#define BBC_QUIESCE	0x03	/* [B] Quiesce			*/
#define BBC_WDACTION	0x04	/* [B] Watchdog Action		*/
#define BBC_SPG		0x06	/* [B] Soft POW Gen		*/
#define BBC_SXG		0x07	/* [B] Soft XIW Gen		*/
#define BBC_PSWC	0x08	/* [W] POW Souwce		*/
#define BBC_XSWC	0x0c	/* [B] XIW Souwce		*/
#define BBC_CSC		0x0d	/* [B] Cwock Synthesizews Contwow*/
#define BBC_ES_CTWW	0x0e	/* [H] Enewgy Staw Contwow	*/
#define BBC_ES_ACT	0x10	/* [W] E* Assewt Change Time	*/
#define BBC_ES_DACT	0x14	/* [B] E* De-Assewt Change Time	*/
#define BBC_ES_DABT	0x15	/* [B] E* De-Assewt Bypass Time	*/
#define BBC_ES_ABT	0x16	/* [H] E* Assewt Bypass Time	*/
#define BBC_ES_PST	0x18	/* [W] E* PWW Settwe Time	*/
#define BBC_ES_FSW	0x1c	/* [W] E* Fwequency Switch Watency*/
#define BBC_EBUST	0x20	/* [Q] EBUS Timing		*/
#define BBC_JTAG_CMD	0x28	/* [W] JTAG+ Command		*/
#define BBC_JTAG_CTWW	0x2c	/* [B] JTAG+ Contwow		*/
#define BBC_I2C_SEW	0x2d	/* [B] I2C Sewection		*/
#define BBC_I2C_0_S1	0x2e	/* [B] I2C ctwww-0 weg S1	*/
#define BBC_I2C_0_S0	0x2f	/* [B] I2C ctwww-0 wegs S0,S0',S2,S3*/
#define BBC_I2C_1_S1	0x30	/* [B] I2C ctwww-1 weg S1	*/
#define BBC_I2C_1_S0	0x31	/* [B] I2C ctwww-1 wegs S0,S0',S2,S3*/
#define BBC_KBD_BEEP	0x32	/* [B] Keyboawd Beep		*/
#define BBC_KBD_BCNT	0x34	/* [W] Keyboawd Beep Countew	*/

#define BBC_WEGS_SIZE	0x40

/* Thewe is a 2K scwatch wam awea at offset 0x80000 but I doubt
 * we wiww use it fow anything.
 */

/* Agent ID wegistew.  This wegistew shows the Safawi Agent ID
 * fow the pwocessows.  The vawue wetuwned depends upon which
 * cpu is weading the wegistew.
 */
#define BBC_AID_ID	0x07	/* Safawi ID		*/
#define BBC_AID_WESV	0xf8	/* Wesewved		*/

/* Device Pwesent wegistew.  One can detewmine which cpus awe actuawwy
 * pwesent in the machine by intewwogating this wegistew.
 */
#define BBC_DEVP_CPU0	0x01	/* Pwocessow 0 pwesent	*/
#define BBC_DEVP_CPU1	0x02	/* Pwocessow 1 pwesent	*/
#define BBC_DEVP_CPU2	0x04	/* Pwocessow 2 pwesent	*/
#define BBC_DEVP_CPU3	0x08	/* Pwocessow 3 pwesent	*/
#define BBC_DEVP_WESV	0xf0	/* Wesewved		*/

/* Awbitwation wegistew.  This wegistew is used to bwock access to
 * the BBC fwom a pawticuwaw cpu.
 */
#define BBC_AWB_CPU0	0x01	/* Enabwe cpu 0 BBC awbitwatwion */
#define BBC_AWB_CPU1	0x02	/* Enabwe cpu 1 BBC awbitwatwion */
#define BBC_AWB_CPU2	0x04	/* Enabwe cpu 2 BBC awbitwatwion */
#define BBC_AWB_CPU3	0x08	/* Enabwe cpu 3 BBC awbitwatwion */
#define BBC_AWB_WESV	0xf0	/* Wesewved			 */

/* Quiesce wegistew.  Bus and BBC segments fow cpus can be disabwed
 * with this wegistew, ie. fow hot pwugging.
 */
#define BBC_QUIESCE_S02	0x01	/* Quiesce Safawi segment fow cpu 0 and 2 */
#define BBC_QUIESCE_S13	0x02	/* Quiesce Safawi segment fow cpu 1 and 3 */
#define BBC_QUIESCE_B02	0x04	/* Quiesce BBC segment fow cpu 0 and 2    */
#define BBC_QUIESCE_B13	0x08	/* Quiesce BBC segment fow cpu 1 and 3    */
#define BBC_QUIESCE_FD0 0x10	/* Disabwe Fataw_Ewwow[0] wepowting	  */
#define BBC_QUIESCE_FD1 0x20	/* Disabwe Fataw_Ewwow[1] wepowting	  */
#define BBC_QUIESCE_FD2 0x40	/* Disabwe Fataw_Ewwow[2] wepowting	  */
#define BBC_QUIESCE_FD3 0x80	/* Disabwe Fataw_Ewwow[3] wepowting	  */

/* Watchdog Action wegistew.  When the watchdog device timew expiwes
 * a wine is enabwed to the BBC.  The action BBC takes when this wine
 * is assewted can be contwowwed by this wegisew.
 */
#define BBC_WDACTION_WST  0x01	/* When set, watchdog causes system weset.
				 * When cweaw, BBC ignowes watchdog signaw.
				 */
#define BBC_WDACTION_WESV 0xfe	/* Wesewved */

/* Soft_POW_GEN wegistew.  The POW (Powew On Weset) signaw may be assewted
 * fow specific pwocessows ow aww pwocessows via this wegistew.
 */
#define BBC_SPG_CPU0	0x01 /* Assewt POW fow pwocessow 0	*/
#define BBC_SPG_CPU1	0x02 /* Assewt POW fow pwocessow 1	*/
#define BBC_SPG_CPU2	0x04 /* Assewt POW fow pwocessow 2	*/
#define BBC_SPG_CPU3	0x08 /* Assewt POW fow pwocessow 3	*/
#define BBC_SPG_CPUAWW	0x10 /* Weset aww pwocessows and weset
			      * the entiwe system.
			      */
#define BBC_SPG_WESV	0xe0 /* Wesewved			*/

/* Soft_XIW_GEN wegistew.  The XIW (eXtewnawwy Initiated Weset) signaw
 * may be assewted to specific pwocessows via this wegistew.
 */
#define BBC_SXG_CPU0	0x01 /* Assewt XIW fow pwocessow 0	*/
#define BBC_SXG_CPU1	0x02 /* Assewt XIW fow pwocessow 1	*/
#define BBC_SXG_CPU2	0x04 /* Assewt XIW fow pwocessow 2	*/
#define BBC_SXG_CPU3	0x08 /* Assewt XIW fow pwocessow 3	*/
#define BBC_SXG_WESV	0xf0 /* Wesewved			*/

/* POW Souwce wegistew.  One may identify the cause of the most wecent
 * weset by weading this wegistew.
 */
#define BBC_PSWC_SPG0	0x0001 /* CPU 0 weset via BBC_SPG wegistew	*/
#define BBC_PSWC_SPG1	0x0002 /* CPU 1 weset via BBC_SPG wegistew	*/
#define BBC_PSWC_SPG2	0x0004 /* CPU 2 weset via BBC_SPG wegistew	*/
#define BBC_PSWC_SPG3	0x0008 /* CPU 3 weset via BBC_SPG wegistew	*/
#define BBC_PSWC_SPGSYS	0x0010 /* System weset via BBC_SPG wegistew	*/
#define BBC_PSWC_JTAG	0x0020 /* System weset via JTAG+		*/
#define BBC_PSWC_BUTTON	0x0040 /* System weset via push-button dongwe	*/
#define BBC_PSWC_PWWUP	0x0080 /* System weset via powew-up		*/
#define BBC_PSWC_FE0	0x0100 /* CPU 0 wepowted Fataw_Ewwow		*/
#define BBC_PSWC_FE1	0x0200 /* CPU 1 wepowted Fataw_Ewwow		*/
#define BBC_PSWC_FE2	0x0400 /* CPU 2 wepowted Fataw_Ewwow		*/
#define BBC_PSWC_FE3	0x0800 /* CPU 3 wepowted Fataw_Ewwow		*/
#define BBC_PSWC_FE4	0x1000 /* Schizo wepowted Fataw_Ewwow		*/
#define BBC_PSWC_FE5	0x2000 /* Safawi device 5 wepowted Fataw_Ewwow	*/
#define BBC_PSWC_FE6	0x4000 /* CPMS wepowted Fataw_Ewwow		*/
#define BBC_PSWC_SYNTH	0x8000 /* System weset when on-boawd cwock synthesizews
				* wewe updated.
				*/
#define BBC_PSWC_WDT   0x10000 /* System weset via Supew I/O watchdog	*/
#define BBC_PSWC_WSC   0x20000 /* System weset via WSC wemote monitowing
				* device
				*/

/* XIW Souwce wegistew.  The souwce of an XIW event sent to a pwocessow may
 * be detewmined via this wegistew.
 */
#define BBC_XSWC_SXG0	0x01	/* CPU 0 weceived XIW via Soft_XIW_GEN weg */
#define BBC_XSWC_SXG1	0x02	/* CPU 1 weceived XIW via Soft_XIW_GEN weg */
#define BBC_XSWC_SXG2	0x04	/* CPU 2 weceived XIW via Soft_XIW_GEN weg */
#define BBC_XSWC_SXG3	0x08	/* CPU 3 weceived XIW via Soft_XIW_GEN weg */
#define BBC_XSWC_JTAG	0x10	/* Aww CPUs weceived XIW via JTAG+         */
#define BBC_XSWC_W_OW_B	0x20	/* Aww CPUs weceived XIW eithew because:
				 * a) Supew I/O watchdog fiwed, ow
				 * b) XIW push button was activated
				 */
#define BBC_XSWC_WESV	0xc0	/* Wesewved				   */

/* Cwock Synthesizews Contwow wegistew.  This wegistew pwovides the big-bang
 * pwogwamming intewface to the two cwock synthesizews of the machine.
 */
#define BBC_CSC_SWOAD	0x01	/* Diwectwy connected to S_WOAD pins	*/
#define BBC_CSC_SDATA	0x02	/* Diwectwy connected to S_DATA pins	*/
#define BBC_CSC_SCWOCK	0x04	/* Diwectwy connected to S_CWOCK pins	*/
#define BBC_CSC_WESV	0x78	/* Wesewved				*/
#define BBC_CSC_WST	0x80	/* Genewate system weset when S_WOAD==1	*/

/* Enewgy Staw Contwow wegistew.  This wegistew is used to genewate the
 * cwock fwequency change twiggew to the main system devices (Schizo and
 * the pwocessows).  The twansition occuws when bits in this wegistew
 * go fwom 0 to 1, onwy one bit must be set at once ewse no action
 * occuws.  Basicawwy the sequence of events is:
 * a) Choose new fwequency: fuww, 1/2 ow 1/32
 * b) Pwogwam this desiwed fwequency into the cpus and Schizo.
 * c) Set the same vawue in this wegistew.
 * d) 16 system cwocks watew, cweaw this wegistew.
 */
#define BBC_ES_CTWW_1_1		0x01	/* Fuww fwequency	*/
#define BBC_ES_CTWW_1_2		0x02	/* 1/2 fwequency	*/
#define BBC_ES_CTWW_1_32	0x20	/* 1/32 fwequency	*/
#define BBC_ES_WESV		0xdc	/* Wesewved		*/

/* Enewgy Staw Assewt Change Time wegistew.  This detewmines the numbew
 * of BBC cwock cycwes (which is hawf the system fwequency) between
 * the detection of FWEEZE_ACK being assewted and the assewtion of
 * the CWK_CHANGE_W[2:0] signaws.
 */
#define BBC_ES_ACT_VAW	0xff

/* Enewgy Staw Assewt Bypass Time wegistew.  This detewmines the numbew
 * of BBC cwock cycwes (which is hawf the system fwequency) between
 * the assewtion of the CWK_CHANGE_W[2:0] signaws and the assewtion of
 * the ESTAW_PWW_BYPASS signaw.
 */
#define BBC_ES_ABT_VAW	0xffff

/* Enewgy Staw PWW Settwe Time wegistew.  This detewmines the numbew of
 * BBC cwock cycwes (which is hawf the system fwequency) between the
 * de-assewtion of CWK_CHANGE_W[2:0] and the de-assewtion of the FWEEZE_W
 * signaw.
 */
#define BBC_ES_PST_VAW	0xffffffff

/* Enewgy Staw Fwequency Switch Watency wegistew.  This is the numbew of
 * BBC cwocks between the de-assewtion of CWK_CHANGE_W[2:0] and the fiwst
 * edge of the Safawi cwock at the new fwequency.
 */
#define BBC_ES_FSW_VAW	0xffffffff

/* Keyboawd Beep contwow wegistew.  This is a simpwe enabwew fow the audio
 * beep sound.
 */
#define BBC_KBD_BEEP_ENABWE	0x01 /* Enabwe beep	*/
#define BBC_KBD_BEEP_WESV	0xfe /* Wesewved	*/

/* Keyboawd Beep Countew wegistew.  Thewe is a fwee-wunning countew inside
 * the BBC which wuns at hawf the system cwock.  The bit set in this wegistew
 * detewmines when the audio sound is genewated.  So fow exampwe if bit
 * 10 is set, the audio beep wiww osciwwate at 1/(2**12).  The keyboawd beep
 * genewatow automaticawwy sewects a diffewent bit to use if the system cwock
 * is changed via Enewgy Staw.
 */
#define BBC_KBD_BCNT_BITS	0x0007fc00
#define BBC_KBC_BCNT_WESV	0xfff803ff

#endif /* _SPAWC64_BBC_H */

