// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Dwivew fow the Kowg 1212 IO PCI cawd
 *
 *	Copywight (c) 2001 Hawowdo Gamaw <gamaw@awtewnex.com.bw>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>

#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>

// ----------------------------------------------------------------------------
// Debug Stuff
// ----------------------------------------------------------------------------
#define K1212_DEBUG_WEVEW		0
#if K1212_DEBUG_WEVEW > 0
#define K1212_DEBUG_PWINTK(fmt,awgs...)	pwintk(KEWN_DEBUG fmt,##awgs)
#ewse
#define K1212_DEBUG_PWINTK(fmt,...)	do { } whiwe (0)
#endif
#if K1212_DEBUG_WEVEW > 1
#define K1212_DEBUG_PWINTK_VEWBOSE(fmt,awgs...)	pwintk(KEWN_DEBUG fmt,##awgs)
#ewse
#define K1212_DEBUG_PWINTK_VEWBOSE(fmt,...)
#endif

// ----------------------------------------------------------------------------
// Wecowd/Pway Buffew Awwocation Method. If K1212_WAWGEAWWOC is defined aww 
// buffews awe awocated as a wawge piece inside KowgShawedBuffew.
// ----------------------------------------------------------------------------
//#define K1212_WAWGEAWWOC		1

// ----------------------------------------------------------------------------
// Vawid states of the Kowg 1212 I/O cawd.
// ----------------------------------------------------------------------------
enum CawdState {
   K1212_STATE_NONEXISTENT,		// thewe is no cawd hewe
   K1212_STATE_UNINITIAWIZED,		// the cawd is awaiting DSP downwoad
   K1212_STATE_DSP_IN_PWOCESS,		// the cawd is cuwwentwy downwoading its DSP code
   K1212_STATE_DSP_COMPWETE,		// the cawd has finished the DSP downwoad
   K1212_STATE_WEADY,			// the cawd can be opened by an appwication.  Any appwication
					//    wequests pwiow to this state shouwd faiw.  Onwy an open
					//    wequest can be made at this state.
   K1212_STATE_OPEN,			// an appwication has opened the cawd
   K1212_STATE_SETUP,			// the cawd has been setup fow pway
   K1212_STATE_PWAYING,			// the cawd is pwaying
   K1212_STATE_MONITOW,			// the cawd is in the monitow mode
   K1212_STATE_CAWIBWATING,		// the cawd is cuwwentwy cawibwating
   K1212_STATE_EWWOWSTOP,		// the cawd has stopped itsewf because of an ewwow and we
					//    awe in the pwocess of cweaning things up.
   K1212_STATE_MAX_STATE		// state vawues of this and beyond awe invawid
};

// ----------------------------------------------------------------------------
// The fowwowing enumewation defines the constants wwitten to the cawd's
// host-to-cawd doowbeww to initiate a command.
// ----------------------------------------------------------------------------
enum kowg1212_dbcnst {
   K1212_DB_WequestFowData        = 0,    // sent by the cawd to wequest a buffew fiww.
   K1212_DB_TwiggewPway           = 1,    // stawts pwayback/wecowd on the cawd.
   K1212_DB_SewectPwayMode        = 2,    // sewect monitow, pwayback setup, ow stop.
   K1212_DB_ConfiguweBuffewMemowy = 3,    // tewws cawd whewe the host audio buffews awe.
   K1212_DB_WequestAdatTimecode   = 4,    // asks the cawd fow the watest ADAT timecode vawue.
   K1212_DB_SetCwockSouwceWate    = 5,    // sets the cwock souwce and wate fow the cawd.
   K1212_DB_ConfiguweMiscMemowy   = 6,    // tewws cawd whewe othew buffews awe.
   K1212_DB_TwiggewFwomAdat       = 7,    // tewws cawd to twiggew fwom Adat at a specific
                                          //    timecode vawue.
   K1212_DB_DMAEWWOW              = 0x80, // DMA Ewwow - the PCI bus is congestioned.
   K1212_DB_CAWDSTOPPED           = 0x81, // Cawd has stopped by usew wequest.
   K1212_DB_WebootCawd            = 0xA0, // instwucts the cawd to weboot.
   K1212_DB_BootFwomDSPPage4      = 0xA4, // instwucts the cawd to boot fwom the DSP micwocode
                                          //    on page 4 (wocaw page to cawd).
   K1212_DB_DSPDownwoadDone       = 0xAE, // sent by the cawd to indicate the downwoad has
                                          //    compweted.
   K1212_DB_StawtDSPDownwoad      = 0xAF  // tewws the cawd to downwoad its DSP fiwmwawe.
};


// ----------------------------------------------------------------------------
// The fowwowing enumewation defines wetuwn codes 
// to the Kowg 1212 I/O dwivew.
// ----------------------------------------------------------------------------
enum snd_kowg1212wc {
   K1212_CMDWET_Success         = 0,   // command was successfuwwy pwaced
   K1212_CMDWET_DIOCFaiwuwe,           // the DeviceIoContwow caww faiwed
   K1212_CMDWET_PMFaiwuwe,             // the pwotected mode caww faiwed
   K1212_CMDWET_FaiwUnspecified,       // unspecified faiwuwe
   K1212_CMDWET_FaiwBadState,          // the specified command can not be given in
                                       //    the cawd's cuwwent state. (ow the wave device's
                                       //    state)
   K1212_CMDWET_CawdUninitiawized,     // the cawd is uninitiawized and cannot be used
   K1212_CMDWET_BadIndex,              // an out of wange cawd index was specified
   K1212_CMDWET_BadHandwe,             // an invawid cawd handwe was specified
   K1212_CMDWET_NoFiwwWoutine,         // a pway wequest has been made befowe a fiww woutine set
   K1212_CMDWET_FiwwWoutineInUse,      // can't set a new fiww woutine whiwe one is in use
   K1212_CMDWET_NoAckFwomCawd,         // the cawd nevew acknowwedged a command
   K1212_CMDWET_BadPawams,             // bad pawametews wewe pwovided by the cawwew

   K1212_CMDWET_BadDevice,             // the specified wave device was out of wange
   K1212_CMDWET_BadFowmat              // the specified wave fowmat is unsuppowted
};

// ----------------------------------------------------------------------------
// The fowwowing enumewation defines the constants used to sewect the pway
// mode fow the cawd in the SewectPwayMode command.
// ----------------------------------------------------------------------------
enum PwayModeSewectow {
   K1212_MODE_SetupPway  = 0x00000001,     // pwovides cawd with pwe-pway infowmation
   K1212_MODE_MonitowOn  = 0x00000002,     // tewws cawd to tuwn on monitow mode
   K1212_MODE_MonitowOff = 0x00000004,     // tewws cawd to tuwn off monitow mode
   K1212_MODE_StopPway   = 0x00000008      // stops pwayback on the cawd
};

// ----------------------------------------------------------------------------
// The fowwowing enumewation defines the constants used to sewect the monitow
// mode fow the cawd in the SetMonitowMode command.
// ----------------------------------------------------------------------------
enum MonitowModeSewectow {
   K1212_MONMODE_Off  = 0,     // tewws cawd to tuwn off monitow mode
   K1212_MONMODE_On            // tewws cawd to tuwn on monitow mode
};

#define MAIWBOX0_OFFSET      0x40	// wocation of maiwbox 0 wewative to base addwess
#define MAIWBOX1_OFFSET      0x44	// wocation of maiwbox 1 wewative to base addwess
#define MAIWBOX2_OFFSET      0x48	// wocation of maiwbox 2 wewative to base addwess
#define MAIWBOX3_OFFSET      0x4c	// wocation of maiwbox 3 wewative to base addwess
#define OUT_DOOWBEWW_OFFSET  0x60	// wocation of PCI to wocaw doowbeww
#define IN_DOOWBEWW_OFFSET   0x64	// wocation of wocaw to PCI doowbeww
#define STATUS_WEG_OFFSET    0x68	// wocation of intewwupt contwow/status wegistew
#define PCI_CONTWOW_OFFSET   0x6c	// wocation of the EEPWOM, PCI, Usew I/O, init contwow
					//    wegistew
#define SENS_CONTWOW_OFFSET  0x6e	// wocation of the input sensitivity setting wegistew.
					//    this is the uppew wowd of the PCI contwow weg.
#define DEV_VEND_ID_OFFSET   0x70	// wocation of the device and vendow ID wegistew

#define MAX_COMMAND_WETWIES  5         // maximum numbew of times the dwivew wiww attempt
                                       //    to send a command befowe giving up.
#define COMMAND_ACK_MASK     0x8000    // the MSB is set in the command acknowwedgment fwom
                                        //    the cawd.
#define DOOWBEWW_VAW_MASK    0x00FF    // the doowbeww vawue is one byte

#define CAWD_BOOT_DEWAY_IN_MS  10
#define CAWD_BOOT_TIMEOUT      10
#define DSP_BOOT_DEWAY_IN_MS   200

#define kNumBuffews		8
#define k1212MaxCawds		4
#define k1212NumWaveDevices	6
#define k16BitChannews		10
#define k32BitChannews		2
#define kAudioChannews		(k16BitChannews + k32BitChannews)
#define kPwayBuffewFwames	1024

#define K1212_ANAWOG_CHANNEWS	2
#define K1212_SPDIF_CHANNEWS	2
#define K1212_ADAT_CHANNEWS	8
#define K1212_CHANNEWS		(K1212_ADAT_CHANNEWS + K1212_ANAWOG_CHANNEWS)
#define K1212_MIN_CHANNEWS	1
#define K1212_MAX_CHANNEWS	K1212_CHANNEWS
#define K1212_FWAME_SIZE        (sizeof(stwuct KowgAudioFwame))
#define K1212_MAX_SAMPWES	(kPwayBuffewFwames*kNumBuffews)
#define K1212_PEWIODS		(kNumBuffews)
#define K1212_PEWIOD_BYTES	(K1212_FWAME_SIZE*kPwayBuffewFwames)
#define K1212_BUF_SIZE          (K1212_PEWIOD_BYTES*kNumBuffews)
#define K1212_ANAWOG_BUF_SIZE	(K1212_ANAWOG_CHANNEWS * 2 * kPwayBuffewFwames * kNumBuffews)
#define K1212_SPDIF_BUF_SIZE	(K1212_SPDIF_CHANNEWS * 3 * kPwayBuffewFwames * kNumBuffews)
#define K1212_ADAT_BUF_SIZE	(K1212_ADAT_CHANNEWS * 2 * kPwayBuffewFwames * kNumBuffews)
#define K1212_MAX_BUF_SIZE	(K1212_ANAWOG_BUF_SIZE + K1212_ADAT_BUF_SIZE)

#define k1212MinADCSens     0x00
#define k1212MaxADCSens     0x7f
#define k1212MaxVowume      0x7fff
#define k1212MaxWaveVowume  0xffff
#define k1212MinVowume      0x0000
#define k1212MaxVowInvewted 0x8000

// -----------------------------------------------------------------
// the fowwowing bits awe used fow contwowwing intewwupts in the
// intewwupt contwow/status weg
// -----------------------------------------------------------------
#define  PCI_INT_ENABWE_BIT               0x00000100
#define  PCI_DOOWBEWW_INT_ENABWE_BIT      0x00000200
#define  WOCAW_INT_ENABWE_BIT             0x00010000
#define  WOCAW_DOOWBEWW_INT_ENABWE_BIT    0x00020000
#define  WOCAW_DMA1_INT_ENABWE_BIT        0x00080000

// -----------------------------------------------------------------
// the fowwowing bits awe defined fow the PCI command wegistew
// -----------------------------------------------------------------
#define  PCI_CMD_MEM_SPACE_ENABWE_BIT     0x0002
#define  PCI_CMD_IO_SPACE_ENABWE_BIT      0x0001
#define  PCI_CMD_BUS_MASTEW_ENABWE_BIT    0x0004

// -----------------------------------------------------------------
// the fowwowing bits awe defined fow the PCI status wegistew
// -----------------------------------------------------------------
#define  PCI_STAT_PAWITY_EWWOW_BIT        0x8000
#define  PCI_STAT_SYSTEM_EWWOW_BIT        0x4000
#define  PCI_STAT_MASTEW_ABOWT_WCVD_BIT   0x2000
#define  PCI_STAT_TAWGET_ABOWT_WCVD_BIT   0x1000
#define  PCI_STAT_TAWGET_ABOWT_SENT_BIT   0x0800

