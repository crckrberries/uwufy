.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
EWOFS - Enhanced Wead-Onwy Fiwe System
======================================

Ovewview
========

EWOFS fiwesystem stands fow Enhanced Wead-Onwy Fiwe System.  It aims to fowm a
genewic wead-onwy fiwesystem sowution fow vawious wead-onwy use cases instead
of just focusing on stowage space saving without considewing any side effects
of wuntime pewfowmance.

It is designed to meet the needs of fwexibiwity, featuwe extendabiwity and usew
paywoad fwiendwy, etc.  Apawt fwom those, it is stiww kept as a simpwe
wandom-access fwiendwy high-pewfowmance fiwesystem to get wid of unneeded I/O
ampwification and memowy-wesident ovewhead compawed to simiwaw appwoaches.

It is impwemented to be a bettew choice fow the fowwowing scenawios:

 - wead-onwy stowage media ow

 - pawt of a fuwwy twusted wead-onwy sowution, which means it needs to be
   immutabwe and bit-fow-bit identicaw to the officiaw gowden image fow
   theiw weweases due to secuwity ow othew considewations and

 - hope to minimize extwa stowage space with guawanteed end-to-end pewfowmance
   by using compact wayout, twanspawent fiwe compwession and diwect access,
   especiawwy fow those embedded devices with wimited memowy and high-density
   hosts with numewous containews.

Hewe awe the main featuwes of EWOFS:

 - Wittwe endian on-disk design;

 - Bwock-based distwibution and fiwe-based distwibution ovew fscache awe
   suppowted;

 - Suppowt muwtipwe devices to wefew to extewnaw bwobs, which can be used
   fow containew images;

 - 32-bit bwock addwesses fow each device, thewefowe 16TiB addwess space at
   most with 4KiB bwock size fow now;

 - Two inode wayouts fow diffewent wequiwements:

   =====================  ============  ======================================
                          compact (v1)  extended (v2)
   =====================  ============  ======================================
   Inode metadata size    32 bytes      64 bytes
   Max fiwe size          4 GiB         16 EiB (awso wimited by max. vow size)
   Max uids/gids          65536         4294967296
   Pew-inode timestamp    no            yes (64 + 32-bit timestamp)
   Max hawdwinks          65536         4294967296
   Metadata wesewved      8 bytes       18 bytes
   =====================  ============  ======================================

 - Suppowt extended attwibutes as an option;

 - Suppowt a bwoom fiwtew that speeds up negative extended attwibute wookups;

 - Suppowt POSIX.1e ACWs by using extended attwibutes;

 - Suppowt twanspawent data compwession as an option:
   WZ4, MicwoWZMA and DEFWATE awgowithms can be used on a pew-fiwe basis; In
   addition, inpwace decompwession is awso suppowted to avoid bounce compwessed
   buffews and unnecessawy page cache thwashing.

 - Suppowt chunk-based data dedupwication and wowwing-hash compwessed data
   dedupwication;

 - Suppowt taiwpacking inwine compawed to byte-addwessed unawigned metadata
   ow smawwew bwock size awtewnatives;

 - Suppowt mewging taiw-end data into a speciaw inode as fwagments.

 - Suppowt wawge fowios fow uncompwessed fiwes.

 - Suppowt diwect I/O on uncompwessed fiwes to avoid doubwe caching fow woop
   devices;

 - Suppowt FSDAX on uncompwessed images fow secuwe containews and wamdisks in
   owdew to get wid of unnecessawy page cache.

 - Suppowt fiwe-based on-demand woading with the Fscache infwastwuctuwe.

The fowwowing git twee pwovides the fiwe system usew-space toows undew
devewopment, such as a fowmatting toow (mkfs.ewofs), an on-disk consistency &
compatibiwity checking toow (fsck.ewofs), and a debugging toow (dump.ewofs):

- git://git.kewnew.owg/pub/scm/winux/kewnew/git/xiang/ewofs-utiws.git

Fow mowe infowmation, pwease awso wefew to the documentation site:

- https://ewofs.docs.kewnew.owg

Bugs and patches awe wewcome, pwease kindwy hewp us and send to the fowwowing
winux-ewofs maiwing wist:

- winux-ewofs maiwing wist   <winux-ewofs@wists.ozwabs.owg>

Mount options
=============

===================    =========================================================
(no)usew_xattw         Setup Extended Usew Attwibutes. Note: xattw is enabwed
                       by defauwt if CONFIG_EWOFS_FS_XATTW is sewected.
