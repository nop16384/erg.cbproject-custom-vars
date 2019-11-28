/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision: 11887 $
 * $Id: compileoptionsbase.cpp 11887 2019-10-26 09:12:28Z fuscated $
 * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/compileoptionsbase.cpp $
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include "compileoptionsbase.h"
    #include "sdk_events.h"
    #include "manager.h"
    #include "macrosmanager.h"
#endif

namespace { static const bool s_case_sensitive = platform::windows ? false : true; }

CompileOptionsBase::CompileOptionsBase()
    : m_Platform(spAll),
    m_LinkerExecutable(LinkerExecutableOption::AutoDetect),
    m_Modified(false),
    m_AlwaysRunPostCmds(false)
{
    //ctor
}

CompileOptionsBase::~CompileOptionsBase()
{
    //dtor
}

void CompileOptionsBase::AddPlatform(int platform)
{
    if (m_Platform & platform)
        return;
    m_Platform |= platform;
    SetModified(true);
}

void CompileOptionsBase::RemovePlatform(int platform)
{
    if (!(m_Platform & platform))
        return;
    m_Platform &= ~platform;
    SetModified(true);
}

void CompileOptionsBase::SetPlatforms(int platforms)
{
    if (m_Platform == platforms)
        return;
    m_Platform = platforms;
    SetModified(true);
}

int CompileOptionsBase::GetPlatforms() const
{
    return m_Platform;
}

bool CompileOptionsBase::SupportsCurrentPlatform() const
{
    if(platform::windows)
        return m_Platform & spWindows;
    if(platform::Unix)
        return m_Platform & spUnix;
    if(platform::macosx)
        return m_Platform & spMac;

    return false;
}