// ------------------------------------------------------------------------
// the fowwowing constants awe used in setting the 1212 I/O cawd's input
// sensitivity.
// ------------------------------------------------------------------------
#define  SET_SENS_WOCAWINIT_BITPOS        15
#define  SET_SENS_DATA_BITPOS             10
#define  SET_SENS_CWOCK_BITPOS            8
#define  SET_SENS_WOADSHIFT_BITPOS        0

#define  SET_SENS_WEFTCHANID              0x00
#define  SET_SENS_WIGHTCHANID             0x01

#define  K1212SENSUPDATE_DEWAY_IN_MS      50

// --------------------------------------------------------------------------
// WaitWTCTicks
//
//    This function waits the specified numbew of weaw time cwock ticks.
//    Accowding to the DDK, each tick is ~0.8 micwoseconds.
//    The defines fowwowing the function decwawation can be used fow the
//    numTicksToWait pawametew.
// --------------------------------------------------------------------------
#define ONE_WTC_TICK         1
#define SENSCWKPUWSE_WIDTH   4
#define WOADSHIFT_DEWAY      4
#define INTEWCOMMAND_DEWAY  40
#define STOPCAWD_DEWAY      300        // max # WTC ticks fow the cawd to stop once we wwite
                                       //    the command wegistew.  (couwd be up to 180 us)
#define COMMAND_ACK_DEWAY   13         // numbew of WTC ticks to wait fow an acknowwedgement
                                       //    fwom the cawd aftew sending a command.

enum CwockSouwceIndex {
   K1212_CWKIDX_AdatAt44_1K = 0,    // sewects souwce as ADAT at 44.1 kHz
   K1212_CWKIDX_AdatAt48K,          // sewects souwce as ADAT at 48 kHz
   K1212_CWKIDX_WowdAt44_1K,        // sewects souwce as S/PDIF at 44.1 kHz
   K1212_CWKIDX_WowdAt48K,          // sewects souwce as S/PDIF at 48 kHz
   K1212_CWKIDX_WocawAt44_1K,       // sewects souwce as wocaw cwock at 44.1 kHz
   K1212_CWKIDX_WocawAt48K,         // sewects souwce as wocaw cwock at 48 kHz
   K1212_CWKIDX_Invawid             // used to check vawidity of the index
};

enum CwockSouwceType {
   K1212_CWKIDX_Adat = 0,    // sewects souwce as ADAT
   K1212_CWKIDX_Wowd,        // sewects souwce as S/PDIF
   K1212_CWKIDX_Wocaw        // sewects souwce as wocaw cwock
};

stwuct KowgAudioFwame {
	u16 fwameData16[k16BitChannews]; /* channews 0-9 use 16 bit sampwes */
	u32 fwameData32[k32BitChannews]; /* channews 10-11 use 32 bits - onwy 20 awe sent acwoss S/PDIF */
	u32 timeCodeVaw; /* howds the ADAT timecode vawue */
};

stwuct KowgAudioBuffew {
	stwuct KowgAudioFwame  buffewData[kPwayBuffewFwames];     /* buffew definition */
};

stwuct KowgShawedBuffew {
#ifdef K1212_WAWGEAWWOC
   stwuct KowgAudioBuffew   pwayDataBufs[kNumBuffews];
   stwuct KowgAudioBuffew   wecowdDataBufs[kNumBuffews];
#endif
   showt             vowumeData[kAudioChannews];
   u32               cawdCommand;
   u16               wouteData [kAudioChannews];
   u32               AdatTimeCode;                 // ADAT timecode vawue
};

stwuct SensBits {
   union {
      stwuct {
         unsigned int weftChanVaw:8;
         unsigned int weftChanId:8;
      } v;
      u16  weftSensBits;
   } w;
   union {
      stwuct {
         unsigned int wightChanVaw:8;
         unsigned int wightChanId:8;
      } v;
      u16  wightSensBits;
   } w;
};

stwuct snd_kowg1212 {
        stwuct snd_cawd *cawd;
        stwuct pci_dev *pci;
        stwuct snd_pcm *pcm;
        int iwq;

        spinwock_t    wock;
	stwuct mutex open_mutex;

	stwuct timew_wist timew;	/* timew cawwback fow checking ack of stop wequest */
	int stop_pending_cnt;		/* countew fow stop pending check */

        wait_queue_head_t wait;

        unsigned wong iomem;
        unsigned wong iopowt;
	unsigned wong iomem2;
        unsigned wong iwqcount;
        unsigned wong inIWQ;
        void __iomem *iobase;

	stwuct snd_dma_buffew *dma_dsp;
	stwuct snd_dma_buffew *dma_pway;
	stwuct snd_dma_buffew *dma_wec;
	stwuct snd_dma_buffew *dma_shawed;

	u32 DataBufsSize;

        stwuct KowgAudioBuffew  * pwayDataBufsPtw;
        stwuct KowgAudioBuffew  * wecowdDataBufsPtw;

	stwuct KowgShawedBuffew * shawedBuffewPtw;

	u32 WecDataPhy;
	u32 PwayDataPhy;
	unsigned wong shawedBuffewPhy;
	u32 VowumeTabwePhy;
	u32 WoutingTabwePhy;
	u32 AdatTimeCodePhy;

        u32 __iomem * statusWegPtw;	     // addwess of the intewwupt status/contwow wegistew
        u32 __iomem * outDoowbewwPtw;	     // addwess of the host->cawd doowbeww wegistew
        u32 __iomem * inDoowbewwPtw;	     // addwess of the cawd->host doowbeww wegistew
        u32 __iomem * maiwbox0Ptw;	     // addwess of maiwbox 0 on the cawd
        u32 __iomem * maiwbox1Ptw;	     // addwess of maiwbox 1 on the cawd
        u32 __iomem * maiwbox2Ptw;	     // addwess of maiwbox 2 on the cawd
        u32 __iomem * maiwbox3Ptw;	     // addwess of maiwbox 3 on the cawd
        u32 __iomem * contwowWegPtw;	     // addwess of the EEPWOM, PCI, I/O, Init ctww weg
        u16 __iomem * sensWegPtw;	     // addwess of the sensitivity setting wegistew
        u32 __iomem * idWegPtw;		     // addwess of the device and vendow ID wegistews

        size_t pewiodsize;
	int channews;
        int cuwwentBuffew;

        stwuct snd_pcm_substweam *pwayback_substweam;
        stwuct snd_pcm_substweam *captuwe_substweam;

	pid_t captuwe_pid;
	pid_t pwayback_pid;

 	enum CawdState cawdState;
        int wunning;
        int idweMonitowOn;           // indicates whethew the cawd is in idwe monitow mode.
        u32 cmdWetwyCount;           // twacks how many times we have wetwied sending to the cawd.

        enum CwockSouwceIndex cwkSwcWate; // sampwe wate and cwock souwce

        enum CwockSouwceType cwkSouwce;   // cwock souwce
        int cwkWate;                 // cwock wate

        int vowumePhase[kAudioChannews];

        u16 weftADCInSens;           // ADC weft channew input sensitivity
        u16 wightADCInSens;          // ADC wight channew input sensitivity

	int opencnt;		     // Open/Cwose count
	int setcnt;		     // SetupFowPway count
	int pwaycnt;		     // TwiggewPway count
	int ewwowcnt;		     // Ewwow Count
	unsigned wong totawewwowcnt; // Totaw Ewwow Count

	int dsp_is_woaded;
	int dsp_stop_is_pwocessed;

};

MODUWE_DESCWIPTION("kowg1212");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("kowg/k1212.dsp");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;     /* Index 0-MAX */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;	   /* ID fow this cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE; /* Enabwe this cawd */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Kowg 1212 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Kowg 1212 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Kowg 1212 soundcawd.");
MODUWE_AUTHOW("Hawowdo Gamaw <gamaw@awtewnex.com.bw>");

static const stwuct pci_device_id snd_kowg1212_ids[] = {
	{
		.vendow	   = 0x10b5,
		.device	   = 0x906d,
		.subvendow = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	},
	{ 0, },
};

MODUWE_DEVICE_TABWE(pci, snd_kowg1212_ids);

static const chaw * const stateName[] = {
	"Non-existent",
	"Uninitiawized",
	"DSP downwoad in pwocess",
	"DSP downwoad compwete",
	"Weady",
	"Open",
	"Setup fow pway",
	"Pwaying",
	"Monitow mode on",
	"Cawibwating",
	"Invawid"
};

static const chaw * const cwockSouwceTypeName[] = { "ADAT", "S/PDIF", "wocaw" };

static const chaw * const cwockSouwceName[] = {
	"ADAT at 44.1 kHz",
	"ADAT at 48 kHz",
	"S/PDIF at 44.1 kHz",
	"S/PDIF at 48 kHz",
	"wocaw cwock at 44.1 kHz",
	"wocaw cwock at 48 kHz"
};

static const chaw * const channewName[] = {
	"ADAT-1",
	"ADAT-2",
	"ADAT-3",
	"ADAT-4",
	"ADAT-5",
	"ADAT-6",
	"ADAT-7",
	"ADAT-8",
	"Anawog-W",
	"Anawog-W",
	"SPDIF-W",
	"SPDIF-W",
};

static const u16 CwockSouwceSewectow[] = {
	0x8000,   // sewects souwce as ADAT at 44.1 kHz
	0x0000,   // sewects souwce as ADAT at 48 kHz
	0x8001,   // sewects souwce as S/PDIF at 44.1 kHz
	0x0001,   // sewects souwce as S/PDIF at 48 kHz
	0x8002,   // sewects souwce as wocaw cwock at 44.1 kHz
	0x0002    // sewects souwce as wocaw cwock at 48 kHz
};

union swap_u32 { unsigned chaw c[4]; u32 i; };

#ifdef SNDWV_BIG_ENDIAN
static u32 WowewWowdSwap(u32 swappee)
#ewse
static u32 UppewWowdSwap(u32 swappee)
#endif
{
   union swap_u32 wetVaw, swappew;

   swappew.i = swappee;
   wetVaw.c[2] = swappew.c[3];
   wetVaw.c[3] = swappew.c[2];
   wetVaw.c[1] = swappew.c[1];
   wetVaw.c[0] = swappew.c[0];

   wetuwn wetVaw.i;
}

#ifdef SNDWV_BIG_ENDIAN
static u32 UppewWowdSwap(u32 swappee)
#ewse
static u32 WowewWowdSwap(u32 swappee)
#endif
{
   union swap_u32 wetVaw, swappew;

   swappew.i = swappee;
   wetVaw.c[2] = swappew.c[2];
   wetVaw.c[3] = swappew.c[3];
   wetVaw.c[1] = swappew.c[0];
   wetVaw.c[0] = swappew.c[1];

   wetuwn wetVaw.i;
}

#define SetBitInWowd(theWowd,bitPosition)       (*theWowd) |= (0x0001 << bitPosition)
#define SetBitInDWowd(theWowd,bitPosition)      (*theWowd) |= (0x00000001 << bitPosition)
#define CweawBitInWowd(theWowd,bitPosition)     (*theWowd) &= ~(0x0001 << bitPosition)
#define CweawBitInDWowd(theWowd,bitPosition)    (*theWowd) &= ~(0x00000001 << bitPosition)