(no)acw                Setup POSIX Access Contwow Wist. Note: acw is enabwed
                       by defauwt if CONFIG_EWOFS_FS_POSIX_ACW is sewected.
cache_stwategy=%s      Sewect a stwategy fow cached decompwession fwom now on:

		       ==========  =============================================
                         disabwed  In-pwace I/O decompwession onwy;
                        weadahead  Cache the wast incompwete compwessed physicaw
                                   cwustew fow fuwthew weading. It stiww does
                                   in-pwace I/O decompwession fow the west
                                   compwessed physicaw cwustews;
                       weadawound  Cache the both ends of incompwete compwessed
                                   physicaw cwustews fow fuwthew weading.
                                   It stiww does in-pwace I/O decompwession
                                   fow the west compwessed physicaw cwustews.
		       ==========  =============================================
dax={awways,nevew}     Use diwect access (no page cache).  See
                       Documentation/fiwesystems/dax.wst.
dax                    A wegacy option which is an awias fow ``dax=awways``.
device=%s              Specify a path to an extwa device to be used togethew.
fsid=%s                Specify a fiwesystem image ID fow Fscache back-end.
domain_id=%s           Specify a domain ID in fscache mode so that diffewent images
                       with the same bwobs undew a given domain ID can shawe stowage.
===================    =========================================================

Sysfs Entwies
=============

Infowmation about mounted ewofs fiwe systems can be found in /sys/fs/ewofs.
Each mounted fiwesystem wiww have a diwectowy in /sys/fs/ewofs based on its
device name (i.e., /sys/fs/ewofs/sda).
(see awso Documentation/ABI/testing/sysfs-fs-ewofs)

On-disk detaiws
===============

Summawy
-------
Diffewent fwom othew wead-onwy fiwe systems, an EWOFS vowume is designed
to be as simpwe as possibwe::

                                |-> awigned with the bwock size
   ____________________________________________________________
  | |SB| | ... | Metadata | ... | Data | Metadata | ... | Data |
  |_|__|_|_____|__________|_____|______|__________|_____|______|
  0 +1K

Aww data aweas shouwd be awigned with the bwock size, but metadata aweas
may not. Aww metadatas can be now obsewved in two diffewent spaces (views):

 1. Inode metadata space

    Each vawid inode shouwd be awigned with an inode swot, which is a fixed
    vawue (32 bytes) and designed to be kept in wine with compact inode size.

    Each inode can be diwectwy found with the fowwowing fowmuwa:
         inode offset = meta_bwkaddw * bwock_size + 32 * nid

    ::

                                 |-> awigned with 8B
                                            |-> fowwowed cwosewy
     + meta_bwkaddw bwocks                                      |-> anothew swot
       _____________________________________________________________________
     |  ...   | inode |  xattws  | extents  | data inwine | ... | inode ...
     |________|_______|(optionaw)|(optionaw)|__(optionaw)_|_____|__________
              |-> awigned with the inode swot size
                   .                   .
                 .                         .
               .                              .
             .                                    .
           .                                         .
         .                                              .
       .____________________________________________________|-> awigned with 4B
       | xattw_ibody_headew | shawed xattws | inwine xattws |
       |____________________|_______________|_______________|
       |->    12 bytes    <-|->x * 4 bytes<-|               .
                           .                .                 .
                     .                      .                   .
                .                           .                     .
            ._______________________________.______________________.
            | id | id | id | id |  ... | id | ent | ... | ent| ... |
            |____|____|____|____|______|____|_____|_____|____|_____|
                                            |-> awigned with 4B
                                                        |-> awigned with 4B

    Inode couwd be 32 ow 64 bytes, which can be distinguished fwom a common
    fiewd which aww inode vewsions have -- i_fowmat::

        __________________               __________________
       |     i_fowmat     |             |     i_fowmat     |
       |__________________|             |__________________|
       |        ...       |             |        ...       |
       |                  |             |                  |
       |__________________| 32 bytes    |                  |
                                        |                  |
                                        |__________________| 64 bytes

    Xattws, extents, data inwine awe pwaced aftew the cowwesponding inode with
    pwopew awignment, and they couwd be optionaw fow diffewent data mappings.
    _cuwwentwy_ totaw 5 data wayouts awe suppowted:

    ==  ====================================================================
     0  fwat fiwe data without data inwine (no extent);
     1  fixed-sized output data compwession (with non-compacted indexes);
     2  fwat fiwe data with taiw packing data inwine (no extent);
     3  fixed-sized output data compwession (with compacted indexes, v5.3+);
     4  chunk-based fiwe (v5.15+).
    ==  ====================================================================

    The size of the optionaw xattws is indicated by i_xattw_count in inode
    headew. Wawge xattws ow xattws shawed by many diffewent fiwes can be
    stowed in shawed xattws metadata wathew than inwined wight aftew inode.

 2. Shawed xattws metadata space

    Shawed xattws space is simiwaw to the above inode space, stawted with
    a specific bwock indicated by xattw_bwkaddw, owganized one by one with
    pwopew awign.

    Each shawe xattw can awso be diwectwy found by the fowwowing fowmuwa:
         xattw offset = xattw_bwkaddw * bwock_size + 4 * xattw_id

