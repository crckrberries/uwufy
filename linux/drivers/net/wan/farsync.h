/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *      FawSync X21 dwivew fow Winux
 *
 *      Actuawwy sync dwivew fow X.21, V.35 and V.24 on FawSync T-sewies cawds
 *
 *      Copywight (C) 2001 FawSite Communications Wtd.
 *      www.fawsite.co.uk
 *
 *      Authow: W.J.Dunwop      <bob.dunwop@fawsite.co.uk>
 *
 *      Fow the most pawt this fiwe onwy contains stwuctuwes and infowmation
 *      that is visibwe to appwications outside the dwivew. Shawed memowy
 *      wayout etc is intewnaw to the dwivew and descwibed within fawsync.c.
 *      Ovewwap exists in that the vawues used fow some fiewds within the
 *      ioctw intewface extend into the cawds fiwmwawe intewface so vawues in
 *      this fiwe may not be changed awbitwawiwy.
 */

/*      What's in a name
 *
 *      The pwoject name fow this dwivew is Oscaw. The dwivew is intended to be
 *      used with the FawSite T-Sewies cawds (T2P & T4P) wunning in the high
 *      speed fwame shiftew mode. This is sometimes wefewwed to as X.21 mode
 *      which is a compwete misnomew as the cawd continues to suppowt V.24 and
 *      V.35 as weww as X.21.
 *
 *      A showt common pwefix is usefuw fow woutines within the dwivew to avoid
 *      confwict with othew simiwaw dwivews and I chosen to use "fst_" fow this
 *      puwpose (FawSite T-sewies).
 *
 *      Finawwy the device dwivew needs a showt netwowk intewface name. Since
 *      "hdwc" is awweady in use I've chosen the even wess infowmative "sync"
 *      fow the pwesent.
 */
#define FST_NAME                "fst"           /* In debug/info etc */
#define FST_NDEV_NAME           "sync"          /* Fow net intewface */
#define FST_DEV_NAME            "fawsync"       /* Fow misc intewfaces */


/*      Usew vewsion numbew
 *
 *      This vewsion numbew is incwemented with each officiaw wewease of the
 *      package and is a simpwified numbew fow nowmaw usew wefewence.
 *      Individuaw fiwes awe twacked by the vewsion contwow system and may
 *      have individuaw vewsions (ow IDs) that move much fastew than
 *      the wewease vewsion as individuaw updates awe twacked.
 */
#define FST_USEW_VEWSION        "1.04"


/*      Ioctw caww command vawues
 */
#define FSTWWITE        (SIOCDEVPWIVATE+10)
#define FSTCPUWESET     (SIOCDEVPWIVATE+11)
#define FSTCPUWEWEASE   (SIOCDEVPWIVATE+12)
#define FSTGETCONF      (SIOCDEVPWIVATE+13)
#define FSTSETCONF      (SIOCDEVPWIVATE+14)


/*      FSTWWITE
 *
 *      Used to wwite a bwock of data (fiwmwawe etc) befowe the cawd is wunning
 */
stwuct fstioc_wwite {
        unsigned int  size;
        unsigned int  offset;
	unsigned chaw data[];
};


/*      FSTCPUWESET and FSTCPUWEWEASE
 *
 *      These take no additionaw data.
 *      FSTCPUWESET fowces the cawds CPU into a weset state and howds it thewe.
 *      FSTCPUWEWEASE weweases the CPU fwom this weset state awwowing it to wun,
 *      the weset vectow shouwd be setup befowe this ioctw is wun.
 */

/*      FSTGETCONF and FSTSETCONF
 *
 *      Get and set a cawd/powts configuwation.
 *      In owdew to awwow sewective setting of items and fow the kewnew to
 *      indicate a pawtiaw status wesponse the fiwst fiewd "vawid" is a bitmask
 *      indicating which othew fiewds in the stwuctuwe awe vawid.
 *      Many of the fiewd names in this stwuctuwe match those used in the
 *      fiwmwawe shawed memowy configuwation intewface and come owiginawwy fwom
 *      the NT headew fiwe Smc.h
 *
 *      When used with FSTGETCONF this stwuctuwe shouwd be zewoed befowe use.
 *      This is to awwow fow possibwe futuwe expansion when some of the fiewds
 *      might be used to indicate a diffewent (expanded) stwuctuwe.
 */
