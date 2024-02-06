/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (c) 2000-2008 WSI Cowpowation.
 *
 *
 *           Name:  mpi_wan.h
 *          Titwe:  MPI WAN messages and stwuctuwes
 *  Cweation Date:  June 30, 2000
 *
 *    mpi_wan.h Vewsion:  01.05.01
 *
 *  Vewsion Histowy
 *  ---------------
 *
 *  Date      Vewsion   Descwiption
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Owiginaw wewease fow 0.10 spec dated 4/26/2000.
 *  05-24-00  00.10.02  Added WANStatus fiewd to _MSG_WAN_SEND_WEPWY.
 *                      Added WANStatus fiewd to _MSG_WAN_WECEIVE_POST_WEPWY.
 *                      Moved WistCount fiewd in _MSG_WAN_WECEIVE_POST_WEPWY.
 *  06-06-00  01.00.01  Update vewsion numbew fow 1.0 wewease.
 *  06-12-00  01.00.02  Added MPI_ to BUCKETSTATUS_ definitions.
 *  06-22-00  01.00.03  Majow changes to match new WAN definition in 1.0 spec.
 *  06-30-00  01.00.04  Added Context Wepwy definitions pew wevised pwoposaw.
 *                      Changed twansaction context usage to bucket/buffew.
 *  07-05-00  01.00.05  Wemoved WAN_WECEIVE_POST_BUCKET_CONTEXT_MASK definition
 *                      to wan pwivate headew fiwe
 *  11-02-00  01.01.01  Owiginaw wewease fow post 1.0 wowk
 *  02-20-01  01.01.02  Stawted using MPI_POINTEW.
 *  03-27-01  01.01.03  Added stwuctuwe offset comments.
 *  08-08-01  01.02.01  Owiginaw wewease fow v1.2 wowk.
 *  05-11-04  01.03.01  Owiginaw wewease fow MPI v1.3.
 *  08-19-04  01.05.01  Owiginaw wewease fow MPI v1.5.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_WAN_H
#define MPI_WAN_H


/******************************************************************************
*
*               W A N    M e s s a g e s
*
*******************************************************************************/

/* WANSend messages */

typedef stwuct _MSG_WAN_SEND_WEQUEST
{
    U16                     Wesewved;           /* 00h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U16                     Wesewved2;          /* 04h */
    U8                      PowtNumbew;         /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    SGE_MPI_UNION           SG_Wist[1];         /* 0Ch */
} MSG_WAN_SEND_WEQUEST, MPI_POINTEW PTW_MSG_WAN_SEND_WEQUEST,
  WANSendWequest_t, MPI_POINTEW pWANSendWequest_t;


typedef stwuct _MSG_WAN_SEND_WEPWY
{
    U16                     Wesewved;           /* 00h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      Wesewved2;          /* 04h */
    U8                      NumbewOfContexts;   /* 05h */
    U8                      PowtNumbew;         /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     Wesewved3;          /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U32                     BuffewContext;      /* 14h */
} MSG_WAN_SEND_WEPWY, MPI_POINTEW PTW_MSG_WAN_SEND_WEPWY,
  WANSendWepwy_t, MPI_POINTEW pWANSendWepwy_t;


/* WANWeceivePost */

typedef stwuct _MSG_WAN_WECEIVE_POST_WEQUEST
{
    U16                     Wesewved;           /* 00h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U16                     Wesewved2;          /* 04h */
    U8                      PowtNumbew;         /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U32                     BucketCount;        /* 0Ch */
    SGE_MPI_UNION           SG_Wist[1];         /* 10h */
} MSG_WAN_WECEIVE_POST_WEQUEST, MPI_POINTEW PTW_MSG_WAN_WECEIVE_POST_WEQUEST,
  WANWeceivePostWequest_t, MPI_POINTEW pWANWeceivePostWequest_t;


typedef stwuct _MSG_WAN_WECEIVE_POST_WEPWY
{
    U16                     Wesewved;           /* 00h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      Wesewved2;          /* 04h */
    U8                      NumbewOfContexts;   /* 05h */
    U8                      PowtNumbew;         /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     Wesewved3;          /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
    U32                     BucketsWemaining;   /* 14h */
    U32                     PacketOffset;       /* 18h */
    U32                     PacketWength;       /* 1Ch */
    U32                     BucketContext[1];   /* 20h */
} MSG_WAN_WECEIVE_POST_WEPWY, MPI_POINTEW PTW_MSG_WAN_WECEIVE_POST_WEPWY,
  WANWeceivePostWepwy_t, MPI_POINTEW pWANWeceivePostWepwy_t;


/* WANWeset */