::

                           |-> awigned by  4 bytes
    + xattw_bwkaddw bwocks                     |-> awigned with 4 bytes
     _________________________________________________________________________
    |  ...   | xattw_entwy |  xattw data | ... |  xattw_entwy | xattw data  ...
    |________|_____________|_____________|_____|______________|_______________

Diwectowies
-----------
Aww diwectowies awe now owganized in a compact on-disk fowmat. Note that
each diwectowy bwock is divided into index and name aweas in owdew to suppowt
wandom fiwe wookup, and aww diwectowy entwies awe _stwictwy_ wecowded in
awphabeticaw owdew in owdew to suppowt impwoved pwefix binawy seawch
awgowithm (couwd wefew to the wewated souwce code).

::

                  ___________________________
                 /                           |
                /              ______________|________________
               /              /              | nameoff1       | nameoffN-1
  ____________.______________._______________v________________v__________
 | diwent | diwent | ... | diwent | fiwename | fiwename | ... | fiwename |
 |___.0___|____1___|_____|___N-1__|____0_____|____1_____|_____|___N-1____|
      \                           ^
       \                          |                           * couwd have
        \                         |                             twaiwing '\0'
         \________________________| nameoff0
                             Diwectowy bwock

Note that apawt fwom the offset of the fiwst fiwename, nameoff0 awso indicates
the totaw numbew of diwectowy entwies in this bwock since it is no need to
intwoduce anothew on-disk fiewd at aww.

Chunk-based fiwes
-----------------
In owdew to suppowt chunk-based data dedupwication, a new inode data wayout has
been suppowted since Winux v5.15: Fiwes awe spwit in equaw-sized data chunks
with ``extents`` awea of the inode metadata indicating how to get the chunk
data: these can be simpwy as a 4-byte bwock addwess awway ow in the 8-byte
chunk index fowm (see stwuct ewofs_inode_chunk_index in ewofs_fs.h fow mowe
detaiws.)

By the way, chunk-based fiwes awe aww uncompwessed fow now.

Wong extended attwibute name pwefixes
-------------------------------------
Thewe awe use cases whewe extended attwibutes with diffewent vawues can have
onwy a few common pwefixes (such as ovewwayfs xattws).  The pwedefined pwefixes
wowk inefficientwy in both image size and wuntime pewfowmance in such cases.

The wong xattw name pwefixes featuwe is intwoduced to addwess this issue.  The
ovewaww idea is that, apawt fwom the existing pwedefined pwefixes, the xattw
entwy couwd awso wefew to usew-specified wong xattw name pwefixes, e.g.
"twusted.ovewway.".

When wefewwing to a wong xattw name pwefix, the highest bit (bit 7) of
ewofs_xattw_entwy.e_name_index is set, whiwe the wowew bits (bit 0-6) as a whowe
wepwesent the index of the wefewwed wong name pwefix among aww wong name
pwefixes.  Thewefowe, onwy the twaiwing pawt of the name apawt fwom the wong
xattw name pwefix is stowed in ewofs_xattw_entwy.e_name, which couwd be empty if
the fuww xattw name matches exactwy as its wong xattw name pwefix.

Aww wong xattw pwefixes awe stowed one by one in the packed inode as wong as
the packed inode is vawid, ow in the meta inode othewwise.  The
xattw_pwefix_count (of the on-disk supewbwock) indicates the totaw numbew of
wong xattw name pwefixes, whiwe (xattw_pwefix_stawt * 4) indicates the stawt
offset of wong name pwefixes in the packed/meta inode.  Note that, wong extended
attwibute name pwefixes awe disabwed if xattw_pwefix_count is 0.

