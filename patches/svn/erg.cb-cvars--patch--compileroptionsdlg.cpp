--- src/plugins/compilergcc/compileroptionsdlg.cpp	2019-11-17 10:20:39.246021554 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileroptionsdlg.cpp	2019-11-24 18:51:41.809795806 +0100
@@ -27,6 +27,7 @@
     #include <wx/textdlg.h>
     #include <wx/treectrl.h>
     #include <wx/xrc/xmlres.h>
+    #include <wx/dataview.h>
 
     #include "compiler.h"
     #include "compilerfactory.h"
@@ -40,7 +41,7 @@
 #include <wx/filedlg.h>
 #include <wx/propgrid/propgrid.h>
 #include <wx/xml/xml.h>
-
+#include <wx/dataview.h>
 #include "advancedcompileroptionsdlg.h"
 #include "annoyingdialog.h"
 #include "cbexception.h"
@@ -63,9 +64,9 @@
     EVT_UPDATE_UI(            XRCID("btnCopyDirs"),                     CompilerOptionsDlg::OnUpdateUI)
     EVT_UPDATE_UI(            XRCID("btnMoveDirUp"),                    CompilerOptionsDlg::OnUpdateUI)
     EVT_UPDATE_UI(            XRCID("btnMoveDirDown"),                  CompilerOptionsDlg::OnUpdateUI)
-    EVT_UPDATE_UI(            XRCID("btnEditVar"),                      CompilerOptionsDlg::OnUpdateUI)
+    EVT_UPDATE_UI(            XRCID("btnBrowseVar"),                    CompilerOptionsDlg::OnUpdateUI)
     EVT_UPDATE_UI(            XRCID("btnDeleteVar"),                    CompilerOptionsDlg::OnUpdateUI)
-    EVT_UPDATE_UI(            XRCID("btnClearVar"),                     CompilerOptionsDlg::OnUpdateUI)
+    EVT_UPDATE_UI(            XRCID("btnDeleteAllVars"),                CompilerOptionsDlg::OnUpdateUI)
     EVT_UPDATE_UI(            XRCID("cmbCompilerPolicy"),               CompilerOptionsDlg::OnUpdateUI)
     EVT_UPDATE_UI(            XRCID("cmbLinkerPolicy"),                 CompilerOptionsDlg::OnUpdateUI)
     EVT_UPDATE_UI(            XRCID("cmbIncludesPolicy"),               CompilerOptionsDlg::OnUpdateUI)
@@ -110,7 +111,6 @@
     EVT_TREE_SEL_CHANGING(     XRCID("tcScope"),                        CompilerOptionsDlg::OnTreeSelectionChanging)
     EVT_CHOICE(                XRCID("cmbCategory"),                    CompilerOptionsDlg::OnCategoryChanged)
     EVT_CHOICE(                XRCID("cmbCompiler"),                    CompilerOptionsDlg::OnCompilerChanged)
-    EVT_LISTBOX_DCLICK(        XRCID("lstVars"),                        CompilerOptionsDlg::OnEditVarClick)
     EVT_BUTTON(                XRCID("btnSetDefaultCompiler"),          CompilerOptionsDlg::OnSetDefaultCompilerClick)
     EVT_BUTTON(                XRCID("btnAddCompiler"),                 CompilerOptionsDlg::OnAddCompilerClick)
     EVT_BUTTON(                XRCID("btnRenameCompiler"),              CompilerOptionsDlg::OnEditCompilerClick)
@@ -139,10 +139,10 @@
     EVT_BUTTON(                XRCID("btnMoveLibDown"),                 CompilerOptionsDlg::OnMoveLibDownClick)
     EVT_BUTTON(                XRCID("btnMoveDirUp"),                   CompilerOptionsDlg::OnMoveDirUpClick)
     EVT_BUTTON(                XRCID("btnMoveDirDown"),                 CompilerOptionsDlg::OnMoveDirDownClick)