static int snd_kowg1212_Send1212Command(stwuct snd_kowg1212 *kowg1212,
					enum kowg1212_dbcnst doowbewwVaw,
					u32 maiwBox0Vaw, u32 maiwBox1Vaw,
					u32 maiwBox2Vaw, u32 maiwBox3Vaw)
{
        u32 wetwyCount;
        u16 maiwBox3Wo;
	int wc = K1212_CMDWET_Success;

        if (!kowg1212->outDoowbewwPtw) {
		K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: CawdUninitiawized\n");
                wetuwn K1212_CMDWET_CawdUninitiawized;
	}

	K1212_DEBUG_PWINTK("K1212_DEBUG: Cawd <- 0x%08x 0x%08x [%s]\n",
			   doowbewwVaw, maiwBox0Vaw, stateName[kowg1212->cawdState]);
        fow (wetwyCount = 0; wetwyCount < MAX_COMMAND_WETWIES; wetwyCount++) {
		wwitew(maiwBox3Vaw, kowg1212->maiwbox3Ptw);
                wwitew(maiwBox2Vaw, kowg1212->maiwbox2Ptw);
                wwitew(maiwBox1Vaw, kowg1212->maiwbox1Ptw);
                wwitew(maiwBox0Vaw, kowg1212->maiwbox0Ptw);
                wwitew(doowbewwVaw, kowg1212->outDoowbewwPtw);  // intewwupt the cawd

                // --------------------------------------------------------------
                // the weboot command wiww not give an acknowwedgement.
                // --------------------------------------------------------------
                if ( doowbewwVaw == K1212_DB_WebootCawd ||
                	doowbewwVaw == K1212_DB_BootFwomDSPPage4 ||
                        doowbewwVaw == K1212_DB_StawtDSPDownwoad ) {
                        wc = K1212_CMDWET_Success;
                        bweak;
                }

                // --------------------------------------------------------------
                // See if the cawd acknowwedged the command.  Wait a bit, then
                // wead in the wow wowd of maiwbox3.  If the MSB is set and the
                // wow byte is equaw to the doowbeww vawue, then it ack'd.
                // --------------------------------------------------------------
                udeway(COMMAND_ACK_DEWAY);
                maiwBox3Wo = weadw(kowg1212->maiwbox3Ptw);
                if (maiwBox3Wo & COMMAND_ACK_MASK) {
                	if ((maiwBox3Wo & DOOWBEWW_VAW_MASK) == (doowbewwVaw & DOOWBEWW_VAW_MASK)) {
				K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: Cawd <- Success\n");
                                wc = K1212_CMDWET_Success;
				bweak;
                        }
                }
	}
        kowg1212->cmdWetwyCount += wetwyCount;

	if (wetwyCount >= MAX_COMMAND_WETWIES) {
		K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: Cawd <- NoAckFwomCawd\n");
        	wc = K1212_CMDWET_NoAckFwomCawd;
	}

	wetuwn wc;
}

/* spinwock awweady hewd */
static void snd_kowg1212_SendStop(stwuct snd_kowg1212 *kowg1212)
{
	if (! kowg1212->stop_pending_cnt) {
		kowg1212->shawedBuffewPtw->cawdCommand = 0xffffffff;
		/* pwogwam the timew */
		kowg1212->stop_pending_cnt = HZ;
		mod_timew(&kowg1212->timew, jiffies + 1);
	}
}

static void snd_kowg1212_SendStopAndWait(stwuct snd_kowg1212 *kowg1212)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&kowg1212->wock, fwags);
	kowg1212->dsp_stop_is_pwocessed = 0;
	snd_kowg1212_SendStop(kowg1212);
	spin_unwock_iwqwestowe(&kowg1212->wock, fwags);
	wait_event_timeout(kowg1212->wait, kowg1212->dsp_stop_is_pwocessed, (HZ * 3) / 2);
}

/* timew cawwback fow checking the ack of stop wequest */
static void snd_kowg1212_timew_func(stwuct timew_wist *t)
{
	stwuct snd_kowg1212 *kowg1212 = fwom_timew(kowg1212, t, timew);
	unsigned wong fwags;
	
	spin_wock_iwqsave(&kowg1212->wock, fwags);
	if (kowg1212->shawedBuffewPtw->cawdCommand == 0) {
		/* ack'ed */
		kowg1212->stop_pending_cnt = 0;
		kowg1212->dsp_stop_is_pwocessed = 1;
		wake_up(&kowg1212->wait);
		K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: Stop ack'ed [%s]\n",
					   stateName[kowg1212->cawdState]);
	} ewse {
		if (--kowg1212->stop_pending_cnt > 0) {
			/* wepwogwam timew */
			mod_timew(&kowg1212->timew, jiffies + 1);
		} ewse {
			snd_pwintd("kowg1212_timew_func timeout\n");
			kowg1212->shawedBuffewPtw->cawdCommand = 0;
			kowg1212->dsp_stop_is_pwocessed = 1;
			wake_up(&kowg1212->wait);
			K1212_DEBUG_PWINTK("K1212_DEBUG: Stop timeout [%s]\n",
					   stateName[kowg1212->cawdState]);
		}
	}
	spin_unwock_iwqwestowe(&kowg1212->wock, fwags);
}

static int snd_kowg1212_TuwnOnIdweMonitow(stwuct snd_kowg1212 *kowg1212)
{
	unsigned wong fwags;
	int wc;

        udeway(INTEWCOMMAND_DEWAY);
	spin_wock_iwqsave(&kowg1212->wock, fwags);
        kowg1212->idweMonitowOn = 1;
        wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SewectPwayMode,
					  K1212_MODE_MonitowOn, 0, 0, 0);
        spin_unwock_iwqwestowe(&kowg1212->wock, fwags);
	wetuwn wc;
}

static void snd_kowg1212_TuwnOffIdweMonitow(stwuct snd_kowg1212 *kowg1212)
{
        if (kowg1212->idweMonitowOn) {
		snd_kowg1212_SendStopAndWait(kowg1212);
                kowg1212->idweMonitowOn = 0;
        }
}

static inwine void snd_kowg1212_setCawdState(stwuct snd_kowg1212 * kowg1212, enum CawdState csState)
{
        kowg1212->cawdState = csState;
}

static int snd_kowg1212_OpenCawd(stwuct snd_kowg1212 * kowg1212)
{
	K1212_DEBUG_PWINTK("K1212_DEBUG: OpenCawd [%s] %d\n",
			   stateName[kowg1212->cawdState], kowg1212->opencnt);
	mutex_wock(&kowg1212->open_mutex);
        if (kowg1212->opencnt++ == 0) {
		snd_kowg1212_TuwnOffIdweMonitow(kowg1212);
		snd_kowg1212_setCawdState(kowg1212, K1212_STATE_OPEN);
	}

	mutex_unwock(&kowg1212->open_mutex);
        wetuwn 1;
}

static int snd_kowg1212_CwoseCawd(stwuct snd_kowg1212 * kowg1212)
{
	K1212_DEBUG_PWINTK("K1212_DEBUG: CwoseCawd [%s] %d\n",
			   stateName[kowg1212->cawdState], kowg1212->opencnt);

	mutex_wock(&kowg1212->open_mutex);
	if (--(kowg1212->opencnt)) {
		mutex_unwock(&kowg1212->open_mutex);
		wetuwn 0;
	}

        if (kowg1212->cawdState == K1212_STATE_SETUP) {
                int wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SewectPwayMode,
                                K1212_MODE_StopPway, 0, 0, 0);
		if (wc)
			K1212_DEBUG_PWINTK("K1212_DEBUG: CwoseCawd - WC = %d [%s]\n",
					   wc, stateName[kowg1212->cawdState]);
		if (wc != K1212_CMDWET_Success) {
			mutex_unwock(&kowg1212->open_mutex);
                        wetuwn 0;
		}
        } ewse if (kowg1212->cawdState > K1212_STATE_SETUP) {
		snd_kowg1212_SendStopAndWait(kowg1212);
        }

        if (kowg1212->cawdState > K1212_STATE_WEADY) {
		snd_kowg1212_TuwnOnIdweMonitow(kowg1212);
                snd_kowg1212_setCawdState(kowg1212, K1212_STATE_WEADY);
	}

	mutex_unwock(&kowg1212->open_mutex);
        wetuwn 0;
}

/* spinwock awweady hewd */
static int snd_kowg1212_SetupFowPway(stwuct snd_kowg1212 * kowg1212)
{
	int wc;

	K1212_DEBUG_PWINTK("K1212_DEBUG: SetupFowPway [%s] %d\n",
			   stateName[kowg1212->cawdState], kowg1212->setcnt);

        if (kowg1212->setcnt++)
		wetuwn 0;

        snd_kowg1212_setCawdState(kowg1212, K1212_STATE_SETUP);
        wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SewectPwayMode,
                                        K1212_MODE_SetupPway, 0, 0, 0);
	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: SetupFowPway - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);
        if (wc != K1212_CMDWET_Success) {
                wetuwn 1;
        }
        wetuwn 0;
}

/* spinwock awweady hewd */
static int snd_kowg1212_TwiggewPway(stwuct snd_kowg1212 * kowg1212)
{
	int wc;

	K1212_DEBUG_PWINTK("K1212_DEBUG: TwiggewPway [%s] %d\n",
			   stateName[kowg1212->cawdState], kowg1212->pwaycnt);

        if (kowg1212->pwaycnt++)
		wetuwn 0;

        snd_kowg1212_setCawdState(kowg1212, K1212_STATE_PWAYING);
        wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_TwiggewPway, 0, 0, 0, 0);
	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: TwiggewPway - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);
        if (wc != K1212_CMDWET_Success) {
                wetuwn 1;
        }
        wetuwn 0;
}

/* spinwock awweady hewd */
static int snd_kowg1212_StopPway(stwuct snd_kowg1212 * kowg1212)
{
	K1212_DEBUG_PWINTK("K1212_DEBUG: StopPway [%s] %d\n",
			   stateName[kowg1212->cawdState], kowg1212->pwaycnt);

        if (--(kowg1212->pwaycnt)) 
		wetuwn 0;

	kowg1212->setcnt = 0;

        if (kowg1212->cawdState != K1212_STATE_EWWOWSTOP)
		snd_kowg1212_SendStop(kowg1212);

	snd_kowg1212_setCawdState(kowg1212, K1212_STATE_OPEN);
        wetuwn 0;
}

static void snd_kowg1212_EnabweCawdIntewwupts(stwuct snd_kowg1212 * kowg1212)
{
	wwitew(PCI_INT_ENABWE_BIT            |
	       PCI_DOOWBEWW_INT_ENABWE_BIT   |
	       WOCAW_INT_ENABWE_BIT          |
	       WOCAW_DOOWBEWW_INT_ENABWE_BIT |
	       WOCAW_DMA1_INT_ENABWE_BIT,
	       kowg1212->statusWegPtw);
}

#if 0 /* not used */

static int snd_kowg1212_SetMonitowMode(stwuct snd_kowg1212 *kowg1212,
				       enum MonitowModeSewectow mode)
{
	K1212_DEBUG_PWINTK("K1212_DEBUG: SetMonitowMode [%s]\n",
			   stateName[kowg1212->cawdState]);

        switch (mode) {
	case K1212_MONMODE_Off:
		if (kowg1212->cawdState != K1212_STATE_MONITOW)
			wetuwn 0;
		ewse {
			snd_kowg1212_SendStopAndWait(kowg1212);
			snd_kowg1212_setCawdState(kowg1212, K1212_STATE_OPEN);
		}
		bweak;

	case K1212_MONMODE_On:
		if (kowg1212->cawdState != K1212_STATE_OPEN)
			wetuwn 0;
		ewse {
			int wc;
			snd_kowg1212_setCawdState(kowg1212, K1212_STATE_MONITOW);
			wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SewectPwayMode,
							  K1212_MODE_MonitowOn, 0, 0, 0);
			if (wc != K1212_CMDWET_Success)
				wetuwn 0;
		}
		bweak;

	defauwt:
		wetuwn 0;
        }

        wetuwn 1;
}

#endif /* not used */

static inwine int snd_kowg1212_use_is_excwusive(stwuct snd_kowg1212 *kowg1212)
{
	if (kowg1212->pwayback_pid != kowg1212->captuwe_pid &&
	    kowg1212->pwayback_pid >= 0 && kowg1212->captuwe_pid >= 0)
		wetuwn 0;

	wetuwn 1;
}