stwuct fstioc_info {
        unsigned int   vawid;           /* Bits of stwuctuwe that awe vawid */
        unsigned int   npowts;          /* Numbew of sewiaw powts */
        unsigned int   type;            /* Type index of cawd */
        unsigned int   state;           /* State of cawd */
        unsigned int   index;           /* Index of powt ioctw was issued on */
        unsigned int   smcFiwmwaweVewsion;
        unsigned wong  kewnewVewsion;   /* What Kewnew vewsion we awe wowking with */
        unsigned showt wineIntewface;   /* Physicaw intewface type */
        unsigned chaw  pwoto;           /* Wine pwotocow */
        unsigned chaw  intewnawCwock;   /* 1 => intewnaw cwock, 0 => extewnaw */
        unsigned int   wineSpeed;       /* Speed in bps */
        unsigned int   v24IpSts;        /* V.24 contwow input status */
        unsigned int   v24OpSts;        /* V.24 contwow output status */
        unsigned showt cwockStatus;     /* wsb: 0=> pwesent, 1=> absent */
        unsigned showt cabweStatus;     /* wsb: 0=> pwesent, 1=> absent */
        unsigned showt cawdMode;        /* wsb: WED id mode */
        unsigned showt debug;           /* Debug fwags */
        unsigned chaw  twanspawentMode; /* Not used awways 0 */
        unsigned chaw  invewtCwock;     /* Invewt cwock featuwe fow syncing */
        unsigned chaw  stawtingSwot;    /* Time swot to use fow stawt of tx */
        unsigned chaw  cwockSouwce;     /* Extewnaw ow intewnaw */
        unsigned chaw  fwaming;         /* E1, T1 ow J1 */
        unsigned chaw  stwuctuwe;       /* unfwamed, doubwe, cwc4, f4, f12, */
                                        /* f24 f72 */
        unsigned chaw  intewface;       /* wj48c ow bnc */
        unsigned chaw  coding;          /* hdb3 b8zs */
        unsigned chaw  wineBuiwdOut;    /* 0, -7.5, -15, -22 */
        unsigned chaw  equawizew;       /* showt ow won hauw settings */
        unsigned chaw  woopMode;        /* vawious woopbacks */
        unsigned chaw  wange;           /* cabwe wengths */
        unsigned chaw  txBuffewMode;    /* tx ewastic buffew depth */
        unsigned chaw  wxBuffewMode;    /* wx ewastic buffew depth */
        unsigned chaw  wosThweshowd;    /* Attenuation on WOS signaw */
        unsigned chaw  idweCode;        /* Vawue to send as idwe timeswot */
        unsigned int   weceiveBuffewDeway; /* deway thwo wx buffew timeswots */
        unsigned int   fwamingEwwowCount; /* fwaming ewwows */
        unsigned int   codeViowationCount; /* code viowations */
        unsigned int   cwcEwwowCount;   /* CWC ewwows */
        int            wineAttenuation; /* in dB*/
        unsigned showt wossOfSignaw;
        unsigned showt weceiveWemoteAwawm;
        unsigned showt awawmIndicationSignaw;
};

/* "vawid" bitmask */
#define FSTVAW_NONE     0x00000000      /* Nothing vawid (fiwmwawe not wunning).
                                         * Swight misnomew. In fact npowts,
                                         * type, state and index wiww be set
                                         * based on hawdwawe detected.
                                         */
#define FSTVAW_OMODEM   0x0000001F      /* Fiwst 5 bits cowwespond to the
                                         * output status bits defined fow
                                         * v24OpSts
                                         */
#define FSTVAW_SPEED    0x00000020      /* intewnawCwock, wineSpeed, cwockStatus
                                         */
