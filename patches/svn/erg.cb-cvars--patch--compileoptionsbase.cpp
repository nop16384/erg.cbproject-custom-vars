--- src/sdk/compileoptionsbase.cpp	2019-11-17 10:20:40.370017520 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileoptionsbase.cpp	2019-11-24 18:51:41.785795709 +0100
@@ -520,28 +520,37 @@
     }
 }
 
-bool CompileOptionsBase::SetVar(const wxString& key, const wxString& value, bool onlyIfExists)
+bool CompileOptionsBase::PSetVar(wxString const & _i_key, wxString const & _i_val, int _i_flags, wxString const & _i_comment, bool _i_only_if_exists)
 {
-    if (onlyIfExists)
+    CustomVarHash   &   cvh = ( _i_flags & eVarActive ) ? m_ActiveVars : m_InactiveVars;
+    CustomVar           cv  = { _i_val, _i_comment, _i_flags };
+    //  ............................................................................................
+    if ( _i_only_if_exists )
     {
-        StringHash::iterator it = m_Vars.find(key);
-        if (it == m_Vars.end())
+        CustomVarHash::iterator it = cvh.find(_i_key);
+        if (it == cvh.end())
             return false;
-        it->second = value;
+        it->second = cv;
+        SetModified(true);                                                                          // _ERG_CORR_ added, was missing
         return true;
     }
 
-    m_Vars[key] = value;
+    cvh[_i_key] = cv;
     SetModified(true);
     return true;
 }
 
+bool CompileOptionsBase::SetVar(const wxString& key, const wxString& value, bool onlyIfExists)
+{
+    return PSetVar(key, value, eVarActive, wxString(""), onlyIfExists);
+}
+
 bool CompileOptionsBase::UnsetVar(const wxString& key)
 {
-    StringHash::iterator it = m_Vars.find(key);
-    if (it != m_Vars.end())
+    CustomVarHash::iterator it = m_ActiveVars.find(key);
+    if (it != m_ActiveVars.end())
     {
-        m_Vars.erase(it);
+        m_ActiveVars.erase(it);
         SetModified(true);
         return true;
     }
@@ -550,13 +559,14 @@
 
 void CompileOptionsBase::UnsetAllVars()
 {
-    m_Vars.clear();
+    SetModified(true);                                                                              // _ERG_CORR_ added, was missing
+    m_ActiveVars.clear();
 }
 
 bool CompileOptionsBase::HasVar(const wxString& key) const
 {
-    StringHash::const_iterator it = m_Vars.find(key);
-    if (it != m_Vars.end())
+    CustomVarHash::const_iterator it = m_ActiveVars.find(key);
+    if (it != m_ActiveVars.end())
         return true;
 
     return false;
@@ -564,19 +574,47 @@
 
 const wxString& CompileOptionsBase::GetVar(const wxString& key) const
 {
-    StringHash::const_iterator it = m_Vars.find(key);
-    if (it != m_Vars.end())
-        return it->second;
+    CustomVarHash::const_iterator it = m_ActiveVars.find(key);
+    if (it != m_ActiveVars.end())
+        return it->second.value;
 
     static wxString emptystring = wxEmptyString;
     return emptystring;
 }
 
-const StringHash& CompileOptionsBase::GetAllVars() const
+const CustomVarHash& CompileOptionsBase::GetAllVars() const
+{
+    return m_ActiveVars;
+}
+
+bool CompileOptionsBase::SetInactiveVar(const wxString& _i_key, const wxString& _i_val)
 {
-    return m_Vars;
+    return PSetVar(_i_key, _i_val, eVarInactive, wxString(""), false);
 }
 
+bool CompileOptionsBase::UnsetInactiveVar(const wxString& _i_key)
+{
+    CustomVarHash::iterator it = m_InactiveVars.find(_i_key);
+
+    if (it != m_InactiveVars.end())
+    {
+        m_InactiveVars.erase(it);
+        SetModified(true);
+        return true;
+    }
+    return false;
+}
+
+void CompileOptionsBase::UnsetAllInactiveVars()
+{
+    SetModified(true);
+    m_InactiveVars.clear();
+}
+
+CustomVarHash const & CompileOptionsBase::GetAllInactiveVars() const
+{
+    return m_InactiveVars;
+}
 void CompileOptionsBase::SetLinkerExecutable(LinkerExecutableOption option)
 {
     if (m_LinkerExecutable == option)