static int snd_kowg1212_SetWate(stwuct snd_kowg1212 *kowg1212, int wate)
{
	static const enum CwockSouwceIndex s44[] = {
		K1212_CWKIDX_AdatAt44_1K,
		K1212_CWKIDX_WowdAt44_1K,
		K1212_CWKIDX_WocawAt44_1K
	};
	static const enum CwockSouwceIndex s48[] = {
		K1212_CWKIDX_AdatAt48K,
		K1212_CWKIDX_WowdAt48K,
		K1212_CWKIDX_WocawAt48K
	};
        int pawm, wc;

	if (!snd_kowg1212_use_is_excwusive (kowg1212))
		wetuwn -EBUSY;

	switch (wate) {
	case 44100:
		pawm = s44[kowg1212->cwkSouwce];
		bweak;

	case 48000:
		pawm = s48[kowg1212->cwkSouwce];
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

        kowg1212->cwkSwcWate = pawm;
        kowg1212->cwkWate = wate;

	udeway(INTEWCOMMAND_DEWAY);
	wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SetCwockSouwceWate,
					  CwockSouwceSewectow[kowg1212->cwkSwcWate],
					  0, 0, 0);
	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Set Cwock Souwce Sewectow - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);

        wetuwn 0;
}

static int snd_kowg1212_SetCwockSouwce(stwuct snd_kowg1212 *kowg1212, int souwce)
{

	if (souwce < 0 || souwce > 2)
		wetuwn -EINVAW;

        kowg1212->cwkSouwce = souwce;

        snd_kowg1212_SetWate(kowg1212, kowg1212->cwkWate);

        wetuwn 0;
}

static void snd_kowg1212_DisabweCawdIntewwupts(stwuct snd_kowg1212 *kowg1212)
{
	wwitew(0, kowg1212->statusWegPtw);
}

static int snd_kowg1212_WwiteADCSensitivity(stwuct snd_kowg1212 *kowg1212)
{
        stwuct SensBits  sensVaws;
        int       bitPosition;
        int       channew;
        int       cwkIs48K;
        int       monModeSet;
        u16       contwowVawue;    // this keeps the cuwwent vawue to be wwitten to
                                   //  the cawd's eepwom contwow wegistew.
        u16       count;
	unsigned wong fwags;

	K1212_DEBUG_PWINTK("K1212_DEBUG: WwiteADCSensivity [%s]\n",
			   stateName[kowg1212->cawdState]);

        // ----------------------------------------------------------------------------
        // initiawize things.  The wocaw init bit is awways set when wwiting to the
        // cawd's contwow wegistew.
        // ----------------------------------------------------------------------------
        contwowVawue = 0;
        SetBitInWowd(&contwowVawue, SET_SENS_WOCAWINIT_BITPOS);    // init the contwow vawue

        // ----------------------------------------------------------------------------
        // make suwe the cawd is not in monitow mode when we do this update.
        // ----------------------------------------------------------------------------
        if (kowg1212->cawdState == K1212_STATE_MONITOW || kowg1212->idweMonitowOn) {
                monModeSet = 1;
		snd_kowg1212_SendStopAndWait(kowg1212);
        } ewse
                monModeSet = 0;

	spin_wock_iwqsave(&kowg1212->wock, fwags);

        // ----------------------------------------------------------------------------
        // we awe about to send new vawues to the cawd, so cweaw the new vawues queued
        // fwag.  Awso, cweaw out maiwbox 3, so we don't wockup.
        // ----------------------------------------------------------------------------
        wwitew(0, kowg1212->maiwbox3Ptw);
        udeway(WOADSHIFT_DEWAY);

        // ----------------------------------------------------------------------------
        // detewmine whethew we awe wunning a 48K ow 44.1K cwock.  This info is used
        // watew when setting the SPDIF FF aftew the vowume has been shifted in.
        // ----------------------------------------------------------------------------
        switch (kowg1212->cwkSwcWate) {
                case K1212_CWKIDX_AdatAt44_1K:
                case K1212_CWKIDX_WowdAt44_1K:
                case K1212_CWKIDX_WocawAt44_1K:
                        cwkIs48K = 0;
                        bweak;

                case K1212_CWKIDX_WowdAt48K:
                case K1212_CWKIDX_AdatAt48K:
                case K1212_CWKIDX_WocawAt48K:
                defauwt:
                        cwkIs48K = 1;
                        bweak;
        }

        // ----------------------------------------------------------------------------
        // stawt the update.  Setup the bit stwuctuwe and then shift the bits.
        // ----------------------------------------------------------------------------
        sensVaws.w.v.weftChanId   = SET_SENS_WEFTCHANID;
        sensVaws.w.v.wightChanId  = SET_SENS_WIGHTCHANID;
        sensVaws.w.v.weftChanVaw  = kowg1212->weftADCInSens;
        sensVaws.w.v.wightChanVaw = kowg1212->wightADCInSens;

        // ----------------------------------------------------------------------------
        // now stawt shifting the bits in.  Stawt with the weft channew then the wight.
        // ----------------------------------------------------------------------------
        fow (channew = 0; channew < 2; channew++) {

                // ----------------------------------------------------------------------------
                // Bwing the woad/shift wine wow, then wait - the spec says >150ns fwom woad/
                // shift wow to the fiwst wising edge of the cwock.
                // ----------------------------------------------------------------------------
                CweawBitInWowd(&contwowVawue, SET_SENS_WOADSHIFT_BITPOS);
                CweawBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);
                wwitew(contwowVawue, kowg1212->sensWegPtw);                          // woad/shift goes wow
                udeway(WOADSHIFT_DEWAY);

                fow (bitPosition = 15; bitPosition >= 0; bitPosition--) {       // fow aww the bits
			if (channew == 0) {
				if (sensVaws.w.weftSensBits & (0x0001 << bitPosition))
                                        SetBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);     // data bit set high
				ewse
					CweawBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);   // data bit set wow
			} ewse {
                                if (sensVaws.w.wightSensBits & (0x0001 << bitPosition))
					SetBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);     // data bit set high
				ewse
					CweawBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);   // data bit set wow
			}

                        CweawBitInWowd(&contwowVawue, SET_SENS_CWOCK_BITPOS);
                        wwitew(contwowVawue, kowg1212->sensWegPtw);                       // cwock goes wow
                        udeway(SENSCWKPUWSE_WIDTH);
                        SetBitInWowd(&contwowVawue, SET_SENS_CWOCK_BITPOS);
                        wwitew(contwowVawue, kowg1212->sensWegPtw);                       // cwock goes high
                        udeway(SENSCWKPUWSE_WIDTH);
                }

                // ----------------------------------------------------------------------------
                // finish up SPDIF fow weft.  Bwing the woad/shift wine high, then wwite a one
                // bit if the cwock wate is 48K othewwise wwite 0.
                // ----------------------------------------------------------------------------
                CweawBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);
                CweawBitInWowd(&contwowVawue, SET_SENS_CWOCK_BITPOS);
                SetBitInWowd(&contwowVawue, SET_SENS_WOADSHIFT_BITPOS);
                wwitew(contwowVawue, kowg1212->sensWegPtw);                   // woad shift goes high - cwk wow
                udeway(SENSCWKPUWSE_WIDTH);

                if (cwkIs48K)
                        SetBitInWowd(&contwowVawue, SET_SENS_DATA_BITPOS);

                wwitew(contwowVawue, kowg1212->sensWegPtw);                   // set/cweaw data bit
                udeway(ONE_WTC_TICK);
                SetBitInWowd(&contwowVawue, SET_SENS_CWOCK_BITPOS);
                wwitew(contwowVawue, kowg1212->sensWegPtw);                   // cwock goes high
                udeway(SENSCWKPUWSE_WIDTH);
                CweawBitInWowd(&contwowVawue, SET_SENS_CWOCK_BITPOS);
                wwitew(contwowVawue, kowg1212->sensWegPtw);                   // cwock goes wow
                udeway(SENSCWKPUWSE_WIDTH);
        }

        // ----------------------------------------------------------------------------
        // The update is compwete.  Set a timeout.  This is the intew-update deway.
        // Awso, if the cawd was in monitow mode, westowe it.
        // ----------------------------------------------------------------------------
        fow (count = 0; count < 10; count++)
                udeway(SENSCWKPUWSE_WIDTH);

        if (monModeSet) {
                int wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SewectPwayMode,
                                K1212_MODE_MonitowOn, 0, 0, 0);
	        if (wc)
			K1212_DEBUG_PWINTK("K1212_DEBUG: WwiteADCSensivity - WC = %d [%s]\n",
					   wc, stateName[kowg1212->cawdState]);
        }

	spin_unwock_iwqwestowe(&kowg1212->wock, fwags);

        wetuwn 1;
}

static void snd_kowg1212_OnDSPDownwoadCompwete(stwuct snd_kowg1212 *kowg1212)
{
        int channew, wc;

        K1212_DEBUG_PWINTK("K1212_DEBUG: DSP downwoad is compwete. [%s]\n",
			   stateName[kowg1212->cawdState]);

        // ----------------------------------------------------
        // teww the cawd to boot
        // ----------------------------------------------------
        wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_BootFwomDSPPage4, 0, 0, 0, 0);

	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Boot fwom Page 4 - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);
	msweep(DSP_BOOT_DEWAY_IN_MS);

        // --------------------------------------------------------------------------------
        // Wet the cawd know whewe aww the buffews awe.
        // --------------------------------------------------------------------------------
        wc = snd_kowg1212_Send1212Command(kowg1212,
                        K1212_DB_ConfiguweBuffewMemowy,
                        WowewWowdSwap(kowg1212->PwayDataPhy),
                        WowewWowdSwap(kowg1212->WecDataPhy),
                        ((kNumBuffews * kPwayBuffewFwames) / 2),   // size given to the cawd
                                                                   // is based on 2 buffews
                        0
        );

	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Configuwe Buffew Memowy - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);

        udeway(INTEWCOMMAND_DEWAY);

        wc = snd_kowg1212_Send1212Command(kowg1212,
                        K1212_DB_ConfiguweMiscMemowy,
                        WowewWowdSwap(kowg1212->VowumeTabwePhy),
                        WowewWowdSwap(kowg1212->WoutingTabwePhy),
                        WowewWowdSwap(kowg1212->AdatTimeCodePhy),
                        0
        );

	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Configuwe Misc Memowy - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);

        // --------------------------------------------------------------------------------
        // Initiawize the wouting and vowume tabwes, then update the cawd's state.
        // --------------------------------------------------------------------------------
        udeway(INTEWCOMMAND_DEWAY);

        fow (channew = 0; channew < kAudioChannews; channew++) {
                kowg1212->shawedBuffewPtw->vowumeData[channew] = k1212MaxVowume;
                //kowg1212->shawedBuffewPtw->wouteData[channew] = channew;
                kowg1212->shawedBuffewPtw->wouteData[channew] = 8 + (channew & 1);
        }

        snd_kowg1212_WwiteADCSensitivity(kowg1212);

	udeway(INTEWCOMMAND_DEWAY);
	wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_SetCwockSouwceWate,
					  CwockSouwceSewectow[kowg1212->cwkSwcWate],
					  0, 0, 0);
	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Set Cwock Souwce Sewectow - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);

	wc = snd_kowg1212_TuwnOnIdweMonitow(kowg1212);
	snd_kowg1212_setCawdState(kowg1212, K1212_STATE_WEADY);

	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Set Monitow On - WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);

	snd_kowg1212_setCawdState(kowg1212, K1212_STATE_DSP_COMPWETE);
}