-    EVT_BUTTON(                XRCID("btnAddVar"),                      CompilerOptionsDlg::OnAddVarClick)
-    EVT_BUTTON(                XRCID("btnEditVar"),                     CompilerOptionsDlg::OnEditVarClick)
+    EVT_BUTTON(                XRCID("btnNewVar"),                      CompilerOptionsDlg::OnAddVarClick)
+    EVT_BUTTON(                XRCID("btnBrowseVar"),                   CompilerOptionsDlg::OnBrowseVarClick)
     EVT_BUTTON(                XRCID("btnDeleteVar"),                   CompilerOptionsDlg::OnRemoveVarClick)
-    EVT_BUTTON(                XRCID("btnClearVar"),                    CompilerOptionsDlg::OnClearVarClick)
+    EVT_BUTTON(                XRCID("btnDeleteAllVars"),               CompilerOptionsDlg::OnDeleteAllVarsClick)
     EVT_BUTTON(                XRCID("btnMasterPath"),                  CompilerOptionsDlg::OnMasterPathClick)
     EVT_BUTTON(                XRCID("btnAutoDetect"),                  CompilerOptionsDlg::OnAutoDetectClick)
     EVT_BUTTON(                XRCID("btnCcompiler"),                   CompilerOptionsDlg::OnSelectProgramClick)
@@ -241,7 +241,35 @@
 
     m_FlagsPG->SetMinSize(wxSize(400, 400));
     wxXmlResource::Get()->AttachUnknownControl(wxT("pgCompilerFlags"), m_FlagsPG);
+    wxWindow    *   w1          =   XRCCTRL(*this, "tabVars", wxPanel);
+    wxSizer     *   bsz         =   w1->GetSizer();
+    wxSizerFlags    sizerflags;
+    int             colflags    = wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE;
+    size_t          idx         =   0;
+
+    m_VarsWxCtrl    =   new wxDataViewListCtrl  (w1, wxID_ANY);
+    m_VarsWxModel   =   new wxDataViewListStore ();
+    m_VarsWxCtrl->AssociateModel(m_VarsWxModel);
+
+    wxDataViewRenderer  *   dvr0    =   new wxDataViewToggleRenderer(wxString("bool"), wxDATAVIEW_CELL_ACTIVATABLE , wxDVR_DEFAULT_ALIGNMENT );
+    wxDataViewColumn    *   dvc0    =   new wxDataViewColumn(wxString("Set")    , dvr0, 0,  75, wxALIGN_CENTER, colflags );
+
+    wxDataViewRenderer  *   dvr1    =   new wxDataViewTextRenderer(wxString("string"), wxDATAVIEW_CELL_EDITABLE , wxDVR_DEFAULT_ALIGNMENT );
+    wxDataViewColumn    *   dvc1    =   new wxDataViewColumn(wxString("Key")    , dvr1, 1, 150, wxALIGN_LEFT, colflags);
+
+    wxDataViewRenderer  *   dvr2    =   new wxDataViewTextRenderer(wxString("string"), wxDATAVIEW_CELL_EDITABLE , wxDVR_DEFAULT_ALIGNMENT );
+    wxDataViewColumn    *   dvc2    =   new wxDataViewColumn(wxString("Value")  , dvr2, 2,  80, wxALIGN_LEFT, colflags);
+
+    m_VarsWxCtrl->AppendColumn(dvc0);
+    m_VarsWxCtrl->AppendColumn(dvc1);
+    m_VarsWxCtrl->AppendColumn(dvc2);
+
+    wxXmlResource::Get()->AttachUnknownControl(wxT("ErgCustomVars"), m_VarsWxCtrl);
+
+    sizerflags.Expand().Proportion(1);  // sizeritem for ID_STATICTEXT16 "These variables... " has wxEXPAND so we need to set Proportion
+    bsz->Insert(idx, m_VarsWxCtrl, sizerflags);
 
+    Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &CompilerOptionsDlg::OnChangedVarClick, this);
     if (m_pProject)
     {
         bool hasBuildScripts = m_pProject->GetBuildScripts().GetCount() != 0;
@@ -511,25 +539,37 @@
     ArrayString2ListBox(extraPaths, XRCCTRL(*this, "lstExtraPaths", wxListBox));
 } // DoFillCompilerPrograms
 
