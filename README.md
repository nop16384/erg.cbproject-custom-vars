erg.cbproject-custom-vars
=========================

Enhanced "custom vars" edition for C::B project's "build options".

## 00 Preambule
* More up-to-date, nicer widgets ( wxDataViewListCtrl vs wxListBox )
* Possibility of saving inactive vars ( vars that wont show up on compile command line ) - Until now when you dont a var to be defined in the compilation, you have to delete the var.
* Sort widgets be key, value or active / inactive status


## 01 Branches

### 01.01 Branch master
Main coding.

### 01.02 Branch pub
Releases.

### 01.03 Branch doc
Documentation.

## 03 Screenshots

![scr-001](https://github.com/earlgrey-bis/erg.cbproject-custom-vars/blob/doc/scr/cvars-19.11.16-001.png "screenshot-001.png")
## 04 Tech
### 04.01 Principle
A StringHash named *m_VarsInactive* is added to the *CompileOptionsBase* class. This StringHash contains all inactive vars. The *m_Vars* member of *CompileOptionsBase* is said to hold the active vars.
> CompileOptionsBase.h  
> `StringHash m_Vars;`  
> `StringHash m_VarsInactive;`

The *CompilerOptionsDialog* class therefore get the active and inactive vars from *CompileOptionsBase*, let the user edit them together , and at the end separate them again in active and inactive vars.

For the rest of C::B code, exception made of *ProjectLoader* class, which needs to load / save active and inactive vars, only active vars ( i.e. `CompileOptionsBase::m_Vars` ) exist, as before.

### 04.02 UI changes
* The "Edit" button has been removed, since the vars can be edited from inside the *wxDataViewListCtrl*. The "browse" functionality remains, in a new "Browse" button that replace the "Edit" one.
* The "Variables:" label has been removed, since it is unuseful : the tab is already named "Custom variables".

### 04.03 Build
```
PROJECT_DIR
          +--- build
          |
          +--- notes
          | 
          +--- out
          |      |
          |      +--- pub
          |      |
          |      +--- export
          |
          +--- src
```
* The "dev" target simply copy the files in the "export" dir
* The "pub" target :
    * supress dev comments ("ERG" marks )
    * generate patches
    * copy files & patches to "pub" dir
    * copy files to "export": dir