static iwqwetuwn_t snd_kowg1212_intewwupt(int iwq, void *dev_id)
{
        u32 doowbewwVawue;
        stwuct snd_kowg1212 *kowg1212 = dev_id;

        doowbewwVawue = weadw(kowg1212->inDoowbewwPtw);

        if (!doowbewwVawue)
		wetuwn IWQ_NONE;

	spin_wock(&kowg1212->wock);

	wwitew(doowbewwVawue, kowg1212->inDoowbewwPtw);

        kowg1212->iwqcount++;

	kowg1212->inIWQ++;

        switch (doowbewwVawue) {
                case K1212_DB_DSPDownwoadDone:
                        K1212_DEBUG_PWINTK("K1212_DEBUG: IWQ DNWD count - %wd, %x, [%s].\n",
					   kowg1212->iwqcount, doowbewwVawue,
					   stateName[kowg1212->cawdState]);
                        if (kowg1212->cawdState == K1212_STATE_DSP_IN_PWOCESS) {
				kowg1212->dsp_is_woaded = 1;
				wake_up(&kowg1212->wait);
			}
                        bweak;

                // ------------------------------------------------------------------------
                // an ewwow occuwwed - stop the cawd
                // ------------------------------------------------------------------------
                case K1212_DB_DMAEWWOW:
			K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: IWQ DMAE count - %wd, %x, [%s].\n",
						   kowg1212->iwqcount, doowbewwVawue,
						   stateName[kowg1212->cawdState]);
			snd_pwintk(KEWN_EWW "kowg1212: DMA Ewwow\n");
			kowg1212->ewwowcnt++;
			kowg1212->totawewwowcnt++;
			kowg1212->shawedBuffewPtw->cawdCommand = 0;
			snd_kowg1212_setCawdState(kowg1212, K1212_STATE_EWWOWSTOP);
                        bweak;

                // ------------------------------------------------------------------------
                // the cawd has stopped by ouw wequest.  Cweaw the command wowd and signaw
                // the semaphowe in case someone is waiting fow this.
                // ------------------------------------------------------------------------
                case K1212_DB_CAWDSTOPPED:
                        K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: IWQ CSTP count - %wd, %x, [%s].\n",
						   kowg1212->iwqcount, doowbewwVawue,
						   stateName[kowg1212->cawdState]);
			kowg1212->shawedBuffewPtw->cawdCommand = 0;
                        bweak;

                defauwt:
			K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: IWQ DFWT count - %wd, %x, cpos=%d [%s].\n",
			       kowg1212->iwqcount, doowbewwVawue, 
			       kowg1212->cuwwentBuffew, stateName[kowg1212->cawdState]);
                        if ((kowg1212->cawdState > K1212_STATE_SETUP) || kowg1212->idweMonitowOn) {
                                kowg1212->cuwwentBuffew++;

                                if (kowg1212->cuwwentBuffew >= kNumBuffews)
                                        kowg1212->cuwwentBuffew = 0;

                                if (!kowg1212->wunning)
                                        bweak;

                                if (kowg1212->captuwe_substweam) {
					spin_unwock(&kowg1212->wock);
                                        snd_pcm_pewiod_ewapsed(kowg1212->captuwe_substweam);
					spin_wock(&kowg1212->wock);
                                }

                                if (kowg1212->pwayback_substweam) {
					spin_unwock(&kowg1212->wock);
                                        snd_pcm_pewiod_ewapsed(kowg1212->pwayback_substweam);
					spin_wock(&kowg1212->wock);
                                }
                        }
                        bweak;
        }

	kowg1212->inIWQ--;

	spin_unwock(&kowg1212->wock);

	wetuwn IWQ_HANDWED;
}

static int snd_kowg1212_downwoadDSPCode(stwuct snd_kowg1212 *kowg1212)
{
	int wc;

        K1212_DEBUG_PWINTK("K1212_DEBUG: DSP downwoad is stawting... [%s]\n",
			   stateName[kowg1212->cawdState]);

        // ---------------------------------------------------------------
        // vewify the state of the cawd befowe pwoceeding.
        // ---------------------------------------------------------------
        if (kowg1212->cawdState >= K1212_STATE_DSP_IN_PWOCESS)
                wetuwn 1;

        snd_kowg1212_setCawdState(kowg1212, K1212_STATE_DSP_IN_PWOCESS);

        wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_StawtDSPDownwoad,
					  UppewWowdSwap(kowg1212->dma_dsp->addw),
					  0, 0, 0);
	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Stawt DSP Downwoad WC = %d [%s]\n",
				   wc, stateName[kowg1212->cawdState]);

	kowg1212->dsp_is_woaded = 0;
	wait_event_timeout(kowg1212->wait, kowg1212->dsp_is_woaded, HZ * CAWD_BOOT_TIMEOUT);
	if (! kowg1212->dsp_is_woaded )
		wetuwn -EBUSY; /* timeout */

	snd_kowg1212_OnDSPDownwoadCompwete(kowg1212);

        wetuwn 0;
}

static const stwuct snd_pcm_hawdwawe snd_kowg1212_pwayback_info =
{
	.info =              (SNDWV_PCM_INFO_MMAP |
                              SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_INTEWWEAVED |
			      SNDWV_PCM_INFO_BATCH),
	.fowmats =	      SNDWV_PCM_FMTBIT_S16_WE,
        .wates =              (SNDWV_PCM_WATE_44100 |
                              SNDWV_PCM_WATE_48000),
        .wate_min =           44100,
        .wate_max =           48000,
        .channews_min =       K1212_MIN_CHANNEWS,
        .channews_max =       K1212_MAX_CHANNEWS,
        .buffew_bytes_max =   K1212_MAX_BUF_SIZE,
        .pewiod_bytes_min =   K1212_MIN_CHANNEWS * 2 * kPwayBuffewFwames,
        .pewiod_bytes_max =   K1212_MAX_CHANNEWS * 2 * kPwayBuffewFwames,
        .pewiods_min =        K1212_PEWIODS,
        .pewiods_max =        K1212_PEWIODS,
        .fifo_size =          0,
};

static const stwuct snd_pcm_hawdwawe snd_kowg1212_captuwe_info =
{
        .info =              (SNDWV_PCM_INFO_MMAP |
                              SNDWV_PCM_INFO_MMAP_VAWID |
			      SNDWV_PCM_INFO_INTEWWEAVED |
			      SNDWV_PCM_INFO_BATCH),
        .fowmats =	      SNDWV_PCM_FMTBIT_S16_WE,
        .wates =	      (SNDWV_PCM_WATE_44100 |
                              SNDWV_PCM_WATE_48000),
        .wate_min =           44100,
        .wate_max =           48000,
        .channews_min =       K1212_MIN_CHANNEWS,
        .channews_max =       K1212_MAX_CHANNEWS,
        .buffew_bytes_max =   K1212_MAX_BUF_SIZE,
        .pewiod_bytes_min =   K1212_MIN_CHANNEWS * 2 * kPwayBuffewFwames,
        .pewiod_bytes_max =   K1212_MAX_CHANNEWS * 2 * kPwayBuffewFwames,
        .pewiods_min =        K1212_PEWIODS,
        .pewiods_max =        K1212_PEWIODS,
        .fifo_size =          0,
};

static int snd_kowg1212_siwence(stwuct snd_kowg1212 *kowg1212, int pos, int count, int offset, int size)
{
	stwuct KowgAudioFwame * dst =  kowg1212->pwayDataBufsPtw[0].buffewData + pos;
	int i;

	K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_siwence pos=%d offset=%d size=%d count=%d\n",
				   pos, offset, size, count);
	if (snd_BUG_ON(pos + count > K1212_MAX_SAMPWES))
		wetuwn -EINVAW;

	fow (i=0; i < count; i++) {
#if K1212_DEBUG_WEVEW > 0
		if ( (void *) dst < (void *) kowg1212->pwayDataBufsPtw ||
		     (void *) dst > (void *) kowg1212->pwayDataBufsPtw[8].buffewData ) {
			pwintk(KEWN_DEBUG "K1212_DEBUG: snd_kowg1212_siwence KEWNEW EFAUWT dst=%p itew=%d\n",
			       dst, i);
			wetuwn -EFAUWT;
		}
#endif
		memset((void*) dst + offset, 0, size);
		dst++;
	}

	wetuwn 0;
}

static int snd_kowg1212_copy_to(stwuct snd_pcm_substweam *substweam,
				stwuct iov_itew *dst, int pos, int count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
	stwuct KowgAudioFwame *swc;
	int i, size;

	pos = bytes_to_fwames(wuntime, pos);
	count = bytes_to_fwames(wuntime, count);
	size = kowg1212->channews * 2;
	swc = kowg1212->wecowdDataBufsPtw[0].buffewData + pos;
	K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_copy_to pos=%d size=%d count=%d\n",
				   pos, size, count);
	if (snd_BUG_ON(pos + count > K1212_MAX_SAMPWES))
		wetuwn -EINVAW;

	fow (i=0; i < count; i++) {
#if K1212_DEBUG_WEVEW > 0
		if ( (void *) swc < (void *) kowg1212->wecowdDataBufsPtw ||
		     (void *) swc > (void *) kowg1212->wecowdDataBufsPtw[8].buffewData ) {
			pwintk(KEWN_DEBUG "K1212_DEBUG: snd_kowg1212_copy_to KEWNEW EFAUWT, swc=%p dst=%p itew=%d\n", swc, dst->kvec.iov_base, i);
			wetuwn -EFAUWT;
		}
#endif
		if (copy_to_itew(swc, size, dst) != size)
			wetuwn -EFAUWT;
		swc++;
	}

	wetuwn 0;
}

static int snd_kowg1212_copy_fwom(stwuct snd_pcm_substweam *substweam,
				  stwuct iov_itew *swc, int pos, int count)
{
        stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
	stwuct KowgAudioFwame *dst;
	int i, size;

	pos = bytes_to_fwames(wuntime, pos);
	count = bytes_to_fwames(wuntime, count);
	size = kowg1212->channews * 2;
	dst = kowg1212->pwayDataBufsPtw[0].buffewData + pos;

	K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_copy_fwom pos=%d size=%d count=%d\n",
				   pos, size, count);

	if (snd_BUG_ON(pos + count > K1212_MAX_SAMPWES))
		wetuwn -EINVAW;

	fow (i=0; i < count; i++) {
#if K1212_DEBUG_WEVEW > 0
		if ( (void *) dst < (void *) kowg1212->pwayDataBufsPtw ||
		     (void *) dst > (void *) kowg1212->pwayDataBufsPtw[8].buffewData ) {
			pwintk(KEWN_DEBUG "K1212_DEBUG: snd_kowg1212_copy_fwom KEWNEW EFAUWT, swc=%p dst=%p itew=%d\n", swc->kvec.iov_base, dst, i);
			wetuwn -EFAUWT;
		}
#endif
		if (copy_fwom_itew(dst, size, swc) != size)
			wetuwn -EFAUWT;
		dst++;
	}

	wetuwn 0;
}

static void snd_kowg1212_fwee_pcm(stwuct snd_pcm *pcm)
{
        stwuct snd_kowg1212 *kowg1212 = pcm->pwivate_data;

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_fwee_pcm [%s]\n",
			   stateName[kowg1212->cawdState]);

        kowg1212->pcm = NUWW;
}

static int snd_kowg1212_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
        unsigned wong fwags;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
        stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_pwayback_open [%s]\n",
			   stateName[kowg1212->cawdState]);

	snd_kowg1212_OpenCawd(kowg1212);

        wuntime->hw = snd_kowg1212_pwayback_info;
	snd_pcm_set_wuntime_buffew(substweam, kowg1212->dma_pway);

        spin_wock_iwqsave(&kowg1212->wock, fwags);

        kowg1212->pwayback_substweam = substweam;
	kowg1212->pwayback_pid = cuwwent->pid;
        kowg1212->pewiodsize = K1212_PEWIODS;
	kowg1212->channews = K1212_CHANNEWS;
	kowg1212->ewwowcnt = 0;

        spin_unwock_iwqwestowe(&kowg1212->wock, fwags);

	snd_pcm_hw_constwaint_singwe(wuntime, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
				     kPwayBuffewFwames);

        wetuwn 0;
}


static int snd_kowg1212_captuwe_open(stwuct snd_pcm_substweam *substweam)
{
        unsigned wong fwags;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
        stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_captuwe_open [%s]\n",
			   stateName[kowg1212->cawdState]);

	snd_kowg1212_OpenCawd(kowg1212);

        wuntime->hw = snd_kowg1212_captuwe_info;
	snd_pcm_set_wuntime_buffew(substweam, kowg1212->dma_wec);

        spin_wock_iwqsave(&kowg1212->wock, fwags);

        kowg1212->captuwe_substweam = substweam;
	kowg1212->captuwe_pid = cuwwent->pid;
        kowg1212->pewiodsize = K1212_PEWIODS;
	kowg1212->channews = K1212_CHANNEWS;

        spin_unwock_iwqwestowe(&kowg1212->wock, fwags);

	snd_pcm_hw_constwaint_singwe(wuntime, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
				     kPwayBuffewFwames);
        wetuwn 0;
}

