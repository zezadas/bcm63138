//==============================================================================
//==============================================================================
//
//      Copyright(c) 2007 Media5 Corporation. ("Media5")
//
//  NOTICE:
//   This document contains information that is confidential and proprietary to
//   Media5.
//
//   Media5 reserves all rights to this document as well as to the Intellectual
//   Property of the document and the technology and know-how that it includes
//   and represents.
//
//   This publication cannot be reproduced, neither in whole nor in part, in any
//   form whatsoever without prior written approval by Media5.
//
//   Media5 reserves the right to revise this publication and make changes at
//   any time and without the obligation to notify any person and/or entity of
//   such revisions and/or changes.
//
//==============================================================================
//==============================================================================
#ifndef MXG_CSCECORECOMPONENTSINITIALIZER_H
//M5T_INTERNAL_USE_BEGIN
#define MXG_CSCECORECOMPONENTSINITIALIZER_H

//==============================================================================
//====  INCLUDES + FORWARD DECLARATIONS  =======================================
//==============================================================================

//-- M5T Global definitions.
//---------------------------
#ifndef MXG_MXCONFIG_H
#include "Config/MxConfig.h"
#endif

MX_NAMESPACE_START(MXD_GNS)

//-- Forward Declarations.
//-------------------------

//==============================================================================
//====  CONSTANTS + DEFINES  ===================================================
//==============================================================================

//==============================================================================
//====  NEW TYPE DEFINITIONS  ==================================================
//==============================================================================

//==============================================================================
//== Class: CSceCoreComponentsInitializer
//========================================
//<GROUP TID_PACKAGE_STARTUP_CLASSES>
//
// Summary:
//   This class is responsible of doing the initialization and inalization of
//   the SceCoreComponents package.
//
// Description:
//   This class contains the methods needed to initialize and finalize the
//   SceCoreComponents package. CSceCoreComponentsInitializer::Initialize must be called
//   before any of the functionalities from SceCoreComponents are used.
//   CSceCoreComponentsInitializer::Finalize must be called when the functionalities
//   from SceCoreComponents are not needed anymore.
//
//   This class is not thread safe. If more than one call to Initialize or
//   Finalize are necessary these calls must come from the same thread or be
//   protected against concurrent access.
//
// Location:
//   Startup/CSceCoreComponentsInitializer.h
//
//==============================================================================
class CSceCoreComponentsInitializer
{
//-- Friend Declarations.
//------------------------

//-- New types within class namespace.
//-------------------------------------
private:
    // Function pointers to the Finalize and the Initialize methods.
    //---------------------------------------------------------------
    typedef void (*PFNFinalize)();
    typedef mxt_result (*PFNInitialize)();

    // Structure to hold information on each package Initialize and Finalize
    // methods.
    //-----------------------------------------------------------------------
    struct SInitializeFinalize
    {
        // Method to call to initialize the package.
        //-------------------------------------------
        PFNInitialize   m_pfnInitialize;

        // Method to call to finalize the package.
        //-----------------------------------------
        PFNFinalize     m_pfnFinalize;

        // Package name.
        //---------------
        const char*     m_pszPackageName;
    };

//-- Published Interface.
//------------------------
public:
    //-- << Stereotype >>
    //--------------------

    // Summary:
    //  Initializes the Core and its dependencies.
    //----------------------------------------------------
    static mxt_result Initialize();

    // Summary:
    //  Finalizes the Core and its dependencies.
    //--------------------------------------------------
    static void Finalize();

//-- Hidden Methods
//-------------------
private:
    //-- << Helper methods >>
    //------------------------

    // Summary:
    //  Does the necessary processing for initialization of subpackages.
    //-------------------------------------------------------------------
    static mxt_result InitializeHelper();

    // Summary:
    //  Appends the Finalize method to the list of methods to call at
    //  finalization.
    //----------------------------------------------------------------
    static void AppendFinalize(IN PFNFinalize pfnFinalize);

    //-- << Deactivated Constructors / Destructors / Operators >>
    //------------------------------------------------------------

    // Summary:
    //  Default Constructor.
    //-----------------------
    CSceCoreComponentsInitializer();

    // Summary:
    //  Destructor.
    //--------------
    virtual ~CSceCoreComponentsInitializer();

    // Summary:
    //  Copy Constructor.
    //--------------------
    CSceCoreComponentsInitializer(IN const CSceCoreComponentsInitializer& rSrc);

    // Summary:
    //  Assignment Operator.
    //-----------------------
    CSceCoreComponentsInitializer& operator=(IN const CSceCoreComponentsInitializer& rSrc);

//-- Hidden Data Members.
//------------------------
private:
    // Counts the number of times Initialize and Finalize have been called to
    // make sure that both are done only once.
    static unsigned int ms_uInitializationCount;

    // Counts the number of subpackages successfully initialized.
    static unsigned int ms_uNumSuccessfulInitialize;

    // This array stores all packages to be initialized.
    static const SInitializeFinalize ms_astINITIALIZE_FINALIZE[];

    // This array stores the Finalize() method for Initialize() successfully
    // called. This array is used when calling Finalize. It has the advantage
    // of having to list all subpackages in one place only and avoid
    // synchronization errors between Initialize and Finalize. It also has the
    // advantage of giving a simple way to have Finalize() undo only what
    // Initialize() has done up to the moment an error is encountered by
    // Initialize().
    static PFNFinalize ms_apfnFinalizeToCall[];

};


//==============================================================================
//====  INLINE METHODS  ========================================================
//==============================================================================

MX_NAMESPACE_END(MXD_GNS)

//M5T_INTERNAL_USE_END

#endif //-- #ifndef MXG_CSCECORECOMPONENTSINITIALIZER_H

