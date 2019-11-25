----------------------------------------------------------------------------------------------------
2019.11.22  Fusion of m_Vars and m_InactiveVars
----------------------------------------------------------------------------------------------------
Code using SetVar :

----------------------------------------------------------------------------------------------------
2019.11.22  typedef enums
----------------------------------------------------------------------------------------------------
- Squirrel stuff does not support typedef enum, so just do enums !
----------------------------------------------------------------------------------------------------
2019.11.22  virt functions pb
----------------------------------------------------------------------------------------------------
- Squirrel or scripting or sql does not work with virtual function
  - cant overload by parameters -> bug
  - dont mix virtual SetVar() and SetVar() ->scriptbindings.cpp:901:59: note:   couldn't deduce template parameter ‘Func’
                 func(&CompileOptionsBase::SetVar, "SetVar").
....................................................................................................
BUG
....................................................................................................
- cant have SetVar and :
    - _SetVar   name ?
    - PSetVar   name / decoration ?
    - virtual bool Xxx(wxString const & _i_key, wxString const & _i_val, int _i_flags, wxString const & _i_comment, bool _i_only_if_exists) wtf !!!
    - virtual bool Xxx(wxString const & _i_key, wxString const & _i_val, wxString const & _i_comment, bool _i_only_if_exists);

    seems there is a limit for virtual methods, hasto be 64 / 68 ?

    BUG :
    bool SetInactiveVar(const wxString& _i_key, const wxString& _i_val);    //!< add an inactive CustomVar
    bool UnsetInactiveVar(const wxString& _i_key);                          //!< del an inactive CustomVar
    void UnsetAllInactiveVars();                                            //!< del all inactive CustomVars
    const CustomVarHash& GetAllInactiveVars() const;                           //!< get all inactive CustomVars
    bool PSetVar(wxString const & _i_key, wxString const & _i_val, int _i_flags, wxString const & _i_comment, bool _i_only_if_exists);

    OK :
    virtual bool SetInactiveVar(const wxString& _i_key, const wxString& _i_val);    //!< add an inactive CustomVar
    virtual bool UnsetInactiveVar(const wxString& _i_key);                          //!< del an inactive CustomVar
    virtual void UnsetAllInactiveVars();                                            //!< del all inactive CustomVars
    virtual const CustomVarHash& GetAllInactiveVars() const;                           //!< get all inactive CustomVars
    bool PSetVar(wxString const & _i_key, wxString const & _i_val, int _i_flags, wxString const & _i_comment, bool _i_only_if_exists);

    In fact :
    - wxsproject is not recompiled, but is in CB code
    - wxsmith / wxsproject is in CB code although wxsmith is not on ./configure line

       -----------------------------------------------------
    => HAS TO COMPILE WXSMITH !!! ( but no wxcontrib is OK )
       -----------------------------------------------------

----------------------------------------------------------------------------------------------------
2019.11.25  BUG
----------------------------------------------------------------------------------------------------
events order :
    1 EVT_TREE_SEL_CHANGING             [ OnTreeSelectionChanging() ]
    2 EVT_TREE_SEL_CHANGED              [ OnTreeSelectionChange()   ]   -> call DoFillVars()
    3 wxEVT_DATAVIEW_SELECTION_CHANGED

com = XRCCTRL(*this, "VarComment", wxTextCtrl)->wxTextEntry::GetValue();    -> assert in gtk
com = XRCCTRL(*this, "VarComment", wxTextCtrl)->GetValue();                 -> ok

Why set m_VarsPrevSelModRow = wxNOT_FOUND in OnTreeSelectionChange() and not in DoFillVars() ?
  because DoFillCompilerDependentSettings(), which calls DoFillVars(), is not called systematically.