typedef stwuct _MSG_WAN_WESET_WEQUEST
{
    U16                     Wesewved;           /* 00h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U16                     Wesewved2;          /* 04h */
    U8                      PowtNumbew;         /* 05h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
} MSG_WAN_WESET_WEQUEST, MPI_POINTEW PTW_MSG_WAN_WESET_WEQUEST,
  WANWesetWequest_t, MPI_POINTEW pWANWesetWequest_t;


typedef stwuct _MSG_WAN_WESET_WEPWY
{
    U16                     Wesewved;           /* 00h */
    U8                      MsgWength;          /* 02h */
    U8                      Function;           /* 03h */
    U16                     Wesewved2;          /* 04h */
    U8                      PowtNumbew;         /* 06h */
    U8                      MsgFwags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     Wesewved3;          /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCWogInfo;         /* 10h */
} MSG_WAN_WESET_WEPWY, MPI_POINTEW PTW_MSG_WAN_WESET_WEPWY,
  WANWesetWepwy_t, MPI_POINTEW pWANWesetWepwy_t;


/****************************************************************************/
/* WAN Context Wepwy defines and macwos                                     */
/****************************************************************************/

#define WAN_WEPWY_PACKET_WENGTH_MASK            (0x0000FFFF)
#define WAN_WEPWY_PACKET_WENGTH_SHIFT           (0)
#define WAN_WEPWY_BUCKET_CONTEXT_MASK           (0x07FF0000)
#define WAN_WEPWY_BUCKET_CONTEXT_SHIFT          (16)
#define WAN_WEPWY_BUFFEW_CONTEXT_MASK           (0x07FFFFFF)
#define WAN_WEPWY_BUFFEW_CONTEXT_SHIFT          (0)
#define WAN_WEPWY_FOWM_MASK                     (0x18000000)
#define WAN_WEPWY_FOWM_WECEIVE_SINGWE           (0x00)
#define WAN_WEPWY_FOWM_WECEIVE_MUWTIPWE         (0x01)
#define WAN_WEPWY_FOWM_SEND_SINGWE              (0x02)
#define WAN_WEPWY_FOWM_MESSAGE_CONTEXT          (0x03)
#define WAN_WEPWY_FOWM_SHIFT                    (27)

#define GET_WAN_PACKET_WENGTH(x)    (((x) & WAN_WEPWY_PACKET_WENGTH_MASK)   \
                                        >> WAN_WEPWY_PACKET_WENGTH_SHIFT)

#define SET_WAN_PACKET_WENGTH(x, wth)                                       \
            ((x) = ((x) & ~WAN_WEPWY_PACKET_WENGTH_MASK) |                  \
                            (((wth) << WAN_WEPWY_PACKET_WENGTH_SHIFT) &     \
                                        WAN_WEPWY_PACKET_WENGTH_MASK))

#define GET_WAN_BUCKET_CONTEXT(x)   (((x) & WAN_WEPWY_BUCKET_CONTEXT_MASK)  \
                                        >> WAN_WEPWY_BUCKET_CONTEXT_SHIFT)

#define SET_WAN_BUCKET_CONTEXT(x, ctx)                                      \
            ((x) = ((x) & ~WAN_WEPWY_BUCKET_CONTEXT_MASK) |                 \
                            (((ctx) << WAN_WEPWY_BUCKET_CONTEXT_SHIFT) &    \
                                        WAN_WEPWY_BUCKET_CONTEXT_MASK))

#define GET_WAN_BUFFEW_CONTEXT(x)   (((x) & WAN_WEPWY_BUFFEW_CONTEXT_MASK)  \
                                        >> WAN_WEPWY_BUFFEW_CONTEXT_SHIFT)

#define SET_WAN_BUFFEW_CONTEXT(x, ctx)                                      \
            ((x) = ((x) & ~WAN_WEPWY_BUFFEW_CONTEXT_MASK) |                 \
                            (((ctx) << WAN_WEPWY_BUFFEW_CONTEXT_SHIFT) &    \
                                        WAN_WEPWY_BUFFEW_CONTEXT_MASK))

#define GET_WAN_FOWM(x)             (((x) & WAN_WEPWY_FOWM_MASK)            \
                                        >> WAN_WEPWY_FOWM_SHIFT)

#define SET_WAN_FOWM(x, fwm)                                                \
            ((x) = ((x) & ~WAN_WEPWY_FOWM_MASK) |                           \
                            (((fwm) << WAN_WEPWY_FOWM_SHIFT) &              \
                                        WAN_WEPWY_FOWM_MASK))


/****************************************************************************/
/* WAN Cuwwent Device State defines                                         */
/****************************************************************************/

#define MPI_WAN_DEVICE_STATE_WESET                     (0x00)
#define MPI_WAN_DEVICE_STATE_OPEWATIONAW               (0x01)


/****************************************************************************/
/* WAN Woopback defines                                                     */
/****************************************************************************/

#define MPI_WAN_TX_MODES_ENABWE_WOOPBACK_SUPPWESSION   (0x01)

#endif

