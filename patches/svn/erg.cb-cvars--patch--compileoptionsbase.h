--- src/include/compileoptionsbase.h	2019-11-17 10:20:45.549999136 +0100
+++ /home/gwr/Src/C-C++/codeblocks/erg.cbproject-custom-vars/branch-master/out/pub/compileoptionsbase.h	2019-11-24 18:51:41.781795693 +0100
@@ -11,6 +11,15 @@
 
 WX_DECLARE_STRING_HASH_MAP(wxString, StringHash);
 
+typedef struct
+{
+    wxString    value;
+    wxString    comment;
+    int         flags;
+} CustomVar;
+
+WX_DECLARE_STRING_HASH_MAP(CustomVar, CustomVarHash);
+
 /// Enum which specifies which executable from the toolchain executables would be used for linking
 /// the target.
 enum class LinkerExecutableOption : int32_t
@@ -47,6 +56,13 @@
 class DLLIMPORT CompileOptionsBase
 {
     public:
+        enum
+        {
+            eVarInactive    =   0x0000  ,
+            eVarActive      =   0x0001
+        };
+
+    public:
         CompileOptionsBase();
         virtual ~CompileOptionsBase();
 
@@ -127,7 +143,11 @@
         virtual void UnsetAllVars();
         virtual bool HasVar(const wxString& key) const;
         virtual const wxString& GetVar(const wxString& key) const;
-        virtual const StringHash& GetAllVars() const;
+        virtual const CustomVarHash& GetAllVars() const;
+        virtual bool SetInactiveVar(const wxString& _i_key, const wxString& _i_val);                //!< add an inactive CustomVar
+        virtual bool UnsetInactiveVar(const wxString& _i_key);                                      //!< del an inactive CustomVar
+        virtual void UnsetAllInactiveVars();                                                        //!< del all inactive CustomVars
+        virtual const CustomVarHash& GetAllInactiveVars() const;                                    //!< get all inactive CustomVars
     protected:
         int m_Platform;
         LinkerExecutableOption m_LinkerExecutable;
@@ -143,8 +163,10 @@
         wxArrayString m_Scripts;
         bool m_Modified;
         bool m_AlwaysRunPostCmds;
-        StringHash m_Vars;
+        CustomVarHash   m_ActiveVars;                                                               //!< map for active CustomVars
+        CustomVarHash   m_InactiveVars;                                                             //!< map for inactive CustomVars
     private:
+        bool PSetVar(wxString const & _i_key, wxString const & _i_val, int _i_flags, wxString const & _i_comment, bool _i_only_if_exists); //!< really set var
 };
 
 #endif // COMPILEOPTIONSBASE_H