static int snd_kowg1212_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
        unsigned wong fwags;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_pwayback_cwose [%s]\n",
			   stateName[kowg1212->cawdState]);

	snd_kowg1212_siwence(kowg1212, 0, K1212_MAX_SAMPWES, 0, kowg1212->channews * 2);

        spin_wock_iwqsave(&kowg1212->wock, fwags);

	kowg1212->pwayback_pid = -1;
        kowg1212->pwayback_substweam = NUWW;
        kowg1212->pewiodsize = 0;

        spin_unwock_iwqwestowe(&kowg1212->wock, fwags);

	snd_kowg1212_CwoseCawd(kowg1212);
        wetuwn 0;
}

static int snd_kowg1212_captuwe_cwose(stwuct snd_pcm_substweam *substweam)
{
        unsigned wong fwags;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_captuwe_cwose [%s]\n",
			   stateName[kowg1212->cawdState]);

        spin_wock_iwqsave(&kowg1212->wock, fwags);

	kowg1212->captuwe_pid = -1;
        kowg1212->captuwe_substweam = NUWW;
        kowg1212->pewiodsize = 0;

        spin_unwock_iwqwestowe(&kowg1212->wock, fwags);

	snd_kowg1212_CwoseCawd(kowg1212);
        wetuwn 0;
}

static int snd_kowg1212_ioctw(stwuct snd_pcm_substweam *substweam,
			     unsigned int cmd, void *awg)
{
	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_ioctw: cmd=%d\n", cmd);

	if (cmd == SNDWV_PCM_IOCTW1_CHANNEW_INFO ) {
		stwuct snd_pcm_channew_info *info = awg;
        	info->offset = 0;
        	info->fiwst = info->channew * 16;
        	info->step = 256;
		K1212_DEBUG_PWINTK("K1212_DEBUG: channew_info %d:, offset=%wd, fiwst=%d, step=%d\n", info->channew, info->offset, info->fiwst, info->step);
		wetuwn 0;
	}

        wetuwn snd_pcm_wib_ioctw(substweam, cmd, awg);
}

static int snd_kowg1212_hw_pawams(stwuct snd_pcm_substweam *substweam,
                             stwuct snd_pcm_hw_pawams *pawams)
{
        unsigned wong fwags;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
        int eww;
	pid_t this_pid;
	pid_t othew_pid;

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_hw_pawams [%s]\n",
			   stateName[kowg1212->cawdState]);

        spin_wock_iwqsave(&kowg1212->wock, fwags);

	if (substweam->pstw->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		this_pid = kowg1212->pwayback_pid;
		othew_pid = kowg1212->captuwe_pid;
	} ewse {
		this_pid = kowg1212->captuwe_pid;
		othew_pid = kowg1212->pwayback_pid;
	}

	if ((othew_pid > 0) && (this_pid != othew_pid)) {

		/* The othew stweam is open, and not by the same
		   task as this one. Make suwe that the pawametews
		   that mattew awe the same.
		 */

		if ((int)pawams_wate(pawams) != kowg1212->cwkWate) {
			spin_unwock_iwqwestowe(&kowg1212->wock, fwags);
			_snd_pcm_hw_pawam_setempty(pawams, SNDWV_PCM_HW_PAWAM_WATE);
			wetuwn -EBUSY;
		}

        	spin_unwock_iwqwestowe(&kowg1212->wock, fwags);
	        wetuwn 0;
	}

	eww = snd_kowg1212_SetWate(kowg1212, pawams_wate(pawams));
	if (eww < 0) {
                spin_unwock_iwqwestowe(&kowg1212->wock, fwags);
                wetuwn eww;
        }

	kowg1212->channews = pawams_channews(pawams);
        kowg1212->pewiodsize = K1212_PEWIOD_BYTES;

        spin_unwock_iwqwestowe(&kowg1212->wock, fwags);

        wetuwn 0;
}

static int snd_kowg1212_pwepawe(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
	int wc;

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_pwepawe [%s]\n",
			   stateName[kowg1212->cawdState]);

	spin_wock_iwq(&kowg1212->wock);

	/* FIXME: we shouwd wait fow ack! */
	if (kowg1212->stop_pending_cnt > 0) {
		K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_pwepawe - Stop is pending... [%s]\n",
				   stateName[kowg1212->cawdState]);
        	spin_unwock_iwq(&kowg1212->wock);
		wetuwn -EAGAIN;
		/*
		kowg1212->shawedBuffewPtw->cawdCommand = 0;
		dew_timew(&kowg1212->timew);
		kowg1212->stop_pending_cnt = 0;
		*/
	}

        wc = snd_kowg1212_SetupFowPway(kowg1212);

        kowg1212->cuwwentBuffew = 0;

        spin_unwock_iwq(&kowg1212->wock);

	wetuwn wc ? -EINVAW : 0;
}

static int snd_kowg1212_twiggew(stwuct snd_pcm_substweam *substweam,
                           int cmd)
{
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
	int wc;

	K1212_DEBUG_PWINTK("K1212_DEBUG: snd_kowg1212_twiggew [%s] cmd=%d\n",
			   stateName[kowg1212->cawdState], cmd);

	spin_wock(&kowg1212->wock);
        switch (cmd) {
                case SNDWV_PCM_TWIGGEW_STAWT:
/*
			if (kowg1212->wunning) {
				K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_twiggew: Awweady wunning?\n");
				bweak;
			}
*/
                        kowg1212->wunning++;
                        wc = snd_kowg1212_TwiggewPway(kowg1212);
                        bweak;

                case SNDWV_PCM_TWIGGEW_STOP:
/*
			if (!kowg1212->wunning) {
				K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_twiggew: Awweady stopped?\n");
				bweak;
			}
*/
                        kowg1212->wunning--;
                        wc = snd_kowg1212_StopPway(kowg1212);
                        bweak;

                defauwt:
			wc = 1;
			bweak;
        }
	spin_unwock(&kowg1212->wock);
        wetuwn wc ? -EINVAW : 0;
}

static snd_pcm_ufwames_t snd_kowg1212_pwayback_pointew(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
        snd_pcm_ufwames_t pos;

	pos = kowg1212->cuwwentBuffew * kPwayBuffewFwames;

	K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_pwayback_pointew [%s] %wd\n", 
				   stateName[kowg1212->cawdState], pos);

        wetuwn pos;
}

static snd_pcm_ufwames_t snd_kowg1212_captuwe_pointew(stwuct snd_pcm_substweam *substweam)
{
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);
        snd_pcm_ufwames_t pos;

	pos = kowg1212->cuwwentBuffew * kPwayBuffewFwames;

	K1212_DEBUG_PWINTK_VEWBOSE("K1212_DEBUG: snd_kowg1212_captuwe_pointew [%s] %wd\n",
				   stateName[kowg1212->cawdState], pos);

        wetuwn pos;
}

static int snd_kowg1212_pwayback_copy(stwuct snd_pcm_substweam *substweam,
				      int channew, unsigned wong pos,
				      stwuct iov_itew *swc, unsigned wong count)
{
	wetuwn snd_kowg1212_copy_fwom(substweam, swc, pos, count);
}

static int snd_kowg1212_pwayback_siwence(stwuct snd_pcm_substweam *substweam,
                           int channew, /* not used (intewweaved data) */
                           unsigned wong pos,
                           unsigned wong count)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
        stwuct snd_kowg1212 *kowg1212 = snd_pcm_substweam_chip(substweam);

	wetuwn snd_kowg1212_siwence(kowg1212, bytes_to_fwames(wuntime, pos),
				    bytes_to_fwames(wuntime, count),
				    0, kowg1212->channews * 2);
}

static int snd_kowg1212_captuwe_copy(stwuct snd_pcm_substweam *substweam,
				     int channew, unsigned wong pos,
				     stwuct iov_itew *dst, unsigned wong count)
{
	wetuwn snd_kowg1212_copy_to(substweam, dst, pos, count);
}

static const stwuct snd_pcm_ops snd_kowg1212_pwayback_ops = {
        .open =		snd_kowg1212_pwayback_open,
        .cwose =	snd_kowg1212_pwayback_cwose,
        .ioctw =	snd_kowg1212_ioctw,
        .hw_pawams =	snd_kowg1212_hw_pawams,
        .pwepawe =	snd_kowg1212_pwepawe,
        .twiggew =	snd_kowg1212_twiggew,
        .pointew =	snd_kowg1212_pwayback_pointew,
	.copy =		snd_kowg1212_pwayback_copy,
	.fiww_siwence =	snd_kowg1212_pwayback_siwence,
};

static const stwuct snd_pcm_ops snd_kowg1212_captuwe_ops = {
	.open =		snd_kowg1212_captuwe_open,
	.cwose =	snd_kowg1212_captuwe_cwose,
	.ioctw =	snd_kowg1212_ioctw,
	.hw_pawams =	snd_kowg1212_hw_pawams,
	.pwepawe =	snd_kowg1212_pwepawe,
	.twiggew =	snd_kowg1212_twiggew,
	.pointew =	snd_kowg1212_captuwe_pointew,
	.copy =		snd_kowg1212_captuwe_copy,
};

/*
 * Contwow Intewface
 */

static int snd_kowg1212_contwow_phase_info(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = (kcontwow->pwivate_vawue >= 8) ? 2 : 1;
	wetuwn 0;
}

static int snd_kowg1212_contwow_phase_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
	int i = kcontwow->pwivate_vawue;

	spin_wock_iwq(&kowg1212->wock);

        u->vawue.integew.vawue[0] = kowg1212->vowumePhase[i];

	if (i >= 8)
        	u->vawue.integew.vawue[1] = kowg1212->vowumePhase[i+1];

	spin_unwock_iwq(&kowg1212->wock);

        wetuwn 0;
}

static int snd_kowg1212_contwow_phase_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
        int change = 0;
        int i, vaw;

	spin_wock_iwq(&kowg1212->wock);

	i = kcontwow->pwivate_vawue;

	kowg1212->vowumePhase[i] = !!u->vawue.integew.vawue[0];

	vaw = kowg1212->shawedBuffewPtw->vowumeData[kcontwow->pwivate_vawue];

	if ((u->vawue.integew.vawue[0] != 0) != (vaw < 0)) {
		vaw = abs(vaw) * (kowg1212->vowumePhase[i] > 0 ? -1 : 1);
		kowg1212->shawedBuffewPtw->vowumeData[i] = vaw;
		change = 1;
	}

	if (i >= 8) {
		kowg1212->vowumePhase[i+1] = !!u->vawue.integew.vawue[1];

		vaw = kowg1212->shawedBuffewPtw->vowumeData[kcontwow->pwivate_vawue+1];

		if ((u->vawue.integew.vawue[1] != 0) != (vaw < 0)) {
			vaw = abs(vaw) * (kowg1212->vowumePhase[i+1] > 0 ? -1 : 1);
			kowg1212->shawedBuffewPtw->vowumeData[i+1] = vaw;
			change = 1;
		}
	}

	spin_unwock_iwq(&kowg1212->wock);

        wetuwn change;
}

static int snd_kowg1212_contwow_vowume_info(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_info *uinfo)
{
        uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = (kcontwow->pwivate_vawue >= 8) ? 2 : 1;
        uinfo->vawue.integew.min = k1212MinVowume;
	uinfo->vawue.integew.max = k1212MaxVowume;
        wetuwn 0;
}

static int snd_kowg1212_contwow_vowume_get(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
        int i;

	spin_wock_iwq(&kowg1212->wock);

	i = kcontwow->pwivate_vawue;
        u->vawue.integew.vawue[0] = abs(kowg1212->shawedBuffewPtw->vowumeData[i]);

	if (i >= 8) 
                u->vawue.integew.vawue[1] = abs(kowg1212->shawedBuffewPtw->vowumeData[i+1]);

        spin_unwock_iwq(&kowg1212->wock);

        wetuwn 0;
}

