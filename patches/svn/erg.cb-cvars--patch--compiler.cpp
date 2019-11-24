--- src/sdk/compiler.cpp	2019-11-17 10:20:44.570002587 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compiler.cpp	2019-11-24 18:51:41.825795870 +0100
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
