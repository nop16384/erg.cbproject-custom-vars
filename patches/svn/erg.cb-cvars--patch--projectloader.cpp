--- src/sdk/projectloader.cpp	2019-11-17 10:20:40.370017520 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/projectloader.cpp	2019-11-24 18:51:41.793795741 +0100
@@ -4,7 +4,7 @@
  *
  * $Revision: 11906 $
  * $Id: projectloader.cpp 11906 2019-11-09 12:05:35Z fuscated $
- * $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/trunk/src/sdk/projectloader.cpp $
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
+                    base->SetInactiveVar(name, UnixFilename(value));
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
+    CustomVarHash   const   &   va  =   base->GetAllVars();
+    CustomVarHash   const   &   vi  =   base->GetAllInactiveVars();
     // explicitly sort the keys
     typedef std::map<wxString, wxString> SortedMap;
-    SortedMap map;
-    for (StringHash::const_iterator it = v.begin(); it != v.end(); ++it)
-        map[it->first] = it->second;
-
+    SortedMap mapa;
+    for (CustomVarHash::const_iterator it = va.begin(); it != va.end(); ++it)
+        mapa[it->first] = it->second.value;
+    SortedMap mapi;
+    for (CustomVarHash::const_iterator it = vi.begin(); it != vi.end(); ++it)
+        mapi[it->first] = it->second.value;
     TiXmlElement* node = AddElement(parent, "Environment");
-    for (SortedMap::const_iterator it = map.begin(); it != map.end(); ++it)
+    //  ERg {
+    for (SortedMap::const_iterator it = mapa.begin(); it != mapa.end(); ++it)
+    {
+        TiXmlElement* elem = AddElement(node, "Variable", "name", it->first);
+        elem->SetAttribute("value", cbU2C(it->second));
+        //  active var <=> attribute "active" is present
+        elem->SetAttribute("active", "");
+    }
+    for (SortedMap::const_iterator it = mapi.begin(); it != mapi.end(); ++it)
     {
         TiXmlElement* elem = AddElement(node, "Variable", "name", it->first);
         elem->SetAttribute("value", cbU2C(it->second));
+        //  active var <=> attribute "active" is present
+        //elem->SetAttribute("inactive", "");
     }
 }
 
