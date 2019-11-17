--- src/sdk/compileoptionsbase.cpp	2019-11-17 10:20:40.370017520 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileoptionsbase.cpp	2019-11-17 20:36:17.587890596 +0100
@@ -550,6 +550,7 @@
 
 void CompileOptionsBase::UnsetAllVars()
 {
+    SetModified(true);                                                                              // _ERG_BCOR_ added, was missing
     m_Vars.clear();
 }
 
@@ -576,7 +577,35 @@
 {
     return m_Vars;
 }
+bool CompileOptionsBase::SetVarInactive(const wxString& _i_key, const wxString& _i_val)
+{
+    m_VarsInactive[_i_key] = _i_val;
+    SetModified(true);
+    return true;
+}
+
+bool CompileOptionsBase::UnsetVarInactive(const wxString& _i_key)
+{
+    StringHash::iterator it = m_VarsInactive.find(_i_key);
+    if (it != m_VarsInactive.end())
+    {
+        m_VarsInactive.erase(it);
+        SetModified(true);
+        return true;
+    }
+    return false;
+}
+
+void CompileOptionsBase::UnsetAllVarsInactive()
+{
+    SetModified(true);
+    m_VarsInactive.clear();
+}
 
+StringHash const & CompileOptionsBase::GetAllVarsInactive() const
+{
+    return m_VarsInactive;
+}
 void CompileOptionsBase::SetLinkerExecutable(LinkerExecutableOption option)
 {
     if (m_LinkerExecutable == option)