void CompileOptionsBase::SetLinkerOptions(const wxArrayString& linkerOpts)
{
    if (m_LinkerOptions == linkerOpts)
        return;
    m_LinkerOptions = linkerOpts;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetLinkerOptions() const
{
    return m_LinkerOptions;
}

void CompileOptionsBase::SetLinkLibs(const wxArrayString& linkLibs)
{
    if (m_LinkLibs == linkLibs)
        return;
    m_LinkLibs = linkLibs;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetLinkLibs() const
{
    return m_LinkLibs;
}

void CompileOptionsBase::SetCompilerOptions(const wxArrayString& compilerOpts)
{
    if (m_CompilerOptions == compilerOpts)
        return;
    m_CompilerOptions = compilerOpts;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetCompilerOptions() const
{
    return m_CompilerOptions;
}

void CompileOptionsBase::SetResourceCompilerOptions(const wxArrayString& resourceCompilerOpts)
{
    if (m_ResourceCompilerOptions == resourceCompilerOpts)
        return;
    m_ResourceCompilerOptions = resourceCompilerOpts;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetResourceCompilerOptions() const
{
    return m_ResourceCompilerOptions;
}

void CompileOptionsBase::SetIncludeDirs(const wxArrayString& includeDirs)
{
    if (m_IncludeDirs == includeDirs)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_IncludeDirs.Clear();
    for (size_t i = 0; i < includeDirs.GetCount(); ++i)
    {
        wxString entry = UnixFilename(includeDirs[i]);
        if (m_IncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_IncludeDirs.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetIncludeDirs() const
{
    return m_IncludeDirs;
}

void CompileOptionsBase::SetResourceIncludeDirs(const wxArrayString& resIncludeDirs)
{
    if (m_ResIncludeDirs == resIncludeDirs)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_ResIncludeDirs.Clear();
    for (size_t i = 0; i < resIncludeDirs.GetCount(); ++i)
    {
        wxString entry = UnixFilename(resIncludeDirs[i]);
        if (m_ResIncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_ResIncludeDirs.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetResourceIncludeDirs() const
{
    return m_ResIncludeDirs;
}

void CompileOptionsBase::SetLibDirs(const wxArrayString& libDirs)
{
    if (m_LibDirs == libDirs)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_LibDirs.Clear();
    for (size_t i = 0; i < libDirs.GetCount(); ++i)
    {
        wxString entry = UnixFilename(libDirs[i]);
        if (m_LibDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_LibDirs.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetLibDirs() const
{
    return m_LibDirs;
}

void CompileOptionsBase::SetBuildScripts(const wxArrayString& scripts)
{
    if (m_Scripts == scripts)
        return;

    // make sure we don't have duplicate entries
    // that's why we don't assign the array but rather copy it entry by entry...

    m_Scripts.Clear();
    for (size_t i = 0; i < scripts.GetCount(); ++i)
    {
        wxString entry = UnixFilename(scripts[i]);
        if (m_Scripts.Index(entry, s_case_sensitive) == wxNOT_FOUND)
            m_Scripts.Add(entry);
    }
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetBuildScripts() const
{
    return m_Scripts;
}

void CompileOptionsBase::SetCommandsBeforeBuild(const wxArrayString& commands)
{
    if (m_CmdsBefore == commands)
        return;
    m_CmdsBefore = commands;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetCommandsBeforeBuild() const
{
    return m_CmdsBefore;
}

void CompileOptionsBase::SetCommandsAfterBuild(const wxArrayString& commands)
{
    if (m_CmdsAfter == commands)
        return;
    m_CmdsAfter = commands;
    SetModified(true);
}

const wxArrayString& CompileOptionsBase::GetCommandsAfterBuild() const
{
    return m_CmdsAfter;
}

bool CompileOptionsBase::GetAlwaysRunPostBuildSteps() const
{
    return m_AlwaysRunPostCmds;
}

void CompileOptionsBase::SetAlwaysRunPostBuildSteps(bool always)
{
    if (m_AlwaysRunPostCmds == always)
        return;
    m_AlwaysRunPostCmds = always;
    SetModified(true);
}

bool CompileOptionsBase::GetModified() const
{
    return m_Modified;
}

void CompileOptionsBase::SetModified(bool modified)
{
    m_Modified = modified;
}

void CompileOptionsBase::AddLinkerOption(const wxString& option)
{
    if (m_LinkerOptions.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_LinkerOptions.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddLinkLib(const wxString& option)
{
    if (m_LinkLibs.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_LinkLibs.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddCompilerOption(const wxString& option)
{
    if (m_CompilerOptions.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_CompilerOptions.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddResourceCompilerOption(const wxString& option)
{
    if (m_ResourceCompilerOptions.Index(option, s_case_sensitive) == wxNOT_FOUND)
    {
        m_ResourceCompilerOptions.Add(option);
        SetModified(true);
    }
}

void CompileOptionsBase::AddIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    if (m_IncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
    {
        m_IncludeDirs.Add(entry);
        SetModified(true);
    }
}

void CompileOptionsBase::AddResourceIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    if (m_ResIncludeDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
    {
        m_ResIncludeDirs.Add(entry);
        SetModified(true);
    }
}

void CompileOptionsBase::AddLibDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    if (m_LibDirs.Index(entry, s_case_sensitive) == wxNOT_FOUND)
    {
        m_LibDirs.Add(entry);
        SetModified(true);
    }
}

void CompileOptionsBase::AddCommandsBeforeBuild(const wxString& command)
{
    m_CmdsBefore.Add(command);
    SetModified(true);
}

void CompileOptionsBase::AddCommandsAfterBuild(const wxString& command)
{
    m_CmdsAfter.Add(command);
    SetModified(true);
}

void CompileOptionsBase::AddBuildScript(const wxString& script)
{
    wxString envopt = UnixFilename(script);
    if (m_Scripts.Index(envopt, s_case_sensitive) == wxNOT_FOUND)
    {
        m_Scripts.Add(envopt);
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceLinkerOption(const wxString& option, const wxString& new_option)
{
    int idx = m_LinkerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkerOptions.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceLinkLib(const wxString& option, const wxString& new_option)
{
    int idx = m_LinkLibs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkLibs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceCompilerOption(const wxString& option, const wxString& new_option)
{
    int idx = m_CompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_CompilerOptions.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceResourceCompilerOption(const wxString& option, const wxString& new_option)
{
    int idx = m_ResourceCompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResourceCompilerOptions.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceIncludeDir(const wxString& option, const wxString& new_option)
{
    int idx = m_IncludeDirs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_IncludeDirs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceResourceIncludeDir(const wxString& option, const wxString& new_option)
{
    int idx = m_ResIncludeDirs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResIncludeDirs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::ReplaceLibDir(const wxString& option, const wxString& new_option)
{
    int idx = m_LibDirs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LibDirs.Item(idx) = new_option;
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveLinkerOption(const wxString& option)
{
    int idx = m_LinkerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkerOptions.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveLinkLib(const wxString& option)
{
    int idx = m_LinkLibs.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LinkLibs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveCompilerOption(const wxString& option)
{
    int idx = m_CompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_CompilerOptions.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveResourceCompilerOption(const wxString& option)
{
    int idx = m_ResourceCompilerOptions.Index(option, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResourceCompilerOptions.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    int idx = m_IncludeDirs.Index(entry, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_IncludeDirs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveResourceIncludeDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    int idx = m_ResIncludeDirs.Index(entry, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_ResIncludeDirs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveLibDir(const wxString& option)
{
    wxString entry = UnixFilename(option);
    int idx = m_LibDirs.Index(entry, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_LibDirs.RemoveAt(idx);
        SetModified(true);
    }
}

void CompileOptionsBase::RemoveCommandsBeforeBuild(const wxString& command)
{
    m_CmdsBefore.Remove(command);
    SetModified(true);
}

void CompileOptionsBase::RemoveCommandsAfterBuild(const wxString& command)
{
    m_CmdsAfter.Remove(command);
    SetModified(true);
}

void CompileOptionsBase::RemoveBuildScript(const wxString& script)
{
    wxString envopt = UnixFilename(script);
    int idx = m_Scripts.Index(envopt, s_case_sensitive);
    if (idx != wxNOT_FOUND)
    {
        m_Scripts.RemoveAt(idx);
        SetModified(true);
    }
}
//  ................................................................................................    ERG+
bool CompileOptionsBase::SetVar(const wxString& key, const wxString& value, bool onlyIfExists)
{
    return VarSet(key, value, wxString(""), CompileOptionsBase::eVarActive, onlyIfExists);
}

bool CompileOptionsBase::UnsetVar(const wxString& key)
{
    CustomVarHash::iterator it = m_ActiveVars.find(key);
    if (it != m_ActiveVars.end())
    {
        m_ActiveVars.erase(it);
        SetModified(true);
        return true;
    }
    return false;
}

void CompileOptionsBase::UnsetAllVars()
{
    m_ActiveVars.clear();
    SetModified(true);                                                                              // _ERG_CORR_ added, was missing
}

bool CompileOptionsBase::HasVar(const wxString& key) const
{
    CustomVarHash::const_iterator it = m_ActiveVars.find(key);
    if (it != m_ActiveVars.end())
        return true;
    return false;
}

const wxString& CompileOptionsBase::GetVar(const wxString& key) const
{
    CustomVarHash::const_iterator it = m_ActiveVars.find(key);
    if (it != m_ActiveVars.end())
    return it->second.value;

    static wxString emptystring = wxEmptyString;
    return emptystring;
}

//  ERG const CustomVarHash& CompileOptionsBase::GetAllVars() const
//  ERG {
//  ERG     return m_ActiveVars;
//  ERG }
//  ................................................................................................
bool CompileOptionsBase::VarSet(wxString const & _i_key, wxString const & _i_val, wxString const & _i_comment, int _i_flags, bool _i_only_if_exists)
{
    CustomVarHash               *   h1;                                                             // destination hash
    CustomVarHash               *   h2;                                                             // the other hash
    CustomVarHash::iterator         it1;
    CustomVarHash::iterator         it2;
    CustomVar                       cv  = { _i_val, _i_comment, _i_flags };
    //  ............................................................................................
    if ( _i_flags & CompileOptionsBase::eVarActive )
    {
        h1  =   &m_ActiveVars;
        h2  =   &m_InactiveVars;
    }
    else
    {
        h1  =   &m_InactiveVars;
        h2  =   &m_ActiveVars;
    }

    it1 = h1->find(_i_key);
    it2 = h2->find(_i_key);
    //  ............................................................................................
    if ( _i_only_if_exists )
    {
        if ( it1 == h1->end() )
        {
            if ( it2 == h2->end() )
            {
                return false;
            }
            else
            {
                h2->erase(it2);
                (*h1)[_i_key] = cv;
                SetModified(true);
                return true;
            }
        }
        else
        {
            if ( it2 != h2->end() )                                                                 // PB !
            {
                return false;
            }
            it1->second = cv;
            SetModified(true);
            return true;
        }
    }
    //  ............................................................................................
    if ( it1 == h1->end() )
    {
        if ( it2 == h2->end() )
        {
            (*h1)[_i_key] = cv;
            SetModified(true);
            return true;
        }
        else
        {
            h2->erase(it2);
            (*h1)[_i_key] = cv;
            SetModified(true);
            return true;
        }
    }
    else
    {
        if ( it2 != h2->end() )                                                                     // PB !
        {
            return false;
        }
        it1->second = cv;
        SetModified(true);
        return true;
    }
}

bool CompileOptionsBase::VarSetValue(wxString const & _i_key, wxString const & _i_val)
{
    CustomVarHash::iterator it;
    //  ............................................................................................
    if ( VarGetIterator(_i_key, it) )
    {
        it->second.value = _i_val;
        return true;
    }

    return false;
}

bool CompileOptionsBase::VarSetComment(wxString const & _i_key, wxString const & _i_com)
{
    CustomVarHash::iterator it;
    //  ............................................................................................
    if ( VarGetIterator(_i_key, it) )
    {
        it->second.comment = _i_com;
        return true;
    }

    return false;
}

bool CompileOptionsBase::VarSetFlags  (wxString const & _i_key, int _i_flags)
{
    //  This method can change the stotage ( m_ActiveVars / m_InactiveVars ) following
    //  eVarActive / eVarInactive flag
    //  ............................................................................................
    CustomVar cv;
    //  ............................................................................................
    if ( ! VarGet(_i_key, cv) )
        return false;

    return VarSet(_i_key, cv.value, cv.comment, _i_flags, true);
}

bool CompileOptionsBase::VarGetIterator(wxString const & _i_key, CustomVarHash::iterator & _o_it)
{
    CustomVarHash           &   h1  =   m_ActiveVars;
    CustomVarHash           &   h2  =   m_InactiveVars;
    CustomVarHash::iterator     it;
    //  ............................................................................................
    it = h1.find(_i_key);
    if ( it != h1.end() )
        _o_it = it;
        return true;

    it = h2.find(_i_key);
    if ( it != h2.end() )
        _o_it = it;
        return true;

    return false;
}

bool CompileOptionsBase::VarGet(wxString const & _i_key, CustomVar & _o_cv) const
{
    CustomVarHash                   const   &   h1  =   m_ActiveVars;
    CustomVarHash                   const   &   h2  =   m_InactiveVars;
    CustomVarHash::const_iterator   it;
    //  ............................................................................................
    it = h1.find(_i_key);
    if ( it != h1.end() )
        _o_cv = it->second;
        return true;

    it = h2.find(_i_key);
    if ( it != h2.end() )
        _o_cv = it->second;
        return true;

    return false;
}

bool CompileOptionsBase::VarGetValue(wxString const & _i_key, wxString & _o_val) const
{
    CustomVar cv;
    //  ............................................................................................
    if ( VarGet(_i_key, cv) )
    {
        _o_val = cv.value;
        return true;
    }

    return false;
}

bool CompileOptionsBase::VarGetComment(wxString const & _i_key, wxString & _o_com) const
{
    CustomVar cv;
    //  ............................................................................................
    if ( VarGet(_i_key, cv) )
    {
        _o_com = cv.comment;
        return true;
    }

    return false;
}

bool CompileOptionsBase::VarGetFlags(wxString const & _i_key, int & _o_flags) const
{
    CustomVar cv;
    //  ............................................................................................
    if ( VarGet(_i_key, cv) )
    {
        _o_flags = cv.flags;
        return true;
    }

    return false;
}

//  ERG CustomVarHash const & CompileOptionsBase::VarGetAll(int _i_activity_flags) const
//  ERG {
//  ERG if ( _i_activity_flags & CompileOptionsBase::eVarActive )
//  ERG         return m_ActiveVars;

//  ERG     if ( _i_activity_flags & CompileOptionsBase::eVarInactive )
//  ERG         return m_InactiveVars;

//  ERG     return m_ActiveVars;                                                                            // by default
//  ERG
//  ERG }

bool CompileOptionsBase::VarUnset(wxString const & _i_key)
{
    CustomVarHash           &   h1  =   m_ActiveVars;
    CustomVarHash           &   h2  =   m_InactiveVars;
    CustomVarHash::iterator     it;
    //  ............................................................................................
    it = h1.find(_i_key);
    if ( it != h1.end() )
    {
        h1.erase(it);
        return true;
    }

    it = h2.find(_i_key);
    if ( it != h2.end() )
    {
        h2.erase(it);
        return true;
    }

    return false;
}
void CompileOptionsBase::VarUnsetAll(int _i_activity_flags)
{
    if ( _i_activity_flags & CompileOptionsBase::eVarActive )
        m_ActiveVars.clear();

    if ( _i_activity_flags & CompileOptionsBase::eVarInactive )
        m_InactiveVars.clear();
}

//
//  custom GetAllVars
//

//  this variables because in CB code, GetAllVars() is assumed const. So we cant define these vars
//  as class members.
static  int                                 m_VarEnumFlags;
static  CustomVarHash const             *   m_VarEnumHash;
static  CustomVarHash::const_iterator       m_VarEnumIterator;

void CompileOptionsBase::VarEnumInit(CustomVarHash const * _i_hash) const
{
    m_VarEnumHash       =   _i_hash;
    m_VarEnumIterator   =   m_VarEnumHash->begin();
}

CustomVarHash::const_iterator* CompileOptionsBase::VarEnumFind() const
{
    while ( m_VarEnumIterator != m_VarEnumHash->end() )
    {
        if ( m_VarEnumIterator->second.flags & m_VarEnumFlags )
            return &m_VarEnumIterator;

        m_VarEnumIterator++;
    }

    if ( m_VarEnumHash == &m_InactiveVars )
        return nullptr;

    VarEnumInit(&m_InactiveVars);

    return VarEnumFind();
}

CustomVarHash::const_iterator* CompileOptionsBase::VarEnumGetFirst(int _i_flags) const
{
    m_VarEnumFlags      =   _i_flags;

    VarEnumInit(&m_ActiveVars);

    return VarEnumFind();
 }

CustomVarHash::const_iterator* CompileOptionsBase::VarEnumGetNext() const
{
    m_VarEnumIterator++;
    return VarEnumFind();
}
//  ................................................................................................    ERG-
void CompileOptionsBase::SetLinkerExecutable(LinkerExecutableOption option)
{
    if (m_LinkerExecutable == option)
        return;

    // We need to do this range check because this function could be called from scripting and there
    // is no range checking done by the compiler.
    if (option>= LinkerExecutableOption::First && option <= LinkerExecutableOption::Last)
    {
        m_LinkerExecutable = option;
        SetModified(true);
    }
    else if (m_LinkerExecutable != LinkerExecutableOption::AutoDetect)
    {
        m_LinkerExecutable = LinkerExecutableOption::AutoDetect;
        SetModified(true);
    }
}

LinkerExecutableOption CompileOptionsBase::GetLinkerExecutable() const
{
    return m_LinkerExecutable;
}
