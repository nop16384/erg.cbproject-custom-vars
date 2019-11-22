--- src/sdk/compileoptionsbase.cpp	2019-11-21 19:02:13.238456286 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileoptionsbase.cpp	2019-11-22 21:37:39.051631884 +0100
@@ -2,9 +2,9 @@
  * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
  * http://www.gnu.org/licenses/lgpl-3.0.html
  *
- * $Revision$
- * $Id$
- * $HeadURL$
+ * $Revision: 11887 $
+ * $Id: compileoptionsbase.cpp 11887 2019-10-26 09:12:28Z fuscated $
+ * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/compileoptionsbase.cpp $
  */
 
 #include "sdk_precomp.h"
@@ -550,6 +550,7 @@
 
 void CompileOptionsBase::UnsetAllVars()
 {
+    SetModified(true);                                                                              // _ERG_CORR_ added, was missing
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
 
+void CompileOptionsBase::UnsetAllVarsInactive()
+{
+    SetModified(true);
+    m_VarsInactive.clear();
+}
+
+StringHash const & CompileOptionsBase::GetAllVarsInactive() const
+{
+    return m_VarsInactive;
+}
 void CompileOptionsBase::SetLinkerExecutable(LinkerExecutableOption option)
 {
     if (m_LinkerExecutable == option)
