--- src/sdk/projectloader.cpp	2019-11-21 19:02:13.246456308 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/projectloader.cpp	2019-11-22 21:37:39.059631875 +0100
@@ -2,9 +2,9 @@
  * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
  * http://www.gnu.org/licenses/lgpl-3.0.html
  *
- * $Revision$
- * $Id$
- * $HeadURL$
+ * $Revision: 11906 $
+ * $Id: projectloader.cpp 11906 2019-11-09 12:05:35Z fuscated $
+ * $HeadURL: file:///svn/p/codeblocks/code/trunk/src/sdk/projectloader.cpp $
  */
 
 #include "sdk_precomp.h"
@@ -907,10 +907,17 @@
         TiXmlElement* child = node->FirstChildElement("Variable");
         while (child)
         {
-            wxString name  = cbC2U(child->Attribute("name"));
-            wxString value = cbC2U(child->Attribute("value"));
+            //  active var <=> attribute "active" is present
+            wxString    name    = cbC2U(child->Attribute("name"));
+            wxString    value   = cbC2U(child->Attribute("value"));
+            bool        active  = ( child->Attribute("active") != NULL ) ? true : false;
             if (!name.IsEmpty())
-                base->SetVar(name, UnixFilename(value));
+            {
+                if ( active )
+                    base->SetVar(name, UnixFilename(value));
+                else
+                    base->SetVarInactive(name, UnixFilename(value));
+            }
 
             child = child->NextSiblingElement("Variable");
         }
@@ -1203,21 +1210,31 @@
 {
     if (!base)
         return;
-    const StringHash& v = base->GetAllVars();
-    if (v.empty())
-        return;
-
+    StringHash  const   &   v   =   base->GetAllVars();
+    StringHash  const   &   vi  =   base->GetAllVarsInactive();
     // explicitly sort the keys
     typedef std::map<wxString, wxString> SortedMap;
     SortedMap map;
     for (StringHash::const_iterator it = v.begin(); it != v.end(); ++it)
         map[it->first] = it->second;
-
+    SortedMap mapi;
+    for (StringHash::const_iterator it = vi.begin(); it != vi.end(); ++it)
+        mapi[it->first] = it->second;
     TiXmlElement* node = AddElement(parent, "Environment");
+    //  ERg {
     for (SortedMap::const_iterator it = map.begin(); it != map.end(); ++it)
     {
         TiXmlElement* elem = AddElement(node, "Variable", "name", it->first);
         elem->SetAttribute("value", cbU2C(it->second));
+        //  active var <=> attribute "active" is present
+        elem->SetAttribute("active", "");
+    }
+    for (SortedMap::const_iterator it = mapi.begin(); it != mapi.end(); ++it)
+    {
+        TiXmlElement* elem = AddElement(node, "Variable", "name", it->first);
+        elem->SetAttribute("value", cbU2C(it->second));
+        //  active var <=> attribute "active" is present
+        //elem->SetAttribute("inactive", "");
     }
 }
 