+void CompilerOptionsDlg::WxModelAddVarHelper(wxString const& _i_key, wxString const& _i_val, bool _i_active)
+{
+    wxVector<wxVariant>     row;
+    //  ............................................................................................
+    row.push_back( wxVariant(_i_active) );
+    row.push_back( wxVariant(_i_key)    );
+    row.push_back( wxVariant(_i_val)    );
+
+    m_VarsWxModel->AppendItem(row);
+}
 void CompilerOptionsDlg::DoFillVars()
 {
-    wxListBox* lst = XRCCTRL(*this, "lstVars", wxListBox);
-    if (!lst)
+    const CustomVarHash         *   va      =   0;
+    const CustomVarHash         *   vi      =   0;
+    const CompileOptionsBase    *   base    =   GetVarsOwner();
+    //  ............................................................................................
+    if ( ! base )
         return;
-    lst->Clear();
-    const StringHash* vars = 0;
-    const CompileOptionsBase* base = GetVarsOwner();
-    if (base)
-    {
-        vars = &base->GetAllVars();
-    }
-    if (!vars)
+
+    va  =   &base->GetAllVars();
+    vi  =   &base->GetAllInactiveVars();
+    if ( ( ! va ) || ( ! vi ) )
         return;
-    for (StringHash::const_iterator it = vars->begin(); it != vars->end(); ++it)
-    {
-        wxString text = it->first + _T(" = ") + it->second;
-        lst->Append(text, new VariableListClientData(it->first, it->second));
-    }
+
+    m_VarsWxModel->DeleteAllItems();
+
+    for (CustomVarHash::const_iterator it = va->begin(); it != va->end(); ++it)
+        WxModelAddVarHelper(it->first, it->second.value, true);
+
+    for (CustomVarHash::const_iterator it = vi->begin(); it != vi->end(); ++it)
+        WxModelAddVarHelper(it->first, it->second.value, false);
 } // DoFillVars
 
 void CompilerOptionsDlg::DoFillOthers()
@@ -1146,38 +1186,29 @@
 
 void CompilerOptionsDlg::DoSaveVars()
 {
-    CompileOptionsBase* pBase = GetVarsOwner();
-    if (pBase)
+    CompileOptionsBase  *   base    =   GetVarsOwner();
+    //  ............................................................................................
+    if ( ! base )
+        return;
+
+    base->UnsetAllVars();
+    base->UnsetAllInactiveVars();
+
+    for ( unsigned int ridx = 0 ; ridx != m_VarsWxModel->GetItemCount() ; ridx++ )
     {
-        // let's process all the stored CustomVarActions
-        for (unsigned int idxAction = 0; idxAction < m_CustomVarActions.size(); ++idxAction)
-        {
-            CustomVarAction Action = m_CustomVarActions[idxAction];
-            switch(Action.m_Action)
-            {
-                case CVA_Add:
-                    pBase->SetVar(Action.m_Key, Action.m_KeyValue);
-                    break;
-                case CVA_Edit:
-                {
-                    // first split up the KeyValue
-                    wxString NewKey = Action.m_KeyValue.BeforeFirst(_T('=')).Trim(true).Trim(false);
-                    wxString NewValue = Action.m_KeyValue.AfterFirst(_T('=')).Trim(true).Trim(false);
-                    if (Action.m_Key != NewKey)
-                    {   // the key name changed
-                        pBase->UnsetVar(Action.m_Key);
-                    }
-                    pBase->SetVar(NewKey, NewValue);
-                    break;
-                }
-                case CVA_Remove:
-                    pBase->UnsetVar(Action.m_Key);
-                    break;
-                default:
-                    break;
-            } // end switch
-        } // end for : idx : idxAction
-        m_CustomVarActions.clear();
+        wxVariant   va, vk, vv;
+        m_VarsWxModel->GetValueByRow(va, ridx, 0);
+        m_VarsWxModel->GetValueByRow(vk, ridx, 1);
+        m_VarsWxModel->GetValueByRow(vv, ridx, 2);
+
+        bool        active  = va.GetBool();
+        wxString    key     = vk.GetString().Trim(true).Trim(false);
+        wxString    val     = vv.GetString().Trim(true).Trim(false);
+
+        if ( active )
+            base->SetVar(key, val);
+        else
+            base->SetInactiveVar(key, val);
     }
 } // DoSaveVars
 