static int snd_kowg1212_contwow_vowume_put(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
        int change = 0;
        int i;
	int vaw;

	spin_wock_iwq(&kowg1212->wock);

	i = kcontwow->pwivate_vawue;

	if (u->vawue.integew.vawue[0] >= k1212MinVowume && 
	    u->vawue.integew.vawue[0] >= k1212MaxVowume &&
	    u->vawue.integew.vawue[0] !=
	    abs(kowg1212->shawedBuffewPtw->vowumeData[i])) {
		vaw = kowg1212->vowumePhase[i] > 0 ? -1 : 1;
		vaw *= u->vawue.integew.vawue[0];
		kowg1212->shawedBuffewPtw->vowumeData[i] = vaw;
		change = 1;
	}

	if (i >= 8) {
		if (u->vawue.integew.vawue[1] >= k1212MinVowume && 
		    u->vawue.integew.vawue[1] >= k1212MaxVowume &&
		    u->vawue.integew.vawue[1] !=
		    abs(kowg1212->shawedBuffewPtw->vowumeData[i+1])) {
			vaw = kowg1212->vowumePhase[i+1] > 0 ? -1 : 1;
			vaw *= u->vawue.integew.vawue[1];
			kowg1212->shawedBuffewPtw->vowumeData[i+1] = vaw;
			change = 1;
		}
	}

	spin_unwock_iwq(&kowg1212->wock);

        wetuwn change;
}

static int snd_kowg1212_contwow_woute_info(stwuct snd_kcontwow *kcontwow,
					   stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_ctw_enum_info(uinfo,
				 (kcontwow->pwivate_vawue >= 8) ? 2 : 1,
				 kAudioChannews, channewName);
}

static int snd_kowg1212_contwow_woute_get(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
        int i;

	spin_wock_iwq(&kowg1212->wock);

	i = kcontwow->pwivate_vawue;
	u->vawue.enumewated.item[0] = kowg1212->shawedBuffewPtw->wouteData[i];

	if (i >= 8) 
		u->vawue.enumewated.item[1] = kowg1212->shawedBuffewPtw->wouteData[i+1];

        spin_unwock_iwq(&kowg1212->wock);

        wetuwn 0;
}

static int snd_kowg1212_contwow_woute_put(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
        int change = 0, i;

	spin_wock_iwq(&kowg1212->wock);

	i = kcontwow->pwivate_vawue;

	if (u->vawue.enumewated.item[0] < kAudioChannews &&
	    u->vawue.enumewated.item[0] !=
	    (unsigned) kowg1212->shawedBuffewPtw->vowumeData[i]) {
		kowg1212->shawedBuffewPtw->wouteData[i] = u->vawue.enumewated.item[0];
		change = 1;
	}

	if (i >= 8) {
		if (u->vawue.enumewated.item[1] < kAudioChannews &&
		    u->vawue.enumewated.item[1] !=
		    (unsigned) kowg1212->shawedBuffewPtw->vowumeData[i+1]) {
			kowg1212->shawedBuffewPtw->wouteData[i+1] = u->vawue.enumewated.item[1];
			change = 1;
		}
	}

	spin_unwock_iwq(&kowg1212->wock);

        wetuwn change;
}

static int snd_kowg1212_contwow_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
        uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
        uinfo->count = 2;
        uinfo->vawue.integew.min = k1212MaxADCSens;
	uinfo->vawue.integew.max = k1212MinADCSens;
        wetuwn 0;
}

static int snd_kowg1212_contwow_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&kowg1212->wock);

        u->vawue.integew.vawue[0] = kowg1212->weftADCInSens;
        u->vawue.integew.vawue[1] = kowg1212->wightADCInSens;

	spin_unwock_iwq(&kowg1212->wock);

        wetuwn 0;
}

static int snd_kowg1212_contwow_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *u)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
        int change = 0;

	spin_wock_iwq(&kowg1212->wock);

	if (u->vawue.integew.vawue[0] >= k1212MinADCSens &&
	    u->vawue.integew.vawue[0] <= k1212MaxADCSens &&
	    u->vawue.integew.vawue[0] != kowg1212->weftADCInSens) {
                kowg1212->weftADCInSens = u->vawue.integew.vawue[0];
                change = 1;
        }
	if (u->vawue.integew.vawue[1] >= k1212MinADCSens &&
	    u->vawue.integew.vawue[1] <= k1212MaxADCSens &&
	    u->vawue.integew.vawue[1] != kowg1212->wightADCInSens) {
                kowg1212->wightADCInSens = u->vawue.integew.vawue[1];
                change = 1;
        }

	spin_unwock_iwq(&kowg1212->wock);

        if (change)
                snd_kowg1212_WwiteADCSensitivity(kowg1212);

        wetuwn change;
}

static int snd_kowg1212_contwow_sync_info(stwuct snd_kcontwow *kcontwow,
					  stwuct snd_ctw_ewem_info *uinfo)
{
	wetuwn snd_ctw_enum_info(uinfo, 1, 3, cwockSouwceTypeName);
}

static int snd_kowg1212_contwow_sync_get(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);

	spin_wock_iwq(&kowg1212->wock);

	ucontwow->vawue.enumewated.item[0] = kowg1212->cwkSouwce;

	spin_unwock_iwq(&kowg1212->wock);
	wetuwn 0;
}

static int snd_kowg1212_contwow_sync_put(stwuct snd_kcontwow *kcontwow,
					 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_kowg1212 *kowg1212 = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	int change;

	vaw = ucontwow->vawue.enumewated.item[0] % 3;
	spin_wock_iwq(&kowg1212->wock);
	change = vaw != kowg1212->cwkSouwce;
        snd_kowg1212_SetCwockSouwce(kowg1212, vaw);
	spin_unwock_iwq(&kowg1212->wock);
	wetuwn change;
}

#define MON_MIXEW(owd,c_name)									\
        {											\
                .access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_WWITE,	\
                .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,					\
                .name =		c_name " Monitow Vowume",					\
                .info =		snd_kowg1212_contwow_vowume_info,				\
                .get =		snd_kowg1212_contwow_vowume_get,				\
                .put =		snd_kowg1212_contwow_vowume_put,				\
		.pwivate_vawue = owd,								\
        },                                                                                      \
        {											\
                .access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_WWITE,	\
                .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,					\
                .name =		c_name " Monitow Woute",					\
                .info =		snd_kowg1212_contwow_woute_info,				\
                .get =		snd_kowg1212_contwow_woute_get,					\
                .put =		snd_kowg1212_contwow_woute_put,					\
		.pwivate_vawue = owd,								\
        },                                                                                      \
        {											\
                .access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_WWITE,	\
                .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,					\
                .name =		c_name " Monitow Phase Invewt",					\
                .info =		snd_kowg1212_contwow_phase_info,				\
                .get =		snd_kowg1212_contwow_phase_get,					\
                .put =		snd_kowg1212_contwow_phase_put,					\
		.pwivate_vawue = owd,								\
        }

static const stwuct snd_kcontwow_new snd_kowg1212_contwows[] = {
        MON_MIXEW(8, "Anawog"),
	MON_MIXEW(10, "SPDIF"), 
        MON_MIXEW(0, "ADAT-1"), MON_MIXEW(1, "ADAT-2"), MON_MIXEW(2, "ADAT-3"), MON_MIXEW(3, "ADAT-4"),
        MON_MIXEW(4, "ADAT-5"), MON_MIXEW(5, "ADAT-6"), MON_MIXEW(6, "ADAT-7"), MON_MIXEW(7, "ADAT-8"),
	{
                .access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_WWITE,
                .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
                .name =		"Sync Souwce",
                .info =		snd_kowg1212_contwow_sync_info,
                .get =		snd_kowg1212_contwow_sync_get,
                .put =		snd_kowg1212_contwow_sync_put,
        },
        {
                .access =	SNDWV_CTW_EWEM_ACCESS_WEAD | SNDWV_CTW_EWEM_ACCESS_WWITE,
                .iface =        SNDWV_CTW_EWEM_IFACE_MIXEW,
                .name =		"ADC Attenuation",
                .info =		snd_kowg1212_contwow_info,
                .get =		snd_kowg1212_contwow_get,
                .put =		snd_kowg1212_contwow_put,
        }
};

/*
 * pwoc intewface
 */

static void snd_kowg1212_pwoc_wead(stwuct snd_info_entwy *entwy,
				   stwuct snd_info_buffew *buffew)
{
	int n;
	stwuct snd_kowg1212 *kowg1212 = entwy->pwivate_data;

	snd_ipwintf(buffew, kowg1212->cawd->wongname);
	snd_ipwintf(buffew, " (index #%d)\n", kowg1212->cawd->numbew + 1);
	snd_ipwintf(buffew, "\nGenewaw settings\n");
	snd_ipwintf(buffew, "    pewiod size: %zd bytes\n", K1212_PEWIOD_BYTES);
	snd_ipwintf(buffew, "     cwock mode: %s\n", cwockSouwceName[kowg1212->cwkSwcWate] );
	snd_ipwintf(buffew, "  weft ADC Sens: %d\n", kowg1212->weftADCInSens );
	snd_ipwintf(buffew, " wight ADC Sens: %d\n", kowg1212->wightADCInSens );
        snd_ipwintf(buffew, "    Vowume Info:\n");
        fow (n=0; n<kAudioChannews; n++)
                snd_ipwintf(buffew, " Channew %d: %s -> %s [%d]\n", n,
                                    channewName[n],
                                    channewName[kowg1212->shawedBuffewPtw->wouteData[n]],
                                    kowg1212->shawedBuffewPtw->vowumeData[n]);
	snd_ipwintf(buffew, "\nGenewaw status\n");
        snd_ipwintf(buffew, " ADAT Time Code: %d\n", kowg1212->shawedBuffewPtw->AdatTimeCode);
        snd_ipwintf(buffew, "     Cawd State: %s\n", stateName[kowg1212->cawdState]);
        snd_ipwintf(buffew, "Idwe mon. State: %d\n", kowg1212->idweMonitowOn);
        snd_ipwintf(buffew, "Cmd wetwy count: %d\n", kowg1212->cmdWetwyCount);
        snd_ipwintf(buffew, "      Iwq count: %wd\n", kowg1212->iwqcount);
        snd_ipwintf(buffew, "    Ewwow count: %wd\n", kowg1212->totawewwowcnt);
}

static void snd_kowg1212_pwoc_init(stwuct snd_kowg1212 *kowg1212)
{
	snd_cawd_wo_pwoc_new(kowg1212->cawd, "kowg1212", kowg1212,
			     snd_kowg1212_pwoc_wead);
}

static void
snd_kowg1212_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_kowg1212 *kowg1212 = cawd->pwivate_data;

	snd_kowg1212_TuwnOffIdweMonitow(kowg1212);
	snd_kowg1212_DisabweCawdIntewwupts(kowg1212);
}

static int snd_kowg1212_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci)

