--- src/include/compileoptionsbase.h	2019-11-17 10:20:45.549999136 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileoptionsbase.h	2019-11-17 20:36:17.583890584 +0100
@@ -128,6 +128,10 @@
         virtual bool HasVar(const wxString& key) const;
         virtual const wxString& GetVar(const wxString& key) const;
         virtual const StringHash& GetAllVars() const;
+        virtual bool SetVarInactive(const wxString& _i_key, const wxString& _i_val);
+        virtual bool UnsetVarInactive(const wxString& _i_key);
+        virtual void UnsetAllVarsInactive();
+        virtual const StringHash& GetAllVarsInactive() const;
     protected:
         int m_Platform;
         LinkerExecutableOption m_LinkerExecutable;
@@ -144,6 +148,7 @@
         bool m_Modified;
         bool m_AlwaysRunPostCmds;
         StringHash m_Vars;
+        StringHash m_VarsInactive;
     private:
 };
 