@@ -2026,89 +2057,59 @@
         key.Trim(true).Trim(false);
         value.Trim(true).Trim(false);
         QuoteString(value, _("Add variable quote string"));
-        CustomVarAction Action = {CVA_Add, key, value};
-        m_CustomVarActions.push_back(Action);
-        XRCCTRL(*this, "lstVars", wxListBox)->Append(key + _T(" = ") + value, new VariableListClientData(key, value));
+        WxModelAddVarHelper(key, value ,true);
         m_bDirty = true;
     }
 } // OnAddVarClick
 
-void CompilerOptionsDlg::OnEditVarClick(cb_unused wxCommandEvent& event)
+
+
+void CompilerOptionsDlg::OnBrowseVarClick(cb_unused wxCommandEvent& event)
 {
-    wxListBox *list = XRCCTRL(*this, "lstVars", wxListBox);
-    int sel = list->GetSelection();
-    if (sel == -1)
+    wxString dir = ChooseDirectory(this);
+    if ( dir.IsEmpty() )
         return;
 
-    VariableListClientData *data = static_cast<VariableListClientData*>(list->GetClientObject(sel));
-    wxString key = data->key;
-    wxString value = data->value;
+    int sel = m_VarsWxCtrl->GetSelectedRow();
+    if ( sel == wxNOT_FOUND )                                                                       // should not happend cf OnUpdateUI()
+        return;
 
-    EditPairDlg dlg(this, key, value, _("Edit variable"), EditPairDlg::bmBrowseForDirectory);
-    PlaceWindow(&dlg);
-    if (dlg.ShowModal() == wxID_OK)
-    {
-        key.Trim(true).Trim(false);
-        value.Trim(true).Trim(false);
-        QuoteString(value, _("Edit variable quote string"));
+    m_VarsWxCtrl->SetTextValue(dir, sel, 2);                                                        // this will update the wxDataViewListStore too
 
-        if (value != data->value  ||  key != data->key)
-        { // something has changed
-            CustomVarAction Action = {CVA_Edit, data->key, key + _T(" = ") + value};
-            m_CustomVarActions.push_back(Action);
-            list->SetString(sel, key + _T(" = ") + value);
-            data->key = key;
-            data->value = value;
-            m_bDirty = true;
-        }
-    }
-} // OnEditVarClick
+    m_bDirty = true;
+}
+
+void CompilerOptionsDlg::OnChangedVarClick(cb_unused wxDataViewEvent& event)
+{
+    m_bDirty = true;
+}
 
 void CompilerOptionsDlg::OnRemoveVarClick(cb_unused wxCommandEvent& event)
 {
-    wxListBox *list = XRCCTRL(*this, "lstVars", wxListBox);
-    int sel = list->GetSelection();
-    if (sel == -1)
-        return;
-    const wxString &key = static_cast<VariableListClientData*>(list->GetClientObject(sel))->key;
-    if (key.IsEmpty())
+
+    int sel = m_VarsWxCtrl->GetSelectedRow();
+    if ( sel == wxNOT_FOUND )                                                                       // should not happend cf OnUpdateUI()
         return;
 
     if (cbMessageBox(_("Are you sure you want to delete this variable?"),
                     _("Confirmation"),
                     wxYES_NO | wxICON_QUESTION) == wxID_YES)
     {
-        CustomVarAction Action = {CVA_Remove, key, wxEmptyString};
-        m_CustomVarActions.push_back(Action);
-        list->Delete(sel);
+        m_VarsWxCtrl->DeleteItem(sel);                                                              // this will update the wxDataViewListStore too
         m_bDirty = true;
     }
 } // OnRemoveVarClick
 
