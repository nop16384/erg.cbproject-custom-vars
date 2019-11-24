--- src/sdk/compiler.cpp	2019-11-21 19:02:13.238456286 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compiler.cpp	2019-11-24 18:51:41.825795870 +0100
@@ -2,9 +2,9 @@
  * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
  * http://www.gnu.org/licenses/lgpl-3.0.html
  *
- * $Revision$
- * $Id$
- * $HeadURL$
+ * $Revision: 11182 $
+ * $Id: compiler.cpp 11182 2017-09-29 23:33:53Z fuscated $
+ * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/compiler.cpp $
  */
 
 #include "sdk_precomp.h"
@@ -576,9 +576,9 @@
     // custom vars
     wxString configpath = tmp + _T("/custom_variables/");
     cfg->DeleteSubPath(configpath);
-    const StringHash& v = GetAllVars();
-    for (StringHash::const_iterator it = v.begin(); it != v.end(); ++it)
-        cfg->Write(configpath + it->first, it->second);
+    const CustomVarHash& v = GetAllVars();
+    for (CustomVarHash::const_iterator it = v.begin(); it != v.end(); ++it)
+        cfg->Write(configpath + it->first, it->second.value);
 }
 
 void Compiler::LoadSettings(const wxString& baseKey)
