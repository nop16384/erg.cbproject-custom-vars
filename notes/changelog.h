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
