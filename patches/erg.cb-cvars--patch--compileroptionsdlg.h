--- src/plugins/compilergcc/compileroptionsdlg.h	2019-11-17 10:20:39.298021367 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileroptionsdlg.h	2019-11-17 20:36:17.591890610 +0100
@@ -24,6 +24,9 @@
 class wxPropertyGrid;
 class wxPropertyGridEvent;
 class wxUpdateUIEvent;
+class wxDataViewListCtrl;
+class wxDataViewListStore;
+class wxDataViewEvent;
 
 class CompilerOptionsDlg : public cbConfigurationPanel
 {
@@ -36,23 +39,12 @@
         virtual void OnApply();
         virtual void OnCancel(){}
     private:
-        enum CustomVarActionType
-        {
-            CVA_Add,
-            CVA_Edit,
-            CVA_Remove
-        };
-
-        struct CustomVarAction
-        {
-            CustomVarActionType m_Action;
-            wxString            m_Key;
-            wxString            m_KeyValue;
-        };
+
         void TextToOptions();
         void OptionsToText();
         void DoFillCompilerSets(int compilerIdx);
         void DoFillCompilerPrograms();
+        void DvlsAddVar(wxString const& _i_key, wxString const& _i_val, bool _i_active);
         void DoFillVars();
         void DoFillOthers();
         void DoFillOptions();
@@ -83,7 +75,8 @@
         void OnClearDirClick(wxCommandEvent& event);
         void OnCopyDirsClick(wxCommandEvent& event);
         void OnAddVarClick(wxCommandEvent& event);
-        void OnEditVarClick(wxCommandEvent& event);
+        void OnBrowseVarClick(wxCommandEvent& event);
+        void OnChangedVarClick(wxDataViewEvent&);
         void OnRemoveVarClick(wxCommandEvent& event);
         void OnClearVarClick(wxCommandEvent& event);
         void OnSetDefaultCompilerClick(wxCommandEvent& event);
@@ -125,12 +118,13 @@
         wxArrayString                m_LinkLibs;
         wxArrayString                m_CompilerOptions;
         wxArrayString                m_ResourceCompilerOptions;
+        wxDataViewListCtrl      *    d_dvlc;
+        wxDataViewListStore     *    d_dvls;
         int                          m_CurrentCompilerIdx;
         cbProject*                   m_pProject;
         ProjectBuildTarget*          m_pTarget;
         bool                         m_bDirty;                       //!< true if a setting has changed since last save
         bool                         m_bFlagsDirty;                  //!< true if a flag (not its value) has changed since last save
-        std::vector<CustomVarAction> m_CustomVarActions;             //!< the actions carried out on the custom vars that need to be saved/applied
         wxString                     m_NewProjectOrTargetCompilerId; //!< keeps track of the changes of compiler of the selected project/target
 
         bool                         m_BuildingTree;                 //!< flag to ignore tree changing events while building it