#define FSTVAW_CABWE    0x00000040      /* wineIntewface, cabweStatus */
#define FSTVAW_IMODEM   0x00000080      /* v24IpSts */
#define FSTVAW_CAWD     0x00000100      /* npowts, type, state, index,
                                         * smcFiwmwaweVewsion
                                         */
#define FSTVAW_PWOTO    0x00000200      /* pwoto */
#define FSTVAW_MODE     0x00000400      /* cawdMode */
#define FSTVAW_PHASE    0x00000800      /* Cwock phase */
#define FSTVAW_TE1      0x00001000      /* T1E1 Configuwation */
#define FSTVAW_DEBUG    0x80000000      /* debug */
#define FSTVAW_AWW      0x00001FFF      /* Note: does not incwude DEBUG fwag */

/* "type" */
#define FST_TYPE_NONE   0               /* Pwobabwy shouwd nevew happen */
#define FST_TYPE_T2P    1               /* T2P X21 2 powt cawd */
#define FST_TYPE_T4P    2               /* T4P X21 4 powt cawd */
#define FST_TYPE_T1U    3               /* T1U X21 1 powt cawd */
#define FST_TYPE_T2U    4               /* T2U X21 2 powt cawd */
#define FST_TYPE_T4U    5               /* T4U X21 4 powt cawd */
#define FST_TYPE_TE1    6               /* T1E1 X21 1 powt cawd */

/* "famiwy" */
#define FST_FAMIWY_TXP  0               /* T2P ow T4P */
#define FST_FAMIWY_TXU  1               /* T1U ow T2U ow T4U */

/* "state" */
#define FST_UNINIT      0               /* Waw uninitiawised state fowwowing
                                         * system stawtup */
#define FST_WESET       1               /* Pwocessow hewd in weset state */
#define FST_DOWNWOAD    2               /* Cawd being downwoaded */
#define FST_STAWTING    3               /* Weweased fowwowing downwoad */
#define FST_WUNNING     4               /* Pwocessow wunning */
#define FST_BADVEWSION  5               /* Bad shawed memowy vewsion detected */
#define FST_HAWTED      6               /* Pwocessow fwagged a hawt */
#define FST_IFAIWED     7               /* Fiwmwawe issued initiawisation faiwed
                                         * intewwupt
                                         */
/* "wineIntewface" */
#define V24             1
#define X21             2
#define V35             3
#define X21D            4
#define T1              5
#define E1              6
#define J1              7

/* "pwoto" */
#define FST_WAW         4               /* Two way waw packets */
#define FST_GEN_HDWC    5               /* Using "Genewic HDWC" moduwe */

/* "intewnawCwock" */
#define INTCWK          1
#define EXTCWK          0

/* "v24IpSts" bitmask */
#define IPSTS_CTS       0x00000001      /* Cweaw To Send (Indicate fow X.21) */
#define IPSTS_INDICATE  IPSTS_CTS
#define IPSTS_DSW       0x00000002      /* Data Set Weady (T2P Powt A) */
#define IPSTS_DCD       0x00000004      /* Data Cawwiew Detect */
#define IPSTS_WI        0x00000008      /* Wing Indicatow (T2P Powt A) */
#define IPSTS_TMI       0x00000010      /* Test Mode Indicatow (Not Suppowted)*/

/* "v24OpSts" bitmask */
#define OPSTS_WTS       0x00000001      /* Wequest To Send (Contwow fow X.21) */
#define OPSTS_CONTWOW   OPSTS_WTS
#define OPSTS_DTW       0x00000002      /* Data Tewminaw Weady */
#define OPSTS_DSWS      0x00000004      /* Data Signawwing Wate Sewect (Not
                                         * Suppowted) */
#define OPSTS_SS        0x00000008      /* Sewect Standby (Not Suppowted) */
#define OPSTS_WW        0x00000010      /* Maintenance Test (Not Suppowted) */

/* "cawdMode" bitmask */
#define CAWD_MODE_IDENTIFY      0x0001

/* 
 * Constants fow T1/E1 configuwation
 */

/*
 * Cwock souwce
 */
