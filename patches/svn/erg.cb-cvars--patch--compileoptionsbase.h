--- src/include/compileoptionsbase.h	2019-11-17 10:20:45.549999136 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileoptionsbase.h	2019-11-22 21:37:39.047631888 +0100
@@ -128,6 +128,10 @@
         virtual bool HasVar(const wxString& key) const;
         virtual const wxString& GetVar(const wxString& key) const;
         virtual const StringHash& GetAllVars() const;
+        virtual bool SetVarInactive(const wxString& _i_key, const wxString& _i_val);    //!< add an inactive CustomVar
+        virtual bool UnsetVarInactive(const wxString& _i_key);                          //!< del an inactive CustomVar
+        virtual void UnsetAllVarsInactive();                                            //!< del all inactive CustomVars
+        virtual const StringHash& GetAllVarsInactive() const;                           //!< get all inactive CustomVars
     protected:
         int m_Platform;
         LinkerExecutableOption m_LinkerExecutable;
@@ -143,7 +147,8 @@
         wxArrayString m_Scripts;
         bool m_Modified;
         bool m_AlwaysRunPostCmds;
-        StringHash m_Vars;
+        StringHash m_Vars;                                                              //!< map for active CustomVars
+        StringHash m_VarsInactive;                                                      //!< map for inactive CustomVars
     private:
 };
 
