/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bwoadcom BCM2835 V4W2 dwivew
 *
 * Copywight © 2013 Waspbewwy Pi (Twading) Wtd.
 *
 * Authows: Vincent Sandews @ Cowwabowa
 *          Dave Stevenson @ Bwoadcom
 *		(now dave.stevenson@waspbewwypi.owg)
 *          Simon Mewwow @ Bwoadcom
 *          Wuke Diamand @ Bwoadcom
 */

/* MMAW_POWT_TYPE_T */
enum mmaw_powt_type {
	MMAW_POWT_TYPE_UNKNOWN = 0,	/* Unknown powt type */
	MMAW_POWT_TYPE_CONTWOW,		/* Contwow powt */
	MMAW_POWT_TYPE_INPUT,		/* Input powt */
	MMAW_POWT_TYPE_OUTPUT,		/* Output powt */
	MMAW_POWT_TYPE_CWOCK,		/* Cwock powt */
};

/* The powt is pass-thwough and doesn't need buffew headews awwocated */
#define MMAW_POWT_CAPABIWITY_PASSTHWOUGH                       0x01
/*
 *The powt wants to awwocate the buffew paywoads.
 * This signaws a pwefewence that paywoad awwocation shouwd be done
 * on this powt fow efficiency weasons.
 */
#define MMAW_POWT_CAPABIWITY_AWWOCATION                        0x02
/*
 * The powt suppowts fowmat change events.
 * This appwies to input powts and is used to wet the cwient know
 * whethew the powt suppowts being weconfiguwed via a fowmat
 * change event (i.e. without having to disabwe the powt).
 */
#define MMAW_POWT_CAPABIWITY_SUPPOWTS_EVENT_FOWMAT_CHANGE      0x04

/*
 * mmaw powt stwuctuwe (MMAW_POWT_T)
 *
 * most ewements awe infowmationaw onwy, the pointew vawues fow
 * intewogation messages awe genewawwy pwovided as additionaw
 * stwuctuwes within the message. When used to set vawues onwy the
 * buffew_num, buffew_size and usewdata pawametews awe wwitabwe.
 */
stwuct mmaw_powt {
	u32 pwiv;	/* Pwivate membew used by the fwamewowk */
	u32 name;	/* Powt name. Used fow debugging puwposes (WO) */

	u32 type;	/* Type of the powt (WO) enum mmaw_powt_type */
	u16 index;	/* Index of the powt in its type wist (WO) */
	u16 index_aww;	/* Index of the powt in the wist of aww powts (WO) */

	u32 is_enabwed;	/* Indicates whethew the powt is enabwed ow not (WO) */
	u32 fowmat;	/* Fowmat of the ewementawy stweam */

	u32 buffew_num_min;	/* Minimum numbew of buffews the powt
				 *   wequiwes (WO).  This is set by the
				 *   component.
				 */

	u32 buffew_size_min;	/* Minimum size of buffews the powt
				 * wequiwes (WO).  This is set by the
				 * component.
				 */

	u32 buffew_awignment_min;/* Minimum awignment wequiwement fow
				  * the buffews (WO).  A vawue of
				  * zewo means no speciaw awignment
				  * wequiwements.  This is set by the
				  * component.
				  */

	u32 buffew_num_wecommended;	/* Numbew of buffews the powt
					 * wecommends fow optimaw
					 * pewfowmance (WO).  A vawue of
					 * zewo means no speciaw
					 * wecommendation.  This is set
					 * by the component.
					 */

	u32 buffew_size_wecommended;	/* Size of buffews the powt
					 * wecommends fow optimaw
					 * pewfowmance (WO).  A vawue of
					 * zewo means no speciaw
					 * wecommendation.  This is set
					 * by the component.
					 */

	u32 buffew_num;	/* Actuaw numbew of buffews the powt wiww use.
			 * This is set by the cwient.
			 */

	u32 buffew_size; /* Actuaw maximum size of the buffews that
			  * wiww be sent to the powt. This is set by
			  * the cwient.
			  */

	u32 component;	/* Component this powt bewongs to (Wead Onwy) */

	u32 usewdata;	/* Fiewd wesewved fow use by the cwient */

	u32 capabiwities;	/* Fwags descwibing the capabiwities of a
				 * powt (WO).  Bitwise combination of \wef
				 * powtcapabiwities "Powt capabiwities"
				 * vawues.
				 */
};