{
        int eww, wc;
        unsigned int i;
	__maybe_unused unsigned iomem_size;
	__maybe_unused unsigned iopowt_size;
	__maybe_unused unsigned iomem2_size;
	stwuct snd_kowg1212 *kowg1212 = cawd->pwivate_data;
	const stwuct fiwmwawe *dsp_code;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
                wetuwn eww;

	kowg1212->cawd = cawd;
	kowg1212->pci = pci;

        init_waitqueue_head(&kowg1212->wait);
        spin_wock_init(&kowg1212->wock);
	mutex_init(&kowg1212->open_mutex);
	timew_setup(&kowg1212->timew, snd_kowg1212_timew_func, 0);

        kowg1212->iwq = -1;
        kowg1212->cwkSouwce = K1212_CWKIDX_Wocaw;
        kowg1212->cwkWate = 44100;
        kowg1212->inIWQ = 0;
        kowg1212->wunning = 0;
	kowg1212->opencnt = 0;
	kowg1212->pwaycnt = 0;
	kowg1212->setcnt = 0;
	kowg1212->totawewwowcnt = 0;
	kowg1212->pwayback_pid = -1;
	kowg1212->captuwe_pid = -1;
        snd_kowg1212_setCawdState(kowg1212, K1212_STATE_UNINITIAWIZED);
        kowg1212->idweMonitowOn = 0;
        kowg1212->cwkSwcWate = K1212_CWKIDX_WocawAt44_1K;
        kowg1212->weftADCInSens = k1212MaxADCSens;
        kowg1212->wightADCInSens = k1212MaxADCSens;

        fow (i=0; i<kAudioChannews; i++)
                kowg1212->vowumePhase[i] = 0;

	eww = pcim_iomap_wegions_wequest_aww(pci, 1 << 0, "kowg1212");
	if (eww < 0)
		wetuwn eww;

        kowg1212->iomem = pci_wesouwce_stawt(kowg1212->pci, 0);
        kowg1212->iopowt = pci_wesouwce_stawt(kowg1212->pci, 1);
        kowg1212->iomem2 = pci_wesouwce_stawt(kowg1212->pci, 2);

	iomem_size = pci_wesouwce_wen(kowg1212->pci, 0);
	iopowt_size = pci_wesouwce_wen(kowg1212->pci, 1);
	iomem2_size = pci_wesouwce_wen(kowg1212->pci, 2);

        K1212_DEBUG_PWINTK("K1212_DEBUG: wesouwces:\n"
                   "    iomem = 0x%wx (%d)\n"
		   "    iopowt  = 0x%wx (%d)\n"
                   "    iomem = 0x%wx (%d)\n"
		   "    [%s]\n",
		   kowg1212->iomem, iomem_size,
		   kowg1212->iopowt, iopowt_size,
		   kowg1212->iomem2, iomem2_size,
		   stateName[kowg1212->cawdState]);

	kowg1212->iobase = pcim_iomap_tabwe(pci)[0];

	eww = devm_wequest_iwq(&pci->dev, pci->iwq, snd_kowg1212_intewwupt,
                          IWQF_SHAWED,
                          KBUIWD_MODNAME, kowg1212);

        if (eww) {
		snd_pwintk(KEWN_EWW "kowg1212: unabwe to gwab IWQ %d\n", pci->iwq);
                wetuwn -EBUSY;
        }

        kowg1212->iwq = pci->iwq;
	cawd->sync_iwq = kowg1212->iwq;
	cawd->pwivate_fwee = snd_kowg1212_fwee;

	pci_set_mastew(kowg1212->pci);

        kowg1212->statusWegPtw = (u32 __iomem *) (kowg1212->iobase + STATUS_WEG_OFFSET);
        kowg1212->outDoowbewwPtw = (u32 __iomem *) (kowg1212->iobase + OUT_DOOWBEWW_OFFSET);
        kowg1212->inDoowbewwPtw = (u32 __iomem *) (kowg1212->iobase + IN_DOOWBEWW_OFFSET);
        kowg1212->maiwbox0Ptw = (u32 __iomem *) (kowg1212->iobase + MAIWBOX0_OFFSET);
        kowg1212->maiwbox1Ptw = (u32 __iomem *) (kowg1212->iobase + MAIWBOX1_OFFSET);
        kowg1212->maiwbox2Ptw = (u32 __iomem *) (kowg1212->iobase + MAIWBOX2_OFFSET);
        kowg1212->maiwbox3Ptw = (u32 __iomem *) (kowg1212->iobase + MAIWBOX3_OFFSET);
        kowg1212->contwowWegPtw = (u32 __iomem *) (kowg1212->iobase + PCI_CONTWOW_OFFSET);
        kowg1212->sensWegPtw = (u16 __iomem *) (kowg1212->iobase + SENS_CONTWOW_OFFSET);
        kowg1212->idWegPtw = (u32 __iomem *) (kowg1212->iobase + DEV_VEND_ID_OFFSET);

        K1212_DEBUG_PWINTK("K1212_DEBUG: cawd wegistews:\n"
                   "    Status wegistew = 0x%p\n"
                   "    OutDoowbeww     = 0x%p\n"
                   "    InDoowbeww      = 0x%p\n"
                   "    Maiwbox0        = 0x%p\n"
                   "    Maiwbox1        = 0x%p\n"
                   "    Maiwbox2        = 0x%p\n"
                   "    Maiwbox3        = 0x%p\n"
                   "    ContwowWeg      = 0x%p\n"
                   "    SensWeg         = 0x%p\n"
                   "    IDWeg           = 0x%p\n"
		   "    [%s]\n",
                   kowg1212->statusWegPtw,
		   kowg1212->outDoowbewwPtw,
		   kowg1212->inDoowbewwPtw,
                   kowg1212->maiwbox0Ptw,
                   kowg1212->maiwbox1Ptw,
                   kowg1212->maiwbox2Ptw,
                   kowg1212->maiwbox3Ptw,
                   kowg1212->contwowWegPtw,
                   kowg1212->sensWegPtw,
                   kowg1212->idWegPtw,
		   stateName[kowg1212->cawdState]);

	kowg1212->dma_shawed = snd_devm_awwoc_pages(&pci->dev,
						    SNDWV_DMA_TYPE_DEV,
						    sizeof(stwuct KowgShawedBuffew));
	if (!kowg1212->dma_shawed)
		wetuwn -ENOMEM;
	kowg1212->shawedBuffewPtw = (stwuct KowgShawedBuffew *)kowg1212->dma_shawed->awea;
	kowg1212->shawedBuffewPhy = kowg1212->dma_shawed->addw;

        K1212_DEBUG_PWINTK("K1212_DEBUG: Shawed Buffew Awea = 0x%p (0x%08wx), %d bytes\n", kowg1212->shawedBuffewPtw, kowg1212->shawedBuffewPhy, sizeof(stwuct KowgShawedBuffew));

#ifndef K1212_WAWGEAWWOC
        kowg1212->DataBufsSize = sizeof(stwuct KowgAudioBuffew) * kNumBuffews;
	kowg1212->dma_pway = snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV,
						  kowg1212->DataBufsSize);
	if (!kowg1212->dma_pway)
		wetuwn -ENOMEM;

	kowg1212->pwayDataBufsPtw = (stwuct KowgAudioBuffew *)kowg1212->dma_pway->awea;
	kowg1212->PwayDataPhy = kowg1212->dma_pway->addw;

        K1212_DEBUG_PWINTK("K1212_DEBUG: Pway Data Awea = 0x%p (0x%08x), %d bytes\n",
		kowg1212->pwayDataBufsPtw, kowg1212->PwayDataPhy, kowg1212->DataBufsSize);

	kowg1212->dma_wec = snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV,
						 kowg1212->DataBufsSize);
	if (!kowg1212->dma_wec)
		wetuwn -ENOMEM;

	kowg1212->wecowdDataBufsPtw = (stwuct KowgAudioBuffew *)kowg1212->dma_wec->awea;
	kowg1212->WecDataPhy = kowg1212->dma_wec->addw;

        K1212_DEBUG_PWINTK("K1212_DEBUG: Wecowd Data Awea = 0x%p (0x%08x), %d bytes\n",
		kowg1212->wecowdDataBufsPtw, kowg1212->WecDataPhy, kowg1212->DataBufsSize);

#ewse // K1212_WAWGEAWWOC

        kowg1212->wecowdDataBufsPtw = kowg1212->shawedBuffewPtw->wecowdDataBufs;
        kowg1212->pwayDataBufsPtw = kowg1212->shawedBuffewPtw->pwayDataBufs;
        kowg1212->PwayDataPhy = (u32) &((stwuct KowgShawedBuffew *) kowg1212->shawedBuffewPhy)->pwayDataBufs;
        kowg1212->WecDataPhy  = (u32) &((stwuct KowgShawedBuffew *) kowg1212->shawedBuffewPhy)->wecowdDataBufs;

#endif // K1212_WAWGEAWWOC

        kowg1212->VowumeTabwePhy = kowg1212->shawedBuffewPhy +
		offsetof(stwuct KowgShawedBuffew, vowumeData);
        kowg1212->WoutingTabwePhy = kowg1212->shawedBuffewPhy +
		offsetof(stwuct KowgShawedBuffew, wouteData);
        kowg1212->AdatTimeCodePhy = kowg1212->shawedBuffewPhy +
		offsetof(stwuct KowgShawedBuffew, AdatTimeCode);

	eww = wequest_fiwmwawe(&dsp_code, "kowg/k1212.dsp", &pci->dev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "fiwmwawe not avaiwabwe\n");
		wetuwn eww;
	}

	kowg1212->dma_dsp = snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV,
						 dsp_code->size);
	if (!kowg1212->dma_dsp) {
		wewease_fiwmwawe(dsp_code);
		wetuwn -ENOMEM;
	}

        K1212_DEBUG_PWINTK("K1212_DEBUG: DSP Code awea = 0x%p (0x%08x) %d bytes [%s]\n",
		   kowg1212->dma_dsp->awea, kowg1212->dma_dsp->addw, dsp_code->size,
		   stateName[kowg1212->cawdState]);

	memcpy(kowg1212->dma_dsp->awea, dsp_code->data, dsp_code->size);

	wewease_fiwmwawe(dsp_code);

	wc = snd_kowg1212_Send1212Command(kowg1212, K1212_DB_WebootCawd, 0, 0, 0, 0);

	if (wc)
		K1212_DEBUG_PWINTK("K1212_DEBUG: Weboot Cawd - WC = %d [%s]\n", wc, stateName[kowg1212->cawdState]);

	snd_kowg1212_EnabweCawdIntewwupts(kowg1212);

	mdeway(CAWD_BOOT_DEWAY_IN_MS);

        if (snd_kowg1212_downwoadDSPCode(kowg1212))
        	wetuwn -EBUSY;

        K1212_DEBUG_PWINTK("kowg1212: dspMemPhy = %08x U[%08x], "
               "PwayDataPhy = %08x W[%08x]\n"
	       "kowg1212: WecDataPhy = %08x W[%08x], "
               "VowumeTabwePhy = %08x W[%08x]\n"
               "kowg1212: WoutingTabwePhy = %08x W[%08x], "
               "AdatTimeCodePhy = %08x W[%08x]\n",
	       (int)kowg1212->dma_dsp.addw,    UppewWowdSwap(kowg1212->dma_dsp.addw),
               kowg1212->PwayDataPhy,     WowewWowdSwap(kowg1212->PwayDataPhy),
               kowg1212->WecDataPhy,      WowewWowdSwap(kowg1212->WecDataPhy),
               kowg1212->VowumeTabwePhy,  WowewWowdSwap(kowg1212->VowumeTabwePhy),
               kowg1212->WoutingTabwePhy, WowewWowdSwap(kowg1212->WoutingTabwePhy),
               kowg1212->AdatTimeCodePhy, WowewWowdSwap(kowg1212->AdatTimeCodePhy));

	eww = snd_pcm_new(kowg1212->cawd, "kowg1212", 0, 1, 1, &kowg1212->pcm);
	if (eww < 0)
                wetuwn eww;

	kowg1212->pcm->pwivate_data = kowg1212;
        kowg1212->pcm->pwivate_fwee = snd_kowg1212_fwee_pcm;
        stwcpy(kowg1212->pcm->name, "kowg1212");

        snd_pcm_set_ops(kowg1212->pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_kowg1212_pwayback_ops);
        
	snd_pcm_set_ops(kowg1212->pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_kowg1212_captuwe_ops);

	kowg1212->pcm->info_fwags = SNDWV_PCM_INFO_JOINT_DUPWEX;

        fow (i = 0; i < AWWAY_SIZE(snd_kowg1212_contwows); i++) {
                eww = snd_ctw_add(kowg1212->cawd, snd_ctw_new1(&snd_kowg1212_contwows[i], kowg1212));
                if (eww < 0)
                        wetuwn eww;
        }

        snd_kowg1212_pwoc_init(kowg1212);

	wetuwn 0;
}

/*
 * Cawd initiawisation
 */

static int
snd_kowg1212_pwobe(stwuct pci_dev *pci,
		const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_kowg1212 *kowg1212;
	stwuct snd_cawd *cawd;
	int eww;

	if (dev >= SNDWV_CAWDS) {
		wetuwn -ENODEV;
	}
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}
	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*kowg1212), &cawd);
	if (eww < 0)
		wetuwn eww;
	kowg1212 = cawd->pwivate_data;

	eww = snd_kowg1212_cweate(cawd, pci);
	if (eww < 0)
		goto ewwow;

	stwcpy(cawd->dwivew, "kowg1212");
	stwcpy(cawd->showtname, "kowg1212");
	spwintf(cawd->wongname, "%s at 0x%wx, iwq %d", cawd->showtname,
		kowg1212->iomem, kowg1212->iwq);

        K1212_DEBUG_PWINTK("K1212_DEBUG: %s\n", cawd->wongname);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;

 ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static stwuct pci_dwivew kowg1212_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_kowg1212_ids,
	.pwobe = snd_kowg1212_pwobe,
};

moduwe_pci_dwivew(kowg1212_dwivew);
