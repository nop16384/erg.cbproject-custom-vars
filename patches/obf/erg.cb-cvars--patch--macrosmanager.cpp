--- src/sdk/macrosmanager.cpp	2019-11-21 19:02:13.242456297 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/macrosmanager.cpp	2019-11-24 18:51:41.829795887 +0100
@@ -2,9 +2,9 @@
  * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
  * http://www.gnu.org/licenses/lgpl-3.0.html
  *
- * $Revision$
- * $Id$
- * $HeadURL$
+ * $Revision: 11885 $
+ * $Id: macrosmanager.cpp 11885 2019-10-26 09:11:48Z fuscated $
+ * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/macrosmanager.cpp $
  */
 
 #include "sdk_precomp.h"
@@ -211,9 +211,9 @@
 {
     if (object)
     {
-        const StringHash& v = object->GetAllVars();
-        for (StringHash::const_iterator it = v.begin(); it != v.end(); ++it)
-            macros[it->first.Upper()] = it->second;
+        const CustomVarHash& v = object->GetAllVars();
+        for (CustomVarHash::const_iterator it = v.begin(); it != v.end(); ++it)
+            macros[it->first.Upper()] = it->second.value;
     }
 }
 } // namespace
@@ -230,8 +230,8 @@
     // be visible because it was set by a previous target in the build order.
     if (m_LastTarget)
     {
-        const StringHash& v = m_LastTarget->GetAllVars();
-        for (StringHash::const_iterator it = v.begin(); it != v.end(); ++it)
+        const CustomVarHash& v = m_LastTarget->GetAllVars();
+        for (CustomVarHash::const_iterator it = v.begin(); it != v.end(); ++it)
             m_Macros.erase(it->first.Upper());
     }
 