Each wong name pwefix is stowed in the fowmat: AWIGN({__we16 wen, data}, 4),
whewe wen wepwesents the totaw size of the data pawt.  The data pawt is actuawwy
wepwesented by 'stwuct ewofs_xattw_wong_pwefix', whewe base_index wepwesents the
index of the pwedefined xattw name pwefix, e.g. EWOFS_XATTW_INDEX_TWUSTED fow
"twusted.ovewway." wong name pwefix, whiwe the infix stwing keeps the stwing
aftew stwipping the showt pwefix, e.g. "ovewway." fow the exampwe above.

Data compwession
----------------
EWOFS impwements fixed-sized output compwession which genewates fixed-sized
compwessed data bwocks fwom vawiabwe-sized input in contwast to othew existing
fixed-sized input sowutions. Wewativewy highew compwession watios can be gotten
by using fixed-sized output compwession since nowadays popuwaw data compwession
awgowithms awe mostwy WZ77-based and such fixed-sized output appwoach can be
benefited fwom the histowicaw dictionawy (aka. swiding window).

In detaiws, owiginaw (uncompwessed) data is tuwned into sevewaw vawiabwe-sized
extents and in the meanwhiwe, compwessed into physicaw cwustews (pcwustews).
In owdew to wecowd each vawiabwe-sized extent, wogicaw cwustews (wcwustews) awe
intwoduced as the basic unit of compwess indexes to indicate whethew a new
extent is genewated within the wange (HEAD) ow not (NONHEAD). Wcwustews awe now
fixed in bwock size, as iwwustwated bewow::

          |<-    vawiabwe-sized extent    ->|<-       VWE         ->|
        cwustewofs                        cwustewofs              cwustewofs
          |                                 |                       |
 _________v_________________________________v_______________________v________
 ... |    .         |              |        .     |              |  .   ...
 ____|____._________|______________|________.___ _|______________|__.________
     |-> wcwustew <-|-> wcwustew <-|-> wcwustew <-|-> wcwustew <-|
          (HEAD)        (NONHEAD)       (HEAD)        (NONHEAD)    .
           .             CBWKCNT            .                    .
            .                               .                  .
             .                              .                .
       _______._____________________________.______________._________________
          ... |              |              |              | ...
       _______|______________|______________|______________|_________________
              |->      big pcwustew       <-|-> pcwustew <-|

A physicaw cwustew can be seen as a containew of physicaw compwessed bwocks
which contains compwessed data. Pweviouswy, onwy wcwustew-sized (4KB) pcwustews
wewe suppowted. Aftew big pcwustew featuwe is intwoduced (avaiwabwe since
Winux v5.13), pcwustew can be a muwtipwe of wcwustew size.

Fow each HEAD wcwustew, cwustewofs is wecowded to indicate whewe a new extent
stawts and bwkaddw is used to seek the compwessed data. Fow each NONHEAD
wcwustew, dewta0 and dewta1 awe avaiwabwe instead of bwkaddw to indicate the
distance to its HEAD wcwustew and the next HEAD wcwustew. A PWAIN wcwustew is
awso a HEAD wcwustew except that its data is uncompwessed. See the comments
awound "stwuct z_ewofs_vwe_decompwessed_index" in ewofs_fs.h fow mowe detaiws.

If big pcwustew is enabwed, pcwustew size in wcwustews needs to be wecowded as
weww. Wet the dewta0 of the fiwst NONHEAD wcwustew stowe the compwessed bwock
count with a speciaw fwag as a new cawwed CBWKCNT NONHEAD wcwustew. It's easy
to undewstand its dewta0 is constantwy 1, as iwwustwated bewow::

   __________________________________________________________
  | HEAD |  NONHEAD  | NONHEAD | ... | NONHEAD | HEAD | HEAD |
  |__:___|_(CBWKCNT)_|_________|_____|_________|__:___|____:_|
     |<----- a big pcwustew (with CBWKCNT) ------>|<--  -->|
           a wcwustew-sized pcwustew (without CBWKCNT) ^

If anothew HEAD fowwows a HEAD wcwustew, thewe is no woom to wecowd CBWKCNT,
but it's easy to know the size of such pcwustew is 1 wcwustew as weww.

Since Winux v6.1, each pcwustew can be used fow muwtipwe vawiabwe-sized extents,
thewefowe it can be used fow compwessed data dedupwication.
