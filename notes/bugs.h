 (001)  2019.11.24  [all]
    When switching target, vars are just added. No cleanup is done.

 (002)  2019.11.25  [all]
    - target switch -> DoFillVars() { wxDataViewListStore.Clear(); }  ( see bug (001) )
    - But a "selection changed" event happend just after, with the m_VarsPrevSelModRow value of the
    previous target. So exception for bad index when WxModelSaveComment is called, because
    the wxDataViewListStore is now empty !

 (003)  2019.11.25  [all]
    Comment wxTextCtrl not cleared when switching targets