-void CompilerOptionsDlg::OnClearVarClick(cb_unused wxCommandEvent& event)
+void CompilerOptionsDlg::OnDeleteAllVarsClick(cb_unused wxCommandEvent& event)
 {
-    wxListBox* lstVars = XRCCTRL(*this, "lstVars", wxListBox);
-    if (lstVars->IsEmpty())
-        return;
-
     if (cbMessageBox(_("Are you sure you want to clear all variables?"),
                         _("Confirmation"),
                         wxYES | wxNO | wxICON_QUESTION) == wxID_YES)
     {
-        // Unset all variables of lstVars
-        for (size_t i=0; i < lstVars->GetCount(); ++i)
-        {
-            const wxString &key = static_cast<VariableListClientData*>(lstVars->GetClientObject(i))->key;
-            if (!key.IsEmpty())
-            {
-                CustomVarAction Action = {CVA_Remove, key, wxEmptyString};
-                m_CustomVarActions.push_back(Action);
-            }
-        }
-        lstVars->Clear();
+        m_VarsWxCtrl->DeleteAllItems();                                                             // this will update the wxDataViewListStore too
         m_bDirty = true;
     }
-} // OnClearVarClick
+} // OnDeleteAllVarsClick
 
 void CompilerOptionsDlg::OnSetDefaultCompilerClick(cb_unused wxCommandEvent& event)
 {
@@ -2771,11 +2772,13 @@
     }
 
     // add/edit/delete/clear vars
-    en = XRCCTRL(*this, "lstVars", wxListBox)->GetSelection() >= 0;
-    XRCCTRL(*this, "btnEditVar",   wxButton)->Enable(en);
-    XRCCTRL(*this, "btnDeleteVar", wxButton)->Enable(en);
-    XRCCTRL(*this, "btnClearVar",  wxButton)->Enable(XRCCTRL(*this, "lstVars", wxListBox)->GetCount() != 0);
 
+    // add/browse/delete/clear vars
+    en = ( m_VarsWxCtrl->GetSelectedItemsCount() > 0 );
+    XRCCTRL(*this, "btnBrowseVar"       , wxButton)->Enable(en);
+    XRCCTRL(*this, "btnDeleteVar"       , wxButton)->Enable(en);
+    en = ( m_VarsWxModel->GetItemCount() > 0 );
+    XRCCTRL(*this, "btnDeleteAllVars"   , wxButton)->Enable(en);
     // policies
     wxTreeCtrl* tc = XRCCTRL(*this, "tcScope", wxTreeCtrl);
     ScopeTreeData* data = (ScopeTreeData*)tc->GetItemData(tc->GetSelection());
@@ -2908,7 +2911,7 @@
 
     const wxChar* str_libs[4] = { _T("btnEditLib"),  _T("btnAddLib"),  _T("btnDelLib"),     _T("btnClearLib")   };
     const wxChar* str_dirs[4] = { _T("btnEditDir"),  _T("btnAddDir"),  _T("btnDelDir"),     _T("btnClearDir")   };
-    const wxChar* str_vars[4] = { _T("btnEditVar"),  _T("btnAddVar"),  _T("btnDeleteVar"),  _T("btnClearVar")   };
+    const wxChar* str_vars[4] = { _T("btnEditVar"),  _T("btnNewVar"),  _T("btnDeleteVar"),  _T("btnDeleteAllVars")   };
     const wxChar* str_xtra[4] = { _T("btnExtraEdit"),_T("btnExtraAdd"),_T("btnExtraDelete"),_T("btnExtraClear") };
 
     if (keycode == WXK_RETURN || keycode == WXK_NUMPAD_ENTER)
@@ -2927,8 +2930,8 @@
         { myid =  wxXmlResource::GetXRCID(str_libs[myidx]); }
     else if (id == XRCID("lstIncludeDirs") || id == XRCID("lstLibDirs") || id == XRCID("lstResDirs")) // Directories
         { myid =  wxXmlResource::GetXRCID(str_dirs[myidx]); }
-    else if (id == XRCID("lstVars")) // Custom Vars
-        { myid =  wxXmlResource::GetXRCID(str_vars[myidx]); }
+    else if (id == XRCID("lstVars")) // Custom Vars                                                 // _ERG_TODO_ btnEditVar was deleted !
+    { myid =  wxXmlResource::GetXRCID(str_vars[myidx]); }
     else if (id == XRCID("lstExtraPaths")) // Extra Paths
         { myid =  wxXmlResource::GetXRCID(str_xtra[myidx]); }
     else