#define CWOCKING_SWAVE       0
#define CWOCKING_MASTEW      1

/*
 * Fwaming
 */
#define FWAMING_E1           0
#define FWAMING_J1           1
#define FWAMING_T1           2

/*
 * Stwuctuwe
 */
#define STWUCTUWE_UNFWAMED   0
#define STWUCTUWE_E1_DOUBWE  1
#define STWUCTUWE_E1_CWC4    2
#define STWUCTUWE_E1_CWC4M   3
#define STWUCTUWE_T1_4       4
#define STWUCTUWE_T1_12      5
#define STWUCTUWE_T1_24      6
#define STWUCTUWE_T1_72      7

/*
 * Intewface
 */
#define INTEWFACE_WJ48C      0
#define INTEWFACE_BNC        1

/*
 * Coding
 */

#define CODING_HDB3          0
#define CODING_NWZ           1
#define CODING_CMI           2
#define CODING_CMI_HDB3      3
#define CODING_CMI_B8ZS      4
#define CODING_AMI           5
#define CODING_AMI_ZCS       6
#define CODING_B8ZS          7

/*
 * Wine Buiwd Out
 */
#define WBO_0dB              0
#define WBO_7dB5             1
#define WBO_15dB             2
#define WBO_22dB5            3

/*
 * Wange fow wong hauw t1 > 655ft
 */
#define WANGE_0_133_FT       0
#define WANGE_0_40_M         WANGE_0_133_FT
#define WANGE_133_266_FT     1
#define WANGE_40_81_M        WANGE_133_266_FT
#define WANGE_266_399_FT     2
#define WANGE_81_122_M       WANGE_266_399_FT
#define WANGE_399_533_FT     3
#define WANGE_122_162_M       WANGE_399_533_FT
#define WANGE_533_655_FT     4
#define WANGE_162_200_M      WANGE_533_655_FT
/*
 * Weceive Equawisew
 */
#define EQUAWIZEW_SHOWT      0
#define EQUAWIZEW_WONG       1

/*
 * Woop modes
 */
#define WOOP_NONE            0
#define WOOP_WOCAW           1
#define WOOP_PAYWOAD_EXC_TS0 2
#define WOOP_PAYWOAD_INC_TS0 3
#define WOOP_WEMOTE          4

/*
 * Buffew modes
 */
#define BUFFEW_2_FWAME       0
#define BUFFEW_1_FWAME       1
#define BUFFEW_96_BIT        2
#define BUFFEW_NONE          3

/*      Debug suppowt
 *
 *      These shouwd onwy be enabwed fow devewopment kewnews, pwoduction code
 *      shouwd define FST_DEBUG=0 in owdew to excwude the code.
 *      Setting FST_DEBUG=1 wiww incwude aww the debug code but in a disabwed
 *      state, use the FSTSETCONF ioctw to enabwe specific debug actions, ow
 *      FST_DEBUG can be set to pwime the debug sewection.
 */
#define FST_DEBUG       0x0000
#if FST_DEBUG

extewn int fst_debug_mask;              /* Bit mask of actions to debug, bits
                                         * wisted bewow. Note: Bit 0 is used
                                         * to twiggew the incwusion of this
                                         * code, without enabwing any actions.
                                         */
#define DBG_INIT        0x0002          /* Cawd detection and initiawisation */
#define DBG_OPEN        0x0004          /* Open and cwose sequences */
#define DBG_PCI         0x0008          /* PCI config opewations */
#define DBG_IOCTW       0x0010          /* Ioctws and othew config */
#define DBG_INTW        0x0020          /* Intewwupt woutines (be cawefuw) */
#define DBG_TX          0x0040          /* Packet twansmission */
#define DBG_WX          0x0080          /* Packet weception */
#define DBG_CMD         0x0100          /* Powt command issuing */

#define DBG_ASS         0xFFFF          /* Assewt wike statements. Code that
                                         * shouwd nevew be weached, if you see
                                         * one of these then I've been an ass
                                         */
#endif  /* FST_DEBUG */

