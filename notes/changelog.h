2019.11.17
    - created linux targets
    - created changelog.h
    - created "out/export" and "out/pub" directories
    - splitted lx build in multiple files
    - deleted "ID_VAR_USE" id in compiler_options.xrc
    - compileroptionsdialog.cc : deleted d_dvls->DeleteAllItems() - Bug was in
        compileoptionsbase.cpp
    - better publication directories
    - bash script for users
----------------------------------------------------------------------------------------------------
commit 8a7401e7ce377b2e82b2e199d719c72ffcb5b91c
----------------------------------------------------------------------------------------------------
2019.11.21
    - done modifications following obfuscated's code review
    - updated build scripts following xrc HTML comments removal in pub targets

2019.11.22
    - renamed all "ClearVar" stuff to "DeleteAllVars"
----------------------------------------------------------------------------------------------------
commit eaa6a3fb252e9320a52fc71f6f497667821c12e1
----------------------------------------------------------------------------------------------------
2019.11.22
    - added file notes/notes.h
    - added lx scripts for finding strings among all C::B code
2019.11.24
    - branch typedef-CustomVar created
    [typedef-CustomVar]
    - refactor : m_VarsInactive -> m_InactiveVars
    - m_Vars and m_InactiveVars pased to CustomVarHash
    - worked around wxSmith contrib * BUG * in build system : build wxsmith !
    [master]
    - corrected bug ( see [typedef-CustomVar]::todo 009 )
----------------------------------------------------------------------------------------------------
commit f504221aeab80d98747667e6aa71e3935549403d ( master <- typedef-CustomVar )
----------------------------------------------------------------------------------------------------
2019.11.24
    - branch comment-CustomVar created
    [comment-CustomVar]
    - added comments on vars
    - some commented original code was removed because the new code seems to be stable, dont need
      to keep it anymore
    - corrected bug (001)
    - corrected comment color text for user input ( Dialog : tc->wxControl::SetForegroundColour(tc) )
2019.11.25
    [comment-CustomVar]
    - corrected bugs (002) and (003)
    - set m_bDirty when a comment has changed
    - added file "bugs.h"
2019.11.26
    [master]
    - corrected bug (004L)
2019.11.27
    [master]
    - projectloader.cpp : replaced test if ( active)... by call to VarSet()
    - created branch [custom-GetAllVars-two-maps]
    - CompileOptionsBase.h : deleted old PSetVar() method
2019.11.30
    [custom-GetAllVars-two-maps]
    - CompileOptionsBase.cpp : missing SetModified() calls, but this branch is dead now so wont fix